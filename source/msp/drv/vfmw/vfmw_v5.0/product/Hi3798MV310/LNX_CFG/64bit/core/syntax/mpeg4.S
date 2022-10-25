#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"mpeg4.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	log2bin
	.type	log2bin, %function
log2bin:
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
	.size	log2bin, .-log2bin
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	bs_get_spritetrajectory
	.type	bs_get_spritetrajectory, %function
bs_get_spritetrajectory:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x22, .LC3
	add	x19, x22, 4
	.p2align 2
.L10:
	ldrb	w1, [x19]
	mov	x0, x21
	add	x19, x19, 8
	bl	BsShow
	ldr	w1, [x19, -12]
	cmp	w0, w1
	beq	.L12
	add	w20, w20, 1
	cmp	w20, 12
	bne	.L10
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L12:
	add	x22, x22, x20, uxtw 3
	mov	x0, x21
	ldrb	w1, [x22, 4]
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	bs_get_spritetrajectory, .-bs_get_spritetrajectory
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_GetGMCparam
	.type	MP4_GetGMCparam, %function
MP4_GetGMCparam:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	w8, [x20, 716]
	mov	w11, 2
	ldrb	w0, [x20, 73]
	mov	w9, 3
	ldr	w1, [x20, 712]
	lsl	w2, w8, 4
	str	w2, [x19, 8]
	lsl	w11, w11, w0
	sub	w9, w9, w0
	mov	w5, 16
	ldr	w0, [x20, 712]
	cmp	w8, 1
	sdiv	w12, w5, w11
	lsl	w0, w0, 4
	str	w0, [x19, 12]
	ldrb	w0, [x20, 73]
	str	w0, [x19, 4]
	add	x0, x20, 512
	ldrb	w14, [x20, 72]
	str	w14, [x19]
	ldp	w13, w10, [x0, 176]
	ldp	w6, w7, [x0, 184]
	ldr	w17, [x20, 704]
	ldr	w16, [x20, 708]
	ble	.L38
	mov	w2, 0
	mov	w0, 1
	.p2align 2
.L15:
	add	w2, w2, 1
	lsl	w3, w0, w2
	cmp	w8, w3
	bgt	.L15
	lsl	w30, w3, 4
.L14:
	cmp	w1, 1
	ble	.L39
	mov	w0, 0
	mov	w15, 1
	.p2align 2
.L17:
	add	w0, w0, 1
	lsl	w4, w15, w0
	cmp	w1, w4
	bgt	.L17
	lsl	w15, w4, 4
.L16:
	ldrb	w5, [x20, 12]
	add	w7, w10, w7
	add	w17, w13, w17
	cmp	w5, 1
	beq	.L44
	add	w5, w13, w8, lsl 1
	add	w6, w5, w6
	add	w5, w10, w1, lsl 1
	add	w16, w5, w16
	asr	w5, w11, 1
	mul	w13, w13, w5
	mul	w10, w10, w5
	mul	w6, w6, w5
	mul	w7, w7, w5
	mul	w17, w17, w5
	mul	w16, w16, w5
.L19:
	neg	w5, w8, lsl 4
	sub	w23, w8, w3
	mul	w21, w12, w13
	madd	w6, w12, w6, w5
	asr	w22, w8, 1
	mul	w5, w23, w21
	madd	w5, w6, w3, w5
	cmp	w5, wzr
	ble	.L20
	add	w5, w5, w22
.L21:
	sdiv	w5, w5, w8
	mul	w20, w12, w10
	mul	w7, w12, w7
	mul	w18, w12, w17
	add	w5, w5, w30
	sub	w30, w1, w4
	mul	w6, w23, w20
	madd	w6, w7, w3, w6
	mul	w17, w21, w30
	madd	w17, w18, w4, w17
	cmp	w6, wzr
	add	w7, w6, w22
	sub	w6, w6, w22
	asr	w18, w1, 1
	csel	w6, w6, w7, le
	cmp	w17, wzr
	sdiv	w6, w6, w8
	ble	.L24
	add	w17, w17, w18
.L25:
	neg	w7, w1, lsl 4
	mul	w30, w20, w30
	madd	w8, w12, w16, w7
	madd	w7, w8, w4, w30
	cmp	w7, wzr
	add	w8, w7, w18
	sub	w7, w7, w18
	csel	w7, w7, w8, le
	cmp	w14, 3
	bls	.L45
	ldp	w8, w7, [x19, 16]
	ldp	w5, w9, [x19, 24]
	ldp	w13, w10, [x19, 32]
	ldp	w1, w3, [x19, 40]
	mov	w4, 0
	mov	w0, 0
.L34:
	lsl	w2, w11, w0
	cmp	w2, w8
	beq	.L46
.L35:
	mov	w2, 16
	sub	w0, w2, w0
	sub	w2, w2, w4
	lsl	w13, w13, w0
	lsl	w10, w10, w0
	lsl	w8, w8, w0
	lsl	w7, w7, w0
	lsl	w5, w5, w0
	lsl	w1, w1, w2
	lsl	w3, w3, w2
	lsl	w0, w9, w0
	stp	w8, w7, [x19, 16]
	stp	w5, w0, [x19, 24]
	stp	w13, w10, [x19, 32]
	stp	w1, w3, [x19, 40]
.L13:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L45:
	ldr	x8, .LC4
	ldrb	w8, [x8,w14,uxtw]
	adr	x14, .Lrtx30
	add	x8, x14, w8, sxtb #2
	br	x8
.Lrtx30:
	.section	.rodata
	.align	0
	.align	2
.L30:
	.byte	(.L40 - .Lrtx30) / 4
	.byte	(.L31 - .Lrtx30) / 4
	.byte	(.L32 - .Lrtx30) / 4
	.byte	(.L33 - .Lrtx30) / 4
	.text
	.p2align 3
.L40:
	mov	w3, 0
	mov	w1, 0
	mov	w10, 0
	mov	w13, 0
.L29:
	mov	w0, 0
	mov	w4, 0
.L37:
	asr	w13, w13, w0
	asr	w10, w10, w0
	asr	w1, w1, w4
	asr	w3, w3, w4
	mov	w0, 1
	str	w0, [x19]
	stp	w11, wzr, [x19, 16]
	stp	wzr, w11, [x19, 24]
	stp	w13, w10, [x19, 32]
	stp	w1, w3, [x19, 40]
	b	.L13
	.p2align 3
.L33:
	sdiv	w7, w7, w1
	cmp	w2, w0
	csel	w8, w2, w0, le
	add	w0, w2, w0
	add	w0, w0, w9
	asr	w4, w4, w8
	sub	w0, w0, w8
	asr	w9, w3, w8
	add	w7, w7, w15
	sdiv	w17, w17, w1
	neg	w1, w12
	mul	w8, w1, w13
	mul	w2, w1, w10
	lsl	w1, w3, 1
	add	w5, w5, w8
	add	w17, w17, w8
	add	w6, w6, w2
	mul	w1, w1, w4
	add	w2, w7, w2
	neg	w3, w3, lsl 4
	mul	w8, w5, w4
	mul	w7, w17, w9
	mul	w5, w6, w4
	mul	w9, w2, w9
	mul	w12, w1, w12
	add	w2, w5, w9
	add	w1, w8, w7
	mul	w3, w3, w4
	madd	w1, w12, w13, w1
	sub	w4, w0, #1
	lsl	w13, w13, w0
	madd	w12, w12, w10, w2
	mov	w2, 1
	lsl	w10, w10, w0
	lsl	w4, w2, w4
	add	w1, w1, w3
	add	w13, w13, w4
	add	w10, w10, w4
	add	w4, w0, w2
	add	w3, w12, w3
	lsl	w2, w2, w4
	add	w4, w0, 2
	add	w1, w1, w2
	add	w3, w3, w2
	stp	w8, w7, [x19, 16]
	stp	w5, w9, [x19, 24]
	stp	w13, w10, [x19, 32]
	stp	w1, w3, [x19, 40]
	b	.L34
	.p2align 3
.L32:
	neg	w1, w12
	sub	w7, w20, w6
	add	w0, w9, w2
	mov	w4, 1
	madd	w8, w1, w13, w5
	madd	w5, w1, w10, w6
	lsl	w1, w3, 1
	neg	w3, w3, lsl 4
	mov	w9, w8
	mul	w12, w1, w12
	add	w1, w7, w8
	stp	w8, w7, [x19, 16]
	madd	w1, w12, w13, w1
	lsl	w13, w13, w0
	add	w2, w1, w3
	add	w1, w8, w5
	stp	w5, w8, [x19, 24]
	madd	w12, w12, w10, w1
	sub	w1, w0, #1
	lsl	w10, w10, w0
	add	w12, w12, w3
	add	w3, w0, w4
	lsl	w1, w4, w1
	lsl	w3, w4, w3
	add	w13, w13, w1
	add	w10, w10, w1
	add	w4, w0, 2
	add	w1, w2, w3
	stp	w13, w10, [x19, 32]
	add	w3, w12, w3
	stp	w1, w3, [x19, 40]
	b	.L34
	.p2align 3
.L31:
	and	w1, w13, 1
	and	w3, w10, 1
	orr	w1, w1, w13, asr 1
	orr	w3, w3, w10, asr 1
	b	.L29
	.p2align 3
.L44:
	madd	w5, w11, w8, w13
	add	w6, w5, w6
	madd	w5, w11, w1, w10
	add	w16, w5, w16
	b	.L19
	.p2align 3
.L20:
	sub	w5, w5, w22
	b	.L21
	.p2align 3
.L24:
	sub	w17, w17, w18
	b	.L25
.L39:
	mov	w15, 16
	mov	w4, 1
	mov	w0, 0
	b	.L16
.L38:
	mov	w30, w5
	mov	w3, 1
	mov	w2, 0
	b	.L14
.L46:
	cbnz	w7, .L35
	cbnz	w5, .L35
	cmp	w8, w9
	mov	w7, w5
	bne	.L35
	b	.L37
	.size	MP4_GetGMCparam, .-MP4_GetGMCparam
	.align	3
.LC4:
	.xword	.L30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_GetUserDataBuf
	.type	Mp4_GetUserDataBuf, %function
Mp4_GetUserDataBuf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	w19, w2
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L52
.L48:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L52:
	mov	w0, w21
	bl	GetUsd
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L48
	add	w1, w19, 4
	str	w1, [x0, 1040]
	ldr	x0, [x20, w19, uxtw 3]
	b	.L48
	.size	Mp4_GetUserDataBuf, .-Mp4_GetUserDataBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_ClearUsrData
	.type	Mp4_ClearUsrData, %function
Mp4_ClearUsrData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, 0
	mov	x20, x1
	bl	_mcount
.L54:
	ldr	x1, [x20, x19]
	mov	w0, w21
	bl	FreeUsdByDec
	str	xzr, [x20, x19]
	add	x19, x19, 8
	cmp	x19, 32
	bne	.L54
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Mp4_ClearUsrData, .-Mp4_ClearUsrData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Init
	.type	Mp4_Syntax_Init, %function
Mp4_Syntax_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 16384
	add	x20, x20, 20480
	bl	_mcount
	ldr	x21, .LC7
	mov	x2, 24
	mov	w1, 0
	add	x0, x19, 3632
	ldr	x3, [x21, 96]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 604
	mov	w1, 0
	add	x0, x19, 3656
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 60
	mov	w1, 0
	add	x0, x20, 768
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 776
	mov	w1, 0
	add	x0, x20, 828
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 7
	mov	w1, 0
	add	x0, x20, 1604
	blr	x3
	ldr	x3, .LC8
	mov	w1, 1
	mov	w0, 1
	strb	w1, [x20, 853]
	str	w0, [x20, 2232]
	add	x1, x19, 3744
	add	x4, x3, 256
	mov	w2, 8
	add	x0, x3, 4
	b	.L59
	.p2align 3
.L57:
	ldr	w2, [x0], 4
.L59:
	str	w2, [x1], 4
	cmp	x0, x4
	bne	.L57
	add	x0, x3, 260
	add	x1, x19, 4000
	add	x3, x3, 512
	mov	w2, 16
	b	.L58
	.p2align 3
.L61:
	ldr	w2, [x0], 4
.L58:
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L61
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Mp4_Syntax_Init, .-Mp4_Syntax_Init
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Global_Data_Init
	.type	Global_Data_Init, %function
Global_Data_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldr	x21, .LC11
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 1648
	ldr	x3, [x21, 96]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x19, 1616
	blr	x3
	mov	x0, x20
	bl	Mp4_Syntax_Init
	str	xzr, [x20, 22672]
	str	xzr, [x20, 22680]
	add	x2, x19, 2048
	str	xzr, [x20, 22688]
	mov	w0, 0
	str	xzr, [x20, 22696]
	str	wzr, [x19, 1684]
	str	wzr, [x19, 2144]
	str	wzr, [x19, 2148]
	str	wzr, [x19, 2152]
	str	wzr, [x19, 2160]
	str	xzr, [x20, 22704]
	stp	wzr, wzr, [x2, 116]
	stp	wzr, wzr, [x2, 124]
	str	wzr, [x19, 2180]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Global_Data_Init, .-Global_Data_Init
	.align	3
.LC11:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Bs_Get_Matrix
	.type	Bs_Get_Matrix, %function
Bs_Get_Matrix:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x25, x0
	mov	x0, x30
	mov	x21, x1
	mov	w19, 0
	bl	_mcount
	mov	w22, 0
	ldr	x24, .LC12
	mov	w20, 0
	mov	w23, 63
	b	.L65
	.p2align 3
.L72:
	ldr	w19, [x3, w1, sxtw 2]
	mov	w20, w1
	mov	w22, w0
.L65:
	mov	w1, 8
	mov	x0, x25
	bl	BsGet
	cmp	w0, wzr
	add	w2, w20, 1
	str	w0, [x21, w19, sxtw 2]
	add	x3, x24, 512
	sxtw	x19, w19
	sxth	w1, w2
	ccmp	w1, w23, 0, ne
	ble	.L72
	cbnz	w0, .L63
	cmp	w20, 63
	bgt	.L63
	ldr	x1, .LC12
	b	.L68
	.p2align 3
.L73:
	ldrsw	x19, [x0, w20, sxtw 2]
.L68:
	sxth	w20, w2
	str	w22, [x21, x19, lsl 2]
	cmp	w20, 64
	add	x0, x1, 512
	add	w2, w20, 1
	bne	.L73
.L63:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	Bs_Get_Matrix, .-Bs_Get_Matrix
	.align	3
.LC12:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	NextStartCode
	.type	NextStartCode, %function
NextStartCode:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w2
	mov	x23, x1
	mov	x21, x3
	bl	_mcount
	mov	w2, w22
	mov	x1, x23
	add	x0, x29, 72
	lsl	w19, w22, 3
	bl	BsInit
	mov	w2, 0
	b	.L75
	.p2align 3
.L79:
	cmp	w5, 256
	beq	.L88
.L83:
	bl	BsSkip
	add	x0, x29, 72
	bl	BsPos
	mov	w2, w0
.L75:
	sub	w2, w19, w2
	mov	w1, 32
	cmp	w2, 31
	add	x0, x29, 72
	ble	.L89
	bl	BsShow
	mov	w2, w0
	cmp	w2, 438
	mov	w1, 8
	add	x0, x29, 72
	and	w3, w2, -16
	and	w4, w2, -1024
	and	w5, w2, -256
	beq	.L76
	cmp	w3, 288
	beq	.L76
	cmp	w4, 32768
	bne	.L79
	ldrb	w2, [x20, 9]
	mov	w1, 8
	add	x0, x29, 72
	cmp	w2, 2
	bne	.L90
	ldr	w2, [x20, 752]
	add	w2, w2, 1
	str	w2, [x20, 752]
	cmp	w2, 18
	bls	.L83
	mov	w0, 196
	str	w0, [x21]
	mov	w1, 1
	add	x0, x29, 72
	strb	w1, [x20, 9]
	bl	BsPos
	b	.L78
	.p2align 3
.L76:
	mov	w0, 2
	str	wzr, [x20, 752]
	strb	w0, [x20, 9]
	add	x0, x29, 72
	str	w2, [x21]
	bl	BsPos
.L78:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L89:
	mov	w1, 197
	str	w1, [x21]
	bl	BsPos
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L88:
	str	w2, [x21]
	add	x0, x29, 72
	bl	BsPos
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
.L90:
	mov	w0, 1
	strb	w0, [x20, 9]
	mov	w1, 196
	add	x0, x29, 72
	str	w1, [x21]
	bl	BsPos
	b	.L78
	.size	NextStartCode, .-NextStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4SearchStartCode
	.type	Mp4SearchStartCode, %function
Mp4SearchStartCode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 4
	mov	w0, 0
	ble	.L92
	add	x4, x20, x19, sxtw
	add	x0, x20, 2
.L108:
	cmp	x4, x0
	bls	.L93
.L113:
	ldrb	w2, [x0]
	cmp	w2, 1
	bls	.L94
	and	w3, w2, 252
	cmp	w3, 128
	beq	.L94
.L101:
	add	x0, x0, 3
	cmp	x4, x0
	bhi	.L113
.L93:
	sub	w0, w19, #2
.L92:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L94:
	cbnz	w2, .L96
	ldrb	w2, [x0, -1]
	cbnz	w2, .L97
	add	x0, x0, 1
	b	.L108
	.p2align 3
.L96:
	ldrb	w1, [x0, -2]
	cbnz	w1, .L101
	ldrb	w1, [x0, -1]
	cbnz	w1, .L101
	sub	x0, x0, x20
	sub	w0, w0, #2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L97:
	ldrb	w2, [x0, 1]
	add	x1, x0, 2
	add	x0, x0, 4
	cmp	w2, wzr
	csel	x0, x0, x1, ne
	b	.L108
	.size	Mp4SearchStartCode, .-Mp4SearchStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Gop
	.type	Mp4_Syntax_Gop, %function
Mp4_Syntax_Gop:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	mov	w2, w21
	mov	x1, x20
	add	x0, x29, 56
	bl	BsInit
	mov	w1, 32
	add	x0, x29, 56
	bl	BsSkip
	mov	w1, 5
	add	x0, x29, 56
	bl	BsGet
	mov	w1, 6
	add	x0, x29, 56
	bl	BsGet
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L115
	ldr	x1, .LC15
	mov	w0, 1
	add	x19, x19, 20480
	bl	dprint_vfmw
	add	x0, x29, 56
	strb	wzr, [x19, 1606]
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC16
	ldr	x4, [x0]
	cbz	x4, .L117
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L115:
	mov	w1, 6
	add	x0, x29, 56
	add	x19, x19, 20480
	bl	BsGet
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 830]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 831]
	mov	w1, 1
	add	x0, x29, 56
	strb	w1, [x19, 1606]
	bl	BsPos
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L117:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.size	Mp4_Syntax_Gop, .-Mp4_Syntax_Gop
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC16:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_UserData
	.type	Mp4_Syntax_UserData, %function
Mp4_Syntax_UserData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	w20, w2
	mov	x19, x1
	bl	_mcount
	strb	wzr, [x29, 95]
	cmp	w20, 6
	stp	wzr, wzr, [x29, 96]
	stp	wzr, wzr, [x29, 104]
	ble	.L119
	cmp	w20, 4
	ble	.L120
	ldrb	w0, [x19, 4]
	add	x1, x19, 5
	strb	w0, [x22, 3]
	add	x5, x22, 4
	orr	w0, w0, -256
	mov	w19, 4
	lsl	w0, w0, 8
	b	.L121
	.p2align 3
.L126:
	ldrb	w4, [x1]
	add	x1, x1, 1
	orr	w0, w4, w0
	lsl	w0, w0, 8
	cmp	w0, 256
	beq	.L177
	strb	w4, [x5], 1
	cmp	w3, 1030
	beq	.L178
	mov	w19, w3
.L121:
	add	w3, w19, 1
	sub	w21, w19, #3
	cmp	w20, w3
	bne	.L126
.L124:
	add	x23, x22, 20480
	mov	w1, 1
	cmp	w21, 2
	lsl	w25, w20, 3
	mov	w0, w25
	strb	w1, [x23, 1610]
	bhi	.L179
.L169:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L119:
	add	x22, x22, 20480
	add	w19, w20, 1
	lsl	w0, w19, 3
	strb	wzr, [x22, 1610]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L177:
	sub	w0, w19, #1
	cmp	w20, w0
	bge	.L180
.L125:
	add	w0, w20, 1
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	lsl	w0, w0, 3
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L179:
	ldr	w2, [x23, 2180]
	add	x1, x23, 2192
	ldr	w0, [x23, 2848]
	bl	Mp4_GetUserDataBuf
	str	x0, [x22, 22704]
	cbz	x0, .L181
	sub	w26, w19, #5
	str	w26, [x0, 1052]
	mov	w0, 65533
	ldr	x24, .LC17
	movk	w0, 0x7fff, lsl 16
	add	x20, x22, 3
	cmn	w19, w0
	mov	x2, 0
	ldr	x3, [x24, 104]
	ldr	x0, [x22, 22704]
	bmi	.L182
.L129:
	mov	x1, x20
	blr	x3
	ldr	x1, [x22, 22120]
	ldr	x2, .LC18
	ldr	x0, [x22, 22704]
	ldr	x1, [x1, 56]
	ldr	x4, [x2]
	str	x1, [x0, 1056]
	cbz	x4, .L128
	ldr	w0, [x23, 2848]
	mov	w3, 1064
	ldr	x2, [x22, 22704]
	mov	w1, 6
	blr	x4
.L128:
	mov	w1, 2
	mov	w0, 0
	movk	w1, 0x8000, lsl 16
	cmn	w26, w1
	bmi	.L183
.L130:
	add	x0, x22, x0, sxtw
	ldr	x1, .LC20
	add	x4, x29, 95
	add	x3, x29, 100
	add	x2, x29, 96
	strb	wzr, [x0, 3]
	mov	x0, x20
	ldr	x5, [x24, 144]
	blr	x5
	cmp	w0, 1
	ble	.L184
.L131:
	ldp	w2, w1, [x29, 96]
	cmp	w0, 3
	str	w2, [x23, 1584]
	str	w1, [x23, 1588]
	mov	w0, 0
	beq	.L185
.L133:
	str	w0, [x23, 1592]
.L132:
	ldr	x1, .LC24
	add	x2, x29, 100
	ldr	x3, [x24, 144]
	mov	x0, x20
	blr	x3
	cmp	w0, 1
	beq	.L134
	ldr	x1, .LC26
	add	x5, x29, 100
	ldr	x6, [x24, 144]
	add	x4, x29, 108
	add	x3, x29, 104
	add	x2, x29, 96
	mov	x0, x20
	blr	x6
	cmp	w0, 4
	beq	.L134
	ldr	x1, .LC28
	add	x4, x29, 108
	ldr	x5, [x24, 144]
	add	x3, x29, 104
	add	x2, x29, 96
	mov	x0, x20
	blr	x5
	add	w0, w0, 1
	cmp	w0, 1
	ble	.L135
	ldp	w3, w1, [x29, 104]
	ldr	w2, [x29, 96]
	lsl	w3, w3, 8
	add	w2, w3, w2, lsl 16
	add	w1, w2, w1
	str	w1, [x29, 100]
