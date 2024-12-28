using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;

namespace CJoiner
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private AVITRIMMERCOMLib.TrimmerObjControl m_Trimmer;
		private AVITRIMMERCOMLib.IModuleConfig m_ModuleConfig;
		private Helper m_CB;

		public	bool m_bErrorOccured;
        public bool m_bFinished;
		public  int m_smm_type;

		private ArrayList m_Ranges;
		private System.Windows.Forms.Label labelStatus;
		private System.Windows.Forms.Button buttonInput;
		private System.Windows.Forms.ListView listView1;		//Array of parts to join
		private System.Windows.Forms.ColumnHeader file;
		private System.Windows.Forms.ColumnHeader type;
		private System.Windows.Forms.Button buttonJoin;
		private System.Windows.Forms.ProgressBar ProgressBar1;
		private System.Windows.Forms.Timer Timer1;
		private System.Windows.Forms.Button buttonClear;
		private System.Windows.Forms.Label label1;
		private System.ComponentModel.IContainer components;

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
				m_CB = new Helper( this );
			}
			catch (System.Exception e)
			{
				labelStatus.Text = "Error: Couldn't initialize basic components or interfaces.\r\n" + e.Message;
				EnableControls( false );
				return;
			}

			//Set Callback
			Guid input = new Guid(Helper.SMAT_Callback);
			object  val = m_CB;
			if( false == SetValue( input, val) )
				return;

			m_Ranges = new ArrayList();
			
			//Set MPEG-2 profile
			Guid profile = new Guid(Helper.SMAT_CodecsSet);
			val = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM";
			SetValue( profile, val);
			
			val = Helper.g_ActionKey_Join;
			Guid ActionKey = new Guid( Helper.SMAT_ActionKey );			
			SetValue( ActionKey, val );

			//Set Silent Path.
			//Used only for MPEG-2 files joining when MPEG-2 components aren't registered
			val = "CLSID\\{" + Helper.CLSID_VideoEditingSDK + "}\\Components";
			Guid SilentPath = new Guid( Helper.SMAT_SilentPath );
			SetValue( SilentPath, val );

			Timer1.Tick += new EventHandler(OnTimer);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.file = new System.Windows.Forms.ColumnHeader();
			this.type = new System.Windows.Forms.ColumnHeader();
			this.labelStatus = new System.Windows.Forms.Label();
			this.buttonInput = new System.Windows.Forms.Button();
			this.listView1 = new System.Windows.Forms.ListView();
			this.buttonJoin = new System.Windows.Forms.Button();
			this.ProgressBar1 = new System.Windows.Forms.ProgressBar();
			this.Timer1 = new System.Windows.Forms.Timer(this.components);
			this.buttonClear = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// file
			// 
			this.file.Text = "File";
			this.file.Width = 325;
			// 
			// type
			// 
			this.type.Text = "Type";
			this.type.Width = 86;
			// 
			// labelStatus
			// 
			this.labelStatus.Location = new System.Drawing.Point(8, 216);
			this.labelStatus.Name = "labelStatus";
			this.labelStatus.Size = new System.Drawing.Size(448, 40);
			this.labelStatus.TabIndex = 0;
			// 
			// buttonInput
			// 
			this.buttonInput.Location = new System.Drawing.Point(0, 184);
			this.buttonInput.Name = "buttonInput";
			this.buttonInput.Size = new System.Drawing.Size(72, 24);
			this.buttonInput.TabIndex = 1;
			this.buttonInput.Text = "Select Files";
			this.buttonInput.Click += new System.EventHandler(this.buttonInput_Click);
			// 
			// listView1
			// 
			this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																						this.file,
																						this.type});
			this.listView1.Location = new System.Drawing.Point(0, 0);
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(456, 176);
			this.listView1.TabIndex = 2;
			this.listView1.View = System.Windows.Forms.View.Details;
			// 
			// buttonJoin
			// 
			this.buttonJoin.Location = new System.Drawing.Point(152, 184);
			this.buttonJoin.Name = "buttonJoin";
			this.buttonJoin.Size = new System.Drawing.Size(48, 24);
			this.buttonJoin.TabIndex = 3;
			this.buttonJoin.Text = "Join";
			this.buttonJoin.Click += new System.EventHandler(this.buttonJoin_Click);
			// 
			// ProgressBar1
			// 
			this.ProgressBar1.Location = new System.Drawing.Point(216, 184);
			this.ProgressBar1.Name = "ProgressBar1";
			this.ProgressBar1.Size = new System.Drawing.Size(240, 24);
			this.ProgressBar1.TabIndex = 4;
			// 
			// buttonClear
			// 
			this.buttonClear.Location = new System.Drawing.Point(80, 184);
			this.buttonClear.Name = "buttonClear";
			this.buttonClear.Size = new System.Drawing.Size(64, 24);
			this.buttonClear.TabIndex = 5;
			this.buttonClear.Text = "Clear List";
			this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 264);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(448, 32);
			this.label1.TabIndex = 6;
			this.label1.Text = "Supported formats: ASF, AVI, AVCHD, MKV, MP4, MOV, MP3, MPEG1, MPEG2, WAV, WMA";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(458, 300);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.buttonClear);
			this.Controls.Add(this.ProgressBar1);
			this.Controls.Add(this.buttonJoin);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.buttonInput);
			this.Controls.Add(this.labelStatus);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.Text = "SMM Join C#";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private bool SetValue( Guid param, object val )
		{
			try
			{
				m_ModuleConfig.SetValue(ref param, ref val);
			}
			catch(Exception ex)
			{
				labelStatus.Text = "Error: " + ex.Message;
				return false;
			}
			return true;
		}

		private void buttonInput_Click(object sender, System.EventArgs e)
		{
			labelStatus.Text = "";
			OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

			openFileDialog.Filter = "Media Files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv|All Files|*.*";
			openFileDialog.FilterIndex = 1;
			openFileDialog.RestoreDirectory = true;
			openFileDialog.CheckFileExists = true;
			openFileDialog.CheckPathExists = true;
			openFileDialog.Multiselect = true;
			openFileDialog.Title = "Choose files to join:";

			if (openFileDialog.ShowDialog() != DialogResult.OK)
			{
				return;
			}
			
			string[] files = openFileDialog.FileNames;
			Array.Sort(files);

			foreach (string FileName in files)
			{
				AppendList( FileName );
			}
		}
		private void AppendList( string csFileName )
		{
			object var = csFileName;
			SetValue( new Guid(Helper.SMAT_InputFile), var );
			try
			{
				Helper.SMM_OutputTypes ftype;
				Guid fTypeGuid = new Guid(Helper.SMAT_GetFileType);
				m_ModuleConfig.GetValue( ref fTypeGuid, out var);
				ftype = ((Helper.SMM_OutputTypes) var);
				
				if( CheckSupportedFileTypes( ftype ) )
				{
					ListViewItem item = new ListViewItem(csFileName);
					string stType = Helper.XTLDescr_TrackOutType[(int)ftype];
					item.SubItems.Add(stType);
					listView1.Items.Add(item);
					m_smm_type = (int)ftype;
				}
			}
			catch (System.Exception e)
			{
				labelStatus.Text = "Invalid input: "+e.Message;
			}
		}
		private bool CheckSupportedFileTypes( Helper.SMM_OutputTypes type )
		{
			if( type <= Helper.SMM_OutputTypes.SMM_File_Type_NO ||
				type > Helper.SMM_OutputTypes.SMM_File_Type_MP4 )
				return false;
			else
				return true;
		}

		private void buttonJoin_Click(object sender, System.EventArgs e)
		{
			labelStatus.Text = "";
			if( listView1.Items.Count == 0 )
			{
				labelStatus.Text = "Error: No files selected. Please choose the files to be joined.";
				return;
			}
			string filename = listView1.Items[0].Text;
			SaveFileDialog saveFileDialog = new System.Windows.Forms.SaveFileDialog();

			string sz =  ExtOfFile( filename );
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
			var = Helper.SMM_TaskType.SMM_Task_Type_Joining;
			SetValue(new Guid(Helper.SMAT_TaskType), var);

			//setting output file
			var = output;
			SetValue(new Guid(Helper.SMAT_OutputFile), var);
			//setting output type
			var = m_smm_type;
			SetValue(new Guid(Helper.SMAT_OutputType), var);

			//fill in SMM_TRACK_INFO
			Helper.SMM_TRACK_INFO track = new Helper.SMM_TRACK_INFO();

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
			Helper.SMM_CLIP_INFO[] clips = new Helper.SMM_CLIP_INFO[track.nClips];
			
			cb = Marshal.SizeOf(typeof(Helper.SMM_CLIP_INFO));
			track.pClips = Marshal.AllocHGlobal(cb * track.nClips);
			Int32 curPointer;
			curPointer = track.pClips.ToInt32();
			
			for( int i = 0; i<track.nClips; i++ )
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

			SetValue(new Guid(Helper.SMAT_TrackInfo), var);

			Marshal.DestroyStructure(track.pClips, typeof(Helper.SMM_CLIP_INFO));
			Marshal.FreeHGlobal(track.pClips);
			Marshal.DestroyStructure(ptr, typeof(Helper.SMM_TRACK_INFO));
			Marshal.FreeHGlobal(ptr);
			
			//commit
			var = 0;
			m_ModuleConfig.CommitChanges(out var);

			bool bRun = true;

			int hr;
			try
			{
				//validate files for joining
				Guid ValidateGuid = new Guid(Helper.SMAT_ValidateFiles);
				m_ModuleConfig.GetValue(ref ValidateGuid, out var);

				hr = Convert.ToInt32(var);
				if( 1 == hr )
				{
					if( MessageBox.Show( "Some chosen tracks have different parameters!\n" + 
						"There may be some problems during output file playback.\n" +
						"Would you like to continue?", "Joining Troubles", MessageBoxButtons.YesNo, MessageBoxIcon.Warning ) == DialogResult.No )
						bRun = false;
				}
				else if( hr != 0 )
				{
					MessageBox.Show("Incompatible files detected or error orurred.\n", "Error");
					bRun = false;
				}
			}
			catch (System.Exception ex)
			{
				hr = Marshal.GetHRForException(ex);
				MessageBox.Show("Validate files HRESULT = "+ hr.ToString(), "Error");
			}

			if( bRun )
			{
				try
				{
					//run
                    m_bFinished = false;
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
            Guid ProgressGuid = new Guid(Helper.SMAT_Progress);
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
			labelStatus.Text = "";
			foreach (ListViewItem item in listView1.Items)
			{
				item.Remove();
			}
		}
		private void EnableControls( bool bBlock )
		{
			buttonInput.Enabled = bBlock;
			buttonClear.Enabled = bBlock;
			buttonJoin.Enabled = bBlock;
		}
	}
}
