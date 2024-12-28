using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using AVITRIMMERCOMLib;
namespace CJoiner
{
	/// <summary>
	/// Class implements Editing Engine Callback and most common parameter GUIDS and structures
	/// </summary>
	public class Helper : SMM_Defs, ITrimmerObjControlCB
	{
		public Form1 m_Parent;
		public Helper( Form1 pParent )
		{
			m_Parent = pParent;
		}
		void ITrimmerObjControlCB.OnError(int hr, string val)
		{
			m_Parent.m_bErrorOccured = true;
            m_Parent.m_bFinished = true;
			MessageBox.Show( val, "Error" );
		}
		void ITrimmerObjControlCB.OnStart() { }
		void ITrimmerObjControlCB.OnPause() { }
		void ITrimmerObjControlCB.OnStop()
		{
            m_Parent.m_bFinished = true;
		}
	}
}
