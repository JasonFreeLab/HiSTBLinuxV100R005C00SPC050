#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_mpeg4.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	MP4HAL_V4R3C1_Log2bin
	.type	MP4HAL_V4R3C1_Log2bin, %function
MP4HAL_V4R3C1_Log2bin:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	cbz	w19, .L2
	.p2align 2
.L3:
	add	w0, w0, 1
	lsr	w19, w19, 1
	sxth	w0, w0
	cbnz	w19, .L3
.L2:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP4HAL_V4R3C1_Log2bin, .-MP4HAL_V4R3C1_Log2bin
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4HAL_V4R3C1_InitHal
	.type	MP4HAL_V4R3C1_InitHal, %function
MP4HAL_V4R3C1_InitHal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MP4HAL_V4R3C1_InitHal, .-MP4HAL_V4R3C1_InitHal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4HAL_V4R3C1_CfgReg
	.type	MP4HAL_V4R3C1_CfgReg, %function
MP4HAL_V4R3C1_CfgReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	mov	x20, x3
	bl	_mcount
	cmp	w19, wzr
	bgt	.L31
	ldr	w4, [x23, 14584]
	add	x5, x23, 248
	mov	w1, 0
	mov	w22, -1
	cbz	w4, .L12
	.p2align 2
.L25:
	sxtw	x2, w1
	lsl	x0, x2, 3
	sub	x0, x0, x2
	add	x0, x5, x0, lsl 2
	ldr	w3, [x0, 16]
	cbz	w3, .L16
	ldr	w2, [x0, 8]
	and	w3, w3, -16
	cmp	w22, w3
	cbz	w2, .L16
	csel	w22, w22, w3, ls
.L16:
	ldr	w3, [x0, 20]
	cbz	w3, .L13
	ldr	w0, [x0, 12]
	and	w3, w3, -16
	cmp	w22, w3
	cbz	w0, .L13
	csel	w22, w22, w3, ls
.L13:
	add	w1, w1, 1
	cmp	w1, w4
	bne	.L25
	cmn	w22, #1
	beq	.L12
	str	w22, [x21]
	mov	w21, 1111490560
	mov	x3, x20
	mov	w0, 8
	ldrh	w4, [x23, 176]
	mov	w2, w19
	ldrh	w1, [x23, 178]
	mul	w1, w4, w1
	sub	w1, w1, #1
	and	w1, w1, 1048575
	orr	w21, w1, w21
	mov	w1, w21
	bl	MFDE_ConfigReg
	ldr	x1, .LC6
	mov	w2, w21
	mov	w0, 3
	mov	w21, 49154
	movk	w21, 0x1, lsl 16
	bl	dprint_vfmw
	ldr	w1, [x23, 14672]
	mov	x3, x20
	ldr	w0, [x23, 14676]
	mov	w2, w19
	ubfiz	w1, w1, 30, 1
	ubfiz	w0, w0, 12, 1
	orr	w0, w0, w1
	orr	w21, w0, w21
	mov	w0, 12
	mov	w1, w21
	bl	MFDE_ConfigReg
	ldr	x1, .LC8
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	sxtw	x0, w19
	ldr	x1, .LC9
	lsl	x21, x0, 6
	mov	x3, x20
	sub	x21, x21, x0
	mov	w2, w19
	lsl	x21, x21, 2
	sub	x0, x21, x0
	add	x0, x21, x0, lsl 2
	add	x21, x1, x0
	mov	w0, 16
	ldr	w24, [x21, 72]
	and	w24, w24, -16
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC11
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x21, 56]
	mov	x3, x20
	mov	w0, 20
	and	w24, w24, -16
	mov	w2, w19
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC13
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w1, w22
	mov	w2, w19
	mov	w0, 24
	bl	MFDE_ConfigReg
	ldr	x1, .LC15
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldrh	w1, [x23, 176]
	mov	w0, 4
	mov	x3, x20
	mov	w2, w19
	cmp	w1, 120
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
	ldr	w22, [x23, 224]
	mov	x3, x20
	mov	w0, 96
	and	w22, w22, -16
	mov	w2, w19
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC17
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x23, 14600]
	mov	x3, x20
	mov	w0, 100
	mov	w1, w22
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC19
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x23, 14608]
	mov	x3, x20
	mov	w0, 104
	mov	w1, w22
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC21
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x23, 14616]
	mov	x3, x20
	mov	w0, 108
	mov	w2, w19
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC23
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC25
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w21, [x21, 1220]
	mov	x3, x20
	mov	w0, 144
	mov	w2, w19
	mov	w1, w21
	bl	MFDE_ConfigReg
	ldr	x1, .LC27
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, 32
	mov	x3, x20
	mov	w2, w19
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L10:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L31:
	ldr	x2, .LC0
	mov	w4, 0
	ldr	x1, .LC2
	mov	w3, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L10
