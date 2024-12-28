#pragma once


// CEncoderSelectionDialog dialog
#include "resource.h"
#include "afxwin.h"

class CEncoderSelectionDialog : public CDialog
{
	DECLARE_DYNAMIC(CEncoderSelectionDialog)

public:
	CEncoderSelectionDialog( BOOL bVideo, TCHAR *szFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~CEncoderSelectionDialog();

// Dialog Data
	enum { IDD = IDD_ENCODER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkList2();
	CListBox m_EncoderList;

	DECLARE_MESSAGE_MAP()

protected:
	BOOL		m_bVideo;
	TCHAR		m_szFile[ MAX_PATH ];

	GUID		m_Guids[ 100 ];
	UINT		m_nGuidCount;
	UINT		m_nCurrIndex;
	
	GUID		m_ResultGUID;
	CString	m_szResultName;

public:
	GUID		GetEncoderGUID ( void );
	CString	GetEncoderName( void  );

	afx_msg void OnClose();
};
