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
		VulkanDescriptorSet* m_VulkanDescriptorSet = nullptr;
		VulkanRenderPass* m_VulkanRenderPass = nullptr;
		VulkanFrameBuffer* m_VulkanFrameBuffer = nullptr;
		VulkanCommandPool* m_VulkanCommandPool = nullptr;
		VulkanGraphicPipeLine* m_VulkanGraphicPipeLine = nullptr;
		VulkanVertexBuffer* m_VulkanVertexBuffer = nullptr;
		VulkanIndexBuffer* m_VulkanIndexBuffer = nullptr;
		std::vector<VkCommandBuffer> m_CommandBuffers = { };
	};
}