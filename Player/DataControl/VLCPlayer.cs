using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Player.Setting;
using Declarations;
using Declarations.Players;
using Declarations.Media;
using Implementation;
using Declarations.Events;
using System.IO;
using DevExpress.XtraEditors;

namespace Player.DataControl
{
    public partial class VLCPlayer : PlayerControl, IPlayerControl
    {
        public string TimePositionLabel
        {
            get { return barLblCurrentTime.Caption; }
            set { barLblCurrentTime.Caption = value; }
        }
       // int static LengthFile

        IMediaPlayerFactory m_factory;
        IDiskPlayer m_player;
        IMedia m_media;


        public VLCPlayer()
        {
            InitializeComponent();
            string[] args = new string[]
                           {
                               "-I",
                               "dumy",
                               "--ignore-config",
                               "--no-osd",
                               "--disable-screensaver",
                               "--ffmpeg-hw",
                               "--plugin-path=./plugins",
                               "--vout-filter=clone", // <= new options here
                               "--clone-count=2"
                           };
            //string[] args = new string[] 
            // {
            //    "-I", 
            //    "dumy",  
            //    "--ignore-config", 
            //    "--no-osd",
            //    "--disable-screensaver",
            //    "--ffmpeg-hw",
            //    "--plugin-path=./plugins" 
            // };
            m_factory = new MediaPlayerFactory(args);
            m_player = m_factory.CreatePlayer<IDiskPlayer>();

            //  m_player.Events.PlayerPositionChanged += new EventHandler<MediaPlayerPositionChanged>(Events_PlayerPositionChanged);
            m_player.Events.TimeChanged += new EventHandler<MediaPlayerTimeChanged>(Events_TimeChanged);
            m_player.Events.MediaEnded += new EventHandler(Events_MediaEnded);
            m_player.WindowHandle = panel1.Handle;
            CmdTrkVolume.EditValue = App.Setting.VolumeValue;
            
            UISync.Execute(() => m_player.Volume = App.Setting.VolumeValue);
            // init();
        }

        void Events_MediaEnded(object sender, EventArgs e)
        {
            // m_factory.
            Stop();
        }

        // const int DivValue = 200;
        void Events_TimeChanged(object sender, Declarations.Events.MediaPlayerTimeChanged e)
        {
            lock (trkPosition)
            {
                trkPosition.ValueChanged -= new EventHandler(trkPosition_ValueChanged);
                long PCT = m_player.Time;
                trkPosition.Value = PCT.ToPsistionValue(TotalDuritionFile);
                // if (TotalDuritionFile <= PCT) Stop(); 
                PauseEndChapter(PCT);
                TimePositionLabel = PCT.MeliSecToTimeString();
                trkPosition.ValueChanged += new EventHandler(trkPosition_ValueChanged);

            }


        }



        private void trkPosition_Scroll(object sender, EventArgs e)
        {

        }

        private void trkPosition_ValueChanged(object sender, EventArgs e)
        {
            m_player.Events.TimeChanged -= new EventHandler<MediaPlayerTimeChanged>(Events_TimeChanged);
          //  if (trkPosition.Value != null && TotalDuritionFile != null)
          //  {
                UISync.Execute(() => m_player.Time = trkPosition.Value.ToTimePlayerValue(TotalDuritionFile));
           // }
            m_player.Events.TimeChanged += new EventHandler<MediaPlayerTimeChanged>(Events_TimeChanged);
        }

        const int MeliSecond = 1000;
        #region public or Interface Implement
        public override long CurrentPostion
        {
            get { return m_player.Time; }
            //set {UISync.Execute(() => m_player.Time = value); }

        }
        public override bool IsPlaying { get { return m_player.IsPlaying; } }


        public override void Mute()
        {
            UISync.Execute(() => m_player.Mute = m_player.Mute ^ true);
            if (!m_player.Mute) { Mute1.Caption = "بی صدا"; Mute1.ImageIndex = 9; }
            else { Mute1.Caption = "باصدا"; Mute1.ImageIndex = 8; }
        }



        public override void Play(Chapter chapter)
        {
            EndChapterPosition = chapter.EndPosition == null ? long.MaxValue : chapter.EndPosition;
            Play(chapter.SourceMedia.MediaSource, chapter.StartPosition, EndChapterPosition.Value);
        }
        public override void Play(PlaylistItem playListItem)
        {

            Play(playListItem.MediaSource, 0, long.MaxValue);
          //  m_player.Length

        }

