#include "VulkanCommandBuffer.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
    VulkanCommandBuffer::VulkanCommandBuffer(
        VulkanDescriptorSet* vulkanDescriptorSet, VulkanRenderPass* vulkanRenderPass,
        VulkanFrameBuffer* vulkanFrameBuffer, VulkanCommandPool* vulkanCommandPool,
        VulkanGraphicPipeLine* vulkanGraphicPipeLine, VulkanVertexBuffer* vulkanVertexBuffer,
        VulkanIndexBuffer* vulkanIndexBuffer
    )
        : m_VulkanDescriptorSet(vulkanDescriptorSet), m_VulkanRenderPass(vulkanRenderPass), 
        m_VulkanFrameBuffer(vulkanFrameBuffer), m_VulkanCommandPool(vulkanCommandPool),
        m_VulkanGraphicPipeLine(vulkanGraphicPipeLine), m_VulkanVertexBuffer(vulkanVertexBuffer),
        m_VulkanIndexBuffer(vulkanIndexBuffer)
    {

    }

    VulkanCommandBuffer::~VulkanCommandBuffer()
    {

    }

    void VulkanCommandBuffer::CreateCommandBuffers()
    {
        m_CommandBuffers.resize(m_VulkanFrameBuffer->GetSwapChainFramebuffers().size());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = m_VulkanCommandPool->GetCommandPool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

        if (vkAllocateCommandBuffers(m_VulkanRenderPass->GetVulkanLogicalDevice()->GetDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Can't allocate command buffer");
        }

        for (size_t i = 0; i < m_CommandBuffers.size(); i++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optionnel
            beginInfo.pInheritanceInfo = nullptr; // Optionel

            if (vkBeginCommandBuffer(m_CommandBuffers[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("Can't begin command buffer");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = m_VulkanRenderPass->GetRenderPass();
            renderPassInfo.framebuffer = m_VulkanFrameBuffer->GetSwapChainFramebuffers()[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = m_VulkanDescriptorSet->GetVulkanSwapChain()->GetSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(m_CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(m_CommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_VulkanGraphicPipeLine->GetGraphicsPipeline());

            VkBuffer vertexBuffers[] = { m_VulkanVertexBuffer->GetVertexBuffer() };
            VkDeviceSize offsets[] = { 0 };

            vkCmdBindVertexBuffers(m_CommandBuffers[i], 0, 1, vertexBuffers, offsets);
            vkCmdBindIndexBuffer(m_CommandBuffers[i], m_VulkanIndexBuffer->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);

            vkCmdBindDescriptorSets(
                m_CommandBuffers[i], 
                VK_PIPELINE_BIND_POINT_GRAPHICS, 
                m_VulkanGraphicPipeLine->GetPipelineLayout(), 
                0, 
                1, 
                &m_VulkanDescriptorSet->GetDescriptorSets()[i], 
                0, 
                nullptr
            );

            vkCmdDrawIndexed(m_CommandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
            vkCmdEndRenderPass(m_CommandBuffers[i]);

            if (vkEndCommandBuffer(m_CommandBuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("Can't end command buffer");
            }
        }
    }
}