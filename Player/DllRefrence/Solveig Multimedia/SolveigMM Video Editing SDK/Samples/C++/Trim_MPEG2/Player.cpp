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

#include "stdafx.h"

#include "Player.h"
#include "SimplePlayer.h"
#include <initguid.h>
#include <ISeekProps.h>
#include "SMM_SDKActionKeys.h"

//using namespace ElMuxer;
using namespace EMPEGMUX;
#define CExc CExMsg


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayer::~CPlayer()		
{	
	if( m_pIndex )
	{
		delete m_pIndex;
		m_pIndex = NULL;
	}
	if( m_pFilterDemuxer )
	{
		delete m_pFilterDemuxer;
		m_pFilterDemuxer = NULL;
	}
	if( m_pFilterDecoder )
	{
		delete m_pFilterDecoder;
		m_pFilterDecoder = NULL;
	}
}

void CPlayer::Reset()
{
	if(m_pIVideoWindow)
	{
		m_pIVideoWindow.Release();
		m_pIVideoWindow = NULL;
	}
	if( m_pFilterDecoder )
	{
		m_pFilterDecoder->Remove();
		delete m_pFilterDecoder;
		m_pFilterDecoder = NULL;
	}
	if( m_pFilterDemuxer )
	{
		//remove index from demuxer
		CComPtr<IIndexConfig> pIIndexConfig = NULL;
		m_hrError = m_pFilterDemuxer->QueryInterface( &pIIndexConfig );
		if( SUCCEEDED(m_hrError) )
			m_hrError = pIIndexConfig->UseIndex( NULL );
		pIIndexConfig.Release();

		//release index
		ReleaseIndex();

		m_pFilterDemuxer->Remove();
		delete m_pFilterDemuxer;
		m_pFilterDemuxer = NULL;
	}
	CGraphManager::Reset();
}

HRESULT CPlayer::SetPosition(REFERENCE_TIME rtPos, REFERENCE_TIME rtEndPos /* = 0 */)
{
	m_hrError = E_FAIL;

	if( IsInitialized( ) )
	{
		DWORD dwStopFlag = AM_SEEKING_AbsolutePositioning;
		if(!rtEndPos)
			dwStopFlag = AM_SEEKING_NoPositioning;

		m_hrError = m_pIMS->SetPositions(&rtPos, AM_SEEKING_AbsolutePositioning , &rtEndPos, dwStopFlag);

		if( SUCCEEDED(m_hrError) )
			m_rtFastPosition = rtPos;

		if( rtPos == 0 || rtPos == GetDuration() )
			Sleep(10);
	}

	return m_hrError;
}

HRESULT CPlayer::Run(BOOL bAsync /* = TRUE */)
{
	m_PlaybackMode = modeNormal;
	
	return CGraphManager::Run(bAsync);
}

HRESULT CPlayer::Pause(BOOL bAsync /* = TRUE */)
{
	m_PlaybackMode = modeNormal;
	
	return CGraphManager::Pause(bAsync);
}

HRESULT CPlayer::Stop(BOOL bAsync /* = TRUE */)
{
	m_PlaybackMode = modeNormal;
	
	return CGraphManager::Stop(bAsync);
}

HRESULT	 CPlayer::Step(long lFrames, BOOL bSec /* = FALSE */)
{
	if( m_pStateThread->CurrentGraphState() == graphStopped )
		Pause();

	REFERENCE_TIME rtPos = GetPosition();
	HRESULT hr = S_OK;
	
	if( !bSec )
	{
		
		hr = m_pIMS->SetTimeFormat(&TIME_FORMAT_FRAME);
		rtPos = GetPosition();
		rtPos += lFrames;
	}
	else
		rtPos += lFrames * ONE_SEC;
	
	hr = SetPosition( rtPos );
	m_pIMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);

	return hr;
}

HRESULT CPlayer::FastBackward(long lFrames /* = -1 */, BOOL bSec /* = FALSE */)
{
	HRESULT hr = Step(lFrames, bSec);
	
	m_rtFastPosition = GetPosition();
	m_PlaybackMode = modeFastBckwrd;

	if(!bSec)
		m_rtFastStep = lFrames * 333333;
	else
		m_rtFastStep = lFrames * ONE_SEC;

	return hr;
}

HRESULT CPlayer::FastForward(long lFrames /* = 1 */, BOOL bSec /* = FALSE */)
{
	HRESULT hr = Step(lFrames, bSec);

	m_rtFastPosition = GetPosition();
	m_PlaybackMode = modeFastFrwrd;
	
	if(!bSec)
		m_rtFastStep = lFrames * 333333;
	else
		m_rtFastStep = lFrames * ONE_SEC;
	
	return hr;
}

