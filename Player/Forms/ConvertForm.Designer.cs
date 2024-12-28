namespace Player.Forms
{
    partial class ConvertForm
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
            this.leadConvert1 = new Player.DataControl.LeadConvert();
            this.SuspendLayout();
            // 
            // leadConvert1
            // 
            this.leadConvert1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.leadConvert1.Location = new System.Drawing.Point(0, 0);
            this.leadConvert1.Name = "leadConvert1";
            this.leadConvert1.Size = new System.Drawing.Size(455, 218);
            this.leadConvert1.TabIndex = 0;
            // 
            // ConvertForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 218);
            this.Controls.Add(this.leadConvert1);
            this.Name = "ConvertForm";
            this.Text = "ConvertForm";
            this.ResumeLayout(false);

        }

        #endregion

        //private DataControl.LeadConvert leadConvert1;


    }
}