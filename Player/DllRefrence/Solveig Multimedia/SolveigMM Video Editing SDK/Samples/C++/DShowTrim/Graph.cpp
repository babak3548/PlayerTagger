////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2012 Solveig Multimedia
// All rights are reserved. 
//
// Solveig Multimedia reserves the right to make changes without
// notice at any time. Solveig Multimedia makes no warranty,
// expressed, implied or statutory, including but not limited to any implied
// warranty of merchantability of fitness for any particular purpose, or that
// the use will not infringe any third party patent, copyright or trademark.
// Solveig Multimedia must not be liable for any loss or damage
// arising from its use.
// 
//////////////////////////////////////////////////////////////////////////////////


// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Graph.h"

#define WM_GRAPHNOTIFY WM_APP + 1

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
	IMoniker * pMoniker;
	IRunningObjectTable *pROT;
	if (FAILED(GetRunningObjectTable(0, &pROT))) {
		return E_FAIL;
	}
	WCHAR wsz[256];
	wsprintf(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
	if (SUCCEEDED(hr)) {
		hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph,
			pMoniker, pdwRegister);
		pMoniker->Release();
	}
	pROT->Release();
	return hr;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define  SELF_RELEASE_DOT(val) {	\
		if(val){					\
			val.Release();			\
			val = NULL;				\
		}							\
		}

CGraph::CGraph(HRESULT *phr):
m_pGraph(NULL),
m_pControl(NULL),
m_pEventEx(NULL),
m_pFilesSrc(NULL),
m_pTrimmer(NULL),
m_pAVISplitter(NULL),
m_pFileWriter(NULL),
m_pAVIMuxer(NULL),
m_bGraphCompleted(FALSE)
{
	// Initialize the COM library.
    *phr = CoInitialize(NULL);
}

CGraph::CGraph():
m_pGraph(NULL),
m_pControl(NULL),
m_pEventEx(NULL),
m_pFilesSrc(NULL),
m_pTrimmer(NULL),
m_pAVISplitter(NULL),
m_pFileWriter(NULL),
m_pAVIMuxer(NULL),
m_bGraphCompleted(FALSE)
{
	CoInitialize(NULL);

	WNDCLASS wc;
	// Register the main window class. 
	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC) CGraph::DefWindowProcThunk; 
	wc.cbClsExtra		= 0; 
	wc.cbWndExtra		= 0; 
	wc.hInstance		= (HINSTANCE)this; 
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL; 
	wc.lpszMenuName		=  NULL; 
	wc.lpszClassName	= _T("GraphMessageWnd"); 

	ATOM x = RegisterClass(&wc);

	m_hWnd = CreateWindow(_T("GraphMessageWnd"),
		_T(""),
		0,
		0,
		0,
		1,
		1,
		NULL,
		NULL,
		(HINSTANCE)this,
		0);
	int t = 0;
}

CGraph::~CGraph()
{
	Deinit();
	CoUninitialize();
}

