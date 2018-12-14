using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using MoreLinq.Extensions;
using Tanks.tankOperators;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc />
    /// <summary>
    ///     Represents the current game running.
    /// </summary>
    public class Game : IUpdateable
    {
        private const float TimePerDifficultyIncrease = 10;
        private const float SecondsBetweenPlayerShots = .1f;
        private const float SecondsBetweenEnemyShots = 5;
        private const float BulletDamage = 1;
        private const float TankTankCollisionDamageRate = 5;
        private const float TankRockCollisionDamageRate = 5;

        /// <summary>
        ///     Creates a new game that takes place in the given rectangle.
        /// </summary>
        /// <param name="rect">The rectangle that the game takes place in.</param>
        public Game(RectangleF rect)
        {
            Rocks = new RandomRockFactory(Random).GenerateRocks(rect).ToList();
            Bounds = rect;

            CreatePlayer();
            CenterPlayer();
            WrapStuff();
            AddEnemies();
        }

        /// <summary>
        ///     The current number of enemies on the field.
        /// </summary>
        private int NumEnemies { get; set; } = 1;

        public List<Rock> Rocks { get; }

        /// <summary>
        ///     The RNG used for everything.
        /// </summary>
        private Random Random { get; } = new Random();

        private RectangleF Bounds { get; }
        public Tank Player { get; private set; }
        public List<Bullet> Bullets { get; } = new List<Bullet>();

        /// <summary>
        ///     The enemy tanks of the player.
        /// </summary>
        public List<Tank> Enemies { get; } = new List<Tank>();

        /// <summary>
        ///     Represents all tanks on the field.
        /// </summary>
        private IEnumerable<Tank> Tanks => Enemies.Append(Player);

        /// <summary>
        ///     The current score of the player
        /// </summary>
        public int Score { get; private set; }

        public List<Missile> Missiles { get; } = new List<Missile>();

        /// <summary>
        ///     The AIs controlling the enemy tanks.
        /// </summary>
        private List<TankAi> EnemyAis { get; } = new List<TankAi>();

        /// <summary>
        ///     A boolean to return if this game is over now or not.
        /// </summary>
        public bool IsOver => !Player.Alive;


        private float TimeSinceLastDifficultIncrease { get; set; }

        /// <summary>
        ///     A collection of everything that can be updated in this.
        /// </summary>
        private IEnumerable<IUpdateable> AllUpdatables =>
            EnemyAis.AsEnumerable<IUpdateable>().Concat(Missiles).Concat(Tanks).Concat(Bullets);

        /// <inheritdoc />
        public void Update(TimeSpan deltaT)
        {
            foreach (IUpdateable u in AllUpdatables) u.Update(deltaT);

            HandleCollisions(deltaT);
            RemoveDeadStuff();
            CenterPlayer();
            WrapStuff();
            CheckDifficultyIncrease(deltaT);
            AddEnemies();
        }

        /// <summary>
        ///     Generates the player character.
        /// </summary>
        private void CreatePlayer()
        {
            Tank tank = new Tank {Angle = Random.RandomAngleF(), SecondsBetweenShots = SecondsBetweenPlayerShots};
            tank.OnShoot += Bullets.Add;
            tank.OnFireMissile += Missiles.Add;

            PlacePlayer(tank);
            Player = tank;
        }

        /// <summary>
        ///     Assigns a location to the tank such that it doesn't intersect any rocks
        /// </summary>
        /// <param name="tank"></param>
        private void PlacePlayer(Tank tank)
        {
            do { tank.Location = Random.In(Bounds); } while (IsCollidedWithRocks(tank));
        }

        /// <summary>
        ///     Keeps adding enemy tanks until it reaches the amount specified by <see cref="NumEnemies" />.
        /// </summary>
        private void AddEnemies()
        {
            while (Enemies.Count < NumEnemies) AddEnemy();
        }

        /// <summary>
        ///     Adds an enemy to this game.
        /// </summary>
        private void AddEnemy()
        {
            Tank enemy = GenerateRandomEnemyTank();
            EnemyAis.Add(new TankAi {Tank = enemy, Game = this});
            Enemies.Add(enemy);
        }

        /// <summary>
        ///     Generates a random enemy tank.
        /// </summary>
        private Tank GenerateRandomEnemyTank()
        {
            Tank tank = new Tank
            {
                Angle = Random.RandomAngleF(),
                SecondsBetweenShots = SecondsBetweenEnemyShots,
                SecondsSinceLastShot = Random.RangeF(min: 0, max: SecondsBetweenEnemyShots)
            };

            tank.OnShoot += Bullets.Add;
            PlaceEnemyTank(tank);

            return tank;
        }

        /// <summary>
        ///     Finds a location of the enemy tank that isn't near the player
        ///     or collided with any rocks.
        /// </summary>
        private void PlaceEnemyTank(Tank tank)
        {
            do { tank.Location = Random.In(Bounds); } while (IsCollidedWithRocks(tank) || IsNearPlayer(tank));
        }

        /// <summary>
        ///     Determines if the given tank is near the player.
        /// </summary>
        private bool IsNearPlayer(Tank tank) =>
            Math.Abs(tank.Location.X    - Player.Location.X) < Bounds.Width  / 4
            && Math.Abs(tank.Location.Y - Player.Location.Y) < Bounds.Height / 4;

        /// <summary>
        ///     Removes all objects that are determined to be dead except for the player.
        /// </summary>
        private void RemoveDeadStuff()
        {
            EnemyAis.RemoveAll(ai => !ai.Tank.Alive);
            Bullets.RemoveAll(b => !b.Alive);
            Enemies.RemoveAll(t => !t.Alive);
            Missiles.RemoveAll(m => !m.Target.Alive);
        }

        /// <summary>
        ///     Checks to see if the difficulty should increase.
        /// </summary>
        private void CheckDifficultyIncrease(TimeSpan deltaT)
        {
            TimeSinceLastDifficultIncrease += deltaT.TotalSecondsF();
            if (!(TimeSinceLastDifficultIncrease > TimePerDifficultyIncrease)) return;
            NumEnemies++;
            TimeSinceLastDifficultIncrease -= TimePerDifficultyIncrease;
        }

        /// <summary>
        ///     Handles collisions between different objects.
        /// </summary>
        private void HandleCollisions(TimeSpan deltaT)
        {
            HandleTankRockCollisions(deltaT);
            HandleTankTankCollisions(deltaT);
            HandleTankBulletCollisions();
            HandleTankMissileCollisions();
            HandleBulletRockCollisions();
        }

        /// <summary>
        ///     Handles collisions between tanks and missiles.
        /// </summary>
        private void HandleTankMissileCollisions()
        {
            foreach (Missile missile in Missiles)
            {
                Tank target = missile.Target;
                if (!target.Alive) continue;

                if (!target.IsCollision(missile)) continue;

                target.Life = 0;
                CheckKill(missile.Firer);
            }
        }

        /// <summary>
        ///     Checks to see if the tank is the player and increases their score if so.
        /// </summary>
        private void CheckKill(Tank killer)
        {
            if (killer == Player) Score++;
        }

        /// <summary>
        ///     Checks for collisions between bullets and rocks.
        /// </summary>
        private void HandleBulletRockCollisions()
        {
            foreach (Bullet bullet in Bullets)
            {
                if (Rocks.Any(r => r.IsCollision(bullet))) bullet.LifeTime = 0;
            }
        }

        /// <summary>
        ///     Checks for collisions between tanks and bullets.
        /// </summary>
        private void HandleTankBulletCollisions()
        {
            foreach (Tank tank in Tanks)
            foreach (Bullet bullet in Bullets)
            {
                if (bullet.Firer == tank) continue;
                if (!bullet.IsCollision(tank)) continue;

                tank.Life -= BulletDamage;
                bullet.LifeTime = 0;

                if (!tank.Alive) CheckKill(bullet.Firer);
            }
        }

        /// <summary>
        ///     Handles collisions between tanks.
        /// </summary>
        private void HandleTankTankCollisions(TimeSpan deltaT)
        {
            List<Tank> tanks = Tanks.ToList();
            for (int i = 0; i < tanks.Count; i++)
            for (int j = i + 1; j < tanks.Count; j++)
            {
                Tank t1 = tanks[i];
                Tank t2 = tanks[j];

                if (!t1.IsCollision(t2)) continue;

                HandleTankTankCollision(deltaT, t1, t2);
                HandleTankTankCollision(deltaT, t2, t1);
            }
        }

        /// <summary>
        ///     Handles one tank in a tank-tank collision.
        /// </summary>
        private void HandleTankTankCollision(TimeSpan deltaT, Tank collided, Tank collider)
        {
            collided.UndoUpdate();
            collided.Life -= deltaT.TotalSecondsF() * TankTankCollisionDamageRate;
            if (!collided.Alive) CheckKill(collider);
        }

        /// <summary>
        ///     Handles collisions between tanks and rocks.
        /// </summary>
        /// <param name="deltaT"></param>
        private void HandleTankRockCollisions(TimeSpan deltaT)
        {
            foreach (Tank tank in Tanks)
            {
                if (!Rocks.Any(rock => rock.IsCollision(tank))) continue;

                tank.UndoUpdate();
                tank.Life -= deltaT.TotalSecondsF() * TankRockCollisionDamageRate;
            }
        }

        /// <summary>
        ///     Checks to see if the object is colliding with any rocks.
        /// </summary>
        private bool IsCollidedWithRocks(ICollidable t) { return Rocks.Any(rock => rock.IsCollision(t)); }

        /// <summary>
        ///     Wraps the centers of everything.
        /// </summary>
        private void WrapStuff()
        {
            foreach (Rock r in Rocks) WrapPoint(ref r.Location);
            foreach (Bullet b in Bullets) WrapPoint(ref b.Location);
            foreach (Tank tank in Enemies) WrapPoint(ref tank.Location);
            foreach (Missile missile in Missiles) WrapPoint(ref missile.Location);
        }

        /// <summary>
        ///     Wraps the specified point so it is within bounds.
        /// </summary>
        private void WrapPoint(ref PointF p)
        {
            while (p.X < Bounds.Left) p.X += Bounds.Width;
            while (p.X >= Bounds.Right) p.X -= Bounds.Width;
            while (p.Y < Bounds.Top) p.Y += Bounds.Height;
            while (p.Y >= Bounds.Bottom) p.Y -= Bounds.Height;
        }

        /// <summary>
        ///     Centers the player and adjusts the position of everything else accordingly.
        /// </summary>
        private void CenterPlayer()
        {
            PointF deltaP = Player.Location.Times(r: -1);

            void Transform(ref PointF p) { p = p.Plus(deltaP); }

            foreach (Rock rock in Rocks) Transform(ref rock.Location);
            foreach (Bullet b in Bullets) Transform(ref b.Location);
            foreach (Tank tank in Tanks) Transform(ref tank.Location);
            foreach (Missile missile in Missiles) Transform(ref missile.Location);
        }
    }
}