#pragma once

#include "VulkanDescriptorSet.h"
#include "VulkanRenderPass.h"
#include "VulkanFrameBuffer.h"
#include "VulkanCommandPool.h"
#include "vulkan/vulkan.h"
#include "VulkanGraphicPipeLine.h"
#include "VulkanVertexBuffer.h"
#include "VulkanIndexBuffer.h"

namespace Vulk {
	class VulkanCommandBuffer
	{
	public:
		VulkanCommandBuffer(
			VulkanDescriptorSet* vulkanDescriptorSet, 
			VulkanRenderPass* vulkanRenderPass, 
			VulkanFrameBuffer* vulkanFrameBuffer,
			VulkanCommandPool* vulkanCommandPool,
			VulkanGraphicPipeLine* vulkanGraphicPipeLine,
			VulkanVertexBuffer* vulkanVertexBuffer,
			VulkanIndexBuffer* vulkanIndexBuffer
		);
		~VulkanCommandBuffer();
		void CreateCommandBuffers();
	private:
		std::vector<VkCommandBuffer> m_CommandBuffers;
		VulkanDescriptorSet* m_VulkanDescriptorSet;
		VulkanRenderPass* m_VulkanRenderPass;
		VulkanFrameBuffer* m_VulkanFrameBuffer;
		VulkanCommandPool* m_VulkanCommandPool;
		VulkanGraphicPipeLine* m_VulkanGraphicPipeLine;
		VulkanVertexBuffer* m_VulkanVertexBuffer;
		VulkanIndexBuffer* m_VulkanIndexBuffer;
	};
}