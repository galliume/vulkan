#include "VulkanDescriptorPool.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <set>

namespace Vulk {
	VulkanDescriptorPool::VulkanDescriptorPool(VulkanSwapChain* vulkanSwapChain, VulkanLogicalDevice* vulkanLogicalDevice)
        : m_VulkanSwapChain(vulkanSwapChain), m_VulkanLogicalDevice(vulkanLogicalDevice)
	{

	}

    VulkanDescriptorPool::~VulkanDescriptorPool()
    {

    }

    void VulkanDescriptorPool::CreateDescriptorPool()
    {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(m_VulkanSwapChain->GetSwapChainImage().size());
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(m_VulkanSwapChain->GetSwapChainImage().size());

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(m_VulkanSwapChain->GetSwapChainImage().size());

        if (vkCreateDescriptorPool(m_VulkanLogicalDevice->GetDevice(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create descriptor pool");
        }
    }

}