#include "gfx/Atlas.hpp"

namespace gfx
{
    Atlas::Atlas(Texture texture, glm::vec2 spriteSize) :
        _texture{texture}, _spriteSize{spriteSize}
    {
        _spriteUnit = _spriteSize / _texture.GetSize();
        _pixelUnit = glm::vec2{1, 1} / glm::vec2{_texture.GetSize()};
        _size = _texture.GetSize() / _spriteSize;
    }

    Atlas::~Atlas()
    {
    }

    std::tuple<glm::vec2, glm::vec2> Atlas::GetFragmentUvCords(glm::ivec2 pos)
    {
        glm::ivec2 p_min = {
            pos.x * _spriteSize.x, (_size.y - pos.y - 1) * _spriteSize.y};

        glm::vec2 uv_min = p_min / _texture.GetSize();
        glm::vec2 uv_max = (p_min + _spriteSize) / _texture.GetSize();
        return {uv_min, uv_max};
    }
}
