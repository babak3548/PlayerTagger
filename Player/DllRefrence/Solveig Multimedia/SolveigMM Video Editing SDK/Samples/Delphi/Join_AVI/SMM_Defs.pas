unit SMM_Defs;

interface
{$MESSAGE ERROR 'Evalution version of the SDK misses some clue headers and can not be compilled.' }
{$MESSAGE ERROR '	  To get full version of the SolveigMM Video Editing SDK please email to info@solveigmm.com' }
const
  {enum SMM_TaskType}
    SMM_Task_Type_Trimming: integer = 0;
    SMM_Task_Type_Joining: integer = 1;
    SMM_Task_Type_Join_Gap_Fill: integer = 2;
    SMM_Task_Type_Muxing: integer = 3;
    SMM_Task_Type_Demuxing: integer = 4;

  {enum SMM_OutputTypes}
    SMM_File_Type_NO: integer = 0;
    SMM_File_Type_AVI: integer = 1;
    SMM_File_Type_ASF: integer = 2;
    SMM_File_Type_MPA: integer = 3;
    SMM_File_Type_MPEG2_PS: integer = 4;  // MPEG-2 Program Stream
    SMM_File_Type_MPEG2_TS: integer = 5;  // MPEG-2 Transport Stream
    SMM_File_Type_MPEG2_VES: integer = 6; // MPEG-2 Video Elementary Stream
    SMM_File_Type_MPEG1_SYS: integer = 7; // MPEG-1 System stream. Unsupported
    SMM_File_Type_MPEG1_VES: integer = 8; // MPEG-1 Video only elementary stream.

    XTLDescr_TrackOutType: Array[0..8] of WideString = ('no type', 'avi', 'asf', 'mpa', 'mpg_ps', 'mpg_ts', 'mpg_ves', 'mpg1_sys', 'mpg1_ves');

implementation

end.
