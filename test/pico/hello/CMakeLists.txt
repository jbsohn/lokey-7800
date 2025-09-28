# hello

add_executable(hello
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.cpp
)
#target_include_directories(test_ym_pico PRIVATE
#        ${CMAKE_SOURCE_DIR}/src
#        ${CMAKE_SOURCE_DIR}/external/ymfm/src
#        ${CMAKE_SOURCE_DIR}/external/liblokey/include
#)
target_link_libraries(hello PRIVATE
        pico_stdlib
        hardware_pwm
        hardware_pio
)
pico_enable_stdio_usb(hello 1)
pico_enable_stdio_uart(hello 0)
pico_add_extra_outputs(hello)
