#pragma once
namespace renderer
{
    enum class FillMode
    {
        FILL,
        LINE
    };

#define SHADERS_LAST (unsigned)ShaderType::BASIC_COLOR
    enum class ShaderType
    {
        NONE = 0,
        CHUNK,
        SKY,
        BASIC_TEXTURE,
        BASIC_COLOR
    };

#define TEXTURE_LAST (unsigned)Textures::HOTBAR
    enum class Textures
    {
        CROSSHAIR,
        CLOUDS,
        STAR,
        SUN,
        MOON,
        HOTBAR
    };

#define CAMERA_STACK_MAX 256
    enum class RenderPass
    {
        p2D,
        p3D
    };
}
