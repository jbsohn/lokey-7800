
# pico_stress
add_executable(pico_stress
        ${CMAKE_CURRENT_SOURCE_DIR}/pico_stress.cpp
)
target_link_libraries(pico_stress PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(pico_stress 1)
pico_enable_stdio_uart(pico_stress 0)
pico_add_extra_outputs(pico_stress)
