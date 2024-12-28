#include "stdafx.h"
#include "SMM_ProfileParser.h"
#include <mpgindexator_i.c> ///RAA: CLSID_MpgFileIndexator


ProfileParser& ProfileParser::Instance(CString profile)
{
	static ProfileParser parser(profile);

	
	return parser;
}
ProfileParser::ProfileParser(CString profile) : m_iPos(0), m_profile(profile)
{ 
	CString gs;     

	gs = ConvertGUID((GUID &)ElMux_FilterID);
	m_gsmap[gs] = L"MainConcept MPEG-2 Video Encoder";
	gs = ConvertGUID((GUID &)CLSID_EM2VE);
	m_gsmap[gs] = L"MainConcept MPEG-2 Video Encoder";

	gs = ConvertGUID((GUID &)CLSID_EMPGDMX);
	m_gsmap[gs] = L"Elecard MPEG Demultiplexer";
	gs = ConvertGUID((GUID &)CLSID_EMPEGMUXER);
	m_gsmap[gs] = L"Elecard Multiplexer";
	gs = ConvertGUID((GUID &)CLSID_EM2VE_HD);
	m_gsmap[gs] = L"Elecard MPEG-2 Video Encoder";
	gs = ConvertGUID((GUID &)CLSID_EM2VD);
	m_gsmap[gs] = L"Elecard MPEG-2 Video Decoder";
	gs = ConvertGUID((GUID &)CLSID_MIxReader);
	m_gsmap[gs] = L"Elecard MIxReader Class";
	gs = ConvertGUID((GUID &)CLSID_MpgFileIndexator);
	m_gsmap[gs] = L"Elecard MpgFileIndexator Class";

	gs = ConvertGUID((GUID &)CLSID_AVCEncoder_HD);
	m_gsmap[gs] = L"Elecard AVC Encoder HD";
	gs = ConvertGUID((GUID &)CLSID_EAVCDEC);
	m_gsmap[gs] = L"Elecard AVC Decoder";

	gs = ConvertGUID((GUID &)CLSID_EMP4Demultiplexer);
	m_gsmap[gs] = L"Elecard MP4 Demultiplexer";
	gs = ConvertGUID((GUID &)CLSID_MP4MUX);
	m_gsmap[gs] = L"Elecard MP4 Multiplexer";


	gs = ConvertGUID((GUID &)CLSID_SMM_MP4_DEMUXER);
	m_gsmap[gs] = L"SolveigMM MP4 Demultiplexer";

	gs = ConvertGUID((GUID &)CLSID_SMM_MP4_MUXER);
	m_gsmap[gs] = L"SolveigMM MP4 Multiplexer";


	//m_profile = _T("enc<type:AVC;resolution:sd>_EL__dec<type:AVC;resolution:sd>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM");
	//m_profile = _T("enc<type:AVC>_EL__dec<type:AVC>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM");
	//tResolution resolution = GetResolutionType(Id_Decoder,vesAVC);
	//int i = 0;
}

ProfileParser::~ProfileParser()
{ 
} 

ProfileParser::tResolution ProfileParser::GetResolutionType(fId filterID, tVES codec)
{
	m_iPos = 0;
	if (!QueryFilterMatch(filterID, prmVES, codec))
		return rUnknown;
	FilterParamMap& params = GetFilterParams( );
	long value = GetParam(params,prmRESOLUTION);
	if (value != -1 && value < rUnknown)
		return (tResolution)value;
	return rHD;	// this is default if no specified

}
CString ProfileParser::GetFltrSlntPath( CString RegtoCmpnts, GUID FltGuid )
{
	CString out_pth;
	if (-1 == RegtoCmpnts.Find(_T("Components"),0)){
		return out_pth;
	}

	if( -1 == RegtoCmpnts.Find(_T("Components\\"),0)){
		RegtoCmpnts += "\\";
	}

	LPOLESTR str;
	HKEY     hKey;
	StringFromCLSID(FltGuid,&str);
	CString fltr_gd =str ;
	RegtoCmpnts += fltr_gd;

	TCHAR ch[MAX_PATH];
	ZeroMemory( ch,sizeof(ch) );
	LONG lval = RegOpenKeyEx( HKEY_CLASSES_ROOT, RegtoCmpnts.AllocSysString(), 0, KEY_READ,&hKey);
	if( ERROR_SUCCESS == lval )
	{
		DWORD dwDataSize = MAX_PATH;
		DWORD dwType = REG_SZ;
		RegQueryValueEx(hKey, L"Path", 0, &dwType, (LPBYTE)ch, &dwDataSize);
		RegCloseKey(hKey);
	}
	out_pth = ch;

	return out_pth;
}

