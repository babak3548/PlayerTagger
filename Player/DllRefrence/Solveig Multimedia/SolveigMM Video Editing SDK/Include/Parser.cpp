#include "StdAfx.h"
#include <cstringt.h>
#include "parser.h"
#include <SMM_Utils.h>
//#include <AutoSplitter.h>

CParser::CParser(void):
m_hFile( INVALID_HANDLE_VALUE ),
m_error(PE_NO_ERRORS)
{
	HRESULT hr;
	hr = CoInitialize(NULL);
	m_csFileName = _T("");
}

CParser::~CParser(void)
{
	FreeXTLFile();
}

HRESULT	CParser::LoadXTLFile( CString szFileName)
{
	if( !IsValidXTLFile( szFileName ) )
		return E_FAIL;

	HRESULT hr = spXTL.CoCreateInstance(__uuidof(DOMDocument));

	CString szEncodedData = _T("");
	try
	{
		szEncodedData = EncodeSourceFile(szFileName);
	}catch(...)
	{
		return E_FAIL;
	}

	m_csFileName = szFileName;
	VARIANT_BOOL bSuccess = false;
	hr = spXTL->loadXML(szEncodedData.AllocSysString(), &bSuccess);
	return hr;
}

HRESULT CParser::GetValueByName(CString &value, CString name, IXMLDOMNode * rootnode)
{
	
	value = "";
	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNode> spXMLParameter;
	CComPtr<IXMLDOMNamedNodeMap> spAttr;

	// Ask access to the field's attributes
	hr = rootnode->get_attributes(&spAttr);
	if (hr != S_OK)
		return hr;

	// Ask access to the "Name" object
	hr = spAttr->getNamedItem(name.AllocSysString(), &spXMLParameter);
	if (hr != S_OK)
		return hr;

	// Request It's value
	VARIANT var;
	hr = spXMLParameter->get_nodeValue(&var);
	if (hr != S_OK)
		return hr;
	
	value = var.bstrVal;
	value = DecodeString(value);

	return S_OK;
}

HRESULT CParser::GetGroupName(int nGroup, CString &sName)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spList;
	CComPtr<IXMLDOMNode> spXMLNode;
	CComPtr<IXMLDOMNode> spXMLNode1;

	USES_CONVERSION;
	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spList);
	if (hr != S_OK)
		return hr;

	// Get requested element
	hr = spList->get_item(nGroup, &spXMLNode1);
	if (hr != S_OK)
		return hr;

	hr = GetValueByName(sName, _T("name"), spXMLNode1);
	GetAbsPath( sName );
	return hr;
}

HRESULT CParser::GroupToTask( int nGroup, SMM_GROUP_TASK *pTask )
{
	HRESULT hr			= S_OK;
	long	lmaxclips	= 0;
	long	lTrackNum	= 0;

	hr = GetGroupName ( nGroup, pTask->szDstName ); 
	if (hr != S_OK ) 
		return E_FAIL;
	
	hr = GetGroupType ( nGroup, pTask->nTaskType );
	
	GetGroupOutputType(nGroup, pTask->nOutType);
	
	hr = GetTracksCount( nGroup, (long&)pTask->nTrackCount);
	if ( hr != S_OK ) 
		return E_FAIL;

	for( UINT nTrack = 0; nTrack < pTask->nTrackCount ; nTrack++ )
	{
		SMM_TRACK_INFO * trck = &pTask->tracks[nTrack];
		hr = GetTrimmerConfig( nGroup, nTrack, trck->ulFlags) ;
		if ( hr != S_OK )
			trck->ulFlags = 0;

		hr = GetAudioStream		( nGroup, nTrack, trck->nAudioStream );
		hr = GetVideoStream		( nGroup, nTrack, trck->nVideoStream );
		hr = GetTrimmAccurType	( nGroup, nTrack, trck->nTrimmAccurType );	
		hr = GetASInformation	( nGroup, nTrack, (DWORD&)trck->dwASMode, trck->llASValue );
		hr = GetTrackOutType	( nGroup, nTrack, trck->nOutType );
		if (FAILED(hr))
			return hr;

		CString indName;
		hr = GetMPEG2IdxFile	( nGroup, nTrack, indName );
		indName.CopyChars(trck->szMPEG2IdxFileName, indName.GetBuffer(),  indName.GetLength() );

		hr = GetClipsCount		( nGroup, nTrack, lmaxclips);
		if ( hr != S_OK) 
			return E_FAIL;
		
		pTask->tracks[nTrack].CreateClips(lmaxclips);
		pTask->tracks[nTrack].nClips = 0;

		for ( long j = 0; j < lmaxclips; j++ )
		{
			SMM_CLIP_INFO ci;
			hr = GetClipInfo( nGroup, nTrack, j, ci);
			if (hr != S_OK)
				continue; // Some error: Skip clip

			int pos = pTask->tracks[nTrack].nClips++;
			pTask->tracks[nTrack].pClips[pos] = ci;
		}
	}

	return hr;
}