        public override void Play(string FileName, long? start, long? end)
        {

            UISync.Execute(() => m_player.Pause());

            EndChapterPosition = end;
            // if(m_media!=null)m_media.Dispose();
            if (m_media == null || m_media.Input != FileName)
            {
                m_media = m_factory.CreateMedia<IMedia>(FileName);
                UISync.Execute(() => m_player.Open(m_media));
            }

            //m_media.Parse(false);

            playItem.ImageIndex = 1;

            UISync.Execute(() => m_player.Play());
            UISync.Execute(() => m_player.Time = (start.Value));
            if (m_player.PlaybackRate != 1) AbsNormalPlay();
            m_media.Events.DurationChanged += new EventHandler<MediaDurationChange>(Events_DurationChanged);

            Application.DoEvents();
            //  reset();

        }
        void Events_DurationChanged(object sender, MediaDurationChange e)
        {
            TotalTime = e.NewDuration;
            TotalDuritionFile = TotalTime;
            barLblTootalTime.Caption = TotalTime.MeliSecToTimeString();
        }
        public void reset()
        {
            bar1.DockStyle = DevExpress.XtraBars.BarDockStyle.None;
            bar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Standalone;
            bar1.StandaloneBarDockControl = standaloneBarDockControl1;
        }

        public override Image GetImageScreen()
        {

            Image bmp;
            Point StartPoint = panel1.PointToScreen(new Point(0, 0));
            Rectangle bounds = panel1.DisplayRectangle;
            Size sz = panel1.PreferredSize;
            bmp = ScreenShot.GetFlushedImage(bounds.Size, App.Setting.HorizontalResolution, App.Setting.VerticalResolution, StartPoint, Point.Empty, bounds).GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero);
            return bmp;

        }


        public override void Dispose()
        {

            UISync.Execute(() => m_player.Dispose());
        }


        public override void Stop()
        {
            base.Stop();
            UISync.Execute(() => m_player.Stop());
            playItem.ImageIndex = 0;
        }


        public override void Pause()
        {
            if (m_player.IsPlaying)
            {
                UISync.Execute(() => m_player.Pause());
                playItem.ImageIndex = 0;
            }
        }

        public override void Clean()
        {
            Stop();
            m_media = m_factory.CreateMedia<IMedia>("");
            UISync.Execute(() => m_player.Open(m_media));


        }


        #endregion public or Interface Implement





        #region protected


        protected override void Play()
        {
            if (m_player.IsPlaying)
            { Pause(); }
            else
            {
                EndChapterPosition = long.MaxValue;
                UISync.Execute(() => m_player.Play());
               playItem.ImageIndex = 1;
            }

        }
        protected override void AbsPreviousFrame()
        {
           
        }
        protected override void AbsNextFrame()
        {
            UISync.Execute(() => m_player.NextFrame());
        }
        protected override void AbsSlowPlay()
        {
            if (m_player.PlaybackRate > 0.25) m_player.PlaybackRate -= ((float)0.25);
            SlowPlay.Hint = m_player.PlaybackRate.ToString() + "x";
            FasterPlay.Hint = "";
        }
        protected override void AbsNormalPlay()
        {
            m_player.PlaybackRate = 1;
            FasterPlay.Hint = "";
            SlowPlay.Hint = "";
        }
        protected override void AbsFasterPlay()
        {
            if (m_player.PlaybackRate < 5) m_player.PlaybackRate += 1;
            FasterPlay.Hint = m_player.PlaybackRate.ToString() + "x";
            SlowPlay.Hint = "";
        }


        #endregion protected




        #region private




       //
        private void PauseEndChapter(double CurrentPositionTime)
        {
            if (ShutPlay && EndChapterPosition <= CurrentPositionTime)
            {
                //if (ShutPlay)
                //{
                    Chapter nextchapter =mediaPlayer.GetnextChapter(EndChapterPosition.Value);
                    if (nextchapter != null)
                    {
                        UISync.Execute(() => m_player.Time = (nextchapter.StartPosition.Value));
                        EndChapterPosition = (nextchapter.EndPosition == null ? long.MaxValue : nextchapter.EndPosition.Value);
                    }
                    else
                    {
                        Pause();
                    }
             }
            else if (EndChapterPosition <= CurrentPositionTime) { EndChapterPosition = long.MaxValue; }


                // UISync.Execute(() => Pause());
                // find next start shot and set paly
                //end chapter new shot set 
                //if not new shot pause
            }

        



        #endregion private

        private long TotalTime = 0;
        private void InitVlcControler(long totalTime)
        {

            TotalDuritionFile = totalTime;
            trkPosition.Maximum = (int)totalTime;
            barLblTootalTime.Caption = totalTime.MeliSecToTimeString();
            
            // m_player.Volume = Convert.ToInt16(  CmdTrkVolume.EditValue );



        }

        private void TrkVolumeRepository_EditValueChanging(object sender, DevExpress.XtraEditors.Controls.ChangingEventArgs e)
        {
            App.Setting.VolumeValue = (int)e.NewValue;
            UISync.Execute(() => m_player.Volume = (int)e.NewValue);
        }



        private void trkPosition_BeforeShowValueToolTip(object sender, DevExpress.XtraEditors.TrackBarValueToolTipEventArgs e)
        {
            e.ShowArgs.ToolTip = ((long)trkPosition.Value).MeliSecToTimeString();
        }

        private void trkPosition_MouseDown(object sender, MouseEventArgs e)
        {
            double x = ((double)e.X / (double)trkPosition.Width) * (trkPosition.Maximum - trkPosition.Minimum);
            trkPosition.Value = Convert.ToInt32(x);
        }














    }

}



