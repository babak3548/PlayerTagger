
/////////////////////////////////////////////////////////////////////////////////
//
//	   Copyright (c) 2005 Elecard Ltd.
//	   All rights are reserved.  Reproduction in whole or in part is prohibited
//	   without the written consent of the copyright owner.
//
//	   Elecard Ltd. reserves the right to make changes without
//	   notice at any time. Elecard Ltd. makes no warranty, expressed,
//	   implied or statutory, including but not limited to any implied
//	   warranty of merchantability of fitness for any particular purpose,
//	   or that the use will not infringe any third party patent, copyright
//	   or trademark.
//
//	   Elecard Ltd. must not be liable for any loss or damage arising
//	   from its use.
//
/////////////////////////////////////////////////////////////////////////////////


#ifndef _COMPONENT_MANAGER_
#define _COMPONENT_MANAGER_

#include "AutoApartment.h"

#include "Utils.h"
#include "Elements.h"

#define		EC_ALL					EC_USER + 1
#define		EC_START				EC_USER + 2
#define		EC_STOP					EC_USER + 3
#define		EC_IDLE					EC_USER + 4
#define		EC_STATECHANGED			EC_USER + 5

#define		DEFAULT_IDLE_TIMEOUT	100				// 100 ms
#define		DEFAULT_WAIT_TIMEOUT	2000			

#define		ONE_SEC					10000000

#define		ERROR_MESSAGE(hr, msg) {\
										m_erMessage = msg;\
										return m_hrError = hr;\
									}

class CPinWrapper;
class CFilterWrapper;

////////////////////////////////////////////////////////////////////////////////
//
//

typedef enum _tagTEGraphState
{
	graphStopped			= State_Stopped,
	graphPaused				= State_Paused,
	graphRunning			= State_Running,
	graphPausedNotPushing	= 0x10,
	graphIntermediate		= 0x20,
	graphNone				= 0x30,
	graphError				= 0x40,
		
} GraphState;

////////////////////////////////////////////////////////////////////////////////
//
//

DECLARE_INTERFACE(IEventNotify)
{
	STDMETHOD(OnEvent)(long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG) = 0;
};


////////////////////////////////////////////////////////////////////////////////
//
//

class CStateManager
{
	public:		
		
		CStateManager(IMediaControl* pMC, IMediaEventEx* pME);
		~CStateManager();

		GraphState				GetGraphState(LONG msTimeout = 0)  const;
		GraphState				CurrentGraphState();

		void					Reset();

		virtual void			ReleaseInterface();
		virtual HRESULT			UpdateInterface(IMediaControl* pMC, IMediaEventEx* pME); //IGraphBuilder* pGraphBuilder = NULL);

		HRESULT					SubscribeEvent(long evCode, IEventNotify* pNotify);
		UINT					UnSubscribeEvent(long evCode, IEventNotify* pNotify);

		virtual void			Run()	{ SetInternalEvent(stateRun);	}
		virtual void			Pause() { SetInternalEvent(statePause); }
		virtual void			Stop()	{ SetInternalEvent(stateStop);	}

		HRESULT					PurgeEventQueue();
		HRESULT					GetEvent(LPLONG plEvCode, LONG lTimeout = 0, LPLONG plParam1 = NULL, LPLONG plParam2 = NULL);
		HRESULT					WaitForEvent(LONG lEvCode, LONG lTimeout = 0, LPLONG plParam1 = NULL, LPLONG plParam2 = NULL);		
		void					WaitForOperationCompleted();		

		virtual HRESULT			SetEvent(long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG);

		void					EnableEventThread(BOOL bSet = TRUE);
		void					CreateThreads();
		
		ElUtils::CW32CritSec&	CritSec()
		{
			return	m_CritSec;
		}

		BOOL					IsExit()
		{
			return m_Event[stateExit].IsSet();
		}

	private:

		typedef enum 
		{
			stateStop	= 0,
			statePause,
			stateRun,
			stateExit,
			stateNum
			
		} StateEvent;

		typedef struct TSEventMsg
		{
			long	evCode;
			long	lParam1;
			long	lParam2;

			TSEventMsg(long eCode = 0, long lprm1 = MAXLONG, long lprm2 = MAXLONG) 
				: evCode(eCode), lParam1(lprm1), lParam2(lprm2){};
		};
		
		typedef std::multimap<long, IEventNotify*>	TMMEvent;
		typedef TMMEvent::iterator					TIMMEvent;
		typedef std::list<TSEventMsg*>				TLEventMsg;
		
