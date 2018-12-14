using System;
using System.Drawing;

namespace Tanks.utils
{
    public static partial class Utils
    {
        /// <summary>
        ///     Returns a random floating point number in the specified range.
        /// </summary>
        public static float RangeF(this Random r, float min, float max) => (float) r.NextDouble() * (max - min) + min;

        /// <summary>
        ///     Returns a random point in the specified rectangle.
        /// </summary>
        public static PointF In(this Random r, RectangleF rect)
        {
            return new PointF(
                r.RangeF(rect.Left, rect.Right),
                r.RangeF(rect.Top, rect.Bottom)
            );
        }

        /// <summary>
        ///     Returns a random angle.
        /// </summary>
        public static float RandomAngleF(this Random random) => random.RangeF(0, RadiansPerRotation);
    }
}