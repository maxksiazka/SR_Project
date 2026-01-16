#include "control.h"
#include "VL53L0X_pico.h"
#include "adc_line_detector.h"
#include "pwm_motor_control.h"
#include "tof_i2c.h"

#define DISTANCE_THRESHOLD 600

static buffer_t buf[4];
static buffer_t* head;
static double mean_left;
static double mean_front_left;
static double mean_front_right;
static double mean_right;

void init_data_struct(void) {
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
    head = head->next;
}
enum MODE designate_strategy(void) {
    if (head->data.adc_left < 2000 || head->data.adc_right < 2000) {
        return SURVIVAL;
    }
    if (mean_front_left < DISTANCE_THRESHOLD || mean_front_right < DISTANCE_THRESHOLD) {
        return ATTACK;
    }
    return AQUISITION;
}
void begin_acquisition() {
    pwm_turn_clockwise();
}
bool acquire_target() {
    if (mean_front_left > mean_front_right) {
        pwm_pivot_counterclockwise();
    } else if (mean_front_left < mean_front_right) {
        pwm_pivot_clockwise();
    } else {
        pwm_set_motor_dir(MOTOR_DIR_FORWARD);
    }

    return true;
}
void predict_alignment() {

    pwm_set_motor_dir(MOTOR_DIR_FORWARD);
    // First, we calculate the difference between the left and right distances
    int16_t distance_diff = mean_left - mean_right;
    // Threshold to determine if RADICAL adjustment is needed
    const int16_t ALIGNMENT_THRESHOLD = 100; // in mm
    if (distance_diff > ALIGNMENT_THRESHOLD) {
        // coast left
        pwm_set_motor_speed(MOTOR_LEFT, 0);
        pwm_set_motor_speed(MOTOR_RIGHT, 100);
        return;
    } else if (distance_diff < -ALIGNMENT_THRESHOLD) {
        // coast right
        pwm_set_motor_speed(MOTOR_LEFT, 100);
        pwm_set_motor_speed(MOTOR_RIGHT, 0);
        return;
    }

    // we will need some equation to predict the alignment
    if (distance_diff > 10) {
        // Slightly closer on the right side, turn left
        pwm_set_motor_speed(MOTOR_LEFT, 70);
        pwm_set_motor_speed(MOTOR_RIGHT, 90);
    }

    else if (distance_diff < 10) {
        // Slightly closer on the left side, turn right
        pwm_set_motor_speed(MOTOR_LEFT, 70);
        pwm_set_motor_speed(MOTOR_RIGHT, 90);
    } else {
        // pieknie jest, cała naprzód
        pwm_set_motor_speed(MOTOR_LEFT, 100);
        pwm_set_motor_speed(MOTOR_RIGHT, 100);
    }
}

bool fight_mode_enable() {
    init_data_struct();
    enum MODE current_strategy = AQUISITION;
    begin_acquisition();
    pwm_set_motor_speed(MOTOR_LEFT, 80);
    pwm_set_motor_speed(MOTOR_RIGHT, 80);
    while (true) {
        collect_data();
        calculate_mean();
        current_strategy = designate_strategy();
        if (current_strategy == FIRST_CONTACT) {
            continue;
        }
        if (current_strategy == AQUISITION) {
            acquire_target();
            continue;
        }
        if (current_strategy == SURVIVAL) {
            pwm_set_motor_dir(MOTOR_DIR_BACKWARD);
            pwm_set_motor_speed(MOTOR_LEFT, 100);
            pwm_set_motor_speed(MOTOR_RIGHT, 100);
            sleep_ms(100);
            current_strategy = FIRST_CONTACT;
            begin_acquisition();
            continue;
        }

        predict_alignment();
    }
    return true;
}
