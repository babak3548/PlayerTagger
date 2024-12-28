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
#include <atlbase.h>
#include <initguid.h>

#include <indxdef.h>
#include "SimplePlayer.h"
#include "SimplePlayerDlg.h"

#define MAIN_TIMER			1
#define INDEX_TIMER			2
#define TRIM_TIMER			3

#define PROGRESS_RANGE		100

void setExtension(LPCTSTR tcsFile, LPTSTR tcsIndex)
{
	TCHAR tcsDrive[_MAX_DRIVE];
	TCHAR tcsDir[_MAX_DIR];
	TCHAR tcsFName[_MAX_FNAME];
	TCHAR tcsExt[_MAX_EXT];

	_tsplitpath(tcsFile, tcsDrive, tcsDir, tcsFName, tcsExt);
	_tmakepath(tcsIndex, tcsDrive, tcsDir, tcsFName, _T(".mlmix"));
}


CDlgIndexing::CDlgIndexing(CWnd* pParent ,HRESULT *phr): 
CDialog(CDlgIndexing::IDD, pParent),
m_pIModuleConfig(NULL),
m_pITrimmerObj(NULL),
m_IndexTimer(0)
{
	SetFinishedIndexing( TRUE );
	*phr = ::CoCreateInstance( CLSID_TrimmerObjControl, NULL, CLSCTX_INPROC,
								IID_ITrimmerObjControl, (void**) &m_pITrimmerObj );
	if( FAILED(*phr) )
		return;

	*phr = m_pITrimmerObj->QueryInterface( IID_IModuleConfig, (void **)&m_pIModuleConfig );
	if( FAILED(*phr) )
		return;
	VARIANT var = {0};

	CString silenPt = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	if ( 0 != silenPt.GetLength() )
	{
		var.bstrVal = silenPt.AllocSysString();
		*phr= m_pIModuleConfig->SetValue( &SMAT_SilentPath, &var );
		SysFreeString( var.bstrVal );
	}

	var.bstrVal  = m_csProfile.AllocSysString();
	*phr= m_pIModuleConfig->SetValue( &SMAT_CodecsSet, &var );
	SysFreeString( var.bstrVal );
}

// CDlgIndexing dialog
CDlgIndexing::CDlgIndexing(CWnd* pParent /*=NULL*/): 
CDialog(CDlgIndexing::IDD, pParent)
{
}

CDlgIndexing::~CDlgIndexing()
{
	m_pIModuleConfig.Release();
	m_pITrimmerObj.Release();
}

void CDlgIndexing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_INDEX, m_ctlPogrIndx);
}

BOOL CDlgIndexing::OnInitDialog()
{
	HRESULT hr;	
	
	VARIANT var = {0};
	var.bstrVal  = m_csProfile.AllocSysString();
	hr= m_pIModuleConfig->SetValue( &SMAT_CodecsSet, &var );
	SysFreeString( var.bstrVal );

	CDialog::OnInitDialog();
	m_ctlPogrIndx.SetRange( 0, PROGRESS_RANGE );
	SetFinishedIndexing( FALSE );
	m_IndexTimer = SetTimer( INDEX_TIMER, 500, NULL );
	
	//Set Callback here
	if( &m_xCTrimmerObjControlCB )
	{
		var.pbVal = (BYTE*) &m_xCTrimmerObjControlCB;
		hr = m_pIModuleConfig->SetValue( &SMAT_Callback, &var);
	}
	
	var.vt		= VT_BOOL;
	var.boolVal = TRUE;
	hr = m_pIModuleConfig->SetValue( &SMAT_StartIndexation, &var );
	if( FAILED(hr) )
	{
		SetFinishedIndexing( TRUE );	
		return FALSE;
	}
	return TRUE;
}
HRESULT CDlgIndexing::SetInputFile( CString strInName )
{
	BSTR bstName = strInName.AllocSysString();
	VARIANT var = {0};
	HRESULT hr = E_FAIL;
	var.vt = VT_BSTR;
	var.bstrVal = bstName;
	hr = m_pIModuleConfig->SetValue( &SMAT_InputFile, &var );
	SysFreeString( bstName );
	return hr;
}
HRESULT CDlgIndexing::SetOutputIndexFile( CString strOutInd )
{
	BSTR bstName = strOutInd.AllocSysString();
	VARIANT var = {0};
	HRESULT hr = E_FAIL;
	var.vt = VT_BSTR;
	var.bstrVal = bstName;
	hr = m_pIModuleConfig->SetValue( &SMAT_OutIndexFile, &var );
	SysFreeString( bstName );
	return hr;
}

void CDlgIndexing::OnTimer(UINT_PTR nIDEvent )
{
	CDialog::OnTimer(nIDEvent);
	if( nIDEvent == INDEX_TIMER )
	{
		long lProgress = 1;
		m_pITrimmerObj->get_Status( &lProgress );
		TRACE("%d\n",lProgress);
		//kill timer and release interface if indexing is over
		if( IsFinishedIndexing(  ) ) 
		{
			m_ctlPogrIndx.SetPos( PROGRESS_RANGE );
			KillTimer( m_IndexTimer );
			m_IndexTimer = 0;
			EndDialog (1);
		}
		else if( lProgress >= 0 )
		{
			m_ctlPogrIndx.SetPos(lProgress * PROGRESS_RANGE / 100);
		}
	}
}

void CDlgIndexing::TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime )
{
	int t = 0;
}

