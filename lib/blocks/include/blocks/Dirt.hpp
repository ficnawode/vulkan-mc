#include "blocks/Block.hpp"

namespace blocks
{
    class Dirt : public Block
    {
    public:
        Dirt()
        {
            type = BlockType::DIRT;
        }

        virtual glm::ivec2 GetTextureLocation()
        {
            return {2, 0};
        }
    };
}