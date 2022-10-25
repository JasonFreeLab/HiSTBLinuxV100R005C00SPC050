#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"real9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetBits
	.type	Real9_CB_GetBits, %function
Real9_CB_GetBits:
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
	.size	Real9_CB_GetBits, .-Real9_CB_GetBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_Get1Bit
	.type	Real9_CB_Get1Bit, %function
Real9_CB_Get1Bit:
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
	.size	Real9_CB_Get1Bit, .-Real9_CB_Get1Bit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetVLCBits
	.type	Real9_CB_GetVLCBits, %function
Real9_CB_GetVLCBits:
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
	ldr	x22, .LC2
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
	.size	Real9_CB_GetVLCBits, .-Real9_CB_GetVLCBits
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_GetImageBuffer
	.type	Real9_GetImageBuffer, %function
Real9_GetImageBuffer:
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
	ldr	w0, [x21, 1792]
	bl	FSP_NewLogicFs
	str	w0, [x20, 2040]
	mov	w1, w0
	tbnz	w0, #31, .L14
	ldr	w0, [x21, 1792]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L15
	ldr	x1, .LC8
	mov	w0, 18
	ldr	w2, [x20, 2040]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L13
	ldr	x1, [x19, 40]
	cbz	x1, .L13
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC10
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
	ldr	x1, .LC4
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 2036]
	mov	w2, 1
	ldr	w0, [x21, 1792]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 2032]
	mov	w2, 1
	ldr	w0, [x21, 1792]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 2032]
	str	wzr, [x20, 2036]
	ldr	w0, [x21, 1792]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 2032]
	str	w0, [x20, 2036]
	add	x1, x21, 1184
	strb	wzr, [x19, 25]
	ldr	w0, [x21, 1792]
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L15:
	ldr	x1, .LC6
	mov	w2, 510
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L10
	.size	Real9_GetImageBuffer, .-Real9_GetImageBuffer
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
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_ArrangeVHBMem
	.type	Real9_ArrangeVHBMem, %function
Real9_ArrangeVHBMem:
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
	ldp	w3, w2, [x19, 28]
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
	ldp	w23, w22, [x19, 20]
	mov	w25, 5
	mov	w21, 2
	mov	w24, 4
.L28:
	ldr	x0, .LC15
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x20]
	ldp	w1, w2, [x19, 20]
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
	ldr	w0, [x19, 1792]
	bl	FSP_ConfigInstance
	mov	w2, 0
	cbnz	w0, .L43
	ldr	x1, [x20]
	add	x3, x29, 84
	ldr	w0, [x19, 1792]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L49
	cbnz	w0, .L36
	add	x20, x20, 8192
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x20, 3212]
	b	.L43
	.p2align 3
.L18:
	ldr	x1, .LC12
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
	ldp	w3, w2, [x19, 20]
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
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L48:
	ldr	w22, [x0, 724]
	ldp	w3, w2, [x19, 20]
	cmp	w2, w22
	bhi	.L50
	ldr	w23, [x0, 728]
	cmp	w3, w23
	bhi	.L51
	add	x1, x20, 8192
	ldrb	w2, [x1, 3212]
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
	add	x0, x19, 1184
	bl	ResetVoQueue
.L36:
	ldr	x1, .LC17
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L51:
	mov	w5, w23
.L24:
	ldr	x1, .LC14
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
.L50:
	ldr	w5, [x0, 728]
	b	.L24
	.size	Real9_ArrangeVHBMem, .-Real9_ArrangeVHBMem
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC15:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC17:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetCPFMT
	.type	Real9_CB_GetCPFMT, %function
Real9_CB_GetCPFMT:
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
	str	w20, [x21, 24]
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
	str	w22, [x21, 20]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real9_CB_GetCPFMT, .-Real9_CB_GetCPFMT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_SetDimensions
	.type	Real9_CB_SetDimensions, %function
Real9_CB_SetDimensions:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w2, w0, [x19, 20]
	cmp	w0, 128
	beq	.L73
	cmp	w0, 176
	beq	.L74
	cmp	w0, 352
	bne	.L62
	cmp	w2, 288
	beq	.L75
	.p2align 2
.L58:
	add	w1, w0, 15
	add	w2, w2, 15
	add	x19, x19, 72
	lsr	w1, w1, 4
	lsr	w2, w2, 4
	mov	w0, 6
	stp	w2, w1, [x19, 8]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w1, 47
	bls	.L59
	cmp	w1, 98
	bls	.L68
	cmp	w1, 395
	bls	.L69
	cmp	w1, 1583
	bls	.L70
.L72:
	mov	w2, 6335
	mov	w0, 14
	cmp	w1, w2
	bls	.L76
.L59:
	str	w0, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L74:
	cmp	w2, 144
	bne	.L58
	add	x19, x19, 72
	mov	w2, 11
	mov	w0, 9
	mov	w1, 1
	stp	w0, w2, [x19, 8]
.L61:
	ldr	x0, .LC18
	add	x0, x0, 256
	ldr	w0, [x0, w1, uxtw 2]
	str	w0, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L73:
	cmp	w2, 96
	bne	.L58
	add	x19, x19, 72
	mov	w1, 6
	mov	w2, 8
	mov	w0, w1
	stp	w1, w2, [x19, 8]
	b	.L59
	.p2align 3
.L62:
	cmp	w0, 704
	bne	.L64
	cmp	w2, 576
	bne	.L58
	add	x19, x19, 72
	mov	w1, 44
	mov	w0, 36
	stp	w0, w1, [x19, 8]
.L70:
	mov	w1, 3
	b	.L61
	.p2align 3
.L75:
	add	x19, x19, 72
	mov	w1, 22
	mov	w0, 18
	stp	w0, w1, [x19, 8]
.L69:
	mov	w1, 2
	b	.L61
	.p2align 3
.L64:
	cmp	w0, 1408
	bne	.L58
	cmp	w2, 1152
	bne	.L58
	add	x19, x19, 72
	mov	w2, 88
	mov	w0, 72
	mov	w1, 6335
	stp	w0, w2, [x19, 8]
	b	.L72
	.p2align 3
.L76:
	mov	w1, 4
	b	.L61
.L68:
	mov	w1, 1
	b	.L61
	.size	Real9_CB_SetDimensions, .-Real9_CB_SetDimensions
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetPicSize
	.type	Real9_CB_GetPicSize, %function
Real9_CB_GetPicSize:
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
	ldr	x0, .LC20
	mov	w3, 180
	ldr	w1, [x20, 20]
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
	ldr	w0, [x20, 52]
	str	w0, [x24]
	ldr	w0, [x20, 56]
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
	.size	Real9_CB_GetPicSize, .-Real9_CB_GetPicSize
	.align	3
.LC20:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_FindNextSliceStartCode
	.type	Real9_CB_FindNextSliceStartCode, %function
Real9_CB_FindNextSliceStartCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, 7184
	mov	w19, 0
	bl	_mcount
	movk	w22, 0x1d, lsl 16
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
	bgt	.L99
	b	.L97
	.p2align 3
.L101:
	bl	BsSkip
	cmp	w19, w21
	beq	.L97
.L99:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	cmp	w0, w22
	mov	w1, 8
	mov	x0, x20
	bne	.L101
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L97:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real9_CB_FindNextSliceStartCode, .-Real9_CB_FindNextSliceStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_SearchBits_IgnoreOnly0
	.type	Real9_CB_SearchBits_IgnoreOnly0, %function
Real9_CB_SearchBits_IgnoreOnly0:
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
	beq	.L103
	tst	w22, w19
	bne	.L103
	ldr	x0, .LC23
	mov	w20, 0
	add	x0, x0, 344
	ldr	w25, [x0, w25, uxtw 2]
	b	.L104
	.p2align 3
.L105:
	tst	w22, w19
	bne	.L103
