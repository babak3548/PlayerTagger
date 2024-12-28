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
#include <Dvdmedia.h>

#include "player.h"
#include "register_work.h"


CPlayer::CPlayer()
:CGraphManager()
{
	m_InputFile = _T("");
	m_pIBasicAudio = NULL;
}

CPlayer::~CPlayer()
{
}

HRESULT	CPlayer::SetPosition(REFERENCE_TIME rtPos, REFERENCE_TIME rtEndPos)
{
	m_hrError = E_FAIL;

	if(IsInitialized())
	{
		DWORD dwStopFlag = AM_SEEKING_AbsolutePositioning;		
		if(!rtEndPos)
			dwStopFlag = AM_SEEKING_NoPositioning;

		m_hrError = m_pIMS->SetPositions(&rtPos, AM_SEEKING_AbsolutePositioning , &rtEndPos, dwStopFlag);
		
		if(rtPos == 0 || rtPos == GetDuration())
			Sleep(10);
	}

	return m_hrError;
}

void CPlayer::Reset()
{
	if(m_pIVideoWindow)
	{
		m_pIVideoWindow.Release();
		m_pIVideoWindow = NULL;
	}

	CGraphManager::Reset();
}

HRESULT	CPlayer::Run()
{
	return CGraphManager::Run(TRUE);
}

HRESULT	CPlayer::Pause()
{
	return CGraphManager::Pause(TRUE);
}

HRESULT	CPlayer::Stop()
{
	return CGraphManager::Stop(TRUE);
}

HRESULT CPlayer::RenderMediaFile(CTBString szFileName, int * pnErr)
{
	HRESULT hr = Init();

	if (hr != S_OK)
		return hr;

	m_InputFile = szFileName;

	hr = BuildGraph(pnErr);

	if (m_pIBasicAudio){
		m_pIBasicAudio.Release();
		m_pIBasicAudio = NULL;
	}

	IEnumFilters * ppEnum = NULL;
	p->EnumFilters(&ppEnum);
	ULONG n = 0;
	IBaseFilter * filters = NULL;

	for (int iter = 0;iter < 100;iter++){
		hr = ppEnum->Next(1, &filters, &n);
		if ((n != 1) || (hr != S_OK))
			break;

		filters->QueryInterface(IID_IBasicAudio, (LPVOID*)&m_pIBasicAudio);
		filters->Release();

		if (m_pIBasicAudio)
			break; // we fount audio-renderer, because only it can get this interface
	}

	ppEnum->Release();

	hr = QueryInterface(&m_pIVideoWindow);
	if (m_pIVideoWindow == NULL)
		return S_OK;

	long x0 = 0, x1 = 0, y0 = 0, y1 = 0;
	m_pIVideoWindow->GetWindowPosition(&x0, &y0, &x1, &y1);
	m_pIVideoWindow->put_Visible(OAFALSE);
	m_mashtabX = x1;
	m_mashtabY = y1;

	return hr;
}

CTBString CPlayer::GetInput()
{ 
	return m_InputFile; 
}

HRESULT CPlayer::SetVolume(long iVolume)
{
	if (m_pIBasicAudio == NULL)
		return E_POINTER;

	if (iVolume < 0)
		iVolume = 0;

	if (iVolume > 10)
		iVolume = 10;

	return m_pIBasicAudio->put_Volume(-10000 + iVolume * 1000);
}

REFERENCE_TIME CPlayer::GetCurrentPos()
{
	LONGLONG llPos;

	m_pIMS->GetCurrentPosition(&llPos);	

	return llPos;
}

HRESULT CPlayer::AttachWindow(CWnd * wnd, CWnd * frame, int iDefaultHeight)
{
	if ((wnd == 0) || (wnd->GetSafeHwnd() == 0))
		return E_FAIL;

	long width = 0;
	HRESULT hr = m_pIVideoWindow->get_Height(&width); // Just check: Is window present
	if (hr != S_OK){
		CRect temp;
		wnd->GetWindowRect(&temp);
		temp.bottom = temp.top + iDefaultHeight;
		wnd->MoveWindow(&temp, TRUE);
		frame->MoveWindow(0,0,0,0); 
		return hr;
	}

	// Calculate mashtab
	CRect rect;
	wnd->GetWindowRect(&rect);
	double dMS = (double)m_mashtabX / (rect.right - rect.left - 15.0);

	// Calculate New image sizes
	long RealWidth  = rect.right - rect.left - 15;
	long RealHeight = (long)( m_mashtabY / dMS );

	// Zoom main window
	rect.bottom = rect.top + iDefaultHeight + RealHeight;
	wnd->MoveWindow(&rect);
	frame->MoveWindow(5, iDefaultHeight - 53, RealWidth, RealHeight);

	// and attach window
	m_pIVideoWindow->put_Owner((OAHWND)(frame->GetSafeHwnd()));
	m_pIVideoWindow->put_WindowStyle(WS_CHILD);// | WS_CLIPSIBLINGS);
	m_pIVideoWindow->SetWindowPosition(0, 0, RealWidth, RealHeight);
	m_pIVideoWindow->put_Visible(OATRUE);
	m_pIVideoWindow->SetWindowForeground(-1);
	return S_OK;
}

