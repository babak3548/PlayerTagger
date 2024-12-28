using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AVITRIMMERCOMLib;

namespace VideoEditor
{
  public  class ModuleNotify : IModuleCallback
    {
        public void OnModuleNotify(int cParams, ref Guid pParamIDs)
        {
            System.Windows.Forms.MessageBox.Show(pParamIDs.ToString());
        }
    }
}
