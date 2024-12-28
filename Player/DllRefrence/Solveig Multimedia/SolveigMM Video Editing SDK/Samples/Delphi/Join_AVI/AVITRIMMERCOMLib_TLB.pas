unit AVITRIMMERCOMLib_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 5081 $
// File generated on 27.04.2009 0:04:19 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Solveig Multimedia\SolveigMM Video Editing SDK\Samples\Delphi\engine\SMM_EditEngine.dll (1)
// LIBID: {958BB6C7-14FB-49EF-AFAE-678155680C6A}
// LCID: 0
// Helpfile: 
// HelpString: AVITrimmerCOM 1.0 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Hint: Symbol 'type' renamed to 'type_'
//   Error creating palette bitmap of (TTrimmerObjControl) : Server C:\Program Files\Solveig Multimedia\SolveigMM Video Editing SDK\Samples\Delphi\engine\SMM_EditEngine.dll contains no icons
// ************************************************************************ //
// *************************************************************************//
// NOTE:                                                                      
// Items guarded by $IFDEF_LIVE_SERVER_AT_DESIGN_TIME are used by properties  
// which return objects that may need to be explicitly created via a function 
// call prior to any access via the property. These items have been disabled  
// in order to prevent accidental use from within the object inspector. You   
// may enable them by defining LIVE_SERVER_AT_DESIGN_TIME or by selectively   
// removing them from the $IFDEF blocks. However, such items must still be    
// programmatically created via a method of the appropriate CoClass before    
// they can be used.                                                          
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, OleServer, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  AVITRIMMERCOMLibMajorVersion = 1;
  AVITRIMMERCOMLibMinorVersion = 0;

  LIBID_AVITRIMMERCOMLib: TGUID = '{958BB6C7-14FB-49EF-AFAE-678155680C6A}';

  DIID__IXTransformEvents: TGUID = '{DC2117FE-3CCE-476A-992A-CAF7DED33764}';
  IID_ITrimmerObjControl: TGUID = '{9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}';
  IID_IXTransform: TGUID = '{34FCD759-A1D9-4593-9390-6275BC639B42}';
  IID_ITrimmerObjControlCB: TGUID = '{33968711-8887-46D4-A71B-9B1B061EEDCA}';
  IID_IPersist: TGUID = '{0000010C-0000-0000-C000-000000000046}';
  IID_IPersistStream: TGUID = '{00000109-0000-0000-C000-000000000046}';
  IID_IModuleConfig: TGUID = '{486F726E-4D43-49B9-8A0C-C22A2B0524E8}';
  IID_IModuleConfigForVB: TGUID = '{D211F479-B5F2-469F-9EB9-F0CD7EB202D9}';
  IID_ISequentialStream: TGUID = '{0C733A30-2A1C-11CE-ADE5-00AA0044773D}';
  IID_IStream: TGUID = '{0000000C-0000-0000-C000-000000000046}';
  IID_IParamConfig: TGUID = '{486F726E-5043-49B9-8A0C-C22A2B0524E8}';
  IID_IModuleCallback: TGUID = '{486F726E-4D45-49B9-8A0C-C22A2B0524E8}';
  CLASS_TrimmerObjControl: TGUID = '{B61C3708-CAA8-48CA-9D9C-682D0A5A3852}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  _IXTransformEvents = dispinterface;
  ITrimmerObjControl = interface;
  ITrimmerObjControlDisp = dispinterface;
  IXTransform = interface;
  IXTransformDisp = dispinterface;
  ITrimmerObjControlCB = interface;
  ITrimmerObjControlCBDisp = dispinterface;
  IPersist = interface;
  IPersistStream = interface;
  IModuleConfig = interface;
  IModuleConfigForVB = interface;
  ISequentialStream = interface;
  IStream = interface;
  IParamConfig = interface;
  IModuleCallback = interface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  TrimmerObjControl = ITrimmerObjControl;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  PByte1 = ^Byte; {*}
  PUserType1 = ^TGUID; {*}
  POleVariant1 = ^OleVariant; {*}
  PInteger1 = ^Integer; {*}

  _LARGE_INTEGER = packed record
    QuadPart: Int64;
  end;

  _ULARGE_INTEGER = packed record
    QuadPart: Largeuint;
  end;

  _FILETIME = packed record
    dwLowDateTime: LongWord;
    dwHighDateTime: LongWord;
  end;

  tagSTATSTG = packed record
    pwcsName: PWideChar;
    type_: LongWord;
    cbSize: _ULARGE_INTEGER;
    mtime: _FILETIME;
    ctime: _FILETIME;
    atime: _FILETIME;
    grfMode: LongWord;
    grfLocksSupported: LongWord;
    clsid: TGUID;
    grfStateBits: LongWord;
    reserved: LongWord;
  end;


