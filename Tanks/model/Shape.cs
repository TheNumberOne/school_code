using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using Tanks.utils;

namespace Tanks.model
{
    public class Shape
    {
        private Shape(IEnumerable<PointF> points) : this(points.ToArray())
        {
        }

        private Shape(PointF[] points)
        {
            Points = points;
            Edges = new Edge[points.Length];

            for (var i = 0; i < points.Length; i++)
                Edges[i] = new Edge
                {
                    P1 = points[i],
                    P2 = points[i + 1 == points.Length ? 0 : i + 1]
                };
        }

        private PointF[] Points { get; }

        private Edge[] Edges { get; }

        public Shape Transform(Func<PointF, PointF> t)
        {
            return new Shape(Points.Select(t));
        }

        public static implicit operator PointF[](Shape s)
        {
            return s.Points;
        }

        public static implicit operator Shape(PointF[] ps)
        {
            return new Shape(ps);
        }

        public bool IsCollision(Shape other)
        {
            // Basic bounds check.
            if (MaxX() < other.MinX() ||
                other.MaxX() < MinX() ||
                MaxY() < other.MinY() ||
                other.MaxY() < MinY())
                return false;

            return Edges.Any(e1 => other.Edges.Any(e1.IsCollision));
        }

        public bool ContainsPoint(PointF p)
        {
            if (MaxX() < p.X ||
                p.X < MinX() ||
                MaxY() < p.Y ||
                p.Y < MinY())
                return false;

            var numIntersect = (from edge in Edges
                let p1Above = edge.P1.Y > p.Y
                let p2Above = edge.P2.Y > p.Y
                where p1Above != p2Above
                let clockwise = Utils.SignedTriangleArea(edge.P1, p, edge.P2) < 0
                where clockwise != p1Above
                select p1Above).Count();

            return numIntersect % 2 == 1;
        }

        public PointF Center()
        {
            return new PointF(
                Points.Average(p => p.X),
                Points.Average(p => p.Y)
            );
        }

        public float MaxRadius()
        {
            var c = Center();
            return Points.Max(p => p.Distance(c));
        }

        private float MinX()
        {
            return Points.Min(p => p.X);
        }

        private float MaxX()
        {
            return Points.Max(p => p.X);
        }

        private float MinY()
        {
            return Points.Min(p => p.Y);
        }

        private float MaxY()
        {
            return Points.Max(p => p.Y);
        }
    }

    internal class Edge
    {
        public PointF P1 { get; set; }
        public PointF P2 { get; set; }

        public bool IsCollision(Edge other)
        {
            var a1 = Utils.SignedTriangleArea(P1, P2, other.P2);
            var a2 = Utils.SignedTriangleArea(P1, P2, other.P1);
            if (a1 * a2 >= 0) return false;
            var a3 = Utils.SignedTriangleArea(other.P1, other.P2, P1);
            //float a4 = Utils.SignedTriangleArea(other.P1, other.P2, P2);
            var a4 = a3 + a2 - a1;

            return a3 * a4 < 0;
        }
    }
}