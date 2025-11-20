// SPDX-FileCopyrightText: Copyright 2025 vulkanInfo Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stddef.h>

#if defined(_WIN32)
#  if defined(VULKAN_DEVICE_LIB_EXPORTS)
#    define VDL_API __declspec(dllexport)
#  elif defined(VULKAN_DEVICE_LIB_IMPORTS)
#    define VDL_API __declspec(dllimport)
#  else
#    define VDL_API
#  endif
#else
#  define VDL_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Returns the number of Vulkan physical devices available.
	 */
	VDL_API int GetVulkanDeviceCount();

	/**
	 * Fills the provided array with Vulkan device names.
	 * @param names Array of char* buffers (each buffer must be at least maxNameLength)
	 * @param maxDevices Maximum number of devices to fill
	 * @param maxNameLength Maximum length of each device name (including null terminator)
	 * @return Number of devices actually written
	 */
	VDL_API int GetVulkanDeviceNames(char** names, int maxDevices, int maxNameLength);

#ifdef __cplusplus
}
#endif
