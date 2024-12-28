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
// TrimmerDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Trimmer.h"
#include "TrimmerDlg.h"
#include "SettingsDialog.h"
#include "OutputFileNameDialog.h"
#include "hyperlink.h"
#include "SMM_SDKActionKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
	IDS_STRING_INDICATORS_STATUS,
	IDS_STRING_INDICATORS_FILENAME
};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CHyperlink m_ctlLink;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlLink.Create(NULL, _T(""), WS_CHILD, CRect(45,95,190,110), this, 9999);
	m_ctlLink.SetWindowText(_T("http://www.solveigmm.com"));
	m_ctlLink.SetLinkTarget(_T("http://www.solveigmm.com"));
    m_ctlLink.SetTextColour(0x00FF0000); // Bright Blue.
    m_ctlLink.SetActiveTextColour(0x000000ff); // Bright Red.
    m_ctlLink.AllowModsToFont();
	
    m_ctlLink.SetFontName(_T("Arial"));
    m_ctlLink.SetFontSize(15,0); // Width is best-fit.
	m_ctlLink.SetFontAttributes(HL_FONTNOTBOLD, 0);

	m_ctlLink.SetTextWrapping(FALSE);
	
	m_ctlLink.ShowWindow(SW_SHOWNORMAL);

	return TRUE;  
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTrimmerDlg dialog



CTrimmerDlg::CTrimmerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrimmerDlg::IDD, pParent),
	m_RegWork(),
	m_player()
{
	m_hIcon				  = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pModuleCfg		  = NULL;
	m_pITrimmerObjControl = NULL;
}

CTrimmerDlg::~CTrimmerDlg()
{
}

void CTrimmerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	DDX_Control(pDX, IDC_STOP_TIME, m_ctlStopTime);
	DDX_Control(pDX, IDC_START_TIME, m_ctlStartTime);
	DDX_Control(pDX, IDC_CURRENTPOS, m_ctlCurrentPos);
	DDX_Control(pDX, IDC_MAXLENGTH, m_ctlStreamLength);
	DDX_Control(pDX, IDC_EDIT_STEP, m_ctlStep);
	DDX_Control(pDX, IDC_VOLUME_SLIDER, m_ctlVolume);
	DDX_Control(pDX, IDC_STATIC_VIDEOWINDOW, m_ctlVideoWindow);
	DDX_Control(pDX, IDC_PROGRESS, m_ctlProgress);
}

BEGIN_MESSAGE_MAP(CTrimmerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_OPEN, OnOpenFile)
	ON_BN_CLICKED(ID_BUTTON_LEFTFLAG, SetLeftMarker)
	ON_BN_CLICKED(ID_BUTTON_RIGHTFLAG, SetRightMarker)
	ON_BN_CLICKED(ID_BUTTON_DELETE, RemoveSelecteon)
	ON_BN_CLICKED(ID_BUTTON_BACK, StepBack)
	ON_BN_CLICKED(ID_BUTTON_NEXT, StepNext)
	ON_BN_CLICKED(ID_BUTTON_TRIM, Trim)
	ON_BN_CLICKED(ID_BUTTON_PLAY, OnPlay)
	ON_BN_CLICKED(ID_BUTTON_STOP, OnStop)
	ON_BN_CLICKED(ID_BUTTON_PAUSE, OnPause)
	ON_BN_CLICKED(ID_BUTTON_SETTINGS, OutSettingsDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnNMReleasedcaptureSlider)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_VOLUME_SLIDER, OnNMReleasedcaptureVolumeSlider)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_STEP, OnEnChangeEditStep)
//	ON_WM_MOVING()
ON_WM_MOVE()
//ON_WM_VSCROLL()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()

// CTrimmerDlg message handlers

void CTrimmerDlg::ActivateBars()
{
    CRect rcClientStart;
    CRect rcClientNow;
    GetClientRect(rcClientStart);
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);
    CPoint ptOffset(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top);
    
    CRect rcChild;
    CWnd* pwndChild = GetWindow(GW_CHILD);
    while (pwndChild)
    {
        pwndChild->GetWindowRect(rcChild);
        ScreenToClient(rcChild);
        rcChild.OffsetRect(ptOffset);
        pwndChild->MoveWindow(rcChild, FALSE);
        pwndChild = pwndChild->GetNextWindow();
    }
    
    CRect rcWindow;
    GetWindowRect(rcWindow);
    rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
    rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
    MoveWindow(rcWindow, FALSE);    
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

