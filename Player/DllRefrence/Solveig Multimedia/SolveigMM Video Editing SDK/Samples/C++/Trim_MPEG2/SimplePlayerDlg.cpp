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
#include "IndexingDlg.h"
#include ".\simpleplayerdlg.h"

#define MAIN_TIMER			1
#define TRIM_TIMER			3

#define PROGRESS_RANGE		100

IMPLEMENT_DYNCREATE(CSMMSliderCtrlWrap, CWnd)
void setExtension(LPCTSTR tcsFile, LPTSTR tcsIndex)
{
	TCHAR tcsDrive[_MAX_DRIVE];
	TCHAR tcsDir[_MAX_DIR];
	TCHAR tcsFName[_MAX_FNAME];
	TCHAR tcsExt[_MAX_EXT];

	_tsplitpath(tcsFile, tcsDrive, tcsDir, tcsFName, tcsExt);
	_tmakepath(tcsIndex, tcsDrive, tcsDir, tcsFName, _T(".mlmix"));
}





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
	m_csProfile.SetString( Default_Codecs_Profile );
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	ProfileParser & parser = ProfileParser::Instance(m_csProfile);
	GUID codecGUID = parser.GetFilterCLSID( ProfileParser::Id_IndexReader, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	m_pPlayer		= new CPlayer( parser.GetFltrSlntPath( slntPath, codecGUID ) );
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
	DDX_Control(pDX, IDC_TIME_BEGIN,		m_BeginTime );
	DDX_Control(pDX, IDC_TIME_END,		m_EndTime );

	DDX_Control(pDX, IDC_PROGRESS,			m_Progress);
	DDX_Control(pDX, IDC_CHECK_INDEX,		m_CheckUseIndex);
	DDX_Control(pDX, IDC_CHECK_VIDEO_ONLY,	m_CheckVideoOnly);
	
	DDX_Control(pDX, IDC_DURATION,		m_Duration);
	DDX_Control(pDX, IDC_SMMSLIDERCTRL,		m_sliderCtrl);
	
	DDX_Control(pDX, IDC_ED_FILE,		m_edFileName);	
	DDX_Control(pDX, IDC_ED_FILE_SAVE,	m_edFileNameSave);	
	

	DDX_Control(pDX, IDC_BEGIN,			m_Buttons[buttonBegin]);
	DDX_Control(pDX, IDC_STEPBW,		m_Buttons[buttonStepBW]);
	DDX_Control(pDX, IDC_PLAY,			m_Buttons[buttonPlay]);
	DDX_Control(pDX, IDC_PAUSE,			m_Buttons[buttonPause]);
	DDX_Control(pDX, IDC_STOP,			m_Buttons[buttonStop]);
	DDX_Control(pDX, IDC_STEPFW,		m_Buttons[buttonStepFW]);
	DDX_Control(pDX, IDC_END,			m_Buttons[buttonEnd]);	
	DDX_Control(pDX, IDC_OPEN,			m_Buttons[buttonOpen]);
	DDX_Control(pDX, IDC_SAVE,			m_Buttons[buttonSave]);
	DDX_Control(pDX, IDC_ADD,			m_Buttons[buttonAdd]);
	DDX_Control(pDX, IDC_REMOVE,		m_Buttons[buttonRemove]);
	DDX_Control(pDX, IDC_DESELECT_INTERVAL,		m_Buttons[buttonDesel]);
	DDX_Control(pDX, IDC_SELECT_INTERVAL,		m_Buttons[buttonSel]);

	DDX_Control(pDX, IDC_TRIM,			m_Buttons[buttonTrim]);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimplePlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CSimplePlayerDlg)
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
//	ON_BN_CLICKED(IDC_FULLSCREEN,	OnFullscreen)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnBnClickedRemove)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_TRIM, OnBnClickedTrim)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SELECT_INTERVAL, OnBnClickedSelectInterval)
	ON_BN_CLICKED(IDC_DESELECT_INTERVAL, OnBnClickedDeselectInterval)
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

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_SELINTERVAL));
	m_Buttons[buttonSel].SetIcon(hi);
	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_DESELINTERVAL));
	m_Buttons[buttonDesel].SetIcon(hi);

	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_ADD));
	m_Buttons[buttonAdd].SetIcon(hi);
	hi = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_REMOVE));
	m_Buttons[buttonRemove].SetIcon(hi);

	m_CheckUseIndex.SetCheck(BST_CHECKED);
	m_CheckVideoOnly.SetCheck(BST_UNCHECKED);

	EnableButtons( EnablingInitedDialog , FALSE );

	m_Progress.SetRange(0, PROGRESS_RANGE);

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
	
	if( m_pTrimGraph  && m_pTrimGraph ->IsInitialized())
	{
		m_pTrimGraph->Stop();
		m_pTrimGraph->Reset();
	}
	
	CDialog::OnCancel();
}

