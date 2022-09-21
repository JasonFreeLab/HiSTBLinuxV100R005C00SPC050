#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"yuv_convert.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	IMAGE_TileTo2D
	.type	IMAGE_TileTo2D, %function
IMAGE_TileTo2D:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	mov	w21, w2
	mov	w19, w1
	mov	x20, x3
	str	w2, [x29, 104]
	bl	_mcount
	ldr	w0, [x28, 44]
	str	w0, [x29, 100]
	ldr	w0, [x28, 48]
	str	w0, [x29, 96]
	cbz	w21, .L1
	ldr	x27, .LC0
	lsr	w0, w19, 2
	ldr	x25, .LC2
	str	w0, [x29, 108]
	stp	wzr, wzr, [x29, 148]
	str	wzr, [x29, 156]
	.p2align 2
.L7:
	cbz	w19, .L9
	ldr	w1, [x29, 156]
	mov	w26, 0
	ldp	w24, w2, [x29, 148]
	str	x2, [x29, 128]
	lsr	w21, w1, 4
	ldr	w2, [x29, 100]
	lsr	w0, w1, 5
	and	x22, x1, 15
	mul	w23, w2, w21
	ldr	w2, [x29, 96]
	ubfiz	x21, x21, 2, 1
	mul	w0, w0, w2
	str	x0, [x29, 120]
	and	x0, x1, 31
	str	x0, [x29, 112]
	b	.L6
	.p2align 3
.L5:
	uxtw	x3, w2
	ldr	x9, [x20]
	add	x3, x21, x3
	ldr	x1, [x28]
	ubfiz	x4, x4, 10, 22
	add	x0, x24, x26, uxtw
	add	x3, x22, x3, lsl 4
	ldr	x8, [x27, 104]
	mov	x2, 64
	add	x0, x9, x0
	add	w26, w26, 64
	ldr	w3, [x25, x3, lsl 2]
	ubfiz	x3, x3, 6, 26
	add	x3, x3, x23
	add	x4, x3, x4
	add	x1, x1, x4
	blr	x8
	cmp	w19, w26
	bls	.L9
.L6:
	ldr	w0, [x28, 32]
	lsr	w4, w26, 6
	and	w2, w4, 3
	cmp	w0, 10
	bne	.L5
	mov	w3, w2
	ldr	x2, [x29, 112]
	ubfiz	x8, x3, 5, 2
	ldr	x1, [x20, 8]
	add	x8, x8, x2
	ldr	x2, [x29, 128]
	ubfx	x0, x26, 2, 30
	str	w3, [x29, 136]
	add	x0, x0, x2
	ldr	x3, [x29, 120]
	add	x0, x1, x0
	ldr	x1, .LC1
	ldr	x10, [x28, 8]
	mov	x2, 16
	ldr	x9, [x27, 104]
	ldr	w1, [x1, x8, lsl 2]
	str	w4, [x29, 144]
	add	w1, w1, w4, lsl 5
	ubfiz	x1, x1, 4, 26
	add	x1, x1, x3
	add	x1, x10, x1
	blr	x9
	ldr	w3, [x29, 136]
	ldr	w4, [x29, 144]
	mov	w2, w3
	b	.L5
	.p2align 3
.L9:
	ldr	w1, [x29, 148]
	ldr	w0, [x29, 156]
	add	w1, w1, w19
	str	w1, [x29, 148]
	ldr	w1, [x29, 104]
	add	w0, w0, 1
	str	w0, [x29, 156]
	cmp	w1, w0
	ldr	w0, [x29, 152]
	ldr	w1, [x29, 108]
	add	w0, w0, w1
	str	w0, [x29, 152]
	bne	.L7
	ldr	w1, [x29, 104]
	lsr	w0, w1, 1
	str	w0, [x29, 112]
	cbz	w0, .L1
	ldr	w1, [x29, 100]
	ldr	x27, .LC0
	lsr	w0, w1, 1
	ldr	w1, [x29, 96]
	ldr	x25, .LC2
	str	w0, [x29, 100]
	lsr	w0, w1, 1
	stp	wzr, wzr, [x29, 148]
	str	wzr, [x29, 156]
	str	w0, [x29, 104]
	.p2align 2
