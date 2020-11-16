#pragma once

#include "VulkanLogicalDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanImageView.h"

#include "Log.h"
#include "vulkan/vulkan.h"
#include "stb_image.h"

#include <vector>

namespace Vulk {
	class VulkanTextureImage
	{
	public:
		VulkanTextureImage();
		VulkanTextureImage(VulkanLogicalDevice* vulkanLogicalDevice, VulkanCommandPool* vulkanCommandPool, VulkanImageView* vulkanImageView);
		~VulkanTextureImage();
		void CreateTextureImage();
		inline VkImage GetTextureImage() { return m_TextureImage; };
		VkImageView CreateTextureImageView();
		inline VkImageView GetTextureImageView() { return m_TextureImageView; };
		inline VkDeviceMemory GetTextureImageMemory() { return m_TextureImageMemory; };
	private:
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VulkanCommandPool* m_VulkanCommandPool = nullptr;
		VulkanImageView* m_VulkanImageView = nullptr;
		VkImage m_TextureImage = VK_NULL_HANDLE;
		VkDeviceMemory m_TextureImageMemory = VK_NULL_HANDLE;
		VkImageView m_TextureImageView = VK_NULL_HANDLE;
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