HRESULT CParser::GetClipInfo ( int nGroup, int nTrack, int nClip, SMM_CLIP_INFO &ClipInfo)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList>	spGroupsList;
	CComPtr<IXMLDOMNodeList>	spTrackList;
	CComPtr<IXMLDOMNodeList>	spClipList;
	CComPtr<IXMLDOMNode>		spGroup;
	CComPtr<IXMLDOMNode>		spTrack;
	CComPtr<IXMLDOMNode>		spClip;
	CComPtr<IXMLDOMNode>		spXMLNode;

	USES_CONVERSION;
	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;


	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	// Get child (clips) list
	hr = spTrack->get_childNodes(&spClipList);
	if (hr != S_OK)
		return hr;

	// Go into the requested Clip
	hr = spClipList->get_item(nClip, &spClip);
	if (hr != S_OK)
		return hr;

	CString timeFormat = _T("");
	hr = GetValueByName(timeFormat, _T("timeFormat"), spClip);

	CString strStart;
	hr = GetValueByName(strStart, _T("start"), spClip);
	if (hr != S_OK)
		return hr;

	CString strEnd;
	hr = GetValueByName(strEnd, _T("stop"), spClip);
	if (hr != S_OK)
		return hr;

	if (timeFormat == _T("100ns_units"))
	{
		
		ClipInfo.rtStart = _ttoi64(strStart);	
		ClipInfo.rtEnd = _ttoi64(strEnd);
	}
	else if (timeFormat.IsEmpty() || timeFormat == _T("time10ms"))
	{
		// And Fill fields		
		ClipInfo.rtStart = ConvertString2UNITSTime(strStart);	
		ClipInfo.rtEnd = ConvertString2UNITSTime(strEnd);
	}
	else
		return E_FAIL;
	

	CString temp;
	hr = GetValueByName(temp, _T("mute"), spClip);
	if (hr == S_OK) 
	{
		CString str ("T");
		int n = str.Compare(temp);

		ClipInfo.bMute = ( n == 0 )? TRUE : FALSE;
	}

	CString str;
	hr = GetValueByName( str , _T("src"), spClip);
	GetAbsPath(str);
	str.CopyChars( ClipInfo.wsfName, str.GetBuffer(),  str.GetLength() );
	
	return hr;
}


HRESULT CParser::GetGroupsCount(long * lCount)
 {
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spXMLNode;

	if (lCount == NULL)
		return E_POINTER;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return E_FAIL;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return E_FAIL;

	// Get requested group
	hr = spGroupsList->get_length(lCount);

	return hr;
}

HRESULT CParser::GetClipsCount( int nGroup, int nTrack, long &lCount )
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNodeList> spClipList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spTrack;
	CComPtr<IXMLDOMNode> spXMLNode;


	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	// Go into the track

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	// Get child (clips) list
	hr = spTrack->get_childNodes(&spClipList);
	if (hr != S_OK)
		return hr;

	hr = spClipList->get_length(&lCount);

	return hr;
}

HRESULT CParser::GetTracksCount( int nGroup, long &lTrackNum )
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;

	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spXMLNode;

	USES_CONVERSION;
	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_length(&lTrackNum);
	return hr;
}

HRESULT CParser::GetTrimmerConfig( int nGroup, int nTrack, DWORD &dwConfig )
{
	if( spXTL == NULL )
		return E_FAIL;

	HRESULT						hr	= S_OK;
	CComPtr<IXMLDOMNodeList>	spGroupsList;
	CComPtr<IXMLDOMNodeList>	spTrackList;
	CComPtr<IXMLDOMNode>		spGroup;
	CComPtr<IXMLDOMNode>		spTrack;
	CComPtr<IXMLDOMNode>		spXMLNode;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;
	
	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;
	
	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	int		iVideoStream		= 0;
	int		iAudioStream		= 0;
	int		iLookAtSampleTimes	= 0;
	int		iActiveMode			= 0;	
	
	CString tmp;
	dwConfig = 0;
	hr = GetValueByName(tmp, _T("video"), spTrack);
	if (hr == S_OK){
		iVideoStream = _wtoi(tmp.AllocSysString());
	}else{
		iVideoStream = -1;
	}

	hr = GetValueByName(tmp, _T("audio"), spTrack);
	if (hr == S_OK){
		iAudioStream = _wtoi( tmp );
	}else{
		iAudioStream = -1;
	}

	hr = GetValueByName(tmp, _T("obey_sample_times"), spTrack);
	if (hr == S_OK){
		iLookAtSampleTimes = _wtoi(tmp);
	}

	hr = GetValueByName(tmp, _T("trim_type"), spTrack);
	if (hr == S_OK){
		iActiveMode = _wtoi( tmp );
	}


	// Process converting parameters to the Trim Configuration
	if (iLookAtSampleTimes == 1)
		dwConfig |= SMM_TrimFlags_ObeySampleTimes ;

	if (iActiveMode == 1)
		dwConfig |= SMM_TrimFlags_UsePositioning;

	if ((iVideoStream == -1) &&
		(iAudioStream == -1)){
			// Error? not set params "audio" and "video"
			// We will think, that user want trim 1st audio and 1st video stream
			iVideoStream = 1;
			iAudioStream = 1;
		}

	if ((iVideoStream == 0) &&
		(iAudioStream == 0)){
			// Error. user don't want trim any streams...
			dwConfig |= SMM_TrimFlags_VideoOnly;
			dwConfig |= SMM_TrimFlags_AudioOnly;
			return E_FAIL;
		}

	if (iVideoStream == 0)
		dwConfig |= SMM_TrimFlags_AudioOnly;

	if (iAudioStream == 0)
		dwConfig |= SMM_TrimFlags_VideoOnly;

	return S_OK;
}

