#include "i2c.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "tof.h"
#include "main.h"

const int* const XSHUT_PINS = {4, 5};

void setup_xshut_pins(void) {
    for (int i = 0; i < NUM_SENSORS; i++) {
        gpio_init(XSHUT_PINS[i]);
        gpio_set_dir(XSHUT_PINS[i], GPIO_OUT);
        gpio_put(XSHUT_PINS[i], 0);
    }
    sleep_ms(100);
}

bool tof_set_address(i2c_inst_t *i2c, uint8_t current_addr, uint8_t new_addr) {
    uint8_t buffer[2] = {0x8A, new_addr};

    int ret = i2c_write_blocking(i2c, current_addr, buffer, 2, false);

    return ret == 2;
}

bool i2c_start(void) {
    int model, rev;

    i2c_init(I2C_PORT_0, 400 * 1000);
    i2c_init(I2C_PORT_1, 400 * 1000);

    gpio_set_function(SDA_PIN_0, GPIO_FUNC_I2C);
    gpio_set_function(SDA_PIN_1, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN_0, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN_1, GPIO_FUNC_I2C);

    gpio_pull_up(SDA_PIN_0);
    gpio_pull_up(SDA_PIN_1);
    gpio_pull_up(SCL_PIN_0);
    gpio_pull_up(SCL_PIN_1);

    bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));
    setup_xshut_pins();

    gpio_put(XSHUT_PINS[0], 1);
    gpio_put(XSHUT_PINS[1], 1);

    sleep_ms(10);

    tof_set_address(I2C_PORT_0, DEF_ADDR, NEW_ADDR);
    tof_set_address(I2C_PORT_0, DEF_ADDR, NEW_ADDR);

    gpio_put(XSHUT_PINS[0], 0);
    gpio_put(XSHUT_PINS[1], 0);
    sleep_ms(10);

    if(tofInit(I2C_PORT_0, DEF_ADDR, 0) != 1) {
        DEBUG_printf("Problem z inicjalizacja TOF");
        return false;
    }

    tofGetModel(&model, &rev);
    DEBUG_printf("Model ID: %d\n", model);
    DEBUG_printf("Revision ID: %d\n", rev);
    DEBUG_printf("Zainicjalizowano VL53L0X na adresie %d\n", addr);

    return true;
}