// SimpleJoinerDlg.h : header file
//

#pragma once

class CProgressDlg : public CDialog
{
public:
	CProgressDlg(  );
	CProgressCtrl* m_pPrCtrl;
	ITrimmerObjControl *m_pITrimmerObjControl;

	// Dialog Data
	enum { IDD = IDD_DIALOG_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
protected:
public:
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	void SetTrimmerObjectControl(ITrimmerObjControl *pITrimmerObjControl)
	{
		m_pITrimmerObjControl = pITrimmerObjControl;
	}
	void UpdateProgress( int nPercent );
	void Reset( void )
	{
		m_pPrCtrl->SetPos(0);
		m_pITrimmerObjControl = NULL;
	}
};


// CSimpleJoinerDlg dialog
class CSimpleJoinerDlg : public CDialog
{
// Construction
public:
	CSimpleJoinerDlg(CWnd* pParent = NULL);	// standard constructor
	~CSimpleJoinerDlg();					//Standard destructor

// Dialog Data
	enum { IDD = IDD_SIMPLEJOINER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

//Columns number and order
enum {	TASK_ID = 0,
		SOURCE_FILE,
		FILE_TYPE,
		};

// Implementation
protected:
	HICON						m_hIcon;
	//Pointer to CListCtrl, to have access to it's functions 
	CListCtrl					*m_pListCtrl;
	//Number of columns in the list
	int							m_nColumnsNumber;
	// to store output file's full path
	CString						m_csDestName;
	//To manage the trimmer object
	CComPtr<ITrimmerObjControl>	m_pITrimmerObjControl;
	//To configure the trimmer object
	CComPtr<IModuleConfig>		m_pIModuleConfig;


	//initialization of the file list
	void			InitList( void );
	//Adds file to the file list
	void			AppendList( CString FileName );
	//Mark Item as selected
	void			SelectItem( int nItem, BOOL bSelect = TRUE );
	//Validate files and ask for the output file name
	int				GetSaveFileName( void );
	//Writes list to an XTL-file
	BOOL			WriteXTLFile( CString szFileName, BOOL bTempFile, DWORD dwSaveMode );
	//Validates Files' types compatibility
	BOOL			QuickValidateFileTypes();
	//Decrypt the 4cc code to string
	CString			GetFourCC( DWORD Compression );
	//Get file type(string - to common enumeration ) 
	int				TranslateFileType( CString str );
	//Format the file list to a standard structure
	void			GetGroupTaskFromList( int ItemCount, SMM_GROUP_TASK * tasks );
	//prepare Trimmer object for joining and start process
	HRESULT			ConfigureTrimmerObj( void );
	//if the order of files has changed:
	void			Reindex();

	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART( CTrimmerObjControlCallB, ITrimmerObjControlCB );
	STDMETHOD( OnStop )  ( void );
	STDMETHOD( OnStart ) ( void );
	STDMETHOD( OnPause ) ( void );
	STDMETHOD( OnError ) ( HRESULT hr, BSTR Val );
	END_INTERFACE_PART( CTrimmerObjControlCallB )

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//Flag-variable to terminate the progress-getting cycle
	BOOL			m_bJointStopped;
	//Pointer to the default message handler for CListCtrl
	WNDPROC			m_PrevWndFunc;
	//Progress Dialog
	CProgressDlg	*m_pProgress;

	//Initialize Trimmer object
	HRESULT			InitEngine();
	//Releases resources used by ITrimmerObject;
	void			ResetTrimmerObject();
	//Stops the joining process
	void			Stop();
	//Updates the state of menu items
	void			UpdateMenu( void );
	//Currently supported file formats
	BOOL			CheckSupportedFileTypes( SMM_OutputTypes FileType );
	//CALLBACK from CListCtrl to handle some it's actions
	static LRESULT CALLBACK ListWndProc	( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpenfile();
	afx_msg void OnFileSaveList();
	afx_msg void OnFileStartJoining();
	afx_msg void OnListClearList();
	afx_msg void OnListDeleteSelected();
	afx_msg void OnListMoveDown();
	afx_msg void OnListMoveup();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
};
