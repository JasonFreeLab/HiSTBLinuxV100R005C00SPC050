#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vp9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	Vp9_ModeMvMergeProbs, %function
Vp9_ModeMvMergeProbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	uxtb	w19, w0
	mov	x0, x30
	bl	_mcount
	ldp	w2, w1, [x20]
	mov	w0, w19
	adds	w3, w2, w1
	beq	.L2
	cmp	w3, 20
	mov	w4, 20
	csel	w4, w3, w4, ls
	lsr	w1, w3, 1
	ldr	x6, .LC2
	add	w2, w1, w2, lsl 8
	mov	w0, 256
	mov	w5, 255
	udiv	w1, w2, w3
	ldrb	w4, [x6, x4]
	cmp	w1, wzr
	sub	w0, w0, w4
	csinc	w1, w1, wzr, gt
	cmp	w1, w5
	mul	w0, w0, w19
	csel	w1, w1, w5, le
	add	w0, w0, 128
	and	w1, w1, w5
	madd	w0, w1, w4, w0
	ubfx	x0, x0, 8, 8
.L2:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ModeMvMergeProbs, .-Vp9_ModeMvMergeProbs
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
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
	tbnz	x0, 0, .L9
	asr	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L9:
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
	beq	.L11
	add	x1, x20, x19, uxtw
	cmp	x21, x1
	ccmp	x20, x1, 2, cs
	cset	w0, cc
.L11:
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
	tbnz	w22, #31, .L15
	ldr	w1, [x20, 36]
.L16:
	lsl	w2, w19, 24
	mov	w0, 0
	cmp	w2, w1
	bhi	.L17
	ldr	w3, [x20, 44]
	sub	w1, w1, w2
	mov	w0, 1
	sub	w19, w3, w19
.L17:
	ldr	x2, .LC3
	add	x2, x2, 24
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
.L15:
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
	b	.L16
	.size	Vp9_Cabac_Read, .-Vp9_Cabac_Read
	.align	3
.LC3:
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
	bmi	.L24
	ldr	x27, .LC5
	mov	w26, 0
	mov	w24, 24
	mov	w23, 1
	ldp	w20, w21, [x22, 36]
	ldr	w19, [x22, 44]
	b	.L23
	.p2align 3
.L21:
	lsl	w1, w19, 24
	add	x2, x27, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L22
	ldr	w3, [x22, 44]
	lsl	w0, w23, w25
	sub	w20, w20, w1
	sub	w19, w3, w19
.L22:
	orr	w26, w26, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w25, w25, #1
	lsl	w20, w20, w0
	sub	w21, w21, w0
	lsl	w19, w19, w0
	cmn	w25, #1
	stp	w20, w21, [x22, 36]
	str	w19, [x22, 44]
	beq	.L20
.L23:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w21, #31, .L21
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
	b	.L21
.L24:
	mov	w26, 0
.L20:
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
.LC5:
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
	bhi	.L30
	sub	w2, w2, w0
	sub	w1, w3, w1
	mov	w0, 1
.L29:
	ldr	x4, .LC7
	mov	w3, 24
	add	x4, x4, 24
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
.L30:
	mov	w0, 0
	b	.L29
	.size	Vp9_Cabac_ReaderInit, .-Vp9_Cabac_ReaderInit
	.align	3
.LC7:
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
	ldr	x25, .LC9
	ldp	w20, w22, [x21, 36]
	ldr	w19, [x21, 44]
	mov	w4, 24
	mov	w28, 16
	mov	w26, w23
.L34:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L42
.L32:
	lsl	w1, w19, 24
	add	x2, x25, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L33
	ldr	w3, [x21, 44]
	sub	w20, w20, w1
	lsl	w0, w26, w23
	sub	w19, w3, w19
.L33:
	orr	w24, w24, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w23, w23, #1
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w19, w19, w0
	cmn	w23, #1
	stp	w20, w22, [x21, 36]
	str	w19, [x21, 44]
	bne	.L34
	cmp	w24, 3
	beq	.L43
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L42:
	sub	w1, w4, w22
	sub	w27, w28, w22
	and	w1, w1, -8
	mov	x0, x21
	sub	w27, w27, w1
	str	w4, [x29, 108]
	and	w27, w27, 7
	add	w22, w1, w22
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldr	w4, [x29, 108]
	b	.L32
	.p2align 3
.L43:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L44
.L36:
	lsl	w0, w19, 24
	cmp	w0, w20
	bhi	.L37
	ldr	w1, [x21, 44]
	sub	w20, w20, w0
	mov	w24, 4
	sub	w19, w1, w19
.L37:
	add	x25, x25, 24
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
.L44:
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
	b	.L36
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
	.align	3
.LC9:
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
	tbnz	w24, #31, .L47
	ldr	w20, [x22, 36]
.L48:
	lsl	w1, w19, 24
	cmp	w1, w20
	bhi	.L49
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	ldr	x23, .LC11
	sub	w19, w0, w19
	add	x0, x23, 24
	ldrb	w0, [x0, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L92
.L51:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w0, w19, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L56
	ldr	w19, [x22, 44]
	add	x2, x23, 24
	sub	w20, w20, w1
	sub	w19, w19, w0
	ldrb	w0, [x2, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L93
.L58:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L62
	ldr	w19, [x22, 44]
	add	x2, x23, 24
	sub	w20, w20, w1
	mov	w25, 0
	sub	w0, w19, w0
	mov	w26, 6
	mov	w28, 24
	mov	w4, 16
	mov	w3, 1
	ldrb	w19, [x2, w0, uxtw]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	b	.L63
	.p2align 3
.L67:
	lsl	w1, w19, 24
	add	x2, x23, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L68
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w3, w26
.L68:
	orr	w25, w25, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	beq	.L94
.L63:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w24, #31, .L67
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
	b	.L67
	.p2align 3
.L49:
	ldr	x23, .LC11
	uxtw	x0, w19
	mov	w25, 0
	mov	w26, 3
	add	x1, x23, 24
	mov	w28, 24
	mov	w5, 16
	mov	w4, 1
	ldrb	w0, [x1, x0]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L54:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L95
.L52:
	lsl	w1, w19, 24
	add	x2, x23, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L53
	ldr	w3, [x22, 44]
	lsl	w0, w4, w26
	sub	w20, w20, w1
	sub	w19, w3, w19
.L53:
	orr	w25, w25, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L54
.L55:
	ldrb	w1, [x21]
	add	x23, x23, 280
	sub	w1, w1, #1
	lsl	w3, w1, 1
	ldrb	w2, [x23, w25, sxtw]
	cmp	w3, 255
	bgt	.L70
	add	w0, w2, 1
	cmp	w0, w3
	bgt	.L71
	tbnz	x0, 0, .L96
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L71:
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
.L70:
	mov	w0, 254
	add	w3, w2, 1
	sub	w1, w0, w1
	cmp	w3, w1, lsl 1
	ble	.L97
.L74:
	mov	w0, 255
	sub	w0, w0, w3
.L99:
	strb	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L97:
	tbnz	x3, 0, .L98
	add	w0, w3, w3, lsr 31
	add	w3, w1, w0, asr 1
	mov	w0, 255
	sub	w0, w0, w3
	b	.L99
	.p2align 3
.L56:
	add	x2, x23, 24
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 3
	mov	w4, 24
	mov	w3, 16
	ldrb	w19, [x2, x1]
	mov	w28, 1
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L61:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L100
.L59:
	lsl	w1, w19, 24
	add	x2, x23, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L60
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w28, w26
.L60:
	orr	w25, w25, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L61
	add	w25, w25, 16
	b	.L55
	.p2align 3
.L95:
	sub	w1, w28, w24
	sub	w27, w5, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w4, w5, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w4, w5, [x29, 104]
	b	.L52
	.p2align 3
.L96:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L71
	.p2align 3
.L98:
	add	w2, w2, 2
	sub	w3, w1, w2, lsr 1
	b	.L74
	.p2align 3
.L47:
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
	b	.L48
	.p2align 3
.L100:
	sub	w1, w4, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w4, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w4, w3, [x29, 104]
	b	.L59
	.p2align 3
.L62:
	add	x2, x23, 24
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 4
	mov	w4, 24
	mov	w3, 16
	ldrb	w19, [x2, x1]
	mov	w28, 1
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	.p2align 2
.L66:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L101
.L64:
	lsl	w1, w19, 24
	add	x2, x23, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L65
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w28, w26
.L65:
	orr	w25, w25, w0
	ldrb	w0, [x2, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L66
	add	w25, w25, 32
	b	.L55
	.p2align 3
.L101:
	sub	w1, w4, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w4, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w4, w3, [x29, 104]
	b	.L64
	.p2align 3
.L92:
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
	b	.L51
.L94:
	cmp	w25, 64
	bgt	.L102
	add	w25, w25, 64
	b	.L55
.L102:
	mov	w1, 128
	mov	x0, x22
	bl	Vp9_Cabac_Read
	add	w0, w0, w25, lsl 1
	sub	w25, w0, #65
	add	w25, w25, 64
	b	.L55
.L93:
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
	b	.L58
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
	.align	3
.LC11:
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
	mov	x19, x1
	mov	x23, x0
	mov	x0, x30
	add	x28, x23, 10
	add	x21, x23, 12
	mov	w25, 24
	bl	_mcount
	ldr	x27, .LC16
	ldp	w22, w20, [x19, 36]
	ldr	w2, [x19, 44]
	mov	w24, 16
.L106:
	sub	w2, w2, #1
	lsl	w26, w2, 6
	sub	w2, w26, w2
	ubfx	x2, x2, 6, 24
	add	w26, w2, 1
	tbnz	w20, #31, .L171
.L104:
	lsl	w2, w26, 24
	add	x4, x27, 24
	cmp	w2, w22
	mov	x1, x28
	mov	x0, x19
	sub	w3, w22, w2
	bhi	.L105
	ldr	w2, [x19, 44]
	sub	w2, w2, w26
	ldrb	w26, [x4, w2, uxtw]
	lsl	w2, w2, w26
	sub	w20, w20, w26
	lsl	w3, w3, w26
	str	w2, [x19, 44]
	stp	w3, w20, [x19, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w2, [x19, 44]
	ldp	w22, w20, [x19, 36]
.L148:
	add	x28, x28, 1
	cmp	x21, x28
	bne	.L106
	add	x28, x23, 7
	add	x24, x23, 11
	mov	w26, 24
	mov	w25, 16
.L111:
	sub	w2, w2, #1
	lsl	w21, w2, 6
	sub	w2, w21, w2
	ubfx	x21, x2, 6, 24
	add	w21, w21, 1
	tbnz	w20, #31, .L172
.L107:
	lsl	w0, w21, 24
	cmp	w0, w22
	bhi	.L108
	ldr	w2, [x19, 44]
	add	x3, x27, 24
	sub	w22, w22, w0
	sub	x1, x28, #1
	sub	w21, w2, w21
	mov	x0, x19
	ldrb	w2, [x3, w21, uxtw]
	lsl	w22, w22, w2
	sub	w20, w20, w2
	lsl	w21, w21, w2
	str	w21, [x19, 44]
	stp	w22, w20, [x19, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w21, [x19, 44]
	ldp	w22, w20, [x19, 36]
	sub	w21, w21, #1
	lsl	w2, w21, 6
	sub	w21, w2, w21
	ubfx	x21, x21, 6, 24
	add	w21, w21, 1
	tbnz	w20, #31, .L173
.L109:
	lsl	w0, w21, 24
	cmp	w0, w22
	bhi	.L110
	ldr	w2, [x19, 44]
	add	x3, x27, 24
	sub	w22, w22, w0
	mov	x1, x28
	sub	w2, w2, w21
	mov	x0, x19
	ldrb	w21, [x3, w2, uxtw]
	lsl	w2, w2, w21
	lsl	w22, w22, w21
	sub	w20, w20, w21
	str	w2, [x19, 44]
	stp	w22, w20, [x19, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w2, [x19, 44]
	ldp	w22, w20, [x19, 36]
.L150:
	add	x28, x28, 2
	cmp	x24, x28
	bne	.L111
	sub	w2, w2, #1
	mov	x28, x23
	lsl	w0, w2, 6
	add	x21, x23, 6
	sub	w2, w0, w2
	mov	w25, 24
	ubfx	x2, x2, 6, 24
	mov	w24, 16
	mov	w23, 1
	mov	w26, 254
	add	w2, w2, 1
	tbnz	w20, #31, .L174
.L112:
	lsl	w1, w2, 24
	cmp	w1, w22
	bhi	.L113
.L181:
	ldr	w0, [x19, 44]
	add	x3, x27, 24
	sub	w22, w22, w1
	mov	x1, x28
	sub	w2, w0, w2
	ldrb	w0, [x3, w2, uxtw]
	lsl	w22, w22, w0
	sub	w20, w20, w0
	lsl	w2, w2, w0
	mov	x0, x19
	stp	w22, w20, [x19, 36]
	str	w2, [x19, 44]
	bl	Vp9_DiffUpdateProb
	ldr	w0, [x19, 44]
	ldp	w22, w4, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w4, #31, .L175
.L114:
	lsl	w1, w20, 24
	cmp	w1, w22
	bhi	.L115
.L182:
	ldr	w0, [x19, 44]
	add	x2, x27, 24
	sub	w22, w22, w1
	add	x1, x28, 1
	sub	w0, w0, w20
	ldrb	w3, [x2, w0, uxtw]
	lsl	w0, w0, w3
	lsl	w22, w22, w3
	sub	w4, w4, w3
	str	w0, [x19, 44]
	stp	w22, w4, [x19, 36]
	mov	x0, x19
	bl	Vp9_DiffUpdateProb
	ldr	w0, [x19, 44]
	ldp	w22, w4, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w3, w0, 1
	tbnz	w4, #31, .L176
.L116:
	lsl	w0, w3, 24
	cmp	w0, w22
	bhi	.L117
	ldr	w1, [x19, 44]
	add	x2, x27, 24
	sub	w22, w22, w0
	sub	w1, w1, w3
	ldrb	w0, [x2, w1, uxtw]
	lsl	w2, w22, w0
	sub	w4, w4, w0
	lsl	w22, w1, w0
	str	w22, [x19, 44]
	stp	w2, w4, [x19, 36]
	tbnz	w4, #31, .L177
.L118:
	sub	w1, w22, #1
	ubfx	x20, x1, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w2
	bhi	.L119
	ldr	w20, [x19, 44]
	sub	w22, w2, w0
	add	x0, x27, 24
	sub	w20, w20, w1
	ldrb	w1, [x0, w20, uxtw]
	lsl	w22, w22, w1
	sub	w4, w4, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w22, w4, [x19, 36]
	tbnz	w4, #31, .L178
.L121:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L126
	sub	w22, w22, w1
	ldr	w1, [x19, 44]
	sub	w0, w1, w0
	add	x1, x27, 24
	ldrb	w20, [x1, w0, uxtw]
	lsl	w22, w22, w20
	sub	w4, w4, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w22, w4, [x19, 36]
	tbnz	w4, #31, .L179
.L128:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L132
	ldr	w20, [x19, 44]
	add	x2, x27, 24
	sub	w1, w22, w1
	mov	w22, 0
	sub	w0, w20, w0
	ldrb	w20, [x2, w0, uxtw]
	sub	w3, w4, w20
	lsl	w1, w1, w20
	mov	w4, 6
	lsl	w20, w0, w20
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	b	.L133
	.p2align 3
.L137:
	lsl	w1, w20, 24
	add	x5, x27, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L138
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w23, w4
.L138:
	orr	w22, w22, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L180
.L133:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L137
	sub	w1, w25, w3
	sub	w5, w24, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L137
	.p2align 3
.L110:
	add	x1, x27, 24
	uxtw	x0, w21
	ldrb	w2, [x1, x0]
	lsl	w22, w22, w2
	sub	w20, w20, w2
	lsl	w2, w21, w2
	str	w2, [x19, 44]
	stp	w22, w20, [x19, 36]
	b	.L150
	.p2align 3
.L117:
	add	x1, x27, 24
	uxtw	x0, w3
	ldrb	w0, [x1, x0]
	lsl	w22, w22, w0
	sub	w20, w4, w0
	lsl	w0, w3, w0
	str	w0, [x19, 44]
	stp	w22, w20, [x19, 36]
.L153:
	add	x28, x28, 3
	cmp	x21, x28
	beq	.L103
	ldr	w2, [x19, 44]
	ldp	w22, w20, [x19, 36]
	sub	w2, w2, #1
	lsl	w0, w2, 6
	sub	w2, w0, w2
	ubfx	x2, x2, 6, 24
	add	w2, w2, 1
	tbz	w20, #31, .L112
.L174:
	sub	w4, w25, w20
	sub	w3, w24, w20
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
	lsl	w1, w2, 24
	lsl	w0, w0, w3
	add	w20, w4, w20
	orr	w22, w0, w22
	cmp	w1, w22
	stp	w22, w20, [x19, 36]
	bls	.L181
	.p2align 2
.L113:
	add	x1, x27, 24
	uxtw	x0, w2
	ldrb	w0, [x1, x0]
	sub	w4, w20, w0
	lsl	w22, w22, w0
	lsl	w0, w2, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w22, w4, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w4, #31, .L114
.L175:
	sub	w2, w25, w4
	sub	w3, w24, w4
	and	w2, w2, -8
	mov	x0, x19
	sub	w3, w3, w2
	mov	w1, w2
	stp	w4, w3, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w4, w3, [x29, 100]
	ldr	w2, [x29, 108]
	lsl	w1, w20, 24
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w4, w2, w4
	orr	w22, w0, w22
	cmp	w1, w22
	stp	w22, w4, [x19, 36]
	bls	.L182
	.p2align 2
.L115:
	add	x1, x27, 24
	uxtw	x0, w20
	ldrb	w0, [x1, x0]
	lsl	w22, w22, w0
	sub	w4, w4, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w22, w4, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w3, w0, 1
	tbz	w4, #31, .L116
.L176:
	sub	w2, w25, w4
	mov	x0, x19
	and	w2, w2, -8
	sub	w20, w24, w4
	mov	w1, w2
	sub	w20, w20, w2
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	and	w1, w20, 7
	ldr	w2, [x29, 108]
	ldp	w3, w4, [x29, 100]
	lsl	w0, w0, w1
	orr	w22, w0, w22
	add	w4, w2, w4
	stp	w22, w4, [x19, 36]
	b	.L116
	.p2align 3
.L103:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L108:
	uxtw	x0, w21
	add	x1, x27, 24
	ldrb	w0, [x1, x0]
	lsl	w21, w21, w0
	str	w21, [x19, 44]
	sub	w21, w21, #1
	lsl	w22, w22, w0
	lsl	w2, w21, 6
	sub	w20, w20, w0
	sub	w21, w2, w21
	stp	w22, w20, [x19, 36]
	ubfx	x21, x21, 6, 24
	add	w21, w21, 1
	tbz	w20, #31, .L109
.L173:
	sub	w3, w26, w20
	sub	w2, w25, w20
	and	w3, w3, -8
	mov	x0, x19
	sub	w2, w2, w3
	mov	w1, w3
	stp	w2, w3, [x29, 104]
	bl	BsGet
	ldp	w2, w3, [x29, 104]
	and	w2, w2, 7
	add	w20, w3, w20
	lsl	w0, w0, w2
	orr	w22, w0, w22
	stp	w22, w20, [x19, 36]
	b	.L109
	.p2align 3
.L105:
	add	x1, x27, 24
	uxtw	x0, w26
	ldrb	w0, [x1, x0]
	lsl	w22, w22, w0
	sub	w20, w20, w0
	lsl	w2, w26, w0
	str	w2, [x19, 44]
	stp	w22, w20, [x19, 36]
	b	.L148
	.p2align 3
.L119:
	add	x3, x27, 24
	uxtw	x0, w1
	mov	w5, 3
	ldrb	w20, [x3, x0]
	lsl	w22, w2, w20
	sub	w2, w4, w20
	lsl	w20, w1, w20
	mov	w4, 0
	stp	w22, w2, [x19, 36]
	str	w20, [x19, 44]
.L124:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L183
.L122:
	lsl	w1, w20, 24
	add	x3, x27, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L123
	ldr	w0, [x19, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w5
.L123:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w22, w22, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w22, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L124
.L125:
	add	x0, x27, 280
	ldrb	w2, [x0, w4, sxtw]
	ldrb	w0, [x28, 2]
	sub	w0, w0, #1
	lsl	w3, w0, 1
	cmp	w3, 255
	bgt	.L140
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L141
	tbnz	x1, 0, .L184
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L141:
	add	w1, w1, 1
.L143:
	strb	w1, [x28, 2]
	b	.L153
	.p2align 3
.L140:
	sub	w0, w26, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L144
	tbnz	x1, 0, .L185
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L144:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x28, 2]
	b	.L153
	.p2align 3
.L171:
	sub	w3, w25, w20
	sub	w2, w24, w20
	and	w3, w3, -8
	mov	x0, x19
	sub	w2, w2, w3
	mov	w1, w3
	stp	w2, w3, [x29, 104]
	bl	BsGet
	ldp	w2, w3, [x29, 104]
	and	w2, w2, 7
	add	w20, w3, w20
	lsl	w0, w0, w2
	orr	w0, w0, w22
	mov	w22, w0
	stp	w0, w20, [x19, 36]
	b	.L104
	.p2align 3
.L172:
	sub	w3, w26, w20
	sub	w2, w25, w20
	and	w3, w3, -8
	mov	x0, x19
	sub	w2, w2, w3
	mov	w1, w3
	stp	w2, w3, [x29, 104]
	bl	BsGet
	ldp	w2, w3, [x29, 104]
	and	w2, w2, 7
	add	w20, w3, w20
	lsl	w0, w0, w2
	orr	w22, w0, w22
	stp	w22, w20, [x19, 36]
	b	.L107
	.p2align 3
.L183:
	sub	w1, w25, w2
	sub	w3, w24, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w22, w0, w22
	b	.L122
	.p2align 3
.L126:
	add	x2, x27, 24
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x2, x1]
	lsl	w22, w22, w20
	sub	w4, w4, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w22, w4, [x19, 36]
.L131:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w4, #31, .L186
.L129:
	lsl	w1, w20, 24
	add	x2, x27, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L130
	ldr	w0, [x19, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w5
.L130:
	orr	w3, w3, w0
	ldrb	w0, [x2, w20, uxtw]
	sub	w5, w5, #1
	lsl	w22, w22, w0
	sub	w4, w4, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w22, w4, [x19, 36]
	str	w20, [x19, 44]
	bne	.L131
	add	w4, w3, 16
	b	.L125
	.p2align 3
.L177:
	sub	w3, w25, w4
	mov	x0, x19
	and	w3, w3, -8
	sub	w20, w24, w4
	mov	w1, w3
	sub	w20, w20, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	and	w1, w20, 7
	ldr	w3, [x29, 108]
	lsl	w0, w0, w1
	orr	w0, w0, w2
	add	w4, w3, w4
	mov	w2, w0
	stp	w0, w4, [x19, 36]
	b	.L118
	.p2align 3
.L184:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L143
	.p2align 3
.L186:
	sub	w1, w25, w4
	sub	w2, w24, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w2, w2, w1
	add	w4, w1, w4
	stp	w5, w3, [x29, 96]
	stp	w2, w4, [x29, 104]
	bl	BsGet
	ldp	w2, w4, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w2, w2, 7
	lsl	w0, w0, w2
	orr	w22, w0, w22
	b	.L129
	.p2align 3
.L185:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L144
.L132:
	add	x2, x27, 24
	uxtw	x1, w0
	mov	w3, 4
	ldrb	w20, [x2, x1]
	sub	w2, w4, w20
	lsl	w22, w22, w20
	mov	w4, 0
	lsl	w20, w0, w20
	stp	w22, w2, [x19, 36]
	str	w20, [x19, 44]
	.p2align 2
.L136:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L187
.L134:
	lsl	w1, w20, 24
	add	x5, x27, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L135
	ldr	w0, [x19, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w3
.L135:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w22, w22, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w22, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L136
	add	w4, w4, 32
	b	.L125
	.p2align 3
.L187:
	sub	w1, w25, w2
	sub	w5, w24, w2
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
	orr	w22, w0, w22
	b	.L134
	.p2align 3
.L178:
	sub	w2, w25, w4
	sub	w3, w24, w4
	and	w2, w2, -8
	mov	x0, x19
	sub	w3, w3, w2
	mov	w1, w2
	stp	w4, w3, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w4, w3, [x29, 100]
	ldr	w2, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w4, w2, w4
	orr	w22, w0, w22
	stp	w22, w4, [x19, 36]
	b	.L121
.L180:
	cmp	w22, 64
	mov	w20, w22
	bgt	.L188
	add	w4, w20, 64
	b	.L125
.L188:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w22, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L125
.L179:
	sub	w2, w25, w4
	sub	w5, w24, w4
	and	w2, w2, -8
	mov	x0, x19
	sub	w5, w5, w2
	mov	w1, w2
	stp	w4, w5, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w2, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	add	w4, w2, w4
	orr	w22, w0, w22
	stp	w22, w4, [x19, 36]
	b	.L128
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
	.align	3
.LC16:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCoefProbsCommon
	.type	Vp9_ReadCoefProbsCommon, %function
Vp9_ReadCoefProbsCommon:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x1
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldp	w21, w0, [x28, 40]
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w21, #31, .L190
	ldr	w0, [x28, 36]
.L191:
	lsl	w4, w20, 24
	cmp	w4, w0
	bhi	.L192
	ldr	w1, [x28, 44]
	sub	w0, w0, w4
	ldr	x26, .LC19
	add	x3, x22, 432
	sub	w1, w1, w20
	mov	w24, 24
	add	x2, x26, 24
	str	x3, [x29, 104]
	ldrb	w2, [x2, w1, uxtw]
	lsl	w0, w0, w2
	sub	w21, w21, w2
	lsl	w1, w1, w2
	str	w1, [x28, 44]
	stp	w0, w21, [x28, 36]
.L193:
	str	x22, [x29, 112]
	str	wzr, [x29, 120]
.L297:
	ldrsw	x21, [x29, 120]
	mov	w19, 0
	ldr	x0, [x29, 112]
	str	x0, [x29, 152]
	mov	x0, x21
	lsl	x21, x21, 3
	sub	x21, x21, x0
	lsl	x21, x21, 2
	sub	x21, x21, x0
	.p2align 2
.L295:
	cmp	w19, wzr
	mov	w0, 3
	mov	w1, 6
	mov	w27, 0
	csel	w20, w0, w1, eq
	ldr	x25, [x29, 152]
	cmp	w27, w20
	bge	.L352
	.p2align 2
.L291:
	sxtw	x0, w19
	sxtw	x5, w27
	lsl	x2, x0, 4
	lsl	x1, x5, 2
	add	x0, x2, x0, lsl 1
	sub	x5, x1, x5
	ldp	w2, w4, [x28, 40]
	add	x5, x5, x0
	sub	w4, w4, #1
	add	x5, x5, x21, lsl 2
	lsl	w1, w4, 6
	add	x23, x22, x5
	sub	w0, w1, w4
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L194
	ldr	w4, [x28, 36]
.L195:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L196
	ldr	w0, [x28, 44]
	add	x9, x26, 24
	sub	w4, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x9, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L353
.L197:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L198
	ldr	w0, [x28, 44]
	add	x10, x26, 24
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x10, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L354
.L200:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L205
	ldr	w9, [x28, 44]
	add	x10, x26, 24
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x10, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L355
.L207:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L211
	sub	w4, w4, w1
	ldr	w1, [x28, 44]
	mov	w10, 0
	mov	w11, 6
	sub	w0, w1, w0
	add	x1, x26, 24
	mov	w12, 1
	ldrb	w9, [x1, w0, uxtw]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x28, 44]
	stp	w1, w4, [x28, 36]
	b	.L212
	.p2align 3
.L216:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w9
	mov	w0, 0
	bhi	.L217
	ldr	w14, [x28, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w2, w14, w2
.L217:
	orr	w10, w10, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w4, w4, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	beq	.L356
.L212:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L216
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w13, w0, w4
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w12, w9, [x29, 124]
	stp	w2, w11, [x29, 132]
	stp	w10, w13, [x29, 140]
	bl	BsGet
	ldp	w10, w13, [x29, 140]
	ldp	w12, w9, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w11, [x29, 132]
	orr	w9, w0, w9
	b	.L216
	.p2align 3
.L196:
	add	x1, x26, 24
	uxtw	x0, w10
	ldrb	w0, [x1, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x28, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w4, w2, [x28, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L357
.L227:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L228
	ldr	w0, [x28, 44]
	add	x9, x26, 24
	sub	w1, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x9, w0, uxtw]
	lsl	w4, w1, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L358
.L229:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L230
	ldr	w0, [x28, 44]
	add	x10, x26, 24
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x10, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L359
.L232:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L237
	ldr	w9, [x28, 44]
	add	x10, x26, 24
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x10, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x28, 44]
	stp	w4, w2, [x28, 36]
	tbnz	w2, #31, .L360
.L239:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L243
	sub	w4, w4, w1
	ldr	w1, [x28, 44]
	mov	w10, 0
	mov	w11, 6
	sub	w0, w1, w0
	add	x1, x26, 24
	mov	w12, 1
	ldrb	w9, [x1, w0, uxtw]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x28, 44]
	stp	w1, w4, [x28, 36]
	b	.L244
	.p2align 3
.L248:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w9
	mov	w0, 0
	bhi	.L249
	ldr	w14, [x28, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w2, w14, w2
.L249:
	orr	w10, w10, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w4, w4, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	beq	.L361
.L244:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L248
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w13, w0, w4
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w12, w9, [x29, 124]
	stp	w2, w11, [x29, 132]
	stp	w10, w13, [x29, 140]
	bl	BsGet
	ldp	w10, w13, [x29, 140]
	ldp	w12, w9, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w11, [x29, 132]
	orr	w9, w0, w9
	b	.L248
	.p2align 3
.L228:
	add	x1, x26, 24
	uxtw	x0, w10
	ldrb	w0, [x1, x0]
	lsl	w9, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x28, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w9, w2, [x28, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L362
.L259:
	lsl	w1, w10, 24
	cmp	w1, w9
	bhi	.L260
	ldr	w0, [x28, 44]
	add	x4, x26, 24
	sub	w1, w9, w1
	sub	w0, w0, w10
	ldrb	w4, [x4, w0, uxtw]
	lsl	w12, w1, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x28, 44]
	stp	w12, w2, [x28, 36]
	tbnz	w2, #31, .L363
.L261:
	sub	w4, w4, #1
	ubfx	x4, x4, 1, 24
	add	w0, w4, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L262
	ldr	w4, [x28, 44]
	add	x9, x26, 24
	sub	w1, w12, w1
	sub	w4, w4, w0
	ldrb	w0, [x9, w4, uxtw]
	lsl	w12, w1, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	str	w4, [x28, 44]
	stp	w12, w2, [x28, 36]
	tbnz	w2, #31, .L364
.L264:
	sub	w0, w4, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L269
	ldr	w4, [x28, 44]
	add	x9, x26, 24
	sub	w1, w12, w1
	sub	w0, w4, w0
	ldrb	w4, [x9, w0, uxtw]
	lsl	w12, w1, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x28, 44]
	stp	w12, w2, [x28, 36]
	tbnz	w2, #31, .L365
.L271:
	sub	w0, w4, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L275
	sub	w9, w12, w1
	ldr	w1, [x28, 44]
	mov	w11, 6
	mov	w12, 1
	sub	w0, w1, w0
	add	x1, x26, 24
	ldrb	w10, [x1, w0, uxtw]
	lsl	w1, w9, w10
	sub	w4, w2, w10
	lsl	w0, w0, w10
	mov	w10, 0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	b	.L276
	.p2align 3
.L280:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w9
	mov	w0, 0
	bhi	.L281
	ldr	w14, [x28, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w2, w14, w2
.L281:
	orr	w10, w10, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w4, w4, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	beq	.L366
.L276:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L280
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w13, w0, w4
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w12, w9, [x29, 124]
	stp	w2, w10, [x29, 132]
	stp	w11, w13, [x29, 140]
	bl	BsGet
	ldp	w11, w13, [x29, 140]
	ldp	w12, w9, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 132]
	orr	w9, w0, w9
	b	.L280
	.p2align 3
.L260:
	add	x1, x26, 24
	uxtw	x0, w10
	ldrb	w0, [x1, x0]
	lsl	w1, w9, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x28, 44]
	stp	w1, w2, [x28, 36]
.L300:
	add	w27, w27, 1
	add	x25, x25, 3
	cmp	w27, w20
	blt	.L291
.L352:
	ldr	x0, [x29, 152]
	add	w19, w19, 1
	cmp	w19, 6
	add	x0, x0, 18
	str	x0, [x29, 152]
	bne	.L295
	ldr	w0, [x29, 120]
	ldr	x1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 120]
	add	x1, x1, 108
	cmp	w0, 2
	str	x1, [x29, 112]
	bne	.L297
	ldr	x0, [x29, 104]
	add	x22, x22, 216
	cmp	x0, x22
	bne	.L193
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L262:
	uxtw	x1, w0
	add	x4, x26, 24
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w4, [x4, x1]
	lsl	w1, w12, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x28, 44]
	stp	w1, w2, [x28, 36]
.L267:
	sub	w4, w4, #1
	mov	w12, w1
	ubfx	x4, x4, 1, 24
	add	w4, w4, 1
	tbnz	w2, #31, .L367
.L265:
	lsl	w1, w4, 24
	add	x13, x26, 24
	cmp	w1, w12
	mov	w0, 0
	bhi	.L266
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w4, w14, w4
.L266:
	orr	w9, w9, w0
	ldrb	w0, [x13, w4, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	cmn	w10, #1
	stp	w1, w2, [x28, 36]
	str	w4, [x28, 44]
	bne	.L267
.L268:
	ldrb	w1, [x23, 2]
	add	x0, x26, 280
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L285
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L286
	tbnz	x0, 0, .L368
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L286:
	add	w0, w0, 1
.L288:
	strb	w0, [x23, 2]
	b	.L300
	.p2align 3
.L230:
	add	x12, x26, 24
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x12, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x28, 44]
	stp	w4, w2, [x28, 36]
.L235:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L369
.L233:
	lsl	w1, w12, 24
	add	x13, x26, 24
	cmp	w1, w4
	mov	w0, 0
	bhi	.L234
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w14, w12
.L234:
	orr	w9, w9, w0
	ldrb	w0, [x13, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x28, 36]
	str	w0, [x28, 44]
	bne	.L235
.L236:
	ldrb	w1, [x23, 1]
	add	x0, x26, 280
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L253
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L254
	tbnz	x0, 0, .L370
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L254:
	add	w0, w0, 1
.L256:
	strb	w0, [x23, 1]
	ldr	w0, [x28, 44]
	ldp	w9, w2, [x28, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L259
.L362:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w4, w0, w2
	sub	w4, w4, w11
	mov	w1, w11
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w9, w10, [x29, 132]
	stp	w2, w11, [x29, 140]
	bl	BsGet
	ldr	w4, [x29, 148]
	ldp	w9, w10, [x29, 132]
	and	w4, w4, 7
	ldp	w2, w11, [x29, 140]
	lsl	w0, w0, w4
	orr	w1, w0, w9
	add	w2, w11, w2
	mov	w9, w1
	stp	w1, w2, [x28, 36]
	b	.L259
	.p2align 3
.L198:
	add	x12, x26, 24
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x12, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x28, 44]
	stp	w4, w2, [x28, 36]
.L203:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L371
.L201:
	lsl	w1, w12, 24
	add	x13, x26, 24
	cmp	w1, w4
	mov	w0, 0
	bhi	.L202
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w14, w12
.L202:
	orr	w9, w9, w0
	ldrb	w0, [x13, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x28, 36]
	str	w0, [x28, 44]
	bne	.L203
.L204:
	ldrb	w1, [x25]
	add	x0, x26, 280
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L221
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L222
	tbnz	x0, 0, .L372
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L222:
	add	w0, w0, 1
.L224:
	strb	w0, [x25]
	ldr	w0, [x28, 44]
	ldp	w4, w2, [x28, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L227
.L357:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w9, w0, w2
	sub	w9, w9, w11
	mov	w1, w11
	mov	x0, x28
	str	w9, [x29, 148]
	stp	w4, w10, [x29, 132]
	stp	w2, w11, [x29, 140]
	bl	BsGet
	ldr	w9, [x29, 148]
	ldp	w4, w10, [x29, 132]
	and	w9, w9, 7
	ldp	w2, w11, [x29, 140]
	lsl	w0, w0, w9
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x28, 36]
	b	.L227
	.p2align 3
.L221:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L225
	tbnz	x4, 0, .L373
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L225:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L224
	.p2align 3
.L253:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L257
	tbnz	x4, 0, .L374
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L257:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L256
	.p2align 3
.L285:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L289
	tbnz	x4, 0, .L375
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L289:
	mov	w0, 255
	sub	w0, w0, w4
	strb	w0, [x23, 2]
	b	.L300
	.p2align 3
.L194:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w4, w0, w2
	ldr	w9, [x28, 36]
	sub	w4, w4, w11
	mov	w1, w11
	mov	x0, x28
	stp	w10, w2, [x29, 132]
	stp	w11, w4, [x29, 140]
	str	w9, [x29, 148]
	bl	BsGet
	ldp	w11, w4, [x29, 140]
	ldp	w10, w2, [x29, 132]
	and	w4, w4, 7
	ldr	w9, [x29, 148]
	lsl	w0, w0, w4
	add	w2, w2, w11
	orr	w4, w0, w9
	stp	w4, w2, [x28, 36]
	b	.L195
	.p2align 3
.L367:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w11, w12, [x29, 124]
	stp	w4, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w12, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w4, w10, [x29, 132]
	orr	w12, w0, w12
	b	.L265
	.p2align 3
.L371:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w11, w4, [x29, 124]
	stp	w12, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w4, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 132]
	orr	w4, w0, w4
	b	.L201
	.p2align 3
.L369:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w11, w4, [x29, 124]
	stp	w12, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w4, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 132]
	orr	w4, w0, w4
	b	.L233
	.p2align 3
.L269:
	uxtw	x1, w0
	add	x4, x26, 24
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w4, [x4, x1]
	lsl	w1, w12, w4
	sub	w2, w2, w4
	lsl	w0, w0, w4
	str	w0, [x28, 44]
	stp	w1, w2, [x28, 36]
.L274:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L376
.L272:
	lsl	w1, w4, 24
	add	x13, x26, 24
	cmp	w1, w12
	mov	w0, 0
	bhi	.L273
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w4, w14, w4
.L273:
	orr	w9, w9, w0
	ldrb	w0, [x13, w4, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x28, 36]
	str	w0, [x28, 44]
	bne	.L274
	add	w9, w9, 16
	b	.L268
	.p2align 3
.L205:
	uxtw	x1, w0
	add	x9, x26, 24
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x9, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x28, 44]
	stp	w1, w2, [x28, 36]
