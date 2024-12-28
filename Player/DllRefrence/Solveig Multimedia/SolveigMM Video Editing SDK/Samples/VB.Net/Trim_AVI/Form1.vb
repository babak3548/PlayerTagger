Imports System.Runtime.InteropServices

Public Class Form1
    Inherits System.Windows.Forms.Form
    Dim m_CB As ClassCB
    Dim m_Duration As Double
    Dim m_Trimmer As AVITRIMMERCOMLib.TrimmerObjControl
    Dim m_ModuleConfig As AVITRIMMERCOMLib.IModuleConfig
    Dim flReady0 As Boolean = False
    Dim flReady1 As Boolean = False
    Dim flMpeg2Ves As Boolean = False
    Public flTrimmingNow As Boolean = False
    Dim XTLDescr_TrackOutType() As String = {"no type", "avi", "asf", "mpa", "mpg_ps", "mpg_ts", "mpg_ves", "mpg1_sys", "mpg1_ves", "wav", "avc_ves", "matroska", "mp4", "raw"}
#Region " Windows Form Designer generated code "
    Public Sub New()
        MyBase.New()
        'This call is required by the Windows Form Designer.
        InitializeComponent()
        'Add any initialization after the InitializeComponent() call
#If restricted Then

        Const val = "Evaluation version of the SDK misses some clue headers and samples couldn't be compiled. " & "To get full version of the SolveigMM Video Editing SDK please email to info@solveigmm.com. " & "Please use the compiled sample in 'Bin/release' directory."
        MessageBox.Show(val, "Attention")
