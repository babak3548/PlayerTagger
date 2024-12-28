using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Player.DataControl
{
    interface IConvertControlBase
    {
       
        void SetSourceFile(string SourceFile);
        void StartConvert();
        Dictionary<int,string> ListSuportedFormat();
    }
}
