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

// BatchSplit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <afx.h>
#include <objbase.h>
#include <initGuid.h>
#include <atlstr.h>

#include <streams.h>
#include <Idl\ModuleConfig.h>
#include <Idl\AVITrimmerCOM.h>
#include <Idl\AVITrimmerCOM_i.c>
#include <guid_hdr.h>

#include <SMM_Utils.h>
#include <shellapi.h>

using namespace std;

#define MY_VERSION "2.0.1202.17"
#define DEFAULT_LOG_FILE_NAME _T("BatchSplit.log")
#define DEFAULT__CODEC_PROFILE Default_Codecs_Profile
#define ACTIVATION_KEY g_ActionKey_Trim_Join

#define MAX_SET_FILES			50

int iSetFilesCount = 0;
CString szSetFiles[MAX_SET_FILES] = {""};

CString szLogFileName = "";
CString szProfile =		DEFAULT__CODEC_PROFILE;

BOOL bTerminate = FALSE;

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

	if (ver1 < _ver1){
		return false;
	}
	if (ver1 > _ver1)
		return true;

	if (ver2 < _ver2){
		return false;
	}
	if (ver2 > _ver2)
		return true;

	if (ver3 < _ver3){
		return false;
	}
	if (ver3 > _ver3)
		return true;

	if (ver4 < _ver4){
		return false;
	}

	return true;

}
int usage(_TCHAR * myname)
{
	wprintf(_T("SolveigMM Batch Splitter console utility.\n"));
	wprintf(_T("Version: %s\n"), _T(MY_VERSION) );
	wprintf(_T("Usage:   %s [-L logfilename] file.xtl \n\n"), myname);
	wprintf(_T("Parameters:\n"));
	wprintf(_T("\t-L logfilename: Log file name. By default it equals %s\n"), DEFAULT_LOG_FILE_NAME);
	wprintf(_T("\t\t\tUse value NULL to disable logging \n"));
	wprintf(_T("\t file.xtl:	Batch file name with a full file path \n\n"), MAX_SET_FILES);
	wprintf(_T("\t-P profile:	codecs profile. by default  %s is used \n"), DEFAULT__CODEC_PROFILE);

	return 1;
}

class CTrimCtrl: public ITrimmerObjControlCB, public CFile
{
public: 

	CTrimCtrl(HRESULT *phr, CString InBatchFile, CString LogFn, CString szProfile ):
	  m_csProfile(szProfile),
		  m_cRef(0),
		  m_bStopped(FALSE),
		  m_pIModuleConfig(NULL),
		  m_pITrimmerObjControl ( NULL)
	  {
		  Init(phr, InBatchFile, LogFn);
	  }

	  CTrimCtrl(HRESULT *phr, CString InBatchFile, CString LogFn ):
	  m_cRef(0),
		  m_bStopped(FALSE),
		  m_pIModuleConfig(NULL),
		  m_pITrimmerObjControl ( NULL)
	  {
		  Init(phr, InBatchFile, LogFn);
	  }

