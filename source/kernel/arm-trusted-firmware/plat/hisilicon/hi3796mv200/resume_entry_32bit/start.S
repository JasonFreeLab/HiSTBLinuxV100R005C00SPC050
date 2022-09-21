.balign 4

.globl expt_vec_entry
expt_vec_entry:
	b	atf_32bit_resume
	movs	pc, lr
	movs	pc, lr
	movs	pc, lr
	movs	pc, lr
	movs	pc, lr
	movs	pc, lr
	movs	pc, lr

.globl _expt_vec_entry
_expt_vec_entry:
	.word expt_vec_entry

.globl _atf_32bit_resume
_atf_32bit_resume:
	.word atf_32bit_resume

.globl atf_32bit_resume
atf_32bit_resume:
	isb
	mov	r2, pc
	sub	r2, r2, #12       /* Get the ddr address of relocate label */
	ldr	r1, _expt_vec_entry
	ldr	r0, _atf_32bit_resume
	sub	r1, r0, r1
	sub	r0, r2, r1       /* Get the ddr address where the resume_entry_32bit.bin loaded */

	/* Set VBAR */
	mcr	p15, 0, r0, c12, c0, 0
	/* Enable VBAR */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #1<<13
	mcr	p15, 0, r0, c1, c0, 0
	isb
	/* Enable Async exception */
	mrs	r0, cpsr
	bic	r0, #1<<8
	msr	cpsr_x, r0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	/*enable debug first */
#if 0
	mov	r2, #0
	ldr	r3, =0xf8a210ec
	str	r2, [r3]

	ldr	r3, =0xf8a210f0
	str	r2, [r3]

	ldr	r3, =0xf8a210f4
	str	r2, [r3]

	ldr	r3, =0xf8a210f8
	str	r2, [r3]

	ldr	r3, =0xf8a210fc
	str	r2, [r3]
#endif
	/* Load 64bit resume address from GEN30 */
	mov     r3, #0xf8000000
	ldr     r2, [r3, #0xf8]

	/* Set 64bit resume address to PERI_CPU_RVBARADDR */
	mov	r3, #0x0
	movt	r3, #0xf8a8
	str     r2, [r3, #0x34]

	/* Set all cpus booting-up in 64bit mode */
	ldr     r2, [r3, #0x30]
	orr     r2, r2, #0xF
	str     r2, [r3, #0x30]

	/* Set the arm generic timer freq */
	mov     r3, #0x0
	movt	r3, 0xf8bb
	mov     r2, #1
	str     r2, [r3, #0x20]
	movw    r2, #0x103
	str     r2, [r3]

	/* Warm reset */
	isb
	dsb
	mrc     p15, 0, r3, c12, c0, 2
	orr     r3, r3, #0x3
	mcr     p15, 0, r3, c12, c0, 2
	isb
1:	wfi
	b       1b


