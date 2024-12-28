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
#include <PropID_OCXSlider.h>

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
		buttonAdd,		// Add an element (video fragment)to List
		buttonRemove,	// Remove an element (video fragment)from List
		buttonSel,		// Add an element (video fragment)to List
		buttonDesel,	// Remove an element (video fragment)from List
		buttonTrim,
		buttonNum,

	};

	STDMETHODIMP	OnEvent(long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG);

// Implementation
protected:
	DECLARE_EVENTSINK_MAP()
	void MarkerDownSmmsliderctrl(long lMarkerNumber);
	void MarkerMovedSmmsliderctrl(long lMarkerNumber);
	void MarkerMovingSmmsliderctrl(long lMarkerNumber);
	void SliderDownSmmsliderctrl();
	void SliderMovedSmmsliderctrl();
	void SliderMovingSmmsliderctrl();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimplePlayerDlg)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

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
		EnablingTrimingOn,
		EnablingTrimingOff
	};

	void			EnableButtons(EnablingType EnType, BOOL bEnable);
	void			TimeFormat(REFERENCE_TIME rtTime, CString& sTime);	

	void OnCompleteTrimming();

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedSelectInterval();
	afx_msg void OnBnClickedDeselectInterval();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedTrim();
	afx_msg void OnTimer(UINT nIDEvent);

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
	// Dialog Data
	//{{AFX_DATA(CSimplePlayerDlg)
	enum { IDD = IDD_SIMPLEPLAYER_DIALOG };
	CStatic			m_Duration;
	CStatic			m_Time;
	CStatic			m_BeginTime;
	CStatic			m_EndTime;

	CButton			m_CheckUseIndex;
	CButton			m_CheckVideoOnly;
	CButton			m_Buttons[buttonNum];
	CEdit			m_edFileName;
	CEdit			m_edFileNameSave;
	CProgressCtrl	m_Progress;	
	CSMMSliderCtrlWrap m_sliderCtrl;
	//}}AFX_DATA

};





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEPLAYERDLG_H__13EB3B1D_F8A1_476D_960B_62DB25620C0D__INCLUDED_)
