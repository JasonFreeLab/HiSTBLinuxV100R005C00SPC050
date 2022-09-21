#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_avs2.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_WirteOneSlice
	.type	AVS2HAL_WirteOneSlice, %function
AVS2HAL_WirteOneSlice:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w3
	mov	x20, x1
	mov	w24, w2
	bl	_mcount
	ldr	w0, [x22, 8]
	ldr	w21, [x22, 16]
	ldrb	w1, [x22, 24]
	add	w0, w0, 3
	sub	w0, w0, w23
	lsl	w21, w21, 3
	sub	w21, w21, #24
	and	w25, w0, -16
	ubfiz	w19, w0, 3, 4
	cbnz	w1, .L4
	ldr	w0, [x22, 12]
	ldr	w26, [x22, 20]
	sub	w23, w0, w23
	and	w27, w23, -16
	lsl	w26, w26, 3
	ubfiz	w23, w23, 3, 4
.L2:
	ldr	x1, .LC3
	mov	w0, 4
	and	w24, w24, 262143
	bl	dprint_vfmw
	str	wzr, [x20, 24]
	stp	w25, w19, [x20]
	stp	w21, w27, [x20, 8]
	stp	w23, w26, [x20, 16]
	ldr	x21, .LC5
	mov	x19, 0
	ldr	w0, [x22, 4]
	and	w0, w0, 262143
	str	w0, [x20, 28]
	ldrh	w1, [x22, 2]
	ldrh	w0, [x22]
	ubfiz	w1, w1, 16, 9
	and	w0, w0, 511
	orr	w0, w1, w0
	stp	w0, w24, [x20, 32]
	.p2align 2
.L3:
	ldr	w3, [x20, x19, lsl 2]
	mov	w2, w19
	mov	x1, x21
	mov	w0, 4
	add	x19, x19, 1
	bl	dprint_vfmw
	cmp	x19, 10
	bne	.L3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4:
	mov	w23, 0
	mov	w26, 0
	mov	w27, 0
	b	.L2
	.size	AVS2HAL_WirteOneSlice, .-AVS2HAL_WirteOneSlice
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_WirteSlicMsg
	.type	AVS2HAL_WirteSlicMsg, %function
AVS2HAL_WirteSlicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	w24, w2
	bl	_mcount
	ldr	w1, [x20, 1140]
	cbz	w1, .L12
	add	w24, w24, 256
	mov	w23, 1
	mov	w21, 0
	b	.L11
	.p2align 3
.L15:
	ldr	w2, [x0, 1148]
	sub	w2, w2, #1
.L10:
	uxtw	x0, w21
	ubfiz	x22, x21, 8, 26
	lsl	x1, x0, 5
	add	x22, x19, x22
	add	x0, x1, x0, lsl 2
	ldr	w3, [x20, 88]
	add	x0, x20, x0
	mov	x1, x22
	add	x0, x0, 1144
	add	w21, w21, 1
	bl	AVS2HAL_WirteOneSlice
	str	w24, [x22, 252]
	add	w0, w23, 1
	add	w24, w24, 256
	ldr	w1, [x20, 1140]
	cmp	w1, w23
	mov	w23, w0
	bls	.L14
.L11:
	uxtw	x0, w23
	sub	w1, w1, #1
	lsl	x2, x0, 5
	cmp	w1, w21
	add	x0, x2, x0, lsl 2
	add	x0, x20, x0
	bhi	.L15
	ldp	w2, w0, [x20, 108]
	mul	w2, w0, w2
	sub	w2, w2, #1
	b	.L10
	.p2align 3
.L14:
	lsl	w0, w1, 6
	sub	w0, w0, #64
	add	x0, x0, 63
	lsl	x0, x0, 2
.L8:
	str	wzr, [x19, x0]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L12:
	mov	x0, 17179869180
	b	.L8
	.size	AVS2HAL_WirteSlicMsg, .-AVS2HAL_WirteSlicMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_WirtePicMsg
	.type	AVS2HAL_WirtePicMsg, %function
