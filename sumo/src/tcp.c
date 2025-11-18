#include "tcp.h"

// TODO: change type to account for different fails
bool init_wifi_connection(const char *ssid, const char *password) {
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_POLAND)) {
        printf("Failed to initialize Wi-Fi controller: init_wifi_connection()");
        return false;
    }
    cyw43_arch_enable_sta_mode();

    // 30 seconds to connect
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to Wi-Fi: init_wifi_connnection()");
        return false;
    }
    return true;
}
