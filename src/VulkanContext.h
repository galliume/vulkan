#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "vulkan/vulkan.h"

#include <vector>

namespace Vulk {
	class VulkanContext {
	public:
		VulkanContext(GLFWwindow* windowHandle);
		~VulkanContext();

		void Create();
		void SwapBuffers();
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance m_VkInstance;
		VkSurfaceKHR m_Surface;
		bool m_EnableValidationLayers = true;
		const std::vector<const char*>m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
	private:
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};
}