void CParser::FreeXTLFile()
{
	if (spXTL == NULL)
		return;

	spXTL.Release();
}

HRESULT CParser::GetAudioStream(int nGroup, int trackNum, int &nAudio)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode>	 spGroup;
	CComPtr<IXMLDOMNode>	 spTrack;
	CComPtr<IXMLDOMNode>	 spXMLNode;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(trackNum, &spTrack );
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");
	hr = GetValueByName(tmp, _T("audio"), spTrack);
	if (hr == S_OK){
		nAudio = _wtoi(tmp);
	}else{
		hr = GetValueByName(tmp, _T("video"), spTrack);
		if (hr == S_OK){
			nAudio = 0;
		}else{
			nAudio = 1;
		}
	}

	return S_OK;
}

HRESULT CParser::GetASInformation( int nGroup, int nTrack, DWORD &dwMode, LONGLONG &llValue)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode>	 spGroup;
	CComPtr<IXMLDOMNode>	 spTrack;
	CComPtr<IXMLDOMNode>	 spXMLNode;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	CString szMode;
	hr = GetValueByName(szMode, _T("as_mode"), spTrack);
	if (FAILED(hr))
	{
		dwMode  = SMM_AutoSplitType_None;
		llValue = 0;
		return S_OK;
	}

	CString szValue;
	hr = GetValueByName(szValue, _T("as_value"), spTrack);
	if (FAILED(hr))
	{
		dwMode  = SMM_AutoSplitType_None;
		llValue = 0;
		return S_OK;
	}

	if (szMode == _T("time"))
	{
		dwMode  = SMM_AutoSplitType_TimeBased;
		llValue = ConvertString2UNITSTime(szValue);
	}
	else
	if (szMode == _T("size"))
	{
		dwMode  = SMM_ProgressType_SizeBased;
		llValue = DecodeFileSize(szValue);
	}
	else
	{
		dwMode  = SMM_AutoSplitType_None;
		llValue = 0;
	}

	return S_OK;
}

LONGLONG CParser::DecodeFileSize(CString szData)
{
	CString szNumber;
	int nMul = 0;

	szData.MakeLower();
	for (int i = 0; i<szData.GetLength(); i++)
	{
		if ((szData[i] == '0') ||
			(szData[i] == '1') ||
			(szData[i] == '2') ||
			(szData[i] == '3') ||
			(szData[i] == '4') ||
			(szData[i] == '5') ||
			(szData[i] == '6') ||
			(szData[i] == '7') ||
			(szData[i] == '8') ||
			(szData[i] == '9'))
		{
			szNumber += szData[i];
			continue;
		}

		if (szData[i] == ' ')
			continue;

		if (szData[i] == 'b')
			nMul = 0;
		if (szData[i] == 'k')
			nMul = 1;
		if (szData[i] == 'm')
			nMul = 2;
		if (szData[i] == 'g')
			nMul = 3;

		break;
	}

	USES_CONVERSION;


	LONGLONG llSize = _ttoi64( szNumber  );

	for (int i = 0; i < nMul; i++)
		llSize *= 1024;

	return llSize;
}

HRESULT CParser::GetVideoStream ( int nGroup, int nTrack, int &nVideo)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spTrack;
	CComPtr<IXMLDOMNode> spXMLNode;


	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");
	hr = GetValueByName(tmp, _T("video"), spTrack);
	if (hr == S_OK){
		nVideo = _wtoi(tmp);
	}else{
		hr = GetValueByName(tmp, _T("audio"), spTrack);
		if (hr == S_OK){
			nVideo = 0;
		}else{
			nVideo = 1;
		}
	}

	return S_OK;
}

