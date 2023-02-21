#pragma once

#include "gfx/Window.hpp"
#include "gfx/gfx.hpp"
#include "phase_lambdas.hpp"
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

    void StartLoop()
    {
        _renderer = new renderer::Renderer;
        _window->StartLoop();
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
        return _renderer;
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
        _window = gfx::Window::Instance();
        _window->Create(init, destroy, tick, update, render);
    }

    ~State()
    {
    }

    gfx::Window* _window;
    renderer::Renderer* _renderer;
    world::World _world;
    // struct UI ui;
    size_t _ticks;

    void (*init)() = []() { Instance()->GetWindow()->MouseSetGrabbed(true); };
    void (*destroy)() = []() {};
    void (*tick)() = []()
    {
        Instance()->IncrementTicks();
        Instance()->GetWorld()->Tick();
        // State::Instance().
    };
    void (*update)() = []()
    {
        Instance()->GetRenderer()->Update();
        Instance()->GetWorld()->Update();

        // wireframe toggle (T)
        if(Instance()->GetWindow()->GetKeyboard().keys[GLFW_KEY_T].pressed)
        {
            Instance()->GetRenderer()->ToggleWireframe();
        }

        // mouse toggle (ESC)
        if(Instance()->GetWindow()->GetKeyboard().keys[GLFW_KEY_ESCAPE].pressed)
        {
            bool grabbed = Instance()->GetWindow()->MouseGetGrabbed();
            Instance()->GetWindow()->MouseSetGrabbed(!grabbed);
        }
    };
    void (*render)() = []()
    {
        Instance()->GetRenderer()->Prepare(renderer::RenderPass::p3D);
        Instance()->GetWorld()->Render();
    };
};
