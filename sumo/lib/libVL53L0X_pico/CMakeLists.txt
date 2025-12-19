cmake_minimum_required(VERSION 3.13)
add_library(libVL53L0X_pico 
    src/VL53L0X_pico.c
)
target_include_directories(libVL53L0X_pico PUBLIC 
    inc
)
target_link_libraries(libVL53L0X_pico PUBLIC
    pico_stdlib
    hardware_i2c
)

