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

// TestMuxerAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestMuxerApp.h"
#include "TestMuxerAppDlg.h"
#include ".\testmuxerappdlg.h"
#include "LangIDs.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#undef lstrlenW 

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


// CTestMuxerAppDlg dialog



CTestMuxerAppDlg::CTestMuxerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMuxerAppDlg::IDD, pParent),
	m_bIndexASF( true ),
	m_bWriteLog( false ),
	m_bDirty( false ),
	m_bDirty2( false )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nVideoCount = m_nAudioCount = 0;

	UINT n = 0 ;
	for ( n = 0; n < MAX_VIDEO_STREAMS; n++) m_pVS[ n ] = NULL;
	for ( n = 0; n < MAX_AUDIO_STREAMS; n++) m_pAS[ n ] = NULL;

	m_bTreatVideoASH264_tmp = false;
	m_bUseCustomFOURCC_tmp = false;
	ZeroMemory ( m_szCustomFOURCC_tmp, 10 );
}

void CTestMuxerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTFILE_EDIT, m_InputFileEdit);
	DDX_Control(pDX, IDC_OUTPUTFILE_EDIT, m_OutputFileEdit);
	DDX_Control(pDX, IDC_INDEX_ASF_CHECK, m_IndexASFCheck);
	DDX_Control(pDX, IDC_WRITE_LOG_CHECK, m_WriteLogCheck);
	DDX_Control(pDX, IDC_AUDIO_STREAM_COMBO, m_AudioStreamsCombo);
	DDX_Control(pDX, IDC_VIDEOENABLE_CHECK, m_EnableVideoCheck);
	DDX_Control(pDX, IDC_AUDIOENABLE_CHECK, m_EnableAudioCheck);
	DDX_Control(pDX, IDC_TREAT_VIDEO_AS_H264_CHECK, m_TreatVideoAsH264Check);
	DDX_Control(pDX, IDC_USE_CUSTOM_FOURCC_CHECK, m_bUseCustomFOURCCCheck);
	DDX_Control(pDX, IDC_FOURCC_EDIT, m_FOURCCEdit);
	DDX_Control(pDX, IDC_TRANSCODE_VIDEO_CHECK, m_VideoTranscodeCheck);
	DDX_Control(pDX, IDC_VIDEO_UNCOKPRESSED_CHECK, m_VideoUncompressedCheck);
	DDX_Control(pDX, IDC_AUDIO_TRANSCODE_CHECK, m_AudioTranscodeCheck);
	DDX_Control(pDX, IDC_AUDIO_UNCOKPRESSED_CHECK, m_AudioUncompressedCheck);
	DDX_Control(pDX, IDC_VIDEO_ENCODER_EDIT, m_VideoEncEdit);
	DDX_Control(pDX, IDC_AUDIO_ENCODER_EDIT, m_AudioEncEdit);
	DDX_Control(pDX, IDC_VIDEO_ENCODER_BUTTON, m_VideoEncSelectButton);
	DDX_Control(pDX, IDC_AUDIO_ENCODER_BUTTON, m_AudioEncSelectButton);
	DDX_Control(pDX, IDC_BUILD_GRAPH_BUTTON, m_RebuildButton);
	DDX_Control(pDX, IDC_START_BUTTON, m_StartButton);
	DDX_Control(pDX, IDC_CANCEL_BUTTON, m_CancelButton);
	DDX_Control(pDX, IDC_PROGRESS, m_ProcessProgress);
	DDX_Control(pDX, IDC_PROGRESS_STATIC, m_ProgressStatic);
	DDX_Control(pDX, IDC_SHOW_PROPS_BUTTON, m_ShowASFPropsButton);
	DDX_Control(pDX, IDC_VIDEO_GROUP, m_VideoGroupStatic);
	DDX_Control(pDX, IDC_AUDIO_GROUP, m_AudioGroupStatic);
}

