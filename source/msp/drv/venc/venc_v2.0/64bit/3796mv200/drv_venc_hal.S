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
	mov	w19, w1
	mov	w22, w2
	bl	_mcount
	mov	x21, 0
	cmp	w19, 25
	bls	.L2
	sub	w0, w19, #26
	mov	x21, 1
	cmp	w0, 3
	bls	.L2
	sub	w0, w19, #30
	mov	x21, 2
	cmp	w0, 4
	bls	.L2
	sub	w19, w19, #35
	mov	x0, 3
	mov	x21, 4
	cmp	w19, 7
	csel	x21, x0, x21, cc
.L2:
	cmp	w22, wzr
	lsl	x1, x21, 2
	cset	x19, eq
	sub	x1, x1, x21
	lsl	x3, x19, 2
	lsl	x4, x1, 3
	sub	x3, x3, x19
	sub	x4, x4, x1
	lsl	x0, x3, 3
	add	x1, x1, x1, lsl 4
	sub	x3, x0, x3
	mov	x2, 408
	lsl	x3, x3, 1
	add	x0, x20, 84
	sub	x3, x3, x19
	lsl	x3, x3, 4
	sub	x19, x3, x19
	lsl	x19, x19, 2
	add	x3, x19, x4, lsl 2
	add	x1, x19, x1, lsl 3
	add	x3, x20, x3
	add	x19, x19, x21, lsl 5
	add	x3, x3, 524
	add	x1, x20, x1
	add	x19, x20, x19
	add	x1, x1, 944
	add	x19, x19, 2984
	ldp	x4, x5, [x3]
	stp	x4, x5, [x20]
	ldp	x4, x5, [x3, 16]
	stp	x4, x5, [x20, 16]
	ldp	x4, x5, [x3, 32]
	stp	x4, x5, [x20, 32]
	ldp	x4, x5, [x3, 48]
	stp	x4, x5, [x20, 48]
	ldp	x4, x5, [x3, 64]
	stp	x4, x5, [x20, 64]
	ldr	w3, [x3, 80]
	str	w3, [x20, 80]
	add	x20, x20, 492
	bl	memcpy
	ldp	x0, x1, [x19]
	stp	x0, x1, [x20]
	ldp	x0, x1, [x19, 16]
	stp	x0, x1, [x20, 16]
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
	add	x2, x19, 172
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
	add	x2, x19, 332
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
	stp	wzr, wzr, [x19, 108]
	stp	wzr, wzr, [x19, 116]
	stp	w2, w2, [x19, 124]
	stp	w0, w0, [x19, 156]
	stp	w0, w0, [x19, 164]
	mov	w1, 5
	mov	w7, 2
	stp	w1, w1, [x19, 132]
	str	w7, [x19, 100]
	mov	w6, 96
	mov	w5, 10
	str	w6, [x19, 520]
	mov	w4, 15
	mov	w3, 20
	stp	w5, w4, [x19, 140]
	stp	w3, w0, [x19, 148]
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
	add	x2, x19, 332
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
	stp	wzr, w1, [x19, 124]
	stp	w1, w1, [x19, 132]
	stp	w0, w0, [x19, 164]
	mov	w8, 4
	mov	w7, 32
	str	w8, [x19, 100]
	mov	w6, 9
	str	w7, [x19, 520]
	mov	w5, 11
	mov	w4, 14
	mov	w3, 18
	stp	w6, w5, [x19, 140]
	stp	w4, w3, [x19, 148]
	mov	w2, 25
	stp	w2, w0, [x19, 156]
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
	.type	CfgStrFmt.isra.7, %function
CfgStrFmt.isra.7:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x3, .LC7
	mov	w0, 0
	ldr	w2, [x19, 64]
	bfi	w0, w20, 14, 1
	ldr	x4, [x19, 696]
	ldr	x3, [x3]
	cbnz	w2, .L22
	ldr	w2, [x19, 68]
	mov	w1, 0
	cmp	w2, wzr
	cset	w2, eq
	bfi	w0, w2, 16, 8
.L23:
	ldr	w2, [x19, 60]
	bfi	w0, w1, 6, 4
	and	w0, w0, -64
	cbnz	w2, .L29
.L24:
	str	w0, [x3, 284]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L22:
	ldr	w5, [x19, 68]
	cmp	w2, 2
	mov	w1, 3
	bfi	w0, w5, 16, 8
	beq	.L23
	cmp	w2, 1
	mov	w1, 6
	ldr	w2, [x19, 60]
	csel	w1, w1, wzr, eq
	bfi	w0, w1, 6, 4
	and	w0, w0, -64
	cbz	w2, .L24
.L29:
	str	w0, [x4, 236]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CfgStrFmt.isra.7, .-CfgStrFmt.isra.7
	.align	3
.LC7:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	CfgVcpiMode.isra.8, %function
CfgVcpiMode.isra.8:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x6
	mov	w22, w1
	mov	w21, w3
	mov	w23, w2
	mov	w25, w4
	mov	w24, w5
	bl	_mcount
	ldr	x1, .LC8
	cmp	w20, 2
	ldr	w0, [x19, 2912]
	ldr	x3, [x1]
	lsl	w0, w0, 31
	beq	.L34
	and	w1, w0, -201326593
	cmp	w20, wzr
	orr	w0, w0, 201326592
	csel	w0, w0, w1, ne
.L32:
	ldr	w1, [x19, 2616]
	cmp	w21, wzr
	ldr	w2, [x19, 2604]
	bfi	w0, w1, 30, 1
	ldr	w1, [x19, 2600]
	bfi	w0, w25, 18, 2
	ldr	w6, [x19]
	bfi	w0, w1, 21, 1
	cset	w1, eq
	bfi	w0, w2, 17, 1
	ldr	w2, [x19, 2584]
	bfi	w0, w21, 16, 1
	ldr	w4, [x19, 2636]
	bfi	w0, w24, 12, 1
	cmp	w20, 2
	bfi	w0, w1, 10, 2
	ldr	w1, [x19, 2640]
	bfi	w0, w6, 9, 1
	cset	w5, ne
	bfi	w0, w2, 8, 1
	cmp	w23, wzr
	bfi	w0, w4, 7, 1
	cset	w4, ne
	bfi	w0, w1, 6, 1
	ldr	w2, [x19, 2436]
	bfi	w0, w22, 5, 1
	bfi	w0, w5, 2, 2
	and	w0, w0, -32769
	bfi	w0, w4, 4, 1
	orr	w0, w0, 2
	bfi	w0, w2, 0, 1
	str	w0, [x3, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L34:
	mov	w1, 1
	bfi	w0, w1, 26, 2
	b	.L32
	.size	CfgVcpiMode.isra.8, .-CfgVcpiMode.isra.8
	.align	3
.LC8:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ClrInt
	.type	DRV_VENC_HAL_V500R001_ClrInt, %function
DRV_VENC_HAL_V500R001_ClrInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC9
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L37
	cbz	w19, .L38
	cmp	w19, 2
	beq	.L39
	mov	w1, -1
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L39:
	ldr	w1, [x0, 4]
	orr	w1, w1, 64
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L38:
	ldr	w1, [x0, 4]
	orr	w1, w1, 1
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L37:
	ldr	w1, [x0, 4]
	orr	w1, w1, 2
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_ClrInt, .-DRV_VENC_HAL_V500R001_ClrInt
	.align	3
.LC9:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_DisableInt
	.type	DRV_VENC_HAL_V500R001_DisableInt, %function
DRV_VENC_HAL_V500R001_DisableInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC10
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L45
	cbz	w19, .L46
	cmp	w19, 2
	beq	.L47
	str	wzr, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L47:
	ldr	w1, [x0]
	and	w1, w1, -65
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L46:
	ldr	w1, [x0]
	and	w1, w1, -2
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L45:
	ldr	w1, [x0]
	and	w1, w1, -3
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_DisableInt, .-DRV_VENC_HAL_V500R001_DisableInt
	.align	3
.LC10:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.type	DRV_VENC_HAL_V500R001_ReadReg_Smmu, %function
DRV_VENC_HAL_V500R001_ReadReg_Smmu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC11
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
	.size	DRV_VENC_HAL_V500R001_ReadReg_Smmu, .-DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.align	3
.LC11:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ReadReg
	.type	DRV_VENC_HAL_V500R001_ReadReg, %function
DRV_VENC_HAL_V500R001_ReadReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC12
	ldp	x1, x4, [x0]
	ldr	w0, [x1, 12292]
	and	w0, w0, 1
	str	w0, [x19, 8]
	ldr	w0, [x1, 12292]
	ubfx	x3, x0, 2, 1
	str	w3, [x19, 12]
	ldr	w0, [x1, 12292]
	ubfx	x0, x0, 6, 1
	str	w0, [x19]
	ldr	w0, [x1, 12292]
	ubfx	x0, x0, 1, 1
	str	w0, [x19, 4]
	ldr	w2, [x1, 12292]
	ubfx	x0, x2, 3, 1
	str	w0, [x19, 16]
	orr	w0, w3, w0
	cbnz	w0, .L53
	ldr	w0, [x4, 8]
	cbz	w0, .L56
	ldr	w0, [x1, 14272]
	lsl	w0, w0, 3
	str	w0, [x19, 20]
	ldr	w2, [x1, 15044]
	ldr	w0, [x1, 15076]
	ubfx	x2, x2, 0, 19
	ubfx	x0, x0, 0, 17
	add	w0, w2, w0
.L55:
	lsr	w0, w0, 2
	str	w0, [x19, 28]
.L53:
	ldr	w3, [x1, 14404]
	mov	w0, 0
	ldr	w2, [x1, 14408]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 32]
	ldr	w3, [x1, 14412]
	ldr	w2, [x1, 14416]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 36]
	ldr	w3, [x1, 14420]
	ldr	w2, [x1, 14424]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 40]
	ldr	w3, [x1, 14428]
	ldr	w2, [x1, 14432]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 44]
	ldr	w3, [x1, 14436]
	ldr	w2, [x1, 14440]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 48]
	ldr	w3, [x1, 14444]
	ldr	w2, [x1, 14448]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 52]
	ldr	w3, [x1, 14452]
	ldr	w2, [x1, 14456]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 56]
	ldr	w3, [x1, 14460]
	ldr	w2, [x1, 14464]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 60]
	ldr	w3, [x1, 14468]
	ldr	w2, [x1, 14472]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 64]
	ldr	w3, [x1, 14476]
	ldr	w2, [x1, 14480]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 68]
	ldr	w3, [x1, 14484]
	ldr	w2, [x1, 14488]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 72]
	ldr	w3, [x1, 14492]
	ldr	w2, [x1, 14496]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 76]
	ldr	w3, [x1, 14500]
	ldr	w2, [x1, 14504]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 80]
	ldr	w3, [x1, 14508]
	ldr	w2, [x1, 14512]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 84]
	ldr	w3, [x1, 14516]
	ldr	w2, [x1, 14520]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 88]
	ldr	w3, [x1, 14524]
	ldr	w2, [x1, 14528]
	ubfx	x3, x3, 0, 29
	and	w2, w2, 127
	sub	w2, w3, w2
	str	w2, [x19, 92]
	ldr	w2, [x1, 14408]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 96]
	ldr	w2, [x1, 14416]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 100]
	ldr	w2, [x1, 14424]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 104]
	ldr	w2, [x1, 14432]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 108]
	ldr	w2, [x1, 14440]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 112]
	ldr	w2, [x1, 14448]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 116]
	ldr	w2, [x1, 14456]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 120]
	ldr	w2, [x1, 14464]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 124]
	ldr	w2, [x1, 14472]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 128]
	ldr	w2, [x1, 14480]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 132]
	ldr	w2, [x1, 14488]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 136]
	ldr	w2, [x1, 14496]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 140]
	ldr	w2, [x1, 14504]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 144]
	ldr	w2, [x1, 14512]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 148]
	ldr	w2, [x1, 14520]
	ubfx	x2, x2, 31, 1
	str	w2, [x19, 152]
	ldr	w1, [x1, 14528]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 156]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L56:
	ldr	w0, [x1, 14400]
	lsl	w0, w0, 3
	str	w0, [x19, 20]
	ldr	w0, [x1, 15048]
	ldr	w3, [x1, 15052]
	ldr	w2, [x1, 15080]
	ubfx	x4, x0, 0, 19
	ubfx	x0, x3, 0, 19
	ubfx	x2, x2, 0, 19
	add	w0, w4, w0
	add	w0, w0, w2
	b	.L55
	.size	DRV_VENC_HAL_V500R001_ReadReg, .-DRV_VENC_HAL_V500R001_ReadReg
	.align	3
.LC12:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_CfgReg
	.type	DRV_VENC_HAL_V500R001_CfgReg, %function
DRV_VENC_HAL_V500R001_CfgReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 60]
	cbnz	w0, .L149
	ldr	x0, .LC13
	ldr	w2, [x20, 540]
	ldr	w1, [x20, 548]
	ldp	x19, x24, [x0]
	add	x22, x24, 704
	add	x21, x24, 4096
	mov	x0, x22
	add	x25, x21, 2484
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	ldr	w1, [x20, 8]
	mov	x0, x22
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	w0, [x20, 44]
	cbnz	w0, .L150
.L95:
	ldr	w0, [x20, 8]
	cbz	w0, .L151
	mov	w0, 7
	str	wzr, [x22, 5772]
	str	w0, [x22, 5768]
	str	wzr, [x22, 5776]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	beq	.L152
.L101:
	mov	w0, 207
	str	w0, [x19]
	mov	x6, x25
	ldr	w0, [x20, 8]
	ldr	w1, [x20, 44]
	ldr	w2, [x20, 60]
	ldr	w3, [x20, 540]
	ldr	w4, [x24, 6476]
	ldr	w5, [x24, 6480]
	bl	CfgVcpiMode.isra.8
	ldr	w2, [x21, 5292]
	mov	w0, 0
	ldr	w1, [x21, 5296]
	bfi	w0, w2, 16, 9
	mov	w2, 0
	bfi	w0, w1, 0, 9
	str	w0, [x19, 32]
	mov	w1, 0
	ldr	w0, [x20, 24]
	ldr	w3, [x20, 32]
	ubfiz	w0, w0, 17, 1
	orr	w0, w0, 65536
	bfi	w0, w3, 0, 16
	str	w0, [x19, 40]
	mov	w3, 4
	mov	w0, 0
	ldr	w5, [x20, 548]
	ldr	w4, [x21, 3612]
	bfi	w1, w5, 10, 6
	ldr	w5, [x21, 4948]
	bfi	w1, w5, 5, 5
	ldr	w5, [x21, 4952]
	bfi	w1, w5, 0, 5
	ldr	w5, [x21, 3628]
	bfi	w1, w5, 18, 1
	bfi	w1, w4, 19, 1
	str	w1, [x19, 44]
	mov	w1, 0
	mov	w4, 3
	bfi	w1, w3, 13, 3
	ldr	w5, [x21, 4932]
	bfi	w1, w3, 10, 3
	str	w5, [x19, 16]
	bfi	w1, w4, 7, 3
	mov	w4, 1
	bfi	w1, w4, 5, 2
	bfi	w1, w3, 2, 3
	mov	w3, 0
	bfi	w1, w4, 0, 2
	ldr	w4, [x21, 5108]
	bfi	w2, w4, 8, 2
	ldr	w4, [x21, 5112]
	bfi	w2, w4, 4, 4
	ldr	w4, [x21, 5116]
	bfi	w2, w4, 0, 4
	str	w2, [x19, 48]
	ldr	w4, [x21, 5872]
	ldr	w2, [x21, 5868]
	bfi	w0, w4, 21, 1
	ldr	w4, [x21, 5720]
	bfi	w0, w2, 19, 2
	ldr	w2, [x21, 5748]
	orr	w0, w0, 458752
	bfi	w0, w4, 2, 1
	ldr	w4, [x21, 5724]
	bfi	w0, w2, 23, 1
	ldr	w2, [x21, 5728]
	bfi	w0, w4, 3, 1
	ldr	w4, [x21, 5732]
	bfi	w0, w2, 1, 1
	mov	w2, 0
	bfi	w0, w4, 0, 1
	str	w0, [x19, 52]
	str	w1, [x19, 68]
	mov	w0, 0
	ldp	w1, w4, [x20, 16]
	sub	w4, w4, #1
	sub	w1, w1, #1
	bfi	w3, w4, 16, 13
	bfi	w3, w1, 0, 13
	str	w3, [x19, 36]
	ldr	w4, [x21, 4892]
	ldr	w1, [x21, 4896]
	bfi	w2, w4, 31, 1
	ldr	w3, [x21, 4940]
	bfi	w2, w1, 30, 1
	ldr	w1, [x21, 4944]
	sub	w3, w3, #1
	sub	w1, w1, #1
	bfi	w2, w3, 16, 9
	bfi	w2, w1, 0, 9
	str	w2, [x19, 20]
	ldr	w1, [x21, 5876]
	str	w1, [x19, 24]
	ldr	w2, [x21, 5776]
	ldr	w1, [x21, 5780]
	bfi	w0, w2, 4, 4
	bfi	w0, w1, 0, 4
	str	w0, [x19, 56]
	ldr	w0, [x21, 5504]
	cmp	w0, 1
	beq	.L153
	ldr	w1, [x21, 5128]
	mov	w0, 0
	bfi	w0, w1, 0, 2
.L103:
	str	w0, [x19, 60]
	mov	w0, 0
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x21, 5136]
	mov	w8, 0
	mov	w5, 0
	mov	w6, 0
	and	w4, w4, 1
	str	w4, [x19, 64]
	mov	w10, 2
	mov	w7, 0
	ldr	w4, [x21, 5040]
	mov	w9, 0
	bfi	w0, w4, 12, 4
	ldr	w4, [x21, 5044]
	bfi	w0, w4, 8, 4
	ldr	w4, [x21, 5056]
	bfi	w0, w4, 4, 1
	ldr	w4, [x22, 5768]
	bfi	w0, w4, 0, 3
	ldr	w4, [x21, 5060]
	bfi	w0, w4, 5, 1
	str	w0, [x19, 72]
	mov	w4, 0
	ldr	w0, [x21, 5008]
	bfi	w3, w0, 12, 1
	ldr	w0, [x21, 5016]
	bfi	w3, w0, 4, 2
	mov	w0, 0
	orr	w3, w3, 3
	str	w3, [x19, 76]
	ldr	w3, [x21, 5332]
	bfi	w2, w3, 4, 1
	ldr	w3, [x21, 5048]
	bfi	w2, w3, 2, 1
	ldr	w3, [x21, 5052]
	bfi	w2, w3, 3, 1
	ldr	w3, [x21, 5300]
	bfi	w2, w3, 1, 1
	ldr	w3, [x21, 5304]
	bfi	w2, w3, 0, 1
	str	w2, [x19, 80]
	mov	w3, 0
	ldr	w2, [x21, 5308]
	bfi	w8, w2, 16, 16
	ldr	w2, [x21, 5312]
	bfi	w8, w2, 0, 16
	str	w8, [x19, 84]
	mov	w2, 0
	ldr	w8, [x21, 5316]
	bfi	w5, w8, 24, 8
	ldr	w8, [x21, 5320]
	bfi	w5, w8, 16, 8
	ldr	w8, [x21, 5324]
	bfi	w5, w8, 8, 8
	ldr	w8, [x21, 5328]
	bfi	w5, w8, 0, 8
	str	w5, [x19, 88]
	ldr	w5, [x22, 96]
	bfi	w6, w5, 1, 1
	ldr	w5, [x21, 5708]
	bfi	w6, w5, 16, 8
	ldr	w5, [x21, 5704]
	bfi	w6, w5, 24, 8
	str	w6, [x19, 92]
	ldr	w5, [x24, 704]
	bfi	w4, w5, 2, 1
	ldr	w5, [x22, 4]
	bfi	w4, w5, 1, 1
	ldr	w5, [x21, 2488]
	bfi	w4, w5, 0, 1
	ldr	w5, [x21, 5336]
	bfi	w4, w5, 3, 1
	ldr	w5, [x21, 5340]
	bfi	w4, w5, 4, 1
	str	w4, [x19, 96]
	str	w10, [x19, 100]
	ldr	w4, [x21, 3596]
	ldr	w1, [x21, 3632]
	bfi	w0, w4, 0, 1
	ldr	w4, [x21, 3600]
	bfi	w0, w4, 1, 1
	ldr	w4, [x22, 92]
	bfi	w0, w4, 2, 1
	ldr	w4, [x21, 3624]
	bfi	w0, w4, 4, 1
	ldr	w4, [x21, 3592]
	bfi	w0, w4, 9, 1
	ldr	w4, [x22, 88]
	bfi	w0, w4, 8, 1
	ldr	w4, [x21, 3644]
	bfi	w0, w4, 3, 1
	ldr	w4, [x21, 3700]
	bfi	w0, w4, 15, 1
	ldr	w4, [x21, 3584]
	bfi	w0, w4, 14, 1
	ldr	w4, [x21, 3588]
	bfi	w0, w4, 13, 1
	ldr	w4, [x21, 3696]
	bfi	w0, w4, 12, 1
	ldr	w4, [x21, 3692]
	bfi	w0, w4, 11, 1
	ldr	w4, [x21, 3688]
	bfi	w0, w4, 10, 1
	bfi	w0, w1, 18, 1
	str	w0, [x19, 104]
	ldr	w0, [x21, 5692]
	bfi	w7, w0, 8, 1
	ldr	w0, [x21, 5696]
	bfi	w7, w0, 0, 8
	str	w7, [x19, 108]
	ldr	w0, [x21, 5700]
	bfi	w9, w0, 0, 1
	str	w9, [x19, 112]
	ldr	w4, [x21, 5864]
	ldr	w0, [x21, 5860]
	ldr	w1, [x21, 5856]
	bfi	w3, w4, 0, 1
	bfi	w3, w0, 1, 1
	ldr	w0, [x21, 5852]
	ldr	w4, [x21, 5848]
	bfi	w3, w1, 2, 1
	bfi	w3, w0, 3, 1
	ldr	w0, [x21, 5844]
	ldr	w1, [x21, 5840]
	bfi	w3, w4, 4, 1
	bfi	w3, w0, 5, 1
	ldr	w0, [x21, 5800]
	bfi	w3, w1, 6, 1
	bfi	w3, w0, 7, 1
	str	w3, [x19, 116]
	ldr	w4, [x21, 5836]
	ldr	w0, [x21, 5832]
	ldr	w3, [x21, 5828]
	bfi	w2, w4, 0, 1
	ldr	w1, [x21, 5824]
	bfi	w2, w0, 1, 1
	bfi	w2, w3, 2, 1
	ldr	w0, [x21, 5792]
	ldr	w3, [x21, 5796]
	bfi	w2, w1, 3, 1
	bfi	w2, w0, 4, 1
	ldr	w1, [x21, 5820]
	ldr	w0, [x21, 5816]
	bfi	w2, w3, 5, 1
	bfi	w2, w1, 6, 1
	ldr	w3, [x21, 5804]
	ldr	w1, [x21, 5812]
	bfi	w2, w0, 7, 1
	bfi	w2, w3, 8, 1
	ldr	w0, [x21, 5808]
	bfi	w2, w1, 9, 1
	bfi	w2, w0, 10, 1
	str	w2, [x19, 120]
	ldr	w0, [x20, 8]
	ldr	w1, [x20, 60]
	cmp	w0, w10
	ldr	x2, [x20, 696]
	beq	.L154
	cbnz	w0, .L105
	mov	w0, 15
	mov	w23, 0
	bfi	w23, w0, 16, 6
	mov	w0, 31
	bfi	w23, w0, 0, 7
.L105:
	cbz	w1, .L106
	str	w23, [x2, 80]
