using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Windows.Forms;
using FarseerPhysics.Factories;
using Tanks.model;
using Tanks.utils;

namespace Tanks.ui
{
    public static class GameDisplayer
    {
        private static readonly Brush TankBrush = new SolidBrush(Color.Brown);
        private static readonly Brush RockBrush = new SolidBrush(Color.DimGray);
        private static readonly Pen GunPen = new Pen(Color.Black);
        private static readonly Pen TankHealthPen = new Pen(Color.Green, 3);
        private static readonly Pen TankLackOfHealthPen = new Pen(Color.Red, 3);


        public static void Display(Game game, Graphics g)
        {
            foreach (var tank in game.Tanks)
            {
                Display(tank, g);
            }
            
            foreach (var r in game.Rocks)
            {
                Display(r, g);
            }

            foreach (var bullet in game.Bullets)
            {
                Display(bullet, g);
            }
            
            DisplayScore(game.Score, g);
            if (game.Player.MissileTarget != null) DisplayTarget(game.Player.MissileTarget, g);
        }

        private static void DisplayTarget(Tank target, Graphics g)
        {
            var radius = target.MaxRadius * 1.5f;
            
            var location = new RectangleF(
                target.Location.X - radius,
                target.Location.Y - radius,
                2 * radius, 
                2 * radius
            );
            
            g.DrawEllipse(new Pen(Color.Red, 3), location);
        }

        private static void DisplayScore(int score, Graphics g)
        {
            var location = g.ClipBounds.Location;

            location.X += 10;
            location.Y += 10;
            
            g.DrawString($"Score: {score}", new Font(FontFamily.GenericSansSerif, 12), new SolidBrush(Color.Black), location);
        }

        private static void Display(Tank tank, Graphics g)
        {
            DisplayTankLife(tank, g);
            g.FillPolygon(TankBrush, tank.Border);
            DisplayTankGun(tank, g);
        }

        private static void DisplayTankLife(Tank tank, Graphics g)
        {
            var lifeStart = tank.Location.Plus(new PointF(-tank.MaxRadius, tank.MaxRadius));
            var lifeEnd = tank.Location.Plus(new PointF(tank.MaxRadius, tank.MaxRadius));
            var middle = Utils.Slide(lifeStart, lifeEnd, tank.Life / tank.MaxLife);

            g.DrawLine(TankHealthPen, lifeStart, middle);
            g.DrawLine(TankLackOfHealthPen, middle, lifeEnd);
        }

        private static void DisplayTankGun(Tank tank, Graphics g)
        {
            var gunMiddle = tank.Gun;
            var gunStart = Utils.Slide(tank.Location, gunMiddle, .7f);
            var gunEnd = Utils.Slide(tank.Location, gunMiddle, 1.5f);
            g.DrawLine(GunPen, gunStart, gunEnd);
        }

        private static void Display(Bullet bullet, Graphics g)
        {
            g.DrawRectangle(new Pen(Color.Black), bullet.Location.X, bullet.Location.Y, 1, 1);
        }

        public static void Display(Missile missile, Graphics g)
        {
            throw new NotImplementedException();
        }

        private static void Display(Rock rock, Graphics g)
        {
            g.FillPolygon(RockBrush, rock.Border);
//            g.DrawPolygon(RockBorderPen, rock.Border);
        }

        public static void Display(Shape shape, Graphics g)
        {
            throw new NotImplementedException();
        }
    }
}