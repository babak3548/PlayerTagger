#pragma once
#include "resource.h"
// CDlgIndexing dialog

class CDlgIndexing : public CDialog
{
public:
	CDlgIndexing(CWnd* pParent = NULL);   // standard constructor
	CDlgIndexing(CWnd* pParent /*=NULL*/,HRESULT *hr);
	virtual ~CDlgIndexing();	
	DECLARE_INTERFACE_MAP()
		BEGIN_INTERFACE_PART(CTrimmerObjControlCB, ITrimmerObjControlCB);
		STDMETHOD (OnStop) ( void );
		STDMETHOD (OnStart)( void );
		STDMETHOD (OnPause)( void );
		STDMETHOD (OnError) (HRESULT hr, BSTR Val);
	END_INTERFACE_PART(CTrimmerObjControlCB)
public:
	BOOL OnInitDialog();
	HRESULT SetInputFile( CString strInName );
	HRESULT SetOutputIndexFile( CString strOutInd );
	void	SetMPEG2Profile( CString csProfile )		{ m_csProfile = csProfile; }
	CCritSec Indexing;
	void	SetFinishedIndexing( BOOL bFinished )
	{
		CAutoLock lock(&Indexing);
		m_bFinishedIndexing = bFinished;
	}
	BOOL	IsFinishedIndexing( void )
	{
		CAutoLock lock(&Indexing);
		return m_bFinishedIndexing;
	}
	BOOL	m_bFinishedIndexing;


	// Dialog Data
	enum { IDD = IDD_DIALOG_INDEX };
	
	static void TimerProc(HWND hWnd,UINT nMsg, UINT nIDEvent,DWORD dwTime );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	
	UINT						m_IndexTimer;
	CComPtr<IModuleConfig>		m_pIModuleConfig;
	CComPtr<ITrimmerObjControl> m_pITrimmerObj;
	CString						m_csProfile;


public:
	CProgressCtrl m_ctlPogrIndx;

	// Generated message map functions
	//{{AFX_MSG(CDlgIndexing)
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