BEGIN_MESSAGE_MAP(CDlgIndexing, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
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
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerDlg dialog


CSimplePlayerDlg::CSimplePlayerDlg(CWnd* pParent /*=NULL*/): 
	CDialog(CSimplePlayerDlg::IDD, pParent),
	m_pPlayer(NULL),
	m_pTrimGraph(NULL),
	m_TimerTrim(0),
	m_TimerMain(0),
	m_TrimNotify(this)
{	
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_csProfile = Default_Codecs_Profile;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	ProfileParser & parser = ProfileParser::Instance(m_csProfile);
	GUID codecGUID = parser.GetFilterCLSID( ProfileParser::Id_IndexReader, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	m_pPlayer		= new CPlayer( parser.GetFltrSlntPath( slntPath, codecGUID ) );
	m_pTrimGraph	= new CTrimGrpah( parser.GetFltrSlntPath( slntPath, codecGUID ) );
	m_ftFileType = SMM_File_Type_MPEG2_TS;
}

CSimplePlayerDlg::~CSimplePlayerDlg()
{
	if( m_pPlayer )
		delete m_pPlayer;

	KillTrimmingGraph();
}

void CSimplePlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimplePlayerDlg)
	DDX_Control(pDX, IDC_TIME,				m_Time );
	DDX_Control(pDX, IDC_PROGRESS,			m_Progress);
	DDX_Control(pDX, IDC_LIST,				m_ctlList);
	DDX_Control(pDX, IDC_CHECK_INDEX,		m_CheckUseIndex);
	DDX_Control(pDX, IDC_CHECK_VIDEO_ONLY,	m_CheckVideoOnly);
	DDX_Control(pDX, IDC_DURATION,		m_Duration);
	DDX_Control(pDX, IDC_ED_FILE,		m_edFileName);	
	DDX_Control(pDX, IDC_ED_FILE_SAVE,	m_edFileNameSave);	
	DDX_Control(pDX, IDC_SLD_POSITION,	m_sldPosition);		
	DDX_Control(pDX, IDC_BEGIN,			m_Buttons[buttonBegin]);
	DDX_Control(pDX, IDC_STEPBW,		m_Buttons[buttonStepBW]);
	DDX_Control(pDX, IDC_PLAY,			m_Buttons[buttonPlay]);
	DDX_Control(pDX, IDC_PAUSE,			m_Buttons[buttonPause]);
	DDX_Control(pDX, IDC_STOP,			m_Buttons[buttonStop]);
	DDX_Control(pDX, IDC_STEPFW,		m_Buttons[buttonStepFW]);
	DDX_Control(pDX, IDC_END,			m_Buttons[buttonEnd]);	
	DDX_Control(pDX, IDC_OPEN,			m_Buttons[buttonOpen]);
	DDX_Control(pDX, IDC_SAVE,			m_Buttons[buttonSave]);
	DDX_Control(pDX, IDC_MARK_LEFT,		m_Buttons[buttonMarkLeft]);
	DDX_Control(pDX, IDC_MARK_RIGHT,	m_Buttons[buttonMarkRight]);
	DDX_Control(pDX, IDC_ADD,			m_Buttons[buttonAdd]);
	DDX_Control(pDX, IDC_REMOVE,		m_Buttons[buttonRemove]);
	DDX_Control(pDX, IDC_TRIM,			m_Buttons[buttonTrim]);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimplePlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BEGIN,		OnBegin)
	ON_BN_CLICKED(IDC_BACKWARD,		OnBackward)
	ON_BN_CLICKED(IDC_STEPBW,		OnStepBW)
	ON_BN_CLICKED(IDC_PLAY,			OnPlay)
	ON_BN_CLICKED(IDC_PAUSE,		OnPause)
	ON_BN_CLICKED(IDC_STOP,			OnStop)
	ON_BN_CLICKED(IDC_STEPFW,		OnStepFW)
	ON_BN_CLICKED(IDC_FORWARD,		OnForward)
	ON_BN_CLICKED(IDC_END,			OnEnd)
	ON_BN_CLICKED(IDC_OPEN,			OnOpen)

	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnBnClickedRemove)
	ON_BN_CLICKED(IDC_MARK_RIGHT, OnBnClickedMarkRight)
	ON_BN_CLICKED(IDC_MARK_LEFT, OnBnClickedMarkLeft)
	ON_LBN_SELCHANGE(IDC_LIST, OnLbnSelchangeList)
	ON_WM_KEYDOWN()
	ON_LBN_DBLCLK(IDC_LIST, OnLbnDblclkList)
	ON_BN_CLICKED(IDC_TRIM, OnBnClickedTrim)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerDlg message handlers

