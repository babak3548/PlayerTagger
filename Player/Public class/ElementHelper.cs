using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.Utils;
using System.Drawing;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraEditors.Controls;
using DevExpress.Xpo;
using DevExpress.XtraGrid.Views.Grid;
using DevExpress.XtraGrid.Columns;
using DevExpress.XtraEditors.DXErrorProvider;
using System.Runtime.InteropServices;
using DevExpress.XtraGrid.Views.Base;
using System.Diagnostics;
using DevExpress.XtraEditors;
using DevExpress.Data.Filtering;
using DevExpress.LookAndFeel;
using DevExpress.Skins;
using DevExpress.Data.Helpers;
using System.Windows.Forms;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;
using System.IO;
using System.Collections;
using System.Data.SqlClient;
using DevExpress.XtraGrid;
using DevExpress.XtraLayout;
using DevExpress.XtraGrid.Localization;

namespace Helpers
{
     public interface IExceptionProcesser {
        void Process(Exception e);
    }
    public class ExceptionsProcesser : IExceptionProcesser {
        IWin32Window owner;
        public ExceptionsProcesser(IWin32Window owner) {
            this.owner = owner;
        }
        public void Process(Exception e) {
            XtraMessageBox.Show(owner, e.Message,"Warning", MessageBoxButtons.OK, MessageBoxIcon.Stop);
        }
    }
    public class WinApiWrapper {
        public static int GetModuleHandle(string moduleName) {
            return Import.GetModuleHandle(moduleName);
        }
        public static Icon ExtractIcon(int hinstance, string file, int iconIndex) {
            return IconFromHandle(Import.ExtractIcon(hinstance, file, iconIndex));
        }
        public static Icon GetIconBySHGetFileInfo(string file, bool small) {
            Import.SHFILEINFO shFileInfo = new Import.SHFILEINFO(true);
            int fileInfoSize = Marshal.SizeOf(shFileInfo);
            Import.SHGFI flags = Import.SHGFI.Icon | (small ? Import.SHGFI.SmallIcon : Import.SHGFI.LargeIcon);
            Import.SHGetFileInfo(file, 0, ref shFileInfo, (uint)fileInfoSize, (uint)flags);
            return IconFromHandle(shFileInfo.Hicon);
        }
        public static string GetTypeNameBySHGetFileInfo(string file) {
            Import.SHFILEINFO shFileInfo = new Import.SHFILEINFO(true);
            int fileInfoSize = Marshal.SizeOf(shFileInfo);
            Import.SHGFI flags = Import.SHGFI.TypeName;
            Import.SHGetFileInfo(file, 0, ref shFileInfo, (uint)fileInfoSize, (uint)flags);
            return shFileInfo.TypeName;
        }
        static Icon IconFromHandle(IntPtr hicon) {
            if(hicon == IntPtr.Zero) return null;
            Icon icon = Icon.FromHandle(hicon);
            Icon ret = new Icon(icon, icon.Size);
            Import.DestroyIcon(hicon);
            return ret;
        }
        class Import {
            [DllImport("Kernel32.dll")]
            public static extern int GetModuleHandle(string moduleName);
            [DllImport("Shell32.dll")]
            public static extern IntPtr ExtractIcon(int hinstance, string file, int iconIndex);
            [DllImport("shell32.dll")]
            public static extern IntPtr SHGetFileInfo(string path, uint fileAttributes, ref SHFILEINFO psfi, uint fileInfo, uint flags);
            [DllImport("user32.dll", SetLastError = true)]
            [return: MarshalAs(UnmanagedType.Bool)]
            public static extern bool DestroyIcon(IntPtr hicon);
            public const int MAX_PATH = 260;
            public const int MAX_TYPE = 80;
            [StructLayout(LayoutKind.Sequential)]
            public struct SHFILEINFO {
                public SHFILEINFO(bool b) {
                    Hicon = IntPtr.Zero;
                    IconIndex = 0;
                    Attributes = 0;
                    DisplayName = string.Empty;
                    TypeName = string.Empty;
                }
                public IntPtr Hicon;
                public int IconIndex;
                public uint Attributes;
                [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PATH)]
                public string DisplayName;
                [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_TYPE)]
                public string TypeName;
            };
            [Flags]
            public enum SHGFI : uint {
                Icon = 0x000000100, DisplayName = 0x000000200, TypeName = 0x000000400, Attributes = 0x000000800, IconLocation = 0x000001000,
                ExeType = 0x000002000, SysIconIndex = 0x000004000, LinkOverlay = 0x000008000, Selected = 0x000010000, AttrSpecified = 0x000020000,
                LargeIcon = 0x000000000, SmallIcon = 0x000000001, OpenIcon = 0x000000002, ShellIconSize = 0x000000004, PIDL = 0x000000008, UseFileAttributes = 0x000000010,
                AddOverlays = 0x000000020, OverlayIndex = 0x000000040
            }
        }
    }
    public class WinHelper {
        //public static void SetFormClientSize(Rectangle workingArea, Form form, int width, int height) {
        //    Size tempSize = DevExpress.Utils.Text.TextUtils. GetScaleSize(new Size(width, height));
        //    width = tempSize.Width;
        //    height = tempSize.Height;
        //    form.ClientSize = new Size(Math.Min(workingArea.Width - 20, width), Math.Min(workingArea.Height - 20, height));
        //    form.Location = new Point(workingArea.X + (workingArea.Width - form.Width) / 2, workingArea.Y + (workingArea.Height - form.Height) / 2);
        //}
    
        public static string ReplaceFilterText(object filter, string sourceString, string retString) {
            string displayFilterText = string.Format("{0}", filter);
            if(displayFilterText.Contains(sourceString))
                return displayFilterText.Replace(sourceString, retString);
            return null;
        }
        static BaseView GetBaseViewByControl(Control control) {
            if(control == null) return null;
            foreach(Control cntl in control.Controls)
                if(cntl is GridControl)
                    return ((GridControl)cntl).MainView;
            return null;
        }
        static LayoutControl GetLayoutControlByControl(Control control) {
            if(control == null) return null;
            foreach(Control cntl in control.Controls)
                if(cntl is LayoutControl)
                    return cntl as LayoutControl;
            return null;
        }
        static void CloseElements(Control control) {
            foreach(Control ctrl in control.Controls)
                CloseElements(ctrl);
            BaseView view = GetBaseViewByControl(control);
            if(view != null) {
                foreach(BaseView bView in view.GridControl.Views)
                    if(bView is GridView)
                        ((GridView)bView).DestroyCustomization();
            }
            LayoutControl layout = GetLayoutControlByControl(control);
            if(layout != null)
                layout.HideCustomizationForm();

        }
     
    
        public static Color GetLinkColor(UserLookAndFeel lookAndFeel) {
            Color color = Color.Empty;
            if(lookAndFeel.ActiveStyle == DevExpress.LookAndFeel.ActiveLookAndFeelStyle.Skin) {
                Skin skin = EditorsSkins.GetSkin(lookAndFeel);
                color = skin.Colors.GetColor(EditorsSkins.SkinHyperlinkTextColor);
            }
            if(color.IsEmpty) color = Color.Blue;
            return color;
        }
    }
    public class ObjectHelper {
        public static void ShowWebSite(string url) {
            if(url == null) return;
            string processName = url.Replace(" ", string.Empty);
            if(processName.Length == 0) return;
            const string protocol = "http://";
            const string protocol2 = "https://";
            if(processName.IndexOf(protocol) != 0 && processName.IndexOf(protocol2) != 0)
                processName = protocol + processName;
            StartProcess(processName);
        }
        public static void StartProcess(string processName) {
            try {
                Process.Start(processName);
            } catch(Exception ex) {
                XtraMessageBox.Show(ex.Message,"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
       
        public static void SetFormContainerSize(Form form, Control control) {
            form.StartPosition = FormStartPosition.Manual;
            form.Size = control.Size;
            form.Location = control.FindForm().PointToScreen(control.Location);
        }
        public static void ShowFormDialog(Form form, Form parent) {
            try {
                parent.Enabled = false;
                form.ShowDialog(parent);
            } finally {
                parent.Enabled = true;
            }
        }
        public static void OpenExportedFile(string fileName) {
            if(XtraMessageBox.Show("ExportFileOpen", "Export", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                Process process = new Process();
                try {
                    process.StartInfo.FileName = fileName;
                    process.Start();
                } catch { }
            }
        }
        public static void ShowExportErrorMessage() {
            XtraMessageBox.Show("ExportError", "Export", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        public static string GetPossibleFileName(string name) { return name.Replace("/", ""); }
        public static string GetFileName(string extension, string filter) { return GetFileName(extension, filter, string.Empty); }
        public static string GetFileName(string extension, string filter, string fileName) {
            using(SaveFileDialog dialog = new SaveFileDialog()) {
                dialog.Filter = filter;
                dialog.FileName = fileName;
                dialog.DefaultExt = extension;
                if(dialog.ShowDialog() == DialogResult.OK)
                    return dialog.FileName;
            }
            return String.Empty;
        }
        public static void RemoveCustomizationItemsFromColumnMenu(DevExpress.XtraGrid.Views.Grid.PopupMenuShowingEventArgs e) {
            if(e.MenuType == DevExpress.XtraGrid.Views.Grid.GridMenuType.Column)
                for(int i = e.Menu.Items.Count - 1; i >= 0; i--)
                    if(GridStringId.MenuColumnColumnCustomization.Equals(e.Menu.Items[i].Tag) ||
                        GridStringId.MenuColumnRemoveColumn.Equals(e.Menu.Items[i].Tag))
                        e.Menu.Items.RemoveAt(i);
        }

        internal static string GetArticleByWord(string word) {
            if(string.IsNullOrEmpty(word)) return string.Empty;
            string firstLetter = word.Substring(0, 1).ToLower();
            if(firstLetter == "a") return "an";
            return "a";
        }
    }
    public enum ImageSize { Small16, Large32 }
    public class ElementHelper {
        static ImageCollection receiptTypeImages = null;
        static ImageCollection activeRentTypeImages = null;
        static ImageCollection folderIcons = null;
        static ImageCollection columnHeaderIcons = null;
        static Icon appIcon = null;
        public static Image GetImage(string name, ImageSize size) {
            if(string.IsNullOrEmpty(name)) return null;
            return ResourceImageHelper.CreateImageFromResources(
                string.Format("DevExpress.VideoRent.Resources.SingleImages.{0}_{1}.png", name, GetImageSizeString(size)),
                typeof(ImagesHelper).Assembly);
        }
        public static Image GetAboutPageImage(string name) {
            if(string.IsNullOrEmpty(name)) return null;
            return ResourceImageHelper.CreateImageFromResources(
                string.Format("DevExpress.VideoRent.Resources.AboutPage.{0}.png", name),
                typeof(ImagesHelper).Assembly);
        }
        public static Image GetGroupImage(string name) {
            if(name == null || name == string.Empty) return null;
            return ResourceImageHelper.CreateImageFromResources(
                string.Format("DevExpress.VideoRent.Resources.SingleImages.Group_{0}.png", name),
                typeof(ImagesHelper).Assembly);
        }

        static string GetImageSizeString(ImageSize size) {
            if(size == ImageSize.Small16) return "16x16";
            return "32x32";
        }
        public static ImageCollection ReceiptTypeImages {
            get {
                if(ElementHelper.receiptTypeImages == null)
                    ElementHelper.receiptTypeImages = DevExpress.Utils.Controls.ImageHelper.CreateImageCollectionFromResources("DevExpress.VideoRent.Resources.Images.ReceiptType.png", typeof(ImagesHelper).Assembly, new Size(16, 16));
                return ElementHelper.receiptTypeImages;
            }
        }
        public static ImageCollection ActiveRentTypeImages {
            get {
                if(ElementHelper.activeRentTypeImages == null)
                    ElementHelper.activeRentTypeImages = DevExpress.Utils.Controls.ImageHelper.CreateImageCollectionFromResources("DevExpress.VideoRent.Resources.Images.ActiveRents.png", typeof(ImagesHelper).Assembly, new Size(16, 16));
                return ElementHelper.activeRentTypeImages;
            }
        }
        public static ImageCollection FolderIcons {
            get {
                if(ElementHelper.folderIcons == null)
                    ElementHelper.folderIcons = DevExpress.Utils.Controls.ImageHelper.CreateImageCollectionFromResources("DevExpress.VideoRent.Resources.Images.FolderIcons16x16.png", typeof(ImagesHelper).Assembly, new Size(16, 16));
                return ElementHelper.folderIcons;
            }
        }
        public static ImageCollection ColumnHeaderIcons {
            get {
                if(ElementHelper.columnHeaderIcons == null)
                    ElementHelper.columnHeaderIcons = DevExpress.Utils.Controls.ImageHelper.CreateImageCollectionFromResources("DevExpress.VideoRent.Resources.Images.ColumnHeaderImages.png", typeof(ImagesHelper).Assembly, new Size(13, 13));
                return ElementHelper.columnHeaderIcons;
            }
        }
        public static Icon AppIcon {
            get {
                if(ElementHelper.appIcon == null)
                    ElementHelper.appIcon = ResourceImageHelper.CreateIconFromResources("DevExpress.VideoRent.Win.AppIcon.ico", typeof(ElementHelper).Assembly);
                return ElementHelper.appIcon;
            }
        }
#if DebugTest
        static ImageCollection imagesForTests = null;
        public static ImageCollection ImagesForTests {
            get {
                if(ElementHelper.imagesForTests == null)
                    ElementHelper.imagesForTests = DevExpress.Utils.Controls.ImageHelper.CreateImageCollectionFromResources("DevExpress.VideoRent.Resources.Images.FolderIcons16x16.png", typeof(ImagesHelper).Assembly, new Size(16, 16));
                return ElementHelper.imagesForTests;
            }
        }
#endif
        public static Font FontItalic = new Font("Tahoma", 8, FontStyle.Italic);
        public static Font FontBold = new Font("Tahoma", 8, FontStyle.Bold);
        public static string GetSingleLineString(string text) {
            int index = text.IndexOf("\r\n");
            if(index != -1)
                return text.Substring(0, index);
            return text;
        }
    }
    public class BackstageViewLabel : LabelControl {
        public BackstageViewLabel() {
            Appearance.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            //Appearance.ForeColor = System.Drawing.Color.Gray;
            AutoSizeMode = DevExpress.XtraEditors.LabelAutoSizeMode.None;
            //LineColor = System.Drawing.Color.Silver;
            LineLocation = DevExpress.XtraEditors.LineLocation.Bottom;
            LineStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            LineVisible = true;
            LookAndFeel.Style = DevExpress.LookAndFeel.LookAndFeelStyle.Flat;
            LookAndFeel.UseDefaultLookAndFeel = false;
            ShowLineShadow = false;
        }
    }
    public class ValidationRulesHelper {
        static ConditionValidationRule ruleIsNotBlank = null;
        static ConditionValidationRule ruleGreaterOrEqualZero = null;
        public static ConditionValidationRule RuleIsNotBlank {
            get {
                if(ruleIsNotBlank == null) {
                    ruleIsNotBlank = new ConditionValidationRule();
                    ruleIsNotBlank.ConditionOperator = ConditionOperator.IsNotBlank;
                    ruleIsNotBlank.ErrorText = "RuleIsNotBlankWarning";
                    ruleIsNotBlank.ErrorType = ErrorType.Critical;
                }
                return ruleIsNotBlank;
            }
        }
        public static ConditionValidationRule RuleGreaterOrEqualZero {
            get {
                if(ruleGreaterOrEqualZero == null) {
                    ruleGreaterOrEqualZero = new ConditionValidationRule();
                    ruleGreaterOrEqualZero.ConditionOperator = ConditionOperator.GreaterOrEqual;
                    ruleGreaterOrEqualZero.Value1 = 0;
                    ruleGreaterOrEqualZero.ErrorText = "RuleGreaterOrEqualZeroWarning";
                    ruleGreaterOrEqualZero.ErrorType = ErrorType.Critical;
                }
                return ruleGreaterOrEqualZero;
            }
        }
        public static ConditionValidationRule RuleGreaterOrEqual(int value) {
            ConditionValidationRule ret = new ConditionValidationRule();
            ret.ConditionOperator = ConditionOperator.GreaterOrEqual;
            ret.Value1 = value;
            ret.ErrorText = "RuleGreaterOrEqualZeroWarning";
            ret.ErrorType = ErrorType.Critical;
            return ret;
        }
    }
    public class EditorHelper {
        public static RepositoryItemTextEdit CreateCardNumberTextEdit(RepositoryItemCollection collection) {
            return CreateCardNumberTextEdit(null, collection);
        }
        public static RepositoryItemTextEdit CreateCardNumberTextEdit(RepositoryItemTextEdit edit, RepositoryItemCollection collection) {
            RepositoryItemTextEdit ret = edit == null ? new RepositoryItemTextEdit() : edit;
            if(collection != null) collection.Add(ret);
            ret.Mask.EditMask = "d6";
            ret.Mask.MaskType = DevExpress.XtraEditors.Mask.MaskType.Numeric;
            ret.Mask.UseMaskAsDisplayFormat = true;
            return ret;
        }
        public static RepositoryItemTextEdit CreatePaymentTextEdit(RepositoryItemCollection collection) {
            RepositoryItemTextEdit ret = new RepositoryItemTextEdit();
            if(collection != null) collection.Add(ret);
            ret.Mask.EditMask = "c";
            ret.Mask.MaskType = DevExpress.XtraEditors.Mask.MaskType.Numeric;
            ret.Mask.UseMaskAsDisplayFormat = true;
            return ret;
        }
     
  
      
       
    }
    public class ColorHelper {
        public static void UpdateColor(ImageCollection collection, UserLookAndFeel lf) {
            for(int i = 0; i < collection.Images.Count; i++)
                collection.Images[i] = SetColor(collection.Images[i] as Bitmap, GetHeaderForeColor(lf));
        }
        public static Color GetHeaderForeColor(UserLookAndFeel lf) {
            Color ret = SystemColors.ControlText;
            if(lf.ActiveStyle != ActiveLookAndFeelStyle.Skin) return ret;
            return GridSkins.GetSkin(lf)[GridSkins.SkinHeader].Color.GetForeColor();
        }
        static Bitmap SetColor(Bitmap bmp, Color color) {
            for(int i = 0; i < bmp.Width; i++)
                for(int j = 0; j < bmp.Height; j++)
                    if(bmp.GetPixel(i, j).Name != "0")
                        bmp.SetPixel(i, j, color);
            return bmp;
        }
    }
    public class ImageCreator {
        public static Image CreateImage(Image srcImage, int maxWidth, int maxHeight) {
            if(srcImage == null) return null;
            Size size = GetPhotoSize(srcImage, maxWidth, maxHeight);
            Image ret = new Bitmap(size.Width, size.Height);
            using(Graphics gr = Graphics.FromImage(ret)) {
                gr.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                gr.DrawImage(srcImage, new Rectangle(0, 0, size.Width, size.Height));
            }
            return ret;
        }
        static Size GetPhotoSize(Image image, int maxWidth, int maxHeight) {
            int width = Math.Min(maxWidth, image.Width),
                height = width * image.Height / image.Width;
            if(height > maxHeight) {
                height = maxHeight;
                width = height * image.Width / image.Height;
            }
            return new Size(width, height);
        }
        public static Rectangle GetZoomDestRectangle(Rectangle r, Image img) {
            float horzRatio = Math.Min((float)r.Width / img.Width, 1);
            float vertRatio = Math.Min((float)r.Height / img.Height, 1);
            float zoomRatio = Math.Min(horzRatio, vertRatio);

            return new Rectangle(
                r.Left + (int)(r.Width - img.Width * zoomRatio) / 2,
                r.Top + (int)(r.Height - img.Height * zoomRatio) / 2,
                (int)(img.Width * zoomRatio),
                (int)(img.Height * zoomRatio));
        }
    }
    public class DateHelper {
        public static DateTime GetStartDateForMonths(int count) {
            DateTime dt = DateTime.Now.AddMonths(count);
            return new DateTime(dt.Year, dt.Month, 1);
        }
    }
}
