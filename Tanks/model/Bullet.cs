using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tanks.model;

namespace Tanks
{
    /// <summary>
    /// This represents a bullet shot by one of the tanks.
    /// </summary>
    public class Bullet
    {
        public Vector Location { get; }
        private Vector Velocity { get; }
        private double LifeTime { get; }
        public bool Alive { get; }

        public Bullet(Point location, Point velocity, double lifeTime)
        {
            throw new NotImplementedException();
        }

        public void Update(double deltaT)
        {
            throw new NotImplementedException();
        }

        public bool CheckCollision(Missile missile)
        {
            throw new NotImplementedException();
        }
        public bool CheckCollision(Rock missile)
        {
            throw new NotImplementedException();
        }
        public bool CheckCollision(Tank missile)
        {
            throw new NotImplementedException();
        }
    }
}
