unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, AVITRIMMERCOMLib_TLB, SMM_Defs, ExtCtrls, XPMan;


type
  TForm1 = class;

  TTrimmerObjCallBack = class(TInterfacedObject, ITrimmerObjControlCB)
  private
    procedure StopGUI;
    public
      GUI : TForm1;
    procedure OnStart;safecall;
    procedure OnStop;safecall;
    procedure OnPause;safecall;
    procedure OnError(hr: Integer; const Val: WideString); safecall;
  end;

  TRange = record
    Piece : word;
    dStart : Int64;
    dStop : Int64;
  end;

  TTrimInfoList = record
    Count : integer;
    range : ^TRange;
  end;

  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Button1: TButton;
    Button2: TButton;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    StatusBar1: TStatusBar;
    Button3: TButton;
    Edit3: TEdit;
    Edit4: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Timer1: TTimer;
    ProgressBar1: TProgressBar;
    XPManifest1: TXPManifest;
    CheckBox1: TCheckBox;
    Label5: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure IndexMPEG2File( FileName: string );
    function GetOutput : Boolean;

  private
    { Private declarations }
    m_TrimerObj : ITrimmerObjControl;
    m_IModuleConfig : AVITRIMMERCOMLib_TLB.IModuleConfig;
    m_TrimerObjCB : TTrimmerObjCallBack;
  public
    { Public declarations }
    m_bUseIndex : Boolean;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TTrimmerObjCallBack.OnStart;
begin
  // Occurs on start
  GUI.StatusBar1.SimpleText := 'Status: Started';
end;

procedure TTrimmerObjCallBack.OnStop;
begin
  // Occurs on stop
  GUI.StatusBar1.SimpleText := 'Status: Stopped';
  StopGUI;
end;

procedure TTrimmerObjCallBack.OnPause;
begin
  // Occurs on pause
  GUI.StatusBar1.SimpleText := 'Status: Paused';
end;

procedure TTrimmerObjCallBack.OnError(hr: Integer; const Val: WideString);
begin
  // Occurs on error
  GUI.StatusBar1.SimpleText := 'Status: Error (' + Val + ')';
  StopGUI;
end;

procedure TTrimmerObjCallBack.StopGUI;
begin
  GUI.Timer1.Enabled := False;
  GUI.Button3.Caption := 'Trim';
  GUI.Tag := 0;
  GUI.ProgressBar1.Position := 0;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  guid : TGUID;
  hr : HRESULT;
  v: OleVariant;
  res: Integer;
  bRes: boolean;
begin
  Edit2.Text := '';
  OpenDialog1.Filter := 'Supported files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)'+
  '|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv|All files (*.*)|*.*';
  bRes := OpenDialog1.Execute;
  if Not bRes then
    exit;
  Edit1.Text := OpenDialog1.FileName;
  guid := SMAT_InputFile;
  v := Edit1.Text;
  m_IModuleConfig.SetValue(guid, v);
  guid := SMAT_GetFileType;
  v := 0;
  hr := m_IModuleConfig.GetValue( guid, v );
      if ((v >= SMM_File_Type_MPEG2_PS) and (v <= SMM_File_Type_MPEG1_VES)) or( v = SMM_File_Type_MPEG4_AVC ) then
      begin
        m_bUseIndex := True;
        if FileExists( Edit1.Text + '.mlmix') then
        begin
          res := MessageDlg('Index file found! Would you like to reindex the file?', mtInformation, mbYesNo, 0 );
        end
           else
        begin
          res := MessageDlg('Index file not found! Would you like to index it?', mtInformation, mbOKCancel, 0 );
        end;
        if (res = mrOK) or (res = mrYes) then
          IndexMPEG2File(Edit1.Text);
        if res = mrCancel then
          m_bUseIndex := False;
      end;
      if( (v = SMM_File_Type_AVI) Or (v = SMM_File_Type_MPA) Or (v = SMM_File_Type_WAV) )  then
      begin
        CheckBox1.Checked := False;
        CheckBox1.Enabled := False;
      end
      else
      begin
        CheckBox1.Checked := True;
        CheckBox1.Enabled := True;
      end;
end;

function TForm1.GetOutput : Boolean;
var
  str, extTemp, Filter : string;
  len : Integer;
  n : Integer;
begin
  str := Edit1.Text;
  len := Length(str);
  n := len;
  while str[n] <> '.' do
  begin
    str[n] := UpCase(str[n]);
    n := n - 1;
  end;
  extTemp := Copy(str,n+1,len-n);

  Filter := extTemp+' files ( *. ' + extTemp + ' )|*.' + extTemp + '|All files (*.*)|*.*';

  SaveDialog1.DefaultExt := extTemp;
  SaveDialog1.Filter := Filter;
  SaveDialog1.FileName := 'Default';
  if SaveDialog1.Execute then
  begin
    Edit2.Text := SaveDialog1.FileName;
    GetOutput := True;
  end
  else
    GetOutput := False;
end;
procedure TForm1.Button2Click(Sender: TObject);
begin
  GetOutput();
end;

procedure TForm1.Button3Click(Sender: TObject);
  var
    v : OleVariant;
    guid : TGUID;
    hr : HRESULT;
    trimlist : TTrimInfoList;
