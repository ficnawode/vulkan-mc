#include "render/Renderer.hpp"
#include "gfx/Window.hpp"

namespace renderer
{
    Renderer::Renderer() :
        _perspectiveCamera{5.0 * M_PI / 12.0},
        _orthoCamera{{0, 0}, gfx::Window::Instance()->GetSize()},
        _vao{},
        _vbo{GL_ARRAY_BUFFER, true},
        _ibo{GL_ELEMENT_ARRAY_BUFFER, true},
        _blockAtlas{"res/images/blocks.png", {16, 16}}
    {
        using namespace gfx;
        using VA = VertexAttr;

        _cameraType = camera::CameraType::PERSPECTIVE;
        _currentShaderType = ShaderType::NONE;

        std::array basicTextureAttributes = {VA{0, "position"}, VA{1, "uv"}};

        _shaders.insert(
            {ShaderType::BASIC_TEXTURE,
             Shader(
                 "res/shaders/basic_texture.vs", "res/shaders/basic_texture.fs", basicTextureAttributes)});

        std::array chunkAttributes = {
            VA{0, "position"}, VA{1, "uv"}, VA{2, "color"}};

        _shaders.insert(
            {ShaderType::CHUNK,
             Shader("res/shaders/chunk.vs", "res/shaders/chunk.fs", chunkAttributes)});

        std::array skyAttributes = {VA{0, "position"}, VA{1, "uv"}};

        _shaders.insert(
            {ShaderType::SKY,
             Shader("res/shaders/sky.vs", "res/shaders/sky.fs", skyAttributes)});

        std::array basicColorAttributes = {VA{0, "position"}};
        _shaders.insert(
            {ShaderType::BASIC_COLOR,
             Shader("res/shaders/basic_color.vs", "res/shaders/basic_color.fs", basicColorAttributes)});

        _textures.insert({Textures::CROSSHAIR, Texture("res/images/crosshair.png")});
        _textures.insert({Textures::CLOUDS, Texture("res/images/clouds.png")});
        _textures.insert({Textures::STAR, Texture("res/images/star.png")});
        _textures.insert({Textures::SUN, Texture("res/images/sun.png")});
        _textures.insert({Textures::MOON, Texture("res/images/moon.png")});
        _textures.insert({Textures::HOTBAR, Texture("res/images/hotbar.png")});
    }

    void Renderer::Init()
    {
    }
    void Renderer::Update()
    {
        _blockAtlas.Update();
    }
    void Renderer::Destroy()
    {
    }
    void Renderer::Prepare(RenderPass renderPass)
    {
    }
    void Renderer::SetCamera(camera::CameraType cameraType)
    {
    }
    void Renderer::PushCamera()
    {
    }
    void Renderer::PopCamera()
    {
    }
    void Renderer::SetViewProj()
    {
    }
    void Renderer::UseShader(ShaderType shaderType)
    {
    }
    void Renderer::QuadColor(struct Renderer* self, glm::vec2 size, glm::vec4 color, glm::mat4 model)
    {
    }

    void Renderer::QuadTexture(

        gfx::Texture texture,
        glm::vec2 size,
        glm::vec4 color,
        glm::vec2 uvMin,
        glm::vec2 uvMax,
        glm::mat4 model)
    {
    }
    void Renderer::AABB(gfx::AABB aabb, glm::vec4 color, glm::mat4 model, FillMode fillMode)
    {
    }
}