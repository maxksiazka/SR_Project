#include "tcp_handling.h"
err_t tcp_echo_command(void* arg, struct tcp_pcb* client_pcb, err_t err) {
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
    if (client == NULL) {
        printf("tcp_echo_command: client is NULL\n");
        return ERR_VAL;
    }
    err_t err_write = tcp_write(client_pcb, client->buffer, client->buffer_len,
                                TCP_WRITE_FLAG_COPY);
    if (err_write != ERR_OK) {
        printf("tcp_write failed with error: %d\n", err_write);
        return err_write;
    }
    err_t err_output = tcp_output(client_pcb);
    if (err_output != ERR_OK) {
        printf("tcp_output failed with error: %d\n", err_output);
        return err_output;
    }

    return ERR_OK;
}

err_t tcp_handle_message(void* arg, struct tcp_pcb* client_pcb, err_t err){
    TCP_CLIENT_T_* client = (TCP_CLIENT_T_*)arg;
    if (client == NULL){
        printf("tcp handle messange, client is NULL\n");
        return ERR_VAL;

    }

    return ERR_OK;
}