BEGIN_MESSAGE_MAP(CTestMuxerAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_VIDEO_ENCODER_EDIT, OnEnChangeVideoEncoderEdit)
	ON_BN_CLICKED(IDC_INPUTFILE_BUTTON, OnBnClickedInputfileButton)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OUTPUTFILE_BUTTON, OnBnClickedOutputfileButton)
	ON_BN_CLICKED(IDC_START_BUTTON, OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_BUILD_GRAPH_BUTTON, OnBnClickedBuildGraphButton)
	ON_BN_CLICKED(IDC_INDEX_ASF_CHECK, OnBnClickedIndexAsfCheck)
	ON_BN_CLICKED(IDC_WRITE_LOG_CHECK, OnBnClickedWriteLogCheck)
	ON_CBN_SELCHANGE(IDC_AUDIO_STREAM_COMBO, OnCbnSelchangeAudioStreamCombo)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnBnClickedCancelButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS, OnNMCustomdrawProgress)
	ON_BN_CLICKED(IDC_VIDEOENABLE_CHECK, OnBnClickedVideoenableCheck)
	ON_BN_CLICKED(IDC_AUDIOENABLE_CHECK, OnBnClickedAudioenableCheck)
	ON_BN_CLICKED(IDC_VIDEO_UNCOKPRESSED_CHECK, OnBnClickedVideoUncokpressedCheck)
	ON_BN_CLICKED(IDC_AUDIO_UNCOKPRESSED_CHECK, OnBnClickedAudioUncokpressedCheck)
	ON_BN_CLICKED(IDC_AUDIO_TRANSCODE_CHECK, OnBnClickedAudioTranscodeCheck)
	ON_BN_CLICKED(IDC_TRANSCODE_VIDEO_CHECK, OnBnClickedTranscodeVideoCheck)
	ON_BN_CLICKED(IDC_TREAT_VIDEO_AS_H264_CHECK, OnBnClickedTreatVideoAsH264Check)
	ON_BN_CLICKED(IDC_USE_CUSTOM_FOURCC_H264_CHECK, OnBnClickedUseCustomFourccH264Check)
	ON_EN_KILLFOCUS(IDC_H264_FOURCC_EDIT, OnEnKillfocusH264FourccEdit)
	ON_BN_CLICKED(IDC_SHOW_PROPS_BUTTON, OnBnClickedShowPropsButton)
	ON_BN_CLICKED(IDC_VIDEO_ENCODER_BUTTON, OnBnClickedVideoEncoderButton)
	ON_BN_CLICKED(IDC_AUDIO_ENCODER_BUTTON, OnBnClickedAudioEncoderButton)
	ON_EN_CHANGE(IDC_INPUTFILE_EDIT, OnEnChangeInputfileEdit)
	ON_EN_CHANGE(IDC_OUTPUTFILE_EDIT, OnEnChangeOutputfileEdit)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_AUDIO_LANG_ID, OnCbnSelchangeAudioLangId)
	ON_BN_CLICKED(IDC_USE_LANG, OnBnClickedUseLang)
END_MESSAGE_MAP()


// CTestMuxerAppDlg message handlers

