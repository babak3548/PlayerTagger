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
#include ".\settings.h"


CSettings::CSettings(void) :
	m_bEnabled ( true ),
	m_bUncompressed( false ),
	m_bTranscode( false )
{
	USES_CONVERSION;
	m_guidEnc = GUID_NULL;
	ZeroMemory( m_szEncName, MAX_PATH );
	ZeroMemory ( m_szFormat, MAX_PATH );
	m_bstLang = SysAllocString( T2OLE(wcsLangID[0][1]) );
}

CSettings::~CSettings(void)
{
}

BOOL		CSettings::IsEnabled( void )
{
	CAutoLock lck( &m_csLock );
	return m_bEnabled;
}


void		CSettings::SetEnabled( BOOL bEnabled )
{
	CAutoLock lck( &m_csLock );
	m_bEnabled = bEnabled;
}

BOOL		CSettings::IsUncompressed( void )
{
	CAutoLock lck( &m_csLock );
	return m_bUncompressed;
}

void		CSettings::SetUncompressed ( BOOL bUncompressed )
{
	CAutoLock lck( &m_csLock );
	m_bUncompressed = bUncompressed;
}

BOOL		CSettings::IsTranscode( void )
{
	CAutoLock lck( &m_csLock );
	return m_bTranscode;
}

void		CSettings::SetTranscode( BOOL bTranscode )
{
	CAutoLock lck( &m_csLock );
	m_bTranscode = bTranscode;
}

GUID		CSettings::GetEncoderGUID( void )
{
	CAutoLock lck( &m_csLock );
	return m_guidEnc;
}

void		CSettings::SetEncoderGUID( GUID guidEnc )
{
	CAutoLock lck( &m_csLock );
	m_guidEnc = guidEnc;
}

void		CSettings::GetEncoderName ( TCHAR *szName )
{
	CAutoLock lck( &m_csLock );
	if (szName) _tcscpy( szName, m_szEncName );
}

void		CSettings::SetEncoderName( LPCTSTR szName )
{
	CAutoLock lck( &m_csLock );
	if (szName) _tcscpy( m_szEncName, szName );
}

void		CSettings::GetFormatString ( LPTSTR szFormat )
{
	CAutoLock	lcs ( &m_csLock );
	if (szFormat) 
		_tcscpy( szFormat, m_szFormat );
}

void		CSettings::SetFormatString ( LPCTSTR szFormat )
{
	CAutoLock	lcs ( &m_csLock );
	if (szFormat) 
		_tcscpy( m_szFormat, szFormat );
}

void CSettings::GetLanguage ( BSTR *bstLang )
{
	CAutoLock lcs( &m_csLock );
	if( bstLang ) 
		*bstLang = ::SysAllocString( m_bstLang );
}

void CSettings::SetLanguage ( BSTR bstLang )
{
	USES_CONVERSION;
	CAutoLock lcs( &m_csLock );
	if (bstLang)
	{
		SysFreeString( m_bstLang )	;
		m_bstLang = ::SysAllocString( bstLang );
	}
}

CVideoSettings::CVideoSettings( void ):
	CSettings(),
	m_bTreatAsH264 ( false ),
	m_bUseCustomFOURCC ( false )
{
	ZeroMemory(m_szFOURCC, 4);
}



void		CVideoSettings::SetTreatVideoAsH264( BOOL bTreat )
{
	CAutoLock	lck( &m_csLock );
	m_bTreatAsH264 = bTreat;
}

BOOL		CVideoSettings::GetTreatVideoAsH264( void )
{
	CAutoLock	lck( &m_csLock );
	return m_bTreatAsH264;
}

void		CVideoSettings::SetUseCustomFOURCC( BOOL bUse )
{
	CAutoLock	lck( &m_csLock );
	m_bUseCustomFOURCC = bUse;
}

BOOL		CVideoSettings::GetUseCustomFOURCC( void )
{
	CAutoLock	lck( &m_csLock );
	return m_bUseCustomFOURCC;
}

void		CVideoSettings::SetFOURCC ( LPCTSTR pszFOURCC )
{
	CAutoLock	lck( &m_csLock );
	if (pszFOURCC) _tcscpy( m_szFOURCC, pszFOURCC);
}

void		CVideoSettings::GetFOURCC( TCHAR *pszFOURCC )
{
	CAutoLock lck( &m_csLock );
	if (pszFOURCC) _tcscpy( pszFOURCC, m_szFOURCC);
}