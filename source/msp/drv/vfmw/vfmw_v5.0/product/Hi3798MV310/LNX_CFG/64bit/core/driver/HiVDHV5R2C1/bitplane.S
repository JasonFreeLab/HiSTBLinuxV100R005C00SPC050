#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"bitplane.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	BPD_CfgReg_GetRegVirAddr
	.type	BPD_CfgReg_GetRegVirAddr, %function
BPD_CfgReg_GetRegVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 16]
	cbz	x0, .L6
	mov	w0, 0
.L2:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L6:
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	cbz	x0, .L3
	str	x0, [x19, 16]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L3:
	ldr	x1, .LC1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2
	.size	BPD_CfgReg_GetRegVirAddr, .-BPD_CfgReg_GetRegVirAddr
	.align	3
.LC1:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_CfgReg
	.type	BPD_CfgReg, %function
BPD_CfgReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x3
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	mov	x0, x22
	str	wzr, [x29, 60]
	bl	BPD_CfgReg_GetRegVirAddr
	cbnz	w0, .L22
	ldr	x7, .LC2
	mov	w2, -1
	mov	w1, -2
	ldr	x9, [x7, 16]
	str	w2, [x9, 68]
	str	w1, [x9, 68]
	ldp	w2, w5, [x21, 28]
	ldrsb	w3, [x19, 3104]
	sub	w2, w2, w5
	ubfx	x1, x5, 3, 29
	ubfx	x2, x2, 3, 2
	ldr	x4, [x21]
	add	x2, x2, x1
	add	x1, x4, x2
	cbz	w3, .L9
	ldrb	w2, [x20, 374]
	cbz	w2, .L10
	ldrh	w2, [x20, 374]
	cmp	w2, 4
	beq	.L10
	ldrb	w2, [x20, 197]
	cmp	w2, 1
	beq	.L35
.L12:
	ldrb	w2, [x20, 361]
	mov	w3, 3
	ldrb	w4, [x29, 61]
	cmp	w2, 4
	and	w2, w2, w3
	csel	w2, w2, w3, ne
	ldr	w3, [x20, 404]
	bfi	w4, w2, 6, 2
	ldrb	w2, [x29, 62]
	cmp	w3, 3
	strb	w4, [x29, 61]
	bfi	w2, w3, 0, 2
	ldrb	w3, [x20, 16]
	bfi	w2, w3, 2, 2
	strb	w2, [x29, 62]
	beq	.L36
.L15:
	add	x8, x19, 20480
	mov	w2, 21846
	movk	w2, 0x5555, lsl 16
	ldr	w3, [x8, 3596]
	smull	x2, w3, w2
	lsr	x2, x2, 32
	sub	w2, w2, w3, asr 31
	add	w3, w2, w3
	and	w3, w3, 3
.L19:
	ldrb	w2, [x29, 61]
	and	w11, w5, 7
	ldr	w10, [x8, 3592]
	mov	w4, 21846
	bfi	w2, w3, 2, 2
	add	x3, x19, 36864
	movk	w4, 0x5555, lsl 16
	ldr	x5, [x3, 1640]
	ldr	w6, [x3, 1660]
	sub	x5, x1, x5
	add	x5, x5, x6
	and	w5, w5, 15
	smull	x4, w10, w4
	add	w5, w11, w5, lsl 3
	strb	w5, [x29, 60]
	ldrb	w5, [x29, 62]
	lsr	x4, x4, 32
	sub	w4, w4, w10, asr 31
	and	w5, w5, -17
	orr	w5, w5, 32
	strb	w5, [x29, 62]
	lsl	w5, w4, 2
	sub	w4, w5, w4
	sub	w10, w10, w4
	bfi	w2, w10, 0, 2
	strb	w2, [x29, 61]
	ldr	w2, [x29, 60]
	str	w2, [x9, 4]
	ldr	x5, [x3, 1640]
	ldr	w4, [x3, 1660]
	ldr	x2, [x7, 16]
	sub	x1, x1, x5
	add	w1, w4, w1
	and	w1, w1, -16
	str	w1, [x2, 8]
	ldrsb	w1, [x19, 3104]
	cbz	w1, .L20
	ldr	w1, [x20, 404]
	cmp	w1, 3
	beq	.L37
.L20:
	ldr	w1, [x8, 3596]
	sub	w1, w1, #1
	uxth	w1, w1