.L135:
	cmp	w0, 4
	beq	.L134
	ldr	x1, .LC30
	mov	w2, 7
	ldr	x3, [x24, 152]
	mov	x0, x20
	blr	x3
	cbz	w0, .L186
.L146:
	ldr	x1, .LC32
	add	x2, x29, 100
	ldr	x3, [x24, 144]
	mov	x0, x20
	blr	x3
	cmp	w0, 1
	beq	.L137
	ldr	w0, [x23, 1596]
.L138:
	strb	wzr, [x23, 841]
	strb	wzr, [x23, 842]
	strb	wzr, [x23, 839]
	strb	wzr, [x23, 838]
	strb	wzr, [x23, 840]
	ldr	w1, [x23, 1584]
	cbz	w0, .L139
	cbz	w1, .L140
	str	wzr, [x23, 1584]
	str	wzr, [x23, 1588]
.L140:
	cmp	w0, 1
	beq	.L147
	mov	w1, -1
.L141:
	sub	w0, w0, #1
	cmp	w0, 11
	bls	.L151
.L142:
	ldr	w0, [x23, 1600]
	mov	w2, 4668
	sub	w0, w0, #1
	cmp	w0, w2
	bhi	.L143
	mov	w0, 1
	strb	w0, [x23, 839]
.L143:
	cmp	w1, 498
	bhi	.L144
	mov	w0, 1
	strb	w0, [x23, 839]
.L144:
	mov	x1, 500
	ldr	x2, [x22, 22064]
	movk	x1, 0x19d, lsl 32
	mov	w0, w25
	cmp	x2, x1
	bne	.L169
	mov	w1, 1
	strb	w1, [x23, 840]
	b	.L169
.L178:
	add	x22, x22, 20480
	sub	w19, w19, #1
	lsl	w0, w19, 3
	strb	wzr, [x22, 1610]
	b	.L169
.L139:
	cmp	w1, 499
	bls	.L187
	mov	w2, 1
	cmp	w1, 502
	strb	w2, [x23, 841]
	sub	w1, w1, #1
	bls	.L141
.L150:
	mov	w2, 1
	strb	w2, [x23, 842]
	b	.L141
.L147:
	strb	w0, [x23, 841]
	mov	w1, -1
.L151:
	mov	w0, 1
	strb	w0, [x23, 839]
	b	.L142
.L134:
	ldr	w0, [x29, 100]
	str	w0, [x23, 1600]
	b	.L146
.L186:
	mov	w0, 4600
	str	w0, [x23, 1600]
	b	.L146
.L185:
	ldrsb	w0, [x29, 95]
	cmp	w0, 112
	cset	w0, eq
	b	.L133
.L137:
	ldr	w0, [x29, 100]
	str	w0, [x23, 1596]
	b	.L138
.L183:
	add	w0, w26, 2
	mov	w1, 1024
	cmp	w0, w1
	csel	w0, w0, w1, le
	b	.L130
.L182:
	mov	w1, 1024
	cmp	w21, w1
	csel	w21, w21, w1, le
	sxtw	x2, w21
	b	.L129
.L120:
	cmp	w20, 3
	ble	.L125
	add	x22, x22, 20480
	mov	w1, 1
	mov	w0, 32
	strb	w1, [x22, 1610]
	b	.L169
.L181:
	add	x20, x22, 3
	mov	w26, w21
	ldr	x24, .LC17
	b	.L128
.L184:
	ldr	x1, .LC22
	add	x4, x29, 95
	ldr	x5, [x24, 144]
	add	x3, x29, 100
	add	x2, x29, 96
	mov	x0, x20
	blr	x5
	cmp	w0, 1
	ble	.L132
	b	.L131
	.p2align 3
.L180:
	mov	w20, w0
	b	.L124
.L187:
	cmp	w1, 502
	sub	w1, w1, #1
	bhi	.L150
	b	.L142
	.size	Mp4_Syntax_UserData, .-Mp4_Syntax_UserData
	.align	3
.LC17:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	g_event_report
	.align	3
.LC20:
	.xword	.LC19
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
.LC28:
	.xword	.LC27
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Vo
	.type	Mp4_Syntax_Vo, %function
Mp4_Syntax_Vo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	w22, w2
	bl	_mcount
	add	x19, x20, 20480
	mov	w2, w22
	mov	x1, x21
	add	x0, x29, 56
	mov	w21, 1
	add	x20, x20, 16384
	bl	BsInit
	strb	wzr, [x19, 852]
	mov	w1, 32
	strb	w21, [x19, 853]
	strb	wzr, [x19, 854]
	add	x0, x29, 56
	strb	wzr, [x19, 855]
	strb	wzr, [x19, 856]
	strb	wzr, [x19, 857]
	strb	wzr, [x19, 858]
	strb	wzr, [x19, 859]
	str	wzr, [x19, 864]
	str	wzr, [x19, 868]
	str	wzr, [x19, 872]
	bl	BsSkip
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 3632]
	cbnz	w0, .L203
	strb	w21, [x20, 3633]
	mov	w1, 4
	add	x0, x29, 56
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x20, 3635]
	beq	.L204
.L191:
	strb	wzr, [x19, 1605]
	add	x0, x29, 56
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC33
	ldr	x4, [x0]
	cbz	x4, .L196
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L203:
	mov	w1, 4
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x20, 3633]
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x20, 3634]
	mov	w1, 4
	add	x0, x29, 56
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x20, 3635]
	bne	.L191
.L204:
	mov	w1, w21
	add	x0, x29, 56
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 3636]
	cbnz	w0, .L205
.L193:
	mov	w1, 1
	add	x0, x29, 56
	strb	w1, [x19, 1605]
	bl	BsPos
	cmp	w0, w22, lsl 3
	bgt	.L195
	ldrb	w0, [x20, 3632]
	strb	w0, [x19, 852]
	ldrb	w0, [x20, 3633]
	strb	w0, [x19, 853]
	ldrb	w0, [x20, 3634]
	strb	w0, [x19, 854]
	ldrb	w0, [x20, 3635]
	strb	w0, [x19, 855]
	ldrb	w0, [x20, 3636]
	strb	w0, [x19, 856]
	ldrb	w0, [x20, 3637]
	strb	w0, [x19, 857]
	ldrb	w0, [x20, 3638]
	strb	w0, [x19, 858]
	ldrb	w0, [x20, 3639]
	strb	w0, [x19, 859]
	ldr	w0, [x20, 3644]
	str	w0, [x19, 864]
	ldr	w0, [x20, 3648]
	str	w0, [x19, 868]
	ldr	w0, [x20, 3652]
	str	w0, [x19, 872]
.L195:
	add	x0, x29, 56
	bl	BsPos
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L196:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L205:
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x20, 3637]
	mov	w1, w21
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x20, 3638]
	mov	w1, w21
	add	x0, x29, 56
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 3639]
	cbz	w0, .L193
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	str	w0, [x20, 3644]
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	str	w0, [x20, 3648]
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	str	w0, [x20, 3652]
	b	.L193
	.size	Mp4_Syntax_Vo, .-Mp4_Syntax_Vo
	.align	3
.LC33:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Vol
	.type	Mp4_Syntax_Vol, %function
Mp4_Syntax_Vol:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	mov	x21, x1
	mov	w22, w2
	bl	_mcount
	ldr	x0, .LC34
	ldrsw	x1, [x20, 2848]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L267
	ldr	w23, [x0, 1332]
	ldr	w24, [x0, 1336]
.L207:
	mov	w2, w22
	mov	x1, x21
	add	x0, x29, 88
	add	x19, x19, 16384
	add	x21, x19, 3656
	bl	BsInit
	ldr	x22, .LC35
	mov	x2, 604
	mov	w1, 0
	strb	wzr, [x20, 829]
	mov	x0, x21
	ldr	x3, [x22, 96]
	blr	x3
	mov	w1, 32
	add	x0, x29, 88
	bl	BsSkip
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3660]
	mov	w1, 8
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3684]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3656]
	cbnz	w0, .L354
	ldrb	w0, [x20, 853]
	mov	w1, 4
	strb	w0, [x19, 3657]
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 15
	strb	w0, [x19, 3659]
	beq	.L355
.L210:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3661]
	cbnz	w0, .L356
	mov	w0, 1
	strb	w0, [x19, 3662]
.L215:
	mov	w1, 2
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3664]
	cbz	w0, .L357
.L348:
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L286
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, w19
.L322:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L357:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L349
	mov	w1, 16
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3728]
	cbz	w0, .L223
	subs	w0, w0, #1
	beq	.L275
	mov	w2, w0
	mov	w1, 0
	.p2align 2
.L225:
	add	w1, w1, 1
	lsr	w2, w2, 1
	sxth	w1, w1
	cbnz	w2, .L225
	cmp	w1, wzr
	mov	w1, 0
	ble	.L275
	.p2align 2
.L307:
	add	w1, w1, 1
	lsr	w0, w0, 1
	sxth	w1, w1
	cbnz	w0, .L307
.L224:
	str	w1, [x19, 3724]
.L228:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L349
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3665]
	cbnz	w0, .L358
.L230:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L349
	mov	w1, 13
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3736]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L349
	mov	w1, 13
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3740]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L349
	ldr	w0, [x19, 3736]
	cmp	w0, 31
	bls	.L234
	ldr	w1, [x19, 3740]
	cmp	w1, 31
	bls	.L234
	mul	w0, w0, w1
	mul	w23, w23, w24
	cmp	w0, w23
	bhi	.L234
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3666]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3667]
	cbnz	w0, .L237
	ldr	x0, .LC38
	strb	wzr, [x20, 1607]
	ldr	x4, [x0]
	cbz	x4, .L237
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L237:
	ldrb	w2, [x19, 3657]
	mov	w1, 2
	add	x0, x29, 88
	cmp	w2, 1
	csinc	w1, w1, wzr, ne
	bl	BsGet
	uxtb	w23, w0
	strb	w23, [x19, 3668]
	cbz	w23, .L240
	ldr	x0, .LC39
	ldr	w0, [x0]
	tbz	x0, 3, .L359
	sub	w0, w23, #1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L360
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L247
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L247:
	ldr	x1, .LC45
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L322
	.p2align 3
.L349:
	ldr	x1, .LC37
	mov	w0, 1
	bl	dprint_vfmw
.L234:
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L286
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L356:
	mov	w1, 2
	add	x0, x29, 88
	bl	BsGet
	uxtb	w25, w0
	cmp	w25, 1
	strb	w25, [x19, 3662]
	beq	.L212
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L354:
	mov	w1, 4
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3657]
	mov	w1, 3
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3658]
	mov	w1, 4
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 15
	strb	w0, [x19, 3659]
	bne	.L210
.L355:
	mov	w1, 8
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3688]
	mov	w1, 8
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3692]
	b	.L210
	.p2align 3
.L286:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L212:
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3663]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3696]
	cbz	w0, .L215
	mov	w1, 15
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3700]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L350
	mov	w1, 15
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3704]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L350
	mov	w1, 15
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3708]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L350
	mov	w1, 3
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3712]
	mov	w1, 11
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3716]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L350
	mov	w1, 15
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3720]
	mov	w1, w25
	add	x0, x29, 88
	bl	BsGet
	cbnz	w0, .L215
	.p2align 2
.L350:
	ldr	x1, .LC37
	mov	w0, w25
	bl	dprint_vfmw
	b	.L234
	.p2align 3
.L267:
	mov	w24, 8192
	mov	w23, w24
	b	.L207
	.p2align 3
.L223:
	mov	w0, 1
	str	w0, [x19, 3724]
	b	.L228
	.p2align 3
.L275:
	mov	w1, 1
	b	.L224
	.p2align 3
.L358:
	ldr	w1, [x19, 3724]
	add	x0, x29, 88
	bl	BsGet
	str	w0, [x19, 3732]
	b	.L230
.L361:
	mov	w1, 6
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3680]
	mov	w1, w23
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3681]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3682]
	ldrb	w1, [x19, 3668]
	cmp	w1, 2
	bne	.L352
.L240:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3669]
	cbz	w0, .L248
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L249
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L249:
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L322
.L360:
	cmp	w23, 2
	beq	.L361
.L352:
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L246
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L246:
	ldr	x1, .LC43
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L322
.L248:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3670]
	cbnz	w0, .L362
.L251:
	ldrb	w0, [x19, 3657]
	cmp	w0, 1
	beq	.L258
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3673]
.L259:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3674]
	ldr	x1, .LC50
	cbz	w0, .L343
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 3675]
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3676]
	ldr	x1, .LC52
	cbnz	w0, .L343
	ldrb	w0, [x19, 3657]
	cmp	w0, 1
	beq	.L262
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3677]
	ldr	x1, .LC54
	cbnz	w0, .L343
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3678]
	ldr	x1, .LC56
	cbnz	w0, .L343
.L264:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3679]
	cbz	w0, .L265
	ldr	x1, .LC58
.L343:
	mov	w0, 1
	bl	dprint_vfmw
	b	.L348
.L359:
	strb	wzr, [x20, 1607]
	add	x0, x29, 88
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC38
	ldr	x4, [x0]
	cbz	x4, .L242
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L242:
	ldr	x1, .LC41
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L322
.L258:
	strb	wzr, [x19, 3673]
	b	.L259
.L362:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3671]
	cbnz	w0, .L363
	ldr	x0, .LC48
	add	x1, x19, 3744
	add	x3, x0, 256
.L254:
	ldr	w2, [x0], 4
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L254
.L253:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3672]
	cbnz	w0, .L364
	ldr	x0, .LC48
	add	x1, x19, 4000
	add	x0, x0, 256
	add	x3, x0, 256
.L256:
	ldr	w2, [x0], 4
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L256
	b	.L251
.L363:
	add	x1, x19, 3744
	add	x0, x29, 88
	bl	Bs_Get_Matrix
	b	.L253
.L364:
	add	x1, x19, 4000
	add	x0, x29, 88
	bl	Bs_Get_Matrix
	b	.L251
.L265:
	mov	w0, 1
	ldr	x3, [x22, 104]
	strb	w0, [x20, 1607]
	mov	x2, 604
	strb	w0, [x20, 829]
	mov	x1, x21
	strb	w0, [x20, 1608]
	add	x0, x20, 164
	blr	x3
	add	x0, x29, 88
	bl	BsPos
	b	.L322
.L262:
	strb	wzr, [x19, 3677]
	strb	wzr, [x19, 3678]
	b	.L264
	.size	Mp4_Syntax_Vol, .-Mp4_Syntax_Vol
	.align	3
.LC34:
	.xword	s_pstVfmwChan
	.align	3
.LC35:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC38:
	.xword	g_event_report
	.align	3
.LC39:
	.xword	g_VdmCharacter
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
.LC48:
	.xword	.LANCHOR1
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Vos
	.type	Mp4_Syntax_Vos, %function
Mp4_Syntax_Vos:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	mov	w2, w21
	mov	x1, x20
	add	x0, x29, 56
	add	x20, x19, 20480
	add	x19, x19, 16384
	bl	BsInit
	mov	w1, 32
	add	x0, x29, 56
	str	wzr, [x20, 860]
	bl	BsSkip
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	sub	w2, w0, #1
	sub	w1, w0, #240
	cmp	w2, 2
	ccmp	w1, 5, 0, hi
	str	w0, [x19, 3640]
	ccmp	w0, 8, 4, hi
	beq	.L372
	cbz	w0, .L373
	ldr	x0, .LC63
	strb	wzr, [x20, 1604]
	ldr	x4, [x0]
	cbz	x4, .L367
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	add	x0, x29, 56
	bl	BsPos
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L372:
	mov	w1, 1
	str	w0, [x20, 860]
	strb	w1, [x20, 1604]
.L367:
	add	x0, x29, 56
	bl	BsPos
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L373:
	ldr	x1, .LC62
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	strb	w0, [x20, 1604]
	ldr	w0, [x19, 3640]
	str	w0, [x20, 860]
	b	.L367
	.size	Mp4_Syntax_Vos, .-Mp4_Syntax_Vos
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC63:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Frame_Init
	.type	Frame_Init, %function
Frame_Init:
	sub	sp, sp, #128
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w2
	mov	w21, w1
	bl	_mcount
	sub	w2, w22, #32
	sub	w1, w21, #32
	mov	w0, 3807
	cmp	w2, 2127
	ccmp	w1, w0, 2, ls
	bhi	.L375
	ldr	x0, [x19, 22120]
	ldr	w20, [x0, 764]
	cbnz	w20, .L415
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L416
.L405:
	mov	w24, 2
	mov	w25, 5
	mov	w26, 3
.L379:
	ldr	w1, [x0, 880]
	add	x23, x19, 20480
	cmp	w1, 1
	beq	.L390
	ldr	x1, .LC69
	ldr	x8, [x1, 128]
	cbz	x8, .L392
	add	x23, x19, 20480
	ldr	w1, [x0, 20]
	ldr	x20, .LC72
	mov	w6, 0
	ldr	w0, [x0, 16]
	mov	w5, 40
	ldr	w7, [x23, 2848]
	mov	w4, 2
	mov	w3, w22
	mov	w2, w21
	str	x20, [sp]
	blr	x8
	cbnz	w0, .L392
	ldr	w2, [x20, 56]
	ldr	w3, [x20, 48]
	cmp	w2, 1
	ble	.L394
	cmp	w3, 2
	ble	.L394
	ldr	w0, [x20, 464]
	str	w0, [x23, 1672]
	bl	MEM_Phy2Vir
	str	x0, [x19, 22136]
.L390:
	ldr	x0, .LC75
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x19, 22120]
	stp	w21, w22, [x29, 92]
	stp	w21, w22, [x29, 100]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L396
	strb	w26, [x29, 89]
	sxtb	w24, w24
	strb	w25, [x29, 90]
.L401:
	ldr	w0, [x23, 2848]
	add	x1, x29, 88
	strb	w24, [x29, 91]
	bl	FSP_ConfigInstance
	mov	w20, w0
	cbnz	w0, .L397
	ldr	x1, [x19, 22120]
	add	x3, x29, 84
	ldr	w0, [x23, 2848]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L417
	cbnz	w0, .L399
	add	sp, x29, 0
	mov	w0, 1
	str	w0, [x23, 2852]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L375:
	ldr	x1, .LC65
	mov	w3, w22
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, .LC66
	ldr	x4, [x0]
	cbz	x4, .L402
	add	x19, x19, 20480
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w20, -1
	ldr	w0, [x19, 2848]
	blr	x4
.L408:
	add	sp, x29, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L415:
	ldr	w1, [x0, 28]
	cmp	w1, 25
	bne	.L405
	ldr	w4, [x0, 724]
	ldr	w5, [x0, 728]
	cmp	w21, w4
	bhi	.L386
	cmp	w22, w5
	bhi	.L386
	ldr	w2, [x0, 752]
	mov	w24, 1
	ldr	w1, [x0, 748]
	add	w26, w1, 2
	cbnz	w2, .L418
	ldr	w25, [x0, 772]
	b	.L379
	.p2align 3
.L402:
	add	sp, x29, 0
	mov	w20, -1
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L396:
	mov	w0, 1
	strb	w25, [x29, 90]
	strb	w0, [x29, 89]
	mov	w24, 1
	b	.L401
	.p2align 3
.L418:
	add	w1, w1, w24
	mov	w24, 17
	cmp	w1, w24
	ldr	w25, [x0, 772]
	csel	w24, w1, w24, le
	b	.L379
	.p2align 3
.L416:
	ldr	w4, [x0, 724]
	cmp	w21, w4
	bhi	.L419
	ldr	w1, [x0, 728]
	cmp	w22, w1
	mov	w5, w1
	bhi	.L386
	add	x23, x19, 20480
	ldr	w2, [x23, 2852]
	cmp	w2, 1
	beq	.L408
	ldr	w3, [x0, 752]
	mov	w24, 1
	ldr	w2, [x0, 748]
	add	w26, w2, 2
	cbz	w3, .L384
	add	w2, w2, w24
	mov	w24, 17
	cmp	w2, w24
	csel	w24, w2, w24, le
.L384:
	mov	w22, w1
	mov	w21, w4
	ldr	w25, [x0, 772]
	b	.L379
	.p2align 3
.L417:
	add	x0, x23, 2240
	bl	ResetVoQueue
.L399:
	ldr	x1, .LC77
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	str	wzr, [x23, 2852]
	b	.L408
	.p2align 3
.L394:
	ldr	x1, .LC74
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L408
	.p2align 3
.L392:
	ldr	x1, .LC71
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L408
	.p2align 3
.L397:
	ldr	x1, .LC79
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L408
.L419:
	ldr	w5, [x0, 728]
.L386:
	ldr	x1, .LC68
	mov	w3, w22
	mov	w2, w21
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L408
	.size	Frame_Init, .-Frame_Init
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC66:
	.xword	g_event_report
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC69:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC72:
	.xword	.LANCHOR2
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC75:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vdm_Mem_Move
	.type	Vdm_Mem_Move, %function
Vdm_Mem_Move:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w25, w2
	mov	w24, w3
	mov	w23, w4
	mov	w22, w5
	mov	w21, w6
	bl	_mcount
	add	w22, w22, 15
	ldr	x1, .LC81
	mov	w0, 2
	add	w21, w21, 15
	lsr	w22, w22, 4
	lsr	w21, w21, 4
	bl	dprint_vfmw
	str	w25, [x19, 1272]
	str	w24, [x19, 15636]
	add	x2, x19, 1048
	ldr	w0, [x20, 8]
	str	w0, [x19, 1288]
	strh	w22, [x19, 1224]
	strh	w21, [x19, 1226]
	str	w23, [x19, 1280]
	ldr	x0, [x19, 22120]
	ldr	x1, [x20, 40]
	ldr	w1, [x1, 24]
	str	w1, [x19, 15648]
	ldr	x1, [x20, 40]
	ldr	w1, [x1, 28]
	str	w1, [x19, 15652]
	ldr	x1, [x20, 40]
	ldr	w1, [x1, 60]
	str	w1, [x19, 15656]
	ldr	x1, [x20, 40]
	ldr	w1, [x1, 44]
	str	w1, [x19, 15660]
	ldr	x1, [x20, 40]
	ldr	w1, [x1, 48]
	str	w1, [x19, 15664]
	ldr	w1, [x0, 632]
	str	w1, [x19, 15720]
	ldr	w1, [x0, 684]
	str	w1, [x19, 15724]
	str	x2, [x19, 1040]
	ldr	w1, [x0, 920]
	cmp	w1, 1
	beq	.L436
	cmp	w1, 2
	beq	.L437
