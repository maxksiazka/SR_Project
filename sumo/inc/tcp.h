#ifndef TCP_H
#define TCP_H

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


#endif // TCP_H
       //
