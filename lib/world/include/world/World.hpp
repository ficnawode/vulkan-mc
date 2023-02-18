#pragma once
#include <glm/glm.hpp>

namespace world
{
    class World
    {
    public:
        World() = default;

        void Tick();
        void Update();
        void Render();

        static glm::ivec3 PosToBlock(glm::vec3 position)
        {
            return glm::ivec3{position};
        }
    };
}