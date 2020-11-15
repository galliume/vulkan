#pragma once

#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"

#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanImageView
	{
	public:
		VulkanImageView(VulkanSwapChain* vulkanSwapChain, VulkanPhysicalDevice* vulkanPhysicalDevice, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanImageView();
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	private:
		VulkanSwapChain* m_VulkanSwapChain;
		VulkanPhysicalDevice* m_VulkanPhysicalDevice;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkImageView m_DepthImageView;
		VkImage m_DepthImage;
		VkDeviceMemory m_DepthImageMemory;
	private:
		void CreateDepthResources();
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}