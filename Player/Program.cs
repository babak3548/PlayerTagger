using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using System.Threading;
using Player.Setting;
using System.Windows;
//using Vlc.DotNet.Core;
//using Vlc.DotNet.Forms;


namespace Player
{
    static class Program
    {
        public static MediaPlayer form1;
        public static string filePath = "";
        public static string filePath1 = "";
        /// <summary>
        /// The main entry point for the application.MediaPlayer
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
         
           // tryاین کد در زمان نسخه تحویلی باید اضافه گردد 
           // {
                DevExpress.UserSkins.BonusSkins.Register();
                DevExpress.Skins.SkinManager.EnableFormSkins();
                System.Windows.Forms.Application.EnableVisualStyles();
                System.Windows.Forms.Application.SetCompatibleTextRenderingDefault(false);
                AppDomain.CurrentDomain.UnhandledException += HandelException;
                Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(AppSetting.LanguageList[App.Setting.Language]);
                //  Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo("en");
                string[] args2 = System.Environment.GetCommandLineArgs();
                if (args.Count() > 0) filePath = args[0];
                if (args.Count() > 1) filePath1 = args[1];
            
                    form1 = new MediaPlayer();
                   System.Windows.Forms.Application.Run(form1);
               
            //}
            //catch ( Exception ex )
            //{
            //    XtraMessageBox.Show(ex.Message );
                
            //}


        }
        public static void HandelException(object sender, UnhandledExceptionEventArgs e)
        {
            XtraMessageBox.Show(e.ExceptionObject.ToString());
        }

        private static void Application_Startup(object sender, StartupEventArgs e)
    {
        string[] args = System.Environment.GetCommandLineArgs();
        string filePath = args[0];
    }
    }
}