.L14:
	cbz	w19, .L15
	ldr	w1, [x29, 156]
	mov	w26, 0
	ldp	w24, w2, [x29, 148]
	str	x2, [x29, 136]
	lsr	w21, w1, 3
	ldr	w2, [x29, 100]
	lsr	w0, w1, 4
	and	x22, x1, 7
	mul	w23, w21, w2
	ldr	w2, [x29, 104]
	ubfiz	x21, x21, 2, 1
	mul	w0, w0, w2
	str	x0, [x29, 128]
	and	x0, x1, 15
	str	x0, [x29, 120]
	b	.L13
	.p2align 3
.L12:
	and	x4, x3, 3
	add	x9, x25, 512
	add	x4, x21, x4
	ldr	x10, [x20, 16]
	ldr	x1, [x28, 16]
	ubfiz	x3, x3, 9, 23
	add	x4, x22, x4, lsl 3
	add	x0, x24, x26, uxtw
	ldr	x7, [x27, 104]
	mov	x2, 64
	add	x0, x10, x0
	add	w26, w26, 64
	ldr	w4, [x9, x4, lsl 2]
	ubfiz	x4, x4, 6, 26
	add	x4, x4, x23
	add	x3, x4, x3
	add	x1, x1, x3
	blr	x7
	cmp	w19, w26
	bls	.L15
.L13:
	ldr	w0, [x28, 32]
	lsr	w3, w26, 6
	cmp	w0, 10
	bne	.L12
	ldr	x0, .LC1
	ldr	x2, [x29, 136]
	add	x1, x0, 512
	ubfx	x0, x26, 2, 30
	add	x0, x0, x2
	ldr	x2, [x29, 120]
	str	w3, [x29, 144]
	ldr	x9, [x20, 24]
	ldr	w1, [x1, x2, lsl 2]
	mov	x2, 16
	ldr	x7, [x28, 24]
	add	x0, x9, x0
	add	w1, w1, w3, lsl 4
	ldr	x3, [x29, 128]
	ubfiz	x1, x1, 4, 26
	ldr	x4, [x27, 104]
	add	x1, x1, x3
	add	x1, x7, x1
	blr	x4
	ldr	w3, [x29, 144]
	b	.L12
	.p2align 3
.L15:
	ldr	w1, [x29, 148]
	ldr	w0, [x29, 156]
	add	w1, w1, w19
	str	w1, [x29, 148]
	ldr	w1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 156]
	cmp	w0, w1
	ldr	w0, [x29, 152]
	ldr	w1, [x29, 108]
	add	w0, w0, w1
	str	w0, [x29, 152]
	bne	.L14
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.size	IMAGE_TileTo2D, .-IMAGE_TileTo2D
	.align	3
.LC0:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IMAGE_LinearTo2D
	.type	IMAGE_LinearTo2D, %function
IMAGE_LinearTo2D:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	mov	w21, w2
	mov	w19, w1
	mov	x20, x3
	str	w2, [x29, 108]
	bl	_mcount
	ldr	w0, [x28, 48]
	str	w0, [x29, 104]
	cbz	w21, .L29
	uxtw	x0, w19
	mov	w23, 0
	str	x0, [x29, 112]
	mov	w21, 0
	lsr	w0, w19, 2
	ldr	x27, .LC5
	str	wzr, [x29, 124]
	str	w0, [x29, 120]
	b	.L32
	.p2align 3
.L34:
	ldr	w1, [x28, 44]
	ldp	w6, w5, [x29, 120]
	lsr	w1, w1, 4
	ldr	x0, [x20]
	ldr	x4, [x28]
	add	w5, w5, w6
	mul	w1, w1, w21
	ldr	x3, [x27, 104]
	add	x0, x0, x23, uxtw
	ldr	x2, [x29, 112]
	add	x1, x4, x1
	str	w5, [x29, 124]
	add	w21, w21, 1
	add	w23, w23, w19
	blr	x3
	ldr	w0, [x29, 108]
	cmp	w0, w21
	beq	.L56
.L32:
	ldr	w0, [x28, 32]
	cmp	w0, 10
	bne	.L34
	cbz	w19, .L34
	ldr	w0, [x29, 104]
	lsr	w22, w21, 5
	ldr	w25, [x29, 124]
	mov	w26, 0
	and	x24, x21, 31
	mul	w22, w22, w0
	.p2align 2
