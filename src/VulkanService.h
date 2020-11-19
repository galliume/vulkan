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
#include <memory>

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
		std::shared_ptr<VulkanContext> GetContext() { return m_VulkanContext; };
		void CreateSyncObjects();
		void DrawFrame();
		void CleanUp();
		void CleanupSwapChain();
		void RecreateSwapChain();
		void UpdateUniformBuffer(uint32_t currentImage);
	private:
		GLFWwindow* m_Window;
		std::shared_ptr<VulkanContext> m_VulkanContext;
		std::shared_ptr<VulkanPhysicalDevice> m_VulkanPhysicalDevice;
		std::shared_ptr<VulkanLogicalDevice> m_VulkanLogicalDevice;
		std::shared_ptr<VulkanSwapChain> m_VulkanSwapChain;
		std::shared_ptr<VulkanImageView> m_VulkanImageView;
		std::shared_ptr<VulkanRenderPass> m_VulkanRenderPass;
		std::shared_ptr<VulkanDescriptorSetLayout> m_VulkanDescriptorSetLayout;
		std::shared_ptr<VulkanGraphicPipeLine> m_VulkanGraphicPipeLine;
		std::shared_ptr<VulkanFrameBuffer> m_VulkanFrameBuffer;
		std::shared_ptr<VulkanCommandPool> m_VulkanCommandPool;
		std::shared_ptr<VulkanTextureImage> m_VulkanTextureImage;
		std::shared_ptr<VulkanTextureSampler> m_VulkanTextureSampler;
		std::shared_ptr<VulkanVertexBuffer> m_VulkanVertexBuffer;
		std::shared_ptr<VulkanIndexBuffer> m_VulkanIndexBuffer;
		std::shared_ptr<VulkanUniformBuffer> m_VulkanUniformBuffer;
		std::shared_ptr<VulkanDescriptorPool> m_VulkanDescriptorPool;
		std::shared_ptr<VulkanDescriptorSet> m_VulkanDescriptorSet;
		std::shared_ptr<VulkanCommandBuffer> m_VulkanCommandBuffer;

		std::vector<VkSemaphore>* m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>* m_RenderFinishedSemaphores;
		std::vector<VkFence>* m_ImagesInFlight;
		std::vector<VkFence>* m_InFlightFences;
		size_t* m_CurrentFrame = 0;
		bool* m_FramebufferResized = false;
		VkQueue* m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue* m_PresentQueue = VK_NULL_HANDLE;
	};
}