.L210:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L377
.L208:
	lsl	w1, w4, 24
	add	x13, x26, 24
	cmp	w1, w9
	mov	w0, 0
	bhi	.L209
	ldr	w14, [x28, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w14, w4
.L209:
	orr	w10, w10, w0
	ldrb	w0, [x13, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x28, 36]
	str	w0, [x28, 44]
	bne	.L210
	add	w9, w10, 16
	b	.L204
	.p2align 3
.L237:
	uxtw	x1, w0
	add	x9, x26, 24
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x9, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x28, 44]
	stp	w1, w2, [x28, 36]
.L242:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L378
.L240:
	lsl	w1, w4, 24
	add	x13, x26, 24
	cmp	w1, w9
	mov	w0, 0
	bhi	.L241
	ldr	w14, [x28, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w14, w4
.L241:
	orr	w10, w10, w0
	ldrb	w0, [x13, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x28, 36]
	str	w0, [x28, 44]
	bne	.L242
	add	w9, w10, 16
	b	.L236
	.p2align 3
.L363:
	sub	w10, w24, w2
	mov	w0, 16
	and	w10, w10, -8
	sub	w9, w0, w2
	sub	w9, w9, w10
	mov	w1, w10
	mov	x0, x28
	str	w9, [x29, 148]
	stp	w4, w12, [x29, 132]
	stp	w2, w10, [x29, 140]
	bl	BsGet
	ldr	w9, [x29, 148]
	ldp	w4, w12, [x29, 132]
	and	w9, w9, 7
	ldp	w2, w10, [x29, 140]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x28, 36]
	b	.L261
	.p2align 3
.L353:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w2
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x28
	str	w10, [x29, 148]
	stp	w4, w9, [x29, 132]
	stp	w2, w11, [x29, 140]
	bl	BsGet
	ldr	w10, [x29, 148]
	ldp	w4, w9, [x29, 132]
	ldp	w2, w11, [x29, 140]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x28, 36]
	b	.L197
	.p2align 3
.L358:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w2
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x28
	str	w10, [x29, 148]
	stp	w9, w4, [x29, 132]
	stp	w2, w11, [x29, 140]
	bl	BsGet
	ldr	w10, [x29, 148]
	ldp	w9, w4, [x29, 132]
	ldp	w2, w11, [x29, 140]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w2, w11
	orr	w4, w0, w4
	stp	w4, w2, [x28, 36]
	b	.L229
	.p2align 3
.L372:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L222
	.p2align 3
.L368:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	add	w0, w0, 1
	b	.L288
	.p2align 3
.L370:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L254
	.p2align 3
.L377:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w12, w9, [x29, 124]
	stp	w4, w11, [x29, 132]
	stp	w10, w13, [x29, 140]
	bl	BsGet
	ldp	w10, w13, [x29, 140]
	ldp	w12, w9, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 132]
	orr	w9, w0, w9
	b	.L208
	.p2align 3
.L378:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w12, w9, [x29, 124]
	stp	w4, w11, [x29, 132]
	stp	w10, w13, [x29, 140]
	bl	BsGet
	ldp	w10, w13, [x29, 140]
	ldp	w12, w9, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 132]
	orr	w9, w0, w9
	b	.L240
	.p2align 3
.L376:
	sub	w1, w24, w2
	mov	w0, 16
	sub	w13, w0, w2
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w2, w1, w2
	mov	x0, x28
	str	w2, [x29, 148]
	stp	w11, w12, [x29, 124]
	stp	w4, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w12, [x29, 124]
	and	w13, w13, 7
	ldr	w2, [x29, 148]
	lsl	w0, w0, w13
	ldp	w4, w10, [x29, 132]
	orr	w12, w0, w12
	b	.L272
	.p2align 3
.L374:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L257
	.p2align 3
.L373:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L225
	.p2align 3
.L375:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L289
.L211:
	uxtw	x1, w0
	add	x10, x26, 24
	mov	w9, 0
	mov	w11, 1
	ldrb	w10, [x10, x1]
	lsl	w1, w4, w10
	lsl	w0, w0, w10
	sub	w4, w2, w10
	str	w0, [x28, 44]
	mov	w10, 4
	stp	w1, w4, [x28, 36]
	.p2align 2
.L215:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L379
.L213:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w12
	mov	w0, 0
	bhi	.L214
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w14, w2
.L214:
	orr	w9, w9, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	bne	.L215
	add	w9, w9, 32
	b	.L204
.L243:
	uxtw	x1, w0
	add	x10, x26, 24
	mov	w9, 0
	mov	w11, 1
	ldrb	w10, [x10, x1]
	lsl	w1, w4, w10
	lsl	w0, w0, w10
	sub	w4, w2, w10
	str	w0, [x28, 44]
	mov	w10, 4
	stp	w1, w4, [x28, 36]
	.p2align 2
.L247:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L380
.L245:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w12
	mov	w0, 0
	bhi	.L246
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w14, w2
.L246:
	orr	w9, w9, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	bne	.L247
	add	w9, w9, 32
	b	.L236
.L275:
	uxtw	x1, w0
	add	x4, x26, 24
	mov	w9, 0
	mov	w11, 1
	ldrb	w10, [x4, x1]
	lsl	w1, w12, w10
	sub	w4, w2, w10
	lsl	w0, w0, w10
	mov	w10, 4
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	.p2align 2
.L279:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L381
.L277:
	lsl	w1, w2, 24
	add	x13, x26, 24
	cmp	w1, w12
	mov	w0, 0
	bhi	.L278
	ldr	w14, [x28, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w14, w2
.L278:
	orr	w9, w9, w0
	ldrb	w0, [x13, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x28, 36]
	str	w0, [x28, 44]
	bne	.L279
	add	w9, w9, 32
	b	.L268
	.p2align 3
.L381:
	sub	w1, w24, w4
	mov	w0, 16
	sub	w13, w0, w4
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w12, [x29, 124]
	stp	w2, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w12, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 132]
	orr	w12, w0, w12
	b	.L277
	.p2align 3
.L380:
	sub	w1, w24, w4
	mov	w0, 16
	sub	w13, w0, w4
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w12, [x29, 124]
	stp	w2, w9, [x29, 132]
	stp	w10, w13, [x29, 140]
	bl	BsGet
	ldp	w10, w13, [x29, 140]
	ldp	w11, w12, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 132]
	orr	w12, w0, w12
	b	.L245
	.p2align 3
.L379:
	sub	w1, w24, w4
	mov	w0, 16
	sub	w13, w0, w4
	and	w1, w1, -8
	sub	w13, w13, w1
	add	w4, w1, w4
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w12, [x29, 124]
	stp	w2, w10, [x29, 132]
	stp	w9, w13, [x29, 140]
	bl	BsGet
	ldp	w9, w13, [x29, 140]
	ldp	w11, w12, [x29, 124]
	and	w13, w13, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 132]
	orr	w12, w0, w12
	b	.L213
	.p2align 3
.L364:
	sub	w10, w24, w2
	mov	w0, 16
	and	w10, w10, -8
	sub	w9, w0, w2
	sub	w9, w9, w10
	mov	w1, w10
	mov	x0, x28
	str	w10, [x29, 148]
	stp	w4, w12, [x29, 132]
	stp	w2, w9, [x29, 140]
	bl	BsGet
	ldp	w2, w9, [x29, 140]
	ldp	w4, w12, [x29, 132]
	and	w9, w9, 7
	ldr	w10, [x29, 148]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x28, 36]
	b	.L264
	.p2align 3
.L359:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w9, w0, w2
	sub	w9, w9, w11
	mov	w1, w11
	mov	x0, x28
	str	w11, [x29, 148]
	stp	w10, w4, [x29, 132]
	stp	w2, w9, [x29, 140]
	bl	BsGet
	ldp	w2, w9, [x29, 140]
	ldp	w10, w4, [x29, 132]
	ldr	w11, [x29, 148]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x28, 36]
	b	.L232
	.p2align 3
.L354:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w9, w0, w2
	sub	w9, w9, w11
	mov	w1, w11
	mov	x0, x28
	str	w11, [x29, 148]
	stp	w4, w10, [x29, 132]
	stp	w2, w9, [x29, 140]
	bl	BsGet
	ldp	w2, w9, [x29, 140]
	ldp	w4, w10, [x29, 132]
	ldr	w11, [x29, 148]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x28, 36]
	b	.L200
.L356:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L382
	add	w9, w9, 64
	b	.L204
.L366:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L383
	add	w9, w9, 64
	b	.L268
.L361:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L384
	add	w9, w9, 64
	b	.L236
.L384:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w10, w10, #65
	add	w2, w2, 1
	mov	w11, w1
	tbnz	w4, #31, .L385
.L251:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w11
	bhi	.L252
	ldr	w0, [x28, 44]
	sub	w11, w11, w1
	sub	w2, w0, w2
	mov	w0, 1
.L252:
	add	w9, w10, w0
	add	x0, x26, 24
	add	w9, w9, 64
	ldrb	w1, [x0, w2, uxtw]
	lsl	w0, w11, w1
	lsl	w2, w2, w1
	str	w0, [x28, 36]
	sub	w0, w4, w1
	str	w2, [x28, 44]
	str	w0, [x28, 40]
	b	.L236
.L383:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w10, w10, #65
	add	w2, w2, 1
	mov	w11, w1
	tbnz	w4, #31, .L386
.L283:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w11
	bhi	.L284
	ldr	w0, [x28, 44]
	sub	w11, w11, w1
	sub	w2, w0, w2
	mov	w0, 1
.L284:
	add	w9, w10, w0
	add	x0, x26, 24
	add	w9, w9, 64
	ldrb	w1, [x0, w2, uxtw]
	lsl	w0, w11, w1
	lsl	w2, w2, w1
	str	w0, [x28, 36]
	sub	w0, w4, w1
	str	w2, [x28, 44]
	str	w0, [x28, 40]
	b	.L268
.L382:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w10, w10, #65
	add	w2, w2, 1
	mov	w11, w1
	tbnz	w4, #31, .L387
.L219:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w11
	bhi	.L220
	ldr	w0, [x28, 44]
	sub	w11, w11, w1
	sub	w2, w0, w2
	mov	w0, 1
.L220:
	add	w9, w10, w0
	add	x0, x26, 24
	add	w9, w9, 64
	ldrb	w10, [x0, w2, uxtw]
	lsl	w1, w11, w10
	sub	w0, w4, w10
	lsl	w2, w2, w10
	str	w2, [x28, 44]
	stp	w1, w0, [x28, 36]
	b	.L204
.L365:
	sub	w10, w24, w2
	mov	w0, 16
	and	w10, w10, -8
	sub	w9, w0, w2
	sub	w9, w9, w10
	mov	w1, w10
	mov	x0, x28
	str	w10, [x29, 148]
	stp	w4, w12, [x29, 132]
	stp	w2, w9, [x29, 140]
	bl	BsGet
	ldp	w2, w9, [x29, 140]
	ldp	w4, w12, [x29, 132]
	and	w9, w9, 7
	ldr	w10, [x29, 148]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x28, 36]
	b	.L271
.L360:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w2
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x28
	str	w11, [x29, 148]
	stp	w9, w4, [x29, 132]
	stp	w2, w10, [x29, 140]
	bl	BsGet
	ldp	w2, w10, [x29, 140]
	ldp	w9, w4, [x29, 132]
	and	w10, w10, 7
	ldr	w11, [x29, 148]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x28, 36]
	b	.L239
.L355:
	sub	w11, w24, w2
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w2
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x28
	str	w11, [x29, 148]
	stp	w4, w9, [x29, 132]
	stp	w2, w10, [x29, 140]
	bl	BsGet
	ldp	w2, w10, [x29, 140]
	ldp	w4, w9, [x29, 132]
	and	w10, w10, 7
	ldr	w11, [x29, 148]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x28, 36]
	b	.L207
