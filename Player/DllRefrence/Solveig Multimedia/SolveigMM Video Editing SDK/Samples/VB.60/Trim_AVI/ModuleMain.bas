Attribute VB_Name = "ModuleMain"
'*******************************************************************************
'*       This is a part of the SolveigMM Video Editing SDK Code Samples.
'*       Copyright (C) 2007-2010 Solveig Multimedia.
'*******************************************************************************
Public g_TrimmerCOMObj As Object
Public g_bStopped As Boolean
Public g_bCompleted As Boolean

Sub LogEvent(str As String)
    Call App.LogEvent(str, vbLogEventTypeInformation)
    Debug.Print str
End Sub
Sub LogError(str As String)
    Call App.LogEvent(str, vbLogEventTypeError)
    Debug.Print str
End Sub

Sub Main()
On Error GoTo errcreate
    Dim strLogFile As String
    Dim s As String
    Dim m As Integer
    g_bStopped = True
    g_bCompleted = False
   
    'Test creating and checking of SolveigMM EditEngine COM Object
    Set g_TrimmerCOMObj = New AVITRIMMERCOMLib.TrimmerObjControl
   
    Dim l_IModuleConfigVB As AVITRIMMERCOMLib.IModuleConfigForVB 'Interface intended special for VB6 applications
 
On Error GoTo nointerface
    Set l_IModuleConfigVB = g_TrimmerCOMObj 'check object suppurt IModuleConfigForVB interface
    Set l_IModuleConfigVB = Nothing 'release interface

On Error GoTo errcreateform
    frmMain.Show
    Exit Sub

nointerface:
    MsgBox "Failed QI IModuleConfigVB. May be SolveigMM EditEngine has an obsolete version. Application can not run.", , "Trimmer Sample. Error"
    Exit Sub

errcreate:
    MsgBox "Error creating SolveigMM EditEngine COM Object. Object is not registred. Application can not run.", , "Trimmer Sample. Error"
    Exit Sub

errcreateform:
    MsgBox "Error creating main form. Application can not run.", , "Trimmer Sample. Error"
    Exit Sub
    
End Sub

