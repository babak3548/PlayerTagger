program SMM_DelphiTrimmerSample;

{$R 'res.res' 'res.rc'}

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  AVITRIMMERCOMLib_TLB in 'AVITRIMMERCOMLib_TLB.pas',
  SMM_Defs in 'SMM_Defs.pas';

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.Title := 'SMM_Trim_AVI_Delphi';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