.L422:
	mov	w0, 1
	strb	w0, [x19, 1214]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L436:
	cbz	x2, .L422
	add	x20, x19, 20480
	str	xzr, [x19, 1040]
	add	x21, x19, 16384
	mov	w2, 0
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2876]
	bl	FSP_SetDisplay
	ldr	w22, [x20, 2848]
	ldr	w0, [x21, 3620]
	cmp	w0, wzr
	ble	.L426
	sub	w0, w0, #1
	add	x20, x19, 12288
	add	x0, x0, 3978
	add	x20, x20, 3620
	add	x19, x19, x0, lsl 2
	.p2align 2
.L425:
	ldr	w1, [x20], 4
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	cmp	x20, x19
	bne	.L425
.L426:
	str	wzr, [x21, 3620]
.L438:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L437:
	ldr	w0, [x0, 924]
	cmp	w0, wzr
	ccmp	x2, xzr, 4, gt
	beq	.L422
	add	x20, x19, 20480
	str	xzr, [x19, 1040]
	mov	w2, 0
	add	x21, x19, 16384
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2876]
	bl	FSP_SetDisplay
	ldr	x1, [x19, 22120]
	ldr	w0, [x1, 924]
	sub	w0, w0, #1
	str	w0, [x1, 924]
	ldr	w0, [x21, 3620]
	ldr	w22, [x20, 2848]
	cmp	w0, wzr
	ble	.L426
	sub	w0, w0, #1
	add	x20, x19, 12288
	add	x0, x0, 3978
	add	x20, x20, 3620
	add	x19, x19, x0, lsl 2
	.p2align 2
.L427:
	ldr	w1, [x20], 4
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	cmp	x20, x19
	bne	.L427
	str	wzr, [x21, 3620]
	b	.L438
	.size	Vdm_Mem_Move, .-Vdm_Mem_Move
	.align	3
.LC81:
	.xword	.LC80
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_RecordVFMWState
	.type	Mp4_RecordVFMWState, %function
Mp4_RecordVFMWState:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	Mp4_RecordVFMWState, .-Mp4_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_RecordFrameAtr
	.type	Mp4_RecordFrameAtr, %function
Mp4_RecordFrameAtr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 20480
	mov	w19, w1
	bl	_mcount
	ldrb	w0, [x20, 879]
	cmp	w0, 15
	beq	.L457
	sub	w2, w0, #2
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L450
	sub	w2, w0, #4
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L451
	mov	w22, 5
	cmp	w0, 1
	csel	w22, wzr, w22, ne
.L442:
	ldr	w0, [x20, 2848]
	mov	w1, w19
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L440
	ldr	w2, [x20, 1544]
	mov	w1, w22
	str	w2, [x0, 68]
	ldr	w2, [x20, 1540]
	str	w2, [x0, 72]
	bl	SetAspectRatio
	ldr	x0, [x21, 22120]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L458
.L446:
	ldr	w0, [x20, 1544]
	mov	x4, -1
	str	w0, [x19, 76]
	mov	w0, 29
	ldrb	w2, [x19, 64]
	ldr	w3, [x20, 1540]
	str	w3, [x19, 80]
	ldrb	w1, [x19, 65]
	ldr	w3, [x20, 1544]
	lsr	w3, w3, 1
	str	w3, [x19, 84]
	ldr	w3, [x20, 1540]
	lsr	w3, w3, 1
	str	w3, [x19, 88]
	ldr	w3, [x20, 2148]
	str	w3, [x19, 160]
	ldr	w3, [x20, 2144]
	str	w3, [x19, 156]
	ldrb	w3, [x20, 1480]
	bfi	w2, w3, 0, 2
	strb	w2, [x19, 64]
	ldrb	w3, [x20, 857]
	bfi	w2, w3, 5, 3
	strb	w2, [x19, 64]
	ldrb	w2, [x20, 886]
	and	w2, w2, 1
	bfi	w1, w2, 0, 2
	orr	w1, w1, 12
	strb	w1, [x19, 65]
	ldrb	w2, [x20, 1485]
	bfi	w1, w2, 4, 2
	strb	w1, [x19, 65]
	ldr	w1, [x19, 64]
	bfi	w1, w22, 14, 3
	str	w1, [x19, 64]
	lsr	w1, w1, 16
	ldrb	w2, [x20, 844]
	bfi	w1, w2, 1, 1
	strb	w1, [x19, 66]
	ldr	w1, [x20, 848]
	str	w1, [x19, 120]
	ldrb	w1, [x20, 1480]
	and	w1, w1, 3
	str	w1, [x19, 56]
	ldrb	w1, [x20, 1480]
	and	w1, w1, 3
	str	w1, [x19, 60]
	str	wzr, [x19, 52]
	ldr	x1, [x21, 22672]
	str	x1, [x19, 544]
	ldr	x1, [x21, 22680]
	str	x1, [x19, 552]
	ldr	x1, [x21, 22688]
	str	x1, [x19, 560]
	ldr	x1, [x21, 22696]
	str	x1, [x19, 568]
	ldr	x1, [x21, 22120]
	ldr	x1, [x1, 56]
	str	x1, [x19, 584]
	ldr	x1, [x21, 22120]
	ldr	x1, [x1, 72]
	str	x1, [x19, 592]
	ldr	x1, [x21, 22120]
	ldr	x1, [x1, 88]
	str	x1, [x19, 600]
	ldr	x1, [x21, 22120]
	ldr	w1, [x1, 104]
	str	w1, [x19]
	ldr	x1, [x21, 22120]
	ldr	w1, [x1, 108]
	str	w1, [x19, 4]
	ldr	x1, [x21, 22120]
	ldr	w1, [x1, 112]
	str	w1, [x19, 8]
	ldr	x1, [x21, 22120]
	ldr	w1, [x1, 128]
	str	w1, [x19, 12]
	ldr	x1, [x21, 22120]
	str	x4, [x1, 56]
	ldr	x3, [x19, 592]
	ldr	x2, [x19, 584]
	ldr	x1, .LC83
	bl	dprint_vfmw
	strb	wzr, [x19, 284]
	mov	w1, 1
	strb	w1, [x19, 289]
	add	x1, x19, 256
	strb	wzr, [x19, 291]
	mov	w0, 8
	mov	w2, 2
	stp	w0, w0, [x1, 48]
	stp	w2, w0, [x1, 40]
.L440:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L458:
	ldr	w1, [x19, 72]
	ldr	w3, [x19, 112]
	add	w1, w1, 15
	ldr	w2, [x19, 36]
	lsl	w0, w3, 4
	lsr	w1, w1, 4
	ldr	x4, [x19, 504]
	mul	w0, w1, w0
	add	w1, w3, w2
	str	w1, [x19, 28]
	add	w1, w0, w2
	str	w2, [x19, 20]
	add	x0, x4, x0, sxtw
	add	w3, w3, w1
	str	w1, [x19, 24]
	str	w3, [x19, 32]
	str	w1, [x19, 40]
	str	x0, [x19, 512]
	b	.L446
	.p2align 3
.L451:
	mov	w22, 2
	b	.L442
	.p2align 3
.L450:
	mov	w22, 1
	b	.L442
	.p2align 3
.L457:
	ldr	w1, [x20, 908]
	mov	w22, 0
	ldr	w0, [x20, 912]
	cmp	w1, wzr
	ccmp	w0, wzr, 4, ne
	cset	w3, eq
	cbnz	w3, .L442
	ldr	w2, [x20, 960]
	mov	w22, w3
	mul	w2, w0, w2
	cbz	w2, .L442
	ldr	w0, [x20, 956]
	lsl	w1, w1, 10
	mul	w0, w1, w0
	udiv	w0, w0, w2
	subs	w2, w0, #1365
	bmi	.L459
.L443:
	subs	w1, w0, #1820
	bmi	.L460
.L444:
	mov	w22, 2
	cmp	w2, w1
	csinc	w22, w22, wzr, ge
	b	.L442
	.p2align 3
.L459:
	mov	w2, 1365
	sub	w2, w2, w0
	b	.L443
	.p2align 3
.L460:
	mov	w1, 1820
	sub	w1, w1, w0
	b	.L444
	.size	Mp4_RecordFrameAtr, .-Mp4_RecordFrameAtr
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Frame_Atr
	.type	Mp4_Frame_Atr, %function
Mp4_Frame_Atr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldrb	w0, [x19, 1480]
	strb	w0, [x20, 2]
	cmp	w0, 4
	ldr	w0, [x19, 2848]
	beq	.L471
.L463:
	mov	w1, 1
	bl	FSP_NewLogicFs
	str	w0, [x19, 2876]
	tbnz	w0, #31, .L464
	ldr	w1, [x19, 2852]
	cbz	w1, .L464
	mov	w1, w0
	mov	x0, x20
	bl	Mp4_RecordFrameAtr
	str	wzr, [x19, 2152]
	mov	w0, 0
.L467:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L471:
	sxtw	x2, w0
	ldr	x1, .LC84
	lsl	x3, x2, 4
	add	x2, x3, x2, lsl 2
	add	x1, x1, x2, lsl 4
	sub	x1, x1, x2
	ldr	w2, [x1, 12]
	add	w2, w2, 1
	str	w2, [x1, 12]
	b	.L463
	.p2align 3
.L464:
	ldr	x1, .LC86
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L466
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 568]
	bl	FreeUsdByDec
	add	x0, x20, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2860]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 2860]
	ldr	w0, [x19, 2848]
	str	wzr, [x19, 2868]
	bl	FSP_GetNullLogicFs
	str	w0, [x19, 2860]
	str	w0, [x19, 2868]
.L466:
	ldr	w0, [x19, 2848]
	add	x1, x19, 2240
	str	wzr, [x19, 2856]
	bl	FSP_ClearNotInVoQueue
	mov	w0, -1
	b	.L467
	.size	Mp4_Frame_Atr, .-Mp4_Frame_Atr
	.align	3
.LC84:
	.xword	g_VfmwChanStat
	.align	3
.LC86:
	.xword	.LC85
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Set_DecPar
	.type	Mp4_Set_DecPar, %function
Mp4_Set_DecPar:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldr	x3, .LC87
	mov	x2, 48
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x3, 96]
	blr	x3
	ldrb	w0, [x20, 10]
	cmp	w0, 1
	beq	.L490
	add	x19, x22, 1048
	ldr	w0, [x20, 104]
	add	x21, x22, 20480
	and	w0, w0, -4
	str	w0, [x19, 180]
	ldr	w0, [x21, 1624]
	str	w0, [x19, 192]
	ubfiz	w0, w0, 3, 2
	ldr	x2, [x22, 22096]
	str	x2, [x19, 16]
	ldr	w2, [x21, 1632]
	add	w0, w0, w2
	str	w0, [x19, 200]
	ldr	w0, [x21, 1628]
	lsl	w0, w0, 3
	sub	w0, w0, w2
	str	w0, [x19, 208]
	ldr	w0, [x20, 104]
	str	w0, [x19, 196]
	ldr	x0, [x20, 88]
	str	x0, [x19, 24]
	ldr	w0, [x20, 104]
	ubfiz	w0, w0, 3, 2
	str	w0, [x19, 204]
	ldr	w0, [x20, 108]
	str	wzr, [x19, 188]
	lsl	w0, w0, 3
	str	w0, [x19, 212]
.L474:
	add	x20, x21, 828
	ldr	w2, [x20, 716]
	add	w0, w2, 15
	lsr	w0, w0, 4
	strh	w0, [x19, 176]
	ldr	w1, [x20, 712]
	add	w0, w1, 15
	lsr	w0, w0, 4
	strh	w0, [x19, 178]
	ldrb	w0, [x20, 652]
	strb	w0, [x22, 1048]
	cmp	w0, 3
	ldrb	w0, [x20, 62]
	strb	w0, [x19, 1]
	ldrb	w0, [x20, 9]
	strb	w0, [x19, 2]
	ldrb	w0, [x20, 659]
	strb	w0, [x19, 3]
	ldrb	w0, [x20, 664]
	strb	w0, [x19, 4]
	ldrb	w0, [x20, 663]
	strb	w0, [x19, 5]
	ldr	w0, [x20, 116]
	strb	w0, [x19, 6]
	ldrb	w0, [x20, 660]
	strb	w0, [x19, 7]
	ldrb	w0, [x20, 661]
	strb	w0, [x19, 8]
	ldrb	w0, [x20, 656]
	strb	w0, [x19, 9]
	ldrb	w0, [x20, 67]
	strb	w0, [x19, 10]
	ldrb	w0, [x20, 65]
	strb	w0, [x19, 11]
	ldrb	w0, [x20, 654]
	strb	w0, [x19, 12]
	ldrb	w0, [x20, 658]
	strb	w0, [x19, 13]
	ldrb	w0, [x20, 657]
	strb	w0, [x19, 14]
	ldrb	w0, [x20, 58]
	strb	w0, [x19, 15]
	ldr	w0, [x20, 748]
	str	w0, [x19, 216]
	ldr	w0, [x20, 744]
	str	w0, [x19, 220]
	ldrb	w0, [x20, 12]
	strb	w0, [x19, 162]
	ldrb	w0, [x20, 11]
	strb	w0, [x19, 161]
	ldrb	w0, [x20, 10]
	strb	w0, [x19, 160]
	ldrb	w0, [x20, 13]
	strb	w0, [x19, 163]
	ldrb	w0, [x20, 14]
	strb	w0, [x19, 164]
	ldrb	w0, [x20, 15]
	strb	w0, [x19, 165]
	str	w1, [x19, 14620]
	str	w2, [x19, 14624]
	ldrb	w0, [x20, 60]
	str	w0, [x19, 14628]
	ccmp	w0, 2, 0, eq
	beq	.L491
	ldrb	w0, [x20, 73]
	str	w0, [x19, 14636]
	str	wzr, [x19, 14632]
	str	wzr, [x19, 14640]
	str	wzr, [x19, 14644]
	str	wzr, [x19, 14648]
	str	wzr, [x19, 14652]
	str	wzr, [x19, 14656]
	str	wzr, [x19, 14660]
	str	wzr, [x19, 14664]
	str	wzr, [x19, 14668]
.L476:
	ldr	w1, [x21, 2876]
	ldr	w0, [x21, 2848]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	w1, [x21, 2860]
	ldr	w0, [x21, 2848]
	bl	FSP_GetLogicFs
	mov	x23, x0
	ldr	w1, [x21, 2868]
	ldr	w0, [x21, 2848]
	bl	FSP_GetLogicFs
	cmp	x20, xzr
	ccmp	x23, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L492
	ldp	x5, x6, [x20, 32]
	cbz	x5, .L480
	cbz	x6, .L480
	ldr	w1, [x20, 8]
	str	w1, [x19, 240]
	ldr	w1, [x0, 8]
	str	w1, [x19, 244]
	ldr	x0, [x0, 32]
	cbz	x0, .L493
.L488:
	ldr	w0, [x0, 8]
	str	w0, [x19, 236]
	ldr	x0, [x23, 32]
	cbz	x0, .L494
.L489:
	ldr	w0, [x0, 8]
	add	x1, x22, 1080
	str	w0, [x19, 232]
	add	x3, x21, 1220
	add	x0, x21, 964
	ldr	x2, [x20, 32]
	ldr	w2, [x2, 8]
	str	w2, [x19, 224]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 8]
	str	w2, [x19, 14588]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 24]
	str	w2, [x19, 14600]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 28]
	str	w2, [x19, 14604]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 60]
	str	w2, [x19, 14608]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 44]
	str	w2, [x19, 14612]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 48]
	str	w2, [x19, 14616]
	.p2align 2
.L486:
	ldr	w2, [x0]
	add	x0, x0, 4
	strb	w2, [x1]
	add	x1, x1, 1
	cmp	x3, x0
	ldr	w2, [x0, 252]
	strb	w2, [x1, 63]
	bne	.L486
	ldrh	w1, [x19, 178]
	ldrh	w0, [x19, 176]
	mul	w0, w0, w1
	str	w0, [x21, 1512]
	ldr	x0, [x22, 22120]
	ldr	w1, [x0, 632]
	str	w1, [x19, 14672]
	ldr	w0, [x0, 684]
	str	w0, [x19, 14676]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
.L492:
	ldr	x2, .LC88
	mov	w3, 3353
	ldr	x1, .LC90
	mov	w0, 0
	add	x2, x2, 1280
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
.L490:
	add	x21, x22, 20480
	add	x19, x22, 1048
	ldr	w1, [x21, 1624]
	str	w1, [x19, 180]
	and	w3, w1, -4
	str	w3, [x19, 192]
	ubfiz	w1, w1, 3, 2
	ldr	x3, [x22, 22096]
	str	x3, [x19, 16]
	ldr	w3, [x21, 1632]
	add	w1, w1, w3
	str	w1, [x19, 200]
	ldr	w1, [x21, 1628]
	str	w0, [x19, 188]
	lsl	w0, w1, 3
	str	wzr, [x19, 196]
	sub	w0, w0, w3
	str	wzr, [x19, 204]
	str	wzr, [x19, 212]
	str	w0, [x19, 208]
	b	.L474
.L480:
	ldr	w2, [x21, 2860]
	mov	w0, 0
	ldr	w4, [x21, 2868]
	ldr	w3, [x21, 2876]
	ldr	x1, .LC92
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
.L494:
	ldr	x0, [x20, 32]
	b	.L489
.L493:
	ldr	x0, [x20, 32]
	b	.L488
.L491:
	add	x1, x29, 64
	mov	x0, x20
	bl	MP4_GetGMCparam
	ldrb	w2, [x20, 73]
	ldp	w6, w0, [x29, 80]
	ldr	w1, [x29, 64]
	ldp	w5, w4, [x29, 88]
	ldr	w3, [x29, 96]
	str	w1, [x19, 14632]
	str	w2, [x19, 14636]
	str	w0, [x19, 14644]
	ldp	w2, w1, [x29, 100]
	ldr	w0, [x29, 108]
	str	w6, [x19, 14640]
	str	w5, [x19, 14648]
	str	w4, [x19, 14652]
	str	w3, [x19, 14656]
	str	w2, [x19, 14660]
	str	w1, [x19, 14664]
	str	w0, [x19, 14668]
	b	.L476
	.size	Mp4_Set_DecPar, .-Mp4_Set_DecPar
	.align	3
.LC87:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC88:
	.xword	.LANCHOR1
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Get_DecMode
	.type	Mp4_Get_DecMode, %function
Mp4_Get_DecMode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 20480
	ldr	w0, [x1, 1684]
	cmp	w0, 2
	ldr	x0, [x19, 22120]
	beq	.L507
	ldr	w0, [x0, 8]
	cmp	w0, 2
	beq	.L500
.L508:
	cmp	w0, 1
	beq	.L506
	cmp	w0, 4
	csel	w0, w0, wzr, eq
.L506:
	str	w0, [x1, 1684]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L507:
	ldr	w2, [x0, 8]
	cmp	w2, 2
	beq	.L500
	mov	w2, 1
	str	w2, [x1, 2232]
	ldr	w0, [x0, 8]
	cmp	w0, 2
	bne	.L508
.L500:
	mov	w0, 2
	str	w0, [x1, 1684]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Mp4_Get_DecMode, .-Mp4_Get_DecMode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetTrailingOneLen
	.type	GetTrailingOneLen, %function
GetTrailingOneLen:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x19, sxtw
	bl	_mcount
	mov	w2, 0
	ldrb	w1, [x19, -1]
	tbnz	x1, 0, .L511
	b	.L516
	.p2align 3
.L513:
	mov	w2, w0
.L511:
	lsr	w1, w1, 1
	add	w0, w2, 1
	tbnz	x1, 0, .L513
	add	w2, w2, 2
	cmp	w0, wzr
	csel	w0, w2, w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L516:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetTrailingOneLen, .-GetTrailingOneLen
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_Init
	.type	MPEG4DEC_Init, %function
MPEG4DEC_Init:
	sub	sp, sp, #784
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x1, .LC94
	mov	w0, 2
	bl	dprint_vfmw
	cmp	x19, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L522
	ldr	w0, [x21, 656]
	add	x20, x19, 20480
	ldr	x22, .LC95
	cmp	w0, 1
	beq	.L525
.L520:
	ldr	x3, [x22, 96]
	mov	x2, 23376
	mov	w1, 0
	mov	x0, x19
	ldr	w23, [x20, 2840]
	blr	x3
	str	w23, [x20, 2840]
	add	x0, x20, 2240
	bl	ResetVoQueue
	str	x21, [x19, 22120]
	mov	x0, x19
	str	wzr, [x21, 928]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 2848]
	beq	.L526
	mov	x0, x19
	bl	Global_Data_Init
	mov	w23, w0
	cbnz	w0, .L522
	mov	w0, 1
	ldr	x1, .LC99
	str	w0, [x20, 2156]
	mov	w0, 2
	str	wzr, [x20, 2184]
	bl	dprint_vfmw
	ldr	w21, [x21, 656]
	cmp	w21, 1
	beq	.L527
.L519:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 784
	ret
	.p2align 3
.L527:
	ldr	x3, [x22, 104]
	add	x1, x29, 72
	mov	x2, 776
	add	x0, x20, 828
	add	x19, x19, 16384
	blr	x3
	mov	x2, 24
	add	x0, x29, 72
	ldr	x3, [x22, 104]
	add	x1, x0, x2
	add	x0, x19, 3632
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x29, 120
	mov	x2, 604
	add	x0, x19, 3656
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x29, 64
	mov	x2, 7
	add	x0, x20, 1604
	blr	x3
	strb	w21, [x20, 2885]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 784
	ret
	.p2align 3
.L525:
	ldr	x3, [x22, 104]
	add	x1, x20, 828
	mov	x2, 776
	add	x0, x29, 72
	add	x23, x19, 16384
	blr	x3
	mov	x2, 24
	ldr	x3, [x22, 104]
	add	x0, x29, 72
	add	x1, x23, 3632
	add	x0, x0, x2
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x23, 3656
	mov	x2, 604
	add	x0, x29, 120
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 7
	add	x1, x20, 1604
	add	x0, x29, 64
	blr	x3
	b	.L520
	.p2align 3
.L522:
	mov	w23, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 784
	ret
	.p2align 3
.L526:
	ldr	x1, .LC97
	mov	w0, 0
	mov	w23, -20
	bl	dprint_vfmw
	b	.L519
	.size	MPEG4DEC_Init, .-MPEG4DEC_Init
	.align	3
.LC94:
	.xword	.LC93
	.align	3
.LC95:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_Destroy
	.type	MPEG4DEC_Destroy, %function
MPEG4DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 20480
	bl	_mcount
	ldr	x1, .LC101
	mov	w0, 2
	bl	dprint_vfmw
	str	wzr, [x19, 2156]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG4DEC_Destroy, .-MPEG4DEC_Destroy
	.align	3
.LC101:
	.xword	.LC100
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_RecycleImage
	.type	MPEG4DEC_RecycleImage, %function