AVS2HAL_WirtePicMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	ldr	x1, .LC10
	mov	w0, 4
	bl	dprint_vfmw
	ldp	w0, w4, [x19, 108]
	add	x1, x19, 400
	add	x2, x20, 24
	sub	w4, w4, #1
	sub	w0, w0, #1
	ubfiz	w4, w4, 16, 9
	and	w0, w0, 511
	orr	w0, w4, w0
	str	w0, [x20]
	add	x3, x19, 428
	ldp	w5, w4, [x19, 120]
	ldp	w0, w6, [x19, 128]
	ubfiz	w4, w4, 9, 7
	ubfiz	w5, w5, 20, 1
	ubfiz	w6, w6, 3, 3
	ubfiz	w0, w0, 8, 1
	orr	w0, w0, w6
	orr	w5, w5, w4
	ldrb	w6, [x19]
	orr	w5, w0, w5
	ldr	w4, [x19, 136]
	ubfiz	w0, w6, 16, 4
	ubfiz	w4, w4, 1, 2
	orr	w0, w0, w4
	orr	w0, w5, w0
	str	w0, [x20, 4]
	ldp	w0, w4, [x19, 140]
	ldp	w5, w6, [x19, 148]
	ubfiz	w4, w4, 18, 1
	ubfiz	w0, w0, 19, 1
	ubfiz	w6, w6, 15, 1
	ubfiz	w5, w5, 16, 2
	orr	w5, w5, w6
	orr	w0, w0, w4
	ldp	w6, w4, [x19, 156]
	orr	w0, w5, w0
	ubfiz	w4, w4, 13, 1
	ubfiz	w5, w6, 14, 1
	orr	w5, w5, w4
	ldp	w6, w4, [x19, 164]
	orr	w5, w0, w5
	ubfiz	w4, w4, 9, 3
	ubfiz	w0, w6, 12, 1
	orr	w0, w0, w4
	ldp	w6, w4, [x19, 172]
	orr	w0, w5, w0
	ubfiz	w4, w4, 5, 3
	ubfiz	w5, w6, 8, 1
	orr	w5, w5, w4
	ldp	w6, w4, [x19, 180]
	orr	w5, w0, w5
	ubfiz	w4, w4, 3, 1
	ubfiz	w0, w6, 4, 1
	orr	w0, w0, w4
	ldr	w4, [x19, 116]
	orr	w0, w5, w0
	and	w4, w4, 7
	orr	w0, w0, w4
	str	w0, [x20, 8]
	ldp	w0, w6, [x19, 188]
	ldp	w5, w4, [x19, 204]
	ubfiz	w6, w6, 14, 1
	ubfiz	w0, w0, 15, 1
	and	w4, w4, 1
	ubfiz	w5, w5, 1, 1
	orr	w0, w0, w6
	orr	w5, w5, w4
	ldp	w6, w4, [x19, 196]
	orr	w5, w0, w5
	ubfiz	w4, w4, 2, 6
	ubfiz	w0, w6, 8, 6
	orr	w0, w0, w4
	orr	w0, w5, w0
	str	w0, [x20, 12]
	ldp	w6, w5, [x19, 212]
	ldp	w0, w4, [x19, 220]
	ubfiz	w6, w6, 7, 5
	ubfiz	w5, w5, 2, 5
	and	w4, w4, 1
	ubfiz	w0, w0, 1, 1
	orr	w5, w6, w5
	orr	w0, w0, w4
	orr	w0, w5, w0
	str	w0, [x20, 16]
	ldr	w4, [x19, 336]
	ldr	w5, [x19, 396]
	ldr	w7, [x19, 340]
	ubfiz	w4, w4, 27, 1
	ldr	w6, [x19, 368]
	ubfiz	w5, w5, 28, 1
	ldr	w0, [x19, 364]
	orr	w5, w5, w4
	ldr	w4, [x19, 392]
	ubfiz	w6, w6, 29, 2
	orr	w6, w6, w7, lsl 31
	ubfiz	w0, w0, 25, 2
	ubfiz	w4, w4, 24, 1
	orr	w5, w6, w5
	orr	w0, w0, w4
	ldr	w6, [x19, 332]
	ldr	w4, [x19, 360]
	orr	w0, w5, w0
	ubfiz	w5, w6, 23, 1
	ldr	w6, [x19, 388]
	ubfiz	w4, w4, 21, 2
	orr	w5, w5, w4
	ldr	w4, [x19, 328]
	orr	w5, w0, w5
	ubfiz	w0, w6, 20, 1
	ubfiz	w4, w4, 19, 1
	ldr	w6, [x19, 356]
	orr	w0, w0, w4
	ldr	w4, [x19, 384]
	orr	w0, w5, w0
	ubfiz	w5, w6, 17, 2
	ubfiz	w4, w4, 16, 1
	ldr	w6, [x19, 324]
	orr	w5, w5, w4
	ldr	w4, [x19, 352]
	orr	w5, w0, w5
	ubfiz	w0, w6, 15, 1
	ubfiz	w4, w4, 13, 2
	ldr	w6, [x19, 380]
	orr	w0, w0, w4
	ldr	w4, [x19, 320]
	orr	w0, w5, w0
	ubfiz	w5, w6, 12, 1
	ubfiz	w4, w4, 11, 1
	ldr	w6, [x19, 348]
	orr	w5, w5, w4
	ldr	w4, [x19, 376]
	orr	w5, w0, w5
	ubfiz	w0, w6, 9, 2
	ubfiz	w4, w4, 8, 1
	ldr	w6, [x19, 316]
	orr	w0, w0, w4
	ldr	w4, [x19, 344]
	orr	w0, w5, w0
	ubfiz	w5, w6, 7, 1
	ubfiz	w4, w4, 5, 2
	ldr	w6, [x19, 372]
	orr	w5, w5, w4
	ldr	w4, [x19, 228]
	orr	w5, w0, w5
	ubfiz	w0, w6, 4, 1
	ubfiz	w4, w4, 3, 1
	orr	w0, w0, w4
	ldr	w4, [x19, 236]
	orr	w0, w5, w0
	and	w4, w4, 1
	orr	w0, w0, w4
	str	w0, [x20, 20]
	.p2align 2
