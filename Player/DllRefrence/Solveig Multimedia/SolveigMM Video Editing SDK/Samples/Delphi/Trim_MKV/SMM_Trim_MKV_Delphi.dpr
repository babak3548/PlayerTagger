program SMM_Trim_MKV_Delphi;

{$R '..\Trim_AVI\res.res' '..\Trim_AVI\res.rc'}

uses
  Forms,
  Unit1 in '..\Trim_AVI\Unit1.pas' {Form1},
  AVITRIMMERCOMLib_TLB in '..\Trim_AVI\AVITRIMMERCOMLib_TLB.pas',
  SMM_Defs in '..\Trim_AVI\SMM_Defs.pas';

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.Title := 'SMM_Trimmer_MKV_Delphi';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
