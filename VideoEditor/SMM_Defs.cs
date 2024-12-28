using System;
using System.Runtime.InteropServices;
namespace VideoEditor
{
	public class SMM_Defs
	{
		

		//Parameter GUIDs are available in the full SDK version

        public const string CLSID_TrimmerObjControl = "B61C3708-CAA8-48CA-9D9C-682D0A5A3852";
        public const string CLSID_VideoEditingSDK = "7750A708-3EEB-45b9-8179-077689D77E33";
        public const string g_ActionKey_Trim = "BC342AC510A3DD6697019CA8901B7F1ECFA25F3285801F10FDE815E6830BC3387740137005ADCCD7483F1A7AF124AC646DEDC666E959341DF145423C8ADCFBAC25B7ED16F9AFFDF37E5BF6BE18FD1AA847127A0941E5743191C9EF3F3FF71F9149F74CF1535D0458C6DB2934B87D55EC86F9A83C225702A4CE3A57BE8FC97E694AE86A6700F4801459E563548C3B2EAA25B7ED16F9AFFDF3E1381CAC16C542DD522D7FD01E8D5C9B0B0A9D59E294E028711E7AECCDE50D6D86F9A83C225702A486F9A83C225702A451D589660F5D3C6B25B7ED16F9AFFDF348C62F1A6950BF264B5D9AB0769FE7597E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BBE07518D536E5801DC6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BB935F4D6E792283D64A0983EA6E5EC53AC6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BB935F4D6E792283D6BFE0F6248301AED4C6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BB935F4D6E792283D6D1B2A2FA72C1D18FAE3CF902F4DC779286F9A83C225702A44FB05EBA3E2F234479121FD58DA68D408B579933EE69794DB511C7AC078D50444C70D083B59BEF3E9C6AD18FD56563F57E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BB3E0B7701DBA0294CD1B2A2FA72C1D18FAE3CF902F4DC779286F9A83C225702A44FB05EBA3E2F234479121FD58DA68D408B579933EE69794D6C0A94A9151CBA7FCABDD2C6CD623B84F3E71992AFAF623D86F9A83C225702A486F9A83C225702A451D589660F5D3C6B25B7ED16F9AFFDF348C62F1A6950BF26C7202B890B04180ACD98DD99F73AFB8CC6DB2934B87D55EC86F9A83C225702A4F304D0069CB68781EB9C6865C020B3D518990C004D04DD44D213841E96F178AB86F9A83C225702A4CE3A57BE8FC97E694AE86A6700F4801459E563548C3B2EAA25B7ED16F9AFFDF3E1381CAC16C542DD522D7FD01E8D5C9B0B0A9D59E294E0286AA2476CD56B5B327E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BBB0768EC191D5B3FAC6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BBB5225BE8E082E628AE3CF902F4DC779286F9A83C225702A44FB05EBA3E2F234479121FD58DA68D408B579933EE69794D3D4225E9B73B77F51F0B35D78A50D5CA86F9A83C225702A486F9A83C225702A451D589660F5D3C6B25B7ED16F9AFFDF348C62F1A6950BF263D1003555B24688C7E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BB83F3B171DC5B507DA7AA4D57DC7CE6A77E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BB83F3B171DC5B507D963B7395484ED7407E765D430D81E39C86F9A83C225702A446901E7A438B54ED6DC57B3EE0E0CA39D0EDD6123397B0BB83F3B171DC5B507D21C8129B39921FFDC6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BB935F4D6E792283D6B63F0465C4B80C6BF3E71992AFAF623D86F9A83C225702A486F9A83C225702A451D589660F5D3C6B25B7ED16F9AFFDF348C62F1A6950BF26461799A4D9A58F6621C8129B39921FFDC6DB2934B87D55EC86F9A83C225702A4106CC038D7E0099CCD1A450CBE8841D4074E16A4777C44BBD6BEEAFB537D22F6AE3CF902F4DC779286F9A83C225702A44FB05EBA3E2F234479121FD58DA68D408B579933EE69794D6C0A94A9151CBA7FCABDD2C6CD623B84F3E71992AFAF623D86F9A83C225702A486F9A83C225702A451D589660F5D3C6B25B7ED16F9AFFDF348C62F1A6950BF26C7202B890B04180ACD98DD99F73AFB8CC6DB2934B87D55EC86F9A83C225702A4F304D0069CB68781EB9C6865C020B3D518990C004D04DD44B260AF5D694B4B1CF4EAC99A19985677BBF750315266F37860BA164CC8A75237A73CFA1C2DCE9C4A";
        public const string IID_ITrimmerObjControl = "9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9";
        public const string IID_ITrimmerObjControlCB = "33968711-8887-46D4-A71B-9B1B061EEDCA";
        public const string LIBID_AVITRIMMERCOMLib = "958BB6C7-14FB-49EF-AFAE-678155680C6A";
        public const string SMAT_ActionKey = "6DB8381C-2D6D-4904-8333-C693E9BC3F68";