.L107:
	mov	w2, 1
	mov	w0, 0
	bfi	w0, w2, 16, 6
	mov	w1, 43691
	bfi	w0, w2, 0, 7
	str	w0, [x19, 128]
	movk	w1, 0xaaaa, lsl 16
	mov	w5, 0
	ldr	w0, [x20, 172]
	mov	w4, 0
	mov	w6, 0
	add	x0, x0, 40
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 132]
	ldr	w0, [x20, 172]
	add	w0, w0, 2
	umull	x2, w0, w1
	lsr	x2, x2, 32
	lsr	w2, w2, 1
	lsl	w3, w2, 2
	sub	w2, w3, w2
	mov	w3, 0
	sub	w0, w0, w2
	add	x0, x0, 40
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 136]
	ldr	w2, [x20, 172]
	add	w2, w2, 1
	umull	x0, w2, w1
	lsr	x0, x0, 32
	lsr	w0, w0, 1
	lsl	w1, w0, 2
	sub	w0, w1, w0
	sub	w2, w2, w0
	add	x2, x2, 40
	ldr	w0, [x20, x2, lsl 2]
	mov	w2, 0
	str	w0, [x19, 140]
	ldr	w0, [x20, 200]
	str	w0, [x19, 144]
	ldr	w0, [x20, 72]
	str	w0, [x19, 148]
	ldr	w0, [x20, 76]
	str	w0, [x19, 152]
	ldr	w0, [x20, 80]
	str	w0, [x19, 156]
	ldr	w0, [x20, 84]
	bfi	w5, w0, 16, 16
	ldr	w0, [x20, 88]
	bfi	w5, w0, 0, 16
	str	w5, [x19, 168]
	mov	x0, x20
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 92]
	str	w1, [x19, 172]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 100]
	str	w1, [x19, 176]
	ldr	w1, [x20, 108]
	bfi	w4, w1, 0, 16
	ldr	w1, [x20, 112]
	bfi	w4, w1, 16, 16
	str	w4, [x19, 180]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 116]
	str	w1, [x19, 184]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 124]
	str	w1, [x19, 188]
	ldr	w1, [x20, 132]
	bfi	w6, w1, 0, 16
	str	w6, [x19, 192]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 20
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 12]
	str	w1, [x19, 196]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 24
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 4]
	str	w1, [x19, 200]
	ldp	w4, w1, [x20, 108]
	bfi	w3, w4, 16, 16
	bfi	w3, w1, 0, 16
	str	w3, [x19, 204]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 28
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 4]
	str	w1, [x19, 208]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 28
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 12]
	str	w1, [x19, 212]
	ldp	w3, w1, [x20, 132]
	bfi	w2, w3, 16, 16
	bfi	w2, w1, 0, 16
	str	w2, [x19, 216]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 36
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 8]
	str	w1, [x19, 220]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 152]
	str	w1, [x19, 252]
	ldr	w1, [x20, 140]
	add	x1, x1, 36
	ldr	w1, [x20, x1, lsl 2]
	str	w1, [x19, 260]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 36
	ldr	w1, [x20, x1, lsl 2]
	str	w1, [x19, 264]
	ldr	w1, [x20, 204]
	str	w1, [x19, 268]
	ldr	w1, [x20, 336]
	str	w1, [x19, 272]
	ldr	w1, [x20, 332]
	str	w1, [x19, 276]
	ldr	w1, [x24, 9624]
	bl	CfgStrFmt.isra.7
	mov	w0, 168
	movk	w0, 0x1a8, lsl 16
	str	w0, [x19, 296]
	ldr	w2, [x21, 4616]
	ldr	w6, [x21, 4620]
	ldr	w7, [x21, 4624]
	ldr	w8, [x21, 4628]
	uxtb	w2, w2
	ldr	w1, [x21, 4608]
	uxtb	w6, w6
	ldr	w5, [x21, 4612]
	uxtb	w7, w7
	ldr	w3, [x21, 4600]
	uxtb	w8, w8
	ldr	w4, [x21, 4604]
	orr	w0, w6, w2
	uxtb	w5, w5
	uxtb	w1, w1
	orr	w9, w8, w7
	uxtb	w3, w3
	uxtb	w4, w4
	orr	w9, w9, w0
	orr	w0, w5, w1
	ldr	w10, [x21, 4852]
	orr	w9, w9, w0
	orr	w0, w4, w3
	orr	w9, w9, w0
	mov	w0, 0
	bfi	w0, w9, 24, 1
	ldr	w9, [x21, 4848]
	bfi	w0, w10, 23, 1
	bfi	w0, w9, 22, 1
	ldr	w9, [x21, 4844]
	bfi	w0, w9, 21, 1
	ldr	w9, [x21, 4840]
	bfi	w0, w9, 20, 1
	ldr	w9, [x21, 4836]
	bfi	w0, w9, 19, 1
	ldr	w9, [x21, 4832]
	bfi	w0, w9, 18, 1
	ldr	w9, [x21, 4828]
	bfi	w0, w9, 17, 1
	ldr	w9, [x21, 4824]
	bfi	w0, w9, 16, 1
	ldr	w9, [x21, 4660]
	bfi	w0, w9, 15, 1
	ldr	w9, [x21, 4656]
	bfi	w0, w9, 14, 1
	ldr	w9, [x21, 4652]
	bfi	w0, w9, 13, 1
	ldr	w9, [x21, 4648]
	bfi	w0, w9, 12, 1
	ldr	w9, [x21, 4644]
	bfi	w0, w9, 11, 1
	ldr	w9, [x21, 4640]
	bfi	w0, w9, 10, 1
	ldr	w9, [x21, 4636]
	bfi	w0, w9, 9, 1
	ldr	w9, [x21, 4632]
	bfi	w0, w9, 8, 1
	bfi	w0, w8, 7, 1
	bfi	w0, w7, 6, 1
	mov	w7, 0
	bfi	w0, w6, 5, 1
	bfi	w0, w2, 4, 1
	mov	w2, 0
	bfi	w0, w5, 3, 1
	mov	w5, 0
	bfi	w0, w1, 2, 1
	mov	w1, 0
	bfi	w0, w4, 1, 1
	mov	w4, 0
	bfi	w0, w3, 0, 1
	str	w0, [x19, 512]
	ldr	w3, [x21, 4676]
	ldr	w0, [x21, 4672]
	bfi	w2, w3, 24, 7
	ldr	w3, [x21, 4668]
	bfi	w2, w0, 16, 7
	ldr	w0, [x21, 4664]
	bfi	w2, w3, 8, 7
	bfi	w2, w0, 0, 7
	str	w2, [x19, 516]
	mov	w2, 0
	mov	w0, 0
	ldr	w3, [x21, 4692]
	bfi	w1, w3, 24, 7
	ldr	w3, [x21, 4688]
	bfi	w1, w3, 16, 7
	ldr	w3, [x21, 4684]
	bfi	w1, w3, 8, 7
	ldr	w3, [x21, 4680]
	bfi	w1, w3, 0, 7
	str	w1, [x19, 520]
	mov	w3, 0
	mov	w1, 0
	ldr	w6, [x21, 4728]
	bfi	w5, w6, 16, 10
	ldr	w6, [x21, 4696]
	bfi	w5, w6, 0, 10
	str	w5, [x19, 524]
	ldr	w5, [x21, 4732]
	bfi	w4, w5, 16, 10
	ldr	w5, [x21, 4700]
	bfi	w4, w5, 0, 10
	str	w4, [x19, 528]
	mov	w5, 0
	mov	w4, 0
	ldr	w6, [x21, 4736]
	bfi	w2, w6, 16, 10
	ldr	w6, [x21, 4704]
	bfi	w2, w6, 0, 10
	str	w2, [x19, 532]
	ldr	w2, [x21, 4740]
	bfi	w0, w2, 16, 10
	ldr	w2, [x21, 4708]
	bfi	w0, w2, 0, 10
	str	w0, [x19, 536]
	mov	w2, 0
	mov	w0, 0
	ldr	w6, [x21, 4744]
	bfi	w3, w6, 16, 10
	ldr	w6, [x21, 4712]
	bfi	w3, w6, 0, 10
	str	w3, [x19, 540]
	ldr	w3, [x21, 4748]
	bfi	w1, w3, 16, 10
	ldr	w3, [x21, 4716]
	bfi	w1, w3, 0, 10
	str	w1, [x19, 544]
	mov	w3, 0
	mov	w1, 0
	ldr	w6, [x21, 4752]
	bfi	w5, w6, 16, 10
	ldr	w6, [x21, 4720]
	bfi	w5, w6, 0, 10
	str	w5, [x19, 548]
	ldr	w5, [x21, 4756]
	bfi	w4, w5, 16, 10
	ldr	w5, [x21, 4724]
	bfi	w4, w5, 0, 10
	str	w4, [x19, 552]
	mov	w5, 0
	mov	w4, 0
	ldr	w6, [x21, 4792]
	bfi	w2, w6, 16, 9
	ldr	w6, [x21, 4760]
	bfi	w2, w6, 0, 9
	str	w2, [x19, 556]
	ldr	w2, [x21, 4796]
	bfi	w0, w2, 16, 9
	ldr	w2, [x21, 4764]
	bfi	w0, w2, 0, 9
	str	w0, [x19, 560]
	mov	w2, 0
	mov	w0, 0
	ldr	w6, [x21, 4800]
	bfi	w3, w6, 16, 9
	ldr	w6, [x21, 4768]
	bfi	w3, w6, 0, 9
	str	w3, [x19, 564]
	ldr	w3, [x21, 4804]
	bfi	w1, w3, 16, 9
	ldr	w3, [x21, 4772]
	bfi	w1, w3, 0, 9
	str	w1, [x19, 568]
	mov	w3, 16
	mov	w1, 32
	ldr	w6, [x21, 4808]
	bfi	w5, w6, 16, 9
	ldr	w6, [x21, 4776]
	bfi	w5, w6, 0, 9
	str	w5, [x19, 572]
	ldr	w5, [x21, 4812]
	bfi	w4, w5, 16, 9
	ldr	w5, [x21, 4780]
	bfi	w4, w5, 0, 9
	str	w4, [x19, 576]
	mov	w5, 0
	mov	w4, 0
	ldr	w6, [x21, 4816]
	bfi	w2, w6, 16, 9
	ldr	w6, [x21, 4784]
	bfi	w2, w6, 0, 9
	str	w2, [x19, 580]
	mov	w6, 0
	ldr	w2, [x21, 4820]
	bfi	w0, w2, 16, 9
	ldr	w2, [x21, 4788]
	bfi	w0, w2, 0, 9
	str	w0, [x19, 584]
	add	x0, x21, 2484
	ldr	w2, [x20, 8]
	add	x10, x0, 1280
	cmp	w2, wzr
	csel	w3, w1, w3, ne
	ldp	w2, w1, [x20, 16]
	sub	w2, w2, #1
	sub	w1, w1, #1
	add	w2, w2, w3
	add	w1, w1, w3
	udiv	w2, w2, w3
	udiv	w1, w1, w3
	ldr	w3, [x20, 544]
	mul	w1, w2, w1
	mov	w2, 0
	udiv	w1, w3, w1
	mov	w3, 0
	bfi	w5, w1, 0, 20
	str	w5, [x19, 588]
	mov	w5, 0
	ldr	w1, [x21, 5352]
	bfi	w4, w1, 0, 4
	str	w4, [x19, 592]
	mov	w4, 0
	ldr	w1, [x22, 8]
	bfi	w6, w1, 16, 5
	ldr	w1, [x0, 16]
	bfi	w6, w1, 0, 8
	ldr	w1, [x0, 392]
	bfi	w6, w1, 24, 4
	str	w6, [x19, 604]
	mov	w1, 0
	ldr	w6, [x0, 656]
	bfi	w2, w6, 0, 3
	ldr	w6, [x0, 660]
	bfi	w2, w6, 3, 7
	ldr	w6, [x0, 664]
	bfi	w2, w6, 10, 3
	ldr	w6, [x0, 672]
	bfi	w2, w6, 18, 4
	ldr	w6, [x0, 680]
	bfi	w2, w6, 26, 4
	str	w2, [x19, 608]
	mov	w6, 0
	ldr	w2, [x0, 488]
	bfi	w4, w2, 0, 1
	ldr	w2, [x0, 492]
	bfi	w4, w2, 1, 3
	ldr	w2, [x0, 504]
	bfi	w4, w2, 15, 6
	ldr	w2, [x0, 508]
	bfi	w4, w2, 21, 5
	str	w4, [x19, 612]
	mov	w2, 0
	ldr	w4, [x0, 28]
	bfi	w5, w4, 16, 5
	ldr	w4, [x22, 12]
	bfi	w5, w4, 0, 8
	ldr	w4, [x0, 400]
	bfi	w5, w4, 24, 4
	str	w5, [x19, 620]
	mov	w5, 0
	ldr	w4, [x0, 684]
	bfi	w1, w4, 0, 3
	ldr	w4, [x0, 688]
	bfi	w1, w4, 3, 7
	ldr	w4, [x0, 692]
	bfi	w1, w4, 10, 3
	ldr	w4, [x0, 700]
	bfi	w1, w4, 18, 4
	ldr	w4, [x0, 708]
	bfi	w1, w4, 26, 4
	str	w1, [x19, 624]
	mov	w4, 0
	ldr	w1, [x0, 512]
	bfi	w3, w1, 0, 1
	ldr	w1, [x0, 516]
	bfi	w3, w1, 1, 3
	ldr	w1, [x0, 528]
	bfi	w3, w1, 15, 6
	ldr	w1, [x0, 532]
	bfi	w3, w1, 21, 5
	str	w3, [x19, 628]
	mov	w3, 0
	ldr	w1, [x22, 24]
	bfi	w6, w1, 16, 5
	ldr	w1, [x22, 28]
	bfi	w6, w1, 0, 8
	ldr	w1, [x0, 416]
	bfi	w6, w1, 24, 4
	str	w6, [x19, 636]
	mov	w1, 0
	ldr	w6, [x0, 736]
	bfi	w2, w6, 0, 3
	ldr	w6, [x0, 740]
	bfi	w2, w6, 3, 7
	ldr	w6, [x0, 744]
	bfi	w2, w6, 10, 3
	ldr	w6, [x0, 752]
	bfi	w2, w6, 18, 4
	ldr	w6, [x0, 760]
	bfi	w2, w6, 26, 4
	str	w2, [x19, 640]
	mov	w6, 0
	ldr	w2, [x0, 560]
	bfi	w4, w2, 0, 1
	ldr	w2, [x0, 564]
	bfi	w4, w2, 1, 3
	ldr	w2, [x0, 576]
	bfi	w4, w2, 15, 6
	ldr	w2, [x0, 580]
	bfi	w4, w2, 21, 5
	str	w4, [x19, 644]
	mov	w2, 0
	ldr	w4, [x22, 60]
	bfi	w5, w4, 0, 8
	ldr	w4, [x22, 64]
	bfi	w5, w4, 16, 5
	ldr	w4, [x0, 424]
	bfi	w5, w4, 24, 4
	str	w5, [x19, 652]
	mov	w5, 0
	ldr	w4, [x0, 308]
	bfi	w1, w4, 0, 3
	ldr	w4, [x0, 312]
	bfi	w1, w4, 3, 7
	ldr	w4, [x0, 316]
	bfi	w1, w4, 10, 3
	ldr	w4, [x0, 324]
	bfi	w1, w4, 18, 4
	ldr	w4, [x0, 332]
	bfi	w1, w4, 26, 4
	str	w1, [x19, 656]
	mov	w4, 0
	ldr	w1, [x0, 584]
	bfi	w3, w1, 0, 1
	ldr	w1, [x0, 588]
	bfi	w3, w1, 1, 3
	ldr	w1, [x0, 600]
	bfi	w3, w1, 15, 6
	ldr	w1, [x0, 604]
	bfi	w3, w1, 21, 5
	str	w3, [x19, 660]
	mov	w3, 0
	ldr	w1, [x22, 16]
	bfi	w6, w1, 16, 5
	ldr	w1, [x22, 20]
	bfi	w6, w1, 0, 8
	ldr	w1, [x0, 408]
	bfi	w6, w1, 24, 4
	str	w6, [x19, 668]
	mov	w1, 0
	ldr	w6, [x22, 68]
	bfi	w2, w6, 0, 3
	ldr	w6, [x0, 712]
	bfi	w2, w6, 3, 7
	ldr	w6, [x0, 716]
	bfi	w2, w6, 10, 3
	ldr	w6, [x0, 724]
	bfi	w2, w6, 18, 4
	ldr	w6, [x0, 732]
	bfi	w2, w6, 26, 4
	str	w2, [x19, 672]
	ldr	w2, [x0, 536]
	mov	w6, 0
	bfi	w4, w2, 0, 1
	ldr	w2, [x0, 540]
	bfi	w4, w2, 1, 3
	ldr	w2, [x0, 552]
	bfi	w4, w2, 15, 6
	ldr	w2, [x0, 556]
	bfi	w4, w2, 21, 5
	str	w4, [x19, 676]
	mov	w2, 0
	ldr	w4, [x0, 464]
	bfi	w5, w4, 0, 8
	ldr	w4, [x0, 468]
	bfi	w5, w4, 16, 5
	ldr	w4, [x0, 432]
	bfi	w5, w4, 24, 4
	str	w5, [x19, 684]
	mov	w5, 0
	ldr	w4, [x0, 336]
	bfi	w1, w4, 0, 3
	ldr	w4, [x0, 340]
	bfi	w1, w4, 3, 7
	ldr	w4, [x0, 344]
	bfi	w1, w4, 10, 3
	ldr	w4, [x0, 352]
	bfi	w1, w4, 18, 4
	ldr	w4, [x0, 360]
	bfi	w1, w4, 26, 4
	str	w1, [x19, 688]
	mov	w4, 0
	ldr	w1, [x0, 608]
	bfi	w3, w1, 0, 1
	ldr	w1, [x0, 612]
	bfi	w3, w1, 1, 3
	ldr	w1, [x0, 624]
	bfi	w3, w1, 15, 6
	ldr	w1, [x0, 628]
	bfi	w3, w1, 21, 5
	str	w3, [x19, 692]
	mov	w3, 0
	ldr	w1, [x0, 480]
	bfi	w6, w1, 0, 8
	ldr	w1, [x0, 484]
	bfi	w6, w1, 16, 5
	ldr	w1, [x0, 440]
	bfi	w6, w1, 24, 4
	str	w6, [x19, 700]
	mov	w1, 0
	ldr	w6, [x0, 364]
	bfi	w2, w6, 0, 3
	ldr	w6, [x0, 368]
	bfi	w2, w6, 3, 7
	ldr	w6, [x0, 372]
	bfi	w2, w6, 10, 3
	ldr	w6, [x0, 380]
	bfi	w2, w6, 18, 4
	ldr	w6, [x0, 388]
	bfi	w2, w6, 26, 4
	str	w2, [x19, 704]
	ldr	w2, [x0, 632]
	bfi	w5, w2, 0, 1
	ldr	w2, [x0, 636]
	bfi	w5, w2, 1, 3
	ldr	w2, [x0, 648]
	bfi	w5, w2, 15, 6
	ldr	w2, [x0, 652]
	bfi	w5, w2, 21, 5
	str	w5, [x19, 708]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x0, 60]
	bfi	w4, w6, 0, 4
	ldr	w6, [x0, 56]
	bfi	w4, w6, 4, 4
	ldr	w6, [x0, 52]
	bfi	w4, w6, 8, 4
	ldr	w6, [x0, 72]
	bfi	w4, w6, 16, 4
	ldr	w6, [x0, 68]
	bfi	w4, w6, 20, 4
	ldr	w6, [x22, 32]
	bfi	w4, w6, 24, 4
	str	w4, [x19, 712]
	ldr	w4, [x0, 140]
	bfi	w1, w4, 0, 4
	ldr	w4, [x0, 136]
	bfi	w1, w4, 4, 4
	ldr	w4, [x22, 44]
	bfi	w1, w4, 8, 4
	ldr	w4, [x0, 156]
	bfi	w1, w4, 16, 4
	ldr	w4, [x0, 152]
	bfi	w1, w4, 20, 4
	ldr	w4, [x0, 148]
	bfi	w1, w4, 24, 4
	str	w1, [x19, 716]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x0, 224]
	bfi	w3, w6, 0, 4
	ldr	w6, [x0, 220]
	bfi	w3, w6, 4, 4
	ldr	w6, [x22, 56]
	bfi	w3, w6, 8, 4
	ldr	w6, [x0, 240]
	bfi	w3, w6, 16, 4
	ldr	w6, [x0, 236]
	bfi	w3, w6, 20, 4
	ldr	w6, [x0, 232]
	bfi	w3, w6, 24, 4
	str	w3, [x19, 720]
	ldr	w3, [x0, 80]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 84]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 88]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 96]
	bfi	w2, w3, 24, 4
	ldr	w3, [x22, 36]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 100]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 724]
	mov	w3, 0
	mov	w2, 0
	ldr	w6, [x0, 164]
	bfi	w5, w6, 8, 4
	ldr	w6, [x22, 48]
	bfi	w5, w6, 4, 4
	ldr	w6, [x0, 168]
	bfi	w5, w6, 0, 4
	ldr	w6, [x0, 176]
	bfi	w5, w6, 24, 4
	ldr	w6, [x0, 180]
	bfi	w5, w6, 20, 4
	ldr	w6, [x0, 184]
	bfi	w5, w6, 16, 4
	str	w5, [x19, 728]
	mov	w6, 0
	ldr	w5, [x0, 248]
	bfi	w1, w5, 8, 4
	ldr	w5, [x0, 252]
	bfi	w1, w5, 4, 4
	ldr	w5, [x0, 256]
	bfi	w1, w5, 0, 4
	ldr	w5, [x0, 264]
	bfi	w1, w5, 24, 4
	ldr	w5, [x0, 268]
	bfi	w1, w5, 20, 4
	ldr	w5, [x0, 272]
	bfi	w1, w5, 16, 4
	str	w1, [x19, 732]
	mov	w1, 0
	ldr	w5, [x0, 108]
	bfi	w4, w5, 8, 4
	ldr	w5, [x0, 112]
	bfi	w4, w5, 4, 4
	ldr	w5, [x0, 116]
	bfi	w4, w5, 0, 4
	ldr	w5, [x0, 124]
	bfi	w4, w5, 24, 4
	ldr	w5, [x22, 40]
	bfi	w4, w5, 20, 4
	ldr	w5, [x0, 128]
	bfi	w4, w5, 16, 4
	str	w4, [x19, 736]
	mov	w5, 0
	ldr	w4, [x0, 192]
	bfi	w3, w4, 8, 4
	ldr	w4, [x22, 52]
	bfi	w3, w4, 4, 4
	ldr	w4, [x0, 196]
	bfi	w3, w4, 0, 4
	ldr	w4, [x0, 204]
	bfi	w3, w4, 24, 4
	ldr	w4, [x0, 208]
	bfi	w3, w4, 20, 4
	ldr	w4, [x0, 212]
	bfi	w3, w4, 16, 4
	str	w3, [x19, 740]
	mov	w4, 0
	ldr	w3, [x0, 280]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 284]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 288]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 296]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 300]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 304]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 744]
	mov	w3, 0
	ldr	w2, [x0, 764]
	bfi	w1, w2, 0, 4
	ldr	w2, [x0, 768]
	bfi	w1, w2, 4, 4
	ldr	w2, [x0, 772]
	bfi	w1, w2, 8, 4
	ldr	w2, [x0, 776]
	bfi	w1, w2, 12, 4
	ldr	w2, [x0, 780]
	bfi	w1, w2, 16, 4
	ldr	w2, [x0, 784]
	bfi	w1, w2, 20, 4
	str	w1, [x19, 748]
	mov	w2, 0
	ldr	w1, [x22, 72]
	bfi	w6, w1, 0, 12
	ldr	w1, [x22, 76]
	bfi	w6, w1, 12, 12
	ldr	w1, [x0, 788]
	bfi	w6, w1, 24, 8
	str	w6, [x19, 752]
	mov	w6, 0
	ldr	w1, [x0, 792]
	bfi	w5, w1, 0, 12
	ldr	w1, [x0, 796]
	bfi	w5, w1, 12, 12
	ldr	w1, [x0, 800]
	bfi	w5, w1, 24, 8
	str	w5, [x19, 756]
	mov	w1, 0
	ldr	w5, [x22, 80]
	bfi	w4, w5, 0, 12
	ldr	w5, [x0, 804]
	bfi	w4, w5, 12, 12
	ldr	w5, [x0, 808]
	bfi	w4, w5, 24, 8
	str	w4, [x19, 760]
	ldr	w4, [x0, 812]
	bfi	w3, w4, 0, 8
	ldr	w4, [x0, 816]
	bfi	w3, w4, 8, 8
	ldr	w4, [x0, 820]
	bfi	w3, w4, 16, 8
	str	w3, [x19, 764]
	mov	w3, 0
	mov	w4, 0
	ldr	w5, [x21, 5572]
	bfi	w2, w5, 14, 1
	ldr	w5, [x21, 5576]
	bfi	w2, w5, 15, 1
	ldr	w5, [x20, 44]
	bfi	w2, w5, 28, 1
	ldr	w5, [x22, 5764]
	bfi	w2, w5, 20, 8
	str	w2, [x19, 1024]
	mov	w5, 0
	ldr	w2, [x21, 5592]
	bfi	w1, w2, 0, 8
	ldr	w2, [x21, 5588]
	bfi	w1, w2, 8, 8
	ldr	w2, [x21, 5584]
	bfi	w1, w2, 16, 8
	ldr	w2, [x21, 5580]
	bfi	w1, w2, 24, 8
	str	w1, [x19, 1028]
	mov	w1, 0
	ldr	w2, [x0, 1280]
	bfi	w6, w2, 0, 1
	str	w6, [x19, 1536]
	ldr	w2, [x0, 1284]
	bfi	w3, w2, 0, 16
	str	w3, [x19, 1540]
	mov	w3, 0
	mov	w2, 0
	ldr	w6, [x0, 1288]
	bfi	w4, w6, 0, 16
	str	w4, [x19, 1544]
	ldr	w4, [x0, 1292]
	bfi	w1, w4, 0, 16
	str	w1, [x19, 1548]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x0, 1340]
	bfi	w5, w6, 16, 1
	ldr	w6, [x0, 1344]
	bfi	w5, w6, 0, 16
	str	w5, [x19, 1552]
	ldr	w5, [x0, 1296]
	bfi	w3, w5, 18, 9
	ldr	w5, [x0, 1300]
	bfi	w3, w5, 9, 9
	ldr	w5, [x0, 1304]
	bfi	w3, w5, 0, 9
	str	w3, [x19, 1556]
	mov	w3, 0
	mov	w5, 0
	ldr	w6, [x0, 1308]
	bfi	w2, w6, 16, 8
	ldr	w6, [x0, 1312]
	bfi	w2, w6, 8, 8
	ldr	w6, [x0, 1316]
	bfi	w2, w6, 0, 8
	str	w2, [x19, 1560]
	ldr	w2, [x0, 1320]
	bfi	w1, w2, 8, 4
	ldr	w2, [x0, 1324]
	bfi	w1, w2, 4, 4
	ldr	w2, [x0, 1328]
	bfi	w1, w2, 0, 4
	ldr	w2, [x0, 1336]
	bfi	w1, w2, 12, 8
	ldr	w2, [x0, 1332]
	bfi	w1, w2, 20, 8
	str	w1, [x19, 1564]
	mov	w1, 0
	mov	w2, 0
	ldr	w6, [x21, 4524]
	bfi	w4, w6, 0, 8
	ldr	w6, [x21, 4520]
	bfi	w4, w6, 8, 8
	ldr	w6, [x21, 4516]
	bfi	w4, w6, 16, 8
	ldr	w6, [x21, 4512]
	bfi	w4, w6, 24, 8
	str	w4, [x19, 1572]
	ldr	w4, [x0, 1348]
	bfi	w3, w4, 24, 8
	ldr	w4, [x0, 1352]
	bfi	w3, w4, 16, 8
	ldr	w4, [x0, 1356]
	bfi	w3, w4, 8, 8
	ldr	w4, [x0, 1360]
	bfi	w3, w4, 0, 8
	str	w3, [x19, 1576]
	mov	w4, 0
	mov	w3, 0
	ldr	w6, [x0, 1412]
	bfi	w5, w6, 0, 8
	ldr	w6, [x21, 4552]
	bfi	w5, w6, 17, 1
	str	w5, [x19, 1580]
	mov	w6, 0
	ldr	w5, [x0, 1424]
	bfi	w1, w5, 0, 16
	ldr	w5, [x0, 1428]
	bfi	w1, w5, 16, 16
	str	w1, [x19, 1584]
	mov	w1, 0
	ldr	w5, [x22, 492]
	bfi	w2, w5, 22, 9
	ldr	w5, [x22, 496]
	bfi	w2, w5, 17, 5
	ldr	w5, [x22, 500]
	bfi	w2, w5, 9, 8
	ldr	w5, [x22, 520]
	bfi	w2, w5, 0, 9
	str	w2, [x19, 1588]
	mov	w5, 0
	ldr	w2, [x22, 516]
	bfi	w4, w2, 8, 14
	ldr	w2, [x21, 4436]
	bfi	w4, w2, 0, 8
	str	w4, [x19, 1592]
	mov	w4, 0
	ldr	w2, [x22, 504]
	bfi	w3, w2, 16, 8
	ldr	w2, [x22, 508]
	bfi	w3, w2, 8, 8
	ldr	w2, [x22, 512]
	bfi	w3, w2, 0, 8
	str	w3, [x19, 1596]
	ldr	w2, [x21, 4444]
	bfi	w1, w2, 18, 1
	ldr	w2, [x21, 4448]
	bfi	w1, w2, 12, 2
	ldr	w2, [x21, 4456]
	bfi	w1, w2, 4, 4
	ldr	w2, [x21, 4460]
	bfi	w1, w2, 0, 4
	str	w1, [x19, 1600]
	mov	w2, 0
	ldr	w1, [x21, 4464]
	bfi	w6, w1, 0, 10
	ldr	w1, [x21, 4468]
	bfi	w6, w1, 16, 9
	str	w6, [x19, 1604]
	mov	w6, 0
	ldr	w1, [x21, 4472]
	bfi	w5, w1, 0, 10
	ldr	w1, [x21, 4476]
	bfi	w5, w1, 16, 9
	str	w5, [x19, 1608]
	mov	w1, 0
	mov	w5, 0
	ldr	w3, [x21, 4480]
	bfi	w4, w3, 0, 10
	ldr	w3, [x21, 4484]
	bfi	w4, w3, 16, 9
	str	w4, [x19, 1612]
	ldr	w3, [x21, 4488]
	bfi	w2, w3, 0, 10
	ldr	w3, [x21, 4492]
	bfi	w2, w3, 16, 9
	str	w2, [x19, 1616]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x21, 4496]
	bfi	w7, w4, 0, 16
	str	w7, [x19, 1620]
	ldr	w4, [x21, 4528]
	bfi	w1, w4, 0, 13
	ldr	w4, [x21, 4532]
	bfi	w1, w4, 13, 1
	str	w1, [x19, 1624]
	mov	w1, 0
	ldr	w4, [x21, 4536]
	bfi	w6, w4, 0, 18
	str	w6, [x19, 1628]
	ldr	w4, [x21, 4540]
	bfi	w3, w4, 0, 18
	str	w3, [x19, 1632]
	mov	w4, 0
	mov	w3, 0
	ldr	w6, [x21, 4564]
	bfi	w2, w6, 16, 7
	ldr	w6, [x21, 4568]
	bfi	w2, w6, 23, 7
	str	w2, [x19, 1636]
	ldr	w2, [x21, 4548]
	bfi	w1, w2, 12, 8
	ldr	w2, [x21, 4572]
	bfi	w1, w2, 8, 4
	ldr	w2, [x21, 4576]
	bfi	w1, w2, 0, 8
	ldr	w2, [x21, 4580]
	bfi	w1, w2, 20, 8
	ldr	w2, [x21, 4584]
	bfi	w1, w2, 28, 4
	str	w1, [x19, 1640]
	mov	w2, 0
	mov	w1, 0
	ldr	w6, [x21, 4556]
	bfi	w5, w6, 0, 8
	ldr	w6, [x21, 4560]
	bfi	w5, w6, 8, 8
	ldr	w6, [x21, 4544]
	bfi	w5, w6, 16, 8
	str	w5, [x19, 1644]
	ldr	w5, [x21, 4588]
	bfi	w4, w5, 0, 8
	ldr	w5, [x21, 4592]
	bfi	w4, w5, 8, 8
	ldr	w5, [x21, 4596]
	bfi	w4, w5, 16, 16
	str	w4, [x19, 1648]
	mov	w4, 0
	ldr	w5, [x0, 1364]
	bfi	w3, w5, 24, 8
	ldr	w5, [x0, 1368]
	bfi	w3, w5, 16, 8
	ldr	w5, [x0, 1372]
	bfi	w3, w5, 8, 8
	ldr	w5, [x0, 1376]
	bfi	w3, w5, 0, 8
	str	w3, [x19, 1652]
	ldr	w5, [x0, 1380]
	ldr	w3, [x0, 1384]
	bfi	w2, w5, 24, 8
	ldr	w5, [x0, 1388]
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1392]
	bfi	w2, w5, 8, 8
	bfi	w2, w3, 0, 8
	str	w2, [x19, 1656]
	ldp	w5, w3, [x10, 116]
	ldp	w2, w0, [x10, 124]
	bfi	w1, w5, 28, 4
	bfi	w1, w3, 23, 5
	bfi	w1, w2, 14, 9
	bfi	w1, w0, 0, 14
	str	w1, [x19, 1660]
	ldr	w2, [x20, 556]
	ldr	w1, [x21, 4956]
	ldr	w0, [x20, 552]
	bfi	w4, w2, 8, 6
	bfi	w4, w1, 16, 1
	bfi	w4, w0, 0, 6
	str	w4, [x19, 2304]
	ldr	w0, [x20, 8]
	cbnz	w0, .L109
	ldr	w0, [x20, 20]
	mov	w1, 0
	ldr	w2, [x20, 544]
	lsr	w0, w0, 4
	udiv	w0, w2, w0
	bfi	w1, w0, 6, 25
