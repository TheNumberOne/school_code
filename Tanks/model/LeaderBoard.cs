﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.model
{
    public class LeaderBoard
    {
        public IEnumerable<Score> TopScores { get; }

        public void AddScore(Score score)
        {
            throw new NotImplementedException();
        }

        public void SaveToFile(string fileName)
        {
            throw new NotImplementedException();
        }

        public static LeaderBoard LoadFromFile(string fileName)
        {
            throw new NotImplementedException();
        }

        public static LeaderBoard Empty()
        {
            throw new NotImplementedException();
        }
    }

    public class Score
    {
        public int Points { get; }
        public string Name { get; }
    }
}
