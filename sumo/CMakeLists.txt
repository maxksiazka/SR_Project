cmake_minimum_required(VERSION 3.13)
add_compile_options(-Wall -Wextra)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(sumo C CXX ASM)

pico_sdk_init()

add_executable(sumo src/main.c
    src/tcp_typedefs.c
    src/tcp_api_implementation.c
    src/tcp_handling.c
    src/pwm_motor_control.c
)

target_include_directories(sumo PUBLIC inc)

pico_enable_stdio_usb(sumo 1)
pico_enable_stdio_uart(sumo 1)

target_link_libraries(sumo 
    pico_cyw43_arch_lwip_poll
    pico_stdlib
    hardware_i2c
    hardware_pwm
    hardware_adc
)
pico_add_extra_outputs(sumo)

