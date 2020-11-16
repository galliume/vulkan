#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "VulkanTextureImage.h"
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
			VulkanTextureImage* vulkanTextureImage,
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
		VulkanTextureImage* m_VulkanTextureImage;
		VulkanTextureSampler* m_VulkanTextureSampler;
		VulkanDescriptorPool* m_VulkanDescriptorPool;
		VulkanUniformBuffer* m_VulkanUniformBuffer;
	};
}