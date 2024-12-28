#pragma once

// CSettingsDialog dialog

class CSettingsDialog : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDialog)

public:
	CSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDialog();

// Dialog Data
	enum { IDD = IDD_SETTINGS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSelectfolder();
private:
	CEdit m_ctlOutputFolder;
	CEdit m_ctlComputerID;
	virtual BOOL OnInitDialog();
};
