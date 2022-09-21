#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_vp9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_InitHal
	.type	VP9HAL_V4R3C1_InitHal, %function
VP9HAL_V4R3C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VP9HAL_V4R3C1_InitHal, .-VP9HAL_V4R3C1_InitHal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_CfgReg
	.type	VP9HAL_V4R3C1_CfgReg, %function
VP9HAL_V4R3C1_CfgReg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	x19, x3
	mov	x22, x1
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
	bne	.L24
	ldr	x2, .LC5
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L16
	ldr	w23, [x0, 1232]
.L5:
	cmp	w1, 1
	beq	.L6
	strb	w23, [x19, 1]
.L6:
	cmp	w21, wzr
	bgt	.L25
	bne	.L21
	ldr	x0, [x22]
	cbz	x0, .L26
.L11:
	add	x20, x20, 270336
	ldr	w5, [x22, 1212]
	ldr	w1, [x29, 76]
	mov	x3, x19
	and	w5, w5, -16
	mov	w0, 8
	str	w5, [x20, 2352]
	mov	w2, 0
	ldr	w4, [x20, 2088]
	mov	w21, 3
	ldr	w5, [x22, 1216]
	and	w5, w5, -16
	str	w5, [x20, 2356]
	ldr	w5, [x20, 2092]
	mul	w4, w4, w5
	sub	w4, w4, #1
	bfi	w1, w4, 0, 20
	str	w1, [x29, 76]
	ubfx	x1, x1, 24, 6
	strb	w1, [x29, 79]
	ldr	w24, [x29, 76]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC13
	mov	w2, w24
	mov	w0, w21
	bl	dprint_vfmw
	strh	w21, [x29, 78]
	mov	w0, 0
	ldr	w2, [x20, 2468]
	bfi	w0, w23, 4, 1
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
	ldr	w24, [x29, 76]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC15
	mov	w2, w24
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w24, [x22, 72]
	mov	x3, x19
	mov	w0, 16
	and	w24, w24, -16
	mov	w2, 0
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC17
	mov	w2, w24
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w24, [x22, 56]
	mov	x3, x19
	mov	w0, 20
	and	w24, w24, -16
	mov	w2, 0
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC19
	mov	w2, w24
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w24, [x20, 2128]
	mov	x3, x19
	mov	w0, 24
	mov	w1, w24
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC21
	mov	w2, w24
	mov	w0, w21
	bl	dprint_vfmw
	ldr	w24, [x22, 1180]
	mov	x3, x19
	mov	w0, 128
	and	w24, w24, -16
	mov	w2, 0
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC23
	mov	w2, w24
	mov	w0, w21
	mov	w24, 2
	bl	dprint_vfmw
	ldr	w22, [x22, 1184]
	mov	x3, x19
	mov	w0, 132
	mov	w1, w22
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC25
	mov	w2, w22
	mov	w0, w21
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	dprint_vfmw
	str	w24, [x29, 76]
	mov	x3, x19
	mov	w1, w24
	mov	w0, 152
	mov	w2, 0
	bl	MFDE_ConfigReg
	ldr	x1, .LC27
	mov	w2, w24
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
	cmp	w23, 1
	beq	.L27
	ldr	w22, [x20, 2092]
	mov	w0, 92
	mov	w2, 0
	mov	x3, x19
	lsl	w22, w22, 6
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC29
	mov	w2, w22
	mov	w0, w21
	bl	dprint_vfmw
.L15:
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
	mov	w2, 0
	mov	w1, w21
	bl	MFDE_ConfigReg
	ldr	x1, .LC37
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w20, [x20, 2496]
	mov	x3, x19
	mov	w0, 112
	mov	w2, 0
	mov	w1, w20
	bl	MFDE_ConfigReg
	ldr	x1, .LC39
	mov	w2, w20
	mov	w0, 3
	bl	dprint_vfmw
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
.L27:
	mov	x3, x19
	mov	w2, 0
	mov	w1, 60
	mov	w0, 92
	bl	MFDE_ConfigReg
	ldr	x1, .LC29
	mov	w2, 60
	mov	w0, w21
	bl	dprint_vfmw
	b	.L15
	.p2align 3
