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


#include "stdafx.h"
#include "MKVMuxerApp.h"
#include "MKVMuxerAppDlg.h"
#include ".\mkvmuxerappdlg.h"
#define IDT_PROGRESS 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMKVMuxerAppDlg dialog


CMKVMuxerAppDlg::CMKVMuxerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMKVMuxerAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CMKVMuxerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_INPUTFILE_EDIT, m_InputFileEdit);
	DDX_Control(pDX, IDC_OUTPUTFILE_EDIT, m_OutputFileEdit);
	DDX_Control(pDX, IDC_VIDEO_GROUP, m_videoGroupBox);
	DDX_Control(pDX, IDC_AUDIO_STREAM_COMBO, m_audioStreams);
	DDX_Control(pDX, IDC_VIDEOENABLE_CHECK, m_videoEnableCheck);
	DDX_Control(pDX, IDC_AUDIOENABLE_CHECK, m_audioEnableCheck);
	DDX_Control(pDX, IDC_AUDIO_GROUP, m_audioGroupBox);
	DDX_Control(pDX, IDC_SUBTITLES_GROUP, m_subtitlesGroupBox);
	DDX_Control(pDX, IDC_SUBTITLE_STREAM_COMBO, m_subtitleStreams);
	DDX_Control(pDX, IDC_SUBTITLEENABLE_CHECK, m_subtitleEnableCheck);
	DDX_Control(pDX, IDC_VIDEO_STREAM_COMBO, m_videoStreams);
	DDX_Control(pDX, IDC_START_BUTTON, m_startBtn);
	DDX_Control(pDX, IDC_CHECK_VIDEO_FLAGDEFAULT, m_videoDefaultCheck);
	DDX_Control(pDX, IDC_CHECK_VIDEO_FLAGFORCED, m_videoForcedCheck);
	DDX_Control(pDX, IDC_CHECK_AUDIO_FLAGDEFAULT, m_audioDefaultCheck);
	DDX_Control(pDX, IDC_CHECK_AUDIO_FLAGFORCED, m_audioForcedCheck);
	DDX_Control(pDX, IDC_CHECK_SUBTITLE_FLAGDEFAULT, m_subtitleDefaultCheck);
	DDX_Control(pDX, IDC_CHECK_SUBTITLE_FLAGFORCED, m_subtitleForcedCheck);
	DDX_Control(pDX, IDC_EDIT_VIDEO_TRACK_NAME, m_videoNameEdit);
	DDX_Control(pDX, IDC_EDIT_AUDIO_TRACK_NAME, m_audioNameEdit);
	DDX_Control(pDX, IDC_EDIT_SUBTITLE_TRACK_NAME, m_subtitleNameEdit);
	DDX_Control(pDX, IDC_COMBO_VIDEO_LANG, m_videoLangCombo);
	DDX_Control(pDX, IDC_COMBO_AUDIO_LANG, m_audioLangCombo);
	DDX_Control(pDX, IDC_COMBO_SUBTITLE_LANG, m_subtitleLangCombo);
	DDX_Control(pDX, IDC_BUTTON_ADVANCED, m_advancedOptionsBtn);
	DDX_Control(pDX, IDC_COMBO_OUT_TYPE, m_outputType);
}

