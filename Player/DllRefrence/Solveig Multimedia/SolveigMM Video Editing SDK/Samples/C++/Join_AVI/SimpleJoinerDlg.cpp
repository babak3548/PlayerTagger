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
// SimpleJoinerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleJoiner.h"
#include "SimpleJoinerDlg.h"


#include "SMM_Utils.h"
#include "Parser.h"
#include ".\simplejoinerdlg.h"
#include "SMM_SDKActionKeys.h"

#define TIMER_EVENT_PROGRESS 0x20
#define TempFileName _T("~1.xtl")
#define MBWaringMsg _T("Joiner warning")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


UINT ProgressControl(LPVOID param)
{  
	CSimpleJoinerDlg*  pJoint=( CSimpleJoinerDlg* ) param;
	while( !(pJoint->m_bJointStopped) )
	{
		MSG msg;
		PeekMessage( &msg, 0, 0, 0, PM_REMOVE );
		DispatchMessage( &msg );
		Sleep( 5/*10*/);
	}

	pJoint->KillTimer( TIMER_EVENT_PROGRESS );
	pJoint->m_pProgress->ShowWindow( SW_HIDE );
	pJoint->m_pProgress->Reset();
	CMenu* pSysMenu = pJoint->GetSystemMenu( FALSE );
	pSysMenu->EnableMenuItem( SC_CLOSE, MF_BYCOMMAND|MF_ENABLED );
	pJoint->EnableWindow( TRUE );
	pJoint->ShowWindow( SW_SHOWNORMAL );
	pJoint->SetActiveWindow();
	Sleep(1000);
	pJoint->ResetTrimmerObject();

	return 0;
}
//-------------------------------CProgressDlg Dialog (Progress)
CProgressDlg::CProgressDlg(  ) : CDialog(CProgressDlg::IDD),
m_pITrimmerObjControl(NULL)
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
END_MESSAGE_MAP()

void CProgressDlg::UpdateProgress( int nPercent )
{
	if( nPercent <= 0 )
		return;
	m_pPrCtrl->SetPos( nPercent );
}

void CProgressDlg::OnCancel()
{
	if( m_pITrimmerObjControl )
	{
		m_pITrimmerObjControl->Stop();
	}
}

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pPrCtrl = (CProgressCtrl*)GetDlgItem( IDC_PROGRESS );
	Reset();

	return TRUE;
}

//----------------------------CAboutDlg dialog (About)
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
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()



//------------------------------- CSimpleJoinerDlg dialog (Main)
CString szCaptions[] =	{
							_T(" #"), 
							_T("Source file"), 
							_T("Type")
						};
int nWidth[] =			{
							25,
							340,
							45
						};

CSimpleJoinerDlg::CSimpleJoinerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleJoinerDlg::IDD, pParent),
	m_pListCtrl( 0 )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CSimpleJoinerDlg::~CSimpleJoinerDlg()
{
}

void CSimpleJoinerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimpleJoinerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPENFILE, OnFileOpenfile)
	ON_COMMAND(ID_FILE_SAVEJOINLIST, OnFileSaveList)
	ON_COMMAND(ID_FILE_STARTJOINING, OnFileStartJoining)
	ON_COMMAND(ID_LIST_CLEARLIST, OnListClearList)
	ON_COMMAND(ID_LIST_DELETESELECTEDITEMS, OnListDeleteSelected)
	ON_COMMAND(ID_LIST_MOVEDOWN, OnListMoveDown)
	ON_COMMAND(ID_LIST_MOVEUP, OnListMoveup)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP( CSimpleJoinerDlg, CDialog )
	INTERFACE_PART( CSimpleJoinerDlg, __uuidof(ITrimmerObjControlCB), CTrimmerObjControlCallB )
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG)CSimpleJoinerDlg::XCTrimmerObjControlCallB::AddRef()
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);

	return pThis->ExternalAddRef();

}
STDMETHODIMP_(ULONG)CSimpleJoinerDlg::XCTrimmerObjControlCallB::Release()
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);

	return pThis->ExternalRelease();
}

STDMETHODIMP_(HRESULT)CSimpleJoinerDlg::XCTrimmerObjControlCallB::QueryInterface( REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);

	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(HRESULT) CSimpleJoinerDlg::XCTrimmerObjControlCallB::OnStop()
{ 
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);
	
	pThis->m_bJointStopped = TRUE;
	return S_OK;
}

