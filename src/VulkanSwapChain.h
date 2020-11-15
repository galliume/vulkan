#pragma once

#include "VulkanContext.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

#include "vulkan/vulkan.h"

namespace Vulk {

	class VulkanSwapChain {
	public:
		VulkanSwapChain(VulkanContext* vulkanContext, VulkanLogicalDevice* vulkanLogicalDevice, VkSurfaceKHR* surface);
		~VulkanSwapChain();
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		void CreateSwapChain();
		inline VkFormat GetSwapChainImageFormat() { return m_SwapChainImageFormat; };
		inline VkExtent2D GetSwapChainExtent() { return m_SwapChainExtent; };
		inline std::vector<VkImageView> GetSwapChainImageViews() { return m_SwapChainImageViews; };
		inline std::vector<VkImage> GetSwapChainImage() { return m_SwapChainImages; };
	private:
		VulkanContext* m_VulkanContext;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkSurfaceKHR* m_Surface;
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