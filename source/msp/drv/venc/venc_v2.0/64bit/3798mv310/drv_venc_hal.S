#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"drv_venc_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	DRV_VENC_HAL_SetDefaultAttrByStartQP, %function
DRV_VENC_HAL_SetDefaultAttrByStartQP:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	w22, w2
	bl	_mcount
	mov	x19, 0
	cmp	w21, 25
	bls	.L2
	sub	w0, w21, #26
	mov	x19, 1
	cmp	w0, 3
	bls	.L2
	sub	w0, w21, #30
	mov	x19, 2
	cmp	w0, 4
	bls	.L2
	sub	w21, w21, #35
	mov	x0, 3
	mov	x19, 4
	cmp	w21, 7
	csel	x19, x0, x19, cc
.L2:
	cmp	w22, wzr
	lsl	x3, x19, 2
	cset	x0, eq
	sub	x3, x3, x19
	lsl	x21, x0, 5
	mov	x2, 404
	add	x1, x21, x0, lsl 3
	lsl	x0, x3, 3
	sub	x3, x0, x3
	lsl	x21, x1, 6
	add	x21, x1, x21
	lsl	x0, x19, 3
	add	x3, x21, x3, lsl 2
	sub	x0, x0, x19
	add	x3, x20, x3
	lsl	x0, x0, 1
	add	x3, x3, 520
	sub	x0, x0, x19
	add	x1, x19, x0, lsl 5
	ldp	x4, x5, [x3]
	stp	x4, x5, [x20]
	sub	x1, x1, x0
	add	x0, x20, 84
	ldp	x4, x5, [x3, 16]
	stp	x4, x5, [x20, 16]
	add	x1, x1, x21
	ldp	x4, x5, [x3, 32]
	stp	x4, x5, [x20, 32]
	add	x1, x20, x1
	ldp	x4, x5, [x3, 48]
	stp	x4, x5, [x20, 48]
	add	x1, x1, 940
	ldp	x4, x5, [x3, 64]
	stp	x4, x5, [x20, 64]
	ldr	w3, [x3, 80]
	str	w3, [x20, 80]
	bl	memcpy
	add	x0, x19, 76
	add	x1, x20, 488
	add	x19, x21, x0, lsl 5
	add	x19, x20, x19
	add	x19, x19, 528
	ldp	x2, x3, [x19]
	stp	x2, x3, [x1]
	ldp	x2, x3, [x19, 16]
	stp	x2, x3, [x1, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	DRV_VENC_HAL_SetDefaultAttrByStartQP, .-DRV_VENC_HAL_SetDefaultAttrByStartQP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	DRV_VENC_HAL_SetDefaultAttrByProtocol, %function
DRV_VENC_HAL_SetDefaultAttrByProtocol:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC2
	add	x2, x19, 168
	cbz	w20, .L9
	mov	w3, 18
	add	x0, x1, 4
	add	x4, x1, 160
	b	.L10
	.p2align 3
.L16:
	ldr	w3, [x0], 4
.L10:
	str	w3, [x2], 4
	cmp	x0, x4
	bne	.L16
	add	x0, x1, 484
	add	x2, x19, 328
	add	x1, x1, 640
	mov	w3, 193
	b	.L17
	.p2align 3
.L19:
	ldr	w3, [x0], 4
.L17:
	str	w3, [x2], 4
	cmp	x0, x1
	bne	.L19
	mov	w0, 255
	mov	w2, 3
	mov	w1, 5
	str	w0, [x19, 164]
	stp	wzr, wzr, [x19, 108]
	stp	wzr, w2, [x19, 116]
	stp	w2, w1, [x19, 124]
	stp	w0, w0, [x19, 148]
	stp	w0, w0, [x19, 156]
	mov	w7, 2
	mov	w6, 96
	stp	w7, wzr, [x19, 100]
	str	w6, [x19, 516]
	mov	w5, 10
	mov	w4, 15
	mov	w3, 20
	stp	w1, w5, [x19, 132]
	stp	w4, w3, [x19, 140]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L9:
	mov	w3, 1
	add	x0, x1, 164
	add	x4, x1, 320
	b	.L13
	.p2align 3
.L11:
	ldr	w3, [x0], 4
.L13:
	str	w3, [x2], 4
	cmp	x0, x4
	bne	.L11
	add	x0, x1, 324
	add	x2, x19, 328
	add	x1, x1, 480
	mov	w3, 1
	b	.L12
	.p2align 3
.L20:
	ldr	w3, [x0], 4
.L12:
	str	w3, [x2], 4
	cmp	x0, x1
	bne	.L20
	mov	w1, 7
	mov	w0, 255
	stp	wzr, wzr, [x19, 108]
	stp	wzr, wzr, [x19, 116]
	stp	w1, w1, [x19, 124]
	stp	w0, w0, [x19, 156]
	str	w0, [x19, 164]
	mov	w8, 4
	mov	w7, 32
	mov	w6, 9
	stp	w8, wzr, [x19, 100]
	stp	w1, w6, [x19, 132]
	str	w7, [x19, 516]
	mov	w5, 11
	mov	w4, 14
	mov	w3, 18
	stp	w5, w4, [x19, 140]
	mov	w2, 25
	stp	w3, w2, [x19, 148]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_SetDefaultAttrByProtocol, .-DRV_VENC_HAL_SetDefaultAttrByProtocol
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	DRV_VENC_HAL_DirectCfgReg, %function
DRV_VENC_HAL_DirectCfgReg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC7
	ldr	x3, .LC7
	ldr	w2, [x20, 540]
	ldr	x0, [x0, 8]
	ldr	w1, [x20, 548]
	add	x21, x0, 704
	str	x0, [x29, 104]
	mov	x0, x21
	ldr	x19, [x3]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	ldr	w1, [x20, 8]
	mov	x0, x21
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	w0, [x20, 44]
	cbnz	w0, .L82
.L22:
	ldr	w0, [x20, 8]
	cbz	w0, .L83
.L25:
	mov	w0, 7
	str	wzr, [x21, 5728]
	str	w0, [x21, 5724]
	str	wzr, [x21, 5732]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	beq	.L28
.L91:
	ldr	x0, [x29, 104]
	add	x30, x0, 4096
.L32:
	ldr	w3, [x20, 44]
	mov	w2, 11
	mov	w0, 2
	bfi	w2, w3, 10, 1
	orr	w2, w2, 134217728
	str	w2, [x19, 4]
	ldr	w3, [x20, 8]
	ldr	w4, [x21, 5732]
	cmp	w3, w0
	cset	w2, ne
	bfi	w0, w2, 3, 2
	ldr	w2, [x20, 44]
	bfi	w0, w2, 5, 1
	ldr	w2, [x30, 4068]
	bfi	w0, w2, 6, 1
	ldr	w2, [x30, 4064]
	bfi	w0, w2, 7, 1
	ldr	x2, [x29, 104]
	and	w0, w0, -16777473
	ldr	w2, [x2, 6536]
	bfi	w0, w2, 9, 1
	ldr	w2, [x20, 540]
	cmp	w2, wzr
	cset	w5, eq
	cmp	w3, 2
	bfi	w0, w5, 10, 2
	ldr	w3, [x21, 5728]
	bfi	w0, w4, 12, 1
	mov	w5, 0
	bfi	w0, w2, 16, 1
	mov	w2, 2
	orr	w0, w0, 131072
	csel	w2, w2, wzr, eq
	bfi	w0, w3, 18, 2
	ldr	w3, [x20, 48]
	and	w0, w0, -6291457
	and	w0, w0, -33554433
	bfi	w0, w2, 26, 2
	mov	w2, 0
	bfi	w0, w3, 28, 2
	and	w0, w0, 1073741823
	str	w0, [x19, 20]
	str	w2, [x19, 24]
	mov	w0, 458752
	ldr	w3, [x20, 24]
	ldr	w4, [x20, 32]
	ubfiz	w3, w3, 17, 1
	bfi	w3, w4, 0, 16
	str	w3, [x19, 28]
	mov	w3, 0
	mov	w4, 0
	ldr	w6, [x20, 548]
	bfi	w2, w6, 10, 6
	ldr	w6, [x30, 3472]
	bfi	w2, w6, 18, 1
	ldr	w6, [x30, 3456]
	bfi	w2, w6, 19, 1
	str	w2, [x19, 32]
	str	wzr, [x19, 36]
	mov	w2, 0
	str	wzr, [x19, 40]
	str	w5, [x19, 44]
	ldr	w5, [x30, 4172]
	bfi	w0, w5, 19, 2
	ldr	w5, [x30, 4176]
	bfi	w0, w5, 21, 1
	and	w0, w0, -8388609
	str	w0, [x19, 48]
	ldr	w0, [x20, 20]
	sub	w0, w0, #1
	bfi	w3, w0, 16, 13
	ldr	w0, [x20, 16]
	sub	w0, w0, #1
	bfi	w3, w0, 0, 13
	str	w3, [x19, 52]
	str	w4, [x19, 56]
	ldr	w0, [x30, 4180]
	str	w0, [x19, 60]
	ldr	w3, [x30, 4080]
	ldr	w0, [x30, 4084]
	bfi	w2, w3, 4, 4
	bfi	w2, w0, 0, 4
	str	w2, [x19, 64]
	ldr	w0, [x20, 8]
	cmp	w0, 2
	beq	.L84
	cbz	w0, .L85
.L36:
	mov	w2, 3
	mov	w0, 0
	str	w22, [x19, 88]
	mov	w3, 1
	bfi	w0, w2, 0, 3
	str	w2, [x19, 92]
	bfi	w0, w3, 3, 2
	mov	w1, w3
	bfi	w0, w2, 5, 3
	str	w1, [x19, 96]
	bfi	w0, w2, 8, 3
	str	w0, [x19, 100]
	mov	w5, 0
	mov	w0, 0
	ldr	w1, [x20, 200]
	mov	w6, 0
	str	w1, [x19, 184]
	mov	w4, 0
	mov	w3, 0
	mov	w1, 0
	ldr	w7, [x20, 72]
	str	w7, [x19, 188]
	ldr	w7, [x20, 76]
	str	w7, [x19, 192]
	ldr	w7, [x20, 80]
	str	w7, [x19, 196]
	ldr	w7, [x20, 84]
	bfi	w5, w7, 16, 16
	ldr	w7, [x20, 88]
	bfi	w5, w7, 0, 16
	str	w5, [x19, 208]
	ldr	w5, [x20, 172]
	add	x5, x5, 40
	ldr	w5, [x20, x5, lsl 2]
	str	w5, [x19, 212]
	ldr	w5, [x20, 140]
	add	x5, x20, x5, lsl 2
	ldr	w5, [x5, 92]
	str	w5, [x19, 216]
	ldr	w5, [x20, 140]
	add	x5, x20, x5, lsl 2
	ldr	w5, [x5, 100]
	str	w5, [x19, 220]
	ldr	w5, [x20, 108]
	bfi	w0, w5, 0, 16
	ldr	w5, [x20, 112]
	bfi	w0, w5, 16, 16
	str	w0, [x19, 224]
	ldr	w0, [x20, 140]
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 116]
	str	w0, [x19, 228]
	ldr	w0, [x20, 140]
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 124]
	str	w0, [x19, 232]
	ldr	w0, [x20, 132]
	bfi	w6, w0, 0, 16
	str	w6, [x19, 236]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 20
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 12]
	str	w0, [x19, 240]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 24
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 4]
	str	w0, [x19, 244]
	ldr	w0, [x20, 112]
	bfi	w4, w0, 0, 16
	ldr	w0, [x20, 108]
	bfi	w4, w0, 16, 16
	str	w4, [x19, 248]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 28
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 4]
	str	w0, [x19, 252]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 28
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 12]
	str	w0, [x19, 256]
	ldr	w0, [x20, 132]
	bfi	w3, w0, 16, 16
	ldr	w0, [x20, 136]
	bfi	w3, w0, 0, 16
	str	w3, [x19, 260]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 36
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 8]
	str	w0, [x19, 264]
	ldr	w0, [x20, 140]
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 152]
	str	w0, [x19, 268]
	ldr	w0, [x20, 140]
	add	x0, x0, 36
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 276]
	ldr	w0, [x20, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 36
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 280]
	ldr	w0, [x20, 204]
	str	w0, [x19, 284]
	ldr	w0, [x20, 336]
	str	w0, [x19, 288]
	ldr	w0, [x20, 332]
	str	w0, [x19, 292]
	ldr	w0, [x20, 64]
	cmp	w0, 2
	beq	.L37
	cmp	w0, 1
	beq	.L71
	and	w1, w1, -961
	and	w1, w1, -16385
	cbnz	w0, .L38
	ldr	w0, [x20, 68]
	cmp	w0, wzr
	cset	w2, eq
