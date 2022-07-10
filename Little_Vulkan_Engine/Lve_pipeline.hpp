#pragma once

#include "Lve_device.hpp"

#include <string>
#include <vector>
namespace lve
{

    struct PipelineConfigInfo {};

    class Lvepipeline
    {
    public:
        Lvepipeline(LveDevice& device, 
                    const std::string& vertFilepath, 
                    const std::string& fragFilepath,
                    const PipelineConfigInfo& configInfo);
        ~Lvepipeline() {}

        Lvepipeline(const Lvepipeline&) = delete;
        Lvepipeline& operator=(const Lvepipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> ReadFile(const std::string& filepath);
        void CreateGraphicsPipeline(const std::string& vertFilepath, 
                                    const std::string& fragFilepath, 
                                    const PipelineConfigInfo& configInfo);
        
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
        
        LveDevice& lveDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;

    };
}