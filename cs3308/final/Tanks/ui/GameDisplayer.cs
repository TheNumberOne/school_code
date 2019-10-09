using System;
using System.Drawing;
using Tanks.model;
using Tanks.utils;

namespace Tanks.ui
{
    /// <summary>
    ///     This is the class completely in charge of displaying everything.
    /// </summary>
    public static class GameDisplayer
    {
        /// <summary>
        ///     This is multiplied by the tanks radius to get the radius of the target around it.
        /// </summary>
        private const float TankTargetCircleMultiplier = 1.5f;

        /// <summary>
        ///     This is multiplied by the radius of the target circle to get the radius of the cross hairs.
        /// </summary>
        private const float TankCrosshairMultiplier = 2.25f;

        /// <summary>
        ///     The gun display starts this fraction of the way from the center of the tank to the location of the gun.
        /// </summary>
        private const float FractionTankGunInset = .7f;

        /// <summary>
        ///     The gun extends to this far out relative to the center of the tank from the location of the gun.
        /// </summary>
        private const float FractionTankGunOutset = 1.5f;

        private const float MissileLength = 10;

        private static readonly Brush EnemyBrush = new SolidBrush(Color.CornflowerBlue);
        private static readonly Brush PlayerBrush = new SolidBrush(Color.Brown);
        private static readonly Brush RockBrush = new SolidBrush(Color.DimGray);
        private static readonly Pen GunPen = new Pen(Color.Black);
        private static readonly Pen TankHealthPen = new Pen(Color.Green, width: 3);
        private static readonly Pen TankLackOfHealthPen = new Pen(Color.Red, width: 3);
        private static readonly Pen TargetCirclePen = new Pen(Color.Red, width: 3);
        private static readonly Pen CrosshairPen = new Pen(Color.Red, width: .5f);
        private static readonly PointF ScoreLocation = new PointF(x: 10, y: 10);
        private static readonly Font ScoreFont = new Font(FontFamily.GenericSansSerif, emSize: 12);
        private static readonly SolidBrush TextBrush = new SolidBrush(Color.Black);
        private static readonly PointF InstructionsLocation = new PointF(x: 10, y: 40);
        private static readonly Font InstructionsFont = new Font(FontFamily.GenericSansSerif, emSize: 10);
        private static readonly Pen BulletPen = new Pen(Color.Black);
        private static readonly Pen MissilePen = new Pen(Color.Goldenrod, width: 3);

        /// <summary>
        ///     Displays the entire game on the specified graphics.
        /// </summary>
        public static void Display(Game game, Graphics g)
        {
            foreach (Tank tank in game.Enemies) Display(tank, g, EnemyBrush);
            Display(game.Player, g, PlayerBrush);
            foreach (Rock r in game.Rocks) Display(r, g);
            foreach (Bullet bullet in game.Bullets) Display(bullet, g);
            foreach (Missile missile in game.Missiles) Display(missile, g);

            DisplayScore(game.Score, g);
            DisplayInstructions(g);
            if (game.Player.MissileTarget != null) DisplayTarget(game.Player.MissileTarget, g);
        }

        /// <summary>
        ///     Displays a circle and crosshairs around the specified tank.
        /// </summary>
        private static void DisplayTarget(Tank target, Graphics g)
        {
            DisplayTargetCircle(target, g);
            DisplayTargetCrossHairs(target, g);
        }

        /// <summary>
        ///     Displays crosshairs around the specified tank.
        /// </summary>
        private static void DisplayTargetCrossHairs(Tank target, Graphics g)
        {
            float radius2 = target.MaxRadius * TankCrosshairMultiplier;

            PointF left = target.Location.Plus(new PointF(-radius2, y: 0));
            PointF right = target.Location.Plus(new PointF(radius2, y: 0));
            PointF top = target.Location.Plus(new PointF(x: 0, y: -radius2));
            PointF bottom = target.Location.Plus(new PointF(x: 0, y: radius2));
            g.DrawLine(CrosshairPen, left, right);
            g.DrawLine(CrosshairPen, top, bottom);
        }

        /// <summary>
        ///     Displays a target circle around the specified tank.
        /// </summary>
        private static void DisplayTargetCircle(Tank target, Graphics g)
        {
            float radius = target.MaxRadius * TankTargetCircleMultiplier;

            g.DrawCircle(TargetCirclePen, target.Location, radius);
        }

        /// <summary>
        ///     Draws a circle at the specifies spot with the given radius and pen.
        /// </summary>
        private static void DrawCircle(this Graphics g, Pen pen, PointF center, float radius)
        {
            RectangleF box = new RectangleF(center.X - radius, center.Y - radius, 2 * radius, 2 * radius);
            g.DrawEllipse(pen, box);
        }

        /// <summary>
        ///     Displays the current score on the screen.
        /// </summary>
        private static void DisplayScore(int score, Graphics g)
        {
            PointF location = g.ClipBounds.Location.Plus(ScoreLocation);

            g.DrawString($"Score: {score}", ScoreFont, TextBrush, location);
        }

        /// <summary>
        ///     Displays the instructions on screen.
        /// </summary>
        private static void DisplayInstructions(Graphics g)
        {
            const string instructions = @"WASD keys moves tank.
Space fires gun.
Click fires missile at target.";


            PointF location = g.ClipBounds.Location.Plus(InstructionsLocation);
            g.DrawString(instructions, InstructionsFont, TextBrush, location);
        }

        /// <summary>
        ///     Displays the tank using the given brush.
        /// </summary>
        private static void Display(Tank tank, Graphics g, Brush brush)
        {
            DisplayTankLife(tank, g);
            g.FillPolygon(brush, tank.Border);
            DisplayTankGun(tank, g);
        }

        /// <summary>
        ///     Displays the life of the specifies tank on the screen.
        /// </summary>
        private static void DisplayTankLife(Tank tank, Graphics g)
        {
            PointF lifeStart = tank.Location.Plus(new PointF(-tank.MaxRadius, tank.MaxRadius));
            PointF lifeEnd = tank.Location.Plus(new PointF(tank.MaxRadius, tank.MaxRadius));
            PointF middle = Utils.Slide(lifeStart, lifeEnd, tank.Life / tank.MaxLife);

            g.DrawLine(TankHealthPen, lifeStart, middle);
            g.DrawLine(TankLackOfHealthPen, middle, lifeEnd);
        }

        /// <summary>
        ///     Displays the tanks gun on the screen.
        /// </summary>
        private static void DisplayTankGun(Tank tank, Graphics g)
        {
            PointF gunMiddle = tank.Gun;
            PointF gunStart = Utils.Slide(tank.Location, gunMiddle, FractionTankGunInset);
            PointF gunEnd = Utils.Slide(tank.Location, gunMiddle, FractionTankGunOutset);
            g.DrawLine(GunPen, gunStart, gunEnd);
        }

        /// <summary>
        ///     Displays the bullet on the screen.
        /// </summary>
        private static void Display(Bullet bullet, Graphics g) { g.DrawCircle(BulletPen, bullet.Location, radius: 1); }

        /// <summary>
        ///     Displays the missile on the screen.
        /// </summary>
        private static void Display(Missile missile, Graphics g)
        {
            PointF tip = missile.Location;
            PointF back = Utils.PolarToPointF((float) (missile.Angle + Math.PI), MissileLength).Plus(tip);

            g.DrawLine(MissilePen, back, tip);
        }

        /// <summary>
        ///     Displays the rock on the screen.
        /// </summary>
        private static void Display(Rock rock, Graphics g) { g.FillPolygon(RockBrush, rock.Border); }
    }
}