.L17:
	ldr	w0, [x1], 4
	and	w0, w0, -16
	cmp	x1, x3
	str	w0, [x2], 4
	bne	.L17
	ldp	w1, w3, [x19, 100]
	uxtw	x2, w21
	ldr	x6, .LC11
	ubfiz	w3, w3, 16, 14
	and	w1, w1, 16383
	orr	w1, w3, w1
	str	w1, [x20, 52]
	lsl	x0, x2, 6
	add	x5, x20, 88
	ldp	w3, w4, [x19, 100]
	sub	x0, x0, x2
	add	x8, x19, 1100
	lsl	x0, x0, 2
	add	w4, w4, 7
	sub	x2, x0, x2
	add	w3, w3, 7
	lsr	w4, w4, 3
	lsr	w3, w3, 3
	add	x2, x0, x2, lsl 2
	sub	w4, w4, #1
	sub	w3, w3, #1
	add	x0, x6, x2
	ubfiz	w4, w4, 16, 10
	and	w2, w3, 1023
	orr	w2, w4, w2
	str	w2, [x20, 56]
	add	x1, x19, 524
	ldr	w2, [x0, 1108]
	and	w2, w2, -16
	str	w2, [x20, 60]
	ldr	w2, [x0, 1112]
	and	w2, w2, -16
	str	w2, [x20, 64]
	ldr	w2, [x0, 1120]
	and	w2, w2, -16
	str	w2, [x20, 68]
	ldr	w0, [x0, 1144]
	and	w0, w0, -16
	stp	w0, wzr, [x20, 72]
	ldr	w0, [x19, 240]
	and	w0, w0, -16
	str	w0, [x20, 80]
	ldr	w0, [x19, 244]
	and	w0, w0, -16
	str	w0, [x20, 84]
	.p2align 2
