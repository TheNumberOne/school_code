using System;
using System.Drawing;
using System.Linq;
using MathNet.Numerics;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc cref="IUpdateable" />
    /// <inheritdoc cref="ICollidable" />
    /// <summary>
    ///     Represents a missile in the game.
    /// </summary>
    public class Missile : IUpdateable, ICollidable
    {
        private const float MissileAcceleration = 500;
        private PointF _previousLocation;
        public PointF Location;
        public PointF Velocity;
        public float Angle { get; set; }

        /// <summary>
        ///     The tank that fired this missile.
        /// </summary>
        public Tank Firer { get; set; }

        /// <summary>
        ///     The tank this missile is targeting.
        /// </summary>
        public Tank Target { get; set; }

        /// <inheritdoc />
        public Shape CollisionContainer => new[] {_previousLocation, Location};

        /// <inheritdoc />
        public void Update(TimeSpan deltaT)
        {
            _previousLocation = Location;

            Aim();
            ApplyThrust(deltaT, CalculateThrust());
        }

        /// <summary>
        ///     Applies the specified amount of thrust for the specified amount of time.
        /// </summary>
        private void ApplyThrust(TimeSpan deltaT, PointF thrust)
        {
            Location = Location
                .Plus(Velocity.Times(deltaT.TotalSecondsF()))
                .Plus(thrust.Times(deltaT.TotalSecondsF() * deltaT.TotalSecondsF() / 2));
            Velocity = Velocity.Plus(thrust.Times(deltaT.TotalSecondsF()));
        }

        /// <summary>
        ///     Calculates the current thrust.
        /// </summary>
        private PointF CalculateThrust()
        {
            return new PointF(MissileAcceleration, 0).Rotate(Angle);
        }

        /// <summary>
        ///     Aims the missile to point at the best place.
        /// </summary>
        private void Aim()
        {
            var t = DetermineTimeToCollision();

            var futureLocation = FutureLocation(t);
            Angle = (float) Math.Atan2(Target.Location.Y - futureLocation.Y, Target.Location.X - futureLocation.X);
        }

        /// <summary>
        ///     Returns the future location of this missile assuming it doesn't accelerate.
        /// </summary>
        private PointF FutureLocation(float t)
        {
            return Location.Plus(Velocity.Times(t));
        }

        /// <summary>
        ///     Estimates time to collision assuming that this missile is aimed perfectly.
        /// </summary>
        private float DetermineTimeToCollision()
        {
            var location = Location.Minus(Target.Location);

            // Derived by hand.
            // ||p+vt|| is the distance to the origin at time t assuming a straight line.
            // at^2/2 is the distance it's possible to travel through acceleration
            // so we want to look for where they are equal: 
            // ||p+vt|| = at^2/2
            // (p+vt).(p+vt) = a^2t^4/4
            // (a^2/4)t^4 - (v.v)t^2 - 2(p.v)t - p.p = 0
            var poly = new Polynomial(
                -location.Dot(location), // -p.p
                -2 * location.Dot(Velocity), // -2p.v
                -Velocity.Dot(Velocity), // -v.v
                0,
                MissileAcceleration * MissileAcceleration / 4 // a^2 / 4
            );

            var roots = poly.Roots();

            var t = roots.Where(it => it.IsRealNonNegative()).Min(it => it.Real);
            return (float) t;
        }
    }
}