// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B0DAAE07_DA01_4B49_9423_D72254AFB3A9__INCLUDED_)
#define AFX_STDAFX_H__B0DAAE07_DA01_4B49_9423_D72254AFB3A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


#pragma warning(disable : 4995)
#include <afx.h>
#include <objbase.h>
#include <streams.h>
#include <initGuid.h>
#include <atlstr.h>


#include <SMM_Utils.h>
#include <Idl\ModuleConfig.h>
#include <Idl\AVITrimmerCOM.h>
#include <Idl\AVITrimmerCOM_i.c>
#include <PropID_EditingEngine.h>
#include <PropID_AVITrimmer.h>
#pragma warning(default : 4995)

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B0DAAE07_DA01_4B49_9423_D72254AFB3A9__INCLUDED_)
