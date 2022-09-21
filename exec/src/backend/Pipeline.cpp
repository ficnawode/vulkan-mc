#include "backend/Pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace vkmc
{
    Pipeline::Pipeline(
        const std::string& vertexShaderFilepath,
        const std::string& fragmentShaderFilepath)
    {
        CreateGraphicsPipeline(
            vertexShaderFilepath, fragmentShaderFilepath);
    }

    std::vector<char> Pipeline::ReadFile(const std::string& filepath)
    {
        std::ifstream file{
            filepath, std::ios::ate | std::ios::binary};

        if(!file.is_open())
        {
            throw std::runtime_error(
                "failed to open file: " + filepath);
        }

        auto fileSize = static_cast<std::size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }

    void Pipeline::CreateGraphicsPipeline(
        const std::string& vertexShaderFilepath,
        const std::string& fragmentShaderFilepath)
    {
        auto vertexShader = ReadFile(vertexShaderFilepath);
        auto fragmentShader = ReadFile(fragmentShaderFilepath);

        std::cout << "Vertex shader code size: "
                  << vertexShader.size() << "\n";
        std::cout << "Fragment shader code size: "
                  << fragmentShader.size() << "\n";
    }
}