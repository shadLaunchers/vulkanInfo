# SPDX-FileCopyrightText: Copyright 2025 vulkanInfo Project
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.15)
project(VulkanDeviceLibProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Absolute paths
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXTERNALS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals")

option(USE_SHARED_LIBS "Build VulkanDeviceLib as a shared library" OFF)

if(USE_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()

message(STATUS "VulkanDeviceLib will be built as: ${LIB_TYPE}")

# Force externals to build static libraries if VulkanDeviceLib is static
if(NOT USE_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Force externals static" FORCE)
endif()

add_subdirectory("${EXTERNALS_DIR}")

add_library(VulkanDeviceLib ${LIB_TYPE}
    "${SRC_DIR}/VulkanDeviceLib.cpp"
)

# Include headers
target_include_directories(VulkanDeviceLib
    PUBLIC "${SRC_DIR}"
)

# Link Volk and Vulkan-Headers
target_link_libraries(VulkanDeviceLib
    PRIVATE volk
            Vulkan::Headers
)

# Windows: handle dllexport/dllimport for shared builds
if(WIN32 AND USE_SHARED_LIBS)
    target_compile_definitions(VulkanDeviceLib PRIVATE VULKAN_DEVICE_LIB_EXPORTS)
    set_target_properties(VulkanDeviceLib PROPERTIES PREFIX "")
endif()

# Position-independent code for static libraries
if(NOT USE_SHARED_LIBS)
    set_target_properties(VulkanDeviceLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

install(TARGETS VulkanDeviceLib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES "${SRC_DIR}/VulkanDeviceLib.h" DESTINATION include)
