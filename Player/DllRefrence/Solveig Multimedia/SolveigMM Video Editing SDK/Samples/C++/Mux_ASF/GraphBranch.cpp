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

#include "StdAfx.h"
#include "graphbranch.h"
#include "TestMuxerAppDlg.h"
#undef lstrlenW 
const  MediaFormat  g_pVF[] = 
{
	{ MEDIASUBTYPE_MPEG2_VIDEO, _T("MPEG-2 Video")},
	{ MEDIASUBTYPE_H264_ANNEXB,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_2,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_3,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_4,_T("H.264 Video")},
	{ MEDIASUBTYPE_MPEG4,_T("MPEG-4 Video")},
	{ MEDIASUBTYPE_dvsd,_T("DV Video")},
	{ MEDIASUBTYPE_DIVX,_T("DivX Video")},
	{ MEDIASUBTYPE_DIVX_2, _T("DivX Video")},
	{ MEDIASUBTYPE_DIVX_3,_T( "DivX Video")},
	{ MEDIASUBTYPE_XVID,_T("XVid Video")},
	{ MEDIASUBTYPE_RGB8,_T("RGB 8") }, 
	{ MEDIASUBTYPE_RGB555,_T("RGB 555") }, 
	{ MEDIASUBTYPE_RGB565,_T("RGB 565") }, 
	{ MEDIASUBTYPE_RGB24,_T("RGB 24") }, 
	{ MEDIASUBTYPE_RGB32,_T("RGB 32") },
	{ MEDIASUBTYPE_YUY2,_T("YUY2") },
	{ MEDIASUBTYPE_UYVY,_T("UYVY") },
	{ MEDIASUBTYPE_YUYV,_T("YUYV") },
	{ WMMEDIASUBTYPE_WMV1,_T("Windows Media Video") },
	{ WMMEDIASUBTYPE_WMV2,_T("Windows Media Video") },
	{ WMMEDIASUBTYPE_WMV3,_T("Windows Media Video") }

};

const	 MediaFormat		g_pAF[] =
{
	{ MEDIASUBTYPE_PCM,_T("PCM") },
	{ MEDIASUBTYPE_MPEG1Packet, _T("MPEG-1 Audio") },
	{ MEDIASUBTYPE_MPEG1Payload, _T("MPEG-1 Audio") },
	{ MEDIASUBTYPE_MPEG2_AUDIO , _T("MPEG-2 Audio") },
	{ MEDIASUBTYPE_DVD_LPCM_AUDIO,_T("DVD Audio")},
	{ MEDIASUBTYPE_DOLBY_AC3 ,_T("Dolby AC3 Audio")},
	{ MEDIASUBTYPE_AC3 ,_T("AC3 Audio")},
	{ MEDIASUBTYPE_AAC ,_T("AAC Audio")},
	{ MEDIASUBTYPE_MP3,_T("MP3 Audio (MPEG-1)")},
	{ MEDIASUBTYPE_VOXWARE_AUDIO,_T("Voxware Audio")},
	{ WMMEDIASUBTYPE_WMAudioV7,_T("Windows Media Audio")},
	{ WMMEDIASUBTYPE_WMAudioV8,_T("Windows Media Audio")},
	{ WMMEDIASUBTYPE_WMAudioV9,_T("Windows Media Audio")},
	{ WMMEDIASUBTYPE_WMSP1,_T("Windows Media Audio")}
};

CGraphBranch::CGraphBranch(HRESULT	*phr, CDirectShowGraph *pGraph, CSettings		*pSettings,
						   CDirectShowFilter	*pAsfMuxer, CDirectShowPin &DemuxPin) 
{
	if (!pAsfMuxer ||  !pGraph  ) {
		*phr = E_POINTER;
		return;
	}

	m_pSettings = NULL;

	m_pSettings = pSettings;
	m_pGraph = pGraph;
	m_DemuxPin = m_LastPin = DemuxPin;
	m_pAsfMuxer = pAsfMuxer;
}

CGraphBranch::~CGraphBranch(void)
{
	m_DemuxPin.Release();
	m_LastPin.Release();
	m_fltEncoder.Release();
}