BEGIN_MESSAGE_MAP(CMKVMuxerAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START_BUTTON, &CMKVMuxerAppDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_INPUTFILE_BUTTON, &CMKVMuxerAppDlg::OnBnClickedInputfileButton)
	ON_BN_CLICKED(IDC_OUTPUTFILE_BUTTON, &CMKVMuxerAppDlg::OnBnClickedOutputfileButton)
	ON_CBN_SELCHANGE(IDC_AUDIO_STREAM_COMBO, &CMKVMuxerAppDlg::OnCbnSelchangeAudioStreamCombo)
	ON_CBN_SELCHANGE(IDC_SUBTITLE_STREAM_COMBO, &CMKVMuxerAppDlg::OnCbnSelchangeSubtitleStreamCombo)
	ON_CBN_SELCHANGE(IDC_VIDEO_STREAM_COMBO, &CMKVMuxerAppDlg::OnCbnSelchangeVideoStreamCombo)
	ON_BN_CLICKED(IDC_VIDEOENABLE_CHECK, &CMKVMuxerAppDlg::OnBnClickedVideoenableCheck)
	ON_BN_CLICKED(IDC_AUDIOENABLE_CHECK, &CMKVMuxerAppDlg::OnBnClickedAudioenableCheck)
	ON_BN_CLICKED(IDC_SUBTITLEENABLE_CHECK, &CMKVMuxerAppDlg::OnBnClickedSubtitleenableCheck)
	ON_BN_CLICKED(IDC_BUTTON_ADVANCED, &CMKVMuxerAppDlg::OnBnClickedButtonAdvanced)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_LANG, &CMKVMuxerAppDlg::OnCbnSelchangeComboVideoLang)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIO_LANG, &CMKVMuxerAppDlg::OnCbnSelchangeComboAudioLang)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBTITLE_LANG, &CMKVMuxerAppDlg::OnCbnSelchangeComboSubtitleLang)
	ON_EN_CHANGE(IDC_EDIT_VIDEO_TRACK_NAME, &CMKVMuxerAppDlg::OnEnChangeEditVideoTrackName)
	ON_EN_CHANGE(IDC_EDIT_AUDIO_TRACK_NAME, &CMKVMuxerAppDlg::OnEnChangeEditAudioTrackName)
	ON_EN_CHANGE(IDC_EDIT_SUBTITLE_TRACK_NAME, &CMKVMuxerAppDlg::OnEnChangeEditSubtitleTrackName)
	ON_BN_CLICKED(IDC_CHECK_VIDEO_FLAGDEFAULT, &CMKVMuxerAppDlg::OnBnClickedCheckVideoFlagdefault)
	ON_BN_CLICKED(IDC_CHECK_AUDIO_FLAGDEFAULT, &CMKVMuxerAppDlg::OnBnClickedCheckAudioFlagdefault)
	ON_BN_CLICKED(IDC_CHECK_SUBTITLE_FLAGDEFAULT, &CMKVMuxerAppDlg::OnBnClickedCheckSubtitleFlagdefault)
	ON_BN_CLICKED(IDC_CHECK_VIDEO_FLAGFORCED, &CMKVMuxerAppDlg::OnBnClickedCheckVideoFlagforced)
	ON_BN_CLICKED(IDC_CHECK_AUDIO_FLAGFORCED, &CMKVMuxerAppDlg::OnBnClickedCheckAudioFlagforced)
	ON_BN_CLICKED(IDC_CHECK_SUBTITLE_FLAGFORCED, &CMKVMuxerAppDlg::OnBnClickedCheckSubtitleFlagforced)
	ON_CBN_SELCHANGE(IDC_COMBO_OUT_TYPE, OnCbnSelchangeComboOutType)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMKVMuxerAppDlg message handlers

BOOL CMKVMuxerAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	

	// TODO: Add extra initialization here
	m_outputType.SetCurSel(0);
	UpdateStreamsInformation();
	updateStartButtonState();
	m_progress.SetRange(0,100);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMKVMuxerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMKVMuxerAppDlg::OnPaint()
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
HCURSOR CMKVMuxerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMKVMuxerAppDlg::OnBnClickedStartButton()
{
	if (!m_DSGraph.isInitialized())
		return;
	HRESULT hr = S_OK;
	FILTER_STATE fs;
	m_DSGraph.GetState(fs);
	if (fs == State_Stopped)
	{
		//check out file already exist
		CString outFile;
		m_OutputFileEdit.GetWindowText(outFile);
		if (fileExists(outFile))
		{
			int ret = MessageBox(_T("Output File already exists.\n Do you want to replace it?"),_T("SolveigMM MKV Muxer Sample App"),MB_YESNO | MB_ICONQUESTION);
			if (ret == IDNO)
				return;
		}
		OutType type = (OutType)(m_outputType.GetCurSel());
		if( type == OT_MKV )
		{
			m_DSGraph.SaveMuxerSettings();
			hr = ReBuildGraph((OutType)(m_outputType.GetCurSel()));
		}
		else
		{
			DisconnectOddPins( m_videoStreams );
			DisconnectOddPins( m_audioStreams );
			DisconnectOddPins( m_subtitleStreams );
		}
		if (FAILED(hr))
			return;
		m_DSGraph.Start();
		OnStart(); // OnStop called when graph is stops
	}
	else
		m_DSGraph.Cancel();

	updateStartButtonState();
}
void CMKVMuxerAppDlg::DisconnectOddPins( CComboBox& streams )
{
	int nCount = 0;
	for( int n = 0; n < streams.GetCount(); n++ )
	{
		TrackData *tD = (TrackData *) streams.GetItemDataPtr(n);
		if(!(tD->nEnabled))
			m_DSGraph.DisconnectMuxerPin( tD->dwNumber );
	}
}
void CMKVMuxerAppDlg::OnStart()
{
	SetTimer(IDT_PROGRESS, 100, 0);
	m_progress.SetPos(0);
	// temporary disable controls
	vector<HWND> skipControls;
	skipControls.push_back(m_progress.GetSafeHwnd());
	skipControls.push_back(m_startBtn.GetSafeHwnd());
	TermporaryDisableControls(skipControls);
}