void CPlayer::SetInput(LPCTSTR tcsFileName)
{
	m_InputFile = tcsFileName;
}

HRESULT CPlayer::OnInitCompleted()
{
	if(FAILED(m_hrError = BuildGraph()))
		return m_hrError;

	CComPtr<IIndexConfig> pIIndexConfig = NULL;
	m_hrError = m_pFilterDemuxer->QueryInterface( &pIIndexConfig );
	if( FAILED(m_hrError) )
	{
		CExMsg err(_T("Querying IIndexConfig has been failed"), m_hrError );
		err.MsgBox();
	}
	else
	{
		ASSERT(m_pIndex);
		CComPtr< IMediaIndex > pIMediaIndex = NULL; 
		m_hrError = (*m_pIndex)->get_Index(0, &pIMediaIndex );

		if( FAILED(m_hrError) )
		{
			pIMediaIndex.Release();
			CExMsg err(_T("Querying IMediaIndex has been failed"), m_hrError);
			err.MsgBox();
		}
		else
			m_hrError = pIIndexConfig->UseIndex(pIMediaIndex);
		pIMediaIndex.Release();
	}
	RemoveNotConnectedFilters();
	return CGraphManager::OnInitCompleted();
}

HRESULT CPlayer::CreateFilters()
{
	m_hrError = S_OK;
	CComPtr<IClassFactory>	pClassFactory = NULL;
	CComPtr<IBaseFilter>	pBaseFilter = NULL;
	ProfileParser & parser = ProfileParser::Instance(Default_Codecs_Profile);
	GUID CodecGUID = parser.GetFilterCLSID( ProfileParser::Id_Demuxer, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	CDllWrapper AxDMXWrap( parser.GetFltrSlntPath( slntPath, CodecGUID ).AllocSysString(), &m_hrError );
	AxDMXWrap.GetClassFactory( CodecGUID, &pClassFactory );
	
	if( !pClassFactory )	//if no silent filter, try to search registered one
		m_hrError = ::CoCreateInstance( CodecGUID, NULL, CLSCTX_INPROC,
										IID_IBaseFilter, (void**)&pBaseFilter );
	else
	{
		m_hrError = pClassFactory->CreateInstance( NULL, IID_IBaseFilter, (void**)&pBaseFilter );	
		pClassFactory.Release();
	}
	if( FAILED(m_hrError) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 demuxer filter"), m_hrError);
		err.MsgBox();
		return m_hrError;
	}

	m_pFilterDemuxer = new CFilterWrapper( pBaseFilter );
	m_hrError = AddFilter( *m_pFilterDemuxer, _T("Elecard Demuxer") );
	pBaseFilter.Release();
	if( FAILED( m_hrError ) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 demuxer filter"), m_hrError);
		err.MsgBox();
	}

	CodecGUID = parser.GetFilterCLSID( ProfileParser::Id_Decoder, ProfileParser::prmVES, ProfileParser::vesMPEG2);
	CDllWrapper AxDECWrap( parser.GetFltrSlntPath( slntPath, CodecGUID ).AllocSysString(), &m_hrError );
	AxDECWrap.GetClassFactory( CodecGUID, &pClassFactory );

	if( !pClassFactory )		//if no silent filter, try to search registered one
		m_hrError = ::CoCreateInstance( CodecGUID, NULL, CLSCTX_INPROC,
										IID_IBaseFilter, (void**)&pBaseFilter );
	else
	{
		m_hrError = pClassFactory->CreateInstance( NULL, IID_IBaseFilter, (void**)&pBaseFilter );
		pClassFactory.Release();
	}
	if( FAILED( m_hrError ) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 decoder filter"), m_hrError);
		err.MsgBox();
	}

	m_pFilterDecoder = new CFilterWrapper( pBaseFilter );
	m_hrError = AddFilter( *m_pFilterDecoder, _T("Elecard Decoder") );
	pBaseFilter.Release();
	if( FAILED( m_hrError ) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 decoder filter"), m_hrError);
		err.MsgBox();
	}
	return m_hrError;
}

HRESULT CPlayer::BuildGraph()
{
	m_hrError = S_OK;

	if( m_InputFile.data() )
	{	
		//WCHAR wcsFName[MAX_PATH];

		CFilterWrapper src;
		HRESULT hr = AddFilterSource( CLSID_AsyncReader, _T("File Source (Async) Filter"), m_InputFile.data(), &src );
		if(FAILED(hr))
			return hr;

		hr = ConnectFiltersDirectly(src, *m_pFilterDemuxer );
		if(FAILED(hr))
			return hr;

		hr = ConnectFiltersDirectly(*m_pFilterDemuxer, *m_pFilterDecoder );
		if(FAILED(hr))
			return hr;

		CPinWrapper pin = m_pFilterDecoder->PinOut();
		hr = ((IGraphBuilder*) (*this))->Render(pin);
		if(FAILED(hr))
			return hr;

		CPinWrapper pin_a = m_pFilterDemuxer->PinOut(MEDIATYPE_Audio );
		if( pin_a )
			hr  = ((IGraphBuilder*) (*this))->Render(pin_a );

	} else
		m_hrError = E_FAIL;
	
	return m_hrError;
}

BOOL CPlayer::IsFullscreenMode()
{
	if(m_pIVideoWindow)
	{
		long res = OAFALSE;
		
		m_hrError = m_pIVideoWindow->get_FullScreenMode(&res);
		
		if (res == OATRUE)
			return TRUE;
	}
	
	return FALSE;
}

HRESULT CPlayer::SetFullscreenMode(BOOL bSet /* = TRUE */, OAHWND hWnd /* = 0 */)
{
	m_hrError = S_OK;

	if( !m_pIVideoWindow && bSet )
	{
		if(FAILED( m_hrError = QueryInterface(&m_pIVideoWindow) ))
			return m_hrError;
	}

	if( bSet )
	{
		m_hrError = m_pIVideoWindow->put_MessageDrain(  hWnd );
		ASSERT(SUCCEEDED(m_hrError));
	} 

	m_hrError = m_pIVideoWindow->put_FullScreenMode( bSet ? OATRUE : OAFALSE );

	if( !bSet && SUCCEEDED(m_hrError) )
	{
		if( m_pIVideoWindow )
			m_hrError = m_pIVideoWindow->put_MessageDrain( (OAHWND)NULL );		
		
		m_pIVideoWindow.Release();
		m_pIVideoWindow = NULL;		
	} 

	return m_hrError;
}

HRESULT CPlayer::OnEvent(long levCode, long lparam1 /* = MAXLONG */, long lparam2 /* = MAXLONG */)
{
	if(levCode == EC_IDLE) 
	{
		if(m_PlaybackMode != modeNormal)
		{ 
			// Jump
			REFERENCE_TIME rtDur = GetDuration();
			m_rtFastPosition += m_rtFastStep;
			
			if( m_rtFastPosition < 0 || m_rtFastPosition > rtDur )
			{
				if( m_rtFastPosition < 0 )		m_rtFastPosition = 0;
				if( m_rtFastPosition > rtDur )	m_rtFastPosition = rtDur;
				
				m_PlaybackMode = modeNormal;
				
				m_pStateThread->SetEvent(EC_COMPLETE, S_OK);
			} 
			
			m_pStateThread->WaitForOperationCompleted();
			
			m_hrError = m_pIMS->SetPositions(&m_rtFastPosition, AM_SEEKING_AbsolutePositioning , 
											 0, AM_SEEKING_NoPositioning);
			
			Sleep(1);
		}
	}

	return CGraphManager::OnEvent(levCode, lparam1, lparam2);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//----------------------- CTrimGrpah implementation  --------------------//
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

CTrimGrpah::CTrimGrpah ( CString slntPath ):
CPlayer(slntPath),
m_pConfigTrimmer(NULL),
m_pConfigMuxer(NULL),
m_pConfigDemuxer(NULL),
m_pConfigDmp(NULL),
m_rtListDuration(0),
m_bOutVES(false)
{
	m_pFilterMuxer = NULL;
}

CTrimGrpah::~CTrimGrpah ()
{
	if( m_pFilterMuxer )
	{
		m_pFilterMuxer->Remove();
		delete m_pFilterMuxer;
		m_pFilterMuxer = NULL;
	}
}

HRESULT	CTrimGrpah::CreateFilters()
{
	USES_CONVERSION;
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	HRESULT hr/* = CPlayer::CreateFilters()*/;

	VARIANT var = {0};

#ifdef COMPILE_VARIANT_ENGINE_USING

	CoInitialize(NULL);

	//
	// SolveigMM Video Editing Engine
	//
	hr = ::CoCreateInstance( CLSID_TrimmerObjControl, NULL, CLSCTX_INPROC,
							IID_ITrimmerObjControl, (void**)&m_pITrimmerObjControl );
	if ( hr != S_OK )
	{
		CExMsg err(_T("Error: \t SolveigMM Video Editing Engine creating has been failed"), hr);
		err.MsgBox();
		return hr;
	}

	//
	// Getting SolveigMM Video Editing Engine control interface - IModuleConfig
	//
	hr = m_pITrimmerObjControl->QueryInterface(IID_IModuleConfig, (void **)&m_pModuleCfgEditObj);
	if (hr != S_OK)
	{
		CExMsg err(_T("Error: \t Retrieving IModuleConfig has been failed"), hr);
		err.MsgBox();
		return hr; 
	}
	
	// setting callback interface
	if( m_pITrimmerCallBack )
	{
		var.pbVal = (BYTE*) m_pITrimmerCallBack.p;
		hr = m_pModuleCfgEditObj->SetValue( &SMAT_Callback, &var);
	}else
	{
		CExMsg err(_T("Error: \t Callback interface has not been set"), hr);
		err.MsgBox();
	}
	
	// other preparations
	CString silenPt = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	if ( 0 != silenPt.GetLength() )
	{
		var.bstrVal = silenPt.AllocSysString();
		hr = m_pModuleCfgEditObj->SetValue( &SMAT_SilentPath, &var );
		SysFreeString( var.bstrVal );
	}

	var.bstrVal  = SysAllocString(Default_Codecs_Profile);
	hr= m_pModuleCfgEditObj->SetValue( &SMAT_CodecsSet, &var );
	SysFreeString( var.bstrVal );

	{
		var.vt = VT_BSTR;
		var.bstrVal = CString(g_ActionKey_Trimm_MPEG1_MPEG2).AllocSysString();
		hr= m_pModuleCfgEditObj->SetValue( &SMAT_ActionKey, &var );
		SysFreeString( var.bstrVal );
	}
	return hr; 
#else

	CComPtr<IClassFactory>	pClassFactory = NULL;
	CComPtr<IBaseFilter>	pBaseFilter = NULL;
	//Demuxer Instance
	ProfileParser & parser = ProfileParser::Instance(Default_Codecs_Profile);
	CodecGUID = parser.GetFilterCLSID( ProfileParser::Id_Demuxer, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	CDllWrapper AxDMXWrap( parser.GetFltrSlntPath( slntPath, CodecGUID ).AllocSysString(), &m_hrError );
	AxDMXWrap.GetClassFactory( CodecGUID, &pClassFactory );

	if( !pClassFactory )	//if no silent filter, try to search registered one
		m_hrError = ::CoCreateInstance( CodecGUID, NULL, CLSCTX_INPROC,
										IID_IBaseFilter, (void**)&pBaseFilter );
	else
	{
		m_hrError = pClassFactory->CreateInstance( NULL, IID_IBaseFilter, (void**)&pBaseFilter );	
		pClassFactory.Release();
	}
	if( FAILED(m_hrError) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 demuxer filter"), m_hrError);
		err.MsgBox();
		return m_hrError;
	}

	m_pFilterDemuxer = new CFilterWrapper( pBaseFilter );
	m_hrError = AddFilter( *m_pFilterDemuxer, _T("Elecard Demuxer") );
	pBaseFilter.Release();
	if( FAILED( m_hrError ) )
	{
		CExMsg err(_T("Couldn't create Elecard MPEG2 demuxer filter"), m_hrError);
		err.MsgBox();
	}

	//File Source Instance
	hr = AddFilterSource( CLSID_AsyncReader, _T("File Source (Async) Filter"), m_InputFile.data(), &m_FilterSrc );
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Creating of MS Src filter has been failed"), hr);
		err.MsgBox();
		return hr;
	}

	if (!m_bOutVES)
	{
		//File Writer instance
		hr = AddFilterSink( CLSID_SMAVIWriter, _T("SolveigMM File Writer Filter"), m_OutputFN, &m_FilterDmp );
		if( FAILED( hr ) )
		{
			CExMsg err(_T("SolveigMM File Writer Filter"), hr);
			err.MsgBox();
			return hr;
		}
		//Muxer Instance
		CodecGUID = parser.GetFilterCLSID( ProfileParser::Id_Muxer, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
		
		CDllWrapper AxDMXWrap( parser.GetFltrSlntPath( slntPath, CodecGUID ).AllocSysString(), &m_hrError );
		AxDMXWrap.GetClassFactory( CodecGUID, &pClassFactory );
		if( !pClassFactory )
			m_hrError = ::CoCreateInstance( CodecGUID, NULL, CLSCTX_INPROC,
											IID_IBaseFilter, (void**)&pBaseFilter );

		else
		{
			m_hrError = pClassFactory->CreateInstance( NULL, IID_IBaseFilter, (void**)&pBaseFilter );
			pClassFactory.Release();
		}
		if( FAILED( m_hrError ) )
		{
			CExMsg err(_T("Creating of Elecard Multiplexer filter has been failed"), hr);
			err.MsgBox();
			return hr;
		}

		m_pFilterMuxer = new CFilterWrapper(pBaseFilter);
		hr = AddFilter( *m_pFilterMuxer, _T("Elecard Multiplexer") );
		pBaseFilter.Release();

		if( FAILED( hr ) )
		{
			CExMsg err(_T("Creating of Elecard Multiplexer filter has been failed"), hr);
			err.MsgBox();
			return hr;
		}
	}
	else
	{
		//File writer instance for audio
		hr = AddFilterSink( CLSID_SMAVIWriter, _T("SolveigMM File Writer Filter"), (m_OutputFN + "aud.mpa") ,&m_FilterDmpTestAud );
		if( FAILED( hr ) )
		{
			CExMsg err(_T("SolveigMM File Writer Filter"), hr);
			err.MsgBox();
			return hr;
		}
		//File writer instance for video
		hr = AddFilterSink(CLSID_SMAVIWriter, _T("SolveigMM File Writer Filter"), m_OutputFN ,&m_FilterDmpTestVid);
		if( FAILED( hr ) ){
			CExMsg err(_T("SolveigMM File Writer Filter"), hr);
			err.MsgBox();
			return hr;
		}
	}
	//Trimmer instance
	hr = AddFilter( CLSID_MP2_TRIM_FA, _T("Elecard-SolveigMM MPEG2 Trimmer FA"), &m_FilterTrimmer );
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Elecard-SolveigMM MPEG2 Trimmer FA filter has been failed"), hr);
		err.MsgBox();
		return hr;
	}
	CComPtr<IModuleConfig> pModuleConfig;
	m_FilterTrimmer->QueryInterface( IID_IModuleConfig, (void**)&pModuleConfig );
	
	var.vt = VT_BSTR;
	var.bstrVal = slntPath.AllocSysString();
	hr = pModuleConfig->SetValue( &SMAT_SilentPath ,&var );
	SysFreeString( var.bstrVal );

	var.vt = VT_BSTR;
	var.bstrVal =  SysAllocString(Default_Codecs_Profile);
	hr = pModuleConfig->SetValue( &SMAT_CodecsSet,&var );
	SysFreeString( var.bstrVal );
	var.bstrVal = NULL;
	ASSERT(m_pIndex);
	(*m_pIndex)->get_IndexFileName( &var.bstrVal );
	if (var.bstrVal)
	{
		hr = pModuleConfig->SetValue( &SMAT_MPEG2IndexFileName, &var );
		SysFreeString( var.bstrVal );
	}

	var.boolVal = TRUE;
	hr = pModuleConfig->SetValue( &SM2TFA_UseMPEG2Index, &var );
	hr = pModuleConfig->CommitChanges(NULL);
	pModuleConfig.Release();
	return hr;
#endif
}

HRESULT	CTrimGrpah::QueryInterfaces()
{
	HRESULT hr = CPlayer:: QueryInterfaces();
	if(FAILED(hr)){
		return hr;
	}
#ifdef COMPILE_VARIANT_ENGINE_USING
	return hr;
#endif

	
	if (!m_bOutVES)
	{
		ASSERT( m_pFilterMuxer );
		hr = m_pFilterMuxer->QueryInterface( &m_pConfigMuxer );
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Querying Multiplexer ModuleConfig interface has been failed"), hr);
			err.MsgBox();
			return hr;
		}
		hr = m_FilterDmp->QueryInterface( &m_pConfigDmp);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Querying Elecard Sinc filter  ModuleConfig interface has been failed"), hr);
			err.MsgBox();
			return hr;
		}
	}
	else
	{
		hr = m_FilterDmpTestVid->QueryInterface( &m_pConfigDmp);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Querying Elecard Sinc filter  ModuleConfig interface has been failed"), hr);
			err.MsgBox();
			return hr;
		}
	}

	hr = m_FilterTrimmer->QueryInterface( &m_pConfigTrimmer);
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Querying Trimmer ModuleConfig interface has been failed"), hr);
		err.MsgBox();
		return hr;
	}

	return hr;
}

