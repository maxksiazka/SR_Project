#ifndef ADC_LINE_DETECTOR_H
#define ADC_LINE_DETECTOR_H

#include "main.h"
#include "hardware/adc.h"

#define ADC_LINE_DETECTOR_PIN_LEFT 0 
#define ADC_LINE_DETECTOR_PIN_RIGHT 1

typedef enum {
    LINE_DETECTOR_NO_LINE = 0,
    LINE_DETECTOR_LEFT_DETECTED,
    LINE_DETECTOR_RIGHT_DETECTED,
    LINE_DETECTOR_BOTH_DETECTED
} line_detector_status_t;

bool adc_line_detector_init(void);
line_detector_status_t adc_check_line(void);
uint16_t adc_read_line(uint8_t input_pin);

#endif // ADC_LINE_DETECTOR_H
t_set_a