STDMETHODIMP_(HRESULT) CSimpleJoinerDlg::XCTrimmerObjControlCallB::OnStart()
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);
	return S_OK;	
}

STDMETHODIMP_(HRESULT )CSimpleJoinerDlg::XCTrimmerObjControlCallB::OnPause()
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);
	return S_OK;	
}

STDMETHODIMP_(HRESULT )CSimpleJoinerDlg::XCTrimmerObjControlCallB::OnError (HRESULT hr, BSTR Val)
{
	METHOD_PROLOGUE(CSimpleJoinerDlg, CTrimmerObjControlCallB);

	USES_CONVERSION;
	LPCTSTR StrVal = OLE2T(Val);

	CString str = _T("");
	str += StrVal;
	if( FAILED( hr ) && hr != 12345/*if operation canceled*/ )
		pThis->MessageBox( str, _T("SolveigMM Video Editing Engine error"), MB_ICONERROR );
	
	pThis->m_bJointStopped = TRUE;

	return S_OK;
}

// CSimpleJoinerDlg message handlers

BOOL CSimpleJoinerDlg::OnInitDialog()
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
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	CoInitialize( NULL );
	InitList();
	m_PrevWndFunc = (WNDPROC) GetWindowLong ( m_pListCtrl->GetSafeHwnd(), GWL_WNDPROC );
	SetWindowLong ( m_pListCtrl->GetSafeHwnd(), GWL_WNDPROC, (LONG) CSimpleJoinerDlg::ListWndProc);

	UpdateMenu();

	m_pProgress = new CProgressDlg;
	m_pProgress->Create( IDD_DIALOG_PROGRESS );

	if( FAILED( InitEngine() ) )
		MessageBox( _T("SMM_EditingEngine couldn't be initialized!"), MBWaringMsg );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleJoinerDlg::ResetTrimmerObject()
{
	if( m_pIModuleConfig )
	{
		m_pIModuleConfig.Release();
		m_pIModuleConfig = NULL;
	}
	if( m_pITrimmerObjControl )
	{
		if( !m_bJointStopped )
			Stop();
		m_bJointStopped = TRUE;
		m_pITrimmerObjControl.Release();
		m_pITrimmerObjControl = NULL;
	}
}

void CSimpleJoinerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( (nID == SC_CLOSE) && (lParam == NULL)  )
		return;

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