.L104:
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
	bhi	.L105
.L103:
	cmp	w23, w19
	ldr	x25, [sp, 64]
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	Real9_CB_SearchBits_IgnoreOnly0, .-Real9_CB_SearchBits_IgnoreOnly0
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetSSC
	.type	Real9_CB_GetSSC, %function
Real9_CB_GetSSC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	cmp	w0, 1
	beq	.L111
	mov	x0, x20
	bl	Real9_CB_FindNextSliceStartCode
	cmp	w0, wzr
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L111:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_CB_GetSSC, .-Real9_CB_GetSSC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetSliceHeader
	.type	Real9_CB_GetSliceHeader, %function
Real9_CB_GetSliceHeader:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x5
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	mov	x23, x2
	mov	x25, x3
	mov	x24, x4
	bl	_mcount
	ldr	w20, [x21, 12]
	cmp	w20, 1
	beq	.L150
	cbz	w22, .L151
	str	wzr, [x23]
	mov	w0, -1
	mov	w20, 1
	str	w0, [x24]
.L136:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L150:
	add	x26, x21, 72
	cbnz	w22, .L114
	ldr	w0, [x26, 24]
	cmn	w0, #1
	beq	.L152
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cbnz	w27, .L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	ldr	w0, [x26, 20]
	cmp	w0, w20
	beq	.L117
.L119:
	mov	w20, 0
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L151:
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	bne	.L119
	ldr	w26, [x21, 88]
	mov	x0, x19
	mov	w1, w26
	bl	BsShow
	mov	w27, w0
	mov	w1, w26
	mov	x0, x19
	bl	BsSkip
	str	w27, [x23]
	ldr	w0, [x21, 88]
	cmp	w0, 11
	bls	.L132
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cmp	w22, 1
	bne	.L119
.L132:
	mov	w1, 5
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 5
	mov	x0, x19
	bl	BsSkip
	str	w20, [x24]
	cmp	w20, 31
	bgt	.L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w20, [x21, 60]
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	bne	.L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w21, [x25]
	b	.L136
	.p2align 3
.L152:
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cbnz	w22, .L119
	mov	w1, 2
	mov	x0, x19
	mov	w22, w20
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w20, [x26, 20]
.L117:
	mov	w1, 5
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 5
	mov	x0, x19
	bl	BsSkip
	uxtb	w0, w20
	strb	w0, [x26, 2]
	cmp	w0, 31
	bhi	.L119
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbnz	w20, .L119
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbnz	w20, .L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w27, [x21, 60]
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w27, wzr
	mov	w1, 13
	cset	w0, ne
	strb	w0, [x26, 1]
	mov	x0, x19
	cbz	w22, .L120
	bl	BsShow
	mov	w22, w0
	mov	w1, 13
	mov	x0, x19
	bl	BsSkip
	str	w22, [x26, 28]
	ldr	w0, [x26, 20]
	cmp	w0, 1
	bls	.L122
	cmp	w0, 2
	bne	.L140
	ldp	w1, w0, [x26, 44]
	stp	w1, w0, [x26, 52]
.L140:
	add	x2, x29, 104
	mov	x1, x26
	mov	x0, x19
	add	x3, x29, 108
	bl	Real9_CB_GetPicSize
	ldp	w1, w0, [x29, 104]
	stp	w1, w0, [x26, 44]
	sub	w2, w1, #48
	stp	w0, w1, [x21, 20]
	mov	w1, 8144
	cmp	w2, w1
	bhi	.L136
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L136
	mov	x0, x21
	bl	Real9_CB_SetDimensions
.L128:
	ldr	w20, [x26, 16]
	mov	x0, x19
	mov	w1, w20
	bl	BsShow
	mov	w21, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	str	w21, [x26, 24]
.L114:
	ldr	w0, [x26, 24]
	mov	w20, 1
	str	w0, [x23]
	ldrb	w0, [x26, 2]
	str	w0, [x24]
	mov	w0, w20
	str	wzr, [x25]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L120:
	bl	BsShow
	mov	w21, w0
	mov	w1, 13
	mov	x0, x19
	bl	BsSkip
	ldr	w0, [x26, 28]
	cmp	w0, w21
	bne	.L119
	mov	x1, x26
	mov	x0, x19
	add	x3, x29, 108
	add	x2, x29, 104
	bl	Real9_CB_GetPicSize
	ldr	w1, [x26, 44]
	ldr	w0, [x29, 104]
	cmp	w1, w0
	bne	.L136
	ldr	w1, [x26, 48]
	ldr	w0, [x29, 108]
	cmp	w1, w0
	bne	.L136
	b	.L128
.L122:
	stp	wzr, wzr, [x26, 52]
	b	.L140
	.size	Real9_CB_GetSliceHeader, .-Real9_CB_GetSliceHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetPictureHeader
	.type	Real9_CB_GetPictureHeader, %function
Real9_CB_GetPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	cmp	w0, 1
	beq	.L178
	ldr	x3, .LC26
	mov	x2, 136
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w1, 16
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 16
	mov	x0, x20
	bl	BsSkip
	mov	w0, 21845
	cmp	w21, w0
	bne	.L173
	mov	w1, 16
	mov	x0, x20
	bl	BsShow
	mov	w22, w0
	mov	w1, 16
	mov	x0, x20
	bl	BsSkip
	cmp	w22, w21
	bne	.L173
	mov	x0, x20
	add	x1, x29, 60
	bl	Real9_CB_GetVLCBits
	cmp	w0, 30
	bls	.L173
	ldr	w0, [x29, 60]
	tbnz	x0, 0, .L173
	tbnz	x0, 1, .L164
	mov	w2, 176
	mov	w1, 144
	stp	w1, w2, [x19, 20]
.L165:
	ubfx	x1, x0, 2, 5
	ubfx	x0, x0, 7, 8
	str	w1, [x19, 56]
	add	x1, x29, 60
	str	w0, [x19, 44]
	mov	x0, x20
	bl	Real9_CB_GetVLCBits
	cmp	w0, 1
	beq	.L177
	cmp	w0, 3
	beq	.L179
	cmp	w0, 5
	bne	.L173
	ldr	w0, [x29, 60]
	cbnz	w0, .L173
	mov	w0, 2
.L177:
	str	w0, [x19, 16]
.L167:
	ldr	w0, [x19, 24]
	cbz	w0, .L180
.L169:
	sub	w0, w0, #48
	mov	w1, 8144
	cmp	w0, w1
	bhi	.L173
	ldr	w0, [x19, 20]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L173
	mov	x0, x19
	mov	w21, 1
	bl	Real9_CB_SetDimensions
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	mov	w22, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w22, [x19, 60]
.L155:
	ldp	w2, w1, [x19, 20]
	mov	w0, w21
	add	w1, w1, 15
	add	w2, w2, 15
	lsr	w2, w2, 4
	lsr	w1, w1, 4
	stp	w2, w1, [x19, 28]
	mul	w1, w1, w2
	str	w1, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L179:
	ldr	w0, [x29, 60]
	cmp	w0, 1
	beq	.L181
.L173:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -2
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L178:
	add	x22, x19, 72
	mov	w0, -1
	mov	x5, x19
	add	x4, x29, 60
	add	x3, x29, 52
	add	x2, x29, 56
	str	w0, [x22, 24]
	mov	w1, 0
	mov	x0, x20
	mov	w21, -2
	bl	Real9_CB_GetSliceHeader
	cmp	w0, 1
	bne	.L155
	ldr	w0, [x22, 20]
	cmp	w0, 3
	bls	.L182
