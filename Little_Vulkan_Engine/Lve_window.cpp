#include "Lve_window.hpp"
#include <stdexcept>
namespace lve
{
    Lvewindow::Lvewindow(int w, int h, std::string name) : width(w), height(h), WindowName(name)
    {
        initWindow();
    }

    void Lvewindow::initWindow()
    {
        glfwInit();
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, WindowName.c_str(), nullptr, nullptr);
    }

    Lvewindow::~Lvewindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Lvewindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
    {
        if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface:");
    }
}