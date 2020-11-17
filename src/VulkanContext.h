#pragma once

#include "Log.h"
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace Vulk {
	class VulkanContext {
	public:
		VulkanContext(GLFWwindow* windowHandle);
		~VulkanContext();

		void SwapBuffers();
		inline GLFWwindow* GetWindow() { return m_WindowHandle; };
		inline VkInstance GetInstance() { return m_VkInstance; };
		inline VkSurfaceKHR GetSurface() { return m_Surface; };
	private:
		GLFWwindow* m_WindowHandle = nullptr;
		VkInstance m_VkInstance = VK_NULL_HANDLE;
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		const std::vector<const char*>m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
	private:
		void Create();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};
}