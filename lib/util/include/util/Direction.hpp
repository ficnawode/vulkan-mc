#pragma once
#include <glm/glm.hpp>

namespace util
{
    enum class Direction
    {
        NORTH = 0,
        SOUTH = 1,
        EAST = 2,
        WEST = 3,
        UP = 4,
        DOWN = 5
    };

    glm::ivec3 DirectionToIvec(Direction direction)
    {
        static constexpr glm::ivec3 DIRECTION_IVEC[6] = {
            {0, 0, -1},
            {0, 0, 1},
            {1, 0, 0},
            {-1, 0, 0},
            {0, 1, 0},
            {0, -1, 0},
        };
        return DIRECTION_IVEC[(int)direction];
    }

    glm::ivec3 DirectionToVec(Direction direction)
    {
        static constexpr glm::vec3 DIRECTION_VEC[6] = {
            {0, 0, -1},
            {0, 0, 1},
            {1, 0, 0},
            {-1, 0, 0},
            {0, 1, 0},
            {0, -1, 0},
        };
        return DIRECTION_VEC[(int)direction];
    }

}
