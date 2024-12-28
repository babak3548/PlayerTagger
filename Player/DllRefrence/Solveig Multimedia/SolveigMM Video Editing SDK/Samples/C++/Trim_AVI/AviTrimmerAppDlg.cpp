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
//
// AVITrimmerAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AVITrimmerAppDlg.h"
#include ".\avitrimmerappdlg.h"
#include <smm_utils.h>
#include "SMM_SDKActionKeys.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FILE_FILTER_TEXT  TEXT("Video Files (*.avi)\0*.avi\0")

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define WM_GRAPHNOTIFY WM_APP + 1  

#define SLIDER_POSITIONS 500

/////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
private:
	CStatic m_ctlVer;
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VER, m_ctlVer);	
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR szBuf[128] = {0};

	CString sVersion;

	TCHAR buf[]={_T("#1")};	// Only one VERSION_INFO present
	HRSRC hr= FindResource (NULL, buf, RT_VERSION); 
	if ( hr )
	{		
		HGLOBAL hg= LoadResource (NULL, hr);
		if ( hg )
		{
			BYTE *pByte=(BYTE*)LockResource (hg);
			if ( pByte )
			{
				VS_FIXEDFILEINFO *pVS=(VS_FIXEDFILEINFO*)(pByte+40);
				if ( pVS )
				{
					sVersion += _itot(HIWORD (pVS->dwFileVersionMS), szBuf, 10);
					sVersion += ".";
					sVersion += _itot(LOWORD (pVS->dwFileVersionMS), szBuf, 10);
					sVersion += ".";
					sVersion += _itot(HIWORD (pVS->dwFileVersionLS), szBuf, 10);
					sVersion += ".";
					sVersion += _itot(LOWORD (pVS->dwFileVersionLS), szBuf, 10);
				}
			}
		}
	}

	m_ctlVer.SetWindowText( "AVITrimmerApp Version " + sVersion );
	return TRUE;
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVITrimmerAppDlg dialog

CAVITrimmerAppDlg::CAVITrimmerAppDlg(CWnd* pParent /*=NULL*/): 
	CDialog(CAVITrimmerAppDlg::IDD, pParent)
	,m_nIsSelecting			      (  0     )
	,m_valCurTime			      ( _T("") )
	,m_sGraphAVStreamsNumbers     ( 0, 0   )
	,m_bWasSourceFileInCommandLine( false  )

{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pGraph			= NULL;
	m_pControl			= NULL;
	m_pMediaSeek		= NULL;
	m_pVideoWindow		= NULL;
	m_pTreeImages		= NULL;
	IsPlaying			= false;
	IsOpened			= false;
	IsStateSettingNow	= false;
	NoChange			= false;
	m_nIsSelecting		= 0;
	m_CurrntSplitterGUID= GUID_NULL;
}

void CAVITrimmerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVITrimmerAppDlg)
	DDX_Control(pDX, IDC_EDITFILEOUT,	m_ctlFileDst);
	DDX_Control(pDX, IDC_EDITFILEIN,	m_ctlFileSrc);
	DDX_Control(pDX, IDC_PROGRESS,		m_ctlProgress);
	DDX_Control(pDX, IDC_RUN,			m_RunButton);
	DDX_Control(pDX, IDC_STOP,			m_StopButton);
	DDX_Control(pDX, IDC_STOPTIME,		m_ctlStopTime);
	DDX_Control(pDX, IDC_STARTIME,		m_ctlStartTime);
	DDX_Control(pDX, IDC_CURTIME,		m_ctlCurTime);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_SLIDER1, m_slSeekPosition);
	DDX_Control(pDX, IDC_DIALOGIN, m_bDialogIn);
	DDX_Text(pDX,	 IDC_CURTIME, m_valCurTime);
	DDX_Control(pDX, IDC_STATIC_HYPERLINK, m_ctlHL);
	DDX_Control(pDX, IDC_LIST, m_ctlListBox);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_ctlAdd);
	DDX_Control(pDX, IDC_BUTTON_REM, m_ctlRemove);
	DDX_Control(pDX, IDC_CHANGE, m_ctlChange);
	DDX_Control(pDX, IDINVERT, m_ctlInvert);
	DDX_Control(pDX, IDC_DIALOGOUT, m_bDialogOut);
	DDX_Control(pDX, IDC_TREE_STREAMS, m_ctlTree);

	DDX_Control(pDX, IDC_CHECK_TRIM_OVERLAPPED, m_chbTrimOverlappedIntervals);
	DDX_Control(pDX, IDC_FRAME_ACCURACY, m_chbFrameAccuracy);
}

BEGIN_MESSAGE_MAP(CAVITrimmerAppDlg, CDialog)
	//{{AFX_MSG_MAP(CAVITrimmerAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DIALOGIN,		OnDialogIn)
	ON_BN_CLICKED(IDC_DIALOGOUT,	OnDialogOut)
	ON_BN_CLICKED(IDC_RUN,			OnRunGraph)
	ON_BN_CLICKED(IDC_STOP,			OnStopGraph)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED	( IDC_BUTTON_PLAY,	OnBnClickedPlayPreview)
	ON_BN_CLICKED	( IDC_BUTTON_STOP,	OnBnClickedStopPreview)
	ON_WM_SHOWWINDOW( )
	ON_BN_CLICKED	( IDC_BUTTON_PAUSE, OnBnClickedPreviewPause)
	ON_NOTIFY		( NM_RELEASEDCAPTURE, IDC_SLIDER1, OnNMReleasedCaptureSlider)
	ON_BN_CLICKED	( IDC_BUTTON_PLAYSELECTED,	OnBnClickedPlaySelected)
	ON_WM_HSCROLL	( )
	ON_BN_CLICKED	( IDC_BUTTON_LEFTTSEL, OnBnClickedSetSelectionStart)
	ON_BN_CLICKED	( IDC_BUTTON_RIGHTSEL,  OnBnClickedSetSelectionStop )
	ON_EN_CHANGE	( IDC_STARTIME, OnEnChangeStartime)
	ON_EN_CHANGE	( IDC_STOPTIME, OnEnChangeStoptime)
	ON_WM_ACTIVATE	( )
	ON_WM_MOVE		( )
	ON_BN_CLICKED	( IDC_BUTTON_ADD,	OnBnClickedAddPart)
	ON_LBN_SELCHANGE( IDC_LIST,			OnLbnSelChangeList)
	ON_LBN_DBLCLK	( IDC_LIST,			OnLbnDblclkList)
	ON_BN_CLICKED	( IDC_BUTTON_REM,	OnBnClickedDelPart)
	ON_WM_VKEYTOITEM( )
	ON_BN_CLICKED	( IDC_CHANGE,		OnBnClickedChange)
	ON_BN_CLICKED	( IDINVERT,			OnBnClickedInvert)
ON_NOTIFY(NM_CLICK, IDC_TREE_STREAMS, OnNMClickTreeStreams)
ON_BN_CLICKED(IDC_CHECK_TRIM_OVERLAPPED, OnBnClickedCheckTrimOverlapped)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVITrimmerAppDlg message handlers

BOOL CAVITrimmerAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CanChangePosition = true;

	ASSERT( (IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX );
	ASSERT( IDM_ABOUTBOX < 0xF000 );

	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if ( pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if ( !strAboutMenu.IsEmpty() ) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//
	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	//
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon

	CoInitialize(  NULL  );
	
	CComPtr<IClassFactory> pCF = NULL;
	HRESULT hr	= S_OK;
	
	hr = CoGetClassObject(CLSID_TrimmerObjControl, CLSCTX_INPROC, NULL, IID_IClassFactory, (void**) &pCF);
	if ( FAILED(hr) ) 
	{
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_EDIT_ENGINE_NOT_REGISTRED );
		ExitProcess(0);
		return FALSE;
	}
	
	CComPtr<IUnknown> pUnk = NULL;
    hr = pCF->CreateInstance( NULL, IID_IUnknown, (void**) &pUnk );
	
	if( SUCCEEDED( hr ) ){
		hr = pUnk->QueryInterface(IID_ITrimmerObjControl, (void **)&m_pITrimmerObjControl);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	
		hr = pUnk->QueryInterface( IID_IModuleConfig, (LPVOID *) &m_pModuleCfg); 
		if ( FAILED( hr ) )
			ProcessHRESULT(hr);
	
	m_ctlProgress.SetRange(0, 100);

	VARIANT var;
	var.pbVal = (BYTE *) &m_xCTrimmerObjControlCB;
	var.vt = VT_BYREF | VT_UI1;
	m_pModuleCfg->SetValue( &SMAT_Callback, &var);
	if( FAILED(hr) )
	{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_INVALID_PARAM_SMAT_CALLBACK, IDS_STR_MSG_CAPT_ERROR );
		return false;
	}

	EnableButton(TRUE);

	CString mask = "[0-2][0-9]:[0-5][0-9]:[0-5][0-9]:[0-9][0-9][0-9]";
	m_ctlStopTime.SetMask(mask);
	m_ctlStartTime.SetMask(mask);
	m_ctlCurTime.SetMask(mask);
	
	CString data ="000000000";
	m_ctlStopTime.SetData(data);
	m_ctlStartTime.SetData(data);
	m_ctlCurTime.SetData(data);

	RECT WindowRect = {NULL, NULL, NULL, NULL};
	GetClientRect(&WindowRect);		 	
	RECT ButRect = {WindowRect.left+29,	
		WindowRect.top + 230,
		WindowRect.left + 29+28,
		WindowRect.top + 250};
		
	LoadButtonBitmap( &m_bPlay,		IDC_BUTTON_PLAY, IDB_PL_UP, IDB_PL_DOWN, IDB_PL_DIS ); 
	LoadButtonBitmap( &m_bPause,	IDC_BUTTON_PAUSE, IDB_PAUSE2, IDB_PAUSE22, IDB_PAUSE23 ); 
	LoadButtonBitmap( &m_bStop,		IDC_BUTTON_STOP, IDB_STOP2, IDB_STOP22, IDB_STOP23 ); 
	LoadButtonBitmap( &m_bLeftSel,	IDC_BUTTON_LEFTTSEL, IDB_LEFTSEL2, IDB_LEFTSEL22, IDB_LEFTSEL23 ); 
	LoadButtonBitmap( &m_bRightSel, IDC_BUTTON_RIGHTSEL,IDB_RIGSEL2, IDB_RIGSEL22,IDB_RIGSEL23 ); 
	LoadButtonBitmap( &m_bPlaySelect, IDC_BUTTON_PLAYSELECTED, IDB_PLAYSELECTED2, IDB_PLAYSELECTED22, IDB_PLAYSELECTED23 ); 

	RECT rect;
	GetWindowRect(&rect);
	m_nNormalHeight = rect.bottom - rect.top;
	m_nNormalWidth  = rect.right - rect.left;

	CFont *pCurrFont = m_ctlHL.GetFont();
	LOGFONT lf = {0};
	if(pCurrFont)
	{
		pCurrFont->GetLogFont(&lf);
	}

	CRect   rctWindow;
	m_ctlHL.GetClientRect(&rctWindow);

	m_wndHL.Create(NULL,_T(""),WS_CHILD, rctWindow, &m_ctlHL, 9999);

	m_ctlHL.SetWindowText(_T(""));

	LPCTSTR c =  _T("http://www.solveigmm.com");
	LPCTSTR c1 = _T("Solveig Multimedia WEB-site");
	m_wndHL.SetWindowText(c1);
	m_wndHL.SetLinkTarget(c);
    m_wndHL.SetTextColour(0x00FF0000); // Bright Blue.
    m_wndHL.SetActiveTextColour(0x000000ff); // Bright Red.
    m_wndHL.AllowModsToFont();
	
    m_wndHL.SetFontName(lf.lfFaceName);
    m_wndHL.SetFontSize(lf.lfHeight,lf.lfWidth); // Width is best-fit.
	m_wndHL.SetFontAttributes(HL_FONTNOTBOLD, lf.lfItalic);

	m_wndHL.SetTextWrapping(FALSE);
	
	m_wndHL.ShowWindow(SW_SHOWNORMAL);

	ParseCommandLine();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAVITrimmerAppDlg::ParseCommandLine()
{

	LPWSTR  *szArglist;
	int     nArgs;
	
	USES_CONVERSION;
	LPTSTR st = GetCommandLine();
	szArglist = CommandLineToArgvW( T2W(st), &nArgs );
	if( szArglist == NULL )
		return;

	if( nArgs > 1 )
	{
		m_bWasSourceFileInCommandLine = true;
		m_strCommandLineSourceFile = szArglist[1];
	}
}

void CAVITrimmerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.
void CAVITrimmerAppDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int		i	= 0;
	float	x0	= 0, x1 = 0;
	float	n_mashtab	= 0;
	
	TCHAR str[100];

	RECT SeekRect;
	m_slSeekPosition.GetWindowRect( &SeekRect );
	ScreenToClient( &SeekRect );

	int RECT_X0 = SeekRect.left * 1.9;
	int RECT_X1 = RECT_X0  + SeekRect.right * 0.97 ; //649;
	int RECT_Y0 = SeekRect.bottom + 2;
	int RECT_Y1 = RECT_Y0 + 5;

	
	DWORD DeleteColor = RGB(176, 209, 250);
	DWORD SaveColor   = RGB(82, 156, 247);

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		// create and select a solid red and green brush
	    CBrush brushdel(DeleteColor);
	    CBrush brushsave(SaveColor);
		CBrush* pOldBrush = dc.SelectObject(&brushdel);

		// create and select a thick, black pen
		CPen pen1;
		pen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen1);
		
		// paint main rectangle (red color)
		dc.Rectangle(CRect(RECT_X0, RECT_Y0, RECT_X1, RECT_Y1));

		// select green brush
		dc.SelectObject(&brushsave);
		
		// Load pain list
		for (i = 0; i < m_ctlListBox.GetCount(); i++)
		{
			m_ctlListBox.GetText(i, str);

			// Get x0 and x1 from table
			// We HAVE TO use here <float> and </ ONE_SECOND>.
	
			x0 = (float)ConvertString2Time2(str) / (float)UNITS;
			x1 = (float)ConvertString2Time2( str + 15 ) / (float)UNITS;

			// calculate scale
			n_mashtab  = ( float )( RECT_X1 - RECT_X0 ); 
			n_mashtab /= ( ( (float)m_llStopPosition / (float)UNITS) - ( (float)m_llStartPosition / (float)UNITS ) );

            // recalculate x0 and x1 : now - coords of rectangle!!!
			x0 = RECT_X0 + x0*n_mashtab - 1;
			x1 = RECT_X0 + x1*n_mashtab - 1;

			// test for max and min values:
			if (x0 < RECT_X0)
				x0 = (float)RECT_X0;
			if (x1 < RECT_X0)
				x1 = (float)RECT_X0;
			if (x0 > RECT_X1) 
				x0 = (float)RECT_X1;
			if (x1 > RECT_X1)
				x1 = (float)RECT_X1;

			dc.Rectangle(CRect( int(x0), RECT_Y0, int(x1), RECT_Y1));
		}


		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);

		CDialog::OnPaint();
	}
}

