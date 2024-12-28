using DevExpress.XtraEditors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Utility
{
    public class Helper
    {
        private static ISynchronizeInvoke Sync;

        public static void Init(ISynchronizeInvoke sync)
        {
           // Form.CheckForIllegalCrossThreadCalls = false;
          //  DevExpress.Data.CurrencyDataController.DisableThreadingProblemsDetection = true;
            Sync = sync;
        }

        public static void Execute(Action action)
        {
            //try
            //{
            Sync.BeginInvoke(action, null);
            //}
            //catch (Exception ex)
            //{
            //    XtraMessageBox.Show(ex.ToString(), "", MessageBoxButtons.OK, MessageBoxIcon.Error);

            //}

        }
        private static BackgroundAction CurrentAction;
       // private static Player.Forms.WaitFrm wFrm = new Forms.WaitFrm();
        public delegate void BackgroundAction(DoWorkEventArgs e);
        public static void ExecuteBackground(BackgroundAction action, string WfrmCaption = "", string WfrmDescription = "")
        {
            CurrentAction = action;
            BackgroundWorker bc = new BackgroundWorker();
            bc.DoWork += bc_DoWork;
            bc.RunWorkerCompleted += new RunWorkerCompletedEventHandler(bc_RunWorkerCompleted);

            bc.RunWorkerAsync();
          //wFrm.SetDescription(WfrmDescription);
          // wFrm.SetCaption(WfrmCaption);
          //  wFrm.ShowDialog();

        }
        static void bc_DoWork(object sender, DoWorkEventArgs e)
        {

            if (CurrentAction != null) CurrentAction(e);
        }
        static void bc_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
           // wFrm.Close();
            //ComponentResourceManager resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
            //XtraMessageBox.Show(resourseMng.GetString(e.Result.ToString()), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        public static string GetFileName(string extension, string filter,  string fileName = "", string InitialDirectory = "", bool checkExt = false, string title = "")
        {
            System.Windows.Forms.FileDialog dialog;
            //if (dg == DialogType.SaveDialog) 
                dialog = new SaveFileDialog();
           // else dialog = new OpenFileDialog();
            if (title != "") { dialog.Title = title; }
            dialog.Filter = filter;
            dialog.FileName = fileName;
            dialog.DefaultExt = extension;
            dialog.InitialDirectory = InitialDirectory;
            dialog.FilterIndex = 2;
            dialog.AddExtension = true;
            dialog.RestoreDirectory = true;


            if (dialog.ShowDialog() == DialogResult.OK)
            {
                if (checkExt && !string.IsNullOrEmpty(extension) && dialog.FileName.ExtOfFile() != ("." + extension))
                {
                    XtraMessageBox.Show("Invalid file type", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return String.Empty;
                }

                return dialog.FileName;
            }
            return String.Empty;
        }

        //public static void WriteFile(string fullFileName,string strContent)
        //{
            
        //}
    }
}
