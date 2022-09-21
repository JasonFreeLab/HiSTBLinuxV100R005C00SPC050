#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Write_V5R6C1_CabacTab
	.type	Write_V5R6C1_CabacTab, %function
Write_V5R6C1_CabacTab:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L5
	ldr	x3, .LC2
	mov	x2, 5120
	ldr	x1, .LC3
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L3:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L5:
	ldr	x1, .LC1
	mov	w2, 114
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3
	.size	Write_V5R6C1_CabacTab, .-Write_V5R6C1_CabacTab
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC2:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC3:
	.xword	g_CabacMN
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_InitHal
	.type	H264HAL_V5R6C1_InitHal, %function
H264HAL_V5R6C1_InitHal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 1104]
	bl	Write_V5R6C1_CabacTab
	cbnz	w0, .L11
.L7:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L11:
	ldr	x1, .LC5
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L7
	.size	H264HAL_V5R6C1_InitHal, .-H264HAL_V5R6C1_InitHal
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R6C1_VirAddr
	.type	Get_V5R6C1_VirAddr, %function
Get_V5R6C1_VirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x19, x20, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_V5R6C1_VirAddr, .-Get_V5R6C1_VirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R6C1_PhyAddr
	.type	Get_V5R6C1_PhyAddr, %function
Get_V5R6C1_PhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	w0, w19, w20, lsl 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_V5R6C1_PhyAddr, .-Get_V5R6C1_PhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_CutSliceChain
	.type	H264HAL_V5R6C1_CutSliceChain, %function
H264HAL_V5R6C1_CutSliceChain:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L17
	str	wzr, [x0, 252]
	mov	w0, 0
.L16:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L17:
	ldr	x3, .LC7
	ldr	x2, .LC8
	ldr	x1, .LC10
	bl	dprint_vfmw
	mov	w0, -1
	b	.L16
	.size	H264HAL_V5R6C1_CutSliceChain, .-H264HAL_V5R6C1_CutSliceChain
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC8:
	.xword	.LANCHOR0
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Write_V5R6C1_Qmatrix
	.type	Write_V5R6C1_Qmatrix, %function
Write_V5R6C1_Qmatrix:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	w23, w1
	mov	x0, x30
	mov	w20, w2
	mov	x22, x3
	bl	_mcount
	cbz	w23, .L18
	sub	w23, w23, #1
	ldr	x25, .LC14
	ldr	x24, .LC16
	add	x23, x23, 1
	mov	x19, 0
	.p2align 2
.L20:
	ldr	w0, [x21, x19, lsl 2]
	mov	w2, w19
	str	w0, [x22, x19, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w3, [x21, x19, lsl 2]
	bl	dprint_vfmw
	ldr	w3, [x22, x19, lsl 2]
	mov	w2, w20
	mov	w0, 4
	mov	x1, x24
	add	x19, x19, 1
	add	w20, w20, w0
	bl	dprint_vfmw
	cmp	x19, x23
	bne	.L20
.L18:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	Write_V5R6C1_Qmatrix, .-Write_V5R6C1_Qmatrix
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgStreamAddrInfo
	.type	H264HAL_SetSliceMsgStreamAddrInfo, %function
H264HAL_SetSliceMsgStreamAddrInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	mov	x21, x2
	mov	x22, x1
	mov	w20, w3
	mov	x23, x2
	bl	_mcount
	ldr	x25, .LC20
	ldr	x26, .LC18
	add	x22, x22, 8
	add	x21, x21, 4
	add	w20, w20, 4
	add	x24, x23, 8
	mov	w19, 0
.L26:
	ldr	w4, [x22]
	add	w6, w19, 1
	str	w6, [x29, 108]
	mov	x1, x26
	mov	w2, w6
	mov	w0, 4
	sub	w3, w20, #4
	cbz	w4, .L24
	ldr	w28, [x22, 16]
	ldr	w4, [x22, 8]
	ldr	w8, [x27, 736]
	mov	w5, w28
	add	w7, w4, w28, lsl 3
	and	w28, w28, -16
	and	w7, w7, 127
	and	w8, w8, -16
	mov	w3, w7
	stp	w8, w7, [x29, 100]
	bl	dprint_vfmw
	ldp	w7, w6, [x29, 104]
	str	w7, [x21]
	mov	w3, w20
	mov	w2, w6
	mov	x1, x25
	ldr	w4, [x21]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x22]
	add	w3, w20, 4
	str	w0, [x24]
	add	w2, w19, 2
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x24]
	bl	dprint_vfmw
	ldr	w8, [x29, 100]
	sub	w3, w20, #4
	mov	w2, w19
	mov	x1, x25
	sub	w28, w28, w8
	str	w28, [x23]
	mov	w0, 4
	ldr	w4, [x23]
	bl	dprint_vfmw
.L25:
	add	w19, w19, 3
	add	x22, x22, 4
	cmp	w19, 6
	add	x21, x21, 12
	add	x23, x23, 12
	add	w20, w20, 12
	add	x24, x24, 12
	bne	.L26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L24:
	str	wzr, [x23]
	mov	w2, w19
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x23]
	bl	dprint_vfmw
	str	wzr, [x21]
	mov	w3, w20
	add	w2, w19, 1
	ldr	w4, [x21]
	mov	x1, x25
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x24]
	add	w3, w20, 4
	add	w2, w19, 2
	ldr	w4, [x24]
	mov	x1, x25
	mov	w0, 4
	bl	dprint_vfmw
	b	.L25
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgMvAddrInfo
	.type	H264HAL_SetSliceMsgMvAddrInfo, %function
H264HAL_SetSliceMsgMvAddrInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	x19, x2
	mov	w20, w3
	bl	_mcount
	ldr	x0, .LC21
	ldrb	w1, [x21]
	add	x0, x0, 32
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L36
	mov	w3, 0
	mov	w0, 0
.L29:
	str	w0, [x19, 32]
	add	w2, w20, 32
	str	w3, [x19, 36]
	mov	w0, 4
	ldr	w3, [x19, 32]
	ldr	x1, .LC25
	bl	dprint_vfmw
	ldr	w3, [x19, 36]
	add	w2, w20, 36
	ldr	x1, .LC27
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L36:
	ldr	x1, .LC23
	mov	w0, 4
	ldr	w2, [x21, 2788]
	bl	dprint_vfmw
	ldrb	w0, [x22]
	cbnz	w0, .L30
	ldrb	w0, [x21, 2778]
	cmp	w0, 3
	ldr	w0, [x21, 2788]
	beq	.L37
.L35:
	add	x22, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x22, 584]
	and	w0, w0, -16
	b	.L29
	.p2align 3
.L30:
	ldr	w0, [x21, 2776]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L38
	ldrb	w0, [x21, 2776]
	cmp	w0, 1
	ldr	w0, [x21, 2788]
	beq	.L35
	ldr	w1, [x22, 716]
	add	x22, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x22, 584]
	add	w0, w0, w1
	and	w0, w0, -16
	b	.L29
	.p2align 3
.L37:
	ldr	w3, [x22, 716]
	add	x22, x22, x0, lsl 2
	ldr	w0, [x22, 584]
	add	w3, w0, w3
	and	w0, w0, -16
	and	w3, w3, -16
	b	.L29
	.p2align 3
.L38:
	ldr	w0, [x21, 2788]
	b	.L35
	.size	H264HAL_SetSliceMsgMvAddrInfo, .-H264HAL_SetSliceMsgMvAddrInfo
	.align	3
.LC21:
	.xword	.LANCHOR0
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgEndMbInSlice
	.type	H264HAL_SetSliceMsgEndMbInSlice, %function
H264HAL_SetSliceMsgEndMbInSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x1
	mov	x22, x0
	mov	x0, x30
	mov	x21, x2
	mov	w19, w3
	bl	_mcount
	ldr	x0, [x20, 4056]
	cbz	x0, .L40
	mov	w3, w19
