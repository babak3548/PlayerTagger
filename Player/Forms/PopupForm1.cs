using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DevExpress.ExpressApp.Model;
using DevExpress.ExpressApp.Templates;
using DevExpress.ExpressApp.Utils;
using DevExpress.ExpressApp.Win.Controls;
using DevExpress.ExpressApp.Win.SystemModule;
using DevExpress.ExpressApp.Win.Templates.ActionContainers;
using DevExpress.ExpressApp.Win.Utils;
using DevExpress.Utils.Controls;
using DevExpress.XtraLayout;
using DevExpress.ExpressApp.Win;
using DevExpress.ExpressApp.Win.Templates;

namespace Player.Forms
{
    public partial class PopupForm1 : DevExpress.XtraEditors.XtraForm, IWindowTemplate, ISupportViewChanged, ISupportStoreSettings, IViewSiteTemplate, IBarManagerHolder
    {
        private const int viewControlPreferredWidth = 350;
        private const int viewControlPreferredHeight = 215;
        private Size initialMinimumSize = new Size(420, 150);
        private const string FrameTemplatesPopupForm = @"FrameTemplates\PopupForm";
        private bool autoShrink;
        private TemplatesHelper locaizationHelper;
        private IModelTemplateWin modelTemplate;
        private void OnSettingsReloaded()
        {
            if (SettingsReloaded != null)
            {
                SettingsReloaded(this, EventArgs.Empty);
            }
        }
        private void MoveFocusToFirstViewControl()
        {
            if (viewSitePanel != null)
            {
                viewSitePanel.SelectNextControl(viewSitePanel, true, true, true, false);
            }
        }
        private Size GetViewSitePanelMinSize()
        {
            Control viewControl = viewSitePanel.Controls[0];
            if (viewControl is LayoutControl)
            {
                LayoutControl layoutControl = viewControl as LayoutControl;
                layoutControl.BeginUpdate();
                layoutControl.EndUpdate();
            }
            IXtraResizableControl resizableControl = viewControl as IXtraResizableControl;
            if (resizableControl != null)
            {
                return resizableControl.MinSize;
            }
            return viewControl.MinimumSize;
        }
        public void UpdateSize()
        {
            bottomPanel.MinimumSize = bottomPanel.MinSize;
            if (viewSitePanel.Controls.Count > 0)
            {
                Size viewControlMinimumSize = GetViewSitePanelMinSize();

                //int nonClientWidth = Size.Width - ClientSize.Width;
                //int nonClientHeight = Size.Height - ClientSize.Height;

                //int viewControlMinWidthWithPaddings = viewSitePanel.Padding.Left + viewSitePanel.Padding.Right + viewControlMinimumSize.Width;
                //int viewControlMinHeightWithPaddings = viewSitePanel.Padding.Top + viewSitePanel.Padding.Bottom + viewControlMinimumSize.Height;
                Size calculatedMinumumSize = new Size(Math.Max(viewControlMinimumSize.Width + viewSitePanel.Padding.Size.Width, initialMinimumSize.Width),
                        Math.Max(viewControlMinimumSize.Height + viewSitePanel.Padding.Size.Height + bottomPanel.MinSize.Height, initialMinimumSize.Height));
                if (CustomizeMinimumSize != null)
                {
                    CustomSizeEventArgs eventArgs = new CustomSizeEventArgs(calculatedMinumumSize);
                    CustomizeMinimumSize(this, eventArgs);
                    if (eventArgs.Handled)
                    {
                        calculatedMinumumSize = new Size(Math.Max(calculatedMinumumSize.Width, eventArgs.CustomSize.Width), Math.Max(calculatedMinumumSize.Height, eventArgs.CustomSize.Height));
                    }
                }
                MinimumSize = calculatedMinumumSize;

                if (AutoShrink && !IsSizeable)
                {
                    if (CustomizeClientSize != null)
                    {
                        CustomSizeEventArgs eventArgs = new CustomSizeEventArgs(calculatedMinumumSize);
                        CustomizeClientSize(this, eventArgs);
                        if (eventArgs.Handled)
                        {
                            calculatedMinumumSize = eventArgs.CustomSize;
                        }
                    }
                    if (WindowState == FormWindowState.Maximized)
                    {
                        ClientSize = new Size(
                            Math.Max(calculatedMinumumSize.Width, Size.Width),
                            Math.Max(calculatedMinumumSize.Height, Size.Height));
                    }
                    else
                    {
                        ClientSize = calculatedMinumumSize;
                    }
                }
            }
        }
        protected virtual void ReloadSettingsCore()
        {
            if (modelTemplate != null && IsSizeable)
            {
                formStateModelSynchronizer.ApplyModel();
            }
        }
        protected virtual void OnBarMangerChanged()
        {
            if (BarManagerChanged != null)
            {
                BarManagerChanged(this, EventArgs.Empty);
            }
        }
        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            UpdateSize();
        }
        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            if (Visible)
            {
                UpdateSize();
            }
        }
        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            MoveFocusToFirstViewControl();
        }
        public PopupForm1()
        {
            InitializeComponent();
            NativeMethods.SetExecutingApplicationIcon(this);
            autoShrink = true;
            ShowInTaskbar = true;
            KeyPreview = true;
            UpdateSize();
            //ClientSize = new Size(
            //    ClientSize.Width - viewSitePanel.Width + viewSitePanel.Padding.Left + viewSitePanel.Padding.Right + viewControlPreferredWidth,
            //    ClientSize.Height - viewSitePanel.Height + viewSitePanel.Padding.Top + viewSitePanel.Padding.Bottom + viewControlPreferredHeight);
        }
        public void AddControl(Control control, string caption)
        {
            if (control != null)
            {
                viewSitePanel.Controls.Add(control);
                control.Dock = DockStyle.Fill;
                Text = caption;
            }
        }
        public virtual ICollection<IActionContainer> GetContainers()
        {
            return actionContainersManager.GetContainers();
        }
        public virtual void SetView(DevExpress.ExpressApp.View view)
        {
            viewSiteManager.SetView(view);
            if (ViewChanged != null)
            {
                ViewChanged(this, new TemplateViewChangedEventArgs(view));
            }
            if (view != null)
            {
                if (view.Model != null)
                {
                    string imageName = ViewImageNameHelper.GetImageName(view);
                    NativeMethods.SetFormIcon(this,
                        ImageLoader.Instance.GetImageInfo(imageName).Image,
                        ImageLoader.Instance.GetLargeImageInfo(imageName).Image);
                }
                else
                {
                    NativeMethods.SetFormIcon(this,
                        NativeMethods.ExeIconSmall,
                        NativeMethods.ExeIconLarge);
                }
                Text = view.Caption;
                MoveFocusToFirstViewControl();
            }

        }
        public virtual void SetSettings(IModelTemplate modelTemplate)
        {
            this.modelTemplate = (IModelTemplateWin)modelTemplate;
            locaizationHelper = new TemplatesHelper(this.modelTemplate);

            string viewId = String.Empty;
            if (viewSiteManager.View != null)
            {
                viewId = viewSiteManager.View.Id;
            }
            formStateModelSynchronizer.Model = locaizationHelper.GetFormStateNode(viewId);
            ReloadSettings();
        }
        public void ReloadSettings()
        {
            ReloadSettingsCore();
            OnSettingsReloaded();
        }
        public virtual void SaveSettings()
        {
            if (modelTemplate != null && IsSizeable)
            {
                formStateModelSynchronizer.SynchronizeModel();
            }
        }
        public virtual void SetStatus(string[] messages) { }
        public virtual void SetStatus(System.Collections.Generic.ICollection<string> statusMessages) { }
        public virtual void SetCaption(string caption) { }
        public IActionContainer DefaultContainer
        {
            get { return actionContainersManager.DefaultContainer; }
        }
        public virtual bool IsSizeable
        {
            get
            {
                return FormBorderStyle == FormBorderStyle.Sizable;
            }
            set
            {
                Rectangle storedBounds = DesktopBounds;
                if (value)
                {
                    FormBorderStyle = FormBorderStyle.Sizable;
                }
                else
                {
                    FormBorderStyle = FormBorderStyle.FixedDialog;
                }
                DesktopBounds = storedBounds;
                MinimizeBox = value;
                MaximizeBox = value;
            }
        }
        public ButtonsContainer ButtonsContainer
        {
            get { return buttonsContainer; }
        }
        public bool AutoShrink
        {
            get { return autoShrink; }
            set { autoShrink = value; }
        }
        public object ViewSiteControl
        {
            get { return viewSitePanel; }
        }
        public Size InitialMinimumSize
        {
            get { return initialMinimumSize; }
            set { initialMinimumSize = value; }
        }
        public event EventHandler<CustomSizeEventArgs> CustomizeClientSize;
        public event EventHandler<CustomSizeEventArgs> CustomizeMinimumSize;
        public event EventHandler BarManagerChanged;
        public event EventHandler SettingsReloaded;
        #region IBarManagerHolder Members

        public DevExpress.XtraBars.BarManager BarManager
        {
            get { return xafBarManager; }
        }

        #endregion

        #region ISupportViewChanged Members

        public event EventHandler<TemplateViewChangedEventArgs> ViewChanged;

        #endregion
    }
}
