// {7B4711F1-FA2D-4056-8CF3-C867DB047DC0}
DEFINE_GUID(CLSID_SMM_Jointer, 
			0x7b4711f1, 0xfa2d, 0x4056, 0x8c, 0xf3, 0xc8, 0x67, 0xdb, 0x4, 0x7d, 0xc0);

// {AA2400F1-C3B9-4345-B664-096D3B432AA5}
DEFINE_GUID(CLSID_SMM_Jointer_Prop_Main, 
			0xaa2400f1, 0xc3b9, 0x4345, 0xb6, 0x64, 0x9, 0x6d, 0x3b, 0x43, 0x2a, 0xa5);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GUID							Type		Available range		Default Val		Note
// SMMJ_FileName				   VT_BSTR 											Set/Get the current filename to write to
// SMMJ_BytesWrittenByPin	 in-VT_INT/out-VT_UI8									Set intVal to the pin's number and get ullVal of bytes, written by this pin(Read only)
// SMMJ_GetFullStatistic	  VT_BYREF|VT_UI1										Read only pointer to an array of each pin's StatisticParmeters
// SMMJ_StopWriting																	Has no parameters, just stops writing to file
// SMMJ_FileType				   VT_INT						 SMM_File_Type_NO	Output File's type
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Parameters GUIDS available in FULL version of SDK;

typedef struct StatisticParameters
{
	int			TotalPins;
	int			PinNum;
	LONGLONG	llFramesCount;
	ULONGLONG	ullBytesCount;
	BOOL		EOS;
	GUID		Mediatype;
} StatParams ;


static const GUID MEDIASUBTYPE_MP3 = 
{ 0x00000055, 0x0000, 0x0010, { 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 } };
