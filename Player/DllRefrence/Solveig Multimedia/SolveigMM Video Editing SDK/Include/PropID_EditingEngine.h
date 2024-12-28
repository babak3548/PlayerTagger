#ifndef __PROPID_EDITINGENGINE__
#define __PROPID_EDITINGENGINE__

#include <cstringt.h>
#include <atlstr.h>
#include <list>

#include "PropID_EditingEngine_types.h"

//#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      GUID                                Type        Available range     Default Val         Note
//  SMAT_InputFile                          VT_BSTR         []                  []      Input file name
//  SMAT_OutputFile                         VT_BSTR         []                  []      Output file name
//  SMAT_Flags                              VT_UI4      [SMM_TrimFlags]         []      Contains trim configuration flags to be set ( SMM_TrimFlags )
//  SMAT_ResetFlags                         VT_UI4      [SMM_TrimFlags]         []      Contains trim configuration flags to reset  ( SMM_TrimFlags )
//  SMAT_TrimList                   VT_BYREF | VT_UI1       []                  []      Trim parameters list - TrimInfoList structure
//  SMAT_Progress                           VT_I4           [0,100]     [ SMM_ProgressType_TimeBased ]      
//                                                                                      Progress of trimming process in percentage
//  SMAT_AudioStreamNumber                  VT_I4           [1,n]               [1]     Number of an audio stream in a media file to be trimmed. 
//                                                                                      0 means don't trim audio and is equal to  SMM_TrimFlags::SMM_TrimFlags_VideoOnly flag
//  SMAT_VideoStreamNumber                  VT_I4           [1,n]               [1]     Number of a video stream in a media file to be trimmed.  
//  SMAT_Callback                   VT_BYREF | VT_UI1       []                  []      Sets pointer to ITrimmerObjControlCB callback interface
//  SMAT_GetVersions                VT_BYREF | VT_UI1       []                  []      Enumerating filters being used by Engine ( FILE_VERSIONS )
//  SMAT_GetVersions2               VT_BYREF | VT_UI1       []                  []      Enumerating filters being used by Engine. Additionally included full filters paths( FILE_VERSIONS_2 )
//  SMAT_CurrentSize                        VT_UI8          []                  []      Contains the current size
//  SMAT_StreamLength                       VT_R8           []                  []      Length of stream (in seconds)
//                                                                                      0 means don't trim video and is equal to  SMM_TrimFlags::SMM_TrimFlags_AudioOnly flag
//  SMAT_OutputType                         VT_UI4      [SMM_OutputTypes]   [SMM_File_Type_NO]
//                                                                                      Output type format. Should be set if out has to deffer form input one. e.g for AVI to ASF remuxing
//  SMAT_MPEG2IndexFileName                 VT_BSTR         []                  []      MPEG index file name with full path
//  SMAT_TaskType                                       [ SMM_TaskType]     [SMM_Task_Type_Trimming]
//  SMAT_TrackInfo                  VT_BYREF | VT_UI1       
//  SMAT_LangFileName
//  SMAT_SilentPath                         VT_BSTR
//  SMAT_TrimAccuracy                       VT_I4      [ SMM_TrimmAccuracyType ]

//  SMAT_ASFMarker
//  SMAT_ASFMarker

// 
//--BATCH MODE PARAMS--
//
//  SMAT_BatchFileName                      VT_BSTR         []                  []      Input batch file name(*.xtl)
//  SMAT_CurrentBatchTask                   VT_UI4          [0,n]               []      Number of a task being processed. It's used in batch file processing.
//  SMAT_BatchTasksNum                      VT_UI4          [0,n]               []      Count of tasks in batch file 
//
//--AUTOSPLITTING MODE PARAMS--
//
//  SMAT_SetAutoSplittingMode               VT_I4           [0,1]               [0]     
//  SMAT_SetAutoSplittingValue              VT_I4           []                  []      Time length of parts to be created
//  SMAT_GetProcessingPartNumber            VT_I4           [0, n]              []      Part number of a media file to be processed in auto splitting mode.
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum SMM_ProgressType
{
	SMM_ProgressType_TimeBased = 0,  // default
	SMM_ProgressType_ByteBased = 1   // it is used during ASF(WMW) re-multiplexing
};