.L18:
	ldp	w7, w4, [x1, -24]
	ldp	w3, w2, [x1, -32]
	ldr	w6, [x1]
	ubfiz	w0, w7, 14, 7
	ubfiz	w4, w4, 21, 7
	ubfiz	w2, w2, 7, 7
	orr	w2, w0, w2
	add	x5, x5, 8
	orr	w4, w4, w6, lsl 28
	orr	w0, w4, w2
	and	w2, w3, 127
	orr	w0, w0, w2
	str	w0, [x5, -8]
	ldp	w2, w6, [x1, -16]
	ldp	w4, w7, [x1, -8]
	ldr	w3, [x1], 36
	ubfiz	w0, w6, 7, 7
	ubfiz	w7, w7, 21, 7
	ubfiz	w4, w4, 14, 7
	and	w2, w2, 127
	orr	w4, w7, w4
	orr	w2, w0, w2
	ubfx	x3, x3, 4, 3
	orr	w0, w4, w2
	cmp	x1, x8
	orr	w0, w0, w3, lsl 28
	str	w0, [x5, -4]
	bne	.L18
	add	x4, x20, 216
	add	x6, x19, 1172
.L19:
	ldp	w2, w1, [x8, -32]
	ldp	w0, w3, [x8, -24]
	ldr	w5, [x8]
	ubfiz	w1, w1, 7, 7
	ubfiz	w3, w3, 21, 7
	ubfiz	w0, w0, 14, 7
	orr	w0, w0, w1
	and	w1, w2, 127
	orr	w3, w3, w5, lsl 28
	add	x4, x4, 8
	orr	w0, w3, w0
	orr	w0, w0, w1
	str	w0, [x4, -8]
	ldp	w1, w0, [x8, -16]
	ldp	w3, w5, [x8, -8]
	ldr	w2, [x8], 36
	ubfiz	w0, w0, 7, 7
	ubfiz	w5, w5, 21, 7
	ubfiz	w3, w3, 14, 7
	and	w1, w1, 127
	orr	w3, w5, w3
	orr	w1, w0, w1
	ubfx	x2, x2, 4, 3
	orr	w0, w3, w1
	cmp	x6, x8
	orr	w0, w0, w2, lsl 28
	str	w0, [x4, -4]
	bne	.L19
	add	x0, x19, 430
	add	x1, x20, 256
	add	x4, x19, 446
	.p2align 2
.L20:
	ldrh	w3, [x0]
	add	x1, x1, 4
	ldrh	w2, [x0, -2]
	add	x0, x0, 4
	ubfiz	w3, w3, 16, 10
	cmp	x0, x4
	and	w2, w2, 1023
	orr	w2, w3, w2
	str	w2, [x1, -4]
	ldrh	w3, [x0, 12]
	ldrh	w2, [x0, 10]
	ubfiz	w3, w3, 16, 10
	and	w2, w2, 1023
	orr	w2, w3, w2
	str	w2, [x1, 12]
	ldrh	w3, [x0, 28]
	ldrh	w2, [x0, 26]
	ubfiz	w3, w3, 16, 15
	and	w2, w2, 32767
	orr	w2, w3, w2
	str	w2, [x1, 28]
	ldrh	w3, [x0, 44]
	ldrh	w2, [x0, 42]
	ubfiz	w3, w3, 16, 15
	and	w2, w2, 32767
	orr	w2, w3, w2
	str	w2, [x1, 44]
	bne	.L20
	add	x0, x19, 256
	ldr	w6, [x19, 256]
	ldp	w7, w2, [x19, 248]
	ubfiz	w6, w6, 7, 1
	ldp	w1, w3, [x0, 40]
	ldp	w5, w4, [x0, 48]
	ldr	w0, [x19, 312]
	ubfiz	w2, w2, 8, 1
	ubfiz	w7, w7, 9, 2
	ubfiz	w4, w4, 5, 1
	ubfiz	w0, w0, 6, 1
	orr	w7, w7, w2
	orr	w6, w6, w0
	ldr	w2, [x19, 292]
	ldr	w0, [x19, 288]
	ubfiz	w5, w5, 4, 1
	ubfiz	w3, w3, 3, 1
	orr	w6, w7, w6
	orr	w4, w4, w5
	ubfiz	w1, w1, 2, 1
	orr	w4, w6, w4
	orr	w1, w3, w1
	ubfiz	w2, w2, 1, 1
	and	w0, w0, 1
	orr	w3, w4, w1
	orr	w0, w2, w0
	orr	w2, w3, w0
	add	x1, x20, 360
	str	w2, [x20, 356]
	add	x4, x20, 392
	add	x0, x19, 5
	mov	x2, x1
