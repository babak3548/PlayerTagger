////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2011-2012 Solveig Multimedia
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
#include ".\directshowpin.h"

CDirectShowPin::CDirectShowPin(void)
{
}

CDirectShowPin::~CDirectShowPin(void)
{
}

CDirectShowPin &CDirectShowPin::operator = (IPin* pPin)
{
	if(pPin != p)
		CComPtr<IPin>::operator =(pPin);
	return *this;
}

// Check that pin is connected
BOOL		CDirectShowPin::IsConnected( void )
{
	HRESULT hr = S_OK;
	CComPtr<IPin>pConnected;
	hr = p->ConnectedTo( &pConnected );
	return (hr == S_OK && pConnected) ? true : false;
}

BOOL		CDirectShowPin::IsOutput( void )
{
	PIN_DIRECTION	pd;
	p->QueryDirection( &pd );
	return pd == PINDIR_OUTPUT;
}


BOOL		CDirectShowPin::IsInput( void )
{
	PIN_DIRECTION	pd;
	p->QueryDirection( &pd );
	return pd == PINDIR_INPUT;
}


// Get connected pin
HRESULT	CDirectShowPin::GetConnected( CDirectShowPin	&Pin )
{
	HRESULT hr = S_OK;
	if (!IsConnected()) {
		return VFW_E_NOT_CONNECTED;
	}
	CComPtr<IPin>pConnected;
	hr = p->ConnectedTo( &pConnected );
	if (FAILED(hr)) {
		return hr;
	}

	Pin = pConnected;
	return hr;
}

HRESULT	CDirectShowPin::GetMediaType( CMediaType	&MediaType )
{
	HRESULT hr = S_OK;
	AM_MEDIA_TYPE	amt;
	hr = p->ConnectionMediaType( &amt );
	if (FAILED(hr)) {
		return VFW_E_NOT_CONNECTED;
	}
	MediaType = amt;
	return hr;
}