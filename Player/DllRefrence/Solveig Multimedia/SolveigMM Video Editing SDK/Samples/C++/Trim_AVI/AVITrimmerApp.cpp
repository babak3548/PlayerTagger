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

// AviTrimmerApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <Idl\AVITrimmerCOM_i.c>
#include <Idl\ModuleConfig_i.c>

#include "AviTrimmerApp.h"
#include "AviTrimmerAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAviTrimmerAppApp

BEGIN_MESSAGE_MAP(CAVITrimmerAppApp , CWinApp)
	//{{AFX_MSG_MAP(CAviTrimmerAppApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAviTrimmerAppApp construction

CAVITrimmerAppApp ::CAVITrimmerAppApp ()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAviTrimmerAppApp object

CAVITrimmerAppApp  theApp;

/////////////////////////////////////////////////////////////////////////////
// CAviTrimmerAppApp initialization

BOOL CAVITrimmerAppApp ::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	CAVITrimmerAppDlg *pDlg = new CAVITrimmerAppDlg();
	m_pMainWnd = pDlg;
	
	int nResponse = IDOK;
	if ( pDlg != NULL && (nResponse = pDlg->DoModal()) == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		// dismissed with Cancel
	}
	delete pDlg;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString Sec2Hours(DWORD dsSec)
{
	
	TCHAR ch[20];
	
	DWORD dwHours	 =  dsSec / 3600;;
	DWORD dwMinutes  = ((DWORD) dsSec % 3600) / 60;
	DWORD dwSeconds  = ((DWORD) dsSec % 3600) - dwMinutes * 60;
	DWORD dwMSeconds = ((DWORD) dsSec % 3600) - dwMinutes * 60 - dwSeconds;
	
	_stprintf(ch,_T("%.2u%.2u%.2u%.3u%"),dwHours,dwMinutes,dwSeconds,dwMSeconds);
	
	CString cs(ch);
	return cs;
}


DWORD	Hours2MSec	( CString val )
{
	DWORD dwHours	= _tstoi((LPCTSTR)val.Mid(0,2));
	DWORD dwMinutes = _tstoi((LPCTSTR)val.Mid(2,2));
	DWORD dwSeconds = _tstoi((LPCTSTR)val.Mid(4,2));
	DWORD dwMSeconds= _tstoi((LPCTSTR)val.Mid(6,3));
	
	DWORD dwResMSec	= ( ( (dwHours * 3600) + (dwMinutes * 60) + dwSeconds) * 1000) + dwMSeconds;
	
	return dwResMSec;
}

CString Sec2Hours2(REFERENCE_TIME rtTime)
{	
	TCHAR ch[20];
	DWORD dwMsec	 = DWORD(rtTime / 10000);
	DWORD dwSec		 = dwMsec / 1000;
	DWORD dwHours	 = dwSec / 3600;;
	DWORD dwMinutes  = (dwSec % 3600) / 60;
	DWORD dwSeconds  = (dwSec % 3600) - dwMinutes * 60;
	DWORD dwMSeconds = dwMsec % 1000;

	_stprintf(ch,_T("%.2u:%.2u:%.2u:%.3u"),dwHours,dwMinutes,dwSeconds, dwMSeconds );
	CString cs(ch);

	return cs;
}

void ConvertTime2String(__TSTrimInfo tt, LPTSTR str)
{
	if(str == NULL){
		return;
	}

	TCHAR ch[100];
	TCHAR cstart[40];

	DWORD dwMsec	 = DWORD(tt.llStartPos / 10000);
	DWORD dwSec		 = dwMsec / 1000;
	DWORD dwHours	 = dwSec / 3600;;
	DWORD dwMinutes  = (dwSec % 3600) / 60;
	DWORD dwSeconds  = (dwSec % 3600) - dwMinutes * 60;
	DWORD dwMSeconds = dwMsec % 1000;

	_stprintf(ch,_T("%.2u:%.2u:%.2u:%.3u"),dwHours,dwMinutes,dwSeconds, dwMSeconds );
	_tcscpy(cstart, ch);

	dwMsec		= DWORD(tt.llStopPos / 10000);
	dwSec		= dwMsec / 1000;
	dwHours		= dwSec / 3600;;
	dwMinutes	= (dwSec % 3600) / 60;
	dwSeconds	= (dwSec % 3600) - dwMinutes * 60;
	dwMSeconds	= dwMsec % 1000;

	_stprintf(ch,_T(" - %.2u:%.2u:%.2u:%.3u"),dwHours,dwMinutes,dwSeconds, dwMSeconds );
	_tcscat(cstart, ch);
	_tcscpy(str,cstart);
}

// string format hhmmssmmm
//				 015439320	
// return in 100 nano sec UNITS

ULONGLONG ConvertString2Time(LPCTSTR str)
{
	ULONGLONG ulTime	= 0;
	TCHAR	  ch [10]	= {'0'};

	// Copies n bytes of a string to a destination string.

	_tcsncpy( ch, str, 2 );
	DWORD dwHours = _tstoi(ch);

	_tcsncpy(ch,str + 2, 2 );
	DWORD dwMinutes = _tstoi(ch);

	_tcsncpy(ch,str + 4, 2 );
	DWORD dwSeconds = _tstoi(ch);

	_tcsncpy(ch,str + 6, 3 );
	DWORD dwMSeconds = _tstoi(ch);

	DWORD dwResMSec     = ( ( (dwHours * 3600) + (dwMinutes * 60) + dwSeconds) * 1000) + dwMSeconds;

	ulTime = (ULONGLONG)dwResMSec *  10000;

	return ulTime ;
}

// string format hh:mm:ss:mmm
//				 01:54:39:320	
// return in 100 nano sec UNITS
ULONGLONG ConvertString2Time2(LPCTSTR str)
{
	ULONGLONG	ulTime	= 0;
	TCHAR		ch [10] = {'0'};

	// Copies n bytes of a string to a destination string.
	_tcsncpy(ch,str, 2);
	DWORD dwHours = _tstoi(ch);

	_tcsncpy(ch,str + 3, 2);
	DWORD dwMinutes = _tstoi(ch);

	_tcsncpy(ch,str + 6, 2);
	DWORD dwSeconds = _tstoi(ch);

	_tcsncpy(ch,str + 9, 3);
	DWORD dwMSeconds = _tstoi(ch);

	DWORD dwResMSec     = ( ( (dwHours * 3600) + (dwMinutes * 60) + dwSeconds) * 1000) + dwMSeconds;

	ulTime = (ULONGLONG)dwResMSec *  10000;

	return ulTime ;
}


void ProcessHRESULT(HRESULT hr)
{
	TCHAR str[MAX_ERROR_TEXT_LEN + 1];
	AMGetErrorText(hr, str, MAX_ERROR_TEXT_LEN);
	TCHAR szMsg[255];			
	LoadString(	 GetModuleHandle( NULL )	
				,IDS_STR_MSG_CAPT_ERROR					
				,szMsg						
				,255			
			);							
	MessageBox(NULL, str, szMsg ,MB_OK | MB_ICONERROR);
}


