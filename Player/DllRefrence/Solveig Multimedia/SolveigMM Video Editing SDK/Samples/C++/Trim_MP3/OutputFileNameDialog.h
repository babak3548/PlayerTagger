#pragma once


// COutputFileNameDialog dialog

class COutputFileNameDialog : public CDialog
{
	DECLARE_DYNAMIC(COutputFileNameDialog)

public:
	COutputFileNameDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COutputFileNameDialog();
	void SetFileName(CString FName);

// Dialog Data
	enum { IDD = IDD_OUTPUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CString m_filename;
public:
	virtual BOOL OnInitDialog();
	CEdit m_ctlFileName;
	afx_msg void OnBnClickedCancel();
};
