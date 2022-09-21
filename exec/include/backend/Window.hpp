#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>

namespace vkmc
{
    class Window
    {
    public:
        Window(std::int32_t width, std::int32_t height, std::string name);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ShouldClose();

    private:
        void init();

        std::int32_t _width;
        std::int32_t _height;

        std::string _name;
        GLFWwindow* _window;
    };

    inline bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(_window);
    }
}