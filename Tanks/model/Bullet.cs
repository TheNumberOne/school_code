using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc />
    /// <summary>
    ///     This represents a bullet shot by one of the tanks.
    /// </summary>
    public class Bullet : IUpdateable, ICollidable
    {
        public PointF Location;
        public PointF PreviousLocation;
        public PointF Velocity;
        public Tank Firer { get; set; }
        public double LifeTime { get; set; }
        public bool Alive => LifeTime > 0;

        /// <inheritdoc />
        public void Update(TimeSpan t)
        {
            var time = (float) Math.Min(LifeTime, t.TotalSeconds);
            PreviousLocation = Location;
            Location = Location.Plus(Velocity.Times(time));
            LifeTime -= time;
        }

        /// <summary>
        /// Returns a shape representing the line between this bullet and its previous location. This is useful
        /// for collision detection.
        /// </summary>
        public Shape GetMovementLine()
        {
            return new[] {PreviousLocation, Location};
        }

        /// <inheritdoc/>
        public Shape CollisionContainer => new[] {PreviousLocation, Location};
    }
}