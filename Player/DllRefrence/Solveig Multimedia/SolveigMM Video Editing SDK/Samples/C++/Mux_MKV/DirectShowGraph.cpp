////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2011-2012 Solveig Multimedia
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
#include "DirectShowGraph.h"

#include "PropID_MatroskaMuxer.h"
#include "PropID_AVIWriter.h"



CDirectShowGraph::CDirectShowGraph(void):
m_fMuxer(NULL),
m_ffileWriter(NULL),
m_pMuxConfig(NULL),
m_pMC(NULL),
m_pMS(NULL),
m_pMF(NULL),
m_pMEx(NULL),
bInited(false)
{
	m_OutputType = OT_MKV;
}

CDirectShowGraph::~CDirectShowGraph(void)
{
}

HRESULT CDirectShowGraph::Init(const CString& inputFile, const CString& outputFile, OutType outType)
{
	//Before Reseting save old muxer settings

	Reset();
	if (outputFile.IsEmpty())
	{
		MessageBox(NULL, _T("No output file Specified"), _T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
		return E_INVALIDARG;
	}
	HRESULT hr = S_OK;

	hr = CoCreateInstance( CLSID_FilterGraph );
	if (FAILED(hr)) {
		return hr;
	}
	AddToROT(); // removing is inside CDirectShowGraphBase::Reset()
	hr = QueryInterfaces();
	if (FAILED(hr)) {
		MessageBox(NULL, _T("Failed To Get Graph Intervaces"), _T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
		return hr;
	}
	// At first, add MKV Muxer filter
	LPCTSTR str2 = inputFile;
	if( outType == OT_MKV )
	{
		hr = AddFilter(CLSID_SMM_MKV_MUXER, _T("SolveigMM MKV Muxer Filter"), m_fMuxer);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Creating SolveigMM MKV Muxer has been failed"), _T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
			return hr;
		}
	}
	else
	{
		hr = AddFilter(CLSID_SMM_MP4_MUXER, _T("SolveigMM MP4 Muxer Filter"), m_fMuxer);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Creating SolveigMM MKV Muxer has been failed"), _T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
			return hr;
		}
	}
	if( m_pMuxConfig ){
		m_pMuxConfig.Release();
		m_pMuxConfig = NULL;
	}

	hr = m_fMuxer.QueryInterface( &m_pMuxConfig );
	if (FAILED(hr)) {
		MessageBox(NULL,_T("Can't get IModuleConfig at SolveigMM MKV Muxer"),_T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
		return hr;
	}

	if( outType != OT_MKV )
	{
		VARIANT var = {0};
		var.lVal = (LONG) MMT_isom;
		if( outType == OT_MOV )
			var.lVal = (LONG) MMT_mov;
		m_pMuxConfig->SetValue(&SMMP4_MUX_TYPE, &var);
	}

	// add file writer
	hr = AddSinkFilter(CLSID_SMAVIWriter, _T("File Writer"), m_ffileWriter, outputFile );

	if (FAILED(hr)) {
		MessageBox(NULL,_T("Can't create File Writer Fltr"),_T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
		return hr;
	}
	// connect m_fMuxer and file writer
	hr = ConnectFilters(&m_fMuxer, &m_ffileWriter);
	if (FAILED(hr)){
		MessageBox(NULL,_T("Can't connect SolveigMM MKV Muxer to fileWriter Fltr"),_T("SolveigMM MKV Muxer Sample App"),MB_ICONERROR);
		return hr;
	}
	// Then, render source file 
	hr = p->RenderFile( inputFile, NULL );
	if (FAILED(hr)) {
		return hr;
	}
	m_OutputType = outType;
	FillStreamsInformation();
	bInited = true;
	return hr;
}
HRESULT CDirectShowGraph::QueryInterfaces()
{
	HRESULT hr = S_OK;
	hr = QueryInterface( &m_pMC );
	if (FAILED(hr))
		return hr;

	hr = QueryInterface( &m_pMS);
	if (FAILED(hr))
		return hr;

	hr = QueryInterface( &m_pMF);
	if (FAILED(hr))
		return hr;
	hr = QueryInterface( &m_pMEx);
	if (FAILED(hr))
		return hr;
	return hr;
}

void CDirectShowGraph::Reset()
{
	bInited = false;
	m_pMC.Release();
	m_pMS.Release();
	m_pMF.Release();
	m_pMEx.Release();

	m_pMuxConfig.Release();
	m_fMuxer.Release();
	m_ffileWriter.Release();

	CDirectShowGraphBase::Reset();
}


HRESULT		CDirectShowGraph::Start	( void )
{
	HRESULT hr = S_OK;
	if (!m_pMC || !m_pMF || !m_pMS) {
		return E_POINTER;
	}
	hr = m_pMF->SetSyncSource( NULL );
	if (FAILED(hr)) 
		return hr;
	hr = m_pMC->Run();
	return hr;
}

HRESULT		CDirectShowGraph::Cancel	( void )
{
	if (!m_pMC)
		return E_POINTER;
	HRESULT hr = m_pMC->Stop();
	return hr;
}
HRESULT CDirectShowGraph::GetState(FILTER_STATE& fs)
{
	if (!m_pMC)
		return E_POINTER;
	HRESULT hr = m_pMC->GetState(1000, (OAFilterState*)&fs);
	return hr;
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
				Cancel(); 
			} else if ( lEvent == EC_ERRORABORT) {
				Cancel();
			}
		}
	}
	return hr;
}

