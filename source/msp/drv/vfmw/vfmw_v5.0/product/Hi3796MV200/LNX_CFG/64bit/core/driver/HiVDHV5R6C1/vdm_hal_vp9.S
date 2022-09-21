#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_vp9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_InitHal
	.type	VP9HAL_V5R6C1_InitHal, %function
VP9HAL_V5R6C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VP9HAL_V5R6C1_InitHal, .-VP9HAL_V5R6C1_InitHal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_CfgReg
	.type	VP9HAL_V5R6C1_CfgReg, %function
VP9HAL_V5R6C1_CfgReg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	x19, x3
	mov	x23, x1
	bl	_mcount
	ldr	x1, .LC1
	sbfiz	x0, x21, 6, 32
	ldr	x2, .LC0
	cmp	x19, xzr
	str	wzr, [x29, 76]
	ldrb	w1, [x1]
	add	x0, x2, x0
	ccmp	w1, 1, 4, eq
	ldr	w0, [x0, 8]
	bne	.L22
	ldr	x2, .LC5
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L15
	ldr	w24, [x0, 1272]
.L5:
	cmp	w1, 1
	beq	.L6
	strb	w24, [x19, 1]
.L6:
	cmp	w21, wzr
	bgt	.L23
	bne	.L19
	ldr	x0, [x23]
	cbz	x0, .L24
.L11:
	add	x20, x20, 270336
	ldr	w5, [x23, 1212]
	ldr	w1, [x29, 76]
	mov	x3, x19
	and	w5, w5, -16
	mov	w0, 8
	str	w5, [x20, 2352]
	mov	w2, 0
	ldr	w4, [x20, 2088]
	mov	w21, 3
	ldr	w5, [x23, 1216]
	and	w5, w5, -16
	str	w5, [x20, 2356]
	ldr	w5, [x20, 2092]
	mul	w4, w4, w5
	sub	w4, w4, #1
	bfi	w1, w4, 0, 20
	str	w1, [x29, 76]
	ubfx	x1, x1, 24, 6
	strb	w1, [x29, 79]
	ldr	w22, [x29, 76]
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC13
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
	strh	w21, [x29, 78]
	mov	w0, 0
	ldr	w2, [x20, 2468]
	bfi	w0, w24, 4, 1
	ldr	w3, [x20, 2488]
	and	w0, w0, -33
	mov	w1, 0
	bfi	w0, w2, 6, 1
	bfi	w1, w3, 4, 1
	and	w0, w0, 127
	orr	w1, w1, -64
	strb	w0, [x29, 79]
	mov	w0, 14
	strb	w1, [x29, 77]
	mov	x3, x19
	strb	w0, [x29, 76]
	mov	w2, 0
	mov	w0, 12
	strb	wzr, [x20, 2081]
	ldr	w22, [x29, 76]
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC15
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w22, [x23, 72]
	mov	x3, x19
	mov	w0, 16
	and	w22, w22, -16
	mov	w2, 0
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC17
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w22, [x23, 56]
	mov	x3, x19
	mov	w0, 20
	and	w22, w22, -16
	mov	w2, 0
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC19
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w22, [x20, 2128]
	mov	x3, x19
	mov	w0, 24
	mov	w1, w22
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC21
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w22, [x23, 1180]
	mov	x3, x19
	mov	w0, 128
	and	w22, w22, -16
	mov	w2, 0
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC23
	mov	w2, w22
	mov	w0, w21
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	dprint_vfmw
	ldr	w23, [x23, 1184]
	mov	x3, x19
	mov	w0, 132
	mov	w2, 0
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC25
	mov	w2, w23
	mov	w0, w21
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	mov	x3, x19
	mov	w2, 0
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC27
	mov	w2, 0
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w0, [x20, 2088]
	mov	x3, x19
	mov	w2, 0
	cmp	w0, 256
	mov	w0, 4
	cset	w1, ls
	bl	SCD_ConfigReg
	str	w22, [x29, 76]
	mov	w2, 0
	mov	w1, w22
	mov	w0, 60
	mov	x3, x19
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, w22
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w24, 1
	beq	.L25
.L13:
	ldr	w21, [x20, 2440]
	mov	x3, x19
	mov	w0, 96
	mov	w2, 0
	and	w21, w21, -16
	mov	w1, w21
	bl	MFDE_ConfigReg
	ldr	x1, .LC31
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2096]
	mov	x3, x19
	mov	w0, 100
	mov	w1, w21
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC33
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2108]
	mov	x3, x19
	mov	w0, 104
	mov	w1, w21
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC35
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2504]
	mov	x3, x19
	mov	w0, 108
	mov	w1, w21
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC37
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2508]
	mov	x3, x19
	mov	w0, 116
	mov	w1, w21
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC39
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2512]
	mov	x3, x19
	mov	w0, 120
	mov	w1, w21
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC41
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x20, 2516]
	mov	x3, x19
	mov	w0, 124
	mov	w2, 0
	mov	w1, w21
	str	w21, [x29, 76]
	bl	MFDE_ConfigReg
	ldr	x1, .LC43
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	cmp	w24, 1
	beq	.L26
.L14:
	mov	w0, 32
	mov	x3, x19
	mov	w2, 0
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L4:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L15:
	mov	w24, 0
	b	.L5
	.p2align 3
.L24:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L12
	str	x0, [x23]
	b	.L11
	.p2align 3
.L25:
	mov	w2, 0
	mov	w1, 60
	mov	w0, 92
	mov	x3, x19
	bl	MFDE_ConfigReg
	ldr	x1, .LC29
	mov	w2, 60
	mov	w0, w21
	bl	dprint_vfmw
	b	.L13
	.p2align 3
.L26:
	ldr	w20, [x20, 2496]
	mov	w0, 112
	mov	x3, x19
	mov	w2, 0
	mov	w1, w20
	bl	MFDE_ConfigReg
	ldr	x1, .LC45
	mov	w2, w20
	mov	w0, 3
	bl	dprint_vfmw
	b	.L14
	.p2align 3
