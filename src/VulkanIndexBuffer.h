#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanImageView.h"
#include "VulkanCommandPool.h"

#include "vulkan/vulkan.h"


namespace Vulk {

	const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4
	};

	class VulkanIndexBuffer
	{
	public:
		VulkanIndexBuffer(VulkanLogicalDevice* vulkanLogicalDevice, VulkanImageView* vulkanImageView, VulkanCommandPool* vulkanCommandPool);
		~VulkanIndexBuffer();
		void CreateIndexBuffer();
		inline VkBuffer GetIndexBuffer() { return m_IndexBuffer; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkBuffer m_VertexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
		VulkanImageView* m_VulkanImageView;
		VulkanCommandPool* m_VulkanCommandPool;
		VkBuffer m_IndexBuffer;
		VkDeviceMemory m_IndexBufferMemory;
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