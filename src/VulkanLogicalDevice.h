#pragma once

#include "VulkanPhysicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <set>

namespace Vulk {
	class VulkanLogicalDevice {
	public:
		VulkanLogicalDevice();
		VulkanLogicalDevice(VulkanPhysicalDevice* vulkanPhysicalDevice);
		~VulkanLogicalDevice();
		void CreateLogicalDevice();
		inline VkDevice GetDevice() { return m_LogicalDevice; };
		inline QueueFamilyIndices GetQueueFamilyIndices() { return m_VulkanPhysicalDevice->GetQueueFamilyIndices(); };
		inline VkPhysicalDevice GetPhysicalDevice() { return m_VulkanPhysicalDevice->GetPhysicalDevice(); };
		inline VkQueue GetGraphicsQueue() { return m_GraphicsQueue; };
	private:
		VulkanPhysicalDevice* m_VulkanPhysicalDevice = nullptr;
		VkDevice m_LogicalDevice = VK_NULL_HANDLE;
		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_PresentQueue = VK_NULL_HANDLE;
	private:
	};
}