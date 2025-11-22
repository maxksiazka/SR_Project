#ifndef LWIPOPTS_H_
#define LWIPOPTS_H_

/**
 * @file lwipopts.h
 * @brief Custom lwIP configuration options.
 * This file contains settings for tuning the TCP/IP stack behavior. 
 * Sets polling etc.
 */
#define NO_SYS 1

#define LWIP_IPV4 1
#define LWIP_TCP 1
#define LWIP_DNS 0 // we will be connecting directly to server IP
#define LWIP_TIMEVAL_PRIVATE 0
#define LWIP_ERRNO_STDINCLUDE 0 // for whatever reason lwip has problems with standard errno.h
#define LWIP_PROVIDE_ERRNO 1

#define TCP_MSS 1460 // a lot more than we need, maximum value possible for IPv4
#define TCP_WND (8 * TCP_MSS)
#define MEMP_NUM_TCP_PCB 5 // no reason for 5, need to set it

#define LWIP_NO_HEAP 1
#define MEM_SIZE 16000 // should be more than enough for lwip

#endif // LWIPOPTS_H_
