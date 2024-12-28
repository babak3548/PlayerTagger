object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'SMM Trim Delphi'
  ClientHeight = 204
  ClientWidth = 456
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
    Left = 8
    Top = 11
    Width = 43
    Height = 13
    Caption = 'Input file'
  end
  object Label2: TLabel
    Left = 7
    Top = 38
    Width = 51
    Height = 13
    Caption = 'Output file'
  end
  object Label3: TLabel
    Left = 8
    Top = 75
    Width = 47
    Height = 13
    Caption = 'Start, sec'
  end
  object Label4: TLabel
    Left = 7
    Top = 102
    Width = 45
    Height = 13
    Caption = 'Stop, sec'
  end
  object Label5: TLabel
    Left = 8
    Top = 166
    Width = 433
    Height = 13
    Caption = 
      'Supported formats: ASF, AVI, AVCHD, MKV, MP4, MOV, MP3, MPEG1, M' +
      'PEG2, WAV, WMA'
  end
  object Edit1: TEdit
    Left = 64
    Top = 8
    Width = 344
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 64
    Top = 35
    Width = 344
    Height = 21
    TabOrder = 1
  end
  object Button1: TButton
    Left = 414
    Top = 8
    Width = 34
    Height = 21
    Caption = '...'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 414
    Top = 35
    Width = 34
    Height = 21
    Caption = '...'
    TabOrder = 3
    OnClick = Button2Click
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 185
    Width = 456
    Height = 19
    Panels = <>
    SimplePanel = True
    SimpleText = 'Status:'
    ExplicitTop = 162
  end
  object Button3: TButton
    Left = 373
    Top = 105
    Width = 75
    Height = 25
    Caption = 'Trim'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = Button3Click
  end
  object Edit3: TEdit
    Left = 64
    Top = 72
    Width = 76
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object Edit4: TEdit
    Left = 64
    Top = 99
    Width = 76
    Height = 21
    TabOrder = 7
    Text = '0'
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 136
    Width = 440
    Height = 16
    TabOrder = 8
  end
  object CheckBox1: TCheckBox
    Left = 351
    Top = 74
    Width = 97
    Height = 17
    Alignment = taLeftJustify
    Caption = 'Frame Accuracy'
    TabOrder = 9
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'avi'
    Left = 272
    Top = 64
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'avi'
    Filter = '*.avi|*.avi'
    Left = 240
    Top = 64
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 160
    Top = 72
  end
  object XPManifest1: TXPManifest
    Left = 240
    Top = 96
  end
end