.L39:
	add	x0, x30, 2440
	bfi	w1, w2, 16, 8
	str	w1, [x19, 296]
	mov	w1, 0
	mov	w4, 3
	mov	w6, 1
	ldr	w3, [x21, 5724]
	mov	w12, 0
	ldr	w2, [x0, 1620]
	mov	w11, 0
	bfi	w1, w3, 0, 3
	mov	w3, 5
	bfi	w1, w2, 4, 1
	mov	w2, 0
	and	w1, w1, -33
	bfi	w2, w3, 24, 8
	orr	w1, w1, 1792
	bfi	w2, w3, 16, 8
	orr	w1, w1, 28672
	str	w1, [x19, 316]
	str	w4, [x19, 320]
	mov	w1, 24
	mov	w3, 15
	str	w1, [x19, 324]
	mov	w1, 500
	bfi	w2, w3, 8, 8
	movk	w1, 0x64, lsl 16
	str	w1, [x19, 328]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 332]
	mov	w2, 0
	mov	w4, 0
	ldr	w1, [x0, 4]
	mov	w14, 0
	mov	w9, 0
	mov	w10, 0
	bfi	w2, w1, 0, 1
	ldr	w1, [x21, 4]
	mov	w15, 0
	mov	w28, 0
	bfi	w2, w1, 1, 1
	ldr	x1, [x29, 104]
	mov	w27, 0
	mov	w26, 0
	mov	w25, 0
	mov	w24, 0
	ldr	w1, [x1, 704]
	bfi	w2, w1, 2, 1
	mov	w1, 0
	orr	w2, w2, 8
	and	w2, w2, -17
	str	w2, [x19, 352]
	ldr	w2, [x20, 688]
	str	w2, [x19, 392]
	ldr	w2, [x0, 1008]
	bfi	w1, w2, 0, 1
	ldr	w2, [x0, 1012]
	bfi	w1, w2, 1, 1
	ldr	w2, [x21, 92]
	bfi	w1, w2, 2, 1
	ldr	w2, [x0, 1028]
	bfi	w1, w2, 4, 1
	ldr	w2, [x21, 88]
	bfi	w1, w2, 8, 1
	ldr	w2, [x0, 1004]
	bfi	w1, w2, 9, 1
	ldr	w2, [x0, 1076]
	bfi	w1, w2, 10, 1
	ldr	w2, [x0, 1080]
	bfi	w1, w2, 11, 1
	ldr	w2, [x0, 1084]
	bfi	w1, w2, 12, 1
	ldr	w2, [x0, 1000]
	bfi	w1, w2, 13, 1
	ldr	w2, [x0, 996]
	bfi	w1, w2, 14, 1
	ldr	w2, [x0, 1088]
	bfi	w1, w2, 15, 1
	str	w1, [x19, 440]
	mov	w2, 0
	mov	w1, 2
	ldr	w3, [x21, 96]
	bfi	w2, w3, 1, 1
	mov	w3, 128
	bfi	w2, w1, 16, 8
	bfi	w2, w1, 24, 8
	mov	w1, -128
	str	w2, [x19, 444]
	mov	w2, 0
	bfi	w2, w1, 0, 8
	bfi	w2, w1, 8, 8
	bfi	w2, w1, 16, 8
	str	w2, [x19, 464]
	mov	w2, 0
	bfi	w2, w1, 0, 8
	bfi	w2, w1, 8, 8
	mov	w1, 0
	bfi	w1, w3, 0, 10
	str	w2, [x19, 468]
	bfi	w1, w3, 10, 10
	str	w1, [x19, 472]
	mov	w1, 0
	str	w1, [x19, 476]
	mov	w2, 43691
	ldr	w3, [x20, 172]
	movk	w2, 0xaaaa, lsl 16
	add	w3, w3, 2
	umull	x7, w3, w2
	lsr	x5, x7, 32
	lsr	w8, w5, 1
	lsl	w7, w8, 2
	sub	w5, w7, w8
	mov	w8, 0
	sub	w3, w3, w5
	add	x3, x3, 40
	ldr	w3, [x20, x3, lsl 2]
	str	w3, [x19, 480]
	ldr	w3, [x20, 172]
	add	w3, w3, w6
	umull	x5, w3, w2
	lsr	x2, x5, 32
	lsr	w7, w2, 1
	lsl	w5, w7, 2
	sub	w2, w5, w7
	mov	w7, 0
	sub	w2, w3, w2
	add	x2, x2, 40
	ldr	w2, [x20, x2, lsl 2]
	str	w2, [x19, 484]
	str	w6, [x19, 492]
	ldrb	w23, [x0, 1392]
	ldrb	w22, [x0, 1388]
	ldrb	w18, [x0, 1384]
	ldrb	w17, [x0, 1380]
	orr	w3, w23, w22
	ldrb	w16, [x0, 1376]
	ldrb	w13, [x0, 1372]
	orr	w2, w18, w17
	ldrb	w6, [x0, 1368]
	orr	w3, w3, w2
	ldrb	w5, [x0, 1364]
	orr	w2, w16, w13
	orr	w3, w3, w2
	orr	w2, w6, w5
	orr	w2, w3, w2
	mov	w3, 0
	bfi	w1, w2, 24, 1
	ldr	w2, [x0, 1616]
	bfi	w1, w2, 23, 1
	ldr	w2, [x0, 1612]
	bfi	w1, w2, 22, 1
	ldr	w2, [x0, 1608]
	bfi	w1, w2, 21, 1
	ldr	w2, [x0, 1604]
	bfi	w1, w2, 20, 1
	ldr	w2, [x0, 1600]
	bfi	w1, w2, 19, 1
	ldr	w2, [x0, 1596]
	bfi	w1, w2, 18, 1
	ldr	w2, [x0, 1592]
	bfi	w1, w2, 17, 1
	ldr	w2, [x0, 1588]
	bfi	w1, w2, 16, 1
	ldr	w2, [x0, 1424]
	bfi	w1, w2, 15, 1
	ldr	w2, [x0, 1420]
	bfi	w1, w2, 14, 1
	ldr	w2, [x0, 1416]
	bfi	w1, w2, 13, 1
	ldr	w2, [x0, 1412]
	bfi	w1, w2, 12, 1
	ldr	w2, [x0, 1408]
	bfi	w1, w2, 11, 1
	ldr	w2, [x0, 1404]
	bfi	w1, w2, 10, 1
	ldr	w2, [x0, 1400]
	bfi	w1, w2, 9, 1
	ldr	w2, [x0, 1396]
	bfi	w1, w2, 8, 1
	mov	w2, 0
	bfi	w1, w23, 7, 1
	mov	w23, 0
	bfi	w1, w22, 6, 1
	mov	w22, 0
	bfi	w1, w18, 5, 1
	mov	w18, 16
	bfi	w1, w17, 4, 1
	mov	w17, 0
	bfi	w1, w16, 3, 1
	mov	w16, 0
	bfi	w1, w13, 2, 1
	mov	w13, 0
	bfi	w1, w6, 1, 1
	mov	w6, 0
	bfi	w1, w5, 0, 1
	str	w1, [x19, 512]
	ldr	w1, [x0, 1440]
	mov	w5, 0
	bfi	w4, w1, 24, 7
	ldr	w1, [x0, 1436]
	bfi	w4, w1, 16, 7
	ldr	w1, [x0, 1432]
	bfi	w4, w1, 8, 7
	ldr	w1, [x0, 1428]
	bfi	w4, w1, 0, 7
	str	w4, [x19, 516]
	mov	w4, 0
	ldr	w1, [x0, 1456]
	bfi	w12, w1, 24, 7
	ldr	w1, [x0, 1452]
	bfi	w12, w1, 16, 7
	ldr	w1, [x0, 1448]
	bfi	w12, w1, 8, 7
	ldr	w1, [x0, 1444]
	bfi	w12, w1, 0, 7
	str	w12, [x19, 520]
	mov	w12, 0
	ldr	w1, [x0, 1492]
	bfi	w11, w1, 16, 10
	ldr	w1, [x0, 1460]
	bfi	w11, w1, 0, 10
	str	w11, [x19, 524]
	mov	w11, 0
	ldr	w1, [x0, 1496]
	bfi	w14, w1, 16, 10
	ldr	w1, [x0, 1464]
	bfi	w14, w1, 0, 10
	str	w14, [x19, 528]
	mov	w1, 0
	ldr	w14, [x0, 1500]
	bfi	w9, w14, 16, 10
	ldr	w14, [x0, 1468]
	bfi	w9, w14, 0, 10
	str	w9, [x19, 532]
	ldr	w9, [x0, 1504]
	bfi	w10, w9, 16, 10
	ldr	w9, [x0, 1472]
	bfi	w10, w9, 0, 10
	str	w10, [x19, 536]
	mov	w10, 0
	ldr	w9, [x0, 1508]
	bfi	w15, w9, 16, 10
	ldr	w9, [x0, 1476]
	bfi	w15, w9, 0, 10
	str	w15, [x19, 540]
	mov	w15, 0
	ldr	w9, [x0, 1512]
	bfi	w8, w9, 16, 10
	ldr	w9, [x0, 1480]
	bfi	w8, w9, 0, 10
	str	w8, [x19, 544]
	mov	w9, 0
	ldr	w8, [x0, 1516]
	bfi	w7, w8, 16, 10
	ldr	w8, [x0, 1484]
	bfi	w7, w8, 0, 10
	str	w7, [x19, 548]
	mov	w8, 0
	ldr	w7, [x0, 1520]
	bfi	w6, w7, 16, 10
	ldr	w7, [x0, 1488]
	bfi	w6, w7, 0, 10
	str	w6, [x19, 552]
	mov	w7, 0
	ldr	w6, [x0, 1556]
	bfi	w5, w6, 16, 9
	ldr	w6, [x0, 1524]
	bfi	w5, w6, 0, 9
	str	w5, [x19, 556]
	mov	w6, 0
	ldr	w5, [x0, 1560]
	bfi	w4, w5, 16, 9
	ldr	w5, [x0, 1528]
	bfi	w4, w5, 0, 9
	str	w4, [x19, 560]
	mov	w5, 0
	ldr	w4, [x0, 1564]
	bfi	w3, w4, 16, 9
	ldr	w4, [x0, 1532]
	bfi	w3, w4, 0, 9
	str	w3, [x19, 564]
	mov	w4, 0
	mov	w3, 0
	ldr	w14, [x0, 1568]
	bfi	w2, w14, 16, 9
	ldr	w14, [x0, 1536]
	bfi	w2, w14, 0, 9
	str	w2, [x19, 568]
	mov	w2, 0
	ldr	w14, [x0, 1572]
	bfi	w13, w14, 16, 9
	ldr	w14, [x0, 1540]
	bfi	w13, w14, 0, 9
	str	w13, [x19, 572]
	mov	w14, 0
	ldr	w13, [x0, 1576]
	bfi	w12, w13, 16, 9
	ldr	w13, [x0, 1544]
	bfi	w12, w13, 0, 9
	str	w12, [x19, 576]
	mov	w13, 0
	ldr	w12, [x0, 1580]
	bfi	w11, w12, 16, 9
	ldr	w12, [x0, 1548]
	bfi	w11, w12, 0, 9
	str	w11, [x19, 580]
	ldr	w11, [x0, 1584]
	bfi	w1, w11, 16, 9
	ldr	w11, [x0, 1552]
	bfi	w1, w11, 0, 9
	str	w1, [x19, 584]
	mov	w1, 0
	ldr	w11, [x20, 8]
	ldr	w12, [x20, 20]
	cmp	w11, wzr
	mov	w11, 64
	csel	w11, w11, w18, ne
	ldr	w18, [x20, 16]
	sub	w12, w12, #1
	sub	w18, w18, #1
	add	w12, w12, w11
	add	w18, w18, w11
	udiv	w18, w18, w11
	udiv	w11, w12, w11
	mul	w18, w18, w11
	ldr	w11, [x20, 544]
	udiv	w18, w11, w18
	mov	w11, 0
	bfi	w11, w18, 0, 20
	str	w11, [x19, 588]
	ldr	w11, [x0, 8]
	bfi	w28, w11, 16, 5
	ldr	w11, [x0, 12]
	mov	w18, 0
	bfi	w28, w11, 0, 10
	str	w28, [x19, 640]
	mov	w28, 0
	ldr	w11, [x21, 8]
	bfi	w27, w11, 16, 5
	ldr	w11, [x0, 16]
	bfi	w27, w11, 0, 8
	str	w27, [x19, 644]
	ldr	w11, [x0, 20]
	bfi	w26, w11, 16, 5
	ldr	w11, [x0, 24]
	bfi	w26, w11, 0, 10
	str	w26, [x19, 648]
	mov	w26, 0
	ldr	w11, [x0, 28]
	bfi	w25, w11, 16, 5
	ldr	w11, [x21, 12]
	bfi	w25, w11, 0, 8
	str	w25, [x19, 652]
	mov	w25, 0
	ldr	w11, [x0, 32]
	bfi	w24, w11, 16, 5
	ldr	w11, [x0, 36]
	bfi	w24, w11, 0, 10
	str	w24, [x19, 656]
	mov	w24, 0
	ldr	w11, [x21, 16]
	bfi	w23, w11, 16, 5
	ldr	w11, [x21, 20]
	bfi	w23, w11, 0, 8
	str	w23, [x19, 660]
	mov	w23, 0
	ldr	w11, [x0, 40]
	bfi	w26, w11, 16, 5
	ldr	w11, [x0, 44]
	bfi	w26, w11, 0, 10
	str	w26, [x19, 664]
	mov	w11, 0
	mov	w26, 0
	ldr	w27, [x21, 24]
	bfi	w28, w27, 16, 5
	ldr	w27, [x21, 28]
	bfi	w28, w27, 0, 8
	str	w28, [x19, 668]
	mov	w27, 0
	mov	w28, 0
	ldr	w12, [x0, 48]
	bfi	w10, w12, 12, 4
	ldr	w12, [x0, 52]
	bfi	w10, w12, 8, 4
	ldr	w12, [x0, 56]
	bfi	w10, w12, 4, 4
	ldr	w12, [x0, 60]
	bfi	w10, w12, 0, 4
	ldr	w12, [x0, 64]
	bfi	w10, w12, 28, 4
	ldr	w12, [x21, 32]
	bfi	w10, w12, 24, 4
	ldr	w12, [x0, 68]
	bfi	w10, w12, 20, 4
	ldr	w12, [x0, 72]
	bfi	w10, w12, 16, 4
	str	w10, [x19, 672]
	ldr	w10, [x0, 76]
	bfi	w9, w10, 12, 4
	ldr	w10, [x0, 80]
	bfi	w9, w10, 8, 4
	ldr	w10, [x0, 84]
	bfi	w9, w10, 4, 4
	ldr	w10, [x0, 88]
	bfi	w9, w10, 0, 4
	ldr	w10, [x0, 92]
	bfi	w9, w10, 28, 4
	ldr	w10, [x0, 96]
	bfi	w9, w10, 24, 4
	ldr	w10, [x21, 36]
	bfi	w9, w10, 20, 4
	ldr	w10, [x0, 100]
	bfi	w9, w10, 16, 4
	str	w9, [x19, 676]
	mov	w10, 0
	ldr	w9, [x0, 104]
	bfi	w8, w9, 12, 4
	ldr	w9, [x0, 108]
	bfi	w8, w9, 8, 4
	ldr	w9, [x0, 112]
	bfi	w8, w9, 4, 4
	ldr	w9, [x0, 116]
	bfi	w8, w9, 0, 4
	ldr	w9, [x0, 120]
	bfi	w8, w9, 28, 4
	ldr	w9, [x0, 124]
	bfi	w8, w9, 24, 4
	ldr	w9, [x21, 40]
	bfi	w8, w9, 20, 4
	ldr	w9, [x0, 128]
	bfi	w8, w9, 16, 4
	str	w8, [x19, 680]
	mov	w9, 0
	ldr	w8, [x0, 132]
	bfi	w7, w8, 12, 4
	ldr	w8, [x21, 44]
	bfi	w7, w8, 8, 4
	ldr	w8, [x0, 136]
	bfi	w7, w8, 4, 4
	ldr	w8, [x0, 140]
	bfi	w7, w8, 0, 4
	ldr	w8, [x0, 144]
	bfi	w7, w8, 28, 4
	ldr	w8, [x0, 148]
	bfi	w7, w8, 24, 4
	ldr	w8, [x0, 152]
	bfi	w7, w8, 20, 4
	ldr	w8, [x0, 156]
	bfi	w7, w8, 16, 4
	str	w7, [x19, 684]
	ldr	w7, [x0, 160]
	bfi	w6, w7, 12, 4
	ldr	w7, [x0, 164]
	bfi	w6, w7, 8, 4
	ldr	w7, [x21, 48]
	bfi	w6, w7, 4, 4
	ldr	w7, [x0, 168]
	bfi	w6, w7, 0, 4
	ldr	w7, [x0, 172]
	bfi	w6, w7, 28, 4
	ldr	w7, [x0, 176]
	bfi	w6, w7, 24, 4
	ldr	w7, [x0, 180]
	bfi	w6, w7, 20, 4
	ldr	w7, [x0, 184]
	bfi	w6, w7, 16, 4
	str	w6, [x19, 688]
	mov	w6, 0
	ldr	w7, [x0, 188]
	bfi	w5, w7, 12, 4
	ldr	w7, [x0, 192]
	bfi	w5, w7, 8, 4
	ldr	w7, [x21, 52]
	bfi	w5, w7, 4, 4
	ldr	w7, [x0, 196]
	bfi	w5, w7, 0, 4
	ldr	w7, [x0, 200]
	bfi	w5, w7, 28, 4
	ldr	w7, [x0, 204]
	bfi	w5, w7, 24, 4
	ldr	w7, [x0, 208]
	bfi	w5, w7, 20, 4
	ldr	w7, [x0, 212]
	bfi	w5, w7, 16, 4
	str	w5, [x19, 692]
	mov	w5, 0
	ldr	w7, [x0, 216]
	bfi	w4, w7, 12, 4
	ldr	w7, [x21, 56]
	bfi	w4, w7, 8, 4
	ldr	w7, [x0, 220]
	bfi	w4, w7, 4, 4
	ldr	w7, [x0, 224]
	bfi	w4, w7, 0, 4
	ldr	w7, [x0, 228]
	bfi	w4, w7, 28, 4
	ldr	w7, [x0, 232]
	bfi	w4, w7, 24, 4
	ldr	w7, [x0, 236]
	bfi	w4, w7, 20, 4
	ldr	w7, [x0, 240]
	bfi	w4, w7, 16, 4
	str	w4, [x19, 696]
	mov	w7, 0
	mov	w4, 0
	ldr	w8, [x0, 244]
	bfi	w3, w8, 12, 4
	ldr	w8, [x0, 248]
	bfi	w3, w8, 8, 4
	ldr	w8, [x0, 252]
	bfi	w3, w8, 4, 4
	ldr	w8, [x0, 256]
	bfi	w3, w8, 0, 4
	ldr	w8, [x0, 260]
	bfi	w3, w8, 28, 4
	ldr	w8, [x0, 264]
	bfi	w3, w8, 24, 4
	ldr	w8, [x0, 268]
	bfi	w3, w8, 20, 4
	ldr	w8, [x0, 272]
	bfi	w3, w8, 16, 4
	str	w3, [x19, 700]
	mov	w3, 0
	ldr	w8, [x0, 276]
	bfi	w2, w8, 12, 4
	ldr	w8, [x0, 280]
	bfi	w2, w8, 8, 4
	ldr	w8, [x0, 284]
	bfi	w2, w8, 4, 4
	ldr	w8, [x0, 288]
	bfi	w2, w8, 0, 4
	ldr	w8, [x0, 292]
	bfi	w2, w8, 28, 4
	ldr	w8, [x0, 296]
	bfi	w2, w8, 24, 4
	ldr	w8, [x0, 300]
	bfi	w2, w8, 20, 4
	ldr	w8, [x0, 304]
	bfi	w2, w8, 16, 4
	str	w2, [x19, 704]
	ldr	w2, [x0, 308]
	bfi	w17, w2, 0, 3
	ldr	w2, [x0, 312]
	bfi	w17, w2, 3, 7
	ldr	w2, [x0, 316]
	bfi	w17, w2, 10, 3
	ldr	w2, [x0, 320]
	bfi	w17, w2, 13, 5
	ldr	w2, [x0, 324]
	bfi	w17, w2, 18, 4
	ldr	w2, [x0, 328]
	bfi	w17, w2, 22, 4
	ldr	w2, [x0, 332]
	bfi	w17, w2, 26, 4
	str	w17, [x19, 708]
	mov	w2, 0
	mov	w17, 0
	ldr	w8, [x0, 336]
	bfi	w16, w8, 0, 3
	ldr	w8, [x0, 340]
	bfi	w16, w8, 3, 7
	ldr	w8, [x0, 344]
	bfi	w16, w8, 10, 3
	ldr	w8, [x0, 348]
	bfi	w16, w8, 13, 5
	ldr	w8, [x0, 352]
	bfi	w16, w8, 18, 4
	ldr	w8, [x0, 356]
	bfi	w16, w8, 22, 4
	ldr	w8, [x0, 360]
	bfi	w16, w8, 26, 4
	str	w16, [x19, 712]
	mov	w16, 0
	ldr	w8, [x0, 364]
	bfi	w15, w8, 0, 3
	ldr	w8, [x0, 368]
	bfi	w15, w8, 3, 7
	ldr	w8, [x0, 372]
	bfi	w15, w8, 10, 3
	ldr	w8, [x0, 376]
	bfi	w15, w8, 13, 5
	ldr	w8, [x0, 380]
	bfi	w15, w8, 18, 4
	ldr	w8, [x0, 384]
	bfi	w15, w8, 22, 4
	ldr	w8, [x0, 388]
	bfi	w15, w8, 26, 4
	str	w15, [x19, 716]
	mov	w15, 0
	ldr	w8, [x0, 656]
	bfi	w14, w8, 0, 3
	ldr	w8, [x0, 660]
	bfi	w14, w8, 3, 7
	ldr	w8, [x0, 664]
	bfi	w14, w8, 10, 3
	ldr	w8, [x0, 668]
	bfi	w14, w8, 13, 5
	ldr	w8, [x0, 672]
	bfi	w14, w8, 18, 4
	ldr	w8, [x0, 676]
	bfi	w14, w8, 22, 4
	ldr	w8, [x0, 680]
	bfi	w14, w8, 26, 4
	str	w14, [x19, 720]
	mov	w14, 0
	ldr	w8, [x0, 684]
	bfi	w13, w8, 0, 3
	ldr	w8, [x0, 688]
	bfi	w13, w8, 3, 7
	ldr	w8, [x0, 692]
	bfi	w13, w8, 10, 3
	ldr	w8, [x0, 696]
	bfi	w13, w8, 13, 5
	ldr	w8, [x0, 700]
	bfi	w13, w8, 18, 4
	ldr	w8, [x0, 704]
	bfi	w13, w8, 22, 4
	ldr	w8, [x0, 708]
	bfi	w13, w8, 26, 4
	str	w13, [x19, 724]
	mov	w13, 0
	ldr	w8, [x21, 68]
	bfi	w10, w8, 0, 3
	ldr	w8, [x0, 712]
	bfi	w10, w8, 3, 7
	ldr	w8, [x0, 716]
	bfi	w10, w8, 10, 3
	ldr	w8, [x0, 720]
	bfi	w10, w8, 13, 5
	ldr	w8, [x0, 724]
	bfi	w10, w8, 18, 4
	ldr	w8, [x0, 728]
	bfi	w10, w8, 22, 4
	ldr	w8, [x0, 732]
	bfi	w10, w8, 26, 4
	mov	w8, w10
	str	w8, [x19, 728]
	mov	w10, 0
	mov	w8, 0
	ldr	w12, [x0, 736]
	bfi	w22, w12, 0, 3
	ldr	w12, [x0, 740]
	bfi	w22, w12, 3, 7
	ldr	w12, [x0, 744]
	bfi	w22, w12, 10, 3
	ldr	w12, [x0, 748]
	bfi	w22, w12, 13, 5
	ldr	w12, [x0, 752]
	bfi	w22, w12, 18, 4
	ldr	w12, [x0, 756]
	bfi	w22, w12, 22, 4
	ldr	w12, [x0, 760]
	bfi	w22, w12, 26, 4
	str	w22, [x19, 732]
	mov	w12, 257
	ldr	w22, [x0, 392]
	movk	w12, 0xc8, lsl 16
	bfi	w1, w22, 0, 4
	ldr	w22, [x0, 396]
	bfi	w1, w22, 4, 4
	ldr	w22, [x0, 400]
	bfi	w1, w22, 8, 4
	ldr	w22, [x0, 404]
	bfi	w1, w22, 12, 4
	ldr	w22, [x0, 408]
	bfi	w1, w22, 16, 4
	ldr	w22, [x0, 412]
	bfi	w1, w22, 20, 4
	ldr	w22, [x0, 416]
	bfi	w1, w22, 24, 4
	ldr	w22, [x0, 420]
	bfi	w1, w22, 28, 4
	str	w1, [x19, 736]
	mov	w22, 0
	ldr	w1, [x0, 424]
	bfi	w22, w1, 0, 4
	ldr	w1, [x0, 428]
	bfi	w22, w1, 4, 4
	ldr	w1, [x0, 432]
	bfi	w22, w1, 8, 4
	ldr	w1, [x0, 436]
	bfi	w22, w1, 12, 4
	ldr	w1, [x0, 440]
	bfi	w22, w1, 16, 4
	ldr	w1, [x0, 444]
	bfi	w22, w1, 20, 4
	str	w22, [x19, 740]
	mov	w22, 0
	ldr	w1, [x0, 448]
	bfi	w22, w1, 0, 10
	ldr	w1, [x0, 452]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 744]
	mov	w22, 0
	ldr	w1, [x21, 60]
	bfi	w22, w1, 0, 8
	ldr	w1, [x21, 64]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 748]
	mov	w22, 0
	ldr	w1, [x0, 456]
	bfi	w22, w1, 0, 10
	ldr	w1, [x0, 460]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 752]
	mov	w22, 0
	ldr	w1, [x0, 464]
	bfi	w22, w1, 0, 8
	ldr	w1, [x0, 468]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 756]
	mov	w22, 0
	ldr	w1, [x0, 472]
	bfi	w22, w1, 0, 10
	ldr	w1, [x0, 476]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 760]
	mov	w22, 0
	ldr	w1, [x0, 480]
	bfi	w22, w1, 0, 8
	ldr	w1, [x0, 484]
	bfi	w22, w1, 16, 5
	str	w22, [x19, 764]
	ldr	w1, [x0, 764]
	bfi	w18, w1, 0, 4
	ldr	w1, [x0, 768]
	bfi	w18, w1, 4, 4
	ldr	w1, [x0, 772]
	bfi	w18, w1, 8, 4
	ldr	w1, [x0, 776]
	bfi	w18, w1, 12, 4
	ldr	w1, [x0, 780]
	bfi	w18, w1, 16, 4
	ldr	w1, [x0, 784]
	bfi	w18, w1, 20, 4
	str	w18, [x19, 768]
	mov	w18, 0
	ldr	w1, [x21, 72]
	bfi	w18, w1, 0, 12
	ldr	w1, [x21, 76]
	bfi	w18, w1, 12, 12
	ldr	w1, [x0, 788]
	bfi	w18, w1, 24, 8
	str	w18, [x19, 772]
	mov	w18, 0
	ldr	w1, [x0, 792]
	bfi	w18, w1, 0, 12
	ldr	w1, [x0, 796]
	bfi	w18, w1, 12, 12
	ldr	w1, [x0, 800]
	bfi	w18, w1, 24, 8
	str	w18, [x19, 776]
	mov	w18, 0
	ldr	w1, [x21, 80]
	bfi	w18, w1, 0, 12
	ldr	w1, [x0, 804]
	bfi	w18, w1, 12, 12
	ldr	w1, [x0, 808]
	bfi	w18, w1, 24, 8
	str	w18, [x19, 780]
	mov	w18, 0
	ldr	w1, [x0, 812]
	bfi	w18, w1, 0, 8
	ldr	w1, [x0, 816]
	bfi	w18, w1, 8, 8
	ldr	w1, [x0, 820]
	bfi	w18, w1, 16, 8
	str	w18, [x19, 784]
	ldr	w1, [x0, 488]
	bfi	w24, w1, 0, 1
	ldr	w1, [x0, 492]
	bfi	w24, w1, 1, 3
	ldr	w1, [x0, 496]
	bfi	w24, w1, 4, 6
	ldr	w1, [x0, 500]
	bfi	w24, w1, 10, 5
	ldr	w1, [x0, 504]
	bfi	w24, w1, 15, 6
	ldr	w1, [x0, 508]
	bfi	w24, w1, 21, 5
	str	w24, [x19, 788]
	ldr	w1, [x0, 512]
	bfi	w25, w1, 0, 1
	ldr	w1, [x0, 516]
	bfi	w25, w1, 1, 3
	ldr	w1, [x0, 520]
	bfi	w25, w1, 4, 6
	ldr	w1, [x0, 524]
	bfi	w25, w1, 10, 5
	ldr	w1, [x0, 528]
	bfi	w25, w1, 15, 6
	ldr	w1, [x0, 532]
	bfi	w25, w1, 21, 5
	str	w25, [x19, 792]
	ldr	w1, [x0, 536]
	bfi	w23, w1, 0, 1
	ldr	w1, [x0, 540]
	bfi	w23, w1, 1, 3
	ldr	w1, [x0, 544]
	bfi	w23, w1, 4, 6
	ldr	w1, [x0, 548]
	bfi	w23, w1, 10, 5
	ldr	w1, [x0, 552]
	bfi	w23, w1, 15, 6
	ldr	w1, [x0, 556]
	bfi	w23, w1, 21, 5
	str	w23, [x19, 796]
	ldr	w1, [x0, 560]
	bfi	w11, w1, 0, 1
	ldr	w1, [x0, 564]
	bfi	w11, w1, 1, 3
	ldr	w1, [x0, 568]
	bfi	w11, w1, 4, 6
	ldr	w1, [x0, 572]
	bfi	w11, w1, 10, 5
	ldr	w1, [x0, 576]
	bfi	w11, w1, 15, 6
	ldr	w1, [x0, 580]
	bfi	w11, w1, 21, 5
	str	w11, [x19, 800]
	mov	w11, 0
	ldr	w1, [x0, 584]
	bfi	w26, w1, 0, 1
	ldr	w1, [x0, 588]
	bfi	w26, w1, 1, 3
	ldr	w1, [x0, 592]
	bfi	w26, w1, 4, 6
	ldr	w1, [x0, 596]
	bfi	w26, w1, 10, 5
	ldr	w1, [x0, 600]
	bfi	w26, w1, 15, 6
	ldr	w1, [x0, 604]
	bfi	w26, w1, 21, 5
	str	w26, [x19, 804]
	ldr	w1, [x0, 608]
	bfi	w27, w1, 0, 1
	ldr	w1, [x0, 612]
	bfi	w27, w1, 1, 3
	ldr	w1, [x0, 616]
	bfi	w27, w1, 4, 6
	ldr	w1, [x0, 620]
	bfi	w27, w1, 10, 5
	ldr	w1, [x0, 624]
	bfi	w27, w1, 15, 6
	ldr	w1, [x0, 628]
	bfi	w27, w1, 21, 5
	str	w27, [x19, 808]
	ldr	w1, [x0, 632]
	bfi	w28, w1, 0, 1
	ldr	w1, [x0, 636]
	bfi	w28, w1, 1, 3
	ldr	w1, [x0, 640]
	bfi	w28, w1, 4, 6
	ldr	w1, [x0, 644]
	bfi	w28, w1, 10, 5
	ldr	w1, [x0, 648]
	bfi	w28, w1, 15, 6
	ldr	w1, [x0, 652]
	bfi	w28, w1, 21, 5
	str	w28, [x19, 812]
	ldr	w1, [x21, 5720]
	bfi	w11, w1, 20, 8
	ldr	w1, [x20, 44]
	bfi	w11, w1, 28, 1
	str	w11, [x19, 1024]
	mov	w1, -16711936
	str	w1, [x19, 1120]
	mov	w11, 0
	ldr	w1, [x0, 1144]
	bfi	w11, w1, 0, 1
	str	w11, [x19, 1536]
	mov	w11, 0
	ldr	w1, [x0, 1148]
	bfi	w11, w1, 0, 16
	str	w11, [x19, 1540]
	mov	w11, 0
	ldr	w1, [x0, 1152]
	bfi	w11, w1, 0, 16
	str	w11, [x19, 1544]
	mov	w11, 0
	ldr	w1, [x0, 1156]
	bfi	w11, w1, 0, 16
	str	w11, [x19, 1548]
	ldr	w1, [x0, 1160]
	bfi	w9, w1, 18, 9
	ldr	w1, [x0, 1164]
	bfi	w9, w1, 9, 9
	ldr	w1, [x0, 1168]
	bfi	w9, w1, 0, 9
	str	w9, [x19, 1556]
	mov	w9, 0
	ldr	w1, [x0, 1172]
	bfi	w9, w1, 16, 8
	ldr	w1, [x0, 1176]
	bfi	w9, w1, 8, 8
	ldr	w1, [x0, 1180]
	bfi	w9, w1, 0, 8
	str	w9, [x19, 1560]
	ldr	w1, [x0, 1184]
	bfi	w6, w1, 8, 4
	ldr	w1, [x0, 1188]
	bfi	w6, w1, 4, 4
	ldr	w1, [x0, 1192]
	bfi	w6, w1, 0, 4
	mov	w1, 3
	bfi	w6, w1, 20, 8
	mov	w1, 20
	bfi	w6, w1, 12, 8
	str	w6, [x19, 1564]
	ldrh	w1, [x0, 1292]
	str	w1, [x19, 1568]
	ldr	w1, [x0, 1308]
	bfi	w5, w1, 0, 8
	ldr	w1, [x0, 1304]
	bfi	w5, w1, 8, 8
	ldr	w1, [x0, 1300]
	bfi	w5, w1, 16, 8
	ldr	w1, [x0, 1296]
	bfi	w5, w1, 24, 8
	str	w5, [x19, 1572]
	ldr	w1, [x0, 1196]
	bfi	w7, w1, 24, 8
	ldr	w1, [x0, 1200]
	bfi	w7, w1, 16, 8
	ldr	w1, [x0, 1204]
	bfi	w7, w1, 8, 8
	ldr	w1, [x0, 1208]
	bfi	w7, w1, 0, 8
	str	w7, [x19, 1584]
	ldr	w1, [x0, 1212]
	bfi	w4, w1, 0, 8
	ldr	w1, [x0, 1216]
	bfi	w4, w1, 8, 8
	ldr	w1, [x0, 1220]
	bfi	w4, w1, 16, 1
	ldr	w1, [x0, 1336]
	bfi	w4, w1, 17, 1
	str	w4, [x19, 1588]
	mov	w4, 0
	ldr	w1, [x0, 1224]
	bfi	w4, w1, 0, 16
	ldr	w1, [x0, 1228]
	bfi	w4, w1, 16, 16
	str	w4, [x19, 1592]
	mov	w4, 0
	ldr	w1, [x21, 488]
	bfi	w3, w1, 22, 9
	ldr	w1, [x21, 492]
	bfi	w3, w1, 17, 5
	ldr	w1, [x21, 496]
	bfi	w3, w1, 9, 8
	ldr	w1, [x21, 516]
	bfi	w3, w1, 0, 9
	str	w3, [x19, 1596]
	mov	w3, 0
	ldr	w1, [x21, 512]
	bfi	w4, w1, 8, 14
	ldr	w1, [x0, 1232]
	bfi	w4, w1, 0, 8
	str	w4, [x19, 1732]
	ldr	w1, [x21, 500]
	bfi	w3, w1, 16, 8
	ldr	w1, [x21, 504]
	bfi	w3, w1, 8, 8
	ldr	w1, [x21, 508]
	bfi	w3, w1, 0, 8
	str	w3, [x19, 1736]
	ldr	w1, [x0, 1240]
	bfi	w2, w1, 17, 1
	ldr	w1, [x0, 1244]
	bfi	w2, w1, 12, 2
	ldr	w1, [x0, 1248]
	bfi	w2, w1, 4, 4
	ldr	w1, [x0, 1252]
	bfi	w2, w1, 0, 4
	str	w2, [x19, 1740]
	mov	w2, 0
	ldr	w1, [x0, 1256]
	bfi	w17, w1, 0, 10
	ldr	w1, [x0, 1260]
	bfi	w17, w1, 16, 9
	str	w17, [x19, 1744]
	ldr	w1, [x0, 1264]
	bfi	w16, w1, 0, 10
	ldr	w1, [x0, 1268]
	bfi	w16, w1, 16, 9
	str	w16, [x19, 1748]
	ldr	w1, [x0, 1272]
	bfi	w2, w1, 0, 10
	ldr	w1, [x0, 1276]
	bfi	w2, w1, 16, 9
	str	w2, [x19, 1752]
	mov	w2, 0
	ldr	w1, [x0, 1280]
	bfi	w15, w1, 0, 10
	ldr	w1, [x0, 1284]
	bfi	w15, w1, 16, 9
	str	w15, [x19, 1756]
	ldr	w1, [x0, 1288]
	bfi	w2, w1, 0, 16
	str	w2, [x19, 1776]
	mov	w2, 0
	ldr	w1, [x0, 1312]
	bfi	w14, w1, 0, 13
	ldr	w1, [x0, 1316]
	bfi	w14, w1, 13, 1
	str	w14, [x19, 1780]
	ldr	w1, [x0, 1320]
	bfi	w2, w1, 0, 18
	str	w2, [x19, 1784]
	mov	w2, 0
	ldr	w1, [x0, 1324]
	bfi	w2, w1, 0, 18
	str	w2, [x19, 1788]
	ldr	w1, [x0, 1348]
	bfi	w13, w1, 16, 7
	ldr	w1, [x0, 1352]
	bfi	w13, w1, 23, 7
	str	w13, [x19, 1792]
	ldr	w1, [x0, 1340]
	bfi	w10, w1, 0, 8
	ldr	w1, [x0, 1344]
	bfi	w10, w1, 8, 8
	ldr	w1, [x0, 1328]
	bfi	w10, w1, 16, 8
	str	w10, [x19, 1796]
	ldr	w1, [x0, 1332]
	bfi	w8, w1, 12, 8
	ldr	w1, [x0, 1356]
	ldr	w0, [x0, 1360]
	bfi	w8, w1, 8, 4
	bfi	w8, w0, 0, 8
	str	w8, [x19, 1800]
	str	w12, [x19, 1804]
	ldr	w0, [x20, 8]
	cbnz	w0, .L41
	mov	w1, 23
	mov	w2, 15
	bfi	w0, w1, 0, 5
	bfi	w0, w2, 5, 5
	bfi	w0, w1, 10, 5
	bfi	w0, w2, 15, 5
	and	w0, w0, -1048577
	str	w0, [x19, 2052]
