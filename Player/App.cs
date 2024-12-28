using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WMPLib;
using Player.Setting;
using System.Runtime.InteropServices;
using System.IO;
using Player.Setting;
namespace Player
{
    public static class App
    {
        private static TimeSpan TimeConvert;
       // public static string FileName;
        public static string BackupMetaDataFileName;
        public static string SettingFileName;
        public static string PicDir;
        public const string ExtentionAlbum = "alm";
        public static string DefaultMetadataFileName = @"\PlayListData.";
        public const string PicShuts = "Pic\\";
        public static VideoEditor.VideoEditorManager VM = new VideoEditor.VideoEditorManager();
        public static AppSetting Setting { get; set; }
        public static bool ModifiedProject { get; set; }

        static App()
        {
            TimeConvert = new TimeSpan();
            
            DefaultMetadataFileName = Directory.GetCurrentDirectory() + DefaultMetadataFileName + ExtentionAlbum;
            BackupMetaDataFileName = @"MetaDataBackUp." + ExtentionAlbum;
            SettingFileName = @"AppSetting.xml";
            //if (!System.IO.Directory.Exists(PicDir))
            //{
            //    System.IO.Directory.CreateDirectory(PicDir);
            //}
            if (System.IO.File.Exists(App.SettingFileName))
            {
                Setting = Serializer.DeSerializeFromFile<AppSetting>(App.SettingFileName);
            }
            if (Setting == null) Setting = new AppSetting( DefaultMetadataFileName );

            Setting.MetaDataPath = Setting.MetaDataPath == null ? DefaultMetadataFileName  : Setting.MetaDataPath;

            App.PicDir = GetPicDir();
           // FileName = (Setting.MetaDataPath == null) ? @"PlayListData.xml" : Setting.MetaDataPath;
        }

        internal static void SetPicDir()
        {
            App.PicDir = GetPicDir();
            if (!Directory.Exists(App.PicDir))
            {
                Directory.CreateDirectory(App.PicDir);
            }
        }

        public static string GetPicDir()
        {
            return Setting.MetaDataPath.Replace(FullAlbumName(), "") + AlbumName() + PicShuts;
        }
   public static string  AlbumName()
   {
       System.IO.FileInfo fileInfo = new FileInfo(Setting.MetaDataPath);
       return fileInfo.Name.Replace("." + ExtentionAlbum, "");
   }
   public static string FullAlbumName()
   {
       System.IO.FileInfo fileInfo = new FileInfo(Setting.MetaDataPath);
       return fileInfo.Name;
   }
        public static Dictionary<string, string> GetMediaInfo(this IWMPMedia Media)
        {
            Dictionary<string, string> Dic = new Dictionary<string, string>();
            string x, y;
            for (int i = 0; i < Media.attributeCount; i++)
            {
                x = Media.getAttributeName(i);
                y = Media.getItemInfo(x);


                Dic.Add(x, y);

            }
            return Dic;
        }

        

        public static VideoEditor.SMM_Defs.CInterval_info[] ToCInterval_info(this List<Chapter> lc)
        {
            var result = from c in lc select new VideoEditor.SMM_Defs.CInterval_info() { bselect = true, llstart = (long)(c.StartPosition * 10000000) , llend = (long)(c.EndPosition * 10000000)};
           
          
            return result.ToArray();
        }

        /// <summary>
        /// این متد برای شاتهای که شروع و پایان انها 
        /// با پوزیسن مشخص شده است استفاده می گردد
        /// </summary>
        /// <param name="lc"></param>
        /// <returns></returns>
        public static VideoEditor.SMM_Defs.CInterval_info[] ToCInterval_infoPos(this List<Chapter> lc)
        {
            var result = from c in lc select new VideoEditor.SMM_Defs.CInterval_info() { bselect = true, llstart = (long)(c.StartPosition * DurtionFile(c.SourceMedia.MediaSource ))/ExtentionMethod.LengthTrakBar
                ,llend = (long)(c.EndPosition * DurtionFile(c.SourceMedia.MediaSource)) / ExtentionMethod.LengthTrakBar
            };
            return result.ToArray();
        }

        public static VideoEditor.SMM_Defs.CInterval_info[] ToCInterval_infoPos(this List<Chapter> lc, long DurtionFileInPlayer)
        {
            var result = from c in lc
                         select new VideoEditor.SMM_Defs.CInterval_info()
                         {
                             bselect = true,
                             llstart = (long)(c.StartPosition * DurtionFile(c.SourceMedia.MediaSource)) / DurtionFileInPlayer
                             ,
                             llend = (long)(c.EndPosition * DurtionFile(c.SourceMedia.MediaSource)) / DurtionFileInPlayer
                         };
            return result.ToArray();
        }
        public static List<VideoEditor.SpliteShutInfo> ToSpliteShutInfo(this List<Chapter> lc, long DurtionFileInPlayer,long DurtionFileInCuter)
        {
            var result = from c in lc
                         select new VideoEditor.SpliteShutInfo()
                         {
                            inputFile=c.SourceMedia.MediaSource,
                            startTime = ((long)c.StartPosition).MeliSecToTimeString(),
                            SliceTime = ((long)(c.EndPosition - c.StartPosition)).MeliSecToTimeString(),
                            startTimeInCuter = ((long)c.StartPosition).GetCuterTime(DurtionFileInPlayer,DurtionFileInCuter).MeliSecToTimeString(),
                            SliceTimeInCuter = ((long)(c.EndPosition - c.StartPosition)).GetCuterTime(DurtionFileInPlayer, DurtionFileInCuter).MeliSecToTimeString()
                         };
            return result.ToList();
        }
        public static string ConvertToTimeFormat(this long MiliSecond)
        {
            long Time = MiliSecond / 1000;
            return string.Format("{0:d2}:{1:d2}", Time / 60, Time % 60);
        }

        public static string ExtOfFile(this String sz)
        {
            int lastdotpos = sz.LastIndexOf(".");
            return sz.Substring(lastdotpos, sz.Length - lastdotpos);
        }

        public static long DurtionFile(string FileName)
        {
            FileInfo FI = new FileInfo(FileName);
            if (FI.Exists)
                return VM.DurationMediaSource(FileName,new ProgressForm ());
            else
                return 0;
        }
      


    }
}