HRESULT CParser::GetGroupType(int nGroup, SMM_TaskType &nGrType)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spList;
	CComPtr<IXMLDOMNode> spXMLNode;
	CComPtr<IXMLDOMNode> spXMLNode1;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spList);
	if (hr != S_OK)
		return hr;

	// Get requested element
	hr = spList->get_item(nGroup, &spXMLNode1);
	if (hr != S_OK)
		return hr;

	CString sName;
	 hr = GetValueByName(sName, _T("mode"), spXMLNode1);
	 if (hr != S_OK){
		 return hr;
	 }
	 
	 if( sName == CString("multiplexing") )
	 {
		nGrType = SMM_Task_Type_Muxing;
	 }
	 else
	 if( sName == CString("joining") )				//Smi
	 {
		 nGrType = SMM_Task_Type_Joining;
	 }
	 else
	 if( sName == CString("indexation") )				
	 {
		 nGrType = SMM_Task_Type_Indexation;
	 }

	 return S_OK;
}
HRESULT CParser::GetGroupOutputType(int nGroup, SMM_OutputTypes &nOutputType)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spList;
	CComPtr<IXMLDOMNode> spXMLNode;
	CComPtr<IXMLDOMNode> spXMLNode1;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spList);
	if (hr != S_OK)
		return hr;

	// Get requested element
	hr = spList->get_item(nGroup, &spXMLNode1);
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");
	hr = GetValueByName(tmp, _T("out_type"), spXMLNode1);
	if (hr == S_OK)
		nOutputType = Str2FT( tmp );
    return S_OK;
}
HRESULT	CParser::GetTrimmAccurType( int nGroup, int nTrack, SMM_TrimmAccuracyType &nTrimmAccurType	)
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spTrack;
	CComPtr<IXMLDOMNode> spXMLNode;


	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;


	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");

	//default value for non MPEG-2 Files
	nTrimmAccurType = SMM_TrimmAccuracyType_Deflt;

	hr = GetValueByName(tmp, _T("accuracy"), spTrack );
	if( hr == S_OK )
	{
		if( tmp == CString("gop") ){
			nTrimmAccurType = SMM_TrimmAccuracyType_GOP;
		}
		else
			if(tmp == CString("frame")){
				nTrimmAccurType = SMM_TrimmAccuracyType_Frame;
			}
	}

	return S_OK;
}
HRESULT	CParser::GetMPEG2IdxFile( int nGroup, int nTrack, CString &strFN )
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList> spGroupsList;
	CComPtr<IXMLDOMNodeList> spTrackList;
	CComPtr<IXMLDOMNode> spGroup;
	CComPtr<IXMLDOMNode> spTrack;
	CComPtr<IXMLDOMNode> spXMLNode;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");

	strFN = _T("");
	hr = GetValueByName(tmp, _T("MPEG2_index_file"), spTrack );
	GetAbsPath(tmp);
	if( hr == S_OK ){
		strFN = tmp;
	}

	return S_OK;
}

HRESULT CParser::GetTrackOutType( int nGroup, int nTrack, SMM_OutputTypes &nOutType )
{
	if (spXTL == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IXMLDOMNodeList>	spGroupsList;
	CComPtr<IXMLDOMNodeList>	spTrackList;
	CComPtr<IXMLDOMNode> 		spGroup;
	CComPtr<IXMLDOMNode> 		spTrack;
	CComPtr<IXMLDOMNode> 		spXMLNode;

	// Select root
	hr = spXTL->selectSingleNode( T2BSTR(__T("timeline")), &spXMLNode );
	if (hr != S_OK)
		return hr;

	// Get child list
	hr = spXMLNode->get_childNodes(&spGroupsList);
	if (hr != S_OK)
		return hr;

	// Get requested group
	hr = spGroupsList->get_item(nGroup, &spGroup);
	if (hr != S_OK)
		return hr;

	hr = spGroup->get_childNodes(&spTrackList);
	if (hr != S_OK)
		return hr;

	// Go into the track
	hr = spTrackList->get_item(nTrack, &spTrack );
	if (hr != S_OK)
		return hr;

	CString tmp = _T("");
	hr = GetValueByName(tmp, _T("out_type"), spTrack);
	if (hr == S_OK){
		nOutType = Str2FT( tmp );
		// get group output type make error if no the same
		SMM_OutputTypes groupOutType = SMM_File_Type_NO;
		GetGroupOutputType(nGroup, groupOutType);
		if (groupOutType != SMM_File_Type_NO && groupOutType != nOutType)
		{
			SetError(PE_GROUP_TRACK_OUT_NOT_EQUAL);
			return E_FAIL;
		}
	}else{
		nOutType = SMM_File_Type_NO; 
	}

	return S_OK;
}
CString CParser::EncodeSourceFile(CString szFileName)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	// Read source file 
	hFile = CreateFile(szFileName, 
							  GENERIC_READ, 
							  FILE_SHARE_READ, 
							  NULL, 
							  OPEN_EXISTING, 
							  0, 
							  0);

	if (hFile == INVALID_HANDLE_VALUE)
		return _T("");

	DWORD dwSize = GetFileSize(hFile, NULL);
	if ( dwSize == INVALID_FILE_SIZE ){
		CloseHandle(hFile);
		return _T("");
	}

	BYTE * buffer = new BYTE[dwSize + 10];
	memset(buffer, 0, dwSize + 10);
	DWORD n = 0;

	ReadFile(hFile, buffer, dwSize, &n, NULL);
	if (dwSize != n)
	{
		SELF_DELETE_ARR( buffer);
		CloseHandle(hFile);
		return _T("");
	}

	CloseHandle(hFile);

	CString szResult = _T("");

	if ((buffer[0] == 0xFF) && 
		(buffer[1] == 0xFE)) {
		szResult = ProcessUnicodeEncoding( buffer, dwSize );
	}
	else {
		szResult = ProcessMultiByteEncoding(buffer, dwSize);
	}

	SELF_DELETE_ARR( buffer);

	return szResult;
	
}