//
// The system calls this to obtain the cursor to display while the user drags
// the minimized window.
//
HCURSOR CAVITrimmerAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CAVITrimmerAppDlg::IsVideoPin(IPin * pin)
{
	IEnumMediaTypes * pEnum;
	AM_MEDIA_TYPE * pmt[100];
	ULONG nn, i;
	bool isvideo = true;

	pin->EnumMediaTypes(&pEnum);
	pEnum->Next(100, pmt, &nn);
	i = nn;

	for ( nn--; ; nn-- )
	{
		if (pmt[nn]->formattype == FORMAT_WaveFormatEx){
			isvideo = false;
			break;
		}
		
		if (nn == 0)
			break;
	}

	for ( i--; ;i--){
		CoTaskMemFree(pmt[i]);
		if (i == 0)
			break;
	}

	pEnum->Release();

	return isvideo;
}

void CAVITrimmerAppDlg::ConnToNullRenderer(IPin * pin)
{
	HRESULT hr;
	IBaseFilter *m_pNullRenderer;
	IEnumPins * epins;
	IPin * pins[100];
	ULONG n;

	hr = CoCreateInstance( CLSID_NullRenderer, 0, CLSCTX_INPROC_SERVER,
						   IID_IBaseFilter, (LPVOID *) &m_pNullRenderer);

	hr = m_pGraph->AddFilter(m_pNullRenderer, L"Video Renderer");

	hr = m_pNullRenderer->EnumPins(&epins);
	hr = epins->Next(100, pins, &n);

	hr = m_pGraph->Connect(pin, pins[0]);

	epins->Release();
	m_pNullRenderer->Release();
	
	for ( n--; ;n-- ){
		pins[n]->Release();
		if (n == 0)
			break;
	}
}

HRESULT CAVITrimmerAppDlg::OpenMediaFile(LPCWSTR filename, int * res)
{
	HRESULT hr = S_OK;

	m_sGraphAVStreamsNumbers = AVStreamsNumbers(1,1);
	hr = CreateGraph( &m_sGraphAVStreamsNumbers );
	hr = AddStreamsInfoToCntlTree();

	return hr;
}

void CAVITrimmerAppDlg::FreeSourceFile()
{
	IBaseFilter * src;

	if (m_pGraph == NULL)
		return;

	m_pGraph->FindFilterByName(L"0001", &src);
	m_pGraph->RemoveFilter(src);
	src->Release();
}


void CAVITrimmerAppDlg::OnDialogIn() 
{
	UpdateData(TRUE);

	static TCHAR BASED_CODE szFilter[] = _T("Media Files (*.avi;*.asf;*.wmv)|*.avi;*.asf;*.wmv;|All Files (*.*)|*.*||");
	
	// Select source file
	CFileDialog OpenFDlg(TRUE, NULL, NULL 
		, OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT 
		| OFN_FILEMUSTEXIST
		, szFilter, this);
	
	if (OpenFDlg.DoModal() == IDCANCEL){
		RedrawWindow(0, 0, RDW_INVALIDATE);
		return;
	}
	OpenSourceFile( OpenFDlg.GetPathName() );
	
}
void CAVITrimmerAppDlg::OpenSourceFile( const CString &strFileSource )
{
	int n = 0;
	REFERENCE_TIME Val = 0;

	//if ok...
	//reset graph state
	KillTimer(IDT_MYTIMER);
	IsPlaying	= false;
	IsOpened	= false;
	m_slSeekPosition.ClearSel(TRUE);

	if ( m_pControl != NULL) 
		m_pControl->Stop();

	if (m_pVideoWindow != NULL)
		m_pVideoWindow->put_WindowState(SW_HIDE);

	FreeSourceFile();

	SAFE_RELEASE(m_pVideoWindow);
	SAFE_RELEASE(m_pControl);
	SAFE_RELEASE(m_pMediaSeek);
	SAFE_RELEASE(m_pGraph);

	// Some inits...
	RECT rec = {0};
	GetWindowRect(&rec);
	SetWindowPos(0, rec.left, rec.top, m_nNormalWidth, m_nNormalHeight, 0);

	m_strFileSource = strFileSource;

	m_ctlFileDst.SetWindowText(_T(""));

	BSTR bstrFN = strFileSource.AllocSysString();
	

	if ( m_pModuleCfg == NULL ) {
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_EDIT_ENGINE_NOT_REGISTRED );
		ExitProcess(0);
		return;
	}

	// send file name to the trim system...
	VARIANT var;
	var.vt = VT_BSTR;
	var.bstrVal = bstrFN;
	HRESULT hr	= m_pModuleCfg->SetValue( &SMAT_InputFile, &var);
	m_ctlFileSrc.SetWindowText( (LPCTSTR)strFileSource );
	UpdateData(FALSE);
	SysFreeString( bstrFN );
	
	m_pModuleCfg->GetValue(&SMAT_GetFileType, &var);
	if( var.intVal == SMM_File_Type_ASF )
	{
		m_chbFrameAccuracy.EnableWindow();
		m_chbFrameAccuracy.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chbFrameAccuracy.EnableWindow(FALSE);
		m_chbFrameAccuracy.SetCheck(BST_UNCHECKED);
	}


	// get size of movie
	hr = m_pModuleCfg->GetValue( &SMAT_StreamLength, &var);
	if ( SUCCEEDED(hr ) )
	{
		Val = REFERENCE_TIME(var.dblVal * UNITS);
		CString data =  Sec2Hours2(Val);
		m_ctlStopTime.SetData(data);
	}else{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_OPEN_VIDEO_FILE, IDS_STR_MGS_CAPT_WARNING );
		m_ctlFileSrc.SetWindowText( _T("") );
		return;
	}
	CString data = Sec2Hours(0);
	m_ctlStartTime.SetData(data);


	// Preview
	m_ctlTree.EnableWindow( true );
	n = 0;
	hr = OpenMediaFile(bstrFN, &n);
	switch (n){
		case 1:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_VIDEO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
		case 2:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_AUDIO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
		case 3:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_VIDEO_AUDIO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
	}

	if (FAILED(hr))
	{
		ProcessHRESULT(hr);
		IsOpened=false;
		RedrawWindow(0, 0, RDW_INVALIDATE);
		m_ctlFileSrc.SetWindowText((LPCTSTR)"");
		return;
	}

	// It's ok, file successful opened, process next
	IsOpened=true;
	m_nIsSelecting=false;

	// Some technical inits...
	FillTimes(Val);

	// set visual seekline size and current position
	m_slSeekPosition.SetRange(0, SLIDER_POSITIONS, 0);

	// some inits...
	CString mask = "[0-2][0-9]:[0-5][0-9]:[0-5][0-9]:[0-9][0-9][0-9]";
	m_ctlCurTime.SetMask(mask);

	CString d = Sec2Hours2(0);
	m_ctlCurTime.SetData(d);

	// finish init: reset listbox and so on....
	RECT rect;
	GetWindowRect(&rect);

	m_ctlListBox.ResetContent();
	m_ctlListBox.SetCurSel(0);
	RedrawWindow(0,0,RDW_INVALIDATE | RDW_UPDATENOW);
	m_ctlListBox.RedrawWindow(0, 0, 1|256|4);
	m_slSeekPosition.SetPageSize(1);
	m_slSeekPosition.SetLineSize(1);
	m_slSeekPosition.ClearSel(1);
	m_slSeekPosition.SetPos(0);

	m_pVideoWindow->put_Visible(OATRUE);
	m_pVideoWindow->put_AutoShow(OATRUE);

	m_pControl->Pause();

	RedrawWindow(0, 0, RDW_INVALIDATE);
	RedrawWindow(0, 0, RDW_INVALIDATE);

}

