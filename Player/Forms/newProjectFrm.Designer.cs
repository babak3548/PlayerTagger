namespace Player.Forms
{
    partial class newProjectFrm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtAddress = new DevExpress.XtraEditors.TextEdit();
            this.txtFileName = new DevExpress.XtraEditors.TextEdit();
            this.btnCreate = new DevExpress.XtraEditors.SimpleButton();
            this.btnShowdialog = new DevExpress.XtraEditors.SimpleButton();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.txtAddress.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFileName.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // txtAddress
            // 
            this.txtAddress.Location = new System.Drawing.Point(51, 52);
            this.txtAddress.Name = "txtAddress";
            this.txtAddress.Size = new System.Drawing.Size(294, 20);
            this.txtAddress.TabIndex = 0;
            // 
            // txtFileName
            // 
            this.txtFileName.Location = new System.Drawing.Point(18, 26);
            this.txtFileName.Name = "txtFileName";
            this.txtFileName.Size = new System.Drawing.Size(327, 20);
            this.txtFileName.TabIndex = 1;
            // 
            // btnCreate
            // 
            this.btnCreate.Location = new System.Drawing.Point(251, 78);
            this.btnCreate.Name = "btnCreate";
            this.btnCreate.Size = new System.Drawing.Size(94, 23);
            this.btnCreate.TabIndex = 2;
            this.btnCreate.Text = "ایجاد";
            this.btnCreate.Click += new System.EventHandler(this.btnCreate_Click);
            // 
            // btnShowdialog
            // 
            this.btnShowdialog.Location = new System.Drawing.Point(18, 49);
            this.btnShowdialog.Name = "btnShowdialog";
            this.btnShowdialog.Size = new System.Drawing.Size(27, 23);
            this.btnShowdialog.TabIndex = 3;
            this.btnShowdialog.Text = ". . .";
            this.btnShowdialog.Click += new System.EventHandler(this.btnShowdialog_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(347, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "نام فایل";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(346, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "مسیر فایل";
            // 
            // newProjectFrm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(405, 114);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnShowdialog);
            this.Controls.Add(this.btnCreate);
            this.Controls.Add(this.txtFileName);
            this.Controls.Add(this.txtAddress);
            this.Name = "newProjectFrm";
            this.Text = "ایجاد پروژه جدید";
            ((System.ComponentModel.ISupportInitialize)(this.txtAddress.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFileName.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.TextEdit txtAddress;
        private DevExpress.XtraEditors.TextEdit txtFileName;
        private DevExpress.XtraEditors.SimpleButton btnCreate;
        private DevExpress.XtraEditors.SimpleButton btnShowdialog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}