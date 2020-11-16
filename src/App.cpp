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
