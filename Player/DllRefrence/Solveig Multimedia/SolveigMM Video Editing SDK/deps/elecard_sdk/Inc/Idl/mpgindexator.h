

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Nov 17 17:40:33 2010
 */
/* Compiler settings for .\Inc\Idl\mpgindexator.idl:
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

#ifndef __mpgindexator_h__
#define __mpgindexator_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMpgFileIndexator_FWD_DEFINED__
#define __IMpgFileIndexator_FWD_DEFINED__
typedef interface IMpgFileIndexator IMpgFileIndexator;
#endif 	/* __IMpgFileIndexator_FWD_DEFINED__ */


#ifndef __IMpgFileIndexator2_FWD_DEFINED__
#define __IMpgFileIndexator2_FWD_DEFINED__
typedef interface IMpgFileIndexator2 IMpgFileIndexator2;
#endif 	/* __IMpgFileIndexator2_FWD_DEFINED__ */


#ifndef __MpgFileIndexator_FWD_DEFINED__
#define __MpgFileIndexator_FWD_DEFINED__

#ifdef __cplusplus
typedef class MpgFileIndexator MpgFileIndexator;
#else
typedef struct MpgFileIndexator MpgFileIndexator;
#endif /* __cplusplus */

#endif 	/* __MpgFileIndexator_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMpgFileIndexator_INTERFACE_DEFINED__
#define __IMpgFileIndexator_INTERFACE_DEFINED__

