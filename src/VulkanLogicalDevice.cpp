#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"

namespace Vulk {
    VulkanLogicalDevice::VulkanLogicalDevice()
    {

    }
    VulkanLogicalDevice::VulkanLogicalDevice(VulkanPhysicalDevice* vulkanPhysicalDevice)
        : m_VulkanPhysicalDevice(vulkanPhysicalDevice)
	{

	}

	VulkanLogicalDevice::~VulkanLogicalDevice()
	{

	}

    void VulkanLogicalDevice::CreateLogicalDevice()
    {
        QueueFamilyIndices indices = m_VulkanPhysicalDevice->GetQueueFamilyIndices();

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
        createInfo.ppEnabledExtensionNames = m_VulkanPhysicalDevice->GetDeviceExtensions().data();
        createInfo.pEnabledFeatures = &deviceFeatures;

#ifdef EnableValidationLayers
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
#else
        createInfo.enabledLayerCount = 0;
#endif

        if (vkCreateDevice(m_VulkanPhysicalDevice->GetPhysicalDevice(), &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS)
        {
            throw std::runtime_error("Can't create logical device");
        }

        vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_LogicalDevice, indices.presentFamily.value(), 0, &m_PresentQueue);
    }
}