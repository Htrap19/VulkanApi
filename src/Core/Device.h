//
// Created by aeternum on 9/5/21.
//

#ifndef VULKANAPI_DEVICE_H
#define VULKANAPI_DEVICE_H

#include <vulkan/vulkan.h>
#include <optional>

#include "Instance.h"
#include "Surface.h"

namespace VulkanApi
{
    class PhysicalDevice
    {
    public:
        struct QueueFamilyDetails
        {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;
            inline bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
        };

    public:
        PhysicalDevice(const Ref<Instance>& instance, const Ref<Surface>& surface);
        void PickSuitableDevice();

        QueueFamilyDetails GetQueueFamilyProperties(VkPhysicalDevice device);
        QueueFamilyDetails GetQueueFamilyProperties();

        inline VkPhysicalDevice& GetVkPhysicalDevice() { return m_PhysicalDevice; }

        inline Ref<Instance> GetInstance() { return m_Instance; }

    private:
        bool IsDeviceSuitable(VkPhysicalDevice device);

    private:
        Ref<Instance> m_Instance;
        Ref<Surface> m_Surface;

        VkPhysicalDevice m_PhysicalDevice;
        uint32_t m_DeviceCount;
        std::vector<VkPhysicalDevice> m_Devices;
    };

    class Queue; // Predefined to avoid recursive include error

    class Device
    {
    public:
        Device(const std::initializer_list<const char*>& deviceExtensions, const Ref<PhysicalDevice>& device);
        virtual ~Device();

        inline Ref<PhysicalDevice> GetPhysicalDevice() { return m_PhysicalDevice; }

        inline VkDevice& GetVkDevice() { return m_Device; }

        inline void WaitIdle() const { vkDeviceWaitIdle(m_Device); }

    private:
        Ref<PhysicalDevice> m_PhysicalDevice;

        VkDevice m_Device;
        std::vector<const char*> m_DeviceExtensions;
    };
}


#endif //VULKANAPI_DEVICE_H
