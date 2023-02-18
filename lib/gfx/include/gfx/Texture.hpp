#pragma once
#include "gfx/RGBAImage.hpp"
#include "gfx/gfx.hpp"

#include <string>
#include <vector>
#include "glm/glm.hpp"

namespace gfx
{

    class Texture
    {
    public:
        Texture(RGBAImage image);
        
        Texture(std::string path) : Texture(RGBAImage{path})
        {
        }
        ~Texture();

        void Bind();

        glm::ivec2 GetSize() const
        {
            return _size;
        }
        glm::vec2 GetUvUnit() const
        {
            return _uvUnit;
        }

    private:
        GLuint _handle;
        glm::ivec2 _size;
        glm::vec2 _uvUnit;
    };

};