.L192:
	ldr	x1, .LC19
	uxtw	x2, w20
	add	x1, x1, 24
	ldrb	w2, [x1, x2]
	sub	w1, w21, w2
	lsl	w0, w0, w2
	lsl	w2, w20, w2
	str	w2, [x28, 44]
	stp	w0, w1, [x28, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L190:
	mov	w23, 24
	mov	w24, 16
	sub	w23, w23, w21
	sub	w24, w24, w21
	and	w23, w23, -8
	mov	x0, x28
	mov	w1, w23
	sub	w24, w24, w23
	ldr	w19, [x28, 36]
	and	w24, w24, 7
	bl	BsGet
	lsl	w0, w0, w24
	add	w1, w21, w23
	orr	w0, w0, w19
	mov	w21, w1
	stp	w0, w1, [x28, 36]
	b	.L191
.L387:
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w9, w0, w4
	sub	w9, w9, w1
	add	w4, w4, w1
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w2, [x29, 132]
	stp	w10, w9, [x29, 140]
	bl	BsGet
	ldp	w10, w9, [x29, 140]
	ldp	w11, w2, [x29, 132]
	and	w9, w9, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w9
	orr	w11, w0, w11
	b	.L219
.L386:
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w9, w0, w4
	sub	w9, w9, w1
	add	w4, w4, w1
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w2, [x29, 132]
	stp	w10, w9, [x29, 140]
	bl	BsGet
	ldp	w10, w9, [x29, 140]
	ldp	w11, w2, [x29, 132]
	and	w9, w9, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w9
	orr	w11, w0, w11
	b	.L283
.L385:
	sub	w1, w24, w4
	mov	w0, 16
	and	w1, w1, -8
	sub	w9, w0, w4
	sub	w9, w9, w1
	add	w4, w4, w1
	mov	x0, x28
	str	w4, [x29, 148]
	stp	w11, w2, [x29, 132]
	stp	w10, w9, [x29, 140]
	bl	BsGet
	ldp	w10, w9, [x29, 140]
	ldp	w11, w2, [x29, 132]
	and	w9, w9, 7
	ldr	w4, [x29, 148]
	lsl	w0, w0, w9
	orr	w11, w0, w11
	b	.L251
	.size	Vp9_ReadCoefProbsCommon, .-Vp9_ReadCoefProbsCommon
	.align	3
.LC19:
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
	cbnz	w21, .L394
.L388:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L394:
	mov	x1, x20
	add	x0, x19, 432
	bl	Vp9_ReadCoefProbsCommon
	cmp	w21, 1
	bls	.L390
	mov	x1, x20
	add	x0, x19, 864
	bl	Vp9_ReadCoefProbsCommon
.L390:
	cmp	w21, 2
	bls	.L388
	mov	x1, x20
	add	x0, x19, 1296
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
	mov	x19, x1
	add	x26, x21, 1960
	bl	_mcount
	ldr	x25, .LC22
	add	x21, x21, 1981
	mov	w23, 24
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
	.p2align 2
.L487:
	ldp	w2, w1, [x19, 40]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w1, w0, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L396
	ldr	w28, [x19, 36]
.L397:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L398
	ldr	w1, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x3, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L539
.L399:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L400
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x3, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L540
.L402:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L407
	ldr	w20, [x19, 44]
	sub	w1, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w1, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L541
.L409:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L413
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w1, w28, w1
	mov	w4, 6
	sub	w0, w20, w0
	mov	w28, 0
	ldrb	w20, [x3, w0, uxtw]
	lsl	w1, w1, w20
	sub	w3, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w3, [x19, 36]
	b	.L414
	.p2align 3
.L418:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L419
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L419:
	orr	w28, w28, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L542
.L414:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L418
	sub	w1, w23, w3
	sub	w5, w22, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L418
	.p2align 3
.L398:
	uxtw	x0, w20
	add	x1, x25, 24
	ldrb	w1, [x1, x0]
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
	tbnz	w2, #31, .L543
.L427:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L428
	ldr	w1, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x3, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L544
.L429:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L430
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x3, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L545
.L432:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L437
	ldr	w20, [x19, 44]
	sub	w1, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w1, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L546
.L439:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L443
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w1, w28, w1
	mov	w4, 6
	sub	w0, w20, w0
	mov	w28, 0
	ldrb	w20, [x3, w0, uxtw]
	lsl	w1, w1, w20
	sub	w3, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w3, [x19, 36]
	b	.L444
	.p2align 3
.L448:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L449
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L449:
	orr	w28, w28, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L547
.L444:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L448
	sub	w1, w23, w3
	sub	w5, w22, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L448
	.p2align 3
.L428:
	uxtw	x0, w20
	add	x1, x25, 24
	ldrb	w1, [x1, x0]
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
	tbnz	w2, #31, .L548
.L457:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L458
	ldr	w1, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x3, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L549
.L459:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L460
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x3, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L550
.L462:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L467
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L551
.L469:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L473
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w1, w28, w1
	mov	w4, 6
	sub	w0, w20, w0
	mov	w28, 0
	ldrb	w20, [x3, w0, uxtw]
	lsl	w1, w1, w20
	sub	w3, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w3, [x19, 36]
	b	.L474
	.p2align 3
.L478:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L479
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L479:
	orr	w28, w28, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L552
.L474:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L478
	sub	w1, w23, w3
	sub	w5, w22, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L478
	.p2align 3
.L458:
	add	x1, x25, 24
	uxtw	x0, w20
	ldrb	w1, [x1, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	stp	w28, w2, [x19, 36]
.L490:
	add	x26, x26, 3
	cmp	x26, x21
	bne	.L487
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L460:
	add	x3, x25, 24
	uxtw	x0, w1
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L465:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L553
.L463:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L464
	ldr	w6, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w6, w20
.L464:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L465
.L466:
	ldrb	w0, [x26]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w3, w0, 1
	ldrb	w2, [x1, w4, sxtw]
	cmp	w3, 255
	bgt	.L481
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L482
	tbnz	x1, 0, .L554
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L482:
	add	w1, w1, 1
.L484:
	strb	w1, [x26]
	b	.L490
	.p2align 3
.L430:
	add	x3, x25, 24
	uxtw	x0, w1
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L435:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L555
.L433:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L434
	ldr	w6, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w6, w20
.L434:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L435
.L436:
	ldrb	w0, [x26, -1]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w3, w0, 1
	ldrb	w2, [x1, w4, sxtw]
	cmp	w3, 255
	bgt	.L451
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L452
	tbnz	x1, 0, .L556
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L452:
	add	w1, w1, 1
.L454:
	strb	w1, [x26, -1]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L457
.L548:
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
	b	.L457
	.p2align 3
.L400:
	add	x3, x25, 24
	uxtw	x0, w1
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L405:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L557
.L403:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L404
	ldr	w6, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w6, w20
.L404:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L405
.L406:
	ldrb	w0, [x26, -2]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w3, w0, 1
	ldrb	w2, [x1, w4, sxtw]
	cmp	w3, 255
	bgt	.L421
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L422
	tbnz	x1, 0, .L558
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L422:
	add	w1, w1, 1
.L424:
	strb	w1, [x26, -2]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L427
.L543:
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
	b	.L427
	.p2align 3
.L481:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L485
	tbnz	x1, 0, .L559
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L485:
	mov	w0, 255
	sub	w1, w0, w1
.L565:
	strb	w1, [x26]
	b	.L490
	.p2align 3
.L421:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L425
	tbnz	x1, 0, .L560
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L425:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L424
	.p2align 3
.L451:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L455
	tbnz	x1, 0, .L561
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L455:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L454
	.p2align 3
.L396:
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
	b	.L397
	.p2align 3
.L553:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L463
	.p2align 3
.L557:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L403
	.p2align 3
.L555:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L433
	.p2align 3
.L554:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L484
	.p2align 3
.L558:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L422
	.p2align 3
.L556:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L452
	.p2align 3
.L467:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L472:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L562
.L470:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L471
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L471:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L472
	add	w4, w4, 16
	b	.L466
	.p2align 3
.L437:
	uxtw	x1, w0
	add	x3, x25, 24
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
.L442:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L563
.L440:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L441
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L441:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L442
	add	w4, w4, 16
	b	.L436
	.p2align 3
.L407:
	uxtw	x1, w0
	add	x3, x25, 24
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
.L412:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L564
.L410:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L411
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L411:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L412
	add	w4, w4, 16
	b	.L406
	.p2align 3
.L544:
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
	b	.L429
	.p2align 3
.L549:
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
	b	.L459
	.p2align 3
.L539:
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
	b	.L399
	.p2align 3
.L562:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w4, w5, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w4, w5, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L470
	.p2align 3
.L564:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L410
	.p2align 3
.L563:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w4, w5, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w4, w5, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L440
	.p2align 3
.L559:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L565
	.p2align 3
.L560:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L424
	.p2align 3
.L561:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L454
.L443:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w20, [x3, x1]
	mov	w3, 4
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
	.p2align 2
.L447:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L566
.L445:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L446
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L446:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L447
	add	w4, w4, 32
	b	.L436
.L413:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w20, [x3, x1]
	mov	w3, 4
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
	.p2align 2
.L417:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L567
.L415:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L416
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L416:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L417
	add	w4, w4, 32
	b	.L406
.L473:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w20, [x3, x1]
	mov	w3, 4
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L477:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L568
.L475:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L476
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L476:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L477
	add	w4, w4, 32
	b	.L466
	.p2align 3
.L568:
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
	b	.L475
	.p2align 3
.L567:
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
	b	.L415
	.p2align 3
.L566:
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
	b	.L445
	.p2align 3
.L540:
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
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L402
	.p2align 3
.L550:
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
	b	.L462
	.p2align 3
.L545:
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
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L432
.L542:
	cmp	w28, 64
	mov	w20, w28
	bgt	.L569
	add	w4, w20, 64
	b	.L406
.L547:
	cmp	w28, 64
	mov	w20, w28
	bgt	.L570
	add	w4, w20, 64
	b	.L436
.L552:
	cmp	w28, 64
	mov	w20, w28
	bgt	.L571
	add	w4, w20, 64
	b	.L466
.L571:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L466
.L570:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L436
.L569:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L406
.L541:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w3, w2
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L409
.L551:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w3, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L469
.L546:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w3, w2
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L439
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	3
.LC22:
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
	mov	x19, x1
	add	x26, x21, 1951
	bl	_mcount
	ldr	x25, .LC25
	add	x21, x21, 1959
	mov	w23, 24
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
.L634:
	ldp	w2, w0, [x19, 40]
	sub	w20, w0, #1
	lsl	w0, w20, 6
	sub	w0, w0, w20
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w2, #31, .L573
	ldr	w28, [x19, 36]
.L574:
	lsl	w1, w20, 24
	cmp	w1, w28
	bhi	.L575
	ldr	w0, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w1
	sub	w0, w0, w20
	ldrb	w20, [x3, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L670
.L576:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L577
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L671
.L579:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L584
	ldr	w20, [x19, 44]
	sub	w1, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w1, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L672
.L586:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L590
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w1, w28, w1
	mov	w4, 6
	sub	w0, w20, w0
	mov	w28, 0
	ldrb	w20, [x3, w0, uxtw]
	lsl	w1, w1, w20
	sub	w3, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w3, [x19, 36]
	b	.L591
	.p2align 3
.L595:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L596
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L596:
	orr	w28, w28, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L673
.L591:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L595
	sub	w1, w23, w3
	sub	w5, w22, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L595
	.p2align 3
.L575:
	uxtw	x0, w20
	add	x1, x25, 24
	ldrb	w0, [x1, x0]
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
	tbnz	w2, #31, .L674
.L604:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L605
	ldr	w1, [x19, 44]
	add	x3, x25, 24
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x3, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L675
.L606:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L607
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	add	x0, x25, 24
	sub	w20, w20, w1
	ldrb	w1, [x0, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L676
.L609:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L614
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L677
.L616:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L620
	ldr	w20, [x19, 44]
	add	x3, x25, 24
	sub	w1, w28, w1
	mov	w4, 6
	sub	w0, w20, w0
	mov	w28, 0
	ldrb	w20, [x3, w0, uxtw]
	lsl	w1, w1, w20
	sub	w3, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w3, [x19, 36]
	b	.L621
	.p2align 3
.L625:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w2
	mov	w0, 0
	bhi	.L626
	ldr	w0, [x19, 44]
	sub	w2, w2, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L626:
	orr	w28, w28, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w4, w4, #1
	lsl	w1, w2, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w1, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L678
.L621:
	sub	w20, w20, #1
	mov	w2, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L625
	sub	w1, w23, w3
	sub	w5, w22, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w2, w4, [x29, 96]
	stp	w5, w3, [x29, 104]
	bl	BsGet
	ldp	w5, w3, [x29, 104]
	ldp	w2, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w2, w0, w2
	b	.L625
	.p2align 3
.L605:
	add	x1, x25, 24
	uxtw	x0, w20
	ldrb	w0, [x1, x0]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w28, w2, [x19, 36]
.L636:
	add	x26, x26, 2
	cmp	x26, x21
	bne	.L634
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L607:
	add	x3, x25, 24
	uxtw	x0, w1
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L612:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L679
.L610:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L611
	ldr	w6, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w6, w20
.L611:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L612
.L613:
	ldrb	w0, [x26]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w3, w0, 1
	ldrb	w2, [x1, w4, sxtw]
	cmp	w3, 255
	bgt	.L628
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L629
	tbnz	x1, 0, .L680
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L629:
	add	w1, w1, 1
.L631:
	strb	w1, [x26]
	b	.L636
	.p2align 3
.L577:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L582:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L681
.L580:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L581
	ldr	w6, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w6, w20
.L581:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L582
.L583:
	ldrb	w0, [x26, -1]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w3, w0, 1
	ldrb	w2, [x1, w4, sxtw]
	cmp	w3, 255
	bgt	.L598
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L599
	tbnz	x1, 0, .L682
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L599:
	add	w1, w1, 1
.L601:
	strb	w1, [x26, -1]
	ldr	w0, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w2, #31, .L604
.L674:
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
	b	.L604
	.p2align 3
.L598:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L683
	mov	w0, 255
	sub	w1, w0, w1
	b	.L601
	.p2align 3
.L628:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L684
	mov	w0, 255
	sub	w1, w0, w1
.L686:
	strb	w1, [x26]
	b	.L636
	.p2align 3
.L573:
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
	b	.L574
	.p2align 3
.L684:
	tbnz	x1, 0, .L685
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L686
	.p2align 3
.L683:
	tbnz	x1, 0, .L687
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L601
	.p2align 3
.L614:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L619:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L688
.L617:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L618
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L618:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L619
	add	w4, w4, 16
	b	.L613
	.p2align 3
.L584:
	uxtw	x1, w0
	add	x3, x25, 24
	mov	w4, 0
	mov	w5, 3
	ldrb	w20, [x3, x1]
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
.L589:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L689
.L587:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L588
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L588:
	orr	w4, w4, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L589
	add	w4, w4, 16
	b	.L583
	.p2align 3
.L681:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L580
	.p2align 3
.L679:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L610
	.p2align 3
.L687:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L601
	.p2align 3
.L685:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L686
	.p2align 3
.L670:
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
	b	.L576
	.p2align 3
.L675:
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
	b	.L606
	.p2align 3
.L680:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L631
	.p2align 3
.L682:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L599
	.p2align 3
.L689:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L587
	.p2align 3
.L688:
	sub	w1, w23, w2
	sub	w3, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w3, w3, w1
	add	w2, w1, w2
	stp	w5, w4, [x29, 96]
	stp	w3, w2, [x29, 104]
	bl	BsGet
	ldp	w3, w2, [x29, 104]
	ldp	w5, w4, [x29, 96]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w28, w0, w28
	b	.L617
.L620:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w20, [x3, x1]
	mov	w3, 4
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L624:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L690
.L622:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L623
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L623:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L624
	add	w4, w4, 32
	b	.L613
.L590:
	add	x3, x25, 24
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w20, [x3, x1]
	mov	w3, 4
	lsl	w1, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w1, w2, [x19, 36]
	.p2align 2
.L594:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L691
.L592:
	lsl	w1, w20, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L593
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L593:
	orr	w4, w4, w0
	ldrb	w0, [x5, w20, uxtw]
	sub	w3, w3, #1
	lsl	w1, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w1, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L594
	add	w4, w4, 32
	b	.L583
.L677:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w3, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L616
.L672:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w2, w3
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L586
	.p2align 3
.L690:
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
	b	.L622
	.p2align 3
.L691:
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
	b	.L592
	.p2align 3
.L671:
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
	orr	w1, w0, w28
	mov	w28, w1
	stp	w1, w2, [x19, 36]
	b	.L579
	.p2align 3
.L676:
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
	b	.L609
.L678:
	cmp	w28, 64
	mov	w20, w28
	bgt	.L692
	add	w4, w20, 64
	b	.L613
.L692:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L613
.L673:
	cmp	w28, 64
	mov	w20, w28
	bgt	.L693
	add	w4, w20, 64
	b	.L583
.L693:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w28, lsl 1
	sub	w20, w0, #65
	add	w4, w20, 64
	b	.L583
	.size	Vp9_ReadSwitchableInterpProbs, .-Vp9_ReadSwitchableInterpProbs
	.align	3
.LC25:
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
	cbnz	w19, .L860
	ldr	x25, .LC28
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
	str	wzr, [x29, 124]
.L705:
	sub	w0, w0, #1
	add	x23, x21, 1989
	lsl	w28, w0, 6
	add	x22, x21, 1999
	sub	w0, w28, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w27, 1
	add	w28, w0, 1
	tbnz	w19, #31, .L861
	.p2align 2
.L707:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L708
	ldr	w0, [x20, 44]
	add	x6, x25, 24
	sub	w5, w26, w1
	sub	w0, w0, w28
	ldrb	w28, [x6, w0, uxtw]
	lsl	w26, w5, w28
	sub	w19, w19, w28
	lsl	w28, w0, w28
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L862
.L709:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L710
	ldr	w28, [x20, 44]
	sub	w1, w26, w1
	sub	w28, w28, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w28, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L863
.L712:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L717
	ldr	w5, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w5, w0
	add	x5, x25, 24
	ldrb	w6, [x5, w0, uxtw]
	sub	w26, w19, w6
	lsl	w28, w1, w6
	lsl	w19, w0, w6
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L864
.L719:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L723
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w6, [x1, w0, uxtw]
	sub	w7, w26, w6
	lsl	w1, w5, w6
	lsl	w0, w0, w6
	mov	w26, 6
	stp	w1, w7, [x20, 36]
	str	w0, [x20, 44]
	b	.L724
	.p2align 3
.L728:
	lsl	w1, w28, 24
	add	x8, x25, 24
	cmp	w1, w5
	mov	w0, 0
	bhi	.L729
	ldr	w0, [x20, 44]
	sub	w5, w5, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L729:
	orr	w19, w19, w0
	ldrb	w0, [x8, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w5, w0
	sub	w7, w7, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w7, [x20, 36]
	str	w0, [x20, 44]
	beq	.L865
.L724:
	sub	w0, w0, #1
	mov	w5, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w7, #31, .L728
	sub	w1, w24, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w7
	sub	w8, w8, w1
	add	w7, w1, w7
	mov	x0, x20
	str	w7, [x29, 120]
	stp	w5, w8, [x29, 104]
	bl	BsGet
	ldp	w5, w8, [x29, 104]
	ldr	w7, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L728
	.p2align 3
.L708:
	uxtw	x0, w28
	add	x1, x25, 24
	ldrb	w0, [x1, x0]
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
	tbnz	w19, #31, .L866
.L737:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L738
	ldr	w0, [x20, 44]
	add	x6, x25, 24
	sub	w1, w26, w1
	sub	w0, w0, w28
	ldrb	w6, [x6, w0, uxtw]
	lsl	w26, w1, w6
	sub	w19, w19, w6
	lsl	w28, w0, w6
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L867
.L739:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L740
	sub	w28, w26, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w1, [x1, w0, uxtw]
	sub	w26, w19, w1
	lsl	w28, w28, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L868
.L742:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L747
	ldr	w6, [x20, 44]
	sub	w1, w28, w1
	sub	w0, w6, w0
	add	x6, x25, 24
	ldrb	w6, [x6, w0, uxtw]
	lsl	w28, w1, w6
	sub	w26, w26, w6
	lsl	w19, w0, w6
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L869
.L749:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L753
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w6, [x1, w0, uxtw]
	sub	w7, w26, w6
	lsl	w1, w5, w6
	lsl	w0, w0, w6
	mov	w26, 6
	stp	w1, w7, [x20, 36]
	str	w0, [x20, 44]
	b	.L754
	.p2align 3
.L758:
	lsl	w1, w28, 24
	add	x8, x25, 24
	cmp	w1, w5
	mov	w0, 0
	bhi	.L759
	ldr	w0, [x20, 44]
	sub	w5, w5, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L759:
	orr	w19, w19, w0
	ldrb	w0, [x8, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w5, w0
	sub	w7, w7, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w7, [x20, 36]
	str	w0, [x20, 44]
	beq	.L870
.L754:
	sub	w0, w0, #1
	mov	w5, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w7, #31, .L758
	sub	w1, w24, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w7
	sub	w8, w8, w1
	add	w7, w1, w7
	mov	x0, x20
	str	w7, [x29, 120]
	stp	w5, w8, [x29, 104]
	bl	BsGet
	ldp	w5, w8, [x29, 104]
	ldr	w7, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L758
	.p2align 3
.L738:
	add	x1, x25, 24
	uxtw	x0, w28
	add	x23, x23, 2
	cmp	x23, x22
	ldrb	w0, [x1, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w28, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
	beq	.L767
.L875:
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L707
.L861:
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
	b	.L707
	.p2align 3
.L710:
	add	x6, x25, 24
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w28, [x6, x1]
	lsl	w5, w26, w28
	sub	w19, w19, w28
	mov	w26, 3
	lsl	w28, w0, w28
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
.L715:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w19, #31, .L871
.L713:
	lsl	w1, w28, 24
	add	x6, x25, 24
	cmp	w1, w5
	mov	w0, 0
	bhi	.L714
	ldr	w9, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w28, w9, w28
.L714:
	orr	w7, w7, w0
	ldrb	w0, [x6, w28, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
	bne	.L715
.L716:
	ldrb	w0, [x23, -1]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w6, w0, 1
	ldrb	w5, [x1, w7, sxtw]
	cmp	w6, 255
	bgt	.L731
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L732
	tbnz	x1, 0, .L872
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L732:
	add	w1, w1, 1
.L734:
	strb	w1, [x23, -1]
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L737
.L866:
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
	b	.L737
	.p2align 3
.L740:
	add	x5, x25, 24
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w6, [x5, x1]
	lsl	w28, w26, w6
	sub	w5, w19, w6
	mov	w26, 3
	lsl	w19, w0, w6
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
.L745:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L873
.L743:
	lsl	w1, w19, 24
	add	x6, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L744
	ldr	w9, [x20, 44]
	lsl	w0, w27, w26
	sub	w28, w28, w1
	sub	w19, w9, w19
.L744:
	orr	w7, w7, w0
	ldrb	w0, [x6, w19, uxtw]
	sub	w26, w26, #1
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L745
.L746:
	ldrb	w0, [x23]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w6, w0, 1
	ldrb	w5, [x1, w7, sxtw]
	cmp	w6, 255
	bgt	.L761
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L762
	tbnz	x1, 0, .L874
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L762:
	add	w1, w1, 1
.L764:
	strb	w1, [x23]
.L878:
	add	x23, x23, 2
	cmp	x23, x22
	bne	.L875
.L767:
	ldr	w0, [x29, 124]
	cbnz	w0, .L876
.L769:
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
.L761:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L877
	mov	w0, 255
	sub	w1, w0, w1
.L887:
	strb	w1, [x23]
	b	.L878
	.p2align 3
.L731:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L879
	mov	w0, 255
	sub	w1, w0, w1
	b	.L734
	.p2align 3
.L876:
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
.L706:
	sub	w0, w0, #1
	add	x28, x21, 1998
	lsl	w1, w0, 6
	add	x21, x21, 2003
	sub	w0, w1, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w23, 16
	mov	w27, 1
	add	w22, w0, 1
	tbnz	w19, #31, .L880
	.p2align 2
.L770:
	lsl	w1, w22, 24
	cmp	w1, w26
	bhi	.L771
	ldr	w0, [x20, 44]
	add	x4, x25, 24
	sub	w5, w26, w1
	sub	w0, w0, w22
	ldrb	w22, [x4, w0, uxtw]
	lsl	w26, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L881
.L772:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w0, w22, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L773
	ldr	w22, [x20, 44]
	sub	w1, w26, w1
	sub	w22, w22, w0
	add	x0, x25, 24
	ldrb	w0, [x0, w22, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L882
.L775:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L780
	ldr	w4, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w4, w0
	add	x4, x25, 24
	ldrb	w6, [x4, w0, uxtw]
	sub	w26, w19, w6
	lsl	w22, w1, w6
	lsl	w19, w0, w6
	str	w19, [x20, 44]
	stp	w22, w26, [x20, 36]
	tbnz	w26, #31, .L883
.L782:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L786
	sub	w5, w22, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w6, [x1, w0, uxtw]
	lsl	w1, w5, w6
	lsl	w0, w0, w6
	sub	w5, w26, w6
	str	w0, [x20, 44]
	mov	w26, 6
	stp	w1, w5, [x20, 36]
	b	.L787
	.p2align 3
.L791:
	lsl	w1, w22, 24
	add	x7, x25, 24
	cmp	w1, w4
	mov	w0, 0
	bhi	.L792
	ldr	w0, [x20, 44]
	sub	w4, w4, w1
	sub	w22, w0, w22
	lsl	w0, w27, w26
.L792:
	orr	w19, w19, w0
	ldrb	w0, [x7, w22, uxtw]
	sub	w26, w26, #1
	lsl	w1, w4, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w22, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	beq	.L884
.L787:
	sub	w0, w0, #1
	mov	w4, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w5, #31, .L791
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
	orr	w4, w0, w4
	b	.L791
	.p2align 3
.L879:
	tbnz	x1, 0, .L885
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L734
	.p2align 3
.L877:
	tbnz	x1, 0, .L886
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L887
	.p2align 3
.L717:
	uxtw	x1, w0
	add	x6, x25, 24
	mov	w7, 0
	ldrb	w6, [x6, x1]
	lsl	w1, w26, w6
	sub	w5, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
.L722:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L888
.L720:
	lsl	w1, w28, 24
	add	x6, x25, 24
	cmp	w1, w19
	mov	w0, 0
	bhi	.L721
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L721:
	orr	w7, w7, w0
	ldrb	w0, [x6, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L722
	add	w7, w7, 16
	b	.L716
	.p2align 3
.L747:
	uxtw	x1, w0
	add	x6, x25, 24
	mov	w7, 0
	ldrb	w6, [x6, x1]
	sub	w5, w26, w6
	lsl	w1, w28, w6
	lsl	w0, w0, w6
	mov	w26, 3
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
.L752:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L889
.L750:
	lsl	w1, w28, 24
	add	x6, x25, 24
	cmp	w1, w19
	mov	w0, 0
	bhi	.L751
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L751:
	orr	w7, w7, w0
	ldrb	w0, [x6, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L752
	add	w7, w7, 16
	b	.L746
	.p2align 3
.L771:
	add	x1, x25, 24
	uxtw	x0, w22
	ldrb	w0, [x1, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
.L804:
	add	x28, x28, 1
	cmp	x28, x21
	beq	.L769
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbz	w19, #31, .L770
.L880:
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
	b	.L770
	.p2align 3
.L773:
	add	x4, x25, 24
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w22, [x4, x1]
	lsl	w5, w26, w22
	sub	w19, w19, w22
	mov	w26, 3
	lsl	w22, w0, w22
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
.L778:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w19, #31, .L890
.L776:
	lsl	w1, w22, 24
	add	x4, x25, 24
	cmp	w1, w5
	mov	w0, 0
	bhi	.L777
	ldr	w8, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w22, w8, w22
.L777:
	orr	w6, w6, w0
	ldrb	w0, [x4, w22, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
	bne	.L778
.L779:
	ldrb	w0, [x28]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w5, w0, 1
	ldrb	w4, [x1, w6, sxtw]
	cmp	w5, 255
	bgt	.L794
	add	w1, w4, 1
	cmp	w1, w5
	bgt	.L795
	tbnz	x1, 0, .L891
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L795:
	add	w1, w1, 1
.L797:
	strb	w1, [x28]
	b	.L804
	.p2align 3
.L794:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w4, 1
	cmp	w1, w0, lsl 1
	bgt	.L798
	tbnz	x1, 0, .L892
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L798:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x28]
	b	.L804
	.p2align 3
.L873:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w5
	sub	w6, w6, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w7, w6, [x29, 104]
	bl	BsGet
	ldp	w7, w6, [x29, 104]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w28, w0, w28
	b	.L743
	.p2align 3
.L871:
	sub	w1, w24, w19
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w19
	sub	w6, w6, w1
	mov	x0, x20
	stp	w5, w7, [x29, 104]
	str	w6, [x29, 120]
	add	w19, w1, w19
	bl	BsGet
	ldr	w6, [x29, 120]
	ldp	w5, w7, [x29, 104]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w5, w0, w5
	b	.L713
	.p2align 3
.L890:
	sub	w1, w24, w19
	sub	w4, w23, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w4, w4, w1
	add	w19, w1, w19
	stp	w5, w6, [x29, 104]
	str	w4, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 120]
	ldp	w5, w6, [x29, 104]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w5, w0, w5
	b	.L776
	.p2align 3
.L860:
	ldp	w19, w0, [x20, 40]
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w19, #31, .L696
	ldr	w5, [x20, 36]
.L697:
	lsl	w23, w22, 24
	cmp	w23, w5
	bhi	.L698
	ldr	w0, [x20, 44]
	sub	w5, w5, w23
	ldr	x25, .LC28
	sub	w0, w0, w22
	add	x1, x25, 24
	ldrb	w22, [x1, w0, uxtw]
	lsl	w5, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w5, w19, [x20, 36]
	mov	w23, w5
	tbnz	w19, #31, .L893
.L699:
	sub	w0, w22, #1
	mov	w1, 1
	ubfx	x0, x0, 1, 24
	str	w1, [x29, 124]
	add	w0, w0, w1
	lsl	w1, w0, 24
	cmp	w1, w23
	bhi	.L700
	ldr	w3, [x20, 44]
	sub	w23, w23, w1
	mov	w1, 2
	str	w1, [x29, 124]
	sub	w0, w3, w0
.L700:
	add	x1, x25, 24
	ldr	w2, [x29, 124]
	cmp	w2, 2
	ldrb	w1, [x1, w0, uxtw]
	lsl	w26, w23, w1
	sub	w19, w19, w1
	lsl	w0, w0, w1
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	bne	.L701
	add	x28, x21, 1983
	add	x22, x21, 1988
	mov	w24, 24
	mov	w23, 16
	b	.L704
	.p2align 3
.L895:
	ldr	w3, [x20, 44]
	sub	w27, w3, w27
	ldrb	w3, [x6, w27, uxtw]
	sub	w19, w19, w3
	lsl	w4, w4, w3
	lsl	w27, w27, w3
	str	w27, [x20, 44]
	stp	w4, w19, [x20, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
.L801:
	add	x28, x28, 1
	cmp	x28, x22
	beq	.L705
.L704:
	sub	w0, w0, #1
	lsl	w27, w0, 6
	sub	w0, w27, w0
	ubfx	x0, x0, 6, 24
	add	w27, w0, 1
	tbnz	w19, #31, .L894
.L702:
	lsl	w3, w27, 24
	add	x6, x25, 24
	cmp	w3, w26
	mov	x1, x28
	mov	x0, x20
	sub	w4, w26, w3
	bls	.L895
	add	x1, x25, 24
	uxtw	x0, w27
	ldrb	w0, [x1, x0]
	lsl	w26, w26, w0
	sub	w19, w19, w0
	lsl	w0, w27, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L801
	.p2align 3
.L872:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	b	.L732
	.p2align 3
.L874:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L764
	.p2align 3
.L698:
	ldr	x25, .LC28
	uxtw	x0, w22
	str	wzr, [x29, 124]
	add	x1, x25, 24
	ldrb	w0, [x1, x0]
	lsl	w26, w5, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L705
	.p2align 3
.L891:
	add	w1, w4, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L797
	.p2align 3
.L886:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L887
	.p2align 3
.L885:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L734
	.p2align 3
.L780:
	uxtw	x1, w0
	add	x4, x25, 24
	ldrb	w6, [x4, x1]
	lsl	w1, w26, w6
	sub	w4, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	mov	w6, 0
	str	w0, [x20, 44]
	stp	w1, w4, [x20, 36]
.L785:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w4, #31, .L896
.L783:
	lsl	w1, w22, 24
	add	x5, x25, 24
	cmp	w1, w19
	mov	w0, 0
	bhi	.L784
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w22, w0, w22
	lsl	w0, w27, w26
.L784:
	orr	w6, w6, w0
	ldrb	w0, [x5, w22, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w4, w4, w0
	cmn	w26, #1
	lsl	w0, w22, w0
	stp	w1, w4, [x20, 36]
	str	w0, [x20, 44]
	bne	.L785
	add	w6, w6, 16
	b	.L779
	.p2align 3
.L892:
	add	w4, w4, 2
	sub	w1, w0, w4, lsr 1
	b	.L798
.L786:
	uxtw	x1, w0
	add	x5, x25, 24
	mov	w6, 0
	ldrb	w19, [x5, x1]
	sub	w4, w26, w19
	lsl	w1, w22, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w1, w4, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L790:
	sub	w19, w19, #1
	mov	w22, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w4, #31, .L897
.L788:
	lsl	w1, w19, 24
	add	x7, x25, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L789
	ldr	w0, [x20, 44]
	sub	w22, w22, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L789:
	orr	w6, w6, w0
	ldrb	w0, [x7, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w22, w0
	sub	w4, w4, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w1, w4, [x20, 36]
	str	w19, [x20, 44]
	bne	.L790
	add	w6, w6, 32
	b	.L779
	.p2align 3
.L894:
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
	b	.L702
	.p2align 3
.L867:
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
	b	.L739
	.p2align 3
.L862:
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
	b	.L709
	.p2align 3
.L881:
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
	b	.L772
	.p2align 3
.L889:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w5
	sub	w6, w6, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w7, w6, [x29, 104]
	bl	BsGet
	ldp	w7, w6, [x29, 104]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w19, w0, w19
	b	.L750
	.p2align 3
.L888:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w5
	sub	w6, w6, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w7, w6, [x29, 104]
	bl	BsGet
	ldp	w7, w6, [x29, 104]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w19, w0, w19
	b	.L720
	.p2align 3
.L896:
	sub	w1, w24, w4
	sub	w5, w23, w4
	and	w1, w1, -8
	mov	x0, x20
	sub	w5, w5, w1
	add	w4, w1, w4
	stp	w6, w5, [x29, 104]
	str	w4, [x29, 120]
	bl	BsGet
	ldp	w6, w5, [x29, 104]
	ldr	w4, [x29, 120]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w19, w0, w19
	b	.L783
.L753:
	uxtw	x1, w0
	add	x5, x25, 24
	mov	w7, 0
	ldrb	w6, [x5, x1]
	sub	w5, w26, w6
	lsl	w1, w28, w6
	lsl	w0, w0, w6
	mov	w26, 4
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	.p2align 2
.L757:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w19, w0, 1
	tbnz	w5, #31, .L898
.L755:
	lsl	w1, w19, 24
	add	x6, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L756
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L756:
	orr	w7, w7, w0
	ldrb	w0, [x6, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w19, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L757
	add	w7, w7, 32
	b	.L746
.L723:
	uxtw	x1, w0
	add	x5, x25, 24
	mov	w7, 0
	ldrb	w6, [x5, x1]
	sub	w5, w26, w6
	lsl	w1, w28, w6
	lsl	w0, w0, w6
	mov	w26, 4
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	.p2align 2
.L727:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w19, w0, 1
	tbnz	w5, #31, .L899
.L725:
	lsl	w1, w19, 24
	add	x6, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L726
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L726:
	orr	w7, w7, w0
	ldrb	w0, [x6, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w19, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L727
	add	w7, w7, 32
	b	.L716
.L701:
	ldr	w1, [x29, 124]
	cmp	w1, 1
	beq	.L706
	b	.L705
	.p2align 3
.L899:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w5
	sub	w6, w6, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w7, w6, [x29, 104]
	bl	BsGet
	ldp	w7, w6, [x29, 104]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w28, w0, w28
	b	.L725
	.p2align 3
.L898:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w5
	sub	w6, w6, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w7, w6, [x29, 104]
	bl	BsGet
	ldp	w7, w6, [x29, 104]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w28, w0, w28
	b	.L755
	.p2align 3
.L868:
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
	b	.L742
	.p2align 3
.L863:
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
	b	.L712
	.p2align 3
.L696:
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
	b	.L697
.L897:
	sub	w1, w24, w4
	sub	w7, w23, w4
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w4, w1, w4
	stp	w6, w7, [x29, 104]
	str	w4, [x29, 120]
	bl	BsGet
	ldp	w6, w7, [x29, 104]
	ldr	w4, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w22, w0, w22
	b	.L788
	.p2align 3
.L882:
	sub	w4, w24, w19
	sub	w6, w23, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w6, w6, w4
	mov	w1, w4
	str	w6, [x29, 108]
	str	w4, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w4, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w4, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L775
.L865:
	cmp	w19, 64
	bgt	.L900
	add	w7, w19, 64
	b	.L716
.L900:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w7, w19, 64
	b	.L716
.L870:
	cmp	w19, 64
	bgt	.L901
	add	w7, w19, 64
	b	.L746
.L901:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w7, w19, 64
	b	.L746
.L884:
	cmp	w19, 64
	bgt	.L902
	add	w6, w19, 64
	b	.L779
.L902:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w6, w19, 64
	b	.L779
.L893:
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
	b	.L699
.L869:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w6, w0, w26
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
	add	w5, w5, w26
	orr	w1, w0, w28
	mov	w26, w5
	mov	w28, w1
	stp	w1, w5, [x20, 36]
	b	.L749
.L864:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w6, w0, w26
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
	add	w7, w5, w26
	orr	w1, w0, w28
	mov	w26, w7
	mov	w28, w1
	stp	w1, w7, [x20, 36]
	b	.L719
.L883:
	sub	w5, w24, w26
	sub	w6, w23, w26
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
	add	w4, w5, w26
	orr	w1, w0, w22
	mov	w26, w4
	mov	w22, w1
	stp	w1, w4, [x20, 36]
	b	.L782
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	str	x1, [x29, 104]
	mov	x24, 0
	str	w2, [x29, 120]
	bl	_mcount
	ldp	w7, w20, [x19, 36]
	ldr	x25, .LC31
	mov	w26, 1
	ldr	w0, [x19, 44]
.L909:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w20, #31, .L1009
.L904:
	lsl	w1, w21, 24
	cmp	w1, w7
	bhi	.L905
	ldr	w0, [x19, 44]
	add	x3, x25, 24
	sub	w1, w7, w1
	mov	w27, 0
	sub	w0, w0, w21
	mov	w28, 6
	ldrb	w21, [x3, w0, uxtw]
	lsl	w1, w1, w21
	sub	w20, w20, w21
	lsl	w21, w0, w21
	str	w21, [x19, 44]
	stp	w1, w20, [x19, 36]
	b	.L908
	.p2align 3
.L906:
	lsl	w1, w21, 24
	add	x3, x25, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L907
	ldr	w5, [x19, 44]
	lsl	w0, w26, w28
	sub	w22, w22, w1
	sub	w21, w5, w21
.L907:
	orr	w27, w27, w0
	ldrb	w0, [x3, w21, uxtw]
	sub	w28, w28, #1
	lsl	w1, w22, w0
	sub	w20, w20, w0
	lsl	w21, w21, w0
	cmn	w28, #1
	stp	w1, w20, [x19, 36]
	str	w21, [x19, 44]
	beq	.L1010
.L908:
	sub	w21, w21, #1
	mov	w22, w1
	ubfx	x21, x21, 1, 24
	add	w21, w21, 1
	tbz	w20, #31, .L906
	mov	w0, 24
	sub	w1, w0, w20
	mov	w0, 16
	sub	w3, w0, w20
	and	w1, w1, -8
	mov	x0, x19
	sub	w23, w3, w1
	add	w20, w1, w20
	bl	BsGet
	and	w3, w23, 7
	lsl	w0, w0, w3
	orr	w22, w0, w22
	b	.L906
	.p2align 3
.L1010:
	ldr	x1, [x29, 104]
	lsl	w0, w27, 1
	orr	w0, w0, 1
	strb	w0, [x1, x24]
	ldp	w7, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L966:
	add	x24, x24, 1
	cmp	x24, 3
	bne	.L909
	ldr	x1, [x29, 104]
	mov	w23, 24
	mov	w22, 16
	mov	w27, 1
	add	x21, x1, 14
	add	x1, x1, 80
	str	x1, [x29, 96]
.L935:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w5, w0, 1
	tbnz	w20, #31, .L1011
.L910:
	lsl	w1, w5, 24
	cmp	w1, w7
	bhi	.L911
	ldr	w0, [x19, 44]
	add	x4, x25, 24
	sub	w1, w7, w1
	mov	w26, 0
	sub	w0, w0, w5
	ldrb	w4, [x4, w0, uxtw]
	lsl	w1, w1, w4
	sub	w20, w20, w4
	lsl	w0, w0, w4
	mov	w4, 6
	stp	w1, w20, [x19, 36]
	str	w0, [x19, 44]
	b	.L914
	.p2align 3
.L912:
	lsl	w1, w24, 24
	add	x5, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L913
	ldr	w7, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w24, w7, w24
.L913:
	orr	w26, w26, w0
	ldrb	w0, [x5, w24, uxtw]
	sub	w4, w4, #1
	lsl	w1, w28, w0
	sub	w20, w20, w0
	cmn	w4, #1
	lsl	w0, w24, w0
	stp	w1, w20, [x19, 36]
	str	w0, [x19, 44]
	beq	.L1012
.L914:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w24, w0, 1
	tbz	w20, #31, .L912
	sub	w1, w23, w20
	sub	w5, w22, w20
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	str	w4, [x29, 128]
	str	w5, [x29, 136]
	add	w20, w1, w20
	bl	BsGet
	ldr	w5, [x29, 136]
	ldr	w4, [x29, 128]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L912
	.p2align 3
.L1012:
	lsl	w0, w26, 1
	orr	w0, w0, 1
	strb	w0, [x21, -11]
	ldp	w24, w28, [x19, 36]
	ldr	w0, [x19, 44]
.L967:
	sub	x26, x21, #10
	.p2align 2
.L920:
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w20, w20, w0
	ubfx	x20, x20, 6, 24
	add	w20, w20, 1
	tbnz	w28, #31, .L1013
.L915:
	lsl	w1, w20, 24
	cmp	w1, w24
	bhi	.L916
	ldr	w0, [x19, 44]
	add	x7, x25, 24
	sub	w24, w24, w1
	mov	w5, 0
	sub	w0, w0, w20
	mov	w4, 6
	ldrb	w20, [x7, w0, uxtw]
	lsl	w24, w24, w20
	sub	w28, w28, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w24, w28, [x19, 36]
	b	.L919
	.p2align 3
.L917:
	lsl	w1, w20, 24
	add	x7, x25, 24
	cmp	w1, w24
	mov	w0, 0
	bhi	.L918
	ldr	w8, [x19, 44]
	lsl	w0, w27, w4
	sub	w24, w24, w1
	sub	w20, w8, w20
.L918:
	orr	w5, w5, w0
	ldrb	w0, [x7, w20, uxtw]
	sub	w4, w4, #1
	lsl	w24, w24, w0
	sub	w28, w28, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w24, w28, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1014
.L919:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w28, #31, .L917
	sub	w1, w23, w28
	sub	w7, w22, w28
	and	w1, w1, -8
	mov	x0, x19
	sub	w7, w7, w1
	add	w28, w1, w28
	stp	w4, w5, [x29, 124]
	str	w7, [x29, 136]
	bl	BsGet
	ldr	w7, [x29, 136]
	ldp	w4, w5, [x29, 124]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w24, w0, w24
	b	.L917
	.p2align 3
.L1014:
	lsl	w5, w5, 1
	orr	w5, w5, 1
	strb	w5, [x26]
	ldp	w24, w28, [x19, 36]
	ldr	w0, [x19, 44]
.L968:
	add	x26, x26, 1
	cmp	x21, x26
	bne	.L920
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w4, w0, 1
	tbnz	w28, #31, .L1015
.L921:
	lsl	w1, w4, 24
	cmp	w1, w24
	bhi	.L922
	ldr	w0, [x19, 44]
	sub	w24, w24, w1
	add	x1, x25, 24
	mov	w5, 6
	sub	w0, w0, w4
	mov	w26, 0
	ldrb	w1, [x1, w0, uxtw]
	lsl	w4, w24, w1
	sub	w28, w28, w1
	lsl	w0, w0, w1
	str	w0, [x19, 44]
	stp	w4, w28, [x19, 36]
	b	.L925
	.p2align 3
.L924:
	ldr	w7, [x19, 44]
	sub	w1, w1, w0
	sub	w20, w7, w20
.L927:
	add	x0, x25, 24
	sub	w5, w5, #1
	orr	w26, w26, w4
	cmn	w5, #1
	ldrb	w0, [x0, w20, uxtw]
	lsl	w4, w1, w0
	sub	w28, w28, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w4, w28, [x19, 36]
	beq	.L1016
.L925:
	sub	w0, w0, #1
	mov	w1, w4
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w28, #31, .L923
.L928:
	lsl	w0, w20, 24
	lsl	w4, w27, w5
	cmp	w0, w1
	bls	.L924
	mov	w4, 0
	b	.L927
	.p2align 3
.L916:
	add	x1, x25, 24
	uxtw	x0, w20
	ldrb	w0, [x1, x0]
	lsl	w24, w24, w0
	sub	w28, w28, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w24, w28, [x19, 36]
	b	.L968
	.p2align 3
.L1013:
	sub	w5, w23, w28
	sub	w4, w22, w28
	and	w5, w5, -8
	mov	x0, x19
	sub	w4, w4, w5
	mov	w1, w5
	str	w5, [x29, 128]
	str	w4, [x29, 136]
	bl	BsGet
	ldr	w4, [x29, 136]
	ldr	w5, [x29, 128]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w28, w5, w28
	orr	w24, w0, w24
	stp	w24, w28, [x19, 36]
	b	.L915
	.p2align 3
.L1016:
	lsl	w0, w26, 1
	orr	w0, w0, 1
	strb	w0, [x21]
	ldp	w7, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L969:
	add	x1, x21, 11
	add	x26, x21, 1
	str	x1, [x29, 112]
	.p2align 2
.L934:
	sub	w0, w0, #1
	lsl	w5, w0, 6
	sub	w0, w5, w0
	ubfx	x0, x0, 6, 24
	add	w5, w0, 1
	tbnz	w20, #31, .L1017
.L929:
	lsl	w1, w5, 24
	cmp	w1, w7
	bhi	.L930
	ldr	w0, [x19, 44]
	add	x4, x25, 24
	sub	w28, w7, w1
	mov	w24, 0
	sub	w0, w0, w5
	mov	w5, 6
	ldrb	w1, [x4, w0, uxtw]
	sub	w4, w20, w1
	lsl	w28, w28, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w28, w4, [x19, 36]
	b	.L933
	.p2align 3
.L931:
	lsl	w1, w20, 24
	add	x8, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L932
	ldr	w9, [x19, 44]
	lsl	w0, w27, w5
	sub	w28, w28, w1
	sub	w20, w9, w20
.L932:
	orr	w24, w24, w0
	ldrb	w0, [x8, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w4, w4, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w4, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1018
.L933:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w4, #31, .L931
	sub	w1, w23, w4
	sub	w8, w22, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w8, w8, w1
	add	w4, w1, w4
	stp	w5, w8, [x29, 124]
	str	w4, [x29, 136]
	bl	BsGet
	ldp	w5, w8, [x29, 124]
	ldr	w4, [x29, 136]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L931
	.p2align 3
.L1018:
	lsl	w7, w24, 1
	orr	w7, w7, 1
	strb	w7, [x26]
	ldp	w7, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L970:
	ldr	x1, [x29, 112]
	add	x26, x26, 1
	cmp	x1, x26
	bne	.L934
	ldr	x1, [x29, 96]
	add	x21, x21, 33
	cmp	x1, x21
	bne	.L935
	ldr	x1, [x29, 104]
	mov	w27, 1
	str	x1, [x29, 128]
	add	x1, x1, 66
	str	x1, [x29, 96]
.L936:
	ldr	x26, [x29, 128]
	mov	w1, 2
	str	w1, [x29, 124]
.L943:
	mov	x21, 0
.L942:
	sub	w0, w0, #1
	lsl	w8, w0, 6
	sub	w0, w8, w0
	ubfx	x0, x0, 6, 24
	add	w8, w0, 1
	tbnz	w20, #31, .L1019
.L937:
	lsl	w1, w8, 24
	cmp	w1, w7
	bhi	.L938
	ldr	w0, [x19, 44]
	add	x4, x25, 24
	sub	w28, w7, w1
	mov	w24, 0
	sub	w0, w0, w8
	mov	w23, 6
	ldrb	w1, [x4, w0, uxtw]
	sub	w22, w20, w1
	lsl	w28, w28, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w28, w22, [x19, 36]
	b	.L941
	.p2align 3
.L939:
	lsl	w1, w20, 24
	add	x9, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L940
	ldr	w10, [x19, 44]
	lsl	w0, w27, w23
	sub	w28, w28, w1
	sub	w20, w10, w20
.L940:
	orr	w24, w24, w0
	ldrb	w0, [x9, w20, uxtw]
	sub	w23, w23, #1
	lsl	w28, w28, w0
	sub	w22, w22, w0
	lsl	w20, w20, w0
	cmn	w23, #1
	stp	w28, w22, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1020
.L941:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w22, #31, .L939
	mov	w0, 24
	sub	w1, w0, w22
	mov	w0, 16
	sub	w9, w0, w22
	and	w1, w1, -8
	sub	w9, w9, w1
	mov	x0, x19
	str	w9, [x29, 136]
	add	w22, w1, w22
	bl	BsGet
	ldr	w9, [x29, 136]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w28, w0, w28
	b	.L939
	.p2align 3
.L930:
	add	x1, x25, 24
	uxtw	x0, w5
	ldrb	w0, [x1, x0]
	lsl	w7, w7, w0
	sub	w20, w20, w0
	lsl	w0, w5, w0
	str	w0, [x19, 44]
	stp	w7, w20, [x19, 36]
	b	.L970
	.p2align 3
.L1020:
	add	x0, x26, x21
	lsl	w7, w24, 1
	orr	w7, w7, 1
	strb	w7, [x0, 25]
	ldp	w7, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L971:
	add	x21, x21, 1
	cmp	x21, 3
	bne	.L942
	ldr	w1, [x29, 124]
	add	x26, x26, 3
	subs	w1, w1, #1
	str	w1, [x29, 124]
	bne	.L943
	sub	w0, w0, #1
	mov	x26, 0
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w20, #31, .L1021
.L945:
	lsl	w28, w21, 24
	cmp	w28, w7
	bhi	.L946
.L1023:
	ldr	w0, [x19, 44]
	add	x1, x25, 24
	sub	w28, w7, w28
	mov	w6, 0
	sub	w0, w0, w21
	mov	w4, 6
	ldrb	w21, [x1, w0, uxtw]
	lsl	w28, w28, w21
	sub	w20, w20, w21
	lsl	w21, w0, w21
	str	w21, [x19, 44]
	stp	w28, w20, [x19, 36]
	b	.L949
	.p2align 3
.L947:
	lsl	w1, w21, 24
	add	x7, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L948
	ldr	w8, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w21, w8, w21
.L948:
	orr	w6, w6, w0
	ldrb	w0, [x7, w21, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w20, w20, w0
	lsl	w21, w21, w0
	cmn	w4, #1
	stp	w28, w20, [x19, 36]
	str	w21, [x19, 44]
	beq	.L1022
.L949:
	sub	w21, w21, #1
	ubfx	x21, x21, 1, 24
	add	w21, w21, 1
	tbz	w20, #31, .L947
	mov	w0, 24
	str	w6, [x29, 112]
	sub	w1, w0, w20
	mov	w0, 16
	sub	w7, w0, w20
	and	w1, w1, -8
	sub	w7, w7, w1
	mov	x0, x19
	str	w4, [x29, 124]
	add	w20, w1, w20
	str	w7, [x29, 136]
	bl	BsGet
	ldr	w7, [x29, 136]
	ldr	w6, [x29, 112]
	and	w7, w7, 7
	ldr	w4, [x29, 124]
	lsl	w0, w0, w7
	orr	w28, w0, w28
	b	.L947
	.p2align 3
.L938:
	add	x1, x25, 24
	uxtw	x0, w8
	ldrb	w0, [x1, x0]
	lsl	w7, w7, w0
	sub	w20, w20, w0
	lsl	w0, w8, w0
	str	w0, [x19, 44]
	stp	w7, w20, [x19, 36]
	b	.L971
	.p2align 3
.L1022:
	ldr	x0, [x29, 128]
	lsl	w6, w6, 1
	orr	w6, w6, 1
	add	x0, x0, x26
	add	x26, x26, 1
	cmp	x26, 3
	strb	w6, [x0, 31]
	beq	.L950
.L1024:
	ldr	w0, [x19, 44]
	ldp	w7, w20, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbz	w20, #31, .L945
.L1021:
	mov	w0, 24
	str	w7, [x29, 124]
	sub	w4, w0, w20
	mov	w0, 16
	and	w4, w4, -8
	sub	w28, w0, w20
	mov	w1, w4
	mov	x0, x19
	sub	w28, w28, w4
	str	w4, [x29, 136]
	bl	BsGet
	and	w28, w28, 7
	ldr	w7, [x29, 124]
	lsl	w0, w0, w28
	ldr	w4, [x29, 136]
	orr	w28, w0, w7
	add	w4, w4, w20
	mov	w7, w28
	stp	w28, w4, [x19, 36]
	lsl	w28, w21, 24
	mov	w20, w4
	cmp	w28, w7
	bls	.L1023
	.p2align 2
.L946:
	add	x1, x25, 24
	uxtw	x0, w21
	add	x26, x26, 1
	cmp	x26, 3
	ldrb	w0, [x1, x0]
	lsl	w28, w7, w0
	sub	w4, w20, w0
	lsl	w0, w21, w0
	str	w0, [x19, 44]
	stp	w28, w4, [x19, 36]
	bne	.L1024
.L950:
	ldr	x0, [x29, 128]
	ldr	x1, [x29, 96]
	add	x0, x0, 33
	str	x0, [x29, 128]
	cmp	x1, x0
	beq	.L951
	ldp	w7, w20, [x19, 36]
	ldr	w0, [x19, 44]
	b	.L936
	.p2align 3
.L1017:
	sub	w4, w23, w20
	mov	x0, x19
	and	w24, w4, -8
	sub	w28, w22, w20
	mov	w1, w24
	str	w7, [x29, 128]
	str	w5, [x29, 136]
	sub	w28, w28, w24
	bl	BsGet
	and	w28, w28, 7
	ldr	w7, [x29, 128]
	lsl	w0, w0, w28
	add	w4, w24, w20
	ldr	w5, [x29, 136]
	orr	w28, w0, w7
	mov	w20, w4
	mov	w7, w28
	stp	w28, w4, [x19, 36]
	b	.L929
	.p2align 3
.L1019:
	mov	w0, 24
	str	w7, [x29, 112]
	sub	w4, w0, w20
	mov	w0, 16
	and	w22, w4, -8
	sub	w28, w0, w20
	mov	w1, w22
	mov	x0, x19
	str	w8, [x29, 136]
	sub	w28, w28, w22
	bl	BsGet
	and	w28, w28, 7
	ldr	w7, [x29, 112]
	lsl	w0, w0, w28
	add	w4, w22, w20
	ldr	w8, [x29, 136]
	orr	w28, w0, w7
	mov	w20, w4
	mov	w7, w28
	stp	w28, w4, [x19, 36]
	b	.L937
	.p2align 3
.L905:
	add	x1, x25, 24
	uxtw	x0, w21
	ldrb	w0, [x1, x0]
	lsl	w7, w7, w0
	sub	w20, w20, w0
	lsl	w0, w21, w0
	str	w0, [x19, 44]
	stp	w7, w20, [x19, 36]
	b	.L966
	.p2align 3
.L923:
	sub	w1, w23, w28
	mov	x0, x19
	and	w1, w1, -8
	sub	w24, w22, w28
	sub	w24, w24, w1
	add	w28, w1, w28
	str	w4, [x29, 128]
	and	w24, w24, 7
	str	w5, [x29, 136]
	bl	BsGet
	ldr	w4, [x29, 128]
	lsl	w0, w0, w24
	ldr	w5, [x29, 136]
	orr	w1, w0, w4
	b	.L928
.L951:
	ldr	w0, [x29, 120]
	cbz	w0, .L903
	ldr	x0, [x29, 104]
	mov	w22, 24
	mov	w21, 16
	mov	w26, 1
	add	x24, x0, 35
	add	x0, x0, 101
	str	x0, [x29, 136]
.L964:
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1025
.L954:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L955
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	add	x1, x25, 24
	mov	w6, 0
	sub	w0, w0, w20
	mov	w5, 6
	ldrb	w20, [x1, w0, uxtw]
	lsl	w23, w23, w20
	sub	w28, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w28, [x19, 36]
	b	.L958
	.p2align 3
.L956:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w23
	mov	w0, 0
	bhi	.L957
	ldr	w4, [x19, 44]
	lsl	w0, w26, w5
	sub	w23, w23, w1
	sub	w20, w4, w20
.L957:
	orr	w6, w6, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w23, w23, w0
	sub	w28, w28, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w23, w28, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1026
.L958:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w28, #31, .L956
	sub	w1, w22, w28
	sub	w27, w21, w28
	and	w1, w1, -8
	mov	x0, x19
	sub	w27, w27, w1
	add	w28, w1, w28
	and	w27, w27, 7
	stp	w6, w5, [x29, 124]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w23, w0, w23
	ldp	w6, w5, [x29, 124]
	b	.L956
.L1028:
	lsl	w0, w6, 1
	orr	w0, w0, 1
	strb	w0, [x24]
.L974:
	ldr	x0, [x29, 136]
	add	x24, x24, 33
	cmp	x24, x0
	bne	.L964
.L903:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L911:
	add	x1, x25, 24
	uxtw	x0, w5
	ldrb	w0, [x1, x0]
	lsl	w24, w7, w0
	sub	w28, w20, w0
	lsl	w0, w5, w0
	str	w0, [x19, 44]
	stp	w24, w28, [x19, 36]
	b	.L967
.L922:
	add	x1, x25, 24
	uxtw	x0, w4
	ldrb	w0, [x1, x0]
	lsl	w7, w24, w0
	sub	w20, w28, w0
	lsl	w0, w4, w0
	str	w0, [x19, 44]
	stp	w7, w20, [x19, 36]
	b	.L969
.L1026:
	lsl	w0, w6, 1
	orr	w0, w0, 1
	strb	w0, [x24, -1]
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1027
.L959:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L960
.L1029:
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	add	x1, x25, 24
	mov	w6, 0
	sub	w0, w0, w20
	mov	w5, 6
	ldrb	w20, [x1, w0, uxtw]
	lsl	w23, w23, w20
	sub	w27, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w27, [x19, 36]
	b	.L963
	.p2align 3
.L961:
	lsl	w1, w20, 24
	add	x3, x25, 24
	cmp	w1, w23
	mov	w0, 0
	bhi	.L962
	ldr	w4, [x19, 44]
	lsl	w0, w26, w5
	sub	w23, w23, w1
	sub	w20, w4, w20
.L962:
	orr	w6, w6, w0
	ldrb	w0, [x3, w20, uxtw]
	sub	w5, w5, #1
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w23, w27, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1028
.L963:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w27, #31, .L961
	sub	w1, w22, w27
	sub	w28, w21, w27
	and	w1, w1, -8
	mov	x0, x19
	sub	w28, w28, w1
	add	w27, w1, w27
	and	w28, w28, 7
	stp	w5, w6, [x29, 124]
	bl	BsGet
	lsl	w0, w0, w28
	orr	w23, w0, w23
	ldp	w5, w6, [x29, 124]
	b	.L961
.L955:
	add	x1, x25, 24
	uxtw	x0, w20
	ldrb	w0, [x1, x0]
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w23, w27, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w27, #31, .L959
.L1027:
	sub	w3, w22, w27
	sub	w28, w21, w27
	and	w3, w3, -8
	mov	x0, x19
	mov	w1, w3
	sub	w28, w28, w3
	str	w3, [x29, 128]
	and	w28, w28, 7
	bl	BsGet
	lsl	w0, w0, w28
	ldr	w3, [x29, 128]
	orr	w23, w0, w23
	lsl	w0, w20, 24
	add	w27, w3, w27
	cmp	w0, w23
	stp	w23, w27, [x19, 36]
	bls	.L1029
.L960:
	add	x1, x25, 24
	uxtw	x0, w20
	ldrb	w0, [x1, x0]
	lsl	w23, w23, w0
	sub	w1, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w23, w1, [x19, 36]
	b	.L974
.L1009:
	mov	w0, 24
	str	w7, [x29, 136]
	sub	w3, w0, w20
	mov	w0, 16
	and	w27, w3, -8
	sub	w28, w0, w20
	mov	w1, w27
	mov	x0, x19
	sub	w28, w28, w27
	bl	BsGet
	and	w28, w28, 7
	ldr	w7, [x29, 136]
	lsl	w0, w0, w28
	add	w4, w27, w20
	orr	w28, w0, w7
	mov	w20, w4
	mov	w7, w28
	stp	w28, w4, [x19, 36]
	b	.L904
.L1011:
	sub	w28, w23, w20
	mov	x0, x19
	and	w28, w28, -8
	sub	w24, w22, w20
	mov	w1, w28
	sub	w24, w24, w28
	str	w7, [x29, 128]
	and	w24, w24, 7
	str	w5, [x29, 136]
	bl	BsGet
	ldr	w7, [x29, 128]
	lsl	w0, w0, w24
	add	w4, w28, w20
	ldr	w5, [x29, 136]
	orr	w28, w0, w7
	mov	w20, w4
	mov	w7, w28
	stp	w28, w4, [x19, 36]
	b	.L910
.L1015:
	sub	w5, w23, w28
	mov	x0, x19
	and	w26, w5, -8
	sub	w20, w22, w28
	mov	w1, w26
	str	w4, [x29, 136]
	sub	w20, w20, w26
	add	w28, w26, w28
	bl	BsGet
	and	w1, w20, 7
	ldr	w4, [x29, 136]
	lsl	w0, w0, w1
	orr	w24, w0, w24
	stp	w24, w28, [x19, 36]
	b	.L921
.L1025:
	sub	w28, w22, w27
	sub	w3, w21, w27
	and	w28, w28, -8
	mov	x0, x19
	sub	w3, w3, w28
	mov	w1, w28
	str	w3, [x29, 128]
	add	w27, w27, w28
	bl	BsGet
	ldr	w3, [x29, 128]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w23, w0, w23
	stp	w23, w27, [x19, 36]
	b	.L954
	.size	Vp9_ReadMvProbs, .-Vp9_ReadMvProbs
	.align	3
.LC31:
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
	mov	x19, x0
	mov	x0, x30
	mov	x27, x1
	mov	w23, w2
	mov	w22, w3
	str	w6, [x29, 116]
	str	x7, [x29, 120]
	add	x28, x19, 2015
	stp	w5, w4, [x29, 148]
	bl	_mcount
	ldr	x25, .LC33
	add	x0, x19, 2018
	mov	w20, 24
	mov	w24, 16
	mov	w21, 1
	mov	w26, 254
	str	x0, [x29, 136]
	str	wzr, [x29, 172]
.L1062:
	ldp	w7, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w9, w0, 1
	tbnz	w7, #31, .L1031
	ldr	w1, [x27, 36]
.L1032:
	lsl	w6, w9, 24
	cmp	w6, w1
	bhi	.L1033
	ldr	w0, [x27, 44]
	add	x2, x25, 24
	sub	w1, w1, w6
	sub	w0, w0, w9
	ldrb	w2, [x2, w0, uxtw]
	lsl	w6, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w6, w7, [x27, 36]
	tbnz	w7, #31, .L1200
.L1034:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w6
	bhi	.L1035
	ldr	w2, [x27, 44]
	sub	w1, w6, w1
	sub	w0, w2, w0
	add	x2, x25, 24
	ldrb	w2, [x2, w0, uxtw]
	lsl	w6, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w6, w7, [x27, 36]
	tbnz	w7, #31, .L1201
.L1037:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w6
	bhi	.L1042
	sub	w6, w6, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w1, [x1, w0, uxtw]
	lsl	w9, w6, w1
	lsl	w2, w0, w1
	sub	w6, w7, w1
	str	w2, [x27, 44]
	stp	w9, w6, [x27, 36]
	tbnz	w6, #31, .L1202
.L1044:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w9
	bhi	.L1048
	sub	w2, w9, w1
	ldr	w1, [x27, 44]
	mov	w9, 0
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w7, [x1, w0, uxtw]
	lsl	w1, w2, w7
	sub	w6, w6, w7
	lsl	w0, w0, w7
	mov	w7, 6
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	b	.L1049
.L1053:
	lsl	w1, w10, 24
	add	x2, x25, 24
	cmp	w1, w11
	mov	w0, 0
	bhi	.L1054
	ldr	w0, [x27, 44]
	sub	w11, w11, w1
	sub	w10, w0, w10
	lsl	w0, w21, w7
.L1054:
	orr	w9, w9, w0
	ldrb	w0, [x2, w10, uxtw]
	sub	w7, w7, #1
	lsl	w1, w11, w0
	sub	w6, w6, w0
	cmn	w7, #1
	lsl	w0, w10, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1203
.L1049:
	sub	w0, w0, #1
	mov	w11, w1
	ubfx	x0, x0, 1, 24
	add	w10, w0, 1
	tbz	w6, #31, .L1053
	sub	w1, w20, w6
	sub	w2, w24, w6
	and	w1, w1, -8
	mov	x0, x27
	sub	w2, w2, w1
	add	w6, w1, w6
	stp	w11, w10, [x29, 100]
	stp	w7, w9, [x29, 108]
	str	w2, [x29, 128]
	str	w6, [x29, 144]
	bl	BsGet
	ldr	w2, [x29, 128]
	ldp	w11, w10, [x29, 100]
	and	w2, w2, 7
	ldr	w6, [x29, 144]
	lsl	w0, w0, w2
	ldp	w7, w9, [x29, 108]
	orr	w11, w0, w11
	b	.L1053
	.p2align 3
.L1033:
	add	x2, x25, 24
	uxtw	x0, w9
	ldrb	w0, [x2, x0]
	lsl	w1, w1, w0
	sub	w7, w7, w0
	lsl	w0, w9, w0
	str	w0, [x27, 44]
	stp	w1, w7, [x27, 36]
.L1139:
	ldr	x0, [x29, 136]
	add	x28, x28, 1
	cmp	x28, x0
	bne	.L1062
	cmp	w23, wzr
	ccmp	w22, wzr, 0, ne
	beq	.L1204
.L1063:
	ldr	x1, [x29, 120]
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
.L1035:
	uxtw	x1, w0
	add	x2, x25, 24
	mov	w9, 0
	mov	w10, 3
	ldrb	w2, [x2, x1]
	lsl	w1, w6, w2
	sub	w7, w7, w2
	lsl	w0, w0, w2
	str	w0, [x27, 44]
	stp	w1, w7, [x27, 36]
.L1040:
	sub	w0, w0, #1
	mov	w6, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w7, #31, .L1205
.L1038:
	lsl	w1, w2, 24
	add	x11, x25, 24
	cmp	w1, w6
	mov	w0, 0
	bhi	.L1039
	ldr	w12, [x27, 44]
	lsl	w0, w21, w10
	sub	w6, w6, w1
	sub	w2, w12, w2
.L1039:
	orr	w9, w9, w0
	ldrb	w0, [x11, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w6, w0
	sub	w7, w7, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w7, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1040
.L1041:
	ldrb	w0, [x28]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w6, w0, 1
	ldrb	w2, [x1, w9, sxtw]
	cmp	w6, 255
	bgt	.L1056
.L1231:
	add	w1, w2, 1
	cmp	w1, w6
	bgt	.L1057
	tbnz	x1, 0, .L1206
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1057:
	add	w1, w1, 1
.L1059:
	strb	w1, [x28]
	b	.L1139
	.p2align 3
.L1056:
	sub	w0, w26, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L1060
	tbnz	x1, 0, .L1207
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1060:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x28]
	b	.L1139
	.p2align 3
.L1031:
	sub	w6, w20, w7
	sub	w10, w24, w7
	and	w6, w6, -8
	ldr	w2, [x27, 36]
	sub	w10, w10, w6
	mov	w1, w6
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w9, w7, [x29, 104]
	str	w6, [x29, 128]
	str	w2, [x29, 144]
	bl	BsGet
	ldr	w10, [x29, 112]
	ldp	w9, w7, [x29, 104]
	ldr	w6, [x29, 128]
	and	w10, w10, 7
	ldr	w2, [x29, 144]
	lsl	w0, w0, w10
	add	w7, w7, w6
	orr	w1, w0, w2
	stp	w1, w7, [x27, 36]
	b	.L1032
	.p2align 3
.L1204:
	mov	x0, x19
	mov	x1, x27
	bl	Vp9_ReadInterModeProbs
	ldr	w0, [x29, 152]
	cmp	w0, 4
	beq	.L1208
.L1064:
	add	x26, x19, 1979
	add	x22, x19, 1983
	mov	w24, 24
	mov	w23, 16
.L1068:
	ldp	w20, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w20, #31, .L1065
	ldr	w2, [x27, 36]
.L1066:
	lsl	w0, w28, 24
	add	x6, x25, 24
	cmp	w0, w2
	sub	w5, w2, w0
	mov	x1, x26
	mov	x0, x27
	bhi	.L1067
	ldr	w2, [x27, 44]
	sub	w2, w2, w28
	ldrb	w6, [x6, w2, uxtw]
	lsl	w5, w5, w6
	sub	w3, w20, w6
	lsl	w2, w2, w6
	str	w2, [x27, 44]
	stp	w5, w3, [x27, 36]
	bl	Vp9_DiffUpdateProb
.L1140:
	add	x26, x26, 1
	cmp	x22, x26
	bne	.L1068
	ldr	w2, [x29, 148]
	mov	x1, x27
	mov	x0, x19
	add	x3, x29, 172
	add	x21, x19, 1737
	mov	w24, 24
	bl	Vp9_ReadCompPred
	mov	w26, 1
	ldp	w20, w22, [x27, 36]
	ldr	w0, [x27, 44]
	add	x1, x19, 1773
	str	x1, [x29, 128]
.L1069:
	sub	x23, x21, #9
	.p2align 2
.L1102:
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w22, #31, .L1209
.L1070:
	lsl	w1, w28, 24
	cmp	w1, w20
	bhi	.L1071
	ldr	w0, [x27, 44]
	add	x7, x25, 24
	sub	w6, w20, w1
	sub	w0, w0, w28
	ldrb	w28, [x7, w0, uxtw]
	lsl	w6, w6, w28
	sub	w20, w22, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w6, w20, [x27, 36]
	tbnz	w20, #31, .L1210
.L1072:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w6
	bhi	.L1073
	ldr	w28, [x27, 44]
	add	x7, x25, 24
	sub	w1, w6, w1
	sub	w28, w28, w0
	ldrb	w0, [x7, w28, uxtw]
	lsl	w22, w1, w0
	sub	w6, w20, w0
	lsl	w28, w28, w0
	str	w28, [x27, 44]
	stp	w22, w6, [x27, 36]
	tbnz	w6, #31, .L1211
.L1075:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L1080
	sub	w7, w22, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w22, [x1, w0, uxtw]
	lsl	w20, w7, w22
	sub	w28, w6, w22
	lsl	w22, w0, w22
	str	w22, [x27, 44]
	stp	w20, w28, [x27, 36]
	tbnz	w28, #31, .L1212
.L1082:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L1086
	sub	w6, w20, w1
	ldr	w1, [x27, 44]
	mov	w9, 0
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w7, [x1, w0, uxtw]
	lsl	w1, w6, w7
	sub	w20, w28, w7
	lsl	w0, w0, w7
	mov	w7, 6
	stp	w1, w20, [x27, 36]
	str	w0, [x27, 44]
	b	.L1087
	.p2align 3
.L1091:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L1092
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w22, w0, w22
	lsl	w0, w26, w7
.L1092:
	orr	w9, w9, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w7, w7, #1
	lsl	w1, w28, w0
	sub	w20, w20, w0
	cmn	w7, #1
	lsl	w0, w22, w0
	stp	w1, w20, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1213
.L1087:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w20, #31, .L1091
	sub	w1, w24, w20
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w20
	sub	w10, w10, w1
	mov	x0, x27
	stp	w7, w9, [x29, 144]
	str	w10, [x29, 152]
	add	w20, w1, w20
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w7, w9, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1091
	.p2align 3
.L1071:
	add	x1, x25, 24
	uxtw	x0, w28
	ldrb	w0, [x1, x0]
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w0, w28, w0
	str	w0, [x27, 44]
	stp	w20, w22, [x27, 36]
.L1141:
	add	x23, x23, 1
	cmp	x21, x23
	bne	.L1102
	ldr	x1, [x29, 128]
	add	x21, x21, 9
	cmp	x1, x21
	bne	.L1069
	add	x1, x19, 48
	mov	x28, x19
	mov	w24, 16
	mov	w21, 1
	str	x1, [x29, 152]
	.p2align 2
.L1103:
	sub	w0, w0, #1
	mov	x26, x28
	lsl	w1, w0, 6
	mov	w19, 3
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w23, w0, 1
	tbnz	w22, #31, .L1214
.L1104:
	lsl	w1, w23, 24
	cmp	w1, w20
	bhi	.L1105
	ldr	w0, [x27, 44]
	add	x7, x25, 24
	sub	w6, w20, w1
	sub	w0, w0, w23
	ldrb	w23, [x7, w0, uxtw]
	lsl	w20, w6, w23
	sub	w22, w22, w23
	lsl	w23, w0, w23
	str	w23, [x27, 44]
	stp	w20, w22, [x27, 36]
	tbnz	w22, #31, .L1215
.L1106:
	sub	w23, w23, #1
	ubfx	x23, x23, 1, 24
	add	w0, w23, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L1107
	ldr	w23, [x27, 44]
	add	x7, x25, 24
	sub	w6, w20, w1
	sub	w23, w23, w0
	ldrb	w0, [x7, w23, uxtw]
	lsl	w20, w6, w0
	sub	w22, w22, w0
	lsl	w23, w23, w0
	str	w23, [x27, 44]
	stp	w20, w22, [x27, 36]
	tbnz	w22, #31, .L1216
.L1109:
	sub	w0, w23, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L1114
	sub	w23, w20, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w1, [x1, w0, uxtw]
	sub	w20, w22, w1
	lsl	w23, w23, w1
	lsl	w22, w0, w1
	str	w22, [x27, 44]
	stp	w23, w20, [x27, 36]
	tbnz	w20, #31, .L1217
.L1116:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w23
	bhi	.L1120
	sub	w7, w23, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	add	x1, x25, 24
	ldrb	w9, [x1, w0, uxtw]
	lsl	w1, w7, w9
	sub	w20, w20, w9
	lsl	w0, w0, w9
	mov	w7, 6
	mov	w9, 0
	str	w0, [x27, 44]
	stp	w1, w20, [x27, 36]
	b	.L1121
	.p2align 3
.L1125:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w23
	mov	w0, 0
	bhi	.L1126
	ldr	w0, [x27, 44]
	sub	w23, w23, w1
	sub	w22, w0, w22
	lsl	w0, w21, w7
.L1126:
	orr	w9, w9, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w7, w7, #1
	lsl	w1, w23, w0
	sub	w20, w20, w0
	cmn	w7, #1
	lsl	w0, w22, w0
	stp	w1, w20, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1218
.L1121:
	sub	w0, w0, #1
	mov	w23, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w20, #31, .L1125
	mov	w0, 24
	sub	w10, w24, w20
	sub	w1, w0, w20
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 128]
	sub	w10, w10, w1
	add	w20, w1, w20
	stp	w9, w10, [x29, 144]
	bl	BsGet
	ldp	w9, w10, [x29, 144]
	ldr	w7, [x29, 128]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w23, w0, w23
	b	.L1125
	.p2align 3
.L1105:
	add	x1, x25, 24
	uxtw	x0, w23
	ldrb	w0, [x1, x0]
	lsl	w6, w20, w0
	sub	w22, w22, w0
	lsl	w0, w23, w0
	str	w0, [x27, 44]
	stp	w6, w22, [x27, 36]
.L1142:
	subs	w19, w19, #1
	add	x26, x26, 1
	beq	.L1219
	ldr	w0, [x27, 44]
	ldp	w20, w22, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w23, w0, 1
	tbz	w22, #31, .L1104
.L1214:
	mov	w0, 24
	sub	w7, w24, w22
	sub	w9, w0, w22
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w9, w7, [x29, 144]
	bl	BsGet
	ldp	w9, w7, [x29, 144]
	and	w7, w7, 7
	add	w22, w9, w22
	lsl	w0, w0, w7
	orr	w6, w0, w20
	mov	w20, w6
	stp	w6, w22, [x27, 36]
	b	.L1104
	.p2align 3
.L1219:
	ldr	x0, [x29, 152]
	add	x28, x28, 3
	cmp	x28, x0
	beq	.L1137
	ldp	w20, w22, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1103
	.p2align 3
.L1107:
	add	x10, x25, 24
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w23, [x10, x1]
	lsl	w6, w20, w23
	sub	w22, w22, w23
	lsl	w23, w0, w23
	str	w23, [x27, 44]
	stp	w6, w22, [x27, 36]
.L1112:
	sub	w23, w23, #1
	mov	w20, w6
	ubfx	x23, x23, 1, 24
	add	w23, w23, 1
	tbnz	w22, #31, .L1220
.L1110:
	lsl	w1, w23, 24
	add	x10, x25, 24
	cmp	w1, w20
	mov	w0, 0
	bhi	.L1111
	ldr	w11, [x27, 44]
	lsl	w0, w21, w9
	sub	w20, w20, w1
	sub	w23, w11, w23
.L1111:
	orr	w7, w7, w0
	ldrb	w0, [x10, w23, uxtw]
	sub	w9, w9, #1
	lsl	w6, w20, w0
	sub	w22, w22, w0
	lsl	w23, w23, w0
	cmn	w9, #1
	stp	w6, w22, [x27, 36]
	str	w23, [x27, 44]
	bne	.L1112
.L1113:
	ldrb	w0, [x26, 1902]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1130
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1131
	tbnz	x1, 0, .L1221
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1131:
	add	w1, w1, 1
.L1133:
	strb	w1, [x26, 1902]
	b	.L1142
	.p2align 3
.L1073:
	add	x11, x25, 24
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w28, [x11, x1]
	lsl	w22, w6, w28
	sub	w20, w20, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w22, w20, [x27, 36]
.L1078:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w20, #31, .L1222
.L1076:
	lsl	w1, w28, 24
	add	x10, x25, 24
	cmp	w1, w22
	mov	w0, 0
	bhi	.L1077
	ldr	w11, [x27, 44]
	lsl	w0, w26, w9
	sub	w22, w22, w1
	sub	w28, w11, w28
.L1077:
	orr	w7, w7, w0
	ldrb	w0, [x10, w28, uxtw]
	sub	w9, w9, #1
	lsl	w22, w22, w0
	sub	w20, w20, w0
	lsl	w28, w28, w0
	cmn	w9, #1
	stp	w22, w20, [x27, 36]
	str	w28, [x27, 44]
	bne	.L1078
.L1079:
	ldrb	w0, [x23]
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1096
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1097
	tbnz	x1, 0, .L1223
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1097:
	add	w1, w1, 1
.L1099:
	strb	w1, [x23]
	ldp	w20, w22, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1141
	.p2align 3
.L1130:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1134
	tbnz	x1, 0, .L1224
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1134:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x26, 1902]
	b	.L1142
	.p2align 3
.L1096:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1100
	tbnz	x1, 0, .L1225
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1100:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1099
	.p2align 3
.L1220:
	mov	w0, 24
	sub	w10, w24, w22
	sub	w1, w0, w22
	mov	x0, x27
	and	w1, w1, -8
	str	w9, [x29, 128]
	sub	w10, w10, w1
	add	w22, w1, w22
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w9, [x29, 128]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w20, w0, w20
	b	.L1110
	.p2align 3
.L1209:
	sub	w9, w24, w22
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w22
	sub	w7, w7, w9
	mov	w1, w9
	mov	x0, x27
	stp	w9, w7, [x29, 148]
	bl	BsGet
	ldp	w9, w7, [x29, 148]
	and	w7, w7, 7
	add	w22, w9, w22
	lsl	w0, w0, w7
	orr	w6, w0, w20
	mov	w20, w6
	stp	w6, w22, [x27, 36]
	b	.L1070
	.p2align 3
.L1222:
	sub	w1, w24, w20
	mov	w0, 16
	sub	w10, w0, w20
	and	w1, w1, -8
	sub	w10, w10, w1
	mov	x0, x27
	stp	w9, w7, [x29, 144]
	str	w10, [x29, 152]
	add	w20, w1, w20
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w9, w7, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1076
	.p2align 3
.L1114:
	add	x7, x25, 24
	uxtw	x1, w0
	ldrb	w1, [x7, x1]
	mov	w7, 0
	lsl	w23, w20, w1
	sub	w6, w22, w1
	mov	w20, 3
	lsl	w22, w0, w1
	stp	w23, w6, [x27, 36]
	str	w22, [x27, 44]
.L1119:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w6, #31, .L1226
.L1117:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w23
	mov	w0, 0
	bhi	.L1118
	ldr	w11, [x27, 44]
	lsl	w0, w21, w20
	sub	w23, w23, w1
	sub	w22, w11, w22
.L1118:
	orr	w7, w7, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w20, w20, #1
	lsl	w23, w23, w0
	sub	w6, w6, w0
	lsl	w22, w22, w0
	cmn	w20, #1
	stp	w23, w6, [x27, 36]
	str	w22, [x27, 44]
	bne	.L1119
	add	w7, w7, 16
	b	.L1113
	.p2align 3
.L1080:
	uxtw	x1, w0
	add	x7, x25, 24
	mov	w20, 3
	ldrb	w7, [x7, x1]
	lsl	w1, w22, w7
	sub	w6, w6, w7
	lsl	w22, w0, w7
	mov	w7, 0
	stp	w1, w6, [x27, 36]
	str	w22, [x27, 44]
.L1085:
	sub	w22, w22, #1
	mov	w28, w1
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w6, #31, .L1227
.L1083:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L1084
	ldr	w11, [x27, 44]
	lsl	w0, w26, w20
	sub	w28, w28, w1
	sub	w22, w11, w22
.L1084:
	orr	w7, w7, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w20, w20, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	lsl	w22, w22, w0
	cmn	w20, #1
	stp	w1, w6, [x27, 36]
	str	w22, [x27, 44]
	bne	.L1085
	add	w7, w7, 16
	b	.L1079
	.p2align 3
.L1215:
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
	orr	w6, w0, w20
	mov	w20, w6
	stp	w6, w22, [x27, 36]
	b	.L1106
	.p2align 3
.L1221:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1133
	.p2align 3
.L1067:
	uxtw	x0, w28
	add	x1, x25, 24
	ldrb	w1, [x1, x0]
	lsl	w2, w2, w1
	sub	w0, w20, w1
	lsl	w1, w28, w1
	str	w1, [x27, 44]
	stp	w2, w0, [x27, 36]
	b	.L1140
	.p2align 3
.L1226:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 128]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 128]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w23, w0, w23
	b	.L1117
	.p2align 3
.L1210:
	sub	w7, w24, w20
	mov	w0, 16
	and	w7, w7, -8
	sub	w22, w0, w20
	mov	w1, w7
	mov	x0, x27
	sub	w22, w22, w7
	stp	w6, w7, [x29, 148]
	bl	BsGet
	ldp	w6, w7, [x29, 148]
	and	w1, w22, 7
	lsl	w0, w0, w1
	add	w10, w7, w20
	orr	w22, w0, w6
	mov	w20, w10
	mov	w6, w22
	stp	w22, w10, [x27, 36]
	b	.L1072
	.p2align 3
.L1224:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1134
	.p2align 3
.L1223:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	b	.L1097
	.p2align 3
.L1227:
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
	b	.L1083
	.p2align 3
.L1225:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1100
	.p2align 3
.L1137:
	ldr	w2, [x29, 116]
	mov	x0, x27
	ldr	x1, [x29, 136]
	bl	Vp9_ReadMvProbs
	b	.L1063
	.p2align 3
.L1205:
	sub	w1, w20, w7
	sub	w11, w24, w7
	and	w1, w1, -8
	mov	x0, x27
	sub	w11, w11, w1
	add	w7, w1, w7
	stp	w6, w2, [x29, 100]
	stp	w10, w9, [x29, 108]
	str	w11, [x29, 128]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w11, [x29, 128]
	ldp	w6, w2, [x29, 100]
	and	w11, w11, 7
	ldr	w7, [x29, 144]
	lsl	w0, w0, w11
	ldp	w10, w9, [x29, 108]
	orr	w6, w0, w6
	b	.L1038
.L1120:
	add	x7, x25, 24
	uxtw	x1, w0
	ldrb	w1, [x7, x1]
	mov	w7, 0
	sub	w6, w20, w1
	lsl	w23, w23, w1
	lsl	w0, w0, w1
	mov	w20, 4
	stp	w23, w6, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1124:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w6, #31, .L1228
.L1122:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w23
	mov	w0, 0
	bhi	.L1123
	ldr	w0, [x27, 44]
	sub	w23, w23, w1
	sub	w22, w0, w22
	lsl	w0, w21, w20
.L1123:
	orr	w7, w7, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w20, w20, #1
	lsl	w23, w23, w0
	sub	w6, w6, w0
	cmn	w20, #1
	lsl	w0, w22, w0
	stp	w23, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1124
	add	w7, w7, 32
	b	.L1113
.L1086:
	uxtw	x1, w0
	add	x6, x25, 24
	mov	w7, 0
	ldrb	w9, [x6, x1]
	lsl	w1, w20, w9
	sub	w6, w28, w9
	lsl	w0, w0, w9
	mov	w20, 4
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1090:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w6, #31, .L1229
.L1088:
	lsl	w1, w22, 24
	add	x10, x25, 24
	cmp	w1, w28
	mov	w0, 0
	bhi	.L1089
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w22, w0, w22
	lsl	w0, w26, w20
.L1089:
	orr	w7, w7, w0
	ldrb	w0, [x10, w22, uxtw]
	sub	w20, w20, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	cmn	w20, #1
	lsl	w0, w22, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1090
	add	w7, w7, 32
	b	.L1079
	.p2align 3
.L1228:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 128]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 128]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w23, w0, w23
	b	.L1122
	.p2align 3
.L1216:
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
	orr	w1, w0, w20
	mov	w20, w1
	stp	w1, w22, [x27, 36]
	b	.L1109
	.p2align 3
.L1065:
	sub	w2, w24, w20
	sub	w5, w23, w20
	and	w2, w2, -8
	mov	x0, x27
	sub	w5, w5, w2
	mov	w1, w2
	ldr	w21, [x27, 36]
	str	w5, [x29, 144]
	str	w2, [x29, 152]
	bl	BsGet
	ldr	w5, [x29, 144]
	ldr	w2, [x29, 152]
	and	w5, w5, 7
	add	w3, w20, w2
	lsl	w0, w0, w5
	orr	w2, w0, w21
	mov	w20, w3
	stp	w2, w3, [x27, 36]
	b	.L1066
.L1206:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1059
.L1042:
	uxtw	x1, w0
	add	x2, x25, 24
	mov	w9, 0
	mov	w10, 3
	ldrb	w2, [x2, x1]
	lsl	w1, w6, w2
	sub	w7, w7, w2
	lsl	w0, w0, w2
	str	w0, [x27, 44]
	stp	w1, w7, [x27, 36]
.L1047:
	sub	w0, w0, #1
	mov	w6, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w7, #31, .L1230
.L1045:
	lsl	w1, w2, 24
	add	x11, x25, 24
	cmp	w1, w6
	mov	w0, 0
	bhi	.L1046
	ldr	w0, [x27, 44]
	sub	w6, w6, w1
	sub	w2, w0, w2
	lsl	w0, w21, w10
.L1046:
	orr	w9, w9, w0
	ldrb	w0, [x11, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w6, w0
	sub	w7, w7, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w7, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1047
	ldrb	w0, [x28]
	add	w9, w9, 16
	add	x1, x25, 280
	sub	w0, w0, #1
	lsl	w6, w0, 1
	cmp	w6, 255
	ldrb	w2, [x1, w9, sxtw]
	bgt	.L1056
	b	.L1231
.L1207:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L1060
.L1048:
	uxtw	x1, w0
	add	x2, x25, 24
	mov	w7, 4
	ldrb	w2, [x2, x1]
	lsl	w1, w9, w2
	sub	w6, w6, w2
	lsl	w0, w0, w2
	mov	w9, 0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1052:
	sub	w0, w0, #1
	mov	w10, w1
	ubfx	x0, x0, 1, 24
	add	w11, w0, 1
	tbnz	w6, #31, .L1232
.L1050:
	lsl	w1, w11, 24
	add	x2, x25, 24
	cmp	w1, w10
	mov	w0, 0
	bhi	.L1051
	ldr	w0, [x27, 44]
	sub	w10, w10, w1
	sub	w11, w0, w11
	lsl	w0, w21, w7
.L1051:
	orr	w9, w9, w0
	ldrb	w0, [x2, w11, uxtw]
	sub	w7, w7, #1
	lsl	w1, w10, w0
	sub	w6, w6, w0
	cmn	w7, #1
	lsl	w0, w11, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1052
	add	w9, w9, 32
	b	.L1041
.L1229:
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
	b	.L1088
	.p2align 3
.L1211:
	sub	w9, w24, w6
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w6
	mov	w1, w9
	mov	x0, x27
	sub	w20, w7, w9
	stp	w6, w9, [x29, 148]
	bl	BsGet
	and	w7, w20, 7
	lsl	w0, w0, w7
	ldp	w6, w9, [x29, 148]
	orr	w1, w0, w22
	add	w6, w9, w6
	mov	w22, w1
	stp	w1, w6, [x27, 36]
	b	.L1075
.L1218:
	cmp	w9, 64
	mov	w7, w9
	bgt	.L1233
	add	w7, w7, 64
	b	.L1113
.L1233:
	sub	w22, w0, #1
	lsl	w0, w9, 1
	ubfx	x22, x22, 1, 24
	sub	w7, w0, #65
	add	w22, w22, 1
	mov	w23, w1
	tbnz	w20, #31, .L1234
.L1128:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1129
	ldr	w0, [x27, 44]
	sub	w23, w23, w1
	sub	w22, w0, w22
	mov	w0, 1
.L1129:
	add	w7, w7, w0
	add	x0, x25, 24
	add	w7, w7, 64
	ldrb	w9, [x0, w22, uxtw]
	lsl	w1, w23, w9
	sub	w0, w20, w9
	lsl	w22, w22, w9
	str	w22, [x27, 44]
	stp	w1, w0, [x27, 36]
	b	.L1113
	.p2align 3
.L1200:
	sub	w10, w20, w7
	sub	w9, w24, w7
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w6, w2, [x29, 104]
	str	w7, [x29, 112]
	str	w9, [x29, 128]
	str	w10, [x29, 144]
	bl	BsGet
	ldr	w9, [x29, 128]
	ldp	w6, w2, [x29, 104]
	and	w9, w9, 7
	ldr	w7, [x29, 112]
	ldr	w10, [x29, 144]
	lsl	w0, w0, w9
	orr	w1, w0, w6
	add	w7, w10, w7
	mov	w6, w1
	stp	w1, w7, [x27, 36]
	b	.L1034
.L1213:
	cmp	w9, 64
	mov	w7, w9
	bgt	.L1235
	add	w7, w7, 64
	b	.L1079
.L1230:
	sub	w1, w20, w7
	sub	w11, w24, w7
	and	w1, w1, -8
	mov	x0, x27
	sub	w11, w11, w1
	add	w7, w1, w7
	stp	w6, w2, [x29, 100]
	stp	w10, w9, [x29, 108]
	str	w11, [x29, 128]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w11, [x29, 128]
	ldp	w6, w2, [x29, 100]
	and	w11, w11, 7
	ldr	w7, [x29, 144]
	lsl	w0, w0, w11
	ldp	w10, w9, [x29, 108]
	orr	w6, w0, w6
	b	.L1045
.L1217:
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
	add	w6, w9, w20
	lsl	w0, w0, w7
	mov	w20, w6
	orr	w23, w0, w23
	stp	w23, w6, [x27, 36]
	b	.L1116
.L1208:
	mov	x1, x27
	mov	x0, x19
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1064
.L1201:
	sub	w10, w20, w7
	sub	w9, w24, w7
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w2, w6, [x29, 104]
	str	w7, [x29, 112]
	str	w9, [x29, 128]
	str	w10, [x29, 144]
	bl	BsGet
	ldr	w9, [x29, 128]
	ldp	w2, w6, [x29, 104]
	and	w9, w9, 7
	ldr	w7, [x29, 112]
	ldr	w10, [x29, 144]
	lsl	w0, w0, w9
	orr	w1, w0, w6
	add	w7, w10, w7
	mov	w6, w1
	stp	w1, w7, [x27, 36]
	b	.L1037
.L1235:
	sub	w22, w0, #1
	lsl	w9, w9, 1
	ubfx	x22, x22, 1, 24
	sub	w7, w9, #65
	add	w22, w22, 1
	mov	w28, w1
	tbnz	w20, #31, .L1236
.L1094:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1095
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w22, w0, w22
	mov	w0, 1
.L1095:
	add	w7, w7, w0
	add	x0, x25, 24
	add	w7, w7, 64
	ldrb	w9, [x0, w22, uxtw]
	lsl	w1, w28, w9
	sub	w0, w20, w9
	lsl	w22, w22, w9
	str	w22, [x27, 44]
	stp	w1, w0, [x27, 36]
	b	.L1079
.L1234:
	mov	w0, 24
	sub	w9, w24, w20
	sub	w1, w0, w20
	mov	x0, x27
	and	w1, w1, -8
	sub	w9, w9, w1
	add	w20, w20, w1
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w23, w0, w23
	b	.L1128
.L1212:
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
	orr	w1, w0, w20
	mov	w20, w1
	stp	w1, w6, [x27, 36]
	b	.L1082
.L1232:
	sub	w1, w20, w6
	sub	w2, w24, w6
	and	w1, w1, -8
	mov	x0, x27
	sub	w2, w2, w1
	add	w6, w1, w6
	stp	w10, w11, [x29, 100]
	stp	w7, w9, [x29, 108]
	str	w2, [x29, 128]
	str	w6, [x29, 144]
	bl	BsGet
	ldr	w2, [x29, 128]
	ldp	w10, w11, [x29, 100]
	and	w2, w2, 7
	ldr	w6, [x29, 144]
	lsl	w0, w0, w2
	ldp	w7, w9, [x29, 108]
	orr	w10, w0, w10
	b	.L1050
.L1203:
	cmp	w9, 64
	bgt	.L1237
	add	w9, w9, 64
	b	.L1041
.L1237:
	mov	w1, 128
	mov	x0, x27
	str	w9, [x29, 144]
	bl	Vp9_Cabac_Read
	ldr	w9, [x29, 144]
	add	w0, w0, w9, lsl 1
	sub	w9, w0, #65
	add	w9, w9, 64
	b	.L1041
.L1202:
	sub	w10, w20, w6
	sub	w7, w24, w6
	and	w10, w10, -8
	mov	x0, x27
	sub	w7, w7, w10
	mov	w1, w10
	stp	w2, w9, [x29, 104]
	str	w6, [x29, 112]
	str	w7, [x29, 128]
	str	w10, [x29, 144]
	bl	BsGet
	ldr	w7, [x29, 128]
	ldp	w2, w9, [x29, 104]
	and	w7, w7, 7
	ldr	w6, [x29, 112]
	ldr	w10, [x29, 144]
	lsl	w0, w0, w7
	orr	w1, w0, w9
	add	w6, w10, w6
	mov	w9, w1
	stp	w1, w6, [x27, 36]
	b	.L1044
.L1236:
	sub	w1, w24, w20
	mov	w0, 16
	and	w1, w1, -8
	sub	w9, w0, w20
	sub	w9, w9, w1
	mov	x0, x27
	stp	w7, w9, [x29, 148]
	add	w20, w20, w1
	bl	BsGet
	ldp	w7, w9, [x29, 148]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w28, w0, w28
	b	.L1094
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.align	3
.LC33:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptCoefProbs
	.type	Vp9_AdaptCoefProbs, %function
Vp9_AdaptCoefProbs:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	mov	w21, w3
	mov	x22, x2
	mov	x23, x1
	mov	w19, w4
	mov	w20, w5
	bl	_mcount
	uxtw	x0, w21
	mov	w28, 3
	lsl	x3, x0, 3
	lsl	x4, x0, 9
	sub	x3, x3, x0
	add	x4, x4, x0, lsl 6
	lsl	x3, x3, 2
	lsl	x1, x0, 11
	sub	x3, x3, x0
	add	x4, x4, 8192
	lsl	x3, x3, 4
	add	x0, x1, x0, lsl 8
	add	x0, x22, x0
	add	x1, x24, x3
	add	x4, x22, x4
	str	x1, [x29, 112]
	stp	x0, xzr, [x29, 128]
	add	x1, x23, x3
	add	x0, x4, 1048
	mov	w27, 6
	mov	w30, 255
	mov	w14, 256
	str	x1, [x29, 104]
	str	x0, [x29, 120]
.L1239:
	ldr	x0, [x29, 136]
	mov	w26, 0
	ldr	x1, [x29, 112]
	add	x17, x1, x0
	ldr	x1, [x29, 104]
	add	x16, x1, x0
	ldr	x0, [x29, 120]
	str	x0, [x29, 144]
	ldr	x0, [x29, 128]
	str	x0, [x29, 152]
.L1249:
	sxtw	x23, w26
	mov	w24, 0
	lsl	x0, x23, 3
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x23, x0, x23
	ldp	x21, x25, [x29, 144]
	lsl	x23, x23, 2
	.p2align 2
.L1247:
	sxtw	x7, w24
	cmp	w24, wzr
	lsl	x0, x7, 4
	csel	w8, w28, w27, eq
	mov	x4, x25
	mov	x5, 0
	add	x7, x0, x7, lsl 1
	b	.L1245
	.p2align 3
.L1243:
	add	x0, x0, x7
	ldr	w2, [x21, x5, lsl 2]
	add	x12, x0, x23
	add	x5, x5, 1
	ldp	w18, w3, [x4]
	ldp	w0, w1, [x4, 8]
	asr	w10, w2, 1
	ldrb	w15, [x16, x12]
	add	w0, w0, w3
	add	x4, x4, 16
	asr	w9, w0, 1
	add	w1, w10, w1, lsl 8
	add	w9, w9, w3, lsl 8
	add	x10, x16, x12
	add	x3, x17, x12
	cbz	w2, .L1240
	sdiv	w13, w1, w2
	cmp	w13, wzr
	csinc	w13, w13, wzr, gt
	cmp	w13, 255
	csel	w13, w13, w30, le
	and	w13, w13, 255
.L1240:
	cmp	w2, w19
	mov	w11, 128
	csel	w2, w2, w19, ls
	adds	w1, w0, w18
	asr	w22, w1, 1
	mov	w6, w11
	mul	w2, w2, w20
	add	w18, w22, w18, lsl 8
	udiv	w2, w2, w19
	sub	w22, w14, w2
	mul	w15, w22, w15
	add	w15, w15, w11
	madd	w2, w2, w13, w15
	lsr	w2, w2, 8
	strb	w2, [x17, x12]
	ldrb	w12, [x10, 1]
	beq	.L1241
	sdiv	w18, w18, w1
	cmp	w18, wzr
	csinc	w18, w18, wzr, gt
	cmp	w18, 255
	csel	w18, w18, w30, le
	and	w11, w18, 255
.L1241:
	cmp	w1, w19
	csel	w2, w1, w19, ls
	mul	w2, w2, w20
	udiv	w1, w2, w19
	sub	w2, w14, w1
	mul	w2, w2, w12
	add	w2, w2, 128
	madd	w1, w1, w11, w2
	lsr	w1, w1, 8
	strb	w1, [x3, 1]
	ldrb	w2, [x10, 2]
	cbz	w0, .L1242
	sdiv	w9, w9, w0
	cmp	w9, wzr
	csinc	w9, w9, wzr, gt
	cmp	w9, 255
	csel	w9, w9, w30, le
	and	w6, w9, 255
.L1242:
	cmp	w0, w19
	csel	w1, w0, w19, ls
	mul	w1, w1, w20
	udiv	w0, w1, w19
	sub	w1, w14, w0
	mul	w1, w1, w2
	add	w1, w1, 128
	madd	w0, w0, w6, w1
	lsr	w0, w0, 8
	strb	w0, [x3, 2]
.L1245:
	sxtw	x12, w5
	cmp	w5, w8
	lsl	x0, x12, 2
	mov	w13, 128
	sub	x0, x0, x12
	blt	.L1243
	add	w24, w24, 1
	add	x25, x25, 96
	cmp	w24, 6
	add	x21, x21, 24
	bne	.L1247
	ldr	x0, [x29, 152]
	add	w26, w26, 1
	cmp	w26, 2
	add	x0, x0, 576
	str	x0, [x29, 152]
	ldr	x0, [x29, 144]
	add	x0, x0, 144
	str	x0, [x29, 144]
	bne	.L1249
	ldp	x1, x0, [x29, 128]
	add	x0, x0, 216
	add	x1, x1, 1152
	cmp	x0, 432
	stp	x1, x0, [x29, 128]
	ldr	x0, [x29, 120]
	add	x0, x0, 288
	str	x0, [x29, 120]
	bne	.L1239
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.size	Vp9_AdaptCoefProbs, .-Vp9_AdaptCoefProbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptResidualProbs
	.type	Vp9_AdaptResidualProbs, %function
Vp9_AdaptResidualProbs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w20, w5
	mov	w19, w6
	mov	w24, w4
	mov	x22, x1
	mov	x21, x2
	bl	_mcount
	cmp	w24, wzr
	mov	w0, 128
	ccmp	w20, wzr, 0, ne
	mov	w20, 112
	cset	w2, ne
	cmp	w19, wzr
	cset	w1, eq
	mov	w19, 0
	cmp	w2, w1
	csel	w20, w0, w20, cc
.L1258:
	mov	w3, w19
	mov	w5, w20
	mov	w4, 24
	mov	x2, x21
	mov	x1, x22
	mov	x0, x23
	add	w19, w19, 1
	bl	Vp9_AdaptCoefProbs
	cmp	w19, 4
	bne	.L1258
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_AdaptResidualProbs, .-Vp9_AdaptResidualProbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	mov	x22, x3
	mov	x24, x4
	bl	_mcount
	ldrsb	w0, [x20, w19, uxtw]
	cmp	w0, wzr
	ble	.L1266
	mov	x4, x24
	mov	x3, x22
	mov	x2, x21
	mov	x1, x20
	bl	Vp9_AdaptProbs
	mov	w23, w0
	add	w0, w19, 1
	ldrsb	w0, [x20, x0]
	cmp	w0, wzr
	ble	.L1267
.L1264:
	mov	x1, x20
	mov	x4, x24
	mov	x3, x22
	mov	x2, x21
	bl	Vp9_AdaptProbs
	mov	w20, w0
.L1265:
	ubfx	x19, x19, 1, 31
	add	x1, x29, 72
	stp	w23, w20, [x29, 72]
	ldrb	w0, [x22, x19]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21, x19]
	add	w0, w23, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1266:
	neg	w0, w0
	ldr	w23, [x24, w0, sxtw 2]
	add	w0, w19, 1
	ldrsb	w0, [x20, x0]
	cmp	w0, wzr
	bgt	.L1264
.L1267:
	neg	w0, w0
	ldr	w20, [x24, w0, sxtw 2]
	b	.L1265
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptModeProbs
	.type	Vp9_AdaptModeProbs, %function
Vp9_AdaptModeProbs:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	x20, 0
	mov	x24, x1
	mov	x19, x2
	mov	w27, w3
	mov	w26, w4
	bl	_mcount
.L1269:
	add	x0, x24, x20
	ldr	x1, [x19, 11560]
	add	x1, x1, x20, lsl 3
	ldrb	w0, [x0, 1979]
	bl	Vp9_ModeMvMergeProbs
	add	x1, x23, x20
	add	x20, x20, 1
	cmp	x20, 4
	strb	w0, [x1, 1979]
	bne	.L1269
	add	x22, x24, 1983
	add	x21, x23, 1983
	mov	x20, 0
	.p2align 2
.L1270:
	ldr	x1, [x19, 11568]
	ldrb	w0, [x22], 1
	add	x1, x1, x20
	add	x20, x20, 8
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21], 1
	cmp	x20, 40
	bne	.L1270
	add	x22, x24, 1998
	add	x21, x23, 1998
	mov	x20, 0
	.p2align 2
.L1271:
	ldr	x1, [x19, 11584]
	ldrb	w0, [x22], 1
	add	x1, x1, x20
	add	x20, x20, 8
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21], 1
	cmp	x20, 40
	bne	.L1271
	add	x22, x24, 1988
	add	x21, x23, 1988
	mov	x20, 8
	.p2align 2
.L1272:
	ldr	x2, [x19, 11576]
	sub	x1, x20, #8
	ldrb	w0, [x22]
	add	x21, x21, 2
	add	x1, x2, x1
	add	x22, x22, 2
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21, -2]
	ldr	x1, [x19, 11576]
	ldrb	w0, [x22, -1]
	add	x1, x1, x20
	add	x20, x20, 16
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21, -1]
	cmp	x20, 88
	bne	.L1272
	ldr	x25, .LC38
	add	x22, x23, 1958
	add	x21, x24, 1958
	mov	x20, 0
	add	x28, x25, 536
	.p2align 2
.L1273:
	ldr	x4, [x19, 11552]
	mov	x3, x21
	mov	x2, x22
	mov	x1, x28
	add	x4, x4, x20
	mov	w0, 0
	add	x20, x20, 16
	add	x22, x22, 3
	bl	Vp9_AdaptProbs
	add	x21, x21, 3
	cmp	x20, 112
	bne	.L1273
	add	x22, x23, 1728
	add	x21, x24, 1728
	mov	x20, 0
	add	x28, x25, 544
.L1274:
	ldr	x4, [x19, 9216]
	mov	x3, x21
	mov	x2, x22
	mov	x1, x28
	add	x4, x4, x20
	mov	w0, 0
	add	x20, x20, 40
	add	x22, x22, 9
	bl	Vp9_AdaptProbs
	add	x21, x21, 9
	cmp	x20, 160
	bne	.L1274
	add	x22, x23, 1764
	add	x21, x24, 1764
	mov	x20, 0
	.p2align 2
.L1275:
	ldr	x4, [x19, 9224]
	mov	x3, x21
	mov	x2, x22
	mov	x1, x28
	add	x4, x4, x20
	mov	w0, 0
	add	x20, x20, 40
	add	x22, x22, 9
	bl	Vp9_AdaptProbs
	add	x21, x21, 9
	cmp	x20, 400
	bne	.L1275
	add	x22, x23, 1902
	add	x21, x24, 1902
	mov	x20, 0
	add	x28, x25, 568
	.p2align 2
.L1276:
	ldr	x4, [x19, 9232]
	mov	x3, x21
	mov	x2, x22
	mov	x1, x28
	add	x4, x4, x20
	mov	w0, 0
	add	x20, x20, 16
	add	x22, x22, 3
	bl	Vp9_AdaptProbs
	add	x21, x21, 3
	cmp	x20, 256
	bne	.L1276
	cmp	w27, 4
	beq	.L1277
.L1281:
	cmp	w26, 4
	beq	.L1298
.L1279:
	mov	x20, 0
.L1282:
	add	x0, x24, x20
	ldr	x1, [x19, 11616]
	add	x1, x1, x20, lsl 3
	ldrb	w0, [x0, 2015]
	bl	Vp9_ModeMvMergeProbs
	add	x1, x23, x20
	add	x20, x20, 1
	cmp	x20, 3
	strb	w0, [x1, 2015]
	bne	.L1282
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1277:
	add	x22, x23, 1950
	add	x21, x24, 1950
	mov	x20, 0
	add	x25, x25, 576
.L1280:
	ldr	x4, [x19, 11544]
	mov	x3, x21
	mov	x2, x22
	mov	x1, x25
	add	x4, x4, x20
	mov	w0, 0
	add	x20, x20, 12
	add	x22, x22, 2
	bl	Vp9_AdaptProbs
	add	x21, x21, 2
	cmp	x20, 48
	bne	.L1280
	b	.L1281
.L1298:
	add	x27, x24, 2009
	add	x26, x23, 2009
	mov	x22, 0
	mov	x25, 0
	add	x28, x29, 112
.L1284:
	ldr	x2, [x19, 11608]
	lsl	x1, x25, 3
	add	x0, x24, x25
	mov	x20, 0
	ldr	w3, [x2, x1]
	add	x1, x2, x1
	str	w3, [x29, 96]
	ldrb	w0, [x0, 2013]
	ldr	w1, [x1, 4]
	str	w1, [x29, 100]
	add	x1, x29, 96
	bl	Vp9_ModeMvMergeProbs
	add	x1, x23, x25
	strb	w0, [x1, 2013]
	add	x1, x29, 104
	ldr	x3, [x19, 11600]
	ldrb	w0, [x27]
	add	x2, x3, x22, lsl 2
	ldr	w3, [x3, x22, lsl 2]
	str	w3, [x29, 104]
	ldp	w3, w4, [x2, 4]
	add	w3, w4, w3
	str	w3, [x29, 108]
	ldr	w3, [x2, 4]
	str	w3, [x29, 112]
	ldr	w2, [x2, 8]
	str	w2, [x29, 116]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x26]
	mov	x1, x28
	ldrb	w0, [x27, 1]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x26, 1]
	lsl	x1, x25, 4
	ldr	x2, [x19, 11592]
	add	x0, x2, x1
	ldr	w1, [x2, x1]
	str	w1, [x29, 120]
	ldp	w2, w1, [x0, 4]
	add	w1, w2, w1
	ldr	w2, [x0, 12]
	add	w1, w1, w2
	str	w1, [x29, 124]
	ldr	w1, [x0, 4]
	str	w1, [x29, 128]
	ldr	w1, [x0, 8]
	add	w2, w1, w2
	str	w2, [x29, 132]
	ldr	w1, [x0, 8]
	str	w1, [x29, 136]
	ldr	w0, [x0, 12]
	str	w0, [x29, 140]
.L1283:
	add	x21, x22, x20
	add	x0, x29, 120
	add	x1, x0, x20, lsl 3
	add	x0, x24, x21
	add	x21, x23, x21
	add	x20, x20, 1
	ldrb	w0, [x0, 2003]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x21, 2003]
	cmp	x20, 3
	bne	.L1283
	add	x25, x25, 1
	add	x27, x27, 2
	cmp	x25, 2
	add	x26, x26, 2
	add	x22, x22, 3
	bne	.L1284
	b	.L1279
	.size	Vp9_AdaptModeProbs, .-Vp9_AdaptModeProbs
	.align	3
.LC38:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptMvProbs
	.type	Vp9_AdaptMvProbs, %function
Vp9_AdaptMvProbs:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	x24, x1
	mov	x22, x2
	mov	w26, w3
	bl	_mcount
	ldr	x0, .LC45
	mov	w25, 0
	ldr	x4, [x22, 11624]
	add	x3, x0, 592
	add	x2, x0, 584
	ldr	w1, [x0, 584]
	str	w1, [x29, 80]
	str	w1, [x29, 88]
	add	x1, x29, 104
	ldr	w0, [x2, 2]
	add	x2, x23, 2018
	ldp	x6, x7, [x3]
	ldr	w5, [x3, 16]
	add	x3, x24, 2018
	str	w0, [x29, 82]
	str	w0, [x29, 90]
	mov	w0, 0
	stp	x6, x7, [x1]
	add	x1, x29, 80
	str	w5, [x29, 120]
	bl	Vp9_AdaptProbs
.L1302:
	ldr	x1, [x22, 11632]
	add	x21, x24, 2033
	ldrb	w0, [x24, 2021]
	add	x20, x23, 2033
	mov	x19, 0
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x23, 2021]
	add	x3, x24, 2022
	add	x2, x23, 2022
	ldr	x4, [x22, 11640]
	add	x1, x29, 104
	mov	w0, 0
	bl	Vp9_AdaptProbs
	ldr	x2, [x22, 11648]
	add	x1, x29, 96
	ldrb	w0, [x24, 2032]
	ldp	w3, w2, [x2]
	stp	w3, w2, [x29, 96]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x23, 2032]
	.p2align 2
.L1300:
	ldr	x1, [x22, 11656]
	ldrb	w0, [x21], 1
	add	x1, x1, x19
	add	x19, x19, 8
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x20], 1
	cmp	x19, 80
	bne	.L1300
	ldr	x4, [x22, 11664]
	add	x3, x24, 2043
	add	x2, x23, 2043
	add	x1, x29, 88
	mov	w0, 0
	bl	Vp9_AdaptProbs
	ldr	x4, [x22, 11664]
	add	x3, x24, 2046
	add	x2, x23, 2046
	add	x1, x29, 88
	add	x4, x4, 16
	mov	w0, 0
	bl	Vp9_AdaptProbs
	ldr	x4, [x22, 11672]
	add	x3, x24, 2049
	add	x2, x23, 2049
	add	x1, x29, 88
	mov	w0, 0
	bl	Vp9_AdaptProbs
	cbz	w26, .L1301
	ldr	x1, [x22, 11680]
	ldrb	w0, [x24, 2052]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x23, 2052]
	ldrb	w0, [x24, 2053]
	ldr	x1, [x22, 11688]
	bl	Vp9_ModeMvMergeProbs
	strb	w0, [x23, 2053]
.L1301:
	add	w25, w25, 1
	add	x24, x24, 33
	cmp	w25, 2
	add	x22, x22, 64
	add	x23, x23, 33
	bne	.L1302
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
	.size	Vp9_AdaptMvProbs, .-Vp9_AdaptMvProbs
	.align	3
.LC45:
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
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 270336
	bl	_mcount
	ldr	x22, .LC48
	add	x21, x19, 2644
	mov	x2, 2868
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x22, 96]
	blr	x3
	add	x0, x20, 274432
	mov	w1, 3
	add	x0, x0, 1416
	str	w1, [x19, 5092]
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
.LC48:
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
	mov	x21, x0
	mov	x0, x30
	mov	x23, x1
	add	x19, x21, 274432
	bl	_mcount
	ldr	x1, .LC50
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w22, [x19, 2016]
	ldr	w0, [x23, 656]
	cmp	w0, 1
	beq	.L1324
	mov	w24, 0
	mov	w25, 0
	add	x20, x21, 294912
