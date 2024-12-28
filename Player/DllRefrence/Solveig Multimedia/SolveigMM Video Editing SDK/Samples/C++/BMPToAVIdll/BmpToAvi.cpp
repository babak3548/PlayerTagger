////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2004-2012 Solveig Multimedia
//    All rights are reserved.  
//
//    Solveig Multimedia reserves the right to make changes without
//    notice at any time. Solveig Multimedia makes no warranty,
//    expressed, implied or statutory, including but not limited to any implied
//    warranty of merchantability of fitness for any particular purpose, or that
//    the use will not infringe any third party patent, copyright or trademark.
//    Solveig Multimedia must not be liable for any loss or damage
//    arising from its use.
//
//////////////////////////////////////////////////////////////////////////////////
// BmpToAvi.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CodecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef AVI_DLL
#define AVI_DLL
#endif
#include "InternalGraph.h"


CInternalGraph::CInternalGraph(HINSTANCE inst):
m_pGraph	( NULL ),
m_pSource	( NULL ),
m_pEncoder	( NULL ),
m_pMuxer	( NULL ),
m_pDemuxer	( NULL ),
m_pDump		( NULL ),
m_pSourceIMC( NULL ),
m_bOpened	( FALSE ),
m_bExisting	( FALSE ),
m_pControl	( NULL ),
m_pGrabber	( NULL ),
m_hWnd		( NULL ),
m_pParentInst( inst )
{

}

CInternalGraph::~CInternalGraph(void)
{
	if( m_pGraph )
		DestroyGraph();
	if( m_pDump )
	{
		m_pDump.Release();
		m_pDump = NULL;
	}
	if( m_pMuxer )
	{
		m_pMuxer.Release();
		m_pMuxer = NULL;
	}
	if( m_pEncoder )
	{
		m_pEncoder.Release();
		m_pEncoder = NULL;
	}
	if( m_pSourceIMC )
	{
		m_pSourceIMC.Release();
		m_pSourceIMC = NULL;
	}
	if( m_pDemuxer )
	{
		m_pDemuxer.Release();
		m_pDemuxer = NULL;
	}
	if( m_pGrabber )
	{
		m_pGrabber.Release();
		m_pGrabber = NULL;
	}
	if( m_pSource )
	{
		//delete m_pSource;
		m_pSource.Release();
		m_pSource = NULL;
	}
	if( m_pControl )
		m_pControl.Release();
}

HRESULT CInternalGraph::OpenAVIStreamIn( BSTR bstFileName )
{
	m_csFileName.SetString( bstFileName );
	HANDLE hFile = CreateFile(	m_csFileName,
								0,
								0, NULL, OPEN_EXISTING, 
								FILE_ATTRIBUTE_NORMAL,
								NULL );
	if( hFile == INVALID_HANDLE_VALUE )//Not existing file, assumed it should be created
		m_bExisting = FALSE;
	else
		m_bExisting = TRUE;
	CloseHandle(hFile);
	if( FAILED( BuildGraph( m_bExisting ) ) )
		return E_FAIL;
	m_bOpened = TRUE;
	if( !m_bExisting )
		m_pControl->Run();
	return S_OK;
}

