# CMakeLists.txt
# ym2151-host tests
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(EXTERNAL_PATH "${CMAKE_SOURCE_DIR}/../..")
set(LOKEY_POKEY_PATH "${CMAKE_SOURCE_DIR}/../../..")

project(test_ym_host)

# setup SDL if building for host platform
find_package(SDL2 REQUIRED)

add_subdirectory(${EXTERNAL_PATH}/liblokey liblokey_build)

# test_ym_host
add_executable(test_ym_host_sdl
        test_ym_host_sdl.cpp
        ${LOKEY_POKEY_PATH}/src/ymfm_2151.cpp
        ${EXTERNAL_PATH}/ymfm/src/ymfm_opm.cpp
)
target_include_directories(test_ym_host_sdl PRIVATE
        ${LOKEY_POKEY_PATH}/src
        ${EXTERNAL_PATH}/ymfm/src
)
target_link_libraries(test_ym_host_sdl PRIVATE liblokey SDL2::SDL2)
