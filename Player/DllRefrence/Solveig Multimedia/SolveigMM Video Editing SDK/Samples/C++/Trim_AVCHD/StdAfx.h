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

#if !defined(AFX_STDAFX_H__45473900_DF7E_4F72_AC51_C354D1CE2D10__INCLUDED_)
#define AFX_STDAFX_H__45473900_DF7E_4F72_AC51_C354D1CE2D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>      // MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>        // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <initguid.h>
#include <streams.h>
#include <PropID_EditingEngine.h>
#include <SMM_ProfileParser.h>
#include <Inc\elsdk.h>
#include <idl\AVITrimmerCOM.h>
#include <idl\AVITrimmerCOM_i.c>
#include <PropID_MatroskaDemuxer.h>
#include <PropID_MatroskaMuxer.h>
#include <PropID_MP2FATrimmer.h>
#include <SMM_Utils.h>
#include <SMM_SDKActionKeys.h>
#include <PropID_MPEG4FATrimmer.h>

#define COMPILE_VARIANT_ENGINE_USING   // to use SolveigMM Video Editing engine. 
// Else application builds DirectShow graph with SolveigMM MPEG-4 AVC trimmer filter

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__45473900_DF7E_4F72_AC51_C354D1CE2D10__INCLUDED_)
