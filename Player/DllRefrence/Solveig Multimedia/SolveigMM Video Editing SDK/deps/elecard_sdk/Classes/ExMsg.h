
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

#ifndef _CExMsg_
#define _CExMsg_

#include "Utils.h"

namespace ElUtils
{
	#if  defined(_UNICODE) || defined(UNICODE)
		void ExMsgTrace(LPCWSTR lpszFormat, ...);
	#else
		void ExMsgTrace(LPCSTR lpszFormat, ...);
	#endif

	#define EXC_TRACE ElUtils::ExMsg


	#if  defined(_DEBUG) || defined(DEBUG)
		
		#define	DBG_ETRY	try{

		#define DBG_ECATCH }\
			catch(ElUtils::CExMsg& e){e.DbgOut()} \
			catch(...){}

		#define DBG_ECATCH_THROW(tcsMsg) }\
			catch(ElUtils::CExMsg&){throw;} \
			catch(...){throw CExMsg(tcsMsg);}

		#define DBG_ECATCH_MSG }\
			catch(ElUtils::CExMsg& e){e.DbgMsgBox(); e.DbgOut();} \
			catch(...){}

		#define DBG_ECATCH_HR(hr) }\
			catch(ElUtils::CExMsg& e){hr = e; e.DbgOut();} \
			catch(...){hr = E_FAIL;}

		#define DBG_ECATCH_HR_MSG(hr) }\
			catch(ElUtils::CExMsg& e){hr = e; e.DbgMsgBox(); e.DbgOut();} \
			catch(...){hr = E_FAIL;}

	#else  // _DEBUG
		
		#define	DBG_ETRY	
		#define DBG_ECATCH 
		#define DBG_ECATCH_THROW(tcsMsg)
		#define DBG_ECATCH_MSG 
		#define DBG_ECATCH_HR(hr) 
		#define DBG_ECATCH_HR_MSG(hr) 
	#endif // _DEBUG


	#define ETRY try{
	#define ECATCH }\
		catch(ElUtils::CExMsg& e){e.DbgOut();} \
		catch(...){}

	#define ECATCH_THROW(tcsMsg) }\
		catch(ElUtils::CExMsg&){throw;} \
		catch(...){throw CExMsg(tcsMsg);}

	#define ECATCH_MSG }\
		catch(ElUtils::CExMsg& e){e.MsgBox(); e.DbgOut();} \
		catch(...){}

	#define ECATCH_HR(hr) }\
		catch(ElUtils::CExMsg& e){hr = e;	e.DbgOut();}\
		catch(...){hr = E_FAIL;}

	#define ECATCH_HR_MSG(hr) }\
		catch(ElUtils::CExMsg& e){hr = e;	e.MsgBox();}\
		catch(...){hr = E_FAIL;}

		
	/////////////////////////////////////////////////////////////
	// CException class

	class CExMsg
	{
	public:
		CExMsg(CExMsg& e):
						m_tcsText(e),
						m_hrError(e)
		{
		}

		CExMsg(LPCTSTR tcsMessage):
						m_tcsText(tcsMessage),
						m_hrError(E_FAIL)
		{
		}

		CExMsg(LPCTSTR tcsMessage, HRESULT hr):
						m_tcsText(tcsMessage),
						m_hrError(hr)
		{
		}

		CExMsg(LPCTSTR tcsMessage, DWORD dwWin32Code):
						m_tcsText(tcsMessage),
						m_hrError(HRESULT_FROM_WIN32(dwWin32Code))
		{
		}
		
		virtual void Set(LPCTSTR tcsMessage, HRESULT hr)
		{
			m_tcsText = tcsMessage;
			m_hrError = hr;
		}

		virtual void Reset()
		{
			m_tcsText = _T("");
			m_hrError = S_OK;
		}

		CExMsg& operator =(const CExMsg& e)
		{
			m_tcsText = e.m_tcsText;
			m_hrError = e.m_hrError;
			return *this;
		}

		virtual operator LPCTSTR		() const
		{
			return m_tcsText.data();
		}

		virtual operator HRESULT	() const
		{
			return m_hrError;
		}

		//
		virtual void		DbgOut()
		{
	#if  defined(_DEBUG) || defined(DEBUG)
			try
			{
				OutputDebugString(m_tcsText.data());
			}
			catch(...)
			{
			}
	#endif // _DEBUG
		}

		virtual void		MsgBox(LPCTSTR tcsCaption = _T("Error!"))
		{
	#ifndef	_NO_UI_
			try
			{
				MessageBox(NULL, m_tcsText.data(), tcsCaption, MB_OK|MB_ICONERROR);
			}
			catch(...)
			{
			}
	#endif //	_NO_UI_
		}

		virtual void		DbgMsgBox()
		{
	#if  defined(_DEBUG) || defined(DEBUG)
			MsgBox();
	#endif // _DEBUG
		}
		
	protected:
		std::basic_string<TCHAR>		m_tcsText;
		HRESULT							m_hrError;
	};

}; 

#endif // _CExMag_
