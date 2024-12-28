using DevExpress.XtraEditors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Utility;


namespace VideoEditor
{
    public partial class FfmpegSplit : DevExpress.XtraEditors.XtraForm
    {

        /**/
        //  public static Ffmpeg ffmpeg;
        float durationTime = 0.00F;
        float currentTime = 0.00F;
        public string Arguments = "";
        private string ffmpeg_exePath;
        private string ConcatTempPath;
        private string TempFolderPath;
        private List<string> listFileInconcat;
        ProgressForm2 PF2;

        public static List<SpliteShutInfo> ListSpliteShutInfo;

        public string OutPutFullFileName { get; set; }

        public FfmpegSplit()
        {
            InitializeComponent();
            PF2 = new ProgressForm2();
            // Arguments = @"-i ""C:\myfile.mpg"" -ar 22050 -ab 32 -f flv -s 320×240 -aspect 4:3 -y somemove.flv";
            ffmpeg_exePath = Path.Combine(Application.StartupPath, "ffmpeg.exe");
            if (ListSpliteShutInfo == null) ListSpliteShutInfo = new List<SpliteShutInfo>();
            ConcatTempPath = Path.Combine(Application.StartupPath, "ConcatTemp");
            TempFolderPath = Path.Combine(Application.StartupPath, "TempFolder");
            // ConvertTempPath = Path.Combine(Application.StartupPath, "ConvertTemp");
            listFileInconcat = new List<string>();
            readyTempPath(ConcatTempPath);
            readyTempPath(TempFolderPath);
        }


        public void spliteAShut(List<SpliteShutInfo> SpliteShutInfoList, string OutputPath)
        {

            foreach (var item in SpliteShutInfoList)
            {

                Arguments = "-i " + item.inputFile + " -ss " + item.startTime + " -t " + item.SliceTime + " -c copy " + OutputPath;
                StartProcess();
            }

        }

        public void spliteListShut(List<SpliteShutInfo> SpliteShutInfoList, string OutPath, string OutFileName, string OutFormat)
        {
            int i = 0;
            foreach (var item in SpliteShutInfoList)
            {

                Arguments = "-i \"" + item.inputFile + "\" -ss " + item.startTimeInCuter + " -t " + item.SliceTimeInCuter + " -c copy \"" + OutPath
                    + "\\" + OutFileName + i + "." + OutFormat + "\"";
                StartProcess();
                i++;
            }

        }

        public bool Convert(List<string> listFile, string formatFileName, string OutputPath)
        {
            //string argFfmgeg;
            try
            {
                foreach (var item in listFile)
                {
                    Arguments = "ffmpeg -i  " + item + " " + OutputPath + formatFileName;
                    StartProcess();
                    UpdateProgress2();
                }
                return true;
            }
            catch (Exception ex)
            {
                return false;

            }
        }

        public bool Concat()
        {
           string ExtOutFile=OutPutFullFileName.ExtOfFile().ToLower();
            try
            {
                if (ExtOutFile == "mpg" | ExtOutFile == "ts") GenArgMpg();
                else GenArgAviMp4();
                StartProcess();
                return true;
            }
            catch (Exception ex)
            {
                return false;

            }
        }

        private void GenArgMpg()
        {
            Arguments = "-i \"concat:";
            foreach (var item in listFileInconcat)
            {
                if (item != listFileInconcat.LastOrDefault())
                    Arguments += item + "|";
                else
                    Arguments += item;
            }
            Arguments += "\" -c copy \"" + OutPutFullFileName + "\"";
        }

        private void GenArgAviMp4()
        {
            //\\ConcatFiles.txt
            string tempFullFileName = TempFolderPath + "\\myList.txt";
            string strContent = "";
            //-f concat -i "E:\temp\test.txt" -c copy "E:\temp\res1.avi"
            Arguments = "-f concat -i \"" + tempFullFileName + "\" -c copy \"" + OutPutFullFileName + "\"";
            foreach (var item in listFileInconcat)
            {
                strContent += "file '" + item + "'\r\n";
            }
            File.WriteAllText(tempFullFileName, strContent);
        }