.L23:
	ldr	x2, .LC2
	mov	w4, 0
	ldr	x1, .LC7
	mov	w3, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
	.p2align 3
.L19:
	ldr	x1, .LC9
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
.L22:
	ldr	x2, .LC2
	mov	x3, x19
	ldr	x1, .LC4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
.L12:
	ldr	x1, .LC11
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
	.size	VP9HAL_V5R6C1_CfgReg, .-VP9HAL_V5R6C1_CfgReg
	.align	3
.LC0:
	.xword	g_VdmDrvParam
	.align	3
.LC1:
	.xword	g_HalDisable
	.align	3
.LC2:
	.xword	.LANCHOR0
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	s_pstVfmwChan
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC21:
	.xword	.LC20
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_CfgFrameMsg
	.type	VP9HAL_V5R6C1_CfgFrameMsg, %function
VP9HAL_V5R6C1_CfgFrameMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 72]
	bl	MEM_Phy2Vir
	mov	x23, x0
	cbz	x0, .L38
	ldr	w0, [x19]
	add	x22, x19, 270336
	str	w0, [x23]
	mov	w0, 4
	ldr	x28, .LC52
	ldr	w2, [x23]
	mov	x1, x28
	bl	dprint_vfmw
	ldr	x27, .LC54
	ldr	w0, [x19, 4]
	str	w0, [x23, 4]
	mov	x1, x27
	mov	w0, 4
	ldr	w2, [x23, 4]
	bl	dprint_vfmw
	ldr	x26, .LC56
	ldr	w0, [x19, 8]
	str	w0, [x23, 8]
	mov	x1, x26
	mov	w0, 4
	ldr	w2, [x23, 8]
	bl	dprint_vfmw
	ldr	x25, .LC58
	ldr	w0, [x19, 12]
	str	w0, [x23, 12]
	mov	x1, x25
	mov	w0, 4
	ldr	w2, [x23, 12]
	bl	dprint_vfmw
	ldr	x24, .LC60
	ldr	w0, [x19, 16]
	str	w0, [x23, 16]
	mov	x1, x24
	mov	w0, 4
	ldr	w2, [x23, 16]
	bl	dprint_vfmw
	ldr	w0, [x19, 20]
	str	w0, [x23, 20]
	mov	w0, 4
	ldr	x1, .LC62
	ldr	w2, [x23, 20]
	bl	dprint_vfmw
	ldr	w0, [x19, 24]
	str	w0, [x23, 24]
	mov	w0, 4
	ldr	x1, .LC64
	ldr	w2, [x23, 24]
	bl	dprint_vfmw
	ldr	w0, [x19, 28]
	str	w0, [x23, 28]
	mov	w0, 4
	ldr	x1, .LC66
	ldr	w2, [x23, 28]
	bl	dprint_vfmw
	ldr	w0, [x19, 32]
	str	w0, [x23, 32]
	mov	w0, 4
	ldr	x1, .LC68
	ldr	w2, [x23, 32]
	bl	dprint_vfmw
	ldr	w0, [x19, 36]
	str	w0, [x23, 36]
	mov	w0, 4
	ldr	x1, .LC70
	ldr	w2, [x23, 36]
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	str	w0, [x23, 40]
	mov	w0, 4
	ldr	x1, .LC72
	ldr	w2, [x23, 40]
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	str	w0, [x23, 44]
	mov	w0, 4
	ldr	x1, .LC74
	ldr	w2, [x23, 44]
	bl	dprint_vfmw
	ldr	w0, [x19, 48]
	str	w0, [x23, 48]
	mov	w0, 4
	ldr	x1, .LC76
	ldr	w2, [x23, 48]
	bl	dprint_vfmw
	ldr	w0, [x19, 52]
	str	w0, [x23, 52]
	mov	w0, 4
	ldr	x1, .LC78
	ldr	w2, [x23, 52]
	bl	dprint_vfmw
	ldr	w0, [x19, 56]
	str	w0, [x23, 56]
	mov	w0, 4
	ldr	x1, .LC80
	ldr	w2, [x23, 56]
	bl	dprint_vfmw
	ldr	w0, [x19, 60]
	str	w0, [x23, 60]
	mov	w0, 4
	ldr	x1, .LC82
	ldr	w2, [x23, 60]
	bl	dprint_vfmw
	ldr	w0, [x19, 64]
	str	w0, [x23, 64]
	mov	w0, 4
	ldr	x1, .LC84
	ldr	w2, [x23, 64]
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	str	w0, [x23, 68]
	mov	w0, 4
	ldr	x1, .LC86
	ldr	w2, [x23, 68]
	bl	dprint_vfmw
	ldr	w0, [x19, 72]
	str	w0, [x23, 72]
	mov	w0, 4
	ldr	x1, .LC88
	ldr	w2, [x23, 72]
	bl	dprint_vfmw
	ldr	w0, [x19, 76]
	str	w0, [x23, 76]
	mov	w0, 4
	ldr	x1, .LC90
	ldr	w2, [x23, 76]
	bl	dprint_vfmw
	ldr	w0, [x19, 80]
	str	w0, [x23, 80]
	mov	w0, 4
	ldr	x1, .LC92
	ldr	w2, [x23, 80]
	bl	dprint_vfmw
	ldr	w0, [x19, 84]
	str	w0, [x23, 84]
	mov	w0, 4
	ldr	x1, .LC94
	ldr	w2, [x23, 84]
	bl	dprint_vfmw
	ldr	w0, [x19, 88]
	str	w0, [x23, 88]
	mov	w0, 4
	ldr	x1, .LC96
	ldr	w2, [x23, 88]
	bl	dprint_vfmw
	ldr	w0, [x19, 92]
	str	w0, [x23, 92]
	mov	w0, 4
	ldr	x1, .LC98
	ldr	w2, [x23, 92]
	bl	dprint_vfmw
	ldr	w0, [x19, 96]
	str	w0, [x23, 96]
	mov	w0, 4
	ldr	x1, .LC100
	ldr	w2, [x23, 96]
	bl	dprint_vfmw
	ldr	w0, [x19, 100]
	str	w0, [x23, 100]
	mov	w0, 4
	ldr	x1, .LC102
	ldr	w2, [x23, 100]
	bl	dprint_vfmw
	ldr	w0, [x19, 104]
	str	w0, [x23, 104]
	mov	w0, 4
	ldr	x1, .LC104
	ldr	w2, [x23, 104]
	bl	dprint_vfmw
	ldr	w0, [x19, 108]
	str	w0, [x23, 108]
	mov	w0, 4
	ldr	x1, .LC106
	ldr	w2, [x23, 108]
	bl	dprint_vfmw
	ldr	w0, [x19, 112]
	str	w0, [x23, 112]
	mov	w0, 4
	ldr	x1, .LC108
	ldr	w2, [x23, 112]
	bl	dprint_vfmw
	ldr	w0, [x19, 116]
	str	w0, [x23, 116]
	mov	w0, 4
	ldr	x1, .LC110
	ldr	w2, [x23, 116]
	bl	dprint_vfmw
	ldr	w0, [x19, 120]
	str	w0, [x23, 120]
	mov	w0, 4
	ldr	x1, .LC112
	ldr	w2, [x23, 120]
	bl	dprint_vfmw
	ldr	w0, [x22, 2440]
	str	w0, [x23, 128]
	mov	w0, 4
	ldr	x1, .LC114
	ldr	w2, [x23, 128]
	bl	dprint_vfmw
	ldr	w0, [x22, 2444]
	str	w0, [x23, 132]
	mov	w0, 4
	ldr	x1, .LC116
	ldr	w2, [x23, 132]
	bl	dprint_vfmw
	ldr	w0, [x22, 2448]
	str	w0, [x23, 136]
	mov	w0, 4
	ldr	x1, .LC118
	ldr	w2, [x23, 136]
	bl	dprint_vfmw
	ldr	w0, [x22, 2452]
	str	w0, [x23, 140]
	mov	w0, 4
	ldr	x1, .LC120
	ldr	w2, [x23, 140]
	bl	dprint_vfmw
	ldr	w0, [x20, 1160]
	ldr	x1, .LC122
	and	w0, w0, -16
	str	w0, [x23, 144]
	mov	w0, 4
	ldr	w2, [x23, 144]
	bl	dprint_vfmw
	ldr	w0, [x20, 1164]
	ldr	x1, .LC124
	and	w0, w0, -16
	str	w0, [x23, 148]
	mov	w0, 4
	ldr	w2, [x23, 148]
	bl	dprint_vfmw
	ldr	w0, [x20, 1168]
	ldr	x1, .LC126
	and	w0, w0, -16
	str	w0, [x23, 152]
	mov	w0, 4
	ldr	w2, [x23, 152]
	bl	dprint_vfmw
	ldr	w21, [x20, 1212]
	ldr	x1, .LC128
	mov	w0, 4
	and	w21, w21, -16
	str	w21, [x23, 156]
	ldr	w2, [x23, 156]
	bl	dprint_vfmw
	mov	w0, w21
	bl	MEM_Phy2Vir
	str	x0, [x29, 104]
	cbz	x0, .L31
	ldr	x21, .LC131
	add	x1, x19, 262144
	add	x1, x1, 1029
	mov	x2, 4608
	ldr	x5, [x21, 104]
	blr	x5
	ldr	w0, [x20, 1176]
	ldr	x1, .LC133
	and	w0, w0, -16
	str	w0, [x23, 160]
	mov	w0, 4
	ldr	w2, [x23, 160]
	bl	dprint_vfmw
	ldr	w5, [x20, 1216]
	mov	w0, 4
	ldr	x1, .LC135
	and	w5, w5, -16
	str	w5, [x23, 164]
	str	w5, [x29, 96]
	ldr	w2, [x23, 164]
	bl	dprint_vfmw
	ldr	w5, [x29, 96]
	mov	w0, w5
	bl	MEM_Phy2Vir
	str	x0, [x29, 96]
	cbz	x0, .L31
	ldr	x5, [x21, 104]
	add	x1, x19, 266240
	add	x1, x1, 1541
	mov	x2, 4608
	blr	x5
	ldr	w0, [x22, 2456]
	ldr	x1, .LC137
	and	w0, w0, -16
	str	w0, [x23, 168]
	mov	w0, 4
	ldr	w2, [x23, 168]
	bl	dprint_vfmw
	ldr	w0, [x20, 1208]
	ldr	x1, .LC139
	and	w0, w0, -16
	str	w0, [x23, 172]
	mov	w0, 4
	ldr	w2, [x23, 172]
	bl	dprint_vfmw
	ldr	w0, [x19, 180]
	str	w0, [x23, 180]
	mov	w0, 4
	ldr	x1, .LC141
	ldr	w2, [x23, 180]
	bl	dprint_vfmw
	ldr	w0, [x19, 184]
	str	w0, [x23, 184]
	mov	w0, 4
	ldr	x1, .LC143
	ldr	w2, [x23, 184]
	bl	dprint_vfmw
	ldr	w0, [x19, 188]
	str	w0, [x23, 188]
	mov	w0, 4
	ldr	x1, .LC145
	ldr	w2, [x23, 188]
	bl	dprint_vfmw
	ldr	w0, [x19, 192]
	str	w0, [x23, 192]
	mov	w0, 4
	ldr	x1, .LC147
	ldr	w2, [x23, 192]
	bl	dprint_vfmw
	ldr	w0, [x19, 196]
	str	w0, [x23, 196]
	mov	w0, 4
	ldr	x1, .LC149
	ldr	w2, [x23, 196]
	bl	dprint_vfmw
	ldr	w0, [x19, 200]
	str	w0, [x23, 200]
	mov	w0, 4
	ldr	x1, .LC151
	ldr	w2, [x23, 200]
	bl	dprint_vfmw
	ldr	w0, [x19, 204]
	str	w0, [x23, 204]
	mov	w0, 4
	ldr	x1, .LC153
	ldr	w2, [x23, 204]
	bl	dprint_vfmw
	ldr	w0, [x19, 208]
	str	w0, [x23, 208]
	mov	w0, 4
	ldr	x1, .LC155
	ldr	w2, [x23, 208]
	bl	dprint_vfmw
	ldr	w0, [x19, 212]
	str	w0, [x23, 212]
	mov	w0, 4
	ldr	x1, .LC157
	ldr	w2, [x23, 212]
	bl	dprint_vfmw
	ldr	w0, [x19, 216]
	str	w0, [x23, 216]
	mov	w0, 4
	ldr	x1, .LC159
	ldr	w2, [x23, 216]
	bl	dprint_vfmw
	ldr	w0, [x19, 220]
	str	w0, [x23, 220]
	mov	w0, 4
	ldr	x1, .LC161
	ldr	w2, [x23, 220]
	bl	dprint_vfmw
	ldr	w0, [x19, 224]
	str	w0, [x23, 224]
	mov	w0, 4
	ldr	x1, .LC163
	ldr	w2, [x23, 224]
	bl	dprint_vfmw
	ldr	w0, [x19, 228]
	str	w0, [x23, 228]
	mov	w0, 4
	ldr	x1, .LC165
	ldr	w2, [x23, 228]
	bl	dprint_vfmw
	ldr	w0, [x19, 232]
	str	w0, [x23, 232]
	mov	w0, 4
	ldr	x1, .LC167
	ldr	w2, [x23, 232]
	bl	dprint_vfmw
	ldr	w0, [x19, 236]
	str	w0, [x23, 236]
	mov	w0, 4
	ldr	x1, .LC169
	ldr	w2, [x23, 236]
	bl	dprint_vfmw
	ldr	w0, [x19, 240]
	str	w0, [x23, 240]
	mov	w0, 4
	ldr	x1, .LC171
	ldr	w2, [x23, 240]
	bl	dprint_vfmw
	ldr	w0, [x19, 244]
	str	w0, [x23, 244]
	mov	w0, 4
	ldr	x1, .LC173
	ldr	w2, [x23, 244]
	bl	dprint_vfmw
	ldr	w0, [x19, 248]
	str	w0, [x23, 248]
	mov	w0, 4
	ldr	x1, .LC175
	ldr	w2, [x23, 248]
	bl	dprint_vfmw
	ldr	w0, [x20, 76]
	str	w0, [x23, 252]
	mov	w0, 4
	ldr	x1, .LC177
	ldr	w2, [x23, 252]
	bl	dprint_vfmw
	ldr	w0, [x22, 2520]
	mov	x1, x28
	add	w0, w0, 255
	and	w0, w0, -256
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	asr	w0, w0, 2
	lsl	w0, w0, 4
	str	w0, [x23, 256]
	mov	w0, 4
	ldr	w2, [x23, 256]
	bl	dprint_vfmw
	ldr	w0, [x22, 2468]
	ldr	w2, [x22, 2520]
	ldr	w5, [x22, 2532]
	cmp	w0, 1
	add	w0, w2, 255
	add	w6, w5, 63
	and	w0, w0, -256
	and	w1, w6, -64
	mul	w0, w0, w1
	lsl	w1, w0, 2
	sub	w0, w1, w0
	asr	w0, w0, 1
	beq	.L39
