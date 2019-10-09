using System;
using System.Drawing;
using System.Linq;
using System.Numerics;
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
        private PointF CalculateThrust() => Utils.PolarToPointF(Angle, MissileAcceleration);

        /// <summary>
        ///     Aims the missile to point at the best place.
        /// </summary>
        private void Aim()
        {
            float t = DetermineTimeToCollision();

            PointF futureLocation = FutureLocation(t);
            PointF targetFutureLocation = Target.FutureLocation(t);
            Angle = (float) Math.Atan2(
                targetFutureLocation.Y - futureLocation.Y,
                targetFutureLocation.X - futureLocation.X
            );
        }

        /// <summary>
        ///     Returns the future location of this missile assuming it doesn't accelerate.
        /// </summary>
        private PointF FutureLocation(float t) => Location.Plus(Velocity.Times(t));

        /// <summary>
        ///     Estimates time to collision assuming that this missile is aimed perfectly.
        /// </summary>
        private float DetermineTimeToCollision()
        {
            PointF location = Location.Minus(Target.Location);
            PointF velocity = Velocity.Minus(Target.Velocity);

            // Derived by hand.
            // Basically, assuming both objects don't accelerate, find the lowest time t where the distance between the
            // this missile and its target is equal to the max amount you can accelerate in that time plus the radius of
            // the target.
            //
            // That can be expressed as the smallest positive real solution of the following equation:
            // distance(Location + Velocity * t, Target.Location + Target.Velocity * t) = MissileAcceleration/2 * t^2 + Target.MinRadius
            // which can be simplified to the smallest positive real root of the following quartic polynomial
            Polynomial poly = new Polynomial(
                Tank.MinRadius * Tank.MinRadius - location.Dot(location),
                -2 * location.Dot(velocity),
                MissileAcceleration * Tank.MinRadius - velocity.Dot(velocity),
                0,
                MissileAcceleration * MissileAcceleration / 4
            );

            Complex[] roots = poly.Roots();

            double t = roots.Where(it => it.IsRealNonNegative()).Min(it => it.Real);
            return (float) t;
        }
    }
}