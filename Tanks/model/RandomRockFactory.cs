using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using Tanks.utils;

namespace Tanks.model
{
    /// <summary>
    ///     This class is responsible for generating random rocks.
    /// </summary>
    public class RandomRockFactory
    {
        /// <summary>
        ///     The average number of rocks per pixel.
        /// </summary>
        private const double RockDensity = 30.0 / 1_000_000;

        private const float MinMinRockRadius = 5;
        private const float MaxMinRockRadius = 15;
        private const float MinMaxRadiusMultiple = 1.2f;
        private const float MaxMaxRadiusMultiple = 2;
        private const float RockGenerationAngleDelta = Utils.RadiansPerRotation / NumBorderPoints;
        private const int NumBorderPoints = 20;


        public RandomRockFactory(Random random)
        {
            Random = random;
        }

        private Random Random { get; }

        /// <summary>
        ///     Generates a set of rocks in the specified rectangle.
        /// </summary>
        /// <param name="rect"></param>
        /// <returns></returns>
        public IEnumerable<Rock> GenerateRocks(RectangleF rect)
        {
            var numRocks = (int) Math.Round(RockDensity * rect.Width * rect.Height);
            for (var i = 0; i < numRocks; i++)
            {
                var coord = Random.In(rect);
                var minRadius = Random.RangeF(MinMinRockRadius, MaxMinRockRadius);
                var maxRadiusMultiple = Random.RangeF(MinMaxRadiusMultiple, MaxMaxRadiusMultiple);
                var maxRadius = minRadius * maxRadiusMultiple;

                var rockBorder = Smooth(RandomizedCircle(minRadius, maxRadius)).ToArray();
                yield return new Rock(coord, rockBorder);
            }
        }

        /// <summary>
        ///     Creates a random circle of points.
        /// </summary>
        private IEnumerable<PointF> RandomizedCircle(float minRadius, float maxRadius)
        {
            for (float theta = 0; theta < Utils.RadiansPerRotation; theta += RockGenerationAngleDelta)
            {
                var r = Random.RangeF(minRadius, maxRadius);
                yield return Utils.PolarToPointF(theta, r);
            }
        }

        /// <summary>
        ///     Smooths the points by replacing them with the average between every pair.
        /// </summary>
        private static IEnumerable<PointF> Smooth(IEnumerable<PointF> points)
        {
            using (var iter = points.GetEnumerator())
            {
                // Return nothing if there are no points.
                if (!iter.MoveNext()) yield break;

                var first = iter.Current;

                // Return only the first point if there's only one point.
                if (!iter.MoveNext())
                {
                    yield return first;
                    yield break;
                }

                var last = first;

                // Average each pair.
                do
                {
                    yield return Utils.Average(last, iter.Current);
                    last = iter.Current;
                } while (iter.MoveNext());

                // Average the first and last points to wrap around.
                yield return Utils.Average(last, first);
            }
        }
    }
}