void CAVITrimmerAppDlg::OnDialogOut() 
{
	UpdateData( TRUE );

	CComVariant cvVar;
	HRESULT hr = m_pModuleCfg->GetValue(&SMAT_GetFileType, &cvVar);

	TCHAR csext[_MAX_EXT] = {0};
	_tsplitpath(m_strFileSource,NULL, NULL, NULL, csext); 
	CString csExt(csext);
	csExt.Delete(0);
	CString csFilter;
	csFilter.Format( _T("%s Files (*.%s)|*.%s;|All Files (*.*)|*.*||"), csExt, csExt, csExt);
	
	CFileDialog SaveFDlg(FALSE, csExt, _T("Noname")
		, OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT 
		| OFN_FILEMUSTEXIST
		, csFilter, this);
	
	if ( SaveFDlg.DoModal() == IDCANCEL ){
		RedrawWindow(0, 0, RDW_INVALIDATE);
		return;
	}
	
	CString strFN = SaveFDlg.GetPathName();
	m_ctlFileDst.SetWindowText((LPCTSTR)strFN);
	
	UpdateData(FALSE);
	RedrawWindow(0, 0, RDW_INVALIDATE);
}

HRESULT CAVITrimmerAppDlg::Start(void)
{
	UpdateData(FALSE);
	
	CString strFileSource;
	m_ctlFileSrc.GetWindowText(strFileSource);
	
    if ( !( strFileSource.GetLength() > 0) ) {
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return E_FAIL;
	}

	CString strFileDest;
	m_ctlFileDst.GetWindowText(strFileDest);
	if (!( strFileDest.GetLength() > 0 ) ) {

		OnDialogOut();
		m_ctlFileDst.GetWindowText(strFileDest);

		if (!( strFileDest.GetLength() > 0 ) ) {
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_DST_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
			return E_FAIL;
		}
	}

//
//  Set file source
//
	BSTR bstrFN = strFileSource.AllocSysString();
	VARIANT var;
	var.bstrVal = bstrFN;
	var.vt = VT_BSTR;
	HRESULT hr = m_pModuleCfg->SetValue( &SMAT_InputFile, &var);
	SysFreeString( bstrFN );
	if( FAILED (hr) ){
	TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
	return hr;
	}

//
//  Set File destination
//
	bstrFN = strFileDest.AllocSysString();
	var.bstrVal = bstrFN;
	var.vt = VT_BSTR;
	hr = m_pModuleCfg->SetValue(&SMAT_OutputFile, &var);
	SysFreeString( bstrFN );
	if( FAILED (hr) ){
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_DST_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return hr;
	}

	// start filling list of pieces
	// First - clear it.

	
	if (m_ctlListBox.GetCount() == 0){
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_ADD_VIDEO_FRAGMENT_TO_THE_LIST, IDS_STR_MSG_CAPT_ERROR );
		return E_FAIL;
	}

  	TrimInfoList Trim_List;
	Trim_List.nListSize = m_ctlListBox.GetCount();
	Trim_List.trim_list = new __TSTrimInfo[Trim_List.nListSize];
	
	
	for (int i = 0; i < m_ctlListBox.GetCount(); i++)
	{
		TCHAR str[100];
		m_ctlListBox.GetText(i, str);
		LPTSTR _ch_ = str;

		Trim_List.trim_list[i].nPieceNum	= i + 1;
		Trim_List.trim_list[i].llStartPos = ConvertString2Time2(_ch_);
		Trim_List.trim_list[i].llStopPos	= ConvertString2Time2(_ch_ + 15 );
	}
	
	var.pbVal = (BYTE*)&Trim_List;
	var.vt = VT_BYREF | VT_UI1;
	hr = m_pModuleCfg->SetValue(&SMAT_TrimList,&var);
    m_pModuleCfg->CommitChanges(0);
	
	delete[] Trim_List.trim_list;

	CComVariant cvVar;

	// Select streams to trim
	int iVideoStream   = GetVideoStreamNumber();
	int iAudioStream   = GetAudioStreamNumber();

	if( ( iVideoStream == 0 ) && ( iAudioStream == 0 ) )
	{
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_PLS_SEL_VIDEO_AUDIO_STRIEAM );
		return NULL;
	}

	cvVar = (LONG)iAudioStream;
	if ( FAILED (hr = m_pModuleCfg->SetValue(&SMAT_AudioStreamNumber, &cvVar) ) )
	{
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_AUDIO_STREAM_NUM );
		return hr;
	}

	cvVar = (LONG)iVideoStream;
	if ( FAILED( hr =m_pModuleCfg->SetValue(&SMAT_VideoStreamNumber, &cvVar) ) )  
	{
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_VIDEO_STREAM_NUM );
		return hr;
	}


	if( BST_CHECKED == m_chbTrimOverlappedIntervals.GetCheck() )
	{
		if ( FAILED( hr = m_pModuleCfg->GetValue(&SMAT_Flags, &cvVar) ) )  
		{
			ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_FLAGS );
			return hr;
		}

		cvVar.lVal |= SSM_TrimFlags_TrimOverlappedIntervals;
		if( FAILED( hr = m_pModuleCfg->SetValue(&SMAT_Flags, &cvVar) ) )
		{
			ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_FLAGS );
			return hr;
		}
	}

	cvVar.lVal = SMM_TrimmAccuracyType_GOP;
	if( m_chbFrameAccuracy.IsWindowEnabled() )
	{
		if( BST_CHECKED == m_chbFrameAccuracy.GetCheck() )
			cvVar.lVal = SMM_TrimmAccuracyType_Frame;
	}

	if( FAILED( hr = m_pModuleCfg->SetValue(&SMAT_TrimAccuracy, &cvVar) ) )
	{
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_SET_TRIM_MOD_PARAM_FLAGS );
		return hr;
	}

	{
		var.vt = VT_BSTR;
		var.bstrVal = CString(g_ActionKey_Trimm_AVI_ASF).AllocSysString();
		hr= m_pModuleCfg->SetValue( &SMAT_ActionKey, &var );
		SysFreeString( var.bstrVal );
	}

	m_pModuleCfg->CommitChanges(0);

	if ( FAILED( hr = m_pITrimmerObjControl->Start() ) ) {
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_TRIM_PROC_CANT_BE_STARTED, IDS_STR_MSG_CAPT_ERROR );
		return hr;
	}

	RedrawWindow( 0, 0, RDW_INVALIDATE );
	return hr;
}


void CAVITrimmerAppDlg::OnRunGraph() 
{

	if( m_pModuleCfg == NULL){
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_EDIT_ENGINE_NOT_REGISTRED );
		ExitProcess(0);
		return ;
	}

 	Start();	
}

void CAVITrimmerAppDlg::OnStopGraph() 
{
	if(!m_pITrimmerObjControl){
		ONEARG_MESSAGE_BOX( IDS_STR_MSG_EDIT_ENGINE_NOT_REGISTRED );
		ExitProcess(0);
		return;
	}
	
	m_pITrimmerObjControl->Stop();
	
	RedrawWindow(0, 0, RDW_INVALIDATE);
}


void CAVITrimmerAppDlg::ShowStatus()
{

   long lPos = 0;

   if(!m_pModuleCfg){
	   return;
   }
   
   VARIANT var;
   var.lVal = SMM_ProgressType_TimeBased ;
   HRESULT hr = m_pModuleCfg->GetValue( &SMAT_Progress, &var);
   lPos = var.lVal;

   if ( FAILED(hr) ) {
     m_ctlProgress.SetPos(0);
   }
	else {
		m_ctlProgress.SetPos( lPos );
	}
	
}

void CAVITrimmerAppDlg::ReopenVideoWindow()
{
	HRESULT hr = S_OK;
	long	n  = 0;
	
	IBaseFilter *Renderer = NULL;
	IPin		* pin1	  = NULL;
	IPin		* pin2	  = NULL;
	IEnumPins	*epins	  = NULL;
	
	PIN_INFO pi;
	FILTER_STATE fs;

	hr = m_pVideoWindow->get_WindowState(&n);
	if ( hr != 0 )
		return;

	if ( (n & SW_SHOW) == 0)
	{
		// Ok, user closed window. This is not good!!! Reopen it!
		m_pControl->GetState(10, (OAFilterState *)&fs); // Save current filter state
		if (fs == State_Running)
			m_pControl->Stop(); 

		// Find our renderer
		hr = m_pGraph->FindFilterByName(L"Video Renderer", (IBaseFilter **)&Renderer);
		if (hr != 0){
			KillTimer(IDT_PROGRESS);
			KillTimer(IDT_MYTIMER);
			ONEARG_MESSAGE_BOX( IDS_STR_MSG_CANT_REOPEN_VIDEO_WINDOW );
			return;
		}

		// Find filter, connected to the renderer.
		hr = Renderer->EnumPins(&epins);
		hr = epins->Next(1, &pin1, (ULONG *)&n);
		hr = pin1->ConnectedTo(&pin2);
		hr = pin2->QueryPinInfo(&pi);

		// Stop filters
		hr = Renderer->Stop();
		hr = pi.pFilter->Stop();

		// Reconnect filters
		hr = m_pGraph->Disconnect(pin1);
		hr = m_pGraph->Disconnect(pin2);
		hr = m_pGraph->Connect(pin2, pin1);

		// free used memory
		pin1->Release();
		pin2->Release();
		epins->Release();

		// and... GO!!!!!!!!!!!!!!!!!
		hr = m_pControl->Run();	
		if ( fs != State_Running)
		{
			hr = m_pControl->Stop();
			if (fs == State_Paused)
				hr = m_pControl->Pause(); // If we were paused before call - then pause now.
		}
	}
}

void CAVITrimmerAppDlg::OnTimer(UINT nIDEvent) 
{
	REFERENCE_TIME Now;

	FILTER_STATE fs;
	m_pControl->GetState(10, (OAFilterState *) &fs);
	if ((nIDEvent == IDT_MYTIMER) && (fs != State_Paused) && (IsStateSettingNow==false))
	{
		ReopenVideoWindow();

		m_pMediaSeek->GetCurrentPosition(&Now);

		CString data =  Sec2Hours2(Now);

		int Pos = (int)( double ( Now - m_llStartPosition ) / ( m_llStopPosition - m_llStartPosition )  * SLIDER_POSITIONS );
		if (!IsStateSettingNow){
			m_ctlCurTime.SetData(data);
			m_slSeekPosition.SetPos(Pos);
		}
	}
	else
		if (nIDEvent == IDT_PROGRESS) {
			ShowStatus();
		};
	
	CDialog::OnTimer(nIDEvent);
}

void CAVITrimmerAppDlg::EnableButton(BOOL bFlag)
{
	m_RunButton.EnableWindow		( bFlag );
	m_StopButton.EnableWindow		( !bFlag);
	m_ctlStartTime.EnableWindow		( bFlag );
	m_ctlStopTime.EnableWindow		( bFlag );
	m_slSeekPosition.EnableWindow	( bFlag );
	m_ctlAdd.EnableWindow			( bFlag );
	m_ctlRemove.EnableWindow		( bFlag );
	m_ctlChange.EnableWindow		( bFlag );
	m_ctlListBox.EnableWindow		( bFlag );
	m_ctlInvert.EnableWindow		( bFlag );
	m_bDialogIn.EnableWindow		( bFlag );
	m_bDialogOut.EnableWindow		( bFlag );
}


void CAVITrimmerAppDlg::OnCancel() 
{	
	if ( m_pModuleCfg ){
	  m_pModuleCfg.Release();
	  m_pModuleCfg = NULL;
	}

	CDialog::OnCancel();
}


//
// ITrimmerObjControlCB callback interface implementation
//
BEGIN_INTERFACE_MAP(CAVITrimmerAppDlg, CDialog)
INTERFACE_PART(CAVITrimmerAppDlg, IID_ITrimmerObjControlCB, CTrimmerObjControlCB)
END_INTERFACE_MAP()


