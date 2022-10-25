#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"real8.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetBits
	.type	Real8_CB_GetBits, %function
Real8_CB_GetBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real8_CB_GetBits, .-Real8_CB_GetBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_Get1Bit
	.type	Real8_CB_Get1Bit, %function
Real8_CB_Get1Bit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_CB_Get1Bit, .-Real8_CB_Get1Bit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetVLCBits
	.type	Real8_CB_GetVLCBits, %function
Real8_CB_GetVLCBits:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x23, x1
	mov	w20, 0
	bl	_mcount
	ldr	x22, .LC3
	mov	w19, 0
	.p2align 2
.L4:
	mov	w1, 8
	mov	x0, x21
	bl	BsShow
	ldrb	w2, [x22, w0, uxtw]
	mov	x0, x21
	lsr	w1, w2, 4
	lsr	w3, w2, 5
	add	w20, w20, w1
	and	w2, w2, 15
	lsl	w19, w19, w3
	orr	w19, w2, w19
	bl	BsSkip
	tbz	x20, 0, .L4
	str	w19, [x23]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Real8_CB_GetVLCBits, .-Real8_CB_GetVLCBits
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_GetImageBuffer
	.type	Real8_GetImageBuffer, %function
Real8_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 53248
	add	x19, x19, 8192
	bl	_mcount
	add	x19, x19, 3184
	add	x20, x19, 40960
	mov	w1, 1
	ldr	w0, [x21, 1816]
	bl	FSP_NewLogicFs
	str	w0, [x20, 2064]
	mov	w1, w0
	tbnz	w0, #31, .L14
	ldr	w0, [x21, 1816]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L15
	ldr	x1, .LC9
	mov	w0, 18
	ldr	w2, [x20, 2064]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L13
	ldr	x1, [x19, 40]
	cbz	x1, .L13
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC11
	bl	dprint_vfmw
	mov	w0, 1
.L10:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L13:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L14:
	ldr	x1, .LC5
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 2060]
	mov	w2, 1
	ldr	w0, [x21, 1816]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 2056]
	mov	w2, 1
	ldr	w0, [x21, 1816]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 2056]
	str	wzr, [x20, 2060]
	ldr	w0, [x21, 1816]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 2056]
	str	w0, [x20, 2060]
	add	x1, x21, 1208
	strb	wzr, [x19, 23]
	ldr	w0, [x21, 1816]
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L15:
	ldr	x1, .LC7
	mov	w2, 511
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L10
	.size	Real8_GetImageBuffer, .-Real8_GetImageBuffer
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_ArrangeVHBMem
	.type	Real8_ArrangeVHBMem, %function
Real8_ArrangeVHBMem:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x2
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldp	w3, w2, [x19, 112]
	cmp	w2, 1
	bls	.L18
	sub	w1, w3, #2
	mov	w0, 512
	cmp	w1, 510
	ccmp	w2, w0, 2, ls
	bhi	.L18
	ldr	x0, [x20]
	ldr	w1, [x0, 764]
	cbnz	w1, .L21
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L48
.L22:
	ldp	w23, w22, [x19, 104]
	mov	w25, 5
	mov	w21, 2
	mov	w24, 4
.L28:
	ldr	x0, .LC16
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x20]
	ldp	w1, w2, [x19, 104]
	stp	w22, w23, [x29, 92]
	ldr	w0, [x0, 28]
	stp	w2, w1, [x29, 100]
	cmp	w0, 24
	beq	.L34
	strb	w24, [x29, 89]
	sxtb	w0, w21
	strb	w25, [x29, 90]
.L38:
	add	x19, x20, 53248
	strb	w0, [x29, 91]
	add	x1, x29, 88
	ldr	w0, [x19, 1816]
	bl	FSP_ConfigInstance
	mov	w2, 0
	cbnz	w0, .L43
	ldr	x1, [x20]
	add	x3, x29, 84
	ldr	w0, [x19, 1816]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L49
	cbnz	w0, .L36
	add	x20, x20, 8192
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x20, 3204]
	b	.L43
	.p2align 3
.L18:
	ldr	x1, .LC13
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, w2
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L21:
	ldr	w1, [x0, 28]
	cmp	w1, 25
	bne	.L22
	ldr	w4, [x0, 724]
	ldp	w3, w2, [x19, 104]
	ldr	w5, [x0, 728]
	cmp	w2, w4
	bhi	.L31
	cmp	w3, w5
	bhi	.L31
	ldr	w4, [x0, 752]
	mov	w22, w2
	ldr	w1, [x0, 748]
	mov	w23, w3
	mov	w21, 1
	add	w24, w1, 2
	cbz	w4, .L33
.L46:
	add	w1, w1, w21
	mov	w21, 17
	cmp	w1, w21
	csel	w21, w1, w21, le
.L33:
	ldrsb	w25, [x0, 772]
	b	.L28
	.p2align 3
.L34:
	mov	w0, 1
	strb	w25, [x29, 90]
	strb	w0, [x29, 89]
	mov	w0, 1
	b	.L38
	.p2align 3
.L31:
	ldr	x1, .LC15
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L48:
	ldr	w22, [x0, 724]
	ldp	w3, w2, [x19, 104]
	cmp	w2, w22
	bhi	.L50
	ldr	w23, [x0, 728]
	cmp	w3, w23
	bhi	.L51
	add	x1, x20, 8192
	ldrb	w2, [x1, 3204]
	cmp	w2, 1
	beq	.L43
	ldr	w2, [x0, 752]
	mov	w21, 1
	ldr	w1, [x0, 748]
	add	w24, w1, 2
	cbnz	w2, .L46
	ldrsb	w25, [x0, 772]
	b	.L28
	.p2align 3
.L49:
	add	x0, x19, 1208
	bl	ResetVoQueue
.L36:
	ldr	x1, .LC18
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L51:
	mov	w5, w23
.L24:
	ldr	x1, .LC15
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
.L50:
	ldr	w5, [x0, 728]
	b	.L24
	.size	Real8_ArrangeVHBMem, .-Real8_ArrangeVHBMem
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetCPFMT
	.type	Real8_CB_GetCPFMT, %function
Real8_CB_GetCPFMT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 4
	mov	x0, x19
	bl	BsSkip
	strb	w20, [x21, 8]
	mov	w1, 9
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 9
	mov	x0, x19
	add	w20, w20, 1
	bl	BsSkip
	lsl	w20, w20, 2
	mov	w1, 1
	str	w20, [x21, 108]
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	beq	.L55
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L55:
	mov	w1, 9
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 9
	mov	x0, x19
	lsl	w22, w22, 2
	bl	BsSkip
	str	w22, [x21, 104]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real8_CB_GetCPFMT, .-Real8_CB_GetCPFMT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SetDimensions
	.type	Real8_CB_SetDimensions, %function
Real8_CB_SetDimensions:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x1, 96
	ldr	x0, [x19, 104]
	movk	x1, 0x80, lsl 32
	cmp	x0, x1
	beq	.L72
	mov	x1, 144
	movk	x1, 0xb0, lsl 32
	cmp	x0, x1
	beq	.L73
	mov	x1, 288
	movk	x1, 0x160, lsl 32
	cmp	x0, x1
	beq	.L74
	mov	x1, 576
	movk	x1, 0x2c0, lsl 32
	cmp	x0, x1
	beq	.L75
	mov	x1, 1152
	movk	x1, 0x580, lsl 32
	cmp	x0, x1
	beq	.L76
	ldr	w0, [x19, 108]
	add	x1, x19, 16
	mov	w2, 6
	add	w0, w0, 15
	lsr	w0, w0, 4
	str	w0, [x1, 28]
	ldr	w3, [x19, 104]
	add	w3, w3, 15
	lsr	w3, w3, 4
	str	w3, [x1, 24]
	mul	w0, w0, w3
	sub	w0, w0, #1
	cmp	w0, 47
	bls	.L58
	cmp	w0, 98
	bls	.L67
	cmp	w0, 395
	bls	.L68
	cmp	w0, 1583
	bls	.L69
.L71:
	mov	w3, 6335
	mov	w2, 14
	cmp	w0, w3
	bhi	.L58
	mov	w2, 4
	b	.L60
	.p2align 3
.L72:
	add	x1, x19, 16
	mov	w0, 6
	mov	w3, 8
	mov	w2, w0
	stp	w0, w3, [x1, 24]
