#pragma once
#include "entity/CameraComp.hpp"
#include "entity/ControlComp.hpp"
#include "entity/MovementComp.hpp"
#include "entity/PositionComp.hpp"

namespace entity
{
    class Player
    {
    public:
        Player();
        void Render();
        void Update();
        void Tick();

        CameraComp* GetCameraC()
        {
            return &_camera;
        }

        ControlComp* GetControlC()
        {
            return &_control;
        }

        MovementComp* GetMovementC()
        {
            return &_movement;
        }

        PositionComp* GetPositionC()
        {
            return &_position;
        }

    private:
        CameraComp _camera;
        ControlComp _control;
        MovementComp _movement;
        PositionComp _position;
    };
}