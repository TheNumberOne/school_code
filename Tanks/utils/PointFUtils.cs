using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using MoreLinq;

namespace Tanks.utils
{
    public static partial class Utils
    {
        public static PointF Origin { get; } = new PointF(0, 0);

        public static PointF Average(PointF p1, PointF p2)
        {
            return Slide(p1, p2, .5f);
        }

        public static PointF Slide(PointF p1, PointF p2, float f)
        {
            return p1.Times(1 - f).Plus(p2.Times(f));
        }

        public static PointF Plus(this PointF p1, PointF p2)
        {
            return new PointF(p1.X + p2.X, p1.Y + p2.Y);
        }

        public static PointF Times(this PointF p, float r)
        {
            return new PointF(p.X * r, p.Y * r);
        }

        public static PointF Rotate(this PointF p, float theta)
        {
            return new PointF(
                (float) (p.X * Math.Cos(theta) - p.Y * Math.Sin(theta)),
                (float) (p.X * Math.Sin(theta) + p.Y * Math.Cos(theta))
            );
        }

        /// <summary>
        /// Returns the convex hull of the points. Uses: https://en.wikipedia.org/wiki/Graham_scan
        /// </summary>
        /// <param name="points"></param>
        /// <returns></returns>
        public static PointF[] ConvexHull(PointF[] points)
        {
            if (points.Length < 3) return points;

            PointF[] ps = points.ToArray();
            int smallestIndex = Enumerable.Range(0, ps.Length).MinBy(i => ps[i].Y).First();

            (ps[smallestIndex], ps[0]) = (ps[0], ps[smallestIndex]);
           

            Array.Sort(ps, 1, ps.Length - 1, Comparer<PointF>.Create((a, b) =>
            {
                float slope1 = (a.X - ps[0].X) / (a.Y - ps[0].Y);
                float slope2 = (b.X - ps[0].X) / (b.Y - ps[0].Y);
                return Math.Sign(slope2 - slope1);
            }));

            Stack<PointF> hull = new Stack<PointF>();
            hull.Push(ps[0]);
            hull.Push(ps[1]);
            hull.Push(ps[2]);

            for (int i = 3; i < ps.Length; i++)
            {
                while (true)
                {
                    PointF top = hull.Pop();
                    if (CounterClockWiseness(top, hull.Peek(), ps[i]) > 0) continue;
                    
                    hull.Push(top);
                    break;
                }

                hull.Push(ps[i]);
            }

            return hull.ToArray();
        }

        /// <summary>
        /// Calculates whether the three points are counter clockwise or not.
        /// Returns &gt; 0 if counter clockwise.
        /// Returns &lt; 0 if clockwise.
        /// Returns 0 if collinear.
        /// </summary>
        public static float CounterClockWiseness(PointF p1, PointF p2, PointF p3)
        {
            return (p2.X - p1.X) * (p3.Y - p1.Y) - (p2.Y - p1.Y) * (p3.X - p1.X);
        }
    }
}