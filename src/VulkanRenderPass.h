#pragma once
#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanRenderPass
	{
	public:
		VulkanRenderPass(
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain,
			std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice
		);
		~VulkanRenderPass();
		void CreateRenderPass();
		inline std::shared_ptr<VulkanLogicalDevice> GetVulkanLogicalDevice() { return m_VulkanLogicalDevice; };
		inline VkRenderPass* GetRenderPass() { return m_RenderPass; };
	private:
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = nullptr;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkRenderPass* m_RenderPass = VK_NULL_HANDLE;
	private:
		//@todo delete duplicate in VulkanImageView
		VkFormat FindDepthFormat();
		//@todo delete duplicate in VulkanImageView
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	};
}