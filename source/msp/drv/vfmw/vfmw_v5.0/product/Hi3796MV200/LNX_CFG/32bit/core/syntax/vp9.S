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
	.file	"vp9.c"
	.text
	.align	2
	.global	VP9_u_v_x
	.type	VP9_u_v_x, %function
VP9_u_v_x:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	VP9_u_v_x, .-VP9_u_v_x
	.align	2
	.global	VP9_s_v
	.type	VP9_s_v, %function
VP9_s_v:
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
	add	r1, r1, #1
	bl	BsGet
	tst	r0, #1
	mov	r0, r0, asr #1
	rsbne	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_s_v, .-VP9_s_v
	.align	2
	.global	Vp9_Cabac_ReadIsValid
	.type	Vp9_Cabac_ReadIsValid, %function
Vp9_Cabac_ReadIsValid:
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
	cmp	r2, #0
	cmpne	r0, #0
	moveq	r3, #1
	movne	r3, #0
	beq	.L7
	cmp	r1, #0
	ble	.L8
	add	r0, r0, r1
	cmp	r2, r0
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L7:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L8:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReadIsValid, .-Vp9_Cabac_ReadIsValid
	.align	2
	.global	Vp9_Cabac_ReaderFill
	.type	Vp9_Cabac_ReaderFill, %function
