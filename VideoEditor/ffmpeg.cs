using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Utility;

namespace VideoEditor
{
    public class Ffmpeg 
    {
      //  /**/
      ////  public static Ffmpeg ffmpeg;
      //  float durationTime = 0.00F;
      //  float currentTime = 0.00F;
      //  public string Arguments = "";
      // // int ProgressValue = 0;
      //  private string ffmpeg_exePath;
      //  private string tempFolderPath;
      //  ProgressForm2 PF2 ;
      //  public Ffmpeg()
      //  {
      //      PF2 = new ProgressForm2();
      //     // Arguments = @"-i ""C:\myfile.mpg"" -ar 22050 -ab 32 -f flv -s 320×240 -aspect 4:3 -y somemove.flv";
      //      ffmpeg_exePath=Path.Combine(Application.StartupPath, "ffmpeg.exe");
      //      tempFolderPath = Path.Combine(Application.StartupPath, "tempFolder"); ;
      //      if (!Directory.Exists(tempFolderPath))
      //      {
      //          Directory.CreateDirectory(tempFolderPath);
      //      }
      //  }
      //  private void clearTempFolder()
      //  {
      //      System.IO.DirectoryInfo downloadedMessageInfo = new DirectoryInfo(tempFolderPath);

      //      foreach (FileInfo file in downloadedMessageInfo.GetFiles())
      //      {
      //          file.Delete();
      //      }
      //      foreach (DirectoryInfo dir in downloadedMessageInfo.GetDirectories())
      //      {
      //          dir.Delete(true);
      //      }
      //  }
      //  //private void execthread()
      //  //{
      //  //    //Utility.UISync.Execute(() => StartProcess());
            
      //  //}

      //  private void StartProcess()
      //  {
      //      Process nprocess = new Process();


      //      nprocess.StartInfo.FileName = ffmpeg_exePath;
      //      nprocess.StartInfo.Arguments = Arguments;
      //      nprocess.EnableRaisingEvents = false;
      //      nprocess.StartInfo.UseShellExecute = false;
      //      nprocess.StartInfo.CreateNoWindow = true;
      //      nprocess.StartInfo.RedirectStandardOutput = true;
      //      nprocess.StartInfo.RedirectStandardError = true;
      //      nprocess.Start();
      //      StreamReader d = nprocess.StandardError;
            
            
      //     // Utility.UISync.Execute(() =>PF.ShowDialog(this));
      //      do
      //      {
      //          string s = d.ReadLine();
      //          if (s.Contains("Duration: "))
      //          {
      //              string stime = ExtractDuration(s);
      //              //durationTime = TotalStringToSeconds(stime);
      //              durationTime = stime.StringToMeliSec(0);
      //              //  synchTotal(durationTime.ToString());
      //          }
      //          else
      //          {
      //              if (s.Contains("frame="))
      //              {
      //                  string currents = ExtractTime(s);
      //                //  currentTime = CurrentStringToSeconds(currents);
      //                  currentTime = currents.StringToMeliSec(0);
      //                  PF2.ShowDialog();
      //                  PF2.UpdateProgressBar(GetProgressValue());
      //                  // synchCurrent(currentTime.ToString());
      //                  //  synchTextOutput(s);
      //              }
      //          }
      //      } while (!d.EndOfStream);

      //      nprocess.WaitForExit();
      //      nprocess.Close();
      //  }

      //  private float TotalStringToSeconds(string stime)
      //  {
      //      throw new NotImplementedException();
      //  }

      //  private float CurrentStringToSeconds(string currents)
      //  {
      //      throw new NotImplementedException();
      //  }

      //  private string ExtractTime(string s)
      //  {
      //      //frame=  289 fps=0.0 q=-1.0 Lsize=    6826kB time=00:00:11.73 bitrate=4765.6kbits/s  
      //      int index = s.IndexOf("time=") + 5;
      //      string currentTimeStr = s.Substring(index, 11);
      //      return currentTimeStr;
      //     // throw new NotImplementedException();
      //  }

      //  private string ExtractDuration(string s)
      //  {
      //      //Duration: 00:09:05.62, start: 0.500000, bitrate: 4765 kb/s
      //      int index =s.IndexOf("Duration:")+10;
      //      string Duration = s.Substring(index, 11);
      //      return Duration;
      //      //throw new NotImplementedException();
      //  }


      //  public int GetProgressValue()
      //  {
      //      if (durationTime == 0) return 0;
      //      return (int)Math.Ceiling((currentTime / durationTime )* 100);
      //  }

      //public void CreateArgSplitAshut(string inputPath,string fromTime,string toTime  ,string outPath)
      //  {
      //      //ffmpeg -i input.mpg -ss 00:00:01 -t 00:00:03 output.mpg 
      //      //ffmpeg -i <input_file> -vcodec mjpeg -qscale 1 -an output.avi 
      //    //ffmpeg -ss 00:00:00 -t 00:50:00 -i largefile.mp4 -acodec copy \-vcodec copy smallfile.mp4
      //      Arguments = "-i " + inputPath + " -ss " + fromTime + " -t " + toTime +" -c copy " + outPath; 
      //  }

      //public void spliteAShut(string inputPath, string fromTime, string toTime, string outPath)
      //{ 
      //  CreateArgSplitAshut(inputPath, fromTime,  toTime, outPath);
      //  StartProcess();
      //}

      //public bool Validate(List<SpliteShutInfo> IFs)
      //{
      //    return true;
      //    //throw new NotImplementedException();
      //}

      //public void spliteAShut(List<SpliteShutInfo> SpliteShutInfoList, string fileName)
      //{
          
      //    foreach (var item in SpliteShutInfoList)
      //    {
      //        CreateArgSplitAshut(item.inputFile, item.startTime, item.EndTime, fileName);
      //        StartProcess();
      //    }

      //}


    }
}