HRESULT		CGraphBranch::GetType( LPTSTR szType )
{
	if (!szType) {
		return E_POINTER;
	}

	_tcscpy( szType, m_szBranchType );
	return S_OK;
}


HRESULT		CGraphBranch::GetSettings ( CSettings	**ppSettings )
{
	if (!m_pSettings) {
		return E_POINTER;
	}
	*ppSettings = m_pSettings;
	return S_OK;
}

HRESULT		CGraphBranch::SetSettings( CSettings	*pSettings )
{
	if (!pSettings) {
		return E_POINTER;
	}
	m_pSettings = pSettings;
	return S_OK;
}

HRESULT		CGraphBranch::Init ( void )
{
	HRESULT hr = S_OK;
	UINT n = 0;
	if ( !m_pGraph) {
		return E_POINTER;
	}

	if (m_pSettings)
	{
		if (!m_pSettings->IsEnabled())
			return	S_OK;

        if (m_pSettings->IsUncompressed() ||
			m_pSettings->IsTranscode() )
		{
			// 1) Render branch

			hr =  m_pGraph->Render( &m_LastPin );
			if (FAILED(hr)) {
				return hr;
			}

			// 2) Find Renderer filter
	

			PIN_INFO	pi;
			BOOL	bRenderer;
			BOOL	bConnected;
			CDirectShowFilter filter;
		
			for (;;)
			{
				CDirectShowPin	ConnectedPin;
				bConnected = false;
				hr = m_LastPin.GetConnected( ConnectedPin );
				if (FAILED(hr))
					return hr;

				ConnectedPin->QueryPinInfo( &pi );
				if (FAILED(hr))  {
					return hr;
				}

				filter = ( pi.pFilter );
				bRenderer = true;

				UINT	nPinCount = 0;
				filter.GetPinCount( &nPinCount );

				CDirectShowPin	pin;
				for (n = 0; n < nPinCount; n++)
				{
					hr = filter.GetPin(n, pin );
					if (SUCCEEDED(hr))
					{
						if (pin.IsConnected() && pin.IsOutput())
						{
							m_LastPin = pin;
							bRenderer = false;
							break;
						}
						pin.Release();
					}
				}

				pi.pFilter->Release();
				ConnectedPin.Release();

	
				if (bRenderer)
					break;

				filter.Release();
			}
			

			if (!bRenderer)
				return E_FAIL;

			// 3) Remove renderer filter

			hr = m_pGraph->RemoveFilter( &filter );
			if (FAILED(hr)) 
				return hr;
			filter.Release();

			// 4) TO DO : Add encoder
			if ( m_pSettings->IsTranscode()
				&& !m_pSettings->IsUncompressed())
			{
				if (m_pSettings->GetEncoderGUID() == GUID_NULL)
				{
					MessageBox(NULL, _T("Please specify encoder for transcoding"),
						_T("Select encoder"), MB_ICONERROR);
					return E_FAIL;
				}
				hr = AddEncoder( );
				if (FAILED(hr))
					return hr;

				// Connect last pin with encoder
				hr = m_pGraph->ConnectPinWithFilter( &m_LastPin, &m_fltEncoder );
				if (FAILED(hr))
					return hr;

				UINT	nCount = 0;

				// Make first output pin of encoder as last pin in branch
				hr = m_fltEncoder.GetPinCount( &nCount);
				if (FAILED(hr))
					return hr;

				BOOL	bFound = false;
				CDirectShowPin	pin;


				for (n = 0; n < nCount; n++)
				{
					hr = m_fltEncoder.GetPin( n, pin);
					if (FAILED(hr))
						return hr;

					if (pin.IsOutput()) {
						m_LastPin = pin;
						bFound = true;
						break;
					}
					pin.Release();
				}

				if (!bFound)
					return E_FAIL;
			}
		}
	}
	return hr;
}

HRESULT		CGraphBranch::SelectFormatByGUID( GUID guid )
{
	if (!m_pSettings) {
		return E_POINTER;
	}
	return S_OK;
}