HRESULT	CTrimGrpah::Run( BOOL bAsync )
{
	HRESULT hr = S_OK;

#ifdef COMPILE_VARIANT_ENGINE_USING
	hr = m_pITrimmerObjControl->Start();
	return hr;
#endif
	
	hr = CPlayer::Run(bAsync);
	return hr;
}

HRESULT	CTrimGrpah::StopManual ( void )
{
	HRESULT hr = S_OK;
#ifdef COMPILE_VARIANT_ENGINE_USING
	hr = m_pITrimmerObjControl->Stop();
	return hr;
#endif

	hr = CTrimGrpah::Stop();
	return hr;
}

HRESULT	CTrimGrpah::Stop ( BOOL bAsync  )
{
	HRESULT hr = S_OK;

	hr = CPlayer::Stop(bAsync);
	return hr;
}

HRESULT	CTrimGrpah::BuildGraph()
{
	HRESULT hr = S_OK;

#ifdef COMPILE_VARIANT_ENGINE_USING
	return hr;
#endif

	hr = ConnectFiltersDirectly( m_FilterSrc, *m_pFilterDemuxer );
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Connecting Src with Demuxer has been failed"), hr);
		err.MsgBox();
		return hr;
	}

	CPinWrapper pin = m_pFilterDemuxer->PinOut( MEDIATYPE_Video );
	if( pin == NULL )
	{
		CExMsg err(_T("Unable to find demuxer's video pin "), hr);
		err.MsgBox();
		return E_FAIL;
	}

	hr = ConnectOutPinWithFilter( pin, m_FilterTrimmer);
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Connecting Demuxer's video with trimmer has been failed"), hr);
		err.MsgBox();
		return hr;
	}
	pin.Release();

	if (!m_bOutVES)
	{
		pin = m_pFilterDemuxer->PinOut( MEDIATYPE_Audio );
		if( pin != NULL )
		{
			CComPtr<IModuleConfig> pIMConf = NULL;

			hr = m_FilterTrimmer->QueryInterface( &pIMConf);
			if( FAILED( hr ) )
			{
				CExMsg err(_T("Querying Trimmer ModuleConfig interface has been failed"), hr);
				err.MsgBox();
				return hr;
			}
			CComVariant var(1);
			hr = pIMConf->SetValue( &SM2TFA_AudioPinsNum, &var  );
			hr = pIMConf->CommitChanges(&var );

			pIMConf.Release();

			hr = ConnectOutPinWithFilter( pin, m_FilterTrimmer);
			if( FAILED( hr ) )
			{
				CExMsg err(_T("Connecting Demuxer's audio with trimmer has been failed"), hr);
				err.MsgBox();
				return hr;
			}
			
			pin.Release();

			pin = m_FilterTrimmer.PinOut( MEDIATYPE_Audio );
			hr	= ConnectOutPinWithFilter( pin, *m_pFilterMuxer);
			if( FAILED( hr ) )
			{
				CExMsg err(_T("Connecting audio Trimmer pin with Muxer has been failed"), hr);
				err.MsgBox();
				return hr;
			}
		}

		hr  = ConnectFiltersDirectly( m_FilterTrimmer, *m_pFilterMuxer);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Connecting Trimmer with Muxer has been failed"), hr);
			err.MsgBox();
			return hr;
		}
		
		hr = ConnectFiltersDirectly( *m_pFilterMuxer, m_FilterDmp);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Connecting Muxer with Dump has been failed"), hr);
			err.MsgBox();
			return hr;
		}
	}
	else
	{
		hr = ConnectFiltersDirectly( m_FilterTrimmer, m_FilterDmpTestVid);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Connecting Trimmer's Video with Dmp has been failed"), hr);
			err.MsgBox();
			return hr;
		}
		pin = m_FilterTrimmer.PinOut( MEDIATYPE_Audio );

		if( pin != NULL )
		{
			hr = ConnectOutPinWithFilter( pin, m_FilterDmpTestAud);
			if( FAILED( hr ) )
			{
				CExMsg err(_T("Connecting Trimmer's audio with Muxer has been failed"), hr);
				err.MsgBox();
				return hr;
			}
		}
	}
	return hr;
}

