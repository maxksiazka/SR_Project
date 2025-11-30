#include "pwm_motor_control.h"
#include "main.h"
#include <stdio.h>

void pwm_control_init(void) {
    // intialize PWM on GPIO 0 and GPIO 2
    gpio_set_function(PWM_MOTOR_1_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM_MOTOR_2_GPIO, GPIO_FUNC_PWM);

    uint32_t slice_num[2] = {pwm_gpio_to_slice_num(PWM_MOTOR_1_GPIO),
                             pwm_gpio_to_slice_num(PWM_MOTOR_2_GPIO)};
    uint32_t channel[2] = {pwm_gpio_to_channel(PWM_MOTOR_1_GPIO),
                           pwm_gpio_to_channel(PWM_MOTOR_2_GPIO)};

    pwm_config config[2];
    for (int i = 0; i < 2; i++) {
        config[i] = pwm_get_default_config();
        // the max frequency of the motor driver is 100kHz, we will use 50kHz
        pwm_config_set_clkdiv(&config[i],
                              150.0f); // sys_clk = 150Mhz, 150/150 = 1MHz
        pwm_config_set_wrap(&config[i], (20 - 1));       // 1MHz /20 = 50 kHz
        pwm_set_chan_level(slice_num[i], channel[i], 0); // init stopped
        pwm_init(slice_num[i], &config[i], true);
        DEBUG_printf("PWM Motor %d configuration complete:\n\tslice: "
                     "%d,\n\tchannel: %d\n\tclkdiv: %.2f\n\tTOP: %d\n",
                     i + 1, slice_num[i], channel[i], 150.0f, 20);
    }
    // initialize motor control pins
    gpio_init(GPIO_MOTOR_1_PIN1);
    gpio_set_dir(GPIO_MOTOR_1_PIN1, GPIO_OUT);
    gpio_init(GPIO_MOTOR_1_PIN2);
    gpio_set_dir(GPIO_MOTOR_1_PIN2, GPIO_OUT);

    gpio_init(GPIO_MOTOR_2_PIN1);
    gpio_set_dir(GPIO_MOTOR_2_PIN1, GPIO_OUT);
    gpio_init(GPIO_MOTOR_2_PIN2);
    gpio_set_dir(GPIO_MOTOR_2_PIN2, GPIO_OUT);
}

void pwm_set_motor_dir(MOTOR_DIR direction) {
    switch (direction) {
    case MOTOR_DIR_FORWARD:
        gpio_put(GPIO_MOTOR_1_PIN1, 1);
        gpio_put(GPIO_MOTOR_1_PIN2, 0);
        gpio_put(GPIO_MOTOR_2_PIN1, 1);
        gpio_put(GPIO_MOTOR_2_PIN2, 0);
    case MOTOR_DIR_STOP:
        gpio_put(GPIO_MOTOR_1_PIN1, 0);
        gpio_put(GPIO_MOTOR_1_PIN2, 0);
        gpio_put(GPIO_MOTOR_2_PIN1, 0);
        gpio_put(GPIO_MOTOR_2_PIN2, 0);
        break;
    default:
        DEBUG_printf("Unsupported motor direction command!\n");
        break;
    }
}

void pwm_set_motor_speed(uint8_t motor_id, uint8_t speed_percentage) {
    if (motor_id != 1 && motor_id != 2) {
        DEBUG_printf("Invalid motor ID: %d.\n", motor_id);
        return;
    }
    if (speed_percentage > 100) {
        speed_percentage = 100;
    }

    uint32_t slice_num[2] = {pwm_gpio_to_slice_num(PWM_MOTOR_1_GPIO),
                             pwm_gpio_to_slice_num(PWM_MOTOR_2_GPIO)};
    uint32_t channel[2] = {pwm_gpio_to_channel(PWM_MOTOR_1_GPIO),
                           pwm_gpio_to_channel(PWM_MOTOR_2_GPIO)};

    float duty_cycle_level = (speed_percentage / 100.0f) * 20;

    pwm_set_chan_level(slice_num[motor_id - 1], channel[motor_id - 1],
                       (uint16_t)duty_cycle_level);
}