.L32:
	str	w0, [x23, 260]
	mov	x1, x27
	mov	w0, 4
	ldr	w2, [x23, 260]
	bl	dprint_vfmw
	ldr	w0, [x22, 2520]
	mov	x1, x26
	add	w0, w0, 255
	and	w2, w0, -256
	ldr	w0, [x22, 2532]
	add	w0, w0, 63
	and	w0, w0, -64
	mul	w0, w2, w0
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	asr	w0, w0, 2
	str	w0, [x23, 264]
	mov	w0, 4
	ldr	w2, [x23, 264]
	bl	dprint_vfmw
	ldr	w0, [x22, 2524]
	mov	x1, x25
	add	w0, w0, 255
	and	w0, w0, -256
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	asr	w0, w0, 2
	lsl	w0, w0, 4
	str	w0, [x23, 268]
	mov	w0, 4
	ldr	w2, [x23, 268]
	bl	dprint_vfmw
	ldr	w0, [x22, 2524]
	add	w0, w0, 255
	and	w1, w0, -256
	ldr	w0, [x22, 2536]
	add	w0, w0, 63
	and	w0, w0, -64
	mul	w0, w1, w0
	ldr	w1, [x22, 2468]
	cmp	w1, 1
	lsl	w1, w0, 2
	sub	w0, w1, w0
	asr	w0, w0, 1
	beq	.L40
