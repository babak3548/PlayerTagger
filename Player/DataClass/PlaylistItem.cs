
using System;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Drawing.Design;
using System.Runtime.Serialization;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Linq;
using Player.Public_class;
using System.Xml.Serialization;
using Player.DataClass;
namespace Player
{
    public class PlaylistItem 
    {
        private string mediaSource;

        public PlaylistItem()
            : this("", "", "")
        {
        }
        public PlaylistItem(string title, string description, string mediaSource)
        {
         
            Title = title;
            Description = description;
            MediaSource = mediaSource;
           
            

        }


        #region --- Properties ---
        public MediaType SourceType { get; set; }
        public int SourceTypeIndex { get { return (int)SourceType; } }
        [DataMember()]
        public string Title { get; set; }
        [DataMember()]
        public string MediaSource
        {
            get { return mediaSource; }
            set { mediaSource = value; SourceType = FileHelper.GetMimeFromName(mediaSource); } 
        }
        [DataMember()]
        public string ThumbSource { get; set; }
        [DataMember()]
        public bool IsAdaptiveStreaming { get; set; }

        public string AudioCodec { get; set; }

        public string VideoCodec { get; set; }
        [DataMember()]
        public string Description { get; set; }

       
        /// <summary>
        /// The length of video file in bytes
        /// </summary>
        /// 
        public long FileSize { get; set; }

        public double FrameRate { get; set; }
       

        /// <summary>
        /// The actual height of the video
        /// </summary>
       
        public int Height { get; set; }
        /// <summary>
        /// The actual width of the video
        /// </summary>
        public int Width { get; set; }

       //  [XmlArray("Chapters"), XmlArrayItem("Chapter")]

        public static SortableObservableCollection<Chapter> AllChapters = new SortableObservableCollection<Chapter>();
        public static List<string> AllChapterGroup 
        {
            get { return (from c in AllChapters where c.Group!=null select c.Group  ).Distinct().ToList(); }
        }

       // ObservableCollection<Chapter>
        SortableObservableCollection<Chapter> _chapters;
        [DataMember()]
        public virtual SortableObservableCollection<Chapter> Chapters
        {
            get
            {
                if (_chapters == null)
                {
                    _chapters = new SortableObservableCollection<Chapter>();
                    _chapters.CollectionChanged += onChaptersChange;
                    
                }
                return _chapters;
            }
        }
        public void onChaptersChange(object Sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e )
        {
            if (e.Action == System.Collections.Specialized.NotifyCollectionChangedAction.Add || e.Action == System.Collections.Specialized.NotifyCollectionChangedAction.Replace)
                foreach (var item in e.NewItems)
                {
                     ((Chapter)item).SourceMedia = this;
                     AllChapters.Add((Chapter)item);
                }
            if ((e.Action == System.Collections.Specialized.NotifyCollectionChangedAction.Remove || e.Action==System.Collections.Specialized.NotifyCollectionChangedAction.Reset) && e.OldItems!=null )
            {
                foreach (var item in e.OldItems)
                {
                  
                    AllChapters.Remove((Chapter)item);
                }
            }
         
             
        }
        #endregion

        public override bool Equals(object obj)
        {
            PlaylistItem item =(PlaylistItem) obj;
            if (this.MediaSource == item.MediaSource)
                return true;
            return false;
        }
        
    }
    [Flags]
   public enum MediaType:int
    {
        NotMedia=0,
        Image=1,
        Audio=2,
        Video=4
    }
}