.L110:
	ldr	w2, [x22, 100]
	add	x0, x21, 2484
	mov	w3, 0
	mov	w5, 0
	bfi	w1, w2, 0, 6
	str	w1, [x19, 2308]
	mov	w2, 0
	mov	w4, 0
	ldr	w1, [x0, 988]
	bfi	w3, w1, 0, 16
	str	w3, [x19, 2312]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x0, 960]
	bfi	w5, w6, 8, 6
	ldr	w6, [x0, 936]
	bfi	w5, w6, 16, 4
	ldr	w6, [x0, 964]
	bfi	w5, w6, 0, 6
	str	w5, [x19, 2316]
	ldr	w5, [x0, 948]
	bfi	w2, w5, 8, 6
	ldr	w5, [x0, 928]
	bfi	w2, w5, 16, 4
	ldr	w5, [x0, 1264]
	bfi	w2, w5, 0, 6
	str	w2, [x19, 2320]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x0, 948]
	bfi	w4, w6, 8, 6
	ldr	w6, [x0, 932]
	bfi	w4, w6, 16, 4
	ldr	w6, [x0, 1252]
	bfi	w4, w6, 0, 6
	str	w4, [x19, 2324]
	ldr	w4, [x0, 944]
	bfi	w1, w4, 8, 6
	ldr	w4, [x0, 924]
	bfi	w1, w4, 16, 4
	ldr	w4, [x0, 1260]
	bfi	w1, w4, 0, 6
	str	w1, [x19, 2328]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 104]
	bfi	w3, w6, 8, 6
	ldr	w6, [x22, 84]
	bfi	w3, w6, 16, 4
	ldr	w6, [x0, 1248]
	bfi	w3, w6, 0, 6
	str	w3, [x19, 2332]
	ldr	w3, [x0, 940]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 956]
	bfi	w2, w3, 8, 6
	ldr	w3, [x0, 1256]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 2336]
	mov	w3, 0
	mov	w2, 0
	ldr	w6, [x0, 968]
	bfi	w5, w6, 16, 4
	ldr	w6, [x0, 972]
	bfi	w5, w6, 20, 4
	ldr	w6, [x0, 976]
	bfi	w5, w6, 8, 6
	ldr	w6, [x0, 1268]
	bfi	w5, w6, 0, 6
	str	w5, [x19, 2340]
	ldr	w5, [x22, 120]
	mov	w6, 0
	bfi	w1, w5, 24, 8
	ldr	w5, [x22, 116]
	bfi	w1, w5, 16, 8
	ldr	w5, [x22, 112]
	bfi	w1, w5, 8, 8
	ldr	w5, [x22, 108]
	bfi	w1, w5, 0, 8
	str	w1, [x19, 2344]
	mov	w1, 0
	ldr	w5, [x22, 136]
	bfi	w4, w5, 24, 8
	ldr	w5, [x22, 132]
	bfi	w4, w5, 16, 8
	ldr	w5, [x22, 128]
	bfi	w4, w5, 8, 8
	ldr	w5, [x22, 124]
	bfi	w4, w5, 0, 8
	str	w4, [x19, 2348]
	mov	w5, 0
	ldr	w4, [x22, 152]
	bfi	w3, w4, 24, 8
	ldr	w4, [x22, 148]
	bfi	w3, w4, 16, 8
	ldr	w4, [x22, 144]
	bfi	w3, w4, 8, 8
	ldr	w4, [x22, 140]
	bfi	w3, w4, 0, 8
	str	w3, [x19, 2352]
	mov	w3, 0
	ldr	w4, [x22, 168]
	bfi	w2, w4, 24, 8
	ldr	w4, [x22, 164]
	bfi	w2, w4, 16, 8
	ldr	w4, [x22, 160]
	bfi	w2, w4, 8, 8
	ldr	w4, [x22, 156]
	bfi	w2, w4, 0, 8
	str	w2, [x19, 2356]
	mov	w4, 0
	ldr	w2, [x0, 848]
	bfi	w1, w2, 0, 2
	ldr	w2, [x0, 852]
	bfi	w1, w2, 2, 2
	ldr	w2, [x0, 856]
	bfi	w1, w2, 4, 2
	ldr	w2, [x0, 860]
	bfi	w1, w2, 6, 2
	ldr	w2, [x0, 864]
	bfi	w1, w2, 8, 2
	ldr	w2, [x0, 868]
	bfi	w1, w2, 10, 2
	ldr	w2, [x0, 872]
	bfi	w1, w2, 12, 2
	ldr	w2, [x0, 876]
	bfi	w1, w2, 14, 2
	ldr	w2, [x0, 880]
	bfi	w1, w2, 16, 2
	ldr	w2, [x0, 884]
	bfi	w1, w2, 18, 2
	ldr	w2, [x0, 888]
	bfi	w1, w2, 20, 2
	ldr	w2, [x0, 892]
	bfi	w1, w2, 22, 2
	ldr	w2, [x0, 896]
	bfi	w1, w2, 24, 2
	ldr	w2, [x0, 900]
	bfi	w1, w2, 26, 2
	ldr	w2, [x0, 904]
	bfi	w1, w2, 28, 2
	ldr	w2, [x0, 908]
	bfi	w1, w2, 30, 2
	str	w1, [x19, 2360]
	mov	w1, 0
	ldr	w2, [x0, 912]
	bfi	w6, w2, 0, 5
	str	w6, [x19, 2364]
	ldr	w2, [x0, 980]
	bfi	w3, w2, 0, 4
	ldr	w2, [x0, 984]
	bfi	w3, w2, 4, 4
	str	w3, [x19, 2368]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 172]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2372]
	ldr	w5, [x22, 176]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2376]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 180]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2380]
	ldr	w4, [x22, 184]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2384]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 188]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2388]
	ldr	w3, [x22, 192]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2392]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 196]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2396]
	ldr	w5, [x22, 200]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2400]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 204]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2404]
	ldr	w4, [x22, 208]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2408]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 212]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2412]
	ldr	w3, [x22, 216]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2416]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 220]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2420]
	ldr	w5, [x22, 224]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2424]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 228]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2428]
	ldr	w4, [x22, 232]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2432]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 236]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2436]
	ldr	w3, [x22, 240]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2440]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 244]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2444]
	ldr	w5, [x22, 248]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2448]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 252]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2452]
	ldr	w4, [x22, 256]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2456]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 260]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2460]
	ldr	w3, [x22, 264]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2464]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 268]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2468]
	ldr	w5, [x22, 272]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2472]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 276]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2476]
	ldr	w4, [x22, 280]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2480]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 284]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2484]
	ldr	w3, [x22, 288]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2488]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 292]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2492]
	ldr	w5, [x22, 296]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2496]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 300]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2500]
	ldr	w4, [x22, 304]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2504]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 308]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2508]
	ldr	w3, [x22, 312]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2512]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 316]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2516]
	ldr	w5, [x22, 320]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2520]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 324]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2524]
	ldr	w4, [x22, 328]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2528]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 332]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2532]
	ldr	w3, [x22, 336]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2536]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 340]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2540]
	ldr	w5, [x22, 344]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2544]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 348]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2548]
	ldr	w4, [x22, 352]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2552]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 356]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2556]
	ldr	w3, [x22, 360]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2560]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 364]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2564]
	ldr	w5, [x22, 368]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2568]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 372]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2572]
	ldr	w4, [x22, 376]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2576]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 380]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2580]
	ldr	w3, [x22, 384]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2584]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 388]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2588]
	ldr	w5, [x22, 392]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2592]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 396]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2596]
	ldr	w4, [x22, 400]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2600]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 404]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2604]
	ldr	w3, [x22, 408]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2608]
	mov	w2, 0
	mov	w3, 0
	ldr	w6, [x22, 412]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2612]
	ldr	w5, [x22, 416]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2616]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 420]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2620]
	ldr	w4, [x22, 424]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 2624]
	mov	w2, 0
	mov	w4, 0
	ldr	w6, [x22, 428]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2628]
	ldr	w3, [x22, 432]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 2632]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x22, 436]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2636]
	ldr	w5, [x22, 440]
	bfi	w2, w5, 0, 20
	str	w2, [x19, 2640]
	mov	w2, 0
	mov	w5, 0
	ldr	w6, [x22, 444]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2644]
	ldr	w4, [x22, 448]
	bfi	w1, w4, 0, 20
	str	w1, [x19, 2648]
	mov	w1, 0
	mov	w4, 0
	ldr	w6, [x22, 452]
	bfi	w3, w6, 0, 20
	str	w3, [x19, 2652]
	ldr	w3, [x22, 456]
	bfi	w2, w3, 0, 20
	str	w2, [x19, 2656]
	mov	w3, 0
	mov	w2, 0
	ldr	w6, [x22, 460]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2660]
	ldr	w5, [x22, 464]
	bfi	w1, w5, 0, 20
	str	w1, [x19, 2664]
	mov	w1, 0
	mov	w5, 0
	ldr	w6, [x22, 468]
	bfi	w4, w6, 0, 20
	str	w4, [x19, 2668]
	ldr	w4, [x22, 472]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 2672]
	mov	w4, 0
	mov	w3, 0
	ldr	w6, [x22, 476]
	bfi	w2, w6, 0, 20
	str	w2, [x19, 2676]
	ldr	w2, [x22, 480]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 2680]
	mov	w1, 0
	mov	w2, 0
	ldr	w6, [x22, 484]
	bfi	w5, w6, 0, 20
	str	w5, [x19, 2684]
	ldr	w5, [x22, 488]
	bfi	w4, w5, 0, 20
	str	w4, [x19, 2688]
	mov	w5, 0
	mov	w4, 0
	ldr	w6, [x0, 1196]
	bfi	w3, w6, 8, 2
	ldr	w6, [x0, 1200]
	bfi	w3, w6, 12, 1
	ldr	w6, [x0, 1008]
	bfi	w3, w6, 0, 5
	str	w3, [x19, 2692]
	ldr	w3, [x0, 1004]
	bfi	w1, w3, 16, 4
	ldr	w3, [x0, 1184]
	bfi	w1, w3, 12, 4
	ldr	w3, [x0, 996]
	bfi	w1, w3, 9, 2
	ldr	w3, [x0, 1000]
	bfi	w1, w3, 8, 1
	ldr	w3, [x0, 992]
	bfi	w1, w3, 0, 6
	str	w1, [x19, 2696]
	ldr	w1, [x0, 1164]
	str	w1, [x19, 2700]
	ldr	w1, [x0, 1168]
	str	w1, [x19, 2704]
	ldr	w3, [x0, 1192]
	ldrh	w1, [x0, 1172]
	bfi	w1, w3, 21, 1
	ldr	w3, [x0, 1180]
	bfi	w1, w3, 18, 2
	ldr	w3, [x0, 1176]
	bfi	w1, w3, 16, 2
	str	w1, [x19, 2708]
	mov	w1, 0
	mov	w3, 0
	ldr	w6, [x21, 5716]
	bfi	w2, w6, 4, 2
	ldr	w6, [x21, 5064]
	bfi	w2, w6, 1, 1
	ldr	w6, [x21, 5736]
	bfi	w2, w6, 2, 1
	str	w2, [x19, 3328]
	ldr	w2, [x21, 5416]
	mov	w6, 0
	bfi	w5, w2, 16, 16
	ldr	w2, [x21, 5420]
	bfi	w5, w2, 0, 16
	str	w5, [x19, 3332]
	mov	w2, 0
	ldr	w5, [x21, 5740]
	bfi	w4, w5, 6, 6
	ldr	w5, [x21, 5744]
	bfi	w4, w5, 0, 6
	str	w4, [x19, 3336]
	ldr	w4, [x21, 5400]
	bfi	w1, w4, 31, 1
	ldr	w4, [x21, 5404]
	bfi	w1, w4, 0, 17
	str	w1, [x19, 3340]
	mov	w4, 0
	mov	w1, 0
	ldr	w5, [x21, 5408]
	bfi	w3, w5, 16, 11
	ldr	w5, [x21, 5412]
	bfi	w3, w5, 0, 10
	str	w3, [x19, 3344]
	mov	w5, 0
	ldr	w3, [x21, 5512]
	bfi	w2, w3, 3, 1
	ldr	w3, [x21, 5516]
	bfi	w2, w3, 2, 1
	ldr	w3, [x21, 5520]
	bfi	w2, w3, 1, 1
	ldr	w3, [x21, 5508]
	bfi	w2, w3, 0, 1
	str	w2, [x19, 3840]
	mov	w2, 0
	ldr	w3, [x21, 5524]
	bfi	w6, w3, 4, 1
	str	w6, [x19, 3844]
	ldr	w3, [x21, 5168]
	bfi	w4, w3, 0, 1
	str	w4, [x19, 4096]
	mov	w4, 0
	mov	w3, -1
	ldr	w6, [x21, 5176]
	bfi	w1, w6, 15, 1
	ldr	w6, [x21, 5180]
	bfi	w1, w6, 14, 1
	ldr	w6, [x21, 5184]
	bfi	w1, w6, 13, 1
	ldr	w6, [x21, 5188]
	bfi	w1, w6, 12, 1
	ldr	w6, [x21, 5192]
	bfi	w1, w6, 8, 4
	ldr	w6, [x21, 5196]
	bfi	w1, w6, 4, 4
	ldr	w6, [x21, 5200]
	bfi	w1, w6, 0, 4
	str	w1, [x19, 4100]
	ldr	w1, [x21, 5204]
	bfi	w5, w1, 0, 4
	str	w5, [x19, 4104]
	mov	w5, 7
	mov	w1, 0
	ldr	w6, [x21, 5216]
	bfi	w2, w6, 0, 8
	ldr	w6, [x21, 5212]
	bfi	w2, w6, 8, 8
	ldr	w6, [x21, 5208]
	bfi	w2, w6, 16, 8
	str	w2, [x19, 4108]
	ldr	w2, [x21, 5224]
	bfi	w4, w2, 0, 16
	str	w4, [x19, 4112]
	str	w3, [x19, 4116]
	mov	w4, 0
	str	w3, [x19, 4120]
	mov	w2, 0
	str	w5, [x19, 4124]
	str	w3, [x19, 4128]
	str	w5, [x19, 4132]
	ldr	w5, [x21, 5288]
	ldr	w3, [x21, 5284]
	bfi	w1, w5, 3, 1
	ldr	w5, [x21, 5280]
	bfi	w1, w3, 2, 1
	mov	w3, 0
	bfi	w1, w5, 1, 1
	mov	w5, 0
	orr	w1, w1, 1
	str	w1, [x19, 4136]
	ldr	w1, [x21, 5532]
	str	w1, [x19, 4352]
	ldr	w1, [x21, 5536]
	str	w1, [x19, 4356]
	ldr	w1, [x21, 5540]
	str	w1, [x19, 4360]
	ldr	w1, [x21, 5544]
	str	w1, [x19, 4364]
	ldr	w1, [x21, 5548]
	str	w1, [x19, 4368]
	ldr	w1, [x21, 5552]
	str	w1, [x19, 4372]
	ldr	w1, [x21, 5504]
	bfi	w4, w1, 0, 1
	str	w4, [x19, 4376]
	mov	w1, 0
	ldr	w4, [x21, 5768]
	bfi	w2, w4, 0, 8
	ldr	w4, [x21, 5772]
	bfi	w2, w4, 8, 8
	str	w2, [x19, 4608]
	mov	w4, 0
	mov	w2, 0
	ldr	w6, [x0, 824]
	bfi	w3, w6, 0, 16
	ldr	w6, [x0, 828]
	bfi	w3, w6, 16, 16
	str	w3, [x19, 5376]
	ldr	w3, [x0, 840]
	bfi	w5, w3, 16, 16
	str	w5, [x19, 5380]
	mov	w3, 513
	mov	w5, 9729
	ldr	w6, [x0, 832]
	bfi	w1, w6, 0, 16
	ldr	w6, [x0, 836]
	bfi	w1, w6, 16, 16
	str	w1, [x19, 5384]
	mov	w1, 0
	ldr	w0, [x0, 844]
	bfi	w4, w0, 0, 3
	str	w4, [x19, 5392]
	ldr	w4, [x20, 540]
	ldr	w0, [x21, 5472]
	cmp	w4, wzr
	mov	w4, 0
	csel	w3, w3, w5, eq
	bfi	w2, w0, 8, 3
	bfi	w2, w3, 16, 16
	str	w2, [x19, 6656]
	mov	w0, 16
	mov	w5, 0
	ldr	w3, [x20, 636]
	ldr	w2, [x20, 640]
	bfi	w1, w3, 0, 5
	bfi	w1, w2, 16, 16
	str	w1, [x19, 6660]
	mov	w1, 0
	ldr	w2, [x20, 636]
	ldr	w3, [x20, 676]
	sub	w2, w0, w2
	lsl	w2, w3, w2
	bfi	w5, w2, 0, 16
	str	w5, [x19, 6664]
	ldr	w3, [x22, 5868]
	ldr	w2, [x22, 5872]
	bfi	w1, w3, 0, 5
	bfi	w1, w2, 16, 16
	str	w1, [x19, 6700]
	ldr	w2, [x22, 5868]
	ldr	w1, [x22, 5864]
	sub	w0, w0, w2
	lsl	w0, w1, w0
	bfi	w4, w0, 0, 16
	str	w4, [x19, 6704]
	ldr	w0, [x20, 8]
	cmp	w0, 2
	beq	.L155