	  void Init( HRESULT *phr, CString InBatchFile, CString LogFn )
	  {
	  	AddRef();

		  if(phr == NULL){
			  return;
		  }

		  GetAbsPath( InBatchFile );
		  //
		  // creating log file
		  //
		  CFileException ex;
		  BOOL bval = Open( LogFn, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &ex );
		  if( FALSE == bval ){
			  *phr = HRESULT_FROM_WIN32(ex.m_lOsError);
			  return;
		  }
		  SeekToBegin();

		  USES_CONVERSION;
		  CString str; 

		  CoInitialize(NULL);

		  //
		  // SolveigMM Video Editing Engine
		  //
		  *phr = ::CoCreateInstance(CLSID_TrimmerObjControl,NULL, CLSCTX_INPROC, IID_ITrimmerObjControl, (void**)&m_pITrimmerObjControl);
		  if (*phr != S_OK){
			  str = "Error: \t SolveigMM Video Editing Engine creating has been failed";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }
		  //
		  // Getting SolveigMM Video Editing Engine control interface - IModuleConfig
		  //
		  *phr = m_pITrimmerObjControl->QueryInterface(IID_IModuleConfig, (void **)&m_pIModuleConfig);
		  if (*phr != S_OK){
			  str = "Error: \t Retrieving IModuleConfig has been failed";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return; 
		  }

		  //
		  //Setting the MPEG2 codecs configuration
		  //
		  CString silenPt = GetRegistrySilentPath(CLSID_App);
		  CComVariant var;
		  if ( 0 != silenPt.GetLength() )
		  {
			  var.bstrVal = silenPt.AllocSysString();
			  *phr= m_pIModuleConfig->SetValue(&SMAT_SilentPath, &var);
		  }
		  var.bstrVal  = m_csProfile.AllocSysString();
		  *phr= m_pIModuleConfig->SetValue(&SMAT_CodecsSet, &var);
		  SysFreeString( var.bstrVal );
		  
		  //
		  //Setting the Activation Key
		  //
		  var =  SysAllocString(ACTIVATION_KEY);
		  *phr  = m_pIModuleConfig->SetValue(&SMAT_ActionKey, &var);
		  SysFreeString(var.bstrVal);

		  //
		  // Setting batch file
		  //
		  { // writing to log InBatchFile Name
			  CString str = _T("InBatchFile: ");
			  str+=InBatchFile;
			  str+=_T("\n");
			  Write( T2A(str.GetBuffer()), str.GetLength() );
		  }
		  var =  (BSTR)InBatchFile.AllocSysString();
		  *phr  = m_pIModuleConfig->SetValue(&SMAT_BatchFileName, &var);
		  if (FAILED(*phr))
		  {
			  str = "Error: \t Batch file name setting has been failed";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }

		  *phr  = m_pIModuleConfig->CommitChanges(NULL);
		  if (FAILED(*phr))
		  {
			  str = "Error: \t Input parameters can't be set";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
		  }


		  //
		  // Setting callback interface - ITrimmerObjControlCB
		  //
		  var = (BYTE*)(ITrimmerObjControlCB*) this;
		  *phr  = m_pIModuleConfig->SetValue(&SMAT_Callback, &var);
		  if (FAILED(*phr))
		  {
			  str = "Error: \t Setting callback interface has been failed";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }

		  *phr  = S_OK;
	  }

	  virtual void Write(const void* lpBuf, UINT nCount)
	  {
		  CFile::Write(lpBuf, nCount);
		  printf("%s\n",(char*)lpBuf);
	  }
	  void SetCodecsProfile(CString prfl)
	  {
		  m_csProfile = prfl;
	  }

	  void ResetObject()
	  {
		  if(m_pIModuleConfig){
			  m_pIModuleConfig.Release();
		  }
		  if(m_pITrimmerObjControl)
		  {
			  //
			  // upon ITrimmerObjControl releasing 
			  // ITrimmerObjControlCB::Release is called
			  // Release, in its turn, has to call ~CTrimCtrl() destructor
			  //
			  m_pITrimmerObjControl.Release();
		  }
	  }

	  virtual ~CTrimCtrl()
	  {
		  CFile::Close();
		  CoUninitialize();
	  }

	  STDMETHODIMP OnStart()
	  {
		  m_bStopped = FALSE;

		  //
		  // just logging
		  //
		  CComVariant var;
		  HRESULT hr	= S_OK;
		  CString str = CString("\n---------\n") +
			  CString("Started\n")  +
			  CString("---------\n")   ;

		  hr = m_pIModuleConfig->GetValue( &SMAT_CurrentBatchTask, &var );
		  str.AppendFormat( TEXT("Task#:\t\t %d\n"), var.ulVal );

		  hr = m_pIModuleConfig->GetValue( &SMAT_InputFile, &var );
		  CString fn(var.bstrVal);
		  str.AppendFormat( _T("InFile:\t\t %s\n"), fn );

		  hr = m_pIModuleConfig->GetValue( &SMAT_OutputFile, &var );
		  fn = var.bstrVal;
		  str.AppendFormat( _T("OutFile:\t %s"), fn );

		  USES_CONVERSION;
		  Write( T2A(str.GetBuffer()), str.GetLength() );
		  return S_OK;
	  }

