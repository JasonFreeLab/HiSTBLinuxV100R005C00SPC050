#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_avs.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2, %function
AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	w21, w1
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	cbz	w21, .L1
	add	w1, w21, 1
	mov	x9, x20
	mov	w0, 6
	mov	w2, 1
	b	.L5
	.p2align 3
.L9:
	ldr	w3, [x7, 14612]
	add	w2, w2, 1
	ldr	w5, [x8, 14612]
	cmp	w1, w2
	ldr	w6, [x10, 14612]
	and	w3, w3, 255
	ldr	w4, [x11, 14612]
	ubfiz	w5, w5, 8, 8
	ubfiz	w6, w6, 16, 8
	add	w0, w0, 4
	orr	w5, w6, w5
	orr	w3, w3, w4, lsl 24
	orr	w3, w5, w3
	str	w3, [x9], 4
	beq	.L1
.L5:
	sub	w6, w0, #3
	sub	w5, w0, #5
	sub	w4, w0, #7
	sub	w3, w0, #9
	lsl	w10, w2, 2
	sub	w8, w0, #4
	sub	w7, w9, w20
	add	x6, x19, x6, sxtw 2
	add	x5, x19, x5, sxtw 2
	add	x4, x19, x4, sxtw 2
	add	x3, x19, x3, sxtw 2
	add	x10, x19, x10, sxtw 2
	add	x8, x19, x8, sxtw 2
	add	x11, x19, x0, sxtw 2
	add	x7, x19, x7, sxtw 2
	tbnz	x2, 0, .L9
	ldr	w7, [x4, 14612]
	add	w2, w2, 1
	ldr	w4, [x3, 14612]
	cmp	w1, w2
	ldr	w5, [x5, 14612]
	ubfiz	w3, w7, 8, 8
	ldr	w6, [x6, 14612]
	and	w4, w4, 255
	ubfiz	w5, w5, 16, 8
	orr	w3, w3, w4
	add	w0, w0, 4
	orr	w5, w5, w6, lsl 24
	orr	w3, w5, w3
	str	w3, [x9], 4
	bne	.L5
.L1:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2, .-AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_InitHal
	.type	AVSHAL_V5R2C1_InitHal, %function
AVSHAL_V5R2C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	AVSHAL_V5R2C1_InitHal, .-AVSHAL_V5R2C1_InitHal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec_CheckParam
	.type	AVSHAL_V5R2C1_StartDec_CheckParam, %function
AVSHAL_V5R2C1_StartDec_CheckParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L16
	ldrh	w0, [x19, 72]
	cmp	w0, 512
	bhi	.L15
	ldrh	w0, [x19, 74]
	cmp	w0, 512
	bhi	.L15
	mov	w0, 0
.L13:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L16:
	ldr	x2, .LC0
	mov	w4, 0
	ldr	x1, .LC2
	mov	w3, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L13
	.p2align 3
.L15:
	ldr	x3, .LC4
	mov	w0, 0
	ldr	x2, .LC0
	ldr	x1, .LC6
	bl	dprint_vfmw
	mov	w0, -1
	b	.L13
	.size	AVSHAL_V5R2C1_StartDec_CheckParam, .-AVSHAL_V5R2C1_StartDec_CheckParam
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC6:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec_GetRegAddr
	.type	AVSHAL_V5R2C1_StartDec_GetRegAddr, %function
AVSHAL_V5R2C1_StartDec_GetRegAddr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L22
	sxtw	x2, w19
	ldr	x20, .LC9
	lsl	x19, x2, 6
	mov	w0, -121438208
	sub	x19, x19, x2
	str	w0, [x21]
	lsl	x19, x19, 2
	mov	w21, 0
	sub	x2, x19, x2
	add	x19, x19, x2, lsl 2
	ldr	x1, [x20, x19]
	cbz	x1, .L23
.L19:
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L23:
	bl	MEM_Phy2Vir
	cbz	x0, .L20
	str	x0, [x20, x19]
	b	.L19
	.p2align 3
.L22:
	ldr	x1, .LC8
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L19
.L20:
	ldr	x1, .LC11
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L19
	.size	AVSHAL_V5R2C1_StartDec_GetRegAddr, .-AVSHAL_V5R2C1_StartDec_GetRegAddr
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	g_HwMem
	.align	3
