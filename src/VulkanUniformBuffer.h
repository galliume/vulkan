#pragma once

#include "VulkanSwapChain.h"
#include "VulkanLogicalDevice.h"
#include "VulkanImageView.h"

#include "vulkan/vulkan.h"
#include "iostream"
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
		VulkanUniformBuffer(
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain, 
			std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice, 
			std::shared_ptr<VulkanImageView> vulkanImageView
		);
		~VulkanUniformBuffer();
		inline std::vector<VkBuffer>* GetUniformBuffers() { return m_UniformBuffers; };
		inline uint32_t GetSizeOfUniformBufferObject() { return sizeof(UniformBufferObject); };
		inline std::vector<VkDeviceMemory>* GetUniformBuffersMemory() { return m_UniformBuffersMemory; };
	private:
		std::shared_ptr<VulkanLogicalDevice>m_VulkanLogicalDevice = nullptr;
		std::shared_ptr<VulkanImageView> m_VulkanImageView = nullptr;
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = VK_NULL_HANDLE;
		std::vector<VkBuffer>* m_UniformBuffers = { };
		std::vector<VkDeviceMemory>* m_UniformBuffersMemory = { };
	private:
		void CreateUniformBuffers();
		//@todo duplicate in VulkanVertexBuffer
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	};
}