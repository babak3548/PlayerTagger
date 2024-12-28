

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


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

MIDL_DEFINE_GUID(IID, IID_IIndexEntry,0xF1A29696,0x26A3,0x4C01,0xB3,0x75,0xF5,0xCE,0x05,0x12,0x8E,0x5D);


MIDL_DEFINE_GUID(IID, IID_IMediaIndex,0x15165B12,0x794A,0x4D0D,0xB5,0xBC,0x10,0x84,0x9B,0xFF,0x85,0x6F);


MIDL_DEFINE_GUID(IID, IID_IMediaIndex2,0xE2C5A7C7,0xF263,0x4b32,0x9F,0xB4,0xB1,0x8E,0x56,0x23,0x81,0x33);


MIDL_DEFINE_GUID(IID, IID_IMIxReader,0x432BC59E,0x1F01,0x4A01,0xAA,0x74,0xC4,0x53,0xAE,0xE6,0x7C,0xE2);


MIDL_DEFINE_GUID(IID, IID_IMIxReader2,0x77902765,0xA6AC,0x42e1,0xAB,0xDC,0x8A,0x13,0xFB,0x84,0x9B,0xC6);


MIDL_DEFINE_GUID(IID, LIBID_ELMIXREADERLib,0x94DA391B,0x722B,0x4E9E,0xAA,0x6E,0x3B,0x6C,0x64,0x29,0x62,0x85);


MIDL_DEFINE_GUID(CLSID, CLSID_MIxReader,0x3C46A1D3,0xC35A,0x48C0,0x95,0xAD,0xA1,0xC7,0x14,0x3F,0x12,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

