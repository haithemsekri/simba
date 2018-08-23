/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018, Erik Moqvist
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

#ifndef __PIC32MM_H__
#define __PIC32MM_H__

/* 5. Flash. */
struct pic32mm_flash_t {
    uint32_t NVMCON;
    uint32_t RESERVED0[3];
    uint32_t NVMKEY;
    uint32_t RESERVED1[3];
    uint32_t NVMADDR;
    uint32_t RESERVED2[3];
    uint32_t NVMDATA0;
    uint32_t RESERVED3[3];
    uint32_t NVMDATA1;
    uint32_t RESERVED4[3];
    uint32_t NVMSRCADDR;
    uint32_t RESERVED5[3];
    uint32_t NVMPWP;
    uint32_t RESERVED6[3];
    uint32_t NVMBWP;
};

#define PIC32MM_FLASH_NVMCON_WR                       BIT(15)
#define PIC32MM_FLASH_NVMCON_WREN                     BIT(14)
#define PIC32MM_FLASH_NVMCON_WRERR                    BIT(13)
#define PIC32MM_FLASH_NVMCON_LVDERR                   BIT(12)
#define PIC32MM_FLASH_NVMCON_NVMOP_POS                (0)
#define PIC32MM_FLASH_NVMCON_NVMOP_MASK         \
    (0xf << PIC32MM_FLASH_NVMCON_NVMOP_POS)
#define PIC32MM_FLASH_NVMCON_NVMOP(value)               \
    BITFIELD_SET(PIC32MM_FLASH_NVMCON_NVMOP, value)
#define PIC32MM_FLASH_NVMCON_NVMOP_PROGRAM_ERASE        \
    PIC32MM_FLASH_NVMCON_NVMOP(7)
#define PIC32MM_FLASH_NVMCON_NVMOP_PAGE_ERASE   \
    PIC32MM_FLASH_NVMCON_NVMOP(4)
#define PIC32MM_FLASH_NVMCON_NVMOP_ROW_PROGRAM  \
    PIC32MM_FLASH_NVMCON_NVMOP(3)
#define PIC32MM_FLASH_NVMCON_NVMOP_DWORD_PROGRAM        \
    PIC32MM_FLASH_NVMCON_NVMOP(2)
#define PIC32MM_FLASH_NVMCON_NVMOP_NOP          \
    PIC32MM_FLASH_NVMCON_NVMOP(0)

/* 10. IO. */
struct pic32mm_port_t {
    uint32_t ANSEL;
    uint32_t RESERVED0[3];
    uint32_t TRIS;
    uint32_t RESERVED1[3];
    uint32_t PORT;
    uint32_t RESERVED2[3];
    uint32_t LAT;
    uint32_t RESERVED3[3];
    uint32_t ODC;
    uint32_t RESERVED4[3];
    uint32_t CNPU;
    uint32_t RESERVED5[3];
    uint32_t CNPD;
    uint32_t RESERVED6[3];
    uint32_t CNCON;
    uint32_t RESERVED7[3];
    uint32_t CNEN0;
    uint32_t RESERVED8[3];
    uint32_t CNSTAT;
    uint32_t RESERVED9[3];
    uint32_t CNEN1;
    uint32_t RESERVED10[3];
    uint32_t CNF;
};

struct pic32mm_pinsel_t {
    uint32_t RPCON;
    uint32_t RESERVED0[7];
    struct {
        uint32_t VALUE;
        uint32_t RESERVED0[3];
    } RPINR[12];
    uint32_t RESERVED1[12];
    struct {
        uint32_t VALUE;
        uint32_t RESERVED0[3];
    } RPOR[6];
};

/* 17. UART. */
struct pic32mm_uart_t {
    uint32_t MODE;
    uint32_t RESERVED0[3];
    uint32_t STA;
    uint32_t RESERVED1[3];
    uint32_t TXREG;
    uint32_t RESERVED2[3];
    uint32_t RXREG;
    uint32_t RESERVED3[3];
    uint32_t BRG;
};

#define PIC32MM_UART_MODE_SPLEN       BIT(23)
#define PIC32MM_UART_MODE_ACTIVE      BIT(22)
#define PIC32MM_UART_MODE_CLKSEL_POS  (17)
#define PIC32MM_UART_MODE_CLKSEL_MASK           \
    (0x3 << PIC32MM_UART_MODE_CLKSEL_POS)
#define PIC32MM_UART_MODE_CLKSEL(value)                 \
    BITFIELD_SET(PIC32MM_UART_MODE_CLKSEL, value)
#define PIC32MM_UART_MODE_CLKSEL_PBCLK          \
    PIC32MM_UART_MODE_CLKSEL_PBCLK(0)
