#include "VulkanCommandPool.h"

namespace Vulk {
    VulkanCommandPool::VulkanCommandPool()
    {

    }

	VulkanCommandPool::VulkanCommandPool(VulkanLogicalDevice* vulkanLogicalDevice)
        :m_VulkanLogicalDevice(vulkanLogicalDevice)
	{

	}

	VulkanCommandPool::~VulkanCommandPool()
	{

	}

    void VulkanCommandPool::CreateCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = m_VulkanLogicalDevice->GetQueueFamilyIndices();

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        poolInfo.flags = 0; // Optionel

        if (vkCreateCommandPool(m_VulkanLogicalDevice->GetDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Can't create command pool");
        }
    }
}