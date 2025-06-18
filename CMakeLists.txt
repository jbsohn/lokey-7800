cmake_minimum_required(VERSION 3.13)

project(lokey C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# --- Check if we are targeting RP2040 (Pico) ---
if (DEFINED ENV{PICO_SDK_PATH} OR EXISTS "${CMAKE_SOURCE_DIR}/pico_sdk_import.cmake")
    include(pico_sdk_import.cmake)
    pico_sdk_init()

    add_executable(lokey
            src/main.cpp
            src/sound/pokey.c
    )

    target_include_directories(lokey PRIVATE src)
    target_link_libraries(lokey pico_stdlib hardware_pwm)
    pico_add_extra_outputs(lokey)

else()
    message(STATUS "Skipping Pico target; PICO_SDK_PATH not set.")
endif()

# --- Native SDL2 test target ---
find_package(SDL2 REQUIRED)

add_executable(lokey_sdl_test
        tests/sdl_host/main.cpp
        tests/sdl_host/demo_loop.cpp
        tests/sdl_host/demo_melody.cpp
        tests/sdl_host/demo_scale.cpp
        src/sound/pokey.c
)

target_include_directories(lokey_sdl_test PRIVATE
        ${SDL2_INCLUDE_DIRS}
        src
)

target_link_libraries(lokey_sdl_test ${SDL2_LIBRARIES})