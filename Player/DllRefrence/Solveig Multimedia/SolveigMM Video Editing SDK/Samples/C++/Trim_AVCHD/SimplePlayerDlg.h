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

#if !defined(AFX_SIMPLEPLAYERDLG_H__13EB3B1D_F8A1_476D_960B_62DB25620C0D__INCLUDED_)
#define AFX_SIMPLEPLAYERDLG_H__13EB3B1D_F8A1_476D_960B_62DB25620C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Player.h"
#include "afxcmn.h"
#include <ModuleConfig.h>

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerDlg dialog

class CSimplePlayerDlg : public CDialog,
						 public IEventNotify

{
// Construction
public:

	CSimplePlayerDlg(CWnd* pParent = NULL);	// standard constructor
	~CSimplePlayerDlg();
	

	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(CTrimmerObjControlCB, ITrimmerObjControlCB);
	STDMETHOD (OnStop) ( void );
	STDMETHOD (OnStart)( void );
	STDMETHOD (OnPause)( void );
	STDMETHOD (OnError) (HRESULT hr, BSTR Val);
	END_INTERFACE_PART(CTrimmerObjControlCB)

	void OnCompleteTrimming();

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedMark();
	afx_msg void OnBnClickedIndex();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedMarkRight();
	afx_msg void OnBnClickedMarkLeft();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLbnDblclkList();
	afx_msg void OnBnClickedTrim();
	afx_msg void OnTimer(UINT nIDEvent);

	class CTrimNotify : public IEventNotify
	{
	public:
		CTrimNotify (CSimplePlayerDlg * pDlg):
			 m_pDlg(pDlg)
			 {
			 };
	private:
			 STDMETHODIMP OnEvent( long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG );
			 CSimplePlayerDlg * m_pDlg;
	}m_TrimNotify;

	friend CTrimNotify;

	enum buttonType
	{
		buttonBegin = 0,
		buttonStepBW,
		buttonPlay,
		buttonPause,
		buttonStop,
		buttonStepFW,
		buttonEnd,
		buttonOpen,
		buttonSave,
		buttonMarkLeft,		// To mark MPEG2 file fragment
		buttonMarkRight,		// To mark MPEG2 file fragment
		buttonAdd,		// Add an element (video fragment)to List
		buttonTrim,
		buttonRemove,	// Remove an element (video fragment)from List
		buttonNum
	};

	STDMETHODIMP	OnEvent(long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG);

// Dialog Data
	//{{AFX_DATA(CSimplePlayerDlg)
	enum { IDD = IDD_SIMPLEPLAYER_DIALOG };
	CStatic			m_Duration;
	CStatic			m_Time;
	CButton			m_CheckUseIndex;
	CButton			m_CheckVideoOnly;
	CButton			m_Buttons[buttonNum];
	CEdit			m_edFileName;
	CEdit			m_edFileNameSave;
	CSliderCtrl		m_sldPosition;	
	CProgressCtrl	m_Progress;	
	CListBox		m_ctlList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimplePlayerDlg)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	HICON			m_hIcon;
	HACCEL			m_hAccel;
	CPlayer*		m_pPlayer;
	CTrimGrpah*		m_pTrimGraph;
	UINT			m_TimerTrim,
					m_TimerMain;
	CString			m_csProfile;
	
	struct FragmentParams
	{
		FragmentParams():
		nSldrSelPosLeft(0),
		rtLeftTime(0),
		nSldrSelPosRight(0),
		rtRightTime(0)
		{
		}
		UINT			nSldrSelPosLeft;
		REFERENCE_TIME  rtLeftTime;
		UINT			nSldrSelPosRight;
		REFERENCE_TIME  rtRightTime;

	} m_FragmentParams;
	
	enum EnablingType
	{
		EnablingInitedDialog,
		EnablingInitedPlayer,
		EnablingSelectedFragment,
		EnablingTrimingOn,
		EnablingTrimingOff
	};

	void			EnableButtonForPosition();
	void			EnableButtons(EnablingType EnType, BOOL bEnable);
	void			TimeFormat(REFERENCE_TIME rtTime, CString& sTime);	


	// Generated message map functions
	//{{AFX_MSG(CSimplePlayerDlg)
	virtual BOOL	OnInitDialog();
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void	OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );	
	afx_msg void	OnBegin();
	afx_msg void	OnBackward();
	afx_msg void	OnStepBW();
	afx_msg void	OnPlay();
	afx_msg void	OnPause();
	afx_msg void	OnStop();
	afx_msg void	OnStepFW();
	afx_msg void	OnForward();
	afx_msg void	OnEnd();
	afx_msg void	OnOpen();
	afx_msg void	OnFullscreen();
	afx_msg void	OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void KillTrimmingGraph();
	SMM_OutputTypes DetectType( CString csName );
	SMM_OutputTypes m_ftFileType;
};


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



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEPLAYERDLG_H__13EB3B1D_F8A1_476D_960B_62DB25620C0D__INCLUDED_)
