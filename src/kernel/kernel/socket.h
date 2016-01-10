/**
 * @file kernel/socket.h
 * @version 0.1.0
 *
 * @section License
 * Copyright (C) 2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERSOCKTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#ifndef __KERNEL_SOCKET_H__
#define __KERNEL_SOCKET_H__

#include "simba.h"

/** Internet address family. */
#define AF_INET  2

/** TCP socket type. */
#define SOCKET_TYPE_STREAM    1

/** UDP socket type. */
#define SOCKET_TYPE_DGRAM     2

struct socket_addr_t {
    /** IPv4 address. */
    uint32_t ip;
    /** Port. */
    uint16_t port;
};

struct socket_t {
    struct chan_t base;
    void *pcb_p;
};

/**
 * Initialize given socket with given domain, type and protocol.
 *
 * @rst
 * .. code-block:: c
 *
 *    // The function calls needed to setup an UDP socket and send a
 *    // packet. local_addr, remote_addr and buf should be initialized
 *    // before to this code.
 *    socket_init(&udp, AF_INET, SOCKET_DGRAM);
 *    socket_bind(&udp, &local_addr, sizeof(local_addr));
 *    socket_connect(&udp, &remote_addr, sizeof(remote_addr));
 *    socket_send(&udp, buf, sizeof(buf));
 *    socket_close(&udp);
 *
 *    // The function calls needed to setup an TCP socket and send a
 *    // packet. local_addr, remote_addr and buf should be initialized
 *    // before to this code.
 *    socket_init(&tcp, AF_INET, SOCKET_STREAM);
 *    socket_bind(&tcp, &local_addr, sizeof(local_addr));
 *    socket_connect(&tcp, &remote_addr, sizeof(remote_addr));
 *    socket_send(&tcp, buf, sizeof(buf));
 *    socket_close(&tcp);
 * @endrst
 *
 * @param[out] self_p Socket to initialize.
 * @param[in] domain AF_INET is the only supported domain. It is used
 *                   by internet sockets.
 * @param[in] type Socket type one of SOCK_TYPE_DGRAM (UDP)
 *                 and SOCK_TYPE_STREAM (TCP).
 * @param[in] protocol Unused.
 *
 * @return zero(0) or negative error code.
 */
int socket_init(struct socket_t *self_p,
                int domain,
                int type,
                int protocol);

/**
 * Close given socket.
 *
 * @param[in] self_p Socket to disconnect.
 *
 * @return zero(0) or negative error code.
 */
int socket_close(struct socket_t *self_p);

/**
 * Bind given local address to given socket.
 * 
 * @param[in] self_p Socket.
 * @param[in] local_addr_p Local address.
 * @param[in] addrlen Local address length.
 * 
 * @return zero(0) or negative error code.
 */
int socket_bind(struct socket_t *self_p,
                const struct socket_addr_t *local_addr_p,
                size_t addrlen);

/**
 * Listen for conntctions. Only used by TCP sockets.
 * 
 * @param[in] self_p Socket.
 * @param[in] backlog Unused.
 * 
 * @return zero(0) or negative error code.
 */
int socket_listen(struct socket_t *self_p, int backlog);

/**
 * Connect to given remote address. Connecting a UDP socket sets the
 * default remote address for outgoing datagrams. For TCP a three-way
 * handshake with the remote is initiated.
 * 
 * @param[in] self_p Socket.
 * @param[in] remote_addr_p Remote address.
 * @param[in] addrlen Remote address length.
 * 
 * @return zero(0) or negative error code.
 */
int socket_connect(struct socket_t *self_p,
                   const struct socket_addr_t *remote_addr_p,
                   size_t addrlen);

/**
 * Accept a client connect attempt.
 * 
 * @param[in] self_p Socket.
 * @param[out] accepted_p New client socket.
 * @param[out] remote_addr_p Remote address.
 * @param[out] addrlen_p Remote address length.
 * 
 * @return zero(0) or negative error code.
 */
int socket_accept(struct socket_t *self_p,
                  struct socket_t *accepted_p,
                  struct socket_addr_t *remote_addr_p,
                  size_t *addrlen_p);

/**
 * Write data to given socket.
 * 
 * @param[in] self_p Socket.
 * @param[in] buf_p Buffer to send.
 * @param[in] size Size of buffer to send.
 * @param[in] flags Unused.
 * @param[in] remote_addr_p Remote address to send the data to.
 * @param[in] addrlen Length of remote_addr.
 * 
 * @return Number of sent bytes or negative error code.
 */
ssize_t socket_sendto(struct socket_t *self_p,
                      const void *buf_p,
                      size_t size,
                      int flags,
                      const struct socket_addr_t *remote_addr_p,
                      size_t addrlen);

/**
 * Read data from given socket.
 * 
 * @param[in] self_p Socket.
 * @param[in] buf_p Buffer to read into.
 * @param[in] size Size of buffer to read.
 * @param[in] flags Unused.
 * @param[in] remote_addr_p Remote address to receive data from.
 * @param[in] addrlen Length of remote_addr.
 * 
 * @return Number of received bytes or negative error code.
 */
ssize_t socket_recvfrom(struct socket_t *self_p,
                        void *buf_p,
                        size_t size,
                        int flags,
                        struct socket_addr_t *remote_addr_p,
                        size_t addrlen);

#endif
