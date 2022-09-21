#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_vp6.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VP6HAL_V5R2C1_InitHal
	.type	VP6HAL_V5R2C1_InitHal, %function
VP6HAL_V5R2C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VP6HAL_V5R2C1_InitHal, .-VP6HAL_V5R2C1_InitHal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6HAL_V5R2C1_CfgReg
	.type	VP6HAL_V5R2C1_CfgReg, %function
VP6HAL_V5R2C1_CfgReg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x22, x1
	mov	x20, x3
	bl	_mcount
	cmp	w19, wzr
	ble	.L3
	ldr	x1, .LC1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L11:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3:
	ldr	x0, [x22]
	cbz	x0, .L8
.L6:
	ldrh	w4, [x21, 108]
	mov	w1, 0
	ldrh	w0, [x21, 106]
	mov	x3, x20
	mov	w2, w19
	mul	w0, w0, w4
	sub	w0, w0, #1
	bfi	w1, w0, 0, 20
	str	w1, [x29, 76]
	strb	wzr, [x29, 79]
	mov	w0, 8
	ldr	w23, [x29, 76]
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC27
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w2, [x21, 268]
	mov	w0, 0
	ldrh	w1, [x21, 106]
	mov	w3, 10
	bfi	w0, w2, 4, 1
	strb	w3, [x29, 76]
	orr	w0, w0, -64
	mov	w2, 8192
	cmp	w1, 120
	strb	w0, [x29, 77]
	strh	w2, [x29, 78]
	ble	.L9
	ldr	w0, [x21, 264]
	mov	w4, 0
	strb	wzr, [x21, 104]
	and	w0, w0, 1
.L7:
	ldrb	w1, [x29, 79]
	mov	x3, x20
	mov	w2, w19
	bfi	w1, w4, 5, 1
	bfi	w1, w0, 6, 1
	mov	w0, 12
	and	w1, w1, 127
	strb	w1, [x29, 79]
	ldr	w23, [x29, 76]
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC5
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w23, [x22, 72]
	mov	x3, x20
	mov	w2, w19
	and	w23, w23, -16
	mov	w0, 16
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC7
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w23, [x22, 56]
	mov	x3, x20
	mov	w2, w19
	and	w23, w23, -16
	mov	w0, 20
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC9
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w23, [x21, 112]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w23
	mov	w0, 24
	bl	MFDE_ConfigReg
	ldr	x1, .LC11
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w23, [x22, 1180]
	mov	x3, x20
	mov	w2, w19
	and	w23, w23, -16
	mov	w0, 128
	mov	w1, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC13
	mov	w2, w23
	mov	w0, 3
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	ldr	w0, [x22, 1184]
	mov	x3, x20
	strh	w0, [x29, 76]
	mov	w2, w19
	mov	w0, 132
	ldr	w22, [x29, 76]
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC15
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldrh	w1, [x21, 106]
	mov	x3, x20
	mov	w2, w19
	mov	w0, 4
	cmp	w1, 256
	cset	w1, ls
	bl	SCD_ConfigReg
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
	mov	x3, x20
	mov	w2, w19
	mov	w0, 84
	movk	w1, 0x30, lsl 16
	bl	MFDE_ConfigReg
	ldr	w22, [x21, 228]
	mov	x3, x20
	mov	w2, w19
	and	w22, w22, -16
	mov	w0, 96
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC17
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 244]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, 100
	bl	MFDE_ConfigReg
	ldr	x1, .LC19
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x21, 252]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, 104
	bl	MFDE_ConfigReg
	ldr	x1, .LC21
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x21, 260]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w21
	mov	w0, 108
	bl	MFDE_ConfigReg
	ldr	x1, .LC23
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w19
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC25
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
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L9:
	mov	w0, 1
	mov	w4, 1
	strb	w0, [x21, 104]
	mov	w0, 0
	str	wzr, [x21, 264]
	b	.L7
	.p2align 3
.L8:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L5
	str	x0, [x22]
	b	.L6
.L5:
	ldr	x1, .LC3
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L11
	.size	VP6HAL_V5R2C1_CfgReg, .-VP6HAL_V5R2C1_CfgReg
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6HAL_V5R2C1_CfgDnMsg
	.type	VP6HAL_V5R2C1_CfgDnMsg, %function
