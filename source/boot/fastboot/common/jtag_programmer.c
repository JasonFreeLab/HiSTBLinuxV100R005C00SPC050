#include <config.h>
#include <asm/io.h>
#include <stdarg.h>
#include <linux/string.h>
#include <common.h>

char *jtag_recv_buf = (char *)CONFIG_JTAG_RECV_BUF_ADDR;
char *jtag_send_buf = (char *)CONFIG_JTAG_SEND_BUF_ADDR;
static int send_index = 0;

unsigned int jtag_get_cmd_id(void)
{
	return 0x7F & (readl(REG_BASE_SCTL + REG_SC_GEN8)>>1);
}

int jtag_clear_cmd_set_flag(void)
{
	unsigned int v = readl(REG_BASE_SCTL + REG_SC_GEN8);
	v &= ~1;
	writel(v, REG_BASE_SCTL + REG_SC_GEN8);
	return 0;
}

int jtag_check_cmd_set_flag(void)
{
	unsigned int v = readl(REG_BASE_SCTL + REG_SC_GEN8);
	v &= 1;
	return v;
}

int jtag_set_cmd_result(unsigned int res)
{
	unsigned int v = readl(REG_BASE_SCTL + REG_SC_GEN31);
	v &= ~(0x7F << 1);
	v |= (res & 0x7F)<<1;
	writel(v, REG_BASE_SCTL + REG_SC_GEN31);
	return 0;
}

int jtag_set_cmd_done_flag(void)
{
	unsigned int v = readl(REG_BASE_SCTL + REG_SC_GEN31);
	v |= 1;
	writel(v, REG_BASE_SCTL + REG_SC_GEN31);
	return 0;
}

static void _jtag_put1char(const char c)
{
	jtag_send_buf[send_index] = c;
	send_index++;
}

void jtag_puts(const char *s)
{
	if (send_index + 1 >= CONFIG_JTAG_SEND_BUF_SIZE) {
		serial_puts("ERROR: JTAG send-buffer overflow");
		return;
	}

	while (*s) {
		if (*s == '\n')
			_jtag_put1char('\r');
		_jtag_put1char(*s++);
	}
}

void jtag_pr_tool(char *p)
{
	serial_puts(p);
}

void jtag_reset_send_buffer(void)
{
	send_index = 0;
	memset(jtag_send_buf, 0, CONFIG_JTAG_SEND_BUF_SIZE);
}

int is_jtag_mode(void)
{
	if (CONFIG_JTAG_MAGIC == readl(REG_BASE_SCTL + REG_SC_GEN37))
		return 1;
	return 0;
}

int jtag_init(void)
{
	memset(jtag_recv_buf, 0, CONFIG_JTAG_RECV_BUF_SIZE);
	jtag_clear_cmd_set_flag();
	jtag_set_cmd_result(0);
	jtag_set_cmd_done_flag();

    return 0;
}



