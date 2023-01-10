#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <device.h>

extern VkPhysicalDevice PhysicalDevice;

VkDevice LogicalDevice = VK_NULL_HANDLE;
VkQueue ComputingQueue = VK_NULL_HANDLE;
VkCommandPool ComputeCommandPool = VK_NULL_HANDLE;
VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;

uint32_t ComputeQueueFamilyIndex;

void CreateDeviceAndComputeQueue() {
    VkQueueFamilyProperties families[100];
    uint32_t count = 100;

    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &count, families);

    printf("Found %u queue families\n", count);

    ComputeQueueFamilyIndex = 0;

    while((ComputeQueueFamilyIndex < count) && (families[ComputeQueueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0) {
        ComputeQueueFamilyIndex++;
    }

    if(ComputeQueueFamilyIndex == count) {
        perror("Compute queue not found\n");
        return;
    }

    float prio = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo;
    memset(&queueCreateInfo, 0, sizeof(queueCreateInfo));
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = ComputeQueueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &prio;

    VkDeviceCreateInfo deviceCreateInfo;
    memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;

    if(vkCreateDevice(PhysicalDevice, &deviceCreateInfo, NULL, &LogicalDevice) != VK_SUCCESS) {
        perror("Failed to create logical device\n");
        return;
    }

    vkGetDeviceQueue(LogicalDevice, ComputeQueueFamilyIndex, 0, &ComputingQueue);
}

void CreatecommandPool() {
    VkCommandPoolCreateInfo poolCreateInfo;
    memset(&poolCreateInfo, 0, sizeof(poolCreateInfo));
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.queueFamilyIndex = ComputeQueueFamilyIndex;

    if(vkCreateCommandPool(LogicalDevice, &poolCreateInfo, NULL, &ComputeCommandPool) != VK_SUCCESS) {
        perror("Failed to create a command pool\n");
    }
}

void CreateDescriptorPool() {

}