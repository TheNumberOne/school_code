using System;
using System.Drawing;

namespace Tanks.model
{
    public class Missile
    {
        public PointF Location;
        public PointF Velocity;
        public double Angle { get; set; }
        public Tank Owner { get; set; }
        public Tank Target { get; set; }

        public void CheckCollision(Missile missile, Tank tank)
        {
            throw new NotImplementedException();
        }

        public void Update(double deltaT)
        {
            throw new NotImplementedException();
        }
    }
}