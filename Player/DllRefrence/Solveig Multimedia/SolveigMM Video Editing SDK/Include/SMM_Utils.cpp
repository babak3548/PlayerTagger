#include <stdafx.h>
#include <shfolder.h>
//#include <winhttp.h> // yoszik: what for this here? move this include to the place where it actually used
#include "FileRoutines.h"
#include "CLogger.h"
#include "SMM_Utils.h"

CString SMM_GetAppLogPath( CString appRegPath, CString stCompanyName )
{
	CString path;

	HKEY hkey;
	bool bFound = false;
	LONG res = RegOpenKey(HKEY_CURRENT_USER, appRegPath, &hkey);

	// если ключ не пуст - использовать его

	if ( res == 0 )
	{
		DWORD dwLen = _MAX_PATH;

		res = RegQueryValueEx(hkey, _T("LogPath"), NULL, NULL, (LPBYTE)path.GetBuffer(_MAX_PATH), &dwLen);
		path.ReleaseBuffer();

		if ( res == ERROR_SUCCESS && dwLen > 2 * sizeof(TCHAR) )
		{
			bFound = true;
		}
	}

	RegCloseKey( hkey );

	if (bFound)
	{
		return path;
	}

	// иначе, по умолчанию - это место в папкe пользователя

	HRESULT hr = SHGetFolderPath( NULL, CSIDL_PERSONAL, NULL, 0, path.GetBuffer(_MAX_PATH) );
	path.ReleaseBuffer();
	
	if (hr == S_OK)
	{
		if( stCompanyName.IsEmpty() )
			path += _T("\\Solveig Multimedia\\Logs");
		else
		{
			path += _T("\\");
			path += stCompanyName;
			path += _T("\\Logs");
		}
	}
	else
	{
		// иначе текущая папка рядом с app.exe

		GetModuleFileName(NULL, path.GetBuffer(_MAX_PATH), _MAX_PATH );
		path.ReleaseBuffer();
	}

	return path;
}

BOOL SMM_CreateAppLog( CString appRegPath, CString stCompanyName, CString sName, CLogger * pLogger, BOOL bTruncate )
{
	BOOL bRet = true;

	if (pLogger == NULL || appRegPath == "")
	{
		return false;
	}

	HKEY hkey;
	LONG res = RegOpenKey(HKEY_CURRENT_USER, appRegPath, &hkey);

	pLogger->m_bLog = FALSE;

	if ( res == 0 )
	{
		DWORD dwRes = 0;
		DWORD dwLen = sizeof(dwRes);
		res = RegQueryValueEx(hkey, _T("Log"), NULL, NULL, (LPBYTE)&dwRes, &dwLen);

		if ( res == ERROR_SUCCESS && dwRes )
		{
			pLogger->m_bLog = TRUE;

			CString path = SMM_GetAppLogPath( appRegPath, stCompanyName );

			CreateFolder( path );

			bRet = SMM_CreateLog(path, sName, pLogger, bTruncate);

			if (!bRet)
			{	
				pLogger->m_bLog = FALSE;
			}
		}
	}

	RegCloseKey( hkey );

	return bRet;
}

BOOL SMM_CreateLog( CString path, CString sName, CLogger * pLogger, BOOL bTruncate )
{
	return pLogger->CreateLog( path+_T("\\")+sName+_T(".log"), bTruncate );
}



