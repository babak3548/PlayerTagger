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
#include ".\directshowgraph.h"


int GetFilenameByCLSID(REFCLSID clsid, TCHAR *szFile)
{
	HRESULT hr = S_OK;
	LPOLESTR strCLSID;
	int rc = 0;

	// Convert binary CLSID to a readable version
	hr = StringFromCLSID(clsid, &strCLSID);
	if(SUCCEEDED(hr))
	{
		TCHAR szKey[512];
		CString strQuery(strCLSID);

		// Create key name for reading filename from registry
		wsprintf(szKey, _T("Software\\Classes\\CLSID\\%s\\InprocServer32\0"),
			(LPCTSTR) strQuery);

		// Free memory associated with strCLSID (allocated in StringFromCLSID)
		CoTaskMemFree(strCLSID);

		HKEY hkeyFilter=0;
		DWORD dwSize=MAX_PATH;
		BYTE szFilename[MAX_PATH];

		// Open the CLSID key that contains information about the filter
		rc = RegOpenKey(HKEY_LOCAL_MACHINE, szKey, &hkeyFilter);
		if (rc == ERROR_SUCCESS)
		{
			rc = RegQueryValueEx(hkeyFilter, NULL,  // Read (Default) value
				NULL, NULL, szFilename, &dwSize);

			if (rc == ERROR_SUCCESS)
				wsprintf(szFile, _T("%s\0"), szFilename);

			RegCloseKey(hkeyFilter);
		}
	}
	else
		return -1;

	return rc;
}

bool CheckVersion(REFCLSID clsid, DWORD _ver1, DWORD _ver2, DWORD _ver3, DWORD _ver4, CString szMsg)
{
	TCHAR szFilterDir[MAX_PATH];
	CString sVersion;
	DWORD ver1 			= 0;
	DWORD ver2 			= 0;
	DWORD ver3 			= 0;
	DWORD ver4 			= 0;
	VS_FIXEDFILEINFO *pVS = NULL;

	int nRez = GetFilenameByCLSID(clsid, szFilterDir);
	if(nRez != -1)
	{		
		HINSTANCE hInst = LoadLibrary(szFilterDir);

		if(hInst != NULL)
		{
			TCHAR buf[]={_T("#1")};	// Only one VERSION_INFO present
			HRSRC hr = FindResource(hInst, buf, RT_VERSION); 
			if(hr)
			{		
				HGLOBAL hg = LoadResource(hInst, hr);
				if(hg)
				{
					BYTE *pByte = (BYTE*)LockResource (hg);
					if(pByte)
					{
						pVS = (VS_FIXEDFILEINFO*)(pByte+40);
						if(pVS)
						{
							ver1 = HIWORD (pVS->dwFileVersionMS);
							ver2 = LOWORD (pVS->dwFileVersionMS);
							ver3 = HIWORD (pVS->dwFileVersionLS);
							ver4 = LOWORD (pVS->dwFileVersionLS);
						}
					}
				}
			}
			FreeLibrary(hInst);
		}
	}

	if (pVS == NULL)
		return false;

	if (ver1 < _ver1){
		return false;
	}
	if (ver1 > _ver1)
		return true;

	if (ver2 < _ver2){
		return false;
	}
	if (ver2 > _ver2)
		return true;

	if (ver3 < _ver3){
		return false;
	}
	if (ver3 > _ver3)
		return true;

	if (ver4 < _ver4){
		return false;
	}

	return true;

}

LPTSTR GetTCHAR(LPCWSTR pIn, LPTSTR pOut)
{
#if  defined(_UNICODE) || defined(UNICODE)
	wcscpy((LPWSTR)pOut, pIn);
#else
	int result = ::WideCharToMultiByte(CP_ACP, 0, pIn, -1,
		pOut, (LONG)wcslen(pIn) + 1, NULL, NULL);
	if(result > 0)
		pOut[result - 1] = 0;
#endif
	return	pOut;
}

