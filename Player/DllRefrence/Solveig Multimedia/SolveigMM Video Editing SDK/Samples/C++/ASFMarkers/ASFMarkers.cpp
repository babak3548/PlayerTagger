////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2012 Solveig Multimedia
// All rights are reserved. 
//
// Solveig Multimedia reserves the right to make changes without
// notice at any time. Solveig Multimedia makes no warranty,
// expressed, implied or statutory, including but not limited to any implied
// warranty of merchantability of fitness for any particular purpose, or that
// the use will not infringe any third party patent, copyright or trademark.
// Solveig Multimedia must not be liable for any loss or damage
// arising from its use.
// 
//////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <afx.h>
#include <objbase.h>
#include <initGuid.h>
#include <atlstr.h>
#include <strmif.h>

#include <Idl\ModuleConfig.h>
#include <Idl\AVITrimmerCOM.h>
#include <Idl\AVITrimmerCOM_i.c>
#include <PropID_EditingEngine.h>


using namespace std;

#define MY_VERSION "1.0.903.19"

DWORD CheckRegistration()
{
	return 0x00001005;
}

int GetFilenameByCLSID(REFCLSID clsid, TCHAR *szFile)
{
	HRESULT hr = S_OK;
	LPOLESTR strCLSID;
	int rc = 0;

	// Convert binary CLSID to a readable version
	hr = StringFromCLSID(clsid, &strCLSID);
	if(SUCCEEDED(hr))
	{
		TCHAR szKey[512];
		CString strQuery(strCLSID);

		// Create key name for reading filename from registry
		wsprintf(szKey, _T("Software\\Classes\\CLSID\\%s\\InprocServer32\0"),
			(LPCTSTR) strQuery);

		// Free memory associated with strCLSID (allocated in StringFromCLSID)
		CoTaskMemFree(strCLSID);

		HKEY hkeyFilter=0;
		DWORD dwSize=MAX_PATH;
		BYTE szFilename[MAX_PATH];

		// Open the CLSID key that contains information about the filter
		rc = RegOpenKey(HKEY_LOCAL_MACHINE, szKey, &hkeyFilter);
		if (rc == ERROR_SUCCESS)
		{
			rc = RegQueryValueEx(hkeyFilter, NULL,  // Read (Default) value
				NULL, NULL, szFilename, &dwSize);

			if (rc == ERROR_SUCCESS)
				wsprintf(szFile, _T("%s\0"), szFilename);

			RegCloseKey(hkeyFilter);
		}
	}
	else
		return -1;

	return rc;
}

bool CheckVersion(REFCLSID clsid, DWORD _ver1, DWORD _ver2, DWORD _ver3, DWORD _ver4, CString szMsg)
{
	TCHAR szFilterDir[MAX_PATH];
	CString sVersion	= "";
	DWORD ver1 			= 0;
	DWORD ver2 			= 0;
	DWORD ver3 			= 0;
	DWORD ver4 			= 0;
	VS_FIXEDFILEINFO *pVS = NULL;

	int nRez = GetFilenameByCLSID(clsid, szFilterDir);
	if(nRez != -1)
	{		
		HINSTANCE hInst = LoadLibrary(szFilterDir);

		if(hInst != NULL)
		{
			TCHAR buf[]={_T("#1")};	// Only one VERSION_INFO present
			HRSRC hr = FindResource(hInst, buf, RT_VERSION); 
			if(hr)
			{		
				HGLOBAL hg = LoadResource(hInst, hr);
				if(hg)
				{
					BYTE *pByte = (BYTE*)LockResource (hg);
					if(pByte)
					{
						pVS = (VS_FIXEDFILEINFO*)(pByte+40);
						if(pVS)
						{
							ver1 = HIWORD (pVS->dwFileVersionMS);
							ver2 = LOWORD (pVS->dwFileVersionMS);
							ver3 = HIWORD (pVS->dwFileVersionLS);
							ver4 = LOWORD (pVS->dwFileVersionLS);
						}
					}
				}
			}
			FreeLibrary(hInst);
		}
	}

	if (pVS == NULL)
		return false;

	if (ver1 < _ver1)
		return false;
	else
	if (ver1 > _ver1)
		return true;

	if (ver2 < _ver2)
		return false;
	else
	if (ver2 > _ver2)
		return true;
	else
	if (ver3 < _ver3)
		return false;
	
	if (ver3 > _ver3)
		return true;
	else
	if (ver4 < _ver4)
		return false;
	

	return true;

}
int usage(_TCHAR * myname)
{
	wprintf(_T("\nSolveigMM ASFMarkers console utility\n"));
	wprintf(_T("Version: %s\n"), _T(MY_VERSION) );
	wprintf(_T("Usage:   %s input -a <action> -v <value>\n"), myname);
	wprintf(_T("Params:\n"));
	wprintf(_T("\t input: \t ASF file name \n"));
	wprintf(_T("\t action: \t add; remove; list \n"));
	wprintf(_T("\t value: \t values followed certain action \n\n"));
    wprintf(_T("\t action add- \t adds marker to specified position with specified name \n"));
	wprintf(_T("\t value:  \t pos; name \n"));
	wprintf(_T("\t value pos- \t 100 nanosec time position a marker should be added to \n"));
	wprintf(_T("\t value name- \t marker text description of 5120 chars maximum \n\n"));
	wprintf(_T("\t action remove - removes a marker with specified name or number\n"));
	wprintf(_T("\t value:  \t num; name \n"));
	wprintf(_T("\t value num- \t zero-based number position of a marker to be removed \n"));
	wprintf(_T("\t value name- \t text description of a marker to be removed  \n\n"));
	wprintf(_T("\t action list- \t list all the markers contained by input ASF \n\n"));

	wprintf(_T("Examples:\n"));
	wprintf(_T("\t %s c:\\IN.asf	-a add -v pos 10000000 name \"the first marker\" \n"), myname);
	wprintf(_T("\t %s c:\\IN.asf	-a remove -v num 6	\n"), myname);
	wprintf(_T("\t %s c:\\IN.asf	-a remove -v name \"the first marker\" \n"), myname);
	wprintf(_T("\t %s c:\\IN.asf	-a list \n"), myname);

	return 1;
}


