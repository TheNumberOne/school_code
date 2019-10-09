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
    /// <summary>
    ///     This control is used to display and control a game for a player.
    /// </summary>
    public sealed class GameControl : Control
    {
        /// <summary>
        ///     Event handler definition for when the game ends.
        /// </summary>
        public delegate void OnGameEndEvent(Game g);

        private const Keys ForwardKey = Keys.W;
        private const Keys BackwardsKey = Keys.S;
        private const Keys CounterClockwiseKey = Keys.A;
        private const Keys ClockwiseKey = Keys.D;
        private const Keys FireKey = Keys.Space;

        /// <summary>
        ///     The default size of the game.
        /// </summary>
        private static readonly RectangleF GameSize = new RectangleF(x: -1500, y: -750, width: 3000, height: 1500);

        /// <summary>
        ///     Constructs a new game control.
        /// </summary>
        public GameControl()
        {
            DoubleBuffered = true;
            Game = new Game(GameSize);
            AddEventHandlers();
        }

        /// <summary>
        ///     The current game running.
        /// </summary>
        private Game Game { get; }

        /// <summary>
        ///     The current keys pressed.
        /// </summary>
        private HashSet<Keys> KeysPressed { get; } = new HashSet<Keys>();

        /// <summary>
        ///     The last time the game was updated.
        /// </summary>
        private DateTime LastTime { get; set; } = DateTime.Now;

        /// <summary>
        ///     Used to initialize event handlers for the project.
        /// </summary>
        private void AddEventHandlers()
        {
            KeyDown += (_, e) => Tanks_OnKeyDown(e);
            Paint += (_, e) => Tanks_OnPaint(e);
            KeyUp += (_, e) => Tanks_OnKeyUp(e);
            MouseDown += (_, e) => Tanks_OnMouseDown();
        }

        /// <summary>
        ///     Fire a missile when the mouse is clicked.
        /// </summary>
        private void Tanks_OnMouseDown() { Game.Player.FireMissile(); }

        /// <summary>
        ///     The event fired when the game ends.
        /// </summary>
        public event OnGameEndEvent OnGameEnd;

        /// <summary>
        ///     Determines if the specified key is pressed or not.
        /// </summary>
        private bool Pressed(Keys k) => KeysPressed.Contains(k);

        /// <summary>
        ///     Updates the game and paints.
        /// </summary>
        private void Tanks_OnPaint(PaintEventArgs e)
        {
            UpdateGame();

            Graphics g = e.Graphics;
            g.TranslateTransform(e.ClipRectangle.Width / 2.0f, e.ClipRectangle.Height / 2.0f);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            GameDisplayer.Display(Game, g);
        }

        /// <summary>
        ///     Updates the game.
        /// </summary>
        private void UpdateGame()
        {
            if (Game.IsOver) return;

            DateTime now = DateTime.Now;
            TimeSpan deltaT = now - LastTime;
            LastTime = now;

            if (Pressed(FireKey)) Game.Player.Shoot();
            SelectPlayerMissileTarget();

            Game.Update(deltaT);
            if (Game.IsOver) OnGameEnd?.Invoke(Game);

            Invalidate(); // Invalidate so the game is repainted asap.
        }

        /// <summary>
        ///     Selects the closest enemy tank to the player and sets that as its target.
        /// </summary>
        private void SelectPlayerMissileTarget()
        {
            Game.Player.MissileTarget = Game.Enemies.MinBy(
                    t =>
                        t.Location.Distance(ClientToGameCoordinates(PointToClient(Cursor.Position)))
                )
                .First();
        }

        /// <summary>
        ///     Converts coordinates on the client to game coordinates.
        /// </summary>
        private PointF ClientToGameCoordinates(PointF screen)
        {
            PointF center = ClientRectangle.Location;
            center.X += ClientRectangle.Width  / 2f;
            center.Y += ClientRectangle.Height / 2f;
            return screen.Minus(center);
        }

        /// <summary>
        ///     Handles key presses.
        /// </summary>
        private void Tanks_OnKeyDown(KeyEventArgs e)
        {
            KeysPressed.Add(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        /// <summary>
        ///     Updates rotation and movement of player if certain keys were pressed.
        /// </summary>
        private void UpdateKey(Keys k)
        {
            // Switch not used because of weird flags behavior.
            if (k == CounterClockwiseKey || k == ClockwiseKey) UpdateRotation();
            if (k == ForwardKey          || k == BackwardsKey) UpdateMovement();
        }

        /// <summary>
        ///     Updates the movement of the player by the keys pressed.
        /// </summary>
        private void UpdateMovement()
        {
            if (Pressed(ForwardKey) == Pressed(BackwardsKey))
            {
                Game.Player.Movement = Tank.MoveNone;
                return;
            }

            Game.Player.Movement = Pressed(ForwardKey) ? Tank.MoveForward : Tank.MoveBackwards;
        }

        /// <summary>
        ///     Updates the rotation of the player by the kays pressed.
        /// </summary>
        private void UpdateRotation()
        {
            if (Pressed(CounterClockwiseKey) == Pressed(ClockwiseKey))
            {
                Game.Player.Rotation = Tank.RotationNone;
                return;
            }

            Game.Player.Rotation =
                Pressed(CounterClockwiseKey) ? Tank.RotationCounterclockwise : Tank.RotationClockwise;
        }

        /// <summary>
        ///     Handles key presses.
        /// </summary>
        private void Tanks_OnKeyUp(KeyEventArgs e)
        {
            KeysPressed.Remove(e.KeyCode);
            UpdateKey(e.KeyCode);
        }

        /// <summary>
        ///     Determines if a given key is an input key.
        /// </summary>
        protected override bool IsInputKey(Keys keyData)
        {
            switch (keyData)
            {
                case ForwardKey:
                case BackwardsKey:
                case ClockwiseKey:
                case CounterClockwiseKey:
                case FireKey: return true;
                default: return base.IsInputKey(keyData);
            }
        }
    }
}