.L42:
	mov	w3, 16
	mov	w0, 2
	mov	w1, 0
	str	w0, [x19, 2560]
	str	wzr, [x19, 2592]
	bfi	w1, w3, 6, 6
	mov	w2, 10
	bfi	w1, w2, 0, 6
	str	w1, [x19, 2596]
	ldr	w1, [x20, 556]
	ldr	w2, [x20, 552]
	ubfiz	w1, w1, 8, 6
	orr	w1, w1, 64
	bfi	w1, w2, 0, 6
	ldr	w2, [x30, 3392]
	bfi	w1, w2, 16, 6
	ldr	w2, [x30, 3364]
	bfi	w1, w2, 24, 4
	str	w1, [x19, 3076]
	mov	w2, 64
	ldr	w1, [x20, 8]
	cmp	w1, wzr
	csel	w3, w2, w3, ne
	ldp	w1, w2, [x20, 16]
	sub	w1, w1, #1
	sub	w2, w2, #1
	add	w1, w1, w3
	add	w2, w2, w3
	udiv	w1, w1, w3
	udiv	w2, w2, w3
	ldr	w3, [x20, 544]
	mul	w1, w1, w2
	mov	w2, 0
	udiv	w1, w3, w1
	ldr	w3, [x30, 3380]
	bfi	w2, w1, 0, 16
	bfi	w2, w3, 16, 6
	str	w2, [x19, 3080]
	ldr	w2, [x21, 100]
	ldr	w3, [x30, 3372]
	mov	w1, 0
	bfi	w1, w2, 0, 6
	ldr	w2, [x30, 3376]
	bfi	w1, w3, 24, 6
	ldr	w3, [x30, 3384]
	bfi	w1, w2, 16, 6
	mov	w2, 0
	bfi	w1, w3, 8, 6
	str	w1, [x19, 3084]
	ldp	w3, w1, [x21, 112]
	bfi	w2, w1, 24, 8
	bfi	w2, w3, 16, 8
	ldp	w3, w1, [x21, 104]
	bfi	w2, w1, 8, 8
	mov	w1, 0
	bfi	w2, w3, 0, 8
	str	w2, [x19, 3088]
	ldp	w3, w2, [x21, 128]
	bfi	w1, w2, 24, 8
	bfi	w1, w3, 16, 8
	ldp	w3, w2, [x21, 120]
	bfi	w1, w2, 8, 8
	mov	w2, 0
	bfi	w1, w3, 0, 8
	str	w1, [x19, 3092]
	ldp	w3, w1, [x21, 144]
	bfi	w2, w1, 24, 8
	bfi	w2, w3, 16, 8
	ldp	w3, w1, [x21, 136]
	bfi	w2, w1, 8, 8
	mov	w1, 0
	bfi	w2, w3, 0, 8
	str	w2, [x19, 3096]
	ldp	w3, w2, [x21, 160]
	bfi	w1, w2, 24, 8
	bfi	w1, w3, 16, 8
	ldp	w3, w2, [x21, 152]
	bfi	w1, w2, 8, 8
	mov	w2, 0
	bfi	w1, w3, 0, 8
	str	w1, [x19, 3072]
	ldr	w1, [x30, 3408]
	ldr	w3, [x30, 3412]
	bfi	w2, w1, 0, 4
	mov	w1, 0
	bfi	w2, w3, 4, 4
	str	w2, [x19, 3100]
	ldr	w2, [x30, 3356]
	bfi	w1, w2, 0, 4
	str	w1, [x19, 3104]
	mov	w1, 0
	ldr	w2, [x30, 3352]
	ldr	w0, [x30, 3360]
	bfi	w1, w2, 0, 4
	bfi	w1, w0, 4, 4
	str	w1, [x19, 3108]
	ldr	w0, [x20, 8]
	cbnz	w0, .L44
	mov	w1, 3
	bfi	w0, w1, 0, 4
.L45:
	add	x2, x30, 2440
	str	w0, [x19, 3112]
	mov	w0, 0
	mov	w1, 0
	mov	w4, 0
	ldr	x5, [x29, 104]
	ldr	w3, [x2, 844]
	bfi	w0, w3, 0, 2
	ldr	w3, [x2, 848]
	bfi	w0, w3, 2, 2
	ldr	w3, [x2, 852]
	bfi	w0, w3, 4, 2
	ldr	w3, [x2, 856]
	bfi	w0, w3, 6, 2
	ldr	w3, [x2, 860]
	bfi	w0, w3, 8, 2
	ldr	w3, [x2, 864]
	bfi	w0, w3, 10, 2
	ldr	w3, [x2, 868]
	bfi	w0, w3, 12, 2
	ldr	w3, [x2, 872]
	bfi	w0, w3, 14, 2
	ldr	w3, [x2, 876]
	bfi	w0, w3, 16, 2
	ldr	w3, [x2, 880]
	bfi	w0, w3, 18, 2
	ldr	w3, [x2, 884]
	bfi	w0, w3, 20, 2
	ldr	w3, [x2, 888]
	bfi	w0, w3, 22, 2
	ldr	w3, [x2, 892]
	bfi	w0, w3, 24, 2
	ldr	w3, [x2, 896]
	bfi	w0, w3, 26, 2
	ldr	w3, [x2, 900]
	bfi	w0, w3, 28, 2
	ldr	w3, [x2, 904]
	bfi	w0, w3, 30, 2
	str	w0, [x19, 3116]
	ldr	w0, [x2, 908]
	bfi	w1, w0, 0, 5
	str	w1, [x19, 3120]
	add	x0, x5, 872
	add	x1, x19, 3152
	ldr	w3, [x2, 956]
	bfi	w4, w3, 24, 4
	ldr	w3, [x2, 960]
	bfi	w4, w3, 28, 4
	ldr	w3, [x2, 964]
	bfi	w4, w3, 16, 6
	ldr	w3, [x2, 928]
	ldr	w2, [x2, 948]
	bfi	w4, w3, 8, 4
	add	x3, x5, 1192
	bfi	w4, w2, 0, 6
	str	w4, [x19, 3124]
	.p2align 2
.L46:
	add	x1, x1, 4
	ldr	w2, [x0], 4
	cmp	x3, x0
	str	w2, [x1, -4]
	bne	.L46
	str	wzr, [x19, 3660]
	mov	w0, 0
	str	w0, [x19, 4608]
	mov	w1, 13
	str	w0, [x19, 4612]
	bfi	w0, w1, 0, 4
	str	wzr, [x19, 4616]
	mov	w2, -1
	str	w0, [x19, 4620]
	mov	w0, 7
	str	wzr, [x19, 4624]
	mov	w3, 0
	str	wzr, [x19, 4628]
	mov	w1, 0
	str	wzr, [x19, 4632]
	mov	w5, 0
	str	wzr, [x19, 4636]
	str	w2, [x19, 4640]
	str	w0, [x19, 4644]
	str	w2, [x19, 4648]
	str	w0, [x19, 4652]
	str	w2, [x19, 4656]
	str	w0, [x19, 4660]
	str	w2, [x19, 4664]
	mov	w2, 0
	str	w0, [x19, 4668]
	mov	w0, 0
	ldr	w4, [x30, 4076]
	bfi	w2, w4, 0, 1
	str	w2, [x19, 5308]
	ldr	w2, [x20, 176]
	str	w2, [x19, 5284]
	ldr	w2, [x20, 180]
	str	w2, [x19, 5288]
	ldr	w2, [x20, 184]
	str	w2, [x19, 5292]
	ldr	w2, [x20, 188]
	str	w2, [x19, 5296]
	ldr	w2, [x20, 192]
	str	w2, [x19, 5300]
	ldr	w2, [x20, 196]
	str	w2, [x19, 5304]
	ldr	w2, [x30, 3264]
	bfi	w0, w2, 0, 16
	ldr	w2, [x30, 3268]
	bfi	w0, w2, 16, 16
	str	w0, [x19, 5764]
	mov	w2, 0
	ldr	x0, .LC7
	ldr	w4, [x30, 3280]
	bfi	w3, w4, 16, 16
	str	w3, [x19, 5768]
	ldr	x0, [x0]
	ldr	w4, [x30, 3272]
	ldr	w3, [x30, 3276]
	bfi	w2, w4, 0, 16
	bfi	w2, w3, 16, 16
	str	w2, [x19, 5772]
	mov	w3, 9729
	mov	w2, 513
	ldr	w4, [x20, 540]
	cmp	w4, wzr
	ldr	x4, [x29, 104]
	csel	w2, w2, w3, eq
	mov	w3, 0
	ldr	w4, [x4, 8168]
	bfi	w1, w4, 8, 3
	bfi	w1, w2, 16, 16
	str	w1, [x0, 7680]
	mov	w2, 0
	mov	w1, 16
	ldr	w4, [x20, 636]
	bfi	w3, w4, 0, 5
	ldr	w4, [x20, 640]
	bfi	w3, w4, 16, 16
	str	w3, [x0, 7684]
	mov	w4, 0
	ldr	w3, [x21, 5824]
	bfi	w2, w3, 0, 5
	ldr	w3, [x21, 5828]
	bfi	w2, w3, 16, 16
	str	w2, [x0, 7724]
	ldr	w2, [x20, 636]
	sub	w3, w1, w2
	ldr	w2, [x20, 676]
	lsl	w2, w2, w3
	bfi	w5, w2, 0, 16
	str	w5, [x0, 7688]
	ldr	w3, [x21, 5824]
	ldr	w2, [x21, 5820]
	sub	w1, w1, w3
	lsl	w1, w2, w1
	bfi	w4, w1, 0, 16
	str	w4, [x0, 7728]
	ldr	w1, [x20, 8]
	cmp	w1, 2
	beq	.L86
	ldr	w1, [x20, 604]
	str	w1, [x0, 8196]
	ldr	w1, [x20, 608]
	str	w1, [x0, 8200]
	ldr	w1, [x20, 612]
	str	w1, [x0, 8204]
	ldr	w1, [x20, 616]
	str	w1, [x0, 8208]
	ldr	w1, [x20, 620]
	str	w1, [x0, 8212]
	ldr	w1, [x20, 624]
	str	w1, [x0, 8216]
	ldr	w1, [x20, 628]
	str	w1, [x0, 8220]
	ldr	w1, [x20, 632]
	str	w1, [x0, 8224]
	ldr	w1, [x20, 636]
	ldr	w2, [x0, 8228]
	sub	w1, w1, #1
	bfi	w2, w1, 16, 7
	str	w2, [x0, 8228]
	ldr	w1, [x20, 636]
	ldr	w2, [x0, 8228]
	lsr	w3, w1, 8
	sub	w1, w3, #1
	bfi	w2, w1, 8, 6
	str	w2, [x0, 8228]
	ldrh	w1, [x20, 638]
	ldr	w2, [x0, 8228]
	sub	w1, w1, #1
	bfi	w2, w1, 0, 6
	str	w2, [x0, 8228]
.L55:
	ldr	w1, [x20, 8]
	cmp	w1, 2
	beq	.L87
	ldr	w1, [x21, 5756]
	str	w1, [x0, 8236]
	ldr	w1, [x21, 5760]
	str	w1, [x0, 8240]
	ldr	w1, [x21, 5764]
	str	w1, [x0, 8244]
	ldr	w1, [x21, 5768]
	str	w1, [x0, 8248]
	ldr	w1, [x21, 5772]
	str	w1, [x0, 8252]
	ldr	w1, [x21, 5776]
	str	w1, [x0, 8256]
	ldr	w1, [x21, 5780]
	str	w1, [x0, 8260]
	ldr	w1, [x21, 5784]
	str	w1, [x0, 8264]
	ldr	w1, [x21, 5752]
	ldr	w2, [x0, 8268]
	sub	w1, w1, #1
	bfi	w2, w1, 16, 7
	str	w2, [x0, 8268]
	ldr	w1, [x21, 5752]
	ldr	w2, [x0, 8268]
	lsr	w3, w1, 8
	sub	w1, w3, #1
	bfi	w2, w1, 8, 6
	str	w2, [x0, 8268]
	ldrh	w1, [x21, 5754]
	ldr	w2, [x0, 8268]
	sub	w1, w1, #1
	bfi	w2, w1, 0, 6
	str	w2, [x0, 8268]
