////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2004-2012 Solveig Multimedia
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

#include "StdAfx.h"
#include ".\directshowfilter.h"

CDirectShowFilter::CDirectShowFilter( void )
{
}

CDirectShowFilter::CDirectShowFilter ( CDirectShowFilter &flt )
{
	CComPtr<IBaseFilter>::operator =(flt.p);
}

CDirectShowFilter::CDirectShowFilter( IBaseFilter *pFilter )
{
	CComPtr<IBaseFilter>::operator = ( pFilter );
}


CDirectShowFilter::CDirectShowFilter( CLSID clsFlt,  HRESULT *phr)
{
	*phr = CoCreateInstance( clsFlt );
}


CDirectShowFilter& CDirectShowFilter::operator = ( IBaseFilter* pFilter )
{
	if(pFilter != p)
		CComPtr<IBaseFilter>::operator =(pFilter);
	return *this;
}


CDirectShowFilter::~CDirectShowFilter(void)
{
}

HRESULT		CDirectShowFilter::GetPinCount( UINT *pCount )
{
	HRESULT hr = S_OK;
	CComPtr< IEnumPins > pEnum;
	hr = p->EnumPins( &pEnum );
	if (FAILED(hr)) {
		return hr;
	}

	pEnum->Reset();

	CComPtr<IPin>pPin;
	while (pEnum->Next(1, &pPin, NULL) == S_OK)
	{
		(*pCount)++;
		pPin.Release();
	}

	return S_OK;
}

HRESULT		CDirectShowFilter::GetPin( UINT	nNumber, CDirectShowPin &pin )
{
	HRESULT hr = S_OK;
	CComPtr< IEnumPins > pEnum;
	hr = p->EnumPins( &pEnum );
	if (FAILED(hr)) {
		return hr;
	}

	pEnum->Reset();

	CComPtr<IPin>pPin;
	UINT	nCurrent = 0;
	while (pEnum->Next(1, &pPin, NULL) == S_OK)
	{
		if (nCurrent == nNumber) {
			pin = pPin;
			return S_OK;
		}

		pPin.Release();
		nCurrent++;
	}

	// We did not find pin with specified number
	return E_INVALIDARG;
}

HRESULT		CDirectShowFilter::GetConnectedUpstream( CDirectShowFilter &upstream )
{
	HRESULT hr = S_OK;
	UINT n = 0, count = 0;


	hr = GetPinCount( &count );
	if (FAILED(hr)) {
		return hr;
	}

	BOOL	bConnected = false;
	
	CDirectShowPin	pin, connected;
	CDirectShowFilter	up;

	for (n = 0; n < count; n++)
	{
		
		hr = GetPin(n,pin);
		if (SUCCEEDED(hr))
		{
			if (pin.IsInput())
			{
				hr = pin.GetConnected( connected );
				if (SUCCEEDED(hr)) {
					PIN_INFO pi;
					hr = connected->QueryPinInfo( &pi );	
					if (SUCCEEDED(hr)) 
					{

						upstream = pi.pFilter;
						pi.pFilter->Release();
						bConnected = true;
						pin.Release();
						connected.Release();

						break;
					}
				}
			}
			pin.Release();
		}
	}
		
	if (!bConnected) {
		return VFW_E_NOT_CONNECTED;
	}

	return hr;
}

