using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.utils
{
    public static partial class Utils
    {
        public static double Range(this Random r, double min, double max)
        {
            return r.NextDouble() * (max - min) + min;
        }
    }
}
