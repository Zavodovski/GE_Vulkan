#pragma once
#include "Lve_window.hpp"
#include "Lve_pipeline.hpp"
#include "Lve_device.hpp"
namespace lve
{
    class first_app
    {
    public:
        //first_app();
        //~first_app();
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        void Run();

    private:
        Lvewindow window{WIDTH, HEIGHT, "Hello Vulkan"};
        LveDevice device{window};
        Lvepipeline pipeline{
            device, 
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv", 
            Lvepipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
        
    };
}