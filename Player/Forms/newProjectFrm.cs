using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Player.Forms
{
    public partial class newProjectFrm  : DevExpress.XtraEditors.XtraForm
    {
        Player.MediaPlayer MPF;
        //string fullFileName = "";
        public newProjectFrm()
        {
            InitializeComponent();
        }
       public void ShowDialog(Player.MediaPlayer mpf)
        {
            MPF = mpf;
            this.ShowDialog();
        }

        private void btnCreate_Click(object sender, EventArgs e)
        {
             string fullFileName="";
            MPF.playerControl1.Stop();
            if (txtFileName.Text != "" && txtAddress.Text != "")
            {
                fullFileName = txtAddress.Text +"\\"+ txtFileName.Text +"."+ App.ExtentionAlbum; ;
                if (System.IO.File.Exists(App.Setting.MetaDataPath))
                {
                    if (MPF.SaveProject() == "Cancel")
                    { return; }
                }
                if (!string.IsNullOrEmpty(fullFileName))
                {
                    MPF.clear();
                    App.Setting.MetaDataPath = fullFileName;
                    Serializer.DESSerialize(MPF.PList, App.Setting.MetaDataPath);
                    App.SetPicDir();
                    App.Setting.SaveAppSetting();
                    MPF.SetAlbumName();
                    MPF.RefreshData();
                    Application.DoEvents();
                }
            }
            this.Close();
        }

        private void btnShowdialog_Click(object sender, EventArgs e)
        {
           // txtAddress.Text = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.SaveDialog, "Album1", "ایجاد پروژه جدید");
            txtAddress.Text = Player.ObjectHelper.GetFolderName();
             
        }
    }
}
