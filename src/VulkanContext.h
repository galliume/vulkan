#pragma once

#include "VulkanPhysicalDevice.h"

#include "vulkan/vulkan.h"

#include "GLFW//glfw3.h"
#include <vector>

namespace Vulk {
	class VulkanContext {
	public:
		VulkanContext(GLFWwindow* windowHandle);
		~VulkanContext();

		void Create();
		void SwapBuffers();
		inline GLFWwindow* GetWindow() { return m_WindowHandle; };
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance m_VkInstance;
		VkSurfaceKHR m_Surface;
		const std::vector<const char*>m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
	private:
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};
}