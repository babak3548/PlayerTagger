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
#include "stdafx.h"
#include "IndexingDlg.h"
#define PROGRESS_RANGE_INDEX		100
#define INDEX_TIMER			1
// CDlgIndexing dialog
BEGIN_MESSAGE_MAP(CDlgIndexing, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()
CDlgIndexing::CDlgIndexing(CWnd* pParent ,HRESULT *phr): 
CDialog(CDlgIndexing::IDD, pParent),
m_pIModuleConfig(NULL),
m_pITrimmerObj(NULL),
m_IndexTimer(0)
{
	SetFinishedIndexing( TRUE );

	*phr = ::CoCreateInstance( CLSID_TrimmerObjControl, NULL, CLSCTX_INPROC,
								IID_ITrimmerObjControl, (void**) &m_pITrimmerObj );
	if( FAILED(*phr) )
		return;

	*phr = m_pITrimmerObj->QueryInterface( IID_IModuleConfig, (void **)&m_pIModuleConfig );
	if( FAILED(*phr) )
		return;
	VARIANT var = {0};

	CString silenPt = GetRegistrySilentPath( CLSID_VideoEditingSDK );
	if ( 0 != silenPt.GetLength() )
	{
		var.bstrVal = silenPt.AllocSysString();
		*phr= m_pIModuleConfig->SetValue( &SMAT_SilentPath, &var );
		SysFreeString( var.bstrVal );
	}
}



CDlgIndexing::CDlgIndexing(CWnd* pParent /*=NULL*/): 
CDialog(CDlgIndexing::IDD, pParent)
{
}

CDlgIndexing::~CDlgIndexing()
{
	m_pIModuleConfig.Release();
	m_pITrimmerObj.Release();
}

void CDlgIndexing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_INDEX, m_ctlPogrIndx);
}

BOOL CDlgIndexing::OnInitDialog()
{
	HRESULT hr;	
	
	VARIANT var = {0};
	var.bstrVal  = m_csProfile.AllocSysString();
	hr= m_pIModuleConfig->SetValue( &SMAT_CodecsSet, &var );
	SysFreeString( var.bstrVal );

	CDialog::OnInitDialog();
	m_ctlPogrIndx.SetRange( 0, PROGRESS_RANGE_INDEX );
	SetFinishedIndexing( FALSE );

	m_IndexTimer = SetTimer( INDEX_TIMER, 500, NULL );
	
	//Set Callback here
	if( &m_xCTrimmerObjControlCB )
	{
		var.pbVal = (BYTE*) &m_xCTrimmerObjControlCB;
		hr = m_pIModuleConfig->SetValue( &SMAT_Callback, &var);
	}

	var.vt		= VT_BOOL;
	var.boolVal = TRUE;
	hr = m_pIModuleConfig->SetValue( &SMAT_StartIndexation, &var );
	if( FAILED(hr) )
	{
		MessageBox(_T("Unable to read Index file"), _T("Error"), MB_OK | MB_ICONWARNING);
		SetFinishedIndexing( TRUE );
		return FALSE;
	}
	return TRUE;
}
HRESULT CDlgIndexing::SetInputFile( CString strInName )
{
	BSTR bstName = strInName.AllocSysString();
	VARIANT var = {0};
	HRESULT hr = E_FAIL;
	var.vt = VT_BSTR;
	var.bstrVal = bstName;
	hr = m_pIModuleConfig->SetValue( &SMAT_InputFile, &var );
	SysFreeString( bstName );
	return hr;
}
HRESULT CDlgIndexing::SetOutputIndexFile( CString strOutInd )
{
	BSTR bstName = strOutInd.AllocSysString();
	VARIANT var = {0};
	HRESULT hr = E_FAIL;
	var.vt = VT_BSTR;
	var.bstrVal = bstName;
	hr = m_pIModuleConfig->SetValue( &SMAT_OutIndexFile, &var );
	SysFreeString( bstName );
	return hr;
}

void CDlgIndexing::OnTimer(UINT_PTR nIDEvent )
{
	CDialog::OnTimer(nIDEvent);
	if( nIDEvent == INDEX_TIMER )
	{
		long lProgress = 1;
		m_pITrimmerObj->get_Status( &lProgress );
		TRACE("%d\n",lProgress);
		//kill timer and release interface if indexing is over
		if( IsFinishedIndexing() ) 
		{
			m_ctlPogrIndx.SetPos( PROGRESS_RANGE_INDEX );
			KillTimer( m_IndexTimer );
			m_IndexTimer = 0;
			EndDialog (1);
		}
		else if( lProgress >= 0 )
		{
			m_ctlPogrIndx.SetPos(lProgress * PROGRESS_RANGE_INDEX / 100);
		}
	}
}

void CDlgIndexing::TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime )
{
	int t = 0;
}

