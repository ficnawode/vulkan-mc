#include "camera/PerspectiveCamera.hpp"
#include <algorithm>
#include <cmath>
#include "glm/gtc/matrix_transform.hpp"

namespace camera
{
    PerspectiveCamera::PerspectiveCamera(double fov) : _fov{fov}
    {
        _aspect = ((float)gfx::Window::Instance()->GetSize().x) /
            ((float)gfx::Window::Instance()->GetSize().y);
        _zNear = 0.01f;
        _zFar = 1000.0f;
        Update();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::Update()
    {
        // bound pitch at +- pi/2 and yaw in [0, tau]
        _pitch = std::clamp(_pitch, -M_PI_2, M_PI_2);

        _yaw = (_yaw < 0 ? 2 * M_PI : 0.0f) + fmodf(_yaw, 2 * M_PI);

        _direction = {cosf(_pitch) * sinf(_yaw), sinf(_pitch), cosf(_pitch) * cosf(_yaw)};
        _direction = glm::normalize(_direction);

        _right = glm::cross({0.0f, 1.0f, 0.0f}, _direction);
        _up = glm::cross(_direction, _right);
        _view = glm::lookAt(_position, _position + _direction, _up);
        _proj = glm::perspective(_fov, _aspect, _zNear, _zFar);
    }

}