.L113:
	cbnz	w0, .L119
	ldr	w0, [x20, 604]
	str	w0, [x19, 6912]
	ldr	w0, [x20, 608]
	str	w0, [x19, 6916]
	ldr	w0, [x20, 612]
	str	w0, [x19, 6920]
	ldr	w0, [x20, 616]
	str	w0, [x19, 6924]
	ldr	w0, [x20, 620]
	str	w0, [x19, 6928]
	ldr	w0, [x20, 624]
	str	w0, [x19, 6932]
	ldr	w0, [x20, 628]
	str	w0, [x19, 6936]
	ldr	w0, [x20, 632]
	str	w0, [x19, 6940]
	ldr	w0, [x20, 636]
	ldr	w1, [x19, 6944]
	sub	w0, w0, #1
	bfi	w1, w0, 16, 7
	str	w1, [x19, 6944]
	ldr	w0, [x20, 636]
	ldr	w1, [x19, 6944]
	lsr	w0, w0, 8
	sub	w0, w0, #1
	bfi	w1, w0, 8, 6
	str	w1, [x19, 6944]
	ldrh	w0, [x20, 638]
	ldr	w1, [x19, 6944]
	sub	w0, w0, #1
	bfi	w1, w0, 0, 6
	str	w1, [x19, 6944]
.L119:
	ldr	w1, [x21, 5500]
	mov	w0, 0
	bfi	w0, w1, 1, 24
	str	w0, [x19, 6948]
	ldr	w0, [x20, 8]
	cmp	w0, 2
	beq	.L156
.L120:
	cbnz	w0, .L126
	ldr	w0, [x22, 5800]
	str	w0, [x19, 6952]
	ldr	w0, [x22, 5804]
	str	w0, [x19, 6956]
	ldr	w0, [x22, 5808]
	str	w0, [x19, 6960]
	ldr	w0, [x22, 5812]
	str	w0, [x19, 6964]
	ldr	w0, [x22, 5816]
	str	w0, [x19, 6968]
	ldr	w0, [x22, 5820]
	str	w0, [x19, 6972]
	ldr	w0, [x22, 5824]
	str	w0, [x19, 6976]
	ldr	w0, [x22, 5828]
	str	w0, [x19, 6980]
	ldr	w0, [x22, 5796]
	ldr	w1, [x19, 6984]
	sub	w0, w0, #1
	bfi	w1, w0, 16, 7
	str	w1, [x19, 6984]
	ldr	w0, [x22, 5796]
	ldr	w1, [x19, 6984]
	lsr	w0, w0, 8
	sub	w0, w0, #1
	bfi	w1, w0, 8, 6
	str	w1, [x19, 6984]
	ldrh	w0, [x22, 5798]
	ldr	w1, [x19, 6984]
	sub	w0, w0, #1
	bfi	w1, w0, 0, 6
	str	w1, [x19, 6984]
.L126:
	ldr	w1, [x20, 52]
	mov	w0, 0
	bfi	w0, w1, 0, 1
	str	w0, [x19, 7168]
	ldr	w0, [x21, 5880]
	str	w0, [x19, 7172]
	ldr	w0, [x20, 540]
	cbz	w0, .L127
	ldr	w0, [x19, 7312]
	orr	w0, w0, 65536
	str	w0, [x19, 7312]
.L128:
	ldr	w0, [x19, 7312]
	orr	w0, w0, 256
	str	w0, [x19, 7312]
	ldr	w0, [x19, 7312]
	tbz	x0, 16, .L129
	ldrb	w1, [x20, 344]
	ldr	w0, [x19, 7312]
	bfi	w0, w1, 0, 8
	str	w0, [x19, 7312]
	ldr	w0, [x20, 348]
	str	w0, [x19, 7316]
	ldr	w0, [x20, 352]
	str	w0, [x19, 7320]
	ldr	w0, [x20, 356]
	str	w0, [x19, 7324]
	ldr	w0, [x20, 360]
	str	w0, [x19, 7328]
	ldr	w0, [x20, 364]
	str	w0, [x19, 7332]
	ldr	w0, [x20, 368]
	str	w0, [x19, 7336]
	ldr	w0, [x20, 372]
	str	w0, [x19, 7340]
	ldr	w0, [x20, 376]
	str	w0, [x19, 7344]
	ldr	w0, [x20, 380]
	str	w0, [x19, 7348]
	ldr	w0, [x20, 384]
	str	w0, [x19, 7352]
	ldr	w0, [x20, 388]
	str	w0, [x19, 7356]
	ldr	w0, [x20, 392]
	str	w0, [x19, 7360]
	ldr	w0, [x20, 396]
	str	w0, [x19, 7364]
	ldr	w0, [x20, 400]
	str	w0, [x19, 7368]
	ldr	w0, [x20, 404]
	str	w0, [x19, 7372]
	ldr	w0, [x20, 408]
	str	w0, [x19, 7376]
	ldr	w0, [x20, 412]
	str	w0, [x19, 7380]
	ldr	w0, [x20, 416]
	str	w0, [x19, 7384]
	ldr	w0, [x20, 420]
	str	w0, [x19, 7388]
	ldr	w0, [x20, 424]
	str	w0, [x19, 7392]
	ldr	w0, [x20, 428]
	str	w0, [x19, 7396]
	ldr	w0, [x20, 432]
	str	w0, [x19, 7400]
	ldr	w0, [x20, 436]
	str	w0, [x19, 7404]
	ldr	w0, [x20, 440]
	str	w0, [x19, 7408]
	ldr	w0, [x20, 444]
	str	w0, [x19, 7412]
	ldr	w0, [x20, 448]
	str	w0, [x19, 7416]
	ldr	w0, [x20, 452]
	str	w0, [x19, 7420]
	ldr	w0, [x20, 456]
	str	w0, [x19, 7424]
	ldr	w0, [x20, 460]
	str	w0, [x19, 7428]
	ldr	w0, [x20, 464]
	str	w0, [x19, 7432]
	ldr	w0, [x20, 468]
	str	w0, [x19, 7436]
	ldr	w0, [x20, 472]
	str	w0, [x19, 7440]
	ldr	w0, [x20, 476]
	str	w0, [x19, 7444]
	ldr	w0, [x20, 480]
	str	w0, [x19, 7448]
	ldr	w0, [x20, 484]
	str	w0, [x19, 7452]
	ldr	w0, [x20, 488]
	str	w0, [x19, 7456]
	ldr	w0, [x20, 492]
	str	w0, [x19, 7460]
	ldr	w0, [x20, 496]
	str	w0, [x19, 7464]
	ldr	w0, [x20, 500]
	str	w0, [x19, 7468]
	ldr	w0, [x20, 504]
	str	w0, [x19, 7472]
	ldr	w0, [x20, 508]
	str	w0, [x19, 7476]
	ldr	w0, [x20, 512]
	str	w0, [x19, 7480]
	ldr	w0, [x20, 516]
	str	w0, [x19, 7484]
	ldr	w0, [x20, 520]
	str	w0, [x19, 7488]
	ldr	w0, [x20, 524]
	str	w0, [x19, 7492]
	ldr	w0, [x20, 528]
	str	w0, [x19, 7496]
	ldr	w0, [x20, 532]
	str	w0, [x19, 7500]
	ldr	w0, [x20, 536]
	str	w0, [x19, 7504]
.L129:
	ldr	w1, [x20, 204]
	mov	w2, 0
	str	w1, [x19, 7244]
	mov	w3, 0
	add	x0, x19, 61440
	mov	w10, 3
	ldr	w1, [x20, 208]
	mov	w9, 0
	str	w1, [x19, 7248]
	mov	w1, 9
	bfi	w2, w1, 24, 8
	mov	w8, 0
	ldr	w1, [x20, 212]
	mov	w7, 0
	str	w1, [x19, 7252]
	mov	w1, 7
	bfi	w2, w1, 16, 8
	mov	w6, 0
	ldr	w1, [x20, 216]
	mov	w4, 1
	str	w1, [x19, 7256]
	mov	w5, 0
	and	w2, w2, -65281
	ldr	w1, [x20, 220]
	bfi	w2, w4, 0, 8
	str	w1, [x19, 7260]
	ldr	w11, [x20, 224]
	str	w11, [x19, 7264]
	ldr	w11, [x20, 228]
	str	w11, [x19, 7268]
	ldr	w11, [x20, 232]
	str	w11, [x19, 7272]
	ldr	w11, [x20, 236]
	str	w11, [x19, 7276]
	ldr	w11, [x20, 240]
	str	w11, [x19, 7280]
	ldr	w11, [x20, 244]
	str	w11, [x19, 7284]
	ldr	w11, [x20, 248]
	str	w11, [x19, 7288]
	ldr	w11, [x20, 252]
	str	w11, [x19, 7292]
	ldr	w11, [x20, 256]
	str	w11, [x19, 7296]
	ldr	w11, [x20, 260]
	str	w11, [x19, 7300]
	ldr	w11, [x20, 264]
	str	w11, [x19, 7304]
	ldr	w11, [x20, 340]
	str	w11, [x19, 7308]
	ldr	w11, [x20, 268]
	str	w11, [x19, 7180]
	ldr	w11, [x20, 272]
	str	w11, [x19, 7184]
	ldr	w11, [x20, 276]
	str	w11, [x19, 7188]
	ldr	w11, [x20, 280]
	str	w11, [x19, 7192]
	ldr	w11, [x20, 284]
	str	w11, [x19, 7196]
	ldr	w11, [x20, 288]
	str	w11, [x19, 7200]
	ldr	w11, [x20, 292]
	str	w11, [x19, 7204]
	ldr	w11, [x20, 296]
	str	w11, [x19, 7208]
	ldr	w11, [x20, 300]
	str	w11, [x19, 7212]
	ldr	w11, [x20, 304]
	str	w11, [x19, 7216]
	ldr	w11, [x20, 308]
	str	w11, [x19, 7220]
	ldr	w11, [x20, 312]
	str	w11, [x19, 7224]
	ldr	w11, [x20, 316]
	str	w11, [x19, 7228]
	ldr	w11, [x20, 320]
	str	w11, [x19, 7232]
	ldr	w11, [x20, 324]
	str	w11, [x19, 7236]
	ldr	w11, [x20, 328]
	str	w11, [x19, 7240]
	ldr	w11, [x21, 5784]
	bfi	w3, w11, 0, 1
	ldr	w11, [x21, 5788]
	bfi	w3, w11, 3, 1
	bfi	w3, w10, 16, 4
	str	w3, [x0]
	str	w9, [x0, 8]
	str	w8, [x0, 16]
	str	w7, [x0, 28]
	str	w6, [x0, 32]
	str	w5, [x0, 44]
	str	w2, [x0, 1328]
	str	wzr, [x19, 4]
	ldr	w2, [x20, 580]
	str	w2, [x0, 520]
	ldr	w2, [x20, 580]
	str	w2, [x0, 524]
	ldr	w2, [x20, 588]
	str	w2, [x0, 752]
	ldr	w2, [x20, 584]
	str	w2, [x0, 756]
	ldr	w2, [x20, 588]
	str	w2, [x0, 772]
	ldr	w1, [x20, 584]
	str	w1, [x0, 776]
	mov	w0, 0
	str	w4, [x19, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L156:
	ldr	w0, [x22, 5872]
	cmp	w0, 31
	bhi	.L121
	ldr	w1, [x22, 5832]
	mov	w2, 32
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6708]
	ldr	w0, [x22, 5872]
	cmp	w0, 63
	bhi	.L123
.L167:
	ldr	w1, [x22, 5836]
	mov	w2, 64
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6712]
.L124:
	ldr	w0, [x22, 5872]
	cmp	w0, 64
	bls	.L125
	ldr	w1, [x22, 5840]
	mov	w2, 96
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6716]
.L125:
	ldr	w0, [x22, 5844]
	str	w0, [x19, 6720]
	ldr	w0, [x22, 5848]
	str	w0, [x19, 6724]
	ldr	w0, [x22, 5852]
	str	w0, [x19, 6728]
	ldr	w0, [x22, 5856]
	str	w0, [x19, 6732]
	ldr	w0, [x22, 5860]
	str	w0, [x19, 6736]
	ldr	w0, [x20, 8]
	b	.L120
	.p2align 3
.L155:
	ldr	w0, [x20, 640]
	cmp	w0, 31
	bhi	.L114
	ldr	w1, [x20, 644]
	mov	w2, 32
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6668]
	ldr	w0, [x20, 640]
	cmp	w0, 63
	bhi	.L116
.L168:
	ldr	w1, [x20, 648]
	mov	w2, 64
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6672]
.L117:
	ldr	w0, [x20, 640]
	cmp	w0, 64
	bls	.L118
	ldr	w1, [x20, 652]
	mov	w2, 96
	sub	w0, w2, w0
	lsl	w0, w1, w0
	str	w0, [x19, 6676]
.L118:
	ldr	w0, [x20, 656]
	str	w0, [x19, 6680]
	ldr	w0, [x20, 660]
	str	w0, [x19, 6684]
	ldr	w0, [x20, 664]
	str	w0, [x19, 6688]
	ldr	w0, [x20, 668]
	str	w0, [x19, 6692]
	ldr	w0, [x20, 672]
	str	w0, [x19, 6696]
	ldr	w0, [x20, 8]
	b	.L113
	.p2align 3
.L149:
	ldr	x26, .LC13
	mov	x2, 704
	ldr	x0, .LC14
	mov	x1, x20
	ldr	x19, [x20, 696]
	ldp	x23, x25, [x26]
	ldr	x3, [x0, 8]
	mov	x0, x25
	add	x22, x25, x2
	add	x21, x25, 4096
	blr	x3
	ldr	w2, [x20, 540]
	mov	x0, x22
	ldr	w1, [x20, 548]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	ldr	w1, [x20, 8]
	mov	x0, x22
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	w0, [x20, 44]
	add	x6, x21, 2484
	cbnz	w0, .L157
.L59:
	ldr	w0, [x20, 8]
	cbz	w0, .L158
	mov	w0, 7
	str	wzr, [x22, 5772]
	str	w0, [x22, 5768]
	str	wzr, [x22, 5776]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	beq	.L159
.L65:
	ldr	w1, [x20, 688]
	mov	w0, 207
	str	w1, [x23, 280]
	mov	w2, 0
	str	w0, [x23]
	mov	w0, 0
	add	x27, x21, 2484
	ldr	w1, [x21, 4932]
	str	w1, [x23, 16]
	ldr	w1, [x21, 4892]
	bfi	w0, w1, 31, 1
	ldr	w1, [x21, 4896]
	bfi	w0, w1, 30, 1
	ldr	w1, [x21, 4940]
	sub	w1, w1, #1
	bfi	w0, w1, 16, 9
	ldr	w1, [x21, 4944]
	sub	w1, w1, #1
	bfi	w0, w1, 0, 9
	str	w0, [x23, 20]
	mov	w0, 0
	ldr	w1, [x21, 5876]
	str	w1, [x23, 24]
	ldr	w1, [x21, 5872]
	bfi	w0, w1, 21, 1
	ldr	w1, [x21, 5868]
	bfi	w0, w1, 19, 2
	ldr	w1, [x21, 5720]
	orr	w0, w0, 458752
	bfi	w0, w1, 2, 1
	ldr	w1, [x21, 5748]
	bfi	w0, w1, 23, 1
	ldr	w1, [x21, 5724]
	bfi	w0, w1, 3, 1
	ldr	w1, [x21, 5728]
	bfi	w0, w1, 1, 1
	ldr	w1, [x21, 5732]
	bfi	w0, w1, 0, 1
	str	w0, [x23, 52]
	mov	w1, 4
	ldr	w0, [x21, 5776]
	bfi	w2, w0, 4, 4
	ldr	w0, [x21, 5780]
	bfi	w2, w0, 0, 4
	mov	w0, 0
	bfi	w0, w1, 13, 3
	str	w2, [x23, 56]
	bfi	w0, w1, 10, 3
	mov	w2, 3
	bfi	w0, w2, 7, 3
	mov	w2, 1
	bfi	w0, w2, 5, 2
	bfi	w0, w1, 2, 3
	bfi	w0, w2, 0, 2
	str	w0, [x23, 68]
	mov	w2, 16
	mov	w0, 32
	ldr	w1, [x20, 8]
	cmp	w1, wzr
	csel	w2, w0, w2, ne
	ldr	w0, [x20, 16]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w1, w0, w2
	ldr	w0, [x20, 20]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	ldr	w2, [x20, 544]
	mul	w0, w1, w0
	mov	w1, 0
	udiv	w0, w2, w0
	bfi	w1, w0, 0, 20
	str	w1, [x23, 588]
	ldr	w1, [x21, 5352]
	mov	w0, 0
	bfi	w0, w1, 0, 4
	str	w0, [x23, 592]
	ldr	w5, [x25, 6480]
	ldr	w4, [x25, 6476]
	ldr	w0, [x20, 8]
	ldr	w1, [x20, 44]
	ldr	w2, [x20, 60]
	ldr	w3, [x20, 540]
	bl	CfgVcpiMode.isra.8
	ldr	w1, [x21, 5292]
	mov	w0, 0
	bfi	w0, w1, 16, 9
	ldr	w1, [x21, 5296]
	bfi	w0, w1, 0, 9
	str	w0, [x19]
	ldr	w0, [x20, 24]
	ldr	w1, [x20, 32]
	ubfiz	w0, w0, 17, 1
	orr	w0, w0, 65536
	bfi	w0, w1, 0, 16
	str	w0, [x19, 8]
	mov	w0, 0
	ldr	w1, [x20, 548]
	ldr	w3, [x27, 1144]
	bfi	w0, w1, 10, 6
	ldr	w1, [x21, 4948]
	ldr	w2, [x27, 1128]
	bfi	w0, w1, 5, 5
	ldr	w1, [x21, 4952]
	bfi	w0, w1, 0, 5
	mov	w1, 0
	bfi	w0, w3, 18, 1
	bfi	w0, w2, 19, 1
	str	w0, [x19, 12]
	ldr	w0, [x21, 5108]
	ldr	w2, [x21, 5112]
	bfi	w1, w0, 8, 2
	ldr	w0, [x21, 5116]
	bfi	w1, w2, 4, 4
	bfi	w1, w0, 0, 4
	str	w1, [x19, 16]
	mov	w0, 0
	ldp	w1, w2, [x20, 16]
	sub	w2, w2, #1
	sub	w1, w1, #1
	bfi	w0, w2, 16, 13
	bfi	w0, w1, 0, 13
	str	w0, [x19, 4]
	ldr	w0, [x21, 5504]
	cmp	w0, 1
	beq	.L160
	ldr	w1, [x21, 5128]
	mov	w0, 0
	bfi	w0, w1, 0, 2