CString	CParser::DecodeString(CString szStr)
{
	if (szStr[0] != 'X')
		return szStr;

	// Process decode: CHAR'S HEX CODE -> CHAR
	CString szResult = _T("");
	for (int i = 1; i < szStr.GetLength(); i+=4)
	{
		BYTE byte1 = (BYTE)szStr[i];
		BYTE byte2 = (BYTE)szStr[i+1];
		BYTE byte3 = (BYTE)szStr[i+2];
		BYTE byte4 = (BYTE)szStr[i+3];

		if ((byte1 >= '0') && (byte1 <= '9'))
			byte1 -= '0';
		if ((byte1 >= 'a') && (byte1 <= 'f'))
			byte1 -= ('a' - 10);
		if ((byte1 >= 'A') && (byte1 <= 'F'))
			byte1 -= ('A' - 10);

		if ((byte2 >= '0') && (byte2 <= '9'))
			byte2 -= '0';
		if ((byte2 >= 'a') && (byte2 <= 'f'))
			byte2 -= ('a' - 10);
		if ((byte2 >= 'A') && (byte2 <= 'F'))
			byte2 -= ('A' - 10);

		if ((byte3 >= '0') && (byte3 <= '9'))
			byte3 -= '0';
		if ((byte3 >= 'a') && (byte3 <= 'f'))
			byte3 -= ('a' - 10);
		if ((byte3 >= 'A') && (byte3 <= 'F'))
			byte3 -= ('A' - 10);

		if ((byte4 >= '0') && (byte4 <= '9'))
			byte4 -= '0';
		if ((byte4 >= 'a') && (byte4 <= 'f'))
			byte4 -= ('a' - 10);
		if ((byte4 >= 'A') && (byte4 <= 'F'))
			byte4 -= ('A' - 10);

		CHAR chTemp[(2 + 1) * 2] = {0};
		chTemp[0] = byte3 * 0x10 + byte4;
		chTemp[1] = byte1 * 0x10 + byte2;

		szResult += DecodeChar((LPBYTE)chTemp);
	}

	return szResult;
}

CString CParser::DecodeChar(LPBYTE pBuffer)
{
	CString szResult = _T("");

#ifndef _UNICODE
	if (pBuffer[1] != 0)
	{
		pBuffer[0] = '?';
		pBuffer[1] = '0';
	}

	szResult += CString(pBuffer);
#else
	wchar_t * pTemp = (wchar_t *)pBuffer;
	szResult = pTemp;
#endif

	return szResult;
}

CString CParser::EncodeUnicodeString(CString szStr)
{
	// Process encode: TCHAR -> CHAR'S HEX CODE
	CString szResult = _T("X");

	for ( int i = 0; i<szStr.GetLength(); i++ )
	{
		WORD wData = szStr[i];
		BYTE byte1 = 0;
		BYTE byte2 = 0;
		BYTE byte3 = 0;
		BYTE byte4 = 0;

		byte4 =  wData % 0x10;
		byte3 = (wData % 0x100   - byte4) / 0x10;
		byte2 = (wData % 0x1000  - byte3 * 0x10  - byte4) / 0x100;
		byte1 = (wData % 0x10000 - byte2 * 0x100 - byte3 * 0x10 - byte4) / 0x1000;

		if ((byte1 >= 0) && (byte1 <= 9))
			byte1 += '0';
		if ((byte1 >= 10) && (byte1 <= 15))
			byte1 += 'A' - 10;

		if ((byte2 >= 0) && (byte2 <= 9))
			byte2 += '0';
		if ((byte2 >= 10) && (byte2 <= 15))
			byte2 += 'A' - 10;

		if ((byte3 >= 0) && (byte3 <= 9))
			byte3 += '0';
		if ((byte3 >= 10) && (byte3 <= 15))
			byte3 += 'A' - 10;

		if ((byte4 >= 0) && (byte4 <= 9))
			byte4 += '0';
		if ((byte4 >= 10) && (byte4 <= 15))
			byte4 += 'A' - 10;

		CHAR tcTemp[4*2 + 2] = {0};
		tcTemp[0] = byte1;
		tcTemp[2] = byte2;
		tcTemp[4] = byte3;
		tcTemp[6] = byte4;

		wchar_t * wcTemp = (wchar_t *)tcTemp;

		szResult += wcTemp;
	}

	return szResult;
}

CString CParser::EncodeMultiByteString(CString szStr)
{
	// Process encode: CHAR -> CHAR'S HEX CODE
#ifdef _UNICODE
	return EncodeUnicodeString(szStr);
#endif

	CString szResult = _T("X");

	for (int i = 0; i<szStr.GetLength(); i++){
		char byte1 = 0;
		char byte2 = 0;

		byte1 = szStr[i] / 16;
		byte2 = szStr[i] % 16;

		if ((byte1 >= 0) && (byte1 <= 9))
			byte1 += '0';
		if ((byte1 >= 10) && (byte1 <= 15))
			byte1 += 'A' - 10;

		if ((byte2 >= 0) && (byte2 <= 9))
			byte2 += '0';
		if ((byte2 >= 10) && (byte2 <= 15))
			byte2 += 'A' - 10;

		szResult += _T("00") + (CString)byte1 + (CString)byte2;
	}

	return szResult;
}


HRESULT CParser::WriteXTLFile(CString szFileName, SMM_GROUP_TASK tasks[], int nTasks)
{
	HRESULT hr = S_OK;

	m_hFile = CreateFile(	szFileName, 
							  GENERIC_WRITE,
							  0,
							  NULL,
							  CREATE_ALWAYS,
							  FILE_ATTRIBUTE_NORMAL,
							  0);
	
	if( m_hFile == INVALID_HANDLE_VALUE ){
		return HRESULT_FROM_WIN32( GetLastError() );
	}

#ifdef _UNICODE
	hr = WriteUnicodeHeader(m_hFile);
#endif

    hr = WriteString( m_hFile, _T("<timeline>"));
	
	for ( int i = 0; i < nTasks; i++) {
		WriteGroupPart( tasks[i] );
	}

	hr = WriteString(m_hFile, _T("</timeline>"));
	CloseHandle(m_hFile);
	return hr;
}

