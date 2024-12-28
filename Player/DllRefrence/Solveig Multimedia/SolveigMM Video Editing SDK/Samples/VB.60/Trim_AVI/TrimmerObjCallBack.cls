VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TrimmerObjCallBack"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
' The class implements ITrimmerObjControlCB interface
Implements AVITRIMMERCOMLib.ITrimmerObjControlCB

Public Sub ITrimmerObjControlCB_OnError(ByVal hr As Long, ByVal val As String)
On Error GoTo errline
    g_bStopped = True
    MsgBox val, vbOKOnly, "Trimmer Sample. Error"
errline:
End Sub

Public Sub ITrimmerObjControlCB_OnPause()
On Error GoTo errline
    g_bStopped = True
errline:
End Sub

Public Sub ITrimmerObjControlCB_OnStart()
On Error GoTo errline
    g_bStopped = False
    'MsgBox "ITrimmerObjControlCB OnStart called"
errline:
End Sub

Public Sub ITrimmerObjControlCB_OnStop()
    On Error GoTo errline
    g_bCompleted = True
    'MsgBox "ITrimmerObjControlCB_OnStop() called"
errline:
End Sub

