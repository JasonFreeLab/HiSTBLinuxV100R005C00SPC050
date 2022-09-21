#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"postprocess.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	PostPro_GetRepairStratage
	.type	PostPro_GetRepairStratage, %function
PostPro_GetRepairStratage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	w19, .L4
	cmp	w19, 15
	beq	.L4
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4:
	ldrb	w0, [x20, 3]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetRepairStratage, .-PostPro_GetRepairStratage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Mpeg4
	.type	PostPro_CopyYuv_Mpeg4, %function
PostPro_CopyYuv_Mpeg4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	sxtw	x2, w21
	ldr	x4, .LC0
	lsl	x6, x2, 3
	ldr	w3, [x19, 14588]
	sub	x6, x6, x2
	ldr	w1, [x19, 14600]
	lsl	x6, x6, 3
	ldr	w9, [x19, 14672]
	sub	x6, x6, x2
	mov	w0, 1
	lsl	x6, x6, 1
	sub	x6, x6, x2
	lsl	x6, x6, 4
	add	x5, x4, x6
	str	w3, [x5, 8]
	ldr	w3, [x19, 14604]
	ldr	w2, [x19, 232]
	str	w2, [x5, 20]
	ldr	w2, [x19, 240]
	str	w2, [x5, 24]
	ldr	x2, .LC1
	ldrh	w7, [x19, 176]
	str	w7, [x5, 28]
	ldr	x8, [x2, 272]
	ldrh	w2, [x19, 178]
	stp	w2, w0, [x5, 32]
	stp	w1, w3, [x5, 12]
	mul	w7, w7, w2
	mov	w1, 4
	strb	w9, [x4, x6]
	strh	wzr, [x5, 72]
	sub	w7, w7, #1
	stp	wzr, w0, [x5, 40]
	strh	w7, [x5, 74]
	stp	wzr, w0, [x5, 52]
	str	w1, [x5, 64]
	ldrb	w1, [x19, 167]
	strb	w1, [x5, 1]
	cbz	x8, .L10
	mov	x4, x20
	mov	w3, w21
	mov	w2, 0
	mov	x1, x19
	mov	w0, 2
	blr	x8
	cmp	w0, wzr
	cset	w0, ne
.L10:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_CopyYuv_Mpeg4, .-PostPro_CopyYuv_Mpeg4
	.align	3
.LC0:
	.xword	g_RepairParam
	.align	3
.LC1:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vc1
	.type	PostPro_CopyYuv_Vc1, %function
PostPro_CopyYuv_Vc1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	w21, w1
	bl	_mcount
	ldrh	w2, [x19, 78]
	mov	w4, 16
	sub	w0, w2, #1
	uxth	w0, w0
	cmp	w0, 2047
	bls	.L13
	sub	w0, w2, #2049
	mov	w4, 32
	uxth	w0, w0
	cmp	w0, 2047
	bhi	.L20
.L13:
	sxtw	x0, w21
	ldr	x3, .LC2
	lsl	x6, x0, 3
	ldr	w1, [x19, 14608]
	sub	x6, x6, x0
	ldr	w7, [x19, 14612]
	lsl	x6, x6, 3
	ldr	w2, [x19, 14568]
	sub	x6, x6, x0
	lsl	x6, x6, 1
	sub	x6, x6, x0
	ldr	w0, [x19, 14440]
	lsl	x6, x6, 4
	add	x5, x3, x6
	str	w2, [x5, 8]
	mul	w2, w1, w7
	str	w4, [x5, 60]
	ldr	w4, [x19, 14600]
	sub	w2, w2, #1
	strb	w4, [x3, x6]
	str	w0, [x5, 20]
	stp	w1, w7, [x5, 28]
	ldr	w0, [x19, 14448]
	ldr	x1, .LC3
	ldr	w4, [x19, 14516]
	ldr	w3, [x19, 14520]
	strh	w2, [x5, 74]
	mov	w2, 4
	str	w0, [x5, 24]
	mov	w0, 1
	strh	wzr, [x5, 72]
	str	wzr, [x5, 40]
	stp	wzr, wzr, [x5, 48]
	stp	w4, w3, [x5, 12]
	str	w2, [x5, 64]
	str	w0, [x5, 36]
	str	w0, [x5, 44]
	str	w0, [x5, 56]
	ldr	x6, [x1, 272]
	ldrb	w1, [x19, 75]
	strb	w1, [x5, 1]
	cbz	x6, .L14
	mov	x4, x20
	mov	w3, w21
	mov	w2, 0
	mov	x1, x19
	blr	x6
	cmp	w0, wzr
	cset	w0, ne
.L14:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L20:
	sub	w2, w2, #4096
	mov	w4, 48
	sub	w0, w2, #1
	uxth	w0, w0
	cmp	w0, 2047
	bls	.L13
	sub	w2, w2, #2049
	mov	w0, 16
	mov	w4, 64
	uxth	w2, w2
	cmp	w2, 2047
	csel	w4, w0, w4, hi
	b	.L13
	.size	PostPro_CopyYuv_Vc1, .-PostPro_CopyYuv_Vc1
	.align	3
.LC2:
	.xword	g_RepairParam
	.align	3
.LC3:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vp6
	.type	PostPro_CopyYuv_Vp6, %function
PostPro_CopyYuv_Vp6:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	sxtw	x2, w21
	ldr	x4, .LC4
	lsl	x6, x2, 3
	ldr	w3, [x19, 228]
	sub	x6, x6, x2
	ldr	x7, .LC5
	lsl	x6, x6, 3
	mov	w0, 1
	sub	x6, x6, x2
	mov	w1, 4
	lsl	x6, x6, 1
	ldr	x8, [x7, 272]
	sub	x6, x6, x2
	lsl	x6, x6, 4
	add	x5, x4, x6
	str	w3, [x5, 8]
	ldr	w2, [x19, 236]
	str	w2, [x5, 20]
	ldr	w2, [x19, 240]
	str	w2, [x5, 24]
	ldrh	w7, [x19, 106]
	str	w7, [x5, 28]
	ldrh	w2, [x19, 108]
	stp	w2, w0, [x5, 32]
	strh	wzr, [x5, 72]
	mul	w7, w7, w2
	stp	wzr, w0, [x5, 40]
	str	wzr, [x5, 48]
	sub	w7, w7, #1
	strh	w7, [x5, 74]
	ldr	w2, [x19, 264]
	strb	w2, [x4, x6]
	stp	wzr, w0, [x5, 52]
	str	w1, [x5, 64]
	ldr	w1, [x19, 244]
	str	w1, [x5, 12]
	ldr	w1, [x19, 248]
	str	w1, [x5, 16]
	ldrb	w1, [x19, 104]
	strb	w1, [x5, 1]
	cbz	x8, .L22
	mov	x4, x20
	mov	w3, w21
	mov	w2, 0
	mov	x1, x19
	mov	w0, 10
	blr	x8
	cmp	w0, wzr
	cset	w0, ne
.L22:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_CopyYuv_Vp6, .-PostPro_CopyYuv_Vp6
	.align	3
.LC4:
	.xword	g_RepairParam
	.align	3
.LC5:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vp9
	.type	PostPro_CopyYuv_Vp9, %function
PostPro_CopyYuv_Vp9:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x26, x0
	mov	x0, x30
	mov	w22, w1
	mov	x23, x2
	bl	_mcount
	ldr	x25, .LC6
	sxtw	x0, w22
	add	x21, x26, 270336
	lsl	x20, x0, 3
	mov	w24, 1
	sub	x20, x20, x0
	lsl	x20, x20, 3
	ldr	w1, [x21, 2448]
	sub	x20, x20, x0
	ldr	w2, [x21, 2088]
	lsl	x20, x20, 1
	ldr	w3, [x21, 2092]
	sub	x20, x20, x0
	ldr	w0, [x21, 2456]
	lsl	x20, x20, 4
	ldr	w4, [x21, 2440]
	add	x19, x25, x20
	stp	w1, w0, [x19, 20]
	ldr	x1, .LC8
	mov	w0, 22
	stp	w2, w3, [x19, 28]
	str	w4, [x19, 8]
	stp	w24, wzr, [x19, 36]
	bl	dprint_vfmw
	strh	wzr, [x19, 72]
	ldp	w0, w1, [x19, 28]
	ldr	x2, .LC9
	stp	w24, wzr, [x19, 44]
	mul	w0, w0, w1
	ldr	w1, [x21, 2468]
	strb	w1, [x25, x20]
	sub	w0, w0, #1
	ldrb	w1, [x21, 2081]
	ldr	x5, [x2, 272]
	mov	w2, 6
	strh	w0, [x19, 74]
	strb	w1, [x19, 1]
	stp	wzr, w24, [x19, 52]
	str	w2, [x19, 64]
	cbz	x5, .L26
	mov	x4, x23
	mov	w3, w22
	mov	x1, x26
	mov	w2, 0
	mov	w0, 17
	blr	x5
	cmp	w0, wzr
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L26:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	PostPro_CopyYuv_Vp9, .-PostPro_CopyYuv_Vp9
	.align	3
