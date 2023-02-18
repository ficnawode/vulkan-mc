#pragma once
#include "gfx/Window.hpp"
#include "gfx/gfx.hpp"
#include "render/Renderer.hpp"
#include "world/World.hpp"

// #include "world/sky.h"
// #include "ui/ui.h"

class State
{
public:
    static State* Instance()
    {
        static State instance;
        return &instance;
    }

    void Create(gfx::Window* window)
    {
        _window = window;
    }

    gfx::Window* GetWindow() const
    {
        return _window;
    }

    world::World* GetWorld()
    {
        return &_world;
    }

    renderer::Renderer* GetRenderer()
    {
        return &_renderer;
    }

    size_t GetTicks()
    {
        return _ticks;
    }

    void IncrementTicks()
    {
        _ticks++;
    }

private:
    State()
    {
        _ticks = 0;
    }

    ~State()
    {
    }

    gfx::Window* _window;
    renderer::Renderer _renderer;
    world::World _world;
    // struct UI ui;
    size_t _ticks;
};
