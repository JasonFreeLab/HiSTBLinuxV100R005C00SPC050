#include <common.h>

typedef void (*KERNEL_ENTRY)(unsigned long fdt);

int main_entry(char *fdt, char *data_start)
{
	KERNEL_ENTRY entry = (KERNEL_ENTRY)CONFIG_UNCOMP_ADDR;
	char *fdt_dst = (char *)(CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE);

	uart_early_puts(0);

	memmove(entry, data_start, data_end - data_begin);

	uart_early_puts(1);

	/*
	   The arm64 kernel require that the device tree blob (dtb) must be placed
	   on an 8-byte boundary within the first 512 megabytes from the start of
	   the kernel image and must not cross a 2-megabyte boundary. This is to
	   allow the kernel to map the blob using a single section mapping in the
	   initial page tables. To simplify the implemention, we fix the dtb location
	   to the tail of TAG params area.
	 */
	uart_early_puts(2);
	memmove(fdt_dst, fdt, CONFIG_DTB_MAX_SIZE);
	uart_early_puts(1);

	uart_early_puts(4);
	entry((unsigned long)fdt_dst);

	return 0;
}