LPWSTR GetWCHAR(LPCTSTR pIn, LPWSTR pOut)
{
#if  defined(_UNICODE) || defined(UNICODE)
	wcscpy(pOut, (LPCWSTR)pIn);
#else
	int result = ::MultiByteToWideChar(CP_ACP, 0, pIn, -1,
		pOut, (LONG)strlen(pIn) + 1);
	if(result > 0)
		pOut[result - 1] = 0;
#endif
	return	pOut;
}



CDirectShowGraph::CDirectShowGraph(void):
	m_pGC( NULL ),
	m_dwROT( 0 ),
	m_mmTimer( 0 ),
	m_bIndexASF( true ),
	m_bWriteLog( false ),
	m_bNewFile( false ),
	m_llDuration( 0 )
{
	ZeroMemory( m_szSource, MAX_PATH );
	ZeroMemory( m_szDest, MAX_PATH );
	// Reset branches 
	m_nBranchesCount = m_nVideoBranchesCount = m_nAudioBranchesCount = 0;

	UINT n = 0 ;
	for ( n = 0; n < MAX_GRAPH_BRANCHES; n++ ) m_Branches[n] = NULL;
	for ( n = 0; n < MAX_VIDEO_STREAMS; n++) m_pVS[ n ] = NULL;
	for ( n = 0; n < MAX_AUDIO_STREAMS; n++) m_pAS[ n ] = NULL;
}

CDirectShowGraph::~CDirectShowGraph(void)
{
}


HRESULT	CDirectShowGraph::Init ( CString szSource, CString szDest , IGraphCallback	*pCallback )
{
	HRESULT hr = S_OK;

	if (lstrcmp( (LPTSTR)m_szSource, szSource )) 
		m_bNewFile = true;

	lstrcpy( (LPTSTR)m_szSource, szSource);
	lstrcpy( (LPTSTR)m_szDest, szDest);
	
	if (!pCallback) {
		return E_POINTER;
	}

	m_pGC = pCallback;

	return   Rebuild( );
}


HRESULT		CDirectShowGraph::Rebuild( void )
{
	HRESULT hr = S_OK;
	
	Reset();

	hr = CoCreateInstance( CLSID_FilterGraph );
	if (FAILED(hr)) {
		return hr;
	}

	// Create graph branches
	hr = CreateBranches( );
	if (FAILED(hr)) {
		return hr;
	}

	hr = QueryInterfaces( );
	if (FAILED(hr)) {
		return hr;
	}

	AddToROT();

	
	// Determine stream duration
	DetermineStreamDuration( );

	// Notity owner that graph is built
	if (m_pGC) {
		m_pGC->OnGraphBuilt();
	}

	return hr;
}

HRESULT	CDirectShowGraph::AddToROT( void )
{
	IRunningObjectTable* pROT = NULL;
	if(FAILED(GetRunningObjectTable(0, &pROT)))
		return E_FAIL;

	WCHAR wsz[256], wsz1[24];
	wcscpy(wsz, L"FilterGraph ");
	wcscat(wsz, _itow((int)(DWORD_PTR)this, wsz1, 16));
	wcscat(wsz, L" pid ");
	wcscat(wsz, _itow(GetCurrentProcessId(), wsz1, 16));

	IMoniker* pMoniker = NULL;
	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
	if(SUCCEEDED(hr)) 	
	{
		hr = pROT->Register(0, p, pMoniker, &m_dwROT);
		pMoniker->Release();
	}
	pROT->Release();
	return S_OK;
}