void CMKVMuxerAppDlg::OnStop()
{
	KillTimer(IDT_PROGRESS);
	m_progress.SetPos(0);
	// restore temporary disabled controls
	RestoreTermporaryDisabledControls();
	updateStartButtonState();
}

void CMKVMuxerAppDlg::TermporaryDisableControls(const vector<HWND>& skipControls)
{
	if (m_tempDisabledControls.size())
	{
		ASSERT(FALSE);// old controls wasnt restored
	}

	HWND hWndFirstChild = ::GetWindow(GetSafeHwnd(), GW_CHILD);
	HWND hWndNext = hWndFirstChild;
	do
	{
		if (hWndNext)
		{
			bool bSkip = false;
			for (size_t i = 0; i < skipControls.size(); i++)
			{
				if (hWndNext == skipControls[i])
					bSkip = true;
			}

			if (!bSkip)
			{// save old state

				bool bEnabled = ::IsWindowEnabled(hWndNext);
				HWND_ENABLE_PAIR oldState(hWndNext, bEnabled);
				m_tempDisabledControls.insert(oldState);
				::EnableWindow(hWndNext,false);
			}
			
		}
		hWndNext = ::GetWindow(hWndNext, GW_HWNDNEXT);
	}while(hWndNext);
}
void CMKVMuxerAppDlg::RestoreTermporaryDisabledControls()
{
	for (OLD_STATE_ITER it = m_tempDisabledControls.begin(); it != m_tempDisabledControls.end(); it++)
	{
		::EnableWindow(it->first, it->second);
	}
	m_tempDisabledControls.clear();
}
void CMKVMuxerAppDlg::OnBnClickedInputfileButton()
{
	CFileDialog dlg(true,0,0,OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST);
	dlg.DoModal();
	CString	szSourceFile;
	szSourceFile = dlg.GetPathName();
	if (!szSourceFile.IsEmpty())
	{

	} else {
		return;
	}
	m_InputFileEdit.SetWindowText( szSourceFile );
	m_DSGraph.ClearMuxerSettings();
	HRESULT hr = ReBuildGraph((OutType)(m_outputType.GetCurSel()));
}

void CMKVMuxerAppDlg::OnBnClickedOutputfileButton()
{
	CFileDialog dlg(false,0,0,OFN_ENABLESIZING | OFN_EXPLORER | OFN_OVERWRITEPROMPT);
	dlg.DoModal();
	CString	szSourceFile;
	szSourceFile = dlg.GetPathName();
	if (!szSourceFile.IsEmpty())
	{

	} else {
		return;
	}
	m_OutputFileEdit.SetWindowText( szSourceFile );
	ReBuildGraph((OutType)(m_outputType.GetCurSel()));
}

