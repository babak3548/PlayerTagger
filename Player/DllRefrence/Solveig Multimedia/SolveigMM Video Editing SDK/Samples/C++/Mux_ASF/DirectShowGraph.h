#pragma once

#define MAX_GRAPH_BRANCHES	20

// 
// Inferface  for communication between graph and owner window ( MFC )
//
class	IGraphCallback
{
public:
	virtual	void	OnGraphBuilt ( void ) = 0;
	virtual	void	OnNewFile( void ) = 0;
	virtual	void	OnGraphStarted( void ) = 0;
	virtual	void	OnGraphStopped( void ) = 0;
	virtual	void	OnTimer( void ) = 0;
	virtual	void	OnAbort( void ) = 0;
};

//
// Class that wraps DirectShow Graph Manager object
//
class CDirectShowGraph : public CComPtr<IGraphBuilder>
{
	friend	CGraphBranch;
	friend	CVideoBranch;
	friend	CAudioBranch;

public:
	operator IModuleConfig*() const
	{
		return m_pMuxConfig;
	}
protected:
	// Pointer to graph callback
	IGraphCallback		*m_pGC;

	// Source / Destination file
	LPTSTR		m_szSource[MAX_PATH];
	LPTSTR		m_szDest[MAX_PATH];

	// 
	BOOL			m_bIndexASF;
	BOOL			m_bWriteLog;


	// Indicates that new source file is specified
	BOOL			m_bNewFile;
	//
	// Filters
	//
	CDirectShowFilter	m_fltAsfMuxer;
	CDirectShowFilter	m_fltDVSplitter;

    //
	// Interfaces
	//
	CComPtr<IMediaControl>	m_pMC;
	CComPtr<IMediaFilter>	m_pMF;
	CComPtr<IMediaSeeking>	m_pMS;
	CComPtr<IMediaEventEx>	m_pMEx;
	CComPtr<IModuleConfig>	m_pMuxConfig;

	
	//
	// Timer
	//
	MMRESULT		m_mmTimer;
	
	static void CALLBACK TimeCallback (UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
	{
		CDirectShowGraph	*pGraph = (CDirectShowGraph *)dwUser;
		if (pGraph ) {
			pGraph->OnTimer();
		}
	}
	void		OnTimer( void );


	//
	// Settings
	//
	CVideoSettings	*m_pVS[ MAX_VIDEO_STREAMS ];
	CAudioSettings	*m_pAS[ MAX_AUDIO_STREAMS ];

	//
	// Branches
	//
	CGraphBranch	*m_Branches[MAX_GRAPH_BRANCHES];
	UINT		m_nBranchesCount;
	UINT		m_nVideoBranchesCount;
	UINT		m_nAudioBranchesCount;

	// Current stream duration
	REFERENCE_TIME		m_llDuration;

	// Determine current stream duration
	void		DetermineStreamDuration( void );

	// Pages
	CAUUID	m_Pages;
	
	// Create / Destroy graph branches
	virtual HRESULT		CreateBranches( void );
	virtual void				DestroyBranches( void );

	// Rebuild graph
	virtual HRESULT		Rebuild( void );

	// Add filter to filter graph
	virtual HRESULT		AddFilter( CLSID clsFlt, LPWSTR wszFilterName, CDirectShowFilter &filter);

	// Add existent filter into graph
	virtual HRESULT		AddFilter( CDirectShowFilter	 *pFilter );

	// Add sink filter for filter graph
	virtual HRESULT		AddSinkFilter( CLSID clsFlt, LPWSTR wszFilterName, CDirectShowFilter &filter, LPTSTR	tszFile);
	
	// Remove filter from graph but not release it
	virtual HRESULT		RemoveFilter( CDirectShowFilter *pFilter );

	// Render pin
	virtual HRESULT		Render( CDirectShowPin *pPin );

	// Connect pin with filter
	virtual HRESULT		ConnectPinWithFilter( CDirectShowPin *pPin, CDirectShowFilter *pFilter, BOOL bInt = false );

	// Connect two filters
	virtual HRESULT		ConnectFilters( CDirectShowFilter *pUp, CDirectShowFilter *pDown, BOOL bInt = false );

	// Disconnect filter
	virtual HRESULT		DisconnectFilter( CDirectShowFilter *filter );
	// Disconnect pin
	virtual HRESULT		DisconnectPin( CDirectShowPin		*pin );
	// Queries graph interfaces
	virtual HRESULT		QueryInterfaces( void );


	// Add / Remove graph to/ from Running object table
	DWORD		m_dwROT;
	HRESULT	AddToROT( void );
	HRESULT	RemoveFromROT( void );

	// Graph events
	HRESULT	CheckGraphEvents( void );

	// Called on EC_COMPLETE event
	HRESULT	OnComplete( void );

	// Called on EC_ABORT event
	HRESULT	OnAbort( void );

	// Configure ASF Writer filter;
	HRESULT	ConfigureASFWriter( void );
public:

	// Construction / Destruction
	CDirectShowGraph ( void );
	virtual ~CDirectShowGraph ( void );

	// Init / Reset
	HRESULT	Init	( CString szSource, CString szDest, IGraphCallback	*pCallback );
	void	Reset	( void );

	// Start / Cancel graph
	virtual HRESULT		Start	( void );
	virtual HRESULT		Cancel	( void );

	// Show properties of ASF Writer filter
	virtual HRESULT		ShowASFProps		( HWND	hWnd );

	// Returns number of video streams
	HRESULT				GetVideoCount		( UINT	*pCount );
	
	// Returns number of audio streams
	HRESULT				GetAudioCount		( UINT	*pCount );

	// Sets pointer to video settings
	virtual HRESULT		ApplyVideoSettings	( UINT nNum, CVideoSettings	*pVS);

	// Sets pointer to audio settings
	virtual HRESULT		ApplyAudioSettings	( UINT nNum, CAudioSettings	*pAS);

	// Get stream duration
	virtual HRESULT		GetDuration			( LONGLONG	*pllDuration );
	
	// Get current position
	virtual REFERENCE_TIME	GetCurrentPosition( void );

	// Need to index ASF file
	virtual void	IndexASF	( BOOL	bIndex );

	// Need to write output file
	virtual void	WriteLog	( BOOL bWriteLog );

	// Is custom FOUCC for video enabled
	virtual BOOL	AllowCustomFOURCC	( void );
};