.L62:
	ldr	w1, [x0, 8232]
	mov	w3, 0
	mov	w4, 0
	mov	w5, -85
	and	w1, w1, -33554431
	str	w1, [x0, 8232]
	mov	w6, 0
	add	x1, x30, 2440
	ldr	w2, [x0, 8232]
	bfi	w6, w5, 0, 8
	and	w2, w2, -2
	str	w2, [x0, 8232]
	str	w3, [x0, 8232]
	mov	w0, 85
	bfi	w6, w0, 8, 8
	mov	w0, 0
	ldr	w2, [x20, 268]
	str	w2, [x19, 9220]
	ldr	w2, [x20, 52]
	bfi	w4, w2, 0, 1
	str	w4, [x19, 9232]
	mov	w2, 0
	mov	w4, 0
	ldr	w5, [x30, 4184]
	str	w5, [x19, 9236]
	mov	w5, 0
	ldr	w7, [x20, 540]
	cmp	w7, wzr
	cset	w7, ne
	str	w7, [x19, 9240]
	ldr	w7, [x20, 680]
	str	w7, [x19, 9244]
	str	wzr, [x19, 9248]
	str	wzr, [x19, 9252]
	str	wzr, [x19, 9256]
	str	w6, [x19, 9728]
	ldr	w6, [x1, 976]
	bfi	w3, w6, 0, 6
	ldr	w6, [x1, 980]
	bfi	w3, w6, 8, 2
	ldr	w6, [x1, 984]
	bfi	w3, w6, 10, 1
	ldr	w6, [x1, 988]
	bfi	w3, w6, 12, 4
	ldr	w6, [x1, 992]
	bfi	w3, w6, 16, 5
	str	w3, [x19, 12240]
	ldr	w3, [x1, 1036]
	str	w3, [x19, 12244]
	ldr	w3, [x1, 1040]
	str	w3, [x19, 12248]
	ldr	w3, [x1, 1044]
	bfi	w0, w3, 0, 16
	ldr	w3, [x1, 1048]
	bfi	w0, w3, 16, 2
	ldr	w3, [x1, 1052]
	bfi	w0, w3, 18, 2
	ldr	w3, [x1, 1056]
	bfi	w0, w3, 20, 4
	ldr	w3, [x1, 1060]
	bfi	w0, w3, 24, 1
	ldr	w3, [x1, 1068]
	bfi	w0, w3, 25, 2
	ldr	w3, [x1, 1072]
	bfi	w0, w3, 27, 1
	ldr	w3, [x1, 1064]
	bfi	w0, w3, 28, 1
	str	w0, [x19, 12252]
	ldr	w3, [x1, 1104]
	ldr	w0, [x1, 1100]
	bfi	w2, w3, 0, 1
	ldr	w3, [x1, 1096]
	bfi	w2, w0, 2, 2
	ldr	w0, [x1, 1092]
	bfi	w2, w3, 4, 2
	ldr	w3, [x1, 1112]
	bfi	w2, w0, 6, 1
	ldr	w0, [x1, 1116]
	bfi	w2, w3, 8, 6
	bfi	w2, w0, 24, 6
	str	w2, [x19, 12256]
	ldr	w3, [x1, 1120]
	ldr	w0, [x1, 1124]
	ldr	w2, [x1, 1128]
	bfi	w4, w3, 0, 6
	bfi	w4, w0, 8, 6
	ldr	w0, [x1, 1132]
	bfi	w4, w2, 16, 6
	bfi	w4, w0, 24, 6
	str	w4, [x19, 12260]
	ldr	w2, [x1, 1136]
	ldr	w0, [x20, 8]
	ldr	w1, [x1, 1140]
	bfi	w5, w2, 0, 6
	bfi	w5, w1, 6, 25
	ldr	w1, [x20, 20]
	cbz	w0, .L88
	ldr	w0, [x20, 544]
	lsr	w2, w1, 6
	udiv	w0, w0, w2
	bfi	w5, w0, 6, 25
.L66:
	str	w5, [x19, 12264]
	mov	w0, 0
	ldr	x2, .LC7
	mov	w1, 0
	ldr	w6, [x20, 576]
	ldr	w3, [x20, 572]
	ldr	w4, [x20, 568]
	bfi	w0, w6, 10, 1
	bfi	w0, w3, 9, 1
	ldr	w3, [x30, 4120]
	ldr	w6, [x30, 4124]
	bfi	w0, w4, 8, 1
	bfi	w0, w3, 7, 1
	ldr	w3, [x30, 4100]
	ldr	w4, [x30, 4096]
	bfi	w0, w6, 6, 1
	bfi	w0, w3, 5, 1
	ldr	w3, [x30, 4128]
	ldr	w6, [x30, 4132]
	bfi	w0, w4, 4, 1
	bfi	w0, w3, 3, 1
	ldr	w4, [x30, 4136]
	ldr	w3, [x30, 4140]
	bfi	w0, w6, 2, 1
	bfi	w0, w4, 1, 1
	ldr	x2, [x2]
	bfi	w0, w3, 0, 1
	str	w0, [x19, 504]
	add	x0, x2, 61440
	add	x4, x19, 61440
	ldr	w7, [x30, 4104]
	mov	w3, 0
	ldr	w2, [x30, 4144]
	mov	w6, 3
	bfi	w1, w7, 7, 1
	ldr	w7, [x30, 4168]
	bfi	w1, w2, 6, 1
	ldr	w2, [x30, 4148]
	bfi	w1, w2, 5, 1
	ldr	w2, [x30, 4152]
	bfi	w1, w2, 4, 1
	ldr	w2, [x30, 4156]
	bfi	w1, w2, 3, 1
	ldr	w2, [x30, 4160]
	bfi	w1, w2, 2, 1
	ldr	w2, [x30, 4164]
	bfi	w1, w2, 1, 1
	mov	w2, 1
	bfi	w1, w7, 0, 1
	str	w1, [x19, 508]
	ldr	w7, [x30, 4088]
	ldr	w1, [x30, 4092]
	bfi	w3, w7, 0, 1
	bfi	w3, w1, 3, 1
	bfi	w3, w6, 16, 4
	str	w3, [x4]
	str	wzr, [x4, 32]
	ldr	w1, [x20, 580]
	str	w1, [x0, 520]
	ldr	w1, [x20, 580]
	str	w1, [x0, 524]
	ldr	w1, [x20, 588]
	str	w1, [x0, 752]
	ldr	w1, [x20, 584]
	str	w1, [x0, 756]
	ldr	w1, [x20, 588]
	str	w1, [x0, 772]
	ldr	w1, [x20, 584]
	str	w1, [x0, 776]
	str	wzr, [x4, 8]
	str	wzr, [x19, 16]
	str	w2, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L44:
	ldr	w1, [x21, 84]
	mov	w0, 0
	bfi	w0, w1, 0, 4
	b	.L45
.L41:
	mov	w1, 15
	mov	w0, 0
	bfi	w0, w1, 0, 5
	bfi	w0, w1, 5, 5
	bfi	w0, w1, 10, 5
	bfi	w0, w1, 15, 5
	and	w0, w0, -1048577
	str	w0, [x19, 2052]
	b	.L42
.L71:
	mov	w2, 6
.L37:
	bfi	w1, w2, 6, 4
	and	w1, w1, -16385
.L38:
	ldrb	w2, [x20, 68]
	b	.L39
.L85:
	mov	w0, 15
	mov	w22, 0
	bfi	w22, w0, 16, 6
	mov	w0, 31
	bfi	w22, w0, 0, 7
	b	.L36
.L88:
	ldr	w0, [x20, 544]
	lsr	w2, w1, 4
	udiv	w0, w0, w2
	bfi	w5, w0, 6, 25
	b	.L66
.L82:
	ldr	w0, [x20, 16]
	cmp	w0, 1919
	bhi	.L89
	cmp	w0, 719
	bhi	.L90
	ldr	x1, [x29, 104]
	mov	w0, 1
	str	w0, [x1, 6424]
	ldr	w0, [x20, 8]
	cbnz	w0, .L25
.L83:
	ldr	w1, [x20, 12]
	mov	w0, 5
	mov	w4, 7
	cmp	w1, wzr
	cset	w3, eq
	cmp	w1, 3
	csel	w0, w0, w4, ne
	cset	w2, ne
	str	w0, [x21, 5724]
	str	w2, [x21, 5728]
	str	w3, [x21, 5732]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	bne	.L91
.L28:
	ldr	x4, [x29, 104]
	mov	w2, 28
	str	w2, [x20, 548]
	add	x30, x4, 4096
	str	w2, [x20, 552]
	str	w2, [x20, 556]
	add	x0, x30, 3804
	str	wzr, [x4, 804]
	add	x1, x30, 3832
	str	wzr, [x20, 24]
	str	wzr, [x30, 3472]
	str	wzr, [x30, 3764]
	.p2align 2
.L31:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 220]
	cmp	x0, x1
	bne	.L31
	b	.L32
.L84:
	ldp	w0, w1, [x20, 16]
	mov	w2, 32
	lsr	w3, w1, 2
	lsr	w4, w0, 2
	sub	w1, w3, #16
	sub	w0, w4, #16
	lsr	w3, w1, 1
	lsr	w4, w0, 1
	cmp	w3, w2
	csel	w3, w3, w2, ls
	cmp	w4, 72
	and	w1, w3, 2147483644
	mov	w3, 72
	csel	w4, w4, w3, ls
	cmp	w1, 7
	and	w0, w4, 2147483644
	mov	w3, 7
	bls	.L34
	cmp	w1, w2
	csel	w1, w1, w2, ls
	sub	w1, w1, #1
	and	w3, w1, 63
.L34:
	cmp	w0, 7
	mov	w2, 7
	bls	.L35
	mov	w1, 72
	cmp	w0, w1
	csel	w0, w0, w1, ls
	sub	w0, w0, #1
	and	w2, w0, 127
.L35:
	mov	w22, 0
	bfi	w22, w3, 16, 6
	bfi	w22, w2, 0, 7
	b	.L36
.L87:
	ldr	w1, [x21, 5828]
	cmp	w1, 31
	bls	.L92
	ldr	w1, [x21, 5788]
	str	w1, [x0, 7732]
	ldr	w1, [x21, 5828]
	cmp	w1, 63
	bhi	.L59
.L94:
	ldr	w2, [x21, 5792]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 7736]
.L60:
	ldr	w3, [x21, 5828]
	cmp	w3, 64
	bls	.L61
	ldr	w1, [x21, 5796]
	mov	w2, 96
	sub	w2, w2, w3
	lsl	w1, w1, w2
	str	w1, [x0, 7740]
.L61:
	ldr	w1, [x21, 5800]
	str	w1, [x0, 7744]
	ldr	w1, [x21, 5804]
	str	w1, [x0, 7748]
	ldr	w1, [x21, 5808]
	str	w1, [x0, 7752]
	ldr	w1, [x21, 5812]
	str	w1, [x0, 7756]
	ldr	w1, [x21, 5816]
	str	w1, [x0, 7760]
	b	.L62
.L86:
	ldr	w1, [x20, 640]
	cmp	w1, 31
	bls	.L93
	ldr	w1, [x20, 644]
	str	w1, [x0, 7692]
	ldr	w1, [x20, 640]
	cmp	w1, 63
	bhi	.L52
.L95:
	ldr	w2, [x20, 648]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 7696]
.L53:
	ldr	w1, [x20, 640]
	cmp	w1, 64
	bls	.L54
	ldr	w2, [x20, 652]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 7700]
.L54:
	ldr	w1, [x20, 656]
	str	w1, [x0, 7704]
	ldr	w1, [x20, 660]
	str	w1, [x0, 7708]
	ldr	w1, [x20, 664]
	str	w1, [x0, 7712]
	ldr	w1, [x20, 668]
	str	w1, [x0, 7716]
	ldr	w1, [x20, 672]
	str	w1, [x0, 7720]
	b	.L55
.L92:
	ldr	w2, [x21, 5788]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 7732]
	ldr	w1, [x21, 5828]
	cmp	w1, 63
	bls	.L94
.L59:
	ldr	w1, [x21, 5792]
	str	w1, [x0, 7736]
	b	.L60
.L93:
	ldr	w2, [x20, 644]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 7692]
	ldr	w1, [x20, 640]
	cmp	w1, 63
	bls	.L95
.L52:
	ldr	w1, [x20, 648]
	str	w1, [x0, 7696]
	b	.L53
.L89:
	ldr	x1, [x29, 104]
	mov	w0, 3
	str	w0, [x1, 6424]
	b	.L22
.L90:
	ldr	x1, [x29, 104]
	mov	w0, 2
	str	w0, [x1, 6424]
	b	.L22
	.size	DRV_VENC_HAL_DirectCfgReg, .-DRV_VENC_HAL_DirectCfgReg
	.align	3
.LC7:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ClrInt
	.type	DRV_VENC_HAL_V400R004C02_ClrInt, %function
DRV_VENC_HAL_V400R004C02_ClrInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC8
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L98
	cbz	w19, .L99
	cmp	w19, 2
	beq	.L100
	mov	w1, -1
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L100:
	ldr	w1, [x0, 12]
	orr	w1, w1, 134217728
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L99:
	ldr	w1, [x0, 12]
	orr	w1, w1, 1
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L98:
	ldr	w1, [x0, 12]
	orr	w1, w1, 1024
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_ClrInt, .-DRV_VENC_HAL_V400R004C02_ClrInt
	.align	3
.LC8:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_DisableInt
	.type	DRV_VENC_HAL_V400R004C02_DisableInt, %function
DRV_VENC_HAL_V400R004C02_DisableInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC9
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L106
	cbz	w19, .L107
	cmp	w19, 2
	beq	.L108
	str	wzr, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L108:
	ldr	w1, [x0, 4]
	and	w1, w1, -134217729
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L107:
	ldr	w1, [x0, 4]
	and	w1, w1, -2
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L106:
	ldr	w1, [x0, 4]
	and	w1, w1, -1025
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_DisableInt, .-DRV_VENC_HAL_V400R004C02_DisableInt
	.align	3
.LC9:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.type	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, %function
DRV_VENC_HAL_V400R004C02_ReadReg_Smmu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC10
	mov	w3, -1
	mov	w0, 0
	ldr	x1, [x1]
	add	x1, x1, 61440
	ldr	w2, [x1, 40]
	and	w2, w2, 1
	str	w2, [x19]
	ldr	w2, [x1, 40]
	ubfx	x2, x2, 1, 1
	str	w2, [x19, 4]
	ldr	w2, [x1, 40]
	ubfx	x2, x2, 2, 1
	str	w2, [x19, 8]
	ldr	w2, [x1, 40]
	ubfx	x2, x2, 3, 1
	str	w2, [x19, 12]
	ldr	w2, [x1, 24]
	and	w2, w2, 1
	str	w2, [x19, 16]
	ldr	w2, [x1, 24]
	ubfx	x2, x2, 1, 1
	str	w2, [x19, 20]
	ldr	w2, [x1, 24]
	ubfx	x2, x2, 2, 1
	str	w2, [x19, 24]
	ldr	w2, [x1, 24]
	ubfx	x2, x2, 3, 1
	str	w2, [x19, 28]
	ldr	w2, [x1, 864]
	str	w2, [x19, 32]
	ldr	w2, [x1, 848]
	str	w2, [x19, 40]
	ldr	w2, [x1, 832]
	str	w2, [x19, 36]
	ldr	w2, [x1, 816]
	str	w2, [x19, 44]
	str	w3, [x1, 28]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, .-DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.align	3
.LC10:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ReadReg
	.type	DRV_VENC_HAL_V400R004C02_ReadReg, %function
DRV_VENC_HAL_V400R004C02_ReadReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC11
	ldp	x0, x4, [x1]
	ldr	w1, [x0]
	and	w1, w1, 1
	str	w1, [x19, 8]
	ldr	w1, [x0]
	ubfx	x3, x1, 1, 1
	str	w3, [x19, 12]
	ldr	w2, [x0]
	ubfx	x1, x2, 3, 1
	str	w1, [x19, 16]
	orr	w1, w3, w1
	ldr	w2, [x0]
	ubfx	x2, x2, 27, 1
	str	w2, [x19]
	ldr	w2, [x0]
	ubfx	x2, x2, 10, 1
	str	w2, [x19, 4]
	cbnz	w1, .L114
	ldr	w2, [x0, 5740]
	add	x5, x4, 8
	ubfx	x2, x2, 0, 26
	str	w2, [x19, 24]
	ldr	w1, [x4, 8]
	cbz	w1, .L117
	ldr	w1, [x0, 7808]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w1, [x0, 5636]
	ldr	w0, [x0, 5668]
	ubfx	x1, x1, 0, 19
	ubfx	x0, x0, 0, 17
	add	w0, w1, w0
	str	w0, [x19, 28]
	ldp	w3, w1, [x5, 8]
	add	w3, w3, 7
	add	w1, w1, 7
	lsr	w3, w3, 3
	lsr	w1, w1, 3
	mul	w1, w3, w1
	udiv	w2, w2, w1
	str	w2, [x19, 24]
.L116:
	lsr	w0, w0, 2
	str	w0, [x19, 28]
.L114:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L117:
	ldr	w1, [x0, 8324]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w4, [x0, 5640]
	ldr	w3, [x0, 5644]
	ldr	w1, [x0, 5672]
	ubfx	x4, x4, 0, 19
	ubfx	x0, x3, 0, 19
	ubfx	x1, x1, 0, 19
	add	w0, w4, w0
	add	w0, w0, w1
	str	w0, [x19, 28]
	ldp	w3, w1, [x5, 8]
	add	w3, w3, 15
	add	w1, w1, 15
	lsr	w3, w3, 4
	lsr	w1, w1, 4
	mul	w1, w3, w1
	udiv	w2, w2, w1
	str	w2, [x19, 24]
	b	.L116
	.size	DRV_VENC_HAL_V400R004C02_ReadReg, .-DRV_VENC_HAL_V400R004C02_ReadReg
	.align	3
.LC11:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_CfgReg
	.type	DRV_VENC_HAL_V400R004C02_CfgReg, %function
DRV_VENC_HAL_V400R004C02_CfgReg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x21, 60]
	cbnz	w0, .L183
	mov	x0, x21
	bl	DRV_VENC_HAL_DirectCfgReg
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L183:
	ldr	x3, .LC12
	mov	x2, 704
	ldr	x0, .LC13
	mov	x1, x21
	ldr	x19, [x21, 696]
	ldr	x3, [x3, 8]
	mov	x4, x3
	ldr	x3, [x0, 8]
	ldr	x0, .LC12
	add	x22, x4, x2
	str	x4, [x29, 104]
	ldr	x23, [x0]
	mov	x0, x4
	blr	x3
	ldr	w2, [x21, 540]
	mov	x0, x22
	ldr	w1, [x21, 548]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	ldr	w1, [x21, 8]
	mov	x0, x22
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	w0, [x21, 44]
	cbnz	w0, .L184
.L120:
	ldr	w0, [x21, 8]
	cbz	w0, .L185
	mov	w0, 7
	str	wzr, [x22, 5728]
	str	w0, [x22, 5724]
	str	wzr, [x22, 5732]
	ldr	w0, [x21, 16]
	ldr	w1, [x21, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	beq	.L126
.L193:
	ldr	x0, [x29, 104]
	add	x1, x0, 4096
.L130:
	ldr	w3, [x21, 44]
	mov	w2, 11
	mov	w0, 6
	ldr	x5, [x29, 104]
	bfi	w2, w3, 10, 1
	orr	w2, w2, 134217728
	str	w2, [x23, 4]
	ldr	w4, [x21, 8]
	ldr	w3, [x1, 4068]
	cmp	w4, 2
	ldr	w5, [x5, 6536]
	cset	w2, ne
	bfi	w0, w2, 3, 2
	ldr	w2, [x21, 44]
	bfi	w0, w2, 5, 1
	bfi	w0, w3, 6, 1
	ldr	w3, [x1, 4064]
	bfi	w0, w3, 7, 1
	ldr	w3, [x21, 540]
	and	w0, w0, -16777473
	cmp	w3, wzr
	bfi	w0, w5, 9, 1
	cset	w6, eq
	ldr	w5, [x22, 5732]
	bfi	w0, w6, 10, 2
	cmp	w4, 2
	bfi	w0, w5, 12, 1
	bfi	w0, w3, 16, 1
	ldr	w3, [x22, 5728]
	orr	w0, w0, 131072
	bfi	w0, w3, 18, 2
	mov	w3, 2
	and	w0, w0, -6291457
	csel	w3, w3, wzr, eq
	and	w0, w0, -33554433
	bfi	w0, w3, 26, 2
	ldr	w3, [x21, 48]
	bfi	w0, w3, 28, 2
	and	w0, w0, 1073741823
	str	w0, [x23, 20]
	str	wzr, [x19, 512]
	ldr	w0, [x21, 24]
	ldr	w3, [x21, 32]
	ubfiz	w0, w0, 17, 1
	bfi	w0, w3, 0, 16
	str	w0, [x19, 516]
	mov	w0, 0
	ldr	w3, [x21, 548]
	bfi	w0, w3, 10, 6
	ldr	w3, [x1, 3472]
	bfi	w0, w3, 18, 1
	ldr	w3, [x1, 3456]
	bfi	w0, w3, 19, 1
	str	w0, [x23, 32]
	str	wzr, [x23, 36]
	mov	w0, 458752
	str	wzr, [x23, 40]
	str	wzr, [x19, 520]
	ldr	w3, [x1, 4172]
	bfi	w0, w3, 19, 2
	ldr	w3, [x1, 4176]
	bfi	w0, w3, 21, 1
	mov	w3, 0
	and	w0, w0, -8388609
	str	w0, [x23, 48]
	ldr	w0, [x21, 20]
	sub	w0, w0, #1
	bfi	w3, w0, 16, 13
	ldr	w0, [x21, 16]
	sub	w0, w0, #1
	bfi	w3, w0, 0, 13
	str	w3, [x19]
	mov	w0, 0
	str	w0, [x23, 56]
	ldr	w3, [x1, 4180]
	str	w3, [x23, 60]
	ldr	w3, [x1, 4080]
	ldr	w2, [x1, 4084]
	bfi	w0, w3, 4, 4
	bfi	w0, w2, 0, 4
	str	w0, [x23, 64]
	ldr	w0, [x21, 8]
	cmp	w0, 2
	beq	.L186
	cbz	w0, .L187
.L134:
	mov	w3, 3
	mov	w0, 0
	mov	w2, 1
	bfi	w0, w3, 0, 3
	bfi	w0, w2, 3, 2
	str	w2, [x19, 524]
	stp	w24, w3, [x19, 16]
	bfi	w0, w3, 5, 3
	mov	w2, 0
	bfi	w0, w3, 8, 3
	str	w0, [x23, 100]
	mov	w6, 0
	mov	w5, 0
	ldr	w0, [x21, 200]
	mov	w4, 0
	str	w0, [x19, 128]
	ldr	w0, [x21, 72]
	str	w0, [x19, 132]
	ldr	w0, [x21, 76]
	str	w0, [x19, 136]
	ldr	w0, [x21, 80]
	str	w0, [x19, 140]
	ldr	w0, [x21, 84]
	bfi	w2, w0, 16, 16
	ldr	w0, [x21, 88]
	bfi	w2, w0, 0, 16
	str	w2, [x19, 152]
	mov	w0, 0
	ldr	w2, [x21, 172]
	add	x2, x2, 40
	ldr	w2, [x21, x2, lsl 2]
	str	w2, [x19, 156]
	ldr	w2, [x21, 140]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 92]
	str	w2, [x19, 160]
	ldr	w2, [x21, 140]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 100]
	str	w2, [x19, 164]
	ldr	w2, [x21, 108]
	bfi	w0, w2, 0, 16
	ldr	w2, [x21, 112]
	bfi	w0, w2, 16, 16
	str	w0, [x19, 168]
	mov	w2, 0
	ldr	w0, [x21, 140]
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 116]
	str	w0, [x19, 172]
	ldr	w0, [x21, 140]
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 124]
	str	w0, [x19, 176]
	ldr	w0, [x21, 132]
	bfi	w6, w0, 0, 16
	str	w6, [x19, 180]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 20
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 12]
	str	w0, [x19, 184]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 24
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 4]
	str	w0, [x19, 188]
	ldr	w0, [x21, 112]
	bfi	w5, w0, 0, 16
	ldr	w0, [x21, 108]
	bfi	w5, w0, 16, 16
	str	w5, [x19, 192]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 28
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 4]
	str	w0, [x19, 196]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 28
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 12]
	str	w0, [x19, 200]
	ldr	w0, [x21, 132]
	bfi	w4, w0, 16, 16
	ldr	w0, [x21, 136]
	bfi	w4, w0, 0, 16
	str	w4, [x19, 204]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 36
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 8]
	str	w0, [x19, 208]
	ldr	w0, [x21, 140]
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 152]
	str	w0, [x19, 212]
	ldr	w0, [x21, 140]
	add	x0, x0, 36
	ldr	w0, [x21, x0, lsl 2]
	str	w0, [x19, 48]
	ldr	w0, [x21, 140]
	cmp	w0, wzr
	cset	x0, eq
	add	x0, x0, 36
	ldr	w0, [x21, x0, lsl 2]
	str	w0, [x19, 52]
	ldr	w0, [x21, 204]
	str	w0, [x19, 56]
	ldr	w0, [x21, 336]
	str	w0, [x19, 60]
	ldr	w0, [x21, 332]
	str	w0, [x19, 64]
	ldr	w0, [x21, 64]
	cmp	w0, 2
	beq	.L135
	cmp	w0, 1
	beq	.L171
	and	w2, w2, -961
	and	w2, w2, -16385
	cbnz	w0, .L136
	ldr	w0, [x21, 68]
	cmp	w0, wzr
	cset	w3, eq
