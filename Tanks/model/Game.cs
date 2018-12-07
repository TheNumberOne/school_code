using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using Tanks.utils;

namespace Tanks.model
{
    /// <summary>
    /// Represents the current game running.
    /// </summary>
    public class Game
    {
        private const double RockDensity = 30.0 / 1_000_000;

        private const float MinMinRockRadius = 5;
        private const float MaxMinRockRadius = 15;
        private const float MinMaxRadiusMultiple = 1.2f;
        private const float MaxMaxRadiusMultiple = 2;

        public Tank Player { get; } = new Tank()
        {
            Angle = (float) (Math.PI / 4)
        };

        public Rock[] Rocks { get; }
        private Random Random { get; } = new Random();
        private RectangleF Bounds { get; }

        public Game(RectangleF rect)
        {
            Rocks = GenerateRocks(rect, Random).ToArray();
            Bounds = rect;
        }

        private static IEnumerable<Rock> GenerateRocks(RectangleF rect, Random random)
        {
            int numRocks = (int) (RockDensity * rect.Width * rect.Height);
            for (int i = 0; i < numRocks; i++)
            {
                float x = (float) random.Range(rect.Left, rect.Right);
                float y = (float) random.Range(rect.Top, rect.Bottom);      
                float minRadius = (float) random.Range(MinMinRockRadius, MaxMinRockRadius);
                float maxRadiusMultiple = (float) random.Range(MinMaxRadiusMultiple, MaxMaxRadiusMultiple);
                float maxRadius = minRadius * maxRadiusMultiple;

                
                yield return new Rock(
                    new PointF(x, y),
                    random,
                    minRadius,
                    maxRadius
                );
            }
        }


//        public Player Player { get; set; } = new Player()
//        {
//            Tank = new Tank
//            {
//                Center = new Vector
//                {
//                    X = 0,
//                    Y = 0
//                }
//            }
//        };

//        private List<Bullet> Bullets { get; }
//        private List<EnemyTank> Enemies { get; }
//        private List<Missile> Missiles { get; }
//        private List<Rock> Rocks { get; }
//        private Player Player { get; }
//        private int NumEnemies { get; }
//        private TankFactory TankFactory { get; }
//
//        private double BulletLifeTime { get; }
//
        public void Update(TimeSpan deltaT)
        {
            Player.Update(deltaT);
            CenterPlayer();
            WrapStuff();
        }

        private void WrapStuff()
        {
            foreach (Rock r in Rocks)
            {
                WrapPoint(ref r.Center);
            }
        }

        private void WrapPoint(ref PointF p)
        {
            while (p.X < Bounds.Left) p.X += Bounds.Width;
            while (p.X >= Bounds.Right) p.X -= Bounds.Width;
            while (p.Y < Bounds.Top) p.Y += Bounds.Height;
            while (p.Y >= Bounds.Bottom) p.Y -= Bounds.Height;
        }

        private void CenterPlayer()
        {
            PointF deltaP = Player.Location.Times(-1);

            void Transform(ref PointF p) => p = p.Plus(deltaP);

            Transform(ref Player.Location);

            foreach (Rock rock in Rocks)
            {
                Transform(ref rock.Center);
            }
        }

//
//        public void AddBulletAt(Vector location, Vector direction)
//        {
//            throw new NotImplementedException();
//        }
//
//        public void AddMissileAt(Vector location, Vector target)
//        {
//            throw new NotImplementedException();
//        }
//        
//        public void AddRocks(int numRocks)
//        {
//            throw new NotImplementedException();
//        }
//
//        public Game(int numberEnemies, TankFactory tankFactory, double width, double height, double viewWidth, double viewHeight, PlayerOperator playerOperator)
//        {
//            throw new NotImplementedException();
//        }
    }
}