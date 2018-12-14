using System;
using Tanks.model;

namespace Tanks.utils
{
    public static partial class Utils
    {
        public const float RadiansPerRotation = (float) (Math.PI * 2);

        /// <summary>
        ///     Get the total seconds of this timespan in single precision floating point.
        ///     (Mainly so we don't have to cast stuff everywhere.
        /// </summary>
        public static float TotalSecondsF(this TimeSpan deltaT)
        {
            return (float) deltaT.TotalSeconds;
        }

        /// <summary>
        ///     Helper method for determining if there is a collision between two collidable objects.
        /// </summary>
        public static bool IsCollision(this ICollidable c1, ICollidable c2)
        {
            return c1.CollisionContainer.IsCollision(c2.CollisionContainer);
        }
    }
}