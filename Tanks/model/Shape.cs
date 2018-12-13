using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using MoreLinq;
using Tanks.utils;

namespace Tanks.model
{
    public class Shape
    {
        public Shape(IEnumerable<PointF> points) : this(points.ToArray())
        {
        }

        public Shape(PointF[] points)
        {
            Points = points;
            Edges = new Edge[points.Length];
            
            for (var i = 0; i < points.Length; i++)
            {
                Edges[i] = new Edge
                {
                    P1 = points[i],
                    P2 = points[i + 1 == points.Length ? 0 : i + 1]
                }; 
            }

            for (var i = 0; i < points.Length; i++)
            {
                Edges[i].Prev = Edges[i == 0 ? points.Length - 1 : i - 1];
                Edges[i].Next = Edges[i + 1 == points.Length ? 0 : i + 1];
            }
        }

        public PointF[] Points { get; }

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

            var numIntersect = 0;
            foreach (var edge in Edges)
            {
                var p1Above = edge.P1.Y > p.Y;
                var p2Above = edge.P2.Y > p.Y;

                if (p1Above == p2Above) continue;

                var clockwise = Utils.SignedTriangleArea(edge.P1, p, edge.P2) < 0;

                if (clockwise != p1Above) numIntersect++;
            }

            return numIntersect % 2 == 1;
        }
        
        private Edge[] Edges { get; }

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

        public float MinX()
        {
            return Points.Min(p => p.X);
        }

        public float MaxX()
        {
            return Points.Max(p => p.X);
        }

        public float MinY()
        {
            return Points.Min(p => p.Y);
        }

        public float MaxY()
        {
            return Points.Max(p => p.Y);
        }
    }

    internal class Edge
    {
        public PointF P1 { get; set; }
        public PointF P2 { get; set; }
        public Edge Next { get; set; }
        public Edge Prev { get; set; }

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