.L58:
	str	w2, [x1, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L73:
	add	x1, x19, 16
	mov	w3, 11
	mov	w0, 9
	mov	w2, 1
	stp	w0, w3, [x1, 24]
.L60:
	ldr	x0, .LC19
	add	x0, x0, 256
	ldr	w2, [x0, w2, uxtw 2]
	str	w2, [x1, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L74:
	add	x1, x19, 16
	mov	w2, 22
	mov	w0, 18
	stp	w0, w2, [x1, 24]
.L68:
	mov	w2, 2
	b	.L60
	.p2align 3
.L76:
	add	x1, x19, 16
	mov	w3, 88
	mov	w2, 72
	mov	w0, 6335
	stp	w2, w3, [x1, 24]
	b	.L71
	.p2align 3
.L75:
	add	x1, x19, 16
	mov	w2, 44
	mov	w0, 36
	stp	w0, w2, [x1, 24]
.L69:
	mov	w2, 3
	b	.L60
.L67:
	mov	w2, 1
	b	.L60
	.size	Real8_CB_SetDimensions, .-Real8_CB_SetDimensions
	.align	3
.LC19:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetPicSize
	.type	Real8_CB_GetPicSize, %function
Real8_CB_GetPicSize:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x24, x2
	mov	x23, x3
	bl	_mcount
	ldr	x0, .LC21
	mov	w3, 180
	ldr	w1, [x20, 36]
	add	x2, x0, 280
	add	x0, x0, 312
	sub	w1, w1, #2
	str	w3, [x29, 64]
	cmp	w1, 1
	ldp	x4, x5, [x2]
	stp	x4, x5, [x29, 80]
	ldp	x4, x5, [x0]
	ldp	x2, x3, [x2, 16]
	stp	x4, x5, [x29, 112]
	ldp	x4, x5, [x0, 16]
	stp	x2, x3, [x29, 96]
	mov	w0, 576
	mov	w2, 360
	stp	x4, x5, [x29, 128]
	stp	w0, wzr, [x29, 72]
	str	w2, [x29, 68]
	bls	.L91
.L78:
	mov	w1, 3
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 3
	mov	x0, x19
	bl	BsSkip
	add	x0, x29, 144
	add	x20, x0, x20, uxtw 2
	ldr	w21, [x20, -64]
	cbz	w21, .L81
.L80:
	mov	w1, 3
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 3
	mov	x0, x19
	bl	BsSkip
	add	x0, x29, 144
	add	x0, x0, x22, uxtw 2
	ldr	w20, [x0, -32]
	cbz	w20, .L92
.L82:
	str	w21, [x24]
	str	w20, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L81:
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	add	w21, w21, w20, lsl 2
	bl	BsSkip
	cmp	w20, 255
	beq	.L81
	b	.L80
	.p2align 3
.L91:
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbz	w21, .L78
	ldr	w0, [x20, 68]
	str	w0, [x24]
	ldr	w0, [x20, 72]
	str	w0, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L92:
	mov	w1, 1
	mov	x0, x19
	lsl	w22, w22, 1
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	orr	w0, w20, w22
	add	x1, x29, 144
	ubfiz	x0, x0, 2, 2
	add	x0, x1, x0
	ldr	w20, [x0, -80]
	cbnz	w20, .L82
	.p2align 2
.L83:
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 8
	mov	x0, x19
	add	w20, w20, w22, lsl 2
	bl	BsSkip
	cmp	w22, 255
	beq	.L83
	b	.L82
	.size	Real8_CB_GetPicSize, .-Real8_CB_GetPicSize
	.align	3
.LC21:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_FindNextSliceStartCode
	.type	Real8_CB_FindNextSliceStartCode, %function
Real8_CB_FindNextSliceStartCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #2
	cmp	w21, wzr
	bgt	.L100
	b	.L97
	.p2align 3
.L103:
	bl	BsSkip
	cmp	w19, w21
	beq	.L97
.L100:
	mov	w1, 17
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L103
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L97:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real8_CB_FindNextSliceStartCode, .-Real8_CB_FindNextSliceStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SearchBits_IgnoreOnly0
	.type	Real8_CB_SearchBits_IgnoreOnly0, %function
Real8_CB_SearchBits_IgnoreOnly0:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w25, w1
	mov	w24, w3
	mov	w23, w2
	bl	_mcount
	sub	w2, w25, #1
	mov	w1, w25
	mov	x0, x21
	mov	w22, 1
	lsl	w22, w22, w2
	bl	BsShow
	mov	w19, w0
	mov	w1, w25
	mov	x0, x21
	bl	BsSkip
	cmp	w23, w19
	ccmp	w24, wzr, 4, ne
	beq	.L105
	tst	w22, w19
	bne	.L105
	ldr	x0, .LC24
	mov	w20, 0
	add	x0, x0, 344
	ldr	w25, [x0, w25, uxtw 2]
	b	.L106
	.p2align 3
.L107:
	tst	w22, w19
	bne	.L105
.L106:
	mov	w1, 1
	mov	x0, x21
	add	w20, w20, w1
	and	w19, w25, w19, lsl 1
	bl	BsShow
	mov	w2, w0
	mov	w1, 1
	mov	x0, x21
	orr	w19, w2, w19
	bl	BsSkip
	cmp	w23, w19
	ccmp	w24, w20, 0, ne
	bhi	.L107
.L105:
	cmp	w23, w19
	ldr	x25, [sp, 64]
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	Real8_CB_SearchBits_IgnoreOnly0, .-Real8_CB_SearchBits_IgnoreOnly0
	.align	3
.LC24:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SetRPRSizes
	.type	Real8_CB_SetRPRSizes, %function
Real8_CB_SetRPRSizes:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC26
	add	x6, x29, 56
	add	x1, x29, 96
	str	x21, [x19, 24]
	add	x0, x0, 448
	add	x1, x1, x20, uxtw 2
	str	w20, [x19, 32]
	ldp	x4, x5, [x0]
	stp	x4, x5, [x6]
	add	x4, x29, 72
	ldp	x2, x3, [x0, 16]
	ldr	w0, [x0, 32]
	stp	x2, x3, [x4]
	str	w0, [x29, 88]
	ldr	w0, [x1, -40]
	str	w0, [x19, 20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	Real8_CB_SetRPRSizes, .-Real8_CB_SetRPRSizes
	.align	3
.LC26:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetSSC
	.type	Real8_CB_GetSSC, %function
Real8_CB_GetSSC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 96]
	cmp	w0, 1
	beq	.L114
	mov	x0, x20
	bl	Real8_CB_FindNextSliceStartCode
	cmp	w0, wzr
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_CB_GetSSC, .-Real8_CB_GetSSC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetSliceHeader
	.type	Real8_CB_GetSliceHeader, %function
Real8_CB_GetSliceHeader:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x5
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	x22, x2
	mov	x24, x3
	mov	x23, x4
	bl	_mcount
	ldr	w0, [x19, 96]
	cmp	w0, 1
	beq	.L150
	cbz	w21, .L151
	str	wzr, [x22]
	mov	w0, -1
	mov	w19, 1
	str	w0, [x23]
.L141:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L150:
	cbnz	w21, .L152
	add	x21, x19, 16
	mov	w1, 3
	mov	x0, x20
	ldr	w26, [x21, 40]
	bl	BsShow
	mov	w25, w0
	mov	w1, 3
	mov	x0, x20
	bl	BsSkip
	cmp	w25, 7
	bhi	.L121
	ldr	x0, .LC28
	add	x0, x0, 488
	ldr	w0, [x0, w25, uxtw 2]
	cmp	w0, 2
	bhi	.L121
	cmn	w26, #1
	mov	w1, 2
	mov	x0, x20
	beq	.L153
	bl	BsShow
	mov	w25, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 36]
	cmp	w0, w25
	bne	.L121
.L123:
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cbnz	w25, .L121
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 5
	mov	x0, x20
	bl	BsSkip
	uxtb	w0, w25
	strb	w0, [x21, 2]
	cmp	w0, 31
	bhi	.L121
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w25, wzr
	mov	w1, 13
	cset	w0, ne
	cmn	w26, #1
	strb	w0, [x21, 1]
	mov	x0, x20
	bne	.L124
	bl	BsShow
	mov	w26, w0
	mov	w1, 13
	mov	x0, x20
	bl	BsSkip
	ldr	w25, [x21, 4]
	str	w26, [x21, 44]
	cbz	w25, .L142
	mov	w1, w25
	mov	x0, x20
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 56]
	ldr	x1, [x21, 8]
	cbz	x1, .L121
	lsl	w26, w26, 1
	mov	x0, x19
	add	w3, w26, 1
	ldr	w2, [x1, w26, uxtw 2]
	ldr	w1, [x1, w3, uxtw 2]
	stp	w2, w1, [x21, 60]
	stp	w1, w2, [x19, 104]
	bl	Real8_CB_SetDimensions
.L142:
	ldr	w25, [x21, 32]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 40]
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	strb	w25, [x19, 16]
	b	.L118
	.p2align 3
.L151:
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 1
	beq	.L154
.L121:
	mov	w19, 0
.L155:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L152:
	add	x21, x19, 16
.L118:
	ldr	w0, [x21, 40]
	mov	w19, 1
	str	w0, [x22]
	ldrb	w0, [x21, 2]
	str	w0, [x23]
	mov	w0, w19
	str	wzr, [x24]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L154:
	ldr	w25, [x19, 48]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x22]
	ldr	w0, [x19, 48]
	cmp	w0, 11
	bls	.L134
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, w21
	mov	x0, x20
	bl	BsSkip
	cmp	w19, 1
	bne	.L121
.L134:
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, 5
	mov	x0, x20
	bl	BsSkip
	str	w19, [x23]
	cmp	w19, 31
	bgt	.L121
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w19, 1
	bne	.L121
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w21, [x24]
	b	.L141
	.p2align 3
.L153:
	bl	BsShow
	mov	w25, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w25, [x21, 36]
	b	.L123
.L124:
	bl	BsShow
	mov	w25, w0
	mov	w1, 13
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 44]
	cmp	w0, w25
	bne	.L121
	ldr	w25, [x21, 4]
	cbz	w25, .L146
	mov	w1, w25
	mov	x0, x20
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 56]
	cmp	w0, w26
	bne	.L121
