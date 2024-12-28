
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

#if !defined(_XML_PROFILE_PARSER_H_)
#define _XML_PROFILE_PARSER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <msxml.h>

#include "Utils.h"

#include "GraphPreset.h"

typedef std::map<CComBSTR, CComVariant>		TMValues;

HRESULT	WINAPI GetValue(TMValues& valueList, LPCTSTR name, CComVariant* pValue);
HRESULT	WINAPI WriteToFile(HANDLE hFile, LPCTSTR tcsValue);

DECLARE_INTERFACE(ITagAttribute)
{
	STDMETHOD(OnTagAttributes)(LPCTSTR itemName, CGraphPreset* pPreset, TMValues& valueList) = 0;
	STDMETHOD(SaveTagAttributes)(LPCTSTR itemName, CGraphPreset* pPreset, HANDLE hFile) = 0;
};

class CXMLParser
{
	public:		

		CXMLParser(LPCTSTR tcsMainWord, BOOL bCoInit = TRUE);
		~CXMLParser()
		{
			m_pXMLDom.Release();
			if(m_bCoInit)
				CoUninitialize();
		};

		virtual HRESULT		Load(LPCTSTR tcsXMLFile);
		virtual HRESULT		LoadXML(BSTR bsXML);

		LPCTSTR		GetLastXMLErrorMessage() { return m_Error.c_str(); }

		HRESULT		SubscribeOnTag(ITagAttribute* pTag);
		HRESULT		UnSubscribeOnTag(ITagAttribute* pTag);

		void		SetMainWord(LPCTSTR tcsMain) { m_MainWord = tcsMain; }

	protected:	

		typedef std::list<ITagAttribute*>	TLTagHandler;

		TLTagHandler	m_TagHandler;
		CTBString		m_Error;
		CTBString		m_MainWord;
		BOOL			m_bCoInit;

		CComPtr<IXMLDOMDocument>	m_pXMLDom;

		virtual HRESULT	ParseXML();		
		virtual HRESULT	EnumNodes(LPCTSTR itemName, IXMLDOMNode* pNode, TMValues& valueList, UINT* plParam1, UINT* plParam2);
		virtual HRESULT	OnTagAttr(LPCTSTR itemName, TMValues& valueList, UINT* plParam1, UINT* plParam2);

		HRESULT		GetLastXMLError(IXMLDOMDocument* pDom);
		HRESULT		SpecialSymbolConvert(LPCTSTR tcsText, CTBString& tsText);

};

class CXMLPresetParser : public CXMLParser
{
	public:		

		CXMLPresetParser(BOOL bCoInit = TRUE);
		~CXMLPresetParser()
		{
			m_pXMLDom.Release();
			if(m_bCoInit)
				CoUninitialize();
		};

		virtual HRESULT		Load(LPCTSTR tcsXMLFile, CGraphPreset* pPreset);
		virtual HRESULT		LoadXML(BSTR bsXML, CGraphPreset* pPreset);

		virtual HRESULT		Save(LPCTSTR tcsXMLFile, CGraphPreset* pPreset, UINT profile = MAXLONG);

	protected:	
		
		virtual HRESULT	ParseXML(CGraphPreset* pPreset);		
		virtual HRESULT	SavePreset(HANDLE hFile, CGraphPreset* pPreset, UINT profile = MAXLONG);
		virtual HRESULT SaveUserData(HANDLE hFile, CUserParameter* pUser);

		virtual HRESULT	EnumNodes(LPCTSTR itemName, CGraphPreset* pPreset, IXMLDOMNode* pNode, TMValues& valueList, 
								  UINT* plParam1, UINT* plParam2);
		virtual HRESULT	OnTagAttr(LPCTSTR itemName, CGraphPreset* pPreset, TMValues& valueList, 
								  UINT* plParam1, UINT* plParam2);

		HRESULT		TagSaveHandler(LPCTSTR itemName, CGraphPreset* pPreset, HANDLE hFile);		
};


#endif // _XML_PROFILE_PARSER_H_