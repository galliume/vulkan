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
		VulkanSwapChain* m_VulkanSwapChain = nullptr;
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VulkanTextureImage* m_VulkanTextureImage = nullptr;
		VulkanTextureSampler* m_VulkanTextureSampler = nullptr;
		VulkanDescriptorPool* m_VulkanDescriptorPool = nullptr;
		VulkanUniformBuffer* m_VulkanUniformBuffer = nullptr;
		std::vector<VkDescriptorSet> m_DescriptorSets = { };
		VkDescriptorSetLayout m_DescriptorSetLayout = VK_NULL_HANDLE;
	};
}