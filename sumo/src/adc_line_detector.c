#include "adc_line_detector.h"

bool adc_line_detector_init(void) {
    adc_init();
    return true;
}

line_detector_status_t adc_check_line(void) {
    uint16_t left_value = adc_read_line(ADC_LINE_DETECTOR_PIN_LEFT);
    uint16_t right_value = adc_read_line(ADC_LINE_DETECTOR_PIN_RIGHT);

    const uint16_t THRESHOLD = 700;
    if (left_value < THRESHOLD && right_value < THRESHOLD) {
        return LINE_DETECTOR_BOTH_DETECTED;
    }
    if (left_value < THRESHOLD) {
        return LINE_DETECTOR_LEFT_DETECTED;
    }
    if (right_value < THRESHOLD) {
        return LINE_DETECTOR_RIGHT_DETECTED;
    }
    return LINE_DETECTOR_NO_LINE;
}
uint16_t adc_read_line(uint8_t input_pin) {
    adc_select_input(input_pin);
    uint16_t adc_value = adc_read();
    DEBUG_printf("Pin %d,ADC Value: %u\n",input_pin, adc_value);
    return adc_value;
}