STDMETHODIMP_(HRESULT) CAVITrimmerAppDlg::XCTrimmerObjControlCB::OnStop()
{ 
	METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	
	pThis->EnableButton(TRUE);
	return S_OK;
}

STDMETHODIMP_(HRESULT) CAVITrimmerAppDlg::XCTrimmerObjControlCB::OnStart()
{
	METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
    pThis->EnableButton(FALSE);
	
	pThis->m_uiTimerId = ::SetTimer (pThis->m_hWnd, IDT_PROGRESS, 10, 0);
	
    return S_OK;	
}

STDMETHODIMP_(HRESULT )CAVITrimmerAppDlg::XCTrimmerObjControlCB::OnPause()
{
	METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	
    return S_OK;	
}

STDMETHODIMP_(HRESULT )CAVITrimmerAppDlg::XCTrimmerObjControlCB::OnError (HRESULT hr, BSTR Val)
{
	METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	
	CString str = Val;
	TCHAR	szMsg[255];
	LoadString(	 GetModuleHandle( NULL )
				,IDS_STR_MSG_COM_OBJ_ERR
				,szMsg
				,255
				);

	pThis->MessageBox( str , szMsg);
	return S_OK;
}

STDMETHODIMP_(ULONG )CAVITrimmerAppDlg::XCTrimmerObjControlCB::AddRef()
{
    METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)CAVITrimmerAppDlg::XCTrimmerObjControlCB::Release()
{
    METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	return pThis->ExternalRelease();
}

STDMETHODIMP_(HRESULT)CAVITrimmerAppDlg::XCTrimmerObjControlCB::QueryInterface( REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CAVITrimmerAppDlg,CTrimmerObjControlCB);
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

void CAVITrimmerAppDlg::OnDestroy() 
{
	if( m_pTreeImages )
	{
		delete m_pTreeImages;
		m_pTreeImages = NULL;
	}
	SAFE_RELEASE(m_pControl);
	SAFE_RELEASE(m_pMediaSeek);
	SAFE_RELEASE(m_pVideoWindow);
	SAFE_RELEASE(m_pGraph);
	m_pModuleCfg.Release();
	m_pITrimmerObjControl.Release();
	CDialog::OnDestroy();
}

bool CAVITrimmerAppDlg::FillTimes(REFERENCE_TIME maxlen)
{
	m_llStopPosition    = maxlen;
	m_llStartPosition	= 0;
	m_llStartSelPos		= m_llStartPosition;
	m_llStopSelPos		= m_llStartPosition;
	//koef for converting slider units into seconds
	m_dSliderKoef		= (float)m_llStopPosition / SLIDER_POSITIONS; 
	return true;
}


void CAVITrimmerAppDlg::OnBnClickedPlayPreview()
{	
	if (IsOpened)
	{
		LONGLONG llCurPos;
		m_pMediaSeek->GetCurrentPosition(&llCurPos);
		FILTER_STATE fs;
		m_pControl->GetState(10,(OAFilterState*)&fs);
		if(fs != State_Paused)
			PlayPiece(m_llStartPosition,m_llStopPosition);
		else
			PlayPiece(llCurPos,m_llStopPosition);
	}
	else
		TWOARG_MESSAGE_BOX_ICON_ERROR( IDS_STR_MSG_FILE_ISNT_OPENED, IDS_STR_MSG_CAPT_ERROR );

	RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnBnClickedStopPreview()
{
	m_ctlTree.EnableWindow( true );
	if ( IsOpened )
	{
		ReopenVideoWindow();

		m_pMediaSeek->SetPositions((REFERENCE_TIME *)&m_llStartPosition, AM_SEEKING_AbsolutePositioning,
		0,AM_SEEKING_NoPositioning);
		m_pControl->StopWhenReady();
		m_pControl->Pause();
		IsPlaying		= false;
		m_nIsSelecting	= 0;
		m_slSeekPosition.SetPos(0);
	}
	else
		TWOARG_MESSAGE_BOX_ICON_ERROR( IDS_STR_MSG_FILE_ISNT_OPENED, IDS_STR_MSG_CAPT_ERROR );

	RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//Show playback controls (resizing dialog window)
	RECT rect;
	GetWindowRect(&rect);
	int q = 0;
	if ( IsOpened )
		q = 70;
	
	SetWindowPos(0, 10, 10, m_nNormalWidth, m_nNormalHeight + q, SWP_SHOWWINDOW);

	//init playback slider
	if( m_bWasSourceFileInCommandLine )
		OpenSourceFile( m_strCommandLineSourceFile );
}

void CAVITrimmerAppDlg::OnBnClickedPreviewPause()
{
	if (IsOpened)
	{
		ReopenVideoWindow();

		m_nIsSelecting = 0;
		FILTER_STATE fs;
		m_pControl->GetState(10,(OAFilterState*)&fs);
		if (IsPlaying)
		{
			if (fs == State_Paused)
				m_pControl->Run();
			if (fs == State_Running)
				m_pControl->Pause();
		}
	}
	else 
		TWOARG_MESSAGE_BOX_ICON_ERROR( IDS_STR_MSG_FILE_ISNT_OPENED, IDS_STR_MSG_CAPT_ERROR );

	RedrawWindow(0, 0, RDW_INVALIDATE);
}
	
void CAVITrimmerAppDlg::OnNMReleasedCaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	IsStateSettingNow = true;

	if ( IsOpened == false ) {
		m_slSeekPosition.SetPos(0);
		m_slSeekPosition.ClearSel(TRUE);
		return;
	}

	ReopenVideoWindow();

	if (IsPlaying){
		// Stop playing...
		KillTimer(IDT_MYTIMER);
		Sleep(100); // Wait, while playing is stop.
	}

	int SliderPosition =  m_slSeekPosition.GetPos();
	if ( m_nIsSelecting != 0 )
	{
		REFERENCE_TIME dNew = (REFERENCE_TIME )(SliderPosition * m_dSliderKoef);

		//if Shift pressed
		if (m_nIsSelecting == 1)
			SetSelection(m_llStartSelPos, dNew, false);
		
		//if Ctrl pressed
 		if (m_nIsSelecting == -1) 
			SetSelection(dNew, m_llStopSelPos, true);
	}

	//Setting play position
	double dPercent = (double)SliderPosition / (double)SLIDER_POSITIONS;
	REFERENCE_TIME llCurPosition = (REFERENCE_TIME )( m_llStartPosition + ( m_llStopPosition - m_llStartPosition) * dPercent );

	m_pMediaSeek->SetPositions( &llCurPosition, 
								AM_SEEKING_AbsolutePositioning,
								&m_llStopPosition, 
								AM_SEEKING_AbsolutePositioning);

	 m_slSeekPosition.SetPos(SliderPosition);
	
	CString q = Sec2Hours2(llCurPosition);
	 m_ctlCurTime.SetData(q);

	 SetActiveWindow();

	if (IsPlaying){
		// Continue playing...
		SetTimer(IDT_MYTIMER, 1000, NULL);
	}
	IsStateSettingNow = false;
}

