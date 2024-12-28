namespace Player.DataControl
{
    partial class UCBackUp
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UCBackUp));
            this.txtPath = new DevExpress.XtraEditors.TextEdit();
            this.btnFolderBrowser = new DevExpress.XtraEditors.SimpleButton();
            this.Path = new DevExpress.XtraEditors.LabelControl();
            this.btnStartBackUp = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.TxtFolderBackName = new DevExpress.XtraEditors.TextEdit();
            this.lblFolerName = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.txtPath.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtFolderBackName.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // txtPath
            // 
            resources.ApplyResources(this.txtPath, "txtPath");
            this.txtPath.Name = "txtPath";
            this.txtPath.Properties.ReadOnly = true;
            // 
            // btnFolderBrowser
            // 
            resources.ApplyResources(this.btnFolderBrowser, "btnFolderBrowser");
            this.btnFolderBrowser.Name = "btnFolderBrowser";
            this.btnFolderBrowser.Click += new System.EventHandler(this.btnFolderBrowser_Click);
            // 
            // Path
            // 
            resources.ApplyResources(this.Path, "Path");
            this.Path.Name = "Path";
            // 
            // btnStartBackUp
            // 
            resources.ApplyResources(this.btnStartBackUp, "btnStartBackUp");
            this.btnStartBackUp.Name = "btnStartBackUp";
            this.btnStartBackUp.Click += new System.EventHandler(this.btnStartBackUp_Click);
            // 
            // btnCancel
            // 
            resources.ApplyResources(this.btnCancel, "btnCancel");
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // TxtFolderBackName
            // 
            resources.ApplyResources(this.TxtFolderBackName, "TxtFolderBackName");
            this.TxtFolderBackName.Name = "TxtFolderBackName";
            // 
            // lblFolerName
            // 
            resources.ApplyResources(this.lblFolerName, "lblFolerName");
            this.lblFolerName.Name = "lblFolerName";
            // 
            // UCBackUp
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lblFolerName);
            this.Controls.Add(this.TxtFolderBackName);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnStartBackUp);
            this.Controls.Add(this.Path);
            this.Controls.Add(this.btnFolderBrowser);
            this.Controls.Add(this.txtPath);
            this.Name = "UCBackUp";
            ((System.ComponentModel.ISupportInitialize)(this.txtPath.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtFolderBackName.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.TextEdit txtPath;
        private DevExpress.XtraEditors.SimpleButton btnFolderBrowser;
        private DevExpress.XtraEditors.LabelControl Path;
        private DevExpress.XtraEditors.SimpleButton btnStartBackUp;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.TextEdit TxtFolderBackName;
        private DevExpress.XtraEditors.LabelControl lblFolerName;
    }
}
