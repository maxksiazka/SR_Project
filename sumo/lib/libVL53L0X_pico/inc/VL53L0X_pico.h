#ifndef _TOFLIB_H_
#define _TOFLIB_H_
/*
 * VL53L0X Library Fork
 * Based on work by Pololu, bitbank2, and danjperron.
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
//
// Read the model and revision of the
// tof sensor
//
int tofGetModel(i2c_inst_t *i2c, uint8_t addr, int *model, int *revision);

//
// Read the current distance in mm
//
int tofReadDistance(i2c_inst_t *i2c, uint8_t addr);

//
// Opens a file system handle to the I2C device
// sets the device continous capture mode
//
int tofInit(i2c_inst_t *i2c, uint8_t addr, int bLongRange);

#endif // _TOFLIB_H
