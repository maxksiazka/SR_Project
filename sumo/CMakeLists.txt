cmake_minimum_required(VERSION 3.13)
add_compile_options(-wall -wextra)

add_compile_options(-pedantic)

add_compile_options(-werror=return-type)

add_compile_options(-werror=parentheses)

add_compile_options(-werror=vla)

add_compile_options(-werror=array-bounds)

additional warnings
add_compile_options ( -wcast-qual )
add_compile_options ( -wmaybe-uninitialized )


set(cmake_export_compile_commands on)
set(pico_board pico2_w)

include(pico_sdk_import.cmake)

project(sumo c cxx asm)

pico_sdk_init()

add_executable(sumo src/main.c
    src/tcp_typedefs.c
src/tcp_api_implementation.c
src/tcp_handling.c
)

target_include_directories(sumo public inc)

pico_enable_stdio_usb(sumo 1)
pico_enable_stdio_uart(sumo 1)

target_link_libraries(sumo 
    pico_cyw43_arch_lwip_poll
    pico_stdlib
)
pico_add_extra_outputs(sumo)