BOOL CAVITrimmerAppDlg::PreTranslateMessage(MSG* pMsg)
{
	//Left Ctrl pressed
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->lParam == 1900545)) 
		m_nIsSelecting = -1;
	
	//Left Shift pressed
	if ((pMsg->message == WM_KEYDOWN)&&(pMsg->lParam == 2752513))
		m_nIsSelecting = 1;
	
	//Left Ctrl or Shift released
	if (((pMsg->message == WM_KEYUP) && (pMsg->lParam == -1071841279))	||
		((pMsg->message == WM_KEYUP) && (pMsg->lParam == -1070989311)))
		m_nIsSelecting = 0;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CAVITrimmerAppDlg::OnBnClickedPlaySelected()
{
	if (IsOpened)
	{
		CString NewTime = Sec2Hours2(m_llStartSelPos);
		m_ctlCurTime.SetData(NewTime);

		PlayPiece(m_llStartSelPos, m_llStopSelPos);
	}
	else
		TWOARG_MESSAGE_BOX_ICON_ERROR( IDS_STR_MSG_FILE_ISNT_OPENED, IDS_STR_MSG_CAPT_ERROR );

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::PlayPiece(LONGLONG llStartP,LONGLONG llStopP)
{	
	AVStreamsNumbers NullStreams( 0, 0 );
	if( m_sGraphAVStreamsNumbers == NullStreams )
	{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_SEL_VIDEO_AUDIO_STREAM_TO_BE_PLAYED, IDS_STR_MGS_CAPT_WARNING );
		return;
	}

	AVStreamsNumbers CurAVStreamsNumbers( GetAVStreamsNumbers() );
	if( m_sGraphAVStreamsNumbers != CurAVStreamsNumbers )
	{
		m_sGraphAVStreamsNumbers = CurAVStreamsNumbers;
		HRESULT hr = ReCreateGraph( &m_sGraphAVStreamsNumbers );
		if ( hr != S_OK )
		{
			return;
		}
	}
	m_ctlTree.EnableWindow( false );

	// Timer for slider's moving 
	SetTimer(IDT_MYTIMER, 1000, NULL);

	//Set start/stop positions
	int nPos = int( (REFERENCE_TIME)(llStartP / m_dSliderKoef) );
	m_slSeekPosition.SetPos( nPos );
	m_pMediaSeek->SetPositions((REFERENCE_TIME *)&llStartP, AM_SEEKING_AbsolutePositioning,
		(REFERENCE_TIME *)&llStopP, AM_SEEKING_AbsolutePositioning);

	//start playing
	m_pControl->Run();
	
	IsPlaying		= true;
	m_nIsSelecting	= 0;
	
	RedrawWindow(0, 0, RDW_INVALIDATE);
}
void CAVITrimmerAppDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((nSBCode == TB_PAGEDOWN) || (nSBCode == TB_PAGEUP)){
		//geting mouse position and slider position
		POINT pt;
		RECT Rect, Rect1;
		::GetCursorPos(&pt);
		::GetWindowRect( m_hWnd, &Rect1);

		pt.x -= Rect1.left;
	
		 m_slSeekPosition.GetChannelRect(&Rect);
		int tmp = int( ( double ) SLIDER_POSITIONS * ( ( double )( pt.x ) - 15 ) / ( ( double )( Rect.right-Rect.left ) ) );
		 m_slSeekPosition.SetPos(tmp);
	}

	if (nSBCode == TB_LINEDOWN)
		m_slSeekPosition.SetPos( m_slSeekPosition.GetPos() + 1 );
	
	if (nSBCode == TB_LINEUP)
		m_slSeekPosition.SetPos( m_slSeekPosition.GetPos() - 1 );

	if ( ( nSBCode == TB_LINEDOWN ) || ( nSBCode == TB_LINEUP ) )
		OnNMReleasedCaptureSlider(NULL, NULL);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAVITrimmerAppDlg::OnBnClickedSetSelectionStart()
{
	CString data;

	if ( IsOpened == false ) {
		 m_slSeekPosition.SetPos(0);
		return;
	}

	ReopenVideoWindow();

	REFERENCE_TIME llNewPos;
	m_pMediaSeek->GetPositions(&llNewPos,0);
	// start point before end point??
	if (llNewPos <= m_llStopSelPos){
		SetSelection(llNewPos, m_llStopSelPos, true); // No - mark area
	}else{
		//  Ok, reset end point, new end point - finish of the slide
		data = Sec2Hours2(m_llStopPosition);
		
		CanChangePosition = false;
		m_ctlStopTime.SetData(data);
		SetSelection(llNewPos, m_llStopPosition, true);
		CanChangePosition = true;
	};

	int nPos = int( (REFERENCE_TIME)(m_llStartSelPos / m_dSliderKoef) ); 
	m_slSeekPosition.SetPos( nPos );

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnBnClickedSetSelectionStop()
{
	CString data;

	if ( IsOpened == false ) {
		 m_slSeekPosition.SetPos(0);
		return;
	}

	ReopenVideoWindow();

	REFERENCE_TIME llNewPos;
	m_pMediaSeek->GetPositions(&llNewPos,0);
	// start point before end point??
	if (llNewPos >= m_llStartSelPos)
	{
		SetSelection(m_llStartSelPos, llNewPos, false);

		int nPos = int( (REFERENCE_TIME)(m_llStopSelPos / m_dSliderKoef) ); 
		m_slSeekPosition.SetPos( nPos );
	}
	else
	{
		// Ok, reset start point, new start point - start of the slide
		data = Sec2Hours2(m_llStartPosition);
		CanChangePosition = false;
		m_ctlStartTime.SetData(data);
		m_ctlStopTime.SetData(Sec2Hours2(llNewPos));
		SetSelection(m_llStartPosition, llNewPos, true);
		CanChangePosition = true;

		int nPos = int( (REFERENCE_TIME)(llNewPos  / m_dSliderKoef) );  
		m_slSeekPosition.SetPos( nPos );
	}

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::SetSelection(REFERENCE_TIME llStart, REFERENCE_TIME llStop, bool IsStart)
{
	if (llStart > llStop){
		MessageBeep(-1);
		return;
	}
	m_llStartSelPos = llStart;
	m_llStopSelPos  = llStop;

		if ( IsStart ) {
			NoChange = true;
			CString NewTime = Sec2Hours2(m_llStartSelPos);
			m_ctlStartTime.SetData(NewTime);
		}
		else {
			NoChange = true;
			CString NewTime = Sec2Hours2(m_llStopSelPos);
			m_ctlStopTime.SetData(NewTime);
		}

	RedrawWindow(0, 0, RDW_INVALIDATE);
	m_slSeekPosition.RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnEnChangeStartime()
{
	if ( IsOpened )
	{
		if ( !NoChange )
		{
			CString str			= m_ctlStartTime.GetData();
			if (str.IsEmpty())
				return;
			
			m_llStartSelPos		= ConvertString2Time(str);
			str					= m_ctlStopTime.GetData();
			
			if ( str.IsEmpty() )
				return;
			
			m_llStopSelPos		= ConvertString2Time(str);
			
			int nMin = int( (REFERENCE_TIME)(m_llStartSelPos  / m_dSliderKoef) );  
			int nMax = int( (REFERENCE_TIME)(m_llStopSelPos  / m_dSliderKoef) );  
			m_slSeekPosition.SetSelection( nMin , nMax);

			m_slSeekPosition.RedrawWindow(0, 0, RDW_INVALIDATE);
			if (CanChangePosition){
				int nPos = int( (REFERENCE_TIME)(m_llStartSelPos / m_dSliderKoef) );
				m_slSeekPosition.SetPos( nPos );
			}
		}

		m_nIsSelecting = 0;
		m_pMediaSeek->SetPositions((REFERENCE_TIME *)&(m_llStartSelPos), AM_SEEKING_AbsolutePositioning,
			(REFERENCE_TIME *)&m_llStopPosition, AM_SEEKING_AbsolutePositioning);
		CString NewTime = Sec2Hours2(m_llStartSelPos);
		m_ctlCurTime.SetData(NewTime);
		NoChange = false;

	}
	
	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnEnChangeStoptime()
{
	if ( IsOpened )
	{
		if ( !NoChange )
		{
			CString str			= m_ctlStartTime.GetData();
			if (str.IsEmpty())
				return;
			
			m_llStartSelPos		= ConvertString2Time(str);
			str					= m_ctlStopTime.GetData();
			if (str.IsEmpty())
				return;
			
			m_llStopSelPos		= ConvertString2Time(str);
			
			int nMin = int( (REFERENCE_TIME)(m_llStartSelPos  / m_dSliderKoef) );  
			int nMax = int( (REFERENCE_TIME)(m_llStopSelPos  / m_dSliderKoef) );  

			m_slSeekPosition.SetSelection( nMin , nMax );
			m_slSeekPosition.RedrawWindow(0, 0, RDW_INVALIDATE);
			if (CanChangePosition){
				int nPos = int( (REFERENCE_TIME)(m_llStopSelPos / m_dSliderKoef) );
				m_slSeekPosition.SetPos( nPos );
			}
		}

		m_nIsSelecting = 0;
		m_pMediaSeek->SetPositions((REFERENCE_TIME *)&(m_llStopSelPos), AM_SEEKING_AbsolutePositioning,
			(REFERENCE_TIME *)&m_llStopPosition, AM_SEEKING_AbsolutePositioning);
		CString NewTime = Sec2Hours2(m_llStopSelPos);
		m_ctlCurTime.SetData(NewTime);

		NoChange = false;
	}

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
}


void CAVITrimmerAppDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
}


void CAVITrimmerAppDlg::OnBnClickedAddPart()
{
	LONGLONG llistT0[100];
	LONGLONG llistT1[100];
	LONGLONG lnewlistT0[100];
	LONGLONG lnewlistT1[100];
	int nlistlen, i, i1;
	TCHAR str[100];
	__TSTrimInfo TInew;
	TCHAR buf[100];
	bool added;

	if ( IsOpened )
	{
		if (m_llStartSelPos >= m_llStopSelPos)
		{
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_SEL_FRAGMENT_FIRST, IDS_STR_MSG_CAPT_ERROR );
			return;
		}

		// get current task list
		nlistlen = m_ctlListBox.GetCount();
		for (i = 0; i < nlistlen; i++)
		{
			m_ctlListBox.GetText(i, str);

			// Get T0 and T1 from table
			llistT0[i] = ConvertString2Time2( str		);
			llistT1[i] = ConvertString2Time2( str + 15	);

			llistT0[i] = ConvertString2Time2(Sec2Hours2(llistT0[i]));
			llistT1[i] = ConvertString2Time2(Sec2Hours2(llistT1[i]));
		}

		// Ok, now we have intervals. Start analyze.
		
		added = false;
	
		if( BST_UNCHECKED == m_chbTrimOverlappedIntervals.GetCheck() )
		{

			for (i = 0, i1 = 0; i < nlistlen; i++)
			{
				// First: We have to add new interval or not????
				if ((m_llStartSelPos >= llistT0[i]) &&
					(m_llStopSelPos  <= llistT1[i]))
					return; // We too small.

				if (m_llStartSelPos > llistT1[i]){
					// this interval stay BEFORE us.
					lnewlistT0[i1] = llistT0[i];	// Save it.
					lnewlistT1[i1] = llistT1[i];
					i1++;
					continue;	
				}

				if (m_llStopSelPos < llistT0[i]){
					// this interval stay AFTER us.
					lnewlistT0[i1] = llistT0[i];	// Save it.
					lnewlistT1[i1] = llistT1[i];
					i1++;
					continue;	
				}

				if ((m_llStartSelPos < llistT0[i]) &&
					(m_llStopSelPos  > llistT1[i]))
					continue; // This interval is not need more.

				// Continue analise.
				if ((m_llStartSelPos <= llistT0[i]) &&
					(m_llStopSelPos  > llistT0[i]) &&
					(m_llStopSelPos  < llistT1[i])){
						// ok, move RIGHT border
						m_llStopSelPos = llistT1[i];
						continue;
					}

					if ((m_llStartSelPos > llistT0[i]) &&
						(m_llStartSelPos < llistT1[i]) &&
						(m_llStopSelPos  >= llistT1[i])){
							// ok, move RIGHT border
							m_llStartSelPos = llistT0[i];
							continue;
						}

						if (m_llStartSelPos == llistT1[i]){
							// ok, move RIGHT border
							m_llStartSelPos = llistT0[i];
							continue;
						}

						if (m_llStopSelPos == llistT0[i]){
							// ok, move RIGHT border
							m_llStopSelPos = llistT1[i];
							continue;
						}
			}

			if ( !added ){
				// It's ok, we can simply add this interval
				lnewlistT0[i1] = m_llStartSelPos;
				lnewlistT1[i1] = m_llStopSelPos;
				i1++;
			}
		}
		else
		{
			for (i = 0, i1 = 0; i < nlistlen; i++)
			{
				lnewlistT0[i] = llistT0[i];
				lnewlistT1[i] = llistT1[i];
			}
			lnewlistT0[nlistlen]	= m_llStartSelPos;
			lnewlistT1[nlistlen]	= m_llStopSelPos;
			i1						= nlistlen + 1;

		}

		// finished. Now fill list with new values. It, probably, was changed.
		m_ctlListBox.ResetContent();
		for ( i = 0; i < i1; i++ )
		{
			TInew.llStartPos = lnewlistT0[i];
			TInew.llStopPos  = lnewlistT1[i];

			TInew.llStartPos = ConvertString2Time2( Sec2Hours2( TInew.llStartPos ) );
			TInew.llStopPos  = ConvertString2Time2( Sec2Hours2( TInew.llStopPos ) );

			if ( TInew.llStartPos <= TInew.llStopPos ){
				ConvertTime2String(TInew, buf);
				ListBox_AddString((HWND)m_ctlListBox,buf);
			}
		}
		m_ctlListBox.SetSel(m_ctlListBox.GetCount(), TRUE);
	}else{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return;
	}

	int nMin = int( (REFERENCE_TIME)(m_llStartSelPos  / m_dSliderKoef) );  
	int nMax = int( (REFERENCE_TIME)(m_llStopSelPos  / m_dSliderKoef) );  

	m_slSeekPosition.SetSelection( nMin , nMax );

	RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnLbnSelChangeList()
{
	//Getting current string in ListBox
	int nCount = m_ctlListBox.GetSelCount();
	int indexes[100];
	m_ctlListBox.GetSelItems (100, indexes);
	int iSel = indexes[nCount - 1];

	__TSTrimInfo trim = {0};
		
	//Converting string into times
	TCHAR str[100];
	m_ctlListBox.GetText(iSel, str);
	LPTSTR _ch_ = str;
	trim.nPieceNum	= 0;
	trim.llStartPos = ConvertString2Time2(_ch_);
	trim.llStopPos	= ConvertString2Time2(_ch_ + 15 );

	//Seting Stop time
	m_llStopSelPos = trim.llStopPos;
	NoChange = true;
	CString data = Sec2Hours2(m_llStopSelPos);
	
	//Seting start time
	m_llStartSelPos = trim.llStartPos;
	data = Sec2Hours2(m_llStartSelPos);
	NoChange = true;
	CString curtime = data;

	//Cur time

	CanChangePosition = false;
	m_ctlStopTime.SetData(_ch_ + 15);
	CanChangePosition = true;
	m_ctlStartTime.SetData(_ch_);
	m_ctlCurTime.SetData(_ch_);
	

	//seting play position
	m_pMediaSeek->SetPositions(&m_llStartSelPos, AM_SEEKING_AbsolutePositioning, &m_llStopSelPos,
							   AM_SEEKING_AbsolutePositioning);

	// Reopen video window, if need
	ReopenVideoWindow();
}

void CAVITrimmerAppDlg::OnLbnDblclkList()
{
}

void CAVITrimmerAppDlg::OnBnClickedDelPart()
{
	if (!IsOpened){
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return;
	}

	int nCount = m_ctlListBox.GetSelCount();
	if (nCount == 0){
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_CHOSE_FRAGMENT_FROM_LIST_FIRST, IDS_STR_MSG_CAPT_ERROR );
		return;
	}

	for (int i = 0; i < nCount; i++)
	{
		int indexes[100];
		m_ctlListBox.GetSelItems(100,indexes);
		DeletePiece(indexes[0]);
	}

	m_slSeekPosition.ClearSel(1);
	m_ctlStartTime.SetData("0000000");
	m_ctlStopTime.SetData("0000000");

	RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::DeletePiece(int iIndex)
{
	m_ctlListBox.DeleteString(iIndex);
	CString data;

	if ( m_ctlListBox.GetCount() == 0)
	{
		m_llStartSelPos		= m_llStartPosition;
		m_llStopSelPos		= m_llStartPosition;

		m_slSeekPosition.ClearSel(1);
	};

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}


int CAVITrimmerAppDlg::OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex)
{
	int nCount;
	
	// delete data from list
	if (nKey == 46)
	{
		nCount = m_ctlListBox.GetSelCount();
		for (int i = 0; i < nCount; i++)
		{
			int indexes[100];
			m_ctlListBox.GetSelItems(100,indexes);
			DeletePiece(indexes[0]);
		}
	}
	
	return CDialog::OnVKeyToItem(nKey, pListBox, nIndex);
}

void CAVITrimmerAppDlg::OnBnClickedChange()
{
	if (IsOpened)
	{
		REFERENCE_TIME _start, _stop;

		_start = m_llStartSelPos;
		_stop  = m_llStopSelPos;

		int indexes[100];
		int nCount = m_ctlListBox.GetSelCount();

		if (nCount == 0)
		{
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_CHOSE_FRAGMENT_FROM_LIST_FIRST, IDS_STR_MSG_CAPT_ERROR );
			return;
		}

		// Get number of the last selected element.
		m_ctlListBox.GetSelItems (100, indexes);
		nCount = indexes[nCount-1];

		if (m_llStartSelPos >= m_llStopSelPos)
		{
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_PLS_SEL_FRAGMENT_FIRST, IDS_STR_MSG_CAPT_ERROR );
			return;
		}

		DeletePiece(nCount);

		m_llStartSelPos = _start;
		m_llStopSelPos  = _stop;

		OnBnClickedAddPart();

		m_ctlListBox.SetSel(nCount, FALSE);
	}else{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return;
	}

	 RedrawWindow(0, 0, RDW_INVALIDATE);
}

