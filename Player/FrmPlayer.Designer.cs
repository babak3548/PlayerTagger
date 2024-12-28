namespace Player
{
    partial class FrmPlayer
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmPlayer));
            this.uiPanelManager1 = new Janus.Windows.UI.Dock.UIPanelManager(this.components);
            this.uiPMain = new Janus.Windows.UI.Dock.UIPanelGroup();
            this.uiPB = new Janus.Windows.UI.Dock.UIPanel();
            this.uiPBContainer = new Janus.Windows.UI.Dock.UIPanelInnerContainer();
            this.PlayerControl = new AxWMPLib.AxWindowsMediaPlayer();
            this.uiPT = new Janus.Windows.UI.Dock.UIPanel();
            this.uiPTContainer = new Janus.Windows.UI.Dock.UIPanelInnerContainer();
            this.vGridControl1 = new DevExpress.XtraVerticalGrid.VGridControl();
            this.MediabindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.repositoryItemMemoExEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit();
            this.repositoryItemPictureEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.rowPosition = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowThumbnailSource = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowThumbnailImage = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowTitle = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowDescription = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.uiStatusBar1 = new Janus.Windows.UI.StatusBar.UIStatusBar();
            this.uiCommandManager1 = new Janus.Windows.UI.CommandBars.UICommandManager(this.components);
            this.BottomRebar1 = new Janus.Windows.UI.CommandBars.UIRebar();
            this.Command0 = new Janus.Windows.UI.CommandBars.UICommand("Command0");
            this.LeftRebar1 = new Janus.Windows.UI.CommandBars.UIRebar();
            this.RightRebar1 = new Janus.Windows.UI.CommandBars.UIRebar();
            this.TopRebar1 = new Janus.Windows.UI.CommandBars.UIRebar();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CmdOpenFile = new System.Windows.Forms.ToolStripMenuItem();
            this.bookMarkToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenFile = new System.Windows.Forms.OpenFileDialog();
            //this.axVLCPlugin21 = new AxAXVLC.AxVLCPlugin2();
            ((System.ComponentModel.ISupportInitialize)(this.uiPanelManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiPMain)).BeginInit();
            this.uiPMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.uiPB)).BeginInit();
            this.uiPB.SuspendLayout();
            this.uiPBContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerControl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiPT)).BeginInit();
            this.uiPT.SuspendLayout();
            this.uiPTContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.vGridControl1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MediabindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiCommandManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BottomRebar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LeftRebar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RightRebar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TopRebar1)).BeginInit();
            this.menuStrip.SuspendLayout();
            //((System.ComponentModel.ISupportInitialize)(this.axVLCPlugin21)).BeginInit();
            this.SuspendLayout();
            // 
            // uiPanelManager1
            // 
            this.uiPanelManager1.ContainerControl = this;
            this.uiPanelManager1.VisualStyle = Janus.Windows.UI.Dock.PanelVisualStyle.Office2007;
            this.uiPMain.Id = new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b");
            this.uiPMain.StaticGroup = true;
            this.uiPB.Id = new System.Guid("6971d79e-98c7-4bb8-9956-89a0cc764d56");
            this.uiPMain.Panels.Add(this.uiPB);
            this.uiPT.Id = new System.Guid("9426972a-0276-4f4d-9d84-227fcd574ba9");
            this.uiPMain.Panels.Add(this.uiPT);
            this.uiPanelManager1.Panels.Add(this.uiPMain);
            // 
            // Design Time Panel Info:
            // 
            this.uiPanelManager1.BeginPanelInfo();
            this.uiPanelManager1.AddDockPanelInfo(new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), Janus.Windows.UI.Dock.PanelGroupStyle.HorizontalTiles, Janus.Windows.UI.Dock.PanelDockStyle.Fill, true, new System.Drawing.Size(678, 525), true);
            this.uiPanelManager1.AddDockPanelInfo(new System.Guid("6971d79e-98c7-4bb8-9956-89a0cc764d56"), new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), 372, true);
            this.uiPanelManager1.AddDockPanelInfo(new System.Guid("9426972a-0276-4f4d-9d84-227fcd574ba9"), new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), 149, true);
            this.uiPanelManager1.AddFloatingPanelInfo(new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), Janus.Windows.UI.Dock.PanelGroupStyle.HorizontalTiles, true, new System.Drawing.Point(150, 150), new System.Drawing.Size(200, 200), false);
            this.uiPanelManager1.AddFloatingPanelInfo(new System.Guid("6971d79e-98c7-4bb8-9956-89a0cc764d56"), new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), 249, false);
            this.uiPanelManager1.AddFloatingPanelInfo(new System.Guid("9426972a-0276-4f4d-9d84-227fcd574ba9"), new System.Guid("23adf56e-f45e-45f6-bdb3-16b1667c568b"), 249, false);
            this.uiPanelManager1.EndPanelInfo();
            // 
            // uiPMain
            // 
            this.uiPMain.CaptionVisible = Janus.Windows.UI.InheritableBoolean.False;
            this.uiPMain.CloseButtonVisible = Janus.Windows.UI.InheritableBoolean.False;
            this.uiPMain.FloatingLocation = new System.Drawing.Point(150, 150);
            this.uiPMain.Location = new System.Drawing.Point(3, 27);
            this.uiPMain.Name = "uiPMain";
            this.uiPMain.Size = new System.Drawing.Size(678, 525);
            this.uiPMain.TabIndex = 4;
            // 
            // uiPB
            // 
            this.uiPB.InnerContainer = this.uiPBContainer;
            this.uiPB.Location = new System.Drawing.Point(0, 0);
            this.uiPB.Name = "uiPB";
            this.uiPB.Size = new System.Drawing.Size(678, 372);
            this.uiPB.TabIndex = 4;
            // 
            // uiPBContainer
            // 
            //this.uiPBContainer.Controls.Add(this.axVLCPlugin21);
            this.uiPBContainer.Controls.Add(this.PlayerControl);
            this.uiPBContainer.Location = new System.Drawing.Point(1, 23);
            this.uiPBContainer.Name = "uiPBContainer";
            this.uiPBContainer.Size = new System.Drawing.Size(676, 348);
            this.uiPBContainer.TabIndex = 0;
            // 
            // PlayerControl
            // 
            this.PlayerControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PlayerControl.Enabled = true;
            this.PlayerControl.Location = new System.Drawing.Point(0, 0);
            this.PlayerControl.Name = "PlayerControl";
            this.PlayerControl.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("PlayerControl.OcxState")));
            this.PlayerControl.Size = new System.Drawing.Size(676, 348);
            this.PlayerControl.TabIndex = 0;
            // 
            // uiPT
            // 
            this.uiPT.InnerContainer = this.uiPTContainer;
            this.uiPT.Location = new System.Drawing.Point(0, 376);
            this.uiPT.Name = "uiPT";
            this.uiPT.Size = new System.Drawing.Size(678, 149);
            this.uiPT.TabIndex = 4;
            // 
            // uiPTContainer
            // 
            this.uiPTContainer.Controls.Add(this.vGridControl1);
            this.uiPTContainer.Location = new System.Drawing.Point(1, 23);
            this.uiPTContainer.Name = "uiPTContainer";
            this.uiPTContainer.Size = new System.Drawing.Size(676, 125);
            this.uiPTContainer.TabIndex = 0;
            // 
            // vGridControl1
            // 
            this.vGridControl1.DataSource = this.MediabindingSource;
            this.vGridControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.vGridControl1.Location = new System.Drawing.Point(0, 0);
            this.vGridControl1.LookAndFeel.SkinName = "Blue";
            this.vGridControl1.LookAndFeel.UseDefaultLookAndFeel = false;
            this.vGridControl1.Name = "vGridControl1";
            this.vGridControl1.OptionsBehavior.DragRowHeaders = true;
            this.vGridControl1.OptionsView.ShowEmptyRowImage = true;
            this.vGridControl1.OptionsView.ShowRows = false;
            this.vGridControl1.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemMemoExEdit1,
            this.repositoryItemPictureEdit1});
            this.vGridControl1.Rows.AddRange(new DevExpress.XtraVerticalGrid.Rows.BaseRow[] {
            this.rowPosition,
            this.rowThumbnailSource,
            this.rowThumbnailImage,
            this.rowTitle,
            this.rowDescription});
            this.vGridControl1.Size = new System.Drawing.Size(676, 125);
            this.vGridControl1.TabIndex = 0;
            // 
            // repositoryItemMemoExEdit1
            // 
            this.repositoryItemMemoExEdit1.AutoHeight = false;
            this.repositoryItemMemoExEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemMemoExEdit1.Name = "repositoryItemMemoExEdit1";
            // 
            // repositoryItemPictureEdit1
            // 
            this.repositoryItemPictureEdit1.Name = "repositoryItemPictureEdit1";
            this.repositoryItemPictureEdit1.DoubleClick += new System.EventHandler(this.repositoryItemPictureEdit1_DoubleClick_1);
            // 
            // rowPosition
            // 
            this.rowPosition.Name = "rowPosition";
            this.rowPosition.Properties.Caption = "Position";
            this.rowPosition.Properties.FieldName = "Position";
            this.rowPosition.Visible = false;
            // 
            // rowThumbnailSource
            // 
            this.rowThumbnailSource.Name = "rowThumbnailSource";
            this.rowThumbnailSource.Properties.Caption = "Thumbnail Source";
            this.rowThumbnailSource.Properties.FieldName = "ThumbnailSource";
            this.rowThumbnailSource.Visible = false;
            // 
            // rowThumbnailImage
            // 
            this.rowThumbnailImage.Name = "rowThumbnailImage";
            this.rowThumbnailImage.Properties.Caption = "Thumbnail Image";
            this.rowThumbnailImage.Properties.FieldName = "ThumbnailImage";
            this.rowThumbnailImage.Properties.ReadOnly = true;
            this.rowThumbnailImage.Properties.RowEdit = this.repositoryItemPictureEdit1;
            // 
            // rowTitle
            // 
            this.rowTitle.Name = "rowTitle";
            this.rowTitle.Properties.Caption = "Title";
            this.rowTitle.Properties.FieldName = "Title";
            // 
            // rowDescription
            // 
            this.rowDescription.Name = "rowDescription";
            this.rowDescription.Properties.Caption = "Description";
            this.rowDescription.Properties.FieldName = "Description";
            this.rowDescription.Properties.RowEdit = this.repositoryItemMemoExEdit1;
            // 
            // uiStatusBar1
            // 
            this.uiStatusBar1.Location = new System.Drawing.Point(0, 555);
            this.uiStatusBar1.Name = "uiStatusBar1";
            this.uiStatusBar1.Size = new System.Drawing.Size(684, 23);
            this.uiStatusBar1.TabIndex = 5;
            this.uiStatusBar1.VisualStyle = Janus.Windows.UI.VisualStyle.Office2007;
            // 
            // uiCommandManager1
            // 
            this.uiCommandManager1.BottomRebar = this.BottomRebar1;
            this.uiCommandManager1.Commands.AddRange(new Janus.Windows.UI.CommandBars.UICommand[] {
            this.Command0});
            this.uiCommandManager1.ContainerControl = this;
            this.uiCommandManager1.Id = new System.Guid("74d4454e-ab1f-4987-933c-5cd6f508bfc5");
            this.uiCommandManager1.LeftRebar = this.LeftRebar1;
            this.uiCommandManager1.RightRebar = this.RightRebar1;
            this.uiCommandManager1.TopRebar = this.TopRebar1;
            this.uiCommandManager1.CommandClick += new Janus.Windows.UI.CommandBars.CommandEventHandler(this.uiCommandManager1_CommandClick);
            // 
            // BottomRebar1
            // 
            this.BottomRebar1.CommandManager = this.uiCommandManager1;
            this.BottomRebar1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.BottomRebar1.Location = new System.Drawing.Point(0, 555);
            this.BottomRebar1.Name = "BottomRebar1";
            this.BottomRebar1.Size = new System.Drawing.Size(684, 0);
            // 
            // Command0
            // 
            this.Command0.Key = "Command0";
            this.Command0.Name = "Command0";
            this.Command0.Shortcut = System.Windows.Forms.Shortcut.CtrlB;
            // 
            // LeftRebar1
            // 
            this.LeftRebar1.CommandManager = this.uiCommandManager1;
            this.LeftRebar1.Dock = System.Windows.Forms.DockStyle.Left;
            this.LeftRebar1.Location = new System.Drawing.Point(0, 24);
            this.LeftRebar1.Name = "LeftRebar1";
            this.LeftRebar1.Size = new System.Drawing.Size(0, 554);
            // 
            // RightRebar1
            // 
            this.RightRebar1.CommandManager = this.uiCommandManager1;
            this.RightRebar1.Dock = System.Windows.Forms.DockStyle.Right;
            this.RightRebar1.Location = new System.Drawing.Point(684, 24);
            this.RightRebar1.Name = "RightRebar1";
            this.RightRebar1.Size = new System.Drawing.Size(0, 554);
            // 
            // TopRebar1
            // 
            this.TopRebar1.CommandManager = this.uiCommandManager1;
            this.TopRebar1.Dock = System.Windows.Forms.DockStyle.Top;
            this.TopRebar1.Location = new System.Drawing.Point(0, 0);
            this.TopRebar1.Name = "TopRebar1";
            this.TopRebar1.Size = new System.Drawing.Size(684, 0);
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(684, 24);
            this.menuStrip.TabIndex = 10;
            this.menuStrip.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CmdOpenFile,
            this.bookMarkToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // CmdOpenFile
            // 
            this.CmdOpenFile.Name = "CmdOpenFile";
            this.CmdOpenFile.Size = new System.Drawing.Size(169, 22);
            this.CmdOpenFile.Text = "Open";
            this.CmdOpenFile.Click += new System.EventHandler(this.CmdOpenFile_Click);
            // 
            // bookMarkToolStripMenuItem
            // 
            this.bookMarkToolStripMenuItem.Name = "bookMarkToolStripMenuItem";
            this.bookMarkToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.B)));
            this.bookMarkToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.bookMarkToolStripMenuItem.Text = "BookMark";
            this.bookMarkToolStripMenuItem.Click += new System.EventHandler(this.bookMarkToolStripMenuItem_Click);
            // 
            // OpenFile
            // 
            this.OpenFile.FileName = "openFileDialog1";
            // 
            // axVLCPlugin21
            // 
            //this.axVLCPlugin21.Enabled = true;
            //this.axVLCPlugin21.Location = new System.Drawing.Point(459, 54);
            //this.axVLCPlugin21.Name = "axVLCPlugin21";
            //this.axVLCPlugin21.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axVLCPlugin21.OcxState")));
            //this.axVLCPlugin21.Size = new System.Drawing.Size(175, 188);
            //this.axVLCPlugin21.TabIndex = 1;
            // 
            // FrmPlayer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 578);
            this.Controls.Add(this.uiPMain);
            this.Controls.Add(this.BottomRebar1);
            this.Controls.Add(this.uiStatusBar1);
            this.Controls.Add(this.LeftRebar1);
            this.Controls.Add(this.RightRebar1);
            this.Controls.Add(this.menuStrip);
            this.Controls.Add(this.TopRebar1);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "FrmPlayer";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmPlayer_FormClosing);
            this.Load += new System.EventHandler(this.FrmPlayer_Load);
            ((System.ComponentModel.ISupportInitialize)(this.uiPanelManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiPMain)).EndInit();
            this.uiPMain.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.uiPB)).EndInit();
            this.uiPB.ResumeLayout(false);
            this.uiPBContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.PlayerControl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiPT)).EndInit();
            this.uiPT.ResumeLayout(false);
            this.uiPTContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.vGridControl1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MediabindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.uiCommandManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BottomRebar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LeftRebar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RightRebar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TopRebar1)).EndInit();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            //((System.ComponentModel.ISupportInitialize)(this.axVLCPlugin21)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Janus.Windows.UI.Dock.UIPanelManager uiPanelManager1;
        private Janus.Windows.UI.Dock.UIPanelGroup uiPMain;
        private Janus.Windows.UI.Dock.UIPanel uiPB;
        private Janus.Windows.UI.Dock.UIPanelInnerContainer uiPBContainer;
        private AxWMPLib.AxWindowsMediaPlayer PlayerControl;
        private Janus.Windows.UI.Dock.UIPanel uiPT;
        private Janus.Windows.UI.Dock.UIPanelInnerContainer uiPTContainer;
        private Janus.Windows.UI.StatusBar.UIStatusBar uiStatusBar1;
        private Janus.Windows.UI.CommandBars.UIRebar BottomRebar1;
        private Janus.Windows.UI.CommandBars.UICommandManager uiCommandManager1;
        private Janus.Windows.UI.CommandBars.UIRebar LeftRebar1;
        private Janus.Windows.UI.CommandBars.UIRebar RightRebar1;
        private Janus.Windows.UI.CommandBars.UIRebar TopRebar1;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem CmdOpenFile;
        private System.Windows.Forms.OpenFileDialog OpenFile;
        private System.Windows.Forms.ToolStripMenuItem bookMarkToolStripMenuItem;
        private System.Windows.Forms.BindingSource MediabindingSource;
        private DevExpress.XtraVerticalGrid.VGridControl vGridControl1;
      
        private Janus.Windows.UI.CommandBars.UICommand Command0;
        private DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit repositoryItemMemoExEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit repositoryItemPictureEdit1;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowPosition;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowThumbnailSource;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowThumbnailImage;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowTitle;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowDescription;
      //  private AxAXVLC.AxVLCPlugin2 axVLCPlugin21;

    }
}

