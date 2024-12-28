object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'SMM Join Delphi'
  ClientHeight = 265
  ClientWidth = 534
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 487
    Top = 216
    Width = 18
    Height = 13
    Caption = 'Idle'
  end
  object Label2: TLabel
    Left = 8
    Top = 248
    Width = 433
    Height = 13
    Caption = 
      'Supported formats: ASF, AVI, AVCHD, MKV, MP4, MOV, MP3, MPEG1, M' +
      'PEG2, WAV, WMA'
  end
  object btnJoin: TButton
    Left = 112
    Top = 211
    Width = 75
    Height = 25
    Caption = 'Join'
    TabOrder = 0
    OnClick = btnJoinClick
  end
  object ListView1: TListView
    Left = 8
    Top = 8
    Width = 518
    Height = 190
    Columns = <
      item
        AutoSize = True
        Caption = 'file'
      end
      item
        Caption = 'type'
      end>
    TabOrder = 1
    ViewStyle = vsReport
  end
  object ProgressBar1: TProgressBar
    Left = 209
    Top = 211
    Width = 272
    Height = 25
    TabOrder = 2
  end
  object btnAdd: TButton
    Left = 8
    Top = 211
    Width = 75
    Height = 25
    Caption = 'Add File'
    TabOrder = 3
    OnClick = btnAddClick
  end
  object SaveDialog1: TSaveDialog
    FileName = 'Joined'
    FilterIndex = 0
    Left = 104
    Top = 104
  end
  object OpenDialog1: TOpenDialog
    FilterIndex = 2
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Title = 'Select input media file'
    Left = 56
    Top = 104
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 152
    Top = 112
  end
end
