#include "VulkanImageView.h"

#include "Log.h"
#include "vulkan/vulkan.h"

namespace Vulk {
    VulkanImageView::VulkanImageView(VulkanLogicalDevice* vulkanLogicalDevice)
        : m_VulkanLogicalDevice(vulkanLogicalDevice)
	{

	}

    VulkanImageView::~VulkanImageView()
	{

	}

    VkImageView VulkanImageView::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
    {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(m_VulkanLogicalDevice->GetDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create texture image view!");
        }

        return imageView;
    }
}