.L156:
	ldrb	w1, [x22, 1]
	str	w1, [x19, 52]
	mov	w1, 8144
	ldr	w0, [x19, 24]
	ldrb	w2, [x22, 2]
	str	w2, [x19, 56]
	sub	w0, w0, #48
	cmp	w0, w1
	ldr	w0, [x22, 28]
	str	w0, [x19, 44]
	ldr	w0, [x22, 32]
	str	w0, [x19, 64]
	ldr	w0, [x22, 36]
	str	w0, [x19, 68]
	bhi	.L173
	ldr	w0, [x19, 20]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L173
	mov	x0, x19
	bl	Real9_CB_SetDimensions
	b	.L155
	.p2align 3
.L164:
	stp	wzr, wzr, [x19, 20]
	b	.L165
	.p2align 3
.L180:
	mov	x1, x19
	mov	x0, x20
	bl	Real9_CB_GetCPFMT
	cbz	w0, .L173
	ldr	w0, [x19, 24]
	b	.L169
	.p2align 3
.L182:
	ldr	x1, .LC25
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx158
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx158:
	.section	.rodata
	.align	0
	.align	2
.L158:
	.byte	(.L157 - .Lrtx158) / 4
	.byte	(.L159 - .Lrtx158) / 4
	.byte	(.L160 - .Lrtx158) / 4
	.byte	(.L161 - .Lrtx158) / 4
	.text
	.p2align 3
.L181:
	str	wzr, [x19, 16]
	b	.L167
.L160:
	mov	w0, 1
	str	w0, [x19, 16]
	mov	w21, w0
	b	.L156
.L159:
	str	wzr, [x19, 16]
	mov	w21, 1
	str	wzr, [x22, 4]
	b	.L156
.L157:
	mov	w0, 1
	str	wzr, [x19, 16]
	mov	w21, w0
	str	w0, [x22, 4]
	b	.L156
.L161:
	mov	w0, 2
	mov	w21, 1
	str	w0, [x19, 16]
	b	.L156
	.size	Real9_CB_GetPictureHeader, .-Real9_CB_GetPictureHeader
	.align	3
.LC25:
	.xword	.L158
	.align	3
.LC26:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_SetImgFormat
	.type	Real9_SetImgFormat, %function
Real9_SetImgFormat:
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
	ldr	w0, [x20, 1792]
	ldr	w1, [x1, 2040]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L183
	ldr	w3, [x20, -216]
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
	ldr	w2, [x20, -208]
	str	w2, [x0, 68]
	ldr	w2, [x20, -212]
	str	w2, [x0, 72]
	bl	SetAspectRatio
	ldr	x0, [x21]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L189
.L185:
	mov	w1, 1
	strb	w1, [x19, 291]
	strb	w1, [x19, 289]
	add	x1, x19, 256
	strb	wzr, [x19, 284]
	mov	w0, 8
	mov	w2, 9
	stp	w0, w0, [x1, 48]
	stp	w2, w0, [x1, 40]
.L183:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L189:
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
	b	.L185
	.size	Real9_SetImgFormat, .-Real9_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RV9_RecordVFMWState
	.type	RV9_RecordVFMWState, %function
RV9_RecordVFMWState:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	RV9_RecordVFMWState, .-RV9_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WriteSliceMsg
	.type	Real9_WriteSliceMsg, %function
Real9_WriteSliceMsg:
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
	ldr	w0, [x3, -68]
	add	x2, x19, x2, lsl 2
	str	w0, [x2, 92]
	ldr	w0, [x3, -76]
	str	w0, [x2, 100]
	ldr	w0, [x3, -72]
	str	w0, [x2, 108]
	ldr	w0, [x3, -56]
	str	w0, [x2, 96]
	ldr	w0, [x3, -64]
	str	w0, [x2, 104]
	ldr	w0, [x3, -60]
	str	w0, [x2, 112]
	ldr	w0, [x3, -88]
	str	w0, [x2, 116]
	ldr	w0, [x3, -92]
	str	w0, [x2, 120]
	ldr	w0, [x3, -96]
	str	w0, [x2, 124]
	ldr	w0, [x3, -84]
	str	w0, [x2, 128]
	str	w20, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WriteSliceMsg, .-Real9_WriteSliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WritePicMsg
	.type	Real9_WritePicMsg, %function
Real9_WritePicMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 53248
	mov	x1, 52336
	add	x1, x19, x1
	ldr	w3, [x2, -216]
	strb	w3, [x19, 16]
	cmp	w3, 2
	ldr	w3, [x2, -200]
	str	w3, [x19, 20]
	ldr	w3, [x2, -204]
	str	w3, [x19, 24]
	ldr	w3, [x1, 1956]
	str	w3, [x19, 28]
	ldr	w3, [x1, 1960]
	str	w3, [x19, 32]
	ldr	w2, [x2, -176]
	str	w2, [x19, 36]
	ldr	w3, [x1, 860]
	str	w3, [x19, 40]
	ldr	w3, [x1, 864]
	str	w3, [x19, 44]
	beq	.L192
	str	w2, [x1, 860]
.L192:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WritePicMsg, .-Real9_WritePicMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WriteReg
	.type	Real9_WriteReg, %function
Real9_WriteReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	str	w20, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WriteReg, .-Real9_WriteReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_ModifySliceMsg
	.type	Real9_ModifySliceMsg, %function
Real9_ModifySliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16
	ldr	w1, [x0, 128]
	cbnz	w1, .L202
	ldp	w1, w4, [x0, 4]
	ldr	w5, [x0, 32]
	mul	w4, w1, w4
	cmp	w5, 2
	sub	w4, w4, #1
	bhi	.L224
.L201:
	cmp	w5, 1
	bls	.L206
	sub	w7, w5, #1
	mov	w3, 0
	b	.L207
	.p2align 3
.L208:
	add	w3, w3, 1
	lsl	x1, x1, 2
	sub	x1, x1, x2
	sxtw	x6, w3
	lsl	x2, x6, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	ldr	w6, [x1, 128]
	add	x1, x0, x2, lsl 2
	ldr	w1, [x1, 128]
	cmp	w6, w1
	bge	.L202
.L207:
	sxtw	x2, w3
	cmp	w3, w7
	lsl	x1, x2, 2
	sub	x1, x1, x2
	bne	.L208
	uxtw	x3, w3
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x3, x1, x3
	add	x3, x0, x3, lsl 2
	ldr	w1, [x3, 128]
	cmp	w4, w1
	ccmp	w1, wzr, 4, ge
	ble	.L202
.L206:
	cbz	w5, .L209
	sub	w9, w5, #1
	mov	w8, 0
	mov	x10, 44
	b	.L212
	.p2align 3
.L227:
	beq	.L225
.L212:
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
	beq	.L226
	sub	x3, x3, x6
	add	x2, x0, x2, lsl 2
	add	x3, x0, x3, lsl 2
	ldr	w3, [x3, 128]
	sub	w3, w3, #1
	str	w3, [x2, 132]
.L211:
	lsl	x1, x7, 2
	add	w8, w8, 1
	sub	x1, x1, x7
	lsl	x1, x1, 2
	sub	x1, x1, x7
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 128]
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
	cbz	w1, .L227
	.p2align 2
.L202:
	mov	w0, 0
.L222:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L224:
	ldr	w1, [x0, 172]
	sub	w6, w5, #1
	mov	w2, 1
	cmp	w4, w1
	ccmp	w1, wzr, 4, gt
	bgt	.L204
	b	.L202
	.p2align 3
.L205:
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x1, x1, x3
	add	x1, x0, x1, lsl 2
	ldr	w1, [x1, 128]
	cmp	w1, wzr
	ccmp	w4, w1, 4, gt
	ble	.L202
.L204:
	add	w2, w2, 1
	cmp	w2, w6
	sxtw	x3, w2
	lsl	x1, x3, 2
	bne	.L205
	b	.L201
.L225:
	ldr	w3, [x0, 92]
	mov	w6, 0
	mov	x4, 0
	mov	w2, w3
	b	.L215
	.p2align 3