void CSimpleJoinerDlg::OnPaint() 
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
HCURSOR CSimpleJoinerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimpleJoinerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

}
void CSimpleJoinerDlg::InitList( void )
{
	m_pListCtrl = (CListCtrl*) GetDlgItem( IDC_FILE_LIST );
	if( !m_pListCtrl )
		return;

	m_pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP /*| LVS_EX_DOUBLEBUFFER*/ );

	m_nColumnsNumber = 3;//14;
	for( int i = 0; i < m_nColumnsNumber; i++ )
		m_pListCtrl->InsertColumn( i, szCaptions[i], LVCFMT_LEFT, nWidth[i] );
}
void CSimpleJoinerDlg::OnFileOpenfile()
{
	if( FAILED( InitEngine() ) )// InitEngine does nothing if already initialized
	{
		MessageBox( _T("SMM_EditingEngine couldn't be initialized!"), MBWaringMsg );	
		return;
	}
	USES_CONVERSION;
	CString file = _T("Media files (*.avi;*.asf;*.wmv;*.wma;*.wm;*.m2ts;*.h264;*.mp3;*.mp4;*.mkv;*.mov;*.mpa;*.mp1;*.mpg;*.mpeg;*.vob;*.wav)|*.avi;*.asf;*.wmv;*.wma;*.wm;*.m2ts;*.h264;*.mp3;*.mp4;*.mkv;*.mov;*.mpa;*.mp1;*.mpg;*.mpeg;*.vob;*.wav;|Video files (*.avi;*.asf;*.wmv;*.wm;*.mpg;*.mkv;*.mp4;*.mov;*.m2ts;*.h264;*.vob;)|*.avi;*.asf;*.wmv;*.wm;*.mpg;*.mkv;*.mp4;*.mov;*.m2ts;*.h264;*.vob;|Audio files (*.mp3;*.mpa;*.mp1;*.wma;*.wav;)|*.mp3;*.mpa;*.mp1;*.wma;*.wav;|Windows Media files (*.asf;*.wmv;*.wma;*.wm)|*.asf;*.wmv;*.wma;*.wm;|MPEG1 files (*.mpg;*.mpeg)|*.mpg;*.mpeg|MPEG2 files (*.mpg;*.vob)|*.mpg;*.vob|AVI files (*.avi)|*.avi|MKV files (*.mkv)|*.mkv|MP4 files (*.mp4)|*.mp4|MOV files (*.mov)|*.mov|AVC HD files (*.m2ts;*.h264;*.mpg;)|*.m2ts;*.h264;*.mpg;|WAVE files (*.wav)|*.wav;|All files (*.*)|*.*|");
	CString FileName;
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, file, this );

	dlg.GetOFN().lpstrFile = FileName.GetBuffer(80 * (_MAX_PATH + 1) + 1);
	dlg.GetOFN().nMaxFile = (80 * (_MAX_PATH + 1) + 1);

	HRESULT hr = S_OK;
	POSITION pos;

	int result = ( int )dlg.DoModal();

	DWORD er = CommDlgExtendedError();
	if( result == IDOK)
	{	
		file.ReleaseBuffer();
		pos = dlg.GetStartPosition();
	}else
		return;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	if( pos == NULL )
	{
		file = dlg.GetPathName();
		AppendList( file );
	}else
	{
		while( TRUE )
		{
			file = dlg.GetNextPathName( pos );
			AppendList( file );
			file.ReleaseBuffer();
			if( pos == NULL )
				break;
		}
	}
	file.ReleaseBuffer();
	FileName.ReleaseBuffer();
	SetCursor( LoadCursor(NULL, IDC_ARROW) );

	UpdateMenu();
}

void CSimpleJoinerDlg::AppendList( CString FileName )
{
	HRESULT hr;

	VARIANT val = {0};
	val.vt = VT_BSTR;
	val.bstrVal = FileName.AllocSysString();
	hr = m_pIModuleConfig->SetValue( &SMAT_InputFile, &val );
	hr = m_pIModuleConfig->GetValue( &SMAT_GetFileType, &val );
	if( FAILED(hr) )
		return;
	if( !CheckSupportedFileTypes( (SMM_OutputTypes)val.intVal ) )
		return;
	int nLastItem = m_pListCtrl->GetItemCount();

	m_pListCtrl->InsertItem( LVIF_TEXT | LVIF_STATE, nLastItem, _T(""), 0, LVIS_SELECTED, 0, 0);
	
	TCHAR buffer[15] = {0};

	_itot( nLastItem + 1, buffer, 10 );
	m_pListCtrl->SetItemText( nLastItem, TASK_ID,		buffer);
	m_pListCtrl->SetItemText( nLastItem, SOURCE_FILE,	FileName.GetString());
	
	m_pListCtrl->SetItemText( nLastItem, FILE_TYPE, XTLDescr_TrackOutType[val.intVal] );

	SelectItem( nLastItem, TRUE );
}

