#ifndef PWM_MOTOR_CONTROL_H
#define PWM_MOTOR_CONTROL_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define PWM_MOTOR_1_GPIO 0
#define PWM_MOTOR_2_GPIO 2
#define GPIO_MOTOR_1_PIN1 11
#define GPIO_MOTOR_1_PIN2 12
#define GPIO_MOTOR_2_PIN1 13
#define GPIO_MOTOR_2_PIN2 14

typedef enum MOTOR_DIR_ {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_FORWARD = 1,
    MOTOR_DIR_BACKWARD = 2,
    MOTOR_DIR_LEFT = 3,
    MOTOR_DIR_RIGHT = 4
} MOTOR_DIR;

void pwm_control_init(void);

void pwm_set_motor_dir(MOTOR_DIR direction);

void pwm_set_motor_speed(uint8_t motor_id, uint8_t speed_percentage);
#endif // PWM_MOTOR_CONTROL_H