.L16:
	mov	w23, 0
	b	.L5
	.p2align 3
.L26:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L12
	str	x0, [x22]
	b	.L11
	.p2align 3
.L25:
	ldr	x2, .LC2
	mov	w4, 0
	ldr	x1, .LC7
	mov	w3, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
	.p2align 3
.L21:
	ldr	x1, .LC9
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4
.L24:
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
	.size	VP9HAL_V4R3C1_CfgReg, .-VP9HAL_V4R3C1_CfgReg
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_CfgFrameMsg
	.type	VP9HAL_V4R3C1_CfgFrameMsg, %function
VP9HAL_V4R3C1_CfgFrameMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x21, 72]
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L32
	ldr	w0, [x20]
	add	x22, x20, 270336
	str	w0, [x19]
	mov	w0, 4
	ldr	x1, .LC46
	ldr	w2, [x19]
	bl	dprint_vfmw
	ldr	w0, [x20, 4]
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	x1, .LC48
	ldr	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x20, 8]
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	x1, .LC50
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x20, 12]
	str	w0, [x19, 12]
	mov	w0, 4
	ldr	x1, .LC52
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	w0, [x20, 16]
	str	w0, [x19, 16]
	mov	w0, 4
	ldr	x1, .LC54
	ldr	w2, [x19, 16]
	bl	dprint_vfmw
	ldr	w0, [x20, 20]
	str	w0, [x19, 20]
	mov	w0, 4
	ldr	x1, .LC56
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x20, 24]
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	x1, .LC58
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	w0, [x20, 28]
	str	w0, [x19, 28]
	mov	w0, 4
	ldr	x1, .LC60
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	w0, [x20, 32]
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	x1, .LC62
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	w0, [x20, 36]
	str	w0, [x19, 36]
	mov	w0, 4
	ldr	x1, .LC64
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	str	w0, [x19, 40]
	mov	w0, 4
	ldr	x1, .LC66
	ldr	w2, [x19, 40]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	str	w0, [x19, 44]
	mov	w0, 4
	ldr	x1, .LC68
	ldr	w2, [x19, 44]
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	str	w0, [x19, 48]
	mov	w0, 4
	ldr	x1, .LC70
	ldr	w2, [x19, 48]
	bl	dprint_vfmw
	ldr	w0, [x20, 52]
	str	w0, [x19, 52]
	mov	w0, 4
	ldr	x1, .LC72
	ldr	w2, [x19, 52]
	bl	dprint_vfmw
	ldr	w0, [x20, 56]
	str	w0, [x19, 56]
	mov	w0, 4
	ldr	x1, .LC74
	ldr	w2, [x19, 56]
	bl	dprint_vfmw
	ldr	w0, [x20, 60]
	str	w0, [x19, 60]
	mov	w0, 4
	ldr	x1, .LC76
	ldr	w2, [x19, 60]
	bl	dprint_vfmw
	ldr	w0, [x20, 64]
	str	w0, [x19, 64]
	mov	w0, 4
	ldr	x1, .LC78
	ldr	w2, [x19, 64]
	bl	dprint_vfmw
	ldr	w0, [x20, 68]
	str	w0, [x19, 68]
	mov	w0, 4
	ldr	x1, .LC80
	ldr	w2, [x19, 68]
	bl	dprint_vfmw
	ldr	w0, [x20, 72]
	str	w0, [x19, 72]
	mov	w0, 4
	ldr	x1, .LC82
	ldr	w2, [x19, 72]
	bl	dprint_vfmw
	ldr	w0, [x20, 76]
	str	w0, [x19, 76]
	mov	w0, 4
	ldr	x1, .LC84
	ldr	w2, [x19, 76]
	bl	dprint_vfmw
	ldr	w0, [x20, 80]
	str	w0, [x19, 80]
	mov	w0, 4
	ldr	x1, .LC86
	ldr	w2, [x19, 80]
	bl	dprint_vfmw
	ldr	w0, [x20, 84]
	str	w0, [x19, 84]
	mov	w0, 4
	ldr	x1, .LC88
	ldr	w2, [x19, 84]
	bl	dprint_vfmw
	ldr	w0, [x20, 88]
	str	w0, [x19, 88]
	mov	w0, 4
	ldr	x1, .LC90
	ldr	w2, [x19, 88]
	bl	dprint_vfmw
	ldr	w0, [x20, 92]
	str	w0, [x19, 92]
	mov	w0, 4
	ldr	x1, .LC92
	ldr	w2, [x19, 92]
	bl	dprint_vfmw
	ldr	w0, [x20, 96]
	str	w0, [x19, 96]
	mov	w0, 4
	ldr	x1, .LC94
	ldr	w2, [x19, 96]
	bl	dprint_vfmw
	ldr	w0, [x20, 100]
	str	w0, [x19, 100]
	mov	w0, 4
	ldr	x1, .LC96
	ldr	w2, [x19, 100]
	bl	dprint_vfmw
	ldr	w0, [x20, 104]
	str	w0, [x19, 104]
	mov	w0, 4
	ldr	x1, .LC98
	ldr	w2, [x19, 104]
	bl	dprint_vfmw
	ldr	w0, [x20, 108]
	str	w0, [x19, 108]
	mov	w0, 4
	ldr	x1, .LC100
	ldr	w2, [x19, 108]
	bl	dprint_vfmw
	ldr	w0, [x20, 112]
	str	w0, [x19, 112]
	mov	w0, 4
	ldr	x1, .LC102
	ldr	w2, [x19, 112]
	bl	dprint_vfmw
	ldr	w0, [x20, 116]
	str	w0, [x19, 116]
	mov	w0, 4
	ldr	x1, .LC104
	ldr	w2, [x19, 116]
	bl	dprint_vfmw
	ldr	w0, [x20, 120]
	str	w0, [x19, 120]
	mov	w0, 4
	ldr	x1, .LC106
	ldr	w2, [x19, 120]
	bl	dprint_vfmw
	ldr	w0, [x22, 2440]
	str	w0, [x19, 128]
	mov	w0, 4
	ldr	x1, .LC108
	ldr	w2, [x19, 128]
	bl	dprint_vfmw
	ldr	w0, [x22, 2444]
	str	w0, [x19, 132]
	mov	w0, 4
	ldr	x1, .LC110
	ldr	w2, [x19, 132]
	bl	dprint_vfmw
	ldr	w0, [x22, 2448]
	str	w0, [x19, 136]
	mov	w0, 4
	ldr	x1, .LC112
	ldr	w2, [x19, 136]
	bl	dprint_vfmw
	ldr	w0, [x22, 2452]
	str	w0, [x19, 140]
	mov	w0, 4
	ldr	x1, .LC114
	ldr	w2, [x19, 140]
	bl	dprint_vfmw
	ldr	w2, [x21, 1160]
	mov	w0, 4
	ldr	x1, .LC116
	and	w2, w2, -16
	str	w2, [x19, 144]
	ldr	w2, [x19, 144]
	bl	dprint_vfmw
	ldr	w2, [x21, 1164]
	mov	w0, 4
	ldr	x1, .LC118
	and	w2, w2, -16
	str	w2, [x19, 148]
	ldr	w2, [x19, 148]
	bl	dprint_vfmw
	ldr	w2, [x21, 1168]
	mov	w0, 4
	ldr	x1, .LC120
	and	w2, w2, -16
	str	w2, [x19, 152]
	ldr	w2, [x19, 152]
	bl	dprint_vfmw
	ldr	w23, [x21, 1212]
	ldr	x1, .LC122
	mov	w0, 4
	and	w23, w23, -16
	str	w23, [x19, 156]
	ldr	w2, [x19, 156]
	bl	dprint_vfmw
	mov	w0, w23
	bl	MEM_Phy2Vir
	mov	x23, x0
	cbz	x0, .L33
	ldr	x24, .LC125
	add	x1, x20, 262144
	mov	x2, 4608
	add	x1, x1, 1029
	ldr	x3, [x24, 104]
	blr	x3
	ldr	w2, [x21, 1176]
	mov	w0, 4
	ldr	x1, .LC127
	and	w2, w2, -16
	str	w2, [x19, 160]
	ldr	w2, [x19, 160]
	bl	dprint_vfmw
	ldr	w2, [x21, 1216]
	mov	w0, 4
	ldr	x1, .LC129
	and	w2, w2, -16
	str	w2, [x19, 164]
	ldr	w2, [x19, 164]
	bl	dprint_vfmw
	ldr	w2, [x22, 2456]
	mov	w0, 4
	ldr	x1, .LC131
	and	w2, w2, -16
	str	w2, [x19, 168]
	ldr	w2, [x19, 168]
	bl	dprint_vfmw
	ldr	w2, [x21, 1208]
	mov	w0, 4
	ldr	x1, .LC133
	and	w2, w2, -16
	str	w2, [x19, 172]
	ldr	w2, [x19, 172]
	bl	dprint_vfmw
	ldr	w0, [x20, 180]
	str	w0, [x19, 180]
	mov	w0, 4
	ldr	x1, .LC135
	ldr	w2, [x19, 180]
	bl	dprint_vfmw
	ldr	w0, [x20, 184]
	str	w0, [x19, 184]
	mov	w0, 4
	ldr	x1, .LC137
	ldr	w2, [x19, 184]
	bl	dprint_vfmw
	ldr	w0, [x20, 188]
	str	w0, [x19, 188]
	mov	w0, 4
	ldr	x1, .LC139
	ldr	w2, [x19, 188]
	bl	dprint_vfmw
	ldr	w0, [x20, 192]
	str	w0, [x19, 192]
	mov	w0, 4
	ldr	x1, .LC141
	ldr	w2, [x19, 192]
	bl	dprint_vfmw
	ldr	w0, [x20, 196]
	str	w0, [x19, 196]
	mov	w0, 4
	ldr	x1, .LC143
	ldr	w2, [x19, 196]
	bl	dprint_vfmw
	ldr	w0, [x20, 200]
	str	w0, [x19, 200]
	mov	w0, 4
	ldr	x1, .LC145
	ldr	w2, [x19, 200]
	bl	dprint_vfmw
	ldr	w0, [x20, 204]
	str	w0, [x19, 204]
	mov	w0, 4
	ldr	x1, .LC147
	ldr	w2, [x19, 204]
	bl	dprint_vfmw
	ldr	w0, [x20, 208]
	str	w0, [x19, 208]
	mov	w0, 4
	ldr	x1, .LC149
	ldr	w2, [x19, 208]
	bl	dprint_vfmw
	ldr	w0, [x20, 212]
	str	w0, [x19, 212]
	mov	w0, 4
	ldr	x1, .LC151
	ldr	w2, [x19, 212]
	bl	dprint_vfmw
	ldr	w0, [x20, 216]
	str	w0, [x19, 216]
	mov	w0, 4
	ldr	x1, .LC153
	ldr	w2, [x19, 216]
	bl	dprint_vfmw
	ldr	w0, [x20, 220]
	str	w0, [x19, 220]
	mov	w0, 4
	ldr	x1, .LC155
	ldr	w2, [x19, 220]
	bl	dprint_vfmw
	ldr	w0, [x20, 224]
	str	w0, [x19, 224]
	mov	w0, 4
	ldr	x1, .LC157
	ldr	w2, [x19, 224]
	bl	dprint_vfmw
	ldr	w0, [x20, 228]
	str	w0, [x19, 228]
	mov	w0, 4
	ldr	x1, .LC159
	ldr	w2, [x19, 228]
	bl	dprint_vfmw
	ldr	w0, [x20, 232]
	str	w0, [x19, 232]
	mov	w0, 4
	ldr	x1, .LC161
	ldr	w2, [x19, 232]
	bl	dprint_vfmw
	ldr	w0, [x20, 236]
	str	w0, [x19, 236]
	mov	w0, 4
	ldr	x1, .LC163
	ldr	w2, [x19, 236]
	bl	dprint_vfmw
	ldr	w0, [x20, 240]
	str	w0, [x19, 240]
	mov	w0, 4
	ldr	x1, .LC165
	ldr	w2, [x19, 240]
	bl	dprint_vfmw
	ldr	w0, [x20, 244]
	str	w0, [x19, 244]
	mov	w0, 4
	ldr	x1, .LC167
	ldr	w2, [x19, 244]
	bl	dprint_vfmw
	ldr	w0, [x20, 248]
	str	w0, [x19, 248]
	mov	w0, 4
	ldr	x1, .LC169
	ldr	w2, [x19, 248]
	bl	dprint_vfmw
	ldr	w0, [x21, 76]
	str	w0, [x19, 252]
	mov	w0, 4
	ldr	x1, .LC171
	ldr	w2, [x19, 252]
	bl	dprint_vfmw
	ldr	w1, [x22, 2352]
	mov	x0, x23
	ldr	x3, [x24, 280]
	mov	w2, 4608
	blr	x3
	mov	w0, 0