.L68:
	str	w0, [x19, 20]
	mov	w0, 0
	mov	w2, 0
	mov	w5, 0
	ldr	w3, [x21, 5136]
	mov	w6, 0
	mov	w7, 0
	mov	w9, 2
	and	w3, w3, 1
	str	w3, [x19, 24]
	mov	w3, 0
	mov	w8, 0
	ldr	w4, [x21, 5040]
	bfi	w0, w4, 12, 4
	ldr	w4, [x21, 5044]
	bfi	w0, w4, 8, 4
	ldr	w4, [x21, 5056]
	bfi	w0, w4, 4, 1
	ldr	w4, [x22, 5768]
	bfi	w0, w4, 0, 3
	ldr	w4, [x21, 5060]
	bfi	w0, w4, 5, 1
	str	w0, [x19, 28]
	mov	w4, 0
	ldr	w0, [x21, 5008]
	bfi	w2, w0, 12, 1
	ldr	w0, [x21, 5016]
	bfi	w2, w0, 4, 2
	mov	w0, 0
	orr	w2, w2, 3
	str	w2, [x19, 32]
	ldr	w2, [x21, 5332]
	bfi	w5, w2, 4, 1
	ldr	w2, [x21, 5048]
	bfi	w5, w2, 2, 1
	ldr	w2, [x21, 5052]
	bfi	w5, w2, 3, 1
	ldr	w2, [x21, 5300]
	bfi	w5, w2, 1, 1
	ldr	w2, [x21, 5304]
	bfi	w5, w2, 0, 1
	str	w5, [x19, 36]
	mov	w5, 0
	ldr	w2, [x21, 5308]
	bfi	w3, w2, 16, 16
	ldr	w2, [x21, 5312]
	bfi	w3, w2, 0, 16
	str	w3, [x19, 40]
	mov	w3, 0
	mov	w2, 0
	ldr	w10, [x21, 5316]
	bfi	w6, w10, 24, 8
	ldr	w10, [x21, 5320]
	bfi	w6, w10, 16, 8
	ldr	w10, [x21, 5324]
	bfi	w6, w10, 8, 8
	ldr	w10, [x21, 5328]
	bfi	w6, w10, 0, 8
	str	w6, [x19, 44]
	ldr	w6, [x22, 96]
	bfi	w7, w6, 1, 1
	ldr	w6, [x21, 5708]
	bfi	w7, w6, 16, 8
	ldr	w6, [x21, 5704]
	bfi	w7, w6, 24, 8
	str	w7, [x19, 48]
	ldr	w6, [x25, 704]
	bfi	w4, w6, 2, 1
	ldr	w6, [x22, 4]
	bfi	w4, w6, 1, 1
	ldr	w6, [x21, 2488]
	bfi	w4, w6, 0, 1
	ldr	w6, [x21, 5336]
	bfi	w4, w6, 3, 1
	ldr	w6, [x21, 5340]
	bfi	w4, w6, 4, 1
	stp	w4, w9, [x19, 52]
	ldr	w4, [x21, 3596]
	ldr	w1, [x21, 3632]
	bfi	w0, w4, 0, 1
	ldr	w4, [x21, 3600]
	bfi	w0, w4, 1, 1
	ldr	w4, [x22, 92]
	bfi	w0, w4, 2, 1
	ldr	w4, [x21, 3624]
	bfi	w0, w4, 4, 1
	ldr	w4, [x21, 3592]
	bfi	w0, w4, 9, 1
	ldr	w4, [x22, 88]
	bfi	w0, w4, 8, 1
	ldr	w4, [x21, 3644]
	bfi	w0, w4, 3, 1
	ldr	w4, [x21, 3700]
	bfi	w0, w4, 15, 1
	ldr	w4, [x21, 3584]
	bfi	w0, w4, 14, 1
	ldr	w4, [x21, 3588]
	bfi	w0, w4, 13, 1
	ldr	w4, [x21, 3696]
	bfi	w0, w4, 12, 1
	ldr	w4, [x21, 3692]
	bfi	w0, w4, 11, 1
	ldr	w4, [x21, 3688]
	bfi	w0, w4, 10, 1
	bfi	w0, w1, 18, 1
	str	w0, [x19, 60]
	ldr	w0, [x21, 5692]
	bfi	w5, w0, 8, 1
	ldr	w0, [x21, 5696]
	bfi	w5, w0, 0, 8
	str	w5, [x19, 64]
	ldr	w0, [x21, 5700]
	bfi	w8, w0, 0, 1
	str	w8, [x19, 68]
	ldr	w0, [x21, 5864]
	bfi	w3, w0, 0, 1
	ldr	w0, [x21, 5860]
	bfi	w3, w0, 1, 1
	ldr	w0, [x21, 5856]
	bfi	w3, w0, 2, 1
	ldr	w0, [x21, 5852]
	bfi	w3, w0, 3, 1
	ldr	w0, [x21, 5848]
	bfi	w3, w0, 4, 1
	ldr	w0, [x21, 5844]
	bfi	w3, w0, 5, 1
	ldr	w0, [x21, 5840]
	bfi	w3, w0, 6, 1
	ldr	w0, [x21, 5800]
	ldr	x26, [x26]
	bfi	w3, w0, 7, 1
	str	w3, [x19, 72]
	ldr	w1, [x21, 5836]
	ldr	w0, [x21, 5832]
	bfi	w2, w1, 0, 1
	ldr	w1, [x21, 5828]
	bfi	w2, w0, 1, 1
	ldr	w0, [x21, 5824]
	bfi	w2, w1, 2, 1
	ldr	w1, [x21, 5792]
	bfi	w2, w0, 3, 1
	ldr	w0, [x21, 5796]
	bfi	w2, w1, 4, 1
	ldr	w1, [x21, 5820]
	bfi	w2, w0, 5, 1
	ldr	w0, [x21, 5816]
	bfi	w2, w1, 6, 1
	ldr	w1, [x21, 5804]
	bfi	w2, w0, 7, 1
	ldr	w0, [x21, 5812]
	bfi	w2, w1, 8, 1
	bfi	w2, w0, 9, 1
	ldr	w0, [x21, 5808]
	bfi	w2, w0, 10, 1
	str	w2, [x19, 76]
	ldr	w0, [x20, 8]
	ldr	w1, [x20, 60]
	cmp	w0, w9
	ldr	x2, [x20, 696]
	beq	.L161
	cbnz	w0, .L70
	mov	w0, 15
	mov	w24, 0
	bfi	w24, w0, 16, 6
	mov	w0, 31
	bfi	w24, w0, 0, 7
.L70:
	cbnz	w1, .L162
.L71:
	str	w24, [x26, 124]
.L72:
	mov	w2, 1
	mov	w0, 0
	bfi	w0, w2, 16, 6
	mov	w1, 43691
	bfi	w0, w2, 0, 7
	str	w0, [x23, 128]
	movk	w1, 0xaaaa, lsl 16
	mov	w7, 0
	ldr	w0, [x20, 172]
	mov	w5, 0
	mov	w6, 0
	mov	w4, 0
	add	x0, x0, 40
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 88]
	ldr	w0, [x20, 172]
	add	w0, w0, 2
	umull	x2, w0, w1
	lsr	x2, x2, 32
	lsr	w2, w2, 1
	lsl	w3, w2, 2
	sub	w2, w3, w2
	mov	w3, 0
	sub	w0, w0, w2
	add	x0, x0, 40
	ldr	w0, [x20, x0, lsl 2]
	str	w0, [x19, 92]
	mov	x0, x20
	ldr	w2, [x20, 172]
	add	w2, w2, 1
	umull	x1, w2, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 1
	lsl	w8, w1, 2
	sub	w1, w8, w1
	sub	w2, w2, w1
	add	x2, x2, 40
	ldr	w1, [x20, x2, lsl 2]
	str	w1, [x19, 96]
	ldr	w1, [x20, 200]
	str	w1, [x19, 100]
	ldr	w1, [x20, 72]
	str	w1, [x19, 104]
	ldr	w1, [x20, 76]
	str	w1, [x19, 108]
	ldr	w1, [x20, 80]
	str	w1, [x19, 112]
	ldr	w1, [x20, 84]
	bfi	w7, w1, 16, 16
	ldr	w1, [x20, 88]
	bfi	w7, w1, 0, 16
	str	w7, [x19, 124]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 92]
	str	w1, [x19, 128]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 100]
	str	w1, [x19, 132]
	ldr	w1, [x20, 108]
	bfi	w5, w1, 0, 16
	ldr	w1, [x20, 112]
	bfi	w5, w1, 16, 16
	str	w5, [x19, 136]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 116]
	str	w1, [x19, 140]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 124]
	str	w1, [x19, 144]
	ldr	w1, [x20, 132]
	bfi	w6, w1, 0, 16
	str	w6, [x19, 148]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 20
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 12]
	str	w1, [x19, 152]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 24
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 4]
	str	w1, [x19, 156]
	ldr	w1, [x20, 108]
	bfi	w4, w1, 16, 16
	ldr	w1, [x20, 112]
	bfi	w4, w1, 0, 16
	str	w4, [x19, 160]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 28
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 4]
	str	w1, [x19, 164]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 28
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 12]
	str	w1, [x19, 168]
	ldr	w1, [x20, 132]
	bfi	w3, w1, 16, 16
	ldr	w1, [x20, 136]
	bfi	w3, w1, 0, 16
	str	w3, [x19, 172]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 36
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 8]
	str	w1, [x19, 176]
	ldr	w1, [x20, 140]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 152]
	str	w1, [x19, 208]
	ldr	w1, [x20, 140]
	add	x1, x1, 36
	ldr	w1, [x20, x1, lsl 2]
	str	w1, [x19, 216]
	ldr	w1, [x20, 140]
	cmp	w1, wzr
	cset	x1, eq
	add	x1, x1, 36
	ldr	w1, [x20, x1, lsl 2]
	str	w1, [x19, 220]
	ldr	w1, [x20, 204]
	str	w1, [x19, 224]
	ldr	w1, [x20, 336]
	str	w1, [x19, 228]
	ldr	w1, [x20, 332]
	str	w1, [x19, 232]
	ldr	w1, [x25, 9624]
	bl	CfgStrFmt.isra.7
	ldr	w7, [x21, 4616]
	add	x0, x21, 2484
	ldr	w8, [x21, 4620]
	ldr	w9, [x21, 4624]
	ldr	w10, [x21, 4628]
	uxtb	w7, w7
	ldr	w5, [x21, 4608]
	uxtb	w8, w8
	ldr	w6, [x21, 4612]
	uxtb	w9, w9
	ldr	w3, [x21, 4600]
	uxtb	w10, w10
	ldr	w4, [x21, 4604]
	uxtb	w5, w5
	uxtb	w6, w6
	orr	w1, w10, w9
	orr	w2, w8, w7
	uxtb	w3, w3
	uxtb	w4, w4
	orr	w2, w2, w1
	orr	w1, w6, w5
	ldr	w11, [x21, 4852]
	orr	w2, w2, w1
	orr	w1, w4, w3
	orr	w2, w2, w1
	mov	w1, 0
	bfi	w1, w2, 24, 1
	ldr	w2, [x21, 4848]
	bfi	w1, w11, 23, 1
	bfi	w1, w2, 22, 1
	ldr	w2, [x21, 4844]
	bfi	w1, w2, 21, 1
	ldr	w2, [x21, 4840]
	bfi	w1, w2, 20, 1
	ldr	w2, [x21, 4836]
	bfi	w1, w2, 19, 1
	ldr	w2, [x21, 4832]
	bfi	w1, w2, 18, 1
	ldr	w2, [x21, 4828]
	bfi	w1, w2, 17, 1
	ldr	w2, [x21, 4824]
	bfi	w1, w2, 16, 1
	ldr	w2, [x21, 4660]
	bfi	w1, w2, 15, 1
	ldr	w2, [x21, 4656]
	bfi	w1, w2, 14, 1
	ldr	w2, [x21, 4652]
	bfi	w1, w2, 13, 1
	ldr	w2, [x21, 4648]
	bfi	w1, w2, 12, 1
	ldr	w2, [x21, 4644]
	bfi	w1, w2, 11, 1
	ldr	w2, [x21, 4640]
	bfi	w1, w2, 10, 1
	ldr	w2, [x21, 4636]
	bfi	w1, w2, 9, 1
	ldr	w2, [x21, 4632]
	bfi	w1, w2, 8, 1
	mov	w2, 0
	bfi	w1, w10, 7, 1
	bfi	w1, w9, 6, 1
	bfi	w1, w8, 5, 1
	bfi	w1, w7, 4, 1
	bfi	w1, w6, 3, 1
	bfi	w1, w5, 2, 1
	bfi	w1, w4, 1, 1
	bfi	w1, w3, 0, 1
	str	w1, [x19, 256]
	ldr	w1, [x21, 4676]
	ldr	w3, [x21, 4672]
	bfi	w2, w1, 24, 7
	ldr	w1, [x21, 4668]
	bfi	w2, w3, 16, 7
	ldr	w3, [x21, 4664]
	bfi	w2, w1, 8, 7
	mov	w1, 0
	bfi	w2, w3, 0, 7
	str	w2, [x19, 260]
	ldr	w2, [x21, 4692]
	ldr	w3, [x21, 4688]
	bfi	w1, w2, 24, 7
	ldr	w2, [x21, 4684]
	bfi	w1, w3, 16, 7
	mov	w3, 0
	bfi	w1, w2, 8, 7
	ldr	w2, [x21, 4680]
	bfi	w1, w2, 0, 7
	str	w1, [x19, 264]
	mov	w2, 0
	ldr	w1, [x21, 4728]
	bfi	w3, w1, 16, 10
	ldr	w1, [x21, 4696]
	bfi	w3, w1, 0, 10
	str	w3, [x19, 268]
	ldr	w1, [x21, 4732]
	ldr	w3, [x21, 4700]
	bfi	w2, w1, 16, 10
	mov	w1, 0
	bfi	w2, w3, 0, 10
	str	w2, [x19, 272]
	ldr	w2, [x21, 4736]
	ldr	w3, [x21, 4704]
	bfi	w1, w2, 16, 10
	mov	w2, 0
	bfi	w1, w3, 0, 10
	str	w1, [x19, 276]
	ldr	w1, [x21, 4740]
	ldr	w3, [x21, 4708]
	bfi	w2, w1, 16, 10
	mov	w1, 0
	bfi	w2, w3, 0, 10
	str	w2, [x19, 280]
	ldr	w2, [x21, 4744]
	ldr	w3, [x21, 4712]
	bfi	w1, w2, 16, 10
	mov	w2, 0
	bfi	w1, w3, 0, 10
	str	w1, [x19, 284]
	ldr	w1, [x21, 4748]
	ldr	w3, [x21, 4716]
	bfi	w2, w1, 16, 10
	mov	w1, 0
	bfi	w2, w3, 0, 10
	str	w2, [x19, 288]
	ldr	w2, [x21, 4752]
	ldr	w3, [x21, 4720]
	bfi	w1, w2, 16, 10
	mov	w2, 0
	bfi	w1, w3, 0, 10
	str	w1, [x19, 292]
	ldr	w1, [x21, 4756]
	ldr	w3, [x21, 4724]
	bfi	w2, w1, 16, 10
	mov	w1, 0
	bfi	w2, w3, 0, 10
	str	w2, [x19, 296]
	ldr	w2, [x21, 4792]
	ldr	w3, [x21, 4760]
	bfi	w1, w2, 16, 9
	mov	w2, 0
	bfi	w1, w3, 0, 9
	str	w1, [x19, 300]
	ldr	w1, [x21, 4796]
	ldr	w3, [x21, 4764]
	bfi	w2, w1, 16, 9
	mov	w1, 0
	bfi	w2, w3, 0, 9
	str	w2, [x19, 304]
	ldr	w2, [x21, 4800]
	ldr	w3, [x21, 4768]
	bfi	w1, w2, 16, 9
	mov	w2, 0
	bfi	w1, w3, 0, 9
	str	w1, [x19, 308]
	ldr	w1, [x21, 4804]
	ldr	w3, [x21, 4772]
	bfi	w2, w1, 16, 9
	mov	w1, 0
	bfi	w2, w3, 0, 9
	str	w2, [x19, 312]
	ldr	w2, [x21, 4808]
	ldr	w3, [x21, 4776]
	bfi	w1, w2, 16, 9
	mov	w2, 0
	bfi	w1, w3, 0, 9
	str	w1, [x19, 316]
	ldr	w1, [x21, 4812]
	ldr	w3, [x21, 4780]
	bfi	w2, w1, 16, 9
	mov	w1, 0
	bfi	w2, w3, 0, 9
	str	w2, [x19, 320]
	ldr	w2, [x21, 4816]
	ldr	w3, [x21, 4784]
	bfi	w1, w2, 16, 9
	mov	w2, 0
	bfi	w1, w3, 0, 9
	str	w1, [x19, 324]
	ldr	w1, [x21, 4820]
	ldr	w3, [x21, 4788]
	bfi	w2, w1, 16, 9
	mov	w1, 0
	bfi	w2, w3, 0, 9
	str	w2, [x19, 328]
	ldr	w2, [x22, 8]
	ldr	w3, [x0, 16]
	bfi	w1, w2, 16, 5
	ldr	w2, [x0, 392]
	bfi	w1, w3, 0, 8
	bfi	w1, w2, 24, 4
	str	w1, [x19, 332]
	mov	w1, 0
	mov	w2, 0
	ldr	w3, [x0, 656]
	bfi	w1, w3, 0, 3
	ldr	w3, [x0, 660]
	bfi	w1, w3, 3, 7
	ldr	w3, [x0, 664]
	bfi	w1, w3, 10, 3
	ldr	w3, [x0, 672]
	bfi	w1, w3, 18, 4
	ldr	w3, [x0, 680]
	bfi	w1, w3, 26, 4
	str	w1, [x19, 336]
	mov	w3, 0
	mov	w1, 0
	ldr	w4, [x0, 488]
	bfi	w2, w4, 0, 1
	ldr	w4, [x0, 492]
	bfi	w2, w4, 1, 3
	ldr	w4, [x0, 504]
	bfi	w2, w4, 15, 6
	ldr	w4, [x0, 508]
	bfi	w2, w4, 21, 5
	str	w2, [x19, 340]
	ldr	w2, [x0, 28]
	bfi	w3, w2, 16, 5
	ldr	w2, [x22, 12]
	bfi	w3, w2, 0, 8
	ldr	w2, [x0, 400]
	bfi	w3, w2, 24, 4
	str	w3, [x19, 344]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x0, 684]
	bfi	w1, w4, 0, 3
	ldr	w4, [x0, 688]
	bfi	w1, w4, 3, 7
	ldr	w4, [x0, 692]
	bfi	w1, w4, 10, 3
	ldr	w4, [x0, 700]
	bfi	w1, w4, 18, 4
	ldr	w4, [x0, 708]
	bfi	w1, w4, 26, 4
	str	w1, [x19, 348]
	ldr	w1, [x0, 512]
	bfi	w2, w1, 0, 1
	ldr	w1, [x0, 516]
	bfi	w2, w1, 1, 3
	ldr	w1, [x0, 528]
	bfi	w2, w1, 15, 6
	ldr	w1, [x0, 532]
	bfi	w2, w1, 21, 5
	str	w2, [x19, 352]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 24]
	bfi	w3, w4, 16, 5
	ldr	w4, [x22, 28]
	bfi	w3, w4, 0, 8
	ldr	w4, [x0, 416]
	bfi	w3, w4, 24, 4
	str	w3, [x19, 356]
	ldr	w3, [x0, 736]
	bfi	w1, w3, 0, 3
	ldr	w3, [x0, 740]
	bfi	w1, w3, 3, 7
	ldr	w3, [x0, 744]
	bfi	w1, w3, 10, 3
	ldr	w3, [x0, 752]
	bfi	w1, w3, 18, 4
	ldr	w3, [x0, 760]
	bfi	w1, w3, 26, 4
	str	w1, [x19, 360]
	mov	w3, 0
	mov	w1, 0
	ldr	w4, [x0, 560]
	bfi	w2, w4, 0, 1
	ldr	w4, [x0, 564]
	bfi	w2, w4, 1, 3
	ldr	w4, [x0, 576]
	bfi	w2, w4, 15, 6
	ldr	w4, [x0, 580]
	bfi	w2, w4, 21, 5
	str	w2, [x19, 364]
	ldr	w2, [x22, 60]
	bfi	w3, w2, 0, 8
	ldr	w2, [x22, 64]
	bfi	w3, w2, 16, 5
	ldr	w2, [x0, 424]
	bfi	w3, w2, 24, 4
	str	w3, [x19, 368]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x0, 308]
	bfi	w1, w4, 0, 3
	ldr	w4, [x0, 312]
	bfi	w1, w4, 3, 7
	ldr	w4, [x0, 316]
	bfi	w1, w4, 10, 3
	ldr	w4, [x0, 324]
	bfi	w1, w4, 18, 4
	ldr	w4, [x0, 332]
	bfi	w1, w4, 26, 4
	str	w1, [x19, 372]
	ldr	w1, [x0, 584]
	bfi	w2, w1, 0, 1
	ldr	w1, [x0, 588]
	bfi	w2, w1, 1, 3
	ldr	w1, [x0, 600]
	bfi	w2, w1, 15, 6
	ldr	w1, [x0, 604]
	bfi	w2, w1, 21, 5
	str	w2, [x19, 376]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 16]
	bfi	w3, w4, 16, 5
	ldr	w4, [x22, 20]
	bfi	w3, w4, 0, 8
	ldr	w4, [x0, 408]
	bfi	w3, w4, 24, 4
	str	w3, [x19, 380]
	ldr	w3, [x22, 68]
	bfi	w1, w3, 0, 3
	ldr	w3, [x0, 712]
	bfi	w1, w3, 3, 7
	ldr	w3, [x0, 716]
	bfi	w1, w3, 10, 3
	ldr	w3, [x0, 724]
	bfi	w1, w3, 18, 4
	ldr	w3, [x0, 732]
	bfi	w1, w3, 26, 4
	str	w1, [x19, 384]
	mov	w3, 0
	mov	w1, 0
	ldr	w4, [x0, 536]
	bfi	w2, w4, 0, 1
	ldr	w4, [x0, 540]
	bfi	w2, w4, 1, 3
	ldr	w4, [x0, 552]
	bfi	w2, w4, 15, 6
	ldr	w4, [x0, 556]
	bfi	w2, w4, 21, 5
	str	w2, [x19, 388]
	mov	w4, 0
	ldr	w2, [x0, 464]
	bfi	w3, w2, 0, 8
	ldr	w2, [x0, 468]
	bfi	w3, w2, 16, 5
	ldr	w2, [x0, 432]
	bfi	w3, w2, 24, 4
	str	w3, [x19, 392]
	mov	w2, 0
	ldr	w3, [x0, 336]
	bfi	w1, w3, 0, 3
	ldr	w3, [x0, 340]
	bfi	w1, w3, 3, 7
	ldr	w3, [x0, 344]
	bfi	w1, w3, 10, 3
	ldr	w3, [x0, 352]
	bfi	w1, w3, 18, 4
	ldr	w3, [x0, 360]
	bfi	w1, w3, 26, 4
	str	w1, [x19, 396]
	mov	w3, 0
	ldr	w1, [x0, 608]
	bfi	w2, w1, 0, 1
	ldr	w1, [x0, 612]
	bfi	w2, w1, 1, 3
	ldr	w1, [x0, 624]
	bfi	w2, w1, 15, 6
	ldr	w1, [x0, 628]
	bfi	w2, w1, 21, 5
	str	w2, [x19, 400]
	mov	w1, 0
	ldr	w2, [x0, 480]
	bfi	w4, w2, 0, 8
	ldr	w2, [x0, 484]
	bfi	w4, w2, 16, 5
	ldr	w2, [x0, 440]
	bfi	w4, w2, 24, 4
	str	w4, [x19, 404]
	ldr	w2, [x0, 364]
	bfi	w1, w2, 0, 3
	ldr	w2, [x0, 368]
	bfi	w1, w2, 3, 7
	ldr	w2, [x0, 372]
	bfi	w1, w2, 10, 3
	ldr	w2, [x0, 380]
	bfi	w1, w2, 18, 4
	ldr	w2, [x0, 388]
	bfi	w1, w2, 26, 4
	str	w1, [x19, 408]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x0, 632]
	bfi	w3, w4, 0, 1
	ldr	w4, [x0, 636]
	bfi	w3, w4, 1, 3
	ldr	w4, [x0, 648]
	bfi	w3, w4, 15, 6
	ldr	w4, [x0, 652]
	bfi	w3, w4, 21, 5
	str	w3, [x19, 412]
	ldr	w3, [x0, 60]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 56]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 52]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 72]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 68]
	bfi	w2, w3, 20, 4
	ldr	w3, [x22, 32]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 416]
	ldp	w2, w3, [x0, 136]
	bfi	w1, w3, 0, 4
	ldr	w3, [x22, 44]
	bfi	w1, w2, 4, 4
	ldr	w2, [x0, 156]
	bfi	w1, w3, 8, 4
	bfi	w1, w2, 16, 4
	ldp	w2, w3, [x0, 148]
	bfi	w1, w3, 20, 4
	mov	w3, 0
	bfi	w1, w2, 24, 4
	str	w1, [x19, 420]
	mov	w1, 0
	ldr	w2, [x0, 224]
	bfi	w1, w2, 0, 4
	ldr	w2, [x0, 220]
	bfi	w1, w2, 4, 4
	ldr	w2, [x22, 56]
	bfi	w1, w2, 8, 4
	ldr	w2, [x0, 240]
	bfi	w1, w2, 16, 4
	ldr	w2, [x0, 236]
	bfi	w1, w2, 20, 4
	ldr	w2, [x0, 232]
	bfi	w1, w2, 24, 4
	str	w1, [x19, 424]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x0, 80]
	bfi	w3, w4, 8, 4
	ldr	w4, [x0, 84]
	bfi	w3, w4, 4, 4
	ldr	w4, [x0, 88]
	bfi	w3, w4, 0, 4
	ldr	w4, [x0, 96]
	bfi	w3, w4, 24, 4
	ldr	w4, [x22, 36]
	bfi	w3, w4, 20, 4
	ldr	w4, [x0, 100]
	bfi	w3, w4, 16, 4
	str	w3, [x19, 428]
	ldr	w3, [x0, 164]
	bfi	w1, w3, 8, 4
	ldr	w3, [x22, 48]
	bfi	w1, w3, 4, 4
	ldr	w3, [x0, 168]
	bfi	w1, w3, 0, 4
	ldr	w3, [x0, 176]
	bfi	w1, w3, 24, 4
	ldr	w3, [x0, 180]
	bfi	w1, w3, 20, 4
	ldr	w3, [x0, 184]
	bfi	w1, w3, 16, 4
	str	w1, [x19, 432]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 248]
	bfi	w2, w4, 8, 4
	ldr	w4, [x0, 252]
	bfi	w2, w4, 4, 4
	ldr	w4, [x0, 256]
	bfi	w2, w4, 0, 4
	ldr	w4, [x0, 264]
	bfi	w2, w4, 24, 4
	ldr	w4, [x0, 268]
	bfi	w2, w4, 20, 4
	ldr	w4, [x0, 272]
	bfi	w2, w4, 16, 4
	str	w2, [x19, 436]
	ldr	w2, [x0, 108]
	bfi	w1, w2, 8, 4
	ldr	w2, [x0, 112]
	bfi	w1, w2, 4, 4
	ldr	w2, [x0, 116]
	bfi	w1, w2, 0, 4
	ldr	w2, [x0, 124]
	bfi	w1, w2, 24, 4
	ldr	w2, [x22, 40]
	bfi	w1, w2, 20, 4
	ldr	w2, [x0, 128]
	bfi	w1, w2, 16, 4
	str	w1, [x19, 440]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x0, 192]
	bfi	w3, w4, 8, 4
	ldr	w4, [x22, 52]
	bfi	w3, w4, 4, 4
	ldr	w4, [x0, 196]
	bfi	w3, w4, 0, 4
	ldr	w4, [x0, 204]
	bfi	w3, w4, 24, 4
	ldr	w4, [x0, 208]
	bfi	w3, w4, 20, 4
	ldr	w4, [x0, 212]
	bfi	w3, w4, 16, 4
	str	w3, [x19, 444]
	ldr	w3, [x0, 280]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 284]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 288]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 296]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 300]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 304]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 448]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x0, 764]
	bfi	w1, w4, 0, 4
	ldr	w4, [x0, 768]
	bfi	w1, w4, 4, 4
	ldr	w4, [x0, 772]
	bfi	w1, w4, 8, 4
	ldr	w4, [x0, 776]
	bfi	w1, w4, 12, 4
	ldr	w4, [x0, 780]
	bfi	w1, w4, 16, 4
	ldr	w4, [x0, 784]
	bfi	w1, w4, 20, 4
	str	w1, [x19, 452]
	ldr	w1, [x22, 72]
	bfi	w3, w1, 0, 12
	ldr	w1, [x22, 76]
	bfi	w3, w1, 12, 12
	ldr	w1, [x0, 788]
	bfi	w3, w1, 24, 8
	str	w3, [x19, 456]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 792]
	bfi	w2, w4, 0, 12
	ldr	w4, [x0, 796]
	bfi	w2, w4, 12, 12
	ldr	w4, [x0, 800]
	bfi	w2, w4, 24, 8
	str	w2, [x19, 460]
	ldr	w2, [x22, 80]
	bfi	w1, w2, 0, 12
	ldr	w2, [x0, 804]
	bfi	w1, w2, 12, 12
	ldr	w2, [x0, 808]
	bfi	w1, w2, 24, 8
	str	w1, [x19, 464]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x0, 812]
	bfi	w3, w4, 0, 8
	ldr	w4, [x0, 816]
	bfi	w3, w4, 8, 8
	ldr	w4, [x0, 820]
	bfi	w3, w4, 16, 8
	str	w3, [x19, 468]
	ldr	w3, [x21, 5572]
	bfi	w2, w3, 14, 1
	ldr	w3, [x21, 5576]
	bfi	w2, w3, 15, 1
	ldr	w3, [x20, 44]
	bfi	w2, w3, 28, 1
	ldr	w3, [x22, 5764]
	bfi	w2, w3, 20, 8
	str	w2, [x19, 480]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x21, 5592]
	bfi	w1, w4, 0, 8
	ldr	w4, [x21, 5588]
	bfi	w1, w4, 8, 8
	ldr	w4, [x21, 5584]
	bfi	w1, w4, 16, 8
	ldr	w4, [x21, 5580]
	bfi	w1, w4, 24, 8
	str	w1, [x19, 484]
	ldr	w1, [x0, 1280]
	bfi	w2, w1, 0, 1
	str	w2, [x19, 488]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x0, 1284]
	bfi	w3, w4, 0, 16
	str	w3, [x19, 492]
	ldr	w3, [x0, 1288]
	bfi	w1, w3, 0, 16
	str	w1, [x19, 496]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 1292]
	bfi	w2, w4, 0, 16
	str	w2, [x19, 500]
	ldr	w2, [x0, 1340]
	bfi	w1, w2, 16, 1
	ldr	w2, [x0, 1344]
	bfi	w1, w2, 0, 16
	str	w1, [x19, 504]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x0, 1296]
	bfi	w3, w4, 18, 9
	ldr	w4, [x0, 1300]
	bfi	w3, w4, 9, 9
	ldr	w4, [x0, 1304]
	bfi	w3, w4, 0, 9
	str	w3, [x19, 508]
	ldr	w3, [x0, 1308]
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1312]
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1316]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 512]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x0, 1320]
	bfi	w1, w4, 8, 4
	ldr	w4, [x0, 1324]
	bfi	w1, w4, 4, 4
	ldr	w4, [x0, 1328]
	bfi	w1, w4, 0, 4
	ldr	w4, [x0, 1336]
	bfi	w1, w4, 12, 8
	ldr	w4, [x0, 1332]
	bfi	w1, w4, 20, 8
	str	w1, [x19, 516]
	mov	w4, 0
	ldr	w1, [x21, 4524]
	bfi	w3, w1, 0, 8
	ldr	w1, [x21, 4520]
	bfi	w3, w1, 8, 8
	ldr	w1, [x21, 4516]
	bfi	w3, w1, 16, 8
	ldr	w1, [x21, 4512]
	bfi	w3, w1, 24, 8
	str	w3, [x19, 524]
	mov	w1, 0
	ldr	w3, [x0, 1348]
	bfi	w2, w3, 24, 8
	ldr	w3, [x0, 1352]
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1356]
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1360]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 528]
	mov	w3, 0
	ldr	w2, [x0, 1412]
	bfi	w1, w2, 0, 8
	ldr	w2, [x21, 4552]
	bfi	w1, w2, 17, 1
	str	w1, [x19, 532]
	mov	w1, 0
	ldr	w2, [x0, 1424]
	bfi	w4, w2, 0, 16
	ldr	w2, [x0, 1428]
	bfi	w4, w2, 16, 16
	str	w4, [x19, 536]
	ldr	w2, [x22, 492]
	bfi	w1, w2, 22, 9
	ldr	w2, [x22, 496]
	bfi	w1, w2, 17, 5
	ldr	w2, [x22, 500]
	bfi	w1, w2, 9, 8
	ldr	w2, [x22, 520]
	bfi	w1, w2, 0, 9
	str	w1, [x19, 540]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x22, 516]
	bfi	w3, w4, 8, 14
	ldr	w4, [x21, 4436]
	bfi	w3, w4, 0, 8
	str	w3, [x19, 544]
	ldr	w3, [x22, 504]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 508]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 512]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 548]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x21, 4444]
	bfi	w1, w4, 18, 1
	ldr	w4, [x21, 4448]
	bfi	w1, w4, 12, 2
	ldr	w4, [x21, 4456]
	bfi	w1, w4, 4, 4
	ldr	w4, [x21, 4460]
	bfi	w1, w4, 0, 4
	str	w1, [x19, 552]
	ldr	w1, [x21, 4464]
	bfi	w2, w1, 0, 10
	ldr	w1, [x21, 4468]
	bfi	w2, w1, 16, 9
	str	w2, [x19, 556]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x21, 4472]
	bfi	w3, w4, 0, 10
	ldr	w4, [x21, 4476]
	bfi	w3, w4, 16, 9
	str	w3, [x19, 560]
	ldr	w3, [x21, 4480]
	bfi	w1, w3, 0, 10
	ldr	w3, [x21, 4484]
	bfi	w1, w3, 16, 9
	str	w1, [x19, 564]
	mov	w3, 0
	mov	w1, 0
	ldr	w4, [x21, 4488]
	bfi	w2, w4, 0, 10
	ldr	w4, [x21, 4492]
	bfi	w2, w4, 16, 9
	str	w2, [x19, 568]
	ldr	w2, [x21, 4496]
	bfi	w3, w2, 0, 16
	str	w3, [x19, 572]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x21, 4528]
	bfi	w1, w4, 0, 13
	ldr	w4, [x21, 4532]
	bfi	w1, w4, 13, 1
	str	w1, [x19, 576]
	ldr	w1, [x21, 4536]
	bfi	w2, w1, 0, 18
	str	w2, [x19, 580]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x21, 4540]
	bfi	w3, w4, 0, 18
	str	w3, [x19, 584]
	ldr	w3, [x21, 4564]
	bfi	w2, w3, 16, 7
	ldr	w3, [x21, 4568]
	bfi	w2, w3, 23, 7
	str	w2, [x19, 588]
	mov	w2, 0
	mov	w3, 0
	ldr	w4, [x21, 4548]
	bfi	w1, w4, 12, 8
	ldr	w4, [x21, 4572]
	bfi	w1, w4, 8, 4
	ldr	w4, [x21, 4576]
	bfi	w1, w4, 0, 8
	ldr	w4, [x21, 4580]
	bfi	w1, w4, 20, 8
	ldr	w4, [x21, 4584]
	bfi	w1, w4, 28, 4
	str	w1, [x19, 592]
	ldr	w1, [x21, 4556]
	bfi	w2, w1, 0, 8
	ldr	w1, [x21, 4560]
	bfi	w2, w1, 8, 8
	ldr	w1, [x21, 4544]
	bfi	w2, w1, 16, 8
	str	w2, [x19, 596]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x21, 4588]
	bfi	w3, w4, 0, 8
	ldr	w4, [x21, 4592]
	bfi	w3, w4, 8, 8
	ldr	w4, [x21, 4596]
	bfi	w3, w4, 16, 16
	str	w3, [x19, 600]
	ldr	w3, [x0, 1364]
	bfi	w1, w3, 24, 8
	ldr	w3, [x0, 1368]
	bfi	w1, w3, 16, 8
	ldr	w3, [x0, 1372]
	bfi	w1, w3, 8, 8
	ldr	w3, [x0, 1376]
	bfi	w1, w3, 0, 8
	str	w1, [x19, 604]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 1380]
	bfi	w2, w4, 24, 8
	ldr	w4, [x0, 1384]
	bfi	w2, w4, 16, 8
	ldr	w4, [x0, 1388]
	bfi	w2, w4, 8, 8
	ldr	w4, [x0, 1392]
	bfi	w2, w4, 0, 8
	str	w2, [x19, 608]
	ldr	w2, [x0, 1396]
	bfi	w1, w2, 28, 4
	ldr	w2, [x0, 1400]
	bfi	w1, w2, 23, 5
	ldr	w2, [x0, 1404]
	ldr	w0, [x0, 1408]
	bfi	w1, w2, 14, 9
	bfi	w1, w0, 0, 14
	str	w1, [x19, 612]
	ldr	w2, [x20, 556]
	ldr	w1, [x21, 4956]
	ldr	w0, [x20, 552]
	bfi	w3, w2, 8, 6
	bfi	w3, w1, 16, 1
	bfi	w3, w0, 0, 6
	str	w3, [x19, 624]
	ldr	w0, [x20, 8]
	cbnz	w0, .L73
	ldr	w0, [x20, 20]
	mov	w1, 0
	ldr	w2, [x20, 544]
	lsr	w0, w0, 4
	udiv	w0, w2, w0
	bfi	w1, w0, 6, 25