// *********************************************************************//
// DispIntf:  _IXTransformEvents
// Flags:     (4096) Dispatchable
// GUID:      {DC2117FE-3CCE-476A-992A-CAF7DED33764}
// *********************************************************************//
  _IXTransformEvents = dispinterface
    ['{DC2117FE-3CCE-476A-992A-CAF7DED33764}']
    procedure OnStart; dispid 1;
    procedure OnStop; dispid 2;
    procedure OnComplete; dispid 3;
    procedure OnError(hrError: HResult; const sError: WideString); dispid 4;
  end;

// *********************************************************************//
// Interface: ITrimmerObjControl
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}
// *********************************************************************//
  ITrimmerObjControl = interface(IDispatch)
    ['{9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}']
    function Get_InputFN: WideString; safecall;
    procedure Set_InputFN(const pVal: WideString); safecall;
    function Get_OutputFN: WideString; safecall;
    procedure Set_OutputFN(const pVal: WideString); safecall;
    procedure Start; safecall;
    procedure Stop; safecall;
    function Get_Status: Integer; safecall;
    function Get_StreamLength: Double; safecall;
    function Get_StartPosition: Double; safecall;
    procedure Set_StartPosition(pVal: Double); safecall;
    function Get_StopPosition: Double; safecall;
    procedure Set_StopPosition(pVal: Double); safecall;
    procedure SetCallback(const pITrimmerObjControlCB: ITrimmerObjControlCB); safecall;
    property InputFN: WideString read Get_InputFN write Set_InputFN;
    property OutputFN: WideString read Get_OutputFN write Set_OutputFN;
    property Status: Integer read Get_Status;
    property StreamLength: Double read Get_StreamLength;
    property StartPosition: Double read Get_StartPosition write Set_StartPosition;
    property StopPosition: Double read Get_StopPosition write Set_StopPosition;
  end;

// *********************************************************************//
// DispIntf:  ITrimmerObjControlDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}
// *********************************************************************//
  ITrimmerObjControlDisp = dispinterface
    ['{9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}']
    property InputFN: WideString dispid 1;
    property OutputFN: WideString dispid 2;
    procedure Start; dispid 3;
    procedure Stop; dispid 4;
    property Status: Integer readonly dispid 5;
    property StreamLength: Double readonly dispid 6;
    property StartPosition: Double dispid 7;
    property StopPosition: Double dispid 8;
    procedure SetCallback(const pITrimmerObjControlCB: ITrimmerObjControlCB); dispid 9;
  end;

// *********************************************************************//
// Interface: IXTransform
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {34FCD759-A1D9-4593-9390-6275BC639B42}
// *********************************************************************//
  IXTransform = interface(IDispatch)
    ['{34FCD759-A1D9-4593-9390-6275BC639B42}']
    procedure put_Parameters(var pData: Byte; lBytes: Integer); safecall;
    procedure get_Parameters(out pData: Byte; out plBytes: Integer); safecall;
    procedure get_Progress(out pValue: Smallint; out psState: WideString); safecall;
    procedure get_LastErrorMessage(out psError: WideString); safecall;
    procedure Start; safecall;
    procedure Stop; safecall;
    procedure ShowGraph; safecall;
  end;

