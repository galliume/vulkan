#pragma once

#include "VulkanPhysicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <set>

namespace Vulk {
	class VulkanLogicalDevice {
	public:
		VulkanLogicalDevice(std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice);
		~VulkanLogicalDevice();
		void CreateLogicalDevice();
		inline VkDevice* GetDevice() { return m_LogicalDevice; };
		inline QueueFamilyIndices* GetQueueFamilyIndices() { return m_VulkanPhysicalDevice->GetQueueFamilyIndices(); };
		inline VkPhysicalDevice* GetPhysicalDevice() { return m_VulkanPhysicalDevice->GetPhysicalDevice(); };
		inline VkQueue* GetGraphicsQueue() { return m_GraphicsQueue; };
	private:
		std::shared_ptr<VulkanPhysicalDevice> m_VulkanPhysicalDevice = nullptr;
		VkDevice* m_LogicalDevice = VK_NULL_HANDLE;
		VkQueue* m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue* m_PresentQueue = VK_NULL_HANDLE;
		const std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		const std::vector<const char*> m_DeviceExtensions2 = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	private:
	};
}