.L41:
	str	w3, [x21, 176]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L40:
	ldr	w4, [x22, 740]
	ldrb	w0, [x20, 1]
	cmp	w4, 262144
	ble	.L43
	add	w3, w0, 1
	mov	w1, 262143
	sdiv	w3, w1, w3
	b	.L41
	.p2align 3
.L43:
	sub	w4, w4, #1
	add	w3, w0, 1
	sdiv	w3, w4, w3
	b	.L41
	.size	H264HAL_SetSliceMsgEndMbInSlice, .-H264HAL_SetSliceMsgEndMbInSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicFrame
	.type	H264HAL_SetSliceMsgRefPicFrame, %function
H264HAL_SetSliceMsgRefPicFrame:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x7, x0
	mov	x0, x30
	mov	w26, w4
	add	w28, w4, 3
	stp	x7, x1, [x29, 104]
	mov	x20, x2
	str	w3, [x29, 124]
	bl	_mcount
	lsl	w28, w28, 2
	uxtw	x0, w26
	ldr	x6, [x29, 112]
	lsl	w26, w26, 3
	add	x21, x6, x0, lsl 2
	add	w26, w26, 20
	ldr	w1, [x21, 52]
	cbz	w1, .L47
	lsl	x27, x0, 10
	mov	w19, 0
	mov	w24, 0
	add	x27, x27, x0, lsl 7
	ldr	x22, .LC29
	mov	w25, 0
	mov	w23, 8
	ldr	x7, [x29, 104]
	b	.L53
	.p2align 3
.L51:
	cmp	w10, 3
	beq	.L60
.L52:
	ldr	w0, [x21, 52]
	cmp	w0, w19
	bls	.L61
.L53:
	uxtw	x0, w19
	ldr	w4, [x7, 48]
	lsl	x1, x0, 5
	add	x12, x22, 48
	add	x0, x1, x0, lsl 2
	and	w10, w19, 3
	add	x0, x0, x27
	and	w3, w19, 7
	add	x0, x6, x0
	lsl	w11, w3, 2
	add	w13, w10, w10, lsl 2
	add	w19, w19, 1
	ldrb	w1, [x0, 1626]
	ldrb	w14, [x0, 1627]
	ldr	w2, [x0, 1644]
	add	x4, x4, x1, lsl 1
	cmp	w14, 1
	csel	w1, w23, wzr, eq
	ubfiz	w2, w2, 1, 4
	cmp	w3, 7
	lsl	w2, w2, w13
	ldr	w0, [x12, x4, lsl 2]
	orr	w24, w24, w2
	and	w0, w0, 3
	orr	w0, w0, w1
	lsl	w0, w0, w11
	orr	w25, w25, w0
	bne	.L51
	str	w25, [x20, w28, uxtw 2]
	mov	w2, w28
	ldr	w0, [x29, 124]
	mov	w25, 0
	ldr	w4, [x20, w28, uxtw 2]
	ldr	x1, .LC31
	add	w3, w0, w28, lsl 2
	mov	w0, 4
	str	w10, [x29, 112]
	stp	x6, x7, [x29, 96]
	bl	dprint_vfmw
	add	w28, w28, 1
	ldr	w10, [x29, 112]
	ldp	x6, x7, [x29, 96]
	cmp	w10, 3
	bne	.L52
	.p2align 2
.L60:
	str	w24, [x20, w26, uxtw 2]
	mov	w2, w26
	ldr	w0, [x29, 124]
	mov	w24, 0
	ldr	w4, [x20, w26, uxtw 2]
	ldr	x1, .LC31
	add	w3, w0, w26, lsl 2
	mov	w0, 4
	add	w26, w26, 1
	stp	x6, x7, [x29, 104]
	bl	dprint_vfmw
	ldr	w0, [x21, 52]
	ldp	x6, x7, [x29, 104]
	cmp	w0, w19
	bhi	.L53
	.p2align 2
.L61:
	and	w0, w0, 7
	cbnz	w0, .L62
.L47:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L62:
	str	w25, [x20, w28, uxtw 2]
	mov	w2, w28
	ldr	w21, [x29, 124]
	mov	w0, 4
	ldr	x19, .LC31
	ldr	w4, [x20, w28, uxtw 2]
	add	w3, w21, w28, lsl 2
	mov	x1, x19
	bl	dprint_vfmw
	str	w24, [x20, w26, uxtw 2]
	add	w3, w21, w26, lsl 2
	mov	w2, w26
	ldr	w4, [x20, w26, uxtw 2]
	mov	x1, x19
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	H264HAL_SetSliceMsgRefPicFrame, .-H264HAL_SetSliceMsgRefPicFrame
	.align	3
.LC29:
	.xword	.LANCHOR0
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicField
	.type	H264HAL_SetSliceMsgRefPicField, %function
H264HAL_SetSliceMsgRefPicField:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w4
	mov	x21, x1
	mov	x19, x2
	str	w3, [x29, 108]
	bl	_mcount
	uxtw	x0, w22
	add	w10, w22, 3
	lsl	w7, w22, 3
	lsl	w25, w10, 2
	add	x23, x21, x0, lsl 2
	add	w27, w7, 20
	ldr	w1, [x23, 52]
	cbz	w1, .L63
	lsl	x5, x0, 10
	mov	w28, 0
	mov	w26, 0
	ldr	x22, .LC33
	add	x24, x5, x0, lsl 7
	mov	w9, 0
	b	.L83
	.p2align 3
.L66:
	cmp	w2, 2
	beq	.L74
	and	w12, w28, 3
	and	w0, w28, 7
.L73:
	cmp	w0, 7
	beq	.L99
.L81:
	cmp	w12, 3
	beq	.L100
.L82:
	ldr	w0, [x23, 52]
	add	w28, w28, 1
	cmp	w0, w28
	bls	.L101
.L83:
	uxtw	x1, w28
	lsl	x0, x1, 5
	add	x0, x0, x1, lsl 2
	add	x0, x0, x24
	add	x0, x21, x0
	ldrb	w2, [x0, 1624]
	cmp	w2, 1
	bne	.L66
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L67
	ldrb	w4, [x0, 1629]
	mov	w2, 8
	ldrb	w3, [x0, 1628]
	mov	w0, 4
	cmp	w4, 1
	csel	w2, wzr, w2, ne
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	sbfiz	x3, x3, 1, 32
	orr	w0, w2, w0
	ldr	w2, [x20, 48]
	add	x3, x3, x2
	ldr	x2, .LC33
	add	x2, x2, 80
	ldr	w2, [x2, x3, lsl 2]
	and	w2, w2, 3
.L97:
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	and	w12, w28, 3
	lsl	w2, w2, w3
	cmp	w0, 7
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	lsl	w1, w1, w2
	orr	w26, w26, w1
	bne	.L81
.L99:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w0, [x29, 108]
	ldr	w4, [x19, w25, uxtw 2]
	ldr	x1, .LC34
	add	w3, w0, w25, lsl 2
	mov	w0, 4
	str	w12, [x29, 104]
	add	w25, w25, 1
	bl	dprint_vfmw
	ldr	w12, [x29, 104]
	mov	w9, 0
	cmp	w12, 3
	bne	.L82
	.p2align 2
.L100:
	str	w26, [x19, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 108]
	add	w28, w28, 1
	ldr	w4, [x19, w27, uxtw 2]
	mov	w26, 0
	ldr	x1, .LC34
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	w9, [x29, 104]
	add	w27, w27, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 52]
	ldr	w9, [x29, 104]
	cmp	w0, w28
	bhi	.L83
	.p2align 2
.L101:
	and	w0, w0, 7
	cbnz	w0, .L102
.L63:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L74:
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L75
	ldrb	w4, [x0, 1630]
	ldrb	w0, [x0, 1631]
	sbfiz	x2, x4, 1, 32
	cmp	w0, 1
	ldr	w0, [x20, 48]
	add	x0, x2, x0
	ldr	x2, .LC33
	add	x2, x2, 80
	ldr	w2, [x2, x0, lsl 2]
.L98:
	mov	w0, 8
	and	w2, w2, 3
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w12, w28, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	lsl	w2, w2, w3
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	orr	w1, w1, 1
	lsl	w1, w1, w2
	orr	w26, w26, w1
	b	.L73
	.p2align 3
