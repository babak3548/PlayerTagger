
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
#if !defined(_BASEENGIN_H__5FA3A8DA_67B7_4195_B323_4F13EDF865A6__INCLUDED_)
#define _BASEENGIN_H__5FA3A8DA_67B7_4195_B323_4F13EDF865A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExMsg.h"
#include "Managers.h"
#include "SInfo.h"

#define		UNKNOWN_FILTER		MAXLONG

using namespace ElUtils;

DECLARE_INTERFACE(IUpdateParameters)
{
	STDMETHOD(LoadToFilter)(LONG fIndex, CFilterWrapper& filter, CStreamInfo* pInfo = NULL) = 0;
};

typedef enum _tagTEUpdateMode
{
	update_AfterGraphBuild	= 0,
	update_BeforeAdd		= 1,
	update_AfterAdd			= 2,
	update_BeforeConnection = 3,
	update_AfterConnection  = 4

} TEUpdateMode;

class CEncodeBase  :	public	CGraphManager, 
						private	CAutoApartment 
{
	public:	

		struct Filter_Info
		{
			CTBString		name;
			CTBString		file_name;
			const GUID*		guid;
			const GUID*		type;
			TEUpdateMode	update;		
			
			Filter_Info(LPCTSTR fn, const GUID* pg, const GUID* ftype = &GUID_NULL, 
						LPCTSTR fname = _T(""), TEUpdateMode upmode = update_AfterGraphBuild) 
				: name(fn), guid(pg), type(ftype), file_name(fname), update(upmode ) {};
			
			const GUID&		Guid()		{ return *guid;			}
			LPCTSTR			Name()		{ return name.data();	}
			REFGUID			Type()		{ return *type;			}
			LPCTSTR			FileName()	{ return _tcslen(file_name.data()) ? file_name.data() : NULL; }	
			TEUpdateMode	UpdateMode(){ return update;		}
		};

		CEncodeBase();
		virtual ~CEncodeBase();

		virtual void	Reset();
		
		IVideoWindow*	GetVideoWindow(BOOL bUpdate = FALSE);
		
		virtual HRESULT	RemovePreview();
		virtual HRESULT	RemoveEncodeBrunch() = 0;	
			
		virtual HRESULT	BuildPreview() = 0;	
		virtual HRESULT	BuildToSplitter() = 0;
		virtual HRESULT BuildEncodeGraph() = 0;

		virtual HRESULT	UpdateParameters() = 0;

		HRESULT			SelectFilter(const GUID* type, long index);
		long			Selected(const GUID* type);	
		BOOL			FilterExist(long index);

		Filter_Info&	FilterInfo(long index);
		BOOL			IsFilterInfoValid(long index);
		HRESULT			InsertFilterInfo(long index, const GUID* type, LPCTSTR name, const GUID* guid, 
										 LPCTSTR tcsFileName = NULL, TEUpdateMode update = update_AfterGraphBuild);
		void			EraseFilterInfo(long index);
		
		HRESULT			SetUpdateInterface(IUpdateParameters* pInterface);

		HRESULT			ChangeSecretGUID(const GUID* pGuid = NULL);
		
	protected:
		
		typedef std::map<long, CFilterWrapper>	TMFilters;
		typedef TMFilters::iterator				TIFilter;
		
		typedef std::map<const GUID*, long>		TMSelectedFilter;
		typedef TMSelectedFilter::iterator		TISelectedFilter;
		
		typedef std::map<long, Filter_Info>		TMFiltersInfo;
		typedef TMFiltersInfo::iterator			TIFilterInfo;	
				
		class CEnumFiltersInGroup
		{
			public: 
				CEnumFiltersInGroup(TMFiltersInfo* filterInfo, const GUID* type);
				~CEnumFiltersInGroup();
				
				long	Next();
				void	Reset();
				
			protected:
				
				const GUID*		m_Type;
				TMFiltersInfo*	m_pFilterInfo;
				TIFilterInfo	m_ItFGroup;
		};

		TMFilters				m_Filter;	
		TMSelectedFilter		m_SelectedFilter;
		TMFiltersInfo			m_FilterInfo;

		CLSID					m_secretGuid;

		IUpdateParameters*		m_Update;
		CComPtr<IVideoWindow>	m_pVideoWindow;

		CFilterWrapper&		Filter(long index);
		CFilterWrapper&		Filter(const GUID* type);
		void				EraseFilter(long index);
		long				Index(CFilterWrapper& filter);

		long				GetFilterGroupCount(const GUID* type);
		
		virtual HRESULT		AddFilter(long index, CFilterWrapper& filter);

		virtual HRESULT		CreateFilter(long index, CFilterWrapper& filter);
		virtual HRESULT		CreateFilter(long index, bool bCriticalFilter = true);
		HRESULT				CreateFilter(const CLSID& clsid, CFilterWrapper& filter, LPCTSTR pszFilterName, 
										 bool bCriticalFilter = true, LPCTSTR tcsFileName = NULL);
		
		virtual HRESULT		BuildEncodeToMuxer(CFilterWrapper& splitter, CPinWrapper& out_pin) = 0;	
		virtual HRESULT		BuildDump(CPinWrapper& in_pin) = 0;

		TISelectedFilter	FindSelected(const GUID* type);		
};

