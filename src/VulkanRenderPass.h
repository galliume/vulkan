#pragma once
#include "VulkanSwapChain.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanRenderPass
	{
	public:
		VulkanRenderPass(VulkanSwapChain* vulkanSwapChain, VulkanPhysicalDevice* vulkanPhysicalDevice, VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanRenderPass();
		void CreateRenderPass();
		inline VkRenderPass GetRenderPass() { m_RenderPass; };
	private:
		VkRenderPass m_RenderPass;
		VulkanPhysicalDevice* m_VulkanPhysicalDevice;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
	private:
		VulkanSwapChain* m_VulkanSwapChain;
		//@todo delete duplicate in VulkanImageView
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanImageView
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}