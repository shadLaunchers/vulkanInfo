// SPDX-FileCopyrightText: Copyright 2025 vulkanInfo Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "VulkanDeviceLib.h"
#include <volk.h>
#include <vector>
#include <iostream>

#include "VulkanDeviceLib.h"
#include <volk.h>
#include <vector>
#include <cstring>

static bool g_volkInitialized = false;

/**
 * Helper: Initialize volk once
 */
static bool InitVolk()
{
    if (!g_volkInitialized) {
        if (volkInitialize() != VK_SUCCESS) return false;
        g_volkInitialized = true;
    }
    return true;
}

extern "C" {

    int GetVulkanDeviceCount()
    {
        if (!InitVolk()) return -1;

        VkInstanceCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        VkInstance instance;
        if (vkCreateInstance(&ci, nullptr, &instance) != VK_SUCCESS) return -1;

        volkLoadInstance(instance);

        uint32_t count = 0;
        vkEnumeratePhysicalDevices(instance, &count, nullptr);

        vkDestroyInstance(instance, nullptr);
        return static_cast<int>(count);
    }

    int GetVulkanDeviceNames(char** names, int maxDevices, int maxNameLength)
    {
        if (!InitVolk() || names == nullptr || maxDevices <= 0 || maxNameLength <= 0) return 0;

        VkInstanceCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        VkInstance instance;
        if (vkCreateInstance(&ci, nullptr, &instance) != VK_SUCCESS) return 0;

        volkLoadInstance(instance);

        uint32_t count = 0;
        if (vkEnumeratePhysicalDevices(instance, &count, nullptr) != VK_SUCCESS || count == 0) {
            vkDestroyInstance(instance, nullptr);
            return 0;
        }

        if ((uint32_t)maxDevices < count) count = static_cast<uint32_t>(maxDevices);

        std::vector<VkPhysicalDevice> devices(count);
        vkEnumeratePhysicalDevices(instance, &count, devices.data());

        for (uint32_t i = 0; i < count; ++i) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(devices[i], &props);
            std::strncpy(names[i], props.deviceName, maxNameLength - 1);
            names[i][maxNameLength - 1] = '\0';
        }

        vkDestroyInstance(instance, nullptr);
        return static_cast<int>(count);
    }

} // extern "C"
