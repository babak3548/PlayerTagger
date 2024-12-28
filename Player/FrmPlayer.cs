using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;

namespace Player
{
    public partial class FrmPlayer : Form
    {
        private PlaylistItem CurrentItem;
        public FrmPlayer()
        {
            InitializeComponent();
        }
        public void GetFile()
        {
           
             if( OpenFile.ShowDialog()== DialogResult.OK && OpenFile.FileName != "")
            {
                CurrentItem = new PlaylistItem(OpenFile.FileName, "", OpenFile.FileName);
                 MediabindingSource.DataSource = CurrentItem.Chapters;
                 PlayerControl.URL = OpenFile.FileName;
               
            }
           
       
        }
        public void BookMark()
        {
            Bitmap bmp;
            Point StartPoint = new Point(PlayerControl.Location.X + this.DesktopLocation.X+50, PlayerControl.Location.Y + this.DesktopLocation.Y+65);
            Rectangle bounds = PlayerControl.Bounds;
            bmp = ScreenShot.CaptureImage(StartPoint, Point.Empty, bounds);
            CurrentItem.Chapters.Add(new Chapter(long.Parse(PlayerControl.Ctlcontrols.currentPosition.ToString()), PlayerControl.Ctlcontrols.currentPositionString, "", "", bmp.GetThumbnailImage(80,80,ThumbnailCallback,IntPtr.Zero)));
            MediabindingSource.ResetBindings(false);
            bmp.Dispose();
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
             DialogResult CloseMessage ; 
            CloseMessage = MessageBox.Show("Are you sure you want to close?","",MessageBoxButtons.YesNo);
            if(CloseMessage == DialogResult.Yes)
                PlayerControl.Ctlcontrols.stop();
        
            if (CloseMessage == DialogResult.No )
                e.Cancel = true;
       
        }

        private void FrmPlayer_Load(object sender, EventArgs e)
        {
            PlayerControl.settings.autoStart = true;
            PlayerControl.settings.enableErrorDialogs = false;
            PlayerControl.enableContextMenu = false;
            PlayerControl.settings.balance = 25;
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
            //if (MediabindingSource.Current != null)
            //    PlayerControl.Ctlcontrols.currentPosition = ((Chapter)MediabindingSource.Current).StartPosition;
            //PlayerControl.Ctlcontrols.play();
        }

        
    }
}