DWORD CPlayer::GetAvgFrameTime()
{
	return 0;

	for (int i = 0;i<100;i++){
		CFilterWrapper fw = CGraphManager::GetFilter(i);
		if (fw.PinsCount() == 1){
			CPinWrapper pw = fw.GetPin(GUID_NULL);
			if (pw.Info().dir == PINDIR_INPUT){
				if (pw.ConnectedMType().formattype != FORMAT_WaveFormatEx){
					VIDEOINFOHEADER2 *pVideoInfo = (VIDEOINFOHEADER2 *) pw.ConnectedMType().Format();
					int x = 0;
				}
			}
		}
	}

	return 0;
}

HRESULT CPlayer::BuildGraph(int * pnErr)
{
	CFilterWrapper pMSFileReader;
	CFilterWrapper pMSAVISpliter;
	HRESULT hr = S_OK;
	int nFileTipe = 1; // 0 == AVI, 1 == ASF
	*pnErr = 0; // it's ok.

	WCHAR wcstemp1[MAX_PATH] = {0};
	WCHAR wcstemp2[MAX_PATH] = {0};
	
	TCHAR tcsExt[_MAX_EXT] = {0};
	_tsplitpath(m_InputFile.data(),NULL,NULL,NULL,tcsExt);
	// Check, if file is MP3 or WAV, then just render it.
	if( !_tcsicmp(tcsExt, _T(".mp3")) || !_tcsicmp(tcsExt, _T(".wav")) )
	{
		return p->RenderFile( (m_InputFile.data()), NULL);
	}

	// ok, now we add to the graph 2 filters: Source and Spliter. 
	// Then we render all outgoing pins.
	
	hr = AddFilterSource(CLSID_WMAsfReader,L"WM ASF Reader", m_InputFile.data(),	&pMSAVISpliter);

	if (FAILED(hr)){
		nFileTipe = 0; // AVI
		hr = p->RemoveFilter(GetFilter(0)); // Remove filter
	}
	
	if (nFileTipe == 0){ // AVI
		hr = AddFilterSource(_T("Reader"),m_InputFile.data(), &pMSFileReader);

		hr = AddFilter(CLSID_AviSplitter, L"AVI Splitter", &pMSAVISpliter);
	}
	
	CPinWrapper pw1;
	CPinWrapper pw2;
	if (nFileTipe == 0){
		// Connect reader to the spliter
		pw1 = pMSFileReader.GetPin(PINDIR_OUTPUT);
		pw2 = pMSAVISpliter.GetPin(PINDIR_INPUT);

		hr = p->Connect(pw1, pw2);
		if (hr != 0)
			return hr;
	}

	// Renderer spliter
	int nPinsCount = pMSAVISpliter.PinsCount();
	if (nFileTipe == 0)
		nPinsCount--;

	for (int i = 0; i<nPinsCount; i++){
		pw2 = pMSAVISpliter.GetPin(PINDIR_OUTPUT, MEDIATYPE_NULL, FALSE);
		hr = p->Render(pw2);

		if (FAILED(hr)){
			CMediaType mt = pw2.GetDSMediaType(0);
			if (mt.majortype == MEDIATYPE_Audio){
				*pnErr += 1;
			}else{
				*pnErr += 2;
			}

			AddNullRenderer(pw2);
		}
	}

	return hr;
}

HRESULT CPlayer::AddNullRenderer(CPinWrapper pPinWrapper)
{
	HRESULT hr = S_OK;
	CFilterWrapper temp;

	WCHAR wcstemp1[MAX_PATH] = {0};
	hr = AddFilter(CLSID_NullRenderer, L"Null Renderer", &temp);

	hr = CGraphManager::ConnectOutPinWithFilter(pPinWrapper, temp, TRUE);

	return hr;
}















