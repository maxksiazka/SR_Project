#include "tcp_api_implementation.h"
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>

bool test_tcp(void) {
    printf("TCP test function called.\n");
    TCP_CLIENT_T* tcp_client = tcp_client_init();
    if (tcp_client == NULL) {
        printf("Failed to initialize TCP client.\n");
        return false;
    }
    if (init_wifi_connection(WIFI_SSID, WIFI_PASSWORD) == false) {
        printf("Failed to initialize Wi-Fi connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }
    if (tcp_client_open_connection(tcp_client) == false) {
        printf("Failed to open TCP connection.\n");
        tcp_client_close(tcp_client);
        return false;
    }

    printf("Connected to TCP server.\n");
    while (!tcp_client->connected) {
        cyw43_arch_gpio_put(LED_PIN, !(cyw43_arch_gpio_get(LED_PIN)));
        cyw43_arch_poll();
    }
    return true;
}

int main(void) {
    // Initialize the Raspberry Pi Pico SDK
    stdio_init_all();

    test_tcp();

    printf("Main function completed.\n");
    return 0;
}