HRESULT CMKVMuxerAppDlg::ReBuildGraph( OutType outType )
{
	CString inputFile;
	CString outputFile;
	m_InputFileEdit.GetWindowText(inputFile);
	m_OutputFileEdit.GetWindowText(outputFile);
	OutType type = (OutType) m_outputType.GetCurSel();
	CString csExt;
	switch (outType)
	{
		case 0:
		csExt = _T("mkv");
		break;
		case 1:
		csExt = _T("mp4");
		break;
		case 2:
		csExt = _T("mov");
	}
	if( m_DSGraph.GetOutType() != outType )
		outputFile.Empty();
	
	if (outputFile.IsEmpty())
	{
		CString inputPath = GetPathFromPathName(inputFile);
		CString formatStr   = inputPath+_T("NewName%d.%s");
		// if file exists inc num prefix
		int i = 0;
		do
		{
			outputFile.Format(formatStr, i, csExt);
			i++;
		}
		while(fileExists(outputFile));
		m_OutputFileEdit.SetWindowText(outputFile);
	}
	HRESULT hr = m_DSGraph.Init(inputFile, outputFile, (OutType)m_outputType.GetCurSel());
	m_DSGraph.RestoreMuxerSettings();

	UpdateStreamsInformation();
	updateStartButtonState();
	return hr;
}
void CMKVMuxerAppDlg::UpdateStreamsInformation()
{
	bool bVideoPresent = false;
	bool bAudioPresent = false;
	bool bSubtitlePresent = false;
	
	STREAMNUM_MEDIATYPE audioMediaTypes;
	STREAMNUM_MEDIATYPE videoMediaTypes;
	STREAMNUM_MEDIATYPE subtitleMediatypes;

	vector<CMediaType> mediaTypes;
	m_DSGraph.GetStreamsMediaTypes(mediaTypes);
	for (size_t i = 0; i < mediaTypes.size(); i++)
	{
		if (*(mediaTypes[i].Type()) == MEDIATYPE_Video)
		{
			videoMediaTypes.insert(STREAMNUM_MEDIATYPEPAIR(i, mediaTypes[i]));
			bVideoPresent = true;
		}
		if (*(mediaTypes[i].Type()) == MEDIATYPE_Audio)
		{
			audioMediaTypes.insert(STREAMNUM_MEDIATYPEPAIR(i, mediaTypes[i]));
			bAudioPresent = true;
		}
		if ((*(mediaTypes[i].Type()) == MEDIATYPE_Text) || (*(mediaTypes[i].Type()) == MEDIATYPE_Subtitle))
		{
			subtitleMediatypes.insert(STREAMNUM_MEDIATYPEPAIR(i, mediaTypes[i]));
			bSubtitlePresent = true;
		}
		
	}
	
	EnableVideoGroupBox(bVideoPresent);
	EnableAudioGroupBox(bAudioPresent);
	EnableSubtitlesGroupBox(bSubtitlePresent);

	// fill video combo
	FillStreamsCombo(m_videoStreams, videoMediaTypes);
	// fill audio combo
	FillStreamsCombo(m_audioStreams, audioMediaTypes);
	// fill subtitle combo
	FillStreamsCombo(m_subtitleStreams, subtitleMediatypes);
	updateSelStreamProps();
}
void CMKVMuxerAppDlg::updateStartButtonState()
{
	if (!m_DSGraph.isInitialized())
	{
		m_startBtn.EnableWindow(false);
		m_advancedOptionsBtn.EnableWindow(false);
		return;
	}
	else
	{
		m_startBtn.EnableWindow(true);
		m_advancedOptionsBtn.EnableWindow(true);
		FILTER_STATE fs;
		m_DSGraph.GetState(fs);
		if (fs == State_Stopped)
			m_startBtn.SetWindowText(_T("Start"));
		else
			m_startBtn.SetWindowText(_T("Abort"));

	}
}
void CMKVMuxerAppDlg::FillStreamsCombo(CComboBox& combo, STREAMNUM_MEDIATYPE& streams)
{
	int curSel = combo.GetCurSel();
	FreeItemData( combo );
	combo.ResetContent();
	int i = 0;
	for (STREAMNUM_MEDIATYPE_IT it = streams.begin(); it != streams.end(); it++)
	{
		CString formatName;
		formatName.Format(_T("%d. "), i);
		formatName+= GetFormatNameBySubType(*(it->second.Subtype()));
		int index =  combo.AddString(formatName);
		// set streamNum as TrackData
		// in case of MP4/MOV set the "Enable" state of stream
		TrackData* pData = new TrackData( it->first );
		if( m_outputType.GetCurSel() > 0 )
		{
			if( i == 0 )
				pData->nEnabled = 1;
			else
				pData->nEnabled = 0;
		}
		combo.SetItemDataPtr(index, (void*)pData);
		i++;
	}
	if (curSel == -1 || curSel >= streams.size()) 
		curSel = 0;
	combo.SetCurSel(curSel);
}
void CMKVMuxerAppDlg::EnableVideoGroupBox(bool bEnable)
{
	bool Enable =  bEnable;
	m_videoStreams.EnableWindow(Enable);
	m_videoEnableCheck.EnableWindow(Enable);
	if( m_outputType.GetCurSel() )
	{
		Enable = false;
	}
	m_videoGroupBox.EnableWindow(Enable);
	m_videoDefaultCheck.EnableWindow(Enable);
	m_videoForcedCheck.EnableWindow(Enable);
	m_videoNameEdit.EnableWindow(Enable);
	m_videoLangCombo.EnableWindow(Enable);
}