BOOL CTestMuxerAppDlg::OnInitDialog()
{
	HRESULT hr = S_OK;
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

	CoInitialize(0);

	TCHAR	szCurrentDir[ MAX_PATH ];
	GetCurrentDirectory( MAX_PATH, szCurrentDir );
	m_szCurrentDir = szCurrentDir;
	
	SetTimer(1, 100,NULL );
	xSettingsRead();
	InitControls();
	EnableStreamControls( false );
	hr = BuildGraph( true );
	EnableStreamControls( hr == S_OK );

	m_StartButton.EnableWindow( true );
	m_CancelButton.EnableWindow( false );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void	CTestMuxerAppDlg::EnableStreamControls( BOOL bEnable )
{

	if (m_nVideoCount || m_bNewFile )
	{
		m_EnableVideoCheck.EnableWindow( bEnable );
		m_TreatVideoAsH264Check.EnableWindow( bEnable );
		m_bUseCustomFOURCCCheck.EnableWindow( bEnable );
		m_FOURCCEdit.EnableWindow( bEnable );
		m_VideoTranscodeCheck.EnableWindow( bEnable );
		m_VideoUncompressedCheck.EnableWindow( bEnable );
		m_VideoEncEdit.EnableWindow( bEnable );
		m_VideoEncSelectButton.EnableWindow( bEnable );
	}

	if (m_nAudioCount || m_bNewFile)
	{
		m_EnableAudioCheck.EnableWindow( bEnable );
		m_AudioTranscodeCheck.EnableWindow( bEnable );
		m_AudioUncompressedCheck.EnableWindow( bEnable );
		m_AudioStreamsCombo.EnableWindow( bEnable );
		m_AudioEncSelectButton.EnableWindow( bEnable );
		m_AudioEncEdit.EnableWindow( bEnable );
		GetDlgItem(IDC_USE_LANG)->EnableWindow( bEnable );
		//GetDlgItem(IDC_AUDIO_LANG_ID)->EnableWindow( bEnable );

	}

	if (m_bNewFile) 
	{
		m_bNewFile = false;
	}
	else
	{
		if (bEnable)
		{
			UpdateVideoControls();
			UpdateAudioControls();
		}
	}
}

void			CTestMuxerAppDlg::UpdateVideoControls( void  )
{
	if (m_nVideoCount )
	{
		BOOL b1 = (BOOL)m_EnableVideoCheck.GetCheck();
		m_TreatVideoAsH264Check.EnableWindow( b1  );


		m_bUseCustomFOURCCCheck.EnableWindow( b1  );	
		if (!b1)
		{
			m_bUseCustomFOURCCCheck.EnableWindow( b1  );
			m_FOURCCEdit.EnableWindow( b1  );
		}
		else
		{
			m_bUseCustomFOURCCCheck.EnableWindow( m_DSGraph.AllowCustomFOURCC());
			BOOL b2 = (BOOL)m_bUseCustomFOURCCCheck.GetCheck();
			if (!b2)
			{
				m_FOURCCEdit.EnableWindow( b2  );
			}
			else
			{
				m_FOURCCEdit.EnableWindow( b1  );
			}
		}




		m_VideoTranscodeCheck.EnableWindow( b1 );
		m_VideoUncompressedCheck.EnableWindow( b1  );
		
		BOOL b4 = (BOOL)m_VideoTranscodeCheck.GetCheck();

		if (b1)
		{
			m_VideoEncEdit.EnableWindow( b4  );
			m_VideoEncSelectButton.EnableWindow( b4 );
		} 
		else
		{
			m_VideoEncEdit.EnableWindow( b1  );
			m_VideoEncSelectButton.EnableWindow( b1 );
		}
	}
}

void			CTestMuxerAppDlg::UpdateAudioControls( void  )
{
	if (m_nAudioCount)
	{
		BOOL	b1 = 	(BOOL)m_EnableAudioCheck.GetCheck();
		m_AudioTranscodeCheck.EnableWindow( b1 );
		m_AudioUncompressedCheck.EnableWindow( b1 );
		
		BOOL b2 = (BOOL)m_AudioTranscodeCheck.GetCheck();

		if (b1)
		{
			m_AudioEncSelectButton.EnableWindow( b2 );
			m_AudioEncEdit.EnableWindow(b2 );
		} 
		else
		{
			m_AudioEncSelectButton.EnableWindow( b1 );
			m_AudioEncEdit.EnableWindow( b1 );
		}
	}
}


void	CTestMuxerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestMuxerAppDlg::OnPaint() 
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
HCURSOR CTestMuxerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestMuxerAppDlg::OnEnChangeVideoEncoderEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestMuxerAppDlg::OnBnClickedInputfileButton()
{
	HRESULT hr = E_FAIL;
	CFileDialog dlg(true,0,0,OFN_ENABLESIZING | OFN_EXPLORER);
	INT_PTR res = dlg.DoModal();
	if( res != IDOK )
		return;
	CString	szSourceFile;
	szSourceFile = dlg.GetPathName();
	CString csExt = _T("asf");
	if (!szSourceFile.IsEmpty())
	{
		CString szDestFile;
		m_OutputFileEdit.GetWindowText( szDestFile );
		if( szDestFile.IsEmpty() )
		{
			CString inputPath = GetPathFromPathName(szSourceFile);
			CString formatStr   = inputPath+_T("NewName%d.%s");
			// if file exists inc num prefix
			int i = 0;
			do
			{
				szDestFile.Format(formatStr, i, csExt);
				i++;
			}
			while(fileExists(szDestFile));
			m_OutputFileEdit.SetWindowText(szDestFile);
		}
		m_StartButton.EnableWindow( !szDestFile.IsEmpty() );
		
		m_bNewFile = true;
	} else {
		m_StartButton.EnableWindow( false );
	}

	m_InputFileEdit.SetWindowText( szSourceFile );
	EnableStreamControls( false );
	BuildGraph();
}
CString CTestMuxerAppDlg::GetPathFromPathName(const CString& filePathName)
{
	CString path = _T("");
	TCHAR tcsDrive[_MAX_DRIVE];
	TCHAR tcsDir[_MAX_DIR];
	TCHAR tcsFName[_MAX_FNAME];
	TCHAR tcsExt[_MAX_EXT];
	_tsplitpath(filePathName, tcsDrive, tcsDir, tcsFName, tcsExt);
	path=tcsDrive;
	path+=tcsDir;
	return path;
}
bool CTestMuxerAppDlg::fileExists(const CString& fileName)
{
	HANDLE hFile = CreateFile(fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER lFileSize = {0};
		lFileSize.LowPart =  GetFileSize(hFile, (DWORD*)&lFileSize.HighPart);

		CloseHandle(hFile);

		if (lFileSize.QuadPart == 0)
			return false;

		return true;
	}
	return false;
}
void CTestMuxerAppDlg::OnBnClickedOutputfileButton()
{
	static TCHAR BASED_CODE szFilter[] = _T("ASF Files (*.asf)|*.asf;|All Files (*.*)|*.*||");
	CFileDialog dlg(false,_T("asf"),0,OFN_ENABLESIZING | OFN_EXPLORER, szFilter);
	INT_PTR res = dlg.DoModal();
	if( res != IDOK )
		return;
	CString	szDestFile;
	szDestFile = dlg.GetPathName();
	if (!szDestFile.IsEmpty())	{
		m_StartButton.EnableWindow( true );
	} else {
		m_StartButton.EnableWindow( false );
	}
	m_OutputFileEdit.SetWindowText( szDestFile );
	m_bDirty = true;
}

void CTestMuxerAppDlg::DestroySettings( void )
{
	UINT n = 0;
	
	for (n = 0; n < m_nVideoCount; n++)
	{
		if (m_pVS[n]) {
			delete m_pVS[n];
			m_pVS[n] = NULL;
		}
	}

	for (n = 0; n < m_nAudioCount; n++)
	{
		if (m_pAS[n]) {
			delete m_pAS[n];
			m_pAS[n] = NULL;
		}
	}


}

void		CTestMuxerAppDlg::OnClose()
{
	m_DSGraph.Cancel();
	m_DSGraph.Reset();
	xSettingsWrite();
	DestroySettings();
	CoUninitialize();
	CDialog::OnClose();
}


void	CTestMuxerAppDlg::InitControls( void )
{
	//m_InputFileEdit.SetWindowText( m_szSourceFile );
	//m_OutputFileEdit.SetWindowText( m_szDestFile );
	m_EnableVideoCheck.SetCheck( true );
	m_EnableAudioCheck.SetCheck( true );
	m_TreatVideoAsH264Check.SetCheck ( m_bTreatVideoASH264_tmp );
	m_bUseCustomFOURCCCheck.SetCheck( m_bUseCustomFOURCC_tmp);
	m_FOURCCEdit.SetWindowText ( m_szCustomFOURCC_tmp );

	m_IndexASFCheck.SetCheck( m_bIndexASF );
	m_DSGraph.IndexASF ( (BOOL)m_bIndexASF );
	
	m_WriteLogCheck.SetCheck( m_bWriteLog );
	m_DSGraph.WriteLog ( (BOOL)m_bWriteLog );

	m_bNewFile = true;

	CComboBox *pLangBox = (CComboBox*)GetDlgItem(IDC_AUDIO_LANG_ID);
	for( int i = 0; i < g_nLangCount; i++ )
		pLangBox->AddString(wcsLangID[i][1]);
	pLangBox->SetCurSel(0);
}

void	CTestMuxerAppDlg::xSettingsRead( void )
{
	xCRegSetting reg(HKEY_LOCAL_MACHINE, _T("Software\\Solveig\\Test ASF Muxer application"));
	CAutoLock	lock(&m_csSettings);
	TCHAR	szData[MAX_PATH];
	ZeroMemory(szData, MAX_PATH);
	
	reg[_T("Source file name")]			>> szData ;
	m_szSourceFile = szData;
	ZeroMemory(szData, MAX_PATH);

	reg[_T("Dest file name")]			>> szData ;
	m_szDestFile = szData;
	ZeroMemory(szData, MAX_PATH);

	reg[_T("Index output ASF file")]	>> m_bIndexASF;
	reg[_T("Write log file")]				>> m_bWriteLog;


	reg[_T("Treat input video as H.264")]		>> m_bTreatVideoASH264_tmp;
	reg[_T("Use custom FOURCC ")]	>> m_bUseCustomFOURCC_tmp;
	reg[_T("Custom FOURCC")]				>>	m_szCustomFOURCC_tmp; 


}

void	CTestMuxerAppDlg::xSettingsWrite( void )
{
	xCRegSetting reg(HKEY_LOCAL_MACHINE, _T("Software\\Solveig\\Test ASF Muxer application"));
	CAutoLock	lock(&m_csSettings);
	reg[_T("Source file name")]			<< m_szSourceFile;
	reg[_T("Dest file name")]			<< m_szDestFile;
	reg[_T("Index output ASF file")]	<< m_bIndexASF;
	reg[_T("Write log file")]				<< m_bWriteLog;

	if (m_pVS[0])
	{
		reg[_T("Treat input video as H.264")]		<<	 m_pVS[0]->GetTreatVideoAsH264();
		reg[_T("Use custom FOURCC")]	<<	 m_pVS[0]->GetUseCustomFOURCC();
		TCHAR szFOURCC[10];
		m_pVS[0]->GetFOURCC( szFOURCC );
		reg[_T("Custom FOURCC")]				<<	szFOURCC; 
	}
}


void CTestMuxerAppDlg::OnBnClickedStartButton()
{
	HRESULT hr = S_OK;
	
	// Check output file name
	CString	szDestFile;
	m_OutputFileEdit.GetWindowText( szDestFile );
	if ( szDestFile.IsEmpty() ) {
		MessageBox(_T("Output file is not specified"),_T("Please specify output file"), MB_ICONWARNING);
		hr = S_FALSE;
	}
	else
	{
		if (	m_bDirty )	{
			hr = BuildGraph( );
		}

		if (S_OK == hr)
		{
			hr = m_DSGraph.Start();
			if (FAILED(hr)) {
				MessageBox(_T("Fail to start DirectShow filter graph"), 
					_T("Graph starting failure"), MB_ICONERROR);
			}
		}
	}

	if (hr != S_OK)
		m_StartButton.EnableWindow( true );
}

void CTestMuxerAppDlg::OnBnClickedCancelButton()
{
	HRESULT hr = S_OK;
	hr = m_DSGraph.Cancel();
	if (FAILED(hr)) {
		MessageBox(_T("Fail to stop DirectShow filter graph"), _T("Graph stopping failure"), MB_ICONERROR);
	}
}


void		CTestMuxerAppDlg::OnNewFile( void )
{
	UINT n = 0;
	m_DSGraph.GetAudioCount ( &m_nAudioCount );
	m_DSGraph.GetVideoCount ( &m_nVideoCount );

	for ( n = 0; n < m_nVideoCount; n++)
	{
		if (!m_pVS[n])    m_pVS[n] = new CVideoSettings();
		m_pVS[n]->SetEnabled( true );
		m_pVS[n]->SetTreatVideoAsH264( (BOOL)m_TreatVideoAsH264Check.GetCheck());
		m_pVS[n]->SetUseCustomFOURCC ( (BOOL)m_bUseCustomFOURCCCheck.GetCheck());
		CString szFOURCC;
		m_FOURCCEdit.GetWindowText( szFOURCC );
		m_pVS[n]->SetFOURCC(szFOURCC);
	}

	for ( n = 0; n < m_nAudioCount; n++)
	{
		if (!m_pAS[n])   m_pAS[n] = new CAudioSettings();
		m_pAS[n]->SetEnabled( true );
	}

	// Apply settings
	for (n = 0 ; n < m_nVideoCount; n++)
		m_DSGraph.ApplyVideoSettings( n , m_pVS[n] );
	
	
	for (n = 0 ; n < m_nAudioCount; n++)
		m_DSGraph.ApplyAudioSettings( n , m_pAS[n] );
	
}

void		CTestMuxerAppDlg::OnGraphBuilt( void )
{
	UINT n = 0, count = 0;

	// Create settings for all video and audio streams 
	// Video
	for ( n = 0; n < m_nVideoCount; n++)
	{
		m_EnableVideoCheck.SetCheck( m_pVS[n]->IsEnabled() );
	}


	// Audio
	count = m_AudioStreamsCombo.GetCount();
	for (n = 0; n < count; n++) {
		m_AudioStreamsCombo.DeleteString( 0 );
	}
	
	TCHAR	szCombo[ 30 ];
	for ( n = 0; n < m_nAudioCount; n++)
	{
		ZeroMemory( szCombo, 30 );
		_stprintf( szCombo,_T("Stream %d"), n);
		m_AudioStreamsCombo.InsertString(n, szCombo );
	}

	m_AudioStreamsCombo.SetCurSel( 0 );
	OnCbnSelchangeAudioStreamCombo();

	m_StartButton.EnableWindow( true );
	m_CancelButton.EnableWindow( false );

	EnableStreamControls( true );
}

void		CTestMuxerAppDlg::OnGraphStarted( void )
{
	EnableStreamControls( false );
	
	m_RebuildButton.EnableWindow( false );
	m_StartButton.EnableWindow( false );
	m_CancelButton.EnableWindow( true );
	m_InputFileEdit.EnableWindow( false );
	m_OutputFileEdit.EnableWindow ( false );
	m_IndexASFCheck.EnableWindow( false );
	m_WriteLogCheck.EnableWindow( false );

	m_ProgressStatic.SetWindowText(_T(""));
	m_ProcessProgress.SetPos( 0 );
	m_ProcessProgress.SetRange( 0, 100 );
}

void CTestMuxerAppDlg::OnGraphStopped( void )
{
	m_RebuildButton.EnableWindow( true );
	m_StartButton.EnableWindow( true );
	m_CancelButton.EnableWindow( false );
	m_InputFileEdit.EnableWindow( true );
	m_OutputFileEdit.EnableWindow ( true );
	m_IndexASFCheck.EnableWindow( true );
	m_WriteLogCheck.EnableWindow( true );

	EnableStreamControls( true );
}

BOOL CTestMuxerAppDlg::FileExist( CString szFile )
{
	BOOL bRes = false;
	
	HANDLE hFile	=	CreateFile( szFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
		0,0);

	if ( hFile != INVALID_HANDLE_VALUE)
	{
		bRes = true;
		CloseHandle( hFile );
	}
	return bRes;
}


void CTestMuxerAppDlg::OnTimer( void )
{
}

void CTestMuxerAppDlg::OnAbort( void )
{
	MessageBox(_T("The process is aborted due to some internal error"), _T("Aborting process"), MB_ICONERROR);
}


HRESULT		CTestMuxerAppDlg::BuildGraph( BOOL bFirstBuild , BOOL bVerbose   )
{
	HRESULT hr = S_OK;
	UINT n =  0;
	CString	szSourceFile, szDestFile;
	m_InputFileEdit.GetWindowText( szSourceFile );
	m_OutputFileEdit.GetWindowText( szDestFile );

	m_VideoGroupStatic.SetWindowText( _T("Video") );
	m_AudioGroupStatic.SetWindowText( _T("Audio") );
	m_StartButton.EnableWindow( false );
	//m_ShowASFPropsButton.EnableWindow( false );

	if ( bFirstBuild ) {

	//	bFirstBuild = false;
		if ( szSourceFile.IsEmpty() || szDestFile.IsEmpty() )
			return S_FALSE;

	} else {

		if ( szSourceFile.IsEmpty() ) {
			if ( bVerbose )
				MessageBox(_T("Input file is not specified"),_T("Please specify input file"), MB_ICONWARNING);
			return S_FALSE;
		}

	}

	BOOL	bTemp = false;
	m_szSourceFile = szSourceFile;
	if (!szDestFile.IsEmpty() )
	{
		m_szDestFile = szDestFile;
	}
	else
	{
		TCHAR	szBuffer[ MAX_PATH ];
		GetTempPath( MAX_PATH, szBuffer );
		m_szDestFile = CString( szBuffer ) + CString( _T("\\SMMASF.asf") );
		bTemp = true;
	}


	// Apply settings
	for (n = 0 ; n < m_nVideoCount; n++)
		m_DSGraph.ApplyVideoSettings( n , m_pVS[n] );
	
	
	for (n = 0 ; n < m_nAudioCount; n++)
		m_DSGraph.ApplyAudioSettings( n , m_pAS[n] );
	
	

	hr =m_DSGraph.Init( m_szSourceFile, m_szDestFile, this );
	if (FAILED(hr))
	{  
		if (bVerbose)
			MessageBox(_T("Fail to build DirectShow filter graph"), _T("Graph building failure"), MB_ICONERROR);
	}
	else
	{
		UpdateFormatStrings( );
	}
	m_bDirty = false;
	
	if (bTemp) DeleteFile( m_szDestFile );
	
	return hr;
}

void		CTestMuxerAppDlg::UpdateFormatStrings( void )
{
	if ( m_pVS[0] ) 
	{
		TCHAR	szFormat[ MAX_PATH ];
		m_pVS[0]->GetFormatString( szFormat );
		if ( szFormat[0] ) {
			m_VideoGroupStatic.SetWindowText( CString(_T("Video - Format: ")) + szFormat );
		}  else {
			m_VideoGroupStatic.SetWindowText( CString(_T("Video - Format: Unknown")) );
		}
	} else {
		m_VideoGroupStatic.SetWindowText( CString(_T("Video - Format: Unknown")) );
	}

	UINT m = SelectedAudioStream( );
	if (m_pAS[m] ) 
	{
		TCHAR	szFormat[ MAX_PATH ];
		m_pAS[m]->GetFormatString( szFormat );
		if ( szFormat[0] ) {
			m_AudioGroupStatic.SetWindowText( CString(_T("Audio - Format: ")) + szFormat );
		}  else {
			m_AudioGroupStatic.SetWindowText( CString(_T("Audio - Format: Unknown")) );
		}

	} else {
		m_AudioGroupStatic.SetWindowText( CString(_T("Audio - Format: Unknown")) );
	}
}

void		CTestMuxerAppDlg::OnBnClickedBuildGraphButton()
{
}


void CTestMuxerAppDlg::OnBnClickedIndexAsfCheck()
{
	m_bIndexASF = m_IndexASFCheck.GetCheck();
	m_DSGraph.IndexASF ( (BOOL)m_bIndexASF );
	m_bDirty = true;
}

void CTestMuxerAppDlg::OnBnClickedWriteLogCheck()
{
	m_bWriteLog = m_WriteLogCheck.GetCheck();
	m_DSGraph.WriteLog ( (BOOL)m_bWriteLog );
	m_bDirty = true;
}

UINT CTestMuxerAppDlg::SelectedAudioStream( void )
{
	CString	szSelected;
	if (!m_AudioStreamsCombo.GetCount()) {
		return MAX_AUDIO_STREAMS-1;
	}
	m_AudioStreamsCombo.GetLBText(	m_AudioStreamsCombo.GetCurSel(), szSelected );
	
	
	UINT n = szSelected.Find(' ', 0) + 1;
	UINT count = szSelected.GetLength();
	szSelected = szSelected.Mid(n , count - n );

	return  _ttoi( szSelected );
}

void CTestMuxerAppDlg::OnCbnSelchangeAudioStreamCombo()
{
	USES_CONVERSION;
	UINT n = SelectedAudioStream();
	
	if( m_pAS[n] )
	{
		m_EnableAudioCheck.SetCheck(m_pAS[n]->IsEnabled());
		m_AudioUncompressedCheck.SetCheck(m_pAS[n]->IsUncompressed());
		m_AudioTranscodeCheck.SetCheck(m_pAS[n]->IsTranscode());
		TCHAR szEncName[ MAX_PATH ];
		m_pAS[n]->GetEncoderName( szEncName );
		m_AudioEncEdit.SetWindowText ( szEncName );
		BSTR bstLang;
		m_pAS[n]->GetLanguage( &bstLang );
		int nNum = FindLangNumberByDefinition( OLE2T(bstLang) );
		((CComboBox*)GetDlgItem(IDC_AUDIO_LANG_ID))->SetCurSel(nNum);
	}
	UpdateFormatStrings();
	m_bDirty = true;
}



void CTestMuxerAppDlg::OnNMCustomdrawProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}

