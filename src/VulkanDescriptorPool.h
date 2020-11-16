#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {

	class VulkanDescriptorPool
	{
	public:
		VulkanDescriptorPool();
		VulkanDescriptorPool(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanDescriptorPool();
		void CreateDescriptorPool();
		inline VkDescriptorPool GetDescriptorPool() { return m_DescriptorPool; };
	private:
		VulkanSwapChain* m_VulkanSwapChain = nullptr;
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
	};
}