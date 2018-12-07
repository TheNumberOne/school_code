using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tanks.model;
using Tanks.utils;

namespace Tanks.ui
{
    public static class GameDisplayer
    {
        private static readonly Brush TankBrush = new SolidBrush(Color.Brown);
        private static readonly Brush RockBrush = new SolidBrush(Color.DimGray);
        private static readonly Pen GunPen = new Pen(Color.Black);

        public static void Display(Game game, Graphics g)
        {
            Display(game.Player, g);
            
            foreach (Rock r in game.Rocks)
            {
                Display(r, g);
                if (game.Player.Border.IsCollision(r.Border))
                {
                    g.DrawString("Collision", new Font(FontFamily.GenericSansSerif, 12), new SolidBrush(Color.Black), 50, 50);
                }
            }
        }

        public static void Display(Tank tank, Graphics g)
        {
            g.FillPolygon(TankBrush, tank.Border);

            PointF gunMiddle = tank.Gun;
            PointF gunStart = Utils.Slide(tank.Location, gunMiddle, .7f);
            PointF gunEnd = Utils.Slide(tank.Location, gunMiddle, 1.5f);
            g.DrawLine(GunPen, gunStart, gunEnd);
        }

        private static void Display(Bullet bullet, Graphics graphics)
        {
            throw new NotImplementedException();
        }

        public static void Display(Missile missile, Graphics graphics)
        {
            throw new NotImplementedException();
        }

        public static void Display(Rock rock, Graphics g)
        {
            g.FillPolygon(RockBrush, rock.Border);
        }

        public static void Display(Shape shape, Graphics graphics)
        {
            throw new NotImplementedException();
        }
    }
}