CString ProfileParser::GetFilterName(GUID &g)
{
	CString r;

	CString gs;

	gs = ConvertGUID(g);

	m_gsmap.Lookup(gs, r);

	return r;
}

//
// lookup for all profile fId filters, having specified filter<fParam> tip.
//

ProfileParser::ResultList& ProfileParser::QueryFilters ( fId filter, fParam prm )
{
	static ResultList list;

	list.RemoveAll();

	long t;

	m_iPos = 0;

	while( (t = QueryFilterValueType(filter, prm)) != -1 )
	{
		list.AddTail(t);
	}

	return list;
}

//
// get fId filter GUID, using tip fParam prm = value
// TODO: we need to lookup using several tips (for i.e. type=avc&version=2)
//

GUID ProfileParser::GetFilterCLSID( fId filter, fParam prm, long value )
{
	GUID r = GUID_NULL;

	CodecDeveloper codec_developer = GetDeveloperName( filter, prm, value );

	if (  codec_developer == CodecDeveloper_Mainconcept_0)
	{
		return MC_GetFilterCLSID(filter, prm, value );
	}
	else if(  codec_developer == CodecDeveloper_Elecard_0)
	{
		return EL_GetFilterCLSID(filter, prm, value );
	}
	else if (codec_developer == CodecDeveloper_SolveigMM_0)
	{
		return SM_GetFilterCLSID(filter,prm,value);
	}

	return r;
}



long ProfileParser::QueryFilterValueType( fId filter, fParam prm )
{
	if (m_profile.IsEmpty())
	{
		return -1;
	}

	m_iPos = FindNextStartPos( filter );

	if (m_iPos == -1)
	{
		return -1;
	}

	FilterParamMap& pm = GetFilterParams();

	return GetParam( pm, prm );
}

BOOL ProfileParser::QueryFilterMatch( fId filter, fParam prm, long value )
{
	m_iPos = 0;

	long t;

	while ((t = QueryFilterValueType(filter, prm)) != -1)
	{
		if (t == value)
		{
			return TRUE;  
		}
	}

	return FALSE;
}

CodecDeveloper ProfileParser::GetDeveloperName( fId filter, fParam prm, long value )
{
	if (m_profile.IsEmpty())
	{
		return CodecDeveloper_Not_Specifyied;
	}

	CString csFilterID = FormatFilterName( filter );

	if (csFilterID.IsEmpty())
	{
		return CodecDeveloper_Not_Specifyied;
	}

	m_iPos = 0;

	if (!QueryFilterMatch(filter, prm, value))
	{
	   return CodecDeveloper_Not_Specifyied;
	}

	int nPos  = m_iPos;
	int nPos1 = m_profile.Find( L"_", nPos ) + 1;
	int nPos2 = m_profile.Find( L"__", nPos );

	// in case we check last element
	if( nPos2 == -1 )
		nPos2 = m_profile.GetLength();

	CString cdc_developer = m_profile.Mid( nPos1 , nPos2 - nPos1);

	CodecDeveloper cdc_dvlpr = CodecDeveloper_Not_Specifyied;

	if( cdc_developer == L"EL" )
		cdc_dvlpr = CodecDeveloper_Elecard_0;
	else if( cdc_developer == L"MC" )
		cdc_dvlpr = CodecDeveloper_Mainconcept_0;
	else if (cdc_developer == L"SM" )
		cdc_dvlpr = CodecDeveloper_SolveigMM_0;

	return cdc_dvlpr;
}

