#pragma once
#include "Lve_window.hpp"
#include "Lve_pipeline.hpp"
namespace lve
{
    class first_app
    {
    public:
        //first_app();
        //~first_app();
        void Run();

    private:
        Lvewindow window{WIDTH, HEIGHT, "Hello Vulkan"};
        Lvepipeline pipeline{"shaders/simple_shader.vert.spv","shaders/simple_shader.frag.spv"};
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
    };
}