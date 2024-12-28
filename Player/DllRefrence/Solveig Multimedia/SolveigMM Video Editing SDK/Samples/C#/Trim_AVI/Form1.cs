using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;

namespace csample
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.ComponentModel.IContainer components;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.TextBox txtFolder;
		private System.Windows.Forms.TextBox textFileOutput;
		private System.Windows.Forms.ProgressBar progressBar1;
		private System.Windows.Forms.Button btnStart;
		private System.Windows.Forms.Button btnInputFile;
		private System.Windows.Forms.Button btnOutputFile;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label labDuration;

		public	bool m_bCompleted;		//current process' state
		public	bool m_bNeedIndexing;
		public	bool m_bErrorOccured;
		private long m_Duration;		//Current stream duration
	
		private AVITRIMMERCOMLib.TrimmerObjControl m_Trimmer;
		private AVITRIMMERCOMLib.IModuleConfig m_ModuleConfig;
		private System.Windows.Forms.Label labelFType;
		private System.Windows.Forms.Label labelTime;
		private AxSMM_OCXSliderLib.AxSMM_OCXSlider slider;
		private System.Windows.Forms.CheckBox cbFATrim;
		private System.Windows.Forms.Label label1;
		private Helper m_CB;


		// DLL exports

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
#if RESTRICTED
			MessageBox.Show(this,
					"This is an evaluation version of SDK that doesn't contain all necessary headers\r\nand the sample couldn't be built correctly.\r\nParameter GUIDs are available in the full SDK version",
					"ERROR",
					MessageBoxButtons.OK,
					MessageBoxIcon.Information
					);
			
			btnInputFile.Enabled = false;
			return;
