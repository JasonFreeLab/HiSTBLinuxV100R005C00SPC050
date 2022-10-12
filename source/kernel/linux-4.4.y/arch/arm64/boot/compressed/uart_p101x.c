/* print to uart */
#include <common.h>
/*****************************************************************************/
#define REG_UART_BASE			0xF8B00000

#define UART_DR				0x00
#define UART_RSR			0x04
#define UART_FR				0x18
#define UART_FR_TXFF			(1 << 5)
#define UART_RF_RXFE			(1 << 4)

#define UART_IBRD			0x24
#define UART_FBRD			0x28
#define UART_LCR_H			0x2C
#define UART_LCR_H_8BIT			(3 << 5)
#define UART_LCR_H_FIFO_EN		(1 << 4)

#define UART_CR				0x30
#define UART_CR_EN			(1 << 0)
#define UART_CR_SEND_EN			(1 << 8)
#define UART_CR_REV_EN			(1 << 9)

static void pl01x_putc(char c)
{
	/* Wait until there is space in the FIFO */
	while (readl(REG_UART_BASE + UART_FR) & UART_FR_TXFF);

	/* Send the character */
	writel(c, REG_UART_BASE + UART_DR);
}

void uart_putc(const char c)
{
	if (c == '\n')
		pl01x_putc('\r');

	pl01x_putc(c);
}

void uart_puts(const char *s)
{
	while (*s != '\0') {
		uart_putc(*s++);
	}
}

void uart_put_hex(u32 hex)
{
	int i;
	char c;

	for (i = 28; i >= 0; i-=4) {
		c = (hex >> i) & 0x0F;
		if (c < 10)
			c += '0';
		else
			c += 'A' - 10;
		pl01x_putc(c);
	}
}
