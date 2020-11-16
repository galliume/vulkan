#pragma once

#include "VulkanRenderPass.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanDescriptorSetLayout.h"
#include "VulkanVertexBuffer.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "iostream"
#include <fstream>
#include <array>

namespace Vulk {

	class VulkanGraphicPipeLine {
	public:
		VulkanGraphicPipeLine();
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
		VulkanLogicalDevice* m_VulkanLogicalDevice = nullptr;
		VulkanRenderPass* m_VulkanRenderPass = VK_NULL_HANDLE;
		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;
		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;
		VulkanSwapChain* m_VulkanSwapChain = VK_NULL_HANDLE;
		VulkanDescriptorSetLayout* m_VulkanDescriptorSetLayout = VK_NULL_HANDLE;
	private:
		void CreateGraphicsPipeline();
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
	};
}