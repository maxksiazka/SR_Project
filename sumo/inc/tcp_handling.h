#ifndef TCP_HANDLING_H_
#define TCP_HANDLING_H_
#include <lwip/tcp.h>
#include "tcp_api_implementation.h"

/**
 * \brief A function used to echo the data currently in buffer back to the sender
 *
 * \param[in,out] arg Data pointer to tcp_client (should be TCP_CLIENT_T_*)
 * \param[in,out] client_pcb TCP protocol control block, should be the one inside arg
 * \param[in] err Current error status
 * \return ERR_OK on success, 
 */
err_t tcp_echo_commmand(void *arg, struct tcp_pcb* client_pcb,  err_t err);

err_t tcp_handle_message(void* arg, struct tcp_pcb* client_pcb, err_t err);

#endif // TCP_HANDLING_H_
