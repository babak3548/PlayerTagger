using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraGrid.Views.Base;
using DevExpress.XtraGrid.Views.Grid;
using System.Drawing.Imaging;
using AxWMPLib;
using DevExpress.XtraEditors.Controls;
using System.Diagnostics;
using VideoEditor;
using System.Collections.Specialized;
using Player.Controls;
using System.Threading;
using DevExpress.XtraEditors;
using Player.Public_class;
using Player.Forms;
using Player.Setting;
using Player.DataControl;
using System.Collections.ObjectModel;
using DevExpress.XtraVerticalGrid;
using System.IO;
using System.Resources;
using System.Xml.Serialization;
using Utility;
namespace Player
{
    public partial class MediaPlayer : DevExpress.XtraEditors.XtraForm
    {

        public PlayerControl playerControl1 = new PlayerControl();
        private Factory Factory = new Factory();

        public SecondPlayWindows secondPlayWindowsForm;
        public static  bool FlagSecondPlayWindowsForm=false;
      //  public static long PlayerControlCurrentPostion = 0;
        //public static object PlayerControlCurrentPlayItem;
        public ObservableCollection<Chapter> MergeChapters = new ObservableCollection<Chapter>();
        ComponentResourceManager resourseMng;
       // bool flagChangedProject = false;

        public MediaPlayer()
        {
            Properties.Settings settings = new Properties.Settings();
            InitializeComponent();

            resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
            // new ResourceManager("Player.MediaPlayer", typeof(MediaPlayer).Assembly);
            UISync.Init(this);
        }

        // [XmlArray("ArrayOfPlayList"), XmlArrayItem("PlayList")]
        public List<Playlist> PList = new List<Playlist>();


        public object CurrentItem;

