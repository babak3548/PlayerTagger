Class ClassCB
    Implements AVITRIMMERCOMLib.ITrimmerObjControlCB
    Public m_Parent As Form1
    Public Overloads Sub OnStart() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnStart
        m_Parent.Label1.Text = "Join..."
    End Sub
    Public Overloads Sub OnStop() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnStop
        UpdateGUI()
        m_Parent.Label1.Text = "Idle"
    End Sub
    Public Overloads Sub OnPause() Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnPause
    End Sub
    Public Overloads Sub OnError(ByVal hr As Integer, ByVal val As String) Implements AVITRIMMERCOMLib.ITrimmerObjControlCB.OnError
        UpdateGUI()
        m_Parent.Label1.Text = "Error"
        val = val & " hr = " & CStr(hr)
        MessageBox.Show(val, "AVITRIMMERCOM Error")
    End Sub
    Public Sub New(ByRef pParent As Form1)
        m_Parent = pParent
    End Sub

    Private Sub UpdateGUI()
        m_Parent.m_Finished = True
        m_Parent.ProgressBar1.Value = 0
        m_Parent.ProgressBar1.Update()
    End Sub
End Class