	  STDMETHODIMP OnStop()
	  {
		  BOOL bLast = IsLastTaskOperated();


		  //
		  // just logging
		  //
		  CString str =	CString("\n---------\n") +
			  CString("Stopped\n")  +
			  CString("---------\n");

		  USES_CONVERSION;
		  Write( T2A(str.GetBuffer()), str.GetLength() );

		  if( bLast == TRUE ){
			  m_bStopped = TRUE; //it should terminate the process
		  }
		  return S_OK;
	  }

	  STDMETHODIMP OnPause()
	  {
		  return S_OK;
	  }

	  STDMETHODIMP  OnError(HRESULT hr, BSTR Val)
	  {


		  //
		  // just logging
		  //
		  CString str = CString("\n-----\n") + CString("Error\n") + CString("-----\n") + CString(Val) + "\n";

		  CComVariant var;
		  hr = m_pIModuleConfig->GetValue( &SMAT_CurrentBatchTask, &var );
		  str.AppendFormat( _T("Task#:\t\t %d\n"), var.ulVal );

		  hr = m_pIModuleConfig->GetValue( &SMAT_InputFile, &var );
		  CString fn(var.bstrVal);
		  str.AppendFormat( _T("InFile:\t\t %s\n"), fn );

		  hr = m_pIModuleConfig->GetValue( &SMAT_OutputFile, &var );
		  fn = var.bstrVal;
		  str.AppendFormat( _T( "OutFile:\t %s\n" ), fn );


		  USES_CONVERSION;
		  Write( T2A(str.GetBuffer()), str.GetLength() );
		  BOOL bLast = IsLastTaskOperated();

		  if( bLast == TRUE ){
			  m_bStopped = TRUE; //it should terminate the process
		  }

		  return S_OK;

	  }
	  HRESULT getTasksCount(ULONG& ulTasksNum)
	  {
		  if( !m_pIModuleConfig )
			  return E_NOINTERFACE;
		  CComVariant var;
		  HRESULT hr	= m_pIModuleConfig->GetValue(&SMAT_BatchTasksNum,&var);
		  if (SUCCEEDED(hr)) 
			  ulTasksNum = var.ulVal;
		  return hr;
	  }
	  ULONG getCurrentTaskNum() // zero based
	  {
		  if( !m_pIModuleConfig )
			  return 0;
		  CComVariant var;
		  HRESULT hr	= m_pIModuleConfig->GetValue(&SMAT_CurrentBatchTask,&var);
		  ULONG ulTasksNum = var.lVal;

		  if (SUCCEEDED(hr)) 
			  return ulTasksNum;
		  return 0;
	  }
	  BOOL IsLastTaskOperated( void )
	  {
		  if( !m_pIModuleConfig )
			  return TRUE;
		  BOOL ret_var = FALSE;

		  CComVariant var;

		  HRESULT hr	= m_pIModuleConfig->GetValue(&SMAT_BatchTasksNum,&var);
		  ULONG ulTasksNum = var.ulVal;

		  if (FAILED(hr)) 
		  {
			  USES_CONVERSION;
			  CString str = "Error: \t Getting a count of tasks has been failed";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return TRUE;
		  }


		  // first task is zero based
		  hr  = m_pIModuleConfig->GetValue(&SMAT_CurrentBatchTask, &var );

		  if( var.lVal + 1 >= (LONG)ulTasksNum ){
			  ret_var = TRUE;
		  }

		  return ret_var;
	  }

	  STDMETHODIMP QueryInterface( REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject )
	  {
		  if( riid == IID_ITrimmerObjControlCB ){
			  AddRef();
			  *ppvObject = (ITrimmerObjControlCB*)this;
			  return S_OK;
		  }

		  return E_FAIL;
	  }

