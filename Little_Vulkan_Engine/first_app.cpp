#include "first_app.hpp"

namespace lve
{
    void first_app::Run()
    {
        while(!window.shouldClose())
            glfwPollEvents();
    }
}