using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tanks.utils;

namespace Tanks.model
{
    public class Shape
    {
        public PointF[] Points { get; }

        public Shape(IEnumerable<PointF> points) : this(points.ToArray()) { }

        public Shape(PointF[] points)
        {
            Points = points;
        }

        public Shape Transform(Func<PointF, PointF> t)
        {
            return new Shape(Points.Select(t));
        }

        public static implicit operator PointF[](Shape s) => s.Points;
        public static implicit operator Shape(PointF[] ps) => new Shape(ps);

        public bool IsCollision(Shape other)
        {
            // Basic bounds check.
            if (MaxX() < other.MinX() ||
                other.MaxX() < MinX() ||
                MaxY() < other.MinY() ||
                other.MaxY() < MinY())
            {
                return false;
            }

            return true;
        }

        public float MinX() => Points.Min(p => p.X);
        public float MaxX() => Points.Max(p => p.X);
        public float MinY() => Points.Min(p => p.Y);
        public float MaxY() => Points.Max(p => p.Y);
    }
}
