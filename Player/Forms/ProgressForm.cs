﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using AVITRIMMERCOMLib;
using System.Windows.Forms;
using VideoEditor;
using Utility;


namespace Player
{
    public partial class ProgressForm : DevExpress.XtraEditors.XtraForm, ITrimmerObjControlCB
    {
        public ProgressForm()
        {
            InitializeComponent();
            Form.CheckForIllegalCrossThreadCalls = false;
        }


        
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            CenterToParent();
        }
        public IUpdateProgress m_Vm;
        System.Diagnostics.Stopwatch St = new System.Diagnostics.Stopwatch();
        public DialogResult ShowDialog(IUpdateProgress vm)
        {
            
            m_Vm = vm;
            timer1.Enabled = true;
            St.Reset();
            ShowDialog();
            return System.Windows.Forms.DialogResult.OK;
        }

        public void OnError(int hr, string Val)
        {
            MessageBox.Show("error");
            OnStop();
        }

        public void OnPause()
        {
            timer1.Enabled = false;
        }

        public void OnStart()
        {
            St.Start();
        }

        public void OnStop()
        {
            m_bCompleted=true;
            timer1.Enabled = false;
            St.Stop();
            Close();
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
            object val;

            label.Text = string.Format("({0}) در حال ذخیره سازی", St.ElapsedMilliseconds.ConvertToTimeFormat());

            //Get progress value in %
            
            progressBar.EditValue = m_Vm.GetProgress();
        }

        public bool m_bCompleted { get; set; }
    }
}