.L146:
	ldr	w25, [x21, 32]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 40]
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	ldrb	w0, [x19, 16]
	cmp	w0, w25
	beq	.L118
	mov	w19, 0
	b	.L155
	.size	Real8_CB_GetSliceHeader, .-Real8_CB_GetSliceHeader
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetPictureHeader
	.type	Real8_CB_GetPictureHeader, %function
Real8_CB_GetPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 96]
	cmp	w0, 1
	beq	.L183
	ldr	x3, .LC31
	mov	x2, 160
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w1, 24
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 24
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 1
	bne	.L175
	mov	x0, x20
	add	x1, x29, 60
	bl	Real8_CB_GetVLCBits
	cmp	w0, 30
	bls	.L175
	ldr	w0, [x29, 60]
	tbnz	x0, 0, .L175
	tbz	x0, 1, .L184
	stp	wzr, wzr, [x19, 104]
.L168:
	ubfx	x1, x0, 2, 5
	ubfx	x0, x0, 7, 8
	str	w1, [x19, 140]
	add	x1, x29, 60
	str	w0, [x19, 128]
	mov	x0, x20
	bl	Real8_CB_GetVLCBits
	cmp	w0, 1
	beq	.L179
	cmp	w0, 3
	beq	.L185
	cmp	w0, 5
	bne	.L175
	ldr	w0, [x29, 60]
	cbnz	w0, .L175
	mov	w0, 2
.L179:
	str	w0, [x19, 100]
.L170:
	ldr	w0, [x19, 108]
	cbz	w0, .L186
.L172:
	sub	w0, w0, #48
	mov	w1, 8144
	cmp	w0, w1
	bhi	.L175
.L182:
	ldr	w0, [x19, 104]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L175
	mov	x0, x19
	bl	Real8_CB_SetDimensions
	mov	w0, 1
.L158:
	ldp	w2, w1, [x19, 104]
	add	w1, w1, 15
	add	w2, w2, 15
	lsr	w2, w2, 4
	lsr	w1, w1, 4
	stp	w2, w1, [x19, 112]
	mul	w1, w1, w2
	str	w1, [x19, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L184:
	mov	w2, 176
	mov	w1, 144
	stp	w1, w2, [x19, 104]
	b	.L168
	.p2align 3
.L185:
	ldr	w0, [x29, 60]
	cmp	w0, 1
	beq	.L187
.L175:
	mov	w0, -2
.L189:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L183:
	add	x21, x19, 16
	mov	w0, -1
	mov	x5, x19
	add	x4, x29, 60
	add	x3, x29, 52
	add	x2, x29, 56
	str	w0, [x21, 40]
	mov	w1, 0
	mov	x0, x20
	bl	Real8_CB_GetSliceHeader
	cmp	w0, 1
	mov	w0, -2
	bne	.L158
	ldr	w0, [x21, 36]
	cmp	w0, 3
	bls	.L188
.L159:
	ldrb	w1, [x19, 16]
	str	w1, [x19, 132]
	mov	w1, 8144
	ldr	w0, [x19, 108]
	ldrb	w2, [x21, 1]
	str	w2, [x19, 136]
	sub	w0, w0, #48
	cmp	w0, w1
	ldrb	w0, [x21, 2]
	str	w0, [x19, 140]
	ldr	w0, [x21, 44]
	str	w0, [x19, 128]
	ldr	w0, [x21, 48]
	str	w0, [x19, 148]
	ldr	w0, [x21, 52]
	str	w0, [x19, 152]
	bls	.L182
	mov	w0, -2
	b	.L189
	.p2align 3
.L186:
	mov	x1, x19
	mov	x0, x20
	bl	Real8_CB_GetCPFMT
	cbz	w0, .L175
	ldr	w0, [x19, 108]
	b	.L172
	.p2align 3
.L188:
	ldr	x1, .LC30
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx161
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx161:
	.section	.rodata
	.align	0
	.align	2
.L161:
	.byte	(.L160 - .Lrtx161) / 4
	.byte	(.L162 - .Lrtx161) / 4
	.byte	(.L163 - .Lrtx161) / 4
	.byte	(.L164 - .Lrtx161) / 4
	.text
	.p2align 3
.L187:
	str	wzr, [x19, 100]
	b	.L170
.L163:
	mov	w0, 1
	str	w0, [x19, 100]
	b	.L159
.L162:
	str	wzr, [x19, 100]
	str	wzr, [x21, 20]
	b	.L159
.L160:
	str	wzr, [x19, 100]
	mov	w0, 1
	str	w0, [x21, 20]
	b	.L159
.L164:
	mov	w0, 2
	str	w0, [x19, 100]
	b	.L159
	.size	Real8_CB_GetPictureHeader, .-Real8_CB_GetPictureHeader
	.align	3
.LC30:
	.xword	.L161
	.align	3
.LC31:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_SetImgFormat
	.type	Real8_SetImgFormat, %function
Real8_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 53248
	bl	_mcount
	mov	x1, 52336
	add	x1, x21, x1
	ldr	w0, [x20, 1816]
	ldr	w1, [x1, 2064]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L190
	ldr	w3, [x20, -132]
	mov	w5, 5
	ldrb	w2, [x0, 64]
	mov	w4, 1
	ldrb	w1, [x0, 65]
	bfi	w2, w3, 0, 2
	and	w3, w3, 3
	and	w1, w1, -4
	and	w2, w2, -29
	orr	w1, w1, 12
	bfi	w2, w5, 5, 3
	bfi	w1, w4, 4, 2
	strb	w2, [x0, 64]
	strb	w1, [x0, 65]
	mov	w1, 0
	ldr	w2, [x0, 64]
	and	w2, w2, -114689
	str	w2, [x0, 64]
	lsr	w2, w2, 16
	ldrb	w4, [x20, -232]
	bfi	w2, w4, 1, 1
	strb	w2, [x0, 66]
	ldr	w2, [x20, -228]
	str	w2, [x0, 120]
	stp	wzr, w3, [x0, 52]
	str	w3, [x0, 60]
	ldr	w2, [x20, -124]
	str	w2, [x0, 68]
	ldr	w2, [x20, -128]
	str	w2, [x0, 72]
	bl	SetAspectRatio
	ldr	x0, [x21]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L196
.L192:
	mov	w1, 1
	strb	w1, [x19, 291]
	strb	w1, [x19, 289]
	add	x1, x19, 256
	strb	wzr, [x19, 284]
	mov	w0, 8
	stp	w0, w0, [x1, 40]
	stp	w0, w0, [x1, 48]
.L190:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L196:
	ldr	w1, [x19, 72]
	ldr	w3, [x19, 112]
	add	w1, w1, 15
	ldr	w2, [x19, 36]
	lsl	w0, w3, 4
	lsr	w1, w1, 4
	ldr	x4, [x19, 504]
	add	w5, w3, w2
	mul	w0, w1, w0
	add	w1, w0, w2
	str	w1, [x19, 40]
	add	w3, w3, w1
	add	x0, x4, x0, sxtw
	stp	w2, w1, [x19, 20]
	stp	w5, w3, [x19, 28]
	str	x0, [x19, 512]
	b	.L192
	.size	Real8_SetImgFormat, .-Real8_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RV8_RecordVFMWState
	.type	RV8_RecordVFMWState, %function
RV8_RecordVFMWState:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	RV8_RecordVFMWState, .-RV8_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WriteSliceMsg
	.type	Real8_WriteSliceMsg, %function
Real8_WriteSliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	add	x3, x19, 53248
	lsl	x2, x0, 2
	add	x19, x19, 16
	sub	x2, x2, x0
	add	w20, w20, 1
	lsl	x2, x2, 2
	sub	x2, x2, x0
	ldr	w0, [x3, -44]
	add	x2, x19, x2, lsl 2
	str	w0, [x2, 96]
	ldr	w0, [x3, -52]
	str	w0, [x2, 104]
	ldr	w0, [x3, -48]
	str	w0, [x2, 112]
	ldr	w0, [x3, -32]
	str	w0, [x2, 100]
	ldr	w0, [x3, -40]
	str	w0, [x2, 108]
	ldr	w0, [x3, -36]
	str	w0, [x2, 116]
	ldr	w0, [x3, -64]
	str	w0, [x2, 120]
	ldr	w0, [x3, -68]
	str	w0, [x2, 124]
	ldr	w0, [x3, -72]
	str	w0, [x2, 128]
	ldr	w0, [x3, -60]
	str	w0, [x2, 132]
	str	w20, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WriteSliceMsg, .-Real8_WriteSliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WritePicMsg
	.type	Real8_WritePicMsg, %function
Real8_WritePicMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 53248
	mov	x0, 52336
	add	x0, x19, x0
	ldr	w3, [x2, -132]
	strb	w3, [x19, 28]
	cmp	w3, 2
	ldr	w3, [x2, -116]
	str	w3, [x19, 20]
	ldr	w3, [x2, -120]
	str	w3, [x19, 24]
	ldr	w3, [x0, 1980]
	str	w3, [x19, 32]
	ldr	w3, [x0, 1984]
	str	w3, [x19, 36]
	ldr	w2, [x2, -92]
	str	w2, [x19, 40]
	ldr	w3, [x0, 884]
	str	w3, [x19, 44]
	ldr	w3, [x0, 888]
	str	w3, [x19, 48]
	beq	.L199
	str	w2, [x0, 884]
.L199:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WritePicMsg, .-Real8_WritePicMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WriteReg
	.type	Real8_WriteReg, %function
Real8_WriteReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	str	w20, [x19, 56]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WriteReg, .-Real8_WriteReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_ModifySliceMsg
	.type	Real8_ModifySliceMsg, %function
Real8_ModifySliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16
	ldr	w1, [x0, 132]
	cbnz	w1, .L209
	ldp	w1, w4, [x0, 4]
	ldr	w5, [x0, 36]
	mul	w4, w1, w4
	cmp	w5, 2
	sub	w4, w4, #1
	bhi	.L231
.L208:
	cmp	w5, 1
	bls	.L213
	sub	w7, w5, #1
	mov	w3, 0
	b	.L214
	.p2align 3
.L215:
	add	w3, w3, 1
	lsl	x1, x1, 2
	sub	x1, x1, x2
	sxtw	x6, w3
	lsl	x2, x6, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	ldr	w6, [x1, 132]
	add	x1, x0, x2, lsl 2
	ldr	w1, [x1, 132]
	cmp	w6, w1
	bge	.L209
.L214:
	sxtw	x2, w3
	cmp	w3, w7
	lsl	x1, x2, 2
	sub	x1, x1, x2
	bne	.L215
	uxtw	x3, w3
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x3, x1, x3
	add	x3, x0, x3, lsl 2
	ldr	w1, [x3, 132]
	cmp	w4, w1
	ccmp	w1, wzr, 4, ge
	ble	.L209
.L213:
	cbz	w5, .L216
	sub	w9, w5, #1
	mov	w8, 0
	mov	x10, 44
	b	.L219
	.p2align 3
.L234:
	beq	.L232
.L219:
	add	w3, w8, 1
	sxtw	x7, w8
	lsl	x2, x7, 2
	cmp	w8, w9
	sxtw	x6, w3
	sub	x2, x2, x7
	lsl	x3, x6, 2
	lsl	x2, x2, 2
	sub	x3, x3, x6
	sub	x2, x2, x7
	lsl	x3, x3, 2
	beq	.L233
	sub	x3, x3, x6
	add	x2, x0, x2, lsl 2
	add	x3, x0, x3, lsl 2
	ldr	w3, [x3, 132]
	sub	w3, w3, #1
	str	w3, [x2, 136]
.L218:
	lsl	x1, x7, 2
	add	w8, w8, 1
	sub	x1, x1, x7
	lsl	x1, x1, 2
	sub	x1, x1, x7
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 132]
	cmp	w2, w3
	ccmp	w3, wzr, 1, le
	cset	w1, lt
	cmp	w2, wzr
	ccmp	w4, w2, 1, ge
	cset	w2, lt
	cmp	w4, w3
	cset	w3, lt
	orr	w1, w1, w2
	orr	w1, w3, w1
	cmp	w8, w5
	cbz	w1, .L234
	.p2align 2
