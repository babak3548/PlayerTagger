unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, AVITRIMMERCOMLib_TLB, SMM_Defs, StdCtrls, ComCtrls, ExtCtrls;

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

  //TClipInfo = packed record
  TClipInfo = record
   dwClipNum : DWORD;
   rtStart : Int64;
   rtEnd : Int64;
   bMute : BOOL;
   wsfName : Array[0..1023] of WideChar;
   dwReserv : Array[0..19] of DWORD;
  end;
  PClipInfo = ^TClipInfo;

  TClips = Array[0..1024] of TClipInfo;
  PClips = ^TClips;

  //TTrackInfo = packed record
  TTrackInfo = record
   nVideoStream : integer;
   nAudioStream : integer;
   szMPEG2IdxFileName : Array [0..1023] of WideChar;
   nClips : integer;
   //pClips : ^TClipInfo;
   //pClips : PClipInfo;
   //pClips : Array[0..1024] of TClipInfo;
   pClips: PClips;
   nOutType : integer;
   nTrimmAccurType : integer;
   ulFlags : DWORD;
   dwASMode : integer;
   llASValue : Int64;
   nTrackPos : UINT;
   dwReserv : Array[0..19] of DWORD;
  end;
  PTrackInfo = ^TTrackInfo;

  TForm1 = class(TForm)
    btnJoin: TButton;
    ListView1: TListView;
    ProgressBar1: TProgressBar;
    Label1: TLabel;
    btnAdd: TButton;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    Timer1: TTimer;
    Label2: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure btnJoinClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
    m_TrimerObj : ITrimmerObjControl;
    m_IModuleConfig : AVITRIMMERCOMLib_TLB.IModuleConfig;
    m_TrimerObjCB : TTrimmerObjCallBack;
  public
    { Public declarations }
    function InitEngine : HResult;
    function JoinStart(outFile : string; outType : SMM_OutputTypes) : HResult;
    function ExtensionOfFile(srcFile: string) : string;
    function CheckSupportedFileTypes(filetype: SMM_OutputTypes) : Boolean;
    
    procedure AppendList(f: string);
    procedure AddClipToTrack(clip: PClipInfo; infile: string);
  end;

var
  Form1: TForm1;
  MPEGProfile: WideString;
  FileOutType: SMM_OutputTypes;

implementation

{$R *.dfm}

procedure TTrimmerObjCallBack.OnStart;
begin
  // Occurs on start
  GUI.Label1.Caption := 'Started';
  //ShowMessage('OnStart');
end;

procedure TTrimmerObjCallBack.OnStop;
begin
  // Occurs on stop
  GUI.Label1.Caption := 'Stopped';
  StopGUI;
end;

procedure TTrimmerObjCallBack.OnPause;
begin
  // Occurs on pause
  GUI.Label1.Caption := 'Paused';
end;

procedure TTrimmerObjCallBack.OnError(hr: Integer; const Val: WideString);
begin
  // Occurs on error
  GUI.Label1.Caption := 'Error (' + Val + ')';
  StopGUI;
end;

procedure TTrimmerObjCallBack.StopGUI;
begin
  GUI.Timer1.Enabled := False;
  GUI.ProgressBar1.Position := 0;
end;

function TForm1.ExtensionOfFile(srcFile: string) : string;
var
  str, extTemp: string;
  len : Integer;
  n : Integer;
begin
  str := srcFile;
  len := Length(str);
  n := len;
  while str[n] <> '.' do
  begin
    str[n] := UpCase(str[n]);
    n := n - 1;
  end;
  extTemp := Copy(str,n+1,len-n);
  result := extTemp;
end;

function TForm1.CheckSupportedFileTypes(filetype: SMM_OutputTypes) : Boolean;
begin
  if ( (filetype > SMM_File_Type_NO) and  (filetype <= SMM_File_Type_MP4) )
  then
    result := True
  else
    result := False;
end;

procedure TForm1.AddClipToTrack(clip: PClipInfo; infile: string);
var
  trackfile : WideString;