.L30:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L32:
	ldr	x2, .LC42
	mov	w0, 0
	ldr	x3, .LC41
	ldr	x1, .LC44
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L30
.L33:
	ldr	x2, .LC42
	mov	w0, 0
	ldr	x1, .LC124
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L30
	.size	VP9HAL_V4R3C1_CfgFrameMsg, .-VP9HAL_V4R3C1_CfgFrameMsg
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	.LANCHOR0
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
.LC125:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC129:
	.xword	.LC128
	.align	3
.LC131:
	.xword	.LC130
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_CfgTileMsg
	.type	VP9HAL_V4R3C1_CfgTileMsg, %function
VP9HAL_V4R3C1_CfgTileMsg:
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
	cbz	x0, .L43
	add	x21, x20, 262144
	ldr	w2, [x21, 1024]
	sub	w0, w2, #1
	cmp	w0, 1023
	bhi	.L44
.L37:
	cbz	w2, .L40
	ldr	x28, .LC178
	mov	w24, w19
	ldr	x27, .LC180
	mov	w23, 0
	ldr	x26, .LC182
	.p2align 2
.L38:
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
	ldr	x1, .LC184
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	w0, [x25, 1040]
	str	w0, [x19, 16]
	mov	w0, 4
	ldr	x1, .LC186
	ldr	w2, [x19, 16]
	bl	dprint_vfmw
	ldr	w0, [x25, 1044]
	str	w0, [x19, 20]
	mov	w0, 4
	ldr	x1, .LC188
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x25, 1048]
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	x1, .LC190
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	w0, [x25, 1052]
	str	w0, [x19, 28]
	mov	w0, 4
	ldr	x1, .LC192
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	w0, [x25, 1056]
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	x1, .LC194
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	w0, [x25, 1060]
	str	w0, [x19, 36]
	mov	w0, 4
	ldr	x1, .LC196
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	ldr	w0, [x25, 1064]
	str	w0, [x19, 40]
	mov	w0, 4
	ldr	x1, .LC198
	ldr	w2, [x19, 40]
	bl	dprint_vfmw
	ldr	w0, [x25, 1068]
	str	w0, [x19, 44]
	mov	w0, 4
	ldr	x1, .LC200
	ldr	w2, [x19, 44]
	bl	dprint_vfmw
	ldr	w0, [x25, 1276]
	str	w0, [x19, 252]
	mov	w0, 4
	ldr	x1, .LC202
	ldr	w2, [x19, 252]
	bl	dprint_vfmw
	cmp	w23, wzr
	add	w23, w23, 1
	ble	.L39
	str	w24, [x19, -4]
