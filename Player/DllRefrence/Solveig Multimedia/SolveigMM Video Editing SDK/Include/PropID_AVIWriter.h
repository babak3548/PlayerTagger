#ifndef __PROP_ID_AVI_WRITER__
#define __PROP_ID_AVI_WRITER__

typedef enum AVIWriterFlags
{
	AVIWriterFlags_WriteFile			= 0x1,
	AVIWriterFlags_CountSize			= 0x2, // can not be simultaneously set AVIWriterFlags_WriteFile and AVIWriterFlags_CountSize  flags
	AVIWriterFlags_CountAVIMuxerInfo    = 0x4,
	AVIWriterFlags_CountNativeAVIInfo	= 0x8,
	AVIWriterFlags_RawMode				= 0x10
} AVIWriterFlags;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		GUID								Type		Available range		Default Val						Note
// 	SMAW_Flags								AVIWriterFlags						AVIWriterFlags_WriteFile	
//	SMAW_CurrentSize						VT_UI8			[]					[]							Contains the current size
//	SMAW_WroteIdx1							VT_BOOL			[]					[]							Contains the current size
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Parameter GUIDs are available in the full SDK version