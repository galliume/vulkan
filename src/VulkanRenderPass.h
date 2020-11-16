#pragma once
#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanRenderPass
	{
	public:
		VulkanRenderPass(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanRenderPass();
		void CreateRenderPass();
		VulkanLogicalDevice* GetVulkanLogicalDevice() { return m_VulkanLogicalDevice; };
		inline VkRenderPass GetRenderPass() { return m_RenderPass; };
	private:
		VkRenderPass m_RenderPass = VK_NULL_HANDLE;
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VulkanSwapChain* m_VulkanSwapChain = nullptr;
	private:
		//@todo delete duplicate in VulkanImageView
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanImageView
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}