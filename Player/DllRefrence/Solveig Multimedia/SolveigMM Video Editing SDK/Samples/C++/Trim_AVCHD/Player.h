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

#if !defined(AFX_PLAYER_H__4121C5FA_B6E9_4853_83CC_CFFAA2400DA5__INCLUDED_)
#define AFX_PLAYER_H__4121C5FA_B6E9_4853_83CC_CFFAA2400DA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "index.h"
#include  <PropID_EditingEngine.h>
#include  <PropID_AVIWriter.h>


class CPlayer : public CGraphManager  
{
public:
      
	typedef enum
	{
		modeFastBckwrd    = -1,
		modeNormal        =  0,
		modeFastFrwrd     =  1,
	
	} PlaybackModes;
      

	virtual ~CPlayer();
      
	CPlayer(CString slntPath): 
	CGraphManager()
	{
		HRESULT hr;
		m_pIndex = new CIndexEx( slntPath, hr  );
		m_pFilterDemuxer = NULL;
		m_pFilterDecoder = NULL;
		m_ftType = SMM_File_Type_MPEG2_TS;
	}

	HRESULT					SetPosition(REFERENCE_TIME rtPos, REFERENCE_TIME rtEndPos = 0);

	virtual  void			Reset();
	void					ReleaseIndex()
							{
								if( m_pIndex )
									m_pIndex->ReleaseIndexSet();
							}
      
	virtual  HRESULT		Run      ( BOOL bAsync = TRUE );
	virtual  HRESULT		Pause ( BOOL bAsync = TRUE );
	virtual  HRESULT		Stop  ( BOOL bAsync = TRUE );

	HRESULT					Step  ( long lFrames, BOOL bSec = FALSE );
	HRESULT					FastForward ( long lFrames = 1, BOOL bSec = FALSE );
	HRESULT					FastBackward( long lFrames = -1, BOOL bSec = FALSE );
   
	void					SetInput (LPCTSTR tcsFileName);
	LPCTSTR					GetInput() { return m_InputFile.data(); }

	BOOL					IsFullscreenMode  ();
	HRESULT					SetFullscreenMode ( BOOL bSet = TRUE, OAHWND hWnd = 0 );

	virtual STDMETHODIMP	OnEvent           ( long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG );
	HRESULT					ActivateFilter( IBaseFilter* filter );
	operator CIndexEx& ()
	{
		return *m_pIndex;
	}
	HRESULT					SetIndex( CFilterWrapper *pDemuxer, CIndexEx *pIndex );
	void					SetFileType( SMM_OutputTypes ftInput );
protected:

	std::basic_string<TCHAR>m_InputFile;
	CComPtr<IVideoWindow>	m_pIVideoWindow;

	PlaybackModes			m_PlaybackMode;

	REFERENCE_TIME			m_rtFastStep;
	REFERENCE_TIME			m_rtFastPosition;

	virtual HRESULT			CreateFilters();
	virtual HRESULT			OnInitCompleted();

	virtual HRESULT			BuildGraph();
	CIndexEx				*m_pIndex;

	CFilterWrapper			*m_pFilterDemuxer,
							*m_pFilterDecoder;
	SMM_OutputTypes			m_ftType;
      
};

class CTrimGrpah : public CPlayer
{

public:
	CTrimGrpah ( CString slntPath );
	virtual ~ CTrimGrpah ();

	virtual HRESULT			CreateFilters( void );
	virtual HRESULT			OnInitCompleted( void );
	virtual HRESULT			BuildGraph( void );
			HRESULT			BuildGraphGOPAccur( void){};
	virtual HRESULT			QueryInterfaces( void );
	virtual void			ReleaseAllComponents( void );
	virtual void			Reset( void );
   
	virtual HRESULT			Run( BOOL bAsync = TRUE);
	virtual HRESULT			Stop( BOOL bAsync = TRUE);
			HRESULT			StopManual( void );
	virtual STDMETHODIMP OnEvent( long levCode, long lparam1 = MAXLONG, long lparam2 = MAXLONG);
	     
			HRESULT OnInitCompletedGOPAcc( void );
			UINT GetEditEngineProgress( void );

			void SetIndexObj( CIndexEx *IndObj );

	void  SetOutFormat   ( SMM_OutputTypes format)
	{
		m_OutFormat = format;
	}

	SMM_OutputTypes GetOutFormat  ( void )
	{
		return m_OutFormat; 
	}

	void  SetTrimParams  ( __TSTrimInfo &ti )
	{
		m_TrimParamsList.clear();
		m_TrimParamsList.push_back(ti);
	}

	void  SetTrimParams  ( TLTrimInfo &ti )
	{
		m_TrimParamsList.clear();
		m_TrimParamsList = ti;
	}

	TLTrimInfo& GetTrimParams  ( void)
	{
		return m_TrimParamsList;
	}

	void  SetOutput( LPCTSTR tcsFileName )
	{
		m_OutputFN = tcsFileName;
	}
	LPCTSTR  GetOutput() 
	{ 
		if( m_OutputFN.GetAllocLength() ){
			return  m_OutputFN; 
		}
		return NULL;
	}

	REFERENCE_TIME GetMuxerPosition();
	REFERENCE_TIME m_rtListDuration;
	SMM_OutputTypes m_OutFormat;

protected:

	CFilterWrapper			m_FilterSrc;      // source filter
	CFilterWrapper			m_FilterDmp;
	CFilterWrapper			*m_pFilterMuxer;
	CFilterWrapper			m_FilterTrimmer;
   
	CFilterWrapper			m_FilterDmpTestAud;
	CFilterWrapper			m_FilterDmpTestVid;

	CComPtr<IModuleConfig>	m_pConfigTrimmer;
	CComPtr<IModuleConfig>	m_pConfigMuxer;
	CComPtr<IModuleConfig>	m_pConfigDemuxer;
	CComPtr<IModuleConfig>	m_pConfigDmp;

	CString					m_OutputFN;
	TLTrimInfo				m_TrimParamsList;

#ifdef COMPILE_VARIANT_ENGINE_USING
   CComPtr <ITrimmerObjControl> m_pITrimmerObjControl;
   CComPtr <ITrimmerObjControlCB> m_pITrimmerCallBack;
   CComPtr <IModuleConfig>     m_pModuleCfgEditObj;

public:
   void SetNotifyInteface( IEventNotify* pVAl )
   {
   }

   void SetCBInterface( ITrimmerObjControlCB* pCB )
   {
      m_pITrimmerCallBack = pCB;
   }

#endif   
};

#endif // !defined(AFX_PLAYER_H__4121C5FA_B6E9_4853_83CC_CFFAA2400DA5__INCLUDED_)


