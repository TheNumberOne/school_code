using System.Linq;

namespace RosettaRobertsProject6
{
    /// <summary>
    ///     Author: Rosetta Roberts
    ///     <para />
    ///     Contains utility functions.
    /// </summary>
    internal static class Utils
    {
        /// <summary>
        ///     Repeats this string the specified number of <paramref name="times" />
        /// </summary>
        public static string Repeat(this string repeated, int times) =>
            string.Concat(Enumerable.Repeat(repeated, times));
    }
}