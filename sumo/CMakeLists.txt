cmake_minimum_required(VERSION 3.13)
add_compile_options(-Wall -Wextra)

add_compile_options(-pedantic)

add_compile_options(-Werror=return-type)

add_compile_options(-Werror=parentheses)

add_compile_options(-Werror=vla)

add_compile_options(-Werror=array-bounds)

# additional warnings
add_compile_options ( -Wcast-qual )
add_compile_options ( -Wmaybe-uninitialized )


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(sumo C CXX ASM)

pico_sdk_init()

add_executable(sumo src/main.c
src/tcp_api_implementation.c
src/tcp_handling.c
)

target_include_directories(sumo PUBLIC inc)

pico_enable_stdio_usb(sumo 1)
pico_enable_stdio_uart(sumo 1)

target_link_libraries(sumo 
    pico_cyw43_arch_lwip_poll
    pico_stdlib
)
pico_add_extra_outputs(sumo)

