#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"yuv_convert.c"
	.text
	.align	2
	.global	IMAGE_TileTo2D
	.type	IMAGE_TileTo2D, %function
IMAGE_TileTo2D:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	mov	r6, r3
	ldr	r3, [r0, #28]
	cmp	r2, #0
	mov	r7, r0
	str	r2, [fp, #-84]
	str	r1, [fp, #-48]
	str	r3, [fp, #-88]
	ldr	r3, [r0, #32]
	str	r3, [fp, #-92]
	beq	.L1
	ldr	r10, .L31
	mov	r3, #0
	mov	r2, r1, lsr #2
	str	r3, [fp, #-64]
	str	r2, [fp, #-80]
	str	r3, [fp, #-68]
	str	r3, [fp, #-52]
.L3:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L8
	ldr	r1, [fp, #-68]
	mov	r9, #0
	and	r0, r1, #15
	str	r0, [fp, #-56]
	mov	r8, r1, lsr #4
	mov	r2, r1, lsr #5
	and	r3, r8, #1
	ldr	r0, [fp, #-88]
	mov	r3, r3, asl #2
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-92]
	mul	r8, r0, r8
	mul	r3, r3, r2
	str	r3, [fp, #-72]
	and	r3, r1, #31
	str	r3, [fp, #-76]
	mov	r3, r6
	mov	r6, r8
	mov	r8, r3
	b	.L6
.L5:
	ldr	r3, [fp, #-60]
	ldr	r1, [r7]
	add	r4, r3, r4
	ldr	r3, [fp, #-52]
	ldr	r0, [r8]
	add	r2, r3, r9
	ldr	r3, [fp, #-56]
	add	r0, r0, r2
	mov	r2, #64
	add	r4, r3, r4, lsl #4
	ldr	r3, .L31+4
	add	r9, r9, #64
	add	r4, r3, r4, lsl #2
	ldr	r3, [r10, #52]
	ldr	lr, [r4, #256]
	add	lr, r6, lr, lsl #6
	add	r5, lr, r5, lsl #10
	add	r1, r1, r5
	blx	r3
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bls	.L29
.L6:
	ldr	r2, [r7, #16]
	mov	r5, r9, lsr #6
	and	r4, r5, #3
	cmp	r2, #10
	bne	.L5
	ldr	r3, [fp, #-64]
	ldr	r2, [r8, #4]
	add	r0, r3, r9, lsr #2
	ldr	r3, [fp, #-76]
	ldr	lr, [r7, #4]
	add	r0, r2, r0
	add	r1, r3, r4, lsl #4
	ldr	r3, .L31+4
	mov	r2, #16
	ldr	r1, [r3, r1, asl #2]
	ldr	r3, [fp, #-72]
	add	r1, r1, r5, lsl #5
	mov	r1, r1, asl #6
	add	r1, r3, r1, lsr #2
	ldr	r3, [r10, #52]
	add	r1, lr, r1
	blx	r3
	b	.L5
.L29:
	mov	r6, r8
.L8:
	ldr	r2, [fp, #-52]
	ldr	r1, [fp, #-48]
	ldr	r3, [fp, #-68]
	add	r2, r2, r1
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-68]
	cmp	r3, r2
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	str	r3, [fp, #-64]
	bne	.L3
	ldr	r3, [fp, #-68]
	movs	r3, r3, lsr #1
	str	r3, [fp, #-76]
	beq	.L1
	ldr	r2, [fp, #-88]
	mov	r3, #0
	ldr	r8, .L31
	mov	r10, r3
	str	r3, [fp, #-60]
	mov	r2, r2, lsr #1
	str	r2, [fp, #-88]
	ldr	r2, [fp, #-92]
	str	r3, [fp, #-64]
	mov	r2, r2, lsr #1
	str	r2, [fp, #-84]
.L9:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L13
	ldr	r3, [fp, #-64]
	mov	r5, #0
	ldr	ip, [fp, #-88]
	and	r1, r3, #15
	mov	r2, r3, lsr #3
	mov	r0, r3, lsr #4
	and	r9, r2, #1
	and	r3, r3, #7
	mul	r2, ip, r2
	mov	r9, r9, asl #2
	str	r3, [fp, #-52]
	mov	r3, r9
	mov	r9, r6
	mov	r6, r7
	mov	r7, r3
	str	r2, [fp, #-56]
	mov	r2, r0
	ldr	r0, [fp, #-84]
	mul	r2, r0, r2
	str	r2, [fp, #-68]
	mov	r2, r1, asl #2
	str	r2, [fp, #-72]
	b	.L12
.L11:
	and	lr, r4, #3
	ldr	r3, [fp, #-52]
	add	lr, r7, lr
	ldr	r1, [r6, #8]
	ldr	r0, [r9, #8]
	add	r2, r10, r5
	add	lr, r3, lr, lsl #3
	ldr	r3, .L31+4
	add	r0, r0, r2
	mov	r2, #64
	add	lr, r3, lr, lsl #2
	ldr	r3, [fp, #-56]
	add	r5, r5, #64
	ldr	lr, [lr, #800]
	add	lr, r3, lr, lsl #6
	ldr	r3, [r8, #52]
	add	r4, lr, r4, lsl #9
	add	r1, r1, r4
	blx	r3
	ldr	r3, [fp, #-48]
	cmp	r3, r5
	bls	.L30
.L12:
	ldr	r2, [r6, #16]
	mov	r4, r5, lsr #6
	cmp	r2, #10
	bne	.L11
	ldr	r3, .L31+4
	ldr	r2, [fp, #-72]
	ldr	lr, [r9, #12]
	add	r2, r3, r2
	ldr	r3, [fp, #-60]
	ldr	r1, [r2, #768]
	add	r0, r3, r5, lsr #2
	ldr	r3, [fp, #-68]
	mov	r2, #16
	add	r1, r1, r4, lsl #4
	add	r0, lr, r0
	mov	r1, r1, asl #6
	add	r1, r3, r1, lsr #2
	ldr	r3, [r6, #12]
	add	r1, r3, r1
	ldr	r3, [r8, #52]
	blx	r3
	b	.L11
.L30:
	mov	r7, r6
	mov	r6, r9
.L13:
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-64]
	add	r10, r10, r2
	ldr	r2, [fp, #-76]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, r2
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	str	r3, [fp, #-60]
	bne	.L9
.L1:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L32:
	.align	2
.L31:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	IMAGE_TileTo2D, .-IMAGE_TileTo2D
	.align	2
	.global	IMAGE_LinearTo2D
	.type	IMAGE_LinearTo2D, %function
IMAGE_LinearTo2D:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r8, r3
	ldr	r3, [r0, #32]
	cmp	r2, #0
	mov	r6, r1
	str	r2, [fp, #-56]
	str	r3, [fp, #-68]
	beq	.L33
	mov	r9, #0
	mov	r3, r1, lsr #2
	str	r3, [fp, #-60]
	mov	r3, r8
	ldr	r7, .L62
	mov	r10, r9
	str	r9, [fp, #-52]
	mov	r8, r0
	mov	r5, r3
	b	.L36
.L38:
	ldr	r1, [r8, #28]
	mov	r2, r6
	ldr	r3, [fp, #-60]
	ldr	lr, [r8]
	ldr	r0, [r5]
	add	r9, r9, r3
	mov	r1, r1, lsr #4
	ldr	r3, [fp, #-52]
	ldr	r4, [r7, #52]
	add	r0, r0, r3
	add	r3, r3, r6
	mla	r1, r1, r10, lr
	str	r3, [fp, #-52]
	blx	r4
	ldr	r3, [fp, #-56]
	add	r10, r10, #1
	cmp	r10, r3
	beq	.L61
.L36:
	ldr	r2, [r8, #16]
	cmp	r2, #10
	bne	.L38
	cmp	r6, #0
	beq	.L38
	and	r2, r10, #31
	str	r2, [fp, #-48]
	ldr	r2, [fp, #-68]
	mov	r3, r10, lsr #5
	str	r10, [fp, #-64]
	mov	r4, #0
	mov	r10, r8
	mov	r8, r6
	mul	r3, r2, r3
	mov	r6, r3
.L39:
	mov	lr, r4, lsr #6
	ldr	r3, [fp, #-48]
	and	r2, lr, #3
	ldr	r0, [r5, #4]
	add	r1, r9, r4, lsr #2
	add	r4, r4, #64
	add	r2, r3, r2, lsl #4
	ldr	r3, .L62+4
	add	r0, r0, r1
	ldr	r1, [r3, r2, asl #2]
	mov	r2, #16
	ldr	r3, [r10, #4]
	add	r1, r1, lr, lsl #5
	mov	r1, r1, asl #6
	add	r1, r6, r1, lsr #2
	add	r1, r3, r1
	ldr	r3, [r7, #52]
	blx	r3
	cmp	r8, r4
	bhi	.L39
	mov	r6, r8
	mov	r8, r10
	ldr	r10, [fp, #-64]
	b	.L38
.L33:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L61:
	mov	r3, r5
	mov	r5, r8
	mov	r8, r3
	movs	r3, r10, lsr #1
	str	r3, [fp, #-64]
	beq	.L33
	ldr	r3, [fp, #-68]
	mov	r4, #0
	str	r4, [fp, #-56]
	str	r4, [fp, #-52]
	mov	r3, r3, lsr #1
	str	r3, [fp, #-68]
	b	.L42
.L43:
	ldr	ip, [fp, #-56]
	mov	r2, r6
	ldr	r1, [r5, #28]
	ldr	r0, [r8, #8]
	ldr	lr, [r5, #8]
	add	r0, r0, ip
	add	ip, ip, r6
	str	ip, [fp, #-56]
	mov	r1, r1, lsr #4
	ldr	ip, [fp, #-52]
	ldr	r3, [fp, #-60]
	mla	r1, r1, ip, lr
	add	ip, ip, #1
	add	r4, r4, r3
	ldr	r3, [r7, #52]
	mov	r9, ip
	str	ip, [fp, #-52]
	blx	r3
	ldr	r3, [fp, #-64]
	cmp	r9, r3
	beq	.L33
.L42:
	ldr	r3, [r5, #16]
	cmp	r3, #10
	bne	.L43
	cmp	r6, #0
	beq	.L43
	ldr	r3, [fp, #-52]
	mov	r9, #0
	ldr	r1, [fp, #-68]
	mov	r2, r3, lsr #4
	and	r3, r3, #15
	mul	r2, r1, r2
	str	r2, [fp, #-48]
	ldr	r2, .L62+4
	add	r10, r2, r3, lsl #2
.L44:
	ldr	r3, [r10, #768]
	mov	r1, r9, lsr #6
	ldr	ip, [fp, #-48]
	add	r2, r4, r9, lsr #2
	add	r1, r3, r1, lsl #4
	ldr	lr, [r5, #12]
	ldr	r0, [r8, #12]
	add	r9, r9, #64
	mov	r1, r1, asl #6
	ldr	r3, [r7, #52]
	add	r0, r0, r2
	mov	r2, #16
	add	r1, ip, r1, lsr #2
	add	r1, lr, r1
	blx	r3
	cmp	r6, r9
	bhi	.L44
	b	.L43
.L63:
	.align	2
.L62:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	IMAGE_LinearTo2D, .-IMAGE_LinearTo2D
	.align	2
	.global	IMAGE_ConvertTo2D
	.type	IMAGE_ConvertTo2D, %function
IMAGE_ConvertTo2D:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #24]
	cmp	ip, #1
	beq	.L66
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	IMAGE_LinearTo2D
.L66:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	IMAGE_TileTo2D
	UNWIND(.fnend)
	.size	IMAGE_ConvertTo2D, .-IMAGE_ConvertTo2D
	.global	g_RowMapTable_UV_2b
	.global	g_RowMapTable_Y_2b
	.global	g_RowMapTable_UV
	.global	g_RowMapTable_Y
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	g_RowMapTable_Y_2b, %object
	.size	g_RowMapTable_Y_2b, 256
g_RowMapTable_Y_2b:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.type	g_RowMapTable_Y, %object
	.size	g_RowMapTable_Y, 512
g_RowMapTable_Y:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.type	g_RowMapTable_UV_2b, %object
	.size	g_RowMapTable_UV_2b, 32
g_RowMapTable_UV_2b:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.type	g_RowMapTable_UV, %object
	.size	g_RowMapTable_UV, 256
g_RowMapTable_UV:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
