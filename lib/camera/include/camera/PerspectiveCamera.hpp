#pragma once
#include "gfx/Window.hpp"
#include "glm/glm.hpp"

namespace camera
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(double fov);
        ~PerspectiveCamera();
        void Update();

    private:
        glm::mat4 _view;
        glm::mat4 _proj;
        glm::vec3 _position;
        glm::vec3 _direction;
        glm::vec3 _up;
        glm::vec3 _right;
        double _pitch;
        double _yaw;
        double _fov;
        double _aspect;
        double _zNear;
        double _zFar;
    };

}