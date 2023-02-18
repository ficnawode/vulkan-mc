#pragma once
#include <array>
#include "gfx/Window.hpp"
#include "gfx/gfx.hpp"
#include "glm/glm.hpp"

struct Button
{
    bool down;
    bool last;
    bool last_tick;
    bool pressed;
    bool pressed_tick;
};

struct Mouse
{
    std::array<Button, GLFW_MOUSE_BUTTON_LAST> buttons;
    glm::vec2 position;
    glm::vec2 delta;
};

struct Keyboard
{
    std::array<Button, GLFW_KEY_LAST> keys;
};