#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {

	class VulkanDescriptorPool
	{
	public:
		VulkanDescriptorPool(std::shared_ptr<VulkanSwapChain> vulkanSwapChain, std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice);
		~VulkanDescriptorPool();
		void CreateDescriptorPool();
		inline VkDescriptorPool GetDescriptorPool() { return m_DescriptorPool; };
	private:
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = nullptr;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
	};
}