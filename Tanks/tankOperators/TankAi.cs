using System;
using Tanks.model;
using Tanks.utils;

namespace Tanks.tankOperators
{
    public class TankAi
    {
        public Tank Tank { get; set; }
        public Game Game { get; set; }

        public void Update(TimeSpan deltaT)
        {
            if (Utils.SignedTriangleArea(Tank.Location, Tank.Gun, Game.Player.Location) > 0)
            {
                Tank.Rotation = Tank.RotationClockwise;
            }
            else
            {
                Tank.Rotation = Tank.RotationCounterclockwise;
            }

            Tank.Movement = Tank.MoveForward;
            Tank.Shoot();
        }
    }
}