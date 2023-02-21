#pragma once
#include <glm/glm.hpp>

namespace world
{
    class World
    {
    public:
        World() = default;

        void Tick(){};
        void Update(){};
        void Render(){};

        static constexpr int CHUNK_SIZE = 32;

        static glm::ivec3 PosToBlock(glm::vec3 position)
        {
            return glm::ivec3{position};
        }
        static glm::ivec3 PosToOffset(glm::vec3 position)
        {
            return glm::ivec3{position / glm::vec3{CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}};
        }
    };
}