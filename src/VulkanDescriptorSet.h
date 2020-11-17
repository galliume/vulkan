#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "VulkanTextureImage.h"
#include "VulkanTextureSampler.h"
#include "VulkanDescriptorPool.h"
#include "VulkanUniformBuffer.h"

#include "Log.h"
#include "vulkan/vulkan.h"
#include <vector>

namespace Vulk {

	class VulkanDescriptorSet
	{
	public:
		VulkanDescriptorSet(
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain,
			std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
			std::shared_ptr<VulkanTextureImage> vulkanTextureImage,
			std::shared_ptr<VulkanTextureSampler> vulkanTextureSampler,
			std::shared_ptr<VulkanDescriptorPool> vulkanDescriptorPool,
			std::shared_ptr<VulkanUniformBuffer> vulkanUniformBuffer
		);
		~VulkanDescriptorSet();
		void CreateDescriptorSets();
		inline std::vector<VkDescriptorSet> GetDescriptorSets() { return m_DescriptorSets; };
		inline std::shared_ptr<VulkanSwapChain> GetVulkanSwapChain() { return m_VulkanSwapChain; };
	private:
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = nullptr;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		std::shared_ptr<VulkanTextureImage> m_VulkanTextureImage = nullptr;
		std::shared_ptr<VulkanTextureSampler> m_VulkanTextureSampler = nullptr;
		std::shared_ptr<VulkanDescriptorPool> m_VulkanDescriptorPool = nullptr;
		std::shared_ptr<VulkanUniformBuffer> m_VulkanUniformBuffer = nullptr;
		std::vector<VkDescriptorSet> m_DescriptorSets = { };
		VkDescriptorSetLayout m_DescriptorSetLayout = VK_NULL_HANDLE;
	};
}