// trim configuration flags

enum SMM_TrimFlags
{
	SMM_TrimFlags_None                      = 0,
	SMM_TrimFlags_ObeySampleTimes           = 0x2,  // Use alternative method of audio/video synchronization (by default is not set)
	SMM_TrimFlags_VideoOnly                 = 0x8,  // Process a video stream only regardless of a number video and audio stream an input media file contains. 
	SMM_TrimFlags_AudioOnly                 = 0x10, // Process an audio stream only regardless of a number video and audio stream an input media file contains. 
	SMM_TrimFlags_GettingSize               = 0x20, // Indicates whether getting file size nor trimming file
	SMM_TrimFlags_InASF                     = 0x40, // Used by the video editing engine
	SMM_TrimFlags_UsePositioning            = 0x80, // alternative
	SMM_TrimFlags_IgnoreTrimErrors          = 0x100,
	SSM_TrimFlags_TrimOverlappedIntervals   = 0x200, // After trimming of each interval trim process stops and when starts from the beginning of the input media file.
};

enum SMM_AutoSplitType
{
	SMM_AutoSplitType_None      = 0,  // default
	SMM_AutoSplitType_TimeBased = 1,  // 
	SMM_ProgressType_SizeBased  = 2   // 
};

static const WCHAR *XTLDescr_TrackAutoSplitType[3] = 
{
	L"none",
	L"by_time",
	L"by_size"
};

enum SMM_TrimType
{
	SMM_TrimType_None           = 0,  // 
	SMM_TrimType_UseSeeking     = 1,  // 
	SMM_TrimType_ParseWholeFile = 2   // 
};

static const WCHAR *XTLDescr_TrackTrimType[3] = 
{
	L"none",
	L"use_seeking",
	L"parse_whole_file"
};

typedef struct __tagTSTrimInfo
{
	INT16       nPieceNum;              // Piece number in general sequences
	LONGLONG    llStartPos;             // Time offset of start trim position
	LONGLONG    llStopPos;              // Time offset of stop trim position

	operator int () const {
		return nPieceNum;
	}

} __TSTrimInfo;

typedef std::list< __TSTrimInfo>        TSTrimInfoSTDList;

struct TrimInfoList
{
public: 
	TrimInfoList(): nListSize(0),trim_list(NULL)
	{
	}

	TrimInfoList( UINT size ):
	nListSize(size), trim_list(NULL)
	{
		resize(size);
	}

	void resize(UINT size)
	{
		Clear();
		nListSize = size;	
		if(size)
		{
			trim_list = new __TSTrimInfo[nListSize];
			memset(trim_list,0,sizeof(__TSTrimInfo)* nListSize);
		}
		
	}
	void Clear()
	{
		if( trim_list )
		{
			delete[]    trim_list;

			trim_list   = NULL;
			nListSize   = 0;
		}
	}
public:
	UINT            nListSize;
	__TSTrimInfo    *trim_list;
};

struct VERSION_INFO_2
{
	WCHAR filename[100];
	WCHAR fileversion[100];
	WCHAR filepath[1024];
	DWORD dwReserved[100];
};
struct FILE_VERSIONS_2
{
	int count;
	VERSION_INFO_2 *data;
};


struct SMM_CLIP_INFO
{
	DWORD           dwClipNum;
	REFERENCE_TIME  rtStart;
	REFERENCE_TIME  rtEnd;
	BOOL            bMute;

	WCHAR           wsfName[1024];
	DWORD           dwReserv[20];

	SMM_CLIP_INFO( ):
	rtStart     ( 0 ),
	rtEnd       ( 0 ),
	bMute       ( FALSE ),
	dwClipNum   ( 0 )
	{
		memset(wsfName,  0, sizeof(wsfName) );
		memset(dwReserv, 0, sizeof(dwReserv) );
	}

	void CopyFrom( SMM_CLIP_INFO ClipFrom )
	{
		dwClipNum   = ClipFrom.dwClipNum;
		rtStart     = ClipFrom.rtStart;
		rtEnd       = ClipFrom.rtEnd;
		bMute       = ClipFrom.bMute;
		wcscpy( wsfName, ClipFrom.wsfName);
	}
};

