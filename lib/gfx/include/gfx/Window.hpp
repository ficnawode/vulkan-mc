#pragma once
#include "gfx/controls.hpp"
#include "gfx/gfx.hpp"
#include "glm/glm.hpp"

#include <algorithm>
#include <chrono>
#include <functional>

#define MOUSE_DEBUG_LOG 0
#define KEYBOARD_DEBUG_LOG 0
#define RESIZE_DEBUG_LOG 0

namespace gfx
{
    class Window
    {
    public:
        static Window* Instance();

        void Create(void (*init)(), void (*destroy)(), void (*tick)(), void (*update)(), void (*render)());

        void StartLoop();
        
        glm::ivec2 GetSize() const;

        void MouseSetGrabbed(bool grabbed);
    bool MouseGetGrabbed();

    private:
        Window();
        ~Window();

        GLFWwindow* _handle;
        static GLFWwindow* _instance;
        glm::ivec2 _size;

        void (*_init)();
        void (*_destroy)();
        void (*_tick)();
        void (*_update)();
        void (*_render)();

        void Init();
        void Destroy();
        void Tick();
        void Update();
        void Render();

        Mouse _mouse;
        Keyboard _keyboard;

        std::chrono::time_point<std::chrono::system_clock> _lastSecond;
        std::chrono::time_point<std::chrono::system_clock> _lastFrame;

        std::uint64_t _frames;
        std::uint64_t _fps;
        std::chrono::nanoseconds _frameDelta;

        std::uint64_t _ticks;
        std::uint64_t _tps;
        std::chrono::nanoseconds _tickRemainder;

        void (*_size_callback)(GLFWwindow*, int, int) =
            [](GLFWwindow* handle, int width, int height)
        {
            glViewport(0, 0, width, height);
            Instance()->_size = {width, height};
#if RESIZE_DEBUG_LOG == 1
            printf("Size changed to:%d, %d \n", width, height);
#endif
        };

        void (*_cursor_callback)(GLFWwindow*, double, double) =
            [](GLFWwindow* handle, double xp, double yp)
        {
            glm::vec2 p = {xp, yp};

            Instance()->_mouse.delta = p - Instance()->_mouse.position;
            Instance()->_mouse.delta.x =
                std::clamp(Instance()->_mouse.delta.x, -100.0f, 100.0f);
            Instance()->_mouse.delta.y =
                std::clamp(Instance()->_mouse.delta.y, -100.0f, 100.0f);

            Instance()->_mouse.position = p;
#if MOUSE_DEBUG_LOG == 1
            printf("Mouse Position:%f, %f \n", p.x, p.y);
#endif
        };

        void (*_key_callback)(GLFWwindow*, int, int, int, int) =
            [](GLFWwindow* handle, int key, int scancode, int action, int mods)
        {
            if(key < 0)
            {
                return;
            }

            switch(action)
            {
            case GLFW_PRESS:
                Instance()->_keyboard.keys[key].down = true;
#if KEYBOARD_DEBUG_LOG == 1
                printf("Key Pressed \n");
#endif
                break;
            case GLFW_RELEASE:
                Instance()->_keyboard.keys[key].down = false;
#if KEYBOARD_DEBUG_LOG == 1
                printf("Key Released \n");
#endif
                break;
            default:
                break;
            }
        };

        void (*_mouse_callback)(GLFWwindow*, int, int, int) =
            [](GLFWwindow* handle, int button, int action, int mods)
        {
            if(button < 0)
            {
                return;
            }

            switch(action)
            {
            case GLFW_PRESS:
                Instance()->_mouse.buttons[button].down = true;
#if MOUSE_DEBUG_LOG == 1
                printf("Mouse Pressed \n");
#endif
                break;
            case GLFW_RELEASE:
                Instance()->_mouse.buttons[button].down = false;
#if MOUSE_DEBUG_LOG == 1
                printf("Mouse Released \n");
#endif
                break;
            default:
                break;
            }
        };

        void (*_error_callback)(int, const char*) = [](int code, const char* description)
        { fprintf(stderr, "GLFW error %d: %s\n", code, description); };
    };
}