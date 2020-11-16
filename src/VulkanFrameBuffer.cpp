#include "VulkanFrameBuffer.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
	VulkanFrameBuffer::VulkanFrameBuffer(
        VulkanRenderPass* vulkanRenderPass, VulkanLogicalDevice* vulkanLogicalDevice,
        VulkanSwapChain* vulkanSwapChain, VulkanImageView* vulkanImageView
    )
        :m_VulkanRenderPass(vulkanRenderPass), m_VulkanLogicalDevice(vulkanLogicalDevice),
        m_VulkanSwapChain(vulkanSwapChain), m_VulkanImageView(vulkanImageView)
	{

	}

	VulkanFrameBuffer::~VulkanFrameBuffer()
	{

	}

    void VulkanFrameBuffer::CreateFramebuffers()
    {
        m_SwapChainFramebuffers.resize(m_VulkanSwapChain->GetSwapChainImageViews().size());

        for (size_t i = 0; i < m_VulkanSwapChain->GetSwapChainImageViews().size(); i++)
        {
            std::array<VkImageView, 2> attachments =
            {
                m_VulkanSwapChain->GetSwapChainImageViews()[i],
                m_VulkanImageView->GetDepthImageView()
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = m_VulkanRenderPass->GetRenderPass();
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = m_VulkanSwapChain->GetSwapChainExtent().width;
            framebufferInfo.height = m_VulkanSwapChain->GetSwapChainExtent().height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(m_VulkanLogicalDevice->GetDevice(), &framebufferInfo, nullptr, &m_SwapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Can't create framebuffer");
            }
        }
    }
}