void	CGraph::Deinit()
{
	SELF_RELEASE_DOT(m_pGraph);
	SELF_RELEASE_DOT(m_pControl);
	SELF_RELEASE_DOT(m_pEventEx);


	SELF_RELEASE_DOT(m_pFilesSrc);
	SELF_RELEASE_DOT(m_pTrimmer);
	SELF_RELEASE_DOT(m_pAVISplitter);
	SELF_RELEASE_DOT(m_pFileWriter);
	SELF_RELEASE_DOT(m_pAVIMuxer);

}
HRESULT CGraph::Init()
{
	
	
	// Create the filter graph manager and query for interfaces.
	HRESULT  hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void **)&m_pGraph);
    if (FAILED(hr)){
		MessageBox(NULL,L"Can't create IGraphBuilder objest",L"Error",MB_OK);
        return hr;
    }

	DWORD dwRegister = 0;
	AddToRot( m_pGraph, &dwRegister );

	hr = m_pGraph.QueryInterface(&m_pControl);
	if (FAILED(hr)){
		MessageBox(NULL,L"Can't query IMediaControl Interface",L"Error",MB_OK);
        return hr;
    }

	hr = m_pGraph.QueryInterface(&m_pEventEx);
	if (FAILED(hr)){
		MessageBox(NULL,L"Can't query IMediaEvent Interface",L"Error",MB_OK);
		return hr;
	}

	hr = m_pEventEx->SetNotifyWindow( (OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
	hr = m_pEventEx->SetNotifyFlags(0);
  


	hr = AddFilters();
	if (FAILED(hr)){
		return hr;
	}
	
	hr = ConnectFilters();
	if (FAILED(hr)){
		return hr;
	}


	CComVariant var;
	var.vt		= VT_BYREF | VT_UI1;
	var.pbVal	= (BYTE*)&m_params.trim_param;
	hr = m_pTrimmerConf->SetValue(&SMAT_TrimList,&var);
	hr = m_pTrimmerConf->CommitChanges(NULL);

	return hr;
}

HRESULT CGraph::Start(DWORD dwTimeout)
{


	HRESULT hr = m_pControl->Run();
	
	DWORD dwStart = GetTickCount();
	while(dwStart - GetTickCount() < dwTimeout)
	{
		if(State_Running ==  GetGraphState())
		{
			break;
		}
	}
	m_bGraphCompleted = FALSE;

	return hr;
}

HRESULT CGraph::Stop()
{
	HRESULT hr = m_pControl->Stop();
	long lEvCode;
	m_pEventEx->WaitForCompletion(2000,&lEvCode);
	RemoveAllFilters();
	
	return hr;
}

BOOL CGraph::WaitForStop()
{
	HRESULT hr = m_pControl->StopWhenReady();

	BOOL bval = (hr == S_OK) ;
	return bval; 
}
HRESULT CGraph::AddFilters()
{
	// Create MS Async Source Filter
	HRESULT hr = CoCreateInstance(CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (void **)&m_pFilesSrc);
	if ( FAILED(hr) ){
		printf("ERROR - Could not create Async Source Filter");
		return hr;
	}

	CComPtr<IFileSourceFilter> pIFileSourceFilter = NULL;
	hr = m_pFilesSrc->QueryInterface(&pIFileSourceFilter);
	if (FAILED(hr)){
		printf("ERROR - Could not get IFileSourceFilter interface");
		return hr;
	}


	hr = pIFileSourceFilter->Load( m_params.in_fn.AllocSysString(), NULL );
	if (FAILED(hr)){
		printf("ERROR - Could not load source file");
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pFilesSrc, L"FileSrc");
	if ( FAILED(hr) ){
		printf("ERROR - Could not add Async Source Filter to graph");
		return hr;
	}

	//
	// create SolveigMM Trimmer Filter
	//
	hr = CoCreateInstance(CLSID_SMAVITrimmerFilter, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (void **)&m_pTrimmer);
	if (FAILED(hr)){
		printf("ERROR - Could not create the SolveigMM  Trimmer Filter");
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pTrimmer, L"SolveigMM Trimmer Filter");
	if (FAILED(hr)){
		printf("ERROR - Could not add the SolveigMM Video Trimmer Filter to graph");
		return hr;
	}

	hr = m_pTrimmer.QueryInterface(&m_pTrimmerConf);
	if (FAILED(hr)){
		printf("ERROR - Could not get IModuleConfig interface at SolveigMM Trimmer filter");
		return hr;
	}
	//
	// create MS AVI Splitter
	//
	hr = CoCreateInstance(CLSID_AviSplitter, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (void **)&m_pAVISplitter);
	if (FAILED(hr)){
		printf("ERROR - Could not create the MS AVI Splitter Filter.");
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pAVISplitter, L"MS AVI Splitter ");
	if (FAILED(hr)){
		printf("ERROR - Could not add MS AVI Splitter  to graph");
		return hr;
	}

	//
	// create MS AVI Muxer
	//
	hr = CoCreateInstance(CLSID_AviDest, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (void **)&m_pAVIMuxer );
	if (FAILED(hr)){
		printf("ERROR - Could not create the MS AVI Muxer Filter.");
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pAVIMuxer, L"MS AVI Muxer ");
	if (FAILED(hr)){
		printf("ERROR - Could not add MS AVI Muxer to graph");
		return hr;
	}

	//
	// create MS File Writer
	//
	hr = CoCreateInstance(CLSID_FileWriter, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (void **)&m_pFileWriter);
	if ( FAILED(hr) ){
		printf("ERROR - Could not create the MS File Writer");
		return hr;
	}
	

	CComPtr<IFileSinkFilter > pIFileSinkFilter  = NULL;
	hr = m_pFileWriter->QueryInterface(&pIFileSinkFilter);
	if (FAILED(hr)){
		printf("ERROR - Could not get IFileSinkFilter interface");
		return hr;
	}


	hr = pIFileSinkFilter->SetFileName( m_params.out_fn.AllocSysString(), NULL );
	if (FAILED(hr)){
		printf("ERROR - Could not set out file");
		return hr;
	}
	
	hr = m_pGraph->AddFilter(m_pFileWriter, L"MS File Writer ");
	if (FAILED(hr)){
		printf("ERROR - Could not add MS File Writer to graph");
		return hr;
	}
	
	return hr;
}


	


HRESULT CGraph::ConnectFilters()
{
	ASSERT( m_pFilesSrc );
	ASSERT( m_pTrimmer );
	ASSERT( m_pAVISplitter );
	ASSERT( m_pFileWriter );
	ASSERT( m_pAVIMuxer );

	HRESULT hr = NOERROR;
	CComPtr<IPin> pPinOut	= NULL;
	CComPtr<IPin> pPinIn	= NULL;

	hr = ConnectFilters( m_pFilesSrc, m_pAVISplitter ); 
	if(FAILED(hr) ){
		return hr;
	}

	//
	// Slitter to trimmer connection
	//
	pPinOut = GetPin(m_pAVISplitter, PINDIR_OUTPUT, true, MEDIATYPE_Video, MEDIASUBTYPE_NULL);
	if( pPinOut )
	{
		hr = ConnectPin2Filter( pPinOut , m_pTrimmer ); 
		if(FAILED(hr) ){
			return hr;
		}
		pPinOut.Release();

		pPinOut = GetPin(m_pTrimmer, PINDIR_OUTPUT, true, MEDIATYPE_Video, MEDIASUBTYPE_NULL);
		hr = ConnectPin2Filter(pPinOut ,m_pAVIMuxer); 
		if(FAILED(hr) ){
			return hr;
		}

		pPinOut.Release();
	}

	pPinOut = GetPin(m_pAVISplitter, PINDIR_OUTPUT, true, MEDIATYPE_Audio, MEDIASUBTYPE_NULL);
	if( pPinOut )
	{
		hr = ConnectPin2Filter( pPinOut , m_pTrimmer ); 
		if(FAILED(hr) ){
			return hr;
		}
		pPinOut.Release();

		pPinOut = GetPin(m_pTrimmer, PINDIR_OUTPUT, true, MEDIATYPE_Audio, MEDIASUBTYPE_NULL);
		hr = ConnectPin2Filter(pPinOut ,m_pAVIMuxer); 
		if(FAILED(hr) ){
			return hr;
		}

		pPinOut.Release();
	}

	//
	// try to get at least one connected pin at muxer
	//
	pPinIn =  GetPin( m_pAVIMuxer, PINDIR_INPUT, false );
	if( !pPinIn ){
		return E_FAIL;
	}
	pPinIn.Release();

	hr = ConnectFilters(m_pAVIMuxer,m_pFileWriter); 
	if(FAILED(hr) ){
		return hr;
	}

	return hr;
}

IPin* CGraph::GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir,bool Free)
{
    BOOL       bFound = FALSE;
    IEnumPins  *pEnum;
    IPin       *pPin;
	
    pFilter->EnumPins(&pEnum);
    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if (bFound = (PinDir == PinDirThis && (Free ? !IsConnected(pPin) : IsConnected(pPin)) )){
			bFound = TRUE;
			break;
		}
         
        pPin->Release();
    }
    pEnum->Release();
    return (bFound ? pPin : 0);  
}

