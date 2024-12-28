
/////////////////////////////////////////////////////////////////////////////////
//
//	   Copyright (c) 2005 Elecard Ltd.
//	   All rights are reserved.  Reproduction in whole or in part is prohibited
//	   without the written consent of the copyright owner.
//
//	   Elecard Ltd. reserves the right to make changes without
//	   notice at any time. Elecard Ltd. makes no warranty, expressed,
//	   implied or statutory, including but not limited to any implied
//	   warranty of merchantability of fitness for any particular purpose,
//	   or that the use will not infringe any third party patent, copyright
//	   or trademark.
//
//	   Elecard Ltd. must not be liable for any loss or damage arising
//	   from its use.
//
/////////////////////////////////////////////////////////////////////////////////

#if !defined(_PROFILE_PRESET_PARAMETERS_H_)
#define _PROFILE_PRESET_PARAMETERS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Utils.h"
#include "Elements.h"
#include "Managers.h"
#include "DMOWrapper.h"
#include <ModuleConfig\ModuleConfig.h>


class CParamInfo
{
	public:

		typedef std::deque<CComBSTR>		TVValidNames;
		typedef std::deque<CComVariant>		TVValidValues;		

		typedef struct 
		{
			CComVariant		maxValue;
			CComVariant		minValue;
			CComVariant		delta;

		} TSRange;

		CParamInfo();
		CParamInfo(const CParamInfo& pInfo);
		CParamInfo(IParamConfig* pConfig);
		~CParamInfo();

		void			GetDefault(CComVariant& val) const 	{	val = m_Default;	}		
		void			GetReadOnly(BOOL& val) const		{	val = m_bReadOnly;	}
		void			GetVisible(BOOL& val) const			{	val = m_bVisible;	}
		void			SetVisible(BOOL val);

		HRESULT			GetRange(TSRange* pRange) const;
		HRESULT			EnumValidValues(long* pCount, TVValidValues* pValues, TVValidNames* pNames) const ;

		HRESULT			Update(IParamConfig* pConfig);		
		CParamInfo&		operator = (const CParamInfo& info);

		BOOL			Compare(const CParamInfo& info);

		BOOL			Valid() const						{	return m_bValid;	}

		HRESULT			MeaningToValue(const BSTR bsValue, VARIANT* pValue);
		HRESULT			ValueToMeaning(const VARIANT& pValue, BSTR* pbsValue);
		
	protected:		

		BOOL			m_bValid;
		CComVariant		m_Default;				
		BOOL			m_bReadOnly;
		BOOL			m_bVisible;

		TSRange			m_Range;

		TVValidValues	m_ValidValues;
		TVValidNames	m_ValidNames;

		void			Reset();
};

class CParameter
{
	public:

		CParameter();
		CParameter(const CParameter& param);
		CParameter(IParamConfig* pConfig);
		CParameter(LPCTSTR tcsName, REFGUID pGuid, const VARIANT& pValue);
		~CParameter();

		HRESULT		GetValue(VARIANT* pValue) const;
		HRESULT		SetValue(const VARIANT& pValue);

		HRESULT		SetParameterInfo(LPCTSTR tcsrName, REFGUID fGuid);

		BSTR		GetName() const		{	return m_bsName;		}
		GUID		GetParamID() const	{	return m_pParamID;	}		

		HRESULT		UpdateInfo(IParamConfig* pConfig);
		BOOL		Compare(CParameter& param);

		CParameter&	operator = (const CParameter& param);		

		const CParamInfo&	Info() const		{	return m_Info;		}
	
	protected:

		CComBSTR	m_bsName;
		GUID		m_pParamID;
		CComVariant	m_Value;
		CParamInfo	m_Info;
};

class CUserParameter
{
	public:
		
		CUserParameter();
		CUserParameter(const CUserParameter& param);
		~CUserParameter();

		CUserParameter& operator = (const CUserParameter& param);

		LPCTSTR		GetName() const;
		LPCTSTR		GetDescription() const;
		LPCTSTR		GetDataType() const;
		GUID		GetGuid() const;
		HRESULT		GetValue(VARIANT* pValue) const;

