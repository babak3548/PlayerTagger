using DevExpress.XtraBars;
namespace Player
{
    partial class frmMain {
        protected override void Dispose(bool disposing) {
            if(disposing) {
                if(components != null) {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            DevExpress.XtraGrid.GridLevelNode gridLevelNode1 = new DevExpress.XtraGrid.GridLevelNode();
            DevExpress.XtraGrid.GridLevelNode gridLevelNode2 = new DevExpress.XtraGrid.GridLevelNode();
            this.ListItemgridView = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.colSourceType = new DevExpress.XtraGrid.Columns.GridColumn();
            this.ImageComboBox = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();
            this.imageCollection1 = new DevExpress.Utils.ImageCollection(this.components);
            this.colTitle = new DevExpress.XtraGrid.Columns.GridColumn();
            this.gridControl = new DevExpress.XtraGrid.GridControl();
            this.PlayListbindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.gridView1 = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.gridColumn1 = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.ChaptureGridView = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.gridColumn3 = new DevExpress.XtraGrid.Columns.GridColumn();
            this.colTitle1 = new DevExpress.XtraGrid.Columns.GridColumn();
            this.barManager1 = new DevExpress.XtraBars.BarManager(this.components);
            this.bar1 = new DevExpress.XtraBars.Bar();
            this.siFile = new DevExpress.XtraBars.BarSubItem();
            this.siNew = new DevExpress.XtraBars.BarSubItem();
            this.iProject = new DevExpress.XtraBars.BarButtonItem();
            this.iFile = new DevExpress.XtraBars.BarButtonItem();
            this.iBlankSolution = new DevExpress.XtraBars.BarButtonItem();
            this.iOpen = new DevExpress.XtraBars.BarButtonItem();
            this.iClose = new DevExpress.XtraBars.BarButtonItem();
            this.iAddNewItem = new DevExpress.XtraBars.BarButtonItem();
            this.iAddExistingItem = new DevExpress.XtraBars.BarButtonItem();
            this.siAddProject = new DevExpress.XtraBars.BarSubItem();
            this.iNewProject = new DevExpress.XtraBars.BarButtonItem();
            this.iExistingProject = new DevExpress.XtraBars.BarButtonItem();
            this.iOpenSolution = new DevExpress.XtraBars.BarButtonItem();
            this.iCloseSolution = new DevExpress.XtraBars.BarButtonItem();
            this.iSaveAll = new DevExpress.XtraBars.BarButtonItem();
            this.iPageSetup = new DevExpress.XtraBars.BarButtonItem();
            this.iPrint = new DevExpress.XtraBars.BarButtonItem();
            this.iExit = new DevExpress.XtraBars.BarButtonItem();
            this.siEdit = new DevExpress.XtraBars.BarSubItem();
            this.iUndo = new DevExpress.XtraBars.BarButtonItem();
            this.iRedo = new DevExpress.XtraBars.BarButtonItem();
            this.iCut = new DevExpress.XtraBars.BarButtonItem();
            this.iCopy = new DevExpress.XtraBars.BarButtonItem();
            this.iPaste = new DevExpress.XtraBars.BarButtonItem();
            this.iCycle = new DevExpress.XtraBars.BarButtonItem();
            this.iDelete = new DevExpress.XtraBars.BarButtonItem();
            this.iSelectAll = new DevExpress.XtraBars.BarButtonItem();
            this.siLayouts = new DevExpress.XtraBars.BarSubItem();
            this.iLoadLayout = new DevExpress.XtraBars.BarButtonItem();
            this.iSaveLayout = new DevExpress.XtraBars.BarButtonItem();
            this.siWindow = new DevExpress.XtraBars.BarSubItem();
            this.iPaintStyle = new DevExpress.XtraBars.BarSubItem();
            this.barDockingMenuItem1 = new DevExpress.XtraBars.BarDockingMenuItem();
            this.bar2 = new DevExpress.XtraBars.Bar();
            this.iNew = new DevExpress.XtraBars.BarButtonItem();
            this.popupMenu1 = new DevExpress.XtraBars.PopupMenu(this.components);
            this.iOpenFile = new DevExpress.XtraBars.BarButtonItem();
            this.iSave = new DevExpress.XtraBars.BarButtonItem();
            this.bar3 = new DevExpress.XtraBars.Bar();
            this.iSolutionExplorer = new DevExpress.XtraBars.BarButtonItem();
            this.iProperties = new DevExpress.XtraBars.BarButtonItem();
            this.iToolbox = new DevExpress.XtraBars.BarButtonItem();
            this.iClassView = new DevExpress.XtraBars.BarButtonItem();
            this.iTaskList = new DevExpress.XtraBars.BarButtonItem();
            this.iFindResults = new DevExpress.XtraBars.BarButtonItem();
            this.iOutput = new DevExpress.XtraBars.BarButtonItem();
            this.bar4 = new DevExpress.XtraBars.Bar();
            this.iStatus1 = new DevExpress.XtraBars.BarStaticItem();
            this.iStatus2 = new DevExpress.XtraBars.BarStaticItem();
            this.bar5 = new DevExpress.XtraBars.Bar();
            this.barAndDockingController1 = new DevExpress.XtraBars.BarAndDockingController(this.components);
            this.barDockControl1 = new DevExpress.XtraBars.BarDockControl();
            this.barDockControl2 = new DevExpress.XtraBars.BarDockControl();
            this.barDockControl3 = new DevExpress.XtraBars.BarDockControl();
            this.barDockControl4 = new DevExpress.XtraBars.BarDockControl();
            this.dockManager1 = new DevExpress.XtraBars.Docking.DockManager(this.components);
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.panelContainer2 = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelShot = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel3_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.vGridControlChapters = new DevExpress.XtraVerticalGrid.VGridControl();
            this.ChapterbindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.DesrepositoryItemMemoExEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit();
            this.ImagerepositoryItemPictureEdit = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.TitlerepositoryItemTextEdit = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.LenrepositoryItemTextEdit = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.GrouprepositoryItemMRUEdit = new DevExpress.XtraEditors.Repository.RepositoryItemMRUEdit();
            this.SelectedCheckEdit = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.PositionrepositoryItemTextEdit = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.rowPosition = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowThumbnailSource = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowThumbnailImage = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.LenRow = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.rowTitlerGroup = new DevExpress.XtraVerticalGrid.Rows.MultiEditorRow();
            this.Timerow = new DevExpress.XtraVerticalGrid.Rows.MultiEditorRow();
            this.rowDescription = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.ChapterMSelected = new DevExpress.XtraVerticalGrid.Rows.EditorRow();
            this.dockPanelTask = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel4_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelOutPut = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel5_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.panelContainer1 = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelSolution = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel1_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelFind = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel2_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.gridControl2 = new DevExpress.XtraGrid.GridControl();
            this.AllchapterBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.advBandedGridView1 = new DevExpress.XtraGrid.Views.BandedGrid.AdvBandedGridView();
            this.gridBand1 = new DevExpress.XtraGrid.Views.BandedGrid.GridBand();
            this.colThumbnailImage = new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn();
            this.repositoryItemPictureEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.gridBand2 = new DevExpress.XtraGrid.Views.BandedGrid.GridBand();
            this.Colgroup = new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn();
            this.colTitle2 = new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn();
            this.colDescription = new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn();
            this.repositoryItemMemoEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemMemoEdit();
            this.colFullInfoHtml = new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn();
            this.iFind = new DevExpress.XtraBars.BarButtonItem();
            this.BarMdiChildrenListItem1 = new DevExpress.XtraBars.BarMdiChildrenListItem();
            this.repositoryImageComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();
            this.repositoryItemComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemComboBox();
            this.repositoryItemImageComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();
            this.imageList2 = new System.Windows.Forms.ImageList(this.components);
            this.imageList3 = new System.Windows.Forms.ImageList(this.components);
            this.popupMenu2 = new DevExpress.XtraBars.PopupMenu(this.components);
            this.defaultLookAndFeel1 = new DevExpress.LookAndFeel.DefaultLookAndFeel(this.components);
            this.documentManager1 = new DevExpress.XtraBars.Docking2010.DocumentManager(this.components);
            this.tabbedView1 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.TabbedView(this.components);
            this.imageList4 = new System.Windows.Forms.ImageList(this.components);
            this.document1 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document2 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document3 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document4 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document5 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document6 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.document7 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            this.CurrentChapterbindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.imageCollectionLarge = new DevExpress.Utils.ImageCollection(this.components);
            this.openFileMetaData = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.AllChapterGroupbindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.DurationTimer = new System.Windows.Forms.Timer(this.components);
            this.document8 = new DevExpress.XtraBars.Docking2010.Views.Tabbed.Document(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.ListItemgridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImageComboBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollection1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayListbindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChaptureGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barAndDockingController1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).BeginInit();
            this.panelContainer2.SuspendLayout();
            this.dockPanelShot.SuspendLayout();
            this.dockPanel3_Container.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.vGridControlChapters)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChapterbindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DesrepositoryItemMemoExEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImagerepositoryItemPictureEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TitlerepositoryItemTextEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LenrepositoryItemTextEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GrouprepositoryItemMRUEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SelectedCheckEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PositionrepositoryItemTextEdit)).BeginInit();
            this.dockPanelTask.SuspendLayout();
            this.dockPanelOutPut.SuspendLayout();
            this.panelContainer1.SuspendLayout();
            this.dockPanelSolution.SuspendLayout();
            this.dockPanel1_Container.SuspendLayout();
            this.dockPanelFind.SuspendLayout();
            this.dockPanel2_Container.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AllchapterBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.advBandedGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryImageComboBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemComboBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.documentManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabbedView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document7)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentChapterbindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollectionLarge)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AllChapterGroupbindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.document8)).BeginInit();
            this.SuspendLayout();
            // 
            // ListItemgridView
            // 
            this.ListItemgridView.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.colSourceType,
            this.colTitle});
            this.ListItemgridView.FocusRectStyle = DevExpress.XtraGrid.Views.Grid.DrawFocusRectStyle.RowFocus;
            this.ListItemgridView.GridControl = this.gridControl;
            this.ListItemgridView.Name = "ListItemgridView";
            this.ListItemgridView.OptionsView.ShowColumnHeaders = false;
            this.ListItemgridView.OptionsView.ShowFilterPanelMode = DevExpress.XtraGrid.Views.Base.ShowFilterPanelMode.Never;
            this.ListItemgridView.OptionsView.ShowGroupExpandCollapseButtons = false;
            this.ListItemgridView.OptionsView.ShowGroupPanel = false;
            this.ListItemgridView.OptionsView.ShowIndicator = false;
            this.ListItemgridView.OptionsView.ShowPreviewRowLines = DevExpress.Utils.DefaultBoolean.False;
            this.ListItemgridView.OptionsView.ShowVerticalLines = DevExpress.Utils.DefaultBoolean.False;
            this.ListItemgridView.DoubleClick += new System.EventHandler(this.ListItemgridView_DoubleClick);
            // 
            // colSourceType
            // 
            this.colSourceType.ColumnEdit = this.ImageComboBox;
            this.colSourceType.FieldName = "SourceTypeIndex";
            this.colSourceType.Name = "colSourceType";
            this.colSourceType.OptionsColumn.AllowEdit = false;
            this.colSourceType.OptionsColumn.AllowFocus = false;
            this.colSourceType.OptionsColumn.AllowGroup = DevExpress.Utils.DefaultBoolean.False;
            this.colSourceType.OptionsColumn.AllowIncrementalSearch = false;
            this.colSourceType.OptionsColumn.AllowMerge = DevExpress.Utils.DefaultBoolean.False;
            this.colSourceType.OptionsColumn.AllowMove = false;
            this.colSourceType.OptionsColumn.AllowShowHide = false;
            this.colSourceType.OptionsColumn.AllowSize = false;
            this.colSourceType.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.colSourceType.OptionsColumn.FixedWidth = true;
            this.colSourceType.OptionsColumn.ReadOnly = true;
            this.colSourceType.OptionsColumn.ShowCaption = false;
            this.colSourceType.OptionsColumn.ShowInCustomizationForm = false;
            this.colSourceType.OptionsColumn.ShowInExpressionEditor = false;
            this.colSourceType.Visible = true;
            this.colSourceType.VisibleIndex = 1;
            this.colSourceType.Width = 20;
            // 
            // ImageComboBox
            // 
            this.ImageComboBox.AutoHeight = false;
            this.ImageComboBox.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ImageComboBox.Items.AddRange(new DevExpress.XtraEditors.Controls.ImageComboBoxItem[] {
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", 10, 4),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", 1, 8),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", 2, 10),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", 4, 5),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", 11, 9)});
            this.ImageComboBox.Name = "ImageComboBox";
            this.ImageComboBox.SmallImages = this.imageCollection1;
            // 
            // imageCollection1
            // 
            this.imageCollection1.ImageStream = ((DevExpress.Utils.ImageCollectionStreamer)(resources.GetObject("imageCollection1.ImageStream")));
            this.imageCollection1.Images.SetKeyName(0, "GenericThumbnailImage_Audio.jpg");
            this.imageCollection1.Images.SetKeyName(1, "GenericThumbnailImage_Image.png");
            this.imageCollection1.Images.SetKeyName(2, "GenericThumbnailImage_Video.jpg");
            this.imageCollection1.Images.SetKeyName(3, "pictures.png");
            this.imageCollection1.Images.SetKeyName(4, "Music-folder.ico");
            this.imageCollection1.Images.SetKeyName(5, "Windows-Media-Player.ico");
            this.imageCollection1.Images.SetKeyName(6, "kbemusedsrv.png");
            this.imageCollection1.Images.SetKeyName(7, "playlist_256.png");
            this.imageCollection1.Images.SetKeyName(8, "photos.png");
            this.imageCollection1.Images.SetKeyName(9, "film.png");
            this.imageCollection1.Images.SetKeyName(10, "music-beam.png");
            // 
            // colTitle
            // 
            this.colTitle.FieldName = "Title";
            this.colTitle.Name = "colTitle";
            this.colTitle.OptionsColumn.ShowCaption = false;
            this.colTitle.Visible = true;
            this.colTitle.VisibleIndex = 0;
            // 
            // gridControl
            // 
            this.gridControl.DataSource = this.PlayListbindingSource;
            this.gridControl.Dock = System.Windows.Forms.DockStyle.Fill;
            gridLevelNode1.LevelTemplate = this.ListItemgridView;
            gridLevelNode2.LevelTemplate = this.ChaptureGridView;
            gridLevelNode2.RelationName = "Chapters";
            gridLevelNode1.Nodes.AddRange(new DevExpress.XtraGrid.GridLevelNode[] {
            gridLevelNode2});
            gridLevelNode1.RelationName = "Items";
            this.gridControl.LevelTree.Nodes.AddRange(new DevExpress.XtraGrid.GridLevelNode[] {
            gridLevelNode1});
            this.gridControl.Location = new System.Drawing.Point(0, 0);
            this.gridControl.LookAndFeel.SkinName = "Blue";
            this.gridControl.MainView = this.gridView1;
            this.gridControl.Name = "gridControl";
            this.gridControl.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.ImageComboBox});
            this.gridControl.Size = new System.Drawing.Size(242, 308);
            this.gridControl.TabIndex = 1;
            this.gridControl.UseDisabledStatePainter = false;
            this.gridControl.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView1,
            this.ChaptureGridView,
            this.ListItemgridView});
            // 
            // PlayListbindingSource
            // 
            this.PlayListbindingSource.DataSource = typeof(Player.Playlist);
            // 
            // gridView1
            // 
            this.gridView1.ChildGridLevelName = "ListItemgridView";
            this.gridView1.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gridColumn1,
            this.colName});
            this.gridView1.FocusRectStyle = DevExpress.XtraGrid.Views.Grid.DrawFocusRectStyle.RowFocus;
            this.gridView1.GridControl = this.gridControl;
            this.gridView1.Name = "gridView1";
            this.gridView1.OptionsBehavior.AllowIncrementalSearch = true;
            this.gridView1.OptionsFilter.ShowAllTableValuesInFilterPopup = true;
            this.gridView1.OptionsFilter.UseNewCustomFilterDialog = true;
            this.gridView1.OptionsSelection.InvertSelection = true;
            this.gridView1.OptionsView.ShowChildrenInGroupPanel = true;
            this.gridView1.OptionsView.ShowColumnHeaders = false;
            this.gridView1.OptionsView.ShowFilterPanelMode = DevExpress.XtraGrid.Views.Base.ShowFilterPanelMode.ShowAlways;
            this.gridView1.OptionsView.ShowGroupPanel = false;
            this.gridView1.OptionsView.ShowIndicator = false;
            this.gridView1.OptionsView.ShowVerticalLines = DevExpress.Utils.DefaultBoolean.False;
            // 
            // gridColumn1
            // 
            this.gridColumn1.Caption = "gridColumn1";
            this.gridColumn1.ColumnEdit = this.ImageComboBox;
            this.gridColumn1.FieldName = "gridColumn1";
            this.gridColumn1.Name = "gridColumn1";
            this.gridColumn1.OptionsColumn.AllowEdit = false;
            this.gridColumn1.OptionsColumn.AllowFocus = false;
            this.gridColumn1.OptionsColumn.AllowGroup = DevExpress.Utils.DefaultBoolean.False;
            this.gridColumn1.OptionsColumn.AllowIncrementalSearch = false;
            this.gridColumn1.OptionsColumn.AllowMerge = DevExpress.Utils.DefaultBoolean.False;
            this.gridColumn1.OptionsColumn.AllowMove = false;
            this.gridColumn1.OptionsColumn.AllowShowHide = false;
            this.gridColumn1.OptionsColumn.AllowSize = false;
            this.gridColumn1.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.True;
            this.gridColumn1.OptionsColumn.FixedWidth = true;
            this.gridColumn1.OptionsColumn.ShowCaption = false;
            this.gridColumn1.OptionsColumn.ShowInCustomizationForm = false;
            this.gridColumn1.OptionsColumn.ShowInExpressionEditor = false;
            this.gridColumn1.OptionsColumn.TabStop = false;
            this.gridColumn1.UnboundExpression = "10";
            this.gridColumn1.UnboundType = DevExpress.Data.UnboundColumnType.Integer;
            this.gridColumn1.Visible = true;
            this.gridColumn1.VisibleIndex = 0;
            this.gridColumn1.Width = 33;
            // 
            // colName
            // 
            this.colName.FieldName = "Name";
            this.colName.Name = "colName";
            this.colName.Visible = true;
            this.colName.VisibleIndex = 1;
            this.colName.Width = 217;
            // 
            // ChaptureGridView
            // 
            this.ChaptureGridView.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gridColumn3,
            this.colTitle1});
            this.ChaptureGridView.GridControl = this.gridControl;
            this.ChaptureGridView.Name = "ChaptureGridView";
            this.ChaptureGridView.OptionsView.ShowColumnHeaders = false;
            this.ChaptureGridView.OptionsView.ShowDetailButtons = false;
            this.ChaptureGridView.OptionsView.ShowFilterPanelMode = DevExpress.XtraGrid.Views.Base.ShowFilterPanelMode.Never;
            this.ChaptureGridView.OptionsView.ShowGroupExpandCollapseButtons = false;
            this.ChaptureGridView.OptionsView.ShowGroupPanel = false;
            this.ChaptureGridView.OptionsView.ShowIndicator = false;
            this.ChaptureGridView.OptionsView.ShowPreviewRowLines = DevExpress.Utils.DefaultBoolean.False;
            this.ChaptureGridView.OptionsView.ShowVerticalLines = DevExpress.Utils.DefaultBoolean.False;
            // 
            // gridColumn3
            // 
            this.gridColumn3.Caption = "gridColumn3";
            this.gridColumn3.ColumnEdit = this.ImageComboBox;
            this.gridColumn3.FieldName = "gridColumn3";
            this.gridColumn3.Name = "gridColumn3";
            this.gridColumn3.OptionsColumn.AllowEdit = false;
            this.gridColumn3.OptionsColumn.AllowFocus = false;
            this.gridColumn3.OptionsColumn.AllowGroup = DevExpress.Utils.DefaultBoolean.True;
            this.gridColumn3.OptionsColumn.AllowIncrementalSearch = false;
            this.gridColumn3.OptionsColumn.AllowMerge = DevExpress.Utils.DefaultBoolean.False;
            this.gridColumn3.OptionsColumn.AllowMove = false;
            this.gridColumn3.OptionsColumn.AllowShowHide = false;
            this.gridColumn3.OptionsColumn.AllowSize = false;
            this.gridColumn3.OptionsColumn.AllowSort = DevExpress.Utils.DefaultBoolean.False;
            this.gridColumn3.OptionsColumn.FixedWidth = true;
            this.gridColumn3.OptionsColumn.ReadOnly = true;
            this.gridColumn3.OptionsColumn.ShowCaption = false;
            this.gridColumn3.OptionsColumn.ShowInCustomizationForm = false;
            this.gridColumn3.OptionsColumn.ShowInExpressionEditor = false;
            this.gridColumn3.UnboundExpression = "11";
            this.gridColumn3.UnboundType = DevExpress.Data.UnboundColumnType.Integer;
            this.gridColumn3.Visible = true;
            this.gridColumn3.VisibleIndex = 0;
            this.gridColumn3.Width = 20;
            // 
            // colTitle1
            // 
            this.colTitle1.FieldName = "Title";
            this.colTitle1.Name = "colTitle1";
            this.colTitle1.Visible = true;
            this.colTitle1.VisibleIndex = 1;
            this.colTitle1.Width = 125;
            // 
            // barManager1
            // 
            this.barManager1.Bars.AddRange(new DevExpress.XtraBars.Bar[] {
            this.bar1,
            this.bar2,
            this.bar3,
            this.bar4,
            this.bar5});
            this.barManager1.Categories.AddRange(new DevExpress.XtraBars.BarManagerCategory[] {
            new DevExpress.XtraBars.BarManagerCategory("Built-in Menus", new System.Guid("a984a9d9-f96f-425a-8857-fe4de6df48c2")),
            new DevExpress.XtraBars.BarManagerCategory("File", new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52")),
            new DevExpress.XtraBars.BarManagerCategory("Edit", new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe")),
            new DevExpress.XtraBars.BarManagerCategory("Standard", new System.Guid("fbaaf85d-943d-4ccd-8517-fc398efe9c7b")),
            new DevExpress.XtraBars.BarManagerCategory("View", new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4")),
            new DevExpress.XtraBars.BarManagerCategory("Window", new System.Guid("faa74de1-bd23-44b9-955d-6ba635fa0f01")),
            new DevExpress.XtraBars.BarManagerCategory("Status", new System.Guid("d3532f9f-c716-4c40-8731-d110e1a41e64")),
            new DevExpress.XtraBars.BarManagerCategory("Layouts", new System.Guid("f2b2eae8-5b98-43eb-81aa-d999b20fd3d3")),
            new DevExpress.XtraBars.BarManagerCategory("PaintStyles", new System.Guid("d0a113b2-425b-47f5-a6b5-0aefb1859507"))});
            this.barManager1.Controller = this.barAndDockingController1;
            this.barManager1.DockControls.Add(this.barDockControl1);
            this.barManager1.DockControls.Add(this.barDockControl2);
            this.barManager1.DockControls.Add(this.barDockControl3);
            this.barManager1.DockControls.Add(this.barDockControl4);
            this.barManager1.DockManager = this.dockManager1;
            this.barManager1.Form = this;
            this.barManager1.Images = this.imageList1;
            this.barManager1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.siFile,
            this.siEdit,
            this.siNew,
            this.iOpen,
            this.iClose,
            this.iProject,
            this.iFile,
            this.iBlankSolution,
            this.iAddNewItem,
            this.iAddExistingItem,
            this.siAddProject,
            this.iNewProject,
            this.iExistingProject,
            this.iSaveAll,
            this.iOpenSolution,
            this.iCloseSolution,
            this.iPageSetup,
            this.iPrint,
            this.iExit,
            this.iUndo,
            this.iRedo,
            this.iCut,
            this.iCopy,
            this.iPaste,
            this.iDelete,
            this.iCycle,
            this.iSelectAll,
            this.iFind,
            this.iNew,
            this.iOpenFile,
            this.iSave,
            this.iSolutionExplorer,
            this.iProperties,
            this.iToolbox,
            this.iClassView,
            this.iTaskList,
            this.iFindResults,
            this.iOutput,
            this.BarMdiChildrenListItem1,
            this.siWindow,
            this.iStatus1,
            this.iStatus2,
            this.iLoadLayout,
            this.iSaveLayout,
            this.siLayouts,
            this.iPaintStyle,
            this.barDockingMenuItem1});
            this.barManager1.MainMenu = this.bar1;
            this.barManager1.MaxItemId = 73;
            this.barManager1.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryImageComboBox1,
            this.repositoryItemComboBox1,
            this.repositoryItemImageComboBox1});
            this.barManager1.StatusBar = this.bar4;
            // 
            // bar1
            // 
            this.bar1.BarName = "MainMenu";
            this.bar1.DockCol = 0;
            this.bar1.DockRow = 0;
            this.bar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.bar1.FloatLocation = new System.Drawing.Point(92, 126);
            this.bar1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.siFile),
            new DevExpress.XtraBars.LinkPersistInfo(this.siEdit),
            new DevExpress.XtraBars.LinkPersistInfo(this.siLayouts),
            new DevExpress.XtraBars.LinkPersistInfo(this.siWindow)});
            this.bar1.OptionsBar.AllowQuickCustomization = false;
            this.bar1.OptionsBar.DrawDragBorder = false;
            this.bar1.OptionsBar.MultiLine = true;
            this.bar1.OptionsBar.UseWholeRow = true;
            this.bar1.Text = "MainMenu";
            // 
            // siFile
            // 
            this.siFile.Caption = "&File";
            this.siFile.CategoryGuid = new System.Guid("a984a9d9-f96f-425a-8857-fe4de6df48c2");
            this.siFile.Id = 0;
            this.siFile.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.siNew),
            new DevExpress.XtraBars.LinkPersistInfo(this.iOpen),
            new DevExpress.XtraBars.LinkPersistInfo(this.iClose),
            new DevExpress.XtraBars.LinkPersistInfo(this.iAddNewItem, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iAddExistingItem),
            new DevExpress.XtraBars.LinkPersistInfo(this.siAddProject),
            new DevExpress.XtraBars.LinkPersistInfo(this.iOpenSolution, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCloseSolution),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSaveAll, true),
            new DevExpress.XtraBars.LinkPersistInfo(DevExpress.XtraBars.BarLinkUserDefines.None, this.iPageSetup, "", true, false, true, 0),
            new DevExpress.XtraBars.LinkPersistInfo(DevExpress.XtraBars.BarLinkUserDefines.None, this.iPrint, "", false, false, true, 0),
            new DevExpress.XtraBars.LinkPersistInfo(this.iExit, true)});
            this.siFile.Name = "siFile";
            // 
            // siNew
            // 
            this.siNew.Caption = "&New";
            this.siNew.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.siNew.Id = 2;
            this.siNew.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iProject),
            new DevExpress.XtraBars.LinkPersistInfo(this.iFile),
            new DevExpress.XtraBars.LinkPersistInfo(this.iBlankSolution)});
            this.siNew.Name = "siNew";
            // 
            // iProject
            // 
            this.iProject.Caption = "&Project...";
            this.iProject.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iProject.Hint = "New Project";
            this.iProject.Id = 5;
            this.iProject.ImageIndex = 0;
            this.iProject.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.N));
            this.iProject.Name = "iProject";
            // 
            // iFile
            // 
            this.iFile.Caption = "&File...";
            this.iFile.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iFile.Hint = "New File";
            this.iFile.Id = 6;
            this.iFile.ImageIndex = 1;
            this.iFile.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N));
            this.iFile.Name = "iFile";
            // 
            // iBlankSolution
            // 
            this.iBlankSolution.Caption = "&Blank Solution...";
            this.iBlankSolution.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iBlankSolution.Hint = "Blank Solution";
            this.iBlankSolution.Id = 7;
            this.iBlankSolution.ImageIndex = 2;
            this.iBlankSolution.Name = "iBlankSolution";
            // 
            // iOpen
            // 
            this.iOpen.Caption = "&Open";
            this.iOpen.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iOpen.Id = 3;
            this.iOpen.Name = "iOpen";
            // 
            // iClose
            // 
            this.iClose.Caption = "&Close";
            this.iClose.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iClose.Id = 4;
            this.iClose.Name = "iClose";
            // 
            // iAddNewItem
            // 
            this.iAddNewItem.Caption = "Add Ne&w Item...";
            this.iAddNewItem.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iAddNewItem.Hint = "Add New Item";
            this.iAddNewItem.Id = 8;
            this.iAddNewItem.ImageIndex = 3;
            this.iAddNewItem.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.A));
            this.iAddNewItem.Name = "iAddNewItem";
            // 
            // iAddExistingItem
            // 
            this.iAddExistingItem.Caption = "Add Existin&g Item...";
            this.iAddExistingItem.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iAddExistingItem.Id = 9;
            this.iAddExistingItem.ImageIndex = 4;
            this.iAddExistingItem.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.B));
            this.iAddExistingItem.Name = "iAddExistingItem";
            // 
            // siAddProject
            // 
            this.siAddProject.Caption = "A&dd Project";
            this.siAddProject.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.siAddProject.Id = 10;
            this.siAddProject.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iNewProject),
            new DevExpress.XtraBars.LinkPersistInfo(this.iExistingProject)});
            this.siAddProject.Name = "siAddProject";
            // 
            // iNewProject
            // 
            this.iNewProject.Caption = "&New Project...";
            this.iNewProject.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iNewProject.Hint = "New Project";
            this.iNewProject.Id = 11;
            this.iNewProject.Name = "iNewProject";
            // 
            // iExistingProject
            // 
            this.iExistingProject.Caption = "&Existing Project...";
            this.iExistingProject.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iExistingProject.Id = 12;
            this.iExistingProject.Name = "iExistingProject";
            // 
            // iOpenSolution
            // 
            this.iOpenSolution.Caption = "Op&en Solution...";
            this.iOpenSolution.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iOpenSolution.Id = 14;
            this.iOpenSolution.ImageIndex = 5;
            this.iOpenSolution.Name = "iOpenSolution";
            // 
            // iCloseSolution
            // 
            this.iCloseSolution.Caption = "Close Solu&tion";
            this.iCloseSolution.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iCloseSolution.Id = 15;
            this.iCloseSolution.ImageIndex = 6;
            this.iCloseSolution.Name = "iCloseSolution";
            // 
            // iSaveAll
            // 
            this.iSaveAll.Caption = "Save A&ll";
            this.iSaveAll.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iSaveAll.Enabled = false;
            this.iSaveAll.Hint = "Save All";
            this.iSaveAll.Id = 13;
            this.iSaveAll.ImageIndex = 7;
            this.iSaveAll.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.S));
            this.iSaveAll.Name = "iSaveAll";
            // 
            // iPageSetup
            // 
            this.iPageSetup.Caption = "Page Set&up...";
            this.iPageSetup.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iPageSetup.Id = 16;
            this.iPageSetup.ImageIndex = 8;
            this.iPageSetup.Name = "iPageSetup";
            // 
            // iPrint
            // 
            this.iPrint.Caption = "&Print...";
            this.iPrint.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iPrint.Id = 17;
            this.iPrint.ImageIndex = 9;
            this.iPrint.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P));
            this.iPrint.Name = "iPrint";
            // 
            // iExit
            // 
            this.iExit.Caption = "E&xit";
            this.iExit.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iExit.Id = 18;
            this.iExit.Name = "iExit";
            this.iExit.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iExit_ItemClick);
            // 
            // siEdit
            // 
            this.siEdit.Caption = "&Edit";
            this.siEdit.CategoryGuid = new System.Guid("a984a9d9-f96f-425a-8857-fe4de6df48c2");
            this.siEdit.Id = 1;
            this.siEdit.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iUndo),
            new DevExpress.XtraBars.LinkPersistInfo(this.iRedo),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCut, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCopy),
            new DevExpress.XtraBars.LinkPersistInfo(this.iPaste),
            new DevExpress.XtraBars.LinkPersistInfo(DevExpress.XtraBars.BarLinkUserDefines.None, this.iCycle, "", false, false, true, 0),
            new DevExpress.XtraBars.LinkPersistInfo(this.iDelete),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSelectAll, true)});
            this.siEdit.Name = "siEdit";
            // 
            // iUndo
            // 
            this.iUndo.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.iUndo.Caption = "&Undo";
            this.iUndo.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iUndo.Enabled = false;
            this.iUndo.Hint = "Undo";
            this.iUndo.Id = 19;
            this.iUndo.ImageIndex = 11;
            this.iUndo.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z));
            this.iUndo.Name = "iUndo";
            this.iUndo.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iUndo_ItemClick);
            // 
            // iRedo
            // 
            this.iRedo.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.iRedo.Caption = "&Redo";
            this.iRedo.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iRedo.Enabled = false;
            this.iRedo.Hint = "Redo";
            this.iRedo.Id = 20;
            this.iRedo.ImageIndex = 12;
            this.iRedo.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y));
            this.iRedo.Name = "iRedo";
            this.iRedo.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iRedo_ItemClick);
            // 
            // iCut
            // 
            this.iCut.Caption = "Cu&t";
            this.iCut.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iCut.Hint = "Cut";
            this.iCut.Id = 21;
            this.iCut.ImageIndex = 13;
            this.iCut.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X));
            this.iCut.Name = "iCut";
            this.iCut.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iCut_ItemClick);
            // 
            // iCopy
            // 
            this.iCopy.Caption = "&Copy";
            this.iCopy.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iCopy.Hint = "Copy";
            this.iCopy.Id = 22;
            this.iCopy.ImageIndex = 14;
            this.iCopy.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C));
            this.iCopy.Name = "iCopy";
            this.iCopy.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iCopy_ItemClick);
            // 
            // iPaste
            // 
            this.iPaste.Caption = "&Paste";
            this.iPaste.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iPaste.Enabled = false;
            this.iPaste.Hint = "Paste";
            this.iPaste.Id = 23;
            this.iPaste.ImageIndex = 15;
            this.iPaste.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V));
            this.iPaste.Name = "iPaste";
            this.iPaste.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iPaste_ItemClick);
            // 
            // iCycle
            // 
            this.iCycle.Caption = "C&ycle Clipboard Ring";
            this.iCycle.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iCycle.Id = 25;
            this.iCycle.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.V));
            this.iCycle.Name = "iCycle";
            // 
            // iDelete
            // 
            this.iDelete.Caption = "&Delete";
            this.iDelete.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iDelete.Enabled = false;
            this.iDelete.Id = 24;
            this.iDelete.ImageIndex = 19;
            this.iDelete.ItemShortcut = new DevExpress.XtraBars.BarShortcut(System.Windows.Forms.Keys.Delete);
            this.iDelete.Name = "iDelete";
            // 
            // iSelectAll
            // 
            this.iSelectAll.Caption = "Select &All";
            this.iSelectAll.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iSelectAll.Id = 26;
            this.iSelectAll.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A));
            this.iSelectAll.Name = "iSelectAll";
            this.iSelectAll.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iSelectAll_ItemClick);
            // 
            // siLayouts
            // 
            this.siLayouts.Caption = "&Layouts";
            this.siLayouts.CategoryGuid = new System.Guid("a984a9d9-f96f-425a-8857-fe4de6df48c2");
            this.siLayouts.Id = 49;
            this.siLayouts.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iLoadLayout),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSaveLayout)});
            this.siLayouts.Name = "siLayouts";
            // 
            // iLoadLayout
            // 
            this.iLoadLayout.Caption = "&Load Layout...";
            this.iLoadLayout.CategoryGuid = new System.Guid("f2b2eae8-5b98-43eb-81aa-d999b20fd3d3");
            this.iLoadLayout.Hint = "Load Layout";
            this.iLoadLayout.Id = 47;
            this.iLoadLayout.ImageIndex = 35;
            this.iLoadLayout.Name = "iLoadLayout";
            this.iLoadLayout.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iLoadLayout_ItemClick);
            // 
            // iSaveLayout
            // 
            this.iSaveLayout.Caption = "&Save Layout...";
            this.iSaveLayout.CategoryGuid = new System.Guid("f2b2eae8-5b98-43eb-81aa-d999b20fd3d3");
            this.iSaveLayout.Hint = "Save Layout";
            this.iSaveLayout.Id = 48;
            this.iSaveLayout.ImageIndex = 34;
            this.iSaveLayout.Name = "iSaveLayout";
            this.iSaveLayout.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iSaveLayout_ItemClick);
            // 
            // siWindow
            // 
            this.siWindow.Caption = "&Window";
            this.siWindow.CategoryGuid = new System.Guid("a984a9d9-f96f-425a-8857-fe4de6df48c2");
            this.siWindow.Id = 45;
            this.siWindow.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iPaintStyle),
            new DevExpress.XtraBars.LinkPersistInfo(this.barDockingMenuItem1)});
            this.siWindow.Name = "siWindow";
            // 
            // iPaintStyle
            // 
            this.iPaintStyle.Caption = "Paint Style";
            this.iPaintStyle.CategoryGuid = new System.Guid("d0a113b2-425b-47f5-a6b5-0aefb1859507");
            this.iPaintStyle.Id = 60;
            this.iPaintStyle.ItemAppearance.Normal.Font = new System.Drawing.Font("Arial", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Italic | System.Drawing.FontStyle.Underline))));
            this.iPaintStyle.ItemAppearance.Normal.Options.UseFont = true;
            this.iPaintStyle.Name = "iPaintStyle";
            this.iPaintStyle.PaintStyle = DevExpress.XtraBars.BarItemPaintStyle.CaptionGlyph;
            // 
            // barDockingMenuItem1
            // 
            this.barDockingMenuItem1.Caption = "Window";
            this.barDockingMenuItem1.Id = 72;
            this.barDockingMenuItem1.Name = "barDockingMenuItem1";
            // 
            // bar2
            // 
            this.bar2.BarName = "Standard";
            this.bar2.DockCol = 0;
            this.bar2.DockRow = 1;
            this.bar2.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.bar2.FloatLocation = new System.Drawing.Point(38, 139);
            this.bar2.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iNew),
            new DevExpress.XtraBars.LinkPersistInfo(this.iAddNewItem),
            new DevExpress.XtraBars.LinkPersistInfo(this.iOpenFile),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSave),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSaveAll),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCut, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCopy),
            new DevExpress.XtraBars.LinkPersistInfo(this.iPaste),
            new DevExpress.XtraBars.LinkPersistInfo(this.iUndo, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iRedo)});
            this.bar2.Text = "Standard";
            // 
            // iNew
            // 
            this.iNew.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.iNew.Caption = "New Project";
            this.iNew.CategoryGuid = new System.Guid("fbaaf85d-943d-4ccd-8517-fc398efe9c7b");
            this.iNew.DropDownControl = this.popupMenu1;
            this.iNew.Hint = "New Project";
            this.iNew.Id = 31;
            this.iNew.ImageIndex = 10;
            this.iNew.Name = "iNew";
            // 
            // popupMenu1
            // 
            this.popupMenu1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iProject),
            new DevExpress.XtraBars.LinkPersistInfo(this.iFile),
            new DevExpress.XtraBars.LinkPersistInfo(this.iBlankSolution)});
            this.popupMenu1.Manager = this.barManager1;
            this.popupMenu1.Name = "popupMenu1";
            // 
            // iOpenFile
            // 
            this.iOpenFile.Caption = "Open File";
            this.iOpenFile.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iOpenFile.Hint = "Open File";
            this.iOpenFile.Id = 32;
            this.iOpenFile.ImageIndex = 20;
            this.iOpenFile.Name = "iOpenFile";
            // 
            // iSave
            // 
            this.iSave.Caption = "Save";
            this.iSave.CategoryGuid = new System.Guid("ec880574-4d2a-4f26-8779-903acfad8a52");
            this.iSave.Enabled = false;
            this.iSave.Hint = "Save";
            this.iSave.Id = 33;
            this.iSave.ImageIndex = 21;
            this.iSave.Name = "iSave";
            // 
            // bar3
            // 
            this.bar3.BarName = "View";
            this.bar3.DockCol = 2;
            this.bar3.DockRow = 1;
            this.bar3.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.bar3.FloatLocation = new System.Drawing.Point(36, 181);
            this.bar3.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iSolutionExplorer),
            new DevExpress.XtraBars.LinkPersistInfo(this.iProperties),
            new DevExpress.XtraBars.LinkPersistInfo(this.iToolbox),
            new DevExpress.XtraBars.LinkPersistInfo(this.iClassView),
            new DevExpress.XtraBars.LinkPersistInfo(this.iTaskList, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iFindResults),
            new DevExpress.XtraBars.LinkPersistInfo(this.iOutput)});
            this.bar3.Offset = 342;
            this.bar3.Text = "View";
            // 
            // iSolutionExplorer
            // 
            this.iSolutionExplorer.Caption = "Solution Ex&plorer";
            this.iSolutionExplorer.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iSolutionExplorer.Hint = "Solution Explorer";
            this.iSolutionExplorer.Id = 37;
            this.iSolutionExplorer.ImageIndex = 23;
            this.iSolutionExplorer.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.L));
            this.iSolutionExplorer.Name = "iSolutionExplorer";
            this.iSolutionExplorer.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iSolutionExplorer_ItemClick);
            // 
            // iProperties
            // 
            this.iProperties.Caption = "Properties &Window";
            this.iProperties.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iProperties.Hint = "Properties Window";
            this.iProperties.Id = 38;
            this.iProperties.ImageIndex = 24;
            this.iProperties.ItemShortcut = new DevExpress.XtraBars.BarShortcut(System.Windows.Forms.Keys.F4);
            this.iProperties.Name = "iProperties";
            this.iProperties.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iProperties_ItemClick);
            // 
            // iToolbox
            // 
            this.iToolbox.Caption = "Toolbo&x";
            this.iToolbox.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iToolbox.Hint = "Toolbox";
            this.iToolbox.Id = 39;
            this.iToolbox.ImageIndex = 25;
            this.iToolbox.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.X));
            this.iToolbox.Name = "iToolbox";
            this.iToolbox.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iToolbox_ItemClick);
            // 
            // iClassView
            // 
            this.iClassView.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.iClassView.Caption = "Cl&ass View";
            this.iClassView.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iClassView.Hint = "Class View";
            this.iClassView.Id = 40;
            this.iClassView.ImageIndex = 26;
            this.iClassView.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
                | System.Windows.Forms.Keys.C));
            this.iClassView.Name = "iClassView";
            // 
            // iTaskList
            // 
            this.iTaskList.Caption = "Task List";
            this.iTaskList.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iTaskList.Hint = "Task List";
            this.iTaskList.Id = 68;
            this.iTaskList.ImageIndex = 27;
            this.iTaskList.Name = "iTaskList";
            this.iTaskList.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iTaskList_ItemClick);
            // 
            // iFindResults
            // 
            this.iFindResults.Caption = "Find Results";
            this.iFindResults.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iFindResults.Hint = "Find Results";
            this.iFindResults.Id = 69;
            this.iFindResults.ImageIndex = 28;
            this.iFindResults.Name = "iFindResults";
            this.iFindResults.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iFindResults_ItemClick);
            // 
            // iOutput
            // 
            this.iOutput.Caption = "Output";
            this.iOutput.CategoryGuid = new System.Guid("0cb4cc3e-4798-4d61-9457-672bdc2a90d4");
            this.iOutput.Hint = "Output";
            this.iOutput.Id = 70;
            this.iOutput.ImageIndex = 29;
            this.iOutput.Name = "iOutput";
            this.iOutput.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.iOutput_ItemClick);
            // 
            // bar4
            // 
            this.bar4.BarName = "StatusBar";
            this.bar4.CanDockStyle = DevExpress.XtraBars.BarCanDockStyle.Bottom;
            this.bar4.DockCol = 0;
            this.bar4.DockRow = 0;
            this.bar4.DockStyle = DevExpress.XtraBars.BarDockStyle.Bottom;
            this.bar4.FloatLocation = new System.Drawing.Point(25, 282);
            this.bar4.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iStatus1),
            new DevExpress.XtraBars.LinkPersistInfo(this.iStatus2)});
            this.bar4.OptionsBar.AllowQuickCustomization = false;
            this.bar4.OptionsBar.DrawDragBorder = false;
            this.bar4.OptionsBar.DrawSizeGrip = true;
            this.bar4.OptionsBar.RotateWhenVertical = false;
            this.bar4.OptionsBar.UseWholeRow = true;
            this.bar4.Text = "StatusBar";
            // 
            // iStatus1
            // 
            this.iStatus1.AutoSize = DevExpress.XtraBars.BarStaticItemSize.Spring;
            this.iStatus1.Caption = "Ready";
            this.iStatus1.CategoryGuid = new System.Guid("d3532f9f-c716-4c40-8731-d110e1a41e64");
            this.iStatus1.Id = 50;
            this.iStatus1.Name = "iStatus1";
            this.iStatus1.TextAlignment = System.Drawing.StringAlignment.Near;
            this.iStatus1.Width = 695;
            // 
            // iStatus2
            // 
            this.iStatus2.CategoryGuid = new System.Guid("d3532f9f-c716-4c40-8731-d110e1a41e64");
            this.iStatus2.Id = 51;
            this.iStatus2.LeftIndent = 2;
            this.iStatus2.Name = "iStatus2";
            this.iStatus2.TextAlignment = System.Drawing.StringAlignment.Near;
            // 
            // bar5
            // 
            this.bar5.BarName = "Layouts";
            this.bar5.DockCol = 1;
            this.bar5.DockRow = 1;
            this.bar5.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.bar5.FloatLocation = new System.Drawing.Point(159, 118);
            this.bar5.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iLoadLayout),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSaveLayout)});
            this.bar5.Offset = 309;
            this.bar5.Text = "Layouts";
            // 
            // barAndDockingController1
            // 
            this.barAndDockingController1.PaintStyleName = "Skin";
            this.barAndDockingController1.PropertiesBar.AllowLinkLighting = false;
            // 
            // barDockControl1
            // 
            this.barDockControl1.CausesValidation = false;
            this.barDockControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.barDockControl1.Location = new System.Drawing.Point(0, 0);
            this.barDockControl1.Size = new System.Drawing.Size(768, 50);
            // 
            // barDockControl2
            // 
            this.barDockControl2.CausesValidation = false;
            this.barDockControl2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.barDockControl2.Location = new System.Drawing.Point(0, 610);
            this.barDockControl2.Size = new System.Drawing.Size(768, 26);
            // 
            // barDockControl3
            // 
            this.barDockControl3.CausesValidation = false;
            this.barDockControl3.Dock = System.Windows.Forms.DockStyle.Left;
            this.barDockControl3.Location = new System.Drawing.Point(0, 50);
            this.barDockControl3.Size = new System.Drawing.Size(0, 560);
            // 
            // barDockControl4
            // 
            this.barDockControl4.CausesValidation = false;
            this.barDockControl4.Dock = System.Windows.Forms.DockStyle.Right;
            this.barDockControl4.Location = new System.Drawing.Point(768, 50);
            this.barDockControl4.Size = new System.Drawing.Size(0, 560);
            // 
            // dockManager1
            // 
            this.dockManager1.Controller = this.barAndDockingController1;
            this.dockManager1.Form = this;
            this.dockManager1.Images = this.imageList1;
            this.dockManager1.MenuManager = this.barManager1;
            this.dockManager1.RootPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.panelContainer2,
            this.panelContainer1});
            this.dockManager1.TopZIndexControls.AddRange(new string[] {
            "DevExpress.XtraBars.BarDockControl",
            "System.Windows.Forms.StatusBar"});
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList1.Images.SetKeyName(0, "NewProject_16x16.png");
            this.imageList1.Images.SetKeyName(1, "File_16x16.png");
            this.imageList1.Images.SetKeyName(2, "BlankSolution_16x16.png");
            this.imageList1.Images.SetKeyName(3, "AddNewItem_16x16.png");
            this.imageList1.Images.SetKeyName(4, "AddExistingItem_16x16.png");
            this.imageList1.Images.SetKeyName(5, "OpenSolution_16x16.png");
            this.imageList1.Images.SetKeyName(6, "CloseSolution_16x16.png");
            this.imageList1.Images.SetKeyName(7, "SaveAll_16x16.png");
            this.imageList1.Images.SetKeyName(8, "PrintSetup.bmp");
            this.imageList1.Images.SetKeyName(9, "Print.bmp");
            this.imageList1.Images.SetKeyName(10, "NewProject_16x16.png");
            this.imageList1.Images.SetKeyName(11, "Undo_16x16.png");
            this.imageList1.Images.SetKeyName(12, "Redo_16x16.png");
            this.imageList1.Images.SetKeyName(13, "Cut_16x16.png");
            this.imageList1.Images.SetKeyName(14, "Copy_16x16.png");
            this.imageList1.Images.SetKeyName(15, "Paste_16x16.png");
            this.imageList1.Images.SetKeyName(16, "Find.bmp");
            this.imageList1.Images.SetKeyName(17, "");
            this.imageList1.Images.SetKeyName(18, "FindInFiles_16x16.png");
            this.imageList1.Images.SetKeyName(19, "");
            this.imageList1.Images.SetKeyName(20, "OpenFile_16x16.png");
            this.imageList1.Images.SetKeyName(21, "Save_16x16.png");
            this.imageList1.Images.SetKeyName(22, "StartDebugging_16x16.png");
            this.imageList1.Images.SetKeyName(23, "Solution Explorer.png");
            this.imageList1.Images.SetKeyName(24, "PropertiesWindow_16x16.png");
            this.imageList1.Images.SetKeyName(25, "Toolbox_16x16.png");
            this.imageList1.Images.SetKeyName(26, "ClassView_16x16.png");
            this.imageList1.Images.SetKeyName(27, "TaskList_16x16.png");
            this.imageList1.Images.SetKeyName(28, "FindInFiles_16x16.png");
            this.imageList1.Images.SetKeyName(29, "Output_16x16.png");
            this.imageList1.Images.SetKeyName(30, "");
            this.imageList1.Images.SetKeyName(31, "");
            this.imageList1.Images.SetKeyName(32, "");
            this.imageList1.Images.SetKeyName(33, "");
            this.imageList1.Images.SetKeyName(34, "SaveLayout_16x16.png");
            this.imageList1.Images.SetKeyName(35, "LoadLayout_16x16.png");
            // 
            // panelContainer2
            // 
            this.panelContainer2.ActiveChild = this.dockPanelShot;
            this.panelContainer2.Controls.Add(this.dockPanelShot);
            this.panelContainer2.Controls.Add(this.dockPanelTask);
            this.panelContainer2.Controls.Add(this.dockPanelOutPut);
            this.panelContainer2.Dock = DevExpress.XtraBars.Docking.DockingStyle.Bottom;
            this.panelContainer2.FloatSize = new System.Drawing.Size(304, 139);
            this.panelContainer2.ID = new System.Guid("e52dd830-76be-4297-b8d5-8dd03213d2b7");
            this.panelContainer2.Image = ((System.Drawing.Image)(resources.GetObject("panelContainer2.Image")));
            this.panelContainer2.Location = new System.Drawing.Point(0, 410);
            this.panelContainer2.Name = "panelContainer2";
            this.panelContainer2.OriginalSize = new System.Drawing.Size(200, 200);
            this.panelContainer2.Size = new System.Drawing.Size(768, 200);
            this.panelContainer2.Tabbed = true;
            this.panelContainer2.Text = "panelContainer2";
            // 
            // dockPanelShot
            // 
            this.dockPanelShot.Controls.Add(this.dockPanel3_Container);
            this.dockPanelShot.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelShot.FloatSize = new System.Drawing.Size(304, 139);
            this.dockPanelShot.Header = null;
            this.dockPanelShot.ID = new System.Guid("7351d5e2-6da1-45c0-a5b6-13e4e7d7a56e");
            this.dockPanelShot.Image = ((System.Drawing.Image)(resources.GetObject("dockPanelShot.Image")));
            this.dockPanelShot.ImageIndex = 27;
            this.dockPanelShot.Location = new System.Drawing.Point(3, 24);
            this.dockPanelShot.Name = "dockPanelShot";
            this.dockPanelShot.OriginalSize = new System.Drawing.Size(736, 148);
            this.dockPanelShot.Size = new System.Drawing.Size(762, 148);
            this.dockPanelShot.TabText = "لیست شات ها";
            this.dockPanelShot.Text = "لیست شات ها";
            // 
            // dockPanel3_Container
            // 
            this.dockPanel3_Container.Controls.Add(this.vGridControlChapters);
            this.dockPanel3_Container.Location = new System.Drawing.Point(0, 0);
            this.dockPanel3_Container.Name = "dockPanel3_Container";
            this.dockPanel3_Container.Size = new System.Drawing.Size(762, 148);
            this.dockPanel3_Container.TabIndex = 0;
            // 
            // vGridControlChapters
            // 
            this.vGridControlChapters.AllowDrop = true;
            this.vGridControlChapters.Appearance.FocusedRecord.BackColor = System.Drawing.Color.Lavender;
            this.vGridControlChapters.Appearance.FocusedRecord.BorderColor = System.Drawing.Color.RoyalBlue;
            this.vGridControlChapters.Appearance.FocusedRecord.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Italic);
            this.vGridControlChapters.Appearance.FocusedRecord.GradientMode = System.Drawing.Drawing2D.LinearGradientMode.ForwardDiagonal;
            this.vGridControlChapters.Appearance.FocusedRecord.Options.UseBackColor = true;
            this.vGridControlChapters.Appearance.FocusedRecord.Options.UseBorderColor = true;
            this.vGridControlChapters.Appearance.FocusedRecord.Options.UseFont = true;
            this.vGridControlChapters.Appearance.RecordValue.Options.UseTextOptions = true;
            this.vGridControlChapters.Appearance.RecordValue.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.vGridControlChapters.Appearance.RecordValue.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Center;
            this.vGridControlChapters.Appearance.RowHeaderPanel.Options.UseTextOptions = true;
            this.vGridControlChapters.Appearance.RowHeaderPanel.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.vGridControlChapters.Appearance.RowHeaderPanel.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Center;
            this.vGridControlChapters.DataSource = this.ChapterbindingSource;
            this.vGridControlChapters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.vGridControlChapters.Location = new System.Drawing.Point(0, 0);
            this.vGridControlChapters.LookAndFeel.SkinName = "Office 2010 Blue";
            this.vGridControlChapters.Name = "vGridControlChapters";
            this.vGridControlChapters.OptionsBehavior.AutoFocusNewRecord = true;
            this.vGridControlChapters.OptionsBehavior.DragRowHeaders = true;
            this.vGridControlChapters.OptionsBehavior.UseEnterAsTab = true;
            this.vGridControlChapters.OptionsMenu.EnableContextMenu = true;
            this.vGridControlChapters.OptionsView.ShowEmptyRowImage = true;
            this.vGridControlChapters.OptionsView.ShowRows = false;
            this.vGridControlChapters.RecordWidth = 130;
            this.vGridControlChapters.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.DesrepositoryItemMemoExEdit1,
            this.ImagerepositoryItemPictureEdit,
            this.TitlerepositoryItemTextEdit,
            this.LenrepositoryItemTextEdit,
            this.GrouprepositoryItemMRUEdit,
            this.SelectedCheckEdit,
            this.PositionrepositoryItemTextEdit});
            this.vGridControlChapters.RowHeaderWidth = 141;
            this.vGridControlChapters.Rows.AddRange(new DevExpress.XtraVerticalGrid.Rows.BaseRow[] {
            this.rowPosition,
            this.rowThumbnailSource,
            this.rowThumbnailImage,
            this.LenRow,
            this.rowTitlerGroup,
            this.Timerow,
            this.rowDescription,
            this.ChapterMSelected});
            this.vGridControlChapters.Size = new System.Drawing.Size(762, 148);
            this.vGridControlChapters.TabIndex = 16;
            // 
            // ChapterbindingSource
            // 
            this.ChapterbindingSource.DataSource = typeof(Player.Chapter);
            // 
            // DesrepositoryItemMemoExEdit1
            // 
            this.DesrepositoryItemMemoExEdit1.AutoHeight = false;
            this.DesrepositoryItemMemoExEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.DesrepositoryItemMemoExEdit1.Name = "DesrepositoryItemMemoExEdit1";
            // 
            // ImagerepositoryItemPictureEdit
            // 
            this.ImagerepositoryItemPictureEdit.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Office2003;
            this.ImagerepositoryItemPictureEdit.Name = "ImagerepositoryItemPictureEdit";
            this.ImagerepositoryItemPictureEdit.PictureInterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            this.ImagerepositoryItemPictureEdit.PictureStoreMode = DevExpress.XtraEditors.Controls.PictureStoreMode.Image;
            this.ImagerepositoryItemPictureEdit.ShowZoomSubMenu = DevExpress.Utils.DefaultBoolean.True;
            this.ImagerepositoryItemPictureEdit.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Stretch;
            this.ImagerepositoryItemPictureEdit.UseParentBackground = true;
            this.ImagerepositoryItemPictureEdit.DoubleClick += new System.EventHandler(this.repositoryItemPictureEdit1_DoubleClick_1);
            // 
            // TitlerepositoryItemTextEdit
            // 
            this.TitlerepositoryItemTextEdit.AutoHeight = false;
            this.TitlerepositoryItemTextEdit.Name = "TitlerepositoryItemTextEdit";
            this.TitlerepositoryItemTextEdit.NullText = "انتهای فریم مشخص نشده است";
            this.TitlerepositoryItemTextEdit.NullValuePrompt = "انتهای فریم مشخص نشده است";
            this.TitlerepositoryItemTextEdit.NullValuePromptShowForEmptyValue = true;
            // 
            // LenrepositoryItemTextEdit
            // 
            this.LenrepositoryItemTextEdit.Appearance.Options.UseImage = true;
            this.LenrepositoryItemTextEdit.Appearance.Options.UseTextOptions = true;
            this.LenrepositoryItemTextEdit.Appearance.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.LenrepositoryItemTextEdit.Appearance.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Bottom;
            this.LenrepositoryItemTextEdit.Name = "LenrepositoryItemTextEdit";
            // 
            // GrouprepositoryItemMRUEdit
            // 
            this.GrouprepositoryItemMRUEdit.AutoHeight = false;
            this.GrouprepositoryItemMRUEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.GrouprepositoryItemMRUEdit.CaseSensitiveSearch = true;
            this.GrouprepositoryItemMRUEdit.Name = "GrouprepositoryItemMRUEdit";
            this.GrouprepositoryItemMRUEdit.Sorted = true;
            // 
            // SelectedCheckEdit
            // 
            this.SelectedCheckEdit.AutoHeight = false;
            this.SelectedCheckEdit.Name = "SelectedCheckEdit";
            // 
            // PositionrepositoryItemTextEdit
            // 
            this.PositionrepositoryItemTextEdit.AutoHeight = false;
            this.PositionrepositoryItemTextEdit.Mask.EditMask = "(0?\\d|1\\d|2[0-3]):[0-5]\\d:[0-5]\\d";
            this.PositionrepositoryItemTextEdit.Mask.MaskType = DevExpress.XtraEditors.Mask.MaskType.RegEx;
            this.PositionrepositoryItemTextEdit.Name = "PositionrepositoryItemTextEdit";
            // 
            // rowPosition
            // 
            this.rowPosition.Name = "rowPosition";
            this.rowPosition.Properties.Caption = "Position";
            this.rowPosition.Properties.FieldName = "StartPosition";
            this.rowPosition.Visible = false;
            // 
            // rowThumbnailSource
            // 
            this.rowThumbnailSource.Name = "rowThumbnailSource";
            this.rowThumbnailSource.Properties.Caption = "Thumbnail Source";
            this.rowThumbnailSource.Properties.FieldName = "ThumbnailSource";
            this.rowThumbnailSource.Visible = false;
            // 
            // rowThumbnailImage
            // 
            this.rowThumbnailImage.Height = 84;
            this.rowThumbnailImage.Name = "rowThumbnailImage";
            this.rowThumbnailImage.Properties.Caption = "Thumbnail Image";
            this.rowThumbnailImage.Properties.FieldName = "ThumbnailImage";
            this.rowThumbnailImage.Properties.ReadOnly = true;
            this.rowThumbnailImage.Properties.RowEdit = this.ImagerepositoryItemPictureEdit;
            this.rowThumbnailImage.Properties.UnboundExpression = "[Lengh]";
            // 
            // LenRow
            // 
            this.LenRow.Height = 14;
            this.LenRow.Name = "LenRow";
            this.LenRow.Properties.FieldName = "LenghText";
            this.LenRow.Properties.ReadOnly = true;
            this.LenRow.Properties.RowEdit = this.LenrepositoryItemTextEdit;
            // 
            // rowTitlerGroup
            // 
            this.rowTitlerGroup.Name = "rowTitlerGroup";
            // 
            // Timerow
            // 
            this.Timerow.Name = "Timerow";
            // 
            // rowDescription
            // 
            this.rowDescription.Name = "rowDescription";
            this.rowDescription.Properties.Caption = "Description";
            this.rowDescription.Properties.FieldName = "Description";
            this.rowDescription.Properties.RowEdit = this.DesrepositoryItemMemoExEdit1;
            // 
            // ChapterMSelected
            // 
            this.ChapterMSelected.Name = "ChapterMSelected";
            this.ChapterMSelected.Properties.FieldName = "Selected";
            this.ChapterMSelected.Properties.RowEdit = this.SelectedCheckEdit;
            this.ChapterMSelected.Visible = false;
            // 
            // dockPanelTask
            // 
            this.dockPanelTask.Controls.Add(this.dockPanel4_Container);
            this.dockPanelTask.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelTask.FloatSize = new System.Drawing.Size(304, 139);
            this.dockPanelTask.FloatVertical = true;
            this.dockPanelTask.Footer = null;
            this.dockPanelTask.Header = null;
            this.dockPanelTask.ID = new System.Guid("47b3ea95-3900-46d6-b24c-5f3a779b1ae7");
            this.dockPanelTask.Image = ((System.Drawing.Image)(resources.GetObject("dockPanelTask.Image")));
            this.dockPanelTask.ImageIndex = 28;
            this.dockPanelTask.Location = new System.Drawing.Point(3, 24);
            this.dockPanelTask.Name = "dockPanelTask";
            this.dockPanelTask.OriginalSize = new System.Drawing.Size(736, 148);
            this.dockPanelTask.Size = new System.Drawing.Size(762, 148);
            this.dockPanelTask.Text = "لیست کارها";
            // 
            // dockPanel4_Container
            // 
            this.dockPanel4_Container.Location = new System.Drawing.Point(0, 0);
            this.dockPanel4_Container.Name = "dockPanel4_Container";
            this.dockPanel4_Container.Size = new System.Drawing.Size(762, 148);
            this.dockPanel4_Container.TabIndex = 0;
            // 
            // dockPanelOutPut
            // 
            this.dockPanelOutPut.Controls.Add(this.dockPanel5_Container);
            this.dockPanelOutPut.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelOutPut.FloatSize = new System.Drawing.Size(304, 139);
            this.dockPanelOutPut.FloatVertical = true;
            this.dockPanelOutPut.Footer = null;
            this.dockPanelOutPut.Header = null;
            this.dockPanelOutPut.ID = new System.Guid("dbdb0ba9-5443-476b-93ad-ec35678d61ef");
            this.dockPanelOutPut.Image = ((System.Drawing.Image)(resources.GetObject("dockPanelOutPut.Image")));
            this.dockPanelOutPut.ImageIndex = 29;
            this.dockPanelOutPut.Location = new System.Drawing.Point(3, 24);
            this.dockPanelOutPut.Name = "dockPanelOutPut";
            this.dockPanelOutPut.OriginalSize = new System.Drawing.Size(736, 148);
            this.dockPanelOutPut.Size = new System.Drawing.Size(762, 148);
            this.dockPanelOutPut.Text = "خروجی";
            // 
            // dockPanel5_Container
            // 
            this.dockPanel5_Container.Location = new System.Drawing.Point(0, 0);
            this.dockPanel5_Container.Name = "dockPanel5_Container";
            this.dockPanel5_Container.Size = new System.Drawing.Size(762, 148);
            this.dockPanel5_Container.TabIndex = 0;
            // 
            // panelContainer1
            // 
            this.panelContainer1.ActiveChild = this.dockPanelSolution;
            this.panelContainer1.Controls.Add(this.dockPanelSolution);
            this.panelContainer1.Controls.Add(this.dockPanelFind);
            this.panelContainer1.Dock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.panelContainer1.FloatSize = new System.Drawing.Size(253, 266);
            this.panelContainer1.Footer = null;
            this.panelContainer1.Header = null;
            this.panelContainer1.ID = new System.Guid("6c74c2c4-9754-4cea-b108-63e9e7e6c9a0");
            this.panelContainer1.Image = ((System.Drawing.Image)(resources.GetObject("panelContainer1.Image")));
            this.panelContainer1.Location = new System.Drawing.Point(520, 50);
            this.panelContainer1.Name = "panelContainer1";
            this.panelContainer1.OriginalSize = new System.Drawing.Size(248, 200);
            this.panelContainer1.Size = new System.Drawing.Size(248, 360);
            this.panelContainer1.Tabbed = true;
            this.panelContainer1.Text = "panelContainer1";
            // 
            // dockPanelSolution
            // 
            this.dockPanelSolution.Controls.Add(this.dockPanel1_Container);
            this.dockPanelSolution.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelSolution.FloatSize = new System.Drawing.Size(253, 266);
            this.dockPanelSolution.Footer = null;
            this.dockPanelSolution.Header = null;
            this.dockPanelSolution.ID = new System.Guid("70a62a0b-1c55-4e72-bef0-661a97c3e934");
            this.dockPanelSolution.Image = ((System.Drawing.Image)(resources.GetObject("dockPanelSolution.Image")));
            this.dockPanelSolution.ImageIndex = 23;
            this.dockPanelSolution.Location = new System.Drawing.Point(3, 24);
            this.dockPanelSolution.Name = "dockPanelSolution";
            this.dockPanelSolution.OriginalSize = new System.Drawing.Size(194, 308);
            this.dockPanelSolution.Size = new System.Drawing.Size(242, 308);
            this.dockPanelSolution.TabText = "مدیریت پروژه";
            this.dockPanelSolution.Text = "مدیریت پروژه";
            // 
            // dockPanel1_Container
            // 
            this.dockPanel1_Container.Controls.Add(this.gridControl);
            this.dockPanel1_Container.Location = new System.Drawing.Point(0, 0);
            this.dockPanel1_Container.Name = "dockPanel1_Container";
            this.dockPanel1_Container.Size = new System.Drawing.Size(242, 308);
            this.dockPanel1_Container.TabIndex = 0;
            // 
            // dockPanelFind
            // 
            this.dockPanelFind.Controls.Add(this.dockPanel2_Container);
            this.dockPanelFind.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelFind.FloatSize = new System.Drawing.Size(253, 266);
            this.dockPanelFind.Footer = null;
            this.dockPanelFind.Header = null;
            this.dockPanelFind.ID = new System.Guid("96144626-be47-440b-ae5f-2c5507db5076");
            this.dockPanelFind.ImageIndex = 28;
            this.dockPanelFind.Location = new System.Drawing.Point(3, 24);
            this.dockPanelFind.Name = "dockPanelFind";
            this.dockPanelFind.OriginalSize = new System.Drawing.Size(194, 308);
            this.dockPanelFind.Size = new System.Drawing.Size(242, 308);
            this.dockPanelFind.Text = "جستجو در شات ها";
            // 
            // dockPanel2_Container
            // 
            this.dockPanel2_Container.Controls.Add(this.gridControl2);
            this.dockPanel2_Container.Location = new System.Drawing.Point(0, 0);
            this.dockPanel2_Container.Name = "dockPanel2_Container";
            this.dockPanel2_Container.Size = new System.Drawing.Size(242, 308);
            this.dockPanel2_Container.TabIndex = 0;
            // 
            // gridControl2
            // 
            this.gridControl2.DataSource = this.AllchapterBindingSource;
            this.gridControl2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gridControl2.Location = new System.Drawing.Point(0, 0);
            this.gridControl2.MainView = this.advBandedGridView1;
            this.gridControl2.Name = "gridControl2";
            this.gridControl2.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemPictureEdit2,
            this.repositoryItemMemoEdit1});
            this.gridControl2.Size = new System.Drawing.Size(242, 308);
            this.gridControl2.TabIndex = 1;
            this.gridControl2.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.advBandedGridView1});
            // 
            // AllchapterBindingSource
            // 
            this.AllchapterBindingSource.DataSource = typeof(Player.Chapter);
            // 
            // advBandedGridView1
            // 
            this.advBandedGridView1.Bands.AddRange(new DevExpress.XtraGrid.Views.BandedGrid.GridBand[] {
            this.gridBand1,
            this.gridBand2});
            this.advBandedGridView1.Columns.AddRange(new DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn[] {
            this.colThumbnailImage,
            this.colTitle2,
            this.colDescription,
            this.Colgroup,
            this.colFullInfoHtml});
            this.advBandedGridView1.GridControl = this.gridControl2;
            this.advBandedGridView1.GroupFormat = " [#image]{1} {2}";
            this.advBandedGridView1.GroupPanelText = "برای گروه بندی فیلد مورد نطر به این محل اضافه کنید";
            this.advBandedGridView1.Name = "advBandedGridView1";
            this.advBandedGridView1.OptionsBehavior.Editable = false;
            this.advBandedGridView1.OptionsCustomization.AllowChangeBandParent = true;
            this.advBandedGridView1.OptionsCustomization.AllowChangeColumnParent = true;
            this.advBandedGridView1.OptionsFilter.ShowAllTableValuesInFilterPopup = true;
            this.advBandedGridView1.OptionsFilter.UseNewCustomFilterDialog = true;
            this.advBandedGridView1.OptionsFind.AlwaysVisible = true;
            this.advBandedGridView1.OptionsFind.SearchInPreview = true;
            this.advBandedGridView1.OptionsHint.ShowBandHeaderHints = false;
            this.advBandedGridView1.OptionsHint.ShowCellHints = false;
            this.advBandedGridView1.OptionsHint.ShowColumnHeaderHints = false;
            this.advBandedGridView1.OptionsHint.ShowFooterHints = false;
            this.advBandedGridView1.OptionsNavigation.AutoFocusNewRow = true;
            this.advBandedGridView1.OptionsView.ColumnAutoWidth = true;
            this.advBandedGridView1.OptionsView.ShowAutoFilterRow = true;
            this.advBandedGridView1.OptionsView.ShowBands = false;
            this.advBandedGridView1.OptionsView.ShowChildrenInGroupPanel = true;
            this.advBandedGridView1.OptionsView.ShowDetailButtons = false;
            this.advBandedGridView1.OptionsView.ShowFilterPanelMode = DevExpress.XtraGrid.Views.Base.ShowFilterPanelMode.ShowAlways;
            this.advBandedGridView1.OptionsView.ShowFooter = true;
            this.advBandedGridView1.OptionsView.ShowIndicator = false;
            this.advBandedGridView1.DoubleClick += new System.EventHandler(this.advBandedGridView1_DoubleClick);
            // 
            // gridBand1
            // 
            this.gridBand1.Caption = "gridBand1";
            this.gridBand1.Columns.Add(this.colThumbnailImage);
            this.gridBand1.Name = "gridBand1";
            this.gridBand1.OptionsBand.ShowCaption = false;
            this.gridBand1.Width = 60;
            // 
            // colThumbnailImage
            // 
            this.colThumbnailImage.Caption = "تصویر";
            this.colThumbnailImage.ColumnEdit = this.repositoryItemPictureEdit2;
            this.colThumbnailImage.FieldName = "ThumbnailImage";
            this.colThumbnailImage.Name = "colThumbnailImage";
            this.colThumbnailImage.OptionsColumn.FixedWidth = true;
            this.colThumbnailImage.OptionsColumn.ReadOnly = true;
            this.colThumbnailImage.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.colThumbnailImage.RowCount = 3;
            this.colThumbnailImage.Visible = true;
            this.colThumbnailImage.Width = 60;
            // 
            // repositoryItemPictureEdit2
            // 
            this.repositoryItemPictureEdit2.Name = "repositoryItemPictureEdit2";
            this.repositoryItemPictureEdit2.PictureInterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            this.repositoryItemPictureEdit2.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Stretch;
            // 
            // gridBand2
            // 
            this.gridBand2.Caption = "gridBand2";
            this.gridBand2.Columns.Add(this.Colgroup);
            this.gridBand2.Columns.Add(this.colTitle2);
            this.gridBand2.Columns.Add(this.colDescription);
            this.gridBand2.Name = "gridBand2";
            this.gridBand2.OptionsBand.ShowCaption = false;
            this.gridBand2.Width = 198;
            // 
            // Colgroup
            // 
            this.Colgroup.Caption = "گروه";
            this.Colgroup.FieldName = "Group";
            this.Colgroup.Name = "Colgroup";
            this.Colgroup.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.Colgroup.OptionsFilter.FilterPopupMode = DevExpress.XtraGrid.Columns.FilterPopupMode.CheckedList;
            this.Colgroup.Visible = true;
            this.Colgroup.Width = 95;
            // 
            // colTitle2
            // 
            this.colTitle2.Caption = "عنوان";
            this.colTitle2.FieldName = "Title";
            this.colTitle2.Name = "colTitle2";
            this.colTitle2.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.colTitle2.OptionsFilter.FilterPopupMode = DevExpress.XtraGrid.Columns.FilterPopupMode.CheckedList;
            this.colTitle2.Summary.AddRange(new DevExpress.XtraGrid.GridSummaryItem[] {
            new DevExpress.XtraGrid.GridColumnSummaryItem(DevExpress.Data.SummaryItemType.Sum, "Lengh", "")});
            this.colTitle2.Visible = true;
            this.colTitle2.Width = 103;
            // 
            // colDescription
            // 
            this.colDescription.Caption = "شرح";
            this.colDescription.ColumnEdit = this.repositoryItemMemoEdit1;
            this.colDescription.FieldName = "Description";
            this.colDescription.Name = "colDescription";
            this.colDescription.OptionsColumn.AllowFocus = false;
            this.colDescription.OptionsFilter.AutoFilterCondition = DevExpress.XtraGrid.Columns.AutoFilterCondition.Contains;
            this.colDescription.RowCount = 2;
            this.colDescription.RowIndex = 1;
            this.colDescription.Visible = true;
            this.colDescription.Width = 198;
            // 
            // repositoryItemMemoEdit1
            // 
            this.repositoryItemMemoEdit1.AllowFocused = false;
            this.repositoryItemMemoEdit1.AllowHtmlDraw = DevExpress.Utils.DefaultBoolean.True;
            this.repositoryItemMemoEdit1.Appearance.Options.UseTextOptions = true;
            this.repositoryItemMemoEdit1.Appearance.TextOptions.WordWrap = DevExpress.Utils.WordWrap.Wrap;
            this.repositoryItemMemoEdit1.AppearanceFocused.Options.UseTextOptions = true;
            this.repositoryItemMemoEdit1.AppearanceFocused.TextOptions.WordWrap = DevExpress.Utils.WordWrap.Wrap;
            this.repositoryItemMemoEdit1.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.UltraFlat;
            this.repositoryItemMemoEdit1.Name = "repositoryItemMemoEdit1";
            this.repositoryItemMemoEdit1.ReadOnly = true;
            // 
            // colFullInfoHtml
            // 
            this.colFullInfoHtml.FieldName = "FullInfoHtml";
            this.colFullInfoHtml.Name = "colFullInfoHtml";
            this.colFullInfoHtml.Visible = true;
            // 
            // iFind
            // 
            this.iFind.Caption = "&Find";
            this.iFind.CategoryGuid = new System.Guid("ac82dbe7-c530-4aa2-b6de-94a7777426fe");
            this.iFind.Id = 28;
            this.iFind.ImageIndex = 16;
            this.iFind.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F));
            this.iFind.Name = "iFind";
            // 
            // BarMdiChildrenListItem1
            // 
            this.BarMdiChildrenListItem1.Caption = "Window";
            this.BarMdiChildrenListItem1.CategoryGuid = new System.Guid("faa74de1-bd23-44b9-955d-6ba635fa0f01");
            this.BarMdiChildrenListItem1.Id = 44;
            this.BarMdiChildrenListItem1.Name = "BarMdiChildrenListItem1";
            // 
            // repositoryImageComboBox1
            // 
            this.repositoryImageComboBox1.AllowFocused = false;
            this.repositoryImageComboBox1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryImageComboBox1.Items.AddRange(new DevExpress.XtraEditors.Controls.ImageComboBoxItem[] {
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("Debug", "Debug", -1),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("Release", "Release", -1)});
            this.repositoryImageComboBox1.Name = "repositoryImageComboBox1";
            // 
            // repositoryItemComboBox1
            // 
            this.repositoryItemComboBox1.AllowFocused = false;
            this.repositoryItemComboBox1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemComboBox1.Items.AddRange(new object[] {
            "barManager1"});
            this.repositoryItemComboBox1.Name = "repositoryItemComboBox1";
            // 
            // repositoryItemImageComboBox1
            // 
            this.repositoryItemImageComboBox1.AutoHeight = false;
            this.repositoryItemImageComboBox1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageComboBox1.Name = "repositoryItemImageComboBox1";
            // 
            // imageList2
            // 
            this.imageList2.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList2.ImageStream")));
            this.imageList2.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList2.Images.SetKeyName(0, "Solution Explorer.png");
            this.imageList2.Images.SetKeyName(1, "1.png");
            this.imageList2.Images.SetKeyName(2, "8.png");
            this.imageList2.Images.SetKeyName(3, "5.png");
            this.imageList2.Images.SetKeyName(4, "4.png");
            this.imageList2.Images.SetKeyName(5, "7.png");
            this.imageList2.Images.SetKeyName(6, "10.png");
            this.imageList2.Images.SetKeyName(7, "6.png");
            this.imageList2.Images.SetKeyName(8, "3.png");
            this.imageList2.Images.SetKeyName(9, "9.png");
            this.imageList2.Images.SetKeyName(10, "2.png");
            // 
            // imageList3
            // 
            this.imageList3.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList3.ImageStream")));
            this.imageList3.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList3.Images.SetKeyName(0, "");
            this.imageList3.Images.SetKeyName(1, "");
            this.imageList3.Images.SetKeyName(2, "");
            this.imageList3.Images.SetKeyName(3, "");
            this.imageList3.Images.SetKeyName(4, "Control_Timer.bmp");
            this.imageList3.Images.SetKeyName(5, "Control_Label.bmp");
            this.imageList3.Images.SetKeyName(6, "Control_LinkLabel.bmp");
            this.imageList3.Images.SetKeyName(7, "Control_Button.bmp");
            this.imageList3.Images.SetKeyName(8, "Control_TextBox.bmp");
            this.imageList3.Images.SetKeyName(9, "Control_MainMenu.bmp");
            this.imageList3.Images.SetKeyName(10, "Control_Checkbox.bmp");
            this.imageList3.Images.SetKeyName(11, "Control_RadioButton.bmp");
            this.imageList3.Images.SetKeyName(12, "Control_GroupBox.bmp");
            this.imageList3.Images.SetKeyName(13, "Control_PictureBox.bmp");
            this.imageList3.Images.SetKeyName(14, "Control_Panel.bmp");
            this.imageList3.Images.SetKeyName(15, "BarManager.bmp");
            this.imageList3.Images.SetKeyName(16, "Calculator.bmp");
            this.imageList3.Images.SetKeyName(17, "");
            this.imageList3.Images.SetKeyName(18, "NavBarControl.bmp");
            this.imageList3.Images.SetKeyName(19, "GridControl.bmp");
            this.imageList3.Images.SetKeyName(20, "gaugeControl.png");
            this.imageList3.Images.SetKeyName(21, "CardViewControl.Icon.png");
            this.imageList3.Images.SetKeyName(22, "");
            this.imageList3.Images.SetKeyName(23, "TreeList.bmp");
            this.imageList3.Images.SetKeyName(24, "");
            // 
            // popupMenu2
            // 
            this.popupMenu2.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.iUndo),
            new DevExpress.XtraBars.LinkPersistInfo(this.iRedo),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCut, true),
            new DevExpress.XtraBars.LinkPersistInfo(this.iCopy),
            new DevExpress.XtraBars.LinkPersistInfo(this.iPaste),
            new DevExpress.XtraBars.LinkPersistInfo(this.iSelectAll, true)});
            this.popupMenu2.Manager = this.barManager1;
            this.popupMenu2.Name = "popupMenu2";
            // 
            // defaultLookAndFeel1
            // 
            this.defaultLookAndFeel1.LookAndFeel.SkinName = "VS2010";
            // 
            // documentManager1
            // 
            this.documentManager1.BarAndDockingController = this.barAndDockingController1;
            this.documentManager1.MdiParent = this;
            this.documentManager1.MenuManager = this.barManager1;
            this.documentManager1.ShowToolTips = DevExpress.Utils.DefaultBoolean.True;
            this.documentManager1.View = this.tabbedView1;
            this.documentManager1.ViewCollection.AddRange(new DevExpress.XtraBars.Docking2010.Views.BaseView[] {
            this.tabbedView1});
            // 
            // tabbedView1
            // 
            this.tabbedView1.DocumentGroupProperties.HeaderButtons = ((DevExpress.XtraTab.TabButtons)(((DevExpress.XtraTab.TabButtons.Prev | DevExpress.XtraTab.TabButtons.Next) 
            | DevExpress.XtraTab.TabButtons.Default)));
            this.tabbedView1.DocumentProperties.UseFormIconAsDocumentImage = true;
            this.tabbedView1.DocumentSelectorProperties.AllowHtmlDraw = DevExpress.Utils.DefaultBoolean.True;
            this.tabbedView1.DocumentSelectorProperties.DocumentFooterFormat = "{0}\\{1}";
            this.tabbedView1.DocumentSelectorProperties.DocumentHeaderFormat = "{0}<br>Source file";
            this.tabbedView1.DocumentSelectorProperties.PanelFooterFormat = "";
            this.tabbedView1.UseLoadingIndicator = DevExpress.Utils.DefaultBoolean.True;
            // 
            // imageList4
            // 
            this.imageList4.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList4.ImageStream")));
            this.imageList4.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList4.Images.SetKeyName(0, "Refresh_16x16.png");
            this.imageList4.Images.SetKeyName(1, "");
            this.imageList4.Images.SetKeyName(2, "");
            this.imageList4.Images.SetKeyName(3, "Solution Explorer.png");
            this.imageList4.Images.SetKeyName(4, "C#Project_16x16.png");
            this.imageList4.Images.SetKeyName(5, "11.png");
            this.imageList4.Images.SetKeyName(6, "ReferencesOpened_16x16.png");
            this.imageList4.Images.SetKeyName(7, "ReferencesClosed_16x16.png");
            this.imageList4.Images.SetKeyName(8, "VSFolder_open_hidden.bmp");
            this.imageList4.Images.SetKeyName(9, "VSFolder_closed_hidden.bmp");
            this.imageList4.Images.SetKeyName(10, "12.png");
            this.imageList4.Images.SetKeyName(11, "13.png");
            this.imageList4.Images.SetKeyName(12, "14.png");
            this.imageList4.Images.SetKeyName(13, "VSProject_generatedfile.bmp");
            // 
            // document1
            // 
            this.document1.Caption = "dockPanel1";
            this.document1.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document1.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document2
            // 
            this.document2.Caption = "dockPanel1";
            this.document2.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document2.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document3
            // 
            this.document3.Caption = "dockPanel1";
            this.document3.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document3.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document4
            // 
            this.document4.Caption = "dockPanel1";
            this.document4.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document4.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document5
            // 
            this.document5.Caption = "dockPanel1";
            this.document5.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document5.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document6
            // 
            this.document6.Caption = "dockPanel1";
            this.document6.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document6.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // document7
            // 
            this.document7.Caption = "dockPanel1";
            this.document7.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.False;
            this.document7.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // CurrentChapterbindingSource
            // 
            this.CurrentChapterbindingSource.DataSource = typeof(Player.Chapter);
            // 
            // imageCollectionLarge
            // 
            this.imageCollectionLarge.ImageSize = new System.Drawing.Size(24, 24);
            this.imageCollectionLarge.ImageStream = ((DevExpress.Utils.ImageCollectionStreamer)(resources.GetObject("imageCollectionLarge.ImageStream")));
            this.imageCollectionLarge.Images.SetKeyName(0, "time_frame_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(1, "time_frame_add_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(2, "time_frame_back_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(3, "time_frame_clock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(4, "time_frame_close_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(5, "time_frame_config_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(6, "time_frame_delete_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(7, "time_frame_down_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(8, "time_frame_help_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(9, "time_frame_info_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(10, "time_frame_level_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(11, "time_frame_lock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(12, "time_frame_next_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(13, "time_frame_ok_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(14, "time_frame_reload_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(15, "time_frame_save_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(16, "time_frame_search_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(17, "time_frame_star_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(18, "time_frame_unlock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(19, "time_frame_up_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(20, "time_frame_write_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(21, "time_frame_zoom_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(22, "time_sheet_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(23, "time_sheet_add_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(24, "time_sheet_back_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(25, "time_sheet_clock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(26, "time_sheet_close_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(27, "time_sheet_config_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(28, "time_sheet_delete_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(29, "time_sheet_down_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(30, "time_sheet_help_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(31, "time_sheet_info_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(32, "time_sheet_level_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(33, "time_sheet_lock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(34, "time_sheet_next_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(35, "time_sheet_ok_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(36, "time_sheet_reload_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(37, "time_sheet_save_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(38, "time_sheet_search_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(39, "time_sheet_star_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(40, "time_sheet_unlock_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(41, "time_sheet_up_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(42, "time_sheet_write_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(43, "time_sheet_zoom_32.ico");
            this.imageCollectionLarge.Images.SetKeyName(44, "scissors_save_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(45, "rec_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(46, "refresh_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(47, "reload_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(48, "remove_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(49, "save_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(50, "scissors_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(51, "scissors_add_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(52, "scissors_back_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(53, "scissors_clock_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(54, "scissors_close_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(55, "scissors_config_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(56, "scissors_down_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(57, "scissors_help_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(58, "scissors_info_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(59, "scissors_level_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(60, "scissors_lock_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(61, "scissors_next_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(62, "scissors_next1_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(63, "scissors_ok_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(64, "scissors_reload_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(65, "scissors_remove_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(66, "scissors_save_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(67, "scissors_search_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(68, "scissors_star_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(69, "scissors_unlock_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(70, "scissors_up_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(71, "scissors_write_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(72, "scissors_zoom_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(73, "music_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(74, "music_add_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(75, "music_back_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(76, "music_close_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(77, "music_config_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(78, "music_down_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(79, "music_help_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(80, "music_info_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(81, "music_level_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(82, "music_lock_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(83, "music_next_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(84, "music_ok_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(85, "music_reload_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(86, "music_remove_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(87, "music_save_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(88, "music_search_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(89, "music_star_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(90, "music_unlock_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(91, "music_up_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(92, "music_write_48.ico");
            this.imageCollectionLarge.Images.SetKeyName(93, "music_zoom_48.ico");
            // 
            // openFileMetaData
            // 
            this.openFileMetaData.DefaultExt = "xml";
            this.openFileMetaData.Filter = "xml file|*.xml";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "add_16.ico");
            this.imageList.Images.SetKeyName(1, "handlersetleft.png");
            this.imageList.Images.SetKeyName(2, "handlersetright.png");
            // 
            // document8
            // 
            this.document8.Caption = "PlayerDockPanel";
            this.document8.Properties.AllowClose = DevExpress.Utils.DefaultBoolean.True;
            this.document8.Properties.AllowFloat = DevExpress.Utils.DefaultBoolean.True;
            // 
            // frmMain
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 14);
            this.ClientSize = new System.Drawing.Size(768, 636);
            this.Controls.Add(this.panelContainer1);
            this.Controls.Add(this.panelContainer2);
            this.Controls.Add(this.barDockControl3);
            this.Controls.Add(this.barDockControl4);
            this.Controls.Add(this.barDockControl2);
            this.Controls.Add(this.barDockControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DockingDemo (C# Demo)";
            this.Load += new System.EventHandler(this.frmMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ListItemgridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImageComboBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollection1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayListbindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChaptureGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barAndDockingController1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).EndInit();
            this.panelContainer2.ResumeLayout(false);
            this.dockPanelShot.ResumeLayout(false);
            this.dockPanel3_Container.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.vGridControlChapters)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChapterbindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DesrepositoryItemMemoExEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImagerepositoryItemPictureEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TitlerepositoryItemTextEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LenrepositoryItemTextEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GrouprepositoryItemMRUEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SelectedCheckEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PositionrepositoryItemTextEdit)).EndInit();
            this.dockPanelTask.ResumeLayout(false);
            this.dockPanelOutPut.ResumeLayout(false);
            this.panelContainer1.ResumeLayout(false);
            this.dockPanelSolution.ResumeLayout(false);
            this.dockPanel1_Container.ResumeLayout(false);
            this.dockPanelFind.ResumeLayout(false);
            this.dockPanel2_Container.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.gridControl2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AllchapterBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.advBandedGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryImageComboBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemComboBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.documentManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabbedView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document7)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentChapterbindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollectionLarge)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AllChapterGroupbindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.document8)).EndInit();
            this.ResumeLayout(false);

        }


        #endregion
        private DevExpress.XtraBars.BarManager barManager1;
        private DevExpress.XtraBars.BarDockControl barDockControl1;
        private DevExpress.XtraBars.BarDockControl barDockControl2;
        private DevExpress.XtraBars.BarDockControl barDockControl3;
        private DevExpress.XtraBars.BarDockControl barDockControl4;
        private DevExpress.XtraBars.BarSubItem siFile;
        private DevExpress.XtraBars.BarSubItem siEdit;
        private DevExpress.XtraBars.BarSubItem siNew;
        private DevExpress.XtraBars.BarButtonItem iOpen;
        private DevExpress.XtraBars.BarButtonItem iClose;
        private System.Windows.Forms.ImageList imageList1;
        private DevExpress.XtraBars.BarButtonItem iProject;
        private DevExpress.XtraBars.BarButtonItem iFile;
        private DevExpress.XtraBars.BarButtonItem iBlankSolution;
        private DevExpress.XtraBars.BarButtonItem iAddNewItem;
        private DevExpress.XtraBars.BarButtonItem iAddExistingItem;
        private DevExpress.XtraBars.BarSubItem siAddProject;
        private DevExpress.XtraBars.BarButtonItem iNewProject;
        private DevExpress.XtraBars.BarButtonItem iExistingProject;
        private DevExpress.XtraBars.BarButtonItem iSaveAll;
        private DevExpress.XtraBars.BarButtonItem iOpenSolution;
        private DevExpress.XtraBars.BarButtonItem iCloseSolution;
        private DevExpress.XtraBars.BarButtonItem iPageSetup;
        private DevExpress.XtraBars.BarButtonItem iPrint;
        private DevExpress.XtraBars.BarButtonItem iExit;
        private DevExpress.XtraBars.BarButtonItem iUndo;
        private DevExpress.XtraBars.BarButtonItem iRedo;
        private DevExpress.XtraBars.BarButtonItem iCut;
        private DevExpress.XtraBars.BarButtonItem iCopy;
        private DevExpress.XtraBars.BarButtonItem iPaste;
        private DevExpress.XtraBars.BarButtonItem iDelete;
        private DevExpress.XtraBars.BarButtonItem iCycle;
        private DevExpress.XtraBars.BarButtonItem iSelectAll;
        private DevExpress.XtraBars.BarButtonItem iFind;
        private DevExpress.XtraBars.BarButtonItem iNew;
        private DevExpress.XtraBars.PopupMenu popupMenu1;
        private DevExpress.XtraBars.BarButtonItem iOpenFile;
        private DevExpress.XtraBars.BarButtonItem iSave;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox repositoryImageComboBox1;
        private DevExpress.XtraEditors.Repository.RepositoryItemComboBox repositoryItemComboBox1;
        private DevExpress.XtraBars.BarButtonItem iSolutionExplorer;
        private DevExpress.XtraBars.BarButtonItem iProperties;
        private DevExpress.XtraBars.BarButtonItem iToolbox;
        private DevExpress.XtraBars.BarButtonItem iClassView;
        private DevExpress.XtraBars.BarButtonItem iTaskList;
        private DevExpress.XtraBars.BarButtonItem iFindResults;
        private DevExpress.XtraBars.BarButtonItem iOutput;
        private DevExpress.XtraBars.BarMdiChildrenListItem BarMdiChildrenListItem1;
        private DevExpress.XtraBars.BarSubItem siWindow;
        private DevExpress.XtraBars.PopupMenu popupMenu2;
        private DevExpress.XtraBars.BarStaticItem iStatus1;
        private DevExpress.XtraBars.BarStaticItem iStatus2;
        private System.Windows.Forms.ImageList imageList2;
        private DevExpress.XtraBars.BarButtonItem iLoadLayout;
        private DevExpress.XtraBars.BarButtonItem iSaveLayout;
        private DevExpress.XtraBars.BarSubItem siLayouts;
        private DevExpress.XtraBars.Bar bar1;
        private DevExpress.XtraBars.Bar bar2;
        private DevExpress.XtraBars.Bar bar3;
        private DevExpress.XtraBars.Bar bar4;
        private DevExpress.XtraBars.Bar bar5;
        private DevExpress.XtraBars.BarSubItem iPaintStyle;
        private DevExpress.XtraBars.Docking.DockManager dockManager1;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelSolution;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel1_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelFind;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel2_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelShot;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel3_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelTask;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel4_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelOutPut;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel5_Container;
        private DevExpress.XtraBars.Docking.DockPanel panelContainer1;
        private DevExpress.XtraBars.BarAndDockingController barAndDockingController1;
        private System.Windows.Forms.ImageList imageList3;
        private DevExpress.LookAndFeel.DefaultLookAndFeel defaultLookAndFeel1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox repositoryItemImageComboBox1;
        private System.ComponentModel.IContainer components;
        private DevExpress.XtraBars.Docking2010.DocumentManager documentManager1;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.TabbedView tabbedView1;
        private System.Windows.Forms.ImageList imageList4;
        private BarDockingMenuItem barDockingMenuItem1;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document1;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document2;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document3;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document4;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document5;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document6;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document7;
        private System.Windows.Forms.BindingSource CurrentChapterbindingSource;
        private System.Windows.Forms.BindingSource AllchapterBindingSource;
        private System.Windows.Forms.BindingSource ChapterbindingSource;
        private DevExpress.Utils.ImageCollection imageCollectionLarge;
        private System.Windows.Forms.OpenFileDialog openFileMetaData;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.BindingSource PlayListbindingSource;
        private DevExpress.Utils.ImageCollection imageCollection1;
        private System.Windows.Forms.BindingSource AllChapterGroupbindingSource;
        private System.Windows.Forms.ImageList imageList;
        internal System.Windows.Forms.Timer DurationTimer;
        private DevExpress.XtraGrid.GridControl gridControl;
        private DevExpress.XtraGrid.Views.Grid.GridView ListItemgridView;
        private DevExpress.XtraGrid.Columns.GridColumn colSourceType;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox ImageComboBox;
        private DevExpress.XtraGrid.Columns.GridColumn colTitle;
        private DevExpress.XtraGrid.Views.Grid.GridView ChaptureGridView;
        private DevExpress.XtraGrid.Columns.GridColumn gridColumn3;
        private DevExpress.XtraGrid.Columns.GridColumn colTitle1;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView1;
        private DevExpress.XtraGrid.Columns.GridColumn gridColumn1;
        private DevExpress.XtraGrid.Columns.GridColumn colName;
        private DevExpress.XtraGrid.GridControl gridControl2;
        private DevExpress.XtraGrid.Views.BandedGrid.AdvBandedGridView advBandedGridView1;
        private DevExpress.XtraGrid.Views.BandedGrid.GridBand gridBand1;
        private DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn colThumbnailImage;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit repositoryItemPictureEdit2;
        private DevExpress.XtraGrid.Views.BandedGrid.GridBand gridBand2;
        private DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn Colgroup;
        private DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn colTitle2;
        private DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn colDescription;
        private DevExpress.XtraEditors.Repository.RepositoryItemMemoEdit repositoryItemMemoEdit1;
        private DevExpress.XtraGrid.Views.BandedGrid.BandedGridColumn colFullInfoHtml;
        private DevExpress.XtraVerticalGrid.VGridControl vGridControlChapters;
        private DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit DesrepositoryItemMemoExEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit ImagerepositoryItemPictureEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit TitlerepositoryItemTextEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit LenrepositoryItemTextEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemMRUEdit GrouprepositoryItemMRUEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit SelectedCheckEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit PositionrepositoryItemTextEdit;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowPosition;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowThumbnailSource;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowThumbnailImage;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow LenRow;
        private DevExpress.XtraVerticalGrid.Rows.MultiEditorRow rowTitlerGroup;
        private DevExpress.XtraVerticalGrid.Rows.MultiEditorRow Timerow;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow rowDescription;
        private DevExpress.XtraVerticalGrid.Rows.EditorRow ChapterMSelected;
        private DevExpress.XtraBars.Docking.DockPanel panelContainer2;
        private DevExpress.XtraBars.Docking2010.Views.Tabbed.Document document8;
    }
}
