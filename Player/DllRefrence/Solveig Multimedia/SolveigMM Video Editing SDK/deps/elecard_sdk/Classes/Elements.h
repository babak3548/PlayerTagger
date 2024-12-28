
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


#ifndef _BASE_ELEMENTS_
#define _BASE_ELEMENTS_

#include "Utils.h"
#include "Managers.h"

#define		BOOL_NON		2

#define		RELEASE_POINT(p) if(p){ delete p; p = NULL; }

typedef enum _tagTEBaseEvent
{
	event_None			=	0,
	event_Connect		=	0x1000,
	event_Disconnect	=	0x1001,
	event_Add			=	0x1002,
	event_Remove		=	0x1003

} TEBaseEvent;

typedef enum _tagTEPinDirection
{
	PDIR_INPUT		= 0,
	PDIR_OUTPUT		= PDIR_INPUT + 1,
	PINDIR_ALL		= PDIR_OUTPUT + 1
	
} DIRECTION_PIN;

class CBaseElement
{
	friend class CPinWrapper;
	public:

		typedef enum
		{
			elUnknown = 0,
			elPin,
			elFilter,
			elChain,
			elNone
			
		} ElType;

		CBaseElement(LPCTSTR tcsName = NULL, ElType elType = elUnknown, REFGUID Category = GUID_NULL);

		virtual HRESULT ChangeParam(LPCTSTR tcsName = NULL, ElType elType = elUnknown, REFGUID Category = GUID_NULL);
		
		virtual HRESULT	Connect(CPinWrapper& pin, CMediaType* pmt = NULL);
		virtual HRESULT	Disconnect();
		virtual HRESULT	Remove();

		HRESULT SetParent(CBaseElement* pParent);		
		HRESULT	SetEvent(DWORD dwAction, LPARAM lParam = 0)
		{
			if(m_pParent)
				return m_pParent->OnEvent(this, dwAction, lParam);
			return S_OK;
		}

		virtual HRESULT OnEvent(CBaseElement* pElement, DWORD dwAction = event_None, LPARAM lParam = 0) { return S_OK; }

		LPCTSTR	Name() const		{ return m_tcsName.data(); }
		ElType	Type()	const		{ return m_elType; }
		REFGUID	Category() const 	{ return m_Category; }

	protected:
		CBaseElement*	m_pParent;

		CTBString		m_tcsName;
		GUID			m_Category;
		ElType			m_elType;
};

template <typename TNInterface, typename TNInfo>
class CElementImpl 
{
	public:

		CElementImpl(TNInterface* pInterface = NULL) 
			: m_pInterface(pInterface)
		{
			ZeroMemory(&m_Info, sizeof(TNInfo));
			UpdateInfo();
		};

		virtual operator TNInterface*()	const
		{
			return	m_pInterface;
		}
		
		TNInterface* operator->() const
		{
			ATLASSERT(m_pInterface != NULL);
			return (TNInterface*)m_pInterface;
		}

		BOOL		operator==(TNInterface* pInterface)
		{
			ATLASSERT(m_pInterface != NULL);
			return m_pInterface == pInterface;
		}

		virtual BOOL Valid() const
		{
			return !!m_pInterface;
		}

		virtual const TNInfo& Info()	const
		{
			return	m_Info;
		}

		virtual HRESULT UpdateInfo() { return S_OK; }

		virtual void Release() 
		{ 
			m_pInterface.Release(); 
		}

		template <class Q>
		HRESULT QueryInterface(Q** pp) const
		{
			return m_pInterface.QueryInterface(pp);
		}

	protected:

		mutable CComPtr<TNInterface>	m_pInterface;
		mutable TNInfo					m_Info;
};

class CPinWrapper :	public CBaseElement,
					public CElementImpl<IPin, PIN_INFO> 
{
	public:		

		CPinWrapper(IPin* pPin = NULL);
		CPinWrapper(const CPinWrapper& pin);
		
		~CPinWrapper();

		virtual void Release();

		virtual CPinWrapper& operator = (IPin* pInterface)
		{				
			Release();

			if(pInterface != m_pInterface)				
				m_pInterface = pInterface;
			
			UpdateInfo();

			return *this;
		}
		
		virtual CPinWrapper& operator = (const CPinWrapper& pInterface)
		{	
			Release();

			if(&pInterface != this)
				m_pInterface = (IPin*)pInterface;
			
			UpdateInfo();

			return *this;
		}

		virtual HRESULT	Connect(CPinWrapper& pin, CMediaType* pmt = NULL);
		virtual HRESULT	Disconnect();
		virtual HRESULT	Remove() { return E_NOTIMPL; }

		BOOL			Connected();
		CMediaType		ConnectedMType();
		CPinWrapper		ConnectedPin();

		typedef std::deque<CMediaType> CMTList;
		
		CMediaType		GetDSMediaType(UINT n);
		UINT			GetDSMediaTypeCount();
		UINT			GetDSMediaTypeList(CMTList& list);

		BOOL			HasMediaType(REFCLSID majorType = GUID_NULL, REFCLSID subType = GUID_NULL);
		BOOL			HasMediaType(CMediaType& pmt);

		BOOL			AcceptConnection(CMediaType& mt);
		BOOL			AcceptConnection(CPinWrapper& pin);

		virtual HRESULT ChangeParam(LPCTSTR tcsName = NULL, ElType elType = elUnknown, REFGUID Category = GUID_NULL);
		
		virtual HRESULT UpdateInfo();

	protected:

		CMediaType*		m_pConnectedMType;
		CComPtr<IPin>	m_pConnectedPin;

		HRESULT			GetCategory(IPin* pPin,  GUID* category);
};