.L39:
	ldr	w0, [x21, 1024]
	add	w24, w24, 256
	cmp	w0, w23
	bhi	.L38
	cmp	w0, 1
	bls	.L40
	ubfiz	x1, x0, 8, 26
	mov	w0, 0
	add	x6, x22, x1
	str	wzr, [x6, -4]
.L36:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L44:
	ldr	x1, .LC176
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w2, [x21, 1024]
	b	.L37
	.p2align 3
.L40:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L43:
	ldr	x2, .LC173
	mov	w0, 0
	ldr	x3, .LC172
	ldr	x1, .LC174
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L36
	.size	VP9HAL_V4R3C1_CfgTileMsg, .-VP9HAL_V4R3C1_CfgTileMsg
	.align	3
.LC172:
	.xword	.LC40
	.align	3
.LC173:
	.xword	.LANCHOR0
	.align	3
.LC174:
	.xword	.LC43
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC180:
	.xword	.LC179
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_CalcSize
	.type	VP9HAL_V4R3C1_CalcSize, %function
VP9HAL_V4R3C1_CalcSize:
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
	beq	.L48
	str	wzr, [x19, 2500]
	str	wzr, [x19, 2504]
.L47:
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
.L48:
	adds	w1, w21, 511
	add	w21, w21, 1022
	csel	w21, w21, w1, mi
	add	w20, w20, 126
	and	w21, w21, -512
	cmp	w21, wzr
	add	w1, w21, 63
	csel	w21, w1, w21, lt
	cmp	w2, wzr
	csel	w2, w20, w2, lt
	asr	w21, w21, 6
	asr	w2, w2, 6
	lsl	w21, w21, 1
	lsl	w2, w2, 5
	str	w21, [x19, 2500]
	mul	w2, w2, w21
	str	w2, [x19, 2504]
	add	w0, w0, w2
	str	w0, [x19, 2108]
	b	.L47
	.size	VP9HAL_V4R3C1_CalcSize, .-VP9HAL_V4R3C1_CalcSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9HAL_V4R3C1_StartDec
	.type	VP9HAL_V4R3C1_StartDec, %function
