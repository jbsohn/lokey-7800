# ym2151

add_executable(test_ym_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_ym_pico.cpp
        ${CMAKE_SOURCE_DIR}/external/ymfm/src/ymfm_opm.cpp
)
target_include_directories(test_ym_pico PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/ymfm/src
        ${CMAKE_SOURCE_DIR}/external/liblokey/include
)
target_link_libraries(test_ym_pico PRIVATE
        lokey_audio
        liblokey
        pico_stdlib
        hardware_pwm
        hardware_pio
)
pico_enable_stdio_usb(test_ym_pico 1)
pico_enable_stdio_uart(test_ym_pico 0)
pico_add_extra_outputs(test_ym_pico)