void CTrimmerDlg::InitToolTips()
{
	m_ToolTips.Create(&m_ToolBar);

	CRect rect = CRect(0,0,0,0);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_OPEN, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Open Media File... (L)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_PLAY, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Play (X)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_PAUSE, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Pause (C)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_STOP, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Stop (V)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_BACK, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Back (Left arrow)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_NEXT, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Next (Right arrow)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_DELETE, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Erase selection (Q or Delete)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_LEFTFLAG, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Set left flag ([)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_RIGHTFLAG, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Set right flag (])"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_TRIM, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Start trimming (T)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().GetRect(ID_BUTTON_SETTINGS, &rect);
	m_ToolTips.AddTool(&m_ToolBar, _T("Settings (F11)"), &rect, ID_BUTTON_OPEN);

	m_ToolBar.GetToolBarCtrl().SetToolTips(&m_ToolTips);
}

BOOL CTrimmerDlg::ProcessCommandLine(CString * szFirstParam)
{
    LPWSTR *szArglist = NULL;
    int nArgs = 0;

	if (szFirstParam != NULL)
		*szFirstParam = "";

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (szArglist == NULL)
		return FALSE;

	if (nArgs > 1){
		if (szFirstParam != NULL)
			(*szFirstParam) = szArglist[1];

		return TRUE;
	}

	GlobalFree(szArglist);

	return FALSE;
}


BOOL CTrimmerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Check register
	bool bReseted = false;
	if ((m_RegWork.CheckKeys(&bReseted) != S_OK) || (bReseted)){
		MessageBox(_T("Warning: settings are brokened. Pleese, configure program."));
	}

	// Add ToolBar
	m_ToolBar.CreateEx(this, WS_CHILD | TBSTYLE_FLAT|WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY |  CBRS_FLYBY | CBRS_SIZE_DYNAMIC|CBRS_BORDER_BOTTOM);
	m_ToolBar.LoadToolBar(IDR_TOOLBAR1);

	// Add Status bar
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0, 10, SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo(1, 11, SBPS_STRETCH, 10);
	m_wndStatusBar.SetPaneText(0, _T("Starting..."));
	m_wndStatusBar.SetPaneText(1, _T("No file loaded"));

	ActivateBars();

	InitToolTips();

	// Init controls
	CString mask = _T("[0-2][0-9]:[0-5][0-9]:[0-5][0-9].[0-9][0-9]");
	m_ctlStartTime.SetMask(mask);
	m_ctlStopTime.SetMask(mask);

	TCHAR cStep[100] = {0};
	_itot(m_RegWork.GetStep(), cStep, 10);
	m_ctlStep.SetWindowText(cStep);

	m_ctlVolume.SetRange(0, 10, 1);
	m_ctlVolume.SetPageSize(1);
	m_ctlVolume.SetPos(10 - m_RegWork.GetVolume());

	m_Slider.EnableWindow(FALSE);
	m_Slider.SetRange(0, 100);

	m_StartInterval = -1;
	m_EndInterval   = -1;
	UpdateEditors();

	m_ctlCurrentPos.SetWindowText(_T("00:00:00.00"));
	m_ctlStreamLength.SetWindowText(_T("/   00:00:00.00"));

	EnableAllControls(FALSE);

	// Init used interfaces
	Init();

	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL)){
		m_wndStatusBar.SetPaneText(0, _T("Init failed. Re-install application."));
	}else{
		m_wndStatusBar.SetPaneText(0, _T("Ready"));
	}

	m_ctlVideoWindow.ModifyStyle(0, WS_CLIPCHILDREN);

	this->GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);

	::SetTimer(this->GetSafeHwnd(), 2, 100, NULL); // Process opening sended file...

	return TRUE; 
}

void CTrimmerDlg::Init()
{
	// Init COM-objects
	CoInitialize(NULL);

	HRESULT hr = S_OK;
	
	CComPtr<IClassFactory> pCF = NULL;
	hr = CoGetClassObject(CLSID_TrimmerObjControl, CLSCTX_INPROC, NULL, IID_IClassFactory, (void**) &pCF);
	if ( FAILED(hr) ) {
		MessageBox(_T("SolveigMM AVI Trimmer COM object has not been registered"));
		return;
	}

	CComPtr<IUnknown> pUnk = NULL;
    hr = pCF->CreateInstance( NULL, IID_IUnknown, (void**) &pUnk );

	hr = pUnk->QueryInterface(IID_ITrimmerObjControl, (void **)&m_pITrimmerObjControl);
	hr = pUnk->QueryInterface(IID_IModuleConfig, (LPVOID *) &m_pModuleCfg); 

}

CString CTrimmerDlg::ConvertLongTime2String(long lTime)
{
	char ch[20];
	
	int sec	    = lTime / 100;
	int hours   = sec / 3600;
	int minutes = (sec % 3600) / 60;
	int seconds = (sec % 3600) - minutes * 60;
	int msec    = lTime % 100;
	
	sprintf(ch, "%.2u:%.2u:%.2u.%.2u", hours, minutes, seconds, msec);
	
	CString cstart(ch);
	
	return cstart;
}

