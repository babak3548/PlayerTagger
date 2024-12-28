using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing.Drawing2D;

namespace Player.DataControl
{
    public partial class picturePlayer : PlayerControl ,IPlayerControl 
    {


        private Point RectStartPoint;
        private Rectangle Rect = new Rectangle();
        private Brush selectionBrush = new SolidBrush(Color.FromArgb(128, 72, 145, 220));
        private Graphics graphics;
        public picturePlayer()
        {
            InitializeComponent();
         
        }

        #region public
        public override bool IsPlaying { get { return true; } }
        public object CurrentItem;
        public override void Play(PlaylistItem item)
        {
            CurrentItem = item;
            var bmp = new Bitmap(item.MediaSource);
            using (bmp)
            {
                var bmp2 = new Bitmap(pictureBox1.Width, pictureBox1.Height);
                using (var g = Graphics.FromImage(bmp2))
                {
                    g.InterpolationMode = InterpolationMode.NearestNeighbor;
                //    g.DrawImage(bmp, new Rectangle(Point.Empty, bmp2.Size));
                    g.DrawImage(bmp, new Rectangle(Point.Empty, bmp.Size));
                    pictureBox1.Image = bmp2;
                }
            }
        }

        public override void Play(Chapter item)
        {
            CurrentItem = item;
            var bmp = new Bitmap(item.ThumbnailImage );
            using (bmp)
            {
                var bmp2 = new Bitmap(pictureBox1.Width, pictureBox1.Height);
                using (var g = Graphics.FromImage(bmp2))
                {
                    g.InterpolationMode = InterpolationMode.NearestNeighbor;
                    // g.DrawImage(bmp, new Rectangle(Point.Empty, bmp2.Size));
                     g.DrawImage(bmp, new Rectangle(Point.Empty, bmp.Size));
                    pictureBox1.Image = bmp2;
                }
            }
        }

        public override Image GetImageScreen()
        {
            Image img;

            Point StartPoint = pictureBox1.PointToScreen(   new  Point(X, Y));
            Rectangle bounds = new Rectangle(X,Y,WidthRect,HeightRect);
            if (bounds.Width == 0 || bounds.Height == 0) return null;
             img = ScreenShot.GetFlushedImage(bounds.Size, App.Setting.HorizontalResolution, App.Setting.VerticalResolution, StartPoint, Point.Empty , bounds).GetThumbnailImage(App.Setting.ThumbWidth, App.Setting.ThumbHeight, ThumbnailCallback, IntPtr.Zero);
             Application.DoEvents();
            return img;

        }


        public override void Dispose()
        {
            pictureBox1.Dispose();
            Controls.Clear();
            base.Dispose(Disposing);
        }

        public override void Stop()
        {
            pictureBox1.Image = null;
        }
        #endregion public


        #region private

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (CurrentItem is PlaylistItem) Play(CurrentItem as PlaylistItem);
            else if (CurrentItem is Chapter) Play(CurrentItem as Chapter);
            Application.DoEvents();
            RectStartPoint = e.Location;
            Invalidate();

        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            
            Point tempEndPoint = e.Location;
          
            X=Math.Min(RectStartPoint.X, tempEndPoint.X);
            Y = Math.Min(RectStartPoint.Y, tempEndPoint.Y);
            WidthRect = Math.Abs(RectStartPoint.X - tempEndPoint.X);
            HeightRect=Math.Abs(RectStartPoint.Y - tempEndPoint.Y);

            Rect = new Rectangle(X, Y, WidthRect , HeightRect );
            Invalidate(Rect);
            graphics = pictureBox1.CreateGraphics();

            
            if (Rect != null && Rect.Width > 0 && Rect.Height > 0)
            {
                graphics.DrawRectangle(new Pen(selectionBrush), Rect); // FillRectangle(selectionBrush, Rect);
            }

            //Application.DoEvents();

        }

        #endregion private
    }
}