		TMMEvent						m_SubscribeEvent;
		TLEventMsg						m_EventMsgList;

		ElUtils::CW32Event				m_Event[stateNum];
		ElUtils::CW32Event				m_EventMsg;
		ElUtils::CW32Event				m_EventExit;

		BOOL							m_bEventThread;

		BOOL					FindInRange(TIMMEvent first, TIMMEvent last, IEventNotify* value, TIMMEvent* it);
		void					SetInternalEvent(StateEvent event);				

	protected:

		virtual HRESULT			OnStart();
		virtual HRESULT			OnPause();
		virtual HRESULT			OnStop();
		virtual HRESULT			OnIdle();
		
		virtual void			OnEvent();

		static	DWORD CALLBACK	ThreadHelper(LPVOID pArg);
		HRESULT					ThreadProc();

		static	DWORD CALLBACK	EventThreadHelper(LPVOID pArg);
		HRESULT					EventThreadProc();

		HRESULT					StopThread(DWORD dwTimeout = 1000);
		
		virtual HRESULT			OnStartThread();
		virtual HRESULT			OnExitThread();						

		CComPtr<IMediaControl>			m_pIMC;
		CComPtr<IMediaEventEx>			m_pIME;
		
		HANDLE							m_hThread;
		HANDLE							m_hEventThread;
		
		GraphState						m_currGraphState;		
		
		mutable ElUtils::CW32CritSec	m_CritSec;
		mutable ElUtils::CW32CritSec	m_csEvent;
		mutable ElUtils::CW32CritSec	m_csSubscribe;
		mutable ElUtils::CW32CritSec	m_csThread;
};

////////////////////////////////////////////////////////////////////////////////
// 
//		CBaseGraph class 

class CBaseGraph	:	public CComPtr<IGraphBuilder>
{
	public :

		CBaseGraph();
		CBaseGraph(IGraphBuilder* pGB);
		CBaseGraph(CBaseGraph& pBG);
		~CBaseGraph();

		////////////////////////////////////////////////////////////////////////
		// operators

		typedef	BOOL		(__stdcall* CFA)(IBaseFilter*);

		UINT				FiltersCount(CFA f = 0);
		CFilterWrapper		GetFilter(UINT n, CFA f = 0);

		typedef std::deque<CFilterWrapper> CListOfFilters;	
		UINT				GetFiltersList(CListOfFilters& list, CFA f = 0);

		////////////////////////////////////////////////////////////////////////
		// operators

		CBaseGraph&	operator = (IGraphBuilder*  pGraph);
		CBaseGraph&	operator = (const CBaseGraph&  pGraph);

		operator IGraphBuilder*()	const
		{
			return	p;
		}

		CBaseGraph*		Ptr()
		{
			return this;
		}

		////////////////////////////////////////////////////////////////////////
		// 

		virtual HRESULT		Init();
		virtual void		Reset();

		BOOL				IsInitialized();

		////////////////////////////////////////////////////////////////////////
		// Build & remove graph components functions

		HRESULT				AddFilter(CFilterWrapper& filter, LPCWSTR wcsFilterName);
		HRESULT				AddFilter(REFCLSID clsid, LPCWSTR wcsFilterName, CFilterWrapper* pFilter = NULL);
		HRESULT				AddFilter(REFCLSID clsid, LPCWSTR wcsFilterName, LPOLESTR lcsFilePath, CFilterWrapper* pFilter = NULL);		

#ifndef _UNICODE
		HRESULT				AddFilter(CFilterWrapper& filter, LPCTSTR tcsFilterName);		
		HRESULT				AddFilter(REFCLSID clsid, LPCTSTR tcsFilterName, CFilterWrapper* pFilter = NULL);
		HRESULT				AddFilter(REFCLSID clsid, LPCTSTR tcsFilterName, LPOLESTR lcsFilePath, CFilterWrapper* pFilter = NULL);		
#endif

#if !defined UNDER_CE			
		HRESULT				AddFilter(LPCWSTR wcsFriendlyName, LPCWSTR wcsFilterName, CFilterWrapper* pFilter = NULL);		
		HRESULT				AddFilter(LPCWSTR wcsFriendlyName, const CLSID& clsDeviceCategory, LPCWSTR wcsFilterName, CFilterWrapper* pFilter = NULL);

#ifndef _UNICODE
		HRESULT				AddFilter(LPCWSTR wcsFriendlyName, LPCTSTR tcsFilterName, CFilterWrapper* pFilter = NULL);		
		HRESULT				AddFilter(LPCWSTR wcsFriendlyName, const CLSID& clsDeviceCategory, LPCTSTR tcsFilterName, CFilterWrapper* pFilter = NULL);		
#endif
#endif

#ifndef _UNICODE
		HRESULT				AddFilterSource(CFilterWrapper& filter, LPCTSTR tcsFilterName, LPCTSTR tcsInputFN);
		HRESULT				AddFilterSource(LPCTSTR tcsFilterName, LPCTSTR tcsInputFN, CFilterWrapper* pFilter = NULL);
		HRESULT 			AddFilterSource(REFCLSID clsid, LPCTSTR tcsFilterName, LPCTSTR tcsInputFN, CFilterWrapper* pFilter = NULL);
		HRESULT 			AddFilterSource(REFCLSID clsid, LPCTSTR tcsFilterName, LPCTSTR tcsInputFN, 
			LPCTSTR tcsFilePath, CFilterWrapper* pFilter = NULL);
#endif