VP9HAL_V4R3C1_StartDec:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w1
	mov	x23, x2
	bl	_mcount
	ldr	x24, .LC203
	sxtw	x0, w20
	cmp	w20, wzr
	lsl	x19, x0, 6
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	add	x22, x19, x24
	bgt	.L56
	add	x0, x21, 270336
	ldr	w1, [x0, 2088]
	cmp	w1, 512
	bhi	.L53
	ldr	w0, [x0, 2092]
	cmp	w0, 512
	bhi	.L53
	ldr	x0, [x19, x24]
	cbz	x0, .L57
.L54:
	mov	x0, x21
	bl	VP9HAL_V4R3C1_CalcSize
	mov	x3, x23
	mov	w2, w20
	mov	x1, x22
	mov	x0, x21
	bl	VP9HAL_V4R3C1_CfgReg
	mov	w2, w20
	mov	x1, x22
	mov	x0, x21
	bl	VP9HAL_V4R3C1_CfgFrameMsg
	mov	w2, w20
	mov	x1, x22
	mov	x0, x21
	bl	VP9HAL_V4R3C1_CfgTileMsg
	mov	w0, 0
.L51:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L57:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L55
	str	x0, [x19, x24]
	b	.L54
	.p2align 3
.L56:
	ldr	x2, .LC204
	mov	w4, 0
	ldr	x1, .LC205
	mov	w3, w20
	add	x2, x2, 88
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L51
	.p2align 3
