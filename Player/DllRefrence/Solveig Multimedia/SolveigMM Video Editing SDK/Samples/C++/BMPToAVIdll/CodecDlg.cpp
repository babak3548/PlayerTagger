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
// CodecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CodecDlg.h"


// CCodecDlg dialog

IMPLEMENT_DYNAMIC(CCodecDlg, CDialog)

CCodecDlg::CCodecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodecDlg::IDD, pParent)
{

}

CCodecDlg::~CCodecDlg()
{
}

void CCodecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCodecDlg, CDialog)
	ON_BN_CLICKED(IDC_PROPERTIES, &CCodecDlg::OnBnClickedProperties)
END_MESSAGE_MAP()


// CCodecDlg message handlers

BOOL CCodecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMenu *pSysMenu = GetSystemMenu( FALSE );
	pSysMenu->EnableMenuItem( SC_CLOSE, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED );
	m_bPrefer = FALSE;

	HRESULT hr;
    ICreateDevEnum *pSysDevEnum = NULL;
    IEnumMoniker *pEnum = NULL;
    IMoniker *pMoniker = NULL;

    hr = CoCreateInstance(	CLSID_SystemDeviceEnum, NULL, 
							CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
							(void**)&pSysDevEnum );
    if (FAILED(hr))
    {
        // Handle the error.
    }    

    hr = pSysDevEnum->CreateClassEnumerator( CLSID_VideoCompressorCategory, &pEnum, 0 );
    if (hr == S_OK)  // S_FALSE means nothing in this category.
    {
        while ( S_OK == pEnum->Next( 1, &pMoniker, NULL ) )
        {
            IPropertyBag *pPropBag = NULL;
            pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
            VARIANT var;
            VariantInit( &var );
            hr = pPropBag->Read( L"FriendlyName", &var, 0 );
			USES_CONVERSION;
			if ( SUCCEEDED(hr) )
				SendDlgItemMessage( IDC_CODEC_LIST, LB_ADDSTRING, 0, (LPARAM)OLE2T(var.bstrVal) );
		        
            VariantClear(&var); 
            pPropBag->Release();
            pMoniker->Release();
        }
    }
	SendDlgItemMessage( IDC_CODEC_LIST, LB_ADDSTRING, 0, (LPARAM)_T("(No Encoding)") );
	SendDlgItemMessage( IDC_CODEC_LIST, LB_SETCURSEL, 0, 0 );
    pSysDevEnum->Release();
    pEnum->Release();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BSTR CCodecDlg::InitializeEncoder( IBaseFilter** pEncoderInterface, HRESULT *hr )
{
	if( m_csEncoderFriendlyName == _T("(No Encoding)") )
	{
		*pEncoderInterface = NULL;
		return L"Raw RGB";
	}
	ICreateDevEnum *pSysDevEnum = NULL;
    IEnumMoniker *pEnum = NULL;
    IMoniker *pMoniker = NULL;

    *hr = CoCreateInstance(	CLSID_SystemDeviceEnum, NULL, 
							CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
							(void**)&pSysDevEnum );
    if (FAILED(*hr))
    {
        // Handle the error.
    }    

    *hr = pSysDevEnum->CreateClassEnumerator( CLSID_VideoCompressorCategory, &pEnum, 0 );
    if ( *hr == S_OK )  // S_FALSE means nothing in this category.
    {
        while ( S_OK == pEnum->Next( 1, &pMoniker, NULL ) )
        {
            
			IPropertyBag *pPropBag = NULL;
            pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
            VARIANT var;
            VariantInit( &var );
            *hr = pPropBag->Read( L"FriendlyName", &var, 0 );
			if( var.bstrVal == m_csEncoderFriendlyName )
				*hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)pEncoderInterface);

		}
	}
	return m_csEncoderFriendlyName.AllocSysString();
}
void CCodecDlg::OnOK()
{
	CListBox *pListBox;
	pListBox = (CListBox*)GetDlgItem(IDC_CODEC_LIST);
	
	pListBox->GetText( pListBox->GetCurSel(), m_csEncoderFriendlyName );

	if( IsDlgButtonChecked( IDC_CHECK_PREFER_ENCODER ) == BST_CHECKED )
		m_bPrefer = TRUE;

	CDialog::OnOK();
}

void CCodecDlg::OnBnClickedProperties()
{
	HRESULT hr;
	CString strName;
	CListBox *pListBox;
	pListBox = (CListBox*)GetDlgItem(IDC_CODEC_LIST);
	pListBox->GetText( pListBox->GetCurSel(), strName );

	CComPtr<ICreateDevEnum> pSysDevEnum = NULL;
    CComPtr<IEnumMoniker> pEnum = NULL;
    CComPtr<IMoniker> pMoniker = NULL;
	CComPtr<IAMVfwCompressDialogs>	pCompressDlg = NULL;
	CComPtr<IBaseFilter>			pEncInterface = NULL;

    hr = CoCreateInstance(	CLSID_SystemDeviceEnum, NULL, 
							CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
							(void**)&pSysDevEnum );
    if (FAILED(hr))
    {
        // Handle the error.
    }    

    hr = pSysDevEnum->CreateClassEnumerator( CLSID_VideoCompressorCategory, &pEnum, 0 );
	pSysDevEnum.Release();
    if ( hr == S_OK )  // S_FALSE means nothing in this category.
    {
        while( S_OK == pEnum->Next( 1, &pMoniker, NULL ) )
        {
			CComPtr<IPropertyBag> pPropBag = NULL;
            pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
            VARIANT var;
            VariantInit( &var );
            hr = pPropBag->Read( L"FriendlyName", &var, 0 );
			pPropBag.Release();
			if( var.bstrVal == strName )
			{
				hr = pMoniker->BindToObject(0, 0, IID_IAMVfwCompressDialogs, (void**)&pCompressDlg);
				if( SUCCEEDED(hr) )
				{
					pCompressDlg->ShowDialog( VfwCompressDialog_Config, GetSafeHwnd() );
					pCompressDlg.Release();
					pEnum.Release();
					break;
				}
				hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pEncInterface);
				if( SUCCEEDED(hr) )
				{
					/* Obtain the filter's IBaseFilter interface. (Not shown) */
					CComPtr<ISpecifyPropertyPages> pProp;
					HRESULT hr = pEncInterface->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);
					if (SUCCEEDED(hr)) 
					{
						// Get the filter's name and IUnknown pointer.
						FILTER_INFO FilterInfo;
						hr = pEncInterface->QueryFilterInfo(&FilterInfo); 
						IUnknown* pFilterUnk;
						pEncInterface->QueryInterface(IID_IUnknown, (void **)&pFilterUnk);

						// Show the page. 
						CAUUID caGUID;
						pProp->GetPages(&caGUID);
						OleCreatePropertyFrame(
												GetSafeHwnd(),
												0, 0,
												FilterInfo.achName,
												1,
												&pFilterUnk,
												caGUID.cElems,
												caGUID.pElems,
												0,
												0, NULL	);

						// Clean up.
						pProp.Release();
						CoTaskMemFree(caGUID.pElems);
						pEncInterface.Release();
						pEnum.Release();
						break;
					}
				}
			}
			pMoniker.Release();
		}
		pMoniker.Release();
	}
}