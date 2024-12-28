Imports System.Runtime.InteropServices

Public Class Form1
    Inherits System.Windows.Forms.Form
    Dim m_CB As ClassCB
    Dim m_Trimmer As AVITRIMMERCOMLib.TrimmerObjControl
    Dim m_ModuleConfig As AVITRIMMERCOMLib.IModuleConfig
    Dim m_smm_type As Integer

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()
#If restricted Then

        Const val = "Evaluation version of the SDK misses some clue headers and samples couldn't be compiled. " & "To get full version of the SolveigMM Video Editing SDK please email to info@solveigmm.com. " & "Please use the compiled sample in 'Bin/release' directory."
        MessageBox.Show(val, "Attention")
#Else
        'Add any initialization after the InitializeComponent() call
        Try
            m_Trimmer = New AVITRIMMERCOMLib.TrimmerObjControl     'creating instance of TrimmerObjControl
            m_ModuleConfig = m_Trimmer
            m_CB = New ClassCB(Me)
            Dim var As Object = m_CB
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_Callback), var)
            'registry path to store the information about the SDK components
            'used to get the path of a component
            'for more info on using see MPEG2TrimApp
            var = "CLSID\{" + SMM_Defs.CLSID_VideoEditingSDK + "}\Components"
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_SilentPath), var)

            var = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM"
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_CodecsSet), var)

            var = SMM_Defs.g_ActionKey_Join
            m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_ActionKey), var)

        Catch ex As Exception
            MessageBox.Show("Error while creating instance of AVITRIMMERCOMLib.TrimmerObjControl", "Error")
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
    Friend WithEvents btnAdd As System.Windows.Forms.Button
    Friend WithEvents ListView1 As System.Windows.Forms.ListView
    Friend WithEvents btnJoin As System.Windows.Forms.Button
    Friend WithEvents ProgressBar1 As System.Windows.Forms.ProgressBar
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents file As System.Windows.Forms.ColumnHeader
    Friend WithEvents type As System.Windows.Forms.ColumnHeader
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SaveFileDialog1 As System.Windows.Forms.SaveFileDialog
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.btnAdd = New System.Windows.Forms.Button
        Me.ListView1 = New System.Windows.Forms.ListView
        Me.file = New System.Windows.Forms.ColumnHeader
        Me.type = New System.Windows.Forms.ColumnHeader
        Me.btnJoin = New System.Windows.Forms.Button
        Me.ProgressBar1 = New System.Windows.Forms.ProgressBar
        Me.Label1 = New System.Windows.Forms.Label
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog
        Me.SuspendLayout()
        '
        'btnAdd
        '
        Me.btnAdd.Location = New System.Drawing.Point(8, 160)
        Me.btnAdd.Name = "btnAdd"
        Me.btnAdd.TabIndex = 0
        Me.btnAdd.Text = "Add File..."
        '
        'ListView1
        '
        Me.ListView1.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.file, Me.type})
        Me.ListView1.Location = New System.Drawing.Point(8, 16)
        Me.ListView1.Name = "ListView1"
        Me.ListView1.Size = New System.Drawing.Size(472, 128)
        Me.ListView1.TabIndex = 1
        Me.ListView1.View = System.Windows.Forms.View.Details
        '
        'file
        '
        Me.file.Text = "file"
        Me.file.Width = 306
        '
        'type
        '
        Me.type.Text = "type"
        '
        'btnJoin
        '
        Me.btnJoin.Location = New System.Drawing.Point(96, 160)
        Me.btnJoin.Name = "btnJoin"
        Me.btnJoin.TabIndex = 2
        Me.btnJoin.Text = "Join"
        '
        'ProgressBar1
        '
        Me.ProgressBar1.Location = New System.Drawing.Point(192, 160)
        Me.ProgressBar1.Name = "ProgressBar1"
        Me.ProgressBar1.Size = New System.Drawing.Size(208, 23)
        Me.ProgressBar1.TabIndex = 3
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(424, 160)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 23)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Idle"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Timer1
        '
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.Filter = "Audio-Video Interleaved|*.avi|MPEG Audio|*.mp3;*.mpa;*.mp1;|ASF|*.asf;*.wmv;*.wma" & _
        ";*.wm;|MPEG Video|*.mpg;*.mpeg|All Media Files|*.*"
        Me.OpenFileDialog1.Title = "Select input media file"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(488, 202)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.ProgressBar1)
        Me.Controls.Add(Me.btnJoin)
        Me.Controls.Add(Me.ListView1)
        Me.Controls.Add(Me.btnAdd)
        Me.Name = "Form1"
        Me.Text = "VB.Net ASF AVI AVC MKV MP4 MOV MP3 MPEG1 MPEG2 WAV WMA Joiner"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btnAdd_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnAdd.Click
        If OpenFileDialog1.ShowDialog = DialogResult.OK Then
            AppendList(OpenFileDialog1.FileName)
        End If
    End Sub

    Private Sub AppendList(ByVal f As String)
        Dim var As Object

        'setting input file name
        var = f
        m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_InputFile), var)

        Try
            'getting input file type
            m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_GetFileType), var)

            If CheckSupportedFileTypes(var) Then
                m_smm_type = var
                Dim li As ListViewItem
                li = ListView1.Items.Add(f)
                li.SubItems.Add(SMM_Defs.XTLDescr_TrackOutType(m_smm_type))
            Else
                m_smm_type = 0
            End If
        Catch ex As Exception
            MessageBox.Show("Invalid input" + ControlChars.NewLine + ex.ToString, "Error")
        End Try
    End Sub

    Private Function CheckSupportedFileTypes(ByVal t As Integer) As Boolean
        If t <= SMM_Defs.SMM_OutputTypes.SMM_File_Type_NO Or t >= SMM_Defs.SMM_OutputTypes.SMM_File_Type_RAW Then
            CheckSupportedFileTypes = True
        Else
            CheckSupportedFileTypes = False
        End If
    End Function

    Private Sub btnJoin_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnJoin.Click
        If SaveFileDialog1.ShowDialog = DialogResult.OK Then
            Join(SaveFileDialog1.FileName)
        End If
    End Sub

    Private Sub Join(ByVal f As String)
        Dim var As Object
        Dim cb As Integer

        'setting task type
        var = SMM_Defs.SMM_TaskType.SMM_Task_Type_Joining
        m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_TaskType), var)

        'setting output file
        var = f
        m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_OutputFile), var)

        'fill in SMM_TRACK_INFO
        Dim track As SMM_Defs.SMM_TRACK_INFO
        Dim i As Integer

        track.nVideoStream = -1
        track.nAudioStream = -1
        track.szMPEG2IdxFileName = "not used string" & ChrW(0)
        track.nClips = ListView1.Items.Count

        'fill in pClips
        Dim clips(track.nClips) As SMM_Defs.SMM_CLIP_INFO
        cb = Marshal.SizeOf(GetType(SMM_Defs.SMM_CLIP_INFO))
        track.pClips = Marshal.AllocHGlobal(cb * track.nClips)
        Dim curPointer As Int32
        curPointer = track.pClips.ToInt32()

        For i = 0 To track.nClips - 1
            Dim li As ListViewItem
            Dim curPtr As IntPtr = New IntPtr(curPointer + i * cb)
            li = ListView1.Items.Item(i)
            AddClipToTrack(clips(i), li.Text)
            Marshal.StructureToPtr(clips(i), curPtr, False)
        Next

        track.nOutType = m_smm_type
        track.nTrimmAccurType = -1
        track.ulFlags = Convert.ToUInt32(0)
        track.dwASMode = 0
        track.llASValue = Convert.ToInt64(0)
        track.nTrackPos = Convert.ToUInt32(0)
        ReDim track.dwReserv(20)
        'test purposes
        For i = 0 To 19
            track.dwReserv(i) = Convert.ToUInt32(i)
        Next

        'setting SMM_TRACK_INFO
        cb = Marshal.SizeOf(track)
        Dim ptr As IntPtr = Marshal.AllocHGlobal(cb)
        Marshal.StructureToPtr(track, ptr, False)
        var = ptr

        m_ModuleConfig.SetValue(New Guid(SMM_Defs.SMAT_TrackInfo), var)

        Marshal.DestroyStructure(track.pClips, GetType(SMM_Defs.SMM_CLIP_INFO))
        Marshal.FreeHGlobal(track.pClips)
        Marshal.DestroyStructure(ptr, GetType(SMM_Defs.SMM_TRACK_INFO))
        Marshal.FreeHGlobal(ptr)

        'commit
        var = 0
        m_ModuleConfig.CommitChanges(var)

        Dim bRun As Boolean = True

        Try
            Dim hr As Integer
            'validate files for joining
            m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_ValidateFiles), var)

            hr = Convert.ToInt32(var)

            If (hr = 1) Then
                If (MessageBox.Show("Some chosen tracks have different parameters!" + ControlChars.NewLine + _
                "There may be some problems during output file playback." + ControlChars.NewLine + _
                "Would you like to continue?", "Hmm", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) = DialogResult.No) Then
                    bRun = False
                End If
            End If

        Catch ex As Exception
            Dim hr As Integer = Marshal.GetHRForException(ex)
            MessageBox.Show("Validate files HRESULT=0x" + hr.ToString(), "Error")
        End Try

        If bRun Then
            Try
                'run
                m_Trimmer.Start()
                Timer1.Enabled = True
            Catch ex As Exception
                MessageBox.Show("On start join", "Error")
            End Try
        End If
    End Sub

    Private Sub AddClipToTrack(ByRef clip As SMM_Defs.SMM_CLIP_INFO, ByRef s As String)
        Dim i As Integer
        clip.dwClipNum = Convert.ToUInt32(0)
        clip.rtStart = Convert.ToInt64(0)
        clip.rtStop = Convert.ToInt64(0)
        clip.bMute = 0
        clip.wsfName = s & ChrW(0)
        ReDim clip.dwReserv(20)
        'test purposes
        For i = 0 To 19
            clip.dwReserv(i) = Convert.ToUInt32(i)
        Next
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim var As Object
        'getting current trimming progress
        m_ModuleConfig.GetValue(New Guid(SMM_Defs.SMAT_Progress), var)
        Dim progress As Integer = CInt(var)

        If progress < ProgressBar1.Minimum Then progress = ProgressBar1.Minimum
        If progress > ProgressBar1.Maximum Then progress = ProgressBar1.Maximum
        ProgressBar1.Value = progress
        ProgressBar1.Update()
    End Sub
End Class