HRESULT	CDirectShowGraph::RemoveFromROT( void )
{
	IRunningObjectTable* pROT = NULL;
	if(m_dwROT && SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
	{
		pROT->Revoke(m_dwROT);
		m_dwROT = 0;
		pROT->Release();
	}
	return S_OK;
}



HRESULT		CDirectShowGraph::AddFilter( CLSID clsFlt,  LPWSTR wszFilterName, CDirectShowFilter &filter )
{
	HRESULT hr = S_OK;
	CDirectShowFilter flt(clsFlt, &hr);
	if (FAILED(hr)) {
		return hr;
	}

	filter = flt;

	return  p->AddFilter( filter, wszFilterName );
}

HRESULT		CDirectShowGraph::AddFilter( CDirectShowFilter	 *pFilter )
{
	HRESULT hr = S_OK;
	if (!p) {
		return E_POINTER;
	}
	FILTER_INFO	fi;
	hr = (*pFilter)->QueryFilterInfo( &fi );
	if (SUCCEEDED(hr)) 
	{
		
		hr = p->AddFilter( *pFilter, fi.achName );
        
		if (fi.pGraph)
			fi.pGraph->Release();

		return hr;
	}

	return E_FAIL;

}

HRESULT		CDirectShowGraph::AddSinkFilter( CLSID clsFlt, LPWSTR wszFilterName, CDirectShowFilter &filter, LPTSTR	tszFile)
{
	HRESULT hr = AddFilter( clsFlt, wszFilterName, filter);
	if (FAILED(hr)) {
		return hr;
	}
	CComPtr<IFileSinkFilter>pSink;
	hr = filter.QueryInterface( &pSink );
	if (SUCCEEDED(hr))
	{
		WCHAR	wszFile[ MAX_PATH ];
		GetWCHAR( tszFile, (LPWSTR)wszFile );
		hr = pSink->SetFileName( wszFile, NULL );
	}
	return hr;
}


HRESULT		CDirectShowGraph::RemoveFilter( CDirectShowFilter *pFilter )
{
	HRESULT hr = S_OK;
	if (!p) {
		return E_POINTER;
	}

	hr = DisconnectFilter ( pFilter );
	if (FAILED(hr)) {
		return hr;
	}

	return  p->RemoveFilter( *pFilter );
}

HRESULT		CDirectShowGraph::Render( CDirectShowPin *pPin )
{
	if (!p) {
		return E_POINTER;
	}
	return p->Render( *pPin );
}


HRESULT		CDirectShowGraph::ConnectPinWithFilter( CDirectShowPin *pPin, CDirectShowFilter *pFilter, BOOL bInt )
{
	HRESULT hr = S_OK;
	if (!pPin || !pFilter ) {
		return E_POINTER;
	}

	UINT nPinCount = 0,  n = 0;
	hr = pFilter->GetPinCount( &nPinCount );
	if (FAILED(hr)) 
		return hr;

	CDirectShowPin	pin;
	for (n = 0; n < nPinCount; n++)
	{

		hr = pFilter->GetPin(n, pin );
		if (SUCCEEDED(hr)) 
		{
			if (pin.IsInput()) {
		
				if ( bInt )
					hr = p->Connect( *pPin, pin );
				else
					hr = p->ConnectDirect( *pPin, pin, NULL );

			}
			pin.Release();

			if (SUCCEEDED(hr)) {
				break;
			}
		}
	}
	return hr;
}

HRESULT		CDirectShowGraph::ConnectFilters( CDirectShowFilter *pUp, CDirectShowFilter *pDown, BOOL bInt )
{
	HRESULT hr = S_OK;
	if (!pUp || !pDown) {
		return E_POINTER;
	}

	UINT nPinCount = 0,  n = 0;
	hr = pUp->GetPinCount( &nPinCount );
	if (FAILED(hr)) 
		return hr;

	CDirectShowPin	pin;
	for (n = 0; n < nPinCount; n++)
	{

		hr = pUp->GetPin(n, pin );
		if (SUCCEEDED(hr)) 
		{
			if (pin.IsOutput()) {
				hr = ConnectPinWithFilter( &pin, pDown, bInt );
			}
			
			pin.Release();

			if (FAILED(hr)) {
				return hr;
			
			}
		}	
	}
	return hr;
}

HRESULT		CDirectShowGraph::DisconnectFilter( CDirectShowFilter *filter )
{
	HRESULT hr = S_OK, hrAll = S_OK;
	if (!filter || !p) {
		return E_POINTER;
	}
// Disconnect all pins of filter
	UINT n = 0, count = 0;
	BOOL bNoneConnected = false;

	for (;;)
	{
		count = 0;
		bNoneConnected = true;
		hr = filter->GetPinCount( &count );
		if (FAILED(hr)) {

			hr = S_FALSE;
			break;
		}

		CDirectShowPin pin, connected;

		for (n = 0; n < count; n++)
		{
            hr = filter->GetPin(n, pin );
			if (SUCCEEDED(hr))
			{
				if ( pin.IsConnected() ) {

					bNoneConnected = false;


					hr = pin.GetConnected( connected );	
					if (SUCCEEDED(hr)) 
					{

						hr = DisconnectPin( &connected );
						connected.Release();
						if (FAILED(hr)) {
							return hr;
						}
					}

					hr = DisconnectPin ( &pin );
					pin.Release();
					if (FAILED(hr)) {
						return hr;
					}
				}
			}
		}
		if (bNoneConnected) return S_OK;
	}

	return hr;
}
HRESULT		CDirectShowGraph::DisconnectPin( CDirectShowPin		*pin )
{
	HRESULT hr = S_OK;
	if (!pin || !p) {
		return E_POINTER;
	}

	return p->Disconnect( *pin );
}

HRESULT		CDirectShowGraph::CreateBranches( void )
{
	HRESULT hr = S_OK;

	// At first, add ASF Muxer filter

	hr = AddSinkFilter(CLSID_SMASFMuxFilter, L"SolveigMM ASF Muxer Filter", m_fltAsfMuxer, (LPTSTR)m_szDest );
	if (FAILED(hr)) {
		MessageBox(NULL, _T("Creating SolveigMM ASF Muxer has been failed"), _T("DirectShow filter adding error"), MB_ICONERROR);
		return hr;
	}
	
	if( m_pMuxConfig ){
		m_pMuxConfig.Release();
		m_pMuxConfig = NULL;
	}

	hr = m_fltAsfMuxer.QueryInterface( &m_pMuxConfig );
	if (FAILED(hr)) {
		::MessageBox(NULL, _T("Can't get IModuleConfig at SolveigMM ASF Muxer"), _T("SolveigMM ASF Muxer Sample App"), MB_OK);
		return hr;
	}
	
	bool b = CheckVersion(CLSID_SMASFMuxFilter, 1, 0, 11, 12, _T("0"));
	if( false == b ){
		MessageBox(NULL, _T("SolveigMM ASF Muxer Filter ver 1.0.11.12 or above is required"), _T("Error"), MB_ICONERROR);
		return E_FAIL;
	}


	// Then, render source file 

	WCHAR	wszSourceFile[ MAX_PATH ];
	GetWCHAR ( (LPTSTR)m_szSource, (LPWSTR)wszSourceFile );
	hr = p->RenderFile( (LPWSTR)wszSourceFile, NULL );
	if (FAILED(hr)) {
		return hr;
	}
	


	// Try to insert DV Splitter filter and connect it with ASF Writer filter
	// In order to support DV streams
	{
		// Save filter to which ASF Muxer is connected upstream
		CDirectShowFilter upstream;

		
		hr = m_fltAsfMuxer.GetConnectedUpstream( upstream );
		if (FAILED(hr)) {
			return hr;
		}


		hr = RemoveFilter( &m_fltAsfMuxer );
		if (FAILED(hr)) {
			return hr;
		}

		hr	=	AddFilter(CLSID_DVSplitter, L"DV Splitter", m_fltDVSplitter);
		if (FAILED(hr)) {
			return hr;
		}

		// Add ASF writer to graph again
		hr = AddFilter( &m_fltAsfMuxer );
		if (FAILED(hr)) {
			return hr;
		}


		hr = ConnectFilters( &upstream,  &m_fltDVSplitter );
		if (SUCCEEDED(hr)) {
			hr = ConnectFilters( &m_fltDVSplitter, &m_fltAsfMuxer );
		}

		if (FAILED(hr)) {
	
			RemoveFilter( &m_fltDVSplitter);

			hr = ConnectFilters( &upstream, &m_fltAsfMuxer );
			if (FAILED(hr)) {
				upstream.Release();
				return hr;
			}
		}


		upstream.Release();

	}

	//
	// Now file is rendered to ASF Muxer filter
	// Find demuxer pins, determine branchs type ( Video and Audio )
	// And create them
	//

	UINT	n,m = 0;

	hr = m_fltAsfMuxer.GetPinCount( &m );
	if (FAILED(hr)) {
		return hr;
	}

	// Reset branches 
	m_nBranchesCount = 0;
	m_nVideoBranchesCount = 0;
	m_nAudioBranchesCount = 0;

	for ( n = 0; n < MAX_GRAPH_BRANCHES; n++ ) m_Branches[n] = NULL;

	CDirectShowPin	Pin;
	for (n = 0; n < m; n++)
	{
		hr = m_fltAsfMuxer.GetPin( n, Pin );
		if (FAILED(hr)) {
			return hr;
		}

		// Check that pin is connected
		if ( Pin.IsConnected() )
		{
			CDirectShowPin	ConnectedPin;
			hr = Pin.GetConnected( ConnectedPin );
			if (SUCCEEDED(hr)) 
			{
				CMediaType	MediaType;
				hr = Pin.GetMediaType(	MediaType );
				if (FAILED(hr)) {
					return hr;
				}

				if ( *MediaType.Type() == MEDIATYPE_Video ||
					*MediaType.Type() == MEDIATYPE_Interleaved) 
				{
					m_Branches[ m_nBranchesCount ] = new CVideoBranch( &hr, this, m_pVS[ m_nVideoBranchesCount ], 
						&m_fltAsfMuxer, ConnectedPin );
					if (FAILED(hr)) {
						return hr;
					}
					m_nBranchesCount ++;
					m_nVideoBranchesCount++;
				} 
				else if ( *MediaType.Type() == MEDIATYPE_Audio )
				{
					m_Branches[ m_nBranchesCount ] = new CAudioBranch( &hr, this,m_pAS[ m_nAudioBranchesCount ],
						&m_fltAsfMuxer, ConnectedPin );
					if (FAILED(hr)) {
						return hr;
					}
					m_nBranchesCount ++;
					m_nAudioBranchesCount++;
				}
			}
			ConnectedPin.Release();
		}

		Pin.Release();
	}

	// Remove ASF writer from graph

	hr = RemoveFilter( &m_fltAsfMuxer );
	if (FAILED(hr)) {
		return hr;
	}

	// Init branches
	for ( n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n])
		{
			hr = m_Branches[n]->Init();
			if (FAILED(hr)) {
				return hr;
			}
		}
	}

	
	// Add ASF writer to graph again
	hr = AddFilter( &m_fltAsfMuxer );
	if (FAILED(hr)) {
		return hr;
	}

	if (m_pGC && m_bNewFile)  
	{
		// Notify ownwer that source file is changed
		m_pGC->OnNewFile();

		// Set received settings to branches
		UINT nv = 0, na = 0;
		for ( n = 0; n < m_nBranchesCount; n++)
		{
			if (m_Branches[n])
			{
				TCHAR	szType [ MAX_PATH ];
				m_Branches[n]->GetType( szType );
				if (!_tcscmp ( szType, _T("Video")))
				{
					m_Branches[n]->SetSettings( m_pVS[nv++] );
				}
				else if (!_tcscmp(szType, _T("Audio")))
				{
					m_Branches[n]->SetSettings( m_pAS[na++] );
				}
			}
		}

		m_bNewFile = false;
	}

	// Build branches
	for ( n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n])
		{
			hr = m_Branches[n]->Build();
			if (FAILED(hr)) {
				return hr;
			}
		}
	}
	// Configure ASF Writer
	hr = ConfigureASFWriter ( );
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

