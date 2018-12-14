using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc cref="IUpdateable" />
    /// <inheritdoc cref="ICollidable" />
    /// <summary>
    ///     This represents a bullet shot by one of the tanks.
    /// </summary>
    public class Bullet : IUpdateable, ICollidable
    {
        private PointF _previousLocation;
        public PointF Location;
        public PointF Velocity;
        public Tank Firer { get; set; }
        public double LifeTime { get; set; }
        public bool Alive => LifeTime > 0;

        /// <inheritdoc />
        public Shape CollisionContainer => new[] {_previousLocation, Location};

        /// <inheritdoc />
        public void Update(TimeSpan t)
        {
            var time = (float) Math.Min(LifeTime, t.TotalSeconds);
            _previousLocation = Location;
            Location = Location.Plus(Velocity.Times(time));
            LifeTime -= time;
        }
    }
}