.L67:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20, 48]
	ldrb	w4, [x0, 1628]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1629]
	ldr	x0, .LC33
	cmp	w3, 1
	add	x0, x0, 80
	ldr	w2, [x0, x2, lsl 2]
	mov	w0, 8
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w2, w2, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	b	.L97
	.p2align 3
.L75:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20, 48]
	ldrb	w4, [x0, 1630]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1631]
	add	x0, x22, 80
	cmp	w3, 1
	ldr	w2, [x0, x2, lsl 2]
	b	.L98
	.p2align 3
.L102:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w21, [x29, 108]
	mov	w0, 4
	ldr	x20, .LC34
	ldr	w4, [x19, w25, uxtw 2]
	add	w3, w21, w25, lsl 2
	mov	x1, x20
	bl	dprint_vfmw
	str	w26, [x19, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	ldr	w4, [x19, w27, uxtw 2]
	mov	x1, x20
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	H264HAL_SetSliceMsgRefPicField, .-H264HAL_SetSliceMsgRefPicField
	.align	3
.LC33:
	.xword	.LANCHOR0
	.align	3
.LC34:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicInfo
	.type	H264HAL_SetSliceMsgRefPicInfo, %function
H264HAL_SetSliceMsgRefPicInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	ldrb	w0, [x19]
	mov	w4, 0
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	cbnz	w0, .L104
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicFrame
	ldr	x0, .LC36
	ldrb	w1, [x20]
	add	x0, x0, 32
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L108
.L103:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L104:
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicField
	ldr	x0, .LC36
	ldrb	w1, [x20]
	add	x0, x0, 32
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L103
	mov	w4, 1
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicField
	b	.L103
	.p2align 3
.L108:
	mov	w4, 1
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicFrame
	b	.L103
	.size	H264HAL_SetSliceMsgRefPicInfo, .-H264HAL_SetSliceMsgRefPicInfo
	.align	3
.LC36:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgAPCInfo
	.type	H264HAL_SetSliceMsgAPCInfo, %function
H264HAL_SetSliceMsgAPCInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x1
	mov	x0, x30
	mov	x21, x2
	mov	w23, w3
	bl	_mcount
	ldr	x22, .LC38
	ldr	w2, [x19, 3928]
	add	x20, x19, 3932
	mov	w24, 36
	mov	w19, 0
	and	w2, w2, 31
	.p2align 2
.L110:
	add	w19, w19, 1
	and	w1, w19, 3
	cmp	w19, 32
	add	w3, w1, w1, lsl 2
	beq	.L113
.L112:
	ldr	w0, [x20]
	cmp	w1, 3
	add	x20, x20, 4
	and	w0, w0, 31
	lsl	w0, w0, w3
	orr	w2, w2, w0
	bne	.L110
	str	w2, [x21, w24, uxtw 2]
	add	w3, w23, w24, lsl 2
	mov	w2, w24
	mov	x1, x22
	ldr	w4, [x21, w24, uxtw 2]
	mov	w0, 4
	add	w19, w19, 1
	add	w24, w24, 1
	bl	dprint_vfmw
	and	w1, w19, 3
	cmp	w19, 32
	mov	w2, 0
	add	w3, w1, w1, lsl 2
	bne	.L112
.L113:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	H264HAL_SetSliceMsgAPCInfo, .-H264HAL_SetSliceMsgAPCInfo
	.align	3
.LC38:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgWPInfo
	.type	H264HAL_SetSliceMsgWPInfo, %function
H264HAL_SetSliceMsgWPInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x24, x2
	str	w3, [x29, 108]
	bl	_mcount
	ldr	w0, [x20, 300]
	cbz	w0, .L115
	ldr	x28, .LC39
	ldrb	w1, [x19]
	add	x0, x28, 32
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 1
	beq	.L116
.L115:
	ldr	w0, [x20, 304]
	cmp	w0, 1
	beq	.L145
.L114:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L145:
	ldr	x28, .LC39
	ldrb	w1, [x19]
	add	x0, x28, 32
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L114
.L116:
	ldr	w3, [x29, 108]
	mov	w0, 4
	ldr	x1, .LC41
	add	x25, x24, 256
	ldr	w2, [x19, 44]
	add	w22, w3, 256
	add	x26, x24, 512
	mov	w20, 0
	add	x24, x24, 768
	bl	dprint_vfmw
	ldr	x23, .LC42
	.p2align 2
.L119:
	add	x21, x19, x20, uxtw 2
	ldr	w4, [x19, 80]
	mov	w3, w22
	add	w2, w20, 64
	and	w5, w4, 7
	mov	x1, x23
	ldrb	w6, [x21, 856]
	mov	w0, 4
	ldr	w4, [x21, 88]
	ubfiz	w4, w4, 3, 9
	orr	w4, w4, w6, lsl 12
	orr	w4, w4, w5
	str	w4, [x25, w20, uxtw 2]
	ldr	w4, [x25, w20, uxtw 2]
	bl	dprint_vfmw
	ldrb	w1, [x21, 984]
	add	w3, w22, 256
	ldr	w0, [x21, 216]
	add	w2, w20, 128
	ldr	w4, [x19, 84]
	ubfiz	w0, w0, 3, 9
	and	w4, w4, 7
	orr	w0, w0, w1, lsl 12
	orr	w0, w0, w4
	str	w0, [x26, w20, uxtw 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x26, w20, uxtw 2]
	bl	dprint_vfmw
	ldrb	w5, [x21, 1112]
	add	w3, w22, 512
	ldr	w4, [x21, 344]
	add	w2, w20, 192
	mov	w0, 4
	mov	x1, x23
	and	w4, w4, 511
	add	w22, w22, w0
	orr	w4, w4, w5, lsl 9
	str	w4, [x24, w20, uxtw 2]
	ldr	w4, [x24, w20, uxtw 2]
	add	w20, w20, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L119
	ldr	x1, .LC44
	mov	w0, 4
	ldr	w2, [x19, 80]
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x22, .LC46
	ldr	x21, .LC48
	.p2align 2
.L120:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 88]
	bl	dprint_vfmw
	ldr	w2, [x27, 856]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L120
	add	x0, x28, 32
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L121
.L124:
	ldr	x1, .LC50
	mov	w0, 4
	ldr	w2, [x19, 84]
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x22, .LC56
	ldr	x21, .LC58
	.p2align 2
.L122:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 216]
	bl	dprint_vfmw
	ldr	w2, [x27, 984]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L122
	add	x0, x28, 32
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L125
.L128:
	ldr	x22, .LC64
	mov	w20, 0
	ldr	x21, .LC66
	.p2align 2
.L126:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 344]
	bl	dprint_vfmw
	ldr	w2, [x27, 1112]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L126
	add	x0, x28, 32
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L114
	ldr	x22, .LC68
	mov	w20, 0
	ldr	x27, .LC70
	.p2align 2
.L129:
	add	x21, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x21, 728]
	bl	dprint_vfmw
	ldr	w2, [x21, 1496]
	mov	x1, x27
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w2, [x19, 40]
	cmp	w20, w2
	bls	.L129
	add	x28, x28, 32
	ldrb	w0, [x19]
	ldr	w0, [x28, w0, sxtw 2]
	cmp	w0, 2
	bne	.L114
	ldr	w3, [x29, 108]
	mov	w0, 4
	ldr	x1, .LC72
	mov	w21, 0
	add	w27, w3, 384
	bl	dprint_vfmw
	.p2align 2