MPEG4DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L531
	add	x19, x19, 20480
	mov	w1, w20
	mov	w2, 0
	ldr	w0, [x19, 2848]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 2848]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L532
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 2848]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
.L530:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L532:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L531:
	mov	w0, -2
	b	.L530
	.size	MPEG4DEC_RecycleImage, .-MPEG4DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_SetImgFormat
	.type	MP4_SetImgFormat, %function
MP4_SetImgFormat:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 20480
	bl	_mcount
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2876]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L533
	ldr	w2, [x19, 1544]
	cbnz	w2, .L546
.L535:
	ldp	w2, w1, [x0, 68]
	stp	w2, w1, [x0, 76]
.L536:
	ldrb	w3, [x19, 844]
	mov	w1, 8
	ldrb	w2, [x0, 66]
	mov	w4, 2
	bfi	w2, w3, 1, 1
	strb	w2, [x0, 66]
	mov	w2, 1
	ldr	w3, [x19, 848]
	strb	w2, [x0, 289]
	add	x2, x0, 256
	strb	wzr, [x0, 284]
	strb	wzr, [x0, 291]
	str	w3, [x0, 120]
	stp	w4, w1, [x2, 40]
	stp	w1, w1, [x2, 48]
.L533:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L546:
	ldr	w3, [x19, 1540]
	cbz	w3, .L535
	ldp	w3, w4, [x0, 68]
	cmp	w3, w2
	csel	w2, w3, w2, ls
	str	w2, [x0, 76]
	ldr	w1, [x19, 1540]
	cmp	w1, w4
	csel	w1, w1, w4, ls
	str	w1, [x0, 80]
	b	.L536
	.size	MP4_SetImgFormat, .-MP4_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_GetRemainImg
	.type	MPEG4DEC_GetRemainImg, %function
MPEG4DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldr	x0, [x20, 22120]
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L548
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L548
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_GetDisplay
	cmp	w0, 2
	mov	w23, w0
	beq	.L561
.L548:
	add	x21, x19, 2240
.L552:
	mov	x0, x21
	bl	GetVoLastImageID
.L558:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L561:
	mov	x0, x20
	add	x21, x19, 2240
	bl	MP4_SetImgFormat
	mov	w2, 1
	str	w2, [x22, 180]
	ldr	w1, [x22, 148]
	ldr	w0, [x19, 2848]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 2848]
	mov	x4, x22
	mov	x3, x21
	mov	x2, x20
	mov	w1, w23
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L549
	ldr	w1, [x22, 148]
	mov	x0, x20
	bl	MPEG4DEC_RecycleImage
	ldr	w0, [x19, 2848]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x19, 2848]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L552
	.p2align 3
.L549:
	ldr	w0, [x22, 152]
	cmp	w0, 100
	bhi	.L548
	ldr	w0, [x22, 68]
	cmp	w0, 31
	bls	.L548
	ldr	w1, [x22, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L558
	b	.L552
	.size	MPEG4DEC_GetRemainImg, .-MPEG4DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_GetImageBuffer
	.type	MPEG4DEC_GetImageBuffer, %function
MPEG4DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 20480
	bl	_mcount
	ldr	w0, [x19, 2848]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L563
	ldr	w0, [x19, 2848]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L568
.L563:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L568:
	ldr	w0, [x19, 2848]
	add	x1, x19, 2240
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG4DEC_GetImageBuffer, .-MPEG4DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_GetPacketState
	.type	MP4_GetPacketState, %function
MP4_GetPacketState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 16384
	bl	_mcount
	mov	w0, 3
	ldr	w1, [x19, 3628]
	ldr	x19, [sp, 16]
	cmp	w1, 1
	csinv	w0, w0, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MP4_GetPacketState, .-MP4_GetPacketState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_ClearCurPacket
	.type	MP4_ClearCurPacket, %function
MP4_ClearCurPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 24]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 10]
	cbnz	w0, .L573
	ldrb	w0, [x19, 98]
	cmp	w0, 1
	beq	.L574
.L573:
	ldr	x3, .LC102
	mov	x2, 176
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L574:
	ldr	w1, [x19, 112]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	b	.L573
	.size	MP4_ClearCurPacket, .-MP4_ClearCurPacket
	.align	3
.LC102:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_ClearCurPic
	.type	MP4_ClearCurPic, %function
MP4_ClearCurPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 16384
	bl	_mcount
	add	x1, x20, 20480
	ldr	w0, [x22, 3620]
	cmp	w0, wzr
	ldr	w21, [x1, 2848]
	ble	.L578
	sub	w0, w0, #1
	add	x19, x20, 12288
	add	x0, x0, 3978
	add	x19, x19, 3620
	add	x20, x20, x0, lsl 2
	.p2align 2
.L577:
	ldr	w1, [x19], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x20
	bne	.L577
.L578:
	str	wzr, [x22, 3620]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP4_ClearCurPic, .-MP4_ClearCurPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_GetScdUpMsg
	.type	MP4_GetScdUpMsg, %function
MP4_GetScdUpMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, [x19, 22120]
	add	x0, x19, 12288
	add	x19, x19, 20480
	add	x0, x0, 3616
	add	x19, x19, 2892
	ldr	w2, [x1, 880]
	cmp	w2, 1
	beq	.L584
.L582:
	ldr	x21, .LC103
	add	x20, x20, 80
	mov	x2, 4
	mov	x1, x20
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 4
	mov	x1, x20
	mov	x0, x19
	blr	x3
.L581:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L584:
	ldr	w1, [x1, 928]
	cmp	w1, 1
	bne	.L582
	ldr	x3, .LC103
	mov	x2, 4
	mov	x1, x19
	ldr	x3, [x3, 104]
	blr	x3
	b	.L581
	.size	MP4_GetScdUpMsg, .-MP4_GetScdUpMsg
	.align	3
.LC103:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Check_Slice_NotSH
	.type	Mp4_Check_Slice_NotSH, %function
Mp4_Check_Slice_NotSH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16384
	add	x3, x19, 20480
	ldrb	w0, [x0, 3675]
	ldrb	w2, [x3, 768]
	cbnz	w0, .L593
	add	x19, x19, 12288
	ldrb	w0, [x19, 3616]
	tst	w0, 120
	bne	.L593
	ldrh	w0, [x19, 3616]
	cmp	w2, 3
	ubfx	x0, x0, 7, 4
	add	w0, w0, 17
	bls	.L595
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L586:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L595:
	ldr	x1, .LC104
	ldrb	w1, [x1,w2,uxtw]
	adr	x2, .Lrtx589
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx589:
	.section	.rodata
	.align	0
	.align	2
.L589:
	.byte	(.L594 - .Lrtx589) / 4
	.byte	(.L590 - .Lrtx589) / 4
	.byte	(.L591 - .Lrtx589) / 4
	.byte	(.L590 - .Lrtx589) / 4
	.text
	.p2align 3
.L594:
	mov	w1, 17
.L588:
	cmp	w1, w0
	ldr	x19, [sp, 16]
	csetm	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L591:
	ldrb	w2, [x3, 777]
	ldrb	w1, [x3, 776]
	mov	w3, 18
	cmp	w1, w2, uxtb
	csel	w1, w1, w2, cs
	uxtb	w1, w1
	add	w1, w1, 16
	cmp	w1, w3
	csel	w1, w1, w3, ge
	b	.L588
	.p2align 3
.L590:
	ldrb	w1, [x3, 776]
	add	w1, w1, 16
	b	.L588
	.p2align 3
.L593:
	mov	w0, -1
	b	.L586
	.size	Mp4_Check_Slice_NotSH, .-Mp4_Check_Slice_NotSH
	.align	3
.LC104:
	.xword	.L589
	.align	3
.LC106:
	.xword	.LC105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Combine_SliceData
	.type	Mp4_Combine_SliceData, %function
Mp4_Combine_SliceData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x19, 16384
	add	x4, x19, 1296
	ldr	w3, [x19, 15632]
	ldr	w0, [x0, 3624]
	tbz	x0, 1, .L597
	add	x1, x19, 12288
	ldrb	w0, [x1, 3450]
	cmp	w0, 1
	beq	.L611
	cbnz	w0, .L605
	ldrb	w0, [x1, 3538]
	cmp	w0, 1
	bne	.L605
	sub	w2, w3, #1
	lsl	x0, x2, 3
	sub	x2, x0, x2
	add	x2, x4, x2, lsl 2
	ldr	w0, [x2, 12]
	cbnz	w0, .L607
	ldr	w0, [x2, 20]
	cbnz	w0, .L607
	ldr	w1, [x2, 8]
	add	w20, w1, w20, lsl 3
	str	w20, [x2, 8]
	ldr	w1, [x19, 15832]
	str	w1, [x2, 20]
	ldr	w1, [x19, 15836]
	lsl	w1, w1, 3
	str	w1, [x2, 12]
.L600:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L611:
	sub	w2, w3, #1
	cmp	w2, 510
	bhi	.L612
	lsl	x1, x2, 3
	sub	x1, x1, x2
	add	x2, x4, x1, lsl 2
	ldr	w1, [x2, 12]
	cbz	w1, .L601
	ldr	w3, [x2, 20]
	cbz	w3, .L601
	ldr	w4, [x19, 15744]
	cmp	w3, w4
	bhi	.L613
	add	w1, w1, w20, lsl 3
	mov	w0, 0
	str	w1, [x2, 12]
	b	.L600
	.p2align 3
.L601:
	ldr	w0, [x2, 16]
	ldr	w1, [x19, 15744]
	cmp	w1, w0
	bls	.L603
	ldr	w1, [x2, 8]
	mov	w0, 0
	add	w20, w1, w20, lsl 3
	str	w20, [x2, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L603:
	lsl	w20, w20, 3
	str	w20, [x2, 12]
	mov	w0, 0
	ldr	w1, [x19, 15744]
	str	w1, [x2, 20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L605:
	ldr	x1, .LC110
	mov	w2, 4513
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L600
	.p2align 3
.L607:
	mov	w0, -1
	b	.L600
	.p2align 3
.L597:
	ldr	x1, .LC110
	mov	w2, 4519
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L600
.L612:
	ldr	x1, .LC108
	mov	w2, w3
	bl	dprint_vfmw
	mov	w0, -1
	b	.L600
.L613:
	ldr	x1, .LC110
	mov	w2, 4489
	bl	dprint_vfmw
	mov	w0, -1
	b	.L600
	.size	Mp4_Combine_SliceData, .-Mp4_Combine_SliceData
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Check_StreamType
	.type	MP4_Check_StreamType, %function
MP4_Check_StreamType:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x2, x19, 12288
	add	x19, x19, 20480
	ldrb	w0, [x2, 3616]
	tbnz	x0, 0, .L615
	mov	w0, 2
	strb	w0, [x19, 837]
	ldr	w0, [x20]
	lsr	w0, w0, 8
	sub	w0, w0, #128
	cmp	w0, 3
	bhi	.L616
	ldrb	w0, [x2, 3616]
	orr	w0, w0, 2
	strb	w0, [x2, 3616]
.L616:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L615:
	mov	w0, 196
	str	w0, [x20]
	mov	w0, 1
	strb	w0, [x19, 837]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP4_Check_StreamType, .-MP4_Check_StreamType
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Clean_HeadPacket
	.type	MP4_Clean_HeadPacket, %function
MP4_Clean_HeadPacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 20480
	bl	_mcount
	mov	w1, 64
	ldr	w0, [x22, 2124]
	ldr	w21, [x22, 2848]
	cmp	w0, w1
	csel	w0, w0, w1, le
	cmp	w0, wzr
	ble	.L620
	sub	w0, w0, #1
	add	x19, x22, 1868
	add	x0, x0, 4096
	add	x0, x0, 1492
	add	x20, x20, x0, lsl 2
	.p2align 2
.L619:
	ldr	w1, [x19], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x20
	bne	.L619
.L620:
	ldr	x3, .LC111
	mov	x2, 456
	mov	w1, 0
	add	x0, x22, 1688
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP4_Clean_HeadPacket, .-MP4_Clean_HeadPacket
	.align	3
.LC111:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_VDMPostProc
	.type	MPEG4DEC_VDMPostProc, %function
MPEG4DEC_VDMPostProc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	w25, w1
	add	x20, x22, 20480
	bl	_mcount
	add	x24, x22, 16384
	ldr	x4, [x22, 1040]
	mov	x2, 14680
	ldr	x5, .LC112
	mov	w1, 0
	add	x0, x22, 1048
	ldrb	w6, [x4, 167]
	strb	w6, [x20, 844]
	ldr	x5, [x5, 96]
	ldr	w4, [x4, 14672]
	str	w4, [x20, 848]
	blr	x5
	ldr	w23, [x20, 2848]
	ldr	w0, [x24, 3620]
	cmp	w0, wzr
	ble	.L628
	sub	w21, w0, #1
	add	x19, x22, 12288
	add	x21, x21, 3978
	add	x19, x19, 3620
	add	x21, x22, x21, lsl 2
	.p2align 2
.L627:
	ldr	w1, [x19], 4
	mov	w0, w23
	bl	SM_ReleaseStreamSeg
	cmp	x21, x19
	bne	.L627
.L628:
	mov	x0, x22
	str	wzr, [x24, 3620]
	bl	MP4_Clean_HeadPacket
	str	w25, [x20, 2152]
	ldr	w1, [x20, 2876]
	ldr	w0, [x20, 2848]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	ldr	w1, [x20, 2868]
	ldr	w0, [x20, 2848]
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	cbz	x24, .L679
	ldr	x1, .LC116
	mov	w0, 11
	ldr	w2, [x20, 2160]
	add	x21, x20, 2192
	mov	x19, 0
	bl	dprint_vfmw
	ldrb	w2, [x20, 1480]
	mov	w0, 11
	ldr	x1, .LC118
	bl	dprint_vfmw
	ldr	w0, [x20, 2152]
	str	w0, [x24, 152]
	ldr	w23, [x20, 2848]
.L630:
	ldr	x1, [x21, x19]
	mov	w0, w23
	bl	FreeUsdByDec
	str	xzr, [x21, x19]
	add	x19, x19, 8
	cmp	x19, 32
	bne	.L630
	ldrb	w0, [x20, 1480]
	cmp	w0, 2
	beq	.L631
	ldr	x1, [x22, 22120]
	ldr	w0, [x20, 2152]
	ldr	w2, [x1]
	cmp	w0, w2
	bhi	.L680
.L631:
	mov	x0, x22
	str	wzr, [x20, 2232]
	bl	MP4_SetImgFormat
	ldr	x0, [x22, 22120]
	ldr	w0, [x0, 24]
	cbz	w0, .L681
	ldr	w1, [x20, 2876]
	ldrb	w19, [x20, 1480]
	ldr	w23, [x20, 1572]
	str	w1, [x20, 2880]
.L637:
	cmn	w1, #1
	beq	.L639
	ldr	w0, [x20, 2848]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L682
	cmp	w19, 4
	ccmp	w23, wzr, 0, eq
	beq	.L683
	ldr	w2, [x0, 152]
	cbz	w2, .L642
	ldr	x0, [x22, 22120]
	ldr	w3, [x0, 4]
	cmp	w2, w3
	bhi	.L643
.L642:
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2880]
	bl	FSP_GetLogicFs
	cbz	x0, .L676
	cmp	w19, 2
	beq	.L645
	ldrsb	w0, [x0, 1]
	cmp	w0, 2
	beq	.L645
	ldr	x1, .LC124
	mov	w0, 11
	ldr	w2, [x20, 2880]
	bl	dprint_vfmw
	.p2align 2
.L639:
	ldr	w1, [x20, 2160]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x20, 2160]
.L675:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L681:
	ldrb	w19, [x20, 1480]
	cmp	w19, 2
	beq	.L635
	ldr	w0, [x20, 2856]
	cmp	w0, 1
	ble	.L636
	ldr	w1, [x20, 2860]
	str	w1, [x20, 2880]
	ldr	w23, [x20, 2864]
	ldrb	w19, [x22]
	b	.L637
	.p2align 3
.L643:
	ldr	x0, .LC119
	ldr	x4, [x0]
	cbz	x4, .L648
	ldr	w0, [x20, 2848]
	mov	w1, 104
	stp	w2, w3, [x29, 88]
	mov	w3, 8
	add	x2, x29, 88
	blr	x4
	ldr	x0, [x22, 22120]
	ldr	w2, [x21, 152]
	ldr	w3, [x0, 4]
.L648:
	ldr	x1, .LC126
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 2848]
	ldr	x1, [x21, 544]
	bl	FreeUsdByDec
	str	xzr, [x21, 544]
	ldr	x1, [x21, 552]
	ldr	w0, [x20, 2848]
	bl	FreeUsdByDec
	str	xzr, [x21, 552]
	mov	w2, 0
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2880]
	bl	FSP_SetDisplay
	b	.L639
	.p2align 3
.L645:
	ldr	w0, [x20, 2848]
	mov	w2, 1
	ldr	w1, [x20, 2880]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 2848]
	mov	x4, x21
	add	x3, x20, 2240
	mov	x2, x22
	mov	w1, 2
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L639
.L676:
	ldr	w0, [x20, 2848]
	ldr	x1, [x21, 544]
.L677:
	bl	FreeUsdByDec
	str	xzr, [x21, 544]
	ldr	x1, [x21, 552]
	ldr	w0, [x20, 2848]
	bl	FreeUsdByDec
	str	xzr, [x21, 552]
	mov	w2, 0
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2880]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L675
	.p2align 3
.L635:
	ldr	w1, [x20, 2876]
	str	w1, [x20, 2880]
	ldr	w23, [x20, 1572]
	cbz	x25, .L637
	ldr	x0, [x24, 584]
	ldr	x2, [x25, 584]
	cmp	x2, x0
	bge	.L637
	str	x2, [x24, 584]
	str	x0, [x25, 584]
	ldr	w1, [x20, 2880]
	b	.L637
.L636:
	mov	w0, -1
	str	w0, [x20, 2880]
	b	.L639
.L680:
	ldr	x2, .LC119
	ldr	x4, [x2]
	cbz	x4, .L632
	str	w0, [x29, 88]
	mov	w3, 8
	ldr	w0, [x20, 2848]
	add	x2, x29, 88
	ldr	w5, [x1]
	mov	w1, 104
	str	w5, [x29, 92]
	blr	x4
.L632:
	ldr	w0, [x20, 2848]
	mov	w21, 1
	ldr	w1, [x20, 2868]
	str	w21, [x20, 2232]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L633
	ldr	w0, [x20, 2848]
	ldr	x1, [x19, 544]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2848]
	ldr	x1, [x19, 552]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2848]
	ldr	x1, [x19, 560]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2848]
	ldr	x1, [x19, 568]
	bl	FreeUsdByDec
	add	x0, x19, 512
	mov	w2, w21
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x20, 2848]
	ldr	w1, [x20, 2868]
	bl	FSP_ClearLogicFs
	ldr	w0, [x20, 2848]
	mov	w2, w21
	ldr	w1, [x20, 2860]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 2860]
	ldr	w0, [x20, 2848]
	str	wzr, [x20, 2868]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 2860]
	str	w0, [x20, 2868]
.L633:
	mov	w0, -1
	str	wzr, [x20, 2856]
	b	.L675
.L683:
	ldr	w1, [x20, 2848]
	ldr	x2, .LC122
	mov	w0, w1
	sxtw	x1, w1
	lsl	x3, x1, 4
	add	x1, x3, x1, lsl 2
	add	x2, x2, x1, lsl 4
	sub	x1, x2, x1
	ldr	w2, [x1, 16]
	add	w2, w2, 1
	str	w2, [x1, 16]
	ldr	x1, [x21, 544]
	b	.L677
.L679:
	ldr	x1, .LC114
	mov	x3, x0
	mov	x2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L675
.L682:
	ldr	x1, .LC121
	mov	w2, 4237
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L675
	.size	MPEG4DEC_VDMPostProc, .-MPEG4DEC_VDMPostProc
	.align	3
.LC112:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC119:
	.xword	g_event_report
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC122:
	.xword	g_VfmwChanStat
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC126:
	.xword	.LC125
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Record_SlcSegID
	.type	MP4_Record_SlcSegID, %function
MP4_Record_SlcSegID:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 16384
	bl	_mcount
	ldr	w0, [x22, 3620]
	cmp	w0, 1022
	bhi	.L691
	add	x1, x20, x0, uxtw 2
	ldr	w4, [x20, 15752]
	add	x3, x20, 12288
	add	w2, w0, 1
	str	w4, [x1, 15908]
	str	w2, [x22, 3620]
	ldrb	w1, [x3, 3450]
	cbnz	w1, .L684
	ldrb	w1, [x3, 3538]
	cmp	w1, 1
	beq	.L692
.L684:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L691:
	mov	x0, x20
	add	x23, x20, 20480
	bl	MP4_Clean_HeadPacket
	ldr	w1, [x22, 3620]
	ldr	w21, [x23, 2848]
	cmp	w1, wzr
	ble	.L689
	sub	w1, w1, #1
	add	x24, x20, 12288
	add	x1, x1, 3978
	add	x19, x24, 3620
	add	x20, x20, x1, lsl 2
	.p2align 2
.L687:
	ldr	w1, [x19], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x20
	bne	.L687
	ldr	w0, [x23, 2848]
.L686:
	add	x1, x24, 3440
	str	wzr, [x22, 3620]
	bl	MP4_ClearCurPacket
	ldr	w2, [x22, 3620]
	mov	w3, 1022
	ldr	x1, .LC128
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L692:
	add	x2, x20, x2, uxtw 2
	ldr	w1, [x20, 15840]
	add	w0, w0, 2
	str	w1, [x2, 15908]
	str	w0, [x22, 3620]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L689:
	mov	w0, w21
	add	x24, x20, 12288
	b	.L686
	.size	MP4_Record_SlcSegID, .-MP4_Record_SlcSegID
	.align	3
.LC128:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_ShortHeader
	.type	Mp4_Syntax_ShortHeader, %function
Mp4_Syntax_ShortHeader:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x20, x1
	bl	_mcount
	ldr	w2, [x21, 15632]
	cbnz	w2, .L734
.L694:
	mov	x1, x20
	mov	w2, w19
	add	x0, x29, 72
	add	x20, x21, 20480
	bl	BsInit
	ldr	x3, .LC131
	mov	x2, 60
	mov	w1, 0
	add	x0, x20, 768
	ldr	x3, [x3, 96]
	blr	x3
	mov	w1, 22
	add	x0, x29, 72
	bl	BsSkip
	mov	w1, 13
	add	x0, x29, 72
	bl	BsSkip
	mov	w1, 3
	add	x0, x29, 72
	bl	BsGet
	uxtb	w0, w0
	sub	w1, w0, #1
	strb	w0, [x20, 778]
	cmp	w1, 3
	bls	.L735
	strb	wzr, [x20, 1609]
	add	x0, x29, 72
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC133
	ldr	x4, [x0]
	cbz	x4, .L719
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L735:
	ldr	x0, .LC132
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx697
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx697:
	.section	.rodata
	.align	0
	.align	2
