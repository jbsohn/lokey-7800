
# pico_stress
add_executable(pico_sender
        ${CMAKE_CURRENT_SOURCE_DIR}/pico_sender.cpp
)
target_link_libraries(pico_sender PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(pico_sender 1)
pico_enable_stdio_uart(pico_sender 0)
pico_add_extra_outputs(pico_sender)

# pico_receiver
add_executable(pico_receiver
        ${CMAKE_CURRENT_SOURCE_DIR}/pico_receiver.cpp
)
target_link_libraries(pico_receiver PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(pico_receiver 1)
pico_enable_stdio_uart(pico_receiver 0)
pico_add_extra_outputs(pico_receiver)
