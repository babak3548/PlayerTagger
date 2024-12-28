using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Drawing.Design;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace Player
{
   // [XmlRoot(Namespace = "urn:ArrayOfPlayList")]//911024
      //[XmlElement("file", IsNullable = false)]
   [DataContract(Name = "PlayList", Namespace = "http://www.Player.com")]
    public class Playlist
    {
        public enum StretchModeType
        {
            None = 0,
            Uniform = 1,
            UniformToFill = 2,
            Fill = 3,
        }

       

        #region --- Properties ---


         [DataMember()]
        public string Name { get; set; }

        /// <summary>
        /// Auto loads the video when the page finished loading
        /// </summary>
    [DataMember()]
        public bool AutoLoad { get; set; }
        /// <summary>
        /// Auto plays the video once it get loaded on client-side
        /// </summary>
        [DataMember()]
        public bool AutoPlay { get; set; }
        /// <summary>
        /// Displays the position and duration fields as SMPTE timecode
        /// </summary>

         [DataMember()]
        public bool DisplayTimeCode { get; set; }
        /// <summary>
        /// Uses video hardware to speed up player rendering
        /// </summary>
        /// 
         [DataMember()]
        public bool EnableCachedComposition
        { get; set; }

        /// <summary>
        /// Allow closed caption text over video during playback
        /// </summary>
        /// 
         [DataMember()]
        public bool EnableCaptions
        { get; set; }

        /// <summary>
        /// Allow player to playback offline
        /// </summary>
        /// 
         [DataMember()]
        public bool EnableOffline
        { get; set; }

     
        /// <summary>
        /// Begins playback in a muted state
        /// </summary>
        /// 
         [DataMember()]
        public bool StartMuted
        { get; set; }

        /// <summary>
        /// The stretch mode for the video
        /// </summary>
        /// 
         [DataMember()]
        public StretchModeType StretchMode
        { get; set; }
        #endregion

        List<PlaylistItem> _items;
        [DataMember()]
        public virtual List<PlaylistItem> Items
        {
            get
            {
                if (_items == null)
                {
                    _items = new List<PlaylistItem>();

                }
                return _items;
            }
        }
       

    }
}
