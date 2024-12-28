using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Player.DataControl
{
    interface IBackUp
    {
        /// <summary>
        /// برای لغو عملیات به کار می رود
        /// </summary>
        bool  Cancel  { get; set; }
        /// <summary>
        /// مسیری که نسخه  پشتیبان در آن قرار دارد
        /// </summary>
        string  BackUpPath { get; set; }
        List<Playlist> PList { get; set; }

        /// <summary>
        /// مدیریت عملیات پشتیبان گیری
        /// </summary>
        string  StartBackUp(string backUpPath);

        /// <summary>
        /// PList را پر میکند
        /// </summary>
        void ReadPlayList();

        void SetBackUpPath(string backUpPath);

        /// <summary>
        /// عمل کپی فایلهارا به مسیر ست شده در packUpPath انجام می دهد
        /// </summary>
        /// <param name="PList"></param>
        void copiesFiles();

        /// <summary>
        /// مسیر جدید فایلها را را در فایل متا دیتا به روز رسانی می کند 
        /// </summary>
        void UpdateMetaData();
        /// <summary>
        /// ذخیره متا دیتا در مسیر جاری(BackUpPath)
        /// </summary>
        void SaveMetaDataFile();
               

        //void CopyMetadataFile();


       


     
    }
}