// *********************************************************************//
// DispIntf:  IXTransformDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {34FCD759-A1D9-4593-9390-6275BC639B42}
// *********************************************************************//
  IXTransformDisp = dispinterface
    ['{34FCD759-A1D9-4593-9390-6275BC639B42}']
    procedure put_Parameters(var pData: Byte; lBytes: Integer); dispid 1;
    procedure get_Parameters(out pData: Byte; out plBytes: Integer); dispid 2;
    procedure get_Progress(out pValue: Smallint; out psState: WideString); dispid 3;
    procedure get_LastErrorMessage(out psError: WideString); dispid 4;
    procedure Start; dispid 5;
    procedure Stop; dispid 6;
    procedure ShowGraph; dispid 7;
  end;

// *********************************************************************//
// Interface: ITrimmerObjControlCB
// Flags:     (320) Dual OleAutomation
// GUID:      {33968711-8887-46D4-A71B-9B1B061EEDCA}
// *********************************************************************//
  ITrimmerObjControlCB = interface(IUnknown)
    ['{33968711-8887-46D4-A71B-9B1B061EEDCA}']
    procedure OnStart; safecall;
    procedure OnStop; safecall;
    procedure OnPause; safecall;
    procedure OnError(hr: Integer; const Val: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  ITrimmerObjControlCBDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {33968711-8887-46D4-A71B-9B1B061EEDCA}
// *********************************************************************//
  ITrimmerObjControlCBDisp = dispinterface
    ['{33968711-8887-46D4-A71B-9B1B061EEDCA}']
    procedure OnStart; dispid 1;
    procedure OnStop; dispid 2;
    procedure OnPause; dispid 3;
    procedure OnError(hr: Integer; const Val: WideString); dispid 4;
  end;

// *********************************************************************//
// Interface: IPersist
// Flags:     (0)
// GUID:      {0000010C-0000-0000-C000-000000000046}
// *********************************************************************//
  IPersist = interface(IUnknown)
    ['{0000010C-0000-0000-C000-000000000046}']
    function GetClassID(out pClassID: TGUID): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IPersistStream
// Flags:     (0)
// GUID:      {00000109-0000-0000-C000-000000000046}
// *********************************************************************//
  IPersistStream = interface(IPersist)
    ['{00000109-0000-0000-C000-000000000046}']
    function IsDirty: HResult; stdcall;
    function Load(const pstm: IStream): HResult; stdcall;
    function Save(const pstm: IStream; fClearDirty: Integer): HResult; stdcall;
    function GetSizeMax(out pcbSize: _ULARGE_INTEGER): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IModuleConfig
// Flags:     (0)
// GUID:      {486F726E-4D43-49B9-8A0C-C22A2B0524E8}
// *********************************************************************//
  IModuleConfig = interface(IPersistStream)
    ['{486F726E-4D43-49B9-8A0C-C22A2B0524E8}']
    function SetValue(var pParamID: TGUID; var pValue: OleVariant): HResult; stdcall;
    function GetValue(var pParamID: TGUID; out pValue: OleVariant): HResult; stdcall;
    function GetParamConfig(var pParamID: TGUID; out pValue: IParamConfig): HResult; stdcall;
    function IsSupported(var pParamID: TGUID): HResult; stdcall;
    function SetDefState: HResult; stdcall;
    function EnumParams(var pNumParams: Integer; var pParamIDs: TGUID): HResult; stdcall;
    function CommitChanges(out pReason: OleVariant): HResult; stdcall;
    function DeclineChanges: HResult; stdcall;
    function SaveToRegistry(hKeyRoot: LongWord; const pszKeyName: WideString; 
                            bPreferReadable: Integer): HResult; stdcall;
    function LoadFromRegistry(hKeyRoot: LongWord; const pszKeyName: WideString; 
                              bPreferReadable: Integer): HResult; stdcall;
    function RegisterForNotifies(const pModuleCallback: IModuleCallback): HResult; stdcall;
    function UnregisterFromNotifies(const pModuleCallback: IModuleCallback): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IModuleConfigForVB
// Flags:     (0)
// GUID:      {D211F479-B5F2-469F-9EB9-F0CD7EB202D9}
// *********************************************************************//
  IModuleConfigForVB = interface(IUnknown)
    ['{D211F479-B5F2-469F-9EB9-F0CD7EB202D9}']
    function SetValueVB(const pParamID: WideString; var pValue: OleVariant): HResult; stdcall;
    function GetValueVB(const pParamID: WideString; out pValue: OleVariant): HResult; stdcall;
    function GetParamConfigVB(const pParamID: WideString; out pValue: OleVariant): HResult; stdcall;
    function IsSupportedVB(const pParamID: WideString): HResult; stdcall;
    function SetDefStateVB: HResult; stdcall;
    function EnumParamsVB(var pNumParams: Integer; var pParamIDs: TGUID): HResult; stdcall;
    function CommitChangesVB(out pReason: OleVariant): HResult; stdcall;
    function DeclineChangesVB: HResult; stdcall;
    function SaveToRegistryVB(hKeyRoot: LongWord; const pszKeyName: WideString; 
                              bPreferReadable: Integer): HResult; stdcall;
    function LoadFromRegistryVB(hKeyRoot: LongWord; const pszKeyName: WideString; 
                                bPreferReadable: Integer): HResult; stdcall;
    function RegisterForNotifiesVB(const pModuleCallback: IModuleCallback): HResult; stdcall;
    function UnregisterFromNotifiesVB(const pModuleCallback: IModuleCallback): HResult; stdcall;
    function ConvertREFTIMEtoREFERENCETIME(dVal: Double; out pValue: OleVariant): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: ISequentialStream
// Flags:     (0)
// GUID:      {0C733A30-2A1C-11CE-ADE5-00AA0044773D}
// *********************************************************************//
  ISequentialStream = interface(IUnknown)
    ['{0C733A30-2A1C-11CE-ADE5-00AA0044773D}']
    function RemoteRead(out pv: Byte; cb: LongWord; out pcbRead: LongWord): HResult; stdcall;
    function RemoteWrite(var pv: Byte; cb: LongWord; out pcbWritten: LongWord): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IStream
// Flags:     (0)
// GUID:      {0000000C-0000-0000-C000-000000000046}
// *********************************************************************//
  IStream = interface(ISequentialStream)
    ['{0000000C-0000-0000-C000-000000000046}']
    function RemoteSeek(dlibMove: _LARGE_INTEGER; dwOrigin: LongWord; 
                        out plibNewPosition: _ULARGE_INTEGER): HResult; stdcall;
    function SetSize(libNewSize: _ULARGE_INTEGER): HResult; stdcall;
    function RemoteCopyTo(const pstm: IStream; cb: _ULARGE_INTEGER; out pcbRead: _ULARGE_INTEGER; 
                          out pcbWritten: _ULARGE_INTEGER): HResult; stdcall;
    function Commit(grfCommitFlags: LongWord): HResult; stdcall;
    function Revert: HResult; stdcall;
    function LockRegion(libOffset: _ULARGE_INTEGER; cb: _ULARGE_INTEGER; dwLockType: LongWord): HResult; stdcall;
    function UnlockRegion(libOffset: _ULARGE_INTEGER; cb: _ULARGE_INTEGER; dwLockType: LongWord): HResult; stdcall;
    function Stat(out pstatstg: tagSTATSTG; grfStatFlag: LongWord): HResult; stdcall;
    function Clone(out ppstm: IStream): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IParamConfig
// Flags:     (0)
// GUID:      {486F726E-5043-49B9-8A0C-C22A2B0524E8}
// *********************************************************************//
  IParamConfig = interface(IUnknown)
    ['{486F726E-5043-49B9-8A0C-C22A2B0524E8}']
    function SetValue(var pValue: OleVariant; bSetAndCommit: Integer): HResult; stdcall;
    function GetValue(out pValue: OleVariant; bGetCommitted: Integer): HResult; stdcall;
    function SetVisible(bVisible: Integer): HResult; stdcall;
    function GetVisible(var bVisible: Integer): HResult; stdcall;
    function GetParamID(var pParamID: TGUID): HResult; stdcall;
    function GetName(out pName: WideString): HResult; stdcall;
    function GetReadOnly(var bReadOnly: Integer): HResult; stdcall;
    function GetFullInfo(out pValue: OleVariant; out pMeaning: WideString; out pName: WideString; 
                         out bReadOnly: Integer; out pVisible: Integer): HResult; stdcall;
    function GetDefValue(out pValue: OleVariant): HResult; stdcall;
    function GetValidRange(out pMinValue: OleVariant; out pMaxValue: OleVariant; 
                           out pDelta: OleVariant): HResult; stdcall;
    function EnumValidValues(var pNumValidValues: Integer; var pValidValues: OleVariant; 
                             var pValueNames: WideString): HResult; stdcall;
    function ValueToMeaning(var pValue: OleVariant; out pMeaning: WideString): HResult; stdcall;
    function MeaningToValue(const pMeaning: WideString; out pValue: OleVariant): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IModuleCallback
// Flags:     (0)
// GUID:      {486F726E-4D45-49B9-8A0C-C22A2B0524E8}
// *********************************************************************//
  IModuleCallback = interface(IUnknown)
    ['{486F726E-4D45-49B9-8A0C-C22A2B0524E8}']
    function OnModuleNotify(cParams: Integer; var pParamIDs: TGUID): HResult; stdcall;
  end;

// *********************************************************************//
// The Class CoTrimmerObjControl provides a Create and CreateRemote method to          
// create instances of the default interface ITrimmerObjControl exposed by              
// the CoClass TrimmerObjControl. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoTrimmerObjControl = class
    class function Create: ITrimmerObjControl;
    class function CreateRemote(const MachineName: string): ITrimmerObjControl;
  end;

  TTrimmerObjControlOnError = procedure(ASender: TObject; hrError: HResult; const sError: WideString) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TTrimmerObjControl
// Help String      : SolveigMM AVI TrimmerObjControl Class
// Default Interface: ITrimmerObjControl
// Def. Intf. DISP? : No
// Event   Interface: _IXTransformEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TTrimmerObjControlProperties= class;
{$ENDIF}
  TTrimmerObjControl = class(TOleServer)
  private
    FOnStart: TNotifyEvent;
    FOnStop: TNotifyEvent;
    FOnComplete: TNotifyEvent;
    FOnError: TTrimmerObjControlOnError;
    FIntf: ITrimmerObjControl;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps: TTrimmerObjControlProperties;
    function GetServerProperties: TTrimmerObjControlProperties;
{$ENDIF}
    function GetDefaultInterface: ITrimmerObjControl;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
    function Get_InputFN: WideString;
    procedure Set_InputFN(const pVal: WideString);
    function Get_OutputFN: WideString;
    procedure Set_OutputFN(const pVal: WideString);
    function Get_Status: Integer;
    function Get_StreamLength: Double;
    function Get_StartPosition: Double;
    procedure Set_StartPosition(pVal: Double);
    function Get_StopPosition: Double;
    procedure Set_StopPosition(pVal: Double);
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: ITrimmerObjControl);
    procedure Disconnect; override;
    procedure Start;
    procedure Stop;
    procedure SetCallback(const pITrimmerObjControlCB: ITrimmerObjControlCB);
    property DefaultInterface: ITrimmerObjControl read GetDefaultInterface;
    property Status: Integer read Get_Status;
    property StreamLength: Double read Get_StreamLength;
    property InputFN: WideString read Get_InputFN write Set_InputFN;
    property OutputFN: WideString read Get_OutputFN write Set_OutputFN;
    property StartPosition: Double read Get_StartPosition write Set_StartPosition;
    property StopPosition: Double read Get_StopPosition write Set_StopPosition;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TTrimmerObjControlProperties read GetServerProperties;
{$ENDIF}
    property OnStart: TNotifyEvent read FOnStart write FOnStart;
    property OnStop: TNotifyEvent read FOnStop write FOnStop;
    property OnComplete: TNotifyEvent read FOnComplete write FOnComplete;
    property OnError: TTrimmerObjControlOnError read FOnError write FOnError;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TTrimmerObjControl
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TTrimmerObjControlProperties = class(TPersistent)
  private
    FServer:    TTrimmerObjControl;
    function    GetDefaultInterface: ITrimmerObjControl;
    constructor Create(AServer: TTrimmerObjControl);
  protected
    function Get_InputFN: WideString;
    procedure Set_InputFN(const pVal: WideString);
    function Get_OutputFN: WideString;
    procedure Set_OutputFN(const pVal: WideString);
    function Get_Status: Integer;
    function Get_StreamLength: Double;
    function Get_StartPosition: Double;
    procedure Set_StartPosition(pVal: Double);
    function Get_StopPosition: Double;
    procedure Set_StopPosition(pVal: Double);
  public
    property DefaultInterface: ITrimmerObjControl read GetDefaultInterface;
  published
    property InputFN: WideString read Get_InputFN write Set_InputFN;
    property OutputFN: WideString read Get_OutputFN write Set_OutputFN;
    property StartPosition: Double read Get_StartPosition write Set_StartPosition;
    property StopPosition: Double read Get_StopPosition write Set_StopPosition;
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoTrimmerObjControl.Create: ITrimmerObjControl;
begin
  Result := CreateComObject(CLASS_TrimmerObjControl) as ITrimmerObjControl;
