namespace Player
{
    partial class SettingForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SettingForm));
            this.defaulttitleLabel = new System.Windows.Forms.Label();
            this.horizontalResolutionLabel = new System.Windows.Forms.Label();
            this.showToolTipControllerLabel = new System.Windows.Forms.Label();
            this.thumbHeightLabel = new System.Windows.Forms.Label();
            this.thumbWidthLabel = new System.Windows.Forms.Label();
            this.verticalResolutionLabel = new System.Windows.Forms.Label();
            this.Languge = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cmbPlayerType = new DevExpress.XtraEditors.LookUpEdit();
            this.appSettingBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.btnFolderBrowser = new System.Windows.Forms.Button();
            this.Save = new System.Windows.Forms.Button();
            this.defaulttitleTextEdit = new DevExpress.XtraEditors.TextEdit();
            this.horizontalResolutionSpinEdit = new DevExpress.XtraEditors.SpinEdit();
            this.showToolTipControllerCheckEdit = new DevExpress.XtraEditors.CheckEdit();
            this.thumbHeightSpinEdit = new DevExpress.XtraEditors.SpinEdit();
            this.thumbWidthSpinEdit = new DevExpress.XtraEditors.SpinEdit();
            this.verticalResolutionSpinEdit = new DevExpress.XtraEditors.SpinEdit();
            this.CombLanguge = new DevExpress.XtraEditors.LookUpEdit();
            this.folderBrowserDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.DefaultMetaDataFilePath = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.DefaultFilesPath = new System.Windows.Forms.Label();
            this.LblSkinName = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.txtMetaDataFilePath = new DevExpress.XtraEditors.ButtonEdit();
            this.TxtEDefaultMetaDetaPath = new DevExpress.XtraEditors.ButtonEdit();
            this.tetEDefaultfilesPath = new DevExpress.XtraEditors.ButtonEdit();
            this.standaloneBarDockControl1 = new DevExpress.XtraBars.StandaloneBarDockControl();
            this.barManager1 = new DevExpress.XtraBars.BarManager(this.components);
            this.bar1 = new DevExpress.XtraBars.Bar();
            this.SkinMenu = new DevExpress.XtraBars.BarSubItem();
            this.barDockControlTop = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlBottom = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlLeft = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlRight = new DevExpress.XtraBars.BarDockControl();
            ((System.ComponentModel.ISupportInitialize)(this.cmbPlayerType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.appSettingBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.defaulttitleTextEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.horizontalResolutionSpinEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.showToolTipControllerCheckEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbHeightSpinEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbWidthSpinEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.verticalResolutionSpinEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CombLanguge.Properties)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtMetaDataFilePath.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtEDefaultMetaDetaPath.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tetEDefaultfilesPath.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).BeginInit();
            this.SuspendLayout();
            // 
            // defaulttitleLabel
            // 
            resources.ApplyResources(this.defaulttitleLabel, "defaulttitleLabel");
            this.defaulttitleLabel.Name = "defaulttitleLabel";
            // 
            // horizontalResolutionLabel
            // 
            resources.ApplyResources(this.horizontalResolutionLabel, "horizontalResolutionLabel");
            this.horizontalResolutionLabel.Name = "horizontalResolutionLabel";
            // 
            // showToolTipControllerLabel
            // 
            resources.ApplyResources(this.showToolTipControllerLabel, "showToolTipControllerLabel");
            this.showToolTipControllerLabel.Name = "showToolTipControllerLabel";
            // 
            // thumbHeightLabel
            // 
            resources.ApplyResources(this.thumbHeightLabel, "thumbHeightLabel");
            this.thumbHeightLabel.Name = "thumbHeightLabel";
            // 
            // thumbWidthLabel
            // 
            resources.ApplyResources(this.thumbWidthLabel, "thumbWidthLabel");
            this.thumbWidthLabel.Name = "thumbWidthLabel";
            // 
            // verticalResolutionLabel
            // 
            resources.ApplyResources(this.verticalResolutionLabel, "verticalResolutionLabel");
            this.verticalResolutionLabel.Name = "verticalResolutionLabel";
            // 
            // Languge
            // 
            resources.ApplyResources(this.Languge, "Languge");
            this.Languge.Name = "Languge";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // cmbPlayerType
            // 
            this.cmbPlayerType.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "PlayerType", true));
            resources.ApplyResources(this.cmbPlayerType, "cmbPlayerType");
            this.cmbPlayerType.Name = "cmbPlayerType";
            this.cmbPlayerType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(((DevExpress.XtraEditors.Controls.ButtonPredefines)(resources.GetObject("cmbPlayerType.Properties.Buttons"))))});
            this.cmbPlayerType.Properties.DisplayMember = "Value";
            this.cmbPlayerType.Properties.NullText = resources.GetString("cmbPlayerType.Properties.NullText");
            this.cmbPlayerType.Properties.PopupSizeable = false;
            this.cmbPlayerType.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.Standard;
            this.cmbPlayerType.Properties.ValueMember = "Key";
            // 
            // appSettingBindingSource
            // 
            this.appSettingBindingSource.DataSource = typeof(Player.Setting.AppSetting);
            // 
            // btnFolderBrowser
            // 
            resources.ApplyResources(this.btnFolderBrowser, "btnFolderBrowser");
            this.btnFolderBrowser.Name = "btnFolderBrowser";
            this.btnFolderBrowser.UseVisualStyleBackColor = true;
            // 
            // Save
            // 
            this.Save.ForeColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.Save, "Save");
            this.Save.Name = "Save";
            this.Save.UseVisualStyleBackColor = true;
            this.Save.Click += new System.EventHandler(this.Save_Click);
            // 
            // defaulttitleTextEdit
            // 
            this.defaulttitleTextEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "Defaulttitle", true));
            resources.ApplyResources(this.defaulttitleTextEdit, "defaulttitleTextEdit");
            this.defaulttitleTextEdit.Name = "defaulttitleTextEdit";
            // 
            // horizontalResolutionSpinEdit
            // 
            this.horizontalResolutionSpinEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "HorizontalResolution", true));
            resources.ApplyResources(this.horizontalResolutionSpinEdit, "horizontalResolutionSpinEdit");
            this.horizontalResolutionSpinEdit.Name = "horizontalResolutionSpinEdit";
            this.horizontalResolutionSpinEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            // 
            // showToolTipControllerCheckEdit
            // 
            this.showToolTipControllerCheckEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "ShowToolTipController", true));
            resources.ApplyResources(this.showToolTipControllerCheckEdit, "showToolTipControllerCheckEdit");
            this.showToolTipControllerCheckEdit.Name = "showToolTipControllerCheckEdit";
            this.showToolTipControllerCheckEdit.Properties.Caption = resources.GetString("showToolTipControllerCheckEdit.Properties.Caption");
            // 
            // thumbHeightSpinEdit
            // 
            this.thumbHeightSpinEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "ThumbHeight", true));
            resources.ApplyResources(this.thumbHeightSpinEdit, "thumbHeightSpinEdit");
            this.thumbHeightSpinEdit.Name = "thumbHeightSpinEdit";
            this.thumbHeightSpinEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            // 
            // thumbWidthSpinEdit
            // 
            this.thumbWidthSpinEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "ThumbWidth", true));
            resources.ApplyResources(this.thumbWidthSpinEdit, "thumbWidthSpinEdit");
            this.thumbWidthSpinEdit.Name = "thumbWidthSpinEdit";
            this.thumbWidthSpinEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            // 
            // verticalResolutionSpinEdit
            // 
            this.verticalResolutionSpinEdit.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "VerticalResolution", true));
            resources.ApplyResources(this.verticalResolutionSpinEdit, "verticalResolutionSpinEdit");
            this.verticalResolutionSpinEdit.Name = "verticalResolutionSpinEdit";
            this.verticalResolutionSpinEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            // 
            // CombLanguge
            // 
            this.CombLanguge.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "Language", true));
            resources.ApplyResources(this.CombLanguge, "CombLanguge");
            this.CombLanguge.Name = "CombLanguge";
            this.CombLanguge.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(((DevExpress.XtraEditors.Controls.ButtonPredefines)(resources.GetObject("CombLanguge.Properties.Buttons"))))});
            this.CombLanguge.Properties.DisplayMember = "Value";
            this.CombLanguge.Properties.NullText = resources.GetString("CombLanguge.Properties.NullText");
            this.CombLanguge.Properties.PopupSizeable = false;
            this.CombLanguge.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.Standard;
            this.CombLanguge.Properties.ValueMember = "Key";
            // 
            // folderBrowserDialog1
            // 
            this.folderBrowserDialog1.FileName = "openFileDialog1";
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // DefaultMetaDataFilePath
            // 
            resources.ApplyResources(this.DefaultMetaDataFilePath, "DefaultMetaDataFilePath");
            this.DefaultMetaDataFilePath.Name = "DefaultMetaDataFilePath";
            // 
            // button2
            // 
            resources.ApplyResources(this.button2, "button2");
            this.button2.Name = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // DefaultFilesPath
            // 
            resources.ApplyResources(this.DefaultFilesPath, "DefaultFilesPath");
            this.DefaultFilesPath.Name = "DefaultFilesPath";
            // 
            // LblSkinName
            // 
            resources.ApplyResources(this.LblSkinName, "LblSkinName");
            this.LblSkinName.Name = "LblSkinName";
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Controls.Add(this.Languge, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.DefaultFilesPath, 1, 10);
            this.tableLayoutPanel1.Controls.Add(this.LblSkinName, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.Save, 1, 12);
            this.tableLayoutPanel1.Controls.Add(this.label2, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.showToolTipControllerCheckEdit, 0, 11);
            this.tableLayoutPanel1.Controls.Add(this.defaulttitleLabel, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.horizontalResolutionLabel, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.showToolTipControllerLabel, 1, 11);
            this.tableLayoutPanel1.Controls.Add(this.verticalResolutionLabel, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.verticalResolutionSpinEdit, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.thumbWidthSpinEdit, 0, 7);
            this.tableLayoutPanel1.Controls.Add(this.DefaultMetaDataFilePath, 1, 9);
            this.tableLayoutPanel1.Controls.Add(this.cmbPlayerType, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.thumbHeightLabel, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.CombLanguge, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.thumbWidthLabel, 1, 7);
            this.tableLayoutPanel1.Controls.Add(this.label1, 1, 8);
            this.tableLayoutPanel1.Controls.Add(this.defaulttitleTextEdit, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.horizontalResolutionSpinEdit, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.thumbHeightSpinEdit, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.txtMetaDataFilePath, 0, 8);
            this.tableLayoutPanel1.Controls.Add(this.TxtEDefaultMetaDetaPath, 0, 9);
            this.tableLayoutPanel1.Controls.Add(this.tetEDefaultfilesPath, 0, 10);
            this.tableLayoutPanel1.Controls.Add(this.standaloneBarDockControl1, 0, 2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // txtMetaDataFilePath
            // 
            this.txtMetaDataFilePath.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "MetaDataPath", true));
            resources.ApplyResources(this.txtMetaDataFilePath, "txtMetaDataFilePath");
            this.txtMetaDataFilePath.Name = "txtMetaDataFilePath";
            this.txtMetaDataFilePath.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.txtMetaDataFilePath.Click += new System.EventHandler(this.txtMetaDataFilePath_Click_1);
            // 
            // TxtEDefaultMetaDetaPath
            // 
            this.TxtEDefaultMetaDetaPath.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "DefaulMetaDataPath", true));
            resources.ApplyResources(this.TxtEDefaultMetaDetaPath, "TxtEDefaultMetaDetaPath");
            this.TxtEDefaultMetaDetaPath.Name = "TxtEDefaultMetaDetaPath";
            this.TxtEDefaultMetaDetaPath.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.TxtEDefaultMetaDetaPath.Click += new System.EventHandler(this.textEdit1_Click);
            // 
            // tetEDefaultfilesPath
            // 
            this.tetEDefaultfilesPath.DataBindings.Add(new System.Windows.Forms.Binding("EditValue", this.appSettingBindingSource, "DefaulFilesPath", true));
            resources.ApplyResources(this.tetEDefaultfilesPath, "tetEDefaultfilesPath");
            this.tetEDefaultfilesPath.Name = "tetEDefaultfilesPath";
            this.tetEDefaultfilesPath.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.tetEDefaultfilesPath.Click += new System.EventHandler(this.tetEDefaultfilesPath_Click);
            // 
            // standaloneBarDockControl1
            // 
            this.standaloneBarDockControl1.CausesValidation = false;
            resources.ApplyResources(this.standaloneBarDockControl1, "standaloneBarDockControl1");
            this.standaloneBarDockControl1.Name = "standaloneBarDockControl1";
            // 
            // barManager1
            // 
            this.barManager1.Bars.AddRange(new DevExpress.XtraBars.Bar[] {
            this.bar1});
            this.barManager1.DockControls.Add(this.barDockControlTop);
            this.barManager1.DockControls.Add(this.barDockControlBottom);
            this.barManager1.DockControls.Add(this.barDockControlLeft);
            this.barManager1.DockControls.Add(this.barDockControlRight);
            this.barManager1.DockControls.Add(this.standaloneBarDockControl1);
            this.barManager1.Form = this;
            this.barManager1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.SkinMenu});
            this.barManager1.MaxItemId = 1;
            // 
            // bar1
            // 
            this.bar1.BarName = "Tools";
            this.bar1.DockCol = 0;
            this.bar1.DockRow = 0;
            this.bar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Standalone;
            this.bar1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.SkinMenu)});
            this.bar1.OptionsBar.AllowCollapse = true;
            this.bar1.OptionsBar.AllowQuickCustomization = false;
            this.bar1.OptionsBar.DisableClose = true;
            this.bar1.OptionsBar.DisableCustomization = true;
            this.bar1.OptionsBar.DrawBorder = false;
            this.bar1.OptionsBar.DrawDragBorder = false;
            this.bar1.OptionsBar.MultiLine = true;
            this.bar1.OptionsBar.RotateWhenVertical = false;
            this.bar1.OptionsBar.UseWholeRow = true;
            this.bar1.StandaloneBarDockControl = this.standaloneBarDockControl1;
            resources.ApplyResources(this.bar1, "bar1");
            // 
            // SkinMenu
            // 
            this.SkinMenu.Alignment = DevExpress.XtraBars.BarItemLinkAlignment.Right;
            this.SkinMenu.Id = 0;
            this.SkinMenu.Name = "SkinMenu";
            // 
            // barDockControlTop
            // 
            this.barDockControlTop.CausesValidation = false;
            resources.ApplyResources(this.barDockControlTop, "barDockControlTop");
            // 
            // barDockControlBottom
            // 
            this.barDockControlBottom.CausesValidation = false;
            resources.ApplyResources(this.barDockControlBottom, "barDockControlBottom");
            // 
            // barDockControlLeft
            // 
            this.barDockControlLeft.CausesValidation = false;
            resources.ApplyResources(this.barDockControlLeft, "barDockControlLeft");
            // 
            // barDockControlRight
            // 
            this.barDockControlRight.CausesValidation = false;
            resources.ApplyResources(this.barDockControlRight, "barDockControlRight");
            // 
            // SettingForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnFolderBrowser);
            this.Controls.Add(this.barDockControlLeft);
            this.Controls.Add(this.barDockControlRight);
            this.Controls.Add(this.barDockControlBottom);
            this.Controls.Add(this.barDockControlTop);
            this.Name = "SettingForm";
            this.Load += new System.EventHandler(this.SettingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.cmbPlayerType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.appSettingBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.defaulttitleTextEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.horizontalResolutionSpinEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.showToolTipControllerCheckEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbHeightSpinEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbWidthSpinEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.verticalResolutionSpinEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CombLanguge.Properties)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtMetaDataFilePath.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TxtEDefaultMetaDetaPath.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tetEDefaultfilesPath.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.TextEdit defaulttitleTextEdit;
        private System.Windows.Forms.BindingSource appSettingBindingSource;
        private DevExpress.XtraEditors.SpinEdit horizontalResolutionSpinEdit;
        private DevExpress.XtraEditors.CheckEdit showToolTipControllerCheckEdit;
        private DevExpress.XtraEditors.SpinEdit thumbHeightSpinEdit;
        private DevExpress.XtraEditors.SpinEdit thumbWidthSpinEdit;
        private DevExpress.XtraEditors.SpinEdit verticalResolutionSpinEdit;
        private DevExpress.XtraEditors.LookUpEdit CombLanguge;
        private System.Windows.Forms.Button Save;
        private System.Windows.Forms.Button btnFolderBrowser;
        private DevExpress.XtraEditors.LookUpEdit cmbPlayerType;
        private System.Windows.Forms.OpenFileDialog folderBrowserDialog1;
        private System.Windows.Forms.Label defaulttitleLabel;
        private System.Windows.Forms.Label horizontalResolutionLabel;
        private System.Windows.Forms.Label showToolTipControllerLabel;
        private System.Windows.Forms.Label thumbHeightLabel;
        private System.Windows.Forms.Label thumbWidthLabel;
        private System.Windows.Forms.Label verticalResolutionLabel;
        private System.Windows.Forms.Label Languge;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label DefaultMetaDataFilePath;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label DefaultFilesPath;
        private System.Windows.Forms.Label LblSkinName;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private DevExpress.XtraEditors.ButtonEdit txtMetaDataFilePath;
        private DevExpress.XtraEditors.ButtonEdit TxtEDefaultMetaDetaPath;
        private DevExpress.XtraEditors.ButtonEdit tetEDefaultfilesPath;
        private DevExpress.XtraBars.StandaloneBarDockControl standaloneBarDockControl1;
        private DevExpress.XtraBars.BarManager barManager1;
        private DevExpress.XtraBars.Bar bar1;
        private DevExpress.XtraBars.BarSubItem SkinMenu;
        private DevExpress.XtraBars.BarDockControl barDockControlTop;
        private DevExpress.XtraBars.BarDockControl barDockControlBottom;
        private DevExpress.XtraBars.BarDockControl barDockControlLeft;
        private DevExpress.XtraBars.BarDockControl barDockControlRight;
    }
}