void CAVITrimmerAppDlg::OnBnClickedInvert()
{
	LONGLONG llistT0[100];
	LONGLONG llistT1[100];
	LONGLONG lnewlistT0[100];
	LONGLONG lnewlistT1[100];
	int nlistlen, i, j;
	TCHAR str[100];
	__TSTrimInfo TInew;
	TCHAR buf[100];
	REFERENCE_TIME _start, _stop;

	_start = m_llStartSelPos;
	_stop  = m_llStopSelPos;

	if (IsOpened)
	{
		int nCount = m_ctlListBox.GetSelCount();

		// get current task list
		nlistlen = m_ctlListBox.GetCount();
		for (i = 0, j = 0; i < nlistlen; i++){
			m_ctlListBox.GetText(i, str);

			// Get T0 and T1 from table
			llistT0[j] = ConvertString2Time2(str);
			llistT1[j] = ConvertString2Time2(str + 15 );

			llistT0[j] = ConvertString2Time2(Sec2Hours2(llistT0[j]));
			llistT1[j] = ConvertString2Time2(Sec2Hours2(llistT1[j]));

			if (llistT0[i] < llistT1[i])
				j++;

		}

		nlistlen = j;

		if (nlistlen > 0)
		{
			// Ok, now we have intervals. Start analize.
			if (llistT0[0] != m_llStartPosition){
				lnewlistT0[0] = m_llStartPosition;
				lnewlistT1[0] = llistT0[0];
			}

			for (i = 1; i<nlistlen; i++){
				lnewlistT0[i] = llistT1[i-1];
				lnewlistT1[i] = llistT0[i];
			}

			if (llistT1[nlistlen] != m_llStopPosition){
				lnewlistT0[nlistlen] = llistT1[nlistlen-1];
				lnewlistT1[nlistlen] = m_llStopPosition;
			}
		}

		// finished. Now fill list with new values. It, propably, was changed.
		m_ctlListBox.ResetContent();
		if ( nlistlen != 0 )
		{
			for ( i = 0; i < nlistlen + 1; i++)
			{
				if (lnewlistT0[i] < m_llStartPosition)
					lnewlistT0[i] = m_llStartPosition;

				if (lnewlistT0[i] > m_llStopPosition)
					continue;

				if (lnewlistT1[i] < m_llStartPosition)
					continue;

				if (lnewlistT1[i] > m_llStopPosition)
					lnewlistT1[i] = m_llStopPosition;

				TInew.llStartPos = lnewlistT0[i];
				TInew.llStopPos  = lnewlistT1[i];

				TInew.llStartPos = ConvertString2Time2( Sec2Hours2( TInew.llStartPos ) );
				TInew.llStopPos  = ConvertString2Time2( Sec2Hours2( TInew.llStopPos ) );
				if ( TInew.llStartPos < TInew.llStopPos ){
					ConvertTime2String(TInew, buf);
					ListBox_AddString((HWND)m_ctlListBox,buf);
				}
			}
		}
		else
		{
			TInew.llStartPos = m_llStartPosition;
			TInew.llStopPos  = m_llStopPosition;
			ConvertTime2String(TInew, buf);
			ListBox_AddString((HWND)m_ctlListBox,buf);
		}
		m_ctlListBox.SetSel(m_ctlListBox.GetCount(), TRUE);
	}else{
		TWOARG_MESSAGE_BOX( IDS_STR_MSG_SRC_FILE_HAS_NOT_BEEN_SET, IDS_STR_MSG_CAPT_ERROR );
		return;
	}

	m_llStartSelPos = _start;
	m_llStopSelPos  = _stop;

	int nMin = int( (REFERENCE_TIME)(m_llStartSelPos  / m_dSliderKoef) );  
	int nMax = int( (REFERENCE_TIME)(m_llStopSelPos  / m_dSliderKoef) );  

	m_slSeekPosition.SetSelection( nMin , nMax );

	RedrawWindow(0, 0, RDW_INVALIDATE);
}

HRESULT CAVITrimmerAppDlg::AddStreamsInfoToCntlTree()
{
	HRESULT hr = S_OK;

	CComPtr<IBaseFilter> pIAVISplitter = NULL;
	CComPtr<IEnumPins>   pIEPins	   = NULL;

	pIAVISplitter = FindFilterByGUID( m_CurrntSplitterGUID );
	if( pIAVISplitter == NULL )
		return E_FAIL;

	if( ( hr = pIAVISplitter->EnumPins( &pIEPins) ) != S_OK )
		return hr;

	GetStreamsInfo( pIEPins );

	m_ctlTree.DeleteAllItems();

	AddImageListToCtlTree();

	AddStreamInfoToCntlTree( &StreamInfo.VideoStreams );
	AddStreamInfoToCntlTree( &StreamInfo.AudioStreams );

	m_bStreamClick = false;
	return hr;
}

void CAVITrimmerAppDlg::GetStreamsInfo( IEnumPins *apIPins )
{
	CComPtr<IEnumPins> pIPins = apIPins;
	CComPtr<IPin> pIPin = NULL;	

	StreamInfo.VideoStreams.clear();
	StreamInfo.AudioStreams.clear();

	while( pIPins->Next( 1, &pIPin, NULL ) == S_OK )
	{
	  CComPtr<IEnumMediaTypes> pIEnumMT = NULL;
	  pIPin->EnumMediaTypes(&pIEnumMT);
	  AM_MEDIA_TYPE *pmt = NULL;

		while ( pIEnumMT->Next(1, &pmt, NULL ) == S_OK )
		{
			if( ( pmt->majortype == MEDIATYPE_Video ) || 
				( pmt->majortype == MEDIATYPE_Interleaved )
			  )	
			{
				StreamInfo.VideoStreams.push_back(GetVideoInfo(*pmt));
			}
			else if ( pmt->majortype == MEDIATYPE_Audio )
			{
				StreamInfo.AudioStreams.push_back(GetAudioInfo(pmt->subtype));
			}
			CoTaskMemFree( pmt );
		}
		pIEnumMT.Release();
		pIPin.Release();
	}
	pIPins.Release();
}