.L228:
	ldr	w2, [x2, 92]
.L215:
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
	ldr	w7, [x1, 96]
	add	x2, x0, x2, lsl 2
	cmp	w7, w3
	bcs	.L213
	ldr	w1, [x1, 112]
	cmp	w1, wzr
	csel	w3, w3, w7, eq
.L213:
	cmp	w6, w5
	bne	.L228
	and	w3, w3, -16
	mov	w6, 0
	str	w3, [x0, 40]
	b	.L219
	.p2align 3
.L229:
	ldr	w2, [x1, 100]
	ldr	w7, [x1, 92]
	mov	x4, x2
	add	w2, w7, w2, lsr 3
	and	w4, w4, 7
	sub	w3, w2, w3
	ubfiz	w2, w3, 3, 4
	and	w3, w3, -16
	add	w2, w2, w4
	str	w3, [x1, 92]
	str	w2, [x1, 100]
.L217:
	add	w6, w6, 1
	cmp	w5, w6
	bls	.L218
	ldr	w3, [x0, 40]
.L219:
	sxtw	x2, w6
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 96]
	cbz	w2, .L229
	ldp	w4, w2, [x1, 100]
	ldp	w10, w9, [x1, 92]
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
	stp	w4, w3, [x1, 92]
	stp	w7, w2, [x1, 100]
	b	.L217
.L209:
	ldr	w1, [x0, 92]
	and	w1, w1, -16
	str	w1, [x0, 40]
.L218:
	mov	w0, 1
	b	.L222
.L226:
	madd	x1, x7, x10, x0
	mov	w3, w4
	str	w4, [x1, 132]
	b	.L211
	.size	Real9_ModifySliceMsg, .-Real9_ModifySliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Init
	.type	REAL9DEC_Init, %function
REAL9DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x20, 53248
	bl	_mcount
	ldr	x3, .LC27
	mov	x2, 55056
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x19, 1184
	bl	ResetVoQueue
	str	x21, [x20]
	add	x1, x20, 8192
	mov	w4, 15
	add	x1, x1, 3184
	mov	w2, 1
	add	x3, x1, 40960
	mov	w5, 8192
	mov	x0, x20
	str	w4, [x3, 860]
	str	w4, [x3, 864]
	ldr	w3, [x21, 8]
	strb	w3, [x1, 24]
	strb	wzr, [x1, 28]
	strb	w2, [x19, -224]
	str	w2, [x19, -220]
	str	w5, [x19, -192]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 1792]
	beq	.L233
	mov	w0, 0
.L231:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L233:
	ldr	x1, .LC29
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L231
	.size	REAL9DEC_Init, .-REAL9DEC_Init
	.align	3
.LC27:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Destroy
	.type	REAL9DEC_Destroy, %function
REAL9DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, 52336
	ldr	x1, .LC31
	add	x2, x19, x0
	mov	w0, 2
	ldr	w2, [x2, 1932]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_Destroy, .-REAL9DEC_Destroy
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Decode
	.type	REAL9DEC_Decode, %function
REAL9DEC_Decode:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	add	x23, x20, 53248
	bl	_mcount
	str	xzr, [x29, 296]
	add	x4, x29, 184
	add	x0, x29, 280
	ldp	w2, w1, [x23, -116]
	mov	w3, 8192
	str	w1, [x29, 296]
	stp	xzr, xzr, [x4]
	add	x4, x29, 216
	str	w3, [x23, -192]
	stp	xzr, xzr, [x0]
	add	x0, x29, 168
	str	w1, [x29, 288]
	stp	xzr, xzr, [x4]
	add	x4, x29, 232
	str	w2, [x29, 284]
	stp	xzr, xzr, [x0]
	add	x0, x29, 200
	str	w2, [x29, 292]
	stp	xzr, xzr, [x4]
	add	x4, x29, 248
	stp	xzr, xzr, [x0]
	stp	w2, w1, [x23, -108]
	stp	xzr, xzr, [x4]
	add	x4, x29, 264
	mov	w0, 1
	add	x1, x20, 16
	str	w0, [x23, -220]
	str	w0, [x29, 180]
	stp	xzr, xzr, [x4]
	str	w3, [x29, 208]
	str	x1, [x29, 136]
	cbz	x19, .L376
	ldr	x26, .LC36
	mov	w1, 0
	mov	x2, 11356
	add	x0, x20, 16
	add	x22, x20, 8192
	ldr	x3, [x26, 96]
	blr	x3
	add	x1, x22, 3184
	add	x0, x1, 40960
	str	wzr, [x0, 1896]
	ldr	w2, [x19, 20]
	str	w2, [x0, 1916]
	ldr	w2, [x19, 16]
	str	w2, [x0, 1900]
	ldr	x2, [x19]
	str	x2, [x20, 11376]
	ldr	w2, [x19, 20]
	str	w2, [x0, 1904]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 8]
	ldrb	w3, [x19, 10]
	cmp	w3, 1
	beq	.L238
	ldr	w3, [x19, 104]
	str	w3, [x0, 1908]
	ldr	x3, [x19, 88]
	str	x3, [x1, 16]
	ldr	w3, [x19, 108]
	str	w3, [x0, 1912]
	ldrb	w0, [x19, 98]
	strb	w0, [x1, 9]
	ldrb	w0, [x19, 98]
	cmp	w0, 1
	bne	.L377
	mov	w0, 65525
	sub	w1, w2, #10
	movk	w0, 0x2f, lsl 16
	cmp	w1, w0
	bhi	.L241
.L240:
	ldr	x1, [x20, 11376]
	add	x21, x22, 3184
	cbz	x1, .L241
	add	x19, x23, 1144
	mov	x0, x19
	bl	BsInit
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w24, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	add	w0, w24, 1
	cmp	w24, 255
	add	x24, x21, 40960
	mov	w2, w0
	str	w0, [x24, 868]
	bhi	.L241
	cbz	w0, .L242
	mov	w28, 0
	mov	w25, 3145727
	b	.L243
	.p2align 3
.L378:
	ldr	w2, [x24, 868]
	cmp	w2, w28
	bls	.L242
.L243:
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	uxtw	x1, w28
	rev	w0, w27
	add	x1, x1, 8192
	cmp	w0, w25
	add	w28, w28, 1
	add	x1, x21, x1, lsl 2
	str	w0, [x1, 9064]
	ble	.L378
	.p2align 2
.L241:
	mov	w27, 0
.L364:
	mov	w0, w27
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L377:
	ldr	w1, [x19, 24]
	mov	w27, 0
	ldr	w0, [x23, 1792]
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 112]
	ldr	w0, [x23, 1792]
	bl	SM_ReleaseStreamSeg
	mov	w0, w27
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L238:
	str	wzr, [x0, 1908]
	str	xzr, [x1, 16]
	str	wzr, [x0, 1912]
	mov	w0, 65525
	strb	wzr, [x1, 9]
	movk	w0, 0x2f, lsl 16
	sub	w1, w2, #10
	cmp	w1, w0
	bls	.L240
	b	.L241
	.p2align 3
.L376:
	mov	x2, 52336
	ldr	x1, .LC35
	add	x20, x20, x2
	mov	w27, 0
	ldr	w2, [x20, 1932]
	bl	dprint_vfmw
	mov	w0, w27
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L242:
	add	x24, x20, 49152
	sub	w5, w2, #1
	add	x3, x24, 4056
	mov	w1, 0
	add	x6, x22, 3184
	b	.L244
	.p2align 3
.L245:
	add	x0, x0, 8192
	ldr	w4, [x3], 4
	add	x0, x6, x0, lsl 2
	ldr	w0, [x0, 9064]
	cmp	w0, w4
	ble	.L241
