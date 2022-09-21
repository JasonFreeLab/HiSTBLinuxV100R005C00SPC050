#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vp9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VP9_u_v_x
	.type	VP9_u_v_x, %function
VP9_u_v_x:
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
	.size	VP9_u_v_x, .-VP9_u_v_x
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_s_v
	.type	VP9_s_v, %function
VP9_s_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	w1, w20, 1
	mov	x0, x19
	bl	BsGet
	tbnz	x0, 0, .L6
	asr	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L6:
	neg	w0, w0, asr 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_s_v, .-VP9_s_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReadIsValid
	.type	Vp9_Cabac_ReadIsValid, %function
Vp9_Cabac_ReadIsValid:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	w19, w1
	bl	_mcount
	cmp	x20, xzr
	mov	w0, 0
	ccmp	x21, xzr, 4, ne
	beq	.L8
	add	x1, x20, x19, uxtw
	cmp	x21, x1
	ccmp	x20, x1, 2, cs
	cset	w0, cc
.L8:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Cabac_ReadIsValid, .-Vp9_Cabac_ReadIsValid
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReaderFill
	.type	Vp9_Cabac_ReaderFill, %function
Vp9_Cabac_ReaderFill:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w19, 24
	mov	w20, 16
	bl	_mcount
	ldp	w22, w23, [x21, 36]
	mov	x0, x21
	sub	w19, w19, w23
	sub	w20, w20, w23
	and	w19, w19, -8
	mov	w1, w19
	sub	w20, w20, w19
	and	w20, w20, 7
	add	w19, w23, w19
	bl	BsGet
	lsl	w0, w0, w20
	orr	w20, w0, w22
	stp	w20, w19, [x21, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_Cabac_ReaderFill, .-Vp9_Cabac_ReaderFill
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_Read
	.type	Vp9_Cabac_Read, %function
Vp9_Cabac_Read:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldp	w22, w19, [x20, 40]
	sub	w19, w19, #1
	mul	w19, w19, w21
	lsr	w19, w19, 8
	add	w19, w19, 1
	tbnz	w22, #31, .L12
	ldr	w1, [x20, 36]
.L13:
	lsl	w2, w19, 24
	mov	w0, 0
	cmp	w2, w1
	bhi	.L14
	ldr	w3, [x20, 44]
	sub	w1, w1, w2
	mov	w0, 1
	sub	w19, w3, w19
.L14:
	ldr	x2, .LC0
	ldrb	w2, [x2, w19, uxtw]
	sub	w22, w22, w2
	lsl	w19, w19, w2
	lsl	w1, w1, w2
	str	w19, [x20, 44]
	stp	w1, w22, [x20, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L12:
	mov	w1, 24
	mov	w23, 16
	sub	w1, w1, w22
	sub	w23, w23, w22
	and	w1, w1, -8
	mov	x0, x20
	sub	w23, w23, w1
	ldr	w21, [x20, 36]
	and	w23, w23, 7
	add	w22, w22, w1
	bl	BsGet
	lsl	w0, w0, w23
	orr	w1, w0, w21
	b	.L13
	.size	Vp9_Cabac_Read, .-Vp9_Cabac_Read
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReadLiteral
	.type	Vp9_Cabac_ReadLiteral, %function
Vp9_Cabac_ReadLiteral:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w25, w1
	bl	_mcount
	subs	w25, w25, #1
	bmi	.L21
	ldr	x27, .LC1
	mov	w26, 0
	mov	w24, 24
	mov	w23, 1
	ldp	w20, w21, [x22, 36]
	ldr	w19, [x22, 44]
	b	.L20
	.p2align 3
.L18:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L19
	ldr	w2, [x22, 44]
	lsl	w0, w23, w25
	sub	w20, w20, w1
	sub	w19, w2, w19
.L19:
	orr	w26, w26, w0
	ldrb	w0, [x27, w19, uxtw]
	sub	w25, w25, #1
	lsl	w20, w20, w0
	sub	w21, w21, w0
	lsl	w19, w19, w0
	cmn	w25, #1
	stp	w20, w21, [x22, 36]
	str	w19, [x22, 44]
	beq	.L17
.L20:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w21, #31, .L18
	sub	w1, w24, w21
	mov	w0, 16
	sub	w28, w0, w21
	and	w1, w1, -8
	sub	w28, w28, w1
	mov	x0, x22
	and	w28, w28, 7
	add	w21, w1, w21
	bl	BsGet
	lsl	w0, w0, w28
	orr	w20, w0, w20
	b	.L18
.L21:
	mov	w26, 0
.L17:
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	Vp9_Cabac_ReadLiteral, .-Vp9_Cabac_ReadLiteral
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReaderInit
	.type	Vp9_Cabac_ReaderInit, %function
Vp9_Cabac_ReaderInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, -8
	mov	w1, 32
	stp	wzr, w0, [x19, 36]
	mov	w0, 255
	str	w0, [x19, 44]
	mov	x0, x19
	bl	BsGet
	mov	w2, w0
	ldr	w3, [x19, 44]
	sub	w1, w3, #1
	ubfx	x1, x1, 1, 24
	add	w1, w1, 1
	lsl	w0, w1, 24
	cmp	w0, w2
	bhi	.L27
	sub	w2, w2, w0
	sub	w1, w3, w1
	mov	w0, 1
.L26:
	ldr	x4, .LC2
	mov	w3, 24
	ldrb	w4, [x4, w1, uxtw]
	lsl	w2, w2, w4
	sub	w3, w3, w4
	lsl	w1, w1, w4
	str	w1, [x19, 44]
	stp	w2, w3, [x19, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L27:
	mov	w0, 0
	b	.L26
	.size	Vp9_Cabac_ReaderInit, .-Vp9_Cabac_ReaderInit
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadTxMode
	.type	Vp9_ReadTxMode, %function
Vp9_ReadTxMode:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w23, 1
	mov	w24, 0
	bl	_mcount
	ldr	x25, .LC3
	ldp	w20, w22, [x21, 36]
	ldr	w19, [x21, 44]
	mov	w3, 24
	mov	w28, 16
	mov	w26, w23
.L31:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L39
.L29:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L30
	ldr	w2, [x21, 44]
	lsl	w0, w26, w23
	sub	w20, w20, w1
	sub	w19, w2, w19
.L30:
	orr	w24, w24, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w23, w23, #1
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w19, w19, w0
	cmn	w23, #1
	stp	w20, w22, [x21, 36]
	str	w19, [x21, 44]
	bne	.L31
	cmp	w24, 3
	beq	.L40
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L39:
	sub	w1, w3, w22
	sub	w27, w28, w22
	and	w1, w1, -8
	mov	x0, x21
	sub	w27, w27, w1
	str	w3, [x29, 108]
	and	w27, w27, 7
	add	w22, w1, w22
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldr	w3, [x29, 108]
	b	.L29
	.p2align 3
.L40:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L41
.L33:
	lsl	w0, w19, 24
	cmp	w0, w20
	bhi	.L34
	ldr	w1, [x21, 44]
	sub	w20, w20, w0
	mov	w24, 4
	sub	w19, w1, w19
.L34:
	ldrb	w0, [x25, w19, uxtw]
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w19, w19, w0
	str	w19, [x21, 44]
	stp	w20, w22, [x21, 36]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L41:
	mov	w1, 24
	mov	w23, 16
	sub	w1, w1, w22
	sub	w23, w23, w22
	and	w1, w1, -8
	mov	x0, x21
	sub	w23, w23, w1
	add	w22, w22, w1
	and	w23, w23, 7
	bl	BsGet
	lsl	w0, w0, w23
	orr	w20, w0, w20
	b	.L33
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReaderHasError
	.type	Vp9_ReaderHasError, %function
Vp9_ReaderHasError:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 40]
	mov	w1, 65502
	movk	w1, 0x3fff, lsl 16
	ldr	x19, [sp, 16]
	sub	w0, w0, #33
	cmp	w0, w1
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ReaderHasError, .-Vp9_ReaderHasError
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DiffUpdateProb
	.type	Vp9_DiffUpdateProb, %function
Vp9_DiffUpdateProb:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldp	w24, w19, [x22, 40]
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L44
	ldr	w20, [x22, 36]
.L45:
	lsl	w1, w19, 24
	cmp	w1, w20
	bhi	.L46
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	ldr	x23, .LC4
	sub	w19, w0, w19
	ldrb	w0, [x23, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L89
.L48:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w0, w19, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L53
	ldr	w19, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w19, w0
	ldrb	w0, [x23, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L90
.L55:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L59
	ldr	w19, [x22, 44]
	sub	w20, w20, w1
	mov	w25, 0
	mov	w26, 6
	sub	w0, w19, w0
	mov	w2, 24
	mov	w28, 16
	mov	w3, 1
	ldrb	w19, [x23, w0, uxtw]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	b	.L60
	.p2align 3
.L64:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L65
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w3, w26
.L65:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	beq	.L91
.L60:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w24, #31, .L64
	sub	w1, w2, w24
	sub	w27, w28, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w3, w2, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w3, w2, [x29, 104]
	b	.L64
	.p2align 3
.L46:
	uxtw	x0, w19
	ldr	x23, .LC4
	mov	w25, 0
	mov	w26, 3
	mov	w28, 24
	mov	w4, 16
	ldrb	w0, [x23, x0]
	mov	w3, 1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L51:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L92
.L49:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L50
	ldr	w2, [x22, 44]
	lsl	w0, w3, w26
	sub	w20, w20, w1
	sub	w19, w2, w19
.L50:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L51
.L52:
	ldrb	w1, [x21]
	add	x23, x23, 256
	sub	w1, w1, #1
	lsl	w3, w1, 1
	ldrb	w2, [x23, w25, sxtw]
	cmp	w3, 255
	bgt	.L67
	add	w0, w2, 1
	cmp	w0, w3
	bgt	.L68
	tbnz	x0, 0, .L93
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L68:
	add	w0, w0, 1
	strb	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L67:
	mov	w0, 254
	add	w3, w2, 1
	sub	w1, w0, w1
	cmp	w3, w1, lsl 1
	ble	.L94
.L71:
	mov	w0, 255
	sub	w0, w0, w3
.L96:
	strb	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L94:
	tbnz	x3, 0, .L95
	add	w0, w3, w3, lsr 31
	add	w3, w1, w0, asr 1
	mov	w0, 255
	sub	w0, w0, w3
	b	.L96
	.p2align 3
.L53:
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 3
	mov	w28, 24
	mov	w3, 16
	mov	w2, 1
	ldrb	w19, [x23, x1]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L58:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L97
.L56:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L57
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w2, w26
.L57:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L58
	add	w25, w25, 16
	b	.L52
	.p2align 3
.L92:
	sub	w1, w28, w24
	sub	w27, w4, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w3, w4, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w3, w4, [x29, 104]
	b	.L49
	.p2align 3
.L93:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L68
	.p2align 3
.L95:
	add	w2, w2, 2
	sub	w3, w1, w2, lsr 1
	b	.L71
	.p2align 3
.L44:
	mov	w23, 24
	mov	w25, 16
	sub	w23, w23, w24
	sub	w25, w25, w24
	and	w23, w23, -8
	mov	x0, x22
	mov	w1, w23
	sub	w25, w25, w23
	ldr	w20, [x22, 36]
	and	w25, w25, 7
	bl	BsGet
	lsl	w0, w0, w25
	add	w24, w24, w23
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L45
	.p2align 3
.L97:
	sub	w1, w28, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w2, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w2, w3, [x29, 104]
	b	.L56
	.p2align 3
.L59:
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 4
	mov	w2, 24
	mov	w3, 16
	mov	w28, 1
	ldrb	w19, [x23, x1]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	.p2align 2
.L63:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L98
.L61:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L62
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w28, w26
.L62:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L63
	add	w25, w25, 32
	b	.L52
	.p2align 3
.L98:
	sub	w1, w2, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w2, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w2, w3, [x29, 104]
	b	.L61
	.p2align 3
.L89:
	mov	w26, 24
	mov	w25, 16
	sub	w26, w26, w24
	sub	w25, w25, w24
	and	w26, w26, -8
	mov	x0, x22
	mov	w1, w26
	sub	w25, w25, w26
	and	w25, w25, 7
	add	w24, w26, w24
	bl	BsGet
	lsl	w0, w0, w25
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L48
.L91:
	cmp	w25, 64
	bgt	.L99
	add	w25, w25, 64
	b	.L52
.L99:
	mov	w1, 128
	mov	x0, x22
	bl	Vp9_Cabac_Read
	add	w0, w0, w25, lsl 1
	sub	w25, w0, #65
	add	w25, w25, 64
	b	.L52
.L90:
	mov	w26, 24
	mov	w25, 16
	sub	w26, w26, w24
	sub	w25, w25, w24
	and	w26, w26, -8
	mov	x0, x22
	mov	w1, w26
	sub	w25, w25, w26
	and	w25, w25, 7
	add	w24, w26, w24
	bl	BsGet
	lsl	w0, w0, w25
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L55
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadTxProbs
	.type	Vp9_ReadTxProbs, %function
Vp9_ReadTxProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x1
	mov	x22, x0
	mov	x0, x30
	mov	x26, 0
	mov	w23, 24
	mov	w21, 16
	bl	_mcount
	ldr	x24, .LC8
	ldp	w28, w19, [x20, 36]
	ldr	w1, [x20, 44]
	mov	w27, 1
.L131:
	sub	w1, w1, #1
	lsl	w25, w1, 6
	sub	w1, w25, w1
	ubfx	x1, x1, 6, 24
	add	w25, w1, 1
	tbnz	w19, #31, .L297
.L101:
	lsl	w0, w25, 24
	cmp	w0, w28
	bhi	.L102
	ldr	w1, [x20, 44]
	sub	w28, w28, w0
	sub	w1, w1, w25
	ldrb	w25, [x24, w1, uxtw]
	lsl	w28, w28, w25
	sub	w19, w19, w25
	lsl	w25, w1, w25
	str	w25, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L298
.L103:
	sub	w1, w25, #1
	ubfx	x25, x1, 1, 24
	add	w1, w25, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L104
	ldr	w25, [x20, 44]
	sub	w28, w28, w0
	sub	w25, w25, w1
	ldrb	w1, [x24, w25, uxtw]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w25, w25, w1
	str	w25, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L299
.L106:
	sub	w25, w25, #1
	ubfx	x0, x25, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L111
	sub	w25, w28, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	ldrb	w1, [x24, w0, uxtw]
	sub	w3, w19, w1
	lsl	w25, w25, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w25, w3, [x20, 36]
	tbnz	w3, #31, .L300
.L113:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w25
	bhi	.L117
	sub	w25, w25, w1
	ldr	w1, [x20, 44]
	mov	w28, 0
	mov	w4, 6
	sub	w0, w1, w0
	ldrb	w19, [x24, w0, uxtw]
	lsl	w25, w25, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w25, w3, [x20, 36]
	b	.L118
	.p2align 3
.L122:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L123
	ldr	w0, [x20, 44]
	sub	w25, w25, w1
	sub	w19, w0, w19
	lsl	w0, w27, w4
.L123:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w25, w3, [x20, 36]
	str	w19, [x20, 44]
	beq	.L301
.L118:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w3, #31, .L122
	sub	w1, w23, w3
	sub	w5, w21, w3
	and	w1, w1, -8
	mov	x0, x20
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L122
	.p2align 3
.L102:
	uxtw	x0, w25
	ldrb	w1, [x24, x0]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w1, w25, w1
	str	w1, [x20, 44]
	stp	w28, w19, [x20, 36]
.L229:
	add	x26, x26, 1
	cmp	x26, 2
	bne	.L131
	add	x25, x22, 3
	add	x23, x22, 7
	mov	w26, 24
	mov	w27, 1
.L164:
	sub	w1, w1, #1
	lsl	w21, w1, 6
	sub	w1, w21, w1
	ubfx	x1, x1, 6, 24
	add	w21, w1, 1
	tbnz	w19, #31, .L302
.L132:
	lsl	w0, w21, 24
	cmp	w0, w28
	bhi	.L133
	ldr	w1, [x20, 44]
	sub	w28, w28, w0
	sub	w1, w1, w21
	ldrb	w21, [x24, w1, uxtw]
	lsl	w28, w28, w21
	sub	w19, w19, w21
	lsl	w21, w1, w21
	str	w21, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L303
.L134:
	sub	w21, w21, #1
	ubfx	x21, x21, 1, 24
	add	w1, w21, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L135
	ldr	w21, [x20, 44]
	sub	w28, w28, w0
	sub	w21, w21, w1
	ldrb	w1, [x24, w21, uxtw]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w21, w21, w1
	str	w21, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L304
.L137:
	sub	w21, w21, #1
	ubfx	x0, x21, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L142
	ldr	w4, [x20, 44]
	sub	w1, w28, w1
	sub	w0, w4, w0
	ldrb	w4, [x24, w0, uxtw]
	sub	w28, w19, w4
	lsl	w21, w1, w4
	lsl	w19, w0, w4
	str	w19, [x20, 44]
	stp	w21, w28, [x20, 36]
	tbnz	w28, #31, .L305
.L144:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w21
	bhi	.L148
	sub	w5, w21, w1
	ldr	w1, [x20, 44]
	mov	w21, 0
	mov	w6, 6
	sub	w0, w1, w0
	ldrb	w19, [x24, w0, uxtw]
	lsl	w1, w5, w19
	sub	w4, w28, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w1, w4, [x20, 36]
	b	.L149
	.p2align 3
.L153:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L154
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w6
.L154:
	orr	w21, w21, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w6, w6, #1
	lsl	w1, w28, w0
	sub	w4, w4, w0
	lsl	w19, w19, w0
	cmn	w6, #1
	stp	w1, w4, [x20, 36]
	str	w19, [x20, 44]
	beq	.L306
.L149:
	sub	w19, w19, #1
	mov	w28, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w4, #31, .L153
	sub	w1, w26, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w5, w0, w4
	sub	w5, w5, w1
	add	w4, w1, w4
	mov	x0, x20
	str	w4, [x29, 108]
	stp	w6, w5, [x29, 100]
	bl	BsGet
	ldp	w6, w5, [x29, 100]
	ldr	w4, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L153
	.p2align 3
.L133:
	uxtw	x0, w21
	ldrb	w1, [x24, x0]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w1, w21, w1
	str	w1, [x20, 44]
	sub	w1, w1, #1
	lsl	w21, w1, 6
	sub	w1, w21, w1
	stp	w28, w19, [x20, 36]
	ubfx	x1, x1, 6, 24
	add	w21, w1, 1
	tbnz	w19, #31, .L307
.L162:
	lsl	w0, w21, 24
	cmp	w0, w28
	bhi	.L163
	ldr	w4, [x20, 44]
	sub	w0, w28, w0
	mov	x1, x25
	sub	w21, w4, w21
	ldrb	w4, [x24, w21, uxtw]
	lsl	w0, w0, w4
	sub	w19, w19, w4
	lsl	w21, w21, w4
	str	w21, [x20, 44]
	stp	w0, w19, [x20, 36]
	mov	x0, x20
	bl	Vp9_DiffUpdateProb
	ldr	w1, [x20, 44]
	ldp	w28, w19, [x20, 36]
.L231:
	add	x25, x25, 2
	cmp	x23, x25
	bne	.L164
	sub	w1, w1, #1
	add	x27, x22, 8
	lsl	w26, w1, 6
	add	x22, x22, 14
	sub	w1, w26, w1
	mov	w23, 16
	ubfx	x1, x1, 6, 24
	mov	w21, 1
	mov	w25, 254
	add	w26, w1, 1
	tbnz	w19, #31, .L308
.L165:
	lsl	w0, w26, 24
	cmp	w0, w28
	bhi	.L166
	ldr	w1, [x20, 44]
	sub	w28, w28, w0
	sub	w1, w1, w26
	ldrb	w26, [x24, w1, uxtw]
	lsl	w28, w28, w26
	sub	w19, w19, w26
	lsl	w26, w1, w26
	str	w26, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L309
.L167:
	sub	w26, w26, #1
	ubfx	x26, x26, 1, 24
	add	w1, w26, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L168
	ldr	w26, [x20, 44]
	sub	w28, w28, w0
	sub	w26, w26, w1
	ldrb	w1, [x24, w26, uxtw]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w26, w26, w1
	str	w26, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L310
.L170:
	sub	w26, w26, #1
	ubfx	x0, x26, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L175
	sub	w26, w28, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	ldrb	w1, [x24, w0, uxtw]
	sub	w3, w19, w1
	lsl	w26, w26, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	tbnz	w3, #31, .L311
.L177:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L181
	sub	w26, w26, w1
	ldr	w1, [x20, 44]
	mov	w28, 0
	mov	w4, 6
	sub	w0, w1, w0
	ldrb	w19, [x24, w0, uxtw]
	lsl	w26, w26, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	b	.L182
	.p2align 3
.L186:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L187
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L187:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w3, [x20, 36]
	str	w19, [x20, 44]
	beq	.L312
.L182:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w3, #31, .L186
	mov	w0, 24
	sub	w5, w23, w3
	sub	w1, w0, w3
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L186
	.p2align 3
.L163:
	uxtw	x0, w21
	ldrb	w1, [x24, x0]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w1, w21, w1
	str	w1, [x20, 44]
	stp	w28, w19, [x20, 36]
	b	.L231
	.p2align 3
.L166:
	uxtw	x0, w26
	ldrb	w1, [x24, x0]
	lsl	w28, w28, w1
	sub	w19, w19, w1
	lsl	w1, w26, w1
	str	w1, [x20, 44]
	sub	w1, w1, #1
	lsl	w26, w1, 6
	sub	w26, w26, w1
	stp	w28, w19, [x20, 36]
	ubfx	x0, x26, 6, 24
	add	w26, w0, 1
	tbnz	w19, #31, .L313
.L195:
	lsl	w1, w26, 24
	cmp	w1, w28
	bhi	.L196
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w0, w0, w26
	ldrb	w26, [x24, w0, uxtw]
	lsl	w28, w28, w26
	sub	w19, w19, w26
	lsl	w26, w0, w26
	str	w26, [x20, 44]
	stp	w28, w19, [x20, 36]
	tbnz	w19, #31, .L314
.L197:
	sub	w26, w26, #1
	ubfx	x26, x26, 1, 24
	add	w0, w26, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L198
	ldr	w26, [x20, 44]
	sub	w28, w28, w1
	sub	w26, w26, w0
	ldrb	w0, [x24, w26, uxtw]
	lsl	w28, w28, w0
	sub	w3, w19, w0
	lsl	w26, w26, w0
	str	w26, [x20, 44]
	stp	w28, w3, [x20, 36]
	tbnz	w3, #31, .L315
.L200:
	sub	w26, w26, #1
	ubfx	x19, x26, 1, 24
	add	w0, w19, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L205
	sub	w26, w28, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	ldrb	w19, [x24, w0, uxtw]
	lsl	w26, w26, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	tbnz	w3, #31, .L316
.L207:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L211
	sub	w26, w26, w1
	ldr	w1, [x20, 44]
	mov	w28, 0
	mov	w4, 6
	sub	w0, w1, w0
	ldrb	w19, [x24, w0, uxtw]
	lsl	w26, w26, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	b	.L212
	.p2align 3
.L216:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L217
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L217:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w3, [x20, 36]
	str	w19, [x20, 44]
	beq	.L317
.L212:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w3, #31, .L216
	mov	w0, 24
	sub	w5, w23, w3
	sub	w1, w0, w3
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L216
	.p2align 3
.L196:
	uxtw	x0, w26
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w19, w19, w0
	lsl	w0, w26, w0
	str	w0, [x20, 44]
	sub	w0, w0, #1
	lsl	w26, w0, 6
	sub	w0, w26, w0
	stp	w28, w19, [x20, 36]
	ubfx	x0, x0, 6, 24
	add	w26, w0, 1
	tbnz	w19, #31, .L318
.L225:
	lsl	w0, w26, 24
	cmp	w0, w28
	bhi	.L226
	ldr	w4, [x20, 44]
	sub	w3, w28, w0
	mov	x1, x27
	mov	x0, x20
	sub	w4, w4, w26
	ldrb	w5, [x24, w4, uxtw]
	lsl	w3, w3, w5
	sub	w19, w19, w5
	lsl	w4, w4, w5
	str	w4, [x20, 44]
	stp	w3, w19, [x20, 36]
	bl	Vp9_DiffUpdateProb
.L234:
	add	x27, x27, 3
	cmp	x27, x22
	beq	.L100
	ldr	w1, [x20, 44]
	ldp	w28, w19, [x20, 36]
	sub	w1, w1, #1
	lsl	w26, w1, 6
	sub	w1, w26, w1
	ubfx	x1, x1, 6, 24
	add	w26, w1, 1
	tbz	w19, #31, .L165
.L308:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L165
	.p2align 3
.L100:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L226:
	uxtw	x0, w26
	ldrb	w0, [x24, x0]
	lsl	w3, w28, w0
	sub	w19, w19, w0
	lsl	w0, w26, w0
	str	w0, [x20, 44]
	stp	w3, w19, [x20, 36]
	b	.L234
	.p2align 3
.L168:
	uxtw	x0, w1
	mov	w3, 0
	mov	w5, 3
	ldrb	w26, [x24, x0]
	lsl	w28, w28, w26
	sub	w19, w19, w26
	lsl	w26, w1, w26
	str	w26, [x20, 44]
	stp	w28, w19, [x20, 36]
.L173:
	sub	w26, w26, #1
	ubfx	x26, x26, 1, 24
	add	w26, w26, 1
	tbnz	w19, #31, .L319
.L171:
	lsl	w1, w26, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L172
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w26, w0, w26
	lsl	w0, w21, w5
.L172:
	orr	w3, w3, w0
	ldrb	w0, [x24, w26, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w19, w19, w0
	lsl	w26, w26, w0
	cmn	w5, #1
	stp	w28, w19, [x20, 36]
	str	w26, [x20, 44]
	bne	.L173
.L174:
	add	x0, x24, 256
	ldrb	w3, [x0, w3, sxtw]
	ldrb	w0, [x27, -2]
	sub	w0, w0, #1
	lsl	w4, w0, 1
	cmp	w4, 255
	bgt	.L189
	add	w1, w3, 1
	cmp	w1, w4
	bgt	.L190
	tbnz	x1, 0, .L320
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L190:
	add	w1, w1, 1
.L192:
	strb	w1, [x27, -2]
	ldr	w1, [x20, 44]
	ldp	w28, w19, [x20, 36]
	sub	w1, w1, #1
	lsl	w26, w1, 6
	sub	w26, w26, w1
	ubfx	x0, x26, 6, 24
	add	w26, w0, 1
	tbz	w19, #31, .L195
.L313:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L195
	.p2align 3
.L135:
	uxtw	x0, w1
	mov	w4, 0
	mov	w5, 3
	ldrb	w21, [x24, x0]
	lsl	w28, w28, w21
	sub	w19, w19, w21
	lsl	w21, w1, w21
	str	w21, [x20, 44]
	stp	w28, w19, [x20, 36]
.L140:
	sub	w21, w21, #1
	ubfx	x21, x21, 1, 24
	add	w21, w21, 1
	tbnz	w19, #31, .L321
.L138:
	lsl	w1, w21, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L139
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w21, w0, w21
	lsl	w0, w27, w5
.L139:
	orr	w4, w4, w0
	ldrb	w0, [x24, w21, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w19, w19, w0
	lsl	w21, w21, w0
	cmn	w5, #1
	stp	w28, w19, [x20, 36]
	str	w21, [x20, 44]
	bne	.L140
.L141:
	ldrb	w0, [x25, -1]
	add	x1, x24, 256
	sub	w0, w0, #1
	lsl	w5, w0, 1
	ldrb	w4, [x1, w4, sxtw]
	cmp	w5, 255
	bgt	.L156
	add	w1, w4, 1
	cmp	w1, w5
	bgt	.L157
	tbnz	x1, 0, .L322
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L157:
	add	w1, w1, 1
.L159:
	strb	w1, [x25, -1]
	ldr	w1, [x20, 44]
	ldp	w28, w19, [x20, 36]
	sub	w1, w1, #1
	lsl	w21, w1, 6
	sub	w1, w21, w1
	ubfx	x1, x1, 6, 24
	add	w21, w1, 1
	tbz	w19, #31, .L162
.L307:
	sub	w5, w26, w19
	mov	w0, 16
	and	w5, w5, -8
	sub	w4, w0, w19
	sub	w4, w4, w5
	mov	w1, w5
	mov	x0, x20
	stp	w4, w5, [x29, 104]
	bl	BsGet
	ldp	w4, w5, [x29, 104]
	and	w4, w4, 7
	add	w19, w5, w19
	lsl	w0, w0, w4
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L162
	.p2align 3
.L104:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w25, [x24, x0]
	lsl	w28, w28, w25
	sub	w19, w19, w25
	lsl	w25, w1, w25
	str	w25, [x20, 44]
	stp	w28, w19, [x20, 36]
.L109:
	sub	w25, w25, #1
	ubfx	x25, x25, 1, 24
	add	w25, w25, 1
	tbnz	w19, #31, .L323
.L107:
	lsl	w1, w25, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L108
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w25, w0, w25
	lsl	w0, w27, w4
.L108:
	orr	w3, w3, w0
	ldrb	w0, [x24, w25, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w19, w19, w0
	lsl	w25, w25, w0
	cmn	w4, #1
	stp	w28, w19, [x20, 36]
	str	w25, [x20, 44]
	bne	.L109
.L110:
	add	x0, x24, 256
	ldrb	w3, [x0, w3, sxtw]
	ldrb	w0, [x22, x26]
	sub	w0, w0, #1
	lsl	w4, w0, 1
	cmp	w4, 255
	bgt	.L125
	add	w1, w3, 1
	cmp	w1, w4
	bgt	.L126
	tbnz	x1, 0, .L324
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L126:
	add	w1, w1, 1
.L128:
	strb	w1, [x22, x26]
	ldp	w28, w19, [x20, 36]
	ldr	w1, [x20, 44]
	b	.L229
	.p2align 3
.L198:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w26, [x24, x1]
	lsl	w28, w28, w26
	sub	w19, w19, w26
	lsl	w26, w0, w26
	str	w26, [x20, 44]
	stp	w28, w19, [x20, 36]
.L203:
	sub	w26, w26, #1
	ubfx	x26, x26, 1, 24
	add	w26, w26, 1
	tbnz	w19, #31, .L325
.L201:
	lsl	w1, w26, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L202
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w26, w0, w26
	lsl	w0, w21, w5
.L202:
	orr	w3, w3, w0
	ldrb	w0, [x24, w26, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w19, w19, w0
	lsl	w26, w26, w0
	cmn	w5, #1
	stp	w28, w19, [x20, 36]
	str	w26, [x20, 44]
	bne	.L203
.L204:
	add	x0, x24, 256
	ldrb	w3, [x0, w3, sxtw]
	ldrb	w0, [x27, -1]
	sub	w0, w0, #1
	lsl	w4, w0, 1
	cmp	w4, 255
	bgt	.L219
	add	w1, w3, 1
	cmp	w1, w4
	bgt	.L220
	tbnz	x1, 0, .L326
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L220:
	add	w1, w1, 1
.L222:
	strb	w1, [x27, -1]
	ldr	w0, [x20, 44]
	ldp	w28, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w26, w0, 6
	sub	w0, w26, w0
	ubfx	x0, x0, 6, 24
	add	w26, w0, 1
	tbz	w19, #31, .L225
.L318:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w3, w0, w28
	mov	w28, w3
	stp	w3, w19, [x20, 36]
	b	.L225
	.p2align 3
.L189:
	sub	w0, w25, w0
	add	w1, w3, 1
	cmp	w1, w0, lsl 1
	bgt	.L193
	tbnz	x1, 0, .L327
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L193:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L192
	.p2align 3
.L125:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w3, 1
	cmp	w1, w0, lsl 1
	bgt	.L129
	tbnz	x1, 0, .L328
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L129:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L128
	.p2align 3
.L219:
	sub	w0, w25, w0
	add	w1, w3, 1
	cmp	w1, w0, lsl 1
	bgt	.L223
	tbnz	x1, 0, .L329
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L223:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L222
	.p2align 3
.L156:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w4, 1
	cmp	w1, w0, lsl 1
	bgt	.L160
	tbnz	x1, 0, .L330
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L160:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L159
	.p2align 3
.L302:
	sub	w5, w26, w19
	mov	w0, 16
	and	w5, w5, -8
	sub	w4, w0, w19
	sub	w4, w4, w5
	mov	w1, w5
	mov	x0, x20
	stp	w4, w5, [x29, 104]
	bl	BsGet
	ldp	w4, w5, [x29, 104]
	and	w4, w4, 7
	add	w19, w5, w19
	lsl	w0, w0, w4
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L132
	.p2align 3
.L297:
	sub	w4, w23, w19
	sub	w3, w21, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L101
	.p2align 3
.L325:
	mov	w0, 24
	sub	w4, w23, w19
	sub	w1, w0, w19
	mov	x0, x20
	and	w1, w1, -8
	sub	w4, w4, w1
	add	w19, w1, w19
	stp	w5, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldp	w5, w3, [x29, 100]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L201
	.p2align 3
.L323:
	sub	w1, w23, w19
	sub	w5, w21, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w5, w5, w1
	add	w19, w1, w19
	stp	w4, w3, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w4, w3, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L107
	.p2align 3
.L321:
	sub	w1, w26, w19
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w19
	sub	w6, w6, w1
	mov	x0, x20
	stp	w5, w4, [x29, 100]
	str	w6, [x29, 108]
	add	w19, w1, w19
	bl	BsGet
	ldr	w6, [x29, 108]
	ldp	w5, w4, [x29, 100]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w28, w0, w28
	b	.L138
	.p2align 3
.L319:
	mov	w0, 24
	sub	w4, w23, w19
	sub	w1, w0, w19
	mov	x0, x20
	and	w1, w1, -8
	sub	w4, w4, w1
	add	w19, w1, w19
	stp	w5, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldp	w5, w3, [x29, 100]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L171
	.p2align 3
.L142:
	uxtw	x1, w0
	mov	w5, 3
	ldrb	w4, [x24, x1]
	lsl	w1, w28, w4
	sub	w28, w19, w4
	lsl	w19, w0, w4
	mov	w4, 0
	stp	w1, w28, [x20, 36]
	str	w19, [x20, 44]
.L147:
	sub	w19, w19, #1
	mov	w21, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w28, #31, .L331
.L145:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w21
	bhi	.L146
	ldr	w0, [x20, 44]
	sub	w21, w21, w1
	sub	w19, w0, w19
	lsl	w0, w27, w5
.L146:
	orr	w4, w4, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w5, w5, #1
	lsl	w1, w21, w0
	sub	w28, w28, w0
	lsl	w19, w19, w0
	cmn	w5, #1
	stp	w1, w28, [x20, 36]
	str	w19, [x20, 44]
	bne	.L147
	add	w4, w4, 16
	b	.L141
	.p2align 3
.L111:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w1, [x24, x1]
	lsl	w25, w28, w1
	sub	w28, w19, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w25, w28, [x20, 36]
.L116:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w28, #31, .L332
.L114:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L115
	ldr	w0, [x20, 44]
	sub	w25, w25, w1
	sub	w19, w0, w19
	lsl	w0, w27, w4
.L115:
	orr	w3, w3, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w28, w28, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w25, w28, [x20, 36]
	str	w19, [x20, 44]
	bne	.L116
	add	w3, w3, 16
	b	.L110
	.p2align 3
.L175:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w1, [x24, x1]
	lsl	w26, w28, w1
	sub	w28, w19, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w26, w28, [x20, 36]
.L180:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w28, #31, .L333
.L178:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L179
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L179:
	orr	w3, w3, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w28, w28, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w28, [x20, 36]
	str	w19, [x20, 44]
	bne	.L180
	add	w3, w3, 16
	b	.L174
	.p2align 3
.L205:
	uxtw	x1, w0
	mov	w4, 3
	ldrb	w19, [x24, x1]
	lsl	w26, w28, w19
	sub	w28, w3, w19
	lsl	w19, w0, w19
	mov	w3, 0
	stp	w26, w28, [x20, 36]
	str	w19, [x20, 44]
.L210:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w28, #31, .L334
.L208:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L209
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L209:
	orr	w3, w3, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w28, w28, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w28, [x20, 36]
	str	w19, [x20, 44]
	bne	.L210
	add	w3, w3, 16
	b	.L204
	.p2align 3
.L309:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L167
	.p2align 3
.L314:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L197
	.p2align 3
.L303:
	sub	w5, w26, w19
	mov	w0, 16
	and	w5, w5, -8
	sub	w4, w0, w19
	sub	w4, w4, w5
	mov	w1, w5
	mov	x0, x20
	stp	w4, w5, [x29, 104]
	bl	BsGet
	ldp	w4, w5, [x29, 104]
	and	w4, w4, 7
	add	w19, w5, w19
	lsl	w0, w0, w4
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L134
	.p2align 3
.L298:
	sub	w4, w23, w19
	sub	w3, w21, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w28, w0, w28
	stp	w28, w19, [x20, 36]
	b	.L103
	.p2align 3
.L320:
	add	w1, w3, 2
	sub	w1, w0, w1, lsr 1
	b	.L190
	.p2align 3
.L324:
	add	w1, w3, 2
	sub	w1, w0, w1, lsr 1
	b	.L126
	.p2align 3
.L322:
	add	w1, w4, 2
	sub	w1, w0, w1, lsr 1
	b	.L157
	.p2align 3
.L326:
	add	w1, w3, 2
	sub	w1, w0, w1, lsr 1
	b	.L220
	.p2align 3
.L334:
	mov	w0, 24
	sub	w5, w23, w28
	sub	w1, w0, w28
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w28, w1, w28
	stp	w3, w4, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w3, w4, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L208
	.p2align 3
.L333:
	mov	w0, 24
	sub	w5, w23, w28
	sub	w1, w0, w28
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w28, w1, w28
	stp	w3, w4, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w3, w4, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L178
	.p2align 3
.L332:
	sub	w1, w23, w28
	sub	w5, w21, w28
	and	w1, w1, -8
	mov	x0, x20
	sub	w5, w5, w1
	add	w28, w1, w28
	stp	w4, w3, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w4, w3, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L114
	.p2align 3
.L331:
	sub	w1, w26, w28
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w28
	sub	w6, w6, w1
	mov	x0, x20
	stp	w5, w4, [x29, 100]
	str	w6, [x29, 108]
	add	w28, w1, w28
	bl	BsGet
	ldr	w6, [x29, 108]
	ldp	w5, w4, [x29, 100]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w21, w0, w21
	b	.L145
	.p2align 3
.L327:
	add	w3, w3, 2
	sub	w1, w0, w3, lsr 1
	b	.L193
	.p2align 3
.L328:
	add	w3, w3, 2
	sub	w1, w0, w3, lsr 1
	b	.L129
	.p2align 3
.L330:
	add	w4, w4, 2
	sub	w1, w0, w4, lsr 1
	b	.L160
	.p2align 3
.L329:
	add	w3, w3, 2
	sub	w1, w0, w3, lsr 1
	b	.L223
.L211:
	uxtw	x1, w0
	mov	w28, 0
	mov	w4, 4
	ldrb	w19, [x24, x1]
	lsl	w26, w26, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	.p2align 2
.L215:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w3, #31, .L335
.L213:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L214
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L214:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w3, [x20, 36]
	str	w19, [x20, 44]
	bne	.L215
	add	w3, w28, 32
	b	.L204
.L181:
	uxtw	x1, w0
	mov	w28, 0
	mov	w4, 4
	ldrb	w19, [x24, x1]
	lsl	w26, w26, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w26, w3, [x20, 36]
	.p2align 2
.L185:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w3, #31, .L336
.L183:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L184
	ldr	w0, [x20, 44]
	sub	w26, w26, w1
	sub	w19, w0, w19
	lsl	w0, w21, w4
.L184:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w26, w3, [x20, 36]
	str	w19, [x20, 44]
	bne	.L185
	add	w3, w28, 32
	b	.L174
.L148:
	uxtw	x1, w0
	mov	w5, 4
	ldrb	w19, [x24, x1]
	sub	w4, w28, w19
	lsl	w1, w21, w19
	mov	w28, 0
	lsl	w19, w0, w19
	stp	w1, w4, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L152:
	sub	w19, w19, #1
	mov	w21, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w4, #31, .L337
.L150:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w21
	bhi	.L151
	ldr	w0, [x20, 44]
	sub	w21, w21, w1
	sub	w19, w0, w19
	lsl	w0, w27, w5
.L151:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w5, w5, #1
	lsl	w1, w21, w0
	sub	w4, w4, w0
	lsl	w19, w19, w0
	cmn	w5, #1
	stp	w1, w4, [x20, 36]
	str	w19, [x20, 44]
	bne	.L152
	add	w4, w28, 32
	b	.L141
.L117:
	uxtw	x1, w0
	mov	w28, 0
	mov	w4, 4
	ldrb	w19, [x24, x1]
	lsl	w25, w25, w19
	sub	w3, w3, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w25, w3, [x20, 36]
	.p2align 2
.L121:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w3, #31, .L338
.L119:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L120
	ldr	w0, [x20, 44]
	sub	w25, w25, w1
	sub	w19, w0, w19
	lsl	w0, w27, w4
.L120:
	orr	w28, w28, w0
	ldrb	w0, [x24, w19, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w3, w3, w0
	lsl	w19, w19, w0
	cmn	w4, #1
	stp	w25, w3, [x20, 36]
	str	w19, [x20, 44]
	bne	.L121
	add	w3, w28, 32
	b	.L110
	.p2align 3
.L335:
	mov	w0, 24
	sub	w5, w23, w3
	sub	w1, w0, w3
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L213
	.p2align 3
.L337:
	sub	w1, w26, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w4
	sub	w6, w6, w1
	add	w4, w1, w4
	mov	x0, x20
	str	w4, [x29, 108]
	stp	w5, w6, [x29, 100]
	bl	BsGet
	ldp	w5, w6, [x29, 100]
	ldr	w4, [x29, 108]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w21, w0, w21
	b	.L150
	.p2align 3
.L336:
	mov	w0, 24
	sub	w5, w23, w3
	sub	w1, w0, w3
	mov	x0, x20
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L183
	.p2align 3
.L338:
	sub	w1, w23, w3
	sub	w5, w21, w3
	and	w1, w1, -8
	mov	x0, x20
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L119
	.p2align 3
.L304:
	sub	w4, w26, w19
	mov	w0, 16
	and	w4, w4, -8
	sub	w5, w0, w19
	sub	w5, w5, w4
	mov	w1, w4
	mov	x0, x20
	stp	w5, w4, [x29, 104]
	bl	BsGet
	ldp	w5, w4, [x29, 104]
	and	w5, w5, 7
	add	w19, w4, w19
	lsl	w0, w0, w5
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w19, [x20, 36]
	b	.L137
	.p2align 3
.L299:
	sub	w4, w23, w19
	sub	w3, w21, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w0, w0, w28
	mov	w28, w0
	stp	w0, w19, [x20, 36]
	b	.L106
	.p2align 3
.L315:
	mov	w0, 24
	sub	w19, w23, w3
	sub	w4, w0, w3
	mov	x0, x20
	and	w4, w4, -8
	mov	w1, w4
	sub	w19, w19, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	and	w1, w19, 7
	lsl	w0, w0, w1
	ldp	w3, w4, [x29, 104]
	orr	w1, w0, w28
	add	w3, w4, w3
	mov	w28, w1
	stp	w1, w3, [x20, 36]
	b	.L200
	.p2align 3
.L310:
	mov	w0, 24
	sub	w3, w23, w19
	sub	w4, w0, w19
	mov	x0, x20
	and	w4, w4, -8
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w19, w4, w19
	lsl	w0, w0, w3
	orr	w0, w0, w28
	mov	w28, w0
	stp	w0, w19, [x20, 36]
	b	.L170
.L306:
	cmp	w21, 64
	mov	w19, w21
	bgt	.L339
	add	w4, w19, 64
	b	.L141
.L339:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w21, lsl 1
	sub	w19, w0, #65
	add	w4, w19, 64
	b	.L141
.L317:
	cmp	w28, 64
	mov	w19, w28
	bgt	.L340
	add	w3, w19, 64
	b	.L204
.L340:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w19, w0, #65
	add	w3, w19, 64
	b	.L204
.L312:
	cmp	w28, 64
	mov	w19, w28
	bgt	.L341
	add	w3, w19, 64
	b	.L174
.L341:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w19, w0, #65
	add	w3, w19, 64
	b	.L174
.L301:
	cmp	w28, 64
	mov	w19, w28
	bgt	.L342
	add	w3, w19, 64
	b	.L110
.L342:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w19, w0, #65
	add	w3, w19, 64
	b	.L110
.L300:
	sub	w4, w23, w3
	mov	x0, x20
	and	w4, w4, -8
	sub	w28, w21, w3
	mov	w1, w4
	sub	w28, w28, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	and	w28, w28, 7
	ldp	w3, w4, [x29, 104]
	lsl	w0, w0, w28
	orr	w25, w0, w25
	add	w3, w3, w4
	stp	w25, w3, [x20, 36]
	b	.L113
.L316:
	mov	w0, 24
	sub	w28, w23, w3
	sub	w4, w0, w3
	mov	x0, x20
	and	w4, w4, -8
	mov	w1, w4
	sub	w28, w28, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	and	w28, w28, 7
	ldp	w3, w4, [x29, 104]
	lsl	w0, w0, w28
	orr	w26, w0, w26
	add	w3, w4, w3
	stp	w26, w3, [x20, 36]
	b	.L207
.L305:
	sub	w4, w26, w28
	mov	w0, 16
	and	w4, w4, -8
	sub	w5, w0, w28
	sub	w5, w5, w4
	mov	w1, w4
	mov	x0, x20
	stp	w5, w4, [x29, 104]
	bl	BsGet
	ldp	w5, w4, [x29, 104]
	and	w5, w5, 7
	add	w4, w28, w4
	lsl	w0, w0, w5
	mov	w28, w4
	orr	w1, w0, w21
	mov	w21, w1
	stp	w1, w4, [x20, 36]
	b	.L144
.L311:
	mov	w0, 24
	sub	w28, w23, w3
	sub	w4, w0, w3
	mov	x0, x20
	and	w4, w4, -8
	mov	w1, w4
	sub	w28, w28, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	and	w28, w28, 7
	ldp	w3, w4, [x29, 104]
	lsl	w0, w0, w28
	orr	w26, w0, w26
	add	w3, w4, w3
	stp	w26, w3, [x20, 36]
	b	.L177
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
	.align	3
.LC8:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCoefProbsCommon
	.type	Vp9_ReadCoefProbsCommon, %function
Vp9_ReadCoefProbsCommon:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldp	w22, w19, [x27, 40]
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L344
	ldr	w0, [x27, 36]
.L345:
	lsl	w2, w19, 24
	cmp	w2, w0
	bhi	.L346
	ldr	w1, [x27, 44]
	sub	w0, w0, w2
	ldr	x28, .LC10
	mov	w23, 24
	sub	w19, w1, w19
	add	x1, x21, 1024
	str	x1, [x29, 104]
	ldrb	w2, [x28, w19, uxtw]
	sub	w1, w22, w2
	lsl	w0, w0, w2
	lsl	w19, w19, w2
	str	w0, [x27, 36]
	str	w19, [x27, 44]
	mov	w22, 16
	str	w1, [x27, 40]
.L347:
	str	x21, [x29, 112]
	str	wzr, [x29, 124]
.L451:
	ldr	x0, [x29, 112]
	str	x0, [x29, 160]
	ldr	w0, [x29, 124]
	str	wzr, [x29, 172]
	sbfiz	x0, x0, 3, 32
	str	x0, [x29, 128]
	.p2align 2
.L449:
	ldr	w0, [x29, 172]
	mov	w26, 0
	ldr	x1, [x29, 128]
	cmp	w0, wzr
	ldr	x25, [x29, 160]
	add	x19, x1, x0, sxtw
	mov	w0, 3
	mov	w1, 6
	lsl	x19, x19, 3
	csel	w20, w0, w1, eq
	cmp	w26, w20
	bge	.L506
	.p2align 2
.L445:
	ldp	w2, w0, [x27, 40]
	add	x6, x19, x26, sxtw
	sub	w1, w0, #1
	lsl	w0, w1, 6
	add	x24, x21, x6, lsl 2
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L348
	ldr	w4, [x27, 36]
.L349:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L350
	ldr	w0, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L507
.L351:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L352
	ldr	w0, [x27, 44]
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x28, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L508
.L354:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L359
	ldr	w9, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L509
.L361:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L365
	sub	w12, w4, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L366
	.p2align 3
.L370:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L371
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L371:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L510
.L366:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L370
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L370
	.p2align 3
.L350:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w4, w2, [x27, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L511
.L381:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L382
	ldr	w0, [x27, 44]
	sub	w1, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w1, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L512
.L383:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L384
	ldr	w0, [x27, 44]
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x28, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L513
.L386:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L391
	ldr	w9, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L514
.L393:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L397
	sub	w12, w4, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L398
	.p2align 3
.L402:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L403
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L403:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L515
.L398:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L402
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L402
	.p2align 3
.L382:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w9, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w9, w2, [x27, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L516
.L413:
	lsl	w1, w10, 24
	cmp	w1, w9
	bhi	.L414
	ldr	w0, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w0, w10
	ldrb	w4, [x28, w0, uxtw]
	lsl	w12, w1, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L517
.L415:
	sub	w4, w4, #1
	ubfx	x4, x4, 1, 24
	add	w0, w4, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L416
	ldr	w4, [x27, 44]
	sub	w1, w12, w1
	sub	w4, w4, w0
	ldrb	w0, [x28, w4, uxtw]
	lsl	w12, w1, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	str	w4, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L518
.L418:
	sub	w0, w4, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L423
	ldr	w4, [x27, 44]
	sub	w1, w12, w1
	sub	w0, w4, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w12, w1, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L519
.L425:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L429
	sub	w12, w12, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L430
	.p2align 3
.L434:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L435
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L435:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L520
.L430:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L434
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L434
	.p2align 3
.L414:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w1, w9, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L454:
	add	w26, w26, 1
	add	x25, x25, 4
	cmp	w26, w20
	blt	.L445
.L506:
	ldr	w0, [x29, 172]
	ldr	x1, [x29, 160]
	add	w0, w0, 1
	str	w0, [x29, 172]
	add	x1, x1, 32
	cmp	w0, 6
	str	x1, [x29, 160]
	bne	.L449
	ldr	w0, [x29, 124]
	ldr	x1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 124]
	add	x1, x1, 256
	cmp	w0, 2
	str	x1, [x29, 112]
	bne	.L451
	ldr	x0, [x29, 104]
	add	x21, x21, 512
	cmp	x0, x21
	bne	.L347
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L416:
	uxtw	x1, w0
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w4, [x28, x1]
	lsl	w1, w12, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x27, 44]
	stp	w1, w2, [x27, 36]
.L421:
	sub	w4, w4, #1
	mov	w12, w1
	ubfx	x4, x4, 1, 24
	add	w4, w4, 1
	tbnz	w2, #31, .L521
.L419:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L420
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w4, w13, w4
.L420:
	orr	w9, w9, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	cmn	w10, #1
	stp	w1, w2, [x27, 36]
	str	w4, [x27, 44]
	bne	.L421
.L422:
	ldrb	w1, [x24, 2]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L439
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L440
	tbnz	x0, 0, .L522
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L440:
	add	w0, w0, 1
.L442:
	strb	w0, [x24, 2]
	b	.L454
	.p2align 3
.L384:
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x27, 44]
	stp	w4, w2, [x27, 36]
.L389:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L523
.L387:
	lsl	w1, w12, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L388
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w13, w12
.L388:
	orr	w9, w9, w0
	ldrb	w0, [x28, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L389
.L390:
	ldrb	w1, [x24, 1]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L407
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L408
	tbnz	x0, 0, .L524
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L408:
	add	w0, w0, 1
.L410:
	strb	w0, [x24, 1]
	ldr	w0, [x27, 44]
	ldp	w9, w2, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L413
.L516:
	sub	w11, w23, w2
	sub	w4, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w4, w4, w11
	mov	w1, w11
	stp	w9, w10, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldr	w4, [x29, 168]
	ldp	w9, w10, [x29, 144]
	and	w4, w4, 7
	ldp	w2, w11, [x29, 152]
	lsl	w0, w0, w4
	orr	w1, w0, w9
	add	w2, w11, w2
	mov	w9, w1
	stp	w1, w2, [x27, 36]
	b	.L413
	.p2align 3
.L352:
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x27, 44]
	stp	w4, w2, [x27, 36]
.L357:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L525
.L355:
	lsl	w1, w12, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L356
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w13, w12
.L356:
	orr	w9, w9, w0
	ldrb	w0, [x28, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L357
.L358:
	ldrb	w1, [x25]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L375
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L376
	tbnz	x0, 0, .L526
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L376:
	add	w0, w0, 1
.L378:
	strb	w0, [x25]
	ldr	w0, [x27, 44]
	ldp	w4, w2, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L381
.L511:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w4, w10, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w9, [x29, 168]
	bl	BsGet
	ldr	w9, [x29, 168]
	ldp	w4, w10, [x29, 144]
	and	w9, w9, 7
	ldp	w2, w11, [x29, 152]
	lsl	w0, w0, w9
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L381
	.p2align 3
.L375:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L379
	tbnz	x4, 0, .L527
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L379:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L378
	.p2align 3
.L407:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L411
	tbnz	x4, 0, .L528
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L411:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L410
	.p2align 3
.L439:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L443
	tbnz	x4, 0, .L529
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L443:
	mov	w0, 255
	sub	w0, w0, w4
	strb	w0, [x24, 2]
	b	.L454
	.p2align 3
.L348:
	sub	w11, w23, w2
	sub	w4, w22, w2
	and	w11, w11, -8
	ldr	w9, [x27, 36]
	sub	w4, w4, w11
	mov	w1, w11
	mov	x0, x27
	str	w9, [x29, 168]
	stp	w10, w2, [x29, 144]
	stp	w11, w4, [x29, 152]
	bl	BsGet
	ldp	w11, w4, [x29, 152]
	ldp	w10, w2, [x29, 144]
	and	w4, w4, 7
	ldr	w9, [x29, 168]
	lsl	w0, w0, w4
	add	w2, w2, w11
	orr	w4, w0, w9
	stp	w4, w2, [x27, 36]
	b	.L349
	.p2align 3
.L521:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w12, [x29, 136]
	stp	w4, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L419
	.p2align 3
.L525:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w4, [x29, 136]
	stp	w12, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w4, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 144]
	orr	w4, w0, w4
	b	.L355
	.p2align 3
.L523:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w4, [x29, 136]
	stp	w12, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w4, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 144]
	orr	w4, w0, w4
	b	.L387
	.p2align 3
.L423:
	uxtw	x1, w0
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w13, [x28, x1]
	sub	w4, w2, w13
	lsl	w1, w12, w13
	lsl	w2, w0, w13
	str	w2, [x27, 44]
	stp	w1, w4, [x27, 36]
.L428:
	sub	w2, w2, #1
	mov	w12, w1
	ubfx	x2, x2, 1, 24
	add	w2, w2, 1
	tbnz	w4, #31, .L530
.L426:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L427
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L427:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	lsl	w2, w2, w0
	cmn	w10, #1
	stp	w1, w4, [x27, 36]
	str	w2, [x27, 44]
	bne	.L428
	add	w9, w9, 16
	b	.L422
	.p2align 3
.L359:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L364:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L531
.L362:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L363
	ldr	w13, [x27, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w13, w4
.L363:
	orr	w10, w10, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L364
	add	w9, w10, 16
	b	.L358
	.p2align 3
.L391:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L396:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L532
.L394:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L395
	ldr	w13, [x27, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w13, w4
.L395:
	orr	w10, w10, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L396
	add	w9, w10, 16
	b	.L390
	.p2align 3
.L517:
	sub	w10, w23, w2
	sub	w9, w22, w2
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w4, w12, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w9, [x29, 168]
	bl	BsGet
	ldr	w9, [x29, 168]
	ldp	w4, w12, [x29, 144]
	and	w9, w9, 7
	ldp	w2, w10, [x29, 152]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x27, 36]
	b	.L415
	.p2align 3
.L507:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w4, w9, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldr	w10, [x29, 168]
	ldp	w4, w9, [x29, 144]
	ldp	w2, w11, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L351
	.p2align 3
.L512:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w9, w4, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldr	w10, [x29, 168]
	ldp	w9, w4, [x29, 144]
	ldp	w2, w11, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w2, w11
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L383
	.p2align 3
.L526:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L376
	.p2align 3
.L522:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	add	w0, w0, 1
	b	.L442
	.p2align 3
.L524:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L408
	.p2align 3
.L531:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w12, w9, [x29, 136]
	stp	w4, w11, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w12, w9, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 144]
	orr	w9, w0, w9
	b	.L362
	.p2align 3
.L532:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w12, w9, [x29, 136]
	stp	w4, w11, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w12, w9, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 144]
	orr	w9, w0, w9
	b	.L394
	.p2align 3
.L530:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L426
	.p2align 3
.L528:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L411
	.p2align 3
.L527:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L379
	.p2align 3
.L529:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L443
.L365:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x27, 44]
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	.p2align 2
.L369:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L533
.L367:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L368
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L368:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L369
	add	w9, w9, 32
	b	.L358
.L397:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x27, 44]
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	.p2align 2
.L401:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L534
.L399:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L400
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L400:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L401
	add	w9, w9, 32
	b	.L390
.L429:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w12, w9
	sub	w4, w2, w9
	lsl	w0, w0, w9
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L433:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L535
.L431:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L432
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L432:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L433
	add	w9, w9, 32
	b	.L422
	.p2align 3
.L535:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L431
	.p2align 3
.L534:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L399
	.p2align 3
.L533:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L367
	.p2align 3
.L518:
	sub	w10, w23, w2
	sub	w9, w22, w2
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w4, w12, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w4, w12, [x29, 144]
	and	w9, w9, 7
	ldr	w10, [x29, 168]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x27, 36]
	b	.L418
	.p2align 3
.L513:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w10, w4, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w10, w4, [x29, 144]
	ldr	w11, [x29, 168]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L386
	.p2align 3
.L508:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w4, w10, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w4, w10, [x29, 144]
	ldr	w11, [x29, 168]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L354
.L510:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L536
	add	w9, w9, 64
	b	.L358
.L520:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L537
	add	w9, w9, 64
	b	.L422
.L515:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L538
	add	w9, w9, 64
	b	.L390
.L538:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w10, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L539
.L405:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L406
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L406:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w0, w12, w1
	lsl	w2, w2, w1
	str	w0, [x27, 36]
	sub	w0, w4, w1
	str	w2, [x27, 44]
	str	w0, [x27, 40]
	b	.L390
.L537:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w10, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L540
.L437:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L438
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L438:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w0, w12, w1
	lsl	w2, w2, w1
	str	w0, [x27, 36]
	sub	w0, w4, w1
	str	w2, [x27, 44]
	str	w0, [x27, 40]
	b	.L422
.L536:
	sub	w2, w0, #1
	lsl	w9, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w9, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L541
.L373:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L374
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L374:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w12, w12, w1
	sub	w0, w4, w1
	lsl	w2, w2, w1
	str	w2, [x27, 44]
	stp	w12, w0, [x27, 36]
	b	.L358
.L519:
	sub	w4, w23, w2
	sub	w10, w22, w2
	and	w4, w4, -8
	mov	x0, x27
	sub	w10, w10, w4
	mov	w1, w4
	stp	w9, w12, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w9, w12, [x29, 144]
	ldr	w4, [x29, 168]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w4, w4, w2
	orr	w1, w0, w12
	mov	w2, w4
	mov	w12, w1
	stp	w1, w4, [x27, 36]
	b	.L425
.L514:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w9, w4, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w9, w4, [x29, 144]
	and	w10, w10, 7
	ldr	w11, [x29, 168]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L393
.L509:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w4, w9, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w4, w9, [x29, 144]
	and	w10, w10, 7
	ldr	w11, [x29, 168]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L361
.L346:
	ldr	x2, .LC10
	uxtw	x1, w19
	ldrb	w2, [x2, x1]
	sub	w1, w22, w2
	lsl	w19, w19, w2
	lsl	w0, w0, w2
	str	w19, [x27, 44]
	stp	w0, w1, [x27, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L344:
	mov	w23, 24
	mov	w24, 16
	sub	w23, w23, w22
	sub	w24, w24, w22
	and	w23, w23, -8
	mov	x0, x27
	mov	w1, w23
	sub	w24, w24, w23
	ldr	w20, [x27, 36]
	and	w24, w24, 7
	bl	BsGet
	lsl	w0, w0, w24
	add	w1, w22, w23
	orr	w0, w0, w20
	mov	w22, w1
	stp	w0, w1, [x27, 36]
	b	.L345
.L541:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L373
.L540:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L437
.L539:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L405
	.size	Vp9_ReadCoefProbsCommon, .-Vp9_ReadCoefProbsCommon
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCoefProbs
	.type	Vp9_ReadCoefProbs, %function
Vp9_ReadCoefProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadCoefProbsCommon
	cbnz	w21, .L548
.L542:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L548:
	mov	x1, x20
	add	x0, x19, 1024
	bl	Vp9_ReadCoefProbsCommon
	cmp	w21, 1
	bls	.L544
	mov	x1, x20
	add	x0, x19, 2048
	bl	Vp9_ReadCoefProbsCommon
.L544:
	cmp	w21, 2
	bls	.L542
	mov	x1, x20
	add	x0, x19, 3072
	bl	Vp9_ReadCoefProbsCommon
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_ReadCoefProbs, .-Vp9_ReadCoefProbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadInterModeProbs
	.type	Vp9_ReadInterModeProbs, %function
Vp9_ReadInterModeProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x21, x21, 4096
	mov	x19, x1
	bl	_mcount
	ldr	x25, .LC12
	add	x26, x21, 345
	mov	w23, 24
	add	x21, x21, 366
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
	.p2align 2
.L641:
	ldp	w2, w1, [x19, 40]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w1, w0, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L550
	ldr	w28, [x19, 36]
.L551:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L552
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L693
.L553:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L554
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L694
.L556:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L561
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L695
.L563:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L567
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w3, 0
	mov	w4, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L568
	.p2align 3
.L572:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L573
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L573:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L696
.L568:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L572
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L572
	.p2align 3
.L552:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	stp	w28, w2, [x19, 36]
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L697
.L581:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L582
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L698
.L583:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L584
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L699
.L586:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L591
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L700
.L593:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L597
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w3, 0
	mov	w4, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L598
	.p2align 3
.L602:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L603
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L603:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L701
.L598:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L602
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L602
	.p2align 3
.L582:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	stp	w28, w2, [x19, 36]
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L702
.L611:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L612
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L703
.L613:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L614
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L704
.L616:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L621
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L705
.L623:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L627
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w3, 0
	mov	w4, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L628
	.p2align 3
.L632:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L633
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L633:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L706
.L628:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L632
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L632
	.p2align 3
.L612:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	stp	w28, w2, [x19, 36]
.L644:
	add	x26, x26, 3
	cmp	x26, x21
	bne	.L641
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L614:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L619:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L707
.L617:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L618
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L618:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L619
.L620:
	ldrb	w0, [x26]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L635
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L636
	tbnz	x1, 0, .L708
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L636:
	add	w1, w1, 1
.L638:
	strb	w1, [x26]
	b	.L644
	.p2align 3
.L584:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L589:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L709
.L587:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L588
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L588:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L589
.L590:
	ldrb	w0, [x26, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L605
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L606
	tbnz	x1, 0, .L710
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L606:
	add	w1, w1, 1
.L608:
	strb	w1, [x26, -1]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L611
.L702:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L611
	.p2align 3
.L554:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L559:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L711
.L557:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L558
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L558:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L559
.L560:
	ldrb	w0, [x26, -2]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L575
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L576
	tbnz	x1, 0, .L712
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L576:
	add	w1, w1, 1
.L578:
	strb	w1, [x26, -2]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L581
.L697:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L581
	.p2align 3
.L635:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L639
	tbnz	x1, 0, .L713
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L639:
	mov	w0, 255
	sub	w1, w0, w1
.L719:
	strb	w1, [x26]
	b	.L644
	.p2align 3
.L575:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L579
	tbnz	x1, 0, .L714
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L579:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L578
	.p2align 3
.L605:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L609
	tbnz	x1, 0, .L715
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L609:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L608
	.p2align 3
.L550:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	ldr	w28, [x19, 36]
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w2, w3
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L551
	.p2align 3
.L707:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L617
	.p2align 3
.L711:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L557
	.p2align 3
.L709:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L587
	.p2align 3
.L708:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L638
	.p2align 3
.L712:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L576
	.p2align 3
.L710:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L606
	.p2align 3
.L621:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L626:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L716
.L624:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L625
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L625:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L626
	add	w3, w3, 16
	b	.L620
	.p2align 3
.L591:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L596:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L717
.L594:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L595
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L595:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L596
	add	w3, w3, 16
	b	.L590
	.p2align 3
.L561:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L566:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L718
.L564:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L565
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L565:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L566
	add	w3, w3, 16
	b	.L560
	.p2align 3
.L698:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L583
	.p2align 3
.L703:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L613
	.p2align 3
.L693:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L553
	.p2align 3
.L716:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L624
	.p2align 3
.L718:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L564
	.p2align 3
.L717:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L594
	.p2align 3
.L713:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L719
	.p2align 3
.L714:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L578
	.p2align 3
.L715:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L608
.L597:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L601:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L720
.L599:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L600
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L600:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L601
	add	w3, w3, 32
	b	.L590
.L567:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L571:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L721
.L569:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L570
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L570:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L571
	add	w3, w3, 32
	b	.L560
.L627:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L631:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L722
.L629:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L630
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L630:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L631
	add	w3, w3, 32
	b	.L620
	.p2align 3
.L722:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L629
	.p2align 3
.L721:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L569
	.p2align 3
.L720:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L599
	.p2align 3
.L694:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L556
	.p2align 3
.L704:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L616
	.p2align 3
.L699:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L586
.L696:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L723
	add	w3, w20, 64
	b	.L560
.L701:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L724
	add	w3, w20, 64
	b	.L590
.L706:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L725
	add	w3, w20, 64
	b	.L620
.L725:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L620
.L724:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L590
.L723:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L560
.L695:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L563
.L705:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L623
.L700:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L593
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x21, x21, 4096
	mov	x19, x1
	bl	_mcount
	ldr	x25, .LC14
	add	x26, x21, 365
	mov	w23, 24
	add	x21, x21, 373
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
.L788:
	ldp	w2, w0, [x19, 40]
	sub	w20, w0, #1
	lsl	w0, w20, 6
	sub	w0, w0, w20
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w2, #31, .L727
	ldr	w28, [x19, 36]
.L728:
	lsl	w1, w20, 24
	cmp	w1, w28
	bhi	.L729
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w0, w0, w20
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L824
.L730:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L731
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L825
.L733:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L738
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L826
.L740:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L744
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w3, 0
	mov	w4, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L745
	.p2align 3
.L749:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L750
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L750:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L827
.L745:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L749
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L749
	.p2align 3
.L729:
	uxtw	x0, w20
	ldrb	w0, [x25, x0]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	stp	w28, w2, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w2, #31, .L828
.L758:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L759
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L829
.L760:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L761
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L830
.L763:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L768
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L831
.L770:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L774
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w3, 0
	mov	w4, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L775
	.p2align 3
.L779:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L780
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L780:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L832
.L775:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L779
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L779
	.p2align 3
.L759:
	uxtw	x0, w20
	ldrb	w0, [x25, x0]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w28, w2, [x19, 36]
.L790:
	add	x26, x26, 2
	cmp	x26, x21
	bne	.L788
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L761:
	uxtw	x0, w1
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L766:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L833
.L764:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L765
	ldr	w4, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w4, w20
.L765:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L766
.L767:
	ldrb	w0, [x26]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L782
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L783
	tbnz	x1, 0, .L834
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L783:
	add	w1, w1, 1
.L785:
	strb	w1, [x26]
	b	.L790
	.p2align 3
.L731:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L736:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L835
.L734:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L735
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L735:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L736
.L737:
	ldrb	w0, [x26, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L752
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L753
	tbnz	x1, 0, .L836
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L753:
	add	w1, w1, 1
.L755:
	strb	w1, [x26, -1]
	ldr	w0, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w2, #31, .L758
.L828:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L758
	.p2align 3
.L752:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L837
	mov	w0, 255
	sub	w1, w0, w1
	b	.L755
	.p2align 3
.L782:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L838
	mov	w0, 255
	sub	w1, w0, w1
.L840:
	strb	w1, [x26]
	b	.L790
	.p2align 3
.L727:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	ldr	w28, [x19, 36]
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w2, w3
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L728
	.p2align 3
.L838:
	tbnz	x1, 0, .L839
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L840
	.p2align 3
.L837:
	tbnz	x1, 0, .L841
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L755
	.p2align 3
.L768:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L773:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L842
.L771:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L772
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L772:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L773
	add	w3, w3, 16
	b	.L767
	.p2align 3
.L738:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L743:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L843
.L741:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L742
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L742:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L743
	add	w3, w3, 16
	b	.L737
	.p2align 3
.L835:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L734
	.p2align 3
.L833:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L764
	.p2align 3
.L841:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L755
	.p2align 3
.L839:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L840
	.p2align 3
.L824:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L730
	.p2align 3
.L829:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L760
	.p2align 3
.L834:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L785
	.p2align 3
.L836:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L753
	.p2align 3
.L843:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L741
	.p2align 3
.L842:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L771
.L774:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L778:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L844
.L776:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L777
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L777:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L778
	add	w3, w3, 32
	b	.L767
.L744:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L748:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L845
.L746:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L747
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L747:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L748
	add	w3, w3, 32
	b	.L737
.L831:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L770
.L826:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L740
	.p2align 3
.L844:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L776
	.p2align 3
.L845:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L746
	.p2align 3
.L825:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L733
	.p2align 3
.L830:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L763
.L832:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L846
	add	w3, w20, 64
	b	.L767
.L846:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L767
.L827:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L847
	add	w3, w20, 64
	b	.L737
.L847:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L737
	.size	Vp9_ReadSwitchableInterpProbs, .-Vp9_ReadSwitchableInterpProbs
	.align	3
.LC14:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCompPred
	.type	Vp9_ReadCompPred, %function
Vp9_ReadCompPred:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	w19, w2
	mov	x0, x30
	mov	x20, x1
	str	x3, [x29, 112]
	bl	_mcount
	cbnz	w19, .L1014
	ldr	x25, .LC16
	add	x21, x21, 4096
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
	str	wzr, [x29, 124]
.L859:
	sub	w0, w0, #1
	add	x23, x21, 334
	lsl	w28, w0, 6
	add	x22, x21, 344
	sub	w0, w28, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w27, 1
	add	w28, w0, 1
	tbnz	w19, #31, .L1015
	.p2align 2
.L861:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L862
	ldr	w0, [x20, 44]
	sub	w5, w26, w1
	sub	w0, w0, w28
	ldrb	w28, [x25, w0, uxtw]
	lsl	w26, w5, w28
	sub	w19, w19, w28
	lsl	w28, w0, w28
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1016
.L863:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L864
	ldr	w28, [x20, 44]
	sub	w1, w26, w1
	sub	w28, w28, w0
	ldrb	w0, [x25, w28, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1017
.L866:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L871
	ldr	w5, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w5, w0
	ldrb	w5, [x25, w0, uxtw]
	sub	w26, w19, w5
	lsl	w28, w1, w5
	lsl	w19, w0, w5
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L1018
.L873:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L877
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w8, [x25, w0, uxtw]
	lsl	w1, w5, w8
	sub	w26, w26, w8
	lsl	w0, w0, w8
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L878
	.p2align 3
.L882:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L883
	ldr	w0, [x20, 44]
	sub	w5, w5, w1
	sub	w28, w0, w28
	lsl	w0, w27, w7
.L883:
	orr	w19, w19, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w7, w7, #1
	lsl	w1, w5, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w28, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1019
.L878:
	sub	w0, w0, #1
	mov	w5, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w26, #31, .L882
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w26
	sub	w8, w8, w1
	mov	x0, x20
	stp	w5, w7, [x29, 104]
	str	w8, [x29, 120]
	add	w26, w1, w26
	bl	BsGet
	ldr	w8, [x29, 120]
	ldp	w5, w7, [x29, 104]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L882
	.p2align 3
.L862:
	uxtw	x0, w28
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w19, w19, w0
	lsl	w0, w28, w0
	str	w0, [x20, 44]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	stp	w26, w19, [x20, 36]
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w19, #31, .L1020
.L891:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L892
	ldr	w0, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w0, w28
	ldrb	w6, [x25, w0, uxtw]
	lsl	w26, w1, w6
	sub	w19, w19, w6
	lsl	w28, w0, w6
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1021
.L893:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L894
	sub	w28, w26, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	ldrb	w1, [x25, w0, uxtw]
	sub	w26, w19, w1
	lsl	w28, w28, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L1022
.L896:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L901
	ldr	w6, [x20, 44]
	sub	w28, w28, w1
	sub	w0, w6, w0
	ldrb	w19, [x25, w0, uxtw]
	lsl	w28, w28, w19
	sub	w26, w26, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L1023
.L903:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L907
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w8, [x25, w0, uxtw]
	lsl	w1, w5, w8
	sub	w26, w26, w8
	lsl	w0, w0, w8
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L908
	.p2align 3
.L912:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L913
	ldr	w0, [x20, 44]
	sub	w5, w5, w1
	sub	w28, w0, w28
	lsl	w0, w27, w7
.L913:
	orr	w19, w19, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w7, w7, #1
	lsl	w1, w5, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w28, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1024
.L908:
	sub	w0, w0, #1
	mov	w5, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w26, #31, .L912
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w26
	sub	w8, w8, w1
	mov	x0, x20
	stp	w5, w7, [x29, 104]
	str	w8, [x29, 120]
	add	w26, w1, w26
	bl	BsGet
	ldr	w8, [x29, 120]
	ldp	w5, w7, [x29, 104]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L912
	.p2align 3
.L892:
	uxtw	x0, w28
	add	x23, x23, 2
	cmp	x23, x22
	ldrb	w0, [x25, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w28, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
	beq	.L921
.L1029:
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L861
.L1015:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L861
	.p2align 3
.L864:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w28, [x25, x1]
	lsl	w5, w26, w28
	sub	w19, w19, w28
	mov	w26, 3
	lsl	w28, w0, w28
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
.L869:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w19, #31, .L1025
.L867:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L868
	ldr	w8, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w28, w8, w28
.L868:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
	bne	.L869
.L870:
	ldrb	w0, [x23, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	ldrb	w5, [x1, w6, sxtw]
	lsl	w6, w0, 1
	cmp	w6, 255
	bgt	.L885
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L886
	tbnz	x1, 0, .L1026
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L886:
	add	w1, w1, 1
.L888:
	strb	w1, [x23, -1]
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L891
.L1020:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L891
	.p2align 3
.L894:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	lsl	w28, w26, w6
	sub	w5, w19, w6
	mov	w26, 3
	lsl	w19, w0, w6
	stp	w28, w5, [x20, 36]
	mov	w6, 0
	str	w19, [x20, 44]
.L899:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1027
.L897:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L898
	ldr	w8, [x20, 44]
	lsl	w0, w27, w26
	sub	w28, w28, w1
	sub	w19, w8, w19
.L898:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L899
.L900:
	ldrb	w0, [x23]
	add	x1, x25, 256
	sub	w0, w0, #1
	ldrb	w5, [x1, w6, sxtw]
	lsl	w6, w0, 1
	cmp	w6, 255
	bgt	.L915
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L916
	tbnz	x1, 0, .L1028
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L916:
	add	w1, w1, 1
.L918:
	strb	w1, [x23]
.L1032:
	add	x23, x23, 2
	cmp	x23, x22
	bne	.L1029
.L921:
	ldr	w0, [x29, 124]
	cbnz	w0, .L1030
.L923:
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 124]
	str	w1, [x0]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L915:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L1031
	mov	w0, 255
	sub	w1, w0, w1
.L1041:
	strb	w1, [x23]
	b	.L1032
	.p2align 3
.L885:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L1033
	mov	w0, 255
	sub	w1, w0, w1
	b	.L888
	.p2align 3
.L1030:
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
.L860:
	sub	w0, w0, #1
	add	x28, x21, 328
	lsl	w1, w0, 6
	add	x21, x21, 333
	sub	w0, w1, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w23, 16
	mov	w27, 1
	add	w22, w0, 1
	tbnz	w19, #31, .L1034
	.p2align 2
.L924:
	lsl	w1, w22, 24
	cmp	w1, w26
	bhi	.L925
	ldr	w0, [x20, 44]
	sub	w5, w26, w1
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w26, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1035
.L926:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w0, w22, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L927
	ldr	w22, [x20, 44]
	sub	w1, w26, w1
	sub	w22, w22, w0
	ldrb	w0, [x25, w22, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1036
.L929:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L934
	ldr	w4, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w4, w0
	ldrb	w4, [x25, w0, uxtw]
	sub	w26, w19, w4
	lsl	w22, w1, w4
	lsl	w19, w0, w4
	str	w19, [x20, 44]
	stp	w22, w26, [x20, 36]
	tbnz	w26, #31, .L1037
.L936:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L940
	sub	w6, w22, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w4, [x25, w0, uxtw]
	lsl	w1, w6, w4
	sub	w26, w26, w4
	lsl	w0, w0, w4
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L941
	.p2align 3
.L945:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L946
	ldr	w0, [x20, 44]
	sub	w4, w4, w1
	sub	w22, w0, w22
	lsl	w0, w27, w7
.L946:
	orr	w19, w19, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w7, w7, #1
	lsl	w1, w4, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w22, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1038
.L941:
	sub	w0, w0, #1
	mov	w4, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w26, #31, .L945
	sub	w1, w24, w26
	sub	w6, w23, w26
	and	w1, w1, -8
	mov	x0, x20
	sub	w6, w6, w1
	add	w26, w1, w26
	stp	w4, w7, [x29, 104]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 120]
	ldp	w4, w7, [x29, 104]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w4, w0, w4
	b	.L945
	.p2align 3
.L1033:
	tbnz	x1, 0, .L1039
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L888
	.p2align 3
.L1031:
	tbnz	x1, 0, .L1040
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1041
	.p2align 3
.L871:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	lsl	w1, w26, w6
	sub	w5, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	mov	w6, 0
	str	w0, [x20, 44]
	stp	w1, w5, [x20, 36]
.L876:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L1042
.L874:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L875
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L875:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L876
	add	w6, w6, 16
	b	.L870
	.p2align 3
.L901:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	sub	w5, w26, w6
	lsl	w1, w28, w6
	lsl	w0, w0, w6
	mov	w26, 3
	mov	w6, 0
	str	w0, [x20, 44]
	stp	w1, w5, [x20, 36]
.L906:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L1043
.L904:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L905
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L905:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L906
	add	w6, w6, 16
	b	.L900
	.p2align 3
.L925:
	uxtw	x0, w22
	ldrb	w0, [x25, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
.L958:
	add	x28, x28, 1
	cmp	x28, x21
	beq	.L923
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbz	w19, #31, .L924
.L1034:
	sub	w6, w24, w19
	sub	w4, w23, w19
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w19, w6, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L924
	.p2align 3
.L927:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w22, [x25, x1]
	lsl	w5, w26, w22
	sub	w19, w19, w22
	mov	w26, 3
	lsl	w22, w0, w22
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
.L932:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w19, #31, .L1044
.L930:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L931
	ldr	w7, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w22, w7, w22
.L931:
	orr	w4, w4, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
	bne	.L932
.L933:
	ldrb	w0, [x28]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w5, w0, 1
	ldrb	w4, [x1, w4, sxtw]
	cmp	w5, 255
	bgt	.L948
	add	w1, w4, 1
	cmp	w1, w5
	bgt	.L949
	tbnz	x1, 0, .L1045
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L949:
	add	w1, w1, 1
.L951:
	strb	w1, [x28]
	b	.L958
	.p2align 3
.L948:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w4, 1
	cmp	w1, w0, lsl 1
	bgt	.L952
	tbnz	x1, 0, .L1046
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L952:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x28]
	b	.L958
	.p2align 3
.L1027:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L897
	.p2align 3
.L1025:
	sub	w1, w24, w19
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w19
	sub	w8, w8, w1
	mov	x0, x20
	stp	w5, w6, [x29, 104]
	str	w8, [x29, 120]
	add	w19, w1, w19
	bl	BsGet
	ldr	w8, [x29, 120]
	ldp	w5, w6, [x29, 104]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L867
	.p2align 3
.L1044:
	sub	w1, w24, w19
	sub	w7, w23, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w19, w1, w19
	stp	w5, w4, [x29, 104]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 120]
	ldp	w5, w4, [x29, 104]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w5, w0, w5
	b	.L930
	.p2align 3
.L1014:
	ldp	w19, w0, [x20, 40]
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w19, #31, .L850
	ldr	w5, [x20, 36]
.L851:
	lsl	w23, w22, 24
	cmp	w23, w5
	bhi	.L852
	ldr	w0, [x20, 44]
	sub	w5, w5, w23
	ldr	x25, .LC16
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w5, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w5, w19, [x20, 36]
	mov	w23, w5
	tbnz	w19, #31, .L1047
.L853:
	sub	w0, w22, #1
	mov	w1, 1
	ubfx	x0, x0, 1, 24
	str	w1, [x29, 124]
	add	w0, w0, w1
	lsl	w1, w0, 24
	cmp	w1, w23
	bhi	.L854
	ldr	w3, [x20, 44]
	sub	w23, w23, w1
	mov	w1, 2
	str	w1, [x29, 124]
	sub	w0, w3, w0
.L854:
	ldrb	w1, [x25, w0, uxtw]
	ldr	w2, [x29, 124]
	lsl	w26, w23, w1
	sub	w19, w19, w1
	lsl	w0, w0, w1
	cmp	w2, 2
	stp	w26, w19, [x20, 36]
	str	w0, [x20, 44]
	bne	.L855
	add	x21, x21, 4096
	mov	w24, 24
	add	x28, x21, 323
	add	x22, x21, 328
	mov	w23, 16
	b	.L858
	.p2align 3
.L1049:
	ldr	w3, [x20, 44]
	sub	w27, w3, w27
	ldrb	w3, [x25, w27, uxtw]
	sub	w19, w19, w3
	lsl	w4, w4, w3
	lsl	w27, w27, w3
	str	w27, [x20, 44]
	stp	w4, w19, [x20, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
.L955:
	add	x28, x28, 1
	cmp	x28, x22
	beq	.L859
.L858:
	sub	w0, w0, #1
	lsl	w27, w0, 6
	sub	w0, w27, w0
	ubfx	x0, x0, 6, 24
	add	w27, w0, 1
	tbnz	w19, #31, .L1048
.L856:
	lsl	w3, w27, 24
	mov	x1, x28
	cmp	w3, w26
	mov	x0, x20
	sub	w4, w26, w3
	bls	.L1049
	uxtw	x0, w27
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w19, w19, w0
	lsl	w0, w27, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L955
	.p2align 3
.L1026:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	b	.L886
	.p2align 3
.L1028:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L918
	.p2align 3
.L852:
	ldr	x25, .LC16
	uxtw	x0, w22
	add	x21, x21, 4096
	str	wzr, [x29, 124]
	ldrb	w0, [x25, x0]
	lsl	w26, w5, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L859
	.p2align 3
.L1045:
	add	w1, w4, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L951
	.p2align 3
.L1040:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1041
	.p2align 3
.L1039:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L888
	.p2align 3
.L934:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w6, [x25, x1]
	lsl	w1, w26, w6
	sub	w5, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
.L939:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w5, #31, .L1050
.L937:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L938
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w22, w0, w22
	lsl	w0, w27, w26
.L938:
	orr	w4, w4, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w22, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L939
	add	w4, w4, 16
	b	.L933
	.p2align 3
.L1046:
	add	w4, w4, 2
	sub	w1, w0, w4, lsr 1
	b	.L952
.L940:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w1, w22, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L944:
	sub	w19, w19, #1
	mov	w22, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1051
.L942:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L943
	ldr	w0, [x20, 44]
	sub	w22, w22, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L943:
	orr	w4, w4, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w22, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L944
	add	w4, w4, 32
	b	.L933
	.p2align 3
.L1048:
	sub	w4, w24, w19
	sub	w3, w23, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w3, w3, w4
	mov	w1, w4
	str	w3, [x29, 108]
	str	w4, [x29, 120]
	bl	BsGet
	ldr	w3, [x29, 108]
	ldr	w4, [x29, 120]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w19, w4, w19
	orr	w0, w0, w26
	mov	w26, w0
	stp	w0, w19, [x20, 36]
	b	.L856
	.p2align 3
.L1021:
	sub	w5, w24, w19
	mov	w0, 16
	and	w5, w5, -8
	sub	w6, w0, w19
	sub	w6, w6, w5
	mov	w1, w5
	mov	x0, x20
	str	w6, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w5, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L893
	.p2align 3
.L1016:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L863
	.p2align 3
.L1035:
	sub	w6, w24, w19
	sub	w4, w23, w19
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w19, w6, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L926
	.p2align 3
.L1043:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w19, w0, w19
	b	.L904
	.p2align 3
.L1042:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w19, w0, w19
	b	.L874
	.p2align 3
.L1050:
	sub	w1, w24, w5
	sub	w7, w23, w5
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w5, w1, w5
	stp	w4, w7, [x29, 104]
	str	w5, [x29, 120]
	bl	BsGet
	ldp	w4, w7, [x29, 104]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w19, w0, w19
	b	.L937
.L907:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w28, w28, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L911:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1052
.L909:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L910
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L910:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L911
	add	w6, w6, 32
	b	.L900
.L877:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w1, w28, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L881:
	sub	w19, w19, #1
	mov	w28, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1053
.L879:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L880
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L880:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L881
	add	w6, w6, 32
	b	.L870
.L855:
	ldr	w1, [x29, 124]
	add	x21, x21, 4096
	cmp	w1, 1
	beq	.L860
	b	.L859
	.p2align 3
.L1053:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L879
	.p2align 3
.L1052:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L909
	.p2align 3
.L1022:
	sub	w7, w24, w26
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w26
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	add	w5, w7, w26
	lsl	w0, w0, w6
	orr	w28, w0, w28
	mov	w26, w5
	stp	w28, w5, [x20, 36]
	b	.L896
	.p2align 3
.L1017:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w19, w7
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L866
	.p2align 3
.L850:
	mov	w24, 24
	mov	w25, 16
	sub	w24, w24, w19
	sub	w25, w25, w19
	and	w24, w24, -8
	mov	x0, x20
	mov	w1, w24
	sub	w25, w25, w24
	ldr	w23, [x20, 36]
	and	w25, w25, 7
	bl	BsGet
	lsl	w0, w0, w25
	add	w19, w19, w24
	orr	w5, w0, w23
	stp	w5, w19, [x20, 36]
	b	.L851
.L1051:
	sub	w1, w24, w5
	sub	w7, w23, w5
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w5, w1, w5
	stp	w4, w7, [x29, 104]
	str	w5, [x29, 120]
	bl	BsGet
	ldp	w4, w7, [x29, 104]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w22, w0, w22
	b	.L942
	.p2align 3
.L1036:
	sub	w5, w24, w19
	sub	w6, w23, w19
	and	w5, w5, -8
	mov	x0, x20
	sub	w6, w6, w5
	mov	w1, w5
	str	w6, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w5, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L929
.L1019:
	cmp	w19, 64
	bgt	.L1054
	add	w6, w19, 64
	b	.L870
.L1054:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w6, w19, 64
	b	.L870
.L1024:
	cmp	w19, 64
	bgt	.L1055
	add	w6, w19, 64
	b	.L900
.L1055:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w6, w19, 64
	b	.L900
.L1038:
	cmp	w19, 64
	bgt	.L1056
	add	w4, w19, 64
	b	.L933
.L1056:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w4, w19, 64
	b	.L933
.L1047:
	mov	w1, 24
	mov	w24, 16
	sub	w1, w1, w19
	sub	w24, w24, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w24, w24, w1
	add	w19, w1, w19
	and	w24, w24, 7
	bl	BsGet
	lsl	w0, w0, w24
	orr	w23, w0, w23
	b	.L853
.L1023:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w7, w0, w26
	sub	w7, w7, w5
	mov	w1, w5
	mov	x0, x20
	str	w7, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 108]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	add	w5, w5, w26
	lsl	w0, w0, w7
	orr	w28, w0, w28
	mov	w26, w5
	stp	w28, w5, [x20, 36]
	b	.L903
.L1018:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w7, w0, w26
	sub	w7, w7, w5
	mov	w1, w5
	mov	x0, x20
	str	w7, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 108]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	add	w6, w5, w26
	orr	w1, w0, w28
	mov	w26, w6
	mov	w28, w1
	stp	w1, w6, [x20, 36]
	b	.L873
.L1037:
	sub	w6, w24, w26
	sub	w4, w23, w26
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w5, w6, w26
	orr	w1, w0, w22
	mov	w26, w5
	mov	w22, w1
	stp	w1, w5, [x20, 36]
	b	.L936
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	3
.LC16:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	str	x1, [x29, 104]
	str	w2, [x29, 144]
	bl	_mcount
	ldp	w28, w5, [x19, 36]
	ldr	x24, .LC18
	add	x26, x20, 2
	ldr	w0, [x19, 44]
	mov	w27, 1
	add	x20, x20, 5
.L1063:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w23, w0, 1
	tbnz	w5, #31, .L1163
.L1058:
	lsl	w1, w23, 24
	cmp	w1, w28
	bhi	.L1059
	ldr	w0, [x19, 44]
	sub	w1, w28, w1
	mov	w21, 0
	mov	w28, 6
	sub	w0, w0, w23
	ldrb	w23, [x24, w0, uxtw]
	lsl	w1, w1, w23
	sub	w25, w5, w23
	lsl	w23, w0, w23
	str	w23, [x19, 44]
	stp	w1, w25, [x19, 36]
	b	.L1062
	.p2align 3
.L1060:
	lsl	w1, w23, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1061
	ldr	w4, [x19, 44]
	lsl	w0, w27, w28
	sub	w22, w22, w1
	sub	w23, w4, w23
.L1061:
	orr	w21, w21, w0
	ldrb	w0, [x24, w23, uxtw]
	sub	w28, w28, #1
	lsl	w1, w22, w0
	sub	w25, w25, w0
	lsl	w23, w23, w0
	cmn	w28, #1
	stp	w1, w25, [x19, 36]
	str	w23, [x19, 44]
	beq	.L1164
.L1062:
	sub	w23, w23, #1
	mov	w22, w1
	ubfx	x23, x23, 1, 24
	add	w23, w23, 1
	tbz	w25, #31, .L1060
	mov	w0, 24
	sub	w1, w0, w25
	mov	w0, 16
	sub	w4, w0, w25
	and	w1, w1, -8
	sub	w4, w4, w1
	mov	x0, x19
	str	w4, [x29, 152]
	add	w25, w1, w25
	bl	BsGet
	ldr	w4, [x29, 152]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w22, w0, w22
	b	.L1060
	.p2align 3
.L1164:
	lsl	w0, w21, 1
	orr	w0, w0, 1
	strb	w0, [x26]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1120:
	add	x26, x26, 1
	cmp	x20, x26
	bne	.L1063
	ldr	x1, [x29, 104]
	mov	w22, 24
	mov	w21, 16
	mov	w27, 1
	add	x2, x1, 25
	add	x23, x1, 37
	add	x1, x1, 27
	stp	x1, x2, [x29, 112]
.L1089:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w6, w0, 1
	tbnz	w5, #31, .L1165
.L1064:
	lsl	w0, w6, 24
	cmp	w0, w28
	bhi	.L1065
	sub	w28, w28, w0
	ldr	w0, [x19, 44]
	mov	w25, 0
	mov	w26, 6
	sub	w0, w0, w6
	ldrb	w6, [x24, w0, uxtw]
	lsl	w1, w28, w6
	sub	w4, w5, w6
	lsl	w0, w0, w6
	str	w0, [x19, 44]
	stp	w1, w4, [x19, 36]
	b	.L1068
	.p2align 3
.L1066:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1067
	ldr	w7, [x19, 44]
	lsl	w0, w27, w26
	sub	w28, w28, w1
	sub	w20, w7, w20
.L1067:
	orr	w25, w25, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w4, w4, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w4, [x19, 36]
	str	w0, [x19, 44]
	beq	.L1166
.L1068:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbz	w4, #31, .L1066
	sub	w1, w22, w4
	sub	w7, w21, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w7, w7, w1
	add	w4, w1, w4
	stp	w7, w4, [x29, 148]
	bl	BsGet
	ldp	w7, w4, [x29, 148]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w28, w0, w28
	b	.L1066
	.p2align 3
.L1166:
	ldr	x1, [x29, 120]
	lsl	w0, w25, 1
	orr	w0, w0, 1
	strb	w0, [x1, -25]
	ldp	w26, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L1121:
	sub	x1, x23, #22
	sub	x25, x23, #32
	str	x1, [x29, 128]
	.p2align 2
.L1074:
	sub	w0, w0, #1
	lsl	w9, w0, 6
	sub	w0, w9, w0
	ubfx	x0, x0, 6, 24
	add	w9, w0, 1
	tbnz	w20, #31, .L1167
.L1069:
	lsl	w1, w9, 24
	cmp	w1, w26
	bhi	.L1070
	ldr	w0, [x19, 44]
	sub	w4, w26, w1
	mov	w6, 6
	mov	w26, 0
	sub	w0, w0, w9
	ldrb	w1, [x24, w0, uxtw]
	sub	w28, w20, w1
	lsl	w4, w4, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w4, w28, [x19, 36]
	b	.L1073
	.p2align 3
.L1071:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L1072
	ldr	w9, [x19, 44]
	lsl	w0, w27, w6
	sub	w4, w4, w1
	sub	w20, w9, w20
.L1072:
	orr	w26, w26, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w6, w6, #1
	lsl	w4, w4, w0
	sub	w28, w28, w0
	lsl	w20, w20, w0
	cmn	w6, #1
	stp	w4, w28, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1168
.L1073:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w28, #31, .L1071
	sub	w1, w22, w28
	sub	w9, w21, w28
	and	w1, w1, -8
	mov	x0, x19
	sub	w9, w9, w1
	str	w4, [x29, 136]
	stp	w6, w9, [x29, 148]
	add	w28, w1, w28
	bl	BsGet
	ldp	w6, w9, [x29, 148]
	ldr	w4, [x29, 136]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w4, w0, w4
	b	.L1071
	.p2align 3
.L1168:
	lsl	w8, w26, 1
	orr	w8, w8, 1
	strb	w8, [x25]
	ldp	w26, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L1122:
	ldr	x1, [x29, 128]
	add	x25, x25, 1
	cmp	x1, x25
	bne	.L1074
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w6, w0, 1
	tbnz	w20, #31, .L1169
.L1075:
	lsl	w0, w6, 24
	cmp	w0, w26
	bhi	.L1076
	sub	w4, w26, w0
	ldr	w0, [x19, 44]
	mov	w5, 6
	mov	w26, 0
	sub	w0, w0, w6
	ldrb	w1, [x24, w0, uxtw]
	lsl	w4, w4, w1
	sub	w20, w20, w1
	lsl	w0, w0, w1
	str	w0, [x19, 44]
	stp	w4, w20, [x19, 36]
	b	.L1079
	.p2align 3
.L1078:
	ldr	w8, [x19, 44]
	sub	w1, w1, w0
	sub	w25, w8, w25
.L1081:
	ldrb	w0, [x24, w25, uxtw]
	sub	w5, w5, #1
	orr	w26, w26, w4
	cmn	w5, #1
	lsl	w4, w1, w0
	sub	w20, w20, w0
	lsl	w0, w25, w0
	str	w0, [x19, 44]
	stp	w4, w20, [x19, 36]
	beq	.L1170
.L1079:
	sub	w0, w0, #1
	mov	w1, w4
	ubfx	x0, x0, 1, 24
	add	w25, w0, 1
	tbnz	w20, #31, .L1077
.L1082:
	lsl	w0, w25, 24
	lsl	w4, w27, w5
	cmp	w0, w1
	bls	.L1078
	mov	w4, 0
	b	.L1081
	.p2align 3
.L1070:
	uxtw	x0, w9
	ldrb	w0, [x24, x0]
	lsl	w26, w26, w0
	sub	w20, w20, w0
	lsl	w0, w9, w0
	str	w0, [x19, 44]
	stp	w26, w20, [x19, 36]
	b	.L1122
	.p2align 3
.L1167:
	sub	w6, w22, w20
	sub	w5, w21, w20
	and	w28, w6, -8
	mov	x0, x19
	sub	w5, w5, w28
	mov	w1, w28
	stp	w9, w5, [x29, 148]
	bl	BsGet
	ldp	w9, w5, [x29, 148]
	and	w5, w5, 7
	lsl	w0, w0, w5
	add	w5, w28, w20
	orr	w4, w0, w26
	mov	w20, w5
	mov	w26, w4
	stp	w4, w5, [x19, 36]
	b	.L1069
	.p2align 3
.L1170:
	ldr	x1, [x29, 120]
	lsl	w0, w26, 1
	orr	w0, w0, 1
	strb	w0, [x1]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1123:
	sub	x26, x23, #10
	.p2align 2
.L1088:
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w5, #31, .L1171
.L1083:
	lsl	w1, w20, 24
	cmp	w1, w28
	bhi	.L1084
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	mov	w25, 0
	mov	w7, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w28, w28, w20
	sub	w4, w5, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w4, [x19, 36]
	b	.L1087
	.p2align 3
.L1085:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1086
	ldr	w5, [x19, 44]
	lsl	w0, w27, w7
	sub	w28, w28, w1
	sub	w20, w5, w20
.L1086:
	orr	w25, w25, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w7, w7, #1
	lsl	w28, w28, w0
	sub	w4, w4, w0
	lsl	w20, w20, w0
	cmn	w7, #1
	stp	w28, w4, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1172
.L1087:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w4, #31, .L1085
	sub	w1, w22, w4
	sub	w5, w21, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w4, w1, w4
	str	w7, [x29, 136]
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	ldr	w7, [x29, 136]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L1085
	.p2align 3
.L1172:
	lsl	w8, w25, 1
	orr	w8, w8, 1
	strb	w8, [x26]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1124:
	add	x26, x26, 1
	cmp	x23, x26
	bne	.L1088
	ldp	x2, x1, [x29, 112]
	add	x23, x23, 10
	add	x1, x1, 1
	str	x1, [x29, 120]
	cmp	x1, x2
	bne	.L1089
	ldr	x1, [x29, 104]
	mov	w27, 1
	str	x1, [x29, 112]
	add	x2, x1, 12
	str	x1, [x29, 136]
	str	x2, [x29, 96]
.L1090:
	ldr	x20, [x29, 112]
	mov	w1, 2
	str	w1, [x29, 148]
.L1097:
	mov	x26, 0
.L1096:
	sub	w0, w0, #1
	lsl	w11, w0, 6
	sub	w0, w11, w0
	ubfx	x0, x0, 6, 24
	add	w11, w0, 1
	tbnz	w5, #31, .L1173
.L1091:
	lsl	w1, w11, 24
	cmp	w1, w28
	bhi	.L1092
	ldr	w0, [x19, 44]
	sub	w3, w28, w1
	mov	w25, 0
	mov	w22, 6
	sub	w0, w0, w11
	ldrb	w28, [x24, w0, uxtw]
	lsl	w3, w3, w28
	sub	w21, w5, w28
	lsl	w28, w0, w28
	str	w28, [x19, 44]
	stp	w3, w21, [x19, 36]
	b	.L1095
	.p2align 3
.L1093:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1094
	ldr	w5, [x19, 44]
	lsl	w0, w27, w22
	sub	w23, w23, w1
	sub	w28, w5, w28
.L1094:
	orr	w25, w25, w0
	ldrb	w0, [x24, w28, uxtw]
	sub	w22, w22, #1
	lsl	w3, w23, w0
	sub	w21, w21, w0
	lsl	w28, w28, w0
	cmn	w22, #1
	stp	w3, w21, [x19, 36]
	str	w28, [x19, 44]
	beq	.L1174
.L1095:
	sub	w28, w28, #1
	mov	w23, w3
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbz	w21, #31, .L1093
	mov	w0, 24
	sub	w1, w0, w21
	mov	w0, 16
	sub	w5, w0, w21
	and	w1, w1, -8
	sub	w5, w5, w1
	mov	x0, x19
	str	w5, [x29, 152]
	add	w21, w1, w21
	bl	BsGet
	ldr	w5, [x29, 152]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w23, w0, w23
	b	.L1093
	.p2align 3
.L1084:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1124
	.p2align 3
.L1174:
	add	x0, x20, x26
	lsl	w10, w25, 1
	orr	w10, w10, 1
	strb	w10, [x0, 47]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1125:
	add	x26, x26, 1
	cmp	x26, 3
	bne	.L1096
	ldr	w1, [x29, 148]
	add	x20, x20, 3
	subs	w1, w1, #1
	str	w1, [x29, 148]
	bne	.L1097
	sub	w0, w0, #1
	mov	x20, 0
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w5, #31, .L1175
.L1099:
	lsl	w3, w21, 24
	cmp	w3, w28
	bhi	.L1100
.L1177:
	ldr	w0, [x19, 44]
	sub	w28, w28, w3
	mov	w8, 0
	mov	w3, 6
	sub	w0, w0, w21
	ldrb	w21, [x24, w0, uxtw]
	lsl	w28, w28, w21
	sub	w4, w5, w21
	lsl	w21, w0, w21
	str	w21, [x19, 44]
	stp	w28, w4, [x19, 36]
	b	.L1103
	.p2align 3
.L1101:
	lsl	w1, w21, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1102
	ldr	w5, [x19, 44]
	lsl	w0, w27, w3
	sub	w28, w28, w1
	sub	w21, w5, w21
.L1102:
	orr	w8, w8, w0
	ldrb	w0, [x24, w21, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w4, w4, w0
	lsl	w21, w21, w0
	cmn	w3, #1
	stp	w28, w4, [x19, 36]
	str	w21, [x19, 44]
	beq	.L1176
.L1103:
	sub	w21, w21, #1
	ubfx	x21, x21, 1, 24
	add	w21, w21, 1
	tbz	w4, #31, .L1101
	mov	w0, 24
	str	w3, [x29, 120]
	sub	w1, w0, w4
	mov	w0, 16
	sub	w5, w0, w4
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w4, w1, w4
	mov	x0, x19
	str	w8, [x29, 128]
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	ldr	w3, [x29, 120]
	and	w5, w5, 7
	ldr	w8, [x29, 128]
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L1101
	.p2align 3
.L1092:
	uxtw	x0, w11
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w11, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1125
	.p2align 3
.L1176:
	ldr	x0, [x29, 136]
	lsl	w8, w8, 1
	orr	w8, w8, 1
	add	x0, x0, x20
	add	x20, x20, 1
	cmp	x20, 3
	strb	w8, [x0, 59]
	beq	.L1104
.L1178:
	ldr	w0, [x19, 44]
	ldp	w28, w5, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbz	w5, #31, .L1099
.L1175:
	mov	w0, 24
	str	w5, [x29, 128]
	sub	w4, w0, w5
	mov	w0, 16
	and	w4, w4, -8
	sub	w3, w0, w5
	sub	w3, w3, w4
	mov	w1, w4
	mov	x0, x19
	stp	w3, w4, [x29, 148]
	bl	BsGet
	ldp	w3, w4, [x29, 148]
	ldr	w5, [x29, 128]
	and	w3, w3, 7
	lsl	w0, w0, w3
	lsl	w3, w21, 24
	orr	w28, w0, w28
	add	w4, w4, w5
	cmp	w3, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	bls	.L1177
	.p2align 2
.L1100:
	uxtw	x0, w21
	add	x20, x20, 1
	cmp	x20, 3
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w4, w5, w0
	lsl	w0, w21, w0
	str	w0, [x19, 44]
	stp	w28, w4, [x19, 36]
	bne	.L1178
.L1104:
	ldr	x1, [x29, 136]
	ldr	x0, [x29, 112]
	add	x1, x1, 3
	str	x1, [x29, 136]
	ldr	x1, [x29, 96]
	add	x0, x0, 6
	str	x0, [x29, 112]
	cmp	x0, x1
	beq	.L1105
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
	b	.L1090
	.p2align 3
.L1171:
	sub	w7, w22, w5
	sub	w4, w21, w5
	and	w25, w7, -8
	mov	x0, x19
	sub	w4, w4, w25
	mov	w1, w25
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w4, w25, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1083
	.p2align 3
.L1173:
	mov	w0, 24
	str	w11, [x29, 128]
	sub	w4, w0, w5
	mov	w0, 16
	and	w22, w4, -8
	sub	w3, w0, w5
	mov	w1, w22
	mov	x0, x19
	sub	w21, w3, w22
	str	w5, [x29, 152]
	bl	BsGet
	ldr	w5, [x29, 152]
	and	w3, w21, 7
	lsl	w0, w0, w3
	ldr	w11, [x29, 128]
	add	w4, w22, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1091
	.p2align 3
.L1059:
	uxtw	x0, w23
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w23, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1120
	.p2align 3
.L1077:
	sub	w1, w22, w20
	mov	x0, x19
	and	w1, w1, -8
	sub	w28, w21, w20
	sub	w28, w28, w1
	add	w20, w1, w20
	stp	w4, w5, [x29, 148]
	bl	BsGet
	and	w28, w28, 7
	ldp	w4, w5, [x29, 148]
	lsl	w0, w0, w28
	orr	w1, w0, w4
	b	.L1082
.L1105:
	ldr	w0, [x29, 144]
	cbz	w0, .L1057
	ldr	x0, [x29, 104]
	mov	w22, 24
	mov	w21, 16
	mov	w26, 1
	add	x25, x0, 67
	add	x0, x0, 69
	str	x0, [x29, 152]
.L1118:
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1179
.L1108:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L1109
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	mov	w4, 0
	mov	w28, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w23, w23, w20
	sub	w5, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w5, [x19, 36]
	b	.L1112
	.p2align 3
.L1110:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1111
	ldr	w3, [x19, 44]
	lsl	w0, w26, w28
	sub	w23, w23, w1
	sub	w20, w3, w20
.L1111:
	orr	w4, w4, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w28, w28, #1
	lsl	w23, w23, w0
	sub	w5, w5, w0
	lsl	w20, w20, w0
	cmn	w28, #1
	stp	w23, w5, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1180
.L1112:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w5, #31, .L1110
	sub	w1, w22, w5
	sub	w27, w21, w5
	and	w1, w1, -8
	mov	x0, x19
	add	w5, w1, w5
	sub	w27, w27, w1
	and	w27, w27, 7
	str	w4, [x29, 136]
	str	w5, [x29, 148]
	bl	BsGet
	lsl	w0, w0, w27
	ldr	w4, [x29, 136]
	orr	w23, w0, w23
	ldr	w5, [x29, 148]
	b	.L1110
.L1182:
	lsl	w0, w3, 1
	orr	w0, w0, 1
	strb	w0, [x25]
.L1128:
	ldr	x0, [x29, 152]
	add	x25, x25, 1
	cmp	x25, x0
	bne	.L1118
.L1057:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1065:
	uxtw	x0, w6
	ldrb	w0, [x24, x0]
	lsl	w26, w28, w0
	sub	w20, w5, w0
	lsl	w0, w6, w0
	str	w0, [x19, 44]
	stp	w26, w20, [x19, 36]
	b	.L1121
.L1076:
	uxtw	x0, w6
	ldrb	w0, [x24, x0]
	lsl	w28, w26, w0
	sub	w5, w20, w0
	lsl	w0, w6, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1123
.L1180:
	lsl	w0, w4, 1
	orr	w0, w0, 1
	strb	w0, [x25, -2]
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1181
.L1113:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L1114
.L1183:
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	mov	w3, 0
	mov	w28, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w23, w23, w20
	sub	w27, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w27, [x19, 36]
	b	.L1117
	.p2align 3
.L1115:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1116
	ldr	w4, [x19, 44]
	lsl	w0, w26, w28
	sub	w23, w23, w1
	sub	w20, w4, w20
.L1116:
	orr	w3, w3, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w28, w28, #1
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w20, w20, w0
	cmn	w28, #1
	stp	w23, w27, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1182
.L1117:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w27, #31, .L1115
	sub	w1, w22, w27
	sub	w4, w21, w27
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	str	w3, [x29, 136]
	str	w4, [x29, 148]
	add	w27, w1, w27
	bl	BsGet
	ldr	w4, [x29, 148]
	ldr	w3, [x29, 136]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w23, w0, w23
	b	.L1115
.L1109:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	stp	w23, w27, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w27, #31, .L1113
.L1181:
	sub	w3, w22, w27
	sub	w28, w21, w27
	and	w3, w3, -8
	mov	x0, x19
	mov	w1, w3
	sub	w28, w28, w3
	str	w3, [x29, 148]
	and	w28, w28, 7
	bl	BsGet
	lsl	w0, w0, w28
	ldr	w3, [x29, 148]
	orr	w23, w0, w23
	lsl	w0, w20, 24
	add	w27, w3, w27
	cmp	w0, w23
	stp	w23, w27, [x19, 36]
	bls	.L1183
.L1114:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w23, w23, w0
	sub	w1, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w23, w1, [x19, 36]
	b	.L1128
.L1163:
	mov	w0, 24
	str	w5, [x29, 152]
	sub	w3, w0, w5
	mov	w0, 16
	and	w21, w3, -8
	sub	w25, w0, w5
	mov	w1, w21
	mov	x0, x19
	sub	w25, w25, w21
	bl	BsGet
	and	w25, w25, 7
	ldr	w5, [x29, 152]
	lsl	w0, w0, w25
	orr	w28, w0, w28
	add	w4, w21, w5
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1058
.L1165:
	sub	w4, w22, w5
	mov	x0, x19
	and	w25, w4, -8
	sub	w20, w21, w5
	mov	w1, w25
	sub	w20, w20, w25
	stp	w6, w5, [x29, 148]
	bl	BsGet
	and	w20, w20, 7
	ldp	w6, w5, [x29, 148]
	lsl	w0, w0, w20
	add	w4, w25, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1064
.L1169:
	sub	w5, w22, w20
	mov	x0, x19
	and	w5, w5, -8
	sub	w28, w21, w20
	mov	w1, w5
	sub	w28, w28, w5
	stp	w6, w5, [x29, 148]
	bl	BsGet
	and	w28, w28, 7
	ldp	w6, w5, [x29, 148]
	lsl	w0, w0, w28
	orr	w4, w0, w26
	add	w5, w5, w20
	mov	w26, w4
	mov	w20, w5
	stp	w4, w5, [x19, 36]
	b	.L1075
.L1179:
	sub	w28, w22, w27
	sub	w3, w21, w27
	and	w28, w28, -8
	mov	x0, x19
	sub	w3, w3, w28
	mov	w1, w28
	str	w3, [x29, 148]
	add	w27, w27, w28
	bl	BsGet
	ldr	w3, [x29, 148]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w23, w0, w23
	stp	w23, w27, [x19, 36]
	b	.L1108
	.size	Vp9_ReadMvProbs, .-Vp9_ReadMvProbs
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_PrepareReadModeInfo
	.type	Vp9_PrepareReadModeInfo, %function
Vp9_PrepareReadModeInfo:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 4096
	mov	x27, x1
	mov	w23, w2
	mov	w22, w3
	str	w6, [x29, 124]
	add	x24, x19, 304
	str	x7, [x29, 128]
	add	x26, x19, 307
	stp	w5, w4, [x29, 148]
	bl	_mcount
	ldr	x25, .LC19
	mov	w28, 24
	mov	w21, 1
	str	wzr, [x29, 172]
.L1216:
	ldp	w7, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w9, w0, 1
	tbnz	w7, #31, .L1185
	ldr	w0, [x27, 36]
.L1186:
	lsl	w1, w9, 24
	cmp	w1, w0
	bhi	.L1187
	sub	w1, w0, w1
	ldr	w0, [x27, 44]
	sub	w0, w0, w9
	ldrb	w2, [x25, w0, uxtw]
	lsl	w9, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w9, w7, [x27, 36]
	tbnz	w7, #31, .L1346
.L1188:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w9
	bhi	.L1189
	ldr	w2, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w2, w0
	ldrb	w2, [x25, w0, uxtw]
	lsl	w9, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w9, w7, [x27, 36]
	tbnz	w7, #31, .L1347
.L1191:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w9
	bhi	.L1196
	ldr	w2, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w2, w0
	ldrb	w2, [x25, w0, uxtw]
	lsl	w10, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w10, w7, [x27, 36]
	tbnz	w7, #31, .L1348
.L1198:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w10
	bhi	.L1202
	ldr	w2, [x27, 44]
	sub	w10, w10, w1
	mov	w9, 0
	mov	w11, 6
	sub	w0, w2, w0
	ldrb	w2, [x25, w0, uxtw]
	lsl	w10, w10, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w10, w7, [x27, 36]
	b	.L1203
.L1207:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w10
	bhi	.L1208
	ldr	w0, [x27, 44]
	sub	w10, w10, w1
	sub	w2, w0, w2
	lsl	w0, w21, w11
.L1208:
	orr	w9, w9, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w10, w10, w0
	sub	w7, w7, w0
	lsl	w2, w2, w0
	cmn	w11, #1
	stp	w10, w7, [x27, 36]
	str	w2, [x27, 44]
	beq	.L1349
.L1203:
	sub	w2, w2, #1
	ubfx	x2, x2, 1, 24
	add	w2, w2, 1
	tbz	w7, #31, .L1207
	sub	w1, w28, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w7
	sub	w12, w12, w1
	add	w7, w1, w7
	mov	x0, x27
	str	w9, [x29, 112]
	stp	w10, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w10, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w9, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w7, [x29, 144]
	orr	w10, w0, w10
	b	.L1207
	.p2align 3
.L1187:
	uxtw	x1, w9
	ldrb	w1, [x25, x1]
	lsl	w0, w0, w1
	sub	w7, w7, w1
	stp	w0, w7, [x27, 36]
	lsl	w0, w9, w1
	str	w0, [x27, 44]
.L1289:
	add	x24, x24, 1
	cmp	x24, x26
	bne	.L1216
	cmp	w23, wzr
	ccmp	w22, wzr, 0, ne
	beq	.L1350
.L1217:
	ldr	x1, [x29, 128]
	ldr	w0, [x29, 172]
	str	w0, [x1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1189:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	ldrb	w2, [x25, x1]
	lsl	w1, w9, w2
	lsl	w0, w0, w2
	sub	w9, w7, w2
	str	w0, [x27, 44]
	stp	w1, w9, [x27, 36]
.L1194:
	sub	w0, w0, #1
	mov	w7, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w9, #31, .L1351
.L1192:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w7
	bhi	.L1193
	ldr	w12, [x27, 44]
	lsl	w0, w21, w11
	sub	w7, w7, w1
	sub	w2, w12, w2
.L1193:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w7, w0
	sub	w9, w9, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w9, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1194
.L1195:
	ldrb	w0, [x24]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w7, w0, 1
	ldrb	w2, [x1, w10, sxtw]
	cmp	w7, 255
	bgt	.L1210
.L1377:
	add	w1, w2, 1
	cmp	w1, w7
	bgt	.L1211
	tbnz	x1, 0, .L1352
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1211:
	add	w1, w1, 1
.L1213:
	strb	w1, [x24]
	b	.L1289
	.p2align 3
.L1210:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L1214
	tbnz	x1, 0, .L1353
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1214:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x24]
	b	.L1289
	.p2align 3
.L1185:
	sub	w10, w28, w7
	mov	w0, 16
	and	w10, w10, -8
	sub	w11, w0, w7
	ldr	w2, [x27, 36]
	sub	w11, w11, w10
	mov	w1, w10
	mov	x0, x27
	stp	w9, w11, [x29, 108]
	str	w7, [x29, 120]
	str	w10, [x29, 136]
	str	w2, [x29, 144]
	bl	BsGet
	ldp	w9, w11, [x29, 108]
	ldr	w7, [x29, 120]
	ldr	w10, [x29, 136]
	and	w11, w11, 7
	ldr	w2, [x29, 144]
	lsl	w0, w0, w11
	add	w7, w7, w10
	orr	w0, w0, w2
	stp	w0, w7, [x27, 36]
	b	.L1186
	.p2align 3
.L1350:
	mov	x0, x20
	add	x2, x19, 372
	mov	x1, x27
	str	x2, [x29, 112]
	bl	Vp9_ReadInterModeProbs
	ldr	w0, [x29, 152]
	cmp	w0, 4
	beq	.L1354
.L1218:
	add	x28, x19, 319
	add	x22, x19, 323
	mov	w23, 24
	mov	w24, 16
.L1222:
	ldp	w3, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w3, #31, .L1219
	ldr	w2, [x27, 36]
.L1220:
	lsl	w0, w21, 24
	mov	x1, x28
	cmp	w0, w2
	sub	w6, w2, w0
	mov	x0, x27
	bhi	.L1221
	ldr	w2, [x27, 44]
	sub	w2, w2, w21
	ldrb	w5, [x25, w2, uxtw]
	lsl	w6, w6, w5
	sub	w3, w3, w5
	lsl	w2, w2, w5
	str	w2, [x27, 44]
	stp	w6, w3, [x27, 36]
	bl	Vp9_DiffUpdateProb
.L1290:
	add	x28, x28, 1
	cmp	x22, x28
	bne	.L1222
	ldr	w2, [x29, 148]
	mov	x0, x20
	mov	x1, x27
	add	x3, x29, 172
	add	x21, x19, 9
	mov	w24, 24
	bl	Vp9_ReadCompPred
	mov	w23, 1
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	add	x1, x19, 73
	str	x1, [x29, 136]
.L1223:
	sub	x22, x21, #9
	.p2align 2
.L1254:
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w20, #31, .L1355
.L1224:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L1225
	ldr	w0, [x27, 44]
	sub	w6, w26, w1
	sub	w0, w0, w28
	ldrb	w28, [x25, w0, uxtw]
	lsl	w6, w6, w28
	sub	w26, w20, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w6, w26, [x27, 36]
	tbnz	w26, #31, .L1356
.L1226:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w6
	bhi	.L1227
	ldr	w28, [x27, 44]
	sub	w20, w6, w1
	sub	w28, w28, w0
	ldrb	w0, [x25, w28, uxtw]
	lsl	w20, w20, w0
	sub	w6, w26, w0
	lsl	w28, w28, w0
	str	w28, [x27, 44]
	stp	w20, w6, [x27, 36]
	tbnz	w6, #31, .L1357
.L1229:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L1234
	sub	w7, w20, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w26, w7, w20
	sub	w28, w6, w20
	lsl	w20, w0, w20
	str	w20, [x27, 44]
	stp	w26, w28, [x27, 36]
	tbnz	w28, #31, .L1358
.L1236:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1240
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	mov	w20, 0
	mov	w9, 6
	sub	w0, w1, w0
	ldrb	w7, [x25, w0, uxtw]
	lsl	w1, w6, w7
	sub	w26, w28, w7
	lsl	w0, w0, w7
	str	w0, [x27, 44]
	stp	w1, w26, [x27, 36]
	b	.L1241
	.p2align 3
.L1245:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w7
	bhi	.L1246
	ldr	w0, [x27, 44]
	sub	w7, w7, w1
	sub	w28, w0, w28
	lsl	w0, w23, w9
.L1246:
	orr	w20, w20, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w9, w9, #1
	lsl	w1, w7, w0
	sub	w26, w26, w0
	cmn	w9, #1
	lsl	w0, w28, w0
	stp	w1, w26, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1359
.L1241:
	sub	w0, w0, #1
	mov	w7, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w26, #31, .L1245
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w26
	sub	w10, w10, w1
	mov	x0, x27
	stp	w7, w9, [x29, 144]
	str	w10, [x29, 152]
	add	w26, w1, w26
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w7, w9, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w7, w0, w7
	b	.L1245
	.p2align 3
.L1225:
	uxtw	x0, w28
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w20, w20, w0
	lsl	w0, w28, w0
	str	w0, [x27, 44]
	stp	w26, w20, [x27, 36]
.L1291:
	add	x22, x22, 1
	cmp	x21, x22
	bne	.L1254
	ldr	x1, [x29, 136]
	add	x21, x21, 16
	cmp	x1, x21
	bne	.L1223
	add	x1, x19, 612
	add	x21, x19, 564
	mov	w24, 16
	mov	w23, 1
	str	x1, [x29, 152]
	.p2align 2
.L1255:
	sub	w0, w0, #1
	mov	x19, x21
	lsl	w1, w0, 6
	mov	w28, 3
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbnz	w20, #31, .L1360
.L1256:
	lsl	w1, w22, 24
	cmp	w1, w26
	bhi	.L1257
	ldr	w0, [x27, 44]
	sub	w6, w26, w1
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w26, w6, w22
	sub	w20, w20, w22
	lsl	w22, w0, w22
	str	w22, [x27, 44]
	stp	w26, w20, [x27, 36]
	tbnz	w20, #31, .L1361
.L1258:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w0, w22, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1259
	ldr	w22, [x27, 44]
	sub	w6, w26, w1
	sub	w22, w22, w0
	ldrb	w0, [x25, w22, uxtw]
	lsl	w26, w6, w0
	sub	w20, w20, w0
	lsl	w22, w22, w0
	str	w22, [x27, 44]
	stp	w26, w20, [x27, 36]
	tbnz	w20, #31, .L1362
.L1261:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1266
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	ldrb	w1, [x25, w0, uxtw]
	sub	w22, w20, w1
	lsl	w26, w6, w1
	lsl	w20, w0, w1
	str	w20, [x27, 44]
	stp	w26, w22, [x27, 36]
	tbnz	w22, #31, .L1363
.L1268:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1272
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	mov	w20, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w10, [x25, w0, uxtw]
	lsl	w1, w6, w10
	sub	w26, w22, w10
	lsl	w0, w0, w10
	str	w0, [x27, 44]
	stp	w1, w26, [x27, 36]
	b	.L1273
	.p2align 3
.L1277:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w6
	bhi	.L1278
	ldr	w0, [x27, 44]
	sub	w6, w6, w1
	sub	w22, w0, w22
	lsl	w0, w23, w7
.L1278:
	orr	w20, w20, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w7, w7, #1
	lsl	w1, w6, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w22, w0
	stp	w1, w26, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1364
.L1273:
	sub	w0, w0, #1
	mov	w6, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w26, #31, .L1277
	mov	w0, 24
	sub	w10, w24, w26
	sub	w1, w0, w26
	mov	x0, x27
	and	w1, w1, -8
	str	w6, [x29, 136]
	sub	w10, w10, w1
	add	w26, w1, w26
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w6, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w6, w0, w6
	b	.L1277
	.p2align 3
.L1257:
	uxtw	x0, w22
	ldrb	w0, [x25, x0]
	lsl	w6, w26, w0
	sub	w20, w20, w0
	lsl	w0, w22, w0
	str	w0, [x27, 44]
	stp	w6, w20, [x27, 36]
.L1292:
	subs	w28, w28, #1
	add	x19, x19, 1
	beq	.L1365
	ldr	w0, [x27, 44]
	ldp	w26, w20, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbz	w20, #31, .L1256
.L1360:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w9, w7, [x29, 144]
	bl	BsGet
	ldp	w9, w7, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1256
	.p2align 3
.L1365:
	ldr	x0, [x29, 152]
	add	x21, x21, 3
	cmp	x21, x0
	beq	.L1287
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1255
	.p2align 3
.L1259:
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w22, [x25, x1]
	lsl	w6, w26, w22
	sub	w20, w20, w22
	lsl	w22, w0, w22
	str	w22, [x27, 44]
	stp	w6, w20, [x27, 36]
.L1264:
	sub	w22, w22, #1
	mov	w26, w6
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w20, #31, .L1366
.L1262:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L1263
	ldr	w10, [x27, 44]
	lsl	w0, w23, w9
	sub	w26, w26, w1
	sub	w22, w10, w22
.L1263:
	orr	w7, w7, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w9, w9, #1
	lsl	w6, w26, w0
	sub	w20, w20, w0
	lsl	w22, w22, w0
	cmn	w9, #1
	stp	w6, w20, [x27, 36]
	str	w22, [x27, 44]
	bne	.L1264
.L1265:
	ldrb	w0, [x19]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1280
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1281
	tbnz	x1, 0, .L1367
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1281:
	add	w1, w1, 1
.L1283:
	strb	w1, [x19]
	b	.L1292
	.p2align 3
.L1227:
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w28, [x25, x1]
	lsl	w20, w6, w28
	sub	w26, w26, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w20, w26, [x27, 36]
.L1232:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w26, #31, .L1368
.L1230:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L1231
	ldr	w10, [x27, 44]
	lsl	w0, w23, w9
	sub	w20, w20, w1
	sub	w28, w10, w28
.L1231:
	orr	w7, w7, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w9, w9, #1
	lsl	w20, w20, w0
	sub	w26, w26, w0
	lsl	w28, w28, w0
	cmn	w9, #1
	stp	w20, w26, [x27, 36]
	str	w28, [x27, 44]
	bne	.L1232
.L1233:
	ldrb	w0, [x22]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1248
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1249
	tbnz	x1, 0, .L1369
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1249:
	add	w1, w1, 1
.L1251:
	strb	w1, [x22]
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1291
	.p2align 3
.L1280:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1284
	tbnz	x1, 0, .L1370
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1284:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x19]
	b	.L1292
	.p2align 3
.L1248:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1252
	tbnz	x1, 0, .L1371
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1252:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1251
	.p2align 3
.L1366:
	mov	w0, 24
	sub	w10, w24, w20
	sub	w1, w0, w20
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w20, w1, w20
	stp	w9, w10, [x29, 144]
	bl	BsGet
	ldp	w9, w10, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w26, w0, w26
	b	.L1262
	.p2align 3
.L1355:
	sub	w9, w24, w20
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w20
	sub	w7, w7, w9
	mov	w1, w9
	mov	x0, x27
	stp	w9, w7, [x29, 148]
	bl	BsGet
	ldp	w9, w7, [x29, 148]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1224
	.p2align 3
.L1368:
	sub	w1, w24, w26
	mov	w0, 16
	sub	w10, w0, w26
	and	w1, w1, -8
	sub	w10, w10, w1
	mov	x0, x27
	stp	w9, w7, [x29, 144]
	str	w10, [x29, 152]
	add	w26, w1, w26
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w9, w7, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w20, w0, w20
	b	.L1230
	.p2align 3
.L1266:
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w1, [x25, x1]
	lsl	w22, w26, w1
	sub	w6, w20, w1
	mov	w26, 3
	lsl	w20, w0, w1
	stp	w22, w6, [x27, 36]
	str	w20, [x27, 44]
.L1271:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w6, #31, .L1372
.L1269:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1270
	ldr	w10, [x27, 44]
	lsl	w0, w23, w26
	sub	w22, w22, w1
	sub	w20, w10, w20
.L1270:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w22, w22, w0
	sub	w6, w6, w0
	lsl	w20, w20, w0
	cmn	w26, #1
	stp	w22, w6, [x27, 36]
	str	w20, [x27, 44]
	bne	.L1271
	add	w7, w7, 16
	b	.L1265
	.p2align 3
.L1234:
	uxtw	x1, w0
	mov	w26, 3
	ldrb	w7, [x25, x1]
	lsl	w1, w20, w7
	sub	w6, w6, w7
	lsl	w20, w0, w7
	mov	w7, 0
	stp	w1, w6, [x27, 36]
	str	w20, [x27, 44]
.L1239:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w6, #31, .L1373
.L1237:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1238
	ldr	w10, [x27, 44]
	lsl	w0, w23, w26
	sub	w28, w28, w1
	sub	w20, w10, w20
.L1238:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	lsl	w20, w20, w0
	cmn	w26, #1
	stp	w1, w6, [x27, 36]
	str	w20, [x27, 44]
	bne	.L1239
	add	w7, w7, 16
	b	.L1233
	.p2align 3
.L1361:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1258
	.p2align 3
.L1367:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1283
	.p2align 3
.L1221:
	uxtw	x0, w21
	ldrb	w1, [x25, x0]
	lsl	w2, w2, w1
	sub	w0, w3, w1
	lsl	w1, w21, w1
	str	w1, [x27, 44]
	stp	w2, w0, [x27, 36]
	b	.L1290
	.p2align 3
.L1372:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1269
	.p2align 3
.L1356:
	sub	w7, w24, w26
	mov	w0, 16
	and	w7, w7, -8
	sub	w20, w0, w26
	mov	w1, w7
	mov	x0, x27
	sub	w20, w20, w7
	stp	w6, w7, [x29, 148]
	bl	BsGet
	ldp	w6, w7, [x29, 148]
	and	w1, w20, 7
	lsl	w0, w0, w1
	add	w10, w26, w7
	orr	w20, w0, w6
	mov	w26, w10
	mov	w6, w20
	stp	w20, w10, [x27, 36]
	b	.L1226
	.p2align 3
.L1370:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1284
	.p2align 3
.L1369:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	b	.L1249
	.p2align 3
.L1373:
	sub	w1, w24, w6
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w6
	sub	w10, w10, w1
	add	w6, w1, w6
	mov	x0, x27
	str	w6, [x29, 152]
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w6, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1237
	.p2align 3
.L1371:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1252
	.p2align 3
.L1287:
	ldr	w2, [x29, 124]
	mov	x0, x27
	ldr	x1, [x29, 112]
	bl	Vp9_ReadMvProbs
	b	.L1217
	.p2align 3
.L1351:
	sub	w1, w28, w9
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w9
	sub	w12, w12, w1
	add	w9, w1, w9
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w7, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w9, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w7, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w9, [x29, 144]
	orr	w7, w0, w7
	b	.L1192
.L1272:
	uxtw	x1, w0
	ldrb	w7, [x25, x1]
	lsl	w1, w26, w7
	sub	w6, w22, w7
	lsl	w0, w0, w7
	mov	w26, 4
	mov	w7, 0
	str	w0, [x27, 44]
	stp	w1, w6, [x27, 36]
	.p2align 2
.L1276:
	sub	w0, w0, #1
	mov	w22, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w6, #31, .L1374
.L1274:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1275
	ldr	w0, [x27, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w26
.L1275:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w22, w0
	sub	w6, w6, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1276
	add	w7, w7, 32
	b	.L1265
.L1240:
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w9, [x25, x1]
	lsl	w1, w26, w9
	sub	w6, w28, w9
	lsl	w0, w0, w9
	mov	w26, 4
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1244:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w6, #31, .L1375
.L1242:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1243
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w23, w26
.L1243:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1244
	add	w7, w7, 32
	b	.L1233
	.p2align 3
.L1374:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1274
	.p2align 3
.L1362:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1261
	.p2align 3
.L1219:
	sub	w2, w23, w3
	sub	w6, w24, w3
	and	w2, w2, -8
	mov	x0, x27
	sub	w6, w6, w2
	mov	w1, w2
	ldr	w26, [x27, 36]
	str	w3, [x29, 136]
	str	w6, [x29, 144]
	str	w2, [x29, 152]
	bl	BsGet
	ldr	w6, [x29, 144]
	ldr	w2, [x29, 152]
	ldr	w3, [x29, 136]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w3, w3, w2
	orr	w2, w0, w26
	stp	w2, w3, [x27, 36]
	b	.L1220
.L1352:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1213
.L1196:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	ldrb	w2, [x25, x1]
	lsl	w1, w9, w2
	lsl	w0, w0, w2
	sub	w9, w7, w2
	str	w0, [x27, 44]
	stp	w1, w9, [x27, 36]
.L1201:
	sub	w0, w0, #1
	mov	w7, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w9, #31, .L1376
.L1199:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w7
	bhi	.L1200
	ldr	w0, [x27, 44]
	sub	w7, w7, w1
	sub	w2, w0, w2
	lsl	w0, w21, w11
.L1200:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w7, w0
	sub	w9, w9, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w9, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1201
	ldrb	w0, [x24]
	add	w10, w10, 16
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w7, w0, 1
	cmp	w7, 255
	ldrb	w2, [x1, w10, sxtw]
	bgt	.L1210
	b	.L1377
.L1353:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L1214
.L1202:
	uxtw	x1, w0
	mov	w11, 4
	ldrb	w2, [x25, x1]
	lsl	w1, w10, w2
	sub	w7, w7, w2
	mov	w10, 0
	lsl	w2, w0, w2
	stp	w1, w7, [x27, 36]
	str	w2, [x27, 44]
	.p2align 2
.L1206:
	sub	w2, w2, #1
	mov	w9, w1
	ubfx	x2, x2, 1, 24
	add	w2, w2, 1
	tbnz	w7, #31, .L1378
.L1204:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L1205
	ldr	w0, [x27, 44]
	sub	w9, w9, w1
	sub	w2, w0, w2
	lsl	w0, w21, w11
.L1205:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w7, w7, w0
	lsl	w2, w2, w0
	cmn	w11, #1
	stp	w1, w7, [x27, 36]
	str	w2, [x27, 44]
	bne	.L1206
	add	w10, w10, 32
	b	.L1195
.L1375:
	sub	w1, w24, w6
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w6
	sub	w10, w10, w1
	add	w6, w1, w6
	mov	x0, x27
	str	w6, [x29, 152]
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w6, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1242
	.p2align 3
.L1357:
	sub	w9, w24, w6
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w6
	mov	w1, w9
	mov	x0, x27
	sub	w26, w7, w9
	stp	w6, w9, [x29, 148]
	bl	BsGet
	and	w7, w26, 7
	ldp	w6, w9, [x29, 148]
	lsl	w0, w0, w7
	orr	w20, w0, w20
	add	w6, w9, w6
	stp	w20, w6, [x27, 36]
	b	.L1229
.L1364:
	cmp	w20, 64
	bgt	.L1379
	add	w7, w20, 64
	b	.L1265
.L1379:
	mov	w1, 128
	mov	x0, x27
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w7, w20, 64
	b	.L1265
	.p2align 3
.L1346:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w7
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x27
	str	w2, [x29, 120]
	stp	w9, w7, [x29, 108]
	str	w10, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w10, [x29, 136]
	ldp	w9, w7, [x29, 108]
	and	w10, w10, 7
	ldr	w11, [x29, 144]
	lsl	w0, w0, w10
	ldr	w2, [x29, 120]
	orr	w1, w0, w9
	add	w7, w11, w7
	mov	w9, w1
	stp	w1, w7, [x27, 36]
	b	.L1188
.L1359:
	cmp	w20, 64
	bgt	.L1380
	add	w7, w20, 64
	b	.L1233
.L1376:
	sub	w1, w28, w9
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w9
	sub	w12, w12, w1
	add	w9, w1, w9
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w7, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w9, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w7, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w9, [x29, 144]
	orr	w7, w0, w7
	b	.L1199
.L1363:
	mov	w0, 24
	sub	w7, w24, w22
	sub	w9, w0, w22
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w22, w9, w22
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w22, [x27, 36]
	b	.L1268
.L1354:
	mov	x1, x27
	mov	x0, x20
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1218
.L1347:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w7
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x27
	str	w9, [x29, 120]
	stp	w2, w7, [x29, 108]
	str	w10, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w10, [x29, 136]
	ldr	w9, [x29, 120]
	and	w10, w10, 7
	ldr	w11, [x29, 144]
	ldp	w2, w7, [x29, 108]
	lsl	w0, w0, w10
	orr	w1, w0, w9
	add	w7, w11, w7
	mov	w9, w1
	stp	w1, w7, [x27, 36]
	b	.L1191
.L1380:
	mov	w1, 128
	mov	x0, x27
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w7, w20, 64
	b	.L1233
.L1358:
	sub	w6, w24, w28
	mov	w0, 16
	and	w6, w6, -8
	sub	w9, w0, w28
	sub	w9, w9, w6
	mov	w1, w6
	mov	x0, x27
	stp	w9, w6, [x29, 148]
	bl	BsGet
	ldp	w9, w6, [x29, 148]
	and	w9, w9, 7
	add	w6, w6, w28
	lsl	w0, w0, w9
	mov	w28, w6
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w6, [x27, 36]
	b	.L1236
.L1378:
	sub	w1, w28, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w7
	sub	w12, w12, w1
	add	w7, w1, w7
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w9, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w9, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w7, [x29, 144]
	orr	w9, w0, w9
	b	.L1204
.L1349:
	cmp	w9, 64
	mov	w10, w9
	bgt	.L1381
	add	w10, w10, 64
	b	.L1195
.L1381:
	mov	w1, 128
	mov	x0, x27
	str	w9, [x29, 144]
	bl	Vp9_Cabac_Read
	ldr	w10, [x29, 144]
	add	w0, w0, w10, lsl 1
	sub	w10, w0, #65
	add	w10, w10, 64
	b	.L1195
.L1348:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w9, w0, w7
	sub	w9, w9, w11
	mov	w1, w11
	mov	x0, x27
	str	w10, [x29, 120]
	stp	w2, w7, [x29, 108]
	str	w9, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w9, [x29, 136]
	ldr	w10, [x29, 120]
	and	w9, w9, 7
	ldr	w11, [x29, 144]
	ldp	w2, w7, [x29, 108]
	lsl	w0, w0, w9
	orr	w1, w0, w10
	add	w7, w11, w7
	mov	w10, w1
	stp	w1, w7, [x27, 36]
	b	.L1198
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.align	3
.LC19:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w20, w0
	mov	x22, x1
	mov	x0, x30
	mov	x21, x2
	mov	x23, x3
	mov	x24, x4
	bl	_mcount
	ldrsb	w0, [x22, w20, uxtw]
	cmp	w0, wzr
	ble	.L1391
	mov	x4, x24
	mov	x3, x23
	mov	x2, x21
	mov	x1, x22
	bl	Vp9_AdaptProbs
	mov	w19, w0
	add	w0, w20, 1
	ldrsb	w0, [x22, x0]
	cmp	w0, wzr
	ble	.L1392
.L1385:
	mov	x4, x24
	mov	x3, x23
	mov	x2, x21
	mov	x1, x22
	bl	Vp9_AdaptProbs
.L1386:
	ubfx	x20, x20, 1, 31
	adds	w0, w19, w0
	ldrb	w4, [x23, x20]
	beq	.L1387
	ldr	x6, .LC21
	cmp	w0, 20
	mov	w5, 20
	lsr	w1, w0, 1
	csel	w5, w0, w5, ls
	add	x6, x6, 512
	add	w19, w1, w19, lsl 8
	mov	w3, 256
	mov	w2, 255
	udiv	w1, w19, w0
	ldrb	w5, [x6, x5]
	cmp	w1, wzr
	sub	w3, w3, w5
	csinc	w1, w1, wzr, gt
	mul	w3, w3, w4
	cmp	w1, w2
	csel	w2, w1, w2, le
	add	w1, w3, 128
	and	w2, w2, 255
	madd	w1, w2, w5, w1
	ubfx	x4, x1, 8, 8
.L1387:
	strb	w4, [x21, x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1391:
	neg	w0, w0
	ldr	w19, [x24, w0, sxtw 2]
	add	w0, w20, 1
	ldrsb	w0, [x22, x0]
	cmp	w0, wzr
	bgt	.L1385
.L1392:
	neg	w0, w0
	ldr	w0, [x24, w0, sxtw 2]
	b	.L1386
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	3
.LC21:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Lf_Init_Lut
	.type	Lf_Init_Lut, %function
Lf_Init_Lut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	strb	wzr, [x19, 64]
	strb	wzr, [x19, 67]
	strb	wzr, [x19, 68]
	strb	wzr, [x19, 69]
	strb	wzr, [x19, 70]
	strb	wzr, [x19, 71]
	strb	wzr, [x19, 72]
	strb	wzr, [x19, 65]
	strb	wzr, [x19, 66]
	strb	wzr, [x19, 73]
	strb	wzr, [x19, 76]
	strb	w0, [x19, 74]
	strb	w0, [x19, 75]
	strb	w0, [x19, 77]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Lf_Init_Lut, .-Lf_Init_Lut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Loop_Filter_Init
	.type	VP9_Loop_Filter_Init, %function
VP9_Loop_Filter_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	strb	wzr, [x19, 64]
	strb	wzr, [x19, 67]
	strb	wzr, [x19, 68]
	strb	wzr, [x19, 69]
	strb	wzr, [x19, 70]
	strb	wzr, [x19, 71]
	strb	wzr, [x19, 72]
	strb	wzr, [x19, 65]
	strb	wzr, [x19, 66]
	strb	wzr, [x19, 73]
	strb	wzr, [x19, 76]
	strb	w0, [x19, 74]
	strb	w0, [x19, 75]
	strb	w0, [x19, 77]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Loop_Filter_Init, .-VP9_Loop_Filter_Init
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_InitDecPara
	.type	VP9_InitDecPara, %function
VP9_InitDecPara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 270336
	bl	_mcount
	ldr	x22, .LC23
	add	x20, x19, 2644
	mov	x2, 5488
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x22, 96]
	blr	x3
	add	x0, x21, 274432
	mov	w1, 3
	add	x0, x0, 4040
	str	w1, [x19, 7712]
	bl	ResetVoQueue
	str	wzr, [x19, 2876]
	ldr	x3, [x22, 96]
	mov	w0, 2
	mov	x2, 16
	str	w0, [x19, 2880]
	mov	w1, 0
	add	x0, x19, 2708
	blr	x3
	strb	wzr, [x19, 2964]
	mov	w1, 1
	strb	wzr, [x19, 2967]
	strb	wzr, [x19, 2968]
	strb	wzr, [x19, 2969]
	strb	wzr, [x19, 2970]
	strb	wzr, [x19, 2971]
	strb	wzr, [x19, 2972]
	strb	wzr, [x19, 2965]
	strb	wzr, [x19, 2966]
	strb	wzr, [x19, 2973]
	strb	wzr, [x19, 2976]
	strb	w1, [x19, 2974]
	strb	w1, [x19, 2975]
	strb	w1, [x19, 2977]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_InitDecPara, .-VP9_InitDecPara
	.align	3
.LC23:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_Init
	.type	VP9DEC_Init, %function
VP9DEC_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x1
	add	x19, x20, 278528
	bl	_mcount
	ldr	x1, .LC27
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w22, [x19, 544]
	ldr	w0, [x23, 656]
	cmp	w0, 1
	beq	.L1409
	mov	w24, 0
	mov	w25, 0
	add	x21, x20, 311296
.L1397:
	ldr	x26, .LC28
	mov	x2, 52440
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x26, 96]
	blr	x3
	str	w22, [x19, 544]
	add	x0, x20, 274432
	add	x0, x0, 4040
	bl	ResetVoQueue
	str	x23, [x20]
	mov	x0, x20
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x21, 3272]
	beq	.L1410
	ldr	x1, [x20]
	add	x19, x20, 270336
	add	x22, x19, 2576
	ldr	w0, [x1, 8]
	str	w0, [x19, 2576]
	mov	w0, 3
	stp	w0, wzr, [x22, 8]
	str	w0, [x22, 64]
	ldr	w0, [x1, 48]
	str	w0, [x22, 16]
	ldr	w1, [x1, 52]
	str	w1, [x22, 20]
	bl	MEM_Phy2Vir
	str	x0, [x22, 24]
	mov	w1, 2048
	str	w1, [x22, 32]
	str	wzr, [x21, 3140]
	str	wzr, [x21, 3144]
	str	wzr, [x21, 3168]
	str	wzr, [x21, 3172]
	str	wzr, [x21, 3208]
	str	wzr, [x21, 3212]
	ldr	w0, [x23, 656]
	cmp	w0, 1
	beq	.L1411
	str	wzr, [x21, 3128]
	str	wzr, [x22, 4]
.L1401:
	ldr	x3, [x26, 96]
	mov	w1, 0
	mov	x2, 32
	add	x0, x21, 3176
	blr	x3
	mov	x0, x20
	bl	VP9_InitDecPara
	add	x0, x19, 2724
	add	x1, x19, 2760
	.p2align 2
.L1402:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 32]
	cmp	x0, x1
	bne	.L1402
	add	x0, x19, 2840
	add	x2, x19, 2876
	mov	w1, -1
	.p2align 2
.L1403:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L1403
	add	x0, x19, 2796
	mov	w1, 0
	mov	w2, 1
	.p2align 2
.L1404:
	str	w1, [x0]
	add	w1, w1, 1
	str	w2, [x0, -72]
	cmp	w1, 8
	add	x0, x0, 4
	bne	.L1404
	mov	w0, 0
.L1399:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1409:
	add	x21, x20, 311296
	add	x0, x20, 270336
	ldr	w25, [x21, 3128]
	ldr	w24, [x0, 2580]
	b	.L1397
	.p2align 3
.L1411:
	str	w25, [x21, 3128]
	str	w24, [x22, 4]
	b	.L1401
.L1410:
	ldr	x1, .LC30
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L1399
	.size	VP9DEC_Init, .-VP9DEC_Init
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC28:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC30:
	.xword	.LC29
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ParseSuperFrameIndex
	.type	Vp9_ParseSuperFrameIndex, %function
Vp9_ParseSuperFrameIndex:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	mov	x19, x3
	bl	_mcount
	cmp	w21, wzr
	ble	.L1425
	sxtw	x0, w21
	add	x1, x22, x0
	ldrb	w1, [x1, -1]
	str	wzr, [x19]
	and	w2, w1, 224
	cmp	w2, 192
	beq	.L1426
.L1412:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1426:
	and	w7, w1, 7
	ubfx	x3, x1, 3, 2
	add	w7, w7, 1
	add	w2, w3, 1
	mul	w6, w7, w2
	add	w6, w6, 2
	cmp	w21, w6
	blt	.L1412
	sub	w21, w21, w6
	ldrb	w4, [x22, w21, sxtw]
	cmp	w4, w1
	bne	.L1412
	add	x0, x0, 1
	uxtb	x8, w3
	sub	x0, x0, x6, sxtw
	mov	x3, 0
	add	x6, x22, x0
	add	x8, x8, 1
	cbz	w7, .L1416
	.p2align 2
.L1421:
	mov	x0, 0
	mov	w4, 0
	cbz	w2, .L1427
	.p2align 2
.L1422:
	ldrb	w1, [x6, x0]
	lsl	w5, w0, 3
	add	x0, x0, 1
	cmp	w2, w0
	lsl	w1, w1, w5
	orr	w4, w4, w1
	bhi	.L1422
	add	x6, x6, x8
.L1420:
	str	w4, [x20, x3, lsl 2]
	add	x3, x3, 1
	cmp	w7, w3
	bhi	.L1421
.L1416:
	str	w7, [x19]
	b	.L1412
	.p2align 3
.L1425:
	ldr	x1, .LC32
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1412
.L1427:
	mov	w4, w2
	b	.L1420
	.size	Vp9_ParseSuperFrameIndex, .-Vp9_ParseSuperFrameIndex
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_GetImageBuffer
	.type	VP9_GetImageBuffer, %function
VP9_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 270336
	add	x21, x19, 311296
	add	x22, x20, 2576
	bl	_mcount
	ldr	w0, [x22, 5156]
	cmp	w0, 1
	beq	.L1447
	ldr	w0, [x21, 3272]
	mov	w1, 1
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
.L1430:
	tbnz	w1, #31, .L1448
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L1449
	add	x20, x20, 2576
	ldr	x1, .LC38
	ldr	w2, [x20, 52]
	mov	w0, 18
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L1434
	ldr	x1, [x19, 40]
	cbz	x1, .L1434
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC40
	bl	dprint_vfmw
	ldr	w0, [x20, 5156]
	cmp	w0, 1
	beq	.L1450
	ldr	x1, [x19, 32]
	mov	w0, 0
	str	wzr, [x1, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1434:
	ldr	x1, .LC42
	mov	w2, 2258
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1432:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1448:
	ldr	x1, .LC34
	mov	w0, 0
	bl	dprint_vfmw
	add	x1, x19, 274432
	ldr	w0, [x21, 3272]
	add	x1, x1, 4040
	bl	FSP_ClearNotInVoQueue
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1447:
	ldr	w0, [x21, 3272]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
	b	.L1430
	.p2align 3
.L1449:
	ldr	x1, .LC36
	mov	w2, 2246
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1450:
	ldr	w3, [x20, 5160]
	cmp	w3, 8
	bls	.L1437
	ldr	x2, .LC43
	mov	w0, 0
	ldr	x1, .LC45
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1432
	.p2align 3
.L1437:
	add	x20, x20, x3, sxtw 2
	ldr	w0, [x21, 3272]
	ldr	w1, [x20, 264]
	bl	FSP_GetLogicFs
	mov	x3, x0
	cbz	x0, .L1451
	ldr	x4, [x3, 32]
	add	x1, x0, 48
	str	x4, [x19, 32]
	mov	x2, 632
	add	x0, x19, 48
	ldr	x3, [x3, 32]
	str	x3, [x19, 40]
	ldr	w3, [x4, 72]
	str	w3, [x19, 20]
	bl	memcpy
	strb	wzr, [x19, 2]
	ldrsb	w0, [x19, 3]
	str	w0, [x19, 196]
	mov	w0, 0
	b	.L1432
.L1451:
	ldr	x3, .LC47
	mov	w2, 2275
	ldr	x1, .LC49
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1432
	.size	VP9_GetImageBuffer, .-VP9_GetImageBuffer
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
.LC43:
	.xword	.LANCHOR0
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_FreeCurFb
	.type	VP9_FreeCurFb, %function
VP9_FreeCurFb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x1, x0
	mov	x0, x30
	add	x20, x1, 270336
	add	x19, x1, 311296
	bl	_mcount
	ldr	w1, [x20, 2628]
	tbnz	w1, #31, .L1453
	ldr	w0, [x19, 3272]
	mov	w2, 1
	bl	FSP_ClearLogicFs
.L1453:
	ldr	w0, [x19, 3164]
	cmp	w0, 8
	bhi	.L1452
	add	x0, x20, x0, sxtw 2
	str	wzr, [x0, 2724]
.L1452:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_FreeCurFb, .-VP9_FreeCurFb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_SetImgFormat
	.type	VP9_SetImgFormat, %function
VP9_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1456
	add	x21, x20, 270336
	add	x0, x20, 311296
	ldr	w1, [x21, 2628]
	ldr	w0, [x0, 3272]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1456
	ldr	x1, [x20]
	mov	x2, -1
	mov	w5, 5
	mov	w4, 1
	ldr	x1, [x1, 56]
	str	x1, [x0, 584]
	ldr	x1, [x20]
	str	x2, [x1, 56]
	ldr	w3, [x21, 2636]
	ldrb	w1, [x0, 64]
	ldrb	w2, [x0, 65]
	bfi	w1, w3, 0, 2
	and	w3, w3, 3
	orr	w2, w2, 12
	and	w1, w1, -29
	bfi	w1, w5, 5, 3
	bfi	w2, w4, 4, 2
	strb	w1, [x0, 64]
	mov	w1, 0
	strb	w2, [x0, 65]
	ldr	w2, [x0, 64]
	and	w2, w2, -114689
	str	w2, [x0, 64]
	lsr	w4, w2, 8
	lsr	w2, w2, 16
	and	w4, w4, -4
	strb	w4, [x0, 65]
	ldrb	w4, [x21, 2644]
	bfi	w2, w4, 1, 1
	strb	w2, [x0, 66]
	ldr	w2, [x21, 2648]
	str	w2, [x0, 120]
	stp	w3, w3, [x0, 56]
	bl	SetAspectRatio
	ldr	w5, [x21, 2664]
	str	w5, [x19, 68]
	ldr	w4, [x21, 2668]
	str	w4, [x19, 72]
	ldr	x0, [x20]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1460
	ldr	w0, [x19, 36]
	ldr	x6, [x19, 504]
.L1461:
	ldr	w1, [x21, 2488]
	add	w2, w5, 255
	str	w1, [x19, 124]
	and	w2, w2, -256
	add	w1, w2, 3
	cmp	w2, wzr
	ldr	w3, [x21, 2496]
	csel	w2, w1, w2, lt
	str	w3, [x19, 128]
	asr	w2, w2, 2
	ubfiz	w7, w2, 4, 27
	ldr	w1, [x21, 2500]
	str	w1, [x19, 132]
	ldr	w1, [x21, 2112]
	str	w1, [x19, 112]
	ldr	w1, [x21, 2120]
	str	w1, [x19, 116]
	ldr	x1, [x20]
	ldr	w3, [x21, 2124]
	ldr	w1, [x1, 940]
	str	w1, [x19, 168]
	lsl	w1, w3, 2
	sub	w1, w1, w3
	add	x6, x6, x3, sxtw
	ldr	x8, [x20]
	add	w3, w3, w0
	add	w1, w1, w1, lsr 31
	add	w0, w0, w1, asr 1
	ldr	w1, [x8, 940]
	str	w1, [x19, 172]
	ldr	w1, [x21, 2516]
	str	w1, [x19, 136]
	add	w1, w4, 63
	and	w1, w1, -64
	ldr	w8, [x21, 2520]
	madd	w2, w1, w2, w0
	stp	w3, w0, [x19, 40]
	lsr	w1, w4, 1
	lsr	w3, w5, 1
	str	w2, [x19, 48]
	stp	w5, w4, [x19, 76]
	str	w1, [x19, 88]
	stp	w8, w7, [x19, 140]
	str	x6, [x19, 512]
	str	w3, [x19, 84]
.L1456:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1460:
	ldr	w2, [x19, 112]
	add	w1, w4, 15
	lsr	w1, w1, 4
	ldr	w0, [x19, 36]
	lsl	w3, w2, 4
	ldr	x6, [x19, 504]
	mul	w1, w1, w3
	add	w3, w1, w0
	str	w3, [x19, 40]
	add	x1, x6, x1, sxtw
	str	x1, [x19, 512]
	stp	w0, w3, [x19, 20]
	add	w1, w2, w0
	add	w2, w2, w3
	stp	w1, w2, [x19, 28]
	b	.L1461
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_VDMPostProc
	.type	VP9DEC_VDMPostProc, %function
VP9DEC_VDMPostProc:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 270336
	mov	w23, w1
	mov	w25, w2
	mov	w24, w3
	bl	_mcount
	ldr	w1, [x20, 7784]
	ldrb	w2, [x20, 2097]
	str	w1, [x29, 108]
	ldr	w1, [x20, 2484]
	strb	w2, [x20, 2644]
	str	w1, [x20, 2648]
	ldr	w27, [x20, 7792]
	cbz	w25, .L1466
	ldr	x1, .LC50
	sbfiz	x0, x24, 6, 32
	add	x0, x1, x0
	ldr	w0, [x0, 44]
	cmp	w0, 3
	beq	.L1484
.L1466:
	add	x21, x22, 311296
	ldr	w0, [x21, 3172]
	cbz	w0, .L1469
	ldr	w0, [x21, 3208]
	ldr	w1, [x21, 3212]
	cmp	w1, w0
	beq	.L1469
.L1470:
	ldr	w1, [x20, 2628]
	add	x19, x20, 2760
	ldr	w0, [x21, 3272]
	add	x28, x20, 2796
	bl	FSP_GetFsImagePtr
	mov	x26, x0
	cbnz	x0, .L1506
	b	.L1517
	.p2align 3
.L1473:
	cmp	w2, wzr
	ccmp	w0, wzr, 0, ne
	beq	.L1518
.L1474:
	add	x19, x19, 4
	cmp	x19, x28
	beq	.L1519
.L1506:
	ldr	w2, [x19]
	ldr	w0, [x19, -36]
	cmp	w2, wzr
	ldr	w1, [x19, 80]
	ccmp	w0, wzr, 4, eq
	beq	.L1473
	ldr	w0, [x21, 3272]
	mov	w2, 1
	add	x19, x19, 4
	bl	FSP_SetRef
	cmp	x19, x28
	bne	.L1506
.L1519:
	ldr	x0, .LC53
	mov	x2, 36
	add	x1, x20, 2724
	ldr	x3, [x0, 104]
	add	x0, x20, 2760
	blr	x3
	tbnz	w23, #31, .L1476
	cmp	w23, 100
	mov	w2, 100
	csel	w2, w23, w2, le
	str	w2, [x26, 152]
	ldr	x0, [x22]
	ldr	w3, [x0]
	cmp	w2, w3
	bhi	.L1520
	mov	x0, x22
	bl	VP9_SetImgFormat
	ldr	w0, [x20, 2576]
	cmp	w0, 2
	beq	.L1521
.L1478:
	ldr	w0, [x20, 7728]
	cbnz	w0, .L1480
.L1479:
	mov	w0, -1
	str	w0, [x20, 2632]
	ldr	w1, [x20, 2628]
	mov	w2, 0
	ldr	w0, [x21, 3272]
	bl	FSP_SetDisplay
	ldr	w1, [x20, 2632]
.L1481:
	cmn	w1, #1
	beq	.L1482
	ldr	w0, [x21, 3272]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1522
	ldr	w1, [x20, 2632]
	mov	w2, 1
	ldr	w0, [x21, 3272]
	add	x20, x20, 2576
	bl	FSP_SetDisplay
	add	x3, x22, 274432
	ldr	w0, [x21, 3272]
	mov	x4, x19
	add	x3, x3, 4040
	mov	x2, x22
	mov	w1, 17
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w19, w0
	bne	.L1523
.L1482:
	cbz	w25, .L1484
	ldr	x0, .LC50
	sbfiz	x24, x24, 6, 32
	add	x24, x0, x24
	ldr	w0, [x24, 44]
	cmp	w0, 2
	beq	.L1468
.L1484:
	add	x0, x22, 274432
	ldr	w19, [x0, 3636]
	cbz	w19, .L1524
.L1468:
	mov	w19, 0
.L1515:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1518:
	ldr	w0, [x21, 3272]
	mov	w2, 0
	bl	FSP_SetRef
	b	.L1474
	.p2align 3
.L1480:
	ldr	w1, [x20, 2628]
	str	w1, [x20, 2632]
	b	.L1481
	.p2align 3
.L1524:
	add	x23, x22, 16
	add	x0, x23, 270336
	ldr	w0, [x0, 2356]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L1525
	add	x21, x22, 311296
	ldr	w0, [x21, 3236]
	cbz	w0, .L1526
.L1490:
	mov	w27, 0
.L1486:
	ldr	x0, [x21, 3256]
	cbz	x0, .L1527
.L1487:
	ldr	w0, [x29, 108]
	cbz	w0, .L1468
	mov	x0, 4708
	uxtw	x27, w27
	mov	x2, x0
	add	x1, x22, 278528
	madd	x0, x27, x0, x22
	add	x1, x1, 592
	add	x0, x0, 282624
	add	x0, x0, 1204
	bl	memcpy
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1469:
	mov	x1, x22
	mov	w0, 17
	bl	ReleasePacket
	str	wzr, [x21, 3172]
	b	.L1470
	.p2align 3
.L1476:
	mov	x0, x22
	str	wzr, [x26, 152]
	bl	VP9_SetImgFormat
	ldr	w0, [x20, 2576]
	cmp	w0, 2
	bne	.L1478
.L1521:
	ldr	w0, [x20, 2636]
	cbnz	w0, .L1479
	b	.L1478
	.p2align 3
.L1523:
	ldr	w1, [x20, 56]
	mov	w2, 0
	ldr	w0, [x21, 3272]
	bl	FSP_SetDisplay
	ldr	x1, .LC59
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1526:
	ldr	w0, [x21, 3256]
	cbnz	w0, .L1490
	ldr	w0, [x21, 3240]
	cmp	w0, wzr
	csel	w27, w27, wzr, eq
	b	.L1486
	.p2align 3
.L1527:
	ldr	x24, .LC53
	add	x23, x23, 270336
	mov	x0, x20
	mov	w2, 5120
	ldr	w1, [x23, 2356]
	add	x23, x22, 282624
	ldr	x3, [x24, 280]
	add	x25, x23, 848
	blr	x3
	ldr	x3, [x24, 104]
	add	x0, x22, 278528
	mov	x1, x20
	mov	x2, 4096
	add	x0, x0, 592
	add	x20, x20, 4096
	blr	x3
	ldr	x3, [x24, 104]
	mov	x2, 256
	mov	x1, x20
	add	x0, x23, 592
	blr	x3
	ldr	x3, [x24, 104]
	add	x1, x20, 256
	mov	x2, 256
	mov	x0, x25
	blr	x3
	ldr	w0, [x21, 3240]
	cbz	w0, .L1488
	ldr	x3, [x24, 104]
	mov	x2, 48
	mov	x1, x25
	add	x0, x23, 1108
	blr	x3
	b	.L1487
.L1488:
	ldr	w3, [x21, 3248]
	mov	x2, 48
	ldr	x4, [x24, 104]
	mov	x1, x25
	lsl	x0, x3, 2
	sub	x0, x0, x3
	add	x0, x22, x0, lsl 4
	add	x0, x0, 282624
	add	x0, x0, 1108
	blr	x4
	b	.L1487
.L1520:
	ldr	x1, .LC55
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	ldr	w1, [x20, 2628]
	mov	w2, 0
	ldr	w0, [x21, 3272]
	bl	FSP_SetDisplay
	ldr	w1, [x20, 2628]
	mov	w2, 0
	ldr	w0, [x21, 3272]
	bl	FSP_SetRef
	b	.L1515
.L1522:
	ldr	x1, .LC57
	mov	w2, 2596
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1515
.L1517:
	ldr	x1, .LC52
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1515
.L1525:
	ldr	x1, .LC61
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1515
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	3
.LC50:
	.xword	g_VdmDrvParam
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC53:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_RecycleImage
	.type	VP9DEC_RecycleImage, %function
VP9DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 311296
	mov	w20, w1
	bl	_mcount
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 3272]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 3272]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9DEC_RecycleImage, .-VP9DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_GetRemainImg
	.type	VP9DEC_GetRemainImg, %function
VP9DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 274432
	add	x0, x0, 4040
	bl	GetVoLastImageID
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9DEC_GetRemainImg, .-VP9DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_GetImageBuffer
	.type	VP9DEC_GetImageBuffer, %function
VP9DEC_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 311296
	bl	_mcount
	ldr	w0, [x20, 3272]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w19, w0
	beq	.L1531
	ldr	w0, [x20, 3272]
	mov	w19, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L1536
.L1531:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1536:
	add	x1, x21, 274432
	ldr	w0, [x20, 3272]
	add	x1, x1, 4040
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9DEC_GetImageBuffer, .-VP9DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Check_Sync_Code
	.type	Check_Sync_Code, %function
Check_Sync_Code:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 73
	beq	.L1538
.L1540:
	ldr	x1, .LC63
	mov	w0, 1
	bl	dprint_vfmw
.L1537:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1538:
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 131
	bne	.L1540
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 66
	bne	.L1540
	b	.L1537
	.size	Check_Sync_Code, .-Check_Sync_Code
	.align	3
.LC63:
	.xword	.LC62
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_Frame_Size
	.type	Read_Frame_Size, %function
Read_Frame_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	x21, x1
	bl	_mcount
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 1
	mov	w1, 16
	str	w0, [x21]
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Read_Frame_Size, .-Read_Frame_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	get_free_fb
	.type	get_free_fb, %function
get_free_fb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 80]
	cbz	w0, .L1546
	add	x2, x19, 84
	mov	w0, 1
	.p2align 2
.L1544:
	ldr	w3, [x2]
	add	x2, x2, 4
	cbz	w3, .L1543
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L1544
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1546:
	mov	w0, 0
.L1543:
	add	x19, x19, x0, sxtw 2
	mov	w1, 1
	str	w1, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	get_free_fb, .-get_free_fb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Display_Size
	.type	Setup_Display_Size, %function
Setup_Display_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 52]
	stp	w1, w0, [x19, 60]
	mov	w1, 1
	mov	x0, x20
	stp	wzr, wzr, [x29, 40]
	bl	BsGet
	cbz	w0, .L1552
	add	x2, x29, 44
	add	x1, x29, 40
	mov	x0, x20
	bl	Read_Frame_Size
.L1552:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Setup_Display_Size, .-Setup_Display_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Update_CP_Size
	.type	VP9_Update_CP_Size, %function
VP9_Update_CP_Size:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5060]
	ldr	w5, [x19, 5112]
	ldr	w4, [x19, 5116]
	add	x0, x19, x0, sxtw 4
	add	w3, w5, 7
	add	w2, w4, 7
	and	w3, w3, -8
	and	w2, w2, -8
	asr	w7, w3, 3
	asr	w6, w2, 3
	str	w7, [x19, 5152]
	str	w6, [x19, 5156]
	str	w3, [x0, 5296]
	str	w2, [x0, 5300]
	str	w5, [x0, 5304]
	str	w4, [x0, 5308]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Update_CP_Size, .-VP9_Update_CP_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Frame_Size
	.type	Setup_Frame_Size, %function
Setup_Frame_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x2, x20, 4096
	mov	x0, x21
	add	x19, x2, 964
	add	x1, x2, 1016
	add	x2, x2, 1020
	ldp	w4, w3, [x19, 52]
	stp	w4, w3, [x19, 72]
	bl	Read_Frame_Size
	ldr	w2, [x20, 5060]
	mov	x1, x19
	ldp	w6, w5, [x19, 52]
	mov	x0, x21
	add	x2, x20, x2, sxtw 4
	add	w4, w6, 7
	add	w3, w5, 7
	and	w4, w4, -8
	and	w3, w3, -8
	asr	w8, w4, 3
	asr	w7, w3, 3
	stp	w8, w7, [x19, 92]
	str	w4, [x2, 5296]
	str	w3, [x2, 5300]
	str	w6, [x2, 5304]
	str	w5, [x2, 5308]
	bl	Setup_Display_Size
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Setup_Frame_Size, .-Setup_Frame_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	setup_frame_size_with_refs
	.type	setup_frame_size_with_refs, %function
setup_frame_size_with_refs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x1, 4096
	mov	x23, x1
	add	x22, x20, 964
	mov	w19, 0
	bl	_mcount
.L1562:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	cbnz	w0, .L1568
	add	w19, w19, 1
	cmp	w19, 3
	bne	.L1562
	ldr	w4, [x20, 1016]
	add	x2, x20, 1020
	ldr	w3, [x20, 1020]
	add	x1, x20, 1016
	str	w4, [x20, 1036]
	mov	x0, x21
	str	w3, [x20, 1040]
	bl	Read_Frame_Size
	ldr	w5, [x20, 1016]
	ldr	w4, [x20, 1020]
.L1561:
	ldr	w0, [x23, 5060]
	add	w3, w5, 7
	add	w2, w4, 7
	and	w3, w3, -8
	and	w2, w2, -8
	asr	w6, w3, 3
	add	x0, x23, x0, sxtw 4
	str	w6, [x20, 1056]
	asr	w1, w2, 3
	str	w1, [x20, 1060]
	mov	x1, x22
	str	w3, [x0, 5296]
	str	w2, [x0, 5300]
	str	w5, [x0, 5304]
	str	w4, [x0, 5308]
	mov	x0, x21
	bl	Setup_Display_Size
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1568:
	add	x19, x23, x19, sxtw 2
	ldr	w3, [x20, 1016]
	ldr	w2, [x20, 1020]
	ldr	w1, [x19, 184]
	str	w3, [x20, 1036]
	str	w2, [x20, 1040]
	add	x1, x23, x1, sxtw 4
	ldr	w5, [x1, 5304]
	str	w5, [x20, 1016]
	ldr	w4, [x1, 5308]
	str	w4, [x20, 1020]
	b	.L1561
	.size	setup_frame_size_with_refs, .-setup_frame_size_with_refs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Set_Default_Lf_Deltas
	.type	Set_Default_Lf_Deltas, %function
Set_Default_Lf_Deltas:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	mov	w1, -1
	strb	w0, [x19]
	strb	w0, [x19, 1]
	strb	w0, [x19, 2]
	strb	wzr, [x19, 3]
	strb	w1, [x19, 4]
	strb	w1, [x19, 5]
	strb	wzr, [x19, 6]
	strb	wzr, [x19, 7]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Set_Default_Lf_Deltas, .-Set_Default_Lf_Deltas
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Clearall_Segfeatures
	.type	VP9_Clearall_Segfeatures, %function
VP9_Clearall_Segfeatures:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC64
	mov	x2, 64
	mov	w1, 0
	add	x0, x19, 16
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 80
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Clearall_Segfeatures, .-VP9_Clearall_Segfeatures
	.align	3
.LC64:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Setup_Past_Independence
	.type	VP9_Setup_Past_Independence, %function
VP9_Setup_Past_Independence:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC65
	add	x0, x19, 4096
	mov	x2, 32
	add	x21, x0, 1088
	mov	w1, 0
	ldr	x3, [x20, 96]
	add	x0, x0, 1168
	blr	x3
	strb	wzr, [x21, 3]
	mov	w1, 1
	mov	w2, -1
	ldr	x3, [x20, 96]
	add	x0, x19, 64
	strb	w1, [x19, 336]
	strb	w1, [x19, 337]
	strb	w1, [x19, 338]
	mov	w1, 0
	strb	w2, [x19, 340]
	strb	w2, [x19, 341]
	mov	x2, 16
	strb	wzr, [x19, 339]
	strb	wzr, [x19, 342]
	strb	wzr, [x19, 343]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Setup_Past_Independence, .-VP9_Setup_Past_Independence
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_LoopFilter
	.type	Setup_LoopFilter, %function
Setup_LoopFilter:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 8]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	wzr, [x19, 1]
	str	w0, [x19, 12]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19]
	cbnz	w0, .L1597
.L1572:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1597:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 1]
	cbz	w0, .L1572
	add	x21, x19, 2
	add	x22, x19, 6
.L1578:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1598
.L1575:
	add	x21, x21, 1
	cmp	x21, x22
	bne	.L1578
	mov	w1, 1
	mov	x0, x20
	add	x19, x19, 8
	bl	BsGet
	cbnz	w0, .L1599
.L1579:
	add	x22, x22, 1
	cmp	x22, x19
	beq	.L1572
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbz	w0, .L1579
.L1599:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1581
	neg	w1, w1
.L1581:
	strb	w1, [x22]
	b	.L1579
	.p2align 3
.L1598:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1577
	neg	w1, w1
.L1577:
	strb	w1, [x21]
	b	.L1575
	.size	Setup_LoopFilter, .-Setup_LoopFilter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_Delta_Q
	.type	Read_Delta_Q, %function
Read_Delta_Q:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 1
	mov	x0, x20
	ldr	w21, [x19]
	bl	BsGet
	cbnz	w0, .L1607
.L1601:
	str	w0, [x19]
	cmp	w0, w21
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1607:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	mov	w1, w0
	asr	w0, w0, 1
	tbz	x1, 0, .L1601
	neg	w0, w0
	str	w0, [x19]
	cmp	w0, w21
	cset	w0, ne
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Read_Delta_Q, .-Read_Delta_Q
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Quantization
	.type	Setup_Quantization, %function
Setup_Quantization:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 240]
	add	x1, x19, 244
	mov	x0, x20
	bl	Read_Delta_Q
	add	x1, x19, 248
	mov	x0, x20
	bl	Read_Delta_Q
	add	x1, x19, 252
	mov	x0, x20
	bl	Read_Delta_Q
	ldr	w0, [x19, 240]
	cbnz	w0, .L1610
	ldr	w1, [x19, 244]
	cbnz	w1, .L1609
	ldr	w1, [x19, 248]
	cbnz	w1, .L1609
	ldr	w0, [x19, 252]
	cmp	w0, wzr
	cset	w0, eq
.L1609:
	str	w0, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1610:
	mov	w0, 0
	str	w0, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Setup_Quantization, .-Setup_Quantization
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Enable_Segfeature
	.type	VP9_Enable_Segfeature, %function
VP9_Enable_Segfeature:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	w20, w2
	bl	_mcount
	add	x1, x21, x19, sxtw 2
	mov	w3, 1
	lsl	w2, w3, w20
	ldr	w0, [x1, 80]
	orr	w2, w0, w2
	str	w2, [x1, 80]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Enable_Segfeature, .-VP9_Enable_Segfeature
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Seg_Feature_Data_Max
	.type	VP9_Seg_Feature_Data_Max, %function
VP9_Seg_Feature_Data_Max:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC66
	add	x0, x0, 560
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Seg_Feature_Data_Max, .-VP9_Seg_Feature_Data_Max
	.align	3
.LC66:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_Unsigned_Bits
	.type	Get_Unsigned_Bits, %function
Get_Unsigned_Bits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1
	mov	w0, 0
	bls	.L1615
	subs	w1, w19, #1
	beq	.L1615
	.p2align 2
.L1616:
	lsr	w1, w1, 1
	add	w0, w0, 1
	cbnz	w1, .L1616
.L1615:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_Unsigned_Bits, .-Get_Unsigned_Bits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Decode_Unsigned_Max
	.type	Decode_Unsigned_Max, %function
Decode_Unsigned_Max:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 1
	mov	w1, 0
	bls	.L1621
	subs	w0, w19, #1
	beq	.L1621
	.p2align 2
.L1622:
	lsr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1622
.L1621:
	mov	x0, x20
	bl	BsGet
	cmp	w19, w0
	csel	w0, w19, w0, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Decode_Unsigned_Max, .-Decode_Unsigned_Max
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Is_Segfeature_Signed
	.type	VP9_Is_Segfeature_Signed, %function
VP9_Is_Segfeature_Signed:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC68
	add	x0, x0, 576
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Is_Segfeature_Signed, .-VP9_Is_Segfeature_Signed
	.align	3
.LC68:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Set_Segdata
	.type	VP9_Set_Segdata, %function
VP9_Set_Segdata:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w3
	mov	w21, w1
	bl	_mcount
	ldr	x22, .LC70
	add	x0, x22, 560
	ldr	w23, [x0, w19, uxtw 2]
	cmp	w23, w20
	blt	.L1633
	tbnz	w20, #31, .L1634
.L1630:
	sbfiz	x21, x21, 2, 32
	add	x19, x21, x19, uxtw
	add	x19, x19, 8
	strh	w20, [x24, x19, lsl 1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1633:
	ldr	x1, .LC72
	mov	w3, 2982
	add	x2, x22, 592
	mov	w0, 0
	bl	dprint_vfmw
	tbz	w20, #31, .L1630
.L1634:
	add	x0, x22, 576
	ldr	w0, [x0, w19, uxtw 2]
	cbz	w0, .L1635
.L1631:
	neg	w0, w20
	cmp	w23, w0
	bge	.L1630
	ldr	x1, .LC72
	mov	w3, 2994
	add	x2, x22, 592
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1630
	.p2align 3
.L1635:
	ldr	x1, .LC72
	mov	w3, 2989
	add	x2, x22, 592
	bl	dprint_vfmw
	b	.L1631
	.size	VP9_Set_Segdata, .-VP9_Set_Segdata
	.align	3
.LC70:
	.xword	.LANCHOR0
	.align	3
.LC72:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mi_Cols_Aligned_To_Sb
	.type	Mi_Cols_Aligned_To_Sb, %function
Mi_Cols_Aligned_To_Sb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	and	w0, w0, -8
	ldp	x29, x30, [sp], 32
	ret
	.size	Mi_Cols_Aligned_To_Sb, .-Mi_Cols_Aligned_To_Sb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	To_Sbs
	.type	To_Sbs, %function
To_Sbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	asr	w0, w0, 3
	ldp	x29, x30, [sp], 32
	ret
	.size	To_Sbs, .-To_Sbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Get_Tile_N_Bits
	.type	VP9_Get_Tile_N_Bits, %function
VP9_Get_Tile_N_Bits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	add	w3, w19, 7
	mov	w4, 0
	asr	w3, w3, 3
	cmp	w3, 3
	bgt	.L1640
	b	.L1639
	.p2align 3
.L1644:
	mov	w4, w0
.L1640:
	add	w0, w4, 1
	asr	w5, w3, w0
	cmp	w5, 3
	bgt	.L1644
	cmp	w4, wzr
	csel	w4, w4, wzr, ge
.L1639:
	cmp	w3, 64
	mov	w0, 0
	ble	.L1641
	mov	w6, 64
	.p2align 2
.L1642:
	add	w0, w0, 1
	lsl	w5, w6, w0
	cmp	w5, w3
	blt	.L1642
.L1641:
	str	w0, [x21]
	str	w4, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Get_Tile_N_Bits, .-VP9_Get_Tile_N_Bits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Tile_Info
	.type	Setup_Tile_Info, %function
Setup_Tile_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x21, 92]
	add	w1, w1, 7
	asr	w1, w1, 3
	cmp	w1, 3
	ble	.L1648
	mov	w19, 0
	b	.L1649
	.p2align 3
.L1660:
	mov	w19, w0
.L1649:
	add	w0, w19, 1
	asr	w2, w1, w0
	cmp	w2, 3
	bgt	.L1660
	cmp	w19, wzr
	csel	w19, w19, wzr, ge
	cmp	w1, 64
	ble	.L1661
.L1658:
	mov	w0, 0
	mov	w3, 64
	.p2align 2
.L1651:
	add	w0, w0, 1
	lsl	w2, w3, w0
	cmp	w1, w2
	bgt	.L1651
.L1650:
	subs	w19, w19, w0
	str	w0, [x21, 100]
	bne	.L1670
	b	.L1653
	.p2align 3
.L1656:
	ldr	w0, [x21, 100]
	subs	w19, w19, #1
	add	w0, w0, 1
	str	w0, [x21, 100]
	beq	.L1653
.L1670:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1656
.L1653:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 104]
	cbz	w0, .L1647
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w1, [x21, 104]
	add	w0, w1, w0
	str	w0, [x21, 104]
.L1647:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1648:
	cmp	w1, 64
	mov	w19, 0
	bgt	.L1658
	str	wzr, [x21, 100]
	b	.L1653
	.p2align 3
.L1661:
	mov	w0, 0
	b	.L1650
	.size	Setup_Tile_Info, .-Setup_Tile_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Segmentation
	.type	Setup_Segmentation, %function
Setup_Segmentation:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x23, 1]
	strb	wzr, [x23, 2]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23]
	cbnz	w0, .L1709
.L1673:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1709:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 1]
	cbz	w0, .L1676
	add	x19, x23, 5
	add	x20, x23, 12
	b	.L1678
	.p2align 3
.L1677:
	strb	w1, [x19], 1
	cmp	x19, x20
	beq	.L1710
.L1678:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbz	w0, .L1677
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19], 1
	cmp	x19, x20
	bne	.L1678
.L1710:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 4]
	cbnz	w0, .L1679
	mov	w0, -1
	strb	w0, [x23, 12]
	strb	w0, [x23, 13]
	strb	w0, [x23, 14]
.L1676:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 2]
	cbz	w0, .L1673
	mov	w1, 1
	mov	x0, x21
	add	x19, x23, 80
	mov	w24, 0
	bl	BsGet
	ldr	x20, .LC75
	strb	w0, [x23, 3]
	mov	x2, 64
	mov	w1, 0
	add	x0, x23, 16
	ldr	x3, [x20, 96]
	mov	x25, x19
	mov	w27, 1
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	blr	x3
	ldr	x26, .LC76
	.p2align 2
.L1683:
	mov	x19, 0
.L1686:
	mov	w1, 1
	mov	x0, x21
	mov	w22, w19
	mov	w20, 0
	bl	BsGet
	cbnz	w0, .L1711
.L1685:
	mov	w3, w20
	mov	w2, w22
	mov	w1, w24
	mov	x0, x23
	add	x19, x19, 1
	bl	VP9_Set_Segdata
	cmp	x19, 4
	bne	.L1686
	add	w24, w24, 1
	add	x25, x25, 4
	cmp	w24, 8
	bne	.L1683
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1711:
	ldr	w3, [x25]
	add	x2, x26, 560
	lsl	w1, w27, w19
	mov	x0, x21
	orr	w1, w3, w1
	str	w1, [x25]
	ldr	w1, [x2, x19, lsl 2]
	bl	Decode_Unsigned_Max
	mov	w20, w0
	add	x0, x26, 576
	ldr	w0, [x0, x19, lsl 2]
	cbz	w0, .L1685
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L1685
	.p2align 3
.L1679:
	add	x19, x23, 15
.L1681:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbnz	w0, .L1712
.L1680:
	strb	w1, [x20], 1
	cmp	x20, x19
	bne	.L1681
	b	.L1676
	.p2align 3
.L1712:
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	b	.L1680
	.size	Setup_Segmentation, .-Setup_Segmentation
	.align	3
.LC75:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC76:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	read_interp_filter_type
	.type	read_interp_filter_type, %function
read_interp_filter_type:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 2
	bl	_mcount
	mov	w2, 1
	mov	w3, 3
	mov	w1, w2
	mov	x0, x19
	stp	w2, wzr, [x29, 32]
	stp	w20, w3, [x29, 40]
	bl	BsGet
	cbz	w0, .L1716
	ldp	x19, x20, [sp, 16]
	mov	w0, 4
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1716:
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	add	x1, x29, 48
	add	x0, x1, x0, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldr	w0, [x0, -16]
	ldp	x29, x30, [sp], 48
	ret
	.size	read_interp_filter_type, .-read_interp_filter_type
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	setup_inter_inter
	.type	setup_inter_inter, %function
setup_inter_inter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w0, w2, [x19, 68]
	ldr	w1, [x19, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x19, 60]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	setup_inter_inter, .-setup_inter_inter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ref_cnt_fb
	.type	ref_cnt_fb, %function
ref_cnt_fb:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldr	w1, [x21]
	ldr	w0, [x19, w1, sxtw 2]
	cmp	w0, wzr
	ble	.L1719
	sub	w0, w0, #1
	str	w0, [x19, w1, sxtw 2]
.L1719:
	str	w20, [x21]
	ldr	w0, [x19, w20, sxtw 2]
	add	w0, w0, 1
	str	w0, [x19, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ref_cnt_fb, .-ref_cnt_fb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_get_fixed_point_scale_factor
	.type	VP9_get_fixed_point_scale_factor, %function
VP9_get_fixed_point_scale_factor:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	w20, w1
	mov	x0, x30
	bl	_mcount
	cbz	w20, .L1723
	lsl	w0, w19, 14
	sdiv	w0, w0, w20
.L1722:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1723:
	ldr	x2, .LC79
	mov	w4, 0
	ldr	x1, .LC81
	mov	w3, 3187
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1722
	.size	VP9_get_fixed_point_scale_factor, .-VP9_get_fixed_point_scale_factor
	.align	3
.LC79:
	.xword	.LANCHOR0
	.align	3
.LC81:
	.xword	.LC80
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	check_scale_factors
	.type	check_scale_factors, %function
check_scale_factors:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w2
	mov	w22, w1
	mov	w21, w3
	bl	_mcount
	cmp	w20, w19, lsl 1
	mov	w0, 0
	bgt	.L1725
	cmp	w22, w21, lsl 1
	mov	w0, 0
	bgt	.L1725
	cmp	w19, w20, lsl 4
	bgt	.L1725
	cmp	w21, w22, lsl 4
	cset	w0, le
.L1725:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	check_scale_factors, .-check_scale_factors
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_scaled_val
	.type	VP9_scaled_val, %function
VP9_scaled_val:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	smull	x0, w19, w20
	ldp	x19, x20, [sp, 16]
	lsr	x0, x0, 14
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_scaled_val, .-VP9_scaled_val
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	vp9_setup_scale_factors
	.type	vp9_setup_scale_factors, %function
vp9_setup_scale_factors:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w3
	mov	w20, w1
	mov	w21, w2
	mov	w23, w4
	bl	_mcount
	cmp	w20, w22, lsl 1
	bgt	.L1731
	cmp	w21, w23, lsl 1
	ble	.L1741
.L1731:
	mov	w1, -1
	mov	w0, 16
	stp	w1, w1, [x19]
	stp	w0, w0, [x19, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1741:
	cmp	w22, w20, lsl 4
	bgt	.L1731
	cmp	w23, w21, lsl 4
	bgt	.L1731
	cbz	w22, .L1742
	lsl	w20, w20, 14
	sdiv	w3, w20, w22
	str	w3, [x19]
	cbz	w23, .L1743
.L1734:
	lsl	w21, w21, 14
	sdiv	w21, w21, w23
	sbfx	x0, x21, 10, 22
.L1735:
	str	w0, [x19, 12]
	sbfx	x3, x3, 10, 22
	stp	w21, w3, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1742:
	ldr	x2, .LC82
	mov	w3, 3187
	ldr	x1, .LC83
	mov	w4, 0
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w3, -1
	str	w3, [x19]
	cbnz	w23, .L1734
.L1743:
	ldr	x2, .LC82
	mov	w3, 3187
	ldr	x1, .LC83
	mov	w4, 0
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldr	w3, [x19]
	mov	w21, w0
	b	.L1735
	.size	vp9_setup_scale_factors, .-vp9_setup_scale_factors
	.align	3
.LC82:
	.xword	.LANCHOR0
	.align	3
.LC83:
	.xword	.LC80
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_ReadProfile
	.type	Vp9_Vfmw_ReadProfile, %function
Vp9_Vfmw_ReadProfile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w19, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	orr	w19, w19, w0, lsl 1
	cmp	w19, 2
	ble	.L1745
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	add	w19, w0, w19
.L1745:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_Vfmw_ReadProfile, .-Vp9_Vfmw_ReadProfile
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadBitDepthColorSpaceSampling
	.type	Vp9_ReadBitDepthColorSpaceSampling, %function
Vp9_ReadBitDepthColorSpaceSampling:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	add	x19, x1, 4096
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 976]
	mov	w1, 8
	str	w1, [x19, 1032]
	cmp	w0, 1
	bls	.L1747
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 12
	mov	w2, 10
	csel	w1, w1, w2, ne
	str	w1, [x19, 1032]
.L1747:
	add	x19, x19, 964
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	cmp	w0, 7
	str	w0, [x19, 16]
	beq	.L1749
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w21, [x19, 12]
	str	w0, [x19, 20]
	and	w21, w21, -3
	cmp	w21, 1
	beq	.L1754
	mov	w0, 1
	stp	w0, w0, [x19, 44]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1749:
	ldr	w1, [x19, 12]
	and	w1, w1, -3
	cmp	w1, 1
	beq	.L1755
	ldr	x2, .LC84
	mov	w3, 3290
	ldr	x1, .LC86
	mov	w0, 1
	add	x2, x2, 648
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1754:
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 44]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 48]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1755:
	mov	x0, x20
	stp	wzr, wzr, [x19, 44]
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_ReadBitDepthColorSpaceSampling, .-Vp9_ReadBitDepthColorSpaceSampling
	.align	3
.LC84:
	.xword	.LANCHOR0
	.align	3
.LC86:
	.xword	.LC85
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCompressedHeader
	.type	Vp9_ReadCompressedHeader, %function
Vp9_ReadCompressedHeader:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	w22, w2
	mov	w23, w3
	mov	w24, w4
	mov	w26, w5
	mov	w25, w6
	mov	w27, w7
	bl	_mcount
	str	wzr, [x29, 108]
	mov	w20, 0
	cbz	w27, .L1761
.L1757:
	mov	x2, x19
	mov	w1, w20
	mov	x0, x21
	bl	Vp9_ReadCoefProbs
	mov	x1, x19
	mov	x0, x21
	add	x7, x29, 108
	mov	w6, w26
	mov	w5, w25
	mov	w4, w24
	mov	w3, w23
	mov	w2, w22
	bl	Vp9_PrepareReadModeInfo
	ldr	w0, [x19, 40]
	mov	w1, 65502
	movk	w1, 0x3fff, lsl 16
	sub	w0, w0, #33
	cmp	w0, w1
	bls	.L1760
	ldr	x2, [x29, 112]
	mov	w0, 0
	ldr	w1, [x29, 108]
	str	w1, [x2]
	ldr	x1, [x29, 120]
	str	w20, [x1]
.L1758:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1761:
	mov	x0, x19
	bl	Vp9_ReadTxMode
	cmp	w0, 4
	mov	w20, w0
	bne	.L1757
	add	x0, x21, 4096
	mov	x1, x19
	add	x0, x0, 307
	bl	Vp9_ReadTxProbs
	b	.L1757
	.p2align 3
.L1760:
	mov	w0, -1
	b	.L1758
	.size	Vp9_ReadCompressedHeader, .-Vp9_ReadCompressedHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_UnCompressed_Header
	.type	Read_UnCompressed_Header, %function
Read_UnCompressed_Header:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	add	x22, x1, 4096
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x22, 972]
	mov	w1, 2
	mov	x0, x19
	str	w3, [x22, 968]
	bl	BsGet
	cmp	w0, 2
	beq	.L1763
	ldr	x1, .LC88
	mov	w0, 1
	bl	dprint_vfmw
.L1763:
	mov	x0, x19
	add	x21, x22, 964
	bl	Vp9_Vfmw_ReadProfile
	mov	w1, 1
	str	w0, [x21, 12]
	mov	x0, x19
	bl	BsGet
	mov	w23, w0
	cbnz	w0, .L1793
	mov	w1, 1
	mov	x0, x19
	str	wzr, [x21, 28]
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 24]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, w0
	ldr	w0, [x21, 8]
	str	w1, [x21, 40]
	cbz	w0, .L1794
	ldr	w0, [x21, 24]
	cbz	w0, .L1768
	str	wzr, [x21, 108]
.L1769:
	cbz	w1, .L1770
	str	wzr, [x22, 1076]
.L1771:
	add	x26, x22, 964
	ldr	w0, [x26, 108]
	cbz	w0, .L1772
	mov	x0, x19
	bl	Check_Sync_Code
	ldr	w0, [x26, 12]
	cmp	w0, 1
	bls	.L1773
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1774:
	mov	w1, 8
	mov	x0, x19
	add	x21, x22, 964
	bl	BsGet
	str	w0, [x22, 1080]
	mov	x1, x20
	mov	x0, x19
	bl	Setup_Frame_Size
	ldr	w0, [x21, 40]
	cbnz	w0, .L1780
.L1796:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 80]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 84]
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1052]
	ldr	w2, [x22, 972]
	cbnz	w2, .L1795
	.p2align 2
.L1782:
	mov	x0, x20
	bl	VP9_Setup_Past_Independence
	ldr	w0, [x22, 972]
	cbz	w0, .L1783
	b	.L1784
	.p2align 3
.L1793:
	mov	w1, 3
	mov	x0, x19
	mov	w23, 0
	bl	BsGet
	add	x0, x20, x0, uxtw 2
	mov	w1, 1
	ldr	w0, [x0, 152]
	stp	w1, w0, [x21, 28]
	str	wzr, [x21, 116]
	str	wzr, [x20, 344]
	str	w1, [x21, 24]
.L1765:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1772:
	mov	w1, 8
	mov	x0, x19
	add	x24, x20, 184
	add	x25, x20, 196
	bl	BsGet
	mov	x21, x24
	str	w0, [x26, 116]
.L1775:
	mov	w1, 3
	mov	x0, x19
	add	x21, x21, 4
	bl	BsGet
	add	x2, x20, x0, sxtw 2
	mov	w1, 1
	mov	x0, x19
	ldr	w2, [x2, 152]
	str	w2, [x21, -4]
	bl	BsGet
	str	w0, [x21, -120]
	cmp	x25, x21
	bne	.L1775
	mov	x0, x19
	mov	x1, x20
	bl	setup_frame_size_with_refs
	ldr	w4, [x20, 5112]
	ldr	w5, [x20, 5116]
	sub	w0, w4, #1
	cmp	w0, 4095
	bhi	.L1777
	sub	w0, w5, #1
	cmp	w0, 4095
	bhi	.L1777
	mov	w1, 1
	mov	x0, x19
	add	x21, x22, 1344
	bl	BsGet
	str	w0, [x20, 56]
	mov	x0, x19
	bl	read_interp_filter_type
	str	w0, [x22, 1084]
.L1779:
	ldrsw	x1, [x24], 4
	mov	x0, x21
	ldr	w3, [x20, 5112]
	add	x21, x21, 16
	add	x1, x1, 331
	ldr	w4, [x20, 5116]
	add	x1, x20, x1, lsl 4
	ldr	w2, [x1, 12]
	ldr	w1, [x1, 8]
	bl	vp9_setup_scale_factors
	cmp	x25, x24
	bne	.L1779
	ldp	w0, w2, [x20, 68]
	ldr	w1, [x20, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x20, 60]
	b	.L1767
	.p2align 3
.L1794:
	mov	x0, x19
	bl	Check_Sync_Code
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadBitDepthColorSpaceSampling
	mov	w0, 255
	str	w0, [x21, 116]
	mov	x1, x20
	mov	x0, x19
	ldr	w2, [x20, 5060]
	stp	w2, w2, [x20, 184]
	str	w2, [x20, 192]
	bl	Setup_Frame_Size
.L1767:
	add	x21, x22, 964
	ldr	w0, [x21, 40]
	cbz	w0, .L1796
.L1780:
	stp	wzr, wzr, [x21, 80]
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1052]
	ldr	w2, [x22, 972]
	cbz	w2, .L1782
.L1795:
	ldr	w0, [x22, 1004]
	cbnz	w0, .L1782
	ldr	w0, [x22, 1072]
	cbnz	w0, .L1782
.L1784:
	ldp	w0, w2, [x20, 68]
	ldr	w1, [x20, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x20, 60]
.L1783:
	add	x1, x20, 336
	mov	x0, x19
	bl	Setup_LoopFilter
	mov	x1, x20
	mov	x0, x19
	bl	Setup_Quantization
	add	x1, x22, 1088
	mov	x0, x19
	bl	Setup_Segmentation
	add	x1, x22, 964
	mov	x0, x19
	bl	Setup_Tile_Info
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 8]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1773:
	mov	w0, 1
	mov	w1, 8
	str	w0, [x26, 16]
	stp	w0, w0, [x26, 44]
	str	w1, [x26, 68]
	b	.L1774
	.p2align 3
.L1770:
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1076]
	b	.L1771
	.p2align 3
.L1768:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 108]
	ldr	w1, [x21, 40]
	b	.L1769
	.p2align 3
.L1777:
	ldr	x2, .LC89
	mov	w3, 3443
	ldr	x1, .LC91
	mov	w0, 1
	add	x2, x2, 688
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1765
	.size	Read_UnCompressed_Header, .-Read_UnCompressed_Header
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC89:
	.xword	.LANCHOR0
	.align	3
.LC91:
	.xword	.LC90
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	swap_frame_buffers
	.type	swap_frame_buffers, %function
swap_frame_buffers:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	mov	w1, 0
	add	x0, x0, 964
	add	x5, x19, 80
	mov	x7, x0
	ldr	w0, [x0, 116]
	cbz	w0, .L1802
	.p2align 2
.L1805:
	add	x4, x19, x1, sxtw 2
	tbz	x0, 0, .L1799
	ldr	w6, [x4, 152]
	ldr	w3, [x7]
	ldr	w2, [x5, w6, sxtw 2]
	cmp	w2, wzr
	sub	w2, w2, #1
	ble	.L1800
	str	w2, [x5, w6, sxtw 2]
.L1800:
	str	w3, [x4, 152]
	ldr	w2, [x5, w3, sxtw 2]
	add	w2, w2, 1
	str	w2, [x5, w3, sxtw 2]
.L1799:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1805
.L1802:
	ldrsw	x0, [x19, 5060]
	mov	w1, 2147483647
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 80]
	sub	w2, w2, #1
	str	w2, [x0, 80]
	stp	w1, w1, [x19, 184]
	str	w1, [x19, 192]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	swap_frame_buffers, .-swap_frame_buffers
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Set_DecParam
	.type	VP9_Set_DecParam, %function
VP9_Set_DecParam:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x19, x23, 270336
	add	x20, x23, 16
	add	x22, x19, 2644
	bl	_mcount
	add	x2, x19, 2560
	ldr	w21, [x22, 5088]
	cmp	w21, 1
	beq	.L1842
	add	x3, x20, 262144
	add	x1, x19, 2576
	add	x0, x20, 270336
	strb	wzr, [x3, 1028]
	ldr	w3, [x22, 5068]
	str	w3, [x1, 60]
	ldr	w2, [x2, 8]
	str	w3, [x0, 2112]
	and	w2, w2, -16
	str	w2, [x0, 2128]
	ldr	w2, [x1, 64]
	str	w2, [x0, 2116]
	ldr	w2, [x22, 12]
	str	w2, [x0, 2088]
	ldr	w2, [x22, 16]
	str	w2, [x0, 2092]
	ldr	x2, [x23]
	ldr	w4, [x2, 632]
	str	w4, [x0, 2468]
	ldr	w4, [x2, 636]
	str	w4, [x0, 2472]
	ldr	w4, [x2, 640]
	str	w4, [x0, 2480]
	ldr	w4, [x2, 644]
	str	w4, [x0, 2484]
	ldr	w2, [x2, 684]
	str	w2, [x0, 2488]
	ldr	w2, [x1, 16]
	str	w2, [x0, 2460]
	ldr	w2, [x1, 32]
	str	w2, [x0, 2464]
	ldr	w0, [x22, 192]
	cmp	w0, 8
	ble	.L1843
	add	x21, x23, 311296
	ldrsw	x0, [x21, 3164]
	add	x22, x22, x0, lsl 2
	ldr	w0, [x22, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	bgt	.L1818
.L1848:
	add	x0, x1, x0, sxtw 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	bgt	.L1820
.L1849:
	add	x0, x1, x0, sxtw 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbz	w3, .L1822
.L1850:
	ldr	w0, [x19, 7812]
	cmp	w0, 1
	beq	.L1822
	ldr	w1, [x19, 2628]
.L1823:
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x22, x0
	ldr	w1, [x19, 2620]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x19, 2616]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x19, 2624]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	cmp	x22, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L1824
	cmp	x25, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L1824
	ldr	x1, [x22, 32]
	cbz	x1, .L1844
	add	x1, x20, 270336
	ldr	w2, [x22, 8]
	str	w2, [x1, 2456]
	ldr	x2, [x22, 32]
	ldr	w2, [x2, 20]
	str	w2, [x1, 2496]
	ldr	x2, [x22, 32]
	ldr	w2, [x2, 8]
	str	w2, [x1, 2440]
	ldr	x1, [x25, 32]
	cbz	x1, .L1845
.L1839:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2444]
	ldr	x1, [x24, 32]
	cbz	x1, .L1846
.L1840:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2448]
	ldr	x0, [x0, 32]
	cbz	x0, .L1847
.L1841:
	add	x1, x20, 270336
	ldr	w3, [x0, 8]
	add	x2, x20, 262144
	mov	w0, 0
	str	w3, [x1, 2452]
	ldr	w1, [x21, 3280]
	str	w1, [x21, 3276]
	str	w1, [x2, 1024]
	str	x20, [x23, 8]
.L1812:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1843:
	add	x22, x22, x0, sxtw 2
	add	x21, x23, 311296
	ldr	w0, [x22, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	ble	.L1848
.L1818:
	ldrsw	x0, [x21, 3164]
	add	x0, x1, x0, lsl 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	ble	.L1849
.L1820:
	ldrsw	x0, [x21, 3164]
	add	x0, x1, x0, lsl 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbnz	w3, .L1850
.L1822:
	ldr	w1, [x19, 2628]
	str	w1, [x19, 2616]
	str	w1, [x19, 2620]
	str	w1, [x19, 2624]
	b	.L1823
	.p2align 3
.L1842:
	add	x0, x20, 262144
	add	x26, x20, 270336
	add	x24, x23, 311296
	strb	w21, [x0, 1028]
	ldr	x0, [x23]
	ldr	w1, [x0, 632]
	str	w1, [x26, 2468]
	ldr	w0, [x0, 684]
	str	w0, [x26, 2488]
	ldr	w1, [x19, 2628]
	ldr	w0, [x24, 3272]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldrsw	x1, [x22, 5092]
	ldr	w0, [x24, 3272]
	add	x1, x22, x1, lsl 2
	ldr	w1, [x1, 196]
	bl	FSP_GetLogicFs
	mov	x27, x0
	ldrsw	x1, [x22, 5092]
	ldr	w0, [x24, 3272]
	add	x22, x22, x1, lsl 2
	ldr	w1, [x22, 196]
	bl	FSP_GetFsImagePtr
	mov	x1, x0
	cmp	x25, xzr
	ccmp	x27, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L1824
	ldr	x0, [x25, 32]
	cbz	x0, .L1851
	ldr	w0, [x0, 8]
	str	w0, [x26, 2440]
	ldr	x0, [x27, 32]
	cbz	x0, .L1852
.L1838:
	add	x20, x20, 270336
	ldr	w2, [x0, 8]
	mov	w0, 0
	str	w2, [x20, 2448]
	ldr	x2, [x25, 32]
	ldr	w2, [x2, 20]
	str	w2, [x20, 2496]
	ldr	w2, [x1, 68]
	add	w2, w2, 63
	lsr	w2, w2, 6
	str	w2, [x20, 2088]
	ldr	w2, [x1, 72]
	add	w2, w2, 63
	lsr	w2, w2, 6
	str	w2, [x20, 2092]
	str	xzr, [x23, 8]
	ldr	w2, [x1, 68]
	str	w2, [x19, 2664]
	ldr	w1, [x1, 72]
	str	w1, [x19, 2668]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1847:
	ldr	x0, [x22, 32]
	b	.L1841
	.p2align 3
.L1846:
	ldr	x1, [x22, 32]
	b	.L1840
	.p2align 3
.L1845:
	ldr	x1, [x22, 32]
	b	.L1839
	.p2align 3
.L1824:
	ldr	x1, .LC93
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1812
	.p2align 3
.L1852:
	ldr	x0, [x25, 32]
	b	.L1838
.L1844:
	ldr	x1, .LC97
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1812
.L1851:
	ldr	x1, .LC95
	mov	w0, w21
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1812
	.size	VP9_Set_DecParam, .-VP9_Set_DecParam
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_ArrangeVHBMem
	.type	VP9_ArrangeVHBMem, %function
VP9_ArrangeVHBMem:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 270336
	add	x19, x21, 2644
	bl	_mcount
	ldp	w2, w3, [x19, 20]
	cmp	w3, 31
	bls	.L1855
	mov	w1, 8160
	sub	w4, w2, #32
	mov	w0, 8192
	cmp	w4, w1
	ccmp	w3, w0, 2, ls
	bls	.L1856
.L1855:
	ldr	x1, .LC99
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1857:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1856:
	ldr	x1, .LC101
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x0, [x20]
	ldr	w1, [x0, 764]
	cbnz	w1, .L1858
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	beq	.L1884
.L1859:
	ldr	w0, [x21, 2580]
	cbnz	w0, .L1864
	add	x19, x20, 311296
	ldr	x0, .LC104
	ldr	x4, .LC105
	mov	w1, 0
	mov	x2, 20
	ldrsw	x3, [x19, 3272]
	ldr	x4, [x4, 96]
	ldr	x3, [x0, x3, lsl 3]
	add	x0, x29, 72
	add	x3, x3, 503808
	str	wzr, [x3, 1288]
	blr	x4
	strb	w22, [x29, 74]
	ldr	w4, [x21, 2664]
	mov	w2, 1
	ldr	w3, [x21, 2668]
	add	x1, x29, 72
	ldr	w0, [x19, 3272]
	strb	w2, [x29, 73]
	strb	w2, [x29, 75]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbz	w0, .L1885
.L1865:
	ldr	x1, .LC109
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1857
.L1858:
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	bne	.L1859
	ldr	w4, [x0, 724]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1883
	ldr	w5, [x0, 728]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bls	.L1863
.L1862:
	ldr	x1, .LC103
	mov	w0, 0
	ldr	w3, [x21, 2668]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1857
.L1864:
	add	x22, x20, 311296
	ldr	x23, .LC104
	ldr	x3, .LC105
	mov	w2, 1
	mov	w1, 0
	ldrsw	x0, [x22, 3272]
	ldr	x3, [x3, 96]
	ldr	w19, [x22, 3136]
	ldr	x0, [x23, x0, lsl 3]
	add	x0, x0, 503808
	str	w2, [x0, 1288]
	mov	x2, 20
	add	x0, x29, 72
	blr	x3
	strb	wzr, [x29, 74]
	ldr	x2, [x20]
	add	x1, x29, 72
	ldr	w4, [x21, 2664]
	ldr	w3, [x21, 2668]
	ldr	w0, [x2, 28]
	sxtb	w2, w19
	strb	wzr, [x29, 75]
	cmp	w0, 24
	ldr	w0, [x22, 3272]
	csinc	w2, w2, wzr, ne
	strb	w2, [x29, 73]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbnz	w0, .L1865
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x22, 3272]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbnz	w0, .L1886
.L1868:
	ldrsw	x0, [x22, 3272]
	ldr	x0, [x23, x0, lsl 3]
	str	wzr, [x0, 1536]
.L1866:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21, 2580]
	b	.L1857
.L1883:
	ldr	w5, [x0, 728]
	b	.L1862
.L1884:
	ldr	w4, [x0, 724]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1883
	ldr	w5, [x0, 728]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bhi	.L1862
	ldr	w1, [x21, 2580]
	cmp	w1, 1
	beq	.L1887
.L1863:
	ldr	w22, [x0, 772]
	b	.L1859
.L1887:
	mov	w0, 0
	b	.L1857
	.p2align 3
.L1885:
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x19, 3272]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbz	w0, .L1866
	ldr	x1, .LC107
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1857
.L1886:
	ldr	x1, .LC111
	mov	w0, 2
	bl	dprint_vfmw
	b	.L1868
	.size	VP9_ArrangeVHBMem, .-VP9_ArrangeVHBMem
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
	.xword	s_pstVfmwChan
	.align	3
.LC105:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_GetRefNum
	.type	VP9_GetRefNum, %function
VP9_GetRefNum:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 274432
	add	x19, x29, 104
	bl	_mcount
	ldr	x23, .LC112
	add	x21, x21, 270336
	mov	x2, 36
	add	x1, x21, 2724
	mov	x0, x19
	ldr	x3, [x23, 104]
	ldr	w20, [x22, 3608]
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 32
	add	x1, x21, 2796
	add	x0, x29, 72
	blr	x3
	ldr	w0, [x22, 3636]
	cmp	w0, 1
	beq	.L1905
.L1889:
	ldr	w0, [x22, 3724]
	sxtw	x6, w20
	cbz	w0, .L1896
	mov	w1, 0
	add	x5, x19, x6, lsl 2
	.p2align 2
.L1895:
	sxtw	x2, w1
	tbz	x0, 0, .L1893
	add	x3, x29, 144
	add	x3, x3, x2, lsl 2
	mov	x2, x3
	ldr	w4, [x3, -72]
	ldr	w3, [x19, w4, sxtw 2]
	cmp	w3, wzr
	sub	w3, w3, #1
	ble	.L1894
	str	w3, [x19, w4, sxtw 2]
.L1894:
	str	w20, [x2, -72]
	ldr	w2, [x5]
	add	w2, w2, 1
	str	w2, [x5]
.L1893:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1895
.L1896:
	add	x0, x29, 144
	mov	x1, 0
	add	x2, x0, x6, lsl 2
	mov	w0, 0
	ldr	w3, [x2, -40]
	sub	w3, w3, #1
	str	w3, [x2, -40]
	.p2align 2
.L1892:
	ldr	w2, [x19, x1]
	add	x1, x1, 4
	cmp	w2, wzr
	csinc	w0, w0, w0, eq
	cmp	x1, 36
	bne	.L1892
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1905:
	ldr	w0, [x19, w20, sxtw 2]
	ldr	w1, [x22, 3640]
	cmp	w0, wzr
	ble	.L1890
	sub	w0, w0, #1
	str	w0, [x19, w20, sxtw 2]
.L1890:
	ldr	w0, [x19, w1, sxtw 2]
	mov	w20, w1
	add	w0, w0, 1
	str	w0, [x19, w1, sxtw 2]
	b	.L1889
	.size	VP9_GetRefNum, .-VP9_GetRefNum
	.align	3
.LC112:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DefaultCoefProbs
	.type	Vp9_DefaultCoefProbs, %function
Vp9_DefaultCoefProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC113
	ldr	x20, .LC114
	mov	x2, 1024
	mov	x0, x19
	ldr	x3, [x21, 104]
	mov	x1, x20
	blr	x3
	mov	x2, 1024
	ldr	x3, [x21, 104]
	add	x1, x20, x2
	add	x0, x19, x2
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 2048
	mov	x2, 1024
	add	x0, x19, 2048
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 3072
	mov	x2, 1024
	add	x0, x19, 3072
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_DefaultCoefProbs, .-Vp9_DefaultCoefProbs
	.align	3
.LC113:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC114:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_InitMbmodeProbs
	.type	Vp9_InitMbmodeProbs, %function
Vp9_InitMbmodeProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 4096
	bl	_mcount
	ldr	x21, .LC115
	ldr	x20, .LC116
	mov	x2, 160
	add	x0, x19, 64
	ldr	x3, [x21, 104]
	sub	x1, x20, #256
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #96
	mov	x2, 64
	mov	x0, x19
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #32
	mov	x2, 8
	add	x0, x19, 364
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #24
	mov	x2, 96
	add	x0, x19, 516
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 72
	mov	x2, 4
	add	x0, x19, 319
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 80
	mov	x2, 5
	add	x0, x19, 323
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 88
	mov	x2, 5
	add	x0, x19, 328
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 96
	mov	x2, 10
	add	x0, x19, 333
	blr	x3
	ldr	x3, .LC117
	add	x0, x19, 307
	ldr	x4, [x21, 104]
	add	x1, x20, 112
	mov	x2, 3
	ldr	x5, [x3, 720]
	ldr	w3, [x3, 728]
	str	x5, [x0]
	str	w3, [x0, 8]
	add	x0, x19, 304
	blr	x4
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_InitMbmodeProbs, .-Vp9_InitMbmodeProbs
	.align	3
.LC115:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC116:
	.xword	.LANCHOR2
	.align	3
.LC117:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_InitMvProbs
	.type	Vp9_InitMvProbs, %function
Vp9_InitMvProbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC118
	add	x0, x19, 4096
	add	x2, x0, 433
	add	x0, x0, 372
	add	x3, x1, 793
	add	x1, x1, 732
	ldp	x6, x7, [x1, 16]
	stp	x6, x7, [x0, 16]
	ldp	x8, x9, [x1]
	ldp	x4, x5, [x1, 32]
	ldp	x6, x7, [x1, 48]
	stp	x8, x9, [x0]
	stp	x4, x5, [x0, 32]
	stp	x6, x7, [x0, 48]
	ldr	x0, [x3]
	str	x0, [x2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_InitMvProbs, .-Vp9_InitMvProbs
	.align	3
.LC118:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetupPastIndependence
	.type	Vp9_SetupPastIndependence, %function
Vp9_SetupPastIndependence:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w3
	mov	w24, w4
	mov	w23, w5
	mov	x21, x1
	mov	x22, x2
	bl	_mcount
	mov	x0, x20
	bl	Vp9_DefaultCoefProbs
	mov	x0, x20
	bl	Vp9_InitMbmodeProbs
	ldr	x1, .LC123
	add	x0, x20, 4096
	add	x6, x0, 372
	add	x4, x0, 433
	add	x7, x1, 732
	add	x1, x1, 793
	add	x0, x0, 343
	mov	x2, 21
	ldp	x8, x9, [x7]
	ldr	x5, [x1]
	ldr	x1, .LC124
	stp	x8, x9, [x6]
	ldp	x8, x9, [x7, 16]
	stp	x8, x9, [x6, 16]
	ldp	x8, x9, [x7, 32]
	stp	x8, x9, [x6, 32]
	ldr	x3, [x1, 104]
	ldp	x8, x9, [x7, 48]
	ldr	x1, .LC125
	stp	x8, x9, [x6, 48]
	add	x1, x1, 116
	str	x5, [x4]
	blr	x3
	cmp	w24, wzr
	ccmp	w19, 3, 4, eq
	ccmp	w23, wzr, 4, ne
	beq	.L1915
	cmp	w19, 2
	beq	.L1916
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1915:
	mov	x19, 0
	mov	x23, 18832
	.p2align 2
.L1911:
	add	x0, x21, x19
	mov	x2, 4708
	mov	x1, x20
	add	x19, x19, 4096
	add	x19, x19, 612
	bl	memcpy
	cmp	x19, x23
	bne	.L1911
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1916:
	ldr	w0, [x22]
	mov	w3, 4708
	mov	x1, x20
	mov	x2, 4708
	umull	x0, w0, w3
	add	x0, x21, x0
	bl	memcpy
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_SetupPastIndependence, .-Vp9_SetupPastIndependence
	.align	3
.LC123:
	.xword	.LANCHOR0
	.align	3
.LC124:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC125:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_SegfeatureActive
	.type	Vp9_Vfmw_SegfeatureActive, %function
Vp9_Vfmw_SegfeatureActive:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	ldrb	w0, [x20]
	cbz	w0, .L1919
	add	x19, x20, x19, sxtw 2
	mov	w0, 1
	lsl	w2, w0, w21
	ldr	x21, [sp, 32]
	ldr	w0, [x19, 80]
	ldp	x19, x20, [sp, 16]
	tst	w2, w0
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1919:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_SegfeatureActive, .-Vp9_Vfmw_SegfeatureActive
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_GetSegdata
	.type	Vp9_Vfmw_GetSegdata, %function
Vp9_Vfmw_GetSegdata:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w1
	mov	w19, w2
	sbfiz	x20, x20, 2, 32
	mov	x21, x0
	add	x19, x20, x19, uxtw
	mov	x0, x30
	add	x19, x19, 8
	bl	_mcount
	ldrsh	w0, [x21, x19, lsl 1]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_GetSegdata, .-Vp9_Vfmw_GetSegdata
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_Clamp
	.type	Vp9_Vfmw_Clamp, %function
Vp9_Vfmw_Clamp:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w2
	bl	_mcount
	cmp	w19, w21
	csel	w0, w19, w21, ge
	ldr	x21, [sp, 32]
	cmp	w0, w20
	csel	w0, w0, w20, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_Clamp, .-Vp9_Vfmw_Clamp
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_LoopFilterFrameInit
	.type	Vp9_Vfmw_LoopFilterFrameInit, %function
Vp9_Vfmw_LoopFilterFrameInit:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x27, x2
	mov	w26, w3
	mov	x20, x1
	bl	_mcount
	ldr	x3, .LC130
	asr	w19, w26, 5
	add	x23, x27, 80
	add	x24, x27, 18
	add	x28, x27, 112
	mov	w21, 63
	add	x25, x20, 6
	.p2align 2
.L1928:
	ldrb	w0, [x27]
	mov	w1, w26
	cbz	w0, .L1923
	ldr	w0, [x23]
	tbz	x0, 1, .L1923
	ldrsh	w1, [x24]
	ldrb	w2, [x27, 3]
	add	w0, w1, w26
	cmp	w2, 1
	csel	w1, w0, w1, ne
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 63
	csel	w1, w1, w21, le
.L1923:
	ldrb	w0, [x20]
	cbz	w0, .L1937
	ldrsb	w2, [x20, 2]
	add	x5, x20, 3
	mov	x0, x22
	lsl	w2, w2, w19
	adds	w2, w2, w1
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	strb	w2, [x22]
.L1927:
	ldrsb	w2, [x5]
	add	x0, x0, 2
	ldrsb	w4, [x20, 6]
	lsl	w2, w2, w19
	lsl	w4, w4, w19
	add	w2, w2, w1
	adds	w2, w2, w4
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	strb	w2, [x0]
	ldrsb	w2, [x5], 1
	ldrsb	w4, [x20, 7]
	lsl	w2, w2, w19
	lsl	w4, w4, w19
	add	w2, w2, w1
	adds	w2, w2, w4
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	cmp	x25, x5
	strb	w2, [x0, 1]
	bne	.L1927
	add	x23, x23, 4
	add	x22, x22, 8
	cmp	x28, x23
	add	x24, x24, 8
	bne	.L1928
.L1938:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1937:
	ldr	x4, [x3, 96]
	mov	x0, x22
	mov	x2, 8
	str	x3, [x29, 104]
	add	x23, x23, 4
	add	x22, x22, 8
	blr	x4
	add	x24, x24, 8
	cmp	x28, x23
	ldr	x3, [x29, 104]
	bne	.L1928
	b	.L1938
	.size	Vp9_Vfmw_LoopFilterFrameInit, .-Vp9_Vfmw_LoopFilterFrameInit
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_MiColsAlignedToSb
	.type	Vp9_MiColsAlignedToSb, %function
Vp9_MiColsAlignedToSb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	and	w0, w0, -8
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_MiColsAlignedToSb, .-Vp9_MiColsAlignedToSb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ToSbs
	.type	Vp9_ToSbs, %function
Vp9_ToSbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	asr	w0, w0, 3
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ToSbs, .-Vp9_ToSbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_GetTileOffsets
	.type	Vp9_GetTileOffsets, %function
Vp9_GetTileOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w19, w4
	mov	w21, w3
	mov	x22, x1
	mov	w20, w2
	bl	_mcount
	add	w0, w19, 7
	asr	w0, w0, 3
	mul	w5, w20, w0
	asr	w2, w5, w21
	add	w0, w5, w0
	asr	w3, w0, w21
	lsl	w2, w2, 3
	cmp	w2, w19
	lsl	w3, w3, 3
	csel	w2, w2, w19, le
	cmp	w3, w19
	str	w2, [x23]
	csel	w3, w3, w19, le
	str	w3, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_GetTileOffsets, .-Vp9_GetTileOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_GetTileRowOffsets
	.type	Vp9_GetTileRowOffsets, %function
Vp9_GetTileRowOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x23, x3
	mov	x22, x4
	bl	_mcount
	add	w0, w20, 7
	asr	w6, w0, 3
	mul	w0, w19, w6
	asr	w5, w0, w21
	add	w0, w6, w0
	asr	w2, w0, w21
	lsl	w5, w5, 3
	cmp	w5, w20
	lsl	w2, w2, 3
	csel	w5, w5, w20, le
	cmp	w2, w20
	str	w5, [x23]
	csel	w2, w2, w20, le
	str	w2, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_GetTileRowOffsets, .-Vp9_GetTileRowOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_GetTileColOffsets
	.type	Vp9_Vfmw_GetTileColOffsets, %function
Vp9_Vfmw_GetTileColOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x23, x3
	mov	x22, x4
	bl	_mcount
	add	w0, w20, 7
	asr	w6, w0, 3
	mul	w0, w19, w6
	asr	w5, w0, w21
	add	w0, w6, w0
	asr	w2, w0, w21
	lsl	w5, w5, 3
	cmp	w5, w20
	lsl	w2, w2, 3
	csel	w5, w5, w20, le
	cmp	w2, w20
	str	w5, [x23]
	csel	w2, w2, w20, le
	str	w2, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_Vfmw_GetTileColOffsets, .-Vp9_Vfmw_GetTileColOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetPoolInfoFrame
	.type	Vp9_SetPoolInfoFrame, %function
Vp9_SetPoolInfoFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 16
	mov	x19, x1
	add	x23, x21, 270336
	bl	_mcount
	ldr	w0, [x23, 2480]
	bl	GetCompressRatio
	mov	w22, w0
	ldr	w0, [x23, 2484]
	bl	GetCompressRatio
	add	x1, x20, 270336
	add	x9, x20, 311296
	mov	w6, 1048576
	ldr	w2, [x1, 2876]
	ldr	w4, [x1, 2880]
	ubfiz	w2, w2, 10, 3
	ldr	w5, [x1, 7708]
	ubfiz	w4, w4, 13, 2
	ldr	w3, [x1, 7812]
	orr	w4, w4, w2
	ldr	w2, [x1, 7712]
	ubfiz	w5, w5, 1, 2
	ubfiz	w3, w3, 7, 1
	and	w2, w2, 1
	orr	w2, w5, w2
	orr	w5, w4, w2
	ldr	w4, [x1, 7772]
	ldr	w2, [x1, 7788]
	ubfiz	w4, w4, 15, 4
	ubfiz	w2, w2, 9, 1
	orr	w2, w4, w2
	orr	w4, w5, w2
	ldr	w5, [x1, 7784]
	ubfiz	w5, w5, 8, 1
	orr	w2, w5, w3
	ldr	w3, [x1, 7748]
	orr	w5, w4, w2
	ldr	w2, [x1, 7752]
	ubfiz	w3, w3, 5, 1
	ubfiz	w2, w2, 6, 1
	orr	w2, w2, w3
	ldr	w3, [x1, 7740]
	orr	w4, w5, w2
	ldr	w2, [x1, 7744]
	ubfiz	w3, w3, 3, 1
	ubfiz	w2, w2, 4, 1
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19]
	ldr	w3, [x1, 7756]
	ldr	w2, [x9, 3156]
	cmp	w3, w2
	beq	.L1981
.L1945:
	add	x5, x1, 2644
	ldr	w2, [x5, 76]
	ldr	w3, [x5, 184]
	mov	w10, 0
	ldr	w0, [x5, 5180]
	ubfiz	w2, w2, 7, 1
	ubfiz	w3, w3, 8, 4
	and	w0, w0, 7
	orr	w3, w3, w2
	orr	w6, w0, w6
	ldp	w2, w0, [x5, 188]
	ubfiz	w0, w0, 16, 4
	ubfiz	w2, w2, 12, 4
	orr	w2, w0, w2
	orr	w0, w3, w2
	ldp	w2, w3, [x5, 68]
	ubfiz	w3, w3, 6, 1
	ubfiz	w2, w2, 5, 1
	orr	w2, w3, w2
	orr	w3, w0, w2
	ldr	w2, [x5, 56]
	ldr	w0, [x5, 64]
	ubfiz	w2, w2, 3, 1
	ubfiz	w0, w0, 4, 1
	orr	w2, w0, w2
	orr	w0, w3, w2
	orr	w0, w0, w6
	str	w0, [x19, 4]
	ldr	w0, [x5, 5116]
	ldr	w3, [x5, 5112]
	add	w0, w0, 7
	asr	w0, w0, 3
	add	w3, w3, 7
	sub	w2, w0, #1
	asr	w3, w3, 3
	sub	w0, w3, #1
	orr	w0, w0, w2, lsl 16
	str	w0, [x19, 8]
	ldr	w2, [x5, 344]
	ldr	w0, [x5, 348]
	ubfiz	w2, w2, 8, 6
	and	w0, w0, 7
	orr	w0, w2, w0
	str	w0, [x19, 12]
	.p2align 2
.L1946:
	lsl	w4, w10, 1
	mov	w6, 0
	sbfiz	x11, x10, 2, 32
	add	x4, x19, x4, sxtw 2
.L1947:
	lsl	w0, w6, 1
	add	x4, x4, 4
	add	w2, w0, 1
	add	w6, w6, 1
	add	x0, x11, x0, sxtw
	cmp	w6, 2
	add	x2, x11, x2, sxtw
	add	x7, x5, x0, lsl 1
	add	x8, x5, x2, lsl 1
	mov	x0, x7
	mov	x3, x8
	ldrb	w7, [x7, 257]
	ldrb	w2, [x0, 256]
	ldrb	w8, [x8, 257]
	ubfiz	w0, w7, 8, 6
	ldrb	w3, [x3, 256]
	and	w2, w2, 63
	ubfiz	w7, w8, 24, 6
	orr	w0, w0, w2
	ubfiz	w3, w3, 16, 6
	orr	w3, w7, w3
	orr	w0, w3, w0
	str	w0, [x4, 12]
	bne	.L1947
	add	w10, w10, 1
	cmp	w10, 8
	bne	.L1946
	ldr	w4, [x5, 252]
	mov	w3, 268435456
	ldr	w5, [x1, 2892]
	add	x0, x1, 2644
	cmp	w4, wzr
	add	x0, x0, 4096
	sxtw	x6, w4
	csel	w7, wzr, w3, ge
	cmp	w5, wzr
	mov	w3, 1048576
	eor	x4, x6, x6, asr 63
	csel	w3, wzr, w3, ge
	sub	x4, x4, x6, asr 63
	sxtw	x6, w5
	ubfiz	w5, w4, 24, 4
	orr	w3, w7, w3
	eor	x2, x6, x6, asr 63
	sub	x2, x2, x6, asr 63
	ldrb	w6, [x1, 2884]
	ubfiz	w2, w2, 16, 4
	orr	w4, w2, w5
	ldr	w5, [x1, 2888]
	cmp	w5, wzr
	sxtw	x5, w5
	eor	x2, x5, x5, asr 63
	sub	x2, x2, x5, asr 63
	ubfiz	w2, w2, 8, 4
	orr	w2, w2, w6
	orr	w2, w2, w4
	orr	w2, w2, w3
	mov	w3, 4096
	csel	w3, wzr, w3, ge
	orr	w2, w2, w3
	str	w2, [x19, 80]
	ldrb	w5, [x0, 1089]
	ldrb	w4, [x0, 1092]
	ldrb	w3, [x0, 1091]
	ldrb	w2, [x0, 1088]
	ubfiz	w0, w4, 3, 1
	ubfiz	w3, w3, 2, 1
	ubfiz	w4, w5, 1, 1
	and	w2, w2, 1
	orr	w0, w0, w3
	orr	w2, w4, w2
	add	x5, x20, 274432
	orr	w0, w0, w2
	add	x4, x5, 3812
	mov	w2, 0
	mov	w3, 0
	str	w0, [x19, 84]
	.p2align 2
.L1952:
	ldr	w0, [x4], 4
	and	w0, w0, 15
	lsl	w0, w0, w2
	add	w2, w2, 4
	cmp	w2, 32
	orr	w3, w3, w0
	bne	.L1952
	str	w3, [x19, 88]
	ldrh	w3, [x1, 7860]
	ldrh	w2, [x1, 7852]
	ubfiz	w3, w3, 18, 9
	ubfiz	w2, w2, 9, 9
	orr	w3, w3, w2
	ldrh	w2, [x1, 7844]
	and	w2, w2, 511
	orr	w2, w2, w3
	str	w2, [x19, 92]
	ldrh	w3, [x1, 7884]
	ldrh	w2, [x1, 7876]
	ubfiz	w3, w3, 18, 9
	ubfiz	w2, w2, 9, 9
	orr	w3, w3, w2
	ldrh	w2, [x1, 7868]
	and	w2, w2, 511
	orr	w2, w2, w3
	str	w2, [x19, 96]
	mov	w3, 0
	ldrh	w2, [x1, 7900]
	ldrh	w0, [x1, 7892]
	ubfiz	w2, w2, 9, 9
	and	w0, w0, 511
	orr	w2, w2, w0
	mov	x0, 0
	str	w2, [x19, 100]
.L1953:
	add	x2, x0, 274432
	add	x2, x2, 3750
	ldrb	w2, [x20, x2]
	lsl	w2, w2, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w3, w3, w2
	bne	.L1953
	str	w3, [x19, 104]
	mov	x0, 0
	mov	w3, 0
.L1954:
	add	x2, x0, 274432
	add	x2, x2, 3782
	ldrb	w2, [x20, x2]
	lsl	w2, w2, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w3, w3, w2
	bne	.L1954
	add	x5, x5, 3752
	mov	w4, 0
	mov	w6, 0
	str	w3, [x19, 108]
	.p2align 2
.L1955:
	ldrh	w3, [x5]
	lsl	w7, w4, 1
	ldrh	w2, [x5, 2]
	add	w0, w4, 16
	and	w3, w3, 3
	add	w4, w4, 1
	and	w2, w2, 1
	lsl	w3, w3, w7
	lsl	w0, w2, w0
	cmp	w4, 8
	orr	w0, w3, w0
	add	x5, x5, 8
	orr	w6, w6, w0
	bne	.L1955
	str	w6, [x19, 112]
	add	x0, x1, 2644
	ldr	w3, [x1, 2592]
	str	w3, [x19, 116]
	ldr	w2, [x1, 2608]
	str	w2, [x19, 120]
	ldr	w2, [x0, 36]
	str	w2, [x19, 128]
	ldr	w2, [x0, 40]
	str	w2, [x19, 132]
	ldr	w2, [x0, 44]
	str	w2, [x19, 136]
	ldr	w2, [x0, 48]
	str	w2, [x19, 140]
	ldr	w2, [x0, 5440]
	ldrh	w3, [x0, 5444]
	orr	w2, w3, w2, lsl 16
	str	w2, [x19, 180]
	ldr	w2, [x0, 5456]
	ldrh	w3, [x0, 5460]
	orr	w2, w3, w2, lsl 16
	str	w2, [x19, 184]
	ldr	w2, [x0, 5472]
	ldrh	w3, [x0, 5476]
	orr	w2, w3, w2, lsl 16
	str	w2, [x19, 188]
	ldr	w3, [x0, 5468]
	ldr	w4, [x0, 5484]
	ldr	w2, [x0, 5452]
	ubfiz	w3, w3, 8, 6
	ubfiz	w4, w4, 16, 6
	orr	w3, w4, w3
	and	w2, w2, 63
	orr	w2, w2, w3
	str	w2, [x19, 192]
	ldr	w3, [x0, 5464]
	ldr	w4, [x0, 5480]
	ldr	w2, [x0, 5448]
	ubfiz	w3, w3, 8, 6
	ubfiz	w4, w4, 16, 6
	orr	w3, w4, w3
	and	w2, w2, 63
	orr	w2, w2, w3
	str	w2, [x19, 196]
	ldr	w0, [x0, 184]
	cmp	w0, 8
	bls	.L1956
	str	wzr, [x19, 200]
.L1957:
	ldr	w0, [x1, 2832]
	cmp	w0, 8
	bls	.L1958
	str	wzr, [x19, 204]
.L1959:
	ldr	w0, [x1, 2836]
	cmp	w0, 8
	bls	.L1960
	str	wzr, [x19, 208]
.L1961:
	ldr	w0, [x9, 3160]
	ldrh	w2, [x9, 3156]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 212]
	ldr	w0, [x1, 2828]
	cmp	w0, 8
	bls	.L1962
	stp	wzr, wzr, [x19, 216]
	str	wzr, [x19, 224]
.L1963:
	ldr	w0, [x1, 2832]
	cmp	w0, 8
	bls	.L1965
	stp	wzr, wzr, [x19, 228]
	str	wzr, [x19, 236]
	ldr	w0, [x1, 2836]
	cmp	w0, 8
	bhi	.L1982
.L1968:
	add	x0, x20, x0, sxtw 4
	add	x21, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 3852]
	add	w1, w1, 255
	and	w1, w1, -256
	lsl	w1, w1, 4
	mul	w1, w1, w22
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	asr	w1, w1, 3
	str	w1, [x19, 240]
	ldr	w3, [x0, 3852]
	ldr	w4, [x0, 3856]
	add	w1, w3, 255
	ldr	w7, [x21, 2468]
	and	w1, w1, -256
	add	w5, w4, 63
	and	w6, w5, -64
	mul	w1, w1, w22
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	cmp	w7, 1
	asr	w1, w1, 3
	mul	w1, w1, w6
	beq	.L1983
.L1970:
	str	w1, [x19, 244]
	ldr	w1, [x0, 3852]
	ldr	w3, [x0, 3856]
	adds	w0, w1, 2047
	add	w1, w1, 4094
	csel	w0, w1, w0, mi
	add	w2, w3, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w1, w0, 127
	csel	w0, w1, w0, lt
	adds	w1, w3, 63
	csel	w1, w2, w1, mi
	asr	w0, w0, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	mul	w0, w0, w1
	str	w0, [x19, 248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1965:
	add	x0, x20, x0, sxtw 4
	add	x6, x21, 270336
	add	x3, x0, 274432
	ldr	w0, [x3, 3852]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 228]
	ldr	w4, [x3, 3852]
	ldr	w5, [x3, 3856]
	add	w0, w4, 255
	and	w0, w0, -256
	add	w7, w5, 63
	mul	w2, w0, w22
	cmp	w2, wzr
	add	w0, w2, 7
	csel	w0, w0, w2, lt
	ldr	w2, [x6, 2468]
	asr	w0, w0, 3
	cmp	w2, 1
	and	w2, w7, -64
	mul	w0, w0, w2
	beq	.L1984
.L1967:
	str	w0, [x19, 232]
	ldr	w0, [x3, 3852]
	ldr	w4, [x3, 3856]
	adds	w2, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w2, mi
	add	w3, w4, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w2, w0, 127
	csel	w0, w2, w0, lt
	adds	w2, w4, 63
	csel	w2, w3, w2, mi
	asr	w0, w0, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	mul	w0, w0, w2
	str	w0, [x19, 236]
	ldr	w0, [x1, 2836]
	cmp	w0, 8
	bls	.L1968
.L1982:
	stp	wzr, wzr, [x19, 240]
	str	wzr, [x19, 248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1962:
	add	x0, x20, x0, sxtw 4
	add	x6, x21, 270336
	add	x3, x0, 274432
	ldr	w0, [x3, 3852]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 216]
	ldr	w4, [x3, 3852]
	ldr	w5, [x3, 3856]
	add	w0, w4, 255
	and	w0, w0, -256
	add	w7, w5, 63
	mul	w2, w0, w22
	cmp	w2, wzr
	add	w0, w2, 7
	csel	w0, w0, w2, lt
	ldr	w2, [x6, 2468]
	asr	w0, w0, 3
	cmp	w2, 1
	and	w2, w7, -64
	mul	w0, w0, w2
	beq	.L1985
.L1964:
	str	w0, [x19, 220]
	ldr	w0, [x3, 3852]
	ldr	w4, [x3, 3856]
	adds	w2, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w2, mi
	add	w3, w4, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w2, w0, 127
	csel	w0, w2, w0, lt
	adds	w2, w4, 63
	csel	w2, w3, w2, mi
	asr	w0, w0, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	mul	w0, w0, w2
	str	w0, [x19, 224]
	b	.L1963
	.p2align 3
.L1960:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 3852]
	str	w2, [x3, 2528]
	and	w2, w2, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x3, 2540]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 208]
	b	.L1961
	.p2align 3
.L1958:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 3852]
	str	w2, [x3, 2524]
	and	w2, w2, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x3, 2536]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 204]
	b	.L1959
	.p2align 3
.L1956:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 3852]
	str	w2, [x3, 2520]
	and	w2, w2, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x3, 2532]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 200]
	b	.L1957
	.p2align 3
.L1981:
	ldr	w2, [x1, 7760]
	ldr	w0, [x9, 3160]
	cmp	w2, w0
	csel	w6, w6, wzr, ne
	b	.L1945
	.p2align 3
.L1983:
	ldr	w2, [x21, 2472]
	cbnz	w2, .L1970
	adds	w2, w3, 2047
	add	w3, w3, 4094
	csel	w2, w3, w2, mi
	add	w4, w4, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w3, w2, 127
	csel	w3, w3, w2, lt
	cmp	w5, wzr
	csel	w2, w4, w5, lt
	asr	w3, w3, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	madd	w1, w3, w2, w1
	b	.L1970
.L1984:
	ldr	w2, [x6, 2472]
	cbnz	w2, .L1967
	adds	w2, w4, 2047
	add	w4, w4, 4094
	csel	w2, w4, w2, mi
	add	w5, w5, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w4, w2, 127
	csel	w4, w4, w2, lt
	cmp	w7, wzr
	csel	w2, w5, w7, lt
	asr	w4, w4, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	madd	w0, w4, w2, w0
	b	.L1967
.L1985:
	ldr	w2, [x6, 2472]
	cbnz	w2, .L1964
	adds	w2, w4, 2047
	add	w4, w4, 4094
	csel	w2, w4, w2, mi
	add	w5, w5, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w4, w2, 127
	csel	w4, w4, w2, lt
	cmp	w7, wzr
	csel	w2, w5, w7, lt
	asr	w4, w4, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	madd	w0, w4, w2, w0
	b	.L1964
	.size	Vp9_SetPoolInfoFrame, .-Vp9_SetPoolInfoFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetPoolInfoTile
	.type	Vp9_SetPoolInfoTile, %function
Vp9_SetPoolInfoTile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x3
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19]
	str	w0, [x20]
	ldrb	w0, [x19, 4]
	and	w0, w0, 127
	str	w0, [x20, 4]
	ldr	w0, [x19, 8]
	add	w0, w0, 128
	str	w0, [x20, 8]
	ldr	w0, [x19, 12]
	str	w0, [x20, 12]
	ldrb	w0, [x19, 16]
	and	w0, w0, 127
	str	w0, [x20, 16]
	ldr	w0, [x19, 20]
	str	w0, [x20, 20]
	ldrh	w2, [x19, 24]
	ldrh	w0, [x19, 26]
	add	w1, w2, 7
	cmp	w2, w0
	ubfx	x1, x1, 3, 7
	lsl	w1, w1, 16
	beq	.L1987
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w0, w0, w1
.L1988:
	str	w0, [x20, 24]
	ldrh	w2, [x19, 28]
	ldrh	w0, [x19, 30]
	add	w1, w2, 7
	cmp	w2, w0
	ubfx	x1, x1, 3, 7
	lsl	w1, w1, 16
	orr	w2, w1, 255
	beq	.L1990
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w2, w0, w1
.L1990:
	str	w2, [x20, 28]
	ldr	w0, [x19, 32]
	and	w0, w0, 131071
	str	w0, [x20, 32]
	ldr	w0, [x19, 36]
	and	w0, w0, 131071
	str	w0, [x20, 36]
	ldr	w0, [x19, 40]
	and	w0, w0, 131071
	str	w0, [x20, 40]
	ldr	w0, [x19, 44]
	str	wzr, [x20, 252]
	and	w0, w0, 131071
	str	w0, [x20, 44]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1987:
	orr	w0, w1, 255
	b	.L1988
	.size	Vp9_SetPoolInfoTile, .-Vp9_SetPoolInfoTile
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DecodeTilesCtrl
	.type	Vp9_DecodeTilesCtrl, %function
Vp9_DecodeTilesCtrl:
	stp	x29, x30, [sp, -288]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 270336
	mov	x26, x1
	str	x20, [x29, 136]
	bl	_mcount
	mov	w1, 1
	ldr	w2, [x19, 7804]
	ldr	w0, [x19, 7800]
	ldr	w3, [x19, 7808]
	str	w0, [x29, 120]
	add	x0, x20, 311296
	str	w3, [x29, 112]
	lsl	w3, w1, w3
	str	w2, [x29, 180]
	lsl	w1, w1, w2
	mov	x2, x20
	mov	x20, x0
	str	w1, [x29, 212]
	mov	x0, x2
	add	x1, x2, 16
	ldrsw	x22, [x26, 24]
	ldr	x27, [x26]
	mov	w21, w3
	ldr	w28, [x19, 7796]
	str	w3, [x29, 116]
	add	x22, x27, x22
	str	x20, [x29, 128]
	bl	Vp9_SetPoolInfoFrame
	str	wzr, [x20, 3280]
	cmp	w21, wzr
	ldr	w0, [x19, 2568]
	ldr	x1, [x19, 2560]
	and	w0, w0, 15
	str	x1, [x29, 160]
	str	w0, [x29, 168]
	ble	.L2002
	ldr	w1, [x29, 120]
	add	w0, w28, 7
	mov	w21, 0
	str	wzr, [x29, 124]
	add	w1, w1, 7
	str	wzr, [x29, 144]
	asr	w2, w1, 3
	asr	w1, w0, 3
	ldr	w0, [x29, 212]
	stp	w1, w2, [x29, 104]
	sub	w0, w0, #1
	str	wzr, [x29, 156]
	stp	w0, w1, [x29, 172]
	ldr	w0, [x29, 116]
	sub	w0, w0, #1
	str	w0, [x29, 148]
.L2001:
	ldr	w1, [x29, 108]
	ldr	w0, [x29, 144]
	ldrb	w4, [x29, 112]
	add	w0, w0, w1
	asr	w3, w0, w4
	mov	w2, w0
	ldr	w0, [x29, 124]
	lsl	w25, w3, 3
	str	w2, [x29, 144]
	lsl	w24, w0, 3
	ldr	w0, [x29, 120]
	ldr	w2, [x29, 212]
	cmp	w24, w0
	str	w3, [x29, 124]
	csel	w1, w24, w0, le
	cmp	w25, w0
	csel	w0, w25, w0, le
	cmp	w2, wzr
	stp	w0, w1, [x29, 200]
	mov	w2, w0
	sub	w0, w0, w1
	add	w0, w0, 7
	asr	w3, w0, 3
	str	w3, [x29, 208]
	ble	.L1994
	add	w23, w2, 7
	ldr	w2, [x29, 104]
	asr	w23, w23, 3
	mov	w20, 0
	sub	w23, w23, #1
	mov	w19, 0
	mov	x24, x27
	mul	w0, w23, w2
	str	w0, [x29, 196]
	add	w0, w1, 7
	asr	w0, w0, 3
	mov	w23, 0
	mov	w25, w23
	mov	w23, w28
	mul	w0, w0, w2
	str	w0, [x29, 192]
	ldr	x0, [x29, 136]
	ldr	w2, [x26, 24]
	add	x0, x0, 278528
	str	x0, [x29, 184]
	b	.L2000
	.p2align 3
.L2013:
	ldr	w2, [x29, 148]
	ldr	w3, [x29, 156]
	cmp	w2, w3
	bgt	.L1995
.L1997:
	ldr	x2, [x29, 160]
	sub	w1, w27, w28
	ldrh	w3, [x29, 204]
	add	w1, w1, 7
	sub	x0, x0, x2
	strh	w3, [x29, 256]
	ldr	w2, [x29, 168]
	asr	w1, w1, 3
	ldr	w3, [x29, 208]
	add	w5, w28, 7
	add	w0, w2, w0
	ldr	w6, [x29, 196]
	and	w2, w0, 15
	and	w0, w0, -16
	mul	w1, w1, w3
	ldrh	w3, [x29, 200]
	ubfiz	w2, w2, 3, 5
	strh	w3, [x29, 258]
	add	w3, w27, 7
	str	w0, [x29, 232]
	add	w10, w1, w21
	ldr	w0, [x29, 192]
	add	w3, w6, w3, asr 3
	sub	w3, w3, #1
	add	x6, x29, 288
	add	w5, w0, w5, asr 3
	sub	w0, w10, #1
	str	w21, [x29, 276]
	add	x24, x24, x4, sxtw
	str	w0, [x29, 268]
	lsl	w0, w4, 3
	strh	w28, [x29, 260]
	mov	w21, w10
	strh	w27, [x29, 262]
	strb	wzr, [x29, 248]
	strb	w2, [x29, 236]
	str	wzr, [x29, 244]
	str	wzr, [x29, 252]
	str	w3, [x29, 264]
	str	x6, [x29, 280]
	str	w5, [x29, 272]
	str	w0, [x29, 240]
	cbnz	w1, .L2010
	ldr	x0, [x29, 184]
	ldr	w5, [x0, 576]
	cmp	w4, w5
	bgt	.L2011
.L1999:
	ldr	w2, [x26, 24]
	ldr	w0, [x29, 212]
	sub	w2, w2, w4
	str	w2, [x26, 24]
	cmp	w0, w25
	beq	.L2012
.L2000:
	ldr	w0, [x29, 176]
	lsl	w5, w19, 3
	cmp	w5, w23
	add	x10, x24, 4
	add	w20, w20, w0
	ldrb	w0, [x29, 180]
	csel	w28, w5, w23, le
	mov	x1, x24
	asr	w19, w20, w0
	mov	x0, x26
	lsl	w3, w19, 3
	str	x10, [x29, 216]
	cmp	w3, w23
	csel	w27, w3, w23, le
	bl	BsInit
	ldr	w0, [x29, 172]
	sub	w4, w22, w24
	mov	w1, 32
	ldr	x10, [x29, 216]
	cmp	w25, w0
	add	w25, w25, 1
	mov	x0, x24
	bge	.L2013
.L1995:
	cmp	x24, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2004
	cmp	x22, x10
	ccmp	x10, x24, 0, cs
	mov	x24, x10
	bls	.L2004
	mov	x0, x26
	bl	BsGet
	mov	w4, w0
	mov	x0, x24
	b	.L1997
	.p2align 3
.L2010:
	ldr	x27, [x29, 128]
	add	x3, x29, 232
	str	w4, [x29, 152]
	ldr	x4, [x29, 136]
	ldr	w2, [x27, 3280]
	mov	x0, x4
	str	w10, [x29, 216]
	ubfiz	x1, x2, 8, 32
	add	x1, x1, 1040
	add	x1, x4, x1
	bl	Vp9_SetPoolInfoTile
	ldr	w0, [x27, 3280]
	ldr	w4, [x29, 152]
	add	w0, w0, 1
	str	w0, [x27, 3280]
	ldr	x0, [x29, 184]
	ldr	w10, [x29, 216]
	ldr	w5, [x0, 576]
	cmp	w4, w5
	ble	.L1999
.L2011:
	ldr	x2, .LC131
	mov	w3, 4530
	ldr	x1, .LC133
	mov	w0, 0
	add	x2, x2, 808
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L2004:
	mov	w0, -1
.L1993:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L2012:
	mov	w28, w23
	mov	x27, x24
	mov	w21, w10
.L1994:
	ldr	w0, [x29, 156]
	ldr	w1, [x29, 116]
	add	w0, w0, 1
	str	w0, [x29, 156]
	cmp	w0, w1
	bne	.L2001
.L2002:
	mov	w0, 0
	b	.L1993
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
	.align	3
.LC131:
	.xword	.LANCHOR0
	.align	3
.LC133:
	.xword	.LC132
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
	sub	sp, sp, #192
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	mov	x19, x0
	mov	x0, x30
	add	x23, x19, 270336
	add	x21, x19, 311296
	mov	x26, x1
	mov	w24, w2
	bl	_mcount
	str	wzr, [x29, 124]
	ldr	w22, [x23, 7712]
	mov	w2, w24
	ldr	w0, [x23, 7792]
	mov	x1, x26
	ldr	w3, [x23, 7816]
	cmp	w22, wzr
	ldr	w28, [x23, 2696]
	add	x20, x19, 278528
	ldr	w27, [x23, 2704]
	add	x25, x20, 592
	str	w22, [x21, 3248]
	stp	w0, w3, [x29, 104]
	stp	w0, wzr, [x29, 116]
	cset	w0, eq
	str	w0, [x21, 3236]
	ldr	w0, [x23, 7744]
	str	w0, [x21, 3256]
	add	x0, x29, 128
	ldr	w5, [x23, 7812]
	str	w5, [x21, 3240]
	ldr	w5, [x23, 7788]
	str	w5, [x21, 3260]
	ldr	w5, [x23, 2700]
	str	w5, [x21, 3264]
	ldr	w5, [x23, 7824]
	str	w5, [x21, 3268]
	ldr	w4, [x23, 7708]
	str	w4, [x21, 3252]
	bl	BsInit
	ldr	w0, [x21, 3236]
	ldr	w4, [x21, 3256]
	ldr	w3, [x29, 108]
	cbnz	w0, .L2016
	cbz	w4, .L2031
.L2016:
	add	x1, x19, 282624
	add	x2, x29, 116
	add	x1, x1, 1204
	mov	x0, x25
	mov	w5, w22
	bl	Vp9_SetupPastIndependence
	ldr	x0, .LC134
	mov	x2, 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x23, 2708
	blr	x3
.L2017:
	ldr	w1, [x29, 116]
	mov	x2, 4708
	add	x0, x20, 592
	madd	x1, x1, x2, x19
	add	x1, x1, 282624
	add	x1, x1, 1204
	bl	memcpy
	add	x0, x29, 128
	bl	Vp9_Cabac_ReaderInit
	add	x0, x29, 124
	ldr	w3, [x21, 3240]
	ldr	w5, [x21, 3264]
	mov	w7, w28
	ldr	w4, [x21, 3268]
	mov	w6, w27
	str	x0, [sp, 8]
	add	x0, x29, 120
	mov	w2, w22
	str	x0, [sp]
	mov	x1, x25
	add	x0, x29, 128
	bl	Vp9_ReadCompressedHeader
	cbnz	w0, .L2032
	ldr	w0, [x29, 124]
	add	x2, x23, 2644
	str	w0, [x23, 2876]
	str	w0, [x21, 3244]
	ldr	w0, [x29, 120]
	ldr	w3, [x23, 2988]
	str	w0, [x23, 2880]
	cbnz	w3, .L2033
.L2020:
	ldr	w0, [x21, 3240]
	cbnz	w0, .L2034
	uxtw	x1, w22
	ldr	x27, .LC134
	lsl	x0, x1, 2
	mov	x2, 48
	sub	x1, x0, x1
	add	x0, x20, 592
	ldr	x3, [x27, 104]
	add	x1, x0, x1, lsl 4
	add	x0, x0, 4096
	add	x1, x1, 4096
	add	x0, x0, 256
	add	x1, x1, 516
	blr	x3
.L2022:
	add	x20, x20, 592
	add	x28, x23, 2644
	add	x20, x20, 4096
	add	x28, x28, 4096
	ldr	x3, [x27, 104]
	mov	x2, 7
	add	x1, x28, 1093
	add	x0, x20, 448
	blr	x3
	ldr	x3, [x27, 104]
	add	x1, x28, 1100
	mov	x2, 3
	add	x0, x20, 456
	blr	x3
	add	x0, x19, 262144
	ldr	x3, [x27, 104]
	mov	x1, x25
	add	x0, x0, 1045
	mov	x2, 4608
	blr	x3
	ldr	w0, [x21, 3240]
	cbz	w0, .L2023
	ldr	w21, [x29, 104]
	mov	x0, 4708
	ldr	x3, [x27, 104]
	mov	x2, 48
	mul	x0, x21, x0
	add	x0, x0, 286720
	add	x1, x19, x0
	mov	x0, x1
	add	x1, x1, 1720
	add	x0, x0, 1460
	blr	x3
.L2024:
	mov	x1, 4708
	ldr	x3, [x27, 104]
	add	x0, x19, 266240
	mov	x2, 4608
	madd	x21, x21, x1, x19
	add	x0, x0, 1557
	add	x1, x21, 282624
	add	x1, x1, 1204
	blr	x3
	ldr	w2, [x23, 2652]
	add	x1, x29, 128
	mov	x0, x19
	sub	w24, w24, w2
	str	w24, [x29, 152]
	add	x26, x26, x2, uxtw
	str	x26, [x29, 128]
	bl	Vp9_DecodeTilesCtrl
	mov	w0, 0
.L2019:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L2034:
	ldr	x27, .LC134
	add	x0, x20, 592
	add	x0, x0, 4096
	mov	x2, 48
	add	x1, x0, 516
	add	x0, x0, 256
	ldr	x3, [x27, 104]
	blr	x3
	b	.L2022
	.p2align 3
.L2031:
	ldr	w0, [x21, 3240]
	cbz	w0, .L2017
	b	.L2016
	.p2align 3
.L2023:
	ldr	w21, [x29, 104]
	uxtw	x22, w22
	mov	x0, 4708
	lsl	x1, x22, 2
	sub	x1, x1, x22
	ldr	x3, [x27, 104]
	mul	x0, x21, x0
	mov	x2, 48
	add	x1, x0, x1, lsl 4
	add	x0, x0, 286720
	add	x1, x1, 286720
	add	x0, x19, x0
	add	x1, x19, x1
	add	x0, x0, 1460
	add	x1, x1, 1720
	blr	x3
	b	.L2024
	.p2align 3
.L2033:
	add	x2, x2, 4096
	add	x1, x23, 2980
	add	x2, x2, 1088
	add	x0, x23, 2900
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2020
	.p2align 3
.L2032:
	ldr	x1, .LC136
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2019
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
	.align	3
.LC134:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC136:
	.xword	.LC135
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 311296
	mov	x25, x1
	bl	_mcount
	add	x23, x20, 278528
	add	x26, x20, 270336
	add	x22, x23, 552
	ldr	w0, [x19, 3168]
	add	x24, x26, 2644
	add	x21, x20, 274432
	cbz	w0, .L2036
	ldr	w0, [x21, 3608]
	tbnz	w0, #31, .L2036
.L2037:
	str	w0, [x19, 3164]
	mov	x1, x24
	mov	x0, x22
	bl	Read_UnCompressed_Header
	cbnz	w0, .L2109
	ldr	x0, [x20]
	ldr	w1, [x26, 7772]
	str	w1, [x0, 940]
	ldr	w2, [x26, 7772]
	cmp	w2, 10
	bgt	.L2112
.L2044:
	ldr	w0, [x21, 3636]
	cbnz	w0, .L2046
	ldr	w2, [x26, 2572]
	cmp	w2, 7
	ble	.L2113
.L2046:
	add	x27, x26, 2644
	ldr	w0, [x27, 5112]
	sub	w1, w0, #128
	cmp	w1, 3968
	bls	.L2114
.L2047:
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L2109
	ldr	w0, [x19, 3272]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2107:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2036:
	ldr	w2, [x26, 2724]
	add	x1, x26, 2728
	mov	w0, 1
	cbz	w2, .L2115
	.p2align 2
.L2094:
	ldr	w2, [x1]
	add	x1, x1, 4
	cbz	w2, .L2038
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L2094
	mov	w0, -1
	str	w0, [x21, 3608]
.L2077:
	ldr	x1, .LC138
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2107
	.p2align 3
.L2114:
	ldr	w1, [x27, 5116]
	sub	w2, w1, #128
	cmp	w2, 3968
	bhi	.L2047
	adds	w2, w0, 63
	stp	w0, w1, [x27, 20]
	add	w0, w0, 126
	csel	w0, w0, w2, mi
	asr	w0, w0, 6
	str	w0, [x27, 12]
	adds	w0, w1, 63
	add	w1, w1, 126
	csel	w0, w1, w0, mi
	asr	w0, w0, 6
	str	w0, [x27, 16]
	mov	x0, x20
	bl	VP9_GetRefNum
	str	w0, [x19, 3140]
	ldr	w0, [x19, 3272]
	ldp	w1, w2, [x27, 20]
	bl	VCTRL_GetFsSize
	mov	w1, w0
	str	w0, [x19, 3128]
	ldr	w0, [x19, 3272]
	bl	FSP_GetPhyFsNum
	str	w0, [x19, 3132]
	ldr	x1, .LC144
	ldr	w0, [x19, 3272]
	ldr	x2, [x1, w0, sxtw 3]
	ldr	w1, [x2, 1496]
	str	w1, [x19, 3136]
	ldr	w4, [x27, 20]
	cmp	w4, 1920
	bhi	.L2050
	ldr	w3, [x27, 24]
	cmp	w3, 1088
	bhi	.L2050
	ldr	w3, [x2, 36]
	cmp	w3, 24
	beq	.L2050
	add	x2, x2, 507904
	ldr	w2, [x2, 1396]
	cmp	w2, wzr
	add	w2, w1, 4
	csel	w1, w2, w1, eq
	.p2align 2
.L2050:
	ldr	w3, [x19, 3140]
	ldr	w2, [x19, 3144]
	cmp	w2, w3
	csel	w2, w2, w3, ge
	add	w1, w2, w1
	str	w1, [x19, 3136]
	ldr	w1, [x19, 3148]
	cmp	w4, w1
	beq	.L2116
.L2051:
	str	w3, [x19, 3144]
.L2053:
	mov	w1, 0
	bl	FSP_GetPhyFsNum
	mov	w28, w0
	ldr	w0, [x19, 3132]
	cmp	w28, w0
	ble	.L2054
	sub	w1, w28, w0
	cmp	w1, wzr
	ble	.L2054
	mov	w27, 0
	b	.L2056
	.p2align 3
.L2055:
	ldr	w0, [x19, 3132]
	sub	w1, w28, w0
	cmp	w1, w27
	ble	.L2054
.L2056:
	ldr	w1, [x19, 3128]
	add	w27, w27, 1
	ldr	w0, [x19, 3272]
	bl	FSP_RelsePhyFs
	cbz	w0, .L2055
	ldr	w0, [x19, 3132]
.L2054:
	ldr	w1, [x19, 3136]
	cmp	w1, w0
	bge	.L2059
	sub	w0, w0, w1
	cmp	w0, wzr
	ble	.L2059
	mov	w27, 0
	b	.L2060
	.p2align 3
.L2117:
	ldr	w0, [x19, 3132]
	ldr	w1, [x19, 3136]
	sub	w0, w0, w1
	cmp	w0, w27
	ble	.L2059
.L2060:
	ldr	w0, [x19, 3272]
	mov	w1, 0
	add	w27, w27, 1
	bl	FSP_RelsePhyFs
	cbz	w0, .L2117
.L2059:
	ldr	w0, [x19, 3272]
	mov	w1, 0
	bl	FSP_GetPhyFsNum
	mov	w27, w0
	ldr	w0, [x19, 3136]
	add	w0, w0, 4
	cmp	w27, w0
	bgt	.L2118
	ldr	w1, [x19, 3128]
	ldr	w0, [x19, 3272]
	bl	FSP_GetPhyFsNum
	add	w1, w0, 1
	ldr	w6, [x19, 3140]
	mov	w5, w0
	ldr	w2, [x19, 3136]
	mov	w4, w27
	add	w7, w6, 2
	str	w0, [x19, 3132]
	cmp	w1, w7
	csel	w1, w1, w7, le
	sub	w7, w0, w27
	add	w7, w7, w2
	mov	w0, 2
	cmp	w1, w7
	csel	w7, w1, w7, ge
	str	w7, [x19, 3136]
	ldr	x1, .LC146
	ldr	w2, [x26, 2664]
	ldr	w3, [x26, 2668]
	bl	dprint_vfmw
	ldr	w0, [x26, 2580]
	cbz	w0, .L2061
	ldr	w1, [x19, 3148]
	ldr	w0, [x26, 2664]
	cmp	w1, w0
	bne	.L2061
	ldr	w1, [x19, 3152]
	ldr	w0, [x26, 2668]
	cmp	w1, w0
	bne	.L2061
	ldr	w1, [x19, 3132]
	ldr	w0, [x19, 3136]
	cmp	w1, w0
	bge	.L2062
	.p2align 2
.L2061:
	mov	x0, x20
	bl	VP9_ArrangeVHBMem
	ldr	w0, [x26, 2580]
	cbz	w0, .L2119
.L2062:
	ldr	x0, [x20]
	ldr	w0, [x0, 8]
	str	w0, [x26, 2576]
	ldr	w0, [x21, 3636]
	cbz	w0, .L2120
.L2063:
	ldr	w0, [x19, 3272]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	bne	.L2121
	mov	x0, x22
	bl	BsBitsToNextByte
	cbnz	w0, .L2122
.L2065:
	ldr	w0, [x26, 7732]
	cbz	w0, .L2123
.L2066:
	mov	x0, x20
	bl	VP9_GetImageBuffer
	cbnz	w0, .L2124
	ldrsw	x1, [x19, 3164]
	add	x22, x26, 2644
	ldr	w2, [x26, 2628]
	mov	x0, x20
	add	x1, x22, x1, lsl 2
	str	w2, [x1, 196]
	bl	VP9_Set_DecParam
	cbnz	w0, .L2125
	ldr	w1, [x21, 3636]
	cmp	w1, 1
	beq	.L2126
	ldr	w0, [x22, 20]
	str	w0, [x19, 3156]
	ldr	w0, [x22, 24]
	str	w0, [x19, 3160]
.L2071:
	mov	x0, x24
	bl	swap_frame_buffers
	ldr	x2, [x19, 3216]
	ldr	x3, [x19, 3224]
	cmp	x2, x3
	bcs	.L2072
	ldrb	w0, [x2]
	cbnz	w0, .L2072
	add	x0, x2, 1
	b	.L2073
	.p2align 3
.L2127:
	ldrb	w1, [x0], 1
	cbnz	w1, .L2072
.L2073:
	cmp	x3, x0
	str	x0, [x19, 3216]
	mov	x2, x0
	bne	.L2127
.L2072:
	ldr	w0, [x19, 3172]
	cmp	w0, 1
	beq	.L2128
.L2074:
	str	wzr, [x19, 3168]
	ldr	w0, [x26, 7732]
	cbnz	w0, .L2075
	ldr	w1, [x21, 3632]
	str	w1, [x21, 3644]
	b	.L2107
.L2115:
	mov	w0, 0
	.p2align 2
.L2038:
	add	x1, x26, x0, sxtw 2
	mov	w2, 1
	str	w2, [x1, 2724]
	str	w0, [x21, 3608]
	tbz	w0, #31, .L2037
	b	.L2077
	.p2align 3
.L2113:
	ldr	x1, .LC143
	mov	w0, 1
	bl	dprint_vfmw
.L2109:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2112:
	ldr	x1, .LC140
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC141
	ldr	x4, [x0]
	cbz	x4, .L2044
	ldr	w0, [x26, 7772]
	mov	w3, 8
	stp	wzr, w0, [x29, 104]
	ldr	w0, [x19, 3272]
	add	x2, x29, 104
	mov	w1, 119
	blr	x4
	b	.L2044
.L2120:
	ldr	w1, [x26, 2664]
	str	w1, [x19, 3148]
	ldr	w0, [x26, 2668]
	str	w0, [x19, 3152]
	b	.L2063
.L2116:
	ldr	w4, [x19, 3152]
	ldr	w1, [x26, 2668]
	cmp	w4, w1
	bne	.L2051
	str	w2, [x19, 3144]
	b	.L2053
.L2122:
	mov	w1, w0
	mov	x0, x22
	bl	BsGet
	b	.L2065
.L2123:
	ldr	w0, [x23, 584]
	ldr	w2, [x23, 576]
	add	w0, w0, 7
	lsr	w1, w0, 3
	mov	x0, x20
	sub	w2, w2, w1
	add	x1, x25, x1
	bl	Vp9_DecodeTiles
	b	.L2066
.L2126:
	add	x1, x26, 2724
	ldr	w3, [x21, 3608]
	ldr	w0, [x21, 3640]
	ldr	w2, [x1, w3, sxtw 2]
	cmp	w2, wzr
	ble	.L2070
	sub	w2, w2, #1
	str	w2, [x1, w3, sxtw 2]
.L2070:
	str	w0, [x21, 3608]
	ldr	w2, [x1, w0, sxtw 2]
	add	w2, w2, 1
	str	w2, [x1, w0, sxtw 2]
	b	.L2071
.L2075:
	mov	w3, 0
	mov	w2, 0
	mov	w1, 0
	mov	x0, x20
	bl	VP9DEC_VDMPostProc
	mov	w0, 0
	b	.L2107
.L2128:
	ldr	w0, [x19, 3212]
	add	w1, w0, 1
	sxtw	x0, w0
	add	x0, x0, 77824
	add	x0, x20, x0, lsl 2
	ldrsw	x0, [x0, 3176]
	str	w1, [x19, 3212]
	add	x2, x2, x0
	str	x2, [x19, 3216]
	b	.L2074
.L2118:
	mov	w0, -2
	b	.L2107
.L2121:
	ldr	x2, .LC149
	mov	w3, 4047
	ldr	x1, .LC151
	mov	w0, 23
	add	x2, x2, 832
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2107
.L2124:
	ldr	x1, .LC153
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2107
.L2119:
	ldr	x1, .LC148
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2107
.L2125:
	ldr	x1, .LC155
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2107
	.size	VP9DEC_DecodeFame, .-VP9DEC_DecodeFame
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC141:
	.xword	g_event_report
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC144:
	.xword	s_pstVfmwChan
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC149:
	.xword	.LANCHOR0
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_DecodePacket
	.type	VP9DEC_DecodePacket, %function
VP9DEC_DecodePacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 60]
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L2141
	add	x22, x19, 270336
	ldr	x0, [x20]
	add	x21, x19, 311296
	str	x0, [x22, 2560]
	ldr	w1, [x20, 16]
	str	w1, [x22, 2568]
	ldr	w1, [x20, 20]
	str	w1, [x22, 2572]
	ldr	w5, [x21, 3172]
	cbz	w5, .L2131
	ldr	w2, [x21, 3232]
	ldr	x20, [x21, 3216]
	.p2align 2
.L2135:
	cbz	w2, .L2143
	ldrb	w1, [x20]
	and	w0, w1, 7
	and	w4, w1, 224
	ubfx	x3, x1, 3, 2
	add	w0, w0, 1
	cmp	w4, 192
	madd	w0, w3, w0, w0
	bne	.L2137
	add	w3, w0, 2
	cmp	w3, w2
	bhi	.L2135
	add	w0, w0, 1
	ldrb	w0, [x20, x0]
	cmp	w0, w1
	bne	.L2135
	ldr	x0, [x21, 3224]
	add	x20, x20, x3, uxtb
	sub	w2, w2, w3
	str	x20, [x21, 3216]
	cmp	x20, x0
	str	w2, [x21, 3232]
	bcc	.L2135
	.p2align 2
.L2137:
	cmp	w5, 1
	beq	.L2151
.L2139:
	add	x0, x19, 278528
	mov	x1, x20
	add	x0, x0, 552
	bl	BsInit
	mov	x1, x20
	mov	x0, x19
	bl	VP9DEC_DecodeFame
	cmn	w0, #2
	mov	w20, w0
	beq	.L2152
	mov	w0, 0
	cbnz	w20, .L2153
.L2130:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2153:
	mov	x0, x19
	bl	VP9_FreeCurFb
	str	wzr, [x21, 3172]
	mov	x1, x19
	mov	w0, 17
	bl	ReleasePacket
	ldr	x1, .LC158
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2143:
	cmp	w5, 1
	mov	w2, 0
	bne	.L2139
.L2151:
	ldrsw	x0, [x21, 3212]
	add	x0, x0, 77824
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 3176]
	b	.L2139
	.p2align 3
.L2131:
	add	x3, x29, 60
	add	x2, x29, 64
	bl	Vp9_ParseSuperFrameIndex
	ldr	w0, [x29, 60]
	cbnz	w0, .L2154
.L2133:
	ldr	x20, [x22, 2560]
	str	x20, [x21, 3216]
	ldr	w5, [x21, 3172]
	ldr	w2, [x22, 2572]
	str	w2, [x21, 3232]
	add	x0, x20, x2, uxtw
	str	x0, [x21, 3224]
	b	.L2135
.L2154:
	ldr	x1, .LC156
	mov	w2, 1
	str	w0, [x21, 3208]
	add	x0, x21, 3176
	str	w2, [x21, 3172]
	mov	x2, 32
	ldr	x3, [x1, 104]
	add	x1, x29, 64
	str	wzr, [x21, 3212]
	blr	x3
	b	.L2133
	.p2align 3
.L2152:
	mov	w1, 1
	str	w1, [x21, 3168]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
.L2141:
	mov	w0, -1
	b	.L2130
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.align	3
.LC156:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC158:
	.xword	.LC157
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_TxCoefProbConvert2
	.type	Vp9_TxCoefProbConvert2, %function
Vp9_TxCoefProbConvert2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC159
	mov	x1, x20
	mov	x2, 18
	mov	x0, x19
	ldr	x3, [x21, 104]
	blr	x3
	mov	x2, 18
	ldr	x3, [x21, 104]
	add	x1, x20, x2
	add	x0, x19, 32
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 36
	mov	x2, 18
	add	x0, x19, 64
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 54
	mov	x2, 18
	add	x0, x19, 96
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 72
	mov	x2, 18
	add	x0, x19, 128
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 90
	mov	x2, 18
	add	x0, x19, 160
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 108
	mov	x2, 18
	add	x0, x19, 192
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 256
	mov	x2, 18
	add	x0, x19, 256
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 274
	mov	x2, 18
	add	x0, x19, 288
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 292
	mov	x2, 18
	add	x0, x19, 320
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 310
	mov	x2, 18
	add	x0, x19, 352
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 328
	mov	x2, 18
	add	x0, x19, 384
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 346
	mov	x2, 18
	add	x0, x19, 416
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 364
	mov	x2, 18
	add	x0, x19, 448
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_TxCoefProbConvert2, .-Vp9_TxCoefProbConvert2
	.align	3
.LC159:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ProbBurstConvert
	.type	Vp9_ProbBurstConvert, %function
Vp9_ProbBurstConvert:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x3, .LC160
	mov	x1, x20
	mov	x2, 4608
	mov	x0, x19
	ldr	x3, [x3, 104]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	3
.LC160:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_CoefCountRestore
	.type	Vp9_CoefCountRestore, %function
Vp9_CoefCountRestore:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	mov	x1, x21
	mov	w15, 0
	mov	w0, 0
.L2158:
	add	w16, w0, 288
	mov	x14, x1
	mov	w13, w15
.L2164:
	add	w12, w0, 144
	mov	x11, x14
	mov	w2, w13
	.p2align 2
.L2162:
	add	w10, w0, 24
	mov	x3, x11
	mov	w6, w2
	.p2align 2
.L2159:
	ldr	w4, [x19, w0, uxtw 2]
	add	w5, w0, 1
	add	x3, x3, 16
	add	w8, w0, 2
	and	w9, w4, 67108863
	str	w9, [x20, w6, uxtw 2]
	add	w7, w0, 3
	add	w0, w0, 4
	ldr	w5, [x19, w5, uxtw 2]
	cmp	w0, w10
	add	w6, w6, 1
	ubfiz	w9, w5, 6, 20
	orr	w4, w9, w4, lsr 26
	str	w4, [x3, -16]
	ldr	w4, [x19, w8, uxtw 2]
	ubfiz	w8, w4, 12, 14
	orr	w5, w8, w5, lsr 20
	str	w5, [x3, -12]
	ldr	w5, [x19, w7, uxtw 2]
	ubfiz	w7, w5, 18, 8
	lsr	w5, w5, 8
	orr	w4, w7, w4, lsr 14
	stp	w4, w5, [x3, -8]
	bne	.L2159
	cmp	w0, w12
	add	w2, w2, 6
	add	x11, x11, 96
	bne	.L2162
	cmp	w10, w16
	add	w13, w13, 36
	add	x14, x14, 576
	bne	.L2164
	cmp	w10, 576
	add	w15, w15, 72
	add	x1, x1, 1152
	mov	w0, w10
	bne	.L2158
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	vp9_cabac_norm, %object
	.size	vp9_cabac_norm, 256
vp9_cabac_norm:
	.byte	0
	.byte	7
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_inv_map_table, %object
	.size	vp9_inv_map_table, 254
vp9_inv_map_table:
	.byte	6
	.byte	19
	.byte	32
	.byte	45
	.byte	58
	.byte	71
	.byte	84
	.byte	97
	.byte	110
	.byte	123
	.byte	-120
	.byte	-107
	.byte	-94
	.byte	-81
	.byte	-68
	.byte	-55
	.byte	-42
	.byte	-29
	.byte	-16
	.byte	-3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	21
	.byte	22
	.byte	23
	.byte	24
	.byte	25
	.byte	26
	.byte	27
	.byte	28
	.byte	29
	.byte	30
	.byte	31
	.byte	33
	.byte	34
	.byte	35
	.byte	36
	.byte	37
	.byte	38
	.byte	39
	.byte	40
	.byte	41
	.byte	42
	.byte	43
	.byte	44
	.byte	46
	.byte	47
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	59
	.byte	60
	.byte	61
	.byte	62
	.byte	63
	.byte	64
	.byte	65
	.byte	66
	.byte	67
	.byte	68
	.byte	69
	.byte	70
	.byte	72
	.byte	73
	.byte	74
	.byte	75
	.byte	76
	.byte	77
	.byte	78
	.byte	79
	.byte	80
	.byte	81
	.byte	82
	.byte	83
	.byte	85
	.byte	86
	.byte	87
	.byte	88
	.byte	89
	.byte	90
	.byte	91
	.byte	92
	.byte	93
	.byte	94
	.byte	95
	.byte	96
	.byte	98
	.byte	99
	.byte	100
	.byte	101
	.byte	102
	.byte	103
	.byte	104
	.byte	105
	.byte	106
	.byte	107
	.byte	108
	.byte	109
	.byte	111
	.byte	112
	.byte	113
	.byte	114
	.byte	115
	.byte	116
	.byte	117
	.byte	118
	.byte	119
	.byte	120
	.byte	121
	.byte	122
	.byte	124
	.byte	125
	.byte	126
	.byte	127
	.byte	-128
	.byte	-127
	.byte	-126
	.byte	-125
	.byte	-124
	.byte	-123
	.byte	-122
	.byte	-121
	.byte	-119
	.byte	-118
	.byte	-117
	.byte	-116
	.byte	-115
	.byte	-114
	.byte	-113
	.byte	-112
	.byte	-111
	.byte	-110
	.byte	-109
	.byte	-108
	.byte	-106
	.byte	-105
	.byte	-104
	.byte	-103
	.byte	-102
	.byte	-101
	.byte	-100
	.byte	-99
	.byte	-98
	.byte	-97
	.byte	-96
	.byte	-95
	.byte	-93
	.byte	-92
	.byte	-91
	.byte	-90
	.byte	-89
	.byte	-88
	.byte	-87
	.byte	-86
	.byte	-85
	.byte	-84
	.byte	-83
	.byte	-82
	.byte	-80
	.byte	-79
	.byte	-78
	.byte	-77
	.byte	-76
	.byte	-75
	.byte	-74
	.byte	-73
	.byte	-72
	.byte	-71
	.byte	-70
	.byte	-69
	.byte	-67
	.byte	-66
	.byte	-65
	.byte	-64
	.byte	-63
	.byte	-62
	.byte	-61
	.byte	-60
	.byte	-59
	.byte	-58
	.byte	-57
	.byte	-56
	.byte	-54
	.byte	-53
	.byte	-52
	.byte	-51
	.byte	-50
	.byte	-49
	.byte	-48
	.byte	-47
	.byte	-46
	.byte	-45
	.byte	-44
	.byte	-43
	.byte	-41
	.byte	-40
	.byte	-39
	.byte	-38
	.byte	-37
	.byte	-36
	.byte	-35
	.byte	-34
	.byte	-33
	.byte	-32
	.byte	-31
	.byte	-30
	.byte	-28
	.byte	-27
	.byte	-26
	.byte	-25
	.byte	-24
	.byte	-23
	.byte	-22
	.byte	-21
	.byte	-20
	.byte	-19
	.byte	-18
	.byte	-17
	.byte	-15
	.byte	-14
	.byte	-13
	.byte	-12
	.byte	-11
	.byte	-10
	.byte	-9
	.byte	-8
	.byte	-7
	.byte	-6
	.byte	-5
	.byte	-4
	.zero	2
	.type	count_to_update_factor, %object
	.size	count_to_update_factor, 21
count_to_update_factor:
	.byte	0
	.byte	6
	.byte	12
	.byte	19
	.byte	25
	.byte	32
	.byte	38
	.byte	44
	.byte	51
	.byte	57
	.byte	64
	.byte	70
	.byte	76
	.byte	83
	.byte	89
	.byte	96
	.byte	102
	.byte	108
	.byte	115
	.byte	121
	.byte	-128
	.zero	3
	.type	__func__.12282, %object
	.size	__func__.12282, 19
__func__.12282:
	.string	"VP9_GetImageBuffer"
	.zero	5
	.type	seg_feature_data_max, %object
	.size	seg_feature_data_max, 16
seg_feature_data_max:
	.word	255
	.word	63
	.word	3
	.word	0
	.type	seg_feature_data_signed, %object
	.size	seg_feature_data_signed, 16
seg_feature_data_signed:
	.word	1
	.word	1
	.word	0
	.word	0
	.type	__func__.12458, %object
	.size	__func__.12458, 16
__func__.12458:
	.string	"VP9_Set_Segdata"
	.type	__FUNCTION__.12534, %object
	.size	__FUNCTION__.12534, 33
__FUNCTION__.12534:
	.string	"VP9_get_fixed_point_scale_factor"
	.zero	7
	.type	__FUNCTION__.12563, %object
	.size	__FUNCTION__.12563, 35
__FUNCTION__.12563:
	.string	"Vp9_ReadBitDepthColorSpaceSampling"
	.zero	5
	.type	__FUNCTION__.12593, %object
	.size	__FUNCTION__.12593, 25
__FUNCTION__.12593:
	.string	"Read_UnCompressed_Header"
	.zero	7
	.type	vp9_default_tx_probs, %object
	.size	vp9_default_tx_probs, 12
vp9_default_tx_probs:
	.byte	100
	.byte	66
	.byte	20
	.byte	-104
	.byte	15
	.byte	101
	.byte	3
	.byte	-120
	.byte	37
	.byte	5
	.byte	52
	.byte	13
	.type	vp9_default_nmv_context, %object
	.size	vp9_default_nmv_context, 69
vp9_default_nmv_context:
	.byte	-128
	.byte	-128
	.byte	32
	.byte	64
	.byte	96
	.byte	-32
	.byte	-112
	.byte	-64
	.byte	-88
	.byte	-64
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-11
	.byte	-40
	.byte	-128
	.byte	-80
	.byte	-96
	.byte	-80
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-48
	.byte	-40
	.byte	-48
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-96
	.byte	-128
	.byte	-128
	.zero	7
	.type	__func__.12814, %object
	.size	__func__.12814, 20
__func__.12814:
	.string	"Vp9_DecodeTilesCtrl"
	.zero	4
	.type	__func__.12673, %object
	.size	__func__.12673, 18
__func__.12673:
	.string	"VP9DEC_DecodeFame"
	.data
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 4352
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 1024
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.zero	1
	.byte	84
	.byte	49
	.byte	-120
	.zero	1
	.byte	8
	.byte	42
	.byte	71
	.zero	1
	.zero	20
	.byte	31
	.byte	107
	.byte	-87
	.zero	1
	.byte	35
	.byte	99
	.byte	-97
	.zero	1
	.byte	17
	.byte	82
	.byte	-116
	.zero	1
	.byte	8
	.byte	66
	.byte	114
	.zero	1
	.byte	2
	.byte	44
	.byte	76
	.zero	1
	.byte	1
	.byte	19
	.byte	32
	.zero	1
	.zero	8
	.byte	40
	.byte	-124
	.byte	-55
	.zero	1
	.byte	29
	.byte	114
	.byte	-69
	.zero	1
	.byte	13
	.byte	91
	.byte	-99
	.zero	1
	.byte	7
	.byte	75
	.byte	127
	.zero	1
	.byte	3
	.byte	58
	.byte	95
	.zero	1
	.byte	1
	.byte	28
	.byte	47
	.zero	1
	.zero	8
	.byte	69
	.byte	-114
	.byte	-35
	.zero	1
	.byte	42
	.byte	122
	.byte	-55
	.zero	1
	.byte	15
	.byte	91
	.byte	-97
	.zero	1
	.byte	6
	.byte	67
	.byte	121
	.zero	1
	.byte	1
	.byte	42
	.byte	77
	.zero	1
	.byte	1
	.byte	17
	.byte	31
	.zero	1
	.zero	8
	.byte	102
	.byte	-108
	.byte	-28
	.zero	1
	.byte	67
	.byte	117
	.byte	-52
	.zero	1
	.byte	17
	.byte	82
	.byte	-102
	.zero	1
	.byte	6
	.byte	59
	.byte	114
	.zero	1
	.byte	2
	.byte	39
	.byte	75
	.zero	1
	.byte	1
	.byte	15
	.byte	29
	.zero	1
	.zero	8
	.byte	-100
	.byte	57
	.byte	-23
	.zero	1
	.byte	119
	.byte	57
	.byte	-44
	.zero	1
	.byte	58
	.byte	48
	.byte	-93
	.zero	1
	.byte	29
	.byte	40
	.byte	124
	.zero	1
	.byte	12
	.byte	30
	.byte	81
	.zero	1
	.byte	3
	.byte	12
	.byte	31
	.zero	1
	.zero	8
	.zero	64
	.byte	-65
	.byte	107
	.byte	-30
	.zero	1
	.byte	124
	.byte	117
	.byte	-52
	.zero	1
	.byte	25
	.byte	99
	.byte	-101
	.zero	1
	.zero	20
	.byte	29
	.byte	-108
	.byte	-46
	.zero	1
	.byte	37
	.byte	126
	.byte	-62
	.zero	1
	.byte	8
	.byte	93
	.byte	-99
	.zero	1
	.byte	2
	.byte	68
	.byte	118
	.zero	1
	.byte	1
	.byte	39
	.byte	69
	.zero	1
	.byte	1
	.byte	17
	.byte	33
	.zero	1
	.zero	8
	.byte	41
	.byte	-105
	.byte	-43
	.zero	1
	.byte	27
	.byte	123
	.byte	-63
	.zero	1
	.byte	3
	.byte	82
	.byte	-112
	.zero	1
	.byte	1
	.byte	58
	.byte	105
	.zero	1
	.byte	1
	.byte	32
	.byte	60
	.zero	1
	.byte	1
	.byte	13
	.byte	26
	.zero	1
	.zero	8
	.byte	59
	.byte	-97
	.byte	-36
	.zero	1
	.byte	23
	.byte	126
	.byte	-58
	.zero	1
	.byte	4
	.byte	88
	.byte	-105
	.zero	1
	.byte	1
	.byte	66
	.byte	114
	.zero	1
	.byte	1
	.byte	38
	.byte	71
	.zero	1
	.byte	1
	.byte	18
	.byte	34
	.zero	1
	.zero	8
	.byte	114
	.byte	-120
	.byte	-24
	.zero	1
	.byte	51
	.byte	114
	.byte	-49
	.zero	1
	.byte	11
	.byte	83
	.byte	-101
	.zero	1
	.byte	3
	.byte	56
	.byte	105
	.zero	1
	.byte	1
	.byte	33
	.byte	65
	.zero	1
	.byte	1
	.byte	17
	.byte	34
	.zero	1
	.zero	8
	.byte	-107
	.byte	65
	.byte	-22
	.zero	1
	.byte	121
	.byte	57
	.byte	-41
	.zero	1
	.byte	61
	.byte	49
	.byte	-90
	.zero	1
	.byte	28
	.byte	36
	.byte	114
	.zero	1
	.byte	12
	.byte	25
	.byte	76
	.zero	1
	.byte	3
	.byte	16
	.byte	42
	.zero	1
	.zero	8
	.zero	64
	.byte	-42
	.byte	49
	.byte	-36
	.zero	1
	.byte	-124
	.byte	63
	.byte	-68
	.zero	1
	.byte	42
	.byte	65
	.byte	-119
	.zero	1
	.zero	20
	.byte	85
	.byte	-119
	.byte	-35
	.zero	1
	.byte	104
	.byte	-125
	.byte	-40
	.zero	1
	.byte	49
	.byte	111
	.byte	-64
	.zero	1
	.byte	21
	.byte	87
	.byte	-101
	.zero	1
	.byte	2
	.byte	49
	.byte	87
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.byte	89
	.byte	-93
	.byte	-26
	.zero	1
	.byte	90
	.byte	-119
	.byte	-36
	.zero	1
	.byte	29
	.byte	100
	.byte	-73
	.zero	1
	.byte	10
	.byte	70
	.byte	-121
	.zero	1
	.byte	2
	.byte	42
	.byte	81
	.zero	1
	.byte	1
	.byte	17
	.byte	33
	.zero	1
	.zero	8
	.byte	108
	.byte	-89
	.byte	-19
	.zero	1
	.byte	55
	.byte	-123
	.byte	-34
	.zero	1
	.byte	15
	.byte	97
	.byte	-77
	.zero	1
	.byte	4
	.byte	72
	.byte	-121
	.zero	1
	.byte	1
	.byte	45
	.byte	85
	.zero	1
	.byte	1
	.byte	19
	.byte	38
	.zero	1
	.zero	8
	.byte	124
	.byte	-110
	.byte	-16
	.zero	1
	.byte	66
	.byte	124
	.byte	-32
	.zero	1
	.byte	17
	.byte	88
	.byte	-81
	.zero	1
	.byte	4
	.byte	58
	.byte	122
	.zero	1
	.byte	1
	.byte	36
	.byte	75
	.zero	1
	.byte	1
	.byte	18
	.byte	37
	.zero	1
	.zero	8
	.byte	-115
	.byte	79
	.byte	-15
	.zero	1
	.byte	126
	.byte	70
	.byte	-29
	.zero	1
	.byte	66
	.byte	58
	.byte	-74
	.zero	1
	.byte	30
	.byte	44
	.byte	-120
	.zero	1
	.byte	12
	.byte	34
	.byte	96
	.zero	1
	.byte	2
	.byte	20
	.byte	47
	.zero	1
	.zero	8
	.zero	64
	.byte	-27
	.byte	99
	.byte	-7
	.zero	1
	.byte	-113
	.byte	111
	.byte	-21
	.zero	1
	.byte	46
	.byte	109
	.byte	-64
	.zero	1
	.zero	20
	.byte	82
	.byte	-98
	.byte	-20
	.zero	1
	.byte	94
	.byte	-110
	.byte	-32
	.zero	1
	.byte	25
	.byte	117
	.byte	-65
	.zero	1
	.byte	9
	.byte	87
	.byte	-107
	.zero	1
	.byte	3
	.byte	56
	.byte	99
	.zero	1
	.byte	1
	.byte	33
	.byte	57
	.zero	1
	.zero	8
	.byte	83
	.byte	-89
	.byte	-19
	.zero	1
	.byte	68
	.byte	-111
	.byte	-34
	.zero	1
	.byte	10
	.byte	103
	.byte	-79
	.zero	1
	.byte	2
	.byte	72
	.byte	-125
	.zero	1
	.byte	1
	.byte	41
	.byte	79
	.zero	1
	.byte	1
	.byte	20
	.byte	39
	.zero	1
	.zero	8
	.byte	99
	.byte	-89
	.byte	-17
	.zero	1
	.byte	47
	.byte	-115
	.byte	-32
	.zero	1
	.byte	10
	.byte	104
	.byte	-78
	.zero	1
	.byte	2
	.byte	73
	.byte	-123
	.zero	1
	.byte	1
	.byte	44
	.byte	85
	.zero	1
	.byte	1
	.byte	22
	.byte	47
	.zero	1
	.zero	8
	.byte	127
	.byte	-111
	.byte	-13
	.zero	1
	.byte	71
	.byte	-127
	.byte	-28
	.zero	1
	.byte	17
	.byte	93
	.byte	-79
	.zero	1
	.byte	3
	.byte	61
	.byte	124
	.zero	1
	.byte	1
	.byte	41
	.byte	84
	.zero	1
	.byte	1
	.byte	21
	.byte	52
	.zero	1
	.zero	8
	.byte	-99
	.byte	78
	.byte	-12
	.zero	1
	.byte	-116
	.byte	72
	.byte	-25
	.zero	1
	.byte	69
	.byte	58
	.byte	-72
	.zero	1
	.byte	31
	.byte	44
	.byte	-119
	.zero	1
	.byte	14
	.byte	38
	.byte	105
	.zero	1
	.byte	8
	.byte	23
	.byte	61
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 1024
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.zero	1
	.byte	52
	.byte	41
	.byte	-123
	.zero	1
	.byte	6
	.byte	31
	.byte	56
	.zero	1
	.zero	20
	.byte	37
	.byte	109
	.byte	-103
	.zero	1
	.byte	51
	.byte	102
	.byte	-109
	.zero	1
	.byte	23
	.byte	87
	.byte	-128
	.zero	1
	.byte	8
	.byte	67
	.byte	101
	.zero	1
	.byte	1
	.byte	41
	.byte	63
	.zero	1
	.byte	1
	.byte	19
	.byte	29
	.zero	1
	.zero	8
	.byte	31
	.byte	-102
	.byte	-71
	.zero	1
	.byte	17
	.byte	127
	.byte	-81
	.zero	1
	.byte	6
	.byte	96
	.byte	-111
	.zero	1
	.byte	2
	.byte	73
	.byte	114
	.zero	1
	.byte	1
	.byte	51
	.byte	82
	.zero	1
	.byte	1
	.byte	28
	.byte	45
	.zero	1
	.zero	8
	.byte	23
	.byte	-93
	.byte	-56
	.zero	1
	.byte	10
	.byte	-125
	.byte	-71
	.zero	1
	.byte	2
	.byte	93
	.byte	-108
	.zero	1
	.byte	1
	.byte	67
	.byte	111
	.zero	1
	.byte	1
	.byte	41
	.byte	69
	.zero	1
	.byte	1
	.byte	14
	.byte	24
	.zero	1
	.zero	8
	.byte	29
	.byte	-80
	.byte	-39
	.zero	1
	.byte	12
	.byte	-111
	.byte	-55
	.zero	1
	.byte	3
	.byte	101
	.byte	-100
	.zero	1
	.byte	1
	.byte	69
	.byte	111
	.zero	1
	.byte	1
	.byte	39
	.byte	63
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	57
	.byte	-64
	.byte	-23
	.zero	1
	.byte	25
	.byte	-102
	.byte	-41
	.zero	1
	.byte	6
	.byte	109
	.byte	-89
	.zero	1
	.byte	3
	.byte	78
	.byte	118
	.zero	1
	.byte	1
	.byte	48
	.byte	69
	.zero	1
	.byte	1
	.byte	21
	.byte	29
	.zero	1
	.zero	8
	.zero	64
	.byte	-54
	.byte	105
	.byte	-11
	.zero	1
	.byte	108
	.byte	106
	.byte	-40
	.zero	1
	.byte	18
	.byte	90
	.byte	-112
	.zero	1
	.zero	20
	.byte	33
	.byte	-84
	.byte	-37
	.zero	1
	.byte	64
	.byte	-107
	.byte	-50
	.zero	1
	.byte	14
	.byte	117
	.byte	-79
	.zero	1
	.byte	5
	.byte	90
	.byte	-115
	.zero	1
	.byte	2
	.byte	61
	.byte	95
	.zero	1
	.byte	1
	.byte	37
	.byte	57
	.zero	1
	.zero	8
	.byte	33
	.byte	-77
	.byte	-36
	.zero	1
	.byte	11
	.byte	-116
	.byte	-58
	.zero	1
	.byte	1
	.byte	89
	.byte	-108
	.zero	1
	.byte	1
	.byte	60
	.byte	104
	.zero	1
	.byte	1
	.byte	33
	.byte	57
	.zero	1
	.byte	1
	.byte	12
	.byte	21
	.zero	1
	.zero	8
	.byte	30
	.byte	-75
	.byte	-35
	.zero	1
	.byte	8
	.byte	-115
	.byte	-58
	.zero	1
	.byte	1
	.byte	87
	.byte	-111
	.zero	1
	.byte	1
	.byte	58
	.byte	100
	.zero	1
	.byte	1
	.byte	31
	.byte	55
	.zero	1
	.byte	1
	.byte	12
	.byte	20
	.zero	1
	.zero	8
	.byte	32
	.byte	-70
	.byte	-32
	.zero	1
	.byte	7
	.byte	-114
	.byte	-58
	.zero	1
	.byte	1
	.byte	86
	.byte	-113
	.zero	1
	.byte	1
	.byte	58
	.byte	100
	.zero	1
	.byte	1
	.byte	31
	.byte	55
	.zero	1
	.byte	1
	.byte	12
	.byte	22
	.zero	1
	.zero	8
	.byte	57
	.byte	-64
	.byte	-29
	.zero	1
	.byte	20
	.byte	-113
	.byte	-52
	.zero	1
	.byte	3
	.byte	96
	.byte	-102
	.zero	1
	.byte	1
	.byte	68
	.byte	112
	.zero	1
	.byte	1
	.byte	42
	.byte	69
	.zero	1
	.byte	1
	.byte	19
	.byte	32
	.zero	1
	.zero	8
	.zero	64
	.byte	-44
	.byte	35
	.byte	-41
	.zero	1
	.byte	113
	.byte	47
	.byte	-87
	.zero	1
	.byte	29
	.byte	48
	.byte	105
	.zero	1
	.zero	20
	.byte	74
	.byte	-127
	.byte	-53
	.zero	1
	.byte	106
	.byte	120
	.byte	-53
	.zero	1
	.byte	49
	.byte	107
	.byte	-78
	.zero	1
	.byte	19
	.byte	84
	.byte	-112
	.zero	1
	.byte	4
	.byte	50
	.byte	84
	.zero	1
	.byte	1
	.byte	15
	.byte	25
	.zero	1
	.zero	8
	.byte	71
	.byte	-84
	.byte	-39
	.zero	1
	.byte	44
	.byte	-115
	.byte	-47
	.zero	1
	.byte	15
	.byte	102
	.byte	-83
	.zero	1
	.byte	6
	.byte	76
	.byte	-123
	.zero	1
	.byte	2
	.byte	51
	.byte	89
	.zero	1
	.byte	1
	.byte	24
	.byte	42
	.zero	1
	.zero	8
	.byte	64
	.byte	-71
	.byte	-25
	.zero	1
	.byte	31
	.byte	-108
	.byte	-40
	.zero	1
	.byte	8
	.byte	103
	.byte	-81
	.zero	1
	.byte	3
	.byte	74
	.byte	-125
	.zero	1
	.byte	1
	.byte	46
	.byte	81
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-60
	.byte	-21
	.zero	1
	.byte	25
	.byte	-99
	.byte	-35
	.zero	1
	.byte	5
	.byte	105
	.byte	-82
	.zero	1
	.byte	1
	.byte	67
	.byte	120
	.zero	1
	.byte	1
	.byte	38
	.byte	69
	.zero	1
	.byte	1
	.byte	15
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-52
	.byte	-18
	.zero	1
	.byte	30
	.byte	-100
	.byte	-32
	.zero	1
	.byte	7
	.byte	107
	.byte	-79
	.zero	1
	.byte	2
	.byte	70
	.byte	124
	.zero	1
	.byte	1
	.byte	42
	.byte	73
	.zero	1
	.byte	1
	.byte	18
	.byte	34
	.zero	1
	.zero	8
	.zero	64
	.byte	-31
	.byte	86
	.byte	-5
	.zero	1
	.byte	-112
	.byte	104
	.byte	-21
	.zero	1
	.byte	42
	.byte	99
	.byte	-75
	.zero	1
	.zero	20
	.byte	85
	.byte	-81
	.byte	-17
	.zero	1
	.byte	112
	.byte	-91
	.byte	-27
	.zero	1
	.byte	29
	.byte	-120
	.byte	-56
	.zero	1
	.byte	12
	.byte	103
	.byte	-94
	.zero	1
	.byte	6
	.byte	77
	.byte	123
	.zero	1
	.byte	2
	.byte	53
	.byte	84
	.zero	1
	.zero	8
	.byte	75
	.byte	-73
	.byte	-17
	.zero	1
	.byte	30
	.byte	-101
	.byte	-35
	.zero	1
	.byte	3
	.byte	106
	.byte	-85
	.zero	1
	.byte	1
	.byte	74
	.byte	-128
	.zero	1
	.byte	1
	.byte	44
	.byte	76
	.zero	1
	.byte	1
	.byte	17
	.byte	28
	.zero	1
	.zero	8
	.byte	73
	.byte	-71
	.byte	-16
	.zero	1
	.byte	27
	.byte	-97
	.byte	-34
	.zero	1
	.byte	2
	.byte	107
	.byte	-84
	.zero	1
	.byte	1
	.byte	75
	.byte	127
	.zero	1
	.byte	1
	.byte	42
	.byte	73
	.zero	1
	.byte	1
	.byte	17
	.byte	29
	.zero	1
	.zero	8
	.byte	62
	.byte	-66
	.byte	-18
	.zero	1
	.byte	21
	.byte	-97
	.byte	-34
	.zero	1
	.byte	2
	.byte	107
	.byte	-84
	.zero	1
	.byte	1
	.byte	72
	.byte	122
	.zero	1
	.byte	1
	.byte	40
	.byte	71
	.zero	1
	.byte	1
	.byte	18
	.byte	32
	.zero	1
	.zero	8
	.byte	61
	.byte	-57
	.byte	-16
	.zero	1
	.byte	27
	.byte	-95
	.byte	-30
	.zero	1
	.byte	4
	.byte	113
	.byte	-76
	.zero	1
	.byte	1
	.byte	76
	.byte	-127
	.zero	1
	.byte	1
	.byte	46
	.byte	80
	.zero	1
	.byte	1
	.byte	23
	.byte	41
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 1024
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.zero	1
	.byte	5
	.byte	30
	.byte	95
	.zero	1
	.byte	1
	.byte	16
	.byte	30
	.zero	1
	.zero	20
	.byte	50
	.byte	75
	.byte	127
	.zero	1
	.byte	57
	.byte	75
	.byte	124
	.zero	1
	.byte	27
	.byte	67
	.byte	108
	.zero	1
	.byte	10
	.byte	54
	.byte	86
	.zero	1
	.byte	1
	.byte	33
	.byte	52
	.zero	1
	.byte	1
	.byte	12
	.byte	18
	.zero	1
	.zero	8
	.byte	43
	.byte	125
	.byte	-105
	.zero	1
	.byte	26
	.byte	108
	.byte	-108
	.zero	1
	.byte	7
	.byte	83
	.byte	122
	.zero	1
	.byte	2
	.byte	59
	.byte	89
	.zero	1
	.byte	1
	.byte	38
	.byte	60
	.zero	1
	.byte	1
	.byte	17
	.byte	27
	.zero	1
	.zero	8
	.byte	23
	.byte	-112
	.byte	-93
	.zero	1
	.byte	13
	.byte	112
	.byte	-102
	.zero	1
	.byte	2
	.byte	75
	.byte	117
	.zero	1
	.byte	1
	.byte	50
	.byte	81
	.zero	1
	.byte	1
	.byte	31
	.byte	51
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	18
	.byte	-94
	.byte	-71
	.zero	1
	.byte	6
	.byte	123
	.byte	-85
	.zero	1
	.byte	1
	.byte	78
	.byte	125
	.zero	1
	.byte	1
	.byte	51
	.byte	86
	.zero	1
	.byte	1
	.byte	31
	.byte	54
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	15
	.byte	-57
	.byte	-29
	.zero	1
	.byte	3
	.byte	-106
	.byte	-52
	.zero	1
	.byte	1
	.byte	91
	.byte	-110
	.zero	1
	.byte	1
	.byte	55
	.byte	95
	.zero	1
	.byte	1
	.byte	30
	.byte	53
	.zero	1
	.byte	1
	.byte	11
	.byte	20
	.zero	1
	.zero	8
	.zero	64
	.byte	19
	.byte	55
	.byte	-16
	.zero	1
	.byte	19
	.byte	59
	.byte	-60
	.zero	1
	.byte	3
	.byte	52
	.byte	105
	.zero	1
	.zero	20
	.byte	41
	.byte	-90
	.byte	-49
	.zero	1
	.byte	104
	.byte	-103
	.byte	-57
	.zero	1
	.byte	31
	.byte	123
	.byte	-75
	.zero	1
	.byte	14
	.byte	101
	.byte	-104
	.zero	1
	.byte	5
	.byte	72
	.byte	106
	.zero	1
	.byte	1
	.byte	36
	.byte	52
	.zero	1
	.zero	8
	.byte	35
	.byte	-80
	.byte	-45
	.zero	1
	.byte	12
	.byte	-125
	.byte	-66
	.zero	1
	.byte	2
	.byte	88
	.byte	-112
	.zero	1
	.byte	1
	.byte	60
	.byte	101
	.zero	1
	.byte	1
	.byte	36
	.byte	60
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.byte	28
	.byte	-73
	.byte	-43
	.zero	1
	.byte	8
	.byte	-122
	.byte	-65
	.zero	1
	.byte	1
	.byte	86
	.byte	-114
	.zero	1
	.byte	1
	.byte	56
	.byte	96
	.zero	1
	.byte	1
	.byte	30
	.byte	53
	.zero	1
	.byte	1
	.byte	12
	.byte	20
	.zero	1
	.zero	8
	.byte	20
	.byte	-66
	.byte	-41
	.zero	1
	.byte	4
	.byte	-121
	.byte	-64
	.zero	1
	.byte	1
	.byte	84
	.byte	-117
	.zero	1
	.byte	1
	.byte	53
	.byte	91
	.zero	1
	.byte	1
	.byte	28
	.byte	49
	.zero	1
	.byte	1
	.byte	11
	.byte	20
	.zero	1
	.zero	8
	.byte	13
	.byte	-60
	.byte	-40
	.zero	1
	.byte	2
	.byte	-119
	.byte	-64
	.zero	1
	.byte	1
	.byte	86
	.byte	-113
	.zero	1
	.byte	1
	.byte	57
	.byte	99
	.zero	1
	.byte	1
	.byte	32
	.byte	56
	.zero	1
	.byte	1
	.byte	13
	.byte	24
	.zero	1
	.zero	8
	.zero	64
	.byte	-45
	.byte	29
	.byte	-39
	.zero	1
	.byte	96
	.byte	47
	.byte	-100
	.zero	1
	.byte	22
	.byte	43
	.byte	87
	.zero	1
	.zero	20
	.byte	78
	.byte	120
	.byte	-63
	.zero	1
	.byte	111
	.byte	116
	.byte	-70
	.zero	1
	.byte	46
	.byte	102
	.byte	-92
	.zero	1
	.byte	15
	.byte	80
	.byte	-128
	.zero	1
	.byte	2
	.byte	49
	.byte	76
	.zero	1
	.byte	1
	.byte	18
	.byte	28
	.zero	1
	.zero	8
	.byte	71
	.byte	-95
	.byte	-53
	.zero	1
	.byte	42
	.byte	-124
	.byte	-64
	.zero	1
	.byte	10
	.byte	98
	.byte	-106
	.zero	1
	.byte	3
	.byte	69
	.byte	109
	.zero	1
	.byte	1
	.byte	44
	.byte	70
	.zero	1
	.byte	1
	.byte	18
	.byte	29
	.zero	1
	.zero	8
	.byte	57
	.byte	-70
	.byte	-45
	.zero	1
	.byte	30
	.byte	-116
	.byte	-60
	.zero	1
	.byte	4
	.byte	93
	.byte	-110
	.zero	1
	.byte	1
	.byte	62
	.byte	102
	.zero	1
	.byte	1
	.byte	38
	.byte	65
	.zero	1
	.byte	1
	.byte	16
	.byte	27
	.zero	1
	.zero	8
	.byte	47
	.byte	-57
	.byte	-39
	.zero	1
	.byte	14
	.byte	-111
	.byte	-60
	.zero	1
	.byte	1
	.byte	88
	.byte	-114
	.zero	1
	.byte	1
	.byte	57
	.byte	98
	.zero	1
	.byte	1
	.byte	36
	.byte	62
	.zero	1
	.byte	1
	.byte	15
	.byte	26
	.zero	1
	.zero	8
	.byte	26
	.byte	-37
	.byte	-27
	.zero	1
	.byte	5
	.byte	-101
	.byte	-49
	.zero	1
	.byte	1
	.byte	94
	.byte	-105
	.zero	1
	.byte	1
	.byte	60
	.byte	104
	.zero	1
	.byte	1
	.byte	36
	.byte	62
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.zero	64
	.byte	-23
	.byte	29
	.byte	-8
	.zero	1
	.byte	-110
	.byte	47
	.byte	-36
	.zero	1
	.byte	43
	.byte	52
	.byte	-116
	.zero	1
	.zero	20
	.byte	100
	.byte	-93
	.byte	-24
	.zero	1
	.byte	-77
	.byte	-95
	.byte	-34
	.zero	1
	.byte	63
	.byte	-114
	.byte	-52
	.zero	1
	.byte	37
	.byte	113
	.byte	-82
	.zero	1
	.byte	26
	.byte	89
	.byte	-119
	.zero	1
	.byte	18
	.byte	68
	.byte	97
	.zero	1
	.zero	8
	.byte	85
	.byte	-75
	.byte	-26
	.zero	1
	.byte	32
	.byte	-110
	.byte	-47
	.zero	1
	.byte	7
	.byte	100
	.byte	-92
	.zero	1
	.byte	3
	.byte	71
	.byte	121
	.zero	1
	.byte	1
	.byte	45
	.byte	77
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-69
	.byte	-26
	.zero	1
	.byte	20
	.byte	-108
	.byte	-49
	.zero	1
	.byte	2
	.byte	97
	.byte	-97
	.zero	1
	.byte	1
	.byte	68
	.byte	116
	.zero	1
	.byte	1
	.byte	40
	.byte	70
	.zero	1
	.byte	1
	.byte	14
	.byte	29
	.zero	1
	.zero	8
	.byte	40
	.byte	-62
	.byte	-29
	.zero	1
	.byte	8
	.byte	-109
	.byte	-52
	.zero	1
	.byte	1
	.byte	94
	.byte	-101
	.zero	1
	.byte	1
	.byte	65
	.byte	112
	.zero	1
	.byte	1
	.byte	39
	.byte	66
	.zero	1
	.byte	1
	.byte	14
	.byte	26
	.zero	1
	.zero	8
	.byte	16
	.byte	-48
	.byte	-28
	.zero	1
	.byte	3
	.byte	-105
	.byte	-49
	.zero	1
	.byte	1
	.byte	98
	.byte	-96
	.zero	1
	.byte	1
	.byte	67
	.byte	117
	.zero	1
	.byte	1
	.byte	41
	.byte	74
	.zero	1
	.byte	1
	.byte	17
	.byte	31
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 1024
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.zero	1
	.byte	7
	.byte	34
	.byte	80
	.zero	1
	.byte	1
	.byte	17
	.byte	29
	.zero	1
	.zero	20
	.byte	37
	.byte	75
	.byte	-128
	.zero	1
	.byte	41
	.byte	76
	.byte	-128
	.zero	1
	.byte	26
	.byte	66
	.byte	116
	.zero	1
	.byte	12
	.byte	52
	.byte	94
	.zero	1
	.byte	2
	.byte	32
	.byte	55
	.zero	1
	.byte	1
	.byte	10
	.byte	16
	.zero	1
	.zero	8
	.byte	50
	.byte	127
	.byte	-102
	.zero	1
	.byte	37
	.byte	109
	.byte	-104
	.zero	1
	.byte	16
	.byte	82
	.byte	121
	.zero	1
	.byte	5
	.byte	59
	.byte	85
	.zero	1
	.byte	1
	.byte	35
	.byte	54
	.zero	1
	.byte	1
	.byte	13
	.byte	20
	.zero	1
	.zero	8
	.byte	40
	.byte	-114
	.byte	-89
	.zero	1
	.byte	17
	.byte	110
	.byte	-99
	.zero	1
	.byte	2
	.byte	71
	.byte	112
	.zero	1
	.byte	1
	.byte	44
	.byte	72
	.zero	1
	.byte	1
	.byte	27
	.byte	45
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.byte	30
	.byte	-81
	.byte	-68
	.zero	1
	.byte	9
	.byte	124
	.byte	-87
	.zero	1
	.byte	1
	.byte	74
	.byte	116
	.zero	1
	.byte	1
	.byte	48
	.byte	78
	.zero	1
	.byte	1
	.byte	30
	.byte	49
	.zero	1
	.byte	1
	.byte	11
	.byte	18
	.zero	1
	.zero	8
	.byte	10
	.byte	-34
	.byte	-33
	.zero	1
	.byte	2
	.byte	-106
	.byte	-62
	.zero	1
	.byte	1
	.byte	83
	.byte	-128
	.zero	1
	.byte	1
	.byte	48
	.byte	79
	.zero	1
	.byte	1
	.byte	27
	.byte	45
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.zero	64
	.byte	36
	.byte	41
	.byte	-21
	.zero	1
	.byte	29
	.byte	36
	.byte	-63
	.zero	1
	.byte	10
	.byte	27
	.byte	111
	.zero	1
	.zero	20
	.byte	85
	.byte	-91
	.byte	-34
	.zero	1
	.byte	-79
	.byte	-94
	.byte	-41
	.zero	1
	.byte	110
	.byte	-121
	.byte	-61
	.zero	1
	.byte	57
	.byte	113
	.byte	-88
	.zero	1
	.byte	23
	.byte	83
	.byte	120
	.zero	1
	.byte	10
	.byte	49
	.byte	61
	.zero	1
	.zero	8
	.byte	85
	.byte	-66
	.byte	-33
	.zero	1
	.byte	36
	.byte	-117
	.byte	-56
	.zero	1
	.byte	5
	.byte	90
	.byte	-110
	.zero	1
	.byte	1
	.byte	60
	.byte	103
	.zero	1
	.byte	1
	.byte	38
	.byte	65
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	72
	.byte	-54
	.byte	-33
	.zero	1
	.byte	23
	.byte	-115
	.byte	-57
	.zero	1
	.byte	2
	.byte	86
	.byte	-116
	.zero	1
	.byte	1
	.byte	56
	.byte	97
	.zero	1
	.byte	1
	.byte	36
	.byte	61
	.zero	1
	.byte	1
	.byte	16
	.byte	27
	.zero	1
	.zero	8
	.byte	55
	.byte	-38
	.byte	-31
	.zero	1
	.byte	13
	.byte	-111
	.byte	-56
	.zero	1
	.byte	1
	.byte	86
	.byte	-115
	.zero	1
	.byte	1
	.byte	57
	.byte	99
	.zero	1
	.byte	1
	.byte	35
	.byte	61
	.zero	1
	.byte	1
	.byte	13
	.byte	22
	.zero	1
	.zero	8
	.byte	15
	.byte	-21
	.byte	-44
	.zero	1
	.byte	1
	.byte	-124
	.byte	-72
	.zero	1
	.byte	1
	.byte	84
	.byte	-117
	.zero	1
	.byte	1
	.byte	57
	.byte	97
	.zero	1
	.byte	1
	.byte	34
	.byte	56
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.zero	64
	.byte	-75
	.byte	21
	.byte	-55
	.zero	1
	.byte	61
	.byte	37
	.byte	123
	.zero	1
	.byte	10
	.byte	38
	.byte	71
	.zero	1
	.zero	20
	.byte	47
	.byte	106
	.byte	-84
	.zero	1
	.byte	95
	.byte	104
	.byte	-83
	.zero	1
	.byte	42
	.byte	93
	.byte	-97
	.zero	1
	.byte	18
	.byte	77
	.byte	-125
	.zero	1
	.byte	4
	.byte	50
	.byte	81
	.zero	1
	.byte	1
	.byte	17
	.byte	23
	.zero	1
	.zero	8
	.byte	62
	.byte	-109
	.byte	-57
	.zero	1
	.byte	44
	.byte	-126
	.byte	-67
	.zero	1
	.byte	28
	.byte	102
	.byte	-102
	.zero	1
	.byte	18
	.byte	75
	.byte	115
	.zero	1
	.byte	2
	.byte	44
	.byte	65
	.zero	1
	.byte	1
	.byte	12
	.byte	19
	.zero	1
	.zero	8
	.byte	55
	.byte	-103
	.byte	-46
	.zero	1
	.byte	24
	.byte	-126
	.byte	-62
	.zero	1
	.byte	3
	.byte	93
	.byte	-110
	.zero	1
	.byte	1
	.byte	61
	.byte	97
	.zero	1
	.byte	1
	.byte	31
	.byte	50
	.zero	1
	.byte	1
	.byte	10
	.byte	16
	.zero	1
	.zero	8
	.byte	49
	.byte	-70
	.byte	-33
	.zero	1
	.byte	17
	.byte	-108
	.byte	-52
	.zero	1
	.byte	1
	.byte	96
	.byte	-114
	.zero	1
	.byte	1
	.byte	53
	.byte	83
	.zero	1
	.byte	1
	.byte	26
	.byte	44
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.byte	13
	.byte	-39
	.byte	-44
	.zero	1
	.byte	2
	.byte	-120
	.byte	-76
	.zero	1
	.byte	1
	.byte	78
	.byte	124
	.zero	1
	.byte	1
	.byte	50
	.byte	83
	.zero	1
	.byte	1
	.byte	29
	.byte	49
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.zero	64
	.byte	-59
	.byte	13
	.byte	-9
	.zero	1
	.byte	82
	.byte	17
	.byte	-34
	.zero	1
	.byte	25
	.byte	17
	.byte	-94
	.zero	1
	.zero	20
	.byte	126
	.byte	-70
	.byte	-9
	.zero	1
	.byte	-22
	.byte	-65
	.byte	-13
	.zero	1
	.byte	-80
	.byte	-79
	.byte	-22
	.zero	1
	.byte	104
	.byte	-98
	.byte	-36
	.zero	1
	.byte	66
	.byte	-128
	.byte	-70
	.zero	1
	.byte	55
	.byte	90
	.byte	-119
	.zero	1
	.zero	8
	.byte	111
	.byte	-59
	.byte	-14
	.zero	1
	.byte	46
	.byte	-98
	.byte	-37
	.zero	1
	.byte	9
	.byte	104
	.byte	-85
	.zero	1
	.byte	2
	.byte	65
	.byte	125
	.zero	1
	.byte	1
	.byte	44
	.byte	80
	.zero	1
	.byte	1
	.byte	17
	.byte	91
	.zero	1
	.zero	8
	.byte	104
	.byte	-48
	.byte	-11
	.zero	1
	.byte	39
	.byte	-88
	.byte	-32
	.zero	1
	.byte	3
	.byte	109
	.byte	-94
	.zero	1
	.byte	1
	.byte	79
	.byte	124
	.zero	1
	.byte	1
	.byte	50
	.byte	102
	.zero	1
	.byte	1
	.byte	43
	.byte	102
	.zero	1
	.zero	8
	.byte	84
	.byte	-36
	.byte	-10
	.zero	1
	.byte	31
	.byte	-79
	.byte	-25
	.zero	1
	.byte	2
	.byte	115
	.byte	-76
	.zero	1
	.byte	1
	.byte	79
	.byte	-122
	.zero	1
	.byte	1
	.byte	55
	.byte	77
	.zero	1
	.byte	1
	.byte	60
	.byte	79
	.zero	1
	.zero	8
	.byte	43
	.byte	-13
	.byte	-16
	.zero	1
	.byte	8
	.byte	-76
	.byte	-39
	.zero	1
	.byte	1
	.byte	115
	.byte	-90
	.zero	1
	.byte	1
	.byte	84
	.byte	121
	.zero	1
	.byte	1
	.byte	51
	.byte	67
	.zero	1
	.byte	1
	.byte	16
	.byte	6
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_if_uv_probs, %object
	.size	vp9_default_if_uv_probs, 160
vp9_default_if_uv_probs:
	.byte	120
	.byte	7
	.byte	76
	.byte	-80
	.byte	-48
	.byte	126
	.byte	28
	.byte	54
	.byte	103
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	12
	.byte	-102
	.byte	-101
	.byte	-117
	.byte	90
	.byte	34
	.byte	117
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	67
	.byte	6
	.byte	25
	.byte	-52
	.byte	-13
	.byte	-98
	.byte	13
	.byte	21
	.byte	96
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	97
	.byte	5
	.byte	44
	.byte	-125
	.byte	-80
	.byte	-117
	.byte	48
	.byte	68
	.byte	97
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	42
	.byte	-100
	.byte	111
	.byte	-104
	.byte	26
	.byte	49
	.byte	-104
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	80
	.byte	5
	.byte	58
	.byte	-78
	.byte	74
	.byte	83
	.byte	33
	.byte	62
	.byte	-111
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	86
	.byte	5
	.byte	32
	.byte	-102
	.byte	-64
	.byte	-88
	.byte	14
	.byte	22
	.byte	-93
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	85
	.byte	5
	.byte	32
	.byte	-100
	.byte	-40
	.byte	-108
	.byte	19
	.byte	29
	.byte	73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	77
	.byte	7
	.byte	64
	.byte	116
	.byte	-124
	.byte	122
	.byte	37
	.byte	126
	.byte	120
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	101
	.byte	21
	.byte	107
	.byte	-75
	.byte	-64
	.byte	103
	.byte	19
	.byte	67
	.byte	125
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_if_y_probs, %object
	.size	vp9_default_if_y_probs, 64
vp9_default_if_y_probs:
	.byte	65
	.byte	32
	.byte	18
	.byte	-112
	.byte	-94
	.byte	-62
	.byte	41
	.byte	51
	.byte	98
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-124
	.byte	68
	.byte	18
	.byte	-91
	.byte	-39
	.byte	-60
	.byte	45
	.byte	40
	.byte	78
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-83
	.byte	80
	.byte	19
	.byte	-80
	.byte	-16
	.byte	-63
	.byte	64
	.byte	35
	.byte	46
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-35
	.byte	-121
	.byte	38
	.byte	-62
	.byte	-8
	.byte	121
	.byte	96
	.byte	85
	.byte	29
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_switchable_interp_prob, %object
	.size	vp9_default_switchable_interp_prob, 8
vp9_default_switchable_interp_prob:
	.byte	-21
	.byte	-94
	.byte	36
	.byte	-1
	.byte	34
	.byte	3
	.byte	-107
	.byte	-112
	.type	vp9_default_partition_probs, %object
	.size	vp9_default_partition_probs, 96
vp9_default_partition_probs:
	.byte	-98
	.byte	97
	.byte	94
	.byte	93
	.byte	24
	.byte	99
	.byte	85
	.byte	119
	.byte	44
	.byte	62
	.byte	59
	.byte	67
	.byte	-107
	.byte	53
	.byte	53
	.byte	94
	.byte	20
	.byte	48
	.byte	83
	.byte	53
	.byte	24
	.byte	52
	.byte	18
	.byte	18
	.byte	-106
	.byte	40
	.byte	39
	.byte	78
	.byte	12
	.byte	26
	.byte	67
	.byte	33
	.byte	11
	.byte	24
	.byte	7
	.byte	5
	.byte	-82
	.byte	35
	.byte	49
	.byte	68
	.byte	11
	.byte	27
	.byte	57
	.byte	15
	.byte	9
	.byte	12
	.byte	3
	.byte	3
	.byte	-57
	.byte	122
	.byte	-115
	.byte	-109
	.byte	63
	.byte	-97
	.byte	-108
	.byte	-123
	.byte	118
	.byte	121
	.byte	104
	.byte	114
	.byte	-82
	.byte	73
	.byte	87
	.byte	92
	.byte	41
	.byte	83
	.byte	82
	.byte	99
	.byte	50
	.byte	53
	.byte	39
	.byte	39
	.byte	-79
	.byte	58
	.byte	59
	.byte	68
	.byte	26
	.byte	63
	.byte	52
	.byte	79
	.byte	25
	.byte	17
	.byte	14
	.byte	12
	.byte	-34
	.byte	34
	.byte	30
	.byte	72
	.byte	16
	.byte	44
	.byte	58
	.byte	32
	.byte	12
	.byte	10
	.byte	7
	.byte	6
	.type	vp9_default_intra_inter_p, %object
	.size	vp9_default_intra_inter_p, 4
vp9_default_intra_inter_p:
	.byte	9
	.byte	102
	.byte	-69
	.byte	-31
	.zero	4
	.type	vp9_default_comp_inter_p, %object
	.size	vp9_default_comp_inter_p, 5
vp9_default_comp_inter_p:
	.byte	-17
	.byte	-73
	.byte	119
	.byte	96
	.byte	41
	.zero	3
	.type	vp9_default_comp_ref_p, %object
	.size	vp9_default_comp_ref_p, 5
vp9_default_comp_ref_p:
	.byte	50
	.byte	126
	.byte	123
	.byte	-35
	.byte	-30
	.zero	3
	.type	vp9_default_single_ref_p, %object
	.size	vp9_default_single_ref_p, 10
vp9_default_single_ref_p:
	.byte	33
	.byte	16
	.byte	77
	.byte	74
	.byte	-114
	.byte	-114
	.byte	-84
	.byte	-86
	.byte	-18
	.byte	-9
	.zero	6
	.type	vp9_default_mbskip_probs, %object
	.size	vp9_default_mbskip_probs, 3
vp9_default_mbskip_probs:
	.byte	-64
	.byte	-128
	.byte	64
	.zero	1
	.type	vp9_default_inter_mode_probs, %object
	.size	vp9_default_inter_mode_probs, 21
vp9_default_inter_mode_probs:
	.byte	2
	.byte	-83
	.byte	34
	.byte	7
	.byte	-111
	.byte	85
	.byte	7
	.byte	-90
	.byte	63
	.byte	7
	.byte	94
	.byte	66
	.byte	8
	.byte	64
	.byte	46
	.byte	17
	.byte	81
	.byte	31
	.byte	25
	.byte	29
	.byte	30
	.zero	3
	.type	g_CfgVp9FrmNum, %object
	.size	g_CfgVp9FrmNum, 4
g_CfgVp9FrmNum:
	.word	16
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC26:
	ASCII(.string	"IN VP9DEC_Init\n" )
.LC29:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC31:
	ASCII(.string	"data_sz == 0\n" )
	.zero	2
.LC33:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC35:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC37:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC39:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC41:
	ASCII(.string	"line: %d, fs is NULL!\n" )
	.zero	1
.LC44:
	ASCII(.string	"%s  idx=%d\n" )
	.zero	4
.LC46:
	ASCII(.string	"FSP_GetLogicFs err" )
	.zero	5
.LC48:
	ASCII(.string	"fsp.c,L%d: %s\n" )
	.zero	1
.LC51:
	ASCII(.string	"pCurImg is null\n" )
	.zero	7
.LC54:
	ASCII(.string	"err_level(%d) over ref_thr(%d)\n" )
.LC56:
	ASCII(.string	"line: %d pToQueImg is null\n" )
	.zero	4
.LC58:
	ASCII(.string	"insert img to Voqueue failed!\n" )
	.zero	1
.LC60:
	ASCII(.string	"pu8ProbCntVir == NULL\n" )
	.zero	1
.LC62:
	ASCII(.string	"Invalid frame sync code\n" )
	.zero	7
.LC71:
	ASCII(.string	"%s  %d ERR\n" )
	.zero	4
.LC80:
	ASCII(.string	"%s:%d this_size:%d is invalid!\n" )
.LC85:
	ASCII(.string	"4:4:4 color is not supported in profile 0 or 2 (%s : %d)\n" )
	.zero	6
.LC87:
	ASCII(.string	"Invalid frame marker\n" )
	.zero	2
.LC90:
	ASCII(.string	"%s:%d w&h=%dx%d is invalid!\n" )
	.zero	3
.LC92:
	ASCII(.string	"VP9_Set_DecParam but logic fs is null!\n" )
.LC94:
	ASCII(.string	"Decord FS is NULL!\n" )
	.zero	4
.LC96:
	ASCII(.string	"VP9_Set_DecParam but cur logic pstDecodeFs is null!\n" )
	.zero	3
.LC98:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC100:
	ASCII(.string	"pic_width_in_pix:%d, pic_height_in_pix:%d\n" )
	.zero	5
.LC102:
	ASCII(.string	"vp9 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC106:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC108:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC110:
	ASCII(.string	"vp9 alloc frame only\n" )
	.zero	2
.LC132:
	ASCII(.string	"%s:%d size is invalid  size:%d bslen:%d\n" )
	.zero	7
.LC135:
	ASCII(.string	"ERROR:Vp9_ReadCompressedHeader\n" )
.LC137:
	ASCII(.string	"get_free_fb failed!\n" )
	.zero	3
.LC139:
	ASCII(.string	"bit_depth(%d) > 10.\n" )
	.zero	3
.LC142:
	ASCII(.string	"ERROR: pCtx->StreamParam.Length(%d) < 8\n" )
	.zero	7
.LC145:
	ASCII(.string	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\n" )
	.zero	4
.LC147:
	ASCII(.string	"ERROR: No Img buffer is allocated\n" )
	.zero	5
.LC150:
	ASCII(.string	"%s %d, no fsp\n" )
	.zero	1
.LC152:
	ASCII(.string	"VP9_GetImageBuffer From Queue err\n" )
	.zero	5
.LC154:
	ASCII(.string	"ERROR: VP9_Set_DecParam\n" )
	.zero	7
.LC157:
	ASCII(.string	"VP9_DecOneNal ERR\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