.L12:
	ldr	x1, .LC4
	mov	w2, -1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L10
	.size	MP4HAL_V4R3C1_CfgReg, .-MP4HAL_V4R3C1_CfgReg
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
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	g_HwMem
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
	.global	MP4HAL_V4R3C1_CfgDnMsg
	.type	MP4HAL_V4R3C1_CfgDnMsg, %function
MP4HAL_V4R3C1_CfgDnMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	sxtw	x22, w1
	mov	w19, 0
	bl	_mcount
	ldrh	w0, [x20, 176]
	ldrh	w1, [x20, 178]
	mul	w0, w0, w1
	cbz	w0, .L33
	.p2align 2
.L34:
	add	w19, w19, 1
	lsr	w0, w0, 1
	sxth	w19, w19
	cbnz	w0, .L34
.L33:
	lsl	x0, x22, 6
	ldr	x23, .LC28
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x0, x23, x0
	ldr	w0, [x0, 72]
	bl	MEM_Phy2Vir
	mov	x21, x0
	cbz	x0, .L67
	ldrb	w0, [x20, 2]
	cmp	w0, 1
	beq	.L68
	ldr	x1, .LC32
	mov	w2, 0
	mov	w0, 4
	str	wzr, [x21]
	bl	dprint_vfmw
	ldrb	w2, [x20, 3]
	mov	w0, 4
	ldrb	w3, [x20, 1]
	ldr	x1, .LC34
	ubfiz	w2, w2, 26, 5
	orr	w2, w2, w3, lsl 31
	str	w2, [x21, 4]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	cmp	w0, 2
	beq	.L39
	ldrb	w2, [x20, 12]
	ubfiz	w2, w2, 3, 1
.L40:
	ldrb	w3, [x20, 15]
	ubfiz	w1, w0, 5, 2
	ldr	w4, [x20, 14628]
	ubfiz	w19, w19, 22, 4
	and	w3, w3, 1
	ldr	w5, [x20, 14636]
	ubfiz	w4, w4, 26, 2
	orr	w4, w4, w3
	ldr	w3, [x20, 14632]
	ubfiz	w0, w5, 28, 2
	ldrb	w5, [x20, 11]
	orr	w0, w0, w3, lsl 30
	ldrb	w3, [x20, 14]
	orr	w0, w4, w0
	ubfiz	w4, w3, 1, 1
	ldrb	w3, [x20, 13]
	ubfiz	w3, w3, 2, 1
	orr	w3, w4, w3
	orr	w4, w0, w3
	ubfiz	w0, w5, 4, 1
	ldrb	w3, [x20, 10]
	orr	w0, w0, w1
	ldrb	w1, [x20, 9]
	orr	w0, w4, w0
	ubfiz	w3, w3, 7, 1
	ldrb	w4, [x20, 7]
	ubfiz	w1, w1, 8, 3
	orr	w3, w3, w1
	ldrb	w1, [x20, 8]
	orr	w0, w0, w3
	ubfiz	w3, w4, 11, 3
	ldrb	w4, [x20, 6]
	ubfiz	w1, w1, 14, 3
	orr	w1, w3, w1
	ubfiz	w4, w4, 17, 5
	orr	w3, w0, w1
	orr	w19, w4, w19
	ldr	x1, .LC36
	orr	w3, w3, w19
	mov	w0, 4
	orr	w2, w3, w2
	str	w2, [x21, 8]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	cmp	w0, 2
	beq	.L69
.L38:
	ldrh	w2, [x20, 178]
	mov	w0, 4
	ldrh	w4, [x20, 176]
	sub	w3, w2, #1
	ldr	x1, .LC40
	sub	w4, w4, #1
	and	w2, w4, 65535
	orr	w2, w2, w3, lsl 16
	str	w2, [x21, 16]
	bl	dprint_vfmw
	ldr	w2, [x20, 14620]
	mov	w0, 4
	ldr	w3, [x20, 14624]
	ldr	x1, .LC42
	orr	w2, w3, w2, lsl 16
	str	w2, [x21, 20]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	cmp	w0, 3
	beq	.L70
