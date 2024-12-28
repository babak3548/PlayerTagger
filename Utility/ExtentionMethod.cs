using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DevExpress.XtraEditors;
using System.IO;

namespace Utility
{
   public static  class ExtentionMethod 
    {
      public    const int LengthTrakBar = 50000;
       public static string MeliSecToTimeFormat(this int miliSecond)
       {
           var second = miliSecond / 1000;
           var hh = (int)second / 3600;
           var min = (int)((second - hh * 3600) / 60);
           var sec = second - ((hh * 3600) + (min * 60));
           return hh.ToString() + ":" + min.ToString() +":"+ sec.ToString();
           
       }

       public static int ToPsistionValue(this  long value, long totalDuritionFile)
       {
           if (totalDuritionFile == 0) totalDuritionFile = 1;
           int pos=(int)((value * LengthTrakBar) / totalDuritionFile);
           if (pos > LengthTrakBar)
           { return LengthTrakBar-1; }
           else { return pos; }
       }

       public static long ToTimePlayerValue(this  int value, long totalDuritionFile)
       {
           return (long)((value * totalDuritionFile) / LengthTrakBar);
       }

       public static string MeliSecToTimeString(this long miliSecond)
       {
           return TimeSpan.FromMilliseconds(miliSecond).ToString().PadRight(11).Substring(0,11);
       }

       public static long  StringToMeliSec(this string  TimeString,double?  LastValue=0)
       {

           try
           {
               var meliSec = new TimeSpan();
               TimeSpan.TryParse(TimeString, out meliSec);
               return (long)meliSec.TotalMilliseconds;
           }
           catch (Exception)
           {
               XtraMessageBox.Show("Bad_Format");
               return ((long)LastValue);  
           }

       }

       public static string ToTimeFormat(this int Second)
       {
           var hh = (int)Second / 3600;
           var min = (int)((Second - hh * 3600) / 60);
           var sec = Second - ((hh * 3600) + (min * 60));
           return hh.ToString() + ":" + min.ToString() + ":" + sec.ToString();

       }

       public static int ToIntPosition(this double Position)
       {
           return (int)(Position * LengthTrakBar);
       }

       public static int ToIntPosition(this long  Position)
       {
           return (int)(Position * LengthTrakBar);
       }

       public static string  PositionToCaptionFormat(this int Position)
       {
           return Position.ToString() +"/"+ LengthTrakBar.ToString();
       }



       public static string ExtOfFile(this String sz)
       {
           int lastdotpos = sz.LastIndexOf(".")+1;
           return sz.Substring(lastdotpos, sz.Length - lastdotpos);
       }
       public static string PathOfFullFile(this string s)
       {
         return  s.Replace(s.FileNameWithOutExt()+"." + s.ExtOfFile(), "");
       }
       public static string FileNameWithOutExt(this string s)
       {
           int lastMomyezpos = s.LastIndexOf("\\");
           int lastdotpos = s.LastIndexOf(".");

           return s.Substring(lastMomyezpos, lastdotpos - lastMomyezpos);
       }

       public static double  ToDoublePosition(this double Position)
       {

           return (double)Position / LengthTrakBar;
       }

       public static double ToDoublePosition(this int Position)
       {

           return (double)Position / LengthTrakBar;
       }

       public static double? ToNullableDoublePosition(this double? Position)
       {

           return (double)Position / LengthTrakBar;
       }
    }
}