VP6HAL_V5R2C1_CfgDnMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x22, 72]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L28
	ldr	w2, [x19, 116]
	mov	w0, 0
	str	wzr, [x29, 76]
	bfi	w0, w2, 0, 1
	strb	w0, [x29, 76]
	ldr	x1, .LC34
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20]
	bl	dprint_vfmw
	ldrh	w3, [x19, 106]
	mov	w0, 0
	ldrh	w2, [x19, 108]
	mov	w1, 0
	sub	w3, w3, #1
	sub	w2, w2, #1
	bfi	w0, w3, 0, 9
	bfi	w1, w2, 0, 9
	strh	w0, [x29, 76]
	strh	w1, [x29, 78]
	ubfx	x0, x0, 8, 1
	ubfx	x1, x1, 8, 1
	strb	w0, [x29, 77]
	strb	w1, [x29, 79]
	mov	w0, 4
	ldr	x1, .LC36
	ldr	w2, [x29, 76]
	str	w2, [x20, 4]
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	ldp	w1, w5, [x19, 156]
	ldp	w3, w4, [x19, 124]
	ldr	w2, [x19, 164]
	mov	w0, 0
	bfi	w0, w1, 0, 5
	mov	w1, 0
	bfi	w0, w5, 5, 2
	bfi	w1, w4, 0, 1
	lsr	w2, w2, 1
	bfi	w0, w3, 7, 1
	bfi	w1, w2, 1, 1
	strb	w0, [x29, 76]
	strb	w1, [x29, 77]
	mov	w0, 4
	ldr	x1, .LC38
	ldr	w3, [x29, 76]
	and	w3, w3, 1023
	str	w3, [x29, 76]
	mov	w2, w3
	str	w3, [x20, 8]
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	ldp	w1, w2, [x19, 148]
	mov	w0, 0
	bfi	w0, w2, 0, 5
	bfi	w0, w1, 5, 3
	strb	w0, [x29, 76]
	ldp	w3, w4, [x19, 140]
	ldr	w2, [x29, 76]
	mov	w0, 4
	ldr	x1, .LC40
	bfi	w2, w4, 8, 10
	str	w2, [x29, 76]
	lsr	w2, w2, 16
	bfi	w2, w3, 2, 2
	strb	w2, [x29, 78]
	ldrh	w2, [x29, 78]
	and	w2, w2, 15
	strh	w2, [x29, 78]
	ldr	w2, [x29, 76]
	str	w2, [x20, 12]
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	ldrb	w1, [x19]
	mov	w0, 0
	ldp	w4, w3, [x19, 132]
	bfi	w0, w1, 0, 4
	strb	w0, [x29, 76]
	ldr	x1, .LC42
	mov	w0, 4
	ldrh	w2, [x29, 76]
	bfi	w2, w4, 4, 8
	strh	w2, [x29, 76]
	ldr	w2, [x29, 76]
	bfi	w2, w3, 12, 9
	str	w2, [x29, 76]
	ubfx	x2, x2, 16, 5
	strh	w2, [x29, 78]
	ldr	w2, [x29, 76]
	str	w2, [x20, 16]
	bl	dprint_vfmw
	ldr	w2, [x19, 216]
	mov	w0, 4
	ldr	x1, .LC44
	str	w2, [x20, 32]
	bl	dprint_vfmw
	str	wzr, [x29, 76]
	ldr	w1, [x19, 224]
	mov	w0, 0
	bfi	w0, w1, 0, 4
	strb	w0, [x29, 78]
	ldr	w0, [x19, 220]
	ldrh	w2, [x29, 78]
	strb	w0, [x29, 76]
	mov	w0, 4
	and	w2, w2, 15
	strh	w2, [x29, 78]
	ldr	x1, .LC46
	ldr	w2, [x29, 76]
	str	w2, [x20, 36]
	bl	dprint_vfmw
	ldr	w21, [x19, 176]
	ldr	w0, [x19, 224]
	ldp	w3, w2, [x19, 168]
	add	w0, w0, 8
	cmp	w0, w2
	add	w3, w0, w3
	bls	.L29
	add	w2, w2, 128
	sub	w21, w21, #16
	sub	w2, w2, w0
.L19:
	mov	w0, 0
	ldr	x1, .LC48
	bfi	w0, w3, 0, 25
	str	w0, [x29, 76]
	lsr	w3, w0, 24
	mov	w0, 4
	bfi	w3, w2, 1, 7
	strb	w3, [x29, 79]
	ldr	w2, [x29, 76]
	str	w2, [x20, 64]
	bl	dprint_vfmw
	mov	w0, 0
	ldr	x1, .LC50
	bfi	w0, w21, 0, 24
	str	w0, [x29, 76]
	strb	wzr, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 68]
	bl	dprint_vfmw
	ldr	w1, [x19, 112]
	ldr	w0, [x19, 176]
	add	w0, w1, w0
	bl	MEM_Phy2Vir
	cbz	x0, .L30