.L41:
	ldr	x1, .LC48
	mov	w2, 0
	mov	w0, 4
	str	wzr, [x21, 32]
	lsl	x19, x22, 6
	bl	dprint_vfmw
	str	wzr, [x21, 36]
	ldr	x1, .LC50
	mov	w2, 0
	mov	w0, 4
	sub	x19, x19, x22
	lsl	x19, x19, 2
	bl	dprint_vfmw
	str	wzr, [x21, 40]
	ldr	x1, .LC52
	mov	w2, 0
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x21, 44]
	ldr	x1, .LC54
	mov	w2, 0
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w2, [x20, 14588]
	mov	w0, 4
	ldr	x1, .LC56
	and	w2, w2, -16
	str	w2, [x21, 48]
	bl	dprint_vfmw
	ldr	w2, [x20, 232]
	mov	w0, 4
	ldr	x1, .LC58
	and	w2, w2, -16
	str	w2, [x21, 52]
	bl	dprint_vfmw
	ldr	w2, [x20, 236]
	mov	w0, 4
	ldr	x1, .LC60
	and	w2, w2, -16
	str	w2, [x21, 56]
	bl	dprint_vfmw
	ldr	w2, [x20, 240]
	mov	w0, 4
	ldr	x1, .LC62
	and	w2, w2, -16
	str	w2, [x21, 60]
	bl	dprint_vfmw
	ldr	w2, [x20, 244]
	mov	w0, 4
	ldr	x1, .LC64
	and	w2, w2, -16
	str	w2, [x21, 64]
	bl	dprint_vfmw
	sub	x2, x19, x22
	ldr	x1, .LC66
	mov	w0, 4
	add	x19, x19, x2, lsl 2
	add	x19, x23, x19
	ldr	w2, [x19, 1172]
	and	w2, w2, -16
	str	w2, [x21, 68]
	bl	dprint_vfmw
	ldr	w2, [x19, 1164]
	mov	w0, 4
	ldr	x1, .LC68
	and	w2, w2, -16
	str	w2, [x21, 72]
	bl	dprint_vfmw
	strb	wzr, [x20, 165]
	ldrb	w0, [x20]
	cmp	w0, 3
	beq	.L71
.L47:
	ldrb	w0, [x20, 161]
	strb	w0, [x20, 160]
	and	w0, w0, 1
	lsl	w3, w0, 3
.L49:
	ldrb	w4, [x20, 163]
	orr	w3, w3, w0, lsl 2
	ldrb	w2, [x20, 164]
	and	w0, w4, 1
	ldr	x1, .LC70
	ubfiz	w2, w2, 1, 1
	orr	w2, w2, w0
	mov	w0, 4
	orr	w2, w2, w3
	str	w2, [x21, 76]
	bl	dprint_vfmw
	ldr	w2, [x20, 14640]
	mov	w0, 4
	ldr	x1, .LC72
	str	w2, [x21, 80]
	bl	dprint_vfmw
	ldr	w2, [x20, 14644]
	mov	w0, 4
	ldr	x1, .LC74
	str	w2, [x21, 84]
	bl	dprint_vfmw
	ldr	w2, [x20, 14648]
	mov	w0, 4
	ldr	x1, .LC76
	str	w2, [x21, 88]
	bl	dprint_vfmw
	ldr	w2, [x20, 14652]
	mov	w0, 4
	ldr	x1, .LC78
	str	w2, [x21, 92]
	bl	dprint_vfmw
	ldr	w2, [x20, 14656]
	mov	w0, 4
	ldr	x1, .LC80
	str	w2, [x21, 96]
	bl	dprint_vfmw
	ldr	w2, [x20, 14660]
	mov	w0, 4
	ldr	x1, .LC82
	str	w2, [x21, 100]
	bl	dprint_vfmw
	ldr	w2, [x20, 14664]
	mov	w0, 4
	ldr	x1, .LC84
	str	w2, [x21, 104]
	bl	dprint_vfmw
	ldr	w2, [x20, 14668]
	mov	w0, 4
	ldr	x1, .LC86
	str	w2, [x21, 108]
	bl	dprint_vfmw
	ldrb	w0, [x20, 2]
	cmp	w0, 2
	beq	.L72
.L50:
	lsl	x2, x22, 6
	ldr	x1, .LC90
	sub	x2, x2, x22
	mov	w0, 4
	lsl	x2, x2, 2
	sub	x22, x2, x22
	add	x2, x2, x22, lsl 2
	add	x2, x23, x2
	ldr	w3, [x2, 1160]
	and	w3, w3, -16
	str	w3, [x21, 240]
	ldr	w2, [x2, 72]
	add	w2, w2, 256
	str	w2, [x21, 252]
	bl	dprint_vfmw
	mov	w0, 0
.L36:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L68:
	mov	w24, 4
	ldr	x1, .LC32
	mov	w2, w24
	mov	w0, w24
	str	w24, [x21]
	ubfiz	w19, w19, 22, 4
	bl	dprint_vfmw
	ldrb	w2, [x20, 4]
	ldrb	w1, [x20, 3]
	ldrb	w0, [x20, 5]
	ubfiz	w2, w2, 5, 7
	ubfiz	w1, w1, 26, 5
	sub	w0, w0, #1
	orr	w1, w2, w1
	and	w0, w0, 31
	orr	w0, w1, w0
	ldr	x1, .LC34
	mov	w2, w0
	str	w0, [x21, 4]
	mov	w0, w24
	bl	dprint_vfmw
	ldrb	w2, [x20]
	mov	w0, w24
	ldr	x1, .LC36
	ubfiz	w2, w2, 5, 2
	orr	w2, w2, w19
	str	w2, [x21, 8]
	bl	dprint_vfmw
	b	.L38
	.p2align 3
