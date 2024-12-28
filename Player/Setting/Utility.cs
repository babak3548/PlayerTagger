using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;


namespace Player.Setting
{


   public static  class Utility
    {
       public static Dictionary<int, string> ImageFormats = new Dictionary<int, string>() 
        {
        { 1, ".bmp" }, 
        { 2, ".dib" },
        { 3, ".jpg" },
        { 4, ".jpeg" },
        { 5, ".jpe" },
        { 6, ".jfif" },
        { 7, ".gif" },
        { 8, ".tif" },
        { 9, ".titf" },
        { 10, ".png" }
        };

       public static  bool  IsImage(string Extention)
       {
          return  ImageFormats.Where(i => i.Value == Extention).Any();
       }
       public static ComponentResourceManager resourseMng { get{return  new ComponentResourceManager(typeof(MediaPlayer));}}
    //  public  ComponentResourceManager resourseMng = new ComponentResourceManager(typeof(MediaPlayer));
       //public static bool contains(this IVLCPlaylistItems items ,string Url)
       //{
       //    for (int i = 0; i < items.count; i++)
       //    {
       //        if (items[0] == Url) return true;
       //    }
       //}
    }
}
