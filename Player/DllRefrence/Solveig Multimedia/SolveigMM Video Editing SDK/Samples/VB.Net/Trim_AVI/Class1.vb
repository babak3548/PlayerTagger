Class ClassCB
    Implements AVITRIMMERCOMLib.ITrimmerObjControlCB
    Public m_Parent As Form1
    Public Overloads Sub OnStart() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnStart
        m_Parent.btOpen.Enabled = False
        m_Parent.btSave.Enabled = False
        m_Parent.AxSMM_OCXSlider1.Enabled = False
        m_Parent.btTrim.Enabled = False
        m_Parent.ProgressBar1.Value = m_Parent.ProgressBar1.Minimum
        m_Parent.flTrimmingNow = True
        m_Parent.StatusBar1.Text = "Processing Started"
    End Sub
    Public Overloads Sub OnStop() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnStop
        m_Parent.flTrimmingNow = False
        m_Parent.btOpen.Enabled = True
        m_Parent.btSave.Enabled = True
        m_Parent.AxSMM_OCXSlider1.Enabled = True
        m_Parent.btTrim.Enabled = True
        m_Parent.ProgressBar1.Value = m_Parent.ProgressBar1.Minimum
        m_Parent.StatusBar1.Text = "Processing Stopped"
    End Sub
    Public Overloads Sub OnPause() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnPause
        m_Parent.flTrimmingNow = False
        m_Parent.StatusBar1.Text = "Processing Paused"
    End Sub
    Public Overloads Sub OnError(ByVal hr As Integer, ByVal val As String) Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnError
        m_Parent.flTrimmingNow = False
        m_Parent.StatusBar1.Text = "Trimming Error Occured"
        val = val & " hr = " & CStr(hr)
        MessageBox.Show(val, "AVITRIMMERCOM Error")
    End Sub
    Public Sub New(ByRef pParent As Form1)
        m_Parent = pParent
        'MessageBox.Show("Constructor callback routine called", "AVITRIMMERCOM Notify")
    End Sub
End Class