CAVITrimmerAppDlg::VIDEOAUDIOINFO CAVITrimmerAppDlg::GetVideoInfo( AM_MEDIA_TYPE mt)
{
	GUID subType = mt.subtype;

	VIDEOAUDIOINFO vai;
	vai.strShortInfo = _T("Unknown");
	vai.strFullInfo  = _T("Unknown"); 
	vai.StreamType   = MEDIATYPE_Video;

	CString code;

	//ckeck if video stream is uncompressed
	// e.g. RGB24
	BITMAPINFOHEADER head = {0};
	if( IsEqualGUID(mt.formattype,FORMAT_VideoInfo ) )
	{
		head = ((VIDEOINFOHEADER* )mt.pbFormat)->bmiHeader; 

	}else
		if( IsEqualGUID(mt.formattype, FORMAT_VideoInfo2 ) ){
			head = ((VIDEOINFOHEADER2* )mt.pbFormat)->bmiHeader; 
		}

		if( head.biSize != 0  &&
			head.biCompression == BI_RGB || 
			head.biCompression == BI_BITFIELDS )
		{
			vai.strShortInfo = _T("Uncompressed");
			vai.strFullInfo.Format( _T("Uncompressed Video with %u bits per pixel"), head.biBitCount );
			return vai;
		}

		FOURCCMap fourcc(&subType);
		DWORD videoInfo = fourcc.GetFOURCC();

		TCHAR temp;

		temp = TCHAR( videoInfo & 0x000000FF );
		code += temp;
		temp = TCHAR( videoInfo >> 8 & 0x000000FF );
		code += temp;
		temp = TCHAR( videoInfo >> 16 & 0x000000FF );
		code += temp;
		temp = TCHAR( videoInfo >> 24 & 0x000000FF );
		code += temp;

		code.MakeUpper();
		vai.strShortInfo = code;

		if(code == _T("DX50"))
			vai.strFullInfo = _T("DivX 5.0 codec");

		if(code == _T("DIVX"))
			vai.strFullInfo = _T("OpenDivX (DivX 4.0 and later)");

		if(code == _T("3IV2"))
			vai.strFullInfo = _T("MPEG4-based codec 3ivx");

		if(code == _T("DIV3"))
			vai.strFullInfo = _T("Low motion DivX MPEG-4");

		if(code == _T("DVSD"))
			vai.strFullInfo = _T("Sony Digital Video");

		if(code == _T("WMV3"))
			vai.strFullInfo = _T("Windows Media Video 3");

		if(code == _T("WMV1"))
			vai.strFullInfo = _T("Windows Media Video 1");

		if(code == _T("WMV2"))
			vai.strFullInfo = _T("Windows Media Video 2");

		if (code == _T("XVID"))
			vai.strFullInfo = _T("XviD MPEG-4");

		if (code == _T("CVID"))
			vai.strFullInfo = _T("Cinepak");

		return vai;
}
CAVITrimmerAppDlg::VIDEOAUDIOINFO CAVITrimmerAppDlg::GetAudioInfo(GUID subType)
{
	VIDEOAUDIOINFO vai;

	vai.strShortInfo = _T("Unknown");
	vai.strFullInfo  = _T("Unknown");
	vai.StreamType   = MEDIATYPE_Audio;

	if(subType == MEDIASUBTYPE_AC3)
	{
		vai.strShortInfo = _T("AC3");
		vai.strFullInfo  = _T("FAST Multimedia AG DVM (Dolby AC3)");
	}

	if(subType == MEDIASUBTYPE_MP3)
	{
		vai.strShortInfo = _T("MPEG1 L-3");
		vai.strFullInfo  = _T("MPEG-1 Layer 3");
	}

	if( subType == MEDIASUBTYPE_MPEG1AudioPayload ||
		subType == MEDIASUBTYPE_MPEG1Packet		  ||
		subType == MEDIASUBTYPE_MPEG1Payload	 ||
		subType == MEDIASUBTYPE_MPEG1Audio )
	{
		vai.strShortInfo = _T("MPEG1 ");
		vai.strFullInfo  = _T("MPEG-1 Audio");

	}


	if(subType == MEDIASUBTYPE_PCM)
	{
		vai.strShortInfo = _T("PCM");
		vai.strFullInfo  = _T("Microsoft PCM Format");
	}
	if(subType == WMMEDIASUBTYPE_WMAudioV2)
	{
		vai.strShortInfo = _T("WMAudio V2");
		vai.strFullInfo  = _T("Windows Media Audio");
	}

	if(subType == WMMEDIASUBTYPE_WMAudioV7)
	{
		vai.strShortInfo = _T("WMAudio V7");
		vai.strFullInfo  = _T("Windows Media Audio");
	}

	if(subType == WMMEDIASUBTYPE_WMAudioV8)
	{
		vai.strShortInfo = _T("WMAudio V8");
		vai.strFullInfo  = _T("Windows Media Audio");
	}

	if(subType == WMMEDIASUBTYPE_WMAudioV9)
	{
		vai.strShortInfo = _T("WMAudio V9");
		vai.strFullInfo  = _T("Windows Media Audio");
	}

	if (subType == WMMEDIASUBTYPE_ACELPnet)
	{
		vai.strShortInfo = _T("ACELPnet");
		vai.strFullInfo  = _T("ACELPnet");
	}

	if (subType == WMMEDIASUBTYPE_PCM)
	{
		vai.strShortInfo = _T("PCM");
		vai.strFullInfo  = _T("Pulse-code modulation");
	}

	if (subType == WMMEDIASUBTYPE_WMAudio_Lossless)
	{
		vai.strShortInfo = _T("WMAudio Lossless");
		vai.strFullInfo	 = _T("WMAudio lossless");
	}

	if ( ( subType == MEDIASUBTYPE_OGG ) ||
		( subType == MEDIASUBTYPE_VORBIS ) ||
		( subType == MEDIASUBTYPE_OGG_1 ) )
	{
		vai.strShortInfo = _T("Ogg Audio");
		vai.strFullInfo  = _T("Vorbis Ogg Audio");

		if (subType == MEDIASUBTYPE_OGG_1 ){
			vai.strFullInfo += CString(" mode 1");
		}
	}

	return vai;
}
CString CAVITrimmerAppDlg::Videoaudioinfo2Str( VIDEOAUDIOINFO vai )
{
	CString StreamType;

	if( vai.StreamType == MEDIATYPE_Audio )
		StreamType = _T("Audio");
	else
		StreamType = _T("Video");

	CString StrDescr = StreamType+ _T(" (") + vai.strShortInfo + _T(")");
	return StrDescr;
}


void CAVITrimmerAppDlg::AddStreamInfoToCntlTree( STREAMGROUP *aStreamInfo )
{
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;

	const unsigned StreamsNum = aStreamInfo->size();
	for( unsigned i = 0; i < StreamsNum; i++ )
	{
		USES_CONVERSION;
		CString str = Videoaudioinfo2Str(aStreamInfo->at(i));
		tvInsert.item.pszText = str.GetBuffer();
		aStreamInfo->at(i).hItem = m_ctlTree.InsertItem(&tvInsert);
		if ( i == 0 )
			CheckCTItem( aStreamInfo->at(i).hItem );
		else
			UncheckCTItem( aStreamInfo->at(i).hItem );
	}
}
void CAVITrimmerAppDlg::AddImageListToCtlTree()
{
	m_pTreeImages = new CImageList;
	m_pTreeImages->Create(16, 16, ILC_MASK, 0, 32);

	for (UINT nID = IDB_BITMAP_UNCHECKED; nID <= IDB_BITMAP_CHECKED; nID++)
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(nID);
		m_pTreeImages->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();
	}

	m_ctlTree.SetImageList(m_pTreeImages,TVSIL_NORMAL);
}
void CAVITrimmerAppDlg::SelectStream( STREAMGROUP *StreamGroup,HTREEITEM hItem )
{
	if( !IsCTItemChecked( hItem) )
	{
		unsigned const size = StreamGroup->size();
		for ( unsigned i = 0; i < size; i ++ )
		{
			UncheckCTItem( StreamGroup->at(i).hItem );
		}
		CheckCTItem( hItem );
	}
	else
	{
		UncheckCTItem( hItem );
	}
}
bool CAVITrimmerAppDlg::IsCTItemChecked( HTREEITEM hItem )
{
	int img, img_sel;
	m_ctlTree.GetItemImage( hItem, img, img_sel);
	if( img == CTII_CHECKED )
		return true;
	return false;
}
void CAVITrimmerAppDlg::CheckCTItem( HTREEITEM hItem )
{
	int img = CTII_CHECKED;
	m_ctlTree.SetItemImage( hItem, img, img);
}
void CAVITrimmerAppDlg::UncheckCTItem( HTREEITEM hItem )
{	
	int img = CTII_UNCHECKED;
	m_ctlTree.SetItemImage( hItem, img, img);
}

CAVITrimmerAppDlg::STREAMGROUP* CAVITrimmerAppDlg::FindStreamGroup( HTREEITEM hItem )
{
	STREAMGROUP::iterator item;
	for ( item = StreamInfo.VideoStreams.begin(); item != StreamInfo.VideoStreams.end(); item++ )
	{
		if( item->hItem== hItem )
			return &StreamInfo.VideoStreams;
	}
	for ( item = StreamInfo.AudioStreams.begin(); item != StreamInfo.AudioStreams.end(); item++ )
	{
		if( item->hItem == hItem )
			return &StreamInfo.AudioStreams;
	}
	
	return NULL;
}
int CAVITrimmerAppDlg::GetAudioStreamNumber()
{
	return GetStreamNumber( &StreamInfo.AudioStreams );	
}
int	CAVITrimmerAppDlg::GetVideoStreamNumber()
{
	return GetStreamNumber( &StreamInfo.VideoStreams );	
}
int	CAVITrimmerAppDlg::GetStreamNumber ( STREAMGROUP *StreamGroup )
{
	const unsigned size = StreamGroup->size();
	for( unsigned i = 0; i < size; i++ )
	{
		if(IsCTItemChecked(StreamGroup->at(i).hItem))
			return i + 1;
	}
	return 0;
}
HRESULT CAVITrimmerAppDlg::ConnectSplitterPins( AVStreamsNumbers *sAVStreamsNumbers )
{

	CComPtr<IBaseFilter>  pIMSAVISpliter = NULL;
	CComPtr<IPin>		  pIPSplitPin    = NULL;
	CComPtr<IEnumPins>	  pIEPins		 = NULL;
	
	int n	= 0;
	int res = 0;

	PIN_DIRECTION pd;
	HRESULT		  hr = S_OK;
	
	bool bVideoStreamFound	= false;
	bool bAudioStreamFound	= false;
	bool bAudioPinConnected = false;
	bool bVideoPinConnected = false;
	
	pIMSAVISpliter = FindFilterByGUID( m_CurrntSplitterGUID );

	if ( pIMSAVISpliter == NULL )
		return E_FAIL;

	pIMSAVISpliter->EnumPins(&pIEPins);

	int iVideoPinCnt = 0;
	int iAudioPinCnt = 0;

	while (  pIEPins->Next(1, &pIPSplitPin, NULL ) == S_OK  )
	{
		pIPSplitPin->QueryDirection(&pd);
		if (pd == PINDIR_OUTPUT)
		{	
			CComPtr<IEnumMediaTypes> pIEnumMT = NULL;
			pIPSplitPin->EnumMediaTypes(&pIEnumMT);
			AM_MEDIA_TYPE *pmt = NULL;
			
			hr = pIEnumMT->Next( 1, &pmt, NULL );
			if( hr != S_OK )
				return hr;

			if( ( ( pmt->majortype == MEDIATYPE_Video ) || 
				  ( pmt->majortype == MEDIATYPE_Interleaved )
				) && 
				( sAVStreamsNumbers->iVideoStreamNumber != 0 )
			  )
			{
				bVideoStreamFound = true;
				if( ConnectSplitterPin( sAVStreamsNumbers->iVideoStreamNumber, &iVideoPinCnt, pIPSplitPin ) == S_OK )
					bVideoPinConnected = true;
			}
			else if ( ( pmt->majortype == MEDIATYPE_Audio ) &&
					  ( sAVStreamsNumbers->iAudioStreamNumber != 0 )
					)
			{
				bAudioStreamFound = true;
				if( ConnectSplitterPin( sAVStreamsNumbers->iAudioStreamNumber, &iAudioPinCnt, pIPSplitPin ) == S_OK )
					bAudioPinConnected = true;
	
			}
			else
			{
				ConnToNullRenderer( pIPSplitPin );
			}

			pIEnumMT.Release();
			CoTaskMemFree( pmt );
		}
		pIPSplitPin.Release();
		
	}
	pIEPins.Release();
	pIMSAVISpliter.Release();

	if( !bVideoStreamFound || !bVideoPinConnected )
		sAVStreamsNumbers->iVideoStreamNumber = 0;
	if( !bAudioStreamFound || !bAudioPinConnected )
		sAVStreamsNumbers->iAudioStreamNumber = 0;

	switch (n)
	{
		case 1:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_VIDEO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
		case 2:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_AUDIO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
		case 3:
			TWOARG_MESSAGE_BOX( IDS_STR_MSG_CANT_FIND_VIDEO_AUDIO_DECODER, IDS_STR_MGS_CAPT_WARNING );
			break;
	}	

	return hr;
}
CComPtr<IBaseFilter> CAVITrimmerAppDlg::FindFilterByGUID( const GUID &guid_to_find	)
{
	CComPtr<IEnumFilters> pIEFilters = NULL;
	CComPtr<IBaseFilter>  pIFiler    = NULL;

	m_pGraph->EnumFilters( &pIEFilters );

	while ( pIEFilters->Next( 1, &pIFiler, NULL ) == S_OK )
	{
		GUID cur_guid;
		pIFiler->GetClassID( &cur_guid );
		if( cur_guid == guid_to_find )
			break;
		pIFiler.Release();
	}
	pIEFilters.Release(); 
	
	return pIFiler;
}