bool CDirectShowGraph::isRunning()
{
	if (isInitialized())
	{
		CheckGraphEvents();
		FILTER_STATE fs;
		GetState(fs);
		if (fs == State_Running)
			return true;
	}
	return false;
}
void CDirectShowGraph::FillStreamsInformation()
{
	if (!m_fMuxer)
		return;

	m_streamMediaTypes.clear();
	UINT nPinCount = 0,  n = 0;
	HRESULT hr = m_fMuxer.GetPinCount( &nPinCount );
	if (FAILED(hr)) 
		return;

	CDirectShowPin	pin;
	for (n = 0; n < nPinCount; n++)
	{
		hr = m_fMuxer.GetPin(n, pin );
		if (SUCCEEDED(hr)) 
		{
			if (pin.IsInput()) {
				CMediaType mt;
				hr = pin.GetMediaType(mt);
				if (SUCCEEDED(hr))
				{
					m_streamMediaTypes.push_back(mt);
				}
			}
			pin.Release();
		}
	}
}
void CDirectShowGraph::DisconnectMuxerPin(int nNum)
{
	if (!m_fMuxer)
		return;
	CDirectShowPin pin;
	HRESULT hr = m_fMuxer.GetPin( nNum, pin );
	if( SUCCEEDED(hr) )
		pin->Disconnect();
}
void	CDirectShowGraph::GetStreamsMediaTypes(vector<CMediaType>& types/*output*/)
{
	types =  m_streamMediaTypes;
}

int CDirectShowGraph::GetStreamsCount()
{
	return m_streamMediaTypes.size();
}

bool CDirectShowGraph::GetStreamProps(int index,  TRACK_PROPS& tp/*out*/)
{
	if (!m_pMuxConfig)
		return false;
	HRESULT hr = S_OK;
	CComVariant var;
	TRACK_PROPS tpout(index);
	var.pbVal = (BYTE*)&tpout;
	hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	if (FAILED(hr))
		return false;
	tp = tpout;
	return true;
}
HRESULT CDirectShowGraph::SetStreamEnabled(int index, bool bEnabled)
{
	if (!m_pMuxConfig)
		return E_NOINTERFACE;
	HRESULT hr = S_OK;
	TRACK_PROPS tp(index);
	{
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	}
	if (SUCCEEDED(hr))
	{
		tp.bEnable = bEnabled;
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
	}
	return hr;
}

HRESULT CDirectShowGraph::SetStreamLanguage(int index,const CString& langEnglishName)
{
	if (!m_pMuxConfig)
		return E_NOINTERFACE;
	HRESULT hr = S_OK;
	TRACK_PROPS tp(index);
	{
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	}
	if (SUCCEEDED(hr))
	{
		if (tp.language)
			SysFreeString(tp.language);

		tp.language = SysAllocString(langEnglishName);
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
	}
	return hr;
}

HRESULT CDirectShowGraph::SetStreamName(int index, const CString& name)
{
	if (!m_pMuxConfig)
		return E_NOINTERFACE;
	HRESULT hr = S_OK;
	TRACK_PROPS tp(index);
	{
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	}
	if (SUCCEEDED(hr))
	{
		if (tp.name)
			SysFreeString(tp.name);

		tp.name = SysAllocString(name);
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
	}
	return hr;
}