.L20:
	ldp	w2, w3, [x19, 180]
	mov	w0, 0
	ldr	x1, .LC54
	bfi	w0, w2, 0, 25
	str	w0, [x29, 76]
	lsr	w2, w0, 24
	mov	w0, 4
	bfi	w2, w3, 1, 7
	strb	w2, [x29, 79]
	ldr	w2, [x29, 76]
	str	w2, [x20, 72]
	bl	dprint_vfmw
	ldr	w2, [x19, 188]
	mov	w0, 0
	ldr	x1, .LC56
	bfi	w0, w2, 0, 24
	str	w0, [x29, 76]
	strb	wzr, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 76]
	bl	dprint_vfmw
	ldp	w1, w2, [x19, 192]
	mov	w0, 0
	bfi	w0, w1, 0, 25
	str	w0, [x29, 76]
	lsr	w0, w0, 24
	ldr	x1, .LC58
	bfi	w0, w2, 1, 7
	strb	w0, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 80]
	bl	dprint_vfmw
	ldr	w2, [x19, 200]
	mov	w0, 0
	ldr	x1, .LC60
	bfi	w0, w2, 0, 24
	str	w0, [x29, 76]
	strb	wzr, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 84]
	bl	dprint_vfmw
	ldp	w1, w2, [x19, 204]
	mov	w0, 0
	bfi	w0, w1, 0, 25
	str	w0, [x29, 76]
	lsr	w0, w0, 24
	ldr	x1, .LC62
	bfi	w0, w2, 1, 7
	strb	w0, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 88]
	bl	dprint_vfmw
	ldr	w2, [x19, 212]
	mov	w0, 0
	ldr	x1, .LC64
	bfi	w0, w2, 0, 24
	str	w0, [x29, 76]
	strb	wzr, [x29, 79]
	mov	w0, 4
	ldr	w2, [x29, 76]
	str	w2, [x20, 92]
	bl	dprint_vfmw
	ldr	w2, [x19, 228]
	mov	w0, 4
	ldr	x1, .LC66
	and	w2, w2, -16
	str	w2, [x20, 128]
	bl	dprint_vfmw
	ldr	w2, [x19, 232]
	mov	w0, 4
	ldr	x1, .LC68
	and	w2, w2, -16
	str	w2, [x20, 136]
	bl	dprint_vfmw
	ldr	w2, [x19, 236]
	mov	w0, 4
	ldr	x1, .LC70
	and	w2, w2, -16
	str	w2, [x20, 140]
	bl	dprint_vfmw
	ldr	w2, [x22, 1160]
	mov	w0, 4
	ldr	x1, .LC72
	and	w2, w2, -16
	str	w2, [x20, 144]
	bl	dprint_vfmw
	ldr	w2, [x22, 1164]
	mov	w0, 4
	ldr	x1, .LC74
	and	w2, w2, -16
	str	w2, [x20, 148]
	bl	dprint_vfmw
	ldr	w2, [x22, 1168]
	mov	w0, 4
	ldr	x1, .LC76
	and	w2, w2, -16
	str	w2, [x20, 152]
	bl	dprint_vfmw
	ldr	w21, [x22, 1200]
	ldr	x1, .LC78
	mov	w0, 4
	and	w21, w21, -16
	str	w21, [x20, 156]
	mov	w2, w21
	str	w21, [x29, 76]
	bl	dprint_vfmw
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x23, x0
	ldr	w0, [x22, 1200]
	bl	MEM_Phy2Vir
	cmp	x0, xzr
	ccmp	x23, xzr, 4, ne
	beq	.L31
	ldr	x20, .LC81
	mov	x2, 4096
	mov	w1, 0
	mov	x0, x23
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x1, [x19, 8]
	mov	x2, 64
	ldr	x3, [x20, 104]
	mov	x0, x23
	blr	x3
	ldr	x1, [x19, 16]
	mov	x2, 640
	ldr	x3, [x20, 104]
	add	x0, x23, 64
	blr	x3
	ldr	x1, [x19, 24]
	mov	x2, 64
	ldr	x3, [x20, 104]
	add	x0, x23, 704
	blr	x3
	ldr	w0, [x19, 128]
	cbnz	w0, .L22
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x22, x0
	adds	x0, x0, 768
	beq	.L32
	ldr	x1, [x19, 56]
	mov	x2, 96
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x1, [x19, 72]
	mov	x2, 32
	ldr	x3, [x20, 104]
	add	x0, x22, 864
	blr	x3
	ldr	x1, [x19, 64]
	mov	x2, 576
	ldr	x3, [x20, 104]
	add	x0, x22, 896
	blr	x3
