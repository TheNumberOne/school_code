using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using MoreLinq;
using Tanks.model;
using Tanks.utils;

namespace Tanks.ui
{
    public sealed class GameControl : Control
    {
        private static readonly RectangleF GameSize = new RectangleF(-1500, -750, 3000, 1500);

        private const Keys ForwardKey = Keys.W;
        private const Keys BackwardsKey = Keys.S;
        private const Keys CounterClockwiseKey = Keys.A;
        private const Keys ClockwiseKey = Keys.D;
        private const Keys FireKey = Keys.Space;
        
        
        private const float BulletRate = 10;
        private static readonly TimeSpan BulletInterval = TimeSpan.FromSeconds(1 / BulletRate);
        private DateTime LastBulletFired { get; set; }= DateTime.MinValue;


        public GameControl()
        {
            KeyDown += (_, e) => Tanks_OnKeyDown(e);
            Paint += (_, e) => Tanks_OnPaint(e);
            KeyUp += (_, e) => Tanks_OnKeyUp(e);
            MouseDown += (_, e) => Tanks_OnMouseDown(e);
            DoubleBuffered = true;
            Game = new Game(GameSize);
        }

        private void Tanks_OnMouseDown(MouseEventArgs e)
        {
            Game.Player.FireMissile();
        }

        public delegate void OnGameEndEvent();

        public event OnGameEndEvent OnGameEnd;

        private Game Game { get; }
        private HashSet<Keys> KeysPressed { get; } = new HashSet<Keys>();
        private DateTime LastTime { get; set; } = DateTime.Now;

        private bool Pressed(Keys k)
        {
            return KeysPressed.Contains(k);
        }

        private void Tanks_OnPaint(PaintEventArgs e)
        {
            if (!Game.IsOver)
            {
                var now = DateTime.Now;
                var deltaT = now - LastTime;
                
                if (Pressed(FireKey) && now - LastBulletFired >= BulletInterval)
                {
                    LastBulletFired = now;
                    Game.Player.Shoot();
                }
                
                Game.Update(deltaT);
                LastTime = now;

                if (Game.IsOver) OnGameEnd?.Invoke();
                
//                Console.WriteLine(e.ClipRectangle);

                Game.Player.MissileTarget = Game.Enemies.MinBy(t => t.Location.Distance(ClientToGameCoordinates(PointToClient(Cursor.Position)))).First();
                
                Invalidate();
            }

            var g = e.Graphics;
            g.TranslateTransform(e.ClipRectangle.Width / 2.0f, e.ClipRectangle.Height / 2.0f);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            GameDisplayer.Display(Game, g);
        }

        private PointF ClientToGameCoordinates(PointF screen)
        {
//            Console.WriteLine(this.);
            PointF center = ClientRectangle.Location;
            center.X += ClientRectangle.Width / 2f;
            center.Y += ClientRectangle.Height / 2f;
            return screen.Plus(center.Times(-1));
        }

        private void Tanks_OnKeyDown(KeyEventArgs e)
        {
            KeysPressed.Add(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        private void UpdateKey(Keys k)
        {
            if (k == CounterClockwiseKey || k == ClockwiseKey) UpdateRotation();
            if (k == ForwardKey || k == BackwardsKey) UpdateMovement();
        }

        private void UpdateMovement()
        {
            if (Pressed(ForwardKey) == Pressed(BackwardsKey))
            {
                Game.Player.Movement = Tank.MoveNone;
                return;
            }

            Game.Player.Movement = Pressed(ForwardKey) ? Tank.MoveForward : Tank.MoveBackwards;
        }

        private void UpdateRotation()
        {
            if (Pressed(CounterClockwiseKey) == Pressed(ClockwiseKey))
            {
                Game.Player.Rotation = Tank.RotationNone;
                return;
            }

            Game.Player.Rotation = Pressed(CounterClockwiseKey) ? Tank.RotationCounterclockwise : Tank.RotationClockwise;
        }

        private void Tanks_OnKeyUp(KeyEventArgs e)
        {
            KeysPressed.Remove(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        protected override bool IsInputKey(Keys keyData)
        {
            switch (keyData)
            {
                case ForwardKey:
                case BackwardsKey:
                case ClockwiseKey:
                case CounterClockwiseKey:
                case FireKey:
                    return true;
                default:
                    return base.IsInputKey(keyData);
            }
        }
    }
}