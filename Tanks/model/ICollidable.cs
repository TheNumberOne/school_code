namespace Tanks.model
{
    /// <summary>
    /// Represents an object that can collide with other objects.
    /// </summary>
    public interface ICollidable
    {
        /// <summary>
        /// Returns a shape representing the collision box of this element.
        /// </summary>
        Shape CollisionContainer { get; }
    }
}