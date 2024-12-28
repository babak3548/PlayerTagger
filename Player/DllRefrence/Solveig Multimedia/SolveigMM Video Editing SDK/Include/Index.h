////////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2004-2010 Solveig Multimedia
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
//
////////////////////////////////////////////////////////////////////////////////
//
// Index.h: interface for the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEX_H__7830256F_7F96_4500_AF98_ED732E946ED7__INCLUDED_)
#define AFX_INDEX_H__7830256F_7F96_4500_AF98_ED732E946ED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <atlbase.h>	// ATL helpers
#include <mpgindexator.h>
#include <mediaindexdef.h>
#include <strmif.h>

class CIndex : public CComPtr< IMIxReader2 >
{
	public:
		CIndex ( LPCTSTR tcsIndexFileName);
		CIndex ( SAFEARRAY * psa);
		CIndex ( );
		virtual ~CIndex();
		
		CIndex (HRESULT *phr,  CString str_err, LPCTSTR tcsIndexFileName );

		LPCWSTR			GetMediaFileName() const;
		IMediaIndex*	GetFrameIndex(int streamNum = 0);


		static BOOL		IsMLMIX(LPCTSTR tcsIndexFileName);

	protected:
		CComBSTR		m_bstrMediaFileName;
};

class CIndexEx : public CIndex	
{
public:
	
	CIndexEx(SAFEARRAY * psa):
	  CIndex(psa)
	  {}
	  
	  CIndexEx ( )
	  {};

	  CIndexEx(LPCTSTR tcsIndexFileName):
	  CIndex(tcsIndexFileName)
	  {}
	  
	  CIndexEx( HRESULT *phr, CString str_err , LPCTSTR tcsIndexFileName):
	  CIndex(phr, str_err,tcsIndexFileName)
	  {
	  }

	  CIndexEx( LPCTSTR slntPath, HRESULT &hr  );
	  CIndexEx( LPCTSTR slntPath, LPCTSTR tcsIndexFileName, HRESULT &hr  );
	  
	  //Object is locking the handle to an index file until it has got another index.
	  //This function releases the previously set index file.
	  void ReleaseIndexSet( void )
	  {
		  if(p)
		  HRESULT hr = p->put_IndexFileName(L":"/*L""*/);
	  }
	  HRESULT GetNextIFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta);
	  HRESULT GetNextFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta);
	  
};

class CIndexReader : public CIndexEx
{
public:
	CIndexReader ( ):
	m_bInited(FALSE),
	m_llCurrFrame(0),
	m_rtTimeStamp(0)
	{ };
	virtual ~CIndexReader(){ };

	CIndexReader( HRESULT *phr, CString str_err , LPCTSTR tcsIndexFileName):
	CIndexEx(phr, str_err,tcsIndexFileName),
	m_bInited(FALSE),
	m_llCurrFrame(0),
	m_rtTimeStamp(0)
	{ };

	HRESULT SetIndexFN		( CString fn );

	HRESULT GetNextIFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta)
	{
		return  IsIndexLoaded() ? 
				CIndexEx:: GetNextIFrameTime( CurrentFrameNum, pOutRT, direction, delta ): 
				E_FAIL ;
	}
	HRESULT GetNextFrameTime(const LONGLONG &CurrentFrameNum, REFERENCE_TIME *pOutRT, const int direction, const UINT delta)
	{
		return  IsIndexLoaded() ? 
				CIndexEx:: GetNextFrameTime( CurrentFrameNum, pOutRT, direction, delta ): 
				E_FAIL ;
	}
	REFERENCE_TIME FindFrameInIndex( REFERENCE_TIME rtTime );

	BOOL	IsIndexLoaded	( void )
	{
		return m_bInited;
	}

protected:

	

	BOOL			m_bInited;
	LONGLONG		m_llCurrFrame;
	REFERENCE_TIME	m_rtTimeStamp;
};
#endif // !defined(AFX_INDEX_H__7830256F_7F96_4500_AF98_ED732E946ED7__INCLUDED_)