HRESULT CInternalGraph::BuildGraph( BOOL bExistingFile )
{
	HRESULT hr = E_FAIL;
	if( !m_pGraph )
	{
		hr = InitFilters( bExistingFile );
		if( FAILED(hr) )
			return hr;
	}
	CheckPointer( m_pGraph, E_POINTER );
	CheckPointer( m_pSource, E_POINTER );
	hr = m_pGraph->AddFilter( m_pSource, L"Source Filter" );
	CheckPointer( m_pDump, E_POINTER );
	hr = m_pGraph->AddFilter( m_pDump, L"Dump Filter" );
	if( !bExistingFile )
	{
		CheckPointer( m_pMuxer, E_POINTER );
		m_pGraph->AddFilter( m_pMuxer, L"AVI muxer" );
		if( m_pEncoder )
		{
			m_pGraph->AddFilter( m_pEncoder, L"Encoder" );
			hr = ConnectFilters( m_pSource, m_pEncoder );
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
			hr = ConnectFilters( m_pEncoder, m_pMuxer );
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
		}
		else
		{
			hr = ConnectFilters( m_pSource, m_pMuxer );
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
		}

		hr = ConnectFilters( m_pMuxer, m_pDump );
		if( FAILED(hr) )
			DestroyGraph();
	}
	else
	{
		CheckPointer( m_pGrabber, E_POINTER );
		m_pGraph->AddFilter( m_pGrabber, L"SampleGrabber" );
		
		CComPtr<ISampleGrabber> pGrabberInterface = NULL;
		hr = m_pGrabber->QueryInterface(IID_ISampleGrabber, (void**)&pGrabberInterface);

		AM_MEDIA_TYPE mt;
		ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
		mt.majortype	= MEDIATYPE_Video;
		mt.subtype		= MEDIASUBTYPE_RGB24;
		mt.formattype	= FORMAT_VideoInfo;
		hr = pGrabberInterface->SetMediaType(&mt);
		FreeMediaType(mt);
		pGrabberInterface.Release();

		CheckPointer( m_pDemuxer, E_POINTER );
		m_pGraph->AddFilter( m_pDemuxer, L"AVI Splitter" );

		hr = ConnectFilters( m_pSource, m_pDemuxer );
		if( FAILED(hr) )
		{
			DestroyGraph();
			return hr;
		}

		hr = ConnectFilters( m_pDemuxer, m_pGrabber );
		if( FAILED(hr) )
		{
			DestroyGraph();
			return hr;
		}

		hr = ConnectFilters( m_pGrabber, m_pDump );
		if( FAILED(hr) )
			DestroyGraph();
	}
	
	return hr;
}
HRESULT CInternalGraph::ConnectFilters( IBaseFilter *pUpstream, IBaseFilter *pDownstream )
{
	CheckPointer( m_pGraph, E_FAIL );
	CheckPointer( pUpstream, E_POINTER );
	CheckPointer( pDownstream, E_POINTER );

	HRESULT hr;
	CComPtr<IPin>		pIPin1 = NULL,
		pIPin2 = NULL;
	CComPtr<IEnumPins>	pEnumPins = NULL;
	CComPtr<IEnumMediaTypes> pEnumMT = NULL;
	AM_MEDIA_TYPE*		mt;
	PIN_DIRECTION PinDirection;
	pUpstream->EnumPins( &pEnumPins );
	while ( hr = pEnumPins->Next( 1, &pIPin1, 0 ), hr == S_OK )
	{
		pIPin1->QueryDirection( &PinDirection );
		if( PinDirection == PINDIR_OUTPUT )
		{
			pIPin1->EnumMediaTypes( &pEnumMT );
			hr = pEnumMT->Next( 1, &mt, 0 );
			pEnumMT.Release();
			if( mt->majortype ==  MEDIATYPE_Stream || mt->majortype ==  MEDIATYPE_Video )
				break;
		}
		pIPin1.Release();
	}
	pEnumPins.Release();
	pDownstream->EnumPins(&pEnumPins);
	while ( hr = pEnumPins->Next(1, &pIPin2, 0), hr == S_OK )
	{
		pIPin2->QueryDirection( &PinDirection );
		if( PinDirection == PINDIR_INPUT )
			break;
		pIPin2.Release();
	}
	pEnumPins.Release();
	hr = m_pGraph->ConnectDirect( pIPin1, pIPin2, NULL );
	if( FAILED(hr) )
		hr = m_pGraph->Connect( pIPin1, pIPin2 );
	pIPin1.Release();
	pIPin2.Release();
	return hr;
}