void CMKVMuxerAppDlg::EnableAudioGroupBox(bool bEnable)
{
	bool Enable =  bEnable;
	m_audioStreams.EnableWindow(Enable);
	m_audioEnableCheck.EnableWindow(Enable);
	if( m_outputType.GetCurSel() )
	{
		Enable = false;
	}
	m_audioGroupBox.EnableWindow(Enable);
	m_audioDefaultCheck.EnableWindow(Enable);
	m_audioForcedCheck.EnableWindow(Enable);
	m_audioNameEdit.EnableWindow(Enable);
	m_audioLangCombo.EnableWindow(Enable);
}

void CMKVMuxerAppDlg::EnableSubtitlesGroupBox(bool bEnable)
{
	bool Enable =  bEnable;
	m_subtitleStreams.EnableWindow(Enable);
	m_subtitleEnableCheck.EnableWindow(Enable);
	if( m_outputType.GetCurSel() )
	{
		Enable = false;
	}
	m_subtitlesGroupBox.EnableWindow(Enable);
	m_subtitleDefaultCheck.EnableWindow(Enable);
	m_subtitleForcedCheck.EnableWindow(Enable);
	m_subtitleNameEdit.EnableWindow(Enable);
	m_subtitleLangCombo.EnableWindow(Enable);
}

CString CMKVMuxerAppDlg::GetFormatNameBySubType(const GUID& subtype)
{
	CString ret = _T("Unknown");
	for (size_t n = 0; n < sizeof ( g_pVF ) / sizeof(MediaFormat); n++)
	{
		if (g_pVF[n].guid == subtype)
		{
			ret = g_pVF[n].szFormat;
			return ret;
		}
	}
	for (size_t n = 0; n < sizeof ( g_pAF ) / sizeof(MediaFormat); n++)
	{
		if (g_pAF[n].guid ==  subtype)
		{
			ret = g_pAF[n].szFormat;
			return ret;
		}
	}
	return ret;
}

bool CMKVMuxerAppDlg::fileExists(const CString& fileName)
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
CString CMKVMuxerAppDlg::GetPathFromPathName(const CString& filePathName)
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
void CMKVMuxerAppDlg::OnCbnSelchangeAudioStreamCombo()
{
	updateSelStreamProps();
}

void CMKVMuxerAppDlg::OnCbnSelchangeSubtitleStreamCombo()
{
	updateSelStreamProps();
}
void CMKVMuxerAppDlg::OnCbnSelchangeVideoStreamCombo()
{
	updateSelStreamProps();
}
void CMKVMuxerAppDlg::updateSelStreamProps()
{
	updateSelStreamProps(m_videoStreams, m_videoEnableCheck, m_videoDefaultCheck,m_videoForcedCheck,m_videoNameEdit,m_videoLangCombo);
	updateSelStreamProps(m_audioStreams, m_audioEnableCheck,m_audioDefaultCheck,m_audioForcedCheck,m_audioNameEdit,m_audioLangCombo);
	updateSelStreamProps(m_subtitleStreams, m_subtitleEnableCheck, m_subtitleDefaultCheck, m_subtitleForcedCheck,m_subtitleNameEdit,m_subtitleLangCombo);
}