HRESULT CParser::WriteClipPart	( SMM_CLIP_INFO &clip	)
{

	if( m_hFile == INVALID_HANDLE_VALUE ){
		return HRESULT_FROM_WIN32( GetLastError() );
	}
	
	CString str2wr;
	str2wr =  _T("\t\t\t <clip ");
	str2wr += _T("src=")	  +	AddQuotes( clip.wsfName ) + _T(" ");
	{
		CString startStr;
		startStr.Format(_T("%I64d"),clip.rtStart);
		str2wr += _T("start=")	  + AddQuotes( startStr ) + _T(" ");
		CString stopStr;
		stopStr.Format(	_T("%I64d"),clip.rtEnd);
		str2wr += _T("stop=")	  + AddQuotes( stopStr ) + _T(" ");
	}
	//str2wr += _T("start=")	  + AddQuotes( ConvertUNITSTime2String(clip.rtStart) ) + _T(" ");
	//str2wr += _T("stop=")	  + AddQuotes( ConvertUNITSTime2String(clip.rtEnd) ) + _T(" ");

	str2wr += _T("timeFormat=") + AddQuotes( _T("100ns_units") ) + _T(" ");	// could be 100nsunits, time10ms == default	if no such element

	if( clip.bMute ){
		str2wr += _T("mute=") + AddQuotes(_T("T")) + _T(" ");
	}
	str2wr += _T("/>");
	HRESULT hr = WriteString(m_hFile, str2wr );
	return hr;
}

HRESULT CParser::WriteTrackPart(SMM_TRACK_INFO &track  )
{
	if( m_hFile == INVALID_HANDLE_VALUE ){
		return HRESULT_FROM_WIN32( GetLastError() );
	}
	
	WCHAR tmp[10];
	CString str2wr;
	str2wr =  _T("\t\t<track ");
	
	if( track.nOutType != SMM_File_Type_NO ) {
		str2wr += _T("out_type=") + AddQuotes( XTLDescr_TrackOutType[ track.nOutType ] ) + _T(" ");
	}
	str2wr += _T("video=")	  + AddQuotes( _itot( track.nVideoStream, tmp, 10 ) ) + _T(" ");
	str2wr += _T("audio=")	  + AddQuotes( _itot( track.nAudioStream, tmp, 10 ) ) + _T(" ");
	
	if(track.nTrimmAccurType != SMM_TrimmAccuracyType_Deflt ){
		str2wr += _T("accuracy=") + AddQuotes( XTLDescr_TrackAccuracy[ track.nTrimmAccurType ] ) + _T(" ");
	}

	if( 0 < wcslen( track.szMPEG2IdxFileName ) )	{
		str2wr += _T("MPEG2_index_file=") + AddQuotes( track.szMPEG2IdxFileName ) + _T(" "); 
	}

	if( track.ulFlags & SMM_TrimFlags_ObeySampleTimes ){
		str2wr += _T("obey_sample_times=") + AddQuotes( _itot(1, tmp, 10) ) + _T(" ");
	}
	if( track.ulFlags & SMM_TrimFlags_UsePositioning ){
		str2wr += _T("trim_type=") + AddQuotes( XTLDescr_TrackTrimType[1] ) + _T(" "); //use positioning
	}

	if( track.dwASMode != SMM_AutoSplitType_None )
	{
		str2wr += _T("as_mode=") + AddQuotes( XTLDescr_TrackAutoSplitType[track.dwASMode] ) + _T(" ");
		CString val;
		
		if( track.dwASMode == SMM_AutoSplitType_TimeBased ){
			val = ConvertUNITSTime2String( track.llASValue );
		}
		else
		if( track.dwASMode ==  SMM_ProgressType_SizeBased ){
			val.Format(_T("%I64"), track.llASValue);
		}

		str2wr += _T("as_value=") + AddQuotes( val ) + _T(" "); //use positioning
	}

	str2wr += _T(">");
	
	//
	HRESULT hr = WriteString(m_hFile, str2wr );

	for( int n = 0; n < track.nClips; n++){
		WriteClipPart(track.pClips[n] );
	}
	
	str2wr = _T("\t\t</track>");
	hr = WriteString(m_hFile, str2wr );
	return hr;
}