.L137:
	bfi	w2, w3, 16, 8
	str	w2, [x19, 4]
	add	x0, x1, 2440
	mov	w2, 0
	ldr	w3, [x22, 5724]
	mov	w4, 3
	mov	w13, 0
	mov	w12, 0
	bfi	w2, w3, 0, 3
	ldr	w3, [x0, 1620]
	str	w4, [x19, 72]
	mov	w11, 0
	bfi	w2, w3, 4, 1
	mov	w3, 5
	and	w2, w2, -33
	mov	w15, 0
	orr	w2, w2, 1792
	mov	w16, 0
	orr	w2, w2, 28672
	str	w2, [x19, 528]
	mov	w2, 0
	mov	w10, 0
	bfi	w2, w3, 24, 8
	mov	w30, 16
	bfi	w2, w3, 16, 8
	mov	w3, 15
	bfi	w2, w3, 8, 8
	mov	w28, 0
	bfi	w2, w3, 0, 8
	str	w2, [x19, 544]
	mov	w2, 24
	str	w2, [x19, 532]
	mov	w2, 500
	mov	w3, 0
	movk	w2, 0x64, lsl 16
	str	w2, [x19, 536]
	mov	w2, 0
	mov	w27, 0
	ldr	w4, [x0, 4]
	mov	w26, 0
	bfi	w3, w4, 0, 1
	ldr	w4, [x22, 4]
	bfi	w3, w4, 1, 1
	ldr	x4, [x29, 104]
	ldr	w4, [x4, 704]
	bfi	w3, w4, 2, 1
	mov	w4, 0
	orr	w3, w3, 8
	and	w3, w3, -17
	str	w3, [x23, 352]
	mov	w3, -128
	ldr	w5, [x21, 688]
	str	w5, [x23, 392]
	mov	w5, 0
	bfi	w5, w3, 0, 8
	ldr	w6, [x0, 1008]
	bfi	w5, w3, 8, 8
	bfi	w5, w3, 16, 8
	bfi	w2, w6, 0, 1
	ldr	w6, [x0, 1012]
	bfi	w2, w6, 1, 1
	ldr	w6, [x22, 92]
	bfi	w2, w6, 2, 1
	ldr	w6, [x0, 1028]
	bfi	w2, w6, 4, 1
	ldr	w6, [x22, 88]
	bfi	w2, w6, 8, 1
	ldr	w6, [x0, 1004]
	bfi	w2, w6, 9, 1
	ldr	w6, [x0, 1076]
	bfi	w2, w6, 10, 1
	ldr	w6, [x0, 1080]
	bfi	w2, w6, 11, 1
	ldr	w6, [x0, 1084]
	bfi	w2, w6, 12, 1
	ldr	w6, [x0, 1000]
	bfi	w2, w6, 13, 1
	ldr	w6, [x0, 996]
	bfi	w2, w6, 14, 1
	ldr	w6, [x0, 1088]
	bfi	w2, w6, 15, 1
	str	w2, [x23, 440]
	mov	w2, 2
	mov	w6, 128
	ldr	w7, [x22, 96]
	str	w5, [x19, 1760]
	bfi	w4, w7, 1, 1
	mov	w7, 1
	bfi	w4, w2, 16, 8
	bfi	w4, w2, 24, 8
	mov	w2, 0
	bfi	w2, w3, 0, 8
	str	w4, [x19, 540]
	bfi	w2, w3, 8, 8
	str	w2, [x19, 1764]
	mov	w2, 0
	mov	w3, 43691
	bfi	w2, w6, 0, 10
	movk	w3, 0xaaaa, lsl 16
	bfi	w2, w6, 10, 10
	str	w2, [x19, 1768]
	str	wzr, [x19, 32]
	mov	w2, 0
	ldr	w4, [x21, 172]
	add	w4, w4, 2
	umull	x5, w4, w3
	lsr	x6, x5, 32
	mov	w5, 0
	lsr	w9, w6, 1
	lsl	w8, w9, 2
	sub	w6, w8, w9
	mov	w9, 0
	sub	w4, w4, w6
	add	x4, x4, 40
	ldr	w4, [x21, x4, lsl 2]
	str	w4, [x19, 216]
	ldr	w4, [x21, 172]
	add	w4, w4, w7
	umull	x6, w4, w3
	lsr	x3, x6, 32
	lsr	w8, w3, 1
	lsl	w6, w8, 2
	sub	w3, w6, w8
	sub	w3, w4, w3
	add	x3, x3, 40
	ldr	w3, [x21, x3, lsl 2]
	str	w3, [x19, 220]
	str	w7, [x23, 492]
	ldrb	w25, [x0, 1392]
	ldrb	w24, [x0, 1388]
	ldrb	w18, [x0, 1384]
	ldrb	w17, [x0, 1380]
	orr	w4, w25, w24
	ldrb	w14, [x0, 1376]
	ldrb	w8, [x0, 1372]
	orr	w3, w18, w17
	ldrb	w7, [x0, 1368]
	orr	w4, w4, w3
	ldrb	w6, [x0, 1364]
	orr	w3, w14, w8
	orr	w4, w4, w3
	orr	w3, w7, w6
	orr	w3, w4, w3
	mov	w4, 0
	bfi	w2, w3, 24, 1
	ldr	w3, [x0, 1616]
	bfi	w2, w3, 23, 1
	ldr	w3, [x0, 1612]
	bfi	w2, w3, 22, 1
	ldr	w3, [x0, 1608]
	bfi	w2, w3, 21, 1
	ldr	w3, [x0, 1604]
	bfi	w2, w3, 20, 1
	ldr	w3, [x0, 1600]
	bfi	w2, w3, 19, 1
	ldr	w3, [x0, 1596]
	bfi	w2, w3, 18, 1
	ldr	w3, [x0, 1592]
	bfi	w2, w3, 17, 1
	ldr	w3, [x0, 1588]
	bfi	w2, w3, 16, 1
	ldr	w3, [x0, 1424]
	bfi	w2, w3, 15, 1
	ldr	w3, [x0, 1420]
	bfi	w2, w3, 14, 1
	ldr	w3, [x0, 1416]
	bfi	w2, w3, 13, 1
	ldr	w3, [x0, 1412]
	bfi	w2, w3, 12, 1
	ldr	w3, [x0, 1408]
	bfi	w2, w3, 11, 1
	ldr	w3, [x0, 1404]
	bfi	w2, w3, 10, 1
	ldr	w3, [x0, 1400]
	bfi	w2, w3, 9, 1
	ldr	w3, [x0, 1396]
	bfi	w2, w3, 8, 1
	mov	w3, 0
	bfi	w2, w25, 7, 1
	mov	w25, 0
	bfi	w2, w24, 6, 1
	mov	w24, 0
	bfi	w2, w18, 5, 1
	mov	w18, 0
	bfi	w2, w17, 4, 1
	mov	w17, 0
	bfi	w2, w14, 3, 1
	mov	w14, 0
	bfi	w2, w8, 2, 1
	mov	w8, 0
	bfi	w2, w7, 1, 1
	mov	w7, 0
	bfi	w2, w6, 0, 1
	str	w2, [x19, 1024]
	ldr	w2, [x0, 1440]
	mov	w6, 0
	bfi	w5, w2, 24, 7
	ldr	w2, [x0, 1436]
	bfi	w5, w2, 16, 7
	ldr	w2, [x0, 1432]
	bfi	w5, w2, 8, 7
	ldr	w2, [x0, 1428]
	bfi	w5, w2, 0, 7
	str	w5, [x19, 1028]
	mov	w5, 0
	ldr	w2, [x0, 1456]
	bfi	w13, w2, 24, 7
	ldr	w2, [x0, 1452]
	bfi	w13, w2, 16, 7
	ldr	w2, [x0, 1448]
	bfi	w13, w2, 8, 7
	ldr	w2, [x0, 1444]
	bfi	w13, w2, 0, 7
	str	w13, [x19, 1032]
	mov	w13, 0
	ldr	w2, [x0, 1492]
	bfi	w12, w2, 16, 10
	ldr	w2, [x0, 1460]
	bfi	w12, w2, 0, 10
	str	w12, [x19, 1036]
	mov	w12, 0
	ldr	w2, [x0, 1496]
	bfi	w11, w2, 16, 10
	ldr	w2, [x0, 1464]
	bfi	w11, w2, 0, 10
	str	w11, [x19, 1040]
	mov	w2, 0
	ldr	w11, [x0, 1500]
	bfi	w15, w11, 16, 10
	ldr	w11, [x0, 1468]
	bfi	w15, w11, 0, 10
	str	w15, [x19, 1044]
	ldr	w11, [x0, 1504]
	bfi	w16, w11, 16, 10
	ldr	w11, [x0, 1472]
	bfi	w16, w11, 0, 10
	str	w16, [x19, 1048]
	mov	w16, 0
	ldr	w11, [x0, 1508]
	bfi	w10, w11, 16, 10
	ldr	w11, [x0, 1476]
	bfi	w10, w11, 0, 10
	str	w10, [x19, 1052]
	mov	w11, 0
	ldr	w10, [x0, 1512]
	bfi	w9, w10, 16, 10
	ldr	w10, [x0, 1480]
	bfi	w9, w10, 0, 10
	str	w9, [x19, 1056]
	mov	w10, 0
	ldr	w9, [x0, 1516]
	bfi	w8, w9, 16, 10
	ldr	w9, [x0, 1484]
	bfi	w8, w9, 0, 10
	str	w8, [x19, 1060]
	mov	w9, 0
	ldr	w8, [x0, 1520]
	bfi	w7, w8, 16, 10
	ldr	w8, [x0, 1488]
	bfi	w7, w8, 0, 10
	str	w7, [x19, 1064]
	mov	w8, 0
	ldr	w7, [x0, 1556]
	bfi	w6, w7, 16, 9
	ldr	w7, [x0, 1524]
	bfi	w6, w7, 0, 9
	str	w6, [x19, 1068]
	mov	w7, 0
	ldr	w6, [x0, 1560]
	bfi	w5, w6, 16, 9
	ldr	w6, [x0, 1528]
	bfi	w5, w6, 0, 9
	str	w5, [x19, 1072]
	mov	w6, 0
	ldr	w5, [x0, 1564]
	bfi	w4, w5, 16, 9
	ldr	w5, [x0, 1532]
	bfi	w4, w5, 0, 9
	str	w4, [x19, 1076]
	mov	w5, 0
	ldr	w4, [x0, 1568]
	bfi	w3, w4, 16, 9
	ldr	w4, [x0, 1536]
	bfi	w3, w4, 0, 9
	str	w3, [x19, 1080]
	mov	w4, 0
	mov	w3, 0
	ldr	w15, [x0, 1572]
	bfi	w14, w15, 16, 9
	ldr	w15, [x0, 1540]
	bfi	w14, w15, 0, 9
	str	w14, [x19, 1084]
	mov	w15, 0
	ldr	w14, [x0, 1576]
	bfi	w13, w14, 16, 9
	ldr	w14, [x0, 1544]
	bfi	w13, w14, 0, 9
	str	w13, [x19, 1088]
	mov	w14, 0
	ldr	w13, [x0, 1580]
	bfi	w12, w13, 16, 9
	ldr	w13, [x0, 1548]
	bfi	w12, w13, 0, 9
	str	w12, [x19, 1092]
	mov	w13, 0
	ldr	w12, [x0, 1584]
	bfi	w2, w12, 16, 9
	ldr	w12, [x0, 1552]
	bfi	w2, w12, 0, 9
	str	w2, [x19, 1096]
	mov	w2, 0
	ldr	w12, [x21, 8]
	ldr	w20, [x21, 20]
	cmp	w12, wzr
	mov	w12, 64
	csel	w12, w12, w30, ne
	ldr	w30, [x21, 16]
	sub	w20, w20, #1
	sub	w30, w30, #1
	add	w20, w20, w12
	add	w30, w30, w12
	udiv	w30, w30, w12
	udiv	w12, w20, w12
	mul	w30, w30, w12
	ldr	w12, [x21, 544]
	udiv	w30, w12, w30
	mov	w12, 0
	bfi	w12, w30, 0, 20
	mov	w30, w12
	str	w30, [x23, 588]
	mov	w12, 0
	ldr	w30, [x0, 8]
	bfi	w28, w30, 16, 5
	ldr	w30, [x0, 12]
	bfi	w28, w30, 0, 10
	str	w28, [x19, 1536]
	mov	w30, 0
	ldr	w28, [x22, 8]
	bfi	w27, w28, 16, 5
	ldr	w28, [x0, 16]
	bfi	w27, w28, 0, 8
	str	w27, [x19, 1540]
	mov	w28, 0
	ldr	w27, [x0, 20]
	bfi	w26, w27, 16, 5
	ldr	w27, [x0, 24]
	bfi	w26, w27, 0, 10
	str	w26, [x19, 1544]
	mov	w26, 0
	ldr	w27, [x0, 28]
	bfi	w25, w27, 16, 5
	ldr	w27, [x22, 12]
	bfi	w25, w27, 0, 8
	str	w25, [x19, 1548]
	mov	w27, 0
	ldr	w25, [x0, 32]
	bfi	w27, w25, 16, 5
	ldr	w25, [x0, 36]
	bfi	w27, w25, 0, 10
	str	w27, [x19, 1552]
	mov	w27, 0
	ldr	w25, [x22, 16]
	bfi	w24, w25, 16, 5
	ldr	w25, [x22, 20]
	bfi	w24, w25, 0, 8
	str	w24, [x19, 1556]
	mov	w24, 0
	ldr	w25, [x0, 40]
	bfi	w28, w25, 16, 5
	ldr	w25, [x0, 44]
	bfi	w28, w25, 0, 10
	str	w28, [x19, 1560]
	mov	w28, 0
	ldr	w25, [x22, 24]
	bfi	w12, w25, 16, 5
	ldr	w25, [x22, 28]
	bfi	w12, w25, 0, 8
	mov	w25, w12
	str	w25, [x19, 1564]
	mov	w12, 0
	ldr	w25, [x0, 48]
	bfi	w11, w25, 12, 4
	ldr	w25, [x0, 52]
	bfi	w11, w25, 8, 4
	ldr	w25, [x0, 56]
	bfi	w11, w25, 4, 4
	ldr	w25, [x0, 60]
	bfi	w11, w25, 0, 4
	ldr	w25, [x0, 64]
	bfi	w11, w25, 28, 4
	ldr	w25, [x22, 32]
	bfi	w11, w25, 24, 4
	ldr	w25, [x0, 68]
	bfi	w11, w25, 20, 4
	ldr	w25, [x0, 72]
	bfi	w11, w25, 16, 4
	str	w11, [x19, 1568]
	mov	w25, 0
	ldr	w11, [x0, 76]
	bfi	w10, w11, 12, 4
	ldr	w11, [x0, 80]
	bfi	w10, w11, 8, 4
	ldr	w11, [x0, 84]
	bfi	w10, w11, 4, 4
	ldr	w11, [x0, 88]
	bfi	w10, w11, 0, 4
	ldr	w11, [x0, 92]
	bfi	w10, w11, 28, 4
	ldr	w11, [x0, 96]
	bfi	w10, w11, 24, 4
	ldr	w11, [x22, 36]
	bfi	w10, w11, 20, 4
	ldr	w11, [x0, 100]
	bfi	w10, w11, 16, 4
	str	w10, [x19, 1572]
	ldr	w10, [x0, 104]
	bfi	w9, w10, 12, 4
	ldr	w10, [x0, 108]
	bfi	w9, w10, 8, 4
	ldr	w10, [x0, 112]
	bfi	w9, w10, 4, 4
	ldr	w10, [x0, 116]
	bfi	w9, w10, 0, 4
	ldr	w10, [x0, 120]
	bfi	w9, w10, 28, 4
	ldr	w10, [x0, 124]
	bfi	w9, w10, 24, 4
	ldr	w10, [x22, 40]
	bfi	w9, w10, 20, 4
	ldr	w10, [x0, 128]
	bfi	w9, w10, 16, 4
	str	w9, [x19, 1576]
	mov	w10, 0
	ldr	w9, [x0, 132]
	bfi	w8, w9, 12, 4
	ldr	w9, [x22, 44]
	bfi	w8, w9, 8, 4
	ldr	w9, [x0, 136]
	bfi	w8, w9, 4, 4
	ldr	w9, [x0, 140]
	bfi	w8, w9, 0, 4
	ldr	w9, [x0, 144]
	bfi	w8, w9, 28, 4
	ldr	w9, [x0, 148]
	bfi	w8, w9, 24, 4
	ldr	w9, [x0, 152]
	bfi	w8, w9, 20, 4
	ldr	w9, [x0, 156]
	bfi	w8, w9, 16, 4
	str	w8, [x19, 1580]
	mov	w9, 0
	ldr	w8, [x0, 160]
	bfi	w7, w8, 12, 4
	ldr	w8, [x0, 164]
	bfi	w7, w8, 8, 4
	ldr	w8, [x22, 48]
	bfi	w7, w8, 4, 4
	ldr	w8, [x0, 168]
	bfi	w7, w8, 0, 4
	ldr	w8, [x0, 172]
	bfi	w7, w8, 28, 4
	ldr	w8, [x0, 176]
	bfi	w7, w8, 24, 4
	ldr	w8, [x0, 180]
	bfi	w7, w8, 20, 4
	ldr	w8, [x0, 184]
	bfi	w7, w8, 16, 4
	str	w7, [x19, 1584]
	mov	w7, 0
	ldr	w8, [x0, 188]
	bfi	w6, w8, 12, 4
	ldr	w8, [x0, 192]
	bfi	w6, w8, 8, 4
	ldr	w8, [x22, 52]
	bfi	w6, w8, 4, 4
	ldr	w8, [x0, 196]
	bfi	w6, w8, 0, 4
	ldr	w8, [x0, 200]
	bfi	w6, w8, 28, 4
	ldr	w8, [x0, 204]
	bfi	w6, w8, 24, 4
	ldr	w8, [x0, 208]
	bfi	w6, w8, 20, 4
	ldr	w8, [x0, 212]
	bfi	w6, w8, 16, 4
	str	w6, [x19, 1588]
	ldr	w6, [x0, 216]
	bfi	w5, w6, 12, 4
	ldr	w6, [x22, 56]
	bfi	w5, w6, 8, 4
	ldr	w6, [x0, 220]
	bfi	w5, w6, 4, 4
	ldr	w6, [x0, 224]
	bfi	w5, w6, 0, 4
	ldr	w6, [x0, 228]
	bfi	w5, w6, 28, 4
	ldr	w6, [x0, 232]
	bfi	w5, w6, 24, 4
	ldr	w6, [x0, 236]
	bfi	w5, w6, 20, 4
	ldr	w6, [x0, 240]
	bfi	w5, w6, 16, 4
	str	w5, [x19, 1592]
	mov	w6, 0
	mov	w5, 0
	ldr	w8, [x0, 244]
	bfi	w4, w8, 12, 4
	ldr	w8, [x0, 248]
	bfi	w4, w8, 8, 4
	ldr	w8, [x0, 252]
	bfi	w4, w8, 4, 4
	ldr	w8, [x0, 256]
	bfi	w4, w8, 0, 4
	ldr	w8, [x0, 260]
	bfi	w4, w8, 28, 4
	ldr	w8, [x0, 264]
	bfi	w4, w8, 24, 4
	ldr	w8, [x0, 268]
	bfi	w4, w8, 20, 4
	ldr	w8, [x0, 272]
	bfi	w4, w8, 16, 4
	str	w4, [x19, 1596]
	mov	w4, 0
	ldr	w8, [x0, 276]
	bfi	w3, w8, 12, 4
	ldr	w8, [x0, 280]
	bfi	w3, w8, 8, 4
	ldr	w8, [x0, 284]
	bfi	w3, w8, 4, 4
	ldr	w8, [x0, 288]
	bfi	w3, w8, 0, 4
	ldr	w8, [x0, 292]
	bfi	w3, w8, 28, 4
	ldr	w8, [x0, 296]
	bfi	w3, w8, 24, 4
	ldr	w8, [x0, 300]
	bfi	w3, w8, 20, 4
	ldr	w8, [x0, 304]
	bfi	w3, w8, 16, 4
	str	w3, [x19, 1600]
	mov	w8, 0
	ldr	w3, [x0, 308]
	bfi	w18, w3, 0, 3
	ldr	w3, [x0, 312]
	bfi	w18, w3, 3, 7
	ldr	w3, [x0, 316]
	bfi	w18, w3, 10, 3
	ldr	w3, [x0, 320]
	bfi	w18, w3, 13, 5
	ldr	w3, [x0, 324]
	bfi	w18, w3, 18, 4
	ldr	w3, [x0, 328]
	bfi	w18, w3, 22, 4
	ldr	w3, [x0, 332]
	bfi	w18, w3, 26, 4
	str	w18, [x19, 1604]
	mov	w3, 0
	mov	w18, 0
	ldr	w11, [x0, 336]
	bfi	w17, w11, 0, 3
	ldr	w11, [x0, 340]
	bfi	w17, w11, 3, 7
	ldr	w11, [x0, 344]
	bfi	w17, w11, 10, 3
	ldr	w11, [x0, 348]
	bfi	w17, w11, 13, 5
	ldr	w11, [x0, 352]
	bfi	w17, w11, 18, 4
	ldr	w11, [x0, 356]
	bfi	w17, w11, 22, 4
	ldr	w11, [x0, 360]
	bfi	w17, w11, 26, 4
	str	w17, [x19, 1608]
	mov	w17, 0
	ldr	w11, [x0, 364]
	bfi	w16, w11, 0, 3
	ldr	w11, [x0, 368]
	bfi	w16, w11, 3, 7
	ldr	w11, [x0, 372]
	bfi	w16, w11, 10, 3
	ldr	w11, [x0, 376]
	bfi	w16, w11, 13, 5
	ldr	w11, [x0, 380]
	bfi	w16, w11, 18, 4
	ldr	w11, [x0, 384]
	bfi	w16, w11, 22, 4
	ldr	w11, [x0, 388]
	bfi	w16, w11, 26, 4
	str	w16, [x19, 1612]
	mov	w16, 0
	ldr	w11, [x0, 656]
	bfi	w15, w11, 0, 3
	ldr	w11, [x0, 660]
	bfi	w15, w11, 3, 7
	ldr	w11, [x0, 664]
	bfi	w15, w11, 10, 3
	ldr	w11, [x0, 668]
	bfi	w15, w11, 13, 5
	ldr	w11, [x0, 672]
	bfi	w15, w11, 18, 4
	ldr	w11, [x0, 676]
	bfi	w15, w11, 22, 4
	ldr	w11, [x0, 680]
	bfi	w15, w11, 26, 4
	str	w15, [x19, 1616]
	mov	w15, 0
	ldr	w11, [x0, 684]
	bfi	w14, w11, 0, 3
	ldr	w11, [x0, 688]
	bfi	w14, w11, 3, 7
	ldr	w11, [x0, 692]
	bfi	w14, w11, 10, 3
	ldr	w11, [x0, 696]
	bfi	w14, w11, 13, 5
	ldr	w11, [x0, 700]
	bfi	w14, w11, 18, 4
	ldr	w11, [x0, 704]
	bfi	w14, w11, 22, 4
	ldr	w11, [x0, 708]
	bfi	w14, w11, 26, 4
	str	w14, [x19, 1620]
	mov	w14, 0
	ldr	w11, [x22, 68]
	bfi	w13, w11, 0, 3
	ldr	w11, [x0, 712]
	bfi	w13, w11, 3, 7
	ldr	w11, [x0, 716]
	bfi	w13, w11, 10, 3
	ldr	w11, [x0, 720]
	bfi	w13, w11, 13, 5
	ldr	w11, [x0, 724]
	bfi	w13, w11, 18, 4
	ldr	w11, [x0, 728]
	bfi	w13, w11, 22, 4
	ldr	w11, [x0, 732]
	bfi	w13, w11, 26, 4
	str	w13, [x19, 1624]
	mov	w11, 0
	ldr	w13, [x0, 736]
	bfi	w12, w13, 0, 3
	ldr	w13, [x0, 740]
	bfi	w12, w13, 3, 7
	ldr	w13, [x0, 744]
	bfi	w12, w13, 10, 3
	ldr	w13, [x0, 748]
	bfi	w12, w13, 13, 5
	ldr	w13, [x0, 752]
	bfi	w12, w13, 18, 4
	ldr	w13, [x0, 756]
	bfi	w12, w13, 22, 4
	ldr	w13, [x0, 760]
	bfi	w12, w13, 26, 4
	str	w12, [x19, 1628]
	mov	w12, 0
	mov	w13, 0
	ldr	w20, [x0, 392]
	bfi	w2, w20, 0, 4
	ldr	w20, [x0, 396]
	bfi	w2, w20, 4, 4
	ldr	w20, [x0, 400]
	bfi	w2, w20, 8, 4
	ldr	w20, [x0, 404]
	bfi	w2, w20, 12, 4
	ldr	w20, [x0, 408]
	bfi	w2, w20, 16, 4
	ldr	w20, [x0, 412]
	bfi	w2, w20, 20, 4
	ldr	w20, [x0, 416]
	bfi	w2, w20, 24, 4
	ldr	w20, [x0, 420]
	bfi	w2, w20, 28, 4
	str	w2, [x19, 1632]
	mov	w20, -16711936
	ldr	w2, [x0, 424]
	bfi	w12, w2, 0, 4
	ldr	w2, [x0, 428]
	bfi	w12, w2, 4, 4
	ldr	w2, [x0, 432]
	bfi	w12, w2, 8, 4
	ldr	w2, [x0, 436]
	bfi	w12, w2, 12, 4
	ldr	w2, [x0, 440]
	bfi	w12, w2, 16, 4
	ldr	w2, [x0, 444]
	bfi	w12, w2, 20, 4
	mov	w2, w12
	str	w2, [x19, 1636]
	mov	w12, 0
	ldr	w2, [x0, 448]
	bfi	w12, w2, 0, 10
	ldr	w2, [x0, 452]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1640]
	mov	w12, 0
	ldr	w2, [x22, 60]
	bfi	w12, w2, 0, 8
	ldr	w2, [x22, 64]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1644]
	mov	w12, 0
	ldr	w2, [x0, 456]
	bfi	w12, w2, 0, 10
	ldr	w2, [x0, 460]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1648]
	mov	w12, 0
	ldr	w2, [x0, 464]
	bfi	w12, w2, 0, 8
	ldr	w2, [x0, 468]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1652]
	mov	w12, 0
	ldr	w2, [x0, 472]
	bfi	w12, w2, 0, 10
	ldr	w2, [x0, 476]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1656]
	mov	w12, 0
	ldr	w2, [x0, 480]
	bfi	w12, w2, 0, 8
	ldr	w2, [x0, 484]
	bfi	w12, w2, 16, 5
	mov	w2, w12
	str	w2, [x19, 1660]
	mov	w12, 0
	ldr	w2, [x0, 764]
	bfi	w26, w2, 0, 4
	ldr	w2, [x0, 768]
	bfi	w26, w2, 4, 4
	ldr	w2, [x0, 772]
	bfi	w26, w2, 8, 4
	ldr	w2, [x0, 776]
	bfi	w26, w2, 12, 4
	ldr	w2, [x0, 780]
	bfi	w26, w2, 16, 4
	ldr	w2, [x0, 784]
	bfi	w26, w2, 20, 4
	str	w26, [x19, 1664]
	mov	w26, 0
	ldr	w2, [x22, 72]
	bfi	w26, w2, 0, 12
	ldr	w2, [x22, 76]
	bfi	w26, w2, 12, 12
	ldr	w2, [x0, 788]
	bfi	w26, w2, 24, 8
	str	w26, [x19, 1668]
	mov	w26, 0
	ldr	w2, [x0, 792]
	bfi	w26, w2, 0, 12
	ldr	w2, [x0, 796]
	bfi	w26, w2, 12, 12
	ldr	w2, [x0, 800]
	bfi	w26, w2, 24, 8
	str	w26, [x19, 1672]
	mov	w26, 0
	ldr	w2, [x22, 80]
	bfi	w26, w2, 0, 12
	ldr	w2, [x0, 804]
	bfi	w26, w2, 12, 12
	ldr	w2, [x0, 808]
	bfi	w26, w2, 24, 8
	str	w26, [x19, 1676]
	mov	w26, 0
	ldr	w2, [x0, 812]
	bfi	w26, w2, 0, 8
	ldr	w2, [x0, 816]
	bfi	w26, w2, 8, 8
	ldr	w2, [x0, 820]
	bfi	w26, w2, 16, 8
	str	w26, [x19, 1680]
	ldr	w2, [x0, 488]
	bfi	w24, w2, 0, 1
	ldr	w2, [x0, 492]
	bfi	w24, w2, 1, 3
	ldr	w2, [x0, 496]
	bfi	w24, w2, 4, 6
	ldr	w2, [x0, 500]
	bfi	w24, w2, 10, 5
	ldr	w2, [x0, 504]
	bfi	w24, w2, 15, 6
	ldr	w2, [x0, 508]
	bfi	w24, w2, 21, 5
	str	w24, [x19, 1684]
	mov	w24, 0
	ldr	w2, [x0, 512]
	bfi	w27, w2, 0, 1
	ldr	w2, [x0, 516]
	bfi	w27, w2, 1, 3
	ldr	w2, [x0, 520]
	bfi	w27, w2, 4, 6
	ldr	w2, [x0, 524]
	bfi	w27, w2, 10, 5
	ldr	w2, [x0, 528]
	bfi	w27, w2, 15, 6
	ldr	w2, [x0, 532]
	bfi	w27, w2, 21, 5
	str	w27, [x19, 1688]
	ldr	w2, [x0, 536]
	bfi	w28, w2, 0, 1
	ldr	w2, [x0, 540]
	bfi	w28, w2, 1, 3
	ldr	w2, [x0, 544]
	bfi	w28, w2, 4, 6
	ldr	w2, [x0, 548]
	bfi	w28, w2, 10, 5
	ldr	w2, [x0, 552]
	bfi	w28, w2, 15, 6
	ldr	w2, [x0, 556]
	bfi	w28, w2, 21, 5
	str	w28, [x19, 1692]
	ldr	w2, [x0, 560]
	bfi	w30, w2, 0, 1
	ldr	w2, [x0, 564]
	bfi	w30, w2, 1, 3
	ldr	w2, [x0, 568]
	bfi	w30, w2, 4, 6
	ldr	w2, [x0, 572]
	bfi	w30, w2, 10, 5
	ldr	w2, [x0, 576]
	bfi	w30, w2, 15, 6
	ldr	w2, [x0, 580]
	bfi	w30, w2, 21, 5
	str	w30, [x19, 1696]
	ldr	w2, [x0, 584]
	bfi	w12, w2, 0, 1
	ldr	w2, [x0, 588]
	bfi	w12, w2, 1, 3
	ldr	w2, [x0, 592]
	bfi	w12, w2, 4, 6
	ldr	w2, [x0, 596]
	bfi	w12, w2, 10, 5
	ldr	w2, [x0, 600]
	bfi	w12, w2, 15, 6
	ldr	w2, [x0, 604]
	bfi	w12, w2, 21, 5
	str	w12, [x19, 1700]
	mov	w12, 0
	ldr	w2, [x0, 608]
	bfi	w12, w2, 0, 1
	ldr	w2, [x0, 612]
	bfi	w12, w2, 1, 3
	ldr	w2, [x0, 616]
	bfi	w12, w2, 4, 6
	ldr	w2, [x0, 620]
	bfi	w12, w2, 10, 5
	ldr	w2, [x0, 624]
	bfi	w12, w2, 15, 6
	ldr	w2, [x0, 628]
	bfi	w12, w2, 21, 5
	str	w12, [x19, 1704]
	mov	w12, 0
	ldr	w2, [x0, 632]
	bfi	w25, w2, 0, 1
	ldr	w2, [x0, 636]
	bfi	w25, w2, 1, 3
	ldr	w2, [x0, 640]
	bfi	w25, w2, 4, 6
	ldr	w2, [x0, 644]
	bfi	w25, w2, 10, 5
	ldr	w2, [x0, 648]
	bfi	w25, w2, 15, 6
	ldr	w2, [x0, 652]
	bfi	w25, w2, 21, 5
	str	w25, [x19, 1708]
	ldr	w2, [x22, 5720]
	bfi	w24, w2, 20, 8
	ldr	w2, [x21, 44]
	bfi	w24, w2, 28, 1
	stp	w24, w20, [x19, 8]
	mov	w24, 0
	ldr	w2, [x0, 1144]
	bfi	w24, w2, 0, 1
	str	w24, [x19, 1824]
	mov	w24, 0
	ldr	w2, [x0, 1148]
	bfi	w24, w2, 0, 16
	str	w24, [x19, 1828]
	mov	w24, 0
	ldr	w2, [x0, 1152]
	bfi	w24, w2, 0, 16
	str	w24, [x19, 1832]
	mov	w24, 0
	ldr	w2, [x0, 1156]
	bfi	w24, w2, 0, 16
	str	w24, [x19, 1836]
	ldr	w2, [x0, 1160]
	bfi	w12, w2, 18, 9
	ldr	w2, [x0, 1164]
	bfi	w12, w2, 9, 9
	ldr	w2, [x0, 1168]
	bfi	w12, w2, 0, 9
	str	w12, [x19, 1844]
	ldr	w2, [x0, 1172]
	bfi	w9, w2, 16, 8
	ldr	w2, [x0, 1176]
	bfi	w9, w2, 8, 8
	ldr	w2, [x0, 1180]
	bfi	w9, w2, 0, 8
	str	w9, [x19, 1848]
	ldr	w2, [x0, 1184]
	bfi	w7, w2, 8, 4
	ldr	w2, [x0, 1188]
	bfi	w7, w2, 4, 4
	ldr	w2, [x0, 1192]
	bfi	w7, w2, 0, 4
	mov	w2, 3
	bfi	w7, w2, 20, 8
	mov	w2, 20
	bfi	w7, w2, 12, 8
	str	w7, [x19, 1852]
	ldrh	w2, [x0, 1292]
	str	w2, [x19, 1856]
	ldr	w2, [x0, 1308]
	bfi	w6, w2, 0, 8
	ldr	w2, [x0, 1304]
	bfi	w6, w2, 8, 8
	ldr	w2, [x0, 1300]
	bfi	w6, w2, 16, 8
	ldr	w2, [x0, 1296]
	bfi	w6, w2, 24, 8
	str	w6, [x19, 1860]
	ldr	w2, [x0, 1196]
	bfi	w5, w2, 24, 8
	ldr	w2, [x0, 1200]
	bfi	w5, w2, 16, 8
	ldr	w2, [x0, 1204]
	bfi	w5, w2, 8, 8
	ldr	w2, [x0, 1208]
	bfi	w5, w2, 0, 8
	str	w5, [x19, 1872]
	ldr	w2, [x0, 1212]
	bfi	w4, w2, 0, 8
	ldr	w2, [x0, 1216]
	bfi	w4, w2, 8, 8
	ldr	w2, [x0, 1220]
	bfi	w4, w2, 16, 1
	ldr	w2, [x0, 1336]
	bfi	w4, w2, 17, 1
	str	w4, [x19, 1876]
	mov	w4, 0
	ldr	w2, [x0, 1224]
	bfi	w4, w2, 0, 16
	ldr	w2, [x0, 1228]
	bfi	w4, w2, 16, 16
	str	w4, [x19, 1880]
	mov	w4, 0
	ldr	w2, [x22, 488]
	bfi	w8, w2, 22, 9
	ldr	w2, [x22, 492]
	bfi	w8, w2, 17, 5
	ldr	w2, [x22, 496]
	bfi	w8, w2, 9, 8
	ldr	w2, [x22, 516]
	bfi	w8, w2, 0, 9
	str	w8, [x19, 1884]
	ldr	w2, [x22, 512]
	bfi	w4, w2, 8, 14
	ldr	w2, [x0, 1232]
	bfi	w4, w2, 0, 8
	str	w4, [x19, 1792]
	ldr	w2, [x22, 500]
	bfi	w10, w2, 16, 8
	ldr	w2, [x22, 504]
	bfi	w10, w2, 8, 8
	ldr	w2, [x22, 508]
	bfi	w10, w2, 0, 8
	str	w10, [x19, 1796]
	ldr	w2, [x0, 1240]
	bfi	w3, w2, 17, 1
	ldr	w2, [x0, 1244]
	bfi	w3, w2, 12, 2
	ldr	w2, [x0, 1248]
	bfi	w3, w2, 4, 4
	ldr	w2, [x0, 1252]
	bfi	w3, w2, 0, 4
	str	w3, [x19, 1800]
	mov	w3, 0
	ldr	w2, [x0, 1256]
	bfi	w17, w2, 0, 10
	ldr	w2, [x0, 1260]
	bfi	w17, w2, 16, 9
	str	w17, [x19, 1808]
	ldr	w2, [x0, 1264]
	bfi	w18, w2, 0, 10
	ldr	w2, [x0, 1268]
	bfi	w18, w2, 16, 9
	str	w18, [x19, 1812]
	ldr	w2, [x0, 1272]
	bfi	w16, w2, 0, 10
	ldr	w2, [x0, 1276]
	bfi	w16, w2, 16, 9
	str	w16, [x19, 1816]
	ldr	w2, [x0, 1280]
	bfi	w3, w2, 0, 10
	ldr	w2, [x0, 1284]
	bfi	w3, w2, 16, 9
	str	w3, [x19, 1820]
	mov	w3, 0
	ldr	w2, [x0, 1288]
	bfi	w3, w2, 0, 16
	str	w3, [x19, 1804]
	mov	w3, 0
	ldr	w2, [x0, 1312]
	bfi	w15, w2, 0, 13
	ldr	w2, [x0, 1316]
	bfi	w15, w2, 13, 1
	str	w15, [x19, 36]
	ldr	w2, [x0, 1320]
	bfi	w3, w2, 0, 18
	str	w3, [x19, 40]
	mov	w3, 0
	ldr	w2, [x0, 1324]
	bfi	w3, w2, 0, 18
	str	w3, [x19, 44]
	ldr	w2, [x0, 1348]
	bfi	w14, w2, 16, 7
	ldr	w2, [x0, 1352]
	bfi	w14, w2, 23, 7
	str	w14, [x23, 1792]
	ldr	w2, [x0, 1340]
	bfi	w11, w2, 0, 8
	ldr	w2, [x0, 1344]
	bfi	w11, w2, 8, 8
	ldr	w2, [x0, 1328]
	bfi	w11, w2, 16, 8
	str	w11, [x23, 1796]
	ldr	w2, [x0, 1332]
	bfi	w13, w2, 12, 8
	ldr	w2, [x0, 1356]
	ldr	w0, [x0, 1360]
	bfi	w13, w2, 8, 4
	bfi	w13, w0, 0, 8
	mov	w0, 257
	str	w13, [x23, 1800]
	movk	w0, 0xc8, lsl 16
	str	w0, [x23, 1804]
	ldr	w0, [x21, 8]
	cbnz	w0, .L139
	mov	w2, 23
	mov	w3, 15
	bfi	w0, w2, 0, 5
	bfi	w0, w3, 5, 5
	bfi	w0, w2, 10, 5
	bfi	w0, w3, 15, 5
	and	w0, w0, -1048577
	str	w0, [x19, 24]
