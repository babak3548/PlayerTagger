
#ifndef __IMP2TRIMMERFAPROPS_H__
#define __IMP2TRIMMERFAPROPS_H__

#ifdef __cplusplus
extern "C" {
#endif

// {6E222E86-EB79-44d7-93C6-9B94C41BD3CE}
DEFINE_GUID(IID_IMP2TrimmerFAProps, 
	0x6e222e86, 0xeb79, 0x44d7, 0x93, 0xc6, 0x9b, 0x94, 0xc4, 0x1b, 0xd3, 0xce);
	
// {C80E8877-1634-4e3b-8734-E7FFF361519B}
DEFINE_GUID(CLSID_MP2_TRIM_FA, 
			0xc80e8877, 0x1634, 0x4e3b, 0x87, 0x34, 0xe7, 0xff, 0xf3, 0x61, 0x51, 0x9b);

// {175B4841-C3EC-4bda-B34F-72EDA0DA1171}
DEFINE_GUID(CLSID_MP2_TRIM_FA_PPage, 
			0x175b4841, 0xc3ec, 0x4bda, 0xb3, 0x4f, 0x72, 0xed, 0xa0, 0xda, 0x11, 0x71);

// {4C1B2FB4-A100-42fe-85F6-D325020D00B1}
DEFINE_GUID(CLSID_MP2_TRIM_FA_About_PPage, 
			0x4c1b2fb4, 0xa100, 0x42fe, 0x85, 0xf6, 0xd3, 0x25, 0x2, 0xd, 0x0, 0xb1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GUID								Type		Available range		Default Val		Note
// SM2TFA_TrimList						VT_ARRAY 										list of start/stop times of fragments to be delivered to output (TrimInfoList)
// SM2TFA_TrimListSize					VT_I4											count of time list nodes
// SM2TFA_Duration						VT_UI8											duration of stream in 100 nanosecond units
// SM2TFA_AudioPinsNum					VT_I4							0				a number of audio pins (one unit is input/output pair)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Parameters guids are available in the full SDK version

#ifdef __cplusplus
}
#endif

#endif // __IMP2TRIMMERFAPROPS_H__

