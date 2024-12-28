namespace Player.DataControl
{
    partial class LeadConvert
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LeadConvert));
            this.convertCtrl = new Leadtools.Multimedia.ConvertCtrl();
            ((System.ComponentModel.ISupportInitialize)(this.txtTarget.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtSource.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbFormat.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.convertCtrl)).BeginInit();
            this.SuspendLayout();
            // 
            // txtTarget
            // 
            resources.ApplyResources(this.txtTarget, "txtTarget");
            this.txtTarget.Properties.AccessibleDescription = resources.GetString("txtTarget.Properties.AccessibleDescription");
            this.txtTarget.Properties.AccessibleName = resources.GetString("txtTarget.Properties.AccessibleName");
            this.txtTarget.Properties.AutoHeight = ((bool)(resources.GetObject("txtTarget.Properties.AutoHeight")));
            this.txtTarget.Properties.Mask.AutoComplete = ((DevExpress.XtraEditors.Mask.AutoCompleteType)(resources.GetObject("txtTarget.Properties.Mask.AutoComplete")));
            this.txtTarget.Properties.Mask.BeepOnError = ((bool)(resources.GetObject("txtTarget.Properties.Mask.BeepOnError")));
            this.txtTarget.Properties.Mask.EditMask = resources.GetString("txtTarget.Properties.Mask.EditMask");
            this.txtTarget.Properties.Mask.IgnoreMaskBlank = ((bool)(resources.GetObject("txtTarget.Properties.Mask.IgnoreMaskBlank")));
            this.txtTarget.Properties.Mask.MaskType = ((DevExpress.XtraEditors.Mask.MaskType)(resources.GetObject("txtTarget.Properties.Mask.MaskType")));
            this.txtTarget.Properties.Mask.PlaceHolder = ((char)(resources.GetObject("txtTarget.Properties.Mask.PlaceHolder")));
            this.txtTarget.Properties.Mask.SaveLiteral = ((bool)(resources.GetObject("txtTarget.Properties.Mask.SaveLiteral")));
            this.txtTarget.Properties.Mask.ShowPlaceHolders = ((bool)(resources.GetObject("txtTarget.Properties.Mask.ShowPlaceHolders")));
            this.txtTarget.Properties.Mask.UseMaskAsDisplayFormat = ((bool)(resources.GetObject("txtTarget.Properties.Mask.UseMaskAsDisplayFormat")));
            this.txtTarget.Properties.NullValuePrompt = resources.GetString("txtTarget.Properties.NullValuePrompt");
            this.txtTarget.Properties.NullValuePromptShowForEmptyValue = ((bool)(resources.GetObject("txtTarget.Properties.NullValuePromptShowForEmptyValue")));
            // 
            // TxtSource
            // 
            resources.ApplyResources(this.TxtSource, "TxtSource");
            this.TxtSource.Properties.AccessibleDescription = resources.GetString("TxtSource.Properties.AccessibleDescription");
            this.TxtSource.Properties.AccessibleName = resources.GetString("TxtSource.Properties.AccessibleName");
            this.TxtSource.Properties.AutoHeight = ((bool)(resources.GetObject("TxtSource.Properties.AutoHeight")));
            this.TxtSource.Properties.Mask.AutoComplete = ((DevExpress.XtraEditors.Mask.AutoCompleteType)(resources.GetObject("TxtSource.Properties.Mask.AutoComplete")));
            this.TxtSource.Properties.Mask.BeepOnError = ((bool)(resources.GetObject("TxtSource.Properties.Mask.BeepOnError")));
            this.TxtSource.Properties.Mask.EditMask = resources.GetString("TxtSource.Properties.Mask.EditMask");
            this.TxtSource.Properties.Mask.IgnoreMaskBlank = ((bool)(resources.GetObject("TxtSource.Properties.Mask.IgnoreMaskBlank")));
            this.TxtSource.Properties.Mask.MaskType = ((DevExpress.XtraEditors.Mask.MaskType)(resources.GetObject("TxtSource.Properties.Mask.MaskType")));
            this.TxtSource.Properties.Mask.PlaceHolder = ((char)(resources.GetObject("TxtSource.Properties.Mask.PlaceHolder")));
            this.TxtSource.Properties.Mask.SaveLiteral = ((bool)(resources.GetObject("TxtSource.Properties.Mask.SaveLiteral")));
            this.TxtSource.Properties.Mask.ShowPlaceHolders = ((bool)(resources.GetObject("TxtSource.Properties.Mask.ShowPlaceHolders")));
            this.TxtSource.Properties.Mask.UseMaskAsDisplayFormat = ((bool)(resources.GetObject("TxtSource.Properties.Mask.UseMaskAsDisplayFormat")));
            this.TxtSource.Properties.NullValuePrompt = resources.GetString("TxtSource.Properties.NullValuePrompt");
            this.TxtSource.Properties.NullValuePromptShowForEmptyValue = ((bool)(resources.GetObject("TxtSource.Properties.NullValuePromptShowForEmptyValue")));
            // 
            // btnOpenSource
            // 
            resources.ApplyResources(this.btnOpenSource, "btnOpenSource");
            // 
            // btnSaveFileTarget
            // 
            resources.ApplyResources(this.btnSaveFileTarget, "btnSaveFileTarget");
            // 
            // labelControl1
            // 
            resources.ApplyResources(this.labelControl1, "labelControl1");
            // 
            // labelControl2
            // 
            resources.ApplyResources(this.labelControl2, "labelControl2");
            // 
            // labelControl3
            // 
            resources.ApplyResources(this.labelControl3, "labelControl3");
            // 
            // btnConvert
            // 
            resources.ApplyResources(this.btnConvert, "btnConvert");
            // 
            // cmbFormat
            // 
            resources.ApplyResources(this.cmbFormat, "cmbFormat");
            this.cmbFormat.Properties.AccessibleDescription = resources.GetString("cmbFormat.Properties.AccessibleDescription");
            this.cmbFormat.Properties.AccessibleName = resources.GetString("cmbFormat.Properties.AccessibleName");
            this.cmbFormat.Properties.AutoHeight = ((bool)(resources.GetObject("cmbFormat.Properties.AutoHeight")));
            this.cmbFormat.Properties.NullText = resources.GetString("cmbFormat.Properties.NullText");
            this.cmbFormat.Properties.NullValuePrompt = resources.GetString("cmbFormat.Properties.NullValuePrompt");
            this.cmbFormat.Properties.NullValuePromptShowForEmptyValue = ((bool)(resources.GetObject("cmbFormat.Properties.NullValuePromptShowForEmptyValue")));
            // 
            // prgConvert
            // 
            resources.ApplyResources(this.prgConvert, "prgConvert");
            // 
            // convertCtrl
            // 
            resources.ApplyResources(this.convertCtrl, "convertCtrl");
            this.convertCtrl.AudioCompressors.Selection = -1;
            this.convertCtrl.Name = "convertCtrl";
            this.convertCtrl.OcxState = null;
            this.convertCtrl.SourceFile = null;
            this.convertCtrl.TargetDevices.Selection = -1;
            this.convertCtrl.TargetFile = null;
            this.convertCtrl.VideoCompressors.Selection = -1;
            this.convertCtrl.WMProfile.Description = "";
            this.convertCtrl.WMProfile.Name = "";
            this.convertCtrl.ErrorAbort += new Leadtools.Multimedia.ErrorAbortEventHandler(this.convertCtrl_ErrorAbort);
            this.convertCtrl.Progress += new Leadtools.Multimedia.ProgressEventHandler(this.convertCtrl1_Progress);
            // 
            // LeadConvert
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.convertCtrl);
            this.Name = "LeadConvert";
            this.Controls.SetChildIndex(this.prgConvert, 0);
            this.Controls.SetChildIndex(this.convertCtrl, 0);
            this.Controls.SetChildIndex(this.cmbFormat, 0);
            this.Controls.SetChildIndex(this.TxtSource, 0);
            this.Controls.SetChildIndex(this.btnOpenSource, 0);
            this.Controls.SetChildIndex(this.txtTarget, 0);
            this.Controls.SetChildIndex(this.btnSaveFileTarget, 0);
            this.Controls.SetChildIndex(this.labelControl1, 0);
            this.Controls.SetChildIndex(this.labelControl2, 0);
            this.Controls.SetChildIndex(this.labelControl3, 0);
            this.Controls.SetChildIndex(this.btnConvert, 0);
            ((System.ComponentModel.ISupportInitialize)(this.txtTarget.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtSource.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbFormat.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.convertCtrl)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Leadtools.Multimedia.ConvertCtrl convertCtrl;
    }
}
