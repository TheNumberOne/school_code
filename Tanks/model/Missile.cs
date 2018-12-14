using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    public class Missile
    {
        public PointF PreviousLocation;
        public PointF Location;
        public PointF Velocity;
        public float Angle { get; set; }
        public Tank Owner { get; set; }
        public Tank Target { get; set; }

        public void CheckCollision(Missile missile, Tank tank)
        {
            throw new NotImplementedException();
        }

        public void Update(TimeSpan deltaT)
        {
            PreviousLocation = Location;

            var t = DetermineTimeToCollision(Location, Velocity, Target.Location, 500, .000001f);

            var futureLocation = Location.Plus(Velocity.Times(t));
            Angle = (float) Math.Atan2(Target.Location.Y - futureLocation.Y, Target.Location.X - futureLocation.X);
            var acceleration = new PointF(500, 0).Rotate(Angle).Times((float) deltaT.TotalSeconds);

            Location = Location.Plus(Velocity.Times((float) deltaT.TotalSeconds)).Plus(acceleration.Times((float) (deltaT.TotalSeconds / 2)));
            Velocity = Velocity.Plus(acceleration);
            
//            Location = Location.Plus(Velocity.Times((float) deltaT.TotalSeconds));
//            Velocity = Velocity.Plus(Target.Location.Plus(Location.Times(-1)).Times((float) deltaT.TotalSeconds));
//            Angle = Math.Atan2(Target.Location.Y - Location.Y, Target.Location.X - Location.X);
        }

        private float DetermineTimeToCollision(PointF start, PointF velocity, PointF target, float acceleration,
            float error)
        {
            var minTime = 0f;
            var maxTime = float.PositiveInfinity;

            while (float.IsPositiveInfinity(maxTime))
            {
                var mid = minTime <= 0 ? 1f : minTime * 2;

                var location = start.Plus(velocity.Times(mid));
                var distance = location.Distance(target);
                var maxDistance = acceleration * mid * mid / 2;

                if (distance < maxDistance)
                {
                    maxTime = mid;
                }
                else if (distance > maxDistance)
                {
                    minTime = mid;
                }
                else
                {
                    return mid - error / 2;
                }
            }

            while (maxTime - minTime > error)
            {
                var mid = (minTime + maxTime) / 2;
                
                var location = start.Plus(velocity.Times(mid));
                var distance = location.Distance(target);
                var maxDistance = acceleration * mid * mid / 2;

                if (distance < maxDistance)
                {
                    maxTime = mid;
                }
                else if (distance > maxDistance)
                {
                    minTime = mid;
                }
                else
                {
                    return mid - error / 2;
                }
            }

            return minTime;
        }
    }
}