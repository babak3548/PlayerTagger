

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Jun 06 19:16:26 2007
 */
/* Compiler settings for \Projects\Main_Projects\SolveigMM_Video_Editing_SDK\Include\idl\ModuleConfigForVB.idl:
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

#ifndef __ModuleConfigForVB_h__
#define __ModuleConfigForVB_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IModuleConfigForVB_FWD_DEFINED__
#define __IModuleConfigForVB_FWD_DEFINED__
typedef interface IModuleConfigForVB IModuleConfigForVB;
#endif 	/* __IModuleConfigForVB_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ModuleConfig.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_ModuleConfigForVB_0000 */
/* [local] */ 

//////////////////////////////////////////////////////////////////////////
//
//	original file name: ModuleConfigForVB.idl
//
//////////////////////////////////////////////////////////////////////////
//
//
//	purpose: ModuleConfigForVB interfaces definitions
//
//////////////////////////////////////////////////////////////////////////


// {D211F479-B5F2-469f-9EB9-F0CD7EB202D9}
DEFINE_GUID(IID_IModuleConfigForVB, 0xD211F479, 0xB5F2, 0x469f, 0x9E, 0xB9, 0xF0, 0xCD, 0x7E, 0xB2, 0x02, 0xD9);



extern RPC_IF_HANDLE __MIDL_itf_ModuleConfigForVB_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ModuleConfigForVB_0000_v0_0_s_ifspec;

#ifndef __IModuleConfigForVB_INTERFACE_DEFINED__
#define __IModuleConfigForVB_INTERFACE_DEFINED__