HRESULT	CTrimGrpah::OnInitCompleted()
{
	HRESULT hr = S_OK;

#ifndef COMPILE_VARIANT_ENGINE_USING
	hr = CPlayer::OnInitCompleted();
	if( FAILED(hr) )
		return hr;
#endif
		
	if( 0 == m_TrimParamsList.size() )
	{
		CExMsg err(_T("Trimmer params were not set "), hr);
		err.MsgBox();
		return E_FAIL;
	}

	CComVariant var;
	TrimInfoList info_list;
	
	info_list.nListSize = m_TrimParamsList.size();
	info_list.trim_list = new __TSTrimInfo[info_list.nListSize];
	
	TLITrimInfo	iter = m_TrimParamsList.begin();
	
	for( UINT n = 0; n < info_list.nListSize; n++ )
		info_list.trim_list[n] =(__TSTrimInfo)*iter++; 

    var.pbVal	= (BYTE*)&info_list;

#ifdef COMPILE_VARIANT_ENGINE_USING
	
	USES_CONVERSION;

	var.lVal = SMM_TrimmAccuracyType_Frame;
	hr = m_pModuleCfgEditObj->SetValue(&SMAT_TrimAccuracy, &var);

	var.vt = VT_BSTR;
	var.bstrVal = T2BSTR( m_InputFile.data() ); 
	hr  = m_pModuleCfgEditObj->SetValue( &SMAT_InputFile, &var );
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Setting In FN has been failed"), hr);
        err.MsgBox();
		//release allocated memory for trim_list
		if( info_list.trim_list )
		{
			delete [] info_list.trim_list;
			info_list.trim_list = NULL;
		}
		return hr;
	}

	var = m_OutputFN.AllocSysString();
	hr = m_pModuleCfgEditObj->SetValue( &SMAT_OutputFile , &var);
	SysFreeString( var.bstrVal );
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Setting Out FN has been failed"), hr);
		err.MsgBox();
		//release allocated memory for trim_list
		if( info_list.trim_list )
		{
			delete [] info_list.trim_list;
			info_list.trim_list = NULL;
		}
		return hr;
	}

	var.pbVal	= (BYTE*)&info_list;
	var.vt		=  VT_BYREF | VT_UI1;
	hr = m_pModuleCfgEditObj->SetValue( &SMAT_TrimList , &var);
	//release allocated memory for trim_list
	if( info_list.trim_list )
	{
		delete [] info_list.trim_list;
		info_list.trim_list = NULL;
	}
	if( FAILED( hr ) )
	{
		CExMsg err(_T("Setting fragment params has been failed"), hr);
		err.MsgBox();
		return hr;
	}

	// otherwise engine uses out type equal to input one

	if (m_bOutVES)
	{
		var = (long) SMM_File_Type_MPEG2_VES;
		hr = m_pModuleCfgEditObj->SetValue( &SMAT_OutputType , &var);
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Setting output file type as VES has been failed"), hr);
			err.MsgBox();
			return hr;
		}
		var = (long) 0;
		m_pModuleCfgEditObj->SetValue( &SMAT_AudioStreamNumber, &var );
		if( FAILED( hr ) )
		{
			CExMsg err(_T("Setting output file type as VES has been failed"), hr);
			err.MsgBox();
			return hr;
		}
	}

	BSTR bstrVal;
	hr = (*m_pIndex)->get_IndexFileName( &bstrVal );

	if( FAILED(hr) )
		MessageBox(NULL, _T("Unable to get Index file name"), _T("Error"), MB_OK | MB_ICONWARNING);
	else
	{
		var = bstrVal;
		hr = m_pModuleCfgEditObj->SetValue( &SMAT_MPEG2IndexFileName, &var);
	}


	hr	= m_pModuleCfgEditObj->CommitChanges(&var);
	if(FAILED(hr))
	{
		CString str	= var.bstrVal;
		CExMsg err( str , hr);
		err.MsgBox();
		return E_FAIL;
	}

	return hr;