.L130:
	uxtw	x20, w21
	mov	w3, w27
	add	x22, x20, 32
	add	x20, x19, x20, lsl 2
	ldrb	w2, [x20, 1240]
	ldr	w0, [x20, 472]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x19, 80]
	add	w2, w21, 96
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x25, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x25, x22, lsl 2]
	bl	dprint_vfmw
	ldrb	w2, [x20, 1368]
	add	w3, w27, 256
	ldr	w0, [x20, 600]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x19, 84]
	add	w2, w21, 160
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x26, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x26, x22, lsl 2]
	bl	dprint_vfmw
	ldrb	w1, [x20, 1496]
	add	w3, w27, 512
	ldr	w0, [x20, 728]
	add	w2, w21, 224
	add	w21, w21, 1
	add	w27, w27, 4
	and	w0, w0, 511
	orr	w0, w0, w1, lsl 9
	str	w0, [x24, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x24, x22, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w21, w0
	bls	.L130
	b	.L114
	.p2align 3
.L125:
	ldr	x22, .LC60
	mov	w20, 0
	ldr	x21, .LC62
	.p2align 2
.L127:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 600]
	bl	dprint_vfmw
	ldr	w2, [x27, 1368]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w20, w0
	bls	.L127
	b	.L128
	.p2align 3
.L121:
	ldr	x22, .LC52
	mov	w20, 0
	ldr	x21, .LC54
	.p2align 2
.L123:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 472]
	bl	dprint_vfmw
	ldr	w2, [x27, 1240]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w20, w0
	bls	.L123
	b	.L124
	.size	H264HAL_SetSliceMsgWPInfo, .-H264HAL_SetSliceMsgWPInfo
	.align	3
.LC39:
	.xword	.LANCHOR0
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	.LC30
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
.LC56:
	.xword	.LC55
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.align	3
.LC72:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_CheckParaValid
	.type	H264HAL_CheckParaValid, %function
H264HAL_CheckParaValid:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L154
	cbz	x19, .L155
	ldr	w0, [x19, 44]
	cmp	w0, 512
	bhi	.L151
	ldr	w0, [x19, 36]
	cmp	w0, 512
	bhi	.L151
	ldr	x1, [x19, 944]
	mov	w0, 0
	cbz	x1, .L156
.L148:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L154:
	ldr	x2, .LC74
	mov	w4, 0
	ldr	x1, .LC76
	mov	w3, w20
	add	x2, x2, 112
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L148
	.p2align 3
.L151:
	ldr	x2, .LC74
	ldr	x3, .LC81
.L153:
	ldr	x1, .LC79
	mov	w0, 0
	add	x2, x2, 112
	bl	dprint_vfmw
	mov	w0, -1
	b	.L148
.L155:
	ldr	x2, .LC74
	ldr	x3, .LC78
	b	.L153
.L156:
	ldr	x2, .LC74
	ldr	x3, .LC83
	ldr	x1, .LC79
	add	x2, x2, 112
	bl	dprint_vfmw
	mov	w0, -1
	b	.L148
	.size	H264HAL_CheckParaValid, .-H264HAL_CheckParaValid
	.align	3
.LC74:
	.xword	.LANCHOR0
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC79:
	.xword	.LC9
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_GetVdmRegVirAddr
	.type	H264HAL_GetVdmRegVirAddr, %function
H264HAL_GetVdmRegVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L164
	cmp	w19, 1
	mov	w0, -104529920
	beq	.L159
	ldr	x1, .LC85
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L164:
	mov	w0, -121438208
.L159:
	ldr	x1, [x20]
	cbz	x1, .L162
.L163:
	mov	w0, 0
.L161:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L162:
	bl	MEM_Phy2Vir
	str	x0, [x20]
	cbnz	x0, .L163
	ldr	x1, .LC87
	bl	dprint_vfmw
	mov	w0, -1
	b	.L161
	.size	H264HAL_GetVdmRegVirAddr, .-H264HAL_GetVdmRegVirAddr
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC87:
	.xword	.LC86
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_CfgVdmReg
	.type	H264HAL_V5R6C1_CfgVdmReg, %function
H264HAL_V5R6C1_CfgVdmReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w2
	mov	x22, x3
	mov	x24, x1
	bl	_mcount
	ldr	x1, .LC89
	sbfiz	x0, x23, 6, 32
	ldr	x2, .LC88
	cmp	x22, xzr
	ldrb	w1, [x1]
	add	x0, x2, x0
	ccmp	w1, 1, 4, eq
	ldr	w2, [x0, 8]
	bne	.L190
	ldr	x0, .LC93
	ldr	x0, [x0, w2, sxtw 3]
	cbz	x0, .L178
	ldr	w21, [x0, 1272]
	uxtb	w0, w21
	and	w25, w0, 1
.L169:
	cmp	w1, 1
	beq	.L170
	strb	w0, [x22, 1]
.L170:
	ldr	w2, [x20, 1188]
	mov	w0, 262143
	ldr	w1, [x20, 740]
	cmp	w2, 1
	str	wzr, [x29, 92]
	csetm	w4, eq
	cmp	w1, 262144
	and	w4, w4, 3
	uxtb	w4, w4
	bgt	.L171
	sub	w0, w1, #1
	and	w0, w0, 1048575
.L171:
	ldr	w1, [x29, 92]
	mov	x3, x22
	mov	w2, w23
	bfi	w1, w0, 0, 20
	str	w1, [x29, 92]
	ubfx	x0, x1, 24, 6
	ubfx	x1, x1, 16, 6
	orr	w0, w0, 64
	strb	w1, [x29, 94]
	orr	w0, w0, 1
	and	w0, w0, -3
	bfi	w0, w4, 2, 2
	strb	w0, [x29, 95]
	mov	w0, 8
	ldr	w19, [x29, 92]
	str	w19, [x20, 960]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC95
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	strb	wzr, [x29, 92]
	ldrb	w2, [x20, 16]
	mov	w0, 0
	ldrb	w1, [x20, 2]
	bfi	w0, w2, 4, 1
	mov	w2, 1
	bfi	w0, w1, 6, 1
	strh	w2, [x29, 94]
	mov	w1, 0
	ldrb	w2, [x20, 3]
	orr	w0, w0, -128
	bfi	w1, w25, 4, 1
	strb	w0, [x29, 93]
	strb	w1, [x29, 95]
	cbz	w2, .L172
	ldr	w0, [x20, 44]
	lsl	w0, w0, 4
	cmp	w0, 1920
	bhi	.L173
.L172:
	ldrb	w0, [x29, 95]
	mov	w1, 0
	strb	wzr, [x20, 4]
	and	w0, w0, -33
	strb	w0, [x29, 95]
.L174:
	ldrb	w0, [x29, 95]
	mov	x3, x22
	strb	wzr, [x20, 17]
	mov	w2, w23
	bfi	w0, w1, 6, 1
	and	w0, w0, 127
	strb	w0, [x29, 95]
	mov	w0, 12
	ldr	w19, [x29, 92]
	str	w19, [x20, 964]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC97
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x24, 72]
	mov	x3, x22
	mov	w0, 16
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 968]
	bl	MFDE_ConfigReg
	ldr	x1, .LC99
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x24, 56]
	mov	x3, x22
	mov	w0, 20
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 972]
	bl	MFDE_ConfigReg
	ldr	x1, .LC101
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 736]
	mov	x3, x22
	mov	w0, 24
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 976]
	str	w19, [x29, 92]
	bl	MFDE_ConfigReg
	ldr	x1, .LC103
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	mov	w1, 0
	cmp	w0, 256
	bhi	.L175
	cmp	w0, 119
	mov	w1, 1
	bhi	.L191
.L175:
	mov	x3, x22
	mov	w2, w23
	mov	w0, 4
	mov	w19, 3075
	movk	w19, 0x30, lsl 16
	bl	SCD_ConfigReg
	str	w19, [x29, 92]
	mov	w0, 60
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w21, 1
	beq	.L192
