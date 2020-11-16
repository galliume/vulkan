#pragma once

#include "VulkanRenderPass.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanDescriptorSetLayout.h"
#include "VulkanVertexBuffer.h"

#include "vulkan/vulkan.h"
#include "glm/glm.hpp"

#include <array>

namespace Vulk {

	class VulkanGraphicPipeLine {
	public:
		VulkanGraphicPipeLine(
			VulkanRenderPass* vulkanRenderPass,
			VulkanLogicalDevice* vulkanLogicalDevice,
			VulkanSwapChain* vulkanSwapChain,
			VulkanDescriptorSetLayout* vulkanDescriptorSetLayout
		);
		~VulkanGraphicPipeLine();
		inline VkPipeline GetGraphicsPipeline() { return m_GraphicsPipeline; };
		inline VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; };
	private:
		VulkanRenderPass* m_VulkanRenderPass;
		VulkanLogicalDevice* m_VulkanLogicalDevice;
		VkPipeline m_GraphicsPipeline;
		VkPipelineLayout m_PipelineLayout;
		VulkanSwapChain* m_VulkanSwapChain;
		VulkanDescriptorSetLayout* m_VulkanDescriptorSetLayout;
	private:
		void CreateGraphicsPipeline();
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
	};
}