using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Player.DataControl
{
    public partial class MediaPlayer : PlayerControl 
    {
        public MediaPlayer()
        {
            InitializeComponent();
        }


        #region public or Interface Implement
        public override long CurrentPostion
        {
          
            get { return long.Parse( mediaPlyerCtrl.Ctlcontrols.currentPosition.ToString())  ; }
           
        }

        public override void Play(PlaylistItem playListItem)
        {
            mediaPlyerCtrl.URL = playListItem.MediaSource;
            Play();


        }

        public override void Play(Chapter chapter)
        {

            mediaPlyerCtrl.Ctlcontrols.currentPosition  = chapter.StartPosition.Value ;
            Play();

        }

        public override Image GetImageScreen()
        {
            Image bmp;
            Point StartPoint = mediaPlyerCtrl.PointToScreen(new Point(0, 0));// new Point(PlayerControl.Location.X + this.DesktopLocation.X + 50, PlayerControl.Location.Y + this.DesktopLocation.Y + 65);
            Rectangle bounds = mediaPlyerCtrl.ContainingControl.DisplayRectangle;
            bmp = ScreenShot.GetFlushedImage(mediaPlyerCtrl.PreferredSize, App.Setting.HorizontalResolution, App.Setting.VerticalResolution, StartPoint, Point.Empty, bounds).GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero);
            return bmp;
        }


        public override void Dispose()
        {
            Stop();
            mediaPlyerCtrl = null;
            Controls.Clear();
            base.Dispose(Disposing);
        }


        public override void Stop()
        {
            mediaPlyerCtrl.Ctlcontrols.stop();
        }

        public override void Pause()
        {
             mediaPlyerCtrl.Ctlcontrols.pause();
        }

        #endregion public or Interface Implement





        #region protected


        protected override void Play()
        {
            mediaPlyerCtrl.Ctlcontrols.play();
       

        }
        protected override void AbsPreviousFrame()
        {

        }
        protected override void AbsNextFrame()
        {

        }
        protected override void AbsSlowPlay()
        {
            mediaPlyerCtrl.Ctlcontrols.fastReverse();
        //    if (mediaPlyerCtrl.input.rate > 0.25) mediaPlyerCtrl.input.rate -= 0.25;
        }
        protected override void AbsNormalPlay()
        {
            mediaPlyerCtrl.Ctlcontrols.play();
        }
        protected override void AbsFasterPlay()
        {
            mediaPlyerCtrl.Ctlcontrols.fastForward();
         //   if (mediaPlyerCtrl.input.rate < 5) mediaPlyerCtrl.input.rate += 1;
        }
        #endregion protected




        #region private

        private void mediaPlyerCtrl_PositionChange(object sender, AxWMPLib._WMPOCXEvents_PositionChangeEvent e)
        {
            var x1 = mediaPlyerCtrl.Ctlcontrols.currentPosition;
            var x2 = mediaPlyerCtrl.Ctlcontrols.currentItem;
            var x3 = mediaPlyerCtrl.currentMedia;
            var x4 = mediaPlyerCtrl.currentPlaylist.Item[0];
            var x5 = mediaPlyerCtrl.currentMedia.duration;
            //   trkPosition.Value = (int)e.newPosition;
        }


        #endregion private

        private void mediaPlyerCtrl_OpenStateChange(object sender, AxWMPLib._WMPOCXEvents_OpenStateChangeEvent e)
        {
         //if(mediaPlyerCtrl.openState ==WMPLib.WMPOpenState.wmposMediaOpen )       
         //    trkPosition.Properties.Maximum = Convert.ToInt32(mediaPlyerCtrl.Ctlcontrols.currentItem.duration);
        }

        private void mediaPlyerCtrl_MediaError(object sender, AxWMPLib._WMPOCXEvents_MediaErrorEvent e)
        {

        }

        private void mediaPlyerCtrl_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {

        }


    }
}
