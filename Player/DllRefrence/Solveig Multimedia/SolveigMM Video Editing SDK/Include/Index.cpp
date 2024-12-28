////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2004-2010 Solveig Multimedia
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
//#include <elsdk.h>
#include <initguid.h>
#include <Classes\eDllwrap.h>
#include <mediaindexdef_i.c>
#include <atlstr.h>
#include "Index.h"
#include "SilentPathFilterOperations.h"


//using namespace ElUtils;

LPWSTR SMM_GetWCHAR(LPCTSTR pIn, LPWSTR pOut)
{
#if  defined(_UNICODE) || defined(UNICODE)
	wcscpy(pOut, (LPCWSTR)pIn);
#else
	int result = ::MultiByteToWideChar(CP_ACP, 0, pIn, -1,
		pOut, strlen(pIn) + 1);
	if(result > 0)
		pOut[result - 1] = 0;
#endif
	return	pOut;
}
/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define CExc CExMsg

CIndexEx::CIndexEx( LPCTSTR slntPath, LPCTSTR tcsIndexFileName, HRESULT &hr  )
{
	USES_CONVERSION;

	CCI_OUTPUT cci_output((void**)&p);
	hr = CreateCOMInstance(CCI_INPUT(slntPath, CLSID_MIxReader, IID_IMIxReader2), cci_output);

	if(SUCCEEDED(hr))
	{
		WCHAR wcsFileName[256];
		if(FAILED(hr = p->put_IndexFileName(SMM_GetWCHAR(tcsIndexFileName, wcsFileName))))
			MessageBox(NULL, _T("Unable to open Index file"), _T("Error"),MB_OK);


		BSTR pStr = NULL;
		if(FAILED(hr = p->get_MediaFileName(&pStr)) || !pStr)
			MessageBox(NULL, _T("Unable to read Index file"), _T("Error"),MB_OK);

		m_bstrMediaFileName = pStr;
		SysFreeString(pStr);
	}
}

CIndexEx::CIndexEx( LPCTSTR slntPath, HRESULT &hr )
{
	USES_CONVERSION;

	CCI_OUTPUT cci_output((void**)&p);
	hr = CreateCOMInstance(CCI_INPUT(slntPath, CLSID_MIxReader, IID_IMIxReader2), cci_output);
	
	if( p == NULL ){
		hr = REGDB_E_CLASSNOTREG;
	}
}

CIndex::CIndex(LPCTSTR tcsIndexFileName)
{
	CCI_OUTPUT cci_output((void**)&p);
	HRESULT hr = CreateCOMInstance(CCI_INPUT(GUID_NULL, CLSID_MIxReader, IID_IMIxReader2), cci_output);
	if(FAILED(hr)){
//		throw CExc(_T("Unable to initialize Elecard Media Index Reader object"), hr);
		MessageBox(NULL, _T("Unable to initialize Elecard Media Index Reader object"), _T("Error"),MB_OK);
	}

	WCHAR wcsFileName[256];
	if(FAILED(hr = p->put_IndexFileName(SMM_GetWCHAR(tcsIndexFileName, wcsFileName))))
//		throw CExc(_T("Unable to open Index file"), hr);
		MessageBox(NULL, _T("Unable to open Index file"), _T("Error"),MB_OK);
	

	BSTR pStr = NULL;
	if(FAILED(hr = p->get_MediaFileName(&pStr)) || !pStr)
//		throw CExc(_T("Unable to read Index file"), hr);
		MessageBox(NULL, _T("Unable to read Index file"), _T("Error"),MB_OK);

	m_bstrMediaFileName = pStr;
	SysFreeString(pStr);
}

CIndex::CIndex(HRESULT *phr,  CString str_err, LPCTSTR tcsIndexFileName)
{

	CCI_OUTPUT cci_output((void**)&p);
	HRESULT hr = CreateCOMInstance(CCI_INPUT(GUID_NULL, CLSID_MIxReader, IID_IMIxReader2), cci_output);
	if(FAILED(hr))
	{
		str_err = _T("Unable to initialize Elecard Media Index Reader object");
		*phr = hr;
		return;
	}

	WCHAR wcsFileName[256];
	if(FAILED(hr = p->put_IndexFileName(SMM_GetWCHAR(tcsIndexFileName, wcsFileName))))
	{
		str_err = _T("Unable to open Index file");
		*phr = hr;
		return;
	}

	BSTR pStr = NULL;
	if(FAILED(hr = p->get_MediaFileName(&pStr)) || !pStr)
	{
		str_err = _T("Unable to read Index file");
			*phr = hr;
		return;
	}

	m_bstrMediaFileName = pStr;
	SysFreeString(pStr);
}