.L33:
	str	w0, [x23, 272]
	mov	x1, x24
	mov	w0, 4
	ldr	w2, [x23, 272]
	bl	dprint_vfmw
	ldr	w0, [x22, 2524]
	ldr	x1, .LC62
	add	w0, w0, 255
	and	w2, w0, -256
	ldr	w0, [x22, 2536]
	add	w0, w0, 63
	and	w0, w0, -64
	mul	w0, w2, w0
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	asr	w0, w0, 2
	str	w0, [x23, 276]
	mov	w0, 4
	ldr	w2, [x23, 276]
	bl	dprint_vfmw
	ldr	w2, [x22, 2528]
	ldr	x1, .LC64
	add	w2, w2, 255
	and	w2, w2, -256
	cmp	w2, wzr
	add	w0, w2, 3
	csel	w2, w0, w2, lt
	mov	w0, 4
	asr	w2, w2, 2
	lsl	w2, w2, 4
	str	w2, [x23, 280]
	ldr	w2, [x23, 280]
	bl	dprint_vfmw
	ldr	w1, [x22, 2528]
	ldr	w0, [x22, 2540]
	add	w1, w1, 255
	ldr	w2, [x22, 2468]
	add	w0, w0, 63
	and	w1, w1, -256
	and	w0, w0, -64
	cmp	w2, 1
	mul	w0, w1, w0
	lsl	w1, w0, 2
	sub	w0, w1, w0
	asr	w0, w0, 1
	beq	.L41