.L21:
	ldr	w2, [x8, 3592]
	mov	w4, 3
	strh	w1, [x29, 62]
	mov	w5, 0
	ldr	x6, [x7, 16]
	sub	w1, w2, #1
	strh	w1, [x29, 60]
	bfi	w5, w4, 4, 4
	ldr	w1, [x29, 60]
	str	w1, [x6, 12]
	str	wzr, [x29, 60]
	ldr	w1, [x8, 3592]
	ldr	x6, [x7, 16]
	add	w2, w1, 254
	adds	w1, w1, 127
	csel	w1, w2, w1, mi
	ubfx	x1, x1, 7, 12
	ubfiz	w1, w1, 4, 8
	strh	w1, [x29, 60]
	ldr	w1, [x29, 60]
	str	w1, [x6, 16]
	str	wzr, [x29, 60]
	ldr	x1, [x7, 16]
	strb	w4, [x29, 61]
	ldr	w4, [x3, 1736]
	str	w4, [x1, 20]
	strb	w5, [x29, 60]
	ldr	x1, [x7, 16]
	ldr	w4, [x3, 1740]
	ldr	w2, [x29, 60]
	str	w4, [x1, 24]
	ldr	w4, [x3, 1744]
	str	w4, [x1, 28]
	ldr	w4, [x3, 1748]
	str	w4, [x1, 32]
	ldr	w4, [x3, 1752]
	str	w4, [x1, 36]
	ldr	w4, [x3, 1756]
	str	w4, [x1, 40]
	ldr	w3, [x3, 1760]
	str	w3, [x1, 44]
	str	w2, [x1, 48]
.L8:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L9:
	ldrb	w2, [x20, 259]
	cbz	w2, .L16
	ldr	x2, [x20, 256]
	mov	x3, 67108864
	and	x2, x2, 1099494850560
	cmp	x2, x3
	beq	.L16
.L17:
	ldrb	w6, [x20, 251]
	mov	w3, 3
	ldrb	w4, [x29, 61]
	and	w2, w6, w3
	cmp	w6, 4
	csel	w3, w2, w3, ne
	ldrb	w2, [x29, 62]
	bfi	w4, w3, 6, 2
	ldrb	w3, [x20]
	and	w2, w2, 252
	strb	w4, [x29, 61]
	bfi	w2, w3, 2, 2
	strb	w2, [x29, 62]
	b	.L15
	.p2align 3
.L16:
	ldrb	w2, [x29, 61]
	orr	w2, w2, 16
	strb	w2, [x29, 61]
	b	.L17
	.p2align 3
.L10:
	ldrb	w2, [x29, 61]
	orr	w2, w2, 16
	strb	w2, [x29, 61]
	ldrb	w2, [x20, 197]
	cmp	w2, 1
	bne	.L12
.L35:
	ldr	w2, [x20, 476]
	cmp	w2, 8
	bgt	.L12
	ldrb	w2, [x29, 61]
	orr	w2, w2, 32
	strb	w2, [x29, 61]
	b	.L12
	.p2align 3
.L37:
	ldr	w1, [x8, 3596]
	add	w1, w1, 1
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	sub	w1, w1, #1
	uxth	w1, w1
	b	.L21
	.p2align 3
.L36:
	add	x8, x19, 20480
	mov	w2, 21846
	movk	w2, 0x5555, lsl 16
	ldr	w4, [x8, 3596]
	add	w4, w4, 1
	add	w4, w4, w4, lsr 31
	asr	w3, w4, 1
	smull	x2, w3, w2
	lsr	x2, x2, 32
	sub	w4, w2, w4, asr 31
	add	w3, w3, w4
	and	w3, w3, 3
	b	.L19
	.p2align 3
.L22:
	mov	w0, -1
	b	.L8
	.size	BPD_CfgReg, .-BPD_CfgReg
	.align	3
.LC2:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_Reset
	.type	BPD_Reset, %function
BPD_Reset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	cbz	x0, .L53
	ldr	x20, .LC5
	ldr	x2, [x20]
	ldr	w19, [x2, 136]
	orr	w19, w19, 16
	str	w19, [x2, 136]
	ldr	w0, [x2, 372]
	tbnz	x0, 3, .L41
	mov	w0, 9999
	b	.L42
	.p2align 3
.L55:
	subs	w0, w0, #1
	beq	.L54
