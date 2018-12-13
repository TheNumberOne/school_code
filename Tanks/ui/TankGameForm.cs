using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;

namespace Tanks.ui
{
    public sealed class TankGameForm : Form
    {
        private Control MainControl
        {
            get => Controls[0];
            set
            {
                Controls.Clear();
                Controls.Add(value);
            }
        }

        public TankGameForm()
        {
            SuspendLayout();
            AutoScaleDimensions = new SizeF(6F, 13F);
            AutoScaleMode = AutoScaleMode.Font;
            DoubleBuffered = true;
            Name = "Tanks";
            Text = "Tanks";
            WindowState = FormWindowState.Maximized;
            
            NavigateToMenu();
            ResumeLayout(false);
        }


        private void NavigateToMenu()
        {
            var newGame = new Button
            {
                Text = "Start New Game",
                Anchor = AnchorStyles.None,
                Size = new Size(112, 24)
            };

            newGame.MouseClick += (_, __) => StartGame();
            
            newGame.Location = new Point( (Width - newGame.Width) / 2, (Height - newGame.Height) / 2);
            MainControl = newGame;
        }

        private void StartGame()
        {
            var tankForm = new GameControl {Dock = DockStyle.Fill, AutoSize = true};
            tankForm.OnGameEnd += NavigateToMenu;

            MainControl = tankForm;
            MainControl.Focus();
        }
    }
}