#else

	ASSERT( m_pConfigTrimmer != NULL );
	
	hr	= m_pConfigTrimmer->SetValue( &SM2TFA_TrimList, &var );
	
	// we call this for trimmer asking at demuxer the duration, after it get an index
	hr	= m_pConfigTrimmer->GetValue( &SM2TFA_Duration, &var );


	hr	= m_pConfigTrimmer->CommitChanges(&var_err);
	if( info_list.trim_list )
		delete [] info_list.trim_list;

	if( FAILED(hr) )
	{
		CString str	= var_err.bstrVal;
		MessageBox( NULL,str,_T("Error"),MB_OK );
        CExMsg err( str , hr);
		err.MsgBox();
		SysFreeString( var_err.bstrVal );
		return E_FAIL;
	}

	if (!m_bOutVES)
	{
		CComPtr<IModuleConfig> pConf = NULL;
		hr = m_pFilterDemuxer->QueryInterface(&pConf);
		
		hr = pConf->GetValue(&EMPGDMX_STREAMTYPE, &var);

		switch( var.intVal )
		{
		case 1:
			var =  MPEG1_SYSTEM_STREAM;
			break;
		case 2:
			var =  PROGRAM_STREAM;
			break;
		case 3:
			var =  TRANSPORT_STREAM;
			break;
		default:
			var =  PROGRAM_STREAM;
			break;

		}
		
		ASSERT( m_pConfigMuxer != NULL );
		hr = m_pConfigMuxer->SetValue(&EMUX_OutputStreamType ,&var);
		hr = m_pConfigMuxer->CommitChanges(&var_err);
	}

	var.pbVal = NULL; 
	hr	= m_pConfigTrimmer->GetValue( &SM2TFA_TrimList, &var );
	
	info_list.nListSize = var.lVal;
	info_list.trim_list = new __TSTrimInfo[info_list.nListSize];
	
	var.pbVal = (BYTE*)&info_list;
	hr	= m_pConfigTrimmer->GetValue( &SM2TFA_TrimList, &var);

	m_rtListDuration = GetListDuration( info_list );
	
	if( info_list.trim_list )
		delete [] info_list.trim_list;
	
	CComPtr<IMediaFilter> pMediaFilter = NULL;
	((IGraphBuilder*)*this)->QueryInterface( IID_IMediaFilter, (void**)&pMediaFilter );
	pMediaFilter->SetSyncSource( NULL );
	pMediaFilter.Release();
	
	return hr;
