#pragma once

typedef struct 
{
  GUID guid;
  TCHAR *szFormat;
} MediaFormat;


// Base class for video and audio graph branches
class CDirectShowGraph;
class CGraphBranch
{
protected:
	// Pointer to DirectShow Graph
	CDirectShowGraph		*m_pGraph;


	// Pointer to ASF Muxer filter
	CDirectShowFilter	*m_pAsfMuxer;		

	// Encoder filter
	CDirectShowFilter	m_fltEncoder;

	// Demuxer pin from which the branch is started
	CDirectShowPin		m_DemuxPin;

	// Last pin in branch ( for connection with ASF Muxer filter )
	CDirectShowPin		m_LastPin;

	

	// Branch type
	TCHAR	m_szBranchType[ 20 ];


	// Settings
	CSettings	*m_pSettings;

	// Select format by GUID
	virtual HRESULT		SelectFormatByGUID( GUID guid );
public:
	// Construction / Destruction
	CGraphBranch( HRESULT *phr, CDirectShowGraph	*pGraph, CSettings		*pSettings, 
		CDirectShowFilter	*pAsfMuxer, CDirectShowPin	&DemuxPin);
	virtual ~CGraphBranch(void);


	// Init branch
	virtual HRESULT		Init ( void );

	// Build branch
	virtual HRESULT		Build ( void );

	// Add encoder filter
	virtual HRESULT		AddEncoder( void );

	// Configure ASF Writer
	virtual HRESULT		ConfigureASFWriter( void );

	// Get branch type
	virtual HRESULT		GetType( LPTSTR szType ); 

	// Get settings		
	virtual HRESULT		GetSettings ( CSettings	**ppSettings );

	// Set settings
	virtual HRESULT		SetSettings( CSettings	*pSettings );

};


// Class for video branches
class		CVideoBranch : public CGraphBranch
{
protected:

	// Convert FOURCC string to DWORD value
	HRESULT	FOURCCStringToDWORD( LPCTSTR szFOURCC, DWORD *pdwFOURCC );

	// Select format by GUID
	virtual HRESULT		SelectFormatByGUID( GUID guid );
public:
	// Construction / Destruction
	CVideoBranch( HRESULT *phr, CDirectShowGraph	*pGraph,  CSettings	*pSettings,  
		CDirectShowFilter		*pAsfMuxer, CDirectShowPin &DemuxPin );
	virtual ~CVideoBranch(void);

	// Init branch
	virtual HRESULT		Init ( void );

	// Build branch
	virtual HRESULT		Build ( void );

	// Add encoder filter
	virtual HRESULT		AddEncoder( void );

	// Configure ASF Writer filter
	virtual HRESULT		ConfigureASFWriter( void );

	BOOL		AllowCustomFOURCC( void );
};

// Class for video branches
class		CAudioBranch : public CGraphBranch
{
protected:
	
	// Select format by GUID
	virtual HRESULT		SelectFormatByGUID( GUID guid );
public:
	// Construction / Destruction
	CAudioBranch( HRESULT *phr, CDirectShowGraph	*pGraph,  CSettings	*pSettings, 
		CDirectShowFilter		*pAsfMuxer, CDirectShowPin &DemuxPin );
	virtual ~CAudioBranch(void);

	// Init branch
	virtual HRESULT		Init ( void );

	// Build branch
	virtual HRESULT		Build ( void );

	// Add encoder filter
	virtual HRESULT		AddEncoder( void );
	// Configure ASF Writer filter
	virtual HRESULT		ConfigureASFWriter( void );

};