.L209:
	mov	w0, 0
.L229:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L231:
	ldr	w1, [x0, 176]
	sub	w6, w5, #1
	mov	w2, 1
	cmp	w4, w1
	ccmp	w1, wzr, 4, gt
	bgt	.L211
	b	.L209
	.p2align 3
.L212:
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x1, x1, x3
	add	x1, x0, x1, lsl 2
	ldr	w1, [x1, 132]
	cmp	w1, wzr
	ccmp	w4, w1, 4, gt
	ble	.L209
.L211:
	add	w2, w2, 1
	cmp	w2, w6
	sxtw	x3, w2
	lsl	x1, x3, 2
	bne	.L212
	b	.L208
.L232:
	ldr	w3, [x0, 96]
	mov	w6, 0
	mov	x4, 0
	mov	w2, w3
	b	.L222
	.p2align 3
.L235:
	ldr	w2, [x2, 96]
.L222:
	lsl	x1, x4, 2
	add	w6, w6, 1
	sub	x1, x1, x4
	cmp	w3, w2
	lsl	x1, x1, 2
	csel	w3, w3, w2, ls
	sub	x1, x1, x4
	sxtw	x4, w6
	lsl	x2, x4, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x4
	lsl	x2, x2, 2
	sub	x2, x2, x4
	ldr	w7, [x1, 100]
	add	x2, x0, x2, lsl 2
	cmp	w7, w3
	bcs	.L220
	ldr	w1, [x1, 116]
	cmp	w1, wzr
	csel	w3, w3, w7, eq
.L220:
	cmp	w6, w5
	bne	.L235
	and	w3, w3, -16
	mov	w6, 0
	str	w3, [x0, 44]
	b	.L226
	.p2align 3
.L236:
	ldr	w2, [x1, 104]
	ldr	w7, [x1, 96]
	mov	x4, x2
	add	w2, w7, w2, lsr 3
	and	w4, w4, 7
	sub	w3, w2, w3
	ubfiz	w2, w3, 3, 4
	and	w3, w3, -16
	add	w2, w2, w4
	str	w3, [x1, 96]
	str	w2, [x1, 104]
.L224:
	add	w6, w6, 1
	cmp	w5, w6
	bls	.L225
	ldr	w3, [x0, 44]
.L226:
	sxtw	x2, w6
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 100]
	cbz	w2, .L236
	ldp	w4, w2, [x1, 104]
	ldp	w10, w9, [x1, 96]
	mov	x7, x2
	mov	x8, x4
	add	w2, w9, w2, lsr 3
	add	w4, w10, w4, lsr 3
	sub	w4, w4, w3
	sub	w3, w2, w3
	ubfiz	w10, w4, 3, 4
	ubfiz	w9, w3, 3, 4
	and	w2, w7, 7
	and	w8, w8, 7
	and	w4, w4, -16
	add	w7, w10, w8
	and	w3, w3, -16
	add	w2, w9, w2
	stp	w4, w3, [x1, 96]
	stp	w7, w2, [x1, 104]
	b	.L224
.L216:
	ldr	w1, [x0, 96]
	and	w1, w1, -16
	str	w1, [x0, 44]
.L225:
	mov	w0, 1
	b	.L229
.L233:
	madd	x1, x7, x10, x0
	mov	w3, w4
	str	w4, [x1, 136]
	b	.L218
	.size	Real8_ModifySliceMsg, .-Real8_ModifySliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Init
	.type	REAL8DEC_Init, %function
REAL8DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x20, 53248
	bl	_mcount
	ldr	x3, .LC32
	mov	x2, 55080
	mov	w1, 0
	mov	x0, x20
	ldr	w22, [x19, 1808]
	ldr	x3, [x3, 96]
	blr	x3
	str	w22, [x19, 1808]
	add	x0, x19, 1208
	bl	ResetVoQueue
	str	x21, [x20]
	add	x1, x20, 8192
	mov	w4, 15
	add	x1, x1, 3184
	mov	w2, 1
	add	x3, x1, 40960
	mov	w5, 8192
	mov	x0, x20
	str	w4, [x3, 884]
	str	w4, [x3, 888]
	ldr	w3, [x21, 8]
	strb	w3, [x1, 18]
	strb	wzr, [x1, 20]
	strb	w2, [x19, -224]
	str	w2, [x19, -136]
	str	w5, [x19, -108]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 1816]
	beq	.L240
	mov	w0, 0
.L238:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L240:
	ldr	x1, .LC34
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L238
	.size	REAL8DEC_Init, .-REAL8DEC_Init
	.align	3
.LC32:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC34:
	.xword	.LC33
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Destroy
	.type	REAL8DEC_Destroy, %function
REAL8DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, 52336
	ldr	x1, .LC36
	add	x2, x19, x0
	mov	w0, 2
	ldr	w2, [x2, 1956]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_Destroy, .-REAL8DEC_Destroy
	.align	3
.LC36:
	.xword	.LC35
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Decode
	.type	REAL8DEC_Decode, %function
REAL8DEC_Decode:
	stp	x29, x30, [sp, -416]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	add	x20, x21, 53248
	bl	_mcount
	add	x24, x21, 16
	add	x4, x29, 256
	add	x0, x29, 336
	add	x6, x29, 256
	mov	w3, 8192
	ldp	w2, w1, [x20, -156]
	stp	xzr, xzr, [x4]
	add	x4, x29, 272
	str	w3, [x20, -108]
	stp	xzr, xzr, [x0]
	add	x0, x29, 320
	stp	xzr, xzr, [x4]
	add	x4, x29, 288
	stp	xzr, xzr, [x0]
	add	x0, x29, 352
	stp	xzr, xzr, [x4]
	add	x4, x29, 304
	stp	xzr, xzr, [x0]
	add	x0, x29, 368
	stp	xzr, xzr, [x4]
	add	x4, x29, 384
	stp	xzr, xzr, [x0]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x4]
	add	x4, x29, 400
	mov	w0, 1
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x29, 224]
	stp	xzr, xzr, [x4]
	stp	xzr, xzr, [x29, 240]
	stp	w2, w1, [x20, -148]
	str	w0, [x20, -136]
	stp	w2, w1, [x6, 76]
	stp	w2, w1, [x6, 84]
	str	w0, [x29, 352]
	str	w3, [x29, 380]
	cbz	x19, .L369
	ldr	x26, .LC41
	mov	w1, 0
	mov	x2, 11360
	mov	x0, x24
	add	x23, x21, 8192
	ldr	x3, [x26, 96]
	blr	x3
	add	x1, x23, 3184
	add	x0, x1, 40960
	str	wzr, [x0, 1920]
	ldr	w2, [x19, 20]
	str	w2, [x0, 1940]
	ldr	w2, [x19, 16]
	str	w2, [x0, 1924]
	ldr	x2, [x19]
	str	x2, [x21, 11376]
	ldr	w2, [x19, 20]
	str	w2, [x0, 1928]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 16]
	ldrb	w3, [x19, 10]
	cmp	w3, 1
	beq	.L245
	ldr	w3, [x19, 104]
	str	w3, [x0, 1932]
	ldr	x3, [x19, 88]
	str	x3, [x1, 8]
	ldr	w3, [x19, 108]
	str	w3, [x0, 1936]
	ldrb	w0, [x19, 98]
	strb	w0, [x1, 17]
	ldrb	w0, [x19, 98]
	cmp	w0, 1
	bne	.L370
	mov	w0, 65460
	sub	w1, w2, #75
	movk	w0, 0x2f, lsl 16
	cmp	w1, w0
	bhi	.L248
