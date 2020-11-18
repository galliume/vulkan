#pragma once

#include "Log.h"

#include "VulkanLogicalDevice.h"

#include <vector>

namespace Vulk {
	class VulkanCommandPool
	{
	public:
		VulkanCommandPool(std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice);
		~VulkanCommandPool();
		void CreateCommandPool();
		VkCommandPool* GetCommandPool() { return m_CommandPool; };
	private:
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkCommandPool* m_CommandPool = VK_NULL_HANDLE;
	};
}