void CMKVMuxerAppDlg::updateSelStreamProps(CComboBox& streamCombo, 
										   CButton& streamEnableButton,
										   CButton& streamDefaultButton,
										   CButton& streamForcedButton,
										   CEdit& streamNameEdit,
										   CComboBox& streamLangCombo)
{
	int absStreamNum = -1;
	// video
	int index = streamCombo.GetCurSel();
	USES_CONVERSION;
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;
		TRACK_PROPS tp;
		bool ret = false;
		if( m_outputType.GetCurSel() > 0 )
			streamEnableButton.SetCheck(tD->nEnabled? BST_CHECKED: BST_UNCHECKED);
		else
			ret = m_DSGraph.GetStreamProps(absStreamNum, tp);
		if (ret)
		{
			streamEnableButton.SetCheck(tp.bEnable? BST_CHECKED: BST_UNCHECKED);
			streamDefaultButton.SetCheck(tp.bDefault? BST_CHECKED: BST_UNCHECKED);
			streamForcedButton.SetCheck(tp.bForced? BST_CHECKED: BST_UNCHECKED);
			streamNameEdit.SetWindowText(tp.name);

			// fill langs combo
			streamLangCombo.ResetContent();
			for (int i = 0; i < lang_iso_count; i++)
				streamLangCombo.AddString(A2T(lang_iso[i][0]));
			streamLangCombo.SelectString(-1, tp.language);
		}
	}
}

void CMKVMuxerAppDlg::OnBnClickedVideoenableCheck()
{
	setCurSelStreamEnabled(m_videoStreams, m_videoEnableCheck);
}

void CMKVMuxerAppDlg::OnBnClickedAudioenableCheck()
{
	setCurSelStreamEnabled(m_audioStreams, m_audioEnableCheck);
}

void CMKVMuxerAppDlg::OnBnClickedSubtitleenableCheck()
{
	setCurSelStreamEnabled(m_subtitleStreams, m_subtitleEnableCheck);
}
void CMKVMuxerAppDlg::OnCbnSelchangeComboVideoLang()
{
	setCurSelStreamLanguage(m_videoStreams, m_videoLangCombo);
}

void CMKVMuxerAppDlg::OnCbnSelchangeComboAudioLang()
{
	setCurSelStreamLanguage(m_audioStreams, m_audioLangCombo);
}

void CMKVMuxerAppDlg::OnCbnSelchangeComboSubtitleLang()
{
	setCurSelStreamLanguage(m_subtitleStreams, m_subtitleLangCombo);
}

void CMKVMuxerAppDlg::OnEnChangeEditVideoTrackName()
{
	setCurSelStreamName(m_videoStreams, m_videoNameEdit);
}

void CMKVMuxerAppDlg::OnEnChangeEditAudioTrackName()
{
	setCurSelStreamName(m_audioStreams, m_audioNameEdit);
}

void CMKVMuxerAppDlg::OnEnChangeEditSubtitleTrackName()
{
	setCurSelStreamName(m_subtitleStreams, m_subtitleNameEdit);
}

void CMKVMuxerAppDlg::OnBnClickedCheckVideoFlagdefault()
{
	setCurSelStreamDefault(m_videoStreams, m_videoDefaultCheck);
	// TODO: Add your control notification handler code here
}

void CMKVMuxerAppDlg::OnBnClickedCheckAudioFlagdefault()
{
	setCurSelStreamDefault(m_audioStreams, m_audioDefaultCheck);
	// TODO: Add your control notification handler code here
}

void CMKVMuxerAppDlg::OnBnClickedCheckSubtitleFlagdefault()
{
	setCurSelStreamDefault(m_subtitleStreams, m_subtitleDefaultCheck);
	// TODO: Add your control notification handler code here
}

void CMKVMuxerAppDlg::OnBnClickedCheckVideoFlagforced()
{
	setCurSelStreamForced(m_videoStreams, m_videoForcedCheck);
}

void CMKVMuxerAppDlg::OnBnClickedCheckAudioFlagforced()
{
	setCurSelStreamForced(m_audioStreams, m_audioForcedCheck);
}

