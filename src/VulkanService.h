#pragma once

#include "vulkan/vulkan.h"
#include "Log.h"

#include "GLFW/glfw3.h"

#include "VulkanContext.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanImageView.h"
#include "VulkanRenderPass.h"
#include "VulkanDescriptorSetLayout.h"
#include "VulkanGraphicPipeLine.h"
#include "VulkanFrameBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanTextureImage.h"
#include "VulkanTextureSampler.h"
#include "VulkanVertexBuffer.h"
#include "VulkanIndexBuffer.h"
#include "VulkanUniformBuffer.h"
#include "VulkanDescriptorPool.h"
#include "VulkanDescriptorSet.h"
#include "VulkanCommandBuffer.h"

#include <vector>
#include <chrono>

#define EnableValidationLayers true;
const int MAX_FRAMES_IN_FLIGHT = 2;

namespace Vulk 
{
	class VulkanService 
	{
	public:
		VulkanService(GLFWwindow* window);
		~VulkanService();
		void VulkanService::Init();
		VulkanContext GetContext() { return m_VulkanContext; };
		void CreateSyncObjects();
		void DrawFrame();
		void CleanUp();
		void CleanupSwapChain();
		void RecreateSwapChain();
		void UpdateUniformBuffer(uint32_t currentImage);
	private:
		GLFWwindow* m_Window;
		VulkanContext m_VulkanContext;
		VulkanPhysicalDevice m_VulkanPhysicalDevice;
		VulkanLogicalDevice m_VulkanLogicalDevice;
		VulkanSwapChain m_VulkanSwapChain;
		VulkanImageView m_VulkanImageView;
		VulkanRenderPass m_VulkanRenderPass;
		VulkanDescriptorSetLayout m_VulkanDescriptorSetLayout;
		VulkanGraphicPipeLine m_VulkanGraphicPipeLine;
		VulkanFrameBuffer m_VulkanFrameBuffer;
		VulkanCommandPool m_VulkanCommandPool;
		VulkanTextureImage m_VulkanTextureImage;
		VulkanTextureSampler m_VulkanTextureSampler;
		VulkanVertexBuffer m_VulkanVertexBuffer;
		VulkanIndexBuffer m_VulkanIndexBuffer;
		VulkanUniformBuffer m_VulkanUniformBuffer;
		VulkanDescriptorPool m_VulkanDescriptorPool;
		VulkanDescriptorSet m_VulkanDescriptorSet;
		VulkanCommandBuffer m_VulkanCommandBuffer;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		std::vector<VkFence> m_ImagesInFlight;
		std::vector<VkFence> m_InFlightFences;
		size_t m_CurrentFrame = 0;
		bool m_FramebufferResized = false;
		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_PresentQueue = VK_NULL_HANDLE;

		VkDebugUtilsMessengerEXT m_DebugUtilsCallback = VK_NULL_HANDLE;
	};
}