.L21:
	ldrb	w3, [x0, 8]
	add	x2, x2, 8
	ldrb	w5, [x0]
	add	x0, x0, 1
	cmp	x2, x4
	orr	w3, w5, w3, lsl 8
	str	w3, [x2, -8]
	ldrb	w3, [x0, 11]
	ldrb	w5, [x0, 3]
	orr	w3, w5, w3, lsl 8
	str	w3, [x2, -4]
	bne	.L21
	add	x0, x19, 21
	add	x3, x20, 520
	mov	x2, x0
	.p2align 2
.L22:
	ldrb	w5, [x2, 16]
	add	x4, x4, 16
	ldrb	w6, [x2]
	add	x2, x2, 1
	cmp	x3, x4
	orr	w5, w6, w5, lsl 8
	str	w5, [x4, -16]
	ldrb	w5, [x2, 47]
	ldrb	w6, [x2, 31]
	orr	w5, w6, w5, lsl 8
	str	w5, [x4, -12]
	ldrb	w5, [x2, 23]
	ldrb	w6, [x2, 7]
	orr	w5, w6, w5, lsl 8
	str	w5, [x4, -8]
	ldrb	w5, [x2, 55]
	ldrb	w6, [x2, 39]
	orr	w5, w6, w5, lsl 8
	str	w5, [x4, -4]
	bne	.L22
	add	x5, x20, 648
	.p2align 2
.L23:
	ldrb	w2, [x0, 8]
	add	x3, x3, 16
	ldrb	w4, [x0]
	add	x0, x0, 1
	cmp	x5, x3
	orr	w2, w4, w2, lsl 8
	str	w2, [x3, -16]
	ldrb	w2, [x0, 23]
	ldrb	w4, [x0, 15]
	orr	w2, w4, w2, lsl 8
	str	w2, [x3, -12]
	ldrb	w2, [x0, 39]
	ldrb	w4, [x0, 31]
	orr	w2, w4, w2, lsl 8
	str	w2, [x3, -8]
	ldrb	w2, [x0, 55]
	ldrb	w4, [x0, 47]
	orr	w2, w4, w2, lsl 8
	str	w2, [x3, -4]
	bne	.L23
	ldr	x3, .LC12
	mov	x2, 288
	add	x0, x20, 768
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2HAL_WirtePicMsg, .-AVS2HAL_WirtePicMsg
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC11:
	.xword	g_HwMem
	.align	3
.LC12:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_StartDec_GetStrmAddr
	.type	AVS2HAL_StartDec_GetStrmAddr, %function
AVS2HAL_StartDec_GetStrmAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w6, [x19, 1140]
	cbz	w6, .L32
	mov	w3, 0
	mov	w4, 0
	mov	w8, 36
	mov	x7, 1152
	.p2align 2
.L33:
	smaddl	x0, w3, w8, x7
	mov	w2, 0
	add	x0, x19, x0
