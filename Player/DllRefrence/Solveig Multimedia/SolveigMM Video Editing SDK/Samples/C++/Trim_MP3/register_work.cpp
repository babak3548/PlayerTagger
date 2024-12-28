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

#include "stdafx.h"
#include "register_work.h"
#include "Tlhelp32.h"

CRegWork::CRegWork()
{
	HRESULT hr = RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Solveig Multimedia\\SolveigMM Video&Audio Trimmer"), &m_RootKey);
	if (hr != ERROR_SUCCESS){
		hr = RegCreateKey(HKEY_CURRENT_USER, _T("Software\\Solveig Multimedia"), &m_RootKey);
		hr = RegCreateKey(m_RootKey, _T("Trimmer"), &m_RootKey);
	}

	m_szLookAtSamplesTimes = _T("LookAtSamplesTimes");
	m_szResult_path 	   = _T("result_path");
	m_szComputerID  	   = _T("ComputerID");
	m_szVolume			   = _T("Volume");
	m_szNextID			   = _T("NextID");
	m_szDate			   = _T("Date");
	m_szStep			   = _T("Step");
	m_szExtended		   = _T("ExtendedMode");
}

CRegWork::~CRegWork()
{
	RegCloseKey(m_RootKey);
}

BOOL CRegWork::IsExtended()
{
	DWORD dwExt = 0;
	DWORD size  = 0;
	HRESULT hr  = S_OK;

	size = sizeof(dwExt);
	hr   = RegQueryValueEx(m_RootKey, m_szExtended, NULL, NULL, (LPBYTE)&dwExt, &size);

	if (dwExt == 0)
		return FALSE;

	return TRUE;	
}

HRESULT CRegWork::SetExtended(BOOL bExt)
{
	HRESULT hr   = S_OK;

	DWORD dwTemp = (bExt == TRUE)?1:0;
	hr = RegSetValueEx(m_RootKey, m_szExtended, NULL, REG_DWORD, (LPBYTE)&dwTemp, 4);

	return hr;
}

HRESULT CRegWork::CheckKeys(bool * bChanged)
{
	DWORD dwTemp = 0;
	char * szTemp[1000 + 10];
	DWORD size   = 0;
	HRESULT hr   = S_OK;
	if (bChanged != NULL)
		*bChanged = false;

	// check key Step
	size = sizeof(dwTemp);
	hr   = RegQueryValueEx(m_RootKey, m_szStep, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		hr = SetStep(100);
		if (hr != S_OK)
			return hr;

/*		if (bChanged != NULL)
			*bChanged = true;*/
	}

	// check key Date
	size = sizeof(dwTemp);
	hr   = RegQueryValueEx(m_RootKey, m_szDate, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		dwTemp = GetDateHash();
		hr = RegSetValueEx(m_RootKey, m_szDate,   NULL, REG_DWORD, (LPBYTE)&dwTemp, 4);
		if (hr != S_OK)
			return hr;

/*		if (bChanged != NULL)
			*bChanged = true;*/
	}

	// check key NextID
	size = sizeof(dwTemp);
	hr   = RegQueryValueEx(m_RootKey, m_szNextID, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		hr = SetNextNumber();
		if (hr != S_OK)
			return hr;

/*		if (bChanged != NULL)
			*bChanged = true;*/
	}

	// check key Volume
	size = sizeof(dwTemp);
	hr   = RegQueryValueEx(m_RootKey, m_szVolume, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		hr = SetVolume(100);
		if (hr != S_OK)
			return hr;

/*		if (bChanged != NULL)
			*bChanged = true;*/
	}

	// check key ComputerID
	size = sizeof(dwTemp);
	hr   = RegQueryValueEx(m_RootKey, m_szComputerID, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		hr = SetComputerID(0);
		if (hr != S_OK)
			return hr;

		if (bChanged != NULL)
			*bChanged = true;
	}

	// check key result_path
	size = sizeof(szTemp) - 10;
	hr   = RegQueryValueEx(m_RootKey, m_szResult_path, NULL, NULL, (LPBYTE)&szTemp, &size);
	if (hr != S_OK){
		hr = SetOutPath(_T("."));
		if (hr != S_OK)
			return hr;

		if (bChanged != NULL)
			*bChanged = true;
	}

	hr   = RegQueryValueEx(m_RootKey, m_szExtended, NULL, NULL, (LPBYTE)&dwTemp, &size);
	if (hr != S_OK){
		SetExtended(FALSE);
	}
	
	return S_OK;
}

DWORD	CRegWork::GetVolume()
{
	DWORD dwVolume = 0;
	DWORD size     = 0;
	HRESULT hr     = S_OK;

	size = sizeof(dwVolume);
	hr   = RegQueryValueEx(m_RootKey, m_szVolume, NULL, NULL, (LPBYTE)&dwVolume, &size);

	return dwVolume;	
}

