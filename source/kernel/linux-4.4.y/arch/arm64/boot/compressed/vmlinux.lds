OUTPUT_ARCH(aarch64)
ENTRY(_start)

SECTIONS
{
	. = 0x00000000;

	.text :
	{
		__text_start = .;
		start.o (.text)
		*(.text)
	}

	__text_end = .;

       .image : { *(.image) }

	__data_start = .;
	. = ALIGN(4);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(4);
	.data : { *(.data)  }

	__data_end = .;

	. = ALIGN(4);
	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;

	. = ALIGN(0x100000);
	__page_table_start = .;
	. = . + 0x4000; /* 16K */
	__page_table_end = .;
}

