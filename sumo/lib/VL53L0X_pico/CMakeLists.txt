add_library(VL53L0X_pico_lib STATIC src/tof.c)

target_include_directories(VL53L0X_pico_lib PUBLIC
    # Current directory (lib_common)
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    # The include subdirectory
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(VL53L0X_pico_lib PUBLIC
    pico_stdlib
    hardware_i2c
)