.L34:
	str	w0, [x23, 284]
	mov	w0, 4
	ldr	x1, .LC66
	ldr	w2, [x23, 284]
	bl	dprint_vfmw
	ldr	w5, [x22, 2528]
	mov	w0, 4
	ldr	w2, [x22, 2540]
	add	w5, w5, 255
	ldr	x1, .LC68
	add	w2, w2, 63
	and	w5, w5, -256
	and	w2, w2, -64
	mul	w2, w5, w2
	cmp	w2, wzr
	add	w5, w2, 3
	csel	w2, w5, w2, lt
	asr	w2, w2, 2
	str	w2, [x23, 288]
	ldr	w2, [x23, 288]
	bl	dprint_vfmw
	ldr	w1, [x22, 2352]
	mov	w2, 4608
	ldr	x3, [x21, 280]
	ldr	x0, [x29, 104]
	blr	x3
	ldr	x0, [x29, 96]
	mov	w2, 4608
	ldr	w1, [x22, 2356]
	ldr	x3, [x21, 280]
	blr	x3
	mov	w0, 0
.L29:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L39:
	adds	w1, w2, 2047
	add	w2, w2, 4094
	csel	w2, w2, w1, mi
	add	w5, w5, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w1, w2, 127
	csel	w2, w1, w2, lt
	cmp	w6, wzr
	csel	w5, w5, w6, lt
	asr	w1, w2, 7
	asr	w5, w5, 6
	lsl	w2, w5, 2
	sub	w2, w2, w5
	lsl	w2, w2, 5
	mul	w2, w1, w2
	add	w0, w0, w2, lsr 1
	b	.L32
	.p2align 3
.L41:
	ldr	w2, [x22, 2520]
	ldr	w6, [x22, 2532]
	add	w5, w2, 4094
	adds	w2, w2, 2047
	csel	w2, w5, w2, mi
	add	w5, w6, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w1, w2, 127
	csel	w1, w1, w2, lt
	asr	w2, w1, 7
	adds	w1, w6, 63
	csel	w1, w5, w1, mi
	asr	w1, w1, 6
	lsl	w5, w1, 2
	sub	w1, w5, w1
	lsl	w1, w1, 5
	mul	w1, w2, w1
	add	w0, w0, w1, lsr 1
	b	.L34
	.p2align 3
.L40:
	ldr	w2, [x22, 2520]
	ldr	w6, [x22, 2532]
	adds	w1, w2, 2047
	add	w2, w2, 4094
	csel	w1, w2, w1, mi
	add	w5, w6, 126
	and	w1, w1, -2048
	cmp	w1, wzr
	add	w2, w1, 127
	csel	w1, w2, w1, lt
	asr	w2, w1, 7
	adds	w1, w6, 63
	csel	w1, w5, w1, mi
	asr	w1, w1, 6
	lsl	w5, w1, 2
	sub	w1, w5, w1
	lsl	w1, w1, 5
	mul	w1, w2, w1
	add	w0, w0, w1, lsr 1
	b	.L33
	.p2align 3
.L31:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC130
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L29
.L38:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x3, .LC47
	ldr	x1, .LC50
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L29
	.size	VP9HAL_V5R6C1_CfgFrameMsg, .-VP9HAL_V5R6C1_CfgFrameMsg
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR0
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
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC84:
	.xword	.LC83
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC98:
	.xword	.LC97
	.align	3
.LC100:
	.xword	.LC99
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
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
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC131:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC133:
	.xword	.LC132
	.align	3
.LC135:
	.xword	.LC134
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC147:
	.xword	.LC146
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC177:
	.xword	.LC176
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_CfgTileMsg
	.type	VP9HAL_V5R6C1_CfgTileMsg, %function
VP9HAL_V5R6C1_CfgTileMsg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19, 76]
	mov	w0, w19
	bl	MEM_Phy2Vir
	mov	x22, x0
	cbz	x0, .L51
	add	x21, x20, 262144
	ldr	w2, [x21, 1024]
	sub	w0, w2, #1
	cmp	w0, 1023
	bhi	.L52
.L45:
	cbz	w2, .L48
	ldr	x28, .LC184
	mov	w24, w19
	ldr	x27, .LC186
	mov	w23, 0
	ldr	x26, .LC188
	.p2align 2
.L46:
	sxtw	x3, w23
	mov	x1, x28
	lsl	x2, x3, 8
	mov	w0, 4
	add	x5, x20, x3, lsl 8
	add	x19, x22, x2
	add	x25, x20, x2
	ldr	w5, [x5, 1024]
	str	w5, [x22, x2]
	ldr	w2, [x22, x2]
	bl	dprint_vfmw
	ldr	w0, [x25, 1028]
	mov	x1, x27
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x25, 1032]
	mov	x1, x26
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x25, 1036]
	str	w0, [x19, 12]
	mov	w0, 4
	ldr	x1, .LC190
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	w0, [x25, 1040]
	str	w0, [x19, 16]
	mov	w0, 4
	ldr	x1, .LC192
	ldr	w2, [x19, 16]
	bl	dprint_vfmw
	ldr	w0, [x25, 1044]
	str	w0, [x19, 20]
	mov	w0, 4
	ldr	x1, .LC194
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x25, 1048]
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	x1, .LC196
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	w0, [x25, 1052]
	str	w0, [x19, 28]
	mov	w0, 4
	ldr	x1, .LC198
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	w0, [x25, 1056]
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	x1, .LC200
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	w0, [x25, 1060]
	str	w0, [x19, 36]
	mov	w0, 4
	ldr	x1, .LC202
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	ldr	w0, [x25, 1064]
	str	w0, [x19, 40]
	mov	w0, 4
	ldr	x1, .LC204
	ldr	w2, [x19, 40]
	bl	dprint_vfmw
	ldr	w0, [x25, 1068]
	str	w0, [x19, 44]
	mov	w0, 4
	ldr	x1, .LC206
	ldr	w2, [x19, 44]
	bl	dprint_vfmw
	ldr	w0, [x25, 1276]
	str	w0, [x19, 252]
	mov	w0, 4
	ldr	x1, .LC208
	ldr	w2, [x19, 252]
	bl	dprint_vfmw
	cmp	w23, wzr
	add	w23, w23, 1
	ble	.L47
	str	w24, [x19, -4]