.LC6:
	.xword	g_RepairParam
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroupOfTile
	.type	PostPro_GetHevcMbGroupOfTile, %function
PostPro_GetHevcMbGroupOfTile:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	w19, w3
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC11
	sbfiz	x19, x19, 6, 32
	str	wzr, [x20, 44]
	add	x0, x0, x19
	str	wzr, [x20, 56]
	ldr	x1, .LC10
	ldp	w19, w2, [x20, 28]
	ldrsw	x0, [x0, 8]
	mul	w19, w19, w2
	ldr	x0, [x1, x0, lsl 3]
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	HEVC_CalcTileMap
	ldr	w1, [x22, 12]
	mov	w7, 0
	cbz	w1, .L34
	ldr	x9, .LC12
	mov	w2, 1
	ldr	x8, .LC13
	.p2align 2
.L57:
	add	x5, x22, x7, uxtw 2
	ldrh	w4, [x5, 16]
	ldrh	w3, [x5, 18]
	mov	w0, w4
	cmp	w4, w3
	bhi	.L31
	mov	x6, x5
	b	.L32
	.p2align 3
.L64:
	ldrh	w4, [x5, 16]
.L32:
	cmp	w19, w4
	blt	.L35
	cmp	w19, w3
	blt	.L35
	ldr	w3, [x8, w0, uxtw 2]
	strb	w2, [x9, x3]
.L35:
	ldrh	w3, [x6, 18]
	add	w0, w0, 1
	cmp	w3, w0
	bcs	.L64
	ldr	w1, [x22, 12]
.L31:
	add	w7, w7, 1
	cmp	w1, w7
	bhi	.L57
.L34:
	ldr	w2, [x21, 2488]
	mov	w9, 0
	cbz	w2, .L30
	ldr	x5, .LC13
	ldr	x4, .LC12
	.p2align 2
.L56:
	uxtw	x8, w9
	add	x1, x21, x8, lsl 3
	ldr	w6, [x1, 3592]
	ldr	w1, [x1, 3588]
	cmp	w1, w6
	bhi	.L41
	ldr	w7, [x5, w1, uxtw 2]
	ldrb	w0, [x4, x7]
	cbz	w0, .L38
	mov	w0, w1
	b	.L40
	.p2align 3
.L43:
	ldr	w3, [x5, w0, uxtw 2]
	ldrb	w3, [x4, x3]
	cbz	w3, .L38
.L40:
	add	w0, w0, 1
	cmp	w0, w6
	bls	.L43
.L41:
	add	w9, w9, 1
	cmp	w2, w9
	bhi	.L56
.L30:
	ldr	x3, .LC12
	mov	w4, 0
	.p2align 2
.L48:
	cmp	w4, w19
	bcs	.L49
	ldrb	w0, [x3, w4, uxtw]
	mov	w1, w4
	cmp	w0, 1
	bne	.L62
	b	.L66
	.p2align 3
.L67:
	ldrb	w2, [x3, w0, uxtw]
	cbnz	w2, .L46
	mov	w1, w0
.L62:
	add	w0, w1, 1
	cmp	w19, w0
	bhi	.L67
.L46:
	ldr	w2, [x20, 44]
	add	w5, w2, 1
	add	x2, x20, x2, sxtw 2
	strh	w4, [x2, 72]
	mov	w4, w0
	strh	w1, [x2, 74]
	str	w5, [x20, 44]
.L45:
	cmp	w5, 199
	ble	.L48
	ldr	x1, .LC15
	mov	w0, 1
	sub	w19, w19, #1
	bl	dprint_vfmw
	strh	wzr, [x20, 72]
	mov	w0, 1
	strh	w19, [x20, 74]
	str	w0, [x20, 44]
.L49:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L38:
	add	x3, x21, x8, lsl 3
	b	.L42
	.p2align 3
.L65:
	ldr	w7, [x5, w1, uxtw 2]
.L42:
	strb	wzr, [x4, x7]
	add	w1, w1, 1
	ldr	w0, [x3, 3592]
	cmp	w0, w1
	bcs	.L65
	ldr	w2, [x21, 2488]
	add	w9, w9, 1
	cmp	w2, w9
	bhi	.L56
	b	.L30
	.p2align 3
.L66:
	add	w4, w4, 1
	ldr	w5, [x20, 44]
	b	.L45
	.size	PostPro_GetHevcMbGroupOfTile, .-PostPro_GetHevcMbGroupOfTile
	.align	3
.LC10:
	.xword	s_pstVfmwChan
	.align	3
.LC11:
	.xword	g_VdmDrvParam
	.align	3
.LC12:
	.xword	g_IsDeced
	.align	3
.LC13:
	.xword	g_TsToRsMap
	.align	3
.LC15:
	.xword	.LC14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroupOfNoTile
	.type	PostPro_GetHevcMbGroupOfNoTile, %function
PostPro_GetHevcMbGroupOfNoTile:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	mov	w20, w3
	bl	_mcount
	sbfiz	x20, x20, 6, 32
	ldr	x0, .LC17
	str	wzr, [x21, 44]
	add	x0, x0, x20
	str	wzr, [x21, 56]
	ldr	x1, .LC16
	ldp	w20, w2, [x21, 28]
	ldrsw	x0, [x0, 8]
	mul	w20, w20, w2
	ldr	x0, [x1, x0, lsl 3]
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	HEVC_CalcTileMap
	ldr	w1, [x19, 12]
	mov	w6, -1
	uxth	w9, w20
	mov	w7, w6
	mov	w0, 0
	add	w10, w20, w6
	add	x2, x19, x1, lsl 2
	strh	w9, [x2, 18]
	strh	w9, [x2, 16]
	b	.L77
	.p2align 3
.L85:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w1, w6, 1
	cmp	w2, w1
	ble	.L71
	ldr	w3, [x21, 44]
	cmp	w3, 199
	bgt	.L82
	add	x8, x21, x3, sxtw 2
	add	w7, w7, w7, lsr 31
	sub	w6, w6, #100
	sub	w1, w2, #1
	sxth	w7, w7
	strh	w1, [x8, 74]
	cmp	w6, w7
	strh	w7, [x8, 72]
	ble	.L74
	strh	w6, [x8, 72]
.L74:
	add	w3, w3, 1
	str	w3, [x21, 44]
.L71:
	ldr	w1, [x19, 12]
	sub	w3, w1, #1
	cmp	w3, w0
	beq	.L83
.L80:
	add	w0, w0, 1
	mov	w6, w4
	cmp	w0, w1
	mov	w7, w2
	bhi	.L84
.L77:
	sxtw	x5, w0
	add	x2, x19, x5, lsl 2
	mov	x1, x2
	ldrh	w2, [x2, 16]
	ldrh	w4, [x1, 18]
	cmp	w20, w2
	ccmp	w20, w4, 1, ge
	ccmp	w2, w4, 0, ge
	ble	.L85
	ldr	w1, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w1
	bls	.L77
.L84:
	mov	w0, 0
.L73:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L83:
	add	x5, x19, x5, lsl 2
	ldrh	w5, [x5, 18]
	cmp	w5, w10
	bge	.L80
	ldr	w3, [x21, 44]
	cmp	w3, 199
	bgt	.L86
	add	x1, x21, x3, sxtw 2
	sub	w9, w9, #1
	add	w3, w3, 1
	mov	w0, 0
	strh	w5, [x1, 72]
	strh	w9, [x1, 74]
	str	w3, [x21, 44]
	b	.L73
.L82:
	ldr	x2, .LC18
	mov	w0, 1
	ldr	x1, .LC20
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L86:
	ldr	x2, .LC18
	mov	w0, 1
	ldr	x1, .LC22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L73
	.size	PostPro_GetHevcMbGroupOfNoTile, .-PostPro_GetHevcMbGroupOfNoTile
	.align	3
.LC16:
	.xword	s_pstVfmwChan
	.align	3
.LC17:
	.xword	g_VdmDrvParam
	.align	3
