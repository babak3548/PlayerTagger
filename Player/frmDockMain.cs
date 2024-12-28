using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using DevExpress.XtraBars.Docking;
using DevExpress.XtraBars.Docking2010.Views;
using DevExpress.XtraBars.Helpers;
using DevExpress.XtraRichEdit;
using DevExpress.XtraSplashScreen;
using Player.Forms;
using Player.DataControl;
using System.Collections.ObjectModel;
using System.ComponentModel;
using DevExpress.XtraEditors;
using System.Diagnostics;
using System.Collections.Specialized;
using Player.Controls;
using System.Drawing.Imaging;
using System.Linq;
using DevExpress.XtraGrid.Views.Grid;
using VideoEditor;
namespace Player
{
    public partial class frmMain : DevExpress.XtraEditors.XtraForm
    {
        #region Dock    
        public frmMain() {
          
           // SplashScreenManager.ShowImage(SplashScreenImage, true, false);
          
            Properties.Settings settings = new Properties.Settings();
            InitializeComponent();
            WindowState = FormWindowState.Maximized;

            resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
            // new ResourceManager("Player.MediaPlayer", typeof(MediaPlayer).Assembly);
            UISync.Init(this);
           
   
        }
        Bitmap splashScreenImageCore;
        Bitmap SplashScreenImage { get { return splashScreenImageCore; } }
        Assembly currentAssemblyCore;
        Assembly CurrentAssembly {
            get {
                if(currentAssemblyCore == null)
                    currentAssemblyCore = Assembly.GetExecutingAssembly();
                return currentAssemblyCore;
            }
        }
     
        private void frmMain_Load(object sender, System.EventArgs e) {
            SkinHelper.InitSkinPopupMenu(iPaintStyle);
            
            Init();
        }
       
      
        Cursor currentCursor;
        void InitDemo() {
            
            
        
            //SplashScreenManager.HideImage();
        }
     
        System.Drawing.Icon CreateIcon(int index) {
            return CreateIcon(imageList4.Images[index]);
        }
        System.Drawing.Icon CreateIcon(Image image) {
            if(image == null) return null;
            using(System.Drawing.Bitmap newIcon = new System.Drawing.Bitmap(16, 16, System.Drawing.Imaging.PixelFormat.Format32bppArgb)) {
                using(System.Drawing.Graphics g = System.Drawing.Graphics.FromImage(newIcon)) {
                    g.DrawImageUnscaled(image, 0, 0, 16, 16);
                    return System.Drawing.Icon.FromHandle(newIcon.GetHicon());
                }
            }
        }
        RichEditControl ActiveRTB {
            get {
                if(this.ActiveMdiChild != null && this.ActiveMdiChild.ContainsFocus) {
                    if(this.ActiveMdiChild.Controls.Count == 0) return null;
                    return this.ActiveMdiChild.Controls[0] as RichEditControl;
                }
                return null;
            }
        }
        
       
        void iAbout_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            DevExpress.Utils.About.frmAbout dlg = new DevExpress.Utils.About.frmAbout("DockingDemo for the XtraBars by Developer Express Inc.");
            dlg.ShowDialog();
        }
      
