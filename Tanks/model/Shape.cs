using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using Tanks.utils;

namespace Tanks.model
{
    /// <summary>
    ///     This is a shape used mainly for collision detection. Has the unique property that it will easily convert
    ///     back and forth between an array of points.
    /// </summary>
    public class Shape
    {
        private Shape(IEnumerable<PointF> points) : this(points.ToArray())
        {
        }

        private Shape(PointF[] points)
        {
            Points = points;
            Edges = Edge.EdgesFrom(points);
        }

        private PointF[] Points { get; }

        private Edge[] Edges { get; }

        /// <summary>
        ///     Transforms every point in the shape by the function.
        /// </summary>
        public Shape Transform(Func<PointF, PointF> t)
        {
            return new Shape(Points.Select(t));
        }

        /// <summary>
        ///     Allows automatic conversion of a shape to an array of points.
        /// </summary>
        public static implicit operator PointF[](Shape s)
        {
            return s.Points;
        }

        /// <summary>
        ///     Allows automatic conversion of an array of points to a shape.
        /// </summary>
        /// <param name="ps"></param>
        /// <returns></returns>
        public static implicit operator Shape(PointF[] ps)
        {
            return new Shape(ps);
        }

        /// <summary>
        ///     Determines if there's a collision between two shapes.
        /// </summary>
        public bool IsCollision(Shape other)
        {
            return CheckBoundingBoxCollision(other) && Edges.Any(e1 => other.Edges.Any(e1.IsCollision));
        }

        /// <summary>
        ///     Checks if the bounding boxed between two shapes collides.
        /// </summary>
        private bool CheckBoundingBoxCollision(Shape other)
        {
            return !(MaxX() < other.MinX() || other.MaxX() < MinX() || MaxY() < other.MinY() || other.MaxY() < MinY());
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

    /// <summary>
    ///     A simple object to help assist shapes in collision detection.
    /// </summary>
    internal class Edge
    {
        private PointF P1 { get; }
        private PointF P2 { get; }

        private Edge(PointF p1, PointF p2)
        {
            P1 = p1;
            P2 = p2;
        }

        /// <summary>
        ///     Determines if there's a collision between the two edges.
        /// </summary>
        public bool IsCollision(Edge other)
        {
            // I don't remember where I got this formula from :(
            var a1 = Utils.SignedTriangleArea(P1, P2, other.P2);
            var a2 = Utils.SignedTriangleArea(P1, P2, other.P1);
            if (a1 * a2 >= 0) return false;
            var a3 = Utils.SignedTriangleArea(other.P1, other.P2, P1);
            
            //float a4 = Utils.SignedTriangleArea(other.P1, other.P2, P2);
            var a4 = a3 + a2 - a1;

            return a3 * a4 < 0;
        }

        /// <summary>
        ///     Returns a list of edges from the specified points.
        /// </summary>
        public static Edge[] EdgesFrom(IReadOnlyList<PointF> points)
        {
            var edges = new Edge[points.Count];

            for (var i = 0; i < points.Count; i++)
                edges[i] = new Edge(
                    points[i],
                    points[i + 1 == points.Count ? 0 : i + 1] // wrap around to front
                );
            return edges;
        }
    }
}