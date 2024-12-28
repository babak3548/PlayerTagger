#pragma once

class xCRegSetting
{
	HKEY			m_hKey;
	TCHAR			*m_pValueName;
public:
	xCRegSetting(HKEY hRoot, TCHAR * szKey, int nInstance = 0)
	{
		TCHAR			szKeyOpen[1024];
		_stprintf(szKeyOpen,_T("%s"), szKey);
		if ( ERROR_SUCCESS != RegCreateKeyEx( hRoot, szKeyOpen, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &m_hKey, NULL) )
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
	xCRegSetting & operator << (LPCTSTR szValue)
	{
		RegSetValueEx(m_hKey, m_pValueName, 0, REG_SZ, (LPBYTE)szValue, (DWORD)_tcslen(szValue) + 1);
		return *this;
	}
	xCRegSetting & operator >> (LPTSTR szValue)
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