.L53:
	ldr	x2, .LC204
	mov	w0, 0
	ldr	x3, .LC207
	ldr	x1, .LC208
	add	x2, x2, 88
	bl	dprint_vfmw
	mov	w0, -1
	b	.L51
.L55:
	ldr	x1, .LC209
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L51
	.size	VP9HAL_V4R3C1_StartDec, .-VP9HAL_V4R3C1_StartDec
	.align	3
.LC203:
	.xword	g_HwMem
	.align	3
.LC204:
	.xword	.LANCHOR0
	.align	3
.LC205:
	.xword	.LC6
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC208:
	.xword	.LC43
	.align	3
.LC209:
	.xword	.LC10
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11757, %object
	.size	__func__.11757, 21
__func__.11757:
	.string	"VP9HAL_V4R3C1_CfgReg"
	.zero	3
	.type	__func__.11771, %object
	.size	__func__.11771, 26
__func__.11771:
	.string	"VP9HAL_V4R3C1_CfgFrameMsg"
	.zero	6
	.type	__func__.11782, %object
	.size	__func__.11782, 25
__func__.11782:
	.string	"VP9HAL_V4R3C1_CfgTileMsg"
	.zero	7
	.type	__func__.11803, %object
	.size	__func__.11803, 23
__func__.11803:
	.string	"VP9HAL_V4R3C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC6:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC8:
	ASCII(.string	"VdhId is wrong! VP9HAL_V4R3C1_CfgReg\n" )
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
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC40:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC43:
	ASCII(.string	"%s: %s\n" )
.LC45:
	ASCII(.string	"PicMsg D[0] = 0x%x\n" )
	.zero	4
