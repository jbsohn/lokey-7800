add_library(lokey_audio STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/nuked_opm_ym.cpp
)

target_include_directories(lokey_audio PRIVATE
        ${CMAKE_SOURCE_DIR}/Nuked-OPM
)
