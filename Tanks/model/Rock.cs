using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using Tanks.utils;

namespace Tanks.model
{
    public class Rock
    {
        private const int NumBorderPoints = 20;
        private const float RockGenerationAngleDelta = (float) (2 * Math.PI / NumBorderPoints);

        public Rock(PointF center, Random r, float minRadius, float maxRadius)
        {
            Center = center;

            Prototype = Smooth(RandomRock(r, minRadius, maxRadius)).ToArray();
        }

        public PointF Center;
        public float Angle { get; set; }

        private Shape Prototype { get; }
        public Shape Border => Prototype.Transform(p => p.Rotate(Angle).Plus(Center));

        private static IEnumerable<PointF> RandomRock(Random rand, float minRadius, float maxRadius)
        {
            for (float theta = 0; theta < 2 * Math.PI; theta += RockGenerationAngleDelta)
            {
                float r = (float) (rand.NextDouble() * (maxRadius - minRadius) + minRadius);
                yield return new PointF(r, 0).Rotate(theta);
            }
        }

        private static IEnumerable<PointF> Smooth(IEnumerable<PointF> points)
        {
            using (IEnumerator<PointF> iter = points.GetEnumerator())
            {
                if (!iter.MoveNext()) yield break;

                PointF first = iter.Current;

                if (!iter.MoveNext())
                {
                    yield return first;
                    yield break;
                }

                PointF last = iter.Current;

                yield return Utils.Average(first, last);

                do
                {
                    yield return Utils.Average(last, iter.Current);
                    last = iter.Current;
                } while (iter.MoveNext());

                yield return Utils.Average(last, first);
            }
        }
    }
}