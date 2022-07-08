#include "Lve_window.hpp"

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
}