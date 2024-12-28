using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Collections.Generic;

namespace Player
{

   public class ScreenShot
    {

        public static bool saveToClipboard = false;

        public static void CaptureImage(bool showCursor, Size curSize, Point curPos, Point SourcePoint, Point DestinationPoint, Rectangle SelectionRectangle, string FilePath, string extension)
        {

            using (Bitmap bitmap = new Bitmap(SelectionRectangle.Width, SelectionRectangle.Height))
            {

                using (Graphics g = Graphics.FromImage(bitmap))
                {

                    g.CopyFromScreen(SourcePoint, DestinationPoint, SelectionRectangle.Size);

                    if (showCursor)
                    {

                        Rectangle cursorBounds = new Rectangle(curPos, curSize);
                        Cursors.Default.Draw(g, cursorBounds);

                    }

                }

                if (saveToClipboard)
                {

                    Image img = (Image)bitmap;
                    Clipboard.SetImage(img);

                }
                else
                {

                    switch (extension)
                    {
                        case ".bmp":
                            bitmap.Save(FilePath, ImageFormat.Bmp);
                            break;
                        case ".jpg":
                            bitmap.Save(FilePath, ImageFormat.Jpeg);
                            break;
                        case ".gif":
                            bitmap.Save(FilePath, ImageFormat.Gif);
                            break;
                        case ".tiff":
                            bitmap.Save(FilePath, ImageFormat.Tiff);
                            break;
                        case ".png":
                            bitmap.Save(FilePath, ImageFormat.Png);
                            break;
                        default:
                            bitmap.Save(FilePath, ImageFormat.Jpeg);
                            break;
                    }

                }

            }

        }
        public static Bitmap CaptureImage(Point SourcePoint, Point DestinationPoint, Rectangle SelectionRectangle)
        {
                Bitmap bitmap = new Bitmap(SelectionRectangle.Width, SelectionRectangle.Height);
                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    g.CopyFromScreen(SourcePoint, DestinationPoint, SelectionRectangle.Size);
                }
                
                return bitmap;
         }
        public static Bitmap GetFlushedImage(Size renderingSize, float HorizontalResolution, float VerticalResolution, Point SourcePoint, Point DestinationPoint, Rectangle SelectionRectangle)
        {
            // Returns an image with all drawings flushed, including
            // grids, chronos, magnifier, etc.
            // image should be at same strech factor than the one visible on screen.
            //Size iNewSize = new Size((int)((double)m_FrameServer.CurrentImage.Width * m_FrameServer.CoordinateSystem.Stretch), (int)((double)m_FrameServer.CurrentImage.Height * m_FrameServer.CoordinateSystem.Stretch));


            Bitmap output = new Bitmap(renderingSize.Width, renderingSize.Height, PixelFormat.Format24bppRgb);
            output.SetResolution(HorizontalResolution, VerticalResolution);


            using (Graphics g = Graphics.FromImage(output))
            {
                g.CopyFromScreen(SourcePoint, DestinationPoint, SelectionRectangle.Size);
            }
            return output;
        }
    }
}