long CTrimmerDlg::ConvertString2LongTime(CString strTime)
{
	if( strTime.GetLength() < 8 ) {
		return 0;
	}

	int iHour	 = 0;
	int iMinute  = 0;
	int iSecond  = 0;
	int iMSecond = 0;

	if (strTime[2] == _T(':')){
		iHour	 = _ttoi( strTime.Mid(0, 2) );
		iMinute  = _ttoi( strTime.Mid(3, 5) );
		iSecond  = _ttoi( strTime.Mid(6, 8) );
		iMSecond = _ttoi( strTime.Mid(9, 11) );
	}else{
		iHour	 = _ttoi( strTime.Mid(0, 2) );
		iMinute  = _ttoi( strTime.Mid(2, 2) );
		iSecond  = _ttoi( strTime.Mid(4, 2) );
		iMSecond = _ttoi( strTime.Mid(6, 2) );
	}

	return (iHour * 360000 + iMinute * 6000 + iSecond * 100 + iMSecond);
}

void CTrimmerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrimmerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrimmerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrimmerDlg::ProcessOpenFile(CString szStartFileName)
{
	if ( m_pModuleCfg == NULL || m_pITrimmerObjControl == NULL )
		return;
	
	m_wndStatusBar.SetPaneText(0, _T("Opening file..."));

	if (szStartFileName.IsEmpty()){
		static TCHAR BASED_CODE szFilter[] = _T("Media Files (*.wma;*.mp3;*.wav)|*.wma;*.mp3;*.wav;|All files (*.*)|*.*||");
		
		CFileDialog OpenFDlg(TRUE, 
							NULL, 
							NULL, 
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, 
							szFilter, 
							this);	

		if(OpenFDlg.DoModal() == IDCANCEL) 
		{
			m_wndStatusBar.SetPaneText(0, _T("Ready"));
			return;
		}
	
		m_SourceFileName = OpenFDlg.GetPathName().GetBuffer(MAX_PATH);
	}else{
		m_SourceFileName = szStartFileName;
	}
	

	m_Slider.ClearSel(TRUE);

	VARIANT var;
	var.vt		= VT_BSTR;
	var.bstrVal = m_SourceFileName.AllocSysString();
	HRESULT hr	= m_pModuleCfg->SetValue( &SMAT_InputFile, &var);

	hr = m_pModuleCfg->GetValue( &SMAT_StreamLength, &var);
	if ( SUCCEEDED(hr ) )
	{
		m_StreamLength = (long)(var.dblVal*100);
		CString data = _T("/   ") + ConvertLongTime2String(m_StreamLength);
		m_ctlStopTime.SetData(_T(""));
		m_ctlStartTime.SetData(_T(""));
		m_ctlCurrentPos.SetWindowText(_T("00:00:00.00"));
		m_ctlStreamLength.SetWindowText(data);
		m_Slider.SetRange(0, m_StreamLength, 1);
		m_Slider.SetPageSize(0);
		m_Slider.SetLineSize(0);
		m_Slider.SetPos(0);

		m_StartInterval = -1;
		m_EndInterval   = -1;
		UpdateEditors();

		KillTimer(0);
		KillTimer(1);
	}else{
		m_wndStatusBar.SetPaneText(0, _T("Open failed. Ready"));
		m_player.Reset();
		EnableAllControls(FALSE);
		return;
	}

	EnableAllControls(TRUE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE, FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_TRIM, FALSE);
	
	int nErr = 0;
	m_player.RenderMediaFile(m_SourceFileName.GetBuffer(), &nErr);
	switch (nErr){
		case 0: break;
		case 1:
			MessageBox(_T("Cannot find audio decoder for preview, but trimming should be Ok"), _T("Warning"), MB_OK);
			break;
		case 2:
			MessageBox(_T("Cannot find video decoder for preview, but trimming should be Ok"), _T("Warning"), MB_OK);
			break;
		default:
			MessageBox(_T("Cannot find video or audio decoder for preview, but trimming should be Ok"), _T("Warning"), MB_OK);
			break;
	}
	m_player.AttachWindow(this, &m_ctlVideoWindow, 233);
	m_player.Pause();
	m_player.SetVolume(m_RegWork.GetVolume());

	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PLAY,		 TRUE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PAUSE,	 FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_STOP,		 FALSE);

	m_Slider.SetFocus();

	if ((m_SourceFileName[m_SourceFileName.GetLength() - 3] == 'm') &&
		(m_SourceFileName[m_SourceFileName.GetLength() - 2] == 'p') &&
		(m_SourceFileName[m_SourceFileName.GetLength() - 1] == '3'))
	{
			m_wndStatusBar.SetPaneText(0, _T("Ready"));
			m_wndStatusBar.SetPaneText(1, m_SourceFileName);
			return;
	}

	m_wndStatusBar.SetPaneText(0, _T("Ready"));
	m_wndStatusBar.SetPaneText(1, m_SourceFileName);
}