#endif
}

HRESULT	CTrimGrpah::OnInitCompletedGOPAcc()
{
	CComVariant var;
	VARIANT var_err;

	__TSTrimInfo info_list = *m_TrimParamsList.begin();
	
	CFilterWrapper::CPinList pins;
	CComPtr<IMediaSeeking> pIMediaSeekingDmx = NULL;
	UINT nCount = m_pFilterDemuxer->PinsList(pins, IsOutAndConnected);
	HRESULT hr = pins[0]->QueryInterface( &pIMediaSeekingDmx );
	
	if(FAILED(hr))
	{
		CExMsg err( _T("Getting IMediaSeeking  failed") , hr);
		err.MsgBox();
		return hr;
	}
	LONGLONG lStart = info_list.llStartPos ;
	LONGLONG lStop	= info_list.llStopPos ;
	hr = pIMediaSeekingDmx->SetPositions(&lStart, AM_SEEKING_AbsolutePositioning, &lStop ,AM_SEEKING_AbsolutePositioning);
	if(FAILED(hr))
	{
		CExMsg err( _T("MediaSeek SetPos") , hr);
		err.MsgBox();
		return hr;
	}
	
	ASSERT( m_pConfigMuxer != NULL && m_bOutVES );
	
	if( m_pConfigMuxer )
	{
		var =  PROGRAM_STREAM;
		hr = m_pConfigMuxer->SetValue(&EMUX_OutputStreamType ,&var);
		hr = m_pConfigMuxer->CommitChanges(&var_err);
	}

	return hr;
}
void CTrimGrpah::ReleaseAllComponents()
{
	return CPlayer::ReleaseAllComponents();
}