		HRESULT		SetParam(LPCTSTR tcsName, const GUID* pGuid = NULL, LPCTSTR tcsValueType = NULL, 
							 LPCTSTR tcsValue = NULL, LPCTSTR tcsDataType = NULL, LPCTSTR tcsDescription = NULL);
		HRESULT		SetParam(LPCTSTR tcsName, const GUID* pGuid = NULL, const VARIANT* pValue = NULL, 
							 LPCTSTR tcsDataType = NULL, LPCTSTR tcsDescription = NULL);

	protected:

		CTBString		m_tcsName;
		CTBString		m_tcsDataType;
		CTBString		m_tcsDescription;
		GUID			m_Guid;
		CComVariant		m_Value;

};

typedef std::list<CParameter>		TLParameters;

class CParameterSet
{
	public:

		CParameterSet(){};
		CParameterSet(const CParameterSet& param);
		CParameterSet(TLParameters& param);
		CParameterSet(IModuleConfig* pConfig);
		~CParameterSet();

		HRESULT	GetValue(REFGUID guid, VARIANT* pValue);
		HRESULT SetValue(REFGUID guid, const VARIANT& pValue);

		HRESULT	AddParameter(IParamConfig* pConfig, const VARIANT& pValue);
		HRESULT	AddParameter(LPCTSTR tcsName, REFGUID pGuid, const VARIANT& pValue);
		HRESULT	SetParameter(LPCTSTR tcsName, REFGUID pGuid, const VARIANT& pValue, BOOL bAddIfNotExist = TRUE);
		HRESULT	SetParameterMeaning(LPCTSTR tcsName, REFGUID pGuid, const BSTR bsValue);
		HRESULT	RemoveParameter(REFGUID pGuid);

		HRESULT UpdateParameters(REFGUID filterGuid, BOOL bExist = TRUE, LPCTSTR tcsFilePath = NULL);
		HRESULT UpdateParameters(IModuleConfig* pConfig, BOOL bExist = TRUE);

		HRESULT	EnumParameters(TLParameters* plist) const;

		CParameterSet&	operator = (CParameterSet& param);
		CParameterSet&	operator = (TLParameters& param);

		CParameter*		FindParam(REFGUID guid);

		BOOL	Valid()	{ return !m_Param.empty(); }

	protected:

		TLParameters	m_Param;

		void			Reset();		
};

class CFilterParam
{
	public:
		
		CFilterParam(const CFilterParam& param);
		CFilterParam(CFilterWrapper& filter);		
		CFilterParam(REFGUID fGuid, LPCTSTR tcsFilterName = NULL);

		~CFilterParam();		

		BOOL	Compare(CFilterParam& filter);

		HRESULT	SetFilterInfo(const GUID* fGuid = NULL, LPCTSTR tcsFilterName = NULL);
		
		void			SetParameters(CParameterSet* pParam)	{ m_pParameters = pParam;	}		
		CParameterSet*	GetParameters()							{ return m_pParameters;		}
		
		BOOL	Valid();

		LPCTSTR	GetName() const	{ return m_Name.data();	}
		REFGUID	GetClsid() const { return m_Guid;		}
		
	protected:

		CParameterSet*	m_pParameters;		
		CTBString		m_Name;
		GUID			m_Guid;
};

struct TSConnectionParam
{
	UINT		srcFilter;
	UINT		dstFilter;
	UINT		srcPin;
	UINT		dstPin;
	GUID		mtGuid;
	
	TSConnectionParam(UINT sFilter, UINT dFilter, UINT sPin, UINT dPin, REFGUID mtype = MEDIATYPE_NULL)
		: srcFilter(sFilter), dstFilter(dFilter), srcPin(sPin), dstPin(dPin), mtGuid(mtype)
	{
	};

	TSConnectionParam(const TSConnectionParam& value)
	{
		srcFilter = value.srcFilter;
		dstFilter = value.dstFilter;
		srcPin = value.srcPin;
		dstPin = value.dstPin;		
		mtGuid = value.mtGuid;
	}

};

