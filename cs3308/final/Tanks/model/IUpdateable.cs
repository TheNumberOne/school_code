using System;

namespace Tanks.model
{
    /// <summary>
    ///     Represents an object that can be updated.
    /// </summary>
    public interface IUpdateable
    {
        /// <summary>
        ///     Updates this component by the specified time.
        /// </summary>
        /// <param name="t">The amount of time to update this by.</param>
        void Update(TimeSpan t);
    }
}