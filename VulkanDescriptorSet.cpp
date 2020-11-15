#include "VulkanDescriptorSet.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"

#include "Log.h"
#include "vulkan/vulkan.h"

#include <set>

namespace Vulk {
    VulkanDescriptorSet::VulkanDescriptorSet(
        VulkanSwapChain* vulkanSwapChain, 
        VulkanLogicalDevice* vulkanLogicalDevice, 
        VulkanImageView* vulkanImageView,
        VulkanTextureSampler* vulkanTextureSampler,
        VulkanDescriptorPool* vulkanDescriptorPool,
        VulkanUniformBuffer* vulkanUniformBuffer
    )
        : m_VulkanSwapChain(vulkanSwapChain), m_VulkanLogicalDevice(vulkanLogicalDevice), 
        m_VulkanImageView(vulkanImageView), m_VulkanTextureSampler(vulkanTextureSampler),
        m_VulkanDescriptorPool(vulkanDescriptorPool), m_VulkanUniformBuffer(vulkanUniformBuffer)
    {

    }

    VulkanDescriptorSet::~VulkanDescriptorSet()
    {

    }

    void VulkanDescriptorSet::CreateDescriptorSets()
    {        
        std::vector<VkDescriptorSetLayout> layouts(m_VulkanSwapChain->GetSwapChainImage().size(), m_DescriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = m_VulkanDescriptorPool->GetDescriptorPool();
        allocInfo.descriptorSetCount = static_cast<uint32_t>(m_VulkanSwapChain->GetSwapChainImage().size());
        allocInfo.pSetLayouts = layouts.data();

        m_DescriptorSets.resize(m_VulkanSwapChain->GetSwapChainImage().size());
        if (vkAllocateDescriptorSets(m_VulkanLogicalDevice->GetDevice(), &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate descriptor sets");
        }

        for (size_t i = 0; i < m_VulkanSwapChain->GetSwapChainImage().size(); i++)
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = m_VulkanUniformBuffer->GetUniformBuffers()[i];
            bufferInfo.offset = 0;
            bufferInfo.range = m_VulkanUniformBuffer->GetSizeOfUniformBufferObject();

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = m_VulkanImageView->CreateTextureImageView();
            imageInfo.sampler = m_VulkanTextureSampler->GetTextureSampler();

            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = m_DescriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = m_DescriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(m_VulkanLogicalDevice->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
}