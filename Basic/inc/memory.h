#ifndef _MEMORY_
#define _MEMORY_

#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>

uint32_t FindMemoryIndexType(uint32_t allowedTypesMask, VkMemoryPropertyFlags flags);
VkBuffer CreateBufferAndMemory(uint32_t size, VkDeviceMemory* deviceMemory);
void CreateBuffers(uint32_t inputSize, uint32_t outputSize);
void DestroyBuffers();
void CopyToInputbuffer(void* data, uint32_t size);
void CopyFromOutputbuffer(void* data, uint32_t size);

#endif