.L74:
	ldr	w2, [x22, 100]
	add	x0, x21, 2484
	mov	w3, 0
	bfi	w1, w2, 0, 6
	str	w1, [x19, 628]
	mov	w1, 0
	ldr	w2, [x0, 988]
	bfi	w1, w2, 0, 16
	str	w1, [x19, 632]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x0, 960]
	bfi	w3, w4, 8, 6
	ldr	w4, [x0, 936]
	bfi	w3, w4, 16, 4
	ldr	w4, [x0, 964]
	bfi	w3, w4, 0, 6
	str	w3, [x19, 636]
	ldr	w3, [x0, 948]
	bfi	w1, w3, 8, 6
	ldr	w3, [x0, 928]
	bfi	w1, w3, 16, 4
	ldr	w3, [x0, 1264]
	bfi	w1, w3, 0, 6
	str	w1, [x19, 640]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 948]
	bfi	w2, w4, 8, 6
	ldr	w4, [x0, 932]
	bfi	w2, w4, 16, 4
	ldr	w4, [x0, 1252]
	bfi	w2, w4, 0, 6
	str	w2, [x19, 644]
	ldr	w2, [x0, 944]
	bfi	w1, w2, 8, 6
	ldr	w2, [x0, 924]
	bfi	w1, w2, 16, 4
	ldr	w2, [x0, 1260]
	bfi	w1, w2, 0, 6
	str	w1, [x19, 648]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 104]
	bfi	w3, w4, 8, 6
	ldr	w4, [x22, 84]
	bfi	w3, w4, 16, 4
	ldr	w4, [x0, 1248]
	bfi	w3, w4, 0, 6
	str	w3, [x19, 652]
	ldr	w3, [x0, 940]
	bfi	w1, w3, 16, 4
	ldr	w3, [x0, 956]
	bfi	w1, w3, 8, 6
	ldr	w3, [x0, 1256]
	bfi	w1, w3, 0, 6
	str	w1, [x19, 656]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x0, 968]
	bfi	w2, w4, 16, 4
	ldr	w4, [x0, 972]
	bfi	w2, w4, 20, 4
	ldr	w4, [x0, 976]
	bfi	w2, w4, 8, 6
	ldr	w4, [x0, 1268]
	bfi	w2, w4, 0, 6
	str	w2, [x19, 660]
	ldr	w2, [x22, 120]
	bfi	w1, w2, 24, 8
	ldr	w2, [x22, 116]
	bfi	w1, w2, 16, 8
	ldr	w2, [x22, 112]
	bfi	w1, w2, 8, 8
	ldr	w2, [x22, 108]
	bfi	w1, w2, 0, 8
	str	w1, [x19, 664]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 136]
	bfi	w3, w4, 24, 8
	ldr	w4, [x22, 132]
	bfi	w3, w4, 16, 8
	ldr	w4, [x22, 128]
	bfi	w3, w4, 8, 8
	ldr	w4, [x22, 124]
	bfi	w3, w4, 0, 8
	str	w3, [x19, 668]
	mov	w4, 0
	ldr	w3, [x22, 152]
	bfi	w1, w3, 24, 8
	ldr	w3, [x22, 148]
	bfi	w1, w3, 16, 8
	ldr	w3, [x22, 144]
	bfi	w1, w3, 8, 8
	ldr	w3, [x22, 140]
	bfi	w1, w3, 0, 8
	str	w1, [x19, 672]
	mov	w1, 0
	ldr	w3, [x22, 168]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 164]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 160]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 156]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 676]
	mov	w3, 0
	ldr	w2, [x0, 848]
	bfi	w1, w2, 0, 2
	ldr	w2, [x0, 852]
	bfi	w1, w2, 2, 2
	ldr	w2, [x0, 856]
	bfi	w1, w2, 4, 2
	ldr	w2, [x0, 860]
	bfi	w1, w2, 6, 2
	ldr	w2, [x0, 864]
	bfi	w1, w2, 8, 2
	ldr	w2, [x0, 868]
	bfi	w1, w2, 10, 2
	ldr	w2, [x0, 872]
	bfi	w1, w2, 12, 2
	ldr	w2, [x0, 876]
	bfi	w1, w2, 14, 2
	ldr	w2, [x0, 880]
	bfi	w1, w2, 16, 2
	ldr	w2, [x0, 884]
	bfi	w1, w2, 18, 2
	ldr	w2, [x0, 888]
	bfi	w1, w2, 20, 2
	ldr	w2, [x0, 892]
	bfi	w1, w2, 22, 2
	ldr	w2, [x0, 896]
	bfi	w1, w2, 24, 2
	ldr	w2, [x0, 900]
	bfi	w1, w2, 26, 2
	ldr	w2, [x0, 904]
	bfi	w1, w2, 28, 2
	ldr	w2, [x0, 908]
	bfi	w1, w2, 30, 2
	str	w1, [x19, 680]
	mov	w1, 0
	ldr	w2, [x0, 912]
	bfi	w4, w2, 0, 5
	str	w4, [x19, 684]
	ldr	w2, [x0, 980]
	bfi	w1, w2, 0, 4
	ldr	w2, [x0, 984]
	bfi	w1, w2, 4, 4
	str	w1, [x19, 688]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 172]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 692]
	ldr	w3, [x22, 176]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 696]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 180]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 700]
	ldr	w2, [x22, 184]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 704]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 188]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 708]
	ldr	w3, [x22, 192]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 712]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 196]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 716]
	ldr	w2, [x22, 200]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 720]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 204]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 724]
	ldr	w3, [x22, 208]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 728]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 212]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 732]
	ldr	w2, [x22, 216]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 736]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 220]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 740]
	ldr	w3, [x22, 224]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 744]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 228]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 748]
	ldr	w2, [x22, 232]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 752]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 236]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 756]
	ldr	w3, [x22, 240]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 760]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 244]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 764]
	ldr	w2, [x22, 248]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 768]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 252]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 772]
	ldr	w3, [x22, 256]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 776]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 260]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 780]
	ldr	w2, [x22, 264]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 784]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 268]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 788]
	ldr	w3, [x22, 272]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 792]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 276]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 796]
	ldr	w2, [x22, 280]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 800]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 284]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 804]
	ldr	w3, [x22, 288]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 808]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 292]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 812]
	ldr	w2, [x22, 296]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 816]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 300]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 820]
	ldr	w3, [x22, 304]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 824]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 308]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 828]
	ldr	w2, [x22, 312]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 832]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 316]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 836]
	ldr	w3, [x22, 320]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 840]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 324]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 844]
	ldr	w2, [x22, 328]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 848]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 332]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 852]
	ldr	w3, [x22, 336]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 856]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 340]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 860]
	ldr	w2, [x22, 344]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 864]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 348]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 868]
	ldr	w3, [x22, 352]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 872]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 356]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 876]
	ldr	w2, [x22, 360]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 880]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 364]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 884]
	ldr	w3, [x22, 368]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 888]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 372]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 892]
	ldr	w2, [x22, 376]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 896]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 380]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 900]
	ldr	w3, [x22, 384]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 904]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 388]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 908]
	ldr	w2, [x22, 392]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 912]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 396]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 916]
	ldr	w3, [x22, 400]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 920]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 404]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 924]
	ldr	w2, [x22, 408]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 928]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 412]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 932]
	ldr	w3, [x22, 416]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 936]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 420]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 940]
	ldr	w2, [x22, 424]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 944]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 428]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 948]
	ldr	w3, [x22, 432]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 952]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 436]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 956]
	ldr	w2, [x22, 440]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 960]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 444]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 964]
	ldr	w3, [x22, 448]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 968]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 452]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 972]
	ldr	w2, [x22, 456]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 976]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 460]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 980]
	ldr	w3, [x22, 464]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 984]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 468]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 988]
	ldr	w2, [x22, 472]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 992]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x22, 476]
	bfi	w3, w4, 0, 20
	str	w3, [x19, 996]
	ldr	w3, [x22, 480]
	bfi	w1, w3, 0, 20
	str	w1, [x19, 1000]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x22, 484]
	bfi	w2, w4, 0, 20
	str	w2, [x19, 1004]
	ldr	w2, [x22, 488]
	bfi	w1, w2, 0, 20
	str	w1, [x19, 1008]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x0, 1196]
	bfi	w3, w4, 8, 2
	ldr	w4, [x0, 1200]
	bfi	w3, w4, 12, 1
	ldr	w4, [x0, 1008]
	bfi	w3, w4, 0, 5
	str	w3, [x19, 1012]
	ldr	w3, [x0, 1004]
	bfi	w1, w3, 16, 4
	ldr	w3, [x0, 1184]
	bfi	w1, w3, 12, 4
	ldr	w3, [x0, 996]
	bfi	w1, w3, 9, 2
	ldr	w3, [x0, 1000]
	bfi	w1, w3, 8, 1
	ldr	w3, [x0, 992]
	bfi	w1, w3, 0, 6
	str	w1, [x19, 1016]
	ldr	w1, [x0, 1164]
	str	w1, [x19, 1020]
	ldr	w1, [x0, 1168]
	str	w1, [x19, 1024]
	ldr	w3, [x0, 1192]
	ldrh	w1, [x0, 1172]
	bfi	w1, w3, 21, 1
	ldr	w3, [x0, 1180]
	bfi	w1, w3, 18, 2
	ldr	w3, [x0, 1176]
	bfi	w1, w3, 16, 2
	str	w1, [x19, 1028]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x21, 5716]
	bfi	w2, w4, 4, 2
	ldr	w4, [x21, 5064]
	bfi	w2, w4, 1, 1
	ldr	w4, [x21, 5736]
	bfi	w2, w4, 2, 1
	str	w2, [x19, 1040]
	ldr	w2, [x21, 5416]
	bfi	w1, w2, 16, 16
	ldr	w2, [x21, 5420]
	bfi	w1, w2, 0, 16
	str	w1, [x19, 1044]
	mov	w1, 0
	mov	w2, 0
	ldr	w4, [x21, 5740]
	bfi	w3, w4, 6, 6
	ldr	w4, [x21, 5744]
	bfi	w3, w4, 0, 6
	str	w3, [x19, 1048]
	ldr	w3, [x21, 5400]
	bfi	w1, w3, 31, 1
	ldr	w3, [x21, 5404]
	bfi	w1, w3, 0, 17
	str	w1, [x19, 1052]
	mov	w1, 0
	mov	w3, 0
	ldr	w4, [x21, 5408]
	bfi	w2, w4, 16, 11
	ldr	w4, [x21, 5412]
	bfi	w2, w4, 0, 10
	str	w2, [x19, 1056]
	ldr	w2, [x21, 5512]
	bfi	w1, w2, 3, 1
	ldr	w2, [x21, 5516]
	bfi	w1, w2, 2, 1
	ldr	w2, [x21, 5520]
	bfi	w1, w2, 1, 1
	ldr	w2, [x21, 5508]
	bfi	w1, w2, 0, 1
	str	w1, [x19, 1060]
	mov	w2, 0
	mov	w1, 0
	ldr	w4, [x21, 5524]
	bfi	w3, w4, 4, 1
	str	w3, [x19, 1064]
	ldr	w3, [x21, 5168]
	bfi	w2, w3, 0, 1
	str	w2, [x19, 1068]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x21, 5176]
	bfi	w1, w4, 15, 1
	ldr	w4, [x21, 5180]
	bfi	w1, w4, 14, 1
	ldr	w4, [x21, 5184]
	bfi	w1, w4, 13, 1
	ldr	w4, [x21, 5188]
	bfi	w1, w4, 12, 1
	ldr	w4, [x21, 5192]
	bfi	w1, w4, 8, 4
	ldr	w4, [x21, 5196]
	bfi	w1, w4, 4, 4
	ldr	w4, [x21, 5200]
	bfi	w1, w4, 0, 4
	str	w1, [x19, 1072]
	ldr	w1, [x21, 5204]
	bfi	w3, w1, 0, 4
	str	w3, [x19, 1076]
	mov	w1, -1
	mov	w3, 0
	ldr	w4, [x21, 5216]
	bfi	w2, w4, 0, 8
	ldr	w4, [x21, 5212]
	bfi	w2, w4, 8, 8
	ldr	w4, [x21, 5208]
	bfi	w2, w4, 16, 8
	str	w2, [x19, 1080]
	ldr	w2, [x21, 5224]
	str	w1, [x19, 1088]
	str	w1, [x19, 1092]
	bfi	w3, w2, 0, 16
	str	w1, [x19, 1100]
	mov	w1, 7
	str	w3, [x19, 1084]
	mov	w3, 0
	str	w1, [x19, 1096]
	mov	w2, 0
	str	w1, [x19, 1104]
	mov	w1, 0
	ldr	w4, [x21, 5288]
	bfi	w1, w4, 3, 1
	ldr	w4, [x21, 5284]
	bfi	w1, w4, 2, 1
	ldr	w4, [x21, 5280]
	bfi	w1, w4, 1, 1
	mov	w4, 0
	orr	w1, w1, 1
	str	w1, [x19, 1108]
	ldr	w1, [x21, 5532]
	str	w1, [x19, 1112]
	ldr	w1, [x21, 5536]
	str	w1, [x19, 1116]
	ldr	w1, [x21, 5540]
	str	w1, [x19, 1120]
	ldr	w1, [x21, 5544]
	str	w1, [x19, 1124]
	ldr	w1, [x21, 5548]
	str	w1, [x19, 1128]
	ldr	w1, [x21, 5552]
	str	w1, [x19, 1132]
	ldr	w1, [x21, 5504]
	bfi	w3, w1, 0, 1
	str	w3, [x19, 1136]
	mov	w1, 0
	ldr	w3, [x21, 5768]
	bfi	w2, w3, 0, 8
	ldr	w3, [x21, 5772]
	bfi	w2, w3, 8, 8
	str	w2, [x19, 1140]
	mov	w3, 0
	ldr	w2, [x0, 824]
	bfi	w1, w2, 0, 16
	ldr	w2, [x0, 828]
	bfi	w1, w2, 16, 16
	str	w1, [x19, 1144]
	mov	w1, 0
	ldr	w2, [x0, 840]
	bfi	w4, w2, 16, 16
	str	w4, [x19, 1148]
	ldr	w2, [x0, 832]
	bfi	w1, w2, 0, 16
	ldr	w2, [x0, 836]
	bfi	w1, w2, 16, 16
	str	w1, [x19, 1152]
	mov	w2, 0
	mov	w1, 9729
	ldr	w0, [x0, 844]
	bfi	w3, w0, 0, 3
	str	w3, [x19, 1156]
	mov	w0, 513
	ldr	w4, [x20, 540]
	ldr	w3, [x21, 5472]
	cmp	w4, wzr
	csel	w0, w0, w1, eq
	bfi	w2, w3, 8, 3
	bfi	w2, w0, 16, 16
	str	w2, [x19, 1172]
	mov	w1, 0
	mov	w0, 16
	ldr	w2, [x20, 636]
	mov	w3, 0
	bfi	w1, w2, 0, 5
	ldr	w2, [x20, 640]
	bfi	w1, w2, 16, 16
	str	w1, [x19, 1176]
	ldr	w2, [x20, 636]
	ldr	w1, [x20, 676]
	sub	w2, w0, w2
	lsl	w2, w1, w2
	mov	w1, 0
	bfi	w3, w2, 0, 16
	str	w3, [x19, 1180]
	mov	w2, 0
	ldr	w3, [x22, 5868]
	bfi	w1, w3, 0, 5
	ldr	w3, [x22, 5872]
	bfi	w1, w3, 16, 16
	str	w1, [x19, 1216]
	ldr	w3, [x22, 5868]
	ldr	w1, [x22, 5864]
	sub	w0, w0, w3
	lsl	w0, w1, w0
	bfi	w2, w0, 0, 16
	str	w2, [x19, 1220]
	ldr	w0, [x20, 8]
	cmp	w0, 2
	beq	.L163