HRESULT		CGraphBranch::Build ( void )
{
	HRESULT hr = S_OK;
	if ( !m_pGraph) {
		return E_POINTER;
	}

	if (m_pSettings)
	{
		if (m_pSettings->IsEnabled()) 
		{
			
			hr =  m_pGraph->Render( &m_LastPin );
			if (FAILED(hr)) {
				return hr;
			}
			// Fill format string
			CMediaType mt;
			m_pSettings->SetFormatString(_T(""));
			hr = m_LastPin.GetMediaType( mt );
			if (SUCCEEDED(hr)) {
				SelectFormatByGUID( *mt.Subtype() );
			}

		}
	}
	else 
	{
		hr =  m_pGraph->Render( &m_LastPin );
		if (FAILED(hr)) {
			return hr;
		}
	}
	return hr;
}

HRESULT		CGraphBranch::AddEncoder( void )
{
	if (!m_pGraph || !m_pSettings) {
		return E_POINTER;
	}
	return S_OK;
}

HRESULT		CGraphBranch::ConfigureASFWriter( void )
{
	return S_OK;
}

CVideoBranch::CVideoBranch( HRESULT	*phr, CDirectShowGraph *pGraph, CSettings	*pSettings,
						   CDirectShowFilter	*pAsfMuxer, CDirectShowPin &DemuxPin ) :
	CGraphBranch( phr, pGraph, pSettings,  pAsfMuxer, DemuxPin )
{
	_tcscpy(	m_szBranchType, _T("Video") );
}

CVideoBranch::~CVideoBranch( void )
{
}

HRESULT		CVideoBranch::Init ( void )
{
	HRESULT hr = CGraphBranch::Init();
	if(FAILED(hr)) {
		return hr;
	}
	return hr;
}

HRESULT		CVideoBranch::SelectFormatByGUID( GUID guid )
{
	HRESULT hr = S_OK;
	hr = CGraphBranch::SelectFormatByGUID( guid );
	if (FAILED(hr)) {
		return hr;
	}
	UINT n = 0;
	for (n = 0; n < sizeof ( g_pVF ) / sizeof(MediaFormat); n++)
	{
		if ( g_pVF[n].guid == guid) {
			m_pSettings->SetFormatString( g_pVF[n].szFormat );
			break;			
		}
	}
	return S_OK;
}

HRESULT		CVideoBranch::Build ( void )
{
	HRESULT hr = CGraphBranch::Build();
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

HRESULT		CVideoBranch::FOURCCStringToDWORD( LPCTSTR szFOURCC, DWORD *pdwFOURCC )
{
	HRESULT hr = S_OK;
	*pdwFOURCC = ( szFOURCC[3] << 24) | ( szFOURCC[2] << 16) |
		( szFOURCC[1] << 8) | szFOURCC[0] ;
	return hr;
}


HRESULT		CVideoBranch::AddEncoder( void )
{
	HRESULT hr = S_OK;
	hr = CGraphBranch::AddEncoder();
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter( m_pSettings->GetEncoderGUID(), L"Video encoder",
		m_fltEncoder);

	return hr;
}


HRESULT		CVideoBranch::ConfigureASFWriter( void )
{
	HRESULT hr = CGraphBranch::ConfigureASFWriter();
	if (FAILED(hr)) {
		return hr;
	}
	
	CComVariant val = (UINT)0;
	if ( m_pSettings )
	{
		val.ulVal |= SMM_ASFMuxFlags_InAVC;
		if ( TRUE == ((CVideoSettings *)m_pSettings)->GetTreatVideoAsH264() ) {
			hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_Flags, &val );
		}
		else{
			hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_ResetFlags, &val );
		}
		
		if( TRUE == ((CVideoSettings *)m_pSettings)->GetUseCustomFOURCC() )
		{
			DWORD dwFOURCC = 0;
			TCHAR szFOURCC[10];
			((CVideoSettings *)m_pSettings)->GetFOURCC( szFOURCC );
			FOURCCStringToDWORD( szFOURCC, &dwFOURCC );
			
			val = (UINT)dwFOURCC;
			hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_VideoFOURCC, &val );
		}
		else{
			val = (UINT)0; ; // do not  use custom fourcc
			hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_VideoFOURCC, &val );
		}
	}
	else
	{
		val = UINT(0);
		val.ulVal |= SMM_ASFMuxFlags_InAVC; 
		hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_ResetFlags, &val );

		val = (UINT)0; // do not  use custom fourcc
		hr = ((IModuleConfig*)*m_pGraph)->SetValue( &SMASFMux_VideoFOURCC, &val );

	}


	return hr;
}

