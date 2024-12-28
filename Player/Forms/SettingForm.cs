using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using Player.Setting;

namespace Player
{
    public partial class SettingForm : DevExpress.XtraEditors.XtraForm
    {
        ComponentResourceManager ResourceMng = new ComponentResourceManager(typeof(SettingForm));
        public SettingForm()
        {
            InitializeComponent();
            DevExpress.XtraBars.Helpers.SkinHelper.InitSkinPopupMenu(SkinMenu);
        }

        private void SettingForm_Load(object sender, EventArgs e)
        {
            this.CenterToParent();
            appSettingBindingSource.DataSource = App.Setting;
            CombLanguge.Properties.DataSource = AppSetting.LanguageList;
           
            FillFiledForm();
        }



        private void FillFiledForm()
        {
            
            cmbPlayerType.Properties.DataSource = AppSetting.PlayerTypies;

           txtMetaDataFilePath.Text = App.Setting.MetaDataPath;
        }

        private void UpDateAppSetting()
        {
            //App.Setting.MetaDataPath=txtMetaDataFilePath.Text;
        }


        private void Save_Click(object sender, EventArgs e)
        {
            UpDateAppSetting();
            App.Setting.SaveAppSetting();
            XtraMessageBox.Show(ResourceMng.GetString("Save_Success"));
        }



        //private void button1_Click(object sender, EventArgs e)
        //{
        //    folderBrowserDialog1.ShowDialog();
        //    txtMetaDataFilePath.Text = folderBrowserDialog1.FileName;
        //}

        //private void txtMetaDataFilePath_Click(object sender, EventArgs e)
        //{
        //    folderBrowserDialog1.ShowDialog();
        //    txtMetaDataFilePath.Text = folderBrowserDialog1.FileName;
        //}

        private void txtMetaDataFilePath_Click_1(object sender, EventArgs e)
        {
           // folderBrowserDialog1.ShowDialog();
            string fileName = Player.ObjectHelper.GetFileName("","", ObjectHelper.DialogType.OpenDialog,null,txtMetaDataFilePath.Text);
            txtMetaDataFilePath.Text = fileName;
        }

        private void textEdit1_Click(object sender, EventArgs e)
        {
            string fileName = Player.ObjectHelper.GetFolderName( TxtEDefaultMetaDetaPath.Text);
            TxtEDefaultMetaDetaPath.Text = fileName;
        }


        private void tetEDefaultfilesPath_Click(object sender, EventArgs e)
        {
            string fileName = Player.ObjectHelper.GetFolderName( tetEDefaultfilesPath.Text);
            tetEDefaultfilesPath.Text = fileName;
        }
    }
}