class CFilterWrapper :	public CBaseElement,
						public CElementImpl<IBaseFilter, FILTER_INFO>
						
{
	public:
		CFilterWrapper(const CFilterWrapper& filter);
		CFilterWrapper(const CLSID& clsFilter, HRESULT* pHr = NULL);
		CFilterWrapper(const CLSID& clsFilter, LPOLESTR szFileNamePath, HRESULT* pHr = NULL);
		CFilterWrapper(IBaseFilter* pFilter = NULL, LPCTSTR tcsName = NULL, 
								REFGUID Category = GUID_NULL);
#if !defined UNDER_CE
		CFilterWrapper(LPCWSTR wcsFriendlyName, HRESULT* pHr = NULL);
		CFilterWrapper(const CLSID& clsDeviceCategory, LPCWSTR wcsFriendlyName, HRESULT* pHr = NULL);
#endif
		~CFilterWrapper();

		typedef std::deque<CPinWrapper> CPinList;
		typedef	BOOL (__stdcall* CFA)(CPinWrapper&);
		
		typedef struct TSPinSearch
		{
			BOOL			connected;
			DIRECTION_PIN	direction;
			REFGUID			category;
			REFCLSID		majorType;

			TSPinSearch(DIRECTION_PIN pdirect = PINDIR_ALL, REFCLSID majType = MEDIATYPE_NULL,
						BOOL pbconnect = BOOL_NON, REFGUID pcategory = GUID_NULL) 
						: connected(pbconnect), direction(pdirect)
						, category(pcategory), majorType(majType) {};

		};

		virtual CFilterWrapper& operator = (IBaseFilter* pInterface)
		{	
			Release();
			if(pInterface != NULL && pInterface != m_pInterface)
				m_pInterface = pInterface;
			
			UpdateInfo();

			return *this;
		}
		
		virtual CFilterWrapper& operator = (const CFilterWrapper& pInterface)
		{	
			Release();

			if(pInterface.Valid() && &pInterface != this)
				m_pInterface = (IBaseFilter*)pInterface;
				
			UpdateInfo();

			CBaseElement::ChangeParam(pInterface.Name(), pInterface.Type(), pInterface.Category());

			return *this;
		}

		virtual HRESULT	Connect(CPinWrapper& pin, CMediaType* pmt = NULL);
		virtual HRESULT	Disconnect(PIN_DIRECTION direction = PINDIR_OUTPUT);
		virtual HRESULT	Remove(BOOL bRelease = TRUE);
		
		virtual HRESULT OnEvent(CBaseElement* pElement, DWORD dwAction = event_None, LPARAM lParam = 0);

		CPinWrapper		Pin(UINT n = 0, CFA f = 0);
		CPinWrapper		PinIn(REFCLSID majMediaType = MEDIATYPE_NULL, BOOL bConnected = BOOL_NON);
		CPinWrapper		PinOut(REFCLSID majMediaType = MEDIATYPE_NULL, BOOL bConnected = BOOL_NON);

		CPinWrapper		GetPin(UINT n, TSPinSearch psearch);		
		CPinWrapper		GetPin(REFGUID category, REFCLSID majMediaType = MEDIATYPE_NULL);
		CPinWrapper		GetPin(PIN_DIRECTION direction, REFCLSID majMediaType = MEDIATYPE_NULL, BOOL bConnected = BOOL_NON);				

		UINT			PinsList(CPinList& pnlist, CFA f = 0);
		UINT			PinsList(CPinList& pnlist, TSPinSearch psearch);
		UINT			PinsCount(CFA f = 0);

		BOOL			IsInGraph();

		virtual HRESULT UpdateInfo();

		virtual void	Release();

		HRESULT			GetLCState(DWORD* dwState);
		HRESULT			Activate(REFCLSID clsidActivationKey);
		
		HRESULT			GetClassID(CLSID *pCLSID)
		{
			if(!m_pInterface)
				return E_FAIL;
			
			return m_pInterface->GetClassID(pCLSID);
		}
		
	protected:

		typedef std::deque<CPinWrapper> TVPins;
		TVPins m_Pins;
		
		HRESULT			UpdatePins();
};


inline BOOL __stdcall IsInputPin(CPinWrapper& pin)
{
	return pin.Info().dir == PINDIR_INPUT;
}

inline BOOL __stdcall IsOutputPin(CPinWrapper& pin)
{
	return pin.Info().dir == PINDIR_OUTPUT;
}

inline BOOL __stdcall IsPinConnected(CPinWrapper& pPin)
{
	return pPin.Connected();
}

inline BOOL __stdcall IsPinFree(CPinWrapper& pPin)
{
	return !pPin.Connected();
}

inline BOOL __stdcall IsInAndFree(CPinWrapper& pPin)
{
	return IsInputPin(pPin) && !pPin.Connected();
}

inline BOOL __stdcall IsOutAndFree(CPinWrapper& pPin)
{
	return IsOutputPin(pPin) && !pPin.Connected();
}

inline BOOL __stdcall IsOutAndConnected(CPinWrapper& pPin)
{
	return IsOutputPin(pPin) && pPin.Connected();
}

inline BOOL __stdcall IsInAndConnected(CPinWrapper& pPin)
{
	return IsInputPin(pPin) && pPin.Connected();
}

#endif _BASE_ELEMENTS_