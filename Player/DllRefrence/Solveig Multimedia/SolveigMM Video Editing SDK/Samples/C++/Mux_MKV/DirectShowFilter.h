#pragma once
#include "DirectShowPin.h"
//
// Class that wraps DirectShow filter object
//
class CDirectShowFilter : public CComPtr<IBaseFilter>
{
public:
	// Construction / Destruction
	CDirectShowFilter( void );
	CDirectShowFilter ( CDirectShowFilter &flt );
	CDirectShowFilter( IBaseFilter *pFilter );
	CDirectShowFilter( CLSID clsFlt, HRESULT *phr);
	virtual ~CDirectShowFilter(void);

	// Operators
	operator IBaseFilter*()	 const	{ return	p;	}
	CDirectShowFilter* operator &()	{	return	this;	}
	CDirectShowFilter&	operator = ( IBaseFilter* pFilter );
		

	// Returns amount of pins of filter
	HRESULT		GetPinCount( UINT *pCount );

	//	Gets filter pin with specified number
	HRESULT		GetPin( UINT	nNumber, CDirectShowPin &pin );

	// Gets filter connected upstream
	HRESULT		GetConnectedUpstream( CDirectShowFilter &upstream );

};