void CTrimmerDlg::OnOpenFile()
{
	ProcessOpenFile(_T(""));
}

void CTrimmerDlg::RemoveSelecteon()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;

	m_StartInterval = -1;
	m_EndInterval   = -1;
	m_Slider.ClearSel(1);
	UpdateEditors();
}

void CTrimmerDlg::StepNext()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;

	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Stepping..."));

	CString text;

	m_ctlStep.GetWindowText(text);

	long lCurPos = m_Slider.GetPos();

	lCurPos += _ttoi(text) * 100;
	if (lCurPos > m_StreamLength)
		lCurPos = m_StreamLength;

	m_Slider.SetPos(lCurPos);
	m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(lCurPos));

	m_player.SetPosition(lCurPos * UNITS / 100);

	m_wndStatusBar.SetPaneText(0, OldText);
}

void CTrimmerDlg::StepBack()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;

	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Stepping..."));

	CString text;

	m_ctlStep.GetWindowText(text);

	long lCurPos = m_Slider.GetPos();

	lCurPos -= _ttoi(text) * 100;
	if (lCurPos < 0)
		lCurPos = 0;

	m_Slider.SetPos(lCurPos);
	m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(lCurPos));

	m_player.SetPosition(lCurPos * UNITS / 100);

	m_wndStatusBar.SetPaneText(0, OldText);
}

void CTrimmerDlg::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;

	*pResult = 0;
	
	POINT pt;
	RECT Rect, Rect1;
	::GetCursorPos(&pt);
	::GetWindowRect(this->m_hWnd, &Rect1);
	this->m_Slider.GetChannelRect(&Rect);

	pt.x -= Rect1.left + 17;

	int tmp = (int)((double)(m_StreamLength)*((double)(pt.x) - 8)/((double)(Rect.right - Rect.left - 9)));
	if (tmp < 0)
		tmp = 0;
	if (tmp > m_StreamLength)
		tmp = m_StreamLength;

	this->m_Slider.SetPos(tmp);

	m_player.SetPosition(tmp * UNITS / 100);

	m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(tmp));
}

void CTrimmerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == TB_PAGEDOWN){
		if (::GetFocus() == m_Slider.GetSafeHwnd()){
//			StepNext();
			return;
		}

		if (::GetFocus() == m_ctlVolume.GetSafeHwnd()){
			ChangeVolume();
			return;
		}
	}

	if (nSBCode == TB_PAGEUP){
		if (::GetFocus() == m_Slider.GetSafeHwnd()){
//			StepBack();
			return;
		}

		if (::GetFocus() == m_ctlVolume.GetSafeHwnd()){
			ChangeVolume();
			return;
		}
	}

	if (nSBCode == TB_LINEDOWN){
		if (::GetFocus() == m_Slider.GetSafeHwnd()){
//			m_Slider.SetPos(m_Slider.GetPos()+1);
			return;
		}

		if (::GetFocus() == m_ctlVolume.GetSafeHwnd()){
			ChangeVolume();
			return;
		}
	}

	if (nSBCode == TB_LINEUP){
		if (::GetFocus() == m_Slider.GetSafeHwnd()){
//			m_Slider.SetPos(m_Slider.GetPos()-1);
			return;
		}

		if (::GetFocus() == m_ctlVolume.GetSafeHwnd()){
			ChangeVolume();
			return;
		}
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTrimmerDlg::ChangeVolume()
{
	HRESULT hr = m_player.SetVolume(10 - m_ctlVolume.GetPos());

	m_RegWork.SetVolume(10 - m_ctlVolume.GetPos());
}

void CTrimmerDlg::CorrectVolumeSliderPosition()
{
	POINT pt;
	RECT Rect, Rect1;
	::GetCursorPos(&pt);
	::GetWindowRect(this->m_hWnd, &Rect1);
	this->m_ctlVolume.GetChannelRect(&Rect);

	pt.y -= Rect1.top + 93;

	double tmp = ((10.0)*((double)(pt.y) - 0.0)/(58.0));
	if (tmp < 0)
		tmp = 0;
	if (tmp > 10)
		tmp = 10;

	this->m_ctlVolume.SetPos((int)(tmp + 0.5)); // we will round X.0 .. X.4 -> X; X.5 .. X.9 -> X+1

	ChangeVolume();
}

void CTrimmerDlg::OnNMReleasedcaptureVolumeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	CorrectVolumeSliderPosition();

	*pResult = 0;
}

