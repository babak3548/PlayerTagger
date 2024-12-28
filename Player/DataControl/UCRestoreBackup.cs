using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace Player.DataControl
{
    public partial class UCRestoreBackup : UserControl
    {
        RestoreBackUp _restoreBackUp;
        ComponentResourceManager resourceMng = new ComponentResourceManager(typeof(UCBackUp));

        public UCRestoreBackup()
        {
            InitializeComponent();
        }



        private void btnStartBackUp_Click(object sender, EventArgs e)
        {
            if (txtBackUpPath.Text == "" || TxtRestore.Text == "") XtraMessageBox.Show("plase enter Paths ");
            else
            {
               
               // Form.CheckForIllegalCrossThreadCalls = false;
               // DevExpress.Data.CurrencyDataController.DisableThreadingProblemsDetection = true;
              //  UISync.ExecuteBackground(bc_DoWork, resourceMng.GetString("OperationName"), resourceMng.GetString("BackUpWait"));

                _restoreBackUp = new RestoreBackUp(TxtRestore.Text, txtBackUpPath.Text);
                Form.CheckForIllegalCrossThreadCalls = false;
                DevExpress.Data.CurrencyDataController.DisableThreadingProblemsDetection = true;
              //  Program.form1.playerControl1.Pause();
                UISync.ExecuteBackground(bc_DoWork, resourceMng.GetString("OperationRestoreName"), resourceMng.GetString("BackUpWait"));
              
               
               
            }
        }
        string msg = "";
        void bc_DoWork(DoWorkEventArgs e)
        {
            msg = _restoreBackUp.StartRestorBackUp();
            e.Result = msg;
        }

        private void btnFolderBrowser_Click_1(object sender, EventArgs e)
        {
            //var fileName = Player.ObjectHelper.GetAlbumFileName(ObjectHelper.DialogType.SaveDialog, "Album1");
   
            txtBackUpPath.Text = Player.ObjectHelper.GetFolderName();
        }

        private void btnRestore_Click(object sender, EventArgs e)
        {
           // folderBrowserDialog2.ShowDialog();
            TxtRestore.Text = Player.ObjectHelper.GetFolderName();
         
        }

        private void btnCancel_Click_1(object sender, EventArgs e)
        {
            _restoreBackUp.Cancel = true;
        }

        private void TxtRestore_EditValueChanged(object sender, EventArgs e)
        {

        }


    }
}
