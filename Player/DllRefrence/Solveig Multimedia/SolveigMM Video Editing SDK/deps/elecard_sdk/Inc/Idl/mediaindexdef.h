

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Nov 17 17:40:35 2010
 */
/* Compiler settings for .\Inc\Idl\mediaindexdef.idl:
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

#ifndef __mediaindexdef_h__
#define __mediaindexdef_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIndexEntry_FWD_DEFINED__
#define __IIndexEntry_FWD_DEFINED__
typedef interface IIndexEntry IIndexEntry;
#endif 	/* __IIndexEntry_FWD_DEFINED__ */


#ifndef __IMediaIndex_FWD_DEFINED__
#define __IMediaIndex_FWD_DEFINED__
typedef interface IMediaIndex IMediaIndex;
#endif 	/* __IMediaIndex_FWD_DEFINED__ */


#ifndef __IMediaIndex2_FWD_DEFINED__
#define __IMediaIndex2_FWD_DEFINED__
typedef interface IMediaIndex2 IMediaIndex2;
#endif 	/* __IMediaIndex2_FWD_DEFINED__ */


#ifndef __IMIxReader_FWD_DEFINED__
#define __IMIxReader_FWD_DEFINED__
typedef interface IMIxReader IMIxReader;
#endif 	/* __IMIxReader_FWD_DEFINED__ */


#ifndef __IMIxReader2_FWD_DEFINED__
#define __IMIxReader2_FWD_DEFINED__
typedef interface IMIxReader2 IMIxReader2;
#endif 	/* __IMIxReader2_FWD_DEFINED__ */


#ifndef __MIxReader_FWD_DEFINED__
#define __MIxReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class MIxReader MIxReader;
#else
typedef struct MIxReader MIxReader;
#endif /* __cplusplus */

#endif 	/* __MIxReader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IIndexEntry_INTERFACE_DEFINED__
#define __IIndexEntry_INTERFACE_DEFINED__