CString CTrimmerDlg::Word2String(DWORD x, int max_characters)
{
	TCHAR rez[100] = {0};

	for (int i = 0; i<max_characters; i++){
		rez[max_characters - i - 1] = (TCHAR)(x % 10) + '0';
		x /= 10;
	}

	return rez;
}

CString CTrimmerDlg::GetOutputFileName()
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	CString rez;

	rez += Word2String(time.wYear, 2);
	rez += Word2String(time.wMonth, 2);
	rez += Word2String(time.wDay, 2);
	rez += Word2String(m_RegWork.GetComputerID(), 2);
	rez += Word2String(m_RegWork.GetNextNumber(), 3);

	m_RegWork.SetNextNumber();

	for (int i = m_SourceFileName.GetLength() - 4; i<m_SourceFileName.GetLength(); i++){
		rez += m_SourceFileName[i];
	}

	return rez;
}

void CTrimmerDlg::Trim()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;

	if (m_SourceFileName.IsEmpty())
		return;

	if ((m_StartInterval == -1) || (m_EndInterval == -1) || (m_StartInterval > m_EndInterval))
		return;

	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;

	ReadStartTimeFromEditor(TRUE);
	ReadStopTimeFromEditor(TRUE);

	m_wndStatusBar.SetPaneText(0, _T("Trimming..."));

	TrimInfoList trimlist;
	trimlist.nListSize = 1;
	trimlist.trim_list = new __tagTSTrimInfo;
	trimlist.trim_list[0].llStartPos = m_StartInterval * UNITS / 100;
	trimlist.trim_list[0].llStopPos  = m_EndInterval * UNITS / 100;
	trimlist.trim_list[0].nPieceNum = 0;

	VARIANT var;
	var.vt		= VT_BYREF | VT_UI1;
	var.pbVal	= (BYTE*)&trimlist;
	HRESULT hr	= m_pModuleCfg->SetValue(&SMAT_TrimList,&var);
    hr = m_pModuleCfg->CommitChanges(0);

	delete [] trimlist.trim_list;

	m_DestFileName = m_RegWork.GetOutPath() ;
	if ( ( m_DestFileName[m_DestFileName.GetLength() - 1] != '/' ) && 
		 ( m_DestFileName[m_DestFileName.GetLength() - 1] != '\\' ) )
	{
		m_DestFileName += '\\';
	}
	
	m_DestFileName += GetOutputFileName();
	
	var.vt		= VT_BSTR;
	var.bstrVal = m_DestFileName.AllocSysString();
	hr			= m_pModuleCfg->SetValue(&SMAT_OutputFile, &var);
	if( FAILED (hr) ){
		m_wndStatusBar.SetPaneText(0, _T("Trim failed at step #0. Ready"));
		return;
	}

	// Reset all flags
	var.lVal = 0;
	var.vt   = VT_UI4;
	hr = m_pModuleCfg->SetValue(&SMAT_Flags, &var);
	hr = m_pModuleCfg->CommitChanges(0);

	// And set our flags
	var.lVal = 0;
	var.vt	 = VT_UI4;
	if (m_RegWork.IsExtended() == TRUE)
		var.lVal |= SMM_TrimFlags_UsePositioning ;
	if (m_RegWork.IsLookAtSamplesTimes() == TRUE)
		var.lVal |= SMM_TrimFlags_ObeySampleTimes;

	hr = m_pModuleCfg->SetValue(&SMAT_Flags, &var);
	if( FAILED (hr) ){
		m_wndStatusBar.SetPaneText(0, _T("Trim failed at step #1. Ready"));
		return;
	}

	hr = m_pModuleCfg->CommitChanges(NULL);
	if( FAILED (hr) ){
		m_wndStatusBar.SetPaneText(0, _T("Trim failed at step #2. Ready"));
		return;
	}

	{
		var.vt = VT_BSTR;
		var.bstrVal = CString(g_ActionKey_Trimm_MP3_WMA_WAV).AllocSysString();
		hr= m_pModuleCfg->SetValue( &SMAT_ActionKey, &var );
		SysFreeString( var.bstrVal );
	}


	hr = m_pITrimmerObjControl->Start();
	if( FAILED (hr) ){
		m_wndStatusBar.SetPaneText(0, _T("Trim failed at step #3. Ready"));
		return;
	}

	::SetTimer(this->GetSafeHwnd(), 0, 100, NULL);

	EnableControlsOnStartStopTrim(TRUE);
	m_ctlProgress.SetRange32(0, 100);
	m_ctlProgress.SetPos(0);
}

void CTrimmerDlg::OutSettingsDialog()
{
	CSettingsDialog dialog;
	dialog.DoModal();
}

void CTrimmerDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 0) //progress dialog timer
	{  
		if (m_pModuleCfg)
		{
				VARIANT var;
				var.lVal = 0;
				HRESULT hr = m_pModuleCfg->GetValue( &SMAT_Progress, &var);

				if (hr != S_OK){
					OnStopTrim();
				}else{
					if (var.lVal < 100)
						m_ctlProgress.SetPos(var.lVal);
				}
		}
	}

	if (nIDEvent == 1){ // play timer
		long lPos = (long)(m_player.GetCurrentPos() * 100 / UNITS);
		if (lPos >= m_StreamLength){
			OnPause();
		}
		m_Slider.SetPos(lPos);
		m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(lPos));
	}

	if (nIDEvent == 2){ // Open sended file
		KillTimer(2);

		if (ProcessCommandLine(NULL) == TRUE){
			CString szTemp;
			ProcessCommandLine(&szTemp);
			ProcessOpenFile(szTemp);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CTrimmerDlg::EnableAllControls(BOOL bEnable)
{
	GetDlgItem(IDC_SLIDER)       ->EnableWindow(bEnable);
	GetDlgItem(IDC_VOLUME_SLIDER)->EnableWindow(bEnable);
	
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_LEFTFLAG,  bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_RIGHTFLAG, bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE,    bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_BACK,      bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_NEXT,		 bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_TRIM,		 bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PLAY,		 bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PAUSE,	 bEnable);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_STOP,		 bEnable);
}

void CTrimmerDlg::SetLeftMarker()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;
	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Setting marker..."));
	m_StartInterval = m_Slider.GetPos();

	UpdateSelection(true);
	m_wndStatusBar.SetPaneText(0, OldText);
}

void CTrimmerDlg::SetRightMarker()
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;
	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Setting marker..."));
	m_EndInterval = m_Slider.GetPos();

	UpdateSelection(false);
	m_wndStatusBar.SetPaneText(0, OldText);
}

void CTrimmerDlg::UpdateSelection(bool SetLeftFlag)
{
	if ((m_pModuleCfg == NULL) || (m_pITrimmerObjControl == NULL))
		return;
	if (m_SourceFileName.IsEmpty())
		return;

	if ((m_StartInterval > m_EndInterval) || (m_EndInterval == -1) || (m_StartInterval == -1)){
		if (SetLeftFlag){
			m_EndInterval = m_StreamLength;
		}else{
			m_StartInterval = 0;
		}
	}

	m_Slider.SetSelection(m_StartInterval, m_EndInterval);
	m_Slider.Invalidate();

	UpdateEditors();
}

void CTrimmerDlg::UpdateEditors()
{
	if (m_EndInterval == -1){
		m_ctlStopTime.SetWindowText(_T("00:00:00.00"));
		m_ctlStopTime.EnableWindow(FALSE);
	}else{
		m_ctlStopTime.SetWindowText(ConvertLongTime2String(m_EndInterval));
		m_ctlStopTime.EnableWindow(TRUE);
	}

	if (m_StartInterval == -1){
		m_ctlStartTime.SetWindowText(_T("00:00:00.00"));
		m_ctlStartTime.EnableWindow(FALSE);
	}else{
		m_ctlStartTime.SetWindowText(ConvertLongTime2String(m_StartInterval));
		m_ctlStartTime.EnableWindow(TRUE);
	}

	if ((m_ctlStartTime.IsWindowEnabled() == FALSE) ||
		(m_ctlStopTime.IsWindowEnabled() == FALSE)){
			m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE, FALSE);
			m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_TRIM,   FALSE);
		}else{
			m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE, TRUE);
			m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_TRIM,   TRUE);
		}
}
void CTrimmerDlg::ReadStopTimeFromEditor(BOOL bReadOnly)
{
	CString str;

	m_ctlStopTime.GetWindowText(str);
	long lCurPos = ConvertString2LongTime(str);
	if (lCurPos == m_EndInterval)
		return; // nothing changed

	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Setting marker..."));

	if (bReadOnly == FALSE)
		UpdateSelection(false);

	m_wndStatusBar.SetPaneText(0, OldText);
}

void CTrimmerDlg::ReadStartTimeFromEditor(BOOL bReadOnly)
{
	CString str;

	m_ctlStartTime.GetWindowText(str);
	long lCurPos = ConvertString2LongTime(str);
	if (lCurPos == m_StartInterval)
		return; // nothing changed

	CString OldText = m_wndStatusBar.GetPaneText(0);
	m_wndStatusBar.SetPaneText(0, _T("Setting marker..."));

	if (bReadOnly == FALSE)
		UpdateSelection(false);

	m_wndStatusBar.SetPaneText(0, OldText);
}

