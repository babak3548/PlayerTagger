#pragma once
#include "DirectShowPin.h"
#include "DirectShowFilter.h"

class CDirectShowGraphBase: public  CComPtr<IGraphBuilder>
{
public:
	CDirectShowGraphBase(void);
	~CDirectShowGraphBase(void);
protected:
	virtual void Reset();
	HRESULT		AddFilter( CLSID clsFlt,  LPWSTR wszFilterName, CDirectShowFilter &filter );
	HRESULT		AddSinkFilter( CLSID clsFlt, LPWSTR wszFilterName, CDirectShowFilter &filter, LPCTSTR	tszFile);
	HRESULT		RemoveFilter( CDirectShowFilter *pFilter );
	HRESULT		Render( CDirectShowPin *pPin );
	HRESULT		ConnectPinWithFilter( CDirectShowPin *pPin, CDirectShowFilter *pFilter, BOOL bInt = FALSE );
	HRESULT		ConnectFilters( CDirectShowFilter *pUp, CDirectShowFilter *pDown, BOOL bInt = FALSE);
	HRESULT		DisconnectFilter( CDirectShowFilter *filter );
	HRESULT		DisconnectPin( CDirectShowPin		*pin );

	HRESULT	AddToROT( void );
	HRESULT	RemoveFromROT( void );
private:

	DWORD m_dwROT;
};
