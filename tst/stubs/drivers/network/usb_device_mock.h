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

#ifndef __USB_DEVICE_MOCK_H__
#define __USB_DEVICE_MOCK_H__

#include "simba.h"

int mock_write_usb_device_module_init(int res);

int mock_write_usb_device_init(struct usb_device_t *dev_p,
                               struct usb_device_driver_base_t **drivers_pp,
                               int drivers_max,
                               FAR const union usb_descriptor_t **descriptors_pp,
                               int res);

int mock_write_usb_device_start(int res);

int mock_write_usb_device_stop(int res);

int mock_write_usb_device_write(int endpoint,
                                const void *buf_p,
                                size_t size,
                                ssize_t res);

int mock_write_usb_device_read_isr(int endpoint,
                                   void *buf_p,
                                   size_t size,
                                   ssize_t res);

int mock_write_usb_device_write_isr(int endpoint,
                                    const void *buf_p,
                                    size_t size,
                                    ssize_t res);

#endif