.L244:
	cmp	w1, w5
	add	w0, w1, 1
	mov	x1, x0
	bne	.L245
	add	x25, x22, 3184
	lsl	w2, w2, 3
	add	x0, x25, 40960
	add	w21, w2, 1
	mov	w2, 65534
	mov	w1, 3145727
	movk	w2, 0x2f, lsl 16
	ldr	w28, [x0, 872]
	add	w28, w21, w28
	sub	w3, w28, #1
	cmp	w3, w2
	ccmp	w21, w1, 0, ls
	bgt	.L241
	ldr	w2, [x0, 1904]
	sub	w2, w2, w28
	cmp	w2, wzr
	ble	.L241
	ldr	x1, [x20, 11376]
	mov	x0, x19
	add	x1, x1, x28, sxtw
	bl	BsInit
	add	x1, x29, 168
	mov	x0, x19
	bl	Real9_CB_GetPictureHeader
	cmp	w0, 1
	mov	w27, w0
	bne	.L379
	ldrb	w0, [x25, 28]
	cbz	w0, .L247
	ldr	w0, [x23, -200]
	ldr	w1, [x29, 200]
	cmp	w1, w0
	beq	.L380
.L247:
	ldr	x0, .LC39
	ldr	x4, [x0]
	cbz	x4, .L249
	ldr	w0, [x23, -200]
	mov	w3, 8
	strh	w0, [x29, 160]
	add	x2, x29, 160
	ldr	w0, [x23, -204]
	mov	w1, 2
	strh	w0, [x29, 162]
	ldr	w0, [x29, 200]
	strh	w0, [x29, 164]
	ldr	w0, [x29, 196]
	strh	w0, [x29, 166]
	ldr	w0, [x23, 1792]
	blr	x4
.L249:
	ldr	w0, [x23, 1792]
	bl	FSP_GetFspType
	cbnz	w0, .L250
	add	x25, x29, 304
	ldr	w0, [x23, 1792]
	add	x2, x29, 156
	add	x1, x29, 152
	stp	wzr, wzr, [x29, 152]
	str	wzr, [x25, -144]!
	mov	x3, x25
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x20]
	ldr	w2, [x0, 764]
	cmp	w2, 1
	beq	.L381
.L250:
	add	x0, x22, 3184
	add	x3, x23, 1184
	add	x25, x0, 40960
	mov	x1, x0
	ldr	w0, [x23, 1792]
	mov	w2, 1
	stp	x3, x1, [x29, 120]
	ldr	w1, [x25, 2036]
	bl	FSP_ClearLogicFs
	ldr	w1, [x25, 2032]
	mov	w2, 1
	ldr	w0, [x23, 1792]
	bl	FSP_ClearLogicFs
	str	wzr, [x25, 2032]
	str	wzr, [x25, 2036]
	ldr	w0, [x23, 1792]
	bl	FSP_GetNullLogicFs
	str	w0, [x25, 2032]
	str	w0, [x25, 2036]
	add	x1, x23, 1184
	ldr	x0, [x29, 128]
	strb	wzr, [x0, 25]
	ldr	w0, [x23, 1792]
	bl	FSP_ClearNotInVoQueue
	ldr	w2, [x29, 200]
	cmp	w2, 512
	bhi	.L382
	ldr	w0, [x29, 196]
	cmp	w0, 512
	mov	w3, w0
	bhi	.L257
	ldr	x1, [x20]
	ldr	w3, [x1, 764]
	cbnz	w3, .L259
	ldr	w1, [x1, 28]
	cmp	w1, 25
	beq	.L383
.L259:
	ldr	w0, [x23, 1792]
	bl	FSP_GetFspType
	cbz	w0, .L365
.L368:
	ldp	w0, w2, [x29, 196]
.L261:
	ldr	x1, .LC45
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	add	x2, x29, 168
	mov	x1, x20
	mov	w0, 6
	bl	Real9_ArrangeVHBMem
	cbz	w0, .L384
.L248:
	ldr	x3, [x26, 104]
	add	x0, x24, 3864
	add	x1, x29, 168
	mov	x2, 136
	str	x0, [x29, 120]
	add	x25, x22, 3184
	blr	x3
	ldr	x0, [x20]
	ldr	w0, [x0, 8]
	strb	w0, [x25, 24]
	mov	x0, x20
	bl	Real9_GetImageBuffer
	cbz	w0, .L385
	add	x26, x25, 40960
	ldr	w0, [x23, 1792]
	ldr	w1, [x26, 2040]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L372
	ldr	x0, [x20]
	mov	x4, -1
	ldr	x1, .LC51
	ldr	x0, [x0, 56]
	str	x0, [x2, 584]
	mov	w0, 29
	ldr	x3, [x20]
	ldr	x3, [x3, 72]
	str	x3, [x2, 592]
	ldr	x3, [x20]
	ldr	x3, [x3, 88]
	str	x3, [x2, 600]
	ldr	x3, [x20]
	ldr	w3, [x3, 104]
	str	w3, [x2]
	ldr	x3, [x20]
	ldr	w3, [x3, 108]
	str	w3, [x2, 4]
	ldr	x3, [x20]
	ldr	w3, [x3, 112]
	str	w3, [x2, 8]
	ldr	x3, [x20]
	ldr	w3, [x3, 128]
	str	w3, [x2, 12]
	ldr	x3, [x20]
	str	x4, [x3, 56]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
	ldr	w0, [x23, -216]
	cmp	w0, 2
	beq	.L373
	cmp	w0, 1
	ldrb	w0, [x25, 25]
	beq	.L386
	cmp	w0, wzr
	mov	w0, 2
	csinc	w0, w0, wzr, ne
.L268:
	add	x25, x22, 3184
	strb	w0, [x22, 3209]
	add	x25, x25, 40960
	ldr	w2, [x25, 2032]
	ldr	w0, [x25, 2036]
	cmp	w2, w0
	beq	.L269
	ldr	x1, .LC53
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x23, 1792]
	mov	w2, 0
	ldr	w1, [x25, 2032]
	bl	FSP_SetRef
.L269:
	add	x26, x22, 3184
	mov	w2, 1
	add	x25, x26, 40960
	ldr	w0, [x25, 2036]
	ldr	w1, [x25, 2040]
	str	w1, [x25, 2036]
	str	w0, [x25, 2032]
	ldr	w0, [x23, 1792]
	bl	FSP_SetRef
	ldr	w0, [x23, 1792]
	ldr	w1, [x25, 2032]
	bl	FSP_RemovePmv
	ldr	x1, .LC55
	mov	w0, 13
	ldr	w2, [x25, 2040]
	bl	dprint_vfmw
	ldrb	w0, [x22, 3208]
	cmp	w0, 4
	bne	.L271
	ldr	w0, [x23, -216]
	cbnz	w0, .L273
	str	wzr, [x25, 2048]
.L271:
	add	x26, x22, 3184
	ldr	w0, [x23, 1792]
	add	x26, x26, 40960
	ldr	w1, [x26, 2040]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x26, 2032]
	ldr	w0, [x23, 1792]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x26, 2036]
	ldr	w0, [x23, 1792]
	bl	FSP_GetLogicFs
	mov	x26, x0
	cmp	x25, xzr
	ccmp	x24, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L387
	ldr	x0, [x25, 32]
	cbz	x0, .L277
	ldr	x1, [x25, 40]
	cbz	x1, .L277
	ldr	x1, [x26, 32]
	cbz	x1, .L279
	ldr	w5, [x1, 8]
.L280:
	ldr	x0, [x29, 136]
	str	w5, [x0, 44]
	ldr	x0, [x24, 32]
	cbz	x0, .L388