.L1312:
	ldr	x26, .LC51
	mov	x2, 36712
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x26, 96]
	blr	x3
	str	w22, [x19, 2016]
	add	x0, x19, 1416
	bl	ResetVoQueue
	str	x23, [x21]
	mov	x0, x21
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 3928]
	beq	.L1325
	ldr	x1, [x21]
	add	x19, x21, 270336
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
	str	wzr, [x20, 3796]
	str	wzr, [x20, 3800]
	str	wzr, [x20, 3824]
	str	wzr, [x20, 3828]
	str	wzr, [x20, 3864]
	str	wzr, [x20, 3868]
	ldr	w0, [x23, 656]
	cmp	w0, 1
	beq	.L1326
	str	wzr, [x20, 3784]
	str	wzr, [x22, 4]
.L1316:
	ldr	x3, [x26, 96]
	mov	w1, 0
	mov	x2, 32
	add	x0, x20, 3832
	blr	x3
	mov	x0, x21
	bl	VP9_InitDecPara
	add	x0, x19, 2724
	add	x1, x19, 2760
	.p2align 2
.L1317:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 32]
	cmp	x0, x1
	bne	.L1317
	add	x0, x19, 2840
	add	x2, x19, 2876
	mov	w1, -1
	.p2align 2
.L1318:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L1318
	add	x0, x19, 2796
	mov	w1, 0
	mov	w2, 1
	.p2align 2