class SMM_TRACK_INFO
{
public: 

	int                     nVideoStream;
	int                     nAudioStream;
	WCHAR                   szMPEG2IdxFileName[1024];

	int                     nClips;
	SMM_CLIP_INFO           *pClips;

	SMM_OutputTypes         nOutType;
	SMM_TrimmAccuracyType   nTrimmAccurType;
	DWORD                   ulFlags;
	SMM_AutoSplitType       dwASMode;
	LONGLONG                llASValue;

	UINT                    nTrackPos;
	DWORD                   dwReserv[20];


	SMM_TRACK_INFO( ):
	nVideoStream    ( 0 ),
		nAudioStream    ( 0 ),
		ulFlags         ( SMM_TrimFlags_None ),
		nOutType        ( SMM_File_Type_NO ),
		nTrimmAccurType ( SMM_TrimmAccuracyType_Deflt ),
		dwASMode        ( SMM_AutoSplitType_None ),
		llASValue       ( 0 ),
		nClips          ( 0 ),
		pClips          ( NULL ),
		nTrackPos       ( 0 )
	{
		memset(szMPEG2IdxFileName,   0, sizeof(szMPEG2IdxFileName) );
		memset(dwReserv, 0, sizeof( dwReserv ) );
	}

	SMM_TRACK_INFO( const SMM_TRACK_INFO & Track ):
	nVideoStream    ( Track.nVideoStream ),
		nAudioStream    ( Track.nAudioStream ),
		dwASMode        ( Track.dwASMode ),
		llASValue       ( Track.llASValue ),
		ulFlags         ( Track.ulFlags ),
		nOutType        ( Track.nOutType ),
		nTrimmAccurType ( Track.nTrimmAccurType ),
		nTrackPos       ( Track.nTrackPos ),
		nClips          ( 0 ),
		pClips          ( NULL )
	{
		CreateClips( Track.nClips );
		memcpy( pClips, Track.pClips, sizeof(SMM_CLIP_INFO)* Track.nClips );
		wcscpy(szMPEG2IdxFileName, Track.szMPEG2IdxFileName);
	}

	~SMM_TRACK_INFO()
	{
		ClearClips();
	}

	void     CreateClips ( int nNumber )
	{
		if(0 != pClips ){
			ClearClips();
		}
		nClips = nNumber;
		pClips = new SMM_CLIP_INFO[ nClips ];
	}

	void    ClearClips ( void )
	{
		if( pClips )
		{
			delete pClips;
			pClips = NULL;
		}
		nClips = 0;
	}

	void CopyFrom( SMM_TRACK_INFO TrackFrom )
	{
		nVideoStream = TrackFrom.nVideoStream;
		nAudioStream = TrackFrom.nAudioStream ;
		ulFlags      = TrackFrom.ulFlags;
		dwASMode     = TrackFrom.dwASMode;
		llASValue    = TrackFrom.llASValue;
		wcscpy(szMPEG2IdxFileName, TrackFrom.szMPEG2IdxFileName );

		ClearClips();
		CreateClips( TrackFrom.nClips );

		for( int i = 0; i < nClips; i++ ){
			pClips[i].CopyFrom( TrackFrom.pClips[i] );
		}

		nOutType        = TrackFrom.nOutType;
		nTrimmAccurType = TrackFrom.nTrimmAccurType;
		nTrackPos       = TrackFrom.nTrackPos;
	}
};

struct SMM_GROUP_TASK
{

	CString         szDstName;
	SMM_TaskType    nTaskType;
	SMM_OutputTypes nOutType;
	SMM_TRACK_INFO  tracks[10];
	UINT            nTrackCount;


	SMM_GROUP_TASK():
	nTaskType       ( SMM_Task_Type_Trimming ),
		nTrackCount     ( 1 ),
		szDstName       ( "" ),
		nOutType		(SMM_File_Type_NO)
	{

	}
	void Clear ( void )
	{
		for(UINT n = 0; n < nTrackCount; n++) {
			tracks[n].ClearClips();
		}
	}