/* interface IMpgFileIndexator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMpgFileIndexator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8D55DA48-9053-4abc-ABC7-0ED781B779CC")
    IMpgFileIndexator : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputMediaFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputMediaFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamsDetected( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TypeOfStream( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputIndexFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputIndexFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SaveRelativePath( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IndexTypeGUID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexTypeGUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartIndexing( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelIndexing( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AccessUnitsProcessed( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OperationStatus( 
            /* [retval][out] */ HRESULT *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMpgFileIndexatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMpgFileIndexator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMpgFileIndexator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMpgFileIndexator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMpgFileIndexator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMpgFileIndexator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMpgFileIndexator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMpgFileIndexator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputMediaFile )( 
            IMpgFileIndexator * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputMediaFile )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamsDetected )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TypeOfStream )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputIndexFile )( 
            IMpgFileIndexator * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputIndexFile )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SaveRelativePath )( 
            IMpgFileIndexator * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IndexTypeGUID )( 
            IMpgFileIndexator * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexTypeGUID )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartIndexing )( 
            IMpgFileIndexator * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CancelIndexing )( 
            IMpgFileIndexator * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Progress )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AccessUnitsProcessed )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OperationStatus )( 
            IMpgFileIndexator * This,
            /* [retval][out] */ HRESULT *pVal);
        
        END_INTERFACE
    } IMpgFileIndexatorVtbl;

    interface IMpgFileIndexator
    {
        CONST_VTBL struct IMpgFileIndexatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMpgFileIndexator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMpgFileIndexator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMpgFileIndexator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMpgFileIndexator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMpgFileIndexator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMpgFileIndexator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMpgFileIndexator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMpgFileIndexator_put_InputMediaFile(This,newVal)	\
    (This)->lpVtbl -> put_InputMediaFile(This,newVal)

#define IMpgFileIndexator_get_InputMediaFile(This,pVal)	\
    (This)->lpVtbl -> get_InputMediaFile(This,pVal)

#define IMpgFileIndexator_get_StreamsDetected(This,pVal)	\
    (This)->lpVtbl -> get_StreamsDetected(This,pVal)

#define IMpgFileIndexator_get_TypeOfStream(This,pVal)	\
    (This)->lpVtbl -> get_TypeOfStream(This,pVal)

#define IMpgFileIndexator_put_OutputIndexFile(This,newVal)	\
    (This)->lpVtbl -> put_OutputIndexFile(This,newVal)

#define IMpgFileIndexator_get_OutputIndexFile(This,pVal)	\
    (This)->lpVtbl -> get_OutputIndexFile(This,pVal)

#define IMpgFileIndexator_put_SaveRelativePath(This,newVal)	\
    (This)->lpVtbl -> put_SaveRelativePath(This,newVal)

#define IMpgFileIndexator_put_IndexTypeGUID(This,newVal)	\
    (This)->lpVtbl -> put_IndexTypeGUID(This,newVal)

#define IMpgFileIndexator_get_IndexTypeGUID(This,pVal)	\
    (This)->lpVtbl -> get_IndexTypeGUID(This,pVal)

#define IMpgFileIndexator_StartIndexing(This)	\
    (This)->lpVtbl -> StartIndexing(This)

#define IMpgFileIndexator_CancelIndexing(This)	\
    (This)->lpVtbl -> CancelIndexing(This)

#define IMpgFileIndexator_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IMpgFileIndexator_get_AccessUnitsProcessed(This,pVal)	\
    (This)->lpVtbl -> get_AccessUnitsProcessed(This,pVal)

#define IMpgFileIndexator_get_OperationStatus(This,pVal)	\
    (This)->lpVtbl -> get_OperationStatus(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_put_InputMediaFile_Proxy( 
    IMpgFileIndexator * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMpgFileIndexator_put_InputMediaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_InputMediaFile_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMpgFileIndexator_get_InputMediaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_StreamsDetected_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMpgFileIndexator_get_StreamsDetected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_TypeOfStream_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMpgFileIndexator_get_TypeOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_put_OutputIndexFile_Proxy( 
    IMpgFileIndexator * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMpgFileIndexator_put_OutputIndexFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_OutputIndexFile_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMpgFileIndexator_get_OutputIndexFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_put_SaveRelativePath_Proxy( 
    IMpgFileIndexator * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IMpgFileIndexator_put_SaveRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_put_IndexTypeGUID_Proxy( 
    IMpgFileIndexator * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMpgFileIndexator_put_IndexTypeGUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_IndexTypeGUID_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMpgFileIndexator_get_IndexTypeGUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_StartIndexing_Proxy( 
    IMpgFileIndexator * This);


void __RPC_STUB IMpgFileIndexator_StartIndexing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_CancelIndexing_Proxy( 
    IMpgFileIndexator * This);


void __RPC_STUB IMpgFileIndexator_CancelIndexing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_Progress_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMpgFileIndexator_get_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_AccessUnitsProcessed_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMpgFileIndexator_get_AccessUnitsProcessed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator_get_OperationStatus_Proxy( 
    IMpgFileIndexator * This,
    /* [retval][out] */ HRESULT *pVal);


void __RPC_STUB IMpgFileIndexator_get_OperationStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMpgFileIndexator_INTERFACE_DEFINED__ */


#ifndef __IMpgFileIndexator2_INTERFACE_DEFINED__
#define __IMpgFileIndexator2_INTERFACE_DEFINED__

/* interface IMpgFileIndexator2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMpgFileIndexator2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D452FE92-6EB7-4503-99E5-4C4C26AB3E35")
    IMpgFileIndexator2 : public IMpgFileIndexator
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitIndexingComplete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ContinueIndexing( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetIndexingBaseTime( 
            LONGLONG rtBaseTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMpgFileIndexator2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMpgFileIndexator2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMpgFileIndexator2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMpgFileIndexator2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMpgFileIndexator2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMpgFileIndexator2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMpgFileIndexator2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMpgFileIndexator2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputMediaFile )( 
            IMpgFileIndexator2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputMediaFile )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamsDetected )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TypeOfStream )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputIndexFile )( 
            IMpgFileIndexator2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputIndexFile )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SaveRelativePath )( 
            IMpgFileIndexator2 * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IndexTypeGUID )( 
            IMpgFileIndexator2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexTypeGUID )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartIndexing )( 
            IMpgFileIndexator2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CancelIndexing )( 
            IMpgFileIndexator2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Progress )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AccessUnitsProcessed )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OperationStatus )( 
            IMpgFileIndexator2 * This,
            /* [retval][out] */ HRESULT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitIndexingComplete )( 
            IMpgFileIndexator2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ContinueIndexing )( 
            IMpgFileIndexator2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetIndexingBaseTime )( 
            IMpgFileIndexator2 * This,
            LONGLONG rtBaseTime);
        
        END_INTERFACE
    } IMpgFileIndexator2Vtbl;

    interface IMpgFileIndexator2
    {
        CONST_VTBL struct IMpgFileIndexator2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMpgFileIndexator2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMpgFileIndexator2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMpgFileIndexator2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMpgFileIndexator2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMpgFileIndexator2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMpgFileIndexator2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMpgFileIndexator2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMpgFileIndexator2_put_InputMediaFile(This,newVal)	\
    (This)->lpVtbl -> put_InputMediaFile(This,newVal)

#define IMpgFileIndexator2_get_InputMediaFile(This,pVal)	\
    (This)->lpVtbl -> get_InputMediaFile(This,pVal)

#define IMpgFileIndexator2_get_StreamsDetected(This,pVal)	\
    (This)->lpVtbl -> get_StreamsDetected(This,pVal)

#define IMpgFileIndexator2_get_TypeOfStream(This,pVal)	\
    (This)->lpVtbl -> get_TypeOfStream(This,pVal)

#define IMpgFileIndexator2_put_OutputIndexFile(This,newVal)	\
    (This)->lpVtbl -> put_OutputIndexFile(This,newVal)

#define IMpgFileIndexator2_get_OutputIndexFile(This,pVal)	\
    (This)->lpVtbl -> get_OutputIndexFile(This,pVal)

#define IMpgFileIndexator2_put_SaveRelativePath(This,newVal)	\
    (This)->lpVtbl -> put_SaveRelativePath(This,newVal)

#define IMpgFileIndexator2_put_IndexTypeGUID(This,newVal)	\
    (This)->lpVtbl -> put_IndexTypeGUID(This,newVal)

#define IMpgFileIndexator2_get_IndexTypeGUID(This,pVal)	\
    (This)->lpVtbl -> get_IndexTypeGUID(This,pVal)

#define IMpgFileIndexator2_StartIndexing(This)	\
    (This)->lpVtbl -> StartIndexing(This)

#define IMpgFileIndexator2_CancelIndexing(This)	\
    (This)->lpVtbl -> CancelIndexing(This)

#define IMpgFileIndexator2_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IMpgFileIndexator2_get_AccessUnitsProcessed(This,pVal)	\
    (This)->lpVtbl -> get_AccessUnitsProcessed(This,pVal)

#define IMpgFileIndexator2_get_OperationStatus(This,pVal)	\
    (This)->lpVtbl -> get_OperationStatus(This,pVal)


#define IMpgFileIndexator2_WaitIndexingComplete(This)	\
    (This)->lpVtbl -> WaitIndexingComplete(This)

#define IMpgFileIndexator2_ContinueIndexing(This)	\
    (This)->lpVtbl -> ContinueIndexing(This)

#define IMpgFileIndexator2_SetIndexingBaseTime(This,rtBaseTime)	\
    (This)->lpVtbl -> SetIndexingBaseTime(This,rtBaseTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator2_WaitIndexingComplete_Proxy( 
    IMpgFileIndexator2 * This);


void __RPC_STUB IMpgFileIndexator2_WaitIndexingComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator2_ContinueIndexing_Proxy( 
    IMpgFileIndexator2 * This);


void __RPC_STUB IMpgFileIndexator2_ContinueIndexing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMpgFileIndexator2_SetIndexingBaseTime_Proxy( 
    IMpgFileIndexator2 * This,
    LONGLONG rtBaseTime);


void __RPC_STUB IMpgFileIndexator2_SetIndexingBaseTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMpgFileIndexator2_INTERFACE_DEFINED__ */



#ifndef __ELMPGINDEXATORLib_LIBRARY_DEFINED__
#define __ELMPGINDEXATORLib_LIBRARY_DEFINED__

/* library ELMPGINDEXATORLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ELMPGINDEXATORLib;

EXTERN_C const CLSID CLSID_MpgFileIndexator;

#ifdef __cplusplus

class DECLSPEC_UUID("6736EBE9-378A-4eb8-BC6A-D4981D2D4261")
MpgFileIndexator;
#endif
#endif /* __ELMPGINDEXATORLib_LIBRARY_DEFINED__ */

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


