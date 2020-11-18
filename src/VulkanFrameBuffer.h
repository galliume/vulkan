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
		VulkanFrameBuffer(
			std::shared_ptr<VulkanRenderPass> vulkanRenderPass, std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain, std::shared_ptr<VulkanImageView> vulkanImageView
		);
		~VulkanFrameBuffer();
		void CreateFramebuffers();
		inline std::vector<VkFramebuffer>* GetSwapChainFramebuffers() { return m_SwapChainFramebuffers; };
	private:
		std::shared_ptr<VulkanRenderPass>m_VulkanRenderPass = nullptr;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		std::shared_ptr<VulkanImageView> m_VulkanImageView = nullptr;
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = nullptr;
		std::vector<VkFramebuffer>* m_SwapChainFramebuffers = { };
	};
}