.LC18:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroup
	.type	PostPro_GetHevcMbGroup, %function
PostPro_GetHevcMbGroup:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w1, w2, #1
	cmp	w1, 199
	bhi	.L91
	ldr	w0, [x20, 68]
	mov	w3, w22
	mov	x2, x21
	mov	x1, x19
	cbnz	w0, .L92
	mov	x0, x20
	bl	PostPro_GetHevcMbGroupOfNoTile
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L92:
	mov	x0, x20
	bl	PostPro_GetHevcMbGroupOfTile
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L91:
	ldr	x1, .LC24
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetHevcMbGroup, .-PostPro_GetHevcMbGroup
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHEVCRepairParam
	.type	PostPro_GetHEVCRepairParam, %function
PostPro_GetHEVCRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	mov	w21, w3
	bl	_mcount
	ldr	w0, [x19, 1288]
	mov	w4, 1
	add	x0, x0, 336
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x20, 8]
	ldr	x0, [x19, 2496]
	ldr	w0, [x0, 372]
	add	x0, x0, 336
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x20, 20]
	ldr	w0, [x19, 1292]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 1476]
	str	w0, [x20, 24]
	ldr	w3, [x19, 76]
	str	w3, [x20, 64]
	lsl	w2, w4, w3
	ldrb	w0, [x19]
	strb	w0, [x20]
	ldr	w0, [x19, 196]
	sub	w0, w0, #1
	add	w0, w0, w2
	lsr	w0, w0, w3
	str	w0, [x20, 28]
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	add	w2, w0, w2
	lsr	w2, w2, w3
	str	w2, [x20, 32]
	ldrb	w0, [x19, 225]
	str	w0, [x20, 68]
	str	w4, [x20, 36]
	ldr	w0, [x19, 12]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w0, [x19, 1340]
	cbnz	w0, .L106
	str	wzr, [x22, 12]
.L95:
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L107
.L96:
	str	wzr, [x20, 52]
	ldr	w0, [x19, 1296]
	str	w0, [x20, 12]
	ldr	w0, [x19, 1300]
	str	w0, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L107:
	ldr	w3, [x19, 1472]
	cbz	w3, .L96
	ldr	w1, [x19, 1344]
	mov	w0, 0
	cmp	w2, w1
	bne	.L97
	.p2align 2
.L99:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L96
	ldr	w1, [x1, 1344]
	cmp	w2, w1
	beq	.L99
.L97:
	str	w1, [x20, 20]
	b	.L96
	.p2align 3
.L106:
	mov	w3, w21
	mov	x2, x19
	mov	x1, x22
	mov	x0, x20
	bl	PostPro_GetHevcMbGroup
	b	.L95
	.size	PostPro_GetHEVCRepairParam, .-PostPro_GetHEVCRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp9MbGroup
	.type	PostPro_GetVp9MbGroup, %function
PostPro_GetVp9MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L122
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 18]
	strh	w9, [x3, 16]
	b	.L117
	.p2align 3
.L126:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L113
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L113
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L123
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 72]
	strh	w6, [x8, 74]
	str	w5, [x20, 44]
.L113:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L124
.L120:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L125
.L117:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L126
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L117
.L125:
	mov	w0, 0
.L110:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L124:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w10
	bge	.L120
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L127
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x20, 44]
	b	.L110
.L122:
	ldr	x1, .LC26
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L123:
	ldr	x1, .LC28
	mov	w2, 1140
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L110
.L127:
	ldr	x1, .LC28
	mov	w2, 1154
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L110
	.size	PostPro_GetVp9MbGroup, .-PostPro_GetVp9MbGroup
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC28:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP9RepairParam
	.type	PostPro_GetVP9RepairParam, %function
PostPro_GetVP9RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	add	x3, x20, 270336
	mov	w5, 1
	mov	w4, 6
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x3, 2440]
	str	w2, [x19, 8]
	ldr	w2, [x3, 2448]
	str	w2, [x19, 20]
	ldr	w2, [x3, 2456]
	str	w2, [x19, 24]
	ldr	w2, [x3, 2088]
	str	w2, [x19, 28]
	ldr	w2, [x3, 2092]
	stp	w2, w5, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x3, 2468]
	strb	w2, [x19]
	str	w4, [x19, 64]
	bl	PostPro_GetVp9MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP9RepairParam, .-PostPro_GetVP9RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMp24MbGroup
	.type	PostPro_GetMp24MbGroup, %function
PostPro_GetMp24MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L149
	str	wzr, [x20, 44]
	str	wzr, [x20, 56]
	ldp	w5, w1, [x20, 28]
	ldr	w0, [x19, 12]
	mul	w5, w5, w1
	uxtw	x1, w0
	add	x2, x19, x1, lsl 2
	uxth	w10, w5
	strh	w10, [x2, 18]
	strh	w10, [x2, 16]
	cbnz	w0, .L150
.L132:
	mov	w7, -1
	mov	w0, 0
	mov	w6, w7
	add	w11, w5, w7
	b	.L141
	.p2align 3
.L154:
	cmp	w2, w3
	ccmp	w2, w6, 1, le
	blt	.L133
	cmp	w2, w7
	csel	w7, w7, w6, ge
	add	w4, w7, 1
	cmp	w2, w4
	beq	.L137
	add	w6, w6, w6, lsr 31
	sub	w8, w2, #1
	cmp	w6, w8
	bge	.L137
	ldr	w4, [x20, 44]
	cmp	w4, 199
	bgt	.L151
	add	x9, x20, x4, sxtw 2
	sxth	w6, w6
	cmp	w7, w6
	strh	w6, [x9, 72]
	strh	w8, [x9, 74]
	ble	.L139
	strh	w7, [x9, 72]
.L139:
	add	w4, w4, 1
	str	w4, [x20, 44]
.L137:
	ldr	w4, [x19, 12]
	sub	w6, w4, #1
	cmp	w6, w0
	beq	.L152
.L144:
	add	w0, w0, 1
	mov	w7, w3
	cmp	w0, w4
	mov	w6, w2
	bhi	.L153
.L141:
	uxtw	x1, w0
	add	x2, x19, x1, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w5, w2
	ccmp	w5, w3, 1, ge
	bge	.L154
.L133:
	ldr	w4, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w4
	bls	.L141
.L153:
	mov	w0, 0
.L131:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L152:
	add	x1, x19, x1, lsl 2
	ldrh	w1, [x1, 18]
	cmp	w1, w11
	bge	.L144
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L155
	add	x3, x20, x0, sxtw 2
	sub	w10, w10, #1
	add	w2, w0, 1
	mov	w0, 0
	strh	w1, [x3, 72]
	strh	w10, [x3, 74]
	str	w2, [x20, 44]
	b	.L131
	.p2align 3
.L150:
	sub	w0, w0, #1
	sub	w1, w5, #10
	add	x0, x19, x0, lsl 2
	ldrh	w2, [x0, 18]
	cmp	w2, w1
	blt	.L132
	sub	w1, w10, #1
	strh	w1, [x0, 18]
	b	.L132
.L149:
	ldr	x1, .LC29
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L151:
	ldr	x1, .LC30
	mov	w2, 1501
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L131
.L155:
	ldr	x1, .LC30
	mov	w2, 1532
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L131
	.size	PostPro_GetMp24MbGroup, .-PostPro_GetMp24MbGroup
	.align	3
.LC29:
	.xword	.LC23
	.align	3
.LC30:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMPEG2RepairParam
	.type	PostPro_GetMPEG2RepairParam, %function
PostPro_GetMPEG2RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 188]
	str	w0, [x19, 8]
	ldr	w0, [x20, 184]
	str	w0, [x19, 20]
	ldr	w0, [x20, 224]
	str	w0, [x19, 24]
	ldrh	w0, [x20, 150]
	str	w0, [x19, 28]
	ldrh	w0, [x20, 146]
	str	w0, [x19, 32]
	ldrb	w0, [x20, 3]
	cmp	w0, 3
	cset	w0, eq
	stp	w0, wzr, [x19, 36]
	ldrb	w0, [x20, 3]
	cmp	w0, 1
	beq	.L160
	cmp	w0, 2
	beq	.L160
	cmp	w0, 3
	beq	.L161
.L158:
	add	x20, x20, 45056
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 240]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L161:
	str	wzr, [x19, 52]
	b	.L158
	.p2align 3
.L160:
	str	w0, [x19, 52]
	b	.L158
	.size	PostPro_GetMPEG2RepairParam, .-PostPro_GetMPEG2RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMPEG4RepairParam
	.type	PostPro_GetMPEG4RepairParam, %function
