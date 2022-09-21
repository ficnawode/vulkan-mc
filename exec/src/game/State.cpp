#include "game/State.hpp"

namespace vkmc
{
    void State::Run()
    {
        while(!_window.ShouldClose())
        {
            glfwPollEvents();
        }
    }
}