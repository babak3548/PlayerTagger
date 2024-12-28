namespace Player.DataControl
{
    partial class VLCPlayer :PlayerControl 
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
            this.repositoryItemTextEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.panel1 = new System.Windows.Forms.Panel();
            this.repositoryItemTimeEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemTimeEdit();
            this.repositoryItemTextEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.TimePositionTextEdit = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.repositoryItemTimeValue = new DevExpress.XtraEditors.Repository.RepositoryItemTimeEdit();
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTimeEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TimePositionTextEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTimeValue)).BeginInit();
            this.SuspendLayout();
            // 
            // TrkVolumeRepository
            // 
            this.TrkVolumeRepository.LabelAppearance.Options.UseTextOptions = true;
            this.TrkVolumeRepository.LabelAppearance.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.TrkVolumeRepository.EditValueChanging += new DevExpress.XtraEditors.Controls.ChangingEventHandler(this.TrkVolumeRepository_EditValueChanging);
            // 
            // trkPosition
            // 
            this.trkPosition.Location = new System.Drawing.Point(0, 508);
            this.trkPosition.Margin = new System.Windows.Forms.Padding(0);
            this.trkPosition.Size = new System.Drawing.Size(871, 20);
            this.trkPosition.Scroll += new System.EventHandler(this.trkPosition_Scroll);
            this.trkPosition.ValueChanged += new System.EventHandler(this.trkPosition_ValueChanged);
            this.trkPosition.MouseDown += new System.Windows.Forms.MouseEventHandler(this.trkPosition_MouseDown);
            // 
            // repositoryItemTextEdit1
            // 
            this.repositoryItemTextEdit1.AutoHeight = false;
            this.repositoryItemTextEdit1.Name = "repositoryItemTextEdit1";
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(871, 508);
            this.panel1.TabIndex = 10;
            // 
            // repositoryItemTimeEdit1
            // 
            this.repositoryItemTimeEdit1.AutoHeight = false;
            this.repositoryItemTimeEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemTimeEdit1.Name = "repositoryItemTimeEdit1";
            // 
            // repositoryItemTextEdit2
            // 
            this.repositoryItemTextEdit2.AutoHeight = false;
            this.repositoryItemTextEdit2.Name = "repositoryItemTextEdit2";
            // 
            // TimePositionTextEdit
            // 
            this.TimePositionTextEdit.AutoHeight = false;
            this.TimePositionTextEdit.Mask.AutoComplete = DevExpress.XtraEditors.Mask.AutoCompleteType.Optimistic;
            this.TimePositionTextEdit.Mask.BeepOnError = true;
            this.TimePositionTextEdit.Mask.EditMask = "\\d?\\d:\\d\\d:\\d\\d";
            this.TimePositionTextEdit.Mask.MaskType = DevExpress.XtraEditors.Mask.MaskType.Regular;
            this.TimePositionTextEdit.Mask.UseMaskAsDisplayFormat = true;
            this.TimePositionTextEdit.Name = "TimePositionTextEdit";
            // 
            // repositoryItemTimeValue
            // 
            this.repositoryItemTimeValue.AutoHeight = false;
            this.repositoryItemTimeValue.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemTimeValue.Mask.EditMask = "HH:mm:ss.ff";
            this.repositoryItemTimeValue.Mask.UseMaskAsDisplayFormat = true;
            this.repositoryItemTimeValue.Name = "repositoryItemTimeValue";
            // 
            // VLCPlayer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Name = "VLCPlayer";
            this.Size = new System.Drawing.Size(871, 551);
            this.Controls.SetChildIndex(this.trkPosition, 0);
            this.Controls.SetChildIndex(this.panel1, 0);
            ((System.ComponentModel.ISupportInitialize)(this.TrkVolumeRepository)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkPosition)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTimeEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TimePositionTextEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTimeValue)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

      
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repositoryItemTextEdit1;
        private System.Windows.Forms.Panel panel1;
        private DevExpress.XtraEditors.Repository.RepositoryItemTimeEdit repositoryItemTimeEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repositoryItemTextEdit2;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit TimePositionTextEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemTimeEdit repositoryItemTimeValue;


    }
}
