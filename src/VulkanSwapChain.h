#pragma once

#include "VulkanContext.h"
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {

	class VulkanSwapChain {
	public:
		VulkanSwapChain(std::shared_ptr<VulkanContext> vulkanContext, std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice);
		~VulkanSwapChain();
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		void CreateSwapChain();
		inline VkFormat GetSwapChainImageFormat() { return m_SwapChainImageFormat; };
		inline VkExtent2D GetSwapChainExtent() { return m_SwapChainExtent; };
		inline std::vector<VkImageView> GetSwapChainImageViews() { return m_SwapChainImageViews; };
		inline std::vector<VkImage> GetSwapChainImage() { return m_SwapChainImages; };
		inline VkSwapchainKHR GetSwapChain() { return m_SwapChain; };
	private:
		std::shared_ptr<VulkanContext> m_VulkanContext = VK_NULL_HANDLE;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;
		std::vector<VkImage>m_SwapChainImages = { };
		VkFormat m_SwapChainImageFormat = { };
		VkExtent2D m_SwapChainExtent = { };
		std::vector<VkImageView> m_SwapChainImageViews = { };
	private:
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	};
}