        public bool MangeSpilConvCancat()
        {
            try
            {
                lblWait.Visible = true;
                Application.DoEvents();
                spliteListShut(ListSpliteShutInfo, ConcatTempPath, "temp", OutPutFullFileName.ExtOfFile());
                SetListConcat();
                Concat();
                lblWait.Visible = false;
                XtraMessageBox.Show("عملیات با موفقیت پایان یافت", "پیغام", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return true;
            }
            catch (Exception ex)
            {

                return false;
            }
        }

        private void SetListConcat()
        {
            System.IO.DirectoryInfo downloadedMessageInfo = new DirectoryInfo(ConcatTempPath);
            foreach (FileInfo file in downloadedMessageInfo.GetFiles())
            {
                listFileInconcat.Add(file.FullName);
            }
        }

        public DialogResult ShowDialog(List<SpliteShutInfo> spliteShutInfoList)
        {
            foreach (var item in spliteShutInfoList)
            {
                ListSpliteShutInfo.Add(item);
            }

            // ListBoxCtlShuts.DataSource = ListBoxCtlShuts;
            spliteShutInfoBindingSource1.DataSource = ListSpliteShutInfo;

            ShowDialog();
            Application.DoEvents();

            return System.Windows.Forms.DialogResult.OK;
        }

        private void readyTempPath(string TempPath)
        {
            System.IO.DirectoryInfo downloadedMessageInfo = new DirectoryInfo(TempPath);
            if (downloadedMessageInfo.Exists)
            {
                foreach (FileInfo file in downloadedMessageInfo.GetFiles())
                {
                    file.Delete();
                }
                foreach (DirectoryInfo dir in downloadedMessageInfo.GetDirectories())
                {
                    dir.Delete(true);
                }
            }
            if (!Directory.Exists(TempPath))
            {
                Directory.CreateDirectory(TempPath);
            }
        }
        //private void execthread()
        //{
        //    //Utility.UISync.Execute(() => StartProcess());

        //}

        private void StartProcess()
        {
            Process nprocess = new Process();


            nprocess.StartInfo.FileName = ffmpeg_exePath;
            nprocess.StartInfo.Arguments = Arguments;
            nprocess.EnableRaisingEvents = false;
            nprocess.StartInfo.UseShellExecute = false;
            nprocess.StartInfo.CreateNoWindow = true;
            nprocess.StartInfo.RedirectStandardOutput = true;
            nprocess.StartInfo.RedirectStandardError = true;
            nprocess.Start();
            StreamReader d = nprocess.StandardError;


            // Utility.UISync.Execute(() =>PF.ShowDialog(this));
            do
            {
                string s = d.ReadLine();
                if (s.Contains("Duration: "))
                {
                    string stime = ExtractDuration(s);
                    //durationTime = TotalStringToSeconds(stime);
                    durationTime = stime.StringToMeliSec(0);
                    //  synchTotal(durationTime.ToString());
                }
                else
                {
                    if (s.Contains("frame="))
                    {
                        string currents = ExtractTime(s);
                        //  currentTime = CurrentStringToSeconds(currents);
                        currentTime = currents.StringToMeliSec(0);
                        // PF2.ShowDialog();
                        //PF2.UpdateProgressBar(GetProgressValue());
                        progressBarControlSplit.EditValue = GetProgressValue();
                        // synchCurrent(currentTime.ToString());
                        //  synchTextOutput(s);
                    }
                }
            } while (!d.EndOfStream);

            nprocess.WaitForExit();
            nprocess.Close();
        }

        private float TotalStringToSeconds(string stime)
        {
            throw new NotImplementedException();
        }

        private float CurrentStringToSeconds(string currents)
        {
            throw new NotImplementedException();
        }

        private string ExtractTime(string s)
        {
            //frame=  289 fps=0.0 q=-1.0 Lsize=    6826kB time=00:00:11.73 bitrate=4765.6kbits/s  
            int index = s.IndexOf("time=") + 5;
            string currentTimeStr = s.Substring(index, 11);
            return currentTimeStr;
            // throw new NotImplementedException();
        }

        private string ExtractDuration(string s)
        {
            //Duration: 00:09:05.62, start: 0.500000, bitrate: 4765 kb/s
            int index = s.IndexOf("Duration:") + 10;
            string Duration = s.Substring(index, 11);
            return Duration;
            //throw new NotImplementedException();
        }


        public int GetProgressValue()
        {
            if (durationTime == 0) return 0;
            return (int)Math.Ceiling((currentTime / durationTime) * 100);
        }

        public bool Validate()
        {
            return true;
            //throw new NotImplementedException();
        }


        private void UpdateProgress2()
        {
            return;
            throw new NotImplementedException();
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            try
            {
                if (ListSpliteShutInfo.Count > 0 && OutPutFullFileName != "" && OutPutFullFileName != null)
                {
                    MangeSpilConvCancat();
                    ClearListBoxCtr();
                }
                else if (ListSpliteShutInfo.Count <= 0)
                {
                    // XtraMessageBox.Show("شات های انتخابی هم پوشانی دارند آیا مایل به ادامه عملیات می باشید؟", "", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                    XtraMessageBox.Show("شاتی برای ذخیره کردن موجود نیست", "توجه", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else if (OutPutFullFileName == "" | OutPutFullFileName == null)
                {
                    XtraMessageBox.Show("مسیر و نام فایل خروجی انتخاب نشده است", "توجه", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            catch (Exception ex)
            {
                XtraMessageBox.Show("عملیات با شکست مواجه شد", "خطا", MessageBoxButtons.OK, MessageBoxIcon.Error);
                ClearListBoxCtr();
                throw;
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            ClearListBoxCtr();
        }

        private void ClearListBoxCtr()
        {
            ListSpliteShutInfo.Clear();
            gridControl1.RefreshDataSource();
            // gridControl1.Refresh();
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            SpliteShutInfo spliteShutInfo = ListSpliteShutInfo.LastOrDefault();
            if (spliteShutInfo != null)
            {
                string ext = spliteShutInfo.inputFile.ExtOfFile();
                string filter = "*" + ext;

                filter += "|" + filter;
                txtFullFileName.Text = Utility.Helper.GetFileName(ext, filter, "default", "", false, "ذخیره شاتها");
                OutPutFullFileName = txtFullFileName.Text;
            }
            //OutPutFullFileName = fullFileName;
        }

        private void FfmpegSplit_Load(object sender, EventArgs e)
        {

        }




    }
}
