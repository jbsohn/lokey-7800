
# test_audio_gpio_pico
add_executable(test_bus_play_note_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_bus_play_note_pico.cpp
)
target_link_libraries(test_bus_play_note_pico PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(test_bus_play_note_pico 1)
pico_enable_stdio_uart(test_bus_play_note_pico 0)
pico_add_extra_outputs(test_bus_play_note_pico)

