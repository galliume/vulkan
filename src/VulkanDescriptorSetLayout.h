#pragma once
#include "VulkanLogicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	class VulkanDescriptorSetLayout {
	public:
		VulkanDescriptorSetLayout(std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice);
		~VulkanDescriptorSetLayout();
		inline VkDescriptorSetLayout* GetDescriptorSetLayout() { return m_DescriptorSetLayout; };
	private:
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		VkDescriptorSetLayout* m_DescriptorSetLayout = VK_NULL_HANDLE;
	private:
		void CreateDescriptorSetLayout();
	};
}