.L72:
	ldrb	w0, [x20, 1]
	cbz	w0, .L50
	ldr	x19, .LC88
	add	x4, x20, 32
	mov	w27, 0
	mov	w28, 0
	.p2align 2
.L51:
	mov	w26, w28
	mov	w25, w27
	mov	w24, 0
.L52:
	sxtw	x0, w26
	str	x4, [x29, 104]
	add	x1, x4, x0
	add	w26, w26, 8
	ldrb	w5, [x4, x0]
	ldrb	w2, [x1, 16]
	ldrb	w3, [x1, 32]
	ldrb	w0, [x1, 48]
	sxtw	x1, w25
	lsl	w3, w3, 16
	add	x1, x1, 112
	orr	w3, w3, w2, lsl 8
	add	w2, w24, w24, lsr 31
	orr	w0, w5, w0, lsl 24
	add	w24, w24, 1
	add	w2, w27, w2, asr 1
	orr	w3, w3, w0
	add	w2, w2, 24
	str	w3, [x21, x1]
	mov	w0, 4
	mov	x1, x19
	add	w25, w25, 4
	bl	dprint_vfmw
	cmp	w24, 2
	ldr	x4, [x29, 104]
	bne	.L52
	add	w28, w28, 1
	add	w27, w27, 8
	cmp	w28, 8
	bne	.L51
	add	x25, x20, 96
	mov	w24, 64
	mov	w28, 0
	.p2align 2
.L54:
	lsl	w0, w28, 3
	mov	w27, w28
	mov	w26, w24
	mov	w20, 0
	str	w0, [x29, 104]
.L55:
	sxtw	x0, w27
	add	w27, w27, 8
	add	x1, x25, x0
	ldrb	w5, [x25, x0]
	ldrb	w2, [x1, 16]
	ldrb	w3, [x1, 32]
	ldrb	w0, [x1, 48]
	sxtw	x1, w26
	lsl	w3, w3, 16
	add	x1, x1, 112
	orr	w3, w3, w2, lsl 8
	add	w2, w20, w20, lsr 31
	orr	w0, w5, w0, lsl 24
	add	w20, w20, 1
	orr	w3, w3, w0
	ldr	w0, [x29, 104]
	str	w3, [x21, x1]
	mov	x1, x19
	add	w2, w0, w2, asr 1
	mov	w0, 4
	add	w2, w2, 24
	add	w26, w26, 4
	bl	dprint_vfmw
	cmp	w20, 2
	bne	.L55
	add	w28, w28, 1
	add	w24, w24, 8
	cmp	w28, 8
	bne	.L54
	b	.L50
	.p2align 3
.L71:
	ldr	w0, [x20, 14632]
	cmp	w0, 1
	beq	.L73
	bhi	.L47
	ldrb	w3, [x20, 160]
	ldrb	w1, [x20, 161]
	ubfiz	w3, w3, 3, 1
	and	w0, w1, 1
	b	.L49
	.p2align 3
.L70:
	ldr	w0, [x20, 14632]
	cmp	w0, 1
	bne	.L41
	ldrb	w19, [x20, 162]
	ldrb	w2, [x20, 11]
	cmp	w19, 1
	beq	.L74
	ldr	w1, [x20, 14656]
	lsl	w1, w1, w2
	ldr	w2, [x20, 14636]
	cmp	w1, wzr
	lsl	w0, w0, w2
	add	w0, w1, w0, asr 1
	ble	.L75
.L66:
	ldr	x1, .LC44
	asr	w2, w0, w2
	mov	w0, 4
	str	w2, [x21, 24]
	bl	dprint_vfmw
	ldrb	w3, [x20, 11]
	ldr	w0, [x20, 14660]
	ldr	w2, [x20, 14636]
	lsl	w3, w0, w3
	cmp	w3, wzr
	ble	.L45
	mov	w0, 1
	lsl	w0, w0, w2
	add	w0, w3, w0, asr 1
	asr	w2, w0, w2
.L46:
	ldr	x1, .LC46
	mov	w0, 4
	str	w2, [x21, 28]
	bl	dprint_vfmw
	b	.L41
	.p2align 3
.L39:
	strb	wzr, [x20, 12]
	mov	w2, 0
	b	.L40
.L69:
	ldp	w3, w2, [x20, 216]
	ldr	x1, .LC38
	mov	w0, 4
	ubfiz	w3, w3, 1, 15
	orr	w2, w3, w2, lsl 17
	str	w2, [x21, 12]
	bl	dprint_vfmw
	b	.L38
.L73:
	ldrb	w1, [x20, 161]
	mov	w3, 8
	strb	w0, [x20, 160]
	and	w0, w1, 1
	b	.L49
