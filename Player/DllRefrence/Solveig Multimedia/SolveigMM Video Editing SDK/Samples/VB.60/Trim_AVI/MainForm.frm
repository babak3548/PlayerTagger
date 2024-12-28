VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "SMM Trim VB6.0"
   ClientHeight    =   8550
   ClientLeft      =   5820
   ClientTop       =   3555
   ClientWidth     =   8205
   DrawMode        =   1  'Blackness
   DrawStyle       =   5  'Transparent
   HasDC           =   0   'False
   LinkTopic       =   "frmMain"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   8550
   ScaleWidth      =   8205
   Begin VB.CheckBox Check1 
      Caption         =   "Frame Accuracy"
      Height          =   255
      Left            =   4800
      TabIndex        =   24
      Top             =   1200
      Width           =   1455
   End
   Begin VB.CommandButton btCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   6480
      TabIndex        =   23
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Frame Frame3 
      Caption         =   "Trimming progress"
      Height          =   615
      Left            =   120
      TabIndex        =   20
      Top             =   7560
      Width           =   7935
      Begin VB.Shape shpProgress 
         FillColor       =   &H00FF8080&
         FillStyle       =   0  'Solid
         Height          =   255
         Left            =   120
         Top             =   240
         Width           =   4095
      End
      Begin VB.Shape shpProgressBG 
         Height          =   255
         Left            =   120
         Top             =   240
         Width           =   7695
      End
   End
   Begin VB.TextBox txtElapsed 
      BackColor       =   &H8000000F&
      ForeColor       =   &H80000012&
      Height          =   270
      Left            =   3480
      Locked          =   -1  'True
      TabIndex        =   18
      TabStop         =   0   'False
      Top             =   1200
      Width           =   1155
   End
   Begin VB.CommandButton btStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   4080
      TabIndex        =   17
      Top             =   7080
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.CommandButton btTrim 
      Caption         =   "Start trimming"
      Height          =   375
      Left            =   6480
      TabIndex        =   16
      Top             =   600
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Caption         =   "Trim list"
      Height          =   3975
      Left            =   5640
      TabIndex        =   13
      Top             =   2880
      Width           =   2415
      Begin VB.ListBox List1 
         Height          =   2985
         Left            =   120
         TabIndex        =   15
         Top             =   240
         Width           =   2175
      End
      Begin VB.CommandButton btClear 
         Caption         =   "Clear"
         Height          =   375
         Left            =   480
         TabIndex        =   14
         Top             =   3480
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Click left mouse button to select start position or right mouse button to set stop position"
      Height          =   1215
      Left            =   120
      TabIndex        =   8
      Top             =   1560
      Width           =   7935
      Begin VB.CommandButton btAdd 
         Caption         =   "Add to trimlist"
         Height          =   375
         Left            =   3360
         TabIndex        =   12
         Top             =   720
         Width           =   1335
      End
      Begin VB.TextBox edStop 
         Height          =   285
         Left            =   6480
         Locked          =   -1  'True
         TabIndex        =   11
         Text            =   "00:00:00.000"
         Top             =   720
         Width           =   1095
      End
      Begin VB.TextBox edStart 
         Height          =   285
         Left            =   240
         Locked          =   -1  'True
         TabIndex        =   10
         Text            =   "00:00:00.000"
         Top             =   720
         Width           =   1095
      End
      Begin VB.Shape shpBG 
         Height          =   255
         Left            =   360
         Top             =   360
         Width           =   7095
      End
      Begin VB.Shape shpSelection 
         FillColor       =   &H00800000&
         FillStyle       =   0  'Solid
         Height          =   255
         Left            =   360
         Top             =   360
         Width           =   7095
      End
      Begin VB.Label Label1 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Width           =   7335
      End
   End
   Begin VB.CommandButton btOpen 
      Caption         =   "Set input"
      Height          =   375
      Left            =   6480
      TabIndex        =   6
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox edIn 
      Height          =   285
      Left            =   960
      TabIndex        =   5
      Top             =   120
      Width           =   5295
   End
   Begin VB.TextBox edOut 
      Height          =   285
      Left            =   960
      Locked          =   -1  'True
      TabIndex        =   4
      Top             =   600
      Width           =   5295
   End
   Begin VB.TextBox edDuration 
      Height          =   285
      Left            =   1320
      Locked          =   -1  'True
      TabIndex        =   3
      Text            =   "00:00:00.000"
      Top             =   1200
      Width           =   1095
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   6360
      Top             =   7080
   End
   Begin VB.CommandButton btPlay 
      Caption         =   "Play"
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   7080
      Width           =   1095
   End
   Begin VB.CommandButton btPause 
      Caption         =   "Pause"
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Top             =   7080
      Width           =   1095
   End
   Begin VB.PictureBox picVideoWindow 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00FFFFFF&
      ClipControls    =   0   'False
      DrawMode        =   1  'Blackness
      DrawStyle       =   5  'Transparent
      FillStyle       =   0  'Solid
      HasDC           =   0   'False
      Height          =   4095
      Left            =   120
      ScaleHeight     =   4035
      ScaleWidth      =   5415
      TabIndex        =   0
      Top             =   2880
      Width           =   5475
   End
   Begin VB.Timer tmrTimer 
      Left            =   7080
      Top             =   7080
   End
   Begin VB.Label Label5 
      Caption         =   "Supported formats: ASF, AVI, AVCHD, MKV, MP4, MOV, MP3, MPEG1, MPEG2, WAV, WMA"
      Height          =   255
      Left            =   120
      TabIndex        =   25
      Top             =   8280
      Width           =   7935
   End
   Begin VB.Label Label4 
      Caption         =   "Output file"
      Height          =   255
      Left            =   120
      TabIndex        =   22
      Top             =   600
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Input file"
      Height          =   255
      Left            =   120
      TabIndex        =   21
      Top             =   120
      Width           =   855
   End
   Begin VB.Label lblElapsed 
      AutoSize        =   -1  'True
      Caption         =   "Elapsed Time:"
      Height          =   195
      Left            =   2520
      TabIndex        =   19
      ToolTipText     =   "Elapsed Time (Seconds)"
      Top             =   1200
      Width           =   1005
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Media length"
      Height          =   195
      Left            =   240
      TabIndex        =   7
      Top             =   1200
      Width           =   915
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*******************************************************************************
'*       This is a part of the SolveigMM Video Editing SDK Code Samples.
'*       Copyright (C) 2007-2010 Solveig Multimedia.
'*******************************************************************************
Option Explicit
Option Base 0
Option Compare Text

