#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"hevc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	HEVC_ComparePicByPocAsc, %function
HEVC_ComparePicByPocAsc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 8]
	ldr	w2, [x2, 8]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	HEVC_ComparePicByPocAsc, .-HEVC_ComparePicByPocAsc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_UpdateInterLayerReflist, %function
HEVC_UpdateInterLayerReflist:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w27, [x20, 5584]
	cbz	w27, .L56
	ldr	w10, [x20, 6912]
	ldr	x7, [x20, 2992]
	cmp	w10, wzr
	ble	.L31
	sxtw	x27, w27
	mov	w24, 0
	mov	w25, 0
	mov	w26, 0
	add	x23, x7, 12288
	lsl	x22, x27, 1
	mov	w21, 1
	.p2align 2
.L25:
	add	x1, x20, x26, sxtw 2
	add	x0, x23, 132
	add	x2, x27, 1032
	ldr	w3, [x0, 4128]
	ldrsw	x1, [x1, 6916]
	ldr	w2, [x0, x2, lsl 2]
	add	x1, x22, x1
	add	x1, x1, 1044
	cmp	w2, w3
	ldr	w6, [x0, x1, lsl 2]
	add	x0, x0, x6, sxtw 2
	ble	.L57
	ldr	w0, [x0, 4128]
	cmp	w2, w0
	cset	w28, ge
.L9:
	ldr	w4, [x20, 3372]
	cbz	w4, .L11
	mov	w0, 0
	ldr	w5, [x20, 5564]
	b	.L24
	.p2align 3
.L12:
	cmp	w0, w4
	beq	.L11
.L24:
	sxtw	x2, w0
	add	w0, w0, 1
	add	x1, x20, x2, lsl 3
	ldr	x1, [x1, 3680]
	ldr	w3, [x1, 8]
	cmp	w3, w5
	bne	.L12
	ldr	w3, [x1, 32]
	cmp	w3, w6
	bne	.L12
	add	x19, x20, x2, lsl 3
	mov	w0, 1
	strb	w0, [x1, 1]
	ldr	x0, [x19, 3680]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L58
.L13:
	str	wzr, [x0, 64]
	ldr	x0, [x19, 3680]
	str	w21, [x0, 60]
	ldr	x0, [x19, 3680]
	str	w21, [x0, 72]
	ldr	x4, [x19, 3680]
	cbz	x4, .L59
	ldr	w10, [x20, 5584]
	uxtw	x6, w10
	lsl	x0, x6, 5
	add	x0, x0, x6, lsl 3
	add	x1, x20, x0, lsl 3
	sub	x0, x1, x0
	ldr	w3, [x0, 14172]
	cbz	w3, .L15
	ldr	w0, [x0, 14180]
	cbz	w0, .L60
	mov	w0, 280
	mov	x1, 14184
	mov	w2, 0
	umaddl	x0, w10, w0, x1
	add	x0, x20, x0
	b	.L18
	.p2align 3
.L22:
	ldr	w1, [x0], 4
	cbz	w1, .L16
.L18:
	add	w2, w2, 1
	cmp	w2, w3
	bne	.L22
.L15:
	cbz	w28, .L23
	add	x0, x20, x25, sxtw 3
	add	w25, w25, 1
	str	x4, [x0, 3408]
	ldr	w10, [x20, 6912]
	.p2align 2
.L11:
	add	w26, w26, 1
	cmp	w10, w26
	bgt	.L25
	mov	w2, w25
	mov	w1, w24
.L7:
	ldr	w0, [x20, 3368]
	str	w2, [x20, 3396]
	cmp	w0, w25
	str	w1, [x20, 3400]
	ble	.L29
	.p2align 2
.L41:
	add	x1, x20, x25, sxtw 3
	add	w25, w25, 1
	cmp	w25, w0
	str	xzr, [x1, 3408]
	bne	.L41
.L29:
	cmp	w0, w24
	ble	.L4
	.p2align 2
.L40:
	add	x1, x20, x24, sxtw 3
	add	w24, w24, 1
	cmp	w24, w0
	str	xzr, [x1, 3544]
	bne	.L40
.L4:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L57:
	ldr	w0, [x0, 4128]
	mov	w28, 1
	cmp	w2, w0
	ble	.L9
	cmp	w2, w3
	cset	w28, ge
	b	.L9
.L23:
	add	x0, x20, x24, sxtw 3
	add	w24, w24, 1
	str	x4, [x0, 3544]
	ldr	w10, [x20, 6912]
	b	.L11
.L60:
	mov	w2, 0
.L16:
	ldr	w1, [x4, 28]
	ldr	w0, [x20, 276]
	str	x4, [x29, 120]
	str	x6, [x29, 104]
	stp	w2, w10, [x29, 112]
	bl	FSP_GetLogicFs
	ldr	x4, [x29, 120]
	cbz	x0, .L19
	ldr	x1, [x0, 32]
	ldp	w2, w10, [x29, 112]
	ldr	x6, [x29, 104]
	cbz	x1, .L19
	uxtw	x3, w2
	mov	w1, 70
	lsl	x5, x6, 5
	umaddl	x1, w10, w1, x3
	add	x5, x5, x6, lsl 3
	add	x1, x20, x1, lsl 2
	str	w21, [x1, 14180]
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x1, 14244]
	ldr	w0, [x4, 8]
	str	w0, [x1, 14308]
	add	x0, x20, x5, lsl 3
	sub	x5, x0, x5
	add	x0, x5, x3
	add	x0, x0, 12288
	ldr	w3, [x5, 14176]
	add	w3, w3, 1
	str	w3, [x5, 14176]
	ldr	w3, [x4, 32]
	str	w3, [x1, 14372]
	str	w2, [x4, 36]
	strb	w21, [x0, 2148]
	ldr	x4, [x19, 3680]
	b	.L15
.L56:
	str	wzr, [x20, 3396]
	str	wzr, [x20, 3400]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L58:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3680]
	b	.L13
.L31:
	mov	w1, 0
	mov	w2, 0
	mov	w24, 0
	mov	w25, 0
	b	.L7
.L19:
	ldr	w3, [x4, 8]
	mov	x5, x0
	ldr	w2, [x4, 28]
	mov	x6, 0
	ldrb	w4, [x4, 1]
	mov	w0, 0
	ldr	x1, .LC7
	bl	dprint_vfmw
	ldr	x4, [x19, 3680]
	b	.L15
.L59:
	ldr	x2, .LC3
	mov	w3, 200
	ldr	x1, .LC5
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x4, [x19, 3680]
	b	.L15
	.size	HEVC_UpdateInterLayerReflist, .-HEVC_UpdateInterLayerReflist
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.15, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.15:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 5588]
	mov	w4, 5036
	ldr	x2, [x19, 2960]
	add	x13, x19, 4096
	add	x17, x13, 2388
	ldr	x1, [x19, 2952]
	mov	w3, 12668
	ldr	w7, [x19, 6484]
	smaddl	x2, w0, w4, x2
	ldr	w4, [x17, 4]
	mov	w0, 1
	ldr	w18, [x17, 8]
	ldr	w2, [x2, 32]
	add	w7, w7, w4
	cmp	w7, w18
	mov	w15, w7
	smaddl	x1, w2, w3, x1
	ldr	w5, [x1, 116]
	lsl	w5, w0, w5
	bcs	.L62
	ldr	w3, [x19, 3372]
	mov	w9, 0
	mov	w8, 0
	.p2align 2
.L63:
	sxtw	x16, w15
	cbz	w3, .L69
	add	x12, x19, x16, lsl 2
	mov	w14, 0
	mov	w0, 0
	ldr	w4, [x12, 5640]
	b	.L66
	.p2align 3
.L103:
	ldr	x1, [x2, 3680]
	ldr	w2, [x1, 60]
	cbz	w2, .L65
	ldr	w6, [x1, 8]
	ldr	w2, [x12, 6584]
	cmp	w6, w2
	beq	.L101
.L65:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L102
.L66:
	add	x2, x19, x0, sxtw 3
	cbnz	w4, .L103
	ldr	x1, [x2, 3680]
	ldr	w2, [x1, 60]
	cbz	w2, .L65
	ldr	w11, [x1, 8]
	ldr	w10, [x12, 6584]
	sdiv	w6, w11, w5
	sdiv	w2, w10, w5
	msub	w6, w6, w5, w11
	msub	w2, w2, w5, w10
	cmp	w6, w2
	bne	.L65
.L101:
	ldrb	w1, [x1, 1]
	add	w0, w0, 1
	cmp	w1, wzr
	csinc	w14, w14, wzr, eq
	cmp	w0, w3
	bne	.L66
	.p2align 2
.L102:
	cbz	w14, .L69
.L67:
	add	w15, w15, 1
	cmp	w18, w15
	bne	.L63
	cbz	w7, .L71
.L70:
	mov	w12, 0
	add	x10, x13, 2388
	.p2align 2
.L75:
	mov	w11, 0
	mov	w0, 0
	sxtw	x5, w12
	cbnz	w3, .L93
	b	.L77
	.p2align 3
.L72:
	cmp	w0, w3
	beq	.L104
.L93:
	add	x2, x19, x0, sxtw 3
	add	x1, x5, 8
	add	w0, w0, 1
	ldr	x2, [x2, 3680]
	ldr	w4, [x2, 60]
	cbnz	w4, .L72
	ldr	w4, [x10, x1, lsl 2]
	ldr	w6, [x19, 5564]
	ldr	w1, [x2, 8]
	add	w4, w6, w4
	cmp	w1, w4
	bne	.L72
	ldrb	w1, [x2, 1]
	cmp	w1, wzr
	csinc	w11, w11, wzr, eq
	cmp	w0, w3
	bne	.L93
	.p2align 2
.L104:
	cbz	w11, .L77
.L74:
	add	w12, w12, 1
	cmp	w7, w12
	bhi	.L75
.L71:
	mov	w0, 1
	cbz	w8, .L92
	mov	w0, 0
	str	w9, [x20]
.L92:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L77:
	ldr	w1, [x19, 5584]
	sxtw	x2, w12
	add	x0, x2, 8
	ldr	w4, [x19, 5564]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x10, x0, lsl 2]
	ldr	w1, [x1, 244]
	add	w0, w4, w0
	cmp	w0, w1
	blt	.L74
	add	x2, x10, x2
	ldrb	w1, [x2, 12]
	cmp	w1, wzr
	csel	w9, w9, w0, eq
	csinc	w8, w8, wzr, eq
	b	.L74
	.p2align 3
.L69:
	ldr	w1, [x19, 5584]
	add	x2, x16, 8
	ldr	w4, [x19, 5564]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x17, x2, lsl 2]
	add	w0, w4, w0
	ldr	w1, [x1, 244]
	cmp	w0, w1
	blt	.L67
	add	x16, x17, x16
	ldrb	w1, [x16, 12]
	cmp	w1, wzr
	csel	w9, w9, w0, eq
	csinc	w8, w8, wzr, eq
	b	.L67
.L62:
	cbz	w7, .L92
	mov	w9, 0
	mov	w8, 0
	ldr	w3, [x19, 3372]
	b	.L70
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.15, .-HEVC_CheckThatAllRefPicsAreAvailable.part.15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_SetFrmRepeatCount.part.16, %function
HEVC_SetFrmRepeatCount.part.16:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x19, 308]
	ldr	w2, [x19, 3368]
	ldr	w0, [x19, 304]
	add	w2, w3, w2
	add	w3, w2, 1
	cmp	w0, w3
	bcc	.L106
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L107
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x19, 308]
	add	w0, w0, 2
	str	w0, [x19, 308]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L106:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L107:
	mov	w0, 1
	str	w0, [x20, 16]
	ldr	w0, [x19, 308]
	add	w0, w0, 1
	str	w0, [x19, 308]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount.part.16, .-HEVC_SetFrmRepeatCount.part.16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_OutputFrame, %function
HEVC_OutputFrame:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 276]
	ldr	w1, [x21, 28]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L158
	ldrb	w2, [x19, 1]
	cmp	w2, 1
	beq	.L159
.L112:
	ldr	w0, [x19, 276]
	mov	w2, 1
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	add	x3, x19, 4096
	ldr	w0, [x19, 276]
	mov	x4, x20
	add	x3, x3, 2832
	mov	x2, x19
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L130
.L119:
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L160
	str	wzr, [x20, 16]
.L129:
	ldr	w1, [x19, 308]
	mov	w0, 0
	ldr	w2, [x19, 316]
	add	w1, w1, 1
	str	w1, [x19, 308]
	add	w2, w2, 1
	str	w2, [x19, 316]
.L154:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L160:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.16
	b	.L129
	.p2align 3
.L159:
	ldr	w0, [x19, 276]
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	cmp	w0, 6
	beq	.L161
	tst	w0, -5
	bne	.L127
	ldr	w0, [x21, 32]
	cbz	w0, .L112
	b	.L128
	.p2align 3
.L127:
	cmp	w0, 5
	bne	.L112
	ldr	w0, [x21, 32]
	cmp	w0, 1
	beq	.L112
.L128:
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	b	.L119
	.p2align 3
.L161:
	add	x22, x19, 2408
	cbz	x21, .L114
	ldr	w0, [x21, 32]
	add	x23, x19, 2672
	ldrh	w2, [x19, 2408]
	cmp	w0, wzr
	csel	x23, x22, x23, eq
	ldrh	w0, [x23, 2]
	add	w1, w0, 1
	and	w3, w1, 15
	cmp	w3, w2
	beq	.L162
.L117:
	sbfiz	x0, x0, 4, 32
	ldr	w2, [x21, 8]
	add	x0, x23, x0
	and	w1, w1, 15
	str	w2, [x0, 8]
	ldr	w2, [x21, 28]
	str	w2, [x0, 12]
	str	x20, [x0, 16]
	strh	w1, [x23, 2]
.L114:
	ldr	x23, .LC8
	ldrh	w21, [x19, 2408]
	add	x23, x23, 24
	ldr	x26, .LC20
	ldr	x25, .LC18
	mov	x24, x23
.L118:
	ldrh	w0, [x22, 2]
	cmp	w0, w21
	beq	.L119
.L165:
	ldrh	w5, [x19, 2672]
	ldrh	w0, [x19, 2674]
	cmp	w0, w5
	beq	.L119
	ubfiz	x21, x21, 4, 16
	add	x21, x19, x21
	ldr	x4, [x21, 2424]
	cbz	x4, .L119
	ubfiz	x5, x5, 4, 16
	add	x27, x19, x5
	ldr	x0, [x27, 2688]
	cbz	x0, .L119
	ldr	w3, [x21, 2416]
	ldr	w0, [x27, 2680]
	cmp	w3, w0
	bgt	.L163
	blt	.L164
	ldr	w0, [x4, 180]
	cbz	w0, .L123
	str	wzr, [x4, 180]
	mov	w1, 1
	ldr	x0, [x27, 2688]
	str	w1, [x0, 180]
	ldr	x4, [x21, 2424]
.L123:
	add	x28, x19, 4096
	ldr	w0, [x19, 276]
	add	x28, x28, 2832
	mov	x2, x19
	mov	x3, x28
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L124
	ldr	w3, [x21, 2416]
	mov	x2, x24
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 2420]
	bl	FSP_SetDisplay
.L124:
	ldrh	w0, [x22]
	mov	x3, x28
	mov	x2, x19
	mov	w1, 16
	add	w0, w0, 1
	and	w0, w0, 15
	strh	w0, [x22]
	ldr	w0, [x19, 276]
	ldr	x4, [x27, 2688]
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L125
	ldr	w3, [x27, 2680]
	mov	x2, x23
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L156:
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x27, 2684]
	bl	FSP_SetDisplay
.L125:
	ldrh	w0, [x19, 2672]
	add	w0, w0, 1
	and	w0, w0, 15
	strh	w0, [x19, 2672]
	ldrh	w21, [x22]
	ldrh	w0, [x22, 2]
	cmp	w0, w21
	bne	.L165
	b	.L119
	.p2align 3
.L163:
	ldr	x2, .LC8
	mov	w4, w0
	ldr	x1, .LC14
	mov	w0, 1
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L156
	.p2align 3
.L164:
	ldr	x1, .LC16
	mov	w4, w3
	ldr	x2, .LC23
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x21, 2420]
	mov	w2, 0
	ldr	w0, [x19, 276]
	bl	FSP_SetDisplay
	ldrh	w21, [x22]
	add	w21, w21, 1
	and	w21, w21, 15
	strh	w21, [x22]
	b	.L118
	.p2align 3
.L130:
	ldr	x2, .LC8
	mov	w0, 1
	ldr	x1, .LC22
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L154
.L158:
	ldr	x2, .LC8
	mov	w0, 0
	ldr	x1, .LC10
	bl	dprint_vfmw
	mov	w0, -1
	b	.L154
.L162:
	ldrh	w1, [x23]
	mov	w2, 0
	ldr	w0, [x19, 276]
	add	x1, x23, x1, lsl 4
	ldr	w24, [x1, 12]
	mov	w1, w24
	bl	FSP_SetDisplay
	ldrh	w2, [x23]
	mov	w3, w24
	ldr	x1, .LC12
	mov	w0, 1
	add	w2, w2, 1
	and	w2, w2, 15
	strh	w2, [x23]
	ldr	w2, [x21, 32]
	bl	dprint_vfmw
	ldrh	w0, [x23, 2]
	add	w1, w0, 1
	b	.L117
	.size	HEVC_OutputFrame, .-HEVC_OutputFrame
	.align	3
.LC8:
	.xword	.LANCHOR0
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR0+24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_Sei_Mastering_Display_Colour_Volume.part.25, %function
HEVC_Sei_Mastering_Display_Colour_Volume.part.25:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x1, 4
	add	x22, x1, 16
	bl	_mcount
.L167:
	add	x19, x19, 4
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	str	w0, [x19, -4]
	mov	w1, 16
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x19, 8]
	cmp	x19, x22
	bne	.L167
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 28]
	mov	w1, 16
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x21, 32]
	mov	w1, 32
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x21, 36]
	mov	w1, 32
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x21, 40]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_Sei_Mastering_Display_Colour_Volume.part.25, .-HEVC_Sei_Mastering_Display_Colour_Volume.part.25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckVpsExtOverlap
	.type	HEVC_CheckVpsExtOverlap, %function
HEVC_CheckVpsExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L173
.L170:
	add	x1, x19, 12288
	ldrb	w2, [x19]
	mov	w0, 2
	ldr	x19, [sp, 16]
	cmp	w2, wzr
	ldrb	w2, [x1, 200]
	cset	w1, ne
	ldp	x29, x30, [sp], 32
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ret
	.p2align 3
.L173:
	ldr	x2, .LC24
	mov	w0, 1
	ldr	x1, .LC26
	add	x2, x2, 56
	bl	dprint_vfmw
	b	.L170
	.size	HEVC_CheckVpsExtOverlap, .-HEVC_CheckVpsExtOverlap
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC26:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckPpsExtOverlap
	.type	HEVC_CheckPpsExtOverlap, %function
HEVC_CheckPpsExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L178
.L175:
	ldrb	w1, [x19]
	mov	w0, 2
	ldrb	w2, [x19, 3144]
	cmp	w1, wzr
	ldr	x19, [sp, 16]
	cset	w1, ne
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L178:
	ldr	x2, .LC27
	mov	w0, 1
	ldr	x1, .LC29
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L175
	.size	HEVC_CheckPpsExtOverlap, .-HEVC_CheckPpsExtOverlap
	.align	3
.LC27:
	.xword	.LANCHOR0
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckSliceExtOverlap
	.type	HEVC_CheckSliceExtOverlap, %function
HEVC_CheckSliceExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L183
.L180:
	ldrb	w1, [x19]
	mov	w0, 2
	ldrb	w2, [x19, 16]
	cmp	w1, wzr
	ldr	x19, [sp, 16]
	cset	w1, ne
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L183:
	ldr	x2, .LC30
	mov	w0, 1
	ldr	x1, .LC32
	add	x2, x2, 104
	bl	dprint_vfmw
	b	.L180
	.size	HEVC_CheckSliceExtOverlap, .-HEVC_CheckSliceExtOverlap
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_ParsePts_Init
	.type	HEVC_Sei_ParsePts_Init, %function
HEVC_Sei_ParsePts_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC33
	add	x0, x19, 12288
	mov	x2, 56
	mov	w1, 0
	add	x0, x0, 448
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 4228]
	str	xzr, [x19, 4248]
	str	xzr, [x19, 4256]
	str	xzr, [x19, 4264]
	str	xzr, [x19, 4272]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_ParsePts_Init, .-HEVC_Sei_ParsePts_Init
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Dpb_Output_Time
	.type	HEVC_Sei_Get_Dpb_Output_Time, %function
HEVC_Sei_Get_Dpb_Output_Time:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldr	w2, [x19, 5588]
	mov	w5, 5036
	ldr	x1, [x19, 2960]
	add	x3, x19, 12288
	add	x4, x3, 448
	ldr	x0, [x19, 2952]
	ldr	w6, [x20, 36]
	smaddl	x1, w2, w5, x1
	ldr	w2, [x4, 4]
	mov	w5, 12668
	ldr	w1, [x1, 32]
	cmp	w2, 1
	str	w6, [x4, 12]
	smaddl	x0, w1, w5, x0
	ldr	w2, [x20, 40]
	str	w2, [x4, 16]
	ldr	w1, [x0, 52]
	add	x0, x0, x1, lsl 2
	ldrb	w2, [x0, 360]
	beq	.L193
	ldrb	w0, [x4, 1]
	add	x4, x19, 4096
	cbnz	w0, .L194
	ldr	w0, [x19, 4240]
	ldr	x1, [x19, 4248]
	add	x0, x0, x1
	str	x0, [x19, 4272]
.L187:
	add	x4, x4, 136
	add	x3, x3, 448
	str	x0, [x4, 32]
	ldr	x1, [x3, 32]
	strb	wzr, [x3, 1]
	str	x1, [x3, 48]
	ldrb	w1, [x20, 2]
	cbnz	w1, .L195
.L191:
	ldr	w1, [x4, 12]
	add	x0, x1, x0
	sub	x0, x0, x2, uxtb
	str	x0, [x3, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L194:
	ldrb	w0, [x4, 128]
	cbnz	w0, .L196
	ldp	x1, x6, [x4, 152]
.L190:
	ldr	w7, [x4, 144]
	add	x0, x7, x1
	str	x0, [x4, 152]
	cmp	x0, x6
	str	x0, [x4, 176]
	bge	.L187
	add	x0, x7, x6
	add	x4, x4, 136
	str	x0, [x4, 16]
	add	x3, x3, 448
	str	x0, [x4, 40]
	str	x0, [x4, 32]
	strb	wzr, [x3, 1]
	ldr	x1, [x3, 32]
	str	x1, [x3, 48]
	ldrb	w1, [x20, 2]
	cbz	w1, .L191
.L195:
	ldr	w1, [x4, 12]
	add	x1, x1, x0
	asr	x1, x1, 1
	sub	x0, x1, x2, uxtb
	str	x0, [x3, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L193:
	add	x4, x19, 4096
	ldrsw	x0, [x19, 4228]
	str	x0, [x4, 152]
	str	x0, [x4, 176]
	b	.L187
	.p2align 3
.L196:
	ldr	x6, [x4, 160]
	mov	x1, x6
	b	.L190
	.size	HEVC_Sei_Get_Dpb_Output_Time, .-HEVC_Sei_Get_Dpb_Output_Time
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Get_Last_IDR_Frame_Info
	.type	HEVC_Get_Last_IDR_Frame_Info, %function
HEVC_Get_Last_IDR_Frame_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sub	w0, w20, #19
	cmp	w0, 1
	bls	.L204
.L198:
	sub	w20, w20, #6
	cmp	w20, 3
	bls	.L197
	ldr	x0, [x19, 4272]
	str	x0, [x19, 4256]
.L197:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L204:
	ldr	x0, [x19, 3032]
	ldr	x0, [x0, 56]
	cmn	x0, #1
	beq	.L199
	ldr	x1, [x19, 12768]
	str	x0, [x19, 12760]
	str	x1, [x19, 12776]
.L199:
	add	x0, x19, 12288
	mov	w1, 1
	strb	w1, [x0, 448]
	b	.L198
	.size	HEVC_Get_Last_IDR_Frame_Info, .-HEVC_Get_Last_IDR_Frame_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Frame_Pts
	.type	HEVC_Sei_Get_Frame_Pts, %function
HEVC_Sei_Get_Frame_Pts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 12748]
	ldr	w5, [x19, 12752]
	ldr	x6, [x19, 12760]
	ldr	x3, [x19, 12768]
	ldr	x7, [x19, 12776]
	cbz	w4, .L208
	mov	w1, w4
	mov	w2, w5
	b	.L207
	.p2align 3
.L209:
	mov	w1, w0
.L207:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L209
.L206:
	udiv	w4, w4, w1
	sub	x0, x3, x7
	lsl	w2, w0, 6
	sub	w2, w2, w0
	lsl	w2, w2, 1
	sub	w0, w2, w0
	lsl	w0, w0, 3
	udiv	w1, w5, w1
	mul	w0, w0, w4
	udiv	w1, w0, w1
	add	x1, x1, x6
	str	x1, [x19, 5504]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L208:
	mov	w1, w5
	b	.L206
	.size	HEVC_Sei_Get_Frame_Pts, .-HEVC_Sei_Get_Frame_Pts
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w5
	mov	x20, x4
	bl	_mcount
	cmp	w21, 15
	bgt	.L211
	cmp	w21, 8
	mul	w10, w21, w21
	beq	.L246
	mov	x8, x20
	cbz	w10, .L211
.L217:
	mov	w7, 1
	mov	w1, 0
	mov	w9, 0
	sub	w7, w7, w21
.L221:
	cmp	w21, w9
	mov	w0, w9
	mov	w2, 0
	bgt	.L223
	.p2align 2
.L237:
	sub	w0, w0, #1
	add	w2, w2, 1
	cmp	w21, w0
	ble	.L237
.L223:
	cmp	w0, wzr
	ccmp	w21, w2, 4, ge
	ble	.L219
	madd	w3, w21, w0, w2
	sub	w2, w2, w1
	.p2align 2
.L220:
	str	w3, [x8, w1, uxtw 2]
	sub	w0, w0, #1
	add	w1, w1, 1
	cmp	w0, wzr
	add	w6, w2, w1
	add	w3, w3, w7
	ccmp	w21, w6, 4, ge
	bgt	.L220
.L219:
	cmp	w10, w1
	add	w9, w9, 1
	bhi	.L221
.L211:
	cmp	w21, 4
	ble	.L210
	asr	w14, w21, 2
	add	x0, x19, x14, uxtw
	mul	w16, w14, w14
	ldrsb	w0, [x0, 15]
	add	w0, w0, 1
	cbz	w16, .L210
.L215:
	ldr	x15, .LC35
	sbfiz	x0, x0, 16, 32
	mov	w9, 1
	add	x13, x19, 364
	add	x15, x15, x0
	mov	x12, 0
	sub	w9, w9, w21
.L232:
	cmp	w21, 32
	ldr	w3, [x15, x12, lsl 2]
	beq	.L247
.L225:
	udiv	w2, w3, w14
	lsl	w8, w12, 4
	mov	w10, 0
	mov	w0, 0
	mov	w7, 0
	mov	w1, 0
	madd	w3, w2, w21, w3
	msub	w2, w2, w14, w3
	lsl	w11, w2, 2
	.p2align 2
.L226:
	cmp	w1, wzr
	ccmp	w7, 3, 0, ge
	bgt	.L227
	madd	w2, w21, w1, w7
	sub	w7, w7, w0
	add	w2, w2, w11
	.p2align 2
.L228:
	add	w6, w0, w8
	sub	w1, w1, #1
	add	w0, w0, 1
	cmp	w1, wzr
	add	w3, w7, w0
	str	w2, [x20, w6, uxtw 2]
	ccmp	w3, 3, 0, ge
	add	w2, w2, w9
	ble	.L228
.L227:
	cmp	w0, 15
	add	w10, w10, 1
	bhi	.L229
	cmp	w10, 3
	ble	.L248
	sub	w7, w10, #3
	mov	w1, 3
	b	.L226
.L229:
	add	x12, x12, 1
	add	x13, x13, 4
	cmp	w16, w12
	bhi	.L232
.L210:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L247:
	ldr	w3, [x13]
	b	.L225
.L246:
	add	x8, x19, 364
	cbnz	w10, .L217
	ldrsb	w0, [x19, 17]
	mov	w14, 2
	mov	w16, 4
	add	w0, w0, 1
	b	.L215
.L248:
	mov	w1, w10
	mov	w7, 0
	b	.L226
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	3
.LC35:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x22, 15
	add	x2, x22, 144
	mov	w1, -1
	.p2align 2
.L250:
	strb	w1, [x0], 1
	cmp	x2, x0
	bne	.L250
	ldr	x21, .LC38
	mov	w3, 1
	mov	w2, 2
	mov	w1, 3
	mov	w0, 4
	strb	wzr, [x22, 19]
	strb	w3, [x22, 23]
	mov	w20, 2
	strb	w2, [x22, 31]
	mov	w19, 0
	strb	w1, [x22, 47]
	strb	w0, [x22, 79]
	.p2align 2
.L251:
	mov	w7, w19
	mov	w6, w20
	mov	w5, w20
	mov	x4, x21
	mov	x3, 0
	mov	x2, 0
	mov	x1, 0
	mov	x0, x22
	add	w19, w19, 1
	lsl	w20, w20, 1
	bl	HEVC_InitSigLastScan
	add	x21, x21, 65536
	cmp	w19, 7
	bne	.L251
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.align	3
.LC38:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetDar
	.type	HEVC_GetDar, %function
HEVC_GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w23, w2
	mov	w22, w3
	mov	w24, w4
	mov	w20, 0
	bl	_mcount
	cbz	w19, .L255
	mov	w0, 255
	cmp	w19, 16
	ccmp	w19, w0, 4, gt
	bne	.L255
	cmp	w21, wzr
	ccmp	w23, wzr, 4, ne
	ccmp	w19, w0, 0, eq
	beq	.L255
	cmp	w19, 1
	mov	w20, 5
	beq	.L255
	cmp	w19, w0
	beq	.L256
	ldr	x0, .LC39
	sbfiz	x19, x19, 3, 32
	add	x0, x0, 136
	add	x1, x0, x19
	ldr	w21, [x0, x19]
	ldr	w23, [x1, 4]
.L256:
	lsl	w4, w21, 10
	lsl	w22, w22, 10
	sdiv	w2, w4, w23
	sdiv	w4, w22, w24
	mul	w4, w2, w4
	cmp	w4, wzr
	add	w0, w4, 1023
	csel	w4, w0, w4, lt
	asr	w4, w4, 10
	subs	w1, w4, #2406
	bmi	.L278
.L257:
	subs	w0, w4, #2263
	bmi	.L279
	cmp	w1, w0
	mov	w20, 4
	bge	.L261
.L255:
	ldr	x1, .LC41
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L279:
	mov	w0, 2263
	mov	w20, 4
	sub	w0, w0, w4
	cmp	w1, w0
	blt	.L255
.L261:
	subs	w1, w4, #1820
	bmi	.L280
	cmp	w0, w1
	mov	w20, 3
	blt	.L255
.L262:
	subs	w0, w4, #1365
	bmi	.L281
.L260:
	mov	w20, 2
	cmp	w1, w0
	csinc	w20, w20, wzr, lt
	b	.L255
	.p2align 3
.L278:
	mov	w1, 2406
	sub	w1, w1, w4
	b	.L257
	.p2align 3
.L280:
	mov	w1, 1820
	mov	w20, 3
	sub	w1, w1, w4
	cmp	w0, w1
	blt	.L255
	b	.L262
.L281:
	mov	w0, 1365
	sub	w0, w0, w4
	b	.L260
	.size	HEVC_GetDar, .-HEVC_GetDar
	.align	3
.LC39:
	.xword	.LANCHOR0
	.align	3
.LC41:
	.xword	.LC40
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC44
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, .LC46
	ldr	w0, [x24, 168]
	cmn	w0, #1
	beq	.L286
	mov	w20, 52429
	ldr	x22, .LC50
	mov	w19, 0
	mov	w21, 104
	movk	w20, 0xcccc, lsl 16
	b	.L285
	.p2align 3
.L284:
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bls	.L286
.L285:
	umull	x0, w19, w21
	ldr	x4, [x24, 3024]
	mov	w2, w19
	mov	x1, x22
	add	x4, x4, x0
	mov	w0, 1
	mov	x3, x4
	ldr	w4, [x4, 32]
	bl	dprint_vfmw
	umull	x0, w19, w20
	lsr	x0, x0, 32
	lsr	w0, w0, 3
	lsl	w1, w0, 3
	add	w0, w1, w0, lsl 1
	cmp	w19, w0
	add	w19, w19, 1
	bne	.L284
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bhi	.L285
.L286:
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC48
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC52
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC54
	mov	w0, 1
	ldr	w2, [x19, 5620]
	bl	dprint_vfmw
	ldr	w0, [x19, 5620]
	cbz	w0, .L297
	ldr	x24, .LC58
	mov	w20, 0
	ldr	x22, .LC63
	ldr	x23, .LC60
	ldr	x25, .LC62
	.p2align 2
.L296:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 3056]
	bl	dprint_vfmw
	ldr	x2, [x21, 3056]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L294
	ldr	x2, [x2, 24]
	bl	dprint_vfmw
	ldr	x0, [x21, 3056]
	ldr	x0, [x0, 24]
	cbz	x0, .L294
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L294:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 5620]
	cmp	w0, w20
	bhi	.L296
.L297:
	ldr	x1, .LC56
	mov	w0, 1
	ldr	w2, [x19, 5624]
	bl	dprint_vfmw
	ldr	w0, [x19, 5624]
	cbz	w0, .L292
	ldr	x22, .LC63
	mov	w20, 0
	ldr	x24, .LC67
	ldr	x23, .LC60
	ldr	x25, .LC62
	.p2align 2
.L301:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 3192]
	bl	dprint_vfmw
	ldr	x2, [x21, 3192]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L299
	ldr	x2, [x2, 24]
	bl	dprint_vfmw
	ldr	x0, [x21, 3192]
	ldr	x0, [x0, 24]
	cbz	x0, .L299
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L299:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 5624]
	cmp	w0, w20
	bhi	.L301
.L292:
	ldr	x1, .LC65
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
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
.LC63:
	.xword	.LC45
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC71
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x22, 180]
	cbz	w0, .L315
	ldr	x27, .LC75
	mov	w21, 0
	ldr	x23, .LC77
	mov	w25, 720
	ldr	x26, .LC78
	mov	x24, 15368
	.p2align 2
.L314:
	uxtw	x3, w21
	mov	w2, w21
	lsl	x0, x3, 2
	mov	x1, x27
	sub	x4, x0, x3
	mov	w0, 1
	lsl	x3, x4, 4
	mov	w19, 0
	sub	x3, x3, x4
	lsl	x3, x3, 4
	add	x4, x22, x3
	add	x3, x3, 12288
	add	x5, x4, 12288
	add	x3, x3, 2448
	umaddl	x20, w21, w25, x24
	ldr	w4, [x4, 14784]
	add	x3, x22, x3
	ldrb	w6, [x5, 2450]
	add	x20, x22, x20
	ldrb	w5, [x5, 2449]
	bl	dprint_vfmw
.L313:
	ldr	x3, [x20], 8
	mov	w2, w19
	mov	w0, 1
	mov	x1, x23
	add	w19, w19, w0
	bl	dprint_vfmw
	cmp	w19, 4
	bne	.L313
	mov	w0, 1
	mov	x1, x26
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x22, 180]
	cmp	w0, w21
	bhi	.L314
.L315:
	ldr	x1, .LC73
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC78:
	.xword	.LC45
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	mov	w23, 0
	bl	_mcount
	add	x22, x19, 1892
	ldr	x1, .LC80
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x24, .LC82
	ldr	x21, .LC84
.L321:
	ldp	w4, w3, [x22, -8]
	mov	w2, w23
	mov	x1, x24
	mov	w0, 1
	mov	x20, x22
	mov	w19, 0
	bl	dprint_vfmw
	.p2align 2
.L320:
	ldr	w4, [x20, 64]
	mov	w2, w19
	ldr	w5, [x20, 128]
	mov	w0, 1
	ldr	w3, [x20], 4
	mov	x1, x21
	add	w19, w19, w0
	bl	dprint_vfmw
	cmp	w19, 16
	bne	.L320
	add	w23, w23, 1
	add	x22, x22, 280
	cmp	w23, 2
	bne	.L321
	ldr	x1, .LC86
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
	sub	sp, sp, #176
	stp	x29, x30, [sp, 64]
	add	x29, sp, 64
	stp	x19, x20, [sp, 80]
	stp	x21, x22, [sp, 96]
	stp	x23, x24, [sp, 112]
	stp	x25, x26, [sp, 128]
	stp	x27, x28, [sp, 144]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x1, .LC88
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC90
	mov	w0, 1
	ldr	w2, [x19, 3368]
	ldr	w3, [x19, 3372]
	ldr	w6, [x19, 3380]
	ldr	w4, [x19, 3384]
	ldr	w5, [x19, 3388]
	bl	dprint_vfmw
	ldr	w0, [x19, 3372]
	cbz	w0, .L329
	.p2align 2
.L328:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 276]
	ldr	x2, [x21, 3680]
	ldrb	w7, [x2, 1]
	ldp	w1, w28, [x2, 28]
	ldr	w6, [x2, 48]
	ldrb	w25, [x2]
	ldrb	w22, [x2, 2]
	ldr	w23, [x2, 8]
	ldr	w24, [x2, 60]
	stp	w6, w7, [x29, 104]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	x1, [x21, 3680]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetRef
	mov	w27, w0
	ldr	x1, [x21, 3680]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDisplay
	ldr	x8, [x21, 3680]
	mov	w2, w20
	ldp	w6, w7, [x29, 104]
	mov	x3, x8
	mov	w5, w25
	ldr	w1, [x8, 236]
	mov	w4, w28
	str	w1, [sp, 56]
	add	w20, w20, 1
	ldr	x1, .LC93
	ldr	w8, [x8, 28]
	str	w8, [sp, 48]
	str	w0, [sp, 40]
	mov	w0, 1
	str	w22, [sp]
	str	w23, [sp, 8]
	str	w24, [sp, 16]
	str	x26, [sp, 24]
	str	w27, [sp, 32]
	bl	dprint_vfmw
	ldr	w0, [x19, 3372]
	cmp	w0, w20
	bhi	.L328
.L329:
	ldr	x24, .LC91
	mov	w0, 1
	mov	x1, x24
	bl	dprint_vfmw
	ldr	w0, [x19, 3372]
	cbz	w0, .L327
	ldr	x26, .LC97
	mov	w21, 0
	ldr	x28, .LC99
	ldr	x27, .LC101
	ldr	x25, .LC109
	b	.L336
	.p2align 3
.L340:
	mov	x2, x20
	mov	x1, x28
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x20, 20]
	mov	x1, x27
	mov	w0, 1
	bl	dprint_vfmw
	ldrsb	w2, [x20]
	mov	w0, 1
	ldr	x1, .LC103
	bl	dprint_vfmw
	ldrsb	w2, [x20, 1]
	mov	w0, 1
	ldr	x1, .LC105
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbz	x23, .L332
.L341:
	bl	dprint_vfmw
	ldr	w2, [x23, 72]
	mov	w0, 1
	ldr	x1, .LC111
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbz	x22, .L334
.L342:
	ldr	x1, .LC115
	bl	dprint_vfmw
	ldr	x1, .LC117
	mov	w0, 1
	ldr	w2, [x22, 72]
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 3372]
	cmp	w0, w21
	bls	.L327
.L336:
	add	x22, x19, x21, uxtw 3
	ldr	w0, [x19, 276]
	ldr	x1, [x22, 3680]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	x1, [x22, 3680]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDecPhyFs
	mov	x23, x0
	ldr	x1, [x22, 3680]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	mov	x22, x0
	mov	w2, w21
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
	cbnz	x20, .L340
	ldr	x1, .LC107
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbnz	x23, .L341
	.p2align 2
.L332:
	ldr	x1, .LC113
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbnz	x22, .L342
	.p2align 2
.L334:
	ldr	x1, .LC119
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 3372]
	cmp	w0, w21
	bhi	.L336
.L327:
	ldr	x1, .LC95
	mov	w0, 1
	bl	dprint_vfmw
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC91:
	.xword	.LC45
	.align	3
.LC93:
	.xword	.LC92
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
.LC105:
	.xword	.LC104
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 9
	mov	w0, 1
	bls	.L344
	sub	w19, w19, #16
	cmp	w19, 5
	cset	w0, ls
.L344:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 5
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ands	w19, w19, -7
	mov	w0, 1
	beq	.L348
	cmp	w19, 8
	cset	w0, eq
.L348:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 4
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4864]
	cbnz	w0, .L353
	ldr	x1, [x19, 3032]
	mov	x2, 4294967296
	ldr	x3, [x1, 688]
	cmp	x3, x2
	beq	.L356
.L352:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L353:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L356:
	ldr	w2, [x1, 696]
	cbnz	w2, .L352
	ldr	w0, [x1, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	cset	w0, hi
	b	.L352
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsEosNal
	.type	HEVC_IsEosNal, %function
HEVC_IsEosNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsEosNal, .-HEVC_IsEosNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	mov	x21, x3
	bl	_mcount
	ldr	x0, [x22, 3008]
	ldr	x1, [x22, 3000]
	ldp	w23, w26, [x0, 68]
	ldr	w25, [x1, 128]
	sub	w0, w23, #1
	cmp	w0, 9
	bhi	.L386
	sub	w0, w26, #1
	cmp	w0, 10
	bhi	.L387
	ldr	x24, .LC125
	mov	x2, 512
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x24, 96]
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x20
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x21
	blr	x3
	cmp	w23, wzr
	ble	.L367
	sub	w7, w25, #4
	mov	x2, x20
	mov	w1, 0
	mov	w6, 0
.L366:
	str	w1, [x2]
	lsl	w3, w1, w7
	ldr	x0, [x22, 3008]
	add	x0, x0, x6, sxtw 1
	ldrsh	w5, [x0, 172]
	add	w5, w5, w1
	lsl	w1, w5, w7
	sub	w0, w5, #1
	cmp	w3, w1
	str	w0, [x2, 4]
	bge	.L372
	cmp	w3, 255
	bhi	.L368
	uxtb	w4, w6
	b	.L370
	.p2align 3
.L371:
	cmp	w3, 255
	bhi	.L368
.L370:
	strb	w4, [x19, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w1
	blt	.L371
.L372:
	add	w6, w6, 1
	add	x2, x2, 8
	cmp	w23, w6
	mov	w1, w5
	bne	.L366
.L367:
	cmp	w26, wzr
	ble	.L364
	sub	w25, w25, #4
	mov	w0, 0
	mov	w5, 0
.L374:
	str	w0, [x21]
	lsl	w3, w0, w25
	ldr	x1, [x22, 3008]
	add	x1, x1, x5, sxtw 1
	ldrsh	w4, [x1, 212]
	add	w4, w4, w0
	lsl	w0, w4, w25
	sub	w1, w4, #1
	cmp	w3, w0
	str	w1, [x21, 4]
	bge	.L379
	cmp	w3, 255
	bhi	.L375
	uxtb	w2, w5
	add	x1, x19, 256
	b	.L377
	.p2align 3
.L378:
	cmp	w3, 255
	bhi	.L375
.L377:
	strb	w2, [x1, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w0
	blt	.L378
.L379:
	add	w5, w5, 1
	add	x21, x21, 8
	cmp	w26, w5
	mov	w0, w4
	bne	.L374
.L364:
	mov	w0, 0
	b	.L360
	.p2align 3
.L368:
	ldr	x2, .LC120
	mov	w0, 1
	ldr	x1, .LC127
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
.L360:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L375:
	ldr	x2, .LC120
	mov	w0, 1
	ldr	x1, .LC129
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L360
.L387:
	ldr	x2, .LC120
	mov	w4, 11
	ldr	x1, .LC124
	mov	w3, w26
	add	x2, x2, 272
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L360
.L386:
	ldr	x2, .LC120
	mov	w4, 10
	ldr	x1, .LC122
	mov	w3, w23
	add	x2, x2, 272
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L360
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	3
.LC120:
	.xword	.LANCHOR0
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x1, [x19, 2936]
	mov	x0, x1
	ldp	w2, w19, [x1, 32]
	sub	w19, w2, w19
	bl	BsIsByteAligned
	cmp	w20, w19
	ccmp	w0, wzr, 4, ne
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x3, .LC130
	mov	x2, 40
	ldr	x1, [x19, 2936]
	add	x0, x29, x2
	ldr	x3, [x3, 104]
	blr	x3
	ldp	w0, w1, [x29, 72]
	sub	w0, w0, w1
	mov	w1, 0
	cmp	w0, w20
	bcc	.L396
.L390:
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L396:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	mov	w1, 1
	cbz	w0, .L390
	add	x0, x29, 40
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
	b	.L391
	.p2align 3
.L392:
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
.L391:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	cmp	w19, w20
	mov	w1, 1
	cset	w2, cc
	cmp	w0, wzr
	cset	w3, eq
	add	x0, x29, 40
	tst	w2, w3
	bne	.L392
	mov	w1, w2
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L405
	ldr	x0, [x20, 2936]
	mov	w1, 8
	mov	w21, 3
	bl	BsGet
	mov	w22, w0
.L404:
	cbnz	w22, .L399
	mov	w19, 16
	.p2align 2
.L400:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L400
.L401:
	subs	w21, w21, #1
	bne	.L404
.L409:
	mov	w0, 0
.L398:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L399:
	cmp	w22, 1
	beq	.L408
	cmp	w22, 2
	bne	.L401
	ldr	x0, [x20, 2936]
	mov	w1, 32
	bl	BsGet
	subs	w21, w21, #1
	bne	.L404
	b	.L409
.L408:
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	subs	w21, w21, #1
	bne	.L404
	b	.L409
.L405:
	mov	w0, -1
	b	.L398
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L412
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w0, 0
.L411:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L412:
	mov	w0, -1
	b	.L411
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Mastering_Display_Colour_Volume
	.type	HEVC_Sei_Mastering_Display_Colour_Volume, %function
HEVC_Sei_Mastering_Display_Colour_Volume:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L415
	mov	w0, 1
	mov	x1, x19
	strb	w0, [x19]
	mov	x0, x20
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.25
.L414:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L415:
	mov	w0, -1
	b	.L414
	.size	HEVC_Sei_Mastering_Display_Colour_Volume, .-HEVC_Sei_Mastering_Display_Colour_Volume
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Content_Light_Level_Information
	.type	HEVC_Sei_Content_Light_Level_Information, %function
HEVC_Sei_Content_Light_Level_Information:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L418
	mov	w0, 1
	strb	w0, [x19]
	mov	w1, 16
	ldr	x0, [x20, 2936]
	bl	BsGet
	strh	w0, [x19, 2]
	mov	w1, 16
	ldr	x0, [x20, 2936]
	bl	BsGet
	strh	w0, [x19, 4]
	mov	w1, 0
.L417:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L418:
	mov	w1, -1
	b	.L417
	.size	HEVC_Sei_Content_Light_Level_Information, .-HEVC_Sei_Content_Light_Level_Information
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_HLGHDR_Comapitibility_Info
	.type	HEVC_Sei_HLGHDR_Comapitibility_Info, %function
HEVC_Sei_HLGHDR_Comapitibility_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L421
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x19]
	mov	w1, 0
.L420:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L421:
	mov	w1, -1
	b	.L420
	.size	HEVC_Sei_HLGHDR_Comapitibility_Info, .-HEVC_Sei_HLGHDR_Comapitibility_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L424
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L423:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L424:
	mov	w0, -1
	b	.L423
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L428
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L429
.L427:
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L426:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L429:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L427
	.p2align 3
.L428:
	mov	w0, -1
	b	.L426
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_TSI
	.type	HEVC_Sei_TSI, %function
HEVC_Sei_TSI:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L432
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 4
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
.L431:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L432:
	mov	w0, -1
	b	.L431
	.size	HEVC_Sei_TSI, .-HEVC_Sei_TSI
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	w19, 16
	bl	_mcount
	cmp	w21, 15
	bls	.L444
	.p2align 2
.L441:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L441
	subs	w21, w21, #16
	mov	w19, 0
	beq	.L438
	.p2align 2
.L440:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L440
.L438:
	mov	w0, 0
.L435:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L444:
	ldr	x1, .LC132
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L435
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 5620]
	cbnz	w3, .L486
.L446:
	mov	w0, 0
.L484:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L486:
	ldr	x0, [x19, 3056]
	cbz	x0, .L468
	ldr	x0, [x0, 24]
	mov	w20, 0
	cbnz	x0, .L452
	b	.L448
	.p2align 3
.L488:
	ldr	x1, [x0, 32]
	cbz	x1, .L453
	ldr	w3, [x19, 5620]
	add	w20, w20, 1
	cmp	w3, w20
	add	x0, x19, x20, sxtw 3
	bls	.L487
	ldr	x0, [x0, 3056]
	cbz	x0, .L447
	ldr	x0, [x0, 24]
	cbz	x0, .L448
.L452:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	cbnz	x0, .L488
.L453:
	add	x19, x19, x20, sxtw 3
	ldr	x1, .LC138
	mov	x4, x0
	mov	w2, w20
	mov	w0, 1
	ldr	x3, [x19, 3056]
	ldr	x3, [x3, 24]
	bl	dprint_vfmw
	mov	w0, -1
.L492:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L487:
	cbz	w3, .L446
	ldr	w0, [x19, 5624]
	cbz	w0, .L446
	ldr	x0, [x19, 3192]
	cbz	x0, .L470
	ldr	x0, [x0, 24]
	mov	w20, 0
	cbnz	x0, .L463
	b	.L460
	.p2align 3
.L491:
	ldr	x1, [x0, 32]
	cbz	x1, .L464
	ldr	w0, [x19, 5624]
	add	w20, w20, 1
	cmp	w0, w20
	add	x1, x19, x20, sxtw 3
	bls	.L446
	ldr	x0, [x1, 3192]
	cbz	x0, .L489
	ldr	x0, [x0, 24]
	cbz	x0, .L490
.L463:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	cbnz	x0, .L491
.L464:
	ldr	x1, .LC144
	mov	x3, x0
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L484
.L468:
	mov	w20, 0
	.p2align 2
.L447:
	ldr	x1, .LC134
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L492
	.p2align 3
.L448:
	ldr	x1, .LC136
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L492
.L490:
	ldr	w3, [x19, 5620]
.L460:
	ldr	x1, .LC142
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L484
.L489:
	ldr	w3, [x19, 5620]
.L459:
	ldr	x1, .LC140
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L484
.L470:
	mov	w20, 0
	b	.L459
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, -1
	bl	_mcount
	str	w21, [x20]
	ldr	w3, [x19, 3372]
	cmp	w3, 16
	bhi	.L494
	mov	w4, 2147483647
	mov	w0, 0
	cbz	w3, .L499
	.p2align 2
.L502:
	add	x2, x19, x0, uxtw 3
	ldr	x2, [x2, 3680]
	ldr	w5, [x2, 8]
	cmp	w5, w4
	bge	.L497
	ldr	w2, [x2]
	tst	w2, 16776960
	bne	.L497
	str	w0, [x20]
	mov	w4, w5
	ldr	w3, [x19, 3372]
.L497:
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L502
	ldr	w3, [x20]
	cmn	w3, #1
	beq	.L499
	ldr	x2, .LC145
	mov	w0, 1
	ldr	x1, .LC151
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, 0
.L496:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L499:
	ldr	x2, .LC145
	mov	w0, 1
	ldr	x1, .LC147
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L496
.L494:
	ldr	x2, .LC145
	mov	w0, 1
	ldr	x1, .LC149
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, w21
	b	.L496
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	3
.LC145:
	.xword	.LANCHOR0
	.align	3
.LC147:
	.xword	.LC146
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x20, 3368]
	cmp	w3, 16
	bhi	.L509
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	mov	w19, w0
	ldr	w2, [x20, 276]
	ldr	w0, [x20, 4868]
	ldr	w1, [x20, 4872]
	bl	FSP_GetOccupiedNum
	subs	w0, w19, w0
	csel	w0, w0, wzr, pl
	ldr	x2, .LC152
	cmp	w0, wzr
	ble	.L508
	ldr	w3, [x20, 3368]
	add	w3, w3, 1
	cmp	w3, w0
	bhi	.L508
	ldr	x1, .LC156
	add	x2, x2, 328
	mov	w0, 13
	str	w3, [x20, 3368]
	bl	dprint_vfmw
	mov	w0, 0
.L507:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L508:
	ldr	x1, .LC158
	mov	w3, w0
	add	x2, x2, 328
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L507
	.p2align 3
.L509:
	ldr	x2, .LC152
	mov	w4, 17
	ldr	x1, .LC154
	mov	w0, 1
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w1, 17
	mov	w0, -1
	str	w1, [x20, 3368]
	b	.L507
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	3
.LC152:
	.xword	.LANCHOR0
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5580]
	sub	w1, w0, #16
	cmp	w1, 5
	bhi	.L511
	str	w0, [x19, 4852]
	str	wzr, [x19, 4864]
.L510:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L511:
	ldr	w0, [x19, 4852]
	sub	w0, w0, #16
	cmp	w0, 5
	bls	.L510
	ldr	w0, [x19, 5572]
	cmp	w0, 1
	beq	.L513
	cmp	w0, 2
	beq	.L514
	cbnz	w0, .L510
	mov	w0, 2
	str	w0, [x19, 4864]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L513:
	ldr	w1, [x19, 4864]
	cmp	w1, 2
	beq	.L510
	str	w0, [x19, 4864]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L514:
	ldr	w0, [x19, 4864]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L510
	str	wzr, [x19, 4864]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 5580]
	cmp	w1, 15
	bhi	.L520
	mov	w0, 1
	tbnz	x1, 0, .L521
.L520:
	sub	w1, w1, #16
	cmp	w1, 7
	cset	w0, ls
.L521:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	ubfiz	x20, x20, 6, 32
	bl	_mcount
	add	x1, x21, x20
	ldrb	w4, [x1, 624]
	ldr	w3, [x1, 632]
	ldr	w2, [x1, 628]
	ldrb	w0, [x1, 620]
	ubfiz	w2, w2, 8, 8
	orr	w2, w2, w4, lsl 16
	orr	w0, w0, w3, lsl 24
	orr	w0, w2, w0
	str	w0, [x19]
	ldrb	w4, [x1, 633]
	ldrb	w2, [x1, 625]
	ldr	w3, [x1, 628]
	ldrb	w0, [x1, 621]
	lsl	w2, w2, 16
	and	w3, w3, 65280
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 4]
	ldrb	w4, [x1, 634]
	ldrb	w2, [x1, 630]
	ldr	w3, [x1, 624]
	ldrb	w0, [x1, 622]
	lsl	w2, w2, 8
	and	w3, w3, 16711680
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 8]
	ldrb	w3, [x1, 627]
	ldrb	w2, [x1, 631]
	ldr	w0, [x1, 632]
	ldrb	w1, [x1, 623]
	lsl	w2, w2, 8
	and	w0, w0, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 18
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1788]
	ldr	w3, [x0, 1796]
	ldr	w4, [x0, 1780]
	ldrb	w2, [x1, 620]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1820]
	ldr	w3, [x0, 1828]
	ldr	w4, [x0, 1812]
	ldrb	w2, [x0, 1804]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1797]
	ldrb	w4, [x0, 1789]
	ldr	w3, [x0, 1780]
	ldrb	w2, [x1, 621]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1829]
	ldrb	w4, [x0, 1821]
	ldr	w3, [x0, 1812]
	ldrb	w2, [x0, 1805]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1798]
	ldrb	w4, [x0, 1782]
	ldr	w3, [x0, 1788]
	ldrb	w2, [x1, 622]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1830]
	ldrb	w4, [x0, 1814]
	ldr	w3, [x0, 1820]
	ldrb	w2, [x0, 1806]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1791]
	ldrb	w3, [x0, 1783]
	ldr	w5, [x0, 1796]
	ldrb	w2, [x1, 623]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1823]
	ldrb	w3, [x0, 1815]
	ldr	w1, [x0, 1828]
	ldrb	w2, [x0, 1807]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1792]
	ldr	w2, [x0, 1800]
	ldr	w3, [x0, 1784]
	ldrb	w1, [x0, 1776]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1824]
	ldr	w2, [x0, 1832]
	ldr	w3, [x0, 1816]
	ldrb	w1, [x0, 1808]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1801]
	ldrb	w3, [x0, 1793]
	ldr	w2, [x0, 1784]
	ldrb	w1, [x0, 1777]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1833]
	ldrb	w3, [x0, 1825]
	ldr	w2, [x0, 1816]
	ldrb	w1, [x0, 1809]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1802]
	ldrb	w3, [x0, 1786]
	ldr	w2, [x0, 1792]
	ldrb	w1, [x0, 1778]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1834]
	ldrb	w3, [x0, 1818]
	ldr	w2, [x0, 1824]
	ldrb	w1, [x0, 1810]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1795]
	ldrb	w3, [x0, 1787]
	ldr	w1, [x0, 1800]
	ldrb	w2, [x0, 1779]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1827]
	ldrb	w2, [x0, 1819]
	ldr	w4, [x0, 1832]
	ldrb	w1, [x0, 1811]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 6
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1036]
	ldr	w3, [x0, 1052]
	ldr	w4, [x0, 1020]
	ldrb	w2, [x1, 620]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1044]
	ldr	w3, [x0, 1060]
	ldr	w4, [x0, 1028]
	ldrb	w2, [x0, 1012]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1053]
	ldrb	w4, [x0, 1037]
	ldr	w3, [x0, 1020]
	ldrb	w2, [x1, 621]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1061]
	ldrb	w4, [x0, 1045]
	ldr	w3, [x0, 1028]
	ldrb	w2, [x0, 1013]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1054]
	ldrb	w4, [x0, 1022]
	ldr	w3, [x0, 1036]
	ldrb	w2, [x1, 622]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1062]
	ldrb	w4, [x0, 1030]
	ldr	w3, [x0, 1044]
	ldrb	w2, [x0, 1014]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1039]
	ldrb	w3, [x0, 1023]
	ldr	w5, [x0, 1052]
	ldrb	w2, [x1, 623]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1047]
	ldrb	w3, [x0, 1031]
	ldr	w1, [x0, 1060]
	ldrb	w2, [x0, 1015]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1040]
	ldr	w2, [x0, 1056]
	ldr	w3, [x0, 1024]
	ldrb	w1, [x0, 1008]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1048]
	ldr	w2, [x0, 1064]
	ldr	w3, [x0, 1032]
	ldrb	w1, [x0, 1016]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1057]
	ldrb	w3, [x0, 1041]
	ldr	w2, [x0, 1024]
	ldrb	w1, [x0, 1009]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1065]
	ldrb	w3, [x0, 1049]
	ldr	w2, [x0, 1032]
	ldrb	w1, [x0, 1017]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1058]
	ldrb	w3, [x0, 1026]
	ldr	w2, [x0, 1040]
	ldrb	w1, [x0, 1010]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1066]
	ldrb	w3, [x0, 1034]
	ldr	w2, [x0, 1048]
	ldrb	w1, [x0, 1018]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1043]
	ldrb	w3, [x0, 1027]
	ldr	w1, [x0, 1056]
	ldrb	w2, [x0, 1011]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1051]
	ldrb	w2, [x0, 1035]
	ldr	w4, [x0, 1064]
	ldrb	w1, [x0, 1019]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 12
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1404]
	ldr	w3, [x0, 1412]
	ldr	w4, [x0, 1396]
	ldrb	w2, [x1, 620]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1436]
	ldr	w3, [x0, 1444]
	ldr	w4, [x0, 1428]
	ldrb	w2, [x0, 1420]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1413]
	ldrb	w4, [x0, 1405]
	ldr	w3, [x0, 1396]
	ldrb	w2, [x1, 621]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1445]
	ldrb	w4, [x0, 1437]
	ldr	w3, [x0, 1428]
	ldrb	w2, [x0, 1421]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1414]
	ldrb	w4, [x0, 1398]
	ldr	w3, [x0, 1404]
	ldrb	w2, [x1, 622]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1446]
	ldrb	w4, [x0, 1430]
	ldr	w3, [x0, 1436]
	ldrb	w2, [x0, 1422]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1407]
	ldrb	w3, [x0, 1399]
	ldr	w5, [x0, 1412]
	ldrb	w2, [x1, 623]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1439]
	ldrb	w3, [x0, 1431]
	ldr	w1, [x0, 1444]
	ldrb	w2, [x0, 1423]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1408]
	ldr	w2, [x0, 1416]
	ldr	w3, [x0, 1400]
	ldrb	w1, [x0, 1392]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1440]
	ldr	w2, [x0, 1448]
	ldr	w3, [x0, 1432]
	ldrb	w1, [x0, 1424]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1417]
	ldrb	w3, [x0, 1409]
	ldr	w2, [x0, 1400]
	ldrb	w1, [x0, 1393]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1449]
	ldrb	w3, [x0, 1441]
	ldr	w2, [x0, 1432]
	ldrb	w1, [x0, 1425]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1418]
	ldrb	w3, [x0, 1402]
	ldr	w2, [x0, 1408]
	ldrb	w1, [x0, 1394]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1450]
	ldrb	w3, [x0, 1434]
	ldr	w2, [x0, 1440]
	ldrb	w1, [x0, 1426]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1411]
	ldrb	w3, [x0, 1403]
	ldr	w1, [x0, 1416]
	ldrb	w2, [x0, 1395]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1443]
	ldrb	w2, [x0, 1435]
	ldr	w4, [x0, 1448]
	ldrb	w1, [x0, 1427]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 3008]
	ldrb	w0, [x3, 13]
	cbz	w0, .L561
	ldp	w6, w11, [x3, 68]
	ldr	x0, [x20, 3000]
	mov	w1, 0
	subs	w8, w11, #1
	ldrb	w7, [x3, 15]
	sub	w12, w6, #1
	ldr	w4, [x0, 64]
	ldr	w5, [x0, 128]
	bmi	.L533
	.p2align 2
.L564:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w11, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L564
.L533:
	mov	w1, 0
	tbnz	w12, #31, .L531
	.p2align 2
.L563:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w6, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bne	.L563
.L531:
	mov	w1, 1
	lsl	w0, w1, w5
	sdiv	w5, w4, w0
	msub	w0, w5, w0, w4
	cmp	w0, wzr
	csinc	w5, w5, w5, eq
	sdiv	w9, w19, w5
	msub	w5, w9, w5, w19
	cbz	w7, .L576
	tbnz	w8, #31, .L573
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	.p2align 2
.L545:
	tbnz	w12, #31, .L556
	add	x0, x29, 224
	mov	w7, w4
	add	x0, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x0, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L542
	.p2align 3
.L554:
	mov	w7, w4
.L542:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L540
	cmp	w9, w10
	blt	.L548
.L540:
	cmp	w6, w2
	mov	w1, w3
	bne	.L554
.L546:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L555
	cmp	w9, w10
	blt	.L571
.L555:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	bne	.L545
.L572:
	sub	w9, w9, w10
	mov	w1, w3
	mul	w0, w9, w0
	.p2align 2
.L538:
	sub	w19, w5, w1
	add	w0, w19, w0
	add	w19, w0, w7
.L561:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L576:
	tbnz	w8, #31, .L573
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	tbnz	w12, #31, .L559
	.p2align 2
.L577:
	add	x0, x29, 224
	mov	w7, w4
	add	x3, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x3, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L549
	.p2align 3
.L557:
	mov	w7, w4
.L549:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L547
	cmp	w9, w10
	blt	.L548
.L547:
	cmp	w6, w2
	mov	w1, w3
	bne	.L557
.L553:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L558
	cmp	w9, w10
	blt	.L571
.L558:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	beq	.L572
	tbz	w12, #31, .L577
.L559:
	mov	w3, 0
	add	w10, w14, w8
	b	.L553
	.p2align 3
.L548:
	sub	w9, w9, w14
	mul	w0, w9, w0
	b	.L538
.L556:
	mov	w3, 0
	add	w10, w14, w8
	b	.L546
.L573:
	mov	w0, 0
	mov	w1, 0
	mov	w7, 0
	b	.L538
.L571:
	sub	w9, w9, w14
	mov	w1, w3
	mul	w0, w9, w0
	b	.L538
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 3008]
	ldrb	w0, [x3, 13]
	cbz	w0, .L596
	ldp	w8, w4, [x3, 68]
	ldr	x0, [x20, 3000]
	subs	w13, w4, #1
	sub	w12, w8, #1
	ldr	w5, [x0, 64]
	ldr	w6, [x0, 128]
	bmi	.L580
	mov	w1, 0
	.p2align 2
.L581:
	sxtw	x0, w1
	add	x7, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x7, x0, lsl 2
	cmp	w4, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L581
	tbnz	w12, #31, .L613
.L583:
	mov	w1, 0
	.p2align 2
.L586:
	sxtw	x0, w1
	add	x4, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x4, x0, lsl 2
	cmp	w12, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bge	.L586
	mov	w1, 1
	lsl	w0, w1, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	tbnz	w13, #31, .L584
.L585:
	ldr	w11, [x29, 140]
	mov	w10, 0
	mov	w9, 0
	mov	w4, 0
	mov	w1, 0
	mov	w7, 0
	mov	w2, 0
	add	w11, w11, 1
	.p2align 2
.L592:
	tbnz	w12, #31, .L598
	add	x1, x29, 224
	add	x1, x1, x9, sxtw 2
	ldr	w7, [x1, -172]
	add	w7, w7, 1
	madd	w5, w11, w7, w4
	cmp	w19, w5
	blt	.L599
	mov	w1, w4
	mov	w2, w11
	mov	w6, 0
	mov	w3, 0
	mov	w4, w5
	b	.L589
	.p2align 3
.L590:
	ldr	w2, [x5, -84]
	mov	w1, w4
	add	w2, w2, 1
	madd	w5, w2, w7, w4
	cmp	w5, w19
	bgt	.L591
	mov	w4, w5
.L589:
	add	w3, w3, 1
	add	x5, x29, 224
	cmp	w8, w3
	add	w6, w6, w2
	add	x5, x5, x3, sxtw 2
	bne	.L590
.L593:
	cmp	w4, w19
	bgt	.L597
	add	w9, w9, 1
	add	w10, w10, w7
	cmp	w13, w9
	bge	.L592
.L597:
	mov	w4, w1
	.p2align 2
.L591:
	cbz	w2, .L584
	sub	w4, w19, w4
	sdiv	w1, w4, w2
	add	w10, w1, w10
	msub	w4, w1, w2, w4
	add	w6, w4, w6
	madd	w0, w10, w0, w6
.L608:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L596:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L598:
	mov	w6, 0
	b	.L593
.L599:
	mov	w2, w11
	mov	w6, 0
	b	.L591
.L613:
	mov	w0, 1
	lsl	w0, w0, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	b	.L585
.L580:
	tbz	w12, #31, .L583
.L584:
	ldr	x1, .LC160
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L608
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	3
.LC160:
	.xword	.LC159
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC161
	ldr	x20, .LC162
	mov	x2, 16384
	movk	x2, 0x2, lsl 16
	mov	w1, 0
	ldr	x3, [x21, 96]
	add	x0, x20, 1792
	blr	x3
	ldr	x0, .LC163
	mov	x2, 36864
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 1280
	blr	x3
	add	x0, x19, 8192
	ldr	x3, [x21, 96]
	mov	x2, 880
	mov	w1, 0
	add	x0, x0, 2052
	blr	x3
	str	wzr, [x19, 10240]
	ldr	x1, [x19, 3008]
	ldr	x2, [x19, 3000]
	ldr	w0, [x1, 72]
	ldr	w10, [x2, 188]
	cbz	w0, .L614
	mov	w15, 0
	mov	w17, 0
	mov	w4, 0
.L623:
	ldr	w0, [x1, 68]
	uxtw	x16, w15
	cbz	w0, .L624
	add	x9, x16, 104
	ldr	w0, [x19, 10240]
	mul	w14, w17, w10
	mov	w12, 0
	mov	w13, 0
	lsl	x9, x9, 1
.L622:
	uxtw	x2, w0
	add	x3, x1, x9
	uxtw	x11, w12
	add	x5, x19, x2, lsl 3
	str	w4, [x5, 10244]
	ldrsh	w3, [x3, 4]
	cbz	w3, .L618
	add	x5, x11, 80
	add	w8, w13, w14
	mov	w7, 0
	lsl	x5, x5, 1
	.p2align 2
.L620:
	add	x2, x1, x5
	mov	w0, w4
	sub	w6, w8, w4
	ldrsh	w2, [x2, 12]
	cbz	w2, .L621
	.p2align 2
.L628:
	add	x1, x20, 1792
	add	w2, w6, w0
	str	w2, [x1, w0, sxtw 2]
	add	w0, w0, 1
	sub	w2, w0, w4
	ldr	x1, [x19, 3008]
	add	x3, x1, x5
	ldrsh	w3, [x3, 12]
	cmp	w3, w2
	bhi	.L628
	mov	w4, w0
.L621:
	add	x0, x1, x9
	add	w7, w7, 1
	add	w8, w8, w10
	ldrsh	w0, [x0, 4]
	cmp	w0, w7
	bhi	.L620
	ldr	w0, [x19, 10240]
	uxtw	x2, w0
.L618:
	add	x2, x19, x2, lsl 3
	sub	w3, w4, #1
	add	w0, w0, 1
	add	x11, x1, x11, lsl 1
	add	w12, w12, 1
	str	w3, [x2, 10248]
	str	w0, [x19, 10240]
	ldr	w3, [x1, 68]
	ldrsh	w2, [x11, 172]
	cmp	w3, w12
	add	w13, w13, w2
	bhi	.L622
.L624:
	add	x16, x1, x16, lsl 1
	ldr	w0, [x1, 72]
	add	w15, w15, 1
	cmp	w0, w15
	ldrsh	w0, [x16, 212]
	add	w17, w17, w0
	bhi	.L623
.L614:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	3
.LC161:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC162:
	.xword	.LANCHOR2
	.align	3
.LC163:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 4096
	add	x21, x19, 8192
	bl	_mcount
	ldr	w3, [x19, 4884]
	mov	w0, 2
	ldr	w2, [x19, 5068]
	ldr	x1, .LC166
	bl	dprint_vfmw
	ldr	x1, .LC168
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w22, [x19, 4856]
	ldr	w6, [x19, 5032]
	ldr	w5, [x19, 5036]
	str	w6, [x19, 8832]
	str	w5, [x19, 8836]
	ldr	w4, [x19, 4964]
	ldr	w0, [x19, 4956]
	ldr	w5, [x19, 4884]
	ldr	w6, [x19, 5068]
	ldr	w2, [x19, 4960]
	str	w6, [x19, 8824]
	str	w5, [x19, 8828]
	sub	w2, w2, w0
	ldr	w1, [x19, 4968]
	sub	w0, w4, w0
	ldr	w6, [x19, 5056]
	ldr	w5, [x19, 5060]
	ldr	x3, [x19, 3000]
	str	w6, [x19, 8844]
	str	w5, [x19, 8848]
	ldr	w6, [x19, 5064]
	ldr	x5, [x19, 3040]
	str	w22, [x19, 7568]
	uxtw	x22, w22
	str	w2, [x19, 8840]
	lsl	x24, x22, 3
	str	w0, [x19, 8856]
	sub	w0, w1, w4
	str	w6, [x19, 8852]
	mov	x2, 64
	str	w0, [x19, 8860]
	add	x0, x24, x22, lsl 5
	str	x5, [x19, 10032]
	lsl	x23, x0, 3
	str	wzr, [x19, 204]
	sub	x23, x23, x0
	add	x0, x20, 3568
	ldrb	w1, [x3, 10]
	strb	w1, [x20, 3446]
	ldrb	w1, [x3, 3]
	strb	w1, [x20, 3447]
	ldrb	w1, [x3, 7]
	strb	w1, [x20, 3448]
	ldrb	w1, [x3, 6]
	strb	w1, [x20, 3449]
	ldrb	w1, [x3, 5]
	strb	w1, [x20, 3450]
	ldr	w1, [x3, 60]
	str	w1, [x19, 7548]
	ldr	w1, [x3, 104]
	strb	w1, [x20, 3456]
	ldr	w1, [x3, 192]
	ldr	x4, [x19, 3008]
	sub	w1, w1, #1
	str	w1, [x19, 7556]
	ldr	w6, [x19, 4860]
	add	x1, x23, 12288
	ldr	w5, [x3, 188]
	add	x1, x19, x1
	str	w6, [x19, 7564]
	add	x1, x1, 2020
	sub	w5, w5, #1
	str	w5, [x19, 7560]
	ldr	w5, [x4, 84]
	sub	w5, w5, #2
	str	w5, [x19, 7572]
	ldrb	w5, [x4, 11]
	strb	w5, [x20, 3480]
	ldrb	w4, [x4, 10]
	strb	w4, [x20, 3481]
	ldr	w4, [x3, 164]
	str	w4, [x19, 7580]
	ldr	w4, [x3, 168]
	str	w4, [x19, 7584]
	ldr	w4, [x3, 156]
	str	w4, [x19, 7588]
	ldr	w4, [x3, 160]
	str	w4, [x19, 7592]
	ldr	w4, [x3, 148]
	str	w4, [x19, 7596]
	ldr	w4, [x3, 152]
	str	w4, [x19, 7600]
	ldr	w4, [x3, 172]
	str	w4, [x19, 7604]
	ldr	x4, .LC169
	ldr	w5, [x3, 124]
	str	w5, [x19, 7608]
	ldr	x4, [x4, 104]
	ldr	w5, [x3, 128]
	str	w5, [x19, 7612]
	ldr	w5, [x3, 100]
	str	w5, [x19, 7616]
	ldr	w5, [x3, 92]
	str	w5, [x19, 7620]
	ldr	w5, [x3, 112]
	str	w5, [x19, 7624]
	ldr	w5, [x3, 108]
	str	w5, [x19, 7628]
	ldr	w5, [x3, 96]
	str	w5, [x19, 7632]
	ldr	w3, [x3, 88]
	str	w3, [x19, 7636]
	blr	x4
	ldr	x0, [x19, 3000]
	add	x3, x21, 1676
	add	x2, x21, 1596
	add	x1, x21, 1084
	ldr	w4, [x0, 68]
	str	w4, [x19, 7728]
	ldr	w0, [x0, 64]
	str	w0, [x19, 7732]
	mov	x0, x19
	bl	HEVC_CalcTileInfo
	cbnz	w0, .L654
	ldr	x1, [x19, 3008]
	mov	w0, 0
	ldrb	w2, [x1, 16]
	strb	w2, [x20, 3660]
	ldrb	w2, [x1, 7]
	strb	w2, [x20, 3661]
	ldrb	w2, [x1, 3]
	strb	w2, [x20, 3662]
	ldrb	w2, [x1, 14]
	strb	w2, [x20, 3663]
	ldrb	w2, [x1, 15]
	strb	w2, [x20, 3664]
	ldrb	w2, [x1, 13]
	strb	w2, [x20, 3665]
	ldr	x2, [x19, 3000]
	ldr	w3, [x1, 56]
	ldr	w2, [x2, 128]
	sub	w2, w2, w3
	str	w2, [x19, 7764]
	ldr	w2, [x1, 52]
	str	w2, [x19, 7768]
	ldrb	w2, [x1, 8]
	strb	w2, [x20, 3676]
	ldrb	w2, [x1, 12]
	strb	w2, [x20, 3677]
	ldrb	w2, [x1, 6]
	strb	w2, [x20, 3678]
	ldr	w2, [x1, 60]
	str	w2, [x19, 7776]
	ldr	w2, [x1, 64]
	str	w2, [x19, 7780]
	ldr	w2, [x1, 72]
	sub	w2, w2, #1
	str	w2, [x19, 7784]
	ldr	w2, [x1, 68]
	sub	w2, w2, #1
	str	w2, [x19, 7788]
	ldrb	w2, [x1, 10]
	strb	w2, [x20, 3481]
	ldrb	w1, [x1, 11]
	strb	w1, [x20, 3480]
	str	wzr, [x19, 2372]
	ldr	w1, [x19, 2356]
	cmp	w1, 1
	beq	.L636
	ldr	x1, [x19, 4912]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x25, x0
	cbz	x0, .L655
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L639
	cbz	x3, .L639
	ldr	w0, [x19, 276]
	add	x3, x21, 956
	add	x2, x21, 688
	add	x1, x21, 816
	add	x23, x19, x23
	bl	FSP_GetDecFsAddrTab
	ldr	x1, [x25, 32]
	add	x2, x21, 820
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 4]
	str	w1, [x19, 8824]
	add	x1, x21, 948
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x19, 4884]
	mov	w1, 0
	str	w0, [x19, 8828]
	ldr	w0, [x25, 12]
	str	w0, [x19, 9144]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 10232]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 10236]
	ldr	w3, [x23, 14172]
	str	w3, [x19, 10020]
	cbz	w3, .L644
	add	x22, x24, x22, lsl 1
	lsl	x0, x22, 3
	sub	x22, x0, x22
	.p2align 2
.L648:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x22, x0
	cmp	w1, w3
	add	x0, x19, x0, lsl 2
	add	x2, x19, x2, lsl 2
	ldr	w2, [x2, 14244]
	str	w2, [x0, 9956]
	bne	.L648
.L644:
	add	x23, x20, 3700
	mov	w22, 0
.L642:
	mov	x2, x23
	mov	w0, w22
	mov	x1, x19
	add	w22, w22, 1
	add	x23, x23, 64
	bl	HEVC_WriteQmatrix_8x8
	cmp	w22, 4
	bne	.L642
	mov	w0, w22
	add	x2, x20, 3956
	mov	x1, x19
	add	x23, x21, 116
	mov	w22, 2
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 4020
	mov	x1, x19
	mov	w0, 5
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 4084
	mov	x1, x19
	mov	w0, 0
	bl	HEVC_WriteQmatrix_16x16
	add	x2, x21, 52
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_16x16
.L645:
	mov	x2, x23
	mov	w0, w22
	mov	x1, x19
	add	w22, w22, 1
	add	x23, x23, 64
	bl	HEVC_WriteQmatrix_16x16
	cmp	w22, 6
	bne	.L645
	add	x2, x21, 372
	mov	x1, x19
	mov	w0, 0
	add	x22, x21, 500
	mov	w20, 0
	bl	HEVC_WriteQmatrix_32x32
	add	x2, x21, 436
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_32x32
	.p2align 2
.L646:
	mov	x2, x22
	mov	w0, w20
	mov	x1, x19
	add	w20, w20, 1
	add	x22, x22, 16
	bl	HEVC_WriteQmatrix_4x4
	cmp	w20, 6
	bne	.L646
	add	x0, x19, 2304
	add	x8, x19, 2304
	ldp	w5, w6, [x0, 4]
	ldp	w3, w4, [x8, 20]
	ldp	w7, w2, [x0, -4]
	ldp	w0, w1, [x8, 12]
	lsl	w3, w3, 16
	lsl	w5, w5, 16
	orr	w3, w3, w4, lsl 24
	orr	w5, w5, w6, lsl 24
	orr	w0, w0, w1, lsl 8
	orr	w2, w7, w2, lsl 8
	orr	w0, w3, w0
	ldr	w4, [x19, 4884]
	orr	w1, w5, w2
	str	w0, [x19, 8792]
	str	w1, [x19, 8788]
	mov	w0, 0
	str	w4, [x19, 8820]
.L636:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L654:
	ldr	x2, .LC170
	mov	w0, 1
	ldr	x1, .LC172
	add	x2, x2, 352
	bl	dprint_vfmw
	mov	w0, -1
	b	.L636
.L639:
	ldr	x1, .LC176
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L636
.L655:
	ldr	x2, [x19, 4912]
	mov	w0, 1
	ldr	x1, .LC174
	ldr	w2, [x2, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L636
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.align	3
.LC166:
	.xword	.LC165
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC169:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC170:
	.xword	.LANCHOR0
	.align	3
.LC172:
	.xword	.LC171
	.align	3
.LC174:
	.xword	.LC173
	.align	3
.LC176:
	.xword	.LC175
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	add	x0, x0, 1456
	ldrb	w1, [x0, 1]
	cbz	w1, .L658
	ldrsb	w1, [x19, 14]
	add	x0, x19, 12288
	add	x0, x0, 508
	cbz	w1, .L690
.L658:
	ldp	w4, w5, [x0, 68]
	cmp	w4, 16
	bhi	.L691
	cmp	w5, 16
	bhi	.L662
	cbz	w4, .L663
	ldr	x0, [x19, 3056]
	cbz	x0, .L676
	ldr	x0, [x0, 24]
	cbz	x0, .L692
	add	x0, x19, 3064
	mov	w2, 0
	b	.L668
	.p2align 3
.L669:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L664
	ldr	x1, [x1, 24]
	cbz	x1, .L665
.L668:
	add	w2, w2, 1
	cmp	w4, w2
	bne	.L669
.L663:
	cbz	w5, .L678
	ldr	x0, [x19, 3192]
	cbz	x0, .L679
	ldr	x0, [x0, 24]
	cbz	x0, .L693
	add	x0, x19, 3200
	mov	w2, 0
	b	.L674
	.p2align 3
.L675:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L670
	ldr	x1, [x1, 24]
	cbz	x1, .L671
.L674:
	add	w2, w2, 1
	cmp	w5, w2
	bne	.L675
.L678:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L676:
	mov	w2, 0
	.p2align 2
.L664:
	ldr	x1, .LC185
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L660:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L692:
	mov	w2, 0
.L665:
	ldr	x1, .LC187
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L679:
	mov	w2, 0
.L670:
	ldr	x1, .LC189
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L693:
	mov	w2, 0
.L671:
	ldr	x1, .LC191
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L690:
	ldr	x2, .LC177
	mov	w0, 0
	ldr	x1, .LC179
	add	x2, x2, 376
	bl	dprint_vfmw
	mov	w0, -1
	b	.L660
.L662:
	ldr	x1, .LC183
	mov	w3, 17
	mov	w2, w5
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L660
.L691:
	ldr	x1, .LC181
	mov	w3, 17
	mov	w2, w4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L660
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	3
.LC177:
	.xword	.LANCHOR0
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	ldr	w24, [x19, 4856]
	bl	HEVC_CheckListX
	mov	w23, w0
	cbnz	w0, .L766
	ldr	w3, [x19, 152]
	ldr	w0, [x19, 204]
	cmp	w0, w3
	bcs	.L844
	mov	w22, 1512
	ldr	x21, .LC194
	ldr	x20, [x19, 3040]
	mov	x2, 1512
	umull	x0, w0, w22
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x20, x20, x0
	mov	x0, x20
	blr	x3
	ldr	x3, [x21, 96]
	mov	w1, 0
	mov	x2, 64
	add	x0, x29, 176
	blr	x3
	ldr	w0, [x19, 204]
	ldr	w1, [x19, 152]
	add	w0, w0, 1
	str	w0, [x19, 204]
	cmp	w0, w1
	bcc	.L845
	str	xzr, [x20, 1504]
.L698:
	ldr	w22, [x19, 176]
	ldr	w0, [x19, 260]
	ldr	w1, [x19, 5588]
	add	w22, w22, 1
	ldr	x3, [x19, 2976]
	add	w0, w0, 1
	str	w22, [x19, 176]
	str	w1, [x19, 208]
	str	w0, [x19, 260]
	ldrb	w1, [x3]
	ldr	w0, [x3, 8]
	cmp	w1, 1
	ccmp	w1, w0, 2, ls
	bcs	.L699
	.p2align 2
.L700:
	uxtw	x0, w1
	lsl	x2, x0, 5
	add	x3, x3, x2
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 60]
	str	w3, [x0, 8]
	ldr	x3, [x19, 2976]
	add	x3, x3, x2
	ldr	w3, [x3, 56]
	str	w3, [x20, w1, uxtw 2]
	add	w1, w1, 1
	ldr	x3, [x19, 2976]
	add	x2, x3, x2
	ldr	w2, [x2, 64]
	str	w2, [x0, 16]
	ldr	x3, [x19, 2976]
	ldr	w0, [x3, 8]
	cmp	w0, w1
	ccmp	w1, 1, 2, hi
	bls	.L700
.L699:
	cmp	w0, 1
	bhi	.L705
	.p2align 2
.L816:
	add	x1, x20, x0, uxtw 2
	str	wzr, [x1, 8]
	str	wzr, [x20, w0, uxtw 2]
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 16]
	bne	.L816
.L705:
	add	x25, x19, 4096
	add	x26, x19, 12288
	ldrb	w0, [x25, 1457]
	cbz	w0, .L846
.L703:
	ldr	w0, [x19, 12864]
	cbz	w0, .L706
	mov	w4, 0
	mov	w5, 1
	b	.L710
	.p2align 3
.L848:
	ldr	w1, [x3, 16]
	cbz	w1, .L708
	ldr	w1, [x19, 5584]
	cbz	w1, .L708
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 36]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9012]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 36]
	str	w1, [x0, 372]
	ldrb	w1, [x19, 2]
	cbz	w1, .L709
	str	w5, [x0, 116]
.L709:
	ldr	w0, [x19, 12864]
	add	w4, w4, 1
	cmp	w0, w4
	bls	.L847
	.p2align 2
.L710:
	uxtw	x0, w4
	add	x1, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x2, [x1, 3056]
	ldr	w2, [x2, 4]
	str	w2, [x0, 116]
	ldrb	w2, [x19, 1]
	ldr	x3, [x1, 3056]
	cbnz	w2, .L848
.L708:
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	add	w4, w4, 1
	ldp	w2, w1, [x1, 20]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9012]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 24]
	str	w1, [x0, 372]
	ldr	w0, [x19, 12864]
	cmp	w0, w4
	bhi	.L710
.L847:
	ldr	w3, [x19, 12868]
	cbz	w3, .L711
.L765:
	mov	w4, 0
	mov	w5, 1
	b	.L715
	.p2align 3
.L850:
	ldr	w1, [x3, 16]
	cbz	w1, .L713
	ldr	w1, [x19, 5584]
	cbz	w1, .L713
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 36]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9012]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 36]
	str	w1, [x0, 436]
	ldrb	w1, [x19, 2]
	cbz	w1, .L714
	str	w5, [x0, 180]
.L714:
	ldr	w3, [x19, 12868]
	add	w4, w4, 1
	cmp	w3, w4
	bls	.L849
	.p2align 2
.L715:
	uxtw	x0, w4
	add	x1, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x2, [x1, 3192]
	ldr	w2, [x2, 4]
	str	w2, [x0, 180]
	ldrb	w2, [x19, 1]
	ldr	x3, [x1, 3192]
	cbnz	w2, .L850
.L713:
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	add	w4, w4, 1
	ldp	w2, w1, [x1, 20]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9012]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 24]
	str	w1, [x0, 436]
	ldr	w3, [x19, 12868]
	cmp	w3, w4
	bhi	.L715
.L849:
	ldr	w0, [x19, 12864]
.L711:
	cbz	w0, .L716
	uxtw	x1, w24
	ldr	w2, [x20, 372]
	lsl	x4, x1, 3
	ldr	w5, [x19, 4860]
	add	x4, x4, x1, lsl 1
	lsl	x1, x4, 3
	sub	x4, x1, x4
	add	x1, x4, x2
	add	x1, x19, x1, lsl 2
	ldr	w1, [x1, 14308]
	cmp	w5, w1
	blt	.L772
	sub	w0, w0, #1
	mov	x1, x20
	add	x2, x20, x0, lsl 2
	b	.L719
	.p2align 3
.L720:
	ldr	w0, [x1, 376]
	add	x1, x1, 4
	add	x0, x4, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14308]
	cmp	w0, w5
	bgt	.L772
.L719:
	cmp	x1, x2
	bne	.L720
.L716:
	ldr	w0, [x19, 12816]
	cbnz	w0, .L843
	mov	w0, 1
	cbz	w3, .L717
	uxtw	x1, w24
	ldr	w4, [x19, 4860]
	lsl	x0, x1, 3
	add	x1, x0, x1, lsl 1
	ldr	w0, [x20, 436]
	lsl	x2, x1, 3
	sub	x2, x2, x1
	add	x0, x2, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14308]
	cmp	w4, w0
	blt	.L772
	sub	w3, w3, #1
	mov	x1, x20
	add	x3, x20, x3, lsl 2
	b	.L722
	.p2align 3
.L723:
	ldr	w0, [x1, 440]
	add	x1, x1, 4
	add	x0, x2, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14308]
	cmp	w0, w4
	bgt	.L772
.L722:
	cmp	x1, x3
	bne	.L723
.L843:
	mov	w0, 1
.L717:
	strb	w0, [x20, 24]
	ldrb	w0, [x25, 1457]
	strb	w0, [x20, 25]
	ldr	w2, [x19, 12812]
	str	w2, [x20, 28]
	ldrb	w0, [x26, 515]
	strb	w0, [x20, 32]
	ldr	w0, [x19, 12836]
	str	w0, [x20, 36]
	ldr	w0, [x19, 2356]
	cbnz	w0, .L724
	ldr	x3, [x19, 4912]
	ldr	w4, [x19, 204]
	ldr	w0, [x3, 324]
	sub	w1, w4, #1
	madd	w0, w1, w0, w2
	udiv	w0, w0, w4
	str	w0, [x3, 68]
.L724:
	ldr	w0, [x19, 12816]
	cbz	w0, .L851
	cmp	w0, 1
	mov	w24, 0
	beq	.L726
.L727:
	str	w24, [x20, 40]
	ldr	w0, [x19, 12840]
	str	w0, [x20, 48]
	ldrb	w0, [x26, 516]
	strb	w0, [x20, 52]
	ldr	w0, [x19, 12844]
	str	w0, [x20, 44]
	ldr	w0, [x19, 12872]
	cbz	w0, .L728
	sub	w0, w0, #1
	str	w0, [x20, 60]
.L729:
	ldr	w0, [x19, 12876]
	cbz	w0, .L730
	sub	w0, w0, #1
	str	w0, [x20, 56]
.L731:
	ldrb	w0, [x26, 512]
	strb	w0, [x20, 64]
	ldrb	w0, [x26, 514]
	strb	w0, [x20, 65]
	ldr	w0, [x19, 12864]
	str	w0, [x20, 68]
	ldr	w0, [x19, 12868]
	str	w0, [x20, 72]
	ldr	w0, [x19, 12816]
	str	w0, [x20, 76]
	ldr	w0, [x19, 5592]
	str	w0, [x20, 80]
	ldr	x0, [x19, 3000]
	ldr	w3, [x19, 5592]
	ldr	w1, [x0, 188]
	mov	x0, x19
	udiv	w2, w3, w1
	msub	w1, w2, w1, w3
	str	w1, [x20, 84]
	ldr	x1, [x19, 3000]
	ldr	w2, [x1, 188]
	ldr	w1, [x19, 5592]
	udiv	w1, w1, w2
	str	w1, [x20, 88]
	ldr	w1, [x19, 5592]
	bl	HEVC_CtbRsAddrToTsAddr
	str	w0, [x20, 92]
	ldr	w0, [x19, 12848]
	str	w0, [x20, 96]
	ldr	w0, [x19, 12852]
	str	w0, [x20, 100]
	ldr	w0, [x19, 12860]
	str	w0, [x20, 104]
	ldr	w0, [x19, 12856]
	str	w0, [x20, 108]
	ldrb	w0, [x26, 511]
	strb	w0, [x20, 112]
	ldrb	w0, [x26, 510]
	strb	w0, [x20, 113]
	ldrb	w0, [x26, 517]
	strb	w0, [x20, 114]
	ldrb	w0, [x26, 518]
	strb	w0, [x20, 115]
	ldr	x0, [x19, 3008]
	ldrb	w1, [x0, 10]
	cbz	w1, .L732
	ldr	w1, [x19, 12816]
	cmp	w1, 1
	beq	.L733
.L732:
	ldrb	w0, [x0, 11]
	cmp	w0, 1
	beq	.L852
.L735:
	ldrb	w0, [x26, 512]
	cbz	w0, .L737
	add	x0, x29, 240
	add	x24, x0, x24, sxtw 2
	ldr	w0, [x24, -64]
	str	w0, [x20, 564]
.L738:
	ldrb	w0, [x19, 2]
	cbz	w0, .L739
	ldr	w0, [x19, 5584]
	cbz	w0, .L739
	ldr	x8, [x19, 3040]
	add	x26, x20, 1356
	cmp	x20, x8
	beq	.L853
.L742:
	ldr	w4, [x20, 68]
	cbz	w4, .L743
	mov	x1, 0
	mov	w0, 0
	.p2align 2
.L745:
	add	x2, x19, x0, sxtw 3
	add	w0, w0, 1
	ldr	x2, [x2, 3056]
	ldr	x2, [x2, 24]
	add	x3, x2, 88
	ldr	w2, [x2, 32]
	cmp	w2, wzr
	csel	x1, x1, x3, ne
	cmp	w0, w4
	bne	.L745
	cbz	x1, .L743
.L746:
	ldrsw	x0, [x20, 40]
	ldr	w2, [x19, 4868]
	add	x0, x19, x0
	ldr	w12, [x19, 4872]
	add	x0, x0, 12288
	ldrsb	w0, [x0, 2428]
	cbnz	w0, .L749
	mov	w0, 1
	strb	w0, [x26, 1]
.L750:
	cbz	x1, .L751
	add	x24, x8, 1356
	ldr	w0, [x1, 168]
	ldp	w5, w6, [x1, 68]
	str	w2, [x29, 120]
	str	w0, [x24, 112]
	str	w5, [x29, 128]
	ldr	w0, [x1, 172]
	str	w0, [x24, 116]
	ldr	x3, [x21, 472]
	ldr	w0, [x1, 112]
	str	w0, [x24, 120]
	ldp	w4, w0, [x1, 20]
	sub	w0, w0, w4
	str	w0, [x24, 124]
	ldr	w0, [x1, 140]
	str	w0, [x24, 128]
	ldr	w0, [x1, 144]
	str	w0, [x24, 132]
	ldr	w4, [x1, 20]
	ldr	w0, [x1, 44]
	sub	w0, w0, w4
	str	w0, [x24, 136]
	ldr	w0, [x1, 48]
	ldr	w1, [x1, 44]
	sub	w0, w0, w1
	str	w0, [x24, 140]
	ldr	x10, [x19, 3008]
	stp	x8, x10, [x29, 104]
	add	x4, x10, 1888
	ldr	w0, [x10, 1960]
	ldr	w28, [x10, 2472]
	ldr	w1, [x10, 3496]
	sub	w0, w2, w0, lsl 1
	sub	w9, w0, w28, lsl 1
	ldr	w0, [x10, 2984]
	sxtw	x11, w9
	sub	w0, w5, w0, lsl 1
	sub	w7, w0, w1, lsl 1
	ldr	w0, [x10, 2216]
	stp	w12, w7, [x29, 152]
	ldr	w27, [x10, 2728]
	sub	w0, w12, w0, lsl 1
	ldr	w1, [x10, 3240]
	str	w9, [x29, 160]
	sub	w27, w0, w27, lsl 1
	ldr	w0, [x10, 3752]
	sub	w1, w6, w1, lsl 1
	str	x4, [x29, 144]
	str	w6, [x29, 136]
	sub	w28, w1, w0, lsl 1
	sbfiz	x0, x7, 16, 32
	mov	w1, w9
	add	x0, x0, x11, lsr 1
	blr	x3
	mov	x11, x0
	sxtw	x1, w27
	ldr	x3, [x21, 472]
	sbfiz	x0, x28, 16, 32
	str	x11, [x29, 168]
	add	x0, x0, x1, lsr 1
	mov	w1, w27
	blr	x3
	mov	x21, x0
	ldr	w2, [x29, 120]
	ldr	w5, [x29, 128]
	ldr	w6, [x29, 136]
	cmp	w2, w5
	ldr	w9, [x29, 160]
	ldp	w12, w7, [x29, 152]
	ldp	x8, x10, [x29, 104]
	ldr	x4, [x29, 144]
	ldr	x11, [x29, 168]
	bgt	.L752
	cmp	w11, 65536
	cset	w14, le
.L753:
	cmp	w12, w6
	bgt	.L754
	cmp	w21, 65536
	cset	w13, le
.L755:
	mov	w0, 1
	strb	w0, [x8, 1356]
	stp	w5, w6, [x24, 8]
	cbz	w14, .L756
	orr	w13, w14, w13
	str	w13, [x24, 4]
.L756:
	stp	w11, w21, [x24, 24]
	stp	w11, w21, [x24, 32]
	ldrb	w0, [x4, 2]
	cbz	w0, .L757
	ldr	w0, [x4, 2120]
	str	w0, [x24, 72]
	mul	w8, w0, w11
	ldr	w0, [x10, 4264]
	str	w0, [x24, 76]
	add	w8, w8, 8
	mul	w3, w0, w21
	ldr	w0, [x10, 4520]
	neg	w8, w8, asr 4
	add	w3, w3, 8
	sub	w0, w0, #8
	str	w0, [x24, 80]
	neg	w3, w3, asr 4
	mul	w2, w0, w11
	ldr	w1, [x10, 4776]
	asr	w0, w28, 1
	add	w2, w2, 8
	sub	w1, w1, #8
	str	w1, [x24, 84]
	neg	w2, w2, asr 4
.L758:
	mul	w1, w1, w21
	add	w0, w0, w27, lsl 8
	add	w1, w1, 8
	stp	w8, w3, [x24, 88]
	neg	w1, w1, asr 4
	mov	w3, 4095
	stp	w2, w1, [x24, 96]
	asr	w1, w7, 1
	mov	w2, -4096
	sdiv	w0, w0, w28
	add	w1, w1, w9, lsl 8
	sdiv	w1, w1, w7
	cmp	w1, 4095
	csel	w1, w1, w3, le
	cmn	w1, #4096
	csel	w1, w1, w2, ge
	cmp	w0, w3
	csel	w0, w0, w3, le
	cmp	w0, w2
	csel	w0, w0, w2, ge
	stp	w1, w0, [x24, 104]
	mov	w0, 1
	ldr	w1, [x4, 72]
	lsl	w1, w1, 1
	str	w1, [x24, 40]
	asr	w2, w1, 1
	ldr	w1, [x4, 328]
	lsl	w1, w1, 1
	stp	w1, w2, [x24, 44]
	asr	w1, w1, 1
	str	w1, [x24, 52]
	ldr	w1, [x4, 1096]
	lsl	w1, w1, 1
	str	w1, [x24, 56]
	asr	w2, w1, 1
	ldr	w1, [x4, 1352]
	lsl	w1, w1, 1
	stp	w1, w2, [x24, 60]
	asr	w1, w1, 1
	str	w1, [x24, 68]
	ldr	x1, [x19, 3000]
	ldr	w1, [x1, 128]
	lsl	w1, w0, w1
	sub	w2, w1, #1
	neg	w1, w1
	add	w0, w5, w2
	add	w2, w6, w2
	and	w0, w0, w1
	and	w1, w2, w1
	stp	w0, w1, [x24, 16]
.L751:
	str	wzr, [x26, 144]
	mov	w2, 0
	mov	w0, 0
	ldr	w1, [x19, 14452]
	cbz	w1, .L741
	.p2align 2
.L815:
	add	x1, x19, x0, sxtw
	add	x1, x1, 12288
	ldrsb	w1, [x1, 2428]
	lsl	w1, w1, w0
	add	w0, w0, 1
	orr	w2, w2, w1
	str	w2, [x26, 144]
	ldr	w1, [x19, 14452]
	cmp	w1, w0
	bhi	.L815
	b	.L741
	.p2align 3
.L845:
	ldr	x1, [x19, 3040]
	umull	x0, w0, w22
	add	x0, x1, x0
	str	x0, [x20, 1504]
	b	.L698
	.p2align 3
.L772:
	mov	w0, 0
	b	.L717
	.p2align 3
.L739:
	mov	w1, 1
	strb	wzr, [x20, 1356]
	strb	w1, [x20, 1357]
	str	wzr, [x20, 1360]
.L741:
	ldr	w0, [x19, 2356]
	cbnz	w0, .L762
	ldr	x0, [x19, 3016]
	ldr	x1, [x19, 2976]
	str	x1, [x0, w22, uxtw 3]
	str	xzr, [x19, 2976]
.L762:
	ldrb	w0, [x25, 3665]
	cbz	w0, .L797
	ldr	w0, [x19, 260]
	cmp	w0, 1
	beq	.L854
	sub	w1, w0, #2
	ldr	w2, [x20, 92]
	sub	w0, w0, #1
	add	x1, x19, x1, lsl 3
	sub	w2, w2, #1
	add	x3, x19, x0, lsl 3
	str	w2, [x1, 11128]
	ldr	w1, [x20, 92]
	str	w1, [x3, 11124]
.L764:
	ldr	w1, [x19, 7556]
	add	x0, x19, x0, lsl 3
	ldr	w2, [x19, 7560]
	mov	w3, 36863
	madd	w2, w1, w2, w2
	add	w1, w2, w1
	str	w1, [x0, 11128]
	ldr	w1, [x20, 92]
	sub	w1, w1, #1
	cmp	w1, w3
	bhi	.L797
	mov	x0, x19
	bl	HEVC_CtbTsAddrToRsAddr
	str	w0, [x20, 568]
.L797:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L851:
	ldrb	w0, [x26, 516]
	cbnz	w0, .L726
	ldrsw	x0, [x19, 12840]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 436]
	b	.L727
	.p2align 3
.L737:
	ldr	w0, [x19, 9012]
	str	w0, [x20, 564]
	b	.L738
	.p2align 3
.L730:
	str	wzr, [x20, 56]
	b	.L731
	.p2align 3
.L728:
	str	wzr, [x20, 60]
	b	.L729
	.p2align 3
.L726:
	ldrsw	x0, [x19, 12840]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 372]
	b	.L727
	.p2align 3
.L846:
	ldr	x3, [x21, 104]
	mov	x2, 1376
	add	x1, x25, 1456
	add	x0, x26, 508
	blr	x3
	mov	w0, 1
	strb	w0, [x19, 14]
	b	.L703
	.p2align 3
.L852:
	ldr	w0, [x19, 12816]
	cbnz	w0, .L735
.L733:
	ldr	w0, [x19, 12952]
	mov	x2, 64
	str	w0, [x20, 580]
	add	x1, x26, 800
	ldr	x3, [x21, 104]
	ldr	w0, [x19, 13084]
	str	w0, [x20, 584]
	add	x0, x20, 588
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 64
	add	x1, x26, 668
	add	x0, x20, 716
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 864
	add	x0, x20, 844
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 992
	add	x0, x20, 1100
	blr	x3
	ldr	w0, [x19, 12816]
	cbnz	w0, .L735
	ldr	x3, [x21, 104]
	add	x1, x26, 1120
	mov	x2, 64
	add	x0, x20, 652
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x26, 732
	mov	x2, 64
	add	x0, x20, 780
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x26, 1184
	mov	x2, 128
	add	x0, x20, 972
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 1312
	add	x0, x20, 1228
	blr	x3
	b	.L735
	.p2align 3
.L749:
	strb	wzr, [x26, 1]
	b	.L750
	.p2align 3
.L854:
	ldr	w1, [x20, 92]
	mov	x0, 0
	str	w1, [x19, 11124]
	b	.L764
	.p2align 3
.L754:
	lsl	w0, w6, 2
	mov	w13, 1
	sub	w0, w0, w6
	add	w1, w0, w0, lsr 31
	cmp	w12, w1, asr 1
	ble	.L755
	cmp	w12, w6, lsl 1
	mov	w13, 2
	ble	.L755
	cmp	w12, w0
	mov	w13, 3
	ble	.L755
	ldr	x1, .LC198
	mov	w3, w6
	mov	w2, w12
	mov	w0, 1
	str	x4, [x29, 104]
	str	w13, [x29, 112]
	str	w14, [x29, 120]
	str	x11, [x29, 128]
	str	w7, [x29, 136]
	str	x10, [x29, 144]
	stp	w9, w5, [x29, 152]
	str	x8, [x29, 160]
	str	w6, [x29, 168]
	bl	dprint_vfmw
	ldr	w13, [x29, 112]
	ldr	w14, [x29, 120]
	ldr	w7, [x29, 136]
	ldp	w9, w5, [x29, 152]
	ldr	w6, [x29, 168]
	ldr	x4, [x29, 104]
	ldr	x11, [x29, 128]
	ldr	x10, [x29, 144]
	ldr	x8, [x29, 160]
	b	.L755
	.p2align 3
.L752:
	lsl	w0, w5, 2
	mov	w14, 1
	sub	w0, w0, w5
	add	w1, w0, w0, lsr 31
	cmp	w2, w1, asr 1
	ble	.L753
	cmp	w2, w5, lsl 1
	mov	w14, 2
	ble	.L753
	cmp	w2, w0
	mov	w14, 3
	ble	.L753
	ldr	x1, .LC196
	mov	w3, w5
	mov	w0, 1
	str	x4, [x29, 104]
	str	w14, [x29, 112]
	str	x11, [x29, 120]
	str	w9, [x29, 128]
	str	x10, [x29, 136]
	str	w6, [x29, 144]
	stp	w7, w12, [x29, 152]
	str	x8, [x29, 160]
	str	w5, [x29, 168]
	bl	dprint_vfmw
	ldr	w14, [x29, 112]
	ldr	w9, [x29, 128]
	ldr	w6, [x29, 144]
	ldp	w7, w12, [x29, 152]
	ldr	w5, [x29, 168]
	ldr	x4, [x29, 104]
	ldr	x11, [x29, 120]
	ldr	x10, [x29, 136]
	ldr	x8, [x29, 160]
	b	.L753
	.p2align 3
.L757:
	asr	w0, w28, 1
	mov	w2, 0
	add	w1, w0, w27, lsl 2
	mov	w3, 0
	mov	w8, 0
	sdiv	w1, w1, w28
	stp	wzr, wzr, [x24, 72]
	sub	w1, w1, #4
	stp	wzr, w1, [x24, 80]
	b	.L758
.L706:
	ldr	w0, [x19, 12868]
	cbnz	w0, .L765
	mov	w0, 1
	b	.L717
.L743:
	ldr	w4, [x20, 72]
	mov	x1, 0
	cbz	w4, .L746
	mov	w0, 0
	.p2align 2
.L748:
	add	x2, x19, x0, sxtw 3
	add	w0, w0, 1
	ldr	x2, [x2, 3192]
	ldr	x2, [x2, 24]
	add	x3, x2, 88
	ldr	w2, [x2, 32]
	cmp	w2, wzr
	csel	x1, x1, x3, ne
	cmp	w0, w4
	bne	.L748
	b	.L746
.L853:
	str	wzr, [x26, 4]
	strb	wzr, [x20, 1356]
	b	.L742
.L766:
	mov	w23, -1
	b	.L797
.L844:
	ldr	x1, .LC193
	mov	w2, w0
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L797
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC194:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC198:
	.xword	.LC197
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
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
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
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
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 4876]
	ldr	w0, [x19, 204]
	ldr	w2, [x19, 4880]
	cmp	w1, wzr
	str	w0, [x19, 10024]
	cset	w1, eq
	str	w2, [x19, 8868]
	mov	w0, 0
	str	w1, [x19, 8876]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L888
.L859:
	ldr	w3, [x19, 5588]
	ldr	w4, [x19, 164]
	tbnz	w3, #31, .L862
	cmp	w3, w4
	bge	.L862
	ldr	x0, [x19, 2960]
	mov	w1, 5036
	ldr	w4, [x19, 160]
	smaddl	x3, w3, w1, x0
	ldr	w3, [x3, 32]
	tbnz	w3, #31, .L865
	cmp	w3, w4
	bge	.L865
	add	x20, x19, 4096
	ldr	x2, [x19, 2952]
	mov	w4, 12668
	ldr	w5, [x19, 6484]
	ldr	w6, [x20, 2392]
	mov	w0, 1
	smaddl	x3, w3, w4, x2
	ldr	w9, [x20, 2396]
	add	w8, w5, w6
	ldr	w2, [x3, 116]
	cmp	w8, w9
	mov	w3, w8
	lsl	w2, w0, w2
	bcs	.L878
	cmp	w8, 15
	bgt	.L868
	ldr	w4, [x19, 4860]
	b	.L870
	.p2align 3
.L889:
	cmp	w9, w3
	bls	.L878
	cmp	w3, 16
	beq	.L868
.L870:
	add	x0, x19, x3, sxtw 2
	mov	w1, w4
	add	w3, w3, 1
	ldr	w7, [x0, 5640]
	ldr	w0, [x0, 6584]
	cbnz	w7, .L871
	sdiv	w1, w4, w2
	sdiv	w7, w0, w2
	msub	w1, w1, w2, w4
	msub	w0, w7, w2, w0
.L871:
	cmp	w1, w0
	bne	.L889
	mov	w21, 1
.L867:
	cbz	w8, .L881
	ldr	w3, [x19, 5564]
	add	x2, x20, 2424
	ldr	w1, [x20, 2420]
	mov	w4, 0
	ldr	w0, [x19, 4860]
	add	w1, w3, w1
	cmp	w0, w1
	bne	.L876
	b	.L873
	.p2align 3
.L875:
	ldr	w1, [x2], 4
	add	w1, w3, w1
	cmp	w1, w0
	beq	.L873
.L876:
	add	w4, w4, 1
	cmp	w4, w8
	beq	.L881
	cmp	w4, 17
	bne	.L875
	ldr	x1, .LC206
	mov	w3, w4
	mov	w2, 8976
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w21
	b	.L860
	.p2align 3
.L862:
	ldr	x1, .LC200
	mov	w2, 8915
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
.L860:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L888:
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L859
.L873:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L865:
	ldr	x1, .LC202
	mov	w2, 8927
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L878:
	mov	w21, 0
	b	.L867
	.p2align 3
.L868:
	ldr	x1, .LC204
	mov	w5, w9
	mov	w4, 16
	mov	w2, 8947
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	w5, [x19, 6484]
	ldr	w6, [x20, 2392]
	add	w8, w6, w5
	b	.L867
	.p2align 3
.L881:
	mov	w0, w21
	b	.L860
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicVPSRefresh
	.type	HEVC_IsPicVPSRefresh, %function
HEVC_IsPicVPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 2992]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	beq	.L893
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L893:
	ldrb	w0, [x19, 2]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicVPSRefresh, .-HEVC_IsPicVPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicVPS
	.type	HEVC_UpdatePicVPS, %function
HEVC_UpdatePicVPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 24912
	mov	x20, -24912
	bl	_mcount
	strb	wzr, [x22, 2]
	ldr	x3, .LC207
	mov	x1, x22
	ldr	w0, [x19, 156]
	mov	x2, 24912
	ldr	x4, [x19, 2944]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 156]
	ldr	x1, [x19, 2944]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 2992]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicVPS, .-HEVC_UpdatePicVPS
	.align	3
.LC207:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicSPSRefresh
	.type	HEVC_IsPicSPSRefresh, %function
HEVC_IsPicSPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 3000]
	ldr	w0, [x19, 56]
	ldr	w1, [x1, 56]
	cmp	w1, w0
	beq	.L898
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L898:
	ldrb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicSPSRefresh, .-HEVC_IsPicSPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicSPS
	.type	HEVC_UpdatePicSPS, %function
HEVC_UpdatePicSPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 12668
	mov	x20, -12668
	bl	_mcount
	strb	wzr, [x22]
	ldr	x3, .LC208
	mov	x1, x22
	ldr	w0, [x19, 160]
	mov	x2, 12668
	ldr	x4, [x19, 2952]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 160]
	ldr	x1, [x19, 2952]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 3000]
	ldr	w1, [x0, 56]
	str	w1, [x19, 288]
	ldr	w1, [x0, 64]
	str	w1, [x19, 292]
	ldr	w1, [x0, 68]
	str	w1, [x19, 296]
	ldr	w0, [x0, 128]
	str	w0, [x19, 300]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicSPS, .-HEVC_UpdatePicSPS
	.align	3
.LC208:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicPPSRefresh
	.type	HEVC_IsPicPPSRefresh, %function
HEVC_IsPicPPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 3008]
	ldr	w0, [x19, 28]
	ldr	w1, [x1, 28]
	cmp	w1, w0
	beq	.L903
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L903:
	ldrb	w0, [x19, 1]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicPPSRefresh, .-HEVC_IsPicPPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicPPS
	.type	HEVC_UpdatePicPPS, %function
HEVC_UpdatePicPPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x2
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	strb	wzr, [x19, 1]
	ldrb	w0, [x19, 13]
	cbz	w0, .L905
	ldrb	w0, [x19, 15]
	cbnz	w0, .L925
	ldr	w0, [x19, 68]
	ldr	w2, [x21, 188]
	sub	w3, w0, #1
	add	x1, x19, x0, sxtw 1
	cmp	w3, wzr
	strh	w2, [x1, 170]
	ble	.L917
	sub	w4, w0, #2
	add	x0, x19, 88
	add	x4, x4, 45
	add	x4, x19, x4, lsl 1
	.p2align 2
.L916:
	ldrsh	w3, [x0]
	add	x0, x0, 2
	strh	w3, [x0, 82]
	cmp	x0, x4
	ldrh	w2, [x1, 170]
	sub	w2, w2, w3
	strh	w2, [x1, 170]
	bne	.L916
.L917:
	ldr	w0, [x19, 72]
	ldr	w1, [x21, 192]
	sub	w2, w0, #1
	add	x3, x19, x0, sxtw 1
	cmp	w2, wzr
	strh	w1, [x3, 210]
	ble	.L912
	sub	w4, w0, #2
	add	x0, x19, 128
	add	x4, x4, 65
	add	x4, x19, x4, lsl 1
	.p2align 2
.L918:
	ldrsh	w2, [x0]
	add	x0, x0, 2
	strh	w2, [x0, 82]
	cmp	x4, x0
	ldrh	w1, [x3, 210]
	sub	w1, w1, w2
	strh	w1, [x3, 210]
	bne	.L918
	b	.L912
	.p2align 3
.L905:
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L912:
	ldr	w0, [x20, 164]
	mov	w22, 5036
	ldr	x1, .LC211
	mov	x21, -5036
	ldr	x4, [x20, 2960]
	mov	x2, 5036
	smaddl	x0, w0, w22, x21
	ldr	x3, [x1, 104]
	mov	x1, x19
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x20, 164]
	ldr	x1, [x20, 2960]
	smaddl	x0, w0, w22, x21
	add	x0, x1, x0
	str	x0, [x20, 3008]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L925:
	ldr	w4, [x19, 68]
	add	x1, x19, 172
	mov	w3, 0
	cmp	w4, wzr
	ble	.L911
	.p2align 2
.L920:
	add	w3, w3, 1
	ldr	w5, [x21, 188]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L920
.L911:
	ldr	w4, [x19, 72]
	add	x1, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L912
	.p2align 2
.L919:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L919
	b	.L912
	.size	HEVC_UpdatePicPPS, .-HEVC_UpdatePicPPS
	.align	3
.LC211:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPicInfo
	.type	HEVC_InitPicInfo, %function
HEVC_InitPicInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x3, x19, 4096
	mov	w2, 1
	mov	w1, -1
	ldr	x0, .LC212
	strb	w2, [x3, 753]
	str	w1, [x19, 4880]
	ldr	w4, [x19, 5580]
	ldr	x1, [x19, 3000]
	ldr	w2, [x19, 5564]
	str	w4, [x19, 4852]
	str	w2, [x19, 4860]
	ldrsw	x4, [x19, 276]
	ldr	w5, [x1, 64]
	str	w5, [x19, 4868]
	ldr	x0, [x0, x4, lsl 3]
	ldr	w4, [x1, 68]
	str	w4, [x19, 4872]
	str	wzr, [x19, 4876]
	ldrsb	w4, [x0, 44]
	cmp	w4, 1
	beq	.L939
.L927:
	ldr	w0, [x19, 2356]
	cbnz	w0, .L930
	ldr	x0, [x19, 3032]
	mov	x1, -1
	ldr	x2, [x0, 56]
	str	x2, [x19, 5504]
	ldr	x2, [x0, 72]
	str	x2, [x19, 5512]
	ldr	x2, [x0, 88]
	str	x2, [x19, 5520]
	ldr	w2, [x0, 104]
	str	w2, [x19, 4920]
	ldr	w2, [x0, 108]
	str	w2, [x19, 4924]
	ldr	w2, [x0, 112]
	str	w2, [x19, 4928]
	ldr	w2, [x0, 128]
	str	w2, [x19, 4932]
	str	x1, [x0, 56]
	ldr	x1, [x19, 3000]
.L930:
	ldr	w0, [x1, 64]
	str	w0, [x19, 4988]
	add	x0, x3, 824
	ldr	w2, [x19, 5584]
	ldr	w4, [x1, 68]
	str	w4, [x19, 4992]
	str	w2, [x19, 4856]
	str	wzr, [x19, 4972]
	str	w2, [x19, 5104]
	ldr	w5, [x1, 60]
	ldr	w4, [x1, 2084]
	ldrb	w2, [x3, 888]
	cmp	w5, 1
	bfi	w2, w4, 5, 3
	cset	w4, ne
	bfi	w2, w4, 2, 3
	strb	w2, [x3, 888]
	ldr	w1, [x1, 2068]
	and	w1, w1, 7
	bl	SetAspectRatio
	ldr	w0, [x19, 2356]
	cmp	w0, 1
	beq	.L926
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5564]
	str	w1, [x0, 8]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 4984]
	str	w1, [x0, 152]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 4972]
	str	w1, [x0, 140]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5024]
	str	w1, [x0, 192]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5020]
	str	w1, [x0, 188]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 4988]
	str	w1, [x0, 156]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 4992]
	str	w1, [x0, 160]
	ldr	x1, [x19, 4912]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L932
	ldr	w3, [x19, 4972]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 276]
	cset	w3, ne
	bl	FSP_SetStoreType
.L932:
	ldr	x0, [x19, 3000]
	ldr	x4, [x19, 4912]
	ldr	w1, [x0, 72]
	str	w1, [x19, 5140]
	ldr	w3, [x0, 76]
	str	w3, [x19, 5144]
	ldr	w6, [x0, 80]
	str	w6, [x19, 5148]
	ldr	w5, [x0, 84]
	str	w5, [x19, 5152]
	ldr	w2, [x0, 64]
	sub	w1, w2, w1
	sub	w1, w1, w3
	str	w1, [x19, 4996]
	ldr	w3, [x0, 68]
	sub	w2, w3, w6
	sub	w2, w2, w5
	str	w2, [x19, 5000]
	ldr	w2, [x0, 60]
	str	w2, [x19, 5084]
	ldr	w2, [x0, 88]
	str	w2, [x19, 5088]
	ldr	w0, [x0, 96]
	str	w0, [x19, 5092]
	ldr	w0, [x4, 172]
	str	w0, [x19, 5004]
	ldr	w0, [x4, 176]
	str	w0, [x19, 5008]
	str	w1, [x4, 164]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5000]
	str	w1, [x0, 168]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5004]
	str	w1, [x0, 172]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5008]
	str	w1, [x0, 176]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5088]
	str	w1, [x0, 256]
	ldr	x0, [x19, 4912]
	ldr	w1, [x19, 5092]
	str	w1, [x0, 260]
	str	wzr, [x19, 4864]
.L926:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L939:
	ldr	w4, [x0, 156]
	cbnz	w4, .L927
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L927
	add	x0, x19, 12288
	ldrb	w0, [x0, 448]
	cmp	w0, 1
	bne	.L927
	ldr	x4, [x19, 12768]
	ldr	x0, [x19, 12784]
	cmp	x4, x0
	bls	.L928
	sub	x5, x4, x0
	cmp	x5, 16
	bls	.L928
.L929:
	ldr	w4, [x19, 284]
	sub	w2, w2, w4
	add	x0, x0, x2, sxtw
	str	x0, [x19, 12768]
	b	.L927
.L928:
	cmp	x4, x0
	bcs	.L927
	sub	x4, x0, x4
	cmp	x4, 16
	bls	.L927
	b	.L929
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	3
.LC212:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x26, 5572]
	cmp	w3, 1
	beq	.L942
	cmp	w3, 2
	beq	.L958
	cbz	w3, .L957
	ldr	x2, .LC213
	mov	w0, 1
	ldr	x1, .LC215
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L945:
	ldr	x0, [x26, 3032]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L953
	mov	w0, 1
	str	w0, [x28]
	ldr	x0, [x26, 4912]
	add	x0, x0, 56
	str	x0, [x23, -8]
	.p2align 2
.L953:
	add	w27, w27, 1
	add	x28, x28, 4
	cmp	w27, w22
	add	x23, x23, 136
	bcc	.L955
.L958:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L957:
	mov	w22, 2
.L944:
	ldr	x21, .LC213
	add	x28, x26, 4096
	add	x28, x28, 1524
	add	x23, x26, 3064
	add	x0, x21, 392
	mov	w27, 0
	str	x0, [x29, 104]
	.p2align 2
.L955:
	ldr	w1, [x28]
	cbz	w1, .L945
	ldr	x2, [x23, -8]
	cbnz	x2, .L959
	mov	x3, x23
	mov	w0, 0
	b	.L947
	.p2align 3
.L949:
	ldr	x24, [x3], 8
	cbnz	x24, .L964
.L947:
	add	w0, w0, 1
	cmp	w1, w0
	bne	.L949
	mov	w20, -1
.L948:
	ldr	x0, [x26, 3032]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L950
	ldr	x24, [x26, 4912]
	add	x24, x24, 56
.L946:
	mov	x0, x2
	uxtw	x25, w27
	mov	w19, 0
	lsl	x21, x25, 4
	cbz	x0, .L965
	.p2align 2
.L951:
	add	w19, w19, 1
	add	x0, x21, x25
	cmp	w1, w19
	add	x0, x0, x19, uxtw
	add	x0, x0, 382
	bls	.L953
	ldr	x0, [x26, x0, lsl 3]
	cbnz	x0, .L951
.L965:
	ldr	x1, .LC219
	mov	w4, w19
	ldr	x2, [x29, 104]
	mov	w5, w20
	mov	w3, w27
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x21, x25
	add	x0, x0, x19, uxtw
	add	x0, x0, 382
	str	x24, [x26, x0, lsl 3]
	ldr	w1, [x28]
	b	.L951
	.p2align 3
.L964:
	sxtb	w20, w0
	cmn	w20, #1
	ccmp	x24, xzr, 4, ne
	bne	.L946
	b	.L948
	.p2align 3
.L959:
	mov	x24, x2
	mov	w20, 0
	b	.L946
.L942:
	mov	w22, w3
	b	.L944
.L950:
	ldr	x2, .LC213
	mov	w3, w27
	ldr	x1, .LC217
	mov	w0, 1
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	3
.LC213:
	.xword	.LANCHOR0
	.align	3
.LC215:
	.xword	.LC214
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC219:
	.xword	.LC218
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1029
	ldr	x20, .LC221
	add	x21, x29, 48
	mov	x2, 272
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x20, 96]
	blr	x3
	ldr	w0, [x19, 3384]
	cbz	w0, .L1030
	sub	w3, w0, #1
	mov	w6, 0
	add	x3, x3, 478
	add	x0, x19, 3816
	add	x3, x19, x3, lsl 3
	b	.L970
	.p2align 3
.L969:
	cmp	x0, x3
	beq	.L968
.L970:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L969
	ldr	w2, [x1, 60]
	cbnz	w2, .L969
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L969
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x6, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w6, w6, 1
	str	x1, [x2, 3824]
	bne	.L970
	.p2align 2
.L968:
	ldrb	w8, [x19, 1]
	sub	w7, w6, #1
	cbz	w8, .L971
	ldr	w0, [x19, 3396]
	cbz	w0, .L1031
	sub	w4, w0, #1
	mov	w3, w6
	add	x4, x4, 427
	add	x0, x19, 3408
	add	x4, x19, x4, lsl 3
	b	.L974
	.p2align 3
.L973:
	cmp	x4, x0
	beq	.L1061
.L974:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L973
	ldr	w2, [x1, 72]
	cmp	w2, 1
	bne	.L973
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x3, uxtw 3
	cmp	x4, x0
	sub	x2, x2, #4096
	add	w3, w3, 1
	str	x1, [x2, 3824]
	bne	.L974
	.p2align 2
.L1061:
	sub	w9, w3, w6
.L972:
	ldr	w5, [x19, 3388]
	cbnz	w5, .L1022
	mov	w4, w9
	mov	w11, 0
	b	.L975
	.p2align 3
.L971:
	ldr	w5, [x19, 3388]
	mov	w3, w6
	mov	w9, 0
	cbz	w5, .L1062
.L1022:
	add	x1, x19, 3952
	mov	w0, 0
	b	.L977
	.p2align 3
.L976:
	cmp	w0, w5
	bcs	.L1063
.L977:
	ldr	x2, [x1]
	add	w0, w0, 1
	add	x1, x1, 8
	ldrb	w4, [x2, 1]
	cmp	w4, 1
	bne	.L976
	ldr	w4, [x2, 60]
	cbnz	w4, .L976
	ldr	w4, [x2, 64]
	cmp	w4, 1
	bne	.L976
	add	x4, x29, 320
	add	x2, x2, 56
	add	x4, x4, x3, uxtw 3
	cmp	w0, w5
	sub	x4, x4, #4096
	add	w3, w3, 1
	str	x2, [x4, 3824]
	bcc	.L977
	.p2align 2
.L1063:
	cbz	w8, .L978
	sub	w4, w3, w6
	sub	w11, w4, w9
.L975:
	ldr	w10, [x19, 3380]
	add	w5, w9, w11
	cbz	w10, .L980
.L981:
	add	x1, x19, 4088
	mov	w0, 0
	b	.L984
	.p2align 3
.L983:
	cmp	w0, w10
	bcs	.L1064
.L984:
	ldr	x2, [x1]
	add	w0, w0, 1
	add	x1, x1, 8
	ldrb	w4, [x2, 1]
	cmp	w4, 1
	bne	.L983
	ldr	w4, [x2, 60]
	cmp	w4, 1
	bne	.L983
	ldr	w12, [x2, 64]
	add	x4, x29, 320
	add	x4, x4, x3, uxtw 3
	add	x2, x2, 56
	sub	x4, x4, #4096
	cbnz	w12, .L983
	str	x2, [x4, 3824]
	cmp	w0, w10
	add	w3, w3, 1
	bcc	.L984
	.p2align 2
.L1064:
	sub	w4, w3, w6
	cbnz	w8, .L980
	sub	w4, w4, w11
.L982:
	mov	w0, 0
.L989:
	cbz	w3, .L1065
.L990:
	ldr	w10, [x19, 5572]
	cbnz	w10, .L992
	cbz	w8, .L1066
	add	w12, w6, w9
	cbz	w11, .L1035
	add	x13, x21, 136
	add	w14, w11, w12
	mov	w1, w12
	.p2align 2
.L997:
	add	x2, x29, 320
	add	x2, x2, x1, uxtw 3
	add	w1, w1, 1
	sub	x2, x2, #4096
	cmp	w14, w1
	ldr	x2, [x2, 3824]
	str	x2, [x13], 8
	bne	.L997
	mov	w1, w11
.L996:
	cbz	w0, .L1036
	add	w2, w11, w4
	add	w0, w0, w1
	add	w12, w2, w12
	.p2align 2
.L999:
	add	x2, x29, 320
	add	x13, x29, 320
	add	x2, x2, x12, uxtw 3
	add	x13, x13, x1, uxtw 3
	sub	x2, x2, #4096
	add	w1, w1, 1
	cmp	w0, w1
	add	w12, w12, 1
	ldr	x2, [x2, 3824]
	str	x2, [x13, -136]
	bne	.L999
.L998:
	mov	w1, w0
	cbz	w6, .L1002
.L1024:
	mov	x2, 0
	.p2align 2
.L1001:
	add	x1, x29, 320
	ldr	x13, [x21, x2, lsl 3]
	add	x12, x1, x0, uxtw 3
	add	x2, x2, 1
	cmp	w6, w2
	add	w1, w0, 1
	mov	w0, w1
	str	x13, [x12, -136]
	bhi	.L1001
	cbnz	w8, .L1002
.L1025:
	cbz	w4, .L1004
	add	w7, w11, w7
	add	w4, w4, w1
	mov	w2, w1
	.p2align 2
.L1008:
	add	w5, w2, 1
	add	x0, x29, 320
	add	x6, x0, x2, uxtw 3
	sub	w0, w5, w1
	add	w0, w0, w7
	mov	w2, w5
	cmp	w5, w4
	add	x5, x29, 320
	add	x0, x5, x0, lsl 3
	sub	x0, x0, #4096
	ldr	x0, [x0, 3824]
	str	x0, [x6, -136]
	bne	.L1008
.L1004:
	ldr	w5, [x19, 5628]
	ldr	w7, [x19, 5632]
	str	w5, [x19, 5620]
	str	w7, [x19, 5624]
	cbnz	w5, .L1028
	.p2align 2
.L1026:
	cbz	w7, .L1014
	add	x0, x19, 4096
	add	x4, x19, 3192
	add	x2, x0, 2684
	mov	w1, 0
	ldrb	w6, [x0, 2553]
	.p2align 2
.L1017:
	cbz	w6, .L1015
	ldr	w0, [x2]
.L1016:
	add	x8, x29, 320
	add	w1, w1, 1
	add	x0, x8, x0, uxtw 3
	cmp	w7, w1
	add	x2, x2, 4
	ldr	x0, [x0, -136]
	str	x0, [x4], 8
	bne	.L1017
	mov	w0, w5
.L1013:
	cmp	w0, 16
	bhi	.L1038
	.p2align 2
.L1019:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 3056]
	add	w0, w0, 1
	cmp	w0, 16
	str	x2, [x1, 3056]
	bls	.L1019
.L1038:
	cmp	w7, 16
	mov	w0, w7
	bhi	.L1020
	.p2align 2
.L1021:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 3192]
	add	w0, w0, 1
	cmp	w0, 17
	str	x2, [x1, 3192]
	bne	.L1021
.L1020:
	mov	w0, 0
.L1059:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L980:
	ldr	w0, [x19, 3400]
	sub	w4, w4, w11
	sub	w4, w4, w9
	cbz	w0, .L982
	sub	w10, w0, #1
	add	x0, x19, 3544
	add	x10, x10, 444
	add	x10, x19, x10, lsl 3
	b	.L988
	.p2align 3
.L987:
	cmp	x0, x10
	beq	.L1067
.L988:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L987
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x3, uxtw 3
	cmp	x0, x10
	sub	x2, x2, #4096
	add	w3, w3, 1
	str	x1, [x2, 3824]
	bne	.L988
.L1067:
	sub	w0, w3, w6
	sub	w0, w0, w11
	sub	w0, w0, w9
	sub	w0, w0, w4
	cbnz	w3, .L990
.L1065:
	ldr	x3, [x20, 96]
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 3056
	str	wzr, [x19, 5620]
	str	wzr, [x19, 5624]
	blr	x3
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L1020
	ldr	x1, [x19, 4912]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x19, 5620]
	add	x1, x1, 56
	str	x1, [x19, 3056]
	b	.L1059
	.p2align 3
.L978:
	sub	w11, w3, w6
	add	w5, w9, w11
.L1023:
	ldr	w10, [x19, 3380]
	cbnz	w10, .L981
	mov	w4, 0
	mov	w0, 0
	b	.L989
	.p2align 3
.L992:
	ldr	w5, [x19, 5628]
	ldr	w7, [x19, 5632]
	str	w5, [x19, 5620]
	str	w7, [x19, 5624]
	cbz	w5, .L1009
.L1028:
	add	x1, x19, 4096
	add	x4, x19, 3056
	add	x2, x1, 2556
	mov	w0, 0
	ldrb	w6, [x1, 2552]
	.p2align 2
.L1012:
	cbz	w6, .L1010
	ldr	w1, [x2]
.L1011:
	add	x8, x29, 320
	add	w0, w0, 1
	add	x1, x8, x1, uxtw 3
	cmp	w0, w5
	sub	x1, x1, #4096
	add	x2, x2, 4
	ldr	x1, [x1, 3824]
	str	x1, [x4], 8
	bne	.L1012
	cbnz	w10, .L1013
	b	.L1026
	.p2align 3
.L1010:
	udiv	w1, w0, w3
	msub	w1, w1, w3, w0
	b	.L1011
	.p2align 3
.L1015:
	udiv	w0, w1, w3
	msub	w0, w0, w3, w1
	b	.L1016
	.p2align 3
.L1066:
	mov	w0, 0
	cbz	w11, .L995
	add	x2, x21, 136
	add	w12, w11, w6
	mov	w0, w6
	.p2align 2
.L1000:
	add	x1, x29, 320
	add	x1, x1, x0, uxtw 3
	add	w0, w0, 1
	sub	x1, x1, #4096
	cmp	w12, w0
	ldr	x1, [x1, 3824]
	str	x1, [x2], 8
	bne	.L1000
	mov	w0, w11
.L995:
	mov	w1, w0
	cbnz	w6, .L1024
	b	.L1025
	.p2align 3
.L1002:
	cbz	w4, .L1037
	add	w5, w6, w5
	add	w4, w4, w1
	.p2align 2
.L1006:
	add	x0, x29, 320
	add	x2, x29, 320
	add	x0, x0, x5, uxtw 3
	add	x2, x2, x1, uxtw 3
	sub	x0, x0, #4096
	add	w1, w1, 1
	cmp	w4, w1
	add	w5, w5, 1
	ldr	x0, [x0, 3824]
	str	x0, [x2, -136]
	bne	.L1006
.L1005:
	cbz	w9, .L1004
	add	w9, w4, w9
	mov	w1, w4
	.p2align 2
.L1007:
	add	w2, w1, 1
	add	x0, x29, 320
	add	x5, x0, x1, uxtw 3
	sub	w0, w2, w4
	add	w0, w0, w7
	mov	w1, w2
	cmp	w2, w9
	add	x2, x29, 320
	add	x0, x2, x0, lsl 3
	sub	x0, x0, #4096
	ldr	x0, [x0, 3824]
	str	x0, [x5, -136]
	bne	.L1007
	ldr	w5, [x19, 5628]
	ldr	w7, [x19, 5632]
	str	w5, [x19, 5620]
	str	w7, [x19, 5624]
	cbnz	w5, .L1028
	b	.L1026
.L1014:
	ldr	x3, [x20, 104]
	mov	x2, 136
	add	x1, x19, 3056
	add	x0, x19, 3192
	blr	x3
	ldr	w7, [x19, 5620]
	str	w7, [x19, 5624]
	mov	w0, w7
	b	.L1013
.L1030:
	mov	w6, 0
	b	.L968
.L1062:
	mov	w11, 0
	mov	w9, 0
	b	.L1023
.L1031:
	mov	w3, w6
	mov	w9, 0
	b	.L972
.L1009:
	mov	w0, 0
	b	.L1019
.L1029:
	mov	w0, -1
	b	.L1059
.L1037:
	mov	w4, w1
	b	.L1005
.L1036:
	mov	w0, w1
	b	.L998
.L1035:
	mov	w1, 0
	b	.L996
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	3
.LC221:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5572]
	cmp	w0, 2
	beq	.L1074
	mov	x0, x19
	bl	HEVC_InitListX
	cbnz	w0, .L1075
	mov	x0, x19
	bl	HEVC_RepairList
	mov	w1, 0
	cbnz	w0, .L1076
.L1070:
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1074:
	str	wzr, [x19, 5620]
	mov	w1, 0
	str	wzr, [x19, 5624]
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1075:
	ldr	x1, .LC223
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L1070
.L1076:
	ldr	x1, .LC225
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L1070
	.size	HEVC_DecList, .-HEVC_DecList
	.align	3
.LC223:
	.xword	.LC222
	.align	3
.LC225:
	.xword	.LC224
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ArrangeMem
	.type	HEVC_ArrangeMem, %function
HEVC_ArrangeMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3000]
	mov	w1, 8160
	ldr	w20, [x0, 128]
	ldr	w21, [x0, 192]
	ldr	w0, [x0, 188]
	lsl	w21, w21, w20
	sub	w2, w21, #32
	lsl	w20, w0, w20
	sub	w0, w20, #32
	cmp	w2, w1
	ccmp	w0, w1, 2, ls
	bhi	.L1078
	ldr	x3, .LC226
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 3032]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L1087
	ldrsb	w2, [x19, 3368]
	strb	w2, [x29, 57]
.L1083:
	ldr	w0, [x19, 276]
	add	x1, x29, 56
	strb	w2, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L1088
	ldr	x1, [x19, 3032]
	add	x3, x29, 52
	ldr	w0, [x19, 276]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
.L1085:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1087:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 57]
	b	.L1083
	.p2align 3
.L1078:
	ldr	x2, .LC227
	mov	w4, w21
	ldr	x1, .LC229
	mov	w3, w20
	add	x2, x2, 408
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, -20
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1088:
	ldr	x2, .LC227
	mov	w0, 1
	ldr	x1, .LC231
	add	x2, x2, 408
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1085
	.size	HEVC_ArrangeMem, .-HEVC_ArrangeMem
	.align	3
.LC226:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC227:
	.xword	.LANCHOR0
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC231:
	.xword	.LC230
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x19, x20, uxtw 3
	ldr	x1, [x0, 3680]
	ldr	w4, [x1, 32]
	cmp	w4, 1
	bhi	.L1092
	ldr	w0, [x1, 24]
	cmp	w0, 15
	bhi	.L1089
	sxtw	x2, w4
	uxtw	x0, w0
	lsl	x3, x2, 5
	mov	w6, 70
	add	x3, x3, x2, lsl 3
	mov	w5, 16
	smaddl	x4, w4, w6, x0
	add	x2, x19, x3, lsl 3
	sub	x2, x2, x3
	add	x4, x19, x4, lsl 2
	add	x0, x2, x0
	add	x0, x0, 12288
	str	wzr, [x4, 14180]
	str	wzr, [x4, 14244]
	str	wzr, [x4, 14308]
	str	wzr, [x4, 14372]
	strb	wzr, [x0, 2148]
	ldr	w0, [x1, 20]
	add	x19, x19, x0, lsl 2
	str	wzr, [x19, 2156]
	str	w5, [x1, 24]
	ldr	w0, [x2, 14176]
	sub	w0, w0, #1
	str	w0, [x2, 14176]
.L1089:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1092:
	ldr	x2, .LC232
	mov	w3, w20
	ldr	x1, .LC234
	mov	w0, 1
	add	x2, x2, 424
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	3
.LC232:
	.xword	.LANCHOR0
	.align	3
.LC234:
	.xword	.LC233
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w1, [x20, 3372]
	cbnz	w1, .L1098
	b	.L1093
	.p2align 3
.L1095:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1093
.L1098:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 3680]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L1095
	mov	w1, w19
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	ldr	w1, [x20, 3372]
	cmp	w1, w19
	bhi	.L1098
.L1093:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	w21, 1
	mov	w26, 0
	bl	_mcount
	ldr	w2, [x23, 5588]
	mov	w5, 5036
	ldr	x1, [x23, 2960]
	mov	w4, 12668
	ldr	x0, [x23, 2952]
	ldr	w3, [x23, 3372]
	smaddl	x1, w2, w5, x1
	ldr	w1, [x1, 32]
	smaddl	x0, w1, w4, x0
	ldr	w24, [x0, 116]
	lsl	w24, w21, w24
	cbz	w3, .L1100
	add	x19, x23, 4096
	mov	w22, w21
	add	x19, x19, 2388
	b	.L1131
	.p2align 3
.L1103:
	add	w26, w26, 1
	cmp	w3, w26
	bls	.L1100
.L1131:
	add	x25, x23, x26, sxtw 3
	ldr	w0, [x23, 5584]
	ldr	x1, [x25, 3680]
	ldr	w2, [x1, 32]
	cmp	w2, w0
	bne	.L1103
	ldp	w3, w0, [x19]
	ldr	w2, [x19, 8]
	add	w0, w3, w0
	cmp	w0, w2
	mov	w20, w0
	bcs	.L1142
	ldr	w0, [x1, 8]
	mov	w4, 0
	.p2align 2
.L1111:
	add	x2, x23, x20, sxtw 2
	ldr	w3, [x2, 5640]
	cbz	w3, .L1106
	ldr	w3, [x1, 60]
	cbz	w3, .L1107
	ldr	w3, [x2, 6584]
	cmp	w3, w0
	beq	.L1141
.L1107:
	cbnz	w4, .L1139
	ldrb	w4, [x1, 1]
	ldr	w3, [x2, 6584]
	mov	w2, w0
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	beq	.L1143
.L1122:
	mov	w2, w0
	mov	w4, 0
.L1110:
	ldr	w3, [x19, 8]
	add	w20, w20, 1
	mov	w0, w2
	cmp	w3, w20
	bhi	.L1111
	ldp	w3, w0, [x19]
	add	w0, w3, w0
.L1105:
	ldr	w5, [x23, 5564]
	cbz	w0, .L1113
	mov	w20, 0
	.p2align 2
.L1115:
	ldr	w0, [x1, 60]
	add	x3, x19, x20, sxtw 2
	add	w20, w20, 1
	cbnz	w0, .L1114
	ldr	w0, [x3, 32]
	add	w0, w5, w0
	cmp	w0, w2
	beq	.L1144
.L1114:
	ldp	w3, w0, [x19]
	add	w0, w3, w0
	cmp	w0, w20
	bhi	.L1115
.L1113:
	cmp	w4, wzr
	ccmp	w2, w5, 4, eq
	beq	.L1140
	strb	wzr, [x1, 1]
	ldr	x0, [x25, 3680]
	str	wzr, [x0, 60]
	ldr	x0, [x25, 3680]
	str	wzr, [x0, 72]
	ldr	x0, [x25, 3680]
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1140
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
.L1140:
	ldr	w3, [x23, 3372]
	add	w26, w26, 1
	cmp	w3, w26
	bhi	.L1131
.L1100:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1106:
	ldr	w3, [x1, 60]
	cbz	w3, .L1109
	sdiv	w3, w0, w24
	ldr	w6, [x2, 6584]
	sdiv	w5, w6, w24
	msub	w3, w3, w24, w0
	msub	w5, w5, w24, w6
	cmp	w3, w5
	bne	.L1109
.L1141:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x25, 3680]
	str	wzr, [x0, 72]
	ldr	x0, [x25, 3680]
	str	w21, [x0, 48]
	ldr	x0, [x25, 3680]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
	ldr	x1, [x25, 3680]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L1110
	.p2align 3
.L1109:
	cbnz	w4, .L1139
	ldr	w4, [x2, 6584]
	sdiv	w2, w0, w24
	sdiv	w3, w4, w24
	msub	w2, w2, w24, w0
	msub	w3, w3, w24, w4
	ldrb	w4, [x1, 1]
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	bne	.L1122
.L1143:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x25, 3680]
	str	w21, [x0, 60]
	ldr	x0, [x25, 3680]
	str	wzr, [x0, 72]
	ldr	x0, [x25, 3680]
	str	w21, [x0, 48]
	ldr	x0, [x25, 3680]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
	ldr	x1, [x25, 3680]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L1110
	.p2align 3
.L1139:
	mov	w2, w0
	b	.L1110
	.p2align 3
.L1144:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x25, 3680]
	str	wzr, [x0, 72]
	ldr	x0, [x25, 3680]
	str	w21, [x0, 48]
	ldr	x1, [x25, 3680]
	ldr	w0, [x23, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x25, 3680]
	mov	w4, 1
	ldr	w5, [x23, 5564]
	ldr	w2, [x1, 8]
	b	.L1114
.L1142:
	mov	w4, 0
	ldr	w2, [x1, 8]
	b	.L1105
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 5580]
	sub	w0, w0, #19
	cmp	w0, 2
	bls	.L1147
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.15
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1147:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L1149
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.16
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1149:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 12288
	add	x5, x19, 28672
	add	x2, x2, 2448
	add	x5, x5, 464
	mov	w0, 0
	.p2align 2
.L1156:
	ldr	w1, [x2, 48]
	cbnz	w1, .L1152
	cbz	x2, .L1153
	ldr	w4, [x19, 3372]
	cbz	w4, .L1153
	ldr	x1, [x19, 3680]
	cmp	x1, x2
	beq	.L1152
	sub	w4, w4, #1
	mov	x1, x19
	add	x4, x19, x4, lsl 3
	b	.L1154
	.p2align 3
.L1155:
	ldr	x3, [x1, 3680]
	cmp	x3, x2
	beq	.L1152
.L1154:
	cmp	x4, x1
	add	x1, x1, 8
	bne	.L1155
.L1153:
	add	w0, w0, 1
.L1152:
	add	x2, x2, 720
	cmp	x2, x5
	bne	.L1156
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 6484]
	cbz	w1, .L1186
	add	x24, x20, 4096
	mov	w22, 0
	mov	w21, 0
	add	x23, x24, 2388
	mov	w26, 1
	mov	w25, 1
	.p2align 2
.L1172:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1168
	add	x0, x0, 8
	ldr	w5, [x20, 3372]
	ldr	w4, [x20, 5564]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L1168
	add	x1, x20, 3680
	mov	w0, 0
	b	.L1171
	.p2align 3
.L1169:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1168
.L1171:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L1169
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 5584]
	cmp	w6, w3
	bne	.L1169
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 3680]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L1214
.L1170:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 3680]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 3680]
	str	x1, [x0, 3816]
	.p2align 2
.L1168:
	ldr	w1, [x23]
	add	w21, w21, 1
	cmp	w1, w21
	bhi	.L1172
.L1167:
	ldr	w0, [x20, 3368]
	str	w22, [x20, 3384]
	cmp	w0, w22
	bls	.L1177
	.p2align 2
.L1201:
	add	x2, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w22, w0
	str	xzr, [x2, 3816]
	bne	.L1201
.L1177:
	add	x23, x24, 2388
	mov	w22, 0
	mov	w26, 1
	mov	w25, 1
	ldr	w24, [x23, 4]
	add	w24, w1, w24
	cmp	w24, w21
	bls	.L1175
	.p2align 2
.L1200:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1178
	add	x0, x0, 8
	ldr	w5, [x20, 3372]
	ldr	w4, [x20, 5564]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L1178
	add	x1, x20, 3680
	mov	w0, 0
	b	.L1181
	.p2align 3
.L1179:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1178
.L1181:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L1179
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 5584]
	cmp	w6, w3
	bne	.L1179
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 3680]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L1215
.L1180:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 3680]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 3680]
	str	x1, [x0, 3952]
	.p2align 2
.L1178:
	add	w21, w21, 1
	cmp	w24, w21
	bhi	.L1200
	ldr	w0, [x20, 3368]
.L1175:
	cmp	w0, w22
	str	w22, [x20, 3388]
	bls	.L1166
	.p2align 2
.L1199:
	add	x1, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w0, w22
	str	xzr, [x1, 3952]
	bne	.L1199
.L1166:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1214:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3680]
	b	.L1170
.L1215:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3680]
	b	.L1180
.L1186:
	mov	w22, 0
	mov	w21, 0
	add	x24, x20, 4096
	b	.L1167
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 5588]
	mov	w2, 5036
	ldr	x0, [x19, 2960]
	mov	w5, 12668
	ldr	w6, [x19, 6484]
	add	x1, x19, 4096
	ldr	w9, [x19, 6492]
	add	x1, x1, 2388
	smaddl	x2, w3, w2, x0
	ldr	w0, [x19, 6488]
	sub	w9, w9, #1
	ldr	x4, [x19, 2952]
	mov	w3, 1
	ldr	w2, [x2, 32]
	add	w0, w6, w0
	sub	w0, w0, #1
	cmp	w9, w0
	smaddl	x0, w2, w5, x4
	ldr	w0, [x0, 116]
	lsl	w0, w3, w0
	ble	.L1226
	mov	w10, 0
	mov	x11, x1
	sub	w7, w0, #1
	mov	w13, w3
	mov	w12, w3
	.p2align 2
.L1223:
	sxtw	x0, w9
	add	x1, x11, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1218
	add	x0, x19, x0, lsl 2
	ldr	w8, [x19, 3372]
	ldr	w6, [x0, 5640]
	ldr	w5, [x0, 6584]
	uxtb	w6, w6
	and	w0, w5, w7
	cmp	w6, wzr
	csel	w5, w0, w5, eq
	cmp	w8, wzr
	ble	.L1218
	add	x2, x19, 3680
	mov	w1, 0
	b	.L1222
	.p2align 3
.L1221:
	add	w1, w1, 1
	cmp	w1, w8
	beq	.L1218
.L1222:
	ldr	x3, [x2]
	cmp	w6, wzr
	add	x2, x2, 8
	ldr	w0, [x3, 8]
	and	w4, w0, w7
	csel	w0, w4, w0, eq
	cmp	w5, w0
	bne	.L1221
	ldr	w4, [x3, 32]
	ldr	w0, [x19, 5584]
	cmp	w4, w0
	bne	.L1221
	add	x1, x19, x1, sxtw 3
	strb	w13, [x3, 1]
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	ldr	x2, [x1, 3680]
	str	wzr, [x2, 64]
	ldr	x2, [x1, 3680]
	str	w12, [x2, 60]
	ldr	x1, [x1, 3680]
	str	x1, [x0, 4088]
	.p2align 2
.L1218:
	ldp	w1, w0, [x11]
	sub	w9, w9, #1
	add	w0, w1, w0
	sub	w0, w0, #1
	cmp	w0, w9
	blt	.L1223
	mov	w0, w10
.L1217:
	ldr	w1, [x19, 3368]
	str	w0, [x19, 3380]
	cmp	w1, w10
	ble	.L1216
	.p2align 2
.L1229:
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	cmp	w10, w1
	str	xzr, [x0, 4088]
	bne	.L1229
.L1216:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1226:
	mov	w0, 0
	mov	w10, 0
	b	.L1217
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x23, x1
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1253
	ldr	w20, [x21, 4856]
	uxtw	x22, w20
	lsl	x0, x22, 5
	add	x0, x0, x22, lsl 3
	add	x1, x21, x0, lsl 3
	sub	x0, x1, x0
	ldr	w2, [x0, 14172]
	cbz	w2, .L1237
	ldr	w0, [x0, 14180]
	cbz	w0, .L1254
	mov	w0, 280
	mov	x1, 14184
	mov	w19, 0
	umaddl	x0, w20, w0, x1
	add	x0, x21, x0
	b	.L1240
	.p2align 3
.L1243:
	ldr	w1, [x0], 4
	cbz	w1, .L1238
.L1240:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L1243
.L1237:
	ldr	x1, .LC241
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1250:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1254:
	mov	w19, 0
	.p2align 2
.L1238:
	ldr	w0, [x21, 276]
	ldr	w1, [x23, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1241
	ldr	x1, [x0, 32]
	cbz	x1, .L1241
	uxtw	x24, w19
	mov	w3, 70
	mov	w2, 1
	lsl	x1, x22, 5
	umaddl	x20, w20, w3, x24
	add	x22, x1, x22, lsl 3
	mov	w3, w19
	add	x20, x21, x20, lsl 2
	add	x1, x21, x22, lsl 3
	sub	x22, x1, x22
	ldr	x1, .LC238
	add	x24, x22, x24
	str	w2, [x20, 14180]
	add	x24, x24, 12288
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 14244]
	ldr	w0, [x23, 8]
	str	w0, [x20, 14308]
	ldr	w0, [x22, 14176]
	add	w0, w0, w2
	str	w0, [x22, 14176]
	mov	w0, 13
	ldr	w2, [x23, 236]
	bl	dprint_vfmw
	str	w19, [x23, 24]
	ldr	w1, [x23, 32]
	mov	w0, 0
	str	w1, [x20, 14372]
	strb	wzr, [x24, 2148]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1241:
	ldrb	w4, [x23, 1]
	mov	x5, x0
	ldr	x1, .LC239
	mov	x6, 0
	ldr	w3, [x23, 8]
	mov	w0, 0
	ldr	w2, [x23, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1250
.L1253:
	ldr	x2, .LC235
	mov	w3, 11486
	ldr	x1, .LC236
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1250
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	3
.LC235:
	.xword	.LC2
	.align	3
.LC236:
	.xword	.LC4
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC239:
	.xword	.LC6
	.align	3
.LC241:
	.xword	.LC240
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	cbz	x0, .L1256
	ldrsb	w4, [x0, 1]
	cmp	w4, 3
	ccmp	w4, wzr, 4, ne
	beq	.L1276
	ldr	w0, [x19, 52]
	cmp	w0, 1
	beq	.L1262
	ldr	w4, [x19, 48]
	ldrb	w5, [x19]
	cbz	w4, .L1261
	cmp	w5, 1
	mov	w0, 0
	beq	.L1261
.L1270:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1276:
	ldr	x2, .LC242
	mov	w0, 13
	ldr	x1, .LC244
	ldr	w3, [x19, 28]
	add	x2, x2, 448
	bl	dprint_vfmw
.L1258:
	ldr	w0, [x19, 52]
	cmp	w0, 1
	bne	.L1277
.L1262:
	mov	w1, 1
	mov	w0, 2
	strb	w1, [x19, 2]
	str	w0, [x19, 52]
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1256:
	ldr	x1, .LC246
	mov	x2, x19
	ldr	w3, [x19, 8]
	mov	w0, 1
	ldr	w5, [x19, 28]
	ldr	w4, [x19, 52]
	bl	dprint_vfmw
	b	.L1258
.L1277:
	ldr	x2, .LC242
	mov	w0, 1
	ldr	x1, .LC248
	ldr	w3, [x19, 8]
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -3
	b	.L1270
	.p2align 3
.L1261:
	ldr	x2, .LC242
	mov	x3, x19
	ldr	x1, .LC250
	mov	w0, 1
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1270
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	3
.LC242:
	.xword	.LANCHOR0
	.align	3
.LC244:
	.xword	.LC243
	.align	3
.LC246:
	.xword	.LC245
	.align	3
.LC248:
	.xword	.LC247
	.align	3
.LC250:
	.xword	.LC249
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w23, [x21, 12]
	ldr	x0, [x21, 672]
	cmn	x0, #1
	beq	.L1280
	ldr	w1, [x20, 3372]
	cbz	w1, .L1280
	mov	w25, -1
	mov	x24, -2
	mov	w19, 0
	b	.L1283
	.p2align 3
.L1318:
	ldr	x0, [x22, 3680]
	ldr	w1, [x20, 3372]
	ldr	x0, [x0, 672]
	cmp	x0, x24
	bcs	.L1282
	mov	w25, w19
	mov	x24, x0
.L1282:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1320
.L1283:
	add	x22, x20, x19, sxtw 3
	ldr	x0, [x22, 3680]
	cbz	x0, .L1282
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	cbz	x0, .L1319
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	bne	.L1318
.L1319:
	ldr	w1, [x20, 3372]
	add	w19, w19, 1
	cmp	w1, w19
	bhi	.L1283
.L1320:
	cmn	w25, #1
	beq	.L1280
	ldr	x1, [x21, 672]
	cmp	x1, x24
	bhi	.L1321
.L1280:
	ldrb	w0, [x21, 153]
	ldrb	w1, [x21, 152]
	and	w0, w0, -64
	strb	w0, [x21, 153]
	and	w1, w1, -4
	strb	w1, [x21, 152]
	ldr	w2, [x20, 144]
	str	w2, [x21, 196]
	ldr	x2, [x20, 2992]
	ldrh	w2, [x2, 124]
	cmp	w2, 1
	beq	.L1291
	cmp	w2, 257
	bne	.L1292
	ldr	w2, [x20, 4236]
	cmp	w2, 1
	cset	w4, ne
.L1284:
	ldr	x3, [x20, 3000]
	mov	w2, 3
	ldrb	w3, [x3, 2066]
	cbz	w3, .L1285
	ldr	w3, [x21, 40]
	mov	w2, 1
	cmp	w3, w2
	ccmp	w3, 11, 4, ne
	cset	w4, eq
	cbz	w4, .L1322
.L1286:
	ldr	w3, [x21, 44]
	cmp	w3, wzr
	cset	w4, eq
.L1285:
	mov	w3, 2
	ldrb	w6, [x21, 3]
	bfi	w0, w3, 4, 2
	ldrb	w3, [x21, 154]
	bfi	w0, w2, 2, 2
	ldrb	w5, [x21, 4]
	ldr	w2, [x21, 48]
	bfi	w0, w4, 0, 2
	bfi	w1, w23, 0, 2
	bfi	w3, w6, 1, 1
	strb	w0, [x21, 153]
	strb	w1, [x21, 152]
	strb	w3, [x21, 154]
	str	w5, [x21, 208]
	cbz	w2, .L1287
	ldr	w0, [x21, 16]
	str	w0, [x21, 240]
.L1287:
	ldr	x0, [x20, 3032]
	ldr	w1, [x21, 28]
	ldr	w0, [x0, 636]
	str	w0, [x21, 212]
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 640]
	str	w0, [x21, 216]
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 644]
	str	w0, [x21, 220]
	ldr	w0, [x20, 276]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1278
	ldr	x3, .LC253
	mov	x2, 632
	add	x1, x21, 88
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 16
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 1
	ldr	w2, [x21, 56]
	strb	w1, [x19, 291]
	cmp	w2, wzr
	strb	w1, [x19, 289]
	csel	w0, w0, wzr, ne
	strb	w0, [x19, 284]
	ldr	w0, [x21, 68]
	str	w0, [x19, 236]
.L1278:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1321:
	ldr	w0, [x20, 276]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L1280
	ldr	x1, .LC252
	mov	x3, x24
	ldr	x2, [x21, 672]
	mov	w0, 29
	add	x25, x20, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x25, 3680]
	ldr	x1, [x21, 672]
	str	x1, [x0, 672]
	str	x24, [x21, 672]
	b	.L1280
	.p2align 3
.L1322:
	mov	w4, 2
	and	w3, w3, -9
	mov	w2, 3
	cmp	w3, w4
	csel	w2, w2, w4, ne
	b	.L1286
	.p2align 3
.L1291:
	mov	w4, 0
	b	.L1284
	.p2align 3
.L1292:
	mov	w4, 1
	b	.L1284
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	3
.LC252:
	.xword	.LC251
	.align	3
.LC253:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	uxtw	x19, w1
	bl	_mcount
	cmp	w19, 19
	bhi	.L1325
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x2, x0, 4
	sub	x0, x2, x0
	add	x0, x20, x0, lsl 4
	add	x0, x0, 12288
	ldrb	w0, [x0, 2449]
	cmp	w0, wzr
	cset	w0, ne
.L1324:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1325:
	mov	w0, -1
	b	.L1324
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	w0, [x21, 276]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L1331
	ldrsb	w1, [x0, 1]
	add	x19, x0, 592
	add	x20, x0, 624
	cbz	w1, .L1337
.L1334:
	ldr	x2, [x19]
	mov	x1, x2
	cbz	x2, .L1329
	ldr	w0, [x21, 276]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1329:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L1334
	ldr	w0, [x21, 276]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L1327:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1337:
	ldr	x1, .LC255
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1327
.L1331:
	mov	w0, -1
	b	.L1327
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	3
.LC255:
	.xword	.LC254
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1MasteringDisplayInfo
	.type	HEVC_GetSLHDR1MasteringDisplayInfo, %function
HEVC_GetSLHDR1MasteringDisplayInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x1, x19, 568
	mov	w2, 14999
	ldr	w0, [x1, 4]
	cmp	w0, w2
	bhi	.L1342
	sub	w2, w0, #8192
	mov	w3, 4749
	sub	w2, w2, #308
	cmp	w2, w3
	bhi	.L1341
	mov	w0, 1
	strb	w0, [x20, 3]
	b	.L1340
	.p2align 3
.L1341:
	sub	w0, w0, #12288
	sub	w0, w0, #962
	cmp	w0, 1749
	bls	.L1345
.L1342:
	strb	wzr, [x20, 3]
.L1340:
	ldr	w2, [x1, 36]
	mov	w0, 56963
	movk	w0, 0x431b, lsl 16
	mov	w3, 10000
	add	w2, w2, 249856
	mov	w5, 2063
	add	w2, w2, 144
	movk	w5, 0x5f6, lsl 16
	mov	w4, w3
	umull	x2, w2, w0
	lsr	x2, x2, 32
	lsr	w2, w2, 17
	lsl	w0, w2, 3
	sub	w0, w0, w2
	add	w2, w2, w0, lsl 3
	sub	w0, w2, w0
	cmp	w0, w3
	csel	w0, w0, w3, ls
	strh	w0, [x20, 4]
	ldr	w0, [x1, 40]
	cmp	w0, w5
	bhi	.L1343
	mov	w1, 5977
	movk	w1, 0xd1b7, lsl 16
	umull	x0, w0, w1
	ubfx	x4, x0, 45, 16
.L1343:
	strh	w4, [x20, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1345:
	mov	w0, 2
	strb	w0, [x20, 3]
	b	.L1340
	.size	HEVC_GetSLHDR1MasteringDisplayInfo, .-HEVC_GetSLHDR1MasteringDisplayInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintSLHDR1Info
	.type	HEVC_PrintSLHDR1Info, %function
HEVC_PrintSLHDR1Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x21]
	mov	w0, 32
	ldr	x1, .LC257
	bl	dprint_vfmw
	ldrb	w2, [x21, 1]
	mov	w0, 32
	ldr	x1, .LC259
	bl	dprint_vfmw
	ldrb	w2, [x21, 2]
	mov	w0, 32
	ldr	x1, .LC261
	bl	dprint_vfmw
	ldrb	w2, [x21, 3]
	mov	w0, 32
	ldr	x1, .LC263
	bl	dprint_vfmw
	ldrh	w2, [x21, 4]
	mov	w0, 32
	ldr	x1, .LC265
	bl	dprint_vfmw
	ldrh	w2, [x21, 6]
	mov	w0, 32
	ldr	x1, .LC267
	bl	dprint_vfmw
	ldrb	w2, [x21, 8]
	mov	w0, 32
	ldr	x1, .LC269
	bl	dprint_vfmw
	ldrb	w2, [x21, 9]
	mov	w0, 32
	ldr	x1, .LC271
	bl	dprint_vfmw
	ldrb	w0, [x21, 1]
	ldrb	w2, [x21, 10]
	cbnz	w0, .L1347
	ldr	x1, .LC273
	add	x19, x21, 10
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w2, [x19, 1]
	mov	w0, 32
	ldr	x1, .LC275
	bl	dprint_vfmw
	ldrb	w2, [x19, 2]
	mov	w0, 32
	ldr	x1, .LC277
	bl	dprint_vfmw
	ldrb	w2, [x19, 3]
	mov	w0, 32
	ldr	x1, .LC279
	bl	dprint_vfmw
	ldrb	w2, [x19, 4]
	mov	w0, 32
	ldr	x1, .LC281
	bl	dprint_vfmw
	ldrb	w2, [x19, 5]
	mov	w0, 32
	ldr	x1, .LC283
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cbz	w0, .L1352
	ldr	x23, .LC287
	mov	w20, 0
	ldr	x22, .LC289
	.p2align 2
.L1351:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 6]
	bl	dprint_vfmw
	ldrb	w2, [x21, 17]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cmp	w0, w20
	bhi	.L1351
.L1352:
	ldrb	w2, [x19, 28]
	mov	w0, 32
	ldr	x1, .LC285
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cbz	w0, .L1353
	ldr	x23, .LC291
	mov	w20, 0
	ldr	x22, .LC293
	.p2align 2
.L1354:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 29]
	bl	dprint_vfmw
	ldrb	w2, [x21, 36]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cmp	w0, w20
	bhi	.L1354
.L1353:
	ldr	x1, .LC311
	mov	x2, 290
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1347:
	ldr	x1, .LC295
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21, 10]
	cbz	w0, .L1365
	ldr	x24, .LC299
	mov	w20, 0
	ldr	x23, .LC301
	add	x19, x21, 10
	.p2align 2
.L1358:
	add	x22, x21, x20, uxtw 1
	mov	w2, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w3, [x22, 12]
	bl	dprint_vfmw
	ldrh	w3, [x22, 80]
	mov	w2, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19]
	cmp	w0, w20
	bhi	.L1358
.L1359:
	ldrb	w2, [x19, 138]
	mov	w0, 32
	ldr	x1, .LC297
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cbz	w0, .L1357
	ldr	x24, .LC307
	mov	w20, 0
	ldr	x23, .LC309
	.p2align 2
.L1360:
	add	x22, x21, x20, uxtw 1
	mov	w3, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w2, [x22, 150]
	bl	dprint_vfmw
	ldrh	w2, [x22, 218]
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cmp	w0, w20
	bhi	.L1360
.L1357:
	ldrh	w2, [x19, 276]
	mov	w0, 32
	ldr	x1, .LC303
	bl	dprint_vfmw
	ldrh	w2, [x19, 278]
	mov	w0, 32
	ldr	x1, .LC305
	bl	dprint_vfmw
	b	.L1353
.L1365:
	add	x19, x21, 10
	b	.L1359
	.size	HEVC_PrintSLHDR1Info, .-HEVC_PrintSLHDR1Info
	.align	3
.LC257:
	.xword	.LC256
	.align	3
.LC259:
	.xword	.LC258
	.align	3
.LC261:
	.xword	.LC260
	.align	3
.LC263:
	.xword	.LC262
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC267:
	.xword	.LC266
	.align	3
.LC269:
	.xword	.LC268
	.align	3
.LC271:
	.xword	.LC270
	.align	3
.LC273:
	.xword	.LC272
	.align	3
.LC275:
	.xword	.LC274
	.align	3
.LC277:
	.xword	.LC276
	.align	3
.LC279:
	.xword	.LC278
	.align	3
.LC281:
	.xword	.LC280
	.align	3
.LC283:
	.xword	.LC282
	.align	3
.LC285:
	.xword	.LC284
	.align	3
.LC287:
	.xword	.LC286
	.align	3
.LC289:
	.xword	.LC288
	.align	3
.LC291:
	.xword	.LC290
	.align	3
.LC293:
	.xword	.LC292
	.align	3
.LC295:
	.xword	.LC294
	.align	3
.LC297:
	.xword	.LC296
	.align	3
.LC299:
	.xword	.LC298
	.align	3
.LC301:
	.xword	.LC300
	.align	3
.LC303:
	.xword	.LC302
	.align	3
.LC305:
	.xword	.LC304
	.align	3
.LC307:
	.xword	.LC306
	.align	3
.LC309:
	.xword	.LC308
	.align	3
.LC311:
	.xword	.LC310
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1Info
	.type	HEVC_GetSLHDR1Info, %function
HEVC_GetSLHDR1Info:
	stp	x29, x30, [sp, -352]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	mov	x2, 290
	mov	w1, 0
	add	x0, x29, 56
	bl	memset
	ldrb	w3, [x21, 1]
	ldrb	w4, [x19, 56]
	ldrb	w5, [x19, 568]
	cbz	w3, .L1406
	cbnz	w4, .L1409
.L1406:
	ldrb	w6, [x19, 59]
	ldrb	w7, [x19, 128]
.L1368:
	ldr	x2, .LC312
	mov	w0, 22
	ldr	x1, .LC314
	add	x2, x2, 472
	bl	dprint_vfmw
	strb	wzr, [x20, 466]
.L1366:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 352
	ret
	.p2align 3
.L1409:
	cbz	w5, .L1406
	ldrb	w0, [x19, 59]
	cbnz	w0, .L1371
	ldrb	w7, [x19, 128]
	cbz	w7, .L1410
.L1371:
	mov	w0, 1
	strb	w0, [x20, 466]
	ldr	w1, [x21, 24]
	ldrb	w3, [x19, 57]
	ldrb	w2, [x19, 58]
	cmp	w1, 9
	strb	w3, [x29, 56]
	strb	w2, [x29, 57]
	beq	.L1411
.L1373:
	ldrb	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1374
	ldrb	w1, [x19, 129]
	cmp	w1, 1
	beq	.L1374
	cmp	w1, 9
	ccmp	w0, 9, 4, ne
	beq	.L1412
	ldrb	w0, [x29, 64]
	strb	w0, [x29, 58]
.L1374:
	mov	x1, x19
	add	x0, x29, 56
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	w1, [x29, 64]
	ldrb	w0, [x29, 58]
	cmp	w1, w0
	beq	.L1413
	strb	wzr, [x29, 65]
.L1377:
	ldrb	w0, [x29, 57]
	cbnz	w0, .L1378
	add	x5, x19, 59
	ldrb	w6, [x5, 2]
	ldrb	w4, [x5, 3]
	ldrb	w3, [x5, 4]
	ldrb	w2, [x5, 5]
	ldrb	w1, [x5, 6]
	ldrb	w0, [x5, 7]
	strb	w6, [x29, 66]
	strb	w4, [x29, 67]
	strb	w3, [x29, 68]
	strb	w2, [x29, 69]
	strb	w1, [x29, 70]
	strb	w0, [x29, 71]
	cbz	w0, .L1383
	sub	w4, w0, #1
	add	x2, x29, 56
	add	x4, x4, 17
	add	x0, x29, 72
	add	x1, x19, 82
	add	x4, x2, x4
	.p2align 2
.L1382:
	ldrb	w3, [x1, -15]
	add	x0, x0, 1
	ldrb	w2, [x1], 1
	strb	w3, [x0, -1]
	strb	w2, [x0, 10]
	cmp	x0, x4
	bne	.L1382
.L1383:
	ldrb	w0, [x5, 38]
	strb	w0, [x29, 94]
	cbz	w0, .L1381
	sub	w3, w0, #1
	add	x1, x29, 56
	add	x3, x3, 40
	add	x0, x29, 95
	add	x19, x19, 113
	add	x3, x1, x3
	.p2align 2
.L1386:
	ldrb	w2, [x19, -15]
	add	x0, x0, 1
	ldrb	w1, [x19], 1
	strb	w2, [x0, -1]
	strb	w1, [x0, 6]
	cmp	x0, x3
	bne	.L1386
.L1381:
	ldr	w0, [x20, 472]
	cbnz	w0, .L1414
	ldr	x2, .LC312
	mov	w0, 1
	ldr	x1, .LC316
	add	x2, x2, 472
	bl	dprint_vfmw
	b	.L1366
	.p2align 3
.L1378:
	add	x5, x19, 128
	ldrb	w0, [x5, 40]
	add	w0, w0, 1
	ldp	w2, w1, [x5, 8]
	uxtb	w0, w0
	strh	w2, [x29, 342]
	strb	w0, [x29, 66]
	strh	w1, [x29, 344]
	cbz	w0, .L1390
	sub	w2, w0, #1
	add	x1, x29, 68
	add	x2, x2, 87
	add	x0, x19, 172
	add	x2, x19, x2, lsl 1
	.p2align 2
.L1389:
	ldrh	w4, [x0]
	add	x0, x0, 2
	ldrh	w3, [x0, 196]
	cmp	x0, x2
	strh	w4, [x1]
	add	x1, x1, 2
	strh	w3, [x1, 66]
	bne	.L1389
.L1390:
	ldrb	w0, [x5, 41]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x29, 204]
	cbz	w0, .L1381
	sub	w2, w0, #1
	add	x1, x29, 206
	add	x2, x2, 120
	add	x0, x19, 238
	add	x19, x19, x2, lsl 1
	.p2align 2
.L1391:
	ldrh	w3, [x0]
	add	x0, x0, 2
	ldrh	w2, [x0, 196]
	cmp	x0, x19
	strh	w3, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 66]
	bne	.L1391
	b	.L1381
	.p2align 3
.L1414:
	ldr	x3, .LC317
	mov	x2, 290
	ldr	x0, [x20, 480]
	add	x1, x29, 56
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 290
	str	w0, [x20, 468]
	b	.L1366
	.p2align 3
.L1410:
	mov	w6, 0
	b	.L1368
	.p2align 3
.L1412:
	mov	w0, 1
	strb	w0, [x29, 58]
	b	.L1374
	.p2align 3
.L1413:
	ldrb	w0, [x29, 59]
	strb	w0, [x29, 65]
	b	.L1377
	.p2align 3
.L1411:
	ldr	w1, [x21, 32]
	cmp	w1, 9
	bne	.L1373
	strb	w0, [x29, 64]
	b	.L1373
	.size	HEVC_GetSLHDR1Info, .-HEVC_GetSLHDR1Info
	.align	3
.LC312:
	.xword	.LANCHOR0
	.align	3
.LC314:
	.xword	.LC313
	.align	3
.LC316:
	.xword	.LC315
	.align	3
.LC317:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ConvertHDRInfo
	.type	HEVC_ConvertHDRInfo, %function
HEVC_ConvertHDRInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	x19, x2
	bl	_mcount
	add	x3, x21, 464
	add	x0, x19, 572
	ldrb	w1, [x20]
	add	x2, x21, 496
	add	x4, x19, 584
	strb	w1, [x3, 24]
	ldr	w1, [x20, 24]
	strb	w1, [x3, 25]
	ldr	w1, [x20, 32]
	strb	w1, [x3, 26]
	ldr	w1, [x20, 28]
	str	w1, [x3, 28]
	ldrb	w1, [x19, 568]
	strb	w1, [x21, 464]
.L1416:
	ldr	w1, [x0]
	add	x0, x0, 4
	strh	w1, [x2]
	add	x2, x2, 2
	cmp	x0, x4
	ldr	w1, [x0, 8]
	strh	w1, [x2, 4]
	bne	.L1416
	ldr	w0, [x19, 596]
	mov	x2, x19
	strh	w0, [x3, 44]
	mov	x1, x20
	mov	x0, x21
	ldr	w4, [x19, 600]
	strh	w4, [x3, 46]
	ldr	w4, [x19, 604]
	str	w4, [x3, 48]
	ldr	w4, [x19, 608]
	str	w4, [x3, 52]
	ldrb	w4, [x19, 612]
	strb	w4, [x3, 1]
	ldrh	w4, [x19, 614]
	str	w4, [x3, 56]
	ldrh	w4, [x19, 616]
	str	w4, [x3, 60]
	ldrb	w4, [x19, 618]
	strb	w4, [x3, 64]
	bl	HEVC_GetSLHDR1Info
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ConvertHDRInfo, .-HEVC_ConvertHDRInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x23, x20, 4096
	add	x19, x20, 12288
	bl	_mcount
	add	x19, x19, 2448
	ldr	w1, [x20, 5588]
	mov	w5, 5036
	ldr	x0, [x20, 2960]
	mov	w4, 12668
	ldr	x2, [x20, 2952]
	mov	x3, 0
	smaddl	x0, w1, w5, x0
	ldr	w21, [x0, 32]
	strb	wzr, [x23, 753]
	smaddl	x21, w21, w4, x2
	.p2align 2
.L1424:
	ldr	w0, [x19, 48]
	cbnz	w0, .L1419
	cbz	x19, .L1420
	ldr	w2, [x20, 3372]
	cbz	w2, .L1420
	ldr	x0, [x20, 3680]
	cmp	x0, x19
	beq	.L1419
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L1422
	.p2align 3
.L1423:
	ldr	x1, [x0, 3680]
	cmp	x1, x19
	beq	.L1419
.L1422:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L1423
.L1420:
	lsl	x22, x3, 2
	mov	w0, 101
	sub	x3, x22, x3
	str	w0, [x20, 4888]
	lsl	x0, x3, 4
	mov	w1, 1
	sub	x22, x0, x3
	strb	w1, [x23, 753]
	mov	x2, 632
	add	x0, x23, 824
	add	x22, x20, x22, lsl 4
	add	x24, x22, 12288
	add	x1, x24, 2536
	bl	memcpy
	str	x19, [x20, 4912]
	str	wzr, [x20, 5072]
	str	wzr, [x22, 14752]
	strb	wzr, [x24, 2450]
	strb	wzr, [x19]
	ldr	x0, [x20, 4912]
	str	wzr, [x0, 60]
	ldr	x0, [x20, 4912]
	str	wzr, [x0, 64]
	ldr	x0, [x20, 4912]
	str	wzr, [x0, 52]
	ldrb	w1, [x23, 753]
	cmp	w1, 1
	bne	.L1428
	ldr	w0, [x20, 276]
	bl	FSP_NewLogicFs
	mov	w24, w0
	mov	w1, w0
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x22, x0
	cmp	w24, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L1426
	add	x2, x23, 128
	add	x1, x21, 2064
	add	x19, x0, 48
	bl	HEVC_ConvertHDRInfo
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1441
.L1427:
	ldr	x21, .LC320
	mov	x2, 632
	ldr	x0, [x20, 4912]
	mov	x1, x19
	ldr	x3, [x21, 104]
	add	x0, x0, 88
	blr	x3
	ldr	x1, [x20, 4912]
	mov	x2, 632
	ldr	x3, [x21, 104]
	add	x0, x23, 824
	add	x1, x1, 88
	blr	x3
	ldr	x1, [x20, 4912]
	mov	w0, 0
	str	w24, [x1, 28]
	ldrsb	w1, [x22, 4]
	str	w1, [x20, 4884]
.L1439:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1419:
	add	w3, w3, 1
	add	x19, x19, 720
	cmp	w3, 20
	bne	.L1424
.L1428:
	ldr	x1, .LC319
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1441:
	ldr	x2, [x20, 3000]
	ldr	w21, [x19, 112]
	ldr	w1, [x19, 36]
	ldr	w0, [x2, 68]
	ldr	w2, [x2, 64]
	stp	w2, w0, [x19, 68]
	mul	w21, w0, w21
	stp	wzr, wzr, [x19, 240]
	add	w0, w21, w1
	str	wzr, [x19, 256]
	stp	wzr, wzr, [x19, 248]
	str	w0, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w1, [x19, 20]
	ldr	w2, [x19, 116]
	add	w0, w21, w1
	str	w0, [x19, 24]
	add	w0, w2, w0
	str	w0, [x19, 32]
	b	.L1427
.L1426:
	ldr	x1, .LC322
	mov	w0, 0
	strb	wzr, [x23, 753]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1439
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	3
.LC319:
	.xword	.LC318
	.align	3
.LC320:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC322:
	.xword	.LC321
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x20, 276]
	bl	FSP_GetFspType
	cmn	w0, #1
	mov	w21, w0
	bne	.L1448
	b	.L1450
	.p2align 3
.L1445:
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1447
	cmp	w19, 32
	beq	.L1451
.L1448:
	ldr	w0, [x20, 276]
	mov	w1, w19
	add	w19, w19, 1
	bl	FSP_GetLogicFs
	cbnz	x0, .L1445
	ldr	x1, .LC326
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1450:
	ldr	x1, .LC324
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1447:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1451:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	add	x23, x22, 28672
	bl	_mcount
	add	x20, x20, 2449
	add	x0, x22, 4096
	add	x23, x23, 465
	add	x0, x0, 2832
	bl	ResetVoQueue
	.p2align 2
.L1455:
	strb	wzr, [x20]
	add	x19, x20, 631
	add	x21, x20, 663
	str	wzr, [x20, 47]
.L1454:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1453
	ldr	w0, [x22, 276]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1453:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1454
	add	x20, x20, 720
	cmp	x20, x23
	bne	.L1455
	ldr	w0, [x22, 184]
	cbz	w0, .L1452
	sub	w1, w0, #1
	add	x0, x22, 2156
	add	x1, x1, 540
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1457:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1457
.L1452:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x21, w1
	mov	x20, x0
	mov	x0, x30
	mov	x19, x21
	add	x22, x20, x21, lsl 3
	bl	_mcount
	ldr	x0, [x22, 3680]
	str	wzr, [x0, 48]
	ldr	x1, [x22, 3680]
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1466
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1467
	ldr	x1, [x22, 3680]
	mov	w2, 0
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
.L1467:
	ldr	x1, [x22, 3680]
	mov	w2, 0
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
.L1466:
	ldr	w2, [x20, 3372]
	sub	w2, w2, #1
	cmp	w19, w2
	bhi	.L1470
	.p2align 2
.L1476:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 3680]
	str	x0, [x1, 3680]
	bls	.L1476
.L1470:
	add	x0, x20, x2, uxtw 3
	str	xzr, [x0, 3680]
	str	w2, [x20, 3372]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, 0
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 3372]
	cbnz	w2, .L1487
	b	.L1480
	.p2align 3
.L1482:
	add	w19, w19, 1
	cmp	w2, w19
	mov	w21, w19
	bls	.L1480
.L1487:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 3680]
	ldrb	w1, [x0]
	cbz	w1, .L1482
	mov	w1, w21
	strb	wzr, [x0]
	mov	x0, x20
	sub	w19, w19, #1
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x20
	mov	w21, w19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w2, [x20, 3372]
	cmp	w2, w19
	bhi	.L1487
.L1480:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w25, 0
	bl	_mcount
	ldr	w22, [x21, 3372]
	cbz	w22, .L1491
	mov	w26, 0
	mov	w20, 0
	mov	w24, -1
	mov	w23, 1
	.p2align 2
.L1498:
	add	x19, x21, x26, uxtw 3
	ldr	w0, [x21, 276]
	ldr	x1, [x19, 3680]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1492
	ldrsb	w1, [x0]
	cbnz	w1, .L1507
	ldrsb	w0, [x0, 1]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	ldr	x0, [x19, 3680]
	bne	.L1494
.L1510:
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1494
	str	w24, [x0, 28]
	ldr	x0, [x19, 3680]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 3680]
	strb	w23, [x0, 2]
.L1507:
	ldr	x0, [x19, 3680]
.L1494:
	ldr	w0, [x0]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1511
	add	w26, w26, 1
.L1497:
	add	w20, w20, 1
	cmp	w22, w20
	bne	.L1498
.L1491:
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1492:
	ldr	x0, [x19, 3680]
	b	.L1510
	.p2align 3
.L1511:
	mov	w1, w26
	mov	x0, x21
	mov	w25, 1
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1497
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 14172]
	ldr	w1, [x19, 14176]
	cmp	w1, w0
	bcs	.L1515
	ldr	w0, [x19, 14452]
	ldr	w1, [x19, 14456]
	cmp	w1, w0
	bcs	.L1515
	ldr	w0, [x19, 3368]
	ldr	w1, [x19, 3372]
	cmp	w1, w0
	bcc	.L1512
	cmp	w0, 15
	bls	.L1518
.L1515:
	ldr	x0, [x19, 3680]
	mov	w2, 0
	strb	wzr, [x0, 1]
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_SetRef
	mov	x0, x19
	mov	w1, 0
	bl	HEVC_RemoveApcStore
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L1512:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1518:
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L1515
	b	.L1512
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	str	wzr, [x21]
	mov	w0, 2147483647
	str	w0, [x20]
	ldr	w3, [x19, 3368]
	ldr	w2, [x19, 3372]
	cmp	w2, w3
	bhi	.L1527
.L1520:
	mov	w0, 0
	cbz	w2, .L1519
	.p2align 2
.L1525:
	add	x1, x19, x0, uxtw 3
	ldr	w2, [x20]
	ldr	x1, [x1, 3680]
	ldr	w1, [x1, 8]
	cmp	w2, w1
	ble	.L1522
	str	w1, [x20]
	str	w0, [x21]
.L1522:
	ldr	w1, [x19, 3372]
	add	w0, w0, 1
	cmp	w1, w0
	bhi	.L1525
.L1519:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1527:
	ldr	x1, .LC328
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x19, 3368]
	str	w2, [x19, 3372]
	b	.L1520
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	3
.LC328:
	.xword	.LC327
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w4
	mov	w22, w2
	bl	_mcount
	ldr	w5, [x19, 5588]
	mov	w3, 5036
	ldr	x2, [x19, 2960]
	mov	w1, 12668
	ldr	x0, [x19, 2952]
	smaddl	x3, w5, w3, x2
	ldr	w3, [x3, 32]
	smaddl	x0, w3, w1, x0
	ldr	w1, [x0, 64]
	cmp	w1, w21
	ccmp	w20, wzr, 0, eq
	bne	.L1529
	ldr	w0, [x0, 68]
	cmp	w0, w22
	beq	.L1540
.L1529:
	ldrb	w1, [x19, 1]
	mov	w0, 1
	cmp	w1, w0
	beq	.L1541
.L1530:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1541:
	ldr	x2, [x19, 3032]
	ldr	w2, [x2, 24]
	tst	w2, -5
	beq	.L1530
	ldr	w2, [x19, 2384]
	mov	w0, 0
	cbnz	w2, .L1530
	str	w1, [x19, 2384]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1540:
	ldr	w0, [x19, 172]
	cbz	w0, .L1529
	ldr	x1, [x19, 3032]
	mov	w0, 0
	ldr	w1, [x1, 944]
	cbnz	w1, .L1529
	b	.L1530
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x5, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldrb	w4, [x5]
	ldr	w6, [x0, 32]
	cbz	w4, .L1553
	sub	w2, w4, #1
	mov	w7, 32
	mov	x3, 80
	add	x0, x5, 48
	mov	w1, 0
	umaddl	x3, w2, w7, x3
	add	x3, x5, x3
	.p2align 2
.L1544:
	ldr	w2, [x0], 32
	cmp	x0, x3
	add	w1, w1, w2
	bne	.L1544
.L1543:
	sbfiz	x4, x4, 5, 32
	and	w0, w6, 7
	add	x4, x5, x4
	str	w0, [x4, 60]
	ldr	x3, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w3, [x4, 52]
	add	w0, w3, w0, lsr 3
	sub	w0, w0, w1
	str	w0, [x4, 64]
	ldr	x3, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w2, [x4, 48]
	add	w1, w1, w2
	lsl	w1, w1, 3
	sub	w0, w1, w0
	str	w0, [x4, 56]
	ldr	x1, [x19, 2976]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w2, w1, [x0, 60]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w2
	str	w1, [x0, 60]
	ldr	x1, [x19, 2976]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldr	w1, [x0, 64]
	and	w1, w1, -4
	str	w1, [x0, 64]
	ldr	x3, [x19, 2976]
	ldr	w2, [x3, 8]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1561
	ldrb	w0, [x3]
	add	w4, w0, 1
	cmp	w4, 1
	ccmp	w2, w4, 0, ls
	bls	.L1547
	add	w2, w0, 2
	.p2align 2
.L1548:
	sub	w0, w2, #1
	cmp	w2, 1
	lsl	x1, x0, 5
	add	x0, x0, 1
	add	x3, x3, x1
	lsl	x0, x0, 5
	cset	w5, ls
	str	wzr, [x3, 60]
	ldr	x3, [x19, 2976]
	add	x4, x3, x0
	add	x3, x3, x1
	ldr	w4, [x4, 20]
	str	w4, [x3, 64]
	ldr	x3, [x19, 2976]
	add	x0, x3, x0
	add	x3, x3, x1
	ldr	w0, [x0, 16]
	lsl	w0, w0, 3
	str	w0, [x3, 56]
	ldr	x0, [x19, 2976]
	add	x0, x0, x1
	ldp	w4, w3, [x0, 60]
	ubfiz	w3, w3, 3, 4
	add	w3, w3, w4
	str	w3, [x0, 60]
	ldr	x0, [x19, 2976]
	add	x1, x0, x1
	ldr	w0, [x1, 64]
	and	w0, w0, -16
	str	w0, [x1, 64]
	ldr	x3, [x19, 2976]
	ldr	w0, [x3, 8]
	cmp	w0, w2
	add	w2, w2, 1
	cset	w1, hi
	tst	w5, w1
	bne	.L1548
	sub	w1, w0, #1
.L1547:
	ubfiz	x0, x1, 5, 32
	ldr	w1, [x3, 12]
	add	x3, x3, x0
	ldr	w0, [x3, 56]
	sub	w0, w0, w1
	str	w0, [x3, 56]
	ldr	x3, [x19, 2976]
	ldrb	w0, [x3]
	ldr	w4, [x3, 8]
	cmp	w0, w4
	bcs	.L1542
	.p2align 2
.L1556:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x19, 4880]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 64]
	cmp	w1, w2
	bcs	.L1550
	str	w1, [x19, 4880]
	ldr	w4, [x3, 8]
.L1550:
	cmp	w4, w0
	bhi	.L1556
.L1542:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1561:
	ldr	x1, .LC330
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1553:
	mov	w1, 0
	b	.L1543
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	3
.LC330:
	.xword	.LC329
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 164]
	ldr	w2, [x19, 5588]
	cmp	w2, w0
	bge	.L1570
	mov	w0, 5036
	ldr	x1, [x19, 2960]
	smull	x0, w2, w0
	add	x3, x1, x0
	ldrb	w0, [x1, x0]
	cbz	w0, .L1571
	ldr	w2, [x3, 32]
	ldr	w0, [x19, 160]
	cmp	w2, w0
	bge	.L1572
	ldr	x1, [x19, 2952]
	mov	w0, 12668
	smaddl	x0, w2, w0, x1
	ldrb	w1, [x0, 1]
	cbz	w1, .L1573
	ldr	w2, [x0, 48]
	ldr	w0, [x19, 156]
	cmp	w2, w0
	bcs	.L1574
	mov	w1, 24912
	ldr	x3, [x19, 2944]
	mov	w0, 0
	umull	x1, w2, w1
	ldrb	w1, [x3, x1]
	cbz	w1, .L1575
.L1564:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1570:
	ldr	x1, .LC332
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.p2align 3
.L1571:
	ldr	x1, .LC334
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.p2align 3
.L1572:
	ldr	x1, .LC336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.p2align 3
.L1573:
	ldr	x1, .LC338
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.p2align 3
.L1574:
	ldr	x1, .LC340
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.p2align 3
.L1575:
	ldr	x1, .LC342
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1564
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
	.align	3
.LC332:
	.xword	.LC331
	.align	3
.LC334:
	.xword	.LC333
	.align	3
.LC336:
	.xword	.LC335
	.align	3
.LC338:
	.xword	.LC337
	.align	3
.LC340:
	.xword	.LC339
	.align	3
.LC342:
	.xword	.LC341
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5584]
	mov	w1, 2147483647
	ldr	x2, [x19, 2976]
	add	x3, x19, x0, lsl 2
	ldr	w5, [x3, 244]
	cmp	w5, w1
	ldr	w1, [x2, 16]
	sub	w4, w1, #16
	beq	.L1603
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	beq	.L1581
.L1589:
	sub	w1, w1, #19
	cmp	w1, 1
	bls	.L1604
.L1581:
	ldr	w4, [x19, 5564]
	cmp	w4, w5
	bge	.L1580
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bls	.L1605
.L1582:
	add	x1, x19, x0
	ldrb	w8, [x1, 12]
	cbz	w8, .L1583
	ldr	w6, [x3, 252]
	cmp	w6, w4
	bgt	.L1606
.L1583:
	add	x1, x19, 4096
	ldrb	w5, [x1, 1457]
	cbnz	w5, .L1584
	ldr	w2, [x2, 16]
	sub	w5, w2, #19
	cmp	w5, 1
	bls	.L1601
	cmp	w2, 21
	beq	.L1601
	sub	w2, w2, #16
	cmp	w2, 2
	bhi	.L1584
	add	x0, x19, x0
	str	w4, [x3, 252]
	mov	w2, 1
	strb	w2, [x0, 12]
	.p2align 2
.L1584:
	ldr	w0, [x19, 260]
	ldrb	w2, [x1, 1456]
	ldr	w1, [x19, 5588]
	cbz	w0, .L1588
	ldr	w0, [x19, 208]
	cmp	w1, w0
	csinc	w2, w2, wzr, eq
.L1588:
	ldr	w3, [x19, 320]
	mov	w0, 1
	cmp	w3, w1
	beq	.L1607
.L1598:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1603:
	cmp	w4, 5
	bhi	.L1602
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	bne	.L1589
	ldr	w4, [x19, 5564]
	str	w4, [x3, 244]
.L1580:
	add	x1, x19, x0
	ldrb	w5, [x1, 6]
	cbz	w5, .L1582
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bhi	.L1582
	ldr	x2, .LC343
	mov	w3, 12854
	ldr	x1, .LC347
	mov	w0, 1
	add	x2, x2, 496
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1598
	.p2align 3
.L1606:
	ldr	w7, [x2, 16]
	sub	w1, w7, #8
	cmp	w1, 1
	bhi	.L1583
	ldr	x2, .LC343
	mov	w5, w4
	ldr	x1, .LC349
	mov	w4, w8
	mov	w3, 12863
	add	x2, x2, 496
	mov	w0, 1
	bl	dprint_vfmw
.L1602:
	mov	w0, 2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1601:
	add	x0, x19, x0
	str	w4, [x3, 252]
	strb	wzr, [x0, 12]
	b	.L1584
	.p2align 3
.L1604:
	mov	w5, -2147483647
	str	w5, [x3, 244]
	b	.L1581
	.p2align 3
.L1607:
	ldr	w0, [x19, 284]
	ldr	x19, [sp, 16]
	cmp	w0, w4
	csinc	w0, w2, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1605:
	ldr	x2, .LC343
	mov	w3, 12847
	ldr	x1, .LC345
	mov	w0, 1
	add	x2, x2, 496
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1598
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	3
.LC343:
	.xword	.LANCHOR0
	.align	3
.LC345:
	.xword	.LC344
	.align	3
.LC347:
	.xword	.LC346
	.align	3
.LC349:
	.xword	.LC348
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1613
	ldr	x0, [x19, 2936]
	mov	w20, 0
	bl	BsBitsToNextByte
	mov	w1, w0
	cbz	w0, .L1610
	ldr	x0, [x19, 2936]
	bl	BsGet
	mov	w2, w0
	ldr	x1, .LC353
	mov	w0, 19
	bl	dprint_vfmw
.L1610:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1613:
	ldr	x1, .LC351
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1610
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	3
.LC351:
	.xword	.LC350
	.align	3
.LC353:
	.xword	.LC352
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5580]
	ldr	x19, [sp, 16]
	sub	w0, w0, #16
	cmp	w0, 5
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5580]
	ldr	x19, [sp, 16]
	sub	w0, w0, #19
	cmp	w0, 1
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w24, w2
	mov	x22, x1
	mov	w23, w3
	bl	_mcount
	ldr	x0, [x20, 2936]
	cbnz	w24, .L1654
.L1652:
	mov	w1, 8
	bl	BsGet
	str	w0, [x22, 4]
	cmp	w23, wzr
	ble	.L1622
	sub	w21, w23, #1
	mov	x19, 0
	add	x21, x21, 1
	add	x25, x29, 88
	add	x22, x29, 80
	.p2align 2
.L1623:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x25, x19]
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, x21
	bne	.L1623
	cmp	w23, 7
	mov	w19, w23
	ble	.L1641
	b	.L1633
	.p2align 3
.L1626:
	cmp	w19, 8
	beq	.L1633
.L1641:
	ldr	x0, [x20, 2936]
	mov	w1, 2
	add	w19, w19, 1
	bl	BsGet
	cbz	w0, .L1626
	ldr	x1, .LC355
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1633:
	mov	x21, 0
	.p2align 2
.L1631:
	cbz	w24, .L1628
	ldrb	w0, [x25, x21]
	cbnz	w0, .L1655
.L1628:
	ldrb	w0, [x22, x21]
	cbnz	w0, .L1656
.L1630:
	add	x21, x21, 1
	cmp	w23, w21
	bgt	.L1631
.L1622:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1656:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	b	.L1630
	.p2align 3
.L1655:
	ldr	x0, [x20, 2936]
	mov	w1, 2
	mov	w19, 32
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	.p2align 2
.L1629:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	subs	w19, w19, #1
	bne	.L1629
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 12
	bl	BsGet
	b	.L1628
.L1654:
	mov	w1, 2
	add	x19, x29, 96
	add	x21, x29, 128
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	mov	w25, w0
	.p2align 2
.L1618:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19], 1
	cmp	x19, x21
	bne	.L1618
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	sub	w0, w25, #4
	cmp	w0, 3
	bls	.L1619
	ldrb	w0, [x29, 100]
	cbnz	w0, .L1619
	ldrb	w0, [x29, 101]
	cbnz	w0, .L1619
	ldrb	w0, [x29, 102]
	cbnz	w0, .L1619
	ldrb	w0, [x29, 103]
	cbnz	w0, .L1619
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 11
	bl	BsGet
	b	.L1621
	.p2align 3
.L1619:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 2
	bl	BsGet
.L1621:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	str	w25, [x20, 324]
	ldrb	w2, [x29, 97]
	ldrb	w1, [x29, 98]
	ldr	x0, [x20, 2936]
	str	w2, [x20, 328]
	str	w1, [x20, 332]
	b	.L1652
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	3
.LC355:
	.xword	.LC354
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x26, x20, 2236
	mov	w25, 0
	bl	_mcount
	ldr	x21, .LC357
	ldr	x22, .LC356
	mov	w23, 16
	ldr	x24, .LC358
.L1658:
	ldr	w0, [x26]
	cbz	w0, .L1667
	uxtw	x0, w25
	mov	w27, 0
	lsl	x28, x0, 2
	sub	x28, x28, x0
	lsl	x28, x28, 1
	.p2align 2
.L1664:
	uxtw	x19, w27
	add	x1, x21, 512
	add	x0, x19, x28
	cmp	w25, 3
	mov	x2, 64
	cbz	w25, .L1671
	add	x0, x20, x0, lsl 6
	beq	.L1672
	cmp	w27, 3
	ldr	x4, [x24, 104]
	add	x0, x0, 620
	csel	x1, x22, x1, cc
	blr	x4
.L1660:
	add	x19, x28, x19
	add	w27, w27, 1
	add	x19, x20, x19, lsl 2
	str	w23, [x19, 2252]
	ldr	w0, [x26]
	cmp	w0, w27
	bhi	.L1664
.L1667:
	add	w25, w25, 1
	add	x26, x26, 4
	cmp	w25, 4
	bne	.L1658
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1671:
	add	x0, x20, x19, lsl 6
	ldr	x1, .LC359
	ldr	x4, [x24, 104]
	mov	x2, 16
	add	x0, x0, 620
	blr	x4
	b	.L1660
.L1672:
	ldr	x0, .LC357
	uxtw	x19, w27
	cmp	w27, wzr
	ldr	x4, [x24, 104]
	add	x1, x0, 512
	ldr	x0, .LC356
	mov	x2, 64
	csel	x1, x0, x1, eq
	add	x0, x20, x19, lsl 6
	add	x0, x0, 1772
	blr	x4
	b	.L1660
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	3
.LC356:
	.xword	.LANCHOR4
	.align	3
.LC357:
	.xword	.LANCHOR0
	.align	3
.LC358:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC359:
	.xword	.LANCHOR0+576
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3000]
	ldrb	w1, [x0, 3]
	cbz	w1, .L1705
	ldrb	w1, [x19, 1]
	ldr	x20, [x19, 3008]
	cmp	w1, 1
	beq	.L1721
.L1675:
	ldrb	w1, [x20, 21]
	cbnz	w1, .L1715
	ldrb	w1, [x0, 4]
	cbz	w1, .L1679
.L1716:
	adds	x20, x0, 432
	cset	w0, eq
.L1684:
	cbnz	w0, .L1679
.L1687:
	ldr	x21, .LC360
	mov	x2, 1536
	mov	w1, 0
	add	x0, x19, 620
	ldr	x3, [x21, 96]
	blr	x3
	add	x16, x20, 1
	add	x15, x19, 348
	mov	w12, 0
	mov	w17, 64
	mov	w14, 6
.L1688:
	ldr	w13, [x15, 1888]
	cbz	w13, .L1697
	ldr	w8, [x15]
	mov	x9, x16
	mov	w11, 0
	cmp	w8, 64
	csel	w8, w8, w17, ls
	lsr	w10, w8, 2
.L1695:
	uxtw	x7, w11
	mov	w4, 0
	umaddl	x7, w12, w14, x7
	lsl	x7, x7, 4
	.p2align 2
.L1689:
	cmp	w10, w4
	bls	.L1692
	cbz	w8, .L1689
	add	x0, x7, x4, uxtw
	ldrb	w1, [x9, -1]
	mov	x6, x9
	mov	w3, 0
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 620]
	orr	w1, w2, w1
	str	w1, [x0, 620]
	.p2align 2
.L1700:
	add	w3, w3, 1
	add	x0, x7, x4, uxtw
	cmp	w8, w3
	and	w5, w3, 3
	add	x0, x19, x0, lsl 2
	lsl	w1, w5, 3
	beq	.L1689
	ldrb	w2, [x6], 1
	cmp	w5, 3
	ldr	w5, [x0, 620]
	csinc	w4, w4, w4, ne
	lsl	w1, w2, w1
	orr	w1, w5, w1
	str	w1, [x0, 620]
	b	.L1700
.L1692:
	add	w11, w11, 1
	add	x9, x9, 64
	cmp	w11, w13
	bne	.L1695
.L1697:
	add	w12, w12, 1
	add	x16, x16, 384
	cmp	w12, 4
	add	x15, x15, 4
	bne	.L1688
	ldr	x3, [x21, 104]
	mov	x2, 96
	add	x1, x20, 1536
	add	x0, x19, 2252
	blr	x3
.L1705:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1681:
	ldrb	w1, [x20, 21]
	cbz	w1, .L1716
.L1715:
	adds	x20, x20, 256
	cset	w0, eq
	cbz	w0, .L1687
.L1679:
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
.L1724:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1721:
	ldrb	w1, [x20, 1889]
	cmp	w1, 1
	beq	.L1722
	add	x2, x0, 12288
	ldrb	w2, [x2, 372]
	cmp	w2, 1
	bne	.L1675
	ldrb	w2, [x0, 4]
	cbnz	w2, .L1681
	ldrb	w2, [x20, 21]
	orr	w1, w1, w2
	cbnz	w1, .L1682
	ldrsw	x0, [x0, 12664]
	mov	w20, 12668
	ldr	x1, [x19, 2952]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 228]
	smaddl	x20, w0, w20, x1
	ldrb	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1679
	adds	x20, x20, 432
	cset	w0, eq
	b	.L1684
.L1722:
	ldrsw	x1, [x20, 1956]
	mov	w20, 5036
	ldr	x2, [x19, 2960]
	mov	w4, 12668
	ldr	x0, [x19, 2952]
	add	x1, x19, x1, lsl 2
	ldr	w3, [x1, 236]
	ldr	w1, [x1, 228]
	smaddl	x2, w3, w20, x2
	smaddl	x0, w1, w4, x0
	ldrb	w1, [x2, 21]
	cmp	w1, 1
	beq	.L1723
	ldrb	w1, [x0, 4]
	cmp	w1, 1
	beq	.L1716
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
	b	.L1724
.L1682:
	cbnz	w2, .L1715
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
	b	.L1724
.L1723:
	adds	x20, x2, 256
	cset	w0, eq
	b	.L1684
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	3
.LC360:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	uxtw	x22, w3
	mov	x21, x1
	bl	_mcount
	add	x0, x20, x19, uxtw 2
	mov	w9, 6
	mov	w8, 64
	mov	w5, 0
	umaddl	x9, w19, w9, x22
	ldr	w0, [x0, 348]
	lsl	x9, x9, 4
	cmp	w0, w8
	csel	w8, w0, w8, ls
	lsr	w10, w8, 2
	.p2align 2
.L1726:
	cmp	w5, w10
	bcs	.L1725
	cbz	w8, .L1726
	add	x0, x9, x5, uxtw
	mov	x7, x21
	mov	w4, 0
	add	x0, x20, x0, lsl 2
	ldrb	w2, [x7], 1
	ldr	w3, [x0, 620]
	orr	w2, w3, w2
	str	w2, [x0, 620]
	.p2align 2
.L1732:
	add	w4, w4, 1
	add	x0, x9, x5, uxtw
	cmp	w8, w4
	and	w6, w4, 3
	add	x0, x20, x0, lsl 2
	lsl	w2, w6, 3
	beq	.L1726
	ldrb	w3, [x7], 1
	cmp	w6, 3
	ldr	w6, [x0, 620]
	csinc	w5, w5, w5, ne
	lsl	w2, w3, w2
	orr	w2, w6, w2
	str	w2, [x0, 620]
	b	.L1732
.L1725:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 3
	bls	.L1746
	ldr	x1, .LC364
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1746:
	ldr	x0, .LC362
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1736
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1736:
	.section	.rodata
	.align	0
	.align	2
.L1736:
	.byte	(.L1740 - .Lrtx1736) / 4
	.byte	(.L1738 - .Lrtx1736) / 4
	.byte	(.L1738 - .Lrtx1736) / 4
	.byte	(.L1739 - .Lrtx1736) / 4
	.text
	.p2align 3
.L1738:
	cmp	w20, 2
	ldr	x0, .LC361
	bhi	.L1743
.L1744:
	add	x0, x0, 144
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1739:
	ldr	x0, .LC361
	cbz	w20, .L1744
.L1743:
	add	x0, x0, 80
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1740:
	ldr	x0, .LC361
	ldp	x19, x20, [sp, 16]
	add	x0, x0, 64
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	3
.LC361:
	.xword	.LANCHOR4
	.align	3
.LC362:
	.xword	.L1736
	.align	3
.LC364:
	.xword	.LC363
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	x23, x2
	mov	w20, w3
	bl	_mcount
	cmp	x21, xzr
	ccmp	x23, xzr, 4, ne
	ccmp	x22, xzr, 4, ne
	beq	.L1757
	sub	w0, w20, #1
	mov	w19, 1
	asr	w0, w0, 1
	cbz	w0, .L1749
	.p2align 2
.L1750:
	asr	w0, w0, 1
	add	w19, w19, 1
	cbnz	w0, .L1750
.L1749:
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w20, 1
	strb	w0, [x23]
	cset	w24, hi
	cmp	w0, wzr
	cset	w0, ne
	tst	w24, w0
	beq	.L1754
	ldr	w0, [x21, 76]
	cbz	w0, .L1754
	mov	w20, 0
	.p2align 2
.L1755:
	ldr	x0, [x22, 2936]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 4]
	ldr	w0, [x21, 76]
	cmp	w0, w20
	bhi	.L1755
.L1754:
	ldr	w0, [x21, 20]
	cbz	w0, .L1772
.L1753:
	mov	w0, 0
.L1748:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1772:
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, wzr
	strb	w0, [x23, 1]
	cset	w0, ne
	tst	w24, w0
	beq	.L1753
	ldr	w0, [x21, 80]
	cbz	w0, .L1753
	mov	w20, 0
	.p2align 2
.L1756:
	ldr	x0, [x22, 2936]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 132]
	ldr	w0, [x21, 80]
	cmp	w0, w20
	bhi	.L1756
	b	.L1753
.L1757:
	mov	w0, -1
	b	.L1748
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1775
	ldr	x1, [x19, 2976]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	cset	w0, cc
	ret
	.p2align 3
.L1775:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2936]
	ldr	w2, [x0, 24]
	ldr	w3, [x0, 32]
	lsl	w2, w2, 3
	cmp	w2, w3
	bls	.L1779
	mov	w1, 8
	bl	BsShow
	cmp	w0, 128
	cset	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1779:
	ldr	x1, .LC366
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	3
.LC366:
	.xword	.LC365
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
.L1793:
	ldr	x1, [x20, 2976]
	mov	w3, 0
	ldr	w5, [x1, 8]
	sub	w5, w5, #1
	add	x2, x1, x5, lsl 5
	ldr	w0, [x2, 48]
	ldr	x2, [x2, 40]
	sub	x0, x0, #1
	add	x0, x2, x0
	.p2align 2
.L1781:
	ldrb	w2, [x0]
	add	x19, x5, 1
	lsl	x19, x19, 5
	add	x4, x1, x19
	cbnz	w2, .L1794
	ldr	x2, [x1, 40]
	add	w3, w3, 1
	cmp	x0, x2
	beq	.L1795
	ldr	x2, [x4, 8]
	cmp	x0, x2
	sub	x0, x0, #1
	bne	.L1781
	add	x1, x1, x5, lsl 5
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 68]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x20, 2976]
	add	x19, x0, x19
	str	xzr, [x19, 8]
	ldr	x1, [x20, 2976]
	ldr	w0, [x1, 8]
	sub	w0, w0, #1
	str	w0, [x1, 8]
	b	.L1793
	.p2align 3
.L1794:
	mov	w0, 1
	mov	w5, w0
	tbnz	x2, 0, .L1788
	.p2align 2
.L1791:
	lsl	w4, w5, w0
	add	w0, w0, 1
	tst	w4, w2
	bne	.L1788
	cmp	w0, 8
	bne	.L1791
	ldr	x1, .LC370
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1795:
	ldr	x1, .LC368
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1788:
	str	wzr, [x1, 4]
	add	w3, w0, w3, lsl 3
	mov	w0, 0
	ldr	x1, [x20, 2976]
	str	w3, [x1, 12]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	3
.LC368:
	.xword	.LC367
	.align	3
.LC370:
	.xword	.LC369
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 168]
	ldr	w0, [x19, 148]
	add	w3, w3, 1
	cmp	w3, wzr
	ble	.L1797
	udiv	w1, w0, w3
	mov	w4, 104
	ldr	x5, [x19, 3024]
	msub	w0, w1, w3, w0
	umull	x1, w0, w4
	add	x1, x5, x1
	ldr	w1, [x1, 32]
	cbz	w1, .L1798
	mov	w1, 0
	b	.L1800
	.p2align 3
.L1801:
	udiv	w0, w2, w3
	msub	w0, w0, w3, w2
	umull	x2, w0, w4
	add	x2, x5, x2
	ldr	w2, [x2, 32]
	cbz	w2, .L1798
.L1800:
	add	w1, w1, 1
	cmp	w3, w1
	add	w2, w1, w0
	bne	.L1801
.L1797:
	str	w0, [x19, 148]
.L1812:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1798:
	cmp	w0, w3
	str	w0, [x19, 148]
	bcs	.L1812
	mov	w1, 104
	mov	w2, 1
	umull	x1, w0, w1
	add	x5, x5, x1
	str	w2, [x5, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1822
	ldr	x24, .LC373
	add	x19, x20, 40
	ldr	x23, .LC375
	add	x22, x20, 104
	stp	wzr, wzr, [x20, 32]
.L1817:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L1816
	ldr	w1, [x19, 28]
	bl	SM_ReleaseStreamSeg
	ldr	w4, [x19, 8]
	mov	x2, x24
	ldr	x3, [x19]
	mov	x1, x23
	mov	w0, 7
	bl	dprint_vfmw
	str	xzr, [x19]
	str	wzr, [x19, 8]
	str	wzr, [x19, 20]
.L1816:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L1817
	ldr	x3, .LC376
	mov	x2, 104
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
.L1813:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1822:
	ldr	x2, .LC371
	mov	w3, 14174
	ldr	x1, .LC372
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1813
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	3
.LC371:
	.xword	.LC2
	.align	3
.LC372:
	.xword	.LC4
	.align	3
.LC373:
	.xword	.LANCHOR5
	.align	3
.LC375:
	.xword	.LC374
	.align	3
.LC376:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecBuffers
	.type	HEVC_InitDecBuffers, %function
HEVC_InitDecBuffers:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L1862
.L1824:
	ldr	x0, [x20, 3000]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 3368]
.L1825:
	cmp	w0, 17
	bhi	.L1863
.L1826:
	add	x2, x20, 3328
	add	x0, x20, 3408
	add	x1, x20, 3544
	stp	wzr, wzr, [x2, 44]
	stp	wzr, wzr, [x2, 52]
	str	wzr, [x20, 3388]
	str	wzr, [x20, 3396]
	str	wzr, [x20, 3400]
	.p2align 2
.L1827:
	str	xzr, [x0]
	add	x0, x0, 8
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	str	xzr, [x0, 400]
	str	xzr, [x0, 536]
	str	xzr, [x0, 672]
	cmp	x0, x1
	bne	.L1827
	add	x26, x20, 12288
	ldr	x22, .LC380
	add	x19, x26, 2448
	mov	w21, 0
	mov	w25, 20
	mov	w24, 16
	.p2align 2
.L1828:
	ldr	x3, [x22, 96]
	add	x0, x19, 88
	mov	x2, 632
	mov	w1, 0
	mov	w23, 16
	blr	x3
	str	w21, [x19, 236]
	add	w21, w21, 1
	strb	wzr, [x19]
	strb	wzr, [x19, 1]
	cmp	w21, 20
	strb	wzr, [x19, 2]
	str	wzr, [x19, 8]
	stp	w25, w24, [x19, 20]
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	str	x19, [x19, 80]
	add	x19, x19, 720
	bne	.L1828
	ldr	x3, [x22, 96]
	mov	x2, 280
	mov	w1, 0
	add	x0, x26, 1884
	blr	x3
	str	w23, [x20, 14172]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x26, 2164
	str	wzr, [x20, 14176]
	blr	x3
	str	w23, [x20, 14452]
	add	x1, x20, 3056
	add	x0, x20, 3192
	str	wzr, [x20, 14456]
	.p2align 2
.L1829:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L1829
	add	x1, x20, 3328
	str	wzr, [x20, 5620]
	.p2align 2
.L1830:
	str	xzr, [x0], 8
	cmp	x1, x0
	bne	.L1830
	ldr	w0, [x20, 184]
	str	wzr, [x20, 5624]
	cbz	w0, .L1835
	sub	w1, w0, #1
	add	x0, x20, 2156
	add	x1, x1, 540
	add	x1, x20, x1, lsl 2
	.p2align 2
.L1834:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L1834
.L1835:
	ldr	w3, [x20, 168]
	mov	w19, 0
	cbz	w3, .L1823
	.p2align 2
.L1852:
	ldr	x0, [x20, 3016]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L1836
	ldr	x2, [x20, 2976]
	cmp	x0, x2
	beq	.L1836
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3016]
	mov	w2, 2
	str	xzr, [x0, x21, lsl 3]
	ldr	w1, [x20, 204]
	ldr	w0, [x20, 260]
	ldr	w4, [x20, 176]
	cmp	w1, wzr
	cset	w7, ne
	cmp	w0, wzr
	cset	w5, ne
	sub	w6, w4, #1
	cmp	w4, 3
	ldr	w3, [x20, 168]
	sub	w1, w1, w7
	csel	w2, w6, w2, cs
	sub	w0, w0, w5
	str	w2, [x20, 176]
	str	w1, [x20, 204]
	str	w0, [x20, 260]
.L1836:
	cmp	w3, w19
	bhi	.L1852
.L1823:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1863:
	ldr	x2, .LC377
	mov	w4, 17
	ldr	x1, .LC379
	mov	w3, w4
	add	x2, x2, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 3368]
	b	.L1826
	.p2align 3
.L1862:
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L1824
	ldr	w0, [x20, 2380]
	cbz	w0, .L1824
	ldr	x1, [x20, 3000]
	ldr	w1, [x1, 184]
	mul	w0, w0, w1
	add	w0, w0, 1
	str	w0, [x20, 3368]
	b	.L1825
	.size	HEVC_InitDecBuffers, .-HEVC_InitDecBuffers
	.align	3
.LC377:
	.xword	.LANCHOR5
	.align	3
.LC379:
	.xword	.LC378
	.align	3
.LC380:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1875
	ldr	w3, [x20, 3372]
	mov	w0, 0
	mov	w4, 1
	cbz	w3, .L1870
	.p2align 2
.L1884:
	add	x1, x20, x0, uxtw 3
	add	w0, w0, 1
	ldr	x1, [x1, 3680]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L1868
	strb	w4, [x1, 2]
	ldr	w3, [x20, 3372]
.L1868:
	cmp	w3, w0
	bhi	.L1884
.L1870:
	mov	w0, -2147483647
	add	x19, x20, 3680
	add	x21, x20, 3816
	stp	w0, w0, [x20, 212]
	.p2align 2
.L1867:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L1871
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1871:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L1872
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1872:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L1873
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1873:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L1874
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1874:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L1867
	mov	x0, x20
	bl	HEVC_InitDecBuffers
	mov	w0, 0
.L1865:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1875:
	mov	w0, -1
	b	.L1865
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2976]
	cbz	x0, .L1894
	ldr	w0, [x0, 48]
	cmp	w0, 4095
	bhi	.L1891
	ldr	x1, .LC384
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	ldr	x3, .LC385
	ldr	w2, [x1, 48]
	ldr	x0, [x1, 72]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 40]
	sub	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 2976]
	mov	w3, 1
	ldr	w2, [x0, 100]
	ldr	w1, [x0, 68]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2976]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2976]
	ldr	w4, [x0, 48]
	ldr	x2, [x0, 72]
	sub	x2, x2, x4
	str	x2, [x0, 40]
	ldr	x0, [x19, 2976]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 84]
	sub	w2, w2, w4
	str	w2, [x0, 52]
	ldr	x0, [x19, 2976]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 80]
	add	w2, w4, w2
	str	w2, [x0, 48]
	ldr	x0, [x19, 2976]
	str	w3, [x0, 8]
	ldr	w0, [x19, 276]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 2976]
	str	xzr, [x0, 72]
	ldr	x0, [x19, 2976]
	str	wzr, [x0, 92]
	ldr	x0, [x19, 2976]
	str	wzr, [x0, 80]
.L1891:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1894:
	ldr	x1, .LC382
	bl	dprint_vfmw
	b	.L1891
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	3
.LC382:
	.xword	.LC381
	.align	3
.LC384:
	.xword	.LC383
	.align	3
.LC385:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1900
	ldr	w3, [x19, 3372]
	cbz	w3, .L1900
	ldr	x0, [x19, 3680]
	cmp	x20, x0
	beq	.L1902
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1897
	.p2align 3
.L1898:
	ldr	x2, [x0, 3680]
	cmp	x20, x2
	beq	.L1902
.L1897:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1898
.L1900:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1902:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_u_v, .-HEVC_u_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_f_v, .-HEVC_f_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L1909
	mov	w0, -4370
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1909:
	mov	w1, w0
	mov	x0, x19
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x19
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w21
	mov	x0, x19
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ue_v, .-HEVC_ue_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC387
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1930
.L1915:
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	mov	w0, 0
.L1913:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1930:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 8
	mov	w22, w0
	bhi	.L1931
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 4
	mov	w1, w0
	mov	w0, 0
	bhi	.L1913
	ldr	x0, .LC390
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1914
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1914:
	.section	.rodata
	.align	0
	.align	2
.L1914:
	.byte	(.L1915 - .Lrtx1914) / 4
	.byte	(.L1915 - .Lrtx1914) / 4
	.byte	(.L1916 - .Lrtx1914) / 4
	.byte	(.L1917 - .Lrtx1914) / 4
	.byte	(.L1918 - .Lrtx1914) / 4
	.text
	.p2align 3
.L1916:
	mov	w2, 1
	lsl	w22, w2, w22
	cbz	w22, .L1929
	add	w21, w21, 7
	mov	w20, 0
	and	w21, w21, -8
	.p2align 2
.L1920:
	ldr	x0, [x19, 2936]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	cmp	w22, w20
	bne	.L1920
.L1929:
	mov	w0, 0
.L1932:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1917:
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	cmp	w0, 256
	mov	w23, w0
	bhi	.L1922
	cbz	w0, .L1929
	add	w21, w21, 7
	add	w22, w22, 7
	and	w21, w21, -8
	and	w22, w22, -8
	mov	w20, 0
	.p2align 2
.L1924:
	ldr	x0, [x19, 2936]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, w22
	bl	BsGet
	cmp	w20, w23
	bne	.L1924
	mov	w0, 0
	b	.L1932
	.p2align 3
.L1918:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	beq	.L1933
.L1925:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	mov	w0, 0
	b	.L1932
	.p2align 3
.L1933:
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	b	.L1925
.L1931:
	ldr	x1, .LC389
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1913
.L1922:
	ldr	x1, .LC392
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1913
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	3
.LC387:
	.xword	.LC386
	.align	3
.LC389:
	.xword	.LC388
	.align	3
.LC390:
	.xword	.L1914
	.align	3
.LC392:
	.xword	.LC391
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC394
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1935
	ldr	x0, [x19, 2936]
	mov	w1, 7
	bl	BsGet
	mov	w21, w0
	sub	w0, w0, #3
	cmp	w0, 2
	bhi	.L1942
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w20, w0
	ldr	x0, [x19, 2936]
	mov	w1, 6
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	cmp	w20, wzr
	ccmp	w21, 5, 4, eq
	bne	.L1943
.L1938:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
.L1935:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L1937:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1943:
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	b	.L1938
	.p2align 3
.L1942:
	ldr	x1, .LC396
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1937
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	3
.LC394:
	.xword	.LC393
	.align	3
.LC396:
	.xword	.LC395
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	cmp	x21, xzr
	ccmp	x20, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L1948
	ldr	x1, .LC398
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldrb	w0, [x20, 3]
	cbnz	w0, .L1955
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1956
.L1947:
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L1945:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1955:
	ldr	w1, [x20, 4]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1947
.L1956:
	ldr	w1, [x20, 8]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	b	.L1947
	.p2align 3
.L1948:
	mov	w0, -1
	b	.L1945
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	3
.LC398:
	.xword	.LC397
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC400
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 15
	bgt	.L1958
	tbnz	w0, #31, .L1962
	ldr	x22, .LC404
	add	w21, w0, 1
	mov	w19, 0
	.p2align 2
.L1961:
	ldr	x0, [x20, 2936]
	mov	x1, x22
	add	w19, w19, 1
	bl	HEVC_ue_v
	cmp	w21, w19
	bne	.L1961
.L1962:
	ldr	x0, [x20, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L1960:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1958:
	ldr	x1, .LC402
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1960
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	3
.LC400:
	.xword	.LC399
	.align	3
.LC402:
	.xword	.LC401
	.align	3
.LC404:
	.xword	.LC403
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x22, x2
	bl	_mcount
	ldr	x1, .LC406
	ldr	x0, [x19, 2936]
	str	wzr, [x19, 12744]
	bl	HEVC_ue_v
	cmp	w0, 15
	bhi	.L1990
	add	x0, x19, 12288
	mov	w1, 1
	mov	w24, 0
	strb	w1, [x0, 449]
	ldrb	w0, [x22, 2]
	cbz	w0, .L1991
.L1967:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	mov	w21, w1
	mov	w20, 0
	bl	BsGet
	strb	w0, [x23]
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2936]
	add	w1, w1, w21
	bl	BsGet
.L1968:
	cbz	w20, .L1992
	cmp	w20, 1
	beq	.L1993
.L1973:
	cmp	w21, 1
	bhi	.L1972
.L1971:
	add	w20, w20, 1
	add	w21, w21, 1
	b	.L1968
	.p2align 3
.L1972:
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L1988:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1991:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w24, w0
	cbz	w24, .L1967
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 20]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	b	.L1967
.L1990:
	ldr	x1, .LC408
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1988
.L1992:
	ldrb	w0, [x22]
	cbz	w0, .L1973
	ldr	w0, [x22, 24]
	mov	w23, 0
	cmn	w0, #1
	bne	.L1976
	b	.L1971
	.p2align 3
.L1975:
	ldr	w0, [x22, 24]
	add	w0, w0, 1
	cmp	w0, w23
	bls	.L1973
.L1976:
	ldr	w1, [x22, 12]
	add	w23, w23, 1
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x22, 2]
	orr	w0, w0, w24
	cbz	w0, .L1975
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	b	.L1975
.L1993:
	ldrb	w0, [x22, 1]
	cbz	w0, .L1972
	ldr	w0, [x22, 24]
	cmn	w0, #1
	beq	.L1972
	mov	w23, 0
	b	.L1976
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	3
.LC406:
	.xword	.LC405
	.align	3
.LC408:
	.xword	.LC407
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	x22, x1
	bl	_mcount
	ldr	w1, [x19, 12740]
	ldr	w0, [x19, 12744]
	add	w1, w1, 1
	str	w1, [x19, 12740]
	add	w0, w0, 1
	str	w0, [x19, 12744]
	ldrb	w0, [x20, 2]
	cbnz	w0, .L2021
.L1995:
	ldrh	w0, [x20, 44]
	add	x21, x20, 44
	cbz	w0, .L1997
	ldr	w1, [x21, 16]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x22, 8]
	ldr	w1, [x21, 20]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	str	w0, [x22, 12]
	ldrb	w0, [x21, 2]
	cbnz	w0, .L1998
.L2001:
	ldrsw	x1, [x19, 276]
	ldr	x0, .LC409
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2022
.L1997:
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L2004:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2021:
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	str	w0, [x22]
	mov	w1, 2
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x19, 2936]
	bl	BsGet
	b	.L1995
	.p2align 3
.L2022:
	ldr	w1, [x0, 156]
	cbnz	w1, .L1997
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L1997
	mov	x2, x20
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1997
	.p2align 3
.L1998:
	ldr	w1, [x21, 8]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x21, 2]
	cbz	w0, .L2001
	ldrb	w0, [x21, 3]
	cbz	w0, .L2001
	ldr	x1, .LC411
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	mov	w24, w0
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w25, w0
	cbnz	w25, .L2023
.L2002:
	cmp	w24, 255
	bhi	.L2024
	ldr	x26, .LC415
	add	w24, w24, 1
	mov	w23, 0
	b	.L2006
	.p2align 3
.L2005:
	cmp	w23, w24
	beq	.L2001
.L2006:
	ldr	x0, [x19, 2936]
	mov	x1, x26
	add	w23, w23, 1
	bl	HEVC_ue_v
	cbnz	w25, .L2005
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	b	.L2005
	.p2align 3
.L2023:
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2936]
	add	w1, w1, 1
	bl	BsGet
	b	.L2002
.L2024:
	ldr	x1, .LC413
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2004
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	3
.LC409:
	.xword	s_pstVfmwChan
	.align	3
.LC411:
	.xword	.LC410
	.align	3
.LC413:
	.xword	.LC412
	.align	3
.LC415:
	.xword	.LC414
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Volume_Reconstruction_Info
	.type	HEVC_Sei_Color_Volume_Reconstruction_Info, %function
HEVC_Sei_Color_Volume_Reconstruction_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L2035
	ldr	x1, .LC417
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2027
.L2031:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x20]
.L2026:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2027:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2040
.L2028:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	mov	w21, 0
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x20, 5]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x20, 6]
	mov	w1, 4
	ldr	x0, [x19, 2936]
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 7]
	cbz	w1, .L2033
	.p2align 2
.L2037:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2936]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 8]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x22, 23]
	ldrb	w0, [x20, 7]
	cmp	w0, w21
	bhi	.L2037
.L2033:
	ldr	x0, [x19, 2936]
	mov	w1, 4
	mov	w21, 0
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 38]
	cbz	w1, .L2031
	.p2align 2
.L2036:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2936]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 39]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x22, 54]
	ldrb	w0, [x20, 38]
	cmp	w0, w21
	bhi	.L2036
	b	.L2031
	.p2align 3
.L2035:
	mov	w0, -1
	b	.L2026
	.p2align 3
.L2040:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	b	.L2028
	.size	HEVC_Sei_Color_Volume_Reconstruction_Info, .-HEVC_Sei_Color_Volume_Reconstruction_Info
	.align	3
.LC417:
	.xword	.LC416
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Registered_Itu_T_T35
	.type	HEVC_Sei_User_Data_Registered_Itu_T_T35, %function
HEVC_Sei_User_Data_Registered_Itu_T_T35:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L2048
	cmp	w21, 3
	bls	.L2052
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 2
	beq	.L2053
	cmp	w0, 4
	beq	.L2054
	subs	w21, w21, #4
	mov	w19, 0
	beq	.L2047
	.p2align 2
.L2050:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L2050
.L2047:
	mov	w0, 0
.L2042:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2053:
	add	x1, x20, 4096
	mov	x0, x20
	add	x1, x1, 184
	bl	HEVC_Sei_TSI
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2054:
	add	x1, x20, 4096
	mov	x0, x20
	add	x1, x1, 187
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2048:
	mov	w0, -1
	b	.L2042
.L2052:
	ldr	x1, .LC419
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2042
	.size	HEVC_Sei_User_Data_Registered_Itu_T_T35, .-HEVC_Sei_User_Data_Registered_Itu_T_T35
	.align	3
.LC419:
	.xword	.LC418
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	w20, w3
	mov	x0, x30
	mov	x27, x1
	mov	x19, x2
	bl	_mcount
	cbnz	w20, .L2102
.L2056:
	ldr	x1, .LC433
	ldr	x0, [x22, 2936]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19]
	bhi	.L2103
	ldr	x1, .LC437
	ldr	x0, [x22, 2936]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19, 4]
	bhi	.L2104
	ldr	w1, [x19]
	add	w2, w0, w1
	str	w2, [x19, 8]
	cmp	w2, 16
	bhi	.L2081
	mov	w20, 0
	cbz	w1, .L2083
	ldr	x25, .LC443
	mov	w21, 0
	mov	w23, 0
	mov	w24, 32767
	b	.L2085
	.p2align 3
.L2084:
	str	w23, [x19, x2, lsl 2]
	add	x20, x19, x20
	ldr	x0, [x22, 2936]
	bl	BsGet
	strb	w0, [x20, 12]
	ldr	w20, [x19]
	cmp	w20, w21
	bls	.L2105
.L2085:
	ldr	x0, [x22, 2936]
	mov	x1, x25
	uxtw	x20, w21
	add	w21, w21, 1
	bl	HEVC_ue_v
	cmp	w0, w24
	mvn	w1, w0
	add	x2, x20, 8
	add	w23, w23, w1
	mov	w1, 1
	bls	.L2084
	ldr	x1, .LC445
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2102:
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2056
	ldr	w0, [x27, 176]
	cmp	w20, w0
	beq	.L2106
	sub	w20, w20, #1
.L2060:
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x1, .LC427
	ldr	x0, [x22, 2936]
	bl	HEVC_ue_v
	uxtw	x1, w20
	mov	w4, 1
	lsl	x2, x1, 2
	sub	w25, w4, w25, lsl 1
	sub	x3, x2, x1
	lsl	x2, x3, 3
	sub	x2, x2, x3
	lsl	x24, x2, 1
	sub	x24, x24, x1
	madd	w25, w0, w25, w25
	add	x28, x27, x24, lsl 2
	ldr	w2, [x28, 2172]
	cmp	w2, 16
	bhi	.L2107
	mov	w21, 0
	mov	w26, 0
	mov	w20, 0
	mov	w23, 0
	b	.L2067
	.p2align 3
.L2062:
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L2108
.L2063:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L2109
.L2067:
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2062
	ldr	x0, [x22, 2936]
	mov	w1, 1
	bl	BsGet
	lsl	w0, w0, 1
	sub	w1, w0, #1
	cmp	w1, 1
	bhi	.L2063
.L2108:
	ldr	w5, [x28, 2172]
	add	x1, x24, x21, uxtw
	uxtw	x2, w23
	cmp	w5, w21
	add	x4, x2, 8
	add	x3, x19, x2
	add	x2, x27, x1, lsl 2
	mov	w1, 0
	bls	.L2064
	ldr	w1, [x2, 2196]
.L2064:
	cmp	w0, 1
	add	w0, w1, w25
	str	w0, [x19, x4, lsl 2]
	cset	w1, eq
	strb	w1, [x3, 12]
	tbnz	w0, #31, .L2110
	add	w26, w26, 1
	add	w23, w23, 1
.L2111:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcs	.L2067
.L2109:
	cmp	w23, 16
	str	w23, [x19, 8]
	ccmp	w20, 16, 2, ls
	ccmp	w26, 16, 2, ls
	stp	w20, w26, [x19]
	bhi	.L2068
	cmp	w23, 1
	bls	.L2074
	sub	w10, w23, #2
	add	x9, x19, 36
	add	x10, x10, 1
	mov	x7, 0
	.p2align 2
.L2073:
	add	x0, x19, x7
	mov	w3, w7
	ldr	w5, [x9]
	ldrb	w8, [x0, 13]
	tbnz	w7, #31, .L2077
	.p2align 2
.L2092:
	sxtw	x1, w3
	add	w0, w3, 1
	add	x4, x19, x1
	add	x1, x19, x1, lsl 2
	sxtw	x0, w0
	add	x6, x0, 8
	add	x0, x19, x0
	ldr	w2, [x1, 32]
	cmp	w5, w2
	bge	.L2075
	str	w2, [x19, x6, lsl 2]
	ldrb	w2, [x4, 12]
	strb	w2, [x0, 12]
	str	w5, [x1, 32]
	strb	w8, [x4, 12]
.L2075:
	subs	w3, w3, #1
	bpl	.L2092
.L2077:
	add	x7, x7, 1
	add	x9, x9, 4
	cmp	x10, x7
	bne	.L2073
.L2074:
	lsr	w7, w20, 1
	sub	w20, w20, #1
	cbz	w7, .L2071
	add	x2, x19, 32
	add	x1, x19, 12
	sub	w7, w20, w7
	.p2align 2
.L2078:
	sxtw	x0, w20
	ldrb	w4, [x1]
	add	x3, x19, x0
	ldr	w5, [x2]
	add	x0, x19, x0, lsl 2
	sub	w20, w20, #1
	cmp	w20, w7
	ldr	w6, [x0, 32]
	str	w6, [x2], 4
	ldrb	w6, [x3, 12]
	strb	w6, [x1], 1
	str	w5, [x0, 32]
	strb	w4, [x3, 12]
	bne	.L2078
.L2071:
	mov	w0, 0
.L2101:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2110:
	add	w20, w20, 1
	add	w23, w23, 1
	b	.L2111
.L2105:
	ldr	w2, [x19, 8]
.L2083:
	cmp	w2, w20
	bls	.L2071
	ldr	x24, .LC447
	mov	w23, 0
	.p2align 2
.L2086:
	ldr	x0, [x22, 2936]
	mov	x1, x24
	uxtw	x21, w20
	add	w20, w20, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x2, x21, 8
	add	w23, w23, w0
	add	x21, x19, x21
	mov	w1, 1
	str	w23, [x19, x2, lsl 2]
	ldr	x0, [x22, 2936]
	bl	BsGet
	strb	w0, [x21, 12]
	ldr	w0, [x19, 8]
	cmp	w0, w20
	bhi	.L2086
	b	.L2071
.L2106:
	ldr	x1, .LC421
	ldr	x0, [x22, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w20, w2
	bcc	.L2112
	sub	w3, w20, #1
	sub	w20, w3, w0
	cmp	w20, w3
	bls	.L2060
	ldr	x1, .LC425
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2068:
	ldr	x1, .LC431
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2104:
	ldr	x1, .LC439
	mov	w0, 1
	ldr	w2, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2112:
	ldr	x1, .LC423
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2107:
	ldr	x1, .LC429
	mov	w0, w4
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2103:
	ldr	x1, .LC435
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
.L2081:
	ldr	x1, .LC441
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2101
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	3
.LC421:
	.xword	.LC420
	.align	3
.LC423:
	.xword	.LC422
	.align	3
.LC425:
	.xword	.LC424
	.align	3
.LC427:
	.xword	.LC426
	.align	3
.LC429:
	.xword	.LC428
	.align	3
.LC431:
	.xword	.LC430
	.align	3
.LC433:
	.xword	.LC432
	.align	3
.LC435:
	.xword	.LC434
	.align	3
.LC437:
	.xword	.LC436
	.align	3
.LC439:
	.xword	.LC438
	.align	3
.LC441:
	.xword	.LC440
	.align	3
.LC443:
	.xword	.LC442
	.align	3
.LC445:
	.xword	.LC444
	.align	3
.LC447:
	.xword	.LC446
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	uxtb	w19, w2
	mov	w23, w3
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2136
	cbnz	w19, .L2160
.L2116:
	ldr	x27, .LC451
	mov	w19, 0
	ldr	x25, .LC449
	ldr	x26, .LC453
	ldr	x28, .LC455
	.p2align 2
.L2132:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	uxtw	x21, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2161
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
.L2135:
	ldr	x0, [x20, 2936]
	mov	x1, x25
	bl	HEVC_ue_v
.L2122:
	ldr	x0, [x20, 2936]
	mov	x1, x27
	bl	HEVC_ue_v
	add	x1, x22, x21, lsl 2
	str	w0, [x1, 24]
.L2123:
	cmp	w0, 31
	bhi	.L2162
	mov	w24, 0
.L2125:
	cbz	w24, .L2163
	cmp	w24, 1
	beq	.L2158
.L2131:
	add	w24, w24, 1
	cmp	w24, 2
	bne	.L2125
.L2130:
	add	w19, w19, 1
	cmp	w23, w19
	bcs	.L2132
	mov	w0, 0
.L2157:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2162:
	mov	w2, w0
	mov	x1, x26
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
	b	.L2125
	.p2align 3
.L2161:
	add	x24, x22, x21, lsl 2
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	str	wzr, [x24, 24]
	uxtb	w0, w0
	cbnz	w0, .L2135
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2122
	ldr	w0, [x24, 24]
	b	.L2123
	.p2align 3
.L2160:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x22, 1]
	ldrh	w0, [x22]
	cbz	w0, .L2116
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22, 2]
	cbnz	w0, .L2164
.L2118:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	ldrb	w0, [x22, 2]
	cbnz	w0, .L2165
.L2119:
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 12]
	mov	w1, 5
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x22, 16]
	mov	w1, 5
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L2116
.L2136:
	mov	w0, -1
	b	.L2157
.L2165:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	b	.L2119
.L2164:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x22, 3]
	mov	w1, 5
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L2118
.L2163:
	ldrb	w0, [x22]
	cbnz	w0, .L2138
	mov	w24, 1
.L2158:
	ldrb	w0, [x22, 1]
	cbz	w0, .L2130
.L2138:
	add	x0, x21, 4
	str	wzr, [x29, 108]
	lsl	x0, x0, 2
	str	x0, [x29, 96]
	b	.L2134
.L2133:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x29, 96]
	ldr	w1, [x29, 108]
	add	x0, x22, x0
	ldr	w0, [x0, 8]
	cmp	w0, w1
	bcc	.L2131
.L2134:
	ldr	w2, [x29, 108]
	mov	x1, x28
	ldr	x0, [x20, 2936]
	add	w2, w2, 1
	str	w2, [x29, 108]
	bl	HEVC_ue_v
	ldr	x1, .LC457
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldrb	w0, [x22, 2]
	cbz	w0, .L2133
	ldr	x1, .LC459
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC461
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	b	.L2133
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	3
.LC449:
	.xword	.LC448
	.align	3
.LC451:
	.xword	.LC450
	.align	3
.LC453:
	.xword	.LC452
	.align	3
.LC455:
	.xword	.LC454
	.align	3
.LC457:
	.xword	.LC456
	.align	3
.LC459:
	.xword	.LC458
	.align	3
.LC461:
	.xword	.LC460
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_ParseVPSExtension, %function
HEVC_ParseVPSExtension:
	sub	sp, sp, #672
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x28, x19, 12288
	add	x4, x29, 312
	add	x0, x29, 200
	add	x21, x28, 132
	mov	x2, 12492
	mov	w1, 0
	str	xzr, [x29, 184]
	stp	xzr, xzr, [x4]
	add	x4, x29, 328
	stp	xzr, xzr, [x0]
	ldr	x0, .LC462
	stp	xzr, xzr, [x4]
	add	x4, x29, 344
	ldr	x3, [x0, 96]
	mov	x0, x21
	stp	xzr, xzr, [x29, 168]
	stp	xzr, xzr, [x4]
	add	x4, x29, 360
	stp	xzr, xzr, [x4]
	add	x4, x29, 640
	stp	xzr, xzr, [x4]
	add	x4, x29, 656
	stp	xzr, xzr, [x4]
	add	x4, x29, 672
	stp	xzr, xzr, [x4]
	add	x4, x29, 688
	stp	xzr, xzr, [x4]
	add	x4, x29, 704
	stp	xzr, xzr, [x4]
	add	x4, x29, 720
	stp	xzr, xzr, [x4]
	add	x4, x29, 736
	stp	xzr, xzr, [x4]
	add	x4, x29, 752
	stp	xzr, xzr, [x4]
	add	x4, x29, 376
	stp	xzr, xzr, [x4]
	add	x4, x29, 392
	stp	xzr, xzr, [x4]
	add	x4, x29, 408
	stp	xzr, xzr, [x4]
	add	x4, x29, 424
	stp	xzr, xzr, [x4]
	add	x4, x29, 440
	stp	xzr, xzr, [x4]
	add	x4, x29, 456
	stp	xzr, xzr, [x4]
	add	x4, x29, 472
	stp	xzr, xzr, [x4]
	add	x4, x29, 488
	stp	xzr, xzr, [x4]
	add	x4, x29, 504
	stp	xzr, xzr, [x4]
	add	x4, x29, 520
	stp	xzr, xzr, [x4]
	add	x4, x29, 536
	stp	xzr, xzr, [x4]
	add	x4, x29, 552
	stp	xzr, xzr, [x4]
	blr	x3
	ldr	w0, [x19, 8]
	mov	w3, 62
	cmp	w0, w3
	csel	w3, w0, w3, le
	str	w3, [x28, 4248]
	cmp	w3, 1
	bgt	.L2673
	cmp	w3, wzr
	ble	.L2169
	ldrb	w0, [x19, 3]
	cbnz	w0, .L2674
.L2169:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	mov	x21, 0
	mov	w27, 0
	add	x22, x29, 312
	bl	BsGet
	uxtb	w0, w0
	str	w0, [x29, 152]
.L2170:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cmp	w0, wzr
	str	w0, [x22, x21]
	add	x21, x21, 4
	csinc	w27, w27, w27, eq
	cmp	x21, 64
	bne	.L2170
	ldr	w0, [x29, 152]
	mov	x21, 0
	add	x25, x29, 504
	cmp	w0, wzr
	cset	w23, ne
	sub	w24, w27, w23
	cmp	w24, wzr
	ble	.L2175
.L2174:
	ldr	x0, [x20, 2936]
	mov	w1, 3
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x25, x21, lsl 2]
	add	x21, x21, 1
	cmp	w24, w21
	bgt	.L2174
.L2175:
	mov	w3, 0
	mov	w6, 6
	tbnz	w27, #31, .L2173
.L2551:
	cmp	w27, w3
	cset	w0, eq
	tst	w23, w0
	bne	.L2178
	cmp	w3, #1
	bmi	.L2180
	sxtw	x4, w3
	add	x1, x29, 768
	mov	w0, 0
	add	x1, x1, x4, lsl 2
	sub	x1, x1, #4096
	ldr	w2, [x1, 3704]
.L2181:
	add	x1, x29, 768
	add	x1, x1, x0, sxtw 2
	add	w0, w0, 1
	sub	x1, x1, #4096
	cmp	w0, w3
	ldr	w1, [x1, 3832]
	add	w1, w1, 1
	add	w2, w2, w1
	bne	.L2181
	add	x0, x29, 768
	add	x0, x0, x4, lsl 2
	sub	x0, x0, #4096
	str	w2, [x0, 3704]
.L2180:
	add	w3, w3, 1
	cmp	w27, w3
	bge	.L2551
.L2173:
	ldr	w0, [x29, 152]
	cbz	w0, .L2177
	sub	w0, w27, #1
	add	x2, x29, 768
	mov	w1, 5
	add	x0, x2, x0, sxtw 2
	sub	x0, x0, #4096
	ldr	w2, [x0, 3704]
	sub	w1, w1, w2
	str	w1, [x0, 3832]
.L2177:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	x26, x28, 132
	mov	w24, 1
	bl	BsGet
	uxtb	w0, w0
	ldr	w1, [x26, 4116]
	str	w0, [x29, 128]
	cmp	w1, wzr
	ble	.L2192
	str	x19, [x29, 112]
	mov	x21, x26
	mov	w23, w24
	mov	w19, w27
.L2550:
	ldr	w0, [x29, 128]
	cbnz	w0, .L2675
	sxtw	x4, w24
	mov	w0, w24
	add	x1, x21, x4, lsl 2
	str	w24, [x1, 4136]
.L2188:
	add	x1, x21, x0, sxtw 2
	cmp	w19, wzr
	str	w24, [x1, 4144]
	ldr	w1, [x29, 152]
	cbz	w1, .L2189
	ble	.L2193
	add	x1, x29, 640
	ldr	w6, [x29, 376]
	add	x4, x1, x4, lsl 6
	mov	w2, 0
.L2195:
	add	w2, w2, 1
	add	x1, x29, 768
	cmp	w19, w2
	add	x3, x1, x2, sxtw 2
	sub	x3, x3, #4096
	ldr	w3, [x3, 3704]
	lsl	w1, w23, w3
	sub	w1, w1, #1
	and	w1, w1, w0
	asr	w1, w1, w6
	str	w1, [x4], 4
	mov	w6, w3
	bne	.L2195
.L2193:
	ldr	w0, [x21, 4116]
	add	w24, w24, 1
	cmp	w0, w24
	bge	.L2550
.L2683:
	ldr	x19, [x29, 112]
.L2192:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	ldr	w6, [x28, 4248]
	add	x7, x28, 132
	mov	w23, w0
	tbnz	w6, #31, .L2676
	ldr	w8, [x29, 312]
	mov	w21, 1
	mov	w5, 0
	add	x9, x19, 16384
.L2202:
	sxtw	x4, w5
	mov	w3, w8
	mov	x0, 0
	mov	w2, 0
	add	x1, x7, x4, lsl 2
	lsl	x4, x4, 4
	ldrsw	x10, [x1, 4136]
	add	x1, x29, 768
	add	x1, x1, x10, lsl 2
	sub	x1, x1, #4096
	str	w8, [x1, 3496]
	b	.L2198
	.p2align 3
.L2677:
	ldr	w3, [x22, x0]
.L2198:
	add	x1, x4, x2, sxtw
	cbz	w3, .L2196
	add	x3, x29, 768
	add	w2, w2, 1
	add	x1, x3, x1, lsl 2
	add	x3, x29, 440
	ldr	w1, [x1, -128]
	str	w1, [x3, x0]
.L2196:
	add	x0, x0, 4
	cmp	x0, 64
	bne	.L2677
	add	x0, x29, 768
	ldr	w4, [x29, 444]
	add	x0, x0, x10, lsl 2
	cmp	w5, wzr
	sub	x0, x0, #4096
	str	w4, [x0, 3496]
	ble	.L2199
	sub	w3, w5, #1
	add	x1, x9, 172
	add	x3, x3, 4096
	mov	w2, 1
	add	x3, x3, 44
	add	x3, x19, x3, lsl 2
	.p2align 2
.L2201:
	ldrsw	x0, [x1], 4
	add	x10, x29, 768
	add	x0, x10, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w0, [x0, 3496]
	cmp	w4, w0
	csel	w2, w2, wzr, ne
	cmp	x3, x1
	bne	.L2201
	cmp	w2, wzr
	csinc	w21, w21, w21, eq
.L2199:
	add	w5, w5, 1
	cmp	w5, w6
	ble	.L2202
	cmp	w23, wzr
	ble	.L2203
	cmp	w21, wzr
	ble	.L2203
.L2204:
	add	x22, x19, 16384
	mov	w24, 0
	add	x22, x22, 164
.L2208:
	ldr	x0, [x20, 2936]
	mov	w1, w23
	add	w24, w24, 1
	bl	BsGet
	str	w0, [x22], 4
	cmp	w21, w24
	bgt	.L2208
	ldr	w6, [x28, 4248]
.L2203:
	add	x0, x19, 16384
	cmp	w6, wzr
	str	x0, [x29, 152]
	mov	w25, 1
	add	x23, x28, 132
	ble	.L2213
	str	x28, [x29, 128]
.L2549:
	sxtw	x0, w25
	cmp	w25, wzr
	add	x1, x23, x0, lsl 2
	ldr	w22, [x1, 4136]
	ble	.L2454
	lsl	x0, x0, 1
	sub	w1, w25, #1
	add	x0, x0, 12288
	sxtw	x22, w22
	add	x24, x0, 138
	add	x0, x0, 137
	add	x21, x19, x0
	ldr	x0, [x29, 152]
	add	x24, x24, x1
	mov	w28, 0
	add	x24, x19, x24
	lsl	x26, x22, 1
	add	x27, x0, 172
	.p2align 2
.L2211:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	x21, x21, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, -1]
	add	x1, x26, x28, sxtw
	add	x1, x1, 1044
	cmp	x21, x24
	cbz	w0, .L2210
	ldr	w0, [x27]
	add	w28, w28, 1
	str	w0, [x23, x1, lsl 2]
.L2210:
	add	x27, x27, 4
	bne	.L2211
	add	x22, x22, 1040
	add	w25, w25, 1
	str	w28, [x23, x22, lsl 2]
	ldr	w0, [x23, 4116]
	cmp	w0, w25
	bge	.L2549
.L2693:
	ldr	x28, [x29, 128]
.L2213:
	ldr	x0, .LC462
	mov	x2, 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 200
	blr	x3
	ldr	w7, [x28, 4248]
	add	x10, x28, 132
	mov	w11, 0
	tbnz	w7, #31, .L2458
	mov	x13, 16596
	mov	x12, 4150
	mov	w9, 1
.L2548:
	add	x0, x10, x11, sxtw 2
	ldr	w0, [x0, 4136]
	sxtw	x14, w0
	add	x1, x14, 1040
	ldr	w1, [x10, x1, lsl 2]
	cmp	w1, wzr
	ble	.L2222
	add	x8, x12, x0, sxtw 1
	sub	w1, w1, #1
	add	x8, x8, x1
	add	x1, x29, 768
	add	x3, x1, x14, lsl 3
	add	x0, x13, x0, sxtw 3
	add	x2, x19, x0
	add	x8, x19, x8, lsl 2
	lsl	x14, x14, 1
	sub	x3, x3, #4096
	.p2align 2
.L2221:
	ldrsw	x0, [x2]
	add	x15, x29, 768
	add	x4, x29, 768
	mov	w6, 1
	add	x1, x14, x0
	mov	w5, w6
	add	x4, x4, x0, lsl 3
	add	x2, x2, 4
	add	x1, x15, x1, lsl 2
	sub	x4, x4, #4096
	sub	x1, x1, #4096
	mov	x0, x4
	str	w9, [x1, 3528]
	ldr	w1, [x3, 3528]
	cbnz	w1, .L2219
	ldr	w1, [x4, 3528]
	cmp	w1, wzr
	cset	w6, ne
.L2219:
	ldr	w1, [x3, 3532]
	str	w6, [x3, 3528]
	cbnz	w1, .L2220
	ldr	w0, [x0, 3532]
	cmp	w0, wzr
	cset	w5, ne
.L2220:
	cmp	x2, x8
	str	w5, [x3, 3532]
	bne	.L2221
.L2222:
	add	w11, w11, 1
	cmp	w11, w7
	ble	.L2548
	cmp	w7, wzr
	ble	.L2228
	sub	w4, w7, #1
	add	x5, x19, 16384
	add	x4, x4, 4096
	add	x5, x5, 172
	add	x4, x4, 44
	add	x4, x19, x4, lsl 2
.L2226:
	ldr	w3, [x5]
	mov	w2, 0
	add	w1, w3, 1
	cmp	w1, 1
	sxtw	x3, w3
	bgt	.L2223
	.p2align 2
.L2225:
	add	x0, x3, x1, sxtw 1
	add	x6, x29, 768
	add	w1, w1, 1
	add	x0, x6, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w0, [x0, 3528]
	cmp	w0, wzr
	csinc	w2, w2, w2, eq
	cmp	w1, 2
	bne	.L2225
.L2223:
	add	x0, x29, 768
	add	x5, x5, 4
	add	x0, x0, x3, lsl 2
	cmp	x5, x4
	sub	x0, x0, #4096
	str	w2, [x0, 3504]
	bne	.L2226
.L2228:
	mov	w21, 0
	mov	w1, 0
	add	x3, x28, 132
	mov	w4, 1
.L2227:
	add	x0, x3, x1, sxtw 2
	add	x2, x29, 768
	add	x6, x29, 768
	add	x2, x2, x21, sxtw 2
	sub	x2, x2, #4096
	ldrsw	x0, [x0, 4136]
	add	x5, x0, 1040
	add	x0, x6, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w5, [x3, x5, lsl 2]
	cbnz	w5, .L2230
	ldr	w0, [x0, 3504]
	str	w4, [x2, 3512]
	cmp	w0, wzr
	add	w0, w0, 1
	ble	.L2232
	str	w0, [x2, 3512]
.L2232:
	add	w21, w21, 1
.L2230:
	add	w1, w1, 1
	cmp	w1, w7
	ble	.L2227
	cmp	w21, 1
	ble	.L2458
	ldr	x1, .LC467
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 1023
	mov	w22, w0
	bgt	.L2678
	cmp	w0, wzr
	mov	w24, 1
	mov	w23, 0
	ble	.L2229
.L2547:
	cmp	w21, 1
	add	x26, x29, 188
	mov	w25, 1
	ble	.L2240
	.p2align 2
.L2237:
	ldr	w3, [x26]
	mov	w1, 0
	ldr	x0, [x20, 2936]
	add	w3, w3, 1
	cmp	w3, 1
	bls	.L2235
	.p2align 2
.L2236:
	add	w1, w1, 1
	lsl	w2, w24, w1
	cmp	w3, w2
	bhi	.L2236
.L2235:
	add	w25, w25, 1
	bl	BsGet
	cmp	w21, w25
	add	x26, x26, 4
	bne	.L2237
.L2240:
	add	w23, w23, 1
	cmp	w22, w23
	bne	.L2547
.L2229:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2241
	add	x0, x28, 132
	ldr	w2, [x0, 4116]
	tbnz	w2, #31, .L2245
	ldr	w3, [x19, 12]
	mov	w1, 0
.L2247:
	add	x4, x0, x1, sxtw 2
	add	w1, w1, 1
	cmp	w1, w2
	str	w3, [x4, 4168]
	ble	.L2247
.L2245:
	ldr	w8, [x19, 20]
	mov	w7, 0
	add	x3, x28, 132
	tbnz	w8, #31, .L2244
.L2545:
	sxtw	x6, w7
	mov	w2, 0
	lsl	x5, x6, 1
	mov	w0, 0
	add	x6, x19, x6, lsl 2
	ldr	w4, [x6, 8324]
	cbz	w4, .L2251
	.p2align 2
.L2546:
	add	x1, x5, x0, sxtw
	add	w0, w0, 1
	add	x1, x19, x1, lsl 2
	ldrsw	x1, [x1, 132]
	add	x1, x1, 1036
	ldrsw	x1, [x3, x1, lsl 2]
	add	x1, x3, x1, lsl 2
	ldr	w1, [x1, 4168]
	cmp	w2, w1
	csel	w2, w2, w1, ge
	cmp	w0, w4
	bne	.L2546
.L2251:
	add	x6, x6, 20480
	add	w7, w7, 1
	cmp	w7, w8
	str	w2, [x6, 232]
	ble	.L2545
.L2244:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2252
	add	x3, x28, 132
	ldr	w4, [x3, 4116]
	mov	w5, 7
	cmp	w0, w4
	bge	.L2266
.L2265:
	add	w6, w0, 1
	sxtw	x2, w0
	cmp	w6, w4
	mov	w0, w6
	lsl	x2, x2, 1
	bgt	.L2264
.L2544:
	add	x1, x2, x0, sxtw
	add	w0, w0, 1
	cmp	w0, w4
	add	x1, x3, x1, lsl 2
	str	w5, [x1, 12392]
	ble	.L2544
.L2264:
	mov	w0, w6
	cmp	w0, w4
	blt	.L2265
.L2266:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	mov	w21, 2
	bl	BsGet
	strb	w0, [x28, 134]
	ldr	x1, .LC471
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	mov	w1, w0
	ldrb	w0, [x19, 3]
	str	w1, [x29, 144]
	cmp	w0, wzr
	csinc	w21, w21, wzr, ne
	cmp	w1, w21
	blt	.L2271
.L2543:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	w21, w21, w1
	bl	BsGet
	uxtb	w2, w0
	ldr	w3, [x19, 12]
	add	x1, x29, 192
	mov	x0, x20
	bl	HEVC_DecPTL
	ldr	w0, [x29, 144]
	cmp	w0, w21
	bge	.L2543
.L2271:
	ldr	w7, [x19, 20]
	add	x21, x28, 132
	add	w7, w22, w7
	add	w7, w7, 1
	str	w7, [x21, 4112]
	cmp	w7, 1
	ble	.L2679
	ldr	x1, .LC473
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	mov	w22, w0
	ldr	x0, [x20, 2936]
	mov	w1, 2
	bl	BsGet
	str	w0, [x29, 104]
	ldr	w7, [x21, 4112]
	add	w4, w22, w7
	str	w4, [x21, 4120]
	cmp	w4, 1025
	bgt	.L2449
	mov	w0, -1
	cmp	w4, 1
	str	w0, [x21, 4192]
	ble	.L2273
	mov	w0, 1
	str	w0, [x29, 152]
	ldr	w1, [x29, 104]
	mov	w26, w0
	mov	w25, w0
	ldr	w0, [x29, 152]
	cmp	w1, 2
	str	wzr, [x29, 128]
	cset	w1, eq
	cmp	w7, w0
	str	w1, [x29, 100]
	ccmp	w7, 2, 4, le
	mov	x23, -12429
	mov	x27, x28
	sub	x23, x23, x19
	ble	.L2274
.L2682:
	sub	w7, w7, #1
	mov	w1, 0
	cmp	w7, 1
	ldr	x0, [x20, 2936]
	bls	.L2275
.L2276:
	add	w1, w1, 1
	lsl	w2, w26, w1
	cmp	w7, w2
	bhi	.L2276
.L2275:
	ldrsw	x28, [x29, 152]
	bl	BsGet
	add	x1, x27, 132
	add	x2, x28, 1048
	str	w0, [x1, x2, lsl 2]
	ldr	w7, [x27, 4244]
.L2277:
	ldr	w0, [x29, 152]
	cmp	w7, w0
	mov	w21, w0
	bgt	.L2278
	add	x0, x27, x28, lsl 2
	ldr	w21, [x0, 4324]
	add	w21, w21, 1
.L2278:
	ldr	w0, [x19, 20]
	ldr	w1, [x29, 152]
	cmp	w0, w1
	ldr	w1, [x29, 100]
	cset	w0, lt
	orr	w0, w1, w0
	cbnz	w0, .L2279
	sxtw	x0, w21
	mov	w2, 0
	mov	x1, x0
	str	x1, [x29, 112]
	mov	w0, 0
	add	x3, x19, x1, lsl 2
	ldr	w16, [x3, 8324]
	cbz	w16, .L2281
	add	x1, x27, 132
	sub	w5, w16, #1
	add	x1, x1, x28, lsl 1
	ldr	w4, [x29, 104]
	b	.L2542
.L2680:
	cmp	w4, 2
	add	x2, x1, x0, sxtw
	beq	.L2285
	cbnz	w4, .L2283
	strb	w25, [x2, 9]
.L2283:
	add	w0, w0, 1
	cmp	w0, w16
	mov	w2, w0
	bcs	.L2452
.L2542:
	cmp	w4, 1
	bne	.L2680
	add	x6, x1, x0, sxtw
	cmp	w5, w2
	add	w0, w0, 1
	cset	w7, eq
	cmp	w0, w16
	mov	w2, w0
	strb	w7, [x6, 9]
	bcc	.L2542
.L2452:
	ldr	w16, [x3, 8324]
.L2281:
	ldr	w0, [x27, 4252]
	cbz	w0, .L2295
	sub	w0, w0, #1
	mov	x18, 12431
	add	x15, x19, 16384
	add	x14, x27, 141
	add	x18, x18, x0, uxtw 1
	add	x15, x15, 228
	add	x18, x19, x18
	mov	x17, x19
	mov	x22, 132
	.p2align 2
.L2294:
	ldr	w0, [x15]
	add	w0, w0, 1
	add	x1, x19, x0, uxtw 2
	ldr	w9, [x1, 8324]
	cbz	w9, .L2298
	add	x11, x23, x14
	add	x0, x22, x0, uxtw 3
	add	x11, x11, 12288
	add	x10, x19, x0
	mov	x8, x17
	mov	x6, x14
	mov	w7, 0
	add	x11, x11, 2192
	.p2align 2
.L2297:
	ldrb	w0, [x6]
	strb	wzr, [x6, 2050]
	cbz	w0, .L2299
	strb	w25, [x6, 2050]
	ldr	w0, [x8, 132]
	cbz	w7, .L2299
	add	x3, x27, 132
	sub	w4, w7, #1
	add	x0, x3, x0, uxtw 2
	add	x4, x11, x4
	add	x1, x14, 2050
	add	x4, x19, x4
	mov	x2, x10
	ldrsw	x5, [x0, 4144]
	add	x5, x3, x5, lsl 1
	.p2align 2
.L2301:
	ldr	w0, [x2]
	add	x2, x2, 4
	add	x0, x0, 1036
	ldrsw	x0, [x3, x0, lsl 2]
	add	x0, x5, x0
	ldrb	w0, [x0, 5]
	cbz	w0, .L2300
	strb	w25, [x1]
.L2300:
	add	x1, x1, 1
	cmp	x1, x4
	bne	.L2301
.L2299:
	add	w7, w7, 1
	add	x6, x6, 1
	cmp	w9, w7
	add	x8, x8, 4
	bne	.L2297
.L2298:
	add	x14, x14, 2
	add	x15, x15, 4
	cmp	x14, x18
	add	x17, x17, 8
	bne	.L2294
.L2295:
	mov	w3, 0
	mov	w1, 0
	cbz	w16, .L2292
	ldr	x0, [x29, 112]
	add	x4, x27, 132
	ldr	w6, [x29, 128]
	add	x4, x4, x28, lsl 1
	lsl	x5, x0, 1
	.p2align 2
.L2541:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x5, x0
	add	x0, x4, x0
	cmp	w1, w16
	add	x2, x19, x2, lsl 2
	ldrb	w0, [x0, 9]
	cbz	w0, .L2302
	ldr	w6, [x2, 132]
	add	w3, w3, 1
.L2302:
	bne	.L2541
	ldr	x1, [x29, 112]
	add	x0, x27, 132
	add	x28, x0, x28, lsl 1
	ldr	w0, [x29, 144]
	add	x21, x1, 2080
	mov	w24, 0
	lsl	x21, x21, 2
	add	w22, w0, 1
	mov	x0, x21
	str	w3, [x29, 112]
	mov	x21, x19
	str	w6, [x29, 128]
	mov	x19, x0
	.p2align 2
.L2307:
	add	x0, x28, x24, sxtw
	ldrb	w0, [x0, 2059]
	cbz	w0, .L2304
	ldr	w0, [x21, 20]
	cmp	w0, wzr
	ble	.L2304
	cmp	w22, 1
	mov	w1, 0
	ldr	x0, [x20, 2936]
	bls	.L2305
	.p2align 2
.L2306:
	add	w1, w1, 1
	lsl	w2, w26, w1
	cmp	w22, w2
	bhi	.L2306
.L2305:
	bl	BsGet
.L2304:
	add	x0, x21, x19
	add	w24, w24, 1
	ldr	w0, [x0, 4]
	cmp	w0, w24
	bhi	.L2307
	ldr	w3, [x29, 112]
	mov	x19, x21
	cmp	w3, 1
	beq	.L2681
.L2292:
	add	x21, x27, 132
	ldr	w1, [x29, 152]
	ldr	w0, [x21, 4120]
	add	w1, w1, 1
	str	w1, [x29, 152]
	cmp	w0, w1
	ble	.L2308
.L2684:
	ldr	w7, [x21, 4112]
	ldr	w0, [x29, 152]
	cmp	w7, w0
	ccmp	w7, 2, 4, le
	bgt	.L2682
.L2274:
	ldrsw	x28, [x29, 152]
	add	x0, x27, x28, lsl 2
	str	wzr, [x0, 4324]
	b	.L2277
.L2189:
	ble	.L2193
	add	x0, x29, 640
	mov	x25, 0
	add	x26, x0, x4, lsl 6
	add	x27, x29, 504
.L2194:
	ldr	w1, [x27, x25, lsl 2]
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x26, x25, lsl 2]
	add	x25, x25, 1
	cmp	w19, w25
	bgt	.L2194
	ldr	w0, [x21, 4116]
	add	w24, w24, 1
	cmp	w0, w24
	bge	.L2550
	b	.L2683
.L2178:
	add	x0, x29, 768
	add	x0, x0, x3, sxtw 2
	sub	x0, x0, #4096
	str	w6, [x0, 3704]
	b	.L2180
.L2675:
	ldr	x0, [x20, 2936]
	mov	w1, 6
	bl	BsGet
	sxtw	x4, w24
	add	x1, x21, x4, lsl 2
	str	w0, [x1, 4136]
	b	.L2188
.L2279:
	sxtw	x0, w21
	str	x0, [x29, 112]
	add	x24, x19, x0, lsl 2
	ldr	w16, [x24, 8324]
	cbz	w16, .L2281
	add	x22, x27, 132
	mov	w21, 0
	add	x22, x22, x28, lsl 1
	.p2align 2
.L2282:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	add	x1, x22, x21, sxtw
	add	w21, w21, 1
	strb	w0, [x1, 9]
	ldr	w16, [x24, 8324]
	cmp	w16, w21
	bhi	.L2282
	b	.L2281
.L2681:
	ldr	x0, [x29, 128]
	add	x0, x27, x0, sxtw 2
	ldr	w0, [x0, 4292]
	cmp	w0, wzr
	ble	.L2292
	ldr	x0, [x20, 2936]
	mov	w1, w3
	add	x21, x27, 132
	bl	BsGet
	ldr	w1, [x29, 152]
	ldr	w0, [x21, 4120]
	add	w1, w1, 1
	str	w1, [x29, 152]
	cmp	w0, w1
	bgt	.L2684
.L2308:
	ldr	x1, .LC477
	mov	x28, x27
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 255
	str	w0, [x21, 4124]
	bhi	.L2447
.L2310:
	ldr	x27, .LC481
	mov	w22, 0
	ldr	x26, .LC483
	ldr	x25, .LC485
	ldr	x24, .LC487
	b	.L2324
.L2311:
	add	x23, x19, 24576
	add	x21, x29, 216
	add	x23, x23, 252
.L2313:
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 4]
	mov	w1, 16
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2685
	cbz	x23, .L2318
	ldr	w0, [x23, 12]
	str	w0, [x21, 12]
	ldrb	w0, [x23]
	strb	w0, [x21]
	ldr	w0, [x23, 16]
	str	w0, [x21, 16]
	ldr	w0, [x23, 20]
	str	w0, [x21, 20]
.L2318:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2686
	stp	wzr, wzr, [x21, 24]
	stp	wzr, wzr, [x21, 32]
.L2320:
	ldp	w2, w3, [x21, 16]
	cmp	w2, 8
	bhi	.L2322
	cmp	w3, 8
	bls	.L2323
.L2322:
	ldr	x1, .LC489
	mov	w0, 1
	bl	dprint_vfmw
	stp	wzr, wzr, [x21, 16]
.L2323:
	ldr	w0, [x28, 4256]
	add	w22, w22, 1
	cmp	w0, w22
	bcc	.L2687
.L2324:
	cmp	w22, 1
	bgt	.L2311
	mov	x23, 0
	cbz	w22, .L2312
	sub	w0, w22, #1
	sxtw	x0, w0
	lsl	x23, x0, 5
	add	x23, x23, x0, lsl 3
	add	x23, x23, 24576
	add	x23, x19, x23
	add	x23, x23, 252
.L2312:
	sxtw	x0, w22
	lsl	x21, x0, 5
	add	x21, x21, x0, lsl 3
	add	x21, x21, 24576
	add	x21, x19, x21
	add	x21, x21, 252
	b	.L2313
.L2686:
	ldr	x0, [x20, 2936]
	mov	x1, x27
	bl	HEVC_ue_v
	str	w0, [x21, 24]
	mov	x1, x26
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 28]
	mov	x1, x25
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 32]
	mov	x1, x24
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 36]
	b	.L2320
.L2685:
	ldr	x0, [x20, 2936]
	mov	w1, 2
	bl	BsGet
	cmp	w0, 3
	str	w0, [x21, 12]
	beq	.L2688
	cbz	x23, .L2317
	ldrb	w0, [x23]
	strb	w0, [x21]
.L2316:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	str	w0, [x21, 16]
	mov	w1, 4
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x21, 20]
	b	.L2318
.L2687:
	cbnz	w0, .L2689
	ldrb	w1, [x19, 3]
	mov	w0, 0
	cbz	w1, .L2328
.L2448:
	add	x2, x19, 16384
	mov	w3, 0
	add	x2, x2, 188
.L2327:
	add	w3, w3, 1
	str	wzr, [x2], 4
	cmp	w3, w1
	blt	.L2327
.L2326:
	cbz	w0, .L2328
	cmp	w1, wzr
	ldr	w0, [x28, 4248]
	cset	w22, ne
	mov	w21, 1
	cmp	w22, w0
	bgt	.L2335
.L2540:
	ldr	w3, [x28, 4256]
	mov	w1, 0
	ldr	x0, [x20, 2936]
	add	w3, w3, 1
	cmp	w3, 1
	bls	.L2332
.L2333:
	add	w1, w1, 1
	lsl	w2, w21, w1
	cmp	w3, w2
	bhi	.L2333
.L2332:
	bl	BsGet
	add	x1, x28, 132
	add	x2, x1, x22, sxtw 2
	add	w22, w22, 1
	str	w0, [x2, 4152]
	ldr	w0, [x28, 4248]
	cmp	w0, w22
	bge	.L2540
.L2335:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	mov	w23, w1
	add	x21, x28, 132
	mov	x22, x21
	bl	BsGet
	strb	w0, [x28, 133]
	mov	w1, w23
	ldr	x0, [x20, 2936]
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w0, wzr
	bgt	.L2539
	b	.L2331
	.p2align 3
.L2339:
	ldr	w0, [x22, 4116]
	cmp	w0, w23
	blt	.L2331
.L2539:
	sxtw	x21, w23
	add	w23, w23, 1
	add	x0, x22, x21, lsl 2
	ldrsw	x0, [x0, 4136]
	add	x0, x0, 1040
	ldr	w0, [x22, x0, lsl 2]
	cbnz	w0, .L2339
	add	x21, x22, x21
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21, 3]
	ldr	w0, [x22, 4116]
	cmp	w0, w23
	bge	.L2539
.L2331:
	ldr	w0, [x28, 4252]
	mov	w1, 1
	str	w1, [x29, 112]
	cmp	w0, w1
	bls	.L2338
	ldr	x23, .LC497
	str	x28, [x29, 144]
	mov	x28, x19
.L2537:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 144]
	ldr	w3, [x29, 112]
	add	x1, x1, 132
	ldr	w2, [x1, 4112]
	mov	w25, w3
	cmp	w2, w3
	bhi	.L2343
	add	x1, x1, x3, uxtw 2
	ldr	w25, [x1, 4192]
	add	w25, w25, 1
.L2343:
	cmp	w0, wzr
	ldr	x0, [x29, 144]
	uxtw	x1, w25
	mov	w21, 0
	add	x26, x0, 132
	cset	w0, ne
	str	w0, [x29, 152]
	add	x27, x1, 2072
	ldr	x0, [x29, 112]
	lsl	x27, x27, 2
	str	x1, [x29, 128]
	add	x19, x26, x0, uxtw 1
	.p2align 2
.L2352:
	cmp	w21, wzr
	ldr	w1, [x29, 152]
	cset	w0, ne
	tst	w1, w0
	bne	.L2690
	cmp	w21, wzr
	cset	w0, eq
.L2345:
	cbz	w0, .L2346
	ldr	x0, [x29, 128]
	mov	w25, 0
	lsl	x22, x0, 1
	add	x24, x28, x0, lsl 2
	ldr	w3, [x24, 8324]
	cbz	w3, .L2351
	.p2align 2
.L2538:
	uxtw	x0, w25
	add	w25, w25, 1
	add	x1, x19, x0
	ldrb	w1, [x1, 2059]
	cbz	w1, .L2348
	ldrb	w6, [x28, 3]
	add	x0, x22, x0
	mov	x1, x23
	add	x0, x28, x0, lsl 2
	cbnz	w6, .L2349
	ldr	w0, [x0, 132]
	cbz	w0, .L2348
.L2349:
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	w3, [x24, 8324]
.L2348:
	cmp	w25, w3
	bcc	.L2538
.L2351:
	ldr	x1, .LC493
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC495
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
.L2346:
	add	x0, x26, x27
	add	w21, w21, 1
	ldr	w0, [x0, 4]
	cmp	w21, w0
	bls	.L2352
	ldr	w1, [x29, 112]
	ldr	w0, [x26, 4120]
	add	w1, w1, 1
	str	w1, [x29, 112]
	cmp	w1, w0
	bcc	.L2537
	mov	x19, x28
	ldr	x28, [x29, 144]
.L2338:
	ldr	x1, .LC491
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	mov	w23, w0
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2691
	add	x24, x28, 132
	ldrb	w0, [x19, 3]
	mov	w22, 2
	ldr	w1, [x24, 4116]
	cmp	w0, wzr
	csinc	w22, w22, wzr, eq
	cmp	w22, w1
	bgt	.L2354
	add	w23, w23, 2
.L2357:
	cmp	w0, wzr
	sxtw	x25, w22
	cset	w21, eq
	cmp	w21, w22
	add	x25, x24, x25, lsl 1
	blt	.L2536
	b	.L2362
	.p2align 3
.L2360:
	cmp	w21, w22
	bge	.L2362
.L2536:
	add	x0, x25, x21, sxtw
	add	w21, w21, 1
	ldrb	w0, [x0, 5]
	cbz	w0, .L2360
	ldr	x0, [x20, 2936]
	mov	w1, w23
	bl	BsGet
	cmp	w21, w22
	blt	.L2536
.L2362:
	ldr	w0, [x24, 4116]
	add	w22, w22, 1
	cmp	w0, w22
	blt	.L2354
	ldrb	w0, [x19, 3]
	b	.L2357
.L2690:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L2345
.L2691:
	ldr	x0, [x20, 2936]
	add	w1, w23, 2
	bl	BsGet
.L2354:
	ldr	x1, .LC499
	mov	w21, 1
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, wzr
	mov	w22, w0
	ble	.L2366
.L2535:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	cmp	w22, w21
	bge	.L2535
.L2366:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2692
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 672
	ret
.L2454:
	sxtw	x22, w22
	mov	w28, 0
	add	x22, x22, 1040
	add	w25, w25, 1
	str	w28, [x23, x22, lsl 2]
	ldr	w0, [x23, 4116]
	cmp	w0, w25
	bge	.L2549
	b	.L2693
	.p2align 3
.L2328:
	add	x2, x28, 132
	cmp	w1, wzr
	ldr	w3, [x2, 4116]
	cset	w0, ne
	cmp	w0, w3
	bgt	.L2335
	ldr	w1, [x2, 4124]
.L2336:
	add	x4, x2, x0, sxtw 2
	cmp	w0, w1
	csel	w5, w0, w1, ls
	add	w0, w0, 1
	cmp	w0, w3
	str	w5, [x4, 4152]
	ble	.L2336
	b	.L2335
.L2689:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	ldrb	w1, [x19, 3]
	cbnz	w1, .L2448
	b	.L2326
	.p2align 3
.L2317:
	strb	wzr, [x21]
	b	.L2316
.L2688:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21]
	b	.L2316
.L2285:
	add	x1, x27, 132
	add	x1, x1, x28, lsl 1
.L2288:
	ldr	w4, [x29, 152]
	add	x2, x1, x0, sxtw
	orr	w4, w0, w4
	add	w0, w0, 1
	cbnz	w4, .L2287
.L2694:
	strb	w25, [x2, 9]
	cmp	w16, w0
	bls	.L2452
	ldr	w4, [x29, 152]
	add	x2, x1, x0, sxtw
	orr	w4, w0, w4
	add	w0, w0, 1
	cbz	w4, .L2694
.L2287:
	cmp	w0, w16
	bcc	.L2288
	ldr	w16, [x3, 8324]
	b	.L2281
.L2679:
	cmp	w7, 1025
	str	w7, [x21, 4120]
	ble	.L2695
	mov	w4, w7
	mov	w22, 0
.L2449:
	ldr	x2, .LC463
	mov	w6, w22
	ldr	x1, .LC475
	mov	w5, 1025
	mov	w3, 1665
	add	x2, x2, 40
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
	.p2align 3
.L2252:
	add	x24, x28, 132
	ldr	w0, [x24, 4116]
	mov	x25, 0
	str	x19, [x29, 152]
	cmp	w25, w0
	mov	w27, 7
	mov	x19, x20
	bge	.L2696
.L2259:
	add	w20, w25, 1
	cmp	w0, w20
	blt	.L2255
	mov	w21, w20
	lsl	x26, x25, 1
	b	.L2258
.L2256:
	str	w27, [x1, 12392]
	add	w21, w21, 1
	ldr	w0, [x24, 4116]
	cmp	w0, w21
	blt	.L2255
.L2258:
	sxtw	x23, w21
	add	x1, x26, x23
	add	x0, x24, x23, lsl 1
	add	x0, x0, x25
	add	x1, x24, x1, lsl 2
	ldrb	w0, [x0, 5]
	cbz	w0, .L2256
	ldr	x0, [x19, 2936]
	mov	w1, 3
	add	w21, w21, 1
	bl	BsGet
	add	x1, x26, x23
	add	x1, x24, x1, lsl 2
	str	w0, [x1, 12392]
	ldr	w0, [x24, 4116]
	cmp	w0, w21
	bge	.L2258
.L2255:
	sxtw	x25, w20
	cmp	w25, w0
	blt	.L2259
.L2696:
	mov	x20, x19
	ldr	x19, [x29, 152]
	b	.L2266
.L2241:
	add	x21, x28, 132
	ldr	w0, [x21, 4116]
	tbnz	w0, #31, .L2245
	mov	w23, 0
.L2246:
	ldr	x0, [x20, 2936]
	mov	w1, 3
	bl	BsGet
	add	x1, x21, x23, sxtw 2
	add	w23, w23, 1
	str	w0, [x1, 4168]
	ldr	w0, [x21, 4116]
	cmp	w0, w23
	bge	.L2246
	b	.L2245
.L2458:
	mov	w22, 0
	b	.L2229
.L2692:
	ldr	x0, [x20, 2936]
	bl	BsToNextByte
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2697
.L2368:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w26, w0
	orr	w0, w25, w0
	cbz	w0, .L2370
	ldrb	w1, [x19, 3]
	mov	w24, 0
	ldr	w0, [x19, 20]
	mov	w23, 0
	cmp	w1, wzr
	cset	w22, eq
	cmp	w22, w0
	bhi	.L2370
.L2534:
	mov	w21, 0
.L2376:
	add	w21, w21, 1
	cbnz	w25, .L2698
	cbnz	w26, .L2699
.L2373:
	cbnz	w23, .L2700
.L2374:
	cbnz	w24, .L2701
.L2375:
	ldr	w0, [x19, 12]
	cmp	w21, w0
	bls	.L2376
	ldr	w0, [x19, 20]
	add	w22, w22, 1
	cmp	w22, w0
	bls	.L2534
.L2370:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	cbnz	w0, .L2702
	ldr	w21, [x28, 4248]
.L2379:
	mov	w22, 0
.L2380:
	ldr	x0, [x20, 2936]
	mov	w1, 3
	add	w22, w22, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w22, w21
	bls	.L2380
	cmp	w23, wzr
	ccmp	w21, wzr, 4, ne
	beq	.L2384
	ldrb	w1, [x19, 3]
	ldr	w0, [x28, 4248]
	cmp	w1, wzr
	cset	w21, eq
	cmp	w21, w0
	bhi	.L2384
.L2385:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	add	w21, w21, 1
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2385
.L2384:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2383
	mov	w21, 0
.L2387:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	sub	x1, x29, #3328
	add	x1, x1, x21, uxtw
	add	w21, w21, 1
	strb	w0, [x1, 3488]
	cbz	w0, .L2386
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
.L2386:
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2387
	mov	w23, 1
	cbz	w0, .L2383
.L2533:
	uxtw	x1, w23
	add	x22, x19, x1, lsl 2
	add	x22, x22, 16384
	ldrsw	x0, [x22, 172]
	add	x2, x28, x0, lsl 2
	ldr	w2, [x2, 4292]
	cbz	w2, .L2392
	sub	x2, x29, #3328
	mov	w21, 0
	add	x1, x2, x1
	ldrb	w24, [x1, 3488]
	b	.L2390
.L2389:
	ldrsw	x0, [x22, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w21, w1
	bcs	.L2392
.L2390:
	lsl	x0, x0, 1
	add	x1, x28, 132
	add	x0, x0, x21, uxtw
	add	w21, w21, 1
	add	x0, x0, 1044
	cbz	w24, .L2389
	ldrsw	x0, [x1, x0, lsl 2]
	add	x0, x0, 1036
	ldr	w0, [x1, x0, lsl 2]
	sub	x1, x29, #3328
	add	x0, x1, x0
	ldrb	w0, [x0, 3488]
	cbz	w0, .L2389
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldrsw	x0, [x22, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w21, w1
	bcc	.L2390
.L2392:
	ldr	w0, [x28, 4248]
	add	w23, w23, 1
	cmp	w23, w0
	bls	.L2533
.L2383:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2393
.L2397:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2395
	ldr	w0, [x28, 4248]
	mov	w26, 0
	mov	w22, 1
	cbz	w0, .L2395
	ldr	x23, .LC501
	ldr	x24, .LC503
.L2531:
	add	x21, x19, x22, uxtw 2
	mov	w25, 0
	add	x21, x21, 16384
	ldrsw	x0, [x21, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cbz	w1, .L2407
.L2532:
	lsl	x0, x0, 1
	ldrb	w2, [x19, 3]
	add	x0, x0, x25, uxtw
	mov	x1, x23
	add	w25, w25, 1
	add	x0, x28, x0, lsl 2
	cbnz	w2, .L2399
	ldr	w0, [x0, 4308]
	cmp	w0, wzr
	ble	.L2400
.L2399:
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	mov	w26, w0
.L2400:
	cbnz	w26, .L2703
.L2402:
	ldrsw	x0, [x21, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w25, w1
	bcc	.L2532
.L2407:
	ldr	w0, [x28, 4248]
	add	w22, w22, 1
	cmp	w22, w0
	bls	.L2531
.L2395:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2704
.L2408:
	add	x19, x28, 132
	ldr	w0, [x19, 4116]
	mov	w21, 1
	cbnz	w0, .L2530
	b	.L2446
	.p2align 3
.L2444:
	ldr	w0, [x19, 4116]
	cmp	w21, w0
	bhi	.L2446
.L2530:
	add	x0, x19, x21, uxtw 2
	add	w21, w21, 1
	ldrsw	x0, [x0, 4136]
	add	x0, x0, 1040
	ldr	w0, [x19, x0, lsl 2]
	cbnz	w0, .L2444
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	w0, [x19, 4116]
	cmp	w21, w0
	bls	.L2530
.L2446:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, 0
	add	sp, sp, 672
	ret
.L2700:
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	cbz	w24, .L2375
.L2701:
	ldr	x0, [x20, 2936]
	mov	w1, 2
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 2
	bl	BsGet
	b	.L2375
.L2699:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w24, w0
	cbz	w23, .L2374
	b	.L2700
.L2698:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	cbz	w26, .L2373
	b	.L2699
.L2703:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2402
	ldr	x0, [x20, 2936]
	mov	x1, x24
	bl	HEVC_ue_v
	b	.L2402
.L2393:
	mov	w21, 0
.L2396:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	w21, w21, w1
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2396
	b	.L2397
.L2678:
	ldr	x2, .LC463
	mov	w4, w0
	ldr	x1, .LC469
	mov	w5, 1024
	mov	w3, 1567
	add	x2, x2, 40
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2676:
	cmp	w0, wzr
	mov	w21, 1
	bgt	.L2204
	b	.L2203
.L2674:
	ldr	w3, [x19, 12]
	mov	w2, 0
	add	x1, x29, 192
	mov	x0, x20
	bl	HEVC_DecPTL
	b	.L2169
.L2673:
	ldr	x2, .LC463
	mov	w4, 1
	ldr	x1, .LC465
	mov	w0, w4
	add	x2, x2, 40
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2695:
	mov	w0, -1
	str	w0, [x21, 4192]
.L2273:
	ldr	x1, .LC477
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 255
	str	w0, [x28, 4256]
	bls	.L2310
.L2447:
	ldr	x1, .LC479
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2704:
	ldr	x1, .LC505
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	w21, [x19, 24]
	add	w25, w0, w21
	cmp	w25, 1024
	bhi	.L2409
	cmp	w21, w25
	bcs	.L2416
	ldr	x23, .LC509
	b	.L2415
	.p2align 3
.L2706:
	ldr	x0, [x20, 2936]
	bl	BsGet
	mov	w22, w0
.L2413:
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_ue_v
	mov	w5, w0
	cmp	w5, 7
	mov	w3, w0
	mov	w2, w22
	add	x1, x29, 256
	mov	x0, x20
	bhi	.L2705
	bl	HEVC_DecHrdParam
	add	w21, w21, 1
	cmp	w25, w21
	bls	.L2416
.L2415:
	mov	w1, 1
	cbnz	w21, .L2706
	mov	w22, 1
	b	.L2413
.L2705:
	ldr	x1, .LC511
	mov	w4, 7
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2408
.L2416:
	cbz	w25, .L2408
	ldr	w0, [x28, 4252]
	cmp	w0, 1
	bls	.L2408
	mov	w21, 1
	ldr	x23, .LC523
	mov	w24, w25
	mov	w22, w21
	mov	x25, x19
.L2442:
	add	x27, x25, x21, uxtw 2
	ldr	w0, [x27, 8324]
	cmp	w0, 2
	bls	.L2418
	sub	w0, w0, #1
	str	w0, [x29, 568]
.L2419:
	ldr	x1, .LC513
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 16
	bhi	.L2420
	add	w0, w0, 1
	str	w0, [x29, 112]
	cmp	w0, 1
	add	x0, x29, 572
	str	x0, [x29, 152]
	mov	w0, 1
	str	w0, [x29, 128]
	bls	.L2431
.L2430:
	ldr	x1, .LC517
	mov	w26, 0
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x29, 144]
	ldr	x1, [x29, 152]
	ldr	w4, [x28, 4244]
	str	w0, [x1]
.L2425:
	mov	w19, 0
	b	.L2429
.L2427:
	ldr	x0, [x20, 2936]
	bl	BsGet
	ldr	w4, [x28, 4244]
.L2429:
	cmp	w4, w21
	add	x5, x27, 16384
	mov	w1, 1
	mov	w0, w21
	bhi	.L2426
	ldr	w0, [x5, 228]
	add	w0, w0, w1
.L2426:
	add	x0, x25, x0, uxtw 2
	ldr	w0, [x0, 8324]
	cmp	w19, w0
	add	w19, w19, 1
	bcc	.L2427
	ldr	w0, [x29, 144]
	add	w26, w26, 1
	cmp	w0, w26
	bcs	.L2425
	ldr	x1, [x29, 152]
	ldr	w0, [x29, 128]
	add	x1, x1, 4
	str	x1, [x29, 152]
	ldr	w1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 128]
	cmp	w1, w0
	bne	.L2430
.L2431:
	ldr	w0, [x29, 112]
	cbz	w0, .L2423
	ldr	w1, [x28, 4244]
	add	x0, x28, 132
	str	xzr, [x29, 128]
	str	x0, [x29, 104]
.L2432:
	ldr	w0, [x29, 128]
	str	w0, [x29, 96]
	str	wzr, [x29, 152]
.L2441:
	cmp	w1, w21
	mov	w0, w21
	bhi	.L2439
	add	x0, x27, 16384
	ldr	w0, [x0, 228]
	add	w0, w0, 1
.L2439:
	ldr	x2, [x29, 104]
	add	x0, x2, x0, uxtw 2
	ldr	w2, [x29, 152]
	ldr	w0, [x0, 8292]
	cmp	w2, w0
	bhi	.L2707
	ldr	x1, .LC519
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 31
	bhi	.L2433
	add	w0, w0, 1
	add	x1, x29, 568
	str	w0, [x29, 100]
	ldr	x0, [x29, 128]
	str	wzr, [x29, 144]
	ldr	w26, [x1, x0, lsl 2]
.L2434:
	mov	w19, 0
.L2437:
	cmp	w24, 1
	mov	w1, 0
	ldr	x0, [x20, 2936]
	bls	.L2435
	.p2align 2
.L2436:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w24, w2
	bhi	.L2436
.L2435:
	bl	BsGet
	add	w19, w19, 1
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_ue_v
	cmp	w26, w19
	bcs	.L2437
	ldr	w0, [x29, 144]
	ldr	w1, [x29, 100]
	add	w0, w0, 1
	str	w0, [x29, 144]
	cmp	w0, w1
	bne	.L2434
	ldr	w0, [x29, 152]
	add	w0, w0, 1
	str	w0, [x29, 152]
	ldr	x0, [x29, 104]
	ldr	w1, [x0, 4112]
	b	.L2441
.L2433:
	ldr	x1, .LC521
	mov	w5, w0
	ldr	w3, [x29, 96]
	mov	w2, w21
	ldr	w4, [x29, 152]
	mov	w0, 1
	bl	dprint_vfmw
.L2424:
	ldr	x1, .LC525
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2408
.L2707:
	ldr	x0, [x29, 128]
	ldr	w2, [x29, 112]
	add	x0, x0, 1
	str	x0, [x29, 128]
	cmp	w2, w0
	bhi	.L2432
.L2423:
	ldr	w0, [x28, 4252]
	add	w21, w21, 1
	cmp	w21, w0
	bcc	.L2442
	b	.L2408
.L2420:
	ldr	x1, .LC515
	mov	w3, w0
	mov	w4, 16
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2424
.L2418:
	str	w22, [x29, 568]
	b	.L2419
.L2409:
	ldr	x1, .LC507
	mov	w3, 1024
	mov	w2, w25
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2408
.L2702:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	mov	w21, w0
	b	.L2379
.L2697:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2368
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L2368
	.size	HEVC_ParseVPSExtension, .-HEVC_ParseVPSExtension
	.align	3
.LC462:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC463:
	.xword	.LANCHOR5
	.align	3
.LC465:
	.xword	.LC464
	.align	3
.LC467:
	.xword	.LC466
	.align	3
.LC469:
	.xword	.LC468
	.align	3
.LC471:
	.xword	.LC470
	.align	3
.LC473:
	.xword	.LC472
	.align	3
.LC475:
	.xword	.LC474
	.align	3
.LC477:
	.xword	.LC476
	.align	3
.LC479:
	.xword	.LC478
	.align	3
.LC481:
	.xword	.LC480
	.align	3
.LC483:
	.xword	.LC482
	.align	3
.LC485:
	.xword	.LC484
	.align	3
.LC487:
	.xword	.LC486
	.align	3
.LC489:
	.xword	.LC488
	.align	3
.LC491:
	.xword	.LC490
	.align	3
.LC493:
	.xword	.LC492
	.align	3
.LC495:
	.xword	.LC494
	.align	3
.LC497:
	.xword	.LC496
	.align	3
.LC499:
	.xword	.LC498
	.align	3
.LC501:
	.xword	.LC500
	.align	3
.LC503:
	.xword	.LC502
	.align	3
.LC505:
	.xword	.LC504
	.align	3
.LC507:
	.xword	.LC506
	.align	3
.LC509:
	.xword	.LC508
	.align	3
.LC511:
	.xword	.LC510
	.align	3
.LC513:
	.xword	.LC512
	.align	3
.LC515:
	.xword	.LC514
	.align	3
.LC517:
	.xword	.LC516
	.align	3
.LC519:
	.xword	.LC518
	.align	3
.LC521:
	.xword	.LC520
	.align	3
.LC523:
	.xword	.LC522
	.align	3
.LC525:
	.xword	.LC524
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 1
	ldr	x0, [x21, 2936]
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2709
	ldr	x1, .LC527
	uxtb	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
.L2709:
	ldr	x0, [x21, 2936]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 63
	str	w0, [x20, 8]
	bhi	.L2769
	ldr	x0, [x21, 2936]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 7
	mov	w25, w0
	bhi	.L2770
	str	w0, [x20, 12]
	mov	w1, 1
	ldr	x0, [x21, 2936]
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 16
	ldr	x0, [x21, 2936]
	bl	BsGet
	mov	w1, 65535
	cmp	w0, w1
	bne	.L2771
	mov	w3, w25
	mov	w2, 1
	add	x1, x20, 124
	mov	x0, x21
	bl	HEVC_DecPTL
	cbnz	w0, .L2772
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w28, w0
	tbnz	w25, #31, .L2719
	ldr	x27, .LC537
	add	w23, w25, 1
	ldr	x26, .LC539
	mov	w19, 0
	ldr	x24, .LC541
	b	.L2721
	.p2align 3
.L2718:
	cmp	w23, w19
	beq	.L2719
.L2721:
	add	x22, x20, x19, sxtw 2
	ldr	x0, [x21, 2936]
	mov	x1, x27
	add	w19, w19, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 28]
	mov	x1, x26
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	str	w0, [x22, 60]
	mov	x1, x24
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	str	w0, [x22, 92]
	cbnz	w28, .L2718
	cmp	w25, w19
	blt	.L2719
	.p2align 2
.L2755:
	add	x0, x20, x19, sxtw 2
	ldr	w1, [x20, 28]
	add	w19, w19, 1
	cmp	w23, w19
	str	w1, [x0, 28]
	ldr	w1, [x20, 60]
	str	w1, [x0, 60]
	ldr	w1, [x20, 92]
	str	w1, [x0, 92]
	bne	.L2755
.L2719:
	ldr	x0, [x21, 2936]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 1
	str	w0, [x20, 16]
	bhi	.L2773
	ldr	w1, [x20, 8]
	sub	w1, w1, #1
	cmp	w1, 61
	ccmp	w0, wzr, 4, ls
	bne	.L2774
.L2722:
	ldr	x1, .LC547
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	cmp	w0, 1023
	str	w0, [x20, 20]
	bhi	.L2775
	ldr	x19, .LC550
	mov	x2, 8192
	mov	w1, 0
	add	x0, x20, 132
	mov	w24, 1
	ldr	x3, [x19, 96]
	blr	x3
	add	x0, x20, 8192
	ldr	x3, [x19, 96]
	mov	x2, 4096
	mov	w1, 0
	add	x0, x0, 132
	blr	x3
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L2725
	.p2align 2
.L2754:
	sxtw	x23, w24
	mov	w19, 0
	mov	w26, 0
	lsl	x22, x23, 1
	.p2align 2
.L2727:
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	add	x1, x22, x26, uxtw
	add	x1, x20, x1, lsl 2
	cbz	w0, .L2726
	add	w26, w26, 1
	str	w19, [x1, 132]
.L2726:
	ldr	w0, [x20, 16]
	add	w19, w19, 1
	cmp	w19, w0
	bls	.L2727
	add	x23, x20, x23, lsl 2
	add	w24, w24, 1
	str	w26, [x23, 8324]
	ldr	w0, [x20, 20]
	cmp	w24, w0
	ble	.L2754
.L2725:
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2735
	ldr	x0, [x21, 2936]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x21, 2936]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2776
.L2732:
	ldr	x1, .LC554
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	cmp	w0, 1024
	str	w0, [x20, 24]
	bhi	.L2733
	cmp	w0, wzr
	ble	.L2735
	ldr	x22, .LC558
	mov	w19, 0
	ldr	x0, [x21, 2936]
	mov	x1, x22
	bl	HEVC_ue_v
	mov	w2, 1
	.p2align 2
.L2744:
	mov	w3, w25
	add	x1, x29, 104
	mov	x0, x21
	add	w19, w19, 1
	bl	HEVC_DecHrdParam
	cbnz	w0, .L2777
.L2737:
	ldr	w0, [x20, 24]
	mov	x1, x22
	cmp	w0, w19
	ble	.L2735
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	mov	w2, 1
	cbz	w19, .L2744
	ldr	x0, [x21, 2936]
	mov	w1, w2
	add	w19, w19, 1
	bl	BsGet
	mov	w2, w0
	mov	w3, w25
	add	x1, x29, 104
	mov	x0, x21
	bl	HEVC_DecHrdParam
	cbz	w0, .L2737
.L2777:
	ldr	x1, .LC560
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2735:
	ldr	x0, [x21, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2731
	ldrb	w19, [x21, 1]
	cmp	w19, 1
	bne	.L2740
	b	.L2778
	.p2align 3
.L2779:
	ldr	x0, [x21, 2936]
	bl	BsGet
.L2740:
	ldr	x0, [x21, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2731
	ldr	x2, [x21, 2976]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L2779
.L2731:
	mov	w0, 0
.L2765:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2776:
	ldr	x1, .LC552
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	b	.L2732
.L2774:
	ldr	x1, .LC545
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
	strb	w0, [x21, 1]
	b	.L2722
.L2771:
	ldr	x1, .LC533
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2778:
	ldr	x0, [x21, 2936]
	bl	BsToNextByte
	mov	x1, x20
	mov	x0, x21
	bl	HEVC_ParseVPSExtension
	cbnz	w0, .L2780
	ldr	x0, [x21, 2936]
	mov	w1, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2731
	b	.L2740
	.p2align 3
.L2770:
	ldr	x1, .LC531
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2769:
	ldr	x1, .LC529
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2773:
	mov	w2, 1
	ldr	x1, .LC543
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2772:
	ldr	x1, .LC535
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2775:
	ldr	x1, .LC549
.L2767:
	mov	w2, w0
	mov	w3, 1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
.L2733:
	ldr	x1, .LC556
	b	.L2767
.L2780:
	ldr	x1, .LC562
	mov	w0, w19
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2765
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	3
.LC527:
	.xword	.LC526
	.align	3
.LC529:
	.xword	.LC528
	.align	3
.LC531:
	.xword	.LC530
	.align	3
.LC533:
	.xword	.LC532
	.align	3
.LC535:
	.xword	.LC534
	.align	3
.LC537:
	.xword	.LC536
	.align	3
.LC539:
	.xword	.LC538
	.align	3
.LC541:
	.xword	.LC540
	.align	3
.LC543:
	.xword	.LC542
	.align	3
.LC545:
	.xword	.LC544
	.align	3
.LC547:
	.xword	.LC546
	.align	3
.LC549:
	.xword	.LC548
	.align	3
.LC550:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC552:
	.xword	.LC551
	.align	3
.LC554:
	.xword	.LC553
	.align	3
.LC556:
	.xword	.LC555
	.align	3
.LC558:
	.xword	.LC557
	.align	3
.LC560:
	.xword	.LC559
	.align	3
.LC562:
	.xword	.LC561
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	cmp	w0, 15
	mov	w21, w0
	bhi	.L2787
	mov	w19, 24912
	umull	x19, w0, w19
	ldr	x0, [x20, 2944]
	add	x1, x0, x19
	ldrb	w0, [x0, x19]
	cbnz	w0, .L2788
	str	w21, [x1, 4]
	mov	x0, x20
	ldr	x1, [x20, 2944]
	add	x1, x1, x19
	bl	HEVC_ProcessVPS
	mov	w22, w0
	cbnz	w0, .L2789
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2944]
	strb	w1, [x0, x19]
.L2783:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2788:
	ldr	x25, .LC565
	mov	x2, 24912
	ldr	x24, .LC566
	mov	w1, 0
	add	x23, x24, 3328
	ldr	x3, [x25, 96]
	mov	x0, x23
	blr	x3
	str	w21, [x23, 4]
	mov	x1, x23
	mov	x0, x20
	bl	HEVC_ProcessVPS
	mov	w22, w0
	cbnz	w0, .L2790
	ldr	x0, [x20, 2944]
	mov	w1, 1
	ldr	x3, [x25, 112]
	mov	x2, 24912
	strb	w1, [x23, 2]
	add	x0, x0, x19
	strb	w1, [x24, 3328]
	mov	x1, x23
	blr	x3
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2790:
	ldr	x1, .LC568
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2783
	.p2align 3
.L2787:
	ldr	x1, .LC564
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2783
.L2789:
	ldr	x1, .LC570
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2944]
	strb	wzr, [x0, x19]
	b	.L2783
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	3
.LC564:
	.xword	.LC563
	.align	3
.LC565:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC566:
	.xword	.LANCHOR6
	.align	3
.LC568:
	.xword	.LC567
	.align	3
.LC570:
	.xword	.LC569
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2836
.L2793:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2837
.L2795:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2838
.L2797:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2839
.L2799:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 1
	ldr	x0, [x19, 2936]
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2800
	ldr	x1, .LC577
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	w0, [x21, 60]
	cmp	w0, 3
	bhi	.L2840
	ldr	x1, .LC581
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC583
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC585
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
.L2800:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2803
	ldr	x0, [x19, 2936]
	mov	w1, 32
	bl	BsGet
	str	w0, [x20, 36]
	mov	w1, 32
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x20, 40]
	ldr	w1, [x20, 36]
	cbnz	w1, .L2841
.L2804:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2842
.L2805:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2843
.L2803:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	mov	w0, 0
	cbnz	w1, .L2844
.L2802:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2844:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC592
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	cmp	w0, 4095
	bhi	.L2845
.L2806:
	ldr	x1, .LC596
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC598
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC600
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC602
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2839:
	ldr	x1, .LC573
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC575
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	b	.L2799
	.p2align 3
.L2836:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	str	w0, [x20, 8]
	bne	.L2793
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsGet
	str	w0, [x20, 12]
	mov	w1, 16
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x20, 16]
	b	.L2793
	.p2align 3
.L2838:
	ldr	x0, [x19, 2936]
	mov	w1, 3
	bl	BsGet
	str	w0, [x20, 20]
	mov	w1, 1
	ldr	x0, [x19, 2936]
	bl	BsGet
	strb	w0, [x20]
	mov	w1, 1
	ldr	x0, [x19, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2797
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x20, 28]
	mov	w1, 8
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x20, 32]
	b	.L2797
	.p2align 3
.L2837:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L2795
	.p2align 3
.L2843:
	ldr	w3, [x21, 52]
	mov	w2, 1
	add	x1, x20, 44
	mov	x0, x19
	bl	HEVC_DecHrdParam
	cbz	w0, .L2803
	ldr	x1, .LC590
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2802
	.p2align 3
.L2842:
	ldr	x1, .LC588
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	b	.L2805
	.p2align 3
.L2841:
	ldr	x2, .LC586
	mov	w3, 10000
	umull	x0, w0, w3
	ldr	x2, [x2, 472]
	blr	x2
	add	w0, w0, 5
	mov	w1, 52429
	movk	w1, 0xcccc, lsl 16
	umull	x0, w0, w1
	lsr	x0, x0, 35
	str	w0, [x19, 144]
	b	.L2804
	.p2align 3
.L2845:
	ldr	x1, .LC594
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2806
	.p2align 3
.L2840:
	ldr	x1, .LC579
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2802
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	3
.LC573:
	.xword	.LC572
	.align	3
.LC575:
	.xword	.LC574
	.align	3
.LC577:
	.xword	.LC576
	.align	3
.LC579:
	.xword	.LC578
	.align	3
.LC581:
	.xword	.LC580
	.align	3
.LC583:
	.xword	.LC582
	.align	3
.LC585:
	.xword	.LC584
	.align	3
.LC586:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC588:
	.xword	.LC587
	.align	3
.LC590:
	.xword	.LC589
	.align	3
.LC592:
	.xword	.LC591
	.align	3
.LC594:
	.xword	.LC593
	.align	3
.LC596:
	.xword	.LC595
	.align	3
.LC598:
	.xword	.LC597
	.align	3
.LC600:
	.xword	.LC599
	.align	3
.LC602:
	.xword	.LC601
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L2851
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2851:
	mov	w1, w0
	mov	x0, x20
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	sub	w0, w0, #1
	asr	w2, w0, 1
	and	w0, w0, 1
	cmp	w0, wzr
	mov	w1, w21
	mov	x0, x20
	neg	w19, w2
	csinc	w19, w19, w2, eq
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_se_v, .-HEVC_se_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC604
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC606
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
	cmp	w0, 1024
	mov	w22, w0
	bhi	.L2853
	mov	w19, 0
	cbz	w0, .L2859
	ldr	x24, .LC610
	ldr	x23, .LC612
	.p2align 2
.L2862:
	ldr	x0, [x21, 2936]
	mov	w1, 6
	bl	BsGet
	sub	w20, w0, #19
	ldr	x0, [x21, 2936]
	mov	w1, 3
	bl	BsGet
	cmp	w20, 1
	mov	x1, x24
	bls	.L2856
	ldr	x0, [x21, 2936]
	bl	HEVC_ue_v
.L2856:
	mov	x1, x23
	cbz	w19, .L2857
	ldr	x0, [x21, 2936]
	bl	HEVC_se_v
.L2857:
	add	w19, w19, 1
	cmp	w22, w19
	bne	.L2862
.L2859:
	ldr	x0, [x21, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L2855:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2853:
	ldr	x1, .LC608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2855
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	3
.LC604:
	.xword	.LC603
	.align	3
.LC606:
	.xword	.LC605
	.align	3
.LC608:
	.xword	.LC607
	.align	3
.LC610:
	.xword	.LC609
	.align	3
.LC612:
	.xword	.LC611
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L2867
	ldr	x1, .LC614
	ldr	x0, [x19, 2936]
	bl	HEVC_se_v
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
	mov	w0, 0
.L2866:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2867:
	mov	w0, -1
	b	.L2866
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	3
.LC614:
	.xword	.LC613
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Remapping_Info
	.type	HEVC_Sei_Color_Remapping_Info, %function
HEVC_Sei_Color_Remapping_Info:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2886
	ldr	x1, .LC616
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2870
.L2883:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x22]
.L2869:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2870:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2894
.L2871:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	mov	w23, 3
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
.L2873:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	uxtb	w1, w0
	cbz	w1, .L2876
	and	w0, w0, 255
	mov	w19, 0
	add	w21, w0, 1
	.p2align 2
.L2875:
	ldr	x0, [x20, 2936]
	mov	w1, 16
	add	w19, w19, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 16
	bl	BsGet
	cmp	w21, w19
	bne	.L2875
.L2876:
	subs	w23, w23, #1
	bne	.L2873
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2877
.L2881:
	add	x26, x22, 3
	mov	x23, x22
	mov	w25, 33
.L2878:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	sub	w24, w23, w22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 40]
	cbz	w0, .L2885
	mov	w21, 0
	.p2align 2
.L2884:
	uxtw	x19, w21
	ldr	x0, [x20, 2936]
	mov	w1, 16
	add	w21, w21, 1
	umaddl	x19, w24, w25, x19
	bl	BsGet
	mov	w1, 16
	add	x19, x22, x19, lsl 1
	strh	w0, [x19, 44]
	ldr	x0, [x20, 2936]
	bl	BsGet
	strh	w0, [x19, 242]
	ldrb	w0, [x23, 40]
	add	w0, w0, 1
	cmp	w0, w21
	bhi	.L2884
.L2885:
	add	x23, x23, 1
	cmp	x23, x26
	bne	.L2878
	b	.L2883
	.p2align 3
.L2886:
	mov	w0, -1
	b	.L2869
.L2877:
	ldr	x0, [x20, 2936]
	mov	w1, 4
	add	x19, x22, 4
	add	x24, x22, 40
	bl	BsGet
	ldr	x23, .LC618
.L2879:
	add	x21, x19, 12
.L2880:
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_se_v
	str	w0, [x19], 4
	cmp	x19, x21
	bne	.L2880
	cmp	x19, x24
	bne	.L2879
	b	.L2881
.L2894:
	ldr	x0, [x20, 2936]
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 8
	ldr	x0, [x20, 2936]
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	b	.L2871
	.size	HEVC_Sei_Color_Remapping_Info, .-HEVC_Sei_Color_Remapping_Info
	.align	3
.LC616:
	.xword	.LC615
	.align	3
.LC618:
	.xword	.LC617
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	x23, x2
	mov	w20, w3
	mov	w21, w4
	bl	_mcount
	ldr	x0, [x19, 2976]
	ldr	w0, [x0, 16]
	cmp	w0, 39
	beq	.L2944
	cmp	w20, 5
	beq	.L2924
	cmp	w20, 132
	beq	.L2925
	mov	w20, 0
	cbz	w21, .L2918
	.p2align 2
.L2938:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2938
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbnz	w0, .L2928
	.p2align 2
.L2932:
	mov	w0, 0
.L2920:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2924:
	mov	w2, w21
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Unregistered
	cbnz	w0, .L2921
.L2918:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbz	w0, .L2932
.L2928:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_Payload_Extension_Present
	cbnz	w0, .L2945
	.p2align 2
.L2931:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	bl	BsIsByteAligned
	cbz	w0, .L2931
	b	.L2932
	.p2align 3
.L2944:
	cmp	w20, 147
	bls	.L2946
.L2897:
	mov	w20, 0
	cbz	w21, .L2918
	.p2align 2
.L2937:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2937
	b	.L2918
	.p2align 3
.L2925:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Decoded_Picture_Hash
	cbz	w0, .L2918
	.p2align 2
.L2921:
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2946:
	ldr	x0, .LC619
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx2899
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2899:
	.section	.rodata
	.align	0
	.align	2
.L2899:
	.byte	(.L2898 - .Lrtx2899) / 4
	.byte	(.L2900 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2901 - .Lrtx2899) / 4
	.byte	(.L2924 - .Lrtx2899) / 4
	.byte	(.L2903 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2904 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2905 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2906 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2907 - .Lrtx2899) / 4
	.byte	(.L2908 - .Lrtx2899) / 4
	.byte	(.L2909 - .Lrtx2899) / 4
	.byte	(.L2910 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2911 - .Lrtx2899) / 4
	.byte	(.L2912 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2913 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2914 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2915 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2897 - .Lrtx2899) / 4
	.byte	(.L2916 - .Lrtx2899) / 4
	.text
	.p2align 3
.L2945:
	ldr	x1, .LC621
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	b	.L2931
.L2916:
	add	x0, x22, 618
	cmp	x19, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L2921
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 618]
	b	.L2918
.L2915:
	add	x1, x22, 612
	mov	x0, x19
	bl	HEVC_Sei_Content_Light_Level_Information
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2914:
	add	x1, x22, 128
	mov	x0, x19
	bl	HEVC_Sei_Color_Remapping_Info
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2913:
	add	x1, x22, 568
	cmp	x19, xzr
	ccmp	x1, xzr, 4, ne
	beq	.L2921
	mov	w0, 1
	strb	w0, [x22, 568]
	mov	x0, x19
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.25
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2912:
	add	x22, x22, 568
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2921
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L2918
.L2911:
	mov	w3, w21
	mov	x2, x23
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Scalable_Nesting
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2910:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2909:
	add	x2, x23, 2108
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Dec_Unit_Info
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2908:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Active_Param_sets
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2907:
	mov	w2, w21
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2906:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Display_Orientation
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2905:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2904:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Tone_Mapping_Info
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2903:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Recovery_Point
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2901:
	mov	w2, w21
	add	x1, x22, 56
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2900:
	add	x2, x23, 2064
	add	x1, x22, 8
	mov	x0, x19
	bl	HEVC_Sei_Pic_Timming
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.p2align 3
.L2898:
	add	x2, x23, 2108
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Buf_Period
	cbz	w0, .L2918
	mov	w0, -1
	b	.L2920
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	3
.LC619:
	.xword	.L2899
	.align	3
.LC621:
	.xword	.LC620
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	x23, x2
	bl	_mcount
	mov	w20, 0
	ldr	x0, [x19, 2936]
	b	.L2948
	.p2align 3
.L2950:
	bl	BsSkip
	add	w20, w20, 255
	ldr	x0, [x19, 2936]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2957
.L2948:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2936]
	beq	.L2950
	bl	BsGet
	mov	w21, 0
	mov	w24, w0
	ldr	x0, [x19, 2936]
	b	.L2951
	.p2align 3
.L2952:
	bl	BsSkip
	add	w21, w21, 255
	ldr	x0, [x19, 2936]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2958
.L2951:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2936]
	beq	.L2952
	bl	BsGet
	add	w4, w0, w21
	mov	x1, x22
	add	w3, w24, w20
	mov	x2, x23
	mov	x0, x19
	bl	HEVC_Sei_Payload
	mov	w1, 0
	cbnz	w0, .L2959
.L2949:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2957:
	ldr	x1, .LC623
	mov	w2, 5022
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2958:
	ldr	x1, .LC623
	mov	w2, 5043
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2959:
	ldr	x1, .LC625
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L2949
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	3
.LC623:
	.xword	.LC622
	.align	3
.LC625:
	.xword	.LC624
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L2966
	ldr	x21, [x19, 2968]
	add	x20, x19, 4096
	add	x20, x20, 128
	cbnz	x21, .L2969
	b	.L2972
	.p2align 3
.L2964:
	ldr	x0, [x19, 2936]
	bl	BsIsByteAligned
	cbz	w0, .L2973
	mov	x0, x19
	bl	HEVC_More_Rbsp_Data
	cbz	w0, .L2974
.L2969:
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbz	w0, .L2964
	ldr	x1, .LC629
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2962:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2974:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 128
	bne	.L2975
.L2966:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2973:
	ldr	x1, .LC631
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2975:
	ldr	x1, .LC633
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2962
.L2972:
	ldr	x1, .LC627
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2962
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	3
.LC627:
	.xword	.LC626
	.align	3
.LC629:
	.xword	.LC628
	.align	3
.LC631:
	.xword	.LC630
	.align	3
.LC633:
	.xword	.LC632
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x2
	mov	x21, x1
	bl	_mcount
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2977
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	mov	w20, w0
	ldr	x1, .LC635
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	cmp	w0, 63
	mov	w23, w0
	bhi	.L2992
	and	w20, w20, 255
	cmp	w0, w20
	bcc	.L2983
	ldr	x24, .LC639
	.p2align 2
.L2982:
	ldr	x0, [x19, 2936]
	mov	w1, 3
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2936]
	mov	x1, x24
	bl	HEVC_ue_v
	cmp	w23, w20
	bcs	.L2982
.L2983:
	ldr	x0, [x19, 2936]
	bl	BsToNextByte
.L2981:
	mov	x2, x22
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbnz	w0, .L2993
	ldr	x0, [x19, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2987
	ldr	x1, [x19, 2976]
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	bcc	.L2981
.L2987:
	mov	w0, 0
.L2979:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2977:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2983
	ldr	x0, [x19, 2936]
	mov	w1, 3
	mov	w20, 0
	bl	BsGet
	ldr	x1, .LC641
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	cmp	w0, 63
	add	w23, w0, 1
	bhi	.L2994
	.p2align 2
.L2988:
	ldr	x0, [x19, 2936]
	mov	w1, 6
	add	w20, w20, 1
	bl	BsGet
	cmp	w20, w23
	bne	.L2988
	b	.L2983
	.p2align 3
.L2993:
	ldr	x1, .LC644
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2992:
	ldr	x1, .LC637
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2979
.L2994:
	ldr	x1, .LC643
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2979
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	3
.LC635:
	.xword	.LC634
	.align	3
.LC637:
	.xword	.LC636
	.align	3
.LC639:
	.xword	.LC638
	.align	3
.LC641:
	.xword	.LC640
	.align	3
.LC643:
	.xword	.LC642
	.align	3
.LC644:
	.xword	.LC628
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	str	x1, [x29, 112]
	bl	_mcount
	add	x27, x20, 348
	ldr	x3, .LC646
	add	x1, x19, 1216
	add	x4, x19, 1536
	mov	x2, 64
	add	x0, x19, 1344
	mov	w25, 0
	ldr	x3, [x3, 104]
	stp	x4, x19, [x29, 136]
	blr	x3
	ldr	x23, .LC658
	ldr	x0, .LC645
	add	x1, x19, 1632
	add	x0, x0, 65536
	stp	x0, x1, [x29, 96]
.L2996:
	ldr	w0, [x27, 1888]
	cbz	w0, .L3016
	uxtw	x0, w25
	mov	w24, 0
	ldp	x1, x21, [x29, 136]
	str	x0, [x29, 128]
	lsl	x0, x0, 2
	str	x1, [x29, 152]
	str	x0, [x29, 120]
.L3015:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	w19, [x27]
	mov	w1, 64
	uxtb	w0, w0
	cmp	w19, 64
	csel	w19, w19, w1, le
	cbz	w25, .L2997
	add	x22, x20, 364
	cbz	w0, .L3029
	cmp	w25, 1
	bls	.L3022
	ldr	x1, .LC654
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 254
	bhi	.L3030
	add	w28, w0, 8
	ldr	x0, [x29, 152]
	str	w28, [x0]
.L3008:
	cmp	w19, wzr
	mov	x26, 0
	bgt	.L3012
	b	.L3007
	.p2align 3
.L3011:
	ldr	w0, [x22, x26, lsl 2]
	add	w1, w1, w2
	and	w1, w1, 255
	add	x26, x26, 1
	sub	w28, w1, w2
	cmp	w19, w26
	strb	w28, [x21, x0]
	ble	.L3007
.L3012:
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_se_v
	add	w2, w0, w28
	add	w0, w0, 128
	add	w1, w2, 256
	cmp	w0, 255
	asr	w2, w1, 31
	lsr	w2, w2, 24
	bls	.L3011
	ldr	x1, .LC660
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L3027:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L3029:
	ldr	x1, .LC648
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L3019
	sub	w0, w24, w0
	cmp	w25, 1
	uxtb	w0, w0
	bls	.L3002
	cmp	w0, w24
	beq	.L3021
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	ldr	x2, [x29, 112]
	lsl	x1, x1, 1
	add	x1, x1, x0, uxtb
	add	x1, x1, 384
	ldr	w1, [x2, x1, lsl 2]
.L3003:
	ldr	x2, [x29, 152]
	str	w1, [x2]
.L3002:
	cmp	w0, w24
	beq	.L3031
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	lsl	x1, x1, 1
	add	x0, x1, x0, uxtb
	ldr	x1, [x29, 112]
	add	x1, x1, x0, lsl 6
.L3005:
	cbz	x1, .L3032
	ldr	x0, .LC646
	sxtw	x2, w19
	ldr	x3, [x0, 104]
	mov	x0, x21
	blr	x3
.L3007:
	add	w24, w24, 1
	cmp	w24, 6
	beq	.L3016
	ldr	x0, [x29, 152]
	add	x21, x21, 64
	add	x0, x0, 4
	str	x0, [x29, 152]
	ldr	w0, [x27, 1888]
	cmp	w0, w24
	bhi	.L3015
	.p2align 2
.L3016:
	ldr	x0, [x29, 136]
	add	w25, w25, 1
	ldr	x1, [x29, 104]
	add	x27, x27, 4
	add	x0, x0, 24
	str	x0, [x29, 136]
	cmp	x0, x1
	ldr	x0, [x29, 144]
	add	x0, x0, 384
	str	x0, [x29, 144]
	bne	.L2996
	mov	w0, 0
	b	.L3027
	.p2align 3
.L3022:
	mov	w28, 8
	b	.L3008
.L3031:
	mov	w1, w24
	mov	w0, w25
	bl	HEVC_GetScalingListDefaultAddress
	mov	x1, x0
	b	.L3005
.L3021:
	mov	w1, 16
	b	.L3003
.L3030:
	ldr	x1, .LC656
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3027
.L3019:
	ldr	x1, .LC650
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3027
.L3032:
	ldr	x1, .LC652
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3027
.L2997:
	cbz	w0, .L3017
	mov	w28, 8
	ldr	x22, [x29, 96]
	b	.L3008
.L3017:
	ldr	x1, .LC648
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L3019
	sub	w0, w24, w0
	uxtb	w0, w0
	b	.L3002
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	3
.LC645:
	.xword	.LANCHOR1
	.align	3
.LC646:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC648:
	.xword	.LC647
	.align	3
.LC650:
	.xword	.LC649
	.align	3
.LC652:
	.xword	.LC651
	.align	3
.LC654:
	.xword	.LC653
	.align	3
.LC656:
	.xword	.LC655
	.align	3
.LC658:
	.xword	.LC657
	.align	3
.LC660:
	.xword	.LC659
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldrb	w1, [x20, 1]
	cmp	w1, 1
	beq	.L3228
.L3034:
	ldr	x1, .LC769
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 1
	str	w0, [x19, 60]
	mov	w21, w0
	beq	.L3229
	cmp	w21, 3
	bhi	.L3230
	ldr	x1, .LC669
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L3213:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3230:
	ldr	x1, .LC667
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3228:
	ldr	x0, [x20, 2976]
	ldr	w0, [x0, 24]
	cbz	w0, .L3034
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3034
	ldr	w2, [x19, 48]
	mov	w21, 24912
	ldr	x3, [x20, 2944]
	ldr	x0, [x20, 2936]
	umull	x2, w2, w21
	add	x21, x3, x2
	bl	BsGet
	cbnz	w0, .L3231
	ldr	x1, [x20, 2976]
	add	x0, x21, 12288
	add	x0, x0, 132
	ldr	w1, [x1, 24]
	add	x1, x1, 1036
	ldrsw	x1, [x0, x1, lsl 2]
	add	x0, x0, x1, lsl 2
	ldr	w0, [x0, 4152]
.L3036:
	cmp	w0, 1
	bhi	.L3232
	uxtw	x0, w0
	add	x21, x21, 12288
	lsl	x1, x0, 5
	add	x21, x21, 132
	add	x0, x1, x0, lsl 3
	add	x0, x21, x0
	add	x1, x0, 12288
	ldr	w2, [x0, 12420]
	str	w2, [x19, 60]
	ldrb	w1, [x1, 120]
	strb	w1, [x19, 47]
	ldr	w1, [x0, 12412]
	str	w1, [x19, 64]
	ldr	w1, [x0, 12416]
	str	w1, [x19, 68]
	ldr	w1, [x0, 12424]
	add	w1, w1, 8
	str	w1, [x19, 88]
	ldr	w2, [x0, 12428]
	add	w2, w2, 8
	str	w2, [x19, 96]
	ldr	w2, [x0, 12432]
	str	w2, [x19, 72]
	ldr	w2, [x0, 12436]
	str	w2, [x19, 76]
	ldr	w2, [x0, 12440]
	str	w2, [x19, 80]
	ldr	w0, [x0, 12444]
	str	w0, [x19, 84]
.L3039:
	str	w1, [x20, 196]
	ldr	x1, .LC703
	ldr	w0, [x19, 96]
	str	w0, [x20, 200]
	ldr	w4, [x19, 88]
	ldr	w3, [x19, 96]
	lsl	w2, w4, 2
	lsl	w0, w3, 2
	sub	w2, w2, w4
	sub	w0, w0, w3
	lsl	w2, w2, 1
	lsl	w0, w0, 1
	sub	w2, w2, #48
	sub	w0, w0, #48
	str	w2, [x19, 92]
	str	w0, [x19, 100]
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 12
	bhi	.L3233
	add	w0, w0, 4
	stp	w0, w0, [x19, 116]
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L3234
.L3066:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	mov	w23, 0
	mov	w21, 0
	bl	BsGet
	ldr	x26, .LC707
	mov	w27, w0
	ldr	x25, .LC709
	ldr	x24, .LC711
	b	.L3074
	.p2align 3
.L3070:
	ldr	w0, [x19, 52]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L3073
.L3074:
	add	x22, x19, x21, uxtw 2
	ldr	x0, [x20, 2936]
	mov	x1, x26
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 328]
	mov	x1, x25
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x22, 360]
	mov	x1, x24
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x22, 392]
	ldr	w1, [x22, 328]
	cmp	w23, w1
	csel	w23, w23, w1, cs
	cbnz	w27, .L3070
	ldr	w2, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w2
	bhi	.L3073
	.p2align 2
.L3181:
	add	x0, x19, x21, uxtw 2
	ldr	w1, [x19, 328]
	add	w21, w21, 1
	cmp	w21, w2
	str	w1, [x0, 328]
	ldr	w1, [x19, 360]
	str	w1, [x0, 360]
	ldr	w1, [x19, 392]
	str	w1, [x0, 392]
	bls	.L3181
.L3073:
	ldr	w0, [x19, 184]
	cmp	w0, w23
	csel	w23, w0, w23, ls
	str	w23, [x19, 184]
.L3069:
	ldr	x1, .LC713
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L3235
	ldr	x1, .LC717
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w21, w0
	bhi	.L3236
	add	w2, w22, 3
	add	w1, w0, w2
	sub	w0, w1, #4
	cmp	w0, 2
	stp	w2, w1, [x19, 124]
	bhi	.L3237
	ldp	w4, w0, [x19, 64]
	mov	w23, 1
	lsl	w1, w23, w1
	lsl	w2, w23, w2
	stp	w2, w1, [x19, 132]
	udiv	w3, w4, w1
	stp	w1, w1, [x19, 140]
	udiv	w2, w0, w1
	msub	w4, w3, w1, w4
	cmp	w4, wzr
	csinc	w3, w3, w3, eq
	str	w3, [x19, 188]
	msub	w0, w2, w1, w0
	ldr	x1, .LC723
	cmp	w0, wzr
	csinc	w2, w2, w2, eq
	str	w2, [x19, 192]
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L3238
	ldr	x1, .LC727
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 3
	bhi	.L3239
	ldr	w2, [x19, 124]
	add	w1, w22, 2
	str	w1, [x19, 148]
	cmp	w1, w2
	bcs	.L3240
	add	w1, w0, w1
	str	w1, [x19, 152]
	cmp	w1, 5
	bhi	.L3085
	ldr	w0, [x19, 128]
	cmp	w1, w0
	bhi	.L3085
	ldr	x1, .LC735
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x19, 164]
	ldr	w1, [x19, 128]
	ldr	w2, [x19, 148]
	sub	w1, w1, w2
	cmp	w0, w1
	bhi	.L3241
	ldr	x1, .LC739
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x19, 168]
	ldr	w1, [x19, 128]
	ldr	w4, [x19, 148]
	sub	w1, w1, w4
	cmp	w0, w1
	bhi	.L3088
	ldr	w2, [x19, 140]
	mov	w3, 1
	lsl	w0, w3, w4
	mov	w1, 0
	lsr	w2, w2, w21
	cmp	w2, w0
	bls	.L3090
	.p2align 2
.L3180:
	add	w1, w1, 1
	add	w0, w4, w1
	lsl	w0, w3, w0
	cmp	w0, w2
	bcc	.L3180
.L3090:
	add	w1, w21, w1
	str	w1, [x19, 172]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3]
	cbz	w0, .L3095
	ldrb	w1, [x20, 1]
	cmp	w1, 1
	beq	.L3242
.L3093:
	add	x0, x19, 12288
	strb	wzr, [x0, 372]
.L3125:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 4]
	cbnz	w0, .L3243
.L3095:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 6]
	cbnz	w0, .L3096
	ldr	w2, [x19, 68]
	cmp	w2, 64
	bls	.L3244
.L3096:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	str	w0, [x19, 104]
	cbz	w0, .L3097
	ldr	x0, [x20, 2936]
	mov	w1, 4
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 108]
	mov	w1, 4
	ldr	x0, [x20, 2936]
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 112]
	ldr	x1, .LC747
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w21, w0
	bhi	.L3245
.L3098:
	ldr	x1, .LC751
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w22, w0
	bhi	.L3246
.L3099:
	add	w0, w21, 3
	str	w0, [x19, 156]
	add	w0, w22, w0
	str	w0, [x19, 160]
	cmp	w0, 5
	bhi	.L3100
	ldr	w1, [x19, 128]
	cmp	w0, w1
	bhi	.L3100
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 7]
.L3097:
	ldr	x1, .LC757
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 64
	str	w0, [x19, 176]
	bhi	.L3102
	mov	w21, 0
	cbnz	w0, .L3179
	b	.L3108
	.p2align 3
.L3106:
	ldr	w0, [x19, 176]
	cmp	w0, w21
	bls	.L3108
.L3179:
	uxtw	x5, w21
	mov	w3, w21
	lsl	x2, x5, 2
	mov	x1, x19
	sub	x2, x2, x5
	mov	x0, x20
	lsl	x4, x2, 3
	add	w21, w21, 1
	sub	x2, x4, x2
	lsl	x2, x2, 1
	sub	x2, x2, x5
	add	x2, x19, x2, lsl 2
	add	x2, x2, 2164
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L3106
	ldr	x1, .LC761
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3229:
	ldr	x1, .LC671
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 8192
	str	w0, [x19, 64]
	bls	.L3041
	ldr	x1, .LC673
.L3220:
	mov	w0, w21
	bl	dprint_vfmw
	ldr	x0, .LC674
	ldr	x4, [x0]
	cbz	x4, .L3217
.L3219:
	ldr	w0, [x20, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3041:
	ldr	x1, .LC676
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 4096
	str	w0, [x19, 68]
	bhi	.L3247
	ldr	w2, [x19, 428]
	ldr	w1, [x19, 64]
	cmp	w2, 120
	mul	w0, w0, w1
	beq	.L3046
	bgt	.L3047
	cmp	w2, 60
	beq	.L3127
	ble	.L3248
	cmp	w2, 90
	beq	.L3051
	cmp	w2, 93
	beq	.L3052
	cmp	w2, 63
	beq	.L3249
.L3045:
	ldr	x1, .LC680
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3234:
	ldr	x0, [x20, 2976]
	ldr	w0, [x0, 24]
	cbz	w0, .L3066
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3066
	ldp	w0, w7, [x19, 48]
	mov	w6, 24912
	ldr	x8, [x20, 2944]
	mov	w4, 0
	mov	w2, 0
	umull	x6, w0, w6
	.p2align 2
.L3068:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x0, x6
	add	x0, x19, x0
	add	x1, x8, x1
	ldr	w3, [x1, 28]
	str	w3, [x0, 328]
	cmp	w4, w3
	ldr	w5, [x1, 60]
	csel	w4, w4, w3, cs
	str	w5, [x0, 360]
	cmp	w2, w7
	ldr	w1, [x1, 92]
	str	w1, [x0, 392]
	bls	.L3068
	str	w4, [x19, 184]
	b	.L3069
	.p2align 3
.L3108:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbz	w0, .L3105
	ldr	x1, .LC763
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 32
	str	w0, [x19, 180]
	bhi	.L3111
	mov	w22, 0
	cbz	w0, .L3105
	.p2align 2
.L3178:
	ldr	w1, [x19, 116]
	uxtw	x21, w22
	ldr	x0, [x20, 2936]
	add	w22, w22, 1
	bl	BsGet
	add	x2, x19, x21, lsl 2
	add	x21, x19, x21
	mov	w1, 1
	str	w0, [x2, 196]
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x21, 13]
	ldr	w0, [x19, 180]
	cmp	w0, w22
	bhi	.L3178
.L3105:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 11]
	cbz	w0, .L3110
	mov	x2, x19
	add	x1, x19, 2064
	mov	x0, x20
	bl	HEVC_DecVuiParam
	cbz	w0, .L3110
	ldr	x1, .LC767
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L3217:
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3110:
	ldp	w3, w4, [x19, 64]
	ldr	w0, [x19, 2072]
	ldr	w1, [x19, 2076]
	ldr	w2, [x19, 2080]
	bl	HEVC_GetDar
	str	w0, [x19, 2068]
	ldrb	w21, [x20, 1]
	cmp	w21, 1
	beq	.L3250
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
	b	.L3213
	.p2align 3
.L3231:
	ldr	x0, [x20, 2936]
	mov	w1, 8
	bl	BsGet
	b	.L3036
	.p2align 3
.L3047:
	cmp	w2, 156
	beq	.L3054
	bgt	.L3055
	cmp	w2, 150
	beq	.L3054
	cmp	w2, 153
	beq	.L3054
	cmp	w2, 123
	bne	.L3045
.L3046:
	mov	w2, 32768
	mov	w1, 2228224
	movk	w2, 0x8, lsl 16
	.p2align 2
.L3048:
	cmp	w2, w0
	bcc	.L3057
	mov	w0, 16
	str	w0, [x19, 184]
.L3058:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L3061
	ldr	x1, .LC682
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x21, .LC683
	ldr	w2, [x19, 60]
	ldr	x1, .LC685
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 64]
	mul	w0, w2, w0
	str	w0, [x19, 72]
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldp	w2, w1, [x19, 60]
	ldr	w3, [x19, 72]
	add	x2, x21, x2, lsl 2
	sub	w1, w1, w3
	ldr	w2, [x2, 64]
	mul	w0, w0, w2
	str	w0, [x19, 76]
	sub	w1, w1, w0
	tbnz	w1, #31, .L3251
	ldr	x1, .LC689
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	x1, .LC691
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 80]
	mul	w0, w2, w0
	str	w0, [x19, 80]
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	w1, [x19, 68]
	ldr	w3, [x19, 80]
	add	x21, x21, x2, lsl 2
	sub	w1, w1, w3
	ldr	w2, [x21, 80]
	mul	w0, w0, w2
	str	w0, [x19, 84]
	sub	w1, w1, w0
	tbnz	w1, #31, .L3252
.L3061:
	ldr	x1, .LC695
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 2
	str	w2, [x19, 88]
	bhi	.L3253
	ldr	x1, .LC699
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 6
	str	w2, [x19, 96]
	bhi	.L3254
	ldr	w1, [x19, 88]
	b	.L3039
	.p2align 3
.L3244:
	ldr	x1, .LC745
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC674
	ldr	x4, [x0]
	cbnz	x4, .L3219
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3242:
	ldr	x0, [x20, 2976]
	ldr	w0, [x0, 24]
	cbz	w0, .L3093
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3093
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	add	x1, x19, 12288
	strb	w0, [x1, 372]
	cbz	w0, .L3125
	ldr	x0, [x20, 2936]
	mov	w1, 6
	bl	BsGet
	strb	wzr, [x19, 4]
	str	w0, [x19, 12664]
	b	.L3095
	.p2align 3
.L3057:
	cmp	w0, w1, lsr 1
	bhi	.L3059
	mov	w0, 12
	str	w0, [x19, 184]
	b	.L3058
	.p2align 3
.L3085:
	ldr	x1, .LC733
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3247:
	ldr	x1, .LC678
	b	.L3220
	.p2align 3
.L3246:
	ldr	x1, .LC753
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3099
	.p2align 3
.L3245:
	ldr	x1, .LC749
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3098
	.p2align 3
.L3243:
	add	x1, x19, 432
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbz	w0, .L3095
	ldr	x1, .LC743
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3253:
	ldr	x1, .LC697
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC674
	ldr	x4, [x0]
	cbz	x4, .L3217
	ldr	w1, [x19, 88]
	mov	w3, 8
	ldr	w0, [x20, 276]
	add	x2, x29, 104
	stp	wzr, w1, [x29, 104]
	mov	w1, 119
	blr	x4
	mov	w0, -1
	b	.L3213
.L3059:
	lsl	w2, w1, 2
	sub	w1, w2, w1
	cmp	w0, w1, lsr 2
	bhi	.L3060
	mov	w0, 8
	str	w0, [x19, 184]
	b	.L3058
.L3235:
	ldr	x1, .LC715
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3232:
	mov	w2, 1
	ldr	x1, .LC663
	mov	w0, w2
	bl	dprint_vfmw
	ldr	x1, .LC665
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3238:
	ldr	x1, .LC725
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3055:
	cmp	w2, 183
	beq	.L3056
	cmp	w2, 186
	beq	.L3056
	cmp	w2, 180
	bne	.L3045
.L3056:
	mov	w2, 8912896
	mov	w1, 35651584
	b	.L3048
.L3248:
	cbz	w2, .L3050
	cmp	w2, 30
	bne	.L3045
.L3050:
	mov	w2, 9216
	mov	w1, 36864
	b	.L3048
.L3100:
	ldr	x1, .LC755
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3241:
	ldr	x1, .LC737
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3250:
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L3115
.L3118:
	mov	w0, 0
	b	.L3213
.L3115:
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	uxtb	w19, w0
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	uxtb	w23, w0
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	uxtb	w22, w0
	cbnz	w19, .L3255
	cbnz	w23, .L3256
.L3117:
	cbnz	w22, .L3216
	b	.L3118
	.p2align 3
.L3119:
	ldr	x0, [x20, 2936]
	bl	BsGet
.L3216:
	ldr	x0, [x20, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L3118
	ldr	x2, [x20, 2976]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L3119
	mov	w0, 0
	b	.L3213
.L3256:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L3117
.L3255:
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	cbz	w23, .L3117
	b	.L3256
	.p2align 3
.L3249:
	mov	w2, 61440
	mov	w1, 245760
	b	.L3048
.L3054:
	mov	w2, 2228224
	mov	w1, 8912896
	b	.L3048
.L3127:
	mov	w2, 30720
	mov	w1, 122880
	b	.L3048
.L3052:
	mov	w2, 245760
	mov	w1, 983040
	b	.L3048
.L3051:
	mov	w2, 7168
	mov	w1, 28672
	movk	w2, 0x2, lsl 16
	movk	w1, 0x8, lsl 16
	b	.L3048
.L3060:
	mov	w0, 6
	str	w0, [x19, 184]
	b	.L3058
.L3233:
	ldr	x1, .LC705
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3237:
	ldr	x1, .LC721
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3236:
	ldr	x1, .LC719
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3239:
	ldr	x1, .LC729
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3240:
	ldr	x1, .LC731
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3088:
	ldr	x1, .LC741
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3102:
	ldr	x1, .LC759
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3111:
	ldr	x1, .LC765
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3254:
	ldr	x1, .LC701
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3251:
	ldr	x1, .LC687
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3252:
	ldr	x1, .LC693
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	3
.LC663:
	.xword	.LC662
	.align	3
.LC665:
	.xword	.LC664
	.align	3
.LC667:
	.xword	.LC666
	.align	3
.LC669:
	.xword	.LC668
	.align	3
.LC671:
	.xword	.LC670
	.align	3
.LC673:
	.xword	.LC672
	.align	3
.LC674:
	.xword	g_event_report
	.align	3
.LC676:
	.xword	.LC675
	.align	3
.LC678:
	.xword	.LC677
	.align	3
.LC680:
	.xword	.LC679
	.align	3
.LC682:
	.xword	.LC681
	.align	3
.LC683:
	.xword	.LANCHOR5
	.align	3
.LC685:
	.xword	.LC684
	.align	3
.LC687:
	.xword	.LC686
	.align	3
.LC689:
	.xword	.LC688
	.align	3
.LC691:
	.xword	.LC690
	.align	3
.LC693:
	.xword	.LC692
	.align	3
.LC695:
	.xword	.LC694
	.align	3
.LC697:
	.xword	.LC696
	.align	3
.LC699:
	.xword	.LC698
	.align	3
.LC701:
	.xword	.LC700
	.align	3
.LC703:
	.xword	.LC702
	.align	3
.LC705:
	.xword	.LC704
	.align	3
.LC707:
	.xword	.LC706
	.align	3
.LC709:
	.xword	.LC708
	.align	3
.LC711:
	.xword	.LC710
	.align	3
.LC713:
	.xword	.LC712
	.align	3
.LC715:
	.xword	.LC714
	.align	3
.LC717:
	.xword	.LC716
	.align	3
.LC719:
	.xword	.LC718
	.align	3
.LC721:
	.xword	.LC720
	.align	3
.LC723:
	.xword	.LC722
	.align	3
.LC725:
	.xword	.LC724
	.align	3
.LC727:
	.xword	.LC726
	.align	3
.LC729:
	.xword	.LC728
	.align	3
.LC731:
	.xword	.LC730
	.align	3
.LC733:
	.xword	.LC732
	.align	3
.LC735:
	.xword	.LC734
	.align	3
.LC737:
	.xword	.LC736
	.align	3
.LC739:
	.xword	.LC738
	.align	3
.LC741:
	.xword	.LC740
	.align	3
.LC743:
	.xword	.LC742
	.align	3
.LC745:
	.xword	.LC744
	.align	3
.LC747:
	.xword	.LC746
	.align	3
.LC749:
	.xword	.LC748
	.align	3
.LC751:
	.xword	.LC750
	.align	3
.LC753:
	.xword	.LC752
	.align	3
.LC755:
	.xword	.LC754
	.align	3
.LC757:
	.xword	.LC756
	.align	3
.LC759:
	.xword	.LC758
	.align	3
.LC761:
	.xword	.LC760
	.align	3
.LC763:
	.xword	.LC762
	.align	3
.LC765:
	.xword	.LC764
	.align	3
.LC767:
	.xword	.LC766
	.align	3
.LC769:
	.xword	.LC768
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x23, .LC770
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 96
	ldr	x3, [x23, 96]
	blr	x3
	ldr	x0, [x19, 2936]
	mov	w1, 4
	bl	BsGet
	mov	w24, w0
	ldr	w2, [x19, 156]
	cmp	w2, w0
	bls	.L3279
	ldr	x0, [x19, 2976]
	ldr	w0, [x0, 24]
	cbz	w0, .L3280
	ldr	x0, [x19, 2936]
	mov	w1, 3
	bl	BsGet
	uxtb	w25, w0
	cmp	w25, 7
	beq	.L3262
	and	w21, w0, 255
.L3263:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w26, w0
	mov	w3, w21
	mov	w2, 1
	add	x1, x29, 96
	mov	x0, x19
	bl	HEVC_DecPTL
	cbnz	w0, .L3281
.L3264:
	ldr	x1, .LC778
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	mov	w28, w0
	ldr	w2, [x19, 160]
	cmp	w0, w2
	bcs	.L3282
	mov	w20, 12668
	umull	x20, w0, w20
	ldr	x0, [x19, 2952]
	add	x0, x0, x20
	ldrb	w1, [x0, 1]
	cbz	w1, .L3266
	ldr	x27, .LC782
	mov	x2, 12668
	ldr	x3, [x23, 96]
	mov	w1, 0
	add	x22, x27, 3328
	mov	x0, x22
	blr	x3
	strb	w26, [x22, 2]
	ldr	x3, [x23, 104]
	add	x1, x29, 96
	mov	x2, 8
	strb	w25, [x22, 46]
	stp	w24, w21, [x22, 48]
	add	x0, x27, 3752
	blr	x3
	str	w28, [x22, 56]
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_ProcessSPS
	mov	w21, w0
	cbnz	w0, .L3283
	ldr	x0, [x19, 2952]
	mov	w1, 1
	ldr	x3, [x23, 112]
	mov	x2, 12668
	strb	w1, [x27, 3328]
	add	x0, x0, x20
	strb	w1, [x22, 1]
	mov	x1, x22
	blr	x3
	ldr	x0, [x19, 2952]
	add	x20, x0, x20
	str	x20, [x19, 2968]
.L3278:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3280:
	ldr	x0, [x19, 2936]
	mov	w1, 3
	mov	w25, 0
	bl	BsGet
	cmp	w0, 8
	mov	w21, w0
	bls	.L3263
	ldr	x1, .LC774
	mov	w2, 8
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L3278
	.p2align 3
.L3266:
	str	w24, [x0, 48]
	mov	x2, 8
	add	x1, x29, 96
	ldr	x0, [x19, 2952]
	add	x0, x0, x20
	str	w21, [x0, 52]
	ldr	x0, [x19, 2952]
	add	x0, x0, x20
	strb	w26, [x0, 2]
	ldr	x0, [x19, 2952]
	add	x0, x0, x20
	strb	w25, [x0, 46]
	ldr	x0, [x19, 2952]
	ldr	x3, [x23, 104]
	add	x0, x0, x20
	add	x0, x0, 424
	blr	x3
	ldr	x1, [x19, 2952]
	mov	x0, x19
	add	x1, x1, x20
	str	w28, [x1, 56]
	ldr	x1, [x19, 2952]
	add	x1, x1, x20
	bl	HEVC_ProcessSPS
	mov	w21, w0
	cbnz	w0, .L3284
	ldr	x0, [x19, 2952]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2952]
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2952]
	add	x20, x0, x20
	str	x20, [x19, 2968]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3282:
	ldr	x1, .LC780
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 160]
	cmp	w28, w1
	bcc	.L3273
	ldr	x0, .LC781
	ldr	x4, [x0]
	cbz	x4, .L3273
	ldr	w0, [x19, 276]
	add	x2, x29, 104
	stp	w28, w1, [x29, 104]
	mov	w3, 8
	mov	w1, 109
	mov	w21, -1
	blr	x4
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3273:
	mov	w21, -1
	b	.L3278
	.p2align 3
.L3262:
	ldr	x0, [x19, 2976]
	ldr	w0, [x0, 24]
	cbz	w0, .L3270
	mov	w0, 24912
	ldr	x1, [x19, 2944]
	mov	w26, 1
	umull	x0, w24, w0
	add	x0, x1, x0
	ldr	w21, [x0, 12]
	cbz	w21, .L3264
	ldrb	w26, [x0, 1]
	b	.L3264
	.p2align 3
.L3279:
	ldr	x1, .LC772
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L3278
	.p2align 3
.L3283:
	ldr	x3, [x19, 2952]
	mov	w2, w28
	ldr	x1, .LC784
	mov	w0, 1
	add	x20, x3, x20
	str	x20, [x19, 2968]
	mov	w21, -1
	bl	dprint_vfmw
	b	.L3278
	.p2align 3
.L3281:
	ldr	x1, .LC776
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L3278
.L3284:
	ldr	x1, .LC786
	mov	w2, w28
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2952]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2952]
	add	x20, x0, x20
	strb	wzr, [x20, 1]
	b	.L3278
.L3270:
	mov	w21, 0
	b	.L3263
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	3
.LC770:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC772:
	.xword	.LC771
	.align	3
.LC774:
	.xword	.LC773
	.align	3
.LC776:
	.xword	.LC775
	.align	3
.LC778:
	.xword	.LC777
	.align	3
.LC780:
	.xword	.LC779
	.align	3
.LC781:
	.xword	g_event_report
	.align	3
.LC782:
	.xword	.LANCHOR6
	.align	3
.LC784:
	.xword	.LC783
	.align	3
.LC786:
	.xword	.LC785
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	w22, 1
	bl	_mcount
	mov	w0, 1
	strb	w0, [x19, 16]
	stp	w22, w22, [x19, 68]
	ldr	x1, .LC789
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x19, 32]
	tbnz	w0, #31, .L3286
	ldr	w1, [x20, 160]
	cmp	w0, w1
	bge	.L3286
	ldr	x1, [x20, 2952]
	mov	w21, 12668
	smaddl	x21, w0, w21, x1
	ldrb	w1, [x21, 1]
	cbz	w1, .L3433
	ldr	x0, [x20, 2936]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, w22
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 3
	ldr	x0, [x20, 2936]
	bl	BsGet
	str	w0, [x19, 36]
	mov	w1, w22
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, w22
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 5]
	ldr	x1, .LC795
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 40]
	bhi	.L3434
	ldr	x1, .LC799
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 44]
	bhi	.L3435
	ldr	x1, .LC803
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w2, w0, 26
	str	w2, [x19, 48]
	mov	w0, 51
	ldr	w3, [x21, 92]
	neg	w1, w3
	cmp	w2, w1
	ccmp	w2, w0, 0, ge
	bgt	.L3436
	ldr	x0, [x20, 2936]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, w22
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, w22
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbnz	w0, .L3437
	mov	w0, 0
	str	wzr, [x19, 52]
.L3295:
	str	w0, [x19, 56]
	ldr	x1, .LC811
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 60]
	bhi	.L3438
	ldr	x1, .LC815
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 64]
	bhi	.L3439
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 11]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 14]
	ldrb	w1, [x19, 13]
	cbnz	w1, .L3440
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L3332:
	ldr	w3, [x19, 68]
	cmp	w3, wzr
	ble	.L3337
.L3331:
	ldr	w4, [x21, 140]
	add	x0, x19, 172
	mov	w1, 0
	.p2align 2
.L3336:
	ldrsh	w2, [x0]
	add	w1, w1, 1
	add	x0, x0, 2
	mul	w2, w2, w4
	cmp	w2, 64
	bhi	.L3335
	ldr	w5, [x21, 64]
	cmp	w5, 64
	bhi	.L3441
.L3335:
	cmp	w1, w3
	blt	.L3336
.L3337:
	ldr	w1, [x19, 72]
	cmp	w1, wzr
	ble	.L3334
	ldrsh	w2, [x19, 212]
	ldr	w3, [x21, 140]
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L3338
	sub	w1, w1, #1
	mov	x0, x19
	add	x1, x19, x1, lsl 1
	b	.L3340
	.p2align 3
.L3341:
	ldrsh	w2, [x0, 214]
	add	x0, x0, 2
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L3338
.L3340:
	cmp	x1, x0
	bne	.L3341
.L3334:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 18]
	cbnz	w0, .L3442
.L3343:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 21]
	cbz	w0, .L3346
	add	x1, x19, 256
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbnz	w0, .L3443
.L3346:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 22]
	ldr	x1, .LC858
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 2
	cmp	w2, 1
	str	w2, [x19, 84]
	ble	.L3347
	ldr	w0, [x21, 128]
	cmp	w2, w0
	bhi	.L3347
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 24]
	cbnz	w0, .L3349
.L3372:
	mov	w0, 0
.L3457:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3437:
	ldr	x1, .LC807
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 3
	str	w0, [x19, 52]
	bls	.L3295
	ldr	x1, .LC809
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
	.p2align 3
.L3440:
	ldr	x1, .LC819
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 19
	str	w2, [x19, 68]
	bhi	.L3444
	ldr	x1, .LC823
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 21
	str	w2, [x19, 72]
	bhi	.L3445
	ldr	w3, [x19, 68]
	cmp	w3, 10
	bgt	.L3446
	cmp	w2, 11
	ble	.L3303
	ldr	x1, .LC830
	mov	w3, w2
	mov	w2, 11
.L3430:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC828
	ldr	x4, [x0]
	cbz	x4, .L3424
.L3427:
	ldr	w0, [x20, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L3419:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3349:
	ldrb	w21, [x20, 1]
	cmp	w21, 1
	bne	.L3372
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	uxtb	w22, w0
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	uxtb	w25, w0
	ldr	x0, [x20, 2936]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 5
	bl	BsGet
	uxtb	w0, w0
	str	w0, [x29, 108]
	cbz	w22, .L3351
	ldrb	w0, [x19, 7]
	cbnz	w0, .L3447
.L3352:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3356
	ldr	x1, .LC868
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC870
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 5
	bgt	.L3354
	tbnz	w0, #31, .L3356
	ldr	x24, .LC874
	add	w22, w0, 1
	ldr	x23, .LC876
	mov	w21, 0
	.p2align 2
.L3358:
	ldr	x0, [x20, 2936]
	mov	x1, x24
	add	w21, w21, 1
	bl	HEVC_se_v
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_se_v
	cmp	w21, w22
	bne	.L3358
.L3356:
	ldr	x1, .LC864
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	ldr	x1, .LC866
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
.L3351:
	cbz	w25, .L3350
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	x21, x19, 1888
	bl	BsGet
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, 1]
	cbnz	w0, .L3448
	str	wzr, [x21, 68]
.L3360:
	ldr	x1, .LC880
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	cmp	w0, 63
	bhi	.L3449
	str	wzr, [x21, 72]
	mov	w1, 8
	str	wzr, [x21, 328]
	str	wzr, [x21, 584]
	str	wzr, [x21, 840]
	str	wzr, [x21, 1096]
	str	wzr, [x21, 1352]
	str	wzr, [x21, 1608]
	str	wzr, [x21, 1864]
	str	wzr, [x21, 2120]
	str	wzr, [x19, 4264]
	str	w1, [x19, 4520]
	str	w1, [x19, 4776]
	cbz	w0, .L3371
	sub	w23, w0, #1
	ldr	x28, .LC886
	add	x23, x23, 1891
	ldr	x27, .LC888
	ldr	x26, .LC890
	add	x22, x19, 1890
	ldr	x25, .LC892
	add	x23, x19, x23
	b	.L3370
	.p2align 3
.L3364:
	add	x0, x19, x21, lsl 2
	str	wzr, [x0, 1960]
	str	wzr, [x0, 2216]
	str	wzr, [x0, 2472]
	str	wzr, [x0, 2728]
.L3365:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L3450
	add	x0, x19, x21, lsl 2
	str	wzr, [x0, 2984]
	str	wzr, [x0, 3240]
	str	wzr, [x0, 3496]
	str	wzr, [x0, 3752]
.L3367:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	add	x21, x19, x21, lsl 2
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22]
	cbnz	w0, .L3451
	mov	w0, 8
	str	wzr, [x21, 4008]
	str	wzr, [x21, 4264]
	str	w0, [x21, 4520]
	str	w0, [x21, 4776]
.L3369:
	add	x22, x22, 1
	cmp	x23, x22
	beq	.L3371
.L3370:
	ldr	x0, [x20, 2936]
	mov	w1, 6
	bl	BsGet
	sxtw	x21, w0
	cmp	w21, 63
	bgt	.L3452
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3364
	add	x24, x19, x21, lsl 2
	ldr	x0, [x20, 2936]
	mov	x1, x28
	bl	HEVC_se_v
	str	w0, [x24, 1960]
	mov	x1, x27
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 2216]
	mov	x1, x26
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 2472]
	mov	x1, x25
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 2728]
	b	.L3365
	.p2align 3
.L3338:
	ldr	x1, .LC846
.L3429:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC828
	ldr	x4, [x0]
	cbnz	x4, .L3427
.L3424:
	mov	w0, -1
.L3458:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3441:
	ldr	x1, .LC844
	b	.L3429
	.p2align 3
.L3436:
	ldr	x1, .LC805
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3303:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 15]
	cbnz	w0, .L3453
	ldr	w0, [x19, 68]
	sub	w1, w0, #1
	cmp	w1, wzr
	ble	.L3308
	ldr	x23, .LC832
	mov	w22, 0
	b	.L3312
	.p2align 3
.L3455:
	cmp	w3, w4
	bhi	.L3310
	ldr	w0, [x19, 68]
	add	w22, w22, 1
	sub	w1, w0, #1
	cmp	w1, w22
	ble	.L3454
.L3312:
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 88]
	ldr	w4, [x21, 188]
	tbz	w3, #31, .L3455
.L3310:
	ldr	x1, .LC834
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3446:
	ldr	x1, .LC827
	mov	w2, 10
	b	.L3430
.L3442:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	ldr	x0, [x20, 2936]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 20]
	cbnz	w0, .L3343
	ldr	x1, .LC848
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 76]
	bhi	.L3456
.L3345:
	ldr	x1, .LC852
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 80]
	bls	.L3343
	ldr	x1, .LC854
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 80]
	b	.L3343
.L3453:
	ldr	w0, [x19, 68]
.L3314:
	cmp	w0, wzr
	add	x5, x19, 172
	mov	w3, 0
	ble	.L3307
	.p2align 2
.L3398:
	add	w3, w3, 1
	ldr	w4, [x21, 188]
	sub	w2, w3, #1
	cmp	w3, w0
	mul	w1, w3, w4
	mul	w2, w2, w4
	udiv	w1, w1, w0
	udiv	w2, w2, w0
	sub	w1, w1, w2
	strh	w1, [x5], 2
	bne	.L3398
.L3307:
	ldr	w4, [x19, 72]
	add	x6, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L3322
	.p2align 2
.L3397:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w2, w3, #1
	cmp	w3, w4
	mul	w1, w3, w5
	mul	w2, w2, w5
	udiv	w1, w1, w4
	udiv	w2, w2, w4
	sub	w1, w1, w2
	strh	w1, [x6], 2
	bne	.L3397
.L3322:
	cmp	w0, 1
	bne	.L3330
	ldr	w3, [x19, 72]
	cmp	w3, 1
	beq	.L3331
.L3330:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L3332
.L3371:
	ldr	x0, [x20, 2936]
	mov	w1, 1
	bl	BsGet
.L3350:
	ldr	w0, [x29, 108]
	cbnz	w0, .L3423
	b	.L3372
	.p2align 3
.L3373:
	ldr	x0, [x20, 2936]
	bl	BsGet
	strb	w0, [x19, 25]
.L3423:
	ldr	x0, [x20, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L3372
	ldr	x2, [x20, 2976]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L3373
	mov	w0, 0
	b	.L3457
.L3451:
	ldr	x1, .LC902
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 4008]
	ldr	x1, .LC904
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 4264]
	ldr	x1, .LC906
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 4520]
	ldr	x1, .LC908
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	str	w0, [x21, 4776]
	b	.L3369
.L3450:
	add	x24, x19, x21, lsl 2
	ldr	x1, .LC894
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 2984]
	ldr	x1, .LC896
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 3240]
	ldr	x1, .LC898
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 3496]
	ldr	x1, .LC900
	ldr	x0, [x20, 2936]
	bl	HEVC_se_v
	str	w0, [x24, 3752]
	b	.L3367
.L3286:
	ldr	x1, .LC791
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3433:
	ldr	x1, .LC793
	mov	w2, w0
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3434:
	ldr	x1, .LC797
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3435:
	ldr	x1, .LC801
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3438:
	ldr	x1, .LC813
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3439:
	ldr	x1, .LC817
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3347:
	ldr	x1, .LC860
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3458
.L3454:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	ble	.L3320
.L3313:
	ldr	x23, .LC836
	mov	w22, 0
	b	.L3319
	.p2align 3
.L3460:
	cmp	w3, w4
	bhi	.L3317
	ldr	w0, [x19, 72]
	add	w22, w22, 1
	sub	w0, w0, #1
	cmp	w0, w22
	ble	.L3459
.L3319:
	ldr	x0, [x20, 2936]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 128]
	ldr	w4, [x21, 192]
	tbz	w3, #31, .L3460
.L3317:
	ldr	x1, .LC838
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3447:
	ldr	x1, .LC862
	ldr	x0, [x20, 2936]
	bl	HEVC_ue_v
	b	.L3352
.L3452:
	ldr	x1, .LC884
	mov	w3, 64
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
.L3357:
	ldr	x1, .LC910
	mov	w0, 1
	ldr	w2, [x19, 84]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3444:
	ldr	x1, .LC821
	mov	w3, 20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3448:
	ldr	x0, [x20, 2936]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 1
	str	w0, [x21, 68]
	ble	.L3360
	ldr	x1, .LC878
	mov	w2, w0
	mov	w3, 2
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3357
	.p2align 3
.L3456:
	ldr	x1, .LC850
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 76]
	b	.L3345
.L3459:
	ldr	w0, [x19, 68]
.L3320:
	ldrb	w1, [x19, 15]
	cbnz	w1, .L3314
	add	x5, x19, x0, sxtw 1
	sub	w2, w0, #1
	ldrsh	w3, [x21, 188]
	cmp	w2, wzr
	strh	w3, [x5, 170]
	ble	.L3325
	sub	w6, w0, #2
	add	x4, x19, 88
	add	x6, x6, 45
	add	x6, x19, x6, lsl 1
	.p2align 2
.L3326:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 170]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 170]
	bne	.L3326
.L3325:
	cmp	w3, wzr
	ble	.L3461
	ldr	w1, [x19, 72]
	ldrsh	w3, [x21, 192]
	sub	w2, w1, #1
	add	x5, x19, x1, sxtw 1
	cmp	w2, wzr
	strh	w3, [x5, 210]
	ble	.L3328
	sub	w6, w1, #2
	add	x4, x19, 128
	add	x6, x6, 65
	add	x6, x19, x6, lsl 1
	.p2align 2
.L3329:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 210]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 210]
	bne	.L3329
.L3328:
	cmp	w3, wzr
	bgt	.L3322
	ldr	x1, .LC842
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
	.p2align 3
.L3445:
	ldr	x1, .LC825
	mov	w3, 22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3443:
	ldr	x1, .LC856
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3308:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	bgt	.L3313
	add	x1, x19, x0, sxtw 1
	ldrsh	w3, [x21, 188]
	sub	w2, w0, #1
	strh	w3, [x1, 170]
	b	.L3325
.L3449:
	ldr	x1, .LC882
	mov	w2, w0
	mov	w3, 64
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3357
.L3461:
	ldr	x1, .LC840
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3419
.L3354:
	ldr	x1, .LC872
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3357
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	3
.LC789:
	.xword	.LC788
	.align	3
.LC791:
	.xword	.LC790
	.align	3
.LC793:
	.xword	.LC792
	.align	3
.LC795:
	.xword	.LC794
	.align	3
.LC797:
	.xword	.LC796
	.align	3
.LC799:
	.xword	.LC798
	.align	3
.LC801:
	.xword	.LC800
	.align	3
.LC803:
	.xword	.LC802
	.align	3
.LC805:
	.xword	.LC804
	.align	3
.LC807:
	.xword	.LC806
	.align	3
.LC809:
	.xword	.LC808
	.align	3
.LC811:
	.xword	.LC810
	.align	3
.LC813:
	.xword	.LC812
	.align	3
.LC815:
	.xword	.LC814
	.align	3
.LC817:
	.xword	.LC816
	.align	3
.LC819:
	.xword	.LC818
	.align	3
.LC821:
	.xword	.LC820
	.align	3
.LC823:
	.xword	.LC822
	.align	3
.LC825:
	.xword	.LC824
	.align	3
.LC827:
	.xword	.LC826
	.align	3
.LC828:
	.xword	g_event_report
	.align	3
.LC830:
	.xword	.LC829
	.align	3
.LC832:
	.xword	.LC831
	.align	3
.LC834:
	.xword	.LC833
	.align	3
.LC836:
	.xword	.LC835
	.align	3
.LC838:
	.xword	.LC837
	.align	3
.LC840:
	.xword	.LC839
	.align	3
.LC842:
	.xword	.LC841
	.align	3
.LC844:
	.xword	.LC843
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC848:
	.xword	.LC847
	.align	3
.LC850:
	.xword	.LC849
	.align	3
.LC852:
	.xword	.LC851
	.align	3
.LC854:
	.xword	.LC853
	.align	3
.LC856:
	.xword	.LC855
	.align	3
.LC858:
	.xword	.LC857
	.align	3
.LC860:
	.xword	.LC859
	.align	3
.LC862:
	.xword	.LC861
	.align	3
.LC864:
	.xword	.LC863
	.align	3
.LC866:
	.xword	.LC865
	.align	3
.LC868:
	.xword	.LC867
	.align	3
.LC870:
	.xword	.LC869
	.align	3
.LC872:
	.xword	.LC871
	.align	3
.LC874:
	.xword	.LC873
	.align	3
.LC876:
	.xword	.LC875
	.align	3
.LC878:
	.xword	.LC877
	.align	3
.LC880:
	.xword	.LC879
	.align	3
.LC882:
	.xword	.LC881
	.align	3
.LC884:
	.xword	.LC883
	.align	3
.LC886:
	.xword	.LC885
	.align	3
.LC888:
	.xword	.LC887
	.align	3
.LC890:
	.xword	.LC889
	.align	3
.LC892:
	.xword	.LC891
	.align	3
.LC894:
	.xword	.LC893
	.align	3
.LC896:
	.xword	.LC895
	.align	3
.LC898:
	.xword	.LC897
	.align	3
.LC900:
	.xword	.LC899
	.align	3
.LC902:
	.xword	.LC901
	.align	3
.LC904:
	.xword	.LC903
	.align	3
.LC906:
	.xword	.LC905
	.align	3
.LC908:
	.xword	.LC907
	.align	3
.LC910:
	.xword	.LC909
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC912
	ldr	x0, [x19, 2936]
	bl	HEVC_ue_v
	mov	w21, w0
	ldr	w3, [x19, 164]
	cmp	w0, w3
	bcs	.L3468
	mov	w20, 5036
	umull	x20, w0, w20
	ldr	x0, [x19, 2960]
	add	x1, x0, x20
	ldrb	w0, [x0, x20]
	cbnz	w0, .L3469
	str	w21, [x1, 28]
	mov	x0, x19
	ldr	x1, [x19, 2960]
	add	x1, x1, x20
	bl	HEVC_ProcessPPS
	mov	w22, w0
	cbnz	w0, .L3470
	ldr	x0, [x19, 2960]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2960]
	strb	w1, [x0, x20]
.L3464:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3469:
	ldr	x25, .LC915
	mov	x2, 5036
	ldr	x24, .LC916
	mov	w1, 0
	add	x23, x24, 3328
	ldr	x3, [x25, 96]
	mov	x0, x23
	blr	x3
	str	w21, [x23, 28]
	mov	x1, x23
	mov	x0, x19
	bl	HEVC_ProcessPPS
	mov	w22, w0
	cbnz	w0, .L3471
	ldr	x0, [x19, 2960]
	mov	w1, 1
	ldr	x3, [x25, 112]
	mov	x2, 5036
	strb	w1, [x23, 1]
	add	x0, x0, x20
	strb	w1, [x24, 3328]
	mov	x1, x23
	blr	x3
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3471:
	ldr	x1, .LC918
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3464
	.p2align 3
.L3468:
	ldr	x1, .LC914
	mov	w2, w0
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3464
.L3470:
	ldr	x1, .LC918
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2960]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2960]
	strb	wzr, [x0, x20]
	b	.L3464
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	3
.LC912:
	.xword	.LC911
	.align	3
.LC914:
	.xword	.LC913
	.align	3
.LC915:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC916:
	.xword	.LANCHOR6
	.align	3
.LC918:
	.xword	.LC917
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x28, 5572]
	mov	w4, 5036
	ldr	w0, [x28, 5588]
	ldr	x2, [x28, 2960]
	cmp	w1, 1
	smaddl	x2, w0, w4, x2
	beq	.L3546
	cbnz	w1, .L3476
	ldrb	w0, [x2, 11]
	cbz	w0, .L3476
.L3474:
	ldr	x1, .LC921
	ldr	x0, [x28, 2936]
	ldr	w19, [x2, 32]
	add	x2, x28, 4096
	mov	x21, x2
	ldr	x20, [x28, 2952]
	str	x2, [x29, 104]
	bl	HEVC_ue_v
	cmp	w0, 7
	str	w0, [x28, 5708]
	add	x22, x21, 1612
	bhi	.L3547
	mov	w1, 12668
	smaddl	x19, w19, w1, x20
	ldr	w1, [x19, 60]
	cbnz	w1, .L3548
	str	w0, [x22, 132]
.L3518:
	ldr	w0, [x28, 5628]
	mov	w20, 0
	cbz	w0, .L3488
	.p2align 2
.L3531:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5628]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L3531
	ldr	w0, [x19, 60]
	cbz	w0, .L3484
	mov	w20, 0
	cbz	w1, .L3488
	.p2align 2
.L3530:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5628]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L3530
.L3484:
	mov	w27, 0
	cbz	w1, .L3488
	ldr	x0, [x29, 104]
	ldr	x26, .LC939
	add	x21, x0, 1612
	b	.L3529
	.p2align 3
.L3490:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 5712]
	str	w0, [x20, 5844]
.L3492:
	ldr	w0, [x19, 60]
	cbz	w0, .L3494
	add	x0, x29, 240
	add	x0, x0, x22, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L3495
	lsl	x22, x22, 3
	ldr	w2, [x21, 132]
	add	x1, x28, x22
	add	x22, x21, x22
	mov	w0, 1
	lsl	w0, w0, w2
	str	wzr, [x1, 6036]
	str	w0, [x1, 5908]
	str	w0, [x22, 204]
	str	wzr, [x22, 332]
.L3494:
	ldr	w0, [x28, 5628]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L3488
.L3529:
	uxtw	x22, w27
	add	x0, x29, 240
	lsl	x20, x22, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L3490
	ldr	x1, .LC931
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L3549
	ldr	w2, [x21]
	add	x20, x28, x20
	mov	w23, 1
	ldr	x1, .LC935
	lsl	w2, w23, w2
	add	w0, w2, w0
	str	w0, [x20, 5844]
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	str	w0, [x20, 5712]
	bls	.L3492
	ldr	x1, .LC937
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
	.p2align 3
.L3546:
	ldrb	w0, [x2, 10]
	cbnz	w0, .L3474
.L3476:
	mov	w0, 0
.L3544:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L3495:
	ldr	x0, [x28, 2936]
	mov	x1, x26
	add	x20, x22, 1
	add	x25, x28, x22, lsl 3
	mov	w24, 128
	mov	w22, 1
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	add	x20, x28, x20, lsl 3
	mov	w23, 127
	ldr	x1, .LC943
	bhi	.L3550
.L3496:
	ldr	w6, [x21, 132]
	lsl	w6, w22, w6
	add	w0, w6, w0
	str	w0, [x25, 5908]
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w6, -128
	bhi	.L3551
	ldr	w1, [x25, 5908]
	add	x25, x25, 4
	ldr	w7, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w7
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w23, le
	cmn	w0, #128
	csel	w0, w0, w6, ge
	cmp	x20, x25
	str	w0, [x25, 6032]
	beq	.L3494
	ldr	x0, [x28, 2936]
	mov	x1, x26
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	ldr	x1, .LC943
	bls	.L3496
.L3550:
	ldr	x1, .LC941
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L3488:
	ldr	w0, [x28, 5572]
	cbnz	w0, .L3476
	ldr	w0, [x28, 5632]
	cbz	w0, .L3476
	mov	w20, 0
	.p2align 2
.L3502:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5632]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L3502
	ldr	w0, [x19, 60]
	cbnz	w0, .L3552
.L3503:
	mov	w25, 0
	cbz	w1, .L3476
	ldr	x0, [x29, 104]
	ldr	x23, .LC955
	add	x21, x0, 1612
	b	.L3527
	.p2align 3
.L3507:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 5776]
	str	w0, [x20, 6164]
.L3509:
	ldr	w0, [x19, 60]
	cbz	w0, .L3511
	add	x0, x29, 240
	add	x0, x0, x26, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L3512
	lsl	x26, x26, 3
	ldr	w4, [x21, 132]
	add	x1, x28, x26
	add	x26, x21, x26
	mov	w0, 1
	lsl	w0, w0, w4
	str	wzr, [x1, 6356]
	str	w0, [x1, 6228]
	str	w0, [x26, 524]
	str	wzr, [x26, 652]
.L3511:
	ldr	w0, [x28, 5632]
	add	w25, w25, 1
	cmp	w0, w25
	bls	.L3476
.L3527:
	uxtw	x26, w25
	add	x0, x29, 240
	lsl	x20, x26, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L3507
	ldr	x1, .LC947
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L3553
	ldr	w1, [x21]
	add	x20, x28, x20
	mov	w27, 1
	lsl	w1, w27, w1
	add	w0, w1, w0
	str	w0, [x20, 6164]
	ldr	x1, .LC951
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	str	w0, [x20, 5776]
	add	w0, w0, 128
	cmp	w0, 255
	bls	.L3509
	ldr	x1, .LC953
	mov	w0, w27
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
	.p2align 3
.L3512:
	add	x22, x28, x26, lsl 3
	add	x26, x26, 1
	mov	w20, 1
	mov	w24, 128
	add	x26, x28, x26, lsl 3
	mov	w27, 127
.L3515:
	ldr	x0, [x28, 2936]
	mov	x1, x23
	bl	HEVC_se_v
	add	w5, w0, 128
	cmp	w5, 255
	ldr	x1, .LC959
	bhi	.L3554
	ldr	w5, [x21, 132]
	lsl	w5, w20, w5
	add	w0, w5, w0
	str	w0, [x22, 6228]
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w5, -128
	bhi	.L3555
	ldr	w1, [x22, 6228]
	add	x22, x22, 4
	ldr	w6, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w6
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w27, le
	cmn	w0, #128
	csel	w0, w0, w5, ge
	str	w0, [x22, 6352]
	cmp	x22, x26
	bne	.L3515
	b	.L3511
	.p2align 3
.L3548:
	ldr	x1, .LC925
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 14
	bhi	.L3556
	ldr	w1, [x28, 5708]
	add	w0, w0, w1
	str	w0, [x22, 132]
	cmp	w0, 7
	bls	.L3518
	ldr	x1, .LC929
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
	.p2align 3
.L3551:
	ldr	x1, .LC945
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3552:
	mov	w20, 0
	cbz	w1, .L3476
	.p2align 2
.L3528:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5632]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L3528
	b	.L3503
.L3549:
	ldr	x1, .LC933
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3554:
	ldr	x1, .LC957
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3555:
	ldr	x1, .LC961
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3553:
	ldr	x1, .LC949
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3547:
	ldr	x1, .LC923
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
.L3556:
	ldr	x1, .LC927
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3544
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	3
.LC921:
	.xword	.LC920
	.align	3
.LC923:
	.xword	.LC922
	.align	3
.LC925:
	.xword	.LC924
	.align	3
.LC927:
	.xword	.LC926
	.align	3
.LC929:
	.xword	.LC928
	.align	3
.LC931:
	.xword	.LC930
	.align	3
.LC933:
	.xword	.LC932
	.align	3
.LC935:
	.xword	.LC934
	.align	3
.LC937:
	.xword	.LC936
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC941:
	.xword	.LC940
	.align	3
.LC943:
	.xword	.LC942
	.align	3
.LC945:
	.xword	.LC944
	.align	3
.LC947:
	.xword	.LC946
	.align	3
.LC949:
	.xword	.LC948
	.align	3
.LC951:
	.xword	.LC950
	.align	3
.LC953:
	.xword	.LC952
	.align	3
.LC955:
	.xword	.LC954
	.align	3
.LC957:
	.xword	.LC956
	.align	3
.LC959:
	.xword	.LC958
	.align	3
.LC961:
	.xword	.LC960
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x24, x28, 4096
	bl	_mcount
	ldr	x2, [x28, 2976]
	mov	w1, 1
	ldr	x0, [x28, 2936]
	ldr	w20, [x2, 24]
	bl	BsGet
	strb	w0, [x24, 1456]
	ldr	w25, [x28, 5580]
	sub	w0, w25, #16
	str	w0, [x29, 132]
	cmp	w0, 5
	bls	.L3873
.L3558:
	ldr	x1, .LC963
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	str	w0, [x28, 5588]
	ldr	w4, [x28, 164]
	tbnz	w0, #31, .L3560
	cmp	w0, w4
	bge	.L3560
	mov	x0, x28
	bl	HEVC_VpsSpsPpsCheck
	cbnz	w0, .L3874
	ldr	x0, [x28, 2960]
	mov	w3, 5036
	ldr	w21, [x28, 5588]
	mov	w2, 12668
	ldr	x1, [x28, 2952]
	ldr	x23, [x28, 2944]
	smaddl	x21, w21, w3, x0
	ldr	w19, [x21, 32]
	ldrb	w0, [x21, 2]
	smaddl	x19, w19, w2, x1
	ldr	w22, [x19, 48]
	cbnz	w0, .L3875
.L3566:
	strb	wzr, [x24, 1457]
.L3567:
	ldp	w2, w3, [x19, 140]
	cbz	w2, .L3569
	cbz	w3, .L3569
	ldp	w0, w1, [x19, 64]
	add	w0, w2, w0
	add	w1, w3, w1
	sub	w1, w1, #1
	sub	w0, w0, #1
	udiv	w0, w0, w2
	udiv	w2, w1, w3
	mov	w3, 1
	mov	w1, 0
	mul	w2, w0, w2
	ldr	w0, [x19, 172]
	cmp	w2, 1
	lsl	w0, w0, 1
	lsl	w26, w3, w0
	ble	.L3571
	.p2align 2
.L3572:
	add	w1, w1, 1
	lsl	w0, w3, w1
	cmp	w2, w0
	bgt	.L3572
.L3571:
	ldrb	w0, [x24, 1456]
	str	wzr, [x29, 136]
	cbz	w0, .L3876
.L3573:
	ldr	w0, [x28, 192]
	str	w0, [x28, 5564]
	ldrb	w0, [x24, 1457]
	cbnz	w0, .L3576
	ldrb	w26, [x28, 1]
	ldr	w0, [x21, 36]
	cmp	w26, 1
	beq	.L3577
	mov	w26, 0
	cbz	w0, .L3581
	.p2align 2
.L3810:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	add	w26, w26, w1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w26
	bhi	.L3810
.L3581:
	ldr	x1, .LC974
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	cmp	w0, 2
	str	w0, [x28, 5572]
	bhi	.L3877
	ldrb	w0, [x21, 4]
	cbnz	w0, .L3878
.L3584:
	sub	w0, w25, #19
	str	w0, [x29, 116]
	mov	w0, 24912
	umull	x22, w22, w0
	add	x0, x23, x22
	ldrb	w22, [x28, 1]
	str	x0, [x29, 104]
	cmp	w22, 1
	beq	.L3879
	ldr	w0, [x29, 116]
	str	xzr, [x29, 120]
	str	wzr, [x29, 140]
	cmp	w0, 1
	bls	.L3589
.L3917:
	cbz	w22, .L3880
.L3590:
	ldr	w1, [x19, 116]
	mov	w2, 1
	ldr	w0, [x28, 188]
	lsl	w1, w2, w1
	ldr	w2, [x29, 140]
	mov	w3, w1
	str	w3, [x29, 128]
	udiv	w1, w0, w1
	msub	w1, w1, w3, w0
	cmp	w2, w1
	sub	w0, w0, w1
	bcs	.L3591
	sub	w2, w1, w2
	cmp	w2, w3, lsr 1
	bcc	.L3591
	add	w0, w0, w3
.L3592:
	ldr	w1, [x28, 5580]
	add	x20, x28, x20, uxtw 2
	sub	w1, w1, #16
	cmp	w1, 2
	ldr	w1, [x29, 140]
	csel	w0, w0, wzr, hi
	add	w3, w0, w1
	str	w3, [x28, 5564]
	ldr	w2, [x20, 212]
	cmp	w3, w2
	bge	.L3594
	ldrb	w0, [x24, 1456]
	cmp	w0, 1
	beq	.L3881
.L3594:
	ldr	w0, [x28, 2356]
	cbnz	w0, .L3595
	ldr	w0, [x28, 5564]
	str	w0, [x28, 192]
.L3595:
	ldr	w0, [x28, 5576]
	cbnz	w0, .L3596
	ldr	w0, [x28, 5580]
	cmp	w0, 15
	bhi	.L3597
	mov	w1, 1
	tbz	x0, 0, .L3597
.L3598:
	sub	w0, w0, #7
	tst	w0, -3
	cset	w0, ne
	tst	w1, w0
	beq	.L3596
	ldr	w0, [x28, 5564]
	str	w0, [x28, 188]
	.p2align 2
.L3596:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3599
	ldr	w3, [x19, 176]
	mov	w1, 0
	mov	w2, 1
	mov	w0, 0
	cmp	w3, 1
	bls	.L3601
	.p2align 2
.L3809:
	add	w1, w1, 1
	lsl	w0, w2, w1
	cmp	w0, w3
	bcc	.L3809
	mov	w0, 0
	cbnz	w1, .L3882
.L3604:
	sxtw	x4, w0
	mov	x2, 164
	lsl	x1, x4, 2
	add	x0, x24, 2388
	sub	x1, x1, x4
	lsl	x3, x1, 3
	sub	x1, x3, x1
	lsl	x1, x1, 1
	sub	x1, x1, x4
	add	x1, x19, x1, lsl 2
	add	x1, x1, 2164
	bl	memcpy
	str	x0, [x29, 120]
.L3602:
	ldrb	w0, [x19, 8]
	cbz	w0, .L3606
	ldr	w0, [x19, 180]
	ldr	w1, [x24, 2392]
	ldr	w20, [x28, 6484]
	add	w20, w20, w1
	cbnz	w0, .L3883
	mov	w25, 0
	str	wzr, [x29, 156]
.L3607:
	ldr	x1, .LC988
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	ldr	w3, [x24, 2392]
	add	x1, x24, 2388
	ldr	w2, [x28, 6484]
	add	w0, w0, w25
	mov	w4, w0
	add	w0, w2, w3
	add	w0, w0, w4
	str	w4, [x29, 152]
	cmp	w0, 16
	bhi	.L3884
	ldr	w2, [x29, 152]
	mov	w23, 0
	mov	w27, 0
	add	w0, w20, w2
	str	w0, [x29, 112]
	sub	w22, w0, #1
	cbz	w2, .L3623
	str	x1, [x29, 144]
	b	.L3808
	.p2align 3
.L3887:
	ldr	w1, [x29, 156]
	cbnz	w1, .L3885
.L3614:
	sxtw	x0, w0
	ldr	x1, [x29, 144]
	add	x4, x19, x0
	add	x1, x1, x26
	add	x0, x19, x0, lsl 2
	ldrb	w4, [x4, 13]
	ldr	w20, [x0, 196]
	strb	w4, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2936]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbnz	w0, .L3886
.L3618:
	str	w20, [x1, 6584]
	csel	w23, w23, wzr, ne
	str	wzr, [x1, 5640]
	ldr	w0, [x28, 5564]
	sub	w20, w20, w0
	str	w20, [x1, 6516]
.L3620:
	ldr	w0, [x29, 152]
	add	w27, w27, 1
	sub	w22, w22, #1
	cmp	w0, w27
	beq	.L3623
.L3808:
	cmp	w27, w25
	uxtw	x26, w22
	mov	w0, 0
	bcc	.L3887
	ldr	w1, [x19, 120]
	uxtw	x26, w22
	ldr	x0, [x28, 2936]
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 144]
	add	x1, x1, x26
	strb	w0, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2936]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbz	w0, .L3618
.L3886:
	ldr	x1, .LC994
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	add	w23, w23, w0
	add	x3, x28, x26, lsl 2
	cmp	w27, wzr
	ccmp	w27, w25, 4, ne
	mov	w1, 1
	str	w1, [x3, 5640]
	cset	w1, eq
	cmp	w1, wzr
	csel	w23, w23, w0, eq
	ldr	w0, [x29, 128]
	ldr	w1, [x28, 5564]
	msub	w20, w23, w0, w20
	ldr	w0, [x29, 140]
	sub	w0, w1, w0
	add	w20, w20, w0
	str	w20, [x3, 6584]
	sub	w20, w20, w1
	str	w20, [x3, 6516]
	b	.L3620
	.p2align 3
.L3623:
	ldr	w0, [x29, 112]
	str	w0, [x24, 2396]
	cmp	w0, 16
	bhi	.L3888
.L3606:
	ldrb	w0, [x19, 9]
	cbnz	w0, .L3889
	strb	wzr, [x24, 1460]
	ldrb	w22, [x28, 1]
.L3625:
	cmp	w22, 1
	beq	.L3890
.L3627:
	ldrb	w0, [x19, 6]
	cbnz	w0, .L3891
.L3728:
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bls	.L3892
.L3657:
	ldr	w0, [x28, 5572]
	cmp	w0, 2
	bne	.L3893
.L3658:
	ldrb	w0, [x24, 1460]
	cbnz	w0, .L3732
.L3681:
	mov	w4, 2
.L3688:
	ldrb	w0, [x21, 11]
	cbz	w0, .L3679
	cbnz	w4, .L3679
.L3691:
	mov	x0, x28
	bl	HEVC_DecPredWeightTable
	cbnz	w0, .L3894
	ldr	w4, [x28, 5572]
.L3679:
	cmp	w4, 2
	beq	.L3692
	ldr	x1, .LC1024
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	mov	w3, 4
	mov	w1, 5
	sub	w3, w3, w0
	sub	w2, w1, w0
	cmp	w3, 4
	str	w2, [x28, 5600]
	bhi	.L3895
.L3692:
	ldr	x1, .LC1028
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	ldr	w2, [x21, 48]
	mov	w1, 51
	add	w0, w0, w2
	str	w0, [x28, 5568]
	ldr	w3, [x19, 92]
	neg	w2, w3
	cmp	w0, w2
	ccmp	w0, w1, 0, ge
	bgt	.L3896
	ldrb	w0, [x21, 9]
	cbnz	w0, .L3897
.L3694:
	ldrb	w0, [x21, 18]
	cbz	w0, .L3864
	ldrb	w0, [x21, 19]
	cbnz	w0, .L3898
.L3700:
	ldrb	w0, [x21, 20]
	strb	w0, [x24, 1465]
	ldr	w1, [x21, 76]
	str	w1, [x28, 5612]
	ldr	w1, [x21, 80]
	str	w1, [x28, 5616]
.L3699:
	ldrb	w2, [x19, 6]
	mov	w1, 0
	cbz	w2, .L3703
	ldrh	w1, [x28, 5554]
	cmp	w1, wzr
	cset	w1, ne
.L3703:
	ldrb	w2, [x21, 17]
	cbz	w2, .L3704
	cmp	w0, wzr
	cset	w0, eq
	orr	w1, w0, w1
	cbnz	w1, .L3899
.L3704:
	strb	w2, [x24, 1466]
.L3576:
	ldr	w0, [x21, 12]
	tst	w0, 16776960
	bne	.L3705
.L3712:
	ldrb	w0, [x21, 23]
	cbnz	w0, .L3900
.L3707:
	ldr	w0, [x29, 136]
	cbnz	w0, .L3901
	ldrb	w0, [x28, 3]
	cbz	w0, .L3721
	ldr	w0, [x29, 132]
	cmp	w0, 5
	bhi	.L3722
	ldr	w0, [x28, 5584]
	mov	w2, 1
	add	x1, x28, x0
	strb	w2, [x1, 6]
.L3723:
	ldr	w1, [x28, 5564]
	cmp	w1, wzr
	ldr	w1, [x29, 132]
	ccmp	w1, 5, 2, ne
	bhi	.L3724
	ldr	w1, [x28, 5580]
	add	x0, x28, x0
	cmp	w1, 21
	beq	.L3902
	.p2align 2
.L3865:
	strb	wzr, [x0, 4]
.L3726:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 5704]
	mov	x0, x28
	bl	HEVC_ReadByteAlignment
	cmp	w0, wzr
	csetm	w0, ne
.L3855:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L3875:
	ldrb	w0, [x24, 1456]
	cbnz	w0, .L3566
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1457]
	b	.L3567
	.p2align 3
.L3901:
	ldr	w0, [x28, 5584]
	add	x1, x28, x0
	ldrb	w1, [x1, 6]
	cbnz	w1, .L3723
.L3724:
	add	x0, x28, x0
	b	.L3865
	.p2align 3
.L3591:
	ldr	w2, [x29, 140]
	cmp	w2, w1
	bls	.L3592
	sub	w1, w2, w1
	ldr	w2, [x29, 128]
	cmp	w1, w2, lsr 1
	sub	w1, w0, w2
	csel	w0, w1, w0, hi
	b	.L3592
	.p2align 3
.L3873:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L3558
	.p2align 3
.L3876:
	ldr	x0, [x28, 2936]
	bl	BsGet
	str	w0, [x28, 5592]
	ldp	w1, w3, [x19, 188]
	mul	w3, w1, w3
	tbnz	w0, #31, .L3575
	cmp	w3, w0
	bls	.L3575
	mul	w0, w26, w0
	str	w0, [x29, 136]
	b	.L3573
	.p2align 3
.L3705:
	ldr	x1, .LC1052
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	mov	w20, w0
	ldr	w0, [x21, 12]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L3903
	cmp	w0, 256
	ldr	w0, [x21, 68]
	beq	.L3904
	ldr	w1, [x19, 192]
	mul	w0, w0, w1
	sub	w0, w0, #1
.L3709:
	cmp	w0, 255
	mov	w1, 255
	csel	w3, w0, w1, ls
	cmp	w20, w3
	bhi	.L3905
	cbz	w20, .L3712
	ldr	x1, .LC1056
	mov	w19, 0
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	cmp	w0, 31
	add	w22, w0, 1
	bhi	.L3906
	.p2align 2
.L3807:
	ldr	x0, [x28, 2936]
	mov	w1, w22
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L3807
	ldrb	w0, [x21, 23]
	cbz	w0, .L3707
.L3900:
	ldr	x1, .LC1060
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	cmp	w0, 256
	mov	w20, w0
	bhi	.L3907
	ldr	x0, [x28, 2936]
	bl	BsResidBits
	cmp	w20, w0
	bhi	.L3718
	mov	w19, 0
	cbz	w20, .L3707
	.p2align 2
.L3806:
	ldr	x0, [x28, 2936]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L3806
	b	.L3707
	.p2align 3
.L3721:
	ldr	w0, [x29, 132]
	cmp	w0, 5
	bhi	.L3722
	ldr	w0, [x28, 5584]
	add	x1, x28, x0
	add	x0, x28, x0
	strb	wzr, [x1, 6]
	b	.L3865
.L3903:
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	b	.L3709
	.p2align 3
.L3597:
	sub	w1, w0, #16
	cmp	w1, 7
	cset	w1, ls
	b	.L3598
.L3882:
	ldr	x0, [x28, 2936]
	bl	BsGet
	ldr	w3, [x19, 176]
	tbnz	w0, #31, .L3908
.L3601:
	sub	w3, w3, #1
	cmp	w3, w0
	bcs	.L3604
.L3605:
	ldr	x1, .LC982
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3885:
	ldr	x0, [x28, 2936]
	bl	BsGet
	ldr	w4, [x19, 180]
	sub	w4, w4, #1
	tbnz	w0, #31, .L3616
	cmp	w4, w0
	bcs	.L3614
.L3616:
	ldr	x1, .LC992
	mov	w3, w0
	mov	w2, w27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3893:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1461]
	cbnz	w0, .L3909
	ldr	w0, [x21, 40]
	ldr	w4, [x28, 5572]
	str	w0, [x28, 5628]
	cbnz	w4, .L3666
	ldr	w0, [x21, 44]
	mov	w20, 0
	mov	w22, 0
	str	w0, [x28, 5632]
.L3664:
	ldr	x0, [x29, 120]
	cbz	x0, .L3910
	ldr	x0, [x29, 120]
	ldr	w2, [x0, 8]
	cmp	w2, 16
	bhi	.L3668
	mov	w3, 0
	cbz	w2, .L3670
	ldr	x0, [x29, 120]
	sub	w2, w2, #1
	add	x2, x2, 13
	mov	w3, 0
	add	x2, x0, x2
	add	x0, x0, 12
	.p2align 2
.L3672:
	ldrb	w1, [x0], 1
	cmp	w1, wzr
	csinc	w3, w3, w3, eq
	cmp	x0, x2
	bne	.L3672
.L3670:
	ldrb	w0, [x28, 1]
	cmp	w0, 1
	beq	.L3911
.L3673:
	ldrb	w0, [x21, 22]
	cmp	w0, wzr
	ccmp	w3, 1, 4, ne
	ble	.L3912
	add	x2, x24, 2552
	add	x1, x24, 1456
	mov	x0, x28
	bl	HEVC_DecRefPicListsModification
	cbnz	w0, .L3858
	ldr	w4, [x28, 5572]
	cbnz	w4, .L3674
.L3730:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1462]
	ldr	w4, [x28, 5572]
.L3674:
	cmp	w4, 2
	beq	.L3658
.L3731:
	ldrb	w0, [x21, 5]
	cbnz	w0, .L3913
.L3675:
	ldrb	w0, [x24, 1460]
	cbz	w0, .L3684
	cbz	w4, .L3914
	mov	w0, 1
	cmp	w4, 2
	strb	w0, [x24, 1464]
	beq	.L3681
.L3680:
	ldr	w0, [x28, 5628]
	cmp	w0, 1
	bls	.L3863
.L3683:
	ldr	x1, .LC1018
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	str	w0, [x28, 5596]
	ldrb	w2, [x24, 1464]
	cbnz	w2, .L3915
	sub	w4, w20, #1
.L3686:
	cmp	w4, w0
	ccmp	w0, wzr, 1, cs
	bge	.L3863
	ldr	x1, .LC1020
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3863:
	ldr	w4, [x28, 5572]
.L3684:
	ldrb	w0, [x21, 10]
	cbz	w0, .L3688
	cmp	w4, 1
	bne	.L3688
	b	.L3691
	.p2align 3
.L3722:
	ldr	w0, [x28, 5584]
	add	x0, x28, x0
	b	.L3865
.L3898:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3700
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1465]
	cbnz	w0, .L3699
	ldr	x1, .LC1044
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 5612]
	bhi	.L3916
.L3701:
	ldr	x1, .LC1048
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 5616]
	bls	.L3864
	ldr	x1, .LC1050
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 80]
	str	w0, [x28, 5616]
	.p2align 2
.L3864:
	ldrb	w0, [x24, 1465]
	b	.L3699
	.p2align 3
.L3878:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	b	.L3584
	.p2align 3
.L3912:
	cbnz	w4, .L3731
	b	.L3730
	.p2align 3
.L3879:
	cbz	w20, .L3586
	uxtw	x0, w20
	ldr	x1, [x29, 104]
	add	x0, x0, 4096
	add	x0, x1, x0, lsl 2
	ldr	w0, [x0, 180]
	add	x0, x1, x0
	add	x0, x0, 12288
	ldrb	w0, [x0, 135]
	cbnz	w0, .L3586
.L3587:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2936]
	bl	BsGet
	ldrb	w22, [x28, 1]
	str	w0, [x29, 140]
.L3588:
	add	x0, x24, 2388
	str	x0, [x29, 120]
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bhi	.L3917
.L3589:
	ldr	w0, [x28, 2356]
	str	wzr, [x28, 5564]
	cbnz	w0, .L3626
	str	wzr, [x28, 192]
.L3626:
	ldr	w0, [x28, 5576]
	cbnz	w0, .L3625
	str	wzr, [x28, 188]
	b	.L3625
	.p2align 3
.L3586:
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bhi	.L3587
	str	wzr, [x29, 140]
	b	.L3588
	.p2align 3
.L3891:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1458]
	mov	w1, 1
	ldr	x0, [x28, 2936]
	bl	BsGet
	strb	w0, [x24, 1459]
	b	.L3728
	.p2align 3
.L3560:
	ldr	x2, .LC964
	mov	w3, w0
	ldr	x1, .LC966
	mov	w0, 1
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3892:
	strb	wzr, [x24, 1460]
	b	.L3657
	.p2align 3
.L3897:
	ldr	x1, .LC1032
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 5604]
	bhi	.L3918
	ldr	w3, [x21, 60]
	add	w1, w0, w3
	add	w1, w1, 12
	cmp	w1, 24
	bhi	.L3919
	ldr	x1, .LC1038
	ldr	x0, [x28, 2936]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 5608]
	bhi	.L3920
	ldr	w1, [x21, 64]
	add	w2, w0, w1
	add	w0, w2, 12
	cmp	w0, 24
	bls	.L3694
	ldr	x1, .LC1042
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3599:
	ldr	w3, [x19, 176]
	add	x2, x24, 2388
	mov	x1, x19
	mov	x0, x28
	str	x2, [x29, 120]
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L3602
	ldr	x1, .LC980
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
	.p2align 3
.L3880:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2936]
	bl	BsGet
	str	w0, [x29, 140]
	b	.L3590
.L3913:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1463]
	ldr	w4, [x28, 5572]
	b	.L3675
.L3889:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1460]
	ldrb	w22, [x28, 1]
	b	.L3625
.L3911:
	ldr	w0, [x28, 6912]
	add	w3, w3, w0
	b	.L3673
.L3666:
	mov	w22, 0
	str	wzr, [x28, 5632]
.L3665:
	cmp	w4, 2
	beq	.L3658
	mov	w20, 0
	b	.L3664
.L3577:
	cbz	w0, .L3581
	ldr	x0, [x28, 2936]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 1
	bls	.L3581
	ldr	x0, [x28, 2936]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 2
	bls	.L3581
	ldr	x0, [x28, 2936]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 3
	bls	.L3581
	mov	w26, 3
	.p2align 2
.L3582:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	add	w26, w26, 1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w26
	bhi	.L3582
	b	.L3581
.L3909:
	ldr	x1, .LC1004
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	add	w22, w0, 1
	cmp	w22, 16
	bhi	.L3921
	ldr	w4, [x28, 5572]
	str	w22, [x28, 5628]
	cbz	w4, .L3922
	str	wzr, [x28, 5632]
	b	.L3665
.L3732:
	mov	w0, 1
	mov	w4, 2
	strb	w0, [x24, 1464]
	b	.L3684
.L3899:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1466]
	b	.L3576
.L3915:
	sub	w4, w22, #1
	b	.L3686
.L3902:
	mov	w1, 1
	strb	w1, [x0, 4]
	b	.L3726
.L3881:
	ldr	x1, .LC978
	bl	dprint_vfmw
	b	.L3594
.L3922:
	ldr	x1, .LC1008
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	add	w20, w0, 1
	cmp	w20, 16
	bhi	.L3923
	ldr	w4, [x28, 5572]
	str	w20, [x28, 5632]
	cmp	w4, 2
	bne	.L3664
	b	.L3658
	.p2align 3
.L3907:
	ldr	x1, .LC1062
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3888:
	ldr	x1, .LC996
	mov	w3, 16
	ldr	w2, [x29, 112]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3908:
	sub	w3, w3, #1
	b	.L3605
	.p2align 3
.L3914:
	ldr	x0, [x28, 2936]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1464]
	ldr	w4, [x28, 5572]
	cmp	w4, 2
	beq	.L3692
	cbnz	w0, .L3680
	ldr	w0, [x28, 5632]
	cmp	w0, 1
	bhi	.L3683
	b	.L3684
.L3569:
	ldr	x1, .LC970
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3890:
	ldr	x3, [x28, 2976]
	ldr	w0, [x3, 24]
	cbz	w0, .L3628
	ldr	x2, [x29, 104]
	add	x23, x2, 12288
	ldrb	w1, [x23, 134]
	cbnz	w1, .L3629
	add	x0, x2, x0, uxtw 2
	add	x20, x0, 16384
	ldr	w0, [x20, 196]
	cmp	w0, wzr
	ble	.L3630
	ldr	x0, [x28, 2936]
	mov	w1, w22
	bl	BsGet
	uxtb	w0, w0
	ldr	w4, [x20, 196]
	cbz	w0, .L3632
	cmp	w4, 1
	ble	.L3632
	ldrb	w0, [x23, 133]
	cbnz	w0, .L3633
	mov	w1, 0
	ldr	x0, [x28, 2936]
	bls	.L3634
.L3635:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w4, w2
	bhi	.L3635
.L3634:
	bl	BsGet
	add	w2, w0, 1
	str	w2, [x24, 2816]
	ldr	w4, [x20, 196]
	cmp	w2, w4
	bne	.L3924
.L3861:
	mov	w1, 0
.L3637:
	cmp	w4, 2
	bgt	.L3652
.L3639:
	cmp	w4, wzr
	ble	.L3627
.L3646:
	add	x0, x24, 2820
	mov	w2, 0
	b	.L3656
	.p2align 3
.L3926:
	ldr	w3, [x0]
.L3654:
	cmp	w3, 2
	add	x0, x0, 4
	bgt	.L3925
	add	w2, w2, 1
	cmp	w2, w4
	beq	.L3627
.L3656:
	mov	w3, w2
	cbnz	w1, .L3926
	str	w2, [x0]
	b	.L3654
.L3904:
	ldr	w1, [x21, 72]
	mul	w0, w0, w1
	sub	w0, w0, #1
	b	.L3709
.L3883:
	ldr	x1, .LC984
	ldr	x0, [x28, 2936]
	bl	HEVC_ue_v
	mov	w25, w0
	ldr	w3, [x19, 180]
	cmp	w0, w3
	bhi	.L3927
	cmp	w3, 1
	str	wzr, [x29, 156]
	bls	.L3607
	mov	w1, 1
	.p2align 2
.L3609:
	ldr	w0, [x29, 156]
	add	w0, w0, 1
	str	w0, [x29, 156]
	lsl	w0, w1, w0
	cmp	w3, w0
	bhi	.L3609
	b	.L3607
.L3874:
	ldr	w0, [x28, 260]
	cbz	w0, .L3564
	ldr	w0, [x28, 192]
	str	w0, [x28, 5564]
.L3565:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 5704]
	ldr	x1, .LC968
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3628:
	ldr	x1, [x29, 104]
	add	x1, x1, 12288
	ldrb	w1, [x1, 134]
.L3629:
	cmp	w1, 1
	beq	.L3928
.L3630:
	str	wzr, [x24, 2816]
	b	.L3627
.L3928:
	ldr	x1, [x28, 2944]
	add	x8, x1, x0, sxtw 2
	add	x8, x8, 16384
	ldr	w2, [x8, 196]
	cmp	w2, wzr
	ble	.L3748
	mov	x6, 4150
	sub	w2, w2, #1
	add	x6, x6, x0, sxtw 1
	ldr	w7, [x3, 28]
	add	x6, x6, x2
	mov	x2, 16596
	add	x0, x2, x0, sxtw 3
	mov	w4, 0
	add	x6, x1, x6, lsl 2
	add	x0, x1, x0
	add	x1, x1, 12288
	add	x2, x1, 132
	.p2align 2
.L3651:
	ldrsw	x1, [x0]
	add	x0, x0, 4
	add	x1, x1, 1036
	ldrsw	x1, [x2, x1, lsl 2]
	add	x3, x2, x1, lsl 2
	ldr	w3, [x3, 4168]
	cmp	w7, w3
	bgt	.L3649
	cbz	w7, .L3650
	ldrsw	x3, [x8, 180]
	add	x1, x3, x1, lsl 1
	add	x1, x2, x1, lsl 2
	ldr	w1, [x1, 12392]
	cbz	w1, .L3649
.L3650:
	add	w4, w4, 1
.L3649:
	cmp	x6, x0
	bne	.L3651
	str	w4, [x24, 2816]
	b	.L3861
.L3925:
	ldr	x1, .LC1002
	mov	w4, 2
	mov	w0, 1
	bl	dprint_vfmw
.L3642:
	ldr	x1, .LC1066
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3564:
	str	wzr, [x28, 5564]
	b	.L3565
.L3896:
	ldr	x1, .LC1030
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3575:
	ldr	x1, .LC972
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3877:
	ldr	x1, .LC976
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3718:
	ldr	x1, .LC1064
	mov	w2, w0
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3905:
	ldr	x1, .LC1054
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3668:
	ldr	x1, .LC1014
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3895:
	ldr	x1, .LC1026
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3916:
	ldr	x1, .LC1046
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 76]
	str	w0, [x28, 5612]
	b	.L3701
.L3632:
	cmp	w4, 1
	bne	.L3630
	str	w4, [x24, 2816]
.L3862:
	mov	w1, 0
	b	.L3646
.L3919:
	ldr	x1, .LC1036
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3884:
	ldr	x1, .LC990
	mov	w5, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3894:
	ldr	x1, .LC1022
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3920:
	ldr	x1, .LC1040
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3918:
	ldr	x1, .LC1034
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3633:
	str	w22, [x24, 2816]
	ldr	w4, [x20, 196]
	cmp	w4, 1
	beq	.L3862
.L3638:
	mov	w23, 0
	mov	w22, 1
	add	x25, x24, 2812
.L3645:
	ldr	w3, [x20, 196]
	mov	w1, 0
	ldr	x0, [x28, 2936]
	cmp	w3, 1
	bls	.L3643
	.p2align 2
.L3644:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w3, w2
	bhi	.L3644
.L3643:
	bl	BsGet
	add	x1, x25, x23, sxtw 2
	add	w23, w23, 1
	str	w0, [x1, 8]
	ldr	w4, [x25, 4]
	cmp	w23, w4
	blt	.L3645
	mov	w1, 1
	b	.L3637
.L3921:
	ldr	x1, .LC1006
	mov	w3, 16
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3906:
	ldr	x1, .LC1058
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3858:
	ldr	x1, .LC1016
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3652:
	ldr	x1, .LC1000
	mov	w3, 2
	mov	w2, w4
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3642
.L3927:
	ldr	x1, .LC986
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3924:
	cmp	w2, 2
	bgt	.L3640
	cmp	w2, wzr
	bgt	.L3638
	mov	w4, w2
	mov	w1, 1
	b	.L3639
	.p2align 3
.L3748:
	mov	w4, 0
	str	w4, [x24, 2816]
	b	.L3861
.L3910:
	ldr	x1, .LC1012
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3923:
	ldr	x1, .LC1010
	mov	w3, 16
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3855
.L3640:
	ldr	x1, .LC998
	mov	w3, 2
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3642
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	3
.LC963:
	.xword	.LC962
	.align	3
.LC964:
	.xword	.LANCHOR5
	.align	3
.LC966:
	.xword	.LC965
	.align	3
.LC968:
	.xword	.LC967
	.align	3
.LC970:
	.xword	.LC969
	.align	3
.LC972:
	.xword	.LC971
	.align	3
.LC974:
	.xword	.LC973
	.align	3
.LC976:
	.xword	.LC975
	.align	3
.LC978:
	.xword	.LC977
	.align	3
.LC980:
	.xword	.LC979
	.align	3
.LC982:
	.xword	.LC981
	.align	3
.LC984:
	.xword	.LC983
	.align	3
.LC986:
	.xword	.LC985
	.align	3
.LC988:
	.xword	.LC987
	.align	3
.LC990:
	.xword	.LC989
	.align	3
.LC992:
	.xword	.LC991
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC996:
	.xword	.LC995
	.align	3
.LC998:
	.xword	.LC997
	.align	3
.LC1000:
	.xword	.LC999
	.align	3
.LC1002:
	.xword	.LC1001
	.align	3
.LC1004:
	.xword	.LC1003
	.align	3
.LC1006:
	.xword	.LC1005
	.align	3
.LC1008:
	.xword	.LC1007
	.align	3
.LC1010:
	.xword	.LC1009
	.align	3
.LC1012:
	.xword	.LC1011
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1016:
	.xword	.LC1015
	.align	3
.LC1018:
	.xword	.LC1017
	.align	3
.LC1020:
	.xword	.LC1019
	.align	3
.LC1022:
	.xword	.LC1021
	.align	3
.LC1024:
	.xword	.LC1023
	.align	3
.LC1026:
	.xword	.LC1025
	.align	3
.LC1028:
	.xword	.LC1027
	.align	3
.LC1030:
	.xword	.LC1029
	.align	3
.LC1032:
	.xword	.LC1031
	.align	3
.LC1034:
	.xword	.LC1033
	.align	3
.LC1036:
	.xword	.LC1035
	.align	3
.LC1038:
	.xword	.LC1037
	.align	3
.LC1040:
	.xword	.LC1039
	.align	3
.LC1042:
	.xword	.LC1041
	.align	3
.LC1044:
	.xword	.LC1043
	.align	3
.LC1046:
	.xword	.LC1045
	.align	3
.LC1048:
	.xword	.LC1047
	.align	3
.LC1050:
	.xword	.LC1049
	.align	3
.LC1052:
	.xword	.LC1051
	.align	3
.LC1054:
	.xword	.LC1053
	.align	3
.LC1056:
	.xword	.LC1055
	.align	3
.LC1058:
	.xword	.LC1057
	.align	3
.LC1060:
	.xword	.LC1059
	.align	3
.LC1062:
	.xword	.LC1061
	.align	3
.LC1064:
	.xword	.LC1063
	.align	3
.LC1066:
	.xword	.LC1065
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 2976]
	cbz	x1, .L3931
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L3931:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrSlice
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 168]
	cbz	w2, .L3940
	.p2align 2
.L3943:
	ldr	x0, [x20, 3016]
	ldr	x0, [x0, w19, uxtw 3]
	mov	x1, x0
	cbz	x0, .L3938
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3016]
	str	xzr, [x0, w19, uxtw 3]
	ldr	w2, [x20, 168]
.L3938:
	add	w19, w19, 1
	cmp	w2, w19
	bhi	.L3943
.L3940:
	strb	wzr, [x20, 14]
	mov	w0, 2
	str	wzr, [x20, 204]
	str	w0, [x20, 176]
	mov	w0, 0
	str	wzr, [x20, 260]
	str	wzr, [x20, 268]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	add	x19, x20, 3544
	bl	_mcount
	add	x22, x20, 3680
	mov	x0, x20
	bl	HEVC_ClearAllSlice
	.p2align 2
.L3954:
	ldr	x0, [x19, 136]
	cbz	x0, .L3948
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3948:
	ldr	x0, [x19, 272]
	cbz	x0, .L3949
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3949:
	ldr	x0, [x19, 408]
	cbz	x0, .L3950
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3950:
	ldr	x0, [x19, 544]
	cbz	x0, .L3951
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3951:
	ldr	x0, [x19, -136]
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19, 544]
	cbz	x0, .L3952
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3952:
	ldr	x0, [x19]
	cbz	x0, .L3953
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3953:
	str	xzr, [x19, -136]
	add	x19, x19, 8
	str	xzr, [x19, -8]
	cmp	x22, x19
	bne	.L3954
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L4027
.L3955:
	ldr	x0, [x20, 3000]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 3368]
.L3956:
	cmp	w0, 17
	bhi	.L4028
.L3957:
	add	x4, x20, 3328
	ldr	x22, .LC1069
	add	x19, x20, 12288
	mov	x2, 280
	mov	w1, 0
	add	x0, x19, 1884
	ldr	x3, [x22, 96]
	mov	w23, 16
	stp	wzr, wzr, [x4, 44]
	stp	wzr, wzr, [x4, 52]
	str	wzr, [x20, 3388]
	str	wzr, [x20, 3396]
	str	wzr, [x20, 3400]
	blr	x3
	str	w23, [x20, 14172]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x19, 2164
	str	wzr, [x20, 14176]
	blr	x3
	str	w23, [x20, 14452]
	add	x1, x20, 3056
	add	x0, x20, 3192
	str	wzr, [x20, 14456]
	.p2align 2
.L3958:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L3958
	add	x1, x20, 3328
	str	wzr, [x20, 5620]
	.p2align 2
.L3959:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L3959
	str	wzr, [x20, 5624]
	cbnz	w21, .L3960
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	beq	.L3960
	ldr	w0, [x20, 184]
	cbz	w0, .L3980
.L3976:
	sub	w1, w0, #1
	add	x0, x20, 2156
	add	x1, x1, 540
	add	x1, x20, x1, lsl 2
	.p2align 2
.L3979:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L3979
.L3980:
	ldr	w2, [x20, 168]
	mov	w19, 0
	cbz	w2, .L3978
	.p2align 2
.L4006:
	ldr	x0, [x20, 3016]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L3981
	ldr	x3, [x20, 2976]
	cmp	x0, x3
	beq	.L3981
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3016]
	str	xzr, [x0, x21, lsl 3]
	ldr	w2, [x20, 168]
.L3981:
	cmp	w2, w19
	bhi	.L4006
.L3978:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3960:
	ldrb	w1, [x20, 1]
	mov	w0, 20
	stp	w0, w0, [x20, 180]
	cmp	w1, 1
	beq	.L4029
.L3962:
	mov	x0, x20
	bl	HEVC_ArrangeMem
.L3971:
	cbz	w0, .L3972
	cmp	w0, 2
	beq	.L4024
	ldr	x22, .LC1067
.L3973:
	ldr	x1, .LC1076
	add	x2, x22, 128
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4028:
	ldr	x22, .LC1067
	mov	w4, 17
	ldr	x1, .LC1068
	mov	w3, w4
	add	x2, x22, 128
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 3368]
	b	.L3957
	.p2align 3
.L4027:
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L3955
	ldr	w0, [x20, 2380]
	cbz	w0, .L3955
	ldr	x1, [x20, 3000]
	ldr	w1, [x1, 184]
	mul	w0, w0, w1
	add	w0, w0, 1
	str	w0, [x20, 3368]
	b	.L3956
	.p2align 3
.L4029:
	ldr	x0, [x20, 3032]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L3962
	ldr	w9, [x20, 2380]
	ldr	x13, [x20, 3000]
	cbz	w9, .L4030
	ldp	w8, w7, [x13, 140]
	mov	w19, 0
	mov	w21, 0
	neg	w11, w8
	neg	w10, w7
	mov	w1, 0
	mov	w3, 0
	mov	w2, 8160
	sub	w8, w8, #1
	sub	w7, w7, #1
	ldr	w12, [x20, 5584]
	b	.L3967
	.p2align 3
.L3965:
	cmp	w21, w1
	csel	w21, w21, w1, cs
	cmp	w19, w0
	csel	w19, w19, w0, cs
	sub	w1, w21, #32
	sub	w0, w19, #32
	cmp	w1, w2
	ccmp	w0, w2, 2, ls
	bhi	.L3966
	uxtb	w3, w4
	cmp	w9, w3
	mov	w1, w3
	bls	.L4031
.L3967:
	add	x0, x20, x3, uxtb 2
	cmp	w12, w1
	add	w4, w3, 1
	ldr	w1, [x0, 2388]
	ldr	w0, [x0, 2396]
	add	w1, w8, w1
	add	w0, w7, w0
	and	w1, w1, w11
	and	w0, w0, w10
	bne	.L3965
	ldr	w14, [x13, 128]
	ldp	w6, w5, [x13, 188]
	lsl	w6, w6, w14
	lsl	w5, w5, w14
	cmp	w1, w6
	csel	w1, w1, w6, cs
	cmp	w0, w5
	csel	w0, w0, w5, cs
	b	.L3965
.L3966:
	ldr	x22, .LC1067
	mov	w5, w19
	ldr	x1, .LC1073
	mov	w4, w21
	add	x2, x22, 144
	mov	w0, 0
	bl	dprint_vfmw
	b	.L3973
	.p2align 3
.L3972:
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	cmp	w0, 20
	mov	w0, 20
	ble	.L4032
	str	w0, [x20, 180]
.L4033:
	ldr	w0, [x20, 184]
	cbnz	w0, .L3976
	b	.L3980
.L4032:
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	str	w0, [x20, 180]
	b	.L4033
.L4024:
	add	x0, x20, 4096
	add	x0, x0, 2832
	bl	ResetVoQueue
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -2
	ldp	x29, x30, [sp], 96
	ret
.L4031:
	ldr	x3, [x22, 96]
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 72
	ldr	w22, [x20, 3368]
	blr	x3
	ldr	x0, [x20, 3032]
	stp	w21, w19, [x29, 76]
	stp	w21, w19, [x29, 84]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L3969
	sxtb	w2, w22
	strb	w2, [x29, 73]
.L3983:
	ldr	w0, [x20, 276]
	add	x1, x29, 72
	strb	w2, [x29, 75]
	bl	FSP_ConfigInstance
	cbnz	w0, .L4034
	ldr	x1, [x20, 3032]
	add	x3, x29, 68
	ldr	w0, [x20, 276]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	b	.L3971
.L3969:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 73]
	b	.L3983
.L4030:
	ldr	x22, .LC1067
	mov	w3, 0
	ldr	x1, .LC1071
	mov	w0, 0
	add	x2, x22, 144
	bl	dprint_vfmw
	b	.L3973
.L4034:
	ldr	x22, .LC1067
	mov	w0, 1
	ldr	x1, .LC1074
	add	x2, x22, 144
	bl	dprint_vfmw
	b	.L3973
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	3
.LC1067:
	.xword	.LANCHOR5
	.align	3
.LC1068:
	.xword	.LC378
	.align	3
.LC1069:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1071:
	.xword	.LC1070
	.align	3
.LC1073:
	.xword	.LC1072
	.align	3
.LC1074:
	.xword	.LC230
	.align	3
.LC1076:
	.xword	.LC1075
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	mov	w21, 104
	bl	_mcount
	ldr	w2, [x20, 168]
	cmn	w2, #1
	bne	.L4040
	b	.L4039
	.p2align 3
.L4037:
	add	w0, w2, 1
	cmp	w0, w19
	bls	.L4039
.L4040:
	umull	x1, w19, w21
	ldr	x0, [x20, 3024]
	add	w19, w19, 1
	add	x1, x0, x1
	ldr	w0, [x1, 32]
	cmp	w0, 1
	bne	.L4037
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	w2, [x20, 168]
	add	w0, w2, 1
	cmp	w0, w19
	bhi	.L4040
.L4039:
	strb	wzr, [x20, 9]
	mov	w0, 0
	str	wzr, [x20, 148]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	add	x23, x21, 4096
	add	x25, x21, 12288
	bl	_mcount
	add	x19, x25, 2448
	ldr	x1, .LC1078
	mov	w0, 22
	mov	w20, 0
	mov	w26, 20
	mov	w24, 16
	bl	dprint_vfmw
	strb	wzr, [x21, 4]
	mov	w0, -2147483647
	mov	w2, 1
	mov	w1, 2147483647
	strb	w2, [x21, 6]
	strb	w2, [x21, 7]
	stp	w0, w0, [x21, 212]
	stp	w1, w1, [x21, 244]
	stp	w0, w0, [x21, 252]
	strb	wzr, [x21, 12]
	mov	x0, x21
	strb	wzr, [x21, 5]
	strb	wzr, [x21, 13]
	bl	HEVC_ClearAllNal
	add	x0, x23, 2832
	bl	ResetVoQueue
	ldr	x22, .LC1079
	.p2align 2
.L4044:
	strb	wzr, [x19]
	add	x0, x19, 88
	strb	wzr, [x19, 1]
	mov	x2, 632
	strb	wzr, [x19, 2]
	mov	w1, 0
	str	wzr, [x19, 8]
	stp	w26, w24, [x19, 20]
	str	wzr, [x19, 48]
	ldr	x3, [x22, 96]
	blr	x3
	str	w20, [x19, 236]
	add	w20, w20, 1
	str	wzr, [x19, 56]
	str	x19, [x19, 80]
	cmp	w20, 20
	add	x19, x19, 720
	bne	.L4044
	add	x0, x21, 2156
	add	x1, x21, 2236
	.p2align 2
.L4045:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L4045
	ldr	w1, [x21, 168]
	mov	w0, 0
	cbz	w1, .L4049
	.p2align 2
.L4051:
	ldr	x1, [x21, 3016]
	str	xzr, [x1, w0, uxtw 3]
	add	w0, w0, 1
	ldr	w1, [x21, 168]
	cmp	w1, w0
	bhi	.L4051
.L4049:
	ldr	x3, [x22, 96]
	mov	x2, 280
	mov	w1, 0
	add	x0, x25, 1884
	mov	w19, 16
	blr	x3
	str	w19, [x21, 14172]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x25, 2164
	blr	x3
	str	w19, [x21, 14452]
	add	x0, x21, 3816
	add	x1, x21, 3952
	.p2align 2
.L4047:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x1, x0
	bne	.L4047
	add	x2, x21, 3328
	mov	w0, 17
	add	x19, x21, 3328
	stp	w0, wzr, [x2, 40]
	stp	wzr, wzr, [x2, 48]
	str	wzr, [x21, 3384]
	add	x0, x21, 3192
	str	wzr, [x21, 3388]
	.p2align 2
.L4050:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	cmp	x19, x0
	bne	.L4050
	ldr	x3, [x22, 96]
	mov	w20, 2
	mov	x2, 1376
	str	w20, [x21, 176]
	mov	w1, 0
	add	x0, x23, 1456
	str	wzr, [x21, 204]
	str	wzr, [x21, 260]
	str	wzr, [x21, 268]
	str	xzr, [x21, 2976]
	blr	x3
	strb	wzr, [x21, 8]
	mov	w1, 8
	mov	w3, 1
	stp	w1, w1, [x21, 196]
	add	x1, x21, 2048
	strb	w3, [x21, 3]
	str	wzr, [x21, 172]
	mov	w2, 20
	stp	w2, w2, [x21, 180]
	ldr	x4, [x22, 96]
	mov	w0, 6
	mov	w2, 16
	stp	w0, w20, [x1, 196]
	stp	w0, w0, [x1, 188]
	mov	w1, 64
	str	w2, [x21, 348]
	str	w1, [x21, 352]
	mov	w2, 256
	mov	w1, 1025
	str	w20, [x21, 5572]
	str	w3, [x21, 5704]
	mov	x0, x19
	str	w2, [x21, 356]
	mov	x2, 40
	str	w1, [x21, 360]
	mov	w1, 0
	blr	x4
	str	x19, [x21, 2936]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	3
.LC1078:
	.xword	.LC1077
	.align	3
.LC1079:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	ldr	x0, [x19, 4912]
	cbz	x0, .L4058
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x19, 276]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 4912]
	str	wzr, [x0, 48]
	str	xzr, [x19, 4912]
.L4058:
	add	x19, x19, 4096
	mov	w0, 0
	strb	wzr, [x19, 753]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	cbnz	w20, .L4065
	add	x0, x19, 4096
	add	x0, x0, 2832
	bl	ResetVoQueue
	ldr	w0, [x19, 276]
	bl	FSP_EmptyInstance
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4065:
	add	x1, x19, 4096
	ldr	w0, [x19, 276]
	add	x1, x1, 2832
	bl	FSP_ClearNotInVoQueue
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x28, 5588]
	tbnz	w1, #31, .L4095
	ldr	w2, [x28, 164]
	mov	w0, 0
	cmp	w1, w2
	bge	.L4108
	ldr	x3, [x28, 2960]
	mov	w19, 5036
	mov	w0, 12668
	ldr	x22, [x28, 2952]
	ldr	w2, [x28, 5584]
	smaddl	x19, w1, w19, x3
	ldr	w3, [x28, 300]
	ldr	w4, [x28, 292]
	add	x2, x28, x2, lsl 2
	ldr	w21, [x19, 32]
	mov	w7, w3
	ldr	w3, [x28, 288]
	mov	w6, w4
	mov	w4, 24912
	smull	x21, w21, w0
	mov	w0, 1
	stp	w3, w0, [x29, 116]
	add	x0, x22, x21
	ldr	w3, [x28, 296]
	mov	x5, x0
	str	w3, [x29, 112]
	ldr	x3, [x28, 2944]
	ldr	w0, [x0, 48]
	str	w1, [x2, 236]
	stp	w7, w6, [x29, 100]
	umull	x0, w0, w4
	str	x5, [x29, 128]
	add	x1, x3, x0
	ldr	w0, [x19, 32]
	str	w0, [x2, 228]
	ldr	w0, [x5, 48]
	str	w0, [x2, 220]
	ldr	w0, [x28, 172]
	ldr	w2, [x5, 128]
	cmp	w0, wzr
	ldr	w0, [x5, 64]
	cset	w3, eq
	cmp	w2, w7
	cset	w20, ne
	str	w3, [x29, 124]
	cmp	w6, w0
	beq	.L4118
.L4068:
	ldr	w0, [x29, 124]
	ldr	w2, [x1, 4]
	orr	w20, w0, w20
	ldr	w0, [x29, 120]
	orr	w20, w20, w0
	ldr	x0, [x28, 2992]
	ldr	w0, [x0, 4]
	cmp	w2, w0
	beq	.L4119
.L4069:
	ldr	x0, .LC1080
	mov	w25, 24912
	strb	wzr, [x1, 2]
	mov	x23, -24912
	ldr	x3, [x0, 104]
	ldr	w0, [x28, 156]
	ldr	x2, [x28, 2944]
	smaddl	x0, w0, w25, x23
	add	x0, x2, x0
	mov	x2, 24912
	blr	x3
	ldr	w0, [x28, 156]
	ldr	x1, [x28, 2944]
	smaddl	x0, w0, w25, x23
	add	x0, x1, x0
	str	x0, [x28, 2992]
.L4070:
	ldr	x0, [x28, 3000]
	mov	w23, w20
	ldr	x1, [x29, 128]
	ldr	w2, [x0, 56]
	ldr	w1, [x1, 56]
	cmp	w2, w1
	beq	.L4120
.L4094:
	ldr	x2, [x29, 128]
	ldr	w0, [x0, 184]
	ldr	w1, [x2, 184]
	cmp	w1, w0
	mov	x1, x2
	mov	x0, x28
	cset	w2, ne
	str	w2, [x29, 108]
	bl	HEVC_UpdatePicSPS
.L4072:
	ldr	x0, [x28, 3008]
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 28]
	cmp	w1, w0
	beq	.L4121
.L4073:
	ldr	x1, [x29, 128]
	mov	x2, x19
	mov	x0, x28
	bl	HEVC_UpdatePicPPS
.L4074:
	ldr	x0, [x28, 3000]
	ldr	x2, [x28, 3032]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	str	w0, [x2, 940]
	ldr	x23, [x28, 2992]
	add	x23, x23, 12288
	add	x23, x23, 132
	ldr	w13, [x23, 4124]
	cbz	w13, .L4088
	add	w27, w13, 1
	mov	w0, 2
	cmp	w27, 2
	mov	w26, 0
	csel	w27, w27, w0, ls
	str	x23, [x29, 136]
	str	w27, [x28, 2380]
	mov	w23, w27
	mov	w27, w26
	mov	w21, 1
	cmp	w23, w27
	ldr	x20, .LC1082
	bls	.L4088
	.p2align 2
.L4087:
	add	w22, w27, 1
	sxtw	x19, w27
	cmp	w23, w22
	ldr	x26, [x28, 2992]
	bls	.L4085
	add	x26, x26, 12288
	lsl	x25, x19, 5
	add	x26, x26, 132
	add	x25, x25, x19, lsl 3
	mov	w24, w22
	add	x25, x26, x25
	b	.L4084
	.p2align 3
.L4082:
	ldrb	w4, [x28, 2]
	cmp	w4, 1
	beq	.L4083
	strb	w21, [x28, 2]
	ldr	w6, [x3, 12412]
	ldr	w7, [x3, 12416]
	ldr	w4, [x25, 12416]
	ldr	w3, [x25, 12412]
	bl	dprint_vfmw
.L4083:
	cmp	w24, w23
	bcs	.L4085
.L4084:
	sxtw	x0, w24
	ldr	w7, [x25, 12412]
	lsl	x4, x0, 5
	mov	w5, w24
	add	x4, x4, x0, lsl 3
	add	w24, w24, 1
	add	x4, x26, x4
	mov	w2, w27
	mov	x3, x4
	mov	x1, x20
	mov	w0, 32
	ldr	w6, [x4, 12412]
	cmp	w7, w6
	bne	.L4082
	ldr	w4, [x4, 12416]
	ldr	w6, [x25, 12416]
	cmp	w6, w4
	bne	.L4082
	cmp	w24, w23
	bcc	.L4084
	.p2align 2
.L4085:
	ldr	x1, [x29, 136]
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x5, x28, x19, lsl 2
	add	x0, x1, x0
	ldr	w1, [x5, 2388]
	ldr	w3, [x0, 12412]
	cmp	w1, w3
	bne	.L4080
	ldr	w0, [x0, 12416]
	ldr	w1, [x5, 2396]
	cmp	w1, w0
	beq	.L4086
.L4080:
	lsl	x0, x19, 5
	str	w3, [x5, 2388]
	add	x19, x0, x19, lsl 3
	ldr	x0, [x29, 136]
	ldr	x1, .LC1084
	mov	w2, w27
	add	x19, x0, x19
	mov	w0, 32
	ldr	w4, [x19, 12416]
	str	w4, [x5, 2396]
	bl	dprint_vfmw
	str	wzr, [x28, 2384]
.L4086:
	ldr	w23, [x28, 2380]
	mov	w27, w22
	cmp	w23, w27
	bhi	.L4087
.L4088:
	ldr	w0, [x28, 2356]
	cbnz	w0, .L4077
	ldr	x0, [x29, 128]
	ldr	w1, [x29, 116]
	ldr	w0, [x0, 56]
	cmp	w0, w1
	beq	.L4122
.L4089:
	ldp	w3, w1, [x29, 100]
	ldp	w4, w2, [x29, 108]
	mov	x0, x28
	bl	HEVC_GetReRangeFlag
	cbnz	w0, .L4091
	ldr	x0, [x28, 3032]
	ldr	w1, [x0, 928]
	cmp	w1, 1
	beq	.L4091
.L4092:
	str	wzr, [x0, 944]
.L4090:
	mov	x0, x28
	bl	HEVC_AllocFrameStore
	mov	w19, w0
	cbz	w0, .L4077
	ldr	x1, .LC1088
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
.L4108:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L4077:
	mov	x0, x28
	bl	HEVC_InitPicInfo
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L4091:
	mov	w1, 1
	mov	x0, x28
	bl	HEVC_InitDPB
	cmn	w0, #2
	beq	.L4108
	cbnz	w0, .L4093
	ldr	x0, [x28, 3032]
	b	.L4092
.L4095:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
.L4118:
	ldr	w0, [x5, 68]
	ldr	w2, [x29, 112]
	cmp	w0, w2
	cset	w0, ne
	str	w0, [x29, 120]
	b	.L4068
.L4121:
	ldrb	w0, [x19, 1]
	cmp	w0, wzr
	cset	w0, ne
	orr	w23, w23, w0
	cbz	w23, .L4074
	b	.L4073
	.p2align 3
.L4120:
	ldrb	w1, [x22, x21]
	str	wzr, [x29, 108]
	cmp	w1, wzr
	cset	w1, ne
	orr	w1, w20, w1
	cbz	w1, .L4072
	b	.L4094
	.p2align 3
.L4119:
	ldrb	w0, [x1, 2]
	ldr	w2, [x29, 124]
	cmp	w0, wzr
	cset	w0, ne
	orr	w0, w2, w0
	cbz	w0, .L4070
	b	.L4069
	.p2align 3
.L4122:
	ldp	w1, w0, [x29, 120]
	orr	w0, w0, w1
	ldr	w1, [x29, 108]
	orr	w0, w0, w1
	cbnz	w0, .L4089
	ldr	x0, [x28, 3032]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	bne	.L4090
	b	.L4089
.L4093:
	ldr	x1, .LC1086
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x28
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L4108
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	3
.LC1080:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1082:
	.xword	.LC1081
	.align	3
.LC1084:
	.xword	.LC1083
	.align	3
.LC1086:
	.xword	.LC1085
	.align	3
.LC1088:
	.xword	.LC1087
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 4096
	bl	_mcount
	ldr	x20, [x19, 4912]
	mov	x2, 632
	ldr	w3, [x19, 4888]
	add	x1, x21, 824
	add	x0, x20, 88
	str	w3, [x20, 16]
	bl	memcpy
	mov	x0, x19
	mov	x1, x20
	bl	HEVC_GetImagePara
	ldrb	w0, [x21, 752]
	cbnz	w0, .L4131
.L4124:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_OutputFrame
	mov	w1, 0
	cbnz	w0, .L4132
.L4125:
	mov	w0, w1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4131:
	ldr	w0, [x19, 276]
	mov	w2, 1
	ldr	w1, [x20, 28]
	bl	FSP_SetRef
	b	.L4124
	.p2align 3
.L4132:
	ldr	x2, .LC1089
	mov	w0, 0
	ldr	x1, .LC1091
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w1, -1
	b	.L4125
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	3
.LC1089:
	.xword	.LANCHOR5
	.align	3
.LC1091:
	.xword	.LC1090
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	mov	w20, w0
	cbnz	w0, .L4136
	ldr	x0, [x19, 4912]
	mov	w2, 2
	mov	w1, 1
	str	w2, [x0, 52]
	str	w1, [x19, 12792]
	ldr	w0, [x19, 4856]
	ldr	w2, [x19, 4860]
	add	x0, x19, x0, lsl 2
	str	w2, [x0, 212]
	ldr	x0, [x19, 4912]
	strb	w1, [x0, 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4136:
	ldr	x2, .LC1092
	mov	w0, 1
	ldr	x1, .LC1094
	add	x2, x2, 192
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	3
.LC1092:
	.xword	.LANCHOR5
	.align	3
.LC1094:
	.xword	.LC1093
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L4145
	cmn	w0, #3
	bne	.L4146
.L4141:
	mov	w0, 0
.L4140:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4145:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_OutputFrame
	cbz	w0, .L4141
	ldr	x2, .LC1095
	mov	w0, 0
	ldr	x1, .LC1096
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L4140
	.p2align 3
.L4146:
	ldr	x1, .LC1098
	mov	w3, w0
	mov	w2, 11772
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 236]
	mov	x0, x19
	bl	HEVC_DECRecycleImage
	mov	w0, -1
	b	.L4140
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	3
.LC1095:
	.xword	.LANCHOR5
	.align	3
.LC1096:
	.xword	.LC1090
	.align	3
.LC1098:
	.xword	.LC1097
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 4096
	bl	_mcount
	ldr	x19, [x20, 4912]
	mov	w4, 2
	mov	w3, 1
	add	x1, x21, 824
	mov	x2, 632
	add	x0, x19, 88
	str	w4, [x19, 48]
	strb	wzr, [x19, 1]
	strb	w3, [x19, 2]
	ldr	w3, [x20, 4864]
	str	w3, [x19, 12]
	ldr	w3, [x20, 4888]
	str	w3, [x19, 16]
	bl	memcpy
	str	wzr, [x19, 56]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_OutputFrmToVO
	str	wzr, [x19, 48]
	ldr	x3, .LC1099
	mov	w20, w0
	mov	x2, 704
	mov	w1, 0
	add	x0, x21, 752
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	3
.LC1099:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_DirectOutput
	ldr	w2, [x19, 184]
	ldr	w1, [x19, 4884]
	cmp	w1, w2
	beq	.L4149
	add	x1, x19, x1, uxtw 2
	str	wzr, [x1, 2156]
	str	w2, [x19, 4884]
.L4149:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w5, [x20, 3372]
	ldr	w27, [x20, 4856]
	cbz	w5, .L4151
	sub	w3, w5, #1
	uxtw	x4, w27
	add	x3, x3, 461
	add	x4, x4, 52
	add	x0, x20, 3680
	mov	w22, 0
	add	x3, x20, x3, lsl 3
	lsl	x4, x4, 2
	b	.L4153
	.p2align 3
.L4152:
	cmp	x0, x3
	beq	.L4178
.L4153:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cbnz	w2, .L4152
	ldr	w2, [x1, 32]
	cmp	w27, w2
	bne	.L4152
	add	x2, x20, x4
	ldr	w6, [x1, 8]
	ldr	w1, [x2, 4]
	cmp	w6, w1
	csinc	w22, w22, w22, le
	cmp	x0, x3
	bne	.L4153
	.p2align 2
.L4178:
	ldr	w0, [x20, 2364]
	cmp	w0, 1
	beq	.L4165
.L4154:
	ldr	w0, [x20, 5576]
	ldr	x1, [x20, 3000]
	add	x0, x1, x0, lsl 2
	ldr	w25, [x0, 360]
.L4156:
	cbz	w5, .L4166
	uxtw	x24, w27
	ldr	x21, .LC1100
	add	x28, x24, 52
	ldr	x23, .LC1102
	mov	w19, 0
	add	x21, x21, 240
	lsl	x28, x28, 2
	str	wzr, [x29, 108]
	.p2align 2
.L4164:
	add	x26, x20, x19, uxtw 3
	ldr	x0, [x26, 3680]
	ldrb	w1, [x0, 2]
	cbnz	w1, .L4158
	ldr	w2, [x0, 32]
	cmp	w27, w2
	beq	.L4179
.L4158:
	add	x2, x20, x28
	ldr	w3, [x2, 4]
.L4160:
	cbnz	w3, .L4162
	ldr	w4, [x0, 8]
	tbz	w4, #31, .L4162
	cbz	w1, .L4180
.L4163:
	mov	x2, x21
	mov	x1, x23
	mov	w0, 31
	bl	dprint_vfmw
	ldr	w5, [x20, 3372]
.L4162:
	add	w19, w19, 1
	cmp	w5, w19
	bhi	.L4164
.L4177:
	ldr	w0, [x29, 108]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4179:
	add	x7, x20, x24, lsl 2
	ldr	w2, [x0, 8]
	ldr	w3, [x7, 212]
	cmp	w2, w3
	ble	.L4160
	ldr	w8, [x20, 5576]
	add	x4, x20, 4096
	add	x4, x4, 1456
	cmp	w8, 7
	ccmp	w25, w22, 2, ls
	bcs	.L4160
	ldr	w4, [x4, 12]
	cmp	w2, w4
	blt	.L4161
	add	x2, x20, x24
	ldrb	w2, [x2, 4]
	cbz	w2, .L4160
.L4161:
	mov	w1, 1
	strb	w1, [x0, 2]
	mov	x0, x20
	str	x7, [x29, 96]
	ldr	x1, [x26, 3680]
	sub	w22, w22, #1
	bl	HEVC_OutputFrmToVO
	str	w0, [x29, 108]
	ldr	x0, [x26, 3680]
	ldr	x7, [x29, 96]
	ldr	w0, [x0, 8]
	str	w0, [x7, 212]
	ldr	w5, [x20, 3372]
	b	.L4162
	.p2align 3
.L4180:
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x20, 276]
	bl	FSP_SetDisplay
	ldr	x0, [x26, 3680]
	ldr	w4, [x0, 8]
	add	x0, x20, x28
	ldr	w3, [x0, 4]
	b	.L4163
.L4151:
	ldr	w0, [x20, 2364]
	mov	w22, 0
	cmp	w0, 1
	bne	.L4154
	.p2align 2
.L4165:
	ldr	x2, [x20, 3000]
	mov	w25, 0
	add	x0, x2, 360
	add	x2, x2, 392
	.p2align 2
.L4155:
	ldr	w1, [x0], 4
	cmp	w25, w1
	csel	w25, w25, w1, cs
	cmp	x2, x0
	bne	.L4155
	b	.L4156
.L4166:
	str	wzr, [x29, 108]
	b	.L4177
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	3
.LC1100:
	.xword	.LANCHOR5
	.align	3
.LC1102:
	.xword	.LC1101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, x21, uxtw 3
	bl	_mcount
	mov	w2, 1
	mov	x0, x19
	ldr	x1, [x20, 3680]
	strb	w2, [x1, 2]
	ldr	x1, [x20, 3680]
	bl	HEVC_OutputFrmToVO
	mov	w22, w0
	ldr	x0, [x20, 3680]
	ldr	w1, [x0, 32]
	ldr	w2, [x0, 8]
	add	x1, x19, x1, lsl 2
	str	w2, [x1, 212]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L4182
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L4182:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x29, 44
	mov	x0, x19
	bl	HEVC_GetUnRefPicWithMinPoc
	cbnz	w0, .L4188
	ldr	w1, [x29, 44]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	mov	w1, 0
	cbnz	w0, .L4189
.L4185:
	ldr	x19, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4188:
	ldr	x2, .LC1104
	mov	w0, 1
	ldr	x1, .LC1106
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w1, -1
	b	.L4185
	.p2align 3
.L4189:
	ldr	x2, .LC1104
	mov	w0, 1
	ldr	x1, .LC1108
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w1, -1
	b	.L4185
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	3
.LC1104:
	.xword	.LANCHOR5
	.align	3
.LC1106:
	.xword	.LC1105
	.align	3
.LC1108:
	.xword	.LC1107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L4199
	ldr	w0, [x19, 3372]
	mov	w20, 0
	mov	w22, 1
	cbnz	w0, .L4202
	b	.L4198
	.p2align 3
.L4206:
	strb	w22, [x1, 2]
	ldr	x1, [x21, 3680]
	bl	HEVC_OutputFrmToVO
	cmn	w0, #1
	mov	w21, w0
	beq	.L4205
.L4195:
	ldr	w0, [x19, 3372]
	cmp	w0, w20
	bls	.L4198
.L4202:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 276]
	mov	w2, 0
	add	w20, w20, 1
	ldr	x1, [x21, 3680]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x21, 3680]
	mov	x0, x19
	ldrb	w2, [x1, 2]
	cbz	w2, .L4206
	ldr	w1, [x1, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L4195
	ldr	x1, [x21, 3680]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 3372]
	cmp	w0, w20
	bhi	.L4202
.L4198:
	mov	w1, -2147483647
	mov	x0, x19
	stp	w1, w1, [x19, 212]
	mov	w21, 0
	bl	HEVC_InitDecBuffers
.L4191:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4205:
	ldr	x2, .LC1109
	mov	w0, 0
	ldr	x1, .LC1111
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L4199:
	mov	w21, -1
	b	.L4191
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	3
.LC1109:
	.xword	.LANCHOR5
	.align	3
.LC1111:
	.xword	.LC1110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 2976]
	str	wzr, [x19, 344]
	cbz	x0, .L4237
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 3032]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L4238
.L4214:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L4215
	ldr	x1, [x19, 2976]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bls	.L4216
	ldr	w2, [x1, 36]
	cmp	w2, 1
	beq	.L4215
.L4216:
	ldr	w2, [x20, 24]
	cmp	w2, wzr
	ble	.L4217
	ldr	x2, [x20, 8]
	cbz	x2, .L4217
	ldr	w3, [x20, 16]
	cbnz	w3, .L4239
.L4217:
	mov	w0, 1
	str	w0, [x1, 36]
	ldr	w0, [x19, 276]
	ldr	w1, [x20, 28]
	bl	SM_ReleaseStreamSeg
.L4213:
	ldr	x0, [x19, 2976]
	ldr	w0, [x0, 36]
	cmp	w0, wzr
	csetm	w0, eq
.L4211:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4239:
	uxtw	x0, w0
	add	x0, x1, x0, lsl 5
	str	x2, [x0, 40]
	ldr	x1, [x19, 2976]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 48]
	ldr	x1, [x19, 2976]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 52]
	ldr	x1, [x19, 2976]
	ldr	w2, [x20, 28]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 68]
	ldr	x1, [x19, 2976]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 60]
	ldr	x1, [x19, 2976]
	ldr	w0, [x1, 8]
	add	w0, w0, 1
	str	w0, [x1, 8]
	ldr	x0, [x19, 3032]
	ldrb	w0, [x0, 952]
	cmp	w0, 1
	beq	.L4218
	ldr	w0, [x19, 4900]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4904]
	add	w1, w0, w1
	str	w1, [x19, 4900]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4904]
.L4218:
	mov	x0, x19
	bl	HEVC_CombinePacket
	mov	w0, 1
	str	w0, [x19, 344]
	b	.L4213
	.p2align 3
.L4238:
	ldr	w0, [x0, 928]
	cbnz	w0, .L4213
	b	.L4214
	.p2align 3
.L4237:
	ldr	w0, [x20, 24]
	cmp	w0, wzr
	ble	.L4209
	ldr	x0, [x20, 8]
	cbz	x0, .L4209
	ldr	w0, [x20, 16]
	cbz	w0, .L4209
	mov	x0, x19
	bl	HEVC_FindNaluArraySlot
	cmn	w0, #1
	mov	w21, w0
	beq	.L4240
	ldr	x0, [x19, 3024]
	mov	w2, 104
	mov	w1, 1
	smaddl	x0, w21, w2, x0
	str	x0, [x19, 2976]
	ldr	x2, [x20, 8]
	str	x2, [x0, 40]
	ldr	x0, [x19, 2976]
	ldr	w2, [x20, 24]
	str	w2, [x0, 48]
	ldr	x0, [x19, 2976]
	ldr	w2, [x20, 28]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2976]
	ldr	w2, [x20, 16]
	str	w2, [x0, 52]
	ldr	x0, [x19, 2976]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2976]
	str	w1, [x0, 8]
	ldr	x0, [x19, 2976]
	strb	wzr, [x0]
	ldr	x0, [x19, 2976]
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 3032]
	ldrb	w0, [x0, 952]
	cmp	w0, 1
	beq	.L4212
	ldr	w0, [x19, 4900]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4904]
	add	w1, w0, w1
	str	w1, [x19, 4900]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4904]
.L4212:
	ldr	w0, [x20, 20]
	str	w0, [x19, 2352]
	b	.L4213
	.p2align 3
.L4215:
	ldr	x1, .LC1117
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4211
	.p2align 3
.L4209:
	ldr	x1, .LC1115
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4211
.L4240:
	ldr	x1, .LC1113
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, w21
	b	.L4211
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	3
.LC1113:
	.xword	.LC1112
	.align	3
.LC1115:
	.xword	.LC1114
	.align	3
.LC1117:
	.xword	.LC1116
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w2, [x19, 3372]
	cbnz	w2, .L4253
	b	.L4243
	.p2align 3
.L4244:
	cmp	w2, w20
	bls	.L4243
.L4253:
	add	x0, x19, x20, uxtw 3
	add	w20, w20, 1
	ldr	x0, [x0, 3680]
	ldrb	w1, [x0, 1]
	cbz	w1, .L4244
	strb	wzr, [x0, 1]
	mov	w2, 0
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_SetRef
	ldr	w2, [x19, 3372]
	cmp	w2, w20
	bhi	.L4253
	.p2align 2
.L4243:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbz	w0, .L4247
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L4243
	b	.L4247
	.p2align 3
.L4249:
	bl	HEVC_GetMinPOC
	ldr	w1, [x29, 40]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L4248
.L4247:
	ldr	w3, [x19, 3372]
	add	x2, x29, 40
	add	x1, x29, 44
	mov	x0, x19
	cbnz	w3, .L4249
	mov	w0, 0
.L4248:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_FlushDPB
	cbz	w0, .L4259
	ldr	x2, .LC1118
	mov	w3, w0
	ldr	x1, .LC1120
	mov	w0, 0
	add	x2, x2, 328
	bl	dprint_vfmw
.L4259:
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	3
.LC1118:
	.xword	.LANCHOR5
	.align	3
.LC1120:
	.xword	.LC1119
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC1121
	ldr	x22, .LC1123
	add	x21, x20, 344
	b	.L4264
	.p2align 3
.L4266:
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L4274
.L4264:
	ldr	w5, [x19, 3368]
	mov	x2, x21
	ldr	w6, [x19, 3372]
	mov	x1, x22
	mov	w0, 13
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcs	.L4266
.L4263:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4274:
	ldr	x1, .LC1125
	mov	x2, x21
	mov	w0, 1
	add	x20, x20, 344
	bl	dprint_vfmw
	ldr	x21, .LC1127
	.p2align 2
.L4265:
	ldr	w5, [x19, 3368]
	mov	x2, x20
	ldr	w6, [x19, 3372]
	mov	x1, x21
	mov	w0, 1
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcc	.L4263
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_OutputUnRefPicWithMinPoc
	cbz	w0, .L4265
	ldr	x1, .LC1128
	mov	x2, x20
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	mov	x0, x19
	bl	HEVC_ClearDPB
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	3
.LC1121:
	.xword	.LANCHOR5
	.align	3
.LC1123:
	.xword	.LC1122
	.align	3
.LC1125:
	.xword	.LC1124
	.align	3
.LC1127:
	.xword	.LC1126
	.align	3
.LC1128:
	.xword	.LC1107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	mov	x19, x2
	bl	_mcount
	cmp	w22, 16
	bhi	.L4279
	add	x20, x21, x22, uxtw 3
	ldr	x0, [x19, 64]
	mov	w1, 1
	mov	w2, w1
	str	x0, [x20, 3680]
	str	w1, [x0, 48]
	ldr	x1, [x20, 3680]
	ldr	w0, [x21, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldrb	w1, [x19]
	mov	x2, 632
	ldr	x0, [x20, 3680]
	cmp	w1, wzr
	add	x1, x19, 72
	cset	w3, ne
	strb	w3, [x0, 1]
	ldr	x0, [x20, 3680]
	ldr	w3, [x19, 36]
	str	w3, [x0, 20]
	ldr	x0, [x20, 3680]
	add	x0, x0, 88
	bl	memcpy
	ldr	x0, [x20, 3680]
	add	w1, w22, 1
	ldr	w4, [x19, 40]
	mov	w2, 8
	ldr	x3, .LC1133
	str	w4, [x0, 16]
	add	x0, x21, 3680
	ldr	x4, [x20, 3680]
	ldr	x5, [x19, 64]
	str	x5, [x4, 80]
	ldr	x4, [x20, 3680]
	ldr	w5, [x19, 16]
	str	w5, [x4, 12]
	ldr	x4, [x20, 3680]
	ldr	w5, [x19, 12]
	str	w5, [x4, 8]
	ldr	x4, [x20, 3680]
	ldr	w5, [x19, 8]
	str	w5, [x4, 32]
	ldr	x4, [x20, 3680]
	str	wzr, [x4, 72]
	bl	qsort
	ldr	w1, [x21, 3372]
	mov	x0, x21
	add	w1, w1, 1
	str	w1, [x21, 3372]
	ldr	x1, [x19, 64]
	bl	HEVC_GetAPC
	cbnz	w0, .L4280
	strb	wzr, [x19, 1]
	mov	w0, 0
.L4277:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4279:
	ldr	x2, .LC1130
	mov	w3, w22
	ldr	x1, .LC1132
	mov	w0, 0
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4277
	.p2align 3
.L4280:
	ldr	x2, .LC1130
	mov	w3, w0
	ldr	x1, .LC1135
	mov	w0, 0
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_PrintDPBState
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4277
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	3
.LC1130:
	.xword	.LANCHOR5
	.align	3
.LC1132:
	.xword	.LC1131
	.align	3
.LC1133:
	.xword	HEVC_ComparePicByPocAsc
	.align	3
.LC1135:
	.xword	.LC1134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 4096
	bl	_mcount
	ldrb	w0, [x20, 752]
	cbnz	w0, .L4294
	ldr	x0, [x19, 4912]
	mov	w1, 2
	str	w1, [x0, 48]
.L4283:
	ldr	x1, [x19, 4912]
	mov	w2, 1
	mov	x0, x19
	strb	w2, [x1, 2]
	ldr	x1, [x19, 4912]
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L4295
	cmn	w0, #3
	beq	.L4287
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L4296
.L4287:
	mov	w0, 0
.L4284:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4294:
	mov	x0, x19
	bl	HEVC_SimpleSlideDPB
	ldr	w1, [x19, 3372]
	add	x2, x20, 752
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbz	w0, .L4283
	ldr	x2, .LC1136
	mov	w4, w0
	ldr	x1, .LC1138
	mov	w3, 10933
	add	x2, x2, 392
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4284
	.p2align 3
.L4296:
	ldr	x2, .LC1136
	mov	w0, 0
	ldr	x1, .LC1141
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4284
.L4295:
	ldr	x2, .LC1136
	mov	w0, 0
	ldr	x1, .LC1140
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, w20
	b	.L4284
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	3
.LC1136:
	.xword	.LANCHOR5
	.align	3
.LC1138:
	.xword	.LC1137
	.align	3
.LC1140:
	.xword	.LC1139
	.align	3
.LC1141:
	.xword	.LC1093
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3368]
	ldr	w1, [x19, 3372]
	cmp	w1, w0
	bcs	.L4309
.L4298:
	add	x2, x19, 4096
	mov	x0, x19
	add	x2, x2, 752
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4310
	ldr	x1, [x19, 4912]
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L4311
	cmn	w0, #3
	beq	.L4304
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L4312
.L4304:
	mov	w0, 0
.L4301:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4309:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L4308
	ldr	x2, .LC1142
	mov	w0, 0
	ldr	x1, .LC1144
	add	x2, x2, 416
	bl	dprint_vfmw
.L4308:
	ldr	w1, [x19, 3372]
	b	.L4298
.L4312:
	ldr	x2, .LC1142
	mov	w0, 0
	ldr	x1, .LC1148
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4301
	.p2align 3
.L4310:
	ldr	x2, .LC1142
	mov	w0, 0
	ldr	x1, .LC1146
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4301
.L4311:
	ldr	x2, .LC1142
	mov	w0, 0
	ldr	x1, .LC1147
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, w20
	b	.L4301
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	3
.LC1142:
	.xword	.LANCHOR5
	.align	3
.LC1144:
	.xword	.LC1143
	.align	3
.LC1146:
	.xword	.LC1145
	.align	3
.LC1147:
	.xword	.LC1139
	.align	3
.LC1148:
	.xword	.LC1093
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12792]
	cmp	w0, 1
	beq	.L4314
	mov	x0, x19
	bl	HEVC_FirstFrameFastOut
	cbnz	w0, .L4331
.L4314:
	ldr	w0, [x19, 3368]
	ldr	w1, [x19, 3372]
	cmp	w1, w0
	bcs	.L4332
.L4316:
	add	x2, x19, 4096
	mov	x0, x19
	add	x2, x2, 752
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4333
	ldr	w0, [x19, 3372]
	cbnz	w0, .L4319
.L4320:
	mov	w0, 0
.L4315:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4319:
	mov	x0, x19
	bl	HEVC_OutputFrmFromDPB
	cbz	w0, .L4320
	ldr	x2, .LC1149
	mov	w0, 1
	ldr	x1, .LC1157
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4315
	.p2align 3
.L4332:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L4330
	ldr	x1, .LC1153
	mov	w0, 0
	bl	dprint_vfmw
.L4330:
	ldr	w1, [x19, 3372]
	b	.L4316
	.p2align 3
.L4333:
	ldr	x1, .LC1155
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4315
.L4331:
	ldr	x2, .LC1149
	mov	w0, 0
	ldr	x1, .LC1151
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4315
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	3
.LC1149:
	.xword	.LANCHOR5
	.align	3
.LC1151:
	.xword	.LC1150
	.align	3
.LC1153:
	.xword	.LC1152
	.align	3
.LC1155:
	.xword	.LC1154
	.align	3
.LC1157:
	.xword	.LC1156
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrsw	x1, [x19, 276]
	ldr	x0, .LC1158
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L4389
.L4335:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4390
.L4338:
	add	x21, x19, 4096
	ldrb	w0, [x21, 753]
	cbz	w0, .L4391
	ldr	w0, [x19, 4888]
	cbz	w0, .L4343
	ldr	w1, [x19, 4864]
	cbz	w1, .L4392
.L4344:
	ldr	x1, [x19, 3032]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bcc	.L4393
.L4343:
	ldr	x1, [x19, 3048]
	ldr	x0, [x19, 4912]
	ldr	w1, [x1, 5192]
	str	w1, [x0, 40]
	ldr	x1, [x19, 3048]
	ldr	x0, [x19, 4912]
	ldr	w1, [x1, 5196]
	str	w1, [x0, 44]
	ldr	w0, [x19, 280]
	cmp	w0, 2
	beq	.L4394
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	beq	.L4395
	cmp	w0, 1
	beq	.L4396
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4356
.L4354:
	mov	x0, x19
	bl	HEVC_DispOrderProcess
	mov	w20, w0
	cbnz	w0, .L4397
.L4355:
	strb	wzr, [x21, 753]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4390:
	ldr	w5, [x19, 4856]
	cbz	w5, .L4338
	uxtw	x6, w5
	lsl	x0, x6, 5
	add	x0, x0, x6, lsl 3
	add	x1, x19, x0, lsl 3
	sub	x0, x1, x0
	ldr	w4, [x0, 14172]
	cbz	w4, .L4338
	mov	w2, 280
	mov	x1, 0
	umull	x2, w5, w2
	add	x2, x2, 12288
	add	x0, x2, 1892
	add	x2, x2, 2148
	add	x0, x19, x0
	add	x2, x19, x2
	b	.L4340
	.p2align 3
.L4339:
	add	w1, w1, 1
	add	x2, x2, 1
	cmp	w1, w4
	beq	.L4338
.L4340:
	ldr	w3, [x0]
	add	x0, x0, 4
	cbz	w3, .L4339
	ldrsb	w3, [x2]
	cbz	w3, .L4339
	mov	w2, 70
	lsl	x0, x6, 5
	add	x6, x0, x6, lsl 3
	umaddl	x2, w5, w2, x1
	add	x0, x19, x6, lsl 3
	sub	x6, x0, x6
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1
	add	x0, x1, 12288
	str	wzr, [x2, 14180]
	str	wzr, [x2, 14244]
	str	wzr, [x2, 14308]
	ldr	w1, [x6, 14176]
	sub	w1, w1, #1
	str	w1, [x6, 14176]
	strb	wzr, [x0, 2148]
	str	wzr, [x2, 14372]
	b	.L4338
	.p2align 3
.L4389:
	ldr	w1, [x0, 156]
	cbnz	w1, .L4335
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L4335
	add	x0, x19, 12288
	ldrb	w0, [x0, 448]
	cmp	w0, 1
	bne	.L4335
	ldr	w4, [x19, 12748]
	ldr	w5, [x19, 12752]
	ldr	x6, [x19, 12760]
	ldr	x3, [x19, 12768]
	ldr	x7, [x19, 12776]
	cbz	w4, .L4357
	mov	w1, w4
	mov	w2, w5
	b	.L4337
	.p2align 3
.L4358:
	mov	w1, w0
.L4337:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L4358
.L4336:
	udiv	w0, w4, w1
	sub	x3, x3, x7
	lsl	w2, w3, 6
	sub	w2, w2, w3
	lsl	w2, w2, 1
	sub	w2, w2, w3
	lsl	w2, w2, 3
	udiv	w1, w5, w1
	mul	w0, w2, w0
	udiv	w0, w0, w1
	add	x0, x0, x6
	str	x0, [x19, 5504]
	b	.L4335
	.p2align 3
.L4391:
	ldr	x2, .LC1159
	mov	w0, 1
	ldr	x1, .LC1161
	add	x2, x2, 464
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4393:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x3, [x19, 3032]
	mov	w0, 1
	ldr	w2, [x19, 4888]
	ldr	x1, .LC1166
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4395:
	mov	x0, x19
	bl	HEVC_SimpleDPBProcess
	mov	w20, w0
	cbnz	w0, .L4398
.L4351:
	ldr	x1, .LC1170
	mov	w3, 11210
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L4349:
	cmn	w20, #1
	bne	.L4355
	.p2align 2
.L4356:
	mov	x0, x19
	mov	w20, -1
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1159
	mov	w0, 1
	ldr	x1, .LC1178
	add	x2, x2, 464
	bl	dprint_vfmw
	b	.L4355
	.p2align 3
.L4392:
	ldr	x2, .LC1159
	mov	w0, 1
	ldr	x1, .LC1163
	add	x2, x2, 464
	bl	dprint_vfmw
	ldr	x0, .LC1164
	ldr	x4, [x0]
	cbz	x4, .L4388
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L4388:
	ldr	w0, [x19, 4888]
	b	.L4344
	.p2align 3
.L4394:
	mov	x0, x19
	bl	HEVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 184]
	ldr	w0, [x19, 4884]
	cmp	w0, w1
	beq	.L4347
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 2156]
	str	w1, [x19, 4884]
.L4347:
	cbnz	w20, .L4399
.L4348:
	ldr	x1, .LC1170
	mov	w3, 11195
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L4349
	.p2align 3
.L4396:
	mov	x0, x19
	bl	HEVC_DecOrderProcess
	mov	w20, w0
	cbnz	w0, .L4353
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4355
	b	.L4354
	.p2align 3
.L4397:
	ldr	x2, .LC1159
	mov	w0, 0
	ldr	x1, .LC1176
	add	x2, x2, 464
	bl	dprint_vfmw
	b	.L4349
.L4353:
	ldr	x2, .LC1159
	mov	w0, 0
	ldr	x1, .LC1174
	add	x2, x2, 464
	bl	dprint_vfmw
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4349
	b	.L4354
	.p2align 3
.L4399:
	ldr	x2, .LC1159
	mov	w0, 0
	ldr	x1, .LC1168
	add	x2, x2, 464
	bl	dprint_vfmw
	b	.L4348
	.p2align 3
.L4398:
	ldr	x2, .LC1159
	mov	w0, 0
	ldr	x1, .LC1172
	add	x2, x2, 464
	bl	dprint_vfmw
	b	.L4351
.L4357:
	mov	w1, w5
	b	.L4336
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	3
.LC1158:
	.xword	s_pstVfmwChan
	.align	3
.LC1159:
	.xword	.LANCHOR5
	.align	3
.LC1161:
	.xword	.LC1160
	.align	3
.LC1163:
	.xword	.LC1162
	.align	3
.LC1164:
	.xword	g_event_report
	.align	3
.LC1166:
	.xword	.LC1165
	.align	3
.LC1168:
	.xword	.LC1167
	.align	3
.LC1170:
	.xword	.LC1169
	.align	3
.LC1172:
	.xword	.LC1171
	.align	3
.LC1174:
	.xword	.LC1173
	.align	3
.LC1176:
	.xword	.LC1175
	.align	3
.LC1178:
	.xword	.LC1177
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	sub	sp, sp, #704
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	add	x19, x20, 12288
	bl	_mcount
	mov	w21, 0
	ldr	x3, .LC1179
	mov	x2, 704
	mov	w1, 0
	add	x0, x29, 80
	add	x19, x19, 2448
	ldr	x3, [x3, 96]
	blr	x3
	.p2align 2
.L4406:
	ldr	w0, [x19, 48]
	cbnz	w0, .L4401
	cbz	x19, .L4402
	ldr	w2, [x20, 3372]
	cbz	w2, .L4402
	ldr	x0, [x20, 3680]
	cmp	x19, x0
	beq	.L4401
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L4404
	.p2align 3
.L4405:
	ldr	x1, [x0, 3680]
	cmp	x19, x1
	beq	.L4401
.L4404:
	cmp	x2, x0
	add	x0, x0, 8
	bne	.L4405
.L4402:
	sxtw	x23, w21
	mov	w3, 101
	lsl	x1, x23, 2
	mov	x2, 632
	sub	x23, x1, x23
	add	x0, x29, 152
	lsl	x1, x23, 4
	mov	w24, 1
	sub	x23, x1, x23
	strb	w24, [x29, 81]
	strb	w24, [x29, 80]
	add	x23, x20, x23, lsl 4
	str	w22, [x29, 92]
	add	x25, x23, 12288
	str	w3, [x29, 120]
	add	x1, x25, 2536
	bl	memcpy
	strb	w24, [x25, 2450]
	str	wzr, [x23, 14788]
	cmp	w21, 19
	strb	w24, [x25, 2448]
	str	x19, [x29, 144]
	str	wzr, [x29, 304]
	bgt	.L4407
	ldr	w5, [x20, 3372]
	cbz	w5, .L4409
	mov	w6, 0
	mov	w3, 2147483647
	mov	w1, 0
	.p2align 2
.L4412:
	add	x0, x20, x1, sxtw 3
	add	w1, w1, 1
	ldr	x4, [x0, 3680]
	ldr	w0, [x4, 8]
	sub	w0, w0, w22
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w3
	bge	.L4411
	ldrb	w0, [x4, 1]
	cmp	w0, wzr
	csel	w3, w3, w2, eq
	csinc	w6, w6, wzr, eq
.L4411:
	cmp	w1, w5
	bne	.L4412
	cbz	w6, .L4409
	mov	w1, 0
	b	.L4413
	.p2align 3
.L4414:
	cmp	w5, w1
	beq	.L4415
.L4413:
	sxtw	x19, w1
	add	w1, w1, 1
	add	x19, x19, 458
	add	x19, x20, x19, lsl 3
	ldr	x2, [x19, 16]
	ldr	w0, [x2, 8]
	sub	w0, w0, w22
	sxtw	x0, w0
	eor	x4, x0, x0, asr 63
	sub	x4, x4, x0, asr 63
	cmp	w3, w4
	bne	.L4414
	ldrb	w0, [x2, 1]
	cbz	w0, .L4414
	ldp	w1, w23, [x2, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x21, x0
	ldr	x2, [x19, 16]
	mov	w3, w22
	ldr	x1, .LC1187
	mov	w0, 1
	ldr	w2, [x2, 8]
	bl	dprint_vfmw
	cbz	x21, .L4415
	ldr	x0, [x21, 32]
	cbz	x0, .L4448
	ldr	w0, [x20, 276]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	mov	w19, w0
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x1, x0
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L4418
	ldr	x3, [x29, 144]
	add	x2, x29, 80
	mov	x0, x20
	str	w19, [x3, 28]
	ldr	x3, [x21, 32]
	str	x3, [x1, 32]
	ldr	x3, [x21, 40]
	str	x3, [x1, 40]
	ldrsb	w3, [x21, 4]
	ldr	w1, [x20, 3372]
	str	w23, [x29, 88]
	str	w3, [x29, 116]
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4449
	ldr	w0, [x20, 276]
	mov	w2, 0
	mov	w1, w19
	bl	FSP_SetDisplay
	ldr	w1, [x20, 5584]
	mov	w2, 2147483647
	mov	w0, 0
	add	x20, x20, x1, lsl 2
	ldr	w1, [x20, 244]
	cmp	w1, w2
	bne	.L4434
	str	w22, [x20, 244]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L4401:
	add	w21, w21, 1
	add	x19, x19, 720
	cmp	w21, 20
	bne	.L4406
.L4407:
	ldr	x1, .LC1181
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L4434:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L4415:
	ldr	x1, .LC1183
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	mov	w0, -1
	add	sp, sp, 704
	ret
.L4418:
	ldr	x2, [x29, 144]
	mov	w0, 0
	ldr	x1, .LC1191
	strb	wzr, [x2]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4434
.L4449:
	ldr	x0, [x29, 144]
	mov	w2, 1
	mov	w1, w19
	strb	wzr, [x0]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1193
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4434
.L4409:
	ldr	x1, .LC1185
	mov	w0, 0
	strb	wzr, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4434
.L4448:
	ldr	x1, .LC1189
	bl	dprint_vfmw
	mov	x0, x20
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4434
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	3
.LC1179:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1181:
	.xword	.LC1180
	.align	3
.LC1183:
	.xword	.LC1182
	.align	3
.LC1185:
	.xword	.LC1184
	.align	3
.LC1187:
	.xword	.LC1186
	.align	3
.LC1189:
	.xword	.LC1188
	.align	3
.LC1191:
	.xword	.LC1190
	.align	3
.LC1193:
	.xword	.LC1192
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w3, [x19, 1]
	cmp	w3, 1
	beq	.L4451
.L4455:
	mov	x0, x19
	bl	HEVC_ApplyReferencePictureSet
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	ldr	x20, .LC1195
	b	.L4452
	.p2align 3
.L4461:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.15
	cbnz	w0, .L4465
	ldr	w2, [x29, 44]
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 3032]
	mov	x0, x19
	ldr	w1, [x1, 4]
	cbz	w1, .L4459
	ldr	w1, [x29, 44]
	bl	HEVC_CreateLostPicture
	cbnz	w0, .L4473
.L4452:
	ldr	w2, [x19, 5580]
	add	x1, x29, 44
	mov	x0, x19
	sub	w2, w2, #19
	cmp	w2, 2
	bhi	.L4461
.L4465:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4474
.L4463:
	mov	x0, x19
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
	mov	x0, x19
	bl	HEVC_RecoverDPBProcess
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4459:
	ldr	w3, [x19, 5564]
	mov	w2, 0
	ldr	w4, [x29, 44]
	mov	w0, 1
	ldr	x1, .LC1197
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4473:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4451:
	ldr	w1, [x19, 3396]
	mov	w0, 0
	cbz	w1, .L4457
	.p2align 2
.L4468:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	ldr	x2, [x1, 3408]
	str	wzr, [x2, 60]
	ldr	x1, [x1, 3408]
	str	w3, [x1, 64]
	ldr	w1, [x19, 3396]
	cmp	w0, w1
	bcc	.L4468
.L4457:
	ldr	w1, [x19, 3400]
	mov	w0, 0
	mov	w3, 1
	cbz	w1, .L4455
	.p2align 2
.L4467:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	ldr	x2, [x1, 3544]
	str	wzr, [x2, 60]
	ldr	x1, [x1, 3544]
	str	w3, [x1, 64]
	ldr	w1, [x19, 3400]
	cmp	w0, w1
	bcc	.L4467
	b	.L4455
	.p2align 3
.L4474:
	mov	x0, x19
	bl	HEVC_UpdateInterLayerReflist
	b	.L4463
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	3
.LC1195:
	.xword	.LC1194
	.align	3
.LC1197:
	.xword	.LC1196
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 176]
	cmp	w0, 2
	bls	.L4534
	ldr	w0, [x19, 312]
	add	x21, x19, 4096
	ldr	w1, [x19, 316]
	mov	w2, 1
	add	w0, w0, 1
	ldr	x3, [x19, 3032]
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 312]
	sub	w0, w0, w1
	str	w0, [x3, 616]
	strb	w2, [x21, 752]
	ldr	w20, [x19, 272]
	ldr	w2, [x19, 280]
	ubfx	x20, x20, 16, 3
	cmp	w20, w2
	beq	.L4480
	sub	w0, w2, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L4480
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L4535
.L4480:
	cmp	w20, 2
	str	w20, [x19, 280]
	beq	.L4482
	cmp	w20, 3
	bne	.L4531
.L4533:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
.L4530:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4531:
	ldr	w0, [x19, 260]
	cbz	w0, .L4501
	cmp	w20, 4
	ldr	w0, [x19, 4864]
	bne	.L4488
	cbnz	w0, .L4488
	mov	w0, 2
	strb	w0, [x19, 8]
	.p2align 2
.L4492:
	ldr	w2, [x19, 264]
	mov	w0, 2
	ldr	x1, .LC1207
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w2, [x19, 204]
	cbz	w2, .L4536
	ldr	w1, [x19, 4876]
	ldr	x0, [x19, 3032]
	ldr	w3, [x19, 4880]
	cmp	w1, wzr
	str	w2, [x19, 10024]
	cset	w2, eq
	str	w3, [x19, 8868]
	str	w2, [x19, 8876]
	ldr	w2, [x0, 632]
	strb	w2, [x21, 3440]
	ldr	w2, [x0, 636]
	strb	w2, [x21, 3441]
	ldr	w2, [x0, 640]
	strb	w2, [x21, 3443]
	ldr	w2, [x0, 644]
	strb	w2, [x21, 3444]
	ldr	w2, [x0, 684]
	ldr	w0, [x19, 264]
	str	w2, [x19, 8864]
	cbz	w0, .L4497
	add	x21, x21, 3440
	ldr	w0, [x19, 4892]
	str	x21, [x19, 3048]
	add	w1, w1, 1
	str	w0, [x21, 5192]
	ldr	w0, [x19, 4896]
	str	w0, [x21, 5196]
	str	w1, [x19, 4876]
	str	wzr, [x21, 5188]
	ldr	w0, [x19, 4864]
	cbnz	w0, .L4497
	ldr	x1, [x19, 10032]
	mov	w4, 0
	cbz	x1, .L4499
	.p2align 2
.L4500:
	ldp	w2, w0, [x1]
	ldr	x1, [x1, 1504]
	add	w0, w2, w0
	add	w0, w0, 7
	add	w4, w4, w0, lsr 3
	cbnz	x1, .L4500
.L4499:
	ldr	x0, .LC1198
	ldr	x5, [x0]
	cbz	x5, .L4497
	add	x2, x29, 64
	ldr	w0, [x19, 276]
	mov	w3, 4
	mov	w1, 20
	str	w4, [x2, -8]!
	blr	x5
.L4497:
	ldr	w4, [x19, 4904]
	mov	w0, 0
	ldr	x3, [x19, 4912]
	ldr	w1, [x19, 4900]
	str	w4, [x19, 4900]
	sub	w1, w1, w4
	ldr	w2, [x3, 328]
	add	w2, w2, w1
	str	w2, [x3, 328]
	ldr	w2, [x19, 5160]
	add	w1, w2, w1
	str	w1, [x19, 5160]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4482:
	ldr	w0, [x19, 4864]
	cbnz	w0, .L4486
	ldr	w1, [x19, 260]
	cbz	w1, .L4501
.L4488:
	cmp	w0, 2
	beq	.L4537
	cmp	w0, 1
	bne	.L4492
	strb	w0, [x19, 8]
	b	.L4492
	.p2align 3
.L4537:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	bne	.L4492
	ldr	x0, .LC1205
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L4492
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4492
	mov	w3, 1
	ldr	x1, .LC1212
	ldr	w2, [x19, 4860]
	mov	w0, w3
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1198
	ldr	x4, [x0]
	cbz	x4, .L4538
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, -1
	b	.L4530
	.p2align 3
.L4501:
	ldr	x0, .LC1198
	ldr	x4, [x0]
	cbz	x4, .L4486
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4486:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L4530
.L4535:
	ldr	x1, .LC1204
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	str	w20, [x19, 280]
	b	.L4533
	.p2align 3
.L4538:
	mov	w0, -1
	b	.L4530
	.p2align 3
.L4536:
	ldr	x0, .LC1198
	ldr	x4, [x0]
	cbz	x4, .L4495
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4495:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1208
	mov	w0, 0
	ldr	x1, .LC1210
	add	x2, x2, 488
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4530
	.p2align 3
.L4534:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1198
	ldr	x4, [x0]
	cbz	x4, .L4477
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4477:
	ldr	w0, [x19, 268]
	cmp	w0, 524288
	bls	.L4478
	ldr	x1, .LC1200
	mov	w0, 0
	bl	dprint_vfmw
.L4478:
	ldr	x1, .LC1202
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4530
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	3
.LC1198:
	.xword	g_event_report
	.align	3
.LC1200:
	.xword	.LC1199
	.align	3
.LC1202:
	.xword	.LC1201
	.align	3
.LC1204:
	.xword	.LC1203
	.align	3
.LC1205:
	.xword	g_allow_B_before_P
	.align	3
.LC1207:
	.xword	.LC1206
	.align	3
.LC1208:
	.xword	.LANCHOR5
	.align	3
.LC1210:
	.xword	.LC1209
	.align	3
.LC1212:
	.xword	.LC1211
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w23, w2
	mov	w25, w3
	mov	w20, w1
	bl	_mcount
	ldr	x0, [x19, 2936]
	mov	w1, 16
	str	xzr, [x29, 88]
	add	x22, x19, 4096
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	and	w24, w0, 31
	ldr	x0, [x19, 2936]
	mov	w1, 24
	bl	BsBack
	str	wzr, [x22, 1244]
	ldr	x1, [x22, 1256]
	str	x1, [x29, 88]
	cbz	w20, .L4541
	cmp	w20, 1
	beq	.L4542
	ldr	x1, .LC1229
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
.L4549:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4542:
	mov	w0, 31745
	cmp	w21, w0
	cbz	w23, .L4699
	ccmp	w24, 25, 0, eq
	bne	.L4570
	ldr	x20, .LC1213
	ldr	x4, [x20]
	cbz	x4, .L4571
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4571:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2976]
	cbz	w0, .L4700
.L4694:
	cbz	x1, .L4575
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4575:
	ldr	x4, [x20]
	cbz	x4, .L4674
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4674:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4541:
	cbnz	w23, .L4543
	mov	w0, 31745
	cmp	w21, w0
	ccmp	w24, 25, 0, eq
	bne	.L4544
	ldr	x20, .LC1213
	ldr	x4, [x20]
	cbz	x4, .L4545
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4545:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2976]
	cbnz	w0, .L4694
	ldr	w0, [x1, 48]
	add	x23, x22, 1240
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L4550
	ldr	x1, .LC1215
	mov	w3, 2348
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	b	.L4694
	.p2align 3
.L4543:
	mov	w0, 31745
	and	w21, w21, -513
	cmp	w21, w0
	mov	w0, 1
	bne	.L4549
	ldr	x2, .LC1216
	mov	w3, 2434
	ldr	x1, .LC1225
.L4678:
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	cbz	x1, .L4674
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	mov	w0, -1
	b	.L4549
	.p2align 3
.L4699:
	ccmp	w25, 1, 0, eq
	ccmp	w24, 25, 0, eq
	beq	.L4701
	mov	w1, 32257
	cmp	w21, w1
	beq	.L4702
	cmp	w21, w0
	bne	.L4703
.L4582:
	ldr	x1, [x19, 2976]
.L4685:
	cbz	x1, .L4675
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4675:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4570:
	mov	w1, 32257
	mov	w0, w20
	cmp	w21, w1
	bne	.L4549
	ldr	x2, .LC1216
	mov	w3, 2579
	ldr	x1, .LC1227
	b	.L4678
	.p2align 3
.L4544:
	mov	w1, 32257
	mov	w0, 1
	cmp	w21, w1
	bne	.L4549
	b	.L4582
	.p2align 3
.L4700:
	ldr	w0, [x1, 48]
	add	x23, x22, 1240
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L4574
	ldr	x1, .LC1215
	mov	w3, 2513
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	b	.L4694
	.p2align 3
.L4703:
	ldr	x0, [x19, 2936]
	mov	w1, 8
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2936]
	mov	w1, 8
	ubfx	x20, x20, 1, 6
	bl	BsSkip
	cmp	w20, 49
	bne	.L4582
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L4582
	ldr	x1, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2936]
	mov	w1, 24
	bl	BsSkip
	mov	w0, 2
	b	.L4549
	.p2align 3
.L4701:
	ldr	x20, .LC1213
	ldr	x4, [x20]
	cbz	x4, .L4564
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4564:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2976]
	cbz	w0, .L4685
	b	.L4694
	.p2align 3
.L4574:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 276]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L4704
	ldr	x21, .LC1219
	mov	x2, 5
	ldr	x1, .LC1220
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2976]
	ldr	x0, [x29, 88]
	ldr	w2, [x23, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x21, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x19, 2976]
	ldr	w2, [x1, 80]
	cbz	w2, .L4577
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L4578
	uxtw	x2, w0
	ldr	x1, .LC1215
	mov	w3, 2537
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	cbz	x1, .L4579
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4579:
	ldr	x4, [x20]
	cbz	x4, .L4580
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4580:
	ldr	w0, [x19, 276]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4674
	ldr	x2, .LC1216
	mov	w3, 2544
	ldr	x1, .LC1222
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
	.p2align 3
.L4550:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 276]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L4705
	ldr	x21, .LC1219
	mov	x2, 5
	ldr	x1, .LC1220
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2976]
	ldr	x0, [x29, 88]
	ldr	w2, [x23, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x21, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x19, 2976]
	ldr	w2, [x1, 80]
	cbz	w2, .L4554
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L4555
	uxtw	x2, w0
	ldr	x1, .LC1215
	mov	w3, 2372
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	cbz	x1, .L4556
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4556:
	ldr	x4, [x20]
	cbz	x4, .L4557
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4557:
	ldr	w0, [x19, 276]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4674
	ldr	x2, .LC1216
	mov	w3, 2379
	ldr	x1, .LC1222
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
.L4555:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2976]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L4554:
	ldr	x20, .LC1223
	ldr	w0, [x19, 276]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L4558
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 276]
	ldr	w1, [x22, 1244]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 276]
.L4558:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4582
	ldr	x2, .LC1216
	mov	w3, 2407
	ldr	x1, .LC1222
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
	.p2align 3
.L4578:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2976]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L4577:
	ldr	x20, .LC1223
	ldr	w0, [x19, 276]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L4581
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 276]
	ldr	w1, [x22, 1244]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 276]
.L4581:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4582
	ldr	x2, .LC1216
	mov	w3, 2567
	ldr	x1, .LC1222
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
	.p2align 3
.L4702:
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsSkip
	mov	w0, w20
	b	.L4549
.L4704:
	ldr	x2, .LC1216
	mov	w3, 2525
	ldr	x1, .LC1218
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
.L4705:
	ldr	x2, .LC1216
	mov	w3, 2360
	ldr	x1, .LC1218
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4549
	.size	HEVC_VES_Splitter, .-HEVC_VES_Splitter
	.align	3
.LC1213:
	.xword	g_event_report
	.align	3
.LC1215:
	.xword	.LC1214
	.align	3
.LC1216:
	.xword	.LANCHOR5
	.align	3
.LC1218:
	.xword	.LC1217
	.align	3
.LC1219:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1220:
	.xword	.LANCHOR4
	.align	3
.LC1222:
	.xword	.LC1221
	.align	3
.LC1223:
	.xword	vfmw_save_metadata_file
	.align	3
.LC1225:
	.xword	.LC1224
	.align	3
.LC1227:
	.xword	.LC1226
	.align	3
.LC1229:
	.xword	.LC1228
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CRAOutputFrame
	.type	HEVC_CRAOutputFrame, %function
HEVC_CRAOutputFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3372]
	cbz	w0, .L4718
	sub	w2, w0, #1
	mov	w20, 0
	add	x2, x2, 461
	add	x0, x19, 3680
	add	x2, x19, x2, lsl 3
	.p2align 2
.L4709:
	ldr	x1, [x0], 8
	ldrb	w1, [x1, 2]
	cmp	w1, wzr
	csinc	w20, w20, w20, ne
	cmp	x0, x2
	bne	.L4709
	.p2align 2
.L4710:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L4710
	cmp	w20, wzr
	ble	.L4712
	.p2align 2
.L4725:
	ldr	w1, [x19, 3372]
	cbz	w1, .L4713
	ldr	x0, [x19, 3680]
	ldrb	w0, [x0, 2]
	cbz	w0, .L4720
	add	x2, x19, 3688
	mov	w0, 0
	b	.L4717
	.p2align 3
.L4714:
	ldr	x3, [x2], 8
	ldrb	w3, [x3, 2]
	cbz	w3, .L4719
.L4717:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L4714
.L4713:
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L4715
	subs	w20, w20, #1
	bne	.L4725
.L4712:
	mov	w0, 0
.L4715:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4719:
	mov	w1, w0
	b	.L4713
.L4720:
	mov	w1, 0
	b	.L4713
.L4718:
	mov	w20, 0
	b	.L4710
	.size	HEVC_CRAOutputFrame, .-HEVC_CRAOutputFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2976]
	ldrsw	x3, [x19, 276]
	ldr	x2, .LC1230
	ldr	w1, [x0, 16]
	str	w1, [x19, 5580]
	ldr	w4, [x0, 28]
	str	w4, [x19, 5576]
	ldr	w20, [x0, 24]
	strb	wzr, [x19, 3]
	str	w20, [x19, 5584]
	ldr	x2, [x2, x3, lsl 3]
	ldrsb	w3, [x2, 44]
	cmp	w3, 1
	beq	.L4795
.L4733:
	ldr	w0, [x19, 5704]
	cmp	w0, 1
	beq	.L4796
.L4737:
	ldr	w0, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w0
	bcs	.L4797
	add	x20, x19, 4096
	ldrb	w0, [x20, 753]
	cbz	w0, .L4798
	mov	x0, x19
	bl	HEVC_PicTypeStatistic
	mov	x0, x19
	bl	HEVC_CalcStreamBits
	ldr	w0, [x19, 5704]
	cmp	w0, 2
	beq	.L4755
	ldr	w0, [x19, 2356]
	cbnz	w0, .L4756
	ldrb	w0, [x20, 1457]
	cbz	w0, .L4799
.L4756:
	mov	x0, x19
	bl	HEVC_WriteSliceMsg
	cbnz	w0, .L4800
.L4759:
	ldr	w0, [x19, 2356]
	cbz	w0, .L4801
.L4761:
	ldr	w0, [x19, 4236]
	ldr	w1, [x19, 4232]
	str	w0, [x19, 4896]
	mov	w0, 0
	str	w1, [x19, 4892]
.L4742:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4801:
	ldr	w1, [x19, 5564]
	mov	w0, 1
	ldr	w2, [x19, 5588]
	str	w0, [x19, 172]
	str	w1, [x19, 284]
	str	w2, [x19, 320]
	b	.L4761
	.p2align 3
.L4796:
	ldr	w0, [x19, 2356]
	cbnz	w0, .L4739
	cmp	w20, wzr
	sub	w1, w1, #16
	cset	w21, eq
	cmp	w1, 4
	cset	w0, ls
	tst	w21, w0
	beq	.L4802
.L4740:
	mov	x0, x19
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L4803
.L4741:
	add	x0, x19, x20, uxtw
	ldrb	w0, [x0, 4]
	cmp	w0, 1
	cset	w0, eq
	tst	w21, w0
	beq	.L4743
	ldr	w0, [x19, 3372]
	cbnz	w0, .L4804
	.p2align 2
.L4743:
	ldr	x1, [x19, 3032]
	ldr	w0, [x1, 12]
	cbnz	w0, .L4744
	ldr	w0, [x19, 2364]
	cmp	w0, 1
	beq	.L4805
	ldr	w0, [x19, 5576]
	ldr	x2, [x19, 3000]
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 360]
	cbnz	w20, .L4744
.L4810:
	ldr	w3, [x19, 212]
	mov	w20, -2147483647
	cmp	w3, w20
	beq	.L4744
	ldr	w2, [x19, 5564]
	add	w0, w3, w0
	cmp	w2, w0
	bcs	.L4744
	ldr	w0, [x19, 5580]
	cmp	w0, 21
	bne	.L4744
	ldr	x1, .LC1237
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_CRAOutputFrame
	str	w20, [x19, 212]
	ldr	x1, [x19, 3032]
	.p2align 2
.L4744:
	ldr	w0, [x1, 8]
	cmp	w0, 2
	beq	.L4739
	ldr	w0, [x1, 24]
	cmp	w0, 2
	bne	.L4749
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4806
.L4750:
	mov	x0, x19
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
.L4739:
	mov	x0, x19
	bl	HEVC_InitPic
	cmn	w0, #2
	beq	.L4742
	cbnz	w0, .L4807
	ldr	w1, [x19, 264]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x19, 264]
	bl	HEVC_SetScalingList
	mov	x0, x19
	bl	HEVC_WritePicMsg
	cbz	w0, .L4737
	ldr	x1, .LC1241
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4795:
	ldr	w3, [x2, 156]
	cbnz	w3, .L4733
	ldr	w2, [x2, 160]
	cmp	w2, 1
	bne	.L4733
	ldr	w0, [x0, 16]
	sub	w2, w0, #19
	cmp	w2, 1
	bls	.L4808
.L4735:
	sub	w0, w0, #6
	cmp	w0, 3
	bls	.L4733
	ldr	x2, [x19, 4272]
	str	x2, [x19, 4256]
	b	.L4733
	.p2align 3
.L4755:
	ldr	x1, [x19, 2976]
	cbz	x1, .L4759
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	b	.L4759
	.p2align 3
.L4799:
	mov	x0, x19
	bl	HEVC_DecList
	cbnz	w0, .L4809
	mov	x0, x19
	bl	HEVC_IsRefListWrong
	cbz	w0, .L4756
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	x1, .LC1252
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4802:
	ldr	w0, [x19, 4864]
	cbnz	w0, .L4741
	ldr	x0, [x19, 3032]
	mov	x1, 4294967296
	ldr	x2, [x0, 688]
	cmp	x2, x1
	bne	.L4741
	ldr	w1, [x0, 696]
	cbnz	w1, .L4741
	ldr	w0, [x0, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L4741
	b	.L4740
	.p2align 3
.L4749:
	mov	x0, x19
	bl	HEVC_RefPicProcess
	cbz	w0, .L4739
	mov	w0, -1
	b	.L4742
.L4804:
	mov	x0, x19
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L4743
	ldr	x2, .LC1231
	mov	w0, 1
	ldr	x1, .LC1235
	add	x2, x2, 528
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4798:
	ldr	x1, .LC1248
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4805:
	ldr	x4, [x19, 3000]
	mov	w0, 0
	add	x2, x4, 360
	add	x4, x4, 392
	.p2align 2
.L4746:
	ldr	w3, [x2], 4
	cmp	w0, w3
	csel	w0, w0, w3, cs
	cmp	x2, x4
	bne	.L4746
	cbnz	w20, .L4744
	b	.L4810
	.p2align 3
.L4797:
	ldr	x1, .LC1243
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w1
	bcc	.L4753
	ldr	x0, .LC1244
	ldr	x4, [x0]
	cbz	x4, .L4753
	ldr	w0, [x19, 276]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L4753:
	ldr	x1, .LC1246
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4800:
	ldr	x1, .LC1254
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4807:
	ldr	x1, .LC1239
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.p2align 3
.L4808:
	ldr	x2, [x19, 3032]
	ldr	x2, [x2, 56]
	cmn	x2, #1
	beq	.L4736
	ldr	x3, [x19, 12768]
	str	x2, [x19, 12760]
	str	x3, [x19, 12776]
.L4736:
	add	x2, x19, 12288
	mov	w3, 1
	strb	w3, [x2, 448]
	b	.L4735
.L4806:
	mov	x0, x19
	bl	HEVC_UpdateInterLayerReflist
	b	.L4750
.L4809:
	ldr	x1, .LC1250
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
.L4803:
	ldr	x2, .LC1231
	mov	w0, 1
	ldr	x1, .LC1233
	add	x2, x2, 528
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4742
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	3
.LC1230:
	.xword	s_pstVfmwChan
	.align	3
.LC1231:
	.xword	.LANCHOR5
	.align	3
.LC1233:
	.xword	.LC1232
	.align	3
.LC1235:
	.xword	.LC1234
	.align	3
.LC1237:
	.xword	.LC1236
	.align	3
.LC1239:
	.xword	.LC1238
	.align	3
.LC1241:
	.xword	.LC1240
	.align	3
.LC1243:
	.xword	.LC1242
	.align	3
.LC1244:
	.xword	g_event_report
	.align	3
.LC1246:
	.xword	.LC1245
	.align	3
.LC1248:
	.xword	.LC1247
	.align	3
.LC1250:
	.xword	.LC1249
	.align	3
.LC1252:
	.xword	.LC1251
	.align	3
.LC1254:
	.xword	.LC1253
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, [x19, 2976]
	ldr	w0, [x3, 8]
	cbz	w0, .L4816
	ldr	w2, [x19, 268]
	mov	w0, 0
	.p2align 2
.L4815:
	uxtw	x1, w0
	add	w0, w0, 1
	add	x1, x3, x1, lsl 5
	ldr	w1, [x1, 48]
	add	w2, w2, w1
	str	w2, [x19, 268]
	ldr	w1, [x3, 8]
	cmp	w1, w0
	bhi	.L4815
.L4816:
	strb	wzr, [x3]
	ldr	x0, [x19, 2976]
	ldr	w1, [x0, 16]
	sub	w1, w1, #36
	cmp	w1, 1
	bls	.L4959
.L4814:
	ldr	w1, [x0, 4]
	add	w1, w1, 16
	str	w1, [x0, 4]
	ldr	x1, [x19, 2976]
	ldr	w2, [x1, 16]
	cmp	w2, 49
	bls	.L4960
.L4817:
	ldr	x1, .LC1266
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	ldr	w0, [x1, 16]
	cmp	w0, 63
	bhi	.L4844
	cbnz	x1, .L4946
	.p2align 2
.L4944:
	mov	w0, 0
.L4963:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4960:
	ldr	x0, .LC1255
	ldrb	w0, [x0,w2,uxtw]
	adr	x3, .Lrtx4819
	add	x0, x3, w0, sxtb #2
	br	x0
.Lrtx4819:
	.section	.rodata
	.align	0
	.align	2
.L4819:
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4818 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4820 - .Lrtx4819) / 4
	.byte	(.L4821 - .Lrtx4819) / 4
	.byte	(.L4822 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4823 - .Lrtx4819) / 4
	.byte	(.L4823 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4817 - .Lrtx4819) / 4
	.byte	(.L4824 - .Lrtx4819) / 4
	.byte	(.L4825 - .Lrtx4819) / 4
	.text
	.p2align 3
.L4959:
	mov	w1, 1
	strb	w1, [x19, 3]
	b	.L4814
.L4825:
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L4961
.L4841:
	ldr	x1, [x19, 2976]
	cbz	x1, .L4944
.L4946:
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	mov	w0, 0
.L4943:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4818:
	mov	x0, x19
	bl	HEVC_DecSlice
	cmn	w0, #2
	beq	.L4943
	cbz	w0, .L4944
	ldr	x1, [x19, 2976]
	cbz	x1, .L4957
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4957:
	ldr	x0, .LC1258
	ldr	x4, [x0]
	cbz	x4, .L4945
.L4947:
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4945:
	mov	w0, -1
.L4962:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4821:
	mov	x0, x19
	bl	HEVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 2976]
	cbz	x1, .L4831
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4831:
	cbz	w20, .L4944
	ldr	x1, .LC1260
	b	.L4954
.L4822:
	mov	x0, x19
	bl	HEVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 2976]
	cbz	x1, .L4833
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4833:
	cbz	w20, .L4944
	ldr	x1, .LC1262
	b	.L4954
.L4820:
	mov	x0, x19
	bl	HEVC_DecVPS
	mov	w20, w0
	ldr	x1, [x19, 2976]
	cbz	x1, .L4826
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4826:
	cbz	w20, .L4944
	ldr	x1, .LC1257
.L4954:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1258
	ldr	x4, [x21]
	cbz	x4, .L4945
	add	x2, x29, 64
	ldr	w0, [x19, 276]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L4945
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L4823:
	mov	x0, x19
	bl	HEVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 2976]
	cbz	x1, .L4834
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4834:
	cbz	w20, .L4944
	ldr	x1, .LC1264
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4957
.L4824:
	ldrb	w0, [x19, 10]
	cmp	w0, 1
	beq	.L4839
	cbz	x1, .L4838
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4838:
	add	x0, x19, 4096
	ldrb	w0, [x0, 753]
	cbz	w0, .L4944
.L4839:
	add	x20, x19, 3328
	mov	w1, 32
	strb	wzr, [x19, 10]
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L4944
	ldr	x20, .LC1258
	ldr	x4, [x20]
	cbz	x4, .L4840
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4840:
	add	x0, x19, 4096
	ldrb	w0, [x0, 753]
	cbz	w0, .L4944
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L4944
.L4843:
	ldr	x4, [x20]
	cbnz	x4, .L4947
	mov	w0, -1
	b	.L4962
	.p2align 3
.L4844:
	ldr	x20, .LC1258
	ldr	x4, [x20]
	cbz	x4, .L4845
	ldr	w0, [x19, 276]
	mov	w1, 102
	mov	w3, 0
	mov	x2, 0
	blr	x4
	ldr	x1, [x19, 2976]
	cbz	x1, .L4846
.L4847:
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L4846:
	ldr	x4, [x20]
	cbz	x4, .L4944
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, 0
	b	.L4963
.L4845:
	cbnz	x1, .L4847
	mov	w0, 0
	b	.L4963
.L4961:
	ldr	x20, .LC1258
	strb	w0, [x19, 11]
	ldr	x4, [x20]
	cbz	x4, .L4842
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4842:
	add	x0, x19, 4096
	ldrb	w0, [x0, 753]
	cbz	w0, .L4841
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L4841
	ldr	x1, [x19, 2976]
	cbz	x1, .L4843
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	b	.L4843
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	3
.LC1255:
	.xword	.L4819
	.align	3
.LC1257:
	.xword	.LC1256
	.align	3
.LC1258:
	.xword	g_event_report
	.align	3
.LC1260:
	.xword	.LC1259
	.align	3
.LC1262:
	.xword	.LC1261
	.align	3
.LC1264:
	.xword	.LC1263
	.align	3
.LC1266:
	.xword	.LC1265
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x19, 1]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x21, x2
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	str	wzr, [x21]
	ldr	x3, .LC1267
	add	x0, x19, 4096
	str	wzr, [x22]
	mov	x2, 1376
	mov	w1, 0
	add	x0, x0, 1456
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, [x19, 2976]
	mov	x0, x19
	ldr	w2, [x1, 16]
	str	w2, [x19, 5580]
	ldr	w2, [x1, 28]
	str	w2, [x19, 5576]
	ldr	w1, [x1, 24]
	str	w1, [x19, 5584]
	bl	HEVC_DecSliceSegmentHeader
	cbnz	w0, .L4986
	ldr	w1, [x19, 5588]
	mov	w3, 5036
	ldr	x0, [x19, 2960]
	mov	w20, 12668
	ldr	w23, [x19, 2356]
	ldr	x2, [x19, 2952]
	smaddl	x0, w1, w3, x0
	cmp	w23, 1
	ldr	w0, [x0, 32]
	smaddl	x20, w0, w20, x2
	beq	.L4987
	ldr	w0, [x19, 5704]
	cmp	w0, 1
	cset	w0, eq
	str	w0, [x22]
	ldr	x0, [x19, 3000]
	ldr	x1, [x19, 3032]
	ldr	w2, [x20, 184]
	ldp	w5, w3, [x0, 64]
	ldr	w0, [x0, 184]
	ldp	w6, w4, [x20, 64]
	cmp	w2, w0
	ldr	w0, [x1, 880]
	cset	w2, ne
	cmp	w0, 1
	beq	.L4988
.L4971:
	cmp	w6, w5
	cset	w0, ne
	cmp	w4, w3
	orr	w0, w2, w0
	cset	w1, ne
	orr	w0, w1, w0
	cbz	w0, .L4974
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4989
.L4975:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21]
.L4967:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4987:
	ldr	x0, [x19, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	ldp	w2, w1, [x20, 188]
	ldr	w3, [x19, 204]
	mul	w1, w1, w2
	add	w3, w3, 1
	udiv	w3, w1, w3
	ccmp	w0, w3, 1, ge
	blt	.L4969
.L4974:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4986:
	ldr	x1, .LC1269
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1270
	ldr	x4, [x0]
	cbz	x4, .L4976
	add	x2, x29, 80
	ldr	w0, [x19, 276]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4988:
	ldr	w7, [x20, 96]
	ldr	w0, [x20, 88]
	cmp	w0, w7
	csel	w0, w0, w7, cs
	str	w0, [x1, 940]
	ldr	x0, [x19, 3000]
	ldr	x7, [x19, 3032]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	ldr	w1, [x7, 940]
	cmp	w0, 8
	ccmp	w1, 8, 0, hi
	bne	.L4990
.L4972:
	mov	w0, 1
	str	w0, [x7, 944]
	str	w0, [x21]
	b	.L4971
	.p2align 3
.L4989:
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L4975
	ldr	w1, [x19, 2384]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4976:
	mov	w0, -1
	b	.L4967
	.p2align 3
.L4990:
	cmp	w0, 8
	ccmp	w1, 8, 4, eq
	ble	.L4971
	b	.L4972
.L4969:
	ldr	x1, .LC1272
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4967
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	3
.LC1267:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1269:
	.xword	.LC1268
	.align	3
.LC1270:
	.xword	g_event_report
	.align	3
.LC1272:
	.xword	.LC1271
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w0, [x19, 204]
	cbnz	w0, .L4992
	add	x0, x19, 4096
	mov	w20, -1
	ldrb	w0, [x0, 753]
	cbnz	w0, .L4996
.L4992:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4996:
	ldr	x2, .LC1273
	mov	w0, 0
	ldr	x1, .LC1275
	add	x2, x2, 544
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	3
.LC1273:
	.xword	.LANCHOR5
	.align	3
.LC1275:
	.xword	.LC1274
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19, 10032]
	mov	w0, 0
	cbz	x2, .L4998
	.p2align 2
.L4999:
	ldp	w3, w1, [x2]
	ldr	x2, [x2, 1504]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L4999
.L4998:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFrameEndNal
	.type	HEVC_IsFrameEndNal, %function
HEVC_IsFrameEndNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sub	w0, w19, #32
	sub	w19, w19, #48
	cmp	w0, 2
	ccmp	w19, 1, 0, hi
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFrameEndNal, .-HEVC_IsFrameEndNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_CheckSedOnly
	.type	HEVCDEC_CheckSedOnly, %function
HEVCDEC_CheckSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2352]
	str	wzr, [x19, 2356]
	cmp	w0, 2
	str	wzr, [x19, 2364]
	beq	.L5033
	cmp	w0, 1
	mov	w0, 0
	beq	.L5034
.L5025:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5034:
	ldr	w1, [x19, 2360]
	cmp	w1, 1
	bne	.L5025
	str	wzr, [x19, 2360]
	.p2align 2
.L5031:
	mov	w0, -1
	b	.L5025
	.p2align 3
.L5033:
	ldr	w0, [x19, 2348]
	cbz	w0, .L5031
	ldr	w1, [x19, 2360]
	mov	w0, 0
	cmp	w1, 1
	beq	.L5025
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshSeg
	cbz	w0, .L5031
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L5031
	ldr	x1, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2936]
	mov	w1, 24
	bl	BsSkip
	ldr	x0, [x19, 2936]
	bl	BsResidBits
	cmp	w0, 15
	ble	.L5031
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsSkip
	ldr	x0, [x19, 2936]
	mov	w1, 6
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2936]
	mov	w1, 9
	bl	BsSkip
	mov	w0, w20
	bl	HEVC_IsSliceUnit
	sxtb	w21, w0
	cmp	w21, 1
	beq	.L5035
	ldr	w0, [x19, 204]
	cbz	w0, .L5031
	sub	w0, w20, #32
	sub	w20, w20, #48
	cmp	w0, 2
	ccmp	w20, 1, 0, hi
	bhi	.L5031
.L5012:
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5031
	add	x2, x19, 4096
	mov	w1, 1
	str	w1, [x19, 2364]
	mov	w0, -1
	strb	w1, [x2, 752]
	b	.L5025
	.p2align 3
.L5035:
	ldr	x0, [x19, 2936]
	bl	BsResidBits
	cmp	w0, wzr
	mov	w0, 0
	ble	.L5009
	ldr	x0, [x19, 2936]
	mov	w1, w21
	bl	BsGet
.L5009:
	ldr	w1, [x19, 204]
	cbnz	w1, .L5036
.L5010:
	add	x1, x19, 4096
	mov	w0, 1
	str	wzr, [x19, 2360]
	str	w0, [x19, 2356]
	mov	w0, 0
	ldrb	w1, [x1, 753]
	str	w1, [x19, 2368]
	b	.L5025
.L5036:
	sub	w1, w20, #32
	sub	w20, w20, #48
	cmp	w1, 2
	ccmp	w20, 1, 0, hi
	ccmp	w0, wzr, 0, hi
	beq	.L5010
	b	.L5012
	.size	HEVCDEC_CheckSedOnly, .-HEVCDEC_CheckSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_IsNeedSedOnly
	.type	HEVCDEC_IsNeedSedOnly, %function
HEVCDEC_IsNeedSedOnly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 204]
	cbz	w0, .L5040
	ldr	x1, [x19, 3048]
	cbz	x1, .L5045
.L5040:
	mov	w0, 0
.L5039:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5045:
	ldr	w1, [x19, 7560]
	cmp	w1, 1
	bls	.L5040
	ldr	w1, [x19, 2372]
	cmp	w0, w1
	beq	.L5040
	ldr	w0, [x19, 2356]
	cmp	w0, 1
	beq	.L5046
	cbnz	w0, .L5040
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L5040
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshSeg
	cmp	w0, wzr
	cset	w0, ne
	b	.L5039
	.p2align 3
.L5046:
	ldr	x0, [x19, 2976]
	cmp	x0, xzr
	cset	w0, ne
	b	.L5039
	.size	HEVCDEC_IsNeedSedOnly, .-HEVCDEC_IsNeedSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_SetDecParam
	.type	HEVCDEC_SetDecParam, %function
HEVCDEC_SetDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19, 2360]
	cmp	w20, 1
	beq	.L5063
.L5048:
	mov	x0, x19
	bl	HEVCDEC_IsNeedSedOnly
	cmp	w0, 1
	beq	.L5064
	ldr	w0, [x19, 2356]
	cmp	w0, 1
	beq	.L5065
.L5047:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5065:
	ldr	w2, [x19, 176]
	add	x0, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	ldr	w2, [x19, 2368]
	strb	w2, [x0, 753]
.L5062:
	ldr	x1, [x19, 2976]
	cbz	x1, .L5047
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5063:
	ldr	w0, [x19, 204]
	cbz	w0, .L5048
	ldr	x0, [x19, 3048]
	cbnz	x0, .L5048
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5062
	add	x0, x19, 4096
	str	w20, [x19, 2364]
	strb	w20, [x0, 752]
	b	.L5047
	.p2align 3
.L5064:
	ldr	w1, [x19, 204]
	ldr	x2, [x19, 3032]
	str	w0, [x19, 12724]
	add	x0, x19, 4096
	str	w1, [x19, 2372]
	add	x0, x0, 3440
	str	w1, [x19, 10024]
	ldr	w1, [x2, 684]
	str	w1, [x19, 8864]
	str	wzr, [x19, 2360]
	str	x0, [x19, 3048]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVCDEC_SetDecParam, .-HEVCDEC_SetDecParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMProcSedOnly
	.type	HEVCDEC_VDMProcSedOnly, %function
HEVCDEC_VDMProcSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x3, w20
	ldr	x1, [x19, 3048]
	lsl	x0, x3, 2
	ldr	x20, .LC1277
	sub	x3, x0, x3
	ldr	x4, .LC1276
	lsl	x0, x3, 4
	ldrsw	x5, [x19, 276]
	ldp	w21, w2, [x1, 20]
	sub	x3, x0, x3
	ldr	x1, .LC1279
	mov	w0, 22
	ldr	x22, [x4, x5, lsl 3]
	add	x20, x20, x3, lsl 2
	madd	w21, w2, w21, w21
	ldr	w3, [x20, 20]
	add	w21, w21, w2
	mov	w2, w21
	bl	dprint_vfmw
	ldr	w0, [x20, 20]
	cmp	w21, w0
	ldr	w0, [x19, 2356]
	beq	.L5076
	cmp	w0, 1
	beq	.L5077
.L5071:
	str	xzr, [x19, 3048]
.L5069:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5077:
	ldr	w2, [x19, 176]
	add	x0, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	str	wzr, [x19, 2360]
	ldr	w2, [x19, 2368]
	strb	w2, [x0, 753]
	ldr	x1, [x19, 2976]
	cbz	x1, .L5071
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	b	.L5071
	.p2align 3
.L5076:
	cmp	w0, 1
	beq	.L5068
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5069
	add	x1, x19, 4096
	mov	w0, 1
	str	w0, [x19, 2364]
	strb	w0, [x1, 752]
	b	.L5069
	.p2align 3
.L5068:
	ldr	w2, [x19, 176]
	add	x4, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	str	w0, [x19, 2360]
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	ldr	w5, [x19, 2368]
	strb	w5, [x4, 753]
	strb	w0, [x22, 745]
	strb	w0, [x19, 9]
	mov	w0, 0
	str	xzr, [x19, 3048]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	3
.LC1276:
	.xword	s_pstVfmwChan
	.align	3
.LC1277:
	.xword	g_BackUp
	.align	3
.LC1279:
	.xword	.LC1278
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x20, .LC1280
	mov	x2, 29136
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x19, 7528]
	ldr	x3, [x20, 96]
	blr	x3
	str	x21, [x19, 3032]
	str	xzr, [x19, 3048]
	str	w22, [x19, 7528]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L5088
	mov	w0, 17
	mov	w3, 65
	mov	w2, 200
	mov	w1, 210
	stp	w2, w0, [x19, 152]
	stp	w0, w3, [x19, 160]
	str	w1, [x19, 168]
.L5080:
	ldr	w0, [x21, 624]
	bl	MEM_Phy2Vir
	mov	x5, x0
	cbz	x0, .L5089
	ldr	x11, [x19, 3032]
	mov	w2, 24912
	ldr	w12, [x19, 156]
	mov	w22, 12668
	ldpsw	x7, x6, [x19, 160]
	ldr	w8, [x11, 620]
	mov	w23, 5036
	ldrsw	x9, [x19, 152]
	ldr	w3, [x19, 168]
	madd	w1, w12, w2, w8
	lsl	w4, w9, 2
	add	x8, x0, x8, uxtw
	sub	w10, w4, w9
	str	x8, [x19, 2944]
	madd	w7, w22, w7, w1
	add	x1, x0, x1, uxtw
	str	x1, [x19, 2952]
	add	w1, w3, 1
	lsl	w4, w1, 3
	sub	w4, w4, w1
	lsl	w4, w4, 1
	sub	w1, w4, w1
	lsl	w4, w10, 6
	madd	w6, w23, w6, w7
	sub	w4, w4, w10
	add	x7, x0, x7, uxtw
	str	x7, [x19, 2960]
	add	w4, w6, w4, lsl 3
	add	x0, x0, x6, uxtw
	add	w1, w4, w1, lsl 3
	str	x0, [x19, 3040]
	add	x4, x5, x4, uxtw
	str	x4, [x19, 3024]
	add	x5, x5, x1, uxtw
	str	x5, [x19, 3016]
	add	w3, w1, w3, lsl 3
	ldr	w4, [x11, 628]
	cmp	w3, w4
	bhi	.L5090
	ldr	w1, [x21, 656]
	cbz	w1, .L5091
.L5084:
	lsl	x2, x9, 2
	ldr	x3, [x20, 96]
	sub	x9, x2, x9
	mov	w1, 0
	lsl	x2, x9, 6
	sub	x2, x2, x9
	lsl	x2, x2, 3
	blr	x3
	ldr	w2, [x19, 168]
	mov	w4, 104
	ldr	x3, [x20, 96]
	mov	w1, 0
	add	w2, w2, 1
	ldr	x0, [x19, 3024]
	smull	x2, w2, w4
	blr	x3
	ldrsw	x2, [x19, 168]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 3016]
	lsl	x2, x2, 3
	blr	x3
	ldp	w5, w4, [x19, 156]
	mov	x1, -24912
	mov	w0, 24912
	ldr	w2, [x19, 164]
	mov	w8, 5036
	ldr	x9, [x19, 2944]
	mov	x7, -5036
	smaddl	x0, w5, w0, x1
	mov	w3, 12668
	mov	x1, -12668
	ldr	x6, [x19, 2960]
	smaddl	x3, w4, w3, x1
	ldr	x4, [x19, 2952]
	add	x1, x9, x0
	smaddl	x0, w2, w8, x7
	str	x1, [x19, 2992]
	add	x2, x4, x3
	add	x0, x6, x0
	str	x2, [x19, 3000]
	str	x0, [x19, 3008]
	mov	x0, x19
	str	w5, [x1, 4]
	ldr	x1, [x19, 3008]
	ldr	w2, [x19, 160]
	str	w2, [x1, 28]
	ldr	x1, [x19, 3000]
	ldr	w2, [x19, 164]
	str	w2, [x1, 56]
	bl	HEVC_InitScalingOrderTable
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 276]
	beq	.L5085
	mov	w1, -2147483647
	mov	x0, x19
	stp	w1, w1, [x19, 212]
	bl	HEVC_InitDecPara
	str	wzr, [x19, 12792]
	ldr	w0, [x19, 164]
	mov	w2, 9999
	ldr	x1, [x19, 3032]
	str	w0, [x19, 320]
	mov	w0, 1
	str	w2, [x19, 284]
	strb	w0, [x19]
	ldr	w0, [x1, 12]
	cbnz	w0, .L5086
.L5087:
	str	wzr, [x19, 2376]
	mov	w0, 0
	ldr	w1, [x1, 672]
	str	w1, [x19, 2348]
.L5082:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5086:
	mov	w0, 6
	str	w0, [x1, 24]
	ldr	x1, [x19, 3032]
	b	.L5087
	.p2align 3
.L5091:
	smull	x2, w12, w2
	ldr	x3, [x20, 96]
	mov	x0, x8
	blr	x3
	ldr	w2, [x19, 160]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2952]
	smull	x2, w2, w22
	blr	x3
	ldr	w2, [x19, 164]
	mov	w1, 0
	ldr	x0, [x19, 2960]
	ldr	x3, [x20, 96]
	smull	x2, w2, w23
	blr	x3
	ldrsw	x9, [x19, 152]
	ldr	x0, [x19, 3040]
	b	.L5084
	.p2align 3
.L5088:
	ldr	w0, [x21, 736]
	str	w0, [x19, 156]
	ldr	w0, [x21, 740]
	str	w0, [x19, 160]
	ldr	w0, [x21, 744]
	str	w0, [x19, 164]
	ldr	w0, [x21, 732]
	str	w0, [x19, 152]
	add	w0, w0, 5
	str	w0, [x19, 168]
	b	.L5080
	.p2align 3
.L5090:
	ldr	x2, .LC1281
	mov	w0, 0
	ldr	x1, .LC1285
	add	x2, x2, 568
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5082
.L5085:
	ldr	x2, .LC1281
	mov	w0, 0
	ldr	x1, .LC1287
	add	x2, x2, 568
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5082
.L5089:
	ldr	x2, .LC1281
	mov	w0, 0
	ldr	x1, .LC1283
	add	x2, x2, 568
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5082
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	3
.LC1280:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1281:
	.xword	.LANCHOR5
	.align	3
.LC1283:
	.xword	.LC1282
	.align	3
.LC1285:
	.xword	.LC1284
	.align	3
.LC1287:
	.xword	.LC1286
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 180]
	cbz	w0, .L5095
	add	x20, x19, 4096
	ldrb	w0, [x20, 753]
	cmp	w0, 1
	beq	.L5095
	add	x1, x19, 12288
	add	x4, x19, 28672
	add	x1, x1, 2448
	add	x4, x4, 464
	.p2align 2
.L5101:
	ldr	w0, [x1, 48]
	cbnz	w0, .L5096
	cbz	x1, .L5097
	ldr	w3, [x19, 3372]
	cbz	w3, .L5097
	ldr	x0, [x19, 3680]
	cmp	x0, x1
	beq	.L5096
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L5098
	.p2align 3
.L5099:
	ldr	x2, [x0, 3680]
	cmp	x2, x1
	beq	.L5096
.L5098:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L5099
.L5097:
	ldr	w0, [x19, 276]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L5095
	cmn	w0, #1
	beq	.L5120
.L5119:
	mov	w0, 0
.L5121:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5095:
	ldp	x19, x20, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5096:
	add	x1, x1, 720
	cmp	x1, x4
	bne	.L5101
	add	x2, x29, 44
	add	x1, x29, 40
	add	x0, x20, 2832
	bl	GetQueueImgNum
	mov	x0, x19
	bl	HEVC_PrintFrameStoreState
	ldr	x1, .LC1291
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	w0, [x19, 180]
	ldr	w2, [x19, 3372]
	ldp	w3, w4, [x29, 40]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w4
	cmp	w1, w0
	bge	.L5119
	ldr	x2, .LC1292
	mov	w0, 0
	ldr	x1, .LC1294
	add	x2, x2, 584
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L5120:
	ldr	x1, .LC1289
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	add	x1, x20, 2832
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L5121
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	3
.LC1289:
	.xword	.LC1288
	.align	3
.LC1291:
	.xword	.LC1290
	.align	3
.LC1292:
	.xword	.LANCHOR5
	.align	3
.LC1294:
	.xword	.LC1293
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 100]
	stp	wzr, wzr, [x29, 92]
	cbz	x20, .L5203
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L5204
	ldr	x2, [x19, 3032]
	ldrb	w0, [x19, 9]
	cmp	w0, 1
	ldr	w0, [x2, 8]
	ubfiz	w0, w0, 16, 3
	str	w0, [x19, 272]
	beq	.L5126
	ldr	w0, [x2, 880]
	cmp	w0, 1
	beq	.L5205
.L5127:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_ReceivePacket
	mov	w20, w0
	ldr	x0, [x19, 2976]
	str	x0, [x19, 2984]
.L5128:
	strb	wzr, [x19, 9]
	cbz	w20, .L5129
.L5153:
	mov	w20, 0
.L5198:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L5129:
	mov	x0, x19
	bl	HEVCDEC_CheckSedOnly
	mov	w20, w0
	cbz	w0, .L5206
.L5201:
	ldr	x1, [x19, 2976]
	cbz	x1, .L5134
.L5200:
	ldr	w0, [x19, 276]
	mov	w20, -1
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L5205:
	ldr	w0, [x2, 928]
	cmp	w0, 1
	bne	.L5127
	ldr	w0, [x19, 344]
	cmp	w0, 1
	bne	.L5127
	ldr	x0, [x19, 2984]
	mov	w20, 0
	strb	wzr, [x19, 9]
	str	wzr, [x19, 344]
	str	x0, [x19, 2976]
	b	.L5198
	.p2align 3
.L5126:
	ldr	x0, [x19, 2976]
	cmp	x0, xzr
	csetm	w20, eq
	cbz	w20, .L5128
	ldr	x1, .LC1300
	mov	w0, 0
	bl	dprint_vfmw
	b	.L5198
	.p2align 3
.L5206:
	ldr	x0, [x19, 2976]
	str	wzr, [x0, 4]
	ldr	x1, [x19, 2976]
	ldr	x0, [x19, 2936]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2936]
	mov	w1, 24
	bl	BsSkip
	ldr	x23, .LC1301
	ldrsw	x0, [x19, 276]
	ldr	x0, [x23, x0, lsl 3]
	ldrsb	w21, [x0, 44]
	cmp	w21, 1
	beq	.L5207
	mov	w22, 2
	mov	w21, 0
	mov	w25, w22
.L5132:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x24, [x19, 2976]
	ldr	x0, [x19, 2936]
	mov	w1, 6
	bl	BsGet
	str	w0, [x24, 16]
	mov	w1, 6
	ldr	x24, [x19, 2976]
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x24, 24]
	ldr	x24, [x19, 2976]
	ldr	w2, [x24, 24]
	cmp	w2, 1
	bls	.L5133
	mov	w3, 1
	ldr	x1, .LC1303
	mov	w0, w3
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	cbnz	x1, .L5200
	.p2align 2
.L5134:
	mov	w20, -1
	b	.L5198
	.p2align 3
.L5133:
	ldr	x0, [x19, 3032]
	ldr	w3, [x0, 24]
	and	w0, w3, -5
	cmp	w0, wzr
	ccmp	w2, wzr, 4, eq
	bne	.L5208
	ldr	x0, [x19, 2936]
	mov	w1, 3
	bl	BsGet
	str	w0, [x24, 28]
	ldr	x24, [x19, 2976]
	ldr	w0, [x24, 28]
	cbz	w0, .L5136
	sub	w0, w0, #1
	str	w0, [x24, 28]
	ldr	x24, [x19, 2976]
.L5136:
	ldr	w0, [x24, 16]
	bl	HEVC_IsSliceUnit
	sxtb	w26, w0
	cmp	w26, 1
	beq	.L5209
	str	wzr, [x24, 4]
	add	x0, x19, 3328
	ldr	x1, [x19, 2976]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2936]
	mov	w1, 24
	bl	BsSkip
	cmp	w25, 1
	ccmp	w22, wzr, 0, eq
	ccmp	w21, 1, 4, eq
	beq	.L5151
	ldr	x0, [x19, 2936]
	mov	w1, 16
	bl	BsSkip
.L5151:
	ldr	x0, [x19, 2936]
	mov	w1, 1
	bl	BsGet
	ldr	x21, [x19, 2976]
	ldr	x0, [x19, 2936]
	mov	w1, 6
	bl	BsGet
	str	w0, [x21, 16]
	mov	w1, 6
	ldr	x21, [x19, 2976]
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x21, 24]
	mov	w1, 3
	ldr	x21, [x19, 2976]
	ldr	x0, [x19, 2936]
	bl	BsGet
	str	w0, [x21, 28]
	ldr	x1, [x19, 2976]
	ldr	w0, [x1, 28]
	cbz	w0, .L5141
	sub	w0, w0, #1
	str	w0, [x1, 28]
.L5141:
	mov	x0, x19
	bl	HEVC_DecOneNal
	cmn	w0, #2
	beq	.L5158
	cbnz	w0, .L5210
	ldr	w0, [x19, 2348]
	str	wzr, [x19, 4904]
	cmp	w0, 1
	bne	.L5153
	mov	x0, x19
	bl	HEVCDEC_SetDecParam
	b	.L5198
	.p2align 3
.L5204:
	ldr	x1, .LC1298
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L5198
	.p2align 3
.L5207:
	ldp	w25, w22, [x0, 152]
	ldr	w3, [x0, 160]
	mov	x0, x19
	mov	w2, w22
	mov	w1, w25
	bl	HEVC_VES_Splitter
	cmp	w0, 2
	beq	.L5132
	cmp	w0, 1
	mov	w21, 0
	beq	.L5132
.L5158:
	mov	w20, w0
	b	.L5198
.L5209:
	add	x2, x29, 108
	add	x1, x29, 104
	mov	x0, x19
	bl	HEVC_InquireSliceProperty
	cbnz	w0, .L5138
	ldr	w21, [x29, 104]
	cmp	w21, 1
	beq	.L5211
.L5139:
	ldr	w21, [x29, 108]
	cmp	w21, 1
	bne	.L5141
	ldr	x0, [x19, 2976]
	ldr	w0, [x0, 24]
	add	x0, x19, x0
	ldrb	w22, [x0, 4]
	mov	x0, x19
	cmp	w22, 1
	beq	.L5212
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L5213
.L5144:
	ldr	w0, [x19, 276]
	bl	FSP_GetFspType
	cbnz	w0, .L5141
	ldr	w0, [x19, 276]
	add	x3, x29, 100
	add	x2, x29, 96
	add	x1, x29, 92
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 3032]
	ldr	w0, [x0, 764]
	cmp	w0, 1
	bne	.L5141
	ldr	w1, [x29, 100]
	cmp	w1, wzr
	bgt	.L5147
	ldr	w2, [x29, 96]
	cmp	w2, 32
	bgt	.L5147
	ldr	x2, [x19, 3048]
	cbnz	x2, .L5147
	ldr	w2, [x29, 108]
	cbz	w2, .L5141
	ldr	w3, [x19, 264]
	cbz	w3, .L5141
	ldr	x3, [x19, 3000]
	ldr	w4, [x19, 336]
	ldr	w6, [x3, 68]
	cmp	w6, w4
	beq	.L5141
	ldr	w5, [x3, 64]
	cmp	w1, wzr
	ldr	w3, [x19, 340]
	ccmp	w5, w3, 4, eq
	beq	.L5141
	ldr	x1, .LC1311
	bl	dprint_vfmw
	ldr	x0, [x19, 3000]
	ldr	x1, .LC1312
	ldr	w2, [x0, 68]
	str	w2, [x19, 336]
	ldr	x4, [x1]
	ldr	w0, [x0, 64]
	str	w0, [x19, 340]
	cbz	x4, .L5141
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L5141
	.p2align 3
.L5208:
	ldr	x1, .LC1305
	mov	w0, 1
	bl	dprint_vfmw
	b	.L5201
.L5203:
	ldr	x1, .LC1296
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L5198
.L5138:
	ldr	x1, .LC1314
	mov	w0, w26
	bl	dprint_vfmw
	ldr	x1, [x19, 2976]
	cbz	x1, .L5149
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2976]
.L5149:
	ldr	x0, .LC1312
	ldr	x4, [x0]
	cbz	x4, .L5150
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L5150:
	ldrsw	x0, [x19, 276]
	ldr	x0, [x23, x0, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	bne	.L5134
	ldr	w1, [x0, 156]
	cbnz	w1, .L5134
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L5134
	add	x0, x19, 12288
	ldrb	w1, [x0, 448]
	cbnz	w1, .L5134
	ldr	x3, .LC1315
	mov	x2, 56
	add	x0, x0, 448
	mov	w20, -1
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 4228]
	str	xzr, [x19, 4248]
	str	xzr, [x19, 4256]
	str	xzr, [x19, 4264]
	str	xzr, [x19, 4272]
	b	.L5198
.L5211:
	ldr	w1, [x19, 204]
	cbnz	w1, .L5140
	add	x1, x19, 4096
	ldrb	w1, [x1, 753]
	cbz	w1, .L5139
	ldr	x2, .LC1306
	ldr	x1, .LC1307
	add	x2, x2, 544
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L5139
.L5140:
	ldr	x3, [x19, 2976]
	mov	w2, 13
	ldr	x1, .LC1306
	add	x0, x19, 3328
	mov	w20, -2
	str	wzr, [x3, 4]
	add	x1, x1, 632
	bl	BsInit
	ldr	x0, [x19, 2936]
	mov	w1, 40
	bl	BsSkip
	ldr	x1, [x19, 2976]
	mov	w2, 48
	mov	x0, x19
	str	w2, [x1, 16]
	strb	w21, [x19, 10]
	bl	HEVC_DecOneNal
	strb	w21, [x19, 9]
	ldr	w0, [x19, 304]
	add	w0, w0, 1
	str	w0, [x19, 304]
	b	.L5198
.L5210:
	ldr	x1, .LC1317
	mov	w0, 22
	mov	w20, -1
	bl	dprint_vfmw
	b	.L5198
.L5212:
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L5144
	ldr	x2, .LC1306
	mov	w0, w22
	ldr	x1, .LC1308
	add	x2, x2, 608
	bl	dprint_vfmw
	b	.L5144
.L5213:
	ldr	x2, .LC1306
	mov	w0, w21
	ldr	x1, .LC1309
	add	x2, x2, 608
	bl	dprint_vfmw
	b	.L5144
.L5147:
	mov	w0, 1
	mov	w20, -2
	strb	w0, [x19, 9]
	b	.L5198
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	3
.LC1296:
	.xword	.LC1295
	.align	3
.LC1298:
	.xword	.LC1297
	.align	3
.LC1300:
	.xword	.LC1299
	.align	3
.LC1301:
	.xword	s_pstVfmwChan
	.align	3
.LC1303:
	.xword	.LC1302
	.align	3
.LC1305:
	.xword	.LC1304
	.align	3
.LC1306:
	.xword	.LANCHOR5
	.align	3
.LC1307:
	.xword	.LC1274
	.align	3
.LC1308:
	.xword	.LC1234
	.align	3
.LC1309:
	.xword	.LC1232
	.align	3
.LC1311:
	.xword	.LC1310
	.align	3
.LC1312:
	.xword	g_event_report
	.align	3
.LC1314:
	.xword	.LC1313
	.align	3
.LC1315:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1317:
	.xword	.LC1316
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w24, w1
	mov	x22, x3
	mov	w23, w4
	mov	w20, w5
	bl	_mcount
	ldr	x0, [x19, 3032]
	ldr	x2, [x19, 4912]
	ldr	w21, [x0, 676]
	str	w24, [x19, 4888]
	cbz	x2, .L5215
	add	x0, x19, 4096
	ldrb	w1, [x0, 3445]
	strb	w1, [x2, 3]
	ldrb	w0, [x0, 3440]
	strb	w0, [x2, 4]
	ldr	x0, [x19, 3032]
.L5215:
	ldr	w1, [x19, 2376]
	cmp	w1, 1
	bls	.L5216
.L5219:
	ldr	w1, [x19, 4868]
	cmp	w1, 1920
	bls	.L5217
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L5217
	str	wzr, [x19, 2348]
	cbz	w23, .L5222
.L5252:
	ldr	x5, .LC1318
	sbfiz	x20, x20, 6, 32
	add	x20, x5, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L5249
	cmp	w0, 1
	beq	.L5222
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbnz	w0, .L5250
.L5226:
	cmp	w21, 1
	beq	.L5251
.L5227:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x19, 172]
.L5224:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5216:
	add	w1, w1, 1
	str	w1, [x19, 2376]
	cmp	w1, 1
	bhi	.L5219
.L5217:
	ldr	w0, [x0, 672]
	str	w0, [x19, 2348]
	cbnz	w23, .L5252
.L5222:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbz	w0, .L5226
.L5250:
	ldr	x1, .LC1320
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5251:
	ldr	x22, [x19, 3048]
	ldr	w0, [x22, 1292]
	add	x0, x22, x0, lsl 2
	ldr	w23, [x0, 1476]
	mov	w0, w23
	bl	MEM_Phy2Vir
	mov	x20, x0
	ldr	w2, [x22, 76]
	ldp	w3, w5, [x22, 192]
	lsl	w21, w21, w2
	ldr	x1, .LC1321
	sub	w3, w3, #1
	sub	w5, w5, #1
	add	w5, w5, w21
	add	w21, w3, w21
	lsr	w5, w5, w2
	lsr	w21, w21, w2
	ldr	x3, [x1, 280]
	mov	w1, w23
	mul	w21, w5, w21
	lsl	w2, w21, 4
	blr	x3
	cbz	w21, .L5238
	mov	w5, 0
	mov	w8, 0
	mov	w7, 2147483647
	mov	w4, 0
	mov	w2, 0
	b	.L5235
	.p2align 3
.L5254:
	csel	w7, w7, w0, le
.L5234:
	add	w2, w2, 1
	add	w5, w5, w0
	cmp	w21, w2
	beq	.L5253
.L5235:
	ubfiz	x1, x2, 4, 28
	add	x1, x20, x1
	ldrsh	w3, [x1, 4]
	neg	w0, w3
	and	w6, w3, 32767
	tbz	x3, 15, .L5230
	and	w6, w0, 32767
.L5230:
	ldrsh	w1, [x1, 6]
	neg	w3, w1
	and	w0, w1, 32767
	tbz	x1, 15, .L5232
	and	w0, w3, 32767
.L5232:
	add	w0, w6, w0
	cmp	w4, w0
	csel	w4, w4, w0, ge
	cmp	w7, w0
	cbnz	w0, .L5254
	add	w8, w8, 1
	b	.L5234
	.p2align 3
.L5249:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	w0, 0
	b	.L5224
	.p2align 3
.L5253:
	lsl	w0, w8, 2
	sub	w0, w0, w8
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w8, w0, w8
.L5228:
	udiv	w8, w8, w21
	ldr	x0, [x19, 4912]
	cmp	w8, 100
	csel	w7, w7, wzr, ne
	udiv	w5, w5, w21
	cbz	x0, .L5237
	str	w4, [x0, 332]
	ldr	x0, [x19, 4912]
	str	w7, [x0, 336]
	ldr	x0, [x19, 4912]
	str	w5, [x0, 340]
	ldr	x0, [x19, 4912]
	str	w8, [x0, 344]
	str	w4, [x19, 5164]
	str	w7, [x19, 5168]
	str	w5, [x19, 5172]
	str	w8, [x19, 5176]
	b	.L5227
.L5238:
	mov	w8, 0
	mov	w5, 0
	mov	w7, 2147483647
	mov	w4, 0
	b	.L5228
.L5237:
	ldr	x1, .LC1323
	mov	w0, 0
	bl	dprint_vfmw
	b	.L5227
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	3
.LC1318:
	.xword	g_VdmDrvParam
	.align	3
.LC1320:
	.xword	.LC1319
	.align	3
.LC1321:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1323:
	.xword	.LC1322
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3000]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w2, [x0, 132]
	ldr	w0, [x0, 64]
	add	w1, w2, w0
	neg	w2, w2
	sub	w0, w1, #1
	and	w0, w0, w2
	ret
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3000]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w2, [x0, 132]
	ldr	w0, [x0, 68]
	add	w1, w2, w0
	neg	w2, w2
	sub	w0, w1, #1
	and	w0, w0, w2
	ret
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3372]
	cbz	w0, .L5262
	ldr	x0, .LC1324
	mov	w21, 1
	ldr	x23, .LC1325
	add	x22, x0, 648
	.p2align 2
.L5258:
	add	x2, x29, 72
	add	x1, x29, 76
	mov	x0, x19
	bl	HEVC_GetMinPOC
	ldr	w2, [x29, 72]
	mov	x0, x19
	add	x1, x19, x2, uxtw 3
	ldr	x20, [x1, 3680]
	mov	x1, x20
	cbz	x20, .L5259
	ldrb	w3, [x20, 2]
	cmp	w3, 1
	beq	.L5259
	strb	w21, [x20, 2]
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L5273
.L5272:
	ldr	w2, [x29, 72]
.L5259:
	mov	w1, w2
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	ldr	w1, [x29, 72]
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w0, [x19, 3372]
	cbnz	w0, .L5258
.L5262:
	add	x0, x19, 4096
	add	x0, x0, 2832
	bl	GetVoLastImageID
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5273:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_OutputFrame
	cbz	w0, .L5272
	mov	x1, x23
	mov	x2, x22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	b	.L5272
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	3
.LC1324:
	.xword	.LANCHOR5
	.align	3
.LC1325:
	.xword	.LC1090
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	s_TmpParam
	.global	g_RpuStartCode
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.14040, %object
	.size	__func__.14040, 17
__func__.14040:
	.string	"HEVC_OutputFrame"
	.zero	7
	.type	__func__.12506, %object
	.size	__func__.12506, 26
__func__.12506:
	.string	"HEVC_OutputImgToViewQueue"
	.zero	6
	.type	__func__.11930, %object
	.size	__func__.11930, 24
__func__.11930:
	.string	"HEVC_CheckVpsExtOverlap"
	.type	__func__.11935, %object
	.size	__func__.11935, 24
__func__.11935:
	.string	"HEVC_CheckPpsExtOverlap"
	.type	__func__.11940, %object
	.size	__func__.11940, 26
__func__.11940:
	.string	"HEVC_CheckSliceExtOverlap"
	.zero	6
	.type	SarTable.12701, %object
	.size	SarTable.12701, 136
SarTable.12701:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.12859, %object
	.size	__func__.12859, 18
__func__.12859:
	.string	"HEVC_CalcTileInfo"
	.zero	6
	.type	__func__.13327, %object
	.size	__func__.13327, 27
__func__.13327:
	.string	"HEVC_GetUnRefPicWithMinPoc"
	.zero	5
	.type	__func__.13336, %object
	.size	__func__.13336, 21
__func__.13336:
	.string	"HEVC_IncreaseDPBSize"
	.zero	3
	.type	__func__.13588, %object
	.size	__func__.13588, 17
__func__.13588:
	.string	"HEVC_WritePicMsg"
	.zero	7
	.type	__func__.13617, %object
	.size	__func__.13617, 16
__func__.13617:
	.string	"HEVC_CheckListX"
	.type	__func__.13781, %object
	.size	__func__.13781, 16
__func__.13781:
	.string	"HEVC_RepairList"
	.type	__func__.13868, %object
	.size	__func__.13868, 16
__func__.13868:
	.string	"HEVC_ArrangeMem"
	.type	__func__.13941, %object
	.size	__func__.13941, 20
__func__.13941:
	.string	"HEVC_RemoveApcStore"
	.zero	4
	.type	__func__.14210, %object
	.size	__func__.14210, 21
__func__.14210:
	.string	"HEVC_CheckFrameStore"
	.zero	3
	.type	__func__.14278, %object
	.size	__func__.14278, 19
__func__.14278:
	.string	"HEVC_GetSLHDR1Info"
	.zero	5
	.type	__func__.14405, %object
	.size	__func__.14405, 14
__func__.14405:
	.string	"HEVC_IsNewPic"
	.zero	2
	.type	g_Quant8InterDefault, %object
	.size	g_Quant8InterDefault, 64
g_Quant8InterDefault:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	g_QuantTsDefault, %object
	.size	g_QuantTsDefault, 16
g_QuantTsDefault:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.align	3
.LANCHOR5 = . + 0
	.type	__func__.14720, %object
	.size	__func__.14720, 16
__func__.14720:
	.string	"HEVC_ReleaseNAL"
	.type	__func__.13900, %object
	.size	__func__.13900, 20
__func__.13900:
	.string	"HEVC_InitDecBuffers"
	.zero	4
	.type	__func__.12354, %object
	.size	__func__.12354, 23
__func__.12354:
	.string	"HEVC_ParseVPSExtension"
	.zero	1
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.13441, %object
	.size	__func__.13441, 27
__func__.13441:
	.string	"HEVC_DecSliceSegmentHeader"
	.zero	5
	.type	__func__.13879, %object
	.size	__func__.13879, 13
__func__.13879:
	.string	"HEVC_InitDPB"
	.zero	3
	.type	__func__.12563, %object
	.size	__func__.12563, 20
__func__.12563:
	.string	"HEVC_ArrangeShvcMem"
	.zero	4
	.type	__func__.14047, %object
	.size	__func__.14047, 19
__func__.14047:
	.string	"HEVC_OutputCurrPic"
	.zero	5
	.type	__func__.14052, %object
	.size	__func__.14052, 23
__func__.14052:
	.string	"HEVC_FirstFrameFastOut"
	.zero	1
	.type	__func__.14202, %object
	.size	__func__.14202, 19
__func__.14202:
	.string	"HEVC_OutputFrmToVO"
	.zero	5
	.type	__func__.14164, %object
	.size	__func__.14164, 22
__func__.14164:
	.string	"HEVC_OutputFrmFromDPB"
	.zero	2
	.type	__func__.13342, %object
	.size	__func__.13342, 30
__func__.13342:
	.string	"HEVC_OutputUnRefPicWithMinPoc"
	.zero	2
	.type	__func__.14177, %object
	.size	__func__.14177, 27
__func__.14177:
	.string	"HEVC_FlushOutputFrmFromDPB"
	.zero	5
	.type	__func__.14783, %object
	.size	__func__.14783, 14
__func__.14783:
	.string	"HEVC_ClearDPB"
	.zero	2
	.type	__func__.13347, %object
	.size	__func__.13347, 23
__func__.13347:
	.string	"HEVC_RecoverDPBProcess"
	.zero	1
	.type	__func__.14138, %object
	.size	__func__.14138, 20
__func__.14138:
	.string	"HEVC_InsertFrmInDPB"
	.zero	4
	.type	__func__.14057, %object
	.size	__func__.14057, 22
__func__.14057:
	.string	"HEVC_SimpleDPBProcess"
	.zero	2
	.type	__func__.14062, %object
	.size	__func__.14062, 21
__func__.14062:
	.string	"HEVC_DecOrderProcess"
	.zero	3
	.type	__func__.14067, %object
	.size	__func__.14067, 22
__func__.14067:
	.string	"HEVC_DispOrderProcess"
	.zero	2
	.type	__func__.14081, %object
	.size	__func__.14081, 19
__func__.14081:
	.string	"HEVC_StorePicInDPB"
	.zero	5
	.type	__func__.13703, %object
	.size	__func__.13703, 12
__func__.13703:
	.string	"HEVC_DecVDM"
	.zero	4
	.type	__func__.12589, %object
	.size	__func__.12589, 18
__func__.12589:
	.string	"HEVC_VES_Splitter"
	.zero	6
	.type	__func__.13378, %object
	.size	__func__.13378, 14
__func__.13378:
	.string	"HEVC_DecSlice"
	.zero	2
	.type	__func__.14865, %object
	.size	__func__.14865, 20
__func__.14865:
	.string	"HEVC_HaveSliceToDec"
	.zero	4
	.type	__func__.14911, %object
	.size	__func__.14911, 13
__func__.14911:
	.string	"HEVCDEC_Init"
	.zero	3
	.type	__func__.14925, %object
	.size	__func__.14925, 23
__func__.14925:
	.string	"HEVCDEC_GetImageBuffer"
	.zero	1
	.type	__func__.14940, %object
	.size	__func__.14940, 21
__func__.14940:
	.string	"HEVCDEC_DecodePacket"
	.zero	3
	.type	g_HevcNalTypeEOP, %object
	.size	g_HevcNalTypeEOP, 13
g_HevcNalTypeEOP:
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.zero	3
	.type	__func__.14989, %object
	.size	__func__.14989, 21
__func__.14989:
	.string	"HEVCDEC_GetRemainImg"
	.data
	.align	3
.LANCHOR4 = . + 0
	.type	g_Quant8IntraDefault, %object
	.size	g_Quant8IntraDefault, 64
g_Quant8IntraDefault:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_QuantTSDefault4x4, %object
	.size	g_QuantTSDefault4x4, 16
g_QuantTSDefault4x4:
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
	.type	g_QuantInterDefault8x8, %object
	.size	g_QuantInterDefault8x8, 64
g_QuantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_QuantIntraDefault8x8, %object
	.size	g_QuantIntraDefault8x8, 64
g_QuantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.type	g_RpuStartCode, %object
	.size	g_RpuStartCode, 5
g_RpuStartCode:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	25
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"../../core/syntax/hevc.c" )
	.zero	7
.LC4:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC6:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%d, logic_fs=%p, dec_fs=%p)\n" )
	.zero	1
.LC9:
	ASCII(.string	"%s: pImg is NULL!\n" )
	.zero	5
.LC11:
	ASCII(.string	"View %d image queue is full, discard head image %d.\n" )
	.zero	3
.LC13:
	ASCII(.string	"%s: view0 frame poc(%d) > view1 frame poc(%d)\n" )
	.zero	1
.LC15:
	ASCII(.string	"%s: view1 frame poc(%d) > view0 frame poc(%d)\n" )
	.zero	1
.LC17:
	ASCII(.string	"%s: Image(view=0, poc=%d) output failed!\n" )
	.zero	6
.LC19:
	ASCII(.string	"%s: Image(view=1, poc=%d) output failed!\n" )
	.zero	6
.LC21:
	ASCII(.string	"%s: InsertImgToVoQueue failed!\n" )
.LC25:
	ASCII(.string	"%s pVPSExt = NULL\n" )
	.zero	5
.LC28:
	ASCII(.string	"%s pPPSExt = NULL\n" )
	.zero	5
.LC31:
	ASCII(.string	"%s pSlcExt = NULL\n" )
	.zero	5
.LC40:
	ASCII(.string	"dar=%d\n" )
.LC43:
	ASCII(.string	"--------------- PrintNaluArraySlot START ---------------\n" )
	.zero	6
.LC45:
	ASCII(.string	"\n" )
	.zero	6
.LC47:
	ASCII(.string	"--------------- PrintNaluArraySlot END ---------------\n" )
.LC49:
	ASCII(.string	"NalArray[%d]=%p,is_valid=%d   " )
	.zero	1
.LC51:
	ASCII(.string	"--------------- PrintCurrSlicelistX START ---------------\n" )
	.zero	5
.LC53:
	ASCII(.string	"List0, size: %d\n" )
	.zero	7
.LC55:
	ASCII(.string	"List1, size: %d\n" )
	.zero	7
.LC57:
	ASCII(.string	"pListX[0][%d]:%p " )
	.zero	6
.LC59:
	ASCII(.string	"pFrameStore:%p " )
.LC61:
	ASCII(.string	"pLogicFs:%p " )
	.zero	3
.LC64:
	ASCII(.string	"--------------- PrintCurrSlicelistX END ---------------\n" )
	.zero	7
.LC66:
	ASCII(.string	"pListX[1][%d]: %p" )
	.zero	6
.LC70:
	ASCII(.string	"--------------- PrintFrameStoreState START ---------------\n" )
	.zero	4
.LC72:
	ASCII(.string	"--------------- PrintFrameStoreState END ---------------\n" )
	.zero	6
.LC74:
	ASCII(.string	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displayed=%d " )
	.zero	5
.LC76:
	ASCII(.string	"p_usrdat[%d]=%p " )
	.zero	7
.LC79:
	ASCII(.string	"--------------- PrintAPCState START ---------------\n" )
	.zero	3
.LC81:
	ASCII(.string	"Layer %d: APC.used_size:%d, APC.size:%d\n" )
	.zero	7
.LC83:
	ASCII(.string	"%d: is_used=%d, idc=%d, poc=%d\n" )
.LC85:
	ASCII(.string	"--------------- PrintAPCState END ---------------\n" )
	.zero	5
.LC87:
	ASCII(.string	"--------------- PrintDPBState START ---------------\n" )
	.zero	3
.LC89:
	ASCII(.string	"DPB: size:%d, used_size:%d, negative:%d, positive:%d, longterm:%d\n" )
	.zero	5
.LC92:
	ASCII(.string	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d fsp_disp:%d logic_id:%d img_id:%d\n" )
.LC94:
	ASCII(.string	"--------------- PrintDPBState END ---------------\n" )
	.zero	5
.LC96:
	ASCII(.string	"fs[%d]\t" )
.LC98:
	ASCII(.string	"LogicFs:%p\t" )
	.zero	4
.LC100:
	ASCII(.string	"LogicTick:%d\t" )
	.zero	2
.LC102:
	ASCII(.string	"IsRef:%d\t" )
	.zero	6
.LC104:
	ASCII(.string	"DispState:%d\t" )
	.zero	2
.LC106:
	ASCII(.string	"LogicFs:Null\t" )
	.zero	2
.LC108:
	ASCII(.string	"DecFs:%p\t" )
	.zero	6
.LC110:
	ASCII(.string	"DecTick:%d\t" )
	.zero	4
.LC112:
	ASCII(.string	"DecFs:Null\t" )
	.zero	4
.LC114:
	ASCII(.string	"DispFs:%p\t" )
	.zero	5
.LC116:
	ASCII(.string	"DispTick:%d\t" )
	.zero	3
.LC118:
	ASCII(.string	"DispFs:Null\t" )
	.zero	3
.LC121:
	ASCII(.string	"%s num_tile_columns(%d) out of range(0, %d].\n" )
	.zero	2
.LC123:
	ASCII(.string	"%s num_tile_rows(%d) out of range(0, %d].\n" )
	.zero	5
.LC126:
	ASCII(.string	"%s 0 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC128:
	ASCII(.string	"%s 1 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC131:
	ASCII(.string	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\n" )
	.zero	6
.LC133:
	ASCII(.string	"pListX[0][%d] = NULL, listXsize[0] = %d\n" )
	.zero	7
.LC135:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %d\n" )
	.zero	2
.LC137:
	ASCII(.string	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) invalid\n" )
	.zero	1
.LC139:
	ASCII(.string	"pListX[1][%d] = NULL, listXsize[1] = %d\n" )
	.zero	7
.LC141:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %d\n" )
	.zero	2
.LC143:
	ASCII(.string	"pListX[i][%d] pstLogicFs(%p) invalid\n" )
	.zero	2
.LC146:
	ASCII(.string	"%s can't find such pic.\n" )
	.zero	7
.LC148:
	ASCII(.string	"%s DPB.used_size(%d) >= 17.\n" )
	.zero	3
.LC150:
	ASCII(.string	"%s find pos=%d, poc=%d.\n" )
	.zero	7
.LC153:
	ASCII(.string	"%s DPB.size(%d) already reached max(%d).\n" )
	.zero	6
.LC155:
	ASCII(.string	"%s increase DPB size to %d\n" )
	.zero	4
.LC157:
	ASCII(.string	"%s no enough fs(total_fs_num=%d) to increase DPB size.\n" )
.LC159:
	ASCII(.string	"TileWidthInCtb is 0\n" )
	.zero	3
.LC165:
	ASCII(.string	"image_id=%d, pmv_idc=%d\n" )
	.zero	7
.LC167:
	ASCII(.string	"pic msg burst0:\n" )
	.zero	7
.LC171:
	ASCII(.string	"%s call HEVC_CalcTileInfo failed.\n" )
	.zero	5
.LC173:
	ASCII(.string	"logic frame id(=%d): get LogicFs error!\n" )
	.zero	7
.LC175:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC178:
	ASCII(.string	"%s ERROR: bHaveIndependentSlice = 0\n\n" )
	.zero	2
.LC180:
	ASCII(.string	"ListX ERROR: list0size >= %d\n" )
	.zero	2
.LC182:
	ASCII(.string	"ListX ERROR: list1size >= %d\n" )
	.zero	2
.LC184:
	ASCII(.string	"pListX[0][%d] = NULL\n" )
	.zero	2
.LC186:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL\n" )
	.zero	5
.LC188:
	ASCII(.string	"pListX[1][%d] = NULL\n" )
	.zero	2
.LC190:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL\n" )
	.zero	5
.LC192:
	ASCII(.string	"NumSlicePara(%d) >= MaxSliceNum(%d)\n" )
	.zero	3
.LC195:
	ASCII(.string	"width is larger than 3! (%d, %d)\n" )
	.zero	6
.LC197:
	ASCII(.string	"height is larger than 3! (%d, %d)\n" )
	.zero	5
.LC199:
	ASCII(.string	"line:%d pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC201:
	ASCII(.string	"line:%d seq_parameter_set_id(%d) out of range[0,%d].\n" )
	.zero	2
.LC203:
	ASCII(.string	"line:%d, i(%d) > Max(%d) num_of_pics %d\n" )
	.zero	7
.LC205:
	ASCII(.string	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\n" )
	.zero	7
.LC214:
	ASCII(.string	"%s unkown slice type(%d).\n" )
	.zero	5
.LC216:
	ASCII(.string	"%s pListX[%d] no available pic to repair.\n" )
	.zero	5
.LC218:
	ASCII(.string	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\n" )
	.zero	4
.LC222:
	ASCII(.string	"HEVC_InitListX error.\n" )
	.zero	1
.LC224:
	ASCII(.string	"HEVC_RepairList error.\n" )
.LC228:
	ASCII(.string	"%s image size abnormal(%dx%d)\n" )
	.zero	1
.LC230:
	ASCII(.string	"%s HEVC FSP_ConfigInstance failed!\n" )
	.zero	4
.LC233:
	ASCII(.string	"%s fs[%d]->view_id = %d invalid.\n" )
	.zero	6
.LC237:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC240:
	ASCII(.string	"Cant find free apc slot.\n" )
	.zero	6
.LC243:
	ASCII(.string	"%s frame logic_fs_id=%d, state=%d\n" )
	.zero	5
.LC245:
	ASCII(.string	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null, logic_fs_id = %d\n" )
	.zero	2
.LC247:
	ASCII(.string	"%s frame poc=%d, is already output\n" )
	.zero	4
.LC249:
	ASCII(.string	"%s frame(%p) invalid, state:%d, non_existing:%d\n" )
	.zero	7
.LC251:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC254:
	ASCII(.string	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STATE_NOT_USED\n" )
.LC256:
	ASCII(.string	"%-5d   specVersion\n" )
	.zero	4
.LC258:
	ASCII(.string	"%-5d   payloadMode\n" )
	.zero	4
.LC260:
	ASCII(.string	"%-5d   hdrPicColourSpace\n" )
	.zero	6
.LC262:
	ASCII(.string	"%-5d   hdrMasterDisplayColourSpace\n" )
	.zero	4
.LC264:
	ASCII(.string	"%-5d   hdrMasterDisplayMaxLuminance\n" )
	.zero	3
.LC266:
	ASCII(.string	"%-5d   hdrMasterDisplayMinLuminance\n" )
	.zero	3
.LC268:
	ASCII(.string	"%-5d   sdrPicColourSpace\n" )
	.zero	6
.LC270:
	ASCII(.string	"%-5d   sdrMasterDisplayColourSpace\n" )
	.zero	4
.LC272:
	ASCII(.string	"%-5d   tmInputSignalBlackLevelOffset\n" )
	.zero	2
.LC274:
	ASCII(.string	"%-5d   tmInputSignalWhiteLevelOffset\n" )
	.zero	2
.LC276:
	ASCII(.string	"%-5d   shadowGain\n" )
	.zero	5
.LC278:
	ASCII(.string	"%-5d   highlightGain\n" )
	.zero	2
.LC280:
	ASCII(.string	"%-5d   midToneWidthAdjFactor\n" )
	.zero	2
.LC282:
	ASCII(.string	"%-5d   tmOutputFineTuningNumVal\n" )
	.zero	7
.LC284:
	ASCII(.string	"%-5d   saturationGainNumVal\n" )
	.zero	3
.LC286:
	ASCII(.string	"%-5d   tmOutputFineTuningX[%d]\n" )
.LC288:
	ASCII(.string	"%-5d   tmOutputFineTuningY[%d]\n" )
.LC290:
	ASCII(.string	"%-5d   saturationGainX[%d]\n" )
	.zero	4
.LC292:
	ASCII(.string	"%-5d   saturationGainY[%d]\n" )
	.zero	4
.LC294:
	ASCII(.string	"%-5d   luminanceMappingNumVal\n" )
	.zero	1
.LC296:
	ASCII(.string	"%-5d   colourCorrectionNumVal\n" )
	.zero	1
.LC298:
	ASCII(.string	"%-5d   luminanceMappingX[%d]\n" )
	.zero	2
.LC300:
	ASCII(.string	"%-5d   luminanceMappingY[%d]\n" )
	.zero	2
.LC302:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuA\n" )
	.zero	7
.LC304:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuB\n" )
	.zero	7
.LC306:
	ASCII(.string	"%-5d   colourCorrectionX[%d]\n" )
	.zero	2
.LC308:
	ASCII(.string	"%-5d   colourCorrectionY[%d]\n" )
	.zero	2
.LC310:
	ASCII(.string	"======SL_HDR1_METADATA= %d=======\n" )
	.zero	5
.LC313:
	ASCII(.string	"%s, [%d %d %d %d %d]\n" )
	.zero	2
.LC315:
	ASCII(.string	"%s HDR_Metadata_phy_addr is invalid!!\n" )
	.zero	1
.LC318:
	ASCII(.string	"FS_ALLOC_ERR, ClearAll\n" )
.LC321:
	ASCII(.string	"Can not new logic fs! ClearAll\n" )
.LC323:
	ASCII(.string	"FSP_GetFspType -1\n" )
	.zero	5
.LC325:
	ASCII(.string	"FSP_GetLogicFs return NULL\n" )
	.zero	4
.LC327:
	ASCII(.string	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), error resilence.\n" )
	.zero	6
.LC329:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC331:
	ASCII(.string	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC333:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC335:
	ASCII(.string	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC337:
	ASCII(.string	"sps with this seq_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC339:
	ASCII(.string	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of range\n" )
	.zero	7
.LC341:
	ASCII(.string	"vps with this video_parameter_set_id = %d havn't be decoded\n" )
	.zero	3
.LC344:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, nal_unit_type = %d, should skip this frame\n" )
	.zero	2
.LC346:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d, nal_unit_type = %d, should skip this frame\n" )
.LC348:
	ASCII(.string	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocCRA = %d, nal_unit_type = %d, should skip this frame\n" )
.LC350:
	ASCII(.string	"HEVC_ReadByteAlignment: code should not be zero.\n" )
	.zero	6
.LC352:
	ASCII(.string	"HEVC_ReadByteAlignment: code:%d\n" )
	.zero	7
.LC354:
	ASCII(.string	"reserved_zero_2bits not equal 0.\n" )
	.zero	6
.LC363:
	ASCII(.string	"HEVC_GetScalingListDefaultAddress NULL.\n" )
	.zero	7
.LC365:
	ASCII(.string	"Error, BsLen: 0x%x, TotalPos: 0x%x\n" )
	.zero	4
.LC367:
	ASCII(.string	"Panic: All zero data sequence in RBSP \n" )
.LC369:
	ASCII(.string	"nal_trail_zero_bit_num err\n" )
	.zero	4
.LC374:
	ASCII(.string	"%s release streambuff=%p, bitstream_length=%d\n" )
	.zero	1
.LC378:
	ASCII(.string	"%s DPB size exceed %d, force to %d\n" )
	.zero	4
.LC381:
	ASCII(.string	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\n" )
	.zero	6
.LC383:
	ASCII(.string	"END of the bit buffer, copy the first packet!\n" )
	.zero	1
.LC386:
	ASCII(.string	"tone_map_id" )
	.zero	4
.LC388:
	ASCII(.string	"Unsupport: target_bit_depth(%d) > 8\n" )
	.zero	3
.LC391:
	ASCII(.string	"pTon->num_pivots > 256\n" )
.LC393:
	ASCII(.string	"frame_packing_arrangement_id" )
	.zero	3
.LC395:
	ASCII(.string	"frame_packing_arrangement_type(%d) out of range\n" )
	.zero	7
.LC397:
	ASCII(.string	"decoding_unit_idx" )
	.zero	6
.LC399:
	ASCII(.string	"num_sps_ids_minus1" )
	.zero	5
.LC401:
	ASCII(.string	"pAct->num_sps_ids_minus1 > 15\n" )
	.zero	1
.LC403:
	ASCII(.string	"active_seq_parameter_set_id" )
	.zero	4
.LC405:
	ASCII(.string	"bp_seq_parameter_set_id" )
.LC407:
	ASCII(.string	"Wrong bp_seq_parameter_set_id = %d, should be 0 to 15!\n" )
.LC410:
	ASCII(.string	"num_decoding_units_minus1" )
	.zero	6
.LC412:
	ASCII(.string	"pPic->num_decoding_units_minus1 > 255\n" )
	.zero	1
.LC414:
	ASCII(.string	"num_nalus_in_du_minus1" )
	.zero	1
.LC416:
	ASCII(.string	"cv_rec_id" )
	.zero	6
.LC418:
	ASCII(.string	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize < 4!!\n" )
	.zero	5
.LC420:
	ASCII(.string	"delta_idx_minus1" )
	.zero	7
.LC422:
	ASCII(.string	"delta_idx(%d) > idx(%d).\n" )
	.zero	6
.LC424:
	ASCII(.string	"rIdx(%d) > (idx-1)(%d) or < 0).\n" )
	.zero	7
.LC426:
	ASCII(.string	"abs_delta_rps_minus1" )
	.zero	3
.LC428:
	ASCII(.string	"pTempRPset->num_of_pics(%d) out of range(0,15).\n" )
	.zero	7
.LC430:
	ASCII(.string	"num_of_pics out of range(0,15).\n" )
	.zero	7
.LC432:
	ASCII(.string	"num_negative_pics" )
	.zero	6
.LC434:
	ASCII(.string	"pTempRPset->num_negative_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC436:
	ASCII(.string	"num_positive_pics" )
	.zero	6
.LC438:
	ASCII(.string	"pTempRPset->num_positive_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC440:
	ASCII(.string	"pShortTermRpset->num_of_pics(%d) out of range[0,%d].\n" )
	.zero	2
.LC442:
	ASCII(.string	"delta_poc_s0_minus1" )
	.zero	4
.LC444:
	ASCII(.string	"delta_poc_s0_minus1(%d) out of range.\n" )
	.zero	1
.LC446:
	ASCII(.string	"delta_poc_s1_minus1" )
	.zero	4
.LC448:
	ASCII(.string	"elemental_duration_in_tc_minus1" )
.LC450:
	ASCII(.string	"cpb_cnt_minus1" )
	.zero	1
.LC452:
	ASCII(.string	"cpb_cnt_minus1(%d) out of range(0,31).\n" )
.LC454:
	ASCII(.string	"bit_rate_value_minus1" )
	.zero	2
.LC456:
	ASCII(.string	"cpb_size_value_minus1" )
	.zero	2
.LC458:
	ASCII(.string	"cpb_size_du_value_minus1" )
	.zero	7
.LC460:
	ASCII(.string	"bit_rate_du_value_minus1" )
	.zero	7
.LC464:
	ASCII(.string	"%s: vps_max_layers_minus1 %d out of range[0,%d].\n" )
	.zero	6
.LC466:
	ASCII(.string	"num_add_layer_sets" )
	.zero	5
.LC468:
	ASCII(.string	"%s %d: num_add_layer_sets %d >= HEVC_MAX_VPS_OP_SETS_PLUS1 %d\n" )
	.zero	1
.LC470:
	ASCII(.string	"vps_num_profile_tier_level_minus1" )
	.zero	6
.LC472:
	ASCII(.string	"num_add_olss" )
	.zero	3
.LC474:
	ASCII(.string	"%s %d: num_output_layer_sets %d >= HEVC_MAX_VPS_OP_SETS_PLUS1 %d, num_add_olss %d, num_layer_sets %d\n" )
	.zero	2
.LC476:
	ASCII(.string	"vps_num_rep_formats_minus1" )
	.zero	5
.LC478:
	ASCII(.string	"vps_num_rep_formats_minus1 > 255.\n" )
	.zero	5
.LC480:
	ASCII(.string	"conf_win_vps_left_offset" )
	.zero	7
.LC482:
	ASCII(.string	"conf_win_vps_right_offset" )
	.zero	6
.LC484:
	ASCII(.string	"conf_win_vps_top_offset" )
.LC486:
	ASCII(.string	"conf_win_vps_bottom_offset" )
	.zero	5
.LC488:
	ASCII(.string	"bit_depth_vps_luma_minus8(%d) or bit_depth_vps_chroma_minus8(%d) out of range [0,8]\n" )
	.zero	3
.LC490:
	ASCII(.string	"direct_dep_type_len_minus2" )
	.zero	5
.LC492:
	ASCII(.string	"max_vps_num_reorder_pics" )
	.zero	7
.LC494:
	ASCII(.string	"max_vps_latency_increase_plus1" )
	.zero	1
.LC496:
	ASCII(.string	"max_vps_dec_pic_buffering_minus1" )
	.zero	7
.LC498:
	ASCII(.string	"vps_non_vui_extension_length" )
	.zero	3
.LC500:
	ASCII(.string	"min_spatial_segment_offset_plus1" )
	.zero	7
.LC502:
	ASCII(.string	"min_horizontal_ctu_offset_plus1" )
.LC504:
	ASCII(.string	"vps_num_add_hrd_params" )
	.zero	1
.LC506:
	ASCII(.string	"vps_num_hrd_params %d out of range [0,%d]\n" )
	.zero	5
.LC508:
	ASCII(.string	"num_sub_layer_hrd_minus1" )
	.zero	7
.LC510:
	ASCII(.string	"hrd %d num_sub_layer_hrd_minus1 %d out of range [0,%d]\n" )
.LC512:
	ASCII(.string	"num_signalled_partitioning_schemes" )
	.zero	5
.LC514:
	ASCII(.string	"OPL %d num_signalled_partitioning_schemes %d out of range [0,%d]\n" )
	.zero	6
.LC516:
	ASCII(.string	"num_partitions_in_scheme_minus1" )
.LC518:
	ASCII(.string	"num_bsp_schedules_minus1" )
	.zero	7
.LC520:
	ASCII(.string	"OPL %d Partition %d Tid %dnum_bsp_schedules_minus1 %d out of range [0,31]\n" )
	.zero	5
.LC522:
	ASCII(.string	"bsp_sched_idx" )
	.zero	2
.LC524:
	ASCII(.string	"HEVCC_ParseBspPartitonParameters failed.\n" )
	.zero	6
.LC526:
	ASCII(.string	"vps_base_layer_available_flag(%d) not equal 0x1.\n" )
	.zero	6
.LC528:
	ASCII(.string	"vps_max_layers_minus1 %d out of range[0,63].\n" )
	.zero	2
.LC530:
	ASCII(.string	"vps_max_sub_layers_minus1=%d\n" )
	.zero	2
.LC532:
	ASCII(.string	"vps_reserved_0xffff_16bits not equal 0xffff.\n" )
	.zero	2
.LC534:
	ASCII(.string	"VPS HEVC_DecPTL error.\n" )
.LC536:
	ASCII(.string	"vps_max_dec_pic_buffering_minus1[i]" )
	.zero	4
.LC538:
	ASCII(.string	"vps_num_reorder_pics[i]" )
.LC540:
	ASCII(.string	"vps_max_latency_increase_plus1[i]" )
	.zero	6
.LC542:
	ASCII(.string	"vps_max_layer_id out of range[0,%d].\n" )
	.zero	2
.LC544:
	ASCII(.string	"This is MV_HEVC!\n" )
	.zero	6
.LC546:
	ASCII(.string	"vps_num_layer_sets_minus1" )
	.zero	6
.LC548:
	ASCII(.string	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\n" )
	.zero	5
.LC551:
	ASCII(.string	"vps_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC553:
	ASCII(.string	"vps_num_hrd_parameters" )
	.zero	1
.LC555:
	ASCII(.string	"vps_num_hrd_parameters(%d) out of range[0,%d].\n" )
.LC557:
	ASCII(.string	"hrd_layer_set_idx" )
	.zero	6
.LC559:
	ASCII(.string	"VPS HEVC_DecHrdParam error.\n" )
	.zero	3
.LC561:
	ASCII(.string	"HEVC VPSExtension error.\n" )
	.zero	6
.LC563:
	ASCII(.string	"pVPS->vps_video_parameter_set_id out of range(0,15).\n" )
	.zero	2
.LC567:
	ASCII(.string	"VPS[%d] decode error0.\n" )
.LC569:
	ASCII(.string	"VPS[%d] decode error1.\n" )
.LC572:
	ASCII(.string	"chroma_sample_loc_type_top_field" )
	.zero	7
.LC574:
	ASCII(.string	"chroma_sample_loc_type_bottom_field" )
	.zero	4
.LC576:
	ASCII(.string	"def_disp_win_left_offset" )
	.zero	7
.LC578:
	ASCII(.string	"VUI pSps->chroma_format_idc out of range(0,3).\n" )
.LC580:
	ASCII(.string	"def_disp_win_right_offset" )
	.zero	6
.LC582:
	ASCII(.string	"def_disp_win_top_offset" )
.LC584:
	ASCII(.string	"def_disp_win_bottom_offset" )
	.zero	5
.LC587:
	ASCII(.string	"vui_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC589:
	ASCII(.string	"VUI HEVC_DecHrdParam error.\n" )
	.zero	3
.LC591:
	ASCII(.string	"min_spatial_segmentation_idc" )
	.zero	3
.LC593:
	ASCII(.string	"VUI min_spatial_segmentation_idc out of range(0,4095).\n" )
.LC595:
	ASCII(.string	"max_bytes_per_pic_denom" )
.LC597:
	ASCII(.string	"max_bits_per_min_cu_denom" )
	.zero	6
.LC599:
	ASCII(.string	"log2_max_mv_length_horizontal" )
	.zero	2
.LC601:
	ASCII(.string	"log2_max_mv_length_vertical" )
	.zero	4
.LC603:
	ASCII(.string	"sop_seq_parameter_set_id" )
	.zero	7
.LC605:
	ASCII(.string	"num_entries_in_sop_minus1" )
	.zero	6
.LC607:
	ASCII(.string	"num_entries_in_sop_minus1 out of range(0,1024)\n" )
.LC609:
	ASCII(.string	"sop_short_term_rps_idx" )
	.zero	1
.LC611:
	ASCII(.string	"sop_poc_delta" )
	.zero	2
.LC613:
	ASCII(.string	"recovery_poc_cnt" )
	.zero	7
.LC615:
	ASCII(.string	"colour_remap_id" )
.LC617:
	ASCII(.string	"colour_remap_coeffs" )
	.zero	4
.LC620:
	ASCII(.string	"reserved_payload_extension_data" )
.LC622:
	ASCII(.string	"line:%d Cosume TotalPos(%d > %d)!!!\n" )
	.zero	3
.LC624:
	ASCII(.string	"HEVC_SeiMessage HEVC_Sei_Payload error.\n" )
	.zero	7
.LC626:
	ASCII(.string	"SEI pSEISPS = NULL.\n" )
	.zero	3
.LC628:
	ASCII(.string	"SEI HEVC_SeiMessage error.\n" )
	.zero	4
.LC630:
	ASCII(.string	"SEI BsIsByteAligned error.\n" )
	.zero	4
.LC632:
	ASCII(.string	"SEI rbsp_trailing_bits(%d) not equal 0x80.\n" )
	.zero	4
.LC634:
	ASCII(.string	"nesting_num_ops_minus1" )
	.zero	1
.LC636:
	ASCII(.string	"nesting_num_ops_minus1 out of range(0,%d)\n" )
	.zero	5
.LC638:
	ASCII(.string	"nesting_op_idx" )
	.zero	1
.LC640:
	ASCII(.string	"nesting_num_layers_minus1" )
	.zero	6
.LC642:
	ASCII(.string	"nesting_num_layers_minus1 out of range(0,63)\n" )
	.zero	2
.LC647:
	ASCII(.string	"scaling_list_pred_matrix_id_delta" )
	.zero	6
.LC649:
	ASCII(.string	"scaling_list_pred_matrix_id_delta out of range(0,matrixId).\n" )
	.zero	3
.LC651:
	ASCII(.string	"HEVC_DecScalingListData pMatrixAddress NULL.\n" )
	.zero	2
.LC653:
	ASCII(.string	"scaling_list_dc_coef_minus8" )
	.zero	4
.LC655:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-7,247).\n" )
	.zero	5
.LC657:
	ASCII(.string	"scaling_list_delta_coef" )
.LC659:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-128,127).\n" )
	.zero	3
.LC662:
	ASCII(.string	"sps_rep_format_idx %d > HEVC_MAX_NUM_LAYERS %d\n" )
.LC664:
	ASCII(.string	"HEVC_DeriveSPSRepFormat failed.\n" )
	.zero	7
.LC666:
	ASCII(.string	"pSPS->chroma_format_idc out of range(0,3).\n" )
	.zero	4
.LC668:
	ASCII(.string	"pSPS->chroma_format_idc not equal(%d) 1.\n" )
	.zero	6
.LC670:
	ASCII(.string	"pic_width_in_luma_samples" )
	.zero	6
.LC672:
	ASCII(.string	"pic_width_in_luma_samples out of range(0,8192).\n" )
	.zero	7
.LC675:
	ASCII(.string	"pic_height_in_luma_samples" )
	.zero	5
.LC677:
	ASCII(.string	"pic_height_in_luma_samples out of range(0,4096).\n" )
	.zero	6
.LC679:
	ASCII(.string	"ERROR Unkown level: %d\n" )
.LC681:
	ASCII(.string	"conf_win_left_offset" )
	.zero	3
.LC684:
	ASCII(.string	"conf_win_right_offset" )
	.zero	2
.LC686:
	ASCII(.string	"conf_win_left_offset+conf_win_right_offset out of range.\n" )
	.zero	6
.LC688:
	ASCII(.string	"conf_win_top_offset" )
	.zero	4
.LC690:
	ASCII(.string	"conf_win_bottom_offset" )
	.zero	1
.LC692:
	ASCII(.string	"conf_win_top_offset+conf_win_bottom_offset out of range.\n" )
	.zero	6
.LC694:
	ASCII(.string	"bit_depth_luma_minus8" )
	.zero	2
.LC696:
	ASCII(.string	"bit_depth_luma(%d) out of range(8,10).\n" )
.LC698:
	ASCII(.string	"bit_depth_chroma_minus8" )
.LC700:
	ASCII(.string	"bit_depth_chroma(%d) out of range[8,14].\n" )
	.zero	6
.LC702:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4" )
	.zero	6
.LC704:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12].\n" )
	.zero	1
.LC706:
	ASCII(.string	"sps_max_dec_pic_buffering_minus1" )
	.zero	7
.LC708:
	ASCII(.string	"sps_num_reorder_pics" )
	.zero	3
.LC710:
	ASCII(.string	"sps_max_latency_increase_plus1" )
	.zero	1
.LC712:
	ASCII(.string	"log2_min_coding_block_size_minus3" )
	.zero	6
.LC714:
	ASCII(.string	"log2_min_luma_coding_block_size_minus3 out of range(0,3).\n" )
	.zero	5
.LC716:
	ASCII(.string	"log2_diff_max_min_coding_block_size" )
	.zero	4
.LC718:
	ASCII(.string	"log2_diff_max_min_luma_coding_block_size out of range(0,3).\n" )
	.zero	3
.LC720:
	ASCII(.string	"log2_ctb_sizeY out of range(4,6).\n" )
	.zero	5
.LC722:
	ASCII(.string	"log2_min_transform_block_size_minus2" )
	.zero	3
.LC724:
	ASCII(.string	"log2_min_transform_block_size_minus2 out of range(0,3).\n" )
	.zero	7
.LC726:
	ASCII(.string	"log2_diff_max_min_transform_block_size" )
	.zero	1
.LC728:
	ASCII(.string	"log2_diff_max_min_transform_block_size out of range(0,3).\n" )
	.zero	5
.LC730:
	ASCII(.string	"quadtree_tu_log2_min_size not less than log2_min_cb_sizeY.\n" )
	.zero	4
.LC732:
	ASCII(.string	"quadtree_tu_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC734:
	ASCII(.string	"max_transform_hierarchy_depth_inter" )
	.zero	4
.LC736:
	ASCII(.string	"max_transform_hierarchy_depth_inter out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC738:
	ASCII(.string	"max_transform_hierarchy_depth_intra" )
	.zero	4
.LC740:
	ASCII(.string	"max_transform_hierarchy_depth_intra out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC742:
	ASCII(.string	"SPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC744:
	ASCII(.string	"SPS sao is off and pic height(%d) is too small.(Logic Unsupported).\n" )
	.zero	3
.LC746:
	ASCII(.string	"log2_min_pcm_luma_coding_block_size_minus3" )
	.zero	5
.LC748:
	ASCII(.string	"log2_min_pcm_coding_block_size_minus3(%d) out of range[0,2].\n" )
	.zero	2
.LC750:
	ASCII(.string	"log2_diff_max_min_pcm_luma_coding_block_size" )
	.zero	3
.LC752:
	ASCII(.string	"log2_diff_max_min_pcm_coding_block_size(%d) out of range[0,2].\n" )
.LC754:
	ASCII(.string	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC756:
	ASCII(.string	"num_short_term_ref_pic_sets" )
	.zero	4
.LC758:
	ASCII(.string	"num_short_term_ref_pic_sets out of range[0,%d].\n" )
	.zero	7
.LC760:
	ASCII(.string	"SPS HEVC_DecShortTermRefPicSet error.\n" )
	.zero	1
.LC762:
	ASCII(.string	"num_long_term_ref_pic_sps" )
	.zero	6
.LC764:
	ASCII(.string	"num_long_term_ref_pic_sps out of range[0,32].\n" )
	.zero	1
.LC766:
	ASCII(.string	"SPS HEVC_DecVuiParam error.\n" )
	.zero	3
.LC768:
	ASCII(.string	"chroma_format_idc" )
	.zero	6
.LC771:
	ASCII(.string	"sps_video_parameter_set_id out of range(0,%d).\n" )
.LC773:
	ASCII(.string	"sps_max_sub_layers_minus1 out of range(0,%d).\n" )
	.zero	1
.LC775:
	ASCII(.string	"SPS HEVC_DecPTL error.\n" )
.LC777:
	ASCII(.string	"sps_seq_parameter_set_id" )
	.zero	7
.LC779:
	ASCII(.string	"sps_seq_parameter_set_id out of range(0,%d).\n" )
	.zero	2
.LC783:
	ASCII(.string	"SPS[%d] decode error0.\n" )
.LC785:
	ASCII(.string	"SPS[%d] decode error.\n" )
	.zero	1
.LC788:
	ASCII(.string	"pps_seq_parameter_set_id" )
	.zero	7
.LC790:
	ASCII(.string	"pic_parameter_set_id(%d) out of range[0,15].\n" )
	.zero	2
.LC792:
	ASCII(.string	"SPS(%d) haven't decode.\n" )
	.zero	7
.LC794:
	ASCII(.string	"num_ref_idx_l0_default_active_minus1" )
	.zero	3
.LC796:
	ASCII(.string	"num_ref_idx_l0_default_active out of range[0,15].\n" )
	.zero	5
.LC798:
	ASCII(.string	"num_ref_idx_l1_default_active_minus1" )
	.zero	3
.LC800:
	ASCII(.string	"num_ref_idx_l1_default_active out of range[0,15].\n" )
	.zero	5
.LC802:
	ASCII(.string	"init_qp_minus26" )
.LC804:
	ASCII(.string	"pic_init_qp(%d) out of range[-%d,51].\n" )
	.zero	1
.LC806:
	ASCII(.string	"diff_cu_qp_delta_depth" )
	.zero	1
.LC808:
	ASCII(.string	"diff_cu_qp_delta_depth out of range[0,3].\n" )
	.zero	5
.LC810:
	ASCII(.string	"pps_cb_qp_offset" )
	.zero	7
.LC812:
	ASCII(.string	"pic_cb_qp_offset out of range[-12,12].\n" )
.LC814:
	ASCII(.string	"pps_cr_qp_offset" )
	.zero	7
.LC816:
	ASCII(.string	"pic_cr_qp_offset out of range[-12,12].\n" )
.LC818:
	ASCII(.string	"num_tile_columns_minus1" )
.LC820:
	ASCII(.string	"num_tile_columns(%d) out of range(0,%d).\n" )
	.zero	6
.LC822:
	ASCII(.string	"num_tile_rows_minus1" )
	.zero	3
.LC824:
	ASCII(.string	"num_tile_rows out(%d) of range(0,%d).\n" )
	.zero	1
.LC826:
	ASCII(.string	"Logic limit(%d), num_tile_columns(%d) exceed.\n" )
	.zero	1
.LC829:
	ASCII(.string	"Logic limit(%d), num_tile_rows(%d) exceed.\n" )
	.zero	4
.LC831:
	ASCII(.string	"column_width_minus1" )
	.zero	4
.LC833:
	ASCII(.string	"column_width[%d](%d) out of range (0 %d)\n" )
	.zero	6
.LC835:
	ASCII(.string	"row_height_minus1" )
	.zero	6
.LC837:
	ASCII(.string	"row_height[%d](%d) out of range (0 %d)\n" )
.LC839:
	ASCII(.string	"column_bd[%d](%d) <= 0, invalid!\n" )
	.zero	6
.LC841:
	ASCII(.string	"row_bd[%d](%d) <= 0, invalid!\n" )
	.zero	1
.LC843:
	ASCII(.string	"PPS tile width(%d) is too small.(Logic Unsupport)\n" )
	.zero	5
.LC845:
	ASCII(.string	"PPS tile height(%d) is too small.(Logic Unsupport)\n" )
	.zero	4
.LC847:
	ASCII(.string	"pps_beta_offset_div2" )
	.zero	3
.LC849:
	ASCII(.string	"pps_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	2
.LC851:
	ASCII(.string	"pps_tc_offset_div2" )
	.zero	5
.LC853:
	ASCII(.string	"pps_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	4
.LC855:
	ASCII(.string	"PPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC857:
	ASCII(.string	"log2_parallel_merge_level_minus2" )
	.zero	7
.LC859:
	ASCII(.string	"log2_parallel_merge_level(%d) out of range(2,log2_ctb_sizeY).\n" )
	.zero	1
.LC861:
	ASCII(.string	"log2_max_transform_skip_block_size_minus2" )
	.zero	6
.LC863:
	ASCII(.string	"log2_sao_offset_scale_luma" )
	.zero	5
.LC865:
	ASCII(.string	"log2_sao_offset_scale_chroma" )
	.zero	3
.LC867:
	ASCII(.string	"diff_cu_chroma_qp_offset_depth" )
	.zero	1
.LC869:
	ASCII(.string	"chroma_qp_offset_list_len_minus1" )
	.zero	7
.LC871:
	ASCII(.string	"chroma_qp_offset_list_len_minus1 %d > 5\n" )
	.zero	7
.LC873:
	ASCII(.string	"cb_qp_offset_list" )
	.zero	6
.LC875:
	ASCII(.string	"cr_qp_offset_list" )
	.zero	6
.LC877:
	ASCII(.string	"pps_scaling_list_ref_layer_id %d > HEVC_MAX_NUM_LAYERS %d\n" )
	.zero	5
.LC879:
	ASCII(.string	"num_ref_loc_offsets" )
	.zero	4
.LC881:
	ASCII(.string	"num_ref_loc_offsets %d > HEVC_EXT_MAX_REF_LOC_OFFSET %d\n" )
	.zero	7
.LC883:
	ASCII(.string	"ref_loc_offset_layer_id %d > HEVC_EXT_MAX_REF_LOC_OFFSET %d\n" )
	.zero	3
.LC885:
	ASCII(.string	"scaled_ref_layer_left_offset" )
	.zero	3
.LC887:
	ASCII(.string	"scaled_ref_layer_top_offset" )
	.zero	4
.LC889:
	ASCII(.string	"scaled_ref_layer_right_offset" )
	.zero	2
.LC891:
	ASCII(.string	"scaled_ref_layer_bottom_offset" )
	.zero	1
.LC893:
	ASCII(.string	"ref_region_left_offset" )
	.zero	1
.LC895:
	ASCII(.string	"ref_region_top_offset" )
	.zero	2
.LC897:
	ASCII(.string	"ref_region_right_offset" )
.LC899:
	ASCII(.string	"ref_region_bottom_offset" )
	.zero	7
.LC901:
	ASCII(.string	"phase_hor_luma" )
	.zero	1
.LC903:
	ASCII(.string	"phase_ver_luma" )
	.zero	1
.LC905:
	ASCII(.string	"phase_hor_chroma_plus8" )
	.zero	1
.LC907:
	ASCII(.string	"phase_ver_chroma_plus8" )
	.zero	1
.LC909:
	ASCII(.string	"HEVC_ParsePPSExtension failed.\n" )
.LC911:
	ASCII(.string	"pps_pic_parameter_set_id" )
	.zero	7
.LC913:
	ASCII(.string	"pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC917:
	ASCII(.string	"PPS[%d] decode error.\n" )
	.zero	1
.LC920:
	ASCII(.string	"luma_log2_weight_denom" )
	.zero	1
.LC922:
	ASCII(.string	"luma_log2_weight_denom out of range(0,7).\n" )
	.zero	5
.LC924:
	ASCII(.string	"delta_chroma_log2_weight_denom" )
	.zero	1
.LC926:
	ASCII(.string	"delta_chroma_log2_weight_denom out of range(-7,7).\n" )
	.zero	4
.LC928:
	ASCII(.string	"chroma_log2_weight_denom out of range(0,7).\n" )
	.zero	3
.LC930:
	ASCII(.string	"delta_luma_weight_l0" )
	.zero	3
.LC932:
	ASCII(.string	"delta_luma_weight_l0(%d) out of range(-128,127).\n" )
	.zero	6
.LC934:
	ASCII(.string	"luma_offset_l0" )
	.zero	1
.LC936:
	ASCII(.string	"luma_offset_l0(%d) out of range(-128,127).\n" )
	.zero	4
.LC938:
	ASCII(.string	"delta_chroma_weight_l0" )
	.zero	1
.LC940:
	ASCII(.string	"delta_chroma_weight_l0 out of range(-128,127).\n" )
.LC942:
	ASCII(.string	"delta_chroma_offset_l0" )
	.zero	1
.LC944:
	ASCII(.string	"delta_chroma_offset_l0 out of range(-512,511).\n" )
.LC946:
	ASCII(.string	"delta_luma_weight_l1" )
	.zero	3
.LC948:
	ASCII(.string	"delta_luma_weight_l1 out of range(-128,127).\n" )
	.zero	2
.LC950:
	ASCII(.string	"luma_offset_l1" )
	.zero	1
.LC952:
	ASCII(.string	"luma_offset_l1 out of range(-128,127).\n" )
.LC954:
	ASCII(.string	"delta_chroma_weight_l1" )
	.zero	1
.LC956:
	ASCII(.string	"delta_chroma_weight_l1 out of range(-128,127).\n" )
.LC958:
	ASCII(.string	"delta_chroma_offset_l1" )
	.zero	1
.LC960:
	ASCII(.string	"delta_chroma_offset_l1 out of range(-512,511).\n" )
.LC962:
	ASCII(.string	"slice_pic_parameter_set_id" )
	.zero	5
.LC965:
	ASCII(.string	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\n" )
	.zero	6
.LC967:
	ASCII(.string	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\n" )
.LC969:
	ASCII(.string	"max_cu_width(%d)/max_cu_height(%d) = 0\n" )
.LC971:
	ASCII(.string	"slice_segment_address(%d) out of range(0,%d).\n" )
	.zero	1
.LC973:
	ASCII(.string	"slice_type" )
	.zero	5
.LC975:
	ASCII(.string	"slice_type(%d) out of range(0,2].\n" )
	.zero	5
.LC977:
	ASCII(.string	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \n" )
	.zero	7
.LC979:
	ASCII(.string	"SH HEVC_DecShortTermRefPicSet error.\n" )
	.zero	2
.LC981:
	ASCII(.string	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\n" )
	.zero	4
.LC983:
	ASCII(.string	"num_long_term_sps" )
	.zero	6
.LC985:
	ASCII(.string	"num_long_term_sps(%d) out of range[0,%d].\n" )
	.zero	5
.LC987:
	ASCII(.string	"num_long_term_pics" )
	.zero	5
.LC989:
	ASCII(.string	"SH ERROR: (num_negative_pics(%d) + num_positive_pics(%d) + num_of_longterm_pics(%d)) > %d\n" )
	.zero	5
.LC991:
	ASCII(.string	"lt_idx_sps[%d] = %d, but out of range[0,%d].\n" )
	.zero	2
.LC993:
	ASCII(.string	"delta_poc_msb_cycle_lt" )
	.zero	1
.LC995:
	ASCII(.string	"ERROR: pRPS->num_of_pics(%d) > %d.\n" )
	.zero	4
.LC997:
	ASCII(.string	"Error0: Parse num_active_ref_layer_pics %d > HEVC_MAX_NUM_LAYERS %d, not support\n" )
	.zero	6
.LC999:
	ASCII(.string	"Error1: Parse num_active_ref_layer_pics %d > HEVC_MAX_NUM_LAYERS %d, not support\n" )
	.zero	6
.LC1001:
	ASCII(.string	"Parse inter_layer_pred_layer_idc[%d] %d > HEVC_MAX_NUM_LAYERS %d, not support" )
	.zero	2
.LC1003:
	ASCII(.string	"num_ref_idx_l0_active_minus1" )
	.zero	3
.LC1005:
	ASCII(.string	"num_ref_idx_l0_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC1007:
	ASCII(.string	"num_ref_idx_l1_active_minus1" )
	.zero	3
.LC1009:
	ASCII(.string	"num_ref_idx_l1_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC1011:
	ASCII(.string	"pRPS is null.\n" )
	.zero	1
.LC1013:
	ASCII(.string	"pRPS->num_of_pics out(%d) of range(0,%d).\n" )
	.zero	5
.LC1015:
	ASCII(.string	"SH HEVC_DecRefPicListsModification error.\n" )
	.zero	5
.LC1017:
	ASCII(.string	"collocated_ref_idx" )
	.zero	5
.LC1019:
	ASCII(.string	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) out of range(0,%d).\n" )
.LC1021:
	ASCII(.string	"SH HEVC_DecPredWeightTable error.\n" )
	.zero	5
.LC1023:
	ASCII(.string	"five_minus_max_num_merge_cand" )
	.zero	2
.LC1025:
	ASCII(.string	"SH max_num_merge_cand(%d) out of range(1,5).\n" )
	.zero	2
.LC1027:
	ASCII(.string	"slice_qp_delta" )
	.zero	1
.LC1029:
	ASCII(.string	"SH slice_qp(%d) out of range [-%d,51].\n" )
.LC1031:
	ASCII(.string	"slice_cb_qp_offset" )
	.zero	5
.LC1033:
	ASCII(.string	"SH slice_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC1035:
	ASCII(.string	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	2
.LC1037:
	ASCII(.string	"slice_cr_qp_offset" )
	.zero	5
.LC1039:
	ASCII(.string	"SH slice_cr_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC1041:
	ASCII(.string	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) out of range[-12,12].\n" )
.LC1043:
	ASCII(.string	"slice_beta_offset_div2" )
	.zero	1
.LC1045:
	ASCII(.string	"SH slice_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	5
.LC1047:
	ASCII(.string	"slice_tc_offset_div2" )
	.zero	3
.LC1049:
	ASCII(.string	"SH slice_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	7
.LC1051:
	ASCII(.string	"num_entry_point_offsets" )
.LC1053:
	ASCII(.string	"CurrSlice.num_entry_point_offsets(%d) out of range[0,%d].\n" )
	.zero	5
.LC1055:
	ASCII(.string	"offset_len_minus1" )
	.zero	6
.LC1057:
	ASCII(.string	"CurrSlice.offset_len(%d) out of range[1,32].\n" )
	.zero	2
.LC1059:
	ASCII(.string	"slice_segment_header_extension_length" )
	.zero	2
.LC1061:
	ASCII(.string	"slice_segment_header_extension_length(%d) out of range [0,256]\n" )
.LC1063:
	ASCII(.string	"bitsLeft(%d) < slice_segment_header_extension_length(%d)\n" )
	.zero	6
.LC1065:
	ASCII(.string	"HEVC_ParseSliceExtension failed\n" )
	.zero	7
.LC1070:
	ASCII(.string	"%s layer num %d invalid!\n" )
	.zero	6
.LC1072:
	ASCII(.string	"%s layer %d image size abnormal(%dx%d)\n" )
.LC1075:
	ASCII(.string	"%s arrange mem failed.\n" )
.LC1077:
	ASCII(.string	"Init dec para\n" )
	.zero	1
.LC1081:
	ASCII(.string	"Is SHVC: layer%d %dx%d, layer%d %dx%d.\n" )
.LC1083:
	ASCII(.string	"Layer %d: %d x %d\n" )
	.zero	5
.LC1085:
	ASCII(.string	"HEVC_InitDPB error, return %d\n" )
	.zero	1
.LC1087:
	ASCII(.string	"HEVC_AllocFrameStore error\n" )
	.zero	4
.LC1090:
	ASCII(.string	"%s: HEVC_OutputFrame failed!\n" )
	.zero	2
.LC1093:
	ASCII(.string	"%s output current picture failed\n" )
	.zero	6
.LC1097:
	ASCII(.string	"HEVC.c line %d: frame para err(ret=%d), recycle image self\n" )
	.zero	4
.LC1101:
	ASCII(.string	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\n" )
.LC1105:
	ASCII(.string	"%s call HEVC_GetUnRefPicWithMinPoc failed\n" )
	.zero	5
.LC1107:
	ASCII(.string	"%s call HEVC_OutputOneFrmFromDPB failed\n" )
	.zero	7
.LC1110:
	ASCII(.string	"%s: HEVC_OutputFrmToVO err!\n" )
	.zero	3
.LC1112:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC1114:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC1116:
	ASCII(.string	"nal_release_err\n" )
	.zero	7
.LC1119:
	ASCII(.string	"%s: flush dpb failed, return %d\n" )
	.zero	7
.LC1122:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), need to increase DPB size.\n" )
	.zero	5
.LC1124:
	ASCII(.string	"%s call HEVC_IncreaseDPBSize failed\n" )
	.zero	3
.LC1126:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpoc frame.\n" )
	.zero	3
.LC1131:
	ASCII(.string	"%s with invalid pos(%d)\n" )
	.zero	7
.LC1134:
	ASCII(.string	"%s get APC error, ret %d\n" )
	.zero	6
.LC1137:
	ASCII(.string	"%s %d: InsertFrmInDPB failed, return %d\n" )
	.zero	7
.LC1139:
	ASCII(.string	"%s call HEVC_CheckFrameStore failed!\n" )
	.zero	2
.LC1143:
	ASCII(.string	"%s call HEVC_RemoveUnUsedFrameStore Failed.\n" )
	.zero	3
.LC1145:
	ASCII(.string	"%s call HEVC_InsertFrmInDPB Failed.\n" )
	.zero	3
.LC1150:
	ASCII(.string	"%s call HEVC_FirstFrameFastOut Failed\n" )
	.zero	1
.LC1152:
	ASCII(.string	"DPB.used_size may bigger than DPB.size\n" )
.LC1154:
	ASCII(.string	"HEVC_InsertFrmInDPB Failed, ret = %d\n" )
	.zero	2
.LC1156:
	ASCII(.string	"%s call HEVC_OutputFrmFromDPB failed\n" )
	.zero	2
.LC1160:
	ASCII(.string	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_NORMAL\n" )
	.zero	5
.LC1162:
	ASCII(.string	"%s, REPORT_IFRAME_ERR\n" )
	.zero	1
.LC1165:
	ASCII(.string	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n" )
	.zero	1
.LC1167:
	ASCII(.string	"%s call HEVC_IModeProcess Failed\n" )
	.zero	6
.LC1169:
	ASCII(.string	"HEVC_StorePicInDpb return(%d) from L%d\n" )
.LC1171:
	ASCII(.string	"%s call HEVC_SimpleDPBProcess Failed\n" )
	.zero	2
.LC1173:
	ASCII(.string	"%s call HEVC_DecOrderProcess Failed\n" )
	.zero	3
.LC1175:
	ASCII(.string	"%s call HEVC_DispOrderProcess Failed\n" )
	.zero	2
.LC1177:
	ASCII(.string	"%s return HEVC_DEC_ERR\n" )
.LC1180:
	ASCII(.string	"No frame store for lost pic.\n" )
	.zero	2
.LC1182:
	ASCII(.string	"DPB ERROR: Can not get ref_fs!\n" )
.LC1184:
	ASCII(.string	"DPB no suited fs for lost pic.\n" )
.LC1186:
	ASCII(.string	"Take poc(%d) to creat lost poc(%d).\n" )
	.zero	3
.LC1188:
	ASCII(.string	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\n" )
	.zero	5
.LC1190:
	ASCII(.string	"ERROR: Can not new logic fs!\n" )
	.zero	2
.LC1192:
	ASCII(.string	"Lost pic insert in DPB Failed!\n" )
.LC1194:
	ASCII(.string	"Ref frame(poc %d) lost.\n" )
	.zero	7
.LC1196:
	ASCII(.string	"s32OutErrThr = %d,drop poc %d because lost ref frame(pod %d)\n" )
	.zero	2
.LC1199:
	ASCII(.string	"DecVDM MaxBytesReceived exceed threshold!\n" )
	.zero	5
.LC1201:
	ASCII(.string	"DecVDM no slice and needn't start VDM\n" )
	.zero	1
.LC1203:
	ASCII(.string	"IPBDecMode Changed (%d -> %d)\n" )
	.zero	1
.LC1206:
	ASCII(.string	"VDM start, TotalPicNum=%d.\n" )
	.zero	4
.LC1209:
	ASCII(.string	"%s no correct slice in the pic\n" )
.LC1211:
	ASCII(.string	"Discard this B(poc=%d) before P, is_ref_idc=%d.\n" )
	.zero	7
.LC1214:
	ASCII(.string	"metadatasize is too large:%d at line:%d\n" )
	.zero	7
.LC1217:
	ASCII(.string	"%s:%d Metadata map failed\n" )
	.zero	5
.LC1221:
	ASCII(.string	"%s:%d Metadata unmap failed\n" )
	.zero	3
.LC1224:
	ASCII(.string	"*****[%s][%d],BL Codec can only dec BL stream!!*****\n" )
	.zero	2
.LC1226:
	ASCII(.string	"*****[%s][%d],EL Codec can only dec EL stream in DV_DUAL_VES_IMP stream!!*****\n" )
.LC1228:
	ASCII(.string	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****\n" )
	.zero	3
.LC1232:
	ASCII(.string	"%s call HEVC_FlushOutputFrmFromDPB failed\n" )
	.zero	5
.LC1234:
	ASCII(.string	"%s call HEVC_EmptyFrmFromDPB failed\n" )
	.zero	3
.LC1236:
	ASCII(.string	"Meet CRA frame, force output remain frame, CurPoc %d, LastPoc %d\n" )
	.zero	6
.LC1238:
	ASCII(.string	"Init pic err, exit\n" )
	.zero	4
.LC1240:
	ASCII(.string	"HEVC_WritePicMsg failed!\n" )
	.zero	6
.LC1242:
	ASCII(.string	"Start Reason: SliceParaNum= %d\n" )
.LC1245:
	ASCII(.string	"Too many slice , err!\n" )
	.zero	1
.LC1247:
	ASCII(.string	"Cur pic not init yet, discard this slice!\n" )
	.zero	5
.LC1249:
	ASCII(.string	"Dec List error, ret=%d\n" )
.LC1251:
	ASCII(.string	"Ref List is Wrong!\n" )
	.zero	4
.LC1253:
	ASCII(.string	"HEVC_WriteSliceMsg err.\n" )
	.zero	7
.LC1256:
	ASCII(.string	"VPS decode error.\n" )
	.zero	5
.LC1259:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1261:
	ASCII(.string	"PPS decode error.\n" )
	.zero	5
.LC1263:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1265:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d\n" )
.LC1268:
	ASCII(.string	"HEVC_DecSliceSegmentHeader dec err\n" )
	.zero	4
.LC1271:
	ASCII(.string	"CurBitsLen = %d, MinBitsLen = %d\n" )
	.zero	6
.LC1274:
	ASCII(.string	"%s last frame fs unrelease, fix it!\n" )
	.zero	3
.LC1278:
	ASCII(.string	"CtbNumOneFrame=%d, SedEnd0=%d\n" )
	.zero	1
.LC1282:
	ASCII(.string	"%s: Get context addr failed!\n" )
	.zero	2
.LC1284:
	ASCII(.string	"%s FATAL: MemOffset %d > ContextMemSize %d.\n" )
	.zero	3
.LC1286:
	ASCII(.string	"%s: VCTRL_GetChanIDByCtx() return -1!\n" )
	.zero	1
.LC1288:
	ASCII(.string	"Fs leak, clear dpb fs not in vo queue.\n" )
.LC1290:
	ASCII(.string	"No frame store available!\n" )
	.zero	5
.LC1293:
	ASCII(.string	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak, ClearAll!\n" )
.LC1295:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pPacket!\n" )
	.zero	1
.LC1297:
	ASCII(.string	"HevcCtx not init!\n" )
	.zero	5
.LC1299:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\n" )
	.zero	6
.LC1302:
	ASCII(.string	"nal_layer_id out %d of range[0,1].\n" )
	.zero	4
.LC1304:
	ASCII(.string	"Not need nal of layer %d in output order %d.\n" )
	.zero	2
.LC1310:
	ASCII(.string	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	4
.LC1313:
	ASCII(.string	"HEVC_InquireSliceProperty error.\n" )
	.zero	6
.LC1316:
	ASCII(.string	"HEVC_DecOneNal ERR\n" )
	.zero	4
.LC1319:
	ASCII(.string	"HEVC_StorePicInDPB failed, ret = %d\n" )
	.zero	3
.LC1322:
	ASCII(.string	"pHevcCtx->CurrPic.frame_store is null pointer\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 456960
.LANCHOR3 = . + 604928
.LANCHOR6 = . + 639744
	.type	g_SigLastScan, %object
	.size	g_SigLastScan, 458752
g_SigLastScan:
	.zero	458752
	.type	g_TsToRsMap, %object
	.size	g_TsToRsMap, 147456
g_TsToRsMap:
	.zero	147456
	.type	g_IsDeced, %object
	.size	g_IsDeced, 36864
g_IsDeced:
	.zero	36864
	.type	s_TmpParam, %object
	.size	s_TmpParam, 24912
s_TmpParam:
	.zero	24912
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
