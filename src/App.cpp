#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "vulkan/vulkan.h"
#include "Log.h"
#include "VulkanContext.h"


int main(int argc, char** argv)
{
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	
	Vulk::Log::Init();
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	
	Vulk::VulkanContext vulkanContext = Vulk::VulkanContext(window);
	vulkanContext.Create();

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
