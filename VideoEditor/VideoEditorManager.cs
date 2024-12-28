using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;
using AVITRIMMERCOMLib;
using Utility;

namespace VideoEditor
{

   public class VideoEditorManager : IUpdateProgress
    {

        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName);
        [DllImport("user32.dll")]
        public static extern int SendMessage(int hWnd, uint Msg, int wParam, int lParam);

        public const int WM_SYSCOMMAND = 0x0112;
        public const int SC_CLOSE = 0xF060;

        public bool m_bCompleted;		//current process' state
        public bool m_bNeedIndexing;
        public bool m_bErrorOccured;
        private long m_Duration;		//Current stream duration
        private bool m_cbFATrimEnable;
        private string m_InPutfileName;
        private string m_OutPutfileName;
        private const string Supported_files = "Supported files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv|All files (*.*)|*.*";

        private AVITRIMMERCOMLib.TrimmerObjControl m_Trimmer;
        private AVITRIMMERCOMLib.IModuleConfig m_ModuleConfig;
        
 
        private Helper m_CB;
        Helper.CInterval_info[] m_Intervals;

        public void Init(ITrimmerObjControlCB CB)
        {
            m_Trimmer = new AVITRIMMERCOMLib.TrimmerObjControl();
          
            m_ModuleConfig = (AVITRIMMERCOMLib.IModuleConfig)m_Trimmer;
            Type t = m_Trimmer.GetType();
            
            
            m_CB = new Helper();

            ///Initial Engine settings:
            
            //Set Callback
            Guid input = new Guid(Helper.SMAT_Callback);
            object val = CB;// m_CB;
            
            if (false == SetValue(input, val))
                return;

           


            //Set MPEG-2 profile
            Guid profile = new Guid(Helper.SMAT_CodecsSet);
            val = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM";
            SetValue(profile, val);

            //Set Silent Path. Used when MPEG-2 components aren't registered
            val = "CLSID\\{" + Helper.CLSID_VideoEditingSDK + "}\\Components";
            Guid SilentPath = new Guid(Helper.SMAT_SilentPath);
            SetValue(SilentPath, val);

            val = Helper.g_ActionKey_Trim;
            Guid ActionKey = new Guid(Helper.SMAT_ActionKey);
            SetValue(ActionKey, val);

        }
        public void register()
        {
           object  val = Helper.g_ActionKey_Trim;
            Guid ActionKey = new Guid(Helper.SMAT_ActionKey);
            SetValue(ActionKey, val);
        }
        private bool SetValue(Guid param, object val)
        {
            try
            {
                int x=0;
                m_ModuleConfig.SetValue(ref param, ref val);
             
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }
       
        private void StartIndexing()
        {

            Guid outIndex = new Guid(Helper.SMAT_OutIndexFile);
            object var = m_InPutfileName + ".mlmix";
            SetValue(outIndex, var);

            Guid StartIndex = new Guid(Helper.SMAT_StartIndexation);
            var = true;
            if (false == SetValue(StartIndex, var))
                return;

            m_bNeedIndexing = true;
            m_bCompleted = false;
           
        }
        private bool NeedIndexing(Helper.SMM_OutputTypes Type)
        {
            string txt = "File type is\r\n";

            if (Type == Helper.SMM_OutputTypes.SMM_File_Type_AVI)
            {
                txt += "AVI";
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_ASF)
            {
                txt += "ASF";
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPA)
            {
                txt += "mp3";
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_PS)
            {
                txt += "mpeg2 PS";
                return true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_TS)
            {
                txt += "mpeg2 TS";
                return true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_VES)
            {
                txt += "mpeg2 VES";
               return  true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG1_SYS)
            {
                txt += "mpeg1 SYS";
                return true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG1_VES)
            {
                txt += "mpeg1 VES";
                return true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_WAV)
            {
                txt += "wav";
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG4_AVC)
            {
                txt += "AVC VES";
                return true;
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MKV)
            {
                txt += "MKV";
            }
            else if (Type == Helper.SMM_OutputTypes.SMM_File_Type_MP4)
            {
                txt += "MP4";
            }
            else
            {
                txt += "unsupported";
                
                return false;
            }
            return false;
        }
        private bool SupportFrameAccurate(Helper.SMM_OutputTypes Type)
        {
            //Frame accurate trimming for AVI and audio only files is not supported
            if (Type == Helper.SMM_OutputTypes.SMM_File_Type_AVI ||
                Type == Helper.SMM_OutputTypes.SMM_File_Type_WAV ||
                Type == Helper.SMM_OutputTypes.SMM_File_Type_MPA)
                return false;
            //For other formats we can choose between GOP and Frame accuracy
            //But Frame is by default
            return true;
        }

        private Helper.CInterval_info GetIntervalInfo(int num)
        {
            if (num < m_Intervals.Length)
                return m_Intervals[num];
            return new Helper.CInterval_info(); 
            //Helper.CInterval_info intervalInfo = new Helper.CInterval_info();

            //IntPtr ptr = Marshal.AllocCoTaskMem(Marshal.SizeOf(intervalInfo));
            //this.slider.GetIntervalInfo1(num, (int)ptr);
            //intervalInfo = (Helper.CInterval_info)Marshal.PtrToStructure(ptr, typeof(Helper.CInterval_info));
            //Marshal.FreeCoTaskMem(ptr);
            //return intervalInfo;
        }

        public void InitEngine(VideoEditor.SMM_Defs.SMM_TrimFlags Flags = 0)
        {
            Guid TaskType = new Guid(Helper.SMAT_TaskType);
            object objType = Helper.SMM_TaskType.SMM_Task_Type_Trimming;
            //Set task type (trimming)
            SetValue(TaskType, objType);

            int IntervalsCount = m_Intervals.Length;

            Helper.TrimInfoList TrimList;
            TrimList.nListSize = IntervalsCount; //Count of pieces
            Helper.__TSTrimInfo[] tmp = new Helper.__TSTrimInfo[IntervalsCount];
            for (int i = 0; i < IntervalsCount; i++)
            {
                // get interval props
                Helper.CInterval_info intervalInfo = m_Intervals[i];

                tmp[i].nPieceNum = (Int16)i;//Number of the piece
                tmp[i].llStartPos = intervalInfo.llstart;
                tmp[i].llStopPos = intervalInfo.llend;
            }

            TrimList.trim_list = Marshal.UnsafeAddrOfPinnedArrayElement(tmp, 0); //getting pointer to array
            int cb = Marshal.SizeOf(TrimList);
            IntPtr ptr = Marshal.AllocHGlobal(cb); // reallocating memory for object
            Marshal.StructureToPtr(TrimList, ptr, true); // copying object to memory block
            object var = ptr;
            Guid List = new Guid(Helper.SMAT_TrimList);
            SetValue(List, var);
            Marshal.DestroyStructure(ptr, TrimList.GetType());	// clear the memory block
            Marshal.FreeHGlobal(ptr);				// free the memory block

            //Set trimming accuracy
            Guid AccuracyType = new Guid(Helper.SMAT_TrimAccuracy);
            object objAccuracy = Convert.ToInt32(m_cbFATrimEnable);
            SetValue(AccuracyType, objAccuracy);
           //if(Flags>0) setFlags(Flags);
            m_ModuleConfig.CommitChanges(out var); //commit all parameters set
            
        }

        private void SetInputFile(string FileName)
        {
            //Set input File Name
            Guid input = new Guid(Helper.SMAT_InputFile);
            object val;
            val = FileName;
            m_InPutfileName = FileName;
            SetValue(input, val);

            //Find out the file type
            Guid FType = new Guid(Helper.SMAT_GetFileType);
            val = null;
            m_ModuleConfig.GetValue(ref FType, out val);
            Helper.SMM_OutputTypes Type = (Helper.SMM_OutputTypes)val;
            m_bNeedIndexing = NeedIndexing(Type);
            m_cbFATrimEnable = SupportFrameAccurate(Type);
            Guid length = new Guid(Helper.SMAT_StreamLength);
            m_ModuleConfig.GetValue(ref length, out val);

            m_Duration = (long)(((double)val) * 10000000.0);
            //if (m_bNeedIndexing)
            //    StartIndexing();
        }

        private void SetOutputFile(string FileName)
        {

            if (FileName == "")
                return;
            m_OutPutfileName = FileName;
            Guid output = new Guid(Helper.SMAT_OutputFile);
            object val;

            //Set input File Name
            val = m_OutPutfileName;
            SetValue(output, val);
        }
       private void  setFlags( VideoEditor.SMM_Defs.SMM_TrimFlags Flags=0)
       {
           
           object val;
           Guid fg=new Guid(SMM_Defs.SMAT_Flags);
           m_ModuleConfig.GetValue(ref fg, out val);
           SMM_Defs.SMM_TrimFlags f = (SMM_Defs.SMM_TrimFlags)Enum.Parse(typeof(SMM_Defs.SMM_TrimFlags), val.ToString());
           f |= Flags;
           val=f;
           SetValue(fg, val);

       }
       public long DurationMediaSource(string FileName,ITrimmerObjControlCB TrimControl)
       {
           Init(TrimControl);
           SetInputFile(FileName);
           return m_Duration;
       }

        public bool StartProcess(string InputFileName, string OutPutFileName,ITrimmerObjControlCB TrimControl ,Helper.CInterval_info[] Intervals, VideoEditor.SMM_Defs.SMM_TrimFlags Flags=0)
        {
            try
            {
                Init(TrimControl);
                m_Intervals = Intervals;

                SetInputFile(InputFileName);
                SetOutputFile(OutPutFileName);
                InitEngine(Flags);
                System.Threading.Thread t = new System.Threading.Thread(new System.Threading.ThreadStart(this.Crack));
                t.Start();
                m_Trimmer.Start();
                return true;
            }
            catch (System.Exception x)
            {
                TrimControl.OnStop();
                MessageBox.Show(x.Message);
                return false;
            }

        }


        public bool Validate(string InputFileName, string OutPutFileName, Helper.CInterval_info[] Intervals, string errorMessage="")
        {
            var temp = Intervals;
            var result = (from i in Intervals from t in temp 
                         where (i.llstart > t.llstart && i.llstart <= t.llend) || ((t.llstart > i.llstart && t.llstart <= i.llend)  || i.llstart>=i.llend) select i).Any();
            return !result;
        }

        public void Stop()
        {
            if (m_bNeedIndexing)
            {
                Guid StartIndex = new Guid(Helper.SMAT_StartIndexation);
                object var = false;
                SetValue(StartIndex, var);
                m_bNeedIndexing = false;
            }
            else
                m_Trimmer.Stop();
        }
        public String ExtOfFile(String sz)
        {
            int lastdotpos = sz.LastIndexOf(".");
            return sz.Substring(lastdotpos, sz.Length - lastdotpos);
        }
        public int GetProgress()
        {
            //Get progress value in %
            Guid progress = new Guid(Helper.SMAT_Progress);
            object val=0;

            try
            {
                m_ModuleConfig.GetValue(ref progress, out val);
            }
            catch (System.Exception)
            {
                
                
            }

            
            return (int)val;
        }
       
        void UnregisterFromNotifies(IModuleCallback pModuleCallback)
        {
        }
        public void Crack()
        {
            int iHandle = FindWindow(null, "SolveigMM Video Editing Engine");
            while (iHandle <= 0)
            {
                iHandle = FindWindow(null, "SolveigMM Video Editing Engine");
            }
             
            if (iHandle > 0)
            {
                // close the window using API        
                SendMessage(iHandle, WM_SYSCOMMAND, SC_CLOSE, 0);
               
            }  
        }
    }
}