HRESULT CAVITrimmerAppDlg::ConnectSplitterPin( int			 iStreamNumber
											  ,int			 *piPinNumber
											  ,IPin			 *pIPSplitPin )
{
	CComPtr<IPin> pIPOtherFltPin = NULL;
	HRESULT       hr             = S_OK;

	(*piPinNumber)++;

	hr = pIPSplitPin->ConnectedTo( &pIPOtherFltPin );

	if( hr == S_OK )
	{
		//Disconnect AVISplitter's pin if it's connected to other filter
        hr = m_pGraph->Disconnect( pIPOtherFltPin );

		if( hr != S_OK )
			return hr;		

		pIPOtherFltPin.Release();

		hr = m_pGraph->Disconnect( pIPSplitPin );

		if( hr != S_OK )
			return hr;		
	}
	else if( hr != VFW_E_NOT_CONNECTED )
	{
		return hr;
	}
	hr = S_OK;

    // if AVISplitter's pin is pin corresponding stream user selected
	// render them
	if( *piPinNumber == iStreamNumber )
	{
		hr = m_pGraph->Render( pIPSplitPin );
		if( hr != S_OK )
			return hr;		
	}
	else
	{
		ConnToNullRenderer( pIPSplitPin );

		// переделать сделать что-нить вроде return CONNECTED_NULL_RENDERER
		return E_FAIL;
	}

	return hr;	
}
HRESULT CAVITrimmerAppDlg::ReCreateGraph( AVStreamsNumbers *sAVStreamsNumbers )
{
	HRESULT hr;

	hr = DeleteGraph();
	if( hr != S_OK )
		return hr;
	
	hr = CreateGraph( sAVStreamsNumbers );
	if( hr != S_OK )
		DeleteGraph();

	return hr;
}
HRESULT CAVITrimmerAppDlg::DeleteGraph()
{
	HRESULT hr = S_OK;

	m_pControl->Pause();
	m_pControl->Stop();

	FreeSourceFile();

	SAFE_RELEASE(m_pVideoWindow);
	SAFE_RELEASE(m_pControl);
	SAFE_RELEASE(m_pMediaSeek);
	SAFE_RELEASE(m_pGraph);

	return hr;
}
HRESULT CAVITrimmerAppDlg::CreateGraph( AVStreamsNumbers *sAVStreamsNumbers )
{
	HRESULT hr = S_OK;
	
	if (m_pGraph == NULL)
	{
		hr=CoCreateInstance( CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (LPVOID *) &m_pGraph);
		if (FAILED(hr))
		{
			ProcessHRESULT(hr);
			RedrawWindow(0, 0, RDW_INVALIDATE);
			return E_FAIL;
		}
		m_pGraph->QueryInterface(IID_IMediaControl, (LPVOID *) &m_pControl);
		m_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVideoWindow);
		m_pGraph->QueryInterface(IID_IMediaSeeking, (LPVOID *) &m_pMediaSeek);
	}

	hr = BuildSourceSplitterPart();
	if( FAILED(hr) )
		return hr;
	hr = ConnectSplitterPins( sAVStreamsNumbers );

    return hr;
}
HRESULT CAVITrimmerAppDlg::BuildSourceSplitterPart()
{
	CComVariant cvVar;
	HRESULT hr = m_pModuleCfg->GetValue(&SMAT_GetFileType, &cvVar);
	if( cvVar.intVal == SMM_File_Type_AVI )
		hr = BuildSourceSplitterPartAVI();
	if( cvVar.intVal == SMM_File_Type_ASF )
		hr = BuildSourceSplitterPartASF();
	return hr;
}
HRESULT CAVITrimmerAppDlg::BuildSourceSplitterPartASF()
{
	HRESULT hr = S_OK;
	m_CurrntSplitterGUID = CLSID_WMAsfReader;

	CComPtr<IBaseFilter>	   m_pMSFileReader	= NULL;
	CComPtr<IBaseFilter>	   m_pMSAVISpliter	= NULL;
	CComPtr<IFileSourceFilter> m_pIReader		= NULL;

	hr = CoCreateInstance( CLSID_WMAsfReader, 0, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (LPVOID *) &m_pMSFileReader);
	if (hr != S_OK)
		return E_FAIL;

	m_pMSAVISpliter = NULL;
	hr = m_pGraph->AddFilter( m_pMSFileReader, NULL );

	// now Load requested file.
	hr = m_pMSFileReader->QueryInterface(IID_IFileSourceFilter, (LPVOID *) &m_pIReader);

	//AM_MEDIA_TYPE mt = {0};
	BSTR bstFName = m_strFileSource.AllocSysString();
	hr = m_pIReader->Load( bstFName, /*&mt*/NULL );
	SysFreeString( bstFName );
	m_pIReader.Release();
	if ( hr != S_OK )
	{
		m_pGraph->RemoveFilter( m_pMSFileReader );
		m_pMSFileReader.Release();
		return E_FAIL;
	}

	return S_OK;
}
HRESULT CAVITrimmerAppDlg::BuildSourceSplitterPartAVI()
{
	HRESULT hr = S_OK;
	m_CurrntSplitterGUID = CLSID_AviSplitter;

	CComPtr<IEnumPins> pIEPins		 = NULL;
	CComPtr<IPin>      pIReaderPin   = NULL;
	CComPtr<IPin>      pISplitterPin = NULL;

	CComPtr<IBaseFilter>	   m_pMSFileReader	= NULL;
	CComPtr<IBaseFilter>	   m_pMSAVISpliter	= NULL;
	CComPtr<IFileSourceFilter> m_pIReader		= NULL;

	// First - add to the graph two filters
	hr = CoCreateInstance( CLSID_AsyncReader, 0, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (LPVOID *) &m_pMSFileReader);
	if (hr != S_OK)
		return E_FAIL;

	hr=CoCreateInstance( CLSID_AviSplitter, 0, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (LPVOID *) &m_pMSAVISpliter);
	if (hr != S_OK)
	{
		m_pMSFileReader.Release();
		return E_FAIL;
	}

	hr = m_pGraph->AddFilter( m_pMSFileReader, NULL );
	hr = m_pGraph->AddFilter( m_pMSAVISpliter, NULL );

	// now Load requested file.
	hr = m_pMSFileReader->QueryInterface(IID_IFileSourceFilter, (LPVOID *) &m_pIReader);
	//BSTR bstrFN = strFileSource.AllocSysString()

	AM_MEDIA_TYPE mt = {0};
	mt.majortype = MEDIATYPE_Stream;
	mt.subtype   = MEDIASUBTYPE_Avi;
	BSTR bstFName = m_strFileSource.AllocSysString();
	hr = m_pIReader->Load( bstFName, &mt );
	SysFreeString( bstFName );
	if ( hr != S_OK )
	{
		m_pGraph->RemoveFilter( m_pMSFileReader );
		m_pGraph->RemoveFilter( m_pMSAVISpliter );
		m_pIReader.Release();
		m_pMSFileReader.Release();
		return E_FAIL;
	}
	m_pIReader.Release();

	// Connect reader to the spliter
	m_pMSFileReader->EnumPins(&pIEPins);
	pIEPins->Next( 1, &pIReaderPin, NULL );
	pIEPins.Release();
	m_pMSAVISpliter->EnumPins(&pIEPins);
	pIEPins->Next( 1, &pISplitterPin, NULL );
	pIEPins.Release();

	hr = m_pGraph->Connect( pIReaderPin, pISplitterPin );
	if (hr != 0){
		m_pGraph->RemoveFilter(m_pMSAVISpliter);
		return hr;
	}
	
	pISplitterPin.Release();
	pIReaderPin.Release();

	return S_OK;
}
CAVITrimmerAppDlg::AVStreamsNumbers CAVITrimmerAppDlg::GetAVStreamsNumbers ()
{
	AVStreamsNumbers sAVStramsNum( 0, 0 );

	sAVStramsNum.iAudioStreamNumber = GetAudioStreamNumber();
	sAVStramsNum.iVideoStreamNumber = GetVideoStreamNumber();

	return sAVStramsNum;
}
CAVITrimmerAppDlg::tagAVStreamsNumbers::tagAVStreamsNumbers( int ASN, int VSN ): iAudioStreamNumber( ASN )
																				,iVideoStreamNumber( VSN )
{}
CAVITrimmerAppDlg::tagAVStreamsNumbers::tagAVStreamsNumbers ( const tagAVStreamsNumbers& AVSN )
{
	*this = tagAVStreamsNumbers( AVSN.iAudioStreamNumber, AVSN.iVideoStreamNumber );
}
bool CAVITrimmerAppDlg::tagAVStreamsNumbers::operator==( const tagAVStreamsNumbers& rhs  )
{
	if( ( this->iAudioStreamNumber == rhs.iAudioStreamNumber ) &&
		( this->iVideoStreamNumber == rhs.iVideoStreamNumber )    )
	{
		return true;
	}
	return false;
}
bool CAVITrimmerAppDlg::tagAVStreamsNumbers::operator!=( const tagAVStreamsNumbers& rhs	)
{
	return !( *this == rhs );
}
void CAVITrimmerAppDlg::LoadButtonBitmap( CBitmapButton *pBut
										 ,UINT			  uiButId
										 ,UINT			  uiBitmapUp
										 ,UINT			  uiBitmapDown
										 ,UINT			  uiBitmabDis  )
{
	if ( !pBut->LoadBitmaps( uiBitmapUp, uiBitmapDown, uiBitmabDis ) )
	{
		ONEARG_MESSAGE_BOX( IDS_STR_UNABLE_TO_LOAD_BUTS_BITMAPS );
	}
	else
	{
		VERIFY(pBut->SubclassDlgItem(uiButId, this));
		pBut->SizeToContent();
	}
}
void CAVITrimmerAppDlg::OnNMClickTreeStreams(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	CPoint point;
	GetCursorPos(&point);
	m_ctlTree.ScreenToClient(&point);
	UINT nHitFlags;
	HTREEITEM hItem = m_ctlTree.HitTest(point, &nHitFlags);

	if ( hItem )
	{
		
		SelectStream( FindStreamGroup(hItem), hItem );	
		m_ctlTree.SelectItem( hItem );
		*pResult = 1;
		return;
	}

	*pResult = 0;

}
PCHAR* CAVITrimmerAppDlg::CommandLineToArgvA( PCHAR CmdLine, int* _argc )
{
	PCHAR* argv;
	PCHAR  _argv;
	ULONG   len;
	ULONG   argc;
	CHAR   a;
	ULONG   i, j;

	BOOLEAN  in_QM;
	BOOLEAN  in_TEXT;
	BOOLEAN  in_SPACE;

	len = strlen(CmdLine);
	i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

	argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
		i + (len+2)*sizeof(CHAR));

	_argv = (PCHAR)(((PUCHAR)argv)+i);

	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;

	while( a = CmdLine[i] ) {
		if(in_QM) {
			if(a == '\"') {
				in_QM = FALSE;
			} else {
				_argv[j] = a;
				j++;
			}
		} else {
			switch(a) {
				case '\"':
					in_QM = TRUE;
					in_TEXT = TRUE;
					if(in_SPACE) {
						argv[argc] = _argv+j;
						argc++;
					}
					in_SPACE = FALSE;
					break;
				case ' ':
				case '\t':
				case '\n':
				case '\r':
					if(in_TEXT) {
						_argv[j] = '\0';
						j++;
					}
					in_TEXT = FALSE;
					in_SPACE = TRUE;
					break;
				default:
					in_TEXT = TRUE;
					if(in_SPACE) {
						argv[argc] = _argv+j;
						argc++;
					}
					_argv[j] = a;
					j++;
					in_SPACE = FALSE;
					break;
			}
		}
		i++;
	}
	_argv[j] = '\0';
	argv[argc] = NULL;

	(*_argc) = argc;
	return argv;
}


void CAVITrimmerAppDlg::OnBnClickedCheckTrimOverlapped()
{
	// TODO: Add your control notification handler code here
}
