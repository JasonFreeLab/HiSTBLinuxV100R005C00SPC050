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
	.file	"vdm_hal_mpeg2.c"
	.text
	.align	2
	.global	MP2HAL_V4R3C1_InitHal
	.type	MP2HAL_V4R3C1_InitHal, %function
MP2HAL_V4R3C1_InitHal:
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
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_InitHal, .-MP2HAL_V4R3C1_InitHal
	.align	2
	.global	MP2HAL_V4R3C1_WriteSliceMsg
	.type	MP2HAL_V4R3C1_WriteSliceMsg, %function
MP2HAL_V4R3C1_WriteSliceMsg:
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
	mov	lr, r0
	add	ip, r0, #45056
	str	r0, [fp, #-72]
	ldr	r0, [r0, #268]
	mov	r7, r1
	mov	r5, r2
	str	r3, [fp, #-60]
	cmp	r0, #0
	ldr	r10, [ip, #236]
	add	r9, lr, #236
	mov	r4, #0
	bne	.L27
.L3:
	cmp	r10, #0
	ble	.L24
	mov	r3, r0, asl #5
	mov	r4, #0
	str	r3, [fp, #-64]
	add	r3, r3, r5
	str	r3, [fp, #-68]
.L19:
	cmp	r4, #0
	mov	r5, #44
	mla	r5, r5, r4, r9
	ble	.L8
	ldr	r1, [r5, #32]
	ldr	r2, [r5, #-12]
	cmp	r1, r2
	bls	.L9
.L8:
	ldr	ip, [r5]
	mov	r8, #0
	ldr	r2, [r5, #16]
	mov	r0, r8
	and	lr, ip, #15
	ldr	r6, [r5, #8]
	ldr	r3, [fp, #-64]
	mov	r1, #0
	add	r2, r2, lr, lsl #3
	bfi	r0, r6, #0, #24
	bfi	r1, r2, #0, #7
	str	r0, [fp, #-48]
	strb	r1, [fp, #-45]
	add	r6, r3, r4, lsl #3
	ldr	r2, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L28
	add	r4, r4, #1
	str	ip, [fp, #-56]
	str	r2, [r7, r6, asl #2]
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	ip, [fp, #-56]
	ldr	r3, [fp, #-60]
	mov	lr, r8
	bic	ip, ip, #15
	ldr	r1, .L28+4
	rsb	ip, r3, ip
	mov	r0, #4
	bfi	lr, ip, #0, #24
	str	lr, [r7, r6, asl #2]
	str	lr, [fp, #-48]
	mov	r6, r6, asl #2
	mov	r2, lr
	bl	dprint_vfmw
	ldr	ip, [r5, #4]
	ldr	r2, [r5, #20]
	mov	r0, r8
	and	lr, ip, #15
	ldr	r1, [r5, #12]
	str	ip, [fp, #-56]
	add	r2, r2, lr, lsl #3
	bfi	r0, r1, #0, #24
	mov	r1, #0
	str	r0, [fp, #-48]
	bfi	r1, r2, #0, #7
	strb	r1, [fp, #-45]
	ldr	r2, [fp, #-48]
	add	lr, r6, #4
	ldr	r1, .L28+8
	mov	r0, #4
	str	r2, [r7, lr]
	bl	dprint_vfmw
	ldr	r2, [r5, #4]
	ldr	ip, [fp, #-56]
	mov	r0, #4
	cmp	r2, r8
	ldr	r1, .L28+12
	bicne	ip, ip, #15
	streq	r2, [fp, #-48]
	ldrne	r3, [fp, #-60]
	rsbne	ip, r3, ip
	bfine	r8, ip, #0, #24
	strne	r8, [fp, #-48]
	ldr	r2, [fp, #-48]
	add	ip, r6, #8
	mov	r8, #0
	str	r2, [r7, ip]
	bl	dprint_vfmw
	ldr	r2, [r5, #40]
	ldr	r1, [r5, #36]
	add	ip, r6, #12
	and	r2, r2, #63
	str	r8, [fp, #-48]
	bfi	r2, r1, #6, #1
	strb	r2, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L28+16
	str	r2, [r7, ip]
	bl	dprint_vfmw
	ldr	r1, [r5, #32]
	add	r2, r6, #16
	mov	r0, #4
	bfi	r8, r1, #0, #20
	ldr	r1, .L28+20
	str	r8, [r7, r2]
	mov	r2, r8
	str	r8, [fp, #-48]
	bl	dprint_vfmw
	cmp	r10, r4
	ble	.L12
	mov	r2, #44
	ldr	r1, [r5, #32]
	mul	r2, r2, r4
	add	r0, r9, r2
	ldr	r0, [r0, #32]
	cmp	r1, r0
	bcc	.L12
	sub	r2, r2, #44
	add	r2, r9, r2
	b	.L13
.L15:
	ldr	r3, [r2, #76]
	cmp	r3, r1
	bhi	.L17
.L13:
	add	r4, r4, #1
	add	r2, r2, #44
	cmp	r10, r4
	bne	.L15
.L21:
	ldr	r3, [fp, #-72]
	mov	r8, #0
	mov	r5, r8
	ldrh	r1, [r3, #150]
	ldrh	r2, [r3, #146]
	mul	r2, r2, r1
	sub	r2, r2, #1
.L18:
	add	r0, r6, #20
	mov	ip, #0
	bfi	ip, r2, #0, #20
	add	r6, r6, #24
	str	ip, [r7, r0]
	mov	r0, #4
	mov	r2, ip
	ldr	r1, .L28+24
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	mov	r2, r5
	ldr	r1, .L28+28
	str	r8, [r7, r6]
	mov	r0, #4
	str	r5, [fp, #-48]
	bl	dprint_vfmw
	sub	r4, r4, #1
.L9:
	add	r4, r4, #1
	cmp	r10, r4
	bgt	.L19
.L24:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L12:
	cmp	r10, r4
	beq	.L21
.L17:
	mov	r2, #44
	ldr	r3, [fp, #-68]
	mla	r2, r2, r4, r9
	add	r5, r3, r4, lsl #5
	mov	r8, r5
	ldr	r2, [r2, #32]
	sub	r2, r2, #1
	b	.L18
.L27:
	ldr	r6, [lr, #236]
	mov	r8, lr
	ldr	r2, [lr, #252]
	mov	r1, #1
	and	lr, r6, #15
	str	r1, [fp, #-48]
	mov	ip, #0
	ldr	r1, .L28
	add	r2, r2, lr, lsl #3
	mov	r0, #4
	bfi	ip, r2, #0, #7
	strb	ip, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r7]
	bl	dprint_vfmw
	ldr	r3, [fp, #-60]
	bic	r1, r6, #15
	mov	ip, r4
	rsb	r1, r3, r1
	mov	r0, #4
	bfi	ip, r1, #0, #24
	ldr	r1, .L28+4
	str	ip, [r7, #4]
	mov	r2, ip
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	r6, [r8, #240]
	ldr	r2, [r8, #256]
	mov	ip, #0
	and	lr, r6, #15
	str	r4, [fp, #-48]
	ldr	r1, .L28+8
	mov	r0, #4
	add	r2, r2, lr, lsl #3
	bfi	ip, r2, #0, #7
	strb	ip, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r7, #8]
	bl	dprint_vfmw
	ldr	r2, [r8, #240]
	mov	r3, r8
	ldr	r1, .L28+12
	cmp	r2, r4
	mov	r0, #4
	bicne	r2, r6, #15
	streq	r2, [fp, #-48]
	ldrne	r3, [fp, #-60]
	rsbne	r2, r3, r2
	bfine	r4, r2, #0, #24
	strne	r4, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r4, #0
	str	r2, [r7, #12]
	bl	dprint_vfmw
	ldr	r6, [fp, #-72]
	str	r4, [fp, #-48]
	mov	r0, #4
	ldr	r2, [r6, #276]
	ldr	r1, [r6, #272]
	and	r2, r2, #63
	bfi	r2, r1, #6, #1
	strb	r2, [fp, #-48]
	ldr	r2, [fp, #-48]
	ldr	r1, .L28+16
	str	r2, [r7, #16]
	bl	dprint_vfmw
	mov	ip, r4
	bfi	ip, r4, #0, #20
	ldr	r1, .L28+20
	str	ip, [r7, #20]
	mov	r0, #4
	mov	r2, ip
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, [r6, #268]
	mov	r2, r4
	ldr	r1, .L28+24
	sub	ip, ip, #1
	mov	r0, #4
	bfi	r2, ip, #0, #20
	str	r2, [r7, #24]
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	add	r2, r5, #32
	mov	r0, #1
	str	r2, [r7, #28]
	b	.L3
.L29:
	.align	2
.L28:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_WriteSliceMsg, .-MP2HAL_V4R3C1_WriteSliceMsg
	.align	2
	.global	MP2HAL_V4R3C1_MakeReg
	.type	MP2HAL_V4R3C1_MakeReg, %function
MP2HAL_V4R3C1_MakeReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrh	r6, [r2, #150]
	mov	r4, #3
	ldrh	r3, [r2, #146]
	mov	lr, #1
	ldr	r5, [r0, #8]
	mov	ip, #0
	mul	r3, r3, r6
	ldr	r6, [r5]
	sub	r3, r3, #1
	bfi	r6, r3, #0, #20
	str	r6, [r5]
	ldr	r5, [r0, #8]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	orr	r3, r3, #64
	strb	r3, [r5, #3]
	ldr	r3, [r0, #8]
	ldrb	r5, [r3, #3]	@ zero_extendqisi2
	bfc	r5, #7, #1
	strb	r5, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	r5, [r3]	@ zero_extendqisi2
	bfi	r5, r4, #0, #4
	strb	r5, [r3]
	ldr	r4, [r0, #12]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	orr	r3, r3, #64
	strb	r3, [r4, #1]
	ldr	r3, [r0, #12]
	ldrb	r4, [r3, #1]	@ zero_extendqisi2
	bfc	r4, #7, #1
	strb	r4, [r3, #1]
	ldr	r3, [r0, #12]
	ldrh	r4, [r3, #2]
	bfi	r4, lr, #0, #12
	strh	r4, [r3, #2]	@ movhi
	ldr	lr, [r0, #12]
	ldrb	r3, [lr, #3]	@ zero_extendqisi2
	orr	r3, r3, #32
	strb	r3, [lr, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #7, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #4, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #6, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #60]
	ldrb	lr, [r3]	@ zero_extendqisi2
	bfc	lr, #0, #1
	strb	lr, [r3]
	ldr	r3, [r0, #56]
	str	ip, [r3]
	ldr	r3, [r0, #56]
	ldr	lr, [r2, #196]
	ldrb	ip, [r3]	@ zero_extendqisi2
	bfi	ip, lr, #0, #2
	strb	ip, [r3]
	ldr	r3, [r0, #56]
	ldr	lr, [r2, #192]
	ldrb	ip, [r3]	@ zero_extendqisi2
	bfi	ip, lr, #2, #2
	strb	ip, [r3]
	ldr	ip, [r0, #16]
	ldr	r3, [r1, #56]
	bic	r3, r3, #15
	str	r3, [ip]
	ldr	ip, [r0, #20]
	ldr	r3, [r1, #40]
	bic	r3, r3, #15
	str	r3, [ip]
	ldr	r1, [r0, #28]
	ldr	r3, [r2, #188]
	bic	r3, r3, #255
	str	r3, [r1]
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	ldrh	lr, [r2, #146]
	sub	r1, r1, #1
	ldr	ip, [r0, #32]
	cmp	r1, #1
	ldrh	r1, [r2, #150]
	movls	r3, #2
	movhi	r3, #1
	mul	r3, r3, lr
	str	r1, [ip]
	ldrh	r1, [r2, #150]
	ldr	ip, [r0, #36]
	mul	r3, r1, r3
	mov	r3, r3, asl #8
	str	r3, [ip]
	ldr	r3, [r2, #172]
	cmp	r3, #0
	ldreq	ip, [r2, #160]
	ldrne	ip, [r2, #164]
	ldreq	r1, [r0, #24]
	ldreq	r3, [r2, #152]
	ldrne	r1, [r0, #24]
	mov	r0, #0
	ldrne	r3, [r2, #156]
	add	r3, r3, ip, lsr #3
	bic	r3, r3, #15
	str	r3, [r1]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_MakeReg, .-MP2HAL_V4R3C1_MakeReg
	.align	2
	.global	MP2HAL_V4R3C1_MakeDnMsg
	.type	MP2HAL_V4R3C1_MakeDnMsg, %function
MP2HAL_V4R3C1_MakeDnMsg:
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
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldrh	r3, [r2, #150]
	mov	r4, r2
	mov	r6, r0
	cmp	r3, #512
	mov	r5, r1
	ldrhi	r3, .L60
	bhi	.L57
	ldrh	r2, [r2, #146]
	cmp	r2, #512
	bhi	.L58
	ldr	r2, [r0]
	sub	r3, r3, #1
	ldrh	r1, [r2]
	bfi	r1, r3, #0, #9
	strh	r1, [r2]	@ movhi
	ldr	r2, [r0]
	ldrh	r3, [r4, #146]
	ldrh	r1, [r2, #2]
	sub	r3, r3, #1
	bfi	r1, r3, #0, #9
	strh	r1, [r2, #2]	@ movhi
	ldr	r3, [r0]
	ldr	r1, [r4, #176]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #1, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #0, #2
	strb	r2, [r3, #1]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #2, #1
	strb	r2, [r3, #1]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #2]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #3
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	bfi	r2, r1, #3, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #4, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #15]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #14]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #1]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #13]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #2]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #12]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #6]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #7, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #2
	strb	r2, [r3]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #1]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #2]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #3]
	ldr	r2, [r0, #16]
	ldr	r3, [r4, #180]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #20]
	ldr	r3, [r4, #184]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #24]
	ldr	r3, [r4, #200]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #28]
	ldr	r3, [r4, #224]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r0, [r4, #152]
	bl	MEM_Phy2Vir
	mov	r7, r0
	ldr	r0, [r4, #156]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #172]
	cmp	r1, #0
	mov	r9, r0
	beq	.L59
	ldr	r2, [r4, #160]
	cmp	r7, #0
	ldr	r8, [r4, #164]
	ldr	r1, [r4, #156]
	ldr	r0, [r6, #32]
	ldr	r3, [r4, #152]
	add	r8, r1, r8, lsr #3
	bic	lr, r8, #15
	add	r3, r3, r2, lsr #3
	ldr	ip, [r0]
	bic	r1, r3, #15
	and	r2, r3, #15
	rsb	r3, lr, r1
	bfi	ip, r3, #0, #24
	str	ip, [r0]
	ldr	r3, [r6, #36]
	ldr	r0, [r4, #168]
	ldr	r1, [r3]
	bfi	r1, r0, #0, #24
	str	r1, [r3]
	ldr	r1, [r6, #36]
	ldr	r3, [r4, #160]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r3, r3, r2, lsl #3
	bfi	r0, r3, #0, #7
	strb	r0, [r1, #3]
	beq	.L42
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L60+4
	add	ip, r7, r3, lsr #3
	ldrb	r2, [r7, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L60+8
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r7, r3
	ldrb	r2, [r7, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #152]
	mov	r0, #22
	ldr	r1, .L60+12
	add	r2, r2, r3
	bl	dprint_vfmw
.L42:
	ldr	r3, [r6, #40]
	and	r8, r8, #15
	cmp	r9, #0
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r2, [r6, #44]
	ldr	r3, [r4, #172]
	ldr	r1, [r2]
	add	r3, r3, #24
	bfi	r1, r3, #0, #24
	str	r1, [r2]
	ldr	r2, [r6, #44]
	ldr	r3, [r4, #164]
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r8, r3, r8, lsl #3
	bfi	r1, r8, #0, #7
	strb	r1, [r2, #3]
	beq	.L41
	ldr	r3, [r4, #164]
	mov	r0, #8
	ldr	r1, .L60+16
	add	ip, r9, r3, lsr #3
	ldrb	r2, [r9, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #172]
	ldr	r3, [r4, #164]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L60+20
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r9, r3
	ldrb	r2, [r9, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L41:
	add	r7, r6, #64
	mov	r1, r6
.L45:
	mov	ip, r4
	mov	r3, r1
	mov	r2, #2
.L43:
	ldr	r0, [r3, #48]
	subs	r2, r2, #1
	ldrb	lr, [ip, #80]	@ zero_extendqisi2
	add	r3, r3, #4
	add	ip, ip, #8
	strb	lr, [r0]
	ldr	r0, [r3, #44]
	ldrb	lr, [ip, #88]	@ zero_extendqisi2
	strb	lr, [r0, #1]
	ldr	r0, [r3, #44]
	ldrb	lr, [ip, #104]	@ zero_extendqisi2
	strb	lr, [r0, #2]
	ldr	r0, [r3, #44]
	ldrb	lr, [ip, #120]	@ zero_extendqisi2
	strb	lr, [r0, #3]
	ldr	r0, [r3, #172]
	ldrb	lr, [ip, #8]	@ zero_extendqisi2
	strb	lr, [r0]
	ldr	r0, [r3, #172]
	ldrb	lr, [ip, #24]	@ zero_extendqisi2
	strb	lr, [r0, #1]
	ldr	r0, [r3, #172]
	ldrb	lr, [ip, #40]	@ zero_extendqisi2
	strb	lr, [r0, #2]
	ldr	r0, [r3, #172]
	ldrb	lr, [ip, #56]	@ zero_extendqisi2
	strb	lr, [r0, #3]
	bne	.L43
	add	r1, r1, #8
	add	r4, r4, #1
	cmp	r1, r7
	bne	.L45
	ldr	r1, [r6, #304]
	mov	r0, r2
	ldr	r3, [r5, #1148]
	bic	r3, r3, #15
	str	r3, [r1]
.L56:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L59:
	ldr	r0, [r6, #32]
	cmp	r7, #0
	ldr	r2, [r4, #160]
	ldr	r3, [r4, #152]
	ldr	ip, [r0]
	add	r3, r3, r2, lsr #3
	bfi	ip, r1, #0, #24
	str	ip, [r0]
	ldr	r1, [r6, #36]
	and	r2, r3, #15
	ldr	r3, [r4, #168]
	ldr	r0, [r1]
	add	r3, r3, #24
	bfi	r0, r3, #0, #24
	str	r0, [r1]
	ldr	r1, [r6, #36]
	ldr	r3, [r4, #160]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r3, r3, r2, lsl #3
	bfi	r0, r3, #0, #7
	strb	r0, [r1, #3]
	beq	.L40
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L60+24
	add	ip, r7, r3, lsr #3
	ldrb	r2, [r7, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L60+28
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r7, r3
	ldrb	r2, [r7, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L40:
	ldr	r3, [r6, #40]
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r3, [r6, #44]
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r3, [r6, #44]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfc	r2, #0, #7
	strb	r2, [r3, #3]
	b	.L41
.L58:
	ldr	r3, .L60+32
.L57:
	mov	r0, #0
	ldr	r2, .L60+36
	ldr	r1, .L60+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L56
.L61:
	.align	2
.L60:
	.word	.LC8
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC11
	.word	.LC12
	.word	.LC10
	.word	.LANCHOR0
	.word	.LC9
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_MakeDnMsg, .-MP2HAL_V4R3C1_MakeDnMsg
	.align	2
	.global	MP2HAL_V4R3C1_CfgReg
	.type	MP2HAL_V4R3C1_CfgReg, %function
MP2HAL_V4R3C1_CfgReg:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
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
	subs	r5, r2, #0
	mov	r7, r0
	mov	r8, r1
	mov	r0, #0
	str	r3, [fp, #-56]
	ldr	r6, [fp, #4]
	str	r0, [fp, #-48]
	bgt	.L89
	beq	.L78
	cmp	r5, #1
	moveq	r0, #0
	movteq	r0, 63941
	bne	.L90
.L66:
	ldr	r3, [r8]
	cmp	r3, #0
	beq	.L91
.L68:
	ldrh	lr, [r7, #150]
	mov	r3, r6
	ldrh	ip, [r7, #146]
	mov	r2, r5
	ldr	r1, [fp, #-48]
	mov	r0, #8
	mov	r10, #3
	add	r9, r7, #45056
	mul	ip, ip, lr
	mov	r4, #0
	sub	ip, ip, #1
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-48]
	ubfx	ip, r1, #16, #8
	mov	r1, r1, lsr #24
	orr	ip, ip, #64
	and	r1, r1, #62
	bfc	ip, #7, #1
	orr	r1, r1, #65
	strb	ip, [fp, #-46]
	bfc	r1, #1, #1
	strb	r1, [fp, #-45]
	ldr	ip, [fp, #-48]
	mov	r1, ip
	str	ip, [fp, #-60]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-60]
	ldr	r1, .L92
	mov	r0, r10
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r1, [r9, #244]
	mov	r2, #0
	strh	r10, [fp, #-46]	@ movhi
	mov	r3, r2
	bfi	r2, r1, #4, #1
	bfi	r3, r4, #4, #1
	and	r2, r2, #16
	strb	r3, [fp, #-45]
	orr	r2, r2, #64
	ldr	r0, [r9, #240]
	uxtb	r1, r3
	bfi	r2, r4, #7, #1
	strb	r10, [fp, #-48]
	strb	r2, [fp, #-47]
	bfi	r1, r0, #6, #1
	strb	r1, [fp, #-45]
	mov	r3, r6
	ldr	ip, [fp, #-48]
	mov	r2, r5
	mov	r0, #12
	mov	r1, ip
	str	ip, [fp, #-60]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-60]
	ldr	r1, .L92+4
	mov	r0, r10
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r1, [r8, #56]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #16
	bl	MFDE_ConfigReg
	ldr	r1, [r8, #40]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #20
	bl	MFDE_ConfigReg
	ldr	r1, [r9, #236]
	str	r4, [fp, #-48]
	cmp	r1, r4
	beq	.L76
	mov	r3, r7
	mvn	ip, #0
.L77:
	ldr	r2, [r3, #236]
	cmp	r2, #0
	beq	.L72
	ldr	r0, [r3, #244]
	bic	r2, r2, #15
	cmp	r0, #0
	ble	.L72
	cmp	ip, r2
	movcs	ip, r2
.L72:
	ldr	r2, [r3, #240]
	cmp	r2, #0
	beq	.L70
	ldr	r0, [r3, #248]
	bic	r2, r2, #15
	cmp	r0, #0
	ble	.L70
	cmp	ip, r2
	movcs	ip, r2
.L70:
	add	r4, r4, #1
	add	r3, r3, #44
	cmp	r4, r1
	bne	.L77
	cmn	ip, #1
	beq	.L76
	ldr	r3, [fp, #-56]
	mov	r1, ip
	mov	r2, r5
	mov	r0, #24
	str	ip, [fp, #-48]
	mov	r4, #0
	str	ip, [r3]
	mov	r3, r6
	bl	MFDE_ConfigReg
	ldrh	r1, [r7, #150]
	mov	r3, r6
	mov	r2, r5
	cmp	r1, #120
	mov	r0, #4
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #60
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #64
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #68
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #72
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #76
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #80
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #84
	movt	r1, 48
	bl	MFDE_ConfigReg
	ldr	r1, [r7, #188]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #96
	bl	MFDE_ConfigReg
	ldr	r1, [r7, #208]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	bl	MFDE_ConfigReg
	mov	r3, r6
	ldr	r1, [r7, #212]
	mov	r2, r5
	mov	r0, #104
	bl	MFDE_ConfigReg
	ldr	r2, [r7, #212]
	ldr	r1, .L92+8
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r2, [r7, #196]
	ldr	r1, [r7, #192]
	mov	r3, r6
	and	r2, r2, #3
	str	r4, [fp, #-48]
	bfi	r2, r1, #2, #2
	strb	r2, [fp, #-48]
	ldr	r8, [fp, #-48]
	mov	r2, r5
	mov	r0, #148
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L92+12
	mov	r0, #3
	bl	dprint_vfmw
	str	r4, [fp, #-48]
	mov	r3, #0
	bfi	r3, r4, #0, #1
	strb	r3, [fp, #-48]
	mov	r2, r5
	mov	r3, r6
	ldr	r1, [fp, #-48]
	mov	r0, #152
	bl	MFDE_ConfigReg
	ldr	r7, [r7, #220]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #108
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L92+16
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, #32
	mov	r3, r6
	mov	r2, r5
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, r4
.L87:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L90:
	ldr	r1, .L92+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L78:
	mov	r0, #0
	movt	r0, 63683
	b	.L66
.L89:
	str	r0, [sp]
	mov	r3, r5
	ldr	r2, .L92+24
	ldr	r1, .L92+28
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L91:
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L69
	str	r3, [r8]
	b	.L68
.L76:
	mvn	r2, #0
	ldr	r1, .L92+32
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r2, [fp, #-56]
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r2]
	b	.L87
.L69:
	ldr	r1, .L92+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L87
.L93:
	.align	2
.L92:
	.word	.LC25
	.word	.LC26
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC19
	.word	.LANCHOR0+24
	.word	.LC18
	.word	.LC21
	.word	.LC20
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_CfgReg, .-MP2HAL_V4R3C1_CfgReg
	.align	2
	.global	MP2HAL_V4R3C1_CfgDnMsg
	.type	MP2HAL_V4R3C1_CfgDnMsg, %function
MP2HAL_V4R3C1_CfgDnMsg:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r5, r0
	ldr	r0, [r1, #56]
	str	r3, [fp, #-60]
	mov	r3, #0
	str	r1, [fp, #-56]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	subs	r4, r0, #0
	beq	.L121
	ldrh	r2, [r5, #150]
	cmp	r2, #512
	bhi	.L122
	ldrh	r1, [r5, #146]
	cmp	r1, #512
	bhi	.L123
	ldrh	r3, [fp, #-46]
	sub	r1, r1, #1
	ldr	r0, [r5, #176]
	sub	r2, r2, #1
	bfi	r3, r1, #0, #9
	ldrh	r1, [fp, #-48]
	strh	r3, [fp, #-46]	@ movhi
	mov	r8, #0
	mov	r3, r3, lsr #8
	bfi	r1, r2, #0, #9
	bfi	r3, r0, #1, #1
	strh	r1, [fp, #-48]	@ movhi
	strb	r3, [fp, #-45]
	mov	r7, r8
	ldr	r3, [fp, #-48]
	mov	r6, r8
	mov	lr, r8
	mov	ip, r8
	mov	r0, r8
	mov	r1, r8
	str	r3, [r4]
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldrb	r9, [r5, #2]	@ zero_extendqisi2
	and	r3, r3, #7
	ldrb	r2, [r5, #3]	@ zero_extendqisi2
	bfi	r3, r9, #3, #1
	ldrb	r9, [r5, #1]	@ zero_extendqisi2
	ldrb	r10, [r5, #4]	@ zero_extendqisi2
	and	r2, r2, #3
	bfi	r3, r9, #4, #1
	strb	r3, [fp, #-45]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	mov	r9, r8
	bfi	r2, r10, #2, #1
	strb	r2, [fp, #-47]
	bfi	r8, r3, #0, #1
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	strb	r8, [fp, #-48]
	mov	r2, r7
	bfi	r7, r3, #0, #1
	strb	r7, [fp, #-46]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #4]
	ldrb	r3, [r5, #12]	@ zero_extendqisi2
	ldrb	r8, [r5, #6]	@ zero_extendqisi2
	ldrb	r7, [r5, #15]	@ zero_extendqisi2
	and	r3, r3, #15
	bfi	r3, r8, #7, #1
	strb	r3, [fp, #-45]
	bfi	r6, r7, #0, #4
	ldrb	r3, [r5, #14]	@ zero_extendqisi2
	ldrb	r7, [r5, #13]	@ zero_extendqisi2
	bfi	lr, r3, #0, #4
	strb	r6, [fp, #-48]
	strb	lr, [fp, #-47]
	bfi	ip, r7, #0, #4
	strb	ip, [fp, #-46]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #8]
	ldrb	r3, [r5, #11]	@ zero_extendqisi2
	bfi	r0, r3, #0, #2
	strb	r0, [fp, #-48]
	ldrb	ip, [r5, #10]	@ zero_extendqisi2
	ldrb	r0, [r5, #9]	@ zero_extendqisi2
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	bfi	r1, ip, #0, #1
	bfi	r9, r0, #0, #1
	strb	r1, [fp, #-47]
	bfi	r2, r3, #0, #1
	strb	r9, [fp, #-46]
	strb	r2, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #12]
	ldr	r3, [r5, #180]
	bic	r3, r3, #15
	str	r3, [r4, #16]
	ldr	r3, [r5, #184]
	bic	r3, r3, #15
	str	r3, [r4, #20]
	ldr	r3, [r5, #200]
	bic	r3, r3, #15
	str	r3, [r4, #24]
	ldr	r3, [r5, #224]
	bic	r3, r3, #15
	str	r3, [r4, #28]
	ldr	r0, [r5, #152]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	mov	r6, r0
	ldr	r0, [r5, #156]
	bl	MEM_Phy2Vir
	ldr	r3, [r5, #172]
	cmp	r3, #0
	mov	r8, r0
	beq	.L124
	ldr	r2, [r5, #160]
	mov	r1, #0
	ldr	r7, [r5, #164]
	mov	r0, r1
	ldr	ip, [r5, #156]
	cmp	r6, r1
	ldr	r3, [r5, #152]
	add	r7, ip, r7, lsr #3
	add	r3, r3, r2, lsr #3
	bic	lr, r7, #15
	bic	ip, r3, #15
	and	r2, r3, #15
	rsb	r3, lr, ip
	bfi	r1, r3, #0, #24
	str	r1, [r4, #32]
	ldr	r1, [r5, #168]
	ldr	r3, [r5, #160]
	bfi	r0, r1, #0, #24
	str	r0, [fp, #-48]
	and	r3, r3, #7
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	add	r3, r3, r2, lsl #3
	bfi	r1, r3, #0, #7
	strb	r1, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #36]
	beq	.L102
	ldr	r3, [r5, #160]
	mov	r0, #8
	ldr	r1, .L127
	add	ip, r6, r3, lsr #3
	ldrb	r2, [r6, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r5, #168]
	ldr	r3, [r5, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L127+4
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r6, r3
	ldrb	r2, [r6, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r5, #168]
	ldr	r3, [r5, #152]
	mov	r0, #22
	ldr	r1, .L127+8
	add	r2, r2, r3
	bl	dprint_vfmw
.L102:
	mov	r3, #0
	and	r7, r7, #15
	mov	r2, r3
	bfi	r2, r3, #0, #24
	str	r2, [r4, #40]
	cmp	r8, r3
	ldr	r1, [r5, #172]
	ldr	r2, [r5, #164]
	add	r1, r1, #24
	bfi	r3, r1, #0, #24
	str	r3, [fp, #-48]
	and	r3, r2, #7
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	add	r7, r3, r7, lsl #3
	bfi	r2, r7, #0, #7
	strb	r2, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #44]
	beq	.L101
	ldr	r3, [r5, #164]
	mov	r0, #8
	ldr	r1, .L127+12
	add	ip, r8, r3, lsr #3
	ldrb	r2, [r8, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r5, #172]
	ldr	r3, [r5, #164]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L127+16
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r8, r3
	ldrb	r2, [r8, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L101:
	mov	r9, r5
	mov	r1, #64
.L107:
	add	r8, r1, #64
	mov	r3, r9
	mov	r2, #0
.L103:
	ldrb	r7, [r3, #96]	@ zero_extendqisi2
	add	ip, r1, r2
	ldrb	r6, [r3, #112]	@ zero_extendqisi2
	add	r0, r8, r2
	ldrb	lr, [r3, #128]	@ zero_extendqisi2
	add	r2, r2, #4
	ldrb	r10, [r3, #80]	@ zero_extendqisi2
	cmp	r2, #8
	strb	r7, [fp, #-47]
	add	r3, r3, #8
	strb	r6, [fp, #-46]
	strb	r10, [fp, #-48]
	strb	lr, [fp, #-45]
	ldr	lr, [fp, #-48]
	str	lr, [r4, ip]
	ldrb	ip, [r3, #56]	@ zero_extendqisi2
	ldrb	r7, [r3, #8]	@ zero_extendqisi2
	ldrb	r6, [r3, #24]	@ zero_extendqisi2
	ldrb	lr, [r3, #40]	@ zero_extendqisi2
	strb	r7, [fp, #-48]
	strb	r6, [fp, #-47]
	strb	lr, [fp, #-46]
	strb	ip, [fp, #-45]
	ldr	ip, [fp, #-48]
	str	ip, [r4, r0]
	bne	.L103
	add	r1, r1, #8
	add	r9, r9, #1
	cmp	r1, #128
	bne	.L107
	ldr	r2, [fp, #-56]
	ldr	r3, [r2, #1148]
	bic	r3, r3, #15
	str	r3, [r4, #192]
	ldr	r6, [r2, #56]
	str	r3, [fp, #-48]
	bic	r6, r6, #15
	add	r6, r6, #256
	mov	r0, r6
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L125
	ldr	r3, [fp, #-60]
	mov	r0, r5
	str	r6, [r4, #252]
	mov	r2, r6
	str	r6, [fp, #-48]
	bl	MP2HAL_V4R3C1_WriteSliceMsg
	ldr	r3, .L127+20
	ldr	r3, [r3]
	ands	r0, r3, #16
	bne	.L126
.L120:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L124:
	ldr	ip, [r5, #160]
	mov	r0, r3
	ldr	r2, [r5, #152]
	cmp	r6, #0
	str	r3, [r4, #32]
	ldr	r1, [r5, #168]
	add	r2, r2, ip, lsr #3
	ldr	r3, [r5, #160]
	and	r2, r2, #15
	add	r1, r1, #24
	bfi	r0, r1, #0, #24
	and	r3, r3, #7
	str	r0, [fp, #-48]
	add	r3, r3, r2, lsl #3
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	bfi	r1, r3, #0, #7
	strb	r1, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #36]
	beq	.L100
	ldr	r3, [r5, #160]
	mov	r0, #8
	ldr	r1, .L127+24
	add	ip, r6, r3, lsr #3
	ldrb	r2, [r6, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r5, #168]
	ldr	r3, [r5, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L127+28
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r6, r3
	ldrb	r2, [r6, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L100:
	mov	r3, #0
	mov	r2, #0
	mov	r0, r3
	mov	r1, r3
	bfi	r0, r3, #0, #24
	bfi	r1, r3, #0, #24
	str	r0, [r4, #40]
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #44]
	b	.L101
.L126:
	ldr	ip, .L127+32
	mov	r0, #4
	ldr	r3, [fp, #-56]
	mov	r6, r4
	ldr	r1, .L127+36
	mov	r5, #0
	ldr	r2, [ip]
	ldr	r3, [r3, #56]
	add	r2, r2, #1
	str	r2, [ip]
	bl	dprint_vfmw
.L106:
	ldr	ip, [r6, #12]
	mov	r2, r5
	ldr	r3, [r4, r5, asl #2]
	mov	r0, #4
	ldr	r1, .L127+40
	add	r5, r5, r0
	str	ip, [sp, #8]
	add	r6, r6, #16
	ldr	ip, [r6, #-8]
	str	ip, [sp, #4]
	ldr	ip, [r6, #-12]
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r5, #64
	bne	.L106
	ldr	r1, .L127+44
	mov	r0, #4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L123:
	mov	r0, #0
	ldr	r3, .L127+48
	ldr	r2, .L127+52
	ldr	r1, .L127+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L120
.L122:
	mov	r0, #0
	ldr	r3, .L127+60
	ldr	r2, .L127+52
	ldr	r1, .L127+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L120
.L125:
	ldr	r1, .L127+64
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L120
.L121:
	ldr	r3, .L127+68
	ldr	r2, .L127+52
	ldr	r1, .L127+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L120
.L128:
	.align	2
.L127:
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	g_PrintEnable
	.word	.LC11
	.word	.LC12
	.word	.LANCHOR1
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC10
	.word	.LANCHOR0+48
	.word	.LC9
	.word	.LC8
	.word	.LC28
	.word	.LC27
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_CfgDnMsg, .-MP2HAL_V4R3C1_CfgDnMsg
	.align	2
	.global	MP2HAL_V4R3C1_StartDec
	.type	MP2HAL_V4R3C1_StartDec, %function
MP2HAL_V4R3C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r5, .L143
	cmp	r1, #0
	movw	r4, #1228
	mov	r6, r0
	mla	r4, r4, r1, r5
	bgt	.L140
	bne	.L138
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L141
.L135:
	ldr	lr, .L143+4
	sub	r3, fp, #32
	str	r2, [sp]
	mov	r1, r4
	mov	r2, #0
	mov	r0, r6
	ldr	ip, [lr]
	add	ip, ip, #1
	str	ip, [lr]
	bl	MP2HAL_V4R3C1_CfgReg
	subs	r5, r0, #0
	bne	.L142
	mov	r1, r4
	mov	r0, r6
	ldr	r3, [fp, #-32]
	mov	r2, r5
	bl	MP2HAL_V4R3C1_CfgDnMsg
.L131:
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L141:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L136
	str	r3, [r5]
	ldr	r2, [fp, #-40]
	b	.L135
.L140:
	mov	r3, r1
	mov	r0, #0
	ldr	r2, .L143+8
	mvn	r5, #0
	str	r0, [sp]
	ldr	r1, .L143+12
	bl	dprint_vfmw
	b	.L131
.L142:
	ldr	r1, .L143+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L131
.L138:
	ldr	r1, .L143+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L131
.L136:
	ldr	r1, .L143+24
	mvn	r5, #0
	bl	dprint_vfmw
	b	.L131
.L144:
	.align	2
.L143:
	.word	g_HwMem
	.word	.LANCHOR2
	.word	.LANCHOR0+72
	.word	.LC18
	.word	.LC33
	.word	.LC32
	.word	.LC20
	UNWIND(.fnend)
	.size	MP2HAL_V4R3C1_StartDec, .-MP2HAL_V4R3C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14647, %object
	.size	__func__.14647, 24
__func__.14647:
	.ascii	"MP2HAL_V4R3C1_MakeDnMsg\000"
	.type	__func__.14686, %object
	.size	__func__.14686, 21
__func__.14686:
	.ascii	"MP2HAL_V4R3C1_CfgReg\000"
	.space	3
	.type	__func__.14709, %object
	.size	__func__.14709, 23
__func__.14709:
	.ascii	"MP2HAL_V4R3C1_CfgDnMsg\000"
	.space	1
	.type	__func__.14600, %object
	.size	__func__.14600, 23
__func__.14600:
	.ascii	"MP2HAL_V4R3C1_StartDec\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	FrameNum, %object
	.size	FrameNum, 4
FrameNum:
	.word	-1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"D0 = %#x \012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"D1 = %#x \012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"D2 = %#x \012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"D3 = %#x \012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"D4 = %#x \012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"D5 = %#x \012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"D6 = %#x \012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"D7 = %#x \012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC9:
	ASCII(.ascii	"%s: %s\012\000" )
.LC10:
	ASCII(.ascii	"picture height out of range\000" )
.LC11:
	ASCII(.ascii	"Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"1p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"1p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"1p last phy addr = 0x%x\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"2p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"2p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC19:
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_CfgReg\012\000" )
.LC20:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC21:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC22:
	ASCII(.ascii	"MPEG2  VREG_V4R3C1_UVOFFSET_1D= 0x%x\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"MPEG2  VREG_V4R3C1_REF_PIC_TYPE= 0x%x\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"HEAD_INF_OFFSET = 0x%x\012\000" )
.LC25:
	ASCII(.ascii	"MPEG2  VREG_V4R3C1_BASIC_CFG0= 0x%x\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"MPEG2  VREG_V4R3C1_BASIC_CFG1= 0x%x\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC28:
	ASCII(.ascii	"Map SlcDnMsgPhyAddr to SlcDnMsgVirAddr is NULL \012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC29:
	ASCII(.ascii	"\012*****No.%2d Down Msg (phy addr: %#8x) *****\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC30:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"\012***** Down Msg print finished *****\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_StartDec\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"MP2HAL_V200R003_CfgReg ERROR!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	num.14720, %object
	.size	num.14720, 4
num.14720:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
