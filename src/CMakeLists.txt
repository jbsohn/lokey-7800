add_library(lokey_audio STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ymfm_2151.cpp
)

target_include_directories(lokey_audio PRIVATE
        ${CMAKE_SOURCE_DIR}/external/ymfm/src
)
