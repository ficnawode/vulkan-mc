#pragma once

#include <map>
#include "camera/camera.hpp"
#include "gfx/AABB.hpp"
#include "gfx/Atlas.hpp"
#include "gfx/BlockAtlas.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Vao.hpp"
#include "gfx/Vbo.hpp"
#include "gfx/gfx.hpp"
#include "render/types.hpp"

namespace renderer
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() = default;

        void Init();
        void Update();
        void Destroy();
        void Prepare(RenderPass renderPass);
        void SetCamera(camera::CameraType cameraType);
        void PushCamera();
        void PopCamera();
        void SetViewProj();
        void UseShader(ShaderType shaderType);
        void QuadColor(struct Renderer* self, glm::vec2 size, glm::vec4 color, glm::mat4 model);

        void QuadTexture(
            gfx::Texture texture,
            glm::vec2 size,
            glm::vec4 color,
            glm::vec2 uvMin,
            glm::vec2 uvMax,
            glm::mat4 model);
        void AABB(gfx::AABB aabb, glm::vec4 color, glm::mat4 model, FillMode fillMode);

        void ToggleWireframe()
        {
            _wireframe = !_wireframe;
        }

    private:
        camera::CameraType _cameraType;
        struct
        {
            std::array<camera::CameraType, CAMERA_STACK_MAX> array;
            size_t size = 0;
        } _cameraStack;

        camera::PerspectiveCamera _perspectiveCamera;
        camera::OrthoCamera _orthoCamera;

        std::map<ShaderType, gfx::Shader> _shaders;

        ShaderType _currentShaderType;
        gfx::Shader* _shaderRef;

        std::map<Textures, gfx::Texture> _textures;

        gfx::BlockAtlas _blockAtlas;

        glm::vec4 _clearColor;

        gfx::VBO _vbo;
        gfx::VBO _ibo;
        gfx::VAO _vao;

        bool _wireframe = false;
    };
}
