// TestMuxerAppDlg.h : header file
//

#pragma once
//#include "afxwin.h"

#include "XRegSettings.h"
#include "afxwin.h"
#include "afxcmn.h"


// CTestMuxerAppDlg dialog
class CTestMuxerAppDlg : public CDialog, public IGraphCallback
{
// Construction
public:
	CTestMuxerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTMUXERAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeVideoEncoderEdit();
	afx_msg void OnBnClickedInputfileButton();
	CEdit m_InputFileEdit;
	CEdit m_OutputFileEdit;
	afx_msg void OnClose();
	afx_msg void OnBnClickedOutputfileButton();
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedBuildGraphButton();
	CButton m_IndexASFCheck;
	CButton m_WriteLogCheck;
	afx_msg void OnBnClickedIndexAsfCheck();
	afx_msg void OnBnClickedWriteLogCheck();
	afx_msg void OnCbnSelchangeAudioStreamCombo();
	CButton m_RebuildButton;
	CButton m_StartButton;
	CButton m_CancelButton;
	afx_msg void OnBnClickedEnableVideoCheck();
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnNMCustomdrawProgress(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_ProcessProgress;
	CStatic m_ProgressStatic;
	CStatic m_VideoGroupStatic;
	CStatic m_AudioGroupStatic;
	afx_msg void OnBnClickedVideoenableCheck();
	CButton m_ShowASFPropsButton;
	afx_msg void OnBnClickedAudioenableCheck();
	afx_msg void OnBnClickedVideoUncokpressedCheck();
	afx_msg void OnBnClickedAudioUncokpressedCheck();
	afx_msg void OnBnClickedAudioTranscodeCheck();
	afx_msg void OnBnClickedTranscodeVideoCheck();
	afx_msg void OnBnClickedTreatVideoAsH264Check();
	afx_msg void OnBnClickedUseCustomFourccH264Check();
	afx_msg void OnEnKillfocusH264FourccEdit();
	afx_msg void OnBnClickedShowPropsButton();
	afx_msg void OnBnClickedVideoEncoderButton();
	afx_msg void OnBnClickedAudioEncoderButton();
	afx_msg void OnEnChangeInputfileEdit();
	afx_msg void OnEnChangeOutputfileEdit();
	afx_msg void OnTimer(UINT nIDEvent);

	// Video and Audio controls
	CComboBox m_AudioStreamsCombo;
	CButton m_EnableVideoCheck;
	CButton m_EnableAudioCheck;
	CButton m_TreatVideoAsH264Check;
	CButton m_bUseCustomFOURCCCheck;
	CEdit		m_FOURCCEdit;
	CButton m_VideoTranscodeCheck;
	CButton m_VideoUncompressedCheck;
	CButton m_AudioTranscodeCheck;
	CButton m_AudioUncompressedCheck;
	CEdit		m_VideoEncEdit;
	CEdit		m_AudioEncEdit;
	CButton m_VideoEncSelectButton;
	CButton m_AudioEncSelectButton;

protected:

	// Current directoru
	CString		m_szCurrentDir;

	// Source file name
	CString		m_szSourceFile;

	// Destination file name
	CString		m_szDestFile;

	// Need index output ASF file?
	BOOL			m_bIndexASF;

	// Need write output log?
	BOOL			m_bWriteLog;

	// Temp variables used to store data from registry
	BOOL			m_bTreatVideoASH264_tmp;
	BOOL			m_bUseCustomFOURCC_tmp;
	TCHAR			m_szCustomFOURCC_tmp[ 10 ];



	// Init dialog controls with settings read from registry
	void		InitControls( void );

	// Are the settings changed?
	BOOL		m_bDirty;

	// Are input or output file edit changed?
	BOOL		m_bDirty2;

	// Is new source file loaded
	BOOL		m_bNewFile;

	//Critical section for settings locking
	CCritSec		m_csSettings;

	// Read application settings from registry
	void	xSettingsRead( void );

	// Save application settings to registry
	void	xSettingsWrite( void );

	
	// DirectShow Graph Object
	CDirectShowGraph		m_DSGraph;


	// Amount of audio streams
	UINT			m_nAudioCount;

	// Amount of video streams
	UINT			m_nVideoCount;

	// Video / Audio settings
	CVideoSettings	*m_pVS[ MAX_VIDEO_STREAMS ];
	CAudioSettings	*m_pAS[ MAX_AUDIO_STREAMS ];

	// Critical section for locking graph building
	CCritSec			m_csBuild;

	// Checks if file exist
	BOOL				FileExist( CString szFile );

	// Build graph routine
	HRESULT		BuildGraph( BOOL bFirstBuild = false, BOOL bVerbose = true );

	// Destroy settings
	void				DestroySettings( void );

	// Enable / disable all video and audio specific controls
	void				EnableStreamControls( BOOL bEnable );

	// Update video / audio controls
	void			UpdateVideoControls( void  );
	void			UpdateAudioControls( void  );

	// Returns current audio stream number
	UINT			SelectedAudioStream( void );

	// Updates format strings
	void			UpdateFormatStrings( void );

	// Find Language ordered number
	int FindLangNumberByDefinition( TCHAR *tcsLangDef )
	{
		for( int i = 0; i < g_nLangCount; i++ )
		{
			if(0 == _tcscmp( tcsLangDef, wcsLangID[i][1] ) )
				return i;
		}
		return 0;
	};

	CString GetPathFromPathName(const CString& filePathName);
	bool fileExists(const CString& fileName);
public:
	//
	// IGraphCallback implementation
	//
	virtual void		OnGraphBuilt( void );
	virtual	void	OnNewFile( void );
	virtual void		OnGraphStarted( void );
	virtual void		OnGraphStopped( void );
	virtual void		OnTimer( void );
	virtual void		OnAbort( void );
	afx_msg void OnCbnSelchangeAudioLangId();
	afx_msg void OnBnClickedUseLang();
};