.L47:
	ldr	w0, [x21, 1024]
	add	w24, w24, 256
	cmp	w0, w23
	bhi	.L46
	cmp	w0, 1
	bls	.L48
	ubfiz	x1, x0, 8, 26
	mov	w0, 0
	add	x6, x22, x1
	str	wzr, [x6, -4]
.L44:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L52:
	ldr	x1, .LC182
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w2, [x21, 1024]
	b	.L45
	.p2align 3
.L48:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L51:
	ldr	x2, .LC179
	mov	w0, 0
	ldr	x3, .LC178
	ldr	x1, .LC180
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L44
	.size	VP9HAL_V5R6C1_CfgTileMsg, .-VP9HAL_V5R6C1_CfgTileMsg
	.align	3
.LC178:
	.xword	.LC46
	.align	3
.LC179:
	.xword	.LANCHOR0
	.align	3
.LC180:
	.xword	.LC49
	.align	3
.LC182:
	.xword	.LC181
	.align	3
.LC184:
	.xword	.LC183
	.align	3
.LC186:
	.xword	.LC185
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC190:
	.xword	.LC189
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC194:
	.xword	.LC193
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC208:
	.xword	.LC207
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_CalcSize
	.type	VP9HAL_V5R6C1_CalcSize, %function
VP9HAL_V5R6C1_CalcSize:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 270336
	bl	_mcount
	ldr	w0, [x19, 2480]
	ldr	w21, [x19, 2088]
	ldr	w20, [x19, 2092]
	ldr	w24, [x19, 2468]
	lsl	w21, w21, 6
	ldr	w23, [x19, 2472]
	bl	GetCompressRatio
	mov	w22, w0
	ldr	w0, [x19, 2484]
	lsl	w20, w20, 6
	bl	GetCompressRatio
	add	w1, w21, 255
	and	w3, w1, -256
	lsl	w2, w3, 4
	mul	w1, w22, w2
	asr	w2, w2, 1
	cmp	w1, wzr
	mul	w0, w2, w0
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	add	w4, w0, 7
	cmp	w0, wzr
	asr	w1, w1, 3
	csel	w0, w4, w0, lt
	add	w2, w20, 63
	asr	w4, w0, 3
	and	w5, w2, -64
	lsr	w0, w1, 4
	cmp	w24, 1
	ccmp	w23, wzr, 0, eq
	str	w1, [x19, 2096]
	mul	w0, w0, w5
	str	w4, [x19, 2104]
	str	w0, [x19, 2108]
	beq	.L56
	str	wzr, [x19, 2500]
	str	wzr, [x19, 2504]
.L55:
	add	w2, w3, 3
	cmp	w3, wzr
	csel	w1, w2, w3, lt
	lsl	w2, w0, 2
	asr	w1, w1, 2
	sub	w0, w2, w0
	lsl	w1, w1, 5
	lsr	w0, w0, 1
	lsr	w2, w1, 5
	str	w0, [x19, 2512]
	str	w1, [x19, 2508]
	mul	w0, w2, w5
	str	w0, [x19, 2516]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L56:
	adds	w1, w21, 2047
	add	w21, w21, 4094
	csel	w21, w21, w1, mi
	add	w20, w20, 126
	and	w21, w21, -2048
	cmp	w21, wzr
	add	w1, w21, 127
	csel	w21, w1, w21, lt
	cmp	w2, wzr
	csel	w2, w20, w2, lt
	asr	w21, w21, 7
	asr	w2, w2, 6
	str	w21, [x19, 2500]
	lsl	w2, w2, 5
	mul	w2, w2, w21
	str	w2, [x19, 2504]
	add	w0, w0, w2
	str	w0, [x19, 2108]
	b	.L55
	.size	VP9HAL_V5R6C1_CalcSize, .-VP9HAL_V5R6C1_CalcSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V5R6C1_StartDec
	.type	VP9HAL_V5R6C1_StartDec, %function
VP9HAL_V5R6C1_StartDec:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	x22, x2
	bl	_mcount
	ldr	x23, .LC209
	sxtw	x0, w21
	cmp	w21, wzr
	lsl	x19, x0, 6
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	add	x19, x19, x23
	bgt	.L68
	bne	.L66
	add	x0, x20, 270336
	ldr	w1, [x0, 2088]
	cmp	w1, 512
	bhi	.L62
	ldr	w0, [x0, 2092]
	cmp	w0, 512
	bhi	.L62
	ldr	x0, [x23]
	cbz	x0, .L69
.L64:
	mov	x0, x20
	bl	VP9HAL_V5R6C1_CalcSize
	mov	x3, x22
	mov	w2, 0
	mov	x1, x19
	mov	x0, x20
	bl	VP9HAL_V5R6C1_CfgReg
	mov	w2, 0
	mov	x1, x19
	mov	x0, x20
	bl	VP9HAL_V5R6C1_CfgFrameMsg
	mov	w2, 0
	mov	x1, x19
	mov	x0, x20
	bl	VP9HAL_V5R6C1_CfgTileMsg
	mov	w0, 0
.L59:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L69:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L65
	str	x0, [x23]
	b	.L64
	.p2align 3
