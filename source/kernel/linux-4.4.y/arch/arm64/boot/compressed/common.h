#ifndef COMMONH
#define COMMONH

#include <types.h>

#define MEM_BASE_DDR			0
#define CONFIG_UNCOMP_ADDR		(MEM_BASE_DDR + 0x80000)
#define CONFIG_UNCMOP_MAX_SIZE		0x2000000

#define CFG_BOOT_PARAMS			(MEM_BASE_DDR + 0x0100)
#define CONFIG_BOOT_PARAMS_MAX_SIZE	(0x10000)
#define CONFIG_DTB_MAX_SIZE		(0x20000)

#define readl(_addr)            ({uint32 __v = *(volatile uint32 *)(_addr); asm("dsb sy"); __v;})
#define writel(_value, _addr)    ({asm("dsb sy"); *(volatile uint32 *)(_addr) = (uint32)(_value);})

#define __weak		__attribute__((weak))

extern void uart_putc(const char c);
extern void uart_puts(const char *s);
extern void uart_put_hex(u32 hex);

extern unsigned char data_begin[];
extern unsigned char data_end[];
extern char __page_table_start[], __page_table_end[];

int uncompress(unsigned char *uncompbuf, unsigned int *sz_uncompbuf,
	       const unsigned char *compbuf, unsigned int sz_compbuf);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *s, void *c, size_t n);

extern void uart_early_puts(u32 index);
extern void uart_early_put_hex(u32 index);
extern void debug(u32 index);
#endif /* COMMONH */