        /// <summary>
        /// Sets or retrieves ASF marker with specified name and position
        /// </summary>
        public const string SMAT_ASFMarker = "c022a53f-ce3d-4c03-baed-11fcc7ccded2";

        /// <summary>
        /// Removes a marker from an input ASF
        /// </summary>
        public const string SMAT_ASFMarkerRemove = "72825bb9-b725-456a-8e2c-d650acdfb674";

        /// <summary>
        /// Retrieves a count of markers contained in an input ASF
        /// </summary>
        public const string SMAT_ASFMarkersCount = "0b9c6ab5-f968-46a8-85e1-09fa8b8a734b";

        /// <summary>
        /// Sets a number of an audio stream to be trimmed
        /// </summary>
        public const string SMAT_AudioStreamNumber = "5EB26970-133F-4AD1-BE21-A849618CA8F3";

        /// <summary>
        /// Sets a number of a video stream to be trimmed
        /// </summary>
        public const string SMAT_VideoStreamNumber = "D9898809-5987-4EBC-967D-C595465923A1";

        /// <summary>
        /// Specifies an input batch file name
        /// </summary>
        public const string SMAT_BatchFileName = "909605C1-F9CE-4360-9AFA-0BAE16E95784";

        /// <summary>
        /// Retrieves a number of a current task being processed
        /// </summary>
        public const string SMAT_CurrentBatchTask = "7AF7B8FE-FA2F-44f2-915E-D668EE32E8A6";

        /// <summary>
        /// Retrieves a count of tasks a set batch file contains
        /// </summary>
        public const string SMAT_BatchTasksNum = "102C7E6B-2112-4a52-BD2B-1E80DF137699";

        /// <summary>
        /// Sets a callback COM interface: ITrimmerObjControlCB
        /// </summary>
        public const string SMAT_Callback = "DA1ED33F-9EF4-4c98-BCA5-66FF917FFCBE";

        /// <summary>
        /// Sets the set of codecs to use for MPEG2 files editing
        /// </summary>
        public const string SMAT_CodecsSet = "17B25796-46AB-44a6-BBF4-9A3A160E63FB";
 
        /// <summary>
        /// Retrieves output AVI file size during trimming process
        /// </summary>
        public const string SMAT_CurrentSize = "12258211-7D2F-4373-84C7-B755A8A40DD9";
        /// <summary>
        /// Sets trimming configuration flags to be set
        /// </summary>
        public const string SMAT_Flags = "AAF40DFF-0698-4424-87DC-3B1E2D60CDD8";
        /// <summary>
        /// Sets trimming configuration flags to be reset
        /// </summary>
        public const string SMAT_ResetFlag = "19F90CB9-A5EA-4821-A8BA-AD6FB9422B9C";

        /// <summary>
        /// Returns the type of the file
        /// </summary>
        public const string SMAT_GetFileType = "534D4154-5F47-6574-4669-6C6554797065";
        public const string SMAT_GetProcessingPartNumber = "BE0064CB-5172-4fc9-A07E-305FB1FC2EF5";

        /// <summary>
        /// Retrieves all the objects versions being used by the engine
        /// </summary>
        public const string SMAT_GetVersions = "BD62FD5E-B517-4f8f-976E-5FA1ACE4F9DC";

        /// <summary>
        /// Specifies an input media file name
        /// </summary>
        public const string SMAT_InputFile = "04890910-6B0B-465D-B507-2568710565FD";

        /// <summary>
        /// Provides the name of MPEG2 index filename.
        /// </summary>
        public const string SMAT_MPEG2IndexFileName = "1ade47b6-bb44-4820-a077-6116f861775b";
        public const string SMAT_OutIndexFile = "534D4154-5F46-696C-6554-6F496E646578";
        /// <summary>
        /// Specifies an output media file name
        /// </summary>
        public const string SMAT_OutputFile = "b45c2624-07e5-4905-A1A5-23DDD26EFC13";

        /// <summary>
        /// Specifies an output file type defauly is input type
        /// </summary>
        public const string SMAT_OutputType = "3F20F1D6-1132-4e28-AB6B-ED94700C2949";

        /// <summary>
        /// Retrieves a progress of trimming process
        /// </summary>
        public const string SMAT_Progress = "AE82DE01-D84B-4EE5-90AA-052B108C4380";


        public const string SMAT_SetAutoSplittingMode = "EC9B5486-F1C9-4d51-B240-D6355BA2E2F5";
        public const string SMAT_SetAutoSplittingValue = "2DC69654-929E-46e9-B0CC-6B33D5AAB4C3";