.L42:
	ldr	w1, [x2, 372]
	tbz	x1, 3, .L55
.L41:
	ldr	x0, .LC6
	and	w19, w19, -17
	str	w19, [x2, 136]
	mov	w1, -2
	ldr	x0, [x0, 16]
	str	w1, [x0, 52]
.L38:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L54:
	ldr	x1, .LC8
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x2, [x20]
	b	.L41
.L53:
	ldr	x1, .LC4
	mov	x2, 0
	bl	dprint_vfmw
	b	.L38
	.size	BPD_Reset, .-BPD_Reset
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	g_pstRegCrg
	.align	3
.LC6:
	.xword	g_HwMem
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_Start
	.type	BPD_Start, %function
BPD_Start:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC9
	mov	w2, 1
	ldr	x1, [x0, 16]
	str	wzr, [x1]
	ldr	x1, [x0, 16]
	str	w2, [x1]
	ldr	x0, [x0, 16]
	str	wzr, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	BPD_Start, .-BPD_Start
	.align	3
.LC9:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsBpd_Ready
	.type	IsBpd_Ready, %function
IsBpd_Ready:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC10
	ldr	x0, [x0, 16]
	cbz	x0, .L60
	ldr	w0, [x0, 64]
	and	w0, w0, 1
.L59:
	ldp	x29, x30, [sp], 16
	ret
.L60:
	ldr	x3, .LC12
	ldr	x2, .LC13
	ldr	x1, .LC15
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.size	IsBpd_Ready, .-IsBpd_Ready
	.align	3
.LC10:
	.xword	g_HwMem
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC15:
	.xword	.LC14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPDDRV_WaitBpdReadyIfNoIsr
	.type	BPDDRV_WaitBpdReadyIfNoIsr, %function
BPDDRV_WaitBpdReadyIfNoIsr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x21, .LC16
	ldr	x0, [x21]
	blr	x0
	ldr	x22, .LC17
	mov	w20, w0
	b	.L65
	.p2align 3
.L62:
	ldr	w0, [x0, 64]
	tbnz	x0, 0, .L63
	ldr	x0, [x21]
	blr	x0
	cmp	w0, w20
	csel	w20, w20, wzr, cs
	sub	w19, w0, w20
	cmp	w19, 3999
	bhi	.L67
.L65:
	ldr	x0, [x22, 16]
	cbnz	x0, .L62
	ldr	x3, .LC18
	ldr	x2, .LC19
	ldr	x1, .LC20
	bl	dprint_vfmw
.L63:
	cmp	w19, 3999
	bhi	.L67
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L67:
	ldr	x1, .LC22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	BPDDRV_WaitBpdReadyIfNoIsr, .-BPDDRV_WaitBpdReadyIfNoIsr
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC17:
	.xword	g_HwMem
	.align	3
.LC18:
	.xword	.LC11
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	.LC14
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_GetParam
	.type	BPD_GetParam, %function
BPD_GetParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x2
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC23
	ldr	w4, [x20, 24]
	ldr	w3, [x20, 32]
	ldr	x0, [x0, 16]
	lsl	w1, w4, 3
	sub	w1, w1, w3
	ldr	w2, [x0, 80]
	ldr	w0, [x0, 84]
	cmp	w2, w1
	bcs	.L74
	ldrsb	w1, [x21, 3104]
	cbnz	w1, .L75
	and	w3, w0, 15
	ubfx	x1, x0, 8, 4
	str	w3, [x19, 340]
	ubfx	x0, x0, 4, 4
	str	w1, [x19, 344]
	str	w0, [x19, 348]
.L73:
	mov	w1, w2
	mov	x0, x20
	bl	BsLongSkip
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L75:
	ubfx	x1, x0, 12, 4
	ubfx	x7, x0, 0, 4
	ubfx	x6, x0, 16, 4
	ubfx	x5, x0, 20, 4
	ubfx	x4, x0, 8, 4
	ubfx	x3, x0, 24, 4
	strb	w1, [x19, 397]
	ubfx	x1, x0, 4, 4
	strb	w7, [x19, 394]
	ubfx	x0, x0, 28, 2
	strb	w6, [x19, 398]
	strb	w5, [x19, 399]
	strb	w4, [x19, 395]
	strb	w3, [x19, 400]
	strb	w1, [x19, 396]
	strb	w0, [x19, 390]
	b	.L73
	.p2align 3