.LC11:
	.xword	.LC10
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec_GetStrmAddr
	.type	AVSHAL_V5R2C1_StartDec_GetStrmAddr, %function
AVSHAL_V5R2C1_StartDec_GetStrmAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w5, -1
	str	w5, [x20]
	mov	w4, 0
	ldr	w0, [x19, 14448]
	cmp	w0, wzr
	ble	.L32
	.p2align 2
.L37:
	sxtw	x3, w4
	lsl	x2, x3, 3
	sub	x2, x2, x3
	add	x2, x19, x2, lsl 2
	mov	x0, x2
	ldr	w3, [x2, 112]
	cbz	w3, .L30
	ldr	w2, [x2, 120]
	and	w3, w3, -16
	cmp	w2, wzr
	ble	.L30
	cmp	w5, w3
	csel	w5, w5, w3, ls
	str	w5, [x20]
.L30:
	ldr	w2, [x0, 116]
	cbz	w2, .L27
	ldr	w0, [x0, 124]
	and	w2, w2, -16
	cmp	w0, wzr
	ble	.L27
	cmp	w5, w2
	csel	w5, w5, w2, ls
	str	w5, [x20]
.L27:
	ldr	w0, [x19, 14448]
	add	w4, w4, 1
	cmp	w0, w4
	bgt	.L37
	cmn	w5, #1
	beq	.L32
	mov	w0, 0
.L26:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L32:
	ldr	x1, .LC13
	mov	w2, -1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L26
	.size	AVSHAL_V5R2C1_StartDec_GetStrmAddr, .-AVSHAL_V5R2C1_StartDec_GetStrmAddr
	.align	3
.LC13:
	.xword	.LC12
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec_GetModuleLowlyFlag
	.type	AVSHAL_V5R2C1_StartDec_GetModuleLowlyFlag, %function
AVSHAL_V5R2C1_StartDec_GetModuleLowlyFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC14
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L44
	ldr	w0, [x0, 1272]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L44:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVSHAL_V5R2C1_StartDec_GetModuleLowlyFlag, .-AVSHAL_V5R2C1_StartDec_GetModuleLowlyFlag
	.align	3
.LC14:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix
	.type	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix, %function
AVSHAL_V5R2C1_StartDec_ConfigWQMatrix:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldrb	w0, [x19, 41]
	cmp	w0, 1
	bne	.L45
	mov	x2, x21
	mov	w1, w20
	mov	x0, x19
	bl	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2
.L45:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix, .-AVSHAL_V5R2C1_StartDec_ConfigWQMatrix
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_WirteSlicMsg
	.type	AVSHAL_V5R2C1_WirteSlicMsg, %function
AVSHAL_V5R2C1_WirteSlicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w2
	mov	w21, w1
	bl	_mcount
	add	x19, x20, 112
	sxtw	x0, w22
	ldr	x2, .LC15
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	add	x0, x2, x0
	ldr	w23, [x0, 72]
	mov	w0, w23
	add	w22, w23, 320
	bl	MEM_Phy2Vir
	add	x1, x0, 320
	ldr	w2, [x19, 16]
	mov	w8, 0
	cbz	w2, .L48
	ldr	w2, [x20, 112]
	add	w2, w2, 4
	sub	w2, w2, w21
	ubfiz	w3, w2, 3, 4
	and	w2, w2, -16
	cmp	w3, 7
	bls	.L75
	sub	w3, w3, #8
.L50:
	lsl	w3, w3, 25
	and	w2, w2, 16777215
	orr	w3, w3, 8
	str	w3, [x0, 320]
	str	w2, [x0, 324]
	add	w23, w23, 576
	str	wzr, [x0, 328]
	mov	w8, 1
	str	wzr, [x0, 332]
	ldr	w2, [x19, 16]
	sub	w2, w2, #1
	lsl	w2, w2, 16
	str	w2, [x0, 336]
	str	w23, [x0, 572]
.L48:
	ldr	w5, [x20, 14448]
	cmp	w5, wzr
	ble	.L47
	add	w8, w22, w8, lsl 8
	mov	w2, 0
	mov	w7, 0
	mov	w0, 0
	.p2align 2
