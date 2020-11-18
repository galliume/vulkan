#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"

namespace Vulk {
    VulkanLogicalDevice::VulkanLogicalDevice(std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice)
        : m_VulkanPhysicalDevice(vulkanPhysicalDevice)
	{
        CreateLogicalDevice();
	}

	VulkanLogicalDevice::~VulkanLogicalDevice()
	{

	}

    void VulkanLogicalDevice::CreateLogicalDevice()
    {
        QueueFamilyIndices indices = *m_VulkanPhysicalDevice->GetQueueFamilyIndices();

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};//GPU features like is VR supported or not, not used for the moment by RebelleEngine
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(m_VulkanPhysicalDevice->GetDeviceExtensions().size());
        createInfo.ppEnabledExtensionNames = m_DeviceExtensions2.data();
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

        if (vkCreateDevice(*m_VulkanPhysicalDevice->GetPhysicalDevice(), &createInfo, nullptr, m_LogicalDevice) != VK_SUCCESS)
        {
            VULK_CRITICAL("Can't create logical device");
        }
        
        vkGetDeviceQueue(*m_LogicalDevice, indices.graphicsFamily.value(), 0, m_GraphicsQueue);
        vkGetDeviceQueue(*m_LogicalDevice, indices.presentFamily.value(), 0, m_PresentQueue);

        VULK_TRACE("Created logical device");
    }
}