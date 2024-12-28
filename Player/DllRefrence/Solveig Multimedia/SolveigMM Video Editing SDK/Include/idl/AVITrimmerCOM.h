

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Feb 08 12:36:01 2012
 */
/* Compiler settings for ..\..\..\Include\idl\AVITrimmerCOM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AVITrimmerCOM_h__
#define __AVITrimmerCOM_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITrimmerObjControlCB_FWD_DEFINED__
#define __ITrimmerObjControlCB_FWD_DEFINED__
typedef interface ITrimmerObjControlCB ITrimmerObjControlCB;
#endif 	/* __ITrimmerObjControlCB_FWD_DEFINED__ */


#ifndef __ITrimmerObjControl_FWD_DEFINED__
#define __ITrimmerObjControl_FWD_DEFINED__
typedef interface ITrimmerObjControl ITrimmerObjControl;
#endif 	/* __ITrimmerObjControl_FWD_DEFINED__ */


#ifndef ___IXTransformEvents_FWD_DEFINED__
#define ___IXTransformEvents_FWD_DEFINED__
typedef interface _IXTransformEvents _IXTransformEvents;
#endif 	/* ___IXTransformEvents_FWD_DEFINED__ */


#ifndef __TrimmerObjControl_FWD_DEFINED__
#define __TrimmerObjControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrimmerObjControl TrimmerObjControl;
#else
typedef struct TrimmerObjControl TrimmerObjControl;
#endif /* __cplusplus */

#endif 	/* __TrimmerObjControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "moduleconfig.h"
#include "moduleconfigforvb.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITrimmerObjControlCB_INTERFACE_DEFINED__
#define __ITrimmerObjControlCB_INTERFACE_DEFINED__

/* interface ITrimmerObjControlCB */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITrimmerObjControlCB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33968711-8887-46D4-A71B-9B1B061EEDCA")
    ITrimmerObjControlCB : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnStart( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnStop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnError( 
            long hr,
            BSTR Val) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrimmerObjControlCBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrimmerObjControlCB * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrimmerObjControlCB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrimmerObjControlCB * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnStart )( 
            ITrimmerObjControlCB * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnStop )( 
            ITrimmerObjControlCB * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPause )( 
            ITrimmerObjControlCB * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnError )( 
            ITrimmerObjControlCB * This,
            long hr,
            BSTR Val);
        
        END_INTERFACE
    } ITrimmerObjControlCBVtbl;

    interface ITrimmerObjControlCB
    {
        CONST_VTBL struct ITrimmerObjControlCBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrimmerObjControlCB_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrimmerObjControlCB_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrimmerObjControlCB_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrimmerObjControlCB_OnStart(This)	\
    ( (This)->lpVtbl -> OnStart(This) ) 

#define ITrimmerObjControlCB_OnStop(This)	\
    ( (This)->lpVtbl -> OnStop(This) ) 

#define ITrimmerObjControlCB_OnPause(This)	\
    ( (This)->lpVtbl -> OnPause(This) ) 

#define ITrimmerObjControlCB_OnError(This,hr,Val)	\
    ( (This)->lpVtbl -> OnError(This,hr,Val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrimmerObjControlCB_INTERFACE_DEFINED__ */


#ifndef __ITrimmerObjControl_INTERFACE_DEFINED__
#define __ITrimmerObjControl_INTERFACE_DEFINED__

/* interface ITrimmerObjControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITrimmerObjControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9")
    ITrimmerObjControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputFN( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputFN( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputFN( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputFN( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamLength( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartPosition( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartPosition( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopPosition( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopPosition( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            ITrimmerObjControlCB *pITrimmerObjControlCB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrimmerObjControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrimmerObjControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrimmerObjControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrimmerObjControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITrimmerObjControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITrimmerObjControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITrimmerObjControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITrimmerObjControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputFN )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputFN )( 
            ITrimmerObjControl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputFN )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputFN )( 
            ITrimmerObjControl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            ITrimmerObjControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            ITrimmerObjControl * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamLength )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPosition )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPosition )( 
            ITrimmerObjControl * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopPosition )( 
            ITrimmerObjControl * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopPosition )( 
            ITrimmerObjControl * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCallback )( 
            ITrimmerObjControl * This,
            ITrimmerObjControlCB *pITrimmerObjControlCB);
        
        END_INTERFACE
    } ITrimmerObjControlVtbl;

    interface ITrimmerObjControl
    {
        CONST_VTBL struct ITrimmerObjControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrimmerObjControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrimmerObjControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrimmerObjControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrimmerObjControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITrimmerObjControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITrimmerObjControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITrimmerObjControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITrimmerObjControl_get_InputFN(This,pVal)	\
    ( (This)->lpVtbl -> get_InputFN(This,pVal) ) 

#define ITrimmerObjControl_put_InputFN(This,newVal)	\
    ( (This)->lpVtbl -> put_InputFN(This,newVal) ) 

#define ITrimmerObjControl_get_OutputFN(This,pVal)	\
    ( (This)->lpVtbl -> get_OutputFN(This,pVal) ) 

#define ITrimmerObjControl_put_OutputFN(This,newVal)	\
    ( (This)->lpVtbl -> put_OutputFN(This,newVal) ) 

#define ITrimmerObjControl_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define ITrimmerObjControl_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define ITrimmerObjControl_get_Status(This,pVal)	\
    ( (This)->lpVtbl -> get_Status(This,pVal) ) 

#define ITrimmerObjControl_get_StreamLength(This,pVal)	\
    ( (This)->lpVtbl -> get_StreamLength(This,pVal) ) 

#define ITrimmerObjControl_get_StartPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPosition(This,pVal) ) 

#define ITrimmerObjControl_put_StartPosition(This,newVal)	\
    ( (This)->lpVtbl -> put_StartPosition(This,newVal) ) 

#define ITrimmerObjControl_get_StopPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_StopPosition(This,pVal) ) 

#define ITrimmerObjControl_put_StopPosition(This,newVal)	\
    ( (This)->lpVtbl -> put_StopPosition(This,newVal) ) 

#define ITrimmerObjControl_SetCallback(This,pITrimmerObjControlCB)	\
    ( (This)->lpVtbl -> SetCallback(This,pITrimmerObjControlCB) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrimmerObjControl_INTERFACE_DEFINED__ */



#ifndef __AVITRIMMERCOMLib_LIBRARY_DEFINED__
#define __AVITRIMMERCOMLib_LIBRARY_DEFINED__

/* library AVITRIMMERCOMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AVITRIMMERCOMLib;

#ifndef ___IXTransformEvents_DISPINTERFACE_DEFINED__
#define ___IXTransformEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IXTransformEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IXTransformEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DC2117FE-3CCE-476A-992A-CAF7DED33764")
    _IXTransformEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IXTransformEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IXTransformEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IXTransformEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IXTransformEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IXTransformEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IXTransformEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IXTransformEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IXTransformEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IXTransformEventsVtbl;

    interface _IXTransformEvents
    {
        CONST_VTBL struct _IXTransformEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IXTransformEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IXTransformEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IXTransformEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IXTransformEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IXTransformEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IXTransformEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IXTransformEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IXTransformEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TrimmerObjControl;

#ifdef __cplusplus

class DECLSPEC_UUID("B61C3708-CAA8-48CA-9D9C-682D0A5A3852")
TrimmerObjControl;
#endif
#endif /* __AVITRIMMERCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