HRESULT CParser::WriteGroupPart(SMM_GROUP_TASK &task )
{
	if( m_hFile == INVALID_HANDLE_VALUE ){
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	CString str2wr;
	str2wr =  _T("\t <group ");
	str2wr += _T("name=") + AddQuotes(task.szDstName) + _T(" ");

	if( task.nOutType != SMM_File_Type_NO ) 
		str2wr += _T("out_type=") + AddQuotes( XTLDescr_TrackOutType[ task.nOutType ] ) + _T(" ");

	str2wr += _T("mode=") + AddQuotes( XTLDescr_GroupMode[ task.nTaskType ] );
	str2wr += _T(">");

	HRESULT hr = WriteString(m_hFile, str2wr );

	for( UINT n = 0; n < task.nTrackCount; n++){
		WriteTrackPart(task.tracks[n] );
	}
	
	str2wr = _T("\t </group>");
	hr = WriteString(m_hFile, str2wr);
	return hr;
}

HRESULT CParser::WriteString(HANDLE hFile, CString szText)
{
	szText += _T("\r\n");

	DWORD dwLenght = szText.GetLength() * sizeof(TCHAR);
	DWORD dwLenght1 = 0;

	LPBYTE pBuffer = new BYTE[dwLenght];
	memcpy(pBuffer, szText.GetBuffer(), dwLenght);

	WriteFile(hFile,
			  pBuffer,
			  dwLenght,
			  &dwLenght1,
			  NULL);

	SELF_DELETE_ARR(pBuffer);

	if (dwLenght1 != dwLenght)
		return E_FAIL;
			  
	return S_OK;
}

HRESULT CParser::WriteUnicodeHeader(HANDLE hFile)
{
	DWORD dwLenght = 2;
	DWORD dwLenght1 = 2;
	BYTE header[] = "\xFF\xFE";

	WriteFile(hFile,
			  header,
			  dwLenght,
			  &dwLenght1,
			  NULL);

	if (dwLenght != dwLenght1)
		return E_FAIL;

	return S_OK;
}

CString CParser::ProcessMultiByteEncoding(LPVOID pBuffer, DWORD dwSize)
{
	BYTE * buffer = (LPBYTE)pBuffer;

	// Starting parce source file
	// But first : remove comments from the file!!!
	BOOL OnComment = FALSE;
	for (DWORD i = 0; i<dwSize - 3; i++){
		if ((buffer[i + 0] == '<') &&
			(buffer[i + 1] == '!') &&
			(buffer[i + 2] == '-') &&
			(buffer[i + 3] == '-'))
			OnComment = TRUE;

		if ((buffer[i + 0] == '-') &&
			(buffer[i + 1] == '-') &&
			(buffer[i + 2] == '>')){
				buffer[i + 0] = ' ';
				buffer[i + 1] = ' ';
				buffer[i + 2] = ' ';
				OnComment = FALSE;
			}

		if (OnComment == TRUE)
			buffer[i] = ' ';
	}

	int nStartParam  = -1;
	CString szResult = _T("");
	for (DWORD i = 0; i < dwSize; i++)
	{
		if (buffer[i] == '"')
		{
			if (nStartParam == -1){
				nStartParam = i;
			}
			else
			{
				// Parameter finished. Ok. encode it.
				CString str = PreEncodeMultiByteString(&buffer[nStartParam + 1], i - (nStartParam + 1));

				szResult += '"' + EncodeMultiByteString(str) + '"';
				nStartParam = -1;
			}
		}else{
			if (nStartParam == -1)
				szResult += buffer[i];
		}
	}

	return szResult;
}

CString CParser::PreEncodeMultiByteString(LPBYTE pBuffer, DWORD dwSize)
{
	CString szResult = _T("");
#ifndef _UNICODE
	for (DWORD i = 0; i < dwSize; i++){
		szResult += pBuffer[i];
	}
#else
	TCHAR * pTempBuffer = new TCHAR[(dwSize + 10) * sizeof(TCHAR)];
	memset(pTempBuffer, 0, (dwSize + 10) * sizeof(TCHAR));

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pBuffer, dwSize, pTempBuffer, dwSize + 10);
	szResult = pTempBuffer;

	SELF_DELETE_ARR(pTempBuffer);
#endif
	return szResult;
}

