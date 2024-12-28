using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Leadtools.Multimedia;
using DevExpress.XtraEditors;

namespace Player.DataControl
{
    public partial class LeadConvert : ConvertControl, IconvertControl
    {
        //internal ConvertCtrl convertCtrl=new ConvertCtrl();
        ComponentResourceManager resourseMng = new ComponentResourceManager(typeof(LeadConvert));
        public LeadConvert():base()
        {
            InitializeComponent();
        }

        public override void SetSourceFile(string SourceFile)
        {
            convertCtrl.SourceFile = SourceFile;
        }

        public override void StartConvert()
        {
            convertCtrl.TargetFormat = (TargetFormatType)(Convert.ToInt32(base.cmbFormat.EditValue));
            SetTargetFile(txtTarget.Text);
            if(CeackBeforConvert())  convertCtrl.StartConvert();

        }

        public override Dictionary<int, string> ListSuportedFormat()
        {
            //add all target formats
            return new Dictionary<int, string>() {
           {(int) TargetFormatType.WMV,  "WMV (Windows Media Codecs)"},           
           {(int)TargetFormatType.WMVMux ,  "WMV (Windows Media Codecs - LEAD Mux)"},
           {(int) TargetFormatType.ASFMux, "ASF (Custom Codecs - LEAD Mux)"},
           {(int ) TargetFormatType.AVI,"AVI"},
           {(int)  TargetFormatType.DICOM, "DICOM" },
           {(int)TargetFormatType.MPEG2DICOM, "MPEG-2 DICOM"},
           {(int)TargetFormatType.DVSDAVI , "DVSD-AVI"},
           {(int)TargetFormatType.MP3 ,"MP3"},
           {(int)TargetFormatType.StillImage , "Still Image"},
           {(int)TargetFormatType.WAVE ,"WAVE"},
           {(int)TargetFormatType.Stream ,   "Raw Stream"},
           {(int)TargetFormatType.OGG ,"OGG"},
           {(int)TargetFormatType.DVSDOGG ,"DVSD-OGG"},
           {(int)TargetFormatType.MPEG1System,"MPEG-1 System"},
           {(int)TargetFormatType.MPEG2Program ,"MPEG-2 Program"},
           {(int)TargetFormatType.MPEG2Transport,"MPEG-2 Transport"},
           {(int)TargetFormatType.DVD,"DVD Image"},
           {(int)TargetFormatType.ISO, "ISO (MP4)"},
           {(int)TargetFormatType.FLVH263 ,"Flash FLV (H263)"},
           {(int)TargetFormatType.FLVH264_2,"Flash FLV (H264)"},
           {(int)TargetFormatType.FLVH264, "Flash F4V (H264)"},
           {(int)TargetFormatType.MXF, "MXF"},
           {(int) TargetFormatType.DVSDMXF ,"DVSD-MXF"           },
           {(int)TargetFormatType.MKV, "MKV"},
           {(int)TargetFormatType.SSF ,"SSF (IIS Smooth Streaming Format)"}
            };
        }

        public void SetTargetFile( string FileName)
        {
            convertCtrl.TargetFile = FileName;
        }

        private void convertCtrl1_Progress(object sender, ProgressEventArgs e)
        {
            prgConvert.Value = e.time;
            if (prgConvert.Value == prgConvert.Maximum)
            {
                prgConvert.Refresh();
                ResetUserControl(resourseMng.GetString("Convert_Completed"));
            }

        }



        private void convertCtrl_ErrorAbort(object sender, ErrorAbortEventArgs e)
        {
            convertCtrl.ErrorAbort -= this.convertCtrl_ErrorAbort;
            ResetUserControl(resourseMng.GetString("Error") + e.errorMessage);
            prgConvert.Value = 0;
        }


        public void ResetUserControl(string message)
        {
            XtraMessageBox.Show(message,"",MessageBoxButtons.OK,MessageBoxIcon.Information) ;
            prgConvert.Value = 0;
            convertCtrl.Window = IntPtr.Zero;
            convertCtrl.StopConvert();
            convertCtrl.TargetFile = "";
            txtTarget.Text  = "";
        }


        public bool CeackBeforConvert()
        {
            if (convertCtrl.TargetFile == null || convertCtrl.TargetFile == "" || convertCtrl.SourceFile == null ||
                convertCtrl.SourceFile == ""  || convertCtrl.TargetFormat == TargetFormatType.NULL)
            { ResetUserControl(resourseMng.GetString("please_correct_values")); return false; }
            return true;
        }
    }
}