.L45:
	mov	w1, 1
	lsl	w1, w1, w2
	add	w0, w3, w1, asr 1
	sub	w0, w0, #1
	asr	w2, w0, w2
	b	.L46
.L75:
	sub	w0, w0, #1
	b	.L66
.L74:
	ldr	w0, [x20, 14636]
	ldr	w3, [x20, 14656]
	sub	w2, w0, w2
	ldr	x1, .LC44
	lsl	w2, w19, w2
	mov	w0, 4
	sdiv	w2, w3, w2
	str	w2, [x21, 24]
	bl	dprint_vfmw
	ldrb	w4, [x20, 11]
	mov	w0, 4
	ldr	w3, [x20, 14636]
	ldr	w2, [x20, 14660]
	sub	w3, w3, w4
	ldr	x1, .LC46
	lsl	w19, w19, w3
	sdiv	w2, w2, w19
	str	w2, [x21, 28]
	bl	dprint_vfmw
	b	.L41
.L67:
	ldr	x1, .LC30
	mov	w2, 333
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L36
	.size	MP4HAL_V4R3C1_CfgDnMsg, .-MP4HAL_V4R3C1_CfgDnMsg
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4HAL_V4R3C1_WriteSlicMsg
	.type	MP4HAL_V4R3C1_WriteSlicMsg, %function
MP4HAL_V4R3C1_WriteSlicMsg:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w19, w1
	mov	w23, w2
	bl	_mcount
	add	x26, x22, 248
	sxtw	x0, w19
	ldr	x2, .LC91
	lsl	x1, x0, 6
	ldr	w21, [x22, 14584]
	sub	x1, x1, x0
	str	wzr, [x29, 124]
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	add	x0, x2, x0
	ldr	w25, [x0, 72]
	add	w19, w25, 256
	mov	w0, w19
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L117
	ldr	w0, [x26, 24]
	mov	w24, 0
	cbnz	w0, .L118
.L79:
	cmp	w21, wzr
	ble	.L99
	add	w0, w19, w24, lsl 5
	mov	w25, 0
	str	w0, [x29, 108]
	.p2align 2
.L98:
	sxtw	x19, w25
	cmp	w25, wzr
	lsl	x4, x19, 3
	sub	x4, x4, x19
	add	x27, x26, x4, lsl 2
	ble	.L83
	ldr	w0, [x27, -4]
	ldr	w1, [x27, 24]
	cmp	w1, w0
	bls	.L84
.L83:
	ldr	w28, [x27, 16]
	mov	w2, 0
	ldr	w7, [x27, 8]
	mov	w1, 0
	ldrb	w0, [x27, 6]
	ubfiz	w8, w28, 3, 4
	bfi	w2, w7, 0, 24
	str	w2, [x29, 124]
	add	w0, w8, w0
	add	x19, x19, x24, sxtw 2
	bfi	w1, w0, 0, 7
	strb	w1, [x29, 127]
	lsl	x19, x19, 5
	ldr	x1, .LC96
	ldr	w7, [x29, 124]
	mov	w0, 4
	mov	w2, w7
	str	w7, [x20, x19]
	bl	dprint_vfmw
	add	x7, x19, 4
	and	w6, w28, -16
	sub	w6, w6, w23
	ldr	x1, .LC98
	mov	w2, w6
	mov	w0, 4
	str	w6, [x20, x7]
	bl	dprint_vfmw
	ldr	w28, [x27, 20]
	ldr	w1, [x27, 12]
	mov	w2, 0
	ldrb	w0, [x27, 7]
	ubfiz	w7, w28, 3, 4
	bfi	w2, w1, 0, 24
	mov	w1, 0
	str	w2, [x29, 124]
	add	w0, w7, w0
	bfi	w1, w0, 0, 7
	add	x7, x19, 8
	strb	w1, [x29, 127]
	mov	w0, 4
	ldr	x1, .LC100
	ldr	w2, [x29, 124]
	str	w2, [x20, x7]
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldr	w2, [x27, 20]
	mov	w7, 0
	cbz	w2, .L85
	and	w2, w28, -16
	sub	w2, w2, w23
	mov	w7, w2