void CTestMuxerAppDlg::OnBnClickedVideoenableCheck()
{
	if ( m_pVS[0] ) 
	{
		m_pVS[0]->SetEnabled( (BOOL)m_EnableVideoCheck.GetCheck() );
		m_bDirty = true;
	}

	if (m_nVideoCount && !m_bNewFile) {
		UpdateVideoControls();
	}
}

void CTestMuxerAppDlg::OnBnClickedAudioenableCheck()
{
	UINT n = SelectedAudioStream();
	if (m_pAS[n])
	{
		m_pAS[n]->SetEnabled( (BOOL)m_EnableAudioCheck.GetCheck() );
		m_bDirty = true;

		if (m_nAudioCount && !m_bNewFile) {
			UpdateAudioControls();
		}
	}
	
}


void CTestMuxerAppDlg::OnBnClickedVideoUncokpressedCheck()
{
	if (m_pVS[0])
	{
		BOOL b = (BOOL)m_VideoUncompressedCheck.GetCheck();
		m_pVS[0]->SetUncompressed( b );
		
		BOOL b1 = (BOOL)m_VideoTranscodeCheck.GetCheck();
		if (b && b1)
		{
			m_pVS[0]->SetTranscode(  false );
			m_VideoTranscodeCheck.SetCheck( false );
		}
		m_bDirty = true;
	}
	m_VideoTranscodeCheck.SetCheck( false );
	UpdateVideoControls();
}

