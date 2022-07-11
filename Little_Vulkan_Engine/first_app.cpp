#include "first_app.hpp"
#include <stdexcept>
namespace lve
{
    first_app::first_app()
    {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    first_app::~first_app()
    {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }
    
    void first_app::Run()
    {
        while(!window.shouldClose())
            glfwPollEvents();
    }

    void first_app::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void first_app::createPipeline()
    {
        auto pipelineConfig = Lvepipeline::defaultPipelineConfigInfo(swapchain.width(), swapchain.height());
        pipelineConfig.renderPass = swapchain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Lvepipeline>(
            device,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig
        );
    }

    void first_app::createCommandBuffers() { }
    void first_app::drawFrame() { }
}