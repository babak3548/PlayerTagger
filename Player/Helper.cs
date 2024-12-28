using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Diagnostics;
using DevExpress.XtraEditors;
using System.Windows.Forms;
using System.ComponentModel;

namespace Player
{
    public class UISync
    {
        private static ISynchronizeInvoke Sync;
         
        public static void Init(ISynchronizeInvoke sync)
        {
            Form.CheckForIllegalCrossThreadCalls = false;
            DevExpress.Data.CurrencyDataController.DisableThreadingProblemsDetection = true;
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
        private static Player.Forms.WaitFrm wFrm = new Forms.WaitFrm();
        public delegate void BackgroundAction(DoWorkEventArgs e);
        public static void ExecuteBackground(BackgroundAction action, string WfrmCaption="", string WfrmDescription="")
        {
            CurrentAction = action;
            BackgroundWorker bc = new BackgroundWorker();
            bc.DoWork += bc_DoWork;
            bc.RunWorkerCompleted += new RunWorkerCompletedEventHandler(bc_RunWorkerCompleted);
           
            bc.RunWorkerAsync();
            wFrm.SetDescription(WfrmDescription);
            wFrm.SetCaption(WfrmCaption);
            wFrm.ShowDialog();

        }
        static void bc_DoWork(object sender, DoWorkEventArgs e)
        {
           
            if (CurrentAction != null) CurrentAction(e);
        }
        static void bc_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            wFrm.Close();
            ComponentResourceManager resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
            if (e.Result.ToString().Contains("Not_Success_Operation"))
                XtraMessageBox.Show(resourseMng.GetString("Not_Success_Operation"), "خطا", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
                XtraMessageBox.Show(resourseMng.GetString(e.Result.ToString()), "پیغام", MessageBoxButtons.OK, MessageBoxIcon.Information);
            //resourseMng.GetString(e.Result.ToString())
        }

    
    }

    public class ImageCreator
    {
        public static Image CreateImage(Image srcImage, int maxWidth, int maxHeight)
        {
            if (srcImage == null) return null;
            Size size = GetPhotoSize(srcImage, maxWidth, maxHeight);
            Image ret = new Bitmap(size.Width, size.Height);
            using (Graphics gr = Graphics.FromImage(ret))
            {
                gr.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                gr.DrawImage(srcImage, new Rectangle(0, 0, size.Width, size.Height));
            }
            return ret;
        }
        static Size GetPhotoSize(Image image, int maxWidth, int maxHeight)
        {
            int width = Math.Min(maxWidth, image.Width),
                height = width * image.Height / image.Width;
            if (height > maxHeight)
            {
                height = maxHeight;
                width = height * image.Width / image.Height;
            }
            return new Size(width, height);
        }
        public static Rectangle GetZoomDestRectangle(Rectangle r, Image img)
        {
            float horzRatio = Math.Min((float)r.Width / img.Width, 1);
            float vertRatio = Math.Min((float)r.Height / img.Height, 1);
            float zoomRatio = Math.Min(horzRatio, vertRatio);

            return new Rectangle(
                r.Left + (int)(r.Width - img.Width * zoomRatio) / 2,
                r.Top + (int)(r.Height - img.Height * zoomRatio) / 2,
                (int)(img.Width * zoomRatio),
                (int)(img.Height * zoomRatio));
        }
    }
    public class ObjectHelper
    {
     public   enum DialogType
	{
	     OpenDialog,   
        SaveDialog,

	}
        public static void ShowWebSite(string url)
        {
            if (url == null) return;
            string processName = url.Replace(" ", string.Empty);
            if (processName.Length == 0) return;
            const string protocol = "http://";
            const string protocol2 = "https://";
            if (processName.IndexOf(protocol) != 0 && processName.IndexOf(protocol2) != 0)
                processName = protocol + processName;
            StartProcess(processName);
        }
        public static void StartProcess(string processName)
        {
            try
            {
                Process.Start(processName);
            }
            catch (Exception ex)
            {
                XtraMessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
       
        public static void SetFormContainerSize(Form form, Control control)
        {
            form.StartPosition = FormStartPosition.Manual;
            form.Size = control.Size;
            form.Location = control.FindForm().PointToScreen(control.Location);
        }
        public static void ShowFormDialog(Form form, Form parent)
        {
            try
            {
                parent.Enabled = false;
                form.ShowDialog(parent);
            }
            finally
            {
                parent.Enabled = true;
            }
        }
        public static void OpenExportedFile(string fileName)
        {
            if (XtraMessageBox.Show("ExportFileOpen", "Export", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                Process process = new Process();
                try
                {
                    process.StartInfo.FileName = fileName;
                    process.Start();
                }
                catch { }
            }
        }
        public static void ShowExportErrorMessage()
        {
            XtraMessageBox.Show("ExportError", "Export", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        public static string GetPossibleFileName(string name) { return name.Replace("/", ""); }
        public static string GetFolderName(string selectedPath="")
        {
            System.Windows.Forms.FolderBrowserDialog  dialog;
            dialog = new FolderBrowserDialog();
            dialog.SelectedPath = selectedPath;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                return dialog.SelectedPath;
            }
            return String.Empty;
        }

        public static string GetFileName(string extension, string filter, DialogType dg = DialogType.SaveDialog, string fileName = "", string InitialDirectory = "", bool checkExt = false, string title="")
        {
               System.Windows.Forms.FileDialog dialog;
               if (dg == DialogType.SaveDialog) dialog = new SaveFileDialog();
               else dialog = new OpenFileDialog();
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
                    if (checkExt && !string.IsNullOrEmpty(extension) && dialog.FileName.ExtOfFile() !=("."+ extension))
                    {
                        XtraMessageBox.Show("Invalid file type", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return String.Empty;
                    }

                    return dialog.FileName;
                }
            return String.Empty;
        }

        public static string GetAlbumFileName(DialogType dg = DialogType.SaveDialog, string fileName = "", string title = "")
        {
            string ext = "(*." + App.ExtentionAlbum + ")|*." + App.ExtentionAlbum;
            return GetFileName(App.ExtentionAlbum,ext,dg,fileName,App.Setting.DefaulMetaDataPath,true,title);
        }
        internal static string GetArticleByWord(string word)
        {
            if (string.IsNullOrEmpty(word)) return string.Empty;
            string firstLetter = word.Substring(0, 1).ToLower();
            if (firstLetter == "a") return "an";
            return "a";
        }
    }
}