.L68:
	ldr	x2, .LC210
	mov	w4, 0
	ldr	x1, .LC211
	mov	w3, w21
	add	x2, x2, 88
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.p2align 3
.L62:
	ldr	x2, .LC210
	mov	w0, 0
	ldr	x3, .LC215
	ldr	x1, .LC216
	add	x2, x2, 88
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.p2align 3
.L66:
	ldr	x1, .LC213
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
.L65:
	ldr	x1, .LC217
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.size	VP9HAL_V5R6C1_StartDec, .-VP9HAL_V5R6C1_StartDec
	.align	3
.LC209:
	.xword	g_HwMem
	.align	3
.LC210:
	.xword	.LANCHOR0
	.align	3
.LC211:
	.xword	.LC6
	.align	3
.LC213:
	.xword	.LC212
	.align	3
.LC215:
	.xword	.LC214
	.align	3
.LC216:
	.xword	.LC49
	.align	3
.LC217:
	.xword	.LC10
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.12326, %object
	.size	__func__.12326, 21
__func__.12326:
	.string	"VP9HAL_V5R6C1_CfgReg"
	.zero	3
	.type	__func__.12343, %object
	.size	__func__.12343, 26
__func__.12343:
	.string	"VP9HAL_V5R6C1_CfgFrameMsg"
	.zero	6
	.type	__func__.12354, %object
	.size	__func__.12354, 25
__func__.12354:
	.string	"VP9HAL_V5R6C1_CfgTileMsg"
	.zero	7
	.type	__func__.12375, %object
	.size	__func__.12375, 23
__func__.12375:
	.string	"VP9HAL_V5R6C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC6:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC8:
	ASCII(.string	"VdhId is wrong! VP9HAL_V5R6C1_CfgReg\n" )
	.zero	2
.LC10:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC12:
	ASCII(.string	"BASIC_CFG0 = 0x%x\n" )
	.zero	5
.LC14:
	ASCII(.string	"BASIC_CFG1 = 0x%x\n" )
	.zero	5
.LC16:
	ASCII(.string	"AVM_ADDR = 0x%x\n" )
	.zero	7
.LC18:
	ASCII(.string	"VAM_ADDR = 0x%x\n" )
	.zero	7
.LC20:
	ASCII(.string	"STREAM_BASE_ADDR = 0x%x\n" )
	.zero	7
.LC22:
	ASCII(.string	"PPFD_BUF_ADDR = 0x%x\n" )
	.zero	2
.LC24:
	ASCII(.string	"PPFD_BUF_LEN = 0x%x\n" )
	.zero	3
.LC26:
	ASCII(.string	"FF_APT_EN = 0x%x\n" )
	.zero	6
