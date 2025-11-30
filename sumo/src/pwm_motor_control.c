#include "pwm_motor_control.h"
#include "main.h"
#include <stdio.h>

#define PWM_MOTOR_1_GPIO 0
#define PWM_MOTOR_2_GPIO 2

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
}