IPin* CGraph::GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir,bool Free, REFCLSID MajorType,REFCLSID  Subtype)
{
    BOOL       bFound	= FALSE;
    IEnumPins  *pEnum	= NULL;
    IPin       *pPin	= NULL;
	
	CMediaType	mt(&MajorType) ;
	if( Subtype != MEDIASUBTYPE_NULL)
	{
		mt.SetSubtype(&Subtype);
		if(*mt.Type() == MEDIATYPE_Video && *mt.Subtype() == MEDIASUBTYPE_MPEG2_VIDEO){
			mt.SetFormatType(&FORMAT_MPEG2_VIDEO);
		}
	}
	
	if(FAILED(pFilter->EnumPins(&pEnum))){
		return FALSE;
	}
    
    while(pEnum->Next(1, &pPin, 0) == S_OK 	&& bFound == FALSE)
    {
		PIN_DIRECTION PinDirThis;    
		pPin->QueryDirection(&PinDirThis);
		
		if ((PinDir == PinDirThis && (Free ? !IsConnected(pPin) : IsConnected(pPin)) ))
		{
			
			bFound = (PinDir == PINDIR_INPUT) ?	IsInPinAcceptsMediaType(pPin,&mt) :
												IsOutPinAcceptsMediaType(pPin,&mt);
			if(bFound == TRUE){
				break;
			}
		}
        pPin->Release();
    }
    pEnum->Release();
    return (bFound ? pPin : NULL);  
}