class CGraphPreset : public CAutoApartment
{
	public:

		struct TSProfileParam
		{
			TCHAR		comment[MAX_PATH];
			TCHAR		graphURL[MAX_PATH];
			UINT		graphID;
			TCHAR		parentURL[MAX_PATH];
			UINT		parentID;

			TSProfileParam(const TSProfileParam& param)
			{
				_tcscpy(comment, param.comment);
				_tcscpy(graphURL, param.graphURL);
				_tcscpy(parentURL, param.parentURL);
				graphID = param.graphID;
				parentID = param.parentID;
			}

			TSProfileParam()
			{
				_tcscpy(comment, _T(""));
				_tcscpy(graphURL, _T(""));
				_tcscpy(parentURL, _T(""));
				graphID = MAXLONG;
				parentID = MAXLONG;
			}
		};	

		typedef std::list<GUID*>					TLGuids;		
		typedef std::map<UINT, CTBString>			TMProfiles;	
		typedef std::map<UINT, TSProfileParam>		TMProfileValue;		
		typedef std::map<UINT, CFilterParam>		TMFilters;		
		typedef std::list<TSConnectionParam>		TLConnection;
		typedef std::map<const GUID*, CTBString>	TMGUIDString;
		typedef std::map<UINT, CFilterWrapper>		TMConnectFilters;
		typedef std::list<CUserParameter>			TLUserParameter;
		typedef TLUserParameter::iterator			TLIUserParam;

		CGraphPreset();
		CGraphPreset(CGraphPreset& graph);
		CGraphPreset(CBaseGraph& graph);
		
		~CGraphPreset();		

		CGraphPreset&	operator = (CGraphPreset& graph);
		CGraphPreset&	operator = (CBaseGraph& graph);

		void			Reset();

		HRESULT			SetPresetParam(LPCTSTR version);
		HRESULT			SetGraphParam(UINT id, BOOL bUseClock);
		
		HRESULT			AddProfile(UINT profile, LPCTSTR tcsName, LPCTSTR tcsComment = NULL, 
								   LPCTSTR tcsGraphURL = NULL, UINT graphId = MAXLONG, 
								   LPCTSTR tcaParentURL = NULL, UINT parentId = MAXLONG);
		
		LPCTSTR			GetProfileName(UINT profile);
		HRESULT			GetProfileParam(UINT profile, LPTSTR tcsComment = NULL, LPTSTR tcsGraphURL = NULL, 
										UINT* graphId = NULL, LPTSTR tcaParentURL = NULL, UINT* parentId = NULL);

		HRESULT			UpdateProfileParam(UINT profile, LPCTSTR tcsName = NULL, LPCTSTR tcsComment = NULL, LPCTSTR tcsGraphURL = NULL, 
										   UINT graphId = MAXLONG, LPCTSTR tcaParentURL = NULL, UINT parentId = MAXLONG);

		HRESULT			AddFilter(UINT id, REFGUID pGuid, LPCTSTR tcsFilterName = NULL);		
		HRESULT			UpdateFilter(UINT id, GUID* pGuid = NULL, LPCTSTR tcsFilterName = NULL);
		
		HRESULT			AddParameter(UINT profile, UINT filter, LPCTSTR tcsName, REFGUID pGuid, LPCTSTR type, LPCTSTR value);
		HRESULT			AddParameter(UINT profile, UINT filter, LPCTSTR tcsName, REFGUID pGuid, const VARIANT& pValue, BOOL bValidate = FALSE);
		HRESULT			AddPersistData(UINT profile, UINT filter, LPBYTE pData, DWORD dwLen, BOOL bValidate = FALSE);		
		
		HRESULT			AddConnection(UINT srcFilter, UINT dstFilter, UINT srcPin, UINT dstPin, 
									  REFGUID mtGuid = GUID_NULL, BOOL bOverwrite = FALSE, 
									  TLConnection* pConnection = NULL);

		HRESULT			AddFilterParameters(UINT profile, UINT filter, CGraphPreset& preset, UINT dstProfile, UINT dstFilter);
		
