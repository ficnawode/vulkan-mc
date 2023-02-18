#include "gfx/RGBAImage.hpp"
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace gfx
{
    RGBAImage::RGBAImage(std::string path)
    {
        int width, height, channels;

        // OpenGL has texture coordinates with (0, 0) on bottom
        stbi_set_flip_vertically_on_load(true);
        unsigned char* image =
            stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        assert(image != NULL);

        _width = width;
        _height = height;

        size_t imageSize = _width * _height * 4;
        _pixels.reserve(imageSize);
        _pixels.insert(_pixels.begin(), image, image + imageSize);

        stbi_image_free(image);
    }

    RGBAImage::RGBAImage(std::uint8_t* pixels, std::size_t width, std::size_t height) :
        _width{width}, _height{height}
    {
        _pixels.reserve(_width * _height * 4);
        _pixels.insert(_pixels.begin(), pixels, pixels + _width * _height * 4);
    }

}