HRESULT CDirectShowGraph::SetStreamDefault(int index, bool bDefault)
{
	if (!m_pMuxConfig)
		return E_NOINTERFACE;
	HRESULT hr = S_OK;
	TRACK_PROPS tp(index);
	{
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	}
	if (SUCCEEDED(hr))
	{
		tp.bDefault = bDefault;
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
	}
	return hr;
}

HRESULT CDirectShowGraph::SetStreamForced(int index, bool bForced)
{
	if (!m_pMuxConfig)
		return E_NOINTERFACE;
	HRESULT hr = S_OK;
	TRACK_PROPS tp(index);
	{
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
	}
	if (SUCCEEDED(hr))
	{
		tp.bForced = bForced;
		CComVariant var;
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
	}
	return hr;
}

bool CDirectShowGraph::isInitialized()
{
	return bInited;
}
int CDirectShowGraph::GetProgress()
{
	if (!m_pMuxConfig || !m_pMS)
		return 0;
	LONGLONG duration = 0;
	HRESULT hr = m_pMS->GetDuration(&duration);
	if (FAILED(hr))
		return 0;

	CComVariant var;
	GUID clsidToAsk = SMMP4M_MUX_TIME;
	if( GetOutType() == OT_MKV )
		clsidToAsk = SMMKVM_MUXTIME;
	hr = m_pMuxConfig->GetValue(&clsidToAsk, &var);
	if (FAILED(hr))
		return 0;

	LONGLONG curTime = var.llVal;
	int ret = (int)(((double)curTime/(double)duration)*100.0);
	return ret;
}

HRESULT CDirectShowGraph::RestoreMuxerSettings()
{
	if (!m_pMuxConfig)
		return E_POINTER;

	HRESULT hr = S_OK;
	for (UINT i = 0; i < m_savedTrackProps.size(); i++)
	{
		CComVariant var;
		var.pbVal = (BYTE*)&m_savedTrackProps[i];
		hr = m_pMuxConfig->SetValue(&SMMKVM_TRACKPROPS, &var);
		if (FAILED(hr))
			return hr;
	}
	return hr;
}
void CDirectShowGraph::ClearMuxerSettings()
{
	m_savedTrackProps.clear();
	int i = 0;
}
HRESULT CDirectShowGraph::SaveMuxerSettings()
{
	if (!m_pMuxConfig)
		return E_POINTER;

	m_savedTrackProps.clear();
	CComVariant var;
	HRESULT hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKSCOUNT, &var);
	if (FAILED(hr))
		return hr;

	size_t streamsCount = var.iVal;
	for (size_t i = 0; i< streamsCount; i++)
	{
		TRACK_PROPS tp(i);
		var.pbVal = (BYTE*)&tp;
		hr = m_pMuxConfig->GetValue(&SMMKVM_TRACKPROPS, &var);
		if (FAILED(hr))
			return hr;
		m_savedTrackProps.push_back(tp);
	}
	return hr;
}
HRESULT	CDirectShowGraph::ShowMKVProps( HWND	hWnd )
{
	HRESULT hr = S_OK;
	if (!m_fMuxer) {
		return E_POINTER;
	}
	CAUUID	pages;
	CComPtr<ISpecifyPropertyPages>pSPPages;
	hr	=	m_fMuxer->QueryInterface(&pSPPages);
	if (SUCCEEDED(hr))
	{
		hr	=	pSPPages->GetPages(&pages);
		if (SUCCEEDED(hr))
		{
			IBaseFilter	*pMuxer = m_fMuxer;
			// Display the filter's property page
			hr	=	OleCreatePropertyFrame(
				hWnd,                 // Parent window
				0,                      // x (Reserved)
				0,                      // y (Reserved)
				L"Matroska Muxer properties",     // Caption for the dialog box
				1,                      // Number of filters
				(IUnknown **)&pMuxer,  // Pointer to the filter 
				pages.cElems,          // Number of property pages
				pages.pElems,          // Pointer to property page CLSIDs
				0,                      // Locale identifier
				0,                      // Reserved
				NULL );
			CoTaskMemFree(pages.pElems);
		}
		pSPPages.Release();
	}
	return hr;
}