        private Chapter currentChapter;
        public Chapter CurrentChapter
        {
            get
            {
                return currentChapter;

            }
            set
            {

                currentChapter = value;
                OnCurrentChapterChanged();


            }
        }
        public Chapter LastChapter { get; set; }
        private void OnCurrentChapterChanged()
        {
            lock (CurrentChapterbindingSource.SyncRoot)
            {

                CurrentChapterbindingSource.DataSource = currentChapter;
                CurrentChapterbindingSource.ResetCurrentItem();
                ChapterbindingSource.Position = ChapterbindingSource.IndexOf(currentChapter);
            }
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
            get
            {
                lock (this)
                {
                    return currentPlaylistItem;
                }
            }
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
            // playerControl1.Clean();
            PList.Clear();
            MergeChapters.Clear();
            PlaylistItem.AllChapters.Clear();
            lock (ChapterbindingSource.SyncRoot)
            {
               ChapterbindingSource.Clear(); 
            }
            
           // uiPanel1.Controls.Clear();
        }
        public void Init()
        {


            if (CheakExistMetadataFile())
            {
                var obj = Serializer.DESDeSerializeFromFile<List<Playlist>>(App.Setting.MetaDataPath);
                App.Setting.SaveAppSetting();
                if (obj != null) PList = obj;
                SetAlbumName();
            }
           
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

        public void SetAlbumName()
        {
            AlbumName.Caption = App.AlbumName().Length > 18 ? App.AlbumName().Substring(0, 15) + "..." : App.AlbumName();
            AlbumName.Hint = App.Setting.MetaDataPath + " : " + resourseMng.GetString("Path_Album");
            this.Text =  App.FullAlbumName();
            //resourseMng.GetString("$this.Text") + "  -  " + 
        }
        private int CountAddedFiles()
        {
            int countFilesAdded=0;
            foreach (var list in PList)
            {
                countFilesAdded += list.Items.Count;
            }
            return countFilesAdded;
        }
        public void GetFile()
        {
            if (CurrentPlaylist != null)
            {
                var fileName = Player.ObjectHelper.GetFileName("", "", ObjectHelper.DialogType.OpenDialog,null,App.Setting.DefaulFilesPath);

                if (!string.IsNullOrEmpty(fileName))
                {
                    PlaylistItem NItem = new PlaylistItem(System.IO.Path.GetFileName(fileName), "", fileName);
                    CurrentPlaylistItem = NItem;
                    if (CountAddedFiles ()< 10)
                    {
                        CurrentPlaylist.Items.Add(NItem);
                    }
                    else
                    {
                        XtraMessageBox.Show(resourseMng.GetString("please_Get_Lisence"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    
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
                if (bmp == null) return;
                string FileName = Guid.NewGuid().ToString();
                string FilePath = App.PicDir + FileName;

                bmp.Save(FilePath, ImageFormat.Jpeg);
                var last = CurrentPlaylistItem.Chapters.LastOrDefault(c => c.StartPosition <= playerControl1.CurrentPostion); //DefaultIfEmpty(null).Last();
                if (last != null && last.EndPosition == null) last.EndPosition = playerControl1.CurrentPostion - 2;// Math.Abs(playerControl1.CurrentPostion - 1);
                Chapter CreateChapter = new Chapter(playerControl1.CurrentPostion, resourseMng.GetString("Title"), FileName, "", bmp.GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero));
                CurrentPlaylistItem.Chapters.Add(CreateChapter);
               int IndexOf= CurrentPlaylistItem.Chapters.IndexOf(CreateChapter);
               ChapterbindingSource.Position = IndexOf;
             //   ChapterbindingSource.ResetBindings(false);
                
                //ChapterbindingSource.MoveLast();
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
        private void FrmPlayer_Load(object sender, EventArgs e)
        {


          //  XtraMessageBox.Show(Program.filePath1+ "***" + Program.filePath, resourseMng.GetString("Header_Message"), MessageBoxButtons.OK, MessageBoxIcon.Information);
            if (new DateTime(2014, 10, 10) <= DateTime.Now.Date && DateTime.Now.Date <= new DateTime(2019, 1, 30)) { Init(); }
            else
            {
                XtraMessageBox.Show("لطفا جهت تهیه لایسنس با شرکت بیلگی سافت تماس بگیرید", resourseMng.GetString("Header_Message"), MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.FormClosing -= FrmPlayer_FormClosing;
                Environment.Exit(1);
            }
            ContinuePlay.EditValue = App.Setting.CountinePlay;
            VLCPlayer.ShutPlay=App.Setting.CountinePlay;
            
        }

        void MediaPlayer_FormClosing(object sender, FormClosingEventArgs e)
        {
            throw new NotImplementedException();
        }

        void MediaPlayer_FormClosed(object sender, FormClosedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void FrmPlayer_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (SaveProject() == "Cancel")
            { e.Cancel = true; }
            else
            {
                    PList.Clear();
                    if (playerControl1 != null) playerControl1.Dispose();
            }
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
                //Play(chapter.SourceMedia);
                //playerControl1.Stop();
                //playerControl1.Play(CurrentChapter);
                Play(chapter);
            }

        }

        public bool CheckExistMediaFile(string MediaFile)
        {
           var fileInfo = new FileInfo(MediaFile);
           if (!fileInfo.Exists)
           {
               XtraMessageBox.Show(resourseMng.GetString("this_file_not_Exist_in_path"), "", MessageBoxButtons.OK, MessageBoxIcon.Error);
               return false;
           }
           else return true;
        }
        private void PlayListbindingSource_CurrentChanged(object sender, EventArgs e)
        {
            CurrentPlaylist = (Playlist)PlayListbindingSource.Current;
        }

        public void Play(PlaylistItem item)
        {
            //ComponentResourceManager resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
          
            CurrentItem = item;
            AddPlayerControl();
            playerControl1.Play(item);
            if (FlagSecondPlayWindowsForm ) { secondPlayWindowsForm.Play(item); }
               
        }
        public void Play(Chapter item)
        {
            if (!CheckExistMediaFile(item.SourceMedia.MediaSource)) return;
            CurrentItem = item;
            AddPlayerControl();
            playerControl1.Play(item);
            if (FlagSecondPlayWindowsForm) secondPlayWindowsForm.Play(item);

        }

        private void AddPlayerControl()
        {
            string mediaSource = CurrentItem is Chapter ? (CurrentItem as Chapter).SourceMedia.MediaSource : (CurrentItem as PlaylistItem).MediaSource;
            FileInfo fileInfo = new FileInfo(mediaSource);
            var extension = fileInfo.Extension;
            //if (playerControl1 != null) playerControl1.Stop(); no active
          var plyer = Factory.CurrentPlayer(extension);
          if (playerControl1.GetType() != plyer.GetType())
          {
              playerControl1.Stop();
              playerControl1 = plyer;
              uiPanel1.Controls.Clear();
              playerControl1.Dock = DockStyle.Fill;
              uiPanel1.Controls.Add(playerControl1);
          }
          PlayerControl.mediaPlayer = this;
        }

        public void OnCurrentListItemChange(PlaylistItem item)
        {
            lock (ChapterbindingSource.SyncRoot)
            {
                item.Chapters.Sort(a => a.StartPosition);
                ChapterbindingSource.DataSource = item.Chapters;
                
             //   ChapterbindingSource.Sort = "StartPositionText";
               
                //  vGridControlChapters.DataSource = item.Chapters;.OrderBy(c => c.StartPosition)
            }

            // vGridControlChapters.Refresh();
        }


        private void ListItemgridView_DoubleClick(object sender, EventArgs e)
        {

            GridView v = sender as GridView; //(GridView)gridView1.GetDetailView(gridView1.GetRowHandle(PlayListbindingSource.Position), 0);

            if (v != null)
            {
                var obj = v.GetFocusedRow();
                if (!CheckExistMediaFile(((PlaylistItem) obj).MediaSource)) return;
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
            lock (ChapterbindingSource.SyncRoot)
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
                lock (ChapterbindingSource.SyncRoot)
                {
                    //string PathPicShot = App.PicDir + ((Player.Chapter)(ChapterbindingSource.Current)).ThumbnailSource;
                    //var x = ((Player.Chapter)(ChapterbindingSource.Current));
         
                ChapterbindingSource.RemoveCurrent();
                ChapterbindingSource.ResetCurrentItem();
                RefreshData();//&* اگر ضرب در برنامه مشاهد شد این خط برداشته شود
               
               // Application.DoEvents();

                //File.Delete(PathPicShot);
                }
            }
            catch (Exception ex)
            {


            }

        }


        private void advBandedGridView1_DoubleClick(object sender, EventArgs e)
        {
          Chapter chapter=  (Chapter)AllchapterBindingSource.Current;
          var _playListItem = (chapter).SourceMedia;
            if (!CheckExistMediaFile(_playListItem.MediaSource)) return;
            CurrentPlaylistItem = _playListItem;

            //GoToBookMark((Chapter)AllchapterBindingSource.Current);
            GoToBookMark(chapter);


        }

        ProgressForm pf = new ProgressForm();

        /*
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
              //  FileDialog.FileDialog SaveFileDialog = new FileDialog.FileDialog();
                //SaveFileDialog SaveFileDialog = new SaveFileDialog();
                string sz = CurrentPlaylistItem.MediaSource.ExtOfFile();
                string ext = sz;
                string fileName = "";
              //  SaveFileDialog.FileName = "Default" + sz;
                sz = "*" + sz;
              //  SaveFileDialog.DefaultExt = sz;
                sz = sz + "|" + sz;
                //SaveFileDialog.Filter = sz;
              //  SaveFileDialog.Title = "ذخیره شات";


                if ((cList.Count > 0) )
                {
                   var fdx= Player.ObjectHelper.GetFileName(ext, sz, ObjectHelper.DialogType.SaveDialog, "Default" + ext, "", false, "ذخیره شات");
                  // if (SaveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                   if (fdx != String.Empty)
                    {
                        fileName = fdx;//SaveFileDialog.FileName;
                        fileName = fileName.Replace(ext, "") + ext;
                        VideoEditor.SMM_Defs.CInterval_info[] IFs = cList.ToCInterval_infoPos(PlayerControl.TotalDuritionFile);
                        //  PlayerControl.Ctlcontrols.pause();
                        if (VM.Validate(CurrentPlaylistItem.MediaSource, fileName, IFs))
                        {
                            if (pf == null) pf = new ProgressForm();
                            if (VM.StartProcess(CurrentPlaylistItem.MediaSource, fileName, pf, IFs))
                                pf.ShowDialog(VM);
                        }
                        else if (XtraMessageBox.Show(resourseMng.GetString("Selected_Shut_is_Overlap"), "", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                        {
                            VM.StartProcess(CurrentPlaylistItem.MediaSource, fileName, pf, IFs, SMM_Defs.SMM_TrimFlags.SSM_TrimFlags_TrimOverlappedIntervals);
                            pf.ShowDialog(VM);
                        }
                    }

                }
                else { XtraMessageBox.Show(resourseMng.GetString("Selected_Item_Or_true_File_Name"), "", MessageBoxButtons.OK, MessageBoxIcon.Information); }
            }

        }
        */

        public void saveChapters()
        {
            this.ValidateChildren();
            this.Validate();
            FfmpegSplit ffmpegSplit = new FfmpegSplit();

            if ((CurrentPlaylistItem != null) && (CurrentPlaylistItem.Chapters.Count > 0))
            {
               // VideoEditor.VideoEditorManager VM = new VideoEditor.VideoEditorManager();
               // VideoEditor.Ffmpeg ffm = new VideoEditor.Ffmpeg();
                var cList = (from c in CurrentPlaylistItem.Chapters where c.Selected == true select c).ToList();
                //if(cList.Count >0)
                //{
                var Notvalid = (from c in cList where c.EndPosition == null || c.EndPosition < c.StartPosition select c).Any();
                if (Notvalid)
                {
                    XtraMessageBox.Show(resourseMng.GetString("Undifine_End_Shut"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
                string sz = CurrentPlaylistItem.MediaSource.ExtOfFile();
                string ext = sz;
                string fileName = "";

                sz = "*" + sz;

                sz = sz + "|" + sz;

               // if ((cList.Count > 0))
              //  {
                    //var fdx = Player.ObjectHelper.GetFileName(ext, sz, ObjectHelper.DialogType.SaveDialog, "Default" + ext, "", false, "ذخیره شات");
                    //if (fdx != String.Empty)
                 //   {
                       // fileName = fdx;
                      //  fileName = fileName.Replace(ext, "") + ext;
                        // VideoEditor.SMM_Defs.CInterval_info[] IFs = cList.ToCInterval_infoPos(PlayerControl.TotalDuritionFile);
                List<SpliteShutInfo> IFs = cList.ToSpliteShutInfo(PlayerControl.TotalDuritionFile, CurrentPlaylistItem.MediaSource.DurtionByFfmpeg());
                       ffmpegSplit.ShowDialog(IFs);
                   // }

               // }
               // else { XtraMessageBox.Show(resourseMng.GetString("Selected_Item_Or_true_File_Name"), "", MessageBoxButtons.OK, MessageBoxIcon.Information); }
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
            gridView1.ExpandMasterRow(gridView1.FocusedRowHandle);

        }
        public void NotifyChapterChangedEventHandler(object sender, NotifyCollectionChangedEventArgs e)
        {
            AllchapterBindingSource.ResetBindings(false);
        }

        private void barButtonItem1_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            //   uiPanel6.AutoHide = !uiPanel6.AutoHide;

        }

        private void CmdAddItem_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (CheakExistMetadataFile())
            {
               // PList.Add(new Playlist() { Name = "List1" });
                int LastIndex = PList.FindLastIndex(p => p.Name.Contains("List"));
                
                PlayListbindingSource.Add(new Playlist() { Name = "List" + (LastIndex+2) });
               // PlayListbindingSource.ResetBindings(false);
            }
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

        public string SaveProject()
        {
            var resaultDialogRezult= XtraMessageBox.Show(resourseMng.GetString("do_you_want_save_current_project"), resourseMng.GetString("Header_save"), MessageBoxButtons.YesNoCancel);
            if (PList != null && resaultDialogRezult == System.Windows.Forms.DialogResult.Yes && CheakExistMetadataFile())
            {
                       Serializer.DESSerialize(PList, App.Setting.MetaDataPath);
                      // XtraMessageBox.Show(Properties.Resources.OperationSuccesfull, resourseMng.GetString("Header_save"), MessageBoxButtons.OK, MessageBoxIcon.Information);
                       App.Setting.SaveAppSetting();
                       return "Yes";
            }
            else if (resaultDialogRezult == System.Windows.Forms.DialogResult.No)
            { return "No"; }
            else { return "Cancel"; }

        }
        private bool CheakExistMetadataFile()
        {
            if (System.IO.File.Exists(App.Setting.MetaDataPath))
            {
                return true;
            }
            else
            {
                  XtraMessageBox.Show(resourseMng.GetString("path_metadata_file_cheanged_Please_open_Metadata_file_or_new_metadate"), "", MessageBoxButtons.OK, MessageBoxIcon.Information); 
                return false;

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

            if (!string.IsNullOrEmpty(fileName) && XtraMessageBox.Show(resourseMng.GetString("RequestAppend"), "", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
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

       // private ConvertForm frmConvert = new ConvertForm();
        private void convertToolStripMenuItem_Click(object sender, EventArgs e)
        {
        //    frmConvert.ShowDialog();
        }
        private BackUpForm BackUpFrm = new BackUpForm();
        private void backUpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            playerControl1.Pause();
            SaveProject();
            BackUpFrm.ShowDialog();
          //  BackUpFrm.Close();
        }

        private BackUpRestoreForm backUpRestoreFrm = new BackUpRestoreForm();
        private void restoreBackUpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            playerControl1.Pause();
            backUpRestoreFrm.ShowDialog();
        }

        private void openProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (System.IO.File.Exists(App.Setting.MetaDataPath))
            {
                if (SaveProject() == "Cancel")
                { return; }
                
               
            }

            var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.OpenDialog, "Album1");
            if (!string.IsNullOrEmpty(fileName))
            {
                clear();
                App.Setting.MetaDataPath = fileName;
                App.SetPicDir();
                Init();
                playerControl1.Pause();
            }
        }

        private void newProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Player.Forms.newProjectFrm NPF = new newProjectFrm();
            NPF.ShowDialog(this);

          
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
            FileInfo fileInfo = new FileInfo(CurrentPlaylistItem.MediaSource);
            if (!Player.Setting.Utility.IsImage(fileInfo.Extension))
            {
                playerControl1.Pause();
                saveChapters();
            }
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
                        if (Playitem == CurrentPlaylistItem) playerControl1.Clean();
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
            if (CurrentPlaylistItem != null)
            {
                foreach (var item in CurrentPlaylistItem.Chapters)
                {
                    item.Selected = true;
                }
                ChapterMSelected.Visible = true;
                Application.DoEvents();
                this.ValidateChildren();
                this.Validate();
            }
        }

        private void barButtonItem2_ItemClick_2(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (CurrentPlaylistItem != null)
            {
                foreach (var item in CurrentPlaylistItem.Chapters)
                {
                    item.Selected = false;
                }
                ChapterMSelected.Visible = false;
                Application.DoEvents();
            }
        }

        private void abautToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var frm = new About();
            frm.ShowDialog();
        }




        private void testPlayerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /// TestPlayMethod();
            /// 
            timer1.Enabled = !timer1.Enabled;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Random r1 = new Random();
            int rValue1 = r1.Next(0, 1);
            Random r2 = new Random();
            int rValue2 = r2.Next(PList[rValue1].Items.Count - 1);
            var obj = PList[rValue1].Items[rValue2];
            if (obj != null)
                Play(obj);

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            int countChap = PlaylistItem.AllChapters.Count;
            Random r1 = new Random();
            int rValue1 = r1.Next(countChap - 1);
            var obj = PlaylistItem.AllChapters[rValue1];
            if (obj != null)
            {
                CurrentPlaylistItem = ((Chapter)obj).SourceMedia;

                GoToBookMark((Chapter)obj);
            }
        }

        private void testChaptersPlayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer2.Enabled = !timer2.Enabled;
        }

        //private void ContinuePlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        //{
        //    VLCPlayer.ContinuePaly =Convert.ToBoolean( ((e.Item as DevExpress.XtraBars.BarEditItem).Edit as DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit).ValueChecked );
        // //   VLCPlayer.ContinuePaly=()sender
        //}

   

        private void repositoryContinuePlay_CheckStateChanged(object sender, EventArgs e)
        {
            VLCPlayer.ShutPlay =Convert.ToBoolean( (sender as DevExpress.XtraEditors.CheckEdit).EditValue);
            App.Setting.CountinePlay=Convert.ToBoolean((sender as DevExpress.XtraEditors.CheckEdit).EditValue);
        }
        //متد زیر لازم نیست پاک گردد
        private void RIChEPlayCheckedList_CheckStateChanged(object sender, EventArgs e)
        {
            //VLCPlayer.PlayOnlyCheckList = Convert.ToBoolean((sender as DevExpress.XtraEditors.CheckEdit).EditValue);
        }
        private void SecondWindows_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (!FlagSecondPlayWindowsForm)
            {
                FlagSecondPlayWindowsForm = true;
                //PlayerControlCurrentPostion = playerControl1.CurrentPostion;
               // PlayerControlCurrentPlayItem = CurrentItem;
                
                secondPlayWindowsForm = new SecondPlayWindows();
              //  secondPlayWindowsForm.ParentFormMediaPlayer = this;
                secondPlayWindowsForm.Show(this);
            }
        }

  



        private void EditibleItemPlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            ListItemgridView.OptionsBehavior.Editable = ListItemgridView.OptionsBehavior.Editable ^ true;
            if (ListItemgridView.OptionsBehavior.Editable) EditibleItemPlay.Caption = "فعال";//resourseMng.GetString("UnActive") ;
            else EditibleItemPlay.Caption = "غیر فعال"; //resourseMng.GetString("Active"); 
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.SaveDialog, "Album2");
            if (!string.IsNullOrEmpty(fileName))
            {
                App.Setting.MetaDataPath = fileName;
                Serializer.DESSerialize(PList, App.Setting.MetaDataPath);
                string lastPicDir= App.PicDir;
                App.SetPicDir();
                BackUp.DirectoryCopy(lastPicDir, App.PicDir, false);
                App.Setting.SaveAppSetting();
                //Init();
                SetAlbumName();
                RefreshData();
                Application.DoEvents();
            }

            //clear();
            //App.Setting.MetaDataPath = fileName;
            //Serializer.DESSerialize(PList, App.Setting.MetaDataPath);
            //App.SetPicDir();
            //App.Setting.SaveAppSetting();
            ////Init();
            //SetAlbumName();
            //RefreshData();
            //Application.DoEvents();
        }






        internal Chapter GetnextChapter(long EndChpterPostion)
        {
           
            var cList = (from c in CurrentPlaylistItem.Chapters where c.Selected == true select c).ToList();
            return cList.FirstOrDefault(c => c.StartPosition >= EndChpterPostion);
            
        }

        private void SelectedCheckEdit_CheckStateChanged(object sender, EventArgs e)
        {
           
           // bool value = Convert.ToBoolean((sender as DevExpress.XtraEditors.CheckEdit).EditValue);
            Application.DoEvents();

        }

        private void joinFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            VideoEditor.Join.Form1 frm = new VideoEditor.Join.Form1();
            frm.ShowDialog();
        }
    }




    //public class PlayListTest
    //{
    //    public string FileName;
    //    public long? start;
    //    public long? end;
    //}
}
