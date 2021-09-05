//
// Created by aeternum on 9/5/21.
//

#include "Surface.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <stdexcept>

namespace VulkanApi
{

    Surface::Surface()
        : m_Window(800, 600), m_Instance({ "VK_LAYER_KHRONOS_validation" })
    {
        if (glfwCreateWindowSurface(m_Instance.GetVkInstance(), m_Window.GetWindow(), nullptr, &m_Surface) != VK_SUCCESS)
            throw std::runtime_error("Failed to create surface!");
    }
}