.L1319:
	str	w1, [x0]
	add	w1, w1, 1
	str	w2, [x0, -72]
	cmp	w1, 8
	add	x0, x0, 4
	bne	.L1319
	mov	w0, 0
.L1314:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1324:
	add	x20, x21, 294912
	add	x0, x21, 270336
	ldr	w25, [x20, 3784]
	ldr	w24, [x0, 2580]
	b	.L1312
	.p2align 3
.L1326:
	str	w25, [x20, 3784]
	str	w24, [x22, 4]
	b	.L1316
.L1325:
	ldr	x1, .LC53
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L1314
	.size	VP9DEC_Init, .-VP9DEC_Init
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC51:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC53:
	.xword	.LC52
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
	ble	.L1340
	sxtw	x0, w21
	add	x1, x22, x0
	ldrb	w1, [x1, -1]
	str	wzr, [x19]
	and	w2, w1, 224
	cmp	w2, 192
	beq	.L1341
.L1327:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1341:
	and	w7, w1, 7
	ubfx	x3, x1, 3, 2
	add	w7, w7, 1
	add	w2, w3, 1
	mul	w6, w7, w2
	add	w6, w6, 2
	cmp	w21, w6
	blt	.L1327
	sub	w21, w21, w6
	ldrb	w4, [x22, w21, sxtw]
	cmp	w4, w1
	bne	.L1327
	add	x0, x0, 1
	uxtb	x8, w3
	sub	x0, x0, x6, sxtw
	mov	x3, 0
	add	x6, x22, x0
	add	x8, x8, 1
	cbz	w7, .L1331
	.p2align 2
.L1336:
	mov	x0, 0
	mov	w4, 0
	cbz	w2, .L1342
	.p2align 2
.L1337:
	ldrb	w1, [x6, x0]
	lsl	w5, w0, 3
	add	x0, x0, 1
	cmp	w2, w0
	lsl	w1, w1, w5
	orr	w4, w4, w1
	bhi	.L1337
	add	x6, x6, x8
.L1335:
	str	w4, [x20, x3, lsl 2]
	add	x3, x3, 1
	cmp	w7, w3
	bhi	.L1336
.L1331:
	str	w7, [x19]
	b	.L1327
	.p2align 3
.L1340:
	ldr	x1, .LC55
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1327
.L1342:
	mov	w4, w2
	b	.L1335
	.size	Vp9_ParseSuperFrameIndex, .-Vp9_ParseSuperFrameIndex
	.align	3
.LC55:
	.xword	.LC54
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
	add	x21, x19, 294912
	bl	_mcount
	add	x22, x20, 2576
	ldr	w0, [x20, 5112]
	cmp	w0, 1
	beq	.L1362
	ldr	w0, [x21, 3928]
	mov	w1, 1
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
.L1345:
	tbnz	w1, #31, .L1363
	ldr	w0, [x21, 3928]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L1364
	add	x22, x20, 2576
	ldr	x1, .LC61
	ldr	w2, [x22, 52]
	mov	w0, 18
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L1349
	ldr	x1, [x19, 40]
	cbz	x1, .L1349
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC63
	bl	dprint_vfmw
	ldr	w0, [x20, 5112]
	cmp	w0, 1
	beq	.L1365
	ldr	x1, [x19, 32]
	mov	w0, 0
	str	wzr, [x1, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1349:
	ldr	x1, .LC65
	mov	w2, 2258
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1347:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1363:
	ldr	x1, .LC57
	mov	w0, 0
	bl	dprint_vfmw
	add	x1, x19, 274432
	ldr	w0, [x21, 3928]
	add	x1, x1, 1416
	bl	FSP_ClearNotInVoQueue
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1362:
	ldr	w0, [x21, 3928]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
	b	.L1345
	.p2align 3
.L1364:
	ldr	x1, .LC59
	mov	w2, 2246
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1365:
	ldr	w3, [x20, 5116]
	cmp	w3, 8
	bls	.L1352
	ldr	x2, .LC66
	mov	w0, 0
	ldr	x1, .LC68
	add	x2, x2, 616
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1347
	.p2align 3
.L1352:
	add	x3, x22, x3, sxtw 2
	ldr	w0, [x21, 3928]
	ldr	w1, [x3, 264]
	bl	FSP_GetLogicFs
	mov	x3, x0
	cbz	x0, .L1366
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
	b	.L1347
.L1366:
	ldr	x3, .LC70
	mov	w2, 2275
	ldr	x1, .LC72
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1347
	.size	VP9_GetImageBuffer, .-VP9_GetImageBuffer
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
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC66:
	.xword	.LANCHOR0
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
	.global	VP9_FreeCurFb
	.type	VP9_FreeCurFb, %function
VP9_FreeCurFb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x1, x0
	mov	x0, x30
	add	x20, x1, 270336
	add	x19, x1, 294912
	bl	_mcount
	ldr	w1, [x20, 2628]
	tbnz	w1, #31, .L1368
	ldr	w0, [x19, 3928]
	mov	w2, 1
	bl	FSP_ClearLogicFs
.L1368:
	ldr	w0, [x19, 3820]
	cmp	w0, 8
	bhi	.L1367
	add	x0, x20, x0, sxtw 2
	str	wzr, [x0, 2724]
.L1367:
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
	cbz	x20, .L1371
	add	x21, x20, 270336
	add	x0, x20, 294912
	ldr	w1, [x21, 2628]
	ldr	w0, [x0, 3928]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1371
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
	beq	.L1375
	ldr	w0, [x19, 36]
	ldr	x6, [x19, 504]
.L1376:
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
.L1371:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1375:
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
	b	.L1376
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
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
	add	x19, x19, 294912
	mov	w20, w1
	bl	_mcount
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 3928]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 3928]
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
	add	x0, x0, 1416
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
	add	x20, x21, 294912
	bl	_mcount
	ldr	w0, [x20, 3928]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w19, w0
	beq	.L1383
	ldr	w0, [x20, 3928]
	mov	w19, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L1388
.L1383:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1388:
	add	x1, x21, 274432
	ldr	w0, [x20, 3928]
	add	x1, x1, 1416
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
	beq	.L1390
.L1392:
	ldr	x1, .LC74
	mov	w0, 1
	bl	dprint_vfmw
.L1389:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1390:
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 131
	bne	.L1392
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 66
	bne	.L1392
	b	.L1389
	.size	Check_Sync_Code, .-Check_Sync_Code
	.align	3
.LC74:
	.xword	.LC73
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
	cbz	w0, .L1398
	add	x2, x19, 84
	mov	w0, 1
	.p2align 2
.L1396:
	ldr	w3, [x2]
	add	x2, x2, 4
	cbz	w3, .L1395
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L1396
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1398:
	mov	w0, 0
.L1395:
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
	cbz	w0, .L1404
	add	x2, x29, 44
	add	x1, x29, 40
	mov	x0, x20
	bl	Read_Frame_Size
.L1404:
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
	ldr	w0, [x19, 2440]
	ldr	w5, [x19, 2492]
	ldr	w4, [x19, 2496]
	add	x0, x19, x0, sxtw 4
	add	w2, w5, 7
	add	x3, x0, 2560
	add	w1, w4, 7
	and	w2, w2, -8
	and	w1, w1, -8
	asr	w7, w2, 3
	asr	w6, w1, 3
	str	w7, [x19, 2532]
	str	w6, [x19, 2536]
	stp	w2, w1, [x3, 116]
	stp	w5, w4, [x3, 124]
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
	mov	x20, x1
	mov	x21, x0
	mov	x0, x30
	add	x19, x1, 2440
	bl	_mcount
	ldr	w3, [x20, 2492]
	add	x1, x20, 2492
	ldr	w2, [x20, 2496]
	mov	x0, x21
	str	w3, [x20, 2512]
	str	w2, [x20, 2516]
	add	x2, x20, 2496
	bl	Read_Frame_Size
	ldr	w5, [x20, 2496]
	mov	x1, x19
	ldr	w2, [x20, 2440]
	mov	x0, x21
	add	w3, w5, 7
	ldr	w6, [x20, 2492]
	and	w3, w3, -8
	add	x2, x20, x2, sxtw 4
	asr	w7, w3, 3
	add	w4, w6, 7
	str	w7, [x20, 2536]
	add	x7, x2, 2560
	and	w4, w4, -8
	asr	w8, w4, 3
	str	w8, [x20, 2532]
	stp	w4, w3, [x7, 116]
	stp	w6, w5, [x7, 124]
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
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	add	x20, x1, 2440
	mov	w19, 0
	bl	_mcount
.L1414:
	mov	w1, 1
	mov	x0, x22
	bl	BsGet
	cbnz	w0, .L1420
	add	w19, w19, 1
	cmp	w19, 3
	bne	.L1414
	ldp	w1, w0, [x20, 52]
	stp	w1, w0, [x20, 72]
	add	x2, x21, 2496
	add	x1, x21, 2492
	mov	x0, x22
	bl	Read_Frame_Size
	ldp	w6, w5, [x20, 52]
.L1413:
	ldr	w2, [x21, 2440]
	add	w4, w6, 7
	and	w4, w4, -8
	add	w3, w5, 7
	and	w3, w3, -8
	asr	w0, w4, 3
	add	x2, x21, x2, sxtw 4
	str	w0, [x20, 92]
	add	x7, x2, 2560
	asr	w0, w3, 3
	str	w0, [x20, 96]
	mov	x1, x20
	mov	x0, x22
	stp	w4, w3, [x7, 116]
	stp	w6, w5, [x7, 124]
	bl	Setup_Display_Size
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1420:
	add	x19, x21, x19, sxtw 2
	ldp	w2, w1, [x20, 52]
	ldr	w0, [x19, 184]
	stp	w2, w1, [x20, 72]
	add	x0, x21, x0, sxtw 4
	ldr	w6, [x0, 2684]
	str	w6, [x20, 52]
	ldr	w5, [x0, 2688]
	str	w5, [x20, 56]
	b	.L1413
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
	ldr	x20, .LC75
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
.LC75:
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
	ldr	x20, .LC76
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 2644
	ldr	x3, [x20, 96]
	blr	x3
	strb	wzr, [x19, 2567]
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
.LC76:
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
	cbnz	w0, .L1449
.L1424:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1449:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 1]
	cbz	w0, .L1424
	add	x21, x19, 2
	add	x22, x19, 6
.L1430:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1450
.L1427:
	add	x21, x21, 1
	cmp	x21, x22
	bne	.L1430
	mov	w1, 1
	mov	x0, x20
	add	x19, x19, 8
	bl	BsGet
	cbnz	w0, .L1451
.L1431:
	add	x22, x22, 1
	cmp	x22, x19
	beq	.L1424
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbz	w0, .L1431
.L1451:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1433
	neg	w1, w1
.L1433:
	strb	w1, [x22]
	b	.L1431
	.p2align 3
.L1450:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1429
	neg	w1, w1
.L1429:
	strb	w1, [x21]
	b	.L1427
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
	cbnz	w0, .L1459
.L1453:
	str	w0, [x19]
	cmp	w0, w21
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1459:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	mov	w1, w0
	asr	w0, w0, 1
	tbz	x1, 0, .L1453
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
	cbnz	w0, .L1462
	ldr	w1, [x19, 244]
	cbnz	w1, .L1461
	ldr	w1, [x19, 248]
	cbnz	w1, .L1461
	ldr	w0, [x19, 252]
	cmp	w0, wzr
	cset	w0, eq
.L1461:
	str	w0, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1462:
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
	ldr	x0, .LC77
	add	x0, x0, 640
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Seg_Feature_Data_Max, .-VP9_Seg_Feature_Data_Max
	.align	3
.LC77:
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
	bls	.L1467
	subs	w1, w19, #1
	beq	.L1467
	.p2align 2
.L1468:
	lsr	w1, w1, 1
	add	w0, w0, 1
	cbnz	w1, .L1468
.L1467:
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
	bls	.L1473
	subs	w0, w19, #1
	beq	.L1473
	.p2align 2
.L1474:
	lsr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1474
.L1473:
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
	ldr	x0, .LC79
	add	x0, x0, 656
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Is_Segfeature_Signed, .-VP9_Is_Segfeature_Signed
	.align	3
.LC79:
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
	ldr	x22, .LC81
	add	x0, x22, 640
	ldr	w23, [x0, w19, uxtw 2]
	cmp	w23, w20
	blt	.L1485
	tbnz	w20, #31, .L1486
.L1482:
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
.L1485:
	ldr	x1, .LC83
	mov	w3, 2982
	add	x2, x22, 672
	mov	w0, 0
	bl	dprint_vfmw
	tbz	w20, #31, .L1482
.L1486:
	add	x0, x22, 656
	ldr	w0, [x0, w19, uxtw 2]
	cbz	w0, .L1487
.L1483:
	neg	w0, w20
	cmp	w23, w0
	bge	.L1482
	ldr	x1, .LC83
	mov	w3, 2994
	add	x2, x22, 672
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1482
	.p2align 3
.L1487:
	ldr	x1, .LC83
	mov	w3, 2989
	add	x2, x22, 672
	bl	dprint_vfmw
	b	.L1483
	.size	VP9_Set_Segdata, .-VP9_Set_Segdata
	.align	3
.LC81:
	.xword	.LANCHOR0
	.align	3
.LC83:
	.xword	.LC82
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
	bgt	.L1492
	b	.L1491
	.p2align 3
.L1496:
	mov	w4, w0
.L1492:
	add	w0, w4, 1
	asr	w5, w3, w0
	cmp	w5, 3
	bgt	.L1496
	cmp	w4, wzr
	csel	w4, w4, wzr, ge
.L1491:
	cmp	w3, 64
	mov	w0, 0
	ble	.L1493
	mov	w6, 64
	.p2align 2
.L1494:
	add	w0, w0, 1
	lsl	w5, w6, w0
	cmp	w5, w3
	blt	.L1494
.L1493:
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
	ble	.L1500
	mov	w19, 0
	b	.L1501
	.p2align 3
.L1512:
	mov	w19, w0
.L1501:
	add	w0, w19, 1
	asr	w2, w1, w0
	cmp	w2, 3
	bgt	.L1512
	cmp	w19, wzr
	csel	w19, w19, wzr, ge
	cmp	w1, 64
	ble	.L1513
.L1510:
	mov	w0, 0
	mov	w3, 64
	.p2align 2
.L1503:
	add	w0, w0, 1
	lsl	w2, w3, w0
	cmp	w1, w2
	bgt	.L1503
.L1502:
	subs	w19, w19, w0
	str	w0, [x21, 100]
	bne	.L1522
	b	.L1505
	.p2align 3
.L1508:
	ldr	w0, [x21, 100]
	subs	w19, w19, #1
	add	w0, w0, 1
	str	w0, [x21, 100]
	beq	.L1505
.L1522:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1508
.L1505:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 104]
	cbz	w0, .L1499
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w1, [x21, 104]
	add	w0, w1, w0
	str	w0, [x21, 104]
.L1499:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1500:
	cmp	w1, 64
	mov	w19, 0
	bgt	.L1510
	str	wzr, [x21, 100]
	b	.L1505
	.p2align 3
.L1513:
	mov	w0, 0
	b	.L1502
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
	cbnz	w0, .L1561
.L1525:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1561:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 1]
	cbz	w0, .L1528
	add	x19, x23, 5
	add	x20, x23, 12
	b	.L1530
	.p2align 3
.L1529:
	strb	w1, [x19], 1
	cmp	x19, x20
	beq	.L1562
.L1530:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbz	w0, .L1529
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19], 1
	cmp	x19, x20
	bne	.L1530
.L1562:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 4]
	cbnz	w0, .L1531
	mov	w0, -1
	strb	w0, [x23, 12]
	strb	w0, [x23, 13]
	strb	w0, [x23, 14]
.L1528:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 2]
	cbz	w0, .L1525
	mov	w1, 1
	mov	x0, x21
	add	x19, x23, 80
	mov	w24, 0
	bl	BsGet
	ldr	x20, .LC86
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
	ldr	x26, .LC87
	.p2align 2
.L1535:
	mov	x19, 0
.L1538:
	mov	w1, 1
	mov	x0, x21
	mov	w22, w19
	mov	w20, 0
	bl	BsGet
	cbnz	w0, .L1563
.L1537:
	mov	w3, w20
	mov	w2, w22
	mov	w1, w24
	mov	x0, x23
	add	x19, x19, 1
	bl	VP9_Set_Segdata
	cmp	x19, 4
	bne	.L1538
	add	w24, w24, 1
	add	x25, x25, 4
	cmp	w24, 8
	bne	.L1535
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1563:
	ldr	w3, [x25]
	add	x2, x26, 640
	lsl	w1, w27, w19
	mov	x0, x21
	orr	w1, w3, w1
	str	w1, [x25]
	ldr	w1, [x2, x19, lsl 2]
	bl	Decode_Unsigned_Max
	mov	w20, w0
	add	x0, x26, 656
	ldr	w0, [x0, x19, lsl 2]
	cbz	w0, .L1537
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L1537
	.p2align 3
.L1531:
	add	x19, x23, 15
.L1533:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbnz	w0, .L1564
.L1532:
	strb	w1, [x20], 1
	cmp	x20, x19
	bne	.L1533
	b	.L1528
	.p2align 3
.L1564:
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	b	.L1532
	.size	Setup_Segmentation, .-Setup_Segmentation
	.align	3
.LC86:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC87:
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
	cbz	w0, .L1568
	ldp	x19, x20, [sp, 16]
	mov	w0, 4
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1568:
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
	ble	.L1571
	sub	w0, w0, #1
	str	w0, [x19, w1, sxtw 2]
.L1571:
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
	cbz	w20, .L1575
	lsl	w0, w19, 14
	sdiv	w0, w0, w20
.L1574:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1575:
	ldr	x2, .LC90
	mov	w4, 0
	ldr	x1, .LC92
	mov	w3, 3187
	add	x2, x2, 688
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1574
	.size	VP9_get_fixed_point_scale_factor, .-VP9_get_fixed_point_scale_factor
	.align	3
.LC90:
	.xword	.LANCHOR0
	.align	3
.LC92:
	.xword	.LC91
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
	bgt	.L1577
	cmp	w22, w21, lsl 1
	mov	w0, 0
	bgt	.L1577
	cmp	w19, w20, lsl 4
	bgt	.L1577
	cmp	w21, w22, lsl 4
	cset	w0, le
.L1577:
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
	bgt	.L1583
	cmp	w21, w23, lsl 1
	ble	.L1593
.L1583:
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
.L1593:
	cmp	w22, w20, lsl 4
	bgt	.L1583
	cmp	w23, w21, lsl 4
	bgt	.L1583
	cbz	w22, .L1594
	lsl	w20, w20, 14
	sdiv	w3, w20, w22
	str	w3, [x19]
	cbz	w23, .L1595
.L1586:
	lsl	w21, w21, 14
	sdiv	w21, w21, w23
	sbfx	x0, x21, 10, 22
.L1587:
	str	w0, [x19, 12]
	sbfx	x3, x3, 10, 22
	stp	w21, w3, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1594:
	ldr	x2, .LC93
	mov	w3, 3187
	ldr	x1, .LC94
	mov	w4, 0
	add	x2, x2, 688
	mov	w0, 1
	bl	dprint_vfmw
	mov	w3, -1
	str	w3, [x19]
	cbnz	w23, .L1586
.L1595:
	ldr	x2, .LC93
	mov	w3, 3187
	ldr	x1, .LC94
	mov	w4, 0
	add	x2, x2, 688
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldr	w3, [x19]
	mov	w21, w0
	b	.L1587
	.size	vp9_setup_scale_factors, .-vp9_setup_scale_factors
	.align	3
.LC93:
	.xword	.LANCHOR0
	.align	3
.LC94:
	.xword	.LC91
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
	ble	.L1597
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	add	w19, w0, w19
.L1597:
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
	add	x19, x1, 2440
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	mov	w1, 8
	str	w1, [x19, 68]
	cmp	w0, 1
	bls	.L1599
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 12
	mov	w2, 10
	csel	w1, w1, w2, ne
	str	w1, [x19, 68]
.L1599:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	cmp	w0, 7
	str	w0, [x19, 16]
	beq	.L1601
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w21, [x19, 12]
	str	w0, [x19, 20]
	and	w21, w21, -3
	cmp	w21, 1
	beq	.L1606
	mov	w0, 1
	stp	w0, w0, [x19, 44]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1601:
	ldr	w1, [x19, 12]
	and	w1, w1, -3
	cmp	w1, 1
	beq	.L1607
	ldr	x2, .LC95
	mov	w3, 3290
	ldr	x1, .LC97
	mov	w0, 1
	add	x2, x2, 728
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1606:
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
.L1607:
	mov	x0, x20
	stp	wzr, wzr, [x19, 44]
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_ReadBitDepthColorSpaceSampling, .-Vp9_ReadBitDepthColorSpaceSampling
	.align	3
.LC95:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	.LC96
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
	cbz	w27, .L1613
.L1609:
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
	bls	.L1612
	ldr	x2, [x29, 112]
	mov	w0, 0
	ldr	w1, [x29, 108]
	str	w1, [x2]
	ldr	x1, [x29, 120]
	str	w20, [x1]
.L1610:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1613:
	mov	x0, x19
	bl	Vp9_ReadTxMode
	cmp	w0, 4
	mov	w20, w0
	bne	.L1609
	mov	x1, x19
	add	x0, x21, 2003
	bl	Vp9_ReadTxProbs
	b	.L1609
	.p2align 3
.L1612:
	mov	w0, -1
	b	.L1610
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
	str	x25, [sp, 64]
	add	x19, x1, 2440
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	w0, [x19, 8]
	mov	w1, 2
	str	w0, [x19, 4]
	mov	x0, x20
	bl	BsGet
	cmp	w0, 2
	beq	.L1615
	ldr	x1, .LC99
	mov	w0, 1
	bl	dprint_vfmw
.L1615:
	mov	x0, x20
	bl	Vp9_Vfmw_ReadProfile
	str	w0, [x19, 12]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w23, w0
	cbnz	w0, .L1645
	mov	w1, 1
	mov	x0, x20
	str	wzr, [x19, 28]
	bl	BsGet
	str	w0, [x19, 8]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 24]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w1, w0
	ldr	w0, [x19, 8]
	str	w1, [x19, 40]
	cbz	w0, .L1646
	ldr	w0, [x19, 24]
	cbz	w0, .L1620
	str	wzr, [x19, 108]
.L1621:
	cbz	w1, .L1622
	str	wzr, [x19, 112]
.L1623:
	ldr	w0, [x19, 108]
	cbz	w0, .L1624
	mov	x0, x20
	bl	Check_Sync_Code
	ldr	w0, [x19, 12]
	cmp	w0, 1
	bls	.L1625
	mov	x1, x21
	mov	x0, x20
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1626:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 116]
	mov	x1, x21
	mov	x0, x20
	bl	Setup_Frame_Size
	ldr	w0, [x19, 40]
	cbnz	w0, .L1632
.L1648:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 80]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 84]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 88]
	ldr	w1, [x19, 8]
	cbnz	w1, .L1647
	.p2align 2
.L1634:
	mov	x0, x21
	bl	VP9_Setup_Past_Independence
	ldr	w0, [x19, 8]
	cbz	w0, .L1635
	b	.L1636
	.p2align 3
.L1645:
	mov	w1, 3
	mov	x0, x20
	mov	w23, 0
	bl	BsGet
	add	x0, x21, x0, uxtw 2
	mov	w1, 1
	ldr	w0, [x0, 152]
	stp	w1, w0, [x19, 28]
	str	wzr, [x19, 116]
	str	wzr, [x21, 344]
	str	w1, [x19, 24]
.L1617:
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1624:
	mov	w1, 8
	mov	x0, x20
	add	x24, x21, 184
	add	x25, x21, 196
	bl	BsGet
	mov	x22, x24
	str	w0, [x19, 116]
.L1627:
	mov	w1, 3
	mov	x0, x20
	add	x22, x22, 4
	bl	BsGet
	add	x2, x21, x0, sxtw 2
	mov	w1, 1
	mov	x0, x20
	ldr	w2, [x2, 152]
	str	w2, [x22, -4]
	bl	BsGet
	str	w0, [x22, -120]
	cmp	x25, x22
	bne	.L1627
	mov	x0, x20
	mov	x1, x21
	bl	setup_frame_size_with_refs
	ldr	w4, [x21, 2492]
	ldr	w5, [x21, 2496]
	sub	w0, w4, #1
	cmp	w0, 4095
	bhi	.L1629
	sub	w0, w5, #1
	cmp	w0, 4095
	bhi	.L1629
	mov	w1, 1
	mov	x0, x20
	add	x22, x21, 2820
	bl	BsGet
	str	w0, [x21, 56]
	mov	x0, x20
	bl	read_interp_filter_type
	str	w0, [x19, 120]