.L24:
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x22, x0
	adds	x0, x0, 2560
	beq	.L33
	ldr	x1, [x19, 32]
	mov	x2, 64
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x1, [x19, 40]
	mov	x2, 64
	ldr	x3, [x20, 104]
	add	x0, x22, 2624
	blr	x3
	ldr	x1, [x19, 48]
	mov	x2, 960
	ldr	x3, [x20, 104]
	add	x0, x22, 2688
	blr	x3
	mov	w0, w21
	bl	MEM_Phy2Vir
	adds	x0, x0, 2816
	beq	.L34
	ldr	x1, [x19, 48]
	mov	x2, 960
	ldr	x3, [x20, 104]
	blr	x3
	mov	w0, 0
.L17:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L29:
	sub	w2, w2, w0
	b	.L19
	.p2align 3
.L22:
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x22, x0
	adds	x0, x0, 768
	beq	.L35
	ldr	x1, [x19, 88]
	mov	x2, 1536
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x1, [x19, 80]
	mov	x2, 128
	ldr	x3, [x20, 104]
	add	x0, x22, 2304
	blr	x3
	ldr	x1, [x19, 96]
	mov	x2, 128
	ldr	x3, [x20, 104]
	add	x0, x22, 2432
	blr	x3
	b	.L24
	.p2align 3
.L30:
	ldr	x1, .LC52
	mov	w2, 407
	mov	w0, 1
	bl	dprint_vfmw
	b	.L20
	.p2align 3
.L31:
	ldr	x2, .LC30
	mov	x3, x0
	ldr	x1, .LC80
	mov	x4, x23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
.L28:
	ldr	x3, .LC29
	mov	w0, 0
	ldr	x2, .LC30
	ldr	x1, .LC32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
.L34:
	ldr	x1, .LC83
	mov	w2, 618
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
.L33:
	ldr	x1, .LC83
	mov	w2, 597
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
.L35:
	ldr	x1, .LC83
	mov	w2, 573
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
.L32:
	ldr	x1, .LC83
	mov	w2, 546
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L17
	.size	VP6HAL_V5R2C1_CfgDnMsg, .-VP6HAL_V5R2C1_CfgDnMsg
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC30:
	.xword	.LANCHOR0
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
.LC81:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6HAL_V5R2C1_StartDec
	.type	VP6HAL_V5R2C1_StartDec, %function
VP6HAL_V5R2C1_StartDec:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	ldr	x23, .LC84
	sxtw	x0, w21
	cmp	w21, wzr
	lsl	x19, x0, 6
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	add	x24, x19, x23
	bgt	.L44
	ldrh	w0, [x22, 106]
	sub	w0, w0, #1
	uxth	w0, w0
	cmp	w0, 511
	bhi	.L45
	ldrh	w0, [x22, 108]
	sub	w0, w0, #1
	uxth	w0, w0
	cmp	w0, 511
	bhi	.L46
	ldr	x0, [x19, x23]
	cbz	x0, .L47
.L41:
	mov	x3, x20
	mov	w2, w21
	mov	x1, x24
	mov	x0, x22
	bl	VP6HAL_V5R2C1_CfgReg
	mov	w2, w21
	mov	x1, x24
	mov	x0, x22
	bl	VP6HAL_V5R2C1_CfgDnMsg
	mov	w0, 0
.L38:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L47:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L42
	str	x0, [x19, x23]
	b	.L41
	.p2align 3
.L44:
	ldr	x2, .LC85
	mov	w4, 0
	ldr	x1, .LC87
	mov	w3, w21
	add	x2, x2, 24
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L38
	.p2align 3
.L45:
	ldr	x2, .LC85
	ldr	x3, .LC89
.L43:
	ldr	x1, .LC90
	mov	w0, 0
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L38
	.p2align 3
.L46:
	ldr	x2, .LC85
	ldr	x3, .LC92
	b	.L43
.L42:
	ldr	x1, .LC93
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L38
	.size	VP6HAL_V5R2C1_StartDec, .-VP6HAL_V5R2C1_StartDec
	.align	3
.LC84:
	.xword	g_HwMem
	.align	3