void CSimplePlayerDlg::OnBegin()
{
	if( m_FragmentParams.rtRightTime != m_FragmentParams.rtLeftTime )
	{
		m_pPlayer->SetPosition( m_FragmentParams.rtLeftTime );
		return;
	}
	
	m_pPlayer->SetPosition(0);

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
		return;
	}
	
	REFERENCE_TIME rtPos = m_pPlayer->GetDuration();
	
	if( rtPos != MAXLONGLONG )
		m_pPlayer->SetPosition( rtPos );

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

void CSimplePlayerDlg::OnOpen()
{
	static TCHAR szFilter[] = _T("Media Files | *.vob; *.mpg; *.mpeg; *.m2v;|Index files (*.mlmix)| *.mlmix| All Files (*.*)| *.*||");
	//Execute dialog
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY ,szFilter);
USES_CONVERSION;
	if ( dlg.DoModal() == IDOK )
	{
		RedrawWindow();
		
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
			if( FAILED(hr) )
				MessageBox(_T("Unable to open Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
			SysFreeString( bstStr );

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
			m_edFileName.SetWindowText( dlg.GetPathName() );
			m_pPlayer->SetInput( dlg.GetPathName() );	
		}
		// means we try to open not an index file
		// in this case we should index it
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
		hr = ((CIndexEx) *m_pPlayer)->put_IndexFileName( strFileName.AllocSysString() );
		if(FAILED(hr) )
		{
			m_pPlayer->ReleaseIndex();
			MessageBox(_T("Unable to open Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
		}

		BSTR pStr = NULL;
		hr = ((CIndexEx) *m_pPlayer)->get_MediaFileName( &pStr );
		if(FAILED(hr) )
		{
			m_pPlayer->ReleaseIndex();
			MessageBox(_T("Unable to read Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
		}
		SysFreeString( pStr );
		if( SUCCEEDED( hr = m_pPlayer->Init() ) )
		{
			
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
	m_edFileNameSave.SetWindowText(_T(""));
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
		if( m_pTrimGraph )
			m_pTrimGraph->SetOutput( dlg.GetPathName() );
	}
}


void CSimplePlayerDlg::OnBnClickedAdd()
{
	REFERENCE_TIME curPos = m_sliderCtrl.GetPos();
	m_sliderCtrl.AddMarker(curPos);
}

void CSimplePlayerDlg::OnBnClickedRemove()
{
	m_sliderCtrl.RemoveCurrentMarkers();
}
void CSimplePlayerDlg::OnBnClickedSelectInterval()
{
	long intervalNum = m_sliderCtrl.GetCurrentInterval();
	if (intervalNum >= 0)
		m_sliderCtrl.SetIntervalSelect(intervalNum);

}

void CSimplePlayerDlg::OnBnClickedDeselectInterval()
{
	long intervalNum = m_sliderCtrl.GetCurrentInterval();
	if (intervalNum >= 0)
		m_sliderCtrl.SetIntervalDeselect(intervalNum);	
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

void CSimplePlayerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSimplePlayerDlg::OnBnClickedTrim()
{
	KillTrimmingGraph();
	USES_CONVERSION;
	HRESULT hr = S_OK;

	//means there is no fragment to be cut off

	CString str;
	CString str_orig = "STOP";
	m_Buttons[buttonTrim].GetWindowText(str);
	
	if(str_orig == str){
		hr = m_pTrimGraph->StopManual();
		return ;
	}

	long nCount = m_sliderCtrl.GetIntervalsCount();
	__TSTrimInfo ti = {0};
	TLTrimInfo frm_list;
	for( int t = 0; t < nCount; t++ )
	{
		CInterval_info interval;
		VARIANT var;
		var.pbVal = (BYTE*)&interval;
		m_sliderCtrl.GetIntervalInfo(t, &var);
		if (interval.bselect)
		{
			ti.llStartPos	= interval.llstart;
			ti.llStopPos	= interval.llend;
			frm_list.push_back(ti);
		}
	}
	if (frm_list.size() == 0)
	{
		MessageBox(_T("Please Select at least one interval to save"), _T("Information"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	ProfileParser & parser = ProfileParser::Instance(m_csProfile);
	GUID codecGUID = parser.GetFilterCLSID( ProfileParser::Id_IndexReader, ProfileParser::prmCONTAINER, ProfileParser::cMPEG2);
	CString slntPath = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	m_pTrimGraph = new CTrimGrpah( parser.GetFltrSlntPath( slntPath, codecGUID ) );

	ASSERT( m_pTrimGraph != NULL );
	CString csTmp;
	m_edFileNameSave.GetWindowText(csTmp);
	if(	csTmp.IsEmpty() )
	{
		OnBnClickedSave();
		m_edFileNameSave.GetWindowText(csTmp);
	}
	if(	csTmp.IsEmpty() )
	{
		MessageBox(_T(" Please specify an output file before"), _T("Error"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	m_pTrimGraph->SetOutput( csTmp );

#ifdef COMPILE_VARIANT_ENGINE_USING
		m_pTrimGraph->SetCBInterface(&m_xCTrimmerObjControlCB);
#endif 
		m_pTrimGraph->SetTrimParams( frm_list );
		m_pTrimGraph->SetInput( m_pPlayer->GetInput() );

		if( BST_CHECKED == m_CheckUseIndex.GetCheck() )
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
			m_pTrimGraph->SetOutFormat(true);
		else
			m_pTrimGraph->SetOutFormat(false);
		
		hr = m_pTrimGraph->Init();
		if(FAILED(hr))
		{
			MessageBox(_T(" Trimming process can't be started "), _T("Error"), MB_OK | MB_ICONINFORMATION);
			return;
		}

		m_pTrimGraph->SubscribeEvent( EC_COMPLETE, &m_TrimNotify );
		m_pTrimGraph->SubscribeEvent( EC_STOP, &m_TrimNotify );
		m_pTrimGraph->SubscribeEvent( EC_START, &m_TrimNotify );

		hr = m_pTrimGraph->Run();
		if(FAILED(hr))
		{
			MessageBox(_T(" Trimming process can't be started "), _T("Error"), MB_OK | MB_ICONINFORMATION);
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
			
			CString sValue, sVal;
			REFERENCE_TIME	rtPos		= m_pPlayer->GetPosition(),
							rtDuration	= m_pPlayer->GetDuration();

			// update current pos and duration
			if( rtPos != MAXLONGLONG )
			{
				m_Time.EnableWindow(TRUE);
				TimeFormat(rtPos, sValue);
				m_Time.GetWindowText(sVal);
				if(sVal != sValue)
				{
					m_Time.SetWindowText(sValue);
				}

				if (rtPos != m_sliderCtrl.GetPos() && m_pPlayer->GetGraphState() == State_Running )
				{
					m_sliderCtrl.SetPos(rtPos);
				}
			}

			if(rtDuration != MAXLONGLONG)
			{
				m_Duration.EnableWindow(TRUE);
				TimeFormat(rtDuration, sValue);
				m_Duration.GetWindowText(sVal);
				if(sVal != sValue)
				{
					
					m_Duration.SetWindowText(sValue);
					m_sliderCtrl.SetRange(rtDuration);
				}
			}			
			// update current selected fragment positions
			long num = m_sliderCtrl.GetCurrentInterval();
			if( (num >= 0) && (num < m_sliderCtrl.GetIntervalsCount()) )
			{
				CInterval_info interval;
				VARIANT var;
				var.pbVal = (BYTE*)&interval;
				m_sliderCtrl.GetIntervalInfo(num, &var);
				TimeFormat(interval.llstart, sValue);
				m_BeginTime.GetWindowText(sVal);
				if (sVal != sValue)
					m_BeginTime.SetWindowText(sValue);
				TimeFormat(interval.llend, sValue);
				m_EndTime.GetWindowText(sVal);
				if (sVal != sValue)
					m_EndTime.SetWindowText(sValue);

				m_BeginTime.EnableWindow(TRUE);
				m_EndTime.EnableWindow(TRUE);
			}
			else
			{
				m_BeginTime.SetWindowText(_T("00:00:00"));
				m_EndTime.SetWindowText(_T("00:00:00"));
				m_BeginTime.EnableWindow(FALSE);
				m_EndTime.EnableWindow(FALSE);
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

			m_Buttons[buttonTrim].EnableWindow(bEnable);
			m_Buttons[buttonAdd].EnableWindow(bEnable);
			m_Buttons[buttonRemove].EnableWindow(bEnable);
			m_Buttons[buttonSel].EnableWindow(bEnable);
			m_Buttons[buttonDesel].EnableWindow(bEnable);

			m_CheckUseIndex.EnableWindow(bEnable);
			m_CheckVideoOnly.EnableWindow(bEnable);
			m_sliderCtrl.EnableWindow(bEnable);

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
			m_Buttons[buttonTrim].EnableWindow(bEnable);

			m_Buttons[buttonAdd].EnableWindow(bEnable);
			m_Buttons[buttonRemove].EnableWindow(bEnable);			
			m_Buttons[buttonSel].EnableWindow(bEnable);
			m_Buttons[buttonDesel].EnableWindow(bEnable);


			m_CheckUseIndex.EnableWindow(bEnable);
			m_CheckVideoOnly.EnableWindow(bEnable);
			m_sliderCtrl.EnableWindow(bEnable);
		}

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
			m_Buttons[buttonTrim].SetWindowText(_T("TRIM") );
		}
		break;
	}
}

//
// ITrimmerObjControlCB callback interface implementation
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

BEGIN_EVENTSINK_MAP(CSimplePlayerDlg, CDialog)
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 1, MarkerDownSmmsliderctrl, VTS_I4 )
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 5, MarkerMovedSmmsliderctrl, VTS_I4 )
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 3, MarkerMovingSmmsliderctrl, VTS_I4 )
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 2, SliderDownSmmsliderctrl, VTS_NONE)
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 6, SliderMovedSmmsliderctrl, VTS_NONE)
ON_EVENT(CSimplePlayerDlg, IDC_SMMSLIDERCTRL, 4, SliderMovingSmmsliderctrl, VTS_NONE)
END_EVENTSINK_MAP()

void CSimplePlayerDlg::MarkerDownSmmsliderctrl(long lMarkerNumber)
{
	// TODO: Add your message handler code here
}

void CSimplePlayerDlg::MarkerMovedSmmsliderctrl( long lMarkerNumber)
{
	// TODO: Add your message handler code here
}

void CSimplePlayerDlg::MarkerMovingSmmsliderctrl(long lMarkerNumber)
{
	REFERENCE_TIME rtPos = 0;
	m_sliderCtrl.GetMarkerPosition(lMarkerNumber, &rtPos);
	m_pPlayer->SetPosition(rtPos);
}

void CSimplePlayerDlg::SliderDownSmmsliderctrl()
{
	// TODO: Add your message handler code here
}

void CSimplePlayerDlg::SliderMovedSmmsliderctrl()
{
	// TODO: Add your message handler code here
}

void CSimplePlayerDlg::SliderMovingSmmsliderctrl()
{
	REFERENCE_TIME rtPos = m_sliderCtrl.GetPos();
	m_pPlayer->SetPosition(rtPos);
}