.L1631:
	ldrsw	x1, [x24], 4
	mov	x0, x22
	ldr	w3, [x21, 2492]
	add	x22, x22, 16
	ldr	w4, [x21, 2496]
	add	x1, x21, x1, lsl 4
	add	x1, x1, 2676
	ldr	w2, [x1, 12]
	ldr	w1, [x1, 8]
	bl	vp9_setup_scale_factors
	cmp	x25, x24
	bne	.L1631
	ldp	w0, w2, [x21, 68]
	ldr	w1, [x21, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x21, 60]
	b	.L1619
	.p2align 3
.L1646:
	mov	x0, x20
	bl	Check_Sync_Code
	mov	x1, x21
	mov	x0, x20
	bl	Vp9_ReadBitDepthColorSpaceSampling
	mov	w0, 255
	str	w0, [x19, 116]
	mov	x1, x21
	mov	x0, x20
	ldr	w2, [x21, 2440]
	stp	w2, w2, [x21, 184]
	str	w2, [x21, 192]
	bl	Setup_Frame_Size
.L1619:
	ldr	w0, [x19, 40]
	cbz	w0, .L1648
.L1632:
	mov	w1, 2
	mov	x0, x20
	stp	wzr, wzr, [x19, 80]
	bl	BsGet
	str	w0, [x19, 88]
	ldr	w1, [x19, 8]
	cbz	w1, .L1634
.L1647:
	ldr	w0, [x19, 40]
	cbnz	w0, .L1634
	ldr	w0, [x19, 108]
	cbnz	w0, .L1634
.L1636:
	ldp	w0, w2, [x21, 68]
	ldr	w1, [x21, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x21, 60]
.L1635:
	add	x1, x21, 336
	mov	x0, x20
	bl	Setup_LoopFilter
	mov	x1, x21
	mov	x0, x20
	bl	Setup_Quantization
	add	x1, x21, 2564
	mov	x0, x20
	bl	Setup_Segmentation
	mov	x1, x19
	mov	x0, x20
	bl	Setup_Tile_Info
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 8]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1625:
	mov	w0, 1
	mov	w1, 8
	str	w0, [x19, 16]
	stp	w0, w0, [x19, 44]
	str	w1, [x19, 68]
	b	.L1626
	.p2align 3
.L1622:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 112]
	b	.L1623
	.p2align 3
.L1620:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 108]
	ldr	w1, [x19, 40]
	b	.L1621
	.p2align 3
.L1629:
	ldr	x2, .LC100
	mov	w3, 3443
	ldr	x1, .LC102
	mov	w0, 1
	add	x2, x2, 768
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1617
	.size	Read_UnCompressed_Header, .-Read_UnCompressed_Header
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC100:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LC101
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
	add	x7, x19, 2440
	ldr	w0, [x7, 116]
	mov	w1, 0
	add	x5, x19, 80
	cbz	w0, .L1654
	.p2align 2
.L1657:
	add	x4, x19, x1, sxtw 2
	tbz	x0, 0, .L1651
	ldr	w6, [x4, 152]
	ldr	w3, [x7]
	ldr	w2, [x5, w6, sxtw 2]
	cmp	w2, wzr
	sub	w2, w2, #1
	ble	.L1652
	str	w2, [x5, w6, sxtw 2]
.L1652:
	str	w3, [x4, 152]
	ldr	w2, [x5, w3, sxtw 2]
	add	w2, w2, 1
	str	w2, [x5, w3, sxtw 2]
.L1651:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1657
.L1654:
	ldrsw	x0, [x19, 2440]
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
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 270336
	add	x20, x22, 16
	bl	_mcount
	add	x23, x19, 2644
	add	x2, x19, 2560
	ldr	w21, [x19, 5112]
	cmp	w21, 1
	beq	.L1694
	add	x3, x20, 262144
	add	x1, x19, 2576
	add	x0, x20, 270336
	strb	wzr, [x3, 1028]
	ldr	w3, [x19, 5092]
	str	w3, [x1, 60]
	ldr	w2, [x2, 8]
	str	w3, [x0, 2112]
	and	w2, w2, -16
	str	w2, [x0, 2128]
	ldr	w2, [x1, 64]
	str	w2, [x0, 2116]
	ldr	w2, [x23, 12]
	str	w2, [x0, 2088]
	ldr	w2, [x23, 16]
	str	w2, [x0, 2092]
	ldr	x2, [x22]
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
	ldr	w0, [x23, 192]
	cmp	w0, 8
	ble	.L1695
	add	x21, x22, 294912
	ldrsw	x0, [x21, 3820]
	add	x23, x23, x0, lsl 2
	ldr	w0, [x23, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	bgt	.L1670
.L1700:
	add	x0, x1, x0, sxtw 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	bgt	.L1672
.L1701:
	add	x0, x1, x0, sxtw 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbz	w3, .L1674
.L1702:
	ldr	w0, [x19, 5192]
	cmp	w0, 1
	beq	.L1674
	ldr	w1, [x19, 2628]
.L1675:
	ldr	w0, [x21, 3928]
	bl	FSP_GetLogicFs
	mov	x23, x0
	ldr	w1, [x19, 2620]
	ldr	w0, [x21, 3928]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x19, 2616]
	ldr	w0, [x21, 3928]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x19, 2624]
	ldr	w0, [x21, 3928]
	bl	FSP_GetLogicFs
	cmp	x23, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L1676
	cmp	x25, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L1676
	ldr	x1, [x23, 32]
	cbz	x1, .L1696
	add	x1, x20, 270336
	ldr	w2, [x23, 8]
	str	w2, [x1, 2456]
	ldr	x2, [x23, 32]
	ldr	w2, [x2, 20]
	str	w2, [x1, 2496]
	ldr	x2, [x23, 32]
	ldr	w2, [x2, 8]
	str	w2, [x1, 2440]
	ldr	x1, [x25, 32]
	cbz	x1, .L1697
.L1691:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2444]
	ldr	x1, [x24, 32]
	cbz	x1, .L1698
.L1692:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2448]
	ldr	x0, [x0, 32]
	cbz	x0, .L1699
.L1693:
	add	x1, x20, 270336
	ldr	w3, [x0, 8]
	add	x2, x20, 262144
	mov	w0, 0
	str	w3, [x1, 2452]
	ldr	w1, [x21, 3936]
	str	w1, [x21, 3932]
	str	w1, [x2, 1024]
	str	x20, [x22, 8]
.L1664:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1695:
	add	x23, x23, x0, sxtw 2
	add	x21, x22, 294912
	ldr	w0, [x23, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	ble	.L1700
.L1670:
	ldrsw	x0, [x21, 3820]
	add	x0, x1, x0, lsl 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	ble	.L1701
.L1672:
	ldrsw	x0, [x21, 3820]
	add	x0, x1, x0, lsl 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbnz	w3, .L1702
.L1674:
	ldr	w1, [x19, 2628]
	str	w1, [x19, 2616]
	str	w1, [x19, 2620]
	str	w1, [x19, 2624]
	b	.L1675
	.p2align 3
.L1694:
	add	x0, x20, 262144
	add	x26, x20, 270336
	add	x24, x22, 294912
	strb	w21, [x0, 1028]
	ldr	x0, [x22]
	ldr	w1, [x0, 632]
	str	w1, [x26, 2468]
	ldr	w0, [x0, 684]
	str	w0, [x26, 2488]
	ldr	w1, [x19, 2628]
	ldr	w0, [x24, 3928]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldrsw	x1, [x19, 5116]
	ldr	w0, [x24, 3928]
	add	x1, x23, x1, lsl 2
	ldr	w1, [x1, 196]
	bl	FSP_GetLogicFs
	mov	x27, x0
	ldrsw	x1, [x19, 5116]
	ldr	w0, [x24, 3928]
	add	x23, x23, x1, lsl 2
	ldr	w1, [x23, 196]
	bl	FSP_GetFsImagePtr
	mov	x1, x0
	cmp	x25, xzr
	ccmp	x27, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L1676
	ldr	x0, [x25, 32]
	cbz	x0, .L1703
	ldr	w0, [x0, 8]
	str	w0, [x26, 2440]
	ldr	x0, [x27, 32]
	cbz	x0, .L1704
.L1690:
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
	str	xzr, [x22, 8]
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
.L1699:
	ldr	x0, [x23, 32]
	b	.L1693
	.p2align 3
.L1698:
	ldr	x1, [x23, 32]
	b	.L1692
	.p2align 3
.L1697:
	ldr	x1, [x23, 32]
	b	.L1691
	.p2align 3
.L1676:
	ldr	x1, .LC104
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1664
	.p2align 3
.L1704:
	ldr	x0, [x25, 32]
	b	.L1690
.L1696:
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1664
.L1703:
	ldr	x1, .LC106
	mov	w0, w21
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1664
	.size	VP9_Set_DecParam, .-VP9_Set_DecParam
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
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
	bls	.L1707
	mov	w1, 8160
	sub	w4, w2, #32
	mov	w0, 8192
	cmp	w4, w1
	ccmp	w3, w0, 2, ls
	bls	.L1708
.L1707:
	ldr	x1, .LC110
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1709:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1708:
	ldr	x1, .LC112
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x0, [x20]
	ldr	w1, [x0, 764]
	cbnz	w1, .L1710
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	beq	.L1736
.L1711:
	ldr	w0, [x21, 2580]
	cbnz	w0, .L1716
	add	x19, x20, 294912
	ldr	x0, .LC115
	ldr	x4, .LC116
	mov	w1, 0
	mov	x2, 20
	ldrsw	x3, [x19, 3928]
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
	ldr	w0, [x19, 3928]
	strb	w2, [x29, 73]
	strb	w2, [x29, 75]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbz	w0, .L1737
.L1717:
	ldr	x1, .LC120
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1709
.L1710:
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	bne	.L1711
	ldr	w4, [x0, 724]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1735
	ldr	w5, [x0, 728]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bls	.L1715
.L1714:
	ldr	x1, .LC114
	mov	w0, 0
	ldr	w3, [x21, 2668]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1709
.L1716:
	add	x22, x20, 294912
	ldr	x23, .LC115
	ldr	x3, .LC116
	mov	w2, 1
	mov	w1, 0
	ldrsw	x0, [x22, 3928]
	ldr	x3, [x3, 96]
	ldr	w19, [x22, 3792]
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
	ldr	w0, [x22, 3928]
	csinc	w2, w2, wzr, ne
	strb	w2, [x29, 73]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbnz	w0, .L1717
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x22, 3928]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbnz	w0, .L1738
.L1720:
	ldrsw	x0, [x22, 3928]
	ldr	x0, [x23, x0, lsl 3]
	str	wzr, [x0, 1536]
.L1718:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21, 2580]
	b	.L1709
.L1735:
	ldr	w5, [x0, 728]
	b	.L1714
.L1736:
	ldr	w4, [x0, 724]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1735
	ldr	w5, [x0, 728]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bhi	.L1714
	ldr	w1, [x21, 2580]
	cmp	w1, 1
	beq	.L1739
.L1715:
	ldr	w22, [x0, 772]
	b	.L1711
.L1739:
	mov	w0, 0
	b	.L1709
	.p2align 3
.L1737:
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x19, 3928]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbz	w0, .L1718
	ldr	x1, .LC118
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1709
.L1738:
	ldr	x1, .LC122
	mov	w0, 2
	bl	dprint_vfmw
	b	.L1720
	.size	VP9_ArrangeVHBMem, .-VP9_ArrangeVHBMem
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
.LC115:
	.xword	s_pstVfmwChan
	.align	3
.LC116:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
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
	ldr	x23, .LC123
	add	x21, x21, 270336
	mov	x2, 36
	add	x1, x21, 2724
	mov	x0, x19
	ldr	x3, [x23, 104]
	ldr	w20, [x22, 988]
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 32
	add	x1, x21, 2796
	add	x0, x29, 72
	blr	x3
	ldr	w0, [x22, 1016]
	cmp	w0, 1
	beq	.L1757
.L1741:
	ldr	w0, [x22, 1104]
	sxtw	x6, w20
	cbz	w0, .L1748
	mov	w1, 0
	add	x5, x19, x6, lsl 2
	.p2align 2
.L1747:
	sxtw	x2, w1
	tbz	x0, 0, .L1745
	add	x3, x29, 144
	add	x3, x3, x2, lsl 2
	mov	x2, x3
	ldr	w4, [x3, -72]
	ldr	w3, [x19, w4, sxtw 2]
	cmp	w3, wzr
	sub	w3, w3, #1
	ble	.L1746
	str	w3, [x19, w4, sxtw 2]
.L1746:
	str	w20, [x2, -72]
	ldr	w2, [x5]
	add	w2, w2, 1
	str	w2, [x5]
.L1745:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1747
.L1748:
	add	x0, x29, 144
	mov	x1, 0
	add	x2, x0, x6, lsl 2
	mov	w0, 0
	ldr	w3, [x2, -40]
	sub	w3, w3, #1
	str	w3, [x2, -40]
	.p2align 2
.L1744:
	ldr	w2, [x19, x1]
	add	x1, x1, 4
	cmp	w2, wzr
	csinc	w0, w0, w0, eq
	cmp	x1, 36
	bne	.L1744
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1757:
	ldr	w0, [x19, w20, sxtw 2]
	ldr	w1, [x22, 1020]
	cmp	w0, wzr
	ble	.L1742
	sub	w0, w0, #1
	str	w0, [x19, w20, sxtw 2]
.L1742:
	ldr	w0, [x19, w1, sxtw 2]
	mov	w20, w1
	add	w0, w0, 1
	str	w0, [x19, w1, sxtw 2]
	b	.L1741
	.size	VP9_GetRefNum, .-VP9_GetRefNum
	.align	3
.LC123:
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
	ldr	x21, .LC124
	ldr	x20, .LC125
	mov	x2, 432
	mov	x0, x19
	ldr	x3, [x21, 104]
	mov	x1, x20
	blr	x3
	mov	x2, 432
	ldr	x3, [x21, 104]
	add	x1, x20, x2
	add	x0, x19, x2
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 864
	mov	x2, 432
	add	x0, x19, 864
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1296
	mov	x2, 432
	add	x0, x19, 1296
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_DefaultCoefProbs, .-Vp9_DefaultCoefProbs
	.align	3
.LC124:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC125:
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
	bl	_mcount
	ldr	x21, .LC126
	ldr	x20, .LC127
	mov	x2, 90
	add	x0, x19, 1764
	ldr	x3, [x21, 104]
	add	x1, x20, 1728
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1820
	mov	x2, 36
	add	x0, x19, 1728
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1856
	mov	x2, 8
	add	x0, x19, 1950
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1864
	mov	x2, 96
	add	x0, x19, 1854
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1960
	mov	x2, 4
	add	x0, x19, 1979
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1968
	mov	x2, 5
	add	x0, x19, 1983
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1976
	mov	x2, 5
	add	x0, x19, 1998
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 1984
	mov	x2, 10
	add	x0, x19, 1988
	blr	x3
	ldr	x3, .LC128
	add	x0, x19, 2003
	ldr	x4, [x21, 104]
	add	x1, x20, 2000
	mov	x2, 3
	ldr	x5, [x3, 800]
	ldr	w3, [x3, 808]
	str	x5, [x0]
	str	w3, [x0, 8]
	add	x0, x19, 2015
	blr	x4
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_InitMbmodeProbs, .-Vp9_InitMbmodeProbs
	.align	3
.LC126:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC127:
	.xword	.LANCHOR1
	.align	3
.LC128:
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
	ldr	x1, .LC129
	add	x0, x19, 2018
	add	x2, x19, 2079
	add	x3, x1, 873
	add	x1, x1, 812
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
.LC129:
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
	mov	w22, w5
	mov	x21, x1
	mov	x23, x2
	bl	_mcount
	mov	x0, x20
	bl	Vp9_DefaultCoefProbs
	mov	x0, x20
	bl	Vp9_InitMbmodeProbs
	ldr	x0, .LC134
	add	x6, x20, 2018
	add	x4, x20, 2079
	mov	x2, 21
	add	x7, x0, 812
	add	x0, x0, 873
	ldr	x5, [x0]
	ldr	x0, .LC135
	ldp	x8, x9, [x7, 16]
	stp	x8, x9, [x6, 16]
	ldr	x3, [x0, 104]
	ldp	x8, x9, [x7, 32]
	ldp	x0, x1, [x7]
	stp	x0, x1, [x6]
	stp	x8, x9, [x6, 32]
	ldr	x1, .LC136
	add	x0, x20, 1958
	ldp	x8, x9, [x7, 48]
	stp	x8, x9, [x6, 48]
	add	x1, x1, 2004
	str	x5, [x4]
	blr	x3
	cmp	w24, wzr
	ccmp	w19, 3, 4, eq
	ccmp	w22, wzr, 4, ne
	beq	.L1767
	cmp	w19, 2
	beq	.L1768
	str	wzr, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1767:
	mov	x19, 0
	mov	x22, 8348
	.p2align 2
.L1763:
	add	x0, x21, x19
	mov	x2, 2087
	mov	x1, x20
	add	x19, x19, x2
	bl	memcpy
	cmp	x19, x22
	bne	.L1763
	str	wzr, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1768:
	ldr	w0, [x23]
	mov	w3, 2087
	mov	x1, x20
	mov	x2, 2087
	umull	x0, w0, w3
	add	x0, x21, x0
	bl	memcpy
	str	wzr, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_SetupPastIndependence, .-Vp9_SetupPastIndependence
	.align	3
.LC134:
	.xword	.LANCHOR0
	.align	3
.LC135:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC136:
	.xword	.LANCHOR1
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
	cbz	w0, .L1771
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
.L1771:
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
	ldr	x3, .LC141
	asr	w19, w26, 5
	add	x23, x27, 80
	add	x24, x27, 18
	add	x28, x27, 112
	mov	w21, 63
	add	x25, x20, 6
	.p2align 2
.L1780:
	ldrb	w0, [x27]
	mov	w1, w26
	cbz	w0, .L1775
	ldr	w0, [x23]
	tbz	x0, 1, .L1775
	ldrsh	w1, [x24]
	ldrb	w2, [x27, 3]
	add	w0, w1, w26
	cmp	w2, 1
	csel	w1, w0, w1, ne
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 63
	csel	w1, w1, w21, le
.L1775:
	ldrb	w0, [x20]
	cbz	w0, .L1789
	ldrsb	w2, [x20, 2]
	add	x5, x20, 3
	mov	x0, x22
	lsl	w2, w2, w19
	adds	w2, w2, w1
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	strb	w2, [x22]
.L1779:
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
	bne	.L1779
	add	x23, x23, 4
	add	x22, x22, 8
	cmp	x28, x23
	add	x24, x24, 8
	bne	.L1780
.L1790:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1789:
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
	bne	.L1780
	b	.L1790
	.size	Vp9_Vfmw_LoopFilterFrameInit, .-Vp9_Vfmw_LoopFilterFrameInit
	.align	3
.LC141:
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
	add	x9, x20, 294912
	mov	w4, 1048576
	ldr	w0, [x1, 2876]
	ldr	w3, [x1, 2880]
	ubfiz	w0, w0, 10, 3
	ldr	w2, [x1, 5092]
	ubfiz	w3, w3, 13, 2
	ldr	w5, [x1, 5164]
	orr	w3, w3, w0
	ldr	w0, [x1, 5088]
	and	w2, w2, 1
	ubfiz	w0, w0, 1, 2
	orr	w0, w0, w2
	ldr	w2, [x1, 5152]
	orr	w0, w3, w0
	ubfiz	w3, w2, 15, 4
	ldr	w2, [x1, 5168]
	ubfiz	w2, w2, 9, 1
	orr	w2, w3, w2
	orr	w3, w0, w2
	ldr	w2, [x1, 5192]
	ubfiz	w0, w5, 8, 1
	ldr	w5, [x1, 5124]
	ubfiz	w2, w2, 7, 1
	orr	w0, w0, w2
	ldr	w2, [x1, 5132]
	orr	w0, w3, w0
	ubfiz	w3, w2, 6, 1
	ldr	w2, [x1, 5128]
	ubfiz	w2, w2, 5, 1
	orr	w2, w3, w2
	orr	w3, w0, w2
	ldr	w2, [x1, 5120]
	ubfiz	w0, w5, 4, 1
	ubfiz	w2, w2, 3, 1
	orr	w0, w0, w2
	orr	w0, w3, w0
	str	w0, [x19]
	ldr	w2, [x1, 5136]
	ldr	w0, [x9, 3812]
	cmp	w2, w0
	beq	.L1833
.L1797:
	add	x5, x1, 2644
	ldr	w0, [x1, 5204]
	ldr	w2, [x5, 76]
	mov	w10, 0
	ldr	w3, [x5, 184]
	and	w0, w0, 7
	ubfiz	w2, w2, 7, 1
	orr	w4, w0, w4
	ubfiz	w3, w3, 8, 4
	ldr	w0, [x5, 192]
	orr	w3, w3, w2
	ldr	w2, [x5, 188]
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
	orr	w0, w0, w4
	str	w0, [x19, 4]
	ldr	w0, [x1, 5140]
	ldr	w3, [x1, 5136]
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
.L1798:
	lsl	w4, w10, 1
	mov	w6, 0
	sbfiz	x11, x10, 2, 32
	add	x4, x19, x4, sxtw 2
.L1799:
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
	bne	.L1799
	add	w10, w10, 1
	cmp	w10, 8
	bne	.L1798
	ldr	w4, [x5, 252]
	mov	w2, 268435456
	ldr	w5, [x1, 2892]
	add	x3, x1, 2644
	cmp	w4, wzr
	sxtw	x6, w4
	csel	w7, wzr, w2, ge
	cmp	w5, wzr
	mov	w2, 1048576
	eor	x4, x6, x6, asr 63
	csel	w2, wzr, w2, ge
	sub	x4, x4, x6, asr 63
	sxtw	x6, w5
	ubfiz	w5, w4, 24, 4
	orr	w2, w7, w2
	eor	x0, x6, x6, asr 63
	sub	x0, x0, x6, asr 63
	ldrb	w6, [x1, 2884]
	ubfiz	w0, w0, 16, 4
	orr	w4, w0, w5
	ldr	w5, [x1, 2888]
	cmp	w5, wzr
	sxtw	x5, w5
	eor	x0, x5, x5, asr 63
	sub	x0, x0, x5, asr 63
	ubfiz	w0, w0, 8, 4
	orr	w0, w0, w6
	orr	w0, w0, w4
	orr	w0, w0, w2
	mov	w2, 4096
	csel	w2, wzr, w2, ge
	orr	w0, w0, w2
	str	w0, [x19, 80]
	ldrb	w5, [x3, 2565]
	ldrb	w0, [x3, 2568]
	ldrb	w4, [x3, 2567]
	ldrb	w2, [x3, 2564]
	ubfiz	w0, w0, 3, 1
	ubfiz	w3, w4, 2, 1
	ubfiz	w4, w5, 1, 1
	and	w2, w2, 1
	orr	w0, w0, w3
	orr	w2, w4, w2
	add	x5, x20, 274432
	orr	w0, w0, w2
	add	x4, x5, 1192
	mov	w2, 0
	mov	w3, 0
	str	w0, [x19, 84]
	.p2align 2
.L1804:
	ldr	w0, [x4], 4
	and	w0, w0, 15
	lsl	w0, w0, w2
	add	w2, w2, 4
	cmp	w2, 32
	orr	w3, w3, w0
	bne	.L1804
	str	w3, [x19, 88]
	mov	x0, 0
	mov	w3, 0
	ldrh	w4, [x1, 5240]
	ldrh	w2, [x1, 5232]
	ubfiz	w4, w4, 18, 9
	ubfiz	w2, w2, 9, 9
	orr	w4, w4, w2
	ldrh	w2, [x1, 5224]
	and	w2, w2, 511
	orr	w2, w2, w4
	str	w2, [x19, 92]
	ldrh	w4, [x1, 5264]
	ldrh	w2, [x1, 5256]
	ubfiz	w4, w4, 18, 9
	ubfiz	w2, w2, 9, 9
	orr	w4, w4, w2
	ldrh	w2, [x1, 5248]
	and	w2, w2, 511
	orr	w2, w2, w4
	str	w2, [x19, 96]
	ldrh	w2, [x1, 5280]
	ubfiz	w4, w2, 9, 9
	ldrh	w2, [x1, 5272]
	and	w2, w2, 511
	orr	w2, w4, w2
	str	w2, [x19, 100]
.L1805:
	add	x2, x0, 274432
	add	x2, x2, 1130
	ldrb	w2, [x20, x2]
	lsl	w2, w2, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w3, w3, w2
	bne	.L1805
	str	w3, [x19, 104]
	mov	x0, 0
	mov	w3, 0
.L1806:
	add	x2, x0, 274432
	add	x2, x2, 1162
	ldrb	w2, [x20, x2]
	lsl	w2, w2, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w3, w3, w2
	bne	.L1806
	add	x5, x5, 1132
	mov	w4, 0
	mov	w6, 0
	str	w3, [x19, 108]
	.p2align 2
.L1807:
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
	bne	.L1807
	str	w6, [x19, 112]
	ldr	w2, [x1, 2592]
	str	w2, [x19, 116]
	ldr	w0, [x1, 2608]
	str	w0, [x19, 120]
	ldr	w0, [x1, 2680]
	str	w0, [x19, 128]
	ldr	w0, [x1, 2684]
	str	w0, [x19, 132]
	ldr	w0, [x1, 2688]
	str	w0, [x19, 136]
	ldr	w0, [x1, 2692]
	str	w0, [x19, 140]
	ldr	w0, [x1, 5464]
	ldrh	w2, [x1, 5468]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 180]
	ldr	w0, [x1, 5480]
	ldrh	w2, [x1, 5484]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 184]
	ldr	w0, [x1, 5496]
	ldrh	w2, [x1, 5500]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 188]
	ldr	w2, [x1, 5492]
	ldr	w3, [x1, 5508]
	ldr	w0, [x1, 5476]
	ubfiz	w2, w2, 8, 6
	ubfiz	w3, w3, 16, 6
	orr	w2, w3, w2
	and	w0, w0, 63
	orr	w0, w0, w2
	str	w0, [x19, 192]
	ldr	w2, [x1, 5488]
	ldr	w3, [x1, 5504]
	ldr	w0, [x1, 5472]
	ubfiz	w2, w2, 8, 6
	ubfiz	w3, w3, 16, 6
	orr	w2, w3, w2
	and	w0, w0, 63
	orr	w0, w0, w2
	str	w0, [x19, 196]
	ldr	w0, [x1, 2828]
	cmp	w0, 8
	bls	.L1808
	str	wzr, [x19, 200]
.L1809:
	ldr	w0, [x1, 2832]
	cmp	w0, 8
	bls	.L1810
	str	wzr, [x19, 204]
.L1811:
	ldr	w0, [x1, 2836]
	cmp	w0, 8
	bls	.L1812
	str	wzr, [x19, 208]
.L1813:
	ldr	w0, [x9, 3816]
	ldrh	w2, [x9, 3812]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 212]
	ldr	w0, [x1, 2828]
	cmp	w0, 8
	bls	.L1814
	stp	wzr, wzr, [x19, 216]
	str	wzr, [x19, 224]
.L1815:
	ldr	w0, [x1, 2832]
	cmp	w0, 8
	bls	.L1817
	stp	wzr, wzr, [x19, 228]
	str	wzr, [x19, 236]
	ldr	w0, [x1, 2836]
	cmp	w0, 8
	bhi	.L1834
.L1820:
	add	x0, x20, x0, sxtw 4
	add	x21, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 1232]
	add	w1, w1, 255
	and	w1, w1, -256
	lsl	w1, w1, 4
	mul	w1, w1, w22
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	asr	w1, w1, 3
	str	w1, [x19, 240]
	ldr	w3, [x0, 1232]
	ldr	w4, [x0, 1236]
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
	beq	.L1835
.L1822:
	str	w1, [x19, 244]
	ldr	w1, [x0, 1232]
	ldr	w3, [x0, 1236]
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
.L1817:
	add	x0, x20, x0, sxtw 4
	add	x6, x21, 270336
	add	x3, x0, 274432
	ldr	w0, [x3, 1232]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 228]
	ldr	w4, [x3, 1232]
	ldr	w5, [x3, 1236]
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
	beq	.L1836
.L1819:
	str	w0, [x19, 232]
	ldr	w0, [x3, 1232]
	ldr	w4, [x3, 1236]
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
	bls	.L1820
.L1834:
	stp	wzr, wzr, [x19, 240]
	str	wzr, [x19, 248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1814:
	add	x0, x20, x0, sxtw 4
	add	x6, x21, 270336
	add	x3, x0, 274432
	ldr	w0, [x3, 1232]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w2, w0, 7
	csel	w0, w2, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 216]
	ldr	w4, [x3, 1232]
	ldr	w5, [x3, 1236]
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
	beq	.L1837
.L1816:
	str	w0, [x19, 220]
	ldr	w0, [x3, 1232]
	ldr	w4, [x3, 1236]
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
	b	.L1815
	.p2align 3
.L1812:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 1232]
	str	w2, [x3, 2528]
	and	w2, w2, 65535
	ldr	w0, [x0, 1236]
	str	w0, [x3, 2540]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 208]
	b	.L1813
	.p2align 3
.L1810:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 1232]
	str	w2, [x3, 2524]
	and	w2, w2, 65535
	ldr	w0, [x0, 1236]
	str	w0, [x3, 2536]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 204]
	b	.L1811
	.p2align 3
.L1808:
	add	x0, x20, x0, sxtw 4
	add	x3, x21, 270336
	add	x0, x0, 274432
	ldr	w2, [x0, 1232]
	str	w2, [x3, 2520]
	and	w2, w2, 65535
	ldr	w0, [x0, 1236]
	str	w0, [x3, 2532]
	orr	w0, w2, w0, lsl 16
	str	w0, [x19, 200]
	b	.L1809
	.p2align 3
.L1833:
	ldr	w2, [x1, 5140]
	ldr	w0, [x9, 3816]
	cmp	w2, w0
	csel	w4, w4, wzr, ne
	b	.L1797
	.p2align 3
.L1835:
	ldr	w2, [x21, 2472]
	cbnz	w2, .L1822
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
	b	.L1822
.L1836:
	ldr	w2, [x6, 2472]
	cbnz	w2, .L1819
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
	b	.L1819
.L1837:
	ldr	w2, [x6, 2472]
	cbnz	w2, .L1816
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
	b	.L1816
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
	beq	.L1839
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w0, w0, w1
.L1840:
	str	w0, [x20, 24]
	ldrh	w2, [x19, 28]
	ldrh	w0, [x19, 30]
	add	w1, w2, 7
	cmp	w2, w0
	ubfx	x1, x1, 3, 7
	lsl	w1, w1, 16
	orr	w2, w1, 255
	beq	.L1842
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w2, w0, w1
.L1842:
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
.L1839:
	orr	w0, w1, 255
	b	.L1840
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
	add	x19, x0, 270336
	mov	x20, x0
	mov	x0, x30
	mov	x26, x1
	str	x20, [x29, 136]
	bl	_mcount
	ldr	w28, [x19, 5176]
	ldr	w0, [x19, 5184]
	mov	w2, 1
	mov	x3, x20
	add	x1, x20, 16
	mov	w4, w0
	ldr	w0, [x19, 5188]
	ldrsw	x22, [x26, 24]
	mov	w5, w0
	str	w5, [x29, 112]
	lsl	w5, w2, w5
	lsl	w2, w2, w4
	str	w2, [x29, 212]
	add	x2, x3, 294912
	mov	x21, x2
	ldr	w2, [x19, 5180]
	mov	x0, x20
	ldr	x27, [x26]
	mov	w20, w5
	str	w4, [x29, 180]
	str	w5, [x29, 116]
	add	x22, x27, x22
	str	w2, [x29, 120]
	str	x21, [x29, 128]
	bl	Vp9_SetPoolInfoFrame
	str	wzr, [x21, 3936]
	cmp	w20, wzr
	ldr	w0, [x19, 2568]
	ldr	x1, [x19, 2560]
	and	w0, w0, 15
	str	x1, [x29, 160]
	str	w0, [x29, 168]
	ble	.L1854
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
.L1853:
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
	ble	.L1846
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
	add	x0, x0, 274432
	str	x0, [x29, 184]
	b	.L1852
	.p2align 3
.L1865:
	ldr	w2, [x29, 148]
	ldr	w3, [x29, 156]
	cmp	w2, w3
	bgt	.L1847
.L1849:
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
	cbnz	w1, .L1862
	ldr	x0, [x29, 184]
	ldr	w5, [x0, 2048]
	cmp	w4, w5
	bgt	.L1863
.L1851:
	ldr	w2, [x26, 24]
	ldr	w0, [x29, 212]
	sub	w2, w2, w4
	str	w2, [x26, 24]
	cmp	w0, w25
	beq	.L1864
.L1852:
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
	bge	.L1865
.L1847:
	cmp	x24, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L1856
	cmp	x22, x10
	ccmp	x10, x24, 0, cs
	mov	x24, x10
	bls	.L1856
	mov	x0, x26
	bl	BsGet
	mov	w4, w0
	mov	x0, x24
	b	.L1849
	.p2align 3
.L1862:
	ldr	x27, [x29, 128]
	add	x3, x29, 232
	str	w4, [x29, 152]
	ldr	x4, [x29, 136]
	ldr	w2, [x27, 3936]
	mov	x0, x4
	str	w10, [x29, 216]
	ubfiz	x1, x2, 8, 32
	add	x1, x1, 1040
	add	x1, x4, x1
	bl	Vp9_SetPoolInfoTile
	ldr	w0, [x27, 3936]
	ldr	w4, [x29, 152]
	add	w0, w0, 1
	str	w0, [x27, 3936]
	ldr	x0, [x29, 184]
	ldr	w10, [x29, 216]
	ldr	w5, [x0, 2048]
	cmp	w4, w5
	ble	.L1851
.L1863:
	ldr	x2, .LC142
	mov	w3, 4530
	ldr	x1, .LC144
	mov	w0, 0
	add	x2, x2, 888
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
.L1856:
	mov	w0, -1
.L1845:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L1864:
	mov	w28, w23
	mov	x27, x24
	mov	w21, w10
.L1846:
	ldr	w0, [x29, 156]
	ldr	w1, [x29, 116]
	add	w0, w0, 1
	str	w0, [x29, 156]
	cmp	w0, w1
	bne	.L1853
.L1854:
	mov	w0, 0
	b	.L1845
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
	.align	3
.LC142:
	.xword	.LANCHOR0
	.align	3
.LC144:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_TxCoefProbConvert2
	.type	Vp9_TxCoefProbConvert2, %function
Vp9_TxCoefProbConvert2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x20, .LC145
	mov	x1, x21
	mov	x2, 18
	mov	x0, x19
	add	x22, x21, 108
	ldr	x3, [x20, 104]
	blr	x3
	mov	x2, 18
	ldr	x3, [x20, 104]
	add	x1, x21, x2
	add	x0, x19, 32
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 36
	mov	x2, 18
	add	x0, x19, 64
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 54
	mov	x2, 18
	add	x0, x19, 96
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 72
	mov	x2, 18
	add	x0, x19, 128
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 90
	mov	x2, 18
	add	x0, x19, 160
	blr	x3
	ldr	x3, [x20, 104]
	mov	x1, x22
	mov	x2, 18
	add	x0, x19, 192
	blr	x3
	ldr	x3, [x20, 104]
	mov	x1, x22
	mov	x2, 18
	add	x0, x19, 256
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 126
	mov	x2, 18
	add	x0, x19, 288
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 144
	mov	x2, 18
	add	x0, x19, 320
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 162
	mov	x2, 18
	add	x0, x19, 352
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 180
	mov	x2, 18
	add	x0, x19, 384
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 198
	mov	x2, 18
	add	x0, x19, 416
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 216
	mov	x2, 18
	add	x0, x19, 448
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_TxCoefProbConvert2, .-Vp9_TxCoefProbConvert2
	.align	3
.LC145:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ProbBurstConvert
	.type	Vp9_ProbBurstConvert, %function
Vp9_ProbBurstConvert:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x21, x2
	mov	w22, w3
	mov	w23, w4
	bl	_mcount
	mov	x1, x19
	mov	x0, x20
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 216
	add	x0, x20, 512
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 432
	add	x0, x20, 1024
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 648
	add	x0, x20, 1536
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 864
	add	x0, x20, 2048
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 1080
	add	x0, x20, 2560
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 1296
	add	x0, x20, 3072
	bl	Vp9_TxCoefProbConvert2
	add	x1, x19, 1512
	add	x0, x20, 3584
	bl	Vp9_TxCoefProbConvert2
	add	x10, x20, 4096
	add	x11, x19, 1729
	add	x9, x19, 1765
	mov	w7, 0
.L1868:
	ldrb	w6, [x11, -1]
	add	x8, x11, 8
	mov	x1, x11
	mov	w0, 8
	.p2align 2
.L1872:
	cmp	x8, x1
	beq	.L1923
.L1870:
	ldrb	w5, [x1]
	add	x1, x1, 1
	lsl	w5, w5, w0
	add	w0, w0, 8
	cmp	w0, 32
	orr	w6, w6, w5
	bne	.L1872
	str	w6, [x10, w7, uxtw 2]
	cmp	x8, x1
	mov	w0, 0
	add	w7, w7, 1
	mov	w6, 0
	bne	.L1870
.L1923:
	add	x11, x11, 9
	str	w6, [x10, w7, uxtw 2]
	cmp	x11, x9
	add	w7, w7, 2
	bne	.L1868
	add	x2, x19, 1855
	.p2align 2
.L1875:
	ldrb	w6, [x9, -1]
	add	x8, x9, 8
	mov	x1, x9
	mov	w0, 8
	.p2align 2
.L1877:
	cmp	x1, x8
	beq	.L1924
.L1874:
	ldrb	w5, [x1]
	add	x1, x1, 1
	lsl	w5, w5, w0
	add	w0, w0, 8
	cmp	w0, 32
	orr	w6, w6, w5
	bne	.L1877
	str	w6, [x10, w7, uxtw 2]
	cmp	x1, x8
	mov	w0, 0
	add	w7, w7, 1
	mov	w6, 0
	bne	.L1874
.L1924:
	add	x9, x9, 9
	str	w6, [x10, w7, uxtw 2]
	cmp	x9, x2
	add	w7, w7, 2
	bne	.L1875
	ldr	w0, [x21, 5]
	cmp	w23, wzr
	str	w0, [x20, 4352]
	csel	w6, w22, wzr, eq
	add	x7, x6, 1
	lsl	x0, x6, 2
	ldrb	w1, [x21, 11]
	sub	x6, x0, x6
	ldrb	w2, [x21, 10]
	lsl	x0, x7, 2
	ldrb	w3, [x21, 9]
	sub	x7, x0, x7
	lsl	w2, w2, 8
	add	x5, x10, 256
	orr	w1, w2, w1, lsl 16
	mov	w4, 3
	orr	w0, w3, w1
	str	w0, [x20, 4356]
	add	x6, x19, x6, lsl 4
	add	x7, x19, x7, lsl 4
	ldrb	w2, [x21, 14]
	mov	w1, 0
	ldrb	w0, [x21, 13]
	ldrb	w3, [x21, 12]
	lsl	w0, w0, 8
	orr	w0, w0, w2, lsl 16
	orr	w0, w3, w0
	mov	w3, 0
	str	w0, [x20, 4360]
	.p2align 2
