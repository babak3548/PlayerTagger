using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace Player.DataControl
{
    public partial class PlayerControl : UserControl, IPlayerControl
    {



        public PlayerControl()
        {
            InitializeComponent();
          
        }

        public virtual  void Dispose()
        {
            //Controls.Clear(); 
            //base.Dispose();
        }

        //~PlayerControl()
        //{
        //Controls.Clear(); 
        //    GC.Collect();
        //}

        #region private

        private void PreviousFrame_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            AbsPreviousFrame();
        }

        private void NextFrame_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            AbsNextFrame();
        }

        private void SlowPlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            AbsSlowPlay();
        }

        private void NormalPlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            AbsNormalPlay();
        }

        private void FasterPlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            AbsFasterPlay();
        }


        private void barBtnPlay_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            Play();
        }

        private void barBtnPuse_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            Pause();


        }

        private void barBtnStop_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            Stop();
        }

        private void barBtnShut_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            //  Shut();
        }


        private void barBtnPlay_ItemClick_1(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {


        }


        private void FullScereen_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            TaggelFullScereen();
        }

        private void Mute1_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            Mute();
        }
        private void playItem_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            barBtnPlay.Down = false;

            Play();
        }
        #endregion private






        #region protected Method

        protected virtual long StartPosition { get; set; }
        protected virtual long? EndChapterPosition { get; set; }
        public static  long TotalDuritionFile { get; set; }


        virtual protected void Play()
        {
            //throw new NotImplementedException();
        }

        virtual protected void AbsPreviousFrame()
        {
           // throw new NotImplementedException();
        }
        virtual protected void AbsNextFrame()
        {
            //throw new NotImplementedException();
        }
        virtual protected void AbsSlowPlay()
        {
          //  throw new NotImplementedException();
        }
        virtual protected void AbsNormalPlay()
        {
           // throw new NotImplementedException();
        }
        virtual protected  void AbsFasterPlay()
        {
          //  throw new NotImplementedException();
        }

        virtual protected void TaggelFullScereen()
        {
            ///اسکرین کنترولر جاری را می دهد
            Screen screen = Screen.FromControl(this);
            var preantFrm= ((this.Parent) as System.Windows.Forms.Form);

            if (preantFrm.FormBorderStyle == System.Windows.Forms.FormBorderStyle.None)
            {
                preantFrm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
               ///از ابجکت اسکرین ابعاد فرم را ست می کند
                preantFrm.Bounds = screen.WorkingArea;
                    //new Rectangle(150, 150, 400, 350);
            }
            else
            {
                preantFrm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
                preantFrm.Bounds = screen.Bounds;
            }

        }
        protected bool ThumbnailCallback()
        {
            return true;
        }

        #endregion protected Method




        #region  public

       // public static bool ContinuePaly { get; set; }
        public static bool ShutPlay { get; set; }
        public static Player.MediaPlayer  mediaPlayer { get; set; }
     //   public static bool PlayOnlyCheckList { get; set; }
        public virtual bool IsPlaying { get{return false;} }

        public virtual long CurrentPostion
        {
            get { return 0; }
           // set{}
        }



        public virtual int X { get; set; }
        public virtual int Y { get; set; }
        public virtual int WidthRect { get; set; }
        public virtual int HeightRect { get; set; }

        public virtual void Play(PlaylistItem item)
        {
           
        }

        public virtual void Play(Chapter item)
        {
            
        }


        public virtual void Play(string FileName, long? start, long? end)
        {
        }

        public virtual void Mute()
        {
        }
        public virtual Image GetImageScreen()
        {
            return null;
        }

        public virtual void Stop()
        {
            trkPosition.Value = 0;
        }

        public virtual  void Pause()
        {
           
        }

        public virtual void Clean()
        {
            
        }
        #endregion public






















    }
}
