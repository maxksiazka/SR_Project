#include "tcp_api_implementation.h"

// TODO: change type to account for different fails
bool init_wifi_connection(const char *ssid, const char *password) {
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_POLAND)) {
        printf("Failed to initialize Wi-Fi controller: init_wifi_connection()\n");
        return false;
    }
    cyw43_arch_enable_sta_mode();

    // 30 seconds to connect
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to Wi-Fi: init_wifi_connnection()\n");
        return false;
    }
    return true;
}

TCP_CLIENT_T_ *tcp_client_init(void) {
    TCP_CLIENT_T_ *client = calloc(1, sizeof(TCP_CLIENT_T_));
    if (client == NULL) {
        printf("Failed memory allocation: tcp_client_init\n");
        exit(-1); // don't try to recover
    }
    ip4addr_aton(TCP_SERVER_IP, &client->remote_addr);
    return client;
}

static err_t tcp_connected_callback(void *arg, struct tcp_pcb *client_pcb, err_t err) {
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
#warning "implement connected handling"
    return ERR_OK;
}
static err_t tcp_receive_callback(void *arg, struct tcp_pcb *client_pcb, struct pbuf *p,
                                  err_t err) {
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
#warning "implement receive handling"
    return ERR_OK;
}
static err_t tcp_sent_callback(void *arg, struct tcp_pcb *client_pcb, u_int16_t length) {
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
#warning "implement sent handling"
    return ERR_OK;
}
static void tcp_error_callback(void *arg, err_t err) {
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
#warning "implement error handling"
    return;
}

bool tcp_client_open_connection(TCP_CLIENT_T_ *client) {
    printf("Connecting to %s, on port %d\n", TCP_SERVER_IP, TCP_SERVER_PORT);
    client->tcp_pcb = tcp_new_ip_type(IP_GET_TYPE(&client->remote_addr));
    if (client->tcp_pcb == NULL) {
        printf("Failed memory allocation: tcp_client_open_connection()\n");
        return false;
    }
    tcp_arg(client->tcp_pcb, client); // we wanna pass the entire struct
    tcp_sent(client->tcp_pcb, tcp_sent_callback);
    tcp_recv(client->tcp_pcb, tcp_receive_callback);
    tcp_err(client->tcp_pcb, tcp_error_callback);
    client->buffer_len=0;

    err_t err = tcp_connect(client->tcp_pcb,&client->remote_addr, TCP_SERVER_PORT, tcp_connected_callback);

    return true;
}
