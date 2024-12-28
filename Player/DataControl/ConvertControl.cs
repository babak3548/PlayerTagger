using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Player.DataControl
{
    public partial class ConvertControl : UserControl,IConvertControlBase 
    {
        public ConvertControl()
        {
            InitializeComponent();
            cmbFormat.Properties.DataSource = ListSuportedFormat();
            cmbFormat.Properties.ValueMember = "Key";
            cmbFormat.Properties.DisplayMember = "Value";
           


        }


        private void simpleButton1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Video Files (*.avi;*.mpg;*.mpeg;*.mxf;*.mkv;*.ogg;*.wmv.*.asf;*.qt;*.mov;*.m2v;*.m1v;*.ts;*.m2ts;*.mp4;*.3gp;*.flv;*.f4v;video_ts.ifo;*.LBL)|*.avi;*.mpg;*.mpeg;*.mxf;*.mkv;*.ogg;*.wmv.*.asf;*.qt;*.mov;*.m2v;*.m1v;*.ts;*.m2ts;*.mp4;*.3gp;*.flv;*.f4v;video_ts.ifo;*.LBL|Audio files (*.wav;*.wma;*.ogg;*.mpa;*.mp2;*.mp3;*.mxf;*.mkv;*.au;*.aif;*.aiff;*.snd;*.aac)|*.wav;*.wma;*.ogg;*.mpa;*.mp2;*.mp3;*.mxf;*.mkv;*.au;*.aif;*.aiff;*.snd;*.aac|MPEG Files (*.mpg;*.mpeg;*.m2v;*.m1v;*.ts;*.m2ts)|*.mpg;*.mpeg;*.m2v;*.m1v;*.ts;*.m2ts|MXF Files (*.mxf)|*.mxf|MKV Files (*.mkv)|*.mkv|Windows Media Files (*.asf;*.wma;*.wmv)|*.asf;*.wma;*.wmv|DVD Files (video_ts.ifo)|video_ts.ifo|All Files (*.*)|*.*";
            openFileDialog1.DefaultExt = "avi";
            //OpenFileDialog1.Flags = cdlOFNFileMustExist + cdlOFNReadOnly + cdlOFNPathMustExist
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                TxtSource.Text = openFileDialog1.FileName;
                SetSourceFile( TxtSource.Text);
            }
        }

       virtual  public void SetSourceFile(string SourceFile)
        {
            throw new NotImplementedException();
        }



       private void btnSaveFileTarget_Click(object sender, EventArgs e)
       {
           saveFileDialog1.Filter = "Video Files (*.avi;*.wmv;*.ogg;*.qt;*.mov;*.mpg;*.mpeg;*.mxf;*.mkv;*.m2v;*.m1v;*.ts;*.m2ts;*.mp4;*.3gp;*.flv;*.f4v)|*.avi;*.wmv;*.ogg;*.qt;*.mov;*.mpg;*.mpeg;*.mxf;*.mkv;*.m2v;*.m1v;*.ts;*.m2ts;*.mp4;*.3gp;*.flv;*.f4v|Audio files (*.wav;*.wma;*.ogg;*.mpa;*.mp2;*.mxf;*.mkv;*.aac)|*.wav;*.wma;*.ogg;*.mpa;*.mp2;*.mp3;*.mxf;*.mkv;*.aac|MPEG Files (*.mpg;*.mpeg)|*.mpg;*.mpeg|MXF Files (*.mxf)|*.mxf|MKV Files (*.mkv)|*.mkv|Windows Media Files (*.asf; *.wma; *.wmv)|*.asf; *.wma; *.wmv|All Files (*.*)|*.*;";
          // saveFileDialog1.DefaultExt = "avi";
           //SaveFileDialog1.Flags = cdlOFNOverwritePrompt + cdlOFNPathMustExist + cdlOFNCreatePrompt
           if ((saveFileDialog1.ShowDialog()) == System.Windows.Forms.DialogResult.OK)
           {
               txtTarget.Text = saveFileDialog1.FileName;
           }
       }

       private void btnConvert_Click(object sender, EventArgs e)
       {
           StartConvert();
       }


       virtual public Dictionary<int, string> ListSuportedFormat()
       {

           return null;
       }


       virtual  public void StartConvert()
       {
           throw new NotImplementedException();
       }

         // ConvertCtrl1.Window = IntPtr.Zero;
         //ConvertCtrl1.StopConvert();
         //ConvertCtrl1.TargetFile = "";
    }
}
