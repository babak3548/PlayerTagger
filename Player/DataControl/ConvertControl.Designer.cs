namespace Player.DataControl
{
    partial class ConvertControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConvertControl));
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.TxtSource = new DevExpress.XtraEditors.TextEdit();
            this.btnOpenSource = new DevExpress.XtraEditors.SimpleButton();
            this.btnSaveFileTarget = new DevExpress.XtraEditors.SimpleButton();
            this.txtTarget = new DevExpress.XtraEditors.TextEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.btnConvert = new DevExpress.XtraEditors.SimpleButton();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.cmbFormat = new DevExpress.XtraEditors.LookUpEdit();
            this.prgConvert = new System.Windows.Forms.ProgressBar();
            ((System.ComponentModel.ISupportInitialize)(this.TxtSource.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtTarget.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbFormat.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            resources.ApplyResources(this.openFileDialog1, "openFileDialog1");
            // 
            // TxtSource
            // 
            resources.ApplyResources(this.TxtSource, "TxtSource");
            this.TxtSource.Name = "TxtSource";
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
            this.btnOpenSource.Name = "btnOpenSource";
            this.btnOpenSource.Click += new System.EventHandler(this.simpleButton1_Click);
            // 
            // btnSaveFileTarget
            // 
            resources.ApplyResources(this.btnSaveFileTarget, "btnSaveFileTarget");
            this.btnSaveFileTarget.Name = "btnSaveFileTarget";
            this.btnSaveFileTarget.Click += new System.EventHandler(this.btnSaveFileTarget_Click);
            // 
            // txtTarget
            // 
            resources.ApplyResources(this.txtTarget, "txtTarget");
            this.txtTarget.Name = "txtTarget";
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
            // labelControl1
            // 
            resources.ApplyResources(this.labelControl1, "labelControl1");
            this.labelControl1.Name = "labelControl1";
            // 
            // labelControl2
            // 
            resources.ApplyResources(this.labelControl2, "labelControl2");
            this.labelControl2.Name = "labelControl2";
            // 
            // labelControl3
            // 
            resources.ApplyResources(this.labelControl3, "labelControl3");
            this.labelControl3.Name = "labelControl3";
            // 
            // btnConvert
            // 
            resources.ApplyResources(this.btnConvert, "btnConvert");
            this.btnConvert.Name = "btnConvert";
            this.btnConvert.Click += new System.EventHandler(this.btnConvert_Click);
            // 
            // saveFileDialog1
            // 
            resources.ApplyResources(this.saveFileDialog1, "saveFileDialog1");
            // 
            // cmbFormat
            // 
            resources.ApplyResources(this.cmbFormat, "cmbFormat");
            this.cmbFormat.Name = "cmbFormat";
            this.cmbFormat.Properties.AccessibleDescription = resources.GetString("cmbFormat.Properties.AccessibleDescription");
            this.cmbFormat.Properties.AccessibleName = resources.GetString("cmbFormat.Properties.AccessibleName");
            this.cmbFormat.Properties.AutoHeight = ((bool)(resources.GetObject("cmbFormat.Properties.AutoHeight")));
            this.cmbFormat.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(((DevExpress.XtraEditors.Controls.ButtonPredefines)(resources.GetObject("cmbFormat.Properties.Buttons"))))});
            this.cmbFormat.Properties.NullText = resources.GetString("cmbFormat.Properties.NullText");
            this.cmbFormat.Properties.NullValuePrompt = resources.GetString("cmbFormat.Properties.NullValuePrompt");
            this.cmbFormat.Properties.NullValuePromptShowForEmptyValue = ((bool)(resources.GetObject("cmbFormat.Properties.NullValuePromptShowForEmptyValue")));
            this.cmbFormat.Properties.PopupSizeable = false;
            this.cmbFormat.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.Standard;
            // 
            // prgConvert
            // 
            resources.ApplyResources(this.prgConvert, "prgConvert");
            this.prgConvert.Name = "prgConvert";
            // 
            // ConvertControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.prgConvert);
            this.Controls.Add(this.btnConvert);
            this.Controls.Add(this.labelControl3);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.btnSaveFileTarget);
            this.Controls.Add(this.txtTarget);
            this.Controls.Add(this.btnOpenSource);
            this.Controls.Add(this.TxtSource);
            this.Controls.Add(this.cmbFormat);
            this.Name = "ConvertControl";
            ((System.ComponentModel.ISupportInitialize)(this.TxtSource.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtTarget.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbFormat.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        protected DevExpress.XtraEditors.TextEdit txtTarget;
        protected DevExpress.XtraEditors.TextEdit TxtSource;
        protected DevExpress.XtraEditors.SimpleButton btnOpenSource;
        protected DevExpress.XtraEditors.SimpleButton btnSaveFileTarget;
        protected DevExpress.XtraEditors.LabelControl labelControl1;
        protected DevExpress.XtraEditors.LabelControl labelControl2;
        protected DevExpress.XtraEditors.LabelControl labelControl3;
        protected DevExpress.XtraEditors.SimpleButton btnConvert;
        protected DevExpress.XtraEditors.LookUpEdit cmbFormat;
        protected System.Windows.Forms.ProgressBar prgConvert;
    }
}
