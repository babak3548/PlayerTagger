using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Compression;

namespace Player.DataControl
{
    public class RestoreBackUp:BackUp 
    {
        public string RestorePath { get; set; }
        public RestoreBackUp(string restorePath, string backUpPath)
            : base()
        {
            RestorePath = restorePath;
            BackUpPath = backUpPath;
        }
        public override void copiesFiles()
        {
            int indexS=0;
            int i=0;
            string RestorFullFileName = "";
            string BackupFullFileName = "";
            foreach (var playList in PList )
            {
                foreach (var playListItem in playList.Items)
                {
                    try
                    {
                        if (Cancel == true) break;
                        //  FileInfo fileInfo = new FileInfo();
                        var restoreFolderName = RestorePath + "\\" + playList.Name;

                        if (!Directory.Exists(restoreFolderName))
                        {
                            Directory.CreateDirectory(restoreFolderName);
                        }

                         BackupFullFileName = BackUpPath + "\\" + playListItem.MediaSource;
                         indexS = playListItem.MediaSource.IndexOf("___") + 3;  //BackUpPath + "\\" + fileInfo.Name  + "." + fileInfo.Extension;
                         RestorFullFileName = restoreFolderName + "\\" + playListItem.MediaSource.Substring(indexS );
                         if (File.Exists(RestorFullFileName)) { RestorFullFileName = restoreFolderName + "\\"+i.ToString("D3") + playListItem.MediaSource.Substring(indexS); }
                        File.Copy(BackupFullFileName, RestorFullFileName);
                        playListItem.MediaSource = RestorFullFileName;
                    }
                    catch (Exception)
                    {
                    
                    }
                }
            }

        } 
        public string  StartRestorBackUp()
        {
            try
            {
                ReadPlayList(BackUpPath + "\\" +  App.BackupMetaDataFileName);
        
                copiesFiles();
  
                SaveMetaDataFile(RestorePath);
                App.Setting.MetaDataPath = RestorePath + "\\" + App.BackupMetaDataFileName;

                App.PicDir = App.GetPicDir();
                //بر گرداندن عکس شات ها
                DirectoryCopy((BackUpPath + "\\" + App.PicShuts), App.PicDir, false);

                Program.form1.Init();

            }
            catch (Exception ex)
            {

                return "Not_Success_Operation";
            }

            return "Success_Operation";
        }
    }
}
