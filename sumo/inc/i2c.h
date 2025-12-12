#ifndef __I2C_H
#define __I2C_H

#include "hardware/i2c.h"

#define I2C_PORT_0 i2c0
#define I2C_PORT_1 i2c1
#define SDA_PIN_0 20
#define SCL_PIN_0 21
#define SDA_PIN_1 6
#define SCL_PIN_1 7
#define DEF_ADDR 0x29
#define NEW_ADDR 0x2A

extern const int* const XSHUT_PINS;

bool i2c_start(void);
void setup_xshut_pins(void);
bool tof_set_address(i2c_inst_t *i2c, uint8_t current_addr, uint8_t new_addr);

#endif