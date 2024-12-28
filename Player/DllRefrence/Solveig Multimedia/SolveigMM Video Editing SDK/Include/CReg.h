#ifndef __CReg_H_
#define __CReg_H_

/*	Helper class for work with registry
	The operator [] keep the name for registry value
	And operators << or >> - write or read value from registry
	for the saved name*/

//////////////////////////////////////////////////////////////////////////////
class xCRegSetting
{
	HKEY			m_hKey;
	TCHAR			*m_pValueName;
public:
	xCRegSetting(TCHAR * szKey, int nInstance = 0)
	{
		TCHAR			szKeyOpen[1024] = {0};
//		wsprintf(szKeyOpen,_T("%s\\%d"), szKey, nInstance);
		wsprintf(szKeyOpen,_T("%s"), szKey);
		if ( ERROR_SUCCESS != RegCreateKeyEx( HKEY_CLASSES_ROOT, szKeyOpen, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &m_hKey, NULL) )
			m_hKey = 0;
	}
	~xCRegSetting()
	{
		RegCloseKey(m_hKey);
		m_hKey = 0;
	}
	xCRegSetting & operator [] (TCHAR * szValueName)
	{
		m_pValueName = szValueName;
		return *this;
	}
	xCRegSetting & operator << (DWORD dwValue)
	{
		RegSetValueEx(m_hKey, m_pValueName, 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD));
		return *this;
	}
	xCRegSetting & operator >> (DWORD &dwValue)
	{
		DWORD		dwDataSize = sizeof(DWORD);
		DWORD		dwType = REG_DWORD;
		RegQueryValueEx(m_hKey, m_pValueName, 0, &dwType, (LPBYTE)&dwValue, &dwDataSize);
		return *this;
	}
	xCRegSetting & operator << (TCHAR * szValue)
	{
		RegSetValueEx(m_hKey, m_pValueName, 0, REG_SZ, (LPBYTE)szValue, wcslen(szValue) + 1);
		return *this;
	}
	xCRegSetting & operator >> (TCHAR * szValue)
	{
		DWORD		dwDataSize = MAX_PATH;
		DWORD		dwType = REG_SZ;
		RegQueryValueEx(m_hKey, m_pValueName, 0, &dwType, (LPBYTE)szValue, &dwDataSize);
		return *this;
	}
	xCRegSetting & operator << (BOOL bValue)
	{
		return operator << ((DWORD)bValue);
	}
	xCRegSetting & operator >> (BOOL & bValue)
	{
		return operator >> ((DWORD&)bValue);
	}
};

#endif//#ifndef __CReg_H_