BOOL CTrimmerDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message){
		case WM_KEYDOWN:{
			if (pMsg->wParam == 13){ // Enter...
				if (::GetFocus() == GetDlgItem(IDC_START_TIME)->GetSafeHwnd()){ // ... on left editor
					ReadStartTimeFromEditor();
					
					// Position slider to the start interval's position
					m_Slider.SetPos(m_StartInterval);
					m_player.SetPosition(m_StartInterval * UNITS / 100);
					m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(m_StartInterval));

					return TRUE;
				}

				if (::GetFocus() == GetDlgItem(IDC_STOP_TIME)->GetSafeHwnd()){ // ... on reght editor
					ReadStopTimeFromEditor();

					// Position slider to the stop interval's position
					m_Slider.SetPos(m_EndInterval);
					m_player.SetPosition(m_EndInterval * UNITS / 100);
					m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(m_EndInterval));

					return TRUE;
				}

				// ... on another form: DON'T CLOSE DIALOG!!!
				return TRUE;
			}

			// **************************************
			// * --->  STARTED HOT-KEYS BLOCK  <--- *
			// **************************************
			if (pMsg->wParam == VK_UP){ // pressed UP key: low volume level
//				if ((::GetFocus() == this->GetSafeHwnd()) ||
//					(::GetFocus() == m_ctlVolume.GetSafeHwnd()) ||
//					(::GetFocus() == m_Slider.GetSafeHwnd())){
						if (m_SourceFileName.IsEmpty())
							return TRUE;
						m_ctlVolume.SetPos(m_ctlVolume.GetPos() - 1);
						ChangeVolume();
						return TRUE;
//					}
			}

			if (pMsg->wParam == VK_DOWN){ // pressed DOWN key: high volume level
//				if ((::GetFocus() == this->GetSafeHwnd()) ||
//					(::GetFocus() == m_ctlVolume.GetSafeHwnd()) ||
//					(::GetFocus() == m_Slider.GetSafeHwnd())){
						if (m_SourceFileName.IsEmpty())
							return TRUE;
						m_ctlVolume.SetPos(m_ctlVolume.GetPos() + 1);
						ChangeVolume();
						return TRUE;
//					}
			}

			if (pMsg->wParam == VK_LEFT){ // pressed LEFT key: one step left
				if ((::GetFocus() == m_Slider.GetSafeHwnd()) ||
					(::GetFocus() == m_ctlVolume.GetSafeHwnd())){
					if (m_SourceFileName.IsEmpty())
						return TRUE;
				
					StepBack();		
					return TRUE;
				}

				if (::GetFocus() == m_ctlVolume.GetSafeHwnd())
					return TRUE;
			}

			if (pMsg->wParam == VK_RIGHT){ // pressed RIGHT key: one step right
				if ((::GetFocus() == m_Slider.GetSafeHwnd()) ||
					(::GetFocus() == m_ctlVolume.GetSafeHwnd())){
					if (m_SourceFileName.IsEmpty())
						return TRUE;
				
					StepNext();		
					return TRUE;
				}
			}

			if (pMsg->wParam == 88){ // key <X>: Start playing
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PLAY) == FALSE)
					return TRUE;

				OnPlay();
				return TRUE;
			}

			if (pMsg->wParam == 67){ // key <C>: Pause playing
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PAUSE) == FALSE)
					return TRUE;

				OnPause();
				return TRUE;
			}

			if (pMsg->wParam == 86){ // key <V>: Stop playing
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_STOP) == FALSE)
					return TRUE;

				OnStop();
				return TRUE;
			}

			if (pMsg->wParam == 219){ // key <[>: Set left flag
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_LEFTFLAG) == FALSE)
					return TRUE;

				SetLeftMarker();
				return TRUE;
			}

			if (pMsg->wParam == 221){ // key <]>: Set right flag
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_RIGHTFLAG) == FALSE)
					return TRUE;

				SetRightMarker();
				return TRUE;
			}

			if (pMsg->wParam == 81){ // key <Q> : Delete selection
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_DELETE) == FALSE)
					return TRUE;

				RemoveSelecteon();
				return TRUE;
			}

			if (pMsg->wParam == 46){ // key <Delete> : Delete selection
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_DELETE) == FALSE)
					return TRUE;
				if ((::GetFocus() == m_ctlStopTime.GetSafeHwnd()) ||
					(::GetFocus() == m_ctlStartTime.GetSafeHwnd()) ||
					(::GetFocus() == m_ctlStep.GetSafeHwnd()))
					break;

				RemoveSelecteon();
				return TRUE;
			}

			if (pMsg->wParam == 84){ // key <T>: Start trimming
				if (m_SourceFileName.IsEmpty())
					return TRUE;
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_TRIM) == FALSE)
					return TRUE;

				Trim();
				return TRUE;
			}

			if (pMsg->wParam == 76){ // key <L>: Load (Open) media-file
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_OPEN) == FALSE)
					return TRUE;

				OnOpenFile();
				return TRUE;
			}

			if (pMsg->wParam == VK_F11){ // key <F11>: Settings
				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_SETTINGS) == FALSE)
					return TRUE;

				OutSettingsDialog();
				return TRUE;
			}

			if (pMsg->wParam == 32){ // key <Space>: Play/Pause
				if ((m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PLAY)  == FALSE) &&
					(m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PAUSE) == FALSE))
					return TRUE;

				if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PAUSE)  == FALSE){
					OnPlay();
					return TRUE;
				}

				OnPause();
				return TRUE;
			}

			// ***************************************
			// * --->  FINISHED HOT-KEYS BLOCK  <--- *
			// ***************************************
		};
		break;

		case WM_MOUSEWHEEL:{
			if (m_ctlVolume.IsWindowEnabled() == FALSE)
				return TRUE;

			int iDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
			int iNewPos = m_ctlVolume.GetPos();

			if (iDelta < 0)
				iNewPos++;
			if (iDelta > 0)
				iNewPos--;

			if (iNewPos > 10)
				iNewPos = 10;
			if (iNewPos < 0)
				iNewPos = 0;

			m_ctlVolume.SetPos(iNewPos);

			ChangeVolume();

			return TRUE;
		};
		break;

		case WM_LBUTTONDOWN:
		{
			if (pMsg->hwnd == m_ctlVolume.GetSafeHwnd()){
				CorrectVolumeSliderPosition();
//				return TRUE;
			}
		};
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CTrimmerDlg::OnPlay()
{
	::SetTimer(this->GetSafeHwnd(), 1, 10, NULL);
	m_player.Run();

	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PLAY,		 FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PAUSE,	 TRUE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_STOP,		 TRUE);
}