int ProfileParser::FindNextStartPos( fId filter )
{
	CString csFilterID = FormatFilterName( filter );

	if (csFilterID.IsEmpty())
	{
		return -1;
	}

	int nFltPos = m_profile.Find( csFilterID, m_iPos );

	if (nFltPos != -1)
	{
		return (nFltPos + csFilterID.GetLength());
	}

	return nFltPos;
}

CString ProfileParser::GetFilterParamSpec()
{
	int iStop = m_profile.Find(L"_", m_iPos);

	if (iStop < 0)
		return L"";

	return m_profile.Mid(m_iPos, iStop - m_iPos);
}

ProfileParser::FilterParamMap& ProfileParser::GetFilterParams( )
{
	static FilterParamMap pm;

	pm.RemoveAll();

	CString params = GetFilterParamSpec();

	if (params.IsEmpty())
	{
		return pm;
	}

	int curPos = 0;

	CString res;

	do
	{
		res = params.Tokenize(L"<;>", curPos);

		AddFilterParam( res, pm );
	}
	while (!res.IsEmpty());

	return pm;
}

void ProfileParser::AddFilterParam( CString str, FilterParamMap &p )
{
	int nPos = str.Find(L":", 0);

	if (nPos != -1)
	{
		CString key = str.Left(nPos);

		CString val = str.Right(str.GetLength() - nPos - 1);

		p[key] = val;
	}
}

long ProfileParser::GetParam( FilterParamMap &p, fParam prm )
{
	long x = -1;

	CString key;

	switch (prm)
	{
	case prmVES: case prmCONTAINER:
		key = L"type";
		break;
	case prmRESOLUTION:
		key = L"resolution";
		break;
	case prmVERSION:
		key = L"ver";
		break;
	};

	CString value;

	BOOL bRes = p.Lookup( key, value );

	if (bRes)
	{
		switch(prm)
		{
		case prmVES:
			if (!value.CompareNoCase(L"mpeg2"))
			{
				x = vesMPEG2;
			}
			else if (!value.CompareNoCase(L"avc"))
			{
				x = vesAVC;
			}
			break;
		case prmCONTAINER:
			if (!value.CompareNoCase(L"mpeg2"))
			{
				x = cMPEG2;
			}
			else if (!value.CompareNoCase(L"mp4"))
			{
				x = cMP4;
			}
			else if (!value.CompareNoCase(L"mkv"))
			{
				x = cMKV;
			}
			else if (!value.CompareNoCase(L"avi"))
			{
				x = cAVI;
			}
			break;
		case prmRESOLUTION:
			if (!value.CompareNoCase(L"sd"))
			{
				x = rSD;
			}
			else if (!value.CompareNoCase(L"cif"))
			{
				x = rCIF;
			}
			else if (!value.CompareNoCase(L"hd"))
			{
				x = rHD;
			}
			break;
		case prmVERSION:
			if (!value.CompareNoCase(L"v0"))
			{
				x = v0;
			}
			else if (!value.CompareNoCase(L"v1"))
			{
				x = v1;
			}
			else if (!value.CompareNoCase(L"v2"))
			{
				x = v2;
			}
			break;
		};
	}

	return x;
}

CString ProfileParser::FormatFilterName( fId filter )
{
	CString csFilterID = L"";

	switch( filter )
	{
	case Id_Demuxer:
		csFilterID = L"dmx";
		break;
	case Id_Muxer:
		csFilterID = L"mux";
		break;
	case Id_Decoder:
		csFilterID = L"dec";
		break;
	case Id_Encoder:
		csFilterID = L"enc";
		break;
	case Id_IndexReader:
		csFilterID = L"ixr";
		break;
	case Id_Indexator:
		csFilterID = L"ixw";
		break;
	}

	return csFilterID;
}

