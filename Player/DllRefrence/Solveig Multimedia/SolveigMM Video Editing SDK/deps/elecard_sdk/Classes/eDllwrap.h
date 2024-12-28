
/////////////////////////////////////////////////////////////////////////////////
//
//	   Copyright (c) 2005 Elecard Ltd.
//	   All rights are reserved.  Reproduction in whole or in part is prohibited
//	   without the written consent of the copyright owner.
//
//	   Elecard Ltd. reserves the right to make changes without
//	   notice at any time. Elecard Ltd. makes no warranty, expressed,
//	   implied or statutory, including but not limited to any implied
//	   warranty of merchantability of fitness for any particular purpose,
//	   or that the use will not infringe any third party patent, copyright
//	   or trademark.
//
//	   Elecard Ltd. must not be liable for any loss or damage arising
//	   from its use.
//
/////////////////////////////////////////////////////////////////////////////////


#ifndef __DLLWRAP_HEADER__
#define __DLLWRAP_HEADER__

class CDllWrapper
{
protected:
	HMODULE	m_hModule;
	
public:
	CDllWrapper(LPOLESTR szLibraryName, HRESULT *pHr = NULL);
	CDllWrapper(LPCTSTR szLibraryName, HRESULT *pHr /* = NULL */);
	~CDllWrapper();
#if !defined UNDER_CE
	FARPROC GetProcAddress(LPCSTR szProcName);
#else
	FARPROC GetProcAddress(LPCWSTR szProcName);
#endif
	
	HRESULT GetClassFactory(REFCLSID clsid, IClassFactory **ppClassFactory);
};

#endif // __DLLWRAP_HEADER__