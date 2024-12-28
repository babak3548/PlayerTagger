namespace Player.DataControl
{
    partial class UCRestoreBackup
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UCRestoreBackup));
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.btnStart = new DevExpress.XtraEditors.SimpleButton();
            this.Path = new DevExpress.XtraEditors.LabelControl();
            this.btnFolderBrowser = new DevExpress.XtraEditors.SimpleButton();
            this.txtBackUpPath = new DevExpress.XtraEditors.TextEdit();
            this.btnRestore = new DevExpress.XtraEditors.SimpleButton();
            this.TxtRestore = new DevExpress.XtraEditors.TextEdit();
            this.label1 = new DevExpress.XtraEditors.LabelControl();
            this.label2 = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.txtBackUpPath.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtRestore.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            resources.ApplyResources(this.btnCancel, "btnCancel");
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click_1);
            // 
            // btnStart
            // 
            resources.ApplyResources(this.btnStart, "btnStart");
            this.btnStart.Name = "btnStart";
            this.btnStart.Click += new System.EventHandler(this.btnStartBackUp_Click);
            // 
            // Path
            // 
            resources.ApplyResources(this.Path, "Path");
            this.Path.Name = "Path";
            // 
            // btnFolderBrowser
            // 
            resources.ApplyResources(this.btnFolderBrowser, "btnFolderBrowser");
            this.btnFolderBrowser.Name = "btnFolderBrowser";
            this.btnFolderBrowser.Click += new System.EventHandler(this.btnFolderBrowser_Click_1);
            // 
            // txtBackUpPath
            // 
            resources.ApplyResources(this.txtBackUpPath, "txtBackUpPath");
            this.txtBackUpPath.Name = "txtBackUpPath";
            this.txtBackUpPath.Properties.ReadOnly = true;
            // 
            // btnRestore
            // 
            resources.ApplyResources(this.btnRestore, "btnRestore");
            this.btnRestore.Name = "btnRestore";
            this.btnRestore.Click += new System.EventHandler(this.btnRestore_Click);
            // 
            // TxtRestore
            // 
            resources.ApplyResources(this.TxtRestore, "TxtRestore");
            this.TxtRestore.Name = "TxtRestore";
            this.TxtRestore.Properties.ReadOnly = true;
            this.TxtRestore.EditValueChanged += new System.EventHandler(this.TxtRestore_EditValueChanged);
            // 
            // label1
            // 
            this.label1.Appearance.ForeColor = ((System.Drawing.Color)(resources.GetObject("label1.Appearance.ForeColor")));
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // label2
            // 
            this.label2.Appearance.ForeColor = ((System.Drawing.Color)(resources.GetObject("label2.Appearance.ForeColor")));
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // UCRestoreBackup
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnRestore);
            this.Controls.Add(this.TxtRestore);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.Path);
            this.Controls.Add(this.btnFolderBrowser);
            this.Controls.Add(this.txtBackUpPath);
            this.Name = "UCRestoreBackup";
            ((System.ComponentModel.ISupportInitialize)(this.txtBackUpPath.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtRestore.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SimpleButton btnStart;
        private DevExpress.XtraEditors.LabelControl Path;
        private DevExpress.XtraEditors.SimpleButton btnFolderBrowser;
        private DevExpress.XtraEditors.TextEdit txtBackUpPath;
        private DevExpress.XtraEditors.SimpleButton btnRestore;
        private DevExpress.XtraEditors.TextEdit TxtRestore;
        private DevExpress.XtraEditors.LabelControl label1;
        private DevExpress.XtraEditors.LabelControl label2;
    }
}
