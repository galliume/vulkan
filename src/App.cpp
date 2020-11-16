#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include "Log.h"

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

int main(int argc, char** argv)
{
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	
	#define EnableValidationLayers true;

	Vulk::Log::Init();
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	
	Vulk::VulkanContext vulkanContext = Vulk::VulkanContext(window);
	Vulk::VulkanPhysicalDevice vulkanPhysicalDevice = Vulk::VulkanPhysicalDevice(&vulkanContext);
	Vulk::VulkanLogicalDevice vulkanLogicalDevice = Vulk::VulkanLogicalDevice(&vulkanPhysicalDevice);
	Vulk::VulkanSwapChain vulkanSwapChain = Vulk::VulkanSwapChain(&vulkanContext, &vulkanLogicalDevice);
	Vulk::VulkanImageView vulkanImageView = Vulk::VulkanImageView(&vulkanSwapChain, &vulkanLogicalDevice);
	Vulk::VulkanRenderPass vulkanRenderPass = Vulk::VulkanRenderPass(&vulkanSwapChain, &vulkanLogicalDevice);
	Vulk::VulkanDescriptorSetLayout vulkanDescriptorSetLayout = Vulk::VulkanDescriptorSetLayout(&vulkanLogicalDevice);
	Vulk::VulkanGraphicPipeLine vulkanGraphicPipeLine = Vulk::VulkanGraphicPipeLine(
		&vulkanRenderPass, &vulkanLogicalDevice, &vulkanSwapChain, &vulkanDescriptorSetLayout
	);
	Vulk::VulkanFrameBuffer vulkanFrameBuffer = Vulk::VulkanFrameBuffer(&vulkanRenderPass, &vulkanLogicalDevice, &vulkanSwapChain, &vulkanImageView);
	Vulk::VulkanCommandPool vulkanCommandPool = Vulk::VulkanCommandPool(&vulkanLogicalDevice);
	Vulk::VulkanTextureImage vulkanTextureImage = Vulk::VulkanTextureImage(&vulkanLogicalDevice, &vulkanCommandPool, &vulkanImageView);
	Vulk::VulkanTextureSampler vulkanTextureSampler = Vulk::VulkanTextureSampler(&vulkanLogicalDevice);
	Vulk::VulkanVertexBuffer vulkanVertexBuffer = Vulk::VulkanVertexBuffer(&vulkanLogicalDevice, &vulkanImageView, &vulkanCommandPool);
	Vulk::VulkanIndexBuffer vulkanIndexBuffer = Vulk::VulkanIndexBuffer(&vulkanLogicalDevice, &vulkanImageView, &vulkanCommandPool);
	Vulk::VulkanUniformBuffer vulkanUniformBuffer = Vulk::VulkanUniformBuffer(&vulkanSwapChain, &vulkanLogicalDevice, &vulkanImageView);
	Vulk::VulkanDescriptorPool vulkanDescriptorPool = Vulk::VulkanDescriptorPool(&vulkanSwapChain, &vulkanLogicalDevice);
	Vulk::VulkanDescriptorSet vulkanDescriptorSet = Vulk::VulkanDescriptorSet(
		&vulkanSwapChain, &vulkanLogicalDevice, &vulkanTextureImage, &vulkanTextureSampler, &vulkanDescriptorPool, &vulkanUniformBuffer
	);
	Vulk::VulkanCommandBuffer vulkanCommandBuffer = Vulk::VulkanCommandBuffer(
		&vulkanDescriptorSet, &vulkanRenderPass, &vulkanFrameBuffer, &vulkanCommandPool, &vulkanGraphicPipeLine, &vulkanVertexBuffer, &vulkanIndexBuffer
	);

	glfwSetWindowUserPointer(window, &vulkanContext);
	
	//glfwSetFramebufferSizeCallback(window, vulkanImpl.framebufferResizeCallback);
	//vulkanImpl.init(window);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//vulkanImpl.drawFrame();
	}

	//vulkanImpl.cleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();
}