void	CDirectShowGraph::DestroyBranches( void )
{
	UINT	n = 0;
	for (n = 0; n < MAX_GRAPH_BRANCHES; n++ )
	{
		if (m_Branches[n]) {
			delete m_Branches[n];
			m_Branches[n] = NULL;
		}
	}
}


HRESULT		CDirectShowGraph::QueryInterfaces( void )
{
	HRESULT hr = S_OK;
	hr = QueryInterface( &m_pMC );
	if (FAILED(hr))
		return hr;

	hr = QueryInterface( &m_pMF );
	if (FAILED(hr))
		return hr;

	hr = QueryInterface( &m_pMS);
	if (FAILED(hr))
		return hr;

	hr = QueryInterface( &m_pMEx);
	if (FAILED(hr))
		return hr;


	return hr;
}


void		CDirectShowGraph::Reset( void )
{
	DestroyBranches();
	RemoveFromROT();
	
	m_pMC.Release();
	m_pMF.Release();
	m_pMS.Release();
	m_pMEx.Release();
	m_pMuxConfig.Release();
	m_fltAsfMuxer.Release();
	m_fltDVSplitter.Release();

	Release();
}

HRESULT		CDirectShowGraph::GetVideoCount ( UINT	*pCount )
{
	HRESULT hr = S_OK;
	(*pCount) = 0;
	for (UINT n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n]) 
		{
			TCHAR	szType[ 20 ];
			m_Branches[n]->GetType( szType );
			if (!_tcscmp(szType, _T("Video"))) (*pCount)++;
		}
	}
	return hr;
}
	

