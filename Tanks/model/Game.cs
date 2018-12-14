using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Timers;
using MoreLinq;
using Tanks.tankOperators;
using Tanks.utils;

namespace Tanks.model
{
    /// <summary>
    ///     Represents the current game running.
    /// </summary>
    public class Game
    {
        private const double RockDensity = 30.0 / 1_000_000;

        private const float MinMinRockRadius = 5;
        private const float MaxMinRockRadius = 15;
        private const float MinMaxRadiusMultiple = 1.2f;
        private const float MaxMaxRadiusMultiple = 2;
        private int NumEnemies { get; set; } = 1;

        public Game(RectangleF rect)
        {
            Rocks = GenerateRocks(rect, Random).ToArray();
            Bounds = rect;
            Player = GenerateRandomTank();
            Player.SecondsBetweenShots = .1f;
            Player.OnFireMissile += Missiles.Add;

            var t = new Timer
            {
                Interval = 10_000,
                AutoReset = true,
                
                Enabled = true
            };
            t.Elapsed += (sender, args) => NumEnemies++;

            AddEnemyTanks();
            CenterPlayer();
            WrapStuff();
        }

        public Rock[] Rocks { get; }
        private Random Random { get; } = new Random();
        private RectangleF Bounds { get; }
        public Tank Player { get; }
        public List<Bullet> Bullets { get; } = new List<Bullet>();
        public List<Tank> Enemies { get; } = new List<Tank>();
        public IEnumerable<Tank> Tanks => Enemies.Append(Player);
        public int Score { get; private set; }
        public List<Missile> Missiles { get; } = new List<Missile>();
        private List<TankAi> AIs { get; } = new List<TankAi>();


        public bool IsOver => !Player.IsAlive;

        private void AddEnemyTanks()
        {
            while (Enemies.Count < NumEnemies)
            {
                var enemy = GenerateRandomEnemy();
                AIs.Add(new TankAi { Tank = enemy, Game = this });
                Enemies.Add(enemy);
            }
        }

        private Tank GenerateRandomTank()
        {
            var tank = new Tank {Angle = (float) (Math.PI * 2 * Random.NextDouble())};
            tank.OnShoot += Bullets.Add;

            do
            {
                tank.Location = Random.In(Bounds);
            } while (IsCollidedWithRocks(tank));

            return tank;
        }

        private Tank GenerateRandomEnemy()
        {
            var tank = new Tank {Angle = (float) (Math.PI * 2 * Random.NextDouble())};
            tank.OnShoot += Bullets.Add;
            tank.SecondsBetweenShots = 5;
            tank.SecondsSinceLastShot = (float) (Random.NextDouble() * 5);

            do
            {
                tank.Location = Random.In(Bounds);
            } while (IsCollidedWithRocks(tank) || IsNearPlayer(tank));

            return tank;
        }

        private bool IsNearPlayer(Tank tank)
        {
            return Math.Abs(tank.Location.X) < Bounds.Right / 2 && Math.Abs(tank.Location.Y) < Bounds.Bottom / 2;
        }


        private static IEnumerable<Rock> GenerateRocks(RectangleF rect, Random random)
        {
            var numRocks = (int) (RockDensity * rect.Width * rect.Height);
            for (var i = 0; i < numRocks; i++)
            {
                var x = (float) random.Range(rect.Left, rect.Right);
                var y = (float) random.Range(rect.Top, rect.Bottom);
                var minRadius = (float) random.Range(MinMinRockRadius, MaxMinRockRadius);
                var maxRadiusMultiple = (float) random.Range(MinMaxRadiusMultiple, MaxMaxRadiusMultiple);
                var maxRadius = minRadius * maxRadiusMultiple;


                yield return new Rock(
                    new PointF(x, y),
                    random,
                    minRadius,
                    maxRadius
                );
            }
        }