.L140:
	mov	w5, 16
	mov	w0, 0
	mov	w3, 10
	bfi	w0, w5, 6, 6
	str	wzr, [x19, 552]
	bfi	w0, w3, 0, 6
	mov	w2, 2
	str	w0, [x19, 556]
	str	w2, [x19, 548]
	mov	w4, 64
	ldr	w2, [x21, 556]
	ldr	w0, [x21, 552]
	ubfiz	w2, w2, 8, 6
	ldr	w3, [x1, 3392]
	orr	w2, w2, 64
	bfi	w2, w0, 0, 6
	bfi	w2, w3, 16, 6
	ldr	w3, [x1, 3364]
	bfi	w2, w3, 24, 4
	str	w2, [x23, 3076]
	ldr	w2, [x21, 8]
	ldr	w3, [x21, 20]
	cmp	w2, wzr
	ldr	w2, [x21, 16]
	csel	w4, w4, w5, ne
	sub	w3, w3, #1
	sub	w2, w2, #1
	add	w3, w3, w4
	add	w2, w2, w4
	udiv	w3, w3, w4
	udiv	w2, w2, w4
	mul	w2, w2, w3
	ldr	w3, [x21, 544]
	udiv	w2, w3, w2
	mov	w3, 0
	bfi	w3, w2, 0, 16
	ldr	w2, [x1, 3380]
	bfi	w3, w2, 16, 6
	str	w3, [x23, 3080]
	mov	w2, 0
	ldr	w3, [x22, 100]
	bfi	w2, w3, 0, 6
	ldr	w3, [x1, 3372]
	bfi	w2, w3, 24, 6
	ldr	w3, [x1, 3376]
	bfi	w2, w3, 16, 6
	ldr	w3, [x1, 3384]
	bfi	w2, w3, 8, 6
	str	w2, [x23, 3084]
	mov	w2, 0
	ldr	w3, [x22, 116]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 112]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 108]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 104]
	bfi	w2, w3, 0, 8
	str	w2, [x23, 3088]
	mov	w2, 0
	ldr	w3, [x22, 132]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 128]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 124]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 120]
	bfi	w2, w3, 0, 8
	str	w2, [x23, 3092]
	mov	w2, 0
	ldr	w3, [x22, 148]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 144]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 140]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 136]
	bfi	w2, w3, 0, 8
	str	w2, [x23, 3096]
	mov	w2, 0
	ldr	w3, [x22, 164]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 160]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 156]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 152]
	bfi	w2, w3, 0, 8
	str	w2, [x23, 3072]
	mov	w2, 0
	ldr	w3, [x1, 3408]
	bfi	w2, w3, 0, 4
	ldr	w3, [x1, 3412]
	bfi	w2, w3, 4, 4
	str	w2, [x23, 3100]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x1, 3356]
	bfi	w3, w4, 0, 4
	str	w3, [x23, 3104]
	ldr	w3, [x1, 3352]
	ldr	w0, [x1, 3360]
	bfi	w2, w3, 0, 4
	bfi	w2, w0, 4, 4
	str	w2, [x23, 3108]
	ldr	w0, [x21, 8]
	cbnz	w0, .L142
	mov	w0, 3
	mov	w2, 0
	bfi	w2, w0, 0, 4