		HRESULT				AddFilterSource(CFilterWrapper& filter, LPCWSTR wcsFilterName, LPCWSTR wcsInputFN);		
		HRESULT				AddFilterSource(LPCWSTR wcsFilterName, LPCWSTR wcsInputFN, CFilterWrapper* pFilter = NULL);		
		HRESULT 			AddFilterSource(REFCLSID clsid, LPCWSTR wcsFilterName, LPCWSTR wcsInputFN, CFilterWrapper* pFilter = NULL);
		HRESULT 			AddFilterSource(REFCLSID clsid, LPCWSTR wcsFilterName, LPCWSTR wcsInputFN, 
			LPOLESTR lcsFilePath, CFilterWrapper* pFilter = NULL);

#if !defined UNDER_CE
#ifndef _UNICODE
		HRESULT 			AddFilterSource(LPCWSTR wcsFriendlyName, LPCTSTR tcsFilterName, LPCTSTR tcsInputFN, CFilterWrapper* pFilter = NULL);
#endif
		HRESULT 			AddFilterSource(LPCWSTR wcsFriendlyName, LPCWSTR wcsFilterName, LPCWSTR wcsInputFN, CFilterWrapper* pFilter = NULL);		
#endif

#ifndef _UNICODE
		HRESULT				AddFilterSink(CFilterWrapper& filter, LPCTSTR tcsFilterName, LPCTSTR tcsOutputFN);
		HRESULT 			AddFilterSink(REFCLSID clsid, LPCTSTR tcsFilterName, LPCTSTR tcsOutputFN, CFilterWrapper* pFilter = NULL);
		HRESULT 			AddFilterSink(REFCLSID clsid, LPCTSTR tcsFilterName, LPCTSTR tcsOutputFN, 
			LPCTSTR tcsFilePath, CFilterWrapper* pFilter = NULL);
#endif

		HRESULT				AddFilterSink(CFilterWrapper& filter, LPCWSTR wcsFilterName, LPCWSTR wcsOutputFN);		
		HRESULT 			AddFilterSink(REFCLSID clsid, LPCWSTR wcsFilterName, LPCWSTR wcsOutputFN, CFilterWrapper* pFilter = NULL);		
		HRESULT 			AddFilterSink(REFCLSID clsid, LPCWSTR wcsFilterName, LPCWSTR wcsOutputFN, 
			LPOLESTR lcsFilePath, CFilterWrapper* pFilter = NULL);		


#if !defined UNDER_CE
#ifndef _UNICODE
		HRESULT 			AddFilterSink(LPCWSTR wcsFriendlyName, LPCTSTR tcsFilterName, LPCTSTR tcsOutputFN, CFilterWrapper* pFilter = NULL);
#endif
		HRESULT 			AddFilterSink(LPCWSTR wcsFriendlyName, LPCWSTR wcsFilterName, LPCWSTR wcsOutputFN, CFilterWrapper* pFilter = NULL);		
#endif

		HRESULT				AddFilterDMO(REFCLSID clsid, REFCLSID clsDMOCategory, LPCTSTR tcsFilterName, CFilterWrapper* pDMOFilter = NULL);
		HRESULT				AddFilterDMO(REFCLSID clsid, REFCLSID clsDMOCategory, LPCTSTR tcsFilterName, LPCTSTR tcsFilePath, CFilterWrapper* pDMOFilter = NULL);

#ifndef _UNICODE
		HRESULT				AddFilterDMO(REFCLSID clsid, REFCLSID clsDMOCategory, LPCWSTR wcsFilterName, CFilterWrapper* pDMOFilter = NULL);
		HRESULT				AddFilterDMO(REFCLSID clsid, REFCLSID clsDMOCategory, LPCWSTR wcsFilterName, 
			LPOLESTR lcsFilePath, CFilterWrapper* pDMOFilter = NULL);
#endif

