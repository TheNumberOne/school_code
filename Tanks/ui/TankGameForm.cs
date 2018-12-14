using System;
using System.Drawing;
using System.Windows.Forms;

namespace Tanks.ui
{
    /// <summary>
    ///     The main form of the program.
    /// </summary>
    public sealed class TankGameForm : Form
    {
        private const int LastScoreOffset = 40;
        private const int BestScoreOffset = 20;

        public TankGameForm()
        {
            SuspendLayout();
            AutoScaleDimensions = new SizeF(6F, 13F); // Used so look is consistent across different screen densities.
            AutoScaleMode = AutoScaleMode.Font;
            DoubleBuffered = true;
            Name = "Tanks";
            Text = "Tanks";
            WindowState = FormWindowState.Maximized;

            NavigateToMenu();
            ResumeLayout(false);
        }

        private int? LastScore { get; set; }
        private int BestScore { get; set; }

        /// <summary>
        ///     Displays the main menu.
        /// </summary>
        private void NavigateToMenu()
        {
            Controls.Clear();

            var newGame = AddNewGameButton();
            DisplayBestScore(newGame);
            DisplayLastScore(newGame);
        }

        /// <summary>
        ///     Displays the last score.
        /// </summary>
        /// <param name="newGame">Used to position the last score.</param>
        private void DisplayLastScore(Control newGame)
        {
            if (LastScore != null)
                Controls.Add(new Label
                {
                    Text = $"Last Score: {LastScore}",
                    Anchor = AnchorStyles.None,
                    Location = new Point(newGame.Location.X, newGame.Location.Y - LastScoreOffset)
                });
        }

        /// <summary>
        ///     Displays the best score.
        /// </summary>
        /// <param name="newGame">Used to position the best score.</param>
        private void DisplayBestScore(Control newGame)
        {
            Controls.Add(new Label
            {
                Text = $"Best Score: {BestScore}",
                Anchor = AnchorStyles.None,
                Location = new Point(newGame.Location.X, newGame.Location.Y - BestScoreOffset)
            });
        }

        /// <summary>
        ///     Adds the new game button to the form in the very center.
        /// </summary>
        /// <returns>The button so other controls can use it for positioning.</returns>
        private Button AddNewGameButton()
        {
            var newGame = new Button
            {
                Text = "Start New Game",
                Anchor = AnchorStyles.None,
                Size = new Size(112, 24)
            };

            newGame.MouseClick += (_, __) => StartGame();
            newGame.Location = new Point((Width - newGame.Width) / 2, (Height - newGame.Height) / 2);

            Controls.Add(newGame);
            return newGame;
        }

        /// <summary>
        ///     Starts the game.
        /// </summary>
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