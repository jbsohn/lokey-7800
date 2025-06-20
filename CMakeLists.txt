cmake_minimum_required(VERSION 3.15)
project(lokey)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: SDL2 for host builds
find_package(SDL2 REQUIRED)

# Add subdirectories
add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(firmware)
add_subdirectory(host_test)
