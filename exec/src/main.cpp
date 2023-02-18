#include <iostream>
#include "State.hpp"

// #include "gfx/gfx.hpp"

void (*init)() = []()
{
    State::Instance()->Create(gfx::Window::Instance());
    State::Instance()->GetRenderer()->Init();
    State::Instance()->GetWindow()->MouseSetGrabbed(true);
};
void (*destroy)() = []() {};
void (*tick)() = []()
{
    State::Instance()->IncrementTicks();
    // State::Instance().
};
void (*update)() = []() {};
void (*render)() = []() {};

int main()
{
    gfx::Window::Instance()->Create(init, destroy, tick, update, render);
    gfx::Window::Instance()->StartLoop();
}