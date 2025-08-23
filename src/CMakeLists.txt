add_library(lokeyaudio STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ymfm_2151.cpp
    ${CMAKE_SOURCE_DIR}/external/ymfm/src/ymfm_opm.cpp
)

target_include_directories(lokeyaudio PRIVATE
    ${CMAKE_SOURCE_DIR}/external/ymfm/src
)