.L247:
	ldr	x1, [x21, 11376]
	cbz	x1, .L248
	add	x19, x20, 1168
	mov	x0, x19
	bl	BsInit
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 8
	mov	x0, x19
	str	w22, [x29, 120]
	bl	BsSkip
	cmp	w22, 8
	bhi	.L248
	mov	x25, 0
	add	x22, x29, 192
	.p2align 2
.L249:
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 32
	mov	x0, x19
	rev	w27, w27
	bl	BsSkip
	str	w27, [x22, x25]
	add	x25, x25, 4
	cmp	x25, 64
	bne	.L249
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w25, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	add	w0, w25, 1
	cmp	w25, 255
	add	x25, x23, 3184
	mov	w2, w0
	add	x27, x25, 40960
	str	w0, [x27, 892]
	bhi	.L248
	cbz	w0, .L250
	stp	x27, x25, [x29, 128]
	mov	w28, 3145727
	mov	w27, 0
	b	.L251
	.p2align 3
.L371:
	ldr	x0, [x29, 128]
	ldr	w2, [x0, 892]
	cmp	w2, w27
	bls	.L250
.L251:
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w25, w0
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	uxtw	x1, w27
	ldr	x2, [x29, 136]
	add	x1, x1, 8192
	rev	w0, w25
	add	x1, x1, 2272
	cmp	w0, w28
	add	w27, w27, 1
	str	w0, [x2, x1, lsl 2]
	ble	.L371
	.p2align 2
.L248:
	mov	w22, 0
.L359:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L370:
	ldr	w1, [x19, 24]
	mov	w22, 0
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 112]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L245:
	str	wzr, [x0, 1932]
	str	xzr, [x1, 8]
	str	wzr, [x0, 1936]
	mov	w0, 65460
	strb	wzr, [x1, 17]
	movk	w0, 0x2f, lsl 16
	sub	w1, w2, #75
	cmp	w1, w0
	bls	.L247
	b	.L248
	.p2align 3
.L369:
	mov	x2, 52336
	ldr	x1, .LC40
	add	x21, x21, x2
	mov	w22, 0
	ldr	w2, [x21, 1956]
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L250:
	add	x9, x21, 49152
	sub	w5, w2, #1
	add	x3, x9, 4080
	mov	w1, 0
	b	.L252
	.p2align 3
.L253:
	add	x0, x0, 8192
	ldr	w4, [x3], 4
	add	x0, x23, x0, lsl 2
	ldr	w0, [x0, 12272]
	cmp	w0, w4
	ble	.L248
.L252:
	cmp	w1, w5
	add	w0, w1, 1
	mov	x1, x0
	bne	.L253
	add	x28, x23, 3184
	lsl	w2, w2, 3
	add	x0, x28, 40960
	add	w25, w2, 66
	mov	w2, 65461
	mov	w1, 3145727
	movk	w2, 0x2f, lsl 16
	str	x9, [x29, 136]
	ldr	w27, [x0, 896]
	add	w27, w25, w27
	sub	w3, w27, #74
	cmp	w3, w2
	ccmp	w25, w1, 0, ls
	bgt	.L248
	ldr	w2, [x0, 1928]
	sub	w2, w2, w27
	cmp	w2, wzr
	ble	.L248
	ldr	x1, [x21, 11376]
	mov	x0, x19
	add	x1, x1, x27, sxtw
	bl	BsInit
	str	x22, [x29, 280]
	ldr	w0, [x29, 120]
	add	x1, x29, 416
	ldr	x3, .LC42
	add	x6, x29, 152
	str	w0, [x29, 288]
	add	x2, x1, x0, uxtw 2
	add	x3, x3, 448
	ldr	w0, [x3, 32]
	sub	x2, x2, #4096
	str	w0, [x29, 184]
	add	x1, x29, 256
	ldp	x4, x5, [x3]
	stp	x4, x5, [x6]
	ldp	x4, x5, [x3, 16]
	add	x3, x29, 168
	mov	x0, x19
	stp	x4, x5, [x3]
	ldr	w2, [x2, 3832]
	str	w2, [x29, 276]
	bl	Real8_CB_GetPictureHeader
	cmp	w0, 1
	mov	w22, w0
	ldr	x9, [x29, 136]
	bne	.L372
	ldrb	w0, [x28, 20]
	cbnz	w0, .L255
	ldr	x28, .LC45
	ldr	x4, [x28]
	cbz	x4, .L256
	ldr	w0, [x20, -116]
	mov	w3, 8
	strh	w0, [x29, 152]
	add	x2, x29, 152
	ldr	w0, [x20, -120]
	mov	w1, 2
	strh	w0, [x29, 154]
	ldr	w0, [x29, 372]
	strh	w0, [x29, 156]
	ldr	w0, [x29, 368]
	strh	w0, [x29, 158]
	ldr	w0, [x20, 1816]
	str	x9, [x29, 136]
	blr	x4
	ldr	x9, [x29, 136]
.L256:
	ldr	w0, [x20, 1816]
	str	x9, [x29, 136]
	bl	FSP_GetFspType
	ldr	x9, [x29, 136]
	cbnz	w0, .L257
	ldr	w0, [x20, 1816]
	add	x2, x29, 148
	add	x3, x29, 152
	add	x1, x29, 144
	stp	wzr, wzr, [x29, 144]
	str	wzr, [x29, 152]
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x21]
	ldr	x9, [x29, 136]
	ldr	w2, [x0, 764]
	cmp	w2, 1
	beq	.L373
.L257:
	add	x4, x23, 3184
	add	x1, x20, 1208
	add	x28, x4, 40960
	ldr	w0, [x20, 1816]
	stp	x1, x9, [x29, 120]
	mov	w2, 1
	str	x4, [x29, 136]
	ldr	w1, [x28, 2060]
	bl	FSP_ClearLogicFs
	ldr	w1, [x28, 2056]
	mov	w2, 1
	ldr	w0, [x20, 1816]
	bl	FSP_ClearLogicFs
	str	wzr, [x28, 2056]
	str	wzr, [x28, 2060]
	ldr	w0, [x20, 1816]
	bl	FSP_GetNullLogicFs
	str	w0, [x28, 2056]
	ldr	x4, [x29, 136]
	add	x1, x20, 1208
	str	w0, [x28, 2060]
	strb	wzr, [x4, 23]
	ldr	w0, [x20, 1816]
	bl	FSP_ClearNotInVoQueue
	ldr	w2, [x29, 372]
	ldr	w3, [x29, 368]
	cmp	w2, 512
	ldp	x9, x4, [x29, 128]
	bhi	.L264
	ldr	w0, [x29, 368]
	cmp	w0, 512
	mov	w3, w0
	bhi	.L264
	ldr	x1, [x21]
	ldr	w3, [x1, 764]
	cbnz	w3, .L266
	ldr	w1, [x1, 28]
	cmp	w1, 25
	beq	.L374
.L266:
	ldr	w0, [x20, 1816]
	str	x9, [x29, 136]
	bl	FSP_GetFspType
	ldr	x9, [x29, 136]
	cbz	w0, .L360
	ldr	w0, [x29, 368]
	ldr	w2, [x29, 372]
.L268:
	ldr	x1, .LC51
	mov	w3, w0
	mov	w0, 1
	str	x9, [x29, 136]
	bl	dprint_vfmw
	add	x2, x29, 256
	mov	x1, x21
	mov	w0, 6
	bl	Real8_ArrangeVHBMem
	ldr	x9, [x29, 136]
	cbz	w0, .L375