/* interface IIndexEntry */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIndexEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1A29696-26A3-4C01-B375-F5CE05128E5D")
    IIndexEntry : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsTimeValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ long *pHighWord,
            /* [out] */ long *pLowWord) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsNumberValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Number( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsOffsetValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOffset( 
            /* [out] */ long *pHighWord,
            /* [out] */ long *pLowWord) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TypeCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIndexEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIndexEntry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIndexEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIndexEntry * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIndexEntry * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIndexEntry * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIndexEntry * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIndexEntry * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsTimeValid )( 
            IIndexEntry * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IIndexEntry * This,
            /* [out] */ long *pHighWord,
            /* [out] */ long *pLowWord);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsNumberValid )( 
            IIndexEntry * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Number )( 
            IIndexEntry * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOffsetValid )( 
            IIndexEntry * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOffset )( 
            IIndexEntry * This,
            /* [out] */ long *pHighWord,
            /* [out] */ long *pLowWord);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TypeCode )( 
            IIndexEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IIndexEntryVtbl;

    interface IIndexEntry
    {
        CONST_VTBL struct IIndexEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIndexEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIndexEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIndexEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIndexEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIndexEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIndexEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIndexEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIndexEntry_get_IsTimeValid(This,pVal)	\
    (This)->lpVtbl -> get_IsTimeValid(This,pVal)

#define IIndexEntry_GetTime(This,pHighWord,pLowWord)	\
    (This)->lpVtbl -> GetTime(This,pHighWord,pLowWord)

#define IIndexEntry_get_IsNumberValid(This,pVal)	\
    (This)->lpVtbl -> get_IsNumberValid(This,pVal)

#define IIndexEntry_get_Number(This,pVal)	\
    (This)->lpVtbl -> get_Number(This,pVal)

#define IIndexEntry_get_IsOffsetValid(This,pVal)	\
    (This)->lpVtbl -> get_IsOffsetValid(This,pVal)

#define IIndexEntry_GetOffset(This,pHighWord,pLowWord)	\
    (This)->lpVtbl -> GetOffset(This,pHighWord,pLowWord)

#define IIndexEntry_get_TypeCode(This,pVal)	\
    (This)->lpVtbl -> get_TypeCode(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIndexEntry_get_IsTimeValid_Proxy( 
    IIndexEntry * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IIndexEntry_get_IsTimeValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIndexEntry_GetTime_Proxy( 
    IIndexEntry * This,
    /* [out] */ long *pHighWord,
    /* [out] */ long *pLowWord);


void __RPC_STUB IIndexEntry_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIndexEntry_get_IsNumberValid_Proxy( 
    IIndexEntry * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IIndexEntry_get_IsNumberValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIndexEntry_get_Number_Proxy( 
    IIndexEntry * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IIndexEntry_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIndexEntry_get_IsOffsetValid_Proxy( 
    IIndexEntry * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IIndexEntry_get_IsOffsetValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIndexEntry_GetOffset_Proxy( 
    IIndexEntry * This,
    /* [out] */ long *pHighWord,
    /* [out] */ long *pLowWord);


void __RPC_STUB IIndexEntry_GetOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIndexEntry_get_TypeCode_Proxy( 
    IIndexEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IIndexEntry_get_TypeCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIndexEntry_INTERFACE_DEFINED__ */


#ifndef __IMediaIndex_INTERFACE_DEFINED__
#define __IMediaIndex_INTERFACE_DEFINED__

/* interface IMediaIndex */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaIndex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("15165B12-794A-4D0D-B5BC-10849BFF856F")
    IMediaIndex : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockIndex( 
            BOOL bLock) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexTypeCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EntryStructGuid( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsProgramNumValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgramNum( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsPIDValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PID( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsStreamIdValid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Streamid( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsSubStreamIdVlaid( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubStreamId( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EntriesCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Entry( 
            /* [in] */ long lNumber,
            /* [retval][out] */ IIndexEntry **ppIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaIndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaIndex * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaIndex * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaIndex * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaIndex * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaIndex * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaIndex * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaIndex * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LockIndex )( 
            IMediaIndex * This,
            BOOL bLock);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexTypeCode )( 
            IMediaIndex * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntryStructGuid )( 
            IMediaIndex * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsProgramNumValid )( 
            IMediaIndex * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramNum )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPIDValid )( 
            IMediaIndex * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PID )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsStreamIdValid )( 
            IMediaIndex * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Streamid )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSubStreamIdVlaid )( 
            IMediaIndex * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SubStreamId )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntriesCount )( 
            IMediaIndex * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Entry )( 
            IMediaIndex * This,
            /* [in] */ long lNumber,
            /* [retval][out] */ IIndexEntry **ppIndex);
        
        END_INTERFACE
    } IMediaIndexVtbl;

    interface IMediaIndex
    {
        CONST_VTBL struct IMediaIndexVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaIndex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaIndex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaIndex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaIndex_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaIndex_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaIndex_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaIndex_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaIndex_LockIndex(This,bLock)	\
    (This)->lpVtbl -> LockIndex(This,bLock)

#define IMediaIndex_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IMediaIndex_get_IndexTypeCode(This,pVal)	\
    (This)->lpVtbl -> get_IndexTypeCode(This,pVal)

#define IMediaIndex_get_EntryStructGuid(This,pVal)	\
    (This)->lpVtbl -> get_EntryStructGuid(This,pVal)

#define IMediaIndex_get_IsProgramNumValid(This,pVal)	\
    (This)->lpVtbl -> get_IsProgramNumValid(This,pVal)

#define IMediaIndex_get_ProgramNum(This,pVal)	\
    (This)->lpVtbl -> get_ProgramNum(This,pVal)

#define IMediaIndex_get_IsPIDValid(This,pVal)	\
    (This)->lpVtbl -> get_IsPIDValid(This,pVal)

#define IMediaIndex_get_PID(This,pVal)	\
    (This)->lpVtbl -> get_PID(This,pVal)

#define IMediaIndex_get_IsStreamIdValid(This,pVal)	\
    (This)->lpVtbl -> get_IsStreamIdValid(This,pVal)

#define IMediaIndex_get_Streamid(This,pVal)	\
    (This)->lpVtbl -> get_Streamid(This,pVal)

#define IMediaIndex_get_IsSubStreamIdVlaid(This,pVal)	\
    (This)->lpVtbl -> get_IsSubStreamIdVlaid(This,pVal)

#define IMediaIndex_get_SubStreamId(This,pVal)	\
    (This)->lpVtbl -> get_SubStreamId(This,pVal)

#define IMediaIndex_get_EntriesCount(This,pVal)	\
    (This)->lpVtbl -> get_EntriesCount(This,pVal)

#define IMediaIndex_get_Entry(This,lNumber,ppIndex)	\
    (This)->lpVtbl -> get_Entry(This,lNumber,ppIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMediaIndex_LockIndex_Proxy( 
    IMediaIndex * This,
    BOOL bLock);


void __RPC_STUB IMediaIndex_LockIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_Version_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_IndexTypeCode_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMediaIndex_get_IndexTypeCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_EntryStructGuid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMediaIndex_get_EntryStructGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_IsProgramNumValid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMediaIndex_get_IsProgramNumValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_ProgramNum_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_ProgramNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_IsPIDValid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMediaIndex_get_IsPIDValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_PID_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_PID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_IsStreamIdValid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMediaIndex_get_IsStreamIdValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_Streamid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_Streamid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_IsSubStreamIdVlaid_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMediaIndex_get_IsSubStreamIdVlaid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_SubStreamId_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_SubStreamId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_EntriesCount_Proxy( 
    IMediaIndex * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMediaIndex_get_EntriesCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex_get_Entry_Proxy( 
    IMediaIndex * This,
    /* [in] */ long lNumber,
    /* [retval][out] */ IIndexEntry **ppIndex);


void __RPC_STUB IMediaIndex_get_Entry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaIndex_INTERFACE_DEFINED__ */


#ifndef __IMediaIndex2_INTERFACE_DEFINED__
#define __IMediaIndex2_INTERFACE_DEFINED__

/* interface IMediaIndex2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaIndex2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2C5A7C7-F263-4b32-9FB4-B18E56238133")
    IMediaIndex2 : public IMediaIndex
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetInfoAdditional( 
            /* [out][in] */ long *plSize,
            /* [size_is][out][in] */ byte *pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaIndex2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaIndex2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaIndex2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaIndex2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaIndex2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaIndex2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaIndex2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaIndex2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LockIndex )( 
            IMediaIndex2 * This,
            BOOL bLock);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexTypeCode )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntryStructGuid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsProgramNumValid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramNum )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPIDValid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PID )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsStreamIdValid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Streamid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSubStreamIdVlaid )( 
            IMediaIndex2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SubStreamId )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntriesCount )( 
            IMediaIndex2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Entry )( 
            IMediaIndex2 * This,
            /* [in] */ long lNumber,
            /* [retval][out] */ IIndexEntry **ppIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GetInfoAdditional )( 
            IMediaIndex2 * This,
            /* [out][in] */ long *plSize,
            /* [size_is][out][in] */ byte *pData);
        
        END_INTERFACE
    } IMediaIndex2Vtbl;

    interface IMediaIndex2
    {
        CONST_VTBL struct IMediaIndex2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaIndex2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaIndex2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaIndex2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaIndex2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaIndex2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaIndex2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaIndex2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaIndex2_LockIndex(This,bLock)	\
    (This)->lpVtbl -> LockIndex(This,bLock)

#define IMediaIndex2_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IMediaIndex2_get_IndexTypeCode(This,pVal)	\
    (This)->lpVtbl -> get_IndexTypeCode(This,pVal)

#define IMediaIndex2_get_EntryStructGuid(This,pVal)	\
    (This)->lpVtbl -> get_EntryStructGuid(This,pVal)

#define IMediaIndex2_get_IsProgramNumValid(This,pVal)	\
    (This)->lpVtbl -> get_IsProgramNumValid(This,pVal)

#define IMediaIndex2_get_ProgramNum(This,pVal)	\
    (This)->lpVtbl -> get_ProgramNum(This,pVal)

#define IMediaIndex2_get_IsPIDValid(This,pVal)	\
    (This)->lpVtbl -> get_IsPIDValid(This,pVal)

#define IMediaIndex2_get_PID(This,pVal)	\
    (This)->lpVtbl -> get_PID(This,pVal)

#define IMediaIndex2_get_IsStreamIdValid(This,pVal)	\
    (This)->lpVtbl -> get_IsStreamIdValid(This,pVal)

#define IMediaIndex2_get_Streamid(This,pVal)	\
    (This)->lpVtbl -> get_Streamid(This,pVal)

#define IMediaIndex2_get_IsSubStreamIdVlaid(This,pVal)	\
    (This)->lpVtbl -> get_IsSubStreamIdVlaid(This,pVal)

#define IMediaIndex2_get_SubStreamId(This,pVal)	\
    (This)->lpVtbl -> get_SubStreamId(This,pVal)

#define IMediaIndex2_get_EntriesCount(This,pVal)	\
    (This)->lpVtbl -> get_EntriesCount(This,pVal)

#define IMediaIndex2_get_Entry(This,lNumber,ppIndex)	\
    (This)->lpVtbl -> get_Entry(This,lNumber,ppIndex)


#define IMediaIndex2_get_GetInfoAdditional(This,plSize,pData)	\
    (This)->lpVtbl -> get_GetInfoAdditional(This,plSize,pData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaIndex2_get_GetInfoAdditional_Proxy( 
    IMediaIndex2 * This,
    /* [out][in] */ long *plSize,
    /* [size_is][out][in] */ byte *pData);


void __RPC_STUB IMediaIndex2_get_GetInfoAdditional_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaIndex2_INTERFACE_DEFINED__ */


#ifndef __IMIxReader_INTERFACE_DEFINED__
#define __IMIxReader_INTERFACE_DEFINED__

/* interface IMIxReader */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMIxReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("432BC59E-1F01-4A01-AA74-C453AEE67CE2")
    IMIxReader : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IndexFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFileTypeCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexesCount( 
            /* [retval][out] */ long *pcount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [in] */ long lNumber,
            /* [retval][out] */ IMediaIndex **ppIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMIxReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMIxReader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMIxReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMIxReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMIxReader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMIxReader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMIxReader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMIxReader * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexFileName )( 
            IMIxReader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IndexFileName )( 
            IMIxReader * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IMIxReader * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFileName )( 
            IMIxReader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFileTypeCode )( 
            IMIxReader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexesCount )( 
            IMIxReader * This,
            /* [retval][out] */ long *pcount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IMIxReader * This,
            /* [in] */ long lNumber,
            /* [retval][out] */ IMediaIndex **ppIndex);
        
        END_INTERFACE
    } IMIxReaderVtbl;

    interface IMIxReader
    {
        CONST_VTBL struct IMIxReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMIxReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMIxReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMIxReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMIxReader_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMIxReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMIxReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMIxReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMIxReader_get_IndexFileName(This,pVal)	\
    (This)->lpVtbl -> get_IndexFileName(This,pVal)

#define IMIxReader_put_IndexFileName(This,newVal)	\
    (This)->lpVtbl -> put_IndexFileName(This,newVal)

#define IMIxReader_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IMIxReader_get_MediaFileName(This,pVal)	\
    (This)->lpVtbl -> get_MediaFileName(This,pVal)

#define IMIxReader_get_MediaFileTypeCode(This,pVal)	\
    (This)->lpVtbl -> get_MediaFileTypeCode(This,pVal)

#define IMIxReader_get_IndexesCount(This,pcount)	\
    (This)->lpVtbl -> get_IndexesCount(This,pcount)

#define IMIxReader_get_Index(This,lNumber,ppIndex)	\
    (This)->lpVtbl -> get_Index(This,lNumber,ppIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_IndexFileName_Proxy( 
    IMIxReader * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMIxReader_get_IndexFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMIxReader_put_IndexFileName_Proxy( 
    IMIxReader * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMIxReader_put_IndexFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_Version_Proxy( 
    IMIxReader * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMIxReader_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_MediaFileName_Proxy( 
    IMIxReader * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMIxReader_get_MediaFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_MediaFileTypeCode_Proxy( 
    IMIxReader * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMIxReader_get_MediaFileTypeCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_IndexesCount_Proxy( 
    IMIxReader * This,
    /* [retval][out] */ long *pcount);


void __RPC_STUB IMIxReader_get_IndexesCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMIxReader_get_Index_Proxy( 
    IMIxReader * This,
    /* [in] */ long lNumber,
    /* [retval][out] */ IMediaIndex **ppIndex);


void __RPC_STUB IMIxReader_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMIxReader_INTERFACE_DEFINED__ */


#ifndef __IMIxReader2_INTERFACE_DEFINED__
#define __IMIxReader2_INTERFACE_DEFINED__

/* interface IMIxReader2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMIxReader2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77902765-A6AC-42e1-ABDC-8A13FB849BC6")
    IMIxReader2 : public IMIxReader
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IndexFileList( 
            SAFEARRAY * pSafeArrayIndexFileList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FlushCommonIndexFile( 
            /* [in] */ BSTR newVal1,
            /* [in] */ BSTR newVal2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMIxReader2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMIxReader2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMIxReader2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMIxReader2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMIxReader2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMIxReader2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMIxReader2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMIxReader2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexFileName )( 
            IMIxReader2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IndexFileName )( 
            IMIxReader2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IMIxReader2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFileName )( 
            IMIxReader2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFileTypeCode )( 
            IMIxReader2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexesCount )( 
            IMIxReader2 * This,
            /* [retval][out] */ long *pcount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IMIxReader2 * This,
            /* [in] */ long lNumber,
            /* [retval][out] */ IMediaIndex **ppIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IndexFileList )( 
            IMIxReader2 * This,
            SAFEARRAY * pSafeArrayIndexFileList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FlushCommonIndexFile )( 
            IMIxReader2 * This,
            /* [in] */ BSTR newVal1,
            /* [in] */ BSTR newVal2);
        
        END_INTERFACE
    } IMIxReader2Vtbl;

    interface IMIxReader2
    {
        CONST_VTBL struct IMIxReader2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMIxReader2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMIxReader2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMIxReader2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMIxReader2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMIxReader2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMIxReader2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMIxReader2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMIxReader2_get_IndexFileName(This,pVal)	\
    (This)->lpVtbl -> get_IndexFileName(This,pVal)

#define IMIxReader2_put_IndexFileName(This,newVal)	\
    (This)->lpVtbl -> put_IndexFileName(This,newVal)

#define IMIxReader2_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IMIxReader2_get_MediaFileName(This,pVal)	\
    (This)->lpVtbl -> get_MediaFileName(This,pVal)

#define IMIxReader2_get_MediaFileTypeCode(This,pVal)	\
    (This)->lpVtbl -> get_MediaFileTypeCode(This,pVal)

#define IMIxReader2_get_IndexesCount(This,pcount)	\
    (This)->lpVtbl -> get_IndexesCount(This,pcount)

#define IMIxReader2_get_Index(This,lNumber,ppIndex)	\
    (This)->lpVtbl -> get_Index(This,lNumber,ppIndex)


#define IMIxReader2_put_IndexFileList(This,pSafeArrayIndexFileList)	\
    (This)->lpVtbl -> put_IndexFileList(This,pSafeArrayIndexFileList)

#define IMIxReader2_FlushCommonIndexFile(This,newVal1,newVal2)	\
    (This)->lpVtbl -> FlushCommonIndexFile(This,newVal1,newVal2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMIxReader2_put_IndexFileList_Proxy( 
    IMIxReader2 * This,
    SAFEARRAY * pSafeArrayIndexFileList);


void __RPC_STUB IMIxReader2_put_IndexFileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMIxReader2_FlushCommonIndexFile_Proxy( 
    IMIxReader2 * This,
    /* [in] */ BSTR newVal1,
    /* [in] */ BSTR newVal2);


void __RPC_STUB IMIxReader2_FlushCommonIndexFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMIxReader2_INTERFACE_DEFINED__ */



#ifndef __ELMIXREADERLib_LIBRARY_DEFINED__
#define __ELMIXREADERLib_LIBRARY_DEFINED__

/* library ELMIXREADERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ELMIXREADERLib;

EXTERN_C const CLSID CLSID_MIxReader;

#ifdef __cplusplus

class DECLSPEC_UUID("3C46A1D3-C35A-48C0-95AD-A1C7143F124B")
MIxReader;
#endif
#endif /* __ELMIXREADERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


