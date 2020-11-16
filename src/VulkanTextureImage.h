#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanImageView.h"
#include "vulkan/vulkan.h"

#include <vector>

namespace Vulk {
	class VulkanTextureImage
	{
	public:
		VulkanTextureImage(VulkanLogicalDevice* vulkanLogicalDevice, VulkanCommandPool* vulkanCommandPool, VulkanImageView* vulkanImageView);
		~VulkanTextureImage();
		void CreateTextureImage();
		inline VkImage GetTextureImage() { return m_TextureImage; };
		VkImageView CreateTextureImageView();
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VulkanCommandPool* m_VulkanCommandPool;
		VkImage m_TextureImage;
		VkDeviceMemory m_TextureImageMemory;
		VulkanImageView* m_VulkanImageView;
		VkImageView m_TextureImageView;
	private:
		//@todo duplicate in VulkanVertexBuffer
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		//@todo duplicate in VulkanVertexBuffer
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		//@todo duplicate in VulkanVertexBuffer
		VkCommandBuffer BeginSingleTimeCommands();
		//@todo duplicate in VulkanVertexBuffer
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	};
}