.L255:
	ldr	x3, [x26, 104]
	add	x0, x9, 3864
	add	x1, x29, 256
	mov	x2, 160
	str	x0, [x29, 112]
	add	x26, x23, 3184
	blr	x3
	ldr	x0, [x21]
	ldr	w0, [x0, 8]
	strb	w0, [x23, 3202]
	mov	x0, x21
	bl	Real8_GetImageBuffer
	cbz	w0, .L376
	add	x28, x26, 40960
	ldr	w0, [x20, 1816]
	ldr	w1, [x28, 2064]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L271
	ldr	x0, [x21]
	mov	x4, -1
	ldr	x1, .LC57
	ldr	x0, [x0, 56]
	str	x0, [x2, 584]
	mov	w0, 29
	ldr	x3, [x21]
	ldr	x3, [x3, 72]
	str	x3, [x2, 592]
	ldr	x3, [x21]
	ldr	x3, [x3, 88]
	str	x3, [x2, 600]
	ldr	x3, [x21]
	ldr	w3, [x3, 104]
	str	w3, [x2]
	ldr	x3, [x21]
	ldr	w3, [x3, 108]
	str	w3, [x2, 4]
	ldr	x3, [x21]
	ldr	w3, [x3, 112]
	str	w3, [x2, 8]
	ldr	x3, [x21]
	ldr	w3, [x3, 128]
	str	w3, [x2, 12]
	ldr	x3, [x21]
	str	x4, [x3, 56]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
	ldr	w0, [x20, -132]
	cmp	w0, 2
	beq	.L377
	cmp	w0, 1
	beq	.L378
	ldrb	w0, [x26, 23]
	cmp	w0, wzr
	mov	w0, 2
	csinc	w0, w0, wzr, ne
.L275:
	add	x26, x23, 3184
	strb	w0, [x23, 3207]
	add	x26, x26, 40960
	ldr	w2, [x26, 2056]
	ldr	w0, [x26, 2060]
	cmp	w2, w0
	beq	.L276
	ldr	x1, .LC59
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x20, 1816]
	mov	w2, 0
	ldr	w1, [x26, 2056]
	bl	FSP_SetRef
.L276:
	add	x28, x23, 3184
	mov	w2, 1
	add	x26, x28, 40960
	ldr	w0, [x26, 2060]
	ldr	w1, [x26, 2064]
	str	w1, [x26, 2060]
	str	w0, [x26, 2056]
	ldr	w0, [x20, 1816]
	bl	FSP_SetRef
	ldr	w0, [x20, 1816]
	ldr	w1, [x26, 2056]
	bl	FSP_RemovePmv
	ldr	x1, .LC61
	mov	w0, 13
	ldr	w2, [x26, 2064]
	bl	dprint_vfmw
	ldrb	w0, [x23, 3202]
	cmp	w0, 4
	bne	.L278
	ldr	w0, [x20, -132]
	cbnz	w0, .L281
	str	wzr, [x26, 2072]
.L278:
	add	x28, x23, 3184
	ldr	w0, [x20, 1816]
	add	x28, x28, 40960
	ldr	w1, [x28, 2064]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	w1, [x28, 2056]
	ldr	w0, [x20, 1816]
	bl	FSP_GetLogicFs
	mov	x9, x0
	ldr	w1, [x28, 2060]
	ldr	w0, [x20, 1816]
	str	x9, [x29, 136]
	bl	FSP_GetLogicFs
	mov	x28, x0
	ldr	x9, [x29, 136]
	cmp	x26, xzr
	ccmp	x9, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L379
	ldr	x0, [x26, 32]
	cbz	x0, .L285
	ldr	x1, [x26, 40]
	cbz	x1, .L285
	ldr	x1, [x28, 32]
	cbz	x1, .L287
	ldr	w5, [x1, 8]
.L288:
	str	w5, [x24, 48]
	ldr	x0, [x9, 32]
	cbz	x0, .L380
.L363:
	ldr	w4, [x0, 8]
	str	w4, [x24, 52]
	ldr	x1, .LC68
	ldr	x0, [x26, 32]
	str	x9, [x29, 136]
	ldr	w2, [x0, 8]
	mov	w0, 13
	str	w2, [x24, 56]
	ldr	w6, [x26, 8]
	str	w6, [x24, 68]
	ldr	w7, [x28, 8]
	str	w7, [x24, 72]
	ldr	x3, [x26, 40]
	ldr	w3, [x3, 8]
	str	w3, [x24, 60]
	bl	dprint_vfmw
	ldr	x0, [x26, 40]
	ldr	x9, [x29, 136]
	ldr	w0, [x0, 24]
	str	w0, [x24, 64]
	ldr	x0, [x26, 40]
	ldr	w0, [x0, 60]
	str	w0, [x24, 84]
	ldr	x0, [x26, 40]
	ldr	w0, [x0, 44]
	str	w0, [x24, 88]
	ldr	x0, [x26, 40]
	ldr	w0, [x0, 48]
	str	w0, [x24, 92]
	ldr	w0, [x20, -132]
	cmp	w0, 2
	beq	.L381
.L291:
	ldr	w0, [x20, -104]
	str	w0, [x26, 16]
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w1, [x20, -132]
	ldr	w2, [x20, -92]
	strb	w1, [x24, 12]
	cmp	w1, 2
	str	w2, [x29, 136]
	ldr	w1, [x20, -116]
	str	w1, [x24, 4]
	ldr	w1, [x20, -120]
	str	w1, [x24, 8]
	ldr	w1, [x0, 1980]
	str	w1, [x24, 16]
	ldr	w1, [x0, 1984]
	stp	w1, w2, [x24, 20]
	ldr	w1, [x0, 884]
	str	w1, [x24, 28]
	ldr	w1, [x0, 888]
	str	w1, [x24, 32]
	beq	.L296
	str	w2, [x0, 884]
.L296:
	mov	x0, x19
	bl	BsPos
	and	w1, w0, -2147483641
	tbnz	w0, #31, .L382
.L297:
	str	w1, [x20, -52]
	add	x1, x23, 3184
	add	x1, x1, 40960
	ldr	w0, [x1, 892]
	cmp	w0, 1
	beq	.L383
	ldr	w26, [x1, 896]
	ldr	w0, [x1, 900]
.L364:
	sub	w26, w0, w26
	mov	x0, x19
	lsl	w26, w26, 3
	bl	BsPos
	sub	w0, w26, w0
	add	x26, x23, 3184
	str	w0, [x20, -48]
	add	x9, x26, 40960
	mov	x0, x19
	str	x9, [x29, 128]
	ldr	w1, [x9, 1924]
	add	w27, w27, w1
	bl	BsPos
	str	wzr, [x20, -32]
	mov	w1, 8
	ldr	w2, [x20, -96]
	ldr	w3, [x29, 136]
	mov	w7, 1
	sdiv	w0, w0, w1
	ldr	w1, [x20, -88]
	str	w3, [x20, -72]
	stp	w2, wzr, [x20, -64]
	stp	wzr, wzr, [x20, -40]
	str	w1, [x20, -68]
	add	w0, w0, w27
	str	w0, [x20, -44]
	str	w0, [x24, 96]
	ldr	x9, [x29, 128]
	ldr	w0, [x20, -52]
	str	w0, [x24, 104]
	ldr	w0, [x20, -48]
	stp	wzr, w0, [x24, 108]
	str	w7, [x24, 36]
	str	wzr, [x24, 100]
	stp	wzr, w2, [x24, 116]
	str	w1, [x24, 124]
	str	wzr, [x24, 132]
	str	w3, [x24, 128]
	ldr	w0, [x9, 892]
	cmp	w0, w7
	bls	.L319
	ldr	w6, [x9, 900]
	mov	w0, 3145727
	add	w6, w25, w6
	cmp	w6, w0
	bgt	.L305
	cmp	w6, 73
	ble	.L305
	ldr	w2, [x9, 1928]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L305
	mov	w28, w7
	mov	x27, x9
	str	w0, [x29, 108]
	str	w7, [x29, 120]
	b	.L308
	.p2align 3
.L309:
	ldr	w0, [x27, 892]
	add	w28, w28, 1
	cmp	w0, w28
	bls	.L319
	uxtw	x0, w28
	add	x0, x0, 8192
	add	x0, x0, 2272
	ldr	w6, [x26, x0, lsl 2]
	ldr	w0, [x29, 108]
	add	w6, w25, w6
	cmp	w6, w0
	bgt	.L305
	cmp	w6, 73
	ble	.L305
	ldr	w2, [x27, 1928]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L305
.L308:
	ldr	x1, [x26]
	mov	x0, x19
	str	w6, [x29, 128]
	add	x1, x1, x6, sxtw
	bl	BsInit
	ldr	x5, [x29, 112]
	add	x2, x29, 144
	add	x4, x29, 152
	add	x3, x29, 148
	mov	w1, 0
	mov	x0, x19
	bl	Real8_CB_GetSliceHeader
	cmp	w0, 1
	mov	w2, w0
	ldr	w6, [x29, 128]
	bne	.L309
	ldr	w1, [x29, 144]
	ldr	w0, [x20, -116]
	str	w1, [x29, 128]
	cbz	w0, .L384
	ldr	w0, [x29, 152]
	ldr	w1, [x29, 136]
	cmp	w0, wzr
	str	w6, [x29, 104]
	csel	w0, w1, w0, lt
	str	w0, [x29, 136]
	mov	x0, x19
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	ldr	w6, [x29, 104]
	add	w0, w0, w1
	and	w0, w0, 7
	sub	w0, w0, w1
	str	w0, [x20, -52]
	ldr	w0, [x27, 892]
	sub	w0, w0, #1
	cmp	w0, w28
	beq	.L385
	cmp	w28, 254
	bhi	.L386
	add	w0, w28, 1
	uxtw	x1, w28
	add	x0, x0, 8192
	add	x1, x1, 8192
	add	x0, x0, 2272
	add	x1, x1, 2272
	str	w6, [x29, 100]
	ldr	w0, [x26, x0, lsl 2]
	ldr	w1, [x26, x1, lsl 2]
