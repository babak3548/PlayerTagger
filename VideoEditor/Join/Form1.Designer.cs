using System.Collections;
namespace VideoEditor.Join
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;


       


        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code


        private AVITRIMMERCOMLib.TrimmerObjControl m_Trimmer;
        private AVITRIMMERCOMLib.IModuleConfig m_ModuleConfig;
        private Helper m_CB;

        public bool m_bErrorOccured;
        public bool m_bFinished;
        public int m_smm_type;

        private ArrayList m_Ranges;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.ListView listView1;		//Array of parts to join
        private System.Windows.Forms.ColumnHeader file;
        private System.Windows.Forms.ColumnHeader Type;
        private System.Windows.Forms.ProgressBar ProgressBar1;
        private System.Windows.Forms.Timer Timer1;

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.file = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Type = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.labelStatus = new System.Windows.Forms.Label();
            this.listView1 = new System.Windows.Forms.ListView();
            this.ProgressBar1 = new System.Windows.Forms.ProgressBar();
            this.Timer1 = new System.Windows.Forms.Timer();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.buttonInput = new DevExpress.XtraEditors.SimpleButton();
            this.buttonJoin = new DevExpress.XtraEditors.SimpleButton();
            this.buttonClear = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.BtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.SuspendLayout();
            // 
            // file
            // 
            this.file.Text = "فایل";
            this.file.Width = 325;
            // 
            // Type
            // 
            this.Type.Text = "فرمت";
            this.Type.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.Type.Width = 87;
            // 
            // labelStatus
            // 
            this.labelStatus.Location = new System.Drawing.Point(8, 216);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(448, 40);
            this.labelStatus.TabIndex = 0;
            // 
            // listView1
            // 
            this.listView1.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.file,
            this.Type});
            this.listView1.ForeColor = System.Drawing.SystemColors.WindowText;
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Name = "listView1";
            this.listView1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.listView1.Size = new System.Drawing.Size(600, 176);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // ProgressBar1
            // 
            this.ProgressBar1.Location = new System.Drawing.Point(0, 189);
            this.ProgressBar1.Name = "ProgressBar1";
            this.ProgressBar1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.ProgressBar1.Size = new System.Drawing.Size(308, 24);
            this.ProgressBar1.TabIndex = 4;
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(30, 244);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(389, 13);
            this.labelControl1.TabIndex = 7;
            this.labelControl1.Text = " ASF, AVI, AVCHD, MKV, MP4, MOV,MP3, MPEG1, MPEG2, WAV, WMA, WEBM,TS";
            // 
            // buttonInput
            // 
            this.buttonInput.Location = new System.Drawing.Point(515, 189);
            this.buttonInput.Name = "buttonInput";
            this.buttonInput.Size = new System.Drawing.Size(85, 23);
            this.buttonInput.TabIndex = 8;
            this.buttonInput.Text = "انتخاب فایل";
            this.buttonInput.Click += new System.EventHandler(this.simpleButton1_Click);
            // 
            // buttonJoin
            // 
            this.buttonJoin.Location = new System.Drawing.Point(314, 190);
            this.buttonJoin.Name = "buttonJoin";
            this.buttonJoin.Size = new System.Drawing.Size(85, 23);
            this.buttonJoin.TabIndex = 9;
            this.buttonJoin.Text = "شروع عملیات";
            this.buttonJoin.Click += new System.EventHandler(this.simpleButton2_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(405, 189);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(104, 23);
            this.buttonClear.TabIndex = 10;
            this.buttonClear.Text = "پاک کردن لیست";
            this.buttonClear.Click += new System.EventHandler(this.simpleButton3_Click);
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(440, 244);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(154, 13);
            this.labelControl2.TabIndex = 11;
            this.labelControl2.Text = "فرمت های پشتیبانی شده:";
            // 
            // BtnCancel
            // 
            this.BtnCancel.Location = new System.Drawing.Point(515, 218);
            this.BtnCancel.Name = "BtnCancel";
            this.BtnCancel.Size = new System.Drawing.Size(85, 23);
            this.BtnCancel.TabIndex = 12;
            this.BtnCancel.Text = "لغو  عملیات";
            this.BtnCancel.Click += new System.EventHandler(this.BtnCancel_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(606, 266);
            this.Controls.Add(this.BtnCancel);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.buttonJoin);
            this.Controls.Add(this.buttonInput);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.ProgressBar1);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.labelStatus);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Join files";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.SimpleButton buttonInput;
        private DevExpress.XtraEditors.SimpleButton buttonJoin;
        private DevExpress.XtraEditors.SimpleButton buttonClear;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.SimpleButton BtnCancel;







    }
}