.L697:
	.byte	(.L696 - .Lrtx697) / 4
	.byte	(.L698 - .Lrtx697) / 4
	.byte	(.L699 - .Lrtx697) / 4
	.byte	(.L700 - .Lrtx697) / 4
	.text
	.p2align 3
.L699:
	mov	w3, 18
	mov	w2, 22
	mov	w1, 352
	mov	w0, 288
	strb	w3, [x20, 779]
	strb	w2, [x20, 780]
	str	w0, [x20, 1540]
	str	w1, [x20, 1544]
.L701:
	mov	w1, 1
	add	x0, x29, 72
	bl	BsGet
	uxtb	w0, w0
	ldrb	w1, [x20, 835]
	strb	w0, [x20, 768]
	cmp	w1, 2
	beq	.L703
	ldr	w1, [x20, 2232]
	cmp	w1, 1
	ccmp	w0, wzr, 4, eq
	bne	.L703
	mov	w1, 4
	add	x0, x29, 72
	bl	BsSkip
	mov	w1, 5
	add	x0, x29, 72
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L733
	mov	w0, 1
.L733:
	strb	w0, [x20, 775]
	mov	w1, 1
	add	x0, x29, 72
	lsl	w22, w19, 3
	mov	w19, 0
	bl	BsSkip
.L709:
	mov	w1, 1
	add	x0, x29, 72
	bl	BsGet
	cmp	w0, 1
	beq	.L736
	add	w19, w19, 1
	cmp	w19, 15
	bls	.L710
.L732:
	strb	wzr, [x20, 1609]
	add	x0, x29, 72
	bl	BsPos
	mov	w19, w0
	ldr	x0, .LC133
	ldr	x4, [x0]
	cbz	x4, .L719
	ldr	w0, [x20, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L698:
	mov	w3, 9
	mov	w2, 11
	mov	w1, 176
	mov	w0, 144
	strb	w3, [x20, 779]
	strb	w2, [x20, 780]
	str	w0, [x20, 1540]
	str	w1, [x20, 1544]
	b	.L701
	.p2align 3
.L696:
	mov	w3, 6
	mov	w2, 8
	mov	w1, 128
	mov	w0, 96
	strb	w3, [x20, 779]
	strb	w2, [x20, 780]
	str	w0, [x20, 1540]
	str	w1, [x20, 1544]
	b	.L701
	.p2align 3
.L700:
	mov	w3, 18
	mov	w2, 88
	mov	w1, 704
	mov	w0, 576
	strb	w3, [x20, 779]
	strb	w2, [x20, 780]
	str	w0, [x20, 1540]
	str	w1, [x20, 1544]
	b	.L701
	.p2align 3
.L736:
	add	x0, x29, 72
	add	w19, w19, 1
	bl	BsPos
	cmp	w0, w22
	mov	w1, 8
	add	x0, x29, 72
	bgt	.L737
	bl	BsSkip
	cmp	w19, 15
	bls	.L709
	b	.L732
	.p2align 3
.L734:
	ldr	x1, .LC130
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x21, 15632]
	b	.L694
	.p2align 3
.L710:
	add	x24, x21, 16384
	mov	w2, 1
	strb	w2, [x20, 1609]
	add	x0, x29, 72
	add	x19, x21, 12288
	ldr	w1, [x24, 3624]
	orr	w1, w1, 2
	str	w1, [x24, 3624]
	ldr	w1, [x21, 15632]
	add	w1, w1, 1
	str	w1, [x21, 15632]
	strb	w2, [x20, 776]
	bl	BsPos
	mov	w23, w0
	asr	w0, w0, 31
	sub	w22, w22, w23
	lsr	w0, w0, 29
	str	w22, [x21, 1304]
	add	w1, w23, w0
	add	w2, w23, 7
	ldr	w3, [x20, 1632]
	and	w1, w1, 7
	sub	w0, w1, w0
	cmp	w23, wzr
	add	w0, w3, w0
	strb	w0, [x21, 1302]
	csel	w0, w2, w23, lt
	ldr	w1, [x20, 1624]
	add	w0, w1, w0, asr 3
	str	w0, [x21, 1312]
	ldrb	w0, [x19, 3450]
	cbz	w0, .L738
.L711:
	strb	wzr, [x21, 1303]
	str	wzr, [x21, 1308]
	str	wzr, [x21, 1316]
.L712:
	ldrb	w0, [x20, 768]
	strb	w0, [x21, 1300]
	ldrb	w0, [x20, 777]
	strb	w0, [x21, 1298]
	ldrb	w0, [x20, 776]
	strb	w0, [x21, 1297]
	ldrb	w0, [x20, 775]
	strb	w0, [x21, 1301]
	ldrb	w0, [x20, 772]
	strb	w0, [x21, 1299]
	ldr	w2, [x24, 3620]
	cbnz	w2, .L739
.L713:
	mov	x0, x21
	bl	MP4_Record_SlcSegID
	mov	w0, w23
.L731:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L703:
	add	x0, x29, 72
	bl	BsPos
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L738:
	ldrb	w0, [x19, 3538]
	cmp	w0, 1
	bne	.L711
	ldr	w0, [x21, 15836]
	ldr	w1, [x21, 15832]
	lsl	w0, w0, 3
	strb	wzr, [x21, 1303]
	str	w0, [x21, 1308]
	str	w1, [x21, 1316]
	b	.L712
	.p2align 3
.L719:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
.L739:
	ldr	x1, .LC135
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w22, [x20, 2848]
	ldr	w0, [x24, 3620]
	cmp	w0, wzr
	ble	.L716
	sub	w20, w0, #1
	add	x19, x19, 3620
	add	x20, x20, 3978
	add	x20, x21, x20, lsl 2
	.p2align 2
.L715:
	ldr	w1, [x19], 4
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	cmp	x19, x20
	bne	.L715
.L716:
	str	wzr, [x24, 3620]
	b	.L713
.L737:
	bl	BsPos
	b	.L731
	.size	Mp4_Syntax_ShortHeader, .-Mp4_Syntax_ShortHeader
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC131:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC132:
	.xword	.L697
	.align	3
.LC133:
	.xword	g_event_report
	.align	3
.LC135:
	.xword	.LC134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Vop
	.type	Mp4_Syntax_Vop, %function
Mp4_Syntax_Vop:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	x22, x1
	bl	_mcount
	ldr	w2, [x20, 15632]
	cbnz	w2, .L825
	add	x19, x20, 20480
	ldrb	w0, [x19, 829]
	cbnz	w0, .L742
.L826:
	strb	wzr, [x19, 1609]
	mov	w0, 32
.L743:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L825:
	ldr	x1, .LC136
	mov	w0, 1
	add	x19, x20, 20480
	bl	dprint_vfmw
	str	wzr, [x20, 15632]
	ldrb	w0, [x19, 829]
	cbz	w0, .L826
.L742:
	mov	x1, x22
	mov	w2, w21
	add	x0, x29, 120
	add	x22, x19, 768
	bl	BsInit
	ldr	x23, .LC137
	mov	x2, 60
	mov	w1, 0
	mov	x0, x22
	ldr	x3, [x23, 96]
	blr	x3
	strb	wzr, [x19, 1609]
	mov	w1, 32
	add	x0, x29, 120
	bl	BsSkip
	mov	w1, 2
	add	x0, x29, 120
	bl	BsGet
	strb	w0, [x19, 768]
	ldr	x1, .LC139
	uxtb	w2, w0
	mov	w0, 18
	bl	dprint_vfmw
	ldrb	w0, [x19, 768]
	cmp	w0, 3
	beq	.L827
.L744:
	ldrb	w1, [x19, 835]
	cmp	w0, wzr
	cset	w0, ne
	cmp	w1, 1
	cset	w2, eq
	tst	w0, w2
	bne	.L747
	cmp	w1, 2
	beq	.L747
	ldr	w1, [x19, 2232]
	cmp	w1, 1
	cset	w1, eq
	tst	w0, w1
	bne	.L747
	lsl	w21, w21, 3
	mov	w24, 0
	mov	w25, 6400
	b	.L750
	.p2align 3
.L829:
	add	x0, x29, 120
	add	w24, w24, 1
	bl	BsPos
	cmp	w0, w21
	bgt	.L828
	cmp	w24, w25
	beq	.L751
.L750:
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	cbnz	w0, .L829
	mov	w0, 6399
	cmp	w24, w0
	bhi	.L751
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	cbz	w0, .L824
	ldr	w1, [x19, 944]
	mov	w0, 0
	cbnz	w1, .L830
.L754:
	str	w0, [x19, 1552]
	mov	w1, 1
	str	w24, [x19, 1548]
	add	x0, x29, 120
	bl	BsGet
	cbz	w0, .L824
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 769]
	cbz	w0, .L831
	ldrb	w0, [x19, 768]
	cmp	w0, 1
	beq	.L757
	cmp	w0, 3
	beq	.L832
.L758:
	strb	wzr, [x19, 770]
.L759:
	ldrb	w0, [x19, 884]
	add	x24, x20, 16384
	strb	wzr, [x19, 771]
	cmp	w0, 2
	beq	.L760
	mov	w1, 3
	add	x0, x29, 120
	add	x24, x20, 16384
	bl	BsGet
	strb	w0, [x19, 772]
	ldrb	w0, [x24, 3666]
	cbnz	w0, .L833
	mov	w0, 2
	strb	wzr, [x19, 774]
	strb	w0, [x19, 773]
.L762:
	ldrb	w0, [x19, 888]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L763
.L766:
	mov	w1, 5
	add	x0, x29, 120
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L821
	mov	w0, 1
.L821:
	strb	w0, [x19, 775]
	ldrb	w0, [x19, 768]
	cbnz	w0, .L834
.L760:
	mov	w0, 1
	strb	w0, [x19, 1609]
	ldr	x4, [x23, 104]
	mov	x1, x22
	ldr	w3, [x24, 3624]
	mov	x2, 60
	add	x0, x19, 1480
	add	x23, x20, 12288
	orr	w3, w3, 2
	str	w3, [x24, 3624]
	ldr	w3, [x20, 15632]
	add	w3, w3, 1
	str	w3, [x20, 15632]
	blr	x4
	add	x0, x29, 120
	bl	BsPos
	mov	w22, w0
	asr	w0, w0, 31
	sub	w21, w21, w22
	lsr	w0, w0, 29
	str	w21, [x20, 1304]
	add	w1, w22, w0
	add	w2, w22, 7
	ldr	w3, [x19, 1632]
	and	w1, w1, 7
	sub	w0, w1, w0
	cmp	w22, wzr
	add	w0, w3, w0
	strb	w0, [x20, 1302]
	csel	w0, w2, w22, lt
	ldr	w1, [x19, 1624]
	add	w0, w1, w0, asr 3
	str	w0, [x20, 1312]
	ldrb	w0, [x23, 3450]
	cbnz	w0, .L774
	ldrb	w0, [x23, 3538]
	cmp	w0, 1
	beq	.L835
.L774:
	strb	wzr, [x20, 1303]
	str	wzr, [x20, 1308]
	str	wzr, [x20, 1316]
.L775:
	ldrb	w0, [x19, 768]
	strb	w0, [x20, 1300]
	ldrb	w0, [x19, 777]
	strb	w0, [x20, 1298]
	ldrb	w0, [x19, 776]
	strb	w0, [x20, 1297]
	ldrb	w0, [x19, 775]
	strb	w0, [x20, 1301]
	ldrb	w0, [x19, 772]
	strb	w0, [x20, 1299]
	ldr	w2, [x24, 3620]
	cbnz	w2, .L836
.L776:
	mov	x0, x20
	bl	MP4_Record_SlcSegID
	mov	w0, w22
	b	.L743
	.p2align 3
.L751:
	strb	wzr, [x19, 1609]
	add	x0, x29, 120
	bl	BsPos
	mov	w19, w0
	ldr	x1, .LC147
	mov	w2, w24
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L743
.L832:
	ldrb	w0, [x19, 888]
	cmp	w0, 2
	bne	.L758
.L757:
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	strb	w0, [x19, 770]
	b	.L759
	.p2align 3
.L828:
	add	x0, x29, 120
	bl	BsPos
	mov	w19, w0
	ldr	x1, .LC145
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L743
	.p2align 3
.L827:
	ldr	x1, .LC140
	ldr	w1, [x1]
	tbnz	x1, 3, .L744
	strb	wzr, [x19, 1609]
	add	x0, x29, 120
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L745
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
.L745:
	ldr	x1, .LC143
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
	b	.L743
	.p2align 3
.L747:
	add	x0, x29, 120
	bl	BsPos
	b	.L743
	.p2align 3
.L824:
	ldr	x1, .LC148
	mov	w0, 1
	bl	dprint_vfmw
	strb	wzr, [x19, 1609]
	add	x0, x29, 120
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L782
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
	mov	w0, w20
	b	.L743
.L830:
	add	x0, x29, 120
	bl	BsGet
	b	.L754
.L782:
	mov	w0, w20
	b	.L743
.L836:
	ldr	x1, .LC153
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w25, [x19, 2848]
	ldr	w0, [x24, 3620]
	cmp	w0, wzr
	ble	.L779
	sub	w21, w0, #1
	add	x19, x23, 3620
	add	x21, x21, 3978
	add	x21, x20, x21, lsl 2
	.p2align 2
.L778:
	ldr	w1, [x19], 4
	mov	w0, w25
	bl	SM_ReleaseStreamSeg
	cmp	x21, x19
	bne	.L778
.L779:
	str	wzr, [x24, 3620]
	b	.L776
.L831:
	add	x20, x20, 16384
	mov	w0, 4
	mov	w1, 1
	strb	w0, [x19, 768]
	strb	w0, [x19, 1480]
	add	x0, x29, 120
	strb	w1, [x19, 1609]
	ldr	w1, [x20, 3624]
	orr	w1, w1, 128
	str	w1, [x20, 3624]
	bl	BsPos
	b	.L743
.L833:
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	strb	w0, [x19, 773]
	mov	w1, 1
	add	x0, x29, 120
	bl	BsGet
	strb	w0, [x19, 774]
	b	.L762
.L834:
	mov	w1, 3
	add	x0, x29, 120
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 776]
	cbz	w0, .L837
	ldrb	w0, [x19, 768]
	cmp	w0, 2
	bne	.L760
	mov	w1, 3
	add	x0, x29, 120
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 777]
	cbnz	w0, .L760
	strb	wzr, [x19, 1609]
	add	x0, x29, 120
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L773
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
.L773:
	ldr	x1, .LC152
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
	b	.L743
.L763:
	ldrb	w0, [x19, 768]
	cmp	w0, 3
	bne	.L766
	ldrb	w0, [x19, 900]
	cbz	w0, .L766
	mov	x28, 500
	mov	w25, 0
	movk	x28, 0x19d, lsl 32
	b	.L770
.L767:
	ldr	x0, [x20, 22064]
	mov	w1, 1
	cmp	x0, x28
	beq	.L768
	add	x0, x29, 120
	bl	BsSkip
.L768:
	add	x0, x29, 120
	bl	bs_get_spritetrajectory
	mov	w2, w0
	cbnz	w0, .L838
.L769:
	mov	w1, 1
	add	x0, x29, 120
	bl	BsSkip
	add	x0, x20, x25, uxtw 3
	add	w25, w25, 1
	add	x0, x0, 20480
	str	w27, [x0, 804]
	str	w26, [x0, 808]
	ldrb	w0, [x19, 900]
	cmp	w0, w25
	bls	.L766
.L770:
	add	x0, x29, 120
	mov	w27, 0
	mov	w26, 0
	bl	bs_get_spritetrajectory
	mov	w2, w0
	cbz	w0, .L767
	mov	w1, w0
	add	x0, x29, 120
	str	w2, [x29, 108]
	bl	BsGet
	mov	w27, w0
	ldr	w2, [x29, 108]
	mov	w0, 1
	lsl	w1, w0, w2
	sub	w0, w2, #1
	asr	w0, w27, w0
	sub	w1, w1, #1
	eor	w1, w1, w27
	cbnz	w0, .L767
	neg	w27, w1
	b	.L767
.L838:
	mov	w1, w0
	add	x0, x29, 120
	str	w2, [x29, 108]
	bl	BsGet
	mov	w26, w0
	ldr	w2, [x29, 108]
	mov	w0, 1
	lsl	w1, w0, w2
	sub	w0, w2, #1
	asr	w0, w26, w0
	sub	w1, w1, #1
	eor	w1, w1, w26
	cbnz	w0, .L769
	neg	w26, w1
	b	.L769
.L835:
	ldr	w0, [x20, 15836]
	ldr	w1, [x20, 15832]
	lsl	w0, w0, 3
	strb	wzr, [x20, 1303]
	str	w0, [x20, 1308]
	str	w1, [x20, 1316]
	b	.L775
.L837:
	strb	wzr, [x19, 1609]
	add	x0, x29, 120
	bl	BsPos
	mov	w20, w0
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L772
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
.L772:
	ldrb	w2, [x19, 768]
	mov	w0, 1
	ldr	x1, .LC150
	bl	dprint_vfmw
	mov	w0, w20
	b	.L743
	.size	Mp4_Syntax_Vop, .-Mp4_Syntax_Vop
	.align	3
.LC136:
	.xword	.LC129
	.align	3
.LC137:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC140:
	.xword	g_VdmCharacter
	.align	3
.LC141:
	.xword	g_event_report
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
.LC148:
	.xword	.LC36
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC153:
	.xword	.LC134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Slice_NotSH
	.type	Mp4_Syntax_Slice_NotSH, %function
Mp4_Syntax_Slice_NotSH:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	w21, w2
	bl	_mcount
	ldr	w19, [x20, 15632]
	sub	w0, w19, #1
	cmp	w0, 510
	bls	.L840
	add	x21, x20, 20480
	add	x19, x20, 12288
	add	x23, x20, 16384
	add	x1, x19, 3440
	ldr	w0, [x21, 2848]
	bl	MP4_ClearCurPacket
	ldr	w22, [x21, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L844
	sub	w21, w0, #1
	add	x19, x19, 3620
	add	x21, x21, 3978
	add	x21, x20, x21, lsl 2
	.p2align 2
.L843:
	ldr	w1, [x19], 4
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	cmp	x19, x21
	bne	.L843
.L844:
	ldr	w1, [x23, 3624]
	mov	w0, -435
	str	wzr, [x23, 3620]
	and	w0, w1, w0
	str	w0, [x23, 3624]
	ldr	x2, .LC154
	mov	w0, 1
	ldr	x1, .LC156
	ldr	w3, [x20, 15632]
	add	x2, x2, 1296
	bl	dprint_vfmw
	mov	w0, 0
.L863:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L840:
	add	x25, x20, 12288
	add	w0, w19, 1
	str	w0, [x20, 15632]
	mov	x1, x22
	mov	w2, w21
	add	x0, x29, 88
	ldrh	w22, [x25, 3616]
	add	x24, x20, 20480
	bl	BsInit
	ubfx	x22, x22, 7, 4
	add	x0, x29, 88
	add	w22, w22, 17
	mov	w1, w22
	bl	BsSkip
	ldr	w22, [x24, 1540]
	ldr	w0, [x24, 1544]
	add	w22, w22, 15
	add	w0, w0, 15
	lsr	w22, w22, 4
	lsr	w0, w0, 4
	mul	w22, w0, w22
	cbz	w22, .L845
	mov	w0, w22
	mov	w1, 0
	.p2align 2
.L846:
	add	w1, w1, 1
	lsr	w0, w0, 1
	sxth	w1, w1
	cbnz	w0, .L846
	add	x0, x29, 88
	uxtw	x19, w19
	bl	BsGet
	lsl	x1, x19, 3
	sub	w3, w22, #1
	sub	x1, x1, x19
	cmp	w0, w3
	add	x1, x20, x1, lsl 2
	str	w0, [x1, 1320]
	bhi	.L864
.L847:
	lsl	x22, x19, 3
	mov	w1, 5
	sub	x22, x22, x19
	add	x0, x29, 88
	add	x22, x20, x22, lsl 2
	bl	BsGet
	mov	w1, 1
	strb	w0, [x22, 1301]
	add	x0, x29, 88
	bl	BsGet
	cbz	w0, .L848
	lsl	w21, w21, 3
	.p2align 2
.L849:
	mov	w1, 1
	add	x0, x29, 88
	bl	BsGet
	mov	w22, w0
	add	x0, x29, 88
	bl	BsPos
	cmp	w22, wzr
	ccmp	w0, w21, 0, ne
	blt	.L849
	mov	w1, 1
	add	x23, x20, 16384
	add	x0, x29, 88
	bl	BsSkip
	ldr	w1, [x23, 3724]
	cbnz	w1, .L865
.L850:
	mov	w1, 1
	add	x0, x29, 88
	lsl	x22, x19, 3
	sub	x22, x22, x19
	bl	BsSkip
	mov	w1, 2
	add	x0, x29, 88
	add	x22, x20, x22, lsl 2
	bl	BsGet
	mov	w1, 3
	strb	w0, [x22, 1300]
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x22, 1299]
	ldrb	w1, [x22, 1300]
	cbnz	w1, .L866
.L851:
	lsl	x22, x19, 3
	ldrb	w1, [x24, 776]
	sub	x22, x22, x19
	add	x0, x29, 88
	add	x22, x20, x22, lsl 2
	strb	w1, [x22, 1297]
	ldrb	w1, [x24, 777]
	strb	w1, [x22, 1298]
	ldr	w1, [x23, 3624]
	orr	w1, w1, 16
	str	w1, [x23, 3624]
	bl	BsPos
	mov	w23, w0
	asr	w0, w0, 31
	sub	w21, w21, w23
	lsr	w0, w0, 29
	str	w21, [x22, 1304]
	add	w1, w23, w0
	add	w2, w23, 7
	ldr	w3, [x24, 1632]
	and	w1, w1, 7
	sub	w0, w1, w0
	cmp	w23, wzr
	add	w0, w3, w0
	strb	w0, [x22, 1302]
	csel	w0, w2, w23, lt
	ldr	w1, [x24, 1624]
	add	w0, w1, w0, asr 3
	str	w0, [x22, 1312]
	ldrb	w0, [x25, 3450]
	cbnz	w0, .L852
	ldrb	w0, [x25, 3538]
	cmp	w0, 1
	beq	.L867
.L852:
	lsl	x0, x19, 3
	sub	x19, x0, x19
	add	x19, x20, x19, lsl 2
	strb	wzr, [x19, 1303]
	str	wzr, [x19, 1308]
	str	wzr, [x19, 1316]
.L853:
	mov	x0, x20
	bl	MP4_Record_SlcSegID
	ldr	x25, [sp, 64]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L848:
	ldrb	w0, [x24, 768]
	lsl	w21, w21, 3
	strb	w0, [x22, 1300]
	add	x23, x20, 16384
	ldrb	w0, [x24, 772]
	strb	w0, [x22, 1299]
	b	.L851
	.p2align 3
