using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DevExpress.XtraGrid.Views.Grid;
using DevExpress.Utils;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;
using System.Windows.Forms;
using System.Drawing;
using DevExpress.XtraEditors;
using System.ComponentModel;
using Helpers;
using DevExpress.XtraVerticalGrid;

namespace Player.Controls
{
    public class GridViewImageTextToolTipController : IDisposable
    {
        string fieldName = null;
        string dataName = null;
        GridView view;
        ToolTipController controller;
        GridHitInfo hotTrackInfo = null;
        bool isImage = true;
        int pictureMaxLineSize = 300;
        public GridViewImageTextToolTipController(GridView view, string fieldName) : this(view, fieldName, true) { }
        public GridViewImageTextToolTipController(GridView view, string fieldName, bool image) : this(view, fieldName, null, image) { }
        public GridViewImageTextToolTipController(GridView view, string fieldName, string dataName, bool image) : this(view, fieldName, dataName, image, 0) { }
        public GridViewImageTextToolTipController(GridView view, string fieldName, string dataName, bool image, int pictureMaxLineSize)
        {
            this.view = view;
            this.fieldName = fieldName;
            this.dataName = dataName;
            this.isImage = image;
            this.view.Disposed += new EventHandler(delegate { Dispose(); });
            if (pictureMaxLineSize > 0)
                this.pictureMaxLineSize = pictureMaxLineSize;
            controller = new ToolTipController();
            controller.ToolTipType = ToolTipType.SuperTip;
            controller.AllowHtmlText = dataName != null;
            controller.ReshowDelay = controller.InitialDelay;
            if (dataName != null || !isImage)
                controller.AutoPopDelay = 10000;
            if (view.GridControl == null) return;
            view.GridControl.MouseMove += new System.Windows.Forms.MouseEventHandler(GridControl_MouseMove);
            view.TopRowChanged += new EventHandler(view_TopRowChanged);
            view.ShownEditor += new EventHandler(delegate { controller.HideHint(); });
            view.GridControl.MouseDown += new MouseEventHandler(delegate { controller.HideHint(); });
            view.GridControl.MouseLeave += new EventHandler(delegate { controller.HideHint(); });
        }
        public GridHitInfo HotTrackInfo
        {
            get { return hotTrackInfo; }
            set
            {
                if (!value.InRowCell)
                {
                    controller.HideHint();
                    hotTrackInfo = null;
                    return;
                }
                if (hotTrackInfo != null &&
                    hotTrackInfo.Column == value.Column &&
                    hotTrackInfo.RowHandle == value.RowHandle) return;
                hotTrackInfo = value;
                ShowToolTip();
            }
        }
        bool IsEditing
        {
            get
            {
                return view.ActiveEditor != null &&
                    HotTrackInfo.Column == view.FocusedColumn &&
                    HotTrackInfo.RowHandle == view.FocusedRowHandle;
            }
        }
        void ShowToolTip()
        {
            if (!HotTrackInfo.InRowCell || HotTrackInfo.Column.FieldName != fieldName ||
                IsEditing)
            {
                controller.HideHint();
                return;
            }
            ToolTipControlInfo info = new ToolTipControlInfo();
            ToolTipItem item = new ToolTipItem();
            item.ImageToTextDistance = 0;
            if (isImage)
            {
                item.Image = ImageCreator.CreateImage(
                    view.GetRowCellValue(HotTrackInfo.RowHandle, HotTrackInfo.Column) as Image,
                    pictureMaxLineSize, pictureMaxLineSize);
                if (dataName != null)
                {
                    item.Text = (string)view.GetRowCellValue(HotTrackInfo.RowHandle, view.Columns[dataName]);// string.Format("{0}", view.GetRowCellValue(HotTrackInfo.RowHandle, view.Columns[dataName]));
                    item.ImageToTextDistance = 10;
                }
            }
            else
                item.Text = string.Format("{0}", view.GetRowCellValue(HotTrackInfo.RowHandle, HotTrackInfo.Column));
            info.Object = HotTrackInfo;
            info.SuperTip = new SuperToolTip();
            info.SuperTip.Items.Add(item);
            info.ToolTipPosition = Cursor.Position;
            controller.ShowHint(info);
        }
        void GridControl_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            HotTrackInfo = view.CalcHitInfo(e.X, e.Y);
        }
        void view_TopRowChanged(object sender, EventArgs e)
        {
            controller.HideHint();
            HotTrackInfo = view.CalcHitInfo(view.GridControl.PointToClient(Cursor.Position));
        }
        #region IDisposable Members
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                this.controller.Dispose();
            }
        }
        ~GridViewImageTextToolTipController()
        {
            Dispose(false);
        }
        #endregion
    }
    public class vGridViewImageTextToolTipController : IDisposable
    {
        string fieldName = null;
        string dataName = null;
        VGridControl view;
        ToolTipController controller;
        VGridHitInfo hotTrackInfo = null;
        bool isImage = true;
        int pictureMaxLineSize = 300;
        public vGridViewImageTextToolTipController(VGridControl view, string fieldName) : this(view, fieldName, true) { }
        public vGridViewImageTextToolTipController(VGridControl view, string fieldName, bool image) : this(view, fieldName, null, image) { }
        public vGridViewImageTextToolTipController(VGridControl view, string fieldName, string dataName, bool image) : this(view, fieldName, dataName, image, 0) { }
        public vGridViewImageTextToolTipController(VGridControl view, string fieldName, string dataName, bool image, int pictureMaxLineSize)
        {
            this.view = view;
            this.fieldName = fieldName;
            this.dataName = dataName;
            this.isImage = image;
            this.view.Disposed += new EventHandler(delegate { Dispose(); });
            if (pictureMaxLineSize > 0)
                this.pictureMaxLineSize = pictureMaxLineSize;
            controller = new ToolTipController();
            controller.ToolTipType = ToolTipType.SuperTip;
            controller.AllowHtmlText = dataName != null;
            controller.ReshowDelay = controller.InitialDelay;
            if (dataName != null || !isImage)
                controller.AutoPopDelay = 10000;
            if (view == null) return;
            view.MouseMove += new System.Windows.Forms.MouseEventHandler(GridControl_MouseMove);
            //view.TopVisibleRowIndexChanged+= new EventHandler(view_TopRowChanged);
            view.ShownEditor += new EventHandler(delegate { controller.HideHint(); });
            view.MouseDown += new MouseEventHandler(delegate { controller.HideHint(); });
            view.MouseLeave += new EventHandler(delegate { controller.HideHint(); });
        }
        public VGridHitInfo HotTrackInfo
        {
            get { return hotTrackInfo; }
            set
            {
                if (value.CellIndex<0)
                {
                    controller.HideHint();
                    hotTrackInfo = null;
                    return;
                }
                if (hotTrackInfo != null &&
                    hotTrackInfo.Row == value.Row &&
                    hotTrackInfo.RecordIndex == value.RecordIndex) return;
                hotTrackInfo = value;
                ShowToolTip();
            }
        }
        bool IsEditing
        {
            get
            {
                return view.ActiveEditor != null &&
                    HotTrackInfo.RecordIndex == view.FocusedRecord &&
                    HotTrackInfo.Row == view.FocusedRow;
            }
        }
        void ShowToolTip()
        {
            if (HotTrackInfo.CellIndex<0 || HotTrackInfo.Row.Name != fieldName ||
                IsEditing)
            {
                controller.HideHint();
                return;
            }
            ToolTipControlInfo info = new ToolTipControlInfo();
            ToolTipItem item = new ToolTipItem();
            item.ImageToTextDistance = 0;
            if (isImage)
            {
                item.Image = ImageCreator.CreateImage(
                    view.GetCellValue(HotTrackInfo.Row, HotTrackInfo.RecordIndex) as Image,
                    pictureMaxLineSize, pictureMaxLineSize);
                if (dataName != null)
                {
                    item.Text = (string)view.GetCellValue(view.Rows[dataName],HotTrackInfo.RecordIndex);// string.Format("{0}", view.GetRowCellValue(HotTrackInfo.RowHandle, view.Columns[dataName]));
                    item.ImageToTextDistance = 10;
                }
            }
            else
                item.Text = string.Format("{0}", view.GetCellValue(HotTrackInfo.Row, HotTrackInfo.RecordIndex));
            info.Object = HotTrackInfo;
            info.SuperTip = new SuperToolTip();
            info.SuperTip.Items.Add(item);
            info.ToolTipPosition = Cursor.Position;
            controller.ShowHint(info);
        }
        void GridControl_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            HotTrackInfo = view.CalcHitInfo(e.Location);
        }
        void view_TopRowChanged(object sender, EventArgs e)
        {
            controller.HideHint();
            HotTrackInfo = view.CalcHitInfo(view.PointToClient(Cursor.Position));
        }
        #region IDisposable Members
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                this.controller.Dispose();
            }
        }
        ~vGridViewImageTextToolTipController()
        {
            Dispose(false);
        }
        #endregion
    }

    public class ObjectToolTipController : IDisposable
    {
        ToolTipController controller;
        Control parent;
        object editObject;
        public object EditObject { get { return editObject; } }
        public ObjectToolTipController(Control parent)
        {
            this.parent = parent;
            this.parent.Disposed += new EventHandler(delegate { Dispose(); });
            this.controller = new ToolTipController();
            this.controller.ToolTipType = ToolTipType.SuperTip;
            this.controller.AllowHtmlText = true;
            this.controller.ReshowDelay = controller.InitialDelay;
            this.controller.AutoPopDelay = 10000;
            parent.MouseDown += new MouseEventHandler(delegate { HideHint(false); });
            parent.MouseLeave += new EventHandler(delegate { HideHint(true); });
            //if (parent is PivotGridControl)
            //    ((PivotGridControl)parent).LeftTopCellChanged += new EventHandler<PivotLeftTopCellChangedEventArgs>(delegate { HideHint(true); });
        }
        public void ShowHint(object editObject, Point location)
        {
            if (object.Equals(editObject, this.editObject)) return;
            this.editObject = editObject;
            ToolTipControlInfo info = new ToolTipControlInfo();
            ToolTipItem item = new ToolTipItem();
            InitToolTipItem(item);
            item.ImageToTextDistance = 10;
            info.Object = DateTime.Now.Ticks;
            info.SuperTip = new SuperToolTip();
            info.SuperTip.Items.Add(item);
            info.ToolTipPosition = this.parent.PointToScreen(location);
            controller.ShowHint(info);
        }
        protected virtual void InitToolTipItem(ToolTipItem item)
        {
        }
        public void HideHint(bool clearCurrentObject)
        {
            if (clearCurrentObject) this.editObject = null;
            this.controller.HideHint();
        }
        #region IDisposable Members
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                this.controller.Dispose();
            }
        }
        ~ObjectToolTipController()
        {
            Dispose(false);
        }
        #endregion
    }

 
    //public class StickLookAndFeelForm : CustomTopForm
    //{
    //    EmptySkinElementPainter painter = new EmptySkinElementPainter();
    //    public StickLookAndFeelForm()
    //    {
    //        UserLookAndFeel.Default.StyleChanged += new EventHandler(Default_StyleChanged);
    //        UpdateRegion();
    //    }

    //    void Default_StyleChanged(object sender, EventArgs e)
    //    {
    //        UpdateRegion();
    //    }
    //    protected override void OnPaint(PaintEventArgs e)
    //    {
    //        Skin skin = BarSkins.GetSkin(UserLookAndFeel.Default);
    //        GraphicsCache cache = new GraphicsCache(e);
    //        DrawContent(cache, skin);
    //        DrawTopElement(cache, skin);
    //        base.OnPaint(e);
    //    }
    //    Rectangle GetTopElementRectangle()
    //    {
    //        Rectangle r = this.ClientRectangle;
    //        return new Rectangle(r.X, r.Y, r.Width, 10);
    //    }
    //    void DrawContent(GraphicsCache graphicsCache, Skin skin)
    //    {
    //        SkinElement element = skin[BarSkins.SkinAlertWindow];
    //        SkinElementInfo eInfo = new SkinElementInfo(element, this.ClientRectangle);
    //        ObjectPainter.DrawObject(graphicsCache, SkinElementPainter.Default, eInfo);
    //    }
    //    void DrawTopElement(GraphicsCache graphicsCache, Skin skin)
    //    {
    //        SkinElement element = skin[BarSkins.SkinAlertCaptionTop];
    //        SkinElementInfo eInfo = new SkinElementInfo(element, GetTopElementRectangle());
    //        ObjectPainter.DrawObject(graphicsCache, painter, eInfo);
    //    }
    //    internal void UpdateRegion()
    //    {
    //        SkinElement se = BarSkins.GetSkin(UserLookAndFeel.Default)[BarSkins.SkinAlertWindow];
    //        if (se == null)
    //        {
    //            this.Region = null;
    //            return;
    //        }
    //        int cornerRadius = se.Properties.GetInteger(BarSkins.SkinAlertWindowCornerRadius);
    //        if (cornerRadius == 0) this.Region = null;
    //        else this.Region = NativeMethods.CreateRoundRegion(new Rectangle(Point.Empty, this.Size), cornerRadius);
    //    }
    //    protected override bool HasSystemShadow { get { return true; } }
    //    class EmptySkinElementPainter : SkinElementPainter
    //    {
    //        protected override void DrawSkinForeground(SkinElementInfo ee) { }
    //    }
    //}
    public class FormAnimationSizer
    {
        Form parent;
        Size sizeInit;
        Timer tmr = null;
        int minHeight = 0;
        int step = 10;
        int heightStep = 0;
        public FormAnimationSizer(Form form)
        {
            parent = form;
            sizeInit = form.ClientSize;
            parent.StartPosition = FormStartPosition.Manual;
            parent.Location = new Point(Screen.PrimaryScreen.WorkingArea.Left + (Screen.PrimaryScreen.WorkingArea.Width - sizeInit.Width) / 2,
                Screen.PrimaryScreen.WorkingArea.Top + (Screen.PrimaryScreen.WorkingArea.Height - sizeInit.Height) / 2);
            tmr = new Timer();
            tmr.Enabled = false;
            tmr.Interval = 20;
            tmr.Tick += new EventHandler(tmr_Tick);
        }
        void tmr_Tick(object sender, EventArgs e)
        {
            int allowHeight = parent.ClientSize.Height + (minHeight > parent.ClientSize.Height ? heightStep : -heightStep);
            heightStep += step / 2;
            if (Math.Abs(allowHeight - minHeight) <= heightStep)
            {
                parent.ClientSize = new Size(sizeInit.Width, minHeight);
                tmr.Stop();
            }
            else
            {
                parent.ClientSize = new Size(sizeInit.Width, allowHeight);
            }
        }
        public void SetMinHeight(int height)
        {
            bool animation = minHeight != 0;
            minHeight = height;
            if (animation)
            {
                heightStep = step;
                tmr.Start();
            }
            else
                parent.ClientSize = new Size(sizeInit.Width, minHeight);
        }
    }
    public class HotLabel : LabelControl
    {
        string linkText = string.Empty;
        public HotLabel()
        {
            LookAndFeel.StyleChanged += new EventHandler(Default_StyleChanged);
            UpdateColors();
        }
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                LookAndFeel.StyleChanged -= new EventHandler(Default_StyleChanged);
            }
            base.Dispose(disposing);
        }
        [DefaultValue("")]
        public string LinkText
        {
            get { return linkText; }
            set
            {
                if (linkText == value) return;
                linkText = value;
            }
        }
        void Default_StyleChanged(object sender, EventArgs e)
        {
            UpdateColors();
        }
        public void UpdateColors()
        {
            if (DesignMode) return;
            this.Appearance.ForeColor = WinHelper.GetLinkColor(LookAndFeel);
        }
        protected override void OnMouseEnter(EventArgs e)
        {
            base.OnMouseEnter(e);
            if (DesignMode) return;
            Appearance.Font = new Font(Appearance.Font, FontStyle.Underline);
            Cursor = Cursors.Hand;
        }
        protected override void OnMouseLeave(EventArgs e)
        {
            base.OnMouseLeave(e);
            if (DesignMode) return;
            Appearance.Font = new Font(Appearance.Font, FontStyle.Regular);
            Cursor = Cursors.Default;
        }
        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            if (DesignMode || string.IsNullOrEmpty(LinkText)) return;
            Cursor = Cursors.WaitCursor;
            ObjectHelper.ShowWebSite(LinkText);
        }
    }
}