.L77:
	cbnz	w0, .L83
	ldr	w0, [x20, 636]
	mov	w1, 0
	sub	w3, w0, #1
	lsr	w2, w0, 8
	bfi	w1, w3, 16, 7
	sub	w2, w2, #1
	lsr	w0, w0, 16
	bfi	w1, w2, 8, 6
	sub	w0, w0, #1
	bfi	w1, w0, 0, 6
	str	w1, [x19, 1288]
	ldr	w0, [x20, 604]
	str	w0, [x19, 1256]
	ldr	w0, [x20, 608]
	str	w0, [x19, 1260]
	ldr	w0, [x20, 612]
	str	w0, [x19, 1264]
	ldr	w0, [x20, 616]
	str	w0, [x19, 1268]
	ldr	w0, [x20, 620]
	str	w0, [x19, 1272]
	ldr	w0, [x20, 624]
	str	w0, [x19, 1276]
	ldr	w0, [x20, 628]
	str	w0, [x19, 1280]
	ldr	w0, [x20, 632]
	str	w0, [x19, 1284]
.L83:
	ldr	w0, [x21, 5500]
	ubfiz	w0, w0, 1, 24
	str	w0, [x19, 1292]
	ldr	w0, [x20, 8]
	cmp	w0, 2
	beq	.L164
.L84:
	cbnz	w0, .L90
	ldr	w0, [x22, 5796]
	mov	w1, 0
	sub	w3, w0, #1
	lsr	w2, w0, 8
	bfi	w1, w3, 16, 7
	sub	w2, w2, #1
	lsr	w0, w0, 16
	bfi	w1, w2, 8, 6
	sub	w0, w0, #1
	bfi	w1, w0, 0, 6
	str	w1, [x19, 1328]
	ldr	w0, [x22, 5800]
	str	w0, [x19, 1296]
	ldr	w0, [x22, 5804]
	str	w0, [x19, 1300]
	ldr	w0, [x22, 5808]
	str	w0, [x19, 1304]
	ldr	w0, [x22, 5812]
	str	w0, [x19, 1308]
	ldr	w0, [x22, 5816]
	str	w0, [x19, 1312]
	ldr	w0, [x22, 5820]
	str	w0, [x19, 1316]
	ldr	w0, [x22, 5824]
	str	w0, [x19, 1320]
	ldr	w0, [x22, 5828]
	str	w0, [x19, 1324]
.L90:
	ldr	w2, [x20, 52]
	mov	w1, 0
	mov	w0, 0
	bfi	w1, w2, 0, 1
	str	w1, [x19, 1332]
	orr	w0, w0, 65536
	ldr	w1, [x21, 5880]
	str	w1, [x19, 1336]
	ldr	w1, [x20, 56]
	cmp	w1, wzr
	csel	w0, wzr, w0, eq
	orr	w0, w0, 256
	tbz	x0, 16, .L93
	ldr	w2, [x20, 348]
	ldr	w1, [x20, 344]
	str	w2, [x19, 1476]
	bfi	w0, w1, 0, 8
	ldr	w1, [x20, 352]
	str	w1, [x19, 1480]
	ldr	w1, [x20, 356]
	str	w1, [x19, 1484]
	ldr	w1, [x20, 360]
	str	w1, [x19, 1488]
	ldr	w1, [x20, 364]
	str	w1, [x19, 1492]
	ldr	w1, [x20, 368]
	str	w1, [x19, 1496]
	ldr	w1, [x20, 372]
	str	w1, [x19, 1500]
	ldr	w1, [x20, 376]
	str	w1, [x19, 1504]
	ldr	w1, [x20, 380]
	str	w1, [x19, 1508]
	ldr	w1, [x20, 384]
	str	w1, [x19, 1512]
	ldr	w1, [x20, 388]
	str	w1, [x19, 1516]
	ldr	w1, [x20, 392]
	str	w1, [x19, 1520]
	ldr	w1, [x20, 396]
	str	w1, [x19, 1524]
	ldr	w1, [x20, 400]
	str	w1, [x19, 1528]
	ldr	w1, [x20, 404]
	str	w1, [x19, 1532]
	ldr	w1, [x20, 408]
	str	w1, [x19, 1536]
	ldr	w1, [x20, 412]
	str	w1, [x19, 1540]
	ldr	w1, [x20, 416]
	str	w1, [x19, 1544]
	ldr	w1, [x20, 420]
	str	w1, [x19, 1548]
	ldr	w1, [x20, 424]
	str	w1, [x19, 1552]
	ldr	w1, [x20, 428]
	str	w1, [x19, 1556]
	ldr	w1, [x20, 432]
	str	w1, [x19, 1560]
	ldr	w1, [x20, 436]
	str	w1, [x19, 1564]
	ldr	w1, [x20, 440]
	str	w1, [x19, 1568]
	ldr	w1, [x20, 444]
	str	w1, [x19, 1572]
	ldr	w1, [x20, 448]
	str	w1, [x19, 1576]
	ldr	w1, [x20, 452]
	str	w1, [x19, 1580]
	ldr	w1, [x20, 456]
	str	w1, [x19, 1584]
	ldr	w1, [x20, 460]
	str	w1, [x19, 1588]
	ldr	w1, [x20, 464]
	str	w1, [x19, 1592]
	ldr	w1, [x20, 468]
	str	w1, [x19, 1596]
	ldr	w1, [x20, 472]
	str	w1, [x19, 1600]
	ldr	w1, [x20, 476]
	str	w1, [x19, 1604]
	ldr	w1, [x20, 480]
	str	w1, [x19, 1608]
	ldr	w1, [x20, 484]
	str	w1, [x19, 1612]
	ldr	w1, [x20, 488]
	str	w1, [x19, 1616]
	ldr	w1, [x20, 492]
	str	w1, [x19, 1620]
	ldr	w1, [x20, 496]
	str	w1, [x19, 1624]
	ldr	w1, [x20, 500]
	str	w1, [x19, 1628]
	ldr	w1, [x20, 504]
	str	w1, [x19, 1632]
	ldr	w1, [x20, 508]
	str	w1, [x19, 1636]
	ldr	w1, [x20, 512]
	str	w1, [x19, 1640]
	ldr	w1, [x20, 516]
	str	w1, [x19, 1644]
	ldr	w1, [x20, 520]
	str	w1, [x19, 1648]
	ldr	w1, [x20, 524]
	str	w1, [x19, 1652]
	ldr	w1, [x20, 528]
	str	w1, [x19, 1656]
	ldr	w1, [x20, 532]
	str	w1, [x19, 1660]
	ldr	w1, [x20, 536]
	str	w1, [x19, 1664]
.L93:
	str	w0, [x19, 1472]
	mov	w1, 0
	add	x0, x23, 61440
	mov	w6, 3
	ldr	w2, [x20, 204]
	mov	w5, 0
	str	w2, [x19, 1404]
	mov	w4, 0
	mov	w3, 9
	add	x26, x26, 61440
	ldr	w2, [x20, 208]
	str	w2, [x19, 1408]
	ldr	w2, [x20, 212]
	str	w2, [x19, 1412]
	ldr	w2, [x20, 216]
	str	w2, [x19, 1416]
	ldr	w2, [x20, 220]
	str	w2, [x19, 1420]
	ldr	w2, [x20, 224]
	str	w2, [x19, 1424]
	ldr	w2, [x20, 228]
	str	w2, [x19, 1428]
	ldr	w2, [x20, 232]
	str	w2, [x19, 1432]
	ldr	w2, [x20, 236]
	str	w2, [x19, 1436]
	ldr	w2, [x20, 240]
	str	w2, [x19, 1440]
	ldr	w2, [x20, 244]
	str	w2, [x19, 1444]
	ldr	w2, [x20, 248]
	str	w2, [x19, 1448]
	ldr	w2, [x20, 252]
	str	w2, [x19, 1452]
	ldr	w2, [x20, 256]
	str	w2, [x19, 1456]
	ldr	w2, [x20, 260]
	str	w2, [x19, 1460]
	ldr	w2, [x20, 264]
	str	w2, [x19, 1464]
	ldr	w2, [x20, 340]
	str	w2, [x19, 1468]
	ldr	w2, [x20, 268]
	str	w2, [x19, 1340]
	ldr	w2, [x20, 272]
	str	w2, [x19, 1344]
	ldr	w2, [x20, 276]
	str	w2, [x19, 1348]
	ldr	w2, [x20, 280]
	str	w2, [x19, 1352]
	ldr	w2, [x20, 284]
	str	w2, [x19, 1356]
	ldr	w2, [x20, 288]
	str	w2, [x19, 1360]
	ldr	w2, [x20, 292]
	str	w2, [x19, 1364]
	ldr	w2, [x20, 296]
	str	w2, [x19, 1368]
	ldr	w2, [x20, 300]
	str	w2, [x19, 1372]
	ldr	w2, [x20, 304]
	str	w2, [x19, 1376]
	ldr	w2, [x20, 308]
	str	w2, [x19, 1380]
	ldr	w2, [x20, 312]
	str	w2, [x19, 1384]
	ldr	w2, [x20, 316]
	str	w2, [x19, 1388]
	ldr	w2, [x20, 320]
	str	w2, [x19, 1392]
	ldr	w2, [x20, 324]
	str	w2, [x19, 1396]
	ldr	w2, [x20, 328]
	str	w2, [x19, 1400]
	mov	w2, 0
	ldr	w7, [x21, 5784]
	bfi	w1, w7, 0, 1
	ldr	w7, [x21, 5788]
	bfi	w1, w7, 3, 1
	bfi	w1, w6, 16, 4
	str	w1, [x0]
	str	w5, [x0, 8]
	mov	w1, 0
	str	w4, [x0, 16]
	bfi	w1, w3, 24, 8
	str	w2, [x0, 28]
	mov	w3, 7
	str	w2, [x0, 32]
	bfi	w1, w3, 16, 8
	mov	w2, 1
	mov	w3, 0
	and	w1, w1, -65281
	str	w3, [x0, 44]
	bfi	w1, w2, 0, 8
	str	w1, [x0, 1328]
	str	wzr, [x23, 4]
	ldr	w0, [x20, 580]
	str	w0, [x26, 520]
	ldr	w0, [x20, 580]
	str	w0, [x26, 524]
	ldr	w0, [x20, 588]
	str	w0, [x26, 752]
	ldr	w0, [x20, 584]
	str	w0, [x26, 756]
	ldr	w0, [x20, 588]
	str	w0, [x26, 772]
	ldr	w0, [x20, 584]
	str	w0, [x26, 776]
	mov	w0, 0
	str	w2, [x23, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L106:
	str	w23, [x19, 124]
	b	.L107
	.p2align 3
.L127:
	ldr	w0, [x19, 7312]
	and	w0, w0, -65537
	str	w0, [x19, 7312]
	b	.L128
	.p2align 3
.L109:
	ldr	w0, [x20, 20]
	mov	w1, 0
	ldr	w2, [x20, 544]
	lsr	w0, w0, 5
	udiv	w0, w2, w0
	bfi	w1, w0, 6, 25
	b	.L110
	.p2align 3
.L162:
	str	w24, [x2, 80]
	b	.L72
	.p2align 3
.L150:
	ldr	w0, [x20, 16]
	cmp	w0, 1919
	bhi	.L165
	cmp	w0, 719
	bhi	.L166
	mov	w0, 1
	str	w0, [x24, 6468]
	b	.L95
	.p2align 3
.L151:
	ldr	w1, [x20, 12]
	mov	w0, 5
	mov	w2, 7
	cmp	w1, wzr
	cset	w3, eq
	cmp	w1, 3
	csel	w0, w0, w2, ne
	str	w3, [x22, 5776]
	str	w0, [x22, 5768]
	cset	w3, ne
	str	w3, [x22, 5772]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	bne	.L101
.L152:
	mov	w1, 28
	str	w1, [x20, 548]
	str	w1, [x20, 552]
	str	w1, [x20, 556]
	str	wzr, [x24, 804]
	str	wzr, [x20, 24]
	str	wzr, [x21, 3628]
	str	wzr, [x21, 4540]
	str	wzr, [x21, 5048]
	str	wzr, [x21, 5300]
	str	wzr, [x21, 5304]
	str	wzr, [x21, 5692]
	str	wzr, [x21, 5720]
	b	.L101
	.p2align 3
.L163:
	ldr	w1, [x20, 640]
	ldr	x0, [x20, 696]
	cmp	w1, 31
	bhi	.L78
	ldr	w2, [x20, 644]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1184]
.L79:
	ldr	w1, [x20, 640]
	cmp	w1, 63
	bhi	.L80
	ldr	w2, [x20, 648]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1188]
.L81:
	ldr	w1, [x20, 640]
	cmp	w1, 64
	bls	.L82
	ldr	w2, [x20, 652]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1192]
.L82:
	ldr	w1, [x20, 656]
	str	w1, [x0, 1196]
	ldr	w1, [x20, 660]
	str	w1, [x0, 1200]
	ldr	w1, [x20, 664]
	str	w1, [x0, 1204]
	ldr	w1, [x20, 668]
	str	w1, [x0, 1208]
	ldr	w1, [x20, 672]
	str	w1, [x0, 1212]
	ldr	w0, [x20, 8]
	b	.L77
	.p2align 3
.L164:
	ldr	w1, [x22, 5872]
	ldr	x0, [x20, 696]
	cmp	w1, 31
	bhi	.L85
	ldr	w2, [x22, 5832]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1224]
.L86:
	ldr	w1, [x22, 5872]
	cmp	w1, 63
	bhi	.L87
	ldr	w2, [x22, 5836]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1228]
.L88:
	ldr	w1, [x22, 5872]
	cmp	w1, 64
	bls	.L89
	ldr	w2, [x22, 5840]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1232]
.L89:
	ldr	w1, [x22, 5844]
	str	w1, [x0, 1236]
	ldr	w1, [x22, 5848]
	str	w1, [x0, 1240]
	ldr	w1, [x22, 5852]
	str	w1, [x0, 1244]
	ldr	w1, [x22, 5856]
	str	w1, [x0, 1248]
	ldr	w1, [x22, 5860]
	str	w1, [x0, 1252]
	ldr	w0, [x20, 8]
	b	.L84
	.p2align 3
.L121:
	ldr	w0, [x22, 5832]
	str	w0, [x19, 6708]
	ldr	w0, [x22, 5872]
	cmp	w0, 63
	bls	.L167
.L123:
	ldr	w0, [x22, 5836]
	str	w0, [x19, 6712]
	b	.L124
	.p2align 3
.L114:
	ldr	w0, [x20, 644]
	str	w0, [x19, 6668]
	ldr	w0, [x20, 640]
	cmp	w0, 63
	bls	.L168
.L116:
	ldr	w0, [x20, 648]
	str	w0, [x19, 6672]
	b	.L117
	.p2align 3
.L73:
	ldr	w0, [x20, 20]
	mov	w1, 0
	ldr	w2, [x20, 544]
	lsr	w0, w0, 5
	udiv	w0, w2, w0
	bfi	w1, w0, 6, 25
	b	.L74
	.p2align 3
.L154:
	mov	w0, 19
	mov	w23, 0
	bfi	w23, w0, 16, 6
	mov	w0, 27
	bfi	w23, w0, 0, 7
	b	.L105
	.p2align 3
.L153:
	mov	w0, 3
	b	.L103
	.p2align 3
.L157:
	ldr	w0, [x20, 16]
	cmp	w0, 1919
	bhi	.L169
	cmp	w0, 719
	bhi	.L170
	mov	w0, 1
	str	w0, [x25, 6468]
	b	.L59
	.p2align 3