HRESULT CInternalGraph::InitFilters( BOOL bExistingFile )
{
	HRESULT hr = E_FAIL;

	// Create the filter graph manager and query for interfaces.
	if( !m_pGraph )
	{
		hr = ::CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IGraphBuilder, (void **)&m_pGraph );
		if ( FAILED(hr) )  
			return hr;
		m_pControl.Release();
		hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&m_pControl );
	}

	if( bExistingFile )
	{
		if( !m_pDump )
		{
			hr = CoCreateInstance( CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, 
				IID_IBaseFilter, (void **)&m_pDump );
			if( FAILED( hr ) )
			{
				DestroyGraph();
				return hr;
			}
		}
		m_pSourceIMC.Release();
		m_pSourceIMC = NULL;
		m_pSource.Release();
		if( !m_pSource )
		{
			hr = CoCreateInstance( CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER, 
									IID_IBaseFilter, (void **)&m_pSource );
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}

			CComPtr<IFileSourceFilter> pSourceFilter = NULL;
			m_pSource->QueryInterface( IID_IFileSourceFilter, (void**)&pSourceFilter );
			hr = pSourceFilter->Load( m_csFileName.AllocSysString(), NULL );
			pSourceFilter.Release();
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
		}
		if( !m_pDemuxer )
		{
			hr = CoCreateInstance( CLSID_AviSplitter, NULL, CLSCTX_INPROC_SERVER, 
				IID_IBaseFilter, (void **)&m_pDemuxer );
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
		}
		if( !m_pGrabber )
		{
			hr = CoCreateInstance( CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
				IID_IBaseFilter, (void**)&m_pGrabber);
			if( FAILED(hr) )
			{
				DestroyGraph();
				return hr;
			}
		}
	}
	else
	{
		if( !m_pSource )
		{
			hr = CoCreateInstance( CLSID_BMPPushSource, NULL, CLSCTX_INPROC_SERVER, 
									IID_IBaseFilter, (void **)&m_pSource );
			if( FAILED( hr ) )
			{
				DestroyGraph();
				return hr;
			}
			hr = m_pSource->QueryInterface( IID_IModuleConfig, (void**)&m_pSourceIMC );
		}
		if( !m_pMuxer )
		{
			hr = CoCreateInstance( CLSID_AviDest, NULL, CLSCTX_INPROC_SERVER, 
				IID_IBaseFilter, (void **)&m_pMuxer );
			if( FAILED( hr ) )
			{
				DestroyGraph();
				return hr;
			}
		}
		if( !m_pDump )
		{
			hr = CoCreateInstance( CLSID_FileWriter, NULL, CLSCTX_INPROC_SERVER, 
				IID_IBaseFilter, (void **)&m_pDump );
			if( FAILED( hr ) )
			{
				DestroyGraph();
				return hr;
			}
			CComPtr<IFileSinkFilter> pSink;
			hr = m_pDump->QueryInterface( IID_IFileSinkFilter, (void**)&pSink );
			hr = pSink->SetFileName( m_csFileName.AllocSysString(), NULL );
			pSink.Release();
			if( FAILED( hr ) )
			{
				DestroyGraph();
				return hr;
			}
		}
	}
	return hr;
}
HRESULT CInternalGraph::DestroyGraph()
{
	//Destroy Graph
	if( m_pGraph )
	{
		m_pControl->Stop();
		CComPtr<IEnumFilters>	pEnumFilters = NULL;
		HRESULT hr = m_pGraph->EnumFilters( &pEnumFilters );
		if ( SUCCEEDED(hr) )
		{
			CComPtr<IBaseFilter> pBaseFilter = NULL;
			while ( S_OK == pEnumFilters->Next( 1, &pBaseFilter, NULL ) )
			{
				FILTER_INFO fi;
				pBaseFilter->QueryFilterInfo(&fi);
				// Remove the filter.
				m_pGraph->RemoveFilter(pBaseFilter);
				// Reset the enumerator.
				pEnumFilters->Reset();
				pBaseFilter.Release();
			}
			pEnumFilters.Release();
		}
		if( m_pDump )
		{
			m_pDump.Release();
			m_pDump = NULL;
		}
		if( m_pMuxer )
		{
			m_pMuxer.Release();
			m_pMuxer = NULL;
		}
		if( m_pEncoder )
		{
			m_pEncoder.Release();
			m_pEncoder = NULL;
		}
		if( m_pGrabber )
		{
			m_pGrabber.Release();
			m_pGrabber = NULL;
		}
		if( m_pSourceIMC )
		{
			m_pSourceIMC.Release();
			m_pSourceIMC = NULL;
		}
		if( m_pSource )
		{
			m_pSource.Release();
			m_pSource = NULL;
		}
		if( m_pDemuxer )
		{
			m_pDemuxer.Release();
			m_pSource = NULL;
		}
		m_pControl.Release();
			m_pControl = NULL;
		m_pGraph.Release();
			m_pGraph = NULL;
	}
	return S_OK;
}

BSTR CInternalGraph::ChooseTheEncoder( CString& Preferred )
{
	HRESULT hr = E_FAIL;
	if( m_bOpened )
	{
		return m_bstName = L"";
	}
	if( !Preferred.IsEmpty() )
	{
		CCodecDlg* pCodecDlg = new CCodecDlg(/*pParent*/);
		//remove previously chosen encoder and use new one
		m_pEncoder.Release();
		pCodecDlg->m_csEncoderFriendlyName = Preferred;
		m_bstName = pCodecDlg->InitializeEncoder( &m_pEncoder, &hr );
		delete pCodecDlg;
		return m_bstName;
	}
	HINSTANCE hResourceHandle = AfxGetResourceHandle();
	AfxSetResourceHandle(m_pParentInst);
	CCodecDlg* pCodecDlg = new CCodecDlg(/*pParent*/);
	int result;
	result = (int)pCodecDlg->DoModal();
	if( result != IDOK )
	{
		//No encoder
		m_bstName = L"Raw RGB";
	}
	else
	{
		//remove previously chosen encoder and use new one
		m_pEncoder.Release();
		m_bstName = pCodecDlg->InitializeEncoder( &m_pEncoder, &hr );
		if( pCodecDlg->m_bPrefer )
		{
			Preferred.SetString( m_bstName );
			if( Preferred == _T("Raw RGB") )
				Preferred.SetString(L"(No Encoding)");
		}
	}
	delete pCodecDlg;
	AfxSetResourceHandle(hResourceHandle);
	return m_bstName;
}

