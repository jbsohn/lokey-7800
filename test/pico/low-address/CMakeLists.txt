# pico_low-address

add_executable(pico_low-address
        ${CMAKE_CURRENT_SOURCE_DIR}/low-address.cpp
)

target_link_libraries(pico_low-address PRIVATE
        pico_stdlib
        hardware_pwm
        hardware_pio
)
pico_enable_stdio_usb(pico_low-address 1)
pico_enable_stdio_uart(pico_low-address 0)
pico_add_extra_outputs(pico_low-address)
