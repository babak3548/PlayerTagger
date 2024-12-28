using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace Player.Setting
{
    [DataContract(Name = "PlayList", Namespace = "http://www.Player.com")]
    public class AppSetting
    {
        [DataMember()]
        public int ThumbWidth { get; set; }
        [DataMember()]
        public int ThumbHeight { get; set; }
        [DataMember()]
        public float HorizontalResolution { get; set; }
        [DataMember()]
        public float VerticalResolution { get; set; }
        [DataMember()]
        public string Defaulttitle { get; set; }
        [DataMember()]
        public bool ShowToolTipController { get; set; }
        [DataMember()]
        public int Language { get; set; }
        [DataMember()]
        public string MetaDataPath { get; set; }

        [DataMember()]
        public string DefaulMetaDataPath { get; set; }

        [DataMember()]
        public string DefaulFilesPath { get; set; }

        [DataMember()]
        public int PlayerType { get; set; }

        [DataMember()]
        public int VolumeValue { get; set; }

        [DataMember()]
        public bool CountinePlay { get; set; }

        [DataMember()]
        public string SkinName { get; set; }

        public static Dictionary<int, string> LanguageList = new Dictionary<int, string>() { { 1, "en" }, { 2, "fa-IR" } };
        public static Dictionary<int, string> PlayerTypies = new Dictionary<int, string>() { { 1, "VLCPlayer" }, { 2, "LeadPlayer" },{4,"MediaPlayer"} };

        public AppSetting(string DefaultFileName)
        {
         
                ThumbWidth = 800;
                ThumbHeight = 600;
                HorizontalResolution = 1024;
                VerticalResolution = 1024;
                Defaulttitle = "آلبوم";
                PlayerType = 1;
                MetaDataPath = DefaultFileName;
                Language = 2;
                VolumeValue = 50;
                CountinePlay = true;
        }

 

        //public bool  FillData()
        //{
        //    if (System.IO.File.Exists(App.SettingFileName))
        //    {
        //        var obj = Serializer.DeSerializeFromFile<AppSetting>(App.SettingFileName);
        //        if (obj != null)
        //        {
        //        //  this.MetaDataPath = ((AppSetting)obj).MetaDataPath;
        //        //this.ThumbWidth = ((AppSetting)obj).ThumbWidth;
        //        //this.HorizontalResolution = ((AppSetting)obj).HorizontalResolution;
        //        //this.VerticalResolution = ((AppSetting)obj).VerticalResolution;
        //        //this.Defaulttitle = ((AppSetting)obj).Defaulttitle;
        //        //this.ShowToolTipController = ((AppSetting)obj).ShowToolTipController;
        //        //this.Language = ((AppSetting)obj).Language;
        //        //this.PlayerType = ((AppSetting)obj).PlayerType;
                  
        //         return true;
        //        }

        //        return false;
        //    }
        //    else return false;
        //}


        public  void SaveAppSetting()
        {
            Serializer.Serialize(this, App.SettingFileName);
            
        }
    }

    public  enum EnumPlayeType
    {
        VlCPlayer=1,
        LeadPlayer=2,
        picturePlayer=3,
        MediaPlayer =4
    }
}
