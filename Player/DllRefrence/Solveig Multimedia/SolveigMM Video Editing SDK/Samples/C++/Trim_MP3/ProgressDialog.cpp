////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2012 Solveig Multimedia
// All rights are reserved. 
//
// Solveig Multimedia reserves the right to make changes without
// notice at any time. Solveig Multimedia makes no warranty,
// expressed, implied or statutory, including but not limited to any implied
// warranty of merchantability of fitness for any particular purpose, or that
// the use will not infringe any third party patent, copyright or trademark.
// Solveig Multimedia must not be liable for any loss or damage
// arising from its use.
// 
//////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Trimmer.h"
#include "ProgressDialog.h"
#include ".\progressdialog.h"

// CProgressDialog dialog

IMPLEMENT_DYNAMIC(CProgressDialog, CDialog)
CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent),
	m_bFinished(FALSE)
{
}

CProgressDialog::~CProgressDialog()
{
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgress);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
//	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CProgressDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlProgress.SetRange32(0, m_lMaxPos);
	m_ctlProgress.SetPos(0);

	m_bFinished = FALSE;

	return TRUE;  
}

void CProgressDialog::SetMaxPosition(long lMaxPos)
{
	m_lMaxPos = lMaxPos;
	m_ctlProgress.SetRange32(0, m_lMaxPos);
	m_ctlProgress.SetPos(0);

	m_bFinished = FALSE;
}

void CProgressDialog::SetNewPosition(long lPos)
{
	m_ctlProgress.SetPos(lPos);

	if (lPos == m_lMaxPos){
		m_bFinished = TRUE;
		EndDialog(1);
	}
}

void CProgressDialog::Stop()
{
	EndDialog(1);
	m_bFinished = TRUE;
}