#Else
        AxSMM_OCXSlider1.Enabled = False
        Try
            m_Trimmer = New AVITRIMMERCOMLib.TrimmerObjControl     'creating instance of TrimmerObjControl
            m_ModuleConfig = m_Trimmer
            m_CB = New ClassCB(Me)
            Dim var As Object = m_CB
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_Callback), var)
            'registry path to store the information about the SDK components
            'used to get the path of a component
            'for more info on using see MPEG2TrimApp
            var = "CLSID\{7750A708-3EEB-45b9-8179-077689D77E33}\Components"
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_SilentPath), var)

            var = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM"
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_CodecsSet), var)

            var = SMM_Defs.g_ActionKey_Trim
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_ActionKey), var)

            flReady0 = True
        Catch ex As Exception
            MessageBox.Show("Error while creating instance of AVITRIMMERCOMLib.TrimmerObjControl", "Error")
            flReady0 = False
        End Try
    End Sub
    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents btOpen As System.Windows.Forms.Button
    Friend WithEvents btTrim As System.Windows.Forms.Button
    Friend WithEvents edStop As System.Windows.Forms.TextBox
    Friend WithEvents edStart As System.Windows.Forms.TextBox
    Friend WithEvents edDuration As System.Windows.Forms.TextBox
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SaveFileDialog1 As System.Windows.Forms.SaveFileDialog
    Friend WithEvents edInFile As System.Windows.Forms.TextBox
    Friend WithEvents edOutFile As System.Windows.Forms.TextBox
    Friend WithEvents ProgressBar1 As System.Windows.Forms.ProgressBar
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents btSave As System.Windows.Forms.Button
    Friend WithEvents lbOutpuType As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Public WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents btStop As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents StatusBar1 As System.Windows.Forms.StatusBar
    Friend WithEvents AxSMM_OCXSlider1 As AxSMM_OCXSliderLib.AxSMM_OCXSlider
    Friend WithEvents cbFATrim As System.Windows.Forms.CheckBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.btOpen = New System.Windows.Forms.Button
        Me.btTrim = New System.Windows.Forms.Button
        Me.edStop = New System.Windows.Forms.TextBox
        Me.edStart = New System.Windows.Forms.TextBox
        Me.edDuration = New System.Windows.Forms.TextBox
        Me.edInFile = New System.Windows.Forms.TextBox
        Me.edOutFile = New System.Windows.Forms.TextBox
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.ProgressBar1 = New System.Windows.Forms.ProgressBar
        Me.Label1 = New System.Windows.Forms.Label
        Me.btSave = New System.Windows.Forms.Button
        Me.lbOutpuType = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.btStop = New System.Windows.Forms.Button
        Me.Label3 = New System.Windows.Forms.Label
        Me.StatusBar1 = New System.Windows.Forms.StatusBar
        Me.AxSMM_OCXSlider1 = New AxSMM_OCXSliderLib.AxSMM_OCXSlider
        Me.cbFATrim = New System.Windows.Forms.CheckBox
        CType(Me.AxSMM_OCXSlider1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'btOpen
        '
        Me.btOpen.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btOpen.Location = New System.Drawing.Point(8, 7)
        Me.btOpen.Name = "btOpen"
        Me.btOpen.Size = New System.Drawing.Size(96, 22)
        Me.btOpen.TabIndex = 0
        Me.btOpen.Text = "Open"
        '
        'btTrim
        '
        Me.btTrim.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btTrim.Location = New System.Drawing.Point(8, 80)
        Me.btTrim.Name = "btTrim"
        Me.btTrim.Size = New System.Drawing.Size(48, 21)
        Me.btTrim.TabIndex = 1
        Me.btTrim.Text = "Trim"
        '
        'edStop
        '
        Me.edStop.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.edStop.Location = New System.Drawing.Point(304, 120)
        Me.edStop.Name = "edStop"
        Me.edStop.ReadOnly = True
        Me.edStop.TabIndex = 2
        Me.edStop.Text = ""
        Me.edStop.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'edStart
        '
        Me.edStart.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.edStart.Location = New System.Drawing.Point(8, 120)
        Me.edStart.Name = "edStart"
        Me.edStart.ReadOnly = True
        Me.edStart.TabIndex = 4
        Me.edStart.Text = ""
        Me.edStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'edDuration
        '
        Me.edDuration.Location = New System.Drawing.Point(184, 120)
        Me.edDuration.Name = "edDuration"
        Me.edDuration.ReadOnly = True
        Me.edDuration.TabIndex = 5
        Me.edDuration.Text = "No file"
        Me.edDuration.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'edInFile
        '
        Me.edInFile.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.edInFile.Location = New System.Drawing.Point(112, 9)
        Me.edInFile.Name = "edInFile"
        Me.edInFile.ReadOnly = True
        Me.edInFile.Size = New System.Drawing.Size(352, 20)
        Me.edInFile.TabIndex = 7
        Me.edInFile.Text = ""
        '
        'edOutFile
        '
        Me.edOutFile.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.edOutFile.Location = New System.Drawing.Point(112, 43)
        Me.edOutFile.Name = "edOutFile"
        Me.edOutFile.ReadOnly = True
        Me.edOutFile.Size = New System.Drawing.Size(352, 20)
        Me.edOutFile.TabIndex = 8
        Me.edOutFile.Text = ""
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.Filter = "Media Files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv" & _
        ";*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;" & _
        "*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*" & _
        ".wmv|All Files|*.*"
        Me.OpenFileDialog1.RestoreDirectory = True
        '
        'SaveFileDialog1
        '
        Me.SaveFileDialog1.RestoreDirectory = True
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        '
        'ProgressBar1
        '
        Me.ProgressBar1.Location = New System.Drawing.Point(112, 88)
        Me.ProgressBar1.Name = "ProgressBar1"
        Me.ProgressBar1.Size = New System.Drawing.Size(352, 14)
        Me.ProgressBar1.TabIndex = 9
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(128, 120)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(47, 16)
        Me.Label1.TabIndex = 10
        Me.Label1.Text = "Duration"
        '
        'btSave
        '
        Me.btSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btSave.Location = New System.Drawing.Point(8, 40)
        Me.btSave.Name = "btSave"
        Me.btSave.Size = New System.Drawing.Size(96, 23)
        Me.btSave.TabIndex = 13
        Me.btSave.Text = "Save As"
        '
        'lbOutpuType
        '
        Me.lbOutpuType.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lbOutpuType.Location = New System.Drawing.Point(472, 24)
        Me.lbOutpuType.Name = "lbOutpuType"
        Me.lbOutpuType.Size = New System.Drawing.Size(88, 16)
        Me.lbOutpuType.TabIndex = 16
        Me.lbOutpuType.Text = "____________"
        Me.lbOutpuType.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label2
        '
        Me.Label2.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Label2.Location = New System.Drawing.Point(472, 8)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(88, 16)
        Me.Label2.TabIndex = 17
        Me.Label2.Text = "Output type"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'btStop
        '
        Me.btStop.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btStop.Location = New System.Drawing.Point(56, 80)
        Me.btStop.Name = "btStop"
        Me.btStop.Size = New System.Drawing.Size(48, 21)
        Me.btStop.TabIndex = 20
        Me.btStop.Text = "Stop"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(232, 72)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(112, 16)
        Me.Label3.TabIndex = 21
        Me.Label3.Text = "Progress"
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'StatusBar1
        '
        Me.StatusBar1.Location = New System.Drawing.Point(0, 260)
        Me.StatusBar1.Name = "StatusBar1"
        Me.StatusBar1.Size = New System.Drawing.Size(592, 22)
        Me.StatusBar1.TabIndex = 19
        Me.StatusBar1.Text = "StatusBar1"
        '
        'AxSMM_OCXSlider1
        '
        Me.AxSMM_OCXSlider1.Location = New System.Drawing.Point(0, 152)
        Me.AxSMM_OCXSlider1.Name = "AxSMM_OCXSlider1"
        Me.AxSMM_OCXSlider1.OcxState = CType(resources.GetObject("AxSMM_OCXSlider1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxSMM_OCXSlider1.Size = New System.Drawing.Size(592, 104)
        Me.AxSMM_OCXSlider1.TabIndex = 23
        '
        'cbFATrim
        '
        Me.cbFATrim.Location = New System.Drawing.Point(424, 120)
        Me.cbFATrim.Name = "cbFATrim"
        Me.cbFATrim.Size = New System.Drawing.Size(160, 24)
        Me.cbFATrim.TabIndex = 24
        Me.cbFATrim.Text = "Frame Accurate Trimming"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(592, 282)
        Me.Controls.Add(Me.cbFATrim)
        Me.Controls.Add(Me.AxSMM_OCXSlider1)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.btStop)
        Me.Controls.Add(Me.StatusBar1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.lbOutpuType)
        Me.Controls.Add(Me.btSave)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.edOutFile)
        Me.Controls.Add(Me.edInFile)
        Me.Controls.Add(Me.edDuration)
        Me.Controls.Add(Me.edStart)
        Me.Controls.Add(Me.edStop)
        Me.Controls.Add(Me.ProgressBar1)
        Me.Controls.Add(Me.btTrim)
        Me.Controls.Add(Me.btOpen)
        Me.MaximizeBox = False
        Me.MaximumSize = New System.Drawing.Size(1200, 1024)
        Me.MinimumSize = New System.Drawing.Size(600, 200)
        Me.Name = "Form1"
        Me.Text = "SolveigMM ASF AVI AVC MOV MKV MP4 MP3 MPEG1 MPEG2 WAV WMA VB.Net Trimmer"
        CType(Me.AxSMM_OCXSlider1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region
    Private Sub btOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btOpen.Click
        If OpenFileDialog1.ShowDialog = DialogResult.OK Then
            edInFile.Text = OpenFileDialog1.FileName
            If flReady0 Then
                Dim var As Object
                var = OpenFileDialog1.FileName
                m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_InputFile), var) 'setting input file name
                flReady1 = True
            End If

            AxSMM_OCXSlider1.SetPos(0)
            AxSMM_OCXSlider1.Enabled = True
            If flReady0 Then
                Try
                    Dim vardur As Object
                    m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_StreamLength), vardur) 'getting stream duration
                    m_Duration = vardur

                Catch ex As Exception
                    MessageBox.Show("Error while creating instance of AVITRIMMERCOMLib.TrimmerObjControl", "Error")
                    flReady0 = False
                End Try
            End If
            AxSMM_OCXSlider1().SetRange(10000000.0 * m_Duration)
            edDuration.Text = ConvertDoubleTimeToStr(m_Duration)
            edOutFile.Text = ""

            Dim Type As SMM_Defs.SMM_OutputTypes
            lbOutpuType.Text = TypeOfFile(Type)

            If Type = SMM_Defs.SMM_OutputTypes.SMM_File_Type_AVI Then
                'Frame accurate trimming for AVI files is not supported
                cbFATrim.Enabled = False
                cbFATrim.Checked = False
            Else
                'For other formats we can choose between GOP and Frame accuracy
                'But Frame is by default
                cbFATrim.Enabled = True
                cbFATrim.Checked = True
            End If
            edStart.Text = Convert100nsTimeToStr(AxSMM_OCXSlider1.GetPos())
            edStop.Text = Convert100nsTimeToStr(AxSMM_OCXSlider1.GetRange())
        End If
    End Sub
    Private Sub btSave_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btSave.Click
        If flReady0 And flReady1 Then
            GetOutputFile()
        End If
    End Sub
    Private Sub btTrim_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btTrim.Click
        If flReady0 And flReady1 Then
            If edOutFile.Text() = "" Then
                If Not GetOutputFile() Then
                    MessageBox.Show("Output file is not specified", "Error")
                    Return
                End If
            End If
            'Set the trimming operation
            Dim operation As Object = SMM_Defs.SMM_TaskType.SMM_Task_Type_Trimming
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_TaskType), operation)

            'Create a list of fragments
            Dim maxi As Integer = AxSMM_OCXSlider1.GetIntervalsCount()
            If maxi > 30 Then
                maxi = 29
                MessageBox.Show("Maximum 30 intervals in this demo sample")
            Else
                maxi = maxi - 1
            End If
            Dim TrimList As SMM_Defs.TrimInfoList
            TrimList.nListSize = maxi + 1 'Count of pieces

            Dim tmp(30) As SMM_Defs.__TSTrimInfo 'size of array = Count of pieces
            Dim i As Integer
            For i = 0 To maxi
                Dim item As SMM_Defs.CInterval_info = GetIntervalInfo(i)
                tmp(i).nPieceNum = i 'Number of the piece (not used)
                tmp(i).llStartPos = item.llstart 'start of current interval
                tmp(i).llStopPos = item.llend 'end of current interval
            Next
            ' next operations required for sending pointer on TrimList structure to IModuleConfig
            TrimList.trim_list = Marshal.UnsafeAddrOfPinnedArrayElement(tmp, 0) 'getting pointer to array
            Dim cb As Integer = Marshal.SizeOf(TrimList)
            Dim ptr As IntPtr = Marshal.AllocHGlobal(cb) ' reallocating memory for object
            Marshal.StructureToPtr(TrimList, ptr, True) ' copying object to memory block
            Dim var As Object = ptr
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_TrimList), var) ' putting list with triminfo to object
            Marshal.DestroyStructure(ptr, GetType(SMM_Defs.TrimInfoList)) ' clear the memory block
            Marshal.FreeHGlobal(ptr)                              ' free the memory block

            'Set trimming accuracy
            Dim objAccuracy As Object = Convert.ToInt32(cbFATrim.Checked)
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_TrimAccuracy), objAccuracy)
            m_ModuleConfig.CommitChanges(0) ' commit all parameters set
            Try
                m_Trimmer.Start()
            Catch ex As Exception
                MessageBox.Show("Failed at start trimming", "Error")
            End Try
        End If
    End Sub
    Private Function GetOutputFile() As Boolean
        Dim sz = ExtOfFile(edInFile.Text)
        SaveFileDialog1.DefaultExt = sz
        sz = "*" & sz
        sz = sz & "|" & sz
        SaveFileDialog1.Filter = sz
        SaveFileDialog1.FileName = "Default"
        ' previous few operations with SaveDialog required because of output file name must have same extention as input file name
        If SaveFileDialog1.ShowDialog = DialogResult.OK Then
            edOutFile.Text = SaveFileDialog1.FileName
            Dim var As Object
            var = SaveFileDialog1.FileName
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_OutputFile), var) 'setting output file name
            GetOutputFile = True
        Else
            GetOutputFile = False
        End If
    End Function
    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        GetTrimState()
    End Sub
    Public Sub GetTrimState()
        If flTrimmingNow Then
            Dim var As Object
            m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_Progress), var) 'getting current trimming progress
            Dim progress As Integer = CInt(var)

            If progress < ProgressBar1.Minimum Then progress = ProgressBar1.Minimum
            If progress > ProgressBar1.Maximum Then progress = ProgressBar1.Maximum
            ProgressBar1.Value = progress
            ProgressBar1.Update()
        End If
    End Sub
    Private Sub btStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btStop.Click
        Try
            m_Trimmer.Stop()
        Catch ex As Exception
            'MessageBox.Show("Failed at stop trimming", "Error")
        End Try
    End Sub
    Private Sub UpdateStartEndTimes()
        Dim curNum As Integer = AxSMM_OCXSlider1.GetCurrentInterval()
        Dim intervalInfo As SMM_Defs.CInterval_info
        intervalInfo = GetIntervalInfo(curNum)
        If (intervalInfo.N = -1 Or intervalInfo.N >= AxSMM_OCXSlider1.GetIntervalsCount()) Then
            intervalInfo.llstart = 0
            intervalInfo.llend = 0
        End If
        edStart.Text = Convert100nsTimeToStr(intervalInfo.llstart)
        edStop.Text = Convert100nsTimeToStr(intervalInfo.llend)
    End Sub
    Function GetIntervalInfo(ByVal num As Integer) As SMM_Defs.CInterval_info
        Dim intervalInfo As SMM_Defs.CInterval_info
        Dim ptr As IntPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(intervalInfo))
        AxSMM_OCXSlider1.GetIntervalInfo1(num, ptr.ToInt32())
        intervalInfo = CType(Marshal.PtrToStructure(ptr, GetType(SMM_Defs.CInterval_info)), SMM_Defs.CInterval_info)
        Marshal.FreeCoTaskMem(ptr)
        GetIntervalInfo = intervalInfo
    End Function
    Function IntToStr2(ByVal val As Integer) As String
        If (val < 10) Then
            IntToStr2 = "0" & CStr(val)
        Else
            IntToStr2 = CStr(val)
        End If
    End Function
    Function IntToStr3(ByVal val As Integer) As String
        If (val < 100) Then
            IntToStr3 = "0" & IntToStr2(val)
        Else
            IntToStr3 = CStr(val)
        End If
    End Function
    ' Generate time string from value in second units
    Function ConvertDoubleTimeToStr(ByVal val As Double) As String
        Dim nTotalMsec As Integer = val * 1000
        Dim nHour As Integer
        Dim nMin As Integer
        Dim nSec As Integer
        Dim nMsec As Integer
        nHour = Math.DivRem(nTotalMsec, 3600000, nMin)
        nMin = Math.DivRem(nMin, 60000, nSec)
        nSec = Math.DivRem(nSec, 1000, nMsec)
        Dim str As String
        str = CStr(nHour) & ":" & IntToStr2(nMin) & ":" & IntToStr2(nSec) & "." & IntToStr3(nMsec)
        ConvertDoubleTimeToStr = str
    End Function
    ' Generate time string from value in 100nanosecond units
    Function Convert100nsTimeToStr(ByVal val As Int64) As String
        Convert100nsTimeToStr = ConvertDoubleTimeToStr(val / 10000000)
    End Function
    ' Procedure for extracting extention of file name
    Function ExtOfFile(ByVal sz As String) As String
        Const dot = "."
        Dim lastdotpos = sz.LastIndexOf(dot)
        ExtOfFile = sz.Substring(lastdotpos, sz.Length - lastdotpos)
    End Function
    Private Sub AxSMM_OCXSlider1_SliderMoving(ByVal sender As Object, ByVal e As System.EventArgs) Handles AxSMM_OCXSlider1.SliderMoving
        UpdateStartEndTimes()
    End Sub
    Private Sub AxSMM_OCXSlider1_MarkerMoving(ByVal sender As Object, ByVal e As AxSMM_OCXSliderLib._DSMM_OCXSliderEvents_MarkerMovingEvent) Handles AxSMM_OCXSlider1.MarkerMoving
        UpdateStartEndTimes()
    End Sub
    Function TypeOfFile(ByRef Type As SMM_Defs.SMM_OutputTypes) As String
        'Returns type of file currently set in Editing Engine
        Dim var As Object
        m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_GetFileType), var)
        Type = CInt(var)
        TypeOfFile = XTLDescr_TrackOutType(CInt(var))
    End Function

    Protected Overrides Sub Finalize()
        MyBase.Finalize()
    End Sub
End Class
