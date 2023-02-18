
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <gsl/span>


namespace gfx
{
    class RGBAImage
    {
    public:
        RGBAImage(std::string path);
        RGBAImage(std::uint8_t* pixels, std::size_t width, std::size_t height);

        std::size_t GetWidth() const
        {
            return _width;
        }

        std::size_t GetHeight() const
        {
            return _height;
        }

        gsl::span<std::uint8_t> GetPixels()
        {
            return _pixels;
        }

    private:
        std::vector<std::uint8_t> _pixels;
        std::size_t _width, _height;
    };
}