.L35:
	ldr	w1, [x0]
	add	w2, w2, 1
	cbz	w1, .L34
	ldr	w5, [x0, 8]
	and	w1, w1, -16
	cmp	w1, w4
	ccmp	w4, wzr, 4, hi
	cbz	w5, .L34
	csel	w4, w4, w1, ne
.L34:
	cmp	w2, 2
	add	x0, x0, 4
	bne	.L35
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L33
	cbz	w4, .L32
	mov	w0, 0
	str	w4, [x19, 88]
.L38:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L32:
	ldr	x2, .LC13
	mov	w0, 0
	ldr	x1, .LC15
	bl	dprint_vfmw
	mov	w0, -1
	b	.L38
	.size	AVS2HAL_StartDec_GetStrmAddr, .-AVS2HAL_StartDec_GetStrmAddr
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC15:
	.xword	.LC14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_WirteReg
	.type	AVS2HAL_WirteReg, %function
AVS2HAL_WirteReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	x20, x2
	bl	_mcount
	mov	x0, x21
	bl	AVS2HAL_StartDec_GetStrmAddr
	cbz	w0, .L53
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L53:
	ldp	w22, w1, [x21, 108]
	mov	x3, x20
	mov	w0, 8
	mov	w2, w19
	mul	w22, w1, w22
	sub	w22, w22, #1
	and	w22, w22, 1048575
	orr	w22, w22, 1073741824
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC17
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldrb	w22, [x21, 4]
	ldrb	w2, [x21, 2]
	mov	w1, 49167
	ldrb	w0, [x21, 1]
	movk	w1, 0x3, lsl 16
	ubfiz	w3, w2, 30, 1
	ubfiz	w22, w22, 28, 1
	ubfiz	w0, w0, 12, 1
	orr	w2, w22, w3
	orr	w0, w0, w1
	mov	x3, x20
	orr	w22, w2, w0
	strb	wzr, [x21, 3]
	mov	w1, w22
	mov	w0, 12
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC19
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	sxtw	x1, w19
	ldr	x4, .LC20
	lsl	x22, x1, 6
	mov	x3, x20
	sub	x22, x22, x1
	mov	w0, 16
	lsl	x22, x22, 2
	mov	w2, w19
	sub	x1, x22, x1
	add	x1, x22, x1, lsl 2
	add	x22, x4, x1
	ldr	w23, [x22, 72]
	and	w23, w23, -16
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC22
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x22, 56]
	mov	x3, x20
	mov	w0, 20
	and	w22, w22, -16
	mov	w2, w19
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC24
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 88]
	mov	x3, x20
	mov	w0, 24
	and	w22, w22, -16
	mov	w2, w19
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC26
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 60
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 64
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 68
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 72
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 76
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	x3, x20
	mov	w2, w19
	mov	w0, 80
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	mov	w1, 3075
	mov	w0, 84
	mov	x3, x20
	mov	w2, w19
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	ldrb	w0, [x21, 4]
	cmp	w0, 1
	beq	.L54
.L51:
	ldr	w22, [x21, 92]
	mov	x3, x20
	mov	w0, 96
	mov	w2, w19
	and	w22, w22, -256
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC33
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 260]
	mov	x3, x20
	mov	w0, 100
	mov	w1, w22
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC35
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 268]
	mov	x3, x20
	mov	w0, 104
	mov	w1, w22
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC37
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 272]
	mov	x3, x20
	mov	w0, 108
	mov	w2, w19
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC39
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 10
	beq	.L55
.L52:
	ldr	w1, [x21, 100]
	mov	x3, x20
	mov	w2, w19
	mov	w0, 4
	cmp	w1, 4096
	cset	w1, ls
	bl	SCD_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, 0
	mov	w0, 148
	bl	MFDE_ConfigReg
	ldr	x1, .LC47
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w19
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC49
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w19
	mov	w1, -1
	mov	w0, 32
	bl	MFDE_ConfigReg
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L54:
	ldr	x1, .LC27
	mov	x3, x20
	mov	w2, w19
	mov	w0, 92
	ldr	w22, [x1]
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC29
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 96]
	mov	w2, w19
	mov	w0, 112
	mov	w1, w22
	mov	x3, x20
	bl	MFDE_ConfigReg
	ldr	x1, .LC31
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	b	.L51
	.p2align 3