.L35:
	lsr	w3, w26, 6
	ldr	x4, .LC6
	ubfiz	x7, x3, 5, 2
	ubfx	x0, x26, 2, 30
	add	x7, x7, x24
	ldr	x9, [x20, 8]
	ldr	x1, [x28, 8]
	add	x0, x0, x25
	ldr	x8, [x27, 104]
	mov	x2, 16
	ldr	w7, [x4, x7, lsl 2]
	add	x0, x9, x0
	add	w26, w26, 64
	add	w3, w7, w3, lsl 5
	ubfiz	x3, x3, 4, 26
	add	x3, x3, x22
	add	x1, x1, x3
	blr	x8
	cmp	w19, w26
	bhi	.L35
	b	.L34
	.p2align 3
.L29:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L56:
	ldr	w1, [x29, 108]
	lsr	w0, w1, 1
	str	w0, [x29, 108]
	cbz	w0, .L29
	ldr	w1, [x29, 104]
	mov	w23, 0
	mov	w21, 0
	str	wzr, [x29, 124]
	lsr	w0, w1, 1
	str	w0, [x29, 104]
	b	.L38
	.p2align 3
.L39:
	ldr	w1, [x28, 44]
	ldp	w6, w5, [x29, 120]
	lsr	w1, w1, 4
	ldr	x0, [x20, 16]
	ldr	x4, [x28, 16]
	add	w5, w5, w6
	mul	w1, w1, w21
	ldr	x3, [x27, 104]
	add	x0, x0, x23, uxtw
	ldr	x2, [x29, 112]
	add	x1, x4, x1
	str	w5, [x29, 124]
	add	w21, w21, 1
	add	w23, w23, w19
	blr	x3
	ldr	w0, [x29, 108]
	cmp	w21, w0
	beq	.L29
.L38:
	ldr	w0, [x28, 32]
	cmp	w0, 10
	bne	.L39
	cbz	w19, .L39
	ldr	x0, .LC6
	lsr	w22, w21, 4
	ldr	w25, [x29, 124]
	mov	w26, 0
	add	x1, x0, 512
	and	w0, w21, 15
	ldr	w24, [x1, w0, uxtw 2]
	ldr	w0, [x29, 104]
	mul	w22, w22, w0
	.p2align 2
.L40:
	lsr	w1, w26, 6
	ubfx	x0, x26, 2, 30
	ldr	x7, [x20, 24]
	add	x0, x0, x25
	add	w1, w24, w1, lsl 4
	ldr	x8, [x28, 24]
	ubfiz	x1, x1, 4, 26
	ldr	x4, [x27, 104]
	add	x1, x1, x22
	mov	x2, 16
	add	x0, x7, x0
	add	x1, x8, x1
	add	w26, w26, 64
	blr	x4
	cmp	w19, w26
	bhi	.L40
	b	.L39
	.size	IMAGE_LinearTo2D, .-IMAGE_LinearTo2D
	.align	3
.LC5:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IMAGE_ConvertTo2D
	.type	IMAGE_ConvertTo2D, %function
IMAGE_ConvertTo2D:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x22, x3
	bl	_mcount
	ldr	w0, [x19, 40]
	mov	x3, x22
	mov	w2, w21
	mov	w1, w20
	cmp	w0, 1
	mov	x0, x19
	beq	.L60
	bl	IMAGE_LinearTo2D
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L60:
	bl	IMAGE_TileTo2D
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	IMAGE_ConvertTo2D, .-IMAGE_ConvertTo2D
	.global	g_RowMapTable_UV
	.global	g_RowMapTable_Y
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	g_RowMapTable_Y_2b, %object
	.size	g_RowMapTable_Y_2b, 512
g_RowMapTable_Y_2b:
	.word	0
	.word	16
	.word	1
	.word	17
	.word	2
	.word	18
	.word	3
	.word	19
	.word	4
	.word	20
	.word	5
	.word	21
	.word	6
	.word	22
	.word	7
	.word	23
	.word	8
	.word	24
	.word	9
	.word	25
	.word	10
	.word	26
	.word	11
	.word	27
	.word	12
	.word	28
	.word	13
	.word	29
	.word	14
	.word	30
	.word	15
	.word	31
	.word	16
	.word	0
	.word	17
	.word	1
	.word	18
	.word	2
	.word	19
	.word	3
	.word	20
	.word	4
	.word	21
	.word	5
	.word	22
	.word	6
	.word	23
	.word	7
	.word	24
	.word	8
	.word	25
	.word	9
	.word	26
	.word	10
	.word	27
	.word	11
	.word	28
	.word	12
	.word	29
	.word	13
	.word	30
	.word	14
	.word	31
	.word	15
	.word	16
	.word	0
	.word	17
	.word	1
	.word	18
	.word	2
	.word	19
	.word	3
	.word	20
	.word	4
	.word	21
	.word	5
	.word	22
	.word	6
	.word	23
	.word	7
	.word	24
	.word	8
	.word	25
	.word	9
	.word	26
	.word	10
	.word	27
	.word	11
	.word	28
	.word	12
	.word	29
	.word	13
	.word	30
	.word	14
	.word	31
	.word	15
	.word	0
	.word	16
	.word	1
	.word	17
	.word	2
	.word	18
	.word	3
	.word	19
	.word	4
	.word	20
	.word	5
	.word	21
	.word	6
	.word	22
	.word	7
	.word	23
	.word	8
	.word	24
	.word	9
	.word	25
	.word	10
	.word	26
	.word	11
	.word	27
	.word	12
	.word	28
	.word	13
	.word	29
	.word	14
	.word	30
	.word	15
	.word	31
	.type	g_RowMapTable_UV_2b, %object
	.size	g_RowMapTable_UV_2b, 64
