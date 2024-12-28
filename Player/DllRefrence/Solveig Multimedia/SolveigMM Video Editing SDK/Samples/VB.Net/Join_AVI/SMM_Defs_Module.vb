' SolveigMM Definition file for Visual Basic applications
' The file must be included in project using AVITrimmerComObject
Imports System.Runtime.InteropServices
Module SMM_Defs ' Definitions required for using AVITRIMMERCOMOBJECT

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

    Public XTLDescr_TrackOutType() As String = {"no type", "avi", "asf", "mpa", "mpg_ps", "mpg_ts", "mpg_ves", "mpg1_sys", "mpg1_ves", "wav", "avc_ves", "matroska", "mp4", "raw"}

    Enum SMM_TaskType
        SMM_Task_Type_Trimming = &H0
        SMM_Task_Type_Joining = &H1
        SMM_Task_Type_Indexation = &H5
    End Enum

    <StructLayout(LayoutKind.Explicit, Size:=2176, CharSet:=CharSet.Unicode)> _
    Public Structure SMM_TRACK_INFO
        <MarshalAs(UnmanagedType.I4), FieldOffset(0)> _
            Public nVideoStream As Integer
        <MarshalAs(UnmanagedType.I4), FieldOffset(4)> _
            Public nAudioStream As Integer
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=1024), FieldOffset(8)> _
            Public szMPEG2IdxFileName As String
        <MarshalAs(UnmanagedType.I4), FieldOffset(2056)> _
            Public nClips As Integer
        <FieldOffset(2060)> _
            Public pClips As IntPtr
        <MarshalAs(UnmanagedType.I4), FieldOffset(2064)> _
            Public nOutType As Integer
        <MarshalAs(UnmanagedType.I4), FieldOffset(2068)> _
            Public nTrimmAccurType As Integer
        <MarshalAs(UnmanagedType.U4), FieldOffset(2072)> _
            Public ulFlags As UInt32
        <MarshalAs(UnmanagedType.I4), FieldOffset(2076)> _
            Public dwASMode As Integer
        <MarshalAs(UnmanagedType.I8), FieldOffset(2080)> _
            Public llASValue As Int64
        <MarshalAs(UnmanagedType.U4), FieldOffset(2088)> _
            Public nTrackPos As UInt32
        <MarshalAs(UnmanagedType.ByValArray, ArraySubType:=UnmanagedType.U4, SizeConst:=20), FieldOffset(2092)> _
            Public dwReserv() As UInt32
    End Structure

    <StructLayout(LayoutKind.Explicit, Size:=2160, CharSet:=CharSet.Unicode)> _
    Structure SMM_CLIP_INFO
        <MarshalAs(UnmanagedType.U4), FieldOffset(0)> _
            Public dwClipNum As UInt32
        <MarshalAs(UnmanagedType.I8), FieldOffset(8)> _
            Public rtStart As Int64
        <MarshalAs(UnmanagedType.I8), FieldOffset(16)> _
            Public rtStop As Int64
        <MarshalAs(UnmanagedType.I4), FieldOffset(24)> _
            Public bMute As Int32
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=1024), FieldOffset(28)> _
            Public wsfName As String
        <MarshalAs(UnmanagedType.ByValArray, ArraySubType:=UnmanagedType.U4, SizeConst:=20), FieldOffset(2076)> _
            Public dwReserv() As UInt32
    End Structure
End Module 'SMM_Defs
