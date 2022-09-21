#include "tee_external_api.h"
#include <stdarg.h>
#include "sre_syscall.h"
#include <libhwsecurec/securec.h>
#include <tee_symbol.h>

extern void *asm_memmove(void *dest, const void *src, unsigned int n);
extern void *asm_memcpy(void *dest, const void *src, unsigned int n);

void ASM_MemMove(void* dest, void* src, unsigned int size)
{
    asm_memmove(dest, src, size);
}
void ASM_MemCopy(void* dest, void* src, unsigned int size)
{
    asm_memcpy(dest, src, size);
}

static void puts(const char *s)
{
	while (*s) {
		__console_putc (*s++);
	}
}

void std_printf_func(const char *fmt, ...)
{
	#define CONFIG_SYS_PBSIZE	512
	va_list args;
	char printbuffer[CONFIG_SYS_PBSIZE];

	va_start(args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	vsnprintf_s(printbuffer, sizeof(printbuffer), sizeof(printbuffer), fmt, args);

	va_end(args);

	/* Print the string */
	puts(printbuffer);
}

EXPORT_SYMBOL(std_printf_func);
EXPORT_SYMBOL(ASM_MemMove);
EXPORT_SYMBOL(ASM_MemCopy);

/* for memcpy in TA */
EXPORT_SYMBOL(asm_memmove);
EXPORT_SYMBOL(asm_memcpy);