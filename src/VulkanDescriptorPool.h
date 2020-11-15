#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"

namespace Vulk {

	class VulkanDescriptorPool
	{
	public:
		VulkanDescriptorPool(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanDescriptorPool();
		void CreateDescriptorPool();
		inline VkDescriptorPool GetDescriptorPool() { return m_DescriptorPool; };
	private:
		VkDescriptorPool m_DescriptorPool;
		VulkanSwapChain* m_VulkanSwapChain;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
	};
}