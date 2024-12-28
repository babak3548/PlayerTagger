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

// EncoderSelectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TestMuxerApp.h"
#include "EncoderSelectionDialog.h"
#include ".\encoderselectiondialog.h"

extern LPWSTR GetWCHAR(LPCTSTR pIn, LPWSTR pOut);
// CEncoderSelectionDialog dialog

IMPLEMENT_DYNAMIC(CEncoderSelectionDialog, CDialog)
CEncoderSelectionDialog::CEncoderSelectionDialog(BOOL bVideo, TCHAR *szFile, CWnd* pParent /*=NULL*/)
	: CDialog(CEncoderSelectionDialog::IDD, pParent),
	m_bVideo( bVideo )
{
	m_nGuidCount = 0;
	m_nCurrIndex = 0;
	lstrcpy( m_szFile, szFile );
	ZeroMemory(&m_ResultGUID, sizeof(GUID));
	m_szResultName= "";
}

CEncoderSelectionDialog::~CEncoderSelectionDialog()
{
}

void CEncoderSelectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_EncoderList);
}


BEGIN_MESSAGE_MAP(CEncoderSelectionDialog, CDialog)
	ON_LBN_DBLCLK(IDC_LIST2, OnLbnDblclkList2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEncoderSelectionDialog message handlers

BOOL		CEncoderSelectionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	HRESULT hr = S_OK;

	CString	szVideo =  m_bVideo ?  _T("video") : _T("audio");
	CString szCaption = _T("Select ") + szVideo + _T(" encoder:");
	SetWindowText( szCaption );


	HANDLE	hFile = CreateFile(m_szFile, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD	dwRead;

		CString	szName, szGUID;
		char c;

		BOOL		bEof = false;
		for (;;)
		{
			// Read name
			szName = "";
			for (;;)
			{
				if(!ReadFile( hFile,&c,1, &dwRead, NULL )) {
					bEof = true;				
					break;
				}

				if (!dwRead) {
					bEof = true;
					break;
				}

				if (c ==13) 
					break;

				szName += c;
			}

			if (bEof)
				break;

			ReadFile( hFile,&c,1, &dwRead, NULL );
		
			// Read guid

			szGUID = "";
			for (;;)
			{
				if(!ReadFile( hFile,&c,1, &dwRead, NULL )) {
					bEof = true;				
					break;
				}

				if (!dwRead) {
					bEof = true;
					break;
				}

				if (c ==13) 
					break;

				szGUID += c;
			}

	
			// Try to create object
			CLSID clsid;
			WCHAR	wszGUID[ MAX_PATH ];
			GetWCHAR( szGUID, (LPWSTR)wszGUID );

			hr = CLSIDFromString( wszGUID, &clsid );
			if (SUCCEEDED(hr))
			{
				CComPtr<IUnknown>pUnk;
				hr = pUnk.CoCreateInstance( clsid );
				if (SUCCEEDED(hr))
				{
					
					m_Guids[ m_nGuidCount ] = clsid;
	
					m_EncoderList.InsertString( m_nCurrIndex, szName );
					m_EncoderList.SetItemData( m_nCurrIndex, (DWORD_PTR)&m_Guids[ m_nGuidCount ] );

					m_nCurrIndex++;
					m_nGuidCount++;
					pUnk.Release();
				}
			}

			if (bEof)
				break;

			ReadFile( hFile,&c,1, &dwRead, NULL );
		}
		CloseHandle( hFile );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

GUID		CEncoderSelectionDialog::GetEncoderGUID ( void )
{
	return m_ResultGUID;
}

CString	CEncoderSelectionDialog::GetEncoderName( void  )
{
	return m_szResultName;
}


void CEncoderSelectionDialog::OnLbnDblclkList2()
{
	int nCurSel = m_EncoderList.GetCurSel();
	DWORD_PTR	p = m_EncoderList.GetItemData( nCurSel );
	memcpy( &m_ResultGUID, (void *)p, sizeof(GUID) );
	m_EncoderList.GetText( nCurSel, m_szResultName );
	EndDialog( 0 );
}

void CEncoderSelectionDialog::OnClose()
{
	CDialog::OnClose();
}