.L85:
	add	x6, x19, 12
	ldr	x1, .LC102
	mov	w0, 4
	add	w25, w25, 1
	str	w7, [x20, x6]
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldrb	w2, [x27, 5]
	mov	w0, 0
	ldrb	w1, [x27, 4]
	add	x6, x19, 16
	bfi	w0, w2, 0, 5
	ldrb	w9, [x27, 3]
	bfi	w0, w1, 5, 2
	strb	w0, [x29, 124]
	ldrb	w8, [x27, 1]
	mov	w0, 4
	ldrh	w2, [x29, 124]
	ldrb	w7, [x27, 2]
	bfi	w2, w9, 7, 3
	strh	w2, [x29, 124]
	lsr	x2, x2, 8
	ldr	x1, .LC104
	bfi	w2, w8, 2, 3
	bfi	w2, w7, 5, 3
	strb	w2, [x29, 125]
	ldr	w2, [x29, 124]
	str	w2, [x20, x6]
	bl	dprint_vfmw
	ldr	w1, [x27, 24]
	add	x6, x19, 20
	mov	w0, 0
	bfi	w0, w1, 0, 20
	ldr	x1, .LC106
	str	w0, [x29, 124]
	mov	w2, w0
	str	w0, [x20, x6]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w6, [x22, 14584]
	cmp	w6, w25
	ble	.L86
	sxtw	x7, w25
	ldr	w4, [x27, 24]
	lsl	x0, x7, 3
	sub	x0, x0, x7
	add	x0, x26, x0, lsl 2
	ldr	w8, [x0, 24]
	cmp	w4, w8
	bcc	.L106
	mov	w1, w25
	b	.L89
	.p2align 3
.L91:
	sub	x0, x0, x2
	add	x0, x26, x0, lsl 2
	ldr	w0, [x0, 24]
	cmp	w0, w4
	bhi	.L87
.L89:
	add	w1, w1, 1
	cmp	w6, w1
	sxtw	x2, w1
	lsl	x0, x2, 3
	bgt	.L91
	cmp	w6, w1
	mov	w2, 0
	beq	.L119
.L101:
	cmp	w4, w8
	bcs	.L94
	b	.L92
	.p2align 3
.L96:
	sub	x0, x0, x1
	add	x0, x26, x0, lsl 2
	ldr	w0, [x0, 24]
	cmp	w0, w4
	bhi	.L92
.L94:
	add	w25, w25, 1
	cmp	w25, w6
	sxtw	x1, w25
	lsl	x0, x1, 3
	blt	.L96
	and	w0, w2, 1048575
	mov	w27, 0
.L95:
	cmp	w6, w25
	beq	.L107
.L100:
	mov	w28, w27
.L97:
	add	x8, x19, 24
	mov	w4, 0
	bfi	w4, w0, 0, 20
	ldr	x1, .LC108
	str	w4, [x29, 124]
	mov	w2, w4
	mov	w0, 4
	str	w4, [x20, x8]
	add	x19, x19, 28
	sub	w25, w25, #1
	bl	dprint_vfmw
	str	w28, [x29, 124]
	ldr	x1, .LC110
	mov	w2, w28
	mov	w0, 4
	str	w27, [x20, x19]
	bl	dprint_vfmw
.L84:
	add	w25, w25, 1
	cmp	w21, w25
	bgt	.L98
.L99:
	mov	w0, 0
.L115:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L107:
	mov	w28, 0
	mov	w27, 0
	b	.L97
	.p2align 3
.L92:
	ldr	w0, [x29, 108]
	add	w27, w0, w25, lsl 5
	and	w0, w2, 1048575
	b	.L95
.L106:
	mov	w0, w8
	mov	w1, w25
	.p2align 2
.L87:
	cmp	w6, w1
	sub	w2, w0, #1
	bne	.L101
.L119:
	lsl	x0, x7, 3
	ldrh	w2, [x22, 176]
	sub	x0, x0, x7
	add	x0, x26, x0, lsl 2
	ldr	w8, [x0, 24]
	ldrh	w0, [x22, 178]
	mul	w0, w0, w2
	sub	w2, w0, #1
	b	.L101
.L118:
	ldr	w24, [x26, 16]
	ldr	w0, [x29, 124]
	ldrb	w1, [x26, 6]
	ubfiz	w2, w24, 3, 4
	and	w0, w0, -16777216
	str	w0, [x29, 124]
	add	w1, w2, w1
	lsr	w0, w0, 24
	bfi	w0, w1, 0, 7
	strb	w0, [x29, 127]
	ldr	x1, .LC96
	mov	w0, 4
	ldr	w2, [x29, 124]
	str	w2, [x20]
	bl	dprint_vfmw
	and	w0, w24, -16
	ldr	x1, .LC98
	sub	w0, w0, w23
	str	w0, [x20, 4]
	mov	w2, w0
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w24, [x26, 20]
	ldrb	w0, [x26, 7]
	ubfiz	w1, w24, 3, 4
	str	wzr, [x29, 124]
	add	w0, w1, w0
	mov	w1, 0
	bfi	w1, w0, 0, 7
	strb	w1, [x29, 127]
	ldr	x1, .LC100
	mov	w0, 4
	ldr	w2, [x29, 124]
	str	w2, [x20, 8]
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldr	w2, [x26, 20]
	mov	w0, 0
	cbz	w2, .L80
	and	w2, w24, -16
	sub	w2, w2, w23
	mov	w0, w2
