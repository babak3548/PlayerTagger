using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace csample
{
   /// <summary>
   /// Summary description for Form1.
   /// </summary>
   public class Form1 : System.Windows.Forms.Form
   {
      private System.Windows.Forms.Button btnOpenFolder;
      private System.Windows.Forms.TextBox txtFolder;
      private System.ComponentModel.IContainer components;
      private System.Windows.Forms.GroupBox groupBox1;
      private System.Windows.Forms.Label label1;
      private System.Windows.Forms.Label label2;
      private System.Windows.Forms.TextBox txtWidth;
      private System.Windows.Forms.TextBox txtHeight;
      private System.Windows.Forms.Label label3;
      private System.Windows.Forms.TextBox txtDuration;
      private System.Windows.Forms.ListView listView1;
      private System.Windows.Forms.Timer timer1;
      private System.Windows.Forms.Button btnStart;
      private System.Windows.Forms.Button btnStop;
      private System.Windows.Forms.Button btnConfigure;
      private System.Windows.Forms.ProgressBar progressBar1;
      private System.Windows.Forms.Button btnOutput;
      private System.Windows.Forms.GroupBox groupBox2;
      private System.Windows.Forms.Label label4;
      private System.Windows.Forms.Label label5;
      private System.Windows.Forms.Label label6;
      private System.Windows.Forms.Label label7;
      private System.Windows.Forms.Label label8;
      private System.Windows.Forms.TextBox txtEwidth;
      private System.Windows.Forms.TextBox txtEheight;
      private System.Windows.Forms.TextBox txtEduration;
      private System.Windows.Forms.TextBox txtEtotal;
      private System.Windows.Forms.TextBox txtEcompression;
      private System.Windows.Forms.Button btnExport;
      private System.Windows.Forms.TextBox txtExport;
      private System.Windows.Forms.Button btnClear;
      private System.Windows.Forms.Label labelCompleted;
      private System.Windows.Forms.TextBox txtEncoding;  

      private bool bOpened;         // stream opened
      private bool bClosePending;   // close stream pending
      private bool bFileExists;     // output file empty/exists
      private string [] list;       // input bitmap files list
      private string encoding;      // encoder name
      private int total, completed; // completion status
      private IntPtr stream;        // stream instance

      // DLL exports

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal IntPtr CreateNewStream();

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal void ReleaseStream([In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CharSet=CharSet.Unicode, CallingConvention=CallingConvention.Cdecl)]
      static extern internal int OpenAVIStream([In] string bstFileName, [Out] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CharSet=CharSet.Unicode, CallingConvention=CallingConvention.Cdecl)]
	  [return: MarshalAs(UnmanagedType.BStr)]
      static extern internal string ChooseEncoder([In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal int SetStreamProperties([In] int lHeight, [In] int lWidth, [In] long llFrameDuration, [In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal int WriteImage([In] IntPtr hInputBitmap, [In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal int CloseAVIStream([In] bool bTerminate, [In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal IntPtr ReadImageFromStream([In] long llFrame, [Out] IntPtr plTotalBytes, [In] IntPtr pInstance);

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal void FreeImage([In] IntPtr pBuffer, [In] IntPtr pInstance);

      [StructLayout(LayoutKind.Explicit, Size = 28)] 
      public struct StreamProperties 
      {
         [FieldOffset(0)]public int lWidth;
         [FieldOffset(4)]public int lHeight;
         [FieldOffset(8)]public long lLduration;
         [FieldOffset(16)]public long lLTotal;
         [FieldOffset(24)]public int dwCompression;
      }

      [DllImport("BmpToAvi.dll", CallingConvention=CallingConvention.Cdecl)]
      static extern internal int GetAVIFileInfo([In, Out] IntPtr Params, [In] IntPtr pInstance);

      [DllImport("gdi32.dll")]
      static extern bool DeleteObject(IntPtr hObject);

      public Form1()
      {
         //
         // Required for Windows Form Designer support
         //
         InitializeComponent();

         //
         // TODO: Add any constructor code after InitializeComponent call
         //
         txtWidth.Text = "320";
         txtHeight.Text = "240";
         txtDuration.Text = "400000"; // 25 fps

         encoding = "";

         listView1.Sorting = SortOrder.None;
         listView1.View = View.Details;
         listView1.Columns.Add(new ColumnHeader());

         listView1.Columns[0].Text = "bitmaps";
         listView1.Columns[0].Width = listView1.Width;

         listView1.MultiSelect = true;

         btnStart.Enabled = false;
         btnStop.Enabled = false;
         btnConfigure.Enabled = true;

         bOpened = false;
         bClosePending = false;
         bFileExists = false;

         total = completed = 0;

         timer1.Tick += new EventHandler(OnTimer);
		 stream = CreateNewStream();

         UpdateEncoding();
      }

      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      protected override void Dispose( bool disposing )
      {
         ReleaseStream(stream);
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
         this.btnOpenFolder = new System.Windows.Forms.Button();
         this.txtFolder = new System.Windows.Forms.TextBox();
         this.groupBox1 = new System.Windows.Forms.GroupBox();
         this.txtDuration = new System.Windows.Forms.TextBox();
         this.label3 = new System.Windows.Forms.Label();
         this.txtHeight = new System.Windows.Forms.TextBox();
         this.txtWidth = new System.Windows.Forms.TextBox();
         this.label2 = new System.Windows.Forms.Label();
         this.label1 = new System.Windows.Forms.Label();
         this.btnStart = new System.Windows.Forms.Button();
         this.listView1 = new System.Windows.Forms.ListView();
         this.timer1 = new System.Windows.Forms.Timer(this.components);
         this.btnStop = new System.Windows.Forms.Button();
         this.btnConfigure = new System.Windows.Forms.Button();
         this.progressBar1 = new System.Windows.Forms.ProgressBar();
         this.btnOutput = new System.Windows.Forms.Button();
         this.groupBox2 = new System.Windows.Forms.GroupBox();
         this.txtExport = new System.Windows.Forms.TextBox();
         this.btnExport = new System.Windows.Forms.Button();
         this.txtEcompression = new System.Windows.Forms.TextBox();
         this.txtEtotal = new System.Windows.Forms.TextBox();
         this.txtEduration = new System.Windows.Forms.TextBox();
         this.txtEheight = new System.Windows.Forms.TextBox();
         this.txtEwidth = new System.Windows.Forms.TextBox();
         this.label8 = new System.Windows.Forms.Label();
         this.label7 = new System.Windows.Forms.Label();
         this.label4 = new System.Windows.Forms.Label();
         this.label5 = new System.Windows.Forms.Label();
         this.label6 = new System.Windows.Forms.Label();
         this.btnClear = new System.Windows.Forms.Button();
         this.labelCompleted = new System.Windows.Forms.Label();
         this.txtEncoding = new System.Windows.Forms.TextBox();
         this.groupBox1.SuspendLayout();
         this.groupBox2.SuspendLayout();
         this.SuspendLayout();
         // 
         // btnOpenFolder
         // 
         this.btnOpenFolder.Location = new System.Drawing.Point(8, 8);
         this.btnOpenFolder.Name = "btnOpenFolder";
         this.btnOpenFolder.Size = new System.Drawing.Size(120, 32);
         this.btnOpenFolder.TabIndex = 0;
         this.btnOpenFolder.Text = "Select BMPs...";
         this.btnOpenFolder.Click += new System.EventHandler(this.btnOpenFolder_Click);
         // 
         // txtFolder
         // 
         this.txtFolder.AutoSize = false;
         this.txtFolder.Location = new System.Drawing.Point(240, 320);
         this.txtFolder.Name = "txtFolder";
         this.txtFolder.Size = new System.Drawing.Size(304, 24);
         this.txtFolder.TabIndex = 1;
         this.txtFolder.Text = "";
         // 
         // groupBox1
         // 
         this.groupBox1.Controls.Add(this.txtDuration);
         this.groupBox1.Controls.Add(this.label3);
         this.groupBox1.Controls.Add(this.txtHeight);
         this.groupBox1.Controls.Add(this.txtWidth);
         this.groupBox1.Controls.Add(this.label2);
         this.groupBox1.Controls.Add(this.label1);
         this.groupBox1.Location = new System.Drawing.Point(240, 120);
         this.groupBox1.Name = "groupBox1";
         this.groupBox1.Size = new System.Drawing.Size(144, 112);
         this.groupBox1.TabIndex = 2;
         this.groupBox1.TabStop = false;
         this.groupBox1.Text = "Single picture properties";
         // 
         // txtDuration
         // 
         this.txtDuration.AutoSize = false;
         this.txtDuration.Location = new System.Drawing.Point(64, 80);
         this.txtDuration.Name = "txtDuration";
         this.txtDuration.Size = new System.Drawing.Size(72, 23);
         this.txtDuration.TabIndex = 5;
         this.txtDuration.Text = "";
         // 
         // label3
         // 
         this.label3.Location = new System.Drawing.Point(8, 88);
         this.label3.Name = "label3";
         this.label3.Size = new System.Drawing.Size(48, 16);
         this.label3.TabIndex = 4;
         this.label3.Text = "Duration";
         // 
         // txtHeight
         // 
         this.txtHeight.AutoSize = false;
         this.txtHeight.Location = new System.Drawing.Point(96, 48);
         this.txtHeight.Name = "txtHeight";
         this.txtHeight.Size = new System.Drawing.Size(40, 23);
         this.txtHeight.TabIndex = 3;
         this.txtHeight.Text = "";
         // 
         // txtWidth
         // 
         this.txtWidth.AutoSize = false;
         this.txtWidth.Location = new System.Drawing.Point(96, 16);
         this.txtWidth.Name = "txtWidth";
         this.txtWidth.Size = new System.Drawing.Size(40, 23);
         this.txtWidth.TabIndex = 2;
         this.txtWidth.Text = "";
         // 
         // label2
         // 
         this.label2.Location = new System.Drawing.Point(8, 56);
         this.label2.Name = "label2";
         this.label2.Size = new System.Drawing.Size(40, 16);
         this.label2.TabIndex = 1;
         this.label2.Text = "Height";
         // 
         // label1
         // 
         this.label1.Location = new System.Drawing.Point(8, 24);
         this.label1.Name = "label1";
         this.label1.Size = new System.Drawing.Size(40, 16);
         this.label1.TabIndex = 0;
         this.label1.Text = "Width";
         // 
         // btnStart
         // 
         this.btnStart.Location = new System.Drawing.Point(472, 360);
         this.btnStart.Name = "btnStart";
         this.btnStart.TabIndex = 3;
         this.btnStart.Text = "Start";
         this.btnStart.Click += new System.EventHandler(this.btnAction_Click);
         // 
         // listView1
         // 
         this.listView1.Location = new System.Drawing.Point(8, 56);
         this.listView1.MultiSelect = false;
         this.listView1.Name = "listView1";
         this.listView1.Size = new System.Drawing.Size(224, 288);
         this.listView1.TabIndex = 4;
         this.listView1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.listView1_KeyDown);
         // 
         // btnStop
         // 
         this.btnStop.Location = new System.Drawing.Point(376, 360);
         this.btnStop.Name = "btnStop";
         this.btnStop.TabIndex = 5;
         this.btnStop.Text = "Stop";
         this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
         // 
         // btnConfigure
         // 
         this.btnConfigure.Location = new System.Drawing.Point(240, 56);
         this.btnConfigure.Name = "btnConfigure";
         this.btnConfigure.Size = new System.Drawing.Size(144, 32);
         this.btnConfigure.TabIndex = 6;
         this.btnConfigure.Text = "Configure Encoder";
         this.btnConfigure.Click += new System.EventHandler(this.btnConfigure_Click);
         // 
         // progressBar1
         // 
         this.progressBar1.Location = new System.Drawing.Point(144, 16);
         this.progressBar1.Name = "progressBar1";
         this.progressBar1.Size = new System.Drawing.Size(328, 23);
         this.progressBar1.TabIndex = 7;
         // 
         // btnOutput
         // 
         this.btnOutput.Location = new System.Drawing.Point(320, 280);
         this.btnOutput.Name = "btnOutput";
         this.btnOutput.Size = new System.Drawing.Size(152, 32);
         this.btnOutput.TabIndex = 8;
         this.btnOutput.Text = "Select stream...";
         this.btnOutput.Click += new System.EventHandler(this.btnOutput_Click);
         // 
         // groupBox2
         // 
         this.groupBox2.Controls.Add(this.txtExport);
         this.groupBox2.Controls.Add(this.btnExport);
         this.groupBox2.Controls.Add(this.txtEcompression);
         this.groupBox2.Controls.Add(this.txtEtotal);
         this.groupBox2.Controls.Add(this.txtEduration);
         this.groupBox2.Controls.Add(this.txtEheight);
         this.groupBox2.Controls.Add(this.txtEwidth);
         this.groupBox2.Controls.Add(this.label8);
         this.groupBox2.Controls.Add(this.label7);
         this.groupBox2.Controls.Add(this.label4);
         this.groupBox2.Controls.Add(this.label5);
         this.groupBox2.Controls.Add(this.label6);
         this.groupBox2.Enabled = false;
         this.groupBox2.Location = new System.Drawing.Point(392, 51);
         this.groupBox2.Name = "groupBox2";
         this.groupBox2.Size = new System.Drawing.Size(152, 221);
         this.groupBox2.TabIndex = 9;
         this.groupBox2.TabStop = false;
         this.groupBox2.Text = "Existing stream info";
         // 
         // txtExport
         // 
         this.txtExport.Location = new System.Drawing.Point(8, 184);
         this.txtExport.Name = "txtExport";
         this.txtExport.Size = new System.Drawing.Size(72, 20);
         this.txtExport.TabIndex = 15;
         this.txtExport.Text = "";
         // 
         // btnExport
         // 
         this.btnExport.Location = new System.Drawing.Point(88, 176);
         this.btnExport.Name = "btnExport";
         this.btnExport.Size = new System.Drawing.Size(56, 32);
         this.btnExport.TabIndex = 14;
         this.btnExport.Text = "Export";
         this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
         // 
         // txtEcompression
         // 
         this.txtEcompression.Location = new System.Drawing.Point(80, 144);
         this.txtEcompression.Name = "txtEcompression";
         this.txtEcompression.ReadOnly = true;
         this.txtEcompression.Size = new System.Drawing.Size(64, 20);
         this.txtEcompression.TabIndex = 13;
         this.txtEcompression.Text = "";
         // 
         // txtEtotal
         // 
         this.txtEtotal.Location = new System.Drawing.Point(80, 112);
         this.txtEtotal.Name = "txtEtotal";
         this.txtEtotal.ReadOnly = true;
         this.txtEtotal.Size = new System.Drawing.Size(64, 20);
         this.txtEtotal.TabIndex = 12;
         this.txtEtotal.Text = "";
         // 
         // txtEduration
         // 
         this.txtEduration.Location = new System.Drawing.Point(80, 80);
         this.txtEduration.Name = "txtEduration";
         this.txtEduration.ReadOnly = true;
         this.txtEduration.Size = new System.Drawing.Size(64, 20);
         this.txtEduration.TabIndex = 11;
         this.txtEduration.Text = "";
         // 
         // txtEheight
         // 
         this.txtEheight.Location = new System.Drawing.Point(80, 48);
         this.txtEheight.Name = "txtEheight";
         this.txtEheight.ReadOnly = true;
         this.txtEheight.Size = new System.Drawing.Size(64, 20);
         this.txtEheight.TabIndex = 10;
         this.txtEheight.Text = "";
         // 
         // txtEwidth
         // 
         this.txtEwidth.Location = new System.Drawing.Point(80, 16);
         this.txtEwidth.Name = "txtEwidth";
         this.txtEwidth.ReadOnly = true;
         this.txtEwidth.Size = new System.Drawing.Size(64, 20);
         this.txtEwidth.TabIndex = 9;
         this.txtEwidth.Text = "";
         // 
         // label8
         // 
         this.label8.Location = new System.Drawing.Point(8, 144);
         this.label8.Name = "label8";
         this.label8.Size = new System.Drawing.Size(72, 16);
         this.label8.TabIndex = 8;
         this.label8.Text = "Compression";
         // 
         // label7
         // 
         this.label7.Location = new System.Drawing.Point(8, 112);
         this.label7.Name = "label7";
         this.label7.Size = new System.Drawing.Size(48, 16);
         this.label7.TabIndex = 7;
         this.label7.Text = "Frames";
         // 
         // label4
         // 
         this.label4.Location = new System.Drawing.Point(8, 16);
         this.label4.Name = "label4";
         this.label4.Size = new System.Drawing.Size(40, 16);
         this.label4.TabIndex = 6;
         this.label4.Text = "Width";
         // 
         // label5
         // 
         this.label5.Location = new System.Drawing.Point(8, 48);
         this.label5.Name = "label5";
         this.label5.Size = new System.Drawing.Size(40, 16);
         this.label5.TabIndex = 6;
         this.label5.Text = "Height";
         // 
         // label6
         // 
         this.label6.Location = new System.Drawing.Point(8, 80);
         this.label6.Name = "label6";
         this.label6.Size = new System.Drawing.Size(48, 16);
         this.label6.TabIndex = 6;
         this.label6.Text = "Duration";
         // 
         // btnClear
         // 
         this.btnClear.Location = new System.Drawing.Point(8, 360);
         this.btnClear.Name = "btnClear";
         this.btnClear.TabIndex = 10;
         this.btnClear.Text = "Clear list";
         this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
         // 
         // labelCompleted
         // 
         this.labelCompleted.Location = new System.Drawing.Point(480, 20);
         this.labelCompleted.Name = "labelCompleted";
         this.labelCompleted.Size = new System.Drawing.Size(56, 23);
         this.labelCompleted.TabIndex = 11;
         // 
         // txtEncoding
         // 
         this.txtEncoding.Location = new System.Drawing.Point(240, 96);
         this.txtEncoding.Name = "txtEncoding";
         this.txtEncoding.ReadOnly = true;
         this.txtEncoding.Size = new System.Drawing.Size(144, 20);
         this.txtEncoding.TabIndex = 12;
         this.txtEncoding.Text = "";
         this.txtEncoding.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
         // 
         // Form1
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
         this.ClientSize = new System.Drawing.Size(552, 390);
         this.Controls.Add(this.txtEncoding);
         this.Controls.Add(this.labelCompleted);
         this.Controls.Add(this.btnClear);
         this.Controls.Add(this.groupBox2);
         this.Controls.Add(this.btnOutput);
         this.Controls.Add(this.progressBar1);
         this.Controls.Add(this.btnConfigure);
         this.Controls.Add(this.btnStop);
         this.Controls.Add(this.listView1);
         this.Controls.Add(this.btnStart);
         this.Controls.Add(this.groupBox1);
         this.Controls.Add(this.txtFolder);
         this.Controls.Add(this.btnOpenFolder);
         this.Name = "Form1";
         this.Text = "SolveigMM BMPs to AVI Utility";
         this.Closing += new System.ComponentModel.CancelEventHandler(this.Form1_Closing);
         this.groupBox1.ResumeLayout(false);
         this.groupBox2.ResumeLayout(false);
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

      // add input bitmaps to list
      private void btnOpenFolder_Click(object sender, System.EventArgs e)
      {
         OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

         openFileDialog.InitialDirectory = "c:\\";
         openFileDialog.Filter = "BMP files (*.bmp)|*.bmp|All files (*.*)|*.*";
         openFileDialog.FilterIndex = 1;
         openFileDialog.RestoreDirectory = true;
         openFileDialog.CheckFileExists = true;
         openFileDialog.CheckPathExists = true;
         openFileDialog.Multiselect = true;
         openFileDialog.Title = "Add bitmaps to list or select existing AVI stream";

         if (openFileDialog.ShowDialog() != DialogResult.OK)
         {
            return;
         }


         string[] files = openFileDialog.FileNames;
         Array.Sort(files);

         string [] tmp;

         if (total > 0)
         {
            tmp = new string[list.Length + files.Length];
            list.CopyTo(tmp, 0);
            files.CopyTo(tmp, list.Length);
         }
         else
         {
            tmp = new string[files.Length];
            files.CopyTo(tmp, 0);
         }
         
         list = tmp;

         foreach (string bmpFile in files)
         {
            ListViewItem lvi = new ListViewItem(bmpFile);
            listView1.Items.Add(lvi);
            total++;
         }

         // update image param using the very first bitmap
         Bitmap bmp = new Bitmap(list[0]);

         txtWidth.Text = bmp.Width.ToString();
         txtHeight.Text = bmp.Height.ToString();

         UpdateTxtStatus();
      }

      // write bitmaps thread
      public void ThreadProc() 
      {
         int resW = 0, res = 0;

         btnStart.Enabled = false;
         btnStop.Enabled = true;

         bClosePending = false;

         progressBar1.Minimum = 0;
         progressBar1.Maximum = list.Length;
         progressBar1.Value = 0;

         foreach (string bmpFile in list)
         {
            if (!bClosePending)
            {
               Bitmap bmp = new Bitmap(bmpFile);
               IntPtr hBitmap = bmp.GetHbitmap();
               resW = WriteImage(hBitmap, stream);
               if (resW != 0)
               {
                  bClosePending = true;
                  break;
               }
               DeleteObject(hBitmap);
               bmp.Dispose();
            }
         }

         if (bClosePending)
         {
            bClosePending = false;
            res = CloseAVIStream (false, stream);
            if (res != 0)
               runtime_error(res, "CloseAVIStream");

            bOpened = false;
            btnConfigure.Enabled = false;
         }

         if (resW != 0)
            runtime_error(res, "WriteBitmap");
      }

      // Start click
      private void btnAction_Click(object sender, System.EventArgs e)
      {
         if (list.Length < 1)
         {
            MessageBox.Show(this,
               "You must specify folder including bitmaps.",
               "Error",
               MessageBoxButtons.OK,
               MessageBoxIcon.Error
               );
            return;
         }

         if (txtFolder.Text.Length == 0)
         {
            MessageBox.Show(this,
               "You must specify destination file.",
               "Error",
               MessageBoxButtons.OK,
               MessageBoxIcon.Error
               );
            return;
         }

         // start write bitmap thread routine
         Thread t = new Thread(new ThreadStart(ThreadProc));
         t.Priority = ThreadPriority.BelowNormal;
         t.IsBackground = true;
         t.Start();

         timer1.Interval = 100;
         timer1.Enabled = true;
      }

      // Stop click
      private void btnStop_Click(object sender, System.EventArgs e)
      {
         bClosePending = true;
      }

      // Configure Encoder click
      private void btnConfigure_Click(object sender, System.EventArgs e)
      {
//         if (bOpened)
//         {
            /*encoding =*/ ChooseEncoder(stream);
            UpdateEncoding();
//         }
      }

      // Update status text completion
      private void UpdateTxtStatus()
      {
         labelCompleted.Text = total.ToString() + " / " + completed.ToString();
      }

      private void UpdateEncoding()
      {
         if (encoding.Length > 0)
         {
            txtEncoding.Text = encoding;
         }
         else
         {
            txtEncoding.Text = "(none)";
         }
      }

      // timer func
      private void OnTimer(Object myObject, EventArgs myEventArgs)
      {
         int res;

         StreamProperties x;

         if (bOpened)
         {
            unsafe
            {
               IntPtr t = new IntPtr(&x);
               res = GetAVIFileInfo(t, stream);
               if (res != 0)
                  runtime_error(res, "GetAVIFileInfo");
            }

            completed = (int)x.lLTotal;

            progressBar1.Value = completed;

            UpdateTxtStatus();

            if (completed == total)
            {
               res = CloseAVIStream(true, stream);
               if (res != 0)
                  runtime_error(res, "CloseAVIStream");
               bOpened = false;
            }

            return;
         }

         btnStart.Enabled = true;
         btnStop.Enabled = false;
         btnConfigure.Enabled = true;

         timer1.Enabled = false;
         //ReleaseStream(stream);

         MessageBox.Show(this,
            "Completed successfully!",
            "Done",
            MessageBoxButtons.OK,
            MessageBoxIcon.Information
            );
      }

      // safe Close stream
      private void CloseOpened()
      {
         int res;

         if (bOpened)
         {
            res = CloseAVIStream(false, stream);
            if (res != 0)
               runtime_error(res, "CloseAVIStream");
            //ReleaseStream(stream);
            bOpened = false;
            btnConfigure.Enabled = false;
         }  
      }

      private string get_FourCC(int fourcc)
      {
         string res = "none";

         if (fourcc == 0) // BI_RGB
            return res;
         
         char b0 = (char)(fourcc & 0xFF);
         char b1 = (char)((fourcc & (0xFF << 8)) >> 8);
         char b2 = (char)((fourcc & (0xFF << 16)) >> 16);
         char b3 = (char)((fourcc & (0xFF << 24)) >> 24);

         res = b0.ToString() + b1.ToString() + b2.ToString() + b3.ToString(); 

         return res;
      }

      private void runtime_error(int err, string func)
      {
         MessageBox.Show(this,
            "Whoops! Runtime error in function " + func + ". ErrCode = " + err.ToString(),
            "Error occured",
            MessageBoxButtons.OK,
            MessageBoxIcon.Error
            );
      }

      // Output file selection
      private void btnOutput_Click(object sender, System.EventArgs e)
      {        
         OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();

         openFileDialog.InitialDirectory = "c:\\";
         openFileDialog.Filter = "AVI files (*.avi)|*.avi|All files (*.*)|*.*";
         openFileDialog.FilterIndex = 2;
         openFileDialog.RestoreDirectory = true;
         openFileDialog.CheckFileExists = false;

         if (openFileDialog.ShowDialog() != DialogResult.OK)
         {
            return;
         }

         CloseOpened();

         string resultFile = openFileDialog.FileName;

         txtFolder.Text = resultFile;

         //stream = CreateNewStream();

         btnConfigure.Enabled = false;//true;

         int res = SetStreamProperties(Convert.ToInt32(txtHeight.Text), Convert.ToInt32(txtWidth.Text), Convert.ToInt64(txtDuration.Text), stream);
         if (res != 0)
            runtime_error(res, "SetStreamProperties");

         bOpened = true;

		 res = OpenAVIStream(resultFile, stream);
		 if (res != 0)
			runtime_error(res, "OpenAVIStream");

		 // check weather file exists
         try
         {
            Stream myStream;

			 if((myStream = openFileDialog.OpenFile())!= null)
			 {
				 bFileExists = true;

				 MessageBox.Show(this,
					 "Only export bitmaps from stream is allowed.",
					 "Stream already exists",
					 MessageBoxButtons.OK,
					 MessageBoxIcon.Information
					 );
               
				 myStream.Close();
			 }
//               res = OpenAVIStream(resultFile, stream);
//               if (res != 0)
//                  runtime_error(res, "OpenAVIStream");
            //}
         }
         catch (System.IO.IOException ex)
         {
            bFileExists = false;
         }

         groupBox2.Enabled = bFileExists;

         if (bFileExists)
         {
            StreamProperties x;

            unsafe
            {
               IntPtr t = new IntPtr(&x);

               res = GetAVIFileInfo(t, stream);
               if (res != 0)
                  runtime_error(res, "GetAVIFileInfo");
            }

            txtEwidth.Text = x.lWidth.ToString();
            txtEheight.Text = x.lHeight.ToString();
            txtEduration.Text = x.lLduration.ToString();
            txtEtotal.Text = x.lLTotal.ToString();
            txtEcompression.Text = get_FourCC(x.dwCompression);
         }
         else
         {
            btnStart.Enabled = true;
         }
      }

      // Close window
      private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
      {
         CloseOpened();
      }

      // Construct Bitmap from byte [] array
      unsafe public Bitmap CopyDataToBitmap(byte [] data, int iWidth, int iHeight)
      {
         //Here create the Bitmap to the know height, width and format
         Bitmap bmp = new Bitmap(iWidth, iHeight, PixelFormat.Format24bppRgb);
         //Bitmap bmp = new Bitmap(iWidth, iHeight, PixelFormat.Format32bppArgb);

         //Create a BitmapData and Lock all pixels to be written 
         BitmapData bmpData = bmp.LockBits(
            new Rectangle(0, 0, bmp.Width, bmp.Height),   
            ImageLockMode.WriteOnly, bmp.PixelFormat
         );

         IntPtr dst = bmpData.Scan0;
         // Copy data to Bitmap converting dshow top-bottom
         for (int i = 0; i < bmpData.Height; i++)
         {
            IntPtr dest = new IntPtr((byte *) dst.ToPointer() + i * bmpData.Stride);   
            Marshal.Copy(data, (bmpData.Height - i - 1) * bmpData.Stride, dest, bmpData.Stride);
         }
                
         //Unlock the pixels
         bmp.UnlockBits(bmpData);

         //Return the bitmap 
         return bmp;
      }

      // Export bitmap from existing stream into file
      private void ExportBitmap(long lFrame, int iWidth, int iHeight)
      {
         unsafe
         {
            // Read Image From stream

            int lSize = 0;
            IntPtr size = new IntPtr(&lSize);
            IntPtr data = ReadImageFromStream(lFrame, size, stream);

            // Copy Data to Bitmap
            byte [] arr = new byte[lSize];
            Marshal.Copy(data, arr, 0, (int)lSize);
            Bitmap bmp = CopyDataToBitmap(arr, iWidth, iHeight);

            // Save to File
            string outputFull = txtFolder.Text;
            int pos = outputFull.LastIndexOf('\\') + 1;
            int cnt = outputFull.Length - pos;
            string outDir = outputFull.Remove( pos, cnt );
            string outExport = outDir + "export_" + lFrame.ToString() + ".bmp";
            bmp.Save(outExport, ImageFormat.Bmp);
            bmp.Dispose();

            FreeImage(data, stream);
         }
      }

      // Export bitmap click
      private void btnExport_Click(object sender, System.EventArgs e)
      {
         if (!bOpened)
            return;

         if (txtExport.Text.Length == 0)
            return;

         long lFrame = Convert.ToInt64(txtExport.Text);
         long lTotal = Convert.ToInt64(txtEtotal.Text);

         if (lFrame > 0 && lFrame <= lTotal)
         {
            int iWidth = Convert.ToInt32(txtEwidth.Text);
            int iHeight = Convert.ToInt32(txtEheight.Text);
            ExportBitmap(lFrame, iWidth, iHeight);
         }
      }

      // clear bitmap list
      private void btnClear_Click(object sender, System.EventArgs e)
      {
         listView1.Items.Clear();
         total = 0;
      }

      // Delete items from bitmap list
      private void listView1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
      {
         if (e.KeyCode == Keys.Back || e.KeyCode == Keys.Delete)
         {
            ListView.SelectedListViewItemCollection selection = listView1.SelectedItems;

            foreach ( ListViewItem item in selection )
            {
               listView1.Items.Remove(item);
               total--;
            }

            UpdateTxtStatus();
         }
      }
   }
}
