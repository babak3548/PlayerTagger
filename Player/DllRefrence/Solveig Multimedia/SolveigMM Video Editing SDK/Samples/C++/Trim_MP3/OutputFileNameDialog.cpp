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
// OutputFileNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Trimmer.h"
#include "OutputFileNameDialog.h"


// COutputFileNameDialog dialog

IMPLEMENT_DYNAMIC(COutputFileNameDialog, CDialog)
COutputFileNameDialog::COutputFileNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COutputFileNameDialog::IDD, pParent)
{
}

COutputFileNameDialog::~COutputFileNameDialog()
{
}

void COutputFileNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctlFileName);
}

void COutputFileNameDialog::SetFileName(CString FName)
{
	int i = 0;
	for (i = FName.GetLength(); i>0; i--){
		if ((FName[i] == '/') || (FName[i] == '\\'))
			break;
	}

	m_filename = "";
	for (i++; i<FName.GetLength(); i++){
		m_filename += FName[i];
	}
}


BEGIN_MESSAGE_MAP(COutputFileNameDialog, CDialog)
END_MESSAGE_MAP()


// COutputFileNameDialog message handlers

BOOL COutputFileNameDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlFileName.SetWindowText(m_filename);

	return TRUE;  
}
