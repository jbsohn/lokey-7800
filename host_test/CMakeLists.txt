add_executable(host_test
        main.cpp
)

target_link_libraries(host_test
        lokey_audio
        SDL2::SDL2
)
