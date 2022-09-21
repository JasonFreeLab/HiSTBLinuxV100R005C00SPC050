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
	.global	__aeabi_uidiv
	.text
	.align	2
	.type	Vp9_ModeMvMergeProbs, %function
Vp9_ModeMvMergeProbs:
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
	mov	r4, r0
	ldmia	r1, {r0, r1}
	adds	r3, r0, r1
	beq	.L3
	cmp	r3, #20
	ldr	r2, .L5
	mov	r0, r0, asl #8
	mov	r1, r3
	add	r0, r0, r3, lsr #1
	movcs	r3, #20
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	rsb	r3, r5, #256
	mul	r4, r4, r3
	add	r3, r4, #128
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
	mla	r0, r5, r0, r3
	ubfx	r0, r0, #8, #8
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ModeMvMergeProbs, .-Vp9_ModeMvMergeProbs
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
	beq	.L13
	cmp	r1, #0
	ble	.L14
	add	r0, r0, r1
	cmp	r2, r0
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L14:
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
	blt	.L17
	ldr	r3, [r0, #28]
.L18:
	mov	r2, r4, asl #24
	cmp	r2, r3
	rsbls	r3, r2, r3
	ldr	r2, .L21
	ldrls	r1, [r5, #36]
	movls	r0, #1
	movhi	r0, #0
	rsbls	r4, r4, r1
	add	r2, r2, r4
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r1
	rsb	r7, r1, r7
	mov	r4, r4, asl r1
	str	r3, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L17:
	rsb	r1, r7, #24
	rsb	r8, r7, #16
	bic	r1, r1, #7
	ldr	r6, [r0, #28]
	rsb	r8, r1, r8
	add	r7, r7, r1
	bl	BsGet
	and	r3, r8, #7
	orr	r3, r6, r0, asl r3
	b	.L18
.L22:
	.align	2
.L21:
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
	bmi	.L28
	ldr	r8, [r0, #28]
	mov	r9, #0
	ldr	r4, [r0, #36]
	mov	r3, #1
	ldr	r5, [r0, #32]
	ldr	r10, .L32
	b	.L27
.L25:
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
	add	r2, r10, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L24
.L27:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L25
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
	b	.L25
.L28:
	mov	r9, #0
.L24:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L33:
	.align	2
.L32:
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
	ldr	r1, .L37
	rsbcs	r3, r3, r0
	movcc	r0, r5
	add	r1, r1, r3
	movcs	r0, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r1
	mov	r3, r3, asl r1
	str	r2, [r4, #28]
	rsb	r1, r1, #24
	str	r3, [r4, #36]
	str	r1, [r4, #32]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L38:
	.align	2
.L37:
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
	ldr	r10, .L53
	ldr	r4, [r0, #36]
	mov	r3, r7
	ldr	r5, [r0, #32]
	mov	r9, #0
	ldr	r8, [r0, #28]
	b	.L42
.L40:
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
	add	r2, r10, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L50
.L42:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L40
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
	b	.L40
.L50:
	cmp	r9, #3
	beq	.L51
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L51:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	movge	r0, r8
	blt	.L52
.L44:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r9, #4
	rsbls	r4, r4, r2
	add	r10, r10, r4
	ldrb	r3, [r10, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	mov	r0, r9
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L52:
	rsb	r1, r5, #24
	rsb	r7, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r7, r1, r7
	add	r5, r1, r5
	bl	BsGet
	and	r7, r7, #7
	orr	r0, r8, r0, asl r7
	b	.L44
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
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
	blt	.L57
	ldr	r8, [r0, #28]
.L58:
	mov	r3, r4, asl #24
	cmp	r3, r8
	bhi	.L59
	ldr	r2, [r6, #36]
	rsb	r8, r3, r8
	ldr	r3, .L112
	rsb	r4, r4, r2
	add	r2, r3, r4
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
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
	blt	.L106
.L61:
	mov	r1, r5, asl #24
	cmp	r1, r8
	bhi	.L66
	ldr	r2, [r6, #36]
	rsb	r8, r1, r8
	rsb	r5, r5, r2
	add	r2, r3, r5
	ldrb	ip, [r2, #24]	@ zero_extendqisi2
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
	blt	.L107
.L68:
	mov	r1, r4, asl #24
	cmp	r1, r8
	bhi	.L72
	ldr	r2, [r6, #36]
	rsb	r8, r1, r8
	mov	r7, #0
	mov	r10, #6
	rsb	r1, r4, r2
	mov	r2, #1
	add	r0, r3, r1
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r6, #28]
	mov	r4, r1, asl r4
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L73
.L77:
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
	add	r1, r3, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L108
.L73:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L77
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
	b	.L77
.L66:
	add	r1, r3, r5
	mov	r7, #0
	mov	r10, #3
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L71
.L69:
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
	add	r1, r3, r5
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L109
.L71:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L69
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
	b	.L69
.L59:
	ldr	r3, .L112
	mov	r7, #0
	mov	r10, #3
	mov	r2, #1
	add	r1, r3, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L64
.L62:
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
	add	r1, r3, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L65
.L64:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L62
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
	b	.L62
.L108:
	cmp	r7, #64
	ble	.L79
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl #1
	add	r4, r4, #1
	sub	r7, r7, #65
	movge	r0, r8
	blt	.L110
.L80:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r7, r7, r1
	rsbls	r4, r4, ip
	add	r2, r3, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
.L79:
	add	r7, r7, #64
.L65:
	ldrb	r2, [r9]	@ zero_extendqisi2
	add	r3, r3, r7
	sub	ip, r2, #1
	ldrb	r1, [r3, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L82
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L83
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L83:
	add	r3, r3, #1
	strb	r3, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L82:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L86
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L86:
	rsb	r3, r3, #255
	strb	r3, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L109:
	add	r7, r7, #16
	b	.L65
.L72:
	add	r1, r3, r4
	mov	r7, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	str	r8, [r6, #28]
	mov	r1, r4, asl r1
	str	r5, [r6, #32]
	str	r1, [r6, #36]
	b	.L76
.L74:
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
	add	r1, r3, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r5, r1, r5
	str	r8, [r6, #28]
	mov	r1, r4, asl r1
	str	r5, [r6, #32]
	str	r1, [r6, #36]
	beq	.L111
.L76:
	sub	r1, r1, #1
	cmp	r5, #0
	ubfx	r1, r1, #1, #24
	mov	r0, r8
	add	r4, r1, #1
	bge	.L74
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
	b	.L74
.L111:
	add	r7, r7, #32
	b	.L65
.L57:
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
	b	.L58
.L106:
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
	b	.L61
.L107:
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
	b	.L68
.L110:
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
	b	.L80
.L113:
	.align	2
.L112:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
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
	ldr	r7, .L400
	ldr	r4, [r1, #28]
	add	r8, r0, #10
	ldr	r3, [r1, #36]
	mov	r6, r1
	ldr	r5, [r1, #32]
	add	r2, r0, #12
	str	r0, [fp, #-52]
	str	r2, [fp, #-48]
.L145:
	sub	r10, r3, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L354
.L115:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L116
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L355
.L117:
	mov	r3, r4, asl #24
	cmp	r3, r9
	bhi	.L118
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r4, r4, r2
	add	r3, r7, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L356
.L120:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L125
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r1, r5, asl r2
	rsb	r5, r2, r4
	sub	r9, r1, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r4, [r6, #28]
	blt	.L357
.L127:
	mov	r3, r9, asl #24
	cmp	r3, r4
	bhi	.L131
	ldr	r1, [r6, #36]
	rsb	r0, r3, r4
	mov	r2, #6
	mov	r3, #0
	rsb	r4, r9, r1
	str	r8, [fp, #-64]
	add	r1, r7, r4
	mov	ip, #1
	mov	r8, r3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r10, r1, r5
	mov	r9, r0, asl r1
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	b	.L132
.L136:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	str	r4, [r6, #36]
	beq	.L358
.L132:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L136
	rsb	r1, r10, #24
	rsb	r2, r10, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r10, r1, r10
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r9, r0, asl r2
	b	.L136
.L116:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r10, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
.L271:
	ldr	r2, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r2
	bne	.L145
	ldr	r2, [fp, #-52]
	add	r1, r2, #4
	str	r1, [fp, #-48]
	mov	r8, r2
	str	r2, [fp, #-56]
.L206:
	sub	r10, r3, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L359
.L146:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L147
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L360
.L148:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L149
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L361
.L151:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L156
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L362
.L158:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L162
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r5, r5, r1
	str	r8, [fp, #-68]
	add	r1, r7, r5
	mov	r8, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L163
.L167:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L363
.L163:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L167
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
	b	.L167
.L147:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r10, [r6, #36]
.L272:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L364
.L176:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L177
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L365
.L178:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L179
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L366
.L181:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L186
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L367
.L188:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L192
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r5, r5, r1
	str	r8, [fp, #-68]
	add	r1, r7, r5
	mov	r8, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L193
.L197:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L368
.L193:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L197
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
	b	.L197
.L177:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r10, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
.L273:
	ldr	r2, [fp, #-48]
	add	r8, r8, #2
	cmp	r8, r2
	bne	.L206
	ldr	r2, [fp, #-52]
	mov	r10, r3
	add	r8, r2, #6
	str	r8, [fp, #-48]
	ldr	r8, [fp, #-56]
.L270:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r2, r10, asl #8
	sub	r10, r2, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L369
.L207:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L208
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	mov	r1, r8
	mov	r0, r6
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r5
	mov	r10, r10, asl r3
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
	bl	Vp9_DiffUpdateProb
	ldr	r9, [r6, #28]
	ldr	r10, [r6, #36]
	ldr	r4, [r6, #32]
.L274:
	sub	r10, r10, #1
	cmp	r4, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L370
.L209:
	mov	r5, r10, asl #24
	cmp	r5, r9
	bhi	.L210
	ldr	r3, [r6, #36]
	rsb	r9, r5, r9
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L371
.L211:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L212
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L372
.L214:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L219
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L373
.L221:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L225
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r5, r5, r1
	str	r8, [fp, #-60]
	add	r1, r7, r5
	mov	r8, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L226
.L230:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L374
.L226:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L230
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L230
.L208:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r4, asl r3
	mov	r10, r10, asl r3
	rsb	r4, r3, r5
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
	b	.L274
.L210:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r9, asl r3
	rsb	r4, r3, r4
	mov	r10, r10, asl r3
	str	r5, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L275:
	sub	r10, r10, #1
	cmp	r4, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L375
.L239:
	mov	r9, r10, asl #24
	cmp	r9, r5
	bhi	.L240
	ldr	r3, [r6, #36]
	rsb	r9, r9, r5
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L376
.L241:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L242
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L377
.L244:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L249
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L378
.L251:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L255
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r5, r5, r1
	str	r8, [fp, #-60]
	add	r1, r7, r5
	mov	r8, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L256
.L260:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L379
.L256:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L260
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L260
.L240:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r3
	rsb	r4, r3, r4
	mov	r10, r10, asl r3
	str	r5, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L276:
	ldr	r3, [fp, #-48]
	add	r8, r8, #3
	cmp	r8, r3
	addne	r4, r6, #28
	ldmneia	r4, {r4, r5, r10}
	bne	.L270
.L114:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L212:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L217
.L215:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L380
.L217:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L215
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L215
.L179:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L184
.L182:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L381
.L184:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L182
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
	b	.L182
.L149:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L154
.L152:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L382
.L154:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L152
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
	b	.L152
.L118:
	add	r3, r7, r4
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-64]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r10, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L123
.L121:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L383
.L123:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L121
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L121
.L242:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L247
.L245:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L384
.L247:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L245
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L245
.L401:
	.align	2
.L400:
	.word	.LANCHOR0
.L364:
	rsb	r2, r5, #24
	rsb	r9, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r9, r2, r9
	str	r2, [fp, #-60]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	add	r5, r2, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L176
.L369:
	rsb	r3, r5, #24
	rsb	r9, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r5, r3, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L207
.L370:
	rsb	r3, r4, #24
	rsb	r5, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r5, r3, r5
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r5, r5, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r3, r4
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r5
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L209
.L375:
	rsb	r2, r4, #24
	rsb	r9, r4, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r9, r2, r9
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-52]
	add	r4, r2, r4
	str	r4, [r6, #32]
	orr	r0, r5, r0, asl r3
	str	r0, [r6, #28]
	mov	r5, r0
	b	.L239
.L359:
	rsb	r3, r5, #24
	rsb	r9, r5, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r9, r3, r9
	str	r3, [fp, #-60]
	mov	r1, r3
	and	r9, r9, #7
	bl	BsGet
	ldr	r3, [fp, #-60]
	add	r5, r3, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L146
.L354:
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
	b	.L115
.L382:
	mov	r10, r8
	ldr	r8, [fp, #-68]
.L155:
	ldrb	r2, [r8, #6]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L170
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L171
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L171:
	add	r3, r3, #1
.L173:
	add	r4, r6, #28
	strb	r3, [r8, #6]
	ldmia	r4, {r4, r5, r10}
	b	.L272
.L170:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L385
	rsb	r3, r3, #255
	b	.L173
.L383:
	mov	r10, r8
	ldr	r8, [fp, #-64]
.L124:
	ldrb	r2, [r8]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L139
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L140
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L140:
	add	r3, r3, #1
.L142:
	strb	r3, [r8]
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
	b	.L271
.L139:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L386
	rsb	r3, r3, #255
	b	.L142
.L384:
	mov	r10, r8
	ldr	r8, [fp, #-60]
.L248:
	ldrb	r2, [r8, #2]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L263
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L264
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L264:
	add	r3, r3, #1
.L266:
	strb	r3, [r8, #2]
	b	.L276
.L263:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L387
	rsb	r3, r3, #255
	b	.L266
.L381:
	mov	r10, r8
	ldr	r8, [fp, #-68]
.L185:
	ldrb	r2, [r8, #7]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L200
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L201
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L201:
	add	r3, r3, #1
.L203:
	strb	r3, [r8, #7]
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
	b	.L273
.L200:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L388
	rsb	r3, r3, #255
	b	.L203
.L380:
	mov	r10, r8
	ldr	r8, [fp, #-60]
.L218:
	ldrb	r2, [r8, #1]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L233
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L234
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L234:
	add	r3, r3, #1
.L236:
	strb	r3, [r8, #1]
	ldr	r5, [r6, #28]
	ldr	r10, [r6, #36]
	ldr	r4, [r6, #32]
	b	.L275
.L233:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L389
	rsb	r3, r3, #255
	b	.L236
.L386:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L142
.L385:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L173
.L388:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L203
.L387:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L266
.L389:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L236
.L162:
	add	r3, r7, r5
	mov	r10, #0
	mov	ip, #4
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r5, ip
	b	.L166
.L164:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r5
	cmp	r1, r0
	sub	r5, r5, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r8, r8, ip
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r1, r7, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L390
.L166:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L164
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
	b	.L164
.L192:
	add	r3, r7, r5
	mov	r10, #0
	mov	ip, #4
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r5, ip
	b	.L196
.L194:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r5
	cmp	r1, r0
	sub	r5, r5, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r8, r8, ip
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r1, r7, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L391
.L196:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L194
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
	b	.L194
.L255:
	add	r3, r7, r5
	mov	r10, #0
	mov	ip, #4
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r5, ip
	b	.L259
.L257:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r5
	cmp	r1, r0
	sub	r5, r5, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r8, r8, ip
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r1, r7, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L392
.L259:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L257
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L257
.L131:
	add	r3, r7, r9
	mov	r10, #0
	mov	r2, #4
	str	r8, [fp, #-64]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r3, r4, asl r1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #36]
	mov	r4, r9
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	mov	r10, r3
	mov	r9, r2
	b	.L135
.L133:
	mov	r2, r4, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, lr
	cmn	r9, #1
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L393
.L135:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L133
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L133
.L225:
	add	r3, r7, r5
	mov	r10, #0
	mov	ip, #4
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r5, ip
	b	.L229
.L227:
	mov	r1, r4, asl #24
	mov	ip, r2, asl r5
	cmp	r1, r0
	sub	r5, r5, #1
	rsbls	r0, r1, r0
	ldrls	lr, [r6, #36]
	movhi	ip, #0
	orr	r8, r8, ip
	rsbls	r4, r4, lr
	cmn	r5, #1
	add	r1, r7, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L394
.L229:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L227
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L227
.L156:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L161
.L159:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L395
.L161:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L159
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
	b	.L159
.L125:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-64]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L130
.L128:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L396
.L130:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L128
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L128
.L186:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L191
.L189:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L397
.L191:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L189
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
	b	.L189
.L219:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L224
.L222:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L398
.L224:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L222
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L222
.L249:
	add	r3, r7, r5
	mov	r10, #0
	mov	r2, #3
	str	r8, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r10, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L254
.L252:
	mov	r2, r5, asl #24
	mov	r1, ip, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, lr
	cmn	r9, #1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L399
.L254:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L252
	rsb	r1, r4, #24
	rsb	r2, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r4, r1, r4
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L252
.L399:
	mov	r10, r8
	ldr	r8, [fp, #-60]
	add	r10, r10, #16
	b	.L248
.L395:
	mov	r10, r8
	ldr	r8, [fp, #-68]
	add	r10, r10, #16
	b	.L155
.L398:
	mov	r10, r8
	ldr	r8, [fp, #-60]
	add	r10, r10, #16
	b	.L218
.L397:
	mov	r10, r8
	ldr	r8, [fp, #-68]
	add	r10, r10, #16
	b	.L185
.L396:
	mov	r10, r8
	ldr	r8, [fp, #-64]
	add	r10, r10, #16
	b	.L124
.L358:
	mov	r3, r8
	cmp	r3, #64
	ldr	r8, [fp, #-64]
	movle	r10, r3
	ble	.L138
	mov	r1, #128
	mov	r0, r6
	str	r3, [fp, #-56]
	bl	Vp9_Cabac_Read
	ldr	r3, [fp, #-56]
	add	r0, r0, r3, lsl #1
	sub	r10, r0, #65
.L138:
	add	r10, r10, #64
	b	.L124
.L374:
	mov	r10, r8
	cmp	r10, #64
	ldr	r8, [fp, #-60]
	ble	.L232
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L232:
	add	r10, r10, #64
	b	.L218
.L379:
	mov	r10, r8
	cmp	r10, #64
	ldr	r8, [fp, #-60]
	ble	.L262
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L262:
	add	r10, r10, #64
	b	.L248
.L368:
	mov	r10, r8
	cmp	r10, #64
	ldr	r8, [fp, #-68]
	ble	.L199
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L199:
	add	r10, r10, #64
	b	.L185
.L363:
	mov	r10, r8
	cmp	r10, #64
	ldr	r8, [fp, #-68]
	ble	.L169
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L169:
	add	r10, r10, #64
	b	.L155
.L393:
	mov	r10, r8
	ldr	r8, [fp, #-64]
	add	r10, r10, #32
	b	.L124
.L390:
	mov	r10, r8
	ldr	r8, [fp, #-68]
	add	r10, r10, #32
	b	.L155
.L394:
	mov	r10, r8
	ldr	r8, [fp, #-60]
	add	r10, r10, #32
	b	.L218
.L392:
	mov	r10, r8
	ldr	r8, [fp, #-60]
	add	r10, r10, #32
	b	.L248
.L391:
	mov	r10, r8
	ldr	r8, [fp, #-68]
	add	r10, r10, #32
	b	.L185
.L365:
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
	b	.L178
.L360:
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
	b	.L148
.L355:
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
	b	.L117
.L376:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L241
.L371:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L211
.L357:
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
	b	.L127
.L378:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L251
.L373:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L221
.L367:
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
	b	.L188
.L362:
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
	b	.L158
.L377:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L244
.L356:
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
	b	.L120
.L366:
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
	b	.L181
.L361:
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
	b	.L151
.L372:
	rsb	r3, r4, #24
	rsb	r10, r4, #16
	bic	r3, r3, #7
	mov	r0, r6
	rsb	r10, r3, r10
	str	r3, [fp, #-52]
	mov	r1, r3
	and	r10, r10, #7
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L214
	UNWIND(.fnend)
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
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
	blt	.L403
	ldr	r3, [r1, #28]
.L404:
	mov	r1, r4, asl #24
	cmp	r1, r3
	bhi	.L405
	ldr	r2, [r6, #36]
	rsb	r3, r1, r3
	ldr	r5, .L597
	add	r1, r7, #648
	rsb	r4, r4, r2
	add	r2, r1, #2
	str	r2, [fp, #-80]
	add	r2, r5, r4
	mov	r10, r6
	add	r1, r7, #218
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	str	r1, [fp, #-76]
	mov	r3, r3, asl r2
	rsb	r1, r2, ip
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r1, [r6, #32]
	str	r4, [r6, #36]
.L406:
	ldr	r3, [fp, #-76]
	mov	r6, r10
	sub	r3, r3, #216
	str	r3, [fp, #-72]
.L511:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-52]
.L509:
	ldr	r7, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-48]
.L507:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	bge	.L567
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L407
	ldr	r10, [r6, #28]
.L408:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L409
	ldr	r3, [r6, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	add	r3, r5, r8
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r10, r10, asl r9
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L568
.L410:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L411
	ldr	r2, [r6, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r2
	add	r3, r5, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L569
.L413:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L418
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L570
.L420:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L424
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	add	r1, r5, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L425
.L429:
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
	add	r2, r5, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L571
.L425:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L429
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
	b	.L429
.L409:
	add	r3, r5, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L512:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L572
.L440:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L441
	ldr	r3, [r6, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	add	r3, r5, r8
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r10, r10, asl r9
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L573
.L442:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L443
	ldr	r2, [r6, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r2
	add	r3, r5, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L574
.L445:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L450
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L575
.L452:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L456
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	add	r1, r5, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L457
.L461:
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
	add	r2, r5, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L576
.L457:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L461
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
	b	.L461
.L441:
	add	r3, r5, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L513:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L577
.L472:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L473
	ldr	r3, [r6, #36]
	rsb	r10, r9, r10
	rsb	r8, r8, r3
	add	r3, r5, r8
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r10, r10, asl r9
	str	r3, [r6, #36]
	add	r8, r8, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L578
.L474:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L475
	ldr	r2, [r6, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r2
	add	r3, r5, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L579
.L477:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L482
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L580
.L484:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L488
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-68]
	add	r1, r5, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r8, asl r4
	str	r9, [r6, #32]
	mov	r8, r3
	str	r4, [r6, #36]
	mov	r10, r2
	b	.L489
.L493:
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
	add	r2, r5, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L581
.L489:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L493
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
	b	.L493
.L473:
	add	r3, r5, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
.L514:
	ldr	r3, [fp, #-48]
	add	r7, r7, #3
	add	r3, r3, #1
	str	r3, [fp, #-48]
	b	.L507
.L577:
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
	b	.L472
.L572:
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
	b	.L440
.L407:
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
	b	.L408
.L475:
	add	r1, r5, r8
	mov	r3, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	ip, #1
	mov	r7, r3
	mov	r9, r10, asl r1
	rsb	r4, r1, r4
	mov	r8, r8, asl r1
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r2
	str	r8, [r6, #36]
	b	.L480
.L478:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r10, #1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L582
.L480:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r9
	add	r8, r8, #1
	bge	.L478
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
	orr	r0, r9, r0, asl r2
	b	.L478
.L443:
	add	r1, r5, r8
	mov	r3, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	ip, #1
	mov	r7, r3
	mov	r9, r10, asl r1
	rsb	r4, r1, r4
	mov	r8, r8, asl r1
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r2
	str	r8, [r6, #36]
	b	.L448
.L446:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r10, #1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L583
.L448:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r9
	add	r8, r8, #1
	bge	.L446
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
	orr	r0, r9, r0, asl r2
	b	.L446
.L411:
	add	r1, r5, r8
	mov	r3, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	ip, #1
	mov	r7, r3
	mov	r9, r10, asl r1
	rsb	r4, r1, r4
	mov	r8, r8, asl r1
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r2
	str	r8, [r6, #36]
	b	.L416
.L414:
	mov	r2, r8, asl #24
	mov	r1, ip, asl r10
	cmp	r2, r0
	sub	r10, r10, #1
	rsbls	r0, r2, r0
	ldrls	lr, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r8, r8, lr
	cmn	r10, #1
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L584
.L416:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r9
	add	r8, r8, #1
	bge	.L414
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
	orr	r0, r9, r0, asl r2
	b	.L414
.L584:
	mov	r3, r7
	ldr	r7, [fp, #-68]
.L417:
	ldrb	r2, [r7, #-2]	@ zero_extendqisi2
	add	r10, r5, r3
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L434
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L435
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L435:
	add	r3, r3, #1
.L437:
	strb	r3, [r7, #-2]
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	ldr	r10, [r6, #28]
	b	.L512
.L434:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L438
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L438:
	rsb	r3, r3, #255
	b	.L437
.L583:
	mov	r3, r7
	ldr	r7, [fp, #-68]
.L449:
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	add	r10, r5, r3
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L466
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L467
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L467:
	add	r3, r3, #1
.L469:
	strb	r3, [r7, #-1]
	ldr	r8, [r6, #36]
	ldr	r4, [r6, #32]
	ldr	r10, [r6, #28]
	b	.L513
.L466:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L470
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L470:
	rsb	r3, r3, #255
	b	.L469
.L582:
	mov	r3, r7
	ldr	r7, [fp, #-68]
.L481:
	ldrb	r2, [r7]	@ zero_extendqisi2
	add	r10, r5, r3
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L498
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L499
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L499:
	add	r3, r3, #1
.L501:
	strb	r3, [r7]
	b	.L514
.L498:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L502
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L502:
	rsb	r3, r3, #255
	b	.L501
.L567:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #6
	add	r2, r2, #18
	str	r2, [fp, #-56]
	bne	.L509
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-76]
	add	r3, r3, #108
	str	r3, [fp, #-72]
	cmp	r2, r3
	bne	.L511
	ldr	r3, [fp, #-76]
	mov	r10, r6
	ldr	r2, [fp, #-80]
	add	r3, r3, #216
	str	r3, [fp, #-76]
	cmp	r3, r2
	bne	.L406
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L450:
	add	r3, r5, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L455
.L453:
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
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L585
.L455:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L453
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
	b	.L453
.L418:
	add	r3, r5, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L423
.L421:
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
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L586
.L423:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L421
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
	b	.L421
.L482:
	add	r3, r5, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-68]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	str	r9, [r6, #28]
	mov	r8, r8, asl r3
	mov	r10, r9
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	mov	r9, r2
	b	.L487
.L485:
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
	add	r2, r5, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r8, [r6, #36]
	beq	.L587
.L487:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L485
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
	b	.L485
.L587:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #16
	b	.L481
.L586:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #16
	b	.L417
.L585:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #16
	b	.L449
.L571:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L588
.L431:
	add	r3, r10, #64
	b	.L417
.L581:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L589
.L495:
	add	r3, r10, #64
	b	.L481
.L576:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-68]
	bgt	.L590
.L463:
	add	r3, r10, #64
	b	.L449
.L424:
	add	r3, r5, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r4, r8
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L428
.L598:
	.align	2
.L597:
	.word	.LANCHOR0
.L426:
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
	add	r1, r5, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L591
.L428:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L426
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
	b	.L426
.L488:
	add	r3, r5, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r4, r8
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L492
.L490:
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
	add	r1, r5, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L592
.L492:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L490
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
	b	.L490
.L456:
	add	r3, r5, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r6, #36]
	mov	r4, r8
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L460
.L458:
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
	add	r1, r5, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L593
.L460:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L458
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
	b	.L458
.L593:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #32
	b	.L449
.L592:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #32
	b	.L481
.L591:
	mov	r10, r7
	ldr	r7, [fp, #-68]
	add	r3, r10, #32
	b	.L417
.L578:
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
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L474
.L568:
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
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L410
.L573:
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
	add	r4, r4, r3
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r2
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L442
.L590:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L594
.L464:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r10, r10, r3
	rsbls	r4, r4, r1
	add	r1, r5, r4
	ldrb	r3, [r1, #24]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L463
.L588:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L595
.L432:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r10, r10, r3
	rsbls	r4, r4, r1
	add	r1, r5, r4
	ldrb	r3, [r1, #24]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L431
.L589:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L596
.L496:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r10, r10, r3
	rsbls	r4, r4, r1
	add	r1, r5, r4
	ldrb	r3, [r1, #24]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L495
.L579:
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
	b	.L477
.L574:
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
	b	.L445
.L569:
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
	b	.L413
.L570:
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
	b	.L420
.L575:
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
	b	.L452
.L580:
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
	b	.L484
.L596:
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
	b	.L496
.L594:
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
	b	.L464
.L595:
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
	b	.L432
.L405:
	ldr	r2, .L597
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, ip
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L403:
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
	b	.L404
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
	add	r0, r6, #432
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #1
	bls	.L601
	mov	r1, r5
	add	r0, r6, #864
	bl	Vp9_ReadCoefProbsCommon
.L601:
	cmp	r4, #2
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #1296
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
	ldr	r6, .L771
	mov	r7, r0
	mov	r5, r1
	add	r3, r0, #21
	str	r3, [fp, #-48]
.L696:
	ldr	r3, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r3, r3, #1
	cmp	r4, #0
	mov	r2, r3, asl #8
	sub	r3, r2, r3, asl #2
	mov	r3, r3, lsr #8
	add	r8, r3, #1
	blt	.L605
	ldr	r10, [r5, #28]
.L606:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L607
	ldr	r3, [r5, #36]
	rsb	r10, r9, r10
	rsb	r3, r8, r3
	add	r2, r6, r3
	ldrb	r9, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r9
	rsb	r4, r9, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r10, asl r9
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L748
.L608:
	mov	r10, r8, asl #24
	cmp	r10, r9
	bhi	.L609
	ldr	r2, [r5, #36]
	rsb	r9, r10, r9
	rsb	r8, r8, r2
	add	r3, r6, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L749
.L611:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L616
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L750
.L618:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L622
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-60]
	add	r1, r6, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L623
.L627:
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
	add	r2, r6, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L751
.L623:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L627
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L627
.L607:
	add	r3, r6, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	str	r10, [r5, #28]
	mov	r3, r8, asl r3
	str	r4, [r5, #32]
	str	r3, [r5, #36]
.L697:
	sub	r3, r3, #1
	cmp	r4, #0
	mov	r8, r3, asl #8
	sub	r8, r8, r3, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L752
.L636:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L637
	ldr	r3, [r5, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	add	r3, r6, r8
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r2
	rsb	r4, r2, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r2
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L753
.L638:
	mov	r2, r8, asl #24
	cmp	r2, r9
	bhi	.L639
	ldr	ip, [r5, #36]
	rsb	r9, r2, r9
	rsb	r8, r8, ip
	add	r3, r6, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
	mov	ip, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, ip, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	ip, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L754
.L641:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L646
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r6, r8
	ldrb	ip, [r2, #24]	@ zero_extendqisi2
	rsb	r9, ip, r4
	mov	r1, r8, asl ip
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl ip
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L755
.L648:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L652
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-60]
	add	r1, r6, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L653
.L657:
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
	add	r2, r6, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L756
.L653:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L657
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L657
.L637:
	add	r3, r6, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L698:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L757
.L666:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L667
	ldr	r3, [r5, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	add	r3, r6, r8
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r2
	rsb	r4, r2, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r2
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L758
.L668:
	mov	r2, r8, asl #24
	cmp	r2, r9
	bhi	.L669
	ldr	ip, [r5, #36]
	rsb	r9, r2, r9
	rsb	r8, r8, ip
	add	r3, r6, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
	mov	ip, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, ip, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	ip, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L759
.L671:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L676
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r6, r8
	ldrb	ip, [r2, #24]	@ zero_extendqisi2
	rsb	r9, ip, r4
	mov	r1, r8, asl ip
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl ip
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L760
.L678:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L682
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-60]
	add	r1, r6, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L683
.L687:
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
	add	r2, r6, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L761
.L683:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L687
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L687
.L667:
	add	r3, r6, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L699:
	ldr	r3, [fp, #-48]
	add	r7, r7, #3
	cmp	r7, r3
	bne	.L696
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L757:
	rsb	r2, r4, #24
	rsb	r9, r4, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r9, r2, r9
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-52]
	add	r4, r2, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L666
.L752:
	rsb	r2, r4, #24
	rsb	r9, r4, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r9, r2, r9
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-52]
	add	r4, r2, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L636
.L605:
	rsb	r9, r4, #24
	rsb	r3, r4, #16
	bic	r9, r9, #7
	mov	r0, r5
	rsb	r3, r9, r3
	ldr	r10, [r5, #28]
	mov	r1, r9
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r9
	str	r4, [r5, #32]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L606
.L609:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L614
.L612:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L762
.L614:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L612
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
	b	.L612
.L669:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L674
.L672:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L763
.L674:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L672
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
	b	.L672
.L639:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L644
.L642:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L764
.L644:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L642
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
	b	.L642
.L764:
	mov	r10, r7
	ldr	r7, [fp, #-60]
.L645:
	ldrb	r2, [r7, #1959]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L660
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L661
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L661:
	add	r3, r3, #1
.L663:
	strb	r3, [r7, #1959]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L698
.L660:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L664
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L664:
	rsb	r3, r3, #255
	b	.L663
.L763:
	mov	r10, r7
	ldr	r7, [fp, #-60]
.L675:
	ldrb	r2, [r7, #1960]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
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
	strb	r3, [r7, #1960]
	b	.L699
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
.L762:
	mov	r10, r7
	ldr	r7, [fp, #-60]
.L615:
	ldrb	r2, [r7, #1958]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L630
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L631
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L631:
	add	r3, r3, #1
.L633:
	strb	r3, [r7, #1958]
	ldr	r10, [r5, #28]
	ldr	r3, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L697
.L630:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L634
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L634:
	rsb	r3, r3, #255
	b	.L633
.L622:
	add	r3, r6, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L626
.L624:
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
	add	r1, r6, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L765
.L626:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L624
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L624
.L682:
	add	r3, r6, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L686
.L684:
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
	add	r1, r6, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L766
.L686:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L684
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L684
.L652:
	add	r3, r6, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L656
.L654:
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
	add	r1, r6, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L767
.L656:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L654
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L654
.L676:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L681
.L679:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L768
.L681:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L679
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
	b	.L679
.L646:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L651
.L649:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L769
.L651:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L649
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
	b	.L649
.L616:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L621
.L772:
	.align	2
.L771:
	.word	.LANCHOR0
.L619:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L770
.L621:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L619
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
	b	.L619
.L770:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #16
	b	.L615
.L769:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #16
	b	.L645
.L768:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #16
	b	.L675
.L761:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-60]
	ble	.L689
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L689:
	add	r10, r10, #64
	b	.L675
.L751:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-60]
	ble	.L629
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L629:
	add	r10, r10, #64
	b	.L615
.L756:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-60]
	ble	.L659
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L659:
	add	r10, r10, #64
	b	.L645
.L767:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #32
	b	.L645
.L766:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #32
	b	.L675
.L765:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #32
	b	.L615
.L753:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L638
.L758:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L668
.L748:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L608
.L749:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L611
.L759:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L671
.L754:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L641
.L755:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L648
.L750:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L618
.L760:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L678
	UNWIND(.fnend)
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	2
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
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
	ldr	r6, .L893
	mov	r7, r0
	mov	r5, r1
	add	r3, r0, #8
	str	r3, [fp, #-48]
.L837:
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L774
	ldr	r0, [r5, #28]
.L775:
	mov	r10, r8, asl #24
	cmp	r10, r0
	bhi	.L776
	ldr	r3, [r5, #36]
	rsb	r0, r10, r0
	rsb	r8, r8, r3
	add	r3, r6, r8
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
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
	blt	.L875
.L777:
	mov	r0, r8, asl #24
	cmp	r0, r9
	bhi	.L778
	ldr	r2, [r5, #36]
	rsb	r9, r0, r9
	rsb	r8, r8, r2
	add	r3, r6, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L876
.L780:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L785
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L877
.L787:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L791
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-60]
	add	r1, r6, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L792
.L796:
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
	add	r2, r6, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L878
.L792:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L796
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L796
.L776:
	add	r3, r6, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L838:
	sub	r8, r8, #1
	cmp	r4, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L879
.L807:
	mov	r9, r8, asl #24
	cmp	r9, r10
	bhi	.L808
	ldr	r3, [r5, #36]
	rsb	r9, r9, r10
	rsb	r8, r8, r3
	add	r3, r6, r8
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r2
	rsb	r4, r2, r4
	sub	r8, r3, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r2
	str	r3, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L880
.L809:
	mov	r2, r8, asl #24
	cmp	r2, r9
	bhi	.L810
	ldr	ip, [r5, #36]
	rsb	r9, r2, r9
	rsb	r8, r8, ip
	add	r3, r6, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
	mov	ip, r8, asl r0
	rsb	r4, r0, r4
	sub	r8, ip, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r9, r9, asl r0
	str	ip, [r5, #36]
	add	r8, r8, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L881
.L812:
	mov	r3, r8, asl #24
	cmp	r3, r9
	bhi	.L817
	ldr	r1, [r5, #36]
	rsb	r3, r3, r9
	rsb	r8, r8, r1
	add	r2, r6, r8
	ldrb	ip, [r2, #24]	@ zero_extendqisi2
	rsb	r9, ip, r4
	mov	r1, r8, asl ip
	sub	r8, r1, #1
	cmp	r9, #0
	ubfx	r8, r8, #1, #24
	mov	r4, r3, asl ip
	str	r1, [r5, #36]
	add	r8, r8, #1
	str	r9, [r5, #32]
	str	r4, [r5, #28]
	blt	.L882
.L819:
	mov	r2, r8, asl #24
	cmp	r2, r4
	bhi	.L823
	ldr	r1, [r5, #36]
	rsb	r2, r2, r4
	mov	r10, #0
	mov	r3, #6
	rsb	r8, r8, r1
	str	r7, [fp, #-60]
	add	r1, r6, r8
	mov	r7, r10
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r5, #28]
	mov	r4, r8, asl r4
	str	r9, [r5, #32]
	mov	r8, r3
	str	r4, [r5, #36]
	mov	r10, r2
	b	.L824
.L828:
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
	add	r2, r6, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L883
.L824:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L828
	rsb	r1, r9, #24
	rsb	r2, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L828
.L808:
	add	r3, r6, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r8, r8, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
.L839:
	ldr	r3, [fp, #-48]
	add	r7, r7, #2
	cmp	r7, r3
	bne	.L837
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L879:
	rsb	r2, r4, #24
	rsb	r9, r4, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r9, r2, r9
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-52]
	add	r4, r2, r4
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L807
.L774:
	rsb	r9, r4, #24
	rsb	r3, r4, #16
	bic	r9, r9, #7
	mov	r0, r5
	rsb	r3, r9, r3
	ldr	r10, [r5, #28]
	mov	r1, r9
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	add	r4, r4, r9
	str	r4, [r5, #32]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	b	.L775
.L785:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L790
.L788:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L884
.L790:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L788
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
	b	.L788
.L817:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L822
.L820:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L885
.L822:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L820
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
	b	.L820
.L778:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L783
.L781:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L886
.L783:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L781
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
	b	.L781
.L810:
	add	r3, r6, r8
	mov	r10, #0
	mov	r2, #3
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r5, #28]
	mov	r8, r8, asl r1
	mov	r10, r9
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	mov	r9, r2
	b	.L815
.L813:
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
	add	r2, r6, r8
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r4, r2, r4
	mov	r8, r8, asl r2
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r8, [r5, #36]
	beq	.L887
.L815:
	sub	r8, r8, #1
	cmp	r4, #0
	ubfx	r8, r8, #1, #24
	mov	r0, r10
	add	r8, r8, #1
	bge	.L813
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
	b	.L813
.L887:
	mov	r10, r7
	ldr	r7, [fp, #-60]
.L816:
	ldrb	r2, [r7, #1951]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L831
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L832
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L832:
	add	r3, r3, #1
.L834:
	strb	r3, [r7, #1951]
	b	.L839
.L831:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L835
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L835:
	rsb	r3, r3, #255
	b	.L834
.L886:
	mov	r10, r7
	ldr	r7, [fp, #-60]
.L784:
	ldrb	r2, [r7, #1950]	@ zero_extendqisi2
	add	r10, r6, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L801
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L802
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L802:
	add	r3, r3, #1
.L804:
	strb	r3, [r7, #1950]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L838
.L801:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L805
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L805:
	rsb	r3, r3, #255
	b	.L804
.L885:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #16
	b	.L816
.L884:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #16
	b	.L784
.L878:
	mov	r2, r10
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-60]
	bgt	.L888
	add	r10, r10, #64
	b	.L784
.L883:
	mov	r10, r7
	cmp	r10, #64
	ldr	r7, [fp, #-60]
	addle	r10, r10, #64
	ble	.L816
.L889:
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
	add	r10, r10, #64
	b	.L816
.L888:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r2
	blt	.L890
.L799:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r10, r10, r1
	rsbls	r4, r4, r2
	add	r10, r10, #64
	add	r3, r6, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	b	.L784
.L791:
	add	r3, r6, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L795
.L793:
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
	add	r1, r6, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L891
.L795:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L793
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L793
.L823:
	add	r3, r6, r8
	mov	r10, #0
	mov	ip, #4
	str	r7, [fp, #-60]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r10
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r8, r8, asl r1
	rsb	r9, r1, r9
	str	r8, [r5, #36]
	mov	r4, r8
	str	r3, [r5, #28]
	str	r9, [r5, #32]
	mov	r10, r3
	mov	r8, ip
	b	.L827
.L825:
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
	add	r1, r6, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r10, [r5, #28]
	str	r9, [r5, #32]
	str	r4, [r5, #36]
	beq	.L892
.L827:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L825
	rsb	r1, r9, #24
	rsb	ip, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	ip, r1, ip
	str	r2, [fp, #-56]
	str	ip, [fp, #-52]
	add	r9, r1, r9
	bl	BsGet
	ldr	ip, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	ip, ip, #7
	orr	r0, r10, r0, asl ip
	b	.L825
.L891:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #32
	b	.L784
.L892:
	mov	r10, r7
	ldr	r7, [fp, #-60]
	add	r10, r10, #32
	b	.L816
.L880:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L809
.L875:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L777
.L876:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L780
.L881:
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
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L812
.L877:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L787
.L882:
	rsb	r2, r9, #24
	rsb	r10, r9, #16
	bic	r2, r2, #7
	mov	r0, r5
	rsb	r10, r2, r10
	str	r2, [fp, #-52]
	mov	r1, r2
	bl	BsGet
	and	r3, r10, #7
	ldr	r2, [fp, #-52]
	add	r9, r9, r2
	str	r9, [r5, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L819
.L890:
	rsb	r1, r9, #24
	rsb	r8, r9, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r8
	add	r9, r1, r9
	bl	BsGet
	ldr	r2, [fp, #-52]
	and	r8, r8, #7
	orr	r0, r2, r0, asl r8
	b	.L799
.L894:
	.align	2
.L893:
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
	bne	.L1058
	ldr	r4, [r1, #28]
	ldr	r3, [r1, #36]
	ldr	r5, [r1, #32]
	ldr	r7, .L1088
	str	r2, [fp, #-52]
.L904:
	ldr	r2, [fp, #-56]
	mov	r9, r4
	mov	r10, r3
	add	r1, r2, #10
	str	r1, [fp, #-48]
	mov	r8, r2
.L967:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r2, r10, asl #8
	sub	r10, r2, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1059
.L906:
	mov	r0, r10, asl #24
	cmp	r0, r9
	bhi	.L907
	ldr	r3, [r6, #36]
	rsb	r9, r0, r9
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1060
.L908:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L909
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1061
.L911:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L916
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L1062
.L918:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L922
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r3, #6
	str	r8, [fp, #-72]
	rsb	r5, r5, r1
	mov	r8, r7
	add	r1, r7, r5
	mov	r10, #0
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r7, r2
	b	.L923
.L927:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1063
.L923:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L927
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
	b	.L927
.L907:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r5
	mov	r10, r10, asl r3
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L1002:
	sub	r10, r10, #1
	cmp	r4, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1064
.L936:
	mov	r0, r10, asl #24
	cmp	r0, r9
	bhi	.L937
	ldr	r3, [r6, #36]
	rsb	r9, r0, r9
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1065
.L938:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L939
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1066
.L941:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L946
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L1067
.L948:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L952
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r3, #6
	str	r8, [fp, #-72]
	rsb	r5, r5, r1
	mov	r8, r7
	add	r1, r7, r5
	mov	r10, #0
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r7, r2
	b	.L953
.L957:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1068
.L953:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L957
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
	b	.L957
.L937:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	mov	r10, r10, asl r3
	str	r9, [r6, #28]
	str	r4, [r6, #32]
	str	r10, [r6, #36]
.L1003:
	ldr	r3, [fp, #-48]
	add	r8, r8, #2
	cmp	r8, r3
	ldrne	r9, [r6, #28]
	ldrne	r10, [r6, #36]
	ldrne	r5, [r6, #32]
	bne	.L967
.L966:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	bne	.L1069
.L998:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-52]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1069:
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
.L905:
	ldr	r2, [fp, #-56]
	mov	r10, r3
	add	r8, r2, #1984
	add	r2, r2, #2000
	add	r8, r8, #14
	add	r2, r2, #3
	str	r2, [fp, #-48]
.L999:
	sub	r10, r10, #1
	cmp	r5, #0
	mov	r2, r10, asl #8
	sub	r10, r2, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1070
.L968:
	mov	r9, r10, asl #24
	cmp	r9, r4
	bhi	.L969
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r10, r10, r3
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1071
.L970:
	mov	r3, r4, asl #24
	cmp	r3, r9
	bhi	.L971
	ldr	r2, [r6, #36]
	rsb	r9, r3, r9
	rsb	r4, r4, r2
	add	r3, r7, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1072
.L973:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L978
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r1, r5, asl r2
	rsb	r5, r2, r4
	sub	r9, r1, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r4, r3, asl r2
	str	r1, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1073
.L980:
	mov	r3, r9, asl #24
	cmp	r3, r4
	bhi	.L984
	ldr	r1, [r6, #36]
	rsb	r0, r3, r4
	mov	r2, #6
	mov	r3, #0
	rsb	r4, r9, r1
	str	r8, [fp, #-68]
	add	r1, r7, r4
	mov	r8, r7
	mov	ip, #1
	mov	r7, r3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r10, r1, r5
	mov	r9, r0, asl r1
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	b	.L985
.L989:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r10, r2, r10
	mov	r4, r4, asl r2
	str	r9, [r6, #28]
	str	r10, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1074
.L985:
	sub	r4, r4, #1
	cmp	r10, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L989
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
	b	.L989
.L946:
	add	r3, r7, r5
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L951
.L949:
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
	add	r2, r8, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1075
.L951:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L949
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
	b	.L949
.L916:
	add	r3, r7, r5
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L921
.L919:
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
	add	r2, r8, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1076
.L921:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L919
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
	b	.L919
.L969:
	add	r3, r7, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r10, [r6, #36]
.L1004:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r3
	beq	.L998
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r10}
	b	.L999
.L1064:
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
	b	.L936
.L1059:
	rsb	r2, r5, #24
	rsb	r4, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r4, r2, r4
	str	r2, [fp, #-64]
	mov	r1, r2
	bl	BsGet
	ldr	r2, [fp, #-64]
	and	r3, r4, #7
	add	r4, r2, r5
	str	r4, [r6, #32]
	mov	r5, r4
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r9, r0
	b	.L906
.L939:
	add	r3, r7, r5
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L944
.L942:
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
	add	r2, r8, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1077
.L944:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L942
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
	b	.L942
.L909:
	add	r3, r7, r5
	mov	r2, #3
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L914
.L912:
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
	add	r2, r8, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1078
.L914:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L912
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
	b	.L912
.L1070:
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
	b	.L968
.L1078:
	mov	r7, r8
	ldr	r8, [fp, #-72]
.L915:
	ldrb	r2, [r8, #1988]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L930
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L931
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L931:
	add	r3, r3, #1
.L933:
	strb	r3, [r8, #1988]
	ldr	r9, [r6, #28]
	ldr	r10, [r6, #36]
	ldr	r4, [r6, #32]
	b	.L1002
.L930:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L934
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L934:
	rsb	r3, r3, #255
	b	.L933
.L1077:
	mov	r7, r8
	ldr	r8, [fp, #-72]
.L945:
	ldrb	r2, [r8, #1989]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L960
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L961
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L961:
	add	r3, r3, #1
.L963:
	strb	r3, [r8, #1989]
	b	.L1003
.L960:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L964
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L964:
	rsb	r3, r3, #255
	b	.L963
.L971:
	add	r3, r7, r4
	mov	r2, #3
	str	r8, [fp, #-68]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r7, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L976
.L974:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1079
.L976:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L974
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
	b	.L974
.L1079:
	mov	r7, r8
	ldr	r8, [fp, #-68]
.L977:
	ldrb	r2, [r8]	@ zero_extendqisi2
	add	r10, r7, r10
	sub	ip, r2, #1
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L992
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L993
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L993:
	add	r3, r3, #1
.L995:
	strb	r3, [r8]
	b	.L1004
.L992:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L996
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L996:
	rsb	r3, r3, #255
	b	.L995
.L1058:
	ldr	r8, [r1, #36]
	ldr	r5, [r1, #32]
	sub	r8, r8, #1
	cmp	r5, #0
	ubfx	r8, r8, #1, #24
	add	r8, r8, #1
	blt	.L897
	ldr	r0, [r1, #28]
.L898:
	mov	r4, r8, asl #24
	cmp	r4, r0
	bhi	.L899
	ldr	r3, [r6, #36]
	rsb	r4, r4, r0
	ldr	r7, .L1088
	mov	r1, #128
	rsb	r8, r8, r3
	mov	r0, r6
	add	r3, r7, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r8, r8, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r8, [r6, #36]
	bl	Vp9_Cabac_Read
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
	add	r2, r0, #1
	str	r2, [fp, #-52]
	cmp	r2, #2
	bne	.L900
	ldr	r2, [fp, #-56]
	add	r10, r2, #1968
	add	r9, r2, #1984
	add	r10, r10, #15
	add	r9, r9, #4
	b	.L903
.L1081:
	ldr	r3, [r6, #36]
	rsb	r8, r8, r3
	add	r3, r7, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	rsb	r5, r3, r5
	mov	r2, r2, asl r3
	mov	r8, r8, asl r3
	str	r5, [r6, #32]
	str	r2, [r6, #28]
	str	r8, [r6, #36]
	bl	Vp9_DiffUpdateProb
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
.L1001:
	add	r10, r10, #1
	cmp	r10, r9
	beq	.L904
.L903:
	sub	r8, r3, #1
	cmp	r5, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L1080
.L901:
	mov	r3, r8, asl #24
	mov	r1, r10
	cmp	r3, r4
	mov	r0, r6
	rsb	r2, r3, r4
	bls	.L1081
	add	r3, r7, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r8, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
	b	.L1001
.L1075:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-72]
	b	.L945
.L1076:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-72]
	b	.L915
.L1068:
	cmp	r10, #64
	mov	r7, r8
	ldr	r8, [fp, #-72]
	bgt	.L1082
.L959:
	add	r10, r10, #64
	b	.L945
.L1063:
	cmp	r10, #64
	mov	r7, r8
	ldr	r8, [fp, #-72]
	bgt	.L1083
.L929:
	add	r10, r10, #64
	b	.L915
.L978:
	add	r3, r7, r5
	mov	r2, #3
	str	r8, [fp, #-68]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r7, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L983
.L981:
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
	add	r2, r8, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1084
.L983:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L981
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
	b	.L981
.L1089:
	.align	2
.L1088:
	.word	.LANCHOR0
.L899:
	ldr	r7, .L1088
	mov	r3, #0
	str	r3, [fp, #-52]
	add	r3, r7, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r0, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r8, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
	b	.L904
.L1082:
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
	b	.L959
.L1083:
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
	b	.L929
.L1084:
	mov	r7, r8
	add	r10, r10, #16
	ldr	r8, [fp, #-68]
	b	.L977
.L1080:
	rsb	r2, r5, #24
	rsb	r3, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r3, r2, r3
	str	r2, [fp, #-48]
	mov	r1, r2
	str	r3, [fp, #-64]
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-48]
	and	r3, r3, #7
	add	r5, r2, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L901
.L1074:
	mov	r3, r7
	cmp	r3, #64
	mov	r7, r8
	ldr	r8, [fp, #-68]
	movle	r10, r3
	ble	.L991
	mov	r1, #128
	mov	r0, r6
	str	r3, [fp, #-56]
	bl	Vp9_Cabac_Read
	ldr	r3, [fp, #-56]
	add	r0, r0, r3, lsl #1
	sub	r10, r0, #65
.L991:
	add	r10, r10, #64
	b	.L977
.L922:
	add	r3, r7, r5
	mov	ip, #4
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, ip
	mov	r7, r3
	b	.L926
.L924:
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
	add	r1, r8, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1085
.L926:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L924
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
	b	.L924
.L952:
	add	r3, r7, r5
	mov	ip, #4
	str	r8, [fp, #-72]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	r2, #1
	mov	r3, r4, asl r1
	mov	r5, r5, asl r1
	rsb	r9, r1, r9
	str	r5, [r6, #36]
	mov	r4, r5
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, ip
	mov	r7, r3
	b	.L956
.L954:
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
	add	r1, r8, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1086
.L956:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L954
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
	b	.L954
.L1086:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-72]
	b	.L945
.L1085:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-72]
	b	.L915
.L1065:
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
	b	.L938
.L1060:
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
	b	.L908
.L984:
	add	r3, r7, r9
	mov	r2, #4
	str	r8, [fp, #-68]
	mov	r10, #0
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r7
	mov	ip, #1
	mov	r3, r4, asl r1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #36]
	mov	r4, r9
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	mov	r9, r2
	mov	r7, r3
	b	.L988
.L986:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1087
.L988:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L986
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
	b	.L986
.L1087:
	mov	r7, r8
	add	r10, r10, #32
	ldr	r8, [fp, #-68]
	b	.L977
.L1071:
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
	b	.L970
.L1061:
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
	b	.L911
.L1066:
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
	b	.L941
.L1072:
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
	b	.L973
.L1067:
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
	b	.L948
.L1062:
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
	b	.L918
.L1073:
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
	b	.L980
.L897:
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
	b	.L898
.L900:
	ldr	r2, [fp, #-52]
	cmp	r2, #1
	beq	.L905
	b	.L904
	UNWIND(.fnend)
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	2
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
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
	ldr	r4, [r0, #36]
	ldr	r5, [r0, #32]
	mov	r3, r1
	ldr	r6, [r0, #28]
	mov	ip, r0
	mov	r9, r3
	mov	r7, r0
	str	r1, [fp, #-76]
	add	r1, r1, #3
	str	r2, [fp, #-80]
	str	r1, [fp, #-48]
	str	r3, [fp, #-84]
.L1096:
	sub	r3, r4, #1
	cmp	r5, #0
	mov	r4, r3, asl #8
	sub	r3, r4, r3, asl #2
	mov	r3, r3, lsr #8
	add	r4, r3, #1
	blt	.L1195
.L1091:
	mov	r2, r4, asl #24
	cmp	r2, r6
	bhi	.L1092
	ldr	r3, [r7, #36]
	rsb	r6, r2, r6
	ldr	r1, .L1213
	mov	r10, #0
	rsb	r3, r4, r3
	mov	r8, #6
	add	r1, r1, r3
	mov	r2, #1
	str	r9, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r7, #28]
	mov	r4, r3, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1095
.L1093:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1196
.L1095:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1093
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	str	r2, [fp, #-52]
	rsb	r9, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-52]
	orr	r0, r6, r0, asl r3
	b	.L1093
.L1092:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1149:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L1096
	ldr	r3, [fp, #-76]
	mov	ip, r7
	add	r2, r3, #25
	add	r3, r3, #91
	str	r2, [fp, #-48]
	str	r3, [fp, #-64]
.L1119:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1197
.L1097:
	mov	r2, r4, asl #24
	cmp	r2, r6
	bhi	.L1098
	ldr	r3, [r7, #36]
	rsb	r6, r2, r6
	mov	r9, #0
	mov	r8, #6
	rsb	r4, r4, r3
	ldr	r3, .L1213
	mov	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1101
.L1099:
	mov	r3, r4, asl #24
	mov	r2, r10, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	r1, [r7, #36]
	movhi	r2, #0
	orr	r9, r9, r2
	rsbls	r4, r4, r1
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1198
.L1101:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1099
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	add	r5, r1, r5
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L1099
.L1196:
	ldr	r9, [fp, #-56]
	mov	r3, r10, asl #1
	orr	r3, r3, #1
	strb	r3, [r9]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1149
.L1098:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1150:
	ldr	r3, [fp, #-48]
	sub	r10, r3, #21
	sub	r3, r3, #11
	str	r3, [fp, #-52]
	mov	r9, r10
.L1107:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1199
.L1102:
	mov	r2, r4, asl #24
	cmp	r2, r6
	bhi	.L1103
	ldr	r3, [r7, #36]
	rsb	r6, r2, r6
	ldr	r1, .L1213
	mov	r10, #0
	rsb	r3, r4, r3
	mov	r8, #6
	add	r1, r1, r3
	mov	r2, #1
	str	r9, [fp, #-60]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r7, #28]
	mov	r4, r3, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1106
.L1104:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1200
.L1106:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1104
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	str	r2, [fp, #-56]
	rsb	r9, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-56]
	orr	r0, r6, r0, asl r3
	b	.L1104
.L1103:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1151:
	ldr	r3, [fp, #-52]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L1107
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1201
.L1108:
	mov	r2, r4, asl #24
	cmp	r2, r6
	bhi	.L1109
	ldr	r3, [r7, #36]
	rsb	r6, r2, r6
	mov	r9, #0
	mov	r8, #6
	rsb	r4, r4, r3
	ldr	r3, .L1213
	mov	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1112
.L1110:
	mov	r3, r4, asl #24
	mov	r2, r10, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	r1, [r7, #36]
	movhi	r2, #0
	orr	r9, r9, r2
	rsbls	r4, r4, r1
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1202
.L1112:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1110
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	r3, r1, r3
	add	r5, r1, r5
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L1110
.L1200:
	ldr	r9, [fp, #-60]
	mov	r10, r10, asl #1
	orr	r10, r10, #1
	strb	r10, [r9]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1151
.L1199:
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
	b	.L1102
.L1109:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1152:
	ldr	r3, [fp, #-48]
	sub	r2, r3, #10
	mov	r9, r2
.L1118:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1203
.L1113:
	mov	r1, r4, asl #24
	cmp	r1, r6
	bhi	.L1114
	ldr	r3, [r7, #36]
	rsb	r6, r1, r6
	ldr	r2, .L1213
	mov	r10, #0
	rsb	r3, r4, r3
	mov	r8, #6
	add	r1, r2, r3
	mov	ip, #1
	str	r9, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r7, #28]
	mov	r4, r3, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1117
.L1115:
	mov	r3, r4, asl #24
	mov	r2, ip, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	r1, [r7, #36]
	movhi	r2, #0
	orr	r10, r10, r2
	rsbls	r4, r4, r1
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1204
.L1117:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1115
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	str	ip, [fp, #-52]
	rsb	r9, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r9, #7
	ldr	ip, [fp, #-52]
	orr	r0, r6, r0, asl r3
	b	.L1115
.L1114:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1153:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L1118
	ldr	r2, [fp, #-64]
	add	r3, r9, #33
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L1119
	ldr	r3, [fp, #-76]
	mov	r10, #1
	add	r2, r3, #31
	add	r3, r3, #97
	str	r2, [fp, #-68]
	str	r3, [fp, #-72]
.L1120:
	ldr	r3, [fp, #-68]
	sub	r3, r3, #6
	str	r3, [fp, #-48]
	mov	r3, #2
	str	r3, [fp, #-64]
.L1135:
	ldr	ip, [fp, #-48]
	mov	r2, #0
.L1126:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1205
.L1121:
	mov	r1, r4, asl #24
	cmp	r1, r6
	bhi	.L1122
	ldr	r3, [r7, #36]
	rsb	r6, r1, r6
	ldr	r1, .L1213
	mov	r9, #0
	rsb	r3, r4, r3
	mov	r8, #6
	add	r1, r1, r3
	str	r2, [fp, #-56]
	str	ip, [fp, #-60]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	mov	r4, r3, asl r4
	str	r6, [r7, #28]
	mov	r3, r6
	str	r5, [r7, #32]
	mov	r6, r9
	str	r4, [r7, #36]
	mov	r9, r3
	b	.L1125
.L1123:
	mov	r3, r4, asl #24
	mov	r1, r10, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r9, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1206
.L1125:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L1123
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	ip, r1, ip
	add	r5, r1, r5
	str	ip, [fp, #-52]
	bl	BsGet
	ldr	ip, [fp, #-52]
	and	ip, ip, #7
	orr	r0, r9, r0, asl ip
	b	.L1123
.L1204:
	ldr	r9, [fp, #-56]
	mov	r10, r10, asl #1
	orr	r10, r10, #1
	strb	r10, [r9]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1153
.L1122:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
.L1154:
	add	r2, r2, #1
	add	ip, ip, #1
	cmp	r2, #3
	bne	.L1126
	ldr	r3, [fp, #-64]
	subs	r3, r3, #1
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-48]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	bne	.L1135
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
.L1127:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1207
.L1128:
	mov	r0, r4, asl #24
	cmp	r0, r6
	bhi	.L1129
	ldr	r1, [r7, #36]
	rsb	r6, r0, r6
	ldr	r0, .L1213
	mov	r9, #0
	rsb	r1, r4, r1
	str	r3, [fp, #-52]
	add	r0, r0, r1
	mov	r8, #6
	str	r2, [fp, #-56]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r7, #28]
	mov	r4, r1, asl r4
	mov	r3, r6
	str	r5, [r7, #32]
	mov	r6, r9
	str	r4, [r7, #36]
	mov	r9, r3
	b	.L1132
.L1130:
	mov	r3, r4, asl #24
	mov	r1, r10, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r9, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1208
.L1132:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L1130
	rsb	r1, r5, #24
	rsb	ip, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	rsb	ip, r1, ip
	add	r5, r1, r5
	str	ip, [fp, #-48]
	bl	BsGet
	ldr	ip, [fp, #-48]
	and	ip, ip, #7
	orr	r0, r9, r0, asl ip
	b	.L1130
.L1206:
	ldr	ip, [fp, #-60]
	mov	r9, r6, asl #1
	orr	r9, r9, #1
	ldr	r2, [fp, #-56]
	strb	r9, [ip]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1154
.L1203:
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
	b	.L1113
.L1129:
	ldr	r1, .L1213
	add	r3, r3, #1
	cmp	r3, #3
	add	r2, r2, #1
	add	r1, r1, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r6, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1133
.L1209:
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1127
.L1208:
	ldr	r3, [fp, #-52]
	mov	r9, r6, asl #1
	ldr	r2, [fp, #-56]
	orr	r9, r9, #1
	add	r3, r3, #1
	cmp	r3, #3
	add	r2, r2, #1
	strb	r9, [r2, #-1]
	bne	.L1209
.L1133:
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	add	r3, r3, #33
	str	r3, [fp, #-68]
	cmp	r3, r2
	beq	.L1134
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1120
.L1205:
	rsb	r9, r5, #24
	mov	r0, r7
	bic	r9, r9, #7
	str	ip, [fp, #-56]
	str	r2, [fp, #-52]
	rsb	r8, r5, #16
	mov	r1, r9
	rsb	r8, r9, r8
	bl	BsGet
	and	r8, r8, #7
	add	r5, r9, r5
	ldr	ip, [fp, #-56]
	str	r5, [r7, #32]
	ldr	r2, [fp, #-52]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1121
.L1207:
	rsb	r9, r5, #24
	mov	r0, r7
	bic	r9, r9, #7
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	rsb	r8, r5, #16
	mov	r1, r9
	rsb	r8, r9, r8
	bl	BsGet
	and	r8, r8, #7
	add	r5, r9, r5
	ldr	r2, [fp, #-52]
	str	r5, [r7, #32]
	ldr	r3, [fp, #-48]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1128
.L1202:
	ldr	r2, [fp, #-48]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-11]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1152
.L1198:
	ldr	r2, [fp, #-48]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-22]
	ldr	r4, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r6, [r7, #28]
	b	.L1150
.L1134:
	ldr	r3, [fp, #-80]
	mov	ip, r7
	cmp	r3, #0
	beq	.L1090
	ldr	r3, [fp, #-76]
	add	r6, r3, #66
	str	r6, [fp, #-48]
	ldr	r6, [fp, #-84]
.L1147:
	ldr	r3, [r7, #36]
	ldr	r5, [r7, #32]
	sub	r2, r3, #1
	cmp	r5, #0
	mov	r3, r2, asl #8
	sub	r3, r3, r2, asl #2
	mov	r3, r3, lsr #8
	add	r4, r3, #1
	blt	.L1136
	ldr	r8, [r7, #28]
.L1137:
	mov	r2, r4, asl #24
	cmp	r2, r8
	bhi	.L1138
	ldr	r3, [r7, #36]
	rsb	r8, r2, r8
	ldr	r1, .L1213
	mov	r10, #0
	rsb	r3, r4, r3
	mov	r9, #6
	add	r1, r1, r3
	mov	r2, #1
	str	r6, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r3, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1141
.L1139:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1210
.L1141:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1139
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	str	r2, [fp, #-52]
	rsb	r6, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r6, #7
	ldr	r2, [fp, #-52]
	orr	r0, r8, r0, asl r3
	b	.L1139
.L1143:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r5, r3, r5
	str	r8, [r7, #28]
	mov	r3, r4, asl r3
	str	r5, [r7, #32]
	str	r3, [r7, #36]
.L1157:
	ldr	r3, [fp, #-48]
	add	r6, r6, #33
	cmp	r6, r3
	bne	.L1147
.L1090:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1138:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r5, r3, r5
	str	r8, [r7, #28]
	mov	r3, r4, asl r3
	str	r5, [r7, #32]
	str	r3, [r7, #36]
.L1156:
	sub	r3, r3, #1
	cmp	r5, #0
	mov	r2, r3, asl #8
	sub	r3, r2, r3, asl #2
	mov	r3, r3, lsr #8
	add	r4, r3, #1
	blt	.L1211
.L1142:
	mov	r2, r4, asl #24
	cmp	r2, r8
	bhi	.L1143
	ldr	r3, [r7, #36]
	rsb	r8, r2, r8
	ldr	r1, .L1213
	mov	r10, #0
	rsb	r3, r4, r3
	mov	r9, #6
	add	r1, r1, r3
	mov	r2, #1
	str	r6, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r5, r4, r5
	str	r8, [r7, #28]
	mov	r4, r3, asl r4
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	b	.L1146
.L1144:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r7, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r7, #28]
	str	r5, [r7, #32]
	str	r4, [r7, #36]
	beq	.L1212
.L1146:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1144
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r7
	str	r2, [fp, #-52]
	rsb	r6, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r6, #7
	ldr	r2, [fp, #-52]
	orr	r0, r8, r0, asl r3
	b	.L1144
.L1212:
	ldr	r6, [fp, #-56]
	mov	r3, r10, asl #1
	orr	r3, r3, #1
	strb	r3, [r6, #35]
	b	.L1157
.L1210:
	ldr	r6, [fp, #-56]
	mov	r3, r10, asl #1
	orr	r3, r3, #1
	strb	r3, [r6, #34]
	ldr	r3, [r7, #36]
	ldr	r5, [r7, #32]
	ldr	r8, [r7, #28]
	b	.L1156
.L1195:
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
	b	.L1091
.L1201:
	rsb	r9, r5, #24
	mov	r0, r7
	bic	r9, r9, #7
	rsb	r8, r5, #16
	rsb	r8, r9, r8
	add	r5, r9, r5
	mov	r1, r9
	and	r8, r8, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1108
.L1197:
	rsb	r9, r5, #24
	mov	r0, r7
	bic	r9, r9, #7
	rsb	r8, r5, #16
	rsb	r8, r9, r8
	add	r5, r9, r5
	mov	r1, r9
	and	r8, r8, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r6, r0, asl r8
	str	r0, [r7, #28]
	mov	r6, r0
	b	.L1097
.L1136:
	rsb	r9, r5, #24
	mov	r0, r7
	bic	r9, r9, #7
	ldr	r8, [r7, #28]
	rsb	r10, r5, #16
	add	r5, r5, r9
	mov	r1, r9
	rsb	r10, r9, r10
	bl	BsGet
	and	r10, r10, #7
	str	r5, [r7, #32]
	orr	r0, r8, r0, asl r10
	str	r0, [r7, #28]
	mov	r8, r0
	b	.L1137
.L1211:
	rsb	r10, r5, #24
	mov	r0, r7
	bic	r10, r10, #7
	rsb	r9, r5, #16
	rsb	r9, r10, r9
	add	r5, r10, r5
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r7, #28]
	mov	r8, r0
	b	.L1142
.L1214:
	.align	2
.L1213:
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
	add	r10, r0, #2000
	add	r10, r10, #15
	ldr	r7, .L1365
	str	r0, [fp, #-72]
	mov	r6, r1
	add	r0, r0, #2016
	mov	r8, r10
	add	r0, r0, #2
	mov	r9, r3
	str	r0, [fp, #-76]
	mov	r3, #0
	str	r2, [fp, #-56]
	str	r3, [fp, #-48]
.L1219:
	ldr	r4, [r6, #36]
	ldr	r5, [r6, #32]
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r2, r4, asl #8
	sub	r4, r2, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1216
	ldr	r10, [r6, #28]
.L1217:
	mov	ip, r4, asl #24
	mov	r1, r8
	cmp	ip, r10
	mov	r0, r6
	rsb	r2, ip, r10
	bhi	.L1218
	ldr	ip, [r6, #36]
	rsb	r4, r4, ip
	add	ip, r7, r4
	ldrb	ip, [ip, #24]	@ zero_extendqisi2
	mov	r2, r2, asl ip
	rsb	r5, ip, r5
	mov	r4, r4, asl ip
	str	r2, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1296:
	ldr	r3, [fp, #-76]
	add	r8, r8, #1
	cmp	r8, r3
	bne	.L1219
	ldr	r8, [fp, #-56]
	adds	r8, r8, #0
	movne	r8, #1
	cmp	r9, #0
	movne	r8, #0
	cmp	r8, #0
	bne	.L1342
.L1220:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #16]
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1218:
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1296
.L1216:
	rsb	r2, r5, #24
	rsb	ip, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	ip, r2, ip
	ldr	r10, [r6, #28]
	mov	r1, r2
	str	ip, [fp, #-64]
	str	r2, [fp, #-60]
	bl	BsGet
	ldr	ip, [fp, #-64]
	ldr	r2, [fp, #-60]
	and	ip, ip, #7
	add	r5, r5, r2
	str	r5, [r6, #32]
	orr	r0, r10, r0, asl ip
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1217
.L1342:
	mov	r1, r6
	ldr	r0, [fp, #-72]
	bl	Vp9_ReadInterModeProbs
	ldr	r3, [fp, #4]
	cmp	r3, #4
	beq	.L1343
.L1221:
	ldr	r3, [fp, #-72]
	add	r10, r3, #1968
	mov	r3, r10
	add	r3, r3, #15
	add	r10, r10, #11
	mov	r5, r3
.L1225:
	ldr	r4, [r6, #36]
	ldr	r8, [r6, #32]
	sub	r4, r4, #1
	cmp	r8, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1222
	ldr	r3, [r6, #28]
.L1223:
	mov	r2, r4, asl #24
	mov	r1, r10
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1224
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	add	r3, r7, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1297:
	add	r10, r10, #1
	cmp	r10, r5
	bne	.L1225
	ldr	ip, [fp, #-72]
	sub	r3, fp, #48
	ldr	r2, [fp, #8]
	mov	r1, r6
	add	lr, ip, #1728
	mov	r0, ip
	add	ip, ip, #1760
	mov	r4, lr
	mov	r5, ip
	bl	Vp9_ReadCompPred
	add	r3, r4, #9
	mov	lr, r4
	add	r4, r6, #28
	str	r3, [fp, #-56]
	add	r3, r5, #13
	str	r3, [fp, #-80]
	ldmia	r4, {r4, r5, r9}
	mov	r8, r5
.L1226:
	ldr	r3, [fp, #-56]
	sub	r10, r3, #9
.L1259:
	sub	r5, r9, #1
	cmp	r8, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L1344
.L1227:
	mov	r9, r5, asl #24
	cmp	r9, r4
	bhi	.L1228
	ldr	r3, [r6, #36]
	rsb	r9, r9, r4
	rsb	r5, r5, r3
	add	r3, r7, r5
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1345
.L1229:
	mov	r2, r4, asl #24
	cmp	r2, r9
	bhi	.L1230
	ldr	r3, [r6, #36]
	rsb	r9, r2, r9
	rsb	r4, r4, r3
	add	r3, r7, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
	mov	r3, r4, asl r0
	rsb	r4, r0, r5
	cmp	r4, #0
	sub	r5, r3, #1
	ubfx	r5, r5, #1, #24
	mov	r9, r9, asl r0
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r9, [r6, #28]
	blt	.L1346
.L1232:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1237
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L1347
.L1239:
	mov	r2, r5, asl #24
	cmp	r2, r4
	bhi	.L1243
	ldr	r1, [r6, #36]
	rsb	r2, r2, r4
	mov	r8, #0
	mov	r3, #6
	rsb	r5, r5, r1
	str	r10, [fp, #-68]
	add	r1, r7, r5
	mov	r10, r8
	mov	ip, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r4
	rsb	r9, r4, r9
	str	r2, [r6, #28]
	mov	r4, r5, asl r4
	str	r9, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	mov	r8, r2
	b	.L1244
.L1248:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1348
.L1244:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1248
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
	b	.L1248
.L1228:
	add	r3, r7, r5
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r9
	rsb	r8, r9, r8
	str	r4, [r6, #28]
	mov	r9, r5, asl r9
	str	r8, [r6, #32]
	str	r9, [r6, #36]
.L1298:
	ldr	r3, [fp, #-56]
	add	r10, r10, #1
	cmp	r10, r3
	bne	.L1259
	ldr	r2, [fp, #-80]
	add	r3, r10, #9
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L1226
	ldr	r3, [fp, #-72]
	add	r2, r3, #1888
	add	r3, r3, #1936
	add	r3, r3, #14
	str	r3, [fp, #-64]
	mov	r3, r9
	add	r2, r2, #14
	str	r2, [fp, #-60]
.L1260:
	ldr	r2, [fp, #-60]
	mov	r10, #0
	mov	r9, r3
	str	r2, [fp, #-56]
.L1295:
	sub	r9, r9, #1
	cmp	r8, #0
	mov	r2, r9, asl #8
	sub	r9, r2, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1349
.L1261:
	mov	r0, r9, asl #24
	cmp	r0, r4
	bhi	.L1262
	ldr	r3, [r6, #36]
	rsb	r0, r0, r4
	rsb	r3, r9, r3
	add	r2, r7, r3
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
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
	blt	.L1350
.L1263:
	mov	r2, r4, asl #24
	cmp	r2, r9
	bhi	.L1264
	ldr	ip, [r6, #36]
	rsb	r9, r2, r9
	rsb	r4, r4, ip
	add	r3, r7, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1351
.L1266:
	mov	r3, r5, asl #24
	cmp	r3, r9
	bhi	.L1271
	ldr	r1, [r6, #36]
	rsb	r3, r3, r9
	rsb	r5, r5, r1
	add	r2, r7, r5
	ldrb	ip, [r2, #24]	@ zero_extendqisi2
	mov	r1, r5, asl ip
	rsb	r5, ip, r4
	sub	r9, r1, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r4, r3, asl ip
	str	r1, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r4, [r6, #28]
	blt	.L1352
.L1273:
	mov	r3, r9, asl #24
	cmp	r3, r4
	bhi	.L1277
	ldr	r1, [r6, #36]
	rsb	r0, r3, r4
	mov	r2, #6
	mov	r3, #0
	rsb	r4, r9, r1
	str	r10, [fp, #-80]
	add	r1, r7, r4
	mov	ip, #1
	mov	r10, r3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r8, r1, r5
	mov	r9, r0, asl r1
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r2
	str	r4, [r6, #36]
	b	.L1278
.L1282:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r9, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1353
.L1278:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L1282
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
	b	.L1282
.L1262:
	add	r3, r7, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r8
	mov	r9, r9, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r9, [r6, #36]
.L1299:
	add	r10, r10, #1
	ldr	r3, [fp, #-56]
	cmp	r10, #3
	add	r3, r3, #1
	str	r3, [fp, #-56]
	addne	r4, r6, #28
	ldmneia	r4, {r4, r8, r9}
	bne	.L1295
.L1354:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	add	r3, r3, #3
	str	r3, [fp, #-60]
	cmp	r3, r2
	beq	.L1294
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r8, [r6, #32]
	b	.L1260
.L1349:
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
	b	.L1261
.L1264:
	add	r3, r7, r4
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-80]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r8, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L1269
.L1267:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1355
.L1269:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1267
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
	b	.L1267
.L1355:
	mov	r8, r10
	ldr	r10, [fp, #-80]
.L1270:
	ldr	r3, [fp, #-56]
	add	r8, r7, r8
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1287
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1288
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1288:
	add	r3, r3, #1
.L1290:
	ldr	r2, [fp, #-56]
	strb	r3, [r2]
	b	.L1299
.L1287:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1291
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1291:
	rsb	r3, r3, #255
	b	.L1290
.L1344:
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
	b	.L1227
.L1230:
	add	r3, r7, r4
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #28]
	mov	r4, r4, asl r1
	mov	r8, r9
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	mov	r9, r2
	b	.L1235
.L1233:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1356
.L1235:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1233
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
	b	.L1233
.L1356:
	mov	r8, r10
	ldr	r10, [fp, #-68]
.L1236:
	ldrb	r2, [r10]	@ zero_extendqisi2
	add	r8, r7, r8
	sub	ip, r2, #1
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1253
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1254
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1254:
	add	r3, r3, #1
.L1256:
	add	r4, r6, #28
	strb	r3, [r10]
	ldmia	r4, {r4, r8, r9}
	b	.L1298
.L1253:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1257
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1257:
	rsb	r3, r3, #255
	b	.L1256
.L1271:
	add	r3, r7, r5
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-80]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1276
.L1274:
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
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1357
.L1276:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1274
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
	b	.L1274
.L1357:
	mov	r8, r10
	ldr	r10, [fp, #-80]
	add	r8, r8, #16
	b	.L1270
.L1353:
	mov	r3, r10
	cmp	r3, #64
	ldr	r10, [fp, #-80]
	bgt	.L1358
.L1284:
	add	r8, r3, #64
	b	.L1270
.L1237:
	add	r3, r7, r5
	mov	r8, #0
	mov	r2, #3
	str	r10, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	ip, #1
	mov	r9, r9, asl r1
	rsb	r4, r1, r4
	str	r9, [r6, #28]
	mov	r5, r5, asl r1
	mov	r8, r9
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	mov	r9, r2
	b	.L1242
.L1240:
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
	add	r2, r7, r5
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r4, r2, r4
	mov	r5, r5, asl r2
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1359
.L1242:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1240
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
	b	.L1240
.L1359:
	mov	r8, r10
	ldr	r10, [fp, #-68]
	add	r8, r8, #16
	b	.L1236
.L1348:
	mov	r2, r8
	mov	r8, r10
	cmp	r8, #64
	ldr	r10, [fp, #-68]
	bgt	.L1360
.L1250:
	add	r8, r8, #64
	b	.L1236
.L1277:
	add	r3, r7, r9
	mov	r8, #0
	mov	r2, #4
	str	r10, [fp, #-80]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	ip, #1
	mov	r3, r4, asl r1
	mov	r9, r9, asl r1
	rsb	r5, r1, r5
	str	r9, [r6, #36]
	mov	r4, r9
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	mov	r8, r3
	mov	r9, r2
	b	.L1281
.L1279:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1361
.L1281:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1279
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
	b	.L1279
.L1361:
	mov	r8, r10
	ldr	r10, [fp, #-80]
	add	r8, r8, #32
	b	.L1270
.L1350:
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
	b	.L1263
.L1224:
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	b	.L1297
.L1243:
	add	r3, r7, r5
	mov	r8, #0
	mov	ip, #4
	str	r10, [fp, #-68]
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r10, r8
	mov	r2, #1
	mov	r3, r4, asl r1
	rsb	r9, r1, r9
	mov	r4, r5, asl r1
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	mov	r5, ip
	str	r4, [r6, #36]
	mov	r8, r3
	b	.L1247
.L1245:
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
	add	r1, r7, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r1
	rsb	r9, r1, r9
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1362
.L1247:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1245
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
	orr	r0, r8, r0, asl ip
	b	.L1245
.L1362:
	mov	r8, r10
	ldr	r10, [fp, #-68]
	add	r8, r8, #32
	b	.L1236
.L1345:
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
	b	.L1229
.L1358:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r3, r3, asl #1
	add	r4, r4, #1
	sub	r5, r3, #65
	movge	r0, r9
	blt	.L1363
.L1285:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r3, r5, r3
	rsbls	r4, r4, r2
	add	r2, r7, r4
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r1
	rsb	r2, r1, r8
	mov	r4, r4, asl r1
	str	r9, [r6, #28]
	str	r2, [r6, #32]
	str	r4, [r6, #36]
	b	.L1284
.L1351:
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
	b	.L1266
.L1294:
	ldr	r1, [fp, #-76]
	mov	r0, r6
	ldr	r2, [fp, #12]
	bl	Vp9_ReadMvProbs
	b	.L1220
.L1360:
	sub	r4, r4, #1
	cmp	r9, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r5, r8, #65
	movge	r0, r2
	blt	.L1364
.L1251:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r8, #1
	movhi	r8, #0
	add	r8, r5, r8
	rsbls	r4, r4, r1
	add	r3, r7, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r2, r0, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	r2, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L1250
.L1366:
	.align	2
.L1365:
	.word	.LANCHOR0
.L1346:
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
	b	.L1232
.L1352:
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
	b	.L1273
.L1222:
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
	b	.L1223
.L1347:
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
	b	.L1239
.L1363:
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
	b	.L1285
.L1343:
	mov	r1, r6
	ldr	r0, [fp, #-72]
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1221
.L1364:
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
	b	.L1251
	UNWIND(.fnend)
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.global	__aeabi_idiv
	.align	2
	.global	Vp9_AdaptCoefProbs
	.type	Vp9_AdaptCoefProbs, %function
Vp9_AdaptCoefProbs:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	lr, #432
	mul	lr, lr, r3
	mov	ip, r3, asl #9
	add	ip, ip, r3, lsl #6
	ldr	r9, [fp, #4]
	mov	r4, r3, asl #11
	add	ip, ip, #9216
	add	r3, r4, r3, lsl #8
	add	ip, ip, #8
	add	r0, r0, lr
	add	r3, r2, r3
	str	r0, [fp, #-92]
	add	r0, r2, ip
	str	r3, [fp, #-116]
	add	r3, r1, lr
	str	r0, [fp, #-112]
	str	r3, [fp, #-96]
	mov	r3, #0
	str	r3, [fp, #-84]
.L1368:
	ldr	r3, [fp, #-112]
	str	r3, [fp, #-100]
	ldr	r3, [fp, #-116]
	str	r3, [fp, #-108]
	mov	r3, #0
	str	r3, [fp, #-104]
.L1379:
	mov	r3, #0
	str	r3, [fp, #-72]
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-108]
	ldr	r2, [fp, #-100]
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-104]
	str	r2, [fp, #-80]
	add	r3, r3, #2
	str	r3, [fp, #-88]
.L1377:
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-88]
	ldr	r7, [fp, #-76]
	add	r3, r3, r2
	ldr	r2, [fp, #-80]
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-84]
	add	r3, r3, r2
	ldr	r2, [fp, #-92]
	add	r10, r2, r3
	ldr	r2, [fp, #-96]
	str	r10, [fp, #-48]
	add	r8, r2, r3
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L1375
.L1373:
	ldr	r2, [fp, #-56]
	ldr	r4, [r7, #8]
	ldr	r6, [r7]
	ldr	r3, [r2, #4]!
	ldrb	r10, [r8, #-2]	@ zero_extendqisi2
	subs	r1, r3, #0
	str	r2, [fp, #-56]
	ldr	r2, [r7, #4]
	moveq	r5, #128
	add	r4, r2, r4
	str	r2, [fp, #-60]
	ldr	r2, [r7, #12]
	beq	.L1369
	mov	r0, r1, asr #1
	str	r3, [fp, #-68]
	add	r0, r0, r2, lsl #8
	bl	__aeabi_idiv
	ldr	r3, [fp, #-68]
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r5, r0
.L1369:
	cmp	r9, r3
	mov	r1, r9
	movcs	r0, r3
	ldr	r3, [fp, #8]
	movcc	r0, r9
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	adds	r3, r4, r6
	moveq	r6, #128
	rsb	r2, r0, #256
	mul	r10, r2, r10
	ldr	r2, [fp, #-48]
	add	r10, r10, #128
	mla	r10, r0, r5, r10
	mov	r10, r10, lsr #8
	strb	r10, [r2, #-2]
	ldrb	r5, [r8, #-1]	@ zero_extendqisi2
	beq	.L1370
	mov	r0, r3, asr #1
	mov	r1, r3
	add	r0, r0, r6, lsl #8
	str	r3, [fp, #-68]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-68]
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r6, r0
.L1370:
	cmp	r3, r9
	mov	r1, r9
	movcc	r0, r3
	ldr	r3, [fp, #8]
	movcs	r0, r9
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	cmp	r4, #0
	rsb	r3, r0, #256
	mul	r5, r5, r3
	ldr	r3, [fp, #-48]
	add	r5, r5, #128
	mla	r6, r0, r6, r5
	mov	r6, r6, lsr #8
	strb	r6, [r3, #-1]
	moveq	r6, #128
	ldrb	r5, [r8]	@ zero_extendqisi2
	beq	.L1371
	ldr	r3, [fp, #-60]
	mov	r0, r4, asr #1
	mov	r1, r4
	add	r0, r0, r3, lsl #8
	bl	__aeabi_idiv
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r6, r0
.L1371:
	ldr	r3, [fp, #-52]
	cmp	r4, r9
	mov	r1, r9
	add	r8, r8, #3
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #8]
	movcc	r0, r4
	movcs	r0, r9
	add	r7, r7, #16
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	rsb	r3, r0, #256
	mul	r5, r5, r3
	ldr	r3, [fp, #-48]
	add	r5, r5, #128
	mla	r6, r0, r6, r5
	ubfx	r6, r6, #8, #8
	strb	r6, [r3], #3
	str	r3, [fp, #-48]
.L1375:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-52]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	blt	.L1373
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-72]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, #6
	ldr	r3, [fp, #-76]
	add	r2, r2, #18
	str	r2, [fp, #-72]
	add	r3, r3, #96
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-80]
	add	r3, r3, #24
	str	r3, [fp, #-80]
	bne	.L1377
	ldr	r3, [fp, #-104]
	ldr	r2, [fp, #-108]
	add	r3, r3, #108
	str	r3, [fp, #-104]
	cmp	r3, #216
	ldr	r3, [fp, #-100]
	add	r2, r2, #576
	str	r2, [fp, #-108]
	add	r3, r3, #144
	str	r3, [fp, #-100]
	bne	.L1379
	ldr	r3, [fp, #-84]
	ldr	r2, [fp, #-116]
	add	r3, r3, #216
	str	r3, [fp, #-84]
	cmp	r3, #432
	ldr	r3, [fp, #-112]
	add	r2, r2, #1152
	str	r2, [fp, #-116]
	add	r3, r3, #288
	str	r3, [fp, #-112]
	bne	.L1368
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_AdaptCoefProbs, .-Vp9_AdaptCoefProbs
	.align	2
	.global	Vp9_AdaptResidualProbs
	.type	Vp9_AdaptResidualProbs, %function
Vp9_AdaptResidualProbs:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 0
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
	ldr	r5, [fp, #12]
	ldr	ip, [fp, #8]
	mov	r7, r0
	clz	r3, r5
	ldr	r5, [fp, #4]
	adds	ip, ip, #0
	mov	r6, r1
	mov	r3, r3, lsr #5
	mov	r8, r2
	movne	ip, #1
	cmp	r5, #0
	orreq	ip, ip, #1
	cmp	r3, ip
	mov	r4, #0
	mov	r9, #24
	movhi	r5, #128
	movls	r5, #112
.L1386:
	mov	r3, r4
	str	r5, [sp, #4]
	str	r9, [sp]
	add	r4, r4, #1
	mov	r2, r8
	mov	r1, r6
	mov	r0, r7
	bl	Vp9_AdaptCoefProbs
	cmp	r4, #4
	bne	.L1386
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_AdaptResidualProbs, .-Vp9_AdaptResidualProbs
	.align	2
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	ldrsb	r0, [r1, r0]
	mov	r5, r1
	mov	r7, r2
	mov	r8, r3
	cmp	r0, #0
	ldr	r6, [fp, #4]
	ble	.L1394
	str	r6, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r5, r4
	mov	r9, r0
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	ble	.L1395
.L1392:
	mov	r1, r5
	str	r6, [sp]
	mov	r3, r8
	mov	r2, r7
	bl	Vp9_AdaptProbs
	mov	r5, r0
.L1393:
	ldrb	r0, [r8, r4, lsr #1]	@ zero_extendqisi2
	sub	r1, fp, #44
	str	r9, [fp, #-44]
	str	r5, [fp, #-40]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r7, r4, lsr #1]
	add	r0, r5, r9
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1394:
	mov	r0, r0, asl #2
	add	r3, r5, r4
	rsb	r0, r0, #0
	ldr	r9, [r6, r0]
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	bgt	.L1392
.L1395:
	mov	r0, r0, asl #2
	rsb	r0, r0, #0
	ldr	r5, [r6, r0]
	b	.L1393
	UNWIND(.fnend)
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	2
	.global	Vp9_AdaptModeProbs
	.type	Vp9_AdaptModeProbs, %function
Vp9_AdaptModeProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	add	r10, r0, #1968
	add	r8, r1, #1968
	add	r4, r2, #8192
	add	r8, r8, #10
	add	r10, r10, #10
	mov	r6, r0
	mov	r7, r1
	mov	r9, r3
	mov	r5, #0
.L1397:
	ldr	r1, [r4, #3348]
	ldrb	r0, [r8, #1]!	@ zero_extendqisi2
	add	r1, r1, r5, lsl #3
	add	r5, r5, #1
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #4
	strb	r0, [r10, #1]!
	bne	.L1397
	add	r8, r7, #1968
	add	r10, r6, #1968
	add	r8, r8, #14
	add	r10, r10, #14
	mov	r5, #0
.L1398:
	ldr	r1, [r4, #3352]
	ldrb	r0, [r8, #1]!	@ zero_extendqisi2
	add	r1, r1, r5, lsl #3
	add	r5, r5, #1
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #5
	strb	r0, [r10, #1]!
	bne	.L1398
	add	r8, r7, #1984
	add	r10, r6, #1984
	add	r8, r8, #13
	add	r10, r10, #13
	mov	r5, #0
.L1399:
	ldr	r1, [r4, #3360]
	ldrb	r0, [r8, #1]!	@ zero_extendqisi2
	add	r1, r1, r5, lsl #3
	add	r5, r5, #1
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #5
	strb	r0, [r10, #1]!
	bne	.L1399
	mov	r10, r6
	mov	r8, r7
	mov	r5, #8
	str	r7, [fp, #-100]
	str	r6, [fp, #-96]
.L1400:
	ldr	r1, [r4, #3356]
	sub	r3, r5, #8
	ldrb	r0, [r8, #1988]	@ zero_extendqisi2
	add	r10, r10, #2
	add	r1, r1, r3
	add	r8, r8, #2
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r10, #1986]
	ldr	r1, [r4, #3356]
	ldrb	r0, [r8, #1987]	@ zero_extendqisi2
	add	r1, r1, r5
	add	r5, r5, #16
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #88
	strb	r0, [r10, #1987]
	bne	.L1400
	mov	r8, #0
	mov	r5, r8
.L1401:
	ldr	r0, [r4, #3344]
	add	r2, r8, #1952
	add	r2, r2, #6
	ldr	r1, .L1441
	add	r0, r0, r5
	add	r3, r7, r2
	str	r0, [sp]
	add	r2, r6, r2
	add	r5, r5, #16
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #112
	add	r8, r8, #3
	bne	.L1401
	mov	r8, #0
	mov	r5, r8
.L1402:
	ldr	r0, [r4, #1024]
	add	r2, r8, #1728
	add	r3, r7, r2
	ldr	r1, .L1441+4
	add	r0, r0, r5
	add	r2, r6, r2
	str	r0, [sp]
	add	r5, r5, #40
	mov	r0, #0
	add	r8, r8, #9
	bl	Vp9_AdaptProbs
	cmp	r5, #160
	bne	.L1402
	mov	r8, #0
	mov	r5, r8
.L1403:
	ldr	r0, [r4, #1028]
	add	r2, r8, #1760
	add	r2, r2, #4
	ldr	r1, .L1441+4
	add	r0, r0, r5
	add	r3, r7, r2
	str	r0, [sp]
	add	r2, r6, r2
	add	r5, r5, #40
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #400
	add	r8, r8, #9
	bne	.L1403
	mov	r8, #0
	mov	r5, r8
.L1404:
	ldr	r0, [r4, #1032]
	add	r2, r8, #1888
	add	r2, r2, #14
	ldr	r1, .L1441+8
	add	r0, r0, r5
	add	r3, r7, r2
	str	r0, [sp]
	add	r2, r6, r2
	add	r5, r5, #16
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #256
	add	r8, r8, #3
	bne	.L1404
	cmp	r9, #4
	beq	.L1439
	ldr	r3, [fp, #4]
	cmp	r3, #4
	beq	.L1440
.L1415:
	add	r7, r7, #2000
	add	r6, r6, #2000
	add	r7, r7, #14
	add	r6, r6, #14
	mov	r5, #0
.L1411:
	ldr	r1, [r4, #3376]
	ldrb	r0, [r7, #1]!	@ zero_extendqisi2
	add	r1, r1, r5, lsl #3
	add	r5, r5, #1
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #3
	strb	r0, [r6, #1]!
	bne	.L1411
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1439:
	mov	r9, #0
	mov	r5, r9
.L1406:
	ldr	ip, [r4, #3340]
	add	r2, r9, #1936
	add	r2, r2, #14
	ldr	r1, .L1441+12
	add	ip, ip, r5
	add	r3, r7, r2
	mov	r0, #0
	add	r2, r6, r2
	str	ip, [sp]
	add	r5, r5, #12
	bl	Vp9_AdaptProbs
	cmp	r5, #48
	add	r9, r9, #2
	bne	.L1406
	ldr	r3, [fp, #4]
	cmp	r3, #4
	bne	.L1415
.L1440:
	mov	r8, #0
	add	r3, r7, #2000
	add	r2, r6, #2000
	str	r6, [fp, #-120]
	str	r7, [fp, #-124]
	mov	r7, r8
	ldr	r6, [fp, #-96]
	mov	r1, r3
	ldr	r8, [fp, #-100]
	add	r3, r3, #12
	str	r3, [fp, #-116]
	add	r3, r2, #12
	str	r3, [fp, #-112]
	add	r3, r1, #2
	str	r3, [fp, #-108]
	add	r3, r2, #2
	str	r3, [fp, #-104]
.L1410:
	ldr	r3, [fp, #-116]
	sub	r1, fp, #92
	ldr	ip, [r4, #3372]
	mov	r5, r7, asl #4
	ldr	r10, [fp, #-104]
	ldrb	r0, [r3, #1]!	@ zero_extendqisi2
	ldr	r9, [fp, #-108]
	str	r3, [fp, #-116]
	ldr	r3, [ip, r7, asl #3]
	add	ip, ip, r7, lsl #3
	str	r3, [fp, #-92]
	ldr	r3, [ip, #4]
	str	r3, [fp, #-88]
	bl	Vp9_ModeMvMergeProbs
	ldr	r3, [fp, #-112]
	sub	ip, r5, r7, asl #2
	sub	r1, fp, #84
	str	r5, [fp, #-96]
	mov	r5, #0
	strb	r0, [r3, #1]!
	ldr	r0, [r4, #3368]
	str	r3, [fp, #-112]
	ldr	lr, [r0, ip]
	add	r0, r0, ip
	str	lr, [fp, #-84]
	ldmib	r0, {ip, lr}
	add	ip, ip, lr
	str	ip, [fp, #-80]
	ldr	ip, [r0, #4]
	str	ip, [fp, #-76]
	ldr	ip, [r0, #8]
	ldrb	r0, [r8, #2009]	@ zero_extendqisi2
	str	ip, [fp, #-72]
	bl	Vp9_ModeMvMergeProbs
	sub	r1, fp, #76
	strb	r0, [r6, #2009]
	ldrb	r0, [r8, #2010]	@ zero_extendqisi2
	bl	Vp9_ModeMvMergeProbs
	ldr	r3, [fp, #-96]
	strb	r0, [r6, #2010]
	ldr	r1, [r4, #3364]
	add	r3, r1, r3
	ldr	r1, [r1, r7, asl #4]
	str	r1, [fp, #-68]
	ldmib	r3, {r0, r1}
	add	r1, r1, r0
	ldr	r0, [r3, #12]
	add	r1, r1, r0
	str	r1, [fp, #-64]
	ldr	r1, [r3, #4]
	str	r1, [fp, #-60]
	ldr	r1, [r3, #8]
	add	r1, r1, r0
	str	r1, [fp, #-56]
	ldr	r1, [r3, #8]
	str	r1, [fp, #-52]
	ldr	r3, [r3, #12]
	str	r3, [fp, #-48]
.L1409:
	sub	r3, fp, #68
	ldrb	r0, [r9, #1]!	@ zero_extendqisi2
	add	r1, r3, r5
	add	r5, r5, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #24
	strb	r0, [r10, #1]!
	bne	.L1409
	ldr	r3, [fp, #-108]
	add	r7, r7, #1
	cmp	r7, #2
	add	r8, r8, #2
	add	r3, r3, #3
	str	r3, [fp, #-108]
	ldr	r3, [fp, #-104]
	add	r6, r6, #2
	add	r3, r3, #3
	str	r3, [fp, #-104]
	bne	.L1410
	ldr	r6, [fp, #-120]
	ldr	r7, [fp, #-124]
	b	.L1415
.L1442:
	.align	2
.L1441:
	.word	.LANCHOR0+536
	.word	.LANCHOR0+544
	.word	.LANCHOR0+564
	.word	.LANCHOR0+572
	UNWIND(.fnend)
	.size	Vp9_AdaptModeProbs, .-Vp9_AdaptModeProbs
	.align	2
	.global	Vp9_AdaptMvProbs
	.type	Vp9_AdaptMvProbs, %function
Vp9_AdaptMvProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r7, r0
	mov	r8, r1
	mov	r4, r2
	str	r2, [fp, #-100]
	sub	r0, fp, #88
	mov	r2, #6
	ldr	r1, .L1452
	str	r3, [fp, #-104]
	bl	memcpy
	mov	r2, #20
	ldr	r1, .L1452+4
	sub	r0, fp, #64
	bl	memcpy
	mov	r2, #6
	ldr	r1, .L1452
	sub	r0, fp, #80
	bl	memcpy
	add	r1, r4, #8192
	add	r3, r8, #2016
	add	r2, r7, #2016
	ldr	ip, [r1, #3380]
	add	r3, r3, #2
	sub	r1, fp, #88
	add	r2, r2, #2
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	mov	r3, #0
	str	r3, [fp, #-96]
.L1446:
	ldr	r2, [fp, #-96]
	mov	r4, #0
	ldr	r3, [fp, #-100]
	mov	r6, r8
	ldrb	r0, [r8, #2021]	@ zero_extendqisi2
	mov	r5, r7
	add	r9, r3, r2, lsl #5
	add	r3, r9, #11520
	add	r10, r9, #11584
	add	r10, r10, #4
	ldr	r1, [r3, #56]
	bl	Vp9_ModeMvMergeProbs
	add	lr, r9, #11520
	add	lr, lr, #60
	add	r3, r8, #2016
	add	r2, r7, #2016
	add	r3, r3, #6
	add	r2, r2, #6
	sub	r1, fp, #64
	strb	r0, [r7, #2021]
	mov	r0, r4
	ldr	lr, [lr]
	str	lr, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r9, #11584
	ldrb	r0, [r6, #2032]!	@ zero_extendqisi2
	sub	r1, fp, #72
	ldr	r3, [r3]
	ldmia	r3, {r2, r3}
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r5, #2032]!
.L1444:
	ldr	r1, [r10]
	ldrb	r0, [r6, #1]!	@ zero_extendqisi2
	add	r1, r1, r4, lsl #3
	add	r4, r4, #1
	bl	Vp9_ModeMvMergeProbs
	cmp	r4, #10
	strb	r0, [r5, #1]!
	bne	.L1444
	add	r4, r9, #11584
	add	r3, r8, #2032
	add	r2, r7, #2032
	add	r3, r3, #11
	ldr	ip, [r4, #8]
	add	r2, r2, #11
	sub	r1, fp, #80
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	ldr	r1, [r4, #8]
	add	r3, r8, #2032
	add	r2, r7, #2032
	add	r1, r1, #16
	add	r3, r3, #14
	str	r1, [sp]
	add	r2, r2, #14
	sub	r1, fp, #80
	mov	r0, #0
	bl	Vp9_AdaptProbs
	add	r1, r9, #11584
	add	r3, r8, #2048
	add	r2, r7, #2048
	ldr	ip, [r1, #12]
	add	r3, r3, #1
	add	r2, r2, #1
	sub	r1, fp, #80
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	ldr	r3, [fp, #-104]
	cmp	r3, #0
	beq	.L1445
	add	r3, r9, #11584
	ldrb	r0, [r8, #2052]	@ zero_extendqisi2
	add	r9, r9, #11584
	ldr	r1, [r3, #16]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r7, #2052]
	ldr	r1, [r9, #20]
	ldrb	r0, [r8, #2053]	@ zero_extendqisi2
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r7, #2053]
.L1445:
	ldr	r3, [fp, #-96]
	add	r8, r8, #33
	add	r7, r7, #33
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, #2
	bne	.L1446
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1453:
	.align	2
.L1452:
	.word	.LANCHOR0+576
	.word	.LANCHOR0+584
	UNWIND(.fnend)
	.size	Vp9_AdaptMvProbs, .-Vp9_AdaptMvProbs
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
	ldr	r7, .L1457
	movw	r6, #10820
	movt	r6, 4
	add	r6, r0, r6
	mov	r5, r0
	mov	r1, #0
	movw	r2, #2868
	ldr	r3, [r7, #48]
	mov	r0, r6
	add	r4, r5, #270336
	blx	r3
	add	r3, r5, #274432
	movw	r0, #13688
	mov	r2, #3
	movt	r0, 4
	str	r2, [r3, #980]
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
.L1458:
	.align	2
.L1457:
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
	ldr	r1, .L1473
	add	r4, r5, #274432
	bl	dprint_vfmw
	ldr	r3, [r8, #616]
	ldr	r10, .L1473+4
	mov	r1, #0
	cmp	r3, #1
	ldr	r6, [r4, #1744]
	addeq	r7, r5, #294912
	addeq	r3, r5, #270336
	mov	r0, r5
	movne	r9, #0
	ldreq	r2, [r7, #3380]
	addne	r7, r5, #294912
	ldreq	r9, [r3, #2568]
	ldr	r3, [r10, #48]
	strne	r9, [fp, #-48]
	streq	r2, [fp, #-48]
	movw	r2, #36296
	movt	r2, 4
	blx	r3
	movw	r0, #13688
	str	r6, [r4, #1744]
	movt	r0, 4
	add	r0, r5, r0
	bl	ResetVoQueue
	str	r8, [r5]
	mov	r0, r5
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r7, #3516]
	beq	.L1472
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
	movw	r0, #36196
	str	r6, [r7, #3392]
	movt	r0, 4
	str	r6, [r7, #3396]
	add	r0, r5, r0
	str	r6, [r7, #3420]
	str	r6, [r7, #3424]
	str	r6, [r7, #3460]
	str	r6, [r7, #3464]
	ldr	r3, [r8, #616]
	cmp	r3, #1
	strne	r6, [r7, #3380]
	strne	r6, [r4, #2568]
	ldreq	r3, [fp, #-48]
	streq	r3, [r7, #3380]
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
.L1465:
	str	ip, [r3, #4]!
	cmp	r3, r0
	str	ip, [r1, #4]!
	bne	.L1465
	movw	r3, #11012
	movw	r1, #11048
	movt	r3, 4
	movt	r1, 4
	add	r3, r5, r3
	add	r1, r5, r1
	mvn	r0, #0
.L1466:
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L1466
	movw	r1, #10968
	mov	r3, #0
	movt	r1, 4
	add	r1, r5, r1
	mov	r0, #1
.L1467:
	str	r3, [r1, #4]!
	add	r3, r3, #1
	cmp	r3, #8
	str	r0, [r2, #4]!
	bne	.L1467
	mov	r0, #0
.L1462:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1472:
	ldr	r1, .L1473+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1462
.L1474:
	.align	2
.L1473:
	.word	.LC3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
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
	ble	.L1487
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
	beq	.L1478
	sub	r9, r2, #4
.L1479:
	cmp	r7, #0
	beq	.L1482
	mov	r2, #0
	sub	r1, r4, #1
	add	lr, r4, r8
	mov	r0, r2
.L1480:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	cmp	r1, lr
	orr	r0, r0, ip, asl r2
	add	r2, r2, #8
	bne	.L1480
	add	r4, r4, r7
.L1481:
	add	r5, r5, #1
	str	r0, [r9, #4]!
	cmp	r6, r5
	bhi	.L1479
.L1478:
	str	r6, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1487:
	ldr	r1, .L1488
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1482:
	mov	r0, r7
	b	.L1481
.L1489:
	.align	2
.L1488:
	.word	.LC5
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
	add	r5, r0, #294912
	add	r6, r0, #270336
	mov	r4, r0
	ldr	r3, [r7, #1000]
	ldr	r0, [r5, #3516]
	cmp	r3, #1
	moveq	r1, #0
	movne	r1, #1
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #2612]
	blt	.L1509
	mov	r1, r0
	ldr	r0, [r5, #3516]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L1510
	ldr	r2, [r6, #2612]
	mov	r0, #18
	ldr	r1, .L1513
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L1496
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L1496
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L1513+4
	bl	dprint_vfmw
	ldr	r3, [r7, #1000]
	cmp	r3, #1
	beq	.L1511
	ldr	r2, [r4, #28]
	mov	r3, #0
	mov	r0, r3
	str	r3, [r2, #80]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1496:
	movw	r2, #2258
	ldr	r1, .L1513+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1509:
	ldr	r1, .L1513+12
	mov	r0, #0
	bl	dprint_vfmw
	movw	r1, #13688
	ldr	r0, [r5, #3516]
	movt	r1, 4
	add	r1, r4, r1
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1510:
	movw	r2, #2246
	ldr	r1, .L1513+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1511:
	ldr	r3, [r7, #1004]
	cmp	r3, #8
	bls	.L1499
	ldr	r2, .L1513+20
	mov	r0, #0
	ldr	r1, .L1513+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1499:
	add	r6, r6, r3, lsl #2
	ldr	r0, [r5, #3516]
	ldr	r1, [r6, #2824]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1512
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
.L1512:
	ldr	r3, .L1513+28
	movw	r2, #2275
	ldr	r1, .L1513+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1514:
	.align	2
.L1513:
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR0+604
	.word	.LC11
	.word	.LC12
	.word	.LC13
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
	add	r4, r0, #294912
	ldr	r1, [r5, #2612]
	cmp	r1, #0
	blt	.L1516
	mov	r2, #1
	ldr	r0, [r4, #3516]
	bl	FSP_ClearLogicFs
.L1516:
	ldr	r3, [r4, #3416]
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
	beq	.L1520
	add	r3, r6, #294912
	add	r5, r6, #270336
	ldr	r0, [r3, #3516]
	ldr	r1, [r5, #2612]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1520
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
	beq	.L1524
	add	r7, r4, #512
	ldr	r1, [r4, #36]
	ldrd	r2, [r7, #-8]
	strd	r2, [fp, #-68]
.L1525:
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
	mov	r9, r3, asl #5
	ldr	r2, [r5, #2492]
	bic	r0, r0, #63
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
.L1520:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1524:
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
	b	.L1525
	UNWIND(.fnend)
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
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
	add	r4, r0, #294912
	mov	r5, r1
	mov	r2, #0
	ldr	r0, [r4, #3516]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #3516]
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
	add	r0, r0, #1392
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
	add	r4, r0, #294912
	mov	r5, r0
	ldr	r0, [r4, #3516]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #3516]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L1537
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1537:
	movw	r1, #13688
	ldr	r0, [r4, #3516]
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
	beq	.L1539
.L1540:
	ldr	r1, .L1541
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1539:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	cmp	r0, #131
	bne	.L1540
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	cmp	r0, #66
	bne	.L1540
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1542:
	.align	2
.L1541:
	.word	.LC14
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
	beq	.L1545
	add	r3, r1, #80
	mov	r0, #1
.L1546:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1545
	add	r0, r0, #1
	cmp	r0, #9
	bne	.L1546
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1545:
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
	beq	.L1554
	mov	r0, r4
	sub	r2, fp, #24
	sub	r1, fp, #28
	bl	Read_Frame_Size
.L1554:
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, [r0, #2492]
	ldr	ip, [r0, #2496]
	ldr	r3, [r0, #2440]
	add	r1, lr, #7
	add	r2, ip, #7
	bic	r1, r1, #7
	bic	r2, r2, #7
	add	r3, r0, r3, lsl #4
	mov	r5, r1, asr #3
	mov	r4, r2, asr #3
	str	r5, [r0, #2532]
	str	r4, [r0, #2536]
	str	r1, [r3, #2676]
	str	r2, [r3, #2680]
	str	lr, [r3, #2684]
	str	ip, [r3, #2688]
	ldmfd	sp, {r4, r5, fp, sp, pc}
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r1, #2492]
	mov	r4, r1
	ldr	r3, [r1, #2496]
	add	r5, r1, #2432
	add	r1, r5, #60
	add	r2, r4, #2496
	str	ip, [r4, #2512]
	mov	r6, r0
	str	r3, [r4, #2516]
	add	r5, r5, #8
	bl	Read_Frame_Size
	ldr	r7, [r4, #2492]
	ldr	lr, [r4, #2496]
	mov	r1, r5
	ldr	r3, [r4, #2440]
	add	ip, r7, #7
	add	r2, lr, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r0, r6
	add	r3, r4, r3, lsl #4
	mov	r6, ip, asr #3
	mov	r5, r2, asr #3
	str	r6, [r4, #2532]
	str	r5, [r4, #2536]
	str	ip, [r3, #2676]
	str	r2, [r3, #2680]
	str	r7, [r3, #2684]
	str	lr, [r3, #2688]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r1, #2432
	mov	r4, r1
	add	r7, r7, #8
	mov	r6, r0
	mov	r5, #0
.L1564:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	bne	.L1569
	add	r5, r5, #1
	cmp	r5, #3
	bne	.L1564
	ldr	ip, [r4, #2492]
	add	r2, r4, #2496
	ldr	r3, [r4, #2496]
	add	r1, r7, #52
	mov	r0, r6
	str	ip, [r4, #2512]
	str	r3, [r4, #2516]
	bl	Read_Frame_Size
	ldr	r5, [r4, #2492]
	ldr	lr, [r4, #2496]
.L1563:
	ldr	r3, [r4, #2440]
	add	ip, r5, #7
	add	r2, lr, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r1, r7
	add	r3, r4, r3, lsl #4
	mov	r0, r6
	mov	r7, ip, asr #3
	mov	r6, r2, asr #3
	str	r7, [r4, #2532]
	str	r6, [r4, #2536]
	str	ip, [r3, #2676]
	str	r5, [r3, #2684]
	str	lr, [r3, #2688]
	str	r2, [r3, #2680]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	Setup_Display_Size
.L1569:
	add	r5, r5, #46
	ldr	r1, [r4, #2492]
	ldr	r2, [r4, #2496]
	ldr	r3, [r4, r5, asl #2]
	str	r1, [r4, #2512]
	str	r2, [r4, #2516]
	add	r3, r4, r3, lsl #4
	ldr	r5, [r3, #2684]
	str	r5, [r4, #2492]
	ldr	lr, [r3, #2688]
	str	lr, [r4, #2496]
	b	.L1563
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
	ldr	r5, .L1572
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
.L1573:
	.align	2
.L1572:
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
	ldr	r5, .L1575
	mov	r4, r0
	add	r0, r0, #2640
	mov	r2, #32
	mov	r1, #0
	add	r0, r0, #4
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r5, [r5, #48]
	mov	r3, #0
	mov	ip, #1
	mvn	lr, #0
	mov	r1, r3
	strb	r3, [r4, #2567]
	add	r0, r4, #64
	strb	r3, [r4, #339]
	mov	r2, #16
	strb	r3, [r4, #342]
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
.L1576:
	.align	2
.L1575:
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
.L1581:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1595
.L1580:
	add	r6, r6, #1
	cmp	r6, r7
	bne	.L1581
	add	r4, r4, #8
.L1583:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1596
.L1582:
	add	r7, r7, #1
	cmp	r7, r4
	bne	.L1583
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1595:
	ldr	r2, .L1597
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r6]
	b	.L1580
.L1596:
	ldr	r2, .L1597+4
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r7]
	b	.L1582
.L1598:
	.align	2
.L1597:
	.word	.LC15
	.word	.LC16
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
	beq	.L1600
	mov	r0, r6
	ldr	r2, .L1604
	mov	r1, #4
	bl	VP9_s_v
.L1600:
	str	r0, [r4]
	subs	r0, r0, r5
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1605:
	.align	2
.L1604:
	.word	.LC17
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
	bne	.L1607
	ldr	r2, [r4, #244]
	cmp	r2, #0
	bne	.L1607
	ldr	r2, [r4, #248]
	cmp	r2, #0
	ldreq	r3, [r4, #252]
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
.L1607:
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
	ldr	r3, .L1612
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #624]
	ldmfd	sp, {fp, sp, pc}
.L1613:
	.align	2
.L1612:
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
	bls	.L1618
	subs	r3, r0, #1
	beq	.L1619
	mov	r0, #0
.L1617:
	movs	r3, r3, lsr #1
	add	r0, r0, #1
	bne	.L1617
	ldmfd	sp, {fp, sp, pc}
.L1618:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1619:
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
	bls	.L1622
	subs	r3, r4, #1
	beq	.L1626
	mov	r2, #0
.L1624:
	movs	r3, r3, lsr #1
	add	r2, r2, #1
	bne	.L1624
.L1623:
	mov	r1, r2
.L1622:
	bl	BsGet
	cmp	r0, r4
	movge	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1626:
	mov	r2, r3
	b	.L1623
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
	ldr	r3, .L1629
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #640]
	ldmfd	sp, {fp, sp, pc}
.L1630:
	.align	2
.L1629:
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
	ldr	r7, .L1640
	mov	r9, r2, asl #2
	mov	r5, r3
	mov	r4, r2
	add	r3, r7, r9
	mov	r6, r0
	mov	r10, r1
	ldr	r8, [r3, #624]
	cmp	r8, r5
	blt	.L1637
.L1632:
	cmp	r5, #0
	blt	.L1638
.L1634:
	add	r4, r4, r10, lsl #2
	add	r4, r6, r4, lsl #1
	strh	r5, [r4, #16]	@ movhi
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1638:
	add	r7, r7, r9
	ldr	r0, [r7, #640]
	cmp	r0, #0
	beq	.L1639
.L1635:
	rsb	r3, r5, #0
	cmp	r8, r3
	bge	.L1634
	movw	r3, #2994
	ldr	r2, .L1640+4
	ldr	r1, .L1640+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1634
.L1637:
	movw	r3, #2982
	add	r2, r7, #656
	ldr	r1, .L1640+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1632
.L1639:
	movw	r3, #2989
	ldr	r2, .L1640+4
	ldr	r1, .L1640+8
	bl	dprint_vfmw
	b	.L1635
.L1641:
	.align	2
.L1640:
	.word	.LANCHOR0
	.word	.LANCHOR0+656
	.word	.LC18
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
	ble	.L1645
.L1646:
	add	r3, r3, #1
	mov	ip, r0, asr r3
	cmp	ip, #3
	bgt	.L1646
	sub	r3, r3, #1
	bic	r3, r3, r3, asr #31
.L1645:
	cmp	r0, #64
	mov	ip, #0
	ble	.L1647
	mov	lr, #64
.L1648:
	add	ip, ip, #1
	cmp	r0, lr, asl ip
	bgt	.L1648
.L1647:
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
	ble	.L1654
	mov	r4, #0
	b	.L1655
.L1666:
	mov	r4, r3
.L1655:
	add	r3, r4, #1
	mov	r1, r2, asr r3
	cmp	r1, #3
	bgt	.L1666
	cmp	r2, #64
	bic	r4, r4, r4, asr #31
	ble	.L1677
.L1664:
	mov	r3, #0
	mov	r1, #64
.L1657:
	add	r3, r3, #1
	cmp	r2, r1, asl r3
	bgt	.L1657
.L1656:
	subs	r4, r4, r3
	str	r3, [r6, #100]
	bne	.L1660
	b	.L1659
.L1662:
	ldr	r3, [r6, #100]
	subs	r4, r4, #1
	add	r3, r3, #1
	str	r3, [r6, #100]
	beq	.L1659
.L1660:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1662
.L1659:
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
.L1654:
	cmp	r2, #64
	movgt	r4, #0
	bgt	.L1664
	mov	r3, #0
	str	r3, [r6, #100]
	b	.L1659
.L1677:
	mov	r3, #0
	b	.L1656
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
	bne	.L1715
.L1679:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1715:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L1682
	add	r4, r5, #4
	add	r7, r5, #11
	b	.L1684
.L1683:
	strb	r3, [r4, #1]!
	cmp	r4, r7
	beq	.L1716
.L1684:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	beq	.L1683
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #1]!
	cmp	r4, r7
	bne	.L1684
.L1716:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #4]
	cmp	r0, #0
	addne	r4, r5, #14
	bne	.L1687
	mvn	r3, #0
	strb	r3, [r5, #12]
	strb	r3, [r5, #13]
	strb	r3, [r5, #14]
.L1682:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #2]
	cmp	r0, #0
	beq	.L1679
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	add	r8, r5, #80
	mov	r7, #0
	ldr	r10, .L1719
	strb	r0, [r5, #3]
	mov	r0, r5
	bl	VP9_Clearall_Segfeatures
.L1689:
	mov	r4, #0
	mov	r9, #1
.L1692:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1717
.L1691:
	mov	r2, r4
	mov	r1, r7
	add	r4, r4, #1
	mov	r0, r5
	bl	VP9_Set_Segdata
	cmp	r4, #4
	bne	.L1692
	add	r7, r7, #1
	add	r8, r8, #4
	cmp	r7, #8
	bne	.L1689
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1717:
	ldr	r3, [r8]
	mov	r0, r6
	ldr	r1, [r10, r4, asl #2]
	orr	r3, r3, r9, asl r4
	str	r3, [r8]
	bl	Decode_Unsigned_Max
	ldr	r2, .L1719+4
	ldr	r2, [r2, r4, asl #2]
	cmp	r2, #0
	mov	r3, r0
	beq	.L1691
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
	b	.L1691
.L1687:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	bne	.L1718
.L1686:
	strb	r3, [r7, #1]!
	cmp	r7, r4
	bne	.L1687
	b	.L1682
.L1718:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	b	.L1686
.L1720:
	.align	2
.L1719:
	.word	.LANCHOR0+624
	.word	.LANCHOR0+640
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
	ldr	r3, .L1725
	mov	r4, r0
	sub	ip, fp, #20
	ldmia	r3, {r0, r1, r2, r3}
	stmdb	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r0, #4
	beq	.L1724
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1724:
	mov	r0, r4
	mov	r1, #2
	bl	BsGet
	sub	r3, fp, #20
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #-16]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1726:
	.align	2
.L1725:
	.word	.LANCHOR0+672
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
	beq	.L1733
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
.L1732:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1733:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3187
	ldr	r2, .L1734
	ldr	r1, .L1734+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1732
.L1735:
	.align	2
.L1734:
	.word	.LANCHOR0+688
	.word	.LC19
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
	bgt	.L1740
	cmp	r1, r3, asl #1
	bgt	.L1740
	cmp	r2, r0, asl #4
	bgt	.L1740
	cmp	r3, r1, asl #4
	movle	r0, #1
	movgt	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1740:
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
	bgt	.L1743
	cmp	r2, r6, asl #1
	ble	.L1753
.L1743:
	mvn	r2, #0
	mov	r3, #16
	str	r2, [r4]
	stmib	r4, {r2, r3}
	str	r3, [r4, #12]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1753:
	cmp	r3, r1, asl #4
	bgt	.L1743
	cmp	r6, r2, asl #4
	bgt	.L1743
	cmp	r3, #0
	beq	.L1754
	mov	r1, r3
	mov	r0, ip, asl #14
	bl	__aeabi_idiv
	cmp	r6, #0
	mov	r5, r0
	str	r5, [r4]
	beq	.L1755
.L1746:
	mov	r1, r6
	mov	r0, r7, asl #14
	bl	__aeabi_idiv
	mov	r7, r0, asr #31
	ubfx	r3, r0, #10, #18
	mov	r1, r7, asl #4
	orr	r1, r1, r0, lsr #28
	orr	r1, r3, r1, asl #18
.L1747:
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
.L1754:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3187
	ldr	r2, .L1756
	ldr	r1, .L1756+4
	mvn	r5, #0
	bl	dprint_vfmw
	cmp	r6, #0
	str	r5, [r4]
	bne	.L1746
.L1755:
	ldr	r1, .L1756+4
	movw	r3, #3187
	str	r6, [sp]
	mov	r0, #1
	ldr	r2, .L1756
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r1
	ldr	r5, [r4]
	b	.L1747
.L1757:
	.align	2
.L1756:
	.word	.LANCHOR0+688
	.word	.LC19
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
	ble	.L1759
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	add	r4, r0, r4
.L1759:
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
	ldr	r3, [r1, #2452]
	mov	r2, #8
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	str	r2, [r1, #2508]
	bls	.L1761
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r3, #12
	moveq	r3, #10
	str	r3, [r4, #2508]
.L1761:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	cmp	r0, #7
	str	r0, [r4, #2456]
	beq	.L1763
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #2452]
	bic	r6, r6, #2
	cmp	r6, #1
	movne	r3, #1
	str	r0, [r4, #2460]
	strne	r3, [r4, #2488]
	strne	r3, [r4, #2484]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #2484]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #2488]
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1763:
	ldr	r1, [r4, #2452]
	bic	r1, r1, #2
	cmp	r1, #1
	beq	.L1769
	movw	r3, #3290
	ldr	r2, .L1770
	ldr	r1, .L1770+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1769:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #2488]
	str	r3, [r4, #2484]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1771:
	.align	2
.L1770:
	.word	.LANCHOR0+724
	.word	.LC20
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
	beq	.L1777
.L1773:
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
.L1777:
	bl	Vp9_ReadTxMode
	cmp	r0, #4
	mov	r4, r0
	bne	.L1773
	add	r0, r7, #2000
	mov	r1, r5
	add	r0, r0, #3
	bl	Vp9_ReadTxProbs
	b	.L1773
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r4, r1
	ldr	r3, [r4, #2448]
	mov	r1, #2
	mov	r5, r0
	str	r3, [r4, #2444]
	bl	BsGet
	cmp	r0, #2
	beq	.L1779
	ldr	r1, .L1813
	mov	r0, #1
	bl	dprint_vfmw
.L1779:
	mov	r0, r5
	bl	Vp9_Vfmw_ReadProfile
	mov	r1, #1
	str	r0, [r4, #2452]
	mov	r0, r5
	bl	BsGet
	subs	r6, r0, #0
	bne	.L1809
	mov	r1, #1
	str	r6, [r4, #2468]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2448]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2464]
	mov	r0, r5
	bl	BsGet
	ldr	r2, [r4, #2448]
	cmp	r2, #0
	mov	r3, r0
	str	r0, [r4, #2480]
	beq	.L1810
	ldr	r2, [r4, #2464]
	cmp	r2, #0
	strne	r6, [r4, #2548]
	beq	.L1811
.L1785:
	cmp	r3, #0
	beq	.L1786
	mov	r3, #0
	str	r3, [r4, #2552]
.L1787:
	ldr	r3, [r4, #2548]
	cmp	r3, #0
	beq	.L1788
	mov	r0, r5
	bl	Check_Sync_Code
	ldr	r3, [r4, #2452]
	cmp	r3, #1
	bls	.L1789
	mov	r1, r4
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1790:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r4
	str	r0, [r4, #2556]
	mov	r0, r5
	bl	Setup_Frame_Size
	b	.L1783
.L1809:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r6, r3
	mov	r2, #1
	add	r0, r0, #38
	ldr	r1, [r4, r0, asl #2]
	str	r3, [r4, #2556]
	str	r3, [r4, #344]
	str	r1, [r4, #2472]
	str	r2, [r4, #2468]
	str	r2, [r4, #2464]
.L1781:
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1788:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r7, r4, #180
	add	r8, r4, #192
	mov	r9, r7
	str	r0, [r4, #2556]
.L1791:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	add	r3, r0, #38
	mov	r0, r5
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r9, #4]!
	bl	BsGet
	cmp	r9, r8
	str	r0, [r9, #-116]
	bne	.L1791
	mov	r1, r4
	mov	r0, r5
	bl	setup_frame_size_with_refs
	ldr	r2, [r4, #2492]
	sub	r3, r2, #1
	cmp	r3, #4096
	ldr	r3, [r4, #2496]
	bcs	.L1793
	sub	r1, r3, #1
	cmp	r1, #4096
	bcs	.L1793
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	add	r9, r4, #2816
	add	r9, r9, #4
	str	r0, [r4, #56]
	mov	r0, r5
	bl	read_interp_filter_type
	str	r0, [r4, #2560]
.L1795:
	ldr	r1, [r7, #4]!
	mov	r0, r9
	ldr	ip, [r4, #2496]
	add	r9, r9, #16
	ldr	r3, [r4, #2492]
	add	r1, r4, r1, lsl #4
	add	r1, r1, #2672
	ldr	r2, [r1, #16]
	add	r1, r1, #4
	ldr	r1, [r1, #8]
	str	ip, [sp]
	bl	vp9_setup_scale_factors
	cmp	r8, r7
	bne	.L1795
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #76]
	ldr	r2, [r4, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #60]
	b	.L1783
.L1810:
	mov	r0, r5
	bl	Check_Sync_Code
	mov	r1, r4
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
	ldr	r3, [r4, #2440]
	mov	r2, #255
	mov	r1, r4
	str	r2, [r4, #2556]
	mov	r0, r5
	str	r3, [r4, #184]
	str	r3, [r4, #188]
	str	r3, [r4, #192]
	bl	Setup_Frame_Size
.L1783:
	ldr	r3, [r4, #2480]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #2520]
	strne	r3, [r4, #2524]
	beq	.L1812
.L1797:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #2448]
	cmp	r3, #0
	str	r0, [r4, #2528]
	beq	.L1798
	ldr	r3, [r4, #2480]
	cmp	r3, #0
	bne	.L1798
	ldr	r3, [r4, #2548]
	cmp	r3, #0
	bne	.L1798
.L1800:
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #76]
	ldr	r2, [r4, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #60]
.L1799:
	add	r1, r4, #336
	mov	r0, r5
	bl	Setup_LoopFilter
	mov	r1, r4
	mov	r0, r5
	bl	Setup_Quantization
	add	r1, r4, #2560
	mov	r0, r5
	add	r1, r1, #4
	bl	Setup_Segmentation
	add	r1, r4, #2432
	mov	r0, r5
	add	r1, r1, #8
	bl	Setup_Tile_Info
	mov	r0, r5
	mov	r1, #16
	bl	BsGet
	str	r0, [r4, #8]
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1789:
	mov	r3, #1
	mov	r2, #8
	str	r3, [r4, #2484]
	str	r2, [r4, #2508]
	str	r3, [r4, #2488]
	str	r3, [r4, #2456]
	b	.L1790
.L1798:
	mov	r0, r4
	bl	VP9_Setup_Past_Independence
	ldr	r3, [r4, #2448]
	cmp	r3, #0
	beq	.L1799
	b	.L1800
.L1812:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2520]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #2524]
	b	.L1797
.L1786:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #2552]
	b	.L1787
.L1811:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #2480]
	str	r0, [r4, #2548]
	b	.L1785
.L1793:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #3443
	ldr	r2, .L1813+4
	mvn	r6, #0
	ldr	r1, .L1813+8
	bl	dprint_vfmw
	b	.L1781
.L1814:
	.align	2
.L1813:
	.word	.LC21
	.word	.LANCHOR0+760
	.word	.LC22
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
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #2556]
	cmp	r3, #0
	addne	r2, r0, #152
	addne	lr, r0, #80
	beq	.L1820
.L1819:
	tst	r3, #1
	beq	.L1817
	ldr	r4, [r2]
	ldr	ip, [r0, #2440]
	ldr	r1, [lr, r4, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [lr, r4, asl #2]
	str	ip, [r2]
	ldr	r1, [lr, ip, asl #2]
	add	r1, r1, #1
	str	r1, [lr, ip, asl #2]
.L1817:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1819
.L1820:
	ldr	r3, [r0, #2440]
	mvn	r2, #-2147483648
	add	r3, r0, r3, lsl #2
	ldr	r1, [r3, #80]
	sub	r1, r1, #1
	str	r1, [r3, #80]
	str	r2, [r0, #184]
	str	r2, [r0, #188]
	str	r2, [r0, #192]
	ldmfd	sp, {r4, fp, sp, pc}
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
	ldr	r6, [r7, #1000]
	cmp	r6, #1
	beq	.L1861
	add	r8, r0, #262144
	mov	r3, #0
	strb	r3, [r8, #1036]
	ldr	r2, [r7, #980]
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
	addgt	r6, r5, #294912
	addle	r1, r4, r1, lsl #2
	addle	r6, r5, #294912
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
	ldrgt	r3, [r6, #3416]
	ldrle	r3, [r1, #2824]
	addgt	r3, r4, r3, lsl #2
	ldrgt	r3, [r3, #2824]
	str	r3, [r4, #2604]
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	ldrgt	r3, [r6, #3416]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2600]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	ldrgt	r3, [r6, #3416]
	cmp	r2, #0
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2608]
	bne	.L1862
.L1839:
	ldr	r1, [r4, #2612]
	str	r1, [r4, #2604]
	str	r1, [r4, #2600]
	str	r1, [r4, #2608]
.L1840:
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2604]
	mov	r7, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2600]
	mov	r10, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2608]
	mov	r9, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	cmp	r9, #0
	cmpne	r7, #0
	beq	.L1841
	cmp	r0, #0
	cmpne	r10, #0
	beq	.L1841
	ldr	r2, [r7, #28]
	cmp	r2, #0
	beq	.L1863
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
	ldr	r3, [r6, #3524]
	str	r3, [r6, #3520]
	str	r3, [r8, #1032]
	str	r2, [r5, #4]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1862:
	ldr	r3, [r7, #1080]
	cmp	r3, #1
	beq	.L1839
	ldr	r1, [r4, #2612]
	b	.L1840
.L1861:
	add	r3, r0, #262144
	add	r8, r0, #294912
	strb	r6, [r3, #1036]
	ldr	r3, [r0]
	ldr	r1, [r4, #2612]
	ldr	r2, [r3, #592]
	str	r2, [r4, #2476]
	ldr	r3, [r3, #644]
	str	r3, [r4, #2496]
	ldr	r0, [r8, #3516]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #1004]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r9, r0
	ldr	r0, [r8, #3516]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #1004]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r10, r0
	ldr	r0, [r8, #3516]
	bl	FSP_GetFsImagePtr
	cmp	r9, #0
	cmpne	r10, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r2, r0
	cmp	r3, #0
	bne	.L1841
	ldr	r3, [r9, #28]
	cmp	r3, #0
	beq	.L1864
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
.L1841:
	ldr	r1, .L1865
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1863:
	ldr	r1, .L1865+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1864:
	mov	r0, r6
	ldr	r1, .L1865+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1866:
	.align	2
.L1865:
	.word	.LC23
	.word	.LC25
	.word	.LC24
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
	bls	.L1869
	sub	r0, r2, #32
	movw	r1, #8160
	cmp	r3, #8192
	cmpls	r0, r1
	bls	.L1870
.L1869:
	ldr	r1, .L1896
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1871:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1870:
	ldr	r1, .L1896+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r5]
	ldr	r3, [r1, #724]
	cmp	r3, #0
	bne	.L1872
	ldr	r2, [r1, #28]
	cmp	r2, #25
	beq	.L1893
.L1885:
	mov	r7, #5
.L1873:
	ldr	r3, [r4, #2568]
	add	r6, r5, #294912
	cmp	r3, #0
	bne	.L1878
	ldr	lr, [r6, #3516]
	mov	r1, r3
	ldr	ip, .L1896+8
	mov	r2, #20
	ldr	r8, .L1896+12
	sub	r0, fp, #56
	ldr	ip, [ip, lr, asl #2]
	ldr	r8, [r8, #48]
	add	ip, ip, #290816
	str	r3, [ip, #768]
	blx	r8
	ldr	ip, [r4, #2648]
	ldr	r2, [r4, #2652]
	sub	r1, fp, #56
	ldr	r0, [r6, #3516]
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
	beq	.L1894
.L1879:
	ldr	r1, .L1896+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1871
.L1872:
	ldr	r3, [r1, #28]
	cmp	r3, #25
	bne	.L1885
	ldr	r2, [r4, #2648]
	ldr	ip, [r1, #684]
	cmp	r2, ip
	bhi	.L1876
	ldr	r0, [r4, #2652]
	ldr	r3, [r1, #688]
	cmp	r0, r3
	bls	.L1877
.L1876:
	ldr	lr, [r1, #688]
	mov	r0, #0
	ldr	r3, [r4, #2652]
	ldr	r1, .L1896+20
	str	ip, [sp]
	str	lr, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1871
.L1878:
	ldr	r3, [r6, #3516]
	mov	r7, #1
	ldr	r8, .L1896+8
	mov	r1, #0
	ldr	r2, .L1896+12
	sub	r0, fp, #56
	ldr	r9, [r6, #3388]
	ldr	r3, [r8, r3, asl #2]
	ldr	ip, [r2, #48]
	mov	r2, #20
	add	r3, r3, #290816
	str	r7, [r3, #768]
	blx	ip
	ldr	r1, [r5]
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #3516]
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
	bne	.L1879
	ldr	r1, [r5]
	sub	r3, fp, #60
	ldr	r0, [r6, #3516]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	bne	.L1895
.L1882:
	ldr	r3, [r6, #3516]
	mov	r2, #0
	ldr	r3, [r8, r3, asl #2]
	str	r2, [r3, #1432]
.L1880:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #2568]
	b	.L1871
.L1893:
	ldr	r2, [r4, #2648]
	ldr	ip, [r1, #684]
	cmp	r2, ip
	bhi	.L1876
	ldr	lr, [r4, #2652]
	ldr	r0, [r1, #688]
	cmp	lr, r0
	bhi	.L1876
	ldr	r2, [r4, #2568]
	cmp	r2, #1
	moveq	r0, r3
	beq	.L1871
.L1877:
	ldr	r7, [r1, #732]
	b	.L1873
.L1894:
	ldr	r1, [r5]
	sub	r3, fp, #60
	ldr	r0, [r6, #3516]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	beq	.L1880
	mov	r0, r7
	ldr	r1, .L1896+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1871
.L1895:
	ldr	r1, .L1896+28
	mov	r0, #2
	bl	dprint_vfmw
	b	.L1882
.L1897:
	.align	2
.L1896:
	.word	.LC26
	.word	.LC27
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC28
	.word	.LC29
	.word	.LC31
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
	ldr	r8, .L1917
	movw	r6, #10820
	sub	r4, fp, #72
	add	r7, r0, #274432
	movt	r6, 4
	add	r6, r0, r6
	ldr	r3, [r8, #52]
	add	r1, r6, #80
	mov	r2, #36
	mov	r0, r4
	ldr	r5, [r7, #972]
	blx	r3
	ldr	r3, [r8, #52]
	add	r1, r6, #152
	sub	r0, fp, #104
	mov	r2, #32
	blx	r3
	ldr	r3, [r7, #1000]
	cmp	r3, #1
	beq	.L1916
.L1899:
	ldr	r3, [r7, #1088]
	mov	lr, r5, asl #2
	cmp	r3, #0
	subne	r2, fp, #104
	addne	r0, r4, lr
	beq	.L1906
.L1905:
	tst	r3, #1
	beq	.L1903
	ldr	ip, [r2]
	str	r5, [r2]
	ldr	r1, [r4, ip, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [r4, ip, asl #2]
	ldr	r1, [r0]
	add	r1, r1, #1
	str	r1, [r0]
.L1903:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1905
.L1906:
	sub	r3, fp, #36
	sub	r1, fp, #40
	add	r2, r3, lr
	sub	r3, fp, #76
	mov	r0, #0
	ldr	ip, [r2, #-36]
	sub	ip, ip, #1
	str	ip, [r2, #-36]
.L1902:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	addne	r0, r0, #1
	cmp	r3, r1
	bne	.L1902
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1916:
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [r7, #1004]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r4, r5, asl #2]
	ldr	r3, [r4, r2, asl #2]
	mov	r5, r2
	add	r3, r3, #1
	str	r3, [r4, r2, asl #2]
	b	.L1899
.L1918:
	.align	2
.L1917:
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
	ldr	r5, .L1920
	mov	r2, #432
	ldr	r4, .L1920+4
	mov	r6, r0
	ldr	r3, [r5, #52]
	mov	r1, r4
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #432
	add	r0, r6, #432
	mov	r2, #432
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #864
	add	r0, r6, #864
	mov	r2, #432
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #1296
	add	r0, r6, #1296
	mov	r2, #432
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1921:
	.align	2
.L1920:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1923
	mov	r4, r0
	ldr	r6, .L1923+4
	add	r0, r0, #1760
	mov	r2, #90
	add	r0, r0, #4
	ldr	r3, [r5, #52]
	add	r1, r6, #1728
	blx	r3
	add	r1, r6, #1808
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	add	r0, r4, #1728
	mov	r2, #36
	blx	r3
	add	r0, r4, #1936
	ldr	r3, [r5, #52]
	add	r1, r6, #1856
	mov	r2, #8
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1856
	add	r0, r4, #1840
	ldr	r3, [r5, #52]
	add	r1, r1, #8
	mov	r2, #96
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1952
	add	r0, r4, #1968
	ldr	r3, [r5, #52]
	add	r1, r1, #8
	mov	r2, #4
	add	r0, r0, #11
	blx	r3
	add	r1, r6, #1952
	add	r0, r4, #1968
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	mov	r2, #5
	add	r0, r0, #15
	blx	r3
	add	r1, r6, #1968
	add	r0, r4, #1984
	ldr	r3, [r5, #52]
	add	r1, r1, #4
	mov	r2, #5
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1968
	add	r0, r4, #1984
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	mov	r2, #10
	add	r0, r0, #4
	blx	r3
	add	r0, r4, #2000
	mov	r2, #12
	ldr	r1, .L1923+8
	add	r0, r0, #3
	bl	memcpy
	add	r1, r6, #1984
	add	r0, r4, #2000
	add	r1, r1, #8
	add	r0, r0, #15
	ldr	r3, [r5, #52]
	mov	r2, #3
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1924:
	.align	2
.L1923:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR0+788
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
	add	r0, r0, #2016
	mov	r2, #69
	ldr	r1, .L1926
	add	r0, r0, #2
	bl	memcpy
	ldmfd	sp, {fp, sp, pc}
.L1927:
	.align	2
.L1926:
	.word	.LANCHOR0+800
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
	add	r0, r5, #2016
	mov	r2, #69
	ldr	r1, .L1936
	add	r0, r0, #2
	bl	memcpy
	ldr	r3, .L1936+4
	add	r0, r5, #1952
	mov	r2, #21
	add	r0, r0, #6
	ldr	r1, .L1936+8
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
	bne	.L1934
	cmp	r4, #2
	beq	.L1935
.L1931:
	mov	r3, #0
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1934:
	mov	r4, #0
	movw	r8, #8348
.L1930:
	add	r0, r6, r4
	add	r4, r4, #2080
	add	r4, r4, #7
	movw	r2, #2087
	mov	r1, r5
	bl	memcpy
	cmp	r4, r8
	bne	.L1930
	b	.L1931
.L1935:
	ldr	r0, [r7]
	movw	r2, #2087
	mov	r1, r5
	mla	r0, r2, r0, r6
	bl	memcpy
	b	.L1931
.L1937:
	.align	2
.L1936:
	.word	.LANCHOR0+800
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1996
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
	beq	.L1940
	add	r1, r1, #20
	mov	ip, #1
	ldr	r3, [r0, r1, asl #2]
	ands	r3, r3, ip, asl r2
	movne	r0, ip
	moveq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1940:
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
.L1949:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1952
	ldr	r3, [r7]
	tst	r3, #2
	beq	.L1952
	ldrb	r3, [r9, #3]	@ zero_extendqisi2
	ldrsh	r1, [r8, #18]
	cmp	r3, #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	addne	r1, r1, r10
	cmp	r3, #0
	usat	r1, #6, r1
	beq	.L1957
.L1946:
	mov	r0, r5
	add	lr, r5, #5
	ldrsb	r3, [r0, #2]!
	mov	ip, r6
	add	r3, r1, r3, asl r4
	usat	r3, #6, r3
	strb	r3, [r6]
.L1948:
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
	bne	.L1948
.L1947:
	ldr	r3, [fp, #-48]
	add	r7, r7, #4
	add	r6, r6, #8
	add	r8, r8, #8
	cmp	r7, r3
	bne	.L1949
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1952:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	cmp	r3, #0
	bne	.L1946
.L1957:
	ldr	r3, .L1958
	mov	r2, #8
	mov	r0, r6
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1947
.L1959:
	.align	2
.L1958:
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
	add	r8, r6, #294912
	bl	GetCompressRatio
	str	r0, [fp, #-48]
	ldr	r0, [r4, #2492]
	bl	GetCompressRatio
	ldr	r0, [r4, #2860]
	add	r2, r6, #274432
	ldr	r3, [r4, #2864]
	and	r0, r0, #7
	ldr	r1, [r2, #980]
	and	r3, r3, #3
	ldr	ip, [r2, #976]
	mov	r0, r0, asl #10
	ldr	r9, [r2, #1040]
	orr	r3, r0, r3, asl #13
	and	ip, ip, #3
	ldr	lr, [r2, #1056]
	ldr	r0, [r2, #1080]
	and	r1, r1, #1
	orr	r1, r3, r1
	ldr	r7, [r2, #1052]
	and	r9, r9, #15
	orr	r3, r1, ip, asl #1
	and	lr, lr, #1
	ldr	r1, [r2, #1020]
	orr	r3, r3, r9, asl #15
	and	r7, r7, #1
	mov	r0, r0, asl #7
	orr	ip, r3, lr, asl #9
	ldr	lr, [r2, #1016]
	orr	ip, ip, r7, asl #8
	ldr	r3, [r2, #1012]
	uxtb	r0, r0
	and	r1, r1, #1
	orr	r0, ip, r0
	and	lr, lr, #1
	ldr	ip, [r2, #1008]
	orr	r1, r0, r1, asl #6
	and	r3, r3, #1
	orr	r1, r1, lr, asl #5
	and	r0, ip, #1
	orr	r3, r1, r3, asl #4
	orr	r3, r3, r0, asl #3
	str	r3, [r5]
	ldr	r1, [r2, #1024]
	ldr	r3, [r8, #3408]
	cmp	r1, r3
	movne	ip, #1048576
	beq	.L2002
.L1966:
	ldr	r3, [r4, #2816]
	mov	r9, #0
	ldr	r10, [r4, #2820]
	ldr	r1, [r4, #2704]
	mov	r3, r3, asl #12
	ldr	r0, [r2, #1092]
	ldr	lr, [r4, #2812]
	and	r10, r10, #15
	uxth	r3, r3
	mov	r1, r1, asl #7
	orr	r7, r3, r10, asl #16
	and	lr, lr, #15
	ldr	r3, [r4, #2700]
	and	r10, r0, #7
	orr	r0, r7, r10
	ldr	r10, [r4, #2696]
	ldr	r7, [r4, #2692]
	orr	lr, r0, lr, asl #8
	and	r3, r3, #1
	uxtb	r0, r1
	orr	r0, lr, r0
	and	r10, r10, #1
	ldr	lr, [r4, #2684]
	orr	r0, r0, r3, asl #6
	and	r7, r7, #1
	orr	r1, r0, r10, asl #5
	and	r3, lr, #1
	orr	r1, r1, r7, asl #4
	orr	r3, r1, r3, asl #3
	orr	r3, r3, ip
	str	r3, [r5, #4]
	ldr	r1, [r2, #1028]
	ldr	r3, [r2, #1024]
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
.L1967:
	add	ip, r5, r9, lsl #3
	mov	r7, r9, asl #2
	add	ip, ip, #12
	mov	lr, #0
.L1968:
	mov	r1, lr, asl #1
	add	lr, lr, #1
	add	r0, r1, #1
	add	r1, r7, r1
	add	r0, r7, r0
	cmp	lr, #2
	add	r10, r4, r1, lsl #1
	add	r3, r4, r0, lsl #1
	mov	r1, r10
	ldrb	r10, [r10, #2884]	@ zero_extendqisi2
	mov	r0, r3
	ldrb	r3, [r3, #2884]	@ zero_extendqisi2
	ldrb	r0, [r0, #2885]	@ zero_extendqisi2
	and	r10, r10, #63
	and	r3, r3, #63
	ldrb	r1, [r1, #2885]	@ zero_extendqisi2
	and	r0, r0, #63
	mov	r3, r3, asl #16
	and	r1, r1, #63
	orr	r3, r3, r0, asl #24
	orr	r10, r3, r10
	orr	r3, r10, r1, asl #8
	str	r3, [ip, #4]!
	bne	.L1968
	add	r9, r9, #1
	cmp	r9, #8
	bne	.L1967
	ldr	r3, [r4, #2880]
	movw	r1, #13460
	ldr	ip, [r4, #2876]
	movt	r1, 4
	cmp	r3, #0
	ldrb	r7, [r4, #2868]	@ zero_extendqisi2
	eor	lr, r3, r3, asr #31
	add	r1, r6, r1
	movlt	r10, #268435456
	movge	r10, #0
	cmp	ip, #0
	sub	lr, lr, r3, asr #31
	mov	r3, #0
	and	lr, lr, #15
	movlt	r0, #1048576
	movge	r0, r3
	str	r0, [fp, #-52]
	eor	r0, ip, ip, asr #31
	sub	r0, r0, ip, asr #31
	ldr	ip, [r4, #2872]
	and	r0, r0, #15
	cmp	ip, r3
	mov	r0, r0, asl #16
	movlt	r9, #4096
	movge	r9, r3
	cmp	ip, #0
	orr	r0, r0, lr, asl #24
	rsblt	ip, ip, #0
	orr	r0, r0, r7
	and	ip, ip, #15
	mov	lr, r3
	orr	r0, r0, ip, asl #8
	orr	r10, r0, r10
	ldr	r0, [fp, #-52]
	orr	r10, r10, r0
	orr	r9, r10, r9
	str	r9, [r5, #80]
	ldrb	r9, [r2, #1099]	@ zero_extendqisi2
	ldrb	r0, [r2, #1100]	@ zero_extendqisi2
	and	r9, r9, #1
	ldrb	ip, [r2, #1096]	@ zero_extendqisi2
	ldrb	r7, [r2, #1097]	@ zero_extendqisi2
	and	r10, r0, #1
	mov	r9, r9, asl #2
	and	ip, ip, #1
	orr	r0, r9, r10, asl #3
	and	r7, r7, #1
	orr	r0, r0, ip
	orr	r0, r0, r7, asl #1
	str	r0, [r5, #84]
.L1973:
	ldr	r0, [r1, #4]!
	and	r0, r0, #15
	orr	lr, lr, r0, asl r3
	add	r3, r3, #4
	cmp	r3, #32
	bne	.L1973
	add	r0, r4, #2624
	movw	ip, #2588
	add	r0, r0, #4
	str	lr, [r5, #88]
	movw	r3, #2596
	movw	r1, #2580
	ldrh	r9, [r0, ip]
	movw	lr, #2612
	ldrh	ip, [r0, r3]
	add	r3, r4, #5248
	ubfx	r9, r9, #0, #9
	ldrh	r7, [r0, r1]
	ubfx	r10, ip, #0, #9
	movw	r1, #2604
	mov	r9, r9, asl #9
	ubfx	r7, r7, #0, #9
	orr	ip, r9, r10, asl #18
	movw	r10, #2636
	orr	ip, ip, r7
	str	ip, [r5, #92]
	ldrh	ip, [r0, lr]
	movw	r9, #2628
	ldrh	r7, [r3]
	mov	r3, #0
	ubfx	ip, ip, #0, #9
	ldrh	lr, [r0, r1]
	ubfx	r7, r7, #0, #9
	mov	r1, r3
	mov	ip, ip, asl #9
	ubfx	lr, lr, #0, #9
	orr	ip, ip, r7, asl #18
	orr	lr, ip, lr
	str	lr, [r5, #96]
	ldrh	ip, [r0, r10]
	ldrh	r0, [r0, r9]
	ubfx	ip, ip, #0, #9
	ubfx	r0, r0, #0, #9
	orr	r0, r0, ip, asl #9
	str	r0, [r5, #100]
.L1974:
	movw	r0, #13402
	movt	r0, 4
	add	r0, r3, r0
	ldrb	r0, [r6, r0]	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L1974
	mov	r3, #0
	str	r1, [r5, #104]
	mov	r0, r3
.L1975:
	movw	r1, #13434
	movt	r1, 4
	add	r1, r3, r1
	ldrb	r1, [r6, r1]	@ zero_extendqisi2
	orr	r0, r0, r1, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L1975
	movw	r9, #13404
	mov	r7, #0
	movt	r9, 4
	add	r9, r6, r9
	mov	r6, r7
	str	r0, [r5, #108]
.L1976:
	ldrh	r0, [r9, #2]
	mov	r3, r7, asl #1
	ldrh	r1, [r9], #8
	add	ip, r7, #16
	and	r0, r0, #1
	add	r7, r7, #1
	and	r1, r1, #3
	cmp	r7, #8
	mov	r1, r1, asl r3
	orr	r3, r1, r0, asl ip
	orr	r6, r6, r3
	bne	.L1976
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
	ldr	r3, [r2, #1356]
	ldr	r1, [r2, #1352]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #180]
	ldr	r3, [r2, #1372]
	ldr	r1, [r2, #1368]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #184]
	ldr	r3, [r2, #1388]
	ldr	r1, [r2, #1384]
	uxth	r3, r3
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #188]
	ldr	r1, [r2, #1380]
	ldr	r3, [r2, #1396]
	and	r1, r1, #63
	ldr	r0, [r2, #1364]
	and	r3, r3, #63
	mov	r1, r1, asl #8
	and	r0, r0, #63
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0
	str	r3, [r5, #192]
	ldr	r3, [r2, #1376]
	ldr	r0, [r2, #1392]
	and	r3, r3, #63
	ldr	r1, [r2, #1360]
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
	bls	.L2003
.L1978:
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #204]
	bhi	.L1980
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2532]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2544]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #204]
.L1980:
	ldr	r3, [r4, #2820]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #208]
	bhi	.L1982
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2536]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2548]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #208]
.L1982:
	ldr	r3, [r8, #3408]
	ldr	r2, [r8, #3412]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #212]
	ldr	r2, [r4, #2812]
	cmp	r2, #8
	bls	.L1983
	mov	r3, #0
	str	r3, [r5, #216]
	str	r3, [r5, #220]
	str	r3, [r5, #224]
.L1984:
	ldr	r2, [r4, #2816]
	cmp	r2, #8
	bls	.L1986
	mov	r3, #0
	str	r3, [r5, #228]
	str	r3, [r5, #232]
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bhi	.L2004
.L1989:
	mov	r2, r2, asl #4
	ldr	r7, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #240]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
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
	beq	.L2005
.L1991:
	add	r4, r4, r2
	str	r3, [r5, #244]
	add	r4, r4, #5248
	ldr	r1, [r4, #64]
	ldr	r0, [r4, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2003:
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2528]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2540]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #200]
	b	.L1978
.L1986:
	mov	r2, r2, asl #4
	ldr	r7, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #228]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
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
	beq	.L2006
.L1988:
	add	r2, r4, r2
	str	r3, [r5, #232]
	add	r2, r2, #5248
	ldr	r1, [r2, #64]
	ldr	r0, [r2, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bls	.L1989
.L2004:
	mov	r3, #0
	str	r3, [r5, #240]
	str	r3, [r5, #244]
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1983:
	mov	r2, r2, asl #4
	ldr	r7, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #216]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
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
	beq	.L2007
.L1985:
	add	r2, r4, r2
	str	r3, [r5, #220]
	add	r2, r2, #5248
	ldr	r1, [r2, #64]
	ldr	r0, [r2, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #224]
	b	.L1984
.L2002:
	ldr	ip, [r2, #1028]
	ldr	r3, [r8, #3412]
	cmp	ip, r3
	movne	ip, #1048576
	moveq	ip, #0
	b	.L1966
.L2005:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L1991
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L1991
.L2006:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L1988
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L1988
.L2007:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L1985
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L1985
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
	@ args = 0, pretend = 0, frame = 168
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #180)
	sub	sp, sp, #180
	add	r3, r0, #274432
	add	ip, r0, #294912
	mov	r10, r1
	mov	r2, r3
	str	ip, [fp, #-168]
	ldr	r1, [r2, #1076]
	mov	r5, ip
	mov	ip, r2
	ldr	r2, [r2, #1072]
	str	r3, [fp, #-164]
	mov	r3, #1
	mov	lr, r1
	add	r4, r0, #270336
	mov	r6, r2
	str	r2, [fp, #-148]
	mov	r2, r3, asl lr
	mov	r3, r3, asl r6
	str	r3, [fp, #-120]
	ldr	r3, [ip, #1068]
	mov	r9, r2
	ldr	r8, [r10]
	str	r2, [fp, #-196]
	ldr	r2, [r10, #16]
	str	r1, [fp, #-200]
	add	r1, r0, #8
	str	r3, [fp, #-192]
	add	r3, r8, r2
	str	r0, [fp, #-180]
	str	r3, [fp, #-116]
	ldr	r7, [ip, #1064]
	bl	Vp9_SetPoolInfoFrame
	mov	r1, #0
	str	r1, [r5, #3524]
	ldr	r2, [r4, #2552]
	cmp	r9, #0
	ldr	r3, [r4, #2556]
	str	r2, [fp, #-160]
	and	r3, r3, #15
	str	r3, [fp, #-156]
	ble	.L2024
	ldr	r2, [fp, #-192]
	add	r3, r7, #7
	str	r1, [fp, #-184]
	add	r2, r2, #7
	mov	r0, r3, asr #3
	str	r1, [fp, #-172]
	mov	r3, r2, asr #3
	str	r0, [fp, #-152]
	str	r0, [fp, #-208]
	str	r3, [fp, #-204]
	str	r1, [fp, #-112]
	str	r1, [fp, #-188]
.L2023:
	ldr	r3, [fp, #-184]
	ldr	r2, [fp, #-204]
	ldr	r0, [fp, #-200]
	add	r3, r3, r2
	str	r3, [fp, #-184]
	ldr	r2, [fp, #-192]
	mov	r1, r3
	ldr	r3, [fp, #-188]
	mov	r1, r1, asr r0
	str	r1, [fp, #-188]
	ldr	ip, [fp, #-120]
	mov	r3, r3, asl #3
	mov	r0, r1
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-132]
	mov	r1, r3
	mov	r3, r0, asl #3
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-136]
	mov	r0, r3
	rsb	r3, r1, r0
	add	r3, r3, #7
	cmp	ip, #0
	mov	r2, r1
	mov	r3, r3, asr #3
	str	r3, [fp, #-128]
	ble	.L2016
	add	r3, r0, #7
	ldr	r0, [fp, #-208]
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
	str	r3, [fp, #-140]
	sub	r3, ip, #1
	str	r3, [fp, #-124]
	ldr	r3, [fp, #-196]
	str	r1, [fp, #-144]
	sub	r3, r3, #1
	str	r3, [fp, #-176]
	mov	r3, r10
	mov	r10, r9
	mov	r9, r3
	b	.L2022
.L2035:
	ldr	r2, [fp, #-176]
	ldr	r1, [fp, #-172]
	cmp	r2, r1
	ldrle	r2, [fp, #-116]
	rsble	r5, r8, r2
	bgt	.L2017
.L2019:
	ldrh	r1, [fp, #-132]
	rsb	r2, r3, r4
	add	r2, r2, #7
	strh	r4, [fp, #-66]	@ movhi
	add	r4, r4, #7
	mov	ip, #0
	strh	r1, [fp, #-72]	@ movhi
	mov	r0, r2, asr #3
	ldrh	r1, [fp, #-136]
	mov	r2, #0
	str	r2, [fp, #-84]
	ldr	r2, [fp, #-128]
	strh	r1, [fp, #-70]	@ movhi
	ldr	r1, [fp, #-160]
	mul	r2, r2, r0
	rsb	r0, r1, r8
	ldr	r1, [fp, #-156]
	strb	ip, [fp, #-80]
	sub	ip, fp, #44
	add	r0, r0, r1
	ldr	r1, [fp, #-140]
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
	ldr	r1, [fp, #-144]
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
	bne	.L2032
	ldr	r3, [fp, #-164]
	ldr	r3, [r3, #1768]
	cmp	r5, r3
	bgt	.L2033
.L2021:
	ldr	r3, [fp, #-120]
	add	r6, r6, #1
	ldr	r2, [r9, #16]
	add	r8, r8, r5
	cmp	r6, r3
	rsb	r2, r5, r2
	str	r2, [r9, #16]
	beq	.L2034
	str	r4, [fp, #-112]
.L2022:
	ldr	r3, [fp, #-152]
	mov	r0, r9
	ldr	r1, [fp, #-148]
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
	ldr	r3, [fp, #-124]
	cmp	r6, r3
	ldr	r3, [fp, #-108]
	bge	.L2035
.L2017:
	ldr	r2, [fp, #-116]
	cmp	r2, #0
	cmpne	r8, #0
	beq	.L2026
	add	r8, r8, #4
	str	r3, [fp, #-108]
	cmp	r2, r8
	bcc	.L2026
	mov	r1, #32
	mov	r0, r9
	bl	BsGet
	ldr	r3, [fp, #-108]
	mov	r5, r0
	b	.L2019
.L2032:
	ldr	r3, [fp, #-168]
	sub	r1, fp, #96
	ldr	r2, [r3, #3524]
	mov	r3, r1
	ldr	r1, [fp, #-180]
	mov	r0, r1
	add	r1, r1, r2, lsl #8
	add	r1, r1, #1024
	add	r1, r1, #8
	bl	Vp9_SetPoolInfoTile
	ldr	r2, [fp, #-168]
	ldr	r3, [r2, #3524]
	add	r3, r3, #1
	str	r3, [r2, #3524]
	ldr	r3, [fp, #-164]
	ldr	r3, [r3, #1768]
	cmp	r5, r3
	ble	.L2021
.L2033:
	str	r3, [sp, #4]
	mov	r0, #0
	movw	r3, #4530
	str	r5, [sp]
	ldr	r2, .L2036
	ldr	r1, .L2036+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2026:
	mvn	r0, #0
.L2015:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2034:
	mov	r10, r9
	str	r4, [fp, #-112]
.L2016:
	ldr	r3, [fp, #-172]
	ldr	r2, [fp, #-196]
	add	r3, r3, #1
	str	r3, [fp, #-172]
	cmp	r3, r2
	bne	.L2023
.L2024:
	mov	r0, #0
	b	.L2015
.L2037:
	.align	2
.L2036:
	.word	.LANCHOR0+872
	.word	.LC32
	UNWIND(.fnend)
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
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
	ldr	r4, .L2039
	mov	r2, #18
	mov	r5, r0
	mov	r6, r1
	add	r7, r1, #108
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
	mov	r1, r7
	ldr	r3, [r4, #52]
	add	r0, r5, #192
	mov	r2, #18
	blx	r3
	mov	r1, r7
	ldr	r3, [r4, #52]
	add	r0, r5, #256
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #126
	add	r0, r5, #288
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #144
	add	r0, r5, #320
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #162
	add	r0, r5, #352
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #180
	add	r0, r5, #384
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #198
	add	r0, r5, #416
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #216
	add	r0, r5, #448
	mov	r2, #18
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2040:
	.align	2
.L2039:
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	mov	r9, r3
	mov	r6, r0
	mov	r8, r2
	ldr	r7, [fp, #4]
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #216
	add	r0, r6, #512
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #432
	add	r0, r6, #1024
	add	r4, r5, #1728
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #648
	add	r0, r6, #1536
	add	r10, r5, #1760
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #864
	add	r0, r6, #2048
	add	r4, r4, #8
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #1072
	add	r1, r1, #8
	add	r0, r6, #2560
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #1296
	add	r0, r6, #3072
	add	r10, r10, #12
	bl	Vp9_TxCoefProbConvert2
	add	r1, r5, #1504
	add	r0, r6, #3584
	add	r1, r1, #8
	bl	Vp9_TxCoefProbConvert2
	add	r0, r6, #4096
	mov	r3, #0
.L2042:
	mov	r1, r4
	mov	r2, #8
	ldrb	ip, [r1, #-8]!	@ zero_extendqisi2
	b	.L2046
.L2044:
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	orr	ip, ip, lr, asl r2
	add	r2, r2, #8
	cmp	r2, #32
	streq	ip, [r0, r3, asl #2]
	addeq	r3, r3, #1
	moveq	ip, #0
	moveq	r2, ip
.L2046:
	cmp	r4, r1
	bne	.L2044
	add	r4, r4, #9
	str	ip, [r0, r3, asl #2]
	cmp	r4, r10
	add	r3, r3, #2
	bne	.L2042
	add	r2, r5, #1856
	add	r2, r2, #6
.L2045:
	mov	lr, r10
	mov	ip, #8
	ldrb	r4, [lr, #-8]!	@ zero_extendqisi2
	b	.L2050
.L2048:
	ldrb	r1, [lr, #1]!	@ zero_extendqisi2
	orr	r4, r4, r1, asl ip
	add	ip, ip, #8
	cmp	ip, #32
	streq	r4, [r0, r3, asl #2]
	addeq	r3, r3, #1
	moveq	r4, #0
	moveq	ip, r4
.L2050:
	cmp	r10, lr
	bne	.L2048
	add	r10, r10, #9
	str	r4, [r0, r3, asl #2]
	cmp	r10, r2
	add	r3, r3, #2
	bne	.L2045
	ldrb	r1, [r8, #7]	@ zero_extendqisi2
	cmp	r7, #0
	ldrb	r3, [r8, #8]	@ zero_extendqisi2
	mov	ip, #0
	ldrb	r2, [r8, #5]	@ zero_extendqisi2
	movne	r9, ip
	ldrb	lr, [r8, #6]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	mov	r7, r9, asl #6
	orr	r3, r3, r2
	sub	r7, r7, r9, asl #4
	orr	r3, r3, lr, asl #8
	str	r3, [r0, #256]
	ldrb	r3, [r8, #10]	@ zero_extendqisi2
	add	lr, r7, #1840
	ldrb	r1, [r8, #11]	@ zero_extendqisi2
	add	r7, r7, #1888
	ldrb	r2, [r8, #9]	@ zero_extendqisi2
	add	lr, lr, #13
	mov	r3, r3, asl #8
	add	r7, r7, #13
	orr	r3, r3, r1, asl #16
	add	r6, r6, #4352
	orr	r3, r3, r2
	str	r3, [r0, #260]
	ldrb	r3, [r8, #13]	@ zero_extendqisi2
	add	lr, r5, lr
	ldrb	r1, [r8, #14]	@ zero_extendqisi2
	add	r7, r5, r7
	ldrb	r8, [r8, #12]	@ zero_extendqisi2
	mov	r2, ip
	mov	r3, r3, asl #8
	mov	r4, #3
	orr	r3, r3, r1, asl #16
	orr	r3, r3, r8
	str	r3, [r0, #264]
.L2052:
	mov	r1, lr
	mov	r3, #0
.L2054:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	add	r3, r3, #1
	orr	r2, r2, r0, asl ip
	add	ip, ip, #8
	cmp	ip, #32
	streq	r2, [r6, r4, asl #2]
	addeq	r4, r4, #1
	moveq	r2, #0
	moveq	ip, r2
	cmp	r3, #3
	bne	.L2054
	add	lr, lr, #3
	cmp	lr, r7
	bne	.L2052
	ldrb	r2, [r5, #2016]	@ zero_extendqisi2
	add	r1, r6, r4, lsl #2
	ldrb	r0, [r5, #2017]	@ zero_extendqisi2
	add	lr, r4, #11
	ldrb	ip, [r5, #2015]	@ zero_extendqisi2
	mov	r7, #0
	mov	r2, r2, asl #8
	mov	r3, r7
	orr	r2, r2, r0, asl #16
	mov	r0, r7
	orr	r2, r2, ip
	str	r2, [r6, r4, asl #2]
	ldrb	r8, [r5, #2009]	@ zero_extendqisi2
	mov	r2, #1
	ldrb	ip, [r5, #2010]	@ zero_extendqisi2
	ldrb	r4, [r5, #2013]	@ zero_extendqisi2
	ldrb	r9, [r5, #2014]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #4]
	ldrb	r8, [r5, #2003]	@ zero_extendqisi2
	ldrb	ip, [r5, #2004]	@ zero_extendqisi2
	ldrb	r4, [r5, #2011]	@ zero_extendqisi2
	ldrb	r9, [r5, #2012]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #8]
	ldrb	r8, [r5, #2007]	@ zero_extendqisi2
	ldrb	ip, [r5, #2008]	@ zero_extendqisi2
	ldrb	r4, [r5, #2005]	@ zero_extendqisi2
	ldrb	r9, [r5, #2006]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #12]
	ldrb	r8, [r5, #1981]	@ zero_extendqisi2
	ldrb	ip, [r5, #1982]	@ zero_extendqisi2
	ldrb	r4, [r5, #1979]	@ zero_extendqisi2
	ldrb	r9, [r5, #1980]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #16]
	ldrb	r8, [r5, #1985]	@ zero_extendqisi2
	ldrb	ip, [r5, #1986]	@ zero_extendqisi2
	ldrb	r4, [r5, #1983]	@ zero_extendqisi2
	ldrb	r9, [r5, #1984]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #20]
	ldrb	r8, [r5, #1999]	@ zero_extendqisi2
	ldrb	ip, [r5, #2000]	@ zero_extendqisi2
	ldrb	r4, [r5, #1987]	@ zero_extendqisi2
	ldrb	r9, [r5, #1998]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #24]
	ldrb	r4, [r5, #2002]	@ zero_extendqisi2
	ldrb	ip, [r5, #2001]	@ zero_extendqisi2
	orr	ip, ip, r4, asl #8
	str	ip, [r1, #28]
	ldrb	r8, [r5, #1990]	@ zero_extendqisi2
	ldrb	ip, [r5, #1991]	@ zero_extendqisi2
	ldrb	r4, [r5, #1988]	@ zero_extendqisi2
	ldrb	r9, [r5, #1989]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #32]
	ldrb	r8, [r5, #1994]	@ zero_extendqisi2
	ldrb	ip, [r5, #1995]	@ zero_extendqisi2
	ldrb	r4, [r5, #1992]	@ zero_extendqisi2
	ldrb	r9, [r5, #1993]	@ zero_extendqisi2
	mov	r8, r8, asl #16
	orr	ip, r8, ip, asl #24
	orr	ip, ip, r4
	orr	ip, ip, r9, asl #8
	str	ip, [r1, #36]
	ldrb	ip, [r5, #1997]	@ zero_extendqisi2
	ldrb	r8, [r5, #1958]	@ zero_extendqisi2
	ldrb	r4, [r5, #1996]	@ zero_extendqisi2
	mov	ip, ip, asl #8
	orr	ip, ip, r8, asl #16
	orr	ip, ip, r4
	str	ip, [r1, #40]
.L2056:
	add	ip, r2, r7
	add	ip, ip, #1952
	add	ip, ip, #5
	add	ip, r5, ip
.L2058:
	ldrb	r1, [ip, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	orr	r0, r0, r1, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r0, [r6, lr, asl #2]
	addeq	lr, lr, #1
	moveq	r0, #0
	moveq	r3, r0
	cmp	r2, #2
	ble	.L2058
	add	r7, r7, #3
	mov	r2, #0
	cmp	r7, #21
	bne	.L2056
	add	r4, r5, #8
	mov	r3, r5
	mov	r1, r2
.L2059:
	add	r0, r2, #8
	ldrb	ip, [r3, #1950]	@ zero_extendqisi2
	cmp	r0, #32
	orr	r1, r1, ip, asl r2
	add	r2, r2, #16
	beq	.L2089
	ldrb	ip, [r3, #1951]	@ zero_extendqisi2
	cmp	r2, #32
	orr	r1, r1, ip, asl r0
	streq	r1, [r6, lr, asl #2]
	moveq	r1, #0
	addeq	lr, lr, #1
	moveq	r2, r1
.L2062:
	add	r3, r3, #2
	cmp	r3, r4
	bne	.L2059
	ldrb	r1, [r5, #2054]	@ zero_extendqisi2
	add	ip, r5, #2016
	ldrb	r2, [r5, #2021]	@ zero_extendqisi2
	add	r4, r5, #2096
	add	r0, r6, lr, lsl #2
	mov	r3, #0
	orr	r2, r2, r1, asl #8
	str	r2, [r6, lr, asl #2]
	ldrb	r2, [r5, #2019]	@ zero_extendqisi2
	add	lr, lr, #2
	ldrb	r8, [r5, #2020]	@ zero_extendqisi2
	add	ip, ip, #15
	ldrb	r7, [r5, #2018]	@ zero_extendqisi2
	add	r4, r4, #1
	mov	r2, r2, asl #8
	mov	r1, r3
	orr	r2, r2, r8, asl #16
	orr	r2, r2, r7
	str	r2, [r0, #4]
.L2064:
	sub	r2, ip, #10
.L2066:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r6, lr, asl #2]
	addeq	lr, lr, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	ip, r2
	bne	.L2066
	add	ip, ip, #33
	cmp	ip, r4
	bne	.L2064
	ldrb	r1, [r5, #2065]	@ zero_extendqisi2
	add	r4, r5, #2032
	ldrb	r2, [r5, #2032]	@ zero_extendqisi2
	add	r4, r4, #10
	add	r7, r5, #2096
	mov	r3, #0
	add	r7, r7, #12
	orr	r2, r2, r1, asl #8
	add	ip, lr, #1
	str	r2, [r6, lr, asl #2]
	mov	r1, r3
	mov	lr, r4
.L2068:
	sub	r2, lr, #10
.L2070:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r6, ip, asl #2]
	addeq	ip, ip, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, lr
	bne	.L2070
	add	lr, r2, #33
	cmp	lr, r7
	bne	.L2068
	mov	r3, #0
	mov	r1, r3
.L2071:
	mov	r8, r4
	mov	r9, #2
.L2076:
	mov	r0, r8
	mov	r2, #0
.L2073:
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	orr	r1, r1, lr, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r6, ip, asl #2]
	addeq	ip, ip, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, #3
	bne	.L2073
	subs	r9, r9, #1
	add	r8, r8, #3
	bne	.L2076
	add	r4, r4, #33
	cmp	r4, r7
	bne	.L2071
	ldrb	r3, [r5, #2050]	@ zero_extendqisi2
	add	r0, r6, ip, lsl #2
	ldrb	r1, [r5, #2051]	@ zero_extendqisi2
	ldrb	r2, [r5, #2049]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r3, r3, r1, asl #16
	orr	r3, r3, r2
	str	r3, [r6, ip, asl #2]
	ldrb	r3, [r5, #2083]	@ zero_extendqisi2
	ldrb	r1, [r5, #2084]	@ zero_extendqisi2
	ldrb	r2, [r5, #2082]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r3, r3, r1, asl #16
	orr	r3, r3, r2
	str	r3, [r0, #4]
	ldrb	r1, [r5, #2053]	@ zero_extendqisi2
	ldrb	r3, [r5, #2086]	@ zero_extendqisi2
	ldrb	r2, [r5, #2052]	@ zero_extendqisi2
	ldrb	ip, [r5, #2085]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r0, #8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2089:
	str	r1, [r6, lr, asl #2]
	mov	r2, #8
	add	lr, lr, #1
	ldrb	r1, [r3, #1951]	@ zero_extendqisi2
	b	.L2062
	UNWIND(.fnend)
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	2
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	add	r5, r0, #274432
	add	r4, r0, #294912
	add	r7, r0, #270336
	ldr	r8, [r5, #980]
	mov	r6, r0
	ldr	r3, [r5, #1084]
	sub	r0, fp, #84
	clz	lr, r8
	ldr	r9, [r5, #1060]
	ldr	r10, [r7, #2688]
	mov	ip, #0
	str	r3, [fp, #-108]
	mov	lr, lr, lsr #5
	ldr	r3, [r7, #2680]
	str	lr, [r4, #3480]
	str	r8, [r4, #3492]
	ldr	lr, [r5, #1012]
	str	r3, [fp, #-104]
	str	r9, [fp, #-96]
	movw	r9, #14072
	str	lr, [r4, #3500]
	movt	r9, 4
	ldr	lr, [r5, #1080]
	add	r9, r6, r9
	str	r2, [fp, #-116]
	str	r1, [fp, #-112]
	str	lr, [r4, #3484]
	ldr	lr, [r5, #1056]
	str	ip, [fp, #-92]
	str	ip, [fp, #-88]
	str	lr, [r4, #3504]
	ldr	lr, [r7, #2684]
	str	lr, [r4, #3508]
	ldr	lr, [r5, #1092]
	str	lr, [r4, #3512]
	ldr	lr, [r5, #976]
	str	lr, [r4, #3496]
	bl	BsInit
	ldr	r2, [r4, #3480]
	ldr	r3, [fp, #-108]
	cmp	r2, #0
	ldr	r2, [r4, #3500]
	bne	.L2092
	cmp	r2, #0
	beq	.L2101
.L2092:
	movw	r1, #16159
	stmia	sp, {r2, r8}
	mov	r0, r9
	sub	r2, fp, #96
	movt	r1, 4
	add	r1, r6, r1
	bl	Vp9_SetupPastIndependence
	ldr	r3, .L2103
	movw	r0, #10884
	mov	r2, #16
	movt	r0, 4
	mov	r1, #0
	add	r0, r6, r0
	ldr	r3, [r3, #48]
	blx	r3
.L2093:
	ldr	r3, [fp, #-96]
	movw	r2, #2087
	movw	r1, #16159
	add	r0, r5, #1776
	movt	r1, 4
	add	r0, r0, #8
	mla	r3, r2, r3, r6
	add	r1, r3, r1
	bl	memcpy
	sub	r0, fp, #84
	bl	Vp9_Cabac_ReaderInit
	ldr	r1, [r4, #3508]
	ldr	r0, [r4, #3512]
	mov	r2, r8
	ldr	ip, [fp, #-104]
	sub	lr, fp, #88
	ldr	r3, [r4, #3484]
	sub	r8, fp, #92
	str	r1, [sp, #4]
	mov	r1, r9
	str	r0, [sp]
	sub	r0, fp, #84
	str	ip, [sp, #12]
	str	r10, [sp, #8]
	str	lr, [sp, #20]
	str	r8, [sp, #16]
	bl	Vp9_ReadCompressedHeader
	cmp	r0, #0
	bne	.L2102
	ldr	r3, [fp, #-88]
	ldr	r2, [fp, #-92]
	str	r3, [r7, #2860]
	str	r3, [r4, #3488]
	ldr	r3, [r7, #2972]
	str	r2, [r7, #2864]
	cmp	r3, #0
	bne	.L2096
	movw	r8, #13384
	movt	r8, 4
	add	r8, r6, r8
.L2097:
	ldr	lr, [r4, #3484]
	movw	r0, #1037
	ldr	r3, [r5, #980]
	mov	r1, r9
	mov	r2, r8
	movt	r0, 4
	str	lr, [sp]
	add	r0, r6, r0
	bl	Vp9_ProbBurstConvert
	ldr	r3, [r7, #2636]
	ldr	r2, [fp, #-112]
	sub	r1, fp, #84
	mov	r0, r6
	add	r10, r2, r3
	ldr	r2, [fp, #-116]
	str	r10, [fp, #-84]
	rsb	r9, r3, r2
	str	r9, [fp, #-68]
	bl	Vp9_DecodeTilesCtrl
	mov	r0, #0
.L2095:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2101:
	ldr	r1, [r4, #3484]
	cmp	r1, #0
	beq	.L2093
	b	.L2092
.L2096:
	movw	r0, #10820
	movt	r0, 4
	add	r0, r6, r0
	add	r8, r0, #2560
	add	r1, r0, #336
	add	r8, r8, #4
	add	r0, r0, #256
	mov	r2, r8
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2097
.L2102:
	ldr	r1, .L2103+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2095
.L2104:
	.align	2
.L2103:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	UNWIND(.fnend)
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
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
.L2106:
	ldr	r9, [fp, #-48]
	sub	r8, r7, #1152
	ldr	r4, [fp, #-52]
.L2112:
	add	r6, r4, #576
	mov	r5, r8
	mov	ip, r9
.L2110:
	add	lr, ip, #24
	mov	r0, r5
	mov	r1, r4
.L2107:
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
	bne	.L2107
	add	r4, r4, #96
	add	r5, r5, #96
	cmp	r6, r4
	mov	ip, lr
	bne	.L2110
	add	r8, r8, #576
	add	r9, r9, #144
	cmp	r7, r8
	mov	r4, r6
	bne	.L2112
	ldr	r3, [fp, #-52]
	add	r7, r7, #1152
	add	r3, r3, #1152
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	cmp	r7, r3
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L2106
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.align	2
	.global	Vp9_RestoreCounts
	.type	Vp9_RestoreCounts, %function
Vp9_RestoreCounts:
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
	mov	r5, r2
	mov	r4, r1
	add	r2, r2, #9216
	mov	r6, r0
	add	r2, r2, #12
	mov	r1, r5
	mov	r0, r4
	bl	Vp9_CoefCountRestore
	add	r2, r5, #9792
	add	r2, r2, #12
	add	r1, r5, #2304
	add	r0, r4, #2304
	bl	Vp9_CoefCountRestore
	add	r2, r5, #10368
	add	r2, r2, #12
	add	r1, r5, #4608
	add	r0, r4, #4608
	bl	Vp9_CoefCountRestore
	add	r2, r5, #10944
	add	r0, r4, #6912
	add	r2, r2, #12
	add	r1, r5, #6912
	bl	Vp9_CoefCountRestore
	add	r0, r6, #294912
	ldr	r3, [r0, #3480]
	cmp	r3, #0
	bne	.L2114
	ldr	r3, [r0, #3484]
	cmp	r3, #0
	bne	.L2114
	add	r2, r5, #8192
	add	r0, r4, #10368
	add	r6, r4, #10176
	add	r9, r4, #9600
	add	r10, r4, #9216
	add	r9, r9, #32
	add	r7, r4, #10048
	str	r10, [r2, #1032]
	str	r9, [r2, #1028]
	add	r10, r4, #9472
	add	r9, r4, #10432
	str	r10, [r2, #1024]
	add	r10, r4, #10496
	str	r10, [fp, #-52]
	mov	r5, r6
	mov	r1, r0
	mov	r3, r0
	add	r7, r7, #32
	add	r6, r6, #16
	add	r0, r0, #16
	add	r3, r3, #56
	add	ip, r4, #10304
	str	r7, [r2, #3344]
	add	r7, r9, #24
	str	r6, [r2, #3348]
	add	r9, r9, #48
	add	r6, r4, #10560
	str	r0, [r2, #3372]
	str	r3, [r2, #3364]
	add	r0, r4, #10752
	add	r3, r4, #10816
	str	r7, [r2, #3376]
	str	r9, [r2, #3380]
	add	r9, r4, #10880
	ldr	r7, [fp, #-52]
	add	ip, ip, #40
	add	r8, r4, #9984
	add	lr, r4, #10240
	str	ip, [r2, #3360]
	add	ip, r4, #10688
	add	r8, r8, #48
	add	r5, r5, #48
	add	lr, lr, #24
	add	r1, r1, #32
	str	r8, [r2, #3340]
	add	r7, r7, #60
	mov	r8, r10
	str	r5, [r2, #3352]
	add	r10, r10, #8
	mov	r5, r6
	str	lr, [r2, #3356]
	add	r5, r5, #48
	mov	lr, r6
	str	r1, [r2, #3368]
	str	r10, [r2, #3416]
	mov	r1, r0
	mov	r10, r3
	add	r1, r1, #56
	str	r8, [r2, #3384]
	add	r6, r6, #40
	add	r8, r8, #16
	add	lr, lr, #56
	str	r8, [r2, #3388]
	add	ip, ip, #8
	mov	r8, r9
	add	r0, r0, #24
	str	r1, [r2, #3432]
	add	r3, r3, #24
	add	r1, r10, #40
	str	r9, [r2, #3440]
	add	r10, r10, #56
	add	r9, r9, #8
	add	r8, r8, #16
	str	r7, [r2, #3420]
	str	r6, [r2, #3392]
	str	r5, [r2, #3424]
	str	lr, [r2, #3396]
	str	ip, [r2, #3428]
	str	r0, [r2, #3400]
	str	r3, [r2, #3404]
	str	r1, [r2, #3436]
	str	r10, [r2, #3408]
	str	r9, [r2, #3412]
	str	r8, [r2, #3444]
.L2114:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_RestoreCounts, .-Vp9_RestoreCounts
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	cmp	r2, #0
	str	r2, [fp, #-64]
	add	r2, r0, #274432
	add	r7, r0, #270336
	mov	r8, r0
	mov	ip, r2
	str	r2, [fp, #-48]
	ldrb	r0, [r7, #2089]	@ zero_extendqisi2
	str	r1, [fp, #-52]
	ldr	r2, [r7, #2476]
	ldr	r1, [ip, #1060]
	str	r3, [fp, #-56]
	ldr	r3, [ip, #1052]
	str	r1, [fp, #-72]
	strb	r0, [r7, #2628]
	str	r3, [fp, #-68]
	str	r2, [r7, #2632]
	beq	.L2117
	ldr	r1, [fp, #-56]
	ldr	r2, .L2177
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L2134
.L2117:
	add	r6, r8, #294912
	ldr	r3, [r6, #3424]
	cmp	r3, #0
	beq	.L2120
	ldr	r2, [r6, #3464]
	ldr	r3, [r6, #3460]
	cmp	r2, r3
	beq	.L2120
.L2121:
	ldr	r1, [r7, #2612]
	ldr	r0, [r6, #3516]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	str	r3, [fp, #-60]
	beq	.L2139
	movw	r4, #10932
	movw	r5, #11012
	movw	r9, #10968
	movt	r4, 4
	movt	r5, 4
	movt	r9, 4
	add	r4, r8, r4
	add	r5, r8, r5
	add	r10, r7, #2704
	add	r9, r8, r9
	b	.L2125
.L2123:
	clz	r3, r3
	cmp	r0, #0
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L2167
.L2124:
	cmp	r4, r9
	beq	.L2168
.L2125:
	ldr	r3, [r10, #4]!
	ldr	r0, [r4, #4]!
	adds	r2, r3, #0
	ldr	r1, [r5, #4]!
	movne	r2, #1
	cmp	r0, #0
	movne	r2, #0
	cmp	r2, #0
	beq	.L2123
	mov	r2, #1
	ldr	r0, [r6, #3516]
	bl	FSP_SetRef
	cmp	r4, r9
	bne	.L2125
.L2168:
	ldr	r3, .L2177+4
	movw	r0, #10820
	movt	r0, 4
	add	r0, r8, r0
	add	r1, r0, #80
	mov	r2, #36
	ldr	r3, [r3, #52]
	add	r0, r0, #116
	blx	r3
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	blt	.L2126
	cmp	r3, #100
	movlt	r2, r3
	ldr	r3, [fp, #-60]
	movge	r2, #100
	str	r2, [r3, #152]
	ldr	r3, [r8]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L2169
.L2127:
	mov	r0, r8
	bl	VP9_SetImgFormat
	ldr	r3, [r7, #2564]
	cmp	r3, #2
	beq	.L2170
.L2128:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #996]
	cmp	r3, #0
	bne	.L2130
.L2129:
	mvn	r3, #0
	ldr	r1, [r7, #2612]
	str	r3, [r7, #2616]
	mov	r2, #0
	ldr	r0, [r6, #3516]
	bl	FSP_SetDisplay
	ldr	r1, [r7, #2616]
.L2131:
	cmn	r1, #1
	beq	.L2132
	ldr	r0, [r6, #3516]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L2171
	mov	r2, #1
	ldr	r1, [r7, #2616]
	ldr	r0, [r6, #3516]
	bl	FSP_SetDisplay
	movw	r3, #13688
	ldr	r0, [r6, #3516]
	movt	r3, 4
	str	r4, [sp]
	mov	r2, r8
	add	r3, r8, r3
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r4, r0
	bne	.L2172
.L2132:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	beq	.L2134
	ldr	r1, [fp, #-56]
	ldr	r2, .L2177
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #2
	beq	.L2119
.L2134:
	ldr	r3, [fp, #-48]
	ldr	r4, [r3, #1000]
	cmp	r4, #0
	beq	.L2173
.L2119:
	mov	r4, #0
.L2165:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2167:
	ldr	r0, [r6, #3516]
	bl	FSP_SetRef
	b	.L2124
.L2130:
	ldr	r1, [r7, #2612]
	str	r1, [r7, #2616]
	b	.L2131
.L2173:
	ldr	r0, [r7, #2364]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L2174
	add	r6, r8, #294912
	ldr	r2, [r6, #3480]
	cmp	r2, #0
	ldr	r2, [r6, #3500]
	bne	.L2175
	cmp	r2, #0
	movne	r5, r4
	bne	.L2138
	ldr	r2, [r6, #3484]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	movne	r5, #0
	moveq	r5, r2
.L2137:
	ldr	r2, [r6, #3504]
	cmp	r2, #0
	beq	.L2176
.L2138:
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	beq	.L2119
	movw	r2, #2087
	ldr	r3, [fp, #-48]
	mla	r8, r2, r5, r8
	add	r1, r3, #1776
	movw	r0, #16159
	add	r1, r1, #8
	movt	r0, 4
	add	r0, r8, r0
	bl	memcpy
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2120:
	mov	r1, r8
	mov	r0, #17
	bl	ReleasePacket
	mov	r3, #0
	str	r3, [r6, #3424]
	b	.L2121
.L2126:
	ldr	r2, [fp, #-60]
	mov	r3, #0
	str	r3, [r2, #152]
	b	.L2127
.L2170:
	ldr	r3, [r7, #2620]
	cmp	r3, #0
	bne	.L2129
	b	.L2128
.L2175:
	cmp	r2, #0
	mov	r5, r4
	beq	.L2137
	b	.L2138
.L2172:
	ldr	r1, [r7, #2616]
	mov	r2, #0
	ldr	r0, [r6, #3516]
	bl	FSP_SetDisplay
	ldr	r1, .L2177+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2176:
	ldr	r1, [fp, #-72]
	movw	lr, #2087
	ldr	r2, .L2177+4
	mov	r0, r3
	movw	r10, #16159
	str	r3, [fp, #-52]
	mla	lr, lr, r1, r8
	ldr	ip, [r2, #140]
	ldr	r1, [r7, #2364]
	mov	r2, #11264
	movw	r9, #24508
	movt	r10, 4
	add	r10, lr, r10
	blx	ip
	ldr	r3, [fp, #-52]
	movt	r9, 4
	add	r9, r8, r9
	mov	r0, r8
	movw	r7, #14072
	mov	r1, r3
	mov	r2, r9
	bl	Vp9_RestoreCounts
	ldr	r3, [r6, #3484]
	ldr	lr, [r6, #3496]
	movt	r7, 4
	ldr	ip, [r6, #3492]
	add	r7, r8, r7
	mov	r2, r9
	mov	r1, r10
	stmib	sp, {r3, lr}
	mov	r0, r7
	mov	r3, r5
	str	ip, [sp]
	bl	Vp9_AdaptResidualProbs
	ldr	r3, [r6, #3480]
	cmp	r3, #0
	bne	.L2138
	ldr	r3, [r6, #3484]
	cmp	r3, #0
	bne	.L2138
	ldr	ip, [r6, #3488]
	mov	r2, r9
	ldr	r3, [r6, #3512]
	mov	r1, r10
	mov	r0, r7
	str	ip, [sp]
	bl	Vp9_AdaptModeProbs
	ldr	r3, [r6, #3508]
	mov	r2, r9
	mov	r1, r10
	mov	r0, r7
	bl	Vp9_AdaptMvProbs
	b	.L2138
.L2169:
	ldr	r1, .L2177+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r7, #2612]
	ldr	r0, [r6, #3516]
	mov	r2, #0
	bl	FSP_SetDisplay
	ldr	r1, [r7, #2612]
	ldr	r0, [r6, #3516]
	mov	r2, #0
	mvn	r4, #0
	bl	FSP_SetRef
	b	.L2165
.L2171:
	movw	r2, #2596
	ldr	r1, .L2177+16
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2165
.L2139:
	ldr	r1, .L2177+20
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L2165
.L2174:
	ldr	r1, .L2177+24
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L2165
.L2178:
	.align	2
.L2177:
	.word	g_VdmDrvParam+40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC37
	.word	.LC35
	.word	.LC36
	.word	.LC34
	.word	.LC38
	UNWIND(.fnend)
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	2
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #294912
	movw	r7, #14040
	movw	r8, #10820
	ldr	r3, [r4, #3420]
	movt	r7, 4
	movt	r8, 4
	mov	r5, r0
	cmp	r3, #0
	str	r1, [fp, #-56]
	add	r6, r0, #274432
	add	r7, r0, r7
	add	r8, r0, r8
	beq	.L2180
	ldr	r3, [r6, #972]
	cmp	r3, #0
	blt	.L2180
.L2181:
	str	r3, [r4, #3416]
	mov	r1, r8
	mov	r0, r7
	bl	Read_UnCompressed_Header
	subs	r10, r0, #0
	bne	.L2257
	ldr	r2, [r6, #1040]
	ldr	r3, [r5]
	str	r2, [r3, #900]
	ldr	r2, [r6, #1040]
	cmp	r2, #8
	beq	.L2188
	ldr	r1, .L2275
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2275+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2188
	ldr	lr, [r6, #1040]
	mov	r3, #8
	str	r10, [fp, #-52]
	sub	r2, fp, #52
	mov	r1, #119
	ldr	r0, [r4, #3516]
	str	lr, [fp, #-48]
	blx	ip
.L2188:
	ldr	r3, [r6, #1000]
	add	r9, r5, #270336
	cmp	r3, #0
	bne	.L2190
	ldr	r2, [r9, #2560]
	cmp	r2, #7
	ble	.L2260
.L2190:
	ldr	r3, [r6, #1024]
	sub	r2, r3, #128
	cmp	r2, #3968
	bls	.L2261
.L2191:
	ldr	r3, .L2275+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2257
	mov	r3, #0
	ldr	r0, [r4, #3516]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L2254:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2180:
	add	r9, r5, #270336
	ldr	r3, [r9, #2708]
	cmp	r3, #0
	beq	.L2182
	movw	r2, #10900
	mov	r3, #1
	movt	r2, 4
	add	r2, r5, r2
.L2183:
	ldr	r1, [r2, #4]!
	cmp	r1, #0
	beq	.L2182
	add	r3, r3, #1
	cmp	r3, #9
	bne	.L2183
	mvn	r3, #0
	str	r3, [r6, #972]
.L2222:
	ldr	r1, .L2275+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2254
.L2261:
	ldr	r2, [r6, #1028]
	sub	r1, r2, #128
	cmp	r1, #3968
	bhi	.L2191
	adds	r1, r3, #63
	str	r3, [r9, #2648]
	addmi	r1, r3, #126
	adds	r3, r2, #63
	addmi	r3, r2, #126
	str	r2, [r9, #2652]
	mov	r0, r5
	mov	r2, r1, asr #6
	mov	r3, r3, asr #6
	str	r2, [r9, #2640]
	str	r3, [r9, #2644]
	bl	VP9_GetRefNum
	str	r0, [r4, #3392]
	ldr	r0, [r4, #3516]
	ldr	r2, [r9, #2652]
	ldr	r1, [r9, #2648]
	bl	VCTRL_GetFsSize
	mov	r1, r0
	str	r0, [r4, #3380]
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r3, .L2275+12
	ldr	r1, [r4, #3516]
	ldr	r2, [r3, r1, asl #2]
	str	r0, [r4, #3384]
	ldr	r3, [r2, #1392]
	str	r3, [r4, #3388]
	ldr	r0, [r9, #2648]
	cmp	r0, #1920
	bhi	.L2194
	ldr	lr, [r9, #2652]
	cmp	lr, #1088
	bhi	.L2194
	ldr	lr, [r2, #36]
	cmp	lr, #24
	beq	.L2194
	add	r2, r2, #294912
	ldr	r2, [r2, #876]
	cmp	r2, #0
	addeq	r3, r3, #4
.L2194:
	ldr	lr, [r4, #3396]
	ldr	r2, [r4, #3392]
	ldr	r10, [r4, #3400]
	cmp	r2, lr
	movge	lr, r2
	cmp	r0, r10
	add	r3, lr, r3
	str	r3, [r4, #3388]
	beq	.L2262
.L2195:
	str	r2, [r4, #3396]
.L2197:
	mov	r0, r1
	mov	r1, #0
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #3384]
	cmp	r0, r2
	str	r0, [fp, #-60]
	ble	.L2198
	rsb	r3, r2, r0
	cmp	r3, #0
	ble	.L2198
	mov	r10, #0
	b	.L2200
.L2263:
	ldr	r3, [fp, #-60]
	rsb	r1, r2, r3
	cmp	r1, r10
	ble	.L2198
.L2200:
	ldr	r1, [r4, #3380]
	add	r10, r10, #1
	ldr	r0, [r4, #3516]
	bl	FSP_RelsePhyFs
	ldr	r2, [r4, #3384]
	cmp	r0, #0
	beq	.L2263
.L2198:
	ldr	r3, [r4, #3388]
	cmp	r3, r2
	bge	.L2203
	rsb	r2, r3, r2
	cmp	r2, #0
	ble	.L2203
	mov	r10, #0
	b	.L2204
.L2264:
	ldr	r3, [r4, #3384]
	ldr	r2, [r4, #3388]
	rsb	r3, r2, r3
	cmp	r3, r10
	ble	.L2203
.L2204:
	mov	r1, #0
	ldr	r0, [r4, #3516]
	bl	FSP_RelsePhyFs
	add	r10, r10, #1
	cmp	r0, #0
	beq	.L2264
.L2203:
	mov	r1, #0
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r3, [r4, #3388]
	add	r3, r3, #4
	cmp	r0, r3
	mov	r10, r0
	bgt	.L2265
	ldr	r1, [r4, #3380]
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r1, [r4, #3388]
	mov	r3, r0
	ldr	r0, [r4, #3392]
	str	r3, [r4, #3384]
	add	r2, r0, #1
	str	r3, [sp, #4]
	cmp	r3, r2
	rsb	r2, r10, r3
	addgt	lr, r0, #2
	addle	lr, r3, #1
	add	r2, r2, r1
	str	r0, [sp, #8]
	cmp	lr, r2
	str	r10, [sp]
	mov	r0, #2
	ldr	r1, .L2275+16
	movlt	lr, r2
	str	lr, [r4, #3388]
	ldr	r3, [r9, #2652]
	ldr	r2, [r9, #2648]
	str	lr, [sp, #12]
	bl	dprint_vfmw
	ldr	r3, [r9, #2568]
	cmp	r3, #0
	beq	.L2207
	ldr	r2, [r4, #3400]
	ldr	r3, [r9, #2648]
	cmp	r2, r3
	bne	.L2207
	ldr	r2, [r4, #3404]
	ldr	r3, [r9, #2652]
	cmp	r2, r3
	bne	.L2207
	ldr	r2, [r4, #3384]
	ldr	r3, [r4, #3388]
	cmp	r2, r3
	bge	.L2208
.L2207:
	mov	r0, r5
	bl	VP9_ArrangeVHBMem
	ldr	r3, [r9, #2568]
	cmp	r3, #0
	beq	.L2266
.L2208:
	ldr	r3, [r5]
	ldr	r3, [r3, #8]
	str	r3, [r9, #2564]
	ldr	r3, [r6, #1000]
	ldr	r0, [r4, #3516]
	cmp	r3, #0
	ldreq	r3, [r9, #2648]
	streq	r3, [r4, #3400]
	ldreq	r3, [r9, #2652]
	streq	r3, [r4, #3404]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	bne	.L2267
	mov	r0, r7
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	bne	.L2268
.L2211:
	ldr	r3, [r6, #1000]
	cmp	r3, #0
	beq	.L2269
.L2212:
	mov	r0, r5
	bl	VP9_GetImageBuffer
	cmp	r0, #0
	bne	.L2270
	ldr	r3, [r4, #3416]
	mov	r0, r5
	ldr	r2, [r9, #2612]
	add	r3, r9, r3, lsl #2
	str	r2, [r3, #2824]
	bl	VP9_Set_DecParam
	cmp	r0, #0
	bne	.L2271
	ldr	r3, [r6, #1000]
	cmp	r3, #1
	beq	.L2272
	ldr	r3, [r9, #2648]
	str	r3, [r4, #3408]
	ldr	r3, [r9, #2652]
	str	r3, [r4, #3412]
.L2217:
	mov	r0, r8
	bl	swap_frame_buffers
	ldr	r2, [r4, #3468]
	ldr	r0, [r4, #3472]
	cmp	r2, r0
	bcs	.L2218
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2218
	add	r3, r2, #1
	b	.L2219
.L2273:
	ldrb	r1, [r2]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2218
.L2219:
	cmp	r3, r0
	str	r3, [r4, #3468]
	mov	r2, r3
	add	r3, r3, #1
	bne	.L2273
.L2218:
	ldr	r3, [r4, #3424]
	cmp	r3, #1
	beq	.L2274
.L2220:
	mov	r7, #0
	str	r7, [r4, #3420]
	ldr	r0, [r6, #1000]
	cmp	r0, r7
	bne	.L2221
	ldr	r3, [r6, #996]
	str	r3, [r6, #1008]
	b	.L2254
.L2260:
	ldr	r1, .L2275+20
	mov	r0, #1
	bl	dprint_vfmw
.L2257:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2182:
	add	ip, r9, r3, lsl #2
	cmp	r3, #0
	mov	r2, #1
	str	r2, [ip, #2708]
	str	r3, [r6, #972]
	bge	.L2181
	b	.L2222
.L2262:
	ldr	r3, [r9, #2652]
	ldr	r0, [r4, #3404]
	cmp	r0, r3
	streq	lr, [r4, #3396]
	bne	.L2195
	b	.L2197
.L2269:
	ldr	r3, [r6, #1776]
	mov	r0, r5
	ldr	r2, [r6, #1768]
	add	r3, r3, #7
	ldr	r1, [fp, #-56]
	mov	r3, r3, lsr #3
	add	r1, r1, r3
	rsb	r2, r3, r2
	bl	Vp9_DecodeTiles
	b	.L2212
.L2268:
	mov	r0, r7
	bl	BsGet
	b	.L2211
.L2272:
	ldr	r0, [r6, #972]
	movw	r3, #10900
	movt	r3, 4
	add	r3, r5, r3
	ldr	r2, [r6, #1004]
	ldr	r1, [r3, r0, asl #2]
	cmp	r1, #0
	subgt	r1, r1, #1
	strgt	r1, [r3, r0, asl #2]
	str	r2, [r6, #972]
	ldr	r1, [r3, r2, asl #2]
	add	r1, r1, #1
	str	r1, [r3, r2, asl #2]
	b	.L2217
.L2221:
	mov	r0, r5
	mov	r3, r7
	mov	r2, r7
	mov	r1, r7
	bl	VP9DEC_VDMPostProc
	mov	r0, r7
	b	.L2254
.L2274:
	ldr	r1, [r4, #3464]
	add	r3, r1, #73728
	add	r1, r1, #1
	add	r3, r3, #856
	add	r3, r5, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r1, [r4, #3464]
	add	r2, r2, r3
	str	r2, [r4, #3468]
	b	.L2220
.L2265:
	mvn	r0, #1
	b	.L2254
.L2267:
	movw	r3, #4047
	ldr	r2, .L2275+24
	ldr	r1, .L2275+28
	mov	r0, #23
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2254
.L2270:
	ldr	r1, .L2275+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2254
.L2266:
	ldr	r1, .L2275+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2254
.L2271:
	ldr	r1, .L2275+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2254
.L2276:
	.align	2
.L2275:
	.word	.LC40
	.word	g_event_report
	.word	.LC39
	.word	s_pstVfmwChan
	.word	.LC42
	.word	.LC41
	.word	.LANCHOR0+892
	.word	.LC44
	.word	.LC45
	.word	.LC43
	.word	.LC46
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
	beq	.L2289
	ldr	r0, [r1]
	add	r8, r4, #270336
	add	r5, r4, #294912
	str	r0, [r8, #2552]
	ldr	r3, [r1, #8]
	str	r3, [r8, #2556]
	ldr	r1, [r1, #12]
	str	r1, [r8, #2560]
	ldr	r6, [r5, #3424]
	cmp	r6, #0
	beq	.L2298
	ldr	r2, [r5, #3476]
	ldr	r7, [r5, #3468]
	b	.L2282
.L2300:
	ldrb	ip, [r7]	@ zero_extendqisi2
	and	r3, ip, #7
	and	r0, ip, #224
	ubfx	r1, ip, #3, #2
	add	r3, r3, #1
	cmp	r0, #192
	mla	r3, r1, r3, r3
	bne	.L2285
	add	r1, r3, #2
	cmp	r1, r2
	bls	.L2299
.L2282:
	cmp	r2, #0
	bne	.L2300
.L2285:
	cmp	r6, #1
	movw	r0, #14040
	mov	r1, r7
	movt	r0, 4
	ldreq	r3, [r5, #3464]
	add	r0, r4, r0
	addeq	r3, r3, #73728
	addeq	r3, r3, #856
	addeq	r3, r4, r3, lsl #2
	ldreq	r2, [r3, #4]
	bl	BsInit
	mov	r1, r7
	mov	r0, r4
	bl	VP9DEC_DecodeFame
	cmn	r0, #2
	mov	r6, r0
	moveq	r3, #1
	streq	r3, [r5, #3420]
	beq	.L2278
	cmp	r6, #0
	moveq	r0, r6
	bne	.L2301
.L2278:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2301:
	mov	r0, r4
	bl	VP9_FreeCurFb
	mov	r3, #0
	mov	r1, r4
	str	r3, [r5, #3424]
	mov	r0, #17
	bl	ReleasePacket
	ldr	r1, .L2303
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2299:
	add	r3, r7, r3
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, ip
	bne	.L2282
	ldr	r3, [r5, #3472]
	add	r7, r7, r1
	rsb	r2, r1, r2
	str	r7, [r5, #3468]
	cmp	r7, r3
	str	r2, [r5, #3476]
	bcc	.L2282
	b	.L2285
.L2298:
	sub	r3, fp, #72
	sub	r2, fp, #68
	bl	Vp9_ParseSuperFrameIndex
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L2302
.L2280:
	ldr	r7, [r8, #2552]
	ldr	r6, [r5, #3424]
	str	r7, [r5, #3468]
	ldr	r2, [r8, #2560]
	add	r3, r7, r2
	str	r3, [r5, #3472]
	str	r2, [r5, #3476]
	b	.L2282
.L2302:
	ldr	r2, .L2303+4
	movw	r0, #36196
	str	r3, [r5, #3460]
	mov	ip, #1
	str	r6, [r5, #3464]
	sub	r1, fp, #68
	ldr	r3, [r2, #52]
	movt	r0, 4
	mov	r2, #32
	add	r0, r4, r0
	str	ip, [r5, #3424]
	blx	r3
	b	.L2280
.L2289:
	mvn	r0, #0
	b	.L2278
.L2304:
	.align	2
.L2303:
	.word	.LC47
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	2
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
	.space	3
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
	.type	vp9_inter_mode_tree, %object
	.size	vp9_inter_mode_tree, 6
vp9_inter_mode_tree:
	.byte	-2
	.byte	2
	.byte	0
	.byte	4
	.byte	-1
	.byte	-3
	.space	2
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
	.space	2
	.type	vp9_partition_tree, %object
	.size	vp9_partition_tree, 6
vp9_partition_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.space	2
	.type	vp9_switchable_interp_tree, %object
	.size	vp9_switchable_interp_tree, 4
vp9_switchable_interp_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	-2
.LC0:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.space	2
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
	.type	__func__.14546, %object
	.size	__func__.14546, 19
__func__.14546:
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
	.type	__func__.14724, %object
	.size	__func__.14724, 16
__func__.14724:
	.ascii	"VP9_Set_Segdata\000"
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.type	__FUNCTION__.14800, %object
	.size	__FUNCTION__.14800, 33
__FUNCTION__.14800:
	.ascii	"VP9_get_fixed_point_scale_factor\000"
	.space	3
	.type	__FUNCTION__.14829, %object
	.size	__FUNCTION__.14829, 35
__FUNCTION__.14829:
	.ascii	"Vp9_ReadBitDepthColorSpaceSampling\000"
	.space	1
	.type	__FUNCTION__.14859, %object
	.size	__FUNCTION__.14859, 25
__FUNCTION__.14859:
	.ascii	"Read_UnCompressed_Header\000"
	.space	3
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
	.space	3
	.type	__func__.15079, %object
	.size	__func__.15079, 20
__func__.15079:
	.ascii	"Vp9_DecodeTilesCtrl\000"
	.type	__func__.14939, %object
	.size	__func__.14939, 18
__func__.14939:
	.ascii	"VP9DEC_DecodeFame\000"
	.data
	.align	2
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	9
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
	.space	2
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
.LC3:
	ASCII(.ascii	"IN VP9DEC_Init\012\000" )
.LC4:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC5:
	ASCII(.ascii	"data_sz == 0\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"line: %d, fs is NULL!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"%s  idx=%d\012\000" )
.LC12:
	ASCII(.ascii	"FSP_GetLogicFs err\000" )
	.space	1
.LC13:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"Invalid frame sync code\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"ref_deltas\000" )
	.space	1
.LC16:
	ASCII(.ascii	"mode_deltas\000" )
.LC17:
	ASCII(.ascii	"delta_q\000" )
.LC18:
	ASCII(.ascii	"%s  %d ERR\012\000" )
.LC19:
	ASCII(.ascii	"%s:%d this_size:%d is invalid!\012\000" )
.LC20:
	ASCII(.ascii	"4:4:4 color is not supported in profile 0 or 2 (%s " )
	ASCII(.ascii	": %d)\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"Invalid frame marker\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"%s:%d w&h=%dx%d is invalid!\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"VP9_Set_DecParam but logic fs is null!\012\000" )
.LC24:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC25:
	ASCII(.ascii	"VP9_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC27:
	ASCII(.ascii	"pic_width_in_pix:%d, pic_height_in_pix:%d\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"vp9 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"vp9 alloc frame only\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s:%d size is invalid  size:%d bslen:%d\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"ERROR:Vp9_ReadCompressedHeader\012\000" )
.LC34:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC36:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC37:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"pu8ProbCntVir == NULL\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"get_free_fb failed!\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"bit_depth(%d) not equal 8.\012\000" )
.LC41:
	ASCII(.ascii	"ERROR: pCtx->StreamParam.Length(%d) < 8\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\012\000" )
.LC43:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"%s %d, no fsp\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"VP9_GetImageBuffer From Queue err\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"ERROR: VP9_Set_DecParam\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"VP9_DecOneNal ERR\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
