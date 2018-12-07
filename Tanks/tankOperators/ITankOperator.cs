using Tanks.model;

namespace Tanks
{
    public interface ITankOperator
    {
        void Update(Tank tank, Game game);
    }
}