.L158:
	ldr	w0, [x20, 12]
	cmp	w0, wzr
	cset	w1, eq
	cmp	w0, 3
	str	w1, [x22, 5776]
	cset	w1, ne
	mov	w0, 5
	str	w1, [x22, 5772]
	mov	w1, 7
	csel	w0, w0, w1, ne
	str	w0, [x22, 5768]
	ldr	w0, [x20, 16]
	ldr	w1, [x20, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w1, wzr, 0, ls
	bne	.L65
.L159:
	mov	w1, 28
	str	w1, [x20, 548]
	str	w1, [x20, 552]
	str	w1, [x20, 556]
	str	wzr, [x25, 804]
	str	wzr, [x20, 24]
	str	wzr, [x21, 3628]
	str	wzr, [x21, 4540]
	str	wzr, [x21, 5048]
	str	wzr, [x21, 5300]
	str	wzr, [x21, 5304]
	str	wzr, [x21, 5692]
	str	wzr, [x21, 5720]
	b	.L65
	.p2align 3
.L161:
	mov	w0, 19
	mov	w24, 0
	bfi	w24, w0, 16, 6
	mov	w0, 27
	bfi	w24, w0, 0, 7
	cbz	w1, .L71
	b	.L162
	.p2align 3
.L160:
	mov	w0, 3
	b	.L68
	.p2align 3
.L80:
	ldr	w1, [x20, 648]
	str	w1, [x0, 1188]
	b	.L81
	.p2align 3
.L78:
	ldr	w1, [x20, 644]
	str	w1, [x0, 1184]
	b	.L79
	.p2align 3
.L87:
	ldr	w1, [x22, 5836]
	str	w1, [x0, 1228]
	b	.L88
	.p2align 3
.L85:
	ldr	w1, [x22, 5832]
	str	w1, [x0, 1224]
	b	.L86
	.p2align 3
.L165:
	mov	w0, 3
	str	w0, [x24, 6468]
	b	.L95
	.p2align 3
.L170:
	mov	w0, 2
	str	w0, [x25, 6468]
	b	.L59
	.p2align 3
.L169:
	mov	w0, 3
	str	w0, [x25, 6468]
	b	.L59
	.p2align 3
.L166:
	mov	w0, 2
	str	w0, [x24, 6468]
	b	.L95
	.size	DRV_VENC_HAL_V500R001_CfgReg, .-DRV_VENC_HAL_V500R001_CfgReg
	.align	3
.LC13:
	.xword	.LANCHOR1
	.align	3
.LC14:
	.xword	venc_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_Init
	.type	DRV_VENC_HAL_V500R001_Init, %function
DRV_VENC_HAL_V500R001_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x22, .LC15
	mov	x1, 63232
	mov	x0, 4173856768
	ldr	x2, [x22, 24]
	blr	x2
	ldr	x20, .LC16
	str	x0, [x20]
	cbz	x0, .L187
	ldr	x1, [x22, 40]
	mov	w0, 9984
	blr	x1
	str	x0, [x20, 8]
	ldr	x3, [x22]
	mov	x2, 9984
	mov	w1, 0
	blr	x3
	ldr	x19, [x20, 8]
	cbz	x19, .L186
	ldr	x3, [x22]
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
.L174:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L174
	add	x21, x19, 512
	add	x23, x19, 512
	mov	w2, 28
	mov	w1, 16
	mov	w0, 48
	add	x6, x19, 8192
	stp	w2, w1, [x21, 36]
	stp	wzr, wzr, [x21, 28]
	stp	w0, wzr, [x23, 44]
	stp	wzr, wzr, [x23, 52]
	mov	w5, 1
	mov	w3, 26
	str	wzr, [x19, 572]
	add	x0, x6, 504
	str	wzr, [x19, 576]
	mov	w1, 0
	str	wzr, [x19, 636]
	mov	w2, 7
	str	wzr, [x19, 640]
	.p2align 2
.L175:
	str	w1, [x0, 160]
	mov	w4, 1
	str	w1, [x0, 192]
	add	w1, w1, 5
	str	wzr, [x0]
	cmp	w1, 40
	str	w5, [x0, 32]
	add	x0, x0, 4
	str	w3, [x0, 60]
	str	w2, [x0, 92]
	str	w2, [x0, 124]
	str	wzr, [x0, 220]
	bne	.L175
	add	x2, x19, 4096
	mov	w3, 256
	add	x0, x2, 2484
	mov	w1, 32
	mov	w7, 4
	mov	w5, 128
	str	w4, [x0, 4]
	add	x30, x0, 256
	str	wzr, [x19, 6580]
	add	x8, x0, 512
	stp	w7, w3, [x0, 8]
	mov	w3, 8
	str	w5, [x0, 24]
	stp	w5, w7, [x0, 16]
	str	w1, [x0, 36]
	mov	w5, 3
	stp	w1, wzr, [x0, 44]
	stp	w5, w3, [x0, 28]
	str	w1, [x0, 448]
	add	x1, x0, 512
	str	w3, [x0, 40]
	mov	w3, 6
	stp	wzr, wzr, [x0, 52]
	str	w3, [x0, 452]
	add	x3, x0, 512
	str	wzr, [x0, 60]
	add	x7, x0, 512
	stp	wzr, wzr, [x0, 76]
	stp	wzr, wzr, [x0, 84]
	stp	wzr, wzr, [x0, 104]
	stp	wzr, wzr, [x0, 112]
	stp	wzr, wzr, [x0, 132]
	str	wzr, [x0, 140]
	add	x9, x0, 512
	stp	wzr, wzr, [x0, 160]
	str	wzr, [x0, 168]
	add	x10, x0, 512
	stp	wzr, wzr, [x0, 188]
	str	wzr, [x0, 196]
	add	x11, x0, 512
	stp	wzr, wzr, [x0, 216]
	str	wzr, [x0, 224]
	add	x12, x0, 768
	stp	wzr, wzr, [x0, 244]
	stp	wzr, wzr, [x0, 252]
	stp	wzr, wzr, [x30, 20]
	stp	wzr, wzr, [x30, 28]
	stp	w4, wzr, [x1, 144]
	stp	wzr, wzr, [x1, 152]
	stp	wzr, wzr, [x3, 160]
	stp	wzr, w4, [x3, 168]
	stp	wzr, wzr, [x7, 176]
	stp	wzr, wzr, [x7, 184]
	stp	wzr, wzr, [x8, 192]
	stp	wzr, wzr, [x8, 200]
	stp	wzr, wzr, [x9, 208]
	stp	wzr, wzr, [x9, 216]
	add	x13, x0, 768
	add	x14, x0, 768
	stp	w4, wzr, [x10, 224]
	stp	wzr, wzr, [x10, 232]
	stp	wzr, wzr, [x11, 240]
	stp	wzr, wzr, [x11, 248]
	stp	wzr, wzr, [x12]
	stp	wzr, wzr, [x12, 8]
	add	x15, x0, 768
	add	x16, x0, 256
	stp	wzr, wzr, [x13, 16]
	stp	wzr, wzr, [x13, 24]
	stp	wzr, wzr, [x14, 32]
	stp	wzr, wzr, [x14, 40]
	stp	wzr, wzr, [x15, 48]
	stp	wzr, wzr, [x15, 56]
	str	wzr, [x0, 832]
	add	x17, x0, 512
	stp	wzr, wzr, [x16, 64]
	stp	wzr, wzr, [x16, 72]
	add	x18, x0, 512
	str	wzr, [x0, 316]
	str	wzr, [x0, 312]
	add	x20, x0, 512
	str	w4, [x0, 308]
	add	x5, x2, 3396
	str	wzr, [x0, 836]
	add	x3, x2, 3332
	str	wzr, [x0, 840]
	str	wzr, [x0, 612]
	str	wzr, [x0, 608]
	str	wzr, [x0, 580]
	str	wzr, [x0, 576]
	stp	wzr, wzr, [x17, 40]
	stp	wzr, wzr, [x17, 48]
	stp	wzr, wzr, [x18, 16]
	stp	wzr, wzr, [x18, 24]
	stp	wzr, wzr, [x20, -8]
	stp	wzr, wzr, [x20]
	str	wzr, [x0, 492]
	str	wzr, [x0, 488]
	str	wzr, [x0, 468]
	str	wzr, [x0, 464]
	str	wzr, [x0, 432]
	str	wzr, [x0, 424]
	str	wzr, [x0, 416]
	str	wzr, [x0, 408]
	str	wzr, [x0, 400]
	str	wzr, [x0, 392]
	str	wzr, [x0, 360]
	str	wzr, [x0, 352]
	str	wzr, [x0, 344]
	str	wzr, [x0, 340]
	str	wzr, [x0, 336]
	str	wzr, [x0, 624]
	str	wzr, [x0, 628]
	str	wzr, [x0, 844]
	.p2align 2
.L176:
	str	w4, [x3], 4
	mov	w1, 1
	cmp	x3, x5
	bne	.L176
	add	x0, x2, 3332
	mov	w3, 48
	mov	w4, 4
	mov	w7, 8
	mov	w8, 3
	mov	w9, 2
	stp	wzr, w3, [x0, 92]
	stp	w3, w3, [x0, 100]
	add	x3, x0, 256
	mov	w12, 10
	stp	w7, w9, [x0, 64]
	stp	w12, w4, [x0, 116]
	str	w4, [x0, 164]
	mov	w5, 12
	stp	w8, wzr, [x0, 72]
	stp	w5, w5, [x0, 132]
	stp	wzr, wzr, [x0, 80]
	str	w7, [x0, 124]
	mov	w14, 21845
	str	wzr, [x0, 260]
	mov	w10, 50
	str	wzr, [x0, 292]
	mov	w15, 60
	str	wzr, [x0, 296]
	mov	w13, 160
	str	wzr, [x0, 304]
	mov	w11, 5
	str	wzr, [x0, 308]
	mov	w16, 100
	str	wzr, [x0, 356]
	stp	w12, w12, [x3, 144]
	stp	wzr, w12, [x3, 152]
	mov	w3, 51
	str	w3, [x0, 108]
	str	w3, [x0, 128]
	mov	w3, 44
	str	w12, [x0, 416]
	str	w3, [x0, 112]
	mov	w3, 2592
	str	wzr, [x0, 424]
	str	w3, [x0, 140]
	add	x3, x2, 3760
	stp	w4, w4, [x0, 168]
	stp	w4, w14, [x0, 176]
	stp	w14, w10, [x0, 184]
	add	x14, x0, 256
	str	w15, [x0, 192]
	stp	w10, w15, [x0, 220]
	str	w13, [x0, 212]
	str	w13, [x0, 244]
	stp	w1, w1, [x14, 8]
	stp	wzr, w1, [x14, 16]
	mov	w14, 70
	str	w14, [x0, 196]
	str	w14, [x0, 228]
	mov	w14, 80
	str	w14, [x0, 200]
	str	w14, [x0, 232]
	mov	w14, 120
	str	w14, [x0, 204]
	str	w14, [x0, 236]
	mov	w14, 140
	str	w4, [x0, 336]
	stp	wzr, w4, [x0, 152]
	str	w14, [x0, 208]
	str	w14, [x0, 240]
	mov	w14, 180
	str	w1, [x0, 280]
	str	w14, [x0, 216]
	str	w14, [x0, 248]
	mov	w14, 20
	str	wzr, [x0, 372]
	str	wzr, [x0, 376]
	stp	w11, wzr, [x0, 144]
	str	wzr, [x0, 312]
	str	wzr, [x0, 300]
	str	wzr, [x0, 256]
	str	wzr, [x0, 252]
	str	wzr, [x0, 360]
	str	wzr, [x0, 364]
	str	wzr, [x0, 368]
	mov	w0, 6
	str	wzr, [x19, 7856]
	str	w0, [x3, 52]
	stp	w4, w5, [x3, 28]
	stp	w9, w4, [x3, 44]
	stp	wzr, w14, [x3, 4]
	str	w10, [x3, 12]
	mov	w10, 15
	stp	w5, w7, [x3, 20]
	stp	w7, w4, [x3, 36]
	stp	wzr, wzr, [x3, 64]
	stp	wzr, wzr, [x3, 88]
	stp	wzr, wzr, [x3, 96]
	stp	wzr, wzr, [x3, 104]
	stp	wzr, wzr, [x3, 112]
	stp	wzr, wzr, [x3, 120]
	mov	w5, 150
	str	w5, [x3, 16]
	stp	wzr, wzr, [x3, 128]
	str	wzr, [x2, 4500]
	mov	w5, 511
	str	wzr, [x2, 4504]
	stp	w8, w14, [x3, 56]
	str	w5, [x2, 4508]
	mov	w5, 131
	str	w10, [x2, 4512]
	str	w10, [x2, 4516]
	str	w11, [x2, 4520]
	str	w11, [x2, 4524]
	stp	w5, w13, [x3, 72]
	str	w16, [x3, 80]
	mov	w5, 127
	str	w5, [x3, 84]
	mov	w13, 16
	str	w0, [x2, 4460]
	add	x5, x6, 1620
	add	x0, x6, 760
	str	w9, [x2, 4456]
	mov	w6, 24
	str	wzr, [x2, 4428]
	str	w6, [x2, 4488]
	add	x20, x0, 768
	str	w6, [x2, 4492]
	mov	w6, 767
	str	wzr, [x2, 4432]
	add	x21, x0, 768
	str	w8, [x2, 4436]
	add	x23, x0, 256
	str	wzr, [x2, 4440]
	add	x24, x0, 256
	str	w1, [x2, 4448]
	add	x25, x0, 256
	str	wzr, [x2, 4452]
	add	x26, x0, 256
	str	w7, [x2, 4464]
	add	x30, x0, 256
	str	w7, [x2, 4468]
	add	x17, x0, 256
	str	w7, [x2, 4472]
	add	x18, x0, 256
	str	w7, [x2, 4476]
	str	w13, [x2, 4480]
	str	w13, [x2, 4484]
	str	wzr, [x2, 4496]
	str	wzr, [x2, 4528]
	str	wzr, [x2, 4532]
	str	w15, [x2, 4544]
	add	x15, x0, 256
	str	w14, [x2, 4596]
	str	wzr, [x2, 4536]
	str	wzr, [x2, 4540]
	str	wzr, [x2, 4548]
	str	wzr, [x2, 4552]
	str	wzr, [x2, 4556]
	str	w11, [x2, 4560]
	str	wzr, [x2, 4564]
	str	wzr, [x2, 4568]
	str	wzr, [x2, 4572]
	str	wzr, [x2, 4576]
	str	w7, [x2, 4580]
	str	w7, [x2, 4584]
	str	wzr, [x2, 4588]
	str	wzr, [x2, 4592]
	stp	w12, w14, [x3, 136]
	stp	w1, w6, [x3, 144]
	stp	wzr, wzr, [x0, 32]
	stp	wzr, w1, [x0, 40]
	str	w1, [x0, 48]
	mov	w3, 7
	stp	wzr, wzr, [x0, 60]
	stp	wzr, wzr, [x0, 72]
	stp	w1, w1, [x0, 80]
	stp	w1, wzr, [x0, 88]
	stp	w3, w3, [x0, 184]
	str	wzr, [x0, 96]
	add	x12, x0, 256
	str	wzr, [x0, 52]
	add	x14, x0, 256
	stp	wzr, wzr, [x0, 144]
	stp	wzr, wzr, [x0, 152]
	stp	wzr, wzr, [x0, 160]
	stp	wzr, wzr, [x0, 176]
	stp	wzr, w1, [x0, 204]
	stp	wzr, wzr, [x0, 212]
	stp	wzr, wzr, [x0, 220]
	stp	wzr, w1, [x0, 228]
	stp	wzr, wzr, [x0, 236]
	str	wzr, [x0, 244]
	mov	w6, -1
	str	wzr, [x0, 672]
	stp	wzr, wzr, [x20, 4]
	stp	wzr, wzr, [x20, 12]
	stp	wzr, wzr, [x21, 20]
	stp	wzr, wzr, [x21, 28]
	stp	w1, wzr, [x0, 248]
	str	wzr, [x0, 256]
	add	x20, x0, 512
	str	wzr, [x0, 260]
	add	x21, x0, 512
	str	w8, [x0, 272]
	str	wzr, [x0, 276]
	str	w1, [x0, 280]
	stp	wzr, wzr, [x23, 56]
	stp	wzr, wzr, [x23, 64]
	stp	wzr, wzr, [x24, 72]
	stp	wzr, wzr, [x24, 80]
	stp	wzr, wzr, [x25, 88]
	stp	wzr, wzr, [x25, 96]
	stp	wzr, wzr, [x26, 104]
	stp	wzr, wzr, [x26, 112]
	stp	wzr, w6, [x30, 128]
	stp	wzr, wzr, [x30, 120]
	stp	w3, w6, [x12, 136]
	stp	w3, w6, [x12, 144]
	stp	w3, w6, [x14, 152]
	stp	w3, w1, [x14, 160]
	stp	w1, w1, [x15, 168]
	stp	w1, wzr, [x15, 176]
	stp	wzr, wzr, [x17, 184]
	stp	wzr, w16, [x17, 192]
	stp	w10, w10, [x18, 212]
	stp	w11, w11, [x18, 204]
	str	w1, [x0, 476]
	add	x23, x0, 512
	str	w1, [x0, 480]
	add	x24, x0, 512
	str	wzr, [x0, 484]
	mov	w6, 500
	stp	wzr, wzr, [x20, -8]
	stp	wzr, wzr, [x20]
	str	wzr, [x0, 520]
	add	x25, x0, 512
	str	w1, [x0, 524]
	add	x26, x0, 768
	stp	wzr, wzr, [x21, 32]
	stp	wzr, wzr, [x21, 40]
	str	w10, [x0, 560]
	str	w9, [x0, 848]
	str	w9, [x0, 852]
	str	w6, [x0, 456]
	mov	w6, 255
	stp	wzr, w1, [x0, 192]
	str	w10, [x0, 564]
	stp	wzr, w9, [x23, 76]
	stp	wzr, w8, [x23, 84]
	str	w8, [x0, 604]
	str	wzr, [x0, 608]
	str	wzr, [x0, 612]
	str	wzr, [x0, 640]
	str	wzr, [x0, 644]
	stp	wzr, wzr, [x24, 140]
	stp	wzr, wzr, [x24, 148]
	str	wzr, [x0, 668]
	stp	wzr, wzr, [x25, 164]
	stp	wzr, wzr, [x25, 172]
	str	wzr, [x0, 692]
	str	wzr, [x0, 696]
	str	wzr, [x0, 708]
	str	wzr, [x0, 712]
	str	wzr, [x0, 720]
	str	wzr, [x0, 804]
	stp	wzr, wzr, [x26, 52]
	stp	wzr, wzr, [x26, 60]
	str	wzr, [x0, 836]
	str	wzr, [x0, 840]
	str	wzr, [x0, 844]
	str	wzr, [x0, 540]
	str	w8, [x0, 496]
	str	w9, [x0, 616]
	str	w6, [x0, 724]
	str	w6, [x0, 732]
	str	w1, [x0, 648]
	str	wzr, [x0, 716]
	str	wzr, [x0, 728]
	str	wzr, [x0, 736]
	str	w1, [x0, 268]
	str	w1, [x0, 264]
	str	w1, [x0, 200]
	str	w1, [x0, 100]
	mov	w0, 171
	str	wzr, [x19, 9812]
	stp	wzr, w10, [x5, 20]
	stp	wzr, wzr, [x5, 4]
	stp	wzr, wzr, [x5, 12]
	stp	wzr, wzr, [x5, 32]
	str	wzr, [x5, 44]
	mov	w10, 9
	str	w10, [x5, 28]
	add	x5, x19, 704
	str	w0, [x19, 9864]
	mov	w0, 85
	str	w0, [x19, 9868]
	mov	w0, 23040
	movk	w0, 0x262, lsl 16
	str	w3, [x2, 5780]
	str	w8, [x2, 5776]
	str	wzr, [x2, 5784]
	str	w1, [x2, 5788]
	str	wzr, [x2, 5796]
	str	wzr, [x2, 5804]
	str	wzr, [x2, 5808]
	str	wzr, [x2, 5812]
	str	wzr, [x2, 5792]
	str	w0, [x2, 5876]
	mov	w0, 2304
	str	w9, [x2, 5868]
	movk	w0, 0x3d, lsl 16
	str	wzr, [x2, 5800]
	mov	w9, 64
	str	w0, [x2, 5880]
	add	x0, x19, 788
	str	wzr, [x2, 5816]
	str	wzr, [x2, 5820]
	str	wzr, [x2, 5824]
	str	wzr, [x2, 5828]
	str	wzr, [x2, 5832]
	str	wzr, [x2, 5836]
	str	wzr, [x2, 5840]
	str	wzr, [x2, 5844]
	str	wzr, [x2, 5848]
	str	wzr, [x2, 5852]
	str	wzr, [x2, 5856]
	str	wzr, [x2, 5860]
	str	wzr, [x2, 5864]
	str	w1, [x2, 5872]
	str	w1, [x5, 4]
	str	w1, [x19, 704]
	stp	w8, w9, [x5, 8]
	stp	w4, w13, [x5, 16]
	stp	w4, w13, [x5, 24]
	stp	w13, w4, [x5, 60]
	stp	wzr, wzr, [x5, 44]
	stp	wzr, wzr, [x5, 52]
	stp	w1, wzr, [x5, 68]
	mov	w9, 11
	stp	wzr, wzr, [x5, 76]
	stp	w10, w9, [x0, 56]
	mov	w9, 14
	str	w4, [x0, 16]
	stp	wzr, wzr, [x0, 24]
	stp	wzr, w3, [x0, 40]
	stp	w3, w3, [x0, 48]
	stp	w6, w6, [x0, 76]
	str	w6, [x0, 84]
	mov	w3, 35
	str	w9, [x0, 64]
	mov	w6, 25
	str	w3, [x0, 20]
	mov	w9, 18
	str	w6, [x0, 72]
	add	x3, x19, 1196
	stp	wzr, wzr, [x0, 32]
	str	w9, [x0, 68]
	str	w4, [x19, 788]
	mov	w4, 96
	stp	w1, w1, [x0, 4]
	mov	x0, x3
	mov	w3, 378
	str	w4, [x0, 28]
	str	w1, [x19, 1196]
	stp	w8, w6, [x0, 4]
	str	w3, [x0, 24]
	mov	w3, 128
	stp	w8, w7, [x0, 16]
	str	w3, [x0, 12]
	add	x3, x19, 876
	ldr	x4, .LC17
	add	x0, x4, 164
	add	x6, x4, 320
	b	.L179
	.p2align 3
.L177:
	ldr	w1, [x0], 4
.L179:
	str	w1, [x3], 4
	cmp	x0, x6
	bne	.L177
	add	x0, x4, 324
	add	x1, x19, 1036
	add	x4, x4, 480
	mov	w3, 1
	b	.L178
	.p2align 3
.L193:
	ldr	w3, [x0], 4
.L178:
	str	w3, [x1], 4
	cmp	x0, x4
	bne	.L193
	add	x19, x19, 1228
	mov	w0, 7
	add	x20, x2, 2372
	mov	x25, x19
	mov	w24, 3
	mov	w26, 96
	mov	w21, 4
	mov	w23, 64
	str	w0, [x5, 5768]
	str	wzr, [x5, 5772]
	str	wzr, [x5, 5776]
.L182:
	ldr	x3, [x22]
	mov	x2, 2620
	mov	w1, 0
	mov	x0, x25
	blr	x3
	mov	x2, x25
	mov	x1, x25
	mov	x0, x25
	mov	w4, 0
	mov	w3, 1
	mov	w11, 20
	mov	w10, 8
	mov	w5, 32
	mov	w9, 384
	mov	w8, 2
	mov	w7, 16
	mov	w6, 35
	.p2align 2
.L181:
	str	w24, [x0, 8]
	add	x0, x0, 84
	str	w26, [x1, 2488]
	add	x30, x1, 2304
	str	w21, [x2, 420]
	add	x2, x2, 408
	str	w3, [x0, -80]
	add	x1, x1, 32
	str	w23, [x0, -72]
	add	w4, w4, 1
	str	wzr, [x0, -40]
	cmp	w4, 5
	str	wzr, [x0, -12]
	stp	w24, w11, [x30, 160]
	stp	w23, w21, [x30, 168]
	str	w10, [x1, 2448]
	stp	w21, w5, [x0, -60]
	str	wzr, [x0, -28]
	str	wzr, [x0, -8]
	stp	w3, wzr, [x2, 20]
	str	w9, [x1, 2452]
	str	w3, [x0, -84]
	str	wzr, [x0, -52]
	stp	w5, w21, [x0, -24]
	str	wzr, [x0, -4]
	str	w8, [x1, 2428]
	stp	w21, w7, [x0, -68]
	str	w3, [x0, -16]
	str	w3, [x2, 16]
	str	w6, [x2, 32]
	bne	.L181
	add	x25, x25, 2620
	cmp	x25, x20
	bne	.L182
	mov	w7, 1
	mov	w8, 0
	mov	w2, w7
	mov	w6, 128
	mov	w0, 64
	mov	w15, 6
	mov	w3, 32
	mov	w5, 2
	mov	w14, 15
	mov	w9, 4
	mov	w13, 38
	mov	w1, 3
	mov	w12, 256
	mov	w11, 34
	mov	w10, 16
.L183:
	add	x21, x19, 2560
	str	w6, [x19, 28]
	stp	wzr, wzr, [x19]
	stp	w2, w6, [x19, 8]
	str	w6, [x19, 60]
	cmp	w7, 1
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
	str	w15, [x19, 828]
	str	wzr, [x19, 836]
	str	w4, [x19, 1236]
	str	w13, [x19, 2072]
	stp	w5, w14, [x21, 32]
	stp	w0, w5, [x21, 40]
	str	w9, [x19, 2608]
	cbz	w8, .L194
	add	x16, x19, 256
	str	w2, [x19, 336]
	add	x17, x19, 256
	stp	w9, w10, [x16, 96]
	stp	w1, w3, [x16, 104]
	str	w1, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w1, w3, [x17, 136]
	stp	w1, w2, [x17, 144]
	str	wzr, [x19, 412]
	str	w11, [x19, 416]
	str	w2, [x19, 2064]
	str	w5, [x19, 2588]
	str	w12, [x19, 2612]
	bhi	.L186
.L185:
	add	w8, w8, 1
	add	x19, x19, 2620
	add	w7, w7, 1
	b	.L183
	.p2align 3
.L186:
	mov	w0, 0
.L172:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L187:
	mov	w0, -1
	b	.L172
.L194:
	add	x18, x19, 256
	str	w2, [x19, 336]
	add	x20, x19, 256
	stp	w9, w10, [x18, 96]
	stp	w1, w3, [x18, 104]
	str	w9, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w9, w3, [x20, 136]
	stp	w1, w2, [x20, 144]
	str	wzr, [x19, 412]
	str	w11, [x19, 416]
	str	w2, [x19, 2064]
	str	w5, [x19, 2588]
	str	w12, [x19, 2612]
	b	.L185
	.size	DRV_VENC_HAL_V500R001_Init, .-DRV_VENC_HAL_V500R001_Init
	.align	3
.LC15:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LANCHOR1
	.align	3
.LC17:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_Deinit
	.type	DRV_VENC_HAL_V500R001_Deinit, %function
DRV_VENC_HAL_V500R001_Deinit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC20
	ldr	x19, .LC21
	ldr	x1, [x20, 32]
	ldr	x0, [x19]
	blr	x1
	ldr	x0, [x19, 8]
	ldr	x1, [x20, 48]
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_Deinit, .-DRV_VENC_HAL_V500R001_Deinit
	.align	3
.LC20:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC21:
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