void CSimpleJoinerDlg::UpdateMenu( void )
{
	int i = m_pListCtrl->GetItemCount();

	UINT uiSaveList;
	UINT uiJoin;
	UINT uiLoadList = MF_ENABLED  | MF_BYCOMMAND;
	UINT uiMoveUp   = MF_GRAYED  | MF_BYCOMMAND;
	UINT uiMoveDown = MF_GRAYED  | MF_BYCOMMAND;
	UINT uiDelete   = MF_GRAYED  | MF_BYCOMMAND;

	if (i > 0)
	{
		uiSaveList	= MF_ENABLED  | MF_BYCOMMAND;
		uiJoin		= MF_ENABLED  | MF_BYCOMMAND;
	}else
	{
		uiSaveList	= MF_GRAYED  | MF_BYCOMMAND;
		uiJoin		= MF_GRAYED  | MF_BYCOMMAND;
	}

	if ( i > 0 && m_pListCtrl->GetSelectedCount() > 0 )
	{
		uiDelete =  MF_ENABLED | MF_BYCOMMAND;
		if( i > 1 )
		{
			uiMoveUp = MF_ENABLED  | MF_BYCOMMAND;
			uiMoveDown = MF_ENABLED  | MF_BYCOMMAND;
		}
		
		POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
		int Pos = m_pListCtrl->GetNextSelectedItem( pos );
		if( Pos == 0)
			uiMoveUp = MF_GRAYED  | MF_BYCOMMAND;
		if( Pos == ( i - 1))
			uiMoveDown = MF_GRAYED  | MF_BYCOMMAND;
	}

	CMenu* pSysMenu = GetMenu();

	pSysMenu->GetSubMenu(0)->EnableMenuItem( ID_FILE_SAVEJOINLIST, uiSaveList );
	pSysMenu->GetSubMenu(0)->EnableMenuItem( ID_FILE_STARTJOINING, uiJoin);
	pSysMenu->GetSubMenu(1)->EnableMenuItem( ID_LIST_MOVEUP, uiMoveUp);
	pSysMenu->GetSubMenu(1)->EnableMenuItem( ID_LIST_MOVEDOWN, uiMoveDown);
	pSysMenu->GetSubMenu(1)->EnableMenuItem( ID_LIST_DELETESELECTEDITEMS, uiDelete);
}

CString	CSimpleJoinerDlg::GetFourCC( DWORD Compression )
{
	CString str;
	char ch;
	ch = LOBYTE( LOWORD( Compression ) );
	str += ch;
	ch = HIBYTE( LOWORD( Compression ) );
	str += ch;
	ch = LOBYTE( HIWORD( Compression ) );
	str += ch;
	ch = HIBYTE( HIWORD( Compression ) );
	str += ch;
	return str;
}

void CSimpleJoinerDlg::SelectItem( int nItem, BOOL bSelect )
{
	if (( nItem < 0 ) || ( nItem > m_pListCtrl->GetItemCount() ))
		return;

	UINT uiSelected = (bSelect == TRUE)?LVIS_SELECTED:0;

	ListView_SetItemState( m_pListCtrl->GetSafeHwnd(), nItem, LVIS_FOCUSED|LVIS_SELECTED, 0x000F);
	ListView_EnsureVisible( m_pListCtrl->GetSafeHwnd(), nItem, FALSE);

	uiSelected = 0;

	for ( int i = 0; i < m_pListCtrl->GetItemCount(); i++ )
	{
		if ( i == nItem )
			continue;
		ListView_SetItemState( m_pListCtrl->GetSafeHwnd(), i, 0, 0x000F );
	}
}

