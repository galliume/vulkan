#include "VulkanUniformBuffer.h"

#include "vulkan/vulkan.h"
#include "iostream"

namespace Vulk {
    VulkanUniformBuffer::VulkanUniformBuffer(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice, VulkanImageView* vulkanImageView) 
        : m_VulkanSwapChain(vulkanSwapChain), m_VulkanLogicalDevice(vulkanLogicalDevice), m_VulkanImageView(vulkanImageView)
    {
    }

    VulkanUniformBuffer::~VulkanUniformBuffer()
    {
    }

    void VulkanUniformBuffer::CreateUniformBuffers()
    {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        m_UniformBuffers.resize(m_VulkanSwapChain->GetSwapChainImage().size());
        m_UniformBuffersMemory.resize(m_VulkanSwapChain->GetSwapChainImage().size());

        for (size_t i = 0; i < m_VulkanSwapChain->GetSwapChainImage().size(); i++)
        {
            CreateBuffer(
                bufferSize, 
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
                m_UniformBuffers[i],
                m_UniformBuffersMemory[i]
           );
        }
    }

    void VulkanUniformBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(m_VulkanLogicalDevice->GetDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create buffer");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(m_VulkanLogicalDevice->GetDevice(), buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = m_VulkanImageView->FindMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(m_VulkanLogicalDevice->GetDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate buffer memory");
        }

        vkBindBufferMemory(m_VulkanLogicalDevice->GetDevice(), buffer, bufferMemory, 0);
    }
}