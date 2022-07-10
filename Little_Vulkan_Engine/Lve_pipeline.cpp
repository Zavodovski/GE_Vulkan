#include "Lve_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
namespace lve
{
    Lvepipeline::Lvepipeline(LveDevice& device, 
                            const std::string& vertFilepath, 
                            const std::string& fragFilepath, 
                            const PipelineConfigInfo& configInfo) : lveDevice(device)
    {
        CreateGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
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

    void Lvepipeline::CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo)
    {
        auto vertcode = ReadFile(vertFilepath);
        auto fragcode = ReadFile(fragFilepath);

        std::cout << "vertcode Size: " << vertcode.size() << "\n";
        std::cout << "fragcode Size: " << fragcode.size() << "\n";

    }

    void Lvepipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if(vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
            throw std::runtime_error("failed to create shader module");
    }

    PipelineConfigInfo Lvepipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
    {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }
}