.L369:
	ldr	x8, [x29, 136]
	ldr	w4, [x0, 8]
	ldr	x1, .LC62
	str	w4, [x8, 48]
	ldr	x0, [x25, 32]
	ldr	w2, [x0, 8]
	mov	w0, 13
	str	w2, [x8, 52]
	ldr	w6, [x25, 8]
	str	w6, [x8, 64]
	ldr	w7, [x26, 8]
	str	w7, [x8, 68]
	ldr	x3, [x25, 40]
	ldr	w3, [x3, 8]
	str	w3, [x8, 56]
	bl	dprint_vfmw
	ldr	x0, [x25, 40]
	ldr	x3, [x29, 136]
	ldr	w0, [x0, 24]
	str	w0, [x3, 60]
	add	x0, x22, 3184
	add	x0, x0, 40960
	ldr	x1, [x25, 40]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2004]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 60]
	str	w0, [x3, 80]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 44]
	str	w0, [x3, 84]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 48]
	str	w0, [x3, 88]
	ldr	w0, [x23, -216]
	cmp	w0, 2
	beq	.L389
.L283:
	ldr	w0, [x23, -188]
	str	w0, [x25, 16]
	ldr	x2, [x29, 136]
	ldr	w0, [x23, -176]
	mov	w3, w0
	ldr	w0, [x23, -216]
	strb	w0, [x20, 16]
	cmp	w0, 2
	add	x0, x22, 3184
	ldr	w1, [x23, -200]
	add	x0, x0, 40960
	str	w1, [x2, 4]
	str	w3, [x29, 112]
	ldr	w1, [x23, -204]
	str	w1, [x2, 8]
	ldr	w1, [x0, 1956]
	str	w1, [x2, 12]
	ldr	w1, [x0, 1960]
	str	w1, [x2, 16]
	str	w3, [x2, 20]
	ldr	w1, [x0, 860]
	str	w1, [x2, 24]
	ldr	w1, [x0, 864]
	str	w1, [x2, 28]
	beq	.L288
	str	w3, [x0, 860]
.L288:
	mov	x0, x19
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	add	w0, w0, w1
	and	w0, w0, 7
	sub	w0, w0, w1
	add	x1, x22, 3184
	add	x1, x1, 40960
	str	w0, [x23, -76]
	ldr	w0, [x1, 868]
	cmp	w0, 1
	beq	.L390
	ldr	w25, [x1, 872]
	ldr	w0, [x1, 876]
.L370:
	sub	w25, w0, w25
	mov	x0, x19
	lsl	w25, w25, 3
	add	x24, x22, 3184
	bl	BsPos
	sub	w0, w25, w0
	add	x25, x24, 40960
	str	w0, [x23, -72]
	mov	x0, x19
	ldr	w1, [x25, 1900]
	add	w28, w28, w1
	bl	BsPos
	cmp	w0, wzr
	add	w1, w0, 7
	ldr	x3, [x29, 136]
	csel	w0, w1, w0, lt
	ldr	w2, [x23, -180]
	ldr	w1, [x23, -172]
	mov	w7, 1
	ldr	w4, [x29, 112]
	add	w0, w28, w0, asr 3
	str	w4, [x23, -96]
	str	w0, [x23, -68]
	stp	w2, wzr, [x23, -88]
	stp	wzr, wzr, [x23, -64]
	str	wzr, [x23, -56]
	str	w1, [x23, -92]
	str	w0, [x3, 92]
	ldr	w0, [x23, -76]
	str	w0, [x3, 100]
	ldr	w0, [x23, -72]
	stp	wzr, w0, [x3, 104]
	str	w7, [x3, 32]
	str	wzr, [x3, 96]
	stp	wzr, w2, [x3, 112]
	str	w1, [x3, 120]
	str	wzr, [x3, 128]
	str	w4, [x3, 124]
	ldr	w0, [x25, 868]
	cmp	w0, w7
	bls	.L308
	ldr	w6, [x25, 876]
	mov	w0, 3145727
	add	w6, w21, w6
	cmp	w6, w0
	bgt	.L296
	cmp	w6, wzr
	ble	.L296
	ldr	w2, [x25, 1904]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L296
	mov	x28, x25
	mov	w26, w7
	add	x25, x29, 160
	str	w7, [x29, 108]
	str	w0, [x29, 116]
	b	.L299
	.p2align 3
.L300:
	ldr	w0, [x28, 868]
	add	w26, w26, 1
	cmp	w0, w26
	bls	.L308
	uxtw	x0, w26
	add	x0, x0, 8192
	add	x0, x24, x0, lsl 2
	ldr	w6, [x0, 9064]
	ldr	w0, [x29, 116]
	add	w6, w21, w6
	cmp	w6, w0
	bgt	.L296
	cmp	w6, wzr
	ble	.L296
	ldr	w2, [x28, 1904]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L296
.L299:
	ldr	x1, [x24]
	mov	x0, x19
	str	w6, [x29, 128]
	add	x1, x1, x6, sxtw
	bl	BsInit
	ldr	x5, [x29, 120]
	add	x2, x29, 152
	mov	x4, x25
	add	x3, x29, 156
	mov	w1, 0
	mov	x0, x19
	bl	Real9_CB_GetSliceHeader
	cmp	w0, 1
	mov	w2, w0
	ldr	w6, [x29, 128]
	bne	.L300
	ldr	w1, [x29, 152]
	ldr	w0, [x23, -200]
	str	w1, [x29, 128]
	cbz	w0, .L391
	ldr	w0, [x29, 160]
	ldr	w1, [x29, 112]
	cmp	w0, wzr
	str	w6, [x29, 104]
	csel	w0, w1, w0, lt
	str	w0, [x29, 112]
	mov	x0, x19
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	ldr	w6, [x29, 104]
	add	w0, w0, w1
	and	w0, w0, 7
	sub	w0, w0, w1
	str	w0, [x23, -76]
	ldr	w0, [x28, 868]
	sub	w0, w0, #1
	cmp	w0, w26
	beq	.L392
	cmp	w26, 254
	bhi	.L393
	add	w0, w26, 1
	uxtw	x1, w26
	add	x0, x0, 8192
	add	x1, x1, 8192
	str	w6, [x29, 100]
	add	x0, x24, x0, lsl 2
	add	x1, x24, x1, lsl 2
	ldr	w0, [x0, 9064]
	ldr	w1, [x1, 9064]
.L371:
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w1, w1, 3
	str	w1, [x29, 104]
	bl	BsPos
	ldp	w6, w1, [x29, 100]
	sub	w0, w1, w0
	str	w0, [x23, -72]
	ldr	w0, [x28, 1900]
	add	w6, w6, w0
	mov	x0, x19
	str	w6, [x29, 104]
	bl	BsPos
	cmp	w0, wzr
	ldr	w1, [x29, 128]
	str	w1, [x23, -84]
	ldr	w1, [x29, 112]
	str	w1, [x23, -96]
	ldr	w1, [x29, 108]
	ldr	x4, [x29, 136]
	ldr	w6, [x29, 104]
	sxtw	x2, w1
	add	w1, w1, 1
	mov	w3, w1
	lsl	x1, x2, 2
	sub	x1, x1, x2
	str	wzr, [x23, -56]
	lsl	x1, x1, 2
	str	w3, [x29, 108]
	sub	x1, x1, x2
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	ldr	w2, [x23, -172]
	add	x1, x4, x1, lsl 2
	str	w2, [x23, -92]
	ldr	w2, [x23, -180]
	add	w0, w6, w0, asr 3
	stp	wzr, wzr, [x23, -64]
	str	w2, [x23, -88]
	mov	x2, x4
	str	w0, [x23, -68]
	cmp	w3, 131
	str	w0, [x1, 92]
	ldr	w0, [x23, -76]
	str	w0, [x1, 100]
	ldr	w0, [x23, -72]
	str	w0, [x1, 108]
	ldr	w0, [x23, -56]
	str	w0, [x1, 96]
	ldr	w0, [x23, -64]
	str	w0, [x1, 104]
	ldr	w0, [x23, -60]
	str	w0, [x1, 112]
	ldr	w0, [x23, -88]
	str	w0, [x1, 116]
	ldr	w0, [x23, -92]
	str	w0, [x1, 120]
	ldr	w0, [x23, -96]
	str	w0, [x1, 124]
	ldr	w0, [x23, -84]
	str	w0, [x1, 128]
	str	w3, [x2, 32]
	ble	.L300
	mov	x0, x20
	bl	Real9_ModifySliceMsg
	cmp	w0, 1
	bne	.L394
	ldr	x0, [x29, 136]
	str	x0, [x20, 8]
	b	.L300
