using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Player.DataControl
{
    interface IconvertControl
    {
        void SetTargetFile(string FileName);
        void ResetUserControl(string message);
        bool CeackBeforConvert();
    }
}
