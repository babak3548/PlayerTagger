

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITrimmerObjControlCB,0x33968711,0x8887,0x46D4,0xA7,0x1B,0x9B,0x1B,0x06,0x1E,0xED,0xCA);


MIDL_DEFINE_GUID(IID, IID_ITrimmerObjControl,0x9D9BF96C,0x8E7A,0x41FC,0xAB,0xB1,0xCC,0xC9,0xCE,0xF4,0x93,0xE9);


MIDL_DEFINE_GUID(IID, LIBID_AVITRIMMERCOMLib,0x958BB6C7,0x14FB,0x49EF,0xAF,0xAE,0x67,0x81,0x55,0x68,0x0C,0x6A);


MIDL_DEFINE_GUID(IID, DIID__IXTransformEvents,0xDC2117FE,0x3CCE,0x476A,0x99,0x2A,0xCA,0xF7,0xDE,0xD3,0x37,0x64);


MIDL_DEFINE_GUID(CLSID, CLSID_TrimmerObjControl,0xB61C3708,0xCAA8,0x48CA,0x9D,0x9C,0x68,0x2D,0x0A,0x5A,0x38,0x52);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



