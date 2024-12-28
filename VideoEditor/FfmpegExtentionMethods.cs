using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Utility;

namespace VideoEditor
{
   public static class FfmpegExtentionMethods
    {
        static string lastFFmpegFileDuration = "";
        static string FullFileName = "";

       public static long DurtionByFfmpeg(this string fullFileName)
       {
           if (FullFileName == fullFileName && lastFFmpegFileDuration != null)
           {
               return lastFFmpegFileDuration.StringToMeliSec();
           }
           else
           {
               Process nprocess = new Process();
               nprocess.StartInfo.FileName = Path.Combine(Application.StartupPath, "ffmpeg.exe");
               nprocess.StartInfo.Arguments = "-i \"" + fullFileName + "\"";
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
                       int index = s.IndexOf("Duration:") + 10;
                       lastFFmpegFileDuration = s.Substring(index, 11);
                       return lastFFmpegFileDuration.StringToMeliSec();
                   }
                   else
                   {
                       if (s.Contains("frame="))
                       {

                       }
                   }
               } while (!d.EndOfStream);

               nprocess.WaitForExit();
               nprocess.Close();
           }
           return 0;
       }
    }
}
