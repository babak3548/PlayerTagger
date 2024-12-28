// GongSolutions.Shell - A Windows Shell library for .Net.
// Copyright (C) 2007-2009 Steven J. Kirk
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either 
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public 
// License along with this program; if not, write to the Free 
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  
// Boston, MA 2110-1301, USA.
//
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using GongSolutions.Shell;
using VideoEditor;

namespace FileDialog
{
    public partial class FileDialog : Form
    {


        public string DefaultExt { get { return filterCombo.Filter; } set { filterCombo.Filter=value; } }
        public string FileName {
            get { 
            return shellView.CurrentFolder.FileSystemPath+"\\"+ fileNameCombo.Text; 
            }
            set { fileNameCombo.Text = value; } }
        public string Filter { get { return filterCombo.FilterItems; } set { filterCombo.FilterItems=value; } }
        public int FilterIndex { get { return filterCombo.SelectedIndex; } set { filterCombo.SelectedIndex=value; } }
        public string Title { get; set; }

        public SMM_Defs.SMM_TrimFlags TrimFlags 
        {
            get
            {
                SMM_Defs.SMM_TrimFlags flag=0;

                if (cbVideoOnly.Checked)
                    flag |= SMM_Defs.SMM_TrimFlags.SMM_TrimFlags_VideoOnly;
                if (cbAudioOnly.Checked)
                    flag |= SMM_Defs.SMM_TrimFlags.SMM_TrimFlags_AudioOnly;
                return flag;
            }
        }

        public FileDialog()
        {
            InitializeComponent();
            
           // shellView.CurrentFolder = new ShellItem(Properties.Settings.Default.CurrentFolder);
            shellView.History.Clear();
            this.CenterToParent();
        }

        void OnFileSelected(string filename)
        {
            FileName = filename;
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        void UpdateOpenButtonState()
        {
            SaveButton.Enabled = (shellView.SelectedItems.Length > 0) ||
                                 (fileNameCombo.Text.Length > 0);
        }

        void fileNameCombo_TextChanged(object sender, EventArgs e)
        {
            UpdateOpenButtonState();
        }

        void shellView_DoubleClick(object sender, EventArgs e)
        {
            OnFileSelected(shellView.SelectedItems[0].FileSystemPath);
        }

        void shellView_SelectionChanged(object sender, EventArgs e)
        {
            UpdateOpenButtonState();
        }

        void fileNameCombo_FilenameEntered(object sender, EventArgs e)
        {
            OnFileSelected(fileNameCombo.Text);
        }

        void openButton_Click(object sender, EventArgs e)
        {
            //if (!shellView.NavigateSelectedFolder())
            //{
            //    ShellItem[] selected = shellView.SelectedItems;

            //    if (selected.Length > 0)
            //    {
            //        OnFileSelected(selected[0].FileSystemPath);
            //    }
            //    else if (File.Exists(fileNameCombo.Text))
            //    {
                    
            //        OnFileSelected(shellView.CurrentFolder+  fileNameCombo.Text);
            //    }
            //}
        }

        void cancelButton_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            Close();
        }

        void FileDialog_FormClosed(object sender, FormClosedEventArgs e)
        {
            //Properties.Settings.Default.CurrentFolder = shellView.CurrentFolder.ToString();
            //Properties.Settings.Default.Save();
        }

     

        private void filterCombo_SelectedValueChanged(object sender, EventArgs e)
        {
            string fn = fileNameCombo.Text;
            int index = fn.IndexOf(".");
            if(index>=0)
                {
                    fn = fn.Remove(fn.IndexOf("."));

                }
            fileNameCombo.Text = fn + filterCombo.Filter.Remove(0,1);
                        
        }
    }
}