.L66:
	cmp	w7, 511
	bgt	.L52
	sxtw	x4, w0
	cmp	w0, wzr
	lsl	x3, x4, 3
	sub	x3, x3, x4
	add	x3, x19, x3, lsl 2
	ble	.L54
	ldr	w6, [x3, -12]
	ldr	w9, [x3, 16]
	cmp	w9, w6
	bls	.L55
.L54:
	ldp	w2, w6, [x3]
	ldr	w5, [x3, 8]
	add	w2, w2, 4
	sub	w2, w2, w21
	sub	w5, w5, #4
	and	w9, w2, -16
	lsl	w5, w5, 3
	ubfiz	w2, w2, 3, 4
	cbz	w6, .L74
	lsl	x10, x4, 3
	sub	x10, x10, x4
	add	x10, x20, x10, lsl 2
	ldr	w10, [x10, 124]
	cmp	w10, wzr
	ble	.L74
	ldr	w11, [x3, 12]
	sub	w6, w6, w21
	and	w12, w6, -16
	ubfiz	w10, w6, 3, 4
	lsl	w11, w11, 3
	cbz	w5, .L71
	cmp	w2, 7
	and	w11, w11, 33554431
	orr	w10, w11, w10, lsl 25
	and	w6, w6, 16777200
	bhi	.L57
	.p2align 2
.L78:
	sub	w9, w9, #4
	add	w2, w2, 120
	add	w5, w5, 8
.L58:
	lsl	x4, x4, 8
	and	w5, w5, 33554431
	add	x12, x4, 4
	add	x11, x4, 8
	orr	w2, w5, w2, lsl 25
	add	x5, x4, 12
	str	w2, [x1, x4]
	and	w9, w9, 16777215
	str	w9, [x1, x12]
	add	w2, w0, 1
	str	w10, [x1, x11]
	str	w6, [x1, x5]
	ldr	w6, [x20, 14448]
	cmp	w2, w6
	bge	.L76
	sxtw	x9, w2
	ldr	w5, [x3, 16]
	lsl	x0, x9, 3
	sub	x0, x0, x9
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 16]
	cmp	w5, w0
	bcs	.L62
	b	.L60
	.p2align 3
.L63:
	sub	x0, x0, x3
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 16]
	cmp	w0, w5
	bhi	.L60
.L62:
	add	w2, w2, 1
	cmp	w2, w6
	sxtw	x3, w2
	lsl	x0, x3, 3
	blt	.L63
.L60:
	cmp	w6, w2
	beq	.L77
	sxtw	x3, w2
	add	w6, w8, w2, lsl 8
	lsl	x0, x3, 3
	sub	x0, x0, x3
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 16]
	sub	w0, w0, #1
.L65:
	add	x3, x4, 16
	add	x4, x4, 252
	and	w5, w5, 65535
	add	w7, w7, 1
	orr	w5, w5, w0, lsl 16
	str	w5, [x1, x3]
	str	w6, [x1, x4]
	ldr	w5, [x20, 14448]
.L52:
	sub	w0, w2, #1
.L55:
	add	w0, w0, 1
	cmp	w5, w0
	bgt	.L66
.L47:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L71:
	mov	w9, w12
	mov	w5, w11
	mov	w2, w10
.L74:
	cmp	w2, 7
	mov	w6, 0
	mov	w10, 0
	bls	.L78
.L57:
	sub	w2, w2, #8
	add	w5, w5, 8
	b	.L58
	.p2align 3
.L77:
	ldrh	w0, [x20, 72]
	mov	w6, 0
	ldrh	w3, [x20, 74]
	mul	w0, w0, w3
	sub	w0, w0, #1
	b	.L65
.L75:
	sub	w2, w2, #4
	add	w3, w3, 120
	b	.L50
.L76:
	ldr	w5, [x3, 16]
	b	.L60
	.size	AVSHAL_V5R2C1_WirteSlicMsg, .-AVSHAL_V5R2C1_WirteSlicMsg
	.align	3
.LC15:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSHAL_V5R2C1_StartDec
	.type	AVSHAL_V5R2C1_StartDec, %function