/* interface IModuleConfigForVB */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IModuleConfigForVB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D211F479-B5F2-469f-9EB9-F0CD7EB202D9")
    IModuleConfigForVB : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetValueVB( 
            /* [in] */ BSTR pParamID,
            /* [in] */ const VARIANT *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValueVB( 
            /* [in] */ BSTR pParamID,
            /* [out] */ VARIANT *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetParamConfigVB( 
            /* [in] */ BSTR pParamID,
            /* [out] */ VARIANT *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSupportedVB( 
            /* [in] */ BSTR pParamID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDefStateVB( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumParamsVB( 
            /* [out][in] */ long *pNumParams,
            /* [out][in] */ GUID *pParamIDs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CommitChangesVB( 
            /* [out] */ VARIANT *pReason) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeclineChangesVB( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveToRegistryVB( 
            /* [in] */ DWORD hKeyRoot,
            /* [in] */ const BSTR pszKeyName,
            /* [in] */ const BOOL bPreferReadable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadFromRegistryVB( 
            /* [in] */ DWORD hKeyRoot,
            /* [in] */ const BSTR pszKeyName,
            /* [in] */ const BOOL bPreferReadable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegisterForNotifiesVB( 
            /* [in] */ IModuleCallback *pModuleCallback) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnregisterFromNotifiesVB( 
            /* [in] */ IModuleCallback *pModuleCallback) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertREFTIMEtoREFERENCETIME( 
            /* [in] */ double dVal,
            /* [out] */ VARIANT *pValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModuleConfigForVBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IModuleConfigForVB * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IModuleConfigForVB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IModuleConfigForVB * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetValueVB )( 
            IModuleConfigForVB * This,
            /* [in] */ BSTR pParamID,
            /* [in] */ const VARIANT *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValueVB )( 
            IModuleConfigForVB * This,
            /* [in] */ BSTR pParamID,
            /* [out] */ VARIANT *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetParamConfigVB )( 
            IModuleConfigForVB * This,
            /* [in] */ BSTR pParamID,
            /* [out] */ VARIANT *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsSupportedVB )( 
            IModuleConfigForVB * This,
            /* [in] */ BSTR pParamID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDefStateVB )( 
            IModuleConfigForVB * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumParamsVB )( 
            IModuleConfigForVB * This,
            /* [out][in] */ long *pNumParams,
            /* [out][in] */ GUID *pParamIDs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CommitChangesVB )( 
            IModuleConfigForVB * This,
            /* [out] */ VARIANT *pReason);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeclineChangesVB )( 
            IModuleConfigForVB * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveToRegistryVB )( 
            IModuleConfigForVB * This,
            /* [in] */ DWORD hKeyRoot,
            /* [in] */ const BSTR pszKeyName,
            /* [in] */ const BOOL bPreferReadable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadFromRegistryVB )( 
            IModuleConfigForVB * This,
            /* [in] */ DWORD hKeyRoot,
            /* [in] */ const BSTR pszKeyName,
            /* [in] */ const BOOL bPreferReadable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegisterForNotifiesVB )( 
            IModuleConfigForVB * This,
            /* [in] */ IModuleCallback *pModuleCallback);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnregisterFromNotifiesVB )( 
            IModuleConfigForVB * This,
            /* [in] */ IModuleCallback *pModuleCallback);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertREFTIMEtoREFERENCETIME )( 
            IModuleConfigForVB * This,
            /* [in] */ double dVal,
            /* [out] */ VARIANT *pValue);
        
        END_INTERFACE
    } IModuleConfigForVBVtbl;

    interface IModuleConfigForVB
    {
        CONST_VTBL struct IModuleConfigForVBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModuleConfigForVB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IModuleConfigForVB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IModuleConfigForVB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IModuleConfigForVB_SetValueVB(This,pParamID,pValue)	\
    (This)->lpVtbl -> SetValueVB(This,pParamID,pValue)

#define IModuleConfigForVB_GetValueVB(This,pParamID,pValue)	\
    (This)->lpVtbl -> GetValueVB(This,pParamID,pValue)

#define IModuleConfigForVB_GetParamConfigVB(This,pParamID,pValue)	\
    (This)->lpVtbl -> GetParamConfigVB(This,pParamID,pValue)

#define IModuleConfigForVB_IsSupportedVB(This,pParamID)	\
    (This)->lpVtbl -> IsSupportedVB(This,pParamID)

#define IModuleConfigForVB_SetDefStateVB(This)	\
    (This)->lpVtbl -> SetDefStateVB(This)

#define IModuleConfigForVB_EnumParamsVB(This,pNumParams,pParamIDs)	\
    (This)->lpVtbl -> EnumParamsVB(This,pNumParams,pParamIDs)

#define IModuleConfigForVB_CommitChangesVB(This,pReason)	\
    (This)->lpVtbl -> CommitChangesVB(This,pReason)

#define IModuleConfigForVB_DeclineChangesVB(This)	\
    (This)->lpVtbl -> DeclineChangesVB(This)

#define IModuleConfigForVB_SaveToRegistryVB(This,hKeyRoot,pszKeyName,bPreferReadable)	\
    (This)->lpVtbl -> SaveToRegistryVB(This,hKeyRoot,pszKeyName,bPreferReadable)

#define IModuleConfigForVB_LoadFromRegistryVB(This,hKeyRoot,pszKeyName,bPreferReadable)	\
    (This)->lpVtbl -> LoadFromRegistryVB(This,hKeyRoot,pszKeyName,bPreferReadable)

#define IModuleConfigForVB_RegisterForNotifiesVB(This,pModuleCallback)	\
    (This)->lpVtbl -> RegisterForNotifiesVB(This,pModuleCallback)

#define IModuleConfigForVB_UnregisterFromNotifiesVB(This,pModuleCallback)	\
    (This)->lpVtbl -> UnregisterFromNotifiesVB(This,pModuleCallback)

#define IModuleConfigForVB_ConvertREFTIMEtoREFERENCETIME(This,dVal,pValue)	\
    (This)->lpVtbl -> ConvertREFTIMEtoREFERENCETIME(This,dVal,pValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_SetValueVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ BSTR pParamID,
    /* [in] */ const VARIANT *pValue);


void __RPC_STUB IModuleConfigForVB_SetValueVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_GetValueVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ BSTR pParamID,
    /* [out] */ VARIANT *pValue);


void __RPC_STUB IModuleConfigForVB_GetValueVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_GetParamConfigVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ BSTR pParamID,
    /* [out] */ VARIANT *pValue);


void __RPC_STUB IModuleConfigForVB_GetParamConfigVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_IsSupportedVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ BSTR pParamID);


void __RPC_STUB IModuleConfigForVB_IsSupportedVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_SetDefStateVB_Proxy( 
    IModuleConfigForVB * This);


void __RPC_STUB IModuleConfigForVB_SetDefStateVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_EnumParamsVB_Proxy( 
    IModuleConfigForVB * This,
    /* [out][in] */ long *pNumParams,
    /* [out][in] */ GUID *pParamIDs);


void __RPC_STUB IModuleConfigForVB_EnumParamsVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_CommitChangesVB_Proxy( 
    IModuleConfigForVB * This,
    /* [out] */ VARIANT *pReason);


void __RPC_STUB IModuleConfigForVB_CommitChangesVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_DeclineChangesVB_Proxy( 
    IModuleConfigForVB * This);


void __RPC_STUB IModuleConfigForVB_DeclineChangesVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_SaveToRegistryVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ DWORD hKeyRoot,
    /* [in] */ const BSTR pszKeyName,
    /* [in] */ const BOOL bPreferReadable);


void __RPC_STUB IModuleConfigForVB_SaveToRegistryVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_LoadFromRegistryVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ DWORD hKeyRoot,
    /* [in] */ const BSTR pszKeyName,
    /* [in] */ const BOOL bPreferReadable);


void __RPC_STUB IModuleConfigForVB_LoadFromRegistryVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_RegisterForNotifiesVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ IModuleCallback *pModuleCallback);


void __RPC_STUB IModuleConfigForVB_RegisterForNotifiesVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_UnregisterFromNotifiesVB_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ IModuleCallback *pModuleCallback);


void __RPC_STUB IModuleConfigForVB_UnregisterFromNotifiesVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IModuleConfigForVB_ConvertREFTIMEtoREFERENCETIME_Proxy( 
    IModuleConfigForVB * This,
    /* [in] */ double dVal,
    /* [out] */ VARIANT *pValue);


void __RPC_STUB IModuleConfigForVB_ConvertREFTIMEtoREFERENCETIME_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModuleConfigForVB_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


