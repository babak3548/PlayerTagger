#ifndef __PROPID_EDITINGENGINE_TYPES__
#define __PROPID_EDITINGENGINE_TYPES__
// don't forget to when changing SMM_OutputTypes enum to set XTLDescr_TrackOutType string according to new type
enum SMM_OutputTypes
{
	SMM_File_Type_NO    = 0x0,
	SMM_File_Type_AVI,  // audio video interleaving format
	SMM_File_Type_ASF,  // advanced streaming format
	SMM_File_Type_MPA,  // MPEG audio
	SMM_File_Type_MPEG2_PS,  // MPEG-2 Program Stream
	SMM_File_Type_MPEG2_TS,  // MPEG-2 Transport Stream
	SMM_File_Type_MPEG2_VES,  // MPEG-2 Video Elementary Stream
	SMM_File_Type_MPEG1_SYS,  // MPEG-1 System stream. Unsupported
	SMM_File_Type_MPEG1_VES,  // MPEG-1 Video only elementary stream.
	SMM_File_Type_WAV,  // WAVE audio steam
	SMM_File_Type_MPEG4_AVC,  // MPEG-4 AVC Video only elementary stream.
	SMM_File_Type_MKV,   // Matroska video
	SMM_File_Type_MP4,// MPEG-4 Part 14 - MP4 File format
	SMM_File_Type_RAW, // 
	SMM_File_Type_COUNT // all formats count
}; 

static  const WCHAR* XTLDescr_TrackOutType[SMM_File_Type_COUNT] = 
{
	L"no type", 
	L"avi",     
	L"asf",     
	L"mpa",     
	L"mpg_ps",  
	L"mpg_ts",  
	L"mpg_ves", 
	L"mpg1_sys",
	L"mpg1_ves",
	L"wav",
	L"avc_ves",  
	L"matroska", 
	L"mp4",
	L"raw"
};

enum SMM_TaskType
{
	SMM_Task_Type_Trimming      = 0x0,  // triming
	SMM_Task_Type_Joining       = 0x1,  // 
	SMM_Task_Type_Join_Gap_Fill = 0x2,  // 
	SMM_Task_Type_Muxing        = 0x3,  // 
	SMM_Task_Type_Demuxing      = 0x4,  // 
	SMM_Task_Type_Indexation    = 0x5,  // 
};  

static const WCHAR *XTLDescr_GroupMode[7] = 
{
	L"trimming",		//  valid for group mode
	L"joining",			//
	L"joining",			//
	L"multiplexing",	//  valid for group mode
	L"demultiplexing",	// 
	L"indexation",		// 
};

enum SMM_TrimmAccuracyType
{
    SMM_TrimmAccuracyType_Deflt = -1,
    SMM_TrimmAccuracyType_GOP    = 0,
    SMM_TrimmAccuracyType_Frame  = 1
};


static  const WCHAR* XTLDescr_TrackAccuracy[2] = 
{
    L"gop",
    L"frame"
};


#endif