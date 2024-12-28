' SolveigMM Definition file for Visual Basic applications
' The file must be included in project using AVITrimmerComObject
Imports System.Runtime.InteropServices
Public Class SMM_Defs ' Definitions required for using AVITRIMMERCOMOBJECT
    
'Parameter GUIDs are available in the full SDK version

    Enum SMM_OutputTypes
        SMM_File_Type_NO = 0
        SMM_File_Type_AVI = 1          ' audio video interleaved format
        SMM_File_Type_ASF = 2          ' advanced streaming format
        SMM_File_Type_MPA = 3          ' mpeg audio
        SMM_File_Type_MPEG2_PS = 4     ' MPEG-2 Program Stream
        SMM_File_Type_MPEG2_TS = 5     ' MPEG-2 Transpot Stream
        SMM_File_Type_MPEG2_VES = 6    ' MPEG-2 Video Elementary Stream
        SMM_File_Type_MPEG1_SYS = 7    ' MPEG-1 System stream. Unsupported
        SMM_File_Type_MPEG1_VES = 8    ' MPEG-1 Video only elementary stream.
        SMM_File_Type_WAV = 9          ' WAVE audio steam
        SMM_File_Type_MPEG4_AVC = 10   ' MPEG-4 AVC Video only elementary stream.
        SMM_File_Type_MKV = 11         ' Matroska video
        SMM_File_Type_MP4 = 12         ' MPEG-4 Part 14 - MP4 File format
        SMM_File_Type_RAW = 13
    End Enum

    Enum SMM_TaskType
        SMM_Task_Type_Trimming = &H0
        SMM_Task_Type_Joining = &H1
        SMM_Task_Type_Indexation = &H5
    End Enum

    ' Struct
    <StructLayout(LayoutKind.Sequential)> Structure __TSTrimInfo
        Public nPieceNum As Int16 ' Piece number in general sequences
        Public llStartPos As Int64 ' Time offset of start trim position
        Public llStopPos As Int64 ' Time offset of stop trim position
    End Structure '__TSTrimInfo

    <StructLayout(LayoutKind.Sequential)> Structure TrimInfoList
        Public nListSize As Integer
        '<MarshalAs(UnmanagedType.LPStruct)> Public trim_list '() As __TSTrimInfo
        Public trim_list As IntPtr
    End Structure 'TrimInfoList

    <StructLayout(LayoutKind.Explicit)> Structure SMM_ASF_MARKER
        <FieldOffset(0)> Public name As String
        <FieldOffset(5120)> Public time_pos As Int64
        <FieldOffset(5184)> Public num_pos As Integer
    End Structure 'TrimInfoList

    <StructLayout(LayoutKind.Sequential)> Structure CInterval_info
        Public llstart As Int64
        Public llend As Int64
        Public bselect As Boolean
        Public N As Int32
    End Structure

End Class 'SMM_Defs