.LC47:
	ASCII(.string	"PicMsg D[1] = 0x%x\n" )
	.zero	4
.LC49:
	ASCII(.string	"PicMsg D[2] = 0x%x\n" )
	.zero	4
.LC51:
	ASCII(.string	"PicMsg D[3] = 0x%x\n" )
	.zero	4
.LC53:
	ASCII(.string	"PicMsg D[4] = 0x%x\n" )
	.zero	4
.LC55:
	ASCII(.string	"PicMsg D[5] = 0x%x\n" )
	.zero	4
.LC57:
	ASCII(.string	"PicMsg D[6] = 0x%x\n" )
	.zero	4
.LC59:
	ASCII(.string	"PicMsg D[7] = 0x%x\n" )
	.zero	4
.LC61:
	ASCII(.string	"PicMsg D[8] = 0x%x\n" )
	.zero	4
.LC63:
	ASCII(.string	"PicMsg D[9] = 0x%x\n" )
	.zero	4
.LC65:
	ASCII(.string	"PicMsg D[10] = 0x%x\n" )
	.zero	3
.LC67:
	ASCII(.string	"PicMsg D[11] = 0x%x\n" )
	.zero	3
.LC69:
	ASCII(.string	"PicMsg D[12] = 0x%x\n" )
	.zero	3
.LC71:
	ASCII(.string	"PicMsg D[13] = 0x%x\n" )
	.zero	3
.LC73:
	ASCII(.string	"PicMsg D[14] = 0x%x\n" )
	.zero	3
.LC75:
	ASCII(.string	"PicMsg D[15] = 0x%x\n" )
	.zero	3
.LC77:
	ASCII(.string	"PicMsg D[16] = 0x%x\n" )
	.zero	3
.LC79:
	ASCII(.string	"PicMsg D[17] = 0x%x\n" )
	.zero	3
.LC81:
	ASCII(.string	"PicMsg D[18] = 0x%x\n" )
	.zero	3
.LC83:
	ASCII(.string	"PicMsg D[19] = 0x%x\n" )
	.zero	3
.LC85:
	ASCII(.string	"PicMsg D[20] = 0x%x\n" )
	.zero	3
.LC87:
	ASCII(.string	"PicMsg D[21] = 0x%x\n" )
	.zero	3
.LC89:
	ASCII(.string	"PicMsg D[22] = 0x%x\n" )
	.zero	3
.LC91:
	ASCII(.string	"PicMsg D[23] = 0x%x\n" )
	.zero	3
.LC93:
	ASCII(.string	"PicMsg D[24] = 0x%x\n" )
	.zero	3
.LC95:
	ASCII(.string	"PicMsg D[25] = 0x%x\n" )
	.zero	3
.LC97:
	ASCII(.string	"PicMsg D[26] = 0x%x\n" )
	.zero	3
.LC99:
	ASCII(.string	"PicMsg D[27] = 0x%x\n" )
	.zero	3
.LC101:
	ASCII(.string	"PicMsg D[28] = 0x%x\n" )
	.zero	3
.LC103:
	ASCII(.string	"PicMsg D[29] = 0x%x\n" )
	.zero	3
.LC105:
	ASCII(.string	"PicMsg D[30] = 0x%x\n" )
	.zero	3
.LC107:
	ASCII(.string	"PicMsg D[32] = 0x%x\n" )
	.zero	3
.LC109:
	ASCII(.string	"PicMsg D[33] = 0x%x\n" )
	.zero	3
.LC111:
	ASCII(.string	"PicMsg D[34] = 0x%x\n" )
	.zero	3
.LC113:
	ASCII(.string	"PicMsg D[35] = 0x%x\n" )
	.zero	3
.LC115:
	ASCII(.string	"PicMsg D[36] = 0x%x\n" )
	.zero	3
.LC117:
	ASCII(.string	"PicMsg D[37] = 0x%x\n" )
	.zero	3
.LC119:
	ASCII(.string	"PicMsg D[38] = 0x%x\n" )
	.zero	3
.LC121:
	ASCII(.string	"PicMsg D[39] = 0x%x\n" )
	.zero	3
