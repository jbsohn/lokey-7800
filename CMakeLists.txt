cmake_minimum_required(VERSION 3.25)
project(lokey)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Fetch CPM.cmake from GitHub
include(FetchContent)
FetchContent_Declare(
        CPM
        GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
        GIT_TAG master
)
FetchContent_MakeAvailable(CPM)

# liblokey
CPMAddPackage(
        NAME liblokey
        GITHUB_REPOSITORY jbsohn/liblokey
        GIT_TAG main
)
find_package(liblokey)

# Add subdirectories
add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(firmware)
add_subdirectory(host_test)
