add_library(pokey STATIC pokey.c)

target_include_directories(pokey PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Disable warnings for pokey.c (third-party source)
set_source_files_properties(pokey.c PROPERTIES COMPILE_FLAGS "-w")
