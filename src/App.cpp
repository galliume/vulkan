#define GLFW_INCLUDE_VULKAN
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "Vulkan.h"

int main(int argc, char** argv)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	const uint32_t WIDTH = 2560;
	const uint32_t HEIGHT = 1440;
	Vulkan vulkanImpl = Vulkan();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, &vulkanImpl);
	glfwSetFramebufferSizeCallback(window, vulkanImpl.framebufferResizeCallback);

	vulkanImpl.init(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		vulkanImpl.drawFrame();
	}

	vulkanImpl.cleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();
}
