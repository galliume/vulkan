#include "vulkan/vulkan.h"

#include "Log.h"

#include "GLFW/glfw3.h"
#include "VulkanService.h"

int main(int argc, char** argv)
{
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	Vulk::Log::Init();
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	Vulk::VulkanService vulkanService = Vulk::VulkanService(window);
	vulkanService.Init();

	glfwSetWindowUserPointer(window, &vulkanService.GetContext());

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//vulkanImpl.drawFrame();
	}

	//vulkanImpl.cleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();
}