.L383:
	ldr	x1, [x29, 128]
	ldrb	w1, [x1, 28]
	cbnz	w1, .L261
.L365:
	add	x0, x23, 1184
	bl	ResetVoQueue
	b	.L368
.L379:
	ldr	x1, .LC38
	mov	w0, 1
	mov	w27, 0
	bl	dprint_vfmw
	b	.L364
.L382:
	ldr	w3, [x29, 196]
.L257:
	ldr	x1, .LC43
	mov	w0, 18
	mov	w27, 0
	bl	dprint_vfmw
	b	.L364
.L385:
	add	x25, x25, 40960
	ldr	x1, .LC49
	mov	w27, 0
	ldr	w2, [x25, 1932]
	bl	dprint_vfmw
	b	.L364
.L380:
	ldr	w0, [x23, -204]
	ldr	w1, [x29, 196]
	cmp	w1, w0
	bne	.L247
	b	.L248
.L381:
	ldr	w0, [x29, 160]
	cmp	w0, wzr
	bgt	.L253
	ldr	w0, [x29, 156]
	cmp	w0, 32
	bgt	.L253
	ldr	x0, [x20, 8]
	cbnz	x0, .L253
	ldr	w3, [x23, 1016]
	cbz	w3, .L250
	ldr	w4, [x23, -200]
	cbz	w4, .L250
	ldr	w0, [x23, 1796]
	ldr	w7, [x29, 196]
	cmp	w7, w0
	beq	.L250
	ldr	w0, [x23, 1800]
	ldr	w6, [x29, 200]
	cmp	w6, w0
	beq	.L250
	ldr	x1, .LC41
	mov	w0, w2
	ldr	w5, [x23, -204]
	bl	dprint_vfmw
	ldr	x0, .LC39
	ldr	x4, [x0]
	ldr	w0, [x29, 196]
	str	w0, [x23, 1796]
	ldr	w0, [x29, 200]
	str	w0, [x23, 1800]
	cbz	x4, .L250
	ldr	w0, [x23, 1792]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L250
	.p2align 3
.L384:
	ldr	x1, .LC47
	mov	w0, 1
	mov	w27, 0
	bl	dprint_vfmw
	b	.L364
.L296:
	add	x1, x22, 3184
	ldr	w0, [x23, 1792]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w27, 0
	ldr	w1, [x1, 2040]
	bl	FSP_ClearLogicFs
	b	.L364
.L373:
	ldrb	w0, [x25, 25]
	cmp	w0, 1
	bls	.L372
	ldrb	w0, [x25, 24]
	cmp	w0, 4
	bne	.L271
.L312:
	add	x0, x22, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2048]
	cbnz	w1, .L271
	ldr	w1, [x0, 2040]
	mov	w2, 1
	ldr	w0, [x23, 1792]
	mov	w27, 0
	bl	FSP_ClearLogicFs
	b	.L364
.L386:
	cbz	w0, .L241
	mov	w0, 2
	b	.L268
.L253:
	mov	w27, -2
	b	.L364
.L392:
	uxtw	x0, w26
	str	w6, [x29, 100]
	add	x0, x0, 8192
	add	x0, x24, x0, lsl 2
	ldr	w1, [x0, 9064]
	ldr	w0, [x28, 1904]
	sub	w0, w0, w21
	b	.L371
.L387:
	ldr	x2, .LC56
	mov	w3, 1958
	ldr	x1, .LC58
	mov	w0, 0
	mov	w27, 0
	bl	dprint_vfmw
	b	.L364
.L273:
	cmp	w0, 2
	beq	.L312
	cmp	w0, 1
	bne	.L271
	str	w0, [x25, 2048]
	b	.L271
.L279:
	ldr	w5, [x0, 8]
	b	.L280
.L277:
	add	x1, x22, 3184
	ldr	w0, [x23, 1792]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w27, 0
	ldr	w1, [x1, 2040]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC60
	mov	w0, 0
	bl	dprint_vfmw
	b	.L364
.L308:
	ldr	x0, [x29, 136]
	mov	w19, 1
	str	w19, [x0, 36]
	ldr	x3, [x20, 8]
	cbz	x3, .L395
	ldr	x0, [x20]
	ldr	w1, [x0, 920]
	cmp	w1, 1
	beq	.L313
.L310:
	cmp	w1, 2
	beq	.L396
.L311:
	ldr	w1, [x0, 632]
	str	w1, [x20, 88]
	ldr	w0, [x0, 684]
	str	w0, [x20, 92]
	b	.L364
.L390:
	ldr	w0, [x1, 1904]
	ldr	w25, [x1, 872]
	sub	w0, w0, w21
	b	.L370
.L389:
	ldr	w2, [x24, 16]
	ldr	w1, [x23, -188]
	ldr	w0, [x26, 16]
	subs	w1, w1, w2
	sub	w0, w0, w2
	bmi	.L397
.L284:
	tbnz	w0, #31, .L398
.L285:
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w0, wzr
	ble	.L316
	sub	w3, w0, w1
	lsl	w4, w1, 14
	lsl	w3, w3, 14
	sdiv	w4, w4, w0
	sdiv	w3, w3, w0
.L287:
	add	x2, x22, 3184
	add	x2, x2, 40960
	add	x5, x2, 1792
	stp	w1, w0, [x5, 156]
	stp	w4, w3, [x5, 164]
	b	.L283
.L388:
	ldr	x0, [x25, 32]
	b	.L369
.L372:
	ldr	w0, [x23, 1792]
	mov	w2, 1
	ldr	w1, [x26, 2040]
	mov	w27, 0
	bl	FSP_ClearLogicFs
	b	.L364
.L391:
	add	x11, x24, 40960
	ldr	w0, [x23, 1792]
	mov	w27, 0
	ldr	w1, [x11, 2040]
	bl	FSP_ClearLogicFs
	b	.L364
.L397:
	ldr	w2, [x23, -192]
	add	w1, w1, w2
	b	.L284
.L396:
	ldr	w1, [x0, 924]
	cmp	w1, wzr
	ble	.L311
	ldr	x1, [x20, 8]
	cbz	x1, .L311
	ldrb	w1, [x1]
	cmp	w1, 2
	bne	.L311
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w27, 0
	ldr	w1, [x23, 1128]
	ldr	w0, [x23, 1792]
	bl	FSP_SetDisplay
	ldr	x3, [x20]
	mov	x1, x20
	mov	w0, 9
	ldr	w2, [x3, 924]
	sub	w2, w2, #1
	str	w2, [x3, 924]
	bl	ReleasePacket
	b	.L364
.L394:
	ldr	w0, [x23, 1792]
	mov	w2, 1
	ldr	w1, [x28, 2040]
	mov	w27, 0
	bl	FSP_ClearLogicFs
	b	.L364
.L393:
	ldr	x1, .LC64
	mov	w2, 2190
	mov	w0, 22
	mov	w27, 0
	bl	dprint_vfmw
	b	.L364
.L395:
	mov	x0, x20
	bl	Real9_ModifySliceMsg
	cmp	w0, 1
	bne	.L399
	ldr	x0, [x20]
	ldr	x2, [x29, 136]
	str	x2, [x20, 8]
	ldr	w1, [x0, 920]
	cmp	w1, 1
	bne	.L310
	cbz	x2, .L311
	mov	x3, x2