#define PIC32MM_UART_MODE_CLKSEL_SYSCLK         \
    PIC32MM_UART_MODE_CLKSEL_PBCLK(1)
#define PIC32MM_UART_MODE_CLKSEL_FRC            \
    PIC32MM_UART_MODE_CLKSEL_PBCLK(2)
#define PIC32MM_UART_MODE_CLKSEL_REFO1          \
    PIC32MM_UART_MODE_CLKSEL_PBCLK(3)
#define PIC32MM_UART_MODE_OVFDIS      BIT(16)
#define PIC32MM_UART_MODE_ON          BIT(15)
#define PIC32MM_UART_MODE_SIDL        BIT(13)
#define PIC32MM_UART_MODE_IREN        BIT(12)
#define PIC32MM_UART_MODE_RTSMD       BIT(11)
#define PIC32MM_UART_MODE_UEN_POS  (8)
#define PIC32MM_UART_MODE_UEN_MASK              \
    (0x3 << PIC32MM_UART_MODE_UEN_POS)
#define PIC32MM_UART_MODE_UEN(value)            \
    BITFIELD_SET(PIC32MM_UART_MODE_UEN, value)
#define PIC32MM_UART_MODE_WAKE        BIT(7)
#define PIC32MM_UART_MODE_LPBACK      BIT(6)
#define PIC32MM_UART_MODE_ABAUD       BIT(5)
#define PIC32MM_UART_MODE_RXINV       BIT(4)
#define PIC32MM_UART_MODE_BRGH        BIT(3)
#define PIC32MM_UART_MODE_PDSEL_POS   (1)
#define PIC32MM_UART_MODE_PDSEL_MASK            \
    (0x3 << PIC32MM_UART_MODE_PDSEL_POS)
#define PIC32MM_UART_MODE_PDSEL(value)                  \
    BITFIELD_SET(PIC32MM_UART_MODE_PDSEL, value)
#define PIC32MM_UART_MODE_STSEL       BIT(0)

/* 26. Configuration bits. */
struct pic32mm_conf_t {
    uint32_t RESERVED0;
    uint32_t FDEVOPT;
    uint32_t FICD;
    uint32_t FPOR;
    uint32_t FWDT;
    uint32_t FOSCSEL;
    uint32_t FSEC;
};

/* Base addresses of peripherals. */
#define PIC32MM_UART1   ((volatile struct pic32mm_uart_t *)   0xbf801800ul)
#define PIC32MM_UART2   ((volatile struct pic32mm_uart_t *)   0xbf801900ul)
#define PIC32MM_UART3   ((volatile struct pic32mm_uart_t *)   0xbf802000ul)
#define PIC32MM_FLASH   ((volatile struct pic32mm_flash_t *)  0xbf802930ul)
#define PIC32MM_PINSEL  ((volatile struct pic32mm_pinsel_t *) 0xbf802a00ul)
#define PIC32MM_PORTA   ((volatile struct pic32mm_port_t *)   0xbf802bb0ul)
#define PIC32MM_PORTB   ((volatile struct pic32mm_port_t *)   0xbf802cb0ul)
#define PIC32MM_PORTC   ((volatile struct pic32mm_port_t *)   0xbf802db0ul)
#define PIC32MM_PORTD   ((volatile struct pic32mm_port_t *)   0xbf802eb0ul)
#define PIC32MM_TIMER1  ((volatile struct pic32mm_timer_t *)  0xbf808000ul)
#define PIC32MM_CONF    ((volatile struct pic32mm_conf_t *)   0xbfc017c0ul)

#define PIC32MM_RAM_ADDRESS                 0x00000000
#define PIC32MM_RAM_SIZE                    0x00004000
#define PIC32MM_RAM_END                     0x00008000
#define PIC32MM_FLASH_ADDRESS               0x1d000000
#define PIC32MM_FLASH_SIZE                  0x00040000
#define PIC32MM_FLASH_END                   0x1d040000
#define PIC32MM_SFRS_ADDRESS                0x1f800000
#define PIC32MM_SFRS_SIZE                   0x00010000
#define PIC32MM_SFRS_END                    0x1f810000
#define PIC32MM_BOOT_FLASH_ADDRESS          0x1fc00000
#define PIC32MM_BOOT_FLASH_SIZE             0x00001700
#define PIC32MM_BOOT_FLASH_END              0x1fc01700
#define PIC32MM_CONFIGURATION_BITS_ADDRESS  0x1fc01700
#define PIC32MM_CONFIGURATION_BITS_SIZE     0x00000100
#define PIC32MM_CONFIGURATION_BITS_END      0x1fc01800

/* Interrupt service routine. */
#define ISR(vector)                             \
    void isr_ ## vector(void)

#endif