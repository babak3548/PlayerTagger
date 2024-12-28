namespace Player
{
    partial class ChapterListLyoutView
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
            this.gridControl3 = new DevExpress.XtraGrid.GridControl();
            this.layoutView1 = new DevExpress.XtraGrid.Views.Layout.LayoutView();
            this.bandedGridColumn1 = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.repositoryItemPictureEdit3 = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.layoutViewField_colThumbnailImage1 = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.bandedGridColumn3 = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.repositoryItemMemoExEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit();
            this.layoutViewField_colDescription1 = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.colLengh = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.layoutViewField_colLengh = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.colEndPositionText = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.layoutViewField_colEndPositionText = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.colStartPositionText = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.layoutViewField_colStartPositionText = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.colTitle3 = new DevExpress.XtraGrid.Columns.LayoutViewColumn();
            this.layoutViewField_colTitle3 = new DevExpress.XtraGrid.Views.Layout.LayoutViewField();
            this.layoutViewCard1 = new DevExpress.XtraGrid.Views.Layout.LayoutViewCard();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colThumbnailImage1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colDescription1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colLengh)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colEndPositionText)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colStartPositionText)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colTitle3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewCard1)).BeginInit();
            this.SuspendLayout();
            // 
            // gridControl3
            // 
            this.gridControl3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gridControl3.Location = new System.Drawing.Point(0, 0);
            this.gridControl3.MainView = this.layoutView1;
            this.gridControl3.Name = "gridControl3";
            this.gridControl3.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemPictureEdit3,
            this.repositoryItemMemoExEdit2});
            this.gridControl3.Size = new System.Drawing.Size(853, 161);
            this.gridControl3.TabIndex = 2;
            this.gridControl3.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.layoutView1});
            // 
            // layoutView1
            // 
            this.layoutView1.Appearance.Card.BackColor = System.Drawing.Color.White;
            this.layoutView1.Appearance.Card.ForeColor = System.Drawing.Color.White;
            this.layoutView1.Appearance.Card.Options.UseBackColor = true;
            this.layoutView1.Appearance.Card.Options.UseForeColor = true;
            this.layoutView1.Appearance.FieldEditingValue.BackColor = System.Drawing.Color.White;
            this.layoutView1.Appearance.FieldEditingValue.Options.UseBackColor = true;
            this.layoutView1.Appearance.FieldValue.BackColor = System.Drawing.Color.White;
            this.layoutView1.Appearance.FieldValue.Options.UseBackColor = true;
            this.layoutView1.Appearance.FocusedCardCaption.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.layoutView1.Appearance.FocusedCardCaption.Options.UseBackColor = true;
            this.layoutView1.Appearance.SelectedCardCaption.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.layoutView1.Appearance.SelectedCardCaption.Options.UseBackColor = true;
            this.layoutView1.Appearance.SelectionFrame.BackColor = System.Drawing.Color.Red;
            this.layoutView1.Appearance.SelectionFrame.Options.UseBackColor = true;
            this.layoutView1.CardCaptionFormat = "Title";
            this.layoutView1.CardHorzInterval = 0;
            this.layoutView1.CardMinSize = new System.Drawing.Size(142, 150);
            this.layoutView1.CardVertInterval = 0;
            this.layoutView1.Columns.AddRange(new DevExpress.XtraGrid.Columns.LayoutViewColumn[] {
            this.bandedGridColumn1,
            this.bandedGridColumn3,
            this.colLengh,
            this.colEndPositionText,
            this.colStartPositionText,
            this.colTitle3});
            this.layoutView1.GridControl = this.gridControl3;
            this.layoutView1.Name = "layoutView1";
            this.layoutView1.OptionsBehavior.ScrollVisibility = DevExpress.XtraGrid.Views.Base.ScrollVisibility.Auto;
            this.layoutView1.OptionsCarouselMode.StretchCardToViewWidth = true;
            this.layoutView1.OptionsItemText.TextToControlDistance = 0;
            this.layoutView1.OptionsSelection.MultiSelect = true;
            this.layoutView1.OptionsView.CardArrangeRule = DevExpress.XtraGrid.Views.Layout.LayoutCardArrangeRule.AllowPartialCards;
            this.layoutView1.OptionsView.ShowCardFieldBorders = true;
            this.layoutView1.OptionsView.ShowFilterPanelMode = DevExpress.XtraGrid.Views.Base.ShowFilterPanelMode.Never;
            this.layoutView1.OptionsView.ShowHeaderPanel = false;
            this.layoutView1.OptionsView.ViewMode = DevExpress.XtraGrid.Views.Layout.LayoutViewMode.Row;
            this.layoutView1.TemplateCard = this.layoutViewCard1;
            // 
            // bandedGridColumn1
            // 
            this.bandedGridColumn1.Caption = "تصویر";
            this.bandedGridColumn1.ColumnEdit = this.repositoryItemPictureEdit3;
            this.bandedGridColumn1.CustomizationCaption = "تصویر";
            this.bandedGridColumn1.FieldName = "ThumbnailImage";
            this.bandedGridColumn1.LayoutViewField = this.layoutViewField_colThumbnailImage1;
            this.bandedGridColumn1.Name = "bandedGridColumn1";
            this.bandedGridColumn1.OptionsColumn.AllowSize = false;
            this.bandedGridColumn1.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.bandedGridColumn1.OptionsColumn.FixedWidth = true;
            this.bandedGridColumn1.OptionsColumn.ReadOnly = true;
            this.bandedGridColumn1.OptionsColumn.ShowCaption = false;
            this.bandedGridColumn1.OptionsFilter.AllowFilter = false;
            this.bandedGridColumn1.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.bandedGridColumn1.Width = 60;
            // 
            // repositoryItemPictureEdit3
            // 
            this.repositoryItemPictureEdit3.Name = "repositoryItemPictureEdit3";
            this.repositoryItemPictureEdit3.PictureInterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            this.repositoryItemPictureEdit3.ShowZoomSubMenu = DevExpress.Utils.DefaultBoolean.True;
            this.repositoryItemPictureEdit3.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Stretch;
            // 
            // layoutViewField_colThumbnailImage1
            // 
            this.layoutViewField_colThumbnailImage1.EditorPreferredWidth = 142;
            this.layoutViewField_colThumbnailImage1.Location = new System.Drawing.Point(0, 0);
            this.layoutViewField_colThumbnailImage1.MaxSize = new System.Drawing.Size(130, 84);
            this.layoutViewField_colThumbnailImage1.MinSize = new System.Drawing.Size(130, 24);
            this.layoutViewField_colThumbnailImage1.Name = "layoutViewField_colThumbnailImage1";
            this.layoutViewField_colThumbnailImage1.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colThumbnailImage1.Size = new System.Drawing.Size(142, 24);
            this.layoutViewField_colThumbnailImage1.SizeConstraintsType = DevExpress.XtraLayout.SizeConstraintsType.Custom;
            this.layoutViewField_colThumbnailImage1.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colThumbnailImage1.TextToControlDistance = 0;
            this.layoutViewField_colThumbnailImage1.TextVisible = false;
            // 
            // bandedGridColumn3
            // 
            this.bandedGridColumn3.Caption = "شرح";
            this.bandedGridColumn3.ColumnEdit = this.repositoryItemMemoExEdit2;
            this.bandedGridColumn3.CustomizationCaption = "شرح";
            this.bandedGridColumn3.FieldName = "Description";
            this.bandedGridColumn3.LayoutViewField = this.layoutViewField_colDescription1;
            this.bandedGridColumn3.Name = "bandedGridColumn3";
            this.bandedGridColumn3.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.bandedGridColumn3.OptionsColumn.FixedWidth = true;
            this.bandedGridColumn3.OptionsColumn.ShowCaption = false;
            this.bandedGridColumn3.OptionsFilter.AllowFilter = false;
            this.bandedGridColumn3.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.bandedGridColumn3.Width = 123;
            // 
            // repositoryItemMemoExEdit2
            // 
            this.repositoryItemMemoExEdit2.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemMemoExEdit2.Name = "repositoryItemMemoExEdit2";
            // 
            // layoutViewField_colDescription1
            // 
            this.layoutViewField_colDescription1.EditorPreferredWidth = 142;
            this.layoutViewField_colDescription1.Location = new System.Drawing.Point(0, 72);
            this.layoutViewField_colDescription1.MaxSize = new System.Drawing.Size(0, 18);
            this.layoutViewField_colDescription1.MinSize = new System.Drawing.Size(142, 18);
            this.layoutViewField_colDescription1.Name = "layoutViewField_colDescription1";
            this.layoutViewField_colDescription1.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colDescription1.Size = new System.Drawing.Size(142, 18);
            this.layoutViewField_colDescription1.SizeConstraintsType = DevExpress.XtraLayout.SizeConstraintsType.Custom;
            this.layoutViewField_colDescription1.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colDescription1.TextToControlDistance = 0;
            this.layoutViewField_colDescription1.TextVisible = false;
            // 
            // colLengh
            // 
            this.colLengh.FieldName = "Lengh";
            this.colLengh.LayoutViewField = this.layoutViewField_colLengh;
            this.colLengh.Name = "colLengh";
            this.colLengh.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.colLengh.OptionsFilter.AllowFilter = false;
            // 
            // layoutViewField_colLengh
            // 
            this.layoutViewField_colLengh.EditorPreferredWidth = 142;
            this.layoutViewField_colLengh.Location = new System.Drawing.Point(0, 40);
            this.layoutViewField_colLengh.Name = "layoutViewField_colLengh";
            this.layoutViewField_colLengh.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colLengh.Size = new System.Drawing.Size(142, 16);
            this.layoutViewField_colLengh.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colLengh.TextToControlDistance = 0;
            this.layoutViewField_colLengh.TextVisible = false;
            // 
            // colEndPositionText
            // 
            this.colEndPositionText.FieldName = "EndPositionText";
            this.colEndPositionText.LayoutViewField = this.layoutViewField_colEndPositionText;
            this.colEndPositionText.Name = "colEndPositionText";
            this.colEndPositionText.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.colEndPositionText.OptionsFilter.AllowFilter = false;
            // 
            // layoutViewField_colEndPositionText
            // 
            this.layoutViewField_colEndPositionText.EditorPreferredWidth = 71;
            this.layoutViewField_colEndPositionText.Location = new System.Drawing.Point(71, 56);
            this.layoutViewField_colEndPositionText.Name = "layoutViewField_colEndPositionText";
            this.layoutViewField_colEndPositionText.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colEndPositionText.Size = new System.Drawing.Size(71, 16);
            this.layoutViewField_colEndPositionText.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colEndPositionText.TextToControlDistance = 0;
            this.layoutViewField_colEndPositionText.TextVisible = false;
            // 
            // colStartPositionText
            // 
            this.colStartPositionText.FieldName = "StartPositionText";
            this.colStartPositionText.LayoutViewField = this.layoutViewField_colStartPositionText;
            this.colStartPositionText.Name = "colStartPositionText";
            this.colStartPositionText.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.colStartPositionText.OptionsFilter.AllowFilter = false;
            // 
            // layoutViewField_colStartPositionText
            // 
            this.layoutViewField_colStartPositionText.EditorPreferredWidth = 71;
            this.layoutViewField_colStartPositionText.Location = new System.Drawing.Point(0, 56);
            this.layoutViewField_colStartPositionText.Name = "layoutViewField_colStartPositionText";
            this.layoutViewField_colStartPositionText.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colStartPositionText.Size = new System.Drawing.Size(71, 16);
            this.layoutViewField_colStartPositionText.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colStartPositionText.TextToControlDistance = 0;
            this.layoutViewField_colStartPositionText.TextVisible = false;
            // 
            // colTitle3
            // 
            this.colTitle3.FieldName = "Title";
            this.colTitle3.LayoutViewField = this.layoutViewField_colTitle3;
            this.colTitle3.Name = "colTitle3";
            this.colTitle3.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.colTitle3.OptionsColumn.ShowCaption = false;
            this.colTitle3.OptionsFilter.AllowFilter = false;
            // 
            // layoutViewField_colTitle3
            // 
            this.layoutViewField_colTitle3.EditorPreferredWidth = 142;
            this.layoutViewField_colTitle3.Location = new System.Drawing.Point(0, 24);
            this.layoutViewField_colTitle3.Name = "layoutViewField_colTitle3";
            this.layoutViewField_colTitle3.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewField_colTitle3.Size = new System.Drawing.Size(142, 16);
            this.layoutViewField_colTitle3.TextSize = new System.Drawing.Size(0, 0);
            this.layoutViewField_colTitle3.TextToControlDistance = 0;
            this.layoutViewField_colTitle3.TextVisible = false;
            // 
            // layoutViewCard1
            // 
            this.layoutViewCard1.CaptionImageVisible = false;
            this.layoutViewCard1.CustomizationFormText = "TemplateCard";
            this.layoutViewCard1.ExpandButtonLocation = DevExpress.Utils.GroupElementLocation.AfterText;
            this.layoutViewCard1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.layoutViewField_colThumbnailImage1,
            this.layoutViewField_colLengh,
            this.layoutViewField_colEndPositionText,
            this.layoutViewField_colTitle3,
            this.layoutViewField_colDescription1,
            this.layoutViewField_colStartPositionText});
            this.layoutViewCard1.Name = "layoutViewTemplateCard";
            this.layoutViewCard1.OptionsCustomization.AllowDrag = DevExpress.XtraLayout.ItemDragDropMode.Allow;
            this.layoutViewCard1.OptionsCustomization.AllowDrop = DevExpress.XtraLayout.ItemDragDropMode.Allow;
            this.layoutViewCard1.OptionsItemText.TextToControlDistance = 0;
            this.layoutViewCard1.Padding = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutViewCard1.Text = "TemplateCard";
            // 
            // ChapterListLyoutView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.gridControl3);
            this.Name = "ChapterListLyoutView";
            this.Size = new System.Drawing.Size(853, 161);
            ((System.ComponentModel.ISupportInitialize)(this.gridControl3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colThumbnailImage1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colDescription1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colLengh)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colEndPositionText)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colStartPositionText)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewField_colTitle3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutViewCard1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraGrid.GridControl gridControl3;
        private DevExpress.XtraGrid.Views.Layout.LayoutView layoutView1;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn bandedGridColumn1;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit repositoryItemPictureEdit3;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colThumbnailImage1;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn bandedGridColumn3;
        private DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit repositoryItemMemoExEdit2;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colDescription1;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn colLengh;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colLengh;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn colEndPositionText;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colEndPositionText;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn colStartPositionText;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colStartPositionText;
        private DevExpress.XtraGrid.Columns.LayoutViewColumn colTitle3;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewField layoutViewField_colTitle3;
        private DevExpress.XtraGrid.Views.Layout.LayoutViewCard layoutViewCard1;

    }
}
