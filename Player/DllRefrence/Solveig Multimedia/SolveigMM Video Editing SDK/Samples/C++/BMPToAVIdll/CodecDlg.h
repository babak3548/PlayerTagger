#pragma once


// CCodecDlg dialog

#include "resource.h"
class CCodecDlg : public CDialog
{
	DECLARE_DYNAMIC(CCodecDlg)

public:
	CCodecDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCodecDlg();

// Dialog Data
	enum { IDD = IDD_CODECDLG };
	CString m_csEncoderFriendlyName;
	BOOL	m_bPrefer;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BSTR InitializeEncoder( IBaseFilter** pEncoderInterface, HRESULT *hr );

protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedProperties();
};