	  STDMETHODIMP_(ULONG) AddRef( void )
	  {
		  m_cRef++;
		  return m_cRef;
	  }

	  STDMETHODIMP_(ULONG) Release( void )
	  {
		  m_cRef--;
		  _ASSERT( m_cRef >= 0 );
		  if(m_cRef ==0 )
		  {
			m_cRef++;

			delete this;
			return ULONG(0);
		  }
		  return m_cRef;
	  }

	  void ProcessBatch (void )
	  {
		  if (bTerminate) return;

		  USES_CONVERSION;
		  CString str;
		  ULONG taskscount = 0;
		  HRESULT hr = getTasksCount(taskscount);
		  if (FAILED(hr))
		  {
			  str = "Error: \t Unable to load specified xtl file. Check Syntax. Exiting...";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }
		  if (taskscount == 0)
		  {
			  str = "Error: \t No tasks specified. Exiting...";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }

		  hr  = m_pITrimmerObjControl->Start();

		  if (FAILED(hr)){
			  str = "Error: \t Trimming process can't be started";
			  Write( T2A(str.GetBuffer()), str.GetLength() );
			  return;
		  }
		  // wait for OnComplete of a last task to be called
		  WaitForGraphComplete();
	  }

	  void WaitForGraphComplete()
	  {
		  CComVariant var;
		  LONG prevTask = -1;
		  int prevProgress = 0;
		  do{

			  ULONG  curTask = getCurrentTaskNum();
			  if (prevTask != curTask)
			  {
				  printf("%s%d","\ntask ",curTask);
				  prevTask = curTask;
			  }

			  Sleep( 1000 );
			  HRESULT hr = m_pIModuleConfig->GetValue(&SMAT_Progress , &(var = SMM_ProgressType_TimeBased));
			  if (SUCCEEDED(hr))
			  {
				  int curProgress = (var.lVal);
				  if (curProgress != prevProgress)
				  {
					  printf("%s",".");
					  prevProgress = curProgress;
				  }
			  }
		  }
		  while( FALSE == m_bStopped && !bTerminate );
		  int  t = 0;
	  }
		void GetAbsPath( CString& sName )
		{
			if( -1 != sName.Find(_T(':')) )
				return;
			//if relative path - restore the full path
			DWORD dwLen = _MAX_PATH;
			TCHAR dwBuf[_MAX_PATH+1];
			GetCurrentDirectory( dwLen, dwBuf );
			CString csCurDir(dwBuf);
			if( csCurDir.IsEmpty() ) //nothing to do in this case
				return;

			TCHAR csFullPath[_MAX_PATH]={0};
			if( !PathCombine(csFullPath, csCurDir, sName) )
				return;
		
			sName = csFullPath;
		}
private:
	int		m_cRef; 
	BOOL	m_bStopped;
	CString	m_csProfile;
	CComPtr<IModuleConfig>		m_pIModuleConfig;
	CComPtr<ITrimmerObjControl>	m_pITrimmerObjControl ;

};

int ProcessCommandLine( int argc, _TCHAR* argv[], CString * pLogFileName, CString * codecs_profile)
{
	int i = 0;

	// 1) User didn't use any arguments. Show USAGE
	if (argc == 1)
		return usage(_T("BatchSplit.exe"));

	// 2) User set's flag <-h>: Show USAGE
	for ( i = 1; i < argc; i++)
	{
		CString szCurArg = argv[i];
		if (szCurArg == "-h")
			return usage(_T("BatchSplit.exe"));
	}

	// 3) User set's unknown flag: Show USAGE 
	for (i = 1; i < argc; i++)
	{
		CString szCurArg = argv[i];
		if ( ( szCurArg[0] == '-' ) && 
			( szCurArg[1] != 'h')  && 
			( szCurArg[1] != 'L')  &&
			( szCurArg[1] != 'P') )
		{
			return usage(_T("BatchSplit.exe"));
		}
	}

	// 4) Try get log file name
	*pLogFileName = DEFAULT_LOG_FILE_NAME;
	for (i =1; i < argc - 1; i++)
	{
		CString szCurArg = argv[i];
		if (szCurArg == "-L")
			*pLogFileName = argv[i+1];
	}

	for (i =1; i < argc - 1; i++)
	{
		CString szCurArg = argv[i];
		if (szCurArg == "-P")
			*codecs_profile = argv[i+1];
	}

	if (*pLogFileName == "NULL")
		*pLogFileName = ""; // No log.

	// 5) Try get set file list
	iSetFilesCount = 0;
	for (i = 1; i < argc; i++)
	{
		CString szCurArg = argv[i];
		if (szCurArg[0] == '-')
		{
			if (i == argc)
				break;

			szCurArg = argv[i+1];

			if (szCurArg[0] != '-')
				i++; // this is argument for <-X> parameter: skip it
			continue;
		}

		szSetFiles[iSetFilesCount] = szCurArg;
		iSetFilesCount++;

		if (iSetFilesCount == MAX_SET_FILES)
			break;
	}

	if (iSetFilesCount == 0)
		return usage(_T("BatchSplit.exe"));

	return 0;
}

