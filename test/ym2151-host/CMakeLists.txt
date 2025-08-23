# ym2151-host tests

add_executable(test_ym_host_sdl
        test_ym_host_sdl.cpp
)
target_include_directories(test_ym_host_sdl PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/ymfm/src

)
target_link_libraries(test_ym_host_sdl PRIVATE liblokey lokeyaudio SDL2::SDL2)
