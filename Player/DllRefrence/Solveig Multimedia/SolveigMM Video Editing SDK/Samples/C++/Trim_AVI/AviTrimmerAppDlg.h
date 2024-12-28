// AVITrimmerAppDlg.h : header file
//
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

#if !defined(AFX_AVITRIMMERAPPDLG_H__882F88D5_30F0_4A39_BECF_249763C85BBB__INCLUDED_)
#define AFX_AVITRIMMERAPPDLG_H__882F88D5_30F0_4A39_BECF_249763C85BBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <PropID_EditingEngine.h>
#include "mEdit.h"
#include "hyperlink.h"
#include <vector>
#include <dvdmedia.h>
#include "Guids.h"
#include <wmsdkidl.h>
#include "afxcmn.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CAVITrimmerAppDlg dialog


class CAVITrimmerAppDlg : public CDialog
{

// Construction
public:
//	DECLARE_OLECREATE(CAVITrimmerAppDlg)   
	CAVITrimmerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAVITrimmerAppDlg)
	enum { IDD = IDD_AVITRIMMERAPP_DIALOG };
	CEdit			m_ctlFileDst;
	CEdit			m_ctlFileSrc;
	CProgressCtrl	m_ctlProgress;
	CButton			m_StopButton;
	CButton			m_RunButton;
	CmEdit			m_ctlStopTime;
	CmEdit			m_ctlStartTime;
	CmEdit			m_ctlCurTime;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVITrimmerAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	HICON m_hIcon;

    HRESULT Start			( void );
	void	ShowStatus		( void );
	void	EnableButton	( BOOL bFlag );
	
	DECLARE_INTERFACE_MAP()
		
	BEGIN_INTERFACE_PART(CTrimmerObjControlCB, ITrimmerObjControlCB);
	STDMETHOD (OnStop) ( void );
	STDMETHOD (OnStart)( void );
	STDMETHOD (OnPause)( void );
	STDMETHOD (OnError) (HRESULT hr, BSTR Val);
	END_INTERFACE_PART(CTrimmerObjControlCB)
		
	// Generated message map functions
	//{{AFX_MSG(CAVITrimmerAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDialogIn();
	afx_msg void OnDialogOut();
	afx_msg void OnRunGraph();
	afx_msg void OnStopGraph();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	UINT	m_uiTimerId;