AVSHAL_V5R2C1_StartDec:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	sxtw	x22, w1
	mov	x21, x2
	bl	_mcount
	ldr	x23, .LC19
	ldr	x0, .LC18
	mov	x20, x22
	stp	wzr, wzr, [x29, 104]
	ldrb	w1, [x23]
	add	x0, x0, x22, lsl 6
	cmp	w1, 1
	ccmp	x21, xzr, 0, ne
	ldr	w24, [x0, 8]
	beq	.L99
	mov	x1, x19
	mov	w0, w22
	bl	AVSHAL_V5R2C1_StartDec_CheckParam
	cbnz	w0, .L83
	add	x1, x29, 108
	mov	w0, w22
	bl	AVSHAL_V5R2C1_StartDec_GetRegAddr
	mov	w26, w0
	cbnz	w0, .L83
	ldr	x0, .LC23
	ldr	x0, [x0, w24, sxtw 3]
	cbz	x0, .L84
	ldr	w26, [x0, 1272]
.L84:
	ldrb	w0, [x23]
	cmp	w0, 1
	beq	.L85
	strb	w26, [x21, 1]
.L85:
	add	x1, x29, 104
	mov	x0, x19
	bl	AVSHAL_V5R2C1_StartDec_GetStrmAddr
	mov	w24, w0
	cbnz	w0, .L83
	ldrh	w2, [x19, 74]
	mov	w0, 0
	ldrh	w1, [x19, 72]
	mov	x3, x21
	mul	w1, w1, w2
	mov	w2, w20
	sub	w1, w1, #1
	bfi	w0, w1, 0, 20
	str	w0, [x29, 100]
	lsr	w0, w0, 16
	mov	w1, 65
	orr	w0, w0, 64
	strb	w1, [x29, 103]
	strb	w0, [x29, 102]
	mov	w0, 8
	ldr	w23, [x29, 100]
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC25
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	mov	w1, 1
	mov	w0, 12288
	bfi	w0, w1, 0, 12
	strh	w0, [x29, 102]
	ldrb	w2, [x19, 16]
	mov	w4, 6
	uxth	w0, w0
	ldr	w3, [x19, 14908]
	lsr	w0, w0, 8
	cmp	w2, w1
	bfi	w0, w26, 4, 1
	strb	w0, [x29, 103]
	ccmp	w2, 3, 4, hi
	strb	w4, [x29, 100]
	ldrh	w0, [x19, 72]
	cset	w2, eq
	cmp	w0, 120
	mov	w0, 0
	bfi	w0, w3, 4, 1
	orr	w0, w0, 64
	bfi	w0, w2, 7, 1
	strb	w0, [x29, 101]
	ble	.L100
	ldr	w2, [x19, 14904]
	mov	w1, 0
	strb	wzr, [x19, 48]
	and	w2, w2, 1
.L87:
	ldrb	w0, [x29, 103]
	mov	x3, x21
	lsl	x25, x22, 6
	bfi	w0, w1, 5, 1
	sub	x25, x25, x22
	bfi	w0, w2, 6, 1
	mov	w2, w20
	and	w0, w0, 127
	strb	w0, [x29, 103]
	mov	w0, 12
	lsl	x25, x25, 2
	ldr	w23, [x29, 100]
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC27
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	x23, .LC28
	sub	x0, x25, x22
	mov	x3, x21
	mov	w2, w20
	add	x25, x25, x0, lsl 2
	mov	w0, 16
	add	x25, x23, x25
	ldr	w27, [x25, 72]
	and	w27, w27, -16
	mov	w1, w27
	bl	MFDE_ConfigReg
	ldr	x1, .LC30
	mov	w2, w27
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x25, 56]
	mov	x3, x21
	mov	w2, w20
	and	w25, w25, -16
	mov	w0, 20
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC32
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x29, 104]
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 24
	bl	MFDE_ConfigReg
	ldr	x1, .LC34
	mov	w2, w25
	mov	w0, 3
	mov	w25, 3075
	movk	w25, 0x30, lsl 16
	bl	dprint_vfmw
	ldrh	w0, [x19, 72]
	mov	x3, x21
	mov	w2, w20
	cmp	w0, 120
	mov	w0, 4
	cset	w1, ls
	bl	SCD_ConfigReg
	str	w25, [x29, 100]
	mov	x3, x21
	mov	w2, w20
	mov	w0, 60
	mov	w1, w25
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w26, 1
	beq	.L101
