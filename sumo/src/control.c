#include "control.h"
#include "VL53L0X_pico.h"
#include "adc_line_detector.h"
#include "tof_i2c.h"

void init_data_struct(void) {
    buffer_t buf[4];
    for (uint8_t i = 0; i < 3; ++i) {
        buf[i].next = &buf[(i + 1) % 3];
    }
    head = &buf[0];
}

void collect_data(void) {
    head->data.i2c_left = tofReadDistance(I2C_PORT_LEFT, I2C_LEFT);
    head->data.i2c_right = tofReadDistance(I2C_PORT_RIGHT, I2C_RIGHT);
    head->data.i2c_front_left = tofReadDistance(I2C_PORT_LEFT, I2C_FRONT_LEFT);
    head->data.i2c_front_right = tofReadDistance(I2C_PORT_RIGHT, I2C_FRONT_RIGHT);
    head->data.adc_left = adc_read_line(ADC_LINE_DETECTOR_PIN_LEFT);
    head->data.adc_right = adc_read_line(ADC_LINE_DETECTOR_PIN_RIGHT);
}

void calculate_mean(void) {
    buffer_t* buf1 = head->next;
    buffer_t* buf2 = buf1->next;
    buffer_t* buf3 = buf2->next;
    float alpha = 0.6;

    mean_left = tofReadDistance(I2C_PORT_LEFT, I2C_LEFT) * alpha + (1 - alpha) * mean_left;
    mean_front_left =
        tofReadDistance(I2C_PORT_LEFT, I2C_FRONT_LEFT) * alpha + (1 - alpha) * mean_front_left;
    mean_front_right =
        tofReadDistance(I2C_PORT_RIGHT, I2C_FRONT_RIGHT) * alpha + (1 - alpha) * mean_front_right;
    mean_right = tofReadDistance(I2C_PORT_RIGHT, I2C_RIGHT) * alpha + (1 - alpha) * mean_right;
}
