# SPDX-FileCopyrightText: Copyright 2025 vulkanInfo Project
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.15)
project(VulkanDeviceLibProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force absolute paths to avoid relative path issues
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXTERNALS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals")

# Build external dependencies (Volk + Vulkan-Headers)
add_subdirectory("${EXTERNALS_DIR}")

# Build the DLL
add_library(VulkanDeviceLib SHARED
    "${SRC_DIR}/VulkanDeviceLib.cpp"
)

# Include headers
target_include_directories(VulkanDeviceLib
    PUBLIC
        "${SRC_DIR}"
)

# Link external libraries
target_link_libraries(VulkanDeviceLib
    PRIVATE
        volk
        Vulkan::Headers
)

# Export macro for Windows DLL
target_compile_definitions(VulkanDeviceLib PRIVATE VULKAN_DEVICE_LIB_EXPORTS)

# Windows: remove "lib" prefix
if(WIN32)
    set_target_properties(VulkanDeviceLib PROPERTIES PREFIX "")
endif()

# Installation
install(TARGETS VulkanDeviceLib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES "${SRC_DIR}/VulkanDeviceLib.h" DESTINATION include)
