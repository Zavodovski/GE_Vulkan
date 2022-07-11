#pragma once

#include "Lve_device.hpp"

#include <string>
#include <vector>
namespace lve
{

    struct PipelineConfigInfo 
    {
        //PipelineConfigInfo() = default;
        //PipelineConfigInfo(const PipelineConfigInfo&) = delete;
        //PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

        VkViewport viewport;
        VkRect2D scissor;
        //std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
        //std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        //std::vector<VkDynamicState> dynamicStateEnables;
        //VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class Lvepipeline
    {
    public:
        Lvepipeline(LveDevice& device, 
                    const std::string& vertFilepath, 
                    const std::string& fragFilepath,
                    const PipelineConfigInfo& configInfo);
        ~Lvepipeline();

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