PostPro_GetMPEG4RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 224]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 232]
	str	w2, [x19, 20]
	ldr	w2, [x20, 240]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 176]
	str	w2, [x19, 28]
	ldrh	w2, [x20, 178]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 14672]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetMPEG4RepairParam, .-PostPro_GetMPEG4RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetREAL8RepairParam
	.type	PostPro_GetREAL8RepairParam, %function
PostPro_GetREAL8RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 56]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 52]
	str	w2, [x19, 20]
	ldr	w2, [x20, 68]
	str	w2, [x19, 24]
	ldr	w2, [x20, 4]
	str	w2, [x19, 28]
	ldr	w2, [x20, 8]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 76]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetREAL8RepairParam, .-PostPro_GetREAL8RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetREAL9RepairParam
	.type	PostPro_GetREAL9RepairParam, %function
PostPro_GetREAL9RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 52]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 48]
	str	w2, [x19, 20]
	ldr	w2, [x20, 64]
	str	w2, [x19, 24]
	ldr	w2, [x20, 4]
	str	w2, [x19, 28]
	ldr	w2, [x20, 8]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 72]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetREAL9RepairParam, .-PostPro_GetREAL9RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVc1MbGroup
	.type	PostPro_GetVc1MbGroup, %function
PostPro_GetVc1MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L179
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 18]
	strh	w9, [x3, 16]
	b	.L174
	.p2align 3
.L183:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L170
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L170
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L180
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 72]
	strh	w6, [x8, 74]
	str	w5, [x20, 44]
.L170:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L181
.L177:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L182
.L174:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L183
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L174
.L182:
	mov	w0, 0
.L167:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L181:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w10
	bge	.L177
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L184
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x20, 44]
	b	.L167
.L179:
	ldr	x1, .LC31
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L180:
	ldr	x1, .LC32
	mov	w2, 1596
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L167
.L184:
	ldr	x1, .LC32
	mov	w2, 1616
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L167
	.size	PostPro_GetVc1MbGroup, .-PostPro_GetVc1MbGroup
	.align	3
.LC31:
	.xword	.LC25
	.align	3
.LC32:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVC1RepairParam
	.type	PostPro_GetVC1RepairParam, %function
PostPro_GetVC1RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 14568]
	mov	x1, x21
	str	w0, [x19, 8]
	mov	x0, x19
	ldr	w2, [x20, 14440]
	str	w2, [x19, 20]
	ldr	w2, [x20, 14448]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 82]
	add	w2, w2, 1
	str	w2, [x19, 28]
	ldrh	w2, [x20, 84]
	add	w2, w2, 1
	str	w2, [x19, 32]
	ldrb	w2, [x20, 5]
	and	w2, w2, -3
	uxtb	w2, w2
	cmp	w2, wzr
	cset	w2, eq
	stp	w2, wzr, [x19, 36]
	bl	PostPro_GetVc1MbGroup
	ldrb	w0, [x20, 72]
	ldr	w1, [x19, 36]
	and	w0, w0, 3
	str	w0, [x19, 48]
	cmp	w1, 1
	beq	.L189
	ldrb	w0, [x20, 5]
	cmp	w0, 3
	beq	.L190
.L187:
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L190:
	ldrb	w0, [x20, 8]
	cbz	w0, .L191
	cmp	w0, 1
	bne	.L187
	mov	w0, 2
	str	w0, [x19, 52]
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L191:
	mov	w0, 1
	str	w0, [x19, 52]
	b	.L187
	.p2align 3
.L189:
	str	wzr, [x19, 52]
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVC1RepairParam, .-PostPro_GetVC1RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp6MbGroup
	.type	PostPro_GetVp6MbGroup, %function
PostPro_GetVp6MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L206
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 18]
	strh	w9, [x3, 16]
	b	.L201
	.p2align 3
.L210:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L197
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L197
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L207
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 72]
	strh	w6, [x8, 74]
	str	w5, [x20, 44]
.L197:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L208
.L204:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L209
.L201:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L210
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L201
.L209:
	mov	w0, 0
.L194:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L208:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w10
	bge	.L204
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L211
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x20, 44]
	b	.L194
.L206:
	ldr	x1, .LC33
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L207:
	ldr	x1, .LC34
	mov	w2, 1681
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L194
.L211:
	ldr	x1, .LC34
	mov	w2, 1701
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L194
	.size	PostPro_GetVp6MbGroup, .-PostPro_GetVp6MbGroup
	.align	3
.LC33:
	.xword	.LC25
	.align	3
.LC34:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP6RepairParam
	.type	PostPro_GetVP6RepairParam, %function
PostPro_GetVP6RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 228]
	mov	w3, 1
	str	w0, [x19, 8]
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 236]
	str	w2, [x19, 20]
	ldr	w2, [x20, 240]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 106]
	str	w2, [x19, 28]
	ldrh	w2, [x20, 108]
	stp	w2, w3, [x19, 32]
	str	wzr, [x19, 40]
	bl	PostPro_GetVp6MbGroup
	stp	wzr, wzr, [x19, 48]
	mov	w1, 4
	ldr	w0, [x20, 264]
	strb	w0, [x19]
	str	w1, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP6RepairParam, .-PostPro_GetVP6RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp8MbGroup
	.type	PostPro_GetVp8MbGroup, %function
PostPro_GetVp8MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L227
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 18]
	strh	w9, [x3, 16]
	b	.L222
	.p2align 3
.L231:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L218
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L218
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L228
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 72]
	strh	w6, [x8, 74]
	str	w5, [x20, 44]
.L218:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L229
.L225:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L230
.L222:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L231
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L222
.L230:
	mov	w0, 0
.L215:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L229:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w10
	bge	.L225
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L232
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x20, 44]
	b	.L215
.L227:
	ldr	x1, .LC35
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L228:
	ldr	x1, .LC36
	mov	w2, 1765
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L215
.L232:
	ldr	x1, .LC36
	mov	w2, 1785
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L215
	.size	PostPro_GetVp8MbGroup, .-PostPro_GetVp8MbGroup
	.align	3
.LC35:
	.xword	.LC25
	.align	3
.LC36:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP8RepairParam
	.type	PostPro_GetVP8RepairParam, %function
PostPro_GetVP8RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 3120]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 3132]
	str	w2, [x19, 20]
	ldr	w2, [x20, 3136]
	str	w2, [x19, 24]
	ldr	w2, [x20, 2788]
	str	w2, [x19, 28]
	ldr	w2, [x20, 2792]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 3144]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetVp8MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP8RepairParam, .-PostPro_GetVP8RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetAvsMbGroup
	.type	PostPro_GetAvsMbGroup, %function
PostPro_GetAvsMbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L246
	ldp	w3, w1, [x20, 28]
	str	wzr, [x20, 56]
	mov	w6, -1
	mov	x9, x20
	mov	w0, 0
	ldr	w2, [x19, 12]
	mov	w12, 0
	mul	w1, w3, w1
	mov	w7, w6
	add	x3, x19, x2, lsl 2
	add	w14, w1, w6
	add	w11, w1, w1, lsr 31
	uxth	w13, w1
	asr	w11, w11, 1
	add	w15, w11, w6
	strh	w13, [x3, 18]
	strh	w13, [x3, 16]
	.p2align 2
.L241:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	bgt	.L237
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	ble	.L239
	ldr	w6, [x9, 44]
	uxth	w8, w12
	lsr	w10, w7, 31
	sub	w5, w2, #1
	sub	w5, w5, w8
	sub	w10, w10, w8
	add	x8, x9, x6, sxtw 2
	add	w7, w10, w7
	add	w6, w6, 1
	strh	w7, [x8, 72]
	strh	w5, [x8, 74]
	str	w6, [x9, 44]
	ldr	w5, [x9, 36]
	cbnz	w5, .L239
	cmp	w2, w15
	bge	.L247
	.p2align 2
.L239:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L248
.L244:
	mov	w6, w3
	mov	w7, w2
.L240:
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L241
	mov	w0, 0
.L236:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L237:
	ldr	w5, [x19, 12]
	b	.L240
	.p2align 3
.L248:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w14
	bge	.L244
	ldr	w1, [x20, 44]
	sub	w13, w13, #1
	mov	w0, 0
	add	w2, w1, 1
	add	x1, x20, x1, sxtw 2
	strh	w4, [x1, 72]
	strh	w13, [x1, 74]
	str	w2, [x20, 44]
	b	.L236
	.p2align 3
