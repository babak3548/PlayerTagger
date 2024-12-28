using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Player.DataControl
{
    interface IPlayerControl
    {
        long CurrentPostion { get; }
        void Play(PlaylistItem item);
        void Play(Chapter item);
        void Stop();
        void Pause();

        void Dispose();

        Image GetImageScreen();

    }
}
