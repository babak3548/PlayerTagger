using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;

namespace Player.Public_class
{
   public static class FileHelper
    {
        [DllImport(@"urlmon.dll", CharSet = CharSet.Auto)]
        private extern static System.UInt32 FindMimeFromData(
            System.UInt32 pBC,
            [MarshalAs(UnmanagedType.LPStr)] System.String pwzUrl,
            [MarshalAs(UnmanagedType.LPArray)] byte[] pBuffer,
            System.UInt32 cbSize,
            [MarshalAs(UnmanagedType.LPStr)] System.String pwzMimeProposed,
            System.UInt32 dwMimeFlags,
            out System.UInt32 ppwzMimeOut,
            System.UInt32 dwReserverd
        );
        public static string GetMimeFromFile(string filename)
        {
            if (!File.Exists(filename))
                return string.Empty;

            byte[] buffer = new byte[256];
            using (FileStream fs = new FileStream(filename, FileMode.Open))
            {
                if (fs.Length >= 256)
                    fs.Read(buffer, 0, 256);
                else
                    fs.Read(buffer, 0, (int)fs.Length);
            }
            try
            {
                System.UInt32 mimetype;
                FindMimeFromData(0, null, buffer, 256, null, 0, out mimetype, 0);
                System.IntPtr mimeTypePtr = new IntPtr(mimetype);
                string mime = Marshal.PtrToStringUni(mimeTypePtr);
                Marshal.FreeCoTaskMem(mimeTypePtr);
                return mime;
            }
            catch (Exception e)
            {
                return "unknown/unknown";
            }
        }

        public static MediaType GetMimeFromName(string fileName)
        {
            if (!File.Exists(fileName))
                return MediaType.NotMedia;
            if (MIMETypesDictionary.ContainsKey(Path.GetExtension(fileName).Remove(0, 1).ToLower()))
            {
                return MIMETypesDictionary[Path.GetExtension(fileName).Remove(0, 1).ToLower()];
            }
            return MediaType.NotMedia;
        }

        private static readonly Dictionary<string, MediaType> MIMETypesDictionary = new Dictionary<string, MediaType>
  {
   
    {"aif", MediaType.Audio},
    {"aifc", MediaType.Audio},
    {"aiff", MediaType.Audio},
    {"au", MediaType.Audio},
    {"avi", MediaType.Video},    
    {"bmp", MediaType.Image},    
    {"cgm",  MediaType.Image},
    {"dif",MediaType.Video},
    {"djv",  MediaType.Image},
    {"djvu",  MediaType.Image}, 
    {"dv", MediaType.Video},   
    {"gif",  MediaType.Image},   
    {"ico",  MediaType.Image},
    {"ief",  MediaType.Image},
    {"jp2",  MediaType.Image},
    {"jpe",  MediaType.Image},
    {"jpeg", MediaType.Image},
    {"jpg",  MediaType.Image},
    {"kar", MediaType.Audio},
    {"m3u", MediaType.Audio},
    {"m4a", MediaType.Audio},
    {"m4b", MediaType.Audio},
    {"m4p", MediaType.Audio},
    {"m4u", MediaType.Video},
    {"m4v", MediaType.Video},
    {"mac",  MediaType.Image},
    {"mid", MediaType.Audio},
    {"midi", MediaType.Audio},
    {"mov", MediaType.Video},
    {"movie",MediaType.Video},
    {"mp2", MediaType.Audio},
    {"mp3", MediaType.Audio},
    {"mp4", MediaType.Video},
    {"mpe", MediaType.Video},
    {"mpeg",MediaType.Video},
    {"mpg",MediaType.Video},
    {"mpga",MediaType.Audio},
    {"mxu", MediaType.Video},
    {"pbm",  MediaType.Image},
    {"pct",  MediaType.Image},
    {"pgm",  MediaType.Image}, 
    {"pic", MediaType.Image},
    {"pict",  MediaType.Image},
    {"png",  MediaType.Image}, 
    {"pnm",  MediaType.Image},
    {"pnt",  MediaType.Image},
    {"pntg",  MediaType.Image},
    {"ppm",  MediaType.Image},
    {"qt", MediaType.Video},
    {"qti",  MediaType.Image},
    {"qtif", MediaType.Image},
    {"ra", MediaType.Audio},
    {"ram",MediaType.Audio},
    {"ras",  MediaType.Image},
    {"rgb",  MediaType.Image},
    {"svg",  MediaType.Image},
    {"swf", MediaType.Video},
    {"tif",  MediaType.Image},
    {"tiff", MediaType.Image},
    {"wav",MediaType.Audio},
    {"wbmp",  MediaType.Image},
    {"xbm",  MediaType.Image},
    {"xpm",  MediaType.Image},
    {"xwd", MediaType.Image},
     {"wmv", MediaType.Video},
     {"flv", MediaType.Video},
     {"dat", MediaType.Video},
     {"ts", MediaType.Video}
   
  };

    }
}
