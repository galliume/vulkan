#pragma once

#include "VulkanRenderPass.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanImageView.h"
#include "vulkan/vulkan.h"
#include <vector>

namespace Vulk {
	class VulkanFrameBuffer
	{
	public:
		VulkanFrameBuffer(VulkanRenderPass* vulkanRenderPass, VulkanLogicalDevice* vulkanLogicalDevice, VulkanSwapChain* vulkanSwapChain, VulkanImageView* vulkanImageView);
		~VulkanFrameBuffer();
		void CreateFramebuffers();
		inline std::vector<VkFramebuffer> GetSwapChainFramebuffers() { return m_SwapChainFramebuffers; };
	private:
		VulkanRenderPass* m_VulkanRenderPass;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VulkanImageView* m_VulkanImageView;
		VulkanSwapChain* m_VulkanSwapChain;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;
	};
}