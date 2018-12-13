using System;
using System.Drawing;

namespace Tanks.utils
{
    public static partial class Utils
    {
        public static double Range(this Random r, double min, double max)
        {
            return r.NextDouble() * (max - min) + min;
        }

        public static PointF In(this Random r, RectangleF rect)
        {
            return new PointF(
                (float) r.Range(rect.Left, rect.Right),
                (float) r.Range(rect.Top, rect.Bottom)
            );
        }
    }
}