CIndex::CIndex(SAFEARRAY * psa)
{

	CCI_OUTPUT cci_output((void**)&p);
	HRESULT hr = CreateCOMInstance(CCI_INPUT(GUID_NULL, CLSID_MIxReader, IID_IMIxReader2), cci_output);

	if(FAILED(hr))
//		throw CExc(_T("Unable to initialize Elecard Media Index Reader object"), hr);
	MessageBox(NULL, _T("Unable to initialize Elecard Media Index Reader object"), _T("Error"),MB_OK);

	
	if(FAILED(hr = p->put_IndexFileList(psa)))
//		throw CExc(_T("Unable to open one or more index files for this file list"), hr);
	MessageBox(NULL, _T("Unable to open one or more index files for this file list"), _T("Error"),MB_OK);

	m_bstrMediaFileName="";
}

CIndex::CIndex( )
{

	CCI_OUTPUT cci_output((void**)&p);
	HRESULT hr = CreateCOMInstance(CCI_INPUT(GUID_NULL, CLSID_MIxReader, IID_IMIxReader2), cci_output);
	if(FAILED(hr)){
		CString str = _T("Unable to initialize Elecard Media Index Reader object");
//		MessageBox(NULL, str, _T("Error"), MB_OK | MB_ICONWARNING);
	//	throw CExc(str, hr);
	}
}

CIndex::~CIndex()
{
	Release();
//	DbgDumpObjectRegister ();
}

LPCWSTR	CIndex::GetMediaFileName() const
{
	_ASSERT(!!p);
	if(!p)
//		throw CExc(_T("Index file is not opened"));
		MessageBox(NULL, _T("Index file is not opened"), _T("Error"),MB_OK);

	return m_bstrMediaFileName;
}

IMediaIndex* CIndex::GetFrameIndex(int streamNum)
{
	// first guid for video, second for audio
	const LPCWSTR wcsIndexGuids[] = {	L"{E6EC4B79-3952-4bb5-8BE9-826D48A025C8}", L"{E6EC4B9B-3952-4bb5-8BE9-826D48A025C8}"};
	
	_ASSERT(!!p);
	if(!p)
//		throw CExc(_T("Index file is not opened"));
			MessageBox(NULL, _T("Index file is not opened"), _T("Error"),MB_OK);

	IMediaIndex*	pIndex = NULL;
	LONG			nIndexes = 0;
	BSTR			pStr = NULL;

	HRESULT hr = p->get_IndexesCount(&nIndexes);
	_ASSERT(SUCCEEDED(hr));

	if (SUCCEEDED(hr) && nIndexes > 0)
	{
		if (nIndexes == 1)
		{
			if (p->get_Index(0, &pIndex) == S_OK)
			{
				return pIndex;
			}
		}
		else
		{
			// find video guid
			//
		    int curVideoStreamNum = 0;
			for (LONG n = nIndexes-1; n >=0; n--)
			{
				if (p->get_Index(n, &pIndex) == S_OK)
				{
					// Check guid
					if(SUCCEEDED(hr = pIndex->get_EntryStructGuid(&pStr)) && pStr)
					{
						if(wcsicmp(pStr, wcsIndexGuids[0]) == 0 )
						{
							if (curVideoStreamNum == streamNum)
							{
								SysFreeString(pStr);
								return pIndex;
							}
							curVideoStreamNum++;
						}
						SysFreeString(pStr);
						pStr = NULL;
					}

					pIndex->Release();
				}
			}
		}
	}
					
	return NULL;
}

BOOL CIndex::IsMLMIX(LPCTSTR tcsFileName)
{
	static LPCTSTR tcsListExt[] = {_T(".mlmix")};
	TCHAR tcsExt[128];
	_tsplitpath(tcsFileName, NULL, NULL, NULL, tcsExt);
	for(int n = 0; n < sizeof(tcsListExt)/sizeof(LPCTSTR); n++)
		if(_tcsicmp(tcsListExt[n], tcsExt) == 0)
			return TRUE;
	return FALSE;
}


HRESULT CIndexEx::GetNextIFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta)
{
	HRESULT hr	= E_FAIL;
	UINT step	= delta;
	
	LONG lNumber = long(CurrentFrameNum);
	
	CComPtr<IMediaIndex> pIndex = NULL; 
	pIndex.Attach(GetFrameIndex());
	
	if ( pIndex ) 
	{
		
		LONG lEntriesCount = 0;
		pIndex->get_EntriesCount(&lEntriesCount);
		
		// Convert frame number to IndexEntry number
		
		int ix = lNumber - 5 * direction;
		if ( ix < 0 ) 
			 ix = 0;
		
		if (ix > lEntriesCount) 
			ix = lEntriesCount - 1;
		
		do {
			CComPtr<IIndexEntry> pIndexEntry = NULL;
			
			if (SUCCEEDED(hr = pIndex->get_Entry(ix,&pIndexEntry))) 
			{
				long lEntryNum = 0;
				if(SUCCEEDED(pIndexEntry->get_Number(&lEntryNum))) 
				{
					if (lNumber == lEntryNum) 
					{
						lNumber = ix;
						pIndexEntry.Release();
						break;
					}
				}
			}
			pIndexEntry.Release();
			
			ix += direction;
			
		} while((ix < lEntriesCount ) && (ix >= 0));
		
		
		lNumber += direction;
		// find the next I frame
		do {
			
			CComPtr<IIndexEntry> pIndexEntry = NULL;
			
			if (SUCCEEDED(hr = pIndex->get_Entry(lNumber,&pIndexEntry))) 
			{
				
				BSTR bstrEntryType = NULL;
				pIndexEntry->get_TypeCode(&bstrEntryType);
				
				if (!_wcsicmp(bstrEntryType,L"I")) 
				{
					
					ULONG HighWord = 0;
					ULONG LowWord = 0;
					
					if (SUCCEEDED(hr = pIndexEntry->GetTime((LONG*)&HighWord, (LONG*)&LowWord))) {
						*pOutRT = (((REFERENCE_TIME)HighWord << (sizeof(ULONG) * 8)) | LowWord);
						
						SysFreeString(bstrEntryType);
						if ( !(--step) ) {
							pIndexEntry.Release();
							break;
						}
					}
					
					SysFreeString(bstrEntryType);
				}
				pIndexEntry.Release();
			}
			else {
				break;
			}
			
			lNumber += direction;
			
		} while (TRUE);
	}
	pIndex.Release();
	
	return hr;
}

