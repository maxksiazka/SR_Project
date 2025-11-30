#include "tcp_api_implementation.h"
#include "main.h"
#include "tcp_handling.h"
// TODO: change type to account for different fails
bool init_wifi_connection(const char* ssid, const char* password) {
    if (cyw43_arch_init()) {
        DEBUG_printf(
            "Failed to initialize Wi-Fi controller: init_wifi_connection()\n");
        return false;
    }
    cyw43_arch_enable_sta_mode();

    // 30 seconds to connect
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password,
                                           CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        DEBUG_printf("Failed to connect to Wi-Fi: init_wifi_connnection()\n");
        return false;
    }
    return true;
}

TCP_CLIENT_T* tcp_client_init(void) {
    TCP_CLIENT_T* client = calloc(1, sizeof(TCP_CLIENT_T));
    if (client == NULL) {
        DEBUG_printf("Failed memory allocation: tcp_client_init\n");
        exit(-1); // don't try to recover
    }
    int32_t err = ip4addr_aton(TCP_SERVER_IP, &client->remote_addr);
    if (err == 0) {
        DEBUG_printf("Invalid IP address format: tcp_client_init()\n");
        free(client);
        return NULL;
    }
    return client;
}

err_t tcp_connected_callback(void* arg, struct tcp_pcb* client_pcb, err_t err) {
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    DEBUG_printf("In tcp_connected_callback\n");

    if(client == NULL || client_pcb == NULL) {
        DEBUG_printf("tcp_connected_callback: client or client_pcb is NULL\n");
        return err;
    }

    if(err != ERR_OK) {
        DEBUG_printf("Error %d occuried.", err);
        tcp_client_close(client);
        return err;
    }
    
    client->connected = true;
    DEBUG_printf("Connected established with server.\n");

    return ERR_OK;
}
err_t tcp_receive_callback(void* arg, struct tcp_pcb* client_pcb,
                           struct pbuf* p, err_t err) {
    DEBUG_printf("In tcp_receive_callback\n");
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL) {
        return ERR_VAL;
    }
    if (p == NULL) {
        // connection gracefully closed
        DEBUG_printf("Connection closed signal received.\n");
        err_t err_close = tcp_client_close(client);
        return err_close;
    }

    if (p->tot_len > 0) {
        DEBUG_printf("recv %d bytes\n", p->tot_len);
        const uint16_t buffer_remaining = TCP_BUF_SIZE - client->buffer_len;
        client->buffer_len += pbuf_copy_partial(
            p, client->buffer + client->buffer_len, // addition , so we don't
                                                    // write over the data
            (p->tot_len > buffer_remaining) ? buffer_remaining : p->tot_len,
            0); // the expression ensures we don't overflow

        tcp_recved(client_pcb, p->tot_len);
    }
    pbuf_free(p);
    tcp_handle_message(arg, client_pcb, err);
    client->buffer_len = 0;
    return ERR_OK;
}
err_t tcp_sent_callback(void* arg, struct tcp_pcb* client_pcb,
                        u_int16_t length) {
    DEBUG_printf("In tcp_sent_callback\n");
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL || client_pcb == NULL) {
        DEBUG_printf("tcp_sent_callback: client or client_pcb is NULL\n");
        return ERR_VAL;
    }
    DEBUG_printf("Sent %d bytes\n", length);
    DEBUG_printf("Message sent successfully.\n");
    return ERR_OK;
}
void tcp_error_callback(void* arg, err_t err) {
    DEBUG_printf("In tcp_error_callback\n");

    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if(client == NULL) {
        DEBUG_printf("tcp_error_callback: client is NULL\n");
        return;
    }

    switch(err) {
        case ERR_RST:
            DEBUG_printf("Error occuried. Connection to server disappeard.\n"); break;
        case ERR_ABRT:
            DEBUG_printf("Error occuried. Connection closed unexpectedly.\n"); break;
        case ERR_TIMEOUT:
            DEBUG_printf("Error occuried. Connection timed out.\n"); break;;
        default:
            DEBUG_printf("Error %d occuried.\n", err); break;
    }
    tcp_client_close(client);
    return;
}

bool tcp_client_open_connection(TCP_CLIENT_T* client) {
    DEBUG_printf("Connecting to %s, on port %d\n", TCP_SERVER_IP,
                 TCP_SERVER_PORT);
    client->tcp_pcb = tcp_new_ip_type(IP_GET_TYPE(&client->remote_addr));
    if (client->tcp_pcb == NULL) {
        DEBUG_printf(
            "Failed memory allocation: tcp_client_open_connection()\n");
        return false;
    }
    tcp_arg(client->tcp_pcb, client); // we wanna pass the entire struct
    tcp_sent(client->tcp_pcb, tcp_sent_callback);
    tcp_recv(client->tcp_pcb, tcp_receive_callback);
    tcp_err(client->tcp_pcb, tcp_error_callback);
    client->buffer_len = 0;

    err_t err = tcp_connect(client->tcp_pcb, &client->remote_addr,
                            TCP_SERVER_PORT, tcp_connected_callback);
    if (err != ERR_OK) {
        DEBUG_printf("tcp_connect failed with error: %d\n", err);
        tcp_client_close(client);
        return false;
    }

    return true;
}

err_t tcp_client_close(void* arg) {
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    err_t err = ERR_OK;

    if (client->tcp_pcb != NULL) {
        tcp_arg(client->tcp_pcb, NULL);
        tcp_sent(client->tcp_pcb, NULL);
        tcp_recv(client->tcp_pcb, NULL);
        tcp_err(client->tcp_pcb, NULL);
        err = tcp_close(client->tcp_pcb);
        if (err != ERR_OK) {
            DEBUG_printf("tcp_client_close: tcp_close failed with error: %d\n",
                         err);
            tcp_abort(client->tcp_pcb);
            err = ERR_ABRT;
        }
        client->tcp_pcb = NULL;
        DEBUG_printf("TCP client closed");
    }
    client->connected = false;
    return err;
}
