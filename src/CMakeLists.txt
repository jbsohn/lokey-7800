add_library(lokey_audio STATIC
        lokey_audio.cpp
        NukedOpmYM.cpp
)

target_include_directories(lokey_audio PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Nuked-OPM
)

target_link_libraries(lokey_audio
        liblokey
)
