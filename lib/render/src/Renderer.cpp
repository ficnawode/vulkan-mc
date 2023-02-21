#include "render/Renderer.hpp"
#include <array>
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
        _clearColor = {1, 1, 1, 1};

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

    void Renderer::Update()
    {
        _blockAtlas.Update();
    }

    void Renderer::Prepare(RenderPass renderPass)
    {
        switch(renderPass)
        {
        case RenderPass::p2D:
            _orthoCamera = {
                glm::vec2{0, 0},
                {gfx::Window::Instance()->GetSize().x,
                 gfx::Window::Instance()->GetSize().y}};
            glClear(GL_DEPTH_BUFFER_BIT);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case RenderPass::p3D:
            float r = _clearColor.x;
            float g = _clearColor.y;
            float b = _clearColor.z;
            float a = _clearColor.w;
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPolygonMode(GL_FRONT_AND_BACK, _wireframe ? GL_LINE : GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        }
    }
    void Renderer::SetCamera(camera::CameraType cameraType)
    {
        _cameraType = cameraType;
    }
    void Renderer::PushCamera()
    {
        assert(_cameraStack.size + 1 < CAMERA_STACK_MAX);
        _cameraStack.array[_cameraStack.size++] = _cameraType;
    }
    void Renderer::PopCamera()
    {
        assert(_cameraStack.size > 0);
        _cameraType = _cameraStack.array[--_cameraStack.size];
    }
    void Renderer::SetViewProj()
    {
        glm::mat4 view, proj;
        switch(_cameraType)
        {
        case camera::CameraType::PERSPECTIVE:
            view = _perspectiveCamera.GetView();
            proj = _perspectiveCamera.GetProj();
            break;
        case camera::CameraType::ORTHO:
            view = _orthoCamera.GetView();
            proj = _orthoCamera.GetProj();
            break;
        }

        _shaderRef->Uniform(view, proj);
    }

    void Renderer::UseShader(ShaderType shaderType)
    {
        _currentShaderType = shaderType;
        _shaderRef = &_shaders[shaderType];
        _shaderRef->Bind();
    }

    void Renderer::QuadColor(struct Renderer* self, glm::vec2 size, glm::vec4 color, glm::mat4 model)
    {
        UseShader(ShaderType::BASIC_COLOR);
        SetViewProj();
        _shaderRef->Uniform("m", model);
        _shaderRef->Uniform("color", color);

        std::array<float, 12> vbo_data = {
            0,
            0,
            0,
            0,
            size.y,
            0,
            size.x,
            size.y,
            0,
            size.x,
            0,
            0,
        };
        _vbo.Buffer(vbo_data.data(), 0, sizeof(vbo_data));

        std::array<std::uint32_t, 6> ibo_data = {3, 0, 1, 3, 1, 2};
        _ibo.Buffer(ibo_data.data(), 0, sizeof(ibo_data));

        _vao.Attr(_vbo, 0, 3, GL_FLOAT, 0, 0);
        _vao.Bind();
        _ibo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    }

    void Renderer::QuadTexture(

        gfx::Texture texture,
        glm::vec2 size,
        glm::vec4 color,
        glm::vec2 uvMin,
        glm::vec2 uvMax,
        glm::mat4 model)
    {
        UseShader(ShaderType::BASIC_TEXTURE);
        SetViewProj();
        _shaderRef->Uniform("m", model);
        _shaderRef->Uniform("tex", texture, 0);
        _shaderRef->Uniform("color", color);

        std::array<float, 20> vbo_data = {0,       0,       0,       0,
                                          size.y,  0,       size.x,  size.y,
                                          0,       size.x,  0,       0,

                                          uvMin.x, uvMin.y, uvMin.x, uvMax.y,
                                          uvMax.x, uvMax.y, uvMax.x, uvMin.y};
        _vbo.Buffer(vbo_data.data(), 0, sizeof(vbo_data));

        std::array<std::uint32_t, 6> ibo_data = {3, 0, 1, 3, 1, 2};
        _ibo.Buffer(ibo_data.data(), 0, sizeof(ibo_data));

        _vao.Attr(_vbo, 0, 3, GL_FLOAT, 0, 0);
        _vao.Attr(_vbo, 1, 2, GL_FLOAT, 0, (4 * 3) * sizeof(float));

        _vao.Bind();
        _ibo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    }
    void Renderer::AABB(gfx::AABB aabb, glm::vec4 color, glm::mat4 model, FillMode fillMode)
    {
        UseShader(ShaderType::BASIC_COLOR);
        SetViewProj();
        _shaderRef->Uniform("m", model);
        _shaderRef->Uniform("color", color);

        std::array<std::uint32_t, 36> indices = {
            1, 0, 3, 1, 3, 2, // north (-z)
            4, 5, 6, 4, 6, 7, // south (+z)
            5, 1, 2, 5, 2, 6, // east (+x)
            0, 4, 7, 0, 7, 3, // west (-x)
            2, 3, 7, 2, 7, 6, // top (+y)
            5, 4, 0, 5, 0, 1  // bottom (-y)
        };

        glm::vec3 min = aabb[0], max = aabb[1];
        std::array<float, 24> vertices = {
            min.x, min.y, min.z, max.x, min.y, min.z,
            max.x, max.y, min.z, min.x, max.y, min.z,

            min.x, min.y, max.z, max.x, min.y, max.z,
            max.x, max.y, max.z, min.x, max.y, max.z,
        };

        _vbo.Buffer(vertices.data(), 0, sizeof(vertices));
        _ibo.Buffer(indices.data(), 0, sizeof(indices));

        _vao.Attr(_vbo, 0, 3, GL_FLOAT, 0, 0);

        _vao.Bind();
        _vbo.Bind();

        if(fillMode == FillMode::FILL)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if(fillMode == FillMode::LINE)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
    }
}