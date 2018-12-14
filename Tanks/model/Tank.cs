using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    public class Tank
    {
        public delegate void OnFireMissileEventHandler(Missile missile);

        public delegate void OnShootEventHandler(Bullet bullet);

        public const float RotationNone = 0;
        public const float RotationClockwise = 1;
        public const float RotationCounterclockwise = -RotationClockwise;
        public const float MoveForward = 60;
        public const float MoveBackwards = -MoveForward;
        public const float MoveNone = 0;

        private const float BulletSpeed = 10 * MoveForward;

        private const float StartLife = 10;
        private const float Size = 10;

        public float SecondsBetweenShots { get; set; } = 10;
        public float SecondsSinceLastShot { get; set; } = 0;


        public readonly float MaxRadius = (float) (Math.Sqrt(2) * Size);
        private PointF _previousLocation;
        public PointF Location;

        public Tank MissileTarget { get; set; }

        private static PointF StartingBulletVelocity { get; } = new PointF(BulletSpeed, 0);

        private static Shape ShapePrototype { get; } = new[]
        {
            new PointF(-1, -1),
            new PointF(1, -1),
            new PointF(1, 1),
            new PointF(-1, 1)
        };

        private static PointF GunPrototype { get; } = new PointF(1, 0);
        public PointF Gun => TransformPrototype(GunPrototype);

        public Shape Border => ShapePrototype.Transform(TransformPrototype);
        private float PreviousAngle { get; set; }
        public float Angle { get; set; }

        public float Rotation { get; set; } = RotationNone;
        public float Movement { get; set; } = MoveNone;

        public float Life { get; set; } = StartLife;
        public bool IsAlive => Life > 0;
        public float MaxLife { get; } = StartLife;

        private PointF TransformPrototype(PointF p)
        {
            return p.Rotate(Angle).Times(Size).Plus(Location);
        }

        public void Update(TimeSpan delta)
        {
            var dt = delta.TotalSeconds;
            _previousLocation = Location;
            PreviousAngle = Angle;

            Location.X += (float) (Movement * Math.Cos(Angle) * dt);
            Location.Y += (float) (Movement * Math.Sin(Angle) * dt);
            Angle += (float) (Rotation * dt);
            SecondsSinceLastShot += (float) dt;
        }

        public void UndoUpdate()
        {
            Location = _previousLocation;
            Angle = PreviousAngle;
        }

        public event OnShootEventHandler OnShoot;
        public event OnFireMissileEventHandler OnFireMissile;

        public void FireMissile()
        {
            OnFireMissile?.Invoke(new Missile
            {
                Location = Location,
                Velocity = new PointF(BulletSpeed, 0).Rotate(Angle),
                Angle = Angle,
                Owner = this,
                Target = MissileTarget
            });
        }

        public void Shoot()
        {
            if (SecondsSinceLastShot < SecondsBetweenShots) return;
            
            SecondsSinceLastShot = 0;
            OnShoot?.Invoke(new Bullet
            {
                Location = Gun,
                Velocity = StartingBulletVelocity.Rotate(Angle),
                LifeTime = 1,
                Firer = this
            });
        }
    }
}