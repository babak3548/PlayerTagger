// TrimmerDlg.h : header file
//

#pragma once

#include "medit.h"
#include "register_work.h"
#include "player.h"


// CTrimmerDlg dialog
class CTrimmerDlg : public CDialog
{
// Construction
public:
	CTrimmerDlg(CWnd* pParent = NULL);	// standard constructor
	~CTrimmerDlg();

// Dialog Data
	enum { IDD = IDD_TRIMMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    void OnOpenFile	( void );
	void Init		( void );

	CString ConvertLongTime2String	( long lTime );
	long	ConvertString2LongTime	( CString strTime );
	
	void	SetLeftMarker		( void );
	void	SetRightMarker		( void );
	void	UpdateSelection		( bool SetLeftFlag );
	void	RemoveSelecteon		( void );
	void	UpdateEditors		( void );
	void	StepNext			( void );
	void	StepBack			( void );
	void	Trim				( void );
	void	OnPlay				( void );
	void	OnStop				( void );
	void	OnPause				( void );
	CString GetOutputFileName	( void );
	CString Word2String			( DWORD x, int max_characters );
	void	OutSettingsDialog	( void );
	void	EnableAllControls	( BOOL bEnable );
	bool	CorrectTime			( REFERENCE_TIME * rtTime );
	void	OnStopTrim			( void );

	void	ReadStartTimeFromEditor			( BOOL bReadOnly = FALSE );
	void	ReadStopTimeFromEditor			( BOOL bReadOnly = FALSE );
	void	EnableControlsOnStartStopTrim	( BOOL bStartTrim );
	void	CorrectVolumeSliderPosition		( void );
	
	

// Implementation
protected:

	void ChangeVolume		( void );
	void ActivateBars		( void );
	void InitToolTips		( void );
	void ProcessOpenFile	( CString szStartFileName );
	BOOL ProcessCommandLine	( CString * szFirstParam );

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog		( void );
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	afx_msg void OnSysCommand		( UINT nID, LPARAM lParam );
	afx_msg void OnPaint			( void );
	afx_msg void OnHScroll			( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnTimer			( UINT nIDEvent );
	afx_msg void OnEnChangeEditStep	( void );
	afx_msg void OnMove				( int x, int y );
	afx_msg BOOL OnEraseBkgnd		( CDC* pDC );
	afx_msg HCURSOR OnQueryDragIcon	( void );
	
	afx_msg void OnNMReleasedcaptureSlider		( NMHDR *pNMHDR, LRESULT *pResult );
	afx_msg void OnNMReleasedcaptureVolumeSlider( NMHDR *pNMHDR, LRESULT *pResult );
	afx_msg void OnBnClickedButtonCancel		( void );

	DECLARE_MESSAGE_MAP()

	// Interfaces
	CComPtr<ITrimmerObjControl>	m_pITrimmerObjControl;
	CComPtr <IModuleConfig>     m_pModuleCfg;

	// controls
	CToolBar			m_ToolBar;
	CStatusBar			m_wndStatusBar;
	CmEdit				m_ctlStopTime;
	CmEdit				m_ctlStartTime;
	CEdit				m_ctlStep;
	CStatic				m_ctlCurrentPos;
	CStatic				m_ctlStreamLength;
	CSliderCtrl			m_ctlVolume;
	CSliderCtrl			m_Slider;
	CToolTipCtrl		m_ToolTips;

	// variables
	long 				m_StartInterval;
	long 				m_EndInterval;
	long 				m_StreamLength;

	// Used other classes
	CProgressCtrl	  	m_ctlProgress;
	CString			  	m_SourceFileName;
	CString			  	m_DestFileName;
	CRegWork		  	m_RegWork;
	CPlayer			  	m_player;
	CStatic			  	m_ctlVideoWindow;
};