.L143:
	add	x0, x1, 2440
	str	w2, [x23, 3112]
	mov	w2, 0
	ldr	w20, [x29, 100]
	ldr	w3, [x0, 844]
	bfi	w2, w3, 0, 2
	ldr	w3, [x0, 848]
	bfi	w2, w3, 2, 2
	ldr	w3, [x0, 852]
	bfi	w2, w3, 4, 2
	ldr	w3, [x0, 856]
	bfi	w2, w3, 6, 2
	ldr	w3, [x0, 860]
	bfi	w2, w3, 8, 2
	ldr	w3, [x0, 864]
	bfi	w2, w3, 10, 2
	ldr	w3, [x0, 868]
	bfi	w2, w3, 12, 2
	ldr	w3, [x0, 872]
	bfi	w2, w3, 14, 2
	ldr	w3, [x0, 876]
	bfi	w2, w3, 16, 2
	ldr	w3, [x0, 880]
	bfi	w2, w3, 18, 2
	ldr	w3, [x0, 884]
	bfi	w2, w3, 20, 2
	ldr	w3, [x0, 888]
	bfi	w2, w3, 22, 2
	ldr	w3, [x0, 892]
	bfi	w2, w3, 24, 2
	ldr	w3, [x0, 896]
	bfi	w2, w3, 26, 2
	ldr	w3, [x0, 900]
	bfi	w2, w3, 28, 2
	ldr	w3, [x0, 904]
	bfi	w2, w3, 30, 2
	str	w2, [x23, 3116]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x0, 908]
	bfi	w2, w4, 0, 5
	str	w2, [x23, 3120]
	ldr	x4, [x29, 104]
	ldr	w2, [x0, 956]
	bfi	w3, w2, 24, 4
	ldr	w2, [x0, 960]
	bfi	w3, w2, 28, 4
	ldr	w2, [x0, 964]
	bfi	w3, w2, 16, 6
	ldr	w2, [x0, 928]
	ldr	w0, [x0, 948]
	bfi	w3, w2, 8, 4
	add	x2, x4, 872
	bfi	w3, w0, 0, 6
	add	x0, x4, 936
	str	w3, [x23, 3124]
	add	x3, x19, 1104
	.p2align 2
.L144:
	ldr	w4, [x2], 4
	bfi	w20, w4, 0, 20
	cmp	x2, x0
	str	w20, [x3], 4
	bne	.L144
	ldr	x3, [x29, 104]
	add	x2, x19, 1280
	add	x4, x3, 1192
	.p2align 2
.L145:
	ldr	w3, [x0], 4
	bfi	w20, w3, 0, 20
	cmp	x4, x0
	str	w20, [x2], 4
	bne	.L145
	add	x0, x19, 512
	str	wzr, [x23, 3660]
	add	x4, x19, 512
	str	wzr, [x19, 564]
	str	wzr, [x19, 568]
	add	x5, x19, 512
	str	wzr, [x19, 572]
	mov	w3, -1
	stp	wzr, wzr, [x0, 68]
	stp	wzr, wzr, [x0, 76]
	mov	w2, 7
	stp	w3, w2, [x4, 84]
	stp	w3, w2, [x4, 92]
	stp	w3, w2, [x5, 100]
	stp	w3, w2, [x5, 108]
	mov	w2, 13
	str	w2, [x19, 576]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x1, 4076]
	bfi	w3, w4, 0, 1
	str	w3, [x19, 120]
	ldr	w3, [x21, 176]
	str	w3, [x19, 96]
	ldr	w3, [x21, 180]
	str	w3, [x19, 100]
	ldr	w3, [x21, 184]
	str	w3, [x19, 104]
	ldr	w3, [x21, 188]
	str	w3, [x19, 108]
	ldr	w3, [x21, 192]
	str	w3, [x19, 112]
	ldr	w3, [x21, 196]
	str	w3, [x19, 116]
	ldr	w3, [x1, 3264]
	bfi	w2, w3, 0, 16
	ldr	w3, [x1, 3268]
	bfi	w2, w3, 16, 16
	str	w2, [x19, 1728]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x1, 3280]
	bfi	w3, w4, 16, 16
	str	w3, [x19, 1732]
	ldr	w3, [x1, 3272]
	ldr	w0, [x1, 3276]
	bfi	w2, w3, 0, 16
	bfi	w2, w0, 16, 16
	str	w2, [x19, 1736]
	ldr	w2, [x21, 8]
	ldr	x0, [x21, 696]
	cmp	w2, 2
	beq	.L188
	ldr	w2, [x21, 604]
	mov	w3, 0
	str	w2, [x0, 256]
	ldr	w2, [x21, 608]
	str	w2, [x0, 260]
	ldr	w2, [x21, 612]
	str	w2, [x0, 264]
	ldr	w2, [x21, 616]
	str	w2, [x0, 268]
	ldr	w2, [x21, 620]
	str	w2, [x0, 272]
	ldr	w2, [x21, 624]
	str	w2, [x0, 276]
	ldr	w2, [x21, 628]
	str	w2, [x0, 280]
	ldr	w2, [x21, 632]
	str	w2, [x0, 284]
	ldr	w5, [x21, 636]
	str	wzr, [x0, 292]
	sub	w4, w5, #1
	lsr	w2, w5, 16
	bfi	w3, w4, 16, 7
	lsr	w4, w5, 8
	sub	w4, w4, #1
	sub	w2, w2, #1
	bfi	w3, w4, 8, 6
	bfi	w3, w2, 0, 6
	str	w3, [x0, 288]
.L154:
	ldr	w2, [x21, 8]
	cmp	w2, 2
	beq	.L189
	ldr	w2, [x22, 5756]
	mov	w3, 0
	str	w2, [x0, 296]
	ldr	w2, [x22, 5760]
	str	w2, [x0, 300]
	ldr	w2, [x22, 5764]
	str	w2, [x0, 304]
	ldr	w2, [x22, 5768]
	str	w2, [x0, 308]
	ldr	w2, [x22, 5772]
	str	w2, [x0, 312]
	ldr	w2, [x22, 5776]
	str	w2, [x0, 316]
	ldr	w2, [x22, 5780]
	str	w2, [x0, 320]
	ldr	w2, [x22, 5784]
	str	w2, [x0, 324]
	ldr	w6, [x22, 5752]
	sub	w5, w6, #1
	lsr	w4, w6, 8
	bfi	w3, w5, 16, 7
	sub	w4, w4, #1
	lsr	w2, w6, 16
	bfi	w3, w4, 8, 6
	sub	w2, w2, #1
	bfi	w3, w2, 0, 6
	str	w3, [x0, 328]
.L161:
	ldr	w2, [x21, 268]
	mov	w0, 0
	str	w2, [x19, 68]
	mov	w3, 0
	str	w0, [x23, 9232]
	mov	w2, -85
	add	x0, x1, 2440
	bfi	w3, w2, 0, 8
	ldr	w4, [x1, 4184]
	mov	w2, 85
	str	w4, [x23, 9236]
	bfi	w3, w2, 8, 8
	mov	w4, 0
	mov	w2, 0
	ldr	w5, [x21, 540]
	cmp	w5, wzr
	cset	w5, ne
	str	w5, [x19, 76]
	ldr	w5, [x21, 680]
	stp	w5, wzr, [x19, 80]
	str	w3, [x19, 28]
	mov	w3, 0
	stp	wzr, wzr, [x19, 88]
	mov	w5, 0
	ldr	w6, [x0, 976]
	bfi	w4, w6, 0, 6
	ldr	w6, [x0, 980]
	bfi	w4, w6, 8, 2
	ldr	w6, [x0, 984]
	bfi	w4, w6, 10, 1
	ldr	w6, [x0, 988]
	bfi	w4, w6, 12, 4
	ldr	w6, [x0, 992]
	bfi	w4, w6, 16, 5
	str	w4, [x23, 12240]
	mov	w4, 0
	ldr	w6, [x0, 1036]
	str	w6, [x23, 12244]
	ldr	w6, [x0, 1040]
	str	w6, [x23, 12248]
	ldr	w6, [x0, 1044]
	bfi	w2, w6, 0, 16
	ldr	w6, [x0, 1048]
	bfi	w2, w6, 16, 2
	ldr	w6, [x0, 1052]
	bfi	w2, w6, 18, 2
	ldr	w6, [x0, 1056]
	bfi	w2, w6, 20, 4
	ldr	w6, [x0, 1060]
	bfi	w2, w6, 24, 1
	ldr	w6, [x0, 1068]
	bfi	w2, w6, 25, 2
	ldr	w6, [x0, 1072]
	bfi	w2, w6, 27, 1
	ldr	w6, [x0, 1064]
	bfi	w2, w6, 28, 1
	str	w2, [x23, 12252]
	ldr	w6, [x0, 1104]
	ldr	w2, [x0, 1100]
	bfi	w3, w6, 0, 1
	ldr	w6, [x0, 1096]
	bfi	w3, w2, 2, 2
	ldr	w2, [x0, 1092]
	bfi	w3, w6, 4, 2
	ldr	w6, [x0, 1112]
	bfi	w3, w2, 6, 1
	ldr	w2, [x0, 1116]
	bfi	w3, w6, 8, 6
	bfi	w3, w2, 24, 6
	str	w3, [x23, 12256]
	ldr	w6, [x0, 1120]
	ldr	w2, [x0, 1124]
	ldr	w3, [x0, 1128]
	bfi	w5, w6, 0, 6
	bfi	w5, w2, 8, 6
	ldr	w2, [x0, 1132]
	bfi	w5, w3, 16, 6
	bfi	w5, w2, 24, 6
	str	w5, [x23, 12260]
	ldr	w3, [x0, 1136]
	ldr	w2, [x21, 8]
	ldr	w0, [x0, 1140]
	bfi	w4, w3, 0, 6
	bfi	w4, w0, 6, 25
	cbz	w2, .L190
	ldr	w2, [x21, 20]
	ldr	w0, [x21, 544]
	lsr	w3, w2, 6
	udiv	w0, w0, w3
	bfi	w4, w0, 6, 25
.L165:
	str	w4, [x23, 12264]
	mov	w0, 0
	ldr	x3, .LC12
	mov	w2, 0
	ldr	w7, [x21, 576]
	add	x6, x1, 2440
	ldr	w4, [x21, 572]
	ldr	w5, [x21, 568]
	bfi	w0, w7, 10, 1
	bfi	w0, w4, 9, 1
	ldr	w4, [x1, 4120]
	ldr	w7, [x1, 4124]
	bfi	w0, w5, 8, 1
	bfi	w0, w4, 7, 1
	ldr	w4, [x1, 4100]
	ldr	w5, [x1, 4096]
	bfi	w0, w7, 6, 1
	bfi	w0, w4, 5, 1
	ldr	w4, [x1, 4128]
	ldr	w7, [x1, 4132]
	bfi	w0, w5, 4, 1
	bfi	w0, w4, 3, 1
	ldr	w5, [x1, 4136]
	ldr	w4, [x1, 4140]
	bfi	w0, w7, 2, 1
	bfi	w0, w5, 1, 1
	ldr	x3, [x3]
	bfi	w0, w4, 0, 1
	str	w0, [x23, 504]
	add	x0, x3, 61440
	add	x5, x23, 61440
	ldr	w8, [x1, 4104]
	mov	w4, 0
	ldr	w3, [x1, 4144]
	mov	w7, 3
	bfi	w2, w8, 7, 1
	ldr	w8, [x1, 4164]
	bfi	w2, w3, 6, 1
	ldr	w3, [x1, 4148]
	bfi	w2, w3, 5, 1
	ldr	w3, [x1, 4152]
	bfi	w2, w3, 4, 1
	ldr	w3, [x1, 4156]
	bfi	w2, w3, 3, 1
	ldr	w3, [x1, 4160]
	bfi	w2, w3, 2, 1
	ldr	w3, [x1, 4168]
	bfi	w2, w8, 1, 1
	mov	w1, 1
	bfi	w2, w3, 0, 1
	str	w2, [x23, 508]
	ldr	w3, [x6, 1648]
	ldr	w2, [x6, 1652]
	bfi	w4, w3, 0, 1
	bfi	w4, w2, 3, 1
	bfi	w4, w7, 16, 4
	str	w4, [x5]
	str	wzr, [x5, 32]
	ldr	w2, [x21, 580]
	str	w2, [x0, 520]
	ldr	w2, [x21, 580]
	str	w2, [x0, 524]
	ldr	w2, [x21, 588]
	str	w2, [x0, 752]
	ldr	w2, [x21, 584]
	str	w2, [x0, 756]
	ldr	w2, [x21, 588]
	str	w2, [x0, 772]
	ldr	w2, [x21, 584]
	str	w2, [x0, 776]
	mov	w0, 0
	str	wzr, [x5, 8]
	str	wzr, [x23, 16]
	str	w1, [x23, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L187:
	mov	w0, 15
	mov	w24, 0
	bfi	w24, w0, 16, 6
	mov	w0, 31
	bfi	w24, w0, 0, 7
	b	.L134
.L171:
	mov	w3, 6
.L135:
	bfi	w2, w3, 6, 4
	and	w2, w2, -16385
.L136:
	ldrb	w3, [x21, 68]
	b	.L137
.L142:
	ldr	w0, [x22, 84]
	mov	w2, 0
	bfi	w2, w0, 0, 4
	b	.L143
.L139:
	mov	w2, 15
	mov	w0, 0
	bfi	w0, w2, 0, 5
	bfi	w0, w2, 5, 5
	bfi	w0, w2, 10, 5
	bfi	w0, w2, 15, 5
	and	w0, w0, -1048577
	str	w0, [x19, 24]
	b	.L140
.L190:
	ldr	w2, [x21, 20]
	ldr	w0, [x21, 544]
	lsr	w3, w2, 4
	udiv	w0, w0, w3
	bfi	w4, w0, 6, 25
	b	.L165
.L184:
	ldr	w0, [x21, 16]
	cmp	w0, 1919
	bhi	.L191
	cmp	w0, 719
	bhi	.L192
	ldr	x1, [x29, 104]
	mov	w0, 1
	str	w0, [x1, 6424]
	b	.L120
.L185:
	ldr	w1, [x21, 12]
	mov	w0, 5
	mov	w2, 7
	cmp	w1, wzr
	cset	w3, eq
	cmp	w1, 3
	csel	w0, w0, w2, ne
	str	w3, [x22, 5732]
	str	w0, [x22, 5724]
	cset	w3, ne
	str	w3, [x22, 5728]
	ldr	w0, [x21, 16]
	ldr	w1, [x21, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	bne	.L193
.L126:
	ldr	x4, [x29, 104]
	mov	w2, 28
	str	w2, [x21, 548]
	add	x1, x4, 4096
	str	w2, [x21, 552]
	str	w2, [x21, 556]
	add	x0, x1, 3804
	str	wzr, [x4, 804]
	add	x2, x1, 3832
	str	wzr, [x21, 24]
	ldr	w20, [x29, 100]
	str	wzr, [x1, 3472]
	str	wzr, [x1, 3764]
	.p2align 2
.L129:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 220]
	cmp	x2, x0
	bne	.L129
	str	w20, [x29, 100]
	b	.L130
.L189:
	ldr	w2, [x22, 5828]
	cmp	w2, 31
	bhi	.L156
	ldr	w3, [x22, 5788]
	mov	w4, 32
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 308]
.L157:
	ldr	w2, [x22, 5828]
	cmp	w2, 63
	bhi	.L158
	ldr	w3, [x22, 5792]
	mov	w4, 64
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 312]
.L159:
	ldr	w2, [x22, 5828]
	cmp	w2, 64
	bls	.L160
	ldr	w3, [x22, 5796]
	mov	w4, 96
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 316]
.L160:
	ldr	w2, [x22, 5800]
	str	w2, [x0, 320]
	ldr	w2, [x22, 5804]
	str	w2, [x0, 324]
	ldr	w2, [x22, 5808]
	str	w2, [x0, 328]
	ldr	w2, [x22, 5812]
	str	w2, [x0, 332]
	ldr	w2, [x22, 5816]
	str	w2, [x0, 336]
	b	.L161
.L188:
	ldr	w2, [x21, 540]
	mov	w5, 9729
	mov	w3, 513
	cmp	w2, wzr
	ldr	x2, [x29, 104]
	csel	w3, w3, w5, eq
	ldr	w4, [x2, 8168]
	mov	w2, 0
	bfi	w2, w4, 8, 3
	mov	w4, 0
	bfi	w2, w3, 16, 16
	str	w2, [x0, 256]
	mov	w3, 0
	mov	w2, 16
	ldr	w5, [x21, 636]
	bfi	w4, w5, 0, 5
	ldr	w5, [x21, 640]
	bfi	w4, w5, 16, 16
	str	w4, [x0, 260]
	mov	w5, 0
	ldr	w4, [x22, 5824]
	bfi	w3, w4, 0, 5
	ldr	w4, [x22, 5828]
	bfi	w3, w4, 16, 16
	str	w3, [x0, 300]
	ldr	w3, [x21, 636]
	sub	w4, w2, w3
	ldr	w3, [x21, 676]
	lsl	w3, w3, w4
	mov	w4, 0
	bfi	w5, w3, 0, 16
	str	w5, [x0, 264]
	ldr	w3, [x22, 5824]
	sub	w2, w2, w3
	ldr	w3, [x22, 5820]
	lsl	w2, w3, w2
	bfi	w4, w2, 0, 16
	str	w4, [x0, 304]
	ldr	w2, [x21, 640]
	cmp	w2, 31
	bhi	.L149
	ldr	w3, [x21, 644]
	mov	w4, 32
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 268]
.L150:
	ldr	w2, [x21, 640]
	cmp	w2, 63
	bhi	.L151
	ldr	w3, [x21, 648]
	mov	w4, 64
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 272]
.L152:
	ldr	w2, [x21, 640]
	cmp	w2, 64
	bls	.L153
	ldr	w3, [x21, 652]
	mov	w4, 96
	sub	w2, w4, w2
	lsl	w2, w3, w2
	str	w2, [x0, 276]
.L153:
	ldr	w2, [x21, 656]
	str	w2, [x0, 280]
	ldr	w2, [x21, 660]
	str	w2, [x0, 284]
	ldr	w2, [x21, 664]
	str	w2, [x0, 288]
	ldr	w2, [x21, 668]
	str	w2, [x0, 292]
	ldr	w2, [x21, 672]
	str	w2, [x0, 296]
	b	.L154
.L186:
	ldp	w0, w2, [x21, 16]
	mov	w3, 32
	lsr	w4, w2, 2
	lsr	w5, w0, 2
	sub	w2, w4, #16
	sub	w0, w5, #16
	lsr	w4, w2, 1
	lsr	w5, w0, 1
	cmp	w4, w3
	csel	w4, w4, w3, ls
	cmp	w5, 72
	and	w2, w4, 2147483644
	mov	w4, 72
	csel	w5, w5, w4, ls
	cmp	w2, 7
	and	w0, w5, 2147483644
	mov	w4, 7
	bls	.L132
	cmp	w2, w3
	csel	w2, w2, w3, ls
	sub	w2, w2, #1
	and	w4, w2, 63