HRESULT		CDirectShowGraph::GetAudioCount ( UINT	*pCount )
{
	HRESULT hr = S_OK;
	(*pCount) = 0;
	for (UINT n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n]) 
		{
			TCHAR	szType[ 20 ];
			m_Branches[n]->GetType( szType );
			if (!_tcscmp(szType, _T("Audio"))) (*pCount)++;
		}
	}
	return hr;
}


HRESULT		CDirectShowGraph::ApplyVideoSettings( UINT nNum, CVideoSettings	*pVS)
{
	m_pVS[ nNum ] = pVS;
	return S_OK;
}

HRESULT		CDirectShowGraph::ApplyAudioSettings( UINT nNum, CAudioSettings	*pAS)
{
	m_pAS[ nNum ] = pAS;
	return S_OK;
}


void		CDirectShowGraph::DetermineStreamDuration( void )
{

	m_llDuration = 0;
	
	// Create an instance of Media Detector object
	CComPtr<IMediaDet>pMediaDet;
	HRESULT hr = pMediaDet.CoCreateInstance( CLSID_MediaDet );
	if (SUCCEEDED(hr)) {
		
		WCHAR	wszSource[ MAX_PATH ];
		GetWCHAR( (LPTSTR)m_szSource, wszSource );
		hr = pMediaDet->put_Filename( wszSource );
		if (SUCCEEDED(hr))
		{
			hr = pMediaDet->put_CurrentStream( 0 );
			if (SUCCEEDED(hr))
			{
				double dStreamLength = 0;
				hr = pMediaDet->get_StreamLength( &dStreamLength );
				if (SUCCEEDED(hr)) 
				{
					m_llDuration = REFERENCE_TIME( dStreamLength * 10000000 );
				}
			}
		}
		pMediaDet.Release();
	}

}