.L176:
	ldr	w1, [x20, 308]
	mov	x3, x22
	mov	w0, 96
	mov	w2, w23
	mov	w21, 0
	add	x1, x20, x1, lsl 2
	ldr	w19, [x1, 324]
	and	w19, w19, -16
	str	w19, [x20, 1012]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC110
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 720]
	mov	x3, x22
	mov	w0, 100
	mov	w1, w19
	mov	w2, w23
	str	w19, [x20, 1016]
	bl	MFDE_ConfigReg
	ldr	x1, .LC112
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 320]
	mov	x3, x22
	mov	w0, 104
	mov	w1, w19
	mov	w2, w23
	str	w19, [x20, 1020]
	bl	MFDE_ConfigReg
	ldr	x1, .LC114
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 732]
	mov	x3, x22
	mov	w0, 108
	mov	w1, w19
	mov	w2, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC116
	mov	w2, w19
	mov	w0, 3
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w25, [x24, 1180]
	mov	x3, x22
	mov	w0, 128
	and	w25, w25, -16
	mov	w2, w23
	mov	w1, w25
	str	w25, [x20, 1036]
	bl	MFDE_ConfigReg
	ldr	x1, .LC118
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	str	wzr, [x29, 92]
	ldr	w0, [x24, 1184]
	mov	x3, x22
	strh	w0, [x29, 92]
	mov	w2, w23
	mov	w0, 132
	ldr	w24, [x29, 92]
	str	w24, [x20, 1040]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC120
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	add	x1, x20, 1056
	.p2align 2
.L177:
	ldr	w0, [x1], 4
	and	w0, w0, 3
	lsl	w0, w0, w19
	add	w19, w19, 2
	cmp	w19, 32
	orr	w21, w0, w21
	bne	.L177
	mov	x3, x22
	mov	w1, w21
	mov	w0, 148
	mov	w2, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC122
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x22
	mov	w2, w23
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC124
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, w19
	mov	x3, x22
	mov	w2, w23
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L168:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L191:
	ldr	w0, [x20, 1184]
	cmp	w0, wzr
	cset	w1, eq
	b	.L175
	.p2align 3
.L173:
	ldrb	w0, [x20, 4]
	and	w1, w1, -33
	strb	w1, [x29, 95]
	and	w1, w0, 1
	b	.L174
.L178:
	mov	w25, 0
	mov	w0, 0
	mov	w21, 0
	b	.L169
.L192:
	ldr	x1, .LC104
	mov	x3, x22
	mov	w2, w23
	mov	w0, 92
	ldr	w19, [x1]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC106
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w1, [x20, 308]
	mov	w2, w23
	mov	w0, 112
	mov	x3, x22
	add	x1, x20, x1, lsl 2
	ldr	w19, [x1, 452]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC108
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	b	.L176
.L190:
	ldr	x2, .LC90
	mov	x3, x22
	ldr	x1, .LC92
	mov	w0, 0
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w0, -1
	b	.L168
	.size	H264HAL_V5R6C1_CfgVdmReg, .-H264HAL_V5R6C1_CfgVdmReg
	.align	3
.LC88:
	.xword	g_VdmDrvParam
	.align	3
.LC89:
	.xword	g_HalDisable
	.align	3
.LC90:
	.xword	.LANCHOR0
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC93:
	.xword	s_pstVfmwChan
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC104:
	.xword	g_TunnelLineNumber
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC124:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_FindNextSlicePara
	.type	H264HAL_FindNextSlicePara, %function
H264HAL_FindNextSlicePara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x22, x3
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	bl	_mcount
	ldr	w1, [x19, 48]
	cmp	w20, w21
	str	w20, [x22]
	bge	.L194
	ldr	x19, [x19, 4056]
	cbz	x19, .L197
	ldr	w0, [x19, 48]
	cmp	w1, w0
	bcc	.L194
	add	w2, w20, 1
	b	.L196
	.p2align 3
.L198:
	ldr	x19, [x19, 4056]
	cbz	x19, .L197
	ldr	w0, [x19, 48]
	cmp	w1, w0
	bcc	.L194
.L196:
	cmp	w21, w2
	str	w2, [x22]
	add	w2, w2, 1
	bne	.L198
.L194:
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L197:
	ldr	x1, .LC126
	mov	w2, 882
	mov	w0, 1
	mov	x19, 0
	bl	dprint_vfmw
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	H264HAL_FindNextSlicePara, .-H264HAL_FindNextSlicePara
	.align	3
.LC126:
	.xword	.LC125
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_SetPicMsg
	.type	H264HAL_V5R6C1_SetPicMsg, %function
H264HAL_V5R6C1_SetPicMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w2
	mov	w21, w3
	str	x1, [x29, 96]
	bl	_mcount
	add	w1, w23, 112
	mov	w0, w23
	str	w1, [x29, 108]
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L234
	ldp	w3, w2, [x20, 52]
	ldr	w0, [x20, 32]
	mov	w1, -2147483648
	lsl	w2, w2, 27
	ldr	w5, [x20, 60]
	cmp	w0, wzr
	csel	w0, w0, w1, eq
	orr	w1, w2, w3, lsl 28
	ldrb	w2, [x20, 1]
	ldr	w3, [x20, 48]
	cmp	w2, 1
	ldrb	w2, [x20]
	add	x3, x3, x2, lsl 1
	ldr	x2, .LC129
	add	x2, x2, 200
	ldr	w4, [x2, x3, lsl 2]
	ldr	w3, [x20, 36]
	sub	w3, w3, #1
	lsl	w3, w3, 16
	orr	w3, w3, w4, lsl 14
	ldr	w4, [x20, 44]
	sub	w4, w4, #1
	orr	w4, w4, w5, lsl 26
	orr	w2, w4, w1
	ldr	x1, .LC132
	orr	w4, w3, w2
	mov	w3, 33554432
	csel	w3, wzr, w3, ne
	mov	w2, w23
	orr	w0, w0, w3
	orr	w0, w4, w0
	str	w0, [x19]
	mov	w0, 4
	ldr	w3, [x19]
	bl	dprint_vfmw
	ldr	w0, [x20, 312]
	add	w2, w23, 4
	ldr	x1, .LC134
	and	w0, w0, -16
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w3, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x20, 64]
	add	w2, w23, 8
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	x1, .LC136
	ldr	w3, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cbnz	w0, .L235
	str	wzr, [x19, 12]
	add	w2, w23, 12
	ldr	x1, .LC138
	mov	w0, 4
	ldr	w3, [x19, 12]
	str	wzr, [x19, 16]
.L232:
	bl	dprint_vfmw
	ldr	x1, .LC140
	add	w2, w23, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	x22, [x29, 96]
	ldr	x1, .LC142
	add	w2, w23, 20
	mov	w0, 4
	ldr	w3, [x22, 1160]
	and	w3, w3, -16
	str	w3, [x19, 20]
	ldr	w3, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x22, 1164]
	add	w2, w23, 24
	ldr	x1, .LC144
	and	w0, w0, -16
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	w3, [x19, 24]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	cmp	w0, 2
	beq	.L209
	ldr	w0, [x20, 316]
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 584]
	and	w0, w0, -16
