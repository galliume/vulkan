#pragma once
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanDescriptorSetLayout {
	public:
		VulkanDescriptorSetLayout();
		VulkanDescriptorSetLayout(VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanDescriptorSetLayout();
		inline VkDescriptorSetLayout* GetDescriptorSetLayout() { return m_DescriptorSetLayout; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VkDescriptorSetLayout* m_DescriptorSetLayout = VK_NULL_HANDLE;
	private:
		void CreateDescriptorSetLayout();
	};
}