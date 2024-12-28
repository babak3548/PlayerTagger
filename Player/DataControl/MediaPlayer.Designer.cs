namespace Player.DataControl
{
    partial class MediaPlayer
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MediaPlayer));
            this.mediaPlyerCtrl = new AxWMPLib.AxWindowsMediaPlayer();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mediaPlyerCtrl)).BeginInit();
            this.SuspendLayout();
            // 
            // bar1
            // 
            this.bar1.OptionsBar.AllowCollapse = true;
            this.bar1.OptionsBar.AllowDelete = true;
            this.bar1.OptionsBar.DisableCustomization = true;
            this.bar1.OptionsBar.DrawDragBorder = false;
            this.bar1.OptionsBar.MultiLine = true;
            this.bar1.OptionsBar.RotateWhenVertical = false;
            this.bar1.OptionsBar.UseWholeRow = true;
            // 
            // trkPosition
            // 
         
            // 
            // mediaPlyerCtrl
            // 
            this.mediaPlyerCtrl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mediaPlyerCtrl.Enabled = true;
            this.mediaPlyerCtrl.Location = new System.Drawing.Point(0, 0);
            this.mediaPlyerCtrl.Name = "mediaPlyerCtrl";
            this.mediaPlyerCtrl.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("mediaPlyerCtrl.OcxState")));
            this.mediaPlyerCtrl.Size = new System.Drawing.Size(832, 517);
            this.mediaPlyerCtrl.TabIndex = 10;
            this.mediaPlyerCtrl.MediaError += new AxWMPLib._WMPOCXEvents_MediaErrorEventHandler(this.mediaPlyerCtrl_MediaError);
            this.mediaPlyerCtrl.OpenStateChange += new AxWMPLib._WMPOCXEvents_OpenStateChangeEventHandler(this.mediaPlyerCtrl_OpenStateChange);
            this.mediaPlyerCtrl.PlayStateChange += new AxWMPLib._WMPOCXEvents_PlayStateChangeEventHandler(this.mediaPlyerCtrl_PlayStateChange);
            this.mediaPlyerCtrl.PositionChange += new AxWMPLib._WMPOCXEvents_PositionChangeEventHandler(this.mediaPlyerCtrl_PositionChange);
            // 
            // MediaPlayer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.mediaPlyerCtrl);
            this.Name = "MediaPlayer";
           
            this.Controls.SetChildIndex(this.mediaPlyerCtrl, 0);
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).EndInit();
           
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mediaPlyerCtrl)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxWMPLib.AxWindowsMediaPlayer mediaPlyerCtrl;
    }
}
