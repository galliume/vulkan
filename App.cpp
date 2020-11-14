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

	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

	Vulkan vulkanImpl = Vulkan();
	vulkanImpl.init(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		vulkanImpl.drawFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