void CTrimmerDlg::OnStop()
{
	KillTimer(1);
	m_player.Stop();
	m_Slider.SetPos(0);
	m_player.SetPosition(0);
	m_ctlCurrentPos.SetWindowText(ConvertLongTime2String(0));
	m_player.Pause();

	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PLAY,		 TRUE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PAUSE,	 FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_STOP,		 FALSE);
}

void CTrimmerDlg::OnPause()
{
	KillTimer(1);
	m_player.Pause();

	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PLAY,		 TRUE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_PAUSE,	 FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_STOP,		 TRUE);
}

bool CTrimmerDlg::CorrectTime(REFERENCE_TIME * rtTime)
{
	long  Time1 = (long)(*rtTime * 100 / UNITS);
	double Time2 = ((double)*rtTime) * 100.0 / ((double)UNITS);

	Time2 -= Time1;

	if (Time2 > 0){
		*rtTime = (Time1 + 1) * UNITS / 100;
		return true;
	}

	return false;
}

void CTrimmerDlg::OnEnChangeEditStep()
{
	CString szStep;
	m_ctlStep.GetWindowText(szStep);
	m_RegWork.SetStep(_ttoi(szStep));
}

void CTrimmerDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	if (m_player.GetGraphState() == graphRunning)
		return;

	m_player.SetPosition(m_player.GetPosition()); // redraw window
}

BOOL CTrimmerDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;

    // Get the bounding rectangle for the movie screen
    m_ctlVideoWindow.GetWindowRect(&rc);
    ScreenToClient(&rc);

    // Exclude the clipping region occupied by our movie screen
    pDC->ExcludeClipRect(&rc);

	return CDialog::OnEraseBkgnd(pDC);
}

void CTrimmerDlg::OnBnClickedButtonCancel()
{
	m_pITrimmerObjControl->Stop();
	OnStopTrim();
}

void CTrimmerDlg::EnableControlsOnStartStopTrim(BOOL bStartTrim)
{
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_OPEN, !bStartTrim);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_TRIM, !bStartTrim);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_SETTINGS, !bStartTrim);

	this->GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(bStartTrim);
}

void CTrimmerDlg::OnStopTrim()
{
	if (m_DestFileName.IsEmpty())
		return;

	if (m_SourceFileName.IsEmpty())
		return;

	if (m_ToolBar.GetToolBarCtrl().IsButtonEnabled(ID_BUTTON_PAUSE) != FALSE)
		OnPause();

	KillTimer(0);

	m_ctlProgress.SetPos(0);

	EnableControlsOnStartStopTrim(FALSE);

	COutputFileNameDialog dialog;
	dialog.SetFileName(m_DestFileName);
	dialog.DoModal();

	m_wndStatusBar.SetPaneText(0, _T("Trim finished. Ready"));

	m_DestFileName = "";
}
