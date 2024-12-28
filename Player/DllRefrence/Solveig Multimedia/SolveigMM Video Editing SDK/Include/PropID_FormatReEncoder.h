#pragma once

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GUID                       Type           Available range      Default Val    Note
// SMMFES_Authorized          VT_UI1                                             ???
// SMMFES_Bitrate             VT_UI4                                             Encoder Bitrate
// SMMFES_MediaType           VT_BYREF|VT_UI1                                    CMediaType -> BYTE *
// SMMFES_AllocatorProps      VT_BYREF|VT_UI1                                    ALLOCATOR_PROPS - > BYTE *
// SMMFES_Sample              VT_BYREF|VT_UI1                                    CData -> BYTE *
// SMMFES_SampleFree          VT_BYREF|VT_UI1                                    CData -> BYTE *
// SMMFES_Command             VT_UI4                                             enum
// --------------------------------------------------------------------------------------------------------
// SMAT_SilentPath            VT_BSTR
// SMAT_MPEG2CodecsSet        VT_BSTR
// SMAT_FAEncToUse            VT_BSTR                                            "GUID_0|GUID_1|...|GUID_N"
// SMAT_FADecToUse            VT_BSTR                                            "GUID_0|GUID_1|...|GUID_N"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Parameters guids are available in the full SDK version

#ifdef __cplusplus
}
#endif