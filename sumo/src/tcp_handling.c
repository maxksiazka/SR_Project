#include "tcp_handling.h"
#include "main.h"
#include <string.h>
err_t tcp_echo_command(void* arg, struct tcp_pcb* client_pcb, err_t err) {
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL || client_pcb == NULL) {
        DEBUG_printf("tcp_echo_command: client is NULL\n");
        return ERR_VAL;
    }

    if (client->buffer_len <= 0) {
        DEBUG_printf("tcp_echo_command: buffer length is zero or negative\n");
        return ERR_VAL;
    }

    DEBUG_printf("tcp_echo_command: echoing back %d bytes: %.*s\n",
                 client->buffer_len, client->buffer_len, client->buffer);

    err_t err_write = tcp_write(client_pcb, client->buffer, client->buffer_len,
                                TCP_WRITE_FLAG_COPY);

    if (err_write != ERR_OK) {
        DEBUG_printf("tcp_write failed with error: %d\n", err_write);
        return err_write;
    }

    err_t err_output = tcp_output(client_pcb);
    if (err_output != ERR_OK) {
        DEBUG_printf("tcp_output failed with error: %d\n", err_output);
        return err_output;
    }

    return ERR_OK;
}

err_t tcp_handle_message(void* arg, struct tcp_pcb* client_pcb, err_t err) {
    TCP_CLIENT_T* client = (TCP_CLIENT_T*)arg;
    if (client == NULL || client_pcb == NULL) {
        DEBUG_printf("tcp handle messange, client is NULL\n");
        return ERR_VAL;
    }
    DEBUG_printf("tcp_handle_message: received %d bytes: %.*s\n",
                 client->buffer_len, client->buffer_len, client->buffer);
    switch (
        tcp_command_interpreter((char*)client->buffer, client->buffer_len)) {
    case COMMAND_ECHO:
        DEBUG_printf("COMMAND_ECHO received\n");
        ECHO_MODE_ENABLED = !ECHO_MODE_ENABLED;
        DEBUG_printf("ECHO_MODE_ENABLED set to %d\n", ECHO_MODE_ENABLED);
        break;
    case COMMAND_STOP:
        DEBUG_printf("COMMAND_STOP received\n");
        pwm_set_motor_dir(MOTOR_DIR_STOP);
        break;
    case COMMAND_FORWARD:
        DEBUG_printf("COMMAND_FORWARD received\n");
        pwm_set_motor_dir(MOTOR_DIR_FORWARD);
        break;
    case COMMAND_BACKWARDS:
        DEBUG_printf("COMMAND_BACKWARDS received\n");
        pwm_set_motor_dir(MOTOR_DIR_BACKWARD);
        break;
    case COMMAND_LEFT:
        DEBUG_printf("COMMAND_LEFT received\n");
        pwm_set_motor_dir(MOTOR_DIR_LEFT);
        break;
    case COMMAND_RIGHT:
        DEBUG_printf("COMMAND_RIGHT received\n");
        pwm_set_motor_dir(MOTOR_DIR_RIGHT);
        break;
    case COMMAND_UNDEFINED:
        DEBUG_printf("COMMAND_UNDEFINED received\n");
        break;
    default:
        DEBUG_printf("HOW DID WE GET HERE\n");
        break;
    }
    if (ECHO_MODE_ENABLED) {
        err_t err_echo = tcp_echo_command(arg, client_pcb, err);
        if (err_echo != ERR_OK) {
            DEBUG_printf(
                "tcp_handle_message: tcp_echo_command failed with error: %d\n",
                err_echo);
            return err_echo;
        }
    }
    return ERR_OK;
}

COMMAND_TYPE tcp_command_interpreter(char* command_str, int32_t len) {
    DEBUG_printf("Interpreting command %s\n", command_str);
    for (int i = 0; i <= COMMAND_UNDEFINED; ++i) {
        if (strncmp(command_str, COMMAND_TYPE_STRINGS[i], len - 1) == 0) {
            DEBUG_printf("Command interpreted as %s\n",
                         COMMAND_TYPE_STRINGS[i]);
            return (COMMAND_TYPE)i;
        }
    }
    return COMMAND_UNDEFINED;
}
