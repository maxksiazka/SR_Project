cmake_minimum_required(VERSION 3.13)
# add_compile_options(-Wall -Wextra)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico2_w)
# set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
# set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
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

target_link_libraries(sumo 
    pico_cyw43_arch_lwip_poll
    pico_stdlib
    hardware_pwm
)
target_compile_definitions(sumo PRIVATE
    WIFI_SSID="$ENV{WIFI_SSID}"
    WIFI_PASSWORD="$ENV{WIFI_PASSWORD}"
    TCP_SERVER_IP="$ENV{TCP_SERVER_IP}"
)
pico_enable_stdio_usb(sumo 1)
pico_enable_stdio_uart(sumo 1)

pico_add_extra_outputs(sumo)