end;

class function CoTrimmerObjControl.CreateRemote(const MachineName: string): ITrimmerObjControl;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_TrimmerObjControl) as ITrimmerObjControl;
end;

procedure TTrimmerObjControl.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{B61C3708-CAA8-48CA-9D9C-682D0A5A3852}';
    IntfIID:   '{9D9BF96C-8E7A-41FC-ABB1-CCC9CEF493E9}';
    EventIID:  '{DC2117FE-3CCE-476A-992A-CAF7DED33764}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TTrimmerObjControl.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as ITrimmerObjControl;
  end;
end;

procedure TTrimmerObjControl.ConnectTo(svrIntf: ITrimmerObjControl);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TTrimmerObjControl.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TTrimmerObjControl.GetDefaultInterface: ITrimmerObjControl;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call "Connect" or "ConnectTo" before this operation');
  Result := FIntf;
end;

constructor TTrimmerObjControl.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TTrimmerObjControlProperties.Create(Self);
{$ENDIF}
end;

destructor TTrimmerObjControl.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TTrimmerObjControl.GetServerProperties: TTrimmerObjControlProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TTrimmerObjControl.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
    1: if Assigned(FOnStart) then
         FOnStart(Self);
    2: if Assigned(FOnStop) then
         FOnStop(Self);
    3: if Assigned(FOnComplete) then
         FOnComplete(Self);
    4: if Assigned(FOnError) then
         FOnError(Self,
                  Params[0] {HResult},
                  Params[1] {const WideString});
  end; {case DispID}
