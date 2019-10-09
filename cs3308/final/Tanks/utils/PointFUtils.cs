using System;
using System.Drawing;

namespace Tanks.utils
{
    public static partial class Utils
    {
        /// <summary>
        ///     Returns the average between two points.
        /// </summary>
        public static PointF Average(PointF p1, PointF p2) => Slide(p1, p2, f: .5f);

        /// <summary>
        ///     Allows you to specify a location on the line between two points.
        /// </summary>
        public static PointF Slide(PointF p1, PointF p2, float f) => p1.Times(1 - f).Plus(p2.Times(f));

        /// <summary>
        ///     Adds the coordinates of two points.
        /// </summary>
        public static PointF Plus(this PointF p1, PointF p2) => new PointF(p1.X + p2.X, p1.Y + p2.Y);

        /// <summary>
        ///     Subtracts the coordinates of the second from the first.
        /// </summary>
        public static PointF Minus(this PointF p1, PointF p2) => new PointF(p1.X - p2.X, p1.Y - p2.Y);

        /// <summary>
        ///     Multiplies the coordinates of a point.
        /// </summary>
        public static PointF Times(this PointF p, float r) => new PointF(p.X * r, p.Y * r);

        /// <summary>
        ///     Rotates a point around the origin.
        /// </summary>
        public static PointF Rotate(this PointF p, float theta) =>
            new PointF(
                (float) (p.X * Math.Cos(theta) - p.Y * Math.Sin(theta)),
                (float) (p.X * Math.Sin(theta) + p.Y * Math.Cos(theta))
            );


        /// <summary>
        ///     Finds the distance between two points.
        /// </summary>
        public static float Distance(this PointF p1, PointF p2) =>
            (float) Math.Sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));

        /// <summary>
        ///     Converts polar coordinates to a point.
        /// </summary>
        public static PointF PolarToPointF(float angle, float radius) => new PointF(radius, y: 0).Rotate(angle);

        /// <summary>
        ///     Returns twice the triangle area between the 3 points. Positive if counter clockwise.
        ///     Negative if clockwise.
        /// </summary>
        public static float SignedTriangleArea(PointF p1, PointF p2, PointF p3) =>
            (p2.X - p1.X) * (p3.Y - p1.Y) - (p2.Y - p1.Y) * (p3.X - p1.X);

        /// <summary>
        ///     Returns the dot product of two points.
        /// </summary>
        public static float Dot(this PointF p1, PointF p2) => p1.X * p2.X + p1.Y * p2.Y;
    }
}