Vp9_Cabac_ReaderFill:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #32]
	mov	r7, r0
	ldr	r8, [r0, #28]
	rsb	r6, r5, #24
	rsb	r4, r5, #16
	bic	r6, r6, #7
	rsb	r4, r6, r4
	add	r5, r5, r6
	mov	r1, r6
	and	r4, r4, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r8, r0, asl r4
	str	r0, [r7, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReaderFill, .-Vp9_Cabac_ReaderFill
	.align	2
	.global	Vp9_Cabac_Read
	.type	Vp9_Cabac_Read, %function
Vp9_Cabac_Read:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0, #36]
	mov	r5, r0
	ldr	r7, [r0, #32]
	sub	r4, r4, #1
	cmp	r7, #0
	mul	r1, r4, r1
	mov	r4, r1, lsr #8
	add	r4, r4, #1
	blt	.L12
	ldr	r3, [r0, #28]
.L13:
	mov	r2, r4, asl #24
	cmp	r2, r3
	rsbls	r3, r2, r3
	ldr	r2, .L16
	ldrls	r1, [r5, #36]
	movls	r0, #1
	movhi	r0, #0
	rsbls	r4, r4, r1
	ldrb	r1, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r1
	rsb	r7, r1, r7
	mov	r4, r4, asl r1
	str	r3, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L12:
	rsb	r1, r7, #24
	rsb	r8, r7, #16
	bic	r1, r1, #7
	ldr	r6, [r0, #28]
	rsb	r8, r1, r8
	add	r7, r7, r1
	bl	BsGet
	and	r3, r8, #7
	orr	r3, r6, r0, asl r3
	b	.L13
.L17:
	.align	2
.L16:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_Read, .-Vp9_Cabac_Read
	.align	2
	.global	Vp9_Cabac_ReadLiteral
	.type	Vp9_Cabac_ReadLiteral, %function
Vp9_Cabac_ReadLiteral:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r7, r1, #1
	mov	r6, r0
	bmi	.L23
	ldr	r8, [r0, #28]
	mov	r9, #0
	ldr	r4, [r0, #36]
	mov	r3, #1
	ldr	r5, [r0, #32]
	ldr	r10, .L27
	b	.L22
.L20:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L19
.L22:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L20
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L20
.L23:
	mov	r9, #0
.L19:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L28:
	.align	2
.L27:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReadLiteral, .-Vp9_Cabac_ReadLiteral
	.align	2
	.global	Vp9_Cabac_ReaderInit
	.type	Vp9_Cabac_ReaderInit, %function
Vp9_Cabac_ReaderInit:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mvn	r2, #7
	mov	r3, #255
	mov	r5, #0
	str	r2, [r0, #32]
	str	r3, [r0, #36]
	mov	r1, #32
	str	r5, [r0, #28]
	mov	r4, r0
	bl	BsGet
	mov	r2, r0
	ldr	r0, [r4, #36]
	sub	r3, r0, #1
	ubfx	r3, r3, #1, #24
	add	r3, r3, #1
	mov	r1, r3, asl #24
	cmp	r2, r1
	rsbcs	r2, r1, r2
	ldr	r1, .L32
	rsbcs	r3, r3, r0
	movcc	r0, r5
	movcs	r0, #1
	ldrb	r1, [r1, r3]	@ zero_extendqisi2
	mov	r2, r2, asl r1
	mov	r3, r3, asl r1
	str	r2, [r4, #28]
	rsb	r1, r1, #24
	str	r3, [r4, #36]
	str	r1, [r4, #32]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L33:
	.align	2
.L32:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReaderInit, .-Vp9_Cabac_ReaderInit
	.align	2
	.global	Vp9_ReadTxMode
	.type	Vp9_ReadTxMode, %function
Vp9_ReadTxMode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r7, #1
	mov	r6, r0
	ldr	r10, .L48
	ldr	r4, [r0, #36]
	mov	r3, r7
	ldr	r5, [r0, #32]
	mov	r9, #0
	ldr	r8, [r0, #28]
	b	.L37
.L35:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L45
.L37:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L35
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L35
.L45:
	cmp	r9, #3
	beq	.L46
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L46:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	movge	r0, r8
	blt	.L47
.L39:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r9, #4
	rsbls	r4, r4, r2
	ldrb	r3, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	mov	r0, r9
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L47:
	rsb	r1, r5, #24
	rsb	r7, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r7, r1, r7
	add	r5, r1, r5
	bl	BsGet
	and	r7, r7, #7
	orr	r0, r8, r0, asl r7
	b	.L39
.L49:
	.align	2
.L48:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
	.align	2
	.global	Vp9_ReadTxProbs
	.type	Vp9_ReadTxProbs, %function
Vp9_ReadTxProbs:
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
	ldr	r6, .L399
	ldr	r4, [r1, #28]
	mov	r5, r1
	ldr	r10, [r1, #36]
	mov	r9, r0
	ldr	r8, [r1, #32]
	add	r2, r0, #2
	str	r0, [fp, #-52]
	str	r2, [fp, #-48]
	str	r0, [fp, #-56]
.L83:
	sub	r10, r10, #1
	cmp	r8, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L341
.L51:
	mov	r7, r10, asl #24
	cmp	r7, r4
	bhi	.L52
	ldr	r3, [r5, #36]
	rsb	r7, r7, r4
	rsb	r10, r10, r3
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r8, r3, r8
	sub	r4, r10, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl r3
	str	r10, [r5, #36]
	add	r4, r4, #1
	str	r8, [r5, #32]
	str	r7, [r5, #28]
	blt	.L342
.L53:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L54
	ldr	r2, [r5, #36]
	rsb	r3, r3, r7
	rsb	r4, r4, r2
	ldrb	r0, [r6, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r0
	rsb	r4, r0, r8
	sub	r7, r2, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r3, asl r0
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L343
.L56:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L61
	ldr	r1, [r5, #36]
	rsb	r3, r3, r8
	rsb	r7, r7, r1
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	rsb	r8, r0, r4
	mov	r1, r7, asl r0
	sub	r7, r1, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r4, r3, asl r0
	str	r1, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r4, [r5, #28]
	blt	.L344
.L63:
	mov	r3, r7, asl #24
	cmp	r3, r4
	bhi	.L67
	ldr	r1, [r5, #36]
	rsb	r3, r3, r4
	mov	r10, #0
	mov	r2, #6
	rsb	r7, r7, r1
	str	r9, [fp, #-68]
	mov	ip, #1
	mov	r9, r10
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r2
	str	r4, [r5, #36]
	mov	r10, r3
	b	.L68
.L72:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L345
.L68:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L72
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L72
.L52:
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r8, r3, r8
	mov	r10, r10, asl r3
	str	r4, [r5, #28]
	str	r8, [r5, #32]
	str	r10, [r5, #36]
.L239:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L83
	ldr	r3, [fp, #-52]
	add	r2, r3, #4
	str	r2, [fp, #-48]
	mov	r7, r3
.L144:
	sub	r10, r10, #1
	cmp	r8, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L346
.L84:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L85
	ldr	r3, [r5, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	rsb	r4, r3, r8
	mov	r10, r10, asl r3
	sub	r8, r10, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L347
.L86:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L87
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L348
.L89:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L94
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L349
.L96:
	mov	r3, r8, asl #24
	cmp	r3, r4
	bhi	.L100
	ldr	r1, [r5, #36]
	rsb	r2, r3, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L101
.L105:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L350
.L101:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L105
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L105
.L85:
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r8, r3, r8
	mov	r10, r10, asl r3
	str	r4, [r5, #28]
	str	r8, [r5, #32]
	str	r10, [r5, #36]
.L240:
	sub	r10, r10, #1
	cmp	r8, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L351
.L114:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L115
	ldr	r3, [r5, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	rsb	r4, r3, r8
	mov	r10, r10, asl r3
	sub	r8, r10, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L352
.L116:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L117
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L353
.L119:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L124
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L354
.L126:
	mov	r3, r8, asl #24
	cmp	r3, r4
	bhi	.L130
	ldr	r1, [r5, #36]
	rsb	r2, r3, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L131
.L135:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L355
.L131:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L135
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L135
.L115:
	ldrb	r3, [r6, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r8, r3, r8
	mov	r10, r10, asl r3
	str	r4, [r5, #28]
	str	r8, [r5, #32]
	str	r10, [r5, #36]
.L241:
	ldr	r3, [fp, #-48]
	add	r7, r7, #2
	cmp	r7, r3
	bne	.L144
	ldr	r3, [fp, #-52]
	ldr	r9, [fp, #-56]
	add	r7, r3, #6
	str	r7, [fp, #-48]
	mov	r7, r10
.L238:
	sub	r7, r7, #1
	cmp	r8, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L356
.L145:
	mov	r10, r7, asl #24
	cmp	r10, r4
	bhi	.L146
	ldr	r3, [r5, #36]
	rsb	r10, r10, r4
	rsb	r7, r7, r3
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r2
	rsb	r4, r2, r8
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r2
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L357
.L147:
	mov	r2, r7, asl #24
	cmp	r2, r10
	bhi	.L148
	ldr	ip, [r5, #36]
	rsb	r10, r2, r10
	rsb	r7, r7, ip
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	ip, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, ip, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r0
	str	ip, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L358
.L150:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L155
	ldr	r1, [r5, #36]
	rsb	r3, r3, r10
	rsb	r7, r7, r1
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	rsb	r10, r0, r4
	mov	r1, r7, asl r0
	sub	r7, r1, #1
	cmp	r10, #0
	ubfx	r7, r7, #1, #24
	mov	r4, r3, asl r0
	str	r1, [r5, #36]
	add	r7, r7, #1
	str	r10, [r5, #32]
	str	r4, [r5, #28]
	blt	.L359
.L157:
	mov	r3, r7, asl #24
	cmp	r3, r4
	bhi	.L161
	ldr	r1, [r5, #36]
	rsb	r3, r3, r4
	mov	r8, #0
	mov	r2, #6
	rsb	r7, r7, r1
	str	r9, [fp, #-60]
	mov	ip, #1
	mov	r9, r8
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r10, r4, r10
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r10, [r5, #32]
	mov	r7, r2
	str	r4, [r5, #36]
	mov	r8, r3
	b	.L162
.L166:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r8, [r5, #28]
	str	r10, [r5, #32]
	str	r4, [r5, #36]
	beq	.L360
.L162:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L166
	rsb	r1, r10, #24
	rsb	r2, r10, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r10, r1, r10
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L166
.L146:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r4, asl r3
	mov	r7, r7, asl r3
	rsb	r4, r3, r8
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L242:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L361
.L177:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L178
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r2
	rsb	r4, r2, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r2
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L362
.L179:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L180
	ldr	ip, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, ip
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	ip, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, ip, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	ip, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L363
.L182:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L187
	ldr	r1, [r5, #36]
	rsb	r3, r3, r8
	rsb	r7, r7, r1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	rsb	r8, r2, r4
	mov	r1, r7, asl r2
	sub	r7, r1, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r4, [r5, #28]
	blt	.L364
.L189:
	mov	r3, r7, asl #24
	cmp	r3, r4
	bhi	.L193
	ldr	r1, [r5, #36]
	rsb	r2, r3, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r7, r7, r1
	str	r9, [fp, #-60]
	mov	ip, #1
	mov	r9, r10
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r8, r4, r8
	str	r2, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L194
.L198:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L365
.L194:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L198
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L198
.L178:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L243:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L366
.L207:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L208
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r2
	rsb	r4, r2, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r2
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L367
.L209:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L210
	ldr	ip, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, ip
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	ip, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, ip, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	ip, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L368
.L212:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L217
	ldr	r1, [r5, #36]
	rsb	r3, r3, r8
	rsb	r7, r7, r1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	rsb	r8, r2, r4
	mov	r1, r7, asl r2
	sub	r7, r1, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r4, [r5, #28]
	blt	.L369
.L219:
	mov	r3, r7, asl #24
	cmp	r3, r4
	bhi	.L223
	ldr	r1, [r5, #36]
	rsb	r2, r3, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r7, r7, r1
	str	r9, [fp, #-60]
	mov	ip, #1
	mov	r9, r10
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r8, r4, r8
	str	r2, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L224
.L228:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L370
.L224:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L228
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L228
.L208:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L244:
	ldr	r3, [fp, #-48]
	add	r9, r9, #3
	cmp	r9, r3
	ldrne	r4, [r5, #28]
	ldrne	r7, [r5, #36]
	ldrne	r8, [r5, #32]
	bne	.L238
.L50:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L180:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	str	r8, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r8
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r8, r2
	b	.L185
.L183:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r8, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L371
.L185:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L183
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L183
.L148:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r10, r10, asl r1
	rsb	r4, r1, r4
	str	r10, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r8
	mov	ip, #1
	mov	r8, r10
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r10, r2
	b	.L153
.L151:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r10, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L372
.L153:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L151
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L151
.L117:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L122
.L120:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L373
.L122:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L120
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L120
.L87:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L92
.L90:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L374
.L92:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L90
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L90
.L400:
	.align	2
.L399:
	.word	.LANCHOR0
.L54:
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-68]
	mov	r7, r7, asl r1
	rsb	r8, r1, r8
	str	r7, [r5, #28]
	mov	r4, r4, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r7
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	mov	r7, r2
	b	.L59
.L57:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L375
.L59:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L57
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L57
.L210:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	str	r8, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r8
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r8, r2
	b	.L215
.L213:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r8, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L376
.L215:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L213
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L213
.L366:
	rsb	r3, r4, #24
	rsb	r8, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r8, r3, r8
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r8, r8, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r3, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r8
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L207
.L361:
	rsb	r3, r4, #24
	rsb	r8, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r8, r3, r8
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r8, r8, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r3, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r8
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L177
.L341:
	rsb	r3, r8, #24
	rsb	r7, r8, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r7, r3, r7
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r7, r7, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r8, r3, r8
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r7
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L51
.L351:
	rsb	r2, r8, #24
	rsb	r9, r8, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r9, r2, r9
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	add	r8, r2, r8
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L114
.L346:
	rsb	r3, r8, #24
	rsb	r9, r8, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r9, r3, r9
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r8, r3, r8
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L84
.L356:
	rsb	r3, r8, #24
	rsb	r10, r8, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r8, r3, r8
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r10
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L145
.L372:
	mov	r8, r9
	ldr	r9, [fp, #-60]
.L154:
	ldrb	r2, [r9, #6]	@ zero_extendqisi2
	add	r8, r6, r8
	sub	ip, r2, #1
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L171
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L172
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L172:
	add	r3, r3, #1
.L174:
	strb	r3, [r9, #6]
	ldr	r10, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L242
.L171:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L377
	rsb	r3, r3, #255
	b	.L174
.L371:
	mov	r10, r9
	ldr	r9, [fp, #-60]
.L186:
	ldrb	r2, [r9, #7]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L201
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L202
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L202:
	add	r3, r3, #1
.L204:
	strb	r3, [r9, #7]
	ldr	r10, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L243
.L201:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L378
	rsb	r3, r3, #255
	b	.L204
.L375:
	mov	r10, r9
	ldr	r9, [fp, #-68]
.L60:
	ldrb	r2, [r9]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L77
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L78
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L78:
	add	r3, r3, #1
.L80:
	add	r4, r5, #28
	strb	r3, [r9]
	ldmia	r4, {r4, r8, r10}
	b	.L239
.L77:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L379
	rsb	r3, r3, #255
	b	.L80
.L373:
	mov	r10, r7
	ldr	r7, [fp, #-68]
.L123:
	ldrb	r2, [r7, #3]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L138
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L139
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L139:
	add	r3, r3, #1
.L141:
	add	r4, r5, #28
	strb	r3, [r7, #3]
	ldmia	r4, {r4, r8, r10}
	b	.L241
.L138:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L380
	rsb	r3, r3, #255
	b	.L141
.L376:
	mov	r10, r9
	ldr	r9, [fp, #-60]
.L216:
	ldrb	r2, [r9, #8]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L231
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L232
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L232:
	add	r3, r3, #1
.L234:
	strb	r3, [r9, #8]
	b	.L244
.L231:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L381
	rsb	r3, r3, #255
	b	.L234
.L374:
	mov	r10, r7
	ldr	r7, [fp, #-68]
.L93:
	ldrb	r2, [r7, #2]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L108
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L109
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L109:
	add	r3, r3, #1
.L111:
	add	r4, r5, #28
	strb	r3, [r7, #2]
	ldmia	r4, {r4, r8, r10}
	b	.L240
.L108:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L382
	rsb	r3, r3, #255
	b	.L111
.L377:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L174
.L379:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L80
.L378:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L204
.L381:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L234
.L380:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L141
.L382:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L111
.L161:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #4
	str	r9, [fp, #-60]
	mov	r3, r4, asl r1
	mov	r7, r7, asl r1
	rsb	r10, r1, r10
	str	r7, [r5, #36]
	mov	r9, r8
	mov	r4, r7
	mov	ip, #1
	str	r3, [r5, #28]
	str	r10, [r5, #32]
	mov	r8, r3
	mov	r7, r2
	b	.L165
.L163:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r8, [r5, #28]
	str	r10, [r5, #32]
	str	r4, [r5, #36]
	beq	.L383
.L165:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L163
	rsb	r1, r10, #24
	rsb	r2, r10, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r10, r1, r10
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L163
.L193:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r9, [fp, #-60]
	mov	r3, r4, asl r1
	mov	r7, r7, asl r1
	rsb	r8, r1, r8
	str	r7, [r5, #36]
	mov	r9, r10
	mov	r4, r7
	mov	r2, #1
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	mov	r10, r3
	mov	r7, ip
	b	.L197
.L195:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r7
	cmp	r1, r0
	sub	r7, r7, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r9, r9, ip
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r8, r1, r8
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L384
.L197:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L195
	rsb	r1, r8, #24
	rsb	ip, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r8, r1, r8
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L195
.L130:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L134
.L132:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L385
.L134:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L132
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L132
.L67:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #4
	str	r9, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r7, r7, asl r1
	rsb	r8, r1, r8
	str	r7, [r5, #36]
	mov	r9, r10
	mov	r4, r7
	mov	ip, #1
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	mov	r10, r3
	mov	r7, r2
	b	.L71
.L69:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L386
.L71:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L69
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L69
.L100:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L104
.L102:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L387
.L104:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L102
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L102
.L223:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r9, [fp, #-60]
	mov	r3, r4, asl r1
	mov	r7, r7, asl r1
	rsb	r8, r1, r8
	str	r7, [r5, #36]
	mov	r9, r10
	mov	r4, r7
	mov	r2, #1
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	mov	r10, r3
	mov	r7, ip
	b	.L227
.L225:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r7
	cmp	r1, r0
	sub	r7, r7, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r9, r9, ip
	rsbls	r4, r4, lr
	cmn	r7, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r8, r1, r8
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L388
.L227:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L225
	rsb	r1, r8, #24
	rsb	ip, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r8, r1, r8
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L225
.L61:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-68]
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	str	r8, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r8
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r8, r2
	b	.L66
.L64:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r8, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L389
.L66:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L64
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L64
.L124:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L129
.L127:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L390
.L129:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L127
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L127
.L94:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L99
.L97:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L391
.L99:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L97
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L97
.L217:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	str	r8, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r8
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r8, r2
	b	.L222
.L220:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r8, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L392
.L222:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L220
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L220
.L155:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r10, r10, asl r1
	rsb	r4, r1, r4
	str	r10, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r8
	mov	ip, #1
	mov	r8, r10
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r10, r2
	b	.L160
.L158:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r10, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L393
.L160:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L158
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L158
.L187:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r9, [fp, #-60]
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	str	r8, [r5, #28]
	mov	r7, r7, asl r1
	mov	r9, r10
	mov	ip, #1
	mov	r10, r8
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	mov	r8, r2
	b	.L192
.L190:
	mov	r2, r7, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, lr
	cmn	r8, #1
	ldrb	r2, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L394
.L192:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L190
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L190
.L394:
	mov	r10, r9
	ldr	r9, [fp, #-60]
	add	r10, r10, #16
	b	.L186
.L390:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #16
	b	.L123
.L389:
	mov	r10, r9
	ldr	r9, [fp, #-68]
	add	r10, r10, #16
	b	.L60
.L391:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #16
	b	.L93
.L393:
	mov	r8, r9
	ldr	r9, [fp, #-60]
	add	r8, r8, #16
	b	.L154
.L392:
	mov	r10, r9
	ldr	r9, [fp, #-60]
	add	r10, r10, #16
	b	.L216
.L355:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	ble	.L137
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L137:
	add	r10, r10, #64
	b	.L123
.L350:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	ble	.L107
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L107:
	add	r10, r10, #64
	b	.L93
.L365:
	mov	r10, r9
	cmp	r10, #64
	ldr	r9, [fp, #-60]
	ble	.L200
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L200:
	add	r10, r10, #64
	b	.L186
.L360:
	mov	r3, r8
	mov	r8, r9
	cmp	r8, #64
	ldr	r9, [fp, #-60]
	bgt	.L395
.L168:
	add	r8, r8, #64
	b	.L154
.L370:
	mov	r10, r9
	cmp	r10, #64
	ldr	r9, [fp, #-60]
	ble	.L230
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L230:
	add	r10, r10, #64
	b	.L216
.L345:
	mov	r3, r10
	mov	r10, r9
	cmp	r10, #64
	ldr	r9, [fp, #-68]
	bgt	.L396
.L74:
	add	r10, r10, #64
	b	.L60
.L387:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #32
	b	.L93
.L386:
	mov	r10, r9
	ldr	r9, [fp, #-68]
	add	r10, r10, #32
	b	.L60
.L383:
	mov	r8, r9
	ldr	r9, [fp, #-60]
	add	r8, r8, #32
	b	.L154
.L384:
	mov	r10, r9
	ldr	r9, [fp, #-60]
	add	r10, r10, #32
	b	.L186
.L385:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #32
	b	.L123
.L388:
	mov	r10, r9
	ldr	r9, [fp, #-60]
	add	r10, r10, #32
	b	.L216
.L357:
	rsb	r3, r4, #24
	rsb	r8, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r8, r3, r8
	str	r3, [fp, #-52]
	mov	r1, r3
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L147
.L362:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L179
.L352:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L116
.L342:
	rsb	r3, r8, #24
	rsb	r10, r8, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r8, r8, r3
	str	r8, [r5, #32]
	orr	r0, r7, r0, asl r10
	str	r0, [r5, #28]
	mov	r7, r0
	b	.L53
.L347:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L86
.L367:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L209
.L396:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r3
	blt	.L397
.L75:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	b	.L74
.L395:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r8, r8, #65
	movge	r0, r3
	blt	.L398
.L169:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r8, r8, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r10, [r5, #32]
	str	r4, [r5, #36]
	b	.L168
.L359:
	rsb	r2, r10, #24
	rsb	r8, r10, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r8, r2, r8
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	add	r10, r10, r2
	str	r10, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L157
.L349:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L96
.L354:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L126
.L344:
	rsb	r2, r8, #24
	rsb	r10, r8, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r8, r8, r2
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L63
.L369:
	rsb	r2, r8, #24
	rsb	r10, r8, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r8, r8, r2
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L219
.L364:
	rsb	r2, r8, #24
	rsb	r10, r8, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r8, r8, r2
	str	r8, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L189
.L397:
	rsb	r1, r8, #24
	rsb	r7, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-60]
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L75
.L398:
	rsb	r1, r10, #24
	rsb	r7, r10, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-52]
	rsb	r7, r1, r7
	add	r10, r1, r10
	bl	BsGet
	ldr	r3, [fp, #-52]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L169
.L368:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L212
.L343:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L56
.L358:
	rsb	r2, r4, #24
	rsb	r8, r4, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r8, r2, r8
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	add	r4, r4, r2
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L150
.L353:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L119
.L363:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L182
.L348:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L89
	UNWIND(.fnend)
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
	.align	2
	.global	Vp9_ReaderHasError
	.type	Vp9_ReaderHasError, %function
Vp9_ReaderHasError:
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
	ldr	r0, [r0, #32]
	sub	r0, r0, #33
	cmn	r0, #-1073741790
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_ReaderHasError, .-Vp9_ReaderHasError
	.align	2
	.global	Vp9_DiffUpdateProb
	.type	Vp9_DiffUpdateProb, %function
Vp9_DiffUpdateProb:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r4, [r0, #36]
	ldr	r5, [r0, #32]
	mov	r6, r0
	sub	r4, r4, #1
	mov	r9, r1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	blt	.L403
	ldr	r8, [r0, #28]
.L404:
	mov	r3, r4, asl #24
	cmp	r3, r8
	bhi	.L405
	ldr	r2, [r6, #36]
	rsb	r8, r3, r8
	ldr	r3, .L458
	rsb	r4, r4, r2
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r1
	rsb	r4, r1, r5
	cmp	r4, #0
	sub	r5, r2, #1
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r1
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r8, [r6, #28]
	blt	.L452
.L407:
	mov	r1, r5, asl #24
	cmp	r1, r8
	bhi	.L412
	ldr	r2, [r6, #36]
	rsb	r8, r1, r8
	rsb	r5, r5, r2
	ldrb	ip, [r3, r5]	@ zero_extendqisi2
	mov	r2, r5, asl ip
	rsb	r5, ip, r4
	sub	r1, r2, #1
	cmp	r5, #0
	ubfx	r1, r1, #1, #24
	mov	r8, r8, asl ip
	str	r2, [r6, #36]
	add	r4, r1, #1
	str	r5, [r6, #32]
	str	r8, [r6, #28]
	blt	.L453
.L414:
	mov	r1, r4, asl #24
	cmp	r1, r8
	bhi	.L418
	ldr	r2, [r6, #36]
	rsb	r8, r1, r8
	mov	r7, #0
	mov	r10, #6
	rsb	r1, r4, r2
	mov	r2, #1
	ldrb	r4, [r3, r1]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r6, #28]
	mov	r4, r1, asl r4
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L419
.L423:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L454
.L419:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L423
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	str	ip, [fp, #-48]
	bl	BsGet
	ldr	ip, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	ip, ip, #7
	ldr	r2, [fp, #-56]
	orr	r0, r8, r0, asl ip
	b	.L423
.L412:
	ldrb	r1, [r3, r5]	@ zero_extendqisi2
	mov	r7, #0
	mov	r10, #3
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L417
.L415:
	mov	r1, r5, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r5, r5, lr
	cmn	r10, #1
	ldrb	r1, [r3, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L455
.L417:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L415
	rsb	r1, r4, #24
	rsb	ip, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r4, r1, r4
	str	ip, [fp, #-48]
	bl	BsGet
	ldr	ip, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	ip, ip, #7
	ldr	r2, [fp, #-56]
	orr	r0, r8, r0, asl ip
	b	.L415
.L405:
	ldr	r3, .L458
	mov	r7, #0
	mov	r10, #3
	mov	r2, #1
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L410
.L408:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L411
.L410:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L408
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	str	ip, [fp, #-48]
	bl	BsGet
	ldr	ip, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	ip, ip, #7
	ldr	r2, [fp, #-56]
	orr	r0, r8, r0, asl ip
	b	.L408
.L454:
	cmp	r7, #64
	ble	.L425
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl #1
	add	r4, r4, #1
	sub	r7, r7, #65
	movge	r0, r8
	blt	.L456
.L426:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r7, r7, r1
	rsbls	r4, r4, ip
	ldrb	r2, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
.L425:
	add	r7, r7, #64
.L411:
	ldrb	r2, [r9]	@ zero_extendqisi2
	add	r3, r3, r7
	sub	ip, r2, #1
	ldrb	r1, [r3, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L428
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L429
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L429:
	add	r3, r3, #1
	strb	r3, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L432
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L432:
	rsb	r3, r3, #255
	strb	r3, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L455:
	add	r7, r7, #16
	b	.L411
.L418:
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r7, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	str	r8, [r6, #28]
	mov	r1, r4, asl r1
	str	r5, [r6, #32]
	str	r1, [r6, #36]
	b	.L422
.L420:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	str	r8, [r6, #28]
	mov	r1, r4, asl r1
	str	r5, [r6, #32]
	str	r1, [r6, #36]
	beq	.L457
.L422:
	sub	r1, r1, #1
	cmp	r5, #0
	ubfx	r1, r1, #1, #24
	mov	r0, r8
	add	r4, r1, #1
	bge	.L420
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	str	ip, [fp, #-48]
	bl	BsGet
	ldr	ip, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	ip, ip, #7
	ldr	r2, [fp, #-56]
	orr	r0, r8, r0, asl ip
	b	.L420
.L457:
	add	r7, r7, #32
	b	.L411
.L403:
	rsb	r10, r5, #24
	ldr	r7, [r0, #28]
	bic	r10, r10, #7
	rsb	r8, r5, #16
	rsb	r8, r10, r8
	add	r5, r5, r10
	mov	r1, r10
	and	r8, r8, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r7, r0, asl r8
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L404
.L452:
	rsb	r10, r4, #24
	mov	r0, r6
	bic	r10, r10, #7
	str	r3, [fp, #-48]
	rsb	r7, r4, #16
	add	r4, r4, r10
	mov	r1, r10
	rsb	r7, r10, r7
	bl	BsGet
	and	r7, r7, #7
	str	r4, [r6, #32]
	ldr	r3, [fp, #-48]
	orr	r0, r8, r0, asl r7
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L407
.L453:
	rsb	r10, r5, #24
	mov	r0, r6
	bic	r10, r10, #7
	str	r3, [fp, #-48]
	rsb	r7, r5, #16
	add	r5, r5, r10
	mov	r1, r10
	rsb	r7, r10, r7
	bl	BsGet
	and	r7, r7, #7
	str	r5, [r6, #32]
	ldr	r3, [fp, #-48]
	orr	r0, r8, r0, asl r7
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L414
.L456:
	rsb	r1, r5, #24
	rsb	r10, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r3, [fp, #-48]
	rsb	r10, r1, r10
	add	r5, r1, r5
	bl	BsGet
	and	r10, r10, #7
	ldr	r3, [fp, #-48]
	orr	r0, r8, r0, asl r10
	b	.L426
.L459:
	.align	2
.L458:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
	.align	2
	.global	Vp9_ReadCoefProbsCommon
	.type	Vp9_ReadCoefProbsCommon, %function
Vp9_ReadCoefProbsCommon:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r4, [r1, #36]
	ldr	ip, [r1, #32]
	mov	r6, r1
	sub	r4, r4, #1
	mov	r7, r0
	cmp	ip, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	blt	.L461
	ldr	r3, [r1, #28]
.L462:
	mov	r1, r4, asl #24
	cmp	r1, r3
	bhi	.L463
	ldr	r2, [r6, #36]
	rsb	r3, r1, r3
	ldr	r5, .L655
	add	r1, r7, #512
	rsb	r4, r4, r2
	add	r2, r7, #1536
	add	r2, r2, #2
	str	r2, [fp, #-80]
	ldrb	r2, [r5, r4]	@ zero_extendqisi2
	mov	r10, r6
	add	r1, r1, #2
	str	r1, [fp, #-76]
	mov	r3, r3, asl r2
	rsb	r1, r2, ip
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r1, [r6, #32]
	str	r4, [r6, #36]
.L464:
	ldr	r3, [fp, #-76]
	mov	r6, r10
	sub	r3, r3, #512
	str	r3, [fp, #-72]
.L569:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-52]
.L567:
	ldr	r7, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-48]
.L565:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	bge	.L625
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L465
	ldr	r10, [r6, #28]
.L466:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L467
	ldr	r3, [r6, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	ldrb	r9, [r5, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r10, asl r9
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L626
.L468:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L469
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r5, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L627
.L471:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L476
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r8, r8, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L628
.L478:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L482
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r5, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L483
.L487:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L629
.L483:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L487
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L487
.L467:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L570:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L630
.L498:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L499
	ldr	r3, [r6, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	ldrb	r9, [r5, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r10, asl r9
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L631
.L500:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L501
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r5, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L632
.L503:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L508
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r8, r8, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L633
.L510:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L514
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r5, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L515
.L519:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L634
.L515:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L519
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L519
.L499:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L571:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L635
.L530:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L531
	ldr	r3, [r6, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	ldrb	r0, [r5, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L636
.L532:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L533
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r5, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L637
.L535:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L540
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r8, r8, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L638
.L542:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L546
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r5, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L547
.L551:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L639
.L547:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L551
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L551
.L531:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L572:
	ldr	r3, [fp, #-48]
	add	r7, r7, #4
	add	r3, r3, #1
	str	r3, [fp, #-48]
	b	.L565
.L635:
	rsb	r3, r4, #24
	rsb	r9, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-60]
	mov	r1, r3
	bl	BsGet
	and	r2, r9, #7
	ldr	r3, [fp, #-60]
	add	r4, r3, r4
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L530
.L630:
	rsb	r3, r4, #24
	rsb	r9, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-60]
	mov	r1, r3
	bl	BsGet
	and	r2, r9, #7
	ldr	r3, [fp, #-60]
	add	r4, r3, r4
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L498
.L465:
	rsb	r9, r4, #24
	rsb	r3, r4, #16
	bic	r9, r9, #7
	mov	r0, r6
	rsb	r3, r9, r3
	ldr	r10, [r6, #28]
	mov	r1, r9
	str	r3, [fp, #-60]
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r9
	str	r4, [r6, #32]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L466
.L533:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L538
.L536:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L640
.L538:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L536
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L536
.L501:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L506
.L504:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L641
.L506:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L504
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L504
.L469:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L474
.L472:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L642
.L474:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L472
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L472
.L642:
	mov	r10, r7
	ldr	r7, [fp, #-68]
.L475:
	ldrb	r2, [r7, #-2]	@ zero_extendqisi2
	add	r10, r5, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L492
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L493
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L493:
	add	r3, r3, #1
.L495:
	strb	r3, [r7, #-2]
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	ldr	r10, [r6, #28]
	b	.L570
.L492:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L496
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L496:
	rsb	r3, r3, #255
	b	.L495
.L641:
	mov	r10, r7
	ldr	r7, [fp, #-68]
.L507:
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	add	r10, r5, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L524
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L525
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L525:
	add	r3, r3, #1
.L527:
	strb	r3, [r7, #-1]
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	ldr	r10, [r6, #28]
	b	.L571
.L524:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L528
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L528:
	rsb	r3, r3, #255
	b	.L527
.L640:
	mov	r10, r7
	ldr	r7, [fp, #-68]
.L539:
	ldrb	r2, [r7]	@ zero_extendqisi2
	add	r10, r5, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L556
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L557
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L557:
	add	r3, r3, #1
.L559:
	strb	r3, [r7]
	b	.L572
.L556:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L560
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L560:
	rsb	r3, r3, #255
	b	.L559
.L625:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #6
	add	r2, r2, #32
	str	r2, [fp, #-56]
	bne	.L567
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-76]
	add	r3, r3, #256
	str	r3, [fp, #-72]
	cmp	r3, r2
	bne	.L569
	ldr	r3, [fp, #-76]
	mov	r10, r6
	ldr	r2, [fp, #-80]
	add	r3, r3, #512
	str	r3, [fp, #-76]
	cmp	r3, r2
	bne	.L464
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L508:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L513
.L511:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L643
.L513:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L511
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L511
.L476:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L481
.L479:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L644
.L481:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L479
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L479
.L540:
	ldrb	r3, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L545
.L543:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r5, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L645
.L545:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L543
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L543
.L645:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #16
	b	.L539
.L644:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #16
	b	.L475
.L643:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #16
	b	.L507
.L629:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L646
.L489:
	add	r10, r10, #64
	b	.L475
.L639:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L647
.L553:
	add	r10, r10, #64
	b	.L539
.L634:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L648
.L521:
	add	r10, r10, #64
	b	.L507
.L482:
	ldrb	r1, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L486
.L484:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L649
.L486:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L484
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L484
.L546:
	ldrb	r1, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L550
.L656:
	.align	2
.L655:
	.word	.LANCHOR0
.L548:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L650
.L550:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L548
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L548
.L514:
	ldrb	r1, [r5, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L518
.L516:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r5, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L651
.L518:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L516
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L516
.L651:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #32
	b	.L507
.L650:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #32
	b	.L539
.L649:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r10, r10, #32
	b	.L475
.L636:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L532
.L626:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L468
.L631:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L500
.L648:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L652
.L522:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r5, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L521
.L646:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L653
.L490:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r5, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L489
.L647:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L654
.L554:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r5, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L553
.L637:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L535
.L632:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L503
.L627:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L471
.L628:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L478
.L633:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L510
.L638:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L542
.L654:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L554
.L652:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L522
.L653:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L490
.L463:
	ldr	r2, .L655
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, ip
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L461:
	rsb	r8, ip, #24
	ldr	r10, [r1, #28]
	bic	r8, r8, #7
	mov	r0, r1
	rsb	r9, ip, #16
	str	ip, [fp, #-48]
	mov	r1, r8
	rsb	r9, r8, r9
	bl	BsGet
	ldr	ip, [fp, #-48]
	and	r3, r9, #7
	add	r5, ip, r8
	str	r5, [r6, #32]
	mov	ip, r5
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L462
	UNWIND(.fnend)
	.size	Vp9_ReadCoefProbsCommon, .-Vp9_ReadCoefProbsCommon
	.align	2
	.global	Vp9_ReadCoefProbs
	.type	Vp9_ReadCoefProbs, %function
Vp9_ReadCoefProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r1, r2
	mov	r5, r2
	mov	r6, r0
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #1024
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #1
	bls	.L659
	mov	r1, r5
	add	r0, r6, #2048
	bl	Vp9_ReadCoefProbsCommon
.L659:
	cmp	r4, #2
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #3072
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	Vp9_ReadCoefProbsCommon
	UNWIND(.fnend)
	.size	Vp9_ReadCoefProbs, .-Vp9_ReadCoefProbs
	.align	2
	.global	Vp9_ReadInterModeProbs
	.type	Vp9_ReadInterModeProbs, %function
Vp9_ReadInterModeProbs:
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
	add	r7, r0, #4416
	ldr	r6, .L847
	mov	r5, r1
	mov	r3, r7
	mov	r2, r7
	add	r7, r7, #25
	add	r3, r3, #24
	str	r3, [fp, #-48]
	add	r3, r2, #46
	str	r3, [fp, #-52]
.L760:
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L663
	ldr	r10, [r5, #28]
.L664:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L665
	ldr	r3, [r5, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	ldrb	r9, [r6, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r10, asl r9
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L818
.L666:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L667
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L819
.L669:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L674
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L820
.L676:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L680
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-64]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L681
.L685:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L821
.L681:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L685
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L685
.L665:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L761:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L822
.L696:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L697
	ldr	r3, [r5, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	ldrb	r9, [r6, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r10, asl r9
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L823
.L698:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L699
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L824
.L701:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L706
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L825
.L708:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L712
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-64]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L713
.L717:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L826
.L713:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L717
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L717
.L697:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L762:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L827
.L728:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L729
	ldr	r3, [r5, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L828
.L730:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L731
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L829
.L733:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L738
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L830
.L740:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L744
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-64]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L745
.L749:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L831
.L745:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L749
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L749
.L729:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L763:
	ldr	r3, [fp, #-48]
	add	r7, r7, #3
	add	r3, r3, #3
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	cmp	r7, r3
	bne	.L760
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L827:
	rsb	r3, r4, #24
	rsb	r9, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r9, r3, r9
	str	r3, [fp, #-56]
	mov	r1, r3
	bl	BsGet
	and	r2, r9, #7
	ldr	r3, [fp, #-56]
	add	r4, r3, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L728
.L822:
	rsb	r3, r4, #24
	rsb	r9, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r9, r3, r9
	str	r3, [fp, #-56]
	mov	r1, r3
	bl	BsGet
	and	r2, r9, #7
	ldr	r3, [fp, #-56]
	add	r4, r3, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L696
.L663:
	rsb	r9, r4, #24
	rsb	r3, r4, #16
	bic	r9, r9, #7
	mov	r0, r5
	rsb	r3, r9, r3
	ldr	r10, [r5, #28]
	mov	r1, r9
	str	r3, [fp, #-56]
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r9
	str	r4, [r5, #32]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L664
.L667:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L672
.L670:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L832
.L672:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L670
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L670
.L731:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L736
.L734:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L833
.L736:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L734
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L734
.L699:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L704
.L702:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L834
.L704:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L702
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L702
.L834:
	mov	r10, r7
	ldr	r7, [fp, #-64]
.L705:
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L722
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L723
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L723:
	add	r3, r3, #1
.L725:
	strb	r3, [r7, #-1]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L762
.L722:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L726
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L726:
	rsb	r3, r3, #255
	b	.L725
.L833:
	mov	r10, r7
	ldr	r7, [fp, #-64]
.L737:
	ldr	r3, [fp, #-48]
	add	r10, r6, r10
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L754
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L755
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L755:
	add	r3, r3, #1
.L757:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1]
	b	.L763
.L754:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L758
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L758:
	rsb	r3, r3, #255
	b	.L757
.L832:
	mov	r10, r7
	ldr	r7, [fp, #-64]
.L673:
	ldrb	r2, [r7, #-2]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L690
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L691
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L691:
	add	r3, r3, #1
.L693:
	strb	r3, [r7, #-2]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L761
.L690:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L694
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L694:
	rsb	r3, r3, #255
	b	.L693
.L680:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-64]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	mov	r7, r10
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r8, ip
	mov	r10, r3
	b	.L684
.L682:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L835
.L684:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L682
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L682
.L744:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-64]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L748
.L746:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L836
.L748:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L746
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L746
.L712:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-64]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L716
.L714:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L837
.L716:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L714
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L714
.L738:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L743
.L741:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L838
.L743:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L741
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L741
.L706:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L711
.L709:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L839
.L711:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L709
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L709
.L674:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L679
.L848:
	.align	2
.L847:
	.word	.LANCHOR0
.L677:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L840
.L679:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L677
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L677
.L840:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #16
	b	.L673
.L839:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #16
	b	.L705
.L838:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #16
	b	.L737
.L831:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-64]
	bgt	.L841
.L751:
	add	r10, r10, #64
	b	.L737
.L821:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-64]
	bgt	.L842
.L687:
	add	r10, r10, #64
	b	.L673
.L826:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-64]
	bgt	.L843
.L719:
	add	r10, r10, #64
	b	.L705
.L837:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #32
	b	.L705
.L836:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #32
	b	.L737
.L835:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #32
	b	.L673
.L823:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L698
.L828:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L730
.L818:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L666
.L841:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L844
.L752:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L751
.L843:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L845
.L720:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L719
.L842:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L846
.L688:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L687
.L824:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L701
.L819:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L669
.L829:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L733
.L830:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L740
.L825:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L708
.L820:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L676
.L844:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L752
.L846:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L688
.L845:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L720
	UNWIND(.fnend)
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	2
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
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
	add	r7, r0, #4416
	ldr	r6, .L974
	mov	r5, r1
	mov	r3, r7
	mov	r2, r7
	add	r7, r7, #45
	add	r3, r3, #44
	str	r3, [fp, #-48]
	add	r3, r2, #53
	str	r3, [fp, #-52]
.L915:
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L850
	ldr	r0, [r5, #28]
.L851:
	mov	r9, r8, asl #24
	cmp	r9, r0
	bhi	.L852
	ldr	r3, [r5, #36]
	rsb	r0, r9, r0
	rsb	r8, r8, r3
	ldrb	r9, [r6, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r0, asl r9
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L955
.L853:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L854
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L956
.L856:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L861
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L957
.L863:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L867
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-64]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L868
.L872:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L958
.L868:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L872
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L872
.L852:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L916:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L959
.L883:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L884
	ldr	r3, [r5, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r3, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L960
.L885:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L886
	ldr	r2, [r5, #36]
	rsb	r9, r3, r9
	rsb	r8, r8, r2
	ldrb	r0, [r6, r8]	@ zero_extendqisi2
	mov	r2, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, r2, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L961
.L888:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L893
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r8, asl r2
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L962
.L895:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L899
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-64]
	mov	ip, #1
	mov	r7, r10
	ldrb	r4, [r6, r8]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L900
.L904:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L963
.L900:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L904
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L904
.L884:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L917:
	ldr	r3, [fp, #-48]
	add	r7, r7, #2
	add	r3, r3, #2
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	cmp	r7, r3
	bne	.L915
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L959:
	rsb	r3, r4, #24
	rsb	r9, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r9, r3, r9
	str	r3, [fp, #-56]
	mov	r1, r3
	bl	BsGet
	and	r2, r9, #7
	ldr	r3, [fp, #-56]
	add	r4, r3, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L883
.L850:
	rsb	r9, r4, #24
	rsb	r3, r4, #16
	bic	r9, r9, #7
	mov	r0, r5
	rsb	r3, r9, r3
	ldr	r10, [r5, #28]
	mov	r1, r9
	str	r3, [fp, #-56]
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r9
	str	r4, [r5, #32]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	b	.L851
.L861:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L866
.L864:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L964
.L866:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L864
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L864
.L893:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L898
.L896:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L965
.L898:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L896
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L896
.L854:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L859
.L857:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L966
.L859:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L857
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L857
.L886:
	ldrb	r3, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-64]
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r3
	mov	r7, r10
	mov	ip, #1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L891
.L889:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r5, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r9, #1
	ldrb	r2, [r6, r8]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L967
.L891:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L889
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L889
.L967:
	mov	r10, r7
	ldr	r7, [fp, #-64]
.L892:
	ldr	r3, [fp, #-48]
	add	r10, r6, r10
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L909
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L910
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L910:
	add	r3, r3, #1
.L912:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1]
	b	.L917
.L909:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L913
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L913:
	rsb	r3, r3, #255
	b	.L912
.L966:
	mov	r10, r7
	ldr	r7, [fp, #-64]
.L860:
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L877
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L878
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L878:
	add	r3, r3, #1
.L880:
	strb	r3, [r7, #-1]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L916
.L877:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L881
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L881:
	rsb	r3, r3, #255
	b	.L880
.L965:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #16
	b	.L892
.L964:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #16
	b	.L860
.L958:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-64]
	bgt	.L968
	add	r10, r10, #64
	b	.L860
.L963:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-64]
	addle	r10, r10, #64
	ble	.L892
.L969:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L970
.L907:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	add	r10, r10, #64
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L892
.L968:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L971
.L875:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	add	r10, r10, #64
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L860
.L867:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-64]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L871
.L869:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L972
.L871:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L869
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L869
.L899:
	ldrb	r1, [r6, r8]	@ zero_extendqisi2
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-64]
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r7, r10
	mov	r4, r8
	mov	r2, #1
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L903
.L901:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r8
	cmp	r1, r0
	sub	r8, r8, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r5, #36]
	movhi	ip, #0
	orr	r7, r7, ip
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r1, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L973
.L903:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L901
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L901
.L972:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #32
	b	.L860
.L973:
	mov	r10, r7
	ldr	r7, [fp, #-64]
	add	r10, r10, #32
	b	.L892
.L960:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L885
.L955:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L853
.L956:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L856
.L961:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r5
	rsb	r10, r3, r10
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r4, r4, r3
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L888
.L957:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L863
.L962:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L895
.L970:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L907
.L971:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L875
.L975:
	.align	2
.L974:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadSwitchableInterpProbs, .-Vp9_ReadSwitchableInterpProbs
	.align	2
	.global	Vp9_ReadCompPred
	.type	Vp9_ReadCompPred, %function
Vp9_ReadCompPred:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	cmp	r2, #0
	str	r0, [fp, #-56]
	mov	r6, r1
	str	r3, [fp, #-60]
	bne	.L1194
	add	r4, r1, #28
	ldr	r7, .L1234
	str	r2, [fp, #-52]
	ldmia	r4, {r4, r5, r9}
.L1017:
	mov	r10, r9
	ldr	r3, [fp, #-56]
	add	r8, r3, #4416
	mov	r3, r8
	add	r8, r8, #14
	add	r3, r3, #24
	str	r3, [fp, #-48]
.L1082:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1195
.L1019:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L1020
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	rsb	r4, r3, r5
	mov	r10, r10, asl r3
	sub	r5, r10, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1196
.L1021:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1022
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r0
	rsb	r4, r0, r4
	sub	r5, r2, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1197
.L1024:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1029
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	rsb	r9, r0, r4
	mov	r1, r5, asl r0
	sub	r5, r1, #1
	cmp	r9, #0
	ubfx	r5, r5, #1, #24
	mov	r4, r3, asl r0
	str	r1, [r6, #36]
	add	r5, r5, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1198
.L1031:
	mov	r3, r5, asl #24
	cmp	r3, r4
	bhi	.L1035
	ldr	r1, [r6, #36]
	rsb	r3, r3, r4
	mov	r2, #6
	str	r8, [fp, #-72]
	rsb	r5, r5, r1
	mov	r8, r7
	mov	r10, #0
	mov	ip, #1
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r9, r4, r9
	str	r3, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	mov	r7, r3
	b	.L1036
.L1040:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1199
.L1036:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1040
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1040
.L1020:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r9, r4, asl r3
	mov	r10, r10, asl r3
	rsb	r4, r3, r5
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L1117:
	sub	r10, r10, #1
	cmp	r4, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1200
.L1051:
	mov	r0, r10, asl #24
	cmp	r0, r9
	bhi	.L1052
	ldr	r3, [r6, #36]
	rsb	r9, r0, r9
	rsb	r10, r10, r3
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	sub	r5, r10, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1201
.L1053:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1054
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r0
	rsb	r4, r0, r4
	sub	r5, r2, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1202
.L1056:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1061
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	ldrb	r2, [r7, r5]	@ zero_extendqisi2
	rsb	r9, r2, r4
	mov	r1, r5, asl r2
	sub	r5, r1, #1
	cmp	r9, #0
	ubfx	r5, r5, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r5, r5, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1203
.L1063:
	mov	r3, r5, asl #24
	cmp	r3, r4
	bhi	.L1067
	ldr	r1, [r6, #36]
	rsb	r2, r3, r4
	mov	r3, #6
	str	r8, [fp, #-72]
	rsb	r5, r5, r1
	mov	r8, r7
	mov	r10, #0
	mov	ip, #1
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r7, r2
	b	.L1068
.L1072:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1204
.L1068:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1072
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1072
.L1052:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	mov	r10, r10, asl r3
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L1118:
	ldr	r3, [fp, #-48]
	add	r8, r8, #2
	cmp	r8, r3
	addne	r4, r6, #28
	ldmneia	r4, {r4, r5, r10}
	bne	.L1082
.L1081:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	bne	.L1205
.L1113:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-52]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1205:
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r9}
.L1018:
	mov	r10, r9
	ldr	r3, [fp, #-56]
	add	r8, r3, #4416
	mov	r3, r8
	add	r8, r8, #8
	add	r3, r3, #13
	str	r3, [fp, #-48]
.L1114:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1206
.L1083:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L1084
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r5, r3, r5
	sub	r4, r10, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1207
.L1085:
	mov	r3, r4, asl #24
	cmp	r3, r9
	bhi	.L1086
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r4, r4, r2
	ldrb	r0, [r7, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r0
	rsb	r4, r0, r5
	cmp	r4, #0
	sub	r5, r2, #1
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1208
.L1088:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1093
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	mov	r1, r5, asl r0
	rsb	r5, r0, r4
	sub	r9, r1, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r4, r3, asl r0
	str	r1, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1209
.L1095:
	mov	r3, r9, asl #24
	cmp	r3, r4
	bhi	.L1099
	ldr	r1, [r6, #36]
	rsb	r0, r3, r4
	mov	r2, #6
	mov	r3, #0
	rsb	r4, r9, r1
	str	r8, [fp, #-68]
	mov	ip, #1
	mov	r8, r7
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r7, r3
	rsb	r10, r1, r5
	mov	r9, r0, asl r1
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	b	.L1100
.L1104:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1210
.L1100:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L1104
	rsb	r1, r10, #24
	rsb	r2, r10, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-56]
	add	r10, r1, r10
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r9, r0, asl r2
	b	.L1104
.L1061:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1066
.L1064:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1211
.L1066:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1064
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1064
.L1029:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1034
.L1032:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1212
.L1034:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1032
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1032
.L1084:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r10, [r6, #36]
.L1119:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r3
	beq	.L1113
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r10}
	b	.L1114
.L1200:
	rsb	r3, r4, #24
	rsb	r5, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r5, r3, r5
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r5, r5, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r3, r4
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r5
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1051
.L1195:
	rsb	r3, r5, #24
	rsb	r9, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r5, r3, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1019
.L1054:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1059
.L1057:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1213
.L1059:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1057
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1057
.L1022:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1027
.L1025:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1214
.L1027:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1025
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1025
.L1206:
	rsb	r3, r5, #24
	rsb	r9, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-56]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r5, r3, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1083
.L1214:
	mov	r7, r8
	ldr	r8, [fp, #-72]
.L1028:
	ldrb	r2, [r8, #-1]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1045
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1046
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1046:
	add	r3, r3, #1
.L1048:
	strb	r3, [r8, #-1]
	ldr	r9, [r6, #28]
	ldr	r10, [r6, #36]
	ldr	r4, [r6, #32]
	b	.L1117
.L1045:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1049
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1049:
	rsb	r3, r3, #255
	b	.L1048
.L1213:
	mov	r7, r8
	ldr	r8, [fp, #-72]
.L1060:
	ldrb	r2, [r8]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1075
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1076
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1076:
	add	r3, r3, #1
.L1078:
	strb	r3, [r8]
	b	.L1118
.L1075:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1079
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1079:
	rsb	r3, r3, #255
	b	.L1078
.L1086:
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-68]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L1091
.L1089:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1215
.L1091:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1089
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1089
.L1215:
	mov	r7, r8
	ldr	r8, [fp, #-68]
.L1092:
	ldrb	r2, [r8]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1107
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1108
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1108:
	add	r3, r3, #1
.L1110:
	strb	r3, [r8]
	b	.L1119
.L1107:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1111
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1111:
	rsb	r3, r3, #255
	b	.L1110
.L1194:
	ldr	r9, [r1, #36]
	ldr	r5, [r1, #32]
	sub	r9, r9, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	add	r8, r9, #1
	blt	.L978
	ldr	r0, [r1, #28]
.L979:
	mov	r4, r8, asl #24
	cmp	r4, r0
	bhi	.L980
	ldr	r9, [r6, #36]
	rsb	r0, r4, r0
	ldr	r7, .L1234
	rsb	r9, r8, r9
	ldrb	r2, [r7, r9]	@ zero_extendqisi2
	mov	r3, r9, asl r2
	rsb	r5, r2, r5
	mov	r4, r0, asl r2
	sub	r9, r3, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	str	r3, [r6, #36]
	add	r8, r9, #1
	str	r5, [r6, #32]
	movge	r0, r4
	str	r4, [r6, #28]
	blt	.L1216
.L981:
	mov	r3, r8, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r3, r2, #1
	rsbls	r8, r8, r1
	cmp	r3, #2
	str	r3, [fp, #-52]
	ldrb	r9, [r7, r8]	@ zero_extendqisi2
	mov	r4, r0, asl r9
	rsb	r5, r9, r5
	str	r4, [r6, #28]
	mov	r9, r8, asl r9
	str	r5, [r6, #32]
	str	r9, [r6, #36]
	bne	.L983
	ldr	r3, [fp, #-56]
	add	r8, r3, #4416
	mov	r3, r8
	add	r8, r8, #3
	add	r3, r3, #8
	str	r3, [fp, #-48]
.L1016:
	sub	r10, r9, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1217
.L984:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L985
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r5, r3, r5
	sub	r4, r10, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl r3
	str	r10, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1218
.L986:
	mov	r3, r4, asl #24
	cmp	r3, r9
	bhi	.L987
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r4, r4, r2
	ldrb	r0, [r7, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r0
	rsb	r4, r0, r5
	cmp	r4, #0
	sub	r5, r2, #1
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1219
.L989:
	mov	r10, r5, asl #24
	cmp	r10, r9
	bhi	.L994
	ldr	r2, [r6, #36]
	rsb	r10, r10, r9
	rsb	r5, r5, r2
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r5, r5, asl r3
	rsb	r4, r3, r4
	sub	r9, r5, #1
	cmp	r4, #0
	ubfx	r9, r9, #1, #24
	mov	r10, r10, asl r3
	str	r5, [r6, #36]
	add	r9, r9, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1220
.L996:
	mov	r3, r9, asl #24
	cmp	r3, r10
	bhi	.L1000
	ldr	r1, [r6, #36]
	rsb	r3, r3, r10
	mov	r2, #6
	str	r8, [fp, #-72]
	rsb	r9, r9, r1
	mov	r8, r7
	mov	r10, #0
	mov	ip, #1
	ldrb	r1, [r7, r9]	@ zero_extendqisi2
	mov	r3, r3, asl r1
	rsb	r5, r1, r4
	str	r3, [r6, #28]
	mov	r4, r9, asl r1
	str	r5, [r6, #32]
	mov	r9, r2
	str	r4, [r6, #36]
	mov	r7, r3
	b	.L1001
.L1005:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1221
.L1001:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1005
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1005
.L1211:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-72]
	b	.L1060
.L1212:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-72]
	b	.L1028
.L1204:
	cmp	r10, #64
	mov	r7, r8
	ldr	r8, [fp, #-72]
	bgt	.L1222
.L1074:
	add	r10, r10, #64
	b	.L1060
.L1235:
	.align	2
.L1234:
	.word	.LANCHOR0
.L1199:
	cmp	r10, #64
	mov	r3, r7
	mov	r7, r8
	ldr	r8, [fp, #-72]
	bgt	.L1223
.L1042:
	add	r10, r10, #64
	b	.L1028
.L1093:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-68]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1098
.L1096:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1224
.L1098:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1096
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1096
.L980:
	ldr	r7, .L1234
	mov	r3, #0
	str	r3, [fp, #-52]
	ldrb	r9, [r7, r8]	@ zero_extendqisi2
	mov	r4, r0, asl r9
	rsb	r5, r9, r5
	str	r4, [r6, #28]
	mov	r9, r8, asl r9
	str	r5, [r6, #32]
	str	r9, [r6, #36]
	b	.L1017
.L1222:
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
	b	.L1074
.L1223:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r3
	blt	.L1225
.L1043:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L1042
.L985:
	ldrb	r9, [r7, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r9
	rsb	r5, r9, r5
	str	r4, [r6, #28]
	mov	r9, r10, asl r9
	str	r5, [r6, #32]
	str	r9, [r6, #36]
.L1116:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r3
	bne	.L1016
	b	.L1017
.L1224:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-68]
	b	.L1092
.L1217:
	rsb	r3, r5, #24
	rsb	r9, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r5, r3, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L984
.L1210:
	mov	r3, r7
	cmp	r3, #64
	mov	r7, r8
	ldr	r8, [fp, #-68]
	movle	r10, r3
	ble	.L1106
	mov	r1, #128
	mov	r0, r6
	str	r3, [fp, #-56]
	bl	Vp9_Cabac_Read
	ldr	r3, [fp, #-56]
	add	r0, r0, r3, lsl #1
	sub	r10, r0, #65
.L1106:
	add	r10, r10, #64
	b	.L1092
.L987:
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L992
.L990:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1226
.L992:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L990
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L990
.L1035:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #4
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	mov	r8, r7
	mov	ip, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, r2
	mov	r7, r3
	b	.L1039
.L1037:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1227
.L1039:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1037
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1037
.L1067:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	ip, #4
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	mov	r8, r7
	mov	r2, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, ip
	mov	r7, r3
	b	.L1071
.L1069:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r5
	cmp	r1, r0
	sub	r5, r5, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r10, r10, ip
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r1, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1228
.L1071:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1069
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-68]
	str	ip, [fp, #-64]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	ip, ip, #7
	orr	r0, r7, r0, asl ip
	b	.L1069
.L1226:
	mov	r7, r8
	ldr	r8, [fp, #-72]
.L993:
	ldrb	r3, [r8]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	r0, r3, #1
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	mov	r2, r0, asl #1
	cmp	r2, #255
	bgt	.L1010
	add	r3, r1, #1
	cmp	r3, r2
	bgt	.L1011
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r0, r3, asr #1
	addeq	r3, r0, r3, asr #1
.L1011:
	add	r3, r3, #1
.L1013:
	add	r4, r6, #28
	strb	r3, [r8]
	ldmia	r4, {r4, r5, r9}
	b	.L1116
.L1010:
	rsb	r2, r3, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1014
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1014:
	rsb	r3, r3, #255
	b	.L1013
.L1228:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-72]
	b	.L1060
.L1227:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-72]
	b	.L1028
.L1201:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1053
.L1196:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1021
.L1099:
	ldrb	r1, [r7, r9]	@ zero_extendqisi2
	mov	r2, #4
	str	r8, [fp, #-68]
	mov	r10, #0
	mov	r3, r4, asl r1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #36]
	mov	r4, r9
	mov	r8, r7
	mov	ip, #1
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	mov	r9, r2
	mov	r7, r3
	b	.L1103
.L1101:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1229
.L1103:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1101
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L1101
.L1229:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-68]
	b	.L1092
.L1207:
	rsb	r2, r5, #24
	rsb	r10, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r5, r5, r2
	str	r5, [r6, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1085
.L994:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L999
.L997:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r8, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1230
.L999:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L997
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r7, r0, asl r2
	b	.L997
.L1230:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-72]
	b	.L993
.L1197:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1024
.L1202:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1056
.L1221:
	cmp	r10, #64
	mov	r3, r7
	mov	r7, r8
	ldr	r8, [fp, #-72]
	bgt	.L1231
.L1007:
	add	r10, r10, #64
	b	.L993
.L1208:
	rsb	r2, r4, #24
	rsb	r10, r4, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-56]
	add	r4, r4, r2
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1088
.L1000:
	ldrb	r1, [r7, r9]	@ zero_extendqisi2
	mov	r5, #0
	mov	r2, #4
	str	r8, [fp, #-72]
	mov	r10, r10, asl r1
	rsb	r3, r1, r4
	str	r10, [r6, #28]
	mov	r4, r9, asl r1
	mov	r8, r7
	mov	ip, #1
	mov	r7, r5
	str	r3, [r6, #32]
	mov	r5, r10
	str	r4, [r6, #36]
	mov	r9, r3
	mov	r10, r2
	b	.L1004
.L1002:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r5, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1232
.L1004:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L1002
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-68]
	str	r2, [fp, #-64]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r5, r0, asl r2
	b	.L1002
.L1232:
	mov	r5, r7
	mov	r7, r8
	add	r10, r5, #32
	ldr	r8, [fp, #-72]
	b	.L993
.L1218:
	rsb	r3, r5, #24
	rsb	r10, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r5, r5, r3
	str	r5, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L986
.L1203:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-64]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-64]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1063
.L1198:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-64]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-64]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1031
.L1231:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r9, r10, #65
	movge	r0, r3
	blt	.L1233
.L1008:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r1, [r6, #36]
	movls	r10, #1
	movhi	r10, #0
	add	r10, r9, r10
	rsbls	r4, r4, r1
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r2, r0, asl r1
	rsb	r3, r1, r5
	mov	r4, r4, asl r1
	str	r2, [r6, #28]
	str	r3, [r6, #32]
	str	r4, [r6, #36]
	b	.L1007
.L1209:
	rsb	r2, r5, #24
	rsb	r10, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-56]
	mov	r1, r2
	bl	BsGet
	ldr	r2, [fp, #-56]
	and	r3, r10, #7
	add	r10, r5, r2
	str	r10, [r6, #32]
	mov	r5, r10
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1095
.L978:
	rsb	r7, r5, #24
	ldr	r4, [r1, #28]
	bic	r7, r7, #7
	mov	r0, r1
	rsb	r9, r5, #16
	add	r5, r5, r7
	mov	r1, r7
	rsb	r9, r7, r9
	bl	BsGet
	and	r9, r9, #7
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	b	.L979
.L1219:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-64]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L989
.L1220:
	rsb	r2, r4, #24
	rsb	r5, r4, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r5, r2, r5
	str	r2, [fp, #-64]
	mov	r1, r2
	bl	BsGet
	and	r3, r5, #7
	ldr	r2, [fp, #-64]
	add	r4, r4, r2
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L996
.L1216:
	rsb	r1, r5, #24
	rsb	r9, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r9, r1, r9
	add	r5, r5, r1
	bl	BsGet
	and	r9, r9, #7
	orr	r0, r4, r0, asl r9
	b	.L981
.L1225:
	rsb	r1, r9, #24
	rsb	r5, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r3, [fp, #-64]
	rsb	r5, r1, r5
	add	r9, r1, r9
	bl	BsGet
	ldr	r3, [fp, #-64]
	and	r5, r5, #7
	orr	r0, r3, r0, asl r5
	b	.L1043
.L983:
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	beq	.L1018
	b	.L1017
.L1233:
	rsb	r1, r5, #24
	rsb	r10, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r3, [fp, #-64]
	rsb	r10, r1, r10
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-64]
	and	r10, r10, #7
	orr	r0, r3, r0, asl r10
	b	.L1008
	UNWIND(.fnend)
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	2
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
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
	ldr	r9, .L1358
	ldr	r4, [r0, #36]
	add	ip, r1, #2
	ldr	r5, [r0, #32]
	mov	r7, r0
	ldr	r6, [r0, #28]
	add	r3, r1, #5
	str	r1, [fp, #-84]
	str	r3, [fp, #-48]
	str	r2, [fp, #-88]
.L1242:
	sub	r1, r4, #1
	cmp	r5, #0
	mov	r4, r1, asl #8
	sub	r1, r4, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1341
.L1237:
	mov	r8, r4, asl #24
	cmp	r8, r6
	bhi	.L1238
	ldr	r2, [r7, #36]
	rsb	r8, r8, r6
	mov	r3, #0
	mov	r10, #6
	rsb	r1, r4, r2
	mov	r6, r3
	mov	r2, #1
	str	ip, [fp, #-60]
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r1, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1241
.L1239:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r7, #36]
	movhi	ip, #0
	orr	r6, r6, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1342
.L1241:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1239
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r8, r0, asl ip
	b	.L1239
.L1238:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1295:
	ldr	r3, [fp, #-48]
	add	ip, ip, #1
	cmp	ip, r3
	bne	.L1242
	ldr	r3, [fp, #-84]
	add	r2, r3, #37
	str	r2, [fp, #-48]
	add	r2, r3, #25
	add	r3, r3, #57
	str	r2, [fp, #-68]
	str	r3, [fp, #-72]
.L1265:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1343
.L1243:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1244
	ldr	r2, [r7, #36]
	rsb	r6, r3, r6
	mov	r3, #0
	mov	r10, #6
	rsb	r4, r4, r2
	mov	r2, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r8, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	mov	r6, r3
	str	r4, [r7, #36]
	b	.L1247
.L1245:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1344
.L1247:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1245
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1245
.L1342:
	ldr	ip, [fp, #-60]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [ip]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1295
.L1244:
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1296:
	ldr	r3, [fp, #-48]
	sub	ip, r3, #32
	sub	r3, r3, #22
	str	r3, [fp, #-52]
.L1253:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1345
.L1248:
	mov	r8, r4, asl #24
	cmp	r8, r6
	bhi	.L1249
	ldr	r2, [r7, #36]
	rsb	r8, r8, r6
	mov	r3, #0
	mov	r10, #6
	rsb	r1, r4, r2
	str	ip, [fp, #-64]
	mov	r2, #1
	mov	r6, r3
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r1, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1252
.L1250:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r7, #36]
	movhi	ip, #0
	orr	r6, r6, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1346
.L1252:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1250
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	ip, r1, ip
	str	r2, [fp, #-60]
	str	ip, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r8, r0, asl ip
	b	.L1250
.L1249:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1297:
	ldr	r3, [fp, #-52]
	add	ip, ip, #1
	cmp	ip, r3
	bne	.L1253
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1347
.L1254:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1255
	ldr	r2, [r7, #36]
	rsb	r6, r3, r6
	mov	r3, #0
	mov	r10, #6
	rsb	r4, r4, r2
	mov	r2, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r8, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	mov	r6, r3
	str	r4, [r7, #36]
	b	.L1258
.L1256:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1348
.L1258:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1256
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1256
.L1346:
	ldr	ip, [fp, #-64]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [ip]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1297
.L1345:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	str	ip, [fp, #-56]
	rsb	r8, r5, #16
	add	r5, r10, r5
	mov	r1, r10
	rsb	r8, r10, r8
	bl	BsGet
	and	r8, r8, #7
	str	r5, [r7, #32]
	ldr	ip, [fp, #-56]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1248
.L1255:
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1298:
	ldr	r3, [fp, #-48]
	sub	ip, r3, #10
.L1264:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1349
.L1259:
	mov	r8, r4, asl #24
	cmp	r8, r6
	bhi	.L1260
	ldr	r2, [r7, #36]
	rsb	r8, r8, r6
	mov	r3, #0
	mov	r10, #6
	rsb	r1, r4, r2
	str	ip, [fp, #-60]
	mov	r2, #1
	mov	r6, r3
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r1, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1263
.L1261:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r10
	cmp	r1, r0
	sub	r10, r10, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r7, #36]
	movhi	ip, #0
	orr	r6, r6, ip
	rsbls	r4, r4, lr
	cmn	r10, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1350
.L1263:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1261
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r8, r0, asl ip
	b	.L1261
.L1260:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1299:
	ldr	r3, [fp, #-48]
	add	ip, ip, #1
	cmp	ip, r3
	bne	.L1264
	ldr	r2, [fp, #-68]
	add	r3, ip, #10
	str	r3, [fp, #-48]
	add	r2, r2, #1
	str	r2, [fp, #-68]
	ldr	r2, [fp, #-72]
	cmp	r3, r2
	bne	.L1265
	ldr	r2, [fp, #-84]
	mov	r10, #1
	mov	ip, r7
	add	r3, r2, #59
	add	r2, r2, #47
	str	r3, [fp, #-80]
	str	r2, [fp, #-72]
	str	r3, [fp, #-76]
.L1266:
	ldr	r3, [fp, #-72]
	mov	r8, ip
	str	r3, [fp, #-52]
	mov	r3, #2
	str	r3, [fp, #-68]
.L1281:
	ldr	r3, [fp, #-52]
	mov	ip, #0
	str	r3, [fp, #-48]
.L1272:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1351
.L1267:
	mov	r7, r4, asl #24
	cmp	r7, r6
	bhi	.L1268
	ldr	r1, [r8, #36]
	rsb	r7, r7, r6
	mov	r3, #6
	mov	r2, #0
	rsb	r1, r4, r1
	mov	r6, r3
	str	ip, [fp, #-64]
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r8, #28]
	mov	r4, r1, asl r4
	mov	r3, r7
	str	r5, [r8, #32]
	str	r4, [r8, #36]
	mov	r7, r2
	b	.L1271
.L1269:
	mov	r3, r4, asl #24
	mov	r1, r10, asl r6
	cmp	r3, r0
	sub	r6, r6, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r8, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r3, [r8, #28]
	str	r5, [r8, #32]
	str	r4, [r8, #36]
	beq	.L1352
.L1271:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r3
	add	r4, r4, #1
	bge	.L1269
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r8
	rsb	ip, r1, ip
	str	r3, [fp, #-60]
	str	ip, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	ip, [fp, #-56]
	ldr	r3, [fp, #-60]
	and	ip, ip, #7
	orr	r0, r3, r0, asl ip
	b	.L1269
.L1350:
	ldr	ip, [fp, #-60]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [ip]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1299
.L1268:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r8, #28]
	str	r5, [r8, #32]
	str	r4, [r8, #36]
.L1300:
	add	ip, ip, #1
	ldr	r3, [fp, #-48]
	cmp	ip, #3
	add	r3, r3, #1
	str	r3, [fp, #-48]
	bne	.L1272
	ldr	r3, [fp, #-68]
	subs	r3, r3, #1
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-52]
	add	r3, r3, #3
	str	r3, [fp, #-52]
	bne	.L1281
	ldr	r3, [fp, #-76]
	mov	r7, r8
	ldr	r2, [fp, #-68]
	str	r3, [fp, #-48]
.L1273:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1353
.L1274:
	mov	r8, r4, asl #24
	cmp	r8, r6
	bhi	.L1275
	ldr	r1, [r7, #36]
	rsb	r8, r8, r6
	mov	r3, #6
	mov	ip, #0
	rsb	r1, r4, r1
	mov	r6, r3
	str	r2, [fp, #-60]
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r1, asl r4
	mov	r3, r8
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	mov	r8, ip
	b	.L1278
.L1276:
	mov	r3, r4, asl #24
	mov	r2, r10, asl r6
	cmp	r3, r0
	sub	r6, r6, #1
	rsbls	r0, r3, r0
	ldrls	r1, [r7, #36]
	movhi	r2, #0
	orr	r8, r8, r2
	rsbls	r4, r4, r1
	cmn	r6, #1
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1354
.L1278:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r3
	add	r4, r4, #1
	bge	.L1276
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r2, r1, r2
	str	r3, [fp, #-56]
	str	r2, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r3, r0, asl r2
	b	.L1276
.L1352:
	ldr	r3, [fp, #-48]
	mov	r2, r7, asl #1
	orr	r2, r2, #1
	ldr	ip, [fp, #-64]
	strb	r2, [r3]
	ldr	r4, [r8, #36]
	ldr	r5, [r8, #32]
	ldr	r6, [r8, #28]
	b	.L1300
.L1349:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	str	ip, [fp, #-52]
	rsb	r8, r5, #16
	add	r5, r10, r5
	mov	r1, r10
	rsb	r8, r10, r8
	bl	BsGet
	and	r8, r8, #7
	str	r5, [r7, #32]
	ldr	ip, [fp, #-52]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1259
.L1275:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1301:
	add	r2, r2, #1
	ldr	r3, [fp, #-48]
	cmp	r2, #3
	add	r3, r3, #1
	str	r3, [fp, #-48]
	beq	.L1279
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1273
.L1354:
	ldr	r3, [fp, #-48]
	mov	ip, r8, asl #1
	orr	ip, ip, #1
	ldr	r2, [fp, #-60]
	strb	ip, [r3]
	b	.L1301
.L1279:
	ldr	r2, [fp, #-76]
	mov	ip, r7
	ldr	r3, [fp, #-72]
	add	r2, r2, #3
	str	r2, [fp, #-76]
	ldr	r2, [fp, #-80]
	add	r3, r3, #6
	str	r3, [fp, #-72]
	cmp	r2, r3
	beq	.L1280
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1266
.L1351:
	rsb	r3, r5, #24
	rsb	r7, r5, #16
	bic	r3, r3, #7
	mov	r0, r8
	rsb	r7, r3, r7
	str	ip, [fp, #-60]
	mov	r1, r3
	str	r3, [fp, #-56]
	bl	BsGet
	and	r7, r7, #7
	ldr	r3, [fp, #-56]
	ldr	ip, [fp, #-60]
	add	r5, r3, r5
	str	r5, [r8, #32]
	orr	r0, r6, r0, asl r7
	str	r0, [r8, #28]
	mov	r6, r0
	b	.L1267
.L1353:
	rsb	r3, r5, #24
	rsb	r8, r5, #16
	bic	r3, r3, #7
	mov	r0, r7
	rsb	r8, r3, r8
	str	r2, [fp, #-56]
	mov	r1, r3
	str	r3, [fp, #-52]
	bl	BsGet
	and	r8, r8, #7
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r5, r3, r5
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1274
.L1348:
	ldr	r2, [fp, #-68]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [r2]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1298
.L1344:
	ldr	r2, [fp, #-68]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-25]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1296
.L1280:
	ldr	r3, [fp, #-88]
	cmp	r3, #0
	beq	.L1236
	ldr	r3, [fp, #-84]
	add	r2, r3, #67
	add	r3, r3, #69
	str	r3, [fp, #-48]
	mov	r10, r2
.L1293:
	ldr	r1, [r7, #36]
	ldr	r5, [r7, #32]
	sub	r1, r1, #1
	cmp	r5, #0
	mov	r3, r1, asl #8
	sub	r1, r3, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1282
	ldr	r6, [r7, #28]
.L1283:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1284
	ldr	r1, [r7, #36]
	rsb	r6, r3, r6
	mov	r2, #0
	mov	r3, #6
	rsb	r1, r4, r1
	str	r10, [fp, #-60]
	mov	ip, #1
	mov	r8, r3
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r10, r2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r7, #28]
	mov	r4, r1, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1287
.L1285:
	mov	r3, r4, asl #24
	mov	r1, ip, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	lr, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r8, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1355
.L1287:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1285
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	str	ip, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L1285
.L1289:
	ldrb	r1, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	str	r6, [r7, #28]
	mov	r1, r4, asl r1
	str	r5, [r7, #32]
	str	r1, [r7, #36]
.L1303:
	ldr	r3, [fp, #-48]
	add	r10, r10, #1
	cmp	r10, r3
	bne	.L1293
.L1236:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1284:
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	str	r6, [r7, #28]
	mov	r3, r4, asl r3
	str	r5, [r7, #32]
	str	r3, [r7, #36]
.L1302:
	sub	r3, r3, #1
	cmp	r5, #0
	mov	r1, r3, asl #8
	sub	r3, r1, r3, asl #2
	mov	r1, r3, lsr #8
	add	r4, r1, #1
	blt	.L1356
.L1288:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1289
	ldr	r1, [r7, #36]
	rsb	r6, r3, r6
	mov	r2, #0
	mov	r3, #6
	rsb	r1, r4, r1
	str	r10, [fp, #-60]
	mov	ip, #1
	mov	r10, r2
	ldrb	r4, [r9, r1]	@ zero_extendqisi2
	mov	r8, r6, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r1, asl r4
	str	r5, [r7, #32]
	mov	r6, r3
	str	r4, [r7, #36]
	b	.L1292
.L1290:
	mov	r3, r4, asl #24
	mov	r1, ip, asl r6
	cmp	r3, r0
	sub	r6, r6, #1
	rsbls	r0, r3, r0
	ldrls	lr, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r6, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1357
.L1292:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1290
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	str	ip, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1290
.L1357:
	mov	r2, r10
	ldr	r10, [fp, #-60]
	mov	r3, r2, asl #1
	orr	r3, r3, #1
	strb	r3, [r10]
	b	.L1303
.L1355:
	mov	r2, r10
	ldr	r10, [fp, #-60]
	mov	r3, r2, asl #1
	orr	r3, r3, #1
	strb	r3, [r10, #-2]
	ldr	r3, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1302
.L1341:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	str	ip, [fp, #-52]
	rsb	r8, r5, #16
	add	r5, r10, r5
	mov	r1, r10
	rsb	r8, r10, r8
	bl	BsGet
	and	r8, r8, #7
	str	r5, [r7, #32]
	ldr	ip, [fp, #-52]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1237
.L1347:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	rsb	r8, r5, #16
	rsb	r8, r10, r8
	add	r5, r10, r5
	mov	r1, r10
	and	r8, r8, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1254
.L1343:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	rsb	r8, r5, #16
	rsb	r8, r10, r8
	add	r5, r10, r5
	mov	r1, r10
	and	r8, r8, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1243
.L1282:
	rsb	r8, r5, #24
	rsb	r3, r5, #16
	bic	r8, r8, #7
	mov	r0, r7
	rsb	r3, r8, r3
	ldr	r6, [r7, #28]
	mov	r1, r8
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r5, r5, r8
	str	r5, [r7, #32]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1283
.L1356:
	rsb	r3, r5, #24
	rsb	r8, r5, #16
	bic	r3, r3, #7
	mov	r0, r7
	rsb	r8, r3, r8
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r8, r8, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r5, r3, r5
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1288
.L1359:
	.align	2
.L1358:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadMvProbs, .-Vp9_ReadMvProbs
	.align	2
	.global	Vp9_PrepareReadModeInfo
	.type	Vp9_PrepareReadModeInfo, %function
Vp9_PrepareReadModeInfo:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r8, r0, #4352
	ldr	r7, .L1510
	mov	r6, r1
	mov	r10, r8
	add	r8, r8, #48
	add	r10, r10, #51
	mov	r9, r2
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r0, [fp, #-72]
	str	r3, [fp, #-48]
.L1364:
	ldr	r4, [r6, #36]
	ldr	r5, [r6, #32]
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1361
	ldr	r3, [r6, #28]
.L1362:
	mov	ip, r4, asl #24
	mov	r1, r8
	cmp	ip, r3
	mov	r0, r6
	rsb	r2, ip, r3
	bhi	.L1363
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	r2, r2, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1441:
	add	r8, r8, #1
	cmp	r8, r10
	bne	.L1364
	adds	r9, r9, #0
	ldr	r3, [fp, #-56]
	movne	r9, #1
	cmp	r3, #0
	movne	r9, #0
	cmp	r9, #0
	bne	.L1487
.L1365:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #16]
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1363:
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1441
.L1361:
	rsb	r2, r5, #24
	ldr	r3, [r6, #28]
	bic	r2, r2, #7
	rsb	ip, r5, #16
	mov	r0, r6
	rsb	ip, r2, ip
	mov	r1, r2
	str	ip, [fp, #-68]
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	bl	BsGet
	ldr	ip, [fp, #-68]
	ldr	r3, [fp, #-64]
	and	ip, ip, #7
	ldr	r2, [fp, #-60]
	add	r5, r5, r2
	str	r5, [r6, #32]
	orr	r0, r3, r0, asl ip
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L1362
.L1487:
	ldr	r4, [fp, #-72]
	mov	r1, r6
	mov	r0, r4
	bl	Vp9_ReadInterModeProbs
	ldr	r3, [fp, #4]
	cmp	r3, #4
	add	r3, r4, #4416
	add	r3, r3, #52
	str	r3, [fp, #-80]
	beq	.L1488
.L1366:
	ldr	r3, [fp, #-72]
	add	r10, r3, #4352
	add	r3, r3, #4416
	add	r3, r3, #3
	add	r10, r10, #63
	mov	r5, r3
.L1370:
	ldr	r4, [r6, #36]
	ldr	r8, [r6, #32]
	sub	r4, r4, #1
	cmp	r8, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1367
	ldr	r3, [r6, #28]
.L1368:
	mov	r2, r4, asl #24
	mov	r1, r10
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1369
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1442:
	add	r10, r10, #1
	cmp	r10, r5
	bne	.L1370
	ldr	ip, [fp, #-72]
	sub	r3, fp, #48
	ldr	r2, [fp, #8]
	mov	r1, r6
	add	lr, ip, #4096
	mov	r0, ip
	add	ip, ip, #4160
	mov	r4, lr
	mov	r5, ip
	bl	Vp9_ReadCompPred
	add	r3, r4, #9
	mov	lr, r4
	add	r4, r6, #28
	str	r3, [fp, #-56]
	add	r3, r5, #9
	str	r3, [fp, #-76]
	ldmia	r4, {r4, r5, r9}
	mov	r8, r5
.L1371:
	ldr	r3, [fp, #-56]
	sub	r10, r3, #9
.L1404:
	sub	r5, r9, #1
	cmp	r8, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L1489
.L1372:
	mov	r9, r5, asl #24
	cmp	r9, r4
	bhi	.L1373
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r5, r5, r3
	ldrb	r2, [r7, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r2
	rsb	r5, r2, r8
	sub	r4, r3, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl r2
	str	r3, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1490
.L1374:
	mov	r2, r4, asl #24
	cmp	r2, r9
	bhi	.L1375
	ldr	ip, [r6, #36]
	rsb	r9, r2, r9
	rsb	r4, r4, ip
	ldrb	r0, [r7, r4]	@ zero_extendqisi2
	mov	ip, r4, asl r0
	rsb	r4, r0, r5
	cmp	r4, #0
	sub	r5, ip, #1
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	ip, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1491
.L1377:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1382
	ldr	r2, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r2
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	rsb	r9, r0, r4
	mov	r2, r5, asl r0
	sub	r5, r2, #1
	cmp	r9, #0
	ubfx	r5, r5, #1, #24
	mov	r4, r3, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r9, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1492
.L1384:
	mov	r3, r5, asl #24
	cmp	r3, r4
	bhi	.L1388
	ldr	r1, [r6, #36]
	rsb	r3, r3, r4
	mov	r8, #0
	mov	r2, #6
	rsb	r5, r5, r1
	str	r10, [fp, #-68]
	mov	ip, #1
	mov	r10, r8
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r9, r4, r9
	str	r3, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	mov	r8, r3
	b	.L1389
.L1393:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1493
.L1389:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1393
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1393
.L1373:
	ldrb	r9, [r7, r5]	@ zero_extendqisi2
	mov	r4, r4, asl r9
	rsb	r8, r9, r8
	str	r4, [r6, #28]
	mov	r9, r5, asl r9
	str	r8, [r6, #32]
	str	r9, [r6, #36]
.L1443:
	ldr	r3, [fp, #-56]
	add	r10, r10, #1
	cmp	r10, r3
	bne	.L1404
	ldr	r2, [fp, #-76]
	add	r3, r10, #16
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L1371
	ldr	r3, [fp, #-72]
	add	r2, r3, #4608
	add	r3, r3, #4672
	add	r3, r3, #36
	str	r3, [fp, #-64]
	mov	r3, r9
	add	r2, r2, #52
	str	r2, [fp, #-60]
.L1405:
	ldr	r2, [fp, #-60]
	mov	r10, #0
	mov	r9, r3
	str	r2, [fp, #-56]
.L1440:
	sub	r9, r9, #1
	cmp	r8, #0
	mov	r2, r9, asl #8
	sub	r9, r2, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1494
.L1406:
	mov	r0, r9, asl #24
	cmp	r0, r4
	bhi	.L1407
	ldr	r3, [r6, #36]
	rsb	r0, r0, r4
	rsb	r3, r9, r3
	ldrb	r2, [r7, r3]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r8
	sub	r4, r3, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r0, asl r2
	str	r3, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1495
.L1408:
	mov	r2, r4, asl #24
	cmp	r2, r9
	bhi	.L1409
	ldr	ip, [r6, #36]
	rsb	r9, r2, r9
	rsb	r4, r4, ip
	ldrb	r0, [r7, r4]	@ zero_extendqisi2
	mov	ip, r4, asl r0
	rsb	r4, r0, r5
	cmp	r4, #0
	sub	r5, ip, #1
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	ip, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1496
.L1411:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1416
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	mov	r1, r5, asl r0
	rsb	r5, r0, r4
	sub	r9, r1, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r4, r3, asl r0
	str	r1, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1497
.L1418:
	mov	r3, r9, asl #24
	cmp	r3, r4
	bhi	.L1422
	ldr	r1, [r6, #36]
	rsb	r0, r3, r4
	mov	r2, #6
	mov	r3, #0
	rsb	r4, r9, r1
	str	r10, [fp, #-76]
	mov	ip, #1
	mov	r10, r3
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	rsb	r8, r1, r5
	mov	r9, r0, asl r1
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	b	.L1423
.L1427:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r9, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1498
.L1423:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L1427
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-68]
	ldr	ip, [fp, #-72]
	and	r2, r2, #7
	orr	r0, r9, r0, asl r2
	b	.L1427
.L1407:
	ldrb	r3, [r7, r9]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r8
	mov	r9, r9, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r9, [r6, #36]
.L1444:
	add	r10, r10, #1
	ldr	r3, [fp, #-56]
	cmp	r10, #3
	add	r3, r3, #1
	str	r3, [fp, #-56]
	addne	r4, r6, #28
	ldmneia	r4, {r4, r8, r9}
	bne	.L1440
.L1499:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	add	r3, r3, #3
	str	r3, [fp, #-60]
	cmp	r3, r2
	beq	.L1439
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r8, [r6, #32]
	b	.L1405
.L1494:
	rsb	r2, r8, #24
	rsb	r5, r8, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r5, r2, r5
	str	r2, [fp, #-68]
	mov	r1, r2
	bl	BsGet
	ldr	r2, [fp, #-68]
	and	r3, r5, #7
	add	r5, r2, r8
	str	r5, [r6, #32]
	mov	r8, r5
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1406
.L1409:
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-76]
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r10, r8
	mov	ip, #1
	mov	r8, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L1414
.L1412:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1500
.L1414:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1412
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-68]
	ldr	ip, [fp, #-72]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1412
.L1500:
	mov	r8, r10
	ldr	r10, [fp, #-76]
.L1415:
	ldr	r3, [fp, #-56]
	add	r8, r7, r8
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1432
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1433
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1433:
	add	r3, r3, #1
.L1435:
	ldr	r2, [fp, #-56]
	strb	r3, [r2]
	b	.L1444
.L1432:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1436
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1436:
	rsb	r3, r3, #255
	b	.L1435
.L1489:
	rsb	r3, r8, #24
	rsb	r9, r8, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r8, r3, r8
	str	r8, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1372
.L1375:
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r10, r8
	mov	ip, #1
	mov	r8, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L1380
.L1378:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1501
.L1380:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1378
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1378
.L1501:
	mov	r8, r10
	ldr	r10, [fp, #-68]
.L1381:
	ldrb	r2, [r10]	@ zero_extendqisi2
	add	r8, r7, r8
	sub	ip, r2, #1
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1398
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1399
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1399:
	add	r3, r3, #1
.L1401:
	add	r4, r6, #28
	strb	r3, [r10]
	ldmia	r4, {r4, r8, r9}
	b	.L1443
.L1398:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1402
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1402:
	rsb	r3, r3, #255
	b	.L1401
.L1416:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-76]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r8
	mov	ip, #1
	mov	r8, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1421
.L1419:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1502
.L1421:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1419
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-68]
	ldr	ip, [fp, #-72]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1419
.L1502:
	mov	r8, r10
	ldr	r10, [fp, #-76]
	add	r8, r8, #16
	b	.L1415
.L1498:
	mov	r3, r10
	cmp	r3, #64
	ldr	r10, [fp, #-76]
	bgt	.L1503
.L1429:
	add	r8, r3, #64
	b	.L1415
.L1382:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-68]
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r8
	mov	ip, #1
	mov	r8, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1387
.L1385:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	ldrb	r2, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1504
.L1387:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1385
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1385
.L1504:
	mov	r8, r10
	ldr	r10, [fp, #-68]
	add	r8, r8, #16
	b	.L1381
.L1493:
	mov	r3, r8
	mov	r8, r10
	cmp	r8, #64
	ldr	r10, [fp, #-68]
	bgt	.L1505
.L1395:
	add	r8, r8, #64
	b	.L1381
.L1422:
	ldrb	r1, [r7, r9]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #4
	str	r10, [fp, #-76]
	mov	r3, r4, asl r1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #36]
	mov	r10, r8
	mov	r4, r9
	mov	ip, #1
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	mov	r8, r3
	mov	r9, r2
	b	.L1426
.L1424:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1506
.L1426:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1424
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-68]
	ldr	ip, [fp, #-72]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1424
.L1506:
	mov	r8, r10
	ldr	r10, [fp, #-76]
	add	r8, r8, #32
	b	.L1415
.L1495:
	rsb	r3, r5, #24
	rsb	r8, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r8, r3, r8
	str	r3, [fp, #-68]
	mov	r1, r3
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-68]
	add	r5, r5, r3
	str	r5, [r6, #32]
	orr	r0, r9, r0, asl r2
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1408
.L1369:
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	b	.L1442
.L1388:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #4
	str	r10, [fp, #-68]
	mov	r3, r4, asl r1
	rsb	r9, r1, r9
	mov	r4, r5, asl r1
	mov	r10, r8
	mov	ip, #1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	mov	r8, r3
	b	.L1392
.L1390:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1507
.L1392:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1390
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	ip, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L1390
.L1507:
	mov	r8, r10
	ldr	r10, [fp, #-68]
	add	r8, r8, #32
	b	.L1381
.L1490:
	rsb	r3, r5, #24
	rsb	r8, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r8, r3, r8
	str	r3, [fp, #-60]
	mov	r1, r3
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-60]
	add	r5, r5, r3
	str	r5, [r6, #32]
	orr	r0, r9, r0, asl r2
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1374
.L1503:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r3, r3, asl #1
	add	r4, r4, #1
	sub	r5, r3, #65
	movge	r0, r9
	blt	.L1508
.L1430:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r3, r5, r3
	rsbls	r4, r4, r2
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	mov	r9, r0, asl r1
	rsb	r2, r1, r8
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r2, [r6, #32]
	str	r4, [r6, #36]
	b	.L1429
.L1496:
	rsb	r2, r4, #24
	rsb	r8, r4, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r8, r2, r8
	str	r2, [fp, #-68]
	mov	r1, r2
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-68]
	add	r4, r4, r2
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1411
.L1439:
	ldr	r1, [fp, #-80]
	mov	r0, r6
	ldr	r2, [fp, #12]
	bl	Vp9_ReadMvProbs
	b	.L1365
.L1505:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r5, r8, #65
	movge	r0, r3
	blt	.L1509
.L1396:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r1, [r6, #36]
	movls	r8, #1
	movhi	r8, #0
	add	r8, r5, r8
	rsbls	r4, r4, r1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L1395
.L1491:
	rsb	r2, r4, #24
	rsb	r8, r4, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r8, r2, r8
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	add	r4, r4, r2
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L1377
.L1511:
	.align	2
.L1510:
	.word	.LANCHOR0
.L1497:
	rsb	r2, r5, #24
	rsb	r8, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r8, r2, r8
	str	r2, [fp, #-68]
	mov	r1, r2
	bl	BsGet
	ldr	r2, [fp, #-68]
	and	r3, r8, #7
	add	r8, r5, r2
	str	r8, [r6, #32]
	mov	r5, r8
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1418
.L1367:
	rsb	r2, r8, #24
	rsb	r3, r8, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r3, r2, r3
	ldr	r9, [r6, #28]
	mov	r1, r2
	str	r3, [fp, #-60]
	str	r2, [fp, #-56]
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	add	r8, r8, r2
	str	r8, [r6, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L1368
.L1492:
	rsb	r2, r9, #24
	rsb	r8, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r8, r2, r8
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1384
.L1508:
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	add	r8, r1, r8
	str	r3, [fp, #-68]
	bl	BsGet
	ldr	r3, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r9, r0, asl r3
	b	.L1430
.L1488:
	mov	r1, r6
	ldr	r0, [fp, #-72]
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1366
.L1509:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r3, [fp, #-60]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r8, r8, #7
	orr	r0, r3, r0, asl r8
	b	.L1396
	UNWIND(.fnend)
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.global	__aeabi_uidiv
	.align	2
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r7, r0
	ldrsb	r0, [r1, r0]
	mov	r8, r1
	mov	r6, r2
	mov	r5, r3
	cmp	r0, #0
	ldr	r4, [fp, #4]
	ble	.L1521
	str	r4, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r8, r7
	mov	r9, r0
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	ble	.L1522
.L1515:
	str	r4, [sp]
	mov	r1, r8
	mov	r3, r5
	mov	r2, r6
	bl	Vp9_AdaptProbs
.L1516:
	adds	r4, r0, r9
	ldrb	r5, [r5, r7, lsr #1]	@ zero_extendqisi2
	beq	.L1517
	ldr	r3, .L1523
	mov	r0, r9, asl #8
	mov	r1, r4
	add	r0, r0, r4, lsr #1
	cmp	r4, #20
	addls	r3, r3, r4
	addhi	r3, r3, #20
	ldrb	r8, [r3, #512]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	rsb	r3, r8, #256
	mul	r5, r5, r3
	add	r3, r5, #128
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movlt	r1, r0
	movge	r1, #255
	uxtb	r1, r1
	mla	r5, r8, r1, r3
	ubfx	r5, r5, #8, #8
.L1517:
	mov	r0, r4
	strb	r5, [r6, r7, lsr #1]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1521:
	mov	r0, r0, asl #2
	add	r3, r8, r7
	rsb	r0, r0, #0
	ldr	r9, [r4, r0]
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	bgt	.L1515
.L1522:
	mov	r0, r0, asl #2
	rsb	r0, r0, #0
	ldr	r0, [r4, r0]
	b	.L1516
.L1524:
	.align	2
.L1523:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	2
	.global	Lf_Init_Lut
	.type	Lf_Init_Lut, %function
Lf_Init_Lut:
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
	mov	r3, #0
	mov	r2, #1
	strb	r3, [r0, #64]
	strb	r3, [r0, #67]
	strb	r3, [r0, #68]
	strb	r3, [r0, #69]
	strb	r3, [r0, #70]
	strb	r3, [r0, #71]
	strb	r3, [r0, #72]
	strb	r3, [r0, #65]
	strb	r3, [r0, #66]
	strb	r3, [r0, #73]
	strb	r3, [r0, #76]
	strb	r2, [r0, #74]
	strb	r2, [r0, #75]
	strb	r2, [r0, #77]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Lf_Init_Lut, .-Lf_Init_Lut
	.align	2
	.global	VP9_Loop_Filter_Init
	.type	VP9_Loop_Filter_Init, %function
VP9_Loop_Filter_Init:
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
	mov	r3, #0
	mov	r2, #1
	strb	r3, [r1, #64]
	strb	r3, [r1, #67]
	strb	r3, [r1, #68]
	strb	r3, [r1, #69]
	strb	r3, [r1, #70]
	strb	r3, [r1, #71]
	strb	r3, [r1, #72]
	strb	r3, [r1, #65]
	strb	r3, [r1, #66]
	strb	r3, [r1, #73]
	strb	r3, [r1, #76]
	strb	r2, [r1, #74]
	strb	r2, [r1, #75]
	strb	r2, [r1, #77]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Loop_Filter_Init, .-VP9_Loop_Filter_Init
	.align	2
	.global	VP9_InitDecPara
	.type	VP9_InitDecPara, %function
VP9_InitDecPara:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r7, .L1528
	movw	r6, #10820
	movt	r6, 4
	add	r6, r0, r6
	mov	r5, r0
	mov	r1, #0
	movw	r2, #5488
	ldr	r3, [r7, #48]
	mov	r0, r6
	add	r4, r5, #270336
	blx	r3
	add	r3, r5, #274432
	movw	r0, #16312
	mov	r2, #3
	movt	r0, 4
	str	r2, [r3, #3600]
	add	r0, r5, r0
	mov	r5, #0
	bl	ResetVoQueue
	ldr	r3, [r7, #48]
	mov	r2, #2
	add	r0, r6, #64
	str	r2, [r4, #2864]
	mov	r1, r5
	str	r5, [r4, #2860]
	mov	r2, #16
	blx	r3
	mov	r3, #1
	strb	r5, [r4, #2948]
	strb	r5, [r4, #2951]
	strb	r5, [r4, #2952]
	strb	r5, [r4, #2953]
	strb	r5, [r4, #2954]
	strb	r5, [r4, #2955]
	strb	r5, [r4, #2956]
	strb	r5, [r4, #2949]
	strb	r5, [r4, #2950]
	strb	r5, [r4, #2957]
	strb	r5, [r4, #2960]
	strb	r3, [r4, #2958]
	strb	r3, [r4, #2959]
	strb	r3, [r4, #2961]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1529:
	.align	2
.L1528:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_InitDecPara, .-VP9_InitDecPara
	.align	2
	.global	VP9DEC_Init
	.type	VP9DEC_Init, %function
VP9DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r5, r0
	mov	r8, r1
	mov	r0, #2
	ldr	r1, .L1544
	add	r4, r5, #278528
	bl	dprint_vfmw
	ldr	r3, [r8, #616]
	ldr	r10, .L1544+4
	mov	r1, #0
	cmp	r3, #1
	ldr	r6, [r4, #272]
	addeq	r7, r5, #311296
	addeq	r3, r5, #270336
	mov	r0, r5
	movne	r9, #0
	ldreq	r2, [r7, #2724]
	addne	r7, r5, #311296
	ldreq	r9, [r3, #2568]
	ldr	r3, [r10, #48]
	strne	r9, [fp, #-48]
	streq	r2, [fp, #-48]
	movw	r2, #52024
	movt	r2, 4
	blx	r3
	movw	r0, #16312
	str	r6, [r4, #272]
	movt	r0, 4
	add	r0, r5, r0
	bl	ResetVoQueue
	str	r8, [r5]
	mov	r0, r5
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r7, #2860]
	beq	.L1543
	ldr	r3, [r5]
	add	r4, r5, #270336
	mov	r6, #0
	mov	r2, #3
	ldr	r1, [r3, #8]
	str	r2, [r4, #2624]
	str	r2, [r4, #2572]
	str	r1, [r4, #2564]
	str	r6, [r4, #2576]
	ldr	r0, [r3, #48]
	str	r0, [r4, #2580]
	ldr	r3, [r3, #52]
	str	r3, [r4, #2584]
	bl	MEM_Phy2Vir
	mov	r3, #2048
	str	r3, [r4, #2592]
	mov	r2, #32
	mov	r1, #0
	str	r0, [r4, #2588]
	movw	r0, #51924
	str	r6, [r7, #2736]
	movt	r0, 4
	str	r6, [r7, #2740]
	add	r0, r5, r0
	str	r6, [r7, #2764]
	str	r6, [r7, #2768]
	str	r6, [r7, #2804]
	str	r6, [r7, #2808]
	ldr	r3, [r8, #616]
	cmp	r3, #1
	strne	r6, [r7, #2724]
	strne	r6, [r4, #2568]
	ldreq	r3, [fp, #-48]
	streq	r3, [r7, #2724]
	ldr	r3, [r10, #48]
	streq	r9, [r4, #2568]
	blx	r3
	mov	r0, r5
	bl	VP9_InitDecPara
	movw	r0, #10932
	add	r2, r4, #2704
	movt	r0, 4
	add	r0, r5, r0
	mov	ip, #0
	mov	r3, r2
	mov	r1, r0
.L1536:
	str	ip, [r3, #4]!
	cmp	r3, r0
	str	ip, [r1, #4]!
	bne	.L1536
	movw	r3, #11012
	movw	r1, #11048
	movt	r3, 4
	movt	r1, 4
	add	r3, r5, r3
	add	r1, r5, r1
	mvn	r0, #0
.L1537:
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L1537
	movw	r1, #10968
	mov	r3, #0
	movt	r1, 4
	add	r1, r5, r1
	mov	r0, #1
.L1538:
	str	r3, [r1, #4]!
	add	r3, r3, #1
	cmp	r3, #8
	str	r0, [r2, #4]!
	bne	.L1538
	mov	r0, #0
.L1533:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1543:
	ldr	r1, .L1544+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1533
.L1545:
	.align	2
.L1544:
	.word	.LC1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	VP9DEC_Init, .-VP9DEC_Init
	.align	2
	.global	Vp9_ParseSuperFrameIndex
	.type	Vp9_ParseSuperFrameIndex, %function
Vp9_ParseSuperFrameIndex:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	ble	.L1558
	add	ip, r0, r1
	mov	r5, #0
	ldrb	ip, [ip, #-1]	@ zero_extendqisi2
	str	r5, [r3]
	and	lr, ip, #224
	cmp	lr, #192
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	and	r6, ip, #7
	ubfx	r8, ip, #3, #2
	add	r6, r6, #1
	add	r7, r8, #1
	mul	r4, r6, r7
	add	r4, r4, #2
	cmp	r1, r4
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	rsb	lr, r4, r1
	ldrb	lr, [r0, lr]	@ zero_extendqisi2
	cmp	lr, ip
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r1, r1, #1
	cmp	r6, r5
	rsb	r1, r4, r1
	add	r4, r0, r1
	beq	.L1549
	sub	r9, r2, #4
.L1550:
	cmp	r7, #0
	beq	.L1553
	mov	r2, #0
	sub	r1, r4, #1
	add	lr, r4, r8
	mov	r0, r2
.L1551:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	cmp	r1, lr
	orr	r0, r0, ip, asl r2
	add	r2, r2, #8
	bne	.L1551
	add	r4, r4, r7
.L1552:
	add	r5, r5, #1
	str	r0, [r9, #4]!
	cmp	r6, r5
	bhi	.L1550
.L1549:
	str	r6, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1558:
	ldr	r1, .L1559
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1553:
	mov	r0, r7
	b	.L1552
.L1560:
	.align	2
.L1559:
	.word	.LC3
	UNWIND(.fnend)
	.size	Vp9_ParseSuperFrameIndex, .-Vp9_ParseSuperFrameIndex
	.align	2
	.global	VP9_GetImageBuffer
	.type	VP9_GetImageBuffer, %function
VP9_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r0, #274432
	add	r5, r0, #311296
	add	r6, r0, #270336
	mov	r4, r0
	ldr	r3, [r7, #3620]
	ldr	r0, [r5, #2860]
	cmp	r3, #1
	moveq	r1, #0
	movne	r1, #1
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #2612]
	blt	.L1580
	mov	r1, r0
	ldr	r0, [r5, #2860]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L1581
	ldr	r2, [r6, #2612]
	mov	r0, #18
	ldr	r1, .L1584
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L1567
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L1567
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L1584+4
	bl	dprint_vfmw
	ldr	r3, [r7, #3620]
	cmp	r3, #1
	beq	.L1582
	ldr	r2, [r4, #28]
	mov	r3, #0
	mov	r0, r3
	str	r3, [r2, #80]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1567:
	movw	r2, #2258
	ldr	r1, .L1584+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1580:
	ldr	r1, .L1584+12
	mov	r0, #0
	bl	dprint_vfmw
	movw	r1, #16312
	ldr	r0, [r5, #2860]
	movt	r1, 4
	add	r1, r4, r1
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1581:
	movw	r2, #2246
	ldr	r1, .L1584+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1582:
	ldr	r3, [r7, #3624]
	cmp	r3, #8
	bls	.L1570
	ldr	r2, .L1584+20
	mov	r0, #0
	ldr	r1, .L1584+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1570:
	add	r6, r6, r3, lsl #2
	ldr	r0, [r5, #2860]
	ldr	r1, [r6, #2824]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1583
	ldr	ip, [r3, #28]
	add	r1, r3, #40
	mov	r2, #632
	add	r0, r4, #40
	str	ip, [r4, #28]
	ldr	r3, [r3, #28]
	str	r3, [r4, #32]
	ldr	r3, [ip, #72]
	str	r3, [r4, #20]
	bl	memcpy
	ldrsb	r3, [r4, #3]
	mov	r0, #0
	strb	r0, [r4, #2]
	str	r3, [r4, #188]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1583:
	ldr	r3, .L1584+28
	movw	r2, #2275
	ldr	r1, .L1584+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1585:
	.align	2
.L1584:
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC4
	.word	.LC5
	.word	.LANCHOR0+536
	.word	.LC9
	.word	.LC10
	.word	.LC11
	UNWIND(.fnend)
	.size	VP9_GetImageBuffer, .-VP9_GetImageBuffer
	.align	2
	.global	VP9_FreeCurFb
	.type	VP9_FreeCurFb, %function
VP9_FreeCurFb:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #270336
	add	r4, r0, #311296
	ldr	r1, [r5, #2612]
	cmp	r1, #0
	blt	.L1587
	mov	r2, #1
	ldr	r0, [r4, #2860]
	bl	FSP_ClearLogicFs
.L1587:
	ldr	r3, [r4, #2760]
	cmp	r3, #8
	addls	r3, r3, #20
	movls	r2, #0
	addls	r5, r5, r3, lsl #2
	strls	r2, [r5, #2628]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_FreeCurFb, .-VP9_FreeCurFb
	.align	2
	.global	VP9_SetImgFormat
	.type	VP9_SetImgFormat, %function
VP9_SetImgFormat:
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
	subs	r6, r0, #0
	beq	.L1591
	add	r3, r6, #311296
	add	r5, r6, #270336
	ldr	r0, [r3, #2860]
	ldr	r1, [r5, #2612]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1591
	ldr	r8, [r6]
	add	r7, r4, #592
	mvn	r2, #0
	mvn	r3, #0
	mov	lr, #5
	mov	ip, #1
	ldrd	r8, [r8, #56]
	mov	r1, #0
	strd	r8, [r7, #-8]
	ldr	r7, [r6]
	strd	r2, [r7, #56]
	ldr	r8, [r5, #2620]
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	and	r7, r8, #3
	bfi	r3, r8, #0, #2
	and	r3, r3, #227
	orr	r2, r2, #12
	bfi	r3, lr, #5, #3
	bfi	r2, ip, #4, #2
	strb	r3, [r4, #64]
	strb	r2, [r4, #65]
	ldr	r3, [r4, #64]
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	mov	r2, r3, lsr #8
	mov	r3, r3, lsr #16
	bfc	r2, #0, #2
	strb	r2, [r4, #65]
	ldrb	r2, [r5, #2628]	@ zero_extendqisi2
	bfi	r3, r2, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #2632]
	str	r7, [r4, #56]
	str	r7, [r4, #60]
	str	r3, [r4, #120]
	bl	SetAspectRatio
	ldr	lr, [r5, #2648]
	str	lr, [r4, #68]
	ldr	ip, [r5, #2652]
	str	ip, [r4, #72]
	ldr	r3, [r6]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1595
	add	r7, r4, #512
	ldr	r1, [r4, #36]
	ldrd	r2, [r7, #-8]
	strd	r2, [fp, #-68]
.L1596:
	add	r2, lr, #255
	ldr	r8, [r5, #2480]
	bic	r2, r2, #255
	add	r0, ip, #63
	cmp	r2, #0
	add	r3, r2, #3
	str	r8, [r4, #124]
	mov	r8, lr, lsr #1
	movge	r3, r2
	ldr	r2, [r5, #2488]
	mov	r3, r3, asr #2
	str	r8, [fp, #-52]
	mov	r8, ip, lsr #1
	str	r8, [fp, #-56]
	str	r2, [r4, #128]
	mov	r8, r3, asl #5
	ldr	r2, [r5, #2492]
	bic	r0, r0, #63
	mov	r9, r8, lsr #1
	str	r9, [fp, #-48]
	ldrd	r8, [fp, #-68]
	str	r2, [r4, #132]
	ldr	r2, [r5, #2104]
	str	r2, [r4, #112]
	ldr	r2, [r5, #2112]
	str	r2, [r4, #116]
	ldr	r10, [r6]
	ldr	r2, [r5, #2116]
	ldr	r10, [r10, #900]
	adds	r8, r8, r2
	adc	r9, r9, r2, asr #31
	str	r10, [r4, #168]
	ldr	r10, [r6]
	add	r6, r2, r2, lsl #1
	add	r2, r1, r2
	add	r6, r6, r6, lsr #31
	ldr	r10, [r10, #900]
	add	r6, r1, r6, asr #1
	str	r10, [r4, #172]
	mla	r3, r3, r0, r6
	ldr	r1, [r5, #2508]
	str	r1, [r4, #136]
	ldr	r1, [r5, #2512]
	str	r2, [r4, #40]
	ldr	r2, [fp, #-52]
	str	r1, [r4, #140]
	strd	r8, [r7]
	str	r6, [r4, #44]
	str	lr, [r4, #76]
	str	ip, [r4, #80]
	str	r2, [r4, #84]
	str	r3, [r4, #48]
	ldr	r3, [fp, #-48]
	ldr	r8, [fp, #-56]
	str	r3, [r4, #144]
	str	r8, [r4, #88]
.L1591:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1595:
	ldr	r8, [r4, #112]
	add	r0, ip, #15
	ldr	r1, [r4, #36]
	add	r7, r4, #512
	mov	r3, r0, lsr #4
	mov	r0, r8, asl #4
	add	r10, r1, r8
	mul	r0, r3, r0
	add	r9, r0, r1
	str	r9, [r4, #40]
	ldrd	r2, [r7, #-8]
	add	r8, r9, r8
	strd	r2, [fp, #-68]
	adds	r2, r2, r0
	adc	r3, r3, r0, asr #31
	strd	r2, [r7]
	str	r9, [r4, #24]
	str	r8, [r4, #32]
	str	r10, [r4, #28]
	str	r1, [r4, #20]
	b	.L1596
	UNWIND(.fnend)
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
	.align	2
	.global	VP9DEC_VDMPostProc
	.type	VP9DEC_VDMPostProc, %function
VP9DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r2, #0
	str	r2, [fp, #-64]
	add	r2, r0, #274432
	add	r8, r0, #270336
	mov	r7, r0
	mov	ip, r2
	str	r2, [fp, #-48]
	ldrb	r0, [r8, #2089]	@ zero_extendqisi2
	str	r1, [fp, #-52]
	ldr	r2, [r8, #2476]
	ldr	r1, [ip, #3680]
	str	r3, [fp, #-56]
	ldr	r3, [ip, #3672]
	str	r1, [fp, #-68]
	strb	r0, [r8, #2628]
	str	r3, [fp, #-72]
	str	r2, [r8, #2632]
	beq	.L1601
	ldr	r1, [fp, #-56]
	ldr	r2, .L1662
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L1618
.L1601:
	add	r6, r7, #311296
	ldr	r3, [r6, #2768]
	cmp	r3, #0
	beq	.L1604
	ldr	r2, [r6, #2808]
	ldr	r3, [r6, #2804]
	cmp	r2, r3
	beq	.L1604
.L1605:
	ldr	r1, [r8, #2612]
	ldr	r0, [r6, #2860]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	str	r3, [fp, #-60]
	beq	.L1624
	movw	r4, #10932
	movw	r5, #11012
	movw	r9, #10968
	movt	r4, 4
	movt	r5, 4
	movt	r9, 4
	add	r4, r7, r4
	add	r5, r7, r5
	add	r10, r8, #2704
	add	r9, r7, r9
	b	.L1609
.L1607:
	clz	r3, r3
	cmp	r0, #0
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L1652
.L1608:
	cmp	r4, r9
	beq	.L1653
.L1609:
	ldr	r3, [r10, #4]!
	ldr	r0, [r4, #4]!
	adds	r2, r3, #0
	ldr	r1, [r5, #4]!
	movne	r2, #1
	cmp	r0, #0
	movne	r2, #0
	cmp	r2, #0
	beq	.L1607
	mov	r2, #1
	ldr	r0, [r6, #2860]
	bl	FSP_SetRef
	cmp	r4, r9
	bne	.L1609
.L1653:
	ldr	r3, .L1662+4
	movw	r0, #10820
	movt	r0, 4
	add	r0, r7, r0
	add	r1, r0, #80
	mov	r2, #36
	ldr	r3, [r3, #52]
	add	r0, r0, #116
	blx	r3
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	blt	.L1610
	cmp	r3, #100
	movlt	r2, r3
	ldr	r3, [fp, #-60]
	movge	r2, #100
	str	r2, [r3, #152]
	ldr	r3, [r7]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L1654
.L1611:
	mov	r0, r7
	bl	VP9_SetImgFormat
	ldr	r3, [r8, #2564]
	cmp	r3, #2
	beq	.L1655
.L1612:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #3616]
	cmp	r3, #0
	bne	.L1614
.L1613:
	mvn	r3, #0
	ldr	r1, [r8, #2612]
	str	r3, [r8, #2616]
	mov	r2, #0
	ldr	r0, [r6, #2860]
	bl	FSP_SetDisplay
	ldr	r1, [r8, #2616]
.L1615:
	cmn	r1, #1
	beq	.L1616
	ldr	r0, [r6, #2860]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1656
	mov	r2, #1
	ldr	r1, [r8, #2616]
	ldr	r0, [r6, #2860]
	bl	FSP_SetDisplay
	movw	r3, #16312
	ldr	r0, [r6, #2860]
	movt	r3, 4
	str	r4, [sp]
	mov	r2, r7
	add	r3, r7, r3
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r4, r0
	bne	.L1657
.L1616:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	beq	.L1618
	ldr	r1, [fp, #-56]
	ldr	r2, .L1662
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #2
	beq	.L1603
.L1618:
	ldr	r3, [fp, #-48]
	ldr	r4, [r3, #3620]
	cmp	r4, #0
	beq	.L1658
.L1603:
	mov	r4, #0
.L1650:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1652:
	ldr	r0, [r6, #2860]
	bl	FSP_SetRef
	b	.L1608
.L1614:
	ldr	r1, [r8, #2612]
	str	r1, [r8, #2616]
	b	.L1615
.L1658:
	ldr	r0, [r8, #2364]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L1659
	add	r6, r7, #311296
	ldr	r3, [r6, #2824]
	cmp	r3, #0
	ldr	r3, [r6, #2844]
	bne	.L1660
	cmp	r3, #0
	strne	r4, [fp, #-68]
	bne	.L1622
	ldr	r3, [r6, #2828]
	cmp	r3, #0
	ldr	r3, [fp, #-68]
	movne	r3, #0
	str	r3, [fp, #-68]
.L1621:
	ldr	r3, [r6, #2848]
	cmp	r3, #0
	beq	.L1661
.L1622:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	beq	.L1603
	ldr	r3, [fp, #-68]
	movw	r2, #4708
	add	r1, r7, #278528
	add	r1, r1, #312
	mla	r0, r2, r3, r7
	add	r0, r0, #282624
	add	r0, r0, #924
	bl	memcpy
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1604:
	mov	r1, r7
	mov	r0, #17
	bl	ReleasePacket
	mov	r3, #0
	str	r3, [r6, #2768]
	b	.L1605
.L1610:
	ldr	r2, [fp, #-60]
	mov	r3, #0
	str	r3, [r2, #152]
	b	.L1611
.L1655:
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L1613
	b	.L1612
.L1660:
	cmp	r3, #0
	str	r4, [fp, #-68]
	beq	.L1621
	b	.L1622
.L1657:
	ldr	r1, [r8, #2616]
	mov	r2, #0
	ldr	r0, [r6, #2860]
	bl	FSP_SetDisplay
	ldr	r1, .L1662+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1661:
	ldr	r10, .L1662+4
	mov	r2, #5120
	ldr	r1, [r8, #2364]
	mov	r0, r5
	add	r8, r7, #282624
	ldr	r3, [r10, #140]
	add	r9, r8, #568
	blx	r3
	add	r0, r7, #278528
	ldr	r3, [r10, #52]
	mov	r2, #4096
	mov	r1, r5
	add	r0, r0, #312
	blx	r3
	ldr	r3, [r10, #52]
	mov	r2, #256
	add	r1, r5, #4096
	add	r0, r8, #312
	blx	r3
	ldr	r3, [r10, #52]
	add	r1, r5, #4352
	mov	r0, r9
	mov	r2, #256
	blx	r3
	ldr	r3, [r6, #2828]
	cmp	r3, #0
	beq	.L1623
	ldr	r3, [r10, #52]
	mov	r1, r9
	add	r0, r8, #828
	mov	r2, #48
	blx	r3
	b	.L1622
.L1654:
	ldr	r1, .L1662+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r8, #2612]
	ldr	r0, [r6, #2860]
	mov	r2, #0
	bl	FSP_SetDisplay
	ldr	r1, [r8, #2612]
	ldr	r0, [r6, #2860]
	mov	r2, #0
	mvn	r4, #0
	bl	FSP_SetRef
	b	.L1650
.L1623:
	ldr	r0, [r6, #2836]
	mov	r1, r9
	ldr	ip, [r10, #52]
	mov	r2, #48
	mov	r3, r0, asl #6
	sub	r0, r3, r0, asl #4
	add	r0, r7, r0
	add	r0, r0, #282624
	add	r0, r0, #828
	blx	ip
	b	.L1622
.L1656:
	movw	r2, #2596
	ldr	r1, .L1662+16
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L1650
.L1624:
	ldr	r1, .L1662+20
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L1650
.L1659:
	ldr	r1, .L1662+24
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L1650
.L1663:
	.align	2
.L1662:
	.word	g_VdmDrvParam+40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	.word	.LC13
	.word	.LC14
	.word	.LC12
	.word	.LC16
	UNWIND(.fnend)
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	2
	.global	VP9DEC_RecycleImage
	.type	VP9DEC_RecycleImage, %function
VP9DEC_RecycleImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #311296
	mov	r5, r1
	mov	r2, #0
	ldr	r0, [r4, #2860]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2860]
	bl	FSP_GetFsImagePtr
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9DEC_RecycleImage, .-VP9DEC_RecycleImage
	.align	2
	.global	VP9DEC_GetRemainImg
	.type	VP9DEC_GetRemainImg, %function
VP9DEC_GetRemainImg:
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
	add	r0, r0, #274432
	add	r0, r0, #4016
	add	r0, r0, #8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetVoLastImageID
	UNWIND(.fnend)
	.size	VP9DEC_GetRemainImg, .-VP9DEC_GetRemainImg
	.align	2
	.global	VP9DEC_GetImageBuffer
	.type	VP9DEC_GetImageBuffer, %function
VP9DEC_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #311296
	mov	r5, r0
	ldr	r0, [r4, #2860]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2860]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L1672
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1672:
	movw	r1, #16312
	ldr	r0, [r4, #2860]
	movt	r1, 4
	add	r1, r5, r1
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9DEC_GetImageBuffer, .-VP9DEC_GetImageBuffer
	.align	2
	.global	Check_Sync_Code
	.type	Check_Sync_Code, %function
Check_Sync_Code:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #8
	mov	r4, r0
	bl	BsGet
	cmp	r0, #73
	beq	.L1674
.L1675:
	ldr	r1, .L1676
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1674:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	cmp	r0, #131
	bne	.L1675
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	cmp	r0, #66
	bne	.L1675
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1677:
	.align	2
.L1676:
	.word	.LC17
	UNWIND(.fnend)
	.size	Check_Sync_Code, .-Check_Sync_Code
	.align	2
	.global	Read_Frame_Size
	.type	Read_Frame_Size, %function
Read_Frame_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	mov	r1, #16
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	mov	r1, #16
	add	r3, r0, #1
	mov	r0, r6
	str	r3, [r5]
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Read_Frame_Size, .-Read_Frame_Size
	.align	2
	.global	get_free_fb
	.type	get_free_fb, %function
get_free_fb:
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
	ldr	r0, [r1, #80]
	cmp	r0, #0
	beq	.L1680
	add	r3, r1, #80
	mov	r0, #1
.L1681:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1680
	add	r0, r0, #1
	cmp	r0, #9
	bne	.L1681
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1680:
	add	r3, r0, #20
	mov	r2, #1
	str	r2, [r1, r3, asl #2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	get_free_fb, .-get_free_fb
	.align	2
	.global	Setup_Display_Size
	.type	Setup_Display_Size, %function
Setup_Display_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r3, r1
	ldr	lr, [r3, #52]
	mov	r1, #1
	ldr	ip, [r3, #56]
	mov	r2, #0
	mov	r4, r0
	str	r2, [fp, #-28]
	str	lr, [r3, #60]
	str	ip, [r3, #64]
	str	r2, [fp, #-24]
	bl	BsGet
	cmp	r0, #0
	beq	.L1689
	mov	r0, r4
	sub	r2, fp, #24
	sub	r1, fp, #28
	bl	Read_Frame_Size
.L1689:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	Setup_Display_Size, .-Setup_Display_Size
	.align	2
	.global	VP9_Update_CP_Size
	.type	VP9_Update_CP_Size, %function
VP9_Update_CP_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #4096
	movw	r4, #5304
	ldr	r2, [r3, #964]
	ldr	r5, [r3, #1016]
	ldr	lr, [r3, #1020]
	add	r0, r0, r2, lsl #4
	add	r1, r5, #7
	add	r2, lr, #7
	bic	r1, r1, #7
	bic	r2, r2, #7
	add	ip, r0, #4096
	add	r6, r0, r4
	mov	r8, r1, asr #3
	mov	r7, r2, asr #3
	str	r8, [r3, #1056]
	str	r7, [r3, #1060]
	str	r5, [r0, r4]
	str	lr, [r6, #4]
	str	r1, [ip, #1200]
	str	r2, [ip, #1204]
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Update_CP_Size, .-VP9_Update_CP_Size
	.align	2
	.global	Setup_Frame_Size
	.type	Setup_Frame_Size, %function
Setup_Frame_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r1, #4096
	add	r5, r1, #5056
	add	r2, r5, #60
	mov	r6, r1
	ldr	ip, [r4, #1016]
	add	r1, r5, #56
	ldr	r3, [r4, #1020]
	mov	r7, r0
	add	r5, r5, #4
	movw	r8, #5304
	str	ip, [r4, #1036]
	str	r3, [r4, #1040]
	bl	Read_Frame_Size
	ldr	r3, [r4, #964]
	ldr	r9, [r4, #1016]
	mov	r1, r5
	ldr	lr, [r4, #1020]
	mov	r0, r7
	add	r6, r6, r3, lsl #4
	add	r2, r9, #7
	add	r3, lr, #7
	bic	r2, r2, #7
	bic	r3, r3, #7
	add	ip, r6, #4096
	add	r5, r6, r8
	mov	r10, r2, asr #3
	mov	r7, r3, asr #3
	str	r10, [r4, #1056]
	str	r7, [r4, #1060]
	str	r9, [r6, r8]
	str	lr, [r5, #4]
	str	r2, [ip, #1200]
	str	r3, [ip, #1204]
	sub	sp, fp, #44
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	Setup_Display_Size
	UNWIND(.fnend)
	.size	Setup_Frame_Size, .-Setup_Frame_Size
	.align	2
	.global	setup_frame_size_with_refs
	.type	setup_frame_size_with_refs, %function
setup_frame_size_with_refs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r1, #5056
	mov	r8, r1
	add	r7, r7, #4
	mov	r6, r0
	mov	r4, #0
.L1699:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	bne	.L1704
	add	r4, r4, #1
	cmp	r4, #3
	bne	.L1699
	add	r5, r8, #4096
	add	r2, r7, #56
	add	r1, r7, #52
	mov	r0, r6
	ldr	ip, [r5, #1016]
	ldr	r3, [r5, #1020]
	str	ip, [r5, #1036]
	str	r3, [r5, #1040]
	bl	Read_Frame_Size
	ldr	r9, [r5, #1016]
	ldr	r4, [r5, #1020]
.L1698:
	ldr	r3, [r5, #964]
	add	ip, r9, #7
	add	r2, r4, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r1, r7
	add	r3, r8, r3, lsl #4
	movw	r10, #5304
	add	r7, r3, #4096
	add	lr, r3, #5248
	mov	r0, r6
	mov	r8, ip, asr #3
	mov	r6, r2, asr #3
	str	r8, [r5, #1056]
	str	r6, [r5, #1060]
	str	r9, [r3, r10]
	str	r4, [lr, #60]
	str	ip, [r7, #1200]
	str	r2, [r7, #1204]
	sub	sp, fp, #44
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	Setup_Display_Size
.L1704:
	add	r4, r4, #46
	add	r5, r8, #4096
	movw	r1, #5304
	ldr	r3, [r8, r4, asl #2]
	ldr	ip, [r5, #1016]
	ldr	r0, [r5, #1020]
	add	r3, r8, r3, lsl #4
	str	ip, [r5, #1036]
	add	r2, r3, #5248
	str	r0, [r5, #1040]
	ldr	r9, [r3, r1]
	str	r9, [r5, #1016]
	ldr	r4, [r2, #60]
	str	r4, [r5, #1020]
	b	.L1698
	UNWIND(.fnend)
	.size	setup_frame_size_with_refs, .-setup_frame_size_with_refs
	.align	2
	.global	Set_Default_Lf_Deltas
	.type	Set_Default_Lf_Deltas, %function
Set_Default_Lf_Deltas:
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
	mov	r2, #1
	mov	r3, #0
	mvn	r1, #0
	strb	r2, [r0]
	strb	r2, [r0, #1]
	strb	r2, [r0, #2]
	strb	r3, [r0, #3]
	strb	r3, [r0, #6]
	strb	r3, [r0, #7]
	strb	r1, [r0, #4]
	strb	r1, [r0, #5]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Set_Default_Lf_Deltas, .-Set_Default_Lf_Deltas
	.align	2
	.global	VP9_Clearall_Segfeatures
	.type	VP9_Clearall_Segfeatures, %function
VP9_Clearall_Segfeatures:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1707
	mov	r4, r0
	mov	r2, #64
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r3, [r5, #48]
	add	r0, r4, #80
	mov	r2, #32
	mov	r1, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1708:
	.align	2
.L1707:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_Clearall_Segfeatures, .-VP9_Clearall_Segfeatures
	.align	2
	.global	VP9_Setup_Past_Independence
	.type	VP9_Setup_Past_Independence, %function
VP9_Setup_Past_Independence:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1710
	mov	r4, r0
	add	r0, r0, #5248
	mov	r2, #32
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r5, [r5, #48]
	add	r2, r4, #4096
	mov	r3, #0
	mov	ip, #1
	mvn	lr, #0
	strb	r3, [r2, #1091]
	mov	r1, r3
	strb	r3, [r4, #339]
	add	r0, r4, #64
	strb	r3, [r4, #342]
	mov	r2, #16
	strb	r3, [r4, #343]
	mov	r3, r5
	strb	ip, [r4, #336]
	strb	ip, [r4, #337]
	strb	ip, [r4, #338]
	strb	lr, [r4, #340]
	strb	lr, [r4, #341]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1711:
	.align	2
.L1710:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_Setup_Past_Independence, .-VP9_Setup_Past_Independence
	.align	2
	.global	Setup_LoopFilter
	.type	Setup_LoopFilter, %function
Setup_LoopFilter:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r1, #6
	mov	r5, r0
	bl	BsGet
	mov	r1, #3
	str	r0, [r4, #8]
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r1, #1
	strb	r3, [r4, #1]
	str	r0, [r4, #12]
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r6, r4, #2
	add	r7, r4, #6
.L1716:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1730
.L1715:
	add	r6, r6, #1
	cmp	r6, r7
	bne	.L1716
	add	r4, r4, #8
.L1718:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1731
.L1717:
	add	r7, r7, #1
	cmp	r7, r4
	bne	.L1718
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1730:
	ldr	r2, .L1732
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r6]
	b	.L1715
.L1731:
	ldr	r2, .L1732+4
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r7]
	b	.L1717
.L1733:
	.align	2
.L1732:
	.word	.LC18
	.word	.LC19
	UNWIND(.fnend)
	.size	Setup_LoopFilter, .-Setup_LoopFilter
	.align	2
	.global	Read_Delta_Q
	.type	Read_Delta_Q, %function
Read_Delta_Q:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r1, #1
	ldr	r5, [r4]
	mov	r6, r0
	bl	BsGet
	cmp	r0, #0
	beq	.L1735
	mov	r0, r6
	ldr	r2, .L1739
	mov	r1, #4
	bl	VP9_s_v
.L1735:
	str	r0, [r4]
	subs	r0, r0, r5
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1740:
	.align	2
.L1739:
	.word	.LC20
	UNWIND(.fnend)
	.size	Read_Delta_Q, .-Read_Delta_Q
	.align	2
	.global	Setup_Quantization
	.type	Setup_Quantization, %function
Setup_Quantization:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r1, #8
	mov	r5, r0
	bl	BsGet
	add	r1, r4, #244
	str	r0, [r4, #240]
	mov	r0, r5
	bl	Read_Delta_Q
	add	r1, r4, #248
	mov	r0, r5
	bl	Read_Delta_Q
	mov	r0, r5
	add	r1, r4, #252
	bl	Read_Delta_Q
	ldr	r3, [r4, #240]
	cmp	r3, #0
	movne	r3, #0
	bne	.L1742
	ldr	r2, [r4, #244]
	cmp	r2, #0
	bne	.L1742
	ldr	r2, [r4, #248]
	cmp	r2, #0
	ldreq	r3, [r4, #252]
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
.L1742:
	str	r3, [r4, #52]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Setup_Quantization, .-Setup_Quantization
	.align	2
	.global	VP9_Enable_Segfeature
	.type	VP9_Enable_Segfeature, %function
VP9_Enable_Segfeature:
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
	add	r1, r0, r1, lsl #2
	mov	r0, #1
	ldr	r3, [r1, #80]
	orr	r2, r3, r0, asl r2
	str	r2, [r1, #80]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Enable_Segfeature, .-VP9_Enable_Segfeature
	.align	2
	.global	VP9_Seg_Feature_Data_Max
	.type	VP9_Seg_Feature_Data_Max, %function
VP9_Seg_Feature_Data_Max:
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
	ldr	r3, .L1747
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #556]
	ldmfd	sp, {fp, sp, pc}
.L1748:
	.align	2
.L1747:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP9_Seg_Feature_Data_Max, .-VP9_Seg_Feature_Data_Max
	.align	2
	.global	Get_Unsigned_Bits
	.type	Get_Unsigned_Bits, %function
Get_Unsigned_Bits:
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
	cmp	r0, #1
	bls	.L1753
	subs	r3, r0, #1
	beq	.L1754
	mov	r0, #0
.L1752:
	movs	r3, r3, lsr #1
	add	r0, r0, #1
	bne	.L1752
	ldmfd	sp, {fp, sp, pc}
.L1753:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1754:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Get_Unsigned_Bits, .-Get_Unsigned_Bits
	.align	2
	.global	Decode_Unsigned_Max
	.type	Decode_Unsigned_Max, %function
Decode_Unsigned_Max:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #1
	mov	r4, r1
	movls	r1, #0
	bls	.L1757
	subs	r3, r4, #1
	beq	.L1761
	mov	r2, #0
.L1759:
	movs	r3, r3, lsr #1
	add	r2, r2, #1
	bne	.L1759
.L1758:
	mov	r1, r2
.L1757:
	bl	BsGet
	cmp	r0, r4
	movge	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1761:
	mov	r2, r3
	b	.L1758
	UNWIND(.fnend)
	.size	Decode_Unsigned_Max, .-Decode_Unsigned_Max
	.align	2
	.global	VP9_Is_Segfeature_Signed
	.type	VP9_Is_Segfeature_Signed, %function
VP9_Is_Segfeature_Signed:
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
	ldr	r3, .L1764
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #572]
	ldmfd	sp, {fp, sp, pc}
.L1765:
	.align	2
.L1764:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP9_Is_Segfeature_Signed, .-VP9_Is_Segfeature_Signed
	.align	2
	.global	VP9_Set_Segdata
	.type	VP9_Set_Segdata, %function
VP9_Set_Segdata:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r7, .L1775
	mov	r9, r2, asl #2
	mov	r5, r3
	mov	r4, r2
	add	r3, r7, r9
	mov	r6, r0
	mov	r10, r1
	ldr	r8, [r3, #556]
	cmp	r8, r5
	blt	.L1772
.L1767:
	cmp	r5, #0
	blt	.L1773
.L1769:
	add	r4, r4, r10, lsl #2
	add	r4, r6, r4, lsl #1
	strh	r5, [r4, #16]	@ movhi
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1773:
	add	r7, r7, r9
	ldr	r0, [r7, #572]
	cmp	r0, #0
	beq	.L1774
.L1770:
	rsb	r3, r5, #0
	cmp	r8, r3
	bge	.L1769
	movw	r3, #2994
	ldr	r2, .L1775+4
	ldr	r1, .L1775+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1769
.L1772:
	movw	r3, #2982
	add	r2, r7, #588
	ldr	r1, .L1775+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1767
.L1774:
	movw	r3, #2989
	ldr	r2, .L1775+4
	ldr	r1, .L1775+8
	bl	dprint_vfmw
	b	.L1770
.L1776:
	.align	2
.L1775:
	.word	.LANCHOR0
	.word	.LANCHOR0+588
	.word	.LC21
	UNWIND(.fnend)
	.size	VP9_Set_Segdata, .-VP9_Set_Segdata
	.align	2
	.global	Mi_Cols_Aligned_To_Sb
	.type	Mi_Cols_Aligned_To_Sb, %function
Mi_Cols_Aligned_To_Sb:
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
	add	r0, r0, #7
	bic	r0, r0, #7
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mi_Cols_Aligned_To_Sb, .-Mi_Cols_Aligned_To_Sb
	.align	2
	.global	To_Sbs
	.type	To_Sbs, %function
To_Sbs:
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
	add	r0, r0, #7
	mov	r0, r0, asr #3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	To_Sbs, .-To_Sbs
	.align	2
	.global	VP9_Get_Tile_N_Bits
	.type	VP9_Get_Tile_N_Bits, %function
VP9_Get_Tile_N_Bits:
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
	add	r0, r0, #7
	mov	r3, #0
	mov	r0, r0, asr #3
	cmp	r0, #3
	ble	.L1780
.L1781:
	add	r3, r3, #1
	mov	ip, r0, asr r3
	cmp	ip, #3
	bgt	.L1781
	sub	r3, r3, #1
	bic	r3, r3, r3, asr #31
.L1780:
	cmp	r0, #64
	mov	ip, #0
	ble	.L1782
	mov	lr, #64
.L1783:
	add	ip, ip, #1
	cmp	r0, lr, asl ip
	bgt	.L1783
.L1782:
	str	ip, [r1]
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Get_Tile_N_Bits, .-VP9_Get_Tile_N_Bits
	.align	2
	.global	Setup_Tile_Info
	.type	Setup_Tile_Info, %function
Setup_Tile_Info:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r1, #92]
	mov	r6, r1
	mov	r5, r0
	add	r2, r2, #7
	mov	r2, r2, asr #3
	cmp	r2, #3
	ble	.L1789
	mov	r4, #0
	b	.L1790
.L1801:
	mov	r4, r3
.L1790:
	add	r3, r4, #1
	mov	r1, r2, asr r3
	cmp	r1, #3
	bgt	.L1801
	cmp	r2, #64
	bic	r4, r4, r4, asr #31
	ble	.L1812
.L1799:
	mov	r3, #0
	mov	r1, #64
.L1792:
	add	r3, r3, #1
	cmp	r2, r1, asl r3
	bgt	.L1792
.L1791:
	subs	r4, r4, r3
	str	r3, [r6, #100]
	bne	.L1795
	b	.L1794
.L1797:
	ldr	r3, [r6, #100]
	subs	r4, r4, #1
	add	r3, r3, #1
	str	r3, [r6, #100]
	beq	.L1794
.L1795:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1797
.L1794:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r6, #104]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	ldr	r3, [r6, #104]
	add	r0, r3, r0
	str	r0, [r6, #104]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1789:
	cmp	r2, #64
	movgt	r4, #0
	bgt	.L1799
	mov	r3, #0
	str	r3, [r6, #100]
	b	.L1794
.L1812:
	mov	r3, #0
	b	.L1791
	UNWIND(.fnend)
	.size	Setup_Tile_Info, .-Setup_Tile_Info
	.align	2
	.global	Setup_Segmentation
	.type	Setup_Segmentation, %function
Setup_Segmentation:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r5, r1
	mov	r3, #0
	mov	r1, #1
	strb	r3, [r5, #1]
	mov	r6, r0
	strb	r3, [r5, #2]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	bne	.L1850
.L1814:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1850:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L1817
	add	r4, r5, #4
	add	r7, r5, #11
	b	.L1819
.L1818:
	strb	r3, [r4, #1]!
	cmp	r4, r7
	beq	.L1851
.L1819:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	beq	.L1818
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #1]!
	cmp	r4, r7
	bne	.L1819
.L1851:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #4]
	cmp	r0, #0
	addne	r4, r5, #14
	bne	.L1822
	mvn	r3, #0
	strb	r3, [r5, #12]
	strb	r3, [r5, #13]
	strb	r3, [r5, #14]
.L1817:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #2]
	cmp	r0, #0
	beq	.L1814
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	add	r8, r5, #80
	mov	r7, #0
	ldr	r10, .L1854
	strb	r0, [r5, #3]
	mov	r0, r5
	bl	VP9_Clearall_Segfeatures
.L1824:
	mov	r4, #0
	mov	r9, #1
.L1827:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1852
.L1826:
	mov	r2, r4
	mov	r1, r7
	add	r4, r4, #1
	mov	r0, r5
	bl	VP9_Set_Segdata
	cmp	r4, #4
	bne	.L1827
	add	r7, r7, #1
	add	r8, r8, #4
	cmp	r7, #8
	bne	.L1824
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1852:
	ldr	r3, [r8]
	mov	r0, r6
	ldr	r1, [r10, r4, asl #2]
	orr	r3, r3, r9, asl r4
	str	r3, [r8]
	bl	Decode_Unsigned_Max
	ldr	r2, .L1854+4
	ldr	r2, [r2, r4, asl #2]
	cmp	r2, #0
	mov	r3, r0
	beq	.L1826
	str	r0, [fp, #-48]
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldr	r3, [fp, #-48]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r2, r0, #0
	eor	r3, r3, r2
	add	r3, r3, r0
	b	.L1826
.L1822:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	bne	.L1853
.L1821:
	strb	r3, [r7, #1]!
	cmp	r7, r4
	bne	.L1822
	b	.L1817
.L1853:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	b	.L1821
.L1855:
	.align	2
.L1854:
	.word	.LANCHOR0+556
	.word	.LANCHOR0+572
	UNWIND(.fnend)
	.size	Setup_Segmentation, .-Setup_Segmentation
	.align	2
	.global	read_interp_filter_type
	.type	read_interp_filter_type, %function
read_interp_filter_type:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, .L1860
	mov	r4, r0
	sub	ip, fp, #20
	ldmia	r3, {r0, r1, r2, r3}
	stmdb	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r0, #4
	beq	.L1859
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1859:
	mov	r0, r4
	mov	r1, #2
	bl	BsGet
	sub	r3, fp, #20
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #-16]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1861:
	.align	2
.L1860:
	.word	.LANCHOR0+604
	UNWIND(.fnend)
	.size	read_interp_filter_type, .-read_interp_filter_type
	.align	2
	.global	setup_inter_inter
	.type	setup_inter_inter, %function
setup_inter_inter:
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
	ldr	r3, [r0, #68]
	ldr	r1, [r0, #76]
	ldr	r2, [r0, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r0, #60]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	setup_inter_inter, .-setup_inter_inter
	.align	2
	.global	ref_cnt_fb
	.type	ref_cnt_fb, %function
ref_cnt_fb:
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
	ldr	ip, [r1]
	ldr	r3, [r0, ip, asl #2]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, ip, asl #2]
	str	r2, [r1]
	ldr	r3, [r0, r2, asl #2]
	add	r3, r3, #1
	str	r3, [r0, r2, asl #2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ref_cnt_fb, .-ref_cnt_fb
	.global	__aeabi_idiv
	.align	2
	.global	VP9_get_fixed_point_scale_factor
	.type	VP9_get_fixed_point_scale_factor, %function
VP9_get_fixed_point_scale_factor:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r1, #0
	beq	.L1868
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
.L1867:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1868:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3187
	ldr	r2, .L1869
	ldr	r1, .L1869+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1867
.L1870:
	.align	2
.L1869:
	.word	.LANCHOR0+620
	.word	.LC22
	UNWIND(.fnend)
	.size	VP9_get_fixed_point_scale_factor, .-VP9_get_fixed_point_scale_factor
	.align	2
	.global	check_scale_factors
	.type	check_scale_factors, %function
check_scale_factors:
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
	cmp	r0, r2, asl #1
	bgt	.L1875
	cmp	r1, r3, asl #1
	bgt	.L1875
	cmp	r2, r0, asl #4
	bgt	.L1875
	cmp	r3, r1, asl #4
	movle	r0, #1
	movgt	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1875:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	check_scale_factors, .-check_scale_factors
	.align	2
	.global	VP9_scaled_val
	.type	VP9_scaled_val, %function
VP9_scaled_val:
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
	smull	r2, r3, r0, r1
	mov	r0, r2, lsr #14
	orr	r0, r0, r3, asl #18
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_scaled_val, .-VP9_scaled_val
	.align	2
	.global	vp9_setup_scale_factors
	.type	vp9_setup_scale_factors, %function
vp9_setup_scale_factors:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, r3, asl #1
	mov	ip, r1
	mov	r4, r0
	mov	r7, r2
	ldr	r6, [fp, #4]
	bgt	.L1878
	cmp	r2, r6, asl #1
	ble	.L1888
.L1878:
	mvn	r2, #0
	mov	r3, #16
	str	r2, [r4]
	stmib	r4, {r2, r3}
	str	r3, [r4, #12]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1888:
	cmp	r3, r1, asl #4
	bgt	.L1878
	cmp	r6, r2, asl #4
	bgt	.L1878
	cmp	r3, #0
	beq	.L1889
	mov	r1, r3
	mov	r0, ip, asl #14
	bl	__aeabi_idiv
	cmp	r6, #0
	mov	r5, r0
	str	r5, [r4]
	beq	.L1890
.L1881:
	mov	r1, r6
	mov	r0, r7, asl #14
	bl	__aeabi_idiv
	mov	r7, r0, asr #31
	ubfx	r3, r0, #10, #18
	mov	r1, r7, asl #4
	orr	r1, r1, r0, lsr #28
	orr	r1, r3, r1, asl #18
.L1882:
	mov	r7, r5, asr #31
	ubfx	r3, r5, #10, #18
	str	r0, [r4, #4]
	mov	r2, r7, asl #4
	str	r1, [r4, #12]
	orr	r2, r2, r5, lsr #28
	orr	r3, r3, r2, asl #18
	str	r3, [r4, #8]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1889:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3187
	ldr	r2, .L1891
	ldr	r1, .L1891+4
	mvn	r5, #0
	bl	dprint_vfmw
	cmp	r6, #0
	str	r5, [r4]
	bne	.L1881
.L1890:
	ldr	r1, .L1891+4
	movw	r3, #3187
	str	r6, [sp]
	mov	r0, #1
	ldr	r2, .L1891
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r1
	ldr	r5, [r4]
	b	.L1882
.L1892:
	.align	2
.L1891:
	.word	.LANCHOR0+620
	.word	.LC22
	UNWIND(.fnend)
	.size	vp9_setup_scale_factors, .-vp9_setup_scale_factors
	.align	2
	.global	Vp9_Vfmw_ReadProfile
	.type	Vp9_Vfmw_ReadProfile, %function
Vp9_Vfmw_ReadProfile:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #1
	mov	r5, r0
	bl	BsGet
	mov	r1, #1
	mov	r4, r0
	mov	r0, r5
	bl	BsGet
	orr	r4, r4, r0, asl #1
	cmp	r4, #2
	ble	.L1894
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	add	r4, r0, r4
.L1894:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_ReadProfile, .-Vp9_Vfmw_ReadProfile
	.align	2
	.global	Vp9_ReadBitDepthColorSpaceSampling
	.type	Vp9_ReadBitDepthColorSpaceSampling, %function
Vp9_ReadBitDepthColorSpaceSampling:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r1, #4096
	mov	r2, #8
	mov	r5, r0
	ldr	r3, [r4, #976]
	str	r2, [r4, #1032]
	cmp	r3, #1
	bls	.L1896
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r3, #12
	moveq	r3, #10
	str	r3, [r4, #1032]
.L1896:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	cmp	r0, #7
	str	r0, [r4, #980]
	beq	.L1898
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #976]
	bic	r6, r6, #2
	cmp	r6, #1
	movne	r3, #1
	str	r0, [r4, #984]
	strne	r3, [r4, #1012]
	strne	r3, [r4, #1008]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1008]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1012]
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1898:
	ldr	r1, [r4, #976]
	bic	r1, r1, #2
	cmp	r1, #1
	beq	.L1904
	movw	r3, #3290
	ldr	r2, .L1905
	ldr	r1, .L1905+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1904:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #1012]
	str	r3, [r4, #1008]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1906:
	.align	2
.L1905:
	.word	.LANCHOR0+656
	.word	.LC23
	UNWIND(.fnend)
	.size	Vp9_ReadBitDepthColorSpaceSampling, .-Vp9_ReadBitDepthColorSpaceSampling
	.align	2
	.global	Vp9_ReadCompressedHeader
	.type	Vp9_ReadCompressedHeader, %function
Vp9_ReadCompressedHeader:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 8
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
	ldr	lr, [fp, #16]
	mov	r4, #0
	mov	r7, r1
	cmp	lr, #0
	mov	r6, r2
	mov	r8, r3
	mov	r5, r0
	str	r4, [fp, #-48]
	ldr	r10, [fp, #8]
	ldr	r9, [fp, #12]
	beq	.L1912
.L1908:
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	Vp9_ReadCoefProbs
	ldr	r2, [fp, #4]
	mov	r0, r7
	mov	r3, r8
	sub	ip, fp, #48
	stmib	sp, {r9, r10}
	str	r2, [sp]
	mov	r1, r5
	mov	r2, r6
	str	ip, [sp, #12]
	bl	Vp9_PrepareReadModeInfo
	ldr	r3, [r5, #32]
	sub	r3, r3, #33
	cmn	r3, #-1073741790
	ldrhi	r3, [fp, #-48]
	movhi	r0, #0
	ldrhi	r2, [fp, #20]
	mvnls	r0, #0
	strhi	r3, [r2]
	ldrhi	r3, [fp, #24]
	strhi	r4, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1912:
	bl	Vp9_ReadTxMode
	cmp	r0, #4
	mov	r4, r0
	bne	.L1908
	add	r0, r7, #4352
	mov	r1, r5
	add	r0, r0, #51
	bl	Vp9_ReadTxProbs
	b	.L1908
	UNWIND(.fnend)
	.size	Vp9_ReadCompressedHeader, .-Vp9_ReadCompressedHeader
	.align	2
	.global	Read_UnCompressed_Header
	.type	Read_UnCompressed_Header, %function
Read_UnCompressed_Header:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r4, r1, #4096
	mov	r6, r1
	mov	r1, #2
	ldr	r3, [r4, #972]
	mov	r5, r0
	str	r3, [r4, #968]
	bl	BsGet
	cmp	r0, #2
	beq	.L1914
	ldr	r1, .L1948
	mov	r0, #1
	bl	dprint_vfmw
.L1914:
	mov	r0, r5
	bl	Vp9_Vfmw_ReadProfile
	mov	r1, #1
	str	r0, [r4, #976]
	mov	r0, r5
	bl	BsGet
	subs	r7, r0, #0
	bne	.L1944
	mov	r1, #1
	str	r7, [r4, #992]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #972]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #988]
	mov	r0, r5
	bl	BsGet
	ldr	r2, [r4, #972]
	cmp	r2, #0
	mov	r3, r0
	str	r0, [r4, #1004]
	beq	.L1945
	ldr	r2, [r4, #988]
	cmp	r2, #0
	strne	r7, [r4, #1072]
	beq	.L1946
.L1920:
	cmp	r3, #0
	beq	.L1921
	mov	r3, #0
	str	r3, [r4, #1076]
.L1922:
	ldr	r3, [r4, #1072]
	cmp	r3, #0
	beq	.L1923
	mov	r0, r5
	bl	Check_Sync_Code
	ldr	r3, [r4, #976]
	cmp	r3, #1
	bls	.L1924
	mov	r1, r6
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1925:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1080]
	mov	r0, r5
	bl	Setup_Frame_Size
	b	.L1918
.L1944:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r7, r3
	mov	r2, #1
	add	r0, r0, #38
	ldr	r1, [r6, r0, asl #2]
	str	r3, [r4, #1080]
	str	r2, [r4, #992]
	str	r1, [r4, #996]
	str	r3, [r6, #344]
	str	r2, [r4, #988]
.L1916:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1923:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r8, r6, #180
	add	r9, r6, #192
	mov	r10, r8
	str	r0, [r4, #1080]
.L1926:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	add	r3, r0, #38
	mov	r0, r5
	ldr	r3, [r6, r3, asl #2]
	str	r3, [r10, #4]!
	bl	BsGet
	cmp	r10, r9
	str	r0, [r10, #-116]
	bne	.L1926
	mov	r1, r6
	mov	r0, r5
	bl	setup_frame_size_with_refs
	ldr	r2, [r4, #1016]
	sub	r3, r2, #1
	cmp	r3, #4096
	ldr	r3, [r4, #1020]
	bcs	.L1928
	sub	r1, r3, #1
	cmp	r1, #4096
	bcs	.L1928
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	add	r10, r6, #5440
	str	r0, [r6, #56]
	mov	r0, r5
	bl	read_interp_filter_type
	str	r0, [r4, #1084]
.L1930:
	ldr	r2, [r8, #4]!
	mov	r0, r10
	ldr	ip, [r4, #1020]
	add	r10, r10, #16
	add	r2, r2, #328
	ldr	r3, [r4, #1016]
	add	r2, r2, #3
	str	ip, [sp]
	add	r1, r6, r2, lsl #4
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #8]
	bl	vp9_setup_scale_factors
	cmp	r9, r8
	bne	.L1930
	ldr	r3, [r6, #68]
	ldr	r1, [r6, #76]
	ldr	r2, [r6, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r6, #60]
	b	.L1918
.L1945:
	mov	r0, r5
	bl	Check_Sync_Code
	mov	r1, r6
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
	ldr	r3, [r4, #964]
	mov	r2, #255
	mov	r1, r6
	str	r2, [r4, #1080]
	mov	r0, r5
	str	r3, [r6, #184]
	str	r3, [r6, #188]
	str	r3, [r6, #192]
	bl	Setup_Frame_Size
.L1918:
	ldr	r3, [r4, #1004]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #1044]
	strne	r3, [r4, #1048]
	beq	.L1947
.L1932:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #972]
	cmp	r3, #0
	str	r0, [r4, #1052]
	beq	.L1933
	ldr	r3, [r4, #1004]
	cmp	r3, #0
	bne	.L1933
	ldr	r3, [r4, #1072]
	cmp	r3, #0
	bne	.L1933
.L1935:
	ldr	r3, [r6, #68]
	ldr	r1, [r6, #76]
	ldr	r2, [r6, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r6, #60]
.L1934:
	add	r1, r6, #336
	mov	r0, r5
	bl	Setup_LoopFilter
	mov	r1, r6
	mov	r0, r5
	bl	Setup_Quantization
	add	r1, r6, #5184
	mov	r0, r5
	bl	Setup_Segmentation
	add	r1, r6, #5056
	mov	r0, r5
	add	r1, r1, #4
	bl	Setup_Tile_Info
	mov	r0, r5
	mov	r1, #16
	bl	BsGet
	str	r0, [r6, #8]
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1924:
	mov	r3, #1
	mov	r2, #8
	str	r3, [r4, #1008]
	str	r2, [r4, #1032]
	str	r3, [r4, #1012]
	str	r3, [r4, #980]
	b	.L1925
.L1933:
	mov	r0, r6
	bl	VP9_Setup_Past_Independence
	ldr	r3, [r4, #972]
	cmp	r3, #0
	beq	.L1934
	b	.L1935
.L1947:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #1044]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1048]
	b	.L1932
.L1921:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1076]
	b	.L1922
.L1946:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1004]
	str	r0, [r4, #1072]
	b	.L1920
.L1928:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #3443
	ldr	r2, .L1948+4
	mvn	r7, #0
	ldr	r1, .L1948+8
	bl	dprint_vfmw
	b	.L1916
.L1949:
	.align	2
.L1948:
	.word	.LC24
	.word	.LANCHOR0+692
	.word	.LC25
	UNWIND(.fnend)
	.size	Read_UnCompressed_Header, .-Read_UnCompressed_Header
	.align	2
	.global	swap_frame_buffers
	.type	swap_frame_buffers, %function
swap_frame_buffers:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	ldr	r3, [r5, #1080]
	cmp	r3, #0
	addne	r2, r0, #152
	addne	lr, r0, #80
	beq	.L1955
.L1954:
	tst	r3, #1
	beq	.L1952
	ldr	r4, [r2]
	ldr	ip, [r5, #964]
	ldr	r1, [lr, r4, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [lr, r4, asl #2]
	str	ip, [r2]
	ldr	r1, [lr, ip, asl #2]
	add	r1, r1, #1
	str	r1, [lr, ip, asl #2]
.L1952:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1954
.L1955:
	ldr	r3, [r5, #964]
	mvn	r2, #-2147483648
	add	r3, r0, r3, lsl #2
	ldr	r1, [r3, #80]
	sub	r1, r1, #1
	str	r1, [r3, #80]
	str	r2, [r0, #184]
	str	r2, [r0, #188]
	str	r2, [r0, #192]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	swap_frame_buffers, .-swap_frame_buffers
	.align	2
	.global	VP9_Set_DecParam
	.type	VP9_Set_DecParam, %function
VP9_Set_DecParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r0, #274432
	mov	r5, r0
	add	r4, r0, #270336
	ldr	r6, [r7, #3620]
	cmp	r6, #1
	beq	.L1996
	add	r8, r0, #262144
	mov	r3, #0
	strb	r3, [r8, #1036]
	ldr	r2, [r7, #3600]
	ldr	ip, [r4, #2624]
	ldr	r0, [r4, #2640]
	ldr	r1, [r4, #2644]
	ldr	r3, [r4, #2556]
	str	ip, [r4, #2124]
	str	r0, [r4, #2096]
	bic	r3, r3, #15
	str	r1, [r4, #2100]
	str	r2, [r4, #2620]
	str	r2, [r4, #2120]
	str	r3, [r4, #2136]
	ldr	r3, [r5]
	ldr	r1, [r4, #2820]
	ldr	ip, [r4, #2580]
	ldr	lr, [r3, #592]
	cmp	r1, #8
	ldr	r0, [r4, #2592]
	addgt	r6, r5, #311296
	addle	r1, r4, r1, lsl #2
	addle	r6, r5, #311296
	str	lr, [r4, #2476]
	ldr	lr, [r3, #596]
	str	lr, [r4, #2480]
	ldr	lr, [r3, #600]
	str	lr, [r4, #2488]
	ldr	lr, [r3, #604]
	str	lr, [r4, #2492]
	ldr	r3, [r3, #644]
	str	ip, [r4, #2468]
	str	r0, [r4, #2472]
	str	r3, [r4, #2496]
	ldrgt	r3, [r6, #2760]
	ldrle	r3, [r1, #2824]
	addgt	r3, r4, r3, lsl #2
	ldrgt	r3, [r3, #2824]
	str	r3, [r4, #2604]
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	ldrgt	r3, [r6, #2760]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2600]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	ldrgt	r3, [r6, #2760]
	cmp	r2, #0
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2608]
	bne	.L1997
.L1974:
	ldr	r1, [r4, #2612]
	str	r1, [r4, #2604]
	str	r1, [r4, #2600]
	str	r1, [r4, #2608]
.L1975:
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2604]
	mov	r7, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2600]
	mov	r10, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2608]
	mov	r9, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	cmp	r9, #0
	cmpne	r7, #0
	beq	.L1976
	cmp	r0, #0
	cmpne	r10, #0
	beq	.L1976
	ldr	r2, [r7, #28]
	cmp	r2, #0
	beq	.L1998
	ldr	r2, [r7, #8]
	str	r2, [r4, #2464]
	ldr	r2, [r7, #28]
	ldr	r2, [r2, #20]
	str	r2, [r4, #2504]
	ldr	r2, [r7, #28]
	ldr	r2, [r2, #8]
	str	r2, [r4, #2448]
	ldr	r2, [r10, #28]
	cmp	r2, #0
	ldreq	r2, [r7, #28]
	ldr	r2, [r2, #8]
	str	r2, [r4, #2452]
	ldr	r2, [r9, #28]
	cmp	r2, #0
	ldreq	r2, [r7, #28]
	ldr	r2, [r2, #8]
	str	r2, [r4, #2456]
	add	r2, r5, #8
	ldr	r3, [r0, #28]
	mov	r0, #0
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2460]
	ldr	r3, [r6, #2868]
	str	r3, [r6, #2864]
	str	r3, [r8, #1032]
	str	r2, [r5, #4]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1997:
	ldr	r3, [r7, #3700]
	cmp	r3, #1
	beq	.L1974
	ldr	r1, [r4, #2612]
	b	.L1975
.L1996:
	add	r3, r0, #262144
	add	r8, r0, #311296
	strb	r6, [r3, #1036]
	ldr	r3, [r0]
	ldr	r1, [r4, #2612]
	ldr	r2, [r3, #592]
	str	r2, [r4, #2476]
	ldr	r3, [r3, #644]
	str	r3, [r4, #2496]
	ldr	r0, [r8, #2860]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #3624]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r9, r0
	ldr	r0, [r8, #2860]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #3624]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r10, r0
	ldr	r0, [r8, #2860]
	bl	FSP_GetFsImagePtr
	cmp	r9, #0
	cmpne	r10, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r2, r0
	cmp	r3, #0
	bne	.L1976
	ldr	r3, [r9, #28]
	cmp	r3, #0
	beq	.L1999
	ldr	r3, [r3, #8]
	mov	r1, #0
	mov	r0, r1
	str	r3, [r4, #2448]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	ldreq	r3, [r9, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2456]
	ldr	r3, [r9, #28]
	ldr	r3, [r3, #20]
	str	r3, [r4, #2504]
	ldr	r3, [r2, #68]
	add	r3, r3, #63
	mov	r3, r3, lsr #6
	str	r3, [r4, #2096]
	ldr	r3, [r2, #72]
	add	r3, r3, #63
	mov	r3, r3, lsr #6
	str	r3, [r4, #2100]
	str	r1, [r5, #4]
	ldr	r3, [r2, #68]
	str	r3, [r4, #2648]
	ldr	r3, [r2, #72]
	str	r3, [r4, #2652]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1976:
	ldr	r1, .L2000
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1998:
	ldr	r1, .L2000+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1999:
	mov	r0, r6
	ldr	r1, .L2000+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2001:
	.align	2
.L2000:
	.word	.LC26
	.word	.LC28
	.word	.LC27
	UNWIND(.fnend)
	.size	VP9_Set_DecParam, .-VP9_Set_DecParam
	.align	2
	.global	VP9_ArrangeVHBMem
	.type	VP9_ArrangeVHBMem, %function
VP9_ArrangeVHBMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r4, r0, #270336
	mov	r5, r0
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	cmp	r3, #31
	bls	.L2004
	sub	r0, r2, #32
	movw	r1, #8160
	cmp	r3, #8192
	cmpls	r0, r1
	bls	.L2005
.L2004:
	ldr	r1, .L2031
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L2006:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2005:
	ldr	r1, .L2031+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r5]
	ldr	r3, [r1, #724]
	cmp	r3, #0
	bne	.L2007
	ldr	r2, [r1, #28]
	cmp	r2, #25
	beq	.L2028
.L2020:
	mov	r7, #5
.L2008:
	ldr	r3, [r4, #2568]
	add	r6, r5, #311296
	cmp	r3, #0
	bne	.L2013
	ldr	lr, [r6, #2860]
	mov	r1, r3
	ldr	ip, .L2031+8
	mov	r2, #20
	ldr	r8, .L2031+12
	sub	r0, fp, #56
	ldr	ip, [ip, lr, asl #2]
	ldr	r8, [r8, #48]
	add	ip, ip, #471040
	str	r3, [ip, #888]
	blx	r8
	ldr	ip, [r4, #2648]
	ldr	r2, [r4, #2652]
	sub	r1, fp, #56
	ldr	r0, [r6, #2860]
	mov	r3, #1
	strb	r7, [fp, #-54]
	str	ip, [fp, #-52]
	str	ip, [fp, #-44]
	str	r2, [fp, #-48]
	str	r2, [fp, #-40]
	strb	r3, [fp, #-55]
	strb	r3, [fp, #-53]
	bl	FSP_ConfigInstance
	subs	r7, r0, #0
	beq	.L2029
.L2014:
	ldr	r1, .L2031+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2006
.L2007:
	ldr	r3, [r1, #28]
	cmp	r3, #25
	bne	.L2020
	ldr	r2, [r4, #2648]
	ldr	ip, [r1, #684]
	cmp	r2, ip
	bhi	.L2011
	ldr	r0, [r4, #2652]
	ldr	r3, [r1, #688]
	cmp	r0, r3
	bls	.L2012
.L2011:
	ldr	lr, [r1, #688]
	mov	r0, #0
	ldr	r3, [r4, #2652]
	ldr	r1, .L2031+20
	str	ip, [sp]
	str	lr, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2006
.L2013:
	ldr	r3, [r6, #2860]
	mov	r7, #1
	ldr	r8, .L2031+8
	mov	r1, #0
	ldr	r2, .L2031+12
	sub	r0, fp, #56
	ldr	r9, [r6, #2732]
	ldr	r3, [r8, r3, asl #2]
	ldr	ip, [r2, #48]
	mov	r2, #20
	add	r3, r3, #471040
	str	r7, [r3, #888]
	blx	ip
	ldr	r1, [r5]
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #2860]
	cmp	r1, #24
	sub	r1, fp, #56
	uxtbne	r7, r9
	str	r3, [fp, #-48]
	str	r3, [fp, #-40]
	mov	r3, #0
	str	r2, [fp, #-52]
	str	r2, [fp, #-44]
	strb	r7, [fp, #-55]
	strb	r3, [fp, #-54]
	strb	r3, [fp, #-53]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L2014
	ldr	r1, [r5]
	sub	r3, fp, #60
	ldr	r0, [r6, #2860]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	bne	.L2030
.L2017:
	ldr	r3, [r6, #2860]
	mov	r2, #0
	ldr	r3, [r8, r3, asl #2]
	str	r2, [r3, #1432]
.L2015:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #2568]
	b	.L2006
.L2028:
	ldr	r2, [r4, #2648]
	ldr	ip, [r1, #684]
	cmp	r2, ip
	bhi	.L2011
	ldr	lr, [r4, #2652]
	ldr	r0, [r1, #688]
	cmp	lr, r0
	bhi	.L2011
	ldr	r2, [r4, #2568]
	cmp	r2, #1
	moveq	r0, r3
	beq	.L2006
.L2012:
	ldr	r7, [r1, #732]
	b	.L2008
.L2029:
	ldr	r1, [r5]
	sub	r3, fp, #60
	ldr	r0, [r6, #2860]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	beq	.L2015
	mov	r0, r7
	ldr	r1, .L2031+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2006
.L2030:
	ldr	r1, .L2031+28
	mov	r0, #2
	bl	dprint_vfmw
	b	.L2017
.L2032:
	.align	2
.L2031:
	.word	.LC29
	.word	.LC30
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC31
	.word	.LC32
	.word	.LC34
	UNWIND(.fnend)
	.size	VP9_ArrangeVHBMem, .-VP9_ArrangeVHBMem
	.align	2
	.global	VP9_GetRefNum
	.type	VP9_GetRefNum, %function
VP9_GetRefNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r8, .L2052
	movw	r6, #10820
	sub	r4, fp, #72
	add	r7, r0, #274432
	movt	r6, 4
	add	r6, r0, r6
	ldr	r3, [r8, #52]
	add	r1, r6, #80
	mov	r2, #36
	mov	r0, r4
	ldr	r5, [r7, #3592]
	blx	r3
	ldr	r3, [r8, #52]
	add	r1, r6, #152
	sub	r0, fp, #104
	mov	r2, #32
	blx	r3
	ldr	r3, [r7, #3620]
	cmp	r3, #1
	beq	.L2051
.L2034:
	ldr	r3, [r7, #3708]
	mov	lr, r5, asl #2
	cmp	r3, #0
	subne	r2, fp, #104
	addne	r0, r4, lr
	beq	.L2041
.L2040:
	tst	r3, #1
	beq	.L2038
	ldr	ip, [r2]
	str	r5, [r2]
	ldr	r1, [r4, ip, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [r4, ip, asl #2]
	ldr	r1, [r0]
	add	r1, r1, #1
	str	r1, [r0]
.L2038:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L2040
.L2041:
	sub	r3, fp, #36
	sub	r1, fp, #40
	add	r2, r3, lr
	sub	r3, fp, #76
	mov	r0, #0
	ldr	ip, [r2, #-36]
	sub	ip, ip, #1
	str	ip, [r2, #-36]
.L2037:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	addne	r0, r0, #1
	cmp	r3, r1
	bne	.L2037
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2051:
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [r7, #3624]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r4, r5, asl #2]
	ldr	r3, [r4, r2, asl #2]
	mov	r5, r2
	add	r3, r3, #1
	str	r3, [r4, r2, asl #2]
	b	.L2034
.L2053:
	.align	2
.L2052:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_GetRefNum, .-VP9_GetRefNum
	.align	2
	.global	Vp9_DefaultCoefProbs
	.type	Vp9_DefaultCoefProbs, %function
Vp9_DefaultCoefProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L2055
	mov	r2, #1024
	ldr	r4, .L2055+4
	mov	r6, r0
	ldr	r3, [r5, #52]
	mov	r1, r4
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #1024
	add	r0, r6, #1024
	mov	r2, #1024
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #2048
	add	r0, r6, #2048
	mov	r2, #1024
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #3072
	add	r0, r6, #3072
	mov	r2, #1024
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2056:
	.align	2
.L2055:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	Vp9_DefaultCoefProbs, .-Vp9_DefaultCoefProbs
	.align	2
	.global	Vp9_InitMbmodeProbs
	.type	Vp9_InitMbmodeProbs, %function
Vp9_InitMbmodeProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L2058
	mov	r6, r0
	ldr	r5, .L2058+4
	add	r7, r6, #4096
	mov	r2, #160
	add	r0, r0, #4160
	sub	r1, r5, #4080
	ldr	r3, [r4, #52]
	sub	r1, r1, #8
	sub	r8, r5, #3856
	blx	r3
	sub	r1, r5, #3920
	ldr	r3, [r4, #52]
	mov	r0, r7
	sub	r1, r1, #8
	mov	r2, #64
	blx	r3
	add	r0, r6, #4416
	sub	r1, r8, #8
	ldr	r3, [r4, #52]
	mov	r2, #8
	add	r0, r0, #44
	blx	r3
	add	r0, r6, #4608
	mov	r1, r8
	ldr	r3, [r4, #52]
	mov	r2, #96
	add	r0, r0, #4
	blx	r3
	add	r0, r6, #4352
	ldr	r3, [r4, #52]
	sub	r1, r5, #3760
	mov	r2, #4
	add	r0, r0, #63
	blx	r3
	sub	r8, r5, #3744
	add	r0, r6, #4416
	sub	r1, r8, #12
	ldr	r3, [r4, #52]
	mov	r2, #5
	add	r0, r0, #3
	sub	r5, r5, #3728
	blx	r3
	add	r0, r6, #4416
	sub	r1, r8, #4
	ldr	r3, [r4, #52]
	mov	r2, #5
	add	r0, r0, #8
	blx	r3
	add	r0, r6, #4416
	ldr	r3, [r4, #52]
	sub	r1, r5, #12
	mov	r2, #10
	add	r0, r0, #13
	blx	r3
	add	r0, r7, #304
	mov	r2, #12
	ldr	r1, .L2058+8
	add	r0, r0, #3
	bl	memcpy
	add	r0, r6, #4352
	mov	r1, r5
	add	r0, r0, #48
	ldr	r3, [r4, #52]
	mov	r2, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L2059:
	.align	2
.L2058:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2
	.word	.LANCHOR0+720
	UNWIND(.fnend)
	.size	Vp9_InitMbmodeProbs, .-Vp9_InitMbmodeProbs
	.align	2
	.global	Vp9_InitMvProbs
	.type	Vp9_InitMvProbs, %function
Vp9_InitMvProbs:
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
	add	r0, r0, #4416
	mov	r2, #69
	ldr	r1, .L2061
	add	r0, r0, #52
	bl	memcpy
	ldmfd	sp, {fp, sp, pc}
.L2062:
	.align	2
.L2061:
	.word	.LANCHOR0+732
	UNWIND(.fnend)
	.size	Vp9_InitMvProbs, .-Vp9_InitMvProbs
	.align	2
	.global	Vp9_SetupPastIndependence
	.type	Vp9_SetupPastIndependence, %function
Vp9_SetupPastIndependence:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r4, r3
	mov	r6, r1
	mov	r7, r2
	ldr	r9, [fp, #4]
	ldr	r8, [fp, #8]
	bl	Vp9_DefaultCoefProbs
	mov	r0, r5
	bl	Vp9_InitMbmodeProbs
	add	r0, r5, #4416
	mov	r2, #69
	ldr	r1, .L2071
	add	r0, r0, #52
	bl	memcpy
	ldr	r3, .L2071+4
	add	r0, r5, #4416
	mov	r2, #21
	add	r0, r0, #23
	ldr	r1, .L2071+8
	ldr	r3, [r3, #52]
	blx	r3
	sub	lr, r4, #3
	clz	lr, lr
	mov	lr, lr, lsr #5
	cmp	r9, #0
	moveq	ip, lr
	orrne	ip, lr, #1
	cmp	r8, #0
	orreq	ip, ip, #1
	cmp	ip, #0
	bne	.L2069
	cmp	r4, #2
	beq	.L2070
.L2066:
	mov	r3, #0
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2069:
	mov	r4, #0
	movw	r8, #18832
.L2065:
	add	r0, r6, r4
	add	r4, r4, #4672
	add	r4, r4, #36
	movw	r2, #4708
	mov	r1, r5
	bl	memcpy
	cmp	r4, r8
	bne	.L2065
	b	.L2066
.L2070:
	ldr	r0, [r7]
	movw	r2, #4708
	mov	r1, r5
	mla	r0, r2, r0, r6
	bl	memcpy
	b	.L2066
.L2072:
	.align	2
.L2071:
	.word	.LANCHOR0+732
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2-3724
	UNWIND(.fnend)
	.size	Vp9_SetupPastIndependence, .-Vp9_SetupPastIndependence
	.align	2
	.global	Vp9_Vfmw_SegfeatureActive
	.type	Vp9_Vfmw_SegfeatureActive, %function
Vp9_Vfmw_SegfeatureActive:
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
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2075
	add	r1, r1, #20
	mov	ip, #1
	ldr	r3, [r0, r1, asl #2]
	ands	r3, r3, ip, asl r2
	movne	r0, ip
	moveq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2075:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_SegfeatureActive, .-Vp9_Vfmw_SegfeatureActive
	.align	2
	.global	Vp9_Vfmw_GetSegdata
	.type	Vp9_Vfmw_GetSegdata, %function
Vp9_Vfmw_GetSegdata:
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
	add	r2, r2, r1, lsl #2
	add	r0, r0, r2, lsl #1
	ldrsh	r0, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_GetSegdata, .-Vp9_Vfmw_GetSegdata
	.align	2
	.global	Vp9_Vfmw_Clamp
	.type	Vp9_Vfmw_Clamp, %function
Vp9_Vfmw_Clamp:
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
	cmp	r0, r1
	movlt	r0, r1
	cmp	r0, r2
	movge	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_Clamp, .-Vp9_Vfmw_Clamp
	.align	2
	.global	Vp9_Vfmw_LoopFilterFrameInit
	.type	Vp9_Vfmw_LoopFilterFrameInit, %function
Vp9_Vfmw_LoopFilterFrameInit:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r7, r2, #80
	mov	r9, r2
	mov	r5, r1
	mov	r6, r0
	mov	r8, r2
	mov	r10, r3
	mov	r4, r3, asr #5
	add	r3, r2, #112
	str	r3, [fp, #-48]
.L2084:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2087
	ldr	r3, [r7]
	tst	r3, #2
	beq	.L2087
	ldrb	r3, [r9, #3]	@ zero_extendqisi2
	ldrsh	r1, [r8, #18]
	cmp	r3, #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	addne	r1, r1, r10
	cmp	r3, #0
	usat	r1, #6, r1
	beq	.L2092
.L2081:
	mov	r0, r5
	add	lr, r5, #5
	ldrsb	r3, [r0, #2]!
	mov	ip, r6
	add	r3, r1, r3, asl r4
	usat	r3, #6, r3
	strb	r3, [r6]
.L2083:
	ldrsb	r3, [r0, #1]!
	add	ip, ip, #2
	ldrsb	r2, [r5, #6]
	cmp	r0, lr
	add	r3, r1, r3, asl r4
	add	r3, r3, r2, asl r4
	usat	r3, #6, r3
	strb	r3, [ip]
	ldrsb	r3, [r0]
	ldrsb	r2, [r5, #7]
	add	r3, r1, r3, asl r4
	add	r3, r3, r2, asl r4
	usat	r3, #6, r3
	strb	r3, [ip, #1]
	bne	.L2083
.L2082:
	ldr	r3, [fp, #-48]
	add	r7, r7, #4
	add	r6, r6, #8
	add	r8, r8, #8
	cmp	r7, r3
	bne	.L2084
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2087:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	cmp	r3, #0
	bne	.L2081
.L2092:
	ldr	r3, .L2093
	mov	r2, #8
	mov	r0, r6
	ldr	r3, [r3, #48]
	blx	r3
	b	.L2082
.L2094:
	.align	2
.L2093:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_Vfmw_LoopFilterFrameInit, .-Vp9_Vfmw_LoopFilterFrameInit
	.align	2
	.global	Vp9_MiColsAlignedToSb
	.type	Vp9_MiColsAlignedToSb, %function
Vp9_MiColsAlignedToSb:
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
	add	r0, r0, #7
	bic	r0, r0, #7
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_MiColsAlignedToSb, .-Vp9_MiColsAlignedToSb
	.align	2
	.global	Vp9_ToSbs
	.type	Vp9_ToSbs, %function
Vp9_ToSbs:
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
	add	r0, r0, #7
	mov	r0, r0, asr #3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_ToSbs, .-Vp9_ToSbs
	.align	2
	.global	Vp9_GetTileOffsets
	.type	Vp9_GetTileOffsets, %function
Vp9_GetTileOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, [fp, #4]
	add	ip, lr, #7
	mov	ip, ip, asr #3
	mul	r2, ip, r2
	add	ip, r2, ip
	mov	r2, r2, asr r3
	mov	r3, ip, asr r3
	mov	r2, r2, asl #3
	mov	r3, r3, asl #3
	cmp	r2, lr
	movge	r2, lr
	cmp	r3, lr
	str	r2, [r0]
	movge	r3, lr
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_GetTileOffsets, .-Vp9_GetTileOffsets
	.align	2
	.global	Vp9_GetTileRowOffsets
	.type	Vp9_GetTileRowOffsets, %function
Vp9_GetTileRowOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r1, #7
	ldr	lr, [fp, #4]
	mov	ip, ip, asr #3
	mul	r0, ip, r0
	add	ip, r0, ip
	mov	r0, r0, asr r2
	mov	r2, ip, asr r2
	mov	r0, r0, asl #3
	mov	r2, r2, asl #3
	cmp	r0, r1
	movge	r0, r1
	cmp	r2, r1
	str	r0, [r3]
	movge	r2, r1
	str	r2, [lr]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_GetTileRowOffsets, .-Vp9_GetTileRowOffsets
	.align	2
	.global	Vp9_Vfmw_GetTileColOffsets
	.type	Vp9_Vfmw_GetTileColOffsets, %function
Vp9_Vfmw_GetTileColOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r1, #7
	ldr	lr, [fp, #4]
	mov	ip, ip, asr #3
	mul	r0, ip, r0
	add	ip, r0, ip
	mov	r0, r0, asr r2
	mov	r2, ip, asr r2
	mov	r0, r0, asl #3
	mov	r2, r2, asl #3
	cmp	r0, r1
	movge	r0, r1
	cmp	r2, r1
	str	r0, [r3]
	movge	r2, r1
	str	r2, [lr]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_GetTileColOffsets, .-Vp9_Vfmw_GetTileColOffsets
	.align	2
	.global	Vp9_SetPoolInfoFrame
	.type	Vp9_SetPoolInfoFrame, %function
Vp9_SetPoolInfoFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r4, r0, #270336
	mov	r6, r0
	mov	r5, r1
	ldr	r0, [r4, #2488]
	bl	GetCompressRatio
	str	r0, [fp, #-48]
	ldr	r0, [r4, #2492]
	bl	GetCompressRatio
	ldr	r0, [r4, #2860]
	add	r2, r6, #274432
	add	r1, r6, #311296
	ldr	r3, [r4, #2864]
	and	r0, r0, #7
	mov	r9, r1
	ldr	ip, [r2, #3596]
	str	r1, [fp, #-52]
	and	r3, r3, #3
	ldr	r1, [r2, #3600]
	mov	r0, r0, asl #10
	ldr	r8, [r2, #3660]
	orr	r3, r0, r3, asl #13
	and	ip, ip, #3
	ldr	lr, [r2, #3676]
	ldr	r0, [r2, #3700]
	and	r1, r1, #1
	orr	r1, r3, r1
	ldr	r7, [r2, #3672]
	and	r8, r8, #15
	orr	r3, r1, ip, asl #1
	and	lr, lr, #1
	ldr	r1, [r2, #3640]
	orr	r3, r3, r8, asl #15
	and	r7, r7, #1
	mov	r0, r0, asl #7
	orr	ip, r3, lr, asl #9
	ldr	lr, [r2, #3636]
	orr	ip, ip, r7, asl #8
	ldr	r3, [r2, #3632]
	uxtb	r0, r0
	and	r1, r1, #1
	orr	r0, ip, r0
	and	lr, lr, #1
	ldr	ip, [r2, #3628]
	orr	r1, r0, r1, asl #6
	and	r3, r3, #1
	orr	r1, r1, lr, asl #5
	and	r0, ip, #1
	orr	r3, r1, r3, asl #4
	orr	r3, r3, r0, asl #3
	str	r3, [r5]
	ldr	r1, [r2, #3644]
	ldr	r3, [r9, #2752]
	cmp	r1, r3
	movne	ip, #1048576
	beq	.L2137
.L2101:
	ldr	r3, [r4, #2816]
	mov	r8, #0
	ldr	lr, [r4, #2820]
	ldr	r1, [r4, #2704]
	mov	r3, r3, asl #12
	ldr	r0, [r2, #3712]
	ldr	r10, [r4, #2812]
	and	lr, lr, #15
	uxth	r3, r3
	mov	r1, r1, asl #7
	orr	r7, r3, lr, asl #16
	and	r10, r10, #15
	ldr	r3, [r4, #2700]
	and	lr, r0, #7
	ldr	r9, [r4, #2696]
	orr	r0, r7, lr
	orr	lr, r0, r10, asl #8
	ldr	r7, [r4, #2692]
	uxtb	r0, r1
	and	r3, r3, #1
	orr	r0, lr, r0
	and	r9, r9, #1
	ldr	lr, [r4, #2684]
	orr	r0, r0, r3, asl #6
	and	r7, r7, #1
	orr	r1, r0, r9, asl #5
	and	r3, lr, #1
	orr	r1, r1, r7, asl #4
	orr	r3, r1, r3, asl #3
	orr	r3, r3, ip
	str	r3, [r5, #4]
	ldr	r1, [r2, #3648]
	ldr	r3, [r2, #3644]
	add	r1, r1, #7
	add	r3, r3, #7
	mov	r1, r1, asr #3
	sub	r1, r1, #1
	mov	r3, r3, asr #3
	sub	r3, r3, #1
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #8]
	ldr	r1, [r4, #2972]
	ldr	r3, [r4, #2976]
	and	r1, r1, #63
	and	r3, r3, #7
	orr	r3, r3, r1, asl #8
	str	r3, [r5, #12]
.L2102:
	add	ip, r5, r8, lsl #3
	mov	r7, r8, asl #2
	add	ip, ip, #12
	mov	lr, #0
.L2103:
	mov	r1, lr, asl #1
	add	lr, lr, #1
	add	r3, r1, #1
	add	r1, r7, r1
	add	r3, r7, r3
	cmp	lr, #2
	add	r10, r4, r1, lsl #1
	add	r0, r4, r3, lsl #1
	ldrb	r1, [r10, #2884]	@ zero_extendqisi2
	mov	r3, r0
	ldrb	r0, [r0, #2884]	@ zero_extendqisi2
	ldrb	r3, [r3, #2885]	@ zero_extendqisi2
	and	r1, r1, #63
	and	r0, r0, #63
	ldrb	r9, [r10, #2885]	@ zero_extendqisi2
	and	r3, r3, #63
	mov	r0, r0, asl #16
	and	r9, r9, #63
	orr	r3, r0, r3, asl #24
	orr	r3, r3, r1
	orr	r3, r3, r9, asl #8
	str	r3, [ip, #4]!
	bne	.L2103
	add	r8, r8, #1
	cmp	r8, #8
	bne	.L2102
	ldr	lr, [r4, #2880]
	mov	r3, #0
	ldr	r8, [r4, #2876]
	add	r1, r2, #3792
	cmp	lr, r3
	ldr	ip, [r4, #2872]
	ldrb	r7, [r4, #2868]	@ zero_extendqisi2
	movlt	r10, #268435456
	movge	r10, r3
	cmp	lr, #0
	eor	r0, r8, r8, asr #31
	rsblt	lr, lr, #0
	cmp	r8, r3
	sub	r0, r0, r8, asr #31
	and	lr, lr, #15
	movlt	r9, #1048576
	movge	r9, r3
	cmp	ip, r3
	and	r0, r0, #15
	movlt	r8, #4096
	movge	r8, r3
	cmp	ip, #0
	mov	r0, r0, asl #16
	rsblt	ip, ip, #0
	orr	r0, r0, lr, asl #24
	and	ip, ip, #15
	orr	r0, r0, r7
	mov	lr, r3
	orr	r0, r0, ip, asl #8
	orr	r10, r0, r10
	orr	r9, r10, r9
	orr	r8, r9, r8
	str	r8, [r5, #80]
	ldrb	r8, [r2, #3719]	@ zero_extendqisi2
	ldrb	r0, [r2, #3720]	@ zero_extendqisi2
	and	r8, r8, #1
	ldrb	ip, [r2, #3716]	@ zero_extendqisi2
	ldrb	r7, [r2, #3717]	@ zero_extendqisi2
	and	r9, r0, #1
	mov	r8, r8, asl #2
	and	ip, ip, #1
	orr	r0, r8, r9, asl #3
	and	r7, r7, #1
	orr	r0, r0, ip
	orr	r0, r0, r7, asl #1
	str	r0, [r5, #84]
.L2108:
	ldr	r0, [r1, #4]!
	and	r0, r0, #15
	orr	lr, lr, r0, asl r3
	add	r3, r3, #4
	cmp	r3, #32
	bne	.L2108
	add	r3, r4, #2624
	str	lr, [r5, #88]
	add	r3, r3, #4
	movw	ip, #1112
	add	r0, r3, #4096
	movw	r1, #1144
	add	lr, r0, #1120
	add	r7, r0, #1104
	ldrh	r9, [r0, ip]
	add	ip, r0, #1136
	ldrh	r10, [lr]
	add	lr, r3, #5248
	ubfx	r9, r9, #0, #9
	ldrh	r8, [r7]
	ubfx	r10, r10, #0, #9
	movw	r7, #1128
	mov	r9, r9, asl #9
	ubfx	r8, r8, #0, #9
	orr	r3, r9, r10, asl #18
	movw	r9, #1160
	orr	r3, r3, r8
	str	r3, [r5, #92]
	ldrh	ip, [ip]
	mov	r3, #0
	ldrh	r8, [r0, r1]
	mov	r1, r3
	ubfx	ip, ip, #0, #9
	ldrh	r7, [r0, r7]
	ubfx	r8, r8, #0, #9
	mov	ip, ip, asl #9
	ubfx	r7, r7, #0, #9
	orr	ip, ip, r8, asl #18
	orr	r7, ip, r7
	str	r7, [r5, #96]
	ldrh	ip, [r0, r9]
	ldrh	r0, [lr]
	ubfx	ip, ip, #0, #9
	ubfx	r0, r0, #0, #9
	orr	r0, r0, ip, asl #9
	str	r0, [r5, #100]
.L2109:
	movw	r0, #16022
	movt	r0, 4
	add	r0, r3, r0
	ldrb	r0, [r6, r0]	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L2109
	mov	r3, #0
	str	r1, [r5, #104]
	mov	r0, r3
.L2110:
	movw	r1, #16054
	movt	r1, 4
	add	r1, r3, r1
	ldrb	r1, [r6, r1]	@ zero_extendqisi2
	orr	r0, r0, r1, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L2110
	movw	r8, #16024
	mov	r7, #0
	movt	r8, 4
	add	r8, r6, r8
	mov	r6, r7
	str	r0, [r5, #108]
.L2111:
	ldrh	r0, [r8, #2]
	mov	r3, r7, asl #1
	ldrh	r1, [r8], #8
	add	ip, r7, #16
	and	r0, r0, #1
	add	r7, r7, #1
	and	r1, r1, #3
	cmp	r7, #8
	mov	r1, r1, asl r3
	orr	r3, r1, r0, asl ip
	orr	r6, r6, r3
	bne	.L2111
	str	r6, [r5, #112]
	ldr	r3, [r4, #2580]
	str	r3, [r5, #116]
	ldr	r3, [r4, #2592]
	str	r3, [r5, #120]
	ldr	r3, [r4, #2664]
	str	r3, [r5, #128]
	ldr	r3, [r4, #2668]
	str	r3, [r5, #132]
	ldr	r3, [r4, #2672]
	str	r3, [r5, #136]
	ldr	r3, [r4, #2676]
	str	r3, [r5, #140]
	ldr	r3, [r2, #3976]
	ldr	r1, [r2, #3972]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #180]
	ldr	r3, [r2, #3992]
	ldr	r1, [r2, #3988]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #184]
	ldr	r3, [r2, #4008]
	ldr	r1, [r2, #4004]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #188]
	ldr	r1, [r2, #4000]
	ldr	r3, [r2, #4016]
	and	r1, r1, #63
	ldr	r0, [r2, #3984]
	and	r3, r3, #63
	mov	r1, r1, asl #8
	and	r0, r0, #63
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0
	str	r3, [r5, #192]
	ldr	r3, [r2, #3996]
	ldr	r0, [r2, #4012]
	and	r3, r3, #63
	ldr	r1, [r2, #3980]
	and	r0, r0, #63
	mov	r2, r3, asl #8
	and	r1, r1, #63
	orr	r3, r2, r0, asl #16
	orr	r3, r3, r1
	str	r3, [r5, #196]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #200]
	bls	.L2138
.L2113:
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #204]
	bhi	.L2115
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2532]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2544]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #204]
.L2115:
	ldr	r3, [r4, #2820]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #208]
	bhi	.L2117
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2536]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2548]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #208]
.L2117:
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #2752]
	ldr	r2, [r2, #2756]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #212]
	ldr	r2, [r4, #2812]
	cmp	r2, #8
	bls	.L2118
	mov	r3, #0
	str	r3, [r5, #216]
	str	r3, [r5, #220]
	str	r3, [r5, #224]
.L2119:
	ldr	r2, [r4, #2816]
	cmp	r2, #8
	bls	.L2121
	mov	r3, #0
	str	r3, [r5, #228]
	str	r3, [r5, #232]
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bhi	.L2139
.L2124:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r8, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r8, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #240]
	ldr	ip, [r0, ip]
	ldr	lr, [r1, #64]
	add	r3, ip, #255
	ldr	r7, [r4, #2476]
	bic	r1, r3, #255
	add	r0, lr, #63
	bic	r6, r0, #63
	mul	r3, r8, r1
	cmp	r3, #0
	add	r1, r3, #7
	movlt	r3, r1
	cmp	r7, #1
	mov	r3, r3, asr #3
	mul	r3, r6, r3
	beq	.L2140
.L2126:
	add	r4, r4, r2
	movw	r1, #7932
	add	r2, r4, #7872
	str	r3, [r5, #244]
	ldr	r1, [r4, r1]
	ldr	r0, [r2, #64]
	add	r3, r1, #2032
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r3, r3, #15
	addmi	r2, r0, #126
	add	r1, r1, #14
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2138:
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2528]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2540]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #200]
	b	.L2113
.L2121:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r7, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #228]
	ldr	r0, [r0, ip]
	ldr	ip, [r1, #64]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	bic	lr, r1, #63
	mul	r3, r7, r3
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2141
.L2123:
	add	r2, r4, r2
	movw	r1, #7932
	add	r0, r2, #7872
	str	r3, [r5, #232]
	add	r0, r0, #60
	ldr	r1, [r2, r1]
	ldr	r0, [r0, #4]
	add	r3, r1, #2032
	add	r3, r3, #15
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r1, r1, #14
	addmi	r2, r0, #126
	cmp	r3, #0
	movlt	r3, r1
	mov	r2, r2, asr #6
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bls	.L2124
.L2139:
	mov	r3, #0
	str	r3, [r5, #240]
	str	r3, [r5, #244]
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2118:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r7, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #216]
	ldr	r0, [r0, ip]
	ldr	ip, [r1, #64]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	bic	lr, r1, #63
	mul	r3, r7, r3
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2142
.L2120:
	add	r2, r4, r2
	movw	r1, #7932
	add	r0, r2, #7872
	str	r3, [r5, #220]
	add	r0, r0, #60
	ldr	r1, [r2, r1]
	ldr	r0, [r0, #4]
	add	r3, r1, #2032
	add	r3, r3, #15
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r1, r1, #14
	addmi	r2, r0, #126
	cmp	r3, #0
	movlt	r3, r1
	mov	r2, r2, asr #6
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #224]
	b	.L2119
.L2137:
	ldr	ip, [r2, #3648]
	ldr	r3, [r9, #2756]
	cmp	ip, r3
	movne	ip, #1048576
	moveq	ip, #0
	b	.L2101
.L2140:
	ldr	r1, [r4, #2480]
	cmp	r1, #0
	bne	.L2126
	add	r1, ip, #2032
	cmp	r0, #0
	add	r1, r1, #15
	addlt	r0, lr, #126
	add	ip, ip, #4080
	cmp	r1, #0
	add	ip, ip, #14
	movge	ip, r1
	mov	r1, r0, asr #6
	mov	r0, ip, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2126
.L2141:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2123
	add	lr, r0, #2032
	cmp	r1, #0
	add	lr, lr, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	lr, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2123
.L2142:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2120
	add	lr, r0, #2032
	cmp	r1, #0
	add	lr, lr, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	lr, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2120
	UNWIND(.fnend)
	.size	Vp9_SetPoolInfoFrame, .-Vp9_SetPoolInfoFrame
	.align	2
	.global	Vp9_SetPoolInfoTile
	.type	Vp9_SetPoolInfoTile, %function
Vp9_SetPoolInfoTile:
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
	ldr	r2, [r3]
	str	r2, [r1]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	and	r2, r2, #127
	str	r2, [r1, #4]
	ldr	r2, [r3, #8]
	add	r2, r2, #128
	str	r2, [r1, #8]
	ldr	r2, [r3, #12]
	str	r2, [r1, #12]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	and	r2, r2, #127
	str	r2, [r1, #16]
	ldr	r2, [r3, #20]
	str	r2, [r1, #20]
	ldrh	r2, [r3, #26]
	ldrh	ip, [r3, #24]
	cmp	ip, r2
	add	r0, ip, #7
	addne	r2, r2, #7
	ubfx	r0, r0, #3, #7
	movne	r2, r2, asr #3
	mov	r0, r0, asl #16
	subne	r2, r2, #1
	orreq	r2, r0, #255
	andne	r2, r2, #127
	orrne	r2, r2, r0
	str	r2, [r1, #24]
	ldrh	r0, [r3, #30]
	ldrh	ip, [r3, #28]
	cmp	ip, r0
	add	r2, ip, #7
	addne	r0, r0, #7
	ubfx	r2, r2, #3, #7
	movne	r0, r0, asr #3
	mov	r2, r2, asl #16
	subne	r0, r0, #1
	orreq	r2, r2, #255
	andne	r0, r0, #127
	orrne	r2, r0, r2
	str	r2, [r1, #28]
	ldr	r2, [r3, #32]
	mov	r0, #0
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #32]
	ldr	r2, [r3, #36]
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #36]
	ldr	r2, [r3, #40]
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #40]
	ldr	r3, [r3, #44]
	str	r0, [r1, #252]
	ubfx	r3, r3, #0, #17
	str	r3, [r1, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_SetPoolInfoTile, .-Vp9_SetPoolInfoTile
	.align	2
	.global	Vp9_DecodeTilesCtrl
	.type	Vp9_DecodeTilesCtrl, %function
Vp9_DecodeTilesCtrl:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 160
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #172)
	sub	sp, sp, #172
	add	r3, r0, #274432
	mov	r10, r1
	mov	ip, #1
	ldr	r1, [r3, #3696]
	add	r4, r0, #270336
	ldr	r7, [r3, #3684]
	ldr	r8, [r10]
	mov	lr, r1
	str	r1, [fp, #-196]
	add	r1, r0, #311296
	mov	r2, ip, asl lr
	str	r1, [fp, #-168]
	mov	r5, r1
	ldr	r1, [r3, #3692]
	ldr	r3, [r3, #3688]
	mov	r9, r2
	str	r2, [fp, #-192]
	ldr	r2, [r10, #16]
	mov	r6, r1
	str	r1, [fp, #-152]
	add	r1, r0, #8
	mov	ip, ip, asl r6
	str	r3, [fp, #-188]
	str	r0, [fp, #-116]
	add	r3, r8, r2
	str	ip, [fp, #-124]
	str	r3, [fp, #-120]
	bl	Vp9_SetPoolInfoFrame
	mov	r1, #0
	str	r1, [r5, #2868]
	ldr	r2, [r4, #2552]
	cmp	r9, #0
	ldr	r3, [r4, #2556]
	str	r2, [fp, #-164]
	and	r3, r3, #15
	str	r3, [fp, #-160]
	ble	.L2159
	ldr	r2, [fp, #-188]
	add	r3, r7, #7
	str	r1, [fp, #-180]
	add	r2, r2, #7
	mov	r0, r3, asr #3
	str	r1, [fp, #-172]
	mov	r3, r2, asr #3
	str	r0, [fp, #-156]
	str	r0, [fp, #-204]
	str	r3, [fp, #-200]
	str	r1, [fp, #-112]
	str	r1, [fp, #-184]
.L2158:
	ldr	r3, [fp, #-180]
	ldr	r2, [fp, #-200]
	ldr	r0, [fp, #-196]
	add	r3, r3, r2
	str	r3, [fp, #-180]
	ldr	r2, [fp, #-188]
	mov	r1, r3
	ldr	r3, [fp, #-184]
	mov	r1, r1, asr r0
	str	r1, [fp, #-184]
	ldr	ip, [fp, #-124]
	mov	r3, r3, asl #3
	mov	r0, r1
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-136]
	mov	r1, r3
	mov	r3, r0, asl #3
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-140]
	mov	r0, r3
	rsb	r3, r1, r0
	add	r3, r3, #7
	cmp	ip, #0
	mov	r2, r1
	mov	r3, r3, asr #3
	str	r3, [fp, #-132]
	ble	.L2151
	add	r3, r0, #7
	ldr	r0, [fp, #-204]
	add	r1, r2, #7
	mov	r9, #0
	mov	r3, r3, asr #3
	ldr	r2, [r10, #16]
	sub	r3, r3, #1
	mov	r1, r1, asr #3
	mov	r6, r9
	str	r9, [fp, #-104]
	mul	r3, r0, r3
	mul	r1, r0, r1
	str	r3, [fp, #-144]
	sub	r3, ip, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-192]
	str	r1, [fp, #-148]
	sub	r3, r3, #1
	str	r3, [fp, #-176]
	mov	r3, r10
	mov	r10, r9
	mov	r9, r3
	b	.L2157
.L2170:
	ldr	r2, [fp, #-176]
	ldr	r1, [fp, #-172]
	cmp	r2, r1
	ldrle	r2, [fp, #-120]
	rsble	r5, r8, r2
	bgt	.L2152
.L2154:
	ldrh	r1, [fp, #-136]
	rsb	r2, r3, r4
	add	r2, r2, #7
	strh	r4, [fp, #-66]	@ movhi
	add	r4, r4, #7
	mov	ip, #0
	strh	r1, [fp, #-72]	@ movhi
	mov	r0, r2, asr #3
	ldrh	r1, [fp, #-140]
	mov	r2, #0
	str	r2, [fp, #-84]
	ldr	r2, [fp, #-132]
	strh	r1, [fp, #-70]	@ movhi
	ldr	r1, [fp, #-164]
	mul	r2, r2, r0
	rsb	r0, r1, r8
	ldr	r1, [fp, #-160]
	strb	ip, [fp, #-80]
	sub	ip, fp, #44
	add	r0, r0, r1
	ldr	r1, [fp, #-144]
	str	ip, [fp, #-48]
	and	lr, r0, #15
	ldr	ip, [fp, #-112]
	add	r1, r1, r4, asr #3
	strh	r3, [fp, #-68]	@ movhi
	cmp	r2, #0
	add	r4, ip, r2
	add	r3, r3, #7
	mov	r2, #0
	str	r2, [fp, #-76]
	sub	r2, r1, #1
	ldr	r1, [fp, #-148]
	str	r2, [fp, #-64]
	bic	r0, r0, #15
	add	r3, r1, r3, asr #3
	sub	r2, r4, #1
	str	r3, [fp, #-56]
	mov	r3, lr, asl #3
	str	ip, [fp, #-52]
	strb	r3, [fp, #-92]
	mov	r3, r5, asl #3
	str	r2, [fp, #-60]
	str	r0, [fp, #-96]
	str	r3, [fp, #-88]
	bne	.L2167
.L2155:
	ldr	r3, [fp, #-116]
	add	r3, r3, #278528
	ldr	r3, [r3, #296]
	cmp	r5, r3
	bgt	.L2168
	ldr	r3, [fp, #-124]
	add	r6, r6, #1
	ldr	r2, [r9, #16]
	add	r8, r8, r5
	cmp	r6, r3
	rsb	r2, r5, r2
	str	r2, [r9, #16]
	beq	.L2169
	str	r4, [fp, #-112]
.L2157:
	ldr	r3, [fp, #-156]
	mov	r0, r9
	ldr	r1, [fp, #-152]
	add	r10, r10, r3
	ldr	r3, [fp, #-104]
	mov	r1, r10, asr r1
	str	r1, [fp, #-104]
	mov	r3, r3, asl #3
	cmp	r3, r7
	mov	ip, r1
	mov	r4, ip, asl #3
	mov	r1, r8
	movge	r3, r7
	cmp	r4, r7
	str	r3, [fp, #-108]
	movge	r4, r7
	bl	BsInit
	ldr	r3, [fp, #-128]
	cmp	r6, r3
	ldr	r3, [fp, #-108]
	bge	.L2170
.L2152:
	ldr	r2, [fp, #-120]
	cmp	r2, #0
	cmpne	r8, #0
	beq	.L2161
	add	r8, r8, #4
	str	r3, [fp, #-108]
	cmp	r2, r8
	bcc	.L2161
	mov	r1, #32
	mov	r0, r9
	bl	BsGet
	ldr	r3, [fp, #-108]
	mov	r5, r0
	b	.L2154
.L2167:
	ldr	r3, [fp, #-168]
	sub	r1, fp, #96
	ldr	r2, [r3, #2868]
	mov	r3, r1
	ldr	r1, [fp, #-116]
	mov	r0, r1
	add	r1, r1, r2, lsl #8
	add	r1, r1, #1024
	add	r1, r1, #8
	bl	Vp9_SetPoolInfoTile
	ldr	r2, [fp, #-168]
	ldr	r3, [r2, #2868]
	add	r3, r3, #1
	str	r3, [r2, #2868]
	b	.L2155
.L2161:
	mvn	r0, #0
.L2150:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2169:
	mov	r10, r9
	str	r4, [fp, #-112]
.L2151:
	ldr	r3, [fp, #-172]
	ldr	r2, [fp, #-192]
	add	r3, r3, #1
	str	r3, [fp, #-172]
	cmp	r3, r2
	bne	.L2158
.L2159:
	mov	r0, #0
	b	.L2150
.L2168:
	str	r3, [sp, #4]
	mov	r0, #0
	movw	r3, #4530
	str	r5, [sp]
	ldr	r2, .L2171
	ldr	r1, .L2171+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2172:
	.align	2
.L2171:
	.word	.LANCHOR0+804
	.word	.LC35
	UNWIND(.fnend)
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
	.align	2
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #108)
	sub	sp, sp, #108
	add	r3, r0, #274432
	add	r4, r0, #311296
	add	r6, r0, #270336
	ldr	r7, [r3, #3600]
	mov	r5, r0
	ldr	r0, [r3, #3680]
	mov	lr, #0
	clz	ip, r7
	ldr	r10, [r6, #2688]
	ldr	r8, [r6, #2680]
	mov	r9, r0
	str	r0, [fp, #-108]
	mov	ip, ip, lsr #5
	ldr	r0, [r3, #3704]
	str	ip, [r4, #2824]
	str	r7, [r4, #2836]
	ldr	ip, [r3, #3632]
	str	r0, [fp, #-120]
	sub	r0, fp, #84
	str	lr, [fp, #-92]
	str	ip, [r4, #2844]
	ldr	ip, [r3, #3700]
	str	lr, [fp, #-88]
	add	lr, r5, #278528
	str	r9, [fp, #-96]
	add	r9, lr, #312
	str	ip, [r4, #2828]
	ldr	ip, [r3, #3676]
	str	r1, [fp, #-112]
	str	r2, [fp, #-116]
	str	ip, [r4, #2848]
	ldr	ip, [r6, #2684]
	str	lr, [fp, #-104]
	str	ip, [r4, #2852]
	ldr	ip, [r3, #3712]
	str	ip, [r4, #2856]
	ldr	r3, [r3, #3596]
	str	r3, [r4, #2840]
	bl	BsInit
	ldr	r3, [r4, #2824]
	cmp	r3, #0
	ldr	r3, [r4, #2844]
	bne	.L2175
	cmp	r3, #0
	beq	.L2190
.L2175:
	add	r1, r5, #282624
	stmia	sp, {r3, r7}
	add	r1, r1, #924
	ldr	r3, [fp, #-120]
	sub	r2, fp, #96
	mov	r0, r9
	bl	Vp9_SetupPastIndependence
	ldr	r3, .L2194
	movw	r0, #10884
	mov	r2, #16
	movt	r0, 4
	mov	r1, #0
	add	r0, r5, r0
	ldr	r3, [r3, #48]
	blx	r3
.L2176:
	ldr	r3, [fp, #-96]
	movw	r1, #4708
	mov	r2, r1
	ldr	r0, [fp, #-104]
	mla	r1, r1, r3, r5
	add	r0, r0, #312
	add	r1, r1, #282624
	add	r1, r1, #924
	bl	memcpy
	sub	r0, fp, #84
	bl	Vp9_Cabac_ReaderInit
	ldr	r2, [r4, #2852]
	ldr	r1, [r4, #2856]
	sub	r0, fp, #88
	ldr	r3, [r4, #2828]
	sub	ip, fp, #92
	str	r2, [sp, #4]
	mov	r2, r7
	str	r1, [sp]
	mov	r1, r9
	str	r0, [sp, #20]
	sub	r0, fp, #84
	str	r8, [sp, #12]
	str	r10, [sp, #8]
	str	ip, [sp, #16]
	bl	Vp9_ReadCompressedHeader
	cmp	r0, #0
	bne	.L2191
	ldr	r3, [fp, #-88]
	movw	r8, #10820
	ldr	r2, [fp, #-92]
	movt	r8, 4
	add	r8, r5, r8
	str	r3, [r6, #2860]
	str	r3, [r4, #2832]
	ldr	r3, [r6, #2972]
	str	r2, [r6, #2864]
	cmp	r3, #0
	bne	.L2192
.L2179:
	ldr	r3, [r4, #2828]
	cmp	r3, #0
	bne	.L2193
	mov	r1, r7, asl #6
	ldr	r10, .L2194
	sub	r1, r1, r7, asl #4
	mov	r2, #48
	add	r1, r9, r1
	add	r0, r9, #4352
	add	r1, r1, #4608
	ldr	ip, [r10, #52]
	add	r1, r1, #4
	blx	ip
.L2181:
	add	r1, r8, #5184
	ldr	ip, [r10, #52]
	add	r1, r1, #5
	mov	r2, #7
	add	r0, r9, #4544
	blx	ip
	ldr	r3, [fp, #-104]
	add	r1, r8, #5184
	ldr	ip, [r10, #52]
	add	r1, r1, #12
	add	r0, r3, #4864
	mov	r2, #3
	blx	ip
	movw	r0, #1037
	mov	r2, #4608
	mov	r1, r9
	movt	r0, 4
	ldr	ip, [r10, #52]
	add	r0, r5, r0
	blx	ip
	ldr	r2, [r4, #2828]
	cmp	r2, #0
	beq	.L2182
	ldr	r3, [fp, #-108]
	movw	ip, #4708
	movw	r0, #25756
	mov	r2, #48
	movt	r0, 4
	mul	ip, ip, r3
	ldr	r3, .L2194
	add	r1, r5, ip
	ldr	r4, [r3, #52]
	mov	ip, r1
	add	r1, r1, #286720
	add	r0, ip, r0
	add	r1, r1, #1440
	blx	r4
.L2183:
	ldr	r3, [fp, #-108]
	movw	r1, #4708
	movw	r0, #5645
	mov	r2, #4608
	movt	r0, 4
	add	r0, r5, r0
	mla	r1, r1, r3, r5
	ldr	r3, [r10, #52]
	add	r1, r1, #282624
	add	r1, r1, #924
	blx	r3
	ldr	r3, [r6, #2636]
	ldr	r2, [fp, #-112]
	sub	r1, fp, #84
	ldr	ip, [fp, #-116]
	mov	r0, r5
	add	r2, r2, r3
	str	r2, [fp, #-84]
	rsb	r3, r3, ip
	str	r3, [fp, #-68]
	bl	Vp9_DecodeTilesCtrl
	mov	r0, #0
.L2178:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2193:
	ldr	r10, .L2194
	add	r1, r9, #4608
	add	r1, r1, #4
	mov	r2, #48
	add	r0, r9, #4352
	ldr	ip, [r10, #52]
	blx	ip
	b	.L2181
.L2190:
	ldr	r2, [r4, #2828]
	cmp	r2, #0
	beq	.L2176
	b	.L2175
.L2182:
	ldr	r3, [fp, #-108]
	movw	lr, #4708
	mov	r1, r7, asl #6
	movw	r0, #25756
	sub	r1, r1, r7, asl #4
	movt	r0, 4
	mul	lr, lr, r3
	ldr	r3, .L2194
	mov	r2, #48
	add	r1, r1, lr
	add	lr, r5, lr
	add	r1, r5, r1
	ldr	ip, [r3, #52]
	add	r1, r1, #286720
	add	r0, lr, r0
	add	r1, r1, #1440
	blx	ip
	b	.L2183
.L2192:
	add	r2, r8, #5184
	add	r1, r8, #336
	add	r0, r8, #256
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2179
.L2191:
	ldr	r1, .L2194+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2178
.L2195:
	.align	2
.L2194:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	UNWIND(.fnend)
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
	.align	2
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r4, r0, #311296
	add	r9, r0, #278528
	movw	r7, #10820
	ldr	r3, [r4, #2764]
	movt	r7, 4
	mov	r5, r0
	str	r1, [fp, #-56]
	cmp	r3, #0
	add	r8, r9, #280
	add	r6, r0, #274432
	add	r7, r0, r7
	beq	.L2197
	ldr	r3, [r6, #3592]
	cmp	r3, #0
	blt	.L2197
.L2198:
	str	r3, [r4, #2760]
	mov	r1, r7
	mov	r0, r8
	bl	Read_UnCompressed_Header
	subs	r10, r0, #0
	bne	.L2277
	ldr	r2, [r6, #3660]
	ldr	r3, [r5]
	str	r2, [r3, #900]
	ldr	r2, [r6, #3660]
	cmp	r2, #10
	bgt	.L2280
.L2205:
	ldr	r3, [r6, #3620]
	add	r10, r5, #270336
	cmp	r3, #0
	bne	.L2207
	ldr	r2, [r10, #2560]
	cmp	r2, #7
	ble	.L2281
.L2207:
	ldr	r3, [r6, #3644]
	sub	r2, r3, #128
	cmp	r2, #3968
	bls	.L2282
.L2208:
	ldr	r3, .L2296
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2277
	mov	r3, #0
	ldr	r0, [r4, #2860]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L2271:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2197:
	add	r10, r5, #270336
	ldr	r3, [r10, #2708]
	cmp	r3, #0
	beq	.L2199
	movw	r2, #10900
	mov	r3, #1
	movt	r2, 4
	add	r2, r5, r2
.L2200:
	ldr	r1, [r2, #4]!
	cmp	r1, #0
	beq	.L2199
	add	r3, r3, #1
	cmp	r3, #9
	bne	.L2200
	mvn	r3, #0
	str	r3, [r6, #3592]
.L2239:
	ldr	r1, .L2296+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2271
.L2282:
	ldr	r2, [r6, #3648]
	sub	r1, r2, #128
	cmp	r1, #3968
	bhi	.L2208
	adds	r1, r3, #63
	str	r3, [r10, #2648]
	addmi	r1, r3, #126
	adds	r3, r2, #63
	addmi	r3, r2, #126
	str	r2, [r10, #2652]
	mov	r0, r5
	mov	r2, r1, asr #6
	mov	r3, r3, asr #6
	str	r2, [r10, #2640]
	str	r3, [r10, #2644]
	bl	VP9_GetRefNum
	str	r0, [r4, #2736]
	ldr	r0, [r4, #2860]
	ldr	r2, [r10, #2652]
	ldr	r1, [r10, #2648]
	bl	VCTRL_GetFsSize
	mov	r1, r0
	str	r0, [r4, #2724]
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	r3, .L2296+8
	ldr	r1, [r4, #2860]
	ldr	r2, [r3, r1, asl #2]
	str	r0, [r4, #2728]
	ldr	r3, [r2, #1392]
	str	r3, [r4, #2732]
	ldr	r0, [r10, #2648]
	cmp	r0, #1920
	bhi	.L2211
	ldr	lr, [r10, #2652]
	cmp	lr, #1088
	bhi	.L2211
	ldr	lr, [r2, #36]
	cmp	lr, #24
	beq	.L2211
	add	r2, r2, #475136
	ldr	r2, [r2, #996]
	cmp	r2, #0
	addeq	r3, r3, #4
.L2211:
	ldr	lr, [r4, #2740]
	ldr	r2, [r4, #2736]
	ldr	ip, [r4, #2744]
	cmp	r2, lr
	movge	lr, r2
	cmp	r0, ip
	add	r3, lr, r3
	str	r3, [r4, #2732]
	beq	.L2283
.L2212:
	str	r2, [r4, #2740]
.L2214:
	mov	r0, r1
	mov	r1, #0
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #2728]
	cmp	r0, r2
	ble	.L2215
	rsb	r3, r2, r0
	cmp	r3, #0
	ble	.L2215
	mov	r3, #0
	str	r5, [fp, #-60]
	str	r6, [fp, #-64]
	mov	r5, r3
	mov	r6, r4
	mov	r4, r0
	b	.L2217
.L2216:
	ldr	r2, [r6, #2728]
	rsb	r1, r2, r4
	cmp	r1, r5
	ble	.L2284
.L2217:
	ldr	r1, [r6, #2724]
	add	r5, r5, #1
	ldr	r0, [r6, #2860]
	bl	FSP_RelsePhyFs
	cmp	r0, #0
	beq	.L2216
	mov	r4, r6
	ldr	r5, [fp, #-60]
	ldr	r6, [fp, #-64]
	ldr	r2, [r4, #2728]
.L2215:
	ldr	r3, [r4, #2732]
	cmp	r3, r2
	bge	.L2220
	rsb	r2, r3, r2
	cmp	r2, #0
	ble	.L2220
	mov	r2, #0
	str	r5, [fp, #-60]
	mov	r5, r4
	mov	r4, r2
	b	.L2221
.L2285:
	ldr	r3, [r5, #2728]
	ldr	r1, [r5, #2732]
	rsb	r3, r1, r3
	cmp	r3, r4
	ble	.L2275
.L2221:
	mov	r1, #0
	ldr	r0, [r5, #2860]
	bl	FSP_RelsePhyFs
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L2285
.L2275:
	mov	r4, r5
	ldr	r5, [fp, #-60]
.L2220:
	mov	r1, #0
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	r3, [r4, #2732]
	add	r3, r3, #4
	cmp	r0, r3
	bgt	.L2286
	str	r0, [fp, #-60]
	ldr	r1, [r4, #2724]
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	ip, [fp, #-60]
	mov	r3, r0
	ldr	r0, [r4, #2736]
	rsb	r1, ip, r3
	str	r3, [r4, #2728]
	add	r2, r0, #1
	cmp	r3, r2
	ldr	r2, [r4, #2732]
	addgt	lr, r0, #2
	addle	lr, r3, #1
	add	r2, r1, r2
	str	r0, [sp, #8]
	cmp	lr, r2
	str	r3, [sp, #4]
	str	ip, [sp]
	mov	r0, #2
	movlt	lr, r2
	ldr	r1, .L2296+12
	str	lr, [r4, #2732]
	ldr	r3, [r10, #2652]
	ldr	r2, [r10, #2648]
	str	lr, [sp, #12]
	bl	dprint_vfmw
	ldr	r3, [r10, #2568]
	cmp	r3, #0
	beq	.L2224
	ldr	r2, [r4, #2744]
	ldr	r3, [r10, #2648]
	cmp	r2, r3
	bne	.L2224
	ldr	r2, [r4, #2748]
	ldr	r3, [r10, #2652]
	cmp	r2, r3
	bne	.L2224
	ldr	r2, [r4, #2728]
	ldr	r3, [r4, #2732]
	cmp	r2, r3
	bge	.L2225
.L2224:
	mov	r0, r5
	bl	VP9_ArrangeVHBMem
	ldr	r3, [r10, #2568]
	cmp	r3, #0
	beq	.L2287
.L2225:
	ldr	r3, [r5]
	ldr	r3, [r3, #8]
	str	r3, [r10, #2564]
	ldr	r3, [r6, #3620]
	ldr	r0, [r4, #2860]
	cmp	r3, #0
	ldreq	r3, [r10, #2648]
	streq	r3, [r4, #2744]
	ldreq	r3, [r10, #2652]
	streq	r3, [r4, #2748]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	bne	.L2288
	mov	r0, r8
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	bne	.L2289
.L2228:
	ldr	r3, [r6, #3620]
	cmp	r3, #0
	beq	.L2290
.L2229:
	mov	r0, r5
	bl	VP9_GetImageBuffer
	cmp	r0, #0
	bne	.L2291
	ldr	r3, [r4, #2760]
	mov	r0, r5
	ldr	r2, [r10, #2612]
	add	r3, r10, r3, lsl #2
	str	r2, [r3, #2824]
	bl	VP9_Set_DecParam
	cmp	r0, #0
	bne	.L2292
	ldr	r3, [r6, #3620]
	cmp	r3, #1
	beq	.L2293
	ldr	r3, [r10, #2648]
	str	r3, [r4, #2752]
	ldr	r3, [r10, #2652]
	str	r3, [r4, #2756]
.L2234:
	mov	r0, r7
	bl	swap_frame_buffers
	ldr	r2, [r4, #2812]
	ldr	r0, [r4, #2816]
	cmp	r2, r0
	bcs	.L2235
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2235
	add	r3, r2, #1
	b	.L2236
.L2294:
	ldrb	r1, [r2]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2235
.L2236:
	cmp	r3, r0
	str	r3, [r4, #2812]
	mov	r2, r3
	add	r3, r3, #1
	bne	.L2294
.L2235:
	ldr	r3, [r4, #2768]
	cmp	r3, #1
	beq	.L2295
.L2237:
	mov	r7, #0
	str	r7, [r4, #2764]
	ldr	r0, [r6, #3620]
	cmp	r0, r7
	bne	.L2238
	ldr	r3, [r6, #3616]
	str	r3, [r6, #3628]
	b	.L2271
.L2281:
	ldr	r1, .L2296+16
	mov	r0, #1
	bl	dprint_vfmw
.L2277:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2280:
	ldr	r1, .L2296+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2296
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2205
	ldr	lr, [r6, #3660]
	mov	r3, #8
	str	r10, [fp, #-52]
	sub	r2, fp, #52
	mov	r1, #119
	ldr	r0, [r4, #2860]
	str	lr, [fp, #-48]
	blx	ip
	b	.L2205
.L2199:
	add	ip, r10, r3, lsl #2
	cmp	r3, #0
	mov	r2, #1
	str	r2, [ip, #2708]
	str	r3, [r6, #3592]
	bge	.L2198
	b	.L2239
.L2283:
	ldr	r3, [r10, #2652]
	ldr	r0, [r4, #2748]
	cmp	r0, r3
	streq	lr, [r4, #2740]
	bne	.L2212
	b	.L2214
.L2290:
	ldr	r3, [r9, #304]
	mov	r0, r5
	ldr	r2, [r9, #296]
	add	r3, r3, #7
	ldr	r1, [fp, #-56]
	mov	r3, r3, lsr #3
	add	r1, r1, r3
	rsb	r2, r3, r2
	bl	Vp9_DecodeTiles
	b	.L2229
.L2289:
	mov	r0, r8
	bl	BsGet
	b	.L2228
.L2293:
	ldr	r0, [r6, #3592]
	movw	r3, #10900
	movt	r3, 4
	add	r3, r5, r3
	ldr	r2, [r6, #3624]
	ldr	r1, [r3, r0, asl #2]
	cmp	r1, #0
	subgt	r1, r1, #1
	strgt	r1, [r3, r0, asl #2]
	str	r2, [r6, #3592]
	ldr	r1, [r3, r2, asl #2]
	add	r1, r1, #1
	str	r1, [r3, r2, asl #2]
	b	.L2234
.L2284:
	mov	r4, r6
	ldr	r5, [fp, #-60]
	ldr	r6, [fp, #-64]
	b	.L2215
.L2238:
	mov	r0, r5
	mov	r3, r7
	mov	r2, r7
	mov	r1, r7
	bl	VP9DEC_VDMPostProc
	mov	r0, r7
	b	.L2271
.L2295:
	ldr	r1, [r4, #2808]
	add	r3, r1, #77824
	add	r1, r1, #1
	add	r3, r3, #692
	add	r3, r5, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r1, [r4, #2808]
	add	r2, r2, r3
	str	r2, [r4, #2812]
	b	.L2237
.L2286:
	mvn	r0, #1
	b	.L2271
.L2288:
	movw	r3, #4047
	ldr	r2, .L2296+24
	ldr	r1, .L2296+28
	mov	r0, #23
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2271
.L2291:
	ldr	r1, .L2296+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2271
.L2287:
	ldr	r1, .L2296+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2271
.L2292:
	ldr	r1, .L2296+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2271
.L2297:
	.align	2
.L2296:
	.word	g_event_report
	.word	.LC37
	.word	s_pstVfmwChan
	.word	.LC40
	.word	.LC39
	.word	.LC38
	.word	.LANCHOR0+824
	.word	.LC42
	.word	.LC43
	.word	.LC41
	.word	.LC44
	UNWIND(.fnend)
	.size	VP9DEC_DecodeFame, .-VP9DEC_DecodeFame
	.align	2
	.global	VP9DEC_DecodePacket
	.type	VP9DEC_DecodePacket, %function
VP9DEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #0
	cmpne	r0, #0
	mov	r3, #0
	mov	r4, r0
	str	r3, [fp, #-72]
	beq	.L2310
	ldr	r0, [r1]
	add	r8, r4, #270336
	add	r5, r4, #311296
	str	r0, [r8, #2552]
	ldr	r3, [r1, #12]
	str	r3, [r8, #2556]
	ldr	r1, [r1, #16]
	str	r1, [r8, #2560]
	ldr	r6, [r5, #2768]
	cmp	r6, #0
	beq	.L2319
	ldr	r2, [r5, #2820]
	ldr	r7, [r5, #2812]
	b	.L2303
.L2321:
	ldrb	ip, [r7]	@ zero_extendqisi2
	and	r3, ip, #7
	and	r0, ip, #224
	ubfx	r1, ip, #3, #2
	add	r3, r3, #1
	cmp	r0, #192
	mla	r3, r1, r3, r3
	bne	.L2306
	add	r1, r3, #2
	cmp	r1, r2
	bls	.L2320
.L2303:
	cmp	r2, #0
	bne	.L2321
.L2306:
	cmp	r6, #1
	add	r0, r4, #278528
	add	r0, r0, #280
	mov	r1, r7
	ldreq	r3, [r5, #2808]
	addeq	r3, r3, #77824
	addeq	r3, r3, #692
	addeq	r3, r4, r3, lsl #2
	ldreq	r2, [r3, #4]
	bl	BsInit
	mov	r1, r7
	mov	r0, r4
	bl	VP9DEC_DecodeFame
	cmn	r0, #2
	mov	r6, r0
	moveq	r3, #1
	streq	r3, [r5, #2764]
	beq	.L2299
	cmp	r6, #0
	moveq	r0, r6
	bne	.L2322
.L2299:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2322:
	mov	r0, r4
	bl	VP9_FreeCurFb
	mov	r3, #0
	mov	r1, r4
	str	r3, [r5, #2768]
	mov	r0, #17
	bl	ReleasePacket
	ldr	r1, .L2324
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2320:
	add	r3, r7, r3
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, ip
	bne	.L2303
	ldr	r3, [r5, #2816]
	add	r7, r7, r1
	rsb	r2, r1, r2
	str	r7, [r5, #2812]
	cmp	r7, r3
	str	r2, [r5, #2820]
	bcc	.L2303
	b	.L2306
.L2319:
	sub	r3, fp, #72
	sub	r2, fp, #68
	bl	Vp9_ParseSuperFrameIndex
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L2323
.L2301:
	ldr	r7, [r8, #2552]
	ldr	r6, [r5, #2768]
	str	r7, [r5, #2812]
	ldr	r2, [r8, #2560]
	add	r3, r7, r2
	str	r3, [r5, #2816]
	str	r2, [r5, #2820]
	b	.L2303
.L2323:
	ldr	r2, .L2324+4
	movw	r0, #51924
	str	r3, [r5, #2804]
	mov	ip, #1
	str	r6, [r5, #2808]
	sub	r1, fp, #68
	ldr	r3, [r2, #52]
	movt	r0, 4
	mov	r2, #32
	add	r0, r4, r0
	str	ip, [r5, #2768]
	blx	r3
	b	.L2301
.L2310:
	mvn	r0, #0
	b	.L2299
.L2325:
	.align	2
.L2324:
	.word	.LC45
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.align	2
	.global	Vp9_TxCoefProbConvert2
	.type	Vp9_TxCoefProbConvert2, %function
Vp9_TxCoefProbConvert2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L2327
	mov	r2, #18
	mov	r5, r0
	mov	r6, r1
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #18
	add	r0, r5, #32
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #36
	add	r0, r5, #64
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #54
	add	r0, r5, #96
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #72
	add	r0, r5, #128
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #90
	add	r0, r5, #160
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #108
	add	r0, r5, #192
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #256
	add	r0, r5, #256
	mov	r2, #18
	blx	r3
	add	r1, r6, #272
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #288
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #292
	add	r0, r5, #320
	mov	r2, #18
	blx	r3
	add	r1, r6, #308
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #352
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #328
	add	r0, r5, #384
	mov	r2, #18
	blx	r3
	add	r1, r6, #344
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #416
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #364
	add	r0, r5, #448
	mov	r2, #18
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2328:
	.align	2
.L2327:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_TxCoefProbConvert2, .-Vp9_TxCoefProbConvert2
	.align	2
	.global	Vp9_ProbBurstConvert
	.type	Vp9_ProbBurstConvert, %function
Vp9_ProbBurstConvert:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2330
	mov	r2, #4608
	ldr	r3, [r3, #52]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L2331:
	.align	2
.L2330:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	2
	.global	Vp9_CoefCountRestore
	.type	Vp9_CoefCountRestore, %function
Vp9_CoefCountRestore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r7, r1, #1152
	add	r7, r7, #4
	add	r3, r1, #3456
	add	r3, r3, #4
	str	r0, [fp, #-52]
	str	r2, [fp, #-48]
	str	r3, [fp, #-56]
.L2333:
	ldr	r9, [fp, #-48]
	sub	r8, r7, #1152
	ldr	r4, [fp, #-52]
.L2339:
	add	r6, r4, #576
	mov	r5, r8
	mov	ip, r9
.L2337:
	add	lr, ip, #24
	mov	r0, r5
	mov	r1, r4
.L2334:
	ldr	r3, [r1]
	add	r0, r0, #16
	add	r1, r1, #16
	bic	r2, r3, #-67108864
	str	r2, [ip], #4
	ldr	r2, [r1, #-12]
	mov	r3, r3, lsr #26
	cmp	lr, ip
	ubfx	r10, r2, #0, #20
	mov	r2, r2, lsr #20
	orr	r3, r3, r10, asl #6
	str	r3, [r0, #-20]
	ldr	r3, [r1, #-8]
	ubfx	r10, r3, #0, #14
	mov	r3, r3, lsr #14
	orr	r2, r2, r10, asl #12
	str	r2, [r0, #-16]
	ldr	r2, [r1, #-4]
	uxtb	r10, r2
	mov	r2, r2, lsr #8
	str	r2, [r0, #-8]
	orr	r3, r3, r10, asl #18
	str	r3, [r0, #-12]
	bne	.L2334
	add	r4, r4, #96
	add	r5, r5, #96
	cmp	r6, r4
	mov	ip, lr
	bne	.L2337
	add	r8, r8, #576
	add	r9, r9, #144
	cmp	r7, r8
	mov	r4, r6
	bne	.L2339
	ldr	r3, [fp, #-52]
	add	r7, r7, #1152
	add	r3, r3, #1152
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	cmp	r7, r3
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L2333
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	2
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
	.space	2
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
	.space	3
	.type	__func__.14951, %object
	.size	__func__.14951, 19
__func__.14951:
	.ascii	"VP9_GetImageBuffer\000"
	.space	1
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
	.type	__func__.15127, %object
	.size	__func__.15127, 16
__func__.15127:
	.ascii	"VP9_Set_Segdata\000"
.LC0:
	.word	1
	.word	0
	.word	2
	.word	3
	.type	__FUNCTION__.15203, %object
	.size	__FUNCTION__.15203, 33
__FUNCTION__.15203:
	.ascii	"VP9_get_fixed_point_scale_factor\000"
	.space	3
	.type	__FUNCTION__.15232, %object
	.size	__FUNCTION__.15232, 35
__FUNCTION__.15232:
	.ascii	"Vp9_ReadBitDepthColorSpaceSampling\000"
	.space	1
	.type	__FUNCTION__.15262, %object
	.size	__FUNCTION__.15262, 25
__FUNCTION__.15262:
	.ascii	"Read_UnCompressed_Header\000"
	.space	3
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
	.space	3
	.type	__func__.15483, %object
	.size	__func__.15483, 20
__func__.15483:
	.ascii	"Vp9_DecodeTilesCtrl\000"
	.type	__func__.15342, %object
	.size	__func__.15342, 18
__func__.15342:
	.ascii	"VP9DEC_DecodeFame\000"
	.data
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 8184
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 1024
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.space	1
	.byte	84
	.byte	49
	.byte	-120
	.space	1
	.byte	8
	.byte	42
	.byte	71
	.space	1
	.space	20
	.byte	31
	.byte	107
	.byte	-87
	.space	1
	.byte	35
	.byte	99
	.byte	-97
	.space	1
	.byte	17
	.byte	82
	.byte	-116
	.space	1
	.byte	8
	.byte	66
	.byte	114
	.space	1
	.byte	2
	.byte	44
	.byte	76
	.space	1
	.byte	1
	.byte	19
	.byte	32
	.space	1
	.space	8
	.byte	40
	.byte	-124
	.byte	-55
	.space	1
	.byte	29
	.byte	114
	.byte	-69
	.space	1
	.byte	13
	.byte	91
	.byte	-99
	.space	1
	.byte	7
	.byte	75
	.byte	127
	.space	1
	.byte	3
	.byte	58
	.byte	95
	.space	1
	.byte	1
	.byte	28
	.byte	47
	.space	1
	.space	8
	.byte	69
	.byte	-114
	.byte	-35
	.space	1
	.byte	42
	.byte	122
	.byte	-55
	.space	1
	.byte	15
	.byte	91
	.byte	-97
	.space	1
	.byte	6
	.byte	67
	.byte	121
	.space	1
	.byte	1
	.byte	42
	.byte	77
	.space	1
	.byte	1
	.byte	17
	.byte	31
	.space	1
	.space	8
	.byte	102
	.byte	-108
	.byte	-28
	.space	1
	.byte	67
	.byte	117
	.byte	-52
	.space	1
	.byte	17
	.byte	82
	.byte	-102
	.space	1
	.byte	6
	.byte	59
	.byte	114
	.space	1
	.byte	2
	.byte	39
	.byte	75
	.space	1
	.byte	1
	.byte	15
	.byte	29
	.space	1
	.space	8
	.byte	-100
	.byte	57
	.byte	-23
	.space	1
	.byte	119
	.byte	57
	.byte	-44
	.space	1
	.byte	58
	.byte	48
	.byte	-93
	.space	1
	.byte	29
	.byte	40
	.byte	124
	.space	1
	.byte	12
	.byte	30
	.byte	81
	.space	1
	.byte	3
	.byte	12
	.byte	31
	.space	1
	.space	8
	.space	64
	.byte	-65
	.byte	107
	.byte	-30
	.space	1
	.byte	124
	.byte	117
	.byte	-52
	.space	1
	.byte	25
	.byte	99
	.byte	-101
	.space	1
	.space	20
	.byte	29
	.byte	-108
	.byte	-46
	.space	1
	.byte	37
	.byte	126
	.byte	-62
	.space	1
	.byte	8
	.byte	93
	.byte	-99
	.space	1
	.byte	2
	.byte	68
	.byte	118
	.space	1
	.byte	1
	.byte	39
	.byte	69
	.space	1
	.byte	1
	.byte	17
	.byte	33
	.space	1
	.space	8
	.byte	41
	.byte	-105
	.byte	-43
	.space	1
	.byte	27
	.byte	123
	.byte	-63
	.space	1
	.byte	3
	.byte	82
	.byte	-112
	.space	1
	.byte	1
	.byte	58
	.byte	105
	.space	1
	.byte	1
	.byte	32
	.byte	60
	.space	1
	.byte	1
	.byte	13
	.byte	26
	.space	1
	.space	8
	.byte	59
	.byte	-97
	.byte	-36
	.space	1
	.byte	23
	.byte	126
	.byte	-58
	.space	1
	.byte	4
	.byte	88
	.byte	-105
	.space	1
	.byte	1
	.byte	66
	.byte	114
	.space	1
	.byte	1
	.byte	38
	.byte	71
	.space	1
	.byte	1
	.byte	18
	.byte	34
	.space	1
	.space	8
	.byte	114
	.byte	-120
	.byte	-24
	.space	1
	.byte	51
	.byte	114
	.byte	-49
	.space	1
	.byte	11
	.byte	83
	.byte	-101
	.space	1
	.byte	3
	.byte	56
	.byte	105
	.space	1
	.byte	1
	.byte	33
	.byte	65
	.space	1
	.byte	1
	.byte	17
	.byte	34
	.space	1
	.space	8
	.byte	-107
	.byte	65
	.byte	-22
	.space	1
	.byte	121
	.byte	57
	.byte	-41
	.space	1
	.byte	61
	.byte	49
	.byte	-90
	.space	1
	.byte	28
	.byte	36
	.byte	114
	.space	1
	.byte	12
	.byte	25
	.byte	76
	.space	1
	.byte	3
	.byte	16
	.byte	42
	.space	1
	.space	8
	.space	64
	.byte	-42
	.byte	49
	.byte	-36
	.space	1
	.byte	-124
	.byte	63
	.byte	-68
	.space	1
	.byte	42
	.byte	65
	.byte	-119
	.space	1
	.space	20
	.byte	85
	.byte	-119
	.byte	-35
	.space	1
	.byte	104
	.byte	-125
	.byte	-40
	.space	1
	.byte	49
	.byte	111
	.byte	-64
	.space	1
	.byte	21
	.byte	87
	.byte	-101
	.space	1
	.byte	2
	.byte	49
	.byte	87
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.byte	89
	.byte	-93
	.byte	-26
	.space	1
	.byte	90
	.byte	-119
	.byte	-36
	.space	1
	.byte	29
	.byte	100
	.byte	-73
	.space	1
	.byte	10
	.byte	70
	.byte	-121
	.space	1
	.byte	2
	.byte	42
	.byte	81
	.space	1
	.byte	1
	.byte	17
	.byte	33
	.space	1
	.space	8
	.byte	108
	.byte	-89
	.byte	-19
	.space	1
	.byte	55
	.byte	-123
	.byte	-34
	.space	1
	.byte	15
	.byte	97
	.byte	-77
	.space	1
	.byte	4
	.byte	72
	.byte	-121
	.space	1
	.byte	1
	.byte	45
	.byte	85
	.space	1
	.byte	1
	.byte	19
	.byte	38
	.space	1
	.space	8
	.byte	124
	.byte	-110
	.byte	-16
	.space	1
	.byte	66
	.byte	124
	.byte	-32
	.space	1
	.byte	17
	.byte	88
	.byte	-81
	.space	1
	.byte	4
	.byte	58
	.byte	122
	.space	1
	.byte	1
	.byte	36
	.byte	75
	.space	1
	.byte	1
	.byte	18
	.byte	37
	.space	1
	.space	8
	.byte	-115
	.byte	79
	.byte	-15
	.space	1
	.byte	126
	.byte	70
	.byte	-29
	.space	1
	.byte	66
	.byte	58
	.byte	-74
	.space	1
	.byte	30
	.byte	44
	.byte	-120
	.space	1
	.byte	12
	.byte	34
	.byte	96
	.space	1
	.byte	2
	.byte	20
	.byte	47
	.space	1
	.space	8
	.space	64
	.byte	-27
	.byte	99
	.byte	-7
	.space	1
	.byte	-113
	.byte	111
	.byte	-21
	.space	1
	.byte	46
	.byte	109
	.byte	-64
	.space	1
	.space	20
	.byte	82
	.byte	-98
	.byte	-20
	.space	1
	.byte	94
	.byte	-110
	.byte	-32
	.space	1
	.byte	25
	.byte	117
	.byte	-65
	.space	1
	.byte	9
	.byte	87
	.byte	-107
	.space	1
	.byte	3
	.byte	56
	.byte	99
	.space	1
	.byte	1
	.byte	33
	.byte	57
	.space	1
	.space	8
	.byte	83
	.byte	-89
	.byte	-19
	.space	1
	.byte	68
	.byte	-111
	.byte	-34
	.space	1
	.byte	10
	.byte	103
	.byte	-79
	.space	1
	.byte	2
	.byte	72
	.byte	-125
	.space	1
	.byte	1
	.byte	41
	.byte	79
	.space	1
	.byte	1
	.byte	20
	.byte	39
	.space	1
	.space	8
	.byte	99
	.byte	-89
	.byte	-17
	.space	1
	.byte	47
	.byte	-115
	.byte	-32
	.space	1
	.byte	10
	.byte	104
	.byte	-78
	.space	1
	.byte	2
	.byte	73
	.byte	-123
	.space	1
	.byte	1
	.byte	44
	.byte	85
	.space	1
	.byte	1
	.byte	22
	.byte	47
	.space	1
	.space	8
	.byte	127
	.byte	-111
	.byte	-13
	.space	1
	.byte	71
	.byte	-127
	.byte	-28
	.space	1
	.byte	17
	.byte	93
	.byte	-79
	.space	1
	.byte	3
	.byte	61
	.byte	124
	.space	1
	.byte	1
	.byte	41
	.byte	84
	.space	1
	.byte	1
	.byte	21
	.byte	52
	.space	1
	.space	8
	.byte	-99
	.byte	78
	.byte	-12
	.space	1
	.byte	-116
	.byte	72
	.byte	-25
	.space	1
	.byte	69
	.byte	58
	.byte	-72
	.space	1
	.byte	31
	.byte	44
	.byte	-119
	.space	1
	.byte	14
	.byte	38
	.byte	105
	.space	1
	.byte	8
	.byte	23
	.byte	61
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 1024
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.space	1
	.byte	52
	.byte	41
	.byte	-123
	.space	1
	.byte	6
	.byte	31
	.byte	56
	.space	1
	.space	20
	.byte	37
	.byte	109
	.byte	-103
	.space	1
	.byte	51
	.byte	102
	.byte	-109
	.space	1
	.byte	23
	.byte	87
	.byte	-128
	.space	1
	.byte	8
	.byte	67
	.byte	101
	.space	1
	.byte	1
	.byte	41
	.byte	63
	.space	1
	.byte	1
	.byte	19
	.byte	29
	.space	1
	.space	8
	.byte	31
	.byte	-102
	.byte	-71
	.space	1
	.byte	17
	.byte	127
	.byte	-81
	.space	1
	.byte	6
	.byte	96
	.byte	-111
	.space	1
	.byte	2
	.byte	73
	.byte	114
	.space	1
	.byte	1
	.byte	51
	.byte	82
	.space	1
	.byte	1
	.byte	28
	.byte	45
	.space	1
	.space	8
	.byte	23
	.byte	-93
	.byte	-56
	.space	1
	.byte	10
	.byte	-125
	.byte	-71
	.space	1
	.byte	2
	.byte	93
	.byte	-108
	.space	1
	.byte	1
	.byte	67
	.byte	111
	.space	1
	.byte	1
	.byte	41
	.byte	69
	.space	1
	.byte	1
	.byte	14
	.byte	24
	.space	1
	.space	8
	.byte	29
	.byte	-80
	.byte	-39
	.space	1
	.byte	12
	.byte	-111
	.byte	-55
	.space	1
	.byte	3
	.byte	101
	.byte	-100
	.space	1
	.byte	1
	.byte	69
	.byte	111
	.space	1
	.byte	1
	.byte	39
	.byte	63
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	57
	.byte	-64
	.byte	-23
	.space	1
	.byte	25
	.byte	-102
	.byte	-41
	.space	1
	.byte	6
	.byte	109
	.byte	-89
	.space	1
	.byte	3
	.byte	78
	.byte	118
	.space	1
	.byte	1
	.byte	48
	.byte	69
	.space	1
	.byte	1
	.byte	21
	.byte	29
	.space	1
	.space	8
	.space	64
	.byte	-54
	.byte	105
	.byte	-11
	.space	1
	.byte	108
	.byte	106
	.byte	-40
	.space	1
	.byte	18
	.byte	90
	.byte	-112
	.space	1
	.space	20
	.byte	33
	.byte	-84
	.byte	-37
	.space	1
	.byte	64
	.byte	-107
	.byte	-50
	.space	1
	.byte	14
	.byte	117
	.byte	-79
	.space	1
	.byte	5
	.byte	90
	.byte	-115
	.space	1
	.byte	2
	.byte	61
	.byte	95
	.space	1
	.byte	1
	.byte	37
	.byte	57
	.space	1
	.space	8
	.byte	33
	.byte	-77
	.byte	-36
	.space	1
	.byte	11
	.byte	-116
	.byte	-58
	.space	1
	.byte	1
	.byte	89
	.byte	-108
	.space	1
	.byte	1
	.byte	60
	.byte	104
	.space	1
	.byte	1
	.byte	33
	.byte	57
	.space	1
	.byte	1
	.byte	12
	.byte	21
	.space	1
	.space	8
	.byte	30
	.byte	-75
	.byte	-35
	.space	1
	.byte	8
	.byte	-115
	.byte	-58
	.space	1
	.byte	1
	.byte	87
	.byte	-111
	.space	1
	.byte	1
	.byte	58
	.byte	100
	.space	1
	.byte	1
	.byte	31
	.byte	55
	.space	1
	.byte	1
	.byte	12
	.byte	20
	.space	1
	.space	8
	.byte	32
	.byte	-70
	.byte	-32
	.space	1
	.byte	7
	.byte	-114
	.byte	-58
	.space	1
	.byte	1
	.byte	86
	.byte	-113
	.space	1
	.byte	1
	.byte	58
	.byte	100
	.space	1
	.byte	1
	.byte	31
	.byte	55
	.space	1
	.byte	1
	.byte	12
	.byte	22
	.space	1
	.space	8
	.byte	57
	.byte	-64
	.byte	-29
	.space	1
	.byte	20
	.byte	-113
	.byte	-52
	.space	1
	.byte	3
	.byte	96
	.byte	-102
	.space	1
	.byte	1
	.byte	68
	.byte	112
	.space	1
	.byte	1
	.byte	42
	.byte	69
	.space	1
	.byte	1
	.byte	19
	.byte	32
	.space	1
	.space	8
	.space	64
	.byte	-44
	.byte	35
	.byte	-41
	.space	1
	.byte	113
	.byte	47
	.byte	-87
	.space	1
	.byte	29
	.byte	48
	.byte	105
	.space	1
	.space	20
	.byte	74
	.byte	-127
	.byte	-53
	.space	1
	.byte	106
	.byte	120
	.byte	-53
	.space	1
	.byte	49
	.byte	107
	.byte	-78
	.space	1
	.byte	19
	.byte	84
	.byte	-112
	.space	1
	.byte	4
	.byte	50
	.byte	84
	.space	1
	.byte	1
	.byte	15
	.byte	25
	.space	1
	.space	8
	.byte	71
	.byte	-84
	.byte	-39
	.space	1
	.byte	44
	.byte	-115
	.byte	-47
	.space	1
	.byte	15
	.byte	102
	.byte	-83
	.space	1
	.byte	6
	.byte	76
	.byte	-123
	.space	1
	.byte	2
	.byte	51
	.byte	89
	.space	1
	.byte	1
	.byte	24
	.byte	42
	.space	1
	.space	8
	.byte	64
	.byte	-71
	.byte	-25
	.space	1
	.byte	31
	.byte	-108
	.byte	-40
	.space	1
	.byte	8
	.byte	103
	.byte	-81
	.space	1
	.byte	3
	.byte	74
	.byte	-125
	.space	1
	.byte	1
	.byte	46
	.byte	81
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-60
	.byte	-21
	.space	1
	.byte	25
	.byte	-99
	.byte	-35
	.space	1
	.byte	5
	.byte	105
	.byte	-82
	.space	1
	.byte	1
	.byte	67
	.byte	120
	.space	1
	.byte	1
	.byte	38
	.byte	69
	.space	1
	.byte	1
	.byte	15
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-52
	.byte	-18
	.space	1
	.byte	30
	.byte	-100
	.byte	-32
	.space	1
	.byte	7
	.byte	107
	.byte	-79
	.space	1
	.byte	2
	.byte	70
	.byte	124
	.space	1
	.byte	1
	.byte	42
	.byte	73
	.space	1
	.byte	1
	.byte	18
	.byte	34
	.space	1
	.space	8
	.space	64
	.byte	-31
	.byte	86
	.byte	-5
	.space	1
	.byte	-112
	.byte	104
	.byte	-21
	.space	1
	.byte	42
	.byte	99
	.byte	-75
	.space	1
	.space	20
	.byte	85
	.byte	-81
	.byte	-17
	.space	1
	.byte	112
	.byte	-91
	.byte	-27
	.space	1
	.byte	29
	.byte	-120
	.byte	-56
	.space	1
	.byte	12
	.byte	103
	.byte	-94
	.space	1
	.byte	6
	.byte	77
	.byte	123
	.space	1
	.byte	2
	.byte	53
	.byte	84
	.space	1
	.space	8
	.byte	75
	.byte	-73
	.byte	-17
	.space	1
	.byte	30
	.byte	-101
	.byte	-35
	.space	1
	.byte	3
	.byte	106
	.byte	-85
	.space	1
	.byte	1
	.byte	74
	.byte	-128
	.space	1
	.byte	1
	.byte	44
	.byte	76
	.space	1
	.byte	1
	.byte	17
	.byte	28
	.space	1
	.space	8
	.byte	73
	.byte	-71
	.byte	-16
	.space	1
	.byte	27
	.byte	-97
	.byte	-34
	.space	1
	.byte	2
	.byte	107
	.byte	-84
	.space	1
	.byte	1
	.byte	75
	.byte	127
	.space	1
	.byte	1
	.byte	42
	.byte	73
	.space	1
	.byte	1
	.byte	17
	.byte	29
	.space	1
	.space	8
	.byte	62
	.byte	-66
	.byte	-18
	.space	1
	.byte	21
	.byte	-97
	.byte	-34
	.space	1
	.byte	2
	.byte	107
	.byte	-84
	.space	1
	.byte	1
	.byte	72
	.byte	122
	.space	1
	.byte	1
	.byte	40
	.byte	71
	.space	1
	.byte	1
	.byte	18
	.byte	32
	.space	1
	.space	8
	.byte	61
	.byte	-57
	.byte	-16
	.space	1
	.byte	27
	.byte	-95
	.byte	-30
	.space	1
	.byte	4
	.byte	113
	.byte	-76
	.space	1
	.byte	1
	.byte	76
	.byte	-127
	.space	1
	.byte	1
	.byte	46
	.byte	80
	.space	1
	.byte	1
	.byte	23
	.byte	41
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 1024
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.space	1
	.byte	5
	.byte	30
	.byte	95
	.space	1
	.byte	1
	.byte	16
	.byte	30
	.space	1
	.space	20
	.byte	50
	.byte	75
	.byte	127
	.space	1
	.byte	57
	.byte	75
	.byte	124
	.space	1
	.byte	27
	.byte	67
	.byte	108
	.space	1
	.byte	10
	.byte	54
	.byte	86
	.space	1
	.byte	1
	.byte	33
	.byte	52
	.space	1
	.byte	1
	.byte	12
	.byte	18
	.space	1
	.space	8
	.byte	43
	.byte	125
	.byte	-105
	.space	1
	.byte	26
	.byte	108
	.byte	-108
	.space	1
	.byte	7
	.byte	83
	.byte	122
	.space	1
	.byte	2
	.byte	59
	.byte	89
	.space	1
	.byte	1
	.byte	38
	.byte	60
	.space	1
	.byte	1
	.byte	17
	.byte	27
	.space	1
	.space	8
	.byte	23
	.byte	-112
	.byte	-93
	.space	1
	.byte	13
	.byte	112
	.byte	-102
	.space	1
	.byte	2
	.byte	75
	.byte	117
	.space	1
	.byte	1
	.byte	50
	.byte	81
	.space	1
	.byte	1
	.byte	31
	.byte	51
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	18
	.byte	-94
	.byte	-71
	.space	1
	.byte	6
	.byte	123
	.byte	-85
	.space	1
	.byte	1
	.byte	78
	.byte	125
	.space	1
	.byte	1
	.byte	51
	.byte	86
	.space	1
	.byte	1
	.byte	31
	.byte	54
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	15
	.byte	-57
	.byte	-29
	.space	1
	.byte	3
	.byte	-106
	.byte	-52
	.space	1
	.byte	1
	.byte	91
	.byte	-110
	.space	1
	.byte	1
	.byte	55
	.byte	95
	.space	1
	.byte	1
	.byte	30
	.byte	53
	.space	1
	.byte	1
	.byte	11
	.byte	20
	.space	1
	.space	8
	.space	64
	.byte	19
	.byte	55
	.byte	-16
	.space	1
	.byte	19
	.byte	59
	.byte	-60
	.space	1
	.byte	3
	.byte	52
	.byte	105
	.space	1
	.space	20
	.byte	41
	.byte	-90
	.byte	-49
	.space	1
	.byte	104
	.byte	-103
	.byte	-57
	.space	1
	.byte	31
	.byte	123
	.byte	-75
	.space	1
	.byte	14
	.byte	101
	.byte	-104
	.space	1
	.byte	5
	.byte	72
	.byte	106
	.space	1
	.byte	1
	.byte	36
	.byte	52
	.space	1
	.space	8
	.byte	35
	.byte	-80
	.byte	-45
	.space	1
	.byte	12
	.byte	-125
	.byte	-66
	.space	1
	.byte	2
	.byte	88
	.byte	-112
	.space	1
	.byte	1
	.byte	60
	.byte	101
	.space	1
	.byte	1
	.byte	36
	.byte	60
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.byte	28
	.byte	-73
	.byte	-43
	.space	1
	.byte	8
	.byte	-122
	.byte	-65
	.space	1
	.byte	1
	.byte	86
	.byte	-114
	.space	1
	.byte	1
	.byte	56
	.byte	96
	.space	1
	.byte	1
	.byte	30
	.byte	53
	.space	1
	.byte	1
	.byte	12
	.byte	20
	.space	1
	.space	8
	.byte	20
	.byte	-66
	.byte	-41
	.space	1
	.byte	4
	.byte	-121
	.byte	-64
	.space	1
	.byte	1
	.byte	84
	.byte	-117
	.space	1
	.byte	1
	.byte	53
	.byte	91
	.space	1
	.byte	1
	.byte	28
	.byte	49
	.space	1
	.byte	1
	.byte	11
	.byte	20
	.space	1
	.space	8
	.byte	13
	.byte	-60
	.byte	-40
	.space	1
	.byte	2
	.byte	-119
	.byte	-64
	.space	1
	.byte	1
	.byte	86
	.byte	-113
	.space	1
	.byte	1
	.byte	57
	.byte	99
	.space	1
	.byte	1
	.byte	32
	.byte	56
	.space	1
	.byte	1
	.byte	13
	.byte	24
	.space	1
	.space	8
	.space	64
	.byte	-45
	.byte	29
	.byte	-39
	.space	1
	.byte	96
	.byte	47
	.byte	-100
	.space	1
	.byte	22
	.byte	43
	.byte	87
	.space	1
	.space	20
	.byte	78
	.byte	120
	.byte	-63
	.space	1
	.byte	111
	.byte	116
	.byte	-70
	.space	1
	.byte	46
	.byte	102
	.byte	-92
	.space	1
	.byte	15
	.byte	80
	.byte	-128
	.space	1
	.byte	2
	.byte	49
	.byte	76
	.space	1
	.byte	1
	.byte	18
	.byte	28
	.space	1
	.space	8
	.byte	71
	.byte	-95
	.byte	-53
	.space	1
	.byte	42
	.byte	-124
	.byte	-64
	.space	1
	.byte	10
	.byte	98
	.byte	-106
	.space	1
	.byte	3
	.byte	69
	.byte	109
	.space	1
	.byte	1
	.byte	44
	.byte	70
	.space	1
	.byte	1
	.byte	18
	.byte	29
	.space	1
	.space	8
	.byte	57
	.byte	-70
	.byte	-45
	.space	1
	.byte	30
	.byte	-116
	.byte	-60
	.space	1
	.byte	4
	.byte	93
	.byte	-110
	.space	1
	.byte	1
	.byte	62
	.byte	102
	.space	1
	.byte	1
	.byte	38
	.byte	65
	.space	1
	.byte	1
	.byte	16
	.byte	27
	.space	1
	.space	8
	.byte	47
	.byte	-57
	.byte	-39
	.space	1
	.byte	14
	.byte	-111
	.byte	-60
	.space	1
	.byte	1
	.byte	88
	.byte	-114
	.space	1
	.byte	1
	.byte	57
	.byte	98
	.space	1
	.byte	1
	.byte	36
	.byte	62
	.space	1
	.byte	1
	.byte	15
	.byte	26
	.space	1
	.space	8
	.byte	26
	.byte	-37
	.byte	-27
	.space	1
	.byte	5
	.byte	-101
	.byte	-49
	.space	1
	.byte	1
	.byte	94
	.byte	-105
	.space	1
	.byte	1
	.byte	60
	.byte	104
	.space	1
	.byte	1
	.byte	36
	.byte	62
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.space	64
	.byte	-23
	.byte	29
	.byte	-8
	.space	1
	.byte	-110
	.byte	47
	.byte	-36
	.space	1
	.byte	43
	.byte	52
	.byte	-116
	.space	1
	.space	20
	.byte	100
	.byte	-93
	.byte	-24
	.space	1
	.byte	-77
	.byte	-95
	.byte	-34
	.space	1
	.byte	63
	.byte	-114
	.byte	-52
	.space	1
	.byte	37
	.byte	113
	.byte	-82
	.space	1
	.byte	26
	.byte	89
	.byte	-119
	.space	1
	.byte	18
	.byte	68
	.byte	97
	.space	1
	.space	8
	.byte	85
	.byte	-75
	.byte	-26
	.space	1
	.byte	32
	.byte	-110
	.byte	-47
	.space	1
	.byte	7
	.byte	100
	.byte	-92
	.space	1
	.byte	3
	.byte	71
	.byte	121
	.space	1
	.byte	1
	.byte	45
	.byte	77
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-69
	.byte	-26
	.space	1
	.byte	20
	.byte	-108
	.byte	-49
	.space	1
	.byte	2
	.byte	97
	.byte	-97
	.space	1
	.byte	1
	.byte	68
	.byte	116
	.space	1
	.byte	1
	.byte	40
	.byte	70
	.space	1
	.byte	1
	.byte	14
	.byte	29
	.space	1
	.space	8
	.byte	40
	.byte	-62
	.byte	-29
	.space	1
	.byte	8
	.byte	-109
	.byte	-52
	.space	1
	.byte	1
	.byte	94
	.byte	-101
	.space	1
	.byte	1
	.byte	65
	.byte	112
	.space	1
	.byte	1
	.byte	39
	.byte	66
	.space	1
	.byte	1
	.byte	14
	.byte	26
	.space	1
	.space	8
	.byte	16
	.byte	-48
	.byte	-28
	.space	1
	.byte	3
	.byte	-105
	.byte	-49
	.space	1
	.byte	1
	.byte	98
	.byte	-96
	.space	1
	.byte	1
	.byte	67
	.byte	117
	.space	1
	.byte	1
	.byte	41
	.byte	74
	.space	1
	.byte	1
	.byte	17
	.byte	31
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 1024
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.space	1
	.byte	7
	.byte	34
	.byte	80
	.space	1
	.byte	1
	.byte	17
	.byte	29
	.space	1
	.space	20
	.byte	37
	.byte	75
	.byte	-128
	.space	1
	.byte	41
	.byte	76
	.byte	-128
	.space	1
	.byte	26
	.byte	66
	.byte	116
	.space	1
	.byte	12
	.byte	52
	.byte	94
	.space	1
	.byte	2
	.byte	32
	.byte	55
	.space	1
	.byte	1
	.byte	10
	.byte	16
	.space	1
	.space	8
	.byte	50
	.byte	127
	.byte	-102
	.space	1
	.byte	37
	.byte	109
	.byte	-104
	.space	1
	.byte	16
	.byte	82
	.byte	121
	.space	1
	.byte	5
	.byte	59
	.byte	85
	.space	1
	.byte	1
	.byte	35
	.byte	54
	.space	1
	.byte	1
	.byte	13
	.byte	20
	.space	1
	.space	8
	.byte	40
	.byte	-114
	.byte	-89
	.space	1
	.byte	17
	.byte	110
	.byte	-99
	.space	1
	.byte	2
	.byte	71
	.byte	112
	.space	1
	.byte	1
	.byte	44
	.byte	72
	.space	1
	.byte	1
	.byte	27
	.byte	45
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.byte	30
	.byte	-81
	.byte	-68
	.space	1
	.byte	9
	.byte	124
	.byte	-87
	.space	1
	.byte	1
	.byte	74
	.byte	116
	.space	1
	.byte	1
	.byte	48
	.byte	78
	.space	1
	.byte	1
	.byte	30
	.byte	49
	.space	1
	.byte	1
	.byte	11
	.byte	18
	.space	1
	.space	8
	.byte	10
	.byte	-34
	.byte	-33
	.space	1
	.byte	2
	.byte	-106
	.byte	-62
	.space	1
	.byte	1
	.byte	83
	.byte	-128
	.space	1
	.byte	1
	.byte	48
	.byte	79
	.space	1
	.byte	1
	.byte	27
	.byte	45
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.space	64
	.byte	36
	.byte	41
	.byte	-21
	.space	1
	.byte	29
	.byte	36
	.byte	-63
	.space	1
	.byte	10
	.byte	27
	.byte	111
	.space	1
	.space	20
	.byte	85
	.byte	-91
	.byte	-34
	.space	1
	.byte	-79
	.byte	-94
	.byte	-41
	.space	1
	.byte	110
	.byte	-121
	.byte	-61
	.space	1
	.byte	57
	.byte	113
	.byte	-88
	.space	1
	.byte	23
	.byte	83
	.byte	120
	.space	1
	.byte	10
	.byte	49
	.byte	61
	.space	1
	.space	8
	.byte	85
	.byte	-66
	.byte	-33
	.space	1
	.byte	36
	.byte	-117
	.byte	-56
	.space	1
	.byte	5
	.byte	90
	.byte	-110
	.space	1
	.byte	1
	.byte	60
	.byte	103
	.space	1
	.byte	1
	.byte	38
	.byte	65
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	72
	.byte	-54
	.byte	-33
	.space	1
	.byte	23
	.byte	-115
	.byte	-57
	.space	1
	.byte	2
	.byte	86
	.byte	-116
	.space	1
	.byte	1
	.byte	56
	.byte	97
	.space	1
	.byte	1
	.byte	36
	.byte	61
	.space	1
	.byte	1
	.byte	16
	.byte	27
	.space	1
	.space	8
	.byte	55
	.byte	-38
	.byte	-31
	.space	1
	.byte	13
	.byte	-111
	.byte	-56
	.space	1
	.byte	1
	.byte	86
	.byte	-115
	.space	1
	.byte	1
	.byte	57
	.byte	99
	.space	1
	.byte	1
	.byte	35
	.byte	61
	.space	1
	.byte	1
	.byte	13
	.byte	22
	.space	1
	.space	8
	.byte	15
	.byte	-21
	.byte	-44
	.space	1
	.byte	1
	.byte	-124
	.byte	-72
	.space	1
	.byte	1
	.byte	84
	.byte	-117
	.space	1
	.byte	1
	.byte	57
	.byte	97
	.space	1
	.byte	1
	.byte	34
	.byte	56
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.space	64
	.byte	-75
	.byte	21
	.byte	-55
	.space	1
	.byte	61
	.byte	37
	.byte	123
	.space	1
	.byte	10
	.byte	38
	.byte	71
	.space	1
	.space	20
	.byte	47
	.byte	106
	.byte	-84
	.space	1
	.byte	95
	.byte	104
	.byte	-83
	.space	1
	.byte	42
	.byte	93
	.byte	-97
	.space	1
	.byte	18
	.byte	77
	.byte	-125
	.space	1
	.byte	4
	.byte	50
	.byte	81
	.space	1
	.byte	1
	.byte	17
	.byte	23
	.space	1
	.space	8
	.byte	62
	.byte	-109
	.byte	-57
	.space	1
	.byte	44
	.byte	-126
	.byte	-67
	.space	1
	.byte	28
	.byte	102
	.byte	-102
	.space	1
	.byte	18
	.byte	75
	.byte	115
	.space	1
	.byte	2
	.byte	44
	.byte	65
	.space	1
	.byte	1
	.byte	12
	.byte	19
	.space	1
	.space	8
	.byte	55
	.byte	-103
	.byte	-46
	.space	1
	.byte	24
	.byte	-126
	.byte	-62
	.space	1
	.byte	3
	.byte	93
	.byte	-110
	.space	1
	.byte	1
	.byte	61
	.byte	97
	.space	1
	.byte	1
	.byte	31
	.byte	50
	.space	1
	.byte	1
	.byte	10
	.byte	16
	.space	1
	.space	8
	.byte	49
	.byte	-70
	.byte	-33
	.space	1
	.byte	17
	.byte	-108
	.byte	-52
	.space	1
	.byte	1
	.byte	96
	.byte	-114
	.space	1
	.byte	1
	.byte	53
	.byte	83
	.space	1
	.byte	1
	.byte	26
	.byte	44
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.byte	13
	.byte	-39
	.byte	-44
	.space	1
	.byte	2
	.byte	-120
	.byte	-76
	.space	1
	.byte	1
	.byte	78
	.byte	124
	.space	1
	.byte	1
	.byte	50
	.byte	83
	.space	1
	.byte	1
	.byte	29
	.byte	49
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.space	64
	.byte	-59
	.byte	13
	.byte	-9
	.space	1
	.byte	82
	.byte	17
	.byte	-34
	.space	1
	.byte	25
	.byte	17
	.byte	-94
	.space	1
	.space	20
	.byte	126
	.byte	-70
	.byte	-9
	.space	1
	.byte	-22
	.byte	-65
	.byte	-13
	.space	1
	.byte	-80
	.byte	-79
	.byte	-22
	.space	1
	.byte	104
	.byte	-98
	.byte	-36
	.space	1
	.byte	66
	.byte	-128
	.byte	-70
	.space	1
	.byte	55
	.byte	90
	.byte	-119
	.space	1
	.space	8
	.byte	111
	.byte	-59
	.byte	-14
	.space	1
	.byte	46
	.byte	-98
	.byte	-37
	.space	1
	.byte	9
	.byte	104
	.byte	-85
	.space	1
	.byte	2
	.byte	65
	.byte	125
	.space	1
	.byte	1
	.byte	44
	.byte	80
	.space	1
	.byte	1
	.byte	17
	.byte	91
	.space	1
	.space	8
	.byte	104
	.byte	-48
	.byte	-11
	.space	1
	.byte	39
	.byte	-88
	.byte	-32
	.space	1
	.byte	3
	.byte	109
	.byte	-94
	.space	1
	.byte	1
	.byte	79
	.byte	124
	.space	1
	.byte	1
	.byte	50
	.byte	102
	.space	1
	.byte	1
	.byte	43
	.byte	102
	.space	1
	.space	8
	.byte	84
	.byte	-36
	.byte	-10
	.space	1
	.byte	31
	.byte	-79
	.byte	-25
	.space	1
	.byte	2
	.byte	115
	.byte	-76
	.space	1
	.byte	1
	.byte	79
	.byte	-122
	.space	1
	.byte	1
	.byte	55
	.byte	77
	.space	1
	.byte	1
	.byte	60
	.byte	79
	.space	1
	.space	8
	.byte	43
	.byte	-13
	.byte	-16
	.space	1
	.byte	8
	.byte	-76
	.byte	-39
	.space	1
	.byte	1
	.byte	115
	.byte	-90
	.space	1
	.byte	1
	.byte	84
	.byte	121
	.space	1
	.byte	1
	.byte	51
	.byte	67
	.space	1
	.byte	1
	.byte	16
	.byte	6
	.space	1
	.space	8
	.space	64
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
	.type	vp9_default_comp_inter_p, %object
	.size	vp9_default_comp_inter_p, 5
vp9_default_comp_inter_p:
	.byte	-17
	.byte	-73
	.byte	119
	.byte	96
	.byte	41
	.space	3
	.type	vp9_default_comp_ref_p, %object
	.size	vp9_default_comp_ref_p, 5
vp9_default_comp_ref_p:
	.byte	50
	.byte	126
	.byte	123
	.byte	-35
	.byte	-30
	.space	3
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
	.space	2
	.type	vp9_default_mbskip_probs, %object
	.size	vp9_default_mbskip_probs, 3
vp9_default_mbskip_probs:
	.byte	-64
	.byte	-128
	.byte	64
	.space	1
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
	.space	3
	.type	g_CfgVp9FrmNum, %object
	.size	g_CfgVp9FrmNum, 4
g_CfgVp9FrmNum:
	.word	16
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"IN VP9DEC_Init\012\000" )
.LC2:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC3:
	ASCII(.ascii	"data_sz == 0\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"line: %d, fs is NULL!\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"%s  idx=%d\012\000" )
.LC10:
	ASCII(.ascii	"FSP_GetLogicFs err\000" )
	.space	1
.LC11:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC14:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC15:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"pu8ProbCntVir == NULL\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"Invalid frame sync code\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"ref_deltas\000" )
	.space	1
.LC19:
	ASCII(.ascii	"mode_deltas\000" )
.LC20:
	ASCII(.ascii	"delta_q\000" )
.LC21:
	ASCII(.ascii	"%s  %d ERR\012\000" )
.LC22:
	ASCII(.ascii	"%s:%d this_size:%d is invalid!\012\000" )
.LC23:
	ASCII(.ascii	"4:4:4 color is not supported in profile 0 or 2 (%s " )
	ASCII(.ascii	": %d)\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"Invalid frame marker\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"%s:%d w&h=%dx%d is invalid!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"VP9_Set_DecParam but logic fs is null!\012\000" )
.LC27:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC28:
	ASCII(.ascii	"VP9_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC30:
	ASCII(.ascii	"pic_width_in_pix:%d, pic_height_in_pix:%d\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"vp9 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"vp9 alloc frame only\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"%s:%d size is invalid  size:%d bslen:%d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"ERROR:Vp9_ReadCompressedHeader\012\000" )
.LC37:
	ASCII(.ascii	"get_free_fb failed!\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"bit_depth(%d) > 10.\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"ERROR: pCtx->StreamParam.Length(%d) < 8\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\012\000" )
.LC41:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"%s %d, no fsp\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"VP9_GetImageBuffer From Queue err\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"ERROR: VP9_Set_DecParam\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"VP9_DecOneNal ERR\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
