using System.Drawing;
using Tanks.utils;

namespace Tanks.model
{
    /// <inheritdoc />
    /// <summary>
    ///     Represents a rock in the game.
    /// </summary>
    public class Rock: ICollidable
    {
        /// <summary>
        ///     Used to cache the border. Useful for decreasing slow game speeds.
        /// </summary>
        private Shape _borderCache;
        private PointF _borderCacheCenter;

        public PointF Location;

        public Rock(PointF location, Shape prototype)
        {
            Location = location;
            Prototype = prototype;
        }

        private Shape Prototype { get; }

        public Shape Border
        {
            get
            {
                // Reset the cache if the location has changed.
                if (Location != _borderCacheCenter) _borderCache = null;

                _borderCacheCenter = Location;
                return _borderCache ?? (_borderCache = Prototype.Transform(p => p.Plus(Location)));
            }
        }
        
        /// <inheritdoc />
        public Shape CollisionContainer => Border;
    }
}