#pragma once

#include "VulkanPhysicalDevice.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanLogicalDevice {
	public:
		VulkanLogicalDevice(VulkanPhysicalDevice* vulkanPhysicalDevice);
		~VulkanLogicalDevice();
		void CreateLogicalDevice();
		inline VkDevice GetDevice() { return m_LogicalDevice; };
	private:
		VulkanPhysicalDevice* m_VulkanPhysicalDevice;
		VkDevice m_LogicalDevice = VK_NULL_HANDLE;
		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_PresentQueue = VK_NULL_HANDLE;
	private:
	};
}