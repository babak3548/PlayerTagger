#pragma once

//
// Base class for storing settings of stream of any type
//
class CSettings
{
protected:
	// Critical section for locking settings
	CCritSec		m_csLock;

public:
	CSettings( void );
	virtual ~CSettings( void );

protected:
	// Is branch enabled
	BOOL		m_bEnabled;		

	// Is uncompressed
	BOOL		m_bUncompressed;

	// Need transcode brach
	BOOL		m_bTranscode;

	// Encoder GUID
	GUID		m_guidEnc;

	// Encoder name
	TCHAR		m_szEncName[ MAX_PATH ];

	// Format string
	TCHAR		m_szFormat [ MAX_PATH ];

	//Language
	BSTR		m_bstLang;
public:

	// Interface methods	
	BOOL		IsEnabled( void );
	void		SetEnabled( BOOL bEnabled );
	BOOL		IsUncompressed( void );
	void		SetUncompressed ( BOOL bUncompressed );
	BOOL		IsTranscode( void );
	void		SetTranscode( BOOL bTranscode );
	GUID		GetEncoderGUID( void );
	void		SetEncoderGUID( GUID guidEnc );
	void		GetEncoderName ( TCHAR *szName );
	void		SetEncoderName( LPCTSTR szName );
	void	    GetFormatString ( LPTSTR szFormat );
	void		SetFormatString ( LPCTSTR szFormat );
	void	    GetLanguage ( BSTR *bstLang );
	void		SetLanguage ( BSTR bstLang );



	
};


//
// Class for storing video settings 
//
class	CVideoSettings : public CSettings
{
public:
	// Construction
	CVideoSettings( void );

protected:
	// Treat input video as H.264
	BOOL		m_bTreatAsH264;

	// Use custom FOURCC 
	BOOL		m_bUseCustomFOURCC;

	// FOURCC string
	TCHAR		m_szFOURCC[4];

public:
	void		SetTreatVideoAsH264( BOOL bTreat );
	BOOL		GetTreatVideoAsH264( void );
	void		SetUseCustomFOURCC( BOOL bUse );
	BOOL		GetUseCustomFOURCC( void );
	void		SetFOURCC ( LPCTSTR pszFOURCC );
	void		GetFOURCC( TCHAR *pszFOURCC );

};

//
// Class for storing audio settings 
//
class	CAudioSettings : public CSettings
{
public:
};