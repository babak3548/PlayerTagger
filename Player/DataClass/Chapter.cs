using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Drawing.Design;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Drawing;
using System.Collections.ObjectModel;
using Player.Setting;
using System.Xml.Serialization;
using Player.DataControl;
namespace Player
{

    public enum ChapterPosition
    {
        start,
        end
    }

    [DataContract()]
    public class Chapter : INotifyPropertyChanged, IComparable//, IDisposable
    {

        public static ObservableCollection<Chapter> Chapters = new ObservableCollection<Chapter>();
        private static Chapter onChapter;
        public bool played
        {
            get { return this == onChapter; }
        }
        public void SetPlayeing()
        {
            //if (onChapter != null)
            //    onChapter.NotifyPropertyChanged("played");
            //onChapter = this;
            NotifyPropertyChanged("played");

        }
        public Chapter()
            : this(0, "", "", "")
        { }


        public Chapter(long? position, string title, string thumbnailSource, string desc)
        {
            startPosition = position;
            Title = title;
            ThumbnailSource = thumbnailSource;
            Description = desc;
            Chapters.Add(this);
            NotifyPropertyChanged("Chapters");
        }

        public Chapter(long position, string title, string thumbnailSource, string desc, System.Drawing.Image img)
        {
            StartPosition = position;
            Title = title;
            ThumbnailSource = thumbnailSource;
            Description = desc;
            ThumbnailImage = img;
            Chapters.Add(this);
            NotifyPropertyChanged("Chapters");
        }

        private bool selected = false;

        public bool Selected
        {
            get { return selected; }
            set { selected = value; NotifyPropertyChanged("Selected"); }
        }

        private System.Drawing.Image thumbnailImage;
        public System.Drawing.Image ThumbnailImage
        {
            get
            {
                if (thumbnailImage == null && !string.IsNullOrEmpty(ThumbnailSource))
                {
                    ReloadThumbnailImage();
                }
                return thumbnailImage;
            }
            set { thumbnailImage = value; }
        }
        public PlaylistItem SourceMedia { get; set; }

        public string LenghText { get { return ((long)Convert.ToInt32(EndPosition - StartPosition)).MeliSecToTimeString(); } }
        public double? Lengh { get { return (EndPosition - StartPosition); } }

        /// <summary>
        /// Position in seconds, decimal accepts as milliseconds
        /// </summary>
        /// 

        private long? startPosition;
        [DataMember()]
        public long? StartPosition
        {
            get { return startPosition; }
            set { if (value < EndPosition || EndPosition == null)startPosition = value; onPositionChange(); }
        }

        public string StartPositionText
        {
            // get { return ConvertToTimeFormat(Convert.ToInt32( startPosition)); }
            get { return ((long)startPosition).MeliSecToTimeString(); }
            set { startPosition = value.StringToMeliSec((long)startPosition) <= VLCPlayer.TotalDuritionFile ? value.StringToMeliSec((long)startPosition) : ((long)startPosition); }
        }

        private string ConvertToTimeFormat(long Time)
        {
            return Time.ToString();
            //  return string.Format("{0:d2}:{1:d2}",Time / 60, Time % 60);
        }

        private long? endPosition;
        [DataMember()]
        public long? EndPosition
        {
            get { return endPosition; }
            set { if (value > startPosition | startPosition == null) endPosition = value; onPositionChange(); }
        }


        public string EndPositionText
        {

            get
            {
                if (EndPosition == null)
                    return null;
                return ((long)EndPosition).MeliSecToTimeString();
            }
            set { EndPosition = value.StringToMeliSec(EndPosition) <= VLCPlayer.TotalDuritionFile ? value.StringToMeliSec(EndPosition) : EndPosition; }
        }

        [DataMember()]
        public string ThumbnailSource { get; set; }

        private string group;

        [DataMember()]
        public string Group
        {
            get { return group; }
            set { group = value; NotifyPropertyChanged("Group"); }
        }


        private string title;
        [DataMember()]
        public string Title
        {
            get { return title; }
            set { title = value; NotifyPropertyChanged("Title"); }
        }


        private string description;
        [DataMember()]
        public string Description
        {
            get { return description; }
            set { description = value; NotifyPropertyChanged("Description"); }
        }
        [DataMember()]
        public string ExtensionFile { get; set; }

        public void ReloadThumbnailImage()
        {
            if (System.IO.File.Exists(App.PicDir + ThumbnailSource))
                ThumbnailImage = Image.FromFile(App.PicDir + ThumbnailSource);
            else
                ThumbnailImage = Properties.Resources.Image1;

        }


        DevExpress.XtraEditors.Repository.TrackBarRange barRange = new DevExpress.XtraEditors.Repository.TrackBarRange();
        public DevExpress.XtraEditors.Repository.TrackBarRange BarRange
        {
            get { return barRange; }
            set { barRange = value; startPosition = value.Minimum; endPosition = value.Maximum; }
        }
        private void onPositionChange()
        {
            barRange.Minimum = Convert.ToInt32(startPosition);
            barRange.Maximum = Convert.ToInt32(endPosition);
            NotifyPropertyChanged("BarRange");

        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(String info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }
        public string FullInfoHtml { get { return GetFullInfoHtml(); } }

        public string GetFullInfoHtml()
        {
            string ret = string.Format("<b>{0}</b>", Title);


            if (!string.IsNullOrEmpty(Group)) ret += string.Format("\r\n{1}: <b>{0}</b>", "گروه", Group);
            if (!string.IsNullOrEmpty(LenghText)) ret += string.Format("\r\n{1}: <b>{0}</b>", "زمان", LenghText);
            //if (!string.IsNullOrEmpty(Description)) ret += string.Format("\r\n{1}: <b>{0}</b>", Description, "توضیحات:");
            //ret += string.Format("\r\n{2}: <b>{0}({1:p})</b>", EnumTitlesKeeper<CustomerDiscountLevel>.GetTitle(DiscountLevel), Discount, Properties.Resources.DiscountLevel);
            if (!string.IsNullOrEmpty(Description)) ret += string.Format("\r\n{1}: <i>{0}</i>", "توضیحات:", Description);


            return ret;
        }


        public int CompareTo(object obj)
        {
            Chapter cobj = obj as Chapter;
            if (cobj == null) return 1;

            if (this.StartPosition != null && this.StartPosition > cobj.StartPosition) return 1;

            else if (this.StartPosition != null && this.StartPosition < cobj.StartPosition) return -1;
            return 0;
        }



       //public void Dispose()
       // {
       //     GC.Collect();
       //     GC.SuppressFinalize(this);
       // }
    }
}

