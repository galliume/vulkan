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
			std::shared_ptr<VulkanDescriptorSet> vulkanDescriptorSet, std::shared_ptr<VulkanRenderPass> vulkanRenderPass,
			std::shared_ptr<VulkanFrameBuffer> vulkanFrameBuffer, std::shared_ptr<VulkanCommandPool> vulkanCommandPool,
			std::shared_ptr<VulkanGraphicPipeLine> vulkanGraphicPipeLine, std::shared_ptr<VulkanVertexBuffer> vulkanVertexBuffer,
			std::shared_ptr<VulkanIndexBuffer> vulkanIndexBuffer
		);
		~VulkanCommandBuffer();
		void CreateCommandBuffers();
		inline std::vector<VkCommandBuffer> GetCommandBuffers() { return m_CommandBuffers; }
	private:
		std::shared_ptr<VulkanDescriptorSet> m_VulkanDescriptorSet = nullptr;
		std::shared_ptr<VulkanRenderPass> m_VulkanRenderPass = nullptr;
		std::shared_ptr<VulkanFrameBuffer> m_VulkanFrameBuffer = nullptr;
		std::shared_ptr<VulkanCommandPool> m_VulkanCommandPool = nullptr;
		std::shared_ptr<VulkanGraphicPipeLine> m_VulkanGraphicPipeLine = nullptr;
		std::shared_ptr<VulkanVertexBuffer> m_VulkanVertexBuffer = nullptr;
		std::shared_ptr<VulkanIndexBuffer> m_VulkanIndexBuffer = nullptr;
		std::vector<VkCommandBuffer> m_CommandBuffers = { };
	};
}