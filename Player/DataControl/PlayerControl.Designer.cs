namespace Player.DataControl
{
   public  partial class PlayerControl
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlayerControl));
            this.repositoryItemTrackBar3 = new DevExpress.XtraEditors.Repository.RepositoryItemTrackBar();
            this.barManager1 = new DevExpress.XtraBars.BarManager(this.components);
            this.bar1 = new DevExpress.XtraBars.Bar();
            this.playItem = new DevExpress.XtraBars.BarButtonItem();
            this.barBtnStop = new DevExpress.XtraBars.BarButtonItem();
            this.PreviousFrame = new DevExpress.XtraBars.BarButtonItem();
            this.NextFrame = new DevExpress.XtraBars.BarButtonItem();
            this.SlowPlay = new DevExpress.XtraBars.BarButtonItem();
            this.NormalPlay = new DevExpress.XtraBars.BarButtonItem();
            this.FasterPlay = new DevExpress.XtraBars.BarButtonItem();
            this.CmdTrkVolume = new DevExpress.XtraBars.BarEditItem();
            this.TrkVolumeRepository = new DevExpress.XtraEditors.Repository.RepositoryItemTrackBar();
            this.Mute1 = new DevExpress.XtraBars.BarButtonItem();
            this.barLblCurrentTime = new DevExpress.XtraBars.BarStaticItem();
            this.barLblTootalTime = new DevExpress.XtraBars.BarStaticItem();
            this.barStaticPosition = new DevExpress.XtraBars.BarStaticItem();
            this.FullScereen = new DevExpress.XtraBars.BarButtonItem();
            this.standaloneBarDockControl1 = new DevExpress.XtraBars.StandaloneBarDockControl();
            this.barDockControlTop = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlBottom = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlLeft = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlRight = new DevExpress.XtraBars.BarDockControl();
            this.imageCollectionPlayer = new DevExpress.Utils.ImageCollection(this.components);
            this.barBtnPuse = new DevExpress.XtraBars.BarButtonItem();
            this.barBtnShut = new DevExpress.XtraBars.BarButtonItem();
            this.barButtonItem2 = new DevExpress.XtraBars.BarButtonItem();
            this.barEditItem2 = new DevExpress.XtraBars.BarEditItem();
            this.barBtnPlay = new DevExpress.XtraBars.BarButtonItem();
            this.repositoryItemTrackBar1 = new DevExpress.XtraEditors.Repository.RepositoryItemTrackBar();
            this.repositoryItemSpinEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit();
            this.PlayerRate = new DevExpress.XtraBars.BarEditItem();
            this.barEditItem1 = new DevExpress.XtraBars.BarEditItem();
            this.trkPosition = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTrackBar3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollectionPlayer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTrackBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemSpinEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).BeginInit();
            this.SuspendLayout();
            // 
            // repositoryItemTrackBar3
            // 
            this.repositoryItemTrackBar3.LookAndFeel.SkinName = "Office 2010 Blue";
            this.repositoryItemTrackBar3.Name = "repositoryItemTrackBar3";
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
            this.barManager1.Images = this.imageCollectionPlayer;
            this.barManager1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.barBtnPuse,
            this.barBtnStop,
            this.barBtnShut,
            this.NextFrame,
            this.barButtonItem2,
            this.NormalPlay,
            this.FasterPlay,
            this.PreviousFrame,
            this.SlowPlay,
            this.barEditItem2,
            this.CmdTrkVolume,
            this.barBtnPlay,
            this.barLblCurrentTime,
            this.barLblTootalTime,
            this.barStaticPosition,
            this.FullScereen,
            this.Mute1,
            this.playItem});
            this.barManager1.MaxItemId = 22;
            this.barManager1.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemTrackBar1,
            this.TrkVolumeRepository,
            this.repositoryItemSpinEdit1});
            // 
            // bar1
            // 
            this.bar1.BarName = "Tools";
            this.bar1.CanDockStyle = DevExpress.XtraBars.BarCanDockStyle.Standalone;
            this.bar1.DockCol = 0;
            this.bar1.DockRow = 0;
            this.bar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Standalone;
            this.bar1.FloatLocation = new System.Drawing.Point(0, 40);
            this.bar1.FloatSize = new System.Drawing.Size(0, 40);
            this.bar1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.playItem, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.barBtnStop),
            new DevExpress.XtraBars.LinkPersistInfo(this.PreviousFrame),
            new DevExpress.XtraBars.LinkPersistInfo(this.NextFrame),
            new DevExpress.XtraBars.LinkPersistInfo(this.SlowPlay, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.NormalPlay),
            new DevExpress.XtraBars.LinkPersistInfo(this.FasterPlay),
            new DevExpress.XtraBars.LinkPersistInfo(this.CmdTrkVolume, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.Mute1),
            new DevExpress.XtraBars.LinkPersistInfo(this.barLblCurrentTime, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.barLblTootalTime),
            new DevExpress.XtraBars.LinkPersistInfo(this.barStaticPosition),
            new DevExpress.XtraBars.LinkPersistInfo(this.FullScereen)});
            this.bar1.OptionsBar.AllowQuickCustomization = false;
            this.bar1.OptionsBar.DisableClose = true;
            this.bar1.OptionsBar.DisableCustomization = true;
            this.bar1.OptionsBar.DrawDragBorder = false;
            this.bar1.OptionsBar.MultiLine = true;
            this.bar1.OptionsBar.RotateWhenVertical = false;
            this.bar1.OptionsBar.UseWholeRow = true;
            this.bar1.StandaloneBarDockControl = this.standaloneBarDockControl1;
            resources.ApplyResources(this.bar1, "bar1");
            // 
            // playItem
            // 
            this.playItem.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.playItem, "playItem");
            this.playItem.Down = true;
            this.playItem.GroupIndex = 1;
            this.playItem.Id = 21;
            this.playItem.ImageIndex = 1;
            this.playItem.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.Space));
            this.playItem.Name = "playItem";
            this.playItem.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.playItem_ItemClick);
            // 
            // barBtnStop
            // 
            this.barBtnStop.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.barBtnStop, "barBtnStop");
            this.barBtnStop.GroupIndex = 1;
            this.barBtnStop.Id = 2;
            this.barBtnStop.ImageIndex = 2;
            this.barBtnStop.Name = "barBtnStop";
            this.barBtnStop.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.barBtnStop_ItemClick);
            // 
            // PreviousFrame
            // 
            this.PreviousFrame.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.PreviousFrame, "PreviousFrame");
            this.PreviousFrame.GroupIndex = 1;
            this.PreviousFrame.Id = 9;
            this.PreviousFrame.ImageIndex = 4;
            this.PreviousFrame.Name = "PreviousFrame";
            this.PreviousFrame.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            this.PreviousFrame.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.PreviousFrame_ItemClick);
            // 
            // NextFrame
            // 
            this.NextFrame.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.NextFrame, "NextFrame");
            this.NextFrame.GroupIndex = 1;
            this.NextFrame.Id = 5;
            this.NextFrame.ImageIndex = 3;
            this.NextFrame.Name = "NextFrame";
            this.NextFrame.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.NextFrame_ItemClick);
            // 
            // SlowPlay
            // 
            this.SlowPlay.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.SlowPlay, "SlowPlay");
            this.SlowPlay.GroupIndex = 2;
            this.SlowPlay.Id = 10;
            this.SlowPlay.ImageIndex = 5;
            this.SlowPlay.Name = "SlowPlay";
            this.SlowPlay.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.SlowPlay_ItemClick);
            // 
            // NormalPlay
            // 
            this.NormalPlay.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.NormalPlay, "NormalPlay");
            this.NormalPlay.Down = true;
            this.NormalPlay.GroupIndex = 2;
            this.NormalPlay.Id = 7;
            this.NormalPlay.ImageIndex = 6;
            this.NormalPlay.Name = "NormalPlay";
            this.NormalPlay.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.NormalPlay_ItemClick);
            // 
            // FasterPlay
            // 
            this.FasterPlay.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.FasterPlay, "FasterPlay");
            this.FasterPlay.GroupIndex = 2;
            this.FasterPlay.Id = 8;
            this.FasterPlay.ImageIndex = 7;
            this.FasterPlay.Name = "FasterPlay";
            this.FasterPlay.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.FasterPlay_ItemClick);
            // 
            // CmdTrkVolume
            // 
            resources.ApplyResources(this.CmdTrkVolume, "CmdTrkVolume");
            this.CmdTrkVolume.Edit = this.TrkVolumeRepository;
            this.CmdTrkVolume.EditValue = ((short)(100));
            this.CmdTrkVolume.Id = 12;
            this.CmdTrkVolume.Name = "CmdTrkVolume";
            // 
            // TrkVolumeRepository
            // 
            this.TrkVolumeRepository.AllowHtmlDraw = DevExpress.Utils.DefaultBoolean.True;
            this.TrkVolumeRepository.EditValueChangedDelay = 1;
            this.TrkVolumeRepository.Maximum = 200;
            this.TrkVolumeRepository.Name = "TrkVolumeRepository";
            this.TrkVolumeRepository.ShowValueToolTip = true;
            // 
            // Mute1
            // 
            resources.ApplyResources(this.Mute1, "Mute1");
            this.Mute1.Id = 19;
            this.Mute1.ImageIndex = 8;
            this.Mute1.Name = "Mute1";
            this.Mute1.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.Mute1_ItemClick);
            // 
            // barLblCurrentTime
            // 
            resources.ApplyResources(this.barLblCurrentTime, "barLblCurrentTime");
            this.barLblCurrentTime.Id = 14;
            this.barLblCurrentTime.ItemAppearance.Normal.ForeColor = ((System.Drawing.Color)(resources.GetObject("barLblCurrentTime.ItemAppearance.Normal.ForeColor")));
            this.barLblCurrentTime.ItemAppearance.Normal.Options.UseForeColor = true;
            this.barLblCurrentTime.Name = "barLblCurrentTime";
            this.barLblCurrentTime.TextAlignment = System.Drawing.StringAlignment.Near;
            // 
            // barLblTootalTime
            // 
            resources.ApplyResources(this.barLblTootalTime, "barLblTootalTime");
            this.barLblTootalTime.Id = 15;
            this.barLblTootalTime.ItemAppearance.Normal.ForeColor = ((System.Drawing.Color)(resources.GetObject("barLblTootalTime.ItemAppearance.Normal.ForeColor")));
            this.barLblTootalTime.ItemAppearance.Normal.Options.UseForeColor = true;
            this.barLblTootalTime.Name = "barLblTootalTime";
            this.barLblTootalTime.TextAlignment = System.Drawing.StringAlignment.Near;
            // 
            // barStaticPosition
            // 
            resources.ApplyResources(this.barStaticPosition, "barStaticPosition");
            this.barStaticPosition.Id = 16;
            this.barStaticPosition.ItemAppearance.Normal.ForeColor = ((System.Drawing.Color)(resources.GetObject("barStaticPosition.ItemAppearance.Normal.ForeColor")));
            this.barStaticPosition.ItemAppearance.Normal.Options.UseForeColor = true;
            this.barStaticPosition.Name = "barStaticPosition";
            this.barStaticPosition.TextAlignment = System.Drawing.StringAlignment.Near;
            this.barStaticPosition.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // FullScereen
            // 
            resources.ApplyResources(this.FullScereen, "FullScereen");
            this.FullScereen.Id = 18;
            this.FullScereen.ImageIndex = 11;
            this.FullScereen.ItemAppearance.Normal.ForeColor = ((System.Drawing.Color)(resources.GetObject("FullScereen.ItemAppearance.Normal.ForeColor")));
            this.FullScereen.ItemAppearance.Normal.Options.UseForeColor = true;
            this.FullScereen.Name = "FullScereen";
            this.FullScereen.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            this.FullScereen.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.FullScereen_ItemClick);
            // 
            // standaloneBarDockControl1
            // 
            this.standaloneBarDockControl1.CausesValidation = false;
            resources.ApplyResources(this.standaloneBarDockControl1, "standaloneBarDockControl1");
            this.standaloneBarDockControl1.Name = "standaloneBarDockControl1";
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
            // imageCollectionPlayer
            // 
            resources.ApplyResources(this.imageCollectionPlayer, "imageCollectionPlayer");
            this.imageCollectionPlayer.ImageStream = ((DevExpress.Utils.ImageCollectionStreamer)(resources.GetObject("imageCollectionPlayer.ImageStream")));
            this.imageCollectionPlayer.Images.SetKeyName(0, "01-Play.png");
            this.imageCollectionPlayer.Images.SetKeyName(1, "02-Pause.png");
            this.imageCollectionPlayer.Images.SetKeyName(2, "03-Stop.png");
            this.imageCollectionPlayer.Images.SetKeyName(3, "04-Next.png");
            this.imageCollectionPlayer.Images.SetKeyName(4, "05-Pre.png");
            this.imageCollectionPlayer.Images.SetKeyName(5, "06-Slow.png");
            this.imageCollectionPlayer.Images.SetKeyName(6, "07-Normal_Speed.png");
            this.imageCollectionPlayer.Images.SetKeyName(7, "08-Fast.png");
            this.imageCollectionPlayer.Images.SetKeyName(8, "09-Mute.png");
            this.imageCollectionPlayer.Images.SetKeyName(9, "Mute.png");
            // 
            // barBtnPuse
            // 
            this.barBtnPuse.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.barBtnPuse, "barBtnPuse");
            this.barBtnPuse.GroupIndex = 1;
            this.barBtnPuse.Id = 1;
            this.barBtnPuse.ImageIndex = 1;
            this.barBtnPuse.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Space));
            this.barBtnPuse.Name = "barBtnPuse";
            this.barBtnPuse.PaintStyle = DevExpress.XtraBars.BarItemPaintStyle.CaptionInMenu;
            this.barBtnPuse.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            this.barBtnPuse.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.barBtnPuse_ItemClick);
            // 
            // barBtnShut
            // 
            resources.ApplyResources(this.barBtnShut, "barBtnShut");
            this.barBtnShut.Id = 3;
            this.barBtnShut.Name = "barBtnShut";
            // 
            // barButtonItem2
            // 
            resources.ApplyResources(this.barButtonItem2, "barButtonItem2");
            this.barButtonItem2.Id = 6;
            this.barButtonItem2.Name = "barButtonItem2";
            // 
            // barEditItem2
            // 
            resources.ApplyResources(this.barEditItem2, "barEditItem2");
            this.barEditItem2.Edit = this.repositoryItemTrackBar3;
            this.barEditItem2.Id = 11;
            this.barEditItem2.Name = "barEditItem2";
            // 
            // barBtnPlay
            // 
            this.barBtnPlay.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            resources.ApplyResources(this.barBtnPlay, "barBtnPlay");
            this.barBtnPlay.GroupIndex = 1;
            this.barBtnPlay.Id = 13;
            this.barBtnPlay.ImageIndex = 0;
            this.barBtnPlay.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Space));
            this.barBtnPlay.Name = "barBtnPlay";
            this.barBtnPlay.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.barBtnPlay_ItemClick_1);
            // 
            // repositoryItemTrackBar1
            // 
            this.repositoryItemTrackBar1.Name = "repositoryItemTrackBar1";
            // 
            // repositoryItemSpinEdit1
            // 
            resources.ApplyResources(this.repositoryItemSpinEdit1, "repositoryItemSpinEdit1");
            this.repositoryItemSpinEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemSpinEdit1.Name = "repositoryItemSpinEdit1";
            // 
            // PlayerRate
            // 
            resources.ApplyResources(this.PlayerRate, "PlayerRate");
            this.PlayerRate.Edit = null;
            this.PlayerRate.EditValue = 0D;
            this.PlayerRate.Id = 6;
            this.PlayerRate.Name = "PlayerRate";
            // 
            // barEditItem1
            // 
            resources.ApplyResources(this.barEditItem1, "barEditItem1");
            this.barEditItem1.Edit = null;
            this.barEditItem1.EditValue = 0D;
            this.barEditItem1.Id = 6;
            this.barEditItem1.Name = "barEditItem1";
            // 
            // trkPosition
            // 
            this.trkPosition.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(94)))), ((int)(((byte)(94)))), ((int)(((byte)(94)))));
            this.trkPosition.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.trkPosition, "trkPosition");
            this.trkPosition.Maximum = 50000;
            this.trkPosition.Name = "trkPosition";
            this.trkPosition.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // PlayerControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.trkPosition);
            this.Controls.Add(this.standaloneBarDockControl1);
            this.Controls.Add(this.barDockControlLeft);
            this.Controls.Add(this.barDockControlRight);
            this.Controls.Add(this.barDockControlBottom);
            this.Controls.Add(this.barDockControlTop);
            this.Name = "PlayerControl";
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTrackBar3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollectionPlayer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTrackBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemSpinEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraBars.BarButtonItem barBtnShut;
        private DevExpress.XtraBars.BarDockControl barDockControlTop;
        private DevExpress.XtraBars.BarDockControl barDockControlBottom;
        private DevExpress.XtraBars.BarDockControl barDockControlLeft;
        private DevExpress.XtraBars.BarDockControl barDockControlRight;
        private DevExpress.XtraBars.BarButtonItem barButtonItem2;
        private DevExpress.XtraEditors.Repository.RepositoryItemTrackBar repositoryItemTrackBar1;
        public DevExpress.XtraBars.Bar bar1;
        public DevExpress.XtraBars.BarButtonItem PreviousFrame;
        public DevExpress.XtraBars.BarManager barManager1;
        public DevExpress.XtraBars.BarButtonItem NextFrame;
        private DevExpress.XtraBars.BarEditItem PlayerRate;
        private DevExpress.XtraBars.BarEditItem barEditItem1;
        private DevExpress.XtraBars.BarEditItem barEditItem2;
        protected DevExpress.XtraBars.BarEditItem CmdTrkVolume;
        private DevExpress.XtraEditors.Repository.RepositoryItemTrackBar repositoryItemTrackBar3;
        protected DevExpress.XtraEditors.Repository.RepositoryItemTrackBar TrkVolumeRepository;
        protected DevExpress.XtraBars.BarStaticItem barLblCurrentTime;
        protected DevExpress.XtraBars.BarStaticItem barLblTootalTime;
        protected DevExpress.XtraBars.BarStaticItem barStaticPosition;
        public DevExpress.XtraBars.BarButtonItem barBtnPuse;
        public DevExpress.XtraBars.BarButtonItem barBtnStop;
        public DevExpress.XtraBars.BarButtonItem barBtnPlay;
        protected System.Windows.Forms.TrackBar trkPosition;
        protected DevExpress.XtraBars.StandaloneBarDockControl standaloneBarDockControl1;
        protected DevExpress.XtraBars.BarButtonItem NormalPlay;
        protected DevExpress.XtraBars.BarButtonItem FasterPlay;
        protected DevExpress.XtraBars.BarButtonItem SlowPlay;
        public DevExpress.XtraBars.BarButtonItem FullScereen;
        public DevExpress.XtraBars.BarButtonItem Mute1;
        private DevExpress.Utils.ImageCollection imageCollectionPlayer;
        private DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit repositoryItemSpinEdit1;
        public DevExpress.XtraBars.BarButtonItem playItem;
    }
}
