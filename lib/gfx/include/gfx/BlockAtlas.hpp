#pragma once

#include <array>
#include "gfx/Atlas.hpp"
#include "gfx/Texture.hpp"
#include "gfx/gfx.hpp"

namespace gfx
{
    class BlockAtlas
    {
    public:
        BlockAtlas(std::string path, glm::ivec2 spriteSize);
        ~BlockAtlas() = default;

        void Update();

    private:
        static constexpr uint _FPS = 6;
        static constexpr uint _FRAMES = 16;

        void CopyPixels(uint8_t* pixels, glm::ivec2 imageSize, glm::ivec2 size, glm::ivec2 from, glm::ivec2 to);
        void CopyOffset(uint8_t* pixels, glm::ivec2 from, glm::ivec2 to);

        glm::ivec2 _size;
        glm::ivec2 _sizeSprites;
        glm::ivec2 _spriteSize;

        // std::array<Texture, _FRAMES> _frames;
        Atlas _atlas;
        size_t _ticks;
    };

}