        /// <summary>
        /// Sets the registry path that stores paths of filters to use in silent mode
        /// </summary>
        public const string SMAT_SilentPath = "2e83b26b-65b3-4609-95b5-e918a96ae151";
        public const string SMAT_StartIndexation = "534D4154-5f53-7461-7274-496e64657861";
        public const string SMAT_StreamLength = "D206760E-C900-4A94-BB3D-4C1998BBE120";
        /// <summary>
        /// The type of process to be performed
        /// </summary>
        public const string SMAT_TaskType = "a5e6000d-52d9-4f41-9091-11c4fdae990b";

        /// <summary>
        /// Passes the parameters of the chosen files to Editing Engine
        /// </summary>
        public const string SMAT_TrackInfo = "FA8BD847-4DC6-492d-9585-E86654CDAC1F";
        public const string SMAT_TrimAccuracy = "4B07D80A-0FA6-4d69-8438-159CB1BC749F";

        /// <summary>
        /// Sets trimming parameters
        /// </summary>
        public const string SMAT_TrimList = "C1D0F958-4489-4322-80CD-898089A220C1";

        /// <summary>
        /// Validate the parameters of chosen files.
        /// </summary>
        public const string SMAT_ValidateFiles = "534D4154-5661-6C69-6461-746546696C65";
   
    
		public enum SMM_OutputTypes
		{
			SMM_File_Type_NO = 0,
			SMM_File_Type_AVI = 1,          // audio video interleaving format
			SMM_File_Type_ASF = 2,          // advanced streaming format
			SMM_File_Type_MPA = 3,          // mpeg audio
			SMM_File_Type_MPEG2_PS = 4,     // MPEG-2 Program Stream
			SMM_File_Type_MPEG2_TS = 5,     // MPEG-2 Transpot Stream
			SMM_File_Type_MPEG2_VES = 6	,	// MPEG-2 Video Elementary Stream
            SMM_File_Type_MPEG1_SYS = 7,
            SMM_File_Type_MPEG1_VES = 8,
            SMM_File_Type_WAV = 9,
            SMM_File_Type_MPEG4_AVC = 10,
            SMM_File_Type_MKV = 11,
            SMM_File_Type_MP4 = 12,
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

        [StructLayout(LayoutKind.Sequential)] 
        public struct CInterval_info
        {
            public bool bselect;
            public long llend;
            public long llstart;
            public int N;
        }

        public enum SMM_TaskType
        {
            SMM_Task_Type_Trimming = 0,
            SMM_Task_Type_Joining = 1,
            SMM_Task_Type_Indexation = 5,
        }

        public enum SMM_TrimmAccuracyType
        {
            SMM_TrimmAccuracyType_Deflt = -1,
            SMM_TrimmAccuracyType_GOP = 0,
            SMM_TrimmAccuracyType_Frame = 1,
        }

     [Flags]
     public  enum SMM_TrimFlags
        {
            SMM_TrimFlags_None = 0,
            SMM_TrimFlags_ObeySampleTimes = 2,
            SMM_TrimFlags_VideoOnly = 8,
            SMM_TrimFlags_AudioOnly = 16,
            SMM_TrimFlags_GettingSize = 32,
            SMM_TrimFlags_InASF = 64,
            SMM_TrimFlags_UsePositioning = 128,
            SMM_TrimFlags_IgnoreTrimErrors = 256,
            SSM_TrimFlags_TrimOverlappedIntervals = 512
        }

        //SMM_TrimFlags_None = 0,
        //    SMM_TrimFlags_ObeySampleTimes = 0x2,
        //    SMM_TrimFlags_VideoOnly = 0x8,
        //    SMM_TrimFlags_AudioOnly = 0x10,
        //    SMM_TrimFlags_GettingSize = 0x20,
        //    SMM_TrimFlags_InASF = 0x40,
        //    SMM_TrimFlags_UsePositioning = 0x80,
        //    SMM_TrimFlags_IgnoreTrimErrors = 0x100,
        //    SSM_TrimFlags_TrimOverlappedIntervals = 0x200

//        struct SMM_GROUP_TASK {
//String szDstName ;
//SMM_TaskType nTaskType ;
//SMM_TRACK_INFO tracks[10] ;
//UINT nTrackCount;
//}
//     public   class SMM_TRACK_INFO {
//int nVideoStream;
//int nAudioStream;
//char szMPEG2IdxFileName[1024];
//SMM_CLIP_INFO *pClips;
//Int nClips;
//SMM_OutputTypes nOutType;
//SMM_TrimmAccuracyType nTrimmAccurType;
//DWORD ulFlags;
//SMM_AutoSplitType dwASMode;
//LONGLONG llASValue;
//UINT nTrackPos;
//DWORD dwReserv[20];
//void CreateClips( int nNumber );
//void ClearClips ( void );
//void CopyFrom ( SMM_TRACK_INFO TrackFrom );
//};

	}
}
