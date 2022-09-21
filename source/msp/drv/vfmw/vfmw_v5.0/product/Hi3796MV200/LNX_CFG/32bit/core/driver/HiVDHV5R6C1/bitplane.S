#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"bitplane.c"
	.text
	.align	2
	.global	BPD_CfgReg_GetRegVirAddr
	.type	BPD_CfgReg_GetRegVirAddr, %function
BPD_CfgReg_GetRegVirAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0, #8]
	mov	r5, r0
	cmp	r4, #0
	beq	.L6
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L6:
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L3
	str	r3, [r5, #8]
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	ldr	r1, .L7
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L8:
	.align	2
.L7:
	.word	.LC0
	UNWIND(.fnend)
	.size	BPD_CfgReg_GetRegVirAddr, .-BPD_CfgReg_GetRegVirAddr
	.align	2
	.global	BPD_CfgReg
	.type	BPD_CfgReg, %function
BPD_CfgReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r5, r0
	mov	r0, r3
	mov	r6, r1
	mov	r3, #0
	mov	r4, r2
	str	r3, [fp, #-48]
	bl	BPD_CfgReg_GetRegVirAddr
	cmp	r0, #0
	bne	.L24
	ldr	ip, .L41
	mvn	r2, #0
	mvn	r3, #1
	ldr	lr, [ip, #8]
	str	r2, [lr, #68]
	str	r3, [lr, #68]
	ldr	r8, [r6, #24]
	ldr	r3, [r6, #20]
	ldrb	r1, [r5, #3096]	@ zero_extendqisi2
	rsb	r3, r8, r3
	ldr	r2, [r6]
	ubfx	r3, r3, #3, #2
	cmp	r1, #0
	add	r3, r3, r8, lsr #3
	add	r3, r2, r3
	beq	.L11
	ldrb	r2, [r4, #362]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L12
	movw	r2, #362
	ldrh	r2, [r4, r2]
	cmp	r2, #4
	beq	.L12
	ldrb	r2, [r4, #197]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L37
.L14:
	ldrb	r2, [r4, #349]	@ zero_extendqisi2
	ldr	r6, [r4, #392]
	cmp	r2, #4
	ldrb	r7, [r4, #16]	@ zero_extendqisi2
	andne	r1, r2, #3
	ldrb	r2, [fp, #-46]	@ zero_extendqisi2
	moveq	r1, #3
	cmp	r6, #3
	bfi	r2, r6, #0, #2
	ldrb	r6, [fp, #-47]	@ zero_extendqisi2
	bfi	r2, r7, #2, #2
	strb	r2, [fp, #-46]
	bfi	r6, r1, #6, #2
	strb	r6, [fp, #-47]
	beq	.L38
.L17:
	add	r2, r5, #20480
	movw	r6, #21846
	movt	r6, 21845
	ldr	r1, [r2, #3524]
	smull	r6, r7, r1, r6
	sub	r9, r7, r1, asr #31
	add	r9, r9, r9, lsl #1
	rsb	r9, r9, r1
	and	r9, r9, #3
.L21:
	ldr	r10, [r2, #3520]
	movw	r6, #21846
	movt	r6, 21845
	and	r7, r8, #7
	str	r7, [fp, #-56]
	add	r1, r5, #32768
	smull	r6, r7, r10, r6
	ldr	r8, [r1, #3612]
	sub	r6, r7, r10, asr #31
	ldr	r7, [r1, #3624]
	rsb	r8, r8, r3
	add	r8, r8, r7
	ldrb	r7, [fp, #-47]	@ zero_extendqisi2
	add	r6, r6, r6, lsl #1
	and	r8, r8, #15
	bfi	r7, r9, #2, #2
	ldrb	r9, [fp, #-46]	@ zero_extendqisi2
	rsb	r10, r6, r10
	ldr	r6, [fp, #-56]
	and	r9, r9, #239
	bfi	r7, r10, #0, #2
	add	r8, r6, r8, lsl #3
	strb	r7, [fp, #-47]
	strb	r8, [fp, #-48]
	orr	r9, r9, #32
	strb	r9, [fp, #-46]
	ldr	r6, [fp, #-48]
	str	r6, [lr, #4]
	ldr	r7, [r1, #3612]
	ldr	r6, [r1, #3624]
	ldr	lr, [ip, #8]
	rsb	r3, r7, r3
	add	r3, r3, r6
	bic	r3, r3, #15
	str	r3, [lr, #8]
	ldrb	r3, [r5, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L22
	ldr	r3, [r4, #392]
	cmp	r3, #3
	beq	.L39
.L22:
	ldr	r3, [r2, #3524]
	sub	r3, r3, #1
	uxth	r3, r3
.L23:
	ldr	r5, [r2, #3520]
	mov	lr, #0
	strh	r3, [fp, #-46]	@ movhi
	mov	r4, #0
	sub	r3, r5, #1
	strh	r3, [fp, #-48]	@ movhi
	ldr	r3, [ip, #8]
	mov	r5, #3
	ldr	ip, [fp, #-48]
	bfi	r4, r5, #4, #4
	str	lr, [fp, #-48]
	str	ip, [r3, #12]
	ldr	ip, [r2, #3520]
	adds	r2, ip, #127
	addmi	r2, ip, #254
	mov	r2, r2, lsr r5
	and	r2, r2, #4080
	strh	r2, [fp, #-48]	@ movhi
	ldr	r2, [fp, #-48]
	str	lr, [fp, #-48]
	strb	r4, [fp, #-48]
	str	r2, [r3, #16]
	ldr	ip, [r1, #3696]
	strb	r5, [fp, #-47]
	ldr	r2, [fp, #-48]
	str	ip, [r3, #20]
	ldr	ip, [r1, #3700]
	str	ip, [r3, #24]
	ldr	ip, [r1, #3704]
	str	ip, [r3, #28]
	ldr	ip, [r1, #3708]
	str	ip, [r3, #32]
	ldr	ip, [r1, #3712]
	str	ip, [r3, #36]
	ldr	ip, [r1, #3716]
	str	ip, [r3, #40]
	ldr	r1, [r1, #3720]
	str	r1, [r3, #44]
	str	r2, [r3, #48]
.L10:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L11:
	ldrb	r2, [r4, #259]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L18
	cmp	r2, #4
	beq	.L40
.L19:
	ldrb	r2, [r4, #251]	@ zero_extendqisi2
	ldrb	r6, [fp, #-47]	@ zero_extendqisi2
	cmp	r2, #4
	ldrb	r7, [r4]	@ zero_extendqisi2
	andne	r1, r2, #3
	ldrb	r2, [fp, #-46]	@ zero_extendqisi2
	moveq	r1, #3
	bfi	r6, r1, #6, #2
	and	r2, r2, #252
	strb	r6, [fp, #-47]
	bfi	r2, r7, #2, #2
	strb	r2, [fp, #-46]
	b	.L17
.L12:
	ldrb	r2, [fp, #-47]	@ zero_extendqisi2
	orr	r2, r2, #16
	strb	r2, [fp, #-47]
	ldrb	r2, [r4, #197]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L14
.L37:
	ldr	r2, [r4, #464]
	cmp	r2, #8
	ldrleb	r2, [fp, #-47]	@ zero_extendqisi2
	orrle	r2, r2, #32
	strleb	r2, [fp, #-47]
	b	.L14
.L40:
	ldrb	r2, [r4, #260]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L19
.L18:
	ldrb	r2, [fp, #-47]	@ zero_extendqisi2
	orr	r2, r2, #16
	strb	r2, [fp, #-47]
	b	.L19
.L39:
	ldr	r3, [r2, #3524]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	sub	r3, r3, #1
	uxth	r3, r3
	b	.L23
.L38:
	add	r2, r5, #20480
	movw	r6, #21846
	movt	r6, 21845
	ldr	r1, [r2, #3524]
	add	r1, r1, #1
	add	r1, r1, r1, lsr #31
	mov	r10, r1, asr #1
	smull	r6, r7, r10, r6
	sub	r1, r7, r1, asr #31
	add	r1, r1, r1, lsl #1
	rsb	r1, r1, r10
	and	r9, r1, #3
	b	.L21
.L24:
	mvn	r0, #0
	b	.L10
.L42:
	.align	2
.L41:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	BPD_CfgReg, .-BPD_CfgReg
	.align	2
	.global	BPD_Reset
	.type	BPD_Reset, %function
BPD_Reset:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L59
	ldr	r4, .L62
	ldr	r2, [r4]
	add	r2, r2, #61440
	ldr	r1, [r2, #2060]
	uxtb	r3, r1
	str	r1, [fp, #-24]
	orr	r3, r3, #8
	strb	r3, [fp, #-24]
	ldr	r3, [fp, #-24]
	str	r3, [r2, #2060]
	ldr	r3, [r2, #2064]
	tst	r3, #8
	str	r3, [fp, #-24]
	bne	.L48
	movw	r0, #9999
	b	.L46
.L61:
	subs	r0, r0, #1
	beq	.L60
.L46:
	ldr	r3, [r2, #2064]
	tst	r3, #8
	str	r3, [fp, #-24]
	beq	.L61
.L48:
	ldr	r3, [r2, #2060]
	mvn	r0, #1
	ldr	r1, [r4, #8]
	str	r3, [fp, #-24]
	bfc	r3, #3, #1
	strb	r3, [fp, #-24]
	ldr	r3, [fp, #-24]
	str	r3, [r2, #2060]
	str	r0, [r1, #52]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L60:
	ldr	r1, .L62+4
	bl	dprint_vfmw
	ldr	r2, [r4]
	add	r2, r2, #61440
	b	.L48
.L59:
	ldr	r1, .L62+8
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L63:
	.align	2
.L62:
	.word	g_HwMem
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	BPD_Reset, .-BPD_Reset
	.align	2
	.global	BPD_Start
	.type	BPD_Start, %function
BPD_Start:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L65
	mov	r2, #0
	mov	r0, #1
	ldr	r1, [r3, #8]
	str	r2, [r1]
	ldr	r1, [r3, #8]
	str	r0, [r1]
	ldr	r3, [r3, #8]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L66:
	.align	2
.L65:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	BPD_Start, .-BPD_Start
	.align	2
	.global	IsBpd_Ready
	.type	IsBpd_Ready, %function
IsBpd_Ready:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L71
	ldr	r0, [r3, #8]
	cmp	r0, #0
	beq	.L70
	ldr	r0, [r0, #64]
	and	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L70:
	ldr	r3, .L71+4
	ldr	r2, .L71+8
	ldr	r1, .L71+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L72:
	.align	2
.L71:
	.word	g_HwMem
	.word	.LC3
	.word	.LANCHOR0
	.word	.LC4
	UNWIND(.fnend)
	.size	IsBpd_Ready, .-IsBpd_Ready
	.align	2
	.global	BPDDRV_WaitBpdReadyIfNoIsr
	.type	BPDDRV_WaitBpdReadyIfNoIsr, %function
BPDDRV_WaitBpdReadyIfNoIsr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L81
	mov	r4, #0
	ldr	r3, [r6]
	blx	r3
	mov	r5, r0
	b	.L76
.L80:
	ldr	r3, [r6]
	blx	r3
	cmp	r0, r5
	movcc	r5, #0
	rsb	r4, r5, r0
	cmp	r4, #4000
	bcs	.L78
.L76:
	bl	IsBpd_Ready
	cmp	r0, #0
	beq	.L80
	cmp	r4, #4000
	bcs	.L78
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L78:
	ldr	r1, .L81+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L82:
	.align	2
.L81:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	UNWIND(.fnend)
	.size	BPDDRV_WaitBpdReadyIfNoIsr, .-BPDDRV_WaitBpdReadyIfNoIsr
	.align	2
	.global	BPD_GetParam
	.type	BPD_GetParam, %function
BPD_GetParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L90
	ldr	r4, [r2, #16]
	ldr	r3, [r2, #24]
	ldr	ip, [ip, #8]
	rsb	r5, r3, r4, lsl #3
	ldr	lr, [ip, #80]
	ldr	ip, [ip, #84]
	cmp	lr, r5
	bcs	.L88
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L89
	and	r0, ip, #15
	ubfx	r3, ip, #8, #4
	str	r0, [r1, #328]
	ubfx	ip, ip, #4, #4
	str	r3, [r1, #332]
	str	ip, [r1, #336]
.L87:
	mov	r1, lr
	mov	r0, r2
	bl	BsLongSkip
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L89:
	ubfx	r3, ip, #0, #4
	ubfx	r0, ip, #12, #4
	strb	r3, [r1, #382]
	ubfx	r3, ip, #16, #4
	strb	r0, [r1, #385]
	ubfx	r0, ip, #20, #4
	strb	r3, [r1, #386]
	ubfx	r3, ip, #8, #4
	strb	r0, [r1, #387]
	ubfx	r0, ip, #24, #4
	strb	r3, [r1, #383]
	ubfx	r3, ip, #4, #4
	strb	r0, [r1, #388]
	ubfx	ip, ip, #28, #2
	strb	r3, [r1, #384]
	strb	ip, [r1, #378]
	b	.L87
.L88:
	rsb	r3, r3, r4
	mov	r2, lr
	ldr	r1, .L90+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L91:
	.align	2
.L90:
	.word	g_HwMem
	.word	.LC6
	UNWIND(.fnend)
	.size	BPD_GetParam, .-BPD_GetParam
	.align	2
	.global	BPD_Drv
	.type	BPD_Drv, %function
BPD_Drv:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	add	r4, r1, #20480
	mov	r9, r0
	mov	r0, #2
	ldr	ip, [r4, #3524]
	mov	r8, r2
	mov	r7, r3
	mov	r2, #1
	cmp	ip, r0
	mov	r3, #0
	mov	r6, r1
	str	r0, [fp, #-48]
	str	r3, [fp, #-44]
	str	r2, [fp, #-40]
	ldr	lr, [r4, #3520]
	ble	.L94
	cmp	ip, #128
	sub	r5, lr, #3
	movle	r3, #0
	movgt	r3, #1
	cmp	r5, #125
	movls	r5, r3
	orrhi	r5, r3, #1
	cmp	r5, #0
	beq	.L95
.L94:
	mov	r3, ip, asl #4
	mov	r2, lr, asl #4
	ldr	r1, .L110
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #3520]
	cmp	r3, #128
	ble	.L108
.L96:
	ldr	r3, .L110+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L102
	mov	r3, #0
	mov	r0, r7
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mov	r0, #1
.L97:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L108:
	ldr	r3, [r4, #3524]
	cmp	r3, #128
	bgt	.L96
.L102:
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L95:
	ldr	r7, .L110+8
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L98
	mov	r1, r5
	str	r2, [sp]
	mov	r3, #400
	bl	VDH_Acquire_Usage
	mov	r0, r5
	sub	r1, fp, #48
	bl	VDH_Set_Parameter
.L98:
	ldr	r5, .L110+12
	bl	BPD_Reset
	mov	r2, r8
	mov	r1, r9
	mov	r0, r6
	mov	r3, r5
	bl	BPD_CfgReg
	cmp	r0, #0
	beq	.L109
	ldr	r1, .L110+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r4, #1
.L100:
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r0, r4
	beq	.L97
	mov	r5, #0
	sub	r1, fp, #48
	mov	r0, r5
	str	r5, [fp, #-40]
	bl	VDH_Set_Parameter
	mov	r1, r5
	mov	r2, #1
	mov	r0, #2
	bl	VDH_Loose_Usage
	mov	r0, r4
	b	.L97
.L109:
	ldr	r3, [r5, #8]
	mov	r4, #1
	str	r0, [r3]
	ldr	r3, [r5, #8]
	str	r4, [r3]
	ldr	r3, [r5, #8]
	str	r0, [r3]
	bl	BPDDRV_WaitBpdReadyIfNoIsr
	cmp	r0, #0
	bne	.L100
	mov	r2, r9
	mov	r1, r8
	mov	r0, r6
	bl	BPD_GetParam
	adds	r4, r0, #0
	movne	r4, #1
	b	.L100
.L111:
	.align	2
.L110:
	.word	.LC7
	.word	g_event_report
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LC8
	UNWIND(.fnend)
	.size	BPD_Drv, .-BPD_Drv
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.50160, %object
	.size	__func__.50160, 12
__func__.50160:
	.ascii	"IsBpd_Ready\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"BPD register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC1:
	ASCII(.ascii	"VDMHAL_ResetBPD: map BPD register fail, vir(reg) = " )
	ASCII(.ascii	"(%p)\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"Reset BPD Failed!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"BPD register not mapped yet!\000" )
	.space	3
.LC4:
	ASCII(.ascii	"%s: %s\012\000" )
.LC5:
	ASCII(.ascii	"BPD TimeOut!\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	" BPD ERROR: EAT TOO MUCH BS %#x, but available bs n" )
	ASCII(.ascii	"um %#x!!!\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"NOT SUPPORT SIZE %d*%d\012\000" )
.LC8:
	ASCII(.ascii	"BPD error: no map reg!\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