void CTrimGrpah::Reset()
{

#define SELF_RELEASE(point){\
	if( point ) {\
	point.Release();\
	point = NULL;\
	}\
}
	if( m_pFilterMuxer )
	{
		m_pFilterMuxer->Remove();
		delete m_pFilterMuxer;
		m_pFilterMuxer = NULL;
	}
	m_FilterSrc.Remove();
	m_FilterDmp.Remove();
	m_FilterTrimmer.Remove();

	SELF_RELEASE( m_pConfigTrimmer );	
	SELF_RELEASE( m_pConfigMuxer);
	SELF_RELEASE( m_pConfigDemuxer);
	SELF_RELEASE( m_pConfigDmp);

	m_rtListDuration = 0;

#ifdef COMPILE_VARIANT_ENGINE_USING
	CPlayer::Reset();
	SELF_RELEASE(m_pITrimmerObjControl);
	SELF_RELEASE(m_pModuleCfgEditObj );
#endif

	CPlayer::Reset();
}

UINT CTrimGrpah::GetEditEngineProgress()
{
	UINT val = 0;
#ifdef COMPILE_VARIANT_ENGINE_USING
	CComVariant var = 0;
	HRESULT hr = m_pModuleCfgEditObj->GetValue( &SMAT_Progress, &var );
	val = var.lVal;
#endif
	return val;
}
REFERENCE_TIME CTrimGrpah::GetMuxerPosition()
{

	CComVariant val;
	HRESULT hr = S_OK;

	if (!m_bOutVES)
	{
		if( m_pConfigMuxer == NULL )
			return 0;
		hr = m_pConfigMuxer->GetValue( &EMUX_Mux_Time, &val );
	}
	else
	{
		hr = m_pConfigDmp->GetValue( &SMAW_CurrentSampleTime,&val );
	}
	return REFERENCE_TIME (val.llVal);
}

HRESULT	CTrimGrpah::OnEvent(long levCode, long lparam1, long lparam2 )
{
	HRESULT hr = CPlayer::OnEvent( levCode, lparam1 , lparam2 );

	if(	levCode == EC_STOP)
	{

	}
	return hr;
}