.L866:
	mov	w1, 3
	add	x0, x29, 88
	bl	BsSkip
	ldrb	w0, [x22, 1300]
	cmp	w0, 2
	bne	.L851
	mov	w1, 3
	add	x0, x29, 88
	bl	BsSkip
	b	.L851
	.p2align 3
.L865:
	add	x0, x29, 88
	bl	BsSkip
	b	.L850
	.p2align 3
.L867:
	ldr	w0, [x20, 15836]
	strb	wzr, [x22, 1303]
	lsl	w0, w0, 3
	str	w0, [x22, 1308]
	ldr	w0, [x20, 15832]
	str	w0, [x22, 1316]
	b	.L853
.L845:
	mov	w1, 0
	add	x0, x29, 88
	uxtw	x19, w19
	bl	BsGet
	lsl	x1, x19, 3
	sub	x1, x1, x19
	add	x1, x20, x1, lsl 2
	str	w0, [x1, 1320]
	b	.L847
.L864:
	ldr	x1, .LC158
	mov	w2, w0
	mov	w3, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L863
	.size	Mp4_Syntax_Slice_NotSH, .-Mp4_Syntax_Slice_NotSH
	.align	3
.LC154:
	.xword	.LANCHOR1
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Slice_SH
	.type	Mp4_Syntax_Slice_SH, %function
Mp4_Syntax_Slice_SH:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	w22, w2
	bl	_mcount
	ldr	w3, [x20, 15632]
	sub	w26, w3, #1
	cmp	w26, 510
	bls	.L869
	add	x21, x20, 20480
	add	x19, x20, 12288
	add	x23, x20, 16384
	add	x1, x19, 3440
	ldr	w0, [x21, 2848]
	bl	MP4_ClearCurPacket
	ldr	w22, [x21, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L873
	sub	w21, w0, #1
	add	x19, x19, 3620
	add	x21, x21, 3978
	add	x21, x20, x21, lsl 2
	.p2align 2
.L872:
	ldr	w1, [x19], 4
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	cmp	x19, x21
	bne	.L872
.L873:
	ldr	w1, [x23, 3624]
	mov	w0, -435
	str	wzr, [x23, 3620]
	and	w0, w1, w0
	str	w0, [x23, 3624]
	ldr	x2, .LC159
	mov	w0, 1
	ldr	x1, .LC160
	ldr	w3, [x20, 15632]
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, 0
.L871:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L869:
	add	x24, x20, 12288
	add	w0, w3, 1
	str	w0, [x20, 15632]
	mov	x1, x19
	mov	w2, w22
	add	x0, x29, 88
	ldrb	w19, [x24, 3616]
	uxtw	x25, w3
	bl	BsInit
	add	x23, x20, 20480
	ubfx	x19, x19, 3, 4
	add	x0, x29, 88
	add	w19, w19, 17
	mov	w1, w19
	lsl	x19, x25, 3
	sub	x19, x19, x25
	bl	BsSkip
	mov	w1, 5
	add	x0, x29, 88
	add	x19, x20, x19, lsl 2
	bl	BsGet
	ldrb	w2, [x23, 780]
	mul	w0, w2, w0
	str	w0, [x19, 1320]
	ldrh	w1, [x20, 1226]
	ldrh	w3, [x20, 1224]
	mul	w3, w1, w3
	sub	w3, w3, #1
	cmp	w0, w3
	bhi	.L886
	mov	w1, 2
	add	x0, x29, 88
	lsl	w22, w22, 3
	bl	BsSkip
	mov	w1, 5
	add	x0, x29, 88
	bl	BsGet
	strb	w0, [x19, 1301]
	add	x0, x29, 88
	ldrb	w1, [x23, 768]
	strb	w1, [x19, 1300]
	ldrb	w1, [x23, 772]
	strb	w1, [x19, 1299]
	ldrb	w1, [x23, 776]
	strb	w1, [x19, 1297]
	ldrb	w1, [x23, 777]
	strb	w1, [x19, 1298]
	bl	BsPos
	mov	w21, w0
	asr	w0, w0, 31
	sub	w22, w22, w21
	lsr	w0, w0, 29
	str	w22, [x19, 1304]
	add	w1, w21, w0
	add	w2, w21, 7
	ldr	w3, [x23, 1632]
	and	w1, w1, 7
	sub	w0, w1, w0
	cmp	w21, wzr
	add	w0, w3, w0
	strb	w0, [x19, 1302]
	csel	w0, w2, w21, lt
	add	x1, x20, 16384
	ldr	w2, [x23, 1624]
	add	w0, w2, w0, asr 3
	str	w0, [x19, 1312]
	ldr	w0, [x1, 3624]
	orr	w0, w0, 16
	str	w0, [x1, 3624]
	ldrb	w0, [x24, 3450]
	cbnz	w0, .L875
	ldrb	w0, [x24, 3538]
	cmp	w0, 1
	beq	.L887
.L875:
	lsl	x0, x25, 3
	sub	x0, x0, x25
	add	x0, x20, x0, lsl 2
	strb	wzr, [x0, 1303]
	str	wzr, [x0, 1308]
	str	wzr, [x0, 1316]
.L876:
	uxtw	x0, w26
	lsl	x1, x0, 3
	sub	x1, x1, x0
	add	x1, x20, x1, lsl 2
	ldr	w2, [x1, 1316]
	cbz	w2, .L877
	ldr	w2, [x1, 1308]
	cbnz	w2, .L888
.L877:
	lsl	x1, x0, 3
	ldrb	w2, [x24, 3616]
	sub	x0, x1, x0
	ubfx	x1, x2, 3, 4
	add	x0, x20, x0, lsl 2
	ldr	w2, [x0, 1304]
	add	w1, w2, w1
	str	w1, [x0, 1304]
.L878:
	mov	x0, x20
	bl	MP4_Record_SlcSegID
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L888:
	ldrb	w0, [x24, 3616]
	ubfx	x0, x0, 3, 4
	add	w2, w0, w2
	str	w2, [x1, 1308]
	b	.L878
	.p2align 3
.L887:
	ldr	w0, [x20, 15836]
	strb	wzr, [x19, 1303]
	lsl	w0, w0, 3
	str	w0, [x19, 1308]
	ldr	w0, [x20, 15832]
	str	w0, [x19, 1316]
	b	.L876
.L886:
	ldr	x1, .LC162
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L871
	.size	Mp4_Syntax_Slice_SH, .-Mp4_Syntax_Slice_SH
	.align	3
.LC159:
	.xword	.LANCHOR1
	.align	3
.LC160:
	.xword	.LC155
	.align	3
.LC162:
	.xword	.LC161
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Dec_Slice
	.type	MP4_Dec_Slice, %function
MP4_Dec_Slice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	mov	x22, x1
	mov	w21, w2
	bl	_mcount
	ldrb	w0, [x20, 3616]
	tbz	x0, 0, .L899
	tbz	x0, 2, .L900
.L895:
	mov	w2, w21
	mov	x1, x22
	mov	x0, x19
	bl	Mp4_Syntax_Slice_SH
	cmn	w0, #1
	beq	.L897
.L893:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L900:
	ldrh	w1, [x20, 3616]
	ubfx	x1, x1, 7, 4
	sub	w2, w1, #1
	cmp	w2, 6
	bhi	.L895
	bfi	w0, w1, 3, 4
	mov	w2, w21
	strb	w0, [x20, 3616]
	mov	x1, x22
	mov	x0, x19
	bl	Mp4_Syntax_Slice_SH
	cmn	w0, #1
	bne	.L893
.L897:
	add	x19, x19, 20480
	add	x1, x20, 3440
	ldr	w0, [x19, 2848]
	bl	MP4_ClearCurPacket
	ldr	x2, .LC163
	mov	w0, 1
	ldr	x1, .LC165
	add	x2, x2, 1344
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L899:
	mov	x0, x19
	bl	Mp4_Check_Slice_NotSH
	cbz	w0, .L901
	mov	w1, w21
	mov	x0, x19
	bl	Mp4_Combine_SliceData
	cbnz	w0, .L897
	mov	x0, x19
	bl	MP4_Record_SlcSegID
	b	.L893
	.p2align 3
.L901:
	mov	w2, w21
	mov	x1, x22
	mov	x0, x19
	bl	Mp4_Syntax_Slice_NotSH
	cmn	w0, #1
	beq	.L897
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP4_Dec_Slice, .-MP4_Dec_Slice
	.align	3
.LC163:
	.xword	.LANCHOR1
	.align	3
.LC165:
	.xword	.LC164
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Record_PacketID
	.type	MP4_Record_PacketID, %function
MP4_Record_PacketID:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	bl	_mcount
	ldr	w1, [x20, 2124]
	cmp	w1, 62
	bgt	.L905
	add	x0, x19, x1, sxtw 2
	ldr	w4, [x19, 15752]
	add	x0, x0, 20480
	add	x3, x19, 12288
	add	w2, w1, 1
	str	w4, [x0, 1868]
	str	w2, [x20, 2124]
	ldrb	w2, [x3, 3450]
	cbnz	w2, .L902
	ldrb	w2, [x3, 3538]
	cmp	w2, 1
	beq	.L906
.L902:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L905:
	mov	x0, x19
	bl	MP4_Clean_HeadPacket
	ldr	w0, [x20, 2848]
	add	x1, x19, 12288
	add	x1, x1, 3440
	bl	MP4_ClearCurPacket
	ldr	w2, [x20, 2124]
	mov	w3, 62
	ldr	x1, .LC166
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L906:
	ldr	w2, [x19, 15840]
	add	w1, w1, 2
	str	w2, [x0, 1872]
	str	w1, [x20, 2124]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP4_Record_PacketID, .-MP4_Record_PacketID
	.align	3
.LC166:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Record_HeadPacketInfo
	.type	MP4_Record_HeadPacketInfo, %function
MP4_Record_HeadPacketInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cbz	x21, .L911
	ldr	x22, .LC169
	add	x19, x21, 20480
	add	x20, x21, 12288
	mov	x2, 176
	add	x1, x20, 3440
	add	x0, x19, 1688
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 4
	add	x1, x20, 3616
	add	x0, x19, 1864
	blr	x3
	str	w23, [x19, 2128]
	ldr	w0, [x19, 2132]
	cbz	w0, .L912
.L910:
	ldr	w0, [x19, 2136]
	add	w0, w0, 1
	str	w0, [x19, 2136]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L912:
	mov	x0, x21
	bl	MP4_Record_PacketID
	mov	w0, 1
	str	w0, [x19, 2132]
	b	.L910
	.p2align 3
.L911:
	ldr	x1, .LC168
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	MP4_Record_HeadPacketInfo, .-MP4_Record_HeadPacketInfo
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC169:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mp4_Syntax_Parse
	.type	Mp4_Syntax_Parse, %function
Mp4_Syntax_Parse:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x24, x1
	mov	w25, w2
	bl	_mcount
	ldr	x26, .LC170
	mov	x2, 40
	mov	w1, 0
	add	x0, x29, 112
	add	x23, x22, 16384
	ldr	x3, [x26, 96]
	blr	x3
	mov	w2, w25
	mov	x1, x24
	add	x0, x29, 112
	bl	BsInit
	mov	w1, 32
	add	x0, x29, 112
	bl	BsShow
	str	wzr, [x23, 3628]
	cmp	w0, 510
	mov	w20, w0
	beq	.L1046
	add	x27, x22, 12288
	ldrb	w0, [x27, 3616]
	tbz	x0, 0, .L1047
.L919:
	add	x19, x22, 20480
	mov	w1, 1
	mov	w20, 196
	strb	w1, [x19, 837]
.L920:
	tbnz	x0, 1, .L921
	ldr	w0, [x23, 3624]
	mov	w21, 130
	ands	w21, w0, w21
	bne	.L1048
	cmp	w20, 197
	beq	.L1049
	cmp	w20, 432
	beq	.L1050
	cmp	w20, 437
	beq	.L1051
	and	w0, w20, -16
	cmp	w0, 288
	beq	.L1052
	cmp	w20, 435
	beq	.L1053
	cmp	w20, 438
	beq	.L1054
	cmp	w20, 196
	beq	.L1055
	cmp	w20, 434
	beq	.L1056
	cmp	w20, 286
	bne	.L936
	ldr	x28, .LC171
	ldr	x4, [x28]
	cbz	x4, .L937
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L937:
	ldr	w0, [x19, 2848]
	add	x1, x27, 3440
	add	x21, x24, 4
	sub	w25, w25, #4
	bl	MP4_ClearCurPacket
	ldr	w0, [x23, 3624]
	tbz	x0, 1, .L938
	orr	w0, w0, 256
	str	w0, [x23, 3624]
.L938:
	ldr	w1, [x23, 3624]
	mov	w0, 18
	and	w0, w1, w0
	cmp	w0, 18
	beq	.L939
	ldr	x4, [x28]
	cbz	x4, .L939
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L939:
	ldrb	w0, [x19, 2885]
	mov	w28, 0
	cmp	w0, 1
	beq	.L970
.L945:
	ldrb	w0, [x19, 1607]
	mov	w21, w28
	cmp	w0, 1
	bne	.L1020
	ldr	w0, [x19, 2144]
	mov	x2, 604
	ldr	x3, [x26, 104]
	add	x1, x23, 3656
	add	w0, w0, 1
	str	wzr, [x19, 2148]
	str	w0, [x19, 2144]
	add	x0, x19, 876
	blr	x3
	ldr	w3, [x19, 1540]
	ldr	w1, [x23, 3740]
	ldr	w2, [x23, 3736]
	cmp	w3, w1
	beq	.L1057
.L961:
	ldr	x0, .LC171
	ldr	x4, [x0]
	cbz	x4, .L963
	ldr	w5, [x19, 1544]
	ldr	w0, [x19, 2848]
	strh	w2, [x29, 108]
	add	x2, x29, 104
	strh	w1, [x29, 110]
	mov	w1, 2
	strh	w3, [x29, 106]
	mov	w3, 8
	strh	w5, [x29, 104]
	blr	x4
	ldr	w2, [x23, 3736]
	ldr	w1, [x23, 3740]
.L963:
	str	w1, [x19, 1540]
	str	w2, [x19, 1544]
.L964:
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L966
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x20, 568]
	bl	FreeUsdByDec
	add	x0, x20, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2860]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 2860]
	ldr	w0, [x19, 2848]
	str	wzr, [x19, 2868]
	bl	FSP_GetNullLogicFs
	str	w0, [x19, 2860]
	str	w0, [x19, 2868]
.L966:
	add	x20, x19, 2240
	ldr	w0, [x19, 2848]
	mov	x1, x20
	str	wzr, [x19, 2856]
	bl	FSP_ClearNotInVoQueue
	ldr	x0, [x22, 22120]
	ldr	w1, [x0, 764]
	cbnz	w1, .L967
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1058
.L967:
	ldr	w2, [x19, 1540]
	mov	x0, x22
	ldr	w1, [x19, 1544]
	bl	Frame_Init
	cbz	w0, .L965
	ldr	x1, .LC197
	mov	w0, 0
	bl	dprint_vfmw
	b	.L965
	.p2align 3
.L1048:
	orr	w0, w0, 32
	mov	w1, 1
	mov	w21, 0
	str	w0, [x23, 3624]
	str	w1, [x23, 3628]
.L1020:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L921:
	mov	w2, w25
	mov	x1, x24
	mov	x0, x22
	bl	MP4_Dec_Slice
	mov	w28, w0
.L925:
	ldrb	w0, [x19, 2885]
	mov	x21, x24
	cmp	w0, 1
	beq	.L970
	cmp	w28, w25, lsl 3
	bhi	.L944
.L1063:
	mov	w0, 196
	cmp	w20, 438
	ccmp	w20, w0, 4, ne
	bne	.L945
	ldr	w1, [x23, 3624]
	mov	w0, 130
	tst	w1, w0
	beq	.L945
	ldrb	w0, [x19, 837]
	cmp	w0, 2
	beq	.L1059
	ldr	w1, [x19, 1540]
	ldr	w0, [x19, 1544]
	str	w0, [x19, 2172]
	str	w1, [x19, 2176]
	cbz	w0, .L949
	ldr	w2, [x19, 2164]
	mov	w20, 1
	cmp	w0, w2
	beq	.L949
.L950:
	ldr	x2, .LC171
	ldr	x4, [x2]
	cbz	x4, .L954
	strh	w0, [x29, 108]
	mov	w3, 8
	ldr	w0, [x19, 2164]
	add	x2, x29, 104
	strh	w0, [x29, 104]
	ldr	w0, [x19, 2168]
	strh	w0, [x29, 106]
	ldr	w0, [x19, 2848]
	strh	w1, [x29, 110]
	mov	w1, 2
	blr	x4
.L954:
	cbnz	w20, .L1060
.L956:
	ldr	w1, [x19, 2172]
	ldr	w0, [x19, 2176]
	str	w1, [x19, 2164]
	str	w0, [x19, 2168]
.L948:
	ldr	x3, [x26, 104]
	mov	x2, 60
	add	x1, x19, 768
	add	x0, x19, 1480
	sub	x21, x21, x24
	blr	x3
	ldr	x1, .LC195
	mov	w0, 2
	add	w21, w28, w21, lsl 3
	bl	dprint_vfmw
	ldr	w0, [x19, 2148]
	add	w0, w0, 1
	str	w0, [x19, 2148]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1047:
	add	x19, x22, 20480
	mov	w1, 2
	strb	w1, [x19, 837]
	lsr	w1, w20, 8
	sub	w1, w1, #128
	cmp	w1, 3
	bhi	.L920
	ldrb	w0, [x27, 3616]
	orr	w0, w0, 2
	strb	w0, [x27, 3616]
	uxtb	w0, w0
	b	.L920
	.p2align 3
.L949:
	cbz	w1, .L951
	ldr	w2, [x19, 2168]
	cmp	w1, w2
	beq	.L1061
	mov	w20, 1
	cbz	w0, .L950
	ldr	w2, [x19, 2164]
	cmp	w0, w2
	bne	.L950
.L971:
	ldr	w2, [x19, 2168]
	cmp	w1, w2
	beq	.L954
	b	.L950
	.p2align 3
.L970:
	ldr	w1, [x23, 3736]
	cbz	w1, .L942
	ldr	w2, [x23, 3740]
	cbnz	w2, .L1062
.L942:
	strb	wzr, [x19, 2885]
.L1065:
	cmp	w28, w25, lsl 3
	bls	.L1063
.L944:
	ldr	x1, .LC199
	mov	w0, 2
	sub	x21, x21, x24
	lsl	w21, w21, 3
	bl	dprint_vfmw
	ldr	w1, [x23, 3624]
	mov	w0, -435
	and	w0, w1, w0
	str	w0, [x23, 3624]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1046:
	ldr	x3, [x26, 104]
	mov	x2, 40
	add	x1, x29, 112
	add	x0, x29, 152
	blr	x3
	mov	w1, 32
	add	x0, x29, 152
	bl	BsSkip
	mov	w1, 32
	add	x0, x29, 152
	bl	BsGet
	mov	w19, w0
	mov	w1, 32
	add	x0, x29, 152
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w19, w2
	ccmp	w0, w1, 0, eq
	bne	.L915
	ldr	x1, .LC171
	add	x19, x22, 20480
	mov	w0, 1
	ldr	x4, [x1]
	strb	w0, [x19, 2884]
	cbz	x4, .L916
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 117
	blr	x4
.L916:
	ldr	w0, [x23, 3624]
	mov	w1, 130
	tst	w0, w1
	beq	.L917
	orr	w0, w0, 32
	mov	w1, 1
	str	w0, [x23, 3624]
	str	w1, [x23, 3628]
.L917:
	add	x1, x22, 12288
	ldr	w0, [x19, 2848]
	add	x1, x1, 3440
	mov	w21, 0
	bl	MP4_ClearCurPacket
	b	.L1020
	.p2align 3
.L915:
	add	x27, x22, 12288
	ldrb	w0, [x27, 3616]
	tbnz	x0, 0, .L919
	add	x19, x22, 20480
	mov	w1, 2
	strb	w1, [x19, 837]
	b	.L920
	.p2align 3
.L936:
	ldr	w0, [x19, 2848]
	add	x1, x27, 3440
	add	x21, x24, 4
	sub	w25, w25, #4
	bl	MP4_ClearCurPacket
	b	.L939
	.p2align 3
.L1050:
	ldr	x1, .LC175
	mov	w0, 2
	bl	dprint_vfmw
	str	wzr, [x19, 2180]
	mov	x1, x24
	mov	w2, w25
	mov	x0, x22
	bl	Mp4_Syntax_Vos
	mov	w28, w0
	mov	w1, w20
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	b	.L925
	.p2align 3
.L1054:
	ldr	x1, .LC183
	mov	w0, 2
	bl	dprint_vfmw
	cmp	w25, 4
	beq	.L1064
	mov	w2, w25
	mov	x1, x24
	mov	x0, x22
	bl	Mp4_Syntax_Vop
	mov	w28, w0
	ldr	w0, [x23, 3624]
	tbnz	x0, 1, .L932
	ldr	w0, [x19, 2848]
	add	x1, x27, 3440
	bl	MP4_ClearCurPacket
.L931:
	ldr	x1, .LC185
	mov	w2, w28
	mov	w0, 7
	bl	dprint_vfmw
	b	.L925
	.p2align 3
.L951:
	ldr	w2, [x19, 2852]
	cmp	w2, 1
	cset	w20, ne
	cbz	w0, .L954
.L972:
	ldr	w2, [x19, 2164]
	cmp	w0, w2
	bne	.L950
	cbnz	w1, .L971
	b	.L954
	.p2align 3
.L1062:
	mov	x0, x22
	bl	Frame_Init
	cbz	w0, .L942
	ldr	x1, .LC191
	mov	w0, 0
	bl	dprint_vfmw
	strb	wzr, [x19, 2885]
	b	.L1065
	.p2align 3
.L1057:
	ldr	w0, [x19, 1544]
	cmp	w0, w2
	bne	.L961
	ldr	w0, [x19, 2852]
	cmp	w0, 1
	bne	.L964
.L965:
	ldr	w0, [x19, 1540]
	mov	w21, w28
	ldr	w1, [x19, 1544]
	str	w1, [x19, 2164]
	str	w0, [x19, 2168]
	ldr	w0, [x23, 3740]
	str	w0, [x19, 1540]
	ldr	w0, [x23, 3736]
	str	w0, [x19, 1544]
	strb	wzr, [x19, 1607]
	b	.L1020
	.p2align 3
.L1051:
	ldr	x1, .LC177
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	str	w0, [x19, 2180]
	mov	w2, w25
	mov	x0, x22
	bl	Mp4_Syntax_Vo
	mov	w28, w0
	mov	w1, w20
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	b	.L925
	.p2align 3
