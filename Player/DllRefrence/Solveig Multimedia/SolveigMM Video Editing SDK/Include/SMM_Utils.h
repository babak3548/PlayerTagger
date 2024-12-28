#ifndef __UTILS_H__
#define __UTILS_H__

#include <initguid.h>
#include <list>
#include <cstringt.h>
#include <PropID_EditingEngine.h>


using namespace std;

typedef list<__TSTrimInfo> TLTrimInfo;
typedef list<__TSTrimInfo>::iterator TLITrimInfo;

#define TSTrimInfo __TSTrimInfo

class CLogger;

#define SELF_DELETE(pValue)		\
{								\
	if(pValue) {				\
	delete pValue;				\
	pValue = NULL;				\
	}							\
}								

#define SELF_DELETE_ARR(pValue)	\
{								\
	if(pValue) {				\
	delete []pValue;			\
	pValue = NULL;				\
	}							\
}		

static CString GetRegistrySilentPath( GUID app_guid);
//CString SMM_GetAppLogPath( CString appRegPath, CString stCompanyName = _T("") );
//BOOL SMM_CreateAppLog( CString appRegPath, CString stCompanyName, CString sName, CLogger * pLogger, BOOL bTruncate = TRUE );
//BOOL SMM_CreateLog( CString path, CString sName, CLogger * pLogger, BOOL bTruncate = TRUE );

// return a number of a current pin (pPin) in filter(pFilter) list 
static UINT GetPinNumber(CBasePin *pPin,CBaseFilter* pFilter)
{

	if( pPin == NULL || pFilter == NULL ){
		return 0;
	}

	for(UINT n = 0; n < 40; n++ ) {
		if( pPin == pFilter->GetPin(n) ){
			return n;
		}
	}

	return 0;
}

static REFERENCE_TIME GetListDuration(TrimInfoList &inf)
{
	REFERENCE_TIME rt = 0;

	if(0 == inf.nListSize){
		return 0;
	}
	
	for( UINT n = 0; n < inf.nListSize; n++) {
			rt += (inf.trim_list[n].llStopPos - inf.trim_list[n].llStartPos);
	}
	return rt;

}

static void ConvertTime2String(__TSTrimInfo tt, LPSTR str)
{
	if(str == NULL){
		return;
	}

	char ch[100];
	char cstart[40];
	memset(ch, 0, sizeof(ch));
	memset(cstart, 0, sizeof(cstart));

	DWORD dwMsec	 = DWORD(tt.llStartPos / 10000);
	DWORD dwSec		 = dwMsec / 1000;
	DWORD dwHours	 = dwSec / 3600;;
	DWORD dwMinutes  = (dwSec % 3600) / 60;
	DWORD dwSeconds  = (dwSec % 3600) - dwMinutes * 60;
	DWORD dwMSeconds = dwMsec % 1000;

	sprintf(ch,"%.2u:%.2u:%.2u:%.3u",dwHours,dwMinutes,dwSeconds, dwMSeconds );
	strcpy(cstart, ch);

	dwMsec		= (DWORD) (tt.llStopPos / 10000);
	dwSec		= dwMsec / 1000;
	dwHours		= dwSec / 3600;;
	dwMinutes	= (dwSec % 3600) / 60;
	dwSeconds	= (dwSec % 3600) - dwMinutes * 60;
	dwMSeconds	= dwMsec % 1000;

	sprintf(ch," - %.2u:%.2u:%.2u:%.3u",dwHours,dwMinutes,dwSeconds, dwMSeconds );
	strcat(cstart, ch);
	strcpy(str,cstart);
}


static REFERENCE_TIME ConvertString2UNITSTime( CString strTime )
{
	if( strTime.GetLength() < 8 ) {
		return 0;
	}

	REFERENCE_TIME  iHour	 = _ttoi( strTime.Mid(0, 2) );
	REFERENCE_TIME  iMinute  = _ttoi( strTime.Mid(3, 2) );
	REFERENCE_TIME  iSecond  = _ttoi( strTime.Mid(6, 2) );
	REFERENCE_TIME  iMSecond = _ttoi( strTime.Mid(9, 3) );
	
	//check if millisecond are of two or three digits
	int pos1 = strTime.ReverseFind(':');
	if(pos1 == -1 || (strTime.GetLength() - pos1) > 4 )
		pos1 = strTime.ReverseFind('.');
	
	pos1 += 1;
	int dig  = strTime.GetLength() -  pos1;
	if( dig == 2 ){
		iMSecond *= 10; 
	}
	
	// here awe 

	REFERENCE_TIME rt = ( (iHour * 3600000) + (iMinute * 60000) + (iSecond * 1000) + iMSecond );
	rt *= 10000;

	return rt;
}

// string format hh:mm:ss:mmm
//				 01:54:39:320	
// return in 100 nano sec UNITS
static REFERENCE_TIME ConvertString2Time(LPCSTR str)
{

	USES_CONVERSION;
	CString strn_	= CA2T(str);
	REFERENCE_TIME res	= ConvertString2UNITSTime(strn_);
	return res;
}

//bmsPrecision == true 00:00:00:000
//bmsPrecision == false 00:00:00:00
static CString ConvertUNITSTime2String( REFERENCE_TIME lTime,bool bmsPrecision=false )
{
	TCHAR ch[20];

	DWORD dwMsec	 = DWORD(lTime / 10000);
	DWORD dwSec		 = dwMsec / 1000;
	DWORD dwHours	 = dwSec / 3600;
	DWORD dwMinutes  = (dwSec % 3600) / 60;
	DWORD dwSeconds  = (dwSec % 3600) - dwMinutes * 60;
	DWORD dwMSeconds = (dwMsec % 1000);
	if (!bmsPrecision)
		dwMSeconds /= 10; // should reflect two digits most significant

	//if( lTime % 100000)
	//{
	//	// we encountered the situation when we write time position in file, in hh:mm:ss:ms format, 
	//	// and other digits rejected. in this case when we read this value it 
	//	dwMSeconds += 1;
	//}
	if (bmsPrecision)
		wsprintf(ch,_T("%.2u:%.2u:%.2u:%.3u"),dwHours,dwMinutes,dwSeconds, dwMSeconds );
	else
		wsprintf(ch,_T("%.2u:%.2u:%.2u:%.2u"),dwHours,dwMinutes,dwSeconds, dwMSeconds );

	CString cstart(ch);
	return cstart;
}

CString GetRegistrySilentPath( GUID app_guid)
{

	HRESULT hr = S_OK;
	LPOLESTR strCLSID;

	CString out;
	// Convert binary CLSID to a readable version
	hr = StringFromCLSID(app_guid, &strCLSID);
	CString key = _T("CLSID\\") + CString(strCLSID) + CString("\\Components");

	HKEY hKey	= 0;
	int res		= RegOpenKeyEx( HKEY_CLASSES_ROOT, key, 0, KEY_READ, &hKey);
	if ( res != 0 )
		return out ;

	res = RegCloseKey(hKey);
	return out = key;
};


class CheckUpdate
{
public:

	static CheckUpdate & Instance(const CString & updateURL);

	void Check();

	HRESULT GetResult();

	CString GetVersion();

	CString GetChanges();

	CString GetDownloadUrl();

	bool IsNewVersionAvail(const CString & curVer);

private:

	CheckUpdate(CString product);

	bool Load(CString & url, CStringA & xml);

	HRESULT m_hResult;

	CString m_checkUpdateURL;

	CString m_version;

	CString m_changes;

	CString m_url;
};

#endif //#define __UTILS_H__
