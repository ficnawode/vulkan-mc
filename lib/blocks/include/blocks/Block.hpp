#pragma once

#include "blocks/types.hpp"
#include "gfx/AABB.hpp"
#include "glm/glm.hpp"
#include "util/Direction.hpp"

class World;

// Block abstract class
namespace blocks
{
    class Block
    {
    public:
        Block();
        ~Block() = default;

        virtual glm::ivec2 GetTextureLocation() = 0;
        // virtual void GetMeshInformation(
        //     World* world,
        //     glm::ivec3 position,
        //     util::Direction direction,
        //     glm::vec3* offsetOut,
        //     glm::vec2 sizeOut,
        //     glm::ivec2 uvOffestOut,
        //     glm::ivec2 uvSizeOut) = 0;
        virtual inline gfx::AABB GetAABB(glm::ivec3 pos)
        {
            return {pos, {pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f}};
        }

    protected:
        BlockType type;

        bool transparent = false;
        bool liquid = false;
        bool solid = true;
    };

}
