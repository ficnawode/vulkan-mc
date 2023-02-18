#include "gfx/BlockAtlas.hpp"

namespace gfx
{
    void BlockAtlas::CopyPixels(uint8_t* pixels, glm::ivec2 imageSize, glm::ivec2 size, glm::ivec2 from, glm::ivec2 to)
    {
        for(int j = 0; j < size.y; j++)
        {
            for(int i = 0; i < size.x; i++)
            {
                pixels[((to.y + j) * imageSize.x + (to.x + i)) * 4] =
                    pixels[((from.y + j) * imageSize.x + (from.x + i)) * 4];
            }
        }
    }

    void BlockAtlas::CopyOffset(uint8_t* pixels, glm::ivec2 from, glm::ivec2 to)
    {
        CopyPixels(
            pixels,
            _size,
            _spriteSize,
            _spriteSize * glm::ivec2(from.x, _sizeSprites.y - from.y - 1),
            _spriteSize * glm::ivec2(to.x, _sizeSprites.y - to.y - 1));
    }

    BlockAtlas::BlockAtlas(std::string path, glm::ivec2 spriteSize) :
        _atlas{path, spriteSize}, _spriteSize{spriteSize}
    {
    }

    void BlockAtlas::Update()
    {
    }
}