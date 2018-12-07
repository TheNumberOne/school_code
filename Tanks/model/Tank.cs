using System;
using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    public class Tank
    {
        public const float RotationNone = 0;
        public const float RotationClockwise = 1;
        public const float RotationCounterclockwise = -RotationClockwise;
        public const float MoveForward = 30;
        public const float MoveBackwards = -MoveForward;
        public const float MoveNone = 0;

        private const float Size = 10;


        private static Shape ShapePrototype { get; } = new []
        {
            new PointF(-1, -1),
            new PointF(1, -1),
            new PointF(1, 1),
            new PointF(-1, 1)
        };

        private static PointF GunPrototype { get; } = new PointF(1, 0);
        public PointF Gun => TransformPrototype(GunPrototype);

        public Shape Border => ShapePrototype.Transform(TransformPrototype);
        public PointF Location;
        public float Angle { get; set; }

        public float Rotation { get; set; } = RotationNone;

        public float Movement { get; set; } = MoveNone;

        private PointF TransformPrototype(PointF p)
        {
            return p.Rotate(Angle).Times(Size).Plus(Location);
        }

        public void Update(TimeSpan delta)
        {
            double dt = delta.TotalSeconds;

            Location.X += (float) (Movement * Math.Cos(Angle) * dt);
            Location.Y += (float) (Movement * Math.Sin(Angle) * dt);
            Angle += (float) (Rotation * dt);
        }

//        public bool Alive { get; }
//        public int Life { get; }
//        public Shape Shape { get; }
//        private ITankOperator Operator { get; }
//
//        public void CheckCollision(Rock rock)
//        {
//            throw new NotImplementedException();
//        }
//
//        public Tank(Vector initialLocation, ITankOperator tankOperator)
//        {
//            throw new NotImplementedException();
//        }
//
//        public void Update(double t)
//        {
//            throw new NotImplementedException();
//        }
    }
}