.L74:
	ldr	x1, .LC25
	sub	w3, w4, w3
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	BPD_GetParam, .-BPD_GetParam
	.align	3
.LC23:
	.xword	g_HwMem
	.align	3
.LC25:
	.xword	.LC24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_Drv
	.type	BPD_Drv, %function
BPD_Drv:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	add	x19, x1, 20480
	mov	x22, x0
	mov	x0, x30
	mov	x21, x2
	mov	w23, w3
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x19, 3596]
	mov	w0, 2
	mov	w5, 1
	str	w5, [x29, 72]
	cmp	w3, w0
	ldr	w2, [x19, 3592]
	stp	w0, wzr, [x29, 64]
	ble	.L78
	sub	w1, w2, #3
	cmp	w1, 125
	mov	w1, 128
	ccmp	w3, w1, 0, ls
	ble	.L79
.L78:
	ldr	x1, .LC27
	lsl	w3, w3, 4
	lsl	w2, w2, 4
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 3592]
	cmp	w0, 128
	ble	.L93
	ldr	x0, .LC28
	ldr	x4, [x0]
	cbz	x4, .L86
.L94:
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w23
	mov	w19, 1
	blr	x4
.L81:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L93:
	ldr	w0, [x19, 3596]
	mov	w19, 1
	cmp	w0, 128
	ble	.L81
	ldr	x0, .LC28
	ldr	x4, [x0]
	cbnz	x4, .L94
.L86:
	mov	w19, 1
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L79:
	ldr	x24, .LC29
	ldrb	w1, [x24]
	cmp	w1, 1
	beq	.L82
	mov	w1, 0
	mov	w4, w5
	mov	w3, 400
	mov	w2, w5
	bl	VDH_Acquire_Usage
	add	x1, x29, 64
	mov	w0, 0
	bl	VDH_Set_Parameter
.L82:
	bl	BPD_Reset
	ldr	x23, .LC30
	mov	x2, x21
	mov	x1, x22
	mov	x3, x23
	mov	x0, x20
	bl	BPD_CfgReg
	cbz	w0, .L95
	ldr	x1, .LC32
	mov	w0, 0
	mov	w19, 1
	bl	dprint_vfmw
.L84:
	ldrb	w0, [x24]
	cmp	w0, 1
	beq	.L81
	add	x1, x29, 64
	mov	w0, 0
	str	wzr, [x29, 72]
	bl	VDH_Set_Parameter
	mov	w2, 1
	mov	w1, 0
	mov	w0, 2
	bl	VDH_Loose_Usage
	b	.L81
	.p2align 3
.L95:
	ldr	x0, [x23, 16]
	mov	w19, 1
	str	wzr, [x0]
	ldr	x0, [x23, 16]
	str	w19, [x0]
	ldr	x0, [x23, 16]
	str	wzr, [x0]
	bl	BPDDRV_WaitBpdReadyIfNoIsr
	cbnz	w0, .L84
	mov	x2, x22
	mov	x1, x21
	mov	x0, x20
	bl	BPD_GetParam
	cmp	w0, wzr
	cset	w19, ne
	b	.L84
	.size	BPD_Drv, .-BPD_Drv
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC28:
	.xword	g_event_report
	.align	3
.LC29:
	.xword	g_HalDisable
	.align	3
.LC30:
	.xword	g_HwMem
	.align	3
.LC32:
	.xword	.LC31
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.44861, %object
	.size	__func__.44861, 12
__func__.44861:
	.string	"IsBpd_Ready"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"BPD register virtual address not mapped, reset failed!\n" )
.LC3:
	ASCII(.string	"VDMHAL_ResetBPD: map BPD register fail, vir(reg) = (%p)\n" )
	.zero	7
.LC7:
	ASCII(.string	"Reset BPD Failed!\n" )
	.zero	5
.LC11:
	ASCII(.string	"BPD register not mapped yet!" )
	.zero	3
.LC14:
	ASCII(.string	"%s: %s\n" )
.LC21:
	ASCII(.string	"BPD TimeOut!\n" )
	.zero	2
.LC24:
	ASCII(.string	" BPD ERROR: EAT TOO MUCH BS %#x, but available bs num %#x!!!\n" )
	.zero	2
.LC26:
	ASCII(.string	"NOT SUPPORT SIZE %d*%d\n" )
.LC31:
	ASCII(.string	"BPD error: no map reg!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
