
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


#if !defined(_ROFILE_H_2D06E85E_3189_462a_BCE0_A329B7F4DB6A__INCLUDED)
#define _PROFILE_H_2D06E85E_3189_462a_BCE0_A329B7F4DB6A__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Utils.h"

using namespace ElUtils;

class CProfile
{
public:

	CProfile(LPCTSTR name, UINT id);
	CProfile(CProfile* profile);
	~CProfile();

	HRESULT		Read(HKEY hRoot, LPCTSTR Key = NULL);
	HRESULT		Save(HKEY hRoot, LPCTSTR Key = NULL);

	void		SetName(LPCTSTR name);
	LPCTSTR		GetName();
	UINT		GetID();
	
	HRESULT		GetValue(UINT index, CComVariant* value);
	HRESULT		SetValue(UINT index, CComVariant& value);

	BOOL		Compare(UINT index, CComVariant& value);
	BOOL		Compare(CProfile& profile);

	CProfile&	operator = (CProfile& profile);

	HRESULT		AddParameter(UINT index, CComVariant& Value, LPCTSTR key_name, BOOL bUpdate = FALSE);
	HRESULT		RemoveParameter(UINT index);
	HRESULT		ClearAllParameters();
	
	HRESULT		SetAllDefault();
	HRESULT		SetDefault(UINT index);
	HRESULT		GetDefault(UINT index, CComVariant& value);

	HRESULT		GetKeyName(UINT index, LPTSTR key_name);
	HRESULT		SetKeyName(UINT index, LPCTSTR key_name);

	UINT		Count();
	HRESULT		GetFirst(UINT* index);
	HRESULT		GetNext(UINT* index);

private:
	
	typedef std::map<UINT, TCHAR*>		TMKeyName;	
	typedef std::map<UINT, CComVariant>	TMParameters;
	typedef TMParameters::iterator		TIMParameters;

	TMParameters	m_Param;
	TMParameters	m_Default;
	TMKeyName		m_KeyName;

protected:

	CTBString		m_Name;
	UINT			m_Id;

	TIMParameters	m_iterator;
};


class CProfileGroup
{
public:

	CProfileGroup(){};
	CProfileGroup(CProfileGroup& profile);
	~CProfileGroup();

	CProfile*	Current(UINT category);
	CProfile*	GetProfile(UINT category, UINT id);
	HRESULT		SetCurrent(UINT category, UINT id);	

	CProfile*	AddProfile(UINT category, UINT id, LPCTSTR name, BOOL bUpdate = FALSE);
	CProfile*	AddProfile(UINT category, CProfile* profile, BOOL bUpdate = FALSE);
	HRESULT		RemoveProfile(UINT category, UINT id);

	HRESULT		ClearAllProfiles();

	UINT		Count();
	CProfile*	GetFirst(UINT* category = NULL);
	CProfile*	GetFirst(UINT category);
	CProfile*	GetNext(UINT* category = NULL);	

	CProfileGroup&	operator = (CProfileGroup& profile);

private:

	typedef std::multimap<UINT, CProfile*>	TMMProfiles;
	typedef TMMProfiles::iterator			TIMMProfiles;
	typedef std::map<UINT, TIMMProfiles>	TMCurrent;

	TMMProfiles		m_Profiles;
	TMCurrent		m_Current;

protected:
	
	TMMProfiles::_Pairii	m_category;
	TIMMProfiles			m_iterator;
};

#endif // _PROFILE_H_2D06E85E_3189_462a_BCE0_A329B7F4DB6A__INCLUDED