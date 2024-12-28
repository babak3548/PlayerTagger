#pragma once
#include "afxcmn.h"

// CProgressDialog dialog

class CProgressDialog : public CDialog
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressDialog();
	void SetNewPosition(long lPos);
	void SetMaxPosition(long lMaxPos);
	void Stop();

// Dialog Data
	enum { IDD = IDD_PROGRESS_DIALOG };

	virtual BOOL OnInitDialog();
	BOOL	m_bFinished;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_ctlProgress;
	long		  m_lMaxPos;
};
