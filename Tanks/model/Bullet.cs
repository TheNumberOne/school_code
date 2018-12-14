using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    /// <summary>
    ///     This represents a bullet shot by one of the tanks.
    /// </summary>
    public class Bullet : IUpdateable
    {
        public PointF Location;
        public PointF PreviousLocation;
        public PointF Velocity;
        public Tank Firer { get; set; }
        public double LifeTime { get; set; }
        public bool Alive => LifeTime > 0;

        public void Update(TimeSpan t)
        {
            var time = (float) Math.Min(LifeTime, t.TotalSeconds);
            PreviousLocation = Location;
            Location = Location.Plus(Velocity.Times(time));
            LifeTime -= time;
        }

        public Shape GetMovementLine()
        {
            return new[] {PreviousLocation, Location};
        }
    }
}