IPin* CGraph::GetPin(PIN_DIRECTION PinDir,bool Free, REFCLSID MajorType,REFCLSID  Subtype)
{
    
	IEnumFilters *pEnumFilt	= NULL;
	IBaseFilter	 *pFilter	= NULL;
	IEnumPins    *pEnum		= NULL;
    
	IPin  *pPin		= NULL;
	BOOL  bFound	= FALSE;
	
	if( FAILED(m_pGraph->EnumFilters(&pEnumFilt)) ){
		return 0;
	}
	
	CMediaType	mt(&MajorType) ;
	mt.SetSubtype(&Subtype);
	if(*mt.Type() == MEDIATYPE_Video && *mt.Subtype() == MEDIASUBTYPE_MPEG2_VIDEO){
		mt.SetFormatType(&FORMAT_MPEG2_VIDEO);
	}
	
	while(pEnumFilt->Next(1, &pFilter, 0) == S_OK && bFound == FALSE)
	{
		pFilter->EnumPins(&pEnum);
		
		while(pEnum->Next(1, &pPin, 0) == S_OK && bFound == FALSE)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			
			if( PinDir == PinDirThis && (Free ? !IsConnected(pPin) : IsConnected(pPin)) )
			{
				bFound = (PinDir == PINDIR_INPUT) ?	IsInPinAcceptsMediaType(pPin,&mt) :
													IsOutPinAcceptsMediaType(pPin,&mt);
				if(bFound == TRUE){
					break;
				}
			}
			pPin->Release();
		}
		pFilter->Release();
	}
	pEnum->Release();
	
    return (bFound ? pPin : 0);  
}



BOOL CGraph::IsConnected(IPin* pPin)
{
	_ASSERT(pPin);
	IPin* pConnected = NULL;
	HRESULT	hr = VFW_E_NOT_CONNECTED;
	if(SUCCEEDED(hr = pPin->ConnectedTo(&pConnected)) && pConnected)
		pConnected->Release();
	return (hr == S_OK && pConnected) ? TRUE : FALSE;
}

BOOL CGraph::IsInPinAcceptsMediaType(IPin* pPin,CMediaType *pmt)
{
	_ASSERT(pPin && pmt);
	
	HRESULT hr = pPin->QueryAccept(pmt);
	return SUCCEEDED(hr) && hr != S_FALSE;
}

BOOL CGraph::IsOutPinAcceptsMediaType(IPin* pPin,CMediaType *pmt)
{
	_ASSERT(pPin && pmt);
	
	CComPtr<IEnumMediaTypes> pEnumMT	= NULL;
	AM_MEDIA_TYPE*	pMt					= NULL;
	BOOL bFound							= FALSE;
	
	if( FAILED ( pPin->EnumMediaTypes(&pEnumMT) ) ){
		return FALSE;
	}
	
	while( pEnumMT->Next(1, &pMt, 0) == S_OK && bFound == FALSE )
	{
		if( pMt->majortype == pmt->majortype)
		{
			if (	pmt->subtype == MEDIASUBTYPE_NULL ||
					pmt->subtype == pMt->subtype )
			{
				bFound =  TRUE;
			}
		}
		
		DeleteMediaType(pMt);
	}

	return bFound; 
}

LRESULT CGraph::DefWindowProcThunk	( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CGraph * lpObject = (CGraph*)GetWindowLong(hwnd, GWL_HINSTANCE);

	// Process CREATE messages
	switch (uMsg)
	{
		case WM_NCCREATE:
			return TRUE;

		case WM_CREATE:
			return 0; 
	}

	// for another messages call handler
	if ( lpObject != NULL )
		lpObject->OnGraphNotifyEvent(uMsg, wParam, lParam);

	return 0;
}

