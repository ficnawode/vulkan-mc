
#pragma once

#include "camera/PerspectiveCamera.hpp"
#include "entity/Component.hpp"
#include "entity/Player.hpp"

namespace entity
{
    class CameraComp : public Component
    {
    public:
        CameraComp(Player& player) : _player{player}, _camera{1.3f}
        {
        }

        void Init()
        {
            PositionComp* position = _player.GetPositionC();
            _camera.SetPos(position->GetPosition());
        }
        void Render()
        {
        }
        void Update()
        {
            PositionComp* position = _player.GetPositionC();
            _camera.SetPos(position->GetPosition() + glm::vec3{position->GetOffset()});
            _camera.Update();
        }
        void Tick()
        {
        }

    private:
        Player& _player;

        glm::vec3 offset;
        camera::PerspectiveCamera _camera;
    };

}