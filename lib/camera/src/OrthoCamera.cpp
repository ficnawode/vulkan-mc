#include "camera/OrthoCamera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace camera
{
    OrthoCamera::OrthoCamera( glm::vec2 min, glm::vec2 max) :
        _min{min}, _max{max}
    {
        Update();
    }

    void OrthoCamera::Update()
    {
        _view = glm::mat4{1};
        _proj = glm::ortho(_min.x, _max.x, _min.y, _max.y, -100.0f, 100.0f);
    }

}