Private m_TrimerObj As AVITRIMMERCOMLib.TrimmerObjControl 'SolveigMM AVI Trimmer COM object
Private m_ITrimerObj As AVITRIMMERCOMLib.ITrimmerObjControl
Private m_TrimerObjCB As New TrimmerObjCallBack 'Callback object
Private m_IModuleConfigVB As AVITRIMMERCOMLib.IModuleConfigForVB 'Interface intended special for VB6 applications
Private m_bstrFileNameIn As String 'Loaded file name
Private m_bstrFileNameOut As String 'Trimmed file name
Private m_Ready1 As Boolean, m_Ready2 As Boolean
Private m_dDuration As Double 'media duration in seconds
Private m_Ranges As New Collection
Private m_bNeedIndexing As Boolean
Private Type TRange
    dStart As Double
    dStop As Double
End Type
Private m_SelRange As TRange
Private m_dblStartPosition As Double       'Start position in seconds
Private m_boolVideoRunning As Boolean      'Flag used to trigger clock
Private m_objBasicVideo As IBasicVideo     'Basic Video Object
Private m_objMediaEvent As IMediaEvent     'MediaEvent Object
Private m_objVideoWindow As IVideoWindow   'VideoWindow Object
Private m_objMediaControl As IMediaControl    'MediaControl Object
Private m_objMediaPosition As IMediaPosition 'MediaPosition Object

Private Sub btAdd_Click()
    If Not m_Ready1 Then Exit Sub
    m_Ranges.Add (m_SelRange.dStart)
    m_Ranges.Add (m_SelRange.dStop)
    List1.AddItem (edStart.Text & " - " & edStop.Text)
End Sub

Private Sub btCancel_Click()
    If ObjPtr(m_TrimerObj) > 0 Then
        '''LogEvent "m_ITrimerObj.Stop()..."
        Call m_ITrimerObj.Stop
        '''LogEvent "...OK"
    End If
End Sub

Private Sub btClear_Click()
    Call ClearTrimList
End Sub

Function FileLenEx(FileName As String) As Double
  Const C_MAXINT As Double = &H7FFFFFFF
   
   FileName = Trim$(FileName)
   If LenB(FileName) Then
         FileLenEx = FileLen(FileName)
      If FileLenEx < 0 Then
         FileLenEx = (FileLenEx And C_MAXINT) + C_MAXINT + 1
      End If
   End If
