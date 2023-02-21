#pragma once
#include "gfx/Window.hpp"

namespace camera
{
    class OrthoCamera
    {
    public:
        OrthoCamera(glm::vec2 min, glm::vec2 max);
        ~OrthoCamera() = default;

        void Update();

        glm::mat4 GetView()
        {
            return _view;
        }
        glm::mat4 GetProj()
        {
            return _proj;
        }

    private:
        glm::mat4 _view;
        glm::mat4 _proj;

        glm::vec2 _position;
        glm::vec2 _min;
        glm::vec2 _max;
    };
}