using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Player.DataControl;
using Player.Setting;
using System.Threading;

namespace Player.Forms
{
    public partial class BackUpRestoreForm : DevExpress.XtraEditors.XtraForm
    {
        public BackUpRestoreForm()
        {
            InitializeComponent();
            UCRestoreBackup restoreBackUp = new UCRestoreBackup();

            this.Controls.Add(restoreBackUp);
            restoreBackUp.Dock = DockStyle.Fill;
        }

        private void ucRestoreBackup1_Load(object sender, EventArgs e)
        {

        }
    }
}
