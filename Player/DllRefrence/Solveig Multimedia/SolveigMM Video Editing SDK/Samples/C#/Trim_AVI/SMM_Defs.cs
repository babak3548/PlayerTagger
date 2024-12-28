using System;
using System.Runtime.InteropServices;
namespace csample
{
	public class SMM_Defs
	{
		

		//Parameter GUIDs are available in the full SDK version





		public const string IID_ITrimmerObjControlCB	= "";
		public const string IID_ITrimmerObjControl		= "";
		public const string LIBID_AVITRIMMERCOMLib		= "";
		public const string CLSID_TrimmerObjControl		= "";
		public const string CLSID_VideoEditingSDK		= "";
		//---------------------------------------------------------------------------------
		public const string SMAT_InputFile				= "";
		public const string SMAT_OutputFile				= "";
		public const string SMAT_Flags					= "";
		public const string SMAT_ResetFlag				= "";
		public const string SMAT_CurrentSize			= "";
		public const string SMAT_TrimList				= "";
		public const string SMAT_Progress				= "";
		public const string SMAT_AudioStreamNumber		= "";
		public const string SMAT_VideoStreamNumber		= "";
		public const string SMAT_Callback				= "";
		public const string SMAT_GetVersions			= "";
		public const string SMAT_BatchFileName			= "";
		public const string SMAT_CurrentBatchTask		= "";
		public const string SMAT_BatchTasksNum			= "";
		public const string SMAT_StreamLength			= "";
		public const string SMAT_SetAutoSplittingMode	= "";
		public const string SMAT_SetAutoSplittingValue	= "";
		public const string SMAT_GetProcessingPartNumber = "";
		public const string SMAT_OutputType				= "";
		public const string SMAT_SilentPath				= "";
		public const string SMAT_MPEG2IndexFileName		= "";
		public const string SMAT_MPEG2CodecsSet			= "";
		public const string SMAT_TaskType				= "";
		public const string SMAT_TrackInfo				= "";
		public const string SMAT_TrimAccuracy			= "";
		public const string SMAT_OutIndexFile			= "";
		public const string SMAT_StartIndexation		= "";
		public const string SMAT_GetFileType			= "";
		public const string SMAT_ValidateFiles			= "";
		public const string SMAT_ASFMarkersCount		= "";
		public const string SMAT_ASFMarkerRemove		= "";
		public const string SMAT_ASFMarker				= "";

    
		public enum SMM_OutputTypes
		{
			SMM_File_Type_NO = 0,
			SMM_File_Type_AVI = 1,          // audio video interleaving format
			SMM_File_Type_ASF = 2,          // advanced streaming format
			SMM_File_Type_MPA = 3,          // mpeg audio
			SMM_File_Type_MPEG2_PS = 4,     // MPEG-2 Program Stream
			SMM_File_Type_MPEG2_TS = 5,     // MPEG-2 Transpot Stream
			SMM_File_Type_MPEG2_VES = 6		// MPEG-2 Video Elementary Stream
		}

		[StructLayout(LayoutKind.Sequential)] 
			public struct TrimInfoList 
		{
			public int nListSize;
			public IntPtr trim_list; 
		}

		[StructLayout(LayoutKind.Sequential)] 
			public struct __TSTrimInfo
		{
			public Int16	nPieceNum;				// Piece number in general sequences
			public Int64	llStartPos;				// Time offset of start trim position
			public Int64   	llStopPos;				// Time offset of stop trim position
		}
	}
}
