
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


#ifndef _SDK_UTILS_
#define _SDK_UTILS_


/////////////////////////////////////////////////////////
// String conversion

LPWSTR	WINAPI GetWCHAR(LPCTSTR pIn, LPWSTR pOut);
LPTSTR	WINAPI GetTCHAR(LPCWSTR pIn, LPTSTR pOut);
LPTSTR	WINAPI GetTCHAR(LPCSTR pIn, LPTSTR pOut);

BOOL	WINAPI CheckUpFile(LPCTSTR csFilePath);

HRESULT	WINAPI ConvertString2Variant(LPCTSTR type, LPCTSTR value, VARIANT* pValue);
HRESULT	WINAPI ConvertVariant2String(VARIANT& pValue, LPTSTR type, LPTSTR value);
HRESULT	WINAPI ConvertB2T(LPBYTE pData, DWORD dwLen, LPTSTR* ptsData);
HRESULT	WINAPI ConvertT2B(LPCTSTR ptsData, LPBYTE* pData, DWORD* pdwLen);

HRESULT	WINAPI ShowPropPage(IUnknown* pUnk, HWND hParentWindow, LPCTSTR szTitle);

typedef std::basic_string<TCHAR>	CTBString;

template<class T>
void		ReleaseList(T& lst)
{	
	while(!lst.empty())
	{
		if(lst.front())
			delete lst.front();

		lst.pop_front();
	}

	return;
}

template<class T>
void		ReleaseMapSecond(T& mp)
{		
	while(!mp.empty())
	{
		T::iterator it = mp.begin();

		if((*it).second)
			delete (*it).second;

		mp.erase(it);
	}

	return;
}

template<class T>
HRESULT		ReleaseMapSecondByItem(T* mp, UINT id)
{
	if(mp)
	{
		T::iterator it =  mp->find(id);
		if(it != mp->end())
		{
			if((*it).second)
				delete (*it).second;
			mp->erase(it);
			return S_OK;
		}
	}
	
	return E_FAIL;
}

/////////////////////////////////////////////////////////
// Registry classes

namespace ElUtils
{
	////////////////////////////////////////////////////////
	// Win32 API syncronisation object wrappers
	class CW32Event
	{
	public:
		CW32Event(BOOL bManual = FALSE, BOOL bInitialState = FALSE, LPCTSTR tcsName = NULL, LPSECURITY_ATTRIBUTES lpEventAttributes = NULL) : 
				m_hEvent(CreateEvent(lpEventAttributes, bManual, bInitialState, tcsName)),
				m_bManual(bManual),
				m_tcsEventName(tcsName ? m_tcsEventName = _tcsdup(tcsName) : NULL)
		{}

		// copy constructor throws HRESULT if failed to duplicate handle
		CW32Event(const CW32Event& ev) : 
				m_hEvent(NULL),
				m_bManual(ev.m_bManual),
				m_tcsEventName(ev.m_tcsEventName ? m_tcsEventName = _tcsdup(ev.m_tcsEventName) : NULL)
		{
			if(!DuplicateHandle(NULL, ev, NULL, &m_hEvent, 0, FALSE, DUPLICATE_SAME_ACCESS))
			{
				if(m_tcsEventName)
				{
					free((LPVOID)m_tcsEventName);
					m_tcsEventName = NULL;
				}
				throw HRESULT_FROM_WIN32(GetLastError());
			}
		}

		virtual ~CW32Event()
		{
			CloseHandle(m_hEvent);
			if(m_tcsEventName)
				free((LPVOID)m_tcsEventName);

		}

		///////////////////////////////////////////////////////////////////////
		// Operators
		operator HANDLE() const
		{
			return m_hEvent;
		}
		
		// operator =() throws HRESULT if failed to duplicate handle
		virtual CW32Event& operator =(const CW32Event& ev)
		{
			if(&ev != this)
			{
				// Destroy previos object
				CloseHandle(m_hEvent);
				m_hEvent = NULL;
				if(m_tcsEventName)
				{
					free((LPVOID)m_tcsEventName);
					m_tcsEventName = NULL;
				}

				// Try to ge dublicate of the handle
				if(!DuplicateHandle(NULL, ev, NULL, &m_hEvent, 0, FALSE, DUPLICATE_SAME_ACCESS))
					throw HRESULT_FROM_WIN32(GetLastError());

				
				if(ev.m_tcsEventName)
					m_tcsEventName = _tcsdup(ev.m_tcsEventName);

				m_bManual = ev.m_bManual;
			}
			return *this;
		}
		///////////////////////////////////////////////////////////////////////
		// 
		LPCTSTR		GetName() const
		{
			return m_tcsEventName;
		}

		BOOL		IsManual() const
		{
			return m_bManual;
		}

		//////////////////////////////////////////////////////////////////////
		// Operations
		BOOL		Set()
		{
			return SetEvent(m_hEvent);
		}

		BOOL		Reset()
		{
			return ResetEvent(m_hEvent);
		}

		BOOL		Wait(DWORD dwTimeout = 0) const
		{
			return WaitForSingleObject(m_hEvent, dwTimeout) == WAIT_OBJECT_0;
		}

		BOOL		IsSet() const
		{
			_ASSERT(m_bManual);// don't do it with automatic events!!!
			return WaitForSingleObject(m_hEvent, 0) == WAIT_OBJECT_0; //WAIT_TIMEOUT;
		}

	private :
		HANDLE		m_hEvent;
		BOOL		m_bManual;
		LPCTSTR		m_tcsEventName;
	};

	class CW32CritSec
	{
	public:
		CW32CritSec()
		{
			InitializeCriticalSection(&m_cs);
		}