.L210:
	str	w0, [x19, 28]
	add	w2, w23, 28
	ldr	x1, .LC146
	mov	w0, 4
	ldr	w3, [x19, 28]
	and	w21, w21, -16
	bl	dprint_vfmw
	ldr	x0, [x29, 96]
	add	w2, w23, 32
	ldr	x1, .LC148
	ldr	w0, [x0, 1168]
	and	w0, w0, -16
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	w3, [x19, 32]
	bl	dprint_vfmw
	str	w21, [x19, 36]
	ldr	x1, .LC150
	add	w2, w23, 36
	ldr	w3, [x19, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	ldr	x22, .LC152
	cbz	w21, .L211
	add	w27, w23, 40
	mov	w24, 0
	.p2align 2
.L212:
	uxtw	x0, w24
	mov	w3, w27
	add	x5, x0, 10
	add	w2, w24, 10
	add	x4, x20, x0, lsl 2
	mov	x1, x22
	mov	w0, 4
	add	w24, w24, 1
	add	w27, w27, w0
	ldr	w4, [x4, 744]
	add	x4, x20, x4, lsl 2
	ldr	w4, [x4, 324]
	and	w4, w4, -16
	str	w4, [x19, x5, lsl 2]
	ldr	w4, [x19, x5, lsl 2]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cmp	w21, w24
	bhi	.L212
	cmp	w21, 15
	bhi	.L216
.L211:
	add	w2, w21, 10
	add	w24, w23, w2, lsl 2
	.p2align 2
.L215:
	ldr	w5, [x20, 744]
	uxtw	x4, w21
	add	x4, x4, 10
	mov	w3, w24
	mov	w0, 4
	mov	x1, x22
	add	x5, x20, x5, lsl 2
	add	w21, w21, 1
	add	w24, w24, w0
	ldr	w5, [x5, 324]
	and	w5, w5, -16
	str	w5, [x19, x4, lsl 2]
	ldr	w4, [x19, x4, lsl 2]
	bl	dprint_vfmw
	cmp	w21, 15
	add	w2, w21, 10
	bls	.L215
.L216:
	ldr	x0, [x29, 96]
	add	w2, w23, 104
	ldr	x1, .LC154
	ldr	w3, [x0, 1104]
	mov	w0, 4
	and	w3, w3, -16
	str	w3, [x19, 104]
	ldr	w3, [x19, 104]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cbz	w21, .L236
	add	w24, w23, 108
	mov	w28, 27
	mov	w26, w24
	mov	w27, 0
	.p2align 2
.L218:
	add	x25, x20, x27, uxtw 2
	ubfiz	x4, x27, 1, 31
	add	x4, x4, 27
	mov	w3, w26
	lsl	x21, x4, 2
	mov	w2, w28
	ldr	w6, [x25, 808]
	mov	x1, x22
	str	w6, [x19, x4, lsl 2]
	mov	w0, 4
	add	w27, w27, 1
	ldr	w4, [x19, w28, uxtw 2]
	bl	dprint_vfmw
	add	x4, x21, 4
	add	w6, w28, 1
	ldr	w0, [x25, 872]
	add	w3, w26, 4
	mov	w2, w6
	mov	x1, x22
	str	w0, [x19, x4]
	mov	w0, 4
	add	w28, w28, 2
	add	w26, w26, 8
	ldr	w4, [x19, w6, uxtw 2]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cmp	w21, w27
	bhi	.L218
	cmp	w21, 15
	bhi	.L220
.L217:
	lsl	w27, w21, 1
	add	w28, w24, w21, lsl 3
	.p2align 2
.L219:
	uxtw	x4, w27
	add	w6, w27, 27
	add	x4, x4, 27
	mov	w3, w28
	lsl	x26, x4, 2
	mov	w2, w6
	mov	x1, x22
	mov	w0, 4
	str	wzr, [x19, x4, lsl 2]
	add	w21, w21, 1
	ldr	w4, [x19, w6, uxtw 2]
	bl	dprint_vfmw
	add	x5, x26, 4
	add	w4, w27, 28
	ldr	w0, [x29, 108]
	sub	w3, w28, w24
	mov	w2, w4
	mov	x1, x22
	str	wzr, [x19, x5]
	add	w3, w3, w0
	mov	w0, 4
	add	w27, w27, 2
	ldr	w4, [x19, w4, uxtw 2]
	add	w28, w28, 8
	bl	dprint_vfmw
	cmp	w21, 15
	bls	.L219
.L220:
	ldr	x0, [x29, 96]
	add	x3, x19, 256
	add	w2, w23, 256
	mov	w1, 56
	ldr	w4, [x0, 1176]
	add	x0, x20, 76
	and	w4, w4, -16
	str	w4, [x19, 236]
	bl	Write_V5R6C1_Qmatrix
	mov	w0, 0
.L204:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L235:
	ldr	w0, [x20, 68]
	add	w2, w23, 12
	str	w0, [x19, 12]
	mov	w0, 4
	ldr	x1, .LC138
	ldr	w3, [x20, 72]
	str	w3, [x19, 16]
	ldr	w3, [x19, 12]
	b	.L232
	.p2align 3
.L209:
	ldr	w1, [x20, 316]
	ldr	w0, [x20, 716]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L210
.L236:
	add	w24, w23, 108
	b	.L217
.L234:
	ldr	x2, .LC129
	mov	w0, 0
	ldr	x3, .LC128
	ldr	x1, .LC130
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w0, -1
	b	.L204
	.size	H264HAL_V5R6C1_SetPicMsg, .-H264HAL_V5R6C1_SetPicMsg
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC129:
	.xword	.LANCHOR0
	.align	3
.LC130:
	.xword	.LC9
	.align	3
.LC132:
	.xword	.LC131
	.align	3
.LC134:
	.xword	.LC133
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_SetSliceMsg
	.type	H264HAL_V5R6C1_SetSliceMsg, %function
H264HAL_V5R6C1_SetSliceMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w3
	mov	x19, x2
	mov	w24, w5
	mov	w23, w7
	bl	_mcount
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L251
	mov	x2, x0
	mov	w3, w21
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	w0, [x19, 48]
	add	w2, w21, 24
	ldp	w3, w1, [x19, 32]
	and	w0, w0, 1048575
	ubfiz	w1, w1, 24, 2
	orr	w0, w0, w3, lsl 26
	orr	w0, w0, w1
	str	w0, [x20, 24]
	ldr	x1, .LC160
	mov	w0, 4
	ldr	w3, [x20, 24]
	bl	dprint_vfmw
	ldr	x0, .LC161
	ldrb	w4, [x19, 3]
	ldrb	w0, [x0]
	cbnz	w0, .L241
	cbz	w4, .L252
.L241:
	ldp	w2, w3, [x19, 52]
	ldp	w0, w1, [x19, 40]
	ldr	x25, .LC157
	lsl	w2, w2, 2
	ubfiz	w1, w1, 16, 5
	ubfiz	w0, w0, 21, 5
	orr	w0, w0, w1
	orr	w1, w2, w3, lsl 8
	ldrb	w5, [x19]
	orr	w2, w0, w1
	add	x0, x25, 32
	ldrb	w1, [x19, 2]
	ldr	w0, [x0, w5, sxtw 2]
	orr	w1, w0, w1, lsl 15
	orr	w0, w2, w1
	ldr	x1, .LC163
	orr	w0, w0, w4, lsl 14
	str	w0, [x20, 28]
	add	w2, w21, 28
	mov	w0, 4
	ldr	w3, [x20, 28]
	bl	dprint_vfmw
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgMvAddrInfo
	ldrb	w2, [x19, 4]
	ldp	w0, w1, [x19, 60]
	ubfiz	w0, w0, 5, 5
	and	w1, w1, 31
	orr	w0, w0, w2, lsl 16
	add	w2, w21, 40
	orr	w0, w0, w1
	str	w0, [x20, 40]
	ldr	x1, .LC165
	mov	w0, 4
	ldr	w3, [x20, 40]
	bl	dprint_vfmw
	ldp	w0, w1, [x19, 68]
	ldr	w2, [x19, 76]
	ubfiz	w1, w1, 8, 4
	ubfiz	w0, w0, 16, 4
	orr	w0, w0, w1
	ldr	x1, .LC167
	orr	w0, w0, w2
	str	w0, [x20, 44]
	add	w2, w21, 44
	mov	w0, 4
	ldr	w3, [x20, 44]
	bl	dprint_vfmw
	ldr	x0, [x19, 4056]
	cbz	x0, .L253
.L243:
	str	w23, [x20, 176]
	and	w24, w24, -16
	str	w24, [x20, 252]
	add	x25, x25, 32
	mov	w23, 0
	ldrb	w0, [x19]
	ldr	w0, [x25, w0, sxtw 2]
	cbz	w0, .L239
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgRefPicInfo
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgAPCInfo
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgWPInfo
.L239:
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L252:
	ldp	w1, w0, [x22, 40]
	mul	w0, w0, w1
	cmp	w0, 1620
	bls	.L241
	mov	w23, -1
	b	.L239
	.p2align 3
.L253:
	ldr	w0, [x22, 740]
	ldrb	w23, [x19, 1]
	cmp	w0, 262144
	ble	.L245
	add	w23, w23, 1
	mov	w0, 262143
	sdiv	w23, w0, w23
	b	.L243
	.p2align 3
.L245:
	sub	w0, w0, #1
	add	w23, w23, 1
	sdiv	w23, w0, w23
	b	.L243
.L251:
	ldr	x2, .LC157
	mov	w0, 0
	ldr	x3, .LC156
	mov	w23, -1
	ldr	x1, .LC158
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L239
	.size	H264HAL_V5R6C1_SetSliceMsg, .-H264HAL_V5R6C1_SetSliceMsg
	.align	3
.LC156:
	.xword	.LC6
	.align	3
.LC157:
	.xword	.LANCHOR0
	.align	3
.LC158:
	.xword	.LC9
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC161:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC167:
	.xword	.LC166
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_StartDec
	.type	H264HAL_V5R6C1_StartDec, %function
H264HAL_V5R6C1_StartDec:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	sxtw	x22, w1
	mov	x23, x2
	bl	_mcount
	ldr	x20, .LC169
	lsl	x2, x22, 6
	mov	w1, w22
	sub	x2, x2, x22
	mov	x0, x28
	lsl	x2, x2, 2
	sub	x21, x2, x22
	add	x21, x2, x21, lsl 2
	bl	H264HAL_CheckParaValid
	cmn	w0, #1
	add	x21, x20, x21
	beq	.L285
	mov	w1, w22
	mov	x0, x21
	bl	H264HAL_GetVdmRegVirAddr
	cmn	w0, #1
	beq	.L285
	ldr	x3, .LC170
	mov	w0, 3
	ldr	x1, .LC172
	ldr	w2, [x3]
	add	w2, w2, 1
	str	w2, [x3]
	bl	dprint_vfmw
	mov	x3, x23
	mov	w2, w22
	mov	x1, x21
	mov	x0, x28
	bl	H264HAL_V5R6C1_CfgVdmReg
	cmn	w0, #1
	beq	.L285
	ldp	w2, w3, [x21, 72]
	mov	x1, x21
	mov	x0, x28
	bl	H264HAL_V5R6C1_SetPicMsg
	ldr	x26, [x28, 944]
	ldr	w0, [x28, 1188]
	cmp	w0, 1
	beq	.L286
	ldr	w19, [x26, 48]
	mov	w23, 0
	cbnz	w19, .L287
.L261:
	add	x24, x22, x22, lsl 2
	ldr	w1, [x28, 940]
	lsl	x24, x24, 4
	mov	w27, 0
	sub	x24, x24, x22
	mov	w19, 0
	lsl	x0, x24, 1
	str	x0, [x29, 104]
	.p2align 2
.L263:
	cmp	w19, w1
	bge	.L288
.L268:
	ldr	w6, [x26, 48]
	cmp	w6, w27
	ccmp	w19, wzr, 4, ls
	bgt	.L263
	ldr	x0, [x29, 104]
	add	w4, w23, 4
	add	w5, w23, 5
	add	w4, w4, w19
	sub	x25, x0, x22
	add	w24, w19, w5
	lsl	x25, x25, 1
	add	x3, x29, 140
	add	x4, x25, x4, sxtw
	add	x7, x25, x24, sxtw
	add	w2, w19, 1
	mov	x0, x26
	add	x4, x20, x4, lsl 2
	add	x7, x20, x7, lsl 2
	mov	w27, w6
	stp	w5, w6, [x29, 112]
	ldr	w4, [x4, 56]
	str	w4, [x29, 120]
	ldr	w4, [x7, 56]
	str	w4, [x29, 124]
	bl	H264HAL_FindNextSlicePara
	mov	x9, x0
	mov	w0, 140
	cbz	x9, .L285
	ldr	w19, [x29, 140]
	ldr	w1, [x28, 940]
	ldp	w5, w6, [x29, 112]
	cmp	w1, w19
	ldr	w4, [x29, 120]
	add	w5, w5, w19
	ccmp	w24, w0, 4, ne
	add	x5, x25, x5, sxtw
	beq	.L289
	add	x5, x20, x5, lsl 2
	ldr	w7, [x9, 48]
	ldr	w3, [x29, 124]
	mov	x2, x26
	sub	w7, w7, #1
	mov	x1, x21
	ldr	w5, [x5, 56]
	mov	x0, x28
	mov	x26, x9
	bl	H264HAL_V5R6C1_SetSliceMsg
	cbnz	w0, .L267
.L290:
	ldr	w1, [x28, 940]
	cmp	w19, w1
	blt	.L268
.L288:
	cmp	w1, wzr
	ble	.L269
	add	x0, x22, x22, lsl 2
	add	w1, w1, 4
	lsl	x0, x0, 4
	add	w1, w1, w23
	sub	x0, x0, x22
	lsl	x0, x0, 1
	sub	x0, x0, x22
	lsl	x0, x0, 1
	add	x0, x0, x1, sxtw
	add	x20, x20, x0, lsl 2
	ldr	w0, [x20, 56]
	bl	H264HAL_V5R6C1_CutSliceChain
	mov	w0, 0
.L256:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L289:
	ldr	w0, [x28, 44]
	mov	x2, x26
	ldr	w7, [x28, 36]
	mov	w5, 0
	ldr	w3, [x29, 124]
	mov	x1, x21
	str	xzr, [x26, 4056]
	mov	x26, x9
	mul	w7, w0, w7
	mov	x0, x28
	ldr	w19, [x28, 940]
	sub	w7, w7, #1
	bl	H264HAL_V5R6C1_SetSliceMsg
	cbz	w0, .L290
.L267:
	ldr	x1, .LC174
	mov	w2, 1272
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L269:
	ldr	x1, .LC176
	mov	w0, 1
	bl	dprint_vfmw
.L285:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L286:
	ldr	w1, [x28, 940]
	cmp	w1, 1
	ble	.L259
	.p2align 2
.L260:
	add	w0, w0, 1
	ldr	x26, [x26, 4056]
	cmp	w0, w1
	bne	.L260
.L259:
	lsl	x0, x22, 6
	ldr	w1, [x28, 44]
	sub	x0, x0, x22
	ldr	w7, [x28, 36]
	lsl	x0, x0, 2
	ldr	w6, [x26, 48]
	sub	x22, x0, x22
	mov	w5, 0
	mul	w7, w1, w7
	add	x0, x0, x22, lsl 2
	mov	x2, x26
	add	x20, x20, x0
	mov	w4, 0
	mov	x0, x28
	sub	w7, w7, #1
	mov	x1, x21
	ldr	w3, [x20, 76]
	bl	H264HAL_V5R6C1_SetSliceMsg
	cbz	w0, .L256
	ldr	x1, .LC174
	mov	w2, 1185
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L256
	.p2align 3
.L287:
	ldp	w10, w9, [x26, 8]
	ldp	w8, w27, [x26, 16]
	str	wzr, [x26, 48]
	mov	w23, 1
	stp	wzr, wzr, [x26, 16]
	stp	w23, wzr, [x26, 8]
	ldp	w25, w24, [x26, 24]
	stp	wzr, wzr, [x26, 24]
	sub	w7, w19, #1
	mov	w6, 0
	ldp	w4, w3, [x21, 72]
	ldr	w5, [x21, 80]
	mov	x2, x26
	mov	x1, x21
	mov	x0, x28
	stp	w10, w9, [x29, 116]
	str	w8, [x29, 124]
	bl	H264HAL_V5R6C1_SetSliceMsg
	ldp	w10, w9, [x29, 116]
	ldr	w8, [x29, 124]
	cbnz	w0, .L291
	stp	w10, w9, [x26, 8]
	stp	w8, w27, [x26, 16]
	stp	w25, w24, [x26, 24]
	str	w19, [x26, 48]
	ldr	x26, [x28, 944]
	b	.L261
.L291:
	ldr	x1, .LC174
	mov	w2, 1219
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L256
	.size	H264HAL_V5R6C1_StartDec, .-H264HAL_V5R6C1_StartDec
	.align	3
.LC169:
	.xword	g_HwMem
	.align	3
.LC170:
	.xword	.LANCHOR1
	.align	3
.LC172:
	.xword	.LC171
	.align	3
.LC174:
	.xword	.LC173
	.align	3
.LC176:
	.xword	.LC175
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.12323, %object
	.size	__func__.12323, 29
__func__.12323:
	.string	"H264HAL_V5R6C1_CutSliceChain"
	.zero	3
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.zero	4
	.type	g_ListStructFrame, %object
	.size	g_ListStructFrame, 32
g_ListStructFrame:
	.word	0
	.word	1
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.type	g_ListStructField, %object
	.size	g_ListStructField, 32
g_ListStructField:
	.word	0
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.type	__func__.12457, %object
	.size	__func__.12457, 23
__func__.12457:
	.string	"H264HAL_CheckParaValid"
	.zero	1
	.type	__func__.12479, %object
	.size	__func__.12479, 25
__func__.12479:
	.string	"H264HAL_V5R6C1_CfgVdmReg"
	.zero	7
	.type	__func__.12505, %object
	.size	__func__.12505, 25
__func__.12505:
	.string	"H264HAL_V5R6C1_SetPicMsg"
	.zero	7
	.type	g_StructTrans, %object
	.size	g_StructTrans, 32
g_StructTrans:
	.word	0
	.word	3
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.type	__func__.12535, %object
	.size	__func__.12535, 27
__func__.12535:
	.string	"H264HAL_V5R6C1_SetSliceMsg"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC4:
	ASCII(.string	"H264HAL_V5R6C1_InitHal return error.\n" )
	.zero	2
.LC6:
	ASCII(.string	"can not map slice msg virtual address!\n" )
.LC9:
	ASCII(.string	"%s: %s\n" )
.LC13:
	ASCII(.string	"qmatrix[%d] = 0x%x\n" )
	.zero	4
.LC15:
	ASCII(.string	"picmsg Dxx addr 0x%x = 0x%x\n" )
	.zero	3
.LC17:
	ASCII(.string	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,bytespos = 0x%x\n" )
	.zero	6
.LC19:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC22:
	ASCII(.string	"slicemsg g_pListX[1][0]->frame_store->pmv_address_idc = %d\n" )
	.zero	4
.LC24:
	ASCII(.string	"slicemsg D[6] addr 0x%x = 0x%x\n" )
.LC26:
	ASCII(.string	"slicemsg D[7] addr 0x%x = 0x%x\n" )
.LC30:
	ASCII(.string	"slicemsg D[%d] address 0x%x = 0x%x\n" )
	.zero	4
.LC40:
	ASCII(.string	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31 list0size = %d\n" )
	.zero	4
.LC43:
	ASCII(.string	"luma_lg = %d\n" )
	.zero	2
.LC45:
	ASCII(.string	"wp_weight_l0_y = %d\n" )
	.zero	3
.LC47:
	ASCII(.string	"wp_offset_l0_y = %d\n" )
	.zero	3
.LC49:
	ASCII(.string	"chroma_lg = %d\n" )
.LC51:
	ASCII(.string	"wp_weight_l1_y = %d\n" )
	.zero	3
.LC53:
	ASCII(.string	"wp_offset_l1_y = %d\n" )
	.zero	3
.LC55:
	ASCII(.string	"wp_weight_l0_u = %d\n" )
	.zero	3
.LC57:
	ASCII(.string	"wp_offset_l0_u = %d\n" )
	.zero	3
.LC59:
	ASCII(.string	"wp_weight_l1_u = %d\n" )
	.zero	3
.LC61:
	ASCII(.string	"wp_offset_l1_u = %d\n" )
	.zero	3
.LC63:
	ASCII(.string	"wp_weight_l0_v = %d\n" )
	.zero	3
.LC65:
	ASCII(.string	"wp_offset_l0_v = %d\n" )
	.zero	3
.LC67:
	ASCII(.string	"wp_weight_l1_v = %d\n" )
	.zero	3
.LC69:
	ASCII(.string	"wp_offset_l1_v = %d\n" )
	.zero	3
.LC71:
	ASCII(.string	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~D63 list1size = %d\n" )
	.zero	1
.LC75:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC77:
	ASCII(.string	"point of picture para null\n" )
	.zero	4
.LC80:
	ASCII(.string	"picture width out of range\n" )
	.zero	4
.LC82:
	ASCII(.string	"point of fst slice para null\n" )
	.zero	2
.LC84:
	ASCII(.string	"VdhId is wrong! H264HAL_V200R003_StartDec\n" )
	.zero	5
.LC86:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC91:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC94:
	ASCII(.string	"BASIC_V5R6C1_CFG0 = 0x%x\n" )
	.zero	6
.LC96:
	ASCII(.string	"BASIC_V5R6C1_CFG1 = 0x%x\n" )
	.zero	6
.LC98:
	ASCII(.string	"AVM_V5R6C1_ADDR = 0x%x\n" )
.LC100:
	ASCII(.string	"VAM_V5R6C1_ADDR = 0x%x\n" )
.LC102:
	ASCII(.string	"STREAM_V5R6C1_BASE_ADDR = 0x%x\n" )
.LC105:
	ASCII(.string	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	5
.LC107:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC109:
	ASCII(.string	"YSTADDR_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC111:
	ASCII(.string	"YSTRIDE_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC113:
	ASCII(.string	"UVOFFSET_V5R6C1_1D = 0x%x\n" )
	.zero	5
.LC115:
	ASCII(.string	"HEAD_INF_OFFSET_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC117:
	ASCII(.string	"PPFD_V5R6C1_BUF_ADDR = 0x%x\n" )
	.zero	3
.LC119:
	ASCII(.string	"PPFD_V5R6C1_BUF_LEN = 0x%x\n" )
	.zero	4
.LC121:
	ASCII(.string	"REF_V5R6C1_PIC_TYPE = 0x%x\n" )
	.zero	4
.LC123:
	ASCII(.string	"FF_V5R6C1_APT_EN = 0x%x\n" )
	.zero	7
.LC125:
	ASCII(.string	"line %d pSlicePara is NULL!\n" )
	.zero	3
.LC127:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC131:
	ASCII(.string	"picmsg D[0] addr 0x%x = 0x%x\n" )
	.zero	2
.LC133:
	ASCII(.string	"picmsg D[1] addr 0x%x = 0x%x\n" )
	.zero	2
.LC135:
	ASCII(.string	"picmsg D[2] addr 0x%x = 0x%x\n" )
	.zero	2
.LC137:
	ASCII(.string	"picmsg D[3] addr 0x%x = 0x%x\n" )
	.zero	2
.LC139:
	ASCII(.string	"picmsg D[4] addr 0x%x = 0x%x\n" )
	.zero	2
.LC141:
	ASCII(.string	"picmsg D[5] addr 0x%x = 0x%x\n" )
	.zero	2
.LC143:
	ASCII(.string	"picmsg D[6] addr 0x%x = 0x%x\n" )
	.zero	2
.LC145:
	ASCII(.string	"picmsg D[7] addr 0x%x = 0x%x\n" )
	.zero	2
.LC147:
	ASCII(.string	"picmsg D[8] addr 0x%x = 0x%x\n" )
	.zero	2
.LC149:
	ASCII(.string	"picmsg D[9] addr 0x%x = 0x%x\n" )
	.zero	2
.LC151:
	ASCII(.string	"picmsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	1
.LC153:
	ASCII(.string	"picmsg D[26] addr 0x%x = 0x%x\n" )
	.zero	1
.LC159:
	ASCII(.string	"slicemsg D[4] addr 0x%x = 0x%x\n" )
.LC162:
	ASCII(.string	"slicemsg D[5] addr 0x%x = 0x%x\n" )
.LC164:
	ASCII(.string	"slicemsg D[8] addr 0x%x = 0x%x\n" )
.LC166:
	ASCII(.string	"slicemsg D[9] addr 0x%x = 0x%x\n" )
.LC171:
	ASCII(.string	"\n\n***********************H264HAL_V200R003_StartDec is Now %d***********************\n" )
	.zero	3
.LC173:
	ASCII(.string	"line %d Set slice msg not wrong!\n" )
	.zero	6
.LC175:
	ASCII(.string	"!!! no slice to dec, add up msg report." )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.12557, %object
	.size	StartCnt.12557, 4
StartCnt.12557:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