.L88:
	ldr	w25, [x19, 14464]
	mov	x3, x21
	mov	w2, w20
	mov	w0, 96
	and	w25, w25, -16
	mov	w26, -1
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC40
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x19, 14868]
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 100
	bl	MFDE_ConfigReg
	ldr	x1, .LC42
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x19, 14876]
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 104
	bl	MFDE_ConfigReg
	ldr	x1, .LC44
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x19, 14884]
	mov	x3, x21
	mov	w2, w20
	mov	w1, w25
	mov	w0, 108
	bl	MFDE_ConfigReg
	ldr	x1, .LC46
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	lsl	x0, x22, 6
	mov	x3, x21
	sub	x0, x0, x22
	mov	w2, w20
	lsl	x0, x0, 2
	sub	x25, x0, x22
	add	x0, x0, x25, lsl 2
	add	x25, x23, x0
	mov	w0, 144
	ldr	w27, [x25, 1220]
	mov	w1, w27
	bl	MFDE_ConfigReg
	ldr	x1, .LC48
	mov	w2, w27
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x21
	mov	w2, w20
	mov	w1, 0
	mov	w0, 148
	bl	MFDE_ConfigReg
	ldr	x1, .LC50
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x21
	mov	w2, w20
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC52
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	str	w26, [x29, 100]
	mov	x3, x21
	mov	w2, w20
	mov	w1, w26
	mov	w0, 32
	bl	MFDE_ConfigReg
	ldr	w0, [x25, 72]
	bl	MEM_Phy2Vir
	mov	x21, x0
	cbz	x0, .L102
	ldrh	w2, [x19, 74]
	ldrh	w0, [x29, 102]
	sub	w2, w2, #1
	ldrb	w3, [x19, 40]
	bfi	w0, w2, 0, 9
	ldrb	w2, [x19, 39]
	strh	w0, [x29, 102]
	lsr	x0, x0, 8
	bfi	w0, w3, 1, 2
	ldrh	w1, [x19, 72]
	bfi	w0, w2, 3, 2
	and	w0, w0, 31
	strb	w0, [x29, 103]
	ldrh	w0, [x29, 100]
	sub	w1, w1, #1
	bfi	w0, w1, 0, 9
	strh	w0, [x29, 100]
	ubfx	x0, x0, 8, 1
	strb	w0, [x29, 101]
	ldr	x1, .LC57
	mov	w0, 4
	ldr	w2, [x29, 100]
	str	w2, [x21]
	bl	dprint_vfmw
	str	wzr, [x29, 100]
	ldrb	w2, [x19, 25]
	mov	w0, 0
	ldrb	w1, [x19, 17]
	bfi	w0, w2, 0, 1
	ldrb	w3, [x19, 21]
	bfi	w0, w1, 1, 2
	ldrb	w1, [x19, 16]
	ldrb	w2, [x19, 19]
	bfi	w0, w1, 3, 2
	ldrb	w1, [x19, 24]
	bfi	w0, w1, 5, 1
	ldrb	w1, [x19, 23]
	bfi	w0, w1, 6, 1
	ldrb	w1, [x19, 22]
	bfi	w0, w1, 7, 1
	mov	w1, 0
	bfi	w1, w3, 0, 6
	strb	w0, [x29, 100]
	mov	w0, w1
	mov	w1, 0
	bfi	w1, w2, 0, 1
	ldrb	w2, [x19, 18]
	bfi	w1, w2, 1, 1
	orr	w1, w1, 4
	strb	w1, [x29, 102]
	ldrh	w1, [x29, 102]
	and	w1, w1, 7
	strh	w1, [x29, 102]
	ldrb	w2, [x19, 20]
	ldrb	w1, [x19, 31]
	bfi	w0, w2, 6, 1
	bfi	w0, w1, 7, 1
	strb	w0, [x29, 101]
	ldr	x1, .LC59
	mov	w0, 4
	ldr	w2, [x29, 100]
	str	w2, [x21, 4]
	bl	dprint_vfmw
	str	wzr, [x29, 100]
	ldrb	w2, [x19, 29]
	mov	w0, 0
	ldrb	w1, [x19, 28]
	bfi	w0, w2, 0, 1
	ldrb	w2, [x19, 27]
	bfi	w0, w1, 1, 1
	ldrb	w1, [x19, 26]
	bfi	w0, w2, 2, 5
	strb	w0, [x29, 100]
	ldrh	w0, [x29, 100]
	bfi	w0, w1, 7, 5
	strh	w0, [x29, 100]
	ldr	x1, .LC61
	mov	w0, 4
	ldr	w2, [x29, 100]
	str	w2, [x21, 8]
	bl	dprint_vfmw
	str	wzr, [x29, 100]
	ldrb	w2, [x19, 34]
	mov	w0, 0
	ldrb	w1, [x19, 35]
	bfi	w0, w2, 0, 1
	ldrb	w2, [x19, 36]
	bfi	w0, w1, 1, 2
	ldrb	w1, [x19, 37]
	bfi	w0, w2, 3, 1
	ldrb	w2, [x19, 32]
	bfi	w0, w1, 4, 2
	ldrb	w1, [x19, 33]
	bfi	w0, w2, 6, 1
	strb	w0, [x29, 100]
	ldrh	w0, [x29, 100]
	bfi	w0, w1, 7, 2
	strh	w0, [x29, 100]
	ldr	x1, .LC63
	mov	w0, 4
	ldr	w2, [x29, 100]
	and	w2, w2, 511
	str	w2, [x29, 100]
	str	w2, [x21, 12]
	bl	dprint_vfmw
	ldr	w2, [x19, 14452]
	mov	w0, 4
	ldr	x1, .LC65
	and	w2, w2, -16
	str	w2, [x21, 16]
	bl	dprint_vfmw
	ldr	w2, [x19, 14456]
	mov	w0, 4
	ldr	x1, .LC67
	and	w2, w2, -16
	str	w2, [x21, 20]
	bl	dprint_vfmw
	ldr	w2, [x19, 14460]
	mov	w0, 4
	ldr	x1, .LC69
	and	w2, w2, -16
	str	w2, [x21, 24]
	bl	dprint_vfmw
	ldr	w2, [x19, 14476]
	mov	w0, 4
	ldr	x1, .LC71
	and	w2, w2, -16
	str	w2, [x21, 28]
	bl	dprint_vfmw
	str	wzr, [x29, 100]
	ldrb	w0, [x19, 38]
	mov	w1, 0
	ldrb	w2, [x19, 30]
	bfi	w1, w0, 0, 1
	mov	w0, 0
	bfi	w0, w2, 0, 2
	strb	w1, [x29, 100]
	strb	w0, [x29, 103]
	mov	w0, 4
	ldr	x1, .LC73
	ldr	w2, [x29, 100]
	str	w2, [x21, 32]
	bl	dprint_vfmw
	ldr	w2, [x19, 88]
	mov	w0, 4
	ldr	x1, .LC75
	str	w2, [x21, 36]
	bl	dprint_vfmw
	ldr	w0, [x19, 104]
	mov	w1, 0
	ldr	w2, [x19, 96]
	bfi	w1, w0, 0, 24
	mov	w0, 0
	str	w1, [x29, 100]
	bfi	w0, w2, 0, 7
	strb	w0, [x29, 103]
	mov	w0, 4
	ldr	x1, .LC77
	ldr	w2, [x29, 100]
	str	w2, [x21, 40]
	bl	dprint_vfmw
	ldr	w2, [x19, 92]
	mov	w0, 4
	ldr	x1, .LC79
	str	w2, [x21, 44]
	bl	dprint_vfmw
	str	wzr, [x29, 100]
	ldrb	w0, [x19, 41]
	mov	w1, 0
	ldrb	w2, [x19, 43]
	bfi	w1, w0, 0, 1
	ldrb	w0, [x19, 42]
	ldrb	w3, [x19, 47]
	bfi	w1, w0, 1, 1
	ldrb	w0, [x19, 44]
	bfi	w1, w0, 2, 6
	mov	w0, 0
	bfi	w0, w2, 0, 6
	ldrb	w2, [x19, 45]
	strb	w1, [x29, 100]
	mov	w1, 0
	bfi	w0, w2, 6, 1
	ldrb	w2, [x19, 46]
	bfi	w1, w3, 0, 1
	strb	w1, [x29, 102]
	bfi	w0, w2, 7, 1
	strb	w0, [x29, 101]
	ldr	x1, .LC81
	mov	w0, 4
	ldr	w2, [x29, 100]
	str	w2, [x21, 48]
	bl	dprint_vfmw
	ldr	w2, [x25, 1164]
	mov	w0, 4
	ldr	x1, .LC83
	and	w2, w2, -16
	str	w2, [x21, 52]
	bl	dprint_vfmw
	ldr	w2, [x25, 1168]
	mov	w0, 4
	ldr	x1, .LC85
	and	w2, w2, -16
	str	w2, [x21, 56]
	bl	dprint_vfmw
	ldr	w2, [x19, 14472]
	mov	w0, 4
	ldr	x1, .LC87
	and	w2, w2, -16
	str	w2, [x21, 64]
	bl	dprint_vfmw
	add	x3, x19, 12288
	add	x1, x21, 68
	add	x0, x3, 2196
	add	x3, x3, 2324
	.p2align 2
