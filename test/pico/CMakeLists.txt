
add_executable(test_lokey_7800
        ${CMAKE_CURRENT_SOURCE_DIR}/test_lokey_7800.cpp
)
target_link_libraries(test_lokey_7800 PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(test_lokey_7800 1)
pico_enable_stdio_uart(test_lokey_7800 0)
pico_add_extra_outputs(test_lokey_7800)