#ifndef TCP_TYPEDEFS_H
#define TCP_TYPEDEFS_H

// conditional definitions, since might be added in CMakeLists.txt
#ifndef WIFI_SSID
#define WIFI_SSID "HALNy-2.4G-001f85"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YtWWH9Lc3c"
#endif

#ifndef TCP_SERVER_IP
#define TCP_SERVER_IP "192.168.34.11"
#endif

#ifndef TCP_SERVER_PORT
#define TCP_SERVER_PORT 5001
#endif

#ifndef TCP_BUF_SIZE
#define TCP_BUF_SIZE 2048
#endif

#include <lwip/tcp.h>

typedef enum COMMAND_TYPE_ {
    COMMAND_ECHO = 0,
    COMMAND_STOP = 1,
    COMMAND_FORWARD = 2,
    COMMAND_BACKWARDS = 3,
    COMMAND_LEFT = 4,
    COMMAND_RIGHT = 5,
    COMMAND_UNDEFINED = 255,
} COMMAND_TYPE;

extern const char* COMMAND_TYPE_STRINGS[];

typedef struct TCP_CLIENT_T_ {
    struct tcp_pcb* tcp_pcb;
    ip_addr_t remote_addr;
    uint8_t buffer[TCP_BUF_SIZE];
    int32_t buffer_len;
    bool connected;
} TCP_CLIENT_T;

#endif // TCP_TYPEDEFS_H

/**
 * COMMAND_STOP
 * COMMAND_FORWARD
 * COMMAND_BACKWARDS
 * COMMAND_LEFT
 * COMMAND_RIGHT
 * ...
 */
