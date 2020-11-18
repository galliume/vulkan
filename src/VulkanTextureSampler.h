#pragma once

#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"
#include "iostream"

namespace Vulk {
	class VulkanTextureSampler 
	{
	public:
		VulkanTextureSampler(std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice);
		~VulkanTextureSampler();
		void CreateTextureSampler();
		inline VkSampler* GetTextureSampler() { return m_TextureSampler; };
	private:
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkSampler* m_TextureSampler = VK_NULL_HANDLE;
	};
}
