using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc cref="IUpdateable" />
    /// <inheritdoc cref="ICollidable" />
    /// <summary>
    ///     Represents a tank in our game.
    /// </summary>
    public class Tank: IUpdateable, ICollidable
    {
        /// <summary>
        ///     The event handler definition for when this tank fires a missile.
        /// </summary>
        public delegate void OnFireMissileEventHandler(Missile missile);
        
        /// <summary>
        ///     The event handler definition for when this tank shoots a bullet.
        /// </summary>
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
        private const int BulletLifeTime = 1;

        public float SecondsBetweenShots { get; set; }
        public float SecondsSinceLastShot { get; set; }


        public readonly float MaxRadius = (float) (Math.Sqrt(2) * Size); // sqrt 2 for long diagonal of square.
        
        /// <summary>
        ///     Used to reset the tank's previous location if there is a collision.
        /// </summary>
        private PointF _previousLocation;
        public PointF Location;

        /// <summary>
        ///     The current target that will be fired at when a missile is shot.
        /// </summary>
        public Tank MissileTarget { get; set; }

        /// <summary>
        ///     The basic shape of a tank. I.e. a square.
        /// </summary>
        private static Shape ShapePrototype { get; } = new[]
        {
            new PointF(-1, -1),
            new PointF(1, -1),
            new PointF(1, 1),
            new PointF(-1, 1)
        };

        /// <summary>
        ///     The location on the shape prototype that our gun is.
        /// </summary>
        private static PointF GunPrototype { get; } = new PointF(1, 0);
        
        /// <summary>
        ///     The location that this tank's gun is at.
        /// </summary>
        public PointF Gun => TransformPrototype(GunPrototype);

        /// <summary>
        ///     The current border of this tank.
        /// </summary>
        public Shape Border => ShapePrototype.Transform(TransformPrototype);
        
        /// <summary>
        ///     Used to reset the tank's previous location if there is a collision.
        /// </summary>
        private float PreviousAngle { get; set; }
        
        /// <summary>
        ///     The angle that the tank is rotated to point at.
        /// </summary>
        public float Angle { get; set; }

        /// <summary>
        ///     The rotation direction that this tank is currently rotating. Set to one of
        ///     <see cref="RotationNone"/>, <see cref="RotationClockwise"/>, or <see cref="RotationCounterclockwise"/>.
        /// </summary>
        public float Rotation { get; set; } = RotationNone;
        
        /// <summary>
        ///     The movement that this tank is currently performing. Set to one of <see cref="MoveForward"/>,
        ///     <see cref="MoveBackwards"/>, or <see cref="MoveNone"/>.
        /// </summary>
        public float Movement { get; set; } = MoveNone;

        public float Life { get; set; } = StartLife;
        public bool Alive => Life > 0;
        public float MaxLife { get; } = StartLife;

        /// <summary>
        ///     Transforms the prototype points for our shape and gun to their actual locations.
        /// </summary>
        private PointF TransformPrototype(PointF p)
        {
            return p.Rotate(Angle).Times(Size).Plus(Location);
        }

        /// <inheritdoc />
        public void Update(TimeSpan delta)
        {
            var dt = delta.TotalSecondsF();
            _previousLocation = Location;
            PreviousAngle = Angle;

            Location = Location.Plus(Velocity.Times(dt));
            
            Angle += Rotation * dt;
            SecondsSinceLastShot += dt;
        }
        
        public PointF Velocity => Utils.PolarToPointF(Angle, Movement);

        /// <summary>
        ///     Undoes the last update, but only undoing the changes in location and angle.
        /// </summary>
        public void UndoUpdate()
        {
            Location = _previousLocation;
            Angle = PreviousAngle;
        }

        /// <summary>
        ///     Register your event handlers here if you want to be notified of the gun shooting.
        /// </summary>
        public event OnShootEventHandler OnShoot;
        
        /// <summary>
        ///     Register your event handlers here if you want to be notified of a missile firing.
        /// </summary>
        public event OnFireMissileEventHandler OnFireMissile;

        /// <summary>
        ///     Causes this tank to fire a missile.
        /// </summary>
        public void FireMissile()
        {
            // Currently not rate limited so this could be spammed pretty bad.
            OnFireMissile?.Invoke(new Missile
            {
                Location = Location,
                Velocity = Utils.PolarToPointF(Angle, BulletSpeed),
                Angle = Angle,
                Firer = this,
                Target = MissileTarget
            });
        }

        /// <summary>
        ///     Causes this tank to shoot a bullet.
        /// </summary>
        public void Shoot()
        {
            // The shooting is rate limited.
            if (SecondsSinceLastShot < SecondsBetweenShots) return;
            
            SecondsSinceLastShot = 0;
            OnShoot?.Invoke(new Bullet
            {
                Location = Gun,
                Velocity = Utils.PolarToPointF(Angle, BulletSpeed),
                LifeTime = BulletLifeTime,
                Firer = this
            });
        }

        /// <inheritdoc />
        public Shape CollisionContainer => Border;
    }
}