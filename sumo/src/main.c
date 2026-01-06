#include "main.h"
#include "pwm_motor_control.h"
#include "tcp_api_implementation.h"
#include "adc_line_detector.h"
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include "tof_i2c.h"

bool test_tcp(void) {
    DEBUG_printf("TCP test function called.\n");
    TCP_CLIENT_T* tcp_client = tcp_client_init();
    if (tcp_client == NULL) {
        DEBUG_printf("Failed to initialize TCP client.\n");

        return false;
    }
    if (init_wifi_connection(WIFI_SSID, WIFI_PASSWORD) == false) {
        DEBUG_printf("Failed to initialize Wi-Fi connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }
    DEBUG_printf("Wi-Fi connected.\n");
    DEBUG_printf("Connecting to TCP server at %s:%d...\n", TCP_SERVER_IP,
                 TCP_SERVER_PORT);
    if (tcp_client_open_connection(tcp_client) == false) {
        DEBUG_printf("Failed to open TCP connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }
    DEBUG_printf("Connected to TCP server.\n");
    tcp_client->connected = true;
    cyw43_arch_gpio_put(LED_PIN, 1);
    while (tcp_client) {
        cyw43_arch_poll();
    }
    DEBUG_printf("TCP test function completed.\n");
    free(tcp_client);
    cyw43_arch_gpio_put(LED_PIN, 0);
    return true;
    
}

bool test_pwm_controlling(void) {
    cyw43_arch_gpio_put(LED_PIN, 1);
    DEBUG_printf("In test PWM\n");
    stdio_flush();
    pwm_control_init();
    DEBUG_printf("INIT DONE\n");
    stdio_flush();
    pwm_set_motor_dir(MOTOR_DIR_FORWARD);
    pwm_set_motor_speed(1, 50);
    pwm_set_motor_speed(2, 50);
    sleep_ms(5000);
    // pwm_set_motor_speed(1, 0);
    // pwm_set_motor_speed(2, 0);
    // pwm_set_motor_dir(MOTOR_DIR_STOP);
    return true;
}
bool test_tcp_with_pwm_control(void) {
    DEBUG_printf("TCP test function called.\n");
    TCP_CLIENT_T* tcp_client = tcp_client_init();
    if (tcp_client == NULL) {
        DEBUG_printf("Failed to initialize TCP client.\n");

        return false;
    }
    if (init_wifi_connection(WIFI_SSID, WIFI_PASSWORD) == false) {
        DEBUG_printf("Failed to initialize Wi-Fi connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }
    DEBUG_printf("Wi-Fi connected.\n");
    DEBUG_printf("Connecting to TCP server at %s:%d...\n", TCP_SERVER_IP,
                 TCP_SERVER_PORT);
    if (tcp_client_open_connection(tcp_client) == false) {
        DEBUG_printf("Failed to open TCP connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }
    DEBUG_printf("Connected to TCP server.\n");
    tcp_client->connected = true;
    cyw43_arch_gpio_put(LED_PIN, 1);

    pwm_control_init();
    pwm_set_motor_dir(MOTOR_DIR_FORWARD);
    pwm_set_motor_speed(1, 50);
    pwm_set_motor_speed(2, 50);

    adc_line_detector_init();
    while (tcp_client) {
        line_detector_status_t x = adc_check_line();
        cyw43_arch_poll();
        sleep_ms(100);
    }
    DEBUG_printf("TCP test function completed.\n");
    free(tcp_client);
    cyw43_arch_gpio_put(LED_PIN, 0);
    return true;
}

int main(void) {
    stdio_init_all();
    // test_tcp();
    // bool jd = test_pwm_controlling();
    test_tcp_with_pwm_control();
    if(!i2c_start()) {
        DEBUG_printf("Sensors execution failed.\n");
        return 1;
    }

    DEBUG_printf("Execution finished, entering infinite loop.\n");
    while (true) {
        sleep_ms(1000);
    }
    return 0;
}
