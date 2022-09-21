/*
 * (C) Copyright 2000
 * Rob Taylor, Flying Pig Systems. robt@flyingpig.com.
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* Simple U-Boot driver for the PrimeCell PL010/PL011 UARTs */

#include <common.h>
#include <watchdog.h>
#include <asm/io.h>
#include <serial.h>
#include <linux/compiler.h>
#include "serial_pl01x.h"
#include <jtag_prg.h>
/*
 * Integrator AP has two UARTs, we use the first one, at 38400-8-N-1
 * Integrator CP has two UARTs, use the first one, at 38400-8-N-1
 * Versatile PB has four UARTs.
 */
#define CONSOLE_PORT  CONFIG_CONS_INDEX
#define CONSOLE_PORT1 1
static volatile unsigned char *const port[] = CONFIG_PL01x_PORTS;
#define NUM_PORTS (sizeof(port)/sizeof(port[0]))

unsigned int baudrate = CONFIG_BAUDRATE;
DECLARE_GLOBAL_DATA_PTR;

static struct pl01x_regs *pl01x_get_regs(int portnum)
{
	return (struct pl01x_regs *) port[portnum];
}

#ifdef CONFIG_USB_DEVICE
extern int usb_out_open;
#endif

#ifdef CONFIG_PL010_SERIAL

static int pl01x_init(void)
{
	struct pl01x_regs *regs = pl01x_get_regs(CONSOLE_PORT);
	unsigned int divisor;

	/* First, disable everything */
	writel(0, &regs->pl010_cr);

	/* Set baud rate */
	switch (baudrate) {
	case 9600:
		divisor = UART_PL010_BAUD_9600;
		break;

	case 19200:
		divisor = UART_PL010_BAUD_9600;
		break;

	case 38400:
		divisor = UART_PL010_BAUD_38400;
		break;

	case 57600:
		divisor = UART_PL010_BAUD_57600;
		break;

	case 115200:
		divisor = UART_PL010_BAUD_115200;
		break;

	default:
		divisor = UART_PL010_BAUD_38400;
	}

	writel((divisor & 0xf00) >> 8, &regs->pl010_lcrm);
	writel(divisor & 0xff, &regs->pl010_lcrl);

	/* Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled */
	writel(UART_PL010_LCRH_WLEN_8 | UART_PL010_LCRH_FEN, &regs->pl010_lcrh);

	/* Finally, enable the UART */
	writel(UART_PL010_CR_UARTEN, &regs->pl010_cr);

	return 0;
}

#endif /* CONFIG_PL010_SERIAL */

#ifdef CONFIG_PL011_SERIAL

static int pl01x_init(int portnum)
{
	struct pl01x_regs *regs = pl01x_get_regs(portnum);
	unsigned int temp;
	unsigned int divider;
	unsigned int remainder;
	unsigned int fraction;

	/* First, disable everything */
	writel(0, &regs->pl011_cr);

	/*
	 * Set baud rate
	 *
	 * IBRD = UART_CLK / (16 * BAUD_RATE)
	 * FBRD = RND((64 * MOD(UART_CLK,(16 * BAUD_RATE))) / (16 * BAUD_RATE))
	 */
	temp = 16 * baudrate;
	divider = CONFIG_PL011_CLOCK / temp;
	remainder = CONFIG_PL011_CLOCK % temp;
	temp = (8 * remainder) / baudrate;
	fraction = (temp >> 1) + (temp & 1);

	writel(divider, &regs->pl011_ibrd);
	writel(fraction, &regs->pl011_fbrd);

	/* Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled */
	writel(UART_PL011_LCRH_WLEN_8 | UART_PL011_LCRH_FEN,
	       &regs->pl011_lcrh);

	/* Finally, enable the UART */
	writel(UART_PL011_CR_UARTEN | UART_PL011_CR_TXE | UART_PL011_CR_RXE,
	       &regs->pl011_cr);

	return 0;
}

static int pl01x_serial0_init(void)
{
	return pl01x_init(CONSOLE_PORT);
}

#ifdef CONFIG_SERIAL_MULTI
static int pl01x_serial1_init(void)
{
	return pl01x_init(CONSOLE_PORT1);
}
#endif
#endif /* CONFIG_PL011_SERIAL */

#ifndef CONFIG_SERIAL_NO_DISPLAY
static void pl01x_putc (int portnum, char c)
{
	struct pl01x_regs *regs = pl01x_get_regs(portnum);

	/* Wait until there is space in the FIFO */
	while (readl(&regs->fr) & UART_PL01x_FR_TXFF)
		WATCHDOG_RESET();

	/* Send the character */
	writel(c, &regs->dr);
}

void serial_putc_raw(const char c)
{
	pl01x_putc (CONSOLE_PORT, c);
}