void CTestMuxerAppDlg::OnBnClickedAudioUncokpressedCheck()
{
	UINT n = SelectedAudioStream();
	if (m_pAS[n])
	{
		BOOL b = (BOOL)m_AudioUncompressedCheck.GetCheck();
		m_pAS[n]->SetUncompressed( b );

		BOOL b1 = (BOOL)m_AudioTranscodeCheck.GetCheck();
		if (b && b1)
		{
			m_pAS[n]->SetTranscode(  false );
			m_AudioTranscodeCheck.SetCheck( false );
		}
		m_bDirty = true;
	}
	m_AudioTranscodeCheck.SetCheck( false );
	UpdateAudioControls();
}

void CTestMuxerAppDlg::OnBnClickedTranscodeVideoCheck()
{
	if (m_pVS[0])
	{
		BOOL b = (BOOL)m_VideoTranscodeCheck.GetCheck();
		m_pVS[0]->SetTranscode(  b );

		BOOL b1 = (BOOL)m_VideoUncompressedCheck.GetCheck();
		if ( b && b1 ) {
		  m_pVS[0]->SetUncompressed( false );
		  m_VideoUncompressedCheck.SetCheck( false );
		}
		m_bDirty = true;
	}
	
	UpdateVideoControls();
}

void CTestMuxerAppDlg::OnBnClickedAudioTranscodeCheck()
{
	UINT n = SelectedAudioStream();
	if (m_pAS[n])
	{
		BOOL b = (BOOL)m_AudioTranscodeCheck.GetCheck();
		m_pAS[n]->SetTranscode(  b );
		
		BOOL b1 = (BOOL)m_AudioUncompressedCheck.GetCheck();
		if ( b && b1 ) {
		  m_pAS[n]->SetUncompressed( false );
		  m_AudioUncompressedCheck.SetCheck( false );
		}
		m_bDirty = true;
	}
	m_AudioUncompressedCheck.SetCheck( false );
	UpdateAudioControls();
}