void CSimpleJoinerDlg::OnFileSaveList()
{
	if( GetSaveFileName() != IDOK )
		return;
	CString file = _T("XTL Files (*.xtl)|*.xtl||");
	CFileDialog dlg( FALSE, _T("xtl"), _T("List"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, file, this );
	int result = ( int )dlg.DoModal();
	if( result == IDOK)
	{	
		file.ReleaseBuffer();
		file = dlg.GetPathName();
	}else
		return;

	WriteXTLFile( file, 1, 0 );
}

int CSimpleJoinerDlg::GetSaveFileName()
{	
	//Before you proceed, make sure that all files you are going to join
	//have the same type. It's very important!
	if( !QuickValidateFileTypes() )
	{
		MessageBox( _T("Some files have different types!\r\n(See 'Type' column.)\r\n\r\nThe joining will be canceled!"), MBWaringMsg, MB_OK | MB_ICONWARNING );
		return IDCANCEL;
	}

	CString file = _T("All Media Files (*.*)|*.*||"),
			ext;
	TCHAR tExt[_MAX_PATH] = {0};
	ext = m_pListCtrl->GetItemText( 0, SOURCE_FILE );
	_tsplitpath( ext, NULL, NULL, NULL, tExt );
	ext = tExt;
	ext.Delete(0);
	CFileDialog dlg( FALSE, ext, _T("Joined"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, file, this );
	int result = ( int )dlg.DoModal();
	if( result == IDOK)
		m_csDestName = dlg.GetPathName();
	return result;
}

BOOL CSimpleJoinerDlg::QuickValidateFileTypes()
{
	CString strType;
	strType = m_pListCtrl->GetItemText( 0, FILE_TYPE );

	for( int i = 1; i < m_pListCtrl->GetItemCount(); i++ )
	{
		if( strType != m_pListCtrl->GetItemText( i, FILE_TYPE ) ) 
			return FALSE;
	}
	return TRUE;
}

BOOL CSimpleJoinerDlg::WriteXTLFile( CString szFileName, BOOL bTempFile, DWORD dwSaveMode )
{
	CParser parser;
	int m_nSaveCount = m_pListCtrl->GetItemCount();
	SMM_GROUP_TASK tasks;

	tasks.tracks[0].CreateClips( m_nSaveCount );
	GetGroupTaskFromList( m_nSaveCount,  &tasks );
	
	HRESULT hr = S_OK;
	hr = parser.WriteXTLFile( szFileName, &tasks, 1 );
	
	tasks.Clear();
	return TRUE;
}

int CSimpleJoinerDlg::TranslateFileType( CString str )
{
	for( int i = 0; i < SMM_File_Type_COUNT; i++ )
	{
		CString CtlStr = XTLDescr_TrackOutType[i];
		if( CtlStr == str )
			return i;
	}
	return -1;
}

void CSimpleJoinerDlg::GetGroupTaskFromList( int ItemCount, SMM_GROUP_TASK * tasks )
{
	USES_CONVERSION;
	int i = 0;
	for ( int i = 0; i < ItemCount; i++ )
	{
		//This means the whole file would be appended.
		//Only this mode is currently supported.
		tasks[0].tracks[0].pClips[i].rtStart = 0;
		tasks[0].tracks[0].pClips[i].rtEnd = 0;
		/////////////////////////////////////////////

		tasks[0].tracks[0].nAudioStream = 0;
		tasks[0].tracks[0].nVideoStream = 0;
		tasks[0].nTaskType = SMM_Task_Type_Joining;
		tasks[0].tracks[0].nOutType = ( SMM_OutputTypes )TranslateFileType( m_pListCtrl->GetItemText( i, FILE_TYPE ) );
		tasks[0].nOutType = tasks[0].tracks[0].nOutType;
		if(  tasks[0].tracks[0].nOutType == SMM_File_Type_MPA )
			tasks[0].tracks[0].nAudioStream = 1;
		else
			tasks[0].tracks[0].nVideoStream = 1;
		wcscpy( tasks[0].tracks[0].pClips[i].wsfName, m_pListCtrl->GetItemText( i, SOURCE_FILE ).GetString());
	}
	tasks->szDstName = m_csDestName;
}

void CSimpleJoinerDlg::OnFileStartJoining()
{
	if( GetSaveFileName() == IDOK )
	{
		HRESULT hr = ConfigureTrimmerObj();
		if( SUCCEEDED(hr) )
		{
			RECT	rectMain,
					rectProgress;
			GetWindowRect( &rectMain );
			m_pProgress->GetWindowRect( &rectProgress );
			m_pProgress->MoveWindow( rectMain.left, rectMain.bottom - HEIGHT( &rectProgress ), WIDTH( &rectProgress ), HEIGHT( &rectProgress ) );
			CMenu *pSysMenu = GetSystemMenu( FALSE );
			pSysMenu->EnableMenuItem( SC_CLOSE, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED );
			m_pProgress->ShowWindow( SW_SHOW );
		}
		else
			MessageBox( _T("Can't start joining"), MBWaringMsg );
	}
	return;
}

HRESULT CSimpleJoinerDlg::InitEngine()
{
	HRESULT hr = S_OK;
	if(!m_pITrimmerObjControl)
	{
		hr = ::CoCreateInstance( __uuidof(TrimmerObjControl)/*CLSID_TrimmerObjControl*/,
								NULL,
								CLSCTX_INPROC,
								__uuidof(ITrimmerObjControl)/*IID_ITrimmerObjControl*/,
								(void**) &m_pITrimmerObjControl);
		if( FAILED(hr) )
		{
			m_pITrimmerObjControl = NULL;		
			return hr;
		}
		m_pProgress->SetTrimmerObjectControl( m_pITrimmerObjControl );
		hr = m_pITrimmerObjControl->SetCallback( &m_xCTrimmerObjControlCallB );
	}

	if( !m_pIModuleConfig )
	{
		hr = m_pITrimmerObjControl->QueryInterface(/*IID_IModuleConfig, (void **)*/&m_pIModuleConfig );
		if( FAILED( hr ) )
		{
			m_pITrimmerObjControl.Release();
			return hr;
		}

		CComVariant var;
		var.bstrVal = SysAllocString(Default_Codecs_Profile);
		hr  =  m_pIModuleConfig->SetValue( &SMAT_CodecsSet, &var );
		SysFreeString(var.bstrVal);
		CString silenPt = GetRegistrySilentPath( CLSID_VideoEditingSDK );
		if ( 0 != silenPt.GetLength() )
		{
			var.bstrVal = silenPt.AllocSysString();
			hr= m_pIModuleConfig->SetValue(&SMAT_SilentPath, &var);
		}

		{
		var.vt = VT_BSTR;
		var.bstrVal = CString(g_ActionKey_Join_MKV_MP4_MOV_AVC_AVI_ASF_MP3_WAV_MPEG1_MPEG2).AllocSysString();
		hr= m_pIModuleConfig->SetValue( &SMAT_ActionKey, &var );
		SysFreeString( var.bstrVal );
		}
	
	}
	return hr;
}
HRESULT CSimpleJoinerDlg::ConfigureTrimmerObj( void )
{
	if( FAILED(InitEngine()) )//Does nothing if already initialized
		return E_FAIL;
	HRESULT hr = S_OK;
	SMM_GROUP_TASK task;
	task.tracks[0].CreateClips( m_pListCtrl->GetItemCount() );
	GetGroupTaskFromList( m_pListCtrl->GetItemCount(), &task );

	//Pass params directly to a TrimmerObject via task structure
	CComVariant var;
	var = ( long ) task.nTaskType;
	hr  =  m_pIModuleConfig->SetValue( &SMAT_TaskType, &var );
	if( FAILED( hr ) )
	{
		task.Clear();	
		return hr;
	}
	var.Clear();
	var.vt = VT_BSTR;
	var.bstrVal = task.szDstName.AllocSysString();
	hr  =  m_pIModuleConfig->SetValue( &SMAT_OutputFile, &var );
	SysFreeString( var.bstrVal );
	if( FAILED( hr ) )
	{
		task.Clear();	
		return( hr );
	}
	var.Clear();
	var = (long)task.nOutType;
	hr  =   m_pIModuleConfig->SetValue( &SMAT_OutputType, &var );
	if( FAILED(hr) )
	{
		task.Clear();	
		return hr;
	}

	for( UINT n = 0; n < task.nTrackCount; n++  ) 
	{
		var = (BYTE*) &task.tracks[n];
		task.tracks[n].nTrackPos = n;
		hr  =  m_pIModuleConfig->SetValue( &SMAT_TrackInfo, &var );
		if( FAILED(hr) )
		{
			task.Clear();
			return hr;
		}
	}

	hr = m_pIModuleConfig->CommitChanges( NULL );
	task.Clear();
	if( FAILED(hr) )
		return hr;

	//Now when all parameters has been passed to TrimmerObjControl 
	//attempt full files' validating and analyze the result.
	//There might be different errors caused by type incompatibilities.
	var.Clear();
	hr = m_pIModuleConfig->GetValue( &SMAT_ValidateFiles, &var );
	if( SUCCEEDED(hr) )// check the result of validating
	{
		hr = (HRESULT)var.lVal;
		if( SUCCEEDED(hr) )//Operation should proceed
		{
			if( hr == S_FALSE )	//some parameters (not important ones) are different
								//and we may continue joining,
								//anyway we should ask the user for permission to
								//proceed, and warn him as well
								
			{
				int iRes = MessageBox( _T("Some chosen tracks have different parameters!\r\nThere may be some problems during output file playback.\r\n	Would you like to continue? "), MBWaringMsg, MB_YESNO | MB_ICONQUESTION );
				if ( iRes != IDYES )
					return E_FAIL;
			}
		}
		else//terminate operation and notify user
		{
			MessageBox( _T("Some audio or video streams have different\r\n formats or incompatible parameters!\r\n\r\nThe joining will be cancelled!"), MBWaringMsg, MB_OK | MB_ICONWARNING );
			return hr;
		}
	}

	m_pITrimmerObjControl->Start();
	SetTimer( TIMER_EVENT_PROGRESS, 100, 0);	
	m_bJointStopped = FALSE;

	Sleep(1000);
	AfxBeginThread( ProgressControl, this );

	return hr;
}
void CSimpleJoinerDlg::Stop()
{
	if( m_pITrimmerObjControl && !m_bJointStopped )
	{
		//CComPtr<IModuleConfig> pMC = NULL;
		//HRESULT hr = m_pITrimmerObjControl->QueryInterface( /*IID_IModuleConfig, (void**)*/&pMC );
		//if ( FAILED(hr) )
		//	return;
		//VARIANT val;
		//pMC->SetValue( &SMAT_TerminateJoint, &val );
		//pMC.Release();
		//pMC = NULL;

		m_pITrimmerObjControl->Stop();
		Sleep(1000);
	}
}

void CSimpleJoinerDlg::OnListClearList()
{
	int nCount = m_pListCtrl->GetItemCount();
	for ( int i = 0; i < nCount; i++ )
		m_pListCtrl->DeleteItem( 0 );
	UpdateMenu();
}

void CSimpleJoinerDlg::OnListDeleteSelected()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();

	while( pos )
		m_pListCtrl->DeleteItem( m_pListCtrl->GetNextSelectedItem( pos ) );

	UpdateMenu();
	Reindex();
}

void CSimpleJoinerDlg::OnListMoveDown()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	int Pos = m_pListCtrl->GetNextSelectedItem( pos );

	m_pListCtrl->InsertItem( LVIF_TEXT | LVIF_STATE,  Pos + 2 , _T(""), 0, 0, 0, 0);
	for( int i = 0; i <= FILE_TYPE; i++ )
		m_pListCtrl->SetItemText( Pos + 2, i, m_pListCtrl->GetItemText( Pos, i ) );

	m_pListCtrl->DeleteItem( Pos );
	SelectItem( Pos + 1 );
	Reindex();
	UpdateMenu();
}