//struct _Marker_Action_Params_
//{
//	CString name;
//	REFERENCE_TIME time_pos;
//	ULONG position;
//};
enum _Marker_Action_
{
	_Marker_Action_None = 0,
	_Marker_Action_Add = 1,
	_Marker_Action_Remove = 2,
	_Marker_Action_List = 3,

};

struct ASF_Markers_In_Struct
{
	CString inFile;
	
	_Marker_Action_		actions;
	SMM_ASF_MARKER		marker;
//	SMM_ASF_MARKER	add_params;
//	SMM_ASF_MARKER	list_params;
};


int ProcessCommandLine( int argc, _TCHAR* argv[], ASF_Markers_In_Struct &strct)
{
	int i = 0;

	// 1) User didn't use any arguments. Show USAGE
	if (argc == 1)
		return usage(_T("SMM_ASFMarkers.exe"));

	CString szCurArg = argv[1];
	if ( szCurArg == "-a" || szCurArg == "-v"  ){
		wprintf(_T("\n Please specify an input firstly \n"));
		return 1;
	}


	// ASF file name - szCurArg
    strct.inFile = szCurArg;

	// 5) Try get set file list
//	iSetFilesCount = 0;
	
	// by deaful just list the markers 
	strct.actions  = _Marker_Action_List;
	for (i = 1; i < argc; i++)
	{
		CString szCurArg = argv[i];
		if ( szCurArg == "-a" )
		{
			CString act = argv[ i + 1 ];
			if( act == "add" )
				strct.actions  = _Marker_Action_Add;
			else
			if( act == "remove" )
				strct.actions  = _Marker_Action_Remove;
			else
			if( act == "list" )
				strct.actions  = _Marker_Action_List;
			
		}
	}
	
	for ( i = 2; i < argc; i++)
	{
		CString szCurArg = argv[i];

		if( strct.actions  == _Marker_Action_Add )
		{
			if( szCurArg == "pos" )
				strct.marker.time_pos = _ttoi64( argv[i + 1] ); 

			if( szCurArg == "name" )
				wcscpy(strct.marker.name, argv[i + 1]); 
		}
		else
		if( strct.actions  == _Marker_Action_Remove )
		{
			if( szCurArg == "num" )
				strct.marker.num_pos = _ttoi( argv[i + 1] ); 

			if( szCurArg == "name" )
				wcscpy(strct.marker.name, argv[i + 1]);
		}
	}

//	if (iSetFilesCount == 0)
//		return usage(_T("SMM_ASFMarkers.exe"));

	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	ASF_Markers_In_Struct strct;
	strct.actions = _Marker_Action_None;
	memset(&strct.marker,0,sizeof(strct.marker));

	if (ProcessCommandLine(argc, argv, strct) == 1)
		return 1;

	bool b = CheckVersion(CLSID_TrimmerObjControl, 1, 4, 903,14, "0");
	if( false == b ){
		wprintf(_T("Error: SolveigMM Video Editing object ver 1.4.903.14 or above is required"));
		return 1;
	}

	DWORD dwState = CheckRegistration();
	if( dwState == 0x00001004 ){
//		wprintf(_T("Error: Evaluation period expired, please buy SolveigMM Video Splitter"));
//		return 0;
	}

	HRESULT hr = S_OK;
	CComPtr<IModuleConfig>		pIModuleConfig		= NULL;
	CComPtr<ITrimmerObjControl>	pITrimmerObjControl = NULL;

	CoInitialize(NULL);

	//
	// SolveigMM Video Editing Engine
	//
	hr = ::CoCreateInstance(CLSID_TrimmerObjControl,NULL, CLSCTX_INPROC, IID_ITrimmerObjControl, (void**)&pITrimmerObjControl);
	if ( hr != S_OK ) 
	{
		wprintf(_T("Error: \t SolveigMM Video Editing Engine creating has been failed"));
		return 0;
	}

	//
	// Getting SolveigMM Video Editing Engine control interface - IModuleConfig
	//
	hr = pITrimmerObjControl->QueryInterface(IID_IModuleConfig, (void **)&pIModuleConfig);
	if ( hr != S_OK )
	{
		wprintf(_T("Error: \t Retrieving IModuleConfig has been failed"));
		return 0; 
	}

	CComVariant var;
	var = (BSTR)strct.inFile.AllocSysString();

	//- to add a marker at any point of the video, specifying a name
	//- to delete a marker, specifyng its name
	//- to rename  a marker specifying the old name and the new name (optional fuction, non really necessary)
	//- to list all of the markers included in a video (obtaining a list in the form: marker name, marker position position)

	hr = pIModuleConfig->SetValue(&SMAT_InputFile, &var );
	SysFreeString( var.bstrVal); 

	if(FAILED(hr)){
		wprintf(_T("Error: \t Can't set input file"));
		return 0; 
	}
	


	hr = pIModuleConfig->GetValue(&SMAT_ASFMarkersCount, &var );
	if(FAILED(hr)){
		wprintf(_T("Error: \t Retrieving ASF Markers number has been failed"));
		return 0; 
	}
	
	wprintf( _T("Number of markers detected in input file:  %d\n"), var.lVal);

	if( strct.actions ==  _Marker_Action_List )
	{
		//- to list all of the markers included in a video (obtaining a list in the form: marker name, marker position position)
		wprintf(_T("--Markers List-- \n "));
		int count = var.lVal;
		for(int i = 0; i < count; i++ )
		{
			SMM_ASF_MARKER marker = {0};
			marker.num_pos = i;

			var.pbVal = (BYTE*)&marker;
			var.vt	  = VT_BYREF;

			hr = pIModuleConfig->GetValue(&SMAT_ASFMarker, &var );

			// output
			wprintf( _T("Position : \t %d \t Time position: \t %I64d \t Name: \t %s \n "), marker.num_pos, marker.time_pos, marker.name );
		}
	}
	else
	if( strct.actions ==  _Marker_Action_Remove )
	{
		
		USES_CONVERSION;
		if( wcslen(strct.marker.name) )
		{
			var.vt		= VT_BSTR;
			var.bstrVal = W2BSTR(strct.marker.name);
		}
		else{
			var.vt = VT_I4;
			var.lVal = strct.marker.num_pos;
		}
		
		hr = pIModuleConfig->SetValue(&SMAT_ASFMarkerRemove, &var );
		if(SUCCEEDED(hr))
			wprintf( _T("Removed: Marker with name - %s and position  %d  was sucessfully removed\n"), strct.marker.name,strct.marker.num_pos );
	}
	else
		if( strct.actions ==  _Marker_Action_Add)
		{

			SMM_ASF_MARKER marker = {0};

			USES_CONVERSION;
			
			wcscpy( marker.name,strct.marker.name );
			marker.time_pos = strct.marker.time_pos;
			
			var.pbVal = (BYTE*) &marker;
			var.vt	  = VT_BYREF;

			hr = pIModuleConfig->SetValue(&SMAT_ASFMarker, &var );
			if(SUCCEEDED(hr))
				wprintf( _T("Added: Marker with name - %s and postion  %I64d  was sucessfully added \n"), marker.name, marker.time_pos );

		}

	////- to add a marker at any point of the video, specifying a name

	//hr = pIModuleConfig->SetValue(&SMAT_ASFMarker, &var );

	//
	//hr = pIModuleConfig->SetValue(&SMAT_ASFMarkerRemove, &var );
	
	
	
	return 0;
}
