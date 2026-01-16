#ifndef CONTROL_H
#define CONTROL_H

#include "pico/stdlib.h"

typedef struct {
    uint16_t i2c_left;
    uint16_t i2c_right;
    uint16_t i2c_front_left;
    uint16_t i2c_front_right;
    uint16_t adc_left;
    uint16_t adc_right;
} control_data_t;

typedef struct {
    control_data_t data;
    void * next;
} buffer_t;

enum MODE {SURVIVAL, FIRST_CONTACT ,ATTACK, AQUISITION};


void init_data_struct(void);
void collect_data(void);
/**
 * Funkcja do obliczania średniej wykładniczej
 *
 */
void calculate_mean(void);
uint16_t calculate_real_values(control_data_t data);
enum MODE designate_strategy(void);
void begin_acquisition(void);
bool acquire_target(void);
void predict_alignment(void);

bool fight_mode_enable(void);





#endif
