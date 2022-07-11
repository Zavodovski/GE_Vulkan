#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
namespace lve
{
    class Lvewindow
    {
    public:
        Lvewindow(int w, int h, std::string name);
        ~Lvewindow();

        Lvewindow(const Lvewindow&) = delete;
        Lvewindow operator=(const Lvewindow&) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }

        VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
        

    private:
        void initWindow();

        GLFWwindow* window;
        const int width;
        const int height;
        const std::string WindowName;
        
    };
}