static int pl01x_getc (int portnum)
{
	struct pl01x_regs *regs = pl01x_get_regs(portnum);
	unsigned int data;

	/* Wait until there is data in the FIFO */
	while (readl(&regs->fr) & UART_PL01x_FR_RXFE)
		WATCHDOG_RESET();

	data = readl(&regs->dr);

	/* Check for an error flag */
	if (data & 0xFFFFFF00) {
		/* Clear the error */
		writel(0xFFFFFFFF, &regs->ecr);
		return -1;
	}

	return (int) data;
}

static int pl01x_tstc (int portnum)
{
	struct pl01x_regs *regs = pl01x_get_regs(portnum);

	WATCHDOG_RESET();
	return !(readl(&regs->fr) & UART_PL01x_FR_RXFE);
}


static void pl01x_setbrg(int portnum)
{
	struct pl01x_regs *regs = pl01x_get_regs(portnum);

	baudrate = gd->baudrate;
	/*
	 * Flush FIFO and wait for non-busy before changing baudrate to avoid
	 * crap in console
	 */
	while (!(readl(&regs->fr) & UART_PL01x_FR_TXFE))
		WATCHDOG_RESET();
	while (readl(&regs->fr) & UART_PL01x_FR_BUSY)
		WATCHDOG_RESET();
	pl01x_init(portnum);
}
#else
static void pl01x_putc (int portnum, char c)
{}

static int pl01x_getc (int portnum)
{
	return 0;
}

static int pl01x_tstc (int portnum)
{
	return 0;
}

void serial_putc_raw(const char c)
{}

static void pl01x_setbrg(int portnum)
{}
#endif

static void pl01x_serial0_putc(const char c)
{
	if (c == '\n')
		pl01x_putc (CONSOLE_PORT, '\r');

	pl01x_putc (CONSOLE_PORT, c);
}

static void pl01x_serial0_puts(const char *s)
{
#ifdef CONFIG_USB_DEVICE
	if(usb_out_open)
		tx_status(s);
#endif
	while (*s) {
		if (*s == '\n')
			pl01x_putc (CONSOLE_PORT, '\r');
		pl01x_putc (CONSOLE_PORT, *s++);
	}
}

static int pl01x_serial0_getc(void)
{
	return pl01x_getc (CONSOLE_PORT);
}

static int pl01x_serial0_tstc(void)
{
	return pl01x_tstc (CONSOLE_PORT);
}

static void pl01x_serial0_setbrg(void)
{
	pl01x_setbrg(CONSOLE_PORT);
}

#ifdef CONFIG_SERIAL_MULTI
static void pl01x_serial1_putc(const char c)
{
	if (c == '\n')
		pl01x_putc (CONSOLE_PORT1, '\r');

	pl01x_putc (CONSOLE_PORT1, c);
}

static int pl01x_serial1_getc(void)
{
	return pl01x_getc (CONSOLE_PORT1);
}

static int pl01x_serial1_tstc(void)
{
	return pl01x_tstc (CONSOLE_PORT1);
}

static void pl01x_serial1_puts(const char *s)
{
	while (*s) {
		if (*s == '\n')
			pl01x_putc (CONSOLE_PORT1, '\r');
		pl01x_putc (CONSOLE_PORT1, *s++);
	}
}
static void pl01x_serial1_setbrg(void)
{
	pl01x_setbrg(CONSOLE_PORT1);
}

static struct serial_device pl01x_serial0 = {
	.name	= "serial0",
	.start	= pl01x_serial0_init,
	.stop	= NULL,
	.setbrg	= pl01x_serial0_setbrg,
	.putc	= pl01x_serial0_putc,
	.puts	= pl01x_serial0_puts,
	.getc	= pl01x_serial0_getc,
	.tstc	= pl01x_serial0_tstc,
};

static struct serial_device pl01x_serial1 = {
	.name	= "serial1",
	.start	= pl01x_serial1_init,
	.stop	= NULL,
	.setbrg	= pl01x_serial1_setbrg,
	.putc	= pl01x_serial1_putc,
	.puts	= pl01x_serial1_puts,
	.getc	= pl01x_serial1_getc,
	.tstc	= pl01x_serial1_tstc,
};
void pl01x_serial0_initialize(void)
{
	serial_register(&pl01x_serial0);
}

void pl01x_serial1_initialize(void)
{
	serial_register(&pl01x_serial1);
}

__weak struct serial_device *default_serial_console(void)
{
	return &pl01x_serial0;
}
#else
int serial_init(void)
{
	return pl01x_serial0_init();
}

void serial_setbrg(void)
{
	pl01x_serial0_setbrg();
}

void serial_putc(const char c)
{
	pl01x_serial0_putc(c);
}

void serial_puts(const char *s)
{
	pl01x_serial0_puts(s);
#ifdef CONFIG_JTAG_PRG_SUPPORT
	if (is_jtag_mode())
		jtag_puts(s);
#endif
}

int serial_getc(void)
{
	return pl01x_serial0_getc();
}

int serial_tstc(void)
{
	return pl01x_serial0_tstc();
}
#endif
