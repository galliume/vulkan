#pragma once

#include "VulkanRenderPass.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanDescriptorSetLayout.h"

#include "vulkan/vulkan.h"
#include "glm/glm.hpp"

#include <array>

namespace Vulk {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}
	};

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