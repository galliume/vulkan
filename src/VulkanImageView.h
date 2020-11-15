#pragma once
#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanImageView
	{
	public:
		VulkanImageView(VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanImageView();
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
	};
}