void CTestMuxerAppDlg::OnBnClickedTreatVideoAsH264Check()
{
	if (m_pVS[0])
	{
		m_pVS[0]->SetTreatVideoAsH264( (BOOL)m_TreatVideoAsH264Check.GetCheck() );
		m_bDirty = true;

		UpdateVideoControls ();
	}	
}

void CTestMuxerAppDlg::OnBnClickedUseCustomFourccH264Check()
{
	if (m_pVS[0])
	{
		m_pVS[0]->SetUseCustomFOURCC((BOOL) m_bUseCustomFOURCCCheck.GetCheck() );
		m_bDirty = true;

		UpdateVideoControls ();
	}	
}

void CTestMuxerAppDlg::OnEnKillfocusH264FourccEdit()
{
	if (m_pVS[0])
	{
		CString	szFOURCC;
		m_FOURCCEdit.GetWindowText( szFOURCC );

		m_pVS[0]->SetFOURCC( szFOURCC);
		m_bDirty = true;

		UpdateVideoControls ();
	}	
}

void CTestMuxerAppDlg::OnBnClickedShowPropsButton()
{
	m_DSGraph.ShowASFProps( m_hWnd );
}

void CTestMuxerAppDlg::OnBnClickedVideoEncoderButton()
{
	CString szFile  = m_szCurrentDir +  _T("\\video_encoders.txt");
	CEncoderSelectionDialog dlg( true,  szFile.GetBuffer() );
	dlg.DoModal();

	m_VideoEncEdit.SetWindowText ( dlg.GetEncoderName() );
	if (m_pVS[0]) {
		m_pVS[0]->SetEncoderGUID( dlg.GetEncoderGUID() );
		m_pVS[0]->SetEncoderName( dlg.GetEncoderName().GetBuffer() );
	}
	m_bDirty = true;
}

