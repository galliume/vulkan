#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"

#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanImageView
	{
	public:
		VulkanImageView(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanImageView();
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		VkImageView CreateTextureImageView();
		VkImageView GetImageView() { return m_ImageView; };
		VkImageView GetTextureImageView() { return m_TextureImageView; };
		inline VkImageView GetDepthImageView() { return m_DepthImageView; };
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	private:
		VulkanSwapChain* m_VulkanSwapChain;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkImageView m_DepthImageView;
		VkImage m_DepthImage;
		VkDeviceMemory m_DepthImageMemory;
		VkImageView m_TextureImageView;
		VkImageView m_ImageView;
	private:
		void CreateDepthResources();
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}