.LC123:
	ASCII(.string	"%s: pu8Vir = NULL\n" )
	.zero	5
.LC126:
	ASCII(.string	"PicMsg D[40] = 0x%x\n" )
	.zero	3
.LC128:
	ASCII(.string	"PicMsg D[41] = 0x%x\n" )
	.zero	3
.LC130:
	ASCII(.string	"PicMsg D[42] = 0x%x\n" )
	.zero	3
.LC132:
	ASCII(.string	"PicMsg D[43] = 0x%x\n" )
	.zero	3
.LC134:
	ASCII(.string	"PicMsg D[45] = 0x%x\n" )
	.zero	3
.LC136:
	ASCII(.string	"PicMsg D[46] = 0x%x\n" )
	.zero	3
.LC138:
	ASCII(.string	"PicMsg D[47] = 0x%x\n" )
	.zero	3
.LC140:
	ASCII(.string	"PicMsg D[48] = 0x%x\n" )
	.zero	3
.LC142:
	ASCII(.string	"PicMsg D[49] = 0x%x\n" )
	.zero	3
.LC144:
	ASCII(.string	"PicMsg D[50] = 0x%x\n" )
	.zero	3
.LC146:
	ASCII(.string	"PicMsg D[51] = 0x%x\n" )
	.zero	3
.LC148:
	ASCII(.string	"PicMsg D[52] = 0x%x\n" )
	.zero	3
.LC150:
	ASCII(.string	"PicMsg D[53] = 0x%x\n" )
	.zero	3
.LC152:
	ASCII(.string	"PicMsg D[54] = 0x%x\n" )
	.zero	3
.LC154:
	ASCII(.string	"PicMsg D[55] = 0x%x\n" )
	.zero	3
.LC156:
	ASCII(.string	"PicMsg D[56] = 0x%x\n" )
	.zero	3
.LC158:
	ASCII(.string	"PicMsg D[57] = 0x%x\n" )
	.zero	3
.LC160:
	ASCII(.string	"PicMsg D[58] = 0x%x\n" )
	.zero	3
.LC162:
	ASCII(.string	"PicMsg D[59] = 0x%x\n" )
	.zero	3
.LC164:
	ASCII(.string	"PicMsg D[60] = 0x%x\n" )
	.zero	3
.LC166:
	ASCII(.string	"PicMsg D[61] = 0x%x\n" )
	.zero	3
.LC168:
	ASCII(.string	"PicMsg D[62] = 0x%x\n" )
	.zero	3
.LC170:
	ASCII(.string	"PicMsg D[63] = 0x%x\n" )
	.zero	3
.LC175:
	ASCII(.string	"ERROR: pVp9DecParam->TotalTileNum(%d) out of [0-1024]\n" )
	.zero	1
.LC177:
	ASCII(.string	"TileMsg D[0] = 0x%x\n" )
	.zero	3
.LC179:
	ASCII(.string	"TileMsg D[1] = 0x%x\n" )
	.zero	3
.LC181:
	ASCII(.string	"TileMsg D[2] = 0x%x\n" )
	.zero	3
.LC183:
	ASCII(.string	"TileMsg D[3] = 0x%x\n" )
	.zero	3
.LC185:
	ASCII(.string	"TileMsg D[4] = 0x%x\n" )
	.zero	3
.LC187:
	ASCII(.string	"TileMsg D[5] = 0x%x\n" )
	.zero	3
.LC189:
	ASCII(.string	"TileMsg D[6] = 0x%x\n" )
	.zero	3
.LC191:
	ASCII(.string	"TileMsg D[7] = 0x%x\n" )
	.zero	3
.LC193:
	ASCII(.string	"TileMsg D[8] = 0x%x\n" )
	.zero	3
.LC195:
	ASCII(.string	"TileMsg D[9] = 0x%x\n" )
	.zero	3
.LC197:
	ASCII(.string	"TileMsg D[10] = 0x%x\n" )
	.zero	2
.LC199:
	ASCII(.string	"TileMsg D[11] = 0x%x\n" )
	.zero	2
.LC201:
	ASCII(.string	"TileMsg D[63] = 0x%x\n" )
	.zero	2
.LC206:
	ASCII(.string	"picture width out of range" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
