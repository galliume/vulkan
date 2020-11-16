#pragma once

#include "VulkanRenderPass.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanImageView.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <vector>

namespace Vulk {
	class VulkanFrameBuffer
	{
	public:
		VulkanFrameBuffer();
		VulkanFrameBuffer(VulkanRenderPass* vulkanRenderPass, VulkanLogicalDevice* vulkanLogicalDevice, VulkanSwapChain* vulkanSwapChain, VulkanImageView* vulkanImageView);
		~VulkanFrameBuffer();
		void CreateFramebuffers();
		inline std::vector<VkFramebuffer> GetSwapChainFramebuffers() { return m_SwapChainFramebuffers; };
	private:
		VulkanRenderPass* m_VulkanRenderPass = nullptr;
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VulkanImageView* m_VulkanImageView = nullptr;
		VulkanSwapChain* m_VulkanSwapChain = nullptr;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers = { };
	};
}