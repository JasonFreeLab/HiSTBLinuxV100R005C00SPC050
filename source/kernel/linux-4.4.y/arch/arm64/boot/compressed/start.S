#define STACK_TOP			(0x2000000 - 0x80)

#include <linkage.h>
#include <macro.h>

.globl _start
_start:
	ldr	x1, =STACK_TOP
	mov	sp, x1
	mov	x21,x0
	bl	enable_caches
	mov	x0, x21
	adr	x1, _start   		/*load address*/
	adr	x2, __text_start
	adr	x3, __text_end
	sub	x4, x3, x2		/* uImage offset = __text_end - __text_start*/
	add	x1, x1, x4		/* uImage start address = _start + uImage offset*/
	bl	main_entry