HRESULT CRegWork::SetVolume(DWORD dwVolume)
{
	HRESULT hr   = S_OK;

	hr = RegSetValueEx(m_RootKey, m_szVolume,   NULL, REG_DWORD, (LPBYTE)&dwVolume, 4);

	return hr;
}

DWORD CRegWork::GetStep()
{
	DWORD dwStep = 0;
	DWORD size   = 0;
	HRESULT hr   = S_OK;

	size = sizeof(dwStep);
	hr   = RegQueryValueEx(m_RootKey, m_szStep, NULL, NULL, (LPBYTE)&dwStep, &size);

	return dwStep;
}

HRESULT CRegWork::SetStep(DWORD dwStep)
{
	HRESULT hr   = S_OK;

	hr = RegSetValueEx(m_RootKey, m_szStep,   NULL, REG_DWORD, (LPBYTE)&dwStep, 4);

	return hr;
}

DWORD CRegWork::GetNextNumber()
{
	DWORD nextID  = 0;
	DWORD date    = 0;
	DWORD size    = 0;
	HRESULT hr    = S_OK;

	size = sizeof(nextID);
	hr   = RegQueryValueEx(m_RootKey, m_szNextID, NULL, NULL, (LPBYTE)&nextID, &size);

	size = sizeof(date);
	hr   = RegQueryValueEx(m_RootKey, m_szDate, NULL, NULL, (LPBYTE)&date, &size);

	if (GetDateHash() != date){
		nextID = 0;
	}

	return nextID;
}

DWORD	CRegWork::GetDateHash()
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	return time.wYear * 256 * 256 + time.wDay * 256 + time.wMonth; // calculate hash of current date
}

HRESULT CRegWork::SetNextNumber()
{
	HRESULT hr  = S_OK;
	
	DWORD curID = GetNextNumber();
	curID++;

	hr = RegSetValueEx(m_RootKey, m_szNextID, NULL, REG_DWORD, (LPBYTE)&curID, 4);
	if (hr != S_OK)
		return hr;

	curID = GetDateHash();
	hr = RegSetValueEx(m_RootKey, m_szDate,   NULL, REG_DWORD, (LPBYTE)&curID, 4);

	return hr;
}

DWORD CRegWork::GetComputerID()
{
	DWORD CompID = 0;
	DWORD size   = sizeof(CompID);

	HRESULT hr   = RegQueryValueEx(m_RootKey, m_szComputerID, NULL, NULL, (LPBYTE)&CompID, &size);

	return CompID;
}

HRESULT CRegWork::SetComputerID(DWORD dwCompId)
{
	HRESULT hr = RegSetValueEx(m_RootKey, m_szComputerID,   NULL, REG_DWORD, (LPBYTE)&dwCompId, 4);

	return hr;
}

CString CRegWork::GetOutPath()
{
	DWORD size = 1000;
	TCHAR  * path = new TCHAR[size+10];

	ZeroMemory(path, size);

	HRESULT hr   = RegQueryValueEx(m_RootKey, m_szResult_path, NULL, NULL, (LPBYTE)path, &size);
	
	CString szPath = path;
	delete [] path;

	return szPath;
}

HRESULT CRegWork::SetOutPath(TCHAR * szPath)
{
	HRESULT hr = RegSetValueEx(m_RootKey, m_szResult_path, NULL, REG_SZ, (LPBYTE)szPath, _tcslen(szPath)*sizeof(TCHAR));

	return hr;
}

BOOL CRegWork::IsLookAtSamplesTimes()
{
	DWORD dwLook = 0;
	DWORD size   = 0;
	HRESULT hr   = S_OK;

	size = sizeof(dwLook);
	hr   = RegQueryValueEx(m_RootKey, m_szLookAtSamplesTimes, NULL, NULL, (LPBYTE)&dwLook, &size);

	if (dwLook == 0)
		return FALSE;

	return TRUE;	
}

HRESULT CRegWork::SetLookAtSamplesTimes(BOOL bLook)
{
	HRESULT hr   = S_OK;

	DWORD dwTemp = (bLook == TRUE)?1:0;
	hr = RegSetValueEx(m_RootKey, m_szLookAtSamplesTimes, NULL, REG_DWORD, (LPBYTE)&dwTemp, 4);

	return hr;
}

CString CRegWork::GetExecuteble()
{
	TCHAR cTemp[1000] = {0};
	DWORD dwSize = sizeof(cTemp);

	::GetModuleFileName(NULL, cTemp, dwSize);

	return cTemp;
}