		HRESULT			SetUserParameter(LPCTSTR tcsName, const GUID* pGuid = NULL, LPCTSTR tcsValueType = NULL, 
										 LPCTSTR tcsValue = NULL, LPCTSTR tcsDataType = NULL, LPCTSTR tcsDescription = NULL);
		HRESULT			SetProfileUserParameter(UINT profile, LPCTSTR tcsName, const GUID* pGuid = NULL, 
												LPCTSTR tcsValueType = NULL, LPCTSTR tcsValue = NULL, 
												LPCTSTR tcsDataType = NULL, LPCTSTR tcsDescription = NULL);

		HRESULT			GetUserParameter(LPCTSTR tcsName, CUserParameter& param);
		HRESULT			GetProfileUserParameter(UINT profile, LPCTSTR tcsName, CUserParameter& param);

		HRESULT			SetFiltersPath(TMGUIDString& filtersPath);
		HRESULT			UpdateFilterPath(GUID* pGuid, LPCTSTR tcsPath);
		HRESULT			RemoveFilterPath(GUID* pGuid);

		CFilterParam*	GetFilter(UINT id);

		LPCTSTR			GetVersion() { return m_version; }
		HRESULT			GetGraphParam(UINT& id, BOOL& bUseClock);

		UINT			ProfileCount();
		UINT			FilterCount();
		UINT			ConnectionCount();

		HRESULT			EnumProfiles(TMProfiles& plist, TMProfileValue* pValue = NULL);
		HRESULT			EnumFilters(TMFilters& flist);
		HRESULT			EnumConnection(TLConnection& clist, UINT* psrcFilter = NULL, UINT* pdstFilter = NULL);
		HRESULT			EnumParameters(UINT profile, UINT filter, TLParameters& plist);
		HRESULT			EnumFiltersInGraph(TMConnectFilters& flist);
		HRESULT			EnumFiltersPath(TMGUIDString& filtersPath);
		HRESULT			EnumUserParameter(TLUserParameter& ulist);
		HRESULT			EnumProfileUserParameter(UINT profile, TLUserParameter& ulist);

		HRESULT			ProfileCopy(CGraphPreset& preset, UINT profile, BOOL bGraphStructure = TRUE);
		BOOL			ProfileCompare(CGraphPreset& preset, UINT profile, BOOL bGraphStructure = TRUE);
		BOOL			Compare(CGraphPreset& preset);
		
		HRESULT			GetPersistParameters(UINT profile, UINT filter, LPBYTE* pData, DWORD* pdwSize);		

		HRESULT			RemoveProfile(UINT* profile = NULL);
		HRESULT			RemoveFilter(UINT* filter = NULL, BOOL bFromProfile = TRUE);

		HRESULT			BuildGraph(CBaseGraph& graph, UINT* pProfile = NULL, LPCTSTR tcsInFileName = NULL, LPCTSTR tcsOutFileName = NULL);
		HRESULT			ApplyParameters(CBaseGraph& graph, UINT profile, TLGuids* pBlackFilters = NULL);
		HRESULT			ApplyParameters(CFilterWrapper& filter, UINT profile, UINT fid = MAXLONG);
		HRESULT			GetParametersFromFilter(CFilterWrapper& filter, UINT profile, UINT fid = MAXLONG);

		void			SetSecretGUID(const GUID* secretGuid = NULL);

		HRESULT			SetCurrentProfile(UINT profile);
		UINT			GetCurrentProfile() { return m_profile; }		

		HRESULT			GetCurrentValue(UINT filter, REFGUID pGuid, VARIANT* pValue);
		HRESULT			SetCurrentValue(UINT filter, REFGUID pGuid, const VARIANT& pValue);

		HRESULT			GetValue(UINT profile, UINT filter, REFGUID pGuid, VARIANT* pValue);
		HRESULT			SetValue(UINT profile, UINT filter, REFGUID pGuid, const VARIANT& pValue);

		HRESULT			CloseAllConfigInstance();

	protected:

		struct TSBytes
		{
			LPBYTE		pByte;
			DWORD		dwLen;
			
			TSBytes(const LPBYTE pData = NULL, const DWORD dwSize = 0) : pByte(NULL), dwLen(0)
			{
				if(dwSize > 0 && pData)
				{
					pByte = (LPBYTE)malloc(dwSize + 1);
					memcpy(pByte, pData, dwSize);
					dwLen = dwSize;
				}
			}

			TSBytes(const TSBytes& data) : pByte(NULL), dwLen(0)
			{
				data.CopyData(pByte, &dwLen);
			}

			HRESULT CopyData(LPBYTE pData, DWORD* dwSize) const
			{
				if(dwLen > 0 && pByte)
				{
					pData = (LPBYTE)malloc(dwLen + 1);
					memcpy(pData, pByte, dwLen);
					*dwSize = dwLen;
					return S_OK;
				}
				return E_FAIL;
			}

			~TSBytes()
			{
				free(pByte);
			}

		};					

		typedef CComPtr<IModuleConfig>					TModuleConfig;
		typedef std::map<UINT, TSBytes>					TMPersistData;
		typedef std::map<UINT, CParameterSet>			TMParamSet;
		typedef std::map<UINT, TMParamSet>				TMProfileParam;
		typedef std::map<UINT, TMPersistData>			TMProfilePersist;
		typedef std::map<UINT, TModuleConfig>			TMFilterConfig;		
		typedef std::multimap<UINT, CUserParameter>		TMMUserParameter;		
		typedef TMMUserParameter::iterator				TMMIUserParam;

		TCHAR					m_version[MAX_PATH];
		UINT					m_GraphId;
		BOOL					m_bUseClock;

		TMProfiles				m_Profiles;
		TMFilters				m_Filters;
		TMFilterConfig			m_Config;	

		TLUserParameter			m_userParam;
		TMMUserParameter		m_profileUserParam;

		TMProfileValue			m_ProfValue;

		TMProfileParam			m_ProfileParams;
		TMProfilePersist		m_PersistData;

		TLConnection			m_Connection;
		TMConnectFilters		m_ConnectFilters;
		TMGUIDString			m_filtersPath;

		CLSID					m_secretGuid;
		UINT					m_profile;		

		HRESULT			RemoveParameters(TMParamSet* pParams);
		HRESULT			RemovePersistData(TSBytes* pData);
		HRESULT			RemoveFilter(UINT filter);

		UINT			FindFilter(REFGUID filterGuid);
		LPCTSTR			GetFilterPath(REFGUID filterGuid);
		HRESULT			FindFilterInGraph(UINT id, UINT idp, REFGUID mtGuid, PIN_DIRECTION dir, CBaseGraph& graph, CFilterWrapper& filter);		

		HRESULT			GetInterfaceByPath(REFGUID filterGuid, REFGUID iid, LPCTSTR tcsPath, void** pObj);

		HRESULT			AddFilter(UINT id, UINT idp, REFGUID mtGuid, PIN_DIRECTION dir, CBaseGraph& graph, 
								  CFilterWrapper& filter, UINT* pProfile = NULL, LPCTSTR tcsInFileName = NULL);

		HRESULT			AddToFilterSet(TMParamSet* pSet, UINT filter, TLParameters& plist);
		HRESULT			FindDMOFilter(LPCTSTR tcsName, CLSID& clsid, CLSID& category);

		HRESULT			CorrectConnection(TLConnection& src, TLConnection& dest);
		HRESULT			BuildConnection(CBaseGraph& graph, UINT input, TLConnection* connection, 
										UINT* pProfile = NULL, LPCTSTR tcsInFileName = NULL, LPCTSTR tcsOutFileName = NULL);

		HRESULT			GetStreamSize(IStream* pStream, DWORD& dwSize);
		TLIUserParam	FindParameter(LPCTSTR tcsName);
		TMMIUserParam	FindProfileParameter(UINT profile, LPCTSTR tcsName);
};

#endif //_PROFILE_PRESET_PARAMETERS_H_