GUID ProfileParser::EL_GetFilterCLSID( fId filter, fParam prm, long value )
{
	GUID r = GUID_NULL;

	switch(filter)
	{
	case Id_Demuxer: case Id_Muxer:

		if (prm == prmCONTAINER)
		{
			switch(value)
			{
			case cMPEG2:
				if (filter == Id_Demuxer)
				{
					r = CLSID_EMPGDMX;
				}
				else
				{
					r = CLSID_EMPEGMUXER;
				}
				break;
			case cMP4:
				if (filter == Id_Demuxer)
				{
					r = CLSID_EMP4Demultiplexer;
				}
				else
				{
					r = CLSID_MP4MUX;
				}
				break;
			}
		}
		break;

	case Id_Encoder: case Id_Decoder:

		if (prm == prmVES)
		{
			switch(value)
			{
			case vesMPEG2:
				if (filter == Id_Decoder)
				{
					r = CLSID_EM2VD;
				}
				else
				{
					r = CLSID_EM2VE_HD;
				}
				break;
			case vesAVC:
				{
					
					if (filter == Id_Decoder)
					{
						tResolution resolution = GetResolutionType(Id_Decoder,vesAVC);
						if (resolution == rHD)					
							r = CLSID_EAVCDEC;
						else if (resolution == rSD)
							r = CLSID_EAVCDEC_SD;
					}
					else
					{
						tResolution resolution = GetResolutionType(Id_Decoder,vesAVC);
						if (resolution == rHD)					
							r = CLSID_AVCEncoder_HD;
						else if (resolution == rSD)
							r = CLSID_AVCEncoder_SD;
					}
					
				}
				break;
			}
		}
		break;

	case Id_IndexReader: case Id_Indexator:

		if (prm == prmCONTAINER)
		{
			switch(value)
			{
			case cMPEG2:
				if (filter == Id_IndexReader)
				{
					r = CLSID_MIxReader;
				}
				else
				{
					r = CLSID_MpgFileIndexator;
				}
				break;
			}
		}

		break;
	}

	return r;
}

GUID ProfileParser::MC_GetFilterCLSID( fId filter, fParam prm, long value )
{
	GUID r = GUID_NULL;

	switch(filter)
	{
	case Id_Demuxer: case Id_Muxer:

		if (prm == prmCONTAINER)
		{
			switch(value)
			{
			case cMPEG2:
				if (filter == Id_Demuxer)
				{
					r = CLSID_EMPGDMX;
				}
				else
				{
					r = ElMux_FilterID;
				}
				break;
			}
		}
		break;

	case Id_Encoder: case Id_Decoder:

		if (prm == prmVES)
		{
			switch(value)
			{
			case vesMPEG2:
				if (filter == Id_Decoder)
				{
					r = CLSID_EM2VD;
				}
				else
				{
					r = CLSID_EM2VE;
				}
				break;
			}
		}
		break;

	case Id_IndexReader: case Id_Indexator:

		if (prm == prmCONTAINER)
		{
			switch(value)
			{
			case cMPEG2:
				if (filter == Id_IndexReader)
				{
					r = CLSID_MIxReader;
				}
				else
				{
					r = CLSID_MpgFileIndexator;
				}
				break;
			}
		}

		break;
	}

	return r;
}

GUID ProfileParser::SM_GetFilterCLSID( fId filter, fParam prm, long value )
{
	GUID r = GUID_NULL;

	switch(filter)
	{
	case Id_Demuxer: 
		if (prm == prmCONTAINER)
		{
			switch(value)
			{
				case cMP4:
				r = CLSID_SMM_MP4_DEMUXER;
				break;
			}
		}
		break;
	case Id_Muxer:
		if (prm == prmCONTAINER)
		{
			switch(value)
			{
				case cMP4:
				r = CLSID_SMM_MP4_MUXER;
				break;
			}
		}
		break;
	}
	return r;
}

CString ProfileParser::ConvertGUID(GUID &g)
{
	HRESULT hr;

	LPOLESTR ppsz;

	hr = StringFromCLSID(g, &ppsz);

	if (S_OK == hr)
	{
		CString ret(ppsz);

		if (ppsz)
		{
			CoTaskMemFree(ppsz);
		}

		return ret;
	}      

	return CString(L"");
}