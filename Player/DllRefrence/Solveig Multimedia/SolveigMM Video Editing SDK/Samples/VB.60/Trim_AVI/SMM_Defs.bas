Attribute VB_Name = "SMM_Defs"
'*******************************************************************************
'*       This is a part of the SolveigMM Video Editing SDK Code Samples.
'*       Copyright (C) 2007 Solveig Multimedia.
'*******************************************************************************
    '---------------------------------------------------------------------------------
    





    "Evalution version of the SDK misses some clue headers and samples couldn't be compiled."
    "To get full version of the SolveigMM Video Editing SDK please email to info@solveigmm.com"
    






    'Parameter GUIDs are available in the full SDK version
    '---------------------------------------------------------------------------------
    Public Const SMM_File_Type_NO = 0
    Public Const SMM_File_Type_AVI = 1  '  // audio video interleaving format
    Public Const SMM_File_Type_ASF = 2  '  // advanced streaming format
    Public Const SMM_File_Type_MPA = 3  '  // mpeg audio
    Public Const SMM_File_Type_MPEG2_PS = 4 ',  // MPEG-2 Program Stream
    Public Const SMM_File_Type_MPEG2_TS = 5 ',  // MPEG-2 Transpot Stream
    Public Const SMM_File_Type_MPEG2_VES = 6 '   // MPEG-2 Video Elementary Stream
    '---------------------------------------------------------------------------------
    'since int64 is not supported by VB6
    Public Type LONGLONG
        Lo As Long 'High dword
        Hi As Long 'Low  dword
    End Type
    '---------------------------------------------------------------------------------
    'structure decribing one trim interval
    Public Type tagTSTrimInfo
        nPieceNum As Integer ' //int16 ' Piece number in general sequences
        Arr(0 To 5) As Byte ' must exists only for correct byte align.
        llStartPos As LONGLONG ' Lower  dword of int64 Time offset of start trim position
        llStopPos As LONGLONG  ' Lower  dword of int64 Time offset of stop  trim position
    End Type 'tagTSTrimInfo
    '---------------------------------------------------------------------------------
    'structure decribing trim list which consist of some intervals
    Public Type TrimInfoList
        nListSize As Long 'number of intervals in trimlist
        trim_list As Long 'pointer to array of tagTSTrimInfo
    End Type 'TrimInfoList
    '---------------------------------------------------------------------------------