End Function


Private Sub btOpen_Click()
    '''LogEvent "BEGIN btOpen_Click()"
    Dim nCount As Long
    On Local Error GoTo errline
    
    g_bCompleted = False
    g_bStopped = True
    
    ' We don't use the common file dialog to select a media file
    ' Initialize global variables based on the
    ' contents of the file:
    '   m_bstrFileNameIn - name of file name selected by the user
    '   m_dDuration = length of the file; duration
    '   m_dblStartPosition - point at which to start playing clip
    '   m_objMediaControl, m_objMediaEvent, m_objMediaPosition,
    '   m_objVideoWindow - programmable object
    'clean up memory (in case a file is already open)
    Call Form_Unload(True)
    
    'Retrieve the name of an media
    'file that the user wishes to trim.
    If edIn.Text = vbNullString Then
        MsgBox "Type or paste full path to input file into text box"
        edIn.SetFocus
        Exit Sub
    End If
    
    'check if file exists
    Dim flen As Double
    flen = FileLenEx(edIn.Text)
    If Not FileLenEx(edIn.Text) > 0 Then
        MsgBox "You must specify valid path to input file"
        edIn.SetFocus
        Exit Sub
    End If
    
    'Set input and output files names
    m_bstrFileNameIn = edIn.Text
    m_Ready1 = True
    m_bstrFileNameOut = TrimmedFileName(m_bstrFileNameIn)
    edOut.Text = m_bstrFileNameOut
    m_Ready2 = True
    
    'Clean up
    Set m_objMediaPosition = Nothing
    Set m_objVideoWindow = Nothing
    Set m_objMediaEvent = Nothing
    Set m_objMediaControl = Nothing
    
    'Instantiate a filter graph for the requested file format.
    Set m_objMediaControl = New FilgraphManager
    Call m_objMediaControl.RenderFile(m_bstrFileNameIn)
    
    'Setup the IVideoWindow object.
    'Remove the caption, border, dialog frame,
    'and scrollbars from the default window.
    'Position the window.
    'Set the parent to the app's form.
    Set m_objVideoWindow = m_objMediaControl
    m_objVideoWindow.WindowStyle = CLng(&H6000000)
    m_objVideoWindow.Top = picVideoWindow.Top
    m_objVideoWindow.Left = picVideoWindow.Left
    m_objVideoWindow.Width = picVideoWindow.Width
    m_objVideoWindow.Height = picVideoWindow.Height
    'reset the video window owner
    m_objVideoWindow.Owner = frmMain.hWnd
    picVideoWindow.Visible = False
        
    'Setup the IMediaEvent object for the
    'sample toolbar (run, pause, play).
    Set m_objMediaEvent = m_objMediaControl
    
    'Setup the IMediaPosition object so that we
    'can display the duration of the selected
    'video as well as the elapsed time.
    Set m_objMediaPosition = m_objMediaControl

    'Get media length
    m_dDuration = m_objMediaPosition.Duration
    edDuration.Text = ConvertDoubleTimeToStr(m_dDuration)

    'set the playback rate given the desired optional
    If ObjPtr(m_objMediaPosition) > 0 Then
        m_objMediaPosition.Rate = 1
    End If

    ' Reset start position to 0
    m_dblStartPosition = 0
    
    'enable run buttons by default
    btPlay.Enabled = True
    btStop.Enabled = True
    btPause.Enabled = True
    
    ' Set input to Editing Engine
    Dim var As Variant
    var = m_bstrFileNameIn
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_InputFile, var)
     
    ' Check the file type
    Call m_IModuleConfigVB.GetValueVB(SMM_Defs.SMAT_GetFileType, var)
    Dim FType As Integer
    FType = CInt(var)
    
    If FType = SMM_File_Type_AVI Then
        Check1.Enabled = False
        Check1.Value = False
    Else
        Check1.Enabled = True
        Check1.Value = True
    End If
    
    If FType <= SMM_File_Type_NO And FType > SMM_File_Type_MP4 Then
        MsgBox "Unsupported file type, trimming is not possible."
        btTrim.Enabled = False
    Else
        btTrim.Enabled = True
    End If
    If (FType >= SMM_File_Type_MPEG2_PS And FType <= SMM_File_Type_MPEG1_VES) Or (FType = SMM_File_Type_MPEG4_AVC) Then
        m_bNeedIndexing = True
    End If
        
    'Clear list of fragments
    Call btClear_Click
    ' Select all media
    Call Label1_MouseDown(vbRightButton, 0, Label1.Width, 0)
    Call Label1_MouseDown(vbLeftButton, 0, 0, 0)
    If m_bNeedIndexing Then
        Call StartIndexing
    End If
    Exit Sub
errline:
    err.Clear
    Resume Next
    Exit Sub
EndOfSub:
    Exit Sub
End Sub

Private Sub btPause_Click()
    'Invoke the MediaControl Pause() method
    'and pause the video that is being
    'displayed through the predefined
    'filter graph.
    Call m_objMediaControl.Pause
    m_boolVideoRunning = False
End Sub

Private Sub btPlay_Click()
    'Invoke the MediaControl Run() method
    'and pause the video that is being
    'displayed through the predefined
    'filter graph.
    'Assign specified starting position dependent on state
    If CLng(m_objMediaPosition.CurrentPosition) < CLng(m_dblStartPosition) Then
        m_objMediaPosition.CurrentPosition = m_dblStartPosition
    ElseIf CLng(m_objMediaPosition.CurrentPosition) = CLng(m_dDuration) Then
        m_objMediaPosition.CurrentPosition = m_dblStartPosition
    End If
    Call m_objMediaControl.Run
    m_boolVideoRunning = True
End Sub

Private Sub StartIndexing()
    Dim var As Variant
    var = edIn.Text + ".mlmix"
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_OutIndexFile, var)
    var = True
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_StartIndexation, var)
    m_bNeedIndexing = True
    Timer1.Enabled = True
End Sub

Private Sub btStop_Click()
    'Invoke the MediaControl Stop() method
    'and stop the video that is being
    'displayed through the predefined
    'filter graph.
    Call m_objMediaControl.Stop
    m_boolVideoRunning = False
    ' reset to the beginning of the video
    m_objMediaPosition.CurrentPosition = 0
    txtElapsed.Text = "00:00:00.000"
End Sub

Private Sub btTrim_Click()
    Dim tmpVar As Variant
    
    If Not m_Ready1 Then
        MsgBox "Open media you want to trim", , "Trimmer Sample"
        Exit Sub
    End If
    
    If Not m_Ready2 Then
        MsgBox "Specify output media name", , "Trimmer Sample"
        Exit Sub
    End If
    
    If m_Ranges.Count < 1 Then
        btAdd_Click 'if no ranges are in trim list add current selection
    End If
    
    On Error GoTo errline

    tmpVar = Check1.Value
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_TrimAccuracy, tmpVar)
    
    ''Set callback object
    'Set tmpVar = m_TrimerObjCB
    'Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_Callback, tmpVar)
       
    SetProgressControl (0)

On Error Resume Next
    
    'Set input file name for SmmEditEngine
    tmpVar = m_bstrFileNameIn
    
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_InputFile, tmpVar)
    
    'Set output file name for SmmEditEngine
    tmpVar = m_bstrFileNameOut
    
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_OutputFile, tmpVar)
    
On Error Resume Next
    'Commit changes
    Call m_IModuleConfigVB.CommitChangesVB(0)
    
    'creating trim list info
    Dim smmTL As SMM_Defs.TrimInfoList
    Dim smmTIArr() As SMM_Defs.tagTSTrimInfo
    ReDim smmTIArr(0 To ((m_Ranges.Count \ 2) - 1)) As SMM_Defs.tagTSTrimInfo
    
    Dim i As Integer
    Dim dbl As Double
    Dim ll As SMM_Defs.LONGLONG 'since int64 is not supported in VB6 use defined type
    Dim var As Variant
    Dim tmp As Variant
    i = 0
    
    For Each tmp In m_Ranges
        dbl = CDbl(tmp)
        var = VarPtr(ll)
        Call m_IModuleConfigVB.ConvertREFTIMEtoREFERENCETIME(dbl, var) 'since int64 is not supported in VB6
        If (i Mod 2) = 0 Then
            smmTIArr(i \ 2).llStartPos = ll
            smmTIArr(i \ 2).nPieceNum = i \ 2
        Else
            smmTIArr(i \ 2).llStopPos = ll
        End If
        i = i + 1
    Next tmp
    
    smmTL.nListSize = m_Ranges.Count \ 2
    smmTL.trim_list = VarPtr(smmTIArr(0))
    
    'setting trim list
    var = VarPtr(smmTL)
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_TrimList, var)
    
    'Commit changes
    var = True
    Call m_IModuleConfigVB.CommitChangesVB(var)
    
    g_bCompleted = False
    'g_bStopped = False
    
    Call m_ITrimerObj.Start
    
    Exit Sub
errline:
    err.Clear
End Sub

Private Sub Form_Load()
Dim tmpVar As Variant
    On Local Error GoTo errline
    'Alter the coordinate system so that we work
    'in pixels (instead of the default twips)
    frmMain.ScaleMode = 3   ' pixels
    tmrTimer.Interval = 250   '1/4 second intervals
    'disable all the control buttons by default
    btPlay.Enabled = False
    btStop.Enabled = False
    btPause.Enabled = False
    m_bNeedIndexing = False
    
    'creating SmmEditEngine object
    Set ModuleMain.g_TrimmerCOMObj = New AVITRIMMERCOMLib.TrimmerObjControl
    Set m_TrimerObj = ModuleMain.g_TrimmerCOMObj
    Set m_ITrimerObj = m_TrimerObj
    Set m_IModuleConfigVB = m_TrimerObj
    
    'Set callback object
    Set tmpVar = m_TrimerObjCB
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_Callback, tmpVar)

    'registry path to store the information about the SDK components
    'used to get the path of a component
    'for more info on using see MPEG2TrimApp
    tmpVar = "CLSID\{7750A708-3EEB-45B9-8179-077689D77E33}\Components"
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_SilentPath, tmpVar)
    'MPEG2 Codec profile
    tmpVar = "dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM"
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_CodecsSet, tmpVar)
    
    tmpVar = SMM_Defs.g_ActionKey_Trim
    Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_ActionKey, tmpVar)

    m_Ready1 = False
    m_Ready2 = False
    Exit Sub
errline:
    err.Clear
    Exit Sub
End Sub
            
Private Sub Form_LostFocus()
    frmMain.Left = frmMain.Left + 100
    frmMain.Left = frmMain.Left - 1
End Sub

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    frmMain.Left = frmMain.Left + 5
    frmMain.Left = frmMain.Left - 5
    'picVideoWindow.AutoRedraw
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Local Error GoTo errline
    
    'stop playback
    m_boolVideoRunning = False
    DoEvents
    
    'cleanup media control
    If ObjPtr(m_objMediaControl) > 0 Then
       m_objMediaControl.Stop
    End If
    
    'clean-up video window
    If ObjPtr(m_objVideoWindow) > 0 Then
       m_objVideoWindow.Left = Screen.Width * 8
       m_objVideoWindow.Height = Screen.Height * 8
       m_objVideoWindow.Owner = 0          'sets the Owner to NULL
    End If
    
    'clean-up & dereference
    If ObjPtr(m_objBasicVideo) > 0 Then Set m_objBasicVideo = Nothing
    If ObjPtr(m_objMediaControl) > 0 Then Set m_objMediaControl = Nothing
    If ObjPtr(m_objVideoWindow) > 0 Then Set m_objVideoWindow = Nothing
    If ObjPtr(m_objMediaPosition) > 0 Then Set m_objMediaPosition = Nothing
    
    Exit Sub
errline:
    err.Clear
    Exit Sub
End Sub
            
            
Private Sub mnuFileExit_Click()
    Dim frm As Form
    On Local Error GoTo errline
    
    'unload each loaded form
    For Each frm In Forms
        frm.Move Screen.Width * 8, Screen.Height * 8
        Unload frm
        Set frm = Nothing
    Next
    Exit Sub
    
errline:
    err.Clear
    Exit Sub
End Sub
            
            
Private Sub Label1_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim shR As Integer
    Dim shL As Integer
    If x + Label1.Left > shpBG.Left + shpBG.Width Then
        x = shpBG.Left + shpBG.Width - Label1.Left
    ElseIf x + Label1.Left < shpBG.Left Then
        x = shpBG.Left - Label1.Left
    End If
    If Button = vbLeftButton Then
        shR = shpSelection.Left + shpSelection.Width
        shL = Label1.Left + x
        If shR < shL Then shR = shL
    ElseIf Button = vbRightButton Then
        shL = shpSelection.Left
        shR = Label1.Left + x
        If shR < shL Then shL = shR
    End If
    shpSelection.Left = shL
    shpSelection.Width = shR - shL
    m_SelRange.dStart = (shL - shpBG.Left) * m_dDuration / shpBG.Width
    m_SelRange.dStop = (shR - shpBG.Left) * m_dDuration / shpBG.Width
    edStart.Text = ConvertDoubleTimeToStr(m_SelRange.dStart)
    edStop.Text = ConvertDoubleTimeToStr(m_SelRange.dStop)
On Error Resume Next
    If ObjPtr(m_objMediaPosition) > 0 Then
        If Button = vbLeftButton Then
            m_objMediaPosition.CurrentPosition = m_SelRange.dStart
        ElseIf Button = vbRightButton Then
            m_objMediaPosition.CurrentPosition = m_SelRange.dStop
        End If
    End If
End Sub

Private Sub Timer1_Timer()
    Dim tmp As Variant
    Dim progr As Integer
    
    If g_bStopped Then
        SetProgressControl (0)
        Exit Sub
    End If
    
    If g_bCompleted Then
        g_bStopped = True
        If m_bNeedIndexing = True Then
            m_bNeedIndexing = False
            tmp = edIn.Text + ".mlmix"
            Call m_IModuleConfigVB.SetValueVB(SMM_Defs.SMAT_MPEG2IndexFileName, tmp)
        End If
        Call MsgBox("Processing complete", , "Trimmer Sample")
        SetProgressControl (0)
        Exit Sub
    End If
    
    'get trimming progress
    If ObjPtr(m_IModuleConfigVB) > 0 Then
        Call m_IModuleConfigVB.GetValueVB(SMM_Defs.SMAT_Progress, tmp)
        progr = tmp
        SetProgressControl (progr)
    Else
        SetProgressControl (0)
    End If
err:
End Sub

Private Sub tmrTimer_Timer()

    Dim nReturnCode As Long
    Dim dblPosition As Double
    On Local Error GoTo errline
    'Retrieve the Elapsed Time and
    'display it in the corresponding
    'textbox.
    If m_boolVideoRunning = True Then
        'obtain return code
        'Call m_objMediaEvent.WaitForCompletion(100, nReturnCode)
        If nReturnCode = 0 Then
            'get the current position for display
            dblPosition = m_objMediaPosition.CurrentPosition
            txtElapsed.Text = ConvertDoubleTimeToStr(dblPosition)
        Else
            txtElapsed.Text = ConvertDoubleTimeToStr(m_dDuration)
            m_boolVideoRunning = False
        End If
    End If
    Exit Sub
errline:
    err.Clear
    Resume Next
    Exit Sub
End Sub

'Helper functions for time-to-string conversion
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

Function ConvertDoubleTimeToStr(ByVal val As Double) As String
    Dim nTotalMsec As Long
    Dim nHour As Long
    Dim nMin As Long
    Dim nSec As Long
    Dim nMsec As Long
    nTotalMsec = CLng(val * CDbl(1000))
    nHour = nTotalMsec \ CLng(3600000)
    nTotalMsec = nTotalMsec Mod CLng(3600000)
    nMin = nTotalMsec \ CLng(60000)
    nTotalMsec = nTotalMsec Mod CLng(60000)
    nSec = nTotalMsec \ CLng(1000)
    nMsec = nTotalMsec Mod CLng(1000)
    Dim str As String
    str = CStr(nHour) & ":" & IntToStr2(nMin) & ":" & IntToStr2(nSec) & "." & IntToStr3(nMsec)
    ConvertDoubleTimeToStr = str
End Function

' Procedure for extracting extention of file name
Function ExtOfFile(ByVal sz As String) As String
    Const dot = "."
    Dim lastdotpos As Integer
    lastdotpos = InStrRev(sz, dot)
    ExtOfFile = Mid(sz, lastdotpos)
End Function

Function TrimmedFileName(ByVal sz As String)
    Const dot = "."
    Dim str1 As String
    Dim lastdotpos As Integer
    lastdotpos = InStrRev(sz, dot)
    str1 = Mid(sz, 1, lastdotpos - 1)
    str1 = str1 & "_trimmed"
    str1 = str1 & Mid(sz, lastdotpos)
    TrimmedFileName = str1
End Function

Private Sub ClearTrimList()
    ' Clear trim list
    Dim i As Integer
    For i = m_Ranges.Count To 1 Step -1
        m_Ranges.Remove (i)
    Next i
    List1.Clear
End Sub

Public Sub SetProgressControl(prg As Integer)
    shpProgress.Left = shpProgressBG.Left
    shpProgress.Top = shpProgressBG.Top
    shpProgress.Height = shpProgressBG.Height
    If prg > 100 Then prg = 100
    shpProgress.Width = shpProgressBG.Width * prg / 100
End Sub


