#pragma once

#include "entity/Component.hpp"
#include "entity/Player.hpp"

namespace entity
{
    class ControlComp : public Component
    {
    public:
        ControlComp(Player& player) : _player{player}
        {
        }

        void Render()
        {
        }
        void Update()
        {
        }
        void Tick()
        {
        }

    private:
        Player& _player;

        float _mouseSensitivity;
    };

}