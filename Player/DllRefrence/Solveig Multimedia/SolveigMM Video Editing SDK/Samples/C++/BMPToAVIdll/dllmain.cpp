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
// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>
#include <afxtempl.h>

#ifndef AVI_DLL
#define AVI_DLL
#endif
#include "InternalGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE BmpToAviDLL = { NULL, NULL };
CArray<CInternalGraph*>		g_InstArray;
CCritSec					g_csArrayCritSec;
HINSTANCE					g_dllInstance = NULL;
CString						g_EncoderName = L"";
CCritSec					g_EncoderCriticalSec;

void FreeInstances( void )
{
	LONG lNum = (LONG)g_InstArray.GetCount();
	for( LONG l = 0; l < lNum; l++ )
	{
		CAutoLock lock( &g_csArrayCritSec );
		delete g_InstArray.GetAt( l );
	}
	g_InstArray.RemoveAll();
}

BOOL CheckIsValid( CInternalGraph* pGraphInst, LONG *plPos )
{
	CheckPointer( plPos, E_POINTER );
	CAutoLock lock( &g_csArrayCritSec );
	*plPos = (LONG)g_InstArray.GetCount();
	for( LONG l = 0; l < *plPos; l++ )
		if( g_InstArray.GetAt(l) == pGraphInst )
		{
			*plPos = l;
			return TRUE;
		}

	*plPos = 0;
	return FALSE;
}

//Exported methods

LPVOID CreateNewStream( void )
{
	CAutoLock lock( &g_csArrayCritSec );
	CInternalGraph* pGraph = new CInternalGraph( g_dllInstance );
	if( !pGraph )
		return NULL;
	g_InstArray.Add( pGraph );
	return pGraph;
}
void ReleaseStream( LPVOID pInstance )
{
	LONG lPos = -1;
	CInternalGraph* pGraphInst = (CInternalGraph*)pInstance;
	{
		CAutoLock lock( &g_csArrayCritSec );
		for( LONG l = 0; l < g_InstArray.GetCount(); l++ )
			if( g_InstArray.GetAt(l) == pGraphInst )
				g_InstArray.RemoveAt( lPos = l );
	}
	if( lPos != (-1) )
	{
		pGraphInst->CloseStream(FALSE);
		delete pGraphInst;
	}
}
HRESULT OpenAVIStream( BSTR bstFileName, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->OpenAVIStreamIn( bstFileName );
	else
		return E_FAIL;

}

BSTR ChooseEncoder( LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
	{
		CAutoLock lock(&g_EncoderCriticalSec);	
		return pInst->ChooseTheEncoder( g_EncoderName );
	}
	else
		return L"";
}

HRESULT SetStreamProperties( LONG lHeight, LONG lWidth, LONGLONG llFrameDuration, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->SetStreamProps( lHeight, lWidth, llFrameDuration );
	else
		return E_FAIL;
}

HRESULT WriteImage( HBITMAP hInputBitmap, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->WriteImageToAvi( hInputBitmap );
	else
		return E_FAIL;
}

HRESULT CloseAVIStream( BOOL bTerminate, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->CloseStream( bTerminate );
	else
		return E_FAIL;

}

HRESULT GetAVIFileInfo( BYTE* Params, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->ReadProperties( (StreamParameters*) Params );
	else
		return E_FAIL;
}
BYTE* ReadImageFromStream( LONGLONG llFrame, LONG* plTotalBytes, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->ReadImage( llFrame, plTotalBytes );
	else
		return NULL;

}
void FreeImage ( BYTE* pBuffer, LPVOID pInstance )
{
	LONG lPos;
	CInternalGraph* pInst = (CInternalGraph*)pInstance;
	if( CheckIsValid( pInst, &lPos ) )
		return pInst->DeleteImageBuffer( (char*)pBuffer );

}



extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("BmpToAvi.DLL Initializing!\n");
		CoInitialize(NULL);
		//g_pInternalGraph = new CInternalGraph(hInstance);
		g_dllInstance = hInstance;
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(BmpToAviDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(BmpToAviDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("BmpToAvi.DLL Terminating!\n");
		FreeInstances();
		// Terminate the library before destructors are called
		AfxTermExtensionModule(BmpToAviDLL);
	}
	return 1;   // ok
}
