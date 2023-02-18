#pragma once

#include "blocks/Block.hpp"

namespace blocks
{
    class Air : public Block
    {
    public:
        Air()
        {
            type = BlockType::AIR;
            transparent = true;
            solid = false;
        }
        virtual glm::ivec2 GetTextureLocation()
        {
            return {0, 0};
        }
    };

}