/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2018, Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"

static int test_insert(void)
{
    uint32_t dst;
    uint32_t src;
    int pos;
    int size;

    /* Insert a one at LSB. */
    dst = 0xffffffff;
    src = 0x0;
    pos = 0;
    size = 1;
    BTASSERT(bits_insert_32(dst, pos, size, src) == 0xfffffffe);

    /* Insert a one at MSB. */
    dst = 0xffffffff;
    src = 0x0;
    pos = 31;
    size = 1;
    BTASSERT(bits_insert_32(dst, pos, size, src) == 0x7fffffff);

    /* Insert in the middle. */
    dst = 0xffffffff;
    src = 0x34;
    pos = 17;
    size = 5;
    BTASSERT(bits_insert_32(dst, pos, size, src) == 0xffe9ffff);

    /* Insert the maximum 31 bits. */
    dst = 0xffffffff;
    src = 0x12345678;
    pos = 0;
    size = 31;
    BTASSERT(bits_insert_32(dst, pos, size, src) == 0x92345678);

    return (0);
}

static int test_mask(void)
{
    BTASSERT(bits_mask_32(1) == 0x1);
    BTASSERT(bits_mask_32(5) == 0x1f);

    return (0);
}

static int test_reverse_8(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        BTASSERT(bits_reverse_8(1 << i) == (0x80 >> i));
    }

    return (0);
}

static int test_reverse_16(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        BTASSERT(bits_reverse_16(1 << i) == (0x8000 >> i));
    }

    return (0);
}

static int test_reverse_32(void)
{
    int i;

    for (i = 0; i < 32; i++) {
        BTASSERT(bits_reverse_32(1 << i) == (0x80000000 >> i));
    }

    return (0);
}

int main()
{
    struct harness_testcase_t testcases[] = {
        { test_insert, "test_insert" },
        { test_mask, "test_mask" },
        { test_reverse_8, "test_reverse_8" },
        { test_reverse_16, "test_reverse_16" },
        { test_reverse_32, "test_reverse_32" },
        { NULL, NULL }
    };

    sys_start();

    harness_run(testcases);

    return (0);
}
