#include "gfx/Texture.hpp"

namespace gfx
{

    Texture::Texture(RGBAImage image)
    {
        _size = {image.GetWidth(), image.GetHeight()};

        glGenTextures(1, &_handle);
        glBindTexture(GL_TEXTURE_2D, _handle);

        // No interpolation
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            image.GetWidth(),
            image.GetHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image.GetPixels().data());
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &_handle);
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, _handle);
    }

}