HRESULT CInternalGraph::SetStreamProps( LONG lHeight, LONG lWidth, LONGLONG llFrameDuration )
{
	HRESULT hr = S_FALSE;
	if( m_bOpened || m_bExisting )
		return hr;
	if( !( m_pSource && m_pSourceIMC ) )
	{
		m_pSourceIMC.Release();
		m_pSource.Release();

		hr = CoCreateInstance( CLSID_BMPPushSource, NULL, CLSCTX_INPROC_SERVER, 
								IID_IBaseFilter, (void **)&m_pSource );
		if( FAILED( hr ) )
		{
			DestroyGraph();
			return hr;
		}
		m_pSourceIMC.Release();
		hr = m_pSource->QueryInterface( IID_IModuleConfig, (void**)&m_pSourceIMC );
	}
	StreamParameters AVIParams;
	AVIParams.lHeight = lHeight;
	AVIParams.lWidth = lWidth;
	AVIParams.rtFrameLenght = llFrameDuration;

	VARIANT var = {0};
	var.pbVal = (BYTE*)&(AVIParams);
	hr = m_pSourceIMC->SetValue( &SMMBPS_StrmProps, &var );
	
	return hr;
}
HRESULT CInternalGraph::WriteImageToAvi( HBITMAP hImage )
{
	if( m_bExisting )
	{
		return E_FAIL;
	}
	
	if( m_pSource && m_pSourceIMC )
	{	
		VARIANT var = {0};
		var.pvRecord = &hImage;
		return m_pSourceIMC->SetValue( &SMMBPS_InputBMP, &var );
	}
	else
	{
		return E_FAIL;
	}
}
HRESULT CInternalGraph::CloseStream( BOOL bTerminate )
{
	HRESULT hr;
	VARIANT var;
	HANDLE hBMP = INVALID_HANDLE_VALUE;
	var.pvRecord = &hBMP;
	if( m_pSourceIMC )
	{
		if( bTerminate )
			hr = m_pSourceIMC->SetValue( &SMMBPS_Terminate, &var );
		else
			hr = m_pSourceIMC->SetValue( &SMMBPS_InputBMP, &var );

		while( TRUE )
		{
			Sleep( 10 );
			hr = m_pSourceIMC->GetValue( &SMMBPS_IsQueue, &var );
			if( !var.boolVal )
				break;
		}
	}	
	if( !m_bExisting )
		if( m_pControl )
			hr = m_pControl->Stop();
	hr = DestroyGraph();

	m_bOpened = FALSE;
	m_bExisting = FALSE;
	m_csFileName.Empty();
	return hr;
}
HRESULT CInternalGraph::ReadProperties( StreamParameters *pProps )
{
	HRESULT hr;
	pProps->dwCompression = -1;
	pProps->lHeight = -1;
	pProps->llTotalFrames = 0;
	pProps->lWidth = -1;
	pProps->rtFrameLenght = -1;
	if( !m_bExisting )
	{
		if( m_pSourceIMC )
		{
			VARIANT val;
			val.pbVal = (BYTE*) pProps;
			m_pSourceIMC->GetValue( &SMMBPS_StrmProps, &val );
		}
		CheckPointer( m_pMuxer, E_POINTER );
		CComPtr<IPin> pPin = GetExactPin( &hr, m_pMuxer, FALSE, FALSE, TRUE);
		AM_MEDIA_TYPE mt;
		hr = pPin->ConnectionMediaType( &mt );
		pPin.Release();
		if( FAILED(hr) )
			return hr;
		pProps->dwCompression = 
			( (VIDEOINFOHEADER*)mt.pbFormat )->bmiHeader.biCompression;
	}
	else
	{
		CheckPointer( m_pDump, E_POINTER );
		CComPtr<IPin> pPin = GetExactPin( &hr, m_pDemuxer, FALSE, TRUE, TRUE );//GetActiveInputPin( m_pDump );
		AM_MEDIA_TYPE mt;
		hr = pPin->ConnectionMediaType( &mt );
		pPin.Release();
		if( FAILED(hr) )
			return hr;
		BITMAPINFOHEADER bmpHead = ( (VIDEOINFOHEADER*)mt.pbFormat )->bmiHeader;
		pProps->dwCompression = bmpHead.biCompression;
		pProps->lHeight = bmpHead.biHeight;
		pProps->lWidth = bmpHead.biWidth;
		pProps->rtFrameLenght = ((VIDEOINFOHEADER*)mt.pbFormat)->AvgTimePerFrame;

		CComPtr<IMediaSeeking> pMeidaSeeking = NULL;
		hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&pMeidaSeeking );
		if( FAILED(hr) )
			return hr;
		LONGLONG llDuration;
		hr = pMeidaSeeking->GetDuration( &llDuration );
		pMeidaSeeking.Release();
		if( FAILED(hr) )
			return hr;
		pProps->llTotalFrames = llDuration / pProps->rtFrameLenght;
	}
	return S_OK;
}