HRESULT	CDirectShowGraph::Start ( void )
{
	HRESULT hr = S_OK;
	if (!m_pMC) {
		return E_POINTER;
	}

	
	// Reset reference clock
	hr = m_pMF->SetSyncSource( NULL );
	if (FAILED(hr)) 
		return hr;

	m_mmTimer = timeSetEvent(100, 100, CDirectShowGraph::TimeCallback, 
		(DWORD_PTR)this, TIME_PERIODIC);

	// Set stream position to 0
	LONGLONG	llStart = 0, llStop = 0;
	hr = m_pMS->SetPositions( &llStart,AM_SEEKING_AbsolutePositioning,NULL, 0);

	hr = m_pMC->Run();
	if (SUCCEEDED(hr)) {
		if (m_pGC) 
			m_pGC->OnGraphStarted();
	}
	return hr;
}
HRESULT	CDirectShowGraph::Cancel ( void )
{
	HRESULT hr = S_OK;
	if (!m_pMC) {
		return E_POINTER;
	}


	hr = m_pMC->Stop();
	if (SUCCEEDED(hr)) {
		if (m_pGC) 
			m_pGC->OnGraphStopped();
	}
	
	// Set stream position to 0
	LONGLONG	llStart = 0, llStop = 0;
	hr = m_pMS->SetPositions( &llStart,AM_SEEKING_AbsolutePositioning,NULL, 0);


	timeKillEvent( m_mmTimer );
	return hr;
}

void	CDirectShowGraph::OnTimer( void )
{
	if (m_pGC)
		m_pGC->OnTimer();

	CheckGraphEvents();
}

