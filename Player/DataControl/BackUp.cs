using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace Player.DataControl
{
   public  class BackUp :IBackUp 
    {

       public bool Cancel { get; set; }
        public string BackUpPath{get;set;}
        public string MetaDataFileName { get; set; }


        List<Playlist> _PList=new List<Playlist>();
        public List<Playlist> PList
        {
            get
            {
                return _PList;
            }
            set
            {
                _PList=value ;
            }
        }

        public BackUp()
        {
            
            Cancel = false;
        }
        public string StartBackUp(string backUpPath)
        {
            try
            {
                
            ReadPlayList();
            SetBackUpPath(backUpPath);
         //   CreateFolder(ConstFolderName);
            copiesFiles();

          //  UpdateMetaData();
            SaveMetaDataFile();
            //کپی عکس های شات ها
            DirectoryCopy(App.PicDir,( BackUpPath +"\\"+ App.PicShuts), false);
            }
            catch (Exception ex)
            {

                return  ("Not_Success_Operation" + ex.Message);
            }
            return "Success_Operation";
        }

        public void ReadPlayList()
        {
            if (System.IO.File.Exists(App.Setting.MetaDataPath))
            {
                var obj = Serializer.DESDeSerializeFromFile<List<Playlist>>(App.Setting.MetaDataPath);
                 PList = obj;
            }
        }

        public void ReadPlayList(string PathMetaData)
        {
            if (System.IO.File.Exists(PathMetaData))
            {
                var obj = Serializer.DESDeSerializeFromFile<List<Playlist>>(PathMetaData);
                PList = obj;
            }
        }

        public void SetBackUpPath(string backUpPath)
        {
            BackUpPath = backUpPath;
        }


       virtual   public void copiesFiles()
        {
            foreach (var playList in PList )
            {
                foreach (var playListItem in playList.Items)
                {
                    try
                    {
                        if (Cancel == true) break;
                        FileInfo fileInfo = new FileInfo(playListItem.MediaSource);
                        var pasicalFileName = Guid.NewGuid().ToString()+"___" + fileInfo.Name; //"." + fileInfo.Extension;
                        var FullFileName = BackUpPath + "\\" + pasicalFileName;
                        File.Copy(playListItem.MediaSource, FullFileName);
                        playListItem.MediaSource = pasicalFileName;
                    }
                    catch (Exception)
                    {
                    }
                }   
            }

        }
                
      
           // Copy from the current directory, include subdirectories.
         //  DirectoryCopy(".", @".\temp", true);
       

       public static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
       {
           // Get the subdirectories for the specified directory.
           DirectoryInfo dir = new DirectoryInfo(sourceDirName);
           DirectoryInfo[] dirs = dir.GetDirectories();

           if (!dir.Exists)
           {
               throw new DirectoryNotFoundException(
                   "مسیر مبدا، در سیستم موجود نمی باشد"
                   + sourceDirName);
           }

           // If the destination directory doesn't exist, create it. 
           if (!Directory.Exists(destDirName))
           {
               Directory.CreateDirectory(destDirName);
           }

           // Get the files in the directory and copy them to the new location.
           FileInfo[] files = dir.GetFiles();
           foreach (FileInfo file in files)
           {
               string temppath = Path.Combine(destDirName, file.Name);
               file.CopyTo(temppath, false);
           }

           // If copying subdirectories, copy them and their contents to new location. 
           if (copySubDirs)
           {
               foreach (DirectoryInfo subdir in dirs)
               {
                   string temppath = Path.Combine(destDirName, subdir.Name);
                   DirectoryCopy(subdir.FullName, temppath, copySubDirs);
               }
           }
       }

        public void UpdateMetaData()
        {
            throw new NotImplementedException();
        }

        public void SaveMetaDataFile()
        {
            /// playerControl1.playCtr.Stop();
            Serializer.DESSerialize(PList,BackUpPath + "\\" + App.BackupMetaDataFileName );
             PList.Clear();
        }

        public void SaveMetaDataFile(string path )
        {
            /// playerControl1.playCtr.Stop();
            Serializer.DESSerialize(PList, path + "\\" + App.BackupMetaDataFileName);
            PList.Clear();
        }

        //public void CopyMetadataFile()
        //{
        //    throw new NotImplementedException();
        //}

 

        

    }
}
