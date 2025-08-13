# CMakeLists.txt
# ym2151-host tests
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(test_ym_host)

# setup SDL if building for host platform
find_package(SDL2 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/../../liblokey liblokey_build)

# test_ym_host
add_executable(test_ym_host_sdl
        ${CMAKE_CURRENT_SOURCE_DIR}/test_ym_host_sdl.cpp
        ${CMAKE_SOURCE_DIR}/../../src/ymfm_2151.cpp
        ${CMAKE_SOURCE_DIR}/../../ymfm/src/ymfm_opm.cpp
)
target_include_directories(test_ym_host_sdl PRIVATE
        ${CMAKE_SOURCE_DIR}/../../ymfm/src
        ${CMAKE_SOURCE_DIR}/../../src
)
target_link_libraries(test_ym_host_sdl PRIVATE liblokey SDL2::SDL2)