void CSimpleJoinerDlg::OnListMoveup()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	int Pos = m_pListCtrl->GetNextSelectedItem( pos );

	m_pListCtrl->InsertItem( LVIF_TEXT | LVIF_STATE,  Pos - 1 , _T(""), 0, 0, 0, 0);
	for( int i = 0; i <= FILE_TYPE; i++ )
		m_pListCtrl->SetItemText( Pos - 1, i, m_pListCtrl->GetItemText( Pos + 1, i ) );

	m_pListCtrl->DeleteItem( Pos + 1 );
	SelectItem( Pos - 1 );
	Reindex();
	UpdateMenu();
}

void CSimpleJoinerDlg::Reindex()
{
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)
	{
		TCHAR buffer[10];
		_itot(i + 1, buffer, 10);
		m_pListCtrl->SetItemText( i, TASK_ID, buffer );
	}
}

LRESULT CSimpleJoinerDlg::ListWndProc (HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	CSimpleJoinerApp* lpObject = ( CSimpleJoinerApp *)AfxGetApp();
	CSimpleJoinerDlg* pDialog = (CSimpleJoinerDlg*)lpObject->GetMainWnd();
	switch ( iMessage )
	{
		case WM_LBUTTONDOWN:
		{
			LRESULT res = CallWindowProc( pDialog->m_PrevWndFunc, hWnd, iMessage, wParam, lParam );
			pDialog->UpdateMenu();
			return res;
		}
	}
	// continue with default message processing
	return CallWindowProc( pDialog->m_PrevWndFunc, hWnd, iMessage, wParam, lParam );
}

void CSimpleJoinerDlg::OnTimer(UINT nIDEvent)
{
	if( nIDEvent == TIMER_EVENT_PROGRESS )
	{
		LONG lPos = 0;
		HRESULT hr = m_pITrimmerObjControl->get_Status(&lPos);
		
		m_pProgress->UpdateProgress( lPos );
	}
	CDialog::OnTimer(nIDEvent);
}

void CSimpleJoinerDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if( m_pProgress )
	{
		Sleep(100);
		m_pProgress->DestroyWindow();
		delete m_pProgress;
		m_pProgress = NULL;
	}
}
BOOL CSimpleJoinerDlg::CheckSupportedFileTypes( SMM_OutputTypes FileType )
{
	if( FileType > SMM_File_Type_NO && FileType <= SMM_File_Type_MP4 )
		return TRUE;
	return FALSE;
}