.L90:
	ldr	w2, [x0], 4
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L90
	ldr	w2, [x19, 14468]
	mov	w0, 4
	ldr	x1, .LC89
	and	w2, w2, -16
	str	w2, [x21, 196]
	bl	dprint_vfmw
	lsl	x2, x22, 6
	ldr	x1, .LC91
	sub	x2, x2, x22
	mov	w0, 4
	lsl	x2, x2, 2
	sub	x22, x2, x22
	add	x2, x2, x22, lsl 2
	add	x23, x23, x2
	ldr	w2, [x23, 1176]
	and	w2, w2, -16
	str	w2, [x21, 200]
	bl	dprint_vfmw
	ldr	w2, [x23, 1160]
	mov	w0, 4
	ldr	x1, .LC93
	and	w2, w2, -16
	str	w2, [x21, 204]
	bl	dprint_vfmw
	ldr	w3, [x23, 72]
	mov	w0, 4
	ldr	x1, .LC95
	add	w3, w3, 320
	str	w3, [x21, 252]
	mov	w2, w3
	str	w3, [x29, 100]
	bl	dprint_vfmw
	ldrb	w0, [x19, 41]
	cmp	w0, 1
	beq	.L103
.L91:
	ldr	w1, [x29, 104]
	mov	w2, w20
	mov	x0, x19
	bl	AVSHAL_V5R2C1_WirteSlicMsg
