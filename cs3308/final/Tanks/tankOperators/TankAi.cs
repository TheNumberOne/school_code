using System;
using Tanks.model;
using Tanks.utils;

namespace Tanks.tankOperators
{
    /// <inheritdoc />
    /// <summary>
    ///     A simple ai for our enemy tanks.
    /// </summary>
    public class TankAi : IUpdateable
    {
        public Tank Tank { get; set; }
        public Game Game { get; set; }

        /// <inheritdoc />
        public void Update(TimeSpan deltaT)
        {
            Tank.Rotation = Utils.SignedTriangleArea(Tank.Location, Tank.Gun, Game.Player.Location) > 0
                ? Tank.RotationClockwise
                : Tank.RotationCounterclockwise;

            Tank.Movement = Tank.MoveForward;
            Tank.Shoot();
        }
    }
}