using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using DevExpress.XtraEditors;
using System.Windows.Forms;

namespace Player
{

    static internal class Dangel
    {
        static Dangel()
        {
            init();
        }
        const string FileName = @"\Album.lic";
        /// <summary>
        /// این متد برای لود دی ال ال های دانگیل در حافظه استفاده می شود
        /// </summary>
        /// <returns></returns>
        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool InitLicense();

        /// <summary>
        /// این متد برای لود دادهای فایل تولید شده از طرف شرکت برای یک سازمان که در مسیر جاری
        /// پروژه قرار می گیرد که بعداز لود کردن این فایل توسط این متد دادهای داخل فایل توسط 
        /// سایر متدهای دی ال ال قابل خواندن خواهد بود 
        /// </summary>
        /// <param name="licfilepath"></param>
        /// <returns></returns>
        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern short CheckLicense(string licfilepath);

        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool CheckTokenExist(string sno);

        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern string GetActiveSerial();

        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern string ErrorMessage();

        /// <summary>
        /// از این برای خواندن پارامترهیای نوشته شده در فایل لیسنس استفاده می شود
        /// </summary>
        /// <param name="entryname"></param>
        /// <returns></returns>
        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern string GetLicenseValue(string entryname);

        [DllImport("SLL.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern string F3(string instr, int iter);

        internal static void init()
        {
           return;
            try
            {
                Dangel.InitLicense();
                Dangel.CheckLicense((Directory.GetCurrentDirectory() + FileName));
            }
            catch (Exception ex)
            {
                XtraMessageBox.Show(ex.Message + Player.Setting.Utility.resourseMng.GetString("problem_in_load_dll_Or_licenceFile_dangel"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Environment.Exit(1);
            }

        }

        /// <summary>
        /// وجود دانگلی با سریال تعریف شده در فایل lic را تایید می کند  
        /// </summary>
        /// <returns></returns>
        internal static void ExistDangelTrue()
        {
          return;
            bool resault = false;
            try
            {
                string srNo = Dangel.GetActiveSerial();
                resault = Dangel.CheckTokenExist(srNo);
            }
            catch (Exception ex)
            {
                XtraMessageBox.Show(ex.Message + Player.Setting.Utility.resourseMng.GetString("problem_in_load_dll_Or_licenceFile_dangel"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Environment.Exit(1);
                resault = false;
            }

            if (!resault )
            {
                XtraMessageBox.Show(Player.Setting.Utility.resourseMng.GetString("Please_Enter_Dangel"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Environment.Exit(1);
            }
        }

        internal static string GetLicenseValueDangel(string entryname)
        {
            return "";
            string resault=string.Empty ;
            try
            {
                resault= GetLicenseValue(entryname);
            }
            catch (Exception ex)
            {

                XtraMessageBox.Show(ex.Message + Player.Setting.Utility.resourseMng.GetString("problem_in_load_dll_Or_licenceFile_dangel"), "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Environment.Exit(1);
                return string.Empty;
            }
            return resault;
        }
    }
}
