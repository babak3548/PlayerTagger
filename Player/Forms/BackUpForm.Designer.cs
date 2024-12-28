namespace Player.Forms
{
    partial class BackUpForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BackUpForm));
            this.ucBackUp1 = new Player.DataControl.UCBackUp();
            this.SuspendLayout();
            // 
            // ucBackUp1
            // 
            resources.ApplyResources(this.ucBackUp1, "ucBackUp1");
            this.ucBackUp1.Name = "ucBackUp1";
            // 
            // BackUpForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ucBackUp1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "BackUpForm";
            this.ResumeLayout(false);

        }

        #endregion

        private DataControl.UCBackUp ucBackUp1;

    }
}