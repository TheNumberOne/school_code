using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tanks.model;

namespace Tanks
{
    public class Missile
    {
        public Vector Location { get; }
        private Vector Velocity { get; }
        public Shape Shape { get; }
        public double Angle { get; }

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
