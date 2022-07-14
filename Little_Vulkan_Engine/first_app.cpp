#include "first_app.hpp"
#include <stdexcept>
#include <array>

namespace lve
{
    first_app::first_app()
    {
        loadModels();
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
        {
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(device.device());
    }

    void first_app::loadModels()
    {
        std::vector<LveModel::Vertex> vertices{
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, 
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
        };

        model = std::make_unique<LveModel>(device, vertices);
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

    void first_app::createCommandBuffers() 
    { 
        commandbuffers.resize(swapchain.imageCount());
        
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandbuffers.size());

        if(vkAllocateCommandBuffers(device.device(), &allocInfo, commandbuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for(int i = 0; i < commandbuffers.size(); i ++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if(vkBeginCommandBuffer(commandbuffers[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = swapchain.getRenderPass();
            renderPassInfo.framebuffer = swapchain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapchain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();
            vkCmdBeginRenderPass(commandbuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        
            pipeline->bind(commandbuffers[i]);
            //vkCmdDraw(commandbuffers[i], 3, 1, 0, 0);
            model->bind(commandbuffers[i]);
            model->draw(commandbuffers[i]);

            vkCmdEndRenderPass(commandbuffers[i]);
            if(vkEndCommandBuffer(commandbuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
    void first_app::drawFrame() 
    {
        uint32_t imageIndex;
        auto result = swapchain.acquireNextImage(&imageIndex);
        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = swapchain.submitCommandBuffers(&commandbuffers[imageIndex], &imageIndex);
        if(result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }
}