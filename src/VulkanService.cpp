#include "VulkanService.h"

namespace Vulk 
{
    //Move in VulkUtils ? 
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pCallback);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    //Move in VulkUtils ? 
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, callback, pAllocator);
        }
    }

	VulkanService::VulkanService(GLFWwindow* window) : m_Window(window)
	{
		VulkanContext m_VulkanContext = VulkanContext(m_Window);//Line( const Line &obj);  // copy constructor
		VulkanPhysicalDevice m_VulkanPhysicalDevice = VulkanPhysicalDevice(&m_VulkanContext);		
		m_VulkanLogicalDevice = VulkanLogicalDevice(&m_VulkanPhysicalDevice);
	}

	VulkanService::~VulkanService()
	{

	}
	
	void VulkanService::Init()
	{
		m_VulkanSwapChain = VulkanSwapChain(&m_VulkanContext, &m_VulkanLogicalDevice);
		m_VulkanImageView = VulkanImageView(&m_VulkanSwapChain, &m_VulkanLogicalDevice);
		m_VulkanRenderPass = VulkanRenderPass(&m_VulkanSwapChain, &m_VulkanLogicalDevice);
		m_VulkanDescriptorSetLayout = VulkanDescriptorSetLayout(&m_VulkanLogicalDevice);
		m_VulkanGraphicPipeLine = VulkanGraphicPipeLine(&m_VulkanRenderPass, &m_VulkanLogicalDevice, &m_VulkanSwapChain, &m_VulkanDescriptorSetLayout);
		m_VulkanFrameBuffer = VulkanFrameBuffer(&m_VulkanRenderPass, &m_VulkanLogicalDevice, &m_VulkanSwapChain, &m_VulkanImageView);
		m_VulkanCommandPool = VulkanCommandPool(&m_VulkanLogicalDevice);
		m_VulkanTextureImage = VulkanTextureImage(&m_VulkanLogicalDevice, &m_VulkanCommandPool, &m_VulkanImageView);
		m_VulkanTextureSampler = VulkanTextureSampler(&m_VulkanLogicalDevice);
		m_VulkanVertexBuffer = VulkanVertexBuffer(&m_VulkanLogicalDevice, &m_VulkanImageView, &m_VulkanCommandPool);
		m_VulkanIndexBuffer = VulkanIndexBuffer(&m_VulkanLogicalDevice, &m_VulkanImageView, &m_VulkanCommandPool);
		m_VulkanUniformBuffer = VulkanUniformBuffer(&m_VulkanSwapChain, &m_VulkanLogicalDevice, &m_VulkanImageView);
		m_VulkanDescriptorPool = VulkanDescriptorPool(&m_VulkanSwapChain, &m_VulkanLogicalDevice);
		m_VulkanDescriptorSet = VulkanDescriptorSet(
			&m_VulkanSwapChain, &m_VulkanLogicalDevice, &m_VulkanTextureImage, &m_VulkanTextureSampler, &m_VulkanDescriptorPool, &m_VulkanUniformBuffer
		);
		m_VulkanCommandBuffer = VulkanCommandBuffer(
			&m_VulkanDescriptorSet, &m_VulkanRenderPass, &m_VulkanFrameBuffer, &m_VulkanCommandPool, &m_VulkanGraphicPipeLine, &m_VulkanVertexBuffer, &m_VulkanIndexBuffer
		);
	}

    void VulkanService::CleanUp()
    {
        CleanupSwapChain();

        vkDestroySampler(m_VulkanLogicalDevice.GetDevice(), m_VulkanTextureSampler.GetTextureSampler(), nullptr);
        vkDestroyImageView(m_VulkanLogicalDevice.GetDevice(), m_VulkanTextureImage.GetTextureImageView(), nullptr);

        vkDestroyImage(m_VulkanLogicalDevice.GetDevice(), m_VulkanTextureImage.GetTextureImage(), nullptr);
        vkFreeMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanTextureImage.GetTextureImageMemory(), nullptr);

        vkDestroyDescriptorSetLayout(m_VulkanLogicalDevice.GetDevice(), *m_VulkanDescriptorSetLayout.GetDescriptorSetLayout(), nullptr);
        vkDestroyBuffer(m_VulkanLogicalDevice.GetDevice(), m_VulkanIndexBuffer.GetIndexBuffer(), nullptr);
        vkFreeMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanIndexBuffer.GetIndexBufferMemory(), nullptr);

        vkDestroyBuffer(m_VulkanLogicalDevice.GetDevice(), m_VulkanVertexBuffer.GetVertexBuffer(), nullptr);
        vkFreeMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanVertexBuffer.GetVertexBufferMemory(), nullptr);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(m_VulkanLogicalDevice.GetDevice(), m_RenderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(m_VulkanLogicalDevice.GetDevice(), m_ImageAvailableSemaphores[i], nullptr);
            vkDestroyFence(m_VulkanLogicalDevice.GetDevice(), m_InFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(m_VulkanLogicalDevice.GetDevice(), m_VulkanCommandPool.GetCommandPool(), nullptr);

        vkDestroyDevice(m_VulkanLogicalDevice.GetDevice(), nullptr);

#ifdef EnableValidationLayers
        DestroyDebugUtilsMessengerEXT(m_VulkanContext.GetInstance(), m_DebugUtilsCallback, nullptr);
#endif

        vkDestroySurfaceKHR(m_VulkanContext.GetInstance(), m_VulkanContext.GetSurface(), nullptr);
        vkDestroyInstance(m_VulkanContext.GetInstance(), nullptr);

        glfwDestroyWindow(m_VulkanContext.GetWindow());
        glfwTerminate();
    }

    void VulkanService::CleanupSwapChain()
    {
        vkDestroyImageView(m_VulkanLogicalDevice.GetDevice(), m_VulkanImageView.GetDepthImageView(), nullptr);
        vkDestroyImage(m_VulkanLogicalDevice.GetDevice(), m_VulkanImageView.GetDepthImage(), nullptr);
        vkFreeMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanImageView.GetDepthImageMemory(), nullptr);

        for (auto framebuffer : m_VulkanFrameBuffer.GetSwapChainFramebuffers())
        {
            vkDestroyFramebuffer(m_VulkanLogicalDevice.GetDevice(), framebuffer, nullptr);
        }

        vkFreeCommandBuffers(
            m_VulkanLogicalDevice.GetDevice(), 
            m_VulkanCommandPool.GetCommandPool(), 
            static_cast<uint32_t>(m_VulkanCommandBuffer.GetCommandBuffers().size()),
            m_VulkanCommandBuffer.GetCommandBuffers().data()
        );
        vkDestroyPipeline(m_VulkanLogicalDevice.GetDevice(), m_VulkanGraphicPipeLine.GetGraphicsPipeline(), nullptr);
        vkDestroyPipelineLayout(m_VulkanLogicalDevice.GetDevice(), m_VulkanGraphicPipeLine.GetPipelineLayout(), nullptr);
        vkDestroyRenderPass(m_VulkanLogicalDevice.GetDevice(), m_VulkanRenderPass.GetRenderPass(), nullptr);

        for (auto imageView : m_VulkanSwapChain.GetSwapChainImageViews())
        {
            vkDestroyImageView(m_VulkanLogicalDevice.GetDevice(), imageView, nullptr);
        }

        vkDestroySwapchainKHR(m_VulkanLogicalDevice.GetDevice(), m_VulkanSwapChain.GetSwapChain(), nullptr);

        for (size_t i = 0; i < m_VulkanSwapChain.GetSwapChainImage().size(); i++)
        {
            vkDestroyBuffer(m_VulkanLogicalDevice.GetDevice(), m_VulkanUniformBuffer.GetUniformBuffers()[i], nullptr);
            vkFreeMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanUniformBuffer.GetUniformBuffersMemory()[i], nullptr);
        }

        vkDestroyDescriptorPool(m_VulkanLogicalDevice.GetDevice(), m_VulkanDescriptorPool.GetDescriptorPool(), nullptr);
    }
    void VulkanService::RecreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(m_Window, &width, &height);

        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(m_Window, &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(m_VulkanLogicalDevice.GetDevice());

        CleanupSwapChain();
        Init();
    }

    void VulkanService::CreateSyncObjects()
    {
        m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        m_ImagesInFlight.resize(m_VulkanSwapChain.GetSwapChainImage().size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(m_VulkanLogicalDevice.GetDevice(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(m_VulkanLogicalDevice.GetDevice(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(m_VulkanLogicalDevice.GetDevice(), &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
    void VulkanService::DrawFrame()
    {
        vkWaitForFences(m_VulkanLogicalDevice.GetDevice(), 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(
            m_VulkanLogicalDevice.GetDevice(), 
            m_VulkanSwapChain.GetSwapChain(), 
            UINT64_MAX, 
            m_ImageAvailableSemaphores[m_CurrentFrame],
            VK_NULL_HANDLE, 
            &imageIndex
        );

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_FramebufferResized)
        {
            m_FramebufferResized = false;
            RecreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Can't present image to the swap chain");
        }

        if (m_ImagesInFlight[imageIndex] != VK_NULL_HANDLE)
        {
            vkWaitForFences(m_VulkanLogicalDevice.GetDevice(), 1, &m_ImagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        m_ImagesInFlight[imageIndex] = m_ImagesInFlight[m_CurrentFrame];

        UpdateUniformBuffer(imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_CurrentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_VulkanCommandBuffer.GetCommandBuffers()[imageIndex];

        VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_CurrentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(m_VulkanLogicalDevice.GetDevice(), 1, &m_InFlightFences[m_CurrentFrame]);

        if (vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { m_VulkanSwapChain.GetSwapChain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(m_PresentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
        {
            RecreateSwapChain();
        }
        else if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Can't present image");
        }

        m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void VulkanService::UpdateUniformBuffer(uint32_t currentImage)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.proj = glm::perspective(
            glm::radians(45.0f), 
            m_VulkanSwapChain.GetSwapChainExtent().width / (float)m_VulkanSwapChain.GetSwapChainExtent().height, 
            0.1f, 
            10.0f
        );

        ubo.proj[1][1] *= -1;

        void* data;
        vkMapMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanUniformBuffer.GetUniformBuffersMemory()[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(m_VulkanLogicalDevice.GetDevice(), m_VulkanUniformBuffer.GetUniformBuffersMemory()[currentImage]);
    }
}