.L313:
	ldrb	w1, [x3]
	cmp	w1, 2
	bne	.L311
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w27, 0
	ldr	w1, [x23, 1128]
	ldr	w0, [x23, 1792]
	bl	FSP_SetDisplay
	mov	x1, x20
	mov	w0, 9
	bl	ReleasePacket
	b	.L364
.L316:
	mov	w3, 0
	mov	w4, 0
	b	.L287
.L398:
	ldr	w2, [x23, -192]
	add	w0, w0, w2
	b	.L285
.L399:
	add	x1, x22, 3184
	ldr	w0, [x23, 1792]
	add	x1, x1, 40960
	mov	w2, w19
	mov	w27, 0
	ldr	w1, [x1, 2040]
	bl	FSP_ClearLogicFs
	b	.L364
	.size	REAL9DEC_Decode, .-REAL9DEC_Decode
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC36:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC39:
	.xword	g_event_report
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
.LC56:
	.xword	.LANCHOR1
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_RecycleImage
	.type	REAL9DEC_RecycleImage, %function
REAL9DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L402
	add	x19, x19, 53248
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 1792]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 1792]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L402:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_RecycleImage, .-REAL9DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_GetRemainImg
	.type	REAL9DEC_GetRemainImg, %function
REAL9DEC_GetRemainImg:
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
	beq	.L404
	mov	x21, 52336
	add	x20, x19, 53248
	add	x21, x19, x21
	ldr	w0, [x20, 1792]
	ldr	w1, [x21, 2036]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L404
	ldr	w0, [x20, 1792]
	ldr	w1, [x21, 2036]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L417
.L404:
	add	x22, x20, 1184
.L408:
	mov	x0, x22
	bl	GetVoLastImageID
.L414:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L417:
	mov	x0, x19
	add	x22, x20, 1184
	bl	Real9_SetImgFormat
	mov	w2, 1
	str	w2, [x23, 180]
	ldr	w0, [x20, 1792]
	ldr	w1, [x21, 2036]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 1792]
	mov	x4, x23
	mov	x3, x22
	mov	x2, x19
	mov	w1, 9
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L405
	ldr	w0, [x20, 1792]
	mov	w2, 0
	ldr	w1, [x21, 2036]
	bl	FSP_SetDisplay
	b	.L408
	.p2align 3
.L405:
	ldr	w0, [x23, 152]
	cmp	w0, 100
	bhi	.L404
	ldr	w0, [x23, 68]
	cmp	w0, 31
	bls	.L404
	ldr	w1, [x23, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L414
	b	.L408
	.size	REAL9DEC_GetRemainImg, .-REAL9DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_VDMPostProc
	.type	REAL9DEC_VDMPostProc, %function
REAL9DEC_VDMPostProc:
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
	ldr	x1, .LC66
	mov	w2, w22
	mov	w0, 22
	add	x19, x20, 8192
	add	x25, x19, 3184
	bl	dprint_vfmw
	add	x23, x25, 40960
	ldr	x2, [x20, 8]
	mov	x1, x20
	mov	w0, 9
	ldrb	w3, [x2, 1]
	strb	w3, [x21, -232]
	ldr	w2, [x2, 72]
	str	w2, [x21, -228]
	bl	ReleasePacket
	ldr	w0, [x21, 1792]
	ldr	w1, [x23, 2040]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L427
	ldr	w1, [x23, 696]
	strb	w1, [x19, 3210]
	cmp	w1, 2
	beq	.L420
	and	w24, w24, 31
	str	w24, [x23, 864]
.L420:
	tbnz	w22, #31, .L428
	mov	w1, 100
	cmp	w22, w1
	csel	w22, w22, w1, le
.L421:
	ldr	x1, .LC68
	str	w22, [x0, 152]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	Real9_SetImgFormat
	ldrb	w1, [x19, 3208]
	add	x0, x19, 3184
	cmp	w1, 2
	beq	.L424
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L424
	add	x1, x0, 40960
	ldr	w2, [x1, 696]
	cmp	w2, 2
	beq	.L424
	ldrb	w0, [x0, 25]
	cmp	w0, 1
	bls	.L429
	ldr	w1, [x1, 2032]
.L425:
	add	x0, x19, 3184
	cmn	w1, #1
	add	x0, x0, 40960
	str	w1, [x0, 2044]
	beq	.L426
.L443:
	add	x22, x19, 3184
	ldr	w0, [x21, 1792]
	add	x22, x22, 40960
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	ldr	w23, [x22, 2044]
	ldr	w0, [x21, 1792]
	mov	w1, w23
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC70
	mov	w2, w23
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x21, 1792]
	mov	w2, 1
	ldr	w1, [x22, 2044]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1792]
	mov	x4, x24
	add	x3, x21, 1184
	mov	x2, x20
	mov	w1, 9
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L442
.L426:
	add	x19, x19, 3184
	mov	w0, 1
	add	x19, x19, 40960
	ldr	w1, [x19, 1932]
	add	w1, w1, w0
	str	w1, [x19, 1932]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L424:
	add	x0, x19, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2040]
	str	w1, [x0, 2044]
	cmn	w1, #1
	bne	.L443
	b	.L426
	.p2align 3
.L428:
	mov	w22, 0
	b	.L421
	.p2align 3
.L442:
	ldr	w0, [x21, 1792]
	mov	w2, 0
	ldr	w1, [x22, 2044]
	bl	FSP_SetDisplay
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L429:
	mov	w1, -1
	b	.L425
	.p2align 3
.L427:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	REAL9DEC_VDMPostProc, .-REAL9DEC_VDMPostProc
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_GetImageBuffer
	.type	REAL9DEC_GetImageBuffer, %function
REAL9DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 53248
	bl	_mcount
	ldr	w0, [x19, 1792]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L445
	ldr	w0, [x19, 1792]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L450
.L445:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L450:
	ldr	w0, [x19, 1792]
	add	x1, x19, 1184
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_GetImageBuffer, .-REAL9DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Support
	.type	REAL9DEC_Support, %function
REAL9DEC_Support:
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
	.size	REAL9DEC_Support, .-REAL9DEC_Support
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
	.align	3
.LANCHOR1 = . + 0
	.type	__FUNCTION__.11696, %object
	.size	__FUNCTION__.11696, 16
__FUNCTION__.11696:
	.string	"REAL9DEC_Decode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC5:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC7:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC9:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC11:
	ASCII(.string	"image size abnormal (%dx%d) in MB\n" )
	.zero	5
.LC13:
	ASCII(.string	"real9 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
.LC16:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC28:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC30:
	ASCII(.string	"Decoding quits at frm %d\n" )
	.zero	6
.LC34:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
.LC37:
	ASCII(.string	"Real9_CB_GetPictureHeader Error!\n" )
	.zero	6
.LC40:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC42:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC44:
	ASCII(.string	"new seq size %d * %d\n" )
	.zero	2
.LC46:
	ASCII(.string	"Real9_ArrangeVHBMem err\n" )
	.zero	7
.LC48:
	ASCII(.string	"Fatal Error: frm%d, get image buffer failed\n" )
	.zero	3
.LC50:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC52:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC54:
	ASCII(.string	"++++++++++ ref %d\n" )
	.zero	5
.LC57:
	ASCII(.string	"CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == pFwd) || (NULL == pBwd)!!\n" )
	.zero	2
.LC59:
	ASCII(.string	"CurFsID abnormal!\n" )
	.zero	5
.LC61:
	ASCII(.string	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n" )
.LC63:
	ASCII(.string	"line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\n" )
	.zero	6
.LC65:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC67:
	ASCII(.string	"DEBUG: DEC over\n" )
	.zero	7
.LC69:
	ASCII(.string	"insert buf %d ref %d\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
