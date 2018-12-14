using System;

namespace Tanks.model
{
    public interface IUpdateable
    {
        /// <summary>
        ///     Updates this component by the specified time.
        /// </summary>
        /// <param name="t"></param>
        void Update(TimeSpan t);
    }
}