HRESULT CIndexEx::GetNextFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta)
{
	HRESULT hr = E_FAIL;
	
	LONG lNumber = LONG(CurrentFrameNum + delta * direction);
	
//	CComPtr<IMediaIndex> pIndex = GetFrameIndex();
	CComPtr<IMediaIndex> pIndex = NULL; 
	pIndex.Attach(GetFrameIndex());
	
	if ( pIndex ) 
	{
		
		LONG lEntriesCount = 0;
		pIndex->get_EntriesCount(&lEntriesCount);
		
		// Convert frame number to IndexEntry number
		
		int ix = lNumber - 5 * direction;
		if ( ix < 0 ) 
			ix = 0;
        
		if ( ix > lEntriesCount )
		ix = lEntriesCount - 1;
		
		do {
			CComPtr<IIndexEntry> pIndexEntry = NULL;
			
			if (SUCCEEDED(hr = pIndex->get_Entry(ix,&pIndexEntry)))
			{
				long lEntryNum = 0;
				if(SUCCEEDED(pIndexEntry->get_Number(&lEntryNum))) 
				{
					if (lNumber == lEntryNum) 
					{
						lNumber = ix;
						
						ULONG HighWord = 0;
						ULONG LowWord = 0;
						
						if ( SUCCEEDED(hr = pIndexEntry->GetTime((LONG*)&HighWord, (LONG*)&LowWord ) ) ) 
							*pOutRT = (((REFERENCE_TIME)HighWord << (sizeof(ULONG) * 8)) | LowWord);
						
						pIndexEntry.Release();
						break;
					}
				}
			}
			pIndexEntry.Release();
			
			ix += direction;
			
		} while((ix < lEntriesCount ) && (ix >= 0));
	}
	
	return hr;
}
	  
//---------------

HRESULT	CIndexReader::SetIndexFN( CString fn )
{
	HRESULT hr = S_OK;
	if(FAILED( hr = p->put_IndexFileName( fn.AllocSysString() ) ) ) 
	{
		//		str_err = "Unable to open Index file";
		return hr;
	}

	BSTR pStr = NULL;
	if(FAILED( hr = p->get_MediaFileName(&pStr) ) || !pStr)
	{
		//		str_err = "Unable to read Index file";
		return hr;
	}

//	m_bstrMediaFileName = pStr;
	SysFreeString( pStr );
	m_bInited = TRUE;
	return S_OK;
}


REFERENCE_TIME CIndexReader::FindFrameInIndex( REFERENCE_TIME rtTime )
{
	if( FALSE == IsIndexLoaded() )
		return -1;
	

	REFERENCE_TIME prev_rt	= m_rtTimeStamp;
	REFERENCE_TIME rt		= 0;
	HRESULT hr = S_OK;

	if( rtTime >= m_rtTimeStamp )
	{
		if( m_llCurrFrame == 0 )
			m_llCurrFrame = -1;
		
		while( TRUE )
		{
			hr = GetNextFrameTime( m_llCurrFrame , &rt, 1, 1);
			if(FAILED(hr))
				break;
			

			m_llCurrFrame++;

			if( rt >= rtTime )
			{
				if( (rtTime  - prev_rt) >= ( rt - rtTime ) ){
					m_rtTimeStamp = rt ;
				}
				else{
					m_rtTimeStamp = prev_rt ;
					m_llCurrFrame--;
				}
				break;
			}
			prev_rt = rt;
		}
	}
	else if( rtTime < m_rtTimeStamp )
	{
		while( TRUE)
		{
			hr = GetNextFrameTime( m_llCurrFrame , &rt, -1, 1);
			if(FAILED(hr))
				break;
			
			m_llCurrFrame--;

			if( rt <= rtTime )
			{
				if( (prev_rt - rtTime  ) >= (  rtTime - rt ) ){
					m_rtTimeStamp	 = rt ;
				}
				else{
					m_rtTimeStamp = prev_rt ;
					m_llCurrFrame++;
				}
				break;
			}
			prev_rt = rt;
		}
	}

	return m_rtTimeStamp ;
}