BOOL CSimplePlayerDlg::OnInitDialog()
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
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	HICON hi; 
	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_OPEN));
	m_Buttons[buttonOpen].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_SAVE));
	m_Buttons[buttonSave].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_BEGIN));
	m_Buttons[buttonBegin].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_STEPBW));
	m_Buttons[buttonStepBW].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_PLAY));
	m_Buttons[buttonPlay].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_PAUSE));
	m_Buttons[buttonPause].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_STOP));
	m_Buttons[buttonStop].SetIcon(hi);
	
	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_STEPFW));
	m_Buttons[buttonStepFW].SetIcon(hi);
	
	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_END));
	m_Buttons[buttonEnd].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_MARK_LEFT));
	m_Buttons[buttonMarkLeft].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_MARK_RIGHT));
	m_Buttons[buttonMarkRight].SetIcon(hi);

	m_CheckUseIndex.SetCheck(BST_CHECKED);
	m_CheckVideoOnly.SetCheck(BST_UNCHECKED);

	EnableButtons( EnablingInitedDialog , FALSE );

	m_Progress.SetRange(0, PROGRESS_RANGE);
	m_sldPosition.SetRange(0, 1000);
	
	m_sldPosition.EnableWindow(FALSE);

	m_hAccel = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_APP));
	m_TimerMain = SetTimer( MAIN_TIMER, 500, NULL );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSimplePlayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	int iRes = TranslateAccelerator(this->m_hWnd, m_hAccel, pMsg);
	
	if (iRes) return iRes;
	
	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
	{
		MSG msg;
		::CopyMemory(&msg, pMsg, sizeof(MSG));
		HWND hWndParent = ::GetParent(msg.hwnd);
		
		while (hWndParent && hWndParent != m_hWnd)
		{
			msg.hwnd = hWndParent;
			hWndParent = ::GetParent(hWndParent);
		}	
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CSimplePlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimplePlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimplePlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSimplePlayerDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	WORD wLPar = LOWORD(wParam);
	WORD wHPar = HIWORD(wParam);
	
	if(m_pPlayer && m_pPlayer->IsInitialized())
	{
		if(!m_pPlayer->IsFullscreenMode() && wHPar != 1 && wLPar != IDCANCEL)
			return CDialog::OnCommand(wParam, lParam);

	} else 
	if(wHPar != 1 && wLPar != IDCANCEL)
		return CDialog::OnCommand(wParam, lParam);
	
	if ((wLPar == IDCANCEL || wLPar == IDOK) && m_pPlayer && m_pPlayer->IsFullscreenMode()) 
	{
		m_pPlayer->SetFullscreenMode(FALSE, NULL);
		SetForegroundWindow();
		return TRUE;

	} else
	if(wLPar == IDCANCEL)
		CDialog::OnCancel();
	
	if (wLPar == IDOK) 
		return TRUE;
	
	if (m_pPlayer && m_pPlayer->IsInitialized()) 
	{
		switch(wLPar){
		
		case ID_ACCEL_FullScreen:
			m_pPlayer->SetFullscreenMode(!m_pPlayer->IsFullscreenMode(), (OAHWND) this->m_hWnd);
			if(!m_pPlayer->IsFullscreenMode())
				SetForegroundWindow();
			break;

		case ID_ACCEL_Play:
			if(m_Buttons[buttonPause].IsWindowVisible())
				OnPause();
			else
				OnPlay();
			break;
		case ID_ACCEL_Begin:
			OnBegin();
			break;
		case ID_ACCEL_End:
			OnEnd();
			break;
		case ID_ACCEL_StepBW:
			OnStepBW();
			break;
		case ID_ACCEL_StepFW:
			OnStepFW();
			break;
		}
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CSimplePlayerDlg::OnCancel()
{
	KillTimer( m_TimerMain );
	if(m_pPlayer && m_pPlayer->IsInitialized())
	{
		HRESULT hr = E_FAIL;
		while(hr != S_OK)
			hr = m_pPlayer->Stop();
		m_pPlayer->Reset();
	}
	
	if( m_pTrimGraph  && m_pTrimGraph->IsInitialized())
	{
		HRESULT hr = E_FAIL;
		while(hr != S_OK)
			hr = m_pTrimGraph->Stop();
		m_pTrimGraph->Reset();
	}
	
	CDialog::OnCancel();
}

void CSimplePlayerDlg::OnBegin()
{
	if( m_FragmentParams.rtRightTime != m_FragmentParams.rtLeftTime )
	{
		m_pPlayer->SetPosition( m_FragmentParams.rtLeftTime );
		m_sldPosition.SetPos( m_FragmentParams.nSldrSelPosLeft );
		return;
	}
	
	m_pPlayer->SetPosition(0);

	m_sldPosition.SetPos( m_sldPosition.GetRangeMin() );

	EnableButtonForPosition();
}

void CSimplePlayerDlg::OnBackward()
{
	m_Buttons[buttonPlay].ShowWindow(SW_HIDE);
	m_Buttons[buttonPause].ShowWindow(SW_SHOW);
	m_Buttons[buttonPause].RedrawWindow();

	m_pPlayer->FastBackward(-1, TRUE);
}

void CSimplePlayerDlg::OnStepBW()
{
	m_pPlayer->Step( -1 );

	EnableButtonForPosition();
}

void CSimplePlayerDlg::OnPlay()
{
	m_Buttons[buttonPlay].ShowWindow(SW_HIDE);
	m_Buttons[buttonPause].ShowWindow(SW_SHOW);
	m_Buttons[buttonPause].RedrawWindow();

	m_pPlayer->Run();
}

void CSimplePlayerDlg::OnPause()
{
	m_Buttons[buttonPause].ShowWindow(SW_HIDE);
	m_Buttons[buttonPlay].ShowWindow(SW_SHOW);
	m_Buttons[buttonPlay].RedrawWindow();

	m_pPlayer->Pause();
}

void CSimplePlayerDlg::OnStop()
{
	m_Buttons[buttonPause].ShowWindow(SW_HIDE);
	m_Buttons[buttonPlay].ShowWindow(SW_SHOW);
	m_Buttons[buttonPlay].RedrawWindow();

	m_pPlayer->Stop();
	m_pPlayer->Pause(FALSE);
	
	OnBegin();
}

void CSimplePlayerDlg::OnStepFW()
{
	m_pPlayer->Step( 1 );

	EnableButtonForPosition();
}

void CSimplePlayerDlg::OnForward()
{
	m_Buttons[buttonPlay].ShowWindow(SW_HIDE);
	m_Buttons[buttonPause].ShowWindow(SW_SHOW);
	m_Buttons[buttonPause].RedrawWindow();

	m_pPlayer->FastForward(1, TRUE);
}

void CSimplePlayerDlg::OnEnd()
{
	if( m_FragmentParams.rtRightTime != m_FragmentParams.rtLeftTime )
	{
		m_pPlayer->SetPosition(m_FragmentParams.rtRightTime);
		m_sldPosition.SetPos(m_FragmentParams.nSldrSelPosRight);
		return;
	}
	
	REFERENCE_TIME rtPos = m_pPlayer->GetDuration();
	
	if( rtPos != MAXLONGLONG )
		m_pPlayer->SetPosition( rtPos );

	m_sldPosition.SetPos( m_sldPosition.GetRangeMax() );

	EnableButtonForPosition();
}

void CSimplePlayerDlg::KillTrimmingGraph()
{
	if (m_pTrimGraph )
	{
		m_pTrimGraph->Reset();
		delete m_pTrimGraph;
		m_pTrimGraph = NULL;
	}
}
SMM_OutputTypes CSimplePlayerDlg::DetectType( CString csName )
{
	HRESULT hr = S_FALSE;
	CComPtr<IModuleConfig> pITrimmerObj = NULL;
	hr = ::CoCreateInstance( CLSID_TrimmerObjControl, NULL, CLSCTX_INPROC,
	IID_IModuleConfig, (void**) &pITrimmerObj );
	VARIANT var = {0};
	var.vt = VT_BSTR;
	var.bstrVal = csName.AllocSysString();
	hr = pITrimmerObj->SetValue( &SMAT_InputFile, &var );
	SysFreeString( var.bstrVal );
	VariantClear(&var);
	hr = pITrimmerObj->GetValue( &SMAT_GetFileType, &var );
	return (SMM_OutputTypes)var.intVal;

}
void CSimplePlayerDlg::OnOpen()
{
	static TCHAR szFilter[] = _T("Media Files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov)| *.vob; *.mpg; *.mpeg; *.m2v; *.mp4; *.m4v; *.mkv; *.m2ts; *.h264; *.mov;|Index files (*.mlmix)| *.mlmix| All Files (*.*)| *.*||");
	//Execute dialog
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY ,szFilter);
USES_CONVERSION;
	if ( dlg.DoModal() == IDOK )
	{
		m_ftFileType = DetectType( dlg.GetPathName() );

		RedrawWindow();
		m_edFileNameSave.SetWindowText(_T(""));
		HRESULT hr = m_pPlayer->Stop();
		m_pPlayer->Reset();//Releases the preview filters and index used by the Demuxer filter
		KillTrimmingGraph();
		
		TCHAR tcsIndexName[_MAX_PATH];
		
		//change file's extension to .mlmix
		setExtension( ( ( LPCTSTR) dlg.GetPathName() ), tcsIndexName);
		
		// we deal with index
		if( 0 ==  _tcscmp( tcsIndexName,  dlg.GetPathName() ) )
		{
			BSTR bstStr = T2BSTR(tcsIndexName);
			hr = ((CIndexEx) *m_pPlayer)->put_IndexFileName( bstStr );
			if(FAILED(hr) )
				MessageBox(_T("Unable to open Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
			SysFreeString(bstStr);

			hr = ((CIndexEx) *m_pPlayer)->get_MediaFileName( &bstStr );
			if(FAILED(hr) )
			{
				m_pPlayer->ReleaseIndex();
				MessageBox(_T("Unable to read Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
			}
			
			CString fn_idx	= dlg.GetPathName();
			CString fn_mpg	= bstStr;
			int pos1		= fn_idx.ReverseFind( '\\');
			
			TCHAR csFName[_MAX_PATH];
			_tcscpy( csFName, fn_idx.Left( pos1 ) );
			_tcscat( csFName, ( fn_mpg + "" ) );
						
			m_pPlayer->SetInput( csFName );	
			m_edFileName.SetWindowText( csFName );
			SysFreeString( bstStr );
		}
		else
		{
			// means we try to open not an index file
			// we should index it if the file is AVC HD
			// and shouldnt index if it is an MP4
			m_edFileName.SetWindowText( dlg.GetPathName() );
			m_pPlayer->SetInput( dlg.GetPathName() );	

			if( m_ftFileType != SMM_File_Type_MP4 && m_ftFileType != SMM_File_Type_MKV )
			{
				CString strFileName;
				if( strcmp( T2A(tcsIndexName), T2A( dlg.GetPathName() ) ) != 0 )
				{
					CDlgIndexing dlgInd(this, &hr);
					dlgInd.SetMPEG2Profile( m_csProfile );//Set Profile configuration
					if( FAILED(hr) )
						MessageBox(_T("Unable to create file indexator"), _T("Error"), MB_OK | MB_ICONWARNING);
					else 
					{
						strFileName = m_pPlayer->GetInput();

						//set opened file as input
						hr = dlgInd.SetInputFile( strFileName );

						if ( SUCCEEDED(hr) )
						{
							strFileName = tcsIndexName;

							//set file with .mlmix extension as output
							hr = dlgInd.SetOutputIndexFile( strFileName );
							int res = IDOK;
							if ( SUCCEEDED( hr ) )
								res = dlgInd.DoModal();
							else
								MessageBox(_T("Unable to set Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
							//if indexation was not complete delete the incomplete index file
							//to prevent locking it in put_IndexFileName
							if( res != IDOK )
								DeleteFile( strFileName );
						}
					}
				}
				if( strFileName.GetLength() )
				{
					BSTR pStr = strFileName.AllocSysString();
					hr = ((CIndexEx) *m_pPlayer)->put_IndexFileName( pStr );
					if(FAILED(hr) )
					{
						m_pPlayer->ReleaseIndex();
						MessageBox(_T("Unable to open Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
					}
					SysFreeString( pStr );
				
					hr = ((CIndexEx) *m_pPlayer)->get_MediaFileName( &pStr );
					if(FAILED(hr) )
					{
						m_pPlayer->ReleaseIndex();
						MessageBox(_T("Unable to read Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
					}
					SysFreeString( pStr );
				}
			}
			else
			{
				m_pPlayer->SetFileType( m_ftFileType );
			}
		}
		if( SUCCEEDED( hr = m_pPlayer->Init() ) )
		{
			m_sldPosition.EnableWindow(TRUE);
			m_sldPosition.SetPos(0);
			m_sldPosition.SetSelection(0,0);
			
			hr = m_pPlayer->SetPosition(0);
			hr = m_pPlayer->Pause();
			
			OnBegin();

			m_pPlayer->SubscribeEvent(EC_IDLE, this);
			m_pPlayer->SubscribeEvent(EC_COMPLETE, this);

			SetForegroundWindow();
			
		}
		else
		{
			m_edFileName.SetWindowText(_T(""));
			CString str;
			str.Format(_T("0x%X"),hr);
			MessageBox( str, _T("Error"), MB_OK);
		}
		EnableButtons( EnablingInitedPlayer,TRUE );
		if( m_ftFileType == SMM_File_Type_MP4 || m_ftFileType == SMM_File_Type_MKV )
		{
			m_CheckUseIndex.SetCheck( BST_UNCHECKED );
			m_CheckVideoOnly.SetCheck( BST_UNCHECKED );
			m_CheckUseIndex.EnableWindow( FALSE );
			m_CheckVideoOnly.EnableWindow( FALSE );
		}
		else
		{
			m_CheckUseIndex.SetCheck( BST_CHECKED );
			m_CheckVideoOnly.SetCheck( BST_UNCHECKED );
		}
		m_ctlList.ResetContent();
	}
}

void CSimplePlayerDlg::OnFullscreen()
{
	if ( m_pPlayer && m_pPlayer->IsInitialized() ) 
	{
		m_pPlayer->SetFullscreenMode( !m_pPlayer->IsFullscreenMode(), (OAHWND) this->m_hWnd );
		if( !m_pPlayer->IsFullscreenMode() )
			SetForegroundWindow();
	}
}

void CSimplePlayerDlg::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	int minpos = 0, maxpos = 0;
	
	m_sldPosition.GetRange(minpos, maxpos);
	
	REFERENCE_TIME rtPos, rtDuration = m_pPlayer->GetDuration();

   if ((nSBCode == TB_PAGEDOWN) || (nSBCode == TB_PAGEUP))
   {
      POINT pt;
      RECT Rect, Rect1;
      ::GetCursorPos(&pt);
      ::GetWindowRect(m_hWnd, & Rect1);
      int t = pt.x - Rect1.left;

      m_sldPosition.GetChannelRect(&Rect);
      int tmp = int((double) maxpos * ((double) (t) - 15) / ((double) (Rect.right - Rect.left)));
      m_sldPosition.SetPos(tmp);
   }

   int pos = m_sldPosition.GetPos();
   
   if(rtDuration != MAXLONGLONG)
	{
		rtPos = ( REFERENCE_TIME )( ( (REFERENCE_TIME)pos * rtDuration ) / (maxpos - minpos) );

		m_pPlayer->SetPosition( rtPos );

		rtPos = m_pPlayer->GetPosition();
	}

   if (m_pPlayer->CurrentGraphState() == graphStopped)
   {
      m_pPlayer->Pause();
   }

	EnableButtonForPosition();
}

void CSimplePlayerDlg::TimeFormat(REFERENCE_TIME rtTime, CString& sTime)
{
	REFERENCE_TIME rtT = rtTime / (ONE_SEC / 100);
	
	UINT msec = (UINT)(rtT % 100);	rtT = rtT / 100;	
	UINT sec =	(UINT)(rtT % 60);	rtT = rtT / 60;
	UINT minute = (UINT)(rtT % 60);	rtT = rtT / 60;
	UINT hour = (UINT)rtT;	

	sTime.Format(_T("%.2d:%.2d:%.2d:%.2d"), hour, minute, sec, msec);
}

HRESULT CSimplePlayerDlg::OnEvent(long levCode, long lparam1 /* = MAXLONG */, long lparam2 /* = MAXLONG */)
{
	HRESULT hr = S_OK;

	switch(levCode) 
	{
	case EC_IDLE:
		break;

	case EC_COMPLETE:
		OnStop();
		break;

	default:
		hr = S_OK;
	}
	return hr;
}

HRESULT CSimplePlayerDlg::CTrimNotify ::OnEvent( long levCode, long lparam1 , long lparam2 )
{
	switch( levCode ) 
	{
	case EC_START:	
		m_pDlg->m_TimerTrim = m_pDlg->SetTimer( TRIM_TIMER, 200, NULL );
		m_pDlg->m_Progress.SetPos( 0 );
		m_pDlg->EnableButtons( EnablingTrimingOn, FALSE );
		
		break;

	case EC_COMPLETE:	
		m_pDlg->OnCompleteTrimming();
		break;


	case EC_STOP:
		CTrimNotify::OnEvent( EC_COMPLETE );
		break;

	default:
		break;
	}
	return S_OK;
}

void CSimplePlayerDlg::OnCompleteTrimming()
{
	ASSERT(m_pTrimGraph);
	KillTimer( m_TimerTrim );
	m_Progress.SetPos( 0 );
	EnableButtons( EnablingTrimingOff, TRUE );
	if( m_ftFileType == SMM_File_Type_MP4 || m_ftFileType == SMM_File_Type_MKV )
	{
		m_CheckUseIndex.EnableWindow( FALSE );
		m_CheckVideoOnly.EnableWindow( FALSE );
	}
}

void CSimplePlayerDlg::EnableButtonForPosition()
{
	CString csFileName;
	m_edFileName.GetWindowText(csFileName);
	
	if(csFileName.GetLength()== 0)
	{
		for(UINT i = buttonBegin; i < buttonNum; i++)
		{
			if( i != buttonOpen)
				m_Buttons[i].EnableWindow(FALSE);
		}
		
		return;
	}

	m_Buttons[buttonMarkLeft].EnableWindow(TRUE);
	m_Buttons[buttonMarkRight].EnableWindow(TRUE);
	m_Buttons[buttonSave].EnableWindow(TRUE);
	m_Buttons[buttonAdd].EnableWindow(TRUE);
	m_Buttons[buttonRemove].EnableWindow(TRUE);

	int minpos = 0, maxpos = 0;
	int pos = m_sldPosition.GetPos();
	m_sldPosition.GetRange(minpos, maxpos);	
	
	if(pos == minpos)
	{
		m_Buttons[buttonBegin].EnableWindow(FALSE);
		m_Buttons[buttonStepBW].EnableWindow(FALSE);

		m_Buttons[buttonPlay].EnableWindow(TRUE);
		m_Buttons[buttonPause].EnableWindow(TRUE);
		m_Buttons[buttonStop].EnableWindow(TRUE);

		m_Buttons[buttonStepFW].EnableWindow(TRUE);
		m_Buttons[buttonEnd].EnableWindow(TRUE);
	}

	if(pos == maxpos)
	{
		m_Buttons[buttonBegin].EnableWindow(TRUE);
		m_Buttons[buttonStepBW].EnableWindow(TRUE);
		
		m_Buttons[buttonPlay].EnableWindow(FALSE);
		m_Buttons[buttonPause].EnableWindow(FALSE);
		m_Buttons[buttonStop].EnableWindow(TRUE);
		
		m_Buttons[buttonStepFW].EnableWindow(FALSE);
		m_Buttons[buttonEnd].EnableWindow(FALSE);
	}

	if(pos > minpos && pos < maxpos)
	{
		m_Buttons[buttonBegin].EnableWindow(TRUE);
		m_Buttons[buttonStepBW].EnableWindow(TRUE);
		
		m_Buttons[buttonPlay].EnableWindow(TRUE);
		m_Buttons[buttonPause].EnableWindow(TRUE);
		m_Buttons[buttonStop].EnableWindow(TRUE);
		
		m_Buttons[buttonStepFW].EnableWindow(TRUE);
		m_Buttons[buttonEnd].EnableWindow(TRUE);
	}
}

void CSimplePlayerDlg::OnBnClickedSave()
{
	TCHAR csext[_MAX_EXT] = {0};
	_tsplitpath(m_pPlayer->GetInput(),NULL, NULL, NULL, csext); 
	CString csExt(csext);
	csExt.Delete(0);
	CString csFilter;
	csFilter.Format( _T("%s Files (*.%s)|*.%s;|All Files (*.*)|*.*||"), csExt, csExt, csExt);

	CFileDialog dlg(FALSE, csExt, _T("Noname"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, csFilter, this);

	if( dlg.DoModal() == IDOK )
	{
		RedrawWindow();

		m_edFileNameSave.SetWindowText(dlg.GetPathName());		
	}
}

void CSimplePlayerDlg::OnBnClickedMark()
{
}

void CSimplePlayerDlg::OnBnClickedIndex()
{
}

void CSimplePlayerDlg::OnBnClickedAdd()
{
	USES_CONVERSION;
	if( m_FragmentParams.rtLeftTime == m_FragmentParams.rtRightTime )
	{
		MessageBox(_T(" Please select a video fragment to be removed"), _T("Warning"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	
	__TSTrimInfo ti = {0, m_FragmentParams.rtLeftTime, m_FragmentParams.rtRightTime}; 
	CHAR scTime[100];
	ConvertTime2String( ti, scTime );
	int nSel = 0;
	
	//no item is selected
	if( LB_ERR == ( nSel = m_ctlList.GetCurSel() ) )
		m_ctlList.AddString( A2CT(scTime) );
	else
	{
		m_ctlList.DeleteString( nSel);
		m_ctlList.InsertString( nSel, A2CT(scTime) );
	}
}

void CSimplePlayerDlg::OnBnClickedRemove()
{
	CString time;
	int nSelPos = 0;
	USES_CONVERSION;
	if( LB_ERR == ( nSelPos = m_ctlList.GetCurSel() ) )
		return;
	
	m_ctlList.GetText( nSelPos, time );
	m_ctlList.DeleteString( nSelPos );
	m_ctlList.SetCurSel( nSelPos );

	REFERENCE_TIME rtLeftTime	= ConvertString2Time( T2A( time ) );
	time.Delete( 0, 15 );
	REFERENCE_TIME rtRightTime	= ConvertString2Time( T2A( time ) );
	
	
	if( rtLeftTime  == m_FragmentParams.rtLeftTime &&
		rtRightTime == m_FragmentParams.rtRightTime )
	{
		m_FragmentParams.rtRightTime	  = m_FragmentParams.rtLeftTime; 
		m_FragmentParams.nSldrSelPosRight = m_FragmentParams.nSldrSelPosLeft;
	}

	m_sldPosition.SetSelection( m_FragmentParams.nSldrSelPosLeft, m_FragmentParams.nSldrSelPosRight );
	m_sldPosition.SetPos( m_FragmentParams.nSldrSelPosLeft );
	m_sldPosition.RedrawWindow();

}

void CDlgIndexing::OnBnClickedCancel()
{
	KillTimer(m_IndexTimer);
	m_IndexTimer = 0;
	
	VARIANT var = {0};
	var.vt		= VT_BOOL;
	var.boolVal = FALSE;
	HRESULT hr = m_pIModuleConfig->SetValue( &SMAT_StartIndexation, &var );

	OnCancel();
}

void CSimplePlayerDlg::OnBnClickedMarkRight()
{
	int nPos		= m_sldPosition.GetPos();
	int nLeftBound	= 0;
	int nRightBound = 0;
	
	m_sldPosition.GetSelection( nLeftBound, nRightBound );
	
	m_FragmentParams.nSldrSelPosRight = nPos;	
	
	m_FragmentParams.rtRightTime = m_pPlayer->GetPosition();

	if( nPos < nLeftBound )
	{
		m_FragmentParams.rtLeftTime = 
		m_FragmentParams.rtRightTime;

		m_FragmentParams.nSldrSelPosRight = 
		m_FragmentParams.nSldrSelPosLeft  = nPos;
	}
		
	m_sldPosition.SetSelection( m_FragmentParams.nSldrSelPosLeft, m_FragmentParams.nSldrSelPosRight );
	m_sldPosition.UpdateWindow();
	m_sldPosition.RedrawWindow();
}

void CSimplePlayerDlg::OnBnClickedMarkLeft()
{
	int nPos		= m_sldPosition.GetPos();
	int nLeftBound	= 0;
	int nRightBound = 0;

	m_sldPosition.GetSelection( nLeftBound, nRightBound );

	m_FragmentParams.nSldrSelPosLeft =  nPos;	

	m_FragmentParams.rtLeftTime =  m_pPlayer->GetPosition();

	if( nPos > nRightBound ) 
	{
		m_FragmentParams.rtRightTime = 
		m_FragmentParams.rtLeftTime;  

		m_FragmentParams.nSldrSelPosRight = 
		m_FragmentParams.nSldrSelPosLeft  = nPos;
	}
	m_sldPosition.SetSelection( m_FragmentParams.nSldrSelPosLeft, m_FragmentParams.nSldrSelPosRight );
	m_sldPosition.UpdateWindow();
	m_sldPosition.RedrawWindow();
}

void CSimplePlayerDlg::OnLbnSelchangeList()
{
}

void CSimplePlayerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSimplePlayerDlg::OnLbnDblclkList()
{
	CString time;
USES_CONVERSION;
	int pos				 = m_ctlList.GetCurSel();
	REFERENCE_TIME rtDur = m_pPlayer->GetDuration();
	int nLeftBound	= 0;
	int nRightBound = 0;

	m_ctlList.GetText( pos, time );

	m_FragmentParams.rtLeftTime			= ConvertString2Time( T2A( time ) );
	m_FragmentParams.nSldrSelPosLeft	= UINT( ( m_FragmentParams.rtLeftTime * 1000 ) / rtDur );
	time.Delete( 0, 15 );
	m_FragmentParams.rtRightTime		= ConvertString2Time( T2A( time ) );
	m_FragmentParams.nSldrSelPosRight	= UINT( ( m_FragmentParams.rtRightTime * 1000 ) / rtDur );

	m_sldPosition.GetSelection( nLeftBound, nRightBound );
	
	REFERENCE_TIME rtCurPos = m_pPlayer->GetPosition();

	if( rtCurPos	== m_FragmentParams.rtLeftTime &&
		nLeftBound	== m_FragmentParams.nSldrSelPosLeft&&
		nRightBound	== m_FragmentParams.nSldrSelPosRight )
	{
		rtCurPos  = m_FragmentParams.rtRightTime;
		m_sldPosition.SetPos(m_FragmentParams.nSldrSelPosRight );
	}
	else
	{
		rtCurPos  = m_FragmentParams.rtLeftTime;
		m_sldPosition.SetPos(m_FragmentParams.nSldrSelPosLeft);
	}

	m_pPlayer->SetPosition( rtCurPos  );

	m_sldPosition.SetSelection( m_FragmentParams.nSldrSelPosLeft , m_FragmentParams.nSldrSelPosRight );
	m_sldPosition.RedrawWindow();
}

void CSimplePlayerDlg::OnBnClickedTrim()
{
	KillTrimmingGraph();
	USES_CONVERSION;
	int nCount = m_ctlList.GetCount();
	HRESULT hr = S_OK;
	//means there is no fragment to be cut off

	CString str;
	CString str_orig = "STOP";
	m_Buttons[buttonTrim].GetWindowText(str);
	
	if(str_orig == str){
		hr = m_pTrimGraph->StopManual();
		return ;
	}

	__TSTrimInfo ti = {0};
	TLTrimInfo frm_list;

	if ( nCount == 0) // we deal with one fragment that was not inserted to a list 
	{
		if( m_FragmentParams.rtLeftTime == m_FragmentParams.rtRightTime )
		{
			MessageBox(_T(" Please select a video fragment to be trimmed "), _T("Warning"), MB_OK | MB_ICONINFORMATION);
			return;
		}
		
		ti.llStartPos	= m_FragmentParams.rtLeftTime;
		ti.llStopPos	= m_FragmentParams.rtRightTime;
		frm_list.push_back( ti );
	}
	else  // we deal with a list of fragments
	{
		for( int t = 0; t < nCount; t++ )
		{
			CString time_text;
			m_ctlList.GetText(t,time_text);
			ConvertString2Time( T2A(time_text) );

			ti.llStartPos	= ConvertString2Time( T2A(time_text) );
			int ind = time_text.Find(L" - ");
			ti.llStopPos	= ConvertString2Time( T2A(time_text.Right(ind)) );

			frm_list.push_back(ti);
		}
	}

	ProfileParser & parser = ProfileParser::Instance(m_csProfile);
	GUID codecGUID = parser.GetFilterCLSID( ProfileParser::Id_IndexReader, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	m_pTrimGraph = new CTrimGrpah( parser.GetFltrSlntPath( slntPath, codecGUID ) );

	ASSERT( m_pTrimGraph != NULL );
	CString tmp;
	m_edFileNameSave.GetWindowText( tmp );
	if(	tmp.IsEmpty() )
	{
		OnBnClickedSave();
		m_edFileNameSave.GetWindowText( tmp );
		if(	tmp.IsEmpty() )
		{
			MessageBox(_T(" Please specify an output file before"), _T("Error"), MB_OK | MB_ICONINFORMATION);
			return;
		}
	}
	m_pTrimGraph->SetOutput( tmp );

#ifdef COMPILE_VARIANT_ENGINE_USING
		m_pTrimGraph->SetCBInterface(&m_xCTrimmerObjControlCB);
#endif 
		m_pTrimGraph->SetTrimParams( frm_list );
		m_pTrimGraph->SetInput( m_pPlayer->GetInput() );

		if( BST_CHECKED == m_CheckUseIndex.GetCheck() && (m_ftFileType != SMM_File_Type_MP4) && (m_ftFileType != SMM_File_Type_MKV) )
		{
			ProfileParser & parser = ProfileParser::Instance(m_csProfile);
			GUID codecGUID = parser.GetFilterCLSID( ProfileParser::Id_IndexReader, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
			CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );

			CString str;
			m_edFileName.GetWindowText( str );
			TCHAR tcsIndexName[_MAX_PATH];
			setExtension( str, tcsIndexName);
			BSTR bstName = T2BSTR(tcsIndexName);
			hr = ((CIndexEx) *m_pTrimGraph)->put_IndexFileName( bstName );
			SysFreeString( bstName );
		}
		
		if( BST_CHECKED == m_CheckVideoOnly.GetCheck() )
			m_pTrimGraph->SetOutFormat( SMM_File_Type_MPEG2_VES );
		else
		{
			if( SMM_File_Type_MP4 == m_ftFileType )
				m_pTrimGraph->SetOutFormat( SMM_File_Type_MP4 );
			else if( m_ftFileType == SMM_File_Type_MKV )
				m_pTrimGraph->SetOutFormat( SMM_File_Type_MKV );
			else
				m_pTrimGraph->SetOutFormat( SMM_File_Type_MPEG2_TS );
		}
		
		hr = m_pTrimGraph->Init();
		if(FAILED(hr))
		{
			MessageBox(_T(" Trimming process can't be started 1"), _T("Error"), MB_OK | MB_ICONINFORMATION);
			return;
		}

		m_pTrimGraph->SubscribeEvent( EC_COMPLETE, &m_TrimNotify );
		m_pTrimGraph->SubscribeEvent( EC_STOP, &m_TrimNotify );
		m_pTrimGraph->SubscribeEvent( EC_START, &m_TrimNotify );

		hr = m_pTrimGraph->Run();
		if(FAILED(hr))
		{
			MessageBox(_T(" Trimming process can't be started 2"), _T("Error"), MB_OK | MB_ICONINFORMATION);
			return;
		}
		
}

void CSimplePlayerDlg::OnTimer(UINT nIDEvent)
{
	__super::OnTimer(nIDEvent);

	if( nIDEvent == TRIM_TIMER )
	{
		short shProgress = 0;

#ifdef COMPILE_VARIANT_ENGINE_USING
		UINT n = m_pTrimGraph->GetEditEngineProgress();
		TRACE("Trimming progress: %d\n",n);
		m_Progress.SetPos( n * PROGRESS_RANGE/100 );
		return;
#endif 

		REFERENCE_TIME rtDur = m_pTrimGraph->m_rtListDuration;
		rtDur = (rtDur == 0) ? 1 : rtDur ;

		REFERENCE_TIME rtPos = m_pTrimGraph->GetMuxerPosition();

		int pos = int((( rtPos * PROGRESS_RANGE ) / rtDur));
		m_Progress.SetPos( pos );
		GraphState state;

		if( graphStopped == (state = m_pTrimGraph->CurrentGraphState() ) )
			m_Progress.SetPos( 0 );
	}
	if( nIDEvent == MAIN_TIMER )
	{
		if( m_pPlayer->IsInitialized() )
		{
			int minpos = 0, maxpos = 0;
			int pos = m_sldPosition.GetPos();
			m_sldPosition.GetRange(minpos, maxpos);

			CString sValue, sVal;
			REFERENCE_TIME	rtPos		= m_pPlayer->GetPosition(),
							rtDuration	= m_pPlayer->GetDuration();

			if( rtPos != MAXLONGLONG )
			{
				TimeFormat(rtPos, sValue);
				m_Time.GetWindowText(sVal);
				if(sVal != sValue)
					m_Time.SetWindowText(sValue);

				if( rtDuration != MAXLONGLONG )
				{
					int newpos = (int)(((double)(maxpos - minpos) * rtPos) / rtDuration);
					if(pos != newpos)
						m_sldPosition.SetPos(newpos);
				}
			}

			if(rtDuration != MAXLONGLONG)
			{
				TimeFormat(rtDuration, sValue);
				m_Duration.GetWindowText(sVal);
				if(sVal != sValue)
					m_Duration.SetWindowText(sValue);
			}			
		}
	}
}

void CSimplePlayerDlg::EnableButtons(EnablingType EnType, BOOL bEnable)
{
	switch (EnType)
	{
	case EnablingInitedDialog:
		{
			bEnable = FALSE;
			m_Buttons[buttonSave].EnableWindow(bEnable);

			m_Buttons[buttonBegin].EnableWindow(bEnable);
			m_Buttons[buttonStepBW].EnableWindow(bEnable);
			m_Buttons[buttonPlay].EnableWindow(bEnable);
			m_Buttons[buttonPause].EnableWindow(bEnable);
			m_Buttons[buttonStop].EnableWindow(bEnable);
			m_Buttons[buttonStepFW].EnableWindow(bEnable);
			m_Buttons[buttonEnd].EnableWindow(bEnable);

			m_Buttons[buttonMarkLeft].EnableWindow(bEnable);
			m_Buttons[buttonMarkRight].EnableWindow(bEnable);

			m_Buttons[buttonTrim].EnableWindow(bEnable);
			m_Buttons[buttonAdd].EnableWindow(bEnable);
			m_Buttons[buttonRemove].EnableWindow(bEnable);

			m_ctlList.EnableWindow(bEnable);
			m_sldPosition.EnableWindow(bEnable);

			m_CheckUseIndex.EnableWindow(bEnable);
			m_CheckVideoOnly.EnableWindow(bEnable);

		}
		break;

	case EnablingInitedPlayer :
		{
			bEnable = TRUE;
			m_Buttons[buttonSave].EnableWindow(bEnable);
            m_Buttons[buttonOpen].EnableWindow(bEnable);

			m_Buttons[buttonBegin].EnableWindow(bEnable);
			m_Buttons[buttonStepBW].EnableWindow(bEnable);
			m_Buttons[buttonPlay].EnableWindow(bEnable);
			m_Buttons[buttonPause].EnableWindow(bEnable);
			m_Buttons[buttonStop].EnableWindow(bEnable);
			m_Buttons[buttonStepFW].EnableWindow(bEnable);
			m_Buttons[buttonEnd].EnableWindow(bEnable);
			m_Buttons[buttonMarkLeft].EnableWindow(bEnable);
			m_Buttons[buttonMarkRight].EnableWindow(bEnable);
			m_Buttons[buttonTrim].EnableWindow(bEnable);

			m_sldPosition.EnableWindow(bEnable);
			m_ctlList.EnableWindow(bEnable);

			m_CheckUseIndex.EnableWindow(bEnable);
			m_CheckVideoOnly.EnableWindow(bEnable);
		}

		break;

	case EnablingSelectedFragment:
		bEnable = TRUE;
		m_ctlList.EnableWindow(bEnable);
		break;

	case EnablingTrimingOn:
		{

			EnableButtons( EnablingInitedDialog, FALSE );
			m_Buttons[buttonOpen].EnableWindow( FALSE );
			m_Buttons[buttonTrim].EnableWindow( TRUE );
			m_Buttons[buttonTrim].SetWindowText(_T("STOP") );
			
		}
		break;

	case EnablingTrimingOff:
		{
			EnableButtons( EnablingInitedPlayer, TRUE );

			m_Buttons[buttonMarkLeft].EnableWindow(TRUE);
			m_Buttons[buttonMarkRight].EnableWindow(TRUE);

			m_Buttons[buttonAdd].EnableWindow(TRUE);
			m_Buttons[buttonRemove].EnableWindow(TRUE);
			
			m_Buttons[buttonTrim].SetWindowText(_T("TRIM") );
		}
		break;
	}
}

//
// ITrimmerObjControlCB callback interface implementation for CSimplePlayerDlg
//
BEGIN_INTERFACE_MAP(CSimplePlayerDlg, CDialog)
	INTERFACE_PART(CSimplePlayerDlg, IID_ITrimmerObjControlCB, CTrimmerObjControlCB)
END_INTERFACE_MAP()


STDMETHODIMP_(HRESULT) CSimplePlayerDlg::XCTrimmerObjControlCB::OnStop()
{ 
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);

	((IEventNotify*)(&pThis->m_TrimNotify))->OnEvent(EC_STOP);
	return S_OK;
}

STDMETHODIMP_(HRESULT) CSimplePlayerDlg::XCTrimmerObjControlCB::OnStart()
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);
	((IEventNotify*)(&pThis->m_TrimNotify))->OnEvent(EC_START);
	return S_OK;	
}

STDMETHODIMP_(HRESULT )CSimplePlayerDlg::XCTrimmerObjControlCB::OnPause()
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);

	return S_OK;	
}

STDMETHODIMP_(HRESULT )CSimplePlayerDlg::XCTrimmerObjControlCB::OnError (HRESULT hr, BSTR Val)
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);

	CString str = Val;
	pThis->MessageBox(str, _T("Editing Engine Error") );

	return S_OK;
}

STDMETHODIMP_(ULONG )CSimplePlayerDlg::XCTrimmerObjControlCB::AddRef()
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)CSimplePlayerDlg::XCTrimmerObjControlCB::Release()
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);
	return pThis->ExternalRelease();
}

STDMETHODIMP_(HRESULT)CSimplePlayerDlg::XCTrimmerObjControlCB::QueryInterface( REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CSimplePlayerDlg,CTrimmerObjControlCB);
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

//
// ITrimmerObjControlCB callback interface implementation for CDlgIndexing
//
BEGIN_INTERFACE_MAP(CDlgIndexing, CDialog)
	INTERFACE_PART(CDlgIndexing, IID_ITrimmerObjControlCB, CTrimmerObjControlCB)
END_INTERFACE_MAP()


STDMETHODIMP_(HRESULT) CDlgIndexing::XCTrimmerObjControlCB::OnStop()
{ 
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	pThis->SetFinishedIndexing( TRUE );
	return S_OK;
}

STDMETHODIMP_(HRESULT) CDlgIndexing::XCTrimmerObjControlCB::OnStart()
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	pThis->SetFinishedIndexing( FALSE );
	return S_OK;	
}

STDMETHODIMP_(HRESULT )CDlgIndexing::XCTrimmerObjControlCB::OnPause()
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	return S_OK;	
}

STDMETHODIMP_(HRESULT )CDlgIndexing::XCTrimmerObjControlCB::OnError (HRESULT hr, BSTR Val)
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	pThis->SetFinishedIndexing( TRUE );
	CString str = Val;
	pThis->MessageBox(str, _T("Editing Engine Error") );
	return S_OK;
}

STDMETHODIMP_(ULONG )CDlgIndexing::XCTrimmerObjControlCB::AddRef()
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)CDlgIndexing::XCTrimmerObjControlCB::Release()
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	return pThis->ExternalRelease();
}

STDMETHODIMP_(HRESULT)CDlgIndexing::XCTrimmerObjControlCB::QueryInterface( REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CDlgIndexing,CTrimmerObjControlCB);
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}