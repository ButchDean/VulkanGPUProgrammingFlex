#include <stdio.h>
#include <vulkan/vulkan.h>
#include <instance.h>

static VkInstance Instance = VK_NULL_HANDLE;
static VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

void CreateInstance() {}

void GetPhysicalDevice() {
    VkPhysicalDevice devices[100];
    uint32_t count = 100;

    if(vkEnumeratePhysicalDevices(Instance, &count, devices) != VK_SUCCESS) {
        puts("Eniumerating physicaldevices failed.\n");
        return;
    }

    PhysicalDevice = devices[0];

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(PhysicalDevice, &deviceProperties);
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &deviceFeatures);
}