begin
    if Button3.Caption = 'Trim' then
      begin
        Self.Tag := 1;
      end
    else
      begin
        Self.Tag := 0;
      end;

    if Self.Tag = 1 then
    begin
      ProgressBar1.Position := 0;

       // Output file
      if Edit2.Text = '' then
        if Not GetOutput() then
          Exit;
      if Edit3.Text = Edit4.Text then
      begin
        ShowMessage('Fragment start and stop time are equal.');
        Exit;
      end;
      Button3.Caption := 'Stop';

     // Input file
      v := Edit1.Text;
      guid := SMAT_InputFile;
      hr := m_IModuleConfig.SetValue(guid, v);
      if (hr <> 0) then Exit;

      // Output file
      v := Edit2.Text;
      guid := SMAT_OutputFile;
      hr := m_IModuleConfig.SetValue(guid, v);
      if (hr <> 0) then Exit;

      // Fragments list
      trimlist.Count := 1;
      New(trimlist.range);
      trimlist.range.dStart := StrToInt64(Edit3.Text) * 10000000;
      trimlist.range.dStop := StrToInt64(Edit4.Text) * 10000000;
      trimlist.range.Piece := 0;

      TVarData(v).VType := varByRef;
      TVarData(v).VPointer := @trimlist;

      guid := SMAT_TrimList;
      hr := m_IModuleConfig.SetValue(guid, v);
      if (hr <> 0) then Exit;

      // Output video type
      guid := SMAT_GetFileType;
      hr := m_IModuleConfig.GetValue( guid, v );

      guid := SMAT_OutputType;
      hr := m_IModuleConfig.SetValue(guid, v);
      if (hr <> 0) then Exit;

      if m_bUseIndex then
      begin
        guid := SMAT_MPEG2IndexFileName;
        v := Edit1.Text + '.mlmix';
        m_IModuleConfig.SetValue(guid, v);
      end;

      guid := SMAT_TrimAccuracy;
			v := Integer(CheckBox1.Checked);
			m_IModuleConfig.SetValue( guid, v );

      v := 0;
      m_IModuleConfig.CommitChanges(v);
      m_TrimerObj.Start;

      Timer1.Enabled := True;
    end
    else if Self.Tag = 2 then         
    begin
      m_TrimerObj.Stop;
      m_TrimerObjCB.StopGUI;
    end
    else
    begin
          Button3.Caption := 'Trim';
          guid := SMAT_StartIndexation;
          v := False;
          m_IModuleConfig.SetValue(guid, v);
    end;
end;

procedure TForm1.FormCreate(Sender: TObject);
  var
    vp : OleVariant;
    guid  : TGUID;
    hr : HRESULT;
    rpath: WideString;
begin
  m_TrimerObj := AVITRIMMERCOMLib_TLB.CoTrimmerObjControl.Create();
  m_TrimerObjCB := TTrimmerObjCallBack.Create();
  m_TrimerObj.QueryInterface(IID_IModuleConfig, m_IModuleConfig) ;
  if (m_IModuleConfig = nil) then
    begin
      ShowMessage('Error: can''t query for IModuleConfig. Exiting...');
      Application.Terminate;
    end;

  // Setting callbacks
  m_TrimerObjCB.GUI := Self;
  vp := m_TrimerObjCB as ITrimmerObjControlCB;

  guid := SMAT_Callback;
  hr := m_IModuleConfig.SetValue(guid, vp);
  vp:=0;

  // Set mpeg2 codec profile.
  guid := SMAT_CodecsSet;
  vp := 'dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM';
  hr := m_IModuleConfig.SetValue( guid, vp );
  vp := 0;

  //Set mpeg2 codecs silent path
  guid := CLSID_VideoEditingSDK;
  rpath := 'CLSID\' + GUIDToString(guid) + '\Components';

  guid := SMAT_SilentPath;
  vp := rpath;
  hr := m_IModuleConfig.SetValue( guid, vp );

	vp := g_ActionKey_Trim;
  guid := SMAT_ActionKey;
	m_IModuleConfig.SetValue( guid, vp );

end;

procedure TForm1.IndexMPEG2File( FileName: string );
  var
    v : OleVariant;
    guid : TGUID;
    indexName: WideString;
    hr : HRESULT;
begin
  //Input file
  indexName := System.StringToOleStr( FileName );
  guid := SMAT_InputFile;
  v := indexName;
  m_IModuleConfig.SetValue( guid, v );

  //Index file
  guid := SMAT_OutIndexFile;
  indexName := indexName + StringToOleStr('.mlmix');
  v := indexName;
  hr := m_IModuleConfig.SetValue( guid, v );

  //Start indexation
  guid := SMAT_StartIndexation;
  v := TRUE;
  hr := m_IModuleConfig.SetValue( guid, v );

  Self.StatusBar1.SimpleText := 'Status: Indexing';
  Timer1.Enabled := True;
  Button3.Caption := 'Cancel';
  Self.Tag := 3;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
  var
    v : OleVariant;
    guid : TGUID;
begin
  // Query for progress

  guid := SMAT_Progress;
  m_IModuleConfig.GetValue(guid, v);
  ProgressBar1.Position := v;
  if Self.Tag = 3 then
    if v = 100 then
      m_TrimerObjCB.OnStop();
end;

end.