end;

function TTrimmerObjControl.Get_InputFN: WideString;
begin
    Result := DefaultInterface.InputFN;
end;

procedure TTrimmerObjControl.Set_InputFN(const pVal: WideString);
  { Warning: The property InputFN has a setter and a getter whose
    types do not match. Delphi was unable to generate a property of
    this sort and so is using a Variant as a passthrough. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.InputFN := pVal;
end;

function TTrimmerObjControl.Get_OutputFN: WideString;
begin
    Result := DefaultInterface.OutputFN;
end;

procedure TTrimmerObjControl.Set_OutputFN(const pVal: WideString);
  { Warning: The property OutputFN has a setter and a getter whose
    types do not match. Delphi was unable to generate a property of
    this sort and so is using a Variant as a passthrough. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.OutputFN := pVal;
end;

function TTrimmerObjControl.Get_Status: Integer;
begin
    Result := DefaultInterface.Status;
end;

function TTrimmerObjControl.Get_StreamLength: Double;
begin
    Result := DefaultInterface.StreamLength;
end;

function TTrimmerObjControl.Get_StartPosition: Double;
begin
    Result := DefaultInterface.StartPosition;
end;

procedure TTrimmerObjControl.Set_StartPosition(pVal: Double);
begin
  DefaultInterface.Set_StartPosition(pVal);
end;

function TTrimmerObjControl.Get_StopPosition: Double;
begin
    Result := DefaultInterface.StopPosition;
end;

procedure TTrimmerObjControl.Set_StopPosition(pVal: Double);
begin
  DefaultInterface.Set_StopPosition(pVal);
end;

procedure TTrimmerObjControl.Start;
begin
  DefaultInterface.Start;
end;

procedure TTrimmerObjControl.Stop;
begin
  DefaultInterface.Stop;
end;

procedure TTrimmerObjControl.SetCallback(const pITrimmerObjControlCB: ITrimmerObjControlCB);
begin
  DefaultInterface.SetCallback(pITrimmerObjControlCB);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TTrimmerObjControlProperties.Create(AServer: TTrimmerObjControl);
begin
  inherited Create;
  FServer := AServer;
end;

function TTrimmerObjControlProperties.GetDefaultInterface: ITrimmerObjControl;
begin
  Result := FServer.DefaultInterface;
end;

function TTrimmerObjControlProperties.Get_InputFN: WideString;
begin
    Result := DefaultInterface.InputFN;
end;

procedure TTrimmerObjControlProperties.Set_InputFN(const pVal: WideString);
  { Warning: The property InputFN has a setter and a getter whose
    types do not match. Delphi was unable to generate a property of
    this sort and so is using a Variant as a passthrough. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.InputFN := pVal;
end;

function TTrimmerObjControlProperties.Get_OutputFN: WideString;
begin
    Result := DefaultInterface.OutputFN;
end;

procedure TTrimmerObjControlProperties.Set_OutputFN(const pVal: WideString);
  { Warning: The property OutputFN has a setter and a getter whose
    types do not match. Delphi was unable to generate a property of
    this sort and so is using a Variant as a passthrough. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.OutputFN := pVal;
end;

function TTrimmerObjControlProperties.Get_Status: Integer;
begin
    Result := DefaultInterface.Status;
end;

function TTrimmerObjControlProperties.Get_StreamLength: Double;
begin
    Result := DefaultInterface.StreamLength;
end;

function TTrimmerObjControlProperties.Get_StartPosition: Double;
begin
    Result := DefaultInterface.StartPosition;
end;

procedure TTrimmerObjControlProperties.Set_StartPosition(pVal: Double);
begin
  DefaultInterface.Set_StartPosition(pVal);
end;

function TTrimmerObjControlProperties.Get_StopPosition: Double;
begin
    Result := DefaultInterface.StopPosition;
end;

procedure TTrimmerObjControlProperties.Set_StopPosition(pVal: Double);
begin
  DefaultInterface.Set_StopPosition(pVal);
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TTrimmerObjControl]);
end;

end.
