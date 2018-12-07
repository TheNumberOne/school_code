using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using Tanks.model;

namespace Tanks.ui
{
    public partial class TankForm : Form
    {
        private Game Game { get; set; }
        private HashSet<Keys> KeysPressed { get; } = new HashSet<Keys>();
        private bool Pressed(Keys k) => KeysPressed.Contains(k);

        private DateTime LastTime { get; set; } = DateTime.Now;

        public TankForm()
        {
            InitializeComponent();
        }

        private void PaintScreen(object sender, PaintEventArgs e)
        {
            DateTime now = DateTime.Now;
            Game.Update(now - LastTime);
            LastTime = now;

            Graphics g = e.Graphics;
            g.TranslateTransform(e.ClipRectangle.Width / 2.0f, e.ClipRectangle.Height / 2.0f);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            GameDisplayer.Display(Game, g);
            //g.DrawRectangle(new Pen(ForeColor), 5, 5, 10, 10);
            Invalidate();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            KeysPressed.Add(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        private void UpdateKey(Keys k)
        {
            if (k == Keys.Right || k == Keys.Left) UpdateRotation();
            if (k == Keys.Up || k == Keys.Down) UpdateMovement();
        }

        private void UpdateMovement()
        {
            if (Pressed(Keys.Up) == Pressed(Keys.Down))
            {
                Game.Player.Movement = Tank.MoveNone;
                return;
            }

            Game.Player.Movement = Pressed(Keys.Up) ? Tank.MoveForward : Tank.MoveBackwards;
        }

        private void UpdateRotation()
        {
            if (Pressed(Keys.Left) == Pressed(Keys.Right))
            {
                Game.Player.Rotation = Tank.RotationNone;
                return;
            }

            Game.Player.Rotation = Pressed(Keys.Left) ? Tank.RotationCounterclockwise : Tank.RotationClockwise;
        }

        private void OnKeyUp(object sender, KeyEventArgs e)
        {
            KeysPressed.Remove(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        private void OnLoad(object sender, EventArgs e)
        {
            // Value semantics allow us to use rect without modifying the original bounds.
            RectangleF rect = Bounds;
            rect.Width *= 1.5f;
            rect.Height *= 1.5f;
            rect.X -= rect.Width / 2;
            rect.Y -= rect.Height / 2;

            Game = new Game(rect);
        }
    }
}