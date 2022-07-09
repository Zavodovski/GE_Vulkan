#include "Lve_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
namespace lve
{
    Lvepipeline::Lvepipeline(const std::string& vertFilepath, const std::string& fragFilepath)
    {
        CreateGraphicsPipeline(vertFilepath, fragFilepath);
    }
    std::vector<char> Lvepipeline::ReadFile(const std::string& filepath)
    {
        std::ifstream file{filepath, std::ios::ate | std::ios::binary};

        if(!file.is_open()) 
            std::runtime_error("Failed to open file: " + filepath);
        
        size_t fileSize = static_cast<size_t>(file.tellg());
        file.seekg(0);
        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    void Lvepipeline::CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath)
    {
        auto vertcode = ReadFile(vertFilepath);
        auto fragcode = ReadFile(fragFilepath);

        std::cout << "vertcode Size: " << vertcode.size() << "\n";
        std::cout << "fragcode Size: " << fragcode.size() << "\n";

    }
}