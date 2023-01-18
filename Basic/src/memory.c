#include <memory.h>

VkBuffer InputBuffer = VK_NULL_HANDLE;
VkBuffer OutputBuffer = VK_NULL_HANDLE;
VkDeviceMemory InputBufferMemory = VK_NULL_HANDLE;
VkDeviceMemory OutputBufferMemory = VK_NULL_HANDLE;

extern VkPhysicalDevice PhysicalDevice;
extern VkDevice LogicalDevice;
extern VkDescriptorSet DescriptorSet;

uint32_t FindMemoryIndexType(uint32_t allowedTypesMask, VkMemoryPropertyFlags flags) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &memProperties);

    uint32_t typeMask = 1;
    for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++, typeMask <<=1) {
        if((allowedTypesMask & typeMask) != 0) {
            if((memProperties.memoryTypes[i].propertyFlags & flags) == flags) {
                return i;
            }
        }
    }

    perror("Failed to find memory type index.\n");

    return 0;
}

VkBuffer CreateBufferAndMemory(uint32_t size, VkDeviceMemory* deviceMemory) {
    VkBuffer buffer;
    VkDeviceMemory memory;

    VkBufferCreateInfo bufferInfo;
    memset(&bufferInfo, 0, sizeof(bufferInfo));
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

    if(vkCreateBuffer(LogicalDevice, &bufferInfo, NULL, &buffer) != VK_SUCCESS) {
        perror("Failed to create buffer.\n");
        return VK_NULL_HANDLE;
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(LogicalDevice, buffer, &memoryRequirements);
}

void CreateBuffers(uint32_t inputSize, uint32_t outputSize) {
    InputBuffer = CreateBufferAndMemory(inputSize, &InputBufferMemory);
    OutputBuffer = CreateBufferAndMemory(outputSize, &OutputBufferMemory);

    VkDescriptorBufferInfo descriptorBuffers[2];
    descriptorBuffers[0].buffer = InputBuffer;
    descriptorBuffers[0].offset = 0;
    descriptorBuffers[0].range = inputSize;
    descriptorBuffers[1].buffer = OutputBuffer;
    descriptorBuffers[1].offset = 0;
    descriptorBuffers[1].range = outputSize;

    VkWriteDescriptorSet writeDescriptorSet;
    memset(&writeDescriptorSet, 0, sizeof(writeDescriptorSet));
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = DescriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.descriptorCount = 2;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    writeDescriptorSet.pBufferInfo = descriptorBuffers;

    vkUpdateDescriptorSets(LogicalDevice, 1, &writeDescriptorSet, 0, NULL);
}

void DestroyBuffers() {
    vkDestroyBuffer(LogicalDevice, InputBuffer, NULL);
    vkFreeMemory(LogicalDevice, InputBufferMemory, NULL);
    vkDestroyBuffer(LogicalDevice, OutputBuffer, NULL);
    vkFreeMemory(LogicalDevice, OutputBufferMemory, NULL);
}

void CopyToInputbuffer(void* data, uint32_t size) {
    void* address;

    if(vkMapMemory(LogicalDevice, InputBufferMemory, 0, size, 0, &address) != VK_SUCCESS) {
        perror("Failed to map input buffer memory.\n");
        return;
    }

    memcpy(address, data, size);

    vkUnmapMemory(LogicalDevice, InputBufferMemory);
}

void CopyFromOutputbuffer(void* data, uint32_t size) {
    void* address;

    if(vkMapMemory(LogicalDevice, OutputBufferMemory, 0, size, 0, &address) != VK_SUCCESS) {
        perror("Failed to map output buffer memory.\n");
        return;
    }

    memcpy(data, address, size);

    vkUnmapMemory(LogicalDevice, OutputBufferMemory);    
}