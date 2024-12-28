#pragma once

#ifndef AVI_DLL
#define LIB_API __declspec(dllimport)
#else
#define LIB_API __declspec(dllexport)
#endif

LIB_API HRESULT	OpenAVIStream		( BSTR bstFileName, LPVOID pInstance );
LIB_API BSTR	ChooseEncoder		( /*void*/LPVOID pInstance );
LIB_API HRESULT SetStreamProperties	( LONG lHeight, LONG lWidth, LONGLONG llFrameDuration, LPVOID pInstance );
LIB_API HRESULT WriteImage			( HBITMAP hInputBitmap, LPVOID pInstance );
LIB_API HRESULT CloseAVIStream		( BOOL bTerminate, LPVOID pInstance );
LIB_API HRESULT	GetAVIFileInfo		( BYTE* Params, LPVOID pInstance );
LIB_API BYTE*	ReadImageFromStream	( LONGLONG llFrame, LONG*plTotalBytes, LPVOID pInstance );
LIB_API void	FreeImage			( BYTE* pBuffer, LPVOID pInstance );
LIB_API LPVOID	CreateNewStream		( void );
LIB_API void	ReleaseStream		( LPVOID pInstance );


class CInternalGraph
{
public:


	CInternalGraph(HINSTANCE);
	virtual ~CInternalGraph(void);
	
	CString m_csFileName;
	//IGraphBuilder interface of the graph
	CComPtr<IGraphBuilder>	m_pGraph;
	//IMediaControl interface of the graph
	CComPtr<IMediaControl>	m_pControl;
	//SourceFilter's interface
										
	CComPtr<IBaseFilter>	m_pSource,
	//Grabber Interface
							m_pGrabber,
	//Muxer's interface
							m_pMuxer,
	//Encoder's Interface						
							m_pEncoder,
	//FileWriter's interface				
							m_pDump,
	//AviSplitter for existing files
							m_pDemuxer;
	//IModuleConfig interface to tune the source filter
	CComPtr<IModuleConfig>	m_pSourceIMC;
	//Are we trying to open existing file
	BOOL					m_bExisting,
	//Is the stream already opened
							m_bOpened;
	HWND					m_hWnd;
	HINSTANCE				m_pParentInst;
	BSTR					m_bstName;



	HRESULT OpenAVIStreamIn( BSTR bstFileName );
	HRESULT InitFilters( BOOL bExistingFile = FALSE );
	HRESULT DestroyGraph();
	BSTR	ChooseTheEncoder( CString& Preferred );
	HRESULT	SetStreamProps( LONG lHeight, LONG lWidth, LONGLONG llFrameDuration );
	HRESULT BuildGraph( BOOL bExistingFile );
	HRESULT ConnectFilters( IBaseFilter *pUpstream, IBaseFilter *pDownstream );
	HRESULT WriteImageToAvi( HBITMAP hImage );
	HRESULT CloseStream( BOOL bTerminate );
	IPin*	GetExactPin( HRESULT *hr, IBaseFilter *pOwnerFilter, BOOL IsAudioPin, BOOL IsOutputPin, BOOL IsConnected );
	HRESULT	ReadProperties( StreamParameters *Props );
	void	DeleteImageBuffer( /*BYTE**/char* pBuffer );
	BYTE*	ReadImage( LONGLONG llFrame, LONG* plTotalBytes );



};
