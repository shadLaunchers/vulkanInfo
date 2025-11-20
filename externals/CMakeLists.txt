# SPDX-FileCopyrightText: Copyright 2025 vulkanInfo Project
# SPDX-License-Identifier: GPL-2.0-or-later


if (NOT TARGET Vulkan::Headers)
    set(VULKAN_HEADERS_ENABLE_MODULE OFF)
    add_subdirectory(ext-vulkan-headers)
endif()

add_subdirectory(ext-volk)