        public void Update(TimeSpan deltaT)
        {
            foreach (var ai in AIs) ai.Update(deltaT);
            foreach (var tank in Tanks) tank.Update(deltaT);
            foreach (var bullet in Bullets) bullet.Update(deltaT);
            foreach (var missile in Missiles) missile.Update(deltaT);

            HandleCollisions(deltaT);
            AIs.RemoveAll(ai => !ai.Tank.IsAlive);
            CenterPlayer();
            WrapStuff();
        }

        private void HandleCollisions(TimeSpan deltaT)
        {
            var tanks = Tanks.ToList();

            HandleTankRockCollisions(deltaT, tanks);
            HandleTankTankCollisions(deltaT, tanks);
            HandleTankBulletCollisions(tanks);
            HandleTankMissileCollisions();
            Bullets.RemoveAll(b => !b.Alive);
            HandleBulletRockCollisions();
            Enemies.RemoveAll(t => !t.IsAlive);
            AddEnemyTanks();
        }

        private void HandleTankMissileCollisions()
        {
            foreach (var missile in Missiles)
            {
                var tank = missile.Target;
                if (!tank.IsAlive) continue;

                if (!tank.Border.IsCollision(new[] {missile.Location, missile.PreviousLocation})) continue;
                
                tank.Life = 0;
                if (missile.Owner == Player) Score++;
            }

            Missiles.RemoveAll(m => !m.Target.IsAlive);
        }

        private void HandleBulletRockCollisions()
        {
            Bullets.RemoveAll(b =>
            {
                Shape s = new[] {b.Location, b.PreviousLocation};
                return Rocks.Any(r => r.Border.IsCollision(s));
            });
        }

        private void HandleTankBulletCollisions(IEnumerable<Tank> tanks)
        {
            foreach (var tank in tanks)
            foreach (var bullet in Bullets)
            {
                if (bullet.Firer == tank) continue;
                if (!bullet.GetMovementLine().IsCollision(tank.Border)) continue;

                tank.Life -= 1;
                bullet.LifeTime = 0;

                if (!tank.IsAlive && bullet.Firer == Player) Score++;
            }
        }

        private void HandleTankTankCollisions(TimeSpan deltaT, IReadOnlyList<Tank> tanks)
        {
            for (var i = 0; i < tanks.Count; i++)
            for (var j = i + 1; j < tanks.Count; j++)
            {
                var t1 = tanks[i];
                var t2 = tanks[j];

                if (!t1.Border.IsCollision(t2.Border)) continue;

                t1.UndoUpdate();
                t2.UndoUpdate();
                t1.Life -= (float) deltaT.TotalSeconds * 5;
                t2.Life -= (float) deltaT.TotalSeconds * 5;

                if (!t1.IsAlive && t2 == Player || t1 == Player && !t2.IsAlive) Score++;
            }
        }

        private void HandleTankRockCollisions(TimeSpan deltaT, IEnumerable<Tank> tanks)
        {
            foreach (var tank in tanks)
            {
                if (!Rocks.Any(rock => rock.Border.IsCollision(tank.Border))) continue;

                tank.UndoUpdate();
                tank.Life -= (float) deltaT.TotalSeconds * 5;
            }
        }

        private bool IsCollidedWithRocks(Tank t)
        {
            return Rocks.Any(rock => rock.Border.IsCollision(t.Border));
        }

        private void WrapStuff()
        {
            foreach (var r in Rocks) WrapPoint(ref r.Center);
            foreach (var b in Bullets) WrapPoint(ref b.Location);
            foreach (var tank in Enemies) WrapPoint(ref tank.Location);
            foreach (var missile in Missiles) WrapPoint(ref missile.Location);
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
            var deltaP = Player.Location.Times(-1);

            void Transform(ref PointF p)
            {
                p = p.Plus(deltaP);
            }

            foreach (var rock in Rocks) Transform(ref rock.Center);
            foreach (var b in Bullets) Transform(ref b.Location);
            foreach (var tank in Tanks) Transform(ref tank.Location);
            foreach (var missile in Missiles) Transform(ref missile.Location);
        }
    }
}