void CMKVMuxerAppDlg::OnBnClickedCheckSubtitleFlagforced()
{
	setCurSelStreamForced(m_subtitleStreams, m_subtitleForcedCheck);
}
void CMKVMuxerAppDlg::setCurSelStreamEnabled(CComboBox& streamCombo, CButton& streamEnableButton)
{
	int absStreamNum = -1;
	int index = streamCombo.GetCurSel();
	BOOL bMKV = TRUE;
	if( m_outputType.GetCurSel() > 0 )
		bMKV = FALSE;
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;

		bool bEnable = (streamEnableButton.GetCheck()==BST_CHECKED)? true:false;
		if(!bMKV)
			tD->nEnabled = bEnable;
		else
			m_DSGraph.SetStreamEnabled(absStreamNum, bEnable);
	}
}

void CMKVMuxerAppDlg::setCurSelStreamLanguage(CComboBox& streamCombo, CComboBox& langCombo)
{
	//Only for MKV
	int absStreamNum = -1;
	int index = streamCombo.GetCurSel();
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;

		int curSel = langCombo.GetCurSel();
		if (curSel != -1)
		{
			CString engLangName;
			langCombo.GetLBText(curSel, engLangName);
			m_DSGraph.SetStreamLanguage(absStreamNum, engLangName);
		}
	}
}

void CMKVMuxerAppDlg::setCurSelStreamName(CComboBox& streamCombo, CEdit& nameEdit)
{
	//Only for MKV
	int absStreamNum = -1;
	int index = streamCombo.GetCurSel();
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;

		CString name;
		nameEdit.GetWindowText(name);
		m_DSGraph.SetStreamName(absStreamNum, name);
	}
}

void CMKVMuxerAppDlg::setCurSelStreamDefault(CComboBox& streamCombo, CButton& streamDefaultButton)
{
	//Only for MKV
	int absStreamNum = -1;
	int index = streamCombo.GetCurSel();
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;

		bool bDefault = (streamDefaultButton.GetCheck()==BST_CHECKED)? true:false;
		m_DSGraph.SetStreamDefault(absStreamNum, bDefault);
	}
}

void CMKVMuxerAppDlg::setCurSelStreamForced(CComboBox& streamCombo, CButton& streamForcedButton)
{
	//Only for MKV
	int absStreamNum = -1;
	int index = streamCombo.GetCurSel();
	if (index != -1)
	{
		TrackData* tD = NULL;
		tD = (TrackData*) (streamCombo.GetItemDataPtr(index));
		absStreamNum = tD->dwNumber;

		bool bForced = (streamForcedButton.GetCheck()==BST_CHECKED)? true:false;
		m_DSGraph.SetStreamForced(absStreamNum, bForced);
	}
}

void CMKVMuxerAppDlg::OnBnClickedButtonAdvanced()
{
	m_DSGraph.ShowMKVProps(m_hWnd);
}

void CMKVMuxerAppDlg::OnClose()
{
	if (m_DSGraph.isRunning())
	{	// if is running ask to terminate
		int ret = MessageBox(_T("There is Running Operation.\nAre you sure you want to exit?"),_T("SolveigMM MKV Muxer Sample App"),MB_YESNO | MB_ICONQUESTION);
		if (ret == IDNO)
			return;
		m_DSGraph.Cancel();
	}

	CDialog::OnClose();
}

void CMKVMuxerAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == IDT_PROGRESS)
	{	
		if (m_DSGraph.isRunning())
		{
			int progress = m_DSGraph.GetProgress();
			m_progress.SetPos(progress);
		}
		else
		{
			OnStop();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CMKVMuxerAppDlg::OnCbnSelchangeComboOutType()
{
	CString fName = _T("");
	m_InputFileEdit.GetWindowText( fName );
	if( fName.IsEmpty() )
		return;
	int nPos = m_outputType.GetCurSel();

	ReBuildGraph( (OutType)nPos );
}
void CMKVMuxerAppDlg::FreeItemData( CComboBox& combo )
{
	for( int i = 0; i<combo.GetCount(); i++ )
	{
		TrackData* tD = (TrackData*) combo.GetItemDataPtr(i);
		delete tD;
	}
}
void CMKVMuxerAppDlg::OnDestroy(  )
{
	FreeItemData(m_videoStreams);
	FreeItemData(m_audioStreams);
	FreeItemData(m_subtitleStreams);
}