		virtual ~CW32CritSec()
		{
			DeleteCriticalSection(&m_cs);
		}

		void	Lock()
		{
			EnterCriticalSection(&m_cs);
		}
		void	Unlock()
		{
			LeaveCriticalSection(&m_cs);
		}

		class	CAutoLock
		{
		public:
			CAutoLock(const CW32CritSec& cs) : m_cs(const_cast<CW32CritSec&>(cs))
			{
				m_cs.Lock();
			}

			~CAutoLock()
			{
				m_cs.Unlock();
			}
		private:
			CW32CritSec& m_cs;			
		};

	private:
		CRITICAL_SECTION	m_cs;

	private:
		// Not supported
		CW32CritSec(const CW32CritSec&);
		CW32CritSec& operator =(const CW32CritSec&);
	};
	typedef CW32CritSec::CAutoLock CLockedScope;



	////////////////////////////////////////////////////////
	// Regestry helpers
	class	CRegKey 
	{
	public:
		CRegKey();
		CRegKey(HKEY hRootKey, LPCTSTR tcsName);
		~CRegKey();
		
		/////////////////////////////////////////////////////////////////////////////////////
		// HKEY operator
		operator HKEY () const 
		{
			return m_hKey; 
		};

		/////////////////////////////////////////////////////////////////////////////////////
		// Open Key methods
		HRESULT		Open(HKEY hRootKey, LPCTSTR tcsKeyName, REGSAM keyAccesss = KEY_READ | KEY_WRITE);
		HRESULT		Open(LPCTSTR tcsName = NULL);

#if !defined UNDER_CE
		HRESULT		OpenRemote(LPCTSTR tcsComputerName, HKEY hRootKey, LPCTSTR tcsKeyName, REGSAM keyAccesss = KEY_READ);
#endif	
		/////////////////////////////////////////////////////////////////////////////////////
		// Create Key methods
		HRESULT		Create(HKEY hRootKey, LPCTSTR tcsName);
		HRESULT		Create(LPCTSTR tcsName = NULL);
		void		Close();


		/////////////////////////////////////////////////////////////////////////////////////
		// Read/Write value methods
		BOOL		GetBOOL(LPCTSTR tcsValueName, BOOL bDefault);
		HRESULT		SetBOOL(LPCTSTR tcsValueName, BOOL bValue);

		DWORD		GetDWORD(LPCTSTR tcsValueName, DWORD dwDefault);
		HRESULT		SetDWORD(LPCTSTR tcsValueName, DWORD dwValue);

		LPTSTR		GetString(LPCTSTR tcsValueName, LPCTSTR tcsDefault, LPTSTR tsResult, int cbSize);
		HRESULT		SetString(LPCTSTR tcsValueName, LPCTSTR tcsString);

		DWORD		GetBinary(LPCTSTR tcsValueName, const LPVOID pDefault, LPVOID pResult, int cbSize);
		HRESULT		SetBinary(LPCTSTR tcsValueName, LPVOID pData, int cbSize);
		

		/////////////////////////////////////////////////////////////////////////////////////
		// Deleting value method
		HRESULT		DeleteValue(LPCTSTR tcsValueName);


	protected:
		TCHAR		m_tcsKeyName[MAX_PATH];
		HKEY		m_hKey;
		HKEY		m_hRootKey;
	};

	class CRegKeySR	:	public CRegKey
	{
	public:
		
		CRegKeySR();
		CRegKeySR(HKEY hRootKey, LPCTSTR tcsName);
		
		HRESULT			Save(LPCTSTR name, BOOL);
		HRESULT			Save(LPCTSTR name, LONG);
		HRESULT			Save(LPCTSTR name, DWORD);
		HRESULT			Save(LPCTSTR name, LPCTSTR);
		
		BOOL			Read(LPCTSTR name, BOOL&);
		BOOL			Read(LPCTSTR name, LONG&);
		BOOL			Read(LPCTSTR name, DWORD&);
		BOOL			Read(LPCTSTR name, CTBString&);		
	};

	class CRegEnumKey 
	{
	public:
		CRegEnumKey(HKEY hKey)
		{
			m_hKey = hKey;
			m_dwIndex = 0;
		}

		~CRegEnumKey()
		{
		}

		LONG Next(LPTSTR pszStr, DWORD cbName)
		{
			FILETIME	ftLastWriteTime;
			LONG lRet =  RegEnumKeyEx(m_hKey, m_dwIndex, pszStr, 
							&cbName, NULL, NULL, NULL, &ftLastWriteTime); 
 
			m_dwIndex++;
			return lRet;
		}


		void Reset()
		{
			m_dwIndex = 0;
		}
	protected: 
		HKEY	m_hKey;
		DWORD	m_dwIndex;
	};

	class CRegEnumValue 
	{
	public:
		CRegEnumValue(HKEY hKey)
		{
			m_hKey = hKey;
			m_dwIndex = 0;
		}

		~CRegEnumValue()
		{
		}

		LONG Next(LPTSTR pszStr, DWORD cbName, LPDWORD pType)
		{
			LONG lRet =  RegEnumValue(m_hKey, m_dwIndex, pszStr, 
							&cbName, NULL, pType, NULL, NULL); 
 
			m_dwIndex++;
			return lRet;
		}


		void Reset(void)
		{
			m_dwIndex = 0;
		}
	protected: 
		HKEY	m_hKey;
		DWORD	m_dwIndex;
	};	
};

#ifndef SCOPE_LOCK
#define SCOPE_LOCK(cs) 	ElUtils::CW32CritSec::CAutoLock _scope_auto_lock_cs(cs);
#endif

#endif //_SDK_UTILS_
