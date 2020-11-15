#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "VulkanImageView.h"
#include "VulkanTextureSampler.h"
#include "VulkanDescriptorPool.h"
#include "VulkanUniformBuffer.h"

#include "vulkan/vulkan.h"
#include <vector>

namespace Vulk {

	class VulkanDescriptorSet
	{
	public:
		VulkanDescriptorSet(
			VulkanSwapChain* vulkanSwapChain,
			VulkanLogicalDevice* vulkanLogicalDevice,
			VulkanImageView* vulkanImageView,
			VulkanTextureSampler* vulkanTextureSampler,
			VulkanDescriptorPool* vulkanDescriptorPool,
			VulkanUniformBuffer* vulkanUniformBuffer
		);
		~VulkanDescriptorSet();
		void CreateDescriptorSets();
		inline std::vector<VkDescriptorSet> GetDescriptorSets() { return m_DescriptorSets; };
		inline VulkanSwapChain* GetVulkanSwapChain() { return m_VulkanSwapChain; };
	private:
		std::vector<VkDescriptorSet> m_DescriptorSets;
		VulkanSwapChain* m_VulkanSwapChain;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkDescriptorSetLayout m_DescriptorSetLayout;
		VulkanImageView* m_VulkanImageView;
		VulkanTextureSampler* m_VulkanTextureSampler;
		VulkanDescriptorPool* m_VulkanDescriptorPool;
		VulkanUniformBuffer* m_VulkanUniformBuffer;
	};
}