class CEncodeManager  :	public	CEncodeBase
{
	public:	
		
		CEncodeManager();
		~CEncodeManager();
		
		virtual void	Reset();
		
		virtual HRESULT	RemoveEncodeBrunch();	
		
		virtual HRESULT	BuildToSplitter();	
		virtual HRESULT BuildEncodeGraph();	
		
		virtual BOOL	IsPreviewBuild();
		
		void			EnablePreview(BOOL bSet = TRUE);
		
		virtual HRESULT	UpdateParameters();	

		virtual HRESULT	ConnectOutPinWithFilter(CPinWrapper& OutPin, CFilterWrapper& Filter, BOOL bIntelligent = FALSE);
		virtual HRESULT	ConnectFiltersDirectly(CFilterWrapper& OutFilter, CFilterWrapper& InFilter, BOOL bIntelligent = FALSE);
		
	protected:

		class CBranchInfo
		{
			public:

				typedef std::map<long, CFilterWrapper>	TMFilters;
				
				CBranchInfo(CPinWrapper& pin);
				CBranchInfo(const CBranchInfo& brunch);
				~CBranchInfo();

				CPinWrapper&	GetInfoPin()	{ return m_Info.GetInfoPin();	}
				long			GetInfoType()	{ return m_Info.GetType();		}
				BOOL			IsMain() const	{ return m_Info.IsMain();		}
				CStreamInfo*	Info()			{ return &m_Info; }

				HRESULT			InfoPin(CPinWrapper& pin) const;

				HRESULT			AddFilter(long index, CFilterWrapper filter);
				CFilterWrapper&	Filter(long index);
				UINT			GetFiltersList(TMFilters& flist) const;

				void			Reset();

				BOOL			InfoValid()	{ return m_Info.Valid(); }

			protected:			
				
				TMFilters		m_Filters;
				CStreamInfo		m_Info;
		};
		
		typedef std::list<CBranchInfo>	TLBranches;
		
		TLBranches		m_Branches;
		BOOL			m_bEnablePreview;
		
		virtual HRESULT	CreateFilters();

		virtual HRESULT	AddFilter(long index, CFilterWrapper& filter, CBranchInfo* pBranch = NULL);
		virtual HRESULT	LoadToFilter(UINT index, CBranchInfo* pBranch = NULL);
		virtual HRESULT	LoadToFilter(UINT index, CFilterWrapper& filter, CStreamInfo* pInfo = NULL);		
		
		HRESULT			CreateFilterGroup(const GUID* type, bool bCriticalGroup = true);
		HRESULT			ConnectOutPinWithFilterGroup(CPinWrapper& out_pin, const GUID* type, 
													 long& index, CFilterWrapper& filter);

		HRESULT			ConnectFilter(CPinWrapper& output, CMediaType& mt, CFilterWrapper* pFilter);
		
		virtual HRESULT	BuildEncoderPart(CBranchInfo* info, CPinWrapper& out_pin);
		
		virtual HRESULT InsertSplitter(CPinWrapper& pin);
		virtual HRESULT	InsertDecoder(CBranchInfo* info, CPinWrapper& out_pin);
		virtual HRESULT	UpdateEncodeData() { return S_OK;}		
		
		virtual HRESULT	BuildEncodeToMuxer(CFilterWrapper& splitter, CPinWrapper& out_pin);	
		virtual HRESULT	BuildDump(CPinWrapper& in_pin);	
		
		virtual BOOL	CheckStreamToBuild(CBranchInfo* info, UINT video, UINT audio) { return TRUE; }
};

#endif // !defined(_BASEENGIN_H__5FA3A8DA_67B7_4195_B323_4F13EDF865A6__INCLUDED_)