.L1879:
	mov	x0, 0
.L1881:
	add	x2, x6, x0
	add	x0, x0, 1
	ldrb	w2, [x2, 1854]
	lsl	w2, w2, w1
	add	w1, w1, 8
	cmp	w1, 32
	orr	w3, w3, w2
	beq	.L1925
.L1880:
	cmp	x0, 3
	bne	.L1881
	add	x6, x6, 3
	cmp	x7, x6
	bne	.L1879
	ldrb	w2, [x19, 2017]
	add	x0, x19, 2048
	ldrb	w1, [x19, 2016]
	add	w6, w4, 1
	ldrb	w3, [x19, 2015]
	add	w7, w4, 2
	lsl	w1, w1, 8
	add	w9, w4, 4
	orr	w1, w1, w2, lsl 16
	add	w8, w4, 6
	orr	w1, w3, w1
	str	w1, [x5, w4, uxtw 2]
	ldrb	w2, [x19, 2010]
	ldrb	w3, [x19, 2009]
	ldrh	w1, [x0, -35]
	lsl	w3, w3, 16
	orr	w2, w3, w2, lsl 24
	orr	w1, w2, w1
	str	w1, [x5, w6, uxtw 2]
	add	w6, w4, 3
	ldrb	w2, [x19, 2004]
	ldrb	w3, [x19, 2003]
	ldrh	w1, [x0, -37]
	lsl	w3, w3, 16
	orr	w2, w3, w2, lsl 24
	orr	w1, w2, w1
	str	w1, [x5, w7, uxtw 2]
	add	w1, w4, 5
	add	w7, w4, 7
	ldr	w2, [x0, -43]
	str	w2, [x5, w6, uxtw 2]
	add	w6, w4, 8
	ldr	w2, [x0, -69]
	str	w2, [x5, w9, uxtw 2]
	ldr	w2, [x0, -65]
	str	w2, [x5, w1, uxtw 2]
	ldrb	w1, [x19, 2000]
	ldrb	w3, [x19, 1999]
	ldrb	w2, [x19, 1998]
	lsl	w3, w3, 16
	orr	w3, w3, w1, lsl 24
	ldrb	w1, [x19, 1987]
	orr	w1, w1, w2, lsl 8
	add	w2, w4, 9
	orr	w1, w3, w1
	str	w1, [x5, w8, uxtw 2]
	add	w8, w4, 10
	mov	w1, 1
	ldrh	w0, [x0, -47]
	add	w4, w4, 11
	str	w0, [x5, w7, uxtw 2]
	mov	w3, 0
	mov	w7, 0
	ldr	w0, [x19, 1988]
	str	w0, [x5, w6, uxtw 2]
	mov	w0, 0
	ldr	w6, [x19, 1992]
	str	w6, [x5, w2, uxtw 2]
	ldrb	w2, [x19, 1958]
	ldrb	w6, [x19, 1997]
	lsl	w6, w6, 8
	orr	w2, w6, w2, lsl 16
	ldrb	w6, [x19, 1996]
	orr	w2, w6, w2
	str	w2, [x5, w8, uxtw 2]
	.p2align 2
.L1883:
	sxtw	x6, w7
	add	x2, x19, x6, lsl 2
	sub	x6, x2, x6
	b	.L1885
	.p2align 3
.L1884:
	cmp	w1, 2
	bgt	.L1926
.L1885:
	add	x2, x6, x1, sxtw
	add	w1, w1, 1
	ldrb	w2, [x2, 1958]
	lsl	w2, w2, w0
	add	w0, w0, 8
	cmp	w0, 32
	orr	w3, w3, w2
	bne	.L1884
	str	w3, [x5, w4, uxtw 2]
	cmp	w1, 2
	mov	w0, 0
	add	w4, w4, 1
	mov	w3, 0
	ble	.L1885
.L1926:
	add	w7, w7, 1
	mov	w1, 0
	cmp	w7, 7
	bne	.L1883
	add	x1, x19, 1950
	add	x7, x19, 1958
	mov	w0, 0
	mov	w2, 0
.L1887:
	add	w6, w0, 8
	ldrb	w3, [x1]
	cmp	w6, 32
	lsl	w3, w3, w0
	add	w0, w0, 16
	orr	w2, w3, w2
	beq	.L1927
	ldrb	w3, [x1, 1]
	cmp	w0, 32
	lsl	w3, w3, w6
	orr	w2, w3, w2
	bne	.L1890
	str	w2, [x5, w4, uxtw 2]
	mov	w0, 0
	add	w4, w4, 1
	mov	w2, 0
.L1890:
	add	x1, x1, 2
	cmp	x7, x1
	bne	.L1887
	ldrb	w0, [x19, 2054]
	add	w9, w4, 1
	ldrb	w1, [x19, 2021]
	add	w7, w4, 2
	add	x6, x19, 2032
	add	x8, x19, 2098
	orr	w0, w1, w0, lsl 8
	str	w0, [x5, w4, uxtw 2]
	mov	w3, 0
	mov	w0, 0
	ldrb	w1, [x19, 2020]
	ldrb	w2, [x19, 2019]
	lsl	w2, w2, 8
	orr	w1, w2, w1, lsl 16
	ldrb	w2, [x19, 2018]
	orr	w1, w2, w1
	str	w1, [x5, w9, uxtw 2]
.L1892:
	sub	x1, x6, #10
	b	.L1894
	.p2align 3
.L1893:
	cmp	x1, x6
	beq	.L1928
.L1894:
	ldrb	w2, [x1]
	add	x1, x1, 1
	lsl	w2, w2, w0
	add	w0, w0, 8
	cmp	w0, 32
	orr	w3, w3, w2
	bne	.L1893
	str	w3, [x5, w7, uxtw 2]
	cmp	x1, x6
	mov	w0, 0
	add	w7, w7, 1
	mov	w3, 0
	bne	.L1894
.L1928:
	add	x6, x1, 33
	cmp	x8, x6
	bne	.L1892
	ldrb	w1, [x19, 2065]
	add	w4, w7, 1
	ldrb	w2, [x19, 2032]
	add	x6, x19, 2043
	add	x8, x19, 2109
	mov	w0, 0
	orr	w1, w2, w1, lsl 8
	mov	w3, 0
	str	w1, [x5, w7, uxtw 2]
.L1896:
	sub	x1, x6, #10
	b	.L1898
	.p2align 3
.L1897:
	cmp	x1, x6
	beq	.L1929
.L1898:
	ldrb	w2, [x1]
	add	x1, x1, 1
	lsl	w2, w2, w0
	add	w0, w0, 8
	cmp	w0, 32
	orr	w3, w3, w2
	bne	.L1897
	str	w3, [x5, w4, uxtw 2]
	cmp	x1, x6
	mov	w0, 0
	add	w4, w4, 1
	mov	w3, 0
	bne	.L1898
.L1929:
	add	x6, x1, 33
	cmp	x6, x8
	bne	.L1896
	mov	x8, x19
	add	x9, x19, 66
	mov	w1, 0
	mov	w3, 0
.L1903:
	mov	x6, x8
	mov	w7, 2
.L1905:
	mov	x0, 0
.L1901:
	add	x2, x6, x0
	add	x0, x0, 1
	ldrb	w2, [x2, 2043]
	lsl	w2, w2, w1
	add	w1, w1, 8
	cmp	w1, 32
	orr	w3, w3, w2
	beq	.L1930
.L1900:
	cmp	x0, 3
	bne	.L1901
	subs	w7, w7, #1
	add	x6, x6, 3
	bne	.L1905
	add	x8, x8, 33
	cmp	x9, x8
	bne	.L1903
	ldrb	w1, [x19, 2051]
	add	w2, w4, 1
	ldrb	w0, [x19, 2050]
	add	w6, w4, 2
	ldrb	w3, [x19, 2049]
	lsl	w0, w0, 8
	orr	w0, w0, w1, lsl 16
	orr	w0, w3, w0
	str	w0, [x5, w4, uxtw 2]
	ldrb	w1, [x19, 2084]
	ldrb	w0, [x19, 2083]
	ldrb	w3, [x19, 2082]
	lsl	w0, w0, 8
	orr	w0, w0, w1, lsl 16
	orr	w0, w3, w0
	str	w0, [x5, w2, uxtw 2]
	ldrb	w2, [x19, 2086]
	ldrb	w3, [x19, 2053]
	ldrb	w1, [x19, 2085]
	ldrb	w0, [x19, 2052]
	lsl	w3, w3, 16
	orr	w2, w3, w2, lsl 24
	orr	w0, w0, w1, lsl 8
	orr	w0, w2, w0
	str	w0, [x5, w6, uxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1925:
	str	w3, [x5, w4, uxtw 2]
	mov	w1, 0
	add	w4, w4, 1
	mov	w3, 0
	b	.L1880
	.p2align 3
.L1930:
	str	w3, [x5, w4, uxtw 2]
	mov	w1, 0
	add	w4, w4, 1
	mov	w3, 0
	b	.L1900
	.p2align 3
.L1927:
	str	w2, [x5, w4, uxtw 2]
	mov	w0, 8
	add	w4, w4, 1
	ldrb	w2, [x1, 1]
	b	.L1890
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
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
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 270336
	add	x19, x21, 294912
	mov	x25, x1
	mov	w22, w2
	bl	_mcount
	str	wzr, [x29, 124]
	ldr	w23, [x20, 5092]
	mov	w2, w22
	ldr	w0, [x20, 5172]
	mov	x1, x25
	cmp	w23, wzr
	ldr	w3, [x20, 5196]
	ldr	w27, [x20, 2696]
	add	x28, x21, 274432
	ldr	w26, [x20, 2704]
	add	x24, x28, 2064
	str	w23, [x19, 3904]
	stp	w0, wzr, [x29, 116]
	cset	w0, eq
	str	w0, [x19, 3892]
	str	w3, [x29, 108]
	ldr	w0, [x20, 5124]
	str	w0, [x19, 3912]
	add	x0, x29, 128
	ldr	w5, [x20, 5192]
	str	w5, [x19, 3896]
	ldr	w5, [x20, 5168]
	str	w5, [x19, 3916]
	ldr	w4, [x20, 2700]
	str	w4, [x19, 3920]
	ldr	w4, [x20, 5204]
	str	w4, [x19, 3924]
	ldr	w4, [x20, 5088]
	str	w4, [x19, 3908]
	bl	BsInit
	ldr	w0, [x19, 3892]
	ldr	w4, [x19, 3912]
	ldr	w3, [x29, 108]
	cbnz	w0, .L1933
	cbz	w4, .L1942
.L1933:
	add	x1, x21, 278528
	add	x2, x29, 116
	add	x1, x1, 55
	mov	x0, x24
	mov	w5, w23
	bl	Vp9_SetupPastIndependence
	ldr	x0, .LC146
	mov	x2, 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x20, 2708
	blr	x3
.L1934:
	ldr	w3, [x29, 116]
	mov	x2, 2087
	add	x0, x28, 2064
	lsl	x1, x3, 8
	add	x1, x1, x3, lsl 2
	add	x1, x1, x3
	add	x1, x21, x1, lsl 3
	sub	x1, x1, x3
	add	x1, x1, 278528
	add	x1, x1, 55
	bl	memcpy
	add	x0, x29, 128
	bl	Vp9_Cabac_ReaderInit
	add	x0, x29, 124
	ldr	w3, [x19, 3896]
	ldr	w5, [x19, 3920]
	mov	w7, w27
	ldr	w4, [x19, 3924]
	mov	w6, w26
	str	x0, [sp, 8]
	add	x0, x29, 120
	mov	w2, w23
	str	x0, [sp]
	mov	x1, x24
	add	x0, x29, 128
	bl	Vp9_ReadCompressedHeader
	cbnz	w0, .L1943
	add	x2, x20, 2644
	ldp	w1, w0, [x29, 120]
	add	x23, x2, 2564
	str	w0, [x2, 232]
	str	w0, [x19, 3900]
	str	w1, [x2, 236]
	ldr	w3, [x2, 344]
	cbnz	w3, .L1944
.L1938:
	ldr	w4, [x19, 3896]
	add	x0, x21, 262144
	ldr	w3, [x20, 5092]
	mov	x2, x23
	mov	x1, x24
	add	x0, x0, 1045
	bl	Vp9_ProbBurstConvert
	ldr	w2, [x20, 2652]
	add	x1, x29, 128
	mov	x0, x21
	sub	w22, w22, w2
	str	w22, [x29, 152]
	add	x25, x25, x2, uxtw
	str	x25, [x29, 128]
	bl	Vp9_DecodeTilesCtrl
	mov	w0, 0
.L1936:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1942:
	ldr	w0, [x19, 3896]
	cbz	w0, .L1934
	b	.L1933
	.p2align 3
.L1944:
	mov	x2, x23
	add	x1, x20, 2980
	add	x0, x20, 2900
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L1938
	.p2align 3
.L1943:
	ldr	x1, .LC148
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
	.align	3
.LC146:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC148:
	.xword	.LC147
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
.L1946:
	add	w16, w0, 288
	mov	x14, x1
	mov	w13, w15
.L1952:
	add	w12, w0, 144
	mov	x11, x14
	mov	w2, w13
	.p2align 2
.L1950:
	add	w10, w0, 24
	mov	x3, x11
	mov	w6, w2
	.p2align 2
.L1947:
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
	bne	.L1947
	cmp	w0, w12
	add	w2, w2, 6
	add	x11, x11, 96
	bne	.L1950
	cmp	w10, w16
	add	w13, w13, 36
	add	x14, x14, 576
	bne	.L1952
	cmp	w10, 576
	add	w15, w15, 72
	add	x1, x1, 1152
	mov	w0, w10
	bne	.L1946
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_RestoreCounts
	.type	Vp9_RestoreCounts, %function
Vp9_RestoreCounts:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	mov	x21, x1
	add	x19, x2, 8192
	bl	_mcount
	add	x2, x19, 1048
	mov	x1, x22
	mov	x0, x21
	add	x24, x22, 4096
	add	x23, x21, 4096
	bl	Vp9_CoefCountRestore
	add	x2, x19, 1624
	add	x1, x22, 2304
	add	x0, x21, 2304
	bl	Vp9_CoefCountRestore
	add	x2, x19, 2200
	add	x1, x24, 512
	add	x0, x23, 512
	bl	Vp9_CoefCountRestore
	add	x1, x24, 2816
	add	x0, x23, 2816
	add	x2, x19, 2776
	bl	Vp9_CoefCountRestore
	add	x0, x20, 294912
	ldr	w1, [x0, 3892]
	cbnz	w1, .L1954
	ldr	w0, [x0, 3896]
	cbnz	w0, .L1954
	add	x1, x21, 8192
	add	x5, x1, 1024
	add	x4, x1, 1280
	add	x3, x1, 1440
	add	x2, x1, 1840
	add	x0, x1, 2000
	add	x8, x1, 1888
	add	x7, x1, 2032
	add	x6, x1, 2072
	str	x4, [x22, 9216]
	add	x4, x1, 2192
	str	x3, [x22, 9224]
	add	x3, x1, 2208
	str	x5, [x22, 9232]
	add	x5, x1, 2152
	str	x2, [x22, 11544]
	add	x2, x1, 2232
	str	x0, [x22, 11560]
	add	x0, x1, 2288
	str	x8, [x22, 11552]
	add	x8, x1, 2264
	str	x7, [x22, 11568]
	add	x7, x1, 2304
	str	x6, [x22, 11576]
	add	x6, x1, 2312
	str	x5, [x22, 11584]
	add	x5, x1, 2320
	str	x2, [x22, 11592]
	add	x2, x1, 2416
	str	x3, [x22, 11600]
	add	x3, x1, 2408
	str	x4, [x22, 11608]
	add	x4, x1, 2364
	str	x0, [x22, 11624]
	add	x0, x1, 2504
	str	x8, [x22, 11616]
	add	x8, x1, 2424
	str	x7, [x22, 11632]
	add	x7, x1, 2584
	str	x6, [x22, 11696]
	add	x6, x1, 2616
	str	x5, [x22, 11640]
	add	x5, x1, 2648
	str	x3, [x22, 11648]
	add	x3, x1, 2680
	str	x4, [x22, 11704]
	add	x4, x1, 2664
	str	x2, [x22, 11712]
	add	x2, x1, 2688
	str	x0, [x22, 11720]
	add	x0, x1, 2696
	str	x8, [x22, 11656]
	add	x1, x1, 2704
	str	x7, [x22, 11664]
	str	x6, [x22, 11728]
	str	x5, [x22, 11672]
	str	x3, [x22, 11680]
	str	x0, [x22, 11688]
	str	x4, [x22, 11736]
	str	x2, [x22, 11744]
	str	x1, [x22, 11752]
.L1954:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_RestoreCounts, .-Vp9_RestoreCounts
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
	mov	x21, x0
	mov	x0, x30
	add	x28, x21, 270336
	mov	w22, w1
	mov	w24, w2
	mov	w23, w3
	bl	_mcount
	ldr	w0, [x28, 2484]
	ldrb	w1, [x28, 2097]
	str	w0, [x28, 2648]
	ldr	w0, [x28, 5172]
	strb	w1, [x28, 2644]
	str	w0, [x29, 108]
	ldr	w27, [x28, 5164]
	cbz	w24, .L1957
	ldr	x1, .LC149
	sbfiz	x0, x23, 6, 32
	add	x0, x1, x0
	ldr	w0, [x0, 44]
	cmp	w0, 3
	beq	.L1975
.L1957:
	add	x20, x21, 294912
	ldr	w0, [x20, 3828]
	cbz	w0, .L1960
	ldr	w0, [x20, 3864]
	ldr	w1, [x20, 3868]
	cmp	w1, w0
	beq	.L1960
.L1961:
	ldr	w0, [x20, 3928]
	add	x19, x28, 2760
	ldr	w1, [x28, 2628]
	add	x26, x28, 2796
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	cbnz	x0, .L1998
	b	.L2009
	.p2align 3
.L1964:
	cmp	w2, wzr
	ccmp	w0, wzr, 0, ne
	beq	.L2010
.L1965:
	add	x19, x19, 4
	cmp	x19, x26
	beq	.L2011
.L1998:
	ldr	w2, [x19]
	ldr	w0, [x19, -36]
	cmp	w2, wzr
	ldr	w1, [x19, 80]
	ccmp	w0, wzr, 4, eq
	beq	.L1964
	ldr	w0, [x20, 3928]
	mov	w2, 1
	add	x19, x19, 4
	bl	FSP_SetRef
	cmp	x19, x26
	bne	.L1998
.L2011:
	ldr	x0, .LC152
	mov	x2, 36
	add	x1, x28, 2724
	ldr	x3, [x0, 104]
	add	x0, x28, 2760
	blr	x3
	tbnz	w22, #31, .L1967
	cmp	w22, 100
	mov	w2, 100
	csel	w2, w22, w2, le
	str	w2, [x25, 152]
	ldr	x0, [x21]
	ldr	w3, [x0]
	cmp	w2, w3
	bhi	.L2012
	mov	x0, x21
	bl	VP9_SetImgFormat
	ldr	w0, [x28, 2576]
	cmp	w0, 2
	beq	.L2013
.L1969:
	ldr	w0, [x28, 5108]
	cbnz	w0, .L1971
.L1970:
	mov	w0, -1
	str	w0, [x28, 2632]
	ldr	w1, [x28, 2628]
	mov	w2, 0
	ldr	w0, [x20, 3928]
	bl	FSP_SetDisplay
	ldr	w1, [x28, 2632]
.L1972:
	cmn	w1, #1
	beq	.L1973
	ldr	w0, [x20, 3928]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L2014
	ldr	w1, [x28, 2632]
	mov	w2, 1
	ldr	w0, [x20, 3928]
	add	x28, x28, 2576
	bl	FSP_SetDisplay
	add	x3, x21, 274432
	ldr	w0, [x20, 3928]
	mov	x4, x19
	add	x3, x3, 1416
	mov	x2, x21
	mov	w1, 17
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w19, w0
	bne	.L2015
.L1973:
	cbz	w24, .L1975
	ldr	x0, .LC149
	sbfiz	x23, x23, 6, 32
	add	x23, x0, x23
	ldr	w0, [x23, 44]
	cmp	w0, 2
	beq	.L1959
.L1975:
	add	x22, x21, 274432
	ldr	w19, [x22, 1016]
	cbz	w19, .L2016
.L1959:
	mov	w19, 0
.L2007:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2010:
	ldr	w0, [x20, 3928]
	mov	w2, 0
	bl	FSP_SetRef
	b	.L1965
	.p2align 3
.L1971:
	ldr	w1, [x28, 2628]
	str	w1, [x28, 2632]
	b	.L1972
	.p2align 3
.L2016:
	add	x25, x21, 16
	add	x0, x25, 270336
	ldr	w0, [x0, 2356]
	bl	MEM_Phy2Vir
	mov	x28, x0
	cbz	x0, .L2017
	add	x20, x21, 294912
	mov	w23, 0
	ldr	w0, [x20, 3892]
	cbnz	w0, .L1977
	ldr	w0, [x20, 3912]
	cbnz	w0, .L1977
	ldr	w0, [x20, 3896]
	cmp	w0, wzr
	ldr	w0, [x29, 108]
	csel	w23, w0, wzr, eq
.L1977:
	ldr	x0, [x20, 3912]
	cbz	x0, .L2018
.L1979:
	cbz	w27, .L1959
.L2019:
	uxtw	x0, w23
	add	x1, x22, 2064
	lsl	x3, x0, 8
	mov	x2, 2087
	add	x3, x3, x0, lsl 2
	add	x3, x3, x0
	add	x21, x21, x3, lsl 3
	sub	x0, x21, x0
	add	x0, x0, 278528
	add	x0, x0, 55
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
.L1960:
	mov	x1, x21
	mov	w0, 17
	bl	ReleasePacket
	str	wzr, [x20, 3828]
	b	.L1961
	.p2align 3
.L1967:
	mov	x0, x21
	str	wzr, [x25, 152]
	bl	VP9_SetImgFormat
	ldr	w0, [x28, 2576]
	cmp	w0, 2
	bne	.L1969
.L2013:
	ldr	w0, [x28, 2636]
	cbnz	w0, .L1970
	b	.L1969
	.p2align 3
.L2015:
	ldr	w0, [x20, 3928]
	mov	w2, 0
	ldr	w1, [x28, 56]
	bl	FSP_SetDisplay
	ldr	x1, .LC158
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
.L2018:
	add	x0, x25, 270336
	ldr	w24, [x29, 108]
	mov	w2, 11264
	add	x26, x21, 286720
	add	x26, x26, 216
	add	x25, x22, 2064
	ldr	w1, [x0, 2356]
	lsl	x0, x24, 8
	add	x0, x0, x24, lsl 2
	add	x0, x0, x24
	lsl	x0, x0, 3
	sub	x24, x0, x24
	ldr	x0, .LC152
	add	x24, x24, 278528
	add	x24, x21, x24
	ldr	x3, [x0, 280]
	mov	x0, x28
	add	x24, x24, 55
	blr	x3
	mov	x2, x26
	mov	x1, x28
	mov	x0, x21
	bl	Vp9_RestoreCounts
	ldr	w5, [x20, 3896]
	mov	x0, x25
	ldr	w4, [x20, 3904]
	mov	w3, w23
	ldr	w6, [x20, 3908]
	mov	x2, x26
	mov	x1, x24
	bl	Vp9_AdaptResidualProbs
	ldr	w0, [x20, 3892]
	cbnz	w0, .L1979
	ldr	w0, [x20, 3896]
	cbnz	w0, .L1979
	ldr	w3, [x20, 3924]
	mov	x2, x26
	ldr	w4, [x20, 3900]
	mov	x1, x24
	mov	x0, x25
	bl	Vp9_AdaptModeProbs
	ldr	w3, [x20, 3920]
	mov	x2, x26
	mov	x1, x24
	mov	x0, x25
	bl	Vp9_AdaptMvProbs
	cbnz	w27, .L2019
	b	.L1959
.L2012:
	ldr	x1, .LC154
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	ldr	w0, [x20, 3928]
	mov	w2, 0
	ldr	w1, [x28, 2628]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 3928]
	mov	w2, 0
	ldr	w1, [x28, 2628]
	bl	FSP_SetRef
	b	.L2007
.L2014:
	ldr	x1, .LC156
	mov	w2, 2596
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2007
.L2009:
	ldr	x1, .LC151
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2007
.L2017:
	ldr	x1, .LC160
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2007
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	3
.LC149:
	.xword	g_VdmDrvParam
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC152:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.align	3
.LC160:
	.xword	.LC159
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
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 294912
	mov	x25, x1
	bl	_mcount
	add	x22, x21, 274432
	add	x19, x21, 270336
	add	x23, x22, 2024
	ldr	w0, [x20, 3824]
	add	x24, x19, 2644
	cbz	w0, .L2021
	ldr	w0, [x22, 988]
	tbnz	w0, #31, .L2021
.L2022:
	str	w0, [x20, 3820]
	mov	x1, x24
	mov	x0, x23
	bl	Read_UnCompressed_Header
	cbnz	w0, .L2095
	ldr	x0, [x21]
	ldr	w1, [x19, 5152]
	str	w1, [x0, 940]
	ldr	w2, [x19, 5152]
	cmp	w2, 10
	bgt	.L2098
.L2029:
	ldr	w0, [x22, 1016]
	cbnz	w0, .L2031
	ldr	w2, [x19, 2572]
	cmp	w2, 7
	ble	.L2099
.L2031:
	ldr	w0, [x19, 5136]
	add	x26, x19, 2644
	sub	w1, w0, #128
	cmp	w1, 3968
	bls	.L2100
.L2032:
	ldr	x0, .LC165
	ldr	x4, [x0]
	cbz	x4, .L2095
	ldr	w0, [x20, 3928]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2093:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2021:
	ldr	w2, [x19, 2724]
	add	x1, x19, 2728
	mov	w0, 1
	cbz	w2, .L2101
	.p2align 2
.L2080:
	ldr	w2, [x1]
	add	x1, x1, 4
	cbz	w2, .L2023
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L2080
	mov	w0, -1
	str	w0, [x22, 988]
.L2063:
	ldr	x1, .LC162
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2093
	.p2align 3
.L2100:
	ldr	w1, [x19, 5140]
	sub	w2, w1, #128
	cmp	w2, 3968
	bhi	.L2032
	adds	w2, w0, 63
	stp	w0, w1, [x26, 20]
	add	w0, w0, 126
	csel	w0, w0, w2, mi
	asr	w0, w0, 6
	str	w0, [x26, 12]
	add	w0, w1, 126
	adds	w1, w1, 63
	csel	w1, w0, w1, mi
	mov	x0, x21
	asr	w1, w1, 6
	str	w1, [x26, 16]
	bl	VP9_GetRefNum
	str	w0, [x20, 3796]
	ldr	w0, [x20, 3928]
	ldp	w1, w2, [x26, 20]
	bl	VCTRL_GetFsSize
	mov	w1, w0
	str	w0, [x20, 3784]
	ldr	w0, [x20, 3928]
	bl	FSP_GetPhyFsNum
	str	w0, [x20, 3788]
	ldr	w3, [x20, 3928]
	ldr	x0, .LC168
	ldr	x1, [x0, w3, sxtw 3]
	ldr	w0, [x1, 1496]
	str	w0, [x20, 3792]
	ldr	w4, [x26, 20]
	cmp	w4, 1920
	bhi	.L2035
	ldr	w2, [x26, 24]
	cmp	w2, 1088
	bhi	.L2035
	ldr	w2, [x1, 36]
	cmp	w2, 24
	beq	.L2035
	add	x1, x1, 507904
	ldr	w1, [x1, 1396]
	cmp	w1, wzr
	add	w1, w0, 4
	csel	w0, w1, w0, eq
	.p2align 2
.L2035:
	ldr	w2, [x20, 3796]
	ldr	w1, [x20, 3800]
	cmp	w1, w2
	csel	w1, w1, w2, ge
	add	w0, w1, w0
	str	w0, [x20, 3792]
	ldr	x0, [x21]
	ldr	w0, [x0, 956]
	cmp	w0, 1
	beq	.L2102
.L2036:
	ldr	w0, [x20, 3804]
	cmp	w4, w0
	beq	.L2103
.L2037:
	str	w2, [x20, 3800]
.L2039:
	mov	w1, 0
	mov	w0, w3
	bl	FSP_GetPhyFsNum
	mov	w27, w0
	ldr	w0, [x20, 3788]
	cmp	w27, w0
	ble	.L2040
	sub	w1, w27, w0
	cmp	w1, wzr
	ble	.L2040
	mov	w26, 0
	b	.L2042
	.p2align 3
.L2041:
	ldr	w0, [x20, 3788]
	sub	w1, w27, w0
	cmp	w1, w26
	ble	.L2040
.L2042:
	ldr	w1, [x20, 3784]
	add	w26, w26, 1
	ldr	w0, [x20, 3928]
	bl	FSP_RelsePhyFs
	cbz	w0, .L2041
	ldr	w0, [x20, 3788]
.L2040:
	ldr	w1, [x20, 3792]
	cmp	w1, w0
	bge	.L2045
	sub	w0, w0, w1
	cmp	w0, wzr
	ble	.L2045
	mov	w26, 0
	b	.L2046
	.p2align 3
.L2104:
	ldr	w0, [x20, 3788]
	ldr	w1, [x20, 3792]
	sub	w0, w0, w1
	cmp	w0, w26
	ble	.L2045
.L2046:
	ldr	w0, [x20, 3928]
	mov	w1, 0
	add	w26, w26, 1
	bl	FSP_RelsePhyFs
	cbz	w0, .L2104
.L2045:
	ldr	w0, [x20, 3928]
	mov	w1, 0
	bl	FSP_GetPhyFsNum
	mov	w26, w0
	ldr	w0, [x20, 3792]
	add	w0, w0, 4
	cmp	w26, w0
	bgt	.L2105
	ldr	w1, [x20, 3784]
	ldr	w0, [x20, 3928]
	bl	FSP_GetPhyFsNum
	add	w1, w0, 1
	ldr	w6, [x20, 3796]
	mov	w5, w0
	ldr	w2, [x20, 3792]
	mov	w4, w26
	add	w7, w6, 2
	str	w0, [x20, 3788]
	cmp	w1, w7
	csel	w1, w1, w7, le
	sub	w7, w0, w26
	add	w7, w7, w2
	mov	w0, 2
	cmp	w1, w7
	csel	w7, w1, w7, ge
	str	w7, [x20, 3792]
	ldr	x1, .LC171
	ldr	w2, [x19, 2664]
	ldr	w3, [x19, 2668]
	bl	dprint_vfmw
	ldr	w0, [x19, 2580]
	cbz	w0, .L2047
	ldr	w0, [x19, 2664]
	ldr	w1, [x20, 3804]
	cmp	w1, w0
	bne	.L2047
	ldr	w0, [x19, 2668]
	ldr	w1, [x20, 3808]
	cmp	w1, w0
	bne	.L2047
	ldr	w1, [x20, 3788]
	ldr	w0, [x20, 3792]
	cmp	w1, w0
	bge	.L2048
	.p2align 2
.L2047:
	mov	x0, x21
	bl	VP9_ArrangeVHBMem
	ldr	w0, [x19, 2580]
	cbz	w0, .L2106
.L2048:
	ldr	x0, [x21]
	ldr	w0, [x0, 8]
	str	w0, [x19, 2576]
	ldr	w0, [x22, 1016]
	cbz	w0, .L2107
.L2049:
	ldr	w0, [x20, 3928]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	bne	.L2108
	mov	x0, x23
	bl	BsBitsToNextByte
	cbnz	w0, .L2109
.L2051:
	ldr	w0, [x19, 5112]
	cbz	w0, .L2110
.L2052:
	mov	x0, x21
	bl	VP9_GetImageBuffer
	cbnz	w0, .L2111
	ldrsw	x1, [x20, 3820]
	add	x23, x19, 2644
	ldr	w2, [x19, 2628]
	mov	x0, x21
	add	x1, x23, x1, lsl 2
	str	w2, [x1, 196]
	bl	VP9_Set_DecParam
	cbnz	w0, .L2112
	ldr	w1, [x22, 1016]
	cmp	w1, 1
	beq	.L2113
	ldr	w0, [x23, 20]
	str	w0, [x20, 3812]
	ldr	w0, [x23, 24]
	str	w0, [x20, 3816]
.L2057:
	mov	x0, x24
	bl	swap_frame_buffers
	ldr	x2, [x20, 3872]
	ldr	x3, [x20, 3880]
	cmp	x2, x3
	bcs	.L2058
	ldrb	w0, [x2]
	cbnz	w0, .L2058
	add	x0, x2, 1
	b	.L2059
	.p2align 3
.L2114:
	ldrb	w1, [x0], 1
	cbnz	w1, .L2058
.L2059:
	cmp	x3, x0
	str	x0, [x20, 3872]
	mov	x2, x0
	bne	.L2114
.L2058:
	ldr	w0, [x20, 3828]
	cmp	w0, 1
	beq	.L2115
.L2060:
	str	wzr, [x20, 3824]
	ldr	w0, [x19, 5112]
	cbnz	w0, .L2061
	ldr	w1, [x22, 1012]
	str	w1, [x22, 1024]
	b	.L2093
.L2101:
	mov	w0, 0
	.p2align 2
.L2023:
	add	x1, x19, x0, sxtw 2
	mov	w2, 1
	str	w2, [x1, 2724]
	str	w0, [x22, 988]
	tbz	w0, #31, .L2022
	b	.L2063
	.p2align 3
.L2099:
	ldr	x1, .LC167
	mov	w0, 1
	bl	dprint_vfmw
.L2095:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2098:
	ldr	x1, .LC164
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC165
	ldr	x4, [x0]
	cbz	x4, .L2029
	ldr	w0, [x19, 5152]
	mov	w3, 8
	stp	wzr, w0, [x29, 104]
	ldr	w0, [x20, 3928]
	add	x2, x29, 104
	mov	w1, 119
	blr	x4
	b	.L2029
.L2107:
	ldr	w1, [x19, 2664]
	str	w1, [x20, 3804]
	ldr	w0, [x19, 2668]
	str	w0, [x20, 3808]
	b	.L2049
.L2103:
	ldr	w0, [x19, 2668]
	ldr	w4, [x20, 3808]
	cmp	w4, w0
	bne	.L2037
	str	w1, [x20, 3800]
	b	.L2039
.L2102:
	ldr	x0, .LC169
	ldr	w0, [x0, 2028]
	str	w0, [x20, 3792]
	b	.L2036
.L2109:
	mov	w1, w0
	mov	x0, x23
	bl	BsGet
	b	.L2051
.L2110:
	ldr	w0, [x22, 2056]
	ldr	w2, [x22, 2048]
	add	w0, w0, 7
	lsr	w1, w0, 3
	mov	x0, x21
	sub	w2, w2, w1
	add	x1, x25, x1
	bl	Vp9_DecodeTiles
	b	.L2052
.L2113:
	add	x1, x19, 2724
	ldr	w3, [x22, 988]
	ldr	w0, [x22, 1020]
	ldr	w2, [x1, w3, sxtw 2]
	cmp	w2, wzr
	ble	.L2056
	sub	w2, w2, #1
	str	w2, [x1, w3, sxtw 2]
.L2056:
	str	w0, [x22, 988]
	ldr	w2, [x1, w0, sxtw 2]
	add	w2, w2, 1
	str	w2, [x1, w0, sxtw 2]
	b	.L2057
.L2061:
	mov	w3, 0
	mov	w2, 0
	mov	w1, 0
	mov	x0, x21
	bl	VP9DEC_VDMPostProc
	mov	w0, 0
	b	.L2093
.L2115:
	ldr	w0, [x20, 3868]
	add	w1, w0, 1
	sxtw	x0, w0
	add	x0, x0, 73728
	add	x0, x21, x0, lsl 2
	ldrsw	x0, [x0, 3832]
	str	w1, [x20, 3868]
	add	x2, x2, x0
	str	x2, [x20, 3872]
	b	.L2060
.L2105:
	mov	w0, -2
	b	.L2093
.L2108:
	ldr	x2, .LC174
	mov	w3, 4047
	ldr	x1, .LC176
	mov	w0, 23
	add	x2, x2, 912
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2093
.L2111:
	ldr	x1, .LC178
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2093
.L2106:
	ldr	x1, .LC173
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2093
.L2112:
	ldr	x1, .LC180
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2093
	.size	VP9DEC_DecodeFame, .-VP9DEC_DecodeFame
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	g_event_report
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC168:
	.xword	s_pstVfmwChan
	.align	3
.LC169:
	.xword	.LANCHOR1
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.align	3
.LC174:
	.xword	.LANCHOR0
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC180:
	.xword	.LC179
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
	beq	.L2128
	add	x22, x19, 270336
	ldr	x0, [x20]
	add	x21, x19, 294912
	str	x0, [x22, 2560]
	ldr	w1, [x20, 16]
	str	w1, [x22, 2568]
	ldr	w1, [x20, 20]
	str	w1, [x22, 2572]
	ldr	w5, [x21, 3828]
	cbz	w5, .L2118
	ldr	w2, [x21, 3888]
	ldr	x20, [x21, 3872]
	.p2align 2
.L2122:
	cbz	w2, .L2130
	ldrb	w1, [x20]
	and	w0, w1, 7
	and	w4, w1, 224
	ubfx	x3, x1, 3, 2
	add	w0, w0, 1
	cmp	w4, 192
	madd	w0, w3, w0, w0
	bne	.L2124
	add	w3, w0, 2
	cmp	w3, w2
	bhi	.L2122
	add	w0, w0, 1
	ldrb	w0, [x20, x0]
	cmp	w0, w1
	bne	.L2122
	ldr	x0, [x21, 3880]
	add	x20, x20, x3, uxtb
	sub	w2, w2, w3
	str	x20, [x21, 3872]
	cmp	x20, x0
	str	w2, [x21, 3888]
	bcc	.L2122
	.p2align 2
.L2124:
	cmp	w5, 1
	beq	.L2138
