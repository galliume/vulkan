#pragma once

#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"

#include <vector>

namespace Vulk {
	class VulkanCommandPool
	{
	public:
		VulkanCommandPool(VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanCommandPool();
		void CreateCommandPool();
		VkCommandPool GetCommandPool() { return m_CommandPool; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkCommandPool m_CommandPool;
	};
}