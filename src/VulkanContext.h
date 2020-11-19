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
		inline VkInstance* GetInstance() { return m_VkInstance; };
		inline VkSurfaceKHR* GetSurface() { return m_Surface; };
		inline VkDebugUtilsMessengerEXT* GetDebugUtilsCallback() { return m_DebugUtilsCallback; };
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
	private:
		GLFWwindow* m_WindowHandle = nullptr;
		VkInstance* m_VkInstance = nullptr;
		VkSurfaceKHR* m_Surface = VK_NULL_HANDLE;
		const std::vector<const char*>m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
	private:
		void Create();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		VkDebugUtilsMessengerEXT* m_DebugUtilsCallback = VK_NULL_HANDLE;
	};
}