void CTestMuxerAppDlg::OnBnClickedAudioEncoderButton()
{
	CString szFile  = m_szCurrentDir +  _T("\\audio_encoders.txt");
	CEncoderSelectionDialog dlg( false, szFile.GetBuffer() );
	dlg.DoModal();

	m_AudioEncEdit.SetWindowText ( dlg.GetEncoderName() );

	UINT n = SelectedAudioStream();
	if (m_pAS[n])
	{
		m_pAS[n]->SetEncoderGUID( dlg.GetEncoderGUID() );
		m_pAS[n]->SetEncoderName( dlg.GetEncoderName() );
	}
	m_bDirty = true;
}

void CTestMuxerAppDlg::OnEnChangeInputfileEdit()
{
	
}

void CTestMuxerAppDlg::OnEnChangeOutputfileEdit()
{
	CString szSourceFile;
	m_InputFileEdit.GetWindowText( szSourceFile );
	m_StartButton.EnableWindow( !szSourceFile.IsEmpty() );
	m_bDirty = true;
}

void CTestMuxerAppDlg::OnTimer(UINT nIDEvent)
{
	HRESULT hr = S_OK;


	LONGLONG	llDuration, llCurrentPosition;
	if ( m_DSGraph.p )
	{
		hr = m_DSGraph.GetDuration( &llDuration );
		if (SUCCEEDED(hr) && llDuration )
		{
			llCurrentPosition = m_DSGraph.GetCurrentPosition();
			m_ProcessProgress.SetPos(int( 100 * llCurrentPosition / llDuration ) );
		}
	}

	__super::OnTimer(nIDEvent);
}

void CTestMuxerAppDlg::OnCbnSelchangeAudioLangId()
{
	USES_CONVERSION;
	CComboBox* LangBox = (CComboBox*)GetDlgItem(IDC_AUDIO_LANG_ID);
	m_pAS[m_AudioStreamsCombo.GetCurSel()]->SetLanguage( T2BSTR(wcsLangID[LangBox->GetCurSel()][1]) );
}

void CTestMuxerAppDlg::OnBnClickedUseLang()
{
	GetDlgItem(IDC_AUDIO_LANG_ID)->EnableWindow( IsDlgButtonChecked( IDC_USE_LANG ) == BST_CHECKED );
}
