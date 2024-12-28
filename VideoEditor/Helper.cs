using System;
using System.Runtime.InteropServices;
using AVITRIMMERCOMLib;
using System.Windows.Forms;
namespace VideoEditor
{
	/// <summary>
	/// Class implements Editing Engine Callback and most common parameter GUIDS and structures
	/// </summary>
	public class Helper : SMM_Defs, ITrimmerObjControlCB
	{
        public Form m_Parent;
        System.Diagnostics.Stopwatch s = new System.Diagnostics.Stopwatch();
        public Helper(Form pParent)
		{
			m_Parent = pParent;
		}
        public Helper()
        {
            
        }
		void ITrimmerObjControlCB.OnError(int hr, string val)
		{
            //m_Parent.m_bCompleted = true;
            //m_Parent.m_bErrorOccured = true;
		}
        void ITrimmerObjControlCB.OnStart() { s.Start(); MessageBox.Show("start"); }
		void ITrimmerObjControlCB.OnPause() { }
		void ITrimmerObjControlCB.OnStop()
		{
            s.Stop();
            MessageBox.Show(s.ElapsedMilliseconds.ToString());
			//m_Parent.m_bCompleted = true;
		}
	}
}