begin
  trackfile := infile;

  clip.dwClipNum := 0;
  clip.rtStart := 0;
  clip.rtEnd := 0;
  clip.bMute := FALSE;

  // !note! there is workaround about skiping first bytes in wsfName
  FillChar(clip.wsfName, High(clip.wsfName), #0);
  Move(trackfile[1], clip.wsfName[0], Length(trackfile) * 2);
end;

function TForm1.JoinStart(outFile : string; outType : SMM_OutputTypes) : HResult;
var
  hr: HResult;
  guid: TGUID;
  vp: OleVariant;
  v: OleVariant;
  outF: WideString;
  i : integer;
  bRun : Boolean;
  li : TListItem;
  track : TTrackInfo;
begin

  bRun := true;

  // setting task type
  guid := SMAT_TaskType;
  vp := SMM_Task_Type_Joining;
  hr := m_IModuleConfig.SetValue( guid, vp );

  if (Succeeded(hr)) then
  begin

    outF := outFile;

    // setting output file
    guid := SMAT_OutputFile;
    vp := outF;
    hr := m_IModuleConfig.SetValue( guid, vp );
    // set out type
    guid := SMAT_OutputType;
    vp := Integer(outType);
    hr := m_IModuleConfig.SetValue(guid, vp);

    if (Succeeded(hr)) then begin

      // join task - one track with multiple clips
      track.nClips := ListView1.Items.Count;
      GetMem(track.pClips, track.nClips * SizeOf(TClipInfo));

      // track values doesn't matter
      // the valueable - the very first clip and it's content/params

      track.nOutType := Integer(outType);
      // -1 means all available streams would be used
      track.nVideoStream := -1;
      track.nAudioStream := -1;


      track.nTrimmAccurType := -1;
      track.ulFlags := 0;
      track.dwASMode := 0;
      track.llASValue := 0;
      track.nTrackPos := 0;

      for i := 0 to track.nClips - 1 do begin
        li := ListView1.Items.Item[i];
        AddClipToTrack(@track.pClips[i], li.Caption);
      end;

      guid := SMAT_TrackInfo;

      TVarData(vp).VType := varByRef;
      TVarData(vp).VPointer := @track;

      hr := m_IModuleConfig.SetValue( guid, vp );

      if (Succeeded(hr)) then begin
        v := 0;
        hr := m_IModuleConfig.CommitChanges( v );
        if (Succeeded(hr)) then begin
          guid := SMAT_ValidateFiles;
          hr := m_IModuleConfig.GetValue( guid, v );
          if (Succeeded(hr)) then begin
            hr := v;
            if (Succeeded(hr)) then begin
              if (hr = S_FALSE) then begin
                if (MessageDlg('Some chosen tracks have different parameters!#10#13There may be some problems during output file playback.#10#13   Would you like to continue?', mtWarning, [mbYes, mbNo], 0) <> idOk) then
                bRun := false;
              end;
            end else begin
              bRun := false;
              ShowMessage('Error: validating files');
            end;
          end else bRun := false;
          if (bRun) then begin
            m_TrimerObj.Start();
            Timer1.Enabled := True;
          end;
        end;
      end;
    end;
  end;

  result := hr;

end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  v : OleVariant;
  guid : TGUID;
begin
  guid := SMAT_Progress;
  m_IModuleConfig.GetValue(guid, v);
  ProgressBar1.Position := v;
end;

function TForm1.InitEngine : HResult;
var
  vp : OleVariant;
  guid : TGUID;
  hr : HResult;
  rpath: WideString;
begin

    // Codecs Sets
  MPEGProfile := 'dmx<type:MPEG2>_EL__mux<type:MPEG2>_EL__enc<type:AVC>_EL__enc<type:MPEG2>_EL__dec<type:AVC>_EL__dec<type:MPEG2>_EL__ixr<type:MPEG2>_EL__dmx<type:MP4>_SM__mux<type:MP4>_SM';
  
  // Creating main objects
  m_TrimerObj := AVITRIMMERCOMLib_TLB.CoTrimmerObjControl.Create();

  // Setting callbacks
  m_TrimerObjCB := TTrimmerObjCallBack.Create();
  m_TrimerObjCB.GUI := Self;
  m_TrimerObj.SetCallback(m_TrimerObjCB);

  // IModuleConfig
  m_TrimerObj.QueryInterface(IID_IModuleConfig, m_IModuleConfig);

  if (m_IModuleConfig <> nil) then begin
    guid := SMAT_ActionKey;
    vp := g_ActionKey_Join;
    hr := m_IModuleConfig.SetValue( guid, vp );

    guid := SMAT_CodecsSet;
    vp := MPEGProfile;
    hr := m_IModuleConfig.SetValue( guid, vp );

    if (Succeeded(hr)) then begin
      guid := CLSID_VideoEditingSDK;
      rpath := 'CLSID\' + SysUtils.GUIDToString(guid) + '\Components';

      guid := SMAT_SilentPath;
      vp := rpath;
      hr := m_IModuleConfig.SetValue( guid, vp );
    end;
  end else hr := E_FAIL;

  result := hr;
end;

procedure TForm1.AppendList(f: string);
var
  hr: HResult;
  vp: OleVariant;
  ws: WideString;
  guid: TGUID;
  li: TListItem;
  OutTypeVal: SMM_OutputTypes;
begin

  ws := f;

  guid := SMAT_InputFile;
  vp := ws;
  m_IModuleConfig.SetValue( guid, vp );

  guid := SMAT_GetFileType;
  vp := 0;

  hr := m_IModuleConfig.GetValue( guid, vp );

  if (Succeeded(hr)) then begin

    OutTypeVal := vp;
    if (CheckSupportedFileTypes(OutTypeVal)) then
    begin
      if (FileOutType = SMM_File_Type_NO) then
        FileOutType := OutTypeVal;
      li := ListView1.Items.Add();
      li.Caption := f;
      li.SubItems.Add(XTLDescr_TrackOutType[Integer(OutTypeVal)]);
    end;
  end;
end;

procedure TForm1.btnAddClick(Sender: TObject);
begin
  OpenDialog1.Filter := 'Supported files (*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv)'+
  '|*.vob;*.mpg;*.mpeg;*.m2v;*.mp4;*.m4v;*.mkv;*.m2ts;*.h264;*.mov;*.mkv;*.mov*.mp4;*.mp3;*.avi;*.asf;*.wav;*.wma;*.wmv|All files (*.*)|*.*';
  if (OpenDialog1.Execute()) then
    AppendList(OpenDialog1.FileName);
end;

procedure TForm1.btnJoinClick(Sender: TObject);
var
  hr : HResult;
  extTemp : string;
begin
  extTemp := ExtensionOfFile(ListView1.Items.Item[0].Caption);
  SaveDialog1.DefaultExt := extTemp;
  SaveDialog1.Filter := extTemp+' files ( *. ' + extTemp + ' )|*.' + extTemp + '|All files (*.*)|*.*';
  if (SaveDialog1.Execute()) then begin
    hr := JoinStart(SaveDialog1.FileName, FileOutType);
    if (Failed(hr)) then ShowMessage('Error: Join failed');
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  hr : HResult;
begin
  hr := InitEngine();
  if (Failed(hr))then
    ShowMessage('Error: initializing Edit Engine');
end;

end.