.L80:
	ldr	x1, .LC102
	add	w25, w25, 288
	str	w0, [x20, 12]
	mov	w0, 4
	mov	w24, 1
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldrb	w2, [x26, 5]
	mov	w0, 0
	ldrb	w1, [x26, 4]
	bfi	w0, w2, 0, 5
	ldrb	w2, [x26, 3]
	bfi	w0, w1, 5, 2
	strb	w0, [x29, 124]
	ldrb	w1, [x26, 1]
	ldrh	w0, [x29, 124]
	bfi	w0, w2, 7, 3
	strh	w0, [x29, 124]
	lsr	x0, x0, 8
	ldrb	w2, [x26, 2]
	bfi	w0, w1, 2, 3
	ldr	x1, .LC104
	bfi	w0, w2, 5, 3
	strb	w0, [x29, 125]
	mov	w0, 4
	ldr	w2, [x29, 124]
	str	w2, [x20, 16]
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldr	x1, .LC106
	mov	w2, 0
	str	wzr, [x20, 20]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w2, [x26, 24]
	mov	w0, 0
	ldr	x1, .LC108
	sub	w2, w2, #1
	bfi	w0, w2, 0, 20
	str	w0, [x29, 124]
	mov	w2, w0
	str	w0, [x20, 24]
	mov	w0, 4
	bl	dprint_vfmw
	str	w25, [x20, 28]
	ldr	x1, .LC110
	mov	w2, w25
	mov	w0, 4
	str	w25, [x29, 124]
	bl	dprint_vfmw
	b	.L79
.L86:
	mov	w0, 0
	mov	w27, 0
	bne	.L100
	ldrh	w0, [x22, 178]
	ldrh	w1, [x22, 176]
	mul	w0, w0, w1
	sub	w0, w0, #1
	and	w0, w0, 1048575
	b	.L95
.L117:
	ldr	x2, .LC92
	mov	w0, 0
	ldr	x1, .LC94
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L115
	.size	MP4HAL_V4R3C1_WriteSlicMsg, .-MP4HAL_V4R3C1_WriteSlicMsg
	.align	3
.LC91:
	.xword	g_HwMem
	.align	3
.LC92:
	.xword	.LANCHOR0
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4HAL_V4R3C1_StartDec
	.type	MP4HAL_V4R3C1_StartDec, %function
MP4HAL_V4R3C1_StartDec:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	str	wzr, [x29, 60]
	ldrh	w0, [x19, 176]
	cmp	w0, 512
	bhi	.L123
	ldrh	w0, [x19, 178]
	cmp	w0, 512
	bhi	.L123
	mov	x3, x21
	add	x2, x29, 60
	mov	w1, w20
	mov	x0, x19
	bl	MP4HAL_V4R3C1_CfgReg
	cbnz	w0, .L128
	mov	w1, w20
	mov	x0, x19
	bl	MP4HAL_V4R3C1_CfgDnMsg
	cbnz	w0, .L129
	ldr	w2, [x29, 60]
	mov	w1, w20
	mov	x0, x19
	bl	MP4HAL_V4R3C1_WriteSlicMsg
	mov	w1, 0
	cbnz	w0, .L130
.L122:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	mov	w0, w1
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L123:
	ldr	x2, .LC113
	mov	w0, 0
	ldr	x1, .LC115
	ldr	x3, .LC112
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w1, -1
	b	.L122
	.p2align 3
.L128:
	ldr	x1, .LC117
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L122
	.p2align 3
.L129:
	ldr	x1, .LC119
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L122
	.p2align 3
.L130:
	ldr	x1, .LC121
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L122
	.size	MP4HAL_V4R3C1_StartDec, .-MP4HAL_V4R3C1_StartDec
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC113:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC121:
	.xword	.LC120
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11819, %object
	.size	__func__.11819, 21
__func__.11819:
	.string	"MP4HAL_V4R3C1_CfgReg"
	.zero	3
	.type	__func__.11904, %object
	.size	__func__.11904, 27
__func__.11904:
	.string	"MP4HAL_V4R3C1_WriteSlicMsg"
	.zero	5
	.type	__func__.11796, %object
	.size	__func__.11796, 23
__func__.11796:
	.string	"MP4HAL_V4R3C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC3:
	ASCII(.string	"stream_base_addr = %#x\n" )
.LC5:
	ASCII(.string	"BASIC_V4R3C1_CFG0=0x%x\n" )
.LC7:
	ASCII(.string	"BASIC_V4R3C1_CFG1=0x%x\n" )
.LC10:
	ASCII(.string	"AVM_V4R3C1_ADDR=0x%x\n" )
	.zero	2
.LC12:
	ASCII(.string	"VAM_V4R3C1_ADDR=0x%x\n" )
	.zero	2
