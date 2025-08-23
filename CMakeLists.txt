cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(LOKEY_7800_TARGET_PICO)
        set(LOKEY_TARGET_PICO ON)
        set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk")
        include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
        pico_sdk_init()
endif()

project(lokey-7800)

# Fetch CPM.cmake from GitHub
include(FetchContent)
FetchContent_Declare(
        CPM
        GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
        GIT_TAG master
)
FetchContent_MakeAvailable(CPM)

# doctest
CPMAddPackage(
        NAME doctest
        GITHUB_REPOSITORY doctest/doctest
        VERSION 2.4.12
        OPTIONS "DOCTEST_WITH_MAIN OFF"
)

# setup SDL if building for host platform
if(NOT LOKEY_7800_TARGET_PICO)
        # SDL2
        find_package(SDL2 REQUIRED)
endif()

# Add subdirectories
add_subdirectory(external/liblokey)
add_subdirectory(src)
add_subdirectory(test)
