#pragma once

#include "backend/Pipeline.hpp"
#include "backend/Window.hpp"

namespace vkmc
{
    class State
    {
        // State();
        // ~State();

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        void Run();

    private:
        Window _window{800, 600, "hi vulkan"};
        Pipeline _pipeline{"shaders/simple_shader.vert.spv",
                           "shaders/simple_shader.frag.spv"};
    };

}