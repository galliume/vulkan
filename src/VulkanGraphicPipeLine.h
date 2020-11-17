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
		VulkanGraphicPipeLine(
			std::shared_ptr<VulkanRenderPass> vulkanRenderPass,
			std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
			std::shared_ptr<VulkanSwapChain> vulkanSwapChain,
			std::shared_ptr<VulkanDescriptorSetLayout> vulkanDescriptorSetLayout
		);
		~VulkanGraphicPipeLine();
		inline VkPipeline GetGraphicsPipeline() { return m_GraphicsPipeline; };
		inline VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; };
	private:
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice = nullptr;
		std::shared_ptr<VulkanRenderPass> m_VulkanRenderPass = VK_NULL_HANDLE;
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain = nullptr;
		std::shared_ptr<VulkanDescriptorSetLayout> m_VulkanDescriptorSetLayout = nullptr;
		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;
		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;
	private:
		void CreateGraphicsPipeline();
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
	};
}