.L247:
	add	x9, x20, 872
	mov	w12, w11
	b	.L239
	.p2align 3
.L246:
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetAvsMbGroup, .-PostPro_GetAvsMbGroup
	.align	3
.LC37:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetAVSRepairParam
	.type	PostPro_GetAVSRepairParam, %function
PostPro_GetAVSRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w4, [x20, 14464]
	add	x0, x19, 768
	str	w4, [x19, 8]
	ldr	w7, [x20, 14456]
	str	w7, [x19, 20]
	ldr	w2, [x20, 14468]
	str	w2, [x19, 24]
	ldrh	w6, [x20, 72]
	str	w6, [x19, 28]
	ldrh	w1, [x20, 74]
	str	w1, [x19, 32]
	lsr	w8, w1, 1
	ldrb	w3, [x20, 17]
	cmp	w3, 3
	cset	w5, eq
	stp	w5, wzr, [x19, 36]
	ldr	w3, [x21, 4]
	str	w7, [x19, 892]
	add	w4, w3, w4
	str	w4, [x19, 880]
	ldr	w3, [x21, 4]
	stp	w1, w5, [x0, 136]
	add	w3, w3, w3, lsl 3
	madd	w3, w3, w8, w2
	stp	w3, w6, [x0, 128]
	str	wzr, [x19, 912]
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	beq	.L252
	cmp	w0, 1
	beq	.L253
.L251:
	ldr	w1, [x20, 14904]
	mov	w0, 4
	strb	w1, [x19]
	mov	x1, x21
	str	w0, [x19, 64]
	mov	x0, x19
	bl	PostPro_GetAvsMbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L253:
	str	w0, [x19, 52]
	b	.L251
	.p2align 3
.L252:
	str	wzr, [x19, 52]
	b	.L251
	.size	PostPro_GetAVSRepairParam, .-PostPro_GetAVSRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetAvs2MbGroup
	.type	PostPro_GetAvs2MbGroup, %function
PostPro_GetAvs2MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	cmp	w2, 200
	bhi	.L269
	cbz	w2, .L270
	str	wzr, [x20, 56]
	mov	w6, -1
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mov	w0, 0
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 18]
	strh	w9, [x3, 16]
	b	.L264
	.p2align 3
.L274:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L260
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L260
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L271
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 72]
	strh	w6, [x8, 74]
	str	w5, [x20, 44]
.L260:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L272
.L267:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L273
.L264:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L274
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L264
.L273:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L270:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x20, 44]
	str	w1, [x20, 56]
.L256:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L272:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w10
	bge	.L267
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L275
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x20, 44]
	b	.L256
	.p2align 3
.L269:
	ldr	x1, .LC38
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L271:
	ldr	x1, .LC39
	mov	w2, 1933
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L256
.L275:
	ldr	x1, .LC39
	mov	w2, 1947
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L256
	.size	PostPro_GetAvs2MbGroup, .-PostPro_GetAvs2MbGroup
	.align	3
.LC38:
	.xword	.LC23
	.align	3
.LC39:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetDivx3MbGroup
	.type	PostPro_GetDivx3MbGroup, %function
PostPro_GetDivx3MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 3
	bhi	.L288
	ldp	w3, w1, [x20, 28]
	str	wzr, [x20, 56]
	mov	w6, -1
	mov	x9, x20
	mov	w0, 0
	ldr	w2, [x19, 12]
	mov	w12, 0
	mul	w1, w3, w1
	mov	w7, w6
	add	x3, x19, x2, lsl 2
	add	w14, w1, w6
	add	w11, w1, w1, lsr 31
	uxth	w13, w1
	asr	w11, w11, 1
	add	w15, w11, w6
	strh	w13, [x3, 18]
	strh	w13, [x3, 16]
	.p2align 2
.L283:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 16]
	ldrh	w3, [x3, 18]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	bgt	.L279
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	ble	.L281
	ldr	w6, [x9, 44]
	uxth	w8, w12
	lsr	w10, w7, 31
	sub	w5, w2, #1
	sub	w5, w5, w8
	sub	w10, w10, w8
	add	x8, x9, x6, sxtw 2
	add	w7, w10, w7
	add	w6, w6, 1
	strh	w7, [x8, 72]
	strh	w5, [x8, 74]
	str	w6, [x9, 44]
	ldr	w5, [x9, 36]
	cbnz	w5, .L281
	cmp	w2, w15
	bge	.L289
	.p2align 2
.L281:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L290
.L286:
	mov	w6, w3
	mov	w7, w2
.L282:
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L283
	mov	w0, 0
.L278:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L279:
	ldr	w5, [x19, 12]
	b	.L282
	.p2align 3
.L290:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 18]
	cmp	w4, w14
	bge	.L286
	ldr	w1, [x20, 44]
	sub	w13, w13, #1
	mov	w0, 0
	add	w2, w1, 1
	add	x1, x20, x1, sxtw 2
	strh	w4, [x1, 72]
	strh	w13, [x1, 74]
	str	w2, [x20, 44]
	b	.L278
	.p2align 3
.L289:
	add	x9, x20, 872
	mov	w12, w11
	b	.L281
	.p2align 3
.L288:
	ldr	x1, .LC40
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetDivx3MbGroup, .-PostPro_GetDivx3MbGroup
	.align	3
.LC40:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetDIVX3RepairParam
	.type	PostPro_GetDIVX3RepairParam, %function
PostPro_GetDIVX3RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 128]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 124]
	str	w2, [x19, 20]
	ldr	w2, [x20, 152]
	str	w2, [x19, 24]
	ldr	w2, [x20, 8]
	str	w2, [x19, 28]
	ldr	w2, [x20, 12]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 160]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetDivx3MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetDIVX3RepairParam, .-PostPro_GetDIVX3RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_BubbleSort
	.type	PostPro_BubbleSort, %function
PostPro_BubbleSort:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w9, [x19, 12]
	mov	w8, 1
	add	x10, x19, 16
	cmp	w9, w8
	bls	.L292
	.p2align 2
.L301:
	mov	w1, 0
	sub	w5, w9, w8
	cmp	w1, w5
	add	w1, w1, 1
	mov	x0, x10
	mov	w7, 0
	add	x2, x19, x1, uxtw 2
	beq	.L304
	.p2align 2
.L296:
	ldrh	w3, [x0]
	ldrh	w4, [x2, 16]
	cmp	w3, w4
	bls	.L295
	strh	w4, [x0]
	mov	w7, 1
	ldrh	w4, [x0, 2]
	ldrh	w6, [x2, 18]
	strh	w6, [x0, 2]
	strh	w3, [x2, 16]
	strh	w4, [x2, 18]
.L295:
	cmp	w1, w5
	add	w1, w1, 1
	add	x0, x0, 4
	add	x2, x19, x1, uxtw 2
	bne	.L296
.L304:
	cbz	w7, .L292
	add	w8, w8, 1
	cmp	w9, w8
	ccmp	w7, 1, 0, hi
	beq	.L301
.L292:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_BubbleSort, .-PostPro_BubbleSort
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264MbOfMBAFF
	.type	PostPro_GetH264MbOfMBAFF, %function
PostPro_GetH264MbOfMBAFF:
	sub	sp, sp, #800
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	ldp	w9, w10, [x20, 28]
	lsl	w1, w9, 1
	cbz	w0, .L320
	sub	w0, w0, #1
	mov	x8, 6
	add	x3, x29, 32
	add	x2, x19, 16
	add	x8, x8, x0, uxtw 2
	add	x0, x29, 34
	add	x8, x3, x8
	.p2align 2
.L307:
	ldrh	w4, [x2]
	add	x2, x2, 4
	ldrh	w3, [x2, -2]
	strh	w4, [x0, -2]
	strh	w3, [x0], 4
	cmp	x0, x8
	bne	.L307
	ldrh	w0, [x29, 34]
	ldrh	w3, [x29, 32]
	orr	w0, w0, 1
	and	w3, w3, 65534
	strh	w3, [x29, 32]
	uxth	w0, w0
	strh	w0, [x29, 34]
	cbz	w1, .L320
	add	x6, x29, 38
	mov	w7, 0
	sub	w11, w1, #2
	uxth	w12, w1
	b	.L316
	.p2align 3
