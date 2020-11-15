#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "VulkanImageView.h"

#include "vulkan/vulkan.h"
#include "glm/glm.hpp"

namespace Vulk {

	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	class VulkanUniformBuffer
	{
	public:
		VulkanUniformBuffer(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice, VulkanImageView* vulkanImageView);
		~VulkanUniformBuffer();
		inline std::vector<VkBuffer> GetUniformBuffers() { return m_UniformBuffers; };
		inline uint32_t GetSizeOfUniformBufferObject() { return sizeof(UniformBufferObject); };
	private:
		VulkanSwapChain* m_VulkanSwapChain;
		std::vector<VkBuffer> m_UniformBuffers;
		std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VulkanImageView* m_VulkanImageView;
	private:
		void CreateUniformBuffers();
		//@todo duplicate in VulkanVertexBuffer
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	};
}