	TrimInfoList* ClipsToTIL( int TrNum ) const
	{
		ASSERT( TrNum < 10 );

		TrimInfoList* pTIL = new TrimInfoList( tracks[TrNum ].nClips );
		int i = 0;
		for( i = 0; i < tracks[TrNum].nClips; i++ )
		{
			pTIL->trim_list[i].llStartPos   = tracks[TrNum].pClips[i].rtStart;
			pTIL->trim_list[i].llStopPos    = tracks[TrNum].pClips[i].rtEnd;
		}
		pTIL->nListSize = i;
		return pTIL;
	}
	BOOL IsGroupEqual( SMM_GROUP_TASK &task2 )
	{

		if ( szDstName != task2.szDstName)
			return FALSE;

		if ( nTaskType != task2.nTaskType )
			return FALSE;

		if ( nTrackCount != task2.nTrackCount )
			return FALSE;

		for( UINT n = 0; n < nTrackCount; n++  )
		{
			SMM_TRACK_INFO track1 = tracks[n];
			SMM_TRACK_INFO track2 = task2.tracks[n];

			if ( track1.nVideoStream != track2.nVideoStream )
				return FALSE;

			if ( track1.nAudioStream != track2.nAudioStream )
				return FALSE;

			if ( track1.ulFlags != track2.ulFlags )
				return FALSE;

			if ( track1.dwASMode != track2.dwASMode )
				return FALSE;

			if ( track1.llASValue != track2.llASValue )
				return FALSE;

			int t = wcscmp( track1.szMPEG2IdxFileName,  track2.szMPEG2IdxFileName );
			if( t != 0 ){
				return FALSE;
			}

			if ( track1.nClips != track2.nClips )
				return FALSE;


			for ( int j = 0; j < track1.nClips; j++ )
			{
				if ( track1.pClips[j].rtEnd != track2.pClips[j].rtEnd )
					return FALSE;

				if ( track1.pClips[j].rtStart != track2.pClips[j].rtStart )
					return FALSE;

				if ( track1.pClips[j].wsfName != track2.pClips[j].wsfName )
					return FALSE;

				int t = wcscmp( track1.pClips[j].wsfName,  track2.pClips[j].wsfName);
				if( t != 0 ){
					return FALSE;
				}
			}
		}
		return TRUE;
	}
};
enum SMMCodecType
{
	SMM_CODEC_NO = 0,   //Not specified
	SMM_CODEC_DS,       //Direct Show filter
	SMM_CODEC_CM,       //Compression Manager driver
	SMM_CODEC_DMO,       //DirectX Media Object
	SMM_CODEC_CUSTOM
};

struct SMMCodec
{
	SMMCodecType    CodecType;
	GUID            CodecGUID;
	BSTR            bstCodecName;
	DWORD           dwReserved[100];
};

struct SMM_ASF_MARKER
{
	WCHAR           name[5120];
	REFERENCE_TIME  time_pos;
	ULONG           num_pos;
};

struct FAParams
{
	LONG            lBitrate;
	LONG            lGOPLength;
	int             nBFrameCount;
	BYTE            Reserved[1024];

	FAParams():         //-1 means unspecified, appropriate values will be count automatically
	lBitrate    ( -1 ),
		lGOPLength  ( -1 ),
		nBFrameCount( -1 )
	{

	}
};
// this is old stuff profile!!! use new one below
static const WCHAR * dmx_EL__mux_EL__enc_EL__dec_EL__ixr_EL = 
L"dmx_EL__mux_EL__enc_EL__dec_EL__ixr_EL";
static const WCHAR * dmx_MC__mux_MC__enc_MC__dec_MC__ixr_MC = 
L"dmx_MC__mux_MC__enc_MC__dec_MC__ixr_MC";
//////////////////////////////////////////////////////////

static const WCHAR * All_dmx_EL__mux_EL__enc_EL__dec_EL__ixr_EL =
L"dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL";

static const WCHAR * Default_Codecs_Profile =
L"dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM";

enum CodecDeveloper
{
	CodecDeveloper_Not_Specifyied   = -1,
	CodecDeveloper_Elecard_0        = 0,
	CodecDeveloper_Mainconcept_0    = 1,
	CodecDeveloper_SolveigMM_0      = 2
};






#endif //__PROPID_EDITINGENGINE__
