#include "backend/Window.hpp"

namespace vkmc
{
    Window::Window(std::int32_t width, std::int32_t height, std::string name) :
        _width(width),
        _height(height),
        _name(name)
    {
        init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(_window);
    }

    void Window::init()
    {
        glfwInit();

        // disable opengl context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // disable resizability
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
    }
}