void WriteLogFile(CString szMessage)
{
	if (szLogFileName.IsEmpty())
		return;

	FILE * f = _wfopen(szLogFileName.AllocSysString(), _T(""));
	fwprintf(f, szMessage.AllocSysString());
	fclose(f);
}

BOOL CtrlHandler( DWORD fdwCtrlType ) 
{ 
	switch( fdwCtrlType ) 
	{ 
	case CTRL_CLOSE_EVENT: case CTRL_LOGOFF_EVENT: case CTRL_SHUTDOWN_EVENT: case CTRL_C_EVENT:
		bTerminate = TRUE;
		return FALSE; 

	default: 
		return FALSE; 
	} 
} 
void RunAsAdmin( int argc, _TCHAR* argv[] )
{
	CString csFile = argv[0];
	TCHAR csDir[_MAX_PATH+1];
	DWORD dwLen = _MAX_PATH;
	GetCurrentDirectory(dwLen, csDir);
	//Restore the parameters string
	CString params;

	for(int i = 1; i < argc; i++)
	{
		CString str;
		str.Format(_T("\"%s\" "),argv[i] );
		params+=str;
	}

	HINSTANCE nResult = ShellExecute( NULL, _T("runas"), // Trick for requesting elevation, this is a verb not listed in the documentation above.
    csFile,
    params,    // params
    csDir,        // directory
	SW_NORMAL);
}
int _tmain(int argc, _TCHAR* argv[])
{

	if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE ) )
		return 1;

	if (ProcessCommandLine(argc, argv, &szLogFileName, &szProfile) == 1)
	{
		return 0/*1*/;
	}

	wprintf(_T("Log file:   %s\n"), szLogFileName);
	//wprintf(_T("Batch File: %s\n\n"), szSetFiles[0]);

	bool b = CheckVersion(CLSID_TrimmerObjControl, 1, 3, 11, 7, "0");
	if( false == b ){
		wprintf(_T("Error: SolveigMM Video Editing object ver 1.3.11.7 or above is required"));
		return 1;
	}

	DWORD dwState = CheckRegistration();
	if( dwState != 0 && dwState != 1){
		wprintf(_T("Error: Evaluation period has expired"));
		//		return 0;
	}

	HRESULT hr = S_OK;
	CTrimCtrl *pTrimObj = new CTrimCtrl(&hr, szSetFiles[0], szLogFileName, szProfile ) ;
	if( hr != S_OK )
	{
		pTrimObj->ResetObject();
		pTrimObj->Release();
		//in case of windows Vista or higher
		if( hr == E_ACCESSDENIED )
			RunAsAdmin(argc, argv);
		return 0;
	}
	pTrimObj->SetCodecsProfile(szProfile);

	pTrimObj->ProcessBatch();
	//
	// we don't delete this object since it has to be self-deleted within Release routine
	//
	pTrimObj->ResetObject();
	pTrimObj->Release();
	pTrimObj = NULL;

	return 0;
}
