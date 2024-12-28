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
// SettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Trimmer.h"
#include "SettingsDialog.h"
#include "register_work.h"
#include "cgfiltyp.h"

// CSettingsDialog dialog

IMPLEMENT_DYNAMIC(CSettingsDialog, CDialog)
CSettingsDialog::CSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDialog::IDD, pParent)
{
}

CSettingsDialog::~CSettingsDialog()
{
}

void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTPUT_FOLDER, m_ctlOutputFolder);
	DDX_Control(pDX, IDC_COMPUTER_ID, m_ctlComputerID);
}


BEGIN_MESSAGE_MAP(CSettingsDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SELECTFOLDER, OnBnClickedButtonSelectfolder)
END_MESSAGE_MAP()


// CSettingsDialog message handlers

void CSettingsDialog::OnBnClickedOk()
{
	CRegWork regwork;	

	TCHAR szPath[1000] = {0};
	CString szCompID;

	m_ctlOutputFolder.GetWindowText(szPath, 999);
	m_ctlComputerID.GetWindowText(szCompID);
	
	regwork.SetComputerID(_ttoi(szCompID));
	regwork.SetOutPath(szPath);

	regwork.SetExtended(((this->GetCheckedRadioButton(IDC_RADIO_FASTTRIM, IDC_RADIO_NORMALTRIM) == IDC_RADIO_FASTTRIM)?TRUE:FALSE));

	regwork.SetLookAtSamplesTimes(((this->IsDlgButtonChecked(IDC_CHECK_LOOK_AT_SAMPLES_TIMES) == 0)?FALSE:TRUE));

	OnOK();
}

void CSettingsDialog::OnBnClickedCancel()
{
	OnCancel();
}

TCHAR init_path[1000];

static int WINAPI BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
 switch(uMsg)
 { //case BFFM_ENABLEOK: break;
   case BFFM_INITIALIZED:
     SendMessage(hwnd, BFFM_SETSELECTION,1,(LONG)(init_path));
   break;
 }

 UNREFERENCED_PARAMETER(lpData);
 return 0;
}

void CSettingsDialog::OnBnClickedButtonSelectfolder()
{
	TCHAR  szWorkDir[1000] = {0};
	m_ctlOutputFolder.GetWindowText(szWorkDir, 999);
	m_ctlOutputFolder.GetWindowText(init_path, 999);

	BROWSEINFO bi = {this->m_hWnd,
					 NULL,   
					 szWorkDir,
					 _T("Please, select folder for output file."),
					 BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE,
					 (BFFCALLBACK)BrowseCallbackProc,
					 (LPARAM)init_path,
					 0
					};

	LPITEMIDLIST lpItemDList;
	if(!(lpItemDList=SHBrowseForFolder(&bi))) 
		return;
		
	SHGetPathFromIDList(lpItemDList, szWorkDir);

	m_ctlOutputFolder.SetWindowText(szWorkDir);
}

BOOL CSettingsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRegWork RegWork;
	m_ctlOutputFolder.SetWindowText(RegWork.GetOutPath());

	TCHAR compID[10]; 
	_itot(RegWork.GetComputerID(), compID, 10);

	m_ctlComputerID.SetWindowText(compID);

	if (RegWork.IsExtended() == TRUE){
		this->CheckRadioButton(IDC_RADIO_FASTTRIM, IDC_RADIO_NORMALTRIM, IDC_RADIO_FASTTRIM);
	}else{
		this->CheckRadioButton(IDC_RADIO_FASTTRIM, IDC_RADIO_NORMALTRIM, IDC_RADIO_NORMALTRIM);
	}

	if (RegWork.IsLookAtSamplesTimes() == TRUE){
		this->CheckDlgButton(IDC_CHECK_LOOK_AT_SAMPLES_TIMES, BST_CHECKED);
	}else{
		this->CheckDlgButton(IDC_CHECK_LOOK_AT_SAMPLES_TIMES, BST_UNCHECKED);
	}

	return TRUE;  
}
