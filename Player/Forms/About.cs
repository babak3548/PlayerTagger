using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Player.Forms
{
    public partial class About : DevExpress.XtraEditors.XtraForm
    {
        //const string version = "1.0";
        //const string version = "1.1";
        //const string version = "1.2";
        //const string version = "1.3";
       // const string version = "1.5";
        //const string version = "1.6";
        //const string version = "1.7";
        // const string version = "1.8";
       // const string version = "1.9";
      //  const string version = "2.0 : 2013/04/30  ";
     //const string version = "2.1 : 2013/05/21  ";
        //const string version = "2.3 : 2013/09/23  ";
       // const string version = "2.4 : 2013/10/04  ";
       // const string version = "2.5 : 2013/10/20  ";
      // const string version = "2.6 : 2013/12/06  ";
       // const string version = "2.7 : 2013/12/14  ";
       // const string version = "2.8 : 2013/12/21  ";
        //const string version = "2.9 : 2014/01/11  ";
        //   const string version = "3.0 : 2014/01/18  ";
        //const string version = "3.01 : 2014/01/18  ";
        //const string version = "3.02 : 2014/02/21  ";
        //const string version = "3.03 : 2014/03/15  ";
        const string version = "3.04 : 2014/11/19  ";
        public About()
        {
            InitializeComponent();
            Version.Text = version;
           
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {

            //System.Diagnostics.Process.Start((sender as LinkLabel).Text);
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void About_Load(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
