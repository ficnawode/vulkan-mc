#pragma once
#include <tuple>
#include <gfx/Texture.hpp>

namespace gfx
{
    class Atlas
    {
    public:
        Atlas(Texture texture, glm::vec2 spriteSize);
        Atlas(std::string path, glm::vec2 spriteSize) :
            Atlas(Texture(path), spriteSize){};
        ~Atlas();

        void Update();

        std::tuple<glm::vec2, glm::vec2> GetFragmentUvCords(glm::ivec2 pos);

        glm::ivec2 GetSize() const
        {
            return _size;
        }

        glm::ivec2 GetSpriteSize() const
        {
            return _spriteSize;
        }

        glm::vec2 GetSpriteUnit() const
        {
            return _spriteUnit;
        }

        glm::vec2 GetPixelUnit() const
        {
            return _pixelUnit;
        }

    private:
        Texture _texture;

        glm::ivec2 _size;
        glm::ivec2 _spriteSize;
        glm::vec2 _spriteUnit;
        glm::vec2 _pixelUnit;
    };

}