.L81:
	mov	w0, w24
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L100:
	strb	w1, [x19, 48]
	mov	w2, 0
	str	wzr, [x19, 14904]
	b	.L87
.L83:
	mov	w24, -1
	ldr	x27, [sp, 80]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L101:
	mov	x3, x21
	mov	w2, w20
	mov	w1, 60
	mov	w0, 92
	bl	MFDE_ConfigReg
	ldr	x1, .LC36
	mov	w2, 60
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w25, [x19, 14872]
	mov	w2, w20
	mov	x3, x21
	mov	w1, w25
	mov	w0, 112
	bl	MFDE_ConfigReg
	ldr	x1, .LC38
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	b	.L88
.L103:
	add	x2, x21, 256
	mov	w1, 16
	mov	x0, x19
	bl	AVSHAL_V5R2C1_StartDec_ConfigWQMatrix.part.2
	b	.L91
.L102:
	ldr	x2, .LC20
	mov	w0, 0
	ldr	x3, .LC54
	mov	w24, w26
	ldr	x1, .LC55
	add	x2, x2, 40
	bl	dprint_vfmw
	b	.L81
.L99:
	ldr	x2, .LC20
	mov	x3, x21
	ldr	x1, .LC22
	mov	w0, 0
	add	x2, x2, 40
	mov	w24, -1
	bl	dprint_vfmw
	b	.L81
	.size	AVSHAL_V5R2C1_StartDec, .-AVSHAL_V5R2C1_StartDec
	.align	3
.LC18:
	.xword	g_VdmDrvParam
	.align	3
.LC19:
	.xword	g_HalDisable
	.align	3
