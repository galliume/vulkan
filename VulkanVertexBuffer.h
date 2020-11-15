#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanImageView.h"
#include "VulkanCommandPool.h"

#include "vulkan/vulkan.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>

namespace Vulk {

	class VulkanVertexBuffer
	{
	public:
		VulkanVertexBuffer(VulkanLogicalDevice* vulkanLogicalDevice, VulkanImageView* vulkanImageView, VulkanCommandPool* vulkanCommandPool);
		~VulkanVertexBuffer();
		void CreateVertexBuffer();
		inline VkBuffer GetVertexBuffer() { return m_VertexBuffer; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkBuffer m_VertexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
		VulkanImageView* m_VulkanImageView;
		VulkanCommandPool* m_VulkanCommandPool;
	private:
		//@todo duplicate in VulkanTextureImage
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		//@todo duplicate in VulkanTextureImage
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		//@todo duplicate in VulkanTextureImage
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		//@todo duplicate in VulkanTextureImage
		VkCommandBuffer BeginSingleTimeCommands();
		//@todo duplicate in VulkanTextureImage
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	};
}