void CGraph::OnGraphNotifyEvent(UINT uMsg, long wParam, long lParam)
{
	// Process only WM_GRAPHNOTIFY
	if (uMsg != WM_GRAPHNOTIFY)
		return;

	HRESULT hr	 = S_OK;
	long lEvent  = 0;
	long lParam1 = 0;
	long lParam2 = 0;

	hr = m_pEventEx->GetEvent(&lEvent, &lParam1, &lParam2,0);

	switch (lEvent)
	{
	
	case EC_ERRORABORT:
	case EC_COMPLETE:
			m_bGraphCompleted = TRUE;
	default:
		break;
	}

}

HRESULT CGraph::RemoveAllFilters()
{

	if(State_Stopped != GetGraphState()){
	return E_FAIL;
	}
	// Enumerate the filters in the graph.
	IEnumFilters *pEnum = NULL;
	HRESULT hr = m_pGraph->EnumFilters(&pEnum);
	if (SUCCEEDED(hr))
	{
		IBaseFilter *pFilter = NULL;
		while (S_OK == pEnum->Next(1, &pFilter, NULL))
		{
			// Remove the filter.
			m_pGraph->RemoveFilter(pFilter);
			// Reset the enumerator.
			pEnum->Reset();
			pFilter->Release();
		}
		pEnum->Release();
	}
	return hr;
	
}

_FilterState CGraph:: GetGraphState()
{
	OAFilterState oafilterstate; 
	m_pControl->GetState(0,&oafilterstate);
	return (_FilterState)oafilterstate;
}

HRESULT	CGraph::ConnectPin2Filter( IPin *pUpPin, IBaseFilter *pDnFilt)
{
	ASSERT( pUpPin );
	ASSERT( pDnFilt );

	CComPtr<IEnumPins>  pEnum	= NULL;
	CComPtr<IPin>       pPin	= NULL;
	HRESULT hr = S_OK;
	hr = pDnFilt->EnumPins(&pEnum);
	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if (	PinDirThis	== PINDIR_INPUT && 
				FALSE	== IsConnected(pPin) )
		{
			hr = m_pGraph->Connect(pUpPin,pPin);
			if(SUCCEEDED(hr)){
				break;
			}
		}
		pPin.Release();
	}
	pEnum.Release();

	return hr;
}

HRESULT	CGraph::ConnectFilters(IBaseFilter *pUpFilt,IBaseFilter *pDnFilt)
{

	HRESULT hr = NOERROR;
	CComPtr<IPin> pPinOut	= NULL;
	CComPtr<IPin> pPinIn	= NULL;
	USES_CONVERSION;

	ASSERT( pDnFilt );
	ASSERT( pUpFilt );
	
	pPinOut = GetPin(pUpFilt, PINDIR_OUTPUT, true );
	if(!pPinOut){
		return E_FAIL;
	}

	pPinIn = GetPin(pDnFilt ,PINDIR_INPUT,true);
	if(!pPinIn ){
		return E_FAIL;
	}


	PIN_INFO pi_In		= {0};
	PIN_INFO pi_Out		= {0};
	FILTER_INFO fi_Up	= {0};
	FILTER_INFO fi_Dn	= {0};
	TCHAR ch[100];

#define QUERY_INFO(szVal) {                 \
	pPinOut->QueryPinInfo(&pi_Out);			\
	pi_Out.pFilter->QueryFilterInfo(&fi_Up);\
	pPinIn->QueryPinInfo(&pi_In);			\
	pi_In.pFilter->QueryFilterInfo(&fi_Dn);	\
	wprintf(szVal,"Can't connect \"%s\" pin of \"%s\" filter with \"%s\" pin of \"%s\" filter",\
	/*W2A*/(pi_Out.achName), /*W2A*/(fi_Up.achName), /*W2A*/(pi_In.achName),/*W2A*/(fi_Dn.achName));\
}	

	if(FAILED (hr = m_pGraph->Connect(pPinOut, pPinIn))){
		QUERY_INFO(ch);
		MessageBox (NULL,ch,L"ERROR",MB_OK);
		return hr;
	}

	pPinIn.Release();
	pPinOut.Release();
	return hr;
}

void CGraph::just()
{
//Deactivate
}