.L132:
	cmp	w0, 7
	mov	w3, 7
	bls	.L133
	mov	w2, 72
	cmp	w0, w2
	csel	w0, w0, w2, ls
	sub	w0, w0, #1
	and	w3, w0, 127
.L133:
	mov	w24, 0
	bfi	w24, w4, 16, 6
	bfi	w24, w3, 0, 7
	b	.L134
.L151:
	ldr	w2, [x21, 648]
	str	w2, [x0, 272]
	b	.L152
.L149:
	ldr	w2, [x21, 644]
	str	w2, [x0, 268]
	b	.L150
.L158:
	ldr	w2, [x22, 5792]
	str	w2, [x0, 312]
	b	.L159
.L156:
	ldr	w2, [x22, 5788]
	str	w2, [x0, 308]
	b	.L157
.L192:
	ldr	x1, [x29, 104]
	mov	w0, 2
	str	w0, [x1, 6424]
	b	.L120
.L191:
	ldr	x1, [x29, 104]
	mov	w0, 3
	str	w0, [x1, 6424]
	b	.L120
	.size	DRV_VENC_HAL_V400R004C02_CfgReg, .-DRV_VENC_HAL_V400R004C02_CfgReg
	.align	3
.LC12:
	.xword	.LANCHOR1
	.align	3
.LC13:
	.xword	venc_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_Init
	.type	DRV_VENC_HAL_V400R004C02_Init, %function
DRV_VENC_HAL_V400R004C02_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC14
	mov	x1, 63232
	mov	x0, 4173856768
	ldr	x2, [x21, 24]
	blr	x2
	ldr	x20, .LC15
	str	x0, [x20]
	cbz	x0, .L210
	ldr	x1, [x21, 40]
	mov	w0, 8288
	blr	x1
	str	x0, [x20, 8]
	ldr	x3, [x21]
	mov	x2, 8288
	mov	w1, 0
	blr	x3
	ldr	x19, [x20, 8]
	cbz	x19, .L209
	ldr	x3, [x21]
	mov	x2, 704
	mov	w1, 0
	mov	x0, x19
	blr	x3
	str	wzr, [x19, 68]
	mov	w1, 3
	mov	w0, 1
	ldr	x5, [x20]
	mov	w4, 1280
	mov	w3, 720
	mov	w2, 10240
	stp	wzr, w1, [x19, 8]
	stp	wzr, w0, [x19, 40]
	stp	w1, wzr, [x19, 48]
	stp	w0, wzr, [x19, 60]
	str	x5, [x19]
	add	x0, x19, 268
	stp	w4, w3, [x19, 16]
	stp	wzr, wzr, [x19, 24]
	stp	w2, wzr, [x19, 32]
	str	wzr, [x19, 140]
	add	x1, x19, 332
	stp	wzr, wzr, [x19, 172]
	stp	wzr, wzr, [x19, 180]
	stp	wzr, wzr, [x19, 188]
	str	wzr, [x19, 196]
	.p2align 2
.L197:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L197
	add	x16, x19, 512
	add	x17, x19, 512
	mov	w1, 16
	mov	w2, 28
	mov	w0, 48
	add	x3, x19, 4096
	stp	w2, w1, [x16, 36]
	stp	wzr, wzr, [x16, 28]
	stp	w0, wzr, [x17, 44]
	stp	wzr, wzr, [x17, 52]
	mov	w6, 1
	mov	w5, 26
	mov	w4, 7
	str	wzr, [x19, 572]
	str	wzr, [x19, 576]
	add	x0, x3, 3804
	str	wzr, [x19, 636]
	mov	w1, 0
	str	wzr, [x19, 640]
	.p2align 2
.L198:
	str	w1, [x0, 160]
	mov	w2, 1
	str	w1, [x0, 192]
	add	w1, w1, 5
	str	wzr, [x0]
	cmp	w1, 40
	str	w6, [x0, 32]
	add	x0, x0, 4
	str	w5, [x0, 60]
	str	w4, [x0, 92]
	str	w4, [x0, 124]
	str	wzr, [x0, 220]
	bne	.L198
	add	x0, x3, 2440
	str	w2, [x0, 4]
	str	w2, [x19, 6536]
	mov	w4, 8
	mov	w1, 32
	mov	w5, 128
	stp	w4, w1, [x0, 32]
	stp	w4, w1, [x0, 40]
	add	x30, x0, 256
	mov	w4, 6
	mov	w6, 4
	mov	w7, 256
	stp	w5, w6, [x0, 16]
	stp	w6, w7, [x0, 8]
	str	w5, [x0, 24]
	mov	w5, 3
	str	w1, [x0, 448]
	add	x6, x0, 512
	str	w5, [x0, 28]
	add	x5, x0, 512
	str	w4, [x0, 452]
	add	x4, x0, 512
	stp	wzr, wzr, [x0, 48]
	stp	wzr, wzr, [x0, 56]
	stp	wzr, wzr, [x0, 76]
	stp	wzr, wzr, [x0, 84]
	stp	wzr, wzr, [x0, 104]
	stp	wzr, wzr, [x0, 112]
	stp	wzr, wzr, [x0, 132]
	str	wzr, [x0, 140]
	add	x7, x0, 512
	stp	wzr, wzr, [x0, 160]
	str	wzr, [x0, 168]
	add	x8, x0, 512
	stp	wzr, wzr, [x0, 188]
	str	wzr, [x0, 196]
	add	x9, x0, 512
	stp	wzr, wzr, [x0, 216]
	str	wzr, [x0, 224]
	add	x10, x0, 512
	stp	wzr, wzr, [x0, 244]
	stp	wzr, wzr, [x0, 252]
	stp	wzr, wzr, [x30, 20]
	stp	wzr, wzr, [x30, 28]
	stp	w2, wzr, [x4, 144]
	stp	wzr, wzr, [x4, 152]
	stp	wzr, wzr, [x5, 160]
	stp	wzr, w2, [x5, 168]
	stp	wzr, wzr, [x6, 176]
	stp	wzr, wzr, [x6, 184]
	stp	wzr, wzr, [x7, 192]
	stp	wzr, wzr, [x7, 200]
	add	x11, x0, 768
	add	x12, x0, 768
	stp	wzr, wzr, [x8, 208]
	stp	wzr, wzr, [x8, 216]
	stp	w2, wzr, [x9, 224]
	stp	wzr, wzr, [x9, 232]
	stp	wzr, wzr, [x10, 240]
	stp	wzr, wzr, [x10, 248]
	add	x13, x0, 768
	add	x14, x0, 768
	stp	wzr, wzr, [x11]
	stp	wzr, wzr, [x11, 8]
	stp	wzr, wzr, [x12, 16]
	stp	wzr, wzr, [x12, 24]
	stp	wzr, wzr, [x13, 32]
	stp	wzr, wzr, [x13, 40]
	add	x15, x0, 256
	add	x1, x3, 3284
	stp	wzr, wzr, [x14, 48]
	stp	wzr, wzr, [x14, 56]
	str	wzr, [x0, 832]
	add	x4, x3, 3348
	stp	wzr, wzr, [x15, 64]
	stp	wzr, wzr, [x15, 72]
	str	wzr, [x0, 316]
	str	wzr, [x0, 312]
	str	w2, [x0, 308]
	str	wzr, [x0, 836]
	str	wzr, [x0, 840]
	.p2align 2
.L199:
	str	w2, [x1], 4
	mov	w0, 1
	cmp	x1, x4
	bne	.L199
	add	x2, x3, 3284
	mov	w5, 48
	add	x1, x3, 3584
	mov	w4, 4
	mov	w6, 8
	mov	w7, 10
	stp	wzr, w5, [x2, 84]
	stp	w5, w5, [x2, 92]
	mov	w5, 35
	str	w5, [x2, 100]
	mov	w5, 51
	str	w4, [x2, 212]
	stp	w4, w6, [x2, 112]
	stp	w6, wzr, [x2, 64]
	stp	w0, w4, [x2, 140]
	str	w7, [x2, 268]
	mov	w12, 5
	str	w7, [x2, 272]
	mov	w9, 2
	str	w7, [x2, 280]
	mov	w8, 44
	str	w7, [x2, 284]
	mov	w14, 50
	str	w5, [x2, 104]
	mov	w11, 20
	str	w5, [x2, 120]
	mov	w5, 12
	stp	wzr, wzr, [x2, 72]
	stp	w5, w5, [x2, 124]
	str	w12, [x2, 132]
	mov	w10, 3
	stp	w0, w0, [x2, 164]
	str	w0, [x2, 172]
	mov	w13, 24
	stp	w0, wzr, [x2, 184]
	stp	wzr, wzr, [x2, 232]
	stp	wzr, wzr, [x2, 240]
	str	wzr, [x2, 136]
	str	w8, [x2, 108]
	mov	w8, 16
	str	w7, [x2, 288]
	str	w9, [x2, 80]
	add	x2, x3, 2440
	str	wzr, [x19, 7680]
	stp	w11, w14, [x1, 4]
	mov	w14, 150
	str	w14, [x1, 12]
	mov	w14, 6
	str	w14, [x1, 48]
	mov	w14, 131
	str	w14, [x1, 52]
	mov	w14, 160
	str	w14, [x1, 56]
	mov	w14, 100
	str	w14, [x1, 60]
	stp	w5, w6, [x1, 16]
	stp	w4, w5, [x1, 24]
	stp	w6, w4, [x1, 32]
	stp	w6, w8, [x1, 124]
	stp	w9, w4, [x1, 40]
	stp	wzr, w6, [x1, 108]
	stp	w6, w6, [x1, 116]
	stp	w8, w13, [x1, 132]
	stp	w10, wzr, [x1, 88]
	stp	wzr, w9, [x1, 100]
	mov	w14, 127
	str	w14, [x1, 64]
	stp	w13, wzr, [x1, 140]
	add	x5, x19, 8192
	str	w7, [x1, 68]
	mov	w7, 60
	str	w7, [x1, 184]
	stp	w11, w0, [x1, 72]
	stp	wzr, wzr, [x1, 168]
	stp	wzr, wzr, [x1, 176]
	stp	wzr, wzr, [x1, 188]
	stp	wzr, w12, [x1, 196]
	stp	wzr, wzr, [x1, 204]
	stp	wzr, wzr, [x1, 212]
	mov	w7, 767
	str	w7, [x1, 80]
	mov	x1, x5
	add	x5, x19, 704
	mov	w7, 7
	stp	w0, w0, [x1, -36]
	stp	w0, w9, [x1, -28]
	str	w0, [x1, -20]
	mov	x1, x2
	add	x11, x1, 1536
	mov	w2, 15
	stp	wzr, w0, [x11, 112]
	stp	w2, w2, [x11, 104]
	str	wzr, [x3, 4100]
	add	x2, x19, 1192
	str	wzr, [x3, 4108]
	str	wzr, [x3, 4112]
	str	wzr, [x3, 4116]
	str	wzr, [x1, 1656]
	mov	w1, 11520
	movk	w1, 0x131, lsl 16
	str	wzr, [x3, 4104]
	str	w1, [x3, 4180]
	mov	w1, 2304
	str	wzr, [x3, 4120]
	movk	w1, 0x3d, lsl 16
	str	wzr, [x3, 4124]
	str	w1, [x3, 4184]
	mov	w1, 64
	str	wzr, [x3, 4128]
	str	wzr, [x3, 4132]
	str	wzr, [x3, 4136]
	str	wzr, [x3, 4140]
	str	wzr, [x3, 4144]
	str	wzr, [x3, 4148]
	str	wzr, [x3, 4152]
	str	wzr, [x3, 4156]
	str	wzr, [x3, 4160]
	str	wzr, [x3, 4164]
	str	wzr, [x3, 4168]
	str	w9, [x3, 4172]
	str	w0, [x3, 4176]
	str	w0, [x5, 4]
	str	w0, [x19, 704]
	stp	w10, w1, [x5, 8]
	add	x1, x19, 788
	stp	w4, w8, [x5, 16]
	stp	w4, w8, [x5, 24]
	stp	w8, w4, [x5, 60]
	stp	wzr, wzr, [x5, 44]
	stp	wzr, wzr, [x5, 52]
	stp	w0, wzr, [x5, 68]
	mov	w8, 9
	stp	wzr, wzr, [x5, 76]
	stp	w7, w8, [x1, 48]
	mov	w8, 11
	str	w8, [x1, 56]
	stp	w7, w7, [x1, 40]
	mov	w8, 14
	mov	w7, 255
	stp	w4, wzr, [x1, 16]
	stp	wzr, wzr, [x1, 24]
	stp	w7, w7, [x1, 72]
	str	w7, [x1, 80]
	mov	w7, 25
	str	w8, [x1, 60]
	mov	w8, 18
	stp	wzr, wzr, [x1, 32]
	str	w7, [x1, 68]
	str	w8, [x1, 64]
	str	w4, [x19, 788]
	mov	w4, 96
	stp	w0, w0, [x1, 4]
	mov	x1, x2
	mov	w2, 378
	str	w4, [x1, 28]
	str	w0, [x19, 1192]
	ldr	x4, .LC16
	str	w2, [x1, 24]
	mov	w2, 128
	stp	w10, w6, [x1, 16]
	str	w2, [x1, 12]
	add	x6, x4, 320
	stp	w10, w7, [x1, 4]
	add	x2, x19, 872
	add	x1, x4, 164
	b	.L202
	.p2align 3
.L200:
	ldr	w0, [x1], 4
.L202:
	str	w0, [x2], 4
	cmp	x1, x6
	bne	.L200
	add	x0, x4, 324
	add	x1, x19, 1032
	add	x4, x4, 480
	mov	w2, 1
	b	.L201
	.p2align 3
.L216:
	ldr	w2, [x0], 4
.L201:
	str	w2, [x1], 4
	cmp	x0, x4
	bne	.L216
	add	x19, x19, 1224
	mov	w0, 7
	add	x22, x3, 2328
	mov	x25, x19
	mov	w24, 3
	mov	w26, 96
	mov	w20, 4
	mov	w23, 64
	str	w0, [x5, 5724]
	str	wzr, [x5, 5728]
	str	wzr, [x5, 5732]
.L205:
	ldr	x3, [x21]
	mov	x2, 2600
	mov	w1, 0
	mov	x0, x25
	blr	x3
	mov	x2, x25
	mov	x1, x25
	mov	x0, x25
	mov	w4, 5
	mov	w3, 1
	mov	w10, 20
	mov	w9, 8
	mov	w5, 32
	mov	w8, 384
	mov	w7, 2
	mov	w6, 16
	.p2align 2
.L204:
	str	w24, [x0, 8]
	add	x1, x1, 32
	str	w26, [x1, 2436]
	add	x0, x0, 84
	add	x30, x1, 2304
	str	w20, [x2, 420]
	add	x2, x2, 404
	subs	w4, w4, #1
	str	w3, [x0, -80]
	str	w23, [x0, -72]
	str	wzr, [x0, -40]
	str	wzr, [x0, -12]
	stp	w24, w10, [x30, 108]
	stp	w23, w20, [x30, 116]
	str	w9, [x1, 2428]
	stp	w20, w5, [x0, -60]
	str	wzr, [x0, -28]
	str	wzr, [x0, -8]
	stp	w3, wzr, [x2, 24]
	str	w8, [x1, 2432]
	str	w3, [x0, -84]
	str	wzr, [x0, -52]
	stp	w5, w20, [x0, -24]
	str	wzr, [x0, -4]
	str	w7, [x1, 2408]
	stp	w20, w6, [x0, -68]
	str	w3, [x0, -16]
	str	w3, [x2, 20]
	bne	.L204
	add	x25, x25, 2600
	cmp	x25, x22
	bne	.L205
	mov	w6, 1
	mov	w7, 0
	mov	w2, w6
	mov	w5, 128
	mov	w0, 64
	mov	w14, 6
	mov	w13, 5
	mov	w3, 32
	mov	w4, 2
	mov	w12, 15
	mov	w8, 4
	mov	w1, 3
	mov	w11, 256
	mov	w10, 34
	mov	w9, 16
.L206:
	add	x20, x19, 2560
	str	w5, [x19, 28]
	stp	wzr, wzr, [x19]
	stp	w2, w5, [x19, 8]
	str	w5, [x19, 60]
	cmp	w6, 1
	str	w0, [x19, 96]
	str	w0, [x19, 112]
	str	w0, [x19, 144]
	str	w0, [x19, 180]
	str	w0, [x19, 196]
	str	w0, [x19, 228]
	str	w2, [x19, 380]
	str	wzr, [x19, 384]
	str	wzr, [x19, 388]
	str	w3, [x19, 408]
	str	wzr, [x19, 424]
	str	wzr, [x19, 428]
	str	w14, [x19, 824]
	str	wzr, [x19, 832]
	str	w13, [x19, 1228]
	stp	w4, w12, [x20, 12]
	stp	w0, w4, [x20, 20]
	str	w8, [x19, 2588]
	cbz	w7, .L217
	add	x15, x19, 256
	str	w2, [x19, 336]
	add	x16, x19, 256
	stp	w8, w9, [x15, 96]
	stp	w1, w3, [x15, 104]
	str	w1, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w1, w3, [x16, 136]
	stp	w1, w2, [x16, 144]
	str	wzr, [x19, 412]
	str	w10, [x19, 416]
	str	w2, [x19, 2048]
	str	w4, [x19, 2568]
	str	w11, [x19, 2592]
	bhi	.L209
.L208:
	add	w7, w7, 1
	add	x19, x19, 2600
	add	w6, w6, 1
	b	.L206
	.p2align 3
.L209:
	mov	w0, 0
.L195:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L210:
	mov	w0, -1
	b	.L195
.L217:
	add	x17, x19, 256
	str	w2, [x19, 336]
	add	x18, x19, 256
	stp	w8, w9, [x17, 96]
	stp	w1, w3, [x17, 104]
	str	w8, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w8, w3, [x18, 136]
	stp	w1, w2, [x18, 144]
	str	wzr, [x19, 412]
	str	w10, [x19, 416]
	str	w2, [x19, 2048]
	str	w4, [x19, 2568]
	str	w11, [x19, 2592]
	b	.L208
	.size	DRV_VENC_HAL_V400R004C02_Init, .-DRV_VENC_HAL_V400R004C02_Init
	.align	3
.LC14:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC15:
	.xword	.LANCHOR1
	.align	3
.LC16:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_Deinit
	.type	DRV_VENC_HAL_V400R004C02_Deinit, %function
DRV_VENC_HAL_V400R004C02_Deinit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC19
	ldr	x19, .LC20
	ldr	x1, [x20, 32]
	ldr	x0, [x19]
	blr	x1
	ldr	x0, [x19, 8]
	ldr	x1, [x20, 48]
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_Deinit, .-DRV_VENC_HAL_V400R004C02_Deinit
	.align	3
.LC19:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC20:
	.xword	.LANCHOR1
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 160
g_h265LambdaSsd:
	.word	18
	.word	22
	.word	28
	.word	36
	.word	45
	.word	57
	.word	72
	.word	91
	.word	115
	.word	145
	.word	183
	.word	231
	.word	291
	.word	367
	.word	463
	.word	583
	.word	735
	.word	926
	.word	1167
	.word	1470
	.word	1853
	.word	2334
	.word	2941
	.word	3706
	.word	4669
	.word	5883
	.word	7412
	.word	9338
	.word	11766
	.word	14824
	.word	18677
	.word	23532
	.word	29649
	.word	37355
	.word	47065
	.word	59298
	.word	74711
	.word	94130
	.word	118596
	.word	131071
	.type	g_h264LambdaSsd, %object
	.size	g_h264LambdaSsd, 160
g_h264LambdaSsd:
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	4
	.word	5
	.word	7
	.word	9
	.word	11
	.word	14
	.word	17
	.word	22
	.word	27
	.word	34
	.word	43
	.word	54
	.word	69
	.word	86
	.word	109
	.word	137
	.word	173
	.word	218
	.word	274
	.word	345
	.word	435
	.word	548
	.word	691
	.word	870
	.word	1097
	.word	1382
	.word	1741
	.word	2193
	.word	2763
	.word	3482
	.word	4095
	.word	4095
	.word	4095
	.type	g_h264LambdaSad, %object
	.size	g_h264LambdaSad, 160
g_h264LambdaSad:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	4
	.word	4
	.word	4
	.word	5
	.word	6
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	13
	.word	14
	.word	16
	.word	18
	.word	20
	.word	23
	.word	25
	.word	29
	.word	32
	.word	36
	.word	40
	.word	45
	.word	51
	.word	57
	.word	64
	.word	72
	.word	81
	.word	91
	.type	g_h265LambdaSad, %object
	.size	g_h265LambdaSad, 160
g_h265LambdaSad:
	.word	193
	.word	216
	.word	243
	.word	273
	.word	306
	.word	344
	.word	386
	.word	433
	.word	487
	.word	546
	.word	613
	.word	688
	.word	773
	.word	867
	.word	974
	.word	1093
	.word	1227
	.word	1377
	.word	1546
	.word	1735
	.word	1948
	.word	2186
	.word	2454
	.word	2755
	.word	3092
	.word	3471
	.word	3896
	.word	4373
	.word	4908
	.word	5510
	.word	6184
	.word	6942
	.word	7792
	.word	8746
	.word	9817
	.word	11020
	.word	12369
	.word	13884
	.word	15584
	.word	17493
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	g_pRegBase, %object
	.size	g_pRegBase, 8
g_pRegBase:
	.zero	8
	.type	g_pHalRegInfo, %object
	.size	g_pHalRegInfo, 8
g_pHalRegInfo:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
