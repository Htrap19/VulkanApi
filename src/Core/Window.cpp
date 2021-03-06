//
// Created by aeternum on 9/5/21.
//

#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VulkanApi
{
    bool Window::s_Initialized = false;
    Window* Window::s_Instance = nullptr;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        auto userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        userWindow->OnWindowResized(width, height);
    }

    Window::Window(uint32_t width, uint32_t height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr)
    {
        if (!s_Initialized)
        {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            s_Initialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        if (s_Instance == nullptr)
            s_Instance = this;
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::Closed()
    {
        return glfwWindowShouldClose(m_Window);
    }
}