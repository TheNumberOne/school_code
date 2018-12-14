using System;
using System.Drawing;
using System.Windows.Forms;

namespace Tanks.ui
{
    public sealed class TankGameForm : Form
    {
        private int? LastScore { get; set; } = null;
        private int BestScore { get; set; } = 0;
        
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
            Controls.Clear();
            
            var newGame = new Button
            {
                Text = "Start New Game",
                Anchor = AnchorStyles.None,
                Size = new Size(112, 24)
            };

            newGame.MouseClick += (_, __) => StartGame();
            newGame.Location = new Point((Width - newGame.Width) / 2, (Height - newGame.Height) / 2);

            Controls.Add(newGame);
            Controls.Add(new Label
            {
                Text = $"Best Score: {BestScore}",
                Anchor = AnchorStyles.None,
                Location = new Point(newGame.Location.X, newGame.Location.Y - 20)
            });

            if (LastScore != null)
            {
                Controls.Add(new Label
                {
                    Text = $"Last Score: {LastScore}",
                    Anchor = AnchorStyles.None,
                    Location = new Point(newGame.Location.X, newGame.Location.Y - 40)
                });
                
            }
        }

        private void StartGame()
        {
            Controls.Clear();
            
            var tankForm = new GameControl {Dock = DockStyle.Fill, AutoSize = true};
            tankForm.OnGameEnd += game =>
            {
                LastScore = game.Score;
                BestScore = Math.Max(game.Score, BestScore);
                NavigateToMenu();
            };

            Controls.Add(tankForm);
            tankForm.Focus();
        }    
    }
}