.LC85:
	.xword	.LANCHOR0
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC90:
	.xword	.LC31
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC93:
	.xword	.LC2
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11999, %object
	.size	__func__.11999, 23
__func__.11999:
	.string	"VP6HAL_V5R2C1_CfgDnMsg"
	.zero	1
	.type	__func__.11966, %object
	.size	__func__.11966, 23
__func__.11966:
	.string	"VP6HAL_V5R2C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"VdhId is wrong! VP6HAL_V5R2C1_CfgReg_GetPhyAddr\n" )
	.zero	7
.LC2:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC4:
	ASCII(.string	"BASIC_CFG1 = 0x%x\n" )
	.zero	5
.LC6:
	ASCII(.string	"AVM_ADDR = 0x%x\n" )
	.zero	7
.LC8:
	ASCII(.string	"VAM_ADDR = 0x%x\n" )
	.zero	7
.LC10:
	ASCII(.string	"STREAM_BASE_ADDR = 0x%x\n" )
	.zero	7
.LC12:
	ASCII(.string	"PPFD_V5R2C1_BUF_ADDR = 0x%x\n" )
	.zero	3
.LC14:
	ASCII(.string	"PPFD_V200R003_BUF_LEN = 0x%x\n" )
	.zero	2
.LC16:
	ASCII(.string	"YSTADDR_1D = 0x%x\n" )
	.zero	5
.LC18:
	ASCII(.string	"YSTRIDE_1D = 0x%x\n" )
	.zero	5
.LC20:
	ASCII(.string	"UVOFFSET_1D = 0x%x\n" )
	.zero	4
.LC22:
	ASCII(.string	"HEAD_INF_OFFSET = 0x%x\n" )
.LC24:
	ASCII(.string	"FF_APT_EN = 0x%x\n" )
	.zero	6
.LC26:
	ASCII(.string	"BASIC_CFG0 = 0x%x\n" )
	.zero	5
.LC28:
	ASCII(.string	"can not map down msg virtual address!" )
	.zero	2
.LC31:
	ASCII(.string	"%s: %s\n" )
.LC33:
	ASCII(.string	"D0 = 0x%x\n" )
	.zero	5
.LC35:
	ASCII(.string	"D1 = 0x%x\n" )
	.zero	5
.LC37:
	ASCII(.string	"D2 = 0x%x\n" )
	.zero	5
.LC39:
	ASCII(.string	"D3 = 0x%x\n" )
	.zero	5
.LC41:
	ASCII(.string	"D4 = 0x%x\n" )
	.zero	5
.LC43:
	ASCII(.string	"D8 = 0x%x\n" )
	.zero	5
.LC45:
	ASCII(.string	"D9 = 0x%x\n" )
	.zero	5
.LC47:
	ASCII(.string	"D16 = 0x%x\n" )
	.zero	4
.LC49:
	ASCII(.string	"D17 = 0x%x\n" )
	.zero	4
.LC51:
	ASCII(.string	"LINE:%d NULL == tmpAddr.\n" )
	.zero	6
.LC53:
	ASCII(.string	"D18 = 0x%x\n" )
	.zero	4
.LC55:
	ASCII(.string	"D19 = 0x%x\n" )
	.zero	4
.LC57:
	ASCII(.string	"D20 = 0x%x\n" )
	.zero	4
.LC59:
	ASCII(.string	"D21 = 0x%x\n" )
	.zero	4
.LC61:
	ASCII(.string	"D22 = 0x%x\n" )
	.zero	4
.LC63:
	ASCII(.string	"D23 = 0x%x\n" )
	.zero	4
.LC65:
	ASCII(.string	"D32 = 0x%x\n" )
	.zero	4
.LC67:
	ASCII(.string	"D34 = 0x%x\n" )
	.zero	4
.LC69:
	ASCII(.string	"D35 = 0x%x\n" )
	.zero	4
.LC71:
	ASCII(.string	"D36 = 0x%x\n" )
	.zero	4
.LC73:
	ASCII(.string	"D37 = 0x%x\n" )
	.zero	4
.LC75:
	ASCII(.string	"D38 = 0x%x\n" )
	.zero	4
.LC77:
	ASCII(.string	"D39 = 0x%x\n" )
	.zero	4
.LC79:
	ASCII(.string	"%s: tmpAddr(%p) = NULL / TabBaseAddr(%p) = NULL\n" )
	.zero	7
.LC82:
	ASCII(.string	"line: %d  NULL == TabBaseAddr.\n" )
.LC86:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC88:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC91:
	ASCII(.string	"picture height out of range" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