IPin* CInternalGraph::GetExactPin( HRESULT *hr, IBaseFilter *pOwnerFilter, BOOL IsAudioPin, BOOL IsOutputPin, BOOL IsConnected )
{
	IPin						*pPin = NULL;
	CComPtr<IPin>				pInterPin = NULL;
	CComPtr<IEnumPins>			pEnumPins = NULL;
	CComPtr<IEnumMediaTypes>	pEnumMediaTypes = NULL;
	PIN_DIRECTION				PinDirection = PINDIR_INPUT;
	AM_MEDIA_TYPE				*pMT;

	*hr = S_OK;
	pOwnerFilter->EnumPins( &pEnumPins );
	while( pEnumPins->Next( 1, &pPin, 0 ) == S_OK)
	{
		*hr = pPin->QueryDirection( &PinDirection );
		if( FAILED( *hr ) )
		{
			pEnumPins.Release();
			return NULL;
		}
		if( PinDirection == IsOutputPin )
		{
			if( (pPin->ConnectedTo( &pInterPin ) == VFW_E_NOT_CONNECTED) == (IsConnected == FALSE) )
			{
				if( IsOutputPin == FALSE )
				{
					pEnumMediaTypes.Release();
					pInterPin.Release();
					pEnumPins.Release();
					return  pPin;
				}
				pPin->EnumMediaTypes( &pEnumMediaTypes );
				pEnumMediaTypes->Next(1, &pMT, 0);
				if( (pMT->majortype == MEDIATYPE_Audio ) == (IsAudioPin == TRUE) )
				{
					pEnumMediaTypes.Release();
					pInterPin.Release();
					pEnumPins.Release();
					return  pPin;
				}else
					pEnumMediaTypes.Release();
			}
		}
		pInterPin.Release();
	}
	pEnumMediaTypes.Release();
	pInterPin.Release();
	pEnumPins.Release();
	return NULL;
}

BYTE* CInternalGraph::ReadImage( LONGLONG llFrame, LONG* plTotalBytes )
{
	if( !m_bExisting )
		return NULL;
	HRESULT hr;
	CComPtr<ISampleGrabber> pGrabberInterface = NULL;
	hr = m_pGrabber->QueryInterface(IID_ISampleGrabber, (void**)&pGrabberInterface);
	char *pBuffer = NULL;
	CComPtr<IMediaEvent>	pMediaEvent;
	CComPtr<IMediaSeeking>	pMediaSeeking;
	hr = m_pGraph->QueryInterface(IID_IMediaEvent, (void **)&pMediaEvent);
	hr = m_pGraph->QueryInterface(IID_IMediaSeeking, (void **)&pMediaSeeking);
	hr = pMediaSeeking->SetTimeFormat( &TIME_FORMAT_FRAME );
	hr = pMediaSeeking->SetPositions( &llFrame, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning );
	if( SUCCEEDED(hr) )
	{
		m_pControl->Pause();
		hr = pGrabberInterface->SetOneShot(TRUE);
		hr = pGrabberInterface->SetBufferSamples(TRUE);

		hr = m_pControl->Run(); 

		long evCode;
		pMediaEvent->WaitForCompletion(INFINITE, &evCode); 

		m_pControl->Stop();

		hr = pGrabberInterface->GetCurrentBuffer( (long*)plTotalBytes, NULL );

		pBuffer = new char[*plTotalBytes];
		hr = pGrabberInterface->GetCurrentBuffer((long*)plTotalBytes, (long*)pBuffer);
	}
	pMediaEvent.Release();
	pGrabberInterface.Release();
	
	pMediaSeeking->SetTimeFormat( &TIME_FORMAT_MEDIA_TIME );
	pMediaSeeking.Release();

	return (BYTE*)pBuffer;
}
void CInternalGraph::DeleteImageBuffer( char* pBuffer )
{
	delete[] pBuffer;
}