g_RowMapTable_UV_2b:
	.word	0
	.word	8
	.word	1
	.word	9
	.word	2
	.word	10
	.word	3
	.word	11
	.word	4
	.word	12
	.word	5
	.word	13
	.word	6
	.word	14
	.word	7
	.word	15
	.data
	.align	3
.LANCHOR1 = . + 0
	.type	g_RowMapTable_Y, %object
	.size	g_RowMapTable_Y, 512
g_RowMapTable_Y:
	.word	0
	.word	12
	.word	1
	.word	13
	.word	2
	.word	14
	.word	3
	.word	15
	.word	4
	.word	8
	.word	5
	.word	9
	.word	6
	.word	10
	.word	7
	.word	11
	.word	4
	.word	8
	.word	5
	.word	9
	.word	6
	.word	10
	.word	7
	.word	11
	.word	0
	.word	12
	.word	1
	.word	13
	.word	2
	.word	14
	.word	3
	.word	15
	.word	8
	.word	4
	.word	9
	.word	5
	.word	10
	.word	6
	.word	11
	.word	7
	.word	12
	.word	0
	.word	13
	.word	1
	.word	14
	.word	2
	.word	15
	.word	3
	.word	12
	.word	0
	.word	13
	.word	1
	.word	14
	.word	2
	.word	15
	.word	3
	.word	8
	.word	4
	.word	9
	.word	5
	.word	10
	.word	6
	.word	11
	.word	7
	.word	0
	.word	12
	.word	1
	.word	13
	.word	2
	.word	14
	.word	3
	.word	15
	.word	4
	.word	8
	.word	5
	.word	9
	.word	6
	.word	10
	.word	7
	.word	11
	.word	4
	.word	8
	.word	5
	.word	9
	.word	6
	.word	10
	.word	7
	.word	11
	.word	0
	.word	12
	.word	1
	.word	13
	.word	2
	.word	14
	.word	3
	.word	15
	.word	8
	.word	4
	.word	9
	.word	5
	.word	10
	.word	6
	.word	11
	.word	7
	.word	12
	.word	0
	.word	13
	.word	1
	.word	14
	.word	2
	.word	15
	.word	3
	.word	12
	.word	0
	.word	13
	.word	1
	.word	14
	.word	2
	.word	15
	.word	3
	.word	8
	.word	4
	.word	9
	.word	5
	.word	10
	.word	6
	.word	11
	.word	7
	.type	g_RowMapTable_UV, %object
	.size	g_RowMapTable_UV, 256
g_RowMapTable_UV:
	.word	0
	.word	4
	.word	1
	.word	5
	.word	2
	.word	6
	.word	3
	.word	7
	.word	4
	.word	0
	.word	5
	.word	1
	.word	6
	.word	2
	.word	7
	.word	3
	.word	4
	.word	0
	.word	5
	.word	1
	.word	6
	.word	2
	.word	7
	.word	3
	.word	0
	.word	4
	.word	1
	.word	5
	.word	2
	.word	6
	.word	3
	.word	7
	.word	0
	.word	4
	.word	1
	.word	5
	.word	2
	.word	6
	.word	3
	.word	7
	.word	4
	.word	0
	.word	5
	.word	1
	.word	6
	.word	2
	.word	7
	.word	3
	.word	4
	.word	0
	.word	5
	.word	1
	.word	6
	.word	2
	.word	7
	.word	3
	.word	0
	.word	4
	.word	1
	.word	5
	.word	2
	.word	6
	.word	3
	.word	7
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