.L55:
	ldr	w22, [x21, 276]
	mov	x3, x20
	mov	w2, w19
	mov	w0, 116
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC41
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 280]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, 120
	bl	MFDE_ConfigReg
	ldr	x1, .LC43
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 284]
	mov	w2, w19
	mov	w0, 124
	mov	w1, w22
	mov	x3, x20
	bl	MFDE_ConfigReg
	ldr	x1, .LC45
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	b	.L52
	.size	AVS2HAL_WirteReg, .-AVS2HAL_WirteReg
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC20:
	.xword	g_HwMem
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC27:
	.xword	g_TunnelLineNumber
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_V5R6C1_StartDec
	.type	AVS2HAL_V5R6C1_StartDec, %function
AVS2HAL_V5R6C1_StartDec:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	ldr	x0, .LC50
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L57
	cbz	x20, .L72
	ldrb	w0, [x19, 4]
	strb	w0, [x20, 1]
.L57:
	ldr	w0, [x19, 100]
	cmp	w0, 8192
	bhi	.L61
	ldr	w0, [x19, 104]
	cmp	w0, 8192
	bhi	.L61
	ldr	w0, [x19, 1140]
	sub	w0, w0, #1
	cmp	w0, 254
	bhi	.L73
	cbz	w21, .L64
	cmp	w21, 1
	bne	.L74
	ldr	x2, .LC51
	mov	w4, 0
	ldr	x1, .LC63
	mov	w3, w21
	add	x2, x2, 32
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.p2align 3
.L64:
	ldr	x21, .LC64
	ldr	x0, [x21]
	cbz	x0, .L75
.L66:
	mov	x2, x20
	mov	w1, 0
	mov	x0, x19
	bl	AVS2HAL_WirteReg
	ldr	w20, [x21, 72]
	mov	w0, w20
	bl	MEM_Phy2Vir
	mov	x21, x0
	cbz	x0, .L76
	mov	x2, x0
	mov	x1, x19
	mov	w0, 0
	add	w20, w20, 1280
	bl	AVS2HAL_WirtePicMsg
	str	w20, [x21, 252]
	mov	x0, x19
	mov	w2, w20
	add	x1, x21, 1280
	bl	AVS2HAL_WirteSlicMsg
	mov	w0, 0
.L59:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L74:
	ldr	x1, .LC61
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L75:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	str	x0, [x21]
	cbnz	x0, .L66
	ldr	x1, .LC66
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.p2align 3
.L61:
	ldr	x2, .LC51
	ldr	x3, .LC55
.L71:
	ldr	x1, .LC57
	mov	w0, 0
	add	x2, x2, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.p2align 3
.L73:
	ldr	x2, .LC51
	ldr	x3, .LC59
	b	.L71
.L76:
	ldr	x2, .LC51
	ldr	x3, .LC68
	b	.L71
.L72:
	ldr	x2, .LC51
	mov	x3, 0
	ldr	x1, .LC53
	mov	w0, 0
	add	x2, x2, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.size	AVS2HAL_V5R6C1_StartDec, .-AVS2HAL_V5R6C1_StartDec
	.align	3
.LC50:
	.xword	g_HalDisable
	.align	3
.LC51:
	.xword	.LANCHOR0
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC55:
	.xword	.LC54
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
.LC64:
	.xword	g_HwMem
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2HAL_V5R6C1_InitHal
	.type	AVS2HAL_V5R6C1_InitHal, %function
AVS2HAL_V5R6C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	AVS2HAL_V5R6C1_InitHal, .-AVS2HAL_V5R6C1_InitHal
	.global	Avs2_BitMask
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.12489, %object
	.size	__func__.12489, 29