.L365:
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w1, w1, 3
	str	w1, [x29, 104]
	bl	BsPos
	ldp	w6, w1, [x29, 100]
	sub	w0, w1, w0
	str	w0, [x20, -48]
	ldr	w0, [x27, 1924]
	add	w6, w6, w0
	mov	x0, x19
	str	w6, [x29, 104]
	bl	BsPos
	cmp	w0, wzr
	ldr	w1, [x29, 128]
	str	w1, [x20, -60]
	ldr	w1, [x29, 136]
	str	w1, [x20, -72]
	ldr	w1, [x29, 120]
	ldr	w6, [x29, 104]
	stp	wzr, wzr, [x20, -40]
	sxtw	x2, w1
	add	w1, w1, 1
	mov	w3, w1
	lsl	x1, x2, 2
	sub	x1, x1, x2
	str	wzr, [x20, -32]
	lsl	x1, x1, 2
	str	w3, [x29, 120]
	sub	x1, x1, x2
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	ldr	w2, [x20, -88]
	add	x1, x24, x1, lsl 2
	str	w2, [x20, -68]
	ldr	w2, [x20, -96]
	add	w0, w6, w0, asr 3
	str	w2, [x20, -64]
	cmp	w3, 131
	str	w0, [x20, -44]
	str	w0, [x1, 96]
	ldr	w0, [x20, -52]
	str	w0, [x1, 104]
	ldr	w0, [x20, -48]
	str	w0, [x1, 112]
	ldr	w0, [x20, -32]
	str	w0, [x1, 100]
	ldr	w0, [x20, -40]
	str	w0, [x1, 108]
	ldr	w0, [x20, -36]
	str	w0, [x1, 116]
	ldr	w0, [x20, -64]
	str	w0, [x1, 120]
	ldr	w0, [x20, -68]
	str	w0, [x1, 124]
	ldr	w0, [x20, -72]
	str	w0, [x1, 128]
	ldr	w0, [x20, -60]
	str	w0, [x1, 132]
	str	w3, [x24, 36]
	ble	.L309
	mov	x0, x21
	bl	Real8_ModifySliceMsg
	cmp	w0, 1
	bne	.L387
	str	x24, [x21, 8]
	cbz	x24, .L388
	ldr	x0, [x21]
	ldr	w1, [x0, 920]
	cmp	w1, 1
	beq	.L389
	cmp	w1, 2
	bne	.L309
	ldr	w0, [x0, 924]
	cmp	w0, wzr
	ble	.L309
	ldrb	w0, [x24, 12]
	cmp	w0, 2
	bne	.L309
	str	xzr, [x21, 8]
	mov	w2, 0
	mov	w22, 0
	ldr	w1, [x20, 1152]
	ldr	w0, [x20, 1816]
	bl	FSP_SetDisplay
	ldr	x3, [x21]
	mov	x1, x21
	mov	w0, 8
	ldr	w2, [x3, 924]
	sub	w2, w2, #1
	str	w2, [x3, 924]
	bl	ReleasePacket
	b	.L359
	.p2align 3
.L372:
	ldr	x1, .LC44
	mov	w0, 1
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L264:
	ldr	x1, .LC49
	mov	w0, 18
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L376:
	add	x26, x26, 40960
	ldr	x1, .LC55
	mov	w22, 0
	ldr	w2, [x26, 1956]
	bl	dprint_vfmw
	b	.L359
.L375:
	ldr	x1, .LC53
	mov	w0, 1
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L377:
	ldrb	w0, [x26, 23]
	cmp	w0, 1
	bls	.L305
	ldrb	w0, [x26, 18]
	cmp	w0, 4
	bne	.L278
.L321:
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2072]
	cbnz	w1, .L278
	ldr	w1, [x0, 2064]
	mov	w2, 1
	ldr	w0, [x20, 1816]
	mov	w22, 0
	bl	FSP_ClearLogicFs
	b	.L359
.L378:
	ldrb	w1, [x26, 23]
	mov	w0, 2
	cbnz	w1, .L275
.L305:
	add	x1, x23, 3184
	ldr	w0, [x20, 1816]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w22, 0
	ldr	w1, [x1, 2064]
	bl	FSP_ClearLogicFs
	b	.L359
.L374:
	ldrb	w1, [x4, 20]
	cbnz	w1, .L268
.L360:
	add	x0, x20, 1208
	str	x9, [x29, 136]
	bl	ResetVoQueue
	ldr	w0, [x29, 368]
	ldr	w2, [x29, 372]
	ldr	x9, [x29, 136]
	b	.L268
.L319:
	mov	w19, 1
	str	w19, [x24, 40]
	ldr	x0, [x21, 8]
	cbz	x0, .L390
.L302:
	ldr	x0, [x21]
	ldr	w1, [x0, 632]
	str	w1, [x21, 92]
	ldr	w0, [x0, 684]
	str	w0, [x21, 96]
	b	.L359
.L383:
	ldr	w0, [x1, 1928]
	ldr	w26, [x1, 896]
	sub	w0, w0, w25
	b	.L364
.L381:
	ldr	w2, [x9, 16]
	ldr	w1, [x20, -104]
	ldr	w0, [x28, 16]
	subs	w1, w1, w2
	sub	w0, w0, w2
	bmi	.L391
.L292:
	tbnz	w0, #31, .L392
.L293:
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w0, wzr
	ble	.L325
	sub	w3, w0, w1
	lsl	w4, w1, 14
	lsl	w3, w3, 14
	sdiv	w4, w4, w0
	sdiv	w3, w3, w0
.L295:
	add	x2, x23, 3184
	add	x2, x2, 40960
	add	x5, x2, 1792
	stp	w1, w0, [x5, 180]
	stp	w4, w3, [x5, 188]
	b	.L291
.L379:
	ldr	x2, .LC62
	mov	w3, 1979
	ldr	x1, .LC64
	mov	w0, 22
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L373:
	ldr	w0, [x29, 152]
	cmp	w0, wzr
	bgt	.L260
	ldr	w0, [x29, 148]
	cmp	w0, 32
	bgt	.L260
	ldr	x0, [x21, 8]
	cbnz	x0, .L260
	ldr	w3, [x20, 1040]
	cbz	w3, .L257
	ldr	w4, [x20, -116]
	cbz	w4, .L257
	ldr	w0, [x20, 1820]
	ldr	w7, [x29, 368]
	cmp	w7, w0
	beq	.L257
	ldr	w0, [x20, 1824]
	ldr	w6, [x29, 372]
	cmp	w6, w0
	beq	.L257
	ldr	x1, .LC47
	mov	w0, w2
	ldr	w5, [x20, -120]
	str	x9, [x29, 136]
	bl	dprint_vfmw
	ldr	w0, [x29, 368]
	str	w0, [x20, 1820]
	ldr	x4, [x28]
	ldr	w0, [x29, 372]
	str	w0, [x20, 1824]
	ldr	x9, [x29, 136]
	cbz	x4, .L257
	ldr	w0, [x20, 1816]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	ldr	x9, [x29, 136]
	b	.L257
.L281:
	cmp	w0, 2
	beq	.L321
	cmp	w0, 1
	bne	.L278
	str	w0, [x26, 2072]
	b	.L278
.L385:
	uxtw	x0, w28
	str	w6, [x29, 100]
	add	x0, x0, 8192
	add	x0, x0, 2272
	ldr	w1, [x26, x0, lsl 2]
	ldr	w0, [x27, 1928]
	sub	w0, w0, w25
	b	.L365
.L384:
	add	x26, x26, 40960
	ldr	w0, [x20, 1816]
	mov	w22, 0
	ldr	w1, [x26, 2064]
	bl	FSP_ClearLogicFs
	b	.L359
.L387:
	ldr	w0, [x20, 1816]
	mov	w2, 1
	ldr	w1, [x27, 2064]
	mov	w22, 0
	bl	FSP_ClearLogicFs
	b	.L359
.L386:
	ldr	x1, .LC70
	mov	w2, 2146
	mov	w0, 22
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L389:
	ldrb	w0, [x24, 12]
	cmp	w0, 2
	bne	.L309
	str	xzr, [x21, 8]
	mov	w2, 0
	mov	w22, 0
	ldr	w1, [x20, 1152]
	ldr	w0, [x20, 1816]
	bl	FSP_SetDisplay
	mov	x1, x21
	mov	w0, 8
	bl	ReleasePacket
	b	.L359
.L388:
	ldr	x2, .LC62
	mov	w3, 2179
	ldr	x1, .LC72
	mov	w0, 22
	mov	w22, 0
	bl	dprint_vfmw
	b	.L359
.L285:
	add	x1, x23, 3184
	ldr	w0, [x20, 1816]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w22, 0
	ldr	w1, [x1, 2064]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC66
	mov	w0, 0
	bl	dprint_vfmw
	b	.L359
.L260:
	mov	w22, -2
	b	.L359
.L391:
	ldr	w2, [x20, -108]
	add	w1, w1, w2
	b	.L292
.L382:
	sub	w1, w1, #1
	orr	w1, w1, -8
	add	w1, w1, 1
	b	.L297
.L325:
	mov	w3, 0
	mov	w4, 0
	b	.L295
.L392:
	ldr	w2, [x20, -108]
	add	w0, w0, w2
	b	.L293
.L271:
	ldr	w0, [x20, 1816]
	mov	w2, 1
	ldr	w1, [x28, 2064]
	mov	w22, 0
	bl	FSP_ClearLogicFs
	b	.L359