.LC20:
	.xword	.LANCHOR0
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	s_pstVfmwChan
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC28:
	.xword	g_HwMem
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC55:
	.xword	.LC5
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11910, %object
	.size	__func__.11910, 34
__func__.11910:
	.string	"AVSHAL_V5R2C1_StartDec_CheckParam"
	.zero	6
	.type	__func__.11958, %object
	.size	__func__.11958, 23
__func__.11958:
	.string	"AVSHAL_V5R2C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC3:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC5:
	ASCII(.string	"%s: %s\n" )
.LC7:
	ASCII(.string	"VdhId is wrong! AVSHAL_V200R003_StartDec\n" )
	.zero	6
.LC10:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC12:
	ASCII(.string	"stream_base_addr = %#x\n" )
.LC21:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC24:
	ASCII(.string	"BASIC_V5R2C1_CFG0 = 0x%x\n" )
	.zero	6
.LC26:
	ASCII(.string	"BASIC_V5R2C1_CFG1 = 0x%x\n" )
	.zero	6
.LC29:
	ASCII(.string	"AVM_V5R2C1_ADDR = 0x%x\n" )
.LC31:
	ASCII(.string	"VAM_V5R2C1_ADDR = 0x%x\n" )
.LC33:
	ASCII(.string	"STREAM_V5R2C1_BASE_ADDR = 0x%x\n" )
.LC35:
	ASCII(.string	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	4
.LC37:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC39:
	ASCII(.string	"YSTADDR_V5R2C1_1D = 0x%x\n" )
	.zero	6
.LC41:
	ASCII(.string	"YSTRIDE_V5R2C1_1D = 0x%x\n" )
	.zero	6
.LC43:
	ASCII(.string	"UVOFFSET_V5R2C1_1D = 0x%x\n" )
	.zero	5
.LC45:
	ASCII(.string	"HEAD_INF_OFFSET = 0x%x\n" )
.LC47:
	ASCII(.string	"VREG_V5R2C1_DNR_MBINFO_STADDR = 0x%x\n" )
	.zero	2
.LC49:
	ASCII(.string	"VREG_V200R003_REF_PIC_TYPE = 0x%x\n" )
	.zero	5
.LC51:
	ASCII(.string	"VREG_V5R2C1_FF_APT_EN = 0x%x\n" )
	.zero	2
.LC53:
	ASCII(.string	"can not map down msg virtual address!" )
	.zero	2
.LC56:
	ASCII(.string	"D0 = 0x%x\n" )
	.zero	5
.LC58:
	ASCII(.string	"D1 = 0x%x\n" )
	.zero	5
.LC60:
	ASCII(.string	"D2 = 0x%x\n" )
	.zero	5
.LC62:
	ASCII(.string	"D3 = 0x%x\n" )
	.zero	5
.LC64:
	ASCII(.string	"D4 = 0x%x\n" )
	.zero	5
.LC66:
	ASCII(.string	"D5 = 0x%x\n" )
	.zero	5
.LC68:
	ASCII(.string	"D6 = 0x%x\n" )
	.zero	5
.LC70:
	ASCII(.string	"D7 = 0x%x\n" )
	.zero	5
.LC72:
	ASCII(.string	"D8 = 0x%x\n" )
	.zero	5
.LC74:
	ASCII(.string	"D9 = 0x%x\n" )
	.zero	5
.LC76:
	ASCII(.string	"D10 = 0x%x\n" )
	.zero	4
.LC78:
	ASCII(.string	"D11 = 0x%x\n" )
	.zero	4
.LC80:
	ASCII(.string	"D12 = 0x%x\n" )
	.zero	4
.LC82:
	ASCII(.string	"D13 = 0x%x\n" )
	.zero	4
.LC84:
	ASCII(.string	"D14 = 0x%x\n" )
	.zero	4
.LC86:
	ASCII(.string	"D16 = 0x%x\n" )
	.zero	4
.LC88:
	ASCII(.string	"D49 = 0x%x\n" )
	.zero	4
.LC90:
	ASCII(.string	"D50 = 0x%x\n" )
	.zero	4
.LC92:
	ASCII(.string	"D51 = 0x%x\n" )
	.zero	4
.LC94:
	ASCII(.string	"D63 = 0x%x\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
