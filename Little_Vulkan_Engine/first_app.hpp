#pragma once
#include "Lve_window.hpp"

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
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
    };
}