CString CParser::ProcessUnicodeEncoding(LPVOID pBuffer, DWORD dwSize)
{
	wchar_t * buffer = (wchar_t *)pBuffer;
	buffer++;
	dwSize /= sizeof(wchar_t);

	// Starting parce source file
	// But first : remove comments from the file!!!
	BOOL OnComment = FALSE;
	for (DWORD i = 0; i < dwSize - 3; i++)
	{
		if ((buffer[i + 0] == '<') &&
			(buffer[i + 1] == '!') &&
			(buffer[i + 2] == '-') &&
			(buffer[i + 3] == '-') )
		{
			OnComment = TRUE;
		}

		if ((buffer[i + 0] == '-') &&
			(buffer[i + 1] == '-') &&
			(buffer[i + 2] == '>'))
		{
				buffer[i + 0] = ' ';
				buffer[i + 1] = ' ';
				buffer[i + 2] = ' ';
				OnComment = FALSE;
		}

		if (OnComment == TRUE)
			buffer[i] = ' ';
	}

	int nStartParam  = -1;
	CString szResult = _T("");

	for (DWORD i = 0; i < dwSize; i++)
	{
		if (buffer[i] == '"')
		{
			if (nStartParam == -1){
				nStartParam = i;
			}
			else
			{
				// Parameter finished. Ok. encode it.
				CString str = _T("");
				for (DWORD j = nStartParam + 1; j<i; j++)
				{
#ifndef _UNICODE
					WORD wTemp = buffer[j] / 0x1000;
					if (wTemp != 0) {
						str += "?";
						continue;
					}
#endif
					str += buffer[j];
				}

				szResult += '"' + EncodeUnicodeString(str) + '"';
				nStartParam = -1;
			}
		}else{
			if (nStartParam == -1)
				szResult += buffer[i];
		}
	}

	return szResult;
}
SMM_OutputTypes	CParser::Str2FT( CString strFT  )
{
	if( strFT == CString("avi") )
		return SMM_File_Type_AVI;
	else if( strFT == CString("asf") )
		return SMM_File_Type_ASF;
	else if( strFT == CString("mpa") || strFT == CString("mp3") || strFT == CString("mp1"))
		return SMM_File_Type_MPA;
	else if( strFT == CString("mpg_ts") )
		return SMM_File_Type_MPEG2_TS;
	else if( strFT == CString("mpg_ps") )
		return SMM_File_Type_MPEG2_PS;
	else if( strFT == CString("mpg_ves") )
		return SMM_File_Type_MPEG2_VES;
	else if( strFT == CString("wav") )
		return SMM_File_Type_WAV;
	else if (strFT == CString("asf") ||  strFT == CString("wmv") || strFT == CString("wma"))
		return SMM_File_Type_ASF;
	else if (strFT == CString("raw"))
		return SMM_File_Type_RAW;
	else if (strFT == CString("matroska"))
		return SMM_File_Type_MKV;
	else if (strFT == CString("mp4"))
		return SMM_File_Type_MP4;
	else if (strFT == CString("mpg1_sys"))
		return SMM_File_Type_MPEG1_SYS;
	else if (strFT == CString("mpg1_ves"))
		return SMM_File_Type_MPEG1_VES;
	else if (strFT == CString("avc_ves"))
		return SMM_File_Type_MPEG4_AVC;

	return SMM_File_Type_RAW;
}

CString	CParser::AddQuotes	( CString strIn)
{
	CString Out = _T("\"") + strIn  + _T("\"");
	return Out ;
}

BOOL CParser::IsValidXTLFile( CString csFile )
{
	DWORD	bufSize = 60,
			ActualRead = 0;
	BOOL	bResult = FALSE;
	BYTE*	buffer = new BYTE[bufSize];
	int		res;
	
	TCHAR szCurrentDirectory[32767] = {0};
	GetCurrentDirectory(32767, szCurrentDirectory);
	HANDLE hFile = CreateFile( csFile, 
								GENERIC_READ, 
								FILE_SHARE_READ, 
								NULL, 
								OPEN_EXISTING, 
								0, 
								0 );
	if ( hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	memset( buffer, 0, bufSize );
	ReadFile( hFile, buffer, bufSize, &ActualRead, NULL );
	if( (buffer[0] == 0xFF) && (buffer[1] == 0xFE) )
	{
		WCHAR *wBuffer = (WCHAR*) buffer;
		res = wmemcmp( wBuffer+1, L"<timeline>", 10);
	}else
	{
		void *vBuffer = (void*) buffer;
		res = memcmp( vBuffer, (void*)"<timeline>", 10);
	}
	delete [] buffer;
	if( res == 0 )
		bResult = TRUE;
	SetFilePointer( hFile, 0, NULL, FILE_BEGIN );
	CloseHandle( hFile );
	return bResult;
}
void CParser::SetError(ParserErrors error)
{
	ASSERT(m_error == PE_NO_ERRORS);
	m_error = error;
}
ParserErrors CParser::GetLastError()
{
	ParserErrors error = m_error;
	m_error = PE_NO_ERRORS;
	return error;
}
void CParser::GetAbsPath( CString& sName )
{
	if( -1 != sName.Find(_T(':')) || sName.IsEmpty() )
		return;
//if relative path - restore the full path
	if( m_csFileName.IsEmpty() ) //nothing to do in this case
		return;

	TCHAR csDrive[_MAX_DRIVE] = {0};
	TCHAR csDir[_MAX_DIR]={0};
	
	TCHAR csOut[_MAX_PATH]={0};
	
	_tsplitpath(m_csFileName, csDrive, csDir,NULL,NULL);
	_tmakepath(csOut, csDrive, csDir, NULL, NULL);

	TCHAR csFullPath[_MAX_PATH]={0};
	if( !PathCombine(csFullPath, csOut, sName) )
		return;

	sName = csFullPath;
}

HRESULT CParser::GetListOfInputOutputFiles( std::vector<CString> *csInFiles, std::vector<CString> *csOutFiles )
{
	HRESULT hr = S_OK;
	LONG lGroups = 0;
	hr = GetGroupsCount(&lGroups);
	for(int i = 0; i< lGroups; i++)
	{
		SMM_GROUP_TASK task;
		hr = GroupToTask( i, &task );
		if( FAILED(hr) )
			return hr;

		//Add Dest file
		csOutFiles->push_back(task.szDstName);
		//Add index file if exist
		CString index(task.tracks[0].szMPEG2IdxFileName);
		if( !index.IsEmpty() )
			csInFiles->push_back(index);

		//validate all source files
		int nNum = task.tracks[0].nClips;
		if( task.nTaskType != SMM_Task_Type_Joining )
			nNum = 1;
		for( int i = 0; i<nNum; i++ )
			csInFiles->push_back(CString(task.tracks[0].pClips[i].wsfName));
	}
	return hr;
}