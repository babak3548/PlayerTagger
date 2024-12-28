using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;
using System.Collections;
using DevExpress.XtraEditors;
namespace VideoEditor.Join
{
    public partial class Form1 : DevExpress.XtraEditors.XtraForm
    {
        public Form1()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();
#if RESTRICTED
			MessageBox.Show(this,
					"This is an evaluation version of SDK that doesn't contain all necessary headers.\r\nParameter GUIDs are available in the full SDK version",
					"ERROR",
					MessageBoxButtons.OK,
					MessageBoxIcon.Information
					);
			buttonInput.Enabled = false;
			return;
#endif
            try
            {
                m_Trimmer = new AVITRIMMERCOMLib.TrimmerObjControl();
                m_ModuleConfig = (AVITRIMMERCOMLib.IModuleConfig)m_Trimmer;
                m_CB = new Join.Helper(this);
            }
            catch (System.Exception e)
            {
                // labelStatus.Text = "Error: Couldn't initialize basic components or interfaces.\r\n" + e.Message;
                labelStatus.Text = "خطا :کامپوننت های اصلی فابل اجرا نمی باشد\r\n" + e.Message;
                EnableControls(false);
                return;
            }

            //Set Callback
            Guid input = new Guid(Join.Helper.SMAT_Callback);
            object val = m_CB;
            if (false == SetValue(input, val))
                return;

            m_Ranges = new ArrayList();

            //Set MPEG-2 profile
            Guid profile = new Guid(Join.Helper.SMAT_CodecsSet);
            val = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM__dmx<type:FLV>_SM__mux<type:FLV>_SM";
            SetValue(profile, val);

            val = Join.Helper.g_ActionKey_Join;
            Guid ActionKey = new Guid(Join.Helper.SMAT_ActionKey);
            SetValue(ActionKey, val);

            //Set Silent Path.
            //Used only for MPEG-2 files joining when MPEG-2 components aren't registered
            val = "CLSID\\{" + Join.Helper.CLSID_VideoEditingSDK + "}\\Components";
            Guid SilentPath = new Guid(Join.Helper.SMAT_SilentPath);
            SetValue(SilentPath, val);

            Timer1.Tick += new EventHandler(OnTimer);
        }

        private bool SetValue(Guid param, object val)
        {
            try
            {
                m_ModuleConfig.SetValue(ref param, ref val);
            }
            catch (Exception ex)
            {
                // labelStatus.Text = "Error: " + ex.Message;
                labelStatus.Text = "خطا: " + ex.Message;
                return false;
            }
            return true;
        }

        private void buttonInput_Click(object sender, System.EventArgs e)
        {
            //labelStatus.Text = "";
            //OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

            //openFileDialog.Filter = "Media Files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.webm;*.m2ts;*.h264;*.mov;*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv;*.flv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.webm;*.m2ts;*.h264;*.mov;*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv;*.flv|All Files|*.*";
            //openFileDialog.FilterIndex = 1;
            //openFileDialog.RestoreDirectory = true;
            //openFileDialog.CheckFileExists = true;
            //openFileDialog.CheckPathExists = true;
            //openFileDialog.Multiselect = true;
            //openFileDialog.Title = "Choose files to join:";

            //if (openFileDialog.ShowDialog() != DialogResult.OK)
            //{
            //    return;
            //}

            //string[] files = openFileDialog.FileNames;
            //Array.Sort(files);

            //foreach (string FileName in files)
            //{
            //    AppendList(FileName);
            //}
        }
        private void AppendList(string csFileName)
        {
            object var = csFileName;
            SetValue(new Guid(Join.Helper.SMAT_InputFile), var);
            try
            {
                Join.Helper.SMM_OutputTypes ftype;
                Guid fTypeGuid = new Guid(Join.Helper.SMAT_GetFileType);
                m_ModuleConfig.GetValue(ref fTypeGuid, out var);
                ftype = ((Join.Helper.SMM_OutputTypes)var);

                if (CheckSupportedFileTypes(ftype))
                {
                    ListViewItem item = new ListViewItem(csFileName);
                    string stType = Join.Helper.XTLDescr_TrackOutType[(int)ftype];
                    item.SubItems.Add(stType);
                    item.ForeColor = Color.White;
                    listView1.Items.Add(item);
                    m_smm_type = (int)ftype;
                }
            }
            catch (System.Exception e)
            {
                // labelStatus.Text = "Invalid input: " + e.Message;
                labelStatus.Text = "فایلی انتخابی اشتباه: " + e.Message;
            }
        }
        private bool CheckSupportedFileTypes(Join.Helper.SMM_OutputTypes type)
        {
            if (type <= Join.Helper.SMM_OutputTypes.SMM_File_Type_NO ||
                type >= Join.Helper.SMM_OutputTypes.SMM_File_Type_COUNT)
                return false;
            else
                return true;
        }


