#include "gfx/Window.hpp"
#include <chrono>
#include <gsl/span>

namespace gfx
{
    Window* Window::Instance()
    {
        static Window* instance = new Window;
        return instance;
    }

    void Window::Create(void (*init)(), void (*destroy)(), void (*tick)(), void (*update)(), void (*render)())
    {
        _init = init;
        _destroy = destroy;
        _tick = tick;
        _update = update;
        _render = render;

        _lastFrame = std::chrono::system_clock::now();
        _lastSecond = std::chrono::system_clock::now();

        glfwSetErrorCallback(_error_callback);

        if(!glfwInit())
        {
            fprintf(stderr, "%s", "error initializing GLFW\n");
            exit(1);
        }

        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        _size = {1280, 720};
        _handle = glfwCreateWindow(_size.x, _size.y, "Project", nullptr, nullptr);
        if(_handle == NULL)
        {
            fprintf(stderr, "%s", "error creating window\n");
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(_handle);

        glewExperimental = GL_TRUE;

        if(glewInit() != GLEW_OK)
        {
            fprintf(stderr, "%s", "error initializing GLEW\n");
            exit(1);
        }

        // configure callbacks
        glfwSetFramebufferSizeCallback(_handle, _size_callback);
        glfwSetCursorPosCallback(_handle, _cursor_callback);
        glfwSetKeyCallback(_handle, _key_callback);
        glfwSetMouseButtonCallback(_handle, _mouse_callback);

        glfwSwapInterval(1);
    }

    Window::Window()
    {
    }

    Window::~Window()
    {
        Destroy();
    }

    using clock = std::chrono::high_resolution_clock;
    using namespace std::chrono_literals;

    void Window::StartLoop()
    {
        Init();
        MouseSetGrabbed(false);

        while(!glfwWindowShouldClose(_handle))
        {
            auto now = clock::now();

            _frameDelta = now - _lastFrame;
            _lastFrame = now;

            if(now - _lastSecond > 1000ms)
            {
                _fps = _frames;
                _tps = _ticks;
                _frames = 0;
                _ticks = 0;
                _lastSecond = now;

                printf("FPS: %lu | TPS: %lu\n", _fps, _tps);
            }

            // tick processing
            std::chrono::nanoseconds NS_PER_TICK = 16ms;
            auto tickTime = _frameDelta + _tickRemainder;
            while(tickTime > NS_PER_TICK)
            {
                Tick();
                tickTime -= NS_PER_TICK;
            }
            _tickRemainder = (tickTime > 0ns) ? tickTime : -tickTime;

            Update();
            Render();
            glfwSwapBuffers(_handle);
            glfwPollEvents();
        }
    }

    glm::ivec2 Window::GetSize() const
    {
        return _size;
    }

    static void button_array_tick(gsl::span<Button> buttons)
    {
        for(Button b: buttons)
        {
            b.pressed_tick = b.down && !b.last_tick;
            b.last_tick = b.down;
        }
    }

    static void button_array_update(gsl::span<Button> buttons)
    {
        for(Button b: buttons)
        {
            b.pressed = b.down && !b.last;
            b.last = b.down;
        }
    }

    void Window::Init()
    {
        _init();
    }

    void Window::Destroy()
    {
        _destroy();
        glfwTerminate();
    }

    void Window::Tick()
    {
        _ticks++;
        button_array_tick(_mouse.buttons);
        button_array_tick(_keyboard.keys);
        _tick();
    }
    void Window::Update()
    {
        button_array_update(_mouse.buttons);
        button_array_update(_keyboard.keys);
        _update();

        _mouse.delta = glm::vec2{0, 0};
    }

    void Window::Render()
    {
        _frames++;
        _render();
    }

    void Window::MouseSetGrabbed(bool grabbed)
    {
        glfwSetInputMode(_handle, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    bool Window::MouseGetGrabbed()
    {
        return glfwGetInputMode(_handle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
    }
}