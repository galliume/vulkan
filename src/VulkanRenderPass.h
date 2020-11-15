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
		inline VkRenderPass GetRenderPass() { m_RenderPass; };
	private:
		VkRenderPass m_RenderPass;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
	private:
		VulkanSwapChain* m_VulkanSwapChain;
		//@todo delete duplicate in VulkanImageView
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanImageView
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}