        private void buttonJoin_Click(object sender, System.EventArgs e)
        {
            labelStatus.Text = "";
            if (listView1.Items.Count == 0)
            {
                labelStatus.Text = "Error: No files selected. Please choose the files to be joined.";
                return;
            }
            string filename = listView1.Items[0].Text;
            SaveFileDialog saveFileDialog = new System.Windows.Forms.SaveFileDialog();

            string sz = ExtOfFile(filename);
            saveFileDialog.FileName = "Joined";
            saveFileDialog.DefaultExt = sz;

            sz = "*" + sz;
            sz = sz + "|" + sz;
            saveFileDialog.Filter = sz;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.CheckPathExists = true;
            saveFileDialog.Title = "Choose output file:";

            if (saveFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            string output = saveFileDialog.FileName;
            object var;
            int cb;

            //setting task type
            var = Join.Helper.SMM_TaskType.SMM_Task_Type_Joining;
            SetValue(new Guid(Join.Helper.SMAT_TaskType), var);

            //setting output file
            var = output;
            SetValue(new Guid(Join.Helper.SMAT_OutputFile), var);
            //setting output type
            var = m_smm_type;
            SetValue(new Guid(Join.Helper.SMAT_OutputType), var);

            //fill in SMM_TRACK_INFO
            Join.Helper.SMM_TRACK_INFO track = new Join.Helper.SMM_TRACK_INFO();

            track.nOutType = m_smm_type;
            track.nTrimmAccurType = -1;
            track.ulFlags = Convert.ToUInt32(0);
            track.dwASMode = 0;
            track.llASValue = Convert.ToInt64(0);
            track.nTrackPos = Convert.ToUInt32(0);
            track.nVideoStream = -1;
            track.nAudioStream = -1;
            track.szMPEG2IdxFileName = Convert.ToString(0);
            track.nClips = listView1.Items.Count;

            //fill in pClips
            Join.Helper.SMM_CLIP_INFO[] clips = new Join.Helper.SMM_CLIP_INFO[track.nClips];

            cb = Marshal.SizeOf(typeof(Join.Helper.SMM_CLIP_INFO));
            track.pClips = Marshal.AllocHGlobal(cb * track.nClips);
            Int32 curPointer;
            curPointer = track.pClips.ToInt32();

            for (int i = 0; i < track.nClips; i++)
            {
                ListViewItem li;
                IntPtr curPtr = new IntPtr(curPointer + i * cb);
                li = listView1.Items[i];
                //AddClipToTrack(clips[i], li.Text);
                clips[i].dwClipNum = Convert.ToInt32(0);
                clips[i].rtStart = Convert.ToInt64(0);
                clips[i].rtEnd = Convert.ToInt64(0);
                clips[i].bMute = 0;
                clips[i].wsfName = li.Text + Convert.ToChar(0);

                Marshal.StructureToPtr(clips[i], curPtr, false);
            }
            //setting SMM_TRACK_INFO
            cb = Marshal.SizeOf(track);
            IntPtr ptr = Marshal.AllocHGlobal(cb);
            Marshal.StructureToPtr(track, ptr, false);
            var = ptr;

            SetValue(new Guid(Join.Helper.SMAT_TrackInfo), var);

            Marshal.DestroyStructure(track.pClips, typeof(Join.Helper.SMM_CLIP_INFO));
            Marshal.FreeHGlobal(track.pClips);
            Marshal.DestroyStructure(ptr, typeof(Join.Helper.SMM_TRACK_INFO));
            Marshal.FreeHGlobal(ptr);

            //commit
            var = 0;
            m_ModuleConfig.CommitChanges(out var);

            bool bRun = true;

            int hr;
            try
            {
                //validate files for joining
                Guid ValidateGuid = new Guid(Join.Helper.SMAT_ValidateFiles);
                m_ModuleConfig.GetValue(ref ValidateGuid, out var);

                hr = Convert.ToInt32(var);
                if (1 == hr)
                {
                    if (MessageBox.Show("Some chosen tracks have different parameters!\n" +
                        "There may be some problems during output file playback.\n" +
                        "Would you like to continue?", "Joining Troubles", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                        bRun = false;
                }
                else if (hr != 0)
                {
                    MessageBox.Show("Incompatible files detected or error orurred.\n", "Error");
                    bRun = false;
                }
            }
            catch (System.Exception ex)
            {
                hr = Marshal.GetHRForException(ex);
                MessageBox.Show("Validate files HRESULT = " + hr.ToString(), "Error");
            }

            if (bRun)
            {
                try
                {
                    //run
                    VideoEditorManager VideoEditorManager = new VideoEditor.VideoEditorManager();
                    m_bFinished = false;
                    System.Threading.Thread t = new System.Threading.Thread(new System.Threading.ThreadStart(VideoEditorManager.Crack));
                    t.Start();
                    m_Trimmer.Start();
                    Timer1.Enabled = true;
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("On start join", "Error");
                }
            }
        }
        public string ExtOfFile(String sz)
        {
            int lastdotpos = sz.LastIndexOf(".");
            return sz.Substring(lastdotpos, sz.Length - lastdotpos);
        }



        private void OnTimer(Object myObject, EventArgs myEventArgs)
        {
            object var = 0;
            //getting current trimming progress
            Guid ProgressGuid = new Guid(Join.Helper.SMAT_Progress);
            m_ModuleConfig.GetValue(ref ProgressGuid, out var);
            int progress = Convert.ToInt32(var);

            if (progress < ProgressBar1.Minimum)
                progress = ProgressBar1.Minimum;
            if (progress > ProgressBar1.Maximum)
                progress = ProgressBar1.Maximum;

            ProgressBar1.Value = progress;
            ProgressBar1.Update();

            if (m_bFinished)
            {
                Timer1.Enabled = false;
                ProgressBar1.Value = 0;
                ProgressBar1.Update();
            }

        }

        private void buttonClear_Click(object sender, System.EventArgs e)
        {

        }
        private void EnableControls(bool bBlock)
        {
            buttonInput.Enabled = bBlock;
            buttonClear.Enabled = bBlock;
            buttonJoin.Enabled = bBlock;
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "";
            OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

            openFileDialog.Filter = "Media Files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.webm;*.m2ts;*.h264;*.mov;*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv;*.flv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.webm;*.m2ts;*.h264;*.mov;*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv;*.flv|All Files|*.*";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.Multiselect = true;
            //openFileDialog.Title = "Choose files to join:";
            openFileDialog.Title = "فایلها را انتخاب نمایید:";

            if (openFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            string[] files = openFileDialog.FileNames;
            Array.Sort(files);

            foreach (string FileName in files)
            {
                AppendList(FileName);
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "";
            foreach (ListViewItem item in listView1.Items)
            {
                item.Remove();
            }
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "";
            if (listView1.Items.Count == 0)
            {
                // labelStatus.Text = "Error: No files selected. Please choose the files to be joined.";
                labelStatus.Text = "خطا : فایلی برای اتصال انتخاب نشده است";
                return;
            }
            string filename = listView1.Items[0].Text;
            SaveFileDialog saveFileDialog = new System.Windows.Forms.SaveFileDialog();

            string sz = ExtOfFile(filename);
            saveFileDialog.FileName = "Joined";
            saveFileDialog.DefaultExt = sz;

            sz = "*" + sz;
            sz = sz + "|" + sz;
            saveFileDialog.Filter = sz;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.CheckPathExists = true;
            saveFileDialog.Title = "ذخیره سازی فایل ترکیبی ";
            

            if (saveFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
               
            }

            string output = saveFileDialog.FileName;
            object var;
            int cb;

            //setting task type
            var = Join.Helper.SMM_TaskType.SMM_Task_Type_Joining;
            SetValue(new Guid(Join.Helper.SMAT_TaskType), var);

            //setting output file
            var = output;
            SetValue(new Guid(Join.Helper.SMAT_OutputFile), var);
            //setting output type
            var = m_smm_type;
            SetValue(new Guid(Join.Helper.SMAT_OutputType), var);

            //fill in SMM_TRACK_INFO
            Join.Helper.SMM_TRACK_INFO track = new Join.Helper.SMM_TRACK_INFO();

            track.nOutType = m_smm_type;
            track.nTrimmAccurType = -1;
            track.ulFlags = Convert.ToUInt32(0);
            track.dwASMode = 0;
            track.llASValue = Convert.ToInt64(0);
            track.nTrackPos = Convert.ToUInt32(0);
            track.nVideoStream = -1;
            track.nAudioStream = -1;
            track.szMPEG2IdxFileName = Convert.ToString(0);
            track.nClips = listView1.Items.Count;

            //fill in pClips
            Join.Helper.SMM_CLIP_INFO[] clips = new Join.Helper.SMM_CLIP_INFO[track.nClips];

            cb = Marshal.SizeOf(typeof(Join.Helper.SMM_CLIP_INFO));
            track.pClips = Marshal.AllocHGlobal(cb * track.nClips);
            Int32 curPointer;
            curPointer = track.pClips.ToInt32();

            for (int i = 0; i < track.nClips; i++)
            {
                ListViewItem li;
                IntPtr curPtr = new IntPtr(curPointer + i * cb);
                li = listView1.Items[i];
                //AddClipToTrack(clips[i], li.Text);
                clips[i].dwClipNum = Convert.ToInt32(0);
                clips[i].rtStart = Convert.ToInt64(0);
                clips[i].rtEnd = Convert.ToInt64(0);
                clips[i].bMute = 0;
                clips[i].wsfName = li.Text + Convert.ToChar(0);

                Marshal.StructureToPtr(clips[i], curPtr, false);
            }
            //setting SMM_TRACK_INFO
            cb = Marshal.SizeOf(track);
            IntPtr ptr = Marshal.AllocHGlobal(cb);
            Marshal.StructureToPtr(track, ptr, false);
            var = ptr;

            SetValue(new Guid(Join.Helper.SMAT_TrackInfo), var);

            Marshal.DestroyStructure(track.pClips, typeof(Join.Helper.SMM_CLIP_INFO));
            Marshal.FreeHGlobal(track.pClips);
            Marshal.DestroyStructure(ptr, typeof(Join.Helper.SMM_TRACK_INFO));
            Marshal.FreeHGlobal(ptr);

            //commit
            var = 0;
            m_ModuleConfig.CommitChanges(out var);

            bool bRun = true;

            int hr;
            try
            {
                //validate files for joining
                Guid ValidateGuid = new Guid(Join.Helper.SMAT_ValidateFiles);
                m_ModuleConfig.GetValue(ref ValidateGuid, out var);

                hr = Convert.ToInt32(var);
                if (1 == hr)
                {
                    //if (MessageBox.Show("Some chosen tracks have different parameters!\n" +
                    //    "There may be some problems during output file playback.\n" +
                    //    "Would you like to continue?", "Joining Troubles", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                   if( XtraMessageBox.Show("بعضی از پارامتر های فایلهای انتخابی با هم متفاوت می باشند \n" +
                       "ممکن است با خطا مواجه شوید \n" +
                       "آیا همچنان می خواهید ادامه دهید؟", "خطای اتصال فایلها", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                    //if (MessageBox.Show( MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                        bRun = false;
                }
                else if (hr != 0)
                {
                    //MessageBox.Show("Incompatible files detected or error orurred.\n", "Error");
                    MessageBox.Show("فایلهای انتخابی باهم دیگر سازگار نیستند.\n", "خطا");
                    bRun = false;
                }
            }
            catch (System.Exception ex)
            {
                hr = Marshal.GetHRForException(ex);
               // MessageBox.Show("Validate files HRESULT = " + hr.ToString(), "Error");
                MessageBox.Show("نتیجه اعتبار سنجی فایلها = " + hr.ToString(), "خطا ");
            }

            if (bRun)
            {
                try
                {
                    //run
                    VideoEditorManager VideoEditorManager = new VideoEditor.VideoEditorManager();
                    m_bFinished = false;
                    System.Threading.Thread t = new System.Threading.Thread(new System.Threading.ThreadStart(VideoEditorManager.Crack));
                    t.Start();
                   
                    m_Trimmer.Start();
                    Timer1.Enabled = true;
                   
                }
                catch (System.Exception ex)
                {
                   // MessageBox.Show("On start join", "Error");
                    MessageBox.Show("در شروع اتصال فایلها", "خطا");
                    
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //m_bErrorOccured = true;
            //m_bFinished = true;

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if( !(m_bFinished | m_bErrorOccured))
            //    e.Cancel=true;
        }

        private void BtnCancel_Click(object sender, EventArgs e)
        {
           // m_Trimmer.Stop();
            
            this.Dispose(true);

        }
    }
}
