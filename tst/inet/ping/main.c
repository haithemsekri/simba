/**
 * @file main.c
 * @version 6.0.0
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"

#define BUFFER_SIZE 128

extern void socket_stub_input(void *buf_p, size_t size);
extern void socket_stub_output(void *buf_p, size_t size);

static char qoutbuf[BUFFER_SIZE];
static QUEUE_INIT_DECL(qout, qoutbuf, sizeof(qoutbuf));

static int read_until(char *buf_p, const char *pattern)
{
    char c;
    size_t length = 0;
    size_t pattern_length = strlen(pattern);

    while (length < BUFFER_SIZE - 1) {
        chan_read(&qout, &c, sizeof(c));
#if defined(ARCH_LINUX)
        std_printf(FSTR("%c"), c);
#endif
        *buf_p++ = c;
        length++;
        *buf_p = '\0';

        /* Compare to pattern. */
        if (length >= pattern_length) {
            if (!strcmp(&buf_p[-pattern_length], pattern)) {
                return (1);
            }
        }
    }

    return (0);
}

static int test_host_by_ip_address(struct harness_t *harness_p)
{
    struct inet_ip_addr_t address;
    struct time_t round_trip_time;
    uint8_t request[8];
    uint8_t reply[28];

    /* Prepare the socket stub with the reply packet. The first 20
       bytes in the reply are the IP header. */
    reply[20] = 0;
    reply[21] = 0;
    reply[22] = 0xff;
    reply[23] = 0xfe;
    reply[24] = 0;
    reply[25] = 0;
    reply[26] = 0;
    reply[27] = 1;
    socket_stub_input(reply, sizeof(reply));

    /* Perform the ping. */
    address.number = 0x1;
    BTASSERT(ping_host_by_ip_address(&address, NULL, &round_trip_time) == 0);

    /* Check the request send by the ping module. */
    socket_stub_output(request, sizeof(request));
    BTASSERT(request[0] == 8);
    BTASSERT(request[1] == 0);
    BTASSERT(request[2] == 0xf7);
    BTASSERT(request[3] == 0xfe);
    BTASSERT(request[4] == 0);
    BTASSERT(request[5] == 0);
    BTASSERT(request[6] == 0);
    BTASSERT(request[7] == 1);

    std_printf(FSTR("round trip time: %lu s %lu ns\r\n"),
               round_trip_time.seconds,
               round_trip_time.nanoseconds);

    return (0);
}

static int test_bad_reply_crc(struct harness_t *harness_p)
{
    struct inet_ip_addr_t address;
    struct time_t round_trip_time;
    uint8_t request[8];
    uint8_t reply[28];

    /* Prepare the socket stub with the reply packet. The first 20
       bytes in the reply are the IP header. */
    reply[20] = 0;
    reply[21] = 0;
    reply[22] = 0xfe;
    reply[23] = 0xff;
    reply[24] = 0;
    reply[25] = 0;
    reply[26] = 0;
    reply[27] = 1;
    socket_stub_input(reply, sizeof(reply));

    /* Perform the ping. */
    address.number = 0x1;
    BTASSERT(ping_host_by_ip_address(&address, NULL, &round_trip_time) == -1);

    /* Check the request send by the ping module. */
    socket_stub_output(request, sizeof(request));
    BTASSERT(request[0] == 8);
    BTASSERT(request[1] == 0);
    BTASSERT(request[2] == 0xf7);
    BTASSERT(request[3] == 0xfe);
    BTASSERT(request[4] == 0);
    BTASSERT(request[5] == 0);
    BTASSERT(request[6] == 0);
    BTASSERT(request[7] == 1);

    return (0);
}

static int test_cmd_ping(struct harness_t *harness_p)
{
    uint8_t request[8];
    uint8_t reply[28];
    char buf[128];

    /* Prepare the socket stub with the reply packet. The first 20
       bytes in the reply are the IP header. */
    reply[20] = 0;
    reply[21] = 0;
    reply[22] = 0xff;
    reply[23] = 0xfe;
    reply[24] = 0;
    reply[25] = 0;
    reply[26] = 0;
    reply[27] = 1;
    socket_stub_input(reply, sizeof(reply));

    /* Perform the ping. */
    strcpy(buf, "inet/ping/ping 1.1.1.1\r\n");
    BTASSERT(fs_call(buf, NULL, &qout, NULL) == 0);
    read_until(buf, "Successfully pinged '1.1.1.1' in 0 ms.\r\n");
    
    /* Check the request send by the ping module. */
    socket_stub_output(request, sizeof(request));
    BTASSERT(request[0] == 8);
    BTASSERT(request[1] == 0);
    BTASSERT(request[2] == 0xf7);
    BTASSERT(request[3] == 0xfe);
    BTASSERT(request[4] == 0);
    BTASSERT(request[5] == 0);
    BTASSERT(request[6] == 0);
    BTASSERT(request[7] == 1);
        
    return (0);
}

static int test_cmd_ping_bad_reply(struct harness_t *harness_p)
{
    uint8_t reply[28];
    char buf[128];

    /* Prepare the socket stub with a bad reply packet. The first 20
       bytes in the reply are the IP header. */
    reply[20] = 0;
    reply[21] = 0;
    reply[22] = 0xff;
    reply[23] = 0xfe;
    reply[24] = 0;
    reply[25] = 0;
    reply[26] = 0;
    reply[27] = 2;
    socket_stub_input(reply, sizeof(reply));

    /* Perform the ping. */
    strcpy(buf, "inet/ping/ping 1.1.1.1\r\n");
    BTASSERT(fs_call(buf, NULL, &qout, NULL) == 0);
    read_until(buf, "Failed to ping '1.1.1.1'.\r\n");
        
    return (0);
}

static int test_cmd_ping_bad_input(struct harness_t *harness_p)
{
    char buf[128];
    
    /* Too few arguemnts. */
    strcpy(buf, "inet/ping/ping\r\n");
    BTASSERT(fs_call(buf, NULL, &qout, NULL) == -1);
    read_until(buf, "Usage: inet/ping/ping <remote host>\r\n");

    /* Bad ip address. */
    strcpy(buf, "inet/ping/ping a.b.c.d\r\n");
    BTASSERT(fs_call(buf, NULL, &qout, NULL) == -1);
    read_until(buf, "Bad ip address 'a.b.c.d'.\r\n");
        
    return (0);
}

int main()
{
    struct harness_t harness;
    struct harness_testcase_t harness_testcases[] = {
        { test_host_by_ip_address, "test_host_by_ip_address" },
        { test_bad_reply_crc, "test_bad_reply_crc" },
        { test_cmd_ping, "test_cmd_ping" },
        { test_cmd_ping_bad_reply, "test_cmd_ping_bad_reply" },
        { test_cmd_ping_bad_input, "test_cmd_ping_bad_input" },
        { NULL, NULL }
    };

    sys_start();
    ping_module_init();

    harness_init(&harness);
    harness_run(&harness, harness_testcases);

    return (0);
}