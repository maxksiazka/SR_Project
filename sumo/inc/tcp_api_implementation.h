#ifndef TCP_API_IMPLEMENTATION_H
#define TCP_API_IMPLEMENTATION_H

#ifndef LED_PIN
#define LED_PIN CYW43_WL_GPIO_LED_PIN
#endif

// conditional definitions, since might be added in CMakeLists.txt
#ifndef WIFI_SSID
#define WIFI_SSID "Ogienzrury"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "RobotenMachen"
#endif

#ifndef TCP_SERVER_IP
#define TCP_SERVER_IP "10.149.66.204"
#endif

#ifndef TCP_SERVER_PORT
#define TCP_SERVER_PORT 5001
#endif

#ifndef TCP_BUF_SIZE
#define TCP_BUF_SIZE 2048
#endif

#include "hardware/gpio.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <lwip/tcp.h>

typedef struct TCP_CLIENT_T_{
    struct tcp_pcb* tcp_pcb;
    ip_addr_t remote_addr;
    uint8_t buffer[TCP_BUF_SIZE];
    int buffer_len;
    bool connected;
} TCP_CLIENT_T_;

bool init_wifi_connection(const char *ssid, const char* password);

TCP_CLIENT_T_ *tcp_client_init(void);

bool tcp_client_open_connection(TCP_CLIENT_T_ *client);

//templates from lwip's website
err_t tcp_receive_callback(void *arg, struct tcp_pcb* client_pcb, struct pbuf *p, err_t err);
err_t tcp_sent_callback(void *arg, struct tcp_pcb* client_pcb, u_int16_t length);
void tcp_error_callback(void *arg, err_t err);
err_t tcp_connected_callback(void *arg, struct tcp_pcb* client_pcb,err_t err);


#endif // TCP_API_IMPLEMENTATION_H
