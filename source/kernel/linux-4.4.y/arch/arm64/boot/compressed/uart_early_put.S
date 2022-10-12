#include <linkage.h>
#include <macro.h>

##################################################################
#  x0 -- string index from index0
.align	4
ENTRY(uart_early_put_hex)
	mov	x28, lr
	bl	uart_put_hex
	ret	x28

#ifdef DEBUG_STEP
##################################################################
#  x0 -- string index from index0
.align	4
ENTRY(debug)
	mov	x28, lr
	mov	x22, x0
	adr	x0, str1
	bl	uart_puts
	mov	x0, x22
	bl	uart_put_hex
	adr	x0, str2
	bl	uart_puts
	ret	x28

str1:
	.ascii	"step \0"
	
str2:
	.ascii	" \n\0"
#else
.align	4
ENTRY(debug)
	ret	lr
#endif			
##################################################################
#  x0 -- string index from index0
.align	4
ENTRY(uart_early_puts)
	mov	x28, lr
	adr	x1, STR
	add	x0, x1, x0, lsl #2
	ldr	w2, [x0]
	add	x0, x1, x2
	bl	uart_puts
	ret	x28
.align	4
STR:
	.word	STR0 - STR 
	.word	STR1 - STR 
	.word	STR2 - STR
	.word	STR3 - STR
	.word	STR4 - STR
	.word	STR5 - STR
	.word	STR6 - STR
	.word	STR7 - STR
	.word	STR8 - STR
	.word	STR9 - STR
	.word	STR10 - STR
	.word	STR11 - STR

.align	4
STR0:
	.ascii	"\r\nMove Image...\0"
	
.align	4
STR1:
	.ascii	"OK\n\0"
	
.align	4
STR2:
	.ascii	"\r\nMove dtb...\0"

.align	4
STR3:
	.ascii	"\r\n\r\nInvalid FDT!\n\0"
	
.align	4
STR4:
	.ascii	"Enter ARM64 kernel\n\0"

.align	4
STR5:
	.ascii	"System painc: Insufficient RAM for page table, Please increase the size in get_page_table_size()\n\0"

.align	4
STR6:
	.ascii	"System painc: PTE is not a block. Some driver code wants to modify dcache settings for an range not covered in mem_map\n\0"
	
.align	4
STR7:
	.ascii	"pte not found\n\0"
	
.align	4
STR8:
	.ascii	"Page table pointer not setup.\n\0"
	
.align	4
STR9:
	.ascii	"flushing dcache returns nozero\n\0"
	
.align	4
STR10:
	.ascii	"System painc: PTE should be a table\n\0"
	
.align	4
STR11:
	.ascii	"Emergency page table not setup.\n\0"