HRESULT		CDirectShowGraph::GetDuration( LONGLONG		*pllDuration )
{
	HRESULT hr = S_OK;
	if (m_llDuration) {
		*pllDuration = m_llDuration;
		return S_OK;
	}

	if (!m_pMS) {
		(*pllDuration) = 0;
		return E_POINTER;
	}
	return m_pMS->GetDuration( pllDuration );
}

		
REFERENCE_TIME	CDirectShowGraph::GetCurrentPosition( void )
{
	CComVariant var = 0;
	HRESULT hr = m_pMuxConfig->GetValue(&SMASFMux_CurrentTime, &var );
	return var.ullVal;
}



HRESULT	CDirectShowGraph::CheckGraphEvents( void )
{
	HRESULT hr = S_OK;
	if(m_pMEx)	
	{
		long	 lEvent = 0, lParam1 = 0, lParam2 = 0;
		while((hr = m_pMEx->GetEvent(&lEvent, &lParam1, 
			&lParam2, 0)) != E_ABORT)
		{
			m_pMEx->FreeEventParams(lEvent, lParam1, lParam2);
			if (lEvent == EC_COMPLETE) {
				OnComplete(); 
			} else if ( lEvent == EC_ERRORABORT) {
				OnAbort();
			}
		}
	}
	return hr;
}

HRESULT	CDirectShowGraph::OnComplete( void )
{
	return Cancel();
}

HRESULT	CDirectShowGraph::OnAbort( void )
{
	if (m_pGC) 
		m_pGC->OnAbort();
	return Cancel();
}

void			CDirectShowGraph::IndexASF( BOOL	bIndex )
{
	m_bIndexASF = bIndex;
}

void			CDirectShowGraph::WriteLog( BOOL	bWriteLog )
{
	m_bWriteLog = bWriteLog;
}



HRESULT	CDirectShowGraph::ConfigureASFWriter( void )
{
	HRESULT hr = S_OK;
	UINT n = 0;
	if ( !m_fltAsfMuxer ){
		return E_POINTER;
	}
	

	CComVariant val = (UINT)0;
	val.ulVal |= SMM_ASFMuxFlags_WriteIndex;

	hr = m_pMuxConfig->SetValue( &SMASFMux_Flags, &val );
	if (FAILED(hr)) {
		return hr;
	}

	for (n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n])
		{
			hr = m_Branches[n]->ConfigureASFWriter();
			if (FAILED(hr)) {
				return hr;
			}
		}
	}
	return hr;
}

HRESULT	CDirectShowGraph::ShowASFProps( HWND	hWnd )
{
	HRESULT hr = S_OK;
	if (!m_fltAsfMuxer) {
		return E_POINTER;
	}

	CComPtr<ISpecifyPropertyPages>pSPPages;
	hr	=	m_fltAsfMuxer->QueryInterface(&pSPPages);
	if (SUCCEEDED(hr))
	{
		hr	=	pSPPages->GetPages(&m_Pages);
		if (SUCCEEDED(hr))
		{
			IBaseFilter	*pMuxer = m_fltAsfMuxer;
			// Display the filter's property page
			hr	=	OleCreatePropertyFrame(
				hWnd,                 // Parent window
				0,                      // x (Reserved)
				0,                      // y (Reserved)
				L"ASF Muxer propertries",     // Caption for the dialog box
				1,                      // Number of filters
				(IUnknown **)&pMuxer,  // Pointer to the filter 
				m_Pages.cElems,          // Number of property pages
				m_Pages.pElems,          // Pointer to property page CLSIDs
				0,                      // Locale identifier
				0,                      // Reserved
				NULL );
			CoTaskMemFree(m_Pages.pElems);
		}
		pSPPages.Release();
	}
	return hr;
}

BOOL			CDirectShowGraph::AllowCustomFOURCC( void )
{
	HRESULT hr = S_OK;
	for (UINT n = 0; n < m_nBranchesCount; n++)
	{
		if (m_Branches[n]) 
		{
			TCHAR	szType[ 20 ];
			m_Branches[n]->GetType( szType );
			if (!_tcscmp(szType, _T("Video"))) {
				return ((CVideoBranch *)m_Branches[n])->AllowCustomFOURCC();
			}
		}
	}
	return false;
}