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
#include "stdafx.h"
#include <indxdef.h>


#include "SimplePlayer.h"
#include "SimplePlayerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerApp

BEGIN_MESSAGE_MAP(CSimplePlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CSimplePlayerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerApp construction

CSimplePlayerApp::CSimplePlayerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSimplePlayerApp object

CSimplePlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimplePlayerApp initialization

BOOL CSimplePlayerApp::InitInstance()
{
	AfxEnableControlContainer();

	CAutoApartment Auto;
	
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
	
	_CrtSetDbgFlag(tmpFlag);		
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1310
#ifdef _AFXDLL
	#ifndef UNDER_CE
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#endif
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CSimplePlayerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
