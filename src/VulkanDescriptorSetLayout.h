#pragma once
#include "VulkanLogicalDevice.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanDescriptorSetLayout {
	public:
		VulkanDescriptorSetLayout(VulkanLogicalDevice* vulkanLogicalDevice);
		~VulkanDescriptorSetLayout();
		inline VkDescriptorSetLayout* GetDescriptorSetLayout() { return m_DescriptorSetLayout; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkDescriptorSetLayout* m_DescriptorSetLayout;
	private:
		void CreateDescriptorSetLayout();
	};
}