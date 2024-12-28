using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Player.DataControl;
using System.IO;
using Player.Setting;

namespace Player.Forms
{
    public partial class SecondPlayWindows : DevExpress.XtraEditors.XtraForm
    {
        public PlayerControl playerControl1 = new PlayerControl();
        private Factory Factory = new Factory();
        // = new VLCPlayer();
        public SecondPlayWindows()
        {
            InitializeComponent();

        }

        public void DoEvents()
        {
            Application.DoEvents();
        }

        private void SecondPlayWindows_FormClosed(object sender, FormClosedEventArgs e)
        {
        }

        private void SecondPlayWindows_FormClosing(object sender, FormClosingEventArgs e)
        {
            MediaPlayer.FlagSecondPlayWindowsForm = false;
            // MediaPlayer.PlayerControlCurrentPlayItem = null;
            this.playerControl1.Stop();
            this.playerControl1.Dispose();
        }



        private void SecondPlayWindows_Load(object sender, EventArgs e)
        {
            var mediaPlayer = this.Owner as MediaPlayer;
            AddPlayerControl(mediaPlayer.CurrentItem);
            playerControl1.Mute();

            if (playerControl1 is picturePlayer)
            {
                if (mediaPlayer.CurrentItem is Chapter)
                {
                    playerControl1.Play(mediaPlayer.CurrentItem as Chapter);
                }
                else if (mediaPlayer.CurrentItem is PlaylistItem)
                {
                    playerControl1.Play(mediaPlayer.CurrentItem as PlaylistItem);
                }
            }
            else if( playerControl1 is VLCPlayer)
            {
                if (mediaPlayer.playerControl1.IsPlaying)
                {
                    if (mediaPlayer.CurrentItem is Chapter)
                    {
                        (mediaPlayer.CurrentItem as Chapter).StartPosition = mediaPlayer.playerControl1.CurrentPostion; ;
                        playerControl1.Play(mediaPlayer.CurrentItem as Chapter);
                    }
                    if (mediaPlayer.CurrentItem is PlaylistItem)
                    {
                        //عدد 600 برای سنکرون کردن دو پلیر باهم است
                        playerControl1.Play((mediaPlayer.CurrentItem as PlaylistItem).MediaSource, (mediaPlayer.playerControl1.CurrentPostion + 600), long.MaxValue);
                    }
                }
            }
        }

        public void Play(PlaylistItem CurrentItem)
        {
            AddPlayerControl(CurrentItem);
            playerControl1.Play(CurrentItem);
        }
        public void Play(Chapter CurrentItem)
        {
            AddPlayerControl(CurrentItem);
            playerControl1.Play(CurrentItem);
        }

        private void AddPlayerControl(object CurrentItem)
        {
            try
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
                    Controls.Clear();
                    playerControl1.Dock = DockStyle.Fill;
                    Controls.Add(playerControl1);
                }
                if (playerControl1 is VLCPlayer)
                {
                    playerControl1.FullScereen.Visibility = DevExpress.XtraBars.BarItemVisibility.Always;
                }
            }
            catch (Exception ex)
            {
                
                throw;
            }

        }
    }
}