.L390:
	mov	x0, x21
	bl	Real8_ModifySliceMsg
	cmp	w0, 1
	bne	.L393
	str	x24, [x21, 8]
	b	.L302
.L380:
	ldr	x0, [x26, 32]
	b	.L363
.L287:
	ldr	w5, [x0, 8]
	b	.L288
.L393:
	add	x1, x23, 3184
	ldr	w0, [x20, 1816]
	add	x1, x1, 40960
	mov	w2, w19
	mov	w22, 0
	ldr	w1, [x1, 2064]
	bl	FSP_ClearLogicFs
	b	.L359
	.size	REAL8DEC_Decode, .-REAL8DEC_Decode
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC41:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC42:
	.xword	.LANCHOR0
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	g_event_report
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
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
.LC62:
	.xword	.LANCHOR1
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
	.global	REAL8DEC_RecycleImage
	.type	REAL8DEC_RecycleImage, %function
REAL8DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L396
	add	x19, x19, 53248
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 1816]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 1816]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L396:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_RecycleImage, .-REAL8DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_GetRemainImg
	.type	REAL8DEC_GetRemainImg, %function
REAL8DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 53248
	bl	_mcount
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L398
	mov	x21, 52336
	add	x20, x19, 53248
	add	x21, x19, x21
	ldr	w0, [x20, 1816]
	ldr	w1, [x21, 2060]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L398
	ldr	w0, [x20, 1816]
	ldr	w1, [x21, 2060]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L411
.L398:
	add	x22, x20, 1208
.L402:
	mov	x0, x22
	bl	GetVoLastImageID
.L408:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L411:
	mov	x0, x19
	add	x22, x20, 1208
	bl	Real8_SetImgFormat
	mov	w2, 1
	str	w2, [x23, 180]
	ldr	w0, [x20, 1816]
	ldr	w1, [x21, 2060]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 1816]
	mov	x4, x23
	mov	x3, x22
	mov	x2, x19
	mov	w1, 8
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L399
	ldr	w0, [x20, 1816]
	mov	w2, 0
	ldr	w1, [x21, 2060]
	bl	FSP_SetDisplay
	b	.L402
	.p2align 3
.L399:
	ldr	w0, [x23, 152]
	cmp	w0, 100
	bhi	.L398
	ldr	w0, [x23, 68]
	cmp	w0, 31
	bls	.L398
	ldr	w1, [x23, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L408
	b	.L402
	.size	REAL8DEC_GetRemainImg, .-REAL8DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_VDMPostProc
	.type	REAL8DEC_VDMPostProc, %function
REAL8DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	mov	w24, w2
	bl	_mcount
	add	x21, x20, 53248
	ldr	x1, .LC75
	mov	w2, w22
	mov	w0, 22
	add	x19, x20, 8192
	add	x25, x19, 3184
	bl	dprint_vfmw
	add	x23, x25, 40960
	ldr	x2, [x20, 8]
	mov	x1, x20
	mov	w0, 8
	ldrb	w3, [x2]
	strb	w3, [x21, -232]
	ldr	w2, [x2, 76]
	str	w2, [x21, -228]
	bl	ReleasePacket
	ldr	w0, [x21, 1816]
	ldr	w1, [x23, 2064]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L421
	ldr	w1, [x23, 780]
	strb	w1, [x19, 3205]
	cmp	w1, 2
	beq	.L414
	and	w24, w24, 31
	str	w24, [x23, 888]
.L414:
	tbnz	w22, #31, .L422
	mov	w1, 100
	cmp	w22, w1
	csel	w22, w22, w1, le
.L415:
	ldr	x1, .LC77
	str	w22, [x0, 152]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	Real8_SetImgFormat
	ldrb	w1, [x19, 3202]
	add	x0, x19, 3184
	cmp	w1, 2
	beq	.L418
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L418
	add	x1, x0, 40960
	ldr	w2, [x1, 780]
	cmp	w2, 2
	beq	.L418
	ldrb	w0, [x0, 23]
	cmp	w0, 1
	bls	.L423
	ldr	w1, [x1, 2056]
.L419:
	add	x0, x19, 3184
	cmn	w1, #1
	add	x0, x0, 40960
	str	w1, [x0, 2068]
	beq	.L420
.L437:
	add	x22, x19, 3184
	ldr	w0, [x21, 1816]
	add	x22, x22, 40960
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	ldr	w23, [x22, 2068]
	ldr	w0, [x21, 1816]
	mov	w1, w23
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC79
	mov	w2, w23
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x21, 1816]
	mov	w2, 1
	ldr	w1, [x22, 2068]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1816]
	mov	x4, x24
	add	x3, x21, 1208
	mov	x2, x20
	mov	w1, 8
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L436
.L420:
	add	x19, x19, 3184
	mov	w0, 1
	add	x19, x19, 40960
	ldr	w1, [x19, 1956]
	add	w1, w1, w0
	str	w1, [x19, 1956]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L418:
	add	x0, x19, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2064]
	str	w1, [x0, 2068]
	cmn	w1, #1
	bne	.L437
	b	.L420
	.p2align 3
.L422:
	mov	w22, 0
	b	.L415
	.p2align 3
.L436:
	ldr	w0, [x21, 1816]
	mov	w2, 0
	ldr	w1, [x22, 2068]
	bl	FSP_SetDisplay
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L423:
	mov	w1, -1
	b	.L419
	.p2align 3
.L421:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	REAL8DEC_VDMPostProc, .-REAL8DEC_VDMPostProc
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_GetImageBuffer
	.type	REAL8DEC_GetImageBuffer, %function
REAL8DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 53248
	bl	_mcount
	ldr	w0, [x19, 1816]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L439
	ldr	w0, [x19, 1816]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L444
.L439:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L444:
	ldr	w0, [x19, 1816]
	add	x1, x19, 1208
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_GetImageBuffer, .-REAL8DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Support
	.type	REAL8DEC_Support, %function
REAL8DEC_Support:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	str	w0, [x19]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_Support, .-REAL8DEC_Support
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	gs_VLCDecodeTable, %object
	.size	gs_VLCDecodeTable, 256
gs_VLCDecodeTable:
	.byte	-128
	.byte	-127
	.byte	112
	.byte	112
	.byte	-126
	.byte	-125
	.byte	113
	.byte	113
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	-124
	.byte	-123
	.byte	114
	.byte	114
	.byte	-122
	.byte	-121
	.byte	115
	.byte	115
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	-120
	.byte	-119
	.byte	116
	.byte	116
	.byte	-118
	.byte	-117
	.byte	117
	.byte	117
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	-116
	.byte	-115
	.byte	118
	.byte	118
	.byte	-114
	.byte	-113
	.byte	119
	.byte	119
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	MBA_FieldWidth, %object
	.size	MBA_FieldWidth, 24
MBA_FieldWidth:
	.word	6
	.word	7
	.word	9
	.word	11
	.word	13
	.word	14
.LC0:
	.word	160
	.word	176
	.word	240
	.word	320
	.word	352
	.word	640
	.word	704
	.word	0
.LC1:
	.word	120
	.word	132
	.word	144
	.word	240
	.word	288
	.word	480
	.word	0
	.word	0
	.type	GetBitsMask, %object
	.size	GetBitsMask, 100
GetBitsMask:
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
	.zero	4
.LC2:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	3
	.zero	4
	.type	s_RVVersionEncodingToMinorVersion, %object
	.size	s_RVVersionEncodingToMinorVersion, 32
s_RVVersionEncodingToMinorVersion:
	.word	2
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.align	3
.LANCHOR1 = . + 0
	.type	__FUNCTION__.11702, %object
	.size	__FUNCTION__.11702, 16
__FUNCTION__.11702:
	.string	"REAL8DEC_Decode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC6:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC8:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC10:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC12:
	ASCII(.string	"image size abnormal (%dx%d) in MB\n" )
	.zero	5
.LC14:
	ASCII(.string	"real8 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
.LC17:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC33:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC35:
	ASCII(.string	"Decoding quits at frm %d\n" )
	.zero	6
.LC39:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
.LC43:
	ASCII(.string	"Real8_CB_GetPictureHeader Error!\n" )
	.zero	6
.LC46:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC48:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC50:
	ASCII(.string	"new seq size %d * %d\n" )
	.zero	2
.LC52:
	ASCII(.string	"Real8_ArrangeVHBMem err\n" )
	.zero	7
.LC54:
	ASCII(.string	"Fatal Error: frm%d, get image buffer failed\n" )
	.zero	3
.LC56:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC58:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC60:
	ASCII(.string	"++++++++++ ref %d\n" )
	.zero	5
.LC63:
	ASCII(.string	"%s %d unknow error!!\n" )
	.zero	2
.LC65:
	ASCII(.string	"CurFsID abnormal!\n" )
	.zero	5
.LC67:
	ASCII(.string	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n" )
.LC69:
	ASCII(.string	"line:%d! i > (RV8_MAX_SLC_PARAM_NUM - 2)\n" )
	.zero	6
.LC71:
	ASCII(.string	"%s %d NULL == pCtx->pRv8DecParam!!\n" )
	.zero	4
.LC74:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC76:
	ASCII(.string	"DEBUG: DEC over\n" )
	.zero	7
.LC78:
	ASCII(.string	"insert buf %d ref %d\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