.LC28:
	ASCII(.string	"DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	7
.LC30:
	ASCII(.string	"YSTADDR_1D = 0x%x\n" )
	.zero	5
.LC32:
	ASCII(.string	"YSTRIDE_1D = 0x%x\n" )
	.zero	5
.LC34:
	ASCII(.string	"UVOFFSET_1D = 0x%x\n" )
	.zero	4
.LC36:
	ASCII(.string	"HEAD_INF_OFFSET = 0x%x\n" )
.LC38:
	ASCII(.string	"HEVC_VFMW_YSTRIDE_2BIT = 0x%x\n" )
	.zero	1
.LC40:
	ASCII(.string	"HEVC_VFMW_YOFFSET_2BIT = 0x%x\n" )
	.zero	1
.LC42:
	ASCII(.string	"HEVC_VFMW_UVOFFSET_2BIT = 0x%x\n" )
.LC44:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC46:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC49:
	ASCII(.string	"%s: %s\n" )
.LC51:
	ASCII(.string	"PicMsg D[0] = 0x%x\n" )
	.zero	4
.LC53:
	ASCII(.string	"PicMsg D[1] = 0x%x\n" )
	.zero	4
.LC55:
	ASCII(.string	"PicMsg D[2] = 0x%x\n" )
	.zero	4
.LC57:
	ASCII(.string	"PicMsg D[3] = 0x%x\n" )
	.zero	4
.LC59:
	ASCII(.string	"PicMsg D[4] = 0x%x\n" )
	.zero	4
.LC61:
	ASCII(.string	"PicMsg D[5] = 0x%x\n" )
	.zero	4
.LC63:
	ASCII(.string	"PicMsg D[6] = 0x%x\n" )
	.zero	4
.LC65:
	ASCII(.string	"PicMsg D[7] = 0x%x\n" )
	.zero	4
.LC67:
	ASCII(.string	"PicMsg D[8] = 0x%x\n" )
	.zero	4
.LC69:
	ASCII(.string	"PicMsg D[9] = 0x%x\n" )
	.zero	4
.LC71:
	ASCII(.string	"PicMsg D[10] = 0x%x\n" )
	.zero	3
.LC73:
	ASCII(.string	"PicMsg D[11] = 0x%x\n" )
	.zero	3
.LC75:
	ASCII(.string	"PicMsg D[12] = 0x%x\n" )
	.zero	3
.LC77:
	ASCII(.string	"PicMsg D[13] = 0x%x\n" )
	.zero	3
.LC79:
	ASCII(.string	"PicMsg D[14] = 0x%x\n" )
	.zero	3
.LC81:
	ASCII(.string	"PicMsg D[15] = 0x%x\n" )
	.zero	3
.LC83:
	ASCII(.string	"PicMsg D[16] = 0x%x\n" )
	.zero	3
.LC85:
	ASCII(.string	"PicMsg D[17] = 0x%x\n" )
	.zero	3
.LC87:
	ASCII(.string	"PicMsg D[18] = 0x%x\n" )
	.zero	3
.LC89:
	ASCII(.string	"PicMsg D[19] = 0x%x\n" )
	.zero	3
.LC91:
	ASCII(.string	"PicMsg D[20] = 0x%x\n" )
	.zero	3
.LC93:
	ASCII(.string	"PicMsg D[21] = 0x%x\n" )
	.zero	3
.LC95:
	ASCII(.string	"PicMsg D[22] = 0x%x\n" )
	.zero	3
.LC97:
	ASCII(.string	"PicMsg D[23] = 0x%x\n" )
	.zero	3
.LC99:
	ASCII(.string	"PicMsg D[24] = 0x%x\n" )
	.zero	3
.LC101:
	ASCII(.string	"PicMsg D[25] = 0x%x\n" )
	.zero	3
.LC103:
	ASCII(.string	"PicMsg D[26] = 0x%x\n" )
	.zero	3
.LC105:
	ASCII(.string	"PicMsg D[27] = 0x%x\n" )
	.zero	3
.LC107:
	ASCII(.string	"PicMsg D[28] = 0x%x\n" )
	.zero	3
.LC109:
	ASCII(.string	"PicMsg D[29] = 0x%x\n" )
	.zero	3
.LC111:
	ASCII(.string	"PicMsg D[30] = 0x%x\n" )
	.zero	3
.LC113:
	ASCII(.string	"PicMsg D[32] = 0x%x\n" )
	.zero	3
.LC115:
	ASCII(.string	"PicMsg D[33] = 0x%x\n" )
	.zero	3
.LC117:
	ASCII(.string	"PicMsg D[34] = 0x%x\n" )
	.zero	3
.LC119:
	ASCII(.string	"PicMsg D[35] = 0x%x\n" )
	.zero	3
.LC121:
	ASCII(.string	"PicMsg D[36] = 0x%x\n" )
	.zero	3
.LC123:
	ASCII(.string	"PicMsg D[37] = 0x%x\n" )
	.zero	3
.LC125:
	ASCII(.string	"PicMsg D[38] = 0x%x\n" )
	.zero	3
.LC127:
	ASCII(.string	"PicMsg D[39] = 0x%x\n" )
	.zero	3
.LC129:
	ASCII(.string	"%s: pu8Vir = NULL\n" )
	.zero	5
.LC132:
	ASCII(.string	"PicMsg D[40] = 0x%x\n" )
	.zero	3
.LC134:
	ASCII(.string	"PicMsg D[41] = 0x%x\n" )
	.zero	3
.LC136:
	ASCII(.string	"PicMsg D[42] = 0x%x\n" )
	.zero	3
.LC138:
	ASCII(.string	"PicMsg D[43] = 0x%x\n" )
	.zero	3
.LC140:
	ASCII(.string	"PicMsg D[45] = 0x%x\n" )
	.zero	3
.LC142:
	ASCII(.string	"PicMsg D[46] = 0x%x\n" )
	.zero	3
.LC144:
	ASCII(.string	"PicMsg D[47] = 0x%x\n" )
	.zero	3
.LC146:
	ASCII(.string	"PicMsg D[48] = 0x%x\n" )
	.zero	3
.LC148:
	ASCII(.string	"PicMsg D[49] = 0x%x\n" )
	.zero	3
.LC150:
	ASCII(.string	"PicMsg D[50] = 0x%x\n" )
	.zero	3
.LC152:
	ASCII(.string	"PicMsg D[51] = 0x%x\n" )
	.zero	3
.LC154:
	ASCII(.string	"PicMsg D[52] = 0x%x\n" )
	.zero	3
.LC156:
	ASCII(.string	"PicMsg D[53] = 0x%x\n" )
	.zero	3
.LC158:
	ASCII(.string	"PicMsg D[54] = 0x%x\n" )
	.zero	3
.LC160:
	ASCII(.string	"PicMsg D[55] = 0x%x\n" )
	.zero	3
.LC162:
	ASCII(.string	"PicMsg D[56] = 0x%x\n" )
	.zero	3
.LC164:
	ASCII(.string	"PicMsg D[57] = 0x%x\n" )
	.zero	3
.LC166:
	ASCII(.string	"PicMsg D[58] = 0x%x\n" )
	.zero	3
.LC168:
	ASCII(.string	"PicMsg D[59] = 0x%x\n" )
	.zero	3
.LC170:
	ASCII(.string	"PicMsg D[60] = 0x%x\n" )
	.zero	3
.LC172:
	ASCII(.string	"PicMsg D[61] = 0x%x\n" )
	.zero	3
.LC174:
	ASCII(.string	"PicMsg D[62] = 0x%x\n" )
	.zero	3
.LC176:
	ASCII(.string	"PicMsg D[63] = 0x%x\n" )
	.zero	3
.LC181:
	ASCII(.string	"ERROR: pVp9DecParam->TotalTileNum(%d) out of [0-1024]\n" )
	.zero	1
.LC183:
	ASCII(.string	"TileMsg D[0] = 0x%x\n" )
	.zero	3
.LC185:
	ASCII(.string	"TileMsg D[1] = 0x%x\n" )
	.zero	3
.LC187:
	ASCII(.string	"TileMsg D[2] = 0x%x\n" )
	.zero	3
.LC189:
	ASCII(.string	"TileMsg D[3] = 0x%x\n" )
	.zero	3
.LC191:
	ASCII(.string	"TileMsg D[4] = 0x%x\n" )
	.zero	3
.LC193:
	ASCII(.string	"TileMsg D[5] = 0x%x\n" )
	.zero	3
.LC195:
	ASCII(.string	"TileMsg D[6] = 0x%x\n" )
	.zero	3
.LC197:
	ASCII(.string	"TileMsg D[7] = 0x%x\n" )
	.zero	3
.LC199:
	ASCII(.string	"TileMsg D[8] = 0x%x\n" )
	.zero	3
.LC201:
	ASCII(.string	"TileMsg D[9] = 0x%x\n" )
	.zero	3
.LC203:
	ASCII(.string	"TileMsg D[10] = 0x%x\n" )
	.zero	2
.LC205:
	ASCII(.string	"TileMsg D[11] = 0x%x\n" )
	.zero	2
.LC207:
	ASCII(.string	"TileMsg D[63] = 0x%x\n" )
	.zero	2
.LC212:
	ASCII(.string	"VdhId is wrong! VP9HAL_V5R6C1_StartDec\n" )
.LC214:
	ASCII(.string	"picture width out of range" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