.L2126:
	add	x0, x19, 274432
	mov	x1, x20
	add	x0, x0, 2024
	bl	BsInit
	mov	x1, x20
	mov	x0, x19
	bl	VP9DEC_DecodeFame
	cmn	w0, #2
	mov	w20, w0
	beq	.L2139
	mov	w0, 0
	cbnz	w20, .L2140
.L2117:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2140:
	mov	x0, x19
	bl	VP9_FreeCurFb
	str	wzr, [x21, 3828]
	mov	x1, x19
	mov	w0, 17
	bl	ReleasePacket
	ldr	x1, .LC183
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2130:
	cmp	w5, 1
	mov	w2, 0
	bne	.L2126
.L2138:
	ldrsw	x0, [x21, 3868]
	add	x0, x0, 73728
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 3832]
	b	.L2126
	.p2align 3
.L2118:
	add	x3, x29, 60
	add	x2, x29, 64
	bl	Vp9_ParseSuperFrameIndex
	ldr	w0, [x29, 60]
	cbnz	w0, .L2141
.L2120:
	ldr	x20, [x22, 2560]
	str	x20, [x21, 3872]
	ldr	w5, [x21, 3828]
	ldr	w2, [x22, 2572]
	str	w2, [x21, 3888]
	add	x0, x20, x2, uxtw
	str	x0, [x21, 3880]
	b	.L2122
.L2141:
	ldr	x1, .LC181
	mov	w2, 1
	str	w0, [x21, 3864]
	add	x0, x21, 3832
	str	w2, [x21, 3828]
	mov	x2, 32
	ldr	x3, [x1, 104]
	add	x1, x29, 64
	str	wzr, [x21, 3868]
	blr	x3
	b	.L2120
	.p2align 3
.L2139:
	mov	w1, 1
	str	w1, [x21, 3824]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
.L2128:
	mov	w0, -1
	b	.L2117
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.align	3
.LC181:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC183:
	.xword	.LC182
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
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
	.type	vp9_inter_mode_tree, %object
	.size	vp9_inter_mode_tree, 6
vp9_inter_mode_tree:
	.byte	-2
	.byte	2
	.byte	0
	.byte	4
	.byte	-1
	.byte	-3
	.zero	2
	.type	vp9_intra_mode_tree, %object
	.size	vp9_intra_mode_tree, 18
vp9_intra_mode_tree:
	.byte	0
	.byte	2
	.byte	-9
	.byte	4
	.byte	-1
	.byte	6
	.byte	8
	.byte	12
	.byte	-2
	.byte	10
	.byte	-4
	.byte	-5
	.byte	-3
	.byte	14
	.byte	-8
	.byte	16
	.byte	-6
	.byte	-7
	.zero	6
	.type	vp9_partition_tree, %object
	.size	vp9_partition_tree, 6
vp9_partition_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.zero	2
	.type	vp9_switchable_interp_tree, %object
	.size	vp9_switchable_interp_tree, 4
vp9_switchable_interp_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	-2
	.zero	4
.LC0:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.zero	2
.LC1:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	6
	.byte	8
	.byte	-2
	.byte	-3
	.byte	10
	.byte	12
	.byte	-4
	.byte	-5
	.byte	-6
	.byte	14
	.byte	16
	.byte	18
	.byte	-7
	.byte	-8
	.byte	-9
	.byte	-10
	.zero	4
	.type	__func__.11907, %object
	.size	__func__.11907, 19
__func__.11907:
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
	.type	__func__.12085, %object
	.size	__func__.12085, 16
__func__.12085:
	.string	"VP9_Set_Segdata"
	.type	__FUNCTION__.12161, %object
	.size	__FUNCTION__.12161, 33
__FUNCTION__.12161:
	.string	"VP9_get_fixed_point_scale_factor"
	.zero	7
	.type	__FUNCTION__.12190, %object
	.size	__FUNCTION__.12190, 35
__FUNCTION__.12190:
	.string	"Vp9_ReadBitDepthColorSpaceSampling"
	.zero	5
	.type	__FUNCTION__.12220, %object
	.size	__FUNCTION__.12220, 25
__FUNCTION__.12220:
	.string	"Read_UnCompressed_Header"
	.zero	7
	.type	vp9_default_tx_probs, %object
	.size	vp9_default_tx_probs, 12
vp9_default_tx_probs:
	.byte	3
	.byte	-120
	.byte	37
	.byte	5
	.byte	52
	.byte	13
	.byte	20
	.byte	-104
	.byte	15
	.byte	101
	.byte	100
	.byte	66
	.type	vp9_default_nmv_context, %object
	.size	vp9_default_nmv_context, 69
vp9_default_nmv_context:
	.byte	32
	.byte	64
	.byte	96
	.byte	-128
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
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-128
	.byte	-128
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
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-128
	.zero	7
	.type	__func__.12440, %object
	.size	__func__.12440, 20
__func__.12440:
	.string	"Vp9_DecodeTilesCtrl"
	.zero	4
	.type	__func__.12300, %object
	.size	__func__.12300, 18
__func__.12300:
	.string	"VP9DEC_DecodeFame"
	.data
	.align	3
.LANCHOR1 = . + 0
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 432
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.byte	84
	.byte	49
	.byte	-120
	.byte	8
	.byte	42
	.byte	71
	.zero	9
	.byte	31
	.byte	107
	.byte	-87
	.byte	35
	.byte	99
	.byte	-97
	.byte	17
	.byte	82
	.byte	-116
	.byte	8
	.byte	66
	.byte	114
	.byte	2
	.byte	44
	.byte	76
	.byte	1
	.byte	19
	.byte	32
	.byte	40
	.byte	-124
	.byte	-55
	.byte	29
	.byte	114
	.byte	-69
	.byte	13
	.byte	91
	.byte	-99
	.byte	7
	.byte	75
	.byte	127
	.byte	3
	.byte	58
	.byte	95
	.byte	1
	.byte	28
	.byte	47
	.byte	69
	.byte	-114
	.byte	-35
	.byte	42
	.byte	122
	.byte	-55
	.byte	15
	.byte	91
	.byte	-97
	.byte	6
	.byte	67
	.byte	121
	.byte	1
	.byte	42
	.byte	77
	.byte	1
	.byte	17
	.byte	31
	.byte	102
	.byte	-108
	.byte	-28
	.byte	67
	.byte	117
	.byte	-52
	.byte	17
	.byte	82
	.byte	-102
	.byte	6
	.byte	59
	.byte	114
	.byte	2
	.byte	39
	.byte	75
	.byte	1
	.byte	15
	.byte	29
	.byte	-100
	.byte	57
	.byte	-23
	.byte	119
	.byte	57
	.byte	-44
	.byte	58
	.byte	48
	.byte	-93
	.byte	29
	.byte	40
	.byte	124
	.byte	12
	.byte	30
	.byte	81
	.byte	3
	.byte	12
	.byte	31
	.byte	-65
	.byte	107
	.byte	-30
	.byte	124
	.byte	117
	.byte	-52
	.byte	25
	.byte	99
	.byte	-101
	.zero	9
	.byte	29
	.byte	-108
	.byte	-46
	.byte	37
	.byte	126
	.byte	-62
	.byte	8
	.byte	93
	.byte	-99
	.byte	2
	.byte	68
	.byte	118
	.byte	1
	.byte	39
	.byte	69
	.byte	1
	.byte	17
	.byte	33
	.byte	41
	.byte	-105
	.byte	-43
	.byte	27
	.byte	123
	.byte	-63
	.byte	3
	.byte	82
	.byte	-112
	.byte	1
	.byte	58
	.byte	105
	.byte	1
	.byte	32
	.byte	60
	.byte	1
	.byte	13
	.byte	26
	.byte	59
	.byte	-97
	.byte	-36
	.byte	23
	.byte	126
	.byte	-58
	.byte	4
	.byte	88
	.byte	-105
	.byte	1
	.byte	66
	.byte	114
	.byte	1
	.byte	38
	.byte	71
	.byte	1
	.byte	18
	.byte	34
	.byte	114
	.byte	-120
	.byte	-24
	.byte	51
	.byte	114
	.byte	-49
	.byte	11
	.byte	83
	.byte	-101
	.byte	3
	.byte	56
	.byte	105
	.byte	1
	.byte	33
	.byte	65
	.byte	1
	.byte	17
	.byte	34
	.byte	-107
	.byte	65
	.byte	-22
	.byte	121
	.byte	57
	.byte	-41
	.byte	61
	.byte	49
	.byte	-90
	.byte	28
	.byte	36
	.byte	114
	.byte	12
	.byte	25
	.byte	76
	.byte	3
	.byte	16
	.byte	42
	.byte	-42
	.byte	49
	.byte	-36
	.byte	-124
	.byte	63
	.byte	-68
	.byte	42
	.byte	65
	.byte	-119
	.zero	9
	.byte	85
	.byte	-119
	.byte	-35
	.byte	104
	.byte	-125
	.byte	-40
	.byte	49
	.byte	111
	.byte	-64
	.byte	21
	.byte	87
	.byte	-101
	.byte	2
	.byte	49
	.byte	87
	.byte	1
	.byte	16
	.byte	28
	.byte	89
	.byte	-93
	.byte	-26
	.byte	90
	.byte	-119
	.byte	-36
	.byte	29
	.byte	100
	.byte	-73
	.byte	10
	.byte	70
	.byte	-121
	.byte	2
	.byte	42
	.byte	81
	.byte	1
	.byte	17
	.byte	33
	.byte	108
	.byte	-89
	.byte	-19
	.byte	55
	.byte	-123
	.byte	-34
	.byte	15
	.byte	97
	.byte	-77
	.byte	4
	.byte	72
	.byte	-121
	.byte	1
	.byte	45
	.byte	85
	.byte	1
	.byte	19
	.byte	38
	.byte	124
	.byte	-110
	.byte	-16
	.byte	66
	.byte	124
	.byte	-32
	.byte	17
	.byte	88
	.byte	-81
	.byte	4
	.byte	58
	.byte	122
	.byte	1
	.byte	36
	.byte	75
	.byte	1
	.byte	18
	.byte	37
	.byte	-115
	.byte	79
	.byte	-15
	.byte	126
	.byte	70
	.byte	-29
	.byte	66
	.byte	58
	.byte	-74
	.byte	30
	.byte	44
	.byte	-120
	.byte	12
	.byte	34
	.byte	96
	.byte	2
	.byte	20
	.byte	47
	.byte	-27
	.byte	99
	.byte	-7
	.byte	-113
	.byte	111
	.byte	-21
	.byte	46
	.byte	109
	.byte	-64
	.zero	9
	.byte	82
	.byte	-98
	.byte	-20
	.byte	94
	.byte	-110
	.byte	-32
	.byte	25
	.byte	117
	.byte	-65
	.byte	9
	.byte	87
	.byte	-107
	.byte	3
	.byte	56
	.byte	99
	.byte	1
	.byte	33
	.byte	57
	.byte	83
	.byte	-89
	.byte	-19
	.byte	68
	.byte	-111
	.byte	-34
	.byte	10
	.byte	103
	.byte	-79
	.byte	2
	.byte	72
	.byte	-125
	.byte	1
	.byte	41
	.byte	79
	.byte	1
	.byte	20
	.byte	39
	.byte	99
	.byte	-89
	.byte	-17
	.byte	47
	.byte	-115
	.byte	-32
	.byte	10
	.byte	104
	.byte	-78
	.byte	2
	.byte	73
	.byte	-123
	.byte	1
	.byte	44
	.byte	85
	.byte	1
	.byte	22
	.byte	47
	.byte	127
	.byte	-111
	.byte	-13
	.byte	71
	.byte	-127
	.byte	-28
	.byte	17
	.byte	93
	.byte	-79
	.byte	3
	.byte	61
	.byte	124
	.byte	1
	.byte	41
	.byte	84
	.byte	1
	.byte	21
	.byte	52
	.byte	-99
	.byte	78
	.byte	-12
	.byte	-116
	.byte	72
	.byte	-25
	.byte	69
	.byte	58
	.byte	-72
	.byte	31
	.byte	44
	.byte	-119
	.byte	14
	.byte	38
	.byte	105
	.byte	8
	.byte	23
	.byte	61
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 432
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.byte	52
	.byte	41
	.byte	-123
	.byte	6
	.byte	31
	.byte	56
	.zero	9
	.byte	37
	.byte	109
	.byte	-103
	.byte	51
	.byte	102
	.byte	-109
	.byte	23
	.byte	87
	.byte	-128
	.byte	8
	.byte	67
	.byte	101
	.byte	1
	.byte	41
	.byte	63
	.byte	1
	.byte	19
	.byte	29
	.byte	31
	.byte	-102
	.byte	-71
	.byte	17
	.byte	127
	.byte	-81
	.byte	6
	.byte	96
	.byte	-111
	.byte	2
	.byte	73
	.byte	114
	.byte	1
	.byte	51
	.byte	82
	.byte	1
	.byte	28
	.byte	45
	.byte	23
	.byte	-93
	.byte	-56
	.byte	10
	.byte	-125
	.byte	-71
	.byte	2
	.byte	93
	.byte	-108
	.byte	1
	.byte	67
	.byte	111
	.byte	1
	.byte	41
	.byte	69
	.byte	1
	.byte	14
	.byte	24
	.byte	29
	.byte	-80
	.byte	-39
	.byte	12
	.byte	-111
	.byte	-55
	.byte	3
	.byte	101
	.byte	-100
	.byte	1
	.byte	69
	.byte	111
	.byte	1
	.byte	39
	.byte	63
	.byte	1
	.byte	14
	.byte	23
	.byte	57
	.byte	-64
	.byte	-23
	.byte	25
	.byte	-102
	.byte	-41
	.byte	6
	.byte	109
	.byte	-89
	.byte	3
	.byte	78
	.byte	118
	.byte	1
	.byte	48
	.byte	69
	.byte	1
	.byte	21
	.byte	29
	.byte	-54
	.byte	105
	.byte	-11
	.byte	108
	.byte	106
	.byte	-40
	.byte	18
	.byte	90
	.byte	-112
	.zero	9
	.byte	33
	.byte	-84
	.byte	-37
	.byte	64
	.byte	-107
	.byte	-50
	.byte	14
	.byte	117
	.byte	-79
	.byte	5
	.byte	90
	.byte	-115
	.byte	2
	.byte	61
	.byte	95
	.byte	1
	.byte	37
	.byte	57
	.byte	33
	.byte	-77
	.byte	-36
	.byte	11
	.byte	-116
	.byte	-58
	.byte	1
	.byte	89
	.byte	-108
	.byte	1
	.byte	60
	.byte	104
	.byte	1
	.byte	33
	.byte	57
	.byte	1
	.byte	12
	.byte	21
	.byte	30
	.byte	-75
	.byte	-35
	.byte	8
	.byte	-115
	.byte	-58
	.byte	1
	.byte	87
	.byte	-111
	.byte	1
	.byte	58
	.byte	100
	.byte	1
	.byte	31
	.byte	55
	.byte	1
	.byte	12
	.byte	20
	.byte	32
	.byte	-70
	.byte	-32
	.byte	7
	.byte	-114
	.byte	-58
	.byte	1
	.byte	86
	.byte	-113
	.byte	1
	.byte	58
	.byte	100
	.byte	1
	.byte	31
	.byte	55
	.byte	1
	.byte	12
	.byte	22
	.byte	57
	.byte	-64
	.byte	-29
	.byte	20
	.byte	-113
	.byte	-52
	.byte	3
	.byte	96
	.byte	-102
	.byte	1
	.byte	68
	.byte	112
	.byte	1
	.byte	42
	.byte	69
	.byte	1
	.byte	19
	.byte	32
	.byte	-44
	.byte	35
	.byte	-41
	.byte	113
	.byte	47
	.byte	-87
	.byte	29
	.byte	48
	.byte	105
	.zero	9
	.byte	74
	.byte	-127
	.byte	-53
	.byte	106
	.byte	120
	.byte	-53
	.byte	49
	.byte	107
	.byte	-78
	.byte	19
	.byte	84
	.byte	-112
	.byte	4
	.byte	50
	.byte	84
	.byte	1
	.byte	15
	.byte	25
	.byte	71
	.byte	-84
	.byte	-39
	.byte	44
	.byte	-115
	.byte	-47
	.byte	15
	.byte	102
	.byte	-83
	.byte	6
	.byte	76
	.byte	-123
	.byte	2
	.byte	51
	.byte	89
	.byte	1
	.byte	24
	.byte	42
	.byte	64
	.byte	-71
	.byte	-25
	.byte	31
	.byte	-108
	.byte	-40
	.byte	8
	.byte	103
	.byte	-81
	.byte	3
	.byte	74
	.byte	-125
	.byte	1
	.byte	46
	.byte	81
	.byte	1
	.byte	18
	.byte	30
	.byte	65
	.byte	-60
	.byte	-21
	.byte	25
	.byte	-99
	.byte	-35
	.byte	5
	.byte	105
	.byte	-82
	.byte	1
	.byte	67
	.byte	120
	.byte	1
	.byte	38
	.byte	69
	.byte	1
	.byte	15
	.byte	30
	.byte	65
	.byte	-52
	.byte	-18
	.byte	30
	.byte	-100
	.byte	-32
	.byte	7
	.byte	107
	.byte	-79
	.byte	2
	.byte	70
	.byte	124
	.byte	1
	.byte	42
	.byte	73
	.byte	1
	.byte	18
	.byte	34
	.byte	-31
	.byte	86
	.byte	-5
	.byte	-112
	.byte	104
	.byte	-21
	.byte	42
	.byte	99
	.byte	-75
	.zero	9
	.byte	85
	.byte	-81
	.byte	-17
	.byte	112
	.byte	-91
	.byte	-27
	.byte	29
	.byte	-120
	.byte	-56
	.byte	12
	.byte	103
	.byte	-94
	.byte	6
	.byte	77
	.byte	123
	.byte	2
	.byte	53
	.byte	84
	.byte	75
	.byte	-73
	.byte	-17
	.byte	30
	.byte	-101
	.byte	-35
	.byte	3
	.byte	106
	.byte	-85
	.byte	1
	.byte	74
	.byte	-128
	.byte	1
	.byte	44
	.byte	76
	.byte	1
	.byte	17
	.byte	28
	.byte	73
	.byte	-71
	.byte	-16
	.byte	27
	.byte	-97
	.byte	-34
	.byte	2
	.byte	107
	.byte	-84
	.byte	1
	.byte	75
	.byte	127
	.byte	1
	.byte	42
	.byte	73
	.byte	1
	.byte	17
	.byte	29
	.byte	62
	.byte	-66
	.byte	-18
	.byte	21
	.byte	-97
	.byte	-34
	.byte	2
	.byte	107
	.byte	-84
	.byte	1
	.byte	72
	.byte	122
	.byte	1
	.byte	40
	.byte	71
	.byte	1
	.byte	18
	.byte	32
	.byte	61
	.byte	-57
	.byte	-16
	.byte	27
	.byte	-95
	.byte	-30
	.byte	4
	.byte	113
	.byte	-76
	.byte	1
	.byte	76
	.byte	-127
	.byte	1
	.byte	46
	.byte	80
	.byte	1
	.byte	23
	.byte	41
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 432
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.byte	5
	.byte	30
	.byte	95
	.byte	1
	.byte	16
	.byte	30
	.zero	9
	.byte	50
	.byte	75
	.byte	127
	.byte	57
	.byte	75
	.byte	124
	.byte	27
	.byte	67
	.byte	108
	.byte	10
	.byte	54
	.byte	86
	.byte	1
	.byte	33
	.byte	52
	.byte	1
	.byte	12
	.byte	18
	.byte	43
	.byte	125
	.byte	-105
	.byte	26
	.byte	108
	.byte	-108
	.byte	7
	.byte	83
	.byte	122
	.byte	2
	.byte	59
	.byte	89
	.byte	1
	.byte	38
	.byte	60
	.byte	1
	.byte	17
	.byte	27
	.byte	23
	.byte	-112
	.byte	-93
	.byte	13
	.byte	112
	.byte	-102
	.byte	2
	.byte	75
	.byte	117
	.byte	1
	.byte	50
	.byte	81
	.byte	1
	.byte	31
	.byte	51
	.byte	1
	.byte	14
	.byte	23
	.byte	18
	.byte	-94
	.byte	-71
	.byte	6
	.byte	123
	.byte	-85
	.byte	1
	.byte	78
	.byte	125
	.byte	1
	.byte	51
	.byte	86
	.byte	1
	.byte	31
	.byte	54
	.byte	1
	.byte	14
	.byte	23
	.byte	15
	.byte	-57
	.byte	-29
	.byte	3
	.byte	-106
	.byte	-52
	.byte	1
	.byte	91
	.byte	-110
	.byte	1
	.byte	55
	.byte	95
	.byte	1
	.byte	30
	.byte	53
	.byte	1
	.byte	11
	.byte	20
	.byte	19
	.byte	55
	.byte	-16
	.byte	19
	.byte	59
	.byte	-60
	.byte	3
	.byte	52
	.byte	105
	.zero	9
	.byte	41
	.byte	-90
	.byte	-49
	.byte	104
	.byte	-103
	.byte	-57
	.byte	31
	.byte	123
	.byte	-75
	.byte	14
	.byte	101
	.byte	-104
	.byte	5
	.byte	72
	.byte	106
	.byte	1
	.byte	36
	.byte	52
	.byte	35
	.byte	-80
	.byte	-45
	.byte	12
	.byte	-125
	.byte	-66
	.byte	2
	.byte	88
	.byte	-112
	.byte	1
	.byte	60
	.byte	101
	.byte	1
	.byte	36
	.byte	60
	.byte	1
	.byte	16
	.byte	28
	.byte	28
	.byte	-73
	.byte	-43
	.byte	8
	.byte	-122
	.byte	-65
	.byte	1
	.byte	86
	.byte	-114
	.byte	1
	.byte	56
	.byte	96
	.byte	1
	.byte	30
	.byte	53
	.byte	1
	.byte	12
	.byte	20
	.byte	20
	.byte	-66
	.byte	-41
	.byte	4
	.byte	-121
	.byte	-64
	.byte	1
	.byte	84
	.byte	-117
	.byte	1
	.byte	53
	.byte	91
	.byte	1
	.byte	28
	.byte	49
	.byte	1
	.byte	11
	.byte	20
	.byte	13
	.byte	-60
	.byte	-40
	.byte	2
	.byte	-119
	.byte	-64
	.byte	1
	.byte	86
	.byte	-113
	.byte	1
	.byte	57
	.byte	99
	.byte	1
	.byte	32
	.byte	56
	.byte	1
	.byte	13
	.byte	24
	.byte	-45
	.byte	29
	.byte	-39
	.byte	96
	.byte	47
	.byte	-100
	.byte	22
	.byte	43
	.byte	87
	.zero	9
	.byte	78
	.byte	120
	.byte	-63
	.byte	111
	.byte	116
	.byte	-70
	.byte	46
	.byte	102
	.byte	-92
	.byte	15
	.byte	80
	.byte	-128
	.byte	2
	.byte	49
	.byte	76
	.byte	1
	.byte	18
	.byte	28
	.byte	71
	.byte	-95
	.byte	-53
	.byte	42
	.byte	-124
	.byte	-64
	.byte	10
	.byte	98
	.byte	-106
	.byte	3
	.byte	69
	.byte	109
	.byte	1
	.byte	44
	.byte	70
	.byte	1
	.byte	18
	.byte	29
	.byte	57
	.byte	-70
	.byte	-45
	.byte	30
	.byte	-116
	.byte	-60
	.byte	4
	.byte	93
	.byte	-110
	.byte	1
	.byte	62
	.byte	102
	.byte	1
	.byte	38
	.byte	65
	.byte	1
	.byte	16
	.byte	27
	.byte	47
	.byte	-57
	.byte	-39
	.byte	14
	.byte	-111
	.byte	-60
	.byte	1
	.byte	88
	.byte	-114
	.byte	1
	.byte	57
	.byte	98
	.byte	1
	.byte	36
	.byte	62
	.byte	1
	.byte	15
	.byte	26
	.byte	26
	.byte	-37
	.byte	-27
	.byte	5
	.byte	-101
	.byte	-49
	.byte	1
	.byte	94
	.byte	-105
	.byte	1
	.byte	60
	.byte	104
	.byte	1
	.byte	36
	.byte	62
	.byte	1
	.byte	16
	.byte	28
	.byte	-23
	.byte	29
	.byte	-8
	.byte	-110
	.byte	47
	.byte	-36
	.byte	43
	.byte	52
	.byte	-116
	.zero	9
	.byte	100
	.byte	-93
	.byte	-24
	.byte	-77
	.byte	-95
	.byte	-34
	.byte	63
	.byte	-114
	.byte	-52
	.byte	37
	.byte	113
	.byte	-82
	.byte	26
	.byte	89
	.byte	-119
	.byte	18
	.byte	68
	.byte	97
	.byte	85
	.byte	-75
	.byte	-26
	.byte	32
	.byte	-110
	.byte	-47
	.byte	7
	.byte	100
	.byte	-92
	.byte	3
	.byte	71
	.byte	121
	.byte	1
	.byte	45
	.byte	77
	.byte	1
	.byte	18
	.byte	30
	.byte	65
	.byte	-69
	.byte	-26
	.byte	20
	.byte	-108
	.byte	-49
	.byte	2
	.byte	97
	.byte	-97
	.byte	1
	.byte	68
	.byte	116
	.byte	1
	.byte	40
	.byte	70
	.byte	1
	.byte	14
	.byte	29
	.byte	40
	.byte	-62
	.byte	-29
	.byte	8
	.byte	-109
	.byte	-52
	.byte	1
	.byte	94
	.byte	-101
	.byte	1
	.byte	65
	.byte	112
	.byte	1
	.byte	39
	.byte	66
	.byte	1
	.byte	14
	.byte	26
	.byte	16
	.byte	-48
	.byte	-28
	.byte	3
	.byte	-105
	.byte	-49
	.byte	1
	.byte	98
	.byte	-96
	.byte	1
	.byte	67
	.byte	117
	.byte	1
	.byte	41
	.byte	74
	.byte	1
	.byte	17
	.byte	31
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 432
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.byte	7
	.byte	34
	.byte	80
	.byte	1
	.byte	17
	.byte	29
	.zero	9
	.byte	37
	.byte	75
	.byte	-128
	.byte	41
	.byte	76
	.byte	-128
	.byte	26
	.byte	66
	.byte	116
	.byte	12
	.byte	52
	.byte	94
	.byte	2
	.byte	32
	.byte	55
	.byte	1
	.byte	10
	.byte	16
	.byte	50
	.byte	127
	.byte	-102
	.byte	37
	.byte	109
	.byte	-104
	.byte	16
	.byte	82
	.byte	121
	.byte	5
	.byte	59
	.byte	85
	.byte	1
	.byte	35
	.byte	54
	.byte	1
	.byte	13
	.byte	20
	.byte	40
	.byte	-114
	.byte	-89
	.byte	17
	.byte	110
	.byte	-99
	.byte	2
	.byte	71
	.byte	112
	.byte	1
	.byte	44
	.byte	72
	.byte	1
	.byte	27
	.byte	45
	.byte	1
	.byte	11
	.byte	17
	.byte	30
	.byte	-81
	.byte	-68
	.byte	9
	.byte	124
	.byte	-87
	.byte	1
	.byte	74
	.byte	116
	.byte	1
	.byte	48
	.byte	78
	.byte	1
	.byte	30
	.byte	49
	.byte	1
	.byte	11
	.byte	18
	.byte	10
	.byte	-34
	.byte	-33
	.byte	2
	.byte	-106
	.byte	-62
	.byte	1
	.byte	83
	.byte	-128
	.byte	1
	.byte	48
	.byte	79
	.byte	1
	.byte	27
	.byte	45
	.byte	1
	.byte	11
	.byte	17
	.byte	36
	.byte	41
	.byte	-21
	.byte	29
	.byte	36
	.byte	-63
	.byte	10
	.byte	27
	.byte	111
	.zero	9
	.byte	85
	.byte	-91
	.byte	-34
	.byte	-79
	.byte	-94
	.byte	-41
	.byte	110
	.byte	-121
	.byte	-61
	.byte	57
	.byte	113
	.byte	-88
	.byte	23
	.byte	83
	.byte	120
	.byte	10
	.byte	49
	.byte	61
	.byte	85
	.byte	-66
	.byte	-33
	.byte	36
	.byte	-117
	.byte	-56
	.byte	5
	.byte	90
	.byte	-110
	.byte	1
	.byte	60
	.byte	103
	.byte	1
	.byte	38
	.byte	65
	.byte	1
	.byte	18
	.byte	30
	.byte	72
	.byte	-54
	.byte	-33
	.byte	23
	.byte	-115
	.byte	-57
	.byte	2
	.byte	86
	.byte	-116
	.byte	1
	.byte	56
	.byte	97
	.byte	1
	.byte	36
	.byte	61
	.byte	1
	.byte	16
	.byte	27
	.byte	55
	.byte	-38
	.byte	-31
	.byte	13
	.byte	-111
	.byte	-56
	.byte	1
	.byte	86
	.byte	-115
	.byte	1
	.byte	57
	.byte	99
	.byte	1
	.byte	35
	.byte	61
	.byte	1
	.byte	13
	.byte	22
	.byte	15
	.byte	-21
	.byte	-44
	.byte	1
	.byte	-124
	.byte	-72
	.byte	1
	.byte	84
	.byte	-117
	.byte	1
	.byte	57
	.byte	97
	.byte	1
	.byte	34
	.byte	56
	.byte	1
	.byte	14
	.byte	23
	.byte	-75
	.byte	21
	.byte	-55
	.byte	61
	.byte	37
	.byte	123
	.byte	10
	.byte	38
	.byte	71
	.zero	9
	.byte	47
	.byte	106
	.byte	-84
	.byte	95
	.byte	104
	.byte	-83
	.byte	42
	.byte	93
	.byte	-97
	.byte	18
	.byte	77
	.byte	-125
	.byte	4
	.byte	50
	.byte	81
	.byte	1
	.byte	17
	.byte	23
	.byte	62
	.byte	-109
	.byte	-57
	.byte	44
	.byte	-126
	.byte	-67
	.byte	28
	.byte	102
	.byte	-102
	.byte	18
	.byte	75
	.byte	115
	.byte	2
	.byte	44
	.byte	65
	.byte	1
	.byte	12
	.byte	19
	.byte	55
	.byte	-103
	.byte	-46
	.byte	24
	.byte	-126
	.byte	-62
	.byte	3
	.byte	93
	.byte	-110
	.byte	1
	.byte	61
	.byte	97
	.byte	1
	.byte	31
	.byte	50
	.byte	1
	.byte	10
	.byte	16
	.byte	49
	.byte	-70
	.byte	-33
	.byte	17
	.byte	-108
	.byte	-52
	.byte	1
	.byte	96
	.byte	-114
	.byte	1
	.byte	53
	.byte	83
	.byte	1
	.byte	26
	.byte	44
	.byte	1
	.byte	11
	.byte	17
	.byte	13
	.byte	-39
	.byte	-44
	.byte	2
	.byte	-120
	.byte	-76
	.byte	1
	.byte	78
	.byte	124
	.byte	1
	.byte	50
	.byte	83
	.byte	1
	.byte	29
	.byte	49
	.byte	1
	.byte	14
	.byte	23
	.byte	-59
	.byte	13
	.byte	-9
	.byte	82
	.byte	17
	.byte	-34
	.byte	25
	.byte	17
	.byte	-94
	.zero	9
	.byte	126
	.byte	-70
	.byte	-9
	.byte	-22
	.byte	-65
	.byte	-13
	.byte	-80
	.byte	-79
	.byte	-22
	.byte	104
	.byte	-98
	.byte	-36
	.byte	66
	.byte	-128
	.byte	-70
	.byte	55
	.byte	90
	.byte	-119
	.byte	111
	.byte	-59
	.byte	-14
	.byte	46
	.byte	-98
	.byte	-37
	.byte	9
	.byte	104
	.byte	-85
	.byte	2
	.byte	65
	.byte	125
	.byte	1
	.byte	44
	.byte	80
	.byte	1
	.byte	17
	.byte	91
	.byte	104
	.byte	-48
	.byte	-11
	.byte	39
	.byte	-88
	.byte	-32
	.byte	3
	.byte	109
	.byte	-94
	.byte	1
	.byte	79
	.byte	124
	.byte	1
	.byte	50
	.byte	102
	.byte	1
	.byte	43
	.byte	102
	.byte	84
	.byte	-36
	.byte	-10
	.byte	31
	.byte	-79
	.byte	-25
	.byte	2
	.byte	115
	.byte	-76
	.byte	1
	.byte	79
	.byte	-122
	.byte	1
	.byte	55
	.byte	77
	.byte	1
	.byte	60
	.byte	79
	.byte	43
	.byte	-13
	.byte	-16
	.byte	8
	.byte	-76
	.byte	-39
	.byte	1
	.byte	115
	.byte	-90
	.byte	1
	.byte	84
	.byte	121
	.byte	1
	.byte	51
	.byte	67
	.byte	1
	.byte	16
	.byte	6
	.type	vp9_default_if_uv_probs, %object
	.size	vp9_default_if_uv_probs, 90
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
	.byte	48
	.byte	12
	.byte	-102
	.byte	-101
	.byte	-117
	.byte	90
	.byte	34
	.byte	117
	.byte	119
	.byte	67
	.byte	6
	.byte	25
	.byte	-52
	.byte	-13
	.byte	-98
	.byte	13
	.byte	21
	.byte	96
	.byte	97
	.byte	5
	.byte	44
	.byte	-125
	.byte	-80
	.byte	-117
	.byte	48
	.byte	68
	.byte	97
	.byte	83
	.byte	5
	.byte	42
	.byte	-100
	.byte	111
	.byte	-104
	.byte	26
	.byte	49
	.byte	-104
	.byte	80
	.byte	5
	.byte	58
	.byte	-78
	.byte	74
	.byte	83
	.byte	33
	.byte	62
	.byte	-111
	.byte	86
	.byte	5
	.byte	32
	.byte	-102
	.byte	-64
	.byte	-88
	.byte	14
	.byte	22
	.byte	-93
	.byte	85
	.byte	5
	.byte	32
	.byte	-100
	.byte	-40
	.byte	-108
	.byte	19
	.byte	29
	.byte	73
	.byte	77
	.byte	7
	.byte	64
	.byte	116
	.byte	-124
	.byte	122
	.byte	37
	.byte	126
	.byte	120
	.byte	101
	.byte	21
	.byte	107
	.byte	-75
	.byte	-64
	.byte	103
	.byte	19
	.byte	67
	.byte	125
	.zero	2
	.type	vp9_default_if_y_probs, %object
	.size	vp9_default_if_y_probs, 36
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
	.byte	-124
	.byte	68
	.byte	18
	.byte	-91
	.byte	-39
	.byte	-60
	.byte	45
	.byte	40
	.byte	78
	.byte	-83
	.byte	80
	.byte	19
	.byte	-80
	.byte	-16
	.byte	-63
	.byte	64
	.byte	35
	.byte	46
	.byte	-35
	.byte	-121
	.byte	38
	.byte	-62
	.byte	-8
	.byte	121
	.byte	96
	.byte	85
	.byte	29
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
	.word	22
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC49:
	ASCII(.string	"IN VP9DEC_Init\n" )
.LC52:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC54:
	ASCII(.string	"data_sz == 0\n" )
	.zero	2
.LC56:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC58:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC60:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC62:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC64:
	ASCII(.string	"line: %d, fs is NULL!\n" )
	.zero	1
.LC67:
	ASCII(.string	"%s  idx=%d\n" )
	.zero	4
.LC69:
	ASCII(.string	"FSP_GetLogicFs err" )
	.zero	5
.LC71:
	ASCII(.string	"fsp.c,L%d: %s\n" )
	.zero	1
.LC73:
	ASCII(.string	"Invalid frame sync code\n" )
	.zero	7
.LC82:
	ASCII(.string	"%s  %d ERR\n" )
	.zero	4
.LC91:
	ASCII(.string	"%s:%d this_size:%d is invalid!\n" )
.LC96:
	ASCII(.string	"4:4:4 color is not supported in profile 0 or 2 (%s : %d)\n" )
	.zero	6
.LC98:
	ASCII(.string	"Invalid frame marker\n" )
	.zero	2
.LC101:
	ASCII(.string	"%s:%d w&h=%dx%d is invalid!\n" )
	.zero	3
.LC103:
	ASCII(.string	"VP9_Set_DecParam but logic fs is null!\n" )
.LC105:
	ASCII(.string	"Decord FS is NULL!\n" )
	.zero	4
.LC107:
	ASCII(.string	"VP9_Set_DecParam but cur logic pstDecodeFs is null!\n" )
	.zero	3
.LC109:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC111:
	ASCII(.string	"pic_width_in_pix:%d, pic_height_in_pix:%d\n" )
	.zero	5
.LC113:
	ASCII(.string	"vp9 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC117:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC119:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC121:
	ASCII(.string	"vp9 alloc frame only\n" )
	.zero	2
.LC143:
	ASCII(.string	"%s:%d size is invalid  size:%d bslen:%d\n" )
	.zero	7
.LC147:
	ASCII(.string	"ERROR:Vp9_ReadCompressedHeader\n" )
.LC150:
	ASCII(.string	"pCurImg is null\n" )
	.zero	7
.LC153:
	ASCII(.string	"err_level(%d) over ref_thr(%d)\n" )
.LC155:
	ASCII(.string	"line: %d pToQueImg is null\n" )
	.zero	4
.LC157:
	ASCII(.string	"insert img to Voqueue failed!\n" )
	.zero	1
.LC159:
	ASCII(.string	"pu8ProbCntVir == NULL\n" )
	.zero	1
.LC161:
	ASCII(.string	"get_free_fb failed!\n" )
	.zero	3
.LC163:
	ASCII(.string	"bit_depth(%d) > 10.\n" )
	.zero	3
.LC166:
	ASCII(.string	"ERROR: pCtx->StreamParam.Length(%d) < 8\n" )
	.zero	7
.LC170:
	ASCII(.string	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\n" )
	.zero	4
.LC172:
	ASCII(.string	"ERROR: No Img buffer is allocated\n" )
	.zero	5
.LC175:
	ASCII(.string	"%s %d, no fsp\n" )
	.zero	1
.LC177:
	ASCII(.string	"VP9_GetImageBuffer From Queue err\n" )
	.zero	5
.LC179:
	ASCII(.string	"ERROR: VP9_Set_DecParam\n" )
	.zero	7
.LC182:
	ASCII(.string	"VP9_DecOneNal ERR\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
