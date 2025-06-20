# You can customize this for Pico SDK integration later
add_executable(rp2040_main
        main.cpp
)

target_link_libraries(rp2040_main
        lokey_audio
)
