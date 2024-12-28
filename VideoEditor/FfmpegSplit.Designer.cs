namespace VideoEditor
{
    partial class FfmpegSplit
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

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.progressBarControlSplit = new DevExpress.XtraEditors.ProgressBarControl();
            this.simpleButton1 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton2 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton3 = new DevExpress.XtraEditors.SimpleButton();
            this.txtFullFileName = new DevExpress.XtraEditors.TextEdit();
            this.simpleButton4 = new DevExpress.XtraEditors.SimpleButton();
            this.gridControl1 = new DevExpress.XtraGrid.GridControl();
            this.spliteShutInfoBindingSource1 = new System.Windows.Forms.BindingSource();
            this.gridView1 = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.colinputFile = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colstartTime = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colSliceTime = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colstartTimeInCuter = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colSliceTimeInCuter = new DevExpress.XtraGrid.Columns.GridColumn();
            this.lblWait = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.progressBarControlSplit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFullFileName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spliteShutInfoBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // progressBarControlSplit
            // 
            this.progressBarControlSplit.Location = new System.Drawing.Point(12, 270);
            this.progressBarControlSplit.Name = "progressBarControlSplit";
            this.progressBarControlSplit.Properties.Step = 5;
            this.progressBarControlSplit.Size = new System.Drawing.Size(457, 18);
            this.progressBarControlSplit.TabIndex = 0;
            // 
            // simpleButton1
            // 
            this.simpleButton1.Location = new System.Drawing.Point(367, 294);
            this.simpleButton1.Name = "simpleButton1";
            this.simpleButton1.Size = new System.Drawing.Size(102, 23);
            this.simpleButton1.TabIndex = 1;
            this.simpleButton1.Text = "شروع عملیات";
            this.simpleButton1.Click += new System.EventHandler(this.simpleButton1_Click);
            // 
            // simpleButton2
            // 
            this.simpleButton2.Location = new System.Drawing.Point(151, 294);
            this.simpleButton2.Name = "simpleButton2";
            this.simpleButton2.Size = new System.Drawing.Size(102, 23);
            this.simpleButton2.TabIndex = 2;
            this.simpleButton2.Text = "پاک کردن لیست";
            this.simpleButton2.Click += new System.EventHandler(this.simpleButton2_Click);
            // 
            // simpleButton3
            // 
            this.simpleButton3.Location = new System.Drawing.Point(259, 294);
            this.simpleButton3.Name = "simpleButton3";
            this.simpleButton3.Size = new System.Drawing.Size(102, 23);
            this.simpleButton3.TabIndex = 4;
            this.simpleButton3.Text = "ادامه";
            this.simpleButton3.Click += new System.EventHandler(this.simpleButton3_Click);
            // 
            // txtFullFileName
            // 
            this.txtFullFileName.Enabled = false;
            this.txtFullFileName.Location = new System.Drawing.Point(56, 244);
            this.txtFullFileName.Name = "txtFullFileName";
            this.txtFullFileName.Size = new System.Drawing.Size(414, 20);
            this.txtFullFileName.TabIndex = 5;
            // 
            // simpleButton4
            // 
            this.simpleButton4.Location = new System.Drawing.Point(12, 242);
            this.simpleButton4.Name = "simpleButton4";
            this.simpleButton4.Size = new System.Drawing.Size(38, 23);
            this.simpleButton4.TabIndex = 6;
            this.simpleButton4.Text = ". . .";
            this.simpleButton4.Click += new System.EventHandler(this.simpleButton4_Click);
            // 
            // gridControl1
            // 
            this.gridControl1.DataSource = this.spliteShutInfoBindingSource1;
            this.gridControl1.Location = new System.Drawing.Point(12, 10);
            this.gridControl1.MainView = this.gridView1;
            this.gridControl1.Name = "gridControl1";
            this.gridControl1.Size = new System.Drawing.Size(458, 228);
            this.gridControl1.TabIndex = 7;
            this.gridControl1.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView1});
            // 
            // spliteShutInfoBindingSource1
            // 
            this.spliteShutInfoBindingSource1.DataSource = typeof(VideoEditor.SpliteShutInfo);
            // 
            // gridView1
            // 
            this.gridView1.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.colinputFile,
            this.colstartTime,
            this.colSliceTime,
            this.colstartTimeInCuter,
            this.colSliceTimeInCuter});
            this.gridView1.GridControl = this.gridControl1;
            this.gridView1.Name = "gridView1";
            this.gridView1.OptionsView.ShowGroupPanel = false;
            // 
            // colinputFile
            // 
            this.colinputFile.FieldName = "inputFile";
            this.colinputFile.Name = "colinputFile";
            this.colinputFile.Visible = true;
            this.colinputFile.VisibleIndex = 0;
            this.colinputFile.Width = 300;
            // 
            // colstartTime
            // 
            this.colstartTime.FieldName = "startTime";
            this.colstartTime.Name = "colstartTime";
            this.colstartTime.Visible = true;
            this.colstartTime.VisibleIndex = 1;
            this.colstartTime.Width = 69;
            // 
            // colSliceTime
            // 
            this.colSliceTime.FieldName = "SliceTime";
            this.colSliceTime.Name = "colSliceTime";
            this.colSliceTime.Visible = true;
            this.colSliceTime.VisibleIndex = 2;
            this.colSliceTime.Width = 60;
            // 
            // colstartTimeInCuter
            // 
            this.colstartTimeInCuter.FieldName = "startTimeInCuter";
            this.colstartTimeInCuter.Name = "colstartTimeInCuter";
            // 
            // colSliceTimeInCuter
            // 
            this.colSliceTimeInCuter.FieldName = "SliceTimeInCuter";
            this.colSliceTimeInCuter.Name = "colSliceTimeInCuter";
            // 
            // lblWait
            // 
            this.lblWait.Location = new System.Drawing.Point(8, 297);
            this.lblWait.Name = "lblWait";
            this.lblWait.Size = new System.Drawing.Size(137, 13);
            this.lblWait.TabIndex = 8;
            this.lblWait.Text = "برنامه درحال اجرا می باشد";
            this.lblWait.Visible = false;
            // 
            // FfmpegSplit
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 322);
            this.Controls.Add(this.lblWait);
            this.Controls.Add(this.gridControl1);
            this.Controls.Add(this.simpleButton4);
            this.Controls.Add(this.txtFullFileName);
            this.Controls.Add(this.simpleButton3);
            this.Controls.Add(this.simpleButton2);
            this.Controls.Add(this.simpleButton1);
            this.Controls.Add(this.progressBarControlSplit);
            this.Name = "FfmpegSplit";
            this.Text = "ذخیره شات ها";
            this.Load += new System.EventHandler(this.FfmpegSplit_Load);
            ((System.ComponentModel.ISupportInitialize)(this.progressBarControlSplit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFullFileName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spliteShutInfoBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ProgressBarControl progressBarControlSplit;
        private DevExpress.XtraEditors.SimpleButton simpleButton1;
        private DevExpress.XtraEditors.SimpleButton simpleButton2;
        private DevExpress.XtraEditors.SimpleButton simpleButton3;
        private DevExpress.XtraEditors.TextEdit txtFullFileName;
        private DevExpress.XtraEditors.SimpleButton simpleButton4;
        private DevExpress.XtraGrid.GridControl gridControl1;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView1;
        private System.Windows.Forms.BindingSource spliteShutInfoBindingSource1;
        private DevExpress.XtraGrid.Columns.GridColumn colinputFile;
        private DevExpress.XtraGrid.Columns.GridColumn colstartTime;
        private DevExpress.XtraGrid.Columns.GridColumn colSliceTime;
        private DevExpress.XtraGrid.Columns.GridColumn colstartTimeInCuter;
        private DevExpress.XtraGrid.Columns.GridColumn colSliceTimeInCuter;
        private DevExpress.XtraEditors.LabelControl lblWait;

    }
}