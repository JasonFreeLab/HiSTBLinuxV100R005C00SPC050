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
	.file	"mpeg4.c"
	.text
	.align	2
	.global	log2bin
	.type	log2bin, %function
log2bin:
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
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r3, #0
.L3:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L3
	sxth	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	log2bin, .-log2bin
	.align	2
	.global	bs_get_spritetrajectory
	.type	bs_get_spritetrajectory, %function
bs_get_spritetrajectory:
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
	ldr	r6, .L13
	mov	r7, r0
	mov	r4, #0
	mov	r5, r6
.L10:
	ldrb	r1, [r5, #4]	@ zero_extendqisi2
	mov	r0, r7
	bl	BsShow
	ldr	r3, [r6, r4, asl #3]
	ldr	r2, .L13
	mov	r1, r4, asl #3
	add	r5, r5, #8
	cmp	r0, r3
	beq	.L12
	add	r4, r4, #1
	cmp	r4, #12
	bne	.L10
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L12:
	add	r2, r2, r1
	mov	r0, r7
	ldrb	r1, [r2, #4]	@ zero_extendqisi2
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L14:
	.align	2
.L13:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	bs_get_spritetrajectory, .-bs_get_spritetrajectory
	.global	__aeabi_idiv
	.align	2
	.global	MP4_GetGMCparam
	.type	MP4_GetGMCparam, %function
MP4_GetGMCparam:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldrb	r5, [r0, #73]	@ zero_extendqisi2
	mov	r3, #2
	mov	r10, r0
	mov	r3, r3, asl r5
	mov	r9, r1
	mov	r0, #16
	rsb	r2, r5, #3
	mov	r1, r3
	str	r3, [fp, #-56]
	str	r2, [fp, #-100]
	bl	__aeabi_idiv
	ldr	r8, [r10, #716]
	ldr	r3, [r10, #712]
	cmp	r8, #1
	mov	r2, r8, asl #4
	str	r2, [r9, #8]
	str	r2, [fp, #-64]
	ldr	r2, [r10, #712]
	mov	r2, r2, asl #4
	str	r2, [r9, #12]
	ldrb	r2, [r10, #73]	@ zero_extendqisi2
	str	r2, [r9, #4]
	ldrb	r2, [r10, #72]	@ zero_extendqisi2
	str	r2, [r9]
	str	r2, [fp, #-68]
	ldr	r2, [r10, #704]
	ldr	ip, [r10, #688]
	str	r2, [fp, #-52]
	ldr	r2, [r10, #708]
	str	r2, [fp, #-72]
	str	r0, [fp, #-48]
	add	r0, r10, #692
	ldmia	r0, {r0, r1, lr}
	ble	.L40
	mov	r5, #0
	mov	r2, #1
.L17:
	add	r5, r5, #1
	mov	r6, r2, asl r5
	cmp	r8, r6
	bgt	.L17
	mov	r2, r6, asl #4
	str	r2, [fp, #-96]
.L16:
	cmp	r3, #1
	ble	.L41
	mov	r4, #0
	mov	r2, #1
.L19:
	add	r4, r4, #1
	mov	r7, r2, asl r4
	cmp	r3, r7
	bgt	.L19
	mov	r2, r7, asl #4
	str	r2, [fp, #-104]
.L18:
	ldrb	r2, [r10, #12]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L45
	add	r2, ip, r8, lsl #1
	add	lr, r0, lr
	add	r1, r1, r2
	ldr	r2, [fp, #-56]
	str	lr, [fp, #-76]
	add	r10, r0, r3, lsl #1
	ldr	lr, [fp, #-52]
	mov	r2, r2, asr #1
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-72]
	add	lr, ip, lr
	add	r10, r2, r10
	ldr	r2, [fp, #-52]
	mul	ip, r2, ip
	mul	r1, r1, r2
	str	ip, [fp, #-60]
	ldr	ip, [fp, #-76]
	mul	ip, ip, r2
	str	ip, [fp, #-84]
	mul	ip, lr, r2
	str	ip, [fp, #-88]
	mul	ip, r10, r2
	mul	r2, r2, r0
	str	ip, [fp, #-92]
	str	r2, [fp, #-52]
.L21:
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-48]
	ldr	lr, [fp, #-60]
	rsb	r0, r2, #0
	rsb	r2, r6, r8
	str	r3, [fp, #-72]
	mla	r0, r1, ip, r0
	mov	r1, r8
	mul	r10, lr, ip
	mov	ip, r8, asr #1
	str	r2, [fp, #-76]
	str	ip, [fp, #-80]
	mul	r0, r6, r0
	mla	r0, r10, r2, r0
	cmp	r0, #0
	addgt	r0, r0, ip
	rsble	r0, ip, r0
	bl	__aeabi_idiv
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-48]
	ldr	ip, [fp, #-80]
	mul	r1, r2, r3
	ldr	r2, [fp, #-52]
	mul	r3, r2, r3
	ldr	r2, [fp, #-76]
	mul	r1, r6, r1
	mla	r2, r3, r2, r1
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-96]
	mov	r1, r8
	cmp	r2, #0
	add	r3, r0, r3
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-72]
	addgt	r0, r2, ip
	rsble	r0, ip, r2
	str	r3, [fp, #-72]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-88]
	ldr	r2, [fp, #-48]
	ldr	r8, [fp, #-92]
	mul	lr, r3, r2
	ldr	r3, [fp, #-72]
	rsb	r2, r7, r3
	mov	r1, r3, asr #1
	mov	ip, r0
	mul	r0, r7, lr
	ldr	lr, [fp, #-48]
	mla	r10, r2, r10, r0
	mov	r0, r3, asl #4
	rsb	r0, r0, #0
	mla	r0, r8, lr, r0
	ldr	lr, [fp, #-64]
	cmp	r10, #0
	addgt	r10, r10, r1
	rsble	r10, r1, r10
	mul	r0, r7, r0
	mla	r0, r2, lr, r0
	cmp	r0, #0
	addgt	r2, r0, r1
	rsble	r2, r1, r0
	str	r2, [fp, #-72]
	ldr	r2, [fp, #-68]
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L30
.L32:
	.word	.L42
	.word	.L33
	.word	.L34
	.word	.L35
.L42:
	mov	r0, #0
	mov	r3, r0
	mov	r8, r0
	mov	r10, r0
.L31:
	mov	r5, #0
	mov	ip, r5
.L39:
	ldr	r1, [fp, #-56]
	mov	r10, r10, asr r5
	mov	r3, r3, asr ip
	mov	r5, r8, asr r5
	mov	r0, r0, asr ip
	str	r3, [r9, #40]
	mov	r2, #1
	mov	r3, #0
	str	r10, [r9, #32]
	str	r5, [r9, #36]
	str	r0, [r9, #44]
	str	r1, [r9, #16]
	str	r1, [r9, #28]
	str	r3, [r9, #20]
	str	r3, [r9, #24]
	str	r2, [r9]
	b	.L15
.L35:
	ldr	r2, [fp, #-48]
	cmp	r4, r5
	ldr	r1, [fp, #-60]
	rsb	r2, r2, #0
	ldr	lr, [fp, #-100]
	str	ip, [fp, #-84]
	mov	r0, r2
	add	r2, r5, r4
	add	r2, r2, lr
	movge	r4, r5
	mul	ip, r1, r0
	rsb	r5, r4, r2
	mov	lr, #1
	sub	r8, r5, #1
	mov	r8, lr, asl r8
	ldr	lr, [fp, #-76]
	mov	r7, r7, asr r4
	str	r0, [fp, #-68]
	add	r2, lr, ip
	ldr	lr, [fp, #-52]
	mov	r0, r10
	add	r10, r8, r1, asl r5
	mov	r1, r3
	str	r10, [r9, #32]
	add	r8, r8, lr, asl r5
	str	r8, [r9, #36]
	mov	r4, r6, asr r4
	str	ip, [fp, #-80]
	str	r3, [fp, #-76]
	str	r4, [fp, #-64]
	mul	r4, r7, r2
	bl	__aeabi_idiv
	ldr	r3, [fp, #-76]
	mov	r2, r6, asl #1
	ldr	lr, [fp, #-52]
	mov	r6, r6, asl #4
	ldr	ip, [fp, #-84]
	mov	r1, r3
	ldr	r3, [fp, #-68]
	rsb	r6, r6, #0
	mul	r2, r7, r2
	mul	r6, r7, r6
	mul	r3, lr, r3
	str	r6, [fp, #-68]
	mov	r6, #1
	mov	lr, r3
	add	r3, r5, #1
	mov	r3, r6, asl r3
	ldr	r6, [fp, #-48]
	add	ip, ip, lr
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-64]
	mul	r2, r6, r2
	str	lr, [fp, #-48]
	mul	r6, r7, ip
	ldr	r7, [fp, #-80]
	ldr	ip, [fp, #-60]
	add	r7, r0, r7
	ldr	r0, [fp, #-72]
	str	r2, [fp, #-72]
	mul	r7, r3, r7
	add	r3, r4, r7
	mla	r3, ip, r2, r3
	ldr	ip, [fp, #-68]
	ldr	r2, [fp, #-76]
	add	r3, r3, ip
	add	r3, r3, r2
	str	r3, [r9, #40]
	str	r3, [fp, #-60]
	bl	__aeabi_idiv
	ldr	r1, [fp, #-104]
	add	ip, r5, #2
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-52]
	str	r7, [r9, #20]
	str	r4, [r9, #16]
	str	r6, [r9, #24]
	add	r0, r0, r1
	ldr	r1, [fp, #-48]
	add	lr, r0, r1
	mul	lr, r2, lr
	ldr	r2, [fp, #-72]
	add	r0, r6, lr
	mla	r2, r3, r2, r0
	ldr	r3, [fp, #-68]
	str	lr, [r9, #28]
	add	r0, r3, r2
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-76]
	add	r0, r2, r0
	str	r0, [r9, #44]
.L36:
	ldr	r2, [fp, #-56]
	cmp	r4, r2, asl r5
	beq	.L46
.L37:
	rsb	r5, r5, #16
	rsb	r1, ip, #16
	mov	r2, r4, asl r5
	mov	r10, r10, asl r5
	mov	r4, r7, asl r5
	mov	r8, r8, asl r5
	mov	r7, r6, asl r5
	mov	r3, r3, asl r1
	mov	r5, lr, asl r5
	mov	r0, r0, asl r1
	str	r10, [r9, #32]
	str	r8, [r9, #36]
	str	r2, [r9, #16]
	str	r4, [r9, #20]
	str	r7, [r9, #24]
	str	r5, [r9, #28]
	str	r3, [r9, #40]
	str	r0, [r9, #44]
.L15:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	ldr	lr, [fp, #-48]
	mov	r1, r6, asl #1
	ldr	r10, [fp, #-60]
	ldr	r0, [fp, #-76]
	rsb	r3, lr, #0
	ldr	r2, [fp, #-64]
	mul	r1, lr, r1
	rsb	r7, ip, r2
	mla	r4, r10, r3, r0
	ldr	r0, [fp, #-52]
	ldr	r2, [fp, #-100]
	ldr	r8, [fp, #-52]
	add	r5, r5, r2
	mov	r2, r6, asl #4
	mla	r6, r0, r3, ip
	add	r3, r7, r4
	mov	ip, #1
	rsb	r2, r2, #0
	mla	r3, r10, r1, r3
	add	lr, r4, r6
	add	r0, r5, #1
	str	r7, [r9, #20]
	mla	r1, r8, r1, lr
	mov	r0, ip, asl r0
	add	r3, r3, r2
	sub	r8, r5, #1
	add	r3, r3, r0
	mov	r8, ip, asl r8
	add	r2, r2, r1
	add	r10, r8, r10, asl r5
	add	r0, r0, r2
	ldr	r2, [fp, #-52]
	str	r4, [r9, #16]
	mov	lr, r4
	str	r6, [r9, #24]
	add	ip, r5, #2
	add	r8, r8, r2, asl r5
	ldr	r2, [fp, #-56]
	str	r4, [r9, #28]
	str	r3, [r9, #40]
	cmp	r4, r2, asl r5
	str	r10, [r9, #32]
	str	r0, [r9, #44]
	str	r8, [r9, #36]
	bne	.L37
.L46:
	cmp	r7, #0
	bne	.L37
	cmp	r6, #0
	bne	.L37
	cmp	r4, lr
	bne	.L37
	b	.L39
.L33:
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-52]
	and	r3, r2, #1
	and	r0, r1, #1
	orr	r3, r3, r2, asr #1
	mov	r10, r2
	orr	r0, r0, r1, asr #1
	mov	r8, r1
	b	.L31
.L45:
	ldr	r2, [fp, #-56]
	add	lr, r0, lr
	str	lr, [fp, #-84]
	ldr	lr, [fp, #-52]
	mla	r10, r8, r2, ip
	str	r0, [fp, #-52]
	mla	r2, r3, r2, r0
	ldr	r0, [fp, #-72]
	add	lr, ip, lr
	add	r1, r1, r10
	str	lr, [fp, #-88]
	add	r2, r0, r2
	str	ip, [fp, #-60]
	str	r2, [fp, #-92]
	b	.L21
.L30:
	mov	ip, #0
	ldr	r4, [r9, #16]
	mov	r5, ip
	ldr	r10, [r9, #32]
	ldr	r8, [r9, #36]
	ldr	r3, [r9, #40]
	ldr	r0, [r9, #44]
	ldr	r7, [r9, #20]
	ldr	r6, [r9, #24]
	ldr	lr, [r9, #28]
	b	.L36
.L40:
	mov	r2, #16
	mov	r6, #1
	str	r2, [fp, #-96]
	mov	r5, #0
	b	.L16
.L41:
	mov	r2, #16
	mov	r7, #1
	str	r2, [fp, #-104]
	mov	r4, #0
	b	.L18
	UNWIND(.fnend)
	.size	MP4_GetGMCparam, .-MP4_GetGMCparam
	.align	2
	.global	Mp4_GetUserDataBuf
	.type	Mp4_GetUserDataBuf, %function
Mp4_GetUserDataBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r1, r2, asl #2]
	cmp	r3, #0
	beq	.L52
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L52:
	str	r2, [fp, #-20]
	str	r1, [fp, #-16]
	bl	GetUsd
	ldr	r2, [fp, #-20]
	ldr	r1, [fp, #-16]
	cmp	r0, #0
	mov	r3, r0
	str	r0, [r1, r2, asl #2]
	addne	r0, r2, #4
	strne	r0, [r3, #1040]
	ldrne	r3, [r1, r2, asl #2]
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_GetUserDataBuf, .-Mp4_GetUserDataBuf
	.align	2
	.global	Mp4_ClearUsrData
	.type	Mp4_ClearUsrData, %function
Mp4_ClearUsrData:
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
	sub	r4, r1, #4
	add	r5, r1, #12
	mov	r7, r0
	mov	r6, #0
.L54:
	ldr	r1, [r4, #4]!
	mov	r0, r7
	bl	FreeUsdByDec
	cmp	r4, r5
	str	r6, [r4]
	bne	.L54
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_ClearUsrData, .-Mp4_ClearUsrData
	.align	2
	.global	Mp4_Syntax_Init
	.type	Mp4_Syntax_Init, %function
Mp4_Syntax_Init:
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
	ldr	r5, .L61
	mov	r4, r0
	add	r0, r0, #19968
	mov	r2, #24
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r5, #48]
	mov	r2, #604
	mov	r1, #0
	add	r0, r0, #40
	blx	r3
	add	r0, r4, #20992
	ldr	r3, [r5, #48]
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #224
	blx	r3
	add	r0, r4, #21248
	ldr	r3, [r5, #48]
	mov	r2, #776
	mov	r1, #0
	add	r0, r0, #28
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #7
	mov	r1, #0
	add	r0, r0, #36
	blx	r3
	add	r2, r4, #19968
	add	r3, r4, #20224
	ldr	r1, .L61+4
	add	r0, r4, #20480
	add	r2, r2, #124
	add	r3, r3, #124
	mov	ip, #1
	strb	ip, [r0, #821]
	str	ip, [r0, #2136]
.L57:
	ldr	ip, [r1, #4]!
	str	ip, [r2, #4]!
	cmp	r2, r3
	bne	.L57
	add	r0, r4, #20480
	ldr	r2, .L61+8
	add	r0, r0, #124
.L58:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L58
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L62:
	.align	2
.L61:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1-4
	.word	.LANCHOR1+252
	UNWIND(.fnend)
	.size	Mp4_Syntax_Init, .-Mp4_Syntax_Init
	.align	2
	.global	Global_Data_Init
	.type	Global_Data_Init, %function
Global_Data_Init:
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
	ldr	r5, .L64
	mov	r4, r0
	add	r0, r0, #22016
	mov	r2, #24
	mov	r1, #0
	add	r0, r0, #64
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #44
	blx	r3
	mov	r0, r4
	bl	Mp4_Syntax_Init
	add	r3, r4, #20480
	mov	r2, #0
	mov	r0, r2
	str	r2, [r3, #2116]
	str	r2, [r3, #2120]
	str	r2, [r3, #2124]
	str	r2, [r3, #2128]
	str	r2, [r3, #2088]
	str	r2, [r3, #1628]
	str	r2, [r3, #2072]
	str	r2, [r3, #2076]
	str	r2, [r3, #2080]
	str	r2, [r3, #2132]
	str	r2, [r3, #2092]
	str	r2, [r3, #2096]
	str	r2, [r3, #2100]
	str	r2, [r3, #2104]
	str	r2, [r3, #2108]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L65:
	.align	2
.L64:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Global_Data_Init, .-Global_Data_Init
	.align	2
	.global	Bs_Get_Matrix
	.type	Bs_Get_Matrix, %function
Bs_Get_Matrix:
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
	mov	r5, #0
	mov	r8, r0
	mov	r6, r1
	mov	r4, r5
	ldr	r7, .L76
	b	.L67
.L71:
	mov	r5, r0
.L67:
	mov	r1, #8
	mov	r0, r8
	bl	BsGet
	add	ip, r4, #1
	sxth	r9, r4
	uxth	r3, ip
	add	r1, r7, r9, lsl #2
	sxth	r2, r3
	uxth	r3, r3
	ldr	r1, [r1, #512]
	mov	r4, r3
	adds	lr, r0, #0
	str	r0, [r6, r1, asl #2]
	movne	lr, #1
	cmp	r2, #63
	movgt	r2, #0
	andle	r2, lr, #1
	cmp	r2, #0
	bne	.L71
	cmp	lr, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r9, #63
	ldmgtfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L70:
	uxth	r4, ip
	str	r5, [r6, r1, asl #2]
	add	ip, r4, #1
	sxth	r3, r4
	cmp	r3, #64
	add	r3, r7, r3, lsl #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r1, [r3, #512]
	b	.L70
.L77:
	.align	2
.L76:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	Bs_Get_Matrix, .-Bs_Get_Matrix
	.align	2
	.global	NextStartCode
	.type	NextStartCode, %function
NextStartCode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	mov	r6, r0
	sub	r0, fp, #60
	mov	r7, r3
	mov	r4, r2, asl #3
	movw	r5, #438
	bl	BsInit
	mov	r0, #0
	b	.L79
.L83:
	cmp	lr, #256
	beq	.L92
.L87:
	bl	BsSkip
	sub	r0, fp, #60
	bl	BsPos
.L79:
	rsb	ip, r0, r4
	mov	r1, #32
	cmp	ip, #31
	sub	r0, fp, #60
	ble	.L93
	bl	BsShow
	mov	r1, #8
	mov	ip, r0
	cmp	ip, r5
	bic	r3, r0, #1020
	bic	r2, r0, #15
	bic	lr, r0, #255
	bic	r3, r3, #3
	sub	r0, fp, #60
	beq	.L82
	cmp	r2, #288
	beq	.L82
	cmp	r3, #32768
	bne	.L83
	ldrb	r3, [r6, #9]	@ zero_extendqisi2
	mov	r1, #8
	sub	r0, fp, #60
	cmp	r3, #2
	bne	.L94
	ldr	r3, [r6, #752]
	add	r3, r3, #1
	str	r3, [r6, #752]
	cmp	r3, #18
	bls	.L87
	mov	r2, #196
	mov	r3, #1
	str	r2, [r7]
	sub	r0, fp, #60
	strb	r3, [r6, #9]
	bl	BsPos
	b	.L81
.L82:
	mov	r2, #2
	mov	r3, #0
	strb	r2, [r6, #9]
	sub	r0, fp, #60
	str	r3, [r6, #752]
	str	ip, [r7]
	bl	BsPos
.L81:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L93:
	mov	r3, #197
	str	r3, [r7]
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L92:
	str	ip, [r7]
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L94:
	mov	r2, #1
	mov	r3, #196
	strb	r2, [r6, #9]
	str	r3, [r7]
	bl	BsPos
	b	.L81
	UNWIND(.fnend)
	.size	NextStartCode, .-NextStartCode
	.align	2
	.global	Mp4SearchStartCode
	.type	Mp4SearchStartCode, %function
Mp4SearchStartCode:
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
	cmp	r1, #4
	ble	.L107
	add	lr, r0, r1
	add	r3, r0, #2
.L112:
	cmp	lr, r3
	bls	.L97
.L113:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L98
	and	ip, r2, #252
	cmp	ip, #128
	beq	.L98
.L105:
	add	r3, r3, #3
	cmp	lr, r3
	bhi	.L113
.L97:
	sub	r0, r1, #2
	ldmfd	sp, {fp, sp, pc}
.L98:
	cmp	r2, #0
	bne	.L100
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L112
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L112
.L100:
	cmp	r2, #1
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	beq	.L114
	cmp	r2, #0
	bne	.L105
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L105
	rsb	r0, r0, r3
	sub	r0, r0, #2
	ldmfd	sp, {fp, sp, pc}
.L114:
	cmp	r2, #0
	bne	.L105
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L105
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
.L107:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4SearchStartCode, .-Mp4SearchStartCode
	.align	2
	.global	Mp4_Syntax_Gop
	.type	Mp4_Syntax_Gop, %function
Mp4_Syntax_Gop:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r4, r0
	sub	r0, fp, #60
	bl	BsInit
	mov	r1, #32
	sub	r0, fp, #60
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #6
	sub	r0, fp, #60
	bl	BsGet
	sub	r0, fp, #60
	mov	r1, #1
	bl	BsGet
	subs	r6, r0, #0
	bne	.L116
	add	r4, r4, #20480
	ldr	r1, .L119
	mov	r0, #1
	bl	dprint_vfmw
	strb	r6, [r4, #1574]
	sub	r0, fp, #60
	bl	BsPos
	ldr	r3, .L119+4
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r5, r0
	beq	.L117
	ldr	r0, [r4, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	ip
	mov	r0, r5
.L117:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L116:
	mov	r1, #6
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	sub	r0, fp, #60
	add	r4, r4, #20480
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #798]
	sub	r0, fp, #60
	bl	BsGet
	mov	r3, #1
	strb	r3, [r4, #1574]
	strb	r0, [r4, #799]
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L120:
	.align	2
.L119:
	.word	.LC0
	.word	g_event_report
	UNWIND(.fnend)
	.size	Mp4_Syntax_Gop, .-Mp4_Syntax_Gop
	.align	2
	.global	Mp4_Syntax_UserData
	.type	Mp4_Syntax_UserData, %function
Mp4_Syntax_UserData:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	cmp	r2, #6
	mov	r3, #0
	mov	r4, r0
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	strb	r3, [fp, #-61]
	ble	.L122
	cmp	r2, #4
	ble	.L123
	mov	r5, r0
	ldrb	r0, [r1, #4]!	@ zero_extendqisi2
	mov	ip, #4
	movw	r7, #1030
	mvn	r3, r0, asl #24
	strb	r0, [r5, #3]!
	mvn	r3, r3, lsr #24
	mov	r0, r5
	mov	r3, r3, asl #8
	b	.L124
.L129:
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	orr	r3, r3, lr
	mov	r3, r3, asl #8
	cmp	r3, #256
	beq	.L183
	cmp	ip, r7
	strb	lr, [r0, #1]!
	beq	.L184
.L124:
	sub	r6, ip, #3
	add	ip, ip, #1
	cmp	ip, r2
	bne	.L129
.L180:
	add	r8, r4, #20480
	cmp	r6, #2
	mov	r3, #1
	mov	r10, r6
	mov	r7, r2, asl #3
	strb	r3, [r8, #1578]
	bhi	.L185
.L161:
	mov	r0, r7
.L179:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L122:
	add	r4, r0, #20480
	add	r7, r2, #1
	strb	r3, [r4, #1578]
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L183:
	sub	ip, ip, #2
	cmp	r2, ip
	bge	.L186
.L128:
	add	r7, r2, #1
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L185:
	add	r1, r4, #22528
	ldr	r2, [r8, #2108]
	add	r1, r1, #68
	ldr	r0, [r8, #2496]
	bl	Mp4_GetUserDataBuf
	ldr	r9, .L190
	cmp	r0, #0
	str	r0, [r8, #2132]
	beq	.L132
	cmn	r6, #-2147483648
	ldr	r3, [r9, #52]
	sub	r6, r6, #2
	str	r6, [r0, #1052]
	movpl	r2, #0
	ldr	r0, [r8, #2132]
	bmi	.L187
.L133:
	mov	r1, r5
	blx	r3
	ldr	r1, .L190+4
	ldr	r2, [r8, #1596]
	ldr	r3, [r8, #2132]
	ldr	ip, [r1]
	ldrd	r0, [r2, #56]
	add	r3, r3, #1056
	cmp	ip, #0
	strd	r0, [r3]
	beq	.L132
	movw	r3, #1064
	ldr	r2, [r8, #2132]
	mov	r1, #6
	ldr	r0, [r8, #2496]
	blx	ip
.L132:
	cmn	r6, #-2147483646
	movpl	r6, #0
	bmi	.L188
.L134:
	add	r6, r4, r6
	mov	r2, #0
	sub	r0, fp, #61
	sub	r3, fp, #56
	strb	r2, [r6, #3]
	sub	r2, fp, #60
	str	r0, [sp]
	mov	r0, r5
	ldr	ip, [r9, #72]
	ldr	r1, .L190+8
	blx	ip
	ldr	r2, .L190
	cmp	r0, #1
	ble	.L189
.L135:
	ldr	r3, [fp, #-56]
	cmp	r0, #3
	ldr	r2, [fp, #-60]
	str	r3, [r8, #1556]
	movne	r3, #0
	ldreqsb	r3, [fp, #-61]
	str	r2, [r8, #1552]
	subeq	r3, r3, #112
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	str	r3, [r8, #1560]
.L136:
	ldr	r3, [r9, #72]
	sub	r2, fp, #56
	ldr	r1, .L190+12
	mov	r0, r5
	blx	r3
	ldr	r4, .L190
	cmp	r0, #1
	beq	.L138
	sub	r3, fp, #56
	sub	r6, fp, #48
	str	r3, [sp, #4]
	sub	r2, fp, #60
	ldr	ip, [r4, #72]
	sub	r3, fp, #52
	str	r6, [sp]
	mov	r0, r5
	ldr	r1, .L190+16
	blx	ip
	cmp	r0, #4
	beq	.L138
	str	r6, [sp]
	sub	r3, fp, #52
	ldr	ip, [r4, #72]
	sub	r2, fp, #60
	ldr	r1, .L190+20
	mov	r0, r5
	blx	ip
	add	r0, r0, #1
	cmp	r0, #1
	ble	.L139
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-48]
	mov	r2, r2, asl #8
	add	r3, r2, r3, lsl #16
	add	r3, r3, r1
	str	r3, [fp, #-56]
.L139:
	cmp	r0, #4
	beq	.L138
	ldr	r3, [r9, #76]
	mov	r2, #7
	ldr	r1, .L190+24
	mov	r0, r5
	blx	r3
	cmp	r0, #0
	movweq	r3, #4600
	streq	r3, [r8, #1568]
.L150:
	sub	r2, fp, #56
	ldr	r3, [r9, #72]
	ldr	r1, .L190+28
	mov	r0, r5
	blx	r3
	mov	r3, #0
	ldr	r1, [r8, #1552]
	strb	r3, [r8, #809]
	strb	r3, [r8, #810]
	strb	r3, [r8, #807]
	strb	r3, [r8, #806]
	strb	r3, [r8, #808]
	cmp	r0, #1
	ldreq	r2, [fp, #-56]
	ldrne	r2, [r8, #1564]
	streq	r2, [r8, #1564]
	cmp	r2, #0
	beq	.L143
	cmp	r1, r3
	strne	r3, [r8, #1552]
	strne	r3, [r8, #1556]
	cmp	r2, #1
	mvnne	r0, #0
	movne	r1, #0
	beq	.L182
.L153:
	movw	r3, #502
	cmp	r1, r3
	bls	.L145
.L152:
	mov	r3, #1
	strb	r3, [r8, #810]
.L145:
	sub	r2, r2, #1
	cmp	r2, #11
	bhi	.L146
.L154:
	mov	r3, #1
	strb	r3, [r8, #807]
.L146:
	ldr	r3, [r8, #1568]
	movw	r2, #4668
	sub	r3, r3, #1
	cmp	r3, r2
	movls	r3, #1
	strlsb	r3, [r8, #807]
	movw	r3, #498
	cmp	r0, r3
	movls	r3, #1
	strlsb	r3, [r8, #807]
	cmp	r1, #500
	bne	.L161
	ldr	r2, [r8, #1556]
	movw	r3, #413
	mov	r0, r7
	cmp	r2, r3
	moveq	r3, #1
	streqb	r3, [r8, #808]
	b	.L179
.L184:
	add	r4, r4, #20480
	mov	r3, #0
	movw	r0, #8224
	strb	r3, [r4, #1578]
	b	.L179
.L138:
	ldr	r3, [fp, #-56]
	str	r3, [r8, #1568]
	b	.L150
.L187:
	cmp	r10, #1024
	movlt	r2, r10
	movge	r2, #1024
	b	.L133
.L143:
	cmp	r1, #500
	subcs	r0, r1, #1
	movcs	r3, #1
	strcsb	r3, [r8, #809]
	bcs	.L153
	movw	r3, #502
	cmp	r1, r3
	sub	r0, r1, #1
	bhi	.L152
	b	.L146
.L188:
	add	r6, r6, #2
	cmp	r6, #1024
	movge	r6, #1024
	b	.L134
.L123:
	cmp	r2, #3
	ble	.L128
	add	r4, r4, #20480
	mov	r3, #1
	mov	r0, #32
	strb	r3, [r4, #1578]
	b	.L179
.L186:
	mov	r2, ip
	b	.L180
.L189:
	sub	r3, fp, #61
	ldr	r1, .L190+32
	str	r3, [sp]
	mov	r0, r5
	ldr	ip, [r2, #72]
	sub	r3, fp, #56
	sub	r2, fp, #60
	blx	ip
	cmp	r0, #1
	ble	.L136
	b	.L135
.L182:
	strb	r2, [r8, #809]
	mvn	r0, #0
	mov	r1, #0
	b	.L154
.L191:
	.align	2
.L190:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC1
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC2
	UNWIND(.fnend)
	.size	Mp4_Syntax_UserData, .-Mp4_Syntax_UserData
	.align	2
	.global	Mp4_Syntax_Vo
	.type	Mp4_Syntax_Vo, %function
Mp4_Syntax_Vo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r4, r0, #20480
	mov	r5, r0
	sub	r0, fp, #60
	mov	r7, r2
	mov	r6, #1
	bl	BsInit
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #820]
	strb	r3, [r4, #822]
	sub	r0, fp, #60
	strb	r3, [r4, #823]
	add	r5, r5, #16384
	strb	r3, [r4, #824]
	strb	r3, [r4, #825]
	strb	r3, [r4, #826]
	strb	r3, [r4, #827]
	str	r3, [r4, #832]
	str	r3, [r4, #836]
	str	r3, [r4, #840]
	strb	r6, [r4, #821]
	bl	BsSkip
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3600]
	cmp	r0, #0
	streqb	r6, [r5, #3601]
	bne	.L207
.L194:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r5, #3603]
	cmp	r6, #1
	beq	.L208
	mov	r6, #0
	sub	r0, fp, #60
	strb	r6, [r4, #1573]
	bl	BsPos
	ldr	r3, .L210
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r5, r0
	beq	.L198
	ldr	r0, [r4, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
	mov	r0, r5
.L198:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L207:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #3
	strb	r0, [r5, #3601]
	sub	r0, fp, #60
	bl	BsGet
	strb	r0, [r5, #3602]
	b	.L194
.L208:
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3604]
	cmp	r0, #0
	bne	.L209
.L197:
	mov	r3, #1
	sub	r0, fp, #60
	strb	r3, [r4, #1573]
	bl	BsPos
	cmp	r0, r7, asl #3
	bgt	.L199
	ldrb	r3, [r5, #3600]	@ zero_extendqisi2
	strb	r3, [r4, #820]
	ldrb	r3, [r5, #3601]	@ zero_extendqisi2
	strb	r3, [r4, #821]
	ldrb	r3, [r5, #3602]	@ zero_extendqisi2
	strb	r3, [r4, #822]
	ldrb	r3, [r5, #3603]	@ zero_extendqisi2
	strb	r3, [r4, #823]
	ldrb	r3, [r5, #3604]	@ zero_extendqisi2
	strb	r3, [r4, #824]
	ldrb	r3, [r5, #3605]	@ zero_extendqisi2
	strb	r3, [r4, #825]
	ldrb	r3, [r5, #3606]	@ zero_extendqisi2
	strb	r3, [r4, #826]
	ldrb	r3, [r5, #3607]	@ zero_extendqisi2
	strb	r3, [r4, #827]
	ldr	r3, [r5, #3612]
	str	r3, [r4, #832]
	ldr	r3, [r5, #3616]
	str	r3, [r4, #836]
	ldr	r3, [r5, #3620]
	str	r3, [r4, #840]
.L199:
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L209:
	mov	r1, #3
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3605]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3606]
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3607]
	cmp	r0, #0
	beq	.L197
	mov	r1, #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3612]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3616]
	sub	r0, fp, #60
	bl	BsGet
	str	r0, [r5, #3620]
	b	.L197
.L211:
	.align	2
.L210:
	.word	g_event_report
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vo, .-Mp4_Syntax_Vo
	.align	2
	.global	Mp4_Syntax_Vol
	.type	Mp4_Syntax_Vol, %function
Mp4_Syntax_Vol:
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
	add	r5, r0, #20480
	mov	r6, r0
	ldr	r3, .L374
	ldr	r0, [r5, #2496]
	add	r7, r6, #19968
	ldr	r8, .L374+4
	add	r7, r7, #40
	add	r4, r6, #16384
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #1228]
	moveq	r9, #8192
	ldrne	r9, [r3, #1232]
	streq	r9, [fp, #-80]
	strne	r0, [fp, #-80]
	sub	r0, fp, #76
	bl	BsInit
	ldr	r3, [r8, #48]
	mov	r2, #604
	mov	r1, #0
	mov	r0, r7
	strb	r1, [r5, #797]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #3628]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3652]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3624]
	cmp	r0, #0
	ldreqb	r3, [r5, #821]	@ zero_extendqisi2
	streqb	r3, [r4, #3625]
	bne	.L363
.L215:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3627]
	cmp	r0, #15
	beq	.L364
.L216:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3629]
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #3630]
	bne	.L365
.L221:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3632]
	cmp	r10, #0
	subne	r0, fp, #76
	movne	r6, #0
	beq	.L366
.L357:
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
	mov	r0, r4
.L327:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L366:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #16
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3696]
	beq	.L229
	subs	r0, r0, #1
	beq	.L229
	mov	r2, r10
	mov	r3, r0
.L231:
	add	r2, r2, #1
	movs	r3, r3, lsr #1
	uxth	r2, r2
	bne	.L231
	sxth	r2, r2
	cmp	r2, #0
	ble	.L229
.L233:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L233
	sxth	r3, r3
.L329:
	str	r3, [r4, #3692]
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3633]
	cmp	r0, #0
	bne	.L367
.L236:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3704]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3708]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	ldr	r3, [r4, #3704]
	cmp	r3, #31
	bls	.L240
	ldr	r2, [r4, #3708]
	cmp	r2, #31
	bls	.L240
	mul	r3, r3, r2
	ldr	r2, [fp, #-80]
	mul	r9, r9, r2
	cmp	r3, r9
	bls	.L241
.L240:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r4, r0
	beq	.L292
.L336:
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	ip
	mov	r0, r4
	b	.L327
.L342:
	ldr	r1, .L374+12
	mov	r0, #1
	str	r3, [fp, #-80]
.L344:
	bl	dprint_vfmw
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r5, #1575]
	bl	BsPos
	ldr	r2, .L374+8
	ldr	ip, [r2]
	cmp	ip, #0
	mov	r4, r0
	beq	.L292
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r5, #2496]
	mov	r2, r3
	blx	ip
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L365:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3630]
	cmp	r10, #1
	beq	.L218
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r5, #1575]
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L363:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #3625]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3626]
	b	.L215
.L218:
	mov	r1, r10
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	strb	r0, [r4, #3631]
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3664]
	beq	.L221
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3668]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3672]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3676]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #11
	str	r0, [r4, #3680]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3684]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3688]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	str	r3, [fp, #-84]
	bne	.L221
	ldr	r1, .L374+12
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r6, [fp, #-84]
	sub	r0, fp, #76
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r4, r0
	bne	.L336
.L292:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L364:
	mov	r1, #8
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #3656]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3660]
	b	.L216
.L229:
	mov	r3, #1
	b	.L329
.L359:
	str	r3, [fp, #-80]
	mov	r0, r10
	ldr	r1, .L374+12
	b	.L344
.L367:
	ldr	r1, [r4, #3692]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3700]
	b	.L236
.L241:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3634]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #3635]
	cmp	r3, #0
	bne	.L243
	ldr	r2, .L374+8
	strb	r3, [r5, #1575]
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L243
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r5, #2496]
	blx	ip
.L243:
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	sub	r0, fp, #76
	cmp	r3, #1
	moveq	r1, #1
	movne	r1, #2
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3636]
	cmp	r9, #0
	beq	.L246
	ldr	r3, .L374+16
	ldr	r10, [r3]
	ands	r10, r10, #8
	beq	.L368
	sub	r3, r9, #1
	cmp	r3, #1
	bls	.L369
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r4, r0
	beq	.L253
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
.L253:
	ldr	r1, .L374+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L370:
	mov	r1, #6
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r9
	strb	r0, [r4, #3648]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3649]
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r4, #3636]	@ zero_extendqisi2
	cmp	r3, #2
	strb	r0, [r4, #3650]
	bne	.L361
.L246:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3637]
	cmp	r0, #0
	beq	.L254
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r4, r0
	beq	.L255
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
.L255:
	ldr	r1, .L374+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L369:
	cmp	r9, #2
	beq	.L370
.L361:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, r6
	mov	r4, r0
	beq	.L252
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
.L252:
	ldr	r1, .L374+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L254:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3638]
	cmp	r0, #0
	bne	.L371
.L257:
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r4, #3641]
	beq	.L264
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3641]
.L264:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3642]
	cmp	r9, #0
	ldreq	r1, .L374+32
	beq	.L353
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3643]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3644]
	cmp	r10, #0
	ldrne	r1, .L374+36
	bne	.L355
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L267
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3645]
	cmp	r9, #0
	beq	.L268
	ldr	r1, .L374+40
	mov	r0, #1
	bl	dprint_vfmw
	strb	r10, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	ip
	mov	r0, r4
	b	.L327
.L368:
	strb	r10, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r4, r0
	beq	.L248
	ldr	r0, [r5, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	ip
.L248:
	ldr	r1, .L374+44
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L371:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3639]
	cmp	r0, #0
	bne	.L372
	add	r3, r6, #19968
	add	r1, r6, #20224
	ldr	r2, .L374+48
	add	r3, r3, #124
	add	r1, r1, #124
.L260:
	ldr	r0, [r2, #4]!
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L260
.L259:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3640]
	cmp	r0, #0
	bne	.L272
	add	r3, r6, #20224
	add	r1, r6, #20480
	ldr	r2, .L374+52
	add	r3, r3, #124
	add	r1, r1, #124
.L261:
	ldr	r0, [r2, #4]!
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L261
	b	.L257
.L373:
	ldr	r1, .L374+56
.L353:
	mov	r0, #1
	bl	dprint_vfmw
	strb	r9, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #102
	blx	ip
	mov	r0, r4
	b	.L327
.L268:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3646]
	cmp	r0, #0
	bne	.L373
.L269:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3647]
	cmp	r0, #0
	beq	.L270
	ldr	r1, .L374+60
.L355:
	mov	r0, #1
	mov	r6, #0
	bl	dprint_vfmw
	sub	r0, fp, #76
	b	.L357
.L372:
	add	r1, r6, #19968
	sub	r0, fp, #76
	add	r1, r1, #128
	bl	Bs_Get_Matrix
	b	.L259
.L272:
	add	r1, r6, #20224
	sub	r0, fp, #76
	add	r1, r1, #128
	bl	Bs_Get_Matrix
	b	.L257
.L267:
	strb	r10, [r4, #3645]
	strb	r10, [r4, #3646]
	b	.L269
.L270:
	add	r0, r6, #20480
	mov	r3, #1
	ldr	ip, [r8, #52]
	mov	r1, r7
	mov	r2, #604
	strb	r3, [r5, #1575]
	strb	r3, [r5, #797]
	add	r0, r0, #132
	strb	r3, [r5, #1576]
	blx	ip
	sub	r0, fp, #76
	bl	BsPos
	b	.L327
.L375:
	.align	2
.L374:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC8
	.word	g_VdmCharacter
	.word	.LC11
	.word	.LC12
	.word	.LC10
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC9
	.word	.LANCHOR1-4
	.word	.LANCHOR1+252
	.word	.LC16
	.word	.LC17
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vol, .-Mp4_Syntax_Vol
	.align	2
	.global	Mp4_Syntax_Vos
	.type	Mp4_Syntax_Vos, %function
Mp4_Syntax_Vos:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r5, r0, #20480
	add	r4, r0, #16384
	sub	r0, fp, #52
	bl	BsInit
	mov	r3, #0
	mov	r1, #32
	str	r3, [r5, #828]
	sub	r0, fp, #52
	bl	BsSkip
	sub	r0, fp, #52
	mov	r1, #8
	bl	BsGet
	sub	r3, r0, #1
	sub	r2, r0, #240
	cmp	r2, #5
	cmphi	r3, #2
	str	r0, [r4, #3608]
	movls	r3, #1
	movhi	r3, #0
	cmp	r0, #8
	orreq	r3, r3, #1
	cmp	r3, #0
	strne	r0, [r5, #828]
	movne	r3, #1
	strneb	r3, [r5, #1572]
	bne	.L378
	cmp	r0, #0
	beq	.L383
	ldr	r2, .L384
	strb	r3, [r5, #1572]
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L378
	ldr	r0, [r5, #2496]
	mov	r2, r3
	mov	r1, #102
	blx	ip
.L378:
	sub	r0, fp, #52
	bl	BsPos
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L383:
	mov	r2, r0
	ldr	r1, .L384+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #1
	strb	r3, [r5, #1572]
	ldr	r3, [r4, #3608]
	str	r3, [r5, #828]
	b	.L378
.L385:
	.align	2
.L384:
	.word	g_event_report
	.word	.LC18
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vos, .-Mp4_Syntax_Vos
	.align	2
	.global	Frame_Init
	.type	Frame_Init, %function
Frame_Init:
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r5, r2
	sub	r2, r1, #32
	sub	r3, r5, #32
	cmp	r3, #2128
	cmpcc	r2, #3808
	mov	r4, r1
	mov	r7, r0
	bcs	.L425
	add	r6, r0, #20480
	ldr	r3, [r6, #1596]
	ldr	r8, [r3, #724]
	ldr	r2, [r3, #28]
	cmp	r8, #0
	bne	.L389
	cmp	r2, #25
	beq	.L426
.L416:
	mov	r9, #5
	mov	r10, #3
	mov	r2, #2
	str	r2, [fp, #-72]
.L390:
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L401
	ldr	r2, .L429
	ldr	ip, [r2, #64]
	cmp	ip, #0
	beq	.L403
	ldr	r1, [r3, #20]
	mov	lr, #0
	ldr	r0, [r3, #16]
	mov	r2, #40
	ldr	r3, [r6, #2496]
	ldr	r8, .L429+4
	str	lr, [sp, #8]
	mov	lr, #2
	str	r3, [sp, #12]
	mov	r3, r5
	str	r2, [sp, #4]
	mov	r2, r4
	str	r8, [sp, #16]
	str	lr, [sp]
	blx	ip
	cmp	r0, #0
	bne	.L403
	ldr	r2, [r8, #56]
	ldr	r3, [r8, #48]
	cmp	r2, #1
	ble	.L405
	cmp	r3, #2
	ble	.L405
	ldr	r0, [r8, #464]
	str	r0, [r6, #1616]
	bl	MEM_Phy2Vir
	str	r0, [r6, #1604]
.L401:
	ldr	r3, .L429+8
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, #1596]
	str	r4, [fp, #-60]
	str	r5, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r4, [fp, #-52]
	cmp	r3, #24
	str	r5, [fp, #-48]
	beq	.L407
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	strb	r10, [fp, #-63]
	strb	r9, [fp, #-62]
.L412:
	sub	r1, fp, #64
	ldr	r0, [r6, #2496]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L408
	ldr	r1, [r6, #1596]
	sub	r3, fp, #68
	ldr	r0, [r6, #2496]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L427
	cmp	r0, #0
	moveq	r3, #1
	streq	r3, [r6, #2500]
	bne	.L410
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L425:
	mov	r3, r5
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L429+12
	bl	dprint_vfmw
	ldr	r3, .L429+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L423
	add	r7, r7, #20480
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r7, #2496]
	mvn	r8, #0
	blx	ip
.L419:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L397:
	mov	r3, r5
	str	r1, [sp, #4]
	str	r2, [sp]
.L422:
	mov	r2, r4
	ldr	r1, .L429+20
	mov	r0, #0
	bl	dprint_vfmw
.L423:
	mvn	r8, #0
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L389:
	cmp	r2, #25
	bne	.L416
	ldr	r2, [r3, #684]
	ldr	r1, [r3, #688]
	cmp	r4, r2
	bhi	.L397
	cmp	r5, r1
	bhi	.L397
	ldr	r1, [r3, #712]
	ldr	r2, [r3, #708]
	cmp	r1, #0
	add	r10, r2, #2
	moveq	r2, #1
	streq	r2, [fp, #-72]
	bne	.L428
.L399:
	ldr	r9, [r3, #732]
	b	.L390
.L407:
	mov	r3, #1
	strb	r9, [fp, #-62]
	strb	r3, [fp, #-63]
	b	.L412
.L428:
	add	r2, r2, #1
	cmp	r2, #17
	movge	r2, #17
	str	r2, [fp, #-72]
	b	.L399
.L426:
	ldr	r0, [r3, #684]
	cmp	r1, r0
	ldrhi	r1, [r3, #688]
	bhi	.L392
	ldr	r2, [r3, #688]
	cmp	r5, r2
	mov	r1, r2
	bhi	.L392
	ldr	r1, [r6, #2500]
	cmp	r1, #1
	beq	.L419
	ldr	ip, [r3, #712]
	ldr	r1, [r3, #708]
	cmp	ip, #0
	add	r10, r1, #2
	moveq	r1, #1
	streq	r1, [fp, #-72]
	beq	.L395
	add	r1, r1, #1
	cmp	r1, #17
	movge	r1, #17
	str	r1, [fp, #-72]
.L395:
	mov	r5, r2
	mov	r4, r0
	ldr	r9, [r3, #732]
	b	.L390
.L427:
	add	r0, r7, #22528
	add	r0, r0, #96
	bl	ResetVoQueue
.L410:
	ldr	r1, .L429+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	mov	r3, #0
	str	r3, [r6, #2500]
	b	.L419
.L405:
	ldr	r1, .L429+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L403:
	ldr	r1, .L429+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L408:
	ldr	r1, .L429+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L392:
	str	r1, [sp, #4]
	mov	r3, r5
	str	r0, [sp]
	b	.L422
.L430:
	.align	2
.L429:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	g_event_report
	.word	.LC20
	.word	.LC23
	.word	.LC22
	.word	.LC21
	.word	.LC24
	UNWIND(.fnend)
	.size	Frame_Init, .-Frame_Init
	.align	2
	.global	Mp4_RecordVFMWState
	.type	Mp4_RecordVFMWState, %function
Mp4_RecordVFMWState:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_RecordVFMWState, .-Mp4_RecordVFMWState
	.global	__aeabi_uidiv
	.align	2
	.global	Mp4_RecordFrameAtr
	.type	Mp4_RecordFrameAtr, %function
Mp4_RecordFrameAtr:
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
	add	r5, r0, #20480
	mov	r6, r0
	mov	r4, r1
	ldrb	r3, [r5, #847]	@ zero_extendqisi2
	cmp	r3, #15
	beq	.L452
	sub	r2, r3, #2
	cmp	r2, #1
	movls	r7, #1
	bls	.L434
	sub	r2, r3, #4
	cmp	r2, #1
	movls	r7, #2
	bls	.L434
	cmp	r3, #1
	moveq	r7, #5
	movne	r7, #0
.L434:
	mov	r1, r4
	ldr	r0, [r5, #2496]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L432
	ldr	r3, [r5, #1512]
	mov	r1, r7
	str	r3, [r4, #68]
	ldr	r3, [r5, #1508]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L453
.L440:
	ldr	r3, [r5, #1512]
	add	r6, r6, #22528
	ldrb	lr, [r4, #64]	@ zero_extendqisi2
	mov	ip, #0
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	add	r6, r6, #64
	str	r3, [r4, #76]
	add	r0, r4, #568
	ldr	r8, [r5, #1508]
	add	r3, r4, #536
	mov	r1, ip
	str	r8, [r4, #80]
	ldr	r8, [r5, #1512]
	mov	r8, r8, lsr #1
	str	r8, [r4, #84]
	ldr	r8, [r5, #1508]
	mov	r8, r8, lsr #1
	str	r8, [r4, #88]
	ldr	r8, [r5, #2076]
	str	r8, [r4, #160]
	ldr	r8, [r5, #2072]
	str	r8, [r4, #156]
	ldrb	r8, [r5, #1448]	@ zero_extendqisi2
	bfi	lr, r8, #0, #2
	strb	lr, [r4, #64]
	ldrb	r8, [r5, #825]	@ zero_extendqisi2
	bfi	lr, r8, #5, #3
	strb	lr, [r4, #64]
	ldrb	lr, [r5, #854]	@ zero_extendqisi2
	and	lr, lr, #1
	bfi	r2, lr, #0, #2
	uxtb	r2, r2
	orr	r2, r2, #12
	strb	r2, [r4, #65]
	ldrb	lr, [r5, #1453]	@ zero_extendqisi2
	bfi	r2, lr, #4, #2
	strb	r2, [r4, #65]
	ldr	r2, [r4, #64]
	bfi	r2, r7, #14, #3
	str	r2, [r4, #64]
	ldrb	lr, [r5, #812]	@ zero_extendqisi2
	mov	r2, r2, lsr #16
	bfi	r2, lr, #1, #1
	strb	r2, [r4, #66]
	ldr	r2, [r5, #816]
	str	r2, [r4, #120]
	ldrb	r2, [r5, #1448]	@ zero_extendqisi2
	and	r2, r2, #3
	str	r2, [r4, #56]
	ldrb	r2, [r5, #1448]	@ zero_extendqisi2
	str	ip, [r4, #52]
	and	r2, r2, #3
	str	r2, [r4, #60]
.L441:
	ldr	r2, [r6, #4]!
	mov	r8, #0
	str	r2, [r3, #8]!
	cmp	r3, r0
	str	r1, [r3, #4]
	bne	.L441
	ldr	r3, [r5, #1596]
	add	ip, r4, #592
	add	lr, r4, #608
	mvn	r6, #0
	mvn	r7, #0
	ldr	r1, .L454
	ldrd	r2, [r3, #56]
	mov	r0, #29
	strd	r2, [ip, #-8]
	ldr	r3, [r5, #1596]
	ldrd	r2, [r3, #72]
	strd	r2, [ip]
	ldr	r3, [r5, #1596]
	ldrd	r2, [r3, #88]
	strd	r2, [lr, #-8]
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #104]
	str	r3, [r4]
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #108]
	str	r3, [r4, #4]
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #112]
	str	r3, [r4, #8]
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #128]
	str	r3, [r4, #12]
	ldr	r3, [r5, #1596]
	strd	r6, [r3, #56]
	ldrd	r6, [ip]
	ldrd	r2, [ip, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	mov	r3, #8
	mov	r2, #2
	strb	r8, [r4, #284]
	str	r2, [r4, #296]
	mov	r2, #1
	strb	r8, [r4, #291]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	r2, [r4, #289]
.L432:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L453:
	ldr	r3, [r4, #72]
	add	r8, r4, #512
	ldr	r2, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	mov	r1, r2, asl #4
	mov	r3, r3, lsr #4
	add	r9, ip, r2
	mul	r3, r3, r1
	add	lr, r3, ip
	str	lr, [r4, #40]
	ldrd	r0, [r8, #-8]
	add	r2, lr, r2
	adds	r0, r0, r3
	adc	r1, r1, r3, asr #31
	strd	r0, [r8]
	str	lr, [r4, #24]
	str	r2, [r4, #32]
	str	r9, [r4, #28]
	str	ip, [r4, #20]
	b	.L440
.L452:
	ldr	r2, [r5, #876]
	ldr	r1, [r5, #880]
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r7, #0
	beq	.L434
	ldr	r3, [r5, #928]
	mul	r1, r3, r1
	cmp	r1, #0
	beq	.L443
	ldr	r0, [r5, #924]
	mov	r2, r2, asl #10
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	movw	r3, #1364
	cmp	r0, r3
	movw	r3, #1819
	rsble	r7, r0, #1360
	subgt	r7, r0, #1360
	addle	r7, r7, #5
	subgt	r7, r7, #5
	cmp	r0, r3
	rsble	r0, r0, #1808
	subgt	r0, r0, #1808
	addle	r0, r0, #12
	subgt	r0, r0, #12
	cmp	r7, r0
	movlt	r7, #1
	movge	r7, #2
	b	.L434
.L443:
	mov	r7, r1
	b	.L434
.L455:
	.align	2
.L454:
	.word	.LC25
	UNWIND(.fnend)
	.size	Mp4_RecordFrameAtr, .-Mp4_RecordFrameAtr
	.align	2
	.global	Mp4_Frame_Atr
	.type	Mp4_Frame_Atr, %function
Mp4_Frame_Atr:
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
	add	r4, r0, #20480
	mov	r5, r0
	mov	r1, #1
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #4
	strb	r3, [r0, #2]
	ldreq	r2, .L466
	moveq	r3, #300
	ldr	r0, [r4, #2496]
	mlaeq	r3, r3, r0, r2
	ldreq	r2, [r3, #12]
	addeq	r2, r2, #1
	streq	r2, [r3, #12]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #2524]
	blt	.L459
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	beq	.L459
	mov	r1, r0
	mov	r0, r5
	bl	Mp4_RecordFrameAtr
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2080]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L459:
	ldr	r1, .L466+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L461
	ldr	r1, [r6, #544]
	add	r7, r6, #560
	ldr	r0, [r4, #2496]
	add	r8, r6, #576
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r4, #2496]
	add	r9, r6, #544
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L461:
	add	r1, r5, #22528
	mov	r3, #0
	add	r1, r1, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L467:
	.align	2
.L466:
	.word	g_VfmwChanStat
	.word	.LC26
	UNWIND(.fnend)
	.size	Mp4_Frame_Atr, .-Mp4_Frame_Atr
	.align	2
	.global	Mp4_Set_DecPar
	.type	Mp4_Set_DecPar, %function
Mp4_Set_DecPar:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	r3, .L489
	mov	r6, r2
	mov	r4, r0
	mov	r2, #48
	sub	r0, fp, #92
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldrb	r3, [r6, #6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L486
	ldr	r3, [r6, #92]
	add	r5, r4, #20480
	mov	r1, #0
	bic	r3, r3, #3
	str	r3, [r4, #1208]
	ldr	r3, [r5, #1584]
	and	r2, r3, #3
	str	r3, [r4, #1220]
	ldr	r3, [r5, #1580]
	str	r3, [r4, #1056]
	ldr	r3, [r5, #1592]
	add	r2, r3, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1588]
	rsb	r3, r3, r2, lsl #3
	str	r3, [r4, #1236]
	ldr	r3, [r6, #92]
	str	r3, [r4, #1224]
	ldr	r3, [r6, #80]
	str	r3, [r4, #1060]
	ldr	r3, [r6, #92]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #1232]
	ldr	r3, [r6, #96]
	str	r1, [r4, #1216]
	mov	r3, r3, asl #3
	str	r3, [r4, #1240]
.L470:
	ldr	r2, [r5, #1512]
	add	r7, r4, #1040
	add	r6, r4, #12288
	add	r3, r2, #15
	mov	r3, r3, lsr #4
	strh	r3, [r7, #164]	@ movhi
	ldr	r1, [r5, #1508]
	add	r3, r1, #15
	mov	r3, r3, lsr #4
	strh	r3, [r7, #166]	@ movhi
	ldrb	r3, [r5, #1448]	@ zero_extendqisi2
	strb	r3, [r4, #1040]
	ldrb	r0, [r5, #858]	@ zero_extendqisi2
	strb	r0, [r4, #1041]
	ldrb	r0, [r5, #805]	@ zero_extendqisi2
	strb	r0, [r4, #1042]
	ldrb	r0, [r5, #1455]	@ zero_extendqisi2
	strb	r0, [r4, #1043]
	ldrb	r0, [r5, #1460]	@ zero_extendqisi2
	strb	r0, [r4, #1044]
	ldrb	r0, [r5, #1459]	@ zero_extendqisi2
	strb	r0, [r4, #1045]
	ldr	r0, [r5, #912]
	strb	r0, [r4, #1046]
	ldrb	r0, [r5, #1456]	@ zero_extendqisi2
	strb	r0, [r4, #1047]
	ldrb	r0, [r5, #1457]	@ zero_extendqisi2
	strb	r0, [r4, #1048]
	ldrb	r0, [r5, #1452]	@ zero_extendqisi2
	strb	r0, [r4, #1049]
	ldrb	r0, [r5, #863]	@ zero_extendqisi2
	strb	r0, [r4, #1050]
	ldrb	r0, [r5, #861]	@ zero_extendqisi2
	strb	r0, [r4, #1051]
	ldrb	r0, [r5, #1450]	@ zero_extendqisi2
	strb	r0, [r4, #1052]
	ldrb	r0, [r5, #1454]	@ zero_extendqisi2
	strb	r0, [r4, #1053]
	ldrb	r0, [r5, #1453]	@ zero_extendqisi2
	strb	r0, [r4, #1054]
	ldrb	r0, [r5, #854]	@ zero_extendqisi2
	strb	r0, [r4, #1055]
	ldr	r0, [r5, #1544]
	str	r0, [r4, #1244]
	ldr	r0, [r5, #1540]
	str	r0, [r4, #1248]
	ldrb	r0, [r5, #808]	@ zero_extendqisi2
	strb	r0, [r4, #1194]
	ldrb	r0, [r5, #807]	@ zero_extendqisi2
	strb	r0, [r4, #1193]
	ldrb	r0, [r5, #806]	@ zero_extendqisi2
	strb	r0, [r4, #1192]
	ldrb	r0, [r5, #809]	@ zero_extendqisi2
	strb	r0, [r4, #1195]
	ldrb	r0, [r5, #810]	@ zero_extendqisi2
	strb	r0, [r4, #1196]
	ldrb	r0, [r5, #811]	@ zero_extendqisi2
	strb	r0, [r4, #1197]
	str	r1, [r6, #3360]
	str	r2, [r6, #3364]
	ldrb	r2, [r5, #856]	@ zero_extendqisi2
	cmp	r2, #2
	cmpeq	r3, #3
	str	r2, [r6, #3368]
	moveq	r3, #1
	movne	r3, #0
	beq	.L487
	ldrb	r2, [r5, #869]	@ zero_extendqisi2
	str	r3, [r6, #3372]
	str	r3, [r6, #3380]
	str	r2, [r6, #3376]
	str	r3, [r6, #3384]
	str	r3, [r6, #3388]
	str	r3, [r6, #3392]
	str	r3, [r6, #3396]
	str	r3, [r6, #3400]
	str	r3, [r6, #3404]
	str	r3, [r6, #3408]
.L472:
	ldr	r1, [r5, #2524]
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #2508]
	mov	r8, r0
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #2516]
	mov	r9, r0
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	cmp	r8, #0
	cmpne	r9, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L488
	ldr	ip, [r8, #28]
	ldr	r1, [r8, #32]
	cmp	ip, #0
	beq	.L476
	cmp	r1, #0
	beq	.L476
	ldr	r3, [r8, #8]
	add	lr, r4, #21248
	add	ip, r4, #1056
	add	r1, r4, #21504
	add	r2, r4, #1120
	add	lr, lr, #160
	str	r3, [r4, #1268]
	add	ip, ip, #7
	ldr	r3, [r0, #8]
	add	r1, r1, #160
	add	r2, r2, #7
	str	r3, [r4, #1272]
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ldreq	r3, [r8, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1264]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ldreq	r3, [r8, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1260]
	ldr	r3, [r8, #28]
	ldr	r0, [r3, #8]
	mov	r3, #0
	str	r0, [r4, #1252]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #8]
	str	r0, [r6, #3328]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #24]
	str	r0, [r6, #3340]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #28]
	str	r0, [r6, #3344]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #60]
	str	r0, [r6, #3348]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #44]
	str	r0, [r6, #3352]
	ldr	r0, [r8, #32]
	ldr	r0, [r0, #48]
	str	r0, [r6, #3356]
.L482:
	ldr	r0, [lr, #4]!
	add	r3, r3, #1
	cmp	r3, #64
	strb	r0, [ip, #1]!
	ldr	r0, [r1, #4]!
	strb	r0, [r2, #1]!
	bne	.L482
	ldrh	r1, [r7, #164]
	ldrh	r3, [r7, #166]
	ldr	r2, [r5, #1596]
	mul	r3, r3, r1
	str	r3, [r5, #1480]
	ldr	r3, [r2, #592]
	str	r3, [r6, #3412]
	ldr	r3, [r2, #644]
	str	r3, [r6, #3416]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L488:
	movw	r3, #3353
	ldr	r2, .L489+4
	ldr	r1, .L489+8
	mov	r0, #0
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L486:
	add	r5, r4, #20480
	mov	r0, #0
	ldr	r2, [r5, #1584]
	bic	r1, r2, #3
	str	r1, [r4, #1220]
	str	r2, [r4, #1208]
	and	r2, r2, #3
	ldr	r1, [r5, #1580]
	str	r1, [r4, #1056]
	ldr	r1, [r5, #1592]
	add	r2, r1, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1588]
	str	r3, [r4, #1216]
	str	r0, [r4, #1224]
	rsb	r1, r1, r2, lsl #3
	str	r0, [r4, #1232]
	str	r1, [r4, #1236]
	str	r0, [r4, #1240]
	b	.L470
.L476:
	ldr	lr, [r5, #2516]
	mov	r0, #0
	ldr	r3, [r5, #2524]
	ldr	r2, [r5, #2508]
	str	r1, [sp, #8]
	str	ip, [sp, #4]
	str	lr, [sp]
	ldr	r1, .L489+12
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L487:
	add	r0, r4, #21248
	sub	r1, fp, #92
	add	r0, r0, #28
	bl	MP4_GetGMCparam
	sub	r0, fp, #64
	ldrb	r10, [r5, #869]	@ zero_extendqisi2
	ldmia	r0, {r0, r1, r2, r3}
	ldr	r9, [fp, #-92]
	ldr	r8, [fp, #-76]
	ldr	lr, [fp, #-72]
	ldr	ip, [fp, #-68]
	str	r3, [r6, #3404]
	ldr	r3, [fp, #-48]
	str	r10, [r6, #3376]
	str	r9, [r6, #3372]
	str	r8, [r6, #3380]
	str	lr, [r6, #3384]
	str	ip, [r6, #3388]
	str	r0, [r6, #3392]
	str	r1, [r6, #3396]
	str	r2, [r6, #3400]
	str	r3, [r6, #3408]
	b	.L472
.L490:
	.align	2
.L489:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1280
	.word	.LC27
	.word	.LC28
	UNWIND(.fnend)
	.size	Mp4_Set_DecPar, .-Mp4_Set_DecPar
	.align	2
	.global	Mp4_Get_DecMode
	.type	Mp4_Get_DecMode, %function
Mp4_Get_DecMode:
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
	add	r0, r0, #20480
	ldr	r3, [r0, #1628]
	cmp	r3, #2
	ldr	r3, [r0, #1596]
	beq	.L503
.L493:
	ldr	r3, [r3, #8]
	cmp	r3, #2
	beq	.L496
	cmp	r3, #1
	beq	.L502
	cmp	r3, #4
	movne	r3, #0
.L502:
	str	r3, [r0, #1628]
	ldmfd	sp, {fp, sp, pc}
.L503:
	ldr	r2, [r3, #8]
	cmp	r2, #2
	movne	r2, #1
	strne	r2, [r0, #2136]
	bne	.L493
.L496:
	mov	r3, #2
	str	r3, [r0, #1628]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_Get_DecMode, .-Mp4_Get_DecMode
	.align	2
	.global	GetTrailingOneLen
	.type	GetTrailingOneLen, %function
GetTrailingOneLen:
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
	add	r1, r0, r1
	ldrb	r3, [r1, #-1]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L507
	mov	r0, #0
.L506:
	mov	r3, r3, lsr #1
	add	r0, r0, #1
	tst	r3, #1
	bne	.L506
	cmp	r0, #0
	addne	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L507:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetTrailingOneLen, .-GetTrailingOneLen
	.align	2
	.global	MPEG4DEC_Init
	.type	MPEG4DEC_Init, %function
MPEG4DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 784
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #788)
	sub	sp, sp, #788
	mov	r4, r0
	mov	r6, r1
	mov	r0, #2
	ldr	r1, .L523
	bl	dprint_vfmw
	cmp	r6, #0
	cmpne	r4, #0
	beq	.L517
	ldr	r3, [r6, #616]
	ldr	r7, .L523+4
	cmp	r3, #1
	beq	.L520
.L515:
	add	r5, r4, #20480
	ldr	r3, [r7, #48]
	movw	r2, #23024
	mov	r1, #0
	ldr	r8, [r5, #2488]
	mov	r0, r4
	blx	r3
	add	r0, r4, #22528
	add	r0, r0, #96
	mov	r7, #0
	str	r8, [r5, #2488]
	bl	ResetVoQueue
	str	r6, [r5, #1596]
	mov	r0, r4
	str	r7, [r6, #888]
	bl	VCTRL_GetChanIDByCtx
	ldr	r8, .L523+4
	cmn	r0, #1
	str	r0, [r5, #2496]
	beq	.L521
	mov	r0, r4
	bl	Global_Data_Init
	subs	r7, r0, #0
	bne	.L517
	mov	r3, #1
	str	r7, [r5, #2112]
	ldr	r1, .L523+8
	mov	r0, #2
	str	r3, [r5, #2084]
	bl	dprint_vfmw
	ldr	r6, [r6, #616]
	cmp	r6, #1
	beq	.L522
.L514:
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L522:
	add	r0, r4, #21248
	ldr	r3, [r8, #52]
	sub	r1, fp, #812
	mov	r2, #776
	add	r0, r0, #28
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #788
	mov	r2, #24
	add	r0, r0, #16
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #764
	mov	r2, #604
	add	r0, r0, #40
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r8, #52]
	mov	r2, #7
	sub	r1, fp, #820
	add	r0, r0, #36
	blx	r3
	mov	r0, r7
	strb	r6, [r5, #2533]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L520:
	add	r1, r4, #21248
	ldr	r3, [r7, #52]
	add	r1, r1, #28
	mov	r2, #776
	sub	r0, fp, #812
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #16
	mov	r2, #24
	sub	r0, fp, #788
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #40
	mov	r2, #604
	sub	r0, fp, #764
	blx	r3
	add	r1, r4, #22016
	ldr	r3, [r7, #52]
	add	r1, r1, #36
	mov	r2, #7
	sub	r0, fp, #820
	blx	r3
	b	.L515
.L517:
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L521:
	mov	r0, r7
	ldr	r1, .L523+12
	bl	dprint_vfmw
	mvn	r7, #19
	b	.L514
.L524:
	.align	2
.L523:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_Init, .-MPEG4DEC_Init
	.align	2
	.global	MPEG4DEC_Destroy
	.type	MPEG4DEC_Destroy, %function
MPEG4DEC_Destroy:
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
	add	r4, r4, #20480
	ldr	r1, .L526
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #2084]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L527:
	.align	2
.L526:
	.word	.LC32
	UNWIND(.fnend)
	.size	MPEG4DEC_Destroy, .-MPEG4DEC_Destroy
	.align	2
	.global	MPEG4DEC_RecycleImage
	.type	MPEG4DEC_RecycleImage, %function
MPEG4DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	beq	.L530
	add	r4, r0, #20480
	mov	r2, #0
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L531
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #2496]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #2496]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L531:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L530:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG4DEC_RecycleImage, .-MPEG4DEC_RecycleImage
	.align	2
	.global	MP4_SetImgFormat
	.type	MP4_SetImgFormat, %function
MP4_SetImgFormat:
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
	add	r4, r0, #20480
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r4, #1512]
	cmp	r2, #0
	beq	.L534
	ldr	r1, [r4, #1508]
	cmp	r1, #0
	beq	.L534
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #72]
	cmp	r0, r2
	movcs	r0, r2
	str	r0, [r3, #76]
	ldr	r2, [r4, #1508]
	cmp	r1, r2
	movcs	r1, r2
	str	r1, [r3, #80]
	b	.L535
.L534:
	ldr	r1, [r3, #68]
	ldr	r2, [r3, #72]
	str	r1, [r3, #76]
	str	r2, [r3, #80]
.L535:
	ldrb	r5, [r4, #812]	@ zero_extendqisi2
	mov	r2, #8
	ldrb	r0, [r3, #66]	@ zero_extendqisi2
	mov	r1, #0
	mov	lr, #2
	mov	ip, #1
	bfi	r0, r5, #1, #1
	strb	r0, [r3, #66]
	ldr	r0, [r4, #816]
	str	lr, [r3, #296]
	strb	r1, [r3, #284]
	str	r0, [r3, #120]
	strb	r1, [r3, #291]
	str	r2, [r3, #300]
	str	r2, [r3, #308]
	str	r2, [r3, #304]
	strb	ip, [r3, #289]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_SetImgFormat, .-MP4_SetImgFormat
	.align	2
	.global	MPEG4DEC_GetRemainImg
	.type	MPEG4DEC_GetRemainImg, %function
MPEG4DEC_GetRemainImg:
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
	add	r4, r0, #20480
	mov	r6, r0
	ldr	r3, [r4, #1596]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L560
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L560
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetDisplay
	cmp	r0, #2
	mov	r8, r0
	beq	.L559
.L560:
	add	r5, r6, #22528
	add	r5, r5, #96
.L550:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	GetVoLastImageID
.L559:
	mov	r0, r6
	add	r5, r6, #22528
	bl	MP4_SetImgFormat
	add	r5, r5, #96
	mov	r3, #1
	ldr	r1, [r7, #148]
	mov	r2, r3
	str	r3, [r7, #180]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #2496]
	mov	r1, r8
	str	r7, [sp]
	mov	r3, r5
	mov	r2, r6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L547
	mov	r0, r6
	ldr	r1, [r7, #148]
	add	r10, r7, #544
	bl	MPEG4DEC_RecycleImage
	add	r6, r7, #560
	ldr	r1, [r7, #544]
	ldr	r0, [r4, #2496]
	mov	r8, #0
	bl	FreeUsdByDec
	mov	r9, #0
	strd	r8, [r10]
	ldr	r0, [r4, #2496]
	ldr	r1, [r7, #552]
	bl	FreeUsdByDec
	strd	r8, [r6, #-8]
	b	.L550
.L547:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L550
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L550
	ldr	r3, [r7, #72]
	cmp	r3, #31
	bls	.L550
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG4DEC_GetRemainImg, .-MPEG4DEC_GetRemainImg
	.align	2
	.global	MPEG4DEC_GetImageBuffer
	.type	MPEG4DEC_GetImageBuffer, %function
MPEG4DEC_GetImageBuffer:
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
	add	r4, r0, #20480
	mov	r5, r0
	ldr	r0, [r4, #2496]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2496]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L567
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L567:
	add	r1, r5, #22528
	ldr	r0, [r4, #2496]
	add	r1, r1, #96
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageBuffer, .-MPEG4DEC_GetImageBuffer
	.align	2
	.global	MP4_GetPacketState
	.type	MP4_GetPacketState, %function
MP4_GetPacketState:
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
	add	r0, r0, #16384
	ldr	r3, [r0, #3596]
	cmp	r3, #1
	mvnne	r0, #0
	moveq	r0, #3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_GetPacketState, .-MP4_GetPacketState
	.align	2
	.global	MP4_ClearCurPacket
	.type	MP4_ClearCurPacket, %function
MP4_ClearCurPacket:
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
	ldr	r1, [r1, #20]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L572
	ldrb	r3, [r4, #86]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L573
.L572:
	ldr	r3, .L574
	mov	r0, r4
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L573:
	mov	r0, r5
	ldr	r1, [r4, #100]
	bl	SM_ReleaseStreamSeg
	b	.L572
.L575:
	.align	2
.L574:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_ClearCurPacket, .-MP4_ClearCurPacket
	.align	2
	.global	MP4_ClearCurPic
	.type	MP4_ClearCurPic, %function
MP4_ClearCurPic:
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
	add	r8, r0, #16384
	add	r3, r0, #20480
	ldr	r6, [r8, #3588]
	ldr	r7, [r3, #2496]
	cmp	r6, #0
	addgt	r5, r0, #15872
	movgt	r4, #0
	ble	.L579
.L578:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r6, r4
	bne	.L578
.L579:
	mov	r3, #0
	str	r3, [r8, #3588]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_ClearCurPic, .-MP4_ClearCurPic
	.align	2
	.global	Vdm_Mem_Move
	.type	Vdm_Mem_Move, %function
Vdm_Mem_Move:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 8
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
	mov	r4, r0
	mov	r5, r1
	mov	r0, #2
	ldr	r1, .L593
	mov	r10, r3
	str	r2, [fp, #-48]
	add	r8, r4, #20480
	ldr	r9, [fp, #4]
	ldr	r7, [fp, #8]
	ldr	r6, [fp, #12]
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	add	r0, r4, #12288
	add	r7, r7, #15
	add	r6, r6, #15
	movw	r3, #1206
	add	r1, r4, #1040
	str	r2, [r4, #1252]
	movw	r2, #1204
	str	r10, [r0, #3328]
	mov	r7, r7, lsr #4
	ldr	ip, [r5, #8]
	mov	r6, r6, lsr #4
	str	r9, [r4, #1260]
	str	ip, [r4, #1268]
	strh	r7, [r4, r2]	@ movhi
	strh	r6, [r4, r3]	@ movhi
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #24]
	str	r3, [r0, #3340]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #28]
	str	r3, [r0, #3344]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #60]
	str	r3, [r0, #3348]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #44]
	str	r3, [r0, #3352]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #48]
	str	r3, [r0, #3356]
	ldr	r3, [r8, #1596]
	ldr	r2, [r3, #592]
	str	r2, [r0, #3412]
	ldr	r2, [r3, #644]
	str	r2, [r0, #3416]
	str	r1, [r4, #1036]
	ldr	r2, [r3, #880]
	cmp	r2, #1
	beq	.L591
	cmp	r2, #2
	beq	.L592
.L584:
	mov	r3, #1
	strb	r3, [r4, #1198]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L591:
	cmp	r1, #0
	beq	.L584
	mov	r2, #0
	str	r2, [r4, #1036]
	ldr	r0, [r8, #2496]
	ldr	r1, [r8, #2524]
	bl	FSP_SetDisplay
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L592:
	ldr	r3, [r3, #884]
	cmp	r1, #0
	cmpne	r3, #0
	ble	.L584
	mov	r2, #0
	str	r2, [r4, #1036]
	ldr	r0, [r8, #2496]
	ldr	r1, [r8, #2524]
	bl	FSP_SetDisplay
	ldr	r2, [r8, #1596]
	mov	r0, r4
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L594:
	.align	2
.L593:
	.word	.LC33
	UNWIND(.fnend)
	.size	Vdm_Mem_Move, .-Vdm_Mem_Move
	.align	2
	.global	MP4_GetScdUpMsg
	.type	MP4_GetScdUpMsg, %function
MP4_GetScdUpMsg:
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
	add	r3, r0, #20480
	add	r5, r0, #22784
	add	r5, r5, #236
	add	r0, r0, #15872
	ldr	r3, [r3, #1596]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L597
.L596:
	ldr	r6, .L598
	add	r4, r1, #72
	mov	r2, #4
	mov	r1, r4
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r3, [r6, #52]
	mov	r1, r4
	mov	r0, r5
	mov	r2, #4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L597:
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L596
	ldr	r3, .L598
	mov	r1, r5
	mov	r2, #4
	ldr	r3, [r3, #52]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L599:
	.align	2
.L598:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_GetScdUpMsg, .-MP4_GetScdUpMsg
	.align	2
	.global	Mp4_Check_Slice_NotSH
	.type	Mp4_Check_Slice_NotSH, %function
Mp4_Check_Slice_NotSH:
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
	add	r3, r0, #16384
	add	r1, r0, #20480
	ldrb	r3, [r3, #3643]	@ zero_extendqisi2
	ldrb	r2, [r1, #736]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L608
	add	r3, r0, #12288
	ldrb	r3, [r3, #3584]	@ zero_extendqisi2
	tst	r3, #120
	bne	.L608
	add	r0, r0, #15872
	ldrh	r0, [r0]
	ubfx	r0, r0, #7, #4
	add	r0, r0, #17
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L602
.L604:
	.word	.L609
	.word	.L605
	.word	.L606
	.word	.L605
.L608:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L609:
	mov	r3, #17
.L603:
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L606:
	ldrb	r3, [r1, #745]	@ zero_extendqisi2
	ldrb	r2, [r1, #744]	@ zero_extendqisi2
	cmp	r3, r2
	movcc	r3, r2
	cmp	r3, #1
	addgt	r3, r3, #16
	movle	r3, #18
	b	.L603
.L605:
	ldrb	r3, [r1, #744]	@ zero_extendqisi2
	add	r3, r3, #16
	b	.L603
.L602:
	ldr	r1, .L612
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L613:
	.align	2
.L612:
	.word	.LC34
	UNWIND(.fnend)
	.size	Mp4_Check_Slice_NotSH, .-Mp4_Check_Slice_NotSH
	.align	2
	.global	Mp4_Combine_SliceData
	.type	Mp4_Combine_SliceData, %function
Mp4_Combine_SliceData:
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
	add	r2, r0, #16384
	add	r3, r0, #12288
	add	r0, r0, #1264
	ldr	ip, [r2, #3592]
	add	r0, r0, #12
	ldr	r2, [r3, #3324]
	tst	ip, #2
	beq	.L615
	ldrb	lr, [r3, #3430]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L629
	cmp	lr, #0
	bne	.L623
	ldrb	ip, [r3, #3510]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L623
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	bne	.L625
	ldr	r0, [r2, #20]
	cmp	r0, #0
	bne	.L625
	ldr	ip, [r2, #8]
	add	r1, ip, r1, lsl #3
	str	r1, [r2, #8]
	ldr	r1, [r3, #3516]
	str	r1, [r2, #20]
	ldr	r3, [r3, #3520]
	mov	r3, r3, asl #3
	str	r3, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L629:
	sub	r4, r2, #1
	movw	ip, #510
	cmp	r4, ip
	bhi	.L630
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	beq	.L619
	ldr	ip, [r2, #20]
	cmp	ip, #0
	beq	.L619
	ldr	r3, [r3, #3436]
	cmp	ip, r3
	bhi	.L631
	add	r1, r0, r1, lsl #3
	mov	r0, #0
	str	r1, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L619:
	ldr	ip, [r3, #3436]
	ldr	r0, [r2, #16]
	cmp	ip, r0
	movls	r1, r1, asl #3
	strls	r1, [r2, #12]
	ldrls	r3, [r3, #3436]
	movhi	r0, #0
	ldrhi	r3, [r2, #8]
	movls	r0, #0
	addhi	r1, r3, r1, lsl #3
	strls	r3, [r2, #20]
	strhi	r1, [r2, #8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L623:
	movw	r2, #4513
	ldr	r1, .L632
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L625:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L615:
	movw	r2, #4519
	ldr	r1, .L632
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L630:
	mov	r0, lr
	ldr	r1, .L632+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L631:
	mov	r0, lr
	movw	r2, #4489
	ldr	r1, .L632
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L633:
	.align	2
.L632:
	.word	.LC36
	.word	.LC35
	UNWIND(.fnend)
	.size	Mp4_Combine_SliceData, .-Mp4_Combine_SliceData
	.align	2
	.global	MP4_Check_StreamType
	.type	MP4_Check_StreamType, %function
MP4_Check_StreamType:
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
	add	r2, r0, #12288
	add	r0, r0, #20480
	ldrb	r3, [r2, #3584]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L635
	mov	r3, #2
	strb	r3, [r0, #805]
	ldr	r3, [r1]
	mov	r3, r3, lsr #8
	sub	r3, r3, #128
	cmp	r3, #3
	ldrlsb	r3, [r2, #3584]	@ zero_extendqisi2
	orrls	r3, r3, #2
	strlsb	r3, [r2, #3584]
.L636:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L635:
	mov	r2, #196
	mov	r3, #1
	str	r2, [r1]
	strb	r3, [r0, #805]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_Check_StreamType, .-MP4_Check_StreamType
	.align	2
	.global	MP4_Clean_HeadPacket
	.type	MP4_Clean_HeadPacket, %function
MP4_Clean_HeadPacket:
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
	add	r3, r0, #20480
	mov	r8, r0
	ldr	r6, [r3, #2052]
	ldr	r7, [r3, #2496]
	cmp	r6, #64
	movge	r6, #64
	cmp	r6, #0
	addgt	r5, r0, #22272
	movgt	r4, #0
	ble	.L640
.L639:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r4, r6
	bne	.L639
.L640:
	ldr	r3, .L642
	add	r0, r8, #22016
	add	r0, r0, #96
	mov	r2, #440
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L643:
	.align	2
.L642:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_Clean_HeadPacket, .-MP4_Clean_HeadPacket
	.align	2
	.global	MPEG4DEC_VDMPostProc
	.type	MPEG4DEC_VDMPostProc, %function
MPEG4DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #1036]
	add	r4, r0, #20480
	ldr	r7, .L696
	add	ip, r3, #12288
	movw	r2, #14668
	ldrb	lr, [r3, #159]	@ zero_extendqisi2
	mov	r5, r0
	ldr	r3, [r7, #48]
	mov	r6, r1
	add	r0, r0, #1040
	mov	r1, #0
	strb	lr, [r4, #812]
	ldr	ip, [ip, #2372]
	str	ip, [r4, #816]
	blx	r3
	mov	r0, r5
	bl	MP4_ClearCurPic
	mov	r0, r5
	bl	MP4_Clean_HeadPacket
	str	r6, [r4, #2080]
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #2516]
	mov	r6, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	cmp	r6, #0
	mov	r8, r0
	beq	.L690
	ldr	r2, [r4, #2088]
	mov	r0, #11
	ldr	r1, .L696+4
	bl	dprint_vfmw
	ldrb	r2, [r4, #1448]	@ zero_extendqisi2
	ldr	r1, .L696+8
	mov	r0, #11
	bl	dprint_vfmw
	ldr	r3, [r4, #2080]
	add	r1, r5, #22528
	add	r1, r1, #68
	str	r3, [r6, #152]
	ldr	r0, [r4, #2496]
	bl	Mp4_ClearUsrData
	ldrb	r2, [r4, #1448]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L647
	ldr	r2, [r4, #1596]
	ldr	r3, [r4, #2080]
	ldr	r1, [r2]
	cmp	r3, r1
	bhi	.L691
.L647:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #2136]
	bl	MP4_SetImgFormat
	ldr	r3, [r4, #1596]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L692
	ldr	r1, [r4, #2524]
	ldrb	r6, [r4, #1448]	@ zero_extendqisi2
	ldr	r7, [r4, #1540]
	str	r1, [r4, #2528]
.L653:
	cmn	r1, #1
	beq	.L655
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L693
	cmp	r7, #0
	cmpeq	r6, #4
	beq	.L694
	ldr	r2, [r8, #152]
	cmp	r2, #0
	beq	.L658
	ldr	r3, [r4, #1596]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	bhi	.L659
.L658:
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	subs	r7, r0, #0
	beq	.L695
	cmp	r6, #2
	beq	.L661
	ldrsb	r3, [r7, #1]
	cmp	r3, #2
	beq	.L661
	ldr	r2, [r4, #2528]
	mov	r0, #11
	ldr	r1, .L696+12
	bl	dprint_vfmw
.L655:
	ldr	r3, [r4, #2088]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #2088]
.L688:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L692:
	ldrb	ip, [r4, #1448]	@ zero_extendqisi2
	cmp	ip, #2
	beq	.L651
	ldr	r3, [r4, #2504]
	cmp	r3, #1
	ble	.L652
	ldr	r1, [r4, #2508]
	ldr	r7, [r4, #2512]
	str	r1, [r4, #2528]
	ldrb	r6, [r5]	@ zero_extendqisi2
	b	.L653
.L659:
	ldr	r3, .L696+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L664
	str	r2, [fp, #-44]
	mov	r3, #8
	str	r1, [fp, #-40]
	sub	r2, fp, #44
	mov	r1, #104
	ldr	r0, [r4, #2496]
	blx	ip
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	ldr	r1, [r3, #4]
.L664:
	mov	r3, r1
	add	r9, r8, #544
	ldr	r1, .L696+20
	mov	r0, #1
	bl	dprint_vfmw
	add	r5, r8, #560
	ldr	r1, [r8, #544]
	mov	r6, #0
	ldr	r0, [r4, #2496]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r8, #552]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r2, #0
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	b	.L655
.L661:
	mov	r2, #1
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	add	r3, r5, #22528
	ldr	r0, [r4, #2496]
	add	r3, r3, #96
	str	r8, [sp]
	mov	r2, r5
	mov	r1, #2
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L655
	ldr	r1, [r8, #544]
	add	r9, r8, #544
	ldr	r0, [r4, #2496]
	add	r5, r8, #560
	mov	r6, #0
	mov	r7, #0
.L689:
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r8, #552]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r2, #0
	ldr	r0, [r4, #2496]
	ldr	r1, [r4, #2528]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L688
.L651:
	ldr	r1, [r4, #2524]
	cmp	r8, #0
	ldr	r7, [r4, #1540]
	str	r1, [r4, #2528]
	beq	.L666
	add	r0, r8, #592
	add	r6, r6, #592
	ldrd	r8, [r0, #-8]
	ldrd	r2, [r6, #-8]
	cmp	r8, r2
	sbcs	lr, r9, r3
	bge	.L666
	strd	r8, [r6, #-8]
	mov	r6, ip
	strd	r2, [r0, #-8]
	ldr	r1, [r4, #2528]
	b	.L653
.L652:
	mvn	r3, #0
	str	r3, [r4, #2528]
	b	.L655
.L666:
	mov	r6, ip
	b	.L653
.L691:
	ldr	r1, .L696+16
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L648
	str	r3, [fp, #-44]
	mov	r1, #104
	ldr	lr, [r2]
	mov	r3, #8
	sub	r2, fp, #44
	ldr	r0, [r4, #2496]
	str	lr, [fp, #-40]
	blx	ip
.L648:
	mov	r6, #1
	ldr	r1, [r4, #2516]
	str	r6, [r4, #2136]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L649
	ldr	r1, [r5, #544]
	add	r7, r5, #560
	ldr	r0, [r4, #2496]
	add	r8, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #2496]
	add	r9, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, r6
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r6
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L649:
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2504]
	b	.L688
.L694:
	ldr	r2, [r4, #2496]
	mov	r1, #300
	ldr	r3, .L696+24
	add	r9, r8, #544
	add	r5, r8, #560
	mov	r6, #0
	mov	r0, r2
	mov	r7, #0
	mla	r3, r1, r2, r3
	ldr	r2, [r3, #16]
	add	r2, r2, #1
	str	r2, [r3, #16]
	ldr	r1, [r8, #544]
	b	.L689
.L690:
	mov	r3, r0
	mov	r2, r6
	mov	r0, r6
	ldr	r1, .L696+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L688
.L693:
	movw	r2, #4237
	ldr	r1, .L696+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L688
.L695:
	add	r5, r8, #560
	add	r6, r8, #544
	ldr	r1, [r8, #544]
	mov	r9, #0
	ldr	r0, [r4, #2496]
	mov	r8, #0
	bl	FreeUsdByDec
	strd	r8, [r6]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r8, [r5, #-8]
	mov	r2, r7
	ldr	r0, [r4, #2496]
	ldr	r1, [r4, #2528]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L688
.L697:
	.align	2
.L696:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC38
	.word	.LC39
	.word	.LC41
	.word	g_event_report
	.word	.LC42
	.word	g_VfmwChanStat
	.word	.LC37
	.word	.LC40
	UNWIND(.fnend)
	.size	MPEG4DEC_VDMPostProc, .-MPEG4DEC_VDMPostProc
	.align	2
	.global	MP4_Record_SlcSegID
	.type	MP4_Record_SlcSegID, %function
MP4_Record_SlcSegID:
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
	add	r5, r0, #16384
	movw	r6, #1022
	mov	r4, r0
	ldr	r2, [r5, #3588]
	cmp	r2, r6
	bhi	.L701
	add	r1, r0, #12288
	add	r4, r0, r2, lsl #2
	add	r4, r4, #12288
	add	r3, r2, #1
	ldr	r0, [r1, #3444]
	str	r0, [r4, #3588]
	str	r3, [r5, #3588]
	ldrb	r3, [r1, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r1, #3510]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r1, #3524]
	addeq	r2, r2, #2
	streq	r3, [r4, #3592]
	streq	r2, [r5, #3588]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L701:
	bl	MP4_Clean_HeadPacket
	mov	r0, r4
	bl	MP4_ClearCurPic
	add	r3, r4, #20480
	add	r1, r4, #15680
	ldr	r0, [r3, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	mov	r3, r6
	ldr	r2, [r5, #3588]
	mov	r0, #0
	ldr	r1, .L702
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L703:
	.align	2
.L702:
	.word	.LC43
	UNWIND(.fnend)
	.size	MP4_Record_SlcSegID, .-MP4_Record_SlcSegID
	.align	2
	.global	Mp4_Syntax_ShortHeader
	.type	Mp4_Syntax_ShortHeader, %function
Mp4_Syntax_ShortHeader:
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
	add	r7, r0, #12288
	mov	r4, r2
	mov	r6, r0
	ldr	r2, [r7, #3324]
	mov	r5, r1
	cmp	r2, #0
	bne	.L740
.L705:
	mov	r1, r5
	mov	r2, r4
	sub	r0, fp, #76
	add	r5, r6, #20480
	bl	BsInit
	ldr	r3, .L745
	add	r0, r6, #20992
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #224
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #22
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsSkip
	sub	r0, fp, #76
	mov	r1, #3
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #746]
	sub	r0, r0, #1
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L706
.L708:
	.word	.L707
	.word	.L709
	.word	.L710
	.word	.L711
.L711:
	mov	r2, #18
	mov	r3, #88
	strb	r2, [r5, #747]
	mov	r2, #704
	strb	r3, [r5, #748]
	mov	r3, #576
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
.L712:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r5, #803]	@ zero_extendqisi2
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #736]
	beq	.L714
	adds	r0, r0, #0
	ldr	r3, [r5, #2136]
	movne	r0, #1
	cmp	r3, #1
	movne	r0, #0
	cmp	r0, #0
	bne	.L714
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	mov	r9, r4, asl #3
	bl	BsGet
	mov	r1, #1
	mov	r4, #0
	uxtb	r0, r0
	cmp	r0, #0
	strneb	r0, [r5, #743]
	sub	r0, fp, #76
	moveq	r3, #1
	streqb	r3, [r5, #743]
	bl	BsSkip
.L720:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #1
	beq	.L741
	add	r4, r4, #1
	cmp	r4, #15
	bls	.L721
.L739:
	mov	r4, #0
	sub	r0, fp, #76
	strb	r4, [r5, #1577]
	bl	BsPos
	ldr	r3, .L745+4
	ldr	ip, [r3]
	cmp	ip, r4
	mov	r8, r0
	beq	.L727
	ldr	r0, [r5, #2496]
	mov	r3, r4
	mov	r2, r4
	mov	r1, #103
	blx	ip
	mov	r0, r8
.L738:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L710:
	mov	r2, #18
	mov	r3, #22
	strb	r2, [r5, #747]
	mov	r2, #352
	strb	r3, [r5, #748]
	mov	r3, #288
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L712
.L709:
	mov	r2, #9
	mov	r3, #11
	strb	r2, [r5, #747]
	mov	r2, #176
	strb	r3, [r5, #748]
	mov	r3, #144
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L712
.L707:
	mov	r2, #6
	mov	r3, #8
	strb	r2, [r5, #747]
	mov	r2, #128
	strb	r3, [r5, #748]
	mov	r3, #96
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L712
.L741:
	sub	r0, fp, #76
	add	r4, r4, #1
	bl	BsPos
	mov	r1, #8
	cmp	r0, r9
	sub	r0, fp, #76
	bgt	.L742
	bl	BsSkip
	cmp	r4, #15
	bls	.L720
	b	.L739
.L740:
	ldr	r1, .L745+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #3324]
	b	.L705
.L721:
	add	r10, r6, #16384
	mov	r2, #1
	strb	r2, [r5, #1577]
	sub	r0, fp, #76
	ldr	r3, [r10, #3592]
	orr	r3, r3, #2
	str	r3, [r10, #3592]
	ldr	r3, [r7, #3324]
	add	r3, r3, r2
	str	r3, [r7, #3324]
	strb	r2, [r5, #744]
	bl	BsPos
	mov	r3, r0, asr #31
	mov	r8, r0
	add	r1, r0, #7
	rsb	r4, r0, r9
	mov	r3, r3, lsr #29
	str	r4, [r6, #1284]
	add	r2, r8, r3
	ldr	r0, [r5, #1592]
	and	r2, r2, #7
	cmp	r8, #0
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r6, #1282]
	ldr	r3, [r5, #1584]
	movge	r1, r8
	add	r3, r3, r1, asr #3
	str	r3, [r6, #1292]
	ldrb	r3, [r7, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L743
.L722:
	mov	r3, #0
	str	r3, [r6, #1288]
	strb	r3, [r6, #1283]
	str	r3, [r6, #1296]
.L723:
	ldrb	r3, [r5, #736]	@ zero_extendqisi2
	strb	r3, [r6, #1280]
	ldrb	r3, [r5, #745]	@ zero_extendqisi2
	strb	r3, [r6, #1278]
	ldrb	r3, [r5, #744]	@ zero_extendqisi2
	strb	r3, [r6, #1277]
	ldrb	r3, [r5, #743]	@ zero_extendqisi2
	strb	r3, [r6, #1281]
	ldrb	r3, [r5, #740]	@ zero_extendqisi2
	strb	r3, [r6, #1279]
	ldr	r2, [r10, #3588]
	cmp	r2, #0
	bne	.L744
.L724:
	mov	r0, r6
	bl	MP4_Record_SlcSegID
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L714:
	sub	r0, fp, #76
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L706:
	mov	r4, #0
	sub	r0, fp, #76
	strb	r4, [r5, #1577]
	bl	BsPos
	ldr	r3, .L745+4
	ldr	ip, [r3]
	cmp	ip, r4
	mov	r8, r0
	beq	.L727
	ldr	r0, [r5, #2496]
	mov	r3, r4
	mov	r2, r4
	mov	r1, #102
	blx	ip
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L743:
	ldrb	r2, [r7, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L722
	ldr	r2, [r7, #3520]
	strb	r3, [r6, #1283]
	mov	r3, r2, asl #3
	str	r3, [r6, #1288]
	ldr	r3, [r7, #3516]
	str	r3, [r6, #1296]
	b	.L723
.L744:
	ldr	r1, .L745+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	b	.L724
.L727:
	mov	r0, r8
	b	.L738
.L742:
	bl	BsPos
	b	.L738
.L746:
	.align	2
.L745:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC44
	.word	.LC45
	UNWIND(.fnend)
	.size	Mp4_Syntax_ShortHeader, .-Mp4_Syntax_ShortHeader
	.align	2
	.global	Mp4_Syntax_Vop
	.type	Mp4_Syntax_Vop, %function
Mp4_Syntax_Vop:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	add	r7, r0, #12288
	mov	r6, r2
	mov	r5, r0
	ldr	r2, [r7, #3324]
	mov	r10, r1
	cmp	r2, #0
	bne	.L825
	add	r4, r5, #20480
	ldrb	r3, [r4, #797]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L749
.L826:
	mov	r0, #32
	strb	r3, [r4, #1577]
.L750:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L825:
	add	r4, r5, #20480
	ldr	r1, .L841
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #3324]
	ldrb	r3, [r4, #797]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L826
.L749:
	add	r8, r5, #20992
	ldr	r9, .L841+4
	add	r8, r8, #224
	mov	r1, r10
	sub	r0, fp, #76
	mov	r2, r6
	bl	BsInit
	mov	r2, #60
	ldr	r3, [r9, #48]
	mov	r1, #0
	mov	r0, r8
	blx	r3
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #1577]
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	ldr	r1, .L841+8
	uxtb	r2, r0
	strb	r0, [r4, #736]
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r10, [r4, #736]	@ zero_extendqisi2
	cmp	r10, #3
	beq	.L827
.L751:
	adds	r10, r10, #0
	ldrb	r3, [r4, #803]	@ zero_extendqisi2
	movne	r10, #1
	cmp	r3, #1
	movne	r2, #0
	andeq	r2, r10, #1
	cmp	r2, #0
	bne	.L754
	cmp	r3, #2
	beq	.L754
	ldr	r3, [r4, #2136]
	cmp	r3, #1
	movne	r10, #0
	andeq	r10, r10, #1
	cmp	r10, #0
	bne	.L754
	mov	r6, r6, asl #3
	b	.L757
.L829:
	bl	BsPos
	add	r10, r10, #1
	cmp	r0, r6
	bgt	.L828
	cmp	r10, #6400
	beq	.L758
.L757:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	sub	r0, fp, #76
	bne	.L829
	cmp	r10, #6400
	bcs	.L758
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L830
	ldr	r1, [r4, #912]
	cmp	r1, #0
	moveq	r0, r1
	bne	.L831
.L761:
	str	r10, [r4, #1516]
	mov	r1, #1
	str	r0, [r4, #1520]
	sub	r0, fp, #76
	bl	BsGet
	subs	r10, r0, #0
	bne	.L762
	ldr	r1, .L841+12
	mov	r0, #1
	bl	dprint_vfmw
	strb	r10, [r4, #1577]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L841+16
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r5, r0
	beq	.L788
	ldr	r0, [r4, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #103
	blx	ip
	mov	r0, r5
	b	.L750
.L758:
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r4, #1577]
	bl	BsPos
	mov	r2, r10
	ldr	r1, .L841+20
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L750
.L828:
	sub	r0, fp, #76
	bl	BsPos
	ldr	r1, .L841+24
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L750
.L827:
	ldr	r3, .L841+28
	ldr	r3, [r3]
	ands	r3, r3, #8
	bne	.L751
	strb	r3, [r4, #1577]
	sub	r0, fp, #76
	str	r3, [fp, #-80]
	bl	BsPos
	ldr	r2, .L841+16
	ldr	ip, [r2]
	cmp	ip, #0
	mov	r5, r0
	beq	.L752
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r2, r3
	blx	ip
.L752:
	ldr	r1, .L841+32
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L750
.L754:
	sub	r0, fp, #76
	bl	BsPos
	b	.L750
.L762:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #737]
	cmp	r0, #0
	beq	.L832
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L764
	cmp	r3, #3
	beq	.L833
.L765:
	mov	r3, #0
	strb	r3, [r4, #738]
.L766:
	ldrb	r3, [r4, #852]	@ zero_extendqisi2
	mov	r2, #0
	strb	r2, [r4, #739]
	cmp	r3, #2
	addeq	r10, r5, #16384
	beq	.L767
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	add	r10, r5, #16384
	strb	r0, [r4, #740]
	ldrb	r3, [r10, #3634]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r4, #742]
	moveq	r3, #2
	streqb	r3, [r4, #741]
	bne	.L834
.L769:
	ldrb	r3, [r4, #856]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	bls	.L770
.L773:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #743]
	strneb	r0, [r4, #743]
.L779:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L835
.L767:
	mov	r3, #1
	strb	r3, [r4, #1577]
	ldr	r3, [r10, #3592]
	add	r0, r5, #21760
	mov	r1, r8
	mov	r2, #60
	orr	r3, r3, #2
	str	r3, [r10, #3592]
	ldr	r3, [r7, #3324]
	add	r0, r0, #168
	ldr	ip, [r9, #52]
	add	r3, r3, #1
	str	r3, [r7, #3324]
	blx	ip
	sub	r0, fp, #76
	bl	BsPos
	mov	r3, r0, asr #31
	mov	r8, r0
	add	r1, r0, #7
	rsb	r6, r0, r6
	mov	r3, r3, lsr #29
	str	r6, [r5, #1284]
	add	r2, r8, r3
	ldr	r0, [r4, #1592]
	and	r2, r2, #7
	cmp	r8, #0
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r5, #1282]
	ldr	r3, [r4, #1584]
	movge	r1, r8
	add	r3, r3, r1, asr #3
	str	r3, [r5, #1292]
	ldrb	r3, [r7, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L783
	ldrb	r2, [r7, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L836
.L783:
	mov	r3, #0
	str	r3, [r5, #1288]
	strb	r3, [r5, #1283]
	str	r3, [r5, #1296]
.L784:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	strb	r3, [r5, #1280]
	ldrb	r3, [r4, #745]	@ zero_extendqisi2
	strb	r3, [r5, #1278]
	ldrb	r3, [r4, #744]	@ zero_extendqisi2
	strb	r3, [r5, #1277]
	ldrb	r3, [r4, #743]	@ zero_extendqisi2
	strb	r3, [r5, #1281]
	ldrb	r3, [r4, #740]	@ zero_extendqisi2
	strb	r3, [r5, #1279]
	ldr	r2, [r10, #3588]
	cmp	r2, #0
	bne	.L837
.L785:
	mov	r0, r5
	bl	MP4_Record_SlcSegID
	mov	r0, r8
	b	.L750
.L830:
	ldr	r1, .L841+12
	mov	r0, #1
	str	r3, [fp, #-80]
	bl	dprint_vfmw
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r4, #1577]
	bl	BsPos
	ldr	r2, .L841+16
	ldr	ip, [r2]
	cmp	ip, #0
	mov	r5, r0
	beq	.L788
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r2, r3
	blx	ip
	mov	r0, r5
	b	.L750
.L831:
	sub	r0, fp, #76
	bl	BsGet
	b	.L761
.L788:
	mov	r0, r5
	b	.L750
.L837:
	ldr	r1, .L841+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	bl	MP4_ClearCurPic
	b	.L785
.L832:
	add	r5, r5, #16384
	mov	r3, #4
	mov	r2, #1
	strb	r3, [r4, #736]
	strb	r3, [r4, #1448]
	sub	r0, fp, #76
	strb	r2, [r4, #1577]
	ldr	r3, [r5, #3592]
	orr	r3, r3, #128
	str	r3, [r5, #3592]
	bl	BsPos
	b	.L750
.L833:
	ldrb	r3, [r4, #856]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L765
.L764:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #738]
	b	.L766
.L835:
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #744]
	cmp	r2, #0
	beq	.L838
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L767
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #745]
	cmp	r2, #0
	bne	.L767
	strb	r2, [r4, #1577]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L841+16
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r5, r0
	beq	.L782
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r3, r2
	blx	ip
.L782:
	ldr	r1, .L841+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L750
.L834:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #741]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #742]
	b	.L769
.L770:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L773
	ldrb	r3, [r4, #868]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L773
	add	r3, r5, #21248
	mov	r2, #0
	add	r3, r3, #4
	str	r5, [fp, #-84]
	str	r6, [fp, #-88]
	mov	r6, r2
	str	r8, [fp, #-80]
	mov	r5, r3
	str	r7, [fp, #-92]
	b	.L778
.L774:
	ldr	r3, [r4, #1552]
	cmp	r3, #500
	bne	.L775
	ldr	r2, [r4, #1556]
	movw	r3, #413
	cmp	r2, r3
	beq	.L776
.L775:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
.L776:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r3, r0, #0
	moveq	r7, r3
	bne	.L839
.L777:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	str	r8, [r5]
	str	r7, [r5, #4]
	add	r6, r6, #1
	ldrb	r3, [r4, #868]	@ zero_extendqisi2
	add	r5, r5, #8
	cmp	r3, r6
	bls	.L840
.L778:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r7, r0, #0
	moveq	r8, r7
	beq	.L774
	mov	r1, r7
	sub	r0, fp, #76
	bl	BsGet
	sub	r2, r7, #1
	movs	r3, r0, asr r2
	mov	r8, r0
	moveq	r3, #1
	moveq	r3, r3, asl r7
	subeq	r3, r3, #1
	eoreq	r8, r8, r3
	rsbeq	r8, r8, #0
	b	.L774
.L839:
	mov	r1, r3
	sub	r0, fp, #76
	str	r3, [fp, #-96]
	bl	BsGet
	ldr	r3, [fp, #-96]
	sub	r2, r3, #1
	movs	r2, r0, asr r2
	mov	r7, r0
	moveq	r2, #1
	moveq	r3, r2, asl r3
	subeq	r2, r3, #1
	eoreq	r3, r0, r2
	rsbeq	r7, r3, #0
	b	.L777
.L836:
	ldr	r2, [r7, #3520]
	strb	r3, [r5, #1283]
	mov	r3, r2, asl #3
	str	r3, [r5, #1288]
	ldr	r3, [r7, #3516]
	str	r3, [r5, #1296]
	b	.L784
.L838:
	strb	r2, [r4, #1577]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L841+16
	ldr	ip, [r3]
	cmp	ip, #0
	mov	r5, r0
	beq	.L781
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r3, r2
	blx	ip
.L781:
	ldrb	r2, [r4, #736]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L841+44
	bl	dprint_vfmw
	mov	r0, r5
	b	.L750
.L840:
	ldr	r8, [fp, #-80]
	ldr	r5, [fp, #-84]
	ldr	r6, [fp, #-88]
	ldr	r7, [fp, #-92]
	b	.L773
.L842:
	.align	2
.L841:
	.word	.LC44
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC8
	.word	g_event_report
	.word	.LC49
	.word	.LC48
	.word	g_VdmCharacter
	.word	.LC47
	.word	.LC45
	.word	.LC51
	.word	.LC50
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vop, .-Mp4_Syntax_Vop
	.align	2
	.global	Mp4_Syntax_Slice_NotSH
	.type	Mp4_Syntax_Slice_NotSH, %function
Mp4_Syntax_Slice_NotSH:
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
	add	r7, r0, #12288
	mov	r4, r0
	movw	r3, #510
	ldr	r8, [r7, #3324]
	mov	r5, r2
	sub	r0, r8, #1
	cmp	r0, r3
	bhi	.L864
	add	r3, r4, #15872
	add	r0, r8, #1
	str	r0, [r7, #3324]
	add	r6, r4, #20480
	ldrh	r9, [r3]
	sub	r0, fp, #76
	bl	BsInit
	sub	r0, fp, #76
	ubfx	r9, r9, #7, #4
	add	r9, r9, #17
	mov	r1, r9
	bl	BsSkip
	ldr	r2, [r6, #1508]
	ldr	r9, [r6, #1512]
	add	r2, r2, #15
	add	r9, r9, #15
	mov	r2, r2, lsr #4
	mov	r9, r9, lsr #4
	mul	r9, r9, r2
	cmp	r9, #0
	beq	.L846
	mov	lr, r9
	mov	r1, #0
.L847:
	add	ip, r1, #1
	movs	lr, lr, lsr #1
	uxth	r1, ip
	bne	.L847
	sxth	r1, r1
	sub	r0, fp, #76
	bl	BsGet
	mov	r10, r8, asl #2
	mov	r8, r8, asl #5
	sub	r1, r9, #1
	rsb	r3, r10, r8
	add	r3, r4, r3
	cmp	r0, r1
	str	r0, [r3, #1300]
	bhi	.L865
.L848:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	rsb	r9, r10, r8
	add	r9, r4, r9
	mov	r1, #1
	add	r9, r9, #1264
	add	r9, r9, #8
	strb	r0, [r9, #9]
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	bne	.L866
	ldrb	r3, [r6, #736]	@ zero_extendqisi2
	mov	r5, r5, asl #3
	add	r2, r4, #16384
	strb	r3, [r9, #8]
	ldrb	r3, [r6, #740]	@ zero_extendqisi2
	strb	r3, [r9, #7]
.L852:
	ldrb	ip, [r6, #744]	@ zero_extendqisi2
	rsb	r3, r10, r8
	add	r3, r4, r3
	sub	r0, fp, #76
	add	r1, r3, #1264
	str	r3, [fp, #-84]
	strb	ip, [r3, #1277]
	add	r1, r1, #8
	ldrb	ip, [r6, #745]	@ zero_extendqisi2
	str	r1, [fp, #-80]
	strb	ip, [r3, #1278]
	ldr	ip, [r2, #3592]
	orr	ip, ip, #16
	str	ip, [r2, #3592]
	bl	BsPos
	ldr	r3, [fp, #-84]
	ldr	r1, [fp, #-80]
	mov	r2, r0, asr #31
	mov	r9, r0
	add	ip, r0, #7
	rsb	r5, r0, r5
	mov	r2, r2, lsr #29
	str	r5, [r3, #1284]
	add	r0, r0, r2
	ldr	lr, [r6, #1592]
	and	r0, r0, #7
	cmp	r9, #0
	rsb	r2, r2, r0
	add	r2, r2, lr
	strb	r2, [r1, #10]
	ldr	r2, [r6, #1584]
	movge	ip, r9
	add	r2, r2, ip, asr #3
	str	r2, [r3, #1292]
	ldrb	r2, [r7, #3430]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L853
	ldrb	r1, [r7, #3510]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L867
.L853:
	rsb	r8, r10, r8
	mov	r3, #0
	add	r8, r4, r8
	add	r1, r8, #1280
	add	r2, r8, #1264
	str	r3, [r1, #8]
	mov	r8, r1
	strb	r3, [r2, #19]
	str	r3, [r8, #16]
.L854:
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	mov	r0, r9
.L863:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L866:
	mov	r5, r5, asl #3
.L850:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r9, r0
	sub	r0, fp, #76
	bl	BsPos
	cmp	r9, #0
	cmpne	r0, r5
	blt	.L850
	mov	r1, #1
	sub	r0, fp, #76
	add	r2, r4, #16384
	str	r2, [fp, #-80]
	bl	BsSkip
	ldr	r2, [fp, #-80]
	ldr	r1, [r2, #3692]
	cmp	r1, #0
	bne	.L868
.L851:
	mov	r1, #1
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	rsb	r9, r10, r8
	add	r9, r4, r9
	mov	r1, #3
	add	r9, r9, #1264
	strb	r0, [r9, #16]
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r9, #16]	@ zero_extendqisi2
	ldr	r2, [fp, #-80]
	cmp	r3, #0
	strb	r0, [r9, #15]
	add	r9, r9, #8
	beq	.L852
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	ldrb	r3, [r9, #8]	@ zero_extendqisi2
	ldr	r2, [fp, #-80]
	cmp	r3, #2
	bne	.L852
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r2, [fp, #-80]
	b	.L852
.L864:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	mov	r0, r4
	add	r4, r4, #16384
	bl	MP4_ClearCurPic
	ldr	r2, .L869
	mov	r0, #1
	ldr	r3, [r4, #3592]
	ldr	r1, .L869+4
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r4, #3592]
	ldr	r3, [r7, #3324]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L868:
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r2, [fp, #-80]
	b	.L851
.L867:
	ldr	r1, [r7, #3520]
	strb	r2, [r3, #1283]
	mov	r2, r1, asl #3
	str	r2, [r3, #1288]
	ldr	r2, [r7, #3516]
	str	r2, [r3, #1296]
	b	.L854
.L846:
	mov	r1, r9
	sub	r0, fp, #76
	bl	BsGet
	mov	r10, r8, asl #2
	mov	r8, r8, asl #5
	rsb	r3, r10, r8
	add	r3, r4, r3
	str	r0, [r3, #1300]
	b	.L848
.L865:
	mov	r2, r0
	mov	r3, r9
	ldr	r1, .L869+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L863
.L870:
	.align	2
.L869:
	.word	.LANCHOR1+1296
	.word	.LC52
	.word	.LC53
	UNWIND(.fnend)
	.size	Mp4_Syntax_Slice_NotSH, .-Mp4_Syntax_Slice_NotSH
	.align	2
	.global	Mp4_Syntax_Slice_SH
	.type	Mp4_Syntax_Slice_SH, %function
Mp4_Syntax_Slice_SH:
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
	add	r10, r0, #12288
	mov	r5, r0
	movw	r3, #510
	ldr	r4, [r10, #3324]
	mov	r9, r2
	sub	r0, r4, #1
	str	r0, [fp, #-80]
	cmp	r0, r3
	bhi	.L885
	ldrb	r7, [r10, #3584]	@ zero_extendqisi2
	add	r3, r4, #1
	sub	r0, fp, #76
	str	r3, [r10, #3324]
	ubfx	r7, r7, #3, #4
	bl	BsInit
	add	r7, r7, #17
	sub	r0, fp, #76
	add	r6, r5, #20480
	mov	r1, r7
	bl	BsSkip
	mov	r3, r4, asl #2
	mov	r1, #5
	sub	r0, fp, #76
	mov	r8, r3
	str	r3, [fp, #-88]
	bl	BsGet
	ldrb	r7, [r6, #748]	@ zero_extendqisi2
	mov	ip, r4, asl #5
	movw	lr, #1206
	rsb	r2, r8, ip
	movw	r1, #1204
	add	r4, r5, r2
	mul	r0, r7, r0
	str	r0, [r4, #1300]
	ldrh	lr, [r5, lr]
	ldrh	r1, [r5, r1]
	mul	r1, r1, lr
	sub	r3, r1, #1
	cmp	r0, r3
	bhi	.L886
	mov	r1, #2
	sub	r0, fp, #76
	str	ip, [fp, #-84]
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #1281]
	sub	r0, fp, #76
	ldrb	r1, [r6, #736]	@ zero_extendqisi2
	strb	r1, [r4, #1280]
	ldrb	r1, [r6, #740]	@ zero_extendqisi2
	strb	r1, [r4, #1279]
	ldrb	r1, [r6, #744]	@ zero_extendqisi2
	strb	r1, [r4, #1277]
	ldrb	r1, [r6, #745]	@ zero_extendqisi2
	strb	r1, [r4, #1278]
	bl	BsPos
	ldr	ip, [fp, #-84]
	mov	r7, r0
	mov	r0, r0, asr #31
	rsb	r9, r7, r9, lsl #3
	str	r9, [r4, #1284]
	mov	r0, r0, lsr #29
	ldr	r3, [r6, #1592]
	add	r1, r7, r0
	cmp	r7, #0
	and	r1, r1, #7
	add	lr, r7, #7
	rsb	r1, r0, r1
	add	r9, r5, #16384
	add	r1, r1, r3
	strb	r1, [r4, #1282]
	ldr	r3, [r6, #1584]
	movge	lr, r7
	add	lr, r3, lr, asr #3
	str	lr, [r4, #1292]
	ldr	r3, [r9, #3592]
	orr	r3, r3, #16
	str	r3, [r9, #3592]
	ldrb	r3, [r10, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L887
.L875:
	ldr	r3, [fp, #-88]
	rsb	r4, r3, ip
	mov	r3, #0
	add	r4, r5, r4
	add	r1, r4, #1280
	add	r2, r4, #1264
	str	r3, [r1, #8]
	mov	r4, r1
	strb	r3, [r2, #19]
	str	r3, [r4, #16]
.L876:
	ldr	r3, [fp, #-80]
	mov	r2, r3, asl #2
	mov	r6, r3, asl #5
	rsb	r3, r2, r6
	add	r3, r5, r3
	ldr	r1, [r3, #1296]
	cmp	r1, #0
	bne	.L888
.L877:
	rsb	r6, r2, r6
	ldrb	r3, [r10, #3584]	@ zero_extendqisi2
	add	r6, r5, r6
	ubfx	r3, r3, #3, #4
	ldr	r2, [r6, #1284]
	add	r3, r3, r2
	str	r3, [r6, #1284]
.L878:
	mov	r0, r5
	bl	MP4_Record_SlcSegID
	mov	r0, r7
.L873:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L888:
	ldr	r1, [r3, #1288]
	add	r3, r3, #1280
	add	r3, r3, #4
	cmp	r1, #0
	beq	.L877
	ldrb	r2, [r10, #3584]	@ zero_extendqisi2
	ubfx	r2, r2, #3, #4
	add	r2, r2, r1
	str	r2, [r3, #4]
	b	.L878
.L887:
	ldrb	r1, [r10, #3510]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L875
	ldr	r1, [r10, #3520]
	strb	r3, [r4, #1283]
	mov	r3, r1, asl #3
	str	r3, [r4, #1288]
	ldr	r3, [r10, #3516]
	str	r3, [r4, #1296]
	b	.L876
.L885:
	add	r3, r5, #20480
	add	r1, r5, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	mov	r0, r5
	add	r5, r5, #16384
	bl	MP4_ClearCurPic
	ldr	r2, .L889
	mov	r0, #1
	ldr	r3, [r5, #3592]
	ldr	r1, .L889+4
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r5, #3592]
	ldr	r3, [r10, #3324]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L886:
	mov	r2, r0
	ldr	r1, .L889+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L873
.L890:
	.align	2
.L889:
	.word	.LANCHOR1+1320
	.word	.LC52
	.word	.LC54
	UNWIND(.fnend)
	.size	Mp4_Syntax_Slice_SH, .-Mp4_Syntax_Slice_SH
	.align	2
	.global	MP4_Dec_Slice
	.type	MP4_Dec_Slice, %function
MP4_Dec_Slice:
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
	add	ip, r0, #12288
	mov	r4, r0
	ldrb	r3, [ip, #3584]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L901
	tst	r3, #4
	beq	.L902
	mov	r0, r4
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	beq	.L899
.L895:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L902:
	add	r0, r0, #15872
	ldrh	r0, [r0]
	ubfx	r0, r0, #7, #4
	sub	lr, r0, #1
	cmp	lr, #6
	bfils	r3, r0, #3, #4
	mov	r0, r4
	strlsb	r3, [ip, #3584]
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	bne	.L895
.L899:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	ldr	r2, .L904
	ldr	r1, .L904+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L901:
	str	r2, [fp, #-28]
	str	r1, [fp, #-24]
	bl	Mp4_Check_Slice_NotSH
	ldr	r1, [fp, #-24]
	ldr	r2, [fp, #-28]
	cmp	r0, #0
	beq	.L903
	mov	r1, r2
	mov	r0, r4
	bl	Mp4_Combine_SliceData
	cmp	r0, #0
	bne	.L899
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	b	.L895
.L903:
	mov	r0, r4
	bl	Mp4_Syntax_Slice_NotSH
	cmn	r0, #1
	beq	.L899
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L905:
	.align	2
.L904:
	.word	.LANCHOR1+1340
	.word	.LC55
	UNWIND(.fnend)
	.size	MP4_Dec_Slice, .-MP4_Dec_Slice
	.align	2
	.global	MP4_Record_PacketID
	.type	MP4_Record_PacketID, %function
MP4_Record_PacketID:
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
	add	r5, r0, #20480
	mov	r4, r0
	ldr	r3, [r5, #2052]
	cmp	r3, #62
	bgt	.L909
	add	r1, r0, #12288
	add	r4, r0, r3, lsl #2
	add	r4, r4, #20480
	add	r2, r3, #1
	ldr	r0, [r1, #3444]
	str	r0, [r4, #1796]
	str	r2, [r5, #2052]
	ldrb	r2, [r1, #3430]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r2, [r1, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r2, [r1, #3524]
	addeq	r3, r3, #2
	streq	r2, [r4, #1800]
	streq	r3, [r5, #2052]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L909:
	bl	MP4_Clean_HeadPacket
	add	r1, r4, #15680
	ldr	r0, [r5, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	ldr	r2, [r5, #2052]
	mov	r3, #62
	ldr	r1, .L910
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L911:
	.align	2
.L910:
	.word	.LC43
	UNWIND(.fnend)
	.size	MP4_Record_PacketID, .-MP4_Record_PacketID
	.align	2
	.global	MP4_Record_HeadPacketInfo
	.type	MP4_Record_HeadPacketInfo, %function
MP4_Record_HeadPacketInfo:
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
	subs	r4, r0, #0
	mov	r7, r1
	beq	.L915
	ldr	r6, .L917
	add	r1, r4, #15680
	add	r0, r4, #22016
	add	r1, r1, #32
	mov	r2, #160
	add	r5, r4, #20480
	ldr	r3, [r6, #52]
	add	r0, r0, #96
	blx	r3
	ldr	r3, [r6, #52]
	mov	r2, #4
	add	r1, r4, #15872
	add	r0, r4, #22272
	blx	r3
	ldr	r3, [r5, #2060]
	str	r7, [r5, #2056]
	cmp	r3, #0
	beq	.L916
.L914:
	ldr	r3, [r5, #2064]
	add	r3, r3, #1
	str	r3, [r5, #2064]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L916:
	mov	r0, r4
	bl	MP4_Record_PacketID
	mov	r3, #1
	str	r3, [r5, #2060]
	b	.L914
.L915:
	ldr	r1, .L917+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L918:
	.align	2
.L917:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC56
	UNWIND(.fnend)
	.size	MP4_Record_HeadPacketInfo, .-MP4_Record_HeadPacketInfo
	.align	2
	.global	Mp4_Syntax_Parse
	.type	Mp4_Syntax_Parse, %function
Mp4_Syntax_Parse:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 88
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
	ldr	r9, .L1069
	mov	r6, r0
	mov	r7, r1
	mov	r4, r2
	str	r2, [fp, #-120]
	ldr	r3, [r9, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #108
	blx	r3
	mov	r2, r4
	mov	r1, r7
	sub	r0, fp, #108
	bl	BsInit
	sub	r0, fp, #108
	mov	r1, #32
	add	r8, r6, #16384
	bl	BsShow
	movw	r3, #510
	mov	r10, #0
	str	r10, [r8, #3596]
	cmp	r0, r3
	mov	r5, r0
	beq	.L1048
	add	r1, r6, #12288
	ldrb	r3, [r1, #3584]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L1049
.L925:
	add	r4, r6, #20480
	mov	r5, #196
	mov	r2, #1
	strb	r2, [r4, #805]
.L926:
	and	r3, r3, #2
	ands	r3, r3, #255
	bne	.L927
	ldr	r2, [r8, #3592]
	ands	r10, r2, #130
	bne	.L1050
	cmp	r5, #197
	beq	.L1051
	cmp	r5, #432
	beq	.L1052
	movw	r3, #437
	cmp	r5, r3
	beq	.L1053
	bic	r3, r5, #15
	cmp	r3, #288
	beq	.L1054
	movw	r3, #435
	cmp	r5, r3
	beq	.L1055
	movw	r3, #438
	cmp	r5, r3
	beq	.L1056
	cmp	r5, #196
	beq	.L1057
	movw	r3, #434
	cmp	r5, r3
	beq	.L1058
	movw	r3, #286
	cmp	r5, r3
	bne	.L942
	ldr	r10, .L1069+4
	ldr	ip, [r10]
	cmp	ip, #0
	beq	.L943
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #2496]
	blx	ip
.L943:
	ldr	r3, [fp, #-120]
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	bl	MP4_ClearCurPacket
	ldr	r3, [r8, #3592]
	add	r2, r7, #4
	str	r2, [fp, #-124]
	tst	r3, #2
	orrne	r3, r3, #256
	strne	r3, [r8, #3592]
	ldr	r3, [r8, #3592]
	and	r3, r3, #18
	cmp	r3, #18
	beq	.L945
	ldr	r10, [r10]
	cmp	r10, #0
	beq	.L945
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #2496]
	blx	r10
.L945:
	ldrb	r3, [r4, #2533]	@ zero_extendqisi2
	mov	r10, #0
	cmp	r3, #1
	beq	.L976
.L951:
	ldrb	r3, [r4, #1575]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1045
	ldr	r3, [r4, #2072]
	add	r1, r6, #19968
	add	r0, r6, #21248
	add	r1, r1, #40
	add	r3, r3, #1
	mov	r2, #604
	str	r3, [r4, #2072]
	add	r0, r0, #76
	mov	r3, #0
	ldr	r5, [r9, #52]
	str	r3, [r4, #2076]
	blx	r5
	ldr	r2, [r4, #1508]
	ldr	r0, [r8, #3708]
	ldr	r1, [r8, #3704]
	cmp	r2, r0
	beq	.L1059
.L967:
	ldr	r3, .L1069+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L969
	ldr	lr, [r4, #1512]
	mov	r3, #8
	strh	r2, [fp, #-114]	@ movhi
	sub	r2, fp, #116
	strh	r1, [fp, #-112]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-110]	@ movhi
	strh	lr, [fp, #-116]	@ movhi
	ldr	r0, [r4, #2496]
	blx	r5
	ldr	r0, [r8, #3708]
	ldr	r1, [r8, #3704]
.L969:
	mov	r5, #1
	str	r0, [r4, #1508]
	str	r1, [r4, #1512]
.L968:
	sxtb	r5, r5
	cmp	r5, #1
	beq	.L1060
.L971:
	ldr	r3, [r4, #1508]
	mov	r2, #0
	ldr	r1, [r4, #1512]
	str	r3, [r4, #2096]
	str	r1, [r4, #2092]
	ldr	r3, [r8, #3708]
	str	r3, [r4, #1508]
	ldr	r3, [r8, #3704]
	strb	r2, [r4, #1575]
	str	r3, [r4, #1512]
	b	.L1045
.L1050:
	orr	r2, r2, #32
	mov	r10, r3
	str	r2, [r8, #3592]
	mov	r3, #1
	str	r3, [r8, #3596]
.L1045:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L927:
	ldr	r2, [fp, #-120]
	mov	r1, r7
	mov	r0, r6
	bl	MP4_Dec_Slice
	mov	r10, r0
.L931:
	ldrb	r3, [r4, #2533]	@ zero_extendqisi2
	str	r7, [fp, #-124]
	cmp	r3, #1
	beq	.L976
	ldr	r3, [fp, #-120]
	cmp	r10, r3, asl #3
	bhi	.L950
.L1065:
	movw	r3, #438
	cmp	r5, r3
	cmpne	r5, #196
	bne	.L951
	ldr	r3, [r8, #3592]
	tst	r3, #130
	beq	.L951
	ldrb	r3, [r4, #805]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1061
	ldr	r1, [r4, #1512]
	ldr	r0, [r4, #1508]
	cmp	r1, #0
	str	r1, [r4, #2100]
	str	r0, [r4, #2104]
	beq	.L955
	ldr	r3, [r4, #2092]
	cmp	r1, r3
	beq	.L955
.L984:
	mov	r8, #1
.L956:
	ldr	r3, .L1069+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L960
	ldr	lr, [r4, #2092]
	mov	r3, #8
	ldr	r5, [r4, #2096]
	sub	r2, fp, #116
	strh	r1, [fp, #-112]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-110]	@ movhi
	strh	lr, [fp, #-116]	@ movhi
	strh	r5, [fp, #-114]	@ movhi
	ldr	r0, [r4, #2496]
	blx	ip
.L960:
	sxtb	r8, r8
	cmp	r8, #1
	beq	.L1062
.L962:
	ldr	r2, [r4, #2100]
	ldr	r3, [r4, #2104]
	str	r2, [r4, #2092]
	str	r3, [r4, #2096]
.L954:
	add	r1, r6, #20992
	add	r0, r6, #21760
	ldr	r3, [r9, #52]
	mov	r2, #60
	add	r1, r1, #224
	add	r0, r0, #168
	blx	r3
	ldr	r1, .L1069+8
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [fp, #-124]
	rsb	r7, r7, r3
	ldr	r3, [r4, #2076]
	add	r10, r10, r7, lsl #3
	add	r3, r3, #1
	str	r3, [r4, #2076]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1049:
	mov	r2, r0, lsr #8
	add	r4, r6, #20480
	sub	r2, r2, #128
	mov	r0, #2
	cmp	r2, #3
	strb	r0, [r4, #805]
	ldrlsb	r3, [r1, #3584]	@ zero_extendqisi2
	orrls	r3, r3, r0
	strlsb	r3, [r1, #3584]
	b	.L926
.L955:
	cmp	r0, #0
	beq	.L957
	ldr	r3, [r4, #2096]
	cmp	r0, r3
	beq	.L1063
	cmp	r1, #0
	beq	.L984
	ldr	r3, [r4, #2092]
	cmp	r1, r3
	bne	.L984
	mov	r8, #1
	b	.L977
.L976:
	ldr	r1, [r8, #3704]
	cmp	r1, #0
	beq	.L948
	ldr	r2, [r8, #3708]
	cmp	r2, #0
	bne	.L1064
.L948:
	mov	r3, #0
	strb	r3, [r4, #2533]
	ldr	r3, [fp, #-120]
	cmp	r10, r3, asl #3
	bls	.L1065
.L950:
	ldr	r1, .L1069+12
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-124]
	ldr	r3, [r8, #3592]
	rsb	r7, r7, r2
	bic	r3, r3, #432
	mov	r10, r7, asl #3
	bic	r3, r3, #2
	str	r3, [r8, #3592]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1048:
	ldr	r3, [r9, #52]
	mov	r2, #32
	sub	r1, fp, #108
	sub	r0, fp, #76
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	mov	r4, r0
	sub	r0, fp, #76
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r4, r3
	bne	.L921
	ldr	r3, .L1069+4
	add	r4, r6, #20480
	mov	r2, #1
	strb	r2, [r4, #2532]
	ldr	r5, [r3]
	cmp	r5, r10
	beq	.L922
	mov	r3, r10
	mov	r2, r10
	mov	r1, #117
	ldr	r0, [r4, #2496]
	blx	r5
.L922:
	ldr	r3, [r8, #3592]
	add	r1, r6, #15680
	add	r1, r1, #32
	mov	r10, #0
	tst	r3, #130
	orrne	r3, r3, #32
	strne	r3, [r8, #3592]
	movne	r2, #1
	strne	r2, [r8, #3596]
	ldr	r0, [r4, #2496]
	bl	MP4_ClearCurPacket
	b	.L1045
.L921:
	add	r3, r6, #12288
	ldrb	r3, [r3, #3584]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L925
	add	r4, r6, #20480
	mov	r2, #2
	strb	r2, [r4, #805]
	b	.L926
.L942:
	ldr	r3, [fp, #-120]
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	add	r3, r7, #4
	str	r3, [fp, #-124]
	bl	MP4_ClearCurPacket
	b	.L945
.L1052:
	ldr	r1, .L1069+16
	mov	r0, #2
	bl	dprint_vfmw
	str	r10, [r4, #2108]
	mov	r1, r7
	ldr	r2, [fp, #-120]
	mov	r0, r6
	bl	Mp4_Syntax_Vos
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L957:
	ldr	r8, [r4, #2500]
	subs	r8, r8, #1
	movne	r8, #1
	cmp	r1, #0
	beq	.L960
.L978:
	ldr	r3, [r4, #2092]
	cmp	r1, r3
	bne	.L956
.L959:
	cmp	r0, #0
	beq	.L960
.L977:
	ldr	r3, [r4, #2096]
	cmp	r0, r3
	beq	.L960
	b	.L956
.L1056:
	ldr	r1, .L1069+20
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [fp, #-120]
	cmp	r3, #4
	beq	.L1066
	ldr	r2, [fp, #-120]
	mov	r1, r7
	mov	r0, r6
	bl	Mp4_Syntax_Vop
	ldr	r3, [r8, #3592]
	tst	r3, #2
	mov	r10, r0
	bne	.L938
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
.L937:
	mov	r2, r10
	ldr	r1, .L1069+24
	mov	r0, #7
	bl	dprint_vfmw
	b	.L931
.L1059:
	ldr	r3, [r4, #1512]
	cmp	r3, r1
	bne	.L967
	ldr	r5, [r4, #2500]
	subs	r5, r5, #1
	movne	r5, #1
	b	.L968
.L1053:
	ldr	r1, .L1069+28
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #1
	mov	r1, r7
	ldr	r2, [fp, #-120]
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Vo
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L1054:
	ldr	r1, .L1069+32
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #2
	ldr	r2, [fp, #-120]
	mov	r1, r7
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Vol
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	ldrb	r3, [r4, #1575]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L931
	ldrb	r3, [r4, #1576]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L931
	add	r1, r6, #20480
	add	r0, r6, #19968
	add	r1, r1, #132
	add	r0, r0, #40
	ldr	ip, [r9, #52]
	mov	r2, #604
	str	r3, [fp, #-124]
	blx	ip
	ldr	r3, [fp, #-124]
	strb	r3, [r4, #1575]
	strb	r3, [r4, #797]
	b	.L931
.L1051:
	ldr	r1, .L1069+36
	mov	r0, #2
	bl	dprint_vfmw
	add	r1, r6, #15680
	add	r1, r1, #32
	ldr	r0, [r4, #2496]
	bl	MP4_ClearCurPacket
	b	.L1045
.L1063:
	ldr	r8, [r4, #2500]
	subs	r8, r8, #1
	movne	r8, #1
	cmp	r1, #0
	beq	.L959
	b	.L978
.L1061:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L953
	ldr	r2, [r4, #1524]
	ldr	r3, [r4, #1516]
	ldr	r0, [r4, #1520]
	str	r2, [r4, #1528]
	add	r2, r2, r3
	str	r2, [r4, #1524]
	ldr	r3, [r8, #3696]
	ldr	r1, [r4, #1536]
	mla	r3, r3, r2, r0
	rsb	r2, r1, r3
	str	r2, [r4, #1540]
	str	r3, [r4, #1532]
	str	r3, [r4, #1536]
	b	.L954
.L1055:
	ldr	r1, .L1069+40
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #3
	mov	r1, r7
	ldr	r2, [fp, #-120]
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Gop
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L1064:
	mov	r0, r6
	bl	Frame_Init
	cmp	r0, #0
	beq	.L948
	ldr	r1, .L1069+44
	mov	r0, #0
	bl	dprint_vfmw
	b	.L948
.L1057:
	ldr	r1, .L1069+48
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-120]
	mov	r1, r7
	mov	r0, r6
	bl	Mp4_Syntax_ShortHeader
	ldr	r3, [r8, #3592]
	tst	r3, #2
	mov	r10, r0
	beq	.L1046
	mov	r1, #196
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L931
.L1058:
	ldr	r1, .L1069+52
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-120]
	mov	r1, r7
	mov	r0, r6
	bl	Mp4_Syntax_UserData
	mov	r10, r0
.L1046:
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	b	.L931
.L1062:
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r2, r0, #0
	beq	.L963
	ldr	r1, [r2, #544]
	add	r5, r2, #560
	ldr	r0, [r4, #2496]
	add	r3, r2, #576
	str	r2, [fp, #-128]
	str	r3, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r2, [fp, #-128]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #2496]
	add	r3, r2, #544
	str	r2, [fp, #-132]
	str	r3, [fp, #-128]
	bl	FreeUsdByDec
	ldr	r2, [fp, #-132]
	ldr	r0, [r4, #2496]
	ldr	r1, [r2, #560]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-120]
	ldr	r0, [r4, #2496]
	ldr	r1, [r3, #-8]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-128]
	mov	r0, #0
	mov	r1, #0
	mov	r2, r8
	strd	r0, [r3]
	ldr	r3, [fp, #-120]
	strd	r0, [r5, #-8]
	strd	r0, [r5]
	strd	r0, [r3, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r8
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L963:
	add	r5, r6, #22528
	mov	r3, #0
	add	r5, r5, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L964
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1067
.L964:
	ldr	r2, [r4, #2104]
	mov	r0, r6
	ldr	r1, [r4, #2100]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L962
	ldr	r1, .L1069+56
	mov	r0, #0
	bl	dprint_vfmw
	b	.L962
.L938:
	movw	r1, #438
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L953:
	ldr	r1, [r4, #1528]
	ldr	r2, [r4, #1516]
	ldr	r3, [r8, #3696]
	ldr	ip, [r4, #1520]
	add	r2, r2, r1
	ldr	r0, [r4, #1536]
	ldr	r1, [r4, #1540]
	mla	r3, r3, r2, ip
	rsb	r2, r0, r1
	add	r2, r2, r3
	str	r2, [r4, #1544]
	str	r3, [r4, #1532]
	b	.L954
.L1066:
	mov	r1, r5
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L1060:
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L972
	ldr	r1, [r7, #544]
	add	r3, r7, #576
	ldr	r0, [r4, #2496]
	add	r9, r7, #560
	str	r3, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r1, [r7, #552]
	add	r3, r7, #544
	ldr	r0, [r4, #2496]
	str	r3, [fp, #-124]
	bl	FreeUsdByDec
	ldr	r1, [r7, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r7, [fp, #-120]
	ldr	r0, [r4, #2496]
	ldr	r1, [r7, #-8]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-124]
	mov	r0, #0
	mov	r1, #0
	mov	r2, r5
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r5
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L972:
	add	r5, r6, #22528
	mov	r3, #0
	add	r5, r5, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L973
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1068
.L973:
	mov	r0, r6
	ldr	r2, [r4, #1508]
	ldr	r1, [r4, #1512]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L971
	ldr	r1, .L1069+60
	mov	r0, #0
	bl	dprint_vfmw
	b	.L971
.L1067:
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	bne	.L964
	mov	r0, r5
	bl	ResetVoQueue
	b	.L964
.L1068:
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	bne	.L973
	mov	r0, r5
	bl	ResetVoQueue
	b	.L973
.L1070:
	.align	2
.L1069:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC68
	.word	.LC70
	.word	.LC58
	.word	.LC62
	.word	.LC63
	.word	.LC59
	.word	.LC60
	.word	.LC57
	.word	.LC61
	.word	.LC66
	.word	.LC64
	.word	.LC65
	.word	.LC67
	.word	.LC69
	UNWIND(.fnend)
	.size	Mp4_Syntax_Parse, .-Mp4_Syntax_Parse
	.align	2
	.global	MP4_Combine_HdPacket
	.type	MP4_Combine_HdPacket, %function
MP4_Combine_HdPacket:
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
	add	r5, r0, #20480
	ldr	r3, [r5, #1632]
	cmp	r3, #0
	beq	.L1083
	add	r3, r0, #12288
	ldrb	r4, [r3, #3430]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1084
	cmp	r4, #0
	bne	.L1079
	ldrb	r2, [r3, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1079
	ldr	ip, .L1087
	add	r1, r0, #15744
	ldr	r2, [r5, #1648]
	add	r0, r0, #22016
	ldr	r3, [r3, #3440]
	add	r1, r1, #48
	ldr	ip, [ip, #52]
	add	r0, r0, #176
	add	r3, r3, r2
	mov	r2, #80
	str	r3, [r5, #1648]
	blx	ip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1084:
	ldrb	r4, [r5, #1638]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1085
	cmp	r4, #0
	bne	.L1078
	ldrb	r2, [r5, #1718]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1078
	ldr	r3, [r3, #3440]
	mov	r0, r4
	ldr	r2, [r5, #1728]
	add	r3, r3, r2
	str	r3, [r5, #1728]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1079:
	movw	r2, #5061
	ldr	r1, .L1087+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1085:
	ldr	r1, [r3, #3436]
	ldr	r2, [r5, #1644]
	cmp	r1, r2
	bcc	.L1086
	ldr	r3, [r3, #3440]
	mov	r0, #0
	ldr	r2, [r5, #1648]
	add	r3, r3, r2
	str	r3, [r5, #1648]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1078:
	movw	r2, #5047
	ldr	r1, .L1087+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1086:
	ldr	r3, .L1087
	add	r1, r0, #15680
	add	r0, r0, #22016
	add	r1, r1, #32
	mov	r2, #80
	add	r0, r0, #176
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #0
	strb	r4, [r5, #1718]
	mov	r0, r3
	strb	r3, [r5, #1638]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1083:
	ldr	r2, .L1087+8
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L1073
	ldr	r0, [r5, #2496]
	mov	r2, r3
	mov	r1, #103
	blx	ip
.L1073:
	ldr	r1, .L1087+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1088:
	.align	2
.L1087:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	.word	g_event_report
	.word	.LC71
	UNWIND(.fnend)
	.size	MP4_Combine_HdPacket, .-MP4_Combine_HdPacket
	.align	2
	.global	MP4_Renew_CurPacket
	.type	MP4_Renew_CurPacket, %function
MP4_Renew_CurPacket:
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
	bl	MP4_Combine_HdPacket
	cmn	r0, #1
	mov	r5, r0
	beq	.L1092
	ldr	r5, .L1093
	mov	r0, r4
	bl	MP4_Record_PacketID
	add	r1, r4, #22016
	add	r0, r4, #15680
	add	r1, r1, #96
	ldr	r3, [r5, #52]
	mov	r2, #160
	add	r0, r0, #32
	blx	r3
	add	r0, r4, #15744
	ldr	r3, [r5, #52]
	add	r1, r4, #22272
	mov	r2, #4
	add	r0, r0, #40
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1092:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	movw	r2, #5077
	ldr	r1, .L1093+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1094:
	.align	2
.L1093:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC72
	UNWIND(.fnend)
	.size	MP4_Renew_CurPacket, .-MP4_Renew_CurPacket
	.align	2
	.global	MP4_Check_CurPacket
	.type	MP4_Check_CurPacket, %function
MP4_Check_CurPacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #12288
	add	r5, r0, #20480
	mov	r3, #0
	ldr	r2, [r4, #3436]
	mov	r6, r0
	sub	r0, fp, #60
	str	r2, [r5, #1584]
	ldr	r1, [r4, #3424]
	str	r1, [r5, #1580]
	ldr	r2, [r4, #3440]
	str	r3, [r5, #1592]
	str	r2, [r5, #1588]
	bl	BsInit
	sub	r0, fp, #60
	mov	r1, #32
	bl	BsShow
	ldrb	r2, [r4, #3584]	@ zero_extendqisi2
	tst	r2, #1
	mov	r3, r0
	beq	.L1121
	mov	r3, #1
	strb	r3, [r5, #805]
	ldrb	r3, [r4, #3584]	@ zero_extendqisi2
	tst	r3, #2
	bne	.L1098
	ldr	r2, [r5, #2056]
	mov	r0, #196
.L1102:
	movw	r3, #438
	cmp	r0, r3
	cmpeq	r2, r3
	beq	.L1109
	cmp	r0, #196
	cmpeq	r2, #196
	bne	.L1119
.L1109:
	ldr	r3, [r5, #2064]
	cmp	r3, #1
	bgt	.L1101
	b	.L1119
.L1121:
	mov	r2, r0, lsr #8
	mov	r1, #2
	sub	r2, r2, #128
	strb	r1, [r5, #805]
	cmp	r2, #3
	bls	.L1122
.L1097:
	ldrb	r2, [r4, #3584]	@ zero_extendqisi2
	tst	r2, #2
	ldr	r2, [r5, #2056]
	bne	.L1100
	movw	r1, #438
	cmp	r2, r1
	cmpne	r3, #196
	beq	.L1102
.L1101:
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
.L1119:
	mov	r0, #0
.L1106:
	ldr	r3, [r4, #3424]
	cmp	r3, #0
	beq	.L1112
	ldr	r3, [r4, #3436]
	cmp	r3, #0
	mvneq	r0, #0
.L1118:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1100:
	movw	r1, #438
	sub	r3, r3, #196
	rsb	r2, r1, r2
	clz	r3, r3
	clz	r2, r2
	mov	r3, r3, lsr #5
	mov	r2, r2, lsr #5
	orrs	r1, r3, r2
	beq	.L1103
	ldrb	r0, [r5, #1577]	@ zero_extendqisi2
	cmp	r0, #1
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L1111
.L1103:
	mov	r0, r6
	bl	MP4_Renew_CurPacket
	b	.L1106
.L1098:
	ldr	r3, [r5, #2056]
	movw	r2, #438
	rsb	r2, r2, r3
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1111:
	ldr	r3, [r5, #2060]
	cmp	r3, #1
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r2, #0
	beq	.L1119
	ldr	r3, [r5, #1648]
	cmp	r3, #4
	bne	.L1119
	b	.L1103
.L1122:
	ldrb	r2, [r4, #3584]	@ zero_extendqisi2
	orr	r2, r2, r1
	strb	r2, [r4, #3584]
	b	.L1097
.L1112:
	mvn	r0, #0
	b	.L1118
	UNWIND(.fnend)
	.size	MP4_Check_CurPacket, .-MP4_Check_CurPacket
	.align	2
	.global	MPEG4DEC_Decode
	.type	MPEG4DEC_Decode, %function
MPEG4DEC_Decode:
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
	add	r4, r0, #20480
	mov	r6, r0
	mov	r5, r1
	ldr	r3, [r4, #2084]
	cmp	r3, #0
	beq	.L1124
	ldr	r3, [r1, #16]
	cmp	r3, #0
	beq	.L1124
	ldr	r3, [r1, #12]
	cmp	r3, #0
	beq	.L1124
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L1124
	ldr	r1, .L1230
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [r5, #12]
	ldr	r1, .L1230+4
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #16]
	ldr	r1, .L1230+8
	mov	r0, #7
	bl	dprint_vfmw
	ldrb	r2, [r5, #6]	@ zero_extendqisi2
	ldr	r1, .L1230+12
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #92]
	ldr	r1, .L1230+16
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #96]
	ldr	r1, .L1230+20
	mov	r0, #7
	bl	dprint_vfmw
	ldrb	r2, [r5, #86]	@ zero_extendqisi2
	ldr	r1, .L1230+24
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #16]
	ldr	r1, .L1230+28
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1230+32
	mov	r0, #7
	add	r8, r6, #15680
	ldrb	r2, [r3]	@ zero_extendqisi2
	add	r8, r8, #32
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1230+36
	mov	r0, #7
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1230+40
	mov	r0, #7
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1230+44
	mov	r0, #7
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, .L1230+48
	mov	r2, #160
	mov	r1, r5
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	mov	r0, r6
	bl	MP4_Check_CurPacket
	cmn	r0, #1
	mov	r7, r0
	beq	.L1216
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	add	r3, r6, #12288
	mov	r2, #0
	mov	r0, r6
	ldr	r1, [r3, #3436]
	str	r1, [r4, #1584]
	ldr	r1, [r3, #3424]
	str	r1, [r4, #1580]
	ldr	r3, [r3, #3440]
	str	r2, [r4, #1592]
	str	r3, [r4, #1588]
	bl	Mp4_Get_DecMode
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L1217
.L1128:
	add	r7, r6, #16384
	ldr	r3, [r7, #3592]
	str	r3, [r4, #2536]
.L1129:
	ldr	r2, [r4, #1588]
	mov	r0, r6
	ldr	r1, [r4, #1580]
	bl	Mp4_Syntax_Parse
	ldr	lr, [r4, #1596]
	ldr	ip, [r4, #1580]
	ldr	r2, [r4, #1584]
	ldr	r3, [r4, #1588]
	mov	r1, r0, lsr #3
	and	r0, r0, #7
	rsb	r3, r1, r3
	add	ip, ip, r1
	str	r0, [r4, #1592]
	add	r2, r1, r2
	str	ip, [r4, #1580]
	str	r2, [r4, #1584]
	str	r3, [r4, #1588]
	ldr	r3, [lr, #840]
	cmp	r3, #1
	beq	.L1218
.L1130:
	ldr	r3, [r7, #3592]
	tst	r3, #288
	beq	.L1131
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r7, #3592]
	ldr	r3, [r4, #1628]
	cmp	r3, #2
	beq	.L1219
	cmp	r3, #1
	beq	.L1220
	cmp	r3, #4
	bne	.L1134
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1136
	ldr	r3, [r4, #2112]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2112]
.L1134:
	mov	r0, r6
	bl	Mp4_Frame_Atr
	cmn	r0, #1
	mov	r7, r0
	beq	.L1221
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #2516]
	mov	r8, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	clz	r3, r8
	mov	r3, r3, lsr #5
	clz	r2, r0
	mov	ip, r0
	mov	r2, r2, lsr #5
	orrs	r9, r2, r3
	bne	.L1222
	ldrb	r1, [r4, #803]	@ zero_extendqisi2
	and	r10, r1, #253
	cmp	r10, #1
	beq	.L1223
	cmp	r1, #2
	beq	.L1224
.L1145:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1155
	ldr	r3, [r4, #2504]
	ldr	r1, [r4, #2508]
	cmp	r3, #0
	ldr	r3, [r4, #2516]
	movgt	r2, #2
	movle	r2, #1
	cmp	r1, r3
	str	r2, [r4, #2504]
	beq	.L1153
	mov	r2, #0
	ldr	r0, [r4, #2496]
	bl	FSP_SetRef
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_GetDisplay
	cmp	r0, #3
	beq	.L1213
	mov	r2, #0
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
.L1213:
	ldr	r3, [r4, #2516]
.L1153:
	str	r3, [r4, #2508]
	mov	r2, #1
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	strb	r3, [r6]
	ldr	r3, [r4, #2520]
	ldr	r1, [r4, #2524]
	str	r3, [r4, #2512]
	str	r1, [r4, #2516]
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	strb	r3, [r6, #1]
	ldr	r3, [r4, #1540]
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2520]
	bl	FSP_SetRef
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_RemovePmv
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L1155
	ldrb	r5, [r4, #800]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L1225
.L1166:
	mov	r7, #0
.L1208:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1223:
	cmp	r3, #0
	bne	.L1143
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L1145
	mov	r2, r10
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	mov	r0, r10
	ldr	r1, .L1230+52
	ldr	r3, [r3]
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1136:
	sub	r2, r3, #2
	tst	r2, #253
	bne	.L1139
	ldr	r2, [r4, #2112]
	cmp	r2, #2
	beq	.L1214
.L1139:
	cmp	r3, #1
	streq	r3, [r4, #2112]
	b	.L1134
.L1218:
	ldr	r3, [lr, #888]
	cmp	r3, #0
	beq	.L1130
	b	.L1166
.L1217:
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L1128
	ldr	r3, [r4, #2536]
	add	r7, r6, #16384
	str	r3, [r7, #3592]
	b	.L1129
.L1155:
	mov	r2, r5
	mov	r1, #0
	mov	r0, r6
	bl	Mp4_Set_DecPar
	ldrb	r7, [r4, #1448]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L1226
	ldr	r3, [r4, #2112]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2112]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #880]
	cmp	r2, #1
	beq	.L1165
.L1164:
	cmp	r2, #2
	beq	.L1171
.L1165:
	cmp	r7, #0
	mov	r3, #0
	strb	r3, [r6, #1198]
	bne	.L1166
	ldr	r3, .L1230+56
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1166
	sub	r2, fp, #44
	ldr	r0, [r4, #2496]
	mov	r3, #4
	mov	r1, #20
	str	r7, [r2, #-4]!
	blx	ip
	b	.L1208
.L1226:
	sub	r3, r7, #2
	sub	r9, r7, #2
	clz	r9, r9
	ands	r5, r3, #253
	mov	r9, r9, lsr #5
	bne	.L1159
	ldr	r3, [r4, #2112]
	cmp	r3, #2
	beq	.L1227
.L1159:
	cmp	r7, #1
	beq	.L1228
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #880]
	cmp	r2, #1
	bne	.L1164
	cmp	r3, #0
	moveq	r9, #0
	andne	r9, r9, #1
	cmp	r9, #0
	beq	.L1165
	mov	r3, #0
	str	r3, [r6, #1036]
	ldr	r1, [r4, #2524]
	mvn	r7, #0
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1219:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1134
.L1133:
	mov	r0, r6
	mvn	r7, #0
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1220:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L1134
	b	.L1133
.L1225:
	ldr	r1, .L1230+60
	mov	r0, #11
	bl	dprint_vfmw
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2508]
	mov	r8, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	cmp	r8, #0
	cmpne	r0, #0
	mov	r9, r0
	beq	.L1229
	ldr	r2, [r8, #28]
	cmp	r2, #0
	beq	.L1168
	ldr	r3, [r8, #32]
	cmp	r3, #0
	beq	.L1168
	ldr	r1, [r0, #28]
	mov	r0, r6
	ldr	r2, [r2, #8]
	mov	r7, #0
	cmp	r1, #0
	ldr	lr, [r4, #1508]
	ldr	ip, [r4, #1512]
	ldrne	r1, [r1, #8]
	moveq	r1, r2
	ldr	r3, [r3, #8]
	stmib	sp, {ip, lr}
	str	r1, [sp]
	mov	r1, r8
	bl	Vdm_Mem_Move
	b	.L1208
.L1228:
	str	r7, [r4, #2112]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #880]
	cmp	r2, #1
	beq	.L1162
	cmp	r2, #2
	beq	.L1171
.L1162:
	mov	r3, #0
	strb	r3, [r6, #1198]
	b	.L1166
.L1124:
	ldr	r1, .L1230+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1224:
	cmp	r3, #0
	bne	.L1146
	ldr	r3, [r4, #1596]
	ldr	r1, [r8, #152]
	ldr	r3, [r3]
	cmp	r1, r3
	bhi	.L1147
	cmp	r2, #0
	bne	.L1148
	ldr	r2, [r0, #152]
	cmp	r3, r2
	bcs	.L1145
.L1148:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	str	ip, [fp, #-56]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1596]
	ldr	ip, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1230+68
	ldr	r3, [r3]
	ldr	r2, [ip, #152]
	bl	dprint_vfmw
	b	.L1208
.L1147:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	mov	r0, #1
	ldr	r1, .L1230+72
	ldr	r3, [r3]
	bl	dprint_vfmw
	b	.L1208
.L1227:
	mov	r2, #1
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	ldr	r3, .L1230+56
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1214
	ldr	r0, [r4, #2496]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #127
	blx	ip
	mvn	r7, #0
	b	.L1208
.L1222:
	mov	r3, #3744
	ldr	r2, .L1230+76
	ldr	r1, .L1230+80
	mov	r0, #1
	bl	dprint_vfmw
.L1214:
	mvn	r7, #0
	b	.L1208
.L1171:
	ldr	r2, [r1, #884]
	cmp	r2, #0
	andgt	r9, r9, #1
	movle	r9, #0
	cmp	r3, #0
	moveq	r3, #0
	andne	r3, r9, #1
	cmp	r3, #0
	beq	.L1165
	mov	r3, #0
	mov	r2, #1
	str	r3, [r6, #1036]
	mvn	r7, #0
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #1596]
	mov	r0, r6
	ldr	r3, [r2, #884]
	add	r3, r3, r7
	str	r3, [r2, #884]
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1143:
	mov	r2, r10
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	mov	r0, r10
	movw	r3, #3758
	ldr	r2, .L1230+76
	ldr	r1, .L1230+84
	bl	dprint_vfmw
	b	.L1208
.L1216:
	ldr	r1, .L1230+88
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1208
.L1131:
	ldr	r1, .L1230+92
	mov	r0, #2
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L1208
.L1221:
	ldr	r1, .L1230+96
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1146:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	movw	r3, #3778
	ldr	r2, .L1230+76
	mov	r0, #1
	ldr	r1, .L1230+84
	bl	dprint_vfmw
	b	.L1208
.L1229:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r3, r8
	movw	r2, #3941
	ldr	r1, .L1230+100
	str	r9, [sp]
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1168:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	ldr	r2, [r8, #32]
	ldr	ip, [r4, #2516]
	mov	r0, #0
	ldr	r3, [r4, #2524]
	str	r2, [sp, #8]
	ldr	r1, [r8, #28]
	ldr	r2, [r4, #2508]
	str	ip, [sp]
	str	r1, [sp, #4]
	ldr	r1, .L1230+104
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1208
.L1231:
	.align	2
.L1230:
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	.word	.LC85
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC94
	.word	g_event_report
	.word	.LC89
	.word	.LC73
	.word	.LC96
	.word	.LC95
	.word	.LANCHOR1+1356
	.word	.LC88
	.word	.LC93
	.word	.LC86
	.word	.LC92
	.word	.LC87
	.word	.LC90
	.word	.LC91
	UNWIND(.fnend)
	.size	MPEG4DEC_Decode, .-MPEG4DEC_Decode
	.align	2
	.global	MPEG4DEC_GetImageWidth
	.type	MPEG4DEC_GetImageWidth, %function
MPEG4DEC_GetImageWidth:
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
	add	r0, r0, #20480
	ldr	r0, [r0, #1512]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageWidth, .-MPEG4DEC_GetImageWidth
	.align	2
	.global	MPEG4DEC_GetImageHeight
	.type	MPEG4DEC_GetImageHeight, %function
MPEG4DEC_GetImageHeight:
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
	add	r0, r0, #20480
	ldr	r0, [r0, #1508]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageHeight, .-MPEG4DEC_GetImageHeight
	.global	sprite_trajectory_len
	.global	default_inter_matrix
	.global	default_intra_matrix
	.global	scan_tables
	.section	.rodata
	.align	2
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
	.type	__FUNCTION__.14425, %object
	.size	__FUNCTION__.14425, 15
__FUNCTION__.14425:
	.ascii	"Mp4_Set_DecPar\000"
	.space	1
	.type	__FUNCTION__.14559, %object
	.size	__FUNCTION__.14559, 23
__FUNCTION__.14559:
	.ascii	"Mp4_Syntax_Slice_NotSH\000"
	.space	1
	.type	__FUNCTION__.14573, %object
	.size	__FUNCTION__.14573, 20
__FUNCTION__.14573:
	.ascii	"Mp4_Syntax_Slice_SH\000"
	.type	__FUNCTION__.14588, %object
	.size	__FUNCTION__.14588, 14
__FUNCTION__.14588:
	.ascii	"MP4_Dec_Slice\000"
	.space	2
	.type	__FUNCTION__.14462, %object
	.size	__FUNCTION__.14462, 16
__FUNCTION__.14462:
	.ascii	"MPEG4DEC_Decode\000"
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	sprite_trajectory_len, %object
	.size	sprite_trajectory_len, 120
sprite_trajectory_len:
	.word	0
	.byte	2
	.space	3
	.word	2
	.byte	3
	.space	3
	.word	3
	.byte	3
	.space	3
	.word	4
	.byte	3
	.space	3
	.word	5
	.byte	3
	.space	3
	.word	6
	.byte	3
	.space	3
	.word	14
	.byte	4
	.space	3
	.word	30
	.byte	5
	.space	3
	.word	62
	.byte	6
	.space	3
	.word	126
	.byte	7
	.space	3
	.word	254
	.byte	8
	.space	3
	.word	510
	.byte	9
	.space	3
	.word	1022
	.byte	10
	.space	3
	.word	2046
	.byte	11
	.space	3
	.word	4094
	.byte	12
	.space	3
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"fatal stream error --- GOP marker_bit = 0\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"DivX%4dBuild%4d%c\000" )
	.space	2
.LC2:
	ASCII(.ascii	"DivX%4db%4d%c\000" )
	.space	2
.LC3:
	ASCII(.ascii	"FFmpe%*[^b]b%4d\000" )
.LC4:
	ASCII(.ascii	"FFmpeg v%4d.%4d.%4d / libavcodec build: %d\000" )
	.space	1
.LC5:
	ASCII(.ascii	"Lavc%d.%d.%d\000" )
	.space	3
.LC6:
	ASCII(.ascii	"ffmpeg\000" )
	.space	1
.LC7:
	ASCII(.ascii	"XviD%4d\000" )
.LC8:
	ASCII(.ascii	"fatal stream error --- VOP marker_bit = 0\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"VDH doesn't support SPRITE_STATIC & SPRITE_GMC\012\000" )
.LC10:
	ASCII(.ascii	"VDH doesn't support SPRITE_STATIC\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"Unknown sprite_enable\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"ERROR: not_8_bit !=0\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"not support no complexity_estimation_disable\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"not support data_partitioned\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"not support newpred_enable\012\000" )
.LC16:
	ASCII(.ascii	"not support reduced_resolution_vop_eanble\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"not support scalability\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"warning! profile_and_level_indication=%#x, maybe HD" )
	ASCII(.ascii	" pic...\012\000" )
.LC19:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC20:
	ASCII(.ascii	"actual frame size(%dx%d) exeed max config(%dx%d)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC21:
	ASCII(.ascii	"MPEG4 Frame_Init return err!\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"MPEG4 Frame_Init PmvNum=%d, FrameNum=%d, error!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC23:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"%s %d  abnormal!\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"MPEG4DEC Init  -----\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC31:
	ASCII(.ascii	"MPEG4DEC Init success -----\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"MPEG4 destroy\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"NVOP VDM copy process................\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"vop_coding_type = %d is not expected!\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	" slice num %d is not extpected!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	" line %d packet is wrong!\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"FrameNum=%d\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"vop_coding_type=%d\012\000" )
.LC40:
	ASCII(.ascii	"line: %d pToQueImg is null!\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"CurImage %d is already out put\012\000" )
.LC42:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"StreamIDNum = %d > (%d)\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"Warning : vop slice num %d != 0\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"warning streamIDNum %d != 0 \012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"vop ---%d\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"VDH doesn't support S_VOP\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"parse time_module_base stream not enough\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	"module time base parse error, more than %d '1' was " )
	ASCII(.ascii	"found!\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"error: vop_coding_type = %d, but vop_fcode_forward " )
	ASCII(.ascii	"= 0\012\000" )
.LC51:
	ASCII(.ascii	"error: B vop, but vop_fcode_backward = 0\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"FUN: %s Invalid SlcNum = %d\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	" pSlcPara->mb_start_num = %d, MbCnt = %d\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"pSlcPara->mb_start_num = %d, totalMbMin1 = %d\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"FUN: %s MP4_ClearCurPacket\012\000" )
.LC56:
	ASCII(.ascii	"pCtx is NUL!!!\012\000" )
.LC57:
	ASCII(.ascii	"Not find start code \012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"VOS beginning ~ !\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"VO beginning ~ !\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"VOL beginning ~ !\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"GOP beginning ~ !\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"VOP beginning ~ !\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"BitUsed=%d\012\000" )
.LC64:
	ASCII(.ascii	"SHVOP beginning ~ !\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"USERDATA beginning ~ !\012\000" )
.LC66:
	ASCII(.ascii	"MPEG4 Frame_Init return err 3!\012\000" )
.LC67:
	ASCII(.ascii	"MPEG4 Frame_Init return err 1!\012\000" )
.LC68:
	ASCII(.ascii	"vop right\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"MPEG4 Frame_Init return err 2!\012\000" )
.LC70:
	ASCII(.ascii	"bits over boundary\012\000" )
.LC71:
	ASCII(.ascii	"pLastPacket->StreamPack[0].VirAddr is NULL!!\012\000" )
	.space	2
.LC72:
	ASCII(.ascii	"line %d MP4_Combine_HdPacket failed!!\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"bitsream para error -----\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"MPEG4DEC Decode -----\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"ptr_strm_para->PhyAddr0=0x%x\012\000" )
	.space	2
.LC76:
	ASCII(.ascii	"ptr_strm_para->Length0=%d\012\000" )
	.space	1
.LC77:
	ASCII(.ascii	"ptr_strm_para->IsLastSeg0=%d\012\000" )
	.space	2
.LC78:
	ASCII(.ascii	"ptr_strm_para->PhyAddr1=0x%x\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"ptr_strm_para->Length1=%d\012\000" )
	.space	1
.LC80:
	ASCII(.ascii	"ptr_strm_para->IsLastSeg1=%d\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"ptr_strm_para->Length0 = %d\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"byte0: = 0x%x\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"byte1: = 0x%x\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"byte2: = 0x%x\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"byte3: = 0x%x\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"MP4_Check_CurPacket failed!\012\000" )
	.space	3
.LC87:
	ASCII(.ascii	"Mp4_Frame_Atr return fail\012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"fuction return value is null, %s %d!!\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"NVOP mem move--\012\000" )
	.space	3
.LC90:
	ASCII(.ascii	"line: %d pCur = %p, pFwd = %p\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"CurFsID(f%d,%d,b%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"bits not enought\012\000" )
	.space	2
.LC93:
	ASCII(.ascii	"fuction return value is null,%s %d!!\012\000" )
	.space	2
.LC94:
	ASCII(.ascii	"dec P/S frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000" )
.LC96:
	ASCII(.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
	.type	MemArrange.14363, %object
	.size	MemArrange.14363, 1232
MemArrange.14363:
	.space	1232
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
