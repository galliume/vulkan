#pragma once

#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"
#include "iostream"

namespace Vulk {
	class VulkanTextureSampler 
	{
	public:
		VulkanTextureSampler(VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanTextureSampler();
		void CreateTextureSampler();
		inline VkSampler GetTextureSampler() { return m_TextureSampler; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkSampler m_TextureSampler;
	};
}