.L326:
	cmp	w4, w13
	lsr	w2, w2, 1
	lsr	w15, w3, 1
	beq	.L311
	mul	w4, w12, w4
	uxtw	x14, w7
	add	w3, w7, 1
	cmp	w3, 199
	add	x0, x19, x14, lsl 2
	uxth	w4, w4
	add	w2, w4, w2
	mov	x14, x0
	uxth	w2, w2
	strh	w2, [x0, 16]
	ldr	w0, [x20, 28]
	sub	w0, w0, #1
	add	w4, w4, w0
	strh	w4, [x14, 18]
	bhi	.L312
	mul	w0, w12, w13
	ldr	w4, [x20, 28]
	add	x13, x19, x3, lsl 2
	uxth	w15, w15
	add	w2, w2, w4
	uxth	w0, w0
	add	w4, w7, 2
	add	w5, w0, w15
	strh	w2, [x13, 16]
	cmp	w4, 199
	strh	w5, [x13, 18]
	bhi	.L312
	ldr	w2, [x20, 28]
	add	x3, x19, x4, lsl 2
	add	w7, w7, 3
	add	w2, w0, w2
	cmp	w7, 199
	uxth	w0, w2
	strh	w0, [x3, 16]
	add	w0, w15, w0
	strh	w0, [x3, 18]
	bhi	.L312
.L313:
	cmp	x6, x8
	beq	.L315
.L317:
	ldrh	w0, [x6]
	ldrh	w3, [x6, -2]
	orr	w0, w0, 1
	and	w3, w3, 65534
	strh	w3, [x6, -2]
	uxth	w0, w0
	strh	w0, [x6], 4
.L316:
	udiv	w4, w3, w1
	mul	w5, w4, w1
	sub	w2, w3, w5
	cmp	w2, 1
	bls	.L309
	udiv	w13, w0, w1
	msub	w3, w13, w1, w0
	cmp	w11, w3
	bhi	.L326
	uxtw	x4, w7
	uxth	w5, w5
	add	w2, w5, w2, lsr 1
	add	w3, w7, 1
	add	x13, x19, x4, lsl 2
	cmp	w3, 199
	uxth	w2, w2
	mov	x4, x13
	strh	w2, [x13, 16]
	ldr	w13, [x20, 28]
	sub	w13, w13, #1
	add	w5, w5, w13
	strh	w5, [x4, 18]
	bhi	.L312
	add	x5, x19, x3, lsl 2
	ldr	w4, [x20, 28]
	add	w7, w7, 2
	add	w2, w2, w4
	cmp	w7, 199
	strh	w2, [x5, 16]
	strh	w0, [x5, 18]
	bls	.L313
.L312:
	mul	w9, w9, w10
	mov	w0, 1
	strh	wzr, [x19, 16]
	sub	w9, w9, #1
	str	w0, [x19, 12]
	strh	w9, [x19, 18]
	mov	x0, x19
	bl	PostPro_BubbleSort
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	add	sp, sp, 800
	ret
	.p2align 3
.L309:
	udiv	w2, w0, w1
	mul	w2, w2, w1
	sub	w4, w0, w2
	cmp	w11, w4
	bls	.L314
	uxtw	x5, w7
	uxth	w2, w2
	ubfx	x4, x4, 1, 16
	add	w0, w7, 1
	add	x14, x19, x5, lsl 2
	add	w13, w2, w4
	cmp	w0, 199
	strh	w3, [x14, 16]
	strh	w13, [x14, 18]
	bhi	.L312
	uxtw	x3, w0
	ldr	w0, [x20, 28]
	add	w7, w7, 2
	add	x5, x19, x3, lsl 2
	add	w2, w2, w0
	cmp	w7, 199
	uxth	w2, w2
	strh	w2, [x5, 16]
	add	w2, w4, w2
	strh	w2, [x5, 18]
	bhi	.L312
	cmp	x6, x8
	bne	.L317
	.p2align 2
.L315:
	str	w7, [x19, 12]
.L327:
	mov	x0, x19
	bl	PostPro_BubbleSort
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	add	sp, sp, 800
	ret
	.p2align 3
.L314:
	uxtw	x2, w7
	add	w7, w7, 1
	cmp	w7, 199
	add	x4, x19, x2, lsl 2
	strh	w3, [x4, 16]
	strh	w0, [x4, 18]
	bls	.L313
	b	.L312
	.p2align 3
.L311:
	uxtw	x0, w7
	uxth	w5, w5
	add	w2, w5, w2
	add	w5, w5, w15
	add	x3, x19, x0, lsl 2
	add	w0, w7, 1
	uxth	w2, w2
	uxth	w5, w5
	cmp	w0, 199
	strh	w2, [x3, 16]
	strh	w5, [x3, 18]
	bhi	.L312
	add	x4, x19, x0, lsl 2
	ldr	w3, [x20, 28]
	add	w7, w7, 2
	add	w2, w2, w3
	cmp	w7, 199
	strh	w2, [x4, 16]
	ldr	w2, [x20, 28]
	add	w5, w5, w2
	strh	w5, [x4, 18]
	bls	.L313
	b	.L312
.L320:
	mov	w7, 0
	str	w7, [x19, 12]
	b	.L327
	.size	PostPro_GetH264MbOfMBAFF, .-PostPro_GetH264MbOfMBAFF
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264MbGroup
	.type	PostPro_GetH264MbGroup, %function
PostPro_GetH264MbGroup:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x21, x0
	mov	x0, x30
	mov	w22, w2
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w1, w2, #1
	cmp	w1, 199
	bhi	.L347
	ldp	w20, w0, [x21, 28]
	mul	w20, w20, w0
	cbnz	w22, .L348
.L331:
	str	wzr, [x21, 44]
	mov	w5, -1
	str	wzr, [x21, 56]
	uxth	w9, w20
	mov	w0, 0
	mov	w6, w5
	ldr	w1, [x19, 12]
	add	w10, w20, w5
	add	x2, x19, x1, lsl 2
	strh	w9, [x2, 18]
	strh	w9, [x2, 16]
	b	.L339
	.p2align 3
.L352:
	cmp	w1, w5
	csel	w5, w5, w6, ge
	add	w4, w5, 1
	cmp	w1, w4
	ble	.L334
	ldr	w4, [x21, 44]
	cmp	w4, 199
	bgt	.L349
	add	x8, x21, x4, sxtw 2
	add	w6, w6, w6, lsr 31
	sub	w5, w5, #100
	sub	w7, w1, #1
	sxth	w6, w6
	strh	w7, [x8, 74]
	cmp	w5, w6
	strh	w6, [x8, 72]
	ble	.L336
	strh	w5, [x8, 72]
.L336:
	add	w4, w4, 1
	str	w4, [x21, 44]
.L334:
	ldr	w4, [x19, 12]
	sub	w5, w4, #1
	cmp	w5, w0
	beq	.L350
.L342:
	add	w0, w0, 1
	mov	w5, w2
	cmp	w0, w4
	mov	w6, w1
	bhi	.L351
.L339:
	uxtw	x3, w0
	add	x1, x19, x3, lsl 2
	mov	x2, x1
	ldrh	w1, [x1, 16]
	ldrh	w2, [x2, 18]
	cmp	w20, w1
	ccmp	w20, w2, 1, ge
	ccmp	w1, w2, 0, ge
	ble	.L352
	ldr	w4, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w4
	bls	.L339
.L351:
	mov	w0, 0
.L330:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L350:
	add	x3, x19, x3, lsl 2
	ldrh	w3, [x3, 18]
	cmp	w3, w10
	bge	.L342
	ldr	w0, [x21, 44]
	cmp	w0, 199
	bgt	.L353
	add	x2, x21, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w3, [x2, 72]
	strh	w9, [x2, 74]
	str	w1, [x21, 44]
	b	.L330
	.p2align 3
.L348:
	mov	x1, x19
	mov	x0, x21
	bl	PostPro_GetH264MbOfMBAFF
	b	.L331
.L347:
	ldr	x1, .LC43
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L349:
	ldr	x1, .LC44
	mov	w2, 1396
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L330
.L353:
	ldr	x1, .LC44
	mov	w2, 1424
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L330
	.size	PostPro_GetH264MbGroup, .-PostPro_GetH264MbGroup
	.align	3
.LC43:
	.xword	.LC23
	.align	3
.LC44:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264RepairParam
	.type	PostPro_GetH264RepairParam, %function
PostPro_GetH264RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x19, 308]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 8]
	ldr	x0, [x19, 944]
	ldr	w4, [x0, 1640]
	add	x0, x19, x4, uxtw 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 20]
	ldr	w0, [x19, 316]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 584]
	str	w0, [x20, 24]
	ldr	w0, [x19, 44]
	str	w0, [x20, 28]
	ldr	w0, [x19, 36]
	str	w0, [x20, 32]
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 36]
	ldrb	w0, [x19, 1]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w5, [x19, 936]
	cbz	w5, .L355
	ldr	w0, [x19, 1120]
	cmp	w4, w0
	beq	.L392
	mov	w0, 0
	b	.L358
	.p2align 3