#endif
			this.slider.Enabled = false;
			//Create instance of Editing Engine
			m_Trimmer = new AVITRIMMERCOMLib.TrimmerObjControl();
			m_ModuleConfig = (AVITRIMMERCOMLib.IModuleConfig)m_Trimmer;
			m_CB = new Helper( this );
			
			///Initial Engine settings:
			
			//Set Callback
			Guid input = new Guid(Helper.SMAT_Callback);
			object  val = m_CB;
			if( false == SetValue( input, val) )
				return;

			
			//Set MPEG-2 profile
			Guid profile = new Guid(Helper.SMAT_CodecsSet);
			val = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM";
			SetValue( profile, val);
			
			//Set Silent Path. Used when MPEG-2 components aren't registered
			val = "CLSID\\{" + Helper.CLSID_VideoEditingSDK + "}\\Components";
			Guid SilentPath = new Guid( Helper.SMAT_SilentPath );			
			SetValue( SilentPath, val );

			val = Helper.g_ActionKey_Trim;
			Guid ActionKey = new Guid( Helper.SMAT_ActionKey );			
			SetValue( ActionKey, val );

			btnStart.Enabled = false;
			m_bErrorOccured = false;

			timer1.Tick += new EventHandler(OnTimer);

			m_Duration = 0;
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.btnInputFile = new System.Windows.Forms.Button();
			this.txtFolder = new System.Windows.Forms.TextBox();
			this.btnStart = new System.Windows.Forms.Button();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.btnCancel = new System.Windows.Forms.Button();
			this.progressBar1 = new System.Windows.Forms.ProgressBar();
			this.labelFType = new System.Windows.Forms.Label();
			this.btnOutputFile = new System.Windows.Forms.Button();
			this.textFileOutput = new System.Windows.Forms.TextBox();
			this.labDuration = new System.Windows.Forms.Label();
			this.labelTime = new System.Windows.Forms.Label();
			this.slider = new AxSMM_OCXSliderLib.AxSMM_OCXSlider();
			this.cbFATrim = new System.Windows.Forms.CheckBox();
			this.label1 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.slider)).BeginInit();
			this.SuspendLayout();
			// 
			// btnInputFile
			// 
			this.btnInputFile.Location = new System.Drawing.Point(8, 8);
			this.btnInputFile.Name = "btnInputFile";
			this.btnInputFile.Size = new System.Drawing.Size(104, 24);
			this.btnInputFile.TabIndex = 0;
			this.btnInputFile.Text = "Input File";
			this.btnInputFile.Click += new System.EventHandler(this.btnInputFile_Click);
			// 
			// txtFolder
			// 
			this.txtFolder.AutoSize = false;
			this.txtFolder.Enabled = false;
			this.txtFolder.Location = new System.Drawing.Point(120, 8);
			this.txtFolder.Name = "txtFolder";
			this.txtFolder.Size = new System.Drawing.Size(304, 24);
			this.txtFolder.TabIndex = 1;
			this.txtFolder.Text = "";
			// 
			// btnStart
			// 
			this.btnStart.Enabled = false;
			this.btnStart.Location = new System.Drawing.Point(8, 72);
			this.btnStart.Name = "btnStart";
			this.btnStart.Size = new System.Drawing.Size(48, 23);
			this.btnStart.TabIndex = 3;
			this.btnStart.Text = "Start";
			this.btnStart.Click += new System.EventHandler(this.btnAction_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(64, 72);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(48, 23);
			this.btnCancel.TabIndex = 5;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// progressBar1
			// 
			this.progressBar1.Location = new System.Drawing.Point(120, 72);
			this.progressBar1.Name = "progressBar1";
			this.progressBar1.Size = new System.Drawing.Size(416, 23);
			this.progressBar1.TabIndex = 7;
			// 
			// labelFType
			// 
			this.labelFType.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
			this.labelFType.Location = new System.Drawing.Point(432, 16);
			this.labelFType.Name = "labelFType";
			this.labelFType.Size = new System.Drawing.Size(112, 48);
			this.labelFType.TabIndex = 11;
			this.labelFType.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// btnOutputFile
			// 
			this.btnOutputFile.Enabled = false;
			this.btnOutputFile.Location = new System.Drawing.Point(8, 40);
			this.btnOutputFile.Name = "btnOutputFile";
			this.btnOutputFile.Size = new System.Drawing.Size(104, 24);
			this.btnOutputFile.TabIndex = 13;
			this.btnOutputFile.Text = "Output File";
			this.btnOutputFile.Click += new System.EventHandler(this.btnOutputFile_Click);
			// 
			// textFileOutput
			// 
			this.textFileOutput.AutoSize = false;
			this.textFileOutput.Enabled = false;
			this.textFileOutput.Location = new System.Drawing.Point(120, 40);
			this.textFileOutput.Name = "textFileOutput";
			this.textFileOutput.Size = new System.Drawing.Size(304, 24);
			this.textFileOutput.TabIndex = 14;
			this.textFileOutput.Text = "";
			// 
			// labDuration
			// 
			this.labDuration.Location = new System.Drawing.Point(216, 104);
			this.labDuration.Name = "labDuration";
			this.labDuration.Size = new System.Drawing.Size(120, 16);
			this.labDuration.TabIndex = 18;
			this.labDuration.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// labelTime
			// 
			this.labelTime.Location = new System.Drawing.Point(16, 104);
			this.labelTime.Name = "labelTime";
			this.labelTime.Size = new System.Drawing.Size(192, 16);
			this.labelTime.TabIndex = 19;
			// 
			// slider
			// 
			this.slider.Location = new System.Drawing.Point(8, 128);
			this.slider.Name = "slider";
			this.slider.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("slider.OcxState")));
			this.slider.Size = new System.Drawing.Size(536, 104);
			this.slider.TabIndex = 20;
			this.slider.SliderMoving += new System.EventHandler(this.slider_SliderMoving);
			this.slider.MarkerMoving += new AxSMM_OCXSliderLib._DSMM_OCXSliderEvents_MarkerMovingEventHandler(this.slider_MarkerMoving);
			// 
			// cbFATrim
			// 
			this.cbFATrim.Location = new System.Drawing.Point(360, 104);
			this.cbFATrim.Name = "cbFATrim";
			this.cbFATrim.Size = new System.Drawing.Size(160, 16);
			this.cbFATrim.TabIndex = 21;
			this.cbFATrim.Text = "Frame Accuracy Trimming";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 240);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(536, 16);
			this.label1.TabIndex = 22;
			this.label1.Text = "Supported formats: ASF, AVI, AVCHD, MKV, MP4, MOV, MP3, MPEG1, MPEG2, WAV, WMA";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(546, 260);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.cbFATrim);
			this.Controls.Add(this.slider);
			this.Controls.Add(this.labelTime);
			this.Controls.Add(this.labDuration);
			this.Controls.Add(this.textFileOutput);
			this.Controls.Add(this.txtFolder);
			this.Controls.Add(this.btnOutputFile);
			this.Controls.Add(this.labelFType);
			this.Controls.Add(this.progressBar1);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnStart);
			this.Controls.Add(this.btnInputFile);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.Text = "SMM Trim C#";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.Form1_Closing);
			((System.ComponentModel.ISupportInitialize)(this.slider)).EndInit();
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

		// Start click
		private void btnAction_Click(object sender, System.EventArgs e)
		{
			if( txtFolder.Text == "" )
			{
				MessageBox.Show(this,
					"You must first choose the input file!",
					"Warning",
					MessageBoxButtons.OK,
					MessageBoxIcon.Information
					);
				return;
			}

			if( textFileOutput.Text == "" )
			{
				btnOutputFile_Click(this, null);
				if( textFileOutput.Text == "" )
					return;
			}
			InitEngine();
			m_Trimmer.Start();
			timer1.Enabled = true;
			m_bCompleted = false;

			btnInputFile.Enabled = false;
			btnOutputFile.Enabled = false;
			btnStart.Enabled = false;
			slider.Enabled = false;
		}

		// timer function
		private void OnTimer(Object myObject, EventArgs myEventArgs)
		{
			Guid progress = new Guid(Helper.SMAT_Progress);
			object  val;

			if( m_bCompleted == true )
			{
				timer1.Enabled = false;
				m_bCompleted = false;

				m_bErrorOccured = false;

				progressBar1.Value = 0;

				btnInputFile.Enabled = true;
				btnOutputFile.Enabled = true;
				btnStart.Enabled = true;
				slider.Enabled = true;
				return;
			}

			//Get progress value in %
			m_ModuleConfig.GetValue(ref progress, out val);

			progressBar1.Value = (int)val;

		}

		// Close window
		private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
		}

		private void btnInputFile_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

			openFileDialog.Filter = "Supported files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv|All files (*.*)|*.*";
			openFileDialog.FilterIndex = 1;
			openFileDialog.RestoreDirectory = true;
			openFileDialog.CheckFileExists = false;

			labelFType.Text = "";
			labDuration.Text = "";
			if (openFileDialog.ShowDialog() != DialogResult.OK)
			{	
				txtFolder.Text = "";
				return;
			}
			string resultFile = openFileDialog.FileName;

			txtFolder.Text = resultFile;

			//Set input File Name
			Guid input = new Guid(Helper.SMAT_InputFile);
			object  val;
			val = resultFile;
			SetValue( input, val );

			//Find out the file type
			Guid FType = new Guid( Helper.SMAT_GetFileType );
			val = null;
			m_ModuleConfig.GetValue(ref FType, out val);
			Helper.SMM_OutputTypes Type = (Helper.SMM_OutputTypes) val;
			
			string txt = "File type is\r\n";

			if( Type == Helper.SMM_OutputTypes.SMM_File_Type_AVI )
			{
				txt += "AVI";
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_ASF )
			{
				txt += "ASF";
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPA )
			{
				txt += "mp3";
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_PS )
			{
				txt += "mpeg2 PS";
				m_bNeedIndexing = true;
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_TS )
			{
				txt += "mpeg2 TS";
				m_bNeedIndexing = true;
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG2_VES )
			{
				txt += "mpeg2 VES";
				m_bNeedIndexing = true;
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG1_SYS )
			{
				txt += "mpeg1 SYS";
				m_bNeedIndexing = true;
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG1_VES )
			{
				txt += "mpeg1 VES";
				m_bNeedIndexing = true;
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_WAV )
			{
				txt += "wav";
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MPEG4_AVC )
			{
				txt += "AVC VES";
				m_bNeedIndexing = true;
			}
			else if(Type ==Helper.SMM_OutputTypes.SMM_File_Type_MKV )
			{
				txt += "MKV";
			}
			else if( Type == Helper.SMM_OutputTypes.SMM_File_Type_MP4 )
			{
				txt += "MP4";
			}
			else
			{
				txt += "unsupported";
				labelFType.Text = txt;
				return;
			}
			labelFType.Text = txt;
			
			if( Type == Helper.SMM_OutputTypes.SMM_File_Type_AVI ||
				Type == Helper.SMM_OutputTypes.SMM_File_Type_WAV ||
				Type == Helper.SMM_OutputTypes.SMM_File_Type_MPA )
			{
				//Frame accurate trimming for AVI and audio only files is not supported
				cbFATrim.Enabled = false;
				cbFATrim.Checked = false;
			}
			else
			{
				//For other formats we can choose between GOP and Frame accuracy
				//But Frame is by default
				cbFATrim.Enabled = true;
				cbFATrim.Checked = true;
			}

			Guid length = new Guid(Helper.SMAT_StreamLength);
			m_ModuleConfig.GetValue(ref length, out val);
			
			m_Duration = (long)(((double)val)*10000000.0);
			
			this.slider.SetRange((long)m_Duration);

			labDuration.Text = "Total: " + ConvertTimeToStr( m_Duration );

			
			textFileOutput.Text = "";

			UpdateStartEndTimes();
			
			if( m_bNeedIndexing == true )
				StartIndexing();
			else
			{
				btnOutputFile.Enabled = true;
				btnStart.Enabled = true;
				slider.Enabled = true;
			}
		}

   		private void btnOutputFile_Click(object sender, System.EventArgs e)
		{
			textFileOutput.Text = GetOutputName();
			if( textFileOutput.Text == "" )
				return;
			Guid output = new Guid(Helper.SMAT_OutputFile);
			object  val;

			//Set input File Name
			val = textFileOutput.Text;
			SetValue( output, val);
		}

   		private string ConvertTimeToStr( long time )
		{
			int nTotalMsec = (int)(time / 10000);
			int nHour;
			int nMin;
			int nSec;
			int nMsec;
			nHour = Math.DivRem(nTotalMsec, 3600000, out nMin);
			nMin = Math.DivRem(nMin, 60000, out nSec);
			nSec = Math.DivRem(nSec, 1000, out nMsec);
			String str;
			str = nHour.ToString() + ":" + IntToStr2(nMin) + ":" + IntToStr2(nSec) + "." + IntToStr3(nMsec);
			return str;
		}

		private string IntToStr2(int val)
		{
			if( val < 10 )
				return "0" + val.ToString();
			else
				return val.ToString();
		}

		private string IntToStr3(int val)
		{
			if( val < 100 )
				return "0" + val.ToString();
			else
				return val.ToString();
								
		}

		public String ExtOfFile(String sz)
		{
			int lastdotpos = sz.LastIndexOf(".");
			return sz.Substring(lastdotpos, sz.Length - lastdotpos);
		}

		public void InitEngine(  )
		{	
			Guid TaskType = new Guid(Helper.SMAT_TaskType);
			object objType = Helper.SMM_TaskType.SMM_Task_Type_Trimming;
			//Set task type (trimming)
			SetValue( TaskType, objType );

			int IntervalsCount = this.slider.GetIntervalsCount();
			Helper.TrimInfoList TrimList; 
			TrimList.nListSize = IntervalsCount; //Count of pieces
			Helper.__TSTrimInfo[] tmp = new Helper.__TSTrimInfo[IntervalsCount];
			for (int i = 0; i < IntervalsCount; i++)
			{
				// get interval props
				Helper.CInterval_info intervalInfo = GetIntervalInfo(i);

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
			SetValue( List, var );
			Marshal.DestroyStructure(ptr, TrimList.GetType());	// clear the memory block
			Marshal.FreeHGlobal(ptr);				// free the memory block

			//Set trimming accuracy
			Guid AccuracyType = new Guid(Helper.SMAT_TrimAccuracy);
			object objAccuracy =  Convert.ToInt32(cbFATrim.Checked);
			SetValue( AccuracyType, objAccuracy );

			m_ModuleConfig.CommitChanges( out var ); //commit all parameters set
		}

		private void StartIndexing()
		{

			Guid outIndex = new Guid(Helper.SMAT_OutIndexFile);
			object var = txtFolder.Text + ".mlmix";
			SetValue( outIndex, var );
	
			Guid StartIndex = new Guid(Helper.SMAT_StartIndexation);
			var = true;
			if( false == SetValue( StartIndex, var ) )
				return;
			
			btnInputFile.Enabled = false;
			btnOutputFile.Enabled = false;
			btnStart.Enabled = false;
			slider.Enabled = false;

			m_bNeedIndexing = true;
			m_bCompleted = false;
			timer1.Enabled = true;
		}

		private void btnCancel_Click(object sender, System.EventArgs e)
		{
			if( m_bNeedIndexing )
			{
				Guid StartIndex = new Guid(Helper.SMAT_StartIndexation);
				object var = false;
				SetValue( StartIndex, var );
				m_bNeedIndexing = false;
			}
			else
				m_Trimmer.Stop();

			m_bNeedIndexing = false;
			m_bCompleted = true;
			m_bErrorOccured = true;
		}

		public string GetOutputName()
		{
			string sz = ExtOfFile(txtFolder.Text);
			
			SaveFileDialog SaveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
			SaveFileDialog1.DefaultExt = sz;
			sz = "*" + sz;
			sz = sz + "|" + sz;
			SaveFileDialog1.Filter = sz;
			SaveFileDialog1.FileName = "Default";
			if( SaveFileDialog1.ShowDialog() == DialogResult.OK )
			{
				return SaveFileDialog1.FileName;
			}
			else
				return "";
		}
		
		private bool SetValue( Guid param, object val )
		{
			try
			{
				m_ModuleConfig.SetValue(ref param, ref val);
			}
			catch(Exception ex)
			{
				return false;
			}
			return true;
		}

		private Helper.CInterval_info  GetIntervalInfo(int num)
		{
			Helper.CInterval_info intervalInfo = new Helper.CInterval_info();

            IntPtr ptr = Marshal.AllocCoTaskMem(Marshal.SizeOf(intervalInfo));
            this.slider.GetIntervalInfo1( num, (int)ptr );
            intervalInfo = (Helper.CInterval_info)Marshal.PtrToStructure(ptr, typeof(Helper.CInterval_info));
			Marshal.FreeCoTaskMem(ptr);
			return intervalInfo;
		}
		private void  UpdateStartEndTimes()
		{
			int curNum = this.slider.GetCurrentInterval();
			Helper.CInterval_info intervalInfo = GetIntervalInfo(curNum);
			string text = "Start: "+ ConvertTimeToStr(intervalInfo.llstart) + " / End: "+ ConvertTimeToStr(intervalInfo.llend);
			if (text != labelTime.Text)
			labelTime.Text = text;
		}

		private void slider_SliderMoving(object sender, System.EventArgs e)
		{
			UpdateStartEndTimes();
		}

		private void slider_MarkerMoving(object sender, AxSMM_OCXSliderLib._DSMM_OCXSliderEvents_MarkerMovingEvent e)
		{
			UpdateStartEndTimes();
		}
	}
}