.L1052:
	ldr	x1, .LC179
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, 2
	mov	w2, w25
	mov	x1, x24
	str	w0, [x19, 2180]
	mov	x0, x22
	bl	Mp4_Syntax_Vol
	mov	w28, w0
	mov	w1, w20
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	ldrb	w0, [x19, 1607]
	cmp	w0, 1
	beq	.L925
	ldrb	w21, [x19, 1608]
	cmp	w21, 1
	bne	.L925
	ldr	x3, [x26, 104]
	mov	x2, 604
	add	x1, x19, 164
	add	x0, x23, 3656
	blr	x3
	strb	w21, [x19, 1607]
	strb	w21, [x19, 829]
	b	.L925
	.p2align 3
.L1049:
	ldr	x1, .LC173
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w0, [x19, 2848]
	add	x1, x27, 3440
	bl	MP4_ClearCurPacket
	b	.L1020
	.p2align 3
.L1053:
	ldr	x1, .LC181
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, 3
	mov	x1, x24
	str	w0, [x19, 2180]
	mov	w2, w25
	mov	x0, x22
	bl	Mp4_Syntax_Gop
	mov	w28, w0
	mov	w1, w20
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	b	.L925
	.p2align 3
.L1059:
	ldrb	w0, [x19, 768]
	cmp	w0, 2
	beq	.L947
	ldr	w0, [x19, 1556]
	ldr	w1, [x19, 1548]
	str	w0, [x19, 1560]
	add	w1, w0, w1
	str	w1, [x19, 1556]
	ldr	w3, [x19, 1552]
	ldr	w0, [x23, 3728]
	ldr	w2, [x19, 1568]
	madd	w0, w1, w0, w3
	str	w0, [x19, 1564]
	str	w0, [x19, 1568]
	sub	w0, w0, w2
	str	w0, [x19, 1572]
	b	.L948
	.p2align 3
.L1055:
	ldr	x1, .LC187
	mov	w0, 2
	bl	dprint_vfmw
	mov	w2, w25
	mov	x1, x24
	mov	x0, x22
	bl	Mp4_Syntax_ShortHeader
	mov	w28, w0
	ldr	w0, [x23, 3624]
	tbz	x0, 1, .L1043
	mov	w1, 196
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	b	.L925
	.p2align 3
.L1056:
	ldr	x1, .LC189
	mov	w0, 2
	bl	dprint_vfmw
	mov	w2, w25
	mov	x1, x24
	mov	x0, x22
	bl	Mp4_Syntax_UserData
	mov	w28, w0
.L1043:
	ldr	w0, [x19, 2848]
	add	x1, x27, 3440
	bl	MP4_ClearCurPacket
	b	.L925
	.p2align 3
.L1060:
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L957
	ldr	w0, [x19, 2848]
	ldr	x1, [x23, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x23, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x23, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2848]
	ldr	x1, [x23, 568]
	bl	FreeUsdByDec
	add	x1, x23, 512
	mov	w2, w20
	stp	xzr, xzr, [x1, 32]
	stp	xzr, xzr, [x1, 48]
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2868]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2848]
	mov	w2, w20
	ldr	w1, [x19, 2860]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 2860]
	ldr	w0, [x19, 2848]
	str	wzr, [x19, 2868]
	bl	FSP_GetNullLogicFs
	str	w0, [x19, 2860]
	str	w0, [x19, 2868]
.L957:
	add	x20, x19, 2240
	ldr	w0, [x19, 2848]
	mov	x1, x20
	str	wzr, [x19, 2856]
	bl	FSP_ClearNotInVoQueue
	ldr	x0, [x22, 22120]
	ldr	w1, [x0, 764]
	cbnz	w1, .L958
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1066
.L958:
	ldr	w1, [x19, 2172]
	mov	x0, x22
	ldr	w2, [x19, 2176]
	bl	Frame_Init
	cbz	w0, .L956
	ldr	x1, .LC193
	mov	w0, 0
	bl	dprint_vfmw
	b	.L956
.L932:
	mov	w1, 438
	mov	x0, x22
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L947:
	ldr	w2, [x19, 1560]
	ldr	w1, [x19, 1548]
	ldr	w0, [x23, 3728]
	ldr	w4, [x19, 1552]
	add	w1, w2, w1
	ldr	w3, [x19, 1568]
	ldr	w2, [x19, 1572]
	madd	w0, w1, w0, w4
	sub	w1, w2, w3
	str	w0, [x19, 1564]
	add	w0, w1, w0
	str	w0, [x19, 1576]
	b	.L948
.L1064:
	mov	w1, w20
	mov	x0, x22
	mov	w28, 0
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L1061:
	ldr	w2, [x19, 2852]
	cmp	w2, 1
	cset	w20, ne
	cbnz	w0, .L972
	cbnz	w1, .L971
	b	.L954
.L1058:
	ldr	w0, [x19, 2852]
	cbnz	w0, .L967
	mov	x0, x20
	bl	ResetVoQueue
	b	.L967
.L1066:
	ldr	w0, [x19, 2852]
	cbnz	w0, .L958
	mov	x0, x20
	bl	ResetVoQueue
	b	.L958
	.size	Mp4_Syntax_Parse, .-Mp4_Syntax_Parse
	.align	3
.LC170:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC171:
	.xword	g_event_report
	.align	3
.LC173:
	.xword	.LC172
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC177:
	.xword	.LC176
	.align	3
.LC179:
	.xword	.LC178
	.align	3
.LC181:
	.xword	.LC180
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC187:
	.xword	.LC186
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.align	3
.LC197:
	.xword	.LC196
	.align	3
.LC199:
	.xword	.LC198
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Combine_HdPacket
	.type	MP4_Combine_HdPacket, %function
MP4_Combine_HdPacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 22168]
	add	x0, x19, 20480
	add	x20, x0, 1688
	cbz	x1, .L1079
	add	x1, x19, 12288
	ldrb	w2, [x1, 3450]
	cmp	w2, 1
	beq	.L1080
	cbnz	w2, .L1075
	ldrb	w2, [x1, 3538]
	cmp	w2, 1
	bne	.L1075
	ldr	x4, .LC203
	mov	x2, 88
	ldr	w3, [x19, 15748]
	add	x1, x1, 3528
	ldr	w5, [x20, 20]
	add	x0, x0, 1776
	ldr	x4, [x4, 104]
	add	w3, w5, w3
	str	w3, [x20, 20]
	blr	x4
	mov	w0, 0
.L1070:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1080:
	ldrb	w21, [x20, 10]
	cmp	w21, 1
	beq	.L1081
	cbnz	w21, .L1074
	ldrb	w0, [x20, 98]
	cmp	w0, 1
	bne	.L1074
	ldr	w1, [x19, 15748]
	mov	w0, 0
	ldr	w2, [x20, 108]
	add	w1, w2, w1
	str	w1, [x20, 108]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1075:
	ldr	x1, .LC204
	mov	w2, 5061
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1081:
	ldr	w3, [x19, 15744]
	ldr	w2, [x20, 16]
	cmp	w3, w2
	bcc	.L1082
	ldr	w1, [x19, 15748]
	mov	w0, 0
	ldr	w2, [x20, 20]
	add	w1, w2, w1
	str	w1, [x20, 20]
	b	.L1070
	.p2align 3
.L1074:
	ldr	x1, .LC204
	mov	w2, 5047
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1070
	.p2align 3
.L1082:
	ldr	x3, .LC203
	mov	x2, 88
	add	x1, x1, 3440
	add	x0, x0, 1776
	ldr	x3, [x3, 104]
	blr	x3
	strb	wzr, [x20, 10]
	strb	w21, [x20, 98]
	mov	w0, 0
	b	.L1070
.L1079:
	ldr	x1, .LC200
	ldr	x4, [x1]
	cbz	x4, .L1069
	ldr	w0, [x0, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
.L1069:
	ldr	x1, .LC202
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1070
	.size	MP4_Combine_HdPacket, .-MP4_Combine_HdPacket
	.align	3
.LC200:
	.xword	g_event_report
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC203:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC204:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Renew_CurPacket
	.type	MP4_Renew_CurPacket, %function
MP4_Renew_CurPacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x20
	bl	MP4_Combine_HdPacket
	cmn	w0, #1
	mov	w19, w0
	beq	.L1086
	mov	x0, x20
	add	x20, x20, 20480
	add	x19, x0, 12288
	bl	MP4_Record_PacketID
	ldr	x21, .LC207
	mov	x2, 176
	add	x1, x20, 1688
	add	x0, x19, 3440
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 4
	add	x1, x20, 1864
	add	x0, x19, 3520
	blr	x3
	mov	w0, 0
.L1085:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1086:
	add	x0, x20, 20480
	add	x1, x20, 12288
	add	x1, x1, 3440
	ldr	w0, [x0, 2848]
	bl	MP4_ClearCurPacket
	ldr	x1, .LC206
	mov	w2, 5077
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L1085
	.size	MP4_Renew_CurPacket, .-MP4_Renew_CurPacket
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC207:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP4_Check_CurPacket
	.type	MP4_Check_CurPacket, %function
MP4_Check_CurPacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	add	x21, x19, 20480
	bl	_mcount
	add	x0, x29, 56
	ldr	w1, [x20, 3456]
	str	w1, [x21, 1624]
	ldr	x1, [x19, 15728]
	str	x1, [x19, 22096]
	ldr	w2, [x20, 3460]
	str	w2, [x21, 1628]
	str	wzr, [x21, 1632]
	bl	BsInit
	mov	w1, 32
	add	x0, x29, 56
	bl	BsShow
	ldrb	w1, [x20, 3616]
	tbz	x1, 0, .L1115
	mov	w0, 1
	strb	w0, [x21, 837]
	ldrb	w0, [x20, 3616]
	tbnz	x0, 1, .L1090
	ldr	w2, [x21, 2128]
	mov	w1, 196
.L1094:
	mov	w0, 438
	cmp	w1, w0
	ccmp	w2, w0, 0, eq
	beq	.L1113
	mov	w0, 196
	cmp	w1, w0
	ccmp	w2, w0, 0, eq
	beq	.L1113
.L1112:
	mov	w0, 0
	b	.L1098
	.p2align 3
.L1115:
	lsr	w1, w0, 8
	mov	w2, 2
	sub	w1, w1, #128
	strb	w2, [x21, 837]
	cmp	w1, 3
	mov	w1, w0
	bls	.L1116
.L1089:
	ldrb	w2, [x20, 3616]
	tbz	x2, 1, .L1117
	ldr	w2, [x21, 2128]
	cmp	w0, 196
	cset	w1, eq
	cmp	w2, 438
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L1118
.L1095:
	mov	x0, x19
	bl	MP4_Renew_CurPacket
.L1098:
	ldr	x1, [x19, 15728]
	cbz	x1, .L1102
	ldr	w1, [x19, 15744]
	cmp	w1, wzr
	csinv	w0, w0, wzr, ne
.L1111:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
.L1118:
	ldrb	w0, [x21, 1609]
	cmp	w0, 1
	cset	w0, eq
	orr	w1, w1, w0
	cbz	w1, .L1095
	.p2align 2
.L1090:
	mov	x0, 438
	ldr	x1, [x19, 22608]
	movk	x0, 0x1, lsl 32
	cmp	x1, x0
	bne	.L1112
	ldr	w0, [x21, 1708]
	cmp	w0, 4
	beq	.L1095
	mov	w0, 0
	b	.L1098
	.p2align 3
.L1116:
	ldrb	w2, [x20, 3616]
	orr	w2, w2, 2
	strb	w2, [x20, 3616]
	b	.L1089
	.p2align 3
.L1113:
	ldr	w0, [x21, 2136]
	cmp	w0, 1
	ble	.L1112
.L1093:
	mov	x0, x19
	bl	MP4_Clean_HeadPacket
	mov	w0, 0
	b	.L1098
	.p2align 3
.L1117:
	ldr	w2, [x21, 2128]
	mov	w3, 196
	cmp	w2, 438
	ccmp	w0, w3, 4, ne
	bne	.L1093
	b	.L1094
	.p2align 3
.L1102:
	mov	w0, -1
	b	.L1111
	.size	MP4_Check_CurPacket, .-MP4_Check_CurPacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_Decode
	.type	MPEG4DEC_Decode, %function
MPEG4DEC_Decode:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	mov	x21, x1
	bl	_mcount
	ldr	w0, [x19, 2156]
	cbz	w0, .L1120
	ldr	w0, [x21, 20]
	cbz	w0, .L1120
	ldr	w0, [x21, 16]
	cbz	w0, .L1120
	ldr	x0, [x21]
	cbz	x0, .L1120
	ldr	x1, .LC211
	mov	w0, 2
	add	x22, x20, 12288
	add	x23, x22, 3440
	bl	dprint_vfmw
	ldr	x1, .LC213
	mov	w0, 7
	ldr	w2, [x21, 16]
	bl	dprint_vfmw
	ldr	x1, .LC215
	mov	w0, 7
	ldr	w2, [x21, 20]
	bl	dprint_vfmw
	ldrb	w2, [x21, 10]
	mov	w0, 7
	ldr	x1, .LC217
	bl	dprint_vfmw
	ldr	x1, .LC219
	mov	w0, 7
	ldr	w2, [x21, 104]
	bl	dprint_vfmw
	ldr	x1, .LC221
	mov	w0, 7
	ldr	w2, [x21, 108]
	bl	dprint_vfmw
	ldrb	w2, [x21, 98]
	mov	w0, 7
	ldr	x1, .LC223
	bl	dprint_vfmw
	ldr	x1, .LC225
	mov	w0, 7
	ldr	w2, [x21, 20]
	bl	dprint_vfmw
	ldr	x2, [x21]
	mov	w0, 7
	ldr	x1, .LC227
	ldrb	w2, [x2]
	bl	dprint_vfmw
	ldr	x2, [x21]
	mov	w0, 7
	ldr	x1, .LC229
	ldrb	w2, [x2, 1]
	bl	dprint_vfmw
	ldr	x2, [x21]
	mov	w0, 7
	ldr	x1, .LC231
	ldrb	w2, [x2, 2]
	bl	dprint_vfmw
	ldr	x2, [x21]
	mov	w0, 7
	ldr	x1, .LC233
	ldrb	w2, [x2, 3]
	bl	dprint_vfmw
	ldr	x3, .LC234
	mov	x2, 176
	mov	x1, x21
	mov	x0, x23
	ldr	x3, [x3, 104]
	blr	x3
	mov	x1, x23
	mov	x0, x20
	bl	MP4_GetScdUpMsg
	mov	x0, x20
	bl	MP4_Check_CurPacket
	cmn	w0, #1
	mov	w24, w0
	beq	.L1265
	mov	x1, x23
	mov	x0, x20
	bl	MP4_GetScdUpMsg
	ldr	w1, [x23, 16]
	str	w1, [x19, 1624]
	ldr	x1, [x20, 15728]
	str	x1, [x20, 22096]
	ldr	w0, [x19, 1684]
	ldr	w2, [x23, 20]
	str	w2, [x19, 1628]
	cmp	w0, 2
	str	wzr, [x19, 1632]
	ldr	x3, [x20, 22120]
	beq	.L1266
.L1125:
	ldr	w0, [x3, 8]
	cmp	w0, 2
	beq	.L1126
	cmp	w0, 1
	beq	.L1258
	cmp	w0, 4
	csel	w0, w0, wzr, eq
.L1258:
	str	w0, [x19, 1684]
	add	x23, x20, 16384
	ldr	w0, [x3, 880]
	cmp	w0, 1
	beq	.L1267
.L1131:
	ldr	w0, [x23, 3624]
	str	w0, [x19, 2888]
.L1132:
	mov	x0, x20
	bl	Mp4_Syntax_Parse
	lsr	w2, w0, 3
	ldr	x4, [x20, 22096]
	mov	x3, x2
	and	w0, w0, 7
	add	x2, x4, x2
	str	x2, [x20, 22096]
	str	w0, [x19, 1632]
	ldr	w2, [x19, 1624]
	ldr	w0, [x19, 1628]
	add	w2, w2, w3
	str	w2, [x19, 1624]
	sub	w0, w0, w3
	str	w0, [x19, 1628]
	ldr	x0, [x20, 22120]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L1268
.L1133:
	ldr	w1, [x23, 3624]
	mov	w0, 288
	tst	w1, w0
	beq	.L1134
	mov	w0, -435
	and	w0, w1, w0
	str	w0, [x23, 3624]
	ldr	w0, [x19, 1684]
	cmp	w0, 2
	beq	.L1269
	cmp	w0, 1
	beq	.L1270
	cmp	w0, 4
	bne	.L1188
	ldrb	w0, [x19, 1480]
	cbz	w0, .L1271
	sub	w1, w0, #2
	and	w1, w1, -3
	uxtb	w1, w1
	cbnz	w1, .L1144
	ldr	w1, [x19, 2184]
	cmp	w1, 2
	beq	.L1173
.L1144:
	cmp	w0, 1
	bne	.L1188
	str	w0, [x19, 2184]
	b	.L1188
	.p2align 3
.L1270:
	ldrb	w0, [x19, 1480]
	cmp	w0, 2
	beq	.L1136
.L1188:
	mov	x0, x20
	bl	Mp4_Frame_Atr
	cmn	w0, #1
	beq	.L1272
	ldr	w1, [x19, 2860]
	ldr	w0, [x19, 2848]
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	ldr	w1, [x19, 2868]
	ldr	w0, [x19, 2848]
	bl	FSP_GetFsImagePtr
	mov	x26, x0
	cmp	x25, xzr
	cset	w24, eq
	cmp	x0, xzr
	cset	w0, eq
	orr	w24, w24, w0
	cbnz	w24, .L1273
	ldrb	w0, [x19, 835]
	and	w2, w0, -3
	uxtb	w2, w2
	cmp	w2, 1
	bne	.L1148
	cbz	x25, .L1149
	ldr	x0, [x20, 22120]
	ldr	w1, [x25, 152]
	ldr	w0, [x0]
	cmp	w1, w0
	bls	.L1151
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x23, 3620]
	ldr	w24, [x19, 2848]
	cmp	w21, wzr
	ble	.L1274
.L1190:
	add	x22, x22, 3620
	mov	w19, 0
	.p2align 2
.L1152:
	ldr	w1, [x22], 4
	mov	w0, w24
	add	w19, w19, 1
	bl	SM_ReleaseStreamSeg
	cmp	w19, w21
	blt	.L1152
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
	cbz	x25, .L1189
.L1153:
	ldr	x3, [x20, 22120]
	mov	w0, 1
	ldr	w2, [x25, 152]
	mov	w24, -1
	ldr	x1, .LC245
	ldr	w3, [x3]
	bl	dprint_vfmw
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1148:
	cmp	w0, 2
	beq	.L1275
.L1151:
	ldrb	w0, [x19, 1480]
	cmp	w0, 2
	beq	.L1168
	ldr	w3, [x19, 2856]
	mov	w0, 2
	ldr	w1, [x19, 2860]
	ldr	w2, [x19, 2868]
	cmp	w3, wzr
	csinc	w0, w0, wzr, gt
	str	w0, [x19, 2856]
	cmp	w1, w2
	beq	.L1166
	ldr	w0, [x19, 2848]
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2860]
	bl	FSP_GetDisplay
	cmp	w0, 3
	beq	.L1259
	ldr	w0, [x19, 2848]
	mov	w2, 0
	ldr	w1, [x19, 2860]
	bl	FSP_SetDisplay
.L1259:
	ldr	w2, [x19, 2868]
.L1166:
	str	w2, [x19, 2860]
	mov	w2, 1
	ldrb	w0, [x20, 1]
	strb	w0, [x20]
	ldr	w0, [x19, 2872]
	ldr	w1, [x19, 2876]
	str	w1, [x19, 2868]
	str	w0, [x19, 2864]
	ldrb	w0, [x20, 2]
	strb	w0, [x20, 1]
	ldr	w3, [x19, 1572]
	ldr	w0, [x19, 2848]
	str	w3, [x19, 2872]
	bl	FSP_SetRef
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2860]
	bl	FSP_RemovePmv
	ldrb	w0, [x19, 1480]
	cmp	w0, 4
	bne	.L1168
	ldrb	w0, [x19, 832]
	cbz	w0, .L1276
.L1181:
	mov	w24, 0
.L1249:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1266:
	ldr	w0, [x3, 8]
	cmp	w0, 2
	bne	.L1277
.L1126:
	mov	w0, 2
	str	w0, [x19, 1684]
	add	x23, x20, 16384
	ldr	w0, [x3, 880]
	cmp	w0, 1
	bne	.L1131
.L1267:
	ldr	w0, [x3, 928]
	cmp	w0, 1
	bne	.L1131
	ldr	w0, [x19, 2888]
	str	w0, [x23, 3624]
	b	.L1132
	.p2align 3
.L1268:
	ldr	w0, [x0, 928]
	cbz	w0, .L1133
	b	.L1181
	.p2align 3
.L1168:
	mov	x0, x20
	mov	x2, x21
	mov	w1, 0
	bl	Mp4_Set_DecPar
	ldrb	w0, [x19, 1480]
	cbnz	w0, .L1278
	ldr	w1, [x19, 2184]
	cbnz	w1, .L1170
	mov	w1, 2
	str	w1, [x19, 2184]
.L1171:
	ldr	x3, [x20, 22120]
	add	x1, x20, 1048
	str	x1, [x20, 1040]
	ldr	w2, [x3, 920]
	cmp	w2, 1
	beq	.L1178
.L1177:
	cmp	w2, 2
	beq	.L1197
.L1178:
	strb	wzr, [x20, 1214]
	cbnz	w0, .L1181
	ldr	x0, .LC248
	ldr	x4, [x0]
	cbz	x4, .L1181
	add	x2, x29, 96
	ldr	w0, [x19, 2848]
	mov	w3, 4
	mov	w1, 20
	mov	w24, 0
	str	wzr, [x2, -8]!
	blr	x4
	b	.L1249
	.p2align 3
.L1269:
	ldrb	w0, [x19, 1480]
	cbz	w0, .L1188
.L1136:
	ldr	w0, [x23, 3620]
	ldr	w21, [x19, 2848]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
	.p2align 2
.L1140:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x22
	bne	.L1140
.L1141:
	mov	x0, x20
	str	wzr, [x23, 3620]
	mov	w24, -1
	bl	MP4_Clean_HeadPacket
	b	.L1249
	.p2align 3
.L1271:
	ldr	w0, [x19, 2184]
	cbnz	w0, .L1143
	mov	w0, 2
	str	w0, [x19, 2184]
	b	.L1188
	.p2align 3
.L1277:
	mov	w0, 1
	str	w0, [x19, 2232]
	b	.L1125
	.p2align 3
.L1278:
	sub	w1, w0, #2
	cmp	w0, 2
	and	w1, w1, -3
	cset	w24, eq
	uxtb	w1, w1
	cbnz	w1, .L1172
	ldr	w1, [x19, 2184]
	cmp	w1, 2
	beq	.L1279