BOOL		CVideoBranch::AllowCustomFOURCC( void )
{
	HRESULT hr = S_OK;
	CMediaType	mt;
	hr = m_LastPin.GetMediaType( mt );
	if (SUCCEEDED(hr)) 
	{
		if ((*mt.FormatType() == FORMAT_VideoInfo ) ||
			(*mt.FormatType() == FORMAT_VideoInfo2 )) {
				return true;
			}
	} 
	return false;
}

CAudioBranch::CAudioBranch( HRESULT	*phr,  CDirectShowGraph *pGraph, CSettings *pSettings,
						   CDirectShowFilter	*pAsfMuxer, CDirectShowPin &DemuxPin ):
	CGraphBranch( phr, pGraph, pSettings, pAsfMuxer, DemuxPin ) 
{
	_tcscpy(	m_szBranchType, _T("Audio") );
}

CAudioBranch::~CAudioBranch( void )
{
}

HRESULT		CAudioBranch::Init ( void )
{
	HRESULT hr = CGraphBranch::Init();
	if(FAILED(hr)) {
		return hr;
	}
	return hr;
}

HRESULT		CAudioBranch::SelectFormatByGUID( GUID guid )
{
	HRESULT hr = S_OK;
	hr = CGraphBranch::SelectFormatByGUID( guid );
	if (FAILED(hr)) {
		return hr;
	}
	
	UINT n = 0;
	for (n = 0; n < sizeof ( g_pAF ) / sizeof(MediaFormat); n++)
	{
		if ( g_pAF[n].guid == guid) {
			m_pSettings->SetFormatString( g_pAF[n].szFormat );
			break;			
		}
	}
	return S_OK;
}


HRESULT		CAudioBranch::Build ( void )
{
	HRESULT hr = CGraphBranch::Build();
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

HRESULT		CAudioBranch::AddEncoder( void )
{
	HRESULT hr = S_OK;
	hr = CGraphBranch::AddEncoder();
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter( m_pSettings->GetEncoderGUID(), L"Audio encoder",
		m_fltEncoder);

	return hr;
}

// Configure ASF Writer filter
HRESULT	CAudioBranch::ConfigureASFWriter( void )
{
	USES_CONVERSION;
	HRESULT hr = CGraphBranch::ConfigureASFWriter();
	if (FAILED(hr)) {
		return hr;
	}
	if( AfxGetMainWnd()->IsDlgButtonChecked(IDC_USE_LANG)/*AfxGetMainWnd()->GetDlgItem( IDC_USE_LANG )*/  != BST_CHECKED )
		return hr;
	CComPtr<IPin> pIPin = NULL;
	m_DemuxPin->ConnectedTo( &pIPin );
	if( !pIPin )
		return S_FALSE;
	CComPtr<IModuleConfig> pMC = NULL;
	hr = pIPin.QueryInterface( &pMC );

	VARIANT var;
	((CAudioSettings *)m_pSettings)->GetLanguage( &var.bstrVal );
	int num = 0;

	for( int i = 0; i < g_nLangCount; i++ )
	{
		if(0 == _tcscmp( OLE2T(var.bstrVal), wcsLangID[i][1] ) )
		{
			num = i;
			break;
		}
	}

	SysFreeString( var.bstrVal );
	var.bstrVal = SysAllocString( T2W(wcsLangID[num][0]) );
	hr = pMC->SetValue( &SMASFMux_Language, &var );
	pMC.Release();
	pIPin.Release();
	return hr;
}