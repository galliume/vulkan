#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanImageView
	{
	public:
		VulkanImageView(
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain, std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice
		);
		~VulkanImageView();
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		VkImageView GetImageView() { return m_ImageView; };
		inline VkImageView GetDepthImageView() { return m_DepthImageView; };
		inline VkImage GetDepthImage() { return m_DepthImage; };
		inline VkDeviceMemory GetDepthImageMemory() { return m_DepthImageMemory; };
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	private:
		std::shared_ptr<VulkanSwapChain>m_VulkanSwapChain = nullptr;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkImageView m_DepthImageView = VK_NULL_HANDLE;
		VkImage m_DepthImage = VK_NULL_HANDLE;
		VkDeviceMemory m_DepthImageMemory = VK_NULL_HANDLE;
		VkImageView m_ImageView = VK_NULL_HANDLE;
	private:
		void CreateDepthResources();
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanRenderPass
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}