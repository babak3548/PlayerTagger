
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

#ifndef _AUTO_APARTMENT_
#define _AUTO_APARTMENT_

#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif // _WIN32_DCOM

////////////////////////////////////////////////////////
// CAutoApartment
class CAutoApartment
{
public:
#if !defined UNDER_CE
	CAutoApartment() : m_bApartment(SUCCEEDED(::CoInitialize(NULL)))
#else		
	CAutoApartment() : m_bApartment(SUCCEEDED(::CoInitializeEx(NULL,COINIT_MULTITHREADED)) )
#endif
	{
	}

	~CAutoApartment()
	{
		if(m_bApartment)
			::CoUninitialize();
	}

	BOOL		IsSingleThreadApartment() const
	{
		return m_bApartment;
	}
private:
	BOOL		m_bApartment;
};

class CAutoMultiThread
{
public:
	CAutoMultiThread() : m_bMultiThread(SUCCEEDED(CoInitializeEx(NULL,COINIT_MULTITHREADED | COINIT_SPEED_OVER_MEMORY)))
	{
	}
	
	~CAutoMultiThread()
	{
		if(m_bMultiThread)
			::CoUninitialize();
	}
	
	BOOL		IsMultiThread() const
	{
		return m_bMultiThread;
	}
private:
	BOOL		m_bMultiThread;
};


/////////////////////////////////////////////////////////////////////////////
// CMarshalHelper
template <class Interface, const CLSID* pClsid = &__uuidof(Interface)> class CMarshalHelper
{
public:
	CMarshalHelper(Interface* pPtrToMarshal):
		  m_pMarshalStream(NULL)
	{
		// Create marshalling object
		HRESULT hr = CoMarshalInterThreadInterfaceInStream(*pClsid, pPtrToMarshal, &m_pMarshalStream);
		if(FAILED(hr))
			throw hr;
	} 

	~CMarshalHelper()
	{
		if(m_pMarshalStream)
			m_pMarshalStream->Release();
	}

	HRESULT GetUnmarshaledPtr(Interface** ppInterface)
	{
		HRESULT hr = E_FAIL;
		if(m_pMarshalStream)
		{
			hr = CoGetInterfaceAndReleaseStream(m_pMarshalStream, *pClsid,	(LPVOID*)ppInterface);
			m_pMarshalStream = NULL;
		}
		return hr;
	}

private:
   IStream*				m_pMarshalStream;
};

#endif// _AUTO_APARTMENT_