        void iCut_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) rtb.Cut();
        }
        void iCopy_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) rtb.Copy();
        }
        void iPaste_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) rtb.Paste();
        }
        void iSelectAll_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) {
                rtb.SelectAll();
                rtb.Focus();
            }
        }
        void iUndo_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) rtb.Undo();
            
        }
        void iRedo_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            RichEditControl rtb = ActiveRTB;
            if(rtb != null) rtb.Redo();
           
        }
        //AB15908
        protected DockPanel GetTopDockPanelCore(DockPanel panel) {
            if(panel.ParentPanel != null) return GetTopDockPanel(panel.ParentPanel);
            else return panel;
        }
        protected DockPanel GetTopDockPanel(DockPanel panel) {
            DockPanel floatPanelCandidate = GetTopDockPanelCore(panel);
            if(floatPanelCandidate.Dock == DockingStyle.Float) return floatPanelCandidate;
            else return panel;
        }
        //AB15908
        void iSolutionExplorer_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            GetTopDockPanel(dockPanelSolution).Show();
            tabbedView1.ActivateDocument(dockPanelSolution.Parent);
        }
        void iProperties_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            GetTopDockPanel(dockPanelFind).Show();
            tabbedView1.ActivateDocument(dockPanelFind.Parent);
        }
        void iTaskList_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            GetTopDockPanel(dockPanelShot).Show();
            tabbedView1.ActivateDocument(dockPanelShot.Parent);
        }
        void iFindResults_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            GetTopDockPanel(dockPanelTask).Show();
            tabbedView1.ActivateDocument(dockPanelTask.Parent);
        }
        void iOutput_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            GetTopDockPanel(dockPanelOutPut).Show();
            tabbedView1.ActivateDocument(dockPanelOutPut.Parent);
        }
        void iToolbox_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            //GetTopDockPanel(dockPanelTools).Show();
            //tabbedView1.ActivateDocument(dockPanelTools.Parent);
        }
        void solutionExplorer1_PropertiesItemClick(object sender, System.EventArgs e) {
            GetTopDockPanel(dockPanelFind).Show();
            tabbedView1.ActivateDocument(dockPanelFind.Parent);
        }
       
        void iSaveLayout_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "XML files (*.xml)|*.xml";
            dlg.Title = "Save Layout";
            if(dlg.ShowDialog() == DialogResult.OK) {
                Refresh(true);
                barManager1.SaveToXml(dlg.FileName);
                Refresh(false);
            }
        }
        void iLoadLayout_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "XML files (*.xml)|*.xml|All files|*.*";
            dlg.Title = "Restore Layout";
            if(dlg.ShowDialog() == DialogResult.OK) {
                Refresh(true);
                try {
                    barManager1.RestoreFromXml(dlg.FileName);
                    SkinHelper.InitSkinPopupMenu(iPaintStyle);
                }
                catch { }
                Refresh(false);
            }
        }
        void Refresh(bool isWait) {
            if(isWait) {
                currentCursor = Cursor.Current;
                Cursor.Current = Cursors.WaitCursor;
            }
            else
                Cursor.Current = currentCursor;
            this.Refresh();
        }
        void iExit_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            this.Close();
        }







        #endregion
        #region Player
        public PlayerControl playerControl1 = new PlayerControl();
        private Factory Factory = new Factory();

        public ObservableCollection<Chapter> MergeChapters = new ObservableCollection<Chapter>();
        ComponentResourceManager resourseMng;

        private List<Playlist> PList = new List<Playlist>();


        private object CurrentItem;

        private Chapter currentChapter;
        public Chapter CurrentChapter
        {
            get { return currentChapter; }
            set
            {

                currentChapter = value;
                OnCurrentChapterChanged();
            }
        }
        public Chapter LastChapter { get; set; }
        private void OnCurrentChapterChanged()
        {
            CurrentChapterbindingSource.DataSource = currentChapter;
            CurrentChapterbindingSource.ResetCurrentItem();
            ChapterbindingSource.CurrencyManager.Position = ChapterbindingSource.IndexOf(currentChapter);
        }
        private Playlist currentPlaylist;
        public Playlist CurrentPlaylist
        {
            get { return currentPlaylist; }
            set { currentPlaylist = value; }
        }


        private PlaylistItem currentPlaylistItem;
        public PlaylistItem CurrentPlaylistItem
        {
            get { return currentPlaylistItem; }
            set
            {
                if (currentPlaylistItem != value)
                {
                    currentPlaylistItem = value;
                    OnCurrentListItemChange(value);
                }
            }
        }
        public void clear()
        {
            playerControl1.Stop();

            PList.Clear();
            MergeChapters.Clear();
            PlaylistItem.AllChapters.Clear();
            ChapterbindingSource.Clear();
        }
        public void Init()
        {


            if (System.IO.File.Exists(App.Setting.MetaDataPath))
            {
                var obj = Serializer.DESDeSerializeFromFile<List<Playlist>>(App.Setting.MetaDataPath);
                if (obj != null) PList = obj;

            }
          //  AlbumName.Caption = App.AlbumName();
            PlayListbindingSource.DataSource = PList;

            AllchapterBindingSource.DataSource = PlaylistItem.AllChapters;
            PlaylistItem.AllChapters.CollectionChanged += NotifyChapterChangedEventHandler;

            AllChapterGroupbindingSource.DataSource = PlaylistItem.AllChapterGroup;
            GrouprepositoryItemMRUEdit.Items.AddRange(PlaylistItem.AllChapterGroup);
            RefreshData();
            new GridViewImageTextToolTipController(advBandedGridView1, "ThumbnailImage", true);
            new GridViewImageTextToolTipController(advBandedGridView1, "Description", false);

            new vGridViewImageTextToolTipController(vGridControlChapters, "rowThumbnailImage", true);
            new vGridViewImageTextToolTipController(vGridControlChapters, "rowDescription", false);

        }

        public void GetFile()
        {
            if (CurrentPlaylist != null)
            {
                var fileName = Player.ObjectHelper.GetFileName("", "", ObjectHelper.DialogType.OpenDialog);

                if (!string.IsNullOrEmpty(fileName))
                {
                    PlaylistItem NItem = new PlaylistItem(System.IO.Path.GetFileName(fileName), "", fileName);
                    CurrentPlaylistItem = NItem;
                    CurrentPlaylist.Items.Add(NItem);
                    ChapterbindingSource.DataSource = CurrentPlaylistItem.Chapters;
                    RefreshData();
                }
            }
            else
                XtraMessageBox.Show(resourseMng.GetString("please_select_a_List"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);

        }
        public void BookMark()
        {
            if (CurrentPlaylistItem != null)
            {
                var bmp = playerControl1.GetImageScreen();
                string FileName = Guid.NewGuid().ToString();
                string FilePath = App.PicDir + FileName;

                bmp.Save(FilePath, ImageFormat.Jpeg);
                var last = CurrentPlaylistItem.Chapters.DefaultIfEmpty(null).Last();
                if (last != null && last.EndPosition == null) last.EndPosition = Math.Abs(playerControl1.CurrentPostion - 1000);
                CurrentPlaylistItem.Chapters.Add(new Chapter(playerControl1.CurrentPostion, "Title", FileName, "", bmp.GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero)));
                ChapterbindingSource.ResetBindings(false);
                ChapterbindingSource.MoveLast();
                bmp.Dispose();
                RefreshData();
            }
        }

        public bool ThumbnailCallback()
        {
            return true;
        }


        private void CmdOpenFile_Click(object sender, EventArgs e)
        {
            GetFile();
        }
      

        private void FrmPlayer_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult CloseMessage;
            CloseMessage = XtraMessageBox.Show(resourseMng.GetString("Are_you_sure_you_want_to_close"), resourseMng.GetString("Header_Message"), MessageBoxButtons.YesNo, MessageBoxIcon.Information);
            if (CloseMessage == DialogResult.Yes)
            {

                Serializer.DESSerialize(PList, App.Setting.MetaDataPath);
                PList.Clear();
                if (playerControl1 != null) playerControl1.Dispose();
                App.Setting.SaveAppSetting();

            }

            if (CloseMessage == DialogResult.No)
                e.Cancel = true;

        }


        private void bookMarkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BookMark();
        }





        private void uiCommandManager1_CommandClick(object sender, Janus.Windows.UI.CommandBars.CommandEventArgs e)
        {
            BookMark();
        }

        private void repositoryItemPictureEdit1_DoubleClick_1(object sender, EventArgs e)
        {
            GoToBookMark();
        }

        private void GoToBookMark()
        {
            if (ChapterbindingSource.Current != null)
            {
                CurrentChapter = (Chapter)ChapterbindingSource.Current;

                Play(CurrentChapter);
            }

        }
        private void GoToBookMark(Chapter chapter)
        {
            if (chapter != null)
            {
                CurrentChapter = chapter;
                //   Play(chapter.SourceMedia);
                //playerControl1.Stop();
                //playerControl1.Play(CurrentChapter);
                Play(chapter);
            }

        }


        private void PlayListbindingSource_CurrentChanged(object sender, EventArgs e)
        {
            CurrentPlaylist = (Playlist)PlayListbindingSource.Current;
        }

        public void Play(PlaylistItem item)
        {
            CurrentItem = item;
            AddPlayerControl();
            playerControl1.Play(item);

        }
        public void Play(Chapter item)
        {
            CurrentItem = item;
            AddPlayerControl();
            playerControl1.Play(item);

            //item.SetPlayeing();
            //    ChapterbindingSource.ResetBindings(false);
        }

        private void AddPlayerControl()
        {
            string mediaSource = CurrentItem is Chapter ? (CurrentItem as Chapter).SourceMedia.MediaSource : (CurrentItem as PlaylistItem).MediaSource;
            FileInfo fileInfo = new FileInfo(mediaSource);
            var extension = fileInfo.Extension;
            if (playerControl1 != null) playerControl1.Stop();
            playerControl1 = Factory.CurrentPlayer(extension);
            tabbedView1.BeginUpdate();
            
          // playerControl1.Dock = DockStyle.Fill;
            BaseDocument document = tabbedView1.Controller.AddDocument(playerControl1);
            tabbedView1.EndUpdate();
            
        }

        public void OnCurrentListItemChange(PlaylistItem item)
        {

            ChapterbindingSource.DataSource = item.Chapters;
            vGridControlChapters.Refresh();
        }


        private void ListItemgridView_DoubleClick(object sender, EventArgs e)
        {
            GridView v = sender as GridView; //(GridView)gridView1.GetDetailView(gridView1.GetRowHandle(PlayListbindingSource.Position), 0);
            if (v != null)
            {
                var obj = v.GetFocusedRow();
                CurrentPlaylistItem = (PlaylistItem)obj;
                Play(CurrentPlaylistItem);
            }
        }

        private void btnSetHandlerLeft_Click(object sender, EventArgs e)
        {
            SetChapterPosition(ChapterPosition.start);
        }

        private void btnSetHandlerRight_Click(object sender, EventArgs e)
        {
            SetChapterPosition(ChapterPosition.end);
        }

        private void SetChapterPosition(ChapterPosition position)
        {
            Chapter CurrentChapter = (Chapter)ChapterbindingSource.Current;
            if (CurrentChapter != null)
            {
                if (position == ChapterPosition.start)
                {
                    CurrentChapter.StartPosition = playerControl1.CurrentPostion;
                    var bmp = playerControl1.GetImageScreen();
                    CurrentChapter.ThumbnailImage = bmp.GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero);
                    string FileName = Guid.NewGuid().ToString();
                    CurrentChapter.ThumbnailSource = FileName;
                    string FilePath = App.PicDir + FileName;
                    bmp.Save(FilePath, ImageFormat.Jpeg);
                }
                else
                    CurrentChapter.EndPosition = playerControl1.CurrentPostion;

                ChapterbindingSource.ResetCurrentItem();
            }
        }



        private void CmdSetHandlerLeft_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            SetChapterPosition(ChapterPosition.start);
        }

        private void CmdSetHandlerRight_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            SetChapterPosition(ChapterPosition.end);
        }

        private void barLargeButtonItem1_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            BookMark();
        }

        private void barLargeButtonItem2_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            try
            {
                ChapterbindingSource.RemoveCurrent();
                ChapterbindingSource.ResetCurrentItem();
            }
            catch (Exception)
            {


            }

        }






        private void advBandedGridView1_DoubleClick(object sender, EventArgs e)
        {
            CurrentPlaylistItem = ((Chapter)AllchapterBindingSource.Current).SourceMedia;

            GoToBookMark((Chapter)AllchapterBindingSource.Current);


        }

        ProgressForm pf = new ProgressForm();
        public void saveChapters()
        {
            this.ValidateChildren();
            this.Validate();


            if ((CurrentPlaylistItem != null) && (CurrentPlaylistItem.Chapters.Count > 0))
            {
                VideoEditor.VideoEditorManager VM = new VideoEditor.VideoEditorManager();
                var cList = (from c in CurrentPlaylistItem.Chapters where c.Selected == true select c).ToList();
                //if(cList.Count >0)
                //{
                var Notvalid = (from c in cList where c.EndPosition == null || c.EndPosition < c.StartPosition select c).Any();
                if (Notvalid)
                {
                    XtraMessageBox.Show(resourseMng.GetString("Undifine_End_Shut"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
                FileDialog.FileDialog SaveFileDialog = new FileDialog.FileDialog();
                //SaveFileDialog SaveFileDialog = new SaveFileDialog();
                string sz = CurrentPlaylistItem.MediaSource.ExtOfFile();
                SaveFileDialog.FileName = "Default" + sz;
                sz = "*" + sz;
                SaveFileDialog.DefaultExt = sz;
                sz = sz + "|" + sz;
                SaveFileDialog.Filter = sz;



                if ((cList.Count > 0) && (SaveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK))
                {

                    VideoEditor.SMM_Defs.CInterval_info[] IFs = cList.ToCInterval_infoPos(PlayerControl.TotalDuritionFile);
                    //  PlayerControl.Ctlcontrols.pause();
                    if (VM.Validate(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, IFs))
                    {
                        if (VM.StartProcess(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, pf, IFs))
                            pf.ShowDialog(VM);
                    }
                    else if (XtraMessageBox.Show(resourseMng.GetString("Selected_Shut_is_Overlap"), "", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                    {
                        VM.StartProcess(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, pf, IFs, SMM_Defs.SMM_TrimFlags.SSM_TrimFlags_TrimOverlappedIntervals);
                        pf.ShowDialog(VM);
                    }


                }
                else { XtraMessageBox.Show(resourseMng.GetString("Selected_Item_Or_true_File_Name"), "", MessageBoxButtons.OK, MessageBoxIcon.Information); }
            }

        }

        public void saveChapters(ObservableCollection<Chapter> mergeChapters)
        {

            ChapterbindingSource.EndEdit();
            vGridControlChapters.UpdateFocusedRecord();
            if (mergeChapters.Count > 0)
            {
                VideoEditor.VideoEditorManager VM = new VideoEditor.VideoEditorManager();
                var cList = mergeChapters.ToList();// (from c in mergeChapters where c.Selected == true select c).ToList();
                var Notvalid = (from c in cList where c.EndPosition == null || c.EndPosition < c.StartPosition select c).Any();
                if (Notvalid)
                {
                    XtraMessageBox.Show(resourseMng.GetString("Undifine_End_Shut"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
                FileDialog.FileDialog SaveFileDialog = new FileDialog.FileDialog();
                //SaveFileDialog SaveFileDialog = new SaveFileDialog();
                string sz = (mergeChapters[0] as Chapter).ExtensionFile;
                SaveFileDialog.FileName = "Default" + sz;
                sz = "*" + sz;
                SaveFileDialog.DefaultExt = sz;
                sz = sz + "|" + sz;
                SaveFileDialog.Filter = sz;



                if ((cList.Count > 0) & (SaveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK))
                {

                    VideoEditor.SMM_Defs.CInterval_info[] IFs = cList.ToCInterval_info();
                    //  PlayerControl.Ctlcontrols.pause();
                    if (VM.Validate(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, IFs))
                    {
                        if (VM.StartProcess(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, pf, IFs))
                            pf.ShowDialog(VM);
                    }
                    else if (XtraMessageBox.Show(resourseMng.GetString("Selected_Shut_is_Overlap"), "", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == System.Windows.Forms.DialogResult.Yes)
                    {
                        VM.StartProcess(CurrentPlaylistItem.MediaSource, SaveFileDialog.FileName, pf, IFs, SMM_Defs.SMM_TrimFlags.SSM_TrimFlags_TrimOverlappedIntervals);
                        pf.ShowDialog(VM);
                    }


                }
            }

        }
        private void barLargeButtonItem3_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {

            saveChapters();

        }

        private void barLargeButtonItem4_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo(@"C:\\Program Files\\Solveig Multimedia\\SolveigMM Video Splitter\\SMM_BatchSplit.exe", @"d:\\split.xtl");
            //startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process p = new Process();
            p.StartInfo = startInfo;
            p.OutputDataReceived += DataReceived;
            p.Start();

            p.WaitForExit();

            XtraMessageBox.Show(resourseMng.GetString("finish"));

        }



        void DataReceived(object sender, DataReceivedEventArgs e)
        {
            XtraMessageBox.Show(e.Data);
        }

        private void cmdChapterMSelectItem_DownChanged(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            ChapterMSelected.Visible = !ChapterMSelected.Visible;
        }
        public void RefreshData()
        {
            Dangel.ExistDangelTrue();

            PlayListbindingSource.ResetBindings(false);
            ChapterbindingSource.ResetBindings(false);
            AllchapterBindingSource.ResetBindings(false);
            AllChapterGroupbindingSource.ResetBindings(false);
            GrouprepositoryItemMRUEdit.Items.Clear();
            GrouprepositoryItemMRUEdit.Items.AddRange(PlaylistItem.AllChapterGroup);

        }
        public void NotifyChapterChangedEventHandler(object sender, NotifyCollectionChangedEventArgs e)
        {
            AllchapterBindingSource.ResetBindings(false);
        }


        private void CmdAddItem_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            PList.Add(new Playlist() { Name = "List1" });
            PlayListbindingSource.ResetBindings(false);
        }

        private void CmdDeleteItem_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            try
            {
                if (PlayListbindingSource.Current != null && XtraMessageBox.Show(resourseMng.GetString("Delete_Palay_List"), resourseMng.GetString("Delete"), MessageBoxButtons.YesNo, MessageBoxIcon.Question) == System.Windows.Forms.DialogResult.Yes)
                    PlayListbindingSource.RemoveCurrent();
            }
            catch (Exception)
            {

            }

        }

        private void ChapterbindingSource_CurrentChanged(object sender, EventArgs e)
        {
            AllchapterBindingSource.CurrencyManager.Position = AllchapterBindingSource.IndexOf(ChapterbindingSource.Current);
        }





        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveProject();
        }

        public void SaveProject()
        {
            if (PList != null)
            {
                if (XtraMessageBox.Show(resourseMng.GetString("do_you_want_save_current_project"), resourseMng.GetString("Header_save"), MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                {
                    Serializer.DESSerialize(PList, App.Setting.MetaDataPath);
                    XtraMessageBox.Show(Properties.Resources.OperationSuccesfull, resourseMng.GetString("Header_save"), MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }

        }

        private void CmdExport_Click(object sender, EventArgs e)
        {
            SaveProject();
            string filename = ObjectHelper.GetAlbumFileName();
            if (!string.IsNullOrEmpty(filename))
            {
                //  Serializer.DESSerialize(PList, filename+App.ExtentionAlbum);
                Serializer.DESSerialize(PList, filename);
                XtraMessageBox.Show(resourseMng.GetString("Operation_Succesfull"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void CmdImport_Click(object sender, EventArgs e)
        {
            var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.OpenDialog);

            if (!string.IsNullOrEmpty(fileName) && XtraMessageBox.Show(Properties.Resources.RequestAppend, "", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
            {
                var obj = Serializer.DESDeSerializeFromFile<List<Playlist>>(fileName);
                PList.AddRange(obj);
                PlayListbindingSource.ResetBindings(false);
                gridControl.MainView.RefreshData();
            }
        }

        private void PlayerControl_Enter(object sender, EventArgs e)
        {

        }

      //  private ConvertForm frmConvert = new ConvertForm();
        private void convertToolStripMenuItem_Click(object sender, EventArgs e)
        {
         //   frmConvert.ShowDialog();
        }
        private BackUpForm BackUpFrm = new BackUpForm();
        private void backUpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveProject();
            BackUpFrm.ShowDialog();
        }

        private BackUpRestoreForm backUpRestoreFrm = new BackUpRestoreForm();
        private void restoreBackUpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            backUpRestoreFrm.ShowDialog();
        }

        private void openProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveProject();
            // if (openFileMetaData.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.OpenDialog, "Album1");
            if (!string.IsNullOrEmpty(fileName))
            {
                App.Setting.MetaDataPath = fileName;
                Init();
                playerControl1.Pause();
            }

        }

        private void newProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveProject();
            var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.SaveDialog, "Album1");
            //  if (saveFile.ShowDialog() == System.Windows.Forms.DialogResult.OK) 
            if (!string.IsNullOrEmpty(fileName))
            {
                App.Setting.MetaDataPath = fileName;

                clear();

                Init();
                playerControl1.Pause();
                Application.DoEvents();
            }
        }



        private void barButtonItem2_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            saveChapters(MergeChapters);
        }

        private void cmdAddToBachList_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            var extensionFile = new System.IO.FileInfo(CurrentPlaylistItem.MediaSource).Extension;
            if (ChapterbindingSource.Current != null)
            {
                MergeChapters.Add(ChapterbindingSource.Current as Chapter);
            }
            ///  chapter.ExtensionFile = extensionFile;

        }

        private void cmdSaveCurrentList_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            playerControl1.Pause();
            saveChapters();

        }

        private void barButtonItem2_ItemClick_1(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            GetFile();
        }

        private void barButtonItem3_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            GridView v = (GridView)gridView1.GetDetailView(gridView1.GetRowHandle(PlayListbindingSource.Position), 0);
            if (v != null)
            {
                if (XtraMessageBox.Show(resourseMng.GetString("Delete_All_Chapters_and_file"), resourseMng.GetString("Header_Message"), MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
                {
                    try
                    {
                        var obj = v.GetFocusedRow();
                        var Playitem = CurrentPlaylist.Items.ElementAt(CurrentPlaylist.Items.IndexOf((PlaylistItem)obj));
                        foreach (var item in Playitem.Chapters.ToList())
                        {
                            Playitem.Chapters.Remove(item);
                        }
                        CurrentPlaylist.Items.Remove((PlaylistItem)obj);
                        RefreshData();
                    }
                    catch (Exception)
                    {


                    }

                }
            }

        }
        private SettingForm SettingFrm = new SettingForm();
        private void settingToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            SettingFrm.ShowDialog();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void CmdSelectAll_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            foreach (var item in CurrentPlaylistItem.Chapters)
            {
                item.Selected = true;
            }
            ChapterMSelected.Visible = true;
            Application.DoEvents();
        }

        private void barButtonItem2_ItemClick_2(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            foreach (var item in CurrentPlaylistItem.Chapters)
            {
                item.Selected = false;
            }
            ChapterMSelected.Visible = false;
            Application.DoEvents();
        }

        private void abautToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var frm = new About();
            frm.ShowDialog();
        }


        #endregion

        private void PlayerDockPanel_Click(object sender, EventArgs e)
        {

        }

     
    }
}
