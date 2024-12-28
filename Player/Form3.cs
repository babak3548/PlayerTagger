using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using VideoEditor;
namespace Player
{
    public partial class Form3 : Form
    {
        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName);
        [DllImport("user32.dll")]
        public static extern int SendMessage(int hWnd, uint Msg, int wParam, int lParam);

        public const int WM_SYSCOMMAND = 0x0112;
        public const int SC_CLOSE = 0xF060;


        public Form3()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //int iHandle = FindWindow("Notepad",null);
            //if (iHandle > 0)
            //{
            //    // close the window using API        
            //    SendMessage(iHandle, WM_SYSCOMMAND, SC_CLOSE, 0);
            //}  

            
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();

            FileDialog.FileDialog fd = new FileDialog.FileDialog();
            fd.ShowDialog();
            MessageBox.Show(fd.FileName);
        }

        private void Form3_Load(object sender, EventArgs e)
        {

            //axVLCPlugin21.playlist.add(@"D:\Media\2012-07-21.00.00.3-0.rec\00001.mpg", "apple", " ");
            //axVLCPlugin21.playlist.play();
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //axVLCPlugin21.playlist.add(@"file:///D:\Media\2012-07-21.00.00.3-0.rec\00001.mpg", "apple", " ");
            //axVLCPlugin21.playlist.play();
            //axVLCPlugin21.CtlVisible = true;
            //axVLCPlugin21.video.fullscreen = true;
            //axVLCPlugin21.video.takeSnapshot();
            //axVLCPlugin21.Toolbar = true;
            
            
            
        }
    }
}