__func__.12489:
	.string	"AVS2HAL_StartDec_GetStrmAddr"
	.zero	3
	.type	__func__.12528, %object
	.size	__func__.12528, 24
__func__.12528:
	.string	"AVS2HAL_V5R6C1_StartDec"
	.type	Avs2_BitMask, %object
	.size	Avs2_BitMask, 132
Avs2_BitMask:
	.word	0
	.word	1
	.word	3
	.word	7
	.word	15
	.word	31
	.word	63
	.word	127
	.word	255
	.word	511
	.word	1023
	.word	2047
	.word	4095
	.word	8191
	.word	16383
	.word	32767
	.word	65535
	.word	131071
	.word	262143
	.word	524287
	.word	1048575
	.word	2097151
	.word	4194303
	.word	8388607
	.word	16777215
	.word	33554431
	.word	67108863
	.word	134217727
	.word	268435455
	.word	536870911
	.word	1073741823
	.word	2147483647
	.word	-1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"Slice down message:\n" )
	.zero	3
.LC4:
	ASCII(.string	"D%d  =  0x%x\n" )
	.zero	2
.LC9:
	ASCII(.string	"Picture down message:\n" )
	.zero	1
.LC14:
	ASCII(.string	"%s can not find stream_base_addr\n" )
	.zero	6
.LC16:
	ASCII(.string	"VREG_V5R6C1_BASIC_CFG0 = 0x%x\n" )
	.zero	1
.LC18:
	ASCII(.string	"VREG_V5R6C1_BASIC_CFG1 = 0x%x\n" )
	.zero	1
.LC21:
	ASCII(.string	"VREG_V5R6C1_AVM_ADDR = 0x%x\n" )
	.zero	3
.LC23:
	ASCII(.string	"VREG_V5R6C1_VAM_ADDR = 0x%x\n" )
	.zero	3
.LC25:
	ASCII(.string	"VREG_V5R6C1_STREAM_BASE_ADDR = 0x%x\n" )
	.zero	3
.LC28:
	ASCII(.string	"VREG_V5R6C1_PART_DEC_OVER_INT_LEVEL = 0x%x\n" )
	.zero	4
.LC30:
	ASCII(.string	"VREG_V5R6C1_LINE_NUM_STADDR = 0x%x\n" )
	.zero	4
.LC32:
	ASCII(.string	"VREG_V5R6C1_YSTADDR_1D = 0x%x\n" )
	.zero	1
.LC34:
	ASCII(.string	"VREG_V5R6C1_YSTRIDE_1D = 0x%x\n" )
	.zero	1
.LC36:
	ASCII(.string	"VREG_V5R6C1_UVOFFSET_1D = 0x%x\n" )
.LC38:
	ASCII(.string	"VREG_V5R6C1_HEAD_INF_OFFSET = 0x%x\n" )
	.zero	4
.LC40:
	ASCII(.string	"VREG_V5R6C1_YSTRIDE_2BIT = 0x%x\n" )
	.zero	7
.LC42:
	ASCII(.string	"VREG_V5R6C1_YOFFSET_2BIT = 0x%x\n" )
	.zero	7
.LC44:
	ASCII(.string	"VREG_V5R6C1_UVOFFSET_2BIT = 0x%x\n" )
	.zero	6
.LC46:
	ASCII(.string	"VREG_V5R6C1_REF_PIC_TYPE = 0x%x\n" )
	.zero	7
.LC48:
	ASCII(.string	"VREG_V5R6C1_FF_APT_EN = 0x%x\n" )
	.zero	2
.LC52:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC54:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC56:
	ASCII(.string	"%s: %s\n" )
.LC58:
	ASCII(.string	"SliceNum out of range" )
	.zero	2
.LC60:
	ASCII(.string	"VdhId is wrong! AVS2HAL_V5R6C1_StartDec\n" )
	.zero	7
.LC62:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC65:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC67:
	ASCII(.string	"can not map down msg virtual address!" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
