#pragma once

#include "VulkanContext.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <assert.h>
#include <set>
#include <optional>
#include <vector>

namespace Vulk {

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); };
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice(std::shared_ptr<VulkanContext> vulkanContext);
		~VulkanPhysicalDevice();
		inline QueueFamilyIndices* GetQueueFamilyIndices() { return m_QueueFamilyIndices; };
		inline const std::vector<const char*> GetDeviceExtensions() { return m_DeviceExtensions; };
		inline VkPhysicalDevice* GetPhysicalDevice() { return m_PhysicalDevice; };
	private:
		QueueFamilyIndices* m_QueueFamilyIndices;
		std::shared_ptr<VulkanContext> m_VulkanContext;
		VkPhysicalDevice* m_PhysicalDevice = VK_NULL_HANDLE;
		const std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	private:
		void PickPhysicalDevice();
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices* FindQueueFamilies(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	};
}