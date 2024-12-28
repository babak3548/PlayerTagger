// AviTrimmerApp.h : main header file for the AVITRIMMERAPP application
//

#if !defined(AFX_AVITRIMMERAPP_H__CB97FBFC_6F32_4F8F_A6D1_226291704BD3__INCLUDED_)
#define AFX_AVITRIMMERAPP_H__CB97FBFC_6F32_4F8F_A6D1_226291704BD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAviTrimmerAppApp:
// See AviTrimmerApp.cpp for the implementation of this class
//

class CAVITrimmerAppApp : public CWinApp                         
{
public:
	CAVITrimmerAppApp ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAviTrimmerAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAviTrimmerAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVITRIMMERAPP_H__CB97FBFC_6F32_4F8F_A6D1_226291704BD3__INCLUDED_)
