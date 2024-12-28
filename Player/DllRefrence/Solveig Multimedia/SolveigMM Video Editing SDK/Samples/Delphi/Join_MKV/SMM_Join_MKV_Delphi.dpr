program SMM_Join_MKV_Delphi;



{$R '..\Join_AVI\res.res' '..\Join_AVI\res.rc'}

uses
  Forms,
  AVITRIMMERCOMLib_TLB in '..\Join_AVI\AVITRIMMERCOMLib_TLB.pas',
  SMM_Defs in '..\Join_AVI\SMM_Defs.pas',
  Unit1 in '..\Join_AVI\Unit1.pas' {Form1};

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.Title := 'SMM_Join_MKV';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
