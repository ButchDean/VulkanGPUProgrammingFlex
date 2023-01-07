#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <instance.h>

static VkInstance Instance = VK_NULL_HANDLE;
static VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

void CreateInstance() {
    const char* layers[] = { "VK_LAYER_KHRONOS_validation" };

    VkInstanceCreateInfo instanceCreateInfo;
    memset(&instanceCreateInfo, 0, sizeof(instanceCreateInfo));

    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.ppEnabledExtensionNames = layers;
    instanceCreateInfo.enabledLayerCount = 1;

    if(vkCreateInstance(&instanceCreateInfo, NULL, &Instance) != VK_SUCCESS) {
        perror("Create Instance failed.\n");
    }
}

void GetPhysicalDevice() {
    VkPhysicalDevice devices[100];
    uint32_t count = 100;

    if(vkEnumeratePhysicalDevices(Instance, &count, devices) != VK_SUCCESS) {
        perror("Enumerating physicaldevices failed.\n");
        return;
    }

    PhysicalDevice = devices[0];

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(PhysicalDevice, &deviceProperties);
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &deviceFeatures);
}