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
#include "DirectShowGraphBase.h"
CDirectShowGraphBase::CDirectShowGraphBase(void):
m_dwROT(0)
{
}

CDirectShowGraphBase::~CDirectShowGraphBase(void)
{
	Reset();
}
void CDirectShowGraphBase::Reset()
{
	RemoveFromROT();
	Release();
}


HRESULT		CDirectShowGraphBase::AddFilter( CLSID clsFlt,  LPWSTR wszFilterName, CDirectShowFilter &filter )
{
	HRESULT hr = S_OK;
	CDirectShowFilter flt(clsFlt, &hr);
	if (FAILED(hr)) {
		return hr;
	}

	filter = flt;
	hr =  p->AddFilter( filter, wszFilterName );
	return hr;
}

HRESULT		CDirectShowGraphBase::AddSinkFilter( CLSID clsFlt, LPWSTR wszFilterName, CDirectShowFilter &filter, LPCTSTR	tszFile)
{
	HRESULT hr = AddFilter( clsFlt, wszFilterName, filter);
	if (FAILED(hr)) {
		return hr;
	}
	CComPtr<IFileSinkFilter>pSink;
	hr = filter.QueryInterface( &pSink );
	if (SUCCEEDED(hr))
	{
		USES_CONVERSION;
		hr = pSink->SetFileName( T2W((LPTSTR)tszFile), NULL );
	}
	pSink = NULL;
	return hr;
}

HRESULT		CDirectShowGraphBase::RemoveFilter( CDirectShowFilter *pFilter )
{
	HRESULT hr = S_OK;
	if (!p) {
		return E_POINTER;
	}

	hr = DisconnectFilter ( pFilter );
	if (FAILED(hr)) {
		return hr;
	}

	return  p->RemoveFilter( *pFilter );
}

HRESULT		CDirectShowGraphBase::Render( CDirectShowPin *pPin )
{
	if (!p) {
		return E_POINTER;
	}
	return p->Render( *pPin );
}


HRESULT		CDirectShowGraphBase::ConnectPinWithFilter( CDirectShowPin *pPin, CDirectShowFilter *pFilter, BOOL bInt )
{
	HRESULT hr = S_OK;
	if (!pPin || !pFilter ) {
		return E_POINTER;
	}

	UINT nPinCount = 0,  n = 0;
	hr = pFilter->GetPinCount( &nPinCount );
	if (FAILED(hr)) 
		return hr;

	CDirectShowPin	pin;
	for (n = 0; n < nPinCount; n++)
	{

		hr = pFilter->GetPin(n, pin );
		if (SUCCEEDED(hr)) 
		{
			if (pin.IsInput()) {

				if ( bInt )
					hr = p->Connect( *pPin, pin );
				else
					hr = p->ConnectDirect( *pPin, pin, NULL );

			}
			pin.Release();

			if (SUCCEEDED(hr)) {
				break;
			}
		}
	}
	return hr;
}

HRESULT		CDirectShowGraphBase::ConnectFilters( CDirectShowFilter *pUp, CDirectShowFilter *pDown, BOOL bInt )
{
	HRESULT hr = S_OK;
	if (!pUp || !pDown) {
		return E_POINTER;
	}

	UINT nPinCount = 0,  n = 0;
	hr = pUp->GetPinCount( &nPinCount );
	if (FAILED(hr)) 
		return hr;

	CDirectShowPin	pin;
	for (n = 0; n < nPinCount; n++)
	{

		hr = pUp->GetPin(n, pin );
		if (SUCCEEDED(hr)) 
		{
			if (pin.IsOutput()) {
				hr = ConnectPinWithFilter( &pin, pDown, bInt );
			}

			pin.Release();

			if (FAILED(hr)) {
				return hr;

			}
		}	
	}
	return hr;
}

HRESULT		CDirectShowGraphBase::DisconnectFilter( CDirectShowFilter *filter )
{
	HRESULT hr = S_OK, hrAll = S_OK;
	if (!filter || !p) {
		return E_POINTER;
	}
	// Disconnect all pins of filter
	UINT n = 0, count = 0;
	BOOL bNoneConnected = false;

	for (;;)
	{
		count = 0;
		bNoneConnected = true;
		hr = filter->GetPinCount( &count );
		if (FAILED(hr)) {

			hr = S_FALSE;
			break;
		}

		CDirectShowPin pin, connected;

		for (n = 0; n < count; n++)
		{
			hr = filter->GetPin(n, pin );
			if (SUCCEEDED(hr))
			{
				if ( pin.IsConnected() ) {

					bNoneConnected = false;


					hr = pin.GetConnected( connected );	
					if (SUCCEEDED(hr)) 
					{

						hr = DisconnectPin( &connected );
						connected.Release();
						if (FAILED(hr)) {
							return hr;
						}
					}

					hr = DisconnectPin ( &pin );
					pin.Release();
					if (FAILED(hr)) {
						return hr;
					}
				}
			}
		}
		if (bNoneConnected) return S_OK;
	}

	return hr;
}
HRESULT		CDirectShowGraphBase::DisconnectPin( CDirectShowPin		*pin )
{
	HRESULT hr = S_OK;
	if (!pin || !p) {
		return E_POINTER;
	}

	return p->Disconnect( *pin );
}
HRESULT	CDirectShowGraphBase::AddToROT( void )
{
	IRunningObjectTable* pROT = NULL;
	if(FAILED(GetRunningObjectTable(0, &pROT)))
		return E_FAIL;

	WCHAR wsz[256], wsz1[24];
	wcscpy(wsz, L"FilterGraph ");
	_itow((int)(DWORD_PTR)this, wsz1, 16);
	wcscat(wsz, wsz1);
	wcscat(wsz, L" pid ");
	_itow(GetCurrentProcessId(), wsz1, 16);
	wcscat(wsz, wsz1);

	IMoniker* pMoniker = NULL;
	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
	if(SUCCEEDED(hr)) 	
	{
		hr = pROT->Register(0, p, pMoniker, &m_dwROT);
		pMoniker->Release();
	}
	pROT->Release();
	return S_OK;
}
HRESULT	CDirectShowGraphBase::RemoveFromROT( void )
{
	IRunningObjectTable* pROT = NULL;
	if(m_dwROT && SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
	{
		pROT->Revoke(m_dwROT);
		m_dwROT = 0;
		pROT->Release();
	}
	return S_OK;
}