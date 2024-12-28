//---------------------------------------------------------------------------/
//	created:	2007/04/24
//	file base:	graph.h
//
//	Copyright (c) 2007-2012 Solveig Multimedia
//	All rights are reserved.  Reproduction in whole or in part is prohibited
//	without the written consent of the copyright owner.
//	
//	Solveig Multimedia reserves the right to make changes without
//	notice at any time. Solveig Multimedia makes no warranty,
//	expressed, implied or statutory, including but not limited to any implied
//	warranty of merchantability of fitness for any particular purpose, or that
//	the use will not infringe any third party patent, copyright or trademark.
//	Solveig Multimedia must not be liable for any loss or damage
//	arising from its use.
//
//-------------------------------------------------------------------------------

// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__3D1C7D93_2C82_4B79_B947_2BBC51A419A2__INCLUDED_)
#define AFX_GRAPH_H__3D1C7D93_2C82_4B79_B947_2BBC51A419A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define JIF(x) if (FAILED(hr=(x))) \
    {return hr;}


struct Params
{
	CString in_fn;
	CString out_fn;
	TrimInfoList trim_param;
	BOOL bParamsFilled;
};


class CGraph  
{
	
public:
	void just();
	
	void SetParams( Params params )
	{
		m_params = params;
	}
	
	int GetProgress()
	{
		CComVariant val = 0;
		if( m_pTrimmerConf ){
			HRESULT hr = m_pTrimmerConf->GetValue(&SMAT_Progress, &val);
		}

		return (int)val.lVal;
	}

	HRESULT		Init();
	HRESULT		Start(DWORD dwTimeout = 0);
	
	HRESULT		Stop();
	void		Deinit();
	BOOL		WaitForStop();

	HRESULT		ConnectFilters(void);
		
	CGraph(HRESULT *phr);
	CGraph();
	virtual ~CGraph();

protected:
	HRESULT			ShowProps(IBaseFilter *pFilter, HWND hwdn);

	
	HRESULT			AddFilters();
	HRESULT			RemoveAllFilters();
	
	IPin*			GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir,bool Free);
	IPin*			GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir,bool Free, REFCLSID MajorType,REFCLSID Subtype = MEDIASUBTYPE_NULL);
	IPin*			GetPin(PIN_DIRECTION PinDir,bool Free, REFCLSID MajorType,REFCLSID  Subtype);
	
	HRESULT			ConnectFilters		( IBaseFilter *pUpFilt,IBaseFilter *pDnFilt );
	HRESULT			ConnectPin2Filter	( IPin *pUpPin, IBaseFilter *pDnFilt );

	_FilterState	GetGraphState();
	IBaseFilter *	GetFilterByGuid(REFCLSID FilterGuid);
	BOOL			IsConnected(IPin* pPin);
	BOOL			IsInPinAcceptsMediaType(IPin* pPin,CMediaType *pmt);
	BOOL			IsOutPinAcceptsMediaType(IPin* pPin,CMediaType *pmt);
	
	static LRESULT CALLBACK DefWindowProcThunk	( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	void					OnGraphNotifyEvent	( UINT uMsg, long wParam, long lParam );

	CComPtr<IGraphBuilder>		m_pGraph;
    CComPtr<IMediaControl>		m_pControl;
	CComPtr<IMediaEventEx>		m_pEventEx;


	CComPtr<IBaseFilter>	m_pFilesSrc;
	CComPtr<IBaseFilter>	m_pTrimmer;
	CComPtr<IBaseFilter>	m_pAVISplitter;
	CComPtr<IBaseFilter>	m_pFileWriter;
	CComPtr<IBaseFilter>	m_pAVIMuxer;

	CComPtr<IModuleConfig>   m_pTrimmerConf;
	
	Params	m_params;
	BOOL	m_bGraphCompleted;
	HWND	m_hWnd; // window to be notified of graph messages
};

#endif // !defined(AFX_GRAPH_H__3D1C7D93_2C82_4B79_B947_2BBC51A419A2__INCLUDED_)