.LC14:
	ASCII(.string	"STREAM_V4R3C1_BASE_ADDR=0x%x\n" )
	.zero	2
.LC16:
	ASCII(.string	"YSTADDR_V200R003_1D=0x%x\n" )
	.zero	6
.LC18:
	ASCII(.string	"YSTRIDE_V200R003_1D=0x%x\n" )
	.zero	6
.LC20:
	ASCII(.string	"UVOFFSET_V200R003_1D=0x%x\n" )
	.zero	5
.LC22:
	ASCII(.string	"PRCNUM_1D_CNT=0x%x\n" )
	.zero	4
.LC24:
	ASCII(.string	"PRCMEM2_1D_CNT=0x%x\n" )
	.zero	3
.LC26:
	ASCII(.string	"DNR_MBINFO_STADDR=0x%x\n" )
.LC29:
	ASCII(.string	"line: %d ,pMsgBlock = NULL is not expected value!\n" )
	.zero	5
.LC31:
	ASCII(.string	"D0=0x%x\n" )
	.zero	7
.LC33:
	ASCII(.string	"D1=0x%x\n" )
	.zero	7
.LC35:
	ASCII(.string	"D2=0x%x\n" )
	.zero	7
.LC37:
	ASCII(.string	"D3=0x%x\n" )
	.zero	7
.LC39:
	ASCII(.string	"D4=0x%x\n" )
	.zero	7
.LC41:
	ASCII(.string	"D5=0x%x\n" )
	.zero	7
.LC43:
	ASCII(.string	"D6=0x%x\n" )
	.zero	7
.LC45:
	ASCII(.string	"D7=0x%x\n" )
	.zero	7
.LC47:
	ASCII(.string	"D8=0x%x\n" )
	.zero	7
.LC49:
	ASCII(.string	"D9=0x%x\n" )
	.zero	7
.LC51:
	ASCII(.string	"D10=0x%x\n" )
	.zero	6
.LC53:
	ASCII(.string	"D11=0x%x\n" )
	.zero	6
.LC55:
	ASCII(.string	"D12= 0x%x\n" )
	.zero	5
.LC57:
	ASCII(.string	"D13= 0x%x\n" )
	.zero	5
.LC59:
	ASCII(.string	"D14= 0x%x\n" )
	.zero	5
.LC61:
	ASCII(.string	"D15= 0x%x\n" )
	.zero	5
.LC63:
	ASCII(.string	"D16= 0x%x\n" )
	.zero	5
.LC65:
	ASCII(.string	"D17= 0x%x\n" )
	.zero	5
.LC67:
	ASCII(.string	"D18= 0x%x\n" )
	.zero	5
.LC69:
	ASCII(.string	"D19= 0x%x\n" )
	.zero	5
.LC71:
	ASCII(.string	"D20= 0x%x\n" )
	.zero	5
.LC73:
	ASCII(.string	"D21= 0x%x\n" )
	.zero	5
.LC75:
	ASCII(.string	"D22= 0x%x\n" )
	.zero	5
.LC77:
	ASCII(.string	"D23= 0x%x\n" )
	.zero	5
.LC79:
	ASCII(.string	"D24= 0x%x\n" )
	.zero	5
.LC81:
	ASCII(.string	"D25= 0x%x\n" )
	.zero	5
.LC83:
	ASCII(.string	"D26= 0x%x\n" )
	.zero	5
.LC85:
	ASCII(.string	"D27= 0x%x\n" )
	.zero	5
.LC87:
	ASCII(.string	"D%d= 0x%x\n" )
	.zero	5
.LC89:
	ASCII(.string	"D63= 0x%x\n" )
	.zero	5
.LC93:
	ASCII(.string	"%s: SlcDnMsgVirAddr = NULL\n" )
	.zero	4
.LC95:
	ASCII(.string	"D0 = %#x \n" )
	.zero	5
.LC97:
	ASCII(.string	"D1 = %#x \n" )
	.zero	5
.LC99:
	ASCII(.string	"D2 = %#x \n" )
	.zero	5
.LC101:
	ASCII(.string	"D3 = %#x \n" )
	.zero	5
.LC103:
	ASCII(.string	"D4 = %#x \n" )
	.zero	5
.LC105:
	ASCII(.string	"D5 = %#x \n" )
	.zero	5
.LC107:
	ASCII(.string	"D6 = %#x \n" )
	.zero	5
.LC109:
	ASCII(.string	"D7 = %#x \n" )
	.zero	5
.LC111:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC114:
	ASCII(.string	"%s: %s\n" )
.LC116:
	ASCII(.string	"MP4HAL_V200R003_CfgReg failed!\n" )
.LC118:
	ASCII(.string	"MP4HAL_V200R003_CfgDnMsg failed!\n" )
	.zero	6
.LC120:
	ASCII(.string	"MP4HAL_V200R003_WriteSlicMsg failed!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
