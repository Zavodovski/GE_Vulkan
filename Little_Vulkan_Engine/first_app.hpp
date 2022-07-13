#pragma once
#include "Lve_window.hpp"
#include "Lve_pipeline.hpp"
#include "Lve_device.hpp"
#include "Lve_swap_chain.hpp"
#include "Lve_model.hpp"

//std
#include <memory>
#include <vector>
namespace lve
{
    class first_app
    {
    public:
        first_app();
        ~first_app();

        first_app(const first_app&) = delete;
        first_app& operator=(const first_app&) = delete;
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        void Run();

    private:
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        Lvewindow window{WIDTH, HEIGHT, "Hello Vulkan"};
        LveDevice device{window};
        LveSwapChain swapchain{device, window.getExtent()};
        
        std::unique_ptr<Lvepipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandbuffers;
        std::unique_ptr<LveModel> model;
    };
}