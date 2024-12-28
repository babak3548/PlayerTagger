// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F3FD6254_9A49_4D6E_93B0_5D6CB447DC91__INCLUDED_)
#define AFX_STDAFX_H__F3FD6254_9A49_4D6E_93B0_5D6CB447DC91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <streams.h>
//#include <dxerr9.h>
#include <qedit.h>

#include <Idl\AVITrimmerCOM.h>
#include <Idl\ModuleConfig.h>
#include <PropID_EditingEngine.h>

CString Sec2Hours	( DWORD dsSec );
DWORD	Hours2MSec	( CString val );

void	ProcessHRESULT	( HRESULT hr );
CString Sec2Hours2		( REFERENCE_TIME rtTime );

ULONGLONG	ConvertString2Time2	( LPCTSTR str );
ULONGLONG	ConvertString2Time	( LPCTSTR str );
void		ConvertTime2String	( __TSTrimInfo tt, LPTSTR str );

#define MAX_RES_STR_LEN 4097;

#define ONEARG_MESSAGE_BOX( MESSAGE ) \
{ \
	TCHAR szMsg[255];			\
	LoadString(	 GetModuleHandle( NULL )	\
				,MESSAGE					\
				,szMsg						\
				,255			\
				);							\
   MessageBox( szMsg );						\
}

#define TWOARG_MESSAGE_BOX( MESSAGE, CAPT)	\
{											\
	TCHAR szMsg[255];			\
	TCHAR szCapt[255];			\
	LoadString(	 GetModuleHandle( NULL )	\
				,MESSAGE					\
				,szMsg						\
				,255			\
				);							\
	LoadString(	 GetModuleHandle( NULL )	\
				,CAPT						\
				,szCapt						\
				,255			\
				);							\
	MessageBox( szMsg, szCapt );			\
}
#define TWOARG_MESSAGE_BOX_ICON_ERROR( MESSAGE, CAPT)	\
{											\
	TCHAR szMsg[255];			\
	TCHAR szCapt[255];			\
	LoadString(	 GetModuleHandle( NULL )	\
	,MESSAGE					\
	,szMsg						\
	,255			\
	);							\
	LoadString(	 GetModuleHandle( NULL )	\
	,CAPT						\
	,szCapt						\
	,255			\
	);							\
	MessageBox( szMsg, szCapt, MB_OK | MB_ICONERROR );			\
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F3FD6254_9A49_4D6E_93B0_5D6CB447DC91__INCLUDED_)
