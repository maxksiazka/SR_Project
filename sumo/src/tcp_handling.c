#include "tcp_handling.h"
#include <string.h>
err_t tcp_echo_command(void* arg, struct tcp_pcb* client_pcb, err_t err) {
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL || client_pcb == NULL) {
        printf("tcp_echo_command: client is NULL\n");
        return ERR_VAL;
    }
    if (client->buffer_len<= 0){
        printf("tcp_echo_command: buffer length is zero or negative\n");
        return ERR_VAL;
    }
    printf("tcp_echo_command: echoing back %d bytes: %.*s\n",
           client->buffer_len, client->buffer_len,  client->buffer);
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
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL || client_pcb == NULL) {
        printf("tcp handle messange, client is NULL\n");
        return ERR_VAL;
    }
    printf("tcp_handle_message: received %d bytes: %.*s\n",
           client->buffer_len, client->buffer_len, client->buffer);
    err_t err_echo = tcp_echo_command(arg, client_pcb, err);
    if (err_echo != ERR_OK){
        printf("tcp_handle_message: tcp_echo_command failed with error: %d\n", err_echo);
        return err_echo;
    }


    return ERR_OK;
}