		virtual HRESULT		ConnectOutPinWithFilter(CPinWrapper& OutPin, CFilterWrapper& Filter, BOOL bIntelligent = FALSE);
		virtual HRESULT		ConnectFiltersDirectly(CFilterWrapper& OutFilter, CFilterWrapper& InFilter, BOOL bIntelligent = FALSE);

		HRESULT				DestroyToDown(CPinWrapper& pin);
		HRESULT				RemoveNotConnectedFilters();

		virtual void		RemoveAllComponents();	

		////////////////////////////////////////////////////////////////////////
		//

		HRESULT				FindFilterByNameFromOutPin(CPinWrapper& out_pin, LPCTSTR sFName, CFilterWrapper& filter);

		//////////////////////////////////////////////////////////////////////////
		// Error functions

		HRESULT				GetLastError(LPTSTR tcsMsg = NULL);

	protected:

		BOOL							m_bInitialized;

		HRESULT							m_hrError;
		CTBString						m_erMessage;
		mutable ElUtils::CW32CritSec	m_csError;

		virtual void		ReleaseAllComponents();	
		HRESULT				SetFileNameToSinkFilter(CFilterWrapper& filter, LPCWSTR wcsOutputFN);

};

////////////////////////////////////////////////////////////////////////////////
// 
//		CGraphManager class 

class CGraphManager :	public CBaseGraph 
					,	public IEventNotify
{
	public:
		
		CGraphManager();
		CGraphManager(IGraphBuilder* pGB);
		CGraphManager(CGraphManager& pGM);
		
		~CGraphManager();

		////////////////////////////////////////////////////////////////////////
		//
		
		HRESULT				AddToROT();
		HRESULT				RemoveFromROT();

		////////////////////////////////////////////////////////////////////////
		// operators

		CGraphManager&	operator = (IGraphBuilder*  pGraph);
		CGraphManager&	operator = (const CGraphManager&  pGraph);

		operator IMediaSeeking*()	const
		{
			return	m_pIMS;
		}

		/////////////////////////////////////////////////////////////////////////
		//

		virtual HRESULT		Init();
		virtual void		Reset();

		////////////////////////////////////////////////////////////////////////
		// Build & remove graph components functions		

		virtual void		RemoveAllComponents();	
		
		/////////////////////////////////////////////////////////////////////////
		// State & notification functions

		virtual HRESULT		Run(BOOL bSynCall = TRUE);
		virtual HRESULT		Pause(BOOL bSynCall = TRUE);
		virtual HRESULT		Stop(BOOL bSynCall = TRUE);		
		virtual HRESULT		StopWhenReady();

		GraphState			GetGraphState(LONG msTimeout = 0);
		GraphState			CurrentGraphState();
		
		HRESULT				SubscribeEvent(long evCode, IEventNotify* pNotify);
		UINT				UnSubscribeEvent(long evCode, IEventNotify* pNotify);
		
		HRESULT				GetEvent(LPLONG plEvCode, LONG lTimeout = 0, LPLONG plParam1 = NULL, LPLONG plParam2 = NULL);
		void				WaitForOperationCompleted();
		
		void				EnableEventThread(BOOL bSet = TRUE) { m_pStateThread->EnableEventThread(bSet); }

		virtual STDMETHODIMP	OnEvent(long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG);		

		//////////////////////////////////////////////////////////////////////////
		// Position function

		REFERENCE_TIME		GetDuration();
		REFERENCE_TIME		GetPosition();

	private:

		enum PlaybackEvent
		{
			evStop	= 0,
			evPause,
			evRun,
			evStateChanged,
			evNum			
		} ;

		ElUtils::CW32Event				m_Playback[evNum];
		DWORD							m_dwROT;	

	protected:	

		CStateManager*					m_pStateThread;	

		CComPtr<IMediaSeeking>			m_pIMS;
		CComPtr<IMediaControl>			m_pIMC;
		CComPtr<IMediaEventEx>			m_pIME;

		////////////////////////////////////////////////////////////////////////
		//
		
		virtual HRESULT		QueryInterfaces();
		virtual HRESULT		CreateFilters()		{ return S_OK;	}
		virtual HRESULT		OnInitCompleted();
		
};

#endif //_COMPONENT_MANAGER_