public:
	CComPtr <ITrimmerObjControl> m_pITrimmerObjControl;
	CComPtr <IModuleConfig>		 m_pModuleCfg;

	IGraphBuilder	* m_pGraph;
	IMediaControl	* m_pControl;
	IMediaSeeking	* m_pMediaSeek;
	IVideoWindow	* m_pVideoWindow;

	bool 			IsPlaying;
	bool 			IsOpened;
	bool 			IsStateSettingNow;
	bool 			CanChangePosition;
	bool			NoChange;

	int				m_nIsSelecting;
	int				m_nNormalHeight;
	int				m_nNormalWidth;

	LONGLONG		m_llStartPosition;
	LONGLONG		m_llStopPosition;
	LONGLONG		m_llStartSelPos;
	LONGLONG		m_llStopSelPos;

	double			m_dSliderKoef;
	CString			m_valCurTime;
	CStatic			m_ctlHL;

	afx_msg void OnBnClickedPlayPreview			( void );
	afx_msg void OnBnClickedStopPreview			( void );
	afx_msg void OnShowWindow					( BOOL bShow, UINT nStatus );
	afx_msg void OnBnClickedPreviewPause		( void );
	afx_msg void OnNMReleasedCaptureSlider		( NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll						( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedPlaySelected		( void );
	afx_msg void OnBnClickedSetSelectionStart	( void );
	afx_msg void OnBnClickedSetSelectionStop	( void );
	afx_msg void OnEnChangeStartime				( void );
	afx_msg void OnEnChangeStoptime				( void );
	afx_msg void OnActivate						( UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMove							( int x, int y);
	afx_msg void OnBnClickedAddPart				( void );
	afx_msg void OnLbnSelChangeList				( void );
	afx_msg void OnLbnDblclkList				( void );
	afx_msg void OnBnClickedDelPart				( void );

	CSliderCtrl		m_slSeekPosition;

	CButton			m_bDialogIn;
	CBitmapButton	m_bPlay;
	CBitmapButton	m_bPlayTest;
	CBitmapButton	m_bPause;
	CBitmapButton	m_bStop;
	CBitmapButton	m_bLeftSel;
	CBitmapButton	m_bRightSel;
	CBitmapButton	m_bPlaySelect;

	CEdit			m_ebSelect;
	CListBox		m_ctlListBox;
	CHyperlink		m_wndHL;
	CImageList      *m_pTreeImages;

	bool FillTimes		( REFERENCE_TIME maxlen );
	void DeletePiece	( int iIndex );
	void PlayPiece		( LONGLONG StartT, LONGLONG StopT );
	void SetSelection	( REFERENCE_TIME dStart, REFERENCE_TIME dStop, bool IsStart );

public:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int  OnVKeyToItem		( UINT nKey, CListBox* pListBox, UINT nIndex);
	afx_msg void OnBnClickedChange	( void );
	afx_msg void OnBnClickedInvert	( void );
	
	void		 ReopenVideoWindow	( void );
	void		 FreeSourceFile		( void );
	HRESULT 	 OpenMediaFile		( LPCWSTR filename, int * res );
	bool		 IsVideoPin			( IPin * pin );
	void		 ConnToNullRenderer	( IPin * pin );

	CButton 	m_ctlAdd;
	CButton 	m_ctlRemove;
	CButton 	m_ctlChange;
	CButton 	m_ctlInvert;
	CButton 	m_bDialogOut;
	bool		m_bSellChanged;

private:
	
	typedef struct tagVIDEOAUDIOINFO
	{
		CString   strShortInfo;
		CString	  strFullInfo;
		GUID	  StreamType;
		HTREEITEM hItem;
	} VIDEOAUDIOINFO;

	typedef std::vector<VIDEOAUDIOINFO> STREAMGROUP; 

	typedef struct tagSTREAMSINFO
	{
		STREAMGROUP VideoStreams;
		STREAMGROUP AudioStreams;
	} STREAMSINFO;

	typedef struct tagAVStreamsNumbers
	{
	public:
		int  iAudioStreamNumber;
		int  iVideoStreamNumber;

	public:
			 explicit tagAVStreamsNumbers ( int ASN, int VSN			    );
			      	  tagAVStreamsNumbers ( const tagAVStreamsNumbers& AVSN );
	    bool		  operator ==         ( const tagAVStreamsNumbers& rhs  );
		bool		  operator !=		  ( const tagAVStreamsNumbers& rhs	);
	} AVStreamsNumbers;		
	
	enum CtlTreeImageIndex{ CTII_UNCHECKED = 0, CTII_CHECKED = 1 };

private:
	CTreeCtrl		 m_ctlTree;
	STREAMSINFO		 StreamInfo;
	CString			 m_strFileSource;
	bool			 m_bAVStreamNumChanged;
	bool			 m_bStreamClick;
	AVStreamsNumbers m_sGraphAVStreamsNumbers;
	GUID			 m_CurrntSplitterGUID;

private:
	void		   GetStreamsInfo		   ( IEnumPins* pIPins			  );
	VIDEOAUDIOINFO GetVideoInfo			   ( AM_MEDIA_TYPE mt		      );
	VIDEOAUDIOINFO GetAudioInfo			   ( GUID subType);
	CString		   Videoaudioinfo2Str	   ( VIDEOAUDIOINFO vai			  );
	void		   AddStreamInfoToCntlTree ( STREAMGROUP *StreamDescr	  );
	HRESULT        AddStreamsInfoToCntlTree(							  );
	void		   AddImageListToCtlTree   (							  );
	void		   SelectStream			   ( STREAMGROUP *StreamGroup
						    				,HTREEITEM hItem			  );
	STREAMGROUP*  FindStreamGroup		   ( HTREEITEM hItem			  );
	void		  CheckCTItem			   ( HTREEITEM hItem			  );
	void		  UncheckCTItem			   ( HTREEITEM hItem			  );
	bool		  IsCTItemChecked		   ( HTREEITEM hItem			  );
	int			  GetAudioStreamNumber     (							  );
	int			  GetVideoStreamNumber     (							  );
	int			  GetStreamNumber          ( STREAMGROUP *StreamGroup	  );
	HRESULT		  BuildSourceSplitterPart  ();
	HRESULT		  BuildSourceSplitterPartAVI();
	HRESULT		  BuildSourceSplitterPartASF();

private:
	HRESULT		  ConnectSplitterPins      ( AVStreamsNumbers *sAVStreamsNumbers );
	HRESULT       ConnectSplitterPin       ( int		   iStreamNumber
											,int		   *piPinNumber
											,IPin		   *pIPSplitPin			 );
	HRESULT       DeleteGraph              (									 );
	HRESULT       CreateGraph              ( AVStreamsNumbers *sAVStreamsNumbers );
	HRESULT       ReCreateGraph            ( AVStreamsNumbers *sAVStreamsNumbers );

private:
	CComPtr<IBaseFilter> FindFilterByGUID    ( const GUID &guid					 );
	AVStreamsNumbers	 GetAVStreamsNumbers (									 );
	void                 LoadButtonBitmap    ( CBitmapButton *pBut
											  ,UINT			  uiButId
											  ,UINT			  uiBitmapUp
											  ,UINT			  uiBitmapDown
											  ,UINT			  uiBitmabDis		 );
	void				OpenSourceFile       ( const CString  &strFileSource	 );
	void                ParseCommandLine     (									 );
	PCHAR*				CommandLineToArgvA	 ( PCHAR CmdLine, int* _argc		 );

private:
	bool	 m_bWasSourceFileInCommandLine;
	CString  m_strCommandLineSourceFile;
		
public:
	afx_msg void OnNMClickTreeStreams(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckTrimOverlapped();
private:
	CButton m_chbTrimOverlappedIntervals;
	CButton m_chbFrameAccuracy;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVITRIMMERAPPDLG_H__882F88D5_30F0_4A39_BECF_249763C85BBB__INCLUDED_)