.L359:
	ldr	w3, [x19, x3, lsl 2]
	cmp	w4, w3
	beq	.L356
.L358:
	add	w0, w0, 1
	cmp	w0, w5
	sxtw	x2, w0
	add	x3, x2, 280
	bne	.L359
.L355:
	ldr	w2, [x19, 48]
	cbz	w2, .L360
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w2, eq
.L360:
	ldrsb	w0, [x19, 2]
	cbnz	w0, .L393
	str	wzr, [x21, 12]
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L394
.L363:
	ldrb	w0, [x19]
	cbz	w0, .L372
	cmp	w0, 1
	beq	.L390
	cmp	w0, 2
	beq	.L390
	cmp	w0, 3
	bne	.L369
.L372:
	str	wzr, [x20, 52]
.L369:
	ldrb	w1, [x19, 4]
	mov	w0, 4
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldr	w0, [x19, 720]
	str	w0, [x20, 12]
	ldr	w0, [x19, 724]
	str	w0, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L390:
	str	w0, [x20, 52]
	b	.L369
.L392:
	mov	x2, 0
	.p2align 2
.L356:
	add	x2, x2, 264
	ldr	w0, [x19, x2, lsl 2]
	str	w0, [x20, 48]
	b	.L355
	.p2align 3
.L393:
	mov	x1, x21
	mov	x0, x20
	bl	PostPro_GetH264MbGroup
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	bne	.L363
.L394:
	ldr	w3, [x19, 580]
	cbz	w3, .L363
	ldr	w1, [x19, 324]
	mov	w0, 0
	cmp	w2, w1
	bne	.L364
	.p2align 2
.L366:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L363
	ldr	w1, [x1, 324]
	cmp	w2, w1
	beq	.L366
.L364:
	str	w1, [x20, 20]
	b	.L363
	.size	PostPro_GetH264RepairParam, .-PostPro_GetH264RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMVCRepairParam
	.type	PostPro_GetMVCRepairParam, %function
PostPro_GetMVCRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x19, 308]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 8]
	ldr	x0, [x19, 944]
	ldr	w4, [x0, 1640]
	add	x0, x19, x4, uxtw 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 20]
	ldr	w0, [x19, 316]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 584]
	str	w0, [x20, 24]
	ldr	w0, [x19, 44]
	str	w0, [x20, 28]
	ldr	w0, [x19, 36]
	str	w0, [x20, 32]
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 36]
	ldrb	w0, [x19, 1]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w5, [x19, 936]
	cbz	w5, .L396
	ldr	w0, [x19, 1120]
	cmp	w4, w0
	beq	.L433
	mov	w0, 0
	b	.L399
	.p2align 3
.L400:
	ldr	w3, [x19, x3, lsl 2]
	cmp	w4, w3
	beq	.L397
.L399:
	add	w0, w0, 1
	cmp	w0, w5
	sxtw	x2, w0
	add	x3, x2, 280
	bne	.L400
.L396:
	ldr	w2, [x19, 48]
	cbz	w2, .L401
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w2, eq
.L401:
	ldrsb	w0, [x19, 2]
	cbnz	w0, .L434
	str	wzr, [x21, 12]
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L435
.L404:
	ldrb	w0, [x19]
	cbz	w0, .L413
	cmp	w0, 1
	beq	.L431
	cmp	w0, 2
	beq	.L431
	cmp	w0, 3
	bne	.L410
.L413:
	str	wzr, [x20, 52]
.L410:
	ldrb	w1, [x19, 4]
	mov	w0, 4
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L431:
	str	w0, [x20, 52]
	mov	w0, 4
	ldrb	w1, [x19, 4]
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L433:
	mov	x2, 0
	.p2align 2
.L397:
	add	x2, x2, 264
	ldr	w0, [x19, x2, lsl 2]
	str	w0, [x20, 48]
	b	.L396
	.p2align 3
.L434:
	mov	x1, x21
	mov	x0, x20
	bl	PostPro_GetH264MbGroup
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	bne	.L404
.L435:
	ldr	w3, [x19, 580]
	cbz	w3, .L404
	ldr	w1, [x19, 324]
	mov	w0, 0
	cmp	w2, w1
	bne	.L405
	.p2align 2
.L407:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L404
	ldr	w1, [x1, 324]
	cmp	w2, w1
	beq	.L407
.L405:
	str	w1, [x20, 20]
	b	.L404
	.size	PostPro_GetMVCRepairParam, .-PostPro_GetMVCRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetRepairParam
	.type	PostPro_GetRepairParam, %function
PostPro_GetRepairParam:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x26, x1
	mov	w20, w0
	add	x25, x1, 872
	mov	x0, x30
	mov	x19, x2
	mov	x21, x3
	mov	w22, w4
	bl	_mcount
	str	w20, [x26, 4]
	cmp	w20, 17
	str	wzr, [x26, 44]
	str	wzr, [x25, 44]
	bls	.L466
.L437:
	ldr	x2, .LC46
	mov	w3, 860
	ldr	x1, .LC48
	mov	w0, 0
	add	x2, x2, 32
	bl	dprint_vfmw
	.p2align 2
.L452:
	ldp	w20, w1, [x26, 28]
	ldr	w0, [x26, 44]
	mul	w20, w20, w1
	cbz	w0, .L458
	ldr	x24, .LC50
	mov	w22, 0
	mov	w23, 0
	.p2align 2
.L454:
	add	x19, x26, x23, uxtw 2
	mov	x1, x24
	mov	w0, 22
	add	w23, w23, 1
	ldrsh	w2, [x19, 74]
	ldrsh	w3, [x19, 72]
	bl	dprint_vfmw
	ldrsh	w0, [x19, 74]
	ldrsh	w2, [x19, 72]
	ldr	w1, [x26, 44]
	sub	w0, w0, w2
	cmp	w1, w23
	add	w0, w0, 1
	add	w22, w22, w0
	bhi	.L454
.L453:
	ldr	w0, [x25, 44]
	cbz	w0, .L455
	sub	w0, w0, #1
	mov	x2, 950
	add	x1, x26, 946
	add	x0, x2, x0, uxtw 2
	add	x26, x26, x0
	.p2align 2
.L456:
	ldrsh	w0, [x1]
	add	x1, x1, 4
	ldrsh	w2, [x1, -6]
	cmp	x26, x1
	sub	w0, w0, w2
	add	w0, w0, 1
	add	w22, w22, w0
	bne	.L456
.L455:
	mov	w19, 0
	cbz	w20, .L457
	lsl	w19, w22, 2
	mov	w1, 100
	sub	w19, w19, w22
	lsl	w0, w19, 5
	add	w19, w19, w0
	add	w19, w19, w22
	udiv	w19, w19, w20
	cmp	w19, w1
	csel	w19, w19, w1, ls
.L457:
	ldr	x1, .LC52
	mov	w3, w22
	mov	w2, w20
	str	wzr, [x21, 12]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L466:
	ldr	x0, .LC45
	ldrh	w0, [x0,w20,uxtw #1]
	adr	x1, .Lrtx439
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx439:
	.section	.rodata
	.align	0
	.align	2
.L439:
	.2byte	(.L438 - .Lrtx439) / 4
	.2byte	(.L440 - .Lrtx439) / 4
	.2byte	(.L441 - .Lrtx439) / 4
	.2byte	(.L442 - .Lrtx439) / 4
	.2byte	(.L437 - .Lrtx439) / 4
	.2byte	(.L443 - .Lrtx439) / 4
	.2byte	(.L444 - .Lrtx439) / 4
	.2byte	(.L437 - .Lrtx439) / 4
	.2byte	(.L445 - .Lrtx439) / 4
	.2byte	(.L446 - .Lrtx439) / 4
	.2byte	(.L447 - .Lrtx439) / 4
	.2byte	(.L447 - .Lrtx439) / 4
	.2byte	(.L447 - .Lrtx439) / 4
	.2byte	(.L448 - .Lrtx439) / 4
	.2byte	(.L437 - .Lrtx439) / 4
	.2byte	(.L449 - .Lrtx439) / 4
	.2byte	(.L450 - .Lrtx439) / 4
	.2byte	(.L451 - .Lrtx439) / 4
	.text
.L451:
	add	x19, x19, 270336
	mov	w4, 1
	mov	w3, 6
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 2440]
	str	w2, [x26, 8]
	ldr	w2, [x19, 2448]
	str	w2, [x26, 20]
	ldr	w2, [x19, 2456]
	str	w2, [x26, 24]
	ldr	w2, [x19, 2088]
	str	w2, [x26, 28]
	ldr	w2, [x19, 2092]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 2468]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetVp9MbGroup
	b	.L452
.L438:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetH264RepairParam
	b	.L452
.L440:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetVC1RepairParam
	b	.L452
.L441:
	ldr	w0, [x19, 224]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 232]
	str	w2, [x26, 20]
	ldr	w2, [x19, 240]
	str	w2, [x26, 24]
	ldrh	w2, [x19, 176]
	str	w2, [x26, 28]
	ldrh	w2, [x19, 178]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 14672]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L452
.L442:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetMPEG2RepairParam
	b	.L452
.L443:
	ldr	w0, [x19, 128]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 124]
	str	w2, [x26, 20]
	ldr	w2, [x19, 152]
	str	w2, [x26, 24]
	ldr	w2, [x19, 8]
	str	w2, [x26, 28]
	ldr	w2, [x19, 12]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 160]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetDivx3MbGroup
	b	.L452
.L444:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetAVSRepairParam
	b	.L452
.L445:
	ldr	w0, [x19, 56]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 52]
	str	w2, [x26, 20]
	ldr	w2, [x19, 68]
	str	w2, [x26, 24]
	ldr	w2, [x19, 4]
	str	w2, [x26, 28]
	ldr	w2, [x19, 8]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 76]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L452
.L446:
	ldr	w0, [x19, 52]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 48]
	str	w2, [x26, 20]
	ldr	w2, [x19, 64]
	str	w2, [x26, 24]
	ldr	w2, [x19, 4]
	str	w2, [x26, 28]
	ldr	w2, [x19, 8]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 72]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L452
.L447:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetVP6RepairParam
	b	.L452
.L448:
	ldr	w0, [x19, 3120]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 3132]
	str	w2, [x26, 20]
	ldr	w2, [x19, 3136]
	str	w2, [x26, 24]
	ldr	w2, [x19, 2788]
	str	w2, [x26, 28]
	ldr	w2, [x19, 2792]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 3144]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetVp8MbGroup
	b	.L452
.L449:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetMVCRepairParam
	b	.L452
.L450:
	mov	w3, w22
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetHEVCRepairParam
	b	.L452
.L458:
	mov	w22, 0
	b	.L453
	.size	PostPro_GetRepairParam, .-PostPro_GetRepairParam
	.align	3
.LC45:
	.xword	.L439
	.align	3
.LC46:
	.xword	.LANCHOR0
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetErrRatio
	.type	PostPro_GetErrRatio, %function
PostPro_GetErrRatio:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L472
	ldr	x3, .LC55
	mov	x2, 24
	ldp	w23, w20, [x19]
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x3, 96]
	ldr	x21, [x19, 8]
	sxtw	x19, w23
	blr	x3
	str	w20, [x29, 72]
	lsl	x1, x19, 3
	ldr	x3, .LC58
	sub	x0, x1, x19
	ldr	x2, .LC57
	lsl	x1, x0, 1
	lsl	x0, x0, 3
	sub	x1, x1, x19
	sub	x0, x0, x19
	lsl	x0, x0, 1
	ldr	x3, [x3, 280]
	add	x22, x19, x1, lsl 6
	sub	x0, x0, x19
	sub	x22, x22, x1
	ldr	x19, .LC56
	add	x22, x22, x2
	str	w23, [x29, 88]
	str	x22, [x29, 80]
	add	x19, x19, x0, lsl 4
	cbz	x3, .L470
	add	x0, x29, 72
	blr	x3
.L471:
	mov	w4, w23
	mov	x3, x22
	mov	x1, x19
	mov	x2, x21
	mov	w0, w20
	bl	PostPro_GetRepairParam
	mov	w19, w0
	ldr	x1, .LC62
	mov	w2, w0
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L470:
	ldr	x1, .LC60
	mov	w2, 98
	mov	w0, 0
	bl	dprint_vfmw
	b	.L471
	.p2align 3
.L472:
	ldr	x1, .LC54
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 1
	ldp	x29, x30, [sp], 96
	ret
	.size	PostPro_GetErrRatio, .-PostPro_GetErrRatio
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC55:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC56:
	.xword	g_RepairParam
	.align	3
.LC57:
	.xword	g_DecReport
	.align	3
.LC58:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_SetFullRepair
	.type	PostPro_SetFullRepair, %function
PostPro_SetFullRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w2
	mov	x21, x1
	bl	_mcount
	sxtw	x3, w19
	ldr	x7, .LC63
	lsl	x0, x3, 3
	ldr	x8, .LC64
	sub	x0, x0, x3
	mov	w4, w19
	lsl	x5, x0, 1
	lsl	x0, x0, 3
	sub	x6, x5, x3
	sub	x0, x0, x3
	lsl	x0, x0, 1
	mov	x2, x21
	add	x5, x3, x6, lsl 6
	sub	x1, x0, x3
	sub	x5, x5, x6
	mov	w0, w20
	add	x6, x7, x5
	add	x1, x8, x1, lsl 4
	mov	x3, x6
	mov	w8, 1
	str	w8, [x7, x5]
	str	wzr, [x6, 12]
	bl	PostPro_GetRepairParam
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_SetFullRepair, .-PostPro_SetFullRepair
	.align	3
.LC63:
	.xword	g_DecReport
	.align	3
.LC64:
	.xword	g_RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_SetDecReport
	.type	PostPro_SetDecReport, %function
PostPro_SetDecReport:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	ldr	x3, .LC65
	mov	x2, 820
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	cmp	w20, 17
	bls	.L492
.L475:
	ldr	x2, .LC67
	mov	w3, 2274
	ldr	x1, .LC68
	mov	w0, 0
	bl	dprint_vfmw
.L490:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L492:
	ldr	x0, .LC66
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx477
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx477:
	.section	.rodata
	.align	0
	.align	2
.L477:
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L475 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L482 - .Lrtx477) / 4
	.byte	(.L475 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L475 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.byte	(.L486 - .Lrtx477) / 4
	.text
	.p2align 3
.L482:
	ldrb	w0, [x21, 17]
	cmp	w0, 1
	beq	.L493
.L486:
	strh	wzr, [x19, 16]
	mov	w0, 1
	strh	wzr, [x19, 18]
	str	w0, [x19, 12]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L493:
	strh	wzr, [x19, 16]
	mov	w0, 2
	strh	wzr, [x19, 18]
	str	w0, [x19, 12]
	ldrh	w1, [x21, 74]
	ldrh	w0, [x21, 72]
	mul	w0, w0, w1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	strh	w0, [x19, 20]
	ldrh	w0, [x21, 72]
	ldrh	w1, [x21, 74]
	mul	w0, w0, w1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	strh	w0, [x19, 22]
	b	.L490
	.size	PostPro_SetDecReport, .-PostPro_SetDecReport
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC66:
	.xword	.L477
	.align	3
.LC67:
	.xword	.LANCHOR1
	.align	3
.LC68:
	.xword	.LC47
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11675, %object
	.size	__func__.11675, 31
__func__.11675:
	.string	"PostPro_GetHevcMbGroupOfNoTile"
	.zero	1
	.type	__func__.11618, %object
	.size	__func__.11618, 23
__func__.11618:
	.string	"PostPro_GetRepairParam"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11895, %object
	.size	__func__.11895, 21
__func__.11895:
	.string	"PostPro_SetDecReport"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC7:
	ASCII(.string	"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeight=%d\n" )
	.zero	6
.LC14:
	ASCII(.string	"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	7
.LC19:
	ASCII(.string	"%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC21:
	ASCII(.string	"%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC23:
	ASCII(.string	"DecSliceNum(=%d) out of range!\n" )
.LC25:
	ASCII(.string	"DecSliceNum out of range!\n" )
	.zero	5
.LC27:
	ASCII(.string	"line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC47:
	ASCII(.string	"%s %d VidStd Err!\n" )
	.zero	5
.LC49:
	ASCII(.string	"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0].MbGroup[i].StartMbn=%d\n" )
	.zero	3
.LC51:
	ASCII(.string	"total_mbs=%d,err_mbs=%d\n" )
	.zero	7
.LC53:
	ASCII(.string	"PostPro_GetErrRatio: pParam = NULL\n" )
	.zero	4
.LC59:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC61:
	ASCII(.string	"err_ratio=%d\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
