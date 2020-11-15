#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <optional>
#include <array>
#include <cstddef>
#include <vector>

class Vulkan
{
public:
	Vulkan();
	inline static Vulkan& Get() { return *s_Instance; }
	inline void setWindow(GLFWwindow* glfwWindow) { window = glfwWindow; };
	inline GLFWwindow* getWindow() { return window; };
	inline VkRenderPass getRenderPass() { return renderPass; };
	inline VkDevice getDevice() { return device; };
	inline uint32_t getQueueFamily() { return queueFamily; };
	inline VkQueue getQueue() { return graphicsQueue; };
	inline uint32_t getImageCount() { return imageCount; };
	inline uint32_t getMinImageCount() { return minImageCount; };
	std::vector<VkCommandBuffer> getCommandBuffers() { return commandBuffers; };
	inline VkDescriptorPool getDescriporPool() { return descriptorPool; };
	void init(GLFWwindow* glfWwindow);
	void cleanUp();
	void drawFrame();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	inline size_t getCurrentFrame() { return currentFrame; };
private:
	static Vulkan* s_Instance;
	uint32_t imageCount = 2;
	uint32_t minImageCount = 2;
	uint32_t queueFamily;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	const int MAX_FRAMES_IN_FLIGHT = 2;
	VkInstance instance = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT callback = VK_NULL_HANDLE;
	bool enableValidationLayers = true;
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;
	GLFWwindow* window = VK_NULL_HANDLE;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
	std::vector<VkImage> swapChainImages = { };
	VkFormat swapChainImageFormat = { };
	VkExtent2D swapChainExtent = { };
	std::vector<VkImageView> swapChainImageViews = { };
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;		
	std::vector<VkFence> imagesInFlight;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;
	bool framebufferResized = false;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkDescriptorSetLayout descriptorSetLayout;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
private:
	inline VkInstance getInstance() { return instance; };
	inline VkSurfaceKHR* getSurface() { return &surface; };
	inline VkPhysicalDevice getPhysicalDevice() { return physicalDevice; };
	void createTextureImage();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createTextureSampler();
	void createDepthResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
};