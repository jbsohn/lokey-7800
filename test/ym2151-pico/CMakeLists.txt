# ym2151

add_executable(test_ym_pico
        test_ym_pico.cpp
        ${CMAKE_SOURCE_DIR}/src/nuked_opm_ym.cpp
        ${CMAKE_SOURCE_DIR}/Nuked-OPM/opm.c
)
target_include_directories(test_ym_pico PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/Nuked-OPM
)
target_link_libraries(test_ym_pico PRIVATE
        liblokey
        pico_stdlib
        hardware_pwm
        hardware_pio
)
pico_add_extra_outputs(test_ym_pico)
