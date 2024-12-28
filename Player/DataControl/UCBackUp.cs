using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using System.IO;

namespace Player.DataControl
{
    public partial class UCBackUp : UserControl
    {
        private BackUp _backUp;
        string destDirName = "";
        ComponentResourceManager resourceMng = new ComponentResourceManager(typeof(UCBackUp));
        public UCBackUp()
        {
            InitializeComponent();
        }

        private void btnFolderBrowser_Click(object sender, EventArgs e)
        {
          //  folderBrowserDialog1.ShowDialog();
          
            txtPath.Text = Player.ObjectHelper.GetFolderName();
        }

        private void btnStartBackUp_Click(object sender, EventArgs e)
        {
            if (txtPath.Text.Trim() != "" && TxtFolderBackName.Text.Trim() != "")
            {
                _backUp = new BackUp();
                 destDirName =  txtPath.Text.Trim()+"\\"+TxtFolderBackName.Text.Trim() ;
                if (!Directory.Exists(destDirName))
                {
                    Directory.CreateDirectory(destDirName);
                }
                UISync.ExecuteBackground(bc_DoWork, resourceMng.GetString("OperationName"), resourceMng.GetString("BackUpWait"));
                ((Player.Forms.BackUpForm)this.Parent).Close();
               
            }
            else XtraMessageBox.Show(resourceMng.GetString("Please_Select_Path_BackUp"),"",MessageBoxButtons.OK,MessageBoxIcon.Warning );
        }
        string msg = "";
        void bc_DoWork(DoWorkEventArgs e)
        {
            msg = _backUp.StartBackUp(destDirName);
          e.Result = msg;
        }


        private void btnCancel_Click(object sender, EventArgs e)
        {
            _backUp.Cancel = true;
        }

   


    }
}