.L1172:
	cmp	w0, 1
	bne	.L1174
	str	w0, [x19, 2184]
	add	x1, x20, 1048
	str	x1, [x20, 1040]
	ldr	x3, [x20, 22120]
	ldr	w2, [x3, 920]
	cmp	w2, 1
	beq	.L1175
	cmp	w2, 2
	beq	.L1197
.L1175:
	strb	wzr, [x20, 1214]
	b	.L1181
	.p2align 3
.L1275:
	cbz	x25, .L1154
	ldr	x0, [x20, 22120]
	ldr	w1, [x25, 152]
	ldr	w0, [x0]
	cmp	w1, w0
	bhi	.L1155
	cbz	x26, .L1159
	ldr	w1, [x26, 152]
	cmp	w0, w1
	bcs	.L1151
.L1159:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x19, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L1160
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
	.p2align 2
.L1161:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x22, x19
	bne	.L1161
.L1160:
	mov	x0, x20
	str	wzr, [x23, 3620]
	mov	w24, -1
	bl	MP4_Clean_HeadPacket
	ldr	x3, [x20, 22120]
	mov	w0, 1
	ldr	x1, .LC258
	ldr	w2, [x26, 152]
	ldr	w3, [x3]
	bl	dprint_vfmw
	b	.L1249
	.p2align 3
.L1276:
	ldr	x1, .LC250
	mov	w0, 11
	bl	dprint_vfmw
	ldr	w1, [x19, 2876]
	ldr	w0, [x19, 2848]
	bl	FSP_GetLogicFs
	mov	x21, x0
	ldr	w1, [x19, 2860]
	ldr	w0, [x19, 2848]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cmp	x21, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L1280
	ldr	x1, [x21, 32]
	cbz	x1, .L1184
	ldr	x0, [x21, 40]
	cbz	x0, .L1184
	ldr	x4, [x24, 32]
	ldr	w3, [x0, 8]
	ldr	w2, [x1, 8]
	cbz	x4, .L1200
	ldr	w4, [x4, 8]
.L1187:
	ldr	w6, [x19, 1540]
	mov	x1, x21
	ldr	w5, [x19, 1544]
	mov	x0, x20
	mov	w24, 0
	bl	Vdm_Mem_Move
	b	.L1249
	.p2align 3
.L1120:
	ldr	x1, .LC209
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1143:
	mov	w0, 1
	str	w0, [x19, 2184]
	b	.L1188
	.p2align 3
.L1170:
	mov	w1, 1
	str	w1, [x19, 2184]
	b	.L1171
	.p2align 3
.L1155:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x23, 3620]
	ldr	w24, [x19, 2848]
	cmp	w21, wzr
	ble	.L1281
.L1193:
	add	x22, x22, 3620
	mov	w19, 0
	.p2align 2
.L1157:
	ldr	w1, [x22], 4
	mov	w0, w24
	add	w19, w19, 1
	bl	SM_ReleaseStreamSeg
	cmp	w19, w21
	blt	.L1157
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
	cbz	x25, .L1195
.L1158:
	ldr	x3, [x20, 22120]
	mov	w0, 1
	ldr	x1, .LC247
	mov	w24, -1
	ldr	w2, [x25, 152]
	ldr	w3, [x3]
	bl	dprint_vfmw
	b	.L1249
	.p2align 3
.L1197:
	ldr	w2, [x3, 924]
	cmp	w2, wzr
	cset	w2, gt
	cmp	x1, xzr
	and	w24, w24, w2
	cset	w1, ne
	tst	w1, w24
	beq	.L1178
	str	xzr, [x20, 1040]
	mov	w2, 1
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	x1, [x20, 22120]
	ldr	w0, [x1, 924]
	sub	w0, w0, #1
	str	w0, [x1, 924]
	ldr	w0, [x23, 3620]
	ldr	w21, [x19, 2848]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
.L1180:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x22, x19
	bne	.L1180
	b	.L1141
	.p2align 3
.L1174:
	ldr	x3, [x20, 22120]
	add	x1, x20, 1048
	str	x1, [x20, 1040]
	ldr	w2, [x3, 920]
	cmp	w2, 1
	bne	.L1177
	cmp	x1, xzr
	cset	w1, ne
	tst	w24, w1
	beq	.L1178
	str	xzr, [x20, 1040]
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x19, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
.L1179:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x22, x19
	bne	.L1179
	b	.L1141
	.p2align 3
.L1149:
	ldr	w0, [x19, 2848]
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x23, 3620]
	ldr	w24, [x19, 2848]
	cmp	w21, wzr
	bgt	.L1190
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
	.p2align 2
.L1189:
	ldr	x2, .LC239
	mov	w3, 3758
	ldr	x1, .LC243
	mov	w0, 1
	add	x2, x2, 1360
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1249
.L1274:
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
	b	.L1153
.L1279:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	x0, .LC248
	ldr	x4, [x0]
	cbz	x4, .L1173
	ldr	w0, [x19, 2848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	mov	w24, -1
	blr	x4
	b	.L1249
.L1265:
	ldr	x1, .LC236
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1249
.L1134:
	ldr	x1, .LC256
	mov	w0, 2
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1249
.L1273:
	ldr	x2, .LC239
	mov	w3, 3744
	ldr	x1, .LC241
	mov	w0, 1
	add	x2, x2, 1360
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1249
.L1272:
	ldr	x1, .LC238
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w21, [x19, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
	.p2align 2
.L1146:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x22, x19
	bne	.L1146
	b	.L1141
.L1200:
	mov	w4, w2
	b	.L1187
.L1154:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	w21, [x23, 3620]
	cmp	w21, wzr
	bgt	.L1282
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
.L1195:
	ldr	x2, .LC239
	mov	w3, 3778
	ldr	x1, .LC243
	mov	w0, 1
	add	x2, x2, 1360
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1249
.L1173:
	mov	w24, -1
	b	.L1249
.L1282:
	ldr	w24, [x19, 2848]
	b	.L1193
.L1280:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC252
	mov	x3, x21
	mov	x4, x24
	mov	w2, 3941
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w21, [x19, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
.L1183:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x22
	bne	.L1183
	b	.L1141
.L1184:
	ldr	w0, [x19, 2848]
	mov	w2, 1
	ldr	w1, [x19, 2876]
	bl	FSP_ClearLogicFs
	ldp	x5, x6, [x21, 32]
	ldr	x1, .LC254
	mov	w0, 0
	ldr	w2, [x19, 2860]
	ldr	w4, [x19, 2868]
	ldr	w3, [x19, 2876]
	bl	dprint_vfmw
	ldr	w21, [x19, 2848]
	ldr	w0, [x23, 3620]
	cmp	w0, wzr
	ble	.L1141
	sub	w19, w0, #1
	add	x22, x22, 3620
	add	x19, x19, 3978
	add	x19, x20, x19, lsl 2
.L1186:
	ldr	w1, [x22], 4
	mov	w0, w21
	bl	SM_ReleaseStreamSeg
	cmp	x19, x22
	bne	.L1186
	b	.L1141
.L1281:
	mov	x0, x20
	str	wzr, [x23, 3620]
	bl	MP4_Clean_HeadPacket
	b	.L1158
	.size	MPEG4DEC_Decode, .-MPEG4DEC_Decode
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.align	3
.LC213:
	.xword	.LC212
	.align	3
.LC215:
	.xword	.LC214
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC223:
	.xword	.LC222
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC227:
	.xword	.LC226
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC234:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC239:
	.xword	.LANCHOR1
	.align	3
.LC241:
	.xword	.LC240
	.align	3
.LC243:
	.xword	.LC242
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC248:
	.xword	g_event_report
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.align	3
.LC254:
	.xword	.LC253
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_GetImageWidth
	.type	MPEG4DEC_GetImageWidth, %function
MPEG4DEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 20480
	bl	_mcount
	ldr	w0, [x19, 1544]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG4DEC_GetImageWidth, .-MPEG4DEC_GetImageWidth
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG4DEC_GetImageHeight
	.type	MPEG4DEC_GetImageHeight, %function
MPEG4DEC_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 20480
	bl	_mcount
	ldr	w0, [x19, 1540]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG4DEC_GetImageHeight, .-MPEG4DEC_GetImageHeight
	.global	sprite_trajectory_len
	.global	default_inter_matrix
	.global	default_intra_matrix
	.global	scan_tables
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	default_intra_matrix, %object
	.size	default_intra_matrix, 256
default_intra_matrix:
	.word	8
	.word	17
	.word	18
	.word	19
	.word	21
	.word	23
	.word	25
	.word	27
	.word	17
	.word	18
	.word	19
	.word	21
	.word	23
	.word	25
	.word	27
	.word	28
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	25
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	41
	.word	27
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	41
	.word	45
	.type	default_inter_matrix, %object
	.size	default_inter_matrix, 256
default_inter_matrix:
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	20
	.word	21
	.word	22
	.word	23
	.word	25
	.word	26
	.word	27
	.word	28
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	28
	.word	30
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	28
	.word	30
	.word	31
	.word	23
	.word	24
	.word	25
	.word	27
	.word	28
	.word	30
	.word	31
	.word	33
	.type	scan_tables, %object
	.size	scan_tables, 768
scan_tables:
	.word	0
	.word	1
	.word	8
	.word	16
	.word	9
	.word	2
	.word	3
	.word	10
	.word	17
	.word	24
	.word	32
	.word	25
	.word	18
	.word	11
	.word	4
	.word	5
	.word	12
	.word	19
	.word	26
	.word	33
	.word	40
	.word	48
	.word	41
	.word	34
	.word	27
	.word	20
	.word	13
	.word	6
	.word	7
	.word	14
	.word	21
	.word	28
	.word	35
	.word	42
	.word	49
	.word	56
	.word	57
	.word	50
	.word	43
	.word	36
	.word	29
	.word	22
	.word	15
	.word	23
	.word	30
	.word	37
	.word	44
	.word	51
	.word	58
	.word	59
	.word	52
	.word	45
	.word	38
	.word	31
	.word	39
	.word	46
	.word	53
	.word	60
	.word	61
	.word	54
	.word	47
	.word	55
	.word	62
	.word	63
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	16
	.word	17
	.word	10
	.word	11
	.word	4
	.word	5
	.word	6
	.word	7
	.word	15
	.word	14
	.word	13
	.word	12
	.word	19
	.word	18
	.word	24
	.word	25
	.word	32
	.word	33
	.word	26
	.word	27
	.word	20
	.word	21
	.word	22
	.word	23
	.word	28
	.word	29
	.word	30
	.word	31
	.word	34
	.word	35
	.word	40
	.word	41
	.word	48
	.word	49
	.word	42
	.word	43
	.word	36
	.word	37
	.word	38
	.word	39
	.word	44
	.word	45
	.word	46
	.word	47
	.word	50
	.word	51
	.word	56
	.word	57
	.word	58
	.word	59
	.word	52
	.word	53
	.word	54
	.word	55
	.word	60
	.word	61
	.word	62
	.word	63
	.word	0
	.word	8
	.word	16
	.word	24
	.word	1
	.word	9
	.word	2
	.word	10
	.word	17
	.word	25
	.word	32
	.word	40
	.word	48
	.word	56
	.word	57
	.word	49
	.word	41
	.word	33
	.word	26
	.word	18
	.word	3
	.word	11
	.word	4
	.word	12
	.word	19
	.word	27
	.word	34
	.word	42
	.word	50
	.word	58
	.word	35
	.word	43
	.word	51
	.word	59
	.word	20
	.word	28
	.word	5
	.word	13
	.word	6
	.word	14
	.word	21
	.word	29
	.word	36
	.word	44
	.word	52
	.word	60
	.word	37
	.word	45
	.word	53
	.word	61
	.word	22
	.word	30
	.word	7
	.word	15
	.word	23
	.word	31
	.word	38
	.word	46
	.word	54
	.word	62
	.word	39
	.word	47
	.word	55
	.word	63
	.type	__FUNCTION__.11756, %object
	.size	__FUNCTION__.11756, 15
__FUNCTION__.11756:
	.string	"Mp4_Set_DecPar"
	.zero	1
	.type	__FUNCTION__.11890, %object
	.size	__FUNCTION__.11890, 23
__FUNCTION__.11890:
	.string	"Mp4_Syntax_Slice_NotSH"
	.zero	1
	.type	__FUNCTION__.11904, %object
	.size	__FUNCTION__.11904, 20
__FUNCTION__.11904:
	.string	"Mp4_Syntax_Slice_SH"
	.zero	4
	.type	__FUNCTION__.11919, %object
	.size	__FUNCTION__.11919, 14
__FUNCTION__.11919:
	.string	"MP4_Dec_Slice"
	.zero	2
	.type	__FUNCTION__.11793, %object
	.size	__FUNCTION__.11793, 16
__FUNCTION__.11793:
	.string	"MPEG4DEC_Decode"
	.data
	.align	3
.LANCHOR0 = . + 0
	.type	sprite_trajectory_len, %object
	.size	sprite_trajectory_len, 120
sprite_trajectory_len:
	.word	0
	.byte	2
	.zero	3
	.word	2
	.byte	3
	.zero	3
	.word	3
	.byte	3
	.zero	3
	.word	4
	.byte	3
	.zero	3
	.word	5
	.byte	3
	.zero	3
	.word	6
	.byte	3
	.zero	3
	.word	14
	.byte	4
	.zero	3
	.word	30
	.byte	5
	.zero	3
	.word	62
	.byte	6
	.zero	3
	.word	126
	.byte	7
	.zero	3
	.word	254
	.byte	8
	.zero	3
	.word	510
	.byte	9
	.zero	3
	.word	1022
	.byte	10
	.zero	3
	.word	2046
	.byte	11
	.zero	3
	.word	4094
	.byte	12
	.zero	3
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC14:
	ASCII(.string	"fatal stream error --- GOP marker_bit = 0\n" )
	.zero	5
.LC19:
	ASCII(.string	"DivX%4dBuild%4d%c" )
	.zero	6
.LC21:
	ASCII(.string	"DivX%4db%4d%c" )
	.zero	2
.LC23:
	ASCII(.string	"FFmpe%*[^b]b%4d" )
.LC25:
	ASCII(.string	"FFmpeg v%4d.%4d.%4d / libavcodec build: %d" )
	.zero	5
.LC27:
	ASCII(.string	"Lavc%d.%d.%d" )
	.zero	3
.LC29:
	ASCII(.string	"ffmpeg" )
	.zero	1
.LC31:
	ASCII(.string	"XviD%4d" )
.LC36:
	ASCII(.string	"fatal stream error --- VOP marker_bit = 0\n" )
	.zero	5
.LC40:
	ASCII(.string	"VDH doesn't support SPRITE_STATIC & SPRITE_GMC\n" )
.LC42:
	ASCII(.string	"VDH doesn't support SPRITE_STATIC\n" )
	.zero	5
.LC44:
	ASCII(.string	"Unknown sprite_enable\n" )
	.zero	1
.LC46:
	ASCII(.string	"ERROR: not_8_bit !=0\n" )
	.zero	2
.LC49:
	ASCII(.string	"not support no complexity_estimation_disable\n" )
	.zero	2
.LC51:
	ASCII(.string	"not support data_partitioned\n" )
	.zero	2
.LC53:
	ASCII(.string	"not support newpred_enable\n" )
	.zero	4
.LC55:
	ASCII(.string	"not support reduced_resolution_vop_eanble\n" )
	.zero	5
.LC57:
	ASCII(.string	"not support scalability\n" )
	.zero	7
.LC61:
	ASCII(.string	"warning! profile_and_level_indication=%#x, maybe HD pic...\n" )
	.zero	4
.LC64:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC67:
	ASCII(.string	"actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	6
.LC70:
	ASCII(.string	"MPEG4 Frame_Init return err!\n" )
	.zero	2
.LC73:
	ASCII(.string	"MPEG4 Frame_Init PmvNum=%d, FrameNum=%d, error!\n" )
	.zero	7
.LC76:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC78:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC80:
	ASCII(.string	"NVOP VDM copy process................\n" )
	.zero	1
.LC82:
	ASCII(.string	"dec_pts: %lld Usertag: %lld\n" )
	.zero	3
.LC85:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC89:
	ASCII(.string	"%s %d  abnormal!\n" )
	.zero	6
.LC91:
	ASCII(.string	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\n" )
	.zero	3
.LC93:
	ASCII(.string	"MPEG4DEC Init  -----\n" )
	.zero	2
.LC96:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC98:
	ASCII(.string	"MPEG4DEC Init success -----\n" )
	.zero	3
.LC100:
	ASCII(.string	"MPEG4 destroy\n" )
	.zero	1
.LC105:
	ASCII(.string	"vop_coding_type = %d is not expected!\n" )
	.zero	1
.LC107:
	ASCII(.string	" slice num %d is not extpected!\n" )
	.zero	7
.LC109:
	ASCII(.string	" line %d packet is wrong!\n" )
	.zero	5
.LC113:
	ASCII(.string	"pImg is null, pCurImg %#x pBwdImg %#x\n" )
	.zero	1
.LC115:
	ASCII(.string	"FrameNum=%d\n" )
	.zero	3
.LC117:
	ASCII(.string	"vop_coding_type=%d\n" )
	.zero	4
.LC120:
	ASCII(.string	"line: %d pToQueImg is null!\n" )
	.zero	3
.LC123:
	ASCII(.string	"CurImage %d is already out put\n" )
.LC125:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC127:
	ASCII(.string	"StreamIDNum = %d > (%d)\n" )
	.zero	7
.LC129:
	ASCII(.string	"Warning : vop slice num %d != 0\n" )
	.zero	7
.LC134:
	ASCII(.string	"warning streamIDNum %d != 0 \n" )
	.zero	2
.LC138:
	ASCII(.string	"vop ---%d\n" )
	.zero	5
.LC142:
	ASCII(.string	"VDH doesn't support S_VOP\n" )
	.zero	5
.LC144:
	ASCII(.string	"parse time_module_base stream not enough\n" )
	.zero	6
.LC146:
	ASCII(.string	"module time base parse error, more than %d '1' was found!\n" )
	.zero	5
.LC149:
	ASCII(.string	"error: vop_coding_type = %d, but vop_fcode_forward = 0\n" )
.LC151:
	ASCII(.string	"error: B vop, but vop_fcode_backward = 0\n" )
	.zero	6
.LC155:
	ASCII(.string	"FUN: %s Invalid SlcNum = %d\n" )
	.zero	3
.LC157:
	ASCII(.string	" pSlcPara->mb_start_num = %d, MbCnt = %d\n" )
	.zero	6
.LC161:
	ASCII(.string	"pSlcPara->mb_start_num = %d, totalMbMin1 = %d\n" )
	.zero	1
.LC164:
	ASCII(.string	"FUN: %s MP4_ClearCurPacket\n" )
	.zero	4
.LC167:
	ASCII(.string	"pCtx is NUL!!!\n" )
.LC172:
	ASCII(.string	"Not find start code \n" )
	.zero	2
.LC174:
	ASCII(.string	"VOS beginning ~ !\n" )
	.zero	5
.LC176:
	ASCII(.string	"VO beginning ~ !\n" )
	.zero	6
.LC178:
	ASCII(.string	"VOL beginning ~ !\n" )
	.zero	5
.LC180:
	ASCII(.string	"GOP beginning ~ !\n" )
	.zero	5
.LC182:
	ASCII(.string	"VOP beginning ~ !\n" )
	.zero	5
.LC184:
	ASCII(.string	"BitUsed=%d\n" )
	.zero	4
.LC186:
	ASCII(.string	"SHVOP beginning ~ !\n" )
	.zero	3
.LC188:
	ASCII(.string	"USERDATA beginning ~ !\n" )
.LC190:
	ASCII(.string	"MPEG4 Frame_Init return err 3!\n" )
.LC192:
	ASCII(.string	"MPEG4 Frame_Init return err 1!\n" )
.LC194:
	ASCII(.string	"vop right\n" )
	.zero	5
.LC196:
	ASCII(.string	"MPEG4 Frame_Init return err 2!\n" )
.LC198:
	ASCII(.string	"bits over boundary\n" )
	.zero	4
.LC201:
	ASCII(.string	"pLastPacket->StreamPack[0].VirAddr is NULL!!\n" )
	.zero	2
.LC205:
	ASCII(.string	"line %d MP4_Combine_HdPacket failed!!\n" )
	.zero	1
.LC208:
	ASCII(.string	"bitsream para error -----\n" )
	.zero	5
.LC210:
	ASCII(.string	"MPEG4DEC Decode -----\n" )
	.zero	1
.LC212:
	ASCII(.string	"ptr_strm_para->PhyAddr0=0x%x\n" )
	.zero	2
.LC214:
	ASCII(.string	"ptr_strm_para->Length0=%d\n" )
	.zero	5
.LC216:
	ASCII(.string	"ptr_strm_para->IsLastSeg0=%d\n" )
	.zero	2
.LC218:
	ASCII(.string	"ptr_strm_para->PhyAddr1=0x%x\n" )
	.zero	2
.LC220:
	ASCII(.string	"ptr_strm_para->Length1=%d\n" )
	.zero	5
.LC222:
	ASCII(.string	"ptr_strm_para->IsLastSeg1=%d\n" )
	.zero	2
.LC224:
	ASCII(.string	"ptr_strm_para->Length0 = %d\n" )
	.zero	3
.LC226:
	ASCII(.string	"byte0: = 0x%x\n" )
	.zero	1
.LC228:
	ASCII(.string	"byte1: = 0x%x\n" )
	.zero	1
.LC230:
	ASCII(.string	"byte2: = 0x%x\n" )
	.zero	1
.LC232:
	ASCII(.string	"byte3: = 0x%x\n" )
	.zero	1
.LC235:
	ASCII(.string	"MP4_Check_CurPacket failed!\n" )
	.zero	3
.LC237:
	ASCII(.string	"Mp4_Frame_Atr return fail\n" )
	.zero	5
.LC240:
	ASCII(.string	"fuction return value is null, %s %d!!\n" )
	.zero	1
.LC242:
	ASCII(.string	"fuction return value is null,%s %d!!\n" )
	.zero	2
.LC244:
	ASCII(.string	"dec P/S frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.zero	2
.LC246:
	ASCII(.string	"dec B frame, bwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC249:
	ASCII(.string	"NVOP mem move--\n" )
	.zero	7
.LC251:
	ASCII(.string	"line: %d pCur = %p, pFwd = %p\n" )
	.zero	1
.LC253:
	ASCII(.string	"CurFsID(f%d,%d,b%d) abnormal!(%p,%p,%p)\n" )
	.zero	7
.LC255:
	ASCII(.string	"bits not enought\n" )
	.zero	6
.LC257:
	ASCII(.string	"dec B frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.bss
	.align	3
.LANCHOR2 = . + 0
	.type	MemArrange.11694, %object
	.size	MemArrange.11694, 1232
MemArrange.11694:
	.zero	1232
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
