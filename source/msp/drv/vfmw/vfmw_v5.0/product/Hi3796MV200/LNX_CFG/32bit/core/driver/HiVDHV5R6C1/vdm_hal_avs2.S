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
	.file	"vdm_hal_avs2.c"
	.text
	.align	2
	.global	AVS2HAL_WirteOneSlice
	.type	AVS2HAL_WirteOneSlice, %function
AVS2HAL_WirteOneSlice:
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
	mov	r7, r0
	ldr	ip, [r0, #8]
	mov	r6, r1
	ldr	r5, [r0, #16]
	mov	r8, r2
	ldrb	r0, [r0, #24]	@ zero_extendqisi2
	add	r1, ip, #3
	rsb	r1, r3, r1
	sub	r5, r5, #-536870909
	cmp	r0, #0
	and	r2, r1, #15
	bic	r4, r1, #15
	mov	r0, #4
	ldreq	r9, [r7, #12]
	movne	r3, #0
	ldreq	r10, [r7, #20]
	mov	r2, r2, asl #3
	rsbeq	r9, r3, r9
	ldr	r1, .L7
	andeq	r3, r9, #15
	movne	r10, r3
	movne	r9, r3
	biceq	r9, r9, #15
	moveq	r3, r3, asl #3
	moveq	r10, r10, asl #3
	str	r3, [fp, #-52]
	mov	r5, r5, asl #3
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	ubfx	r8, r8, #0, #18
	ldr	r3, [fp, #-52]
	str	r4, [r6]
	str	r2, [r6, #4]
	mov	r2, #0
	str	r5, [r6, #8]
	sub	r5, r6, #4
	str	r9, [r6, #12]
	mov	r4, r2
	str	r3, [r6, #16]
	str	r10, [r6, #20]
	str	r2, [r6, #24]
	ldr	r3, [r7, #4]
	ubfx	r3, r3, #0, #18
	str	r3, [r6, #28]
	ldrh	r1, [r7, #2]
	ldrh	r3, [r7]
	ubfx	r1, r1, #0, #9
	str	r8, [r6, #36]
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r1, asl #16
	str	r3, [r6, #32]
.L3:
	mov	r2, r4
	ldr	r3, [r5, #4]!
	ldr	r1, .L7+4
	add	r4, r4, #1
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, #10
	bne	.L3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L8:
	.align	2
.L7:
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	AVS2HAL_WirteOneSlice, .-AVS2HAL_WirteOneSlice
	.align	2
	.global	AVS2HAL_WirteSlicMsg
	.type	AVS2HAL_WirteSlicMsg, %function
AVS2HAL_WirteSlicMsg:
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
	ldr	r3, [r0, #1140]
	mov	r9, r0
	mov	r6, r1
	cmp	r3, #0
	beq	.L14
	add	r2, r2, #256
	add	r7, r0, #1136
	rsb	r8, r1, r2
	add	r7, r7, #8
	mov	r4, r1
	mov	r5, #1
.L13:
	sub	r2, r5, #1
	sub	r3, r3, #1
	cmp	r3, r2
	mov	r1, r4
	mov	r0, r7
	mov	r10, r5
	ldrls	r2, [r9, #108]
	add	r5, r5, #1
	ldrls	r3, [r9, #112]
	add	r7, r7, #36
	ldrhi	r2, [r7, #4]
	mulls	r2, r3, r2
	ldr	r3, [r9, #88]
	sub	r2, r2, #1
	bl	AVS2HAL_WirteOneSlice
	add	r3, r8, r4
	str	r3, [r4, #252]
	add	r4, r4, #256
	ldr	r3, [r9, #1140]
	cmp	r3, r10
	bhi	.L13
	mov	r3, r3, asl #8
	sub	r3, r3, #4
.L10:
	mov	r2, #0
	str	r2, [r6, r3]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L14:
	mvn	r3, #3
	b	.L10
	UNWIND(.fnend)
	.size	AVS2HAL_WirteSlicMsg, .-AVS2HAL_WirteSlicMsg
	.align	2
	.global	AVS2HAL_WirtePicMsg
	.type	AVS2HAL_WirtePicMsg, %function
AVS2HAL_WirtePicMsg:
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
	mov	r4, r1
	mov	r9, r0
	ldr	r1, .L31
	mov	r0, #4
	mov	r5, r2
	bl	dprint_vfmw
	ldr	r2, [r4, #112]
	ldr	r3, [r4, #108]
	add	ip, r4, #396
	sub	r2, r2, #1
	add	r6, r4, #424
	ubfx	r2, r2, #0, #9
	sub	r3, r3, #1
	ubfx	r3, r3, #0, #9
	mov	lr, r5
	orr	r3, r3, r2, asl #16
	str	r3, [r5]
	ldr	r1, [r4, #120]
	ldr	r0, [r4, #124]
	ldr	r2, [r4, #128]
	and	r1, r1, #1
	ldr	r7, [r4, #132]
	and	r0, r0, #127
	ldr	r3, [r4, #136]
	mov	r1, r1, asl #20
	and	r2, r2, #1
	orr	r1, r1, r0, asl #9
	and	r7, r7, #7
	ldrb	r0, [r4]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #8
	and	r3, r3, #3
	orr	r2, r2, r7, asl #3
	and	r1, r0, #15
	orr	r3, r2, r3, asl #1
	orr	r3, r3, r1, asl #16
	str	r3, [r5, #4]
	ldr	r0, [r4, #144]
	ldr	r2, [r4, #140]
	and	r0, r0, #1
	ldr	r1, [r4, #116]
	ldr	r10, [r4, #148]
	and	r2, r2, #1
	ldr	r7, [r4, #152]
	mov	r0, r0, asl #18
	ldr	r8, [r4, #156]
	orr	r2, r0, r2, asl #19
	and	r1, r1, #7
	and	r10, r10, #3
	orr	r2, r2, r1
	and	r3, r7, #1
	ldr	r7, [r4, #160]
	orr	r2, r2, r10, asl #16
	and	r0, r8, #1
	ldr	r8, [r4, #164]
	and	r10, r7, #1
	orr	r3, r2, r3, asl #15
	ldr	r7, [r4, #168]
	orr	r3, r3, r0, asl #14
	and	r1, r8, #1
	ldr	r8, [r4, #172]
	orr	r0, r3, r10, asl #13
	and	r10, r7, #7
	ldr	r7, [r4, #176]
	orr	r1, r0, r1, asl #12
	ldr	r3, [r4, #180]
	and	r2, r8, #1
	ldr	r0, [r4, #184]
	orr	r1, r1, r10, asl #9
	and	r7, r7, #7
	orr	r2, r1, r2, asl #8
	and	r3, r3, #1
	and	r1, r0, #1
	orr	r2, r2, r7, asl #5
	orr	r3, r2, r3, asl #4
	orr	r3, r3, r1, asl #3
	str	r3, [r5, #8]
	ldr	r0, [r4, #192]
	ldr	r2, [r4, #188]
	and	r0, r0, #1
	ldr	r1, [r4, #208]
	ldr	r7, [r4, #204]
	and	r2, r2, #1
	ldr	r3, [r4, #196]
	mov	r0, r0, asl #14
	orr	r2, r0, r2, asl #15
	and	r1, r1, #1
	ldr	r0, [r4, #200]
	and	r7, r7, #1
	orr	r2, r2, r1
	and	r3, r3, #63
	orr	r2, r2, r7, asl #1
	and	r1, r0, #63
	orr	r3, r2, r3, asl #8
	orr	r3, r3, r1, asl #2
	str	r3, [r5, #12]
	ldr	r1, [r4, #216]
	ldr	r3, [r4, #212]
	and	r1, r1, #31
	ldr	r2, [r4, #224]
	and	r3, r3, #31
	ldr	r0, [r4, #220]
	mov	r1, r1, asl #2
	and	r2, r2, #1
	orr	r3, r1, r3, asl #7
	and	r1, r0, #1
	orr	r3, r3, r2
	orr	r3, r3, r1, asl #1
	str	r3, [r5, #16]
	ldr	r0, [r4, #368]
	ldr	r2, [r4, #340]
	and	r0, r0, #3
	ldr	r3, [r4, #236]
	ldr	r1, [r4, #396]
	ldr	r7, [r4, #336]
	mov	r0, r0, asl #29
	ldr	r8, [r4, #364]
	orr	r0, r0, r2, asl #31
	and	r3, r3, #1
	and	r1, r1, #1
	orr	r0, r0, r3
	and	r10, r7, #1
	ldr	r7, [r4, #392]
	orr	r1, r0, r1, asl #28
	and	r2, r8, #3
	ldr	r0, [r4, #332]
	orr	r1, r1, r10, asl #27
	ldr	r8, [r4, #360]
	and	r10, r7, #1
	orr	r2, r1, r2, asl #25
	ldr	r7, [r4, #388]
	and	r3, r0, #1
	orr	r2, r2, r10, asl #24
	and	r0, r8, #3
	ldr	r8, [r4, #328]
	and	r10, r7, #1
	orr	r3, r2, r3, asl #23
	ldr	r7, [r4, #356]
	orr	r3, r3, r0, asl #21
	and	r1, r8, #1
	ldr	r8, [r4, #384]
	orr	r0, r3, r10, asl #20
	and	r10, r7, #3
	ldr	r7, [r4, #324]
	orr	r1, r0, r1, asl #19
	and	r2, r8, #1
	ldr	r0, [r4, #352]
	orr	r1, r1, r10, asl #17
	ldr	r8, [r4, #380]
	and	r10, r7, #1
	orr	r2, r1, r2, asl #16
	ldr	r7, [r4, #320]
	and	r3, r0, #3
	orr	r2, r2, r10, asl #15
	and	r0, r8, #1
	ldr	r8, [r4, #348]
	and	r10, r7, #1
	orr	r3, r2, r3, asl #13
	ldr	r7, [r4, #376]
	orr	r3, r3, r0, asl #12
	and	r1, r8, #3
	ldr	r8, [r4, #316]
	orr	r0, r3, r10, asl #11
	and	r10, r7, #1
	ldr	r7, [r4, #344]
	orr	r1, r0, r1, asl #9
	ldr	r3, [r4, #372]
	and	r2, r8, #1
	orr	r1, r1, r10, asl #8
	ldr	r0, [r4, #228]
	and	r7, r7, #3
	orr	r2, r1, r2, asl #7
	and	r3, r3, #1
	and	r1, r0, #1
	orr	r2, r2, r7, asl #5
	orr	r3, r2, r3, asl #4
	orr	r3, r3, r1, asl #3
	str	r3, [lr, #20]!
.L17:
	ldr	r3, [ip, #4]!
	cmp	ip, r6
	bic	r3, r3, #15
	str	r3, [lr, #4]!
	bne	.L17
	ldr	r2, [r4, #104]
	movw	lr, #1228
	ldr	r3, [r4, #100]
	mov	r1, #0
	ubfx	r2, r2, #0, #14
	ldr	ip, .L31+4
	ubfx	r3, r3, #0, #14
	add	r8, r4, #576
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #52]
	ldr	r0, [r4, #104]
	mov	r7, r4
	ldr	r2, [r4, #100]
	mov	r3, r5
	mla	r9, lr, r9, ip
	add	r0, r0, #7
	add	r2, r2, #7
	mov	r6, r5
	mov	r0, r0, lsr #3
	mov	lr, r4
	sub	r0, r0, #1
	mov	r2, r2, lsr #3
	ubfx	r0, r0, #0, #10
	sub	r2, r2, #1
	ubfx	r2, r2, #0, #10
	orr	r2, r2, r0, asl #16
	str	r2, [r5, #56]
	ldr	r2, [r9, #1092]
	bic	r2, r2, #15
	str	r2, [r5, #60]
	ldr	r2, [r9, #1096]
	bic	r2, r2, #15
	str	r2, [r5, #64]
	ldr	r2, [r9, #1104]
	bic	r2, r2, #15
	str	r2, [r5, #68]
	ldr	r2, [r9, #1128]
	str	r1, [r5, #76]
	bic	r2, r2, #15
	str	r2, [r5, #72]
	ldr	r2, [r4, #240]
	bic	r2, r2, #15
	str	r2, [r5, #80]
	ldr	r2, [r4, #244]
	bic	r2, r2, #15
	str	r2, [r5, #84]
.L18:
	ldr	r0, [lr, #504]
	add	lr, lr, #36
	ldr	r2, [lr, #488]
	add	r6, r6, #8
	and	r0, r0, #127
	ldr	r9, [lr, #464]
	ldr	r1, [lr, #456]
	ldr	ip, [lr, #460]
	mov	r0, r0, asl #21
	orr	r0, r0, r2, asl #28
	and	r1, r1, #127
	and	r2, r9, #127
	orr	r1, r0, r1
	and	ip, ip, #127
	orr	r2, r1, r2, asl #14
	orr	r2, r2, ip, asl #7
	str	r2, [r6, #80]
	ldr	r0, [lr, #480]
	ldr	r2, [lr, #484]
	and	r0, r0, #127
	ldr	r1, [lr, #472]
	ldr	r9, [lr, #476]
	and	r2, r2, #127
	ldr	ip, [lr, #488]
	mov	r0, r0, asl #14
	orr	r0, r0, r2, asl #21
	and	r1, r1, #127
	and	r2, r9, #127
	orr	r1, r0, r1
	ubfx	ip, ip, #4, #3
	cmp	lr, r8
	orr	r2, r1, r2, asl #7
	orr	r2, r2, ip, asl #28
	str	r2, [r6, #84]
	bne	.L18
	add	r8, r4, #72
	mov	r6, r5
	mov	lr, r4
.L19:
	ldr	r0, [lr, #1080]
	add	lr, lr, #36
	ldr	r2, [lr, #1064]
	add	r6, r6, #8
	and	r0, r0, #127
	ldr	r9, [lr, #1040]
	ldr	r1, [lr, #1032]
	ldr	ip, [lr, #1036]
	mov	r0, r0, asl #21
	orr	r0, r0, r2, asl #28
	and	r1, r1, #127
	and	r2, r9, #127
	orr	r1, r0, r1
	and	ip, ip, #127
	orr	r2, r1, r2, asl #14
	orr	r2, r2, ip, asl #7
	str	r2, [r6, #208]
	ldr	r0, [lr, #1056]
	ldr	r2, [lr, #1060]
	and	r0, r0, #127
	ldr	r1, [lr, #1048]
	ldr	r9, [lr, #1052]
	and	r2, r2, #127
	ldr	ip, [lr, #1064]
	mov	r0, r0, asl #14
	orr	r0, r0, r2, asl #21
	and	r1, r1, #127
	and	r2, r9, #127
	orr	r1, r0, r1
	ubfx	ip, ip, #4, #3
	cmp	lr, r8
	orr	r2, r1, r2, asl #7
	orr	r2, r2, ip, asl #28
	str	r2, [r6, #212]
	bne	.L19
	mov	r0, r5
	mov	ip, #0
.L20:
	add	r2, r4, ip
	add	ip, ip, #4
	add	r6, r2, #428
	add	r9, r2, #444
	add	r9, r9, #2
	add	r10, r2, #444
	ldrh	r1, [r6, #2]
	add	r8, r2, #460
	ldrh	lr, [r6]
	add	r6, r2, #460
	ubfx	r1, r1, #0, #10
	add	r6, r6, #2
	ubfx	lr, lr, #0, #10
	cmp	ip, #16
	orr	r1, lr, r1, asl #16
	str	r1, [r0, #256]
	ldrh	r9, [r9]
	add	lr, r2, #476
	ldrh	r1, [r10]
	add	r0, r0, #4
	ubfx	r9, r9, #0, #10
	ubfx	r1, r1, #0, #10
	orr	r1, r1, r9, asl #16
	str	r1, [r0, #268]
	ldrh	r6, [r6]
	ldrh	r1, [r8]
	ubfx	r6, r6, #0, #15
	ubfx	r1, r1, #0, #15
	orr	r1, r1, r6, asl #16
	str	r1, [r0, #284]
	ldrh	r1, [lr, #2]
	ldrh	r2, [lr]
	ubfx	r1, r1, #0, #15
	ubfx	r2, r2, #0, #15
	orr	r2, r2, r1, asl #16
	str	r2, [r0, #300]
	bne	.L20
	ldr	r1, [r4, #252]
	mov	r0, r5
	ldr	r6, [r4, #248]
	mov	ip, #0
	and	r1, r1, #1
	ldr	r2, [r4, #288]
	ldr	r10, [r4, #256]
	and	r6, r6, #3
	ldr	r9, [r4, #312]
	mov	r1, r1, asl #8
	orr	r6, r1, r6, asl #9
	ldr	r8, [r4, #308]
	and	r10, r10, #1
	and	r2, r2, #1
	orr	r2, r6, r2
	and	lr, r9, #1
	ldr	r9, [r4, #304]
	orr	r6, r2, r10, asl #7
	and	r10, r8, #1
	ldr	r8, [r4, #300]
	orr	lr, r6, lr, asl #6
	ldr	r2, [r4, #296]
	and	r1, r9, #1
	orr	lr, lr, r10, asl #5
	ldr	r6, [r4, #292]
	and	r8, r8, #1
	orr	r1, lr, r1, asl #4
	and	r2, r2, #1
	orr	r1, r1, r8, asl #3
	and	lr, r6, #1
	orr	r2, r1, r2, asl #2
	orr	r2, r2, lr, asl #1
	str	r2, [r5, #356]
.L21:
	ldrb	r1, [r7, #13]	@ zero_extendqisi2
	add	ip, ip, #1
	ldrb	r2, [r7, #5]	@ zero_extendqisi2
	cmp	ip, #4
	add	r7, r7, #1
	add	r0, r0, #8
	orr	r2, r2, r1, asl #8
	str	r2, [r0, #352]
	ldrb	r1, [r7, #16]	@ zero_extendqisi2
	ldrb	r2, [r7, #8]	@ zero_extendqisi2
	orr	r2, r2, r1, asl #8
	str	r2, [r0, #356]
	bne	.L21
	add	r10, r4, #20
	add	r8, r4, #36
	add	r6, r4, #52
	add	r9, r4, #28
	add	r2, r4, #68
	add	r0, r4, #60
	str	r2, [fp, #-80]
	mov	r1, r5
	str	r0, [fp, #-64]
	add	r7, r4, #44
	str	r2, [fp, #-48]
	mov	r2, #0
	str	r0, [fp, #-56]
	mov	r0, r10
	add	r4, r4, #76
	mov	ip, r8
	mov	lr, r6
	str	r6, [fp, #-60]
	str	r8, [fp, #-68]
	mov	r8, r9
	ldr	r6, [fp, #-64]
	str	r9, [fp, #-76]
	str	r4, [fp, #-52]
	ldr	r9, [fp, #-80]
	str	r7, [fp, #-64]
	str	r3, [fp, #-72]
	str	r10, [fp, #-80]
.L22:
	ldrb	r10, [ip, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	cmp	r2, #8
	add	r1, r1, #16
	orr	r3, r3, r10, asl #8
	str	r3, [r1, #376]
	ldrb	r10, [r9, #1]!	@ zero_extendqisi2
	ldrb	r3, [lr, #1]!	@ zero_extendqisi2
	orr	r3, r3, r10, asl #8
	str	r3, [r1, #380]
	ldrb	r10, [r7, #1]!	@ zero_extendqisi2
	ldrb	r3, [r8, #1]!	@ zero_extendqisi2
	orr	r3, r3, r10, asl #8
	str	r3, [r1, #384]
	ldrb	r10, [r4, #1]!	@ zero_extendqisi2
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	orr	r3, r3, r10, asl #8
	str	r3, [r1, #388]
	bne	.L22
	ldr	r4, [fp, #-52]
	mov	ip, #0
	ldr	r0, [fp, #-56]
	ldr	r6, [fp, #-60]
	ldr	r7, [fp, #-64]
	ldr	r8, [fp, #-68]
	ldr	r3, [fp, #-72]
	ldr	r9, [fp, #-76]
	ldr	r10, [fp, #-80]
	ldr	r1, [fp, #-48]
.L23:
	ldrb	lr, [r9, #1]!	@ zero_extendqisi2
	add	ip, ip, #1
	ldrb	r2, [r10, #1]!	@ zero_extendqisi2
	cmp	ip, #8
	add	r3, r3, #16
	orr	r2, r2, lr, asl #8
	str	r2, [r3, #504]
	ldrb	lr, [r7, #1]!	@ zero_extendqisi2
	ldrb	r2, [r8, #1]!	@ zero_extendqisi2
	orr	r2, r2, lr, asl #8
	str	r2, [r3, #508]
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	orr	r2, r2, lr, asl #8
	str	r2, [r3, #512]
	ldrb	lr, [r4, #1]!	@ zero_extendqisi2
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	orr	r2, r2, lr, asl #8
	str	r2, [r3, #516]
	bne	.L23
	ldr	r3, .L31+8
	mov	r2, #288
	add	r1, r5, #360
	add	r0, r5, #768
	ldr	r3, [r3, #52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L32:
	.align	2
.L31:
	.word	.LC2
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	AVS2HAL_WirtePicMsg, .-AVS2HAL_WirtePicMsg
	.align	2
	.global	AVS2HAL_StartDec_GetStrmAddr
	.type	AVS2HAL_StartDec_GetStrmAddr, %function
AVS2HAL_StartDec_GetStrmAddr:
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
	ldr	r6, [r0, #1140]
	cmp	r6, #0
	beq	.L34
	add	ip, r0, #1136
	mov	r4, #0
	add	ip, ip, #12
	mov	lr, r4
.L35:
	mov	r1, ip
	mov	r3, #0
.L37:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	cmp	r2, #0
	beq	.L36
	ldr	r5, [r1, #8]
	bic	r2, r2, #15
	cmp	r5, #0
	beq	.L36
	cmp	lr, #0
	cmpne	lr, r2
	movcs	lr, r2
.L36:
	cmp	r3, #2
	bne	.L37
	add	r4, r4, #1
	add	ip, ip, #36
	cmp	r4, r6
	bne	.L35
	cmp	lr, #0
	strne	lr, [r0, #88]
	movne	r3, #0
	beq	.L34
.L40:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L34:
	ldr	r2, .L51
	mov	r0, #0
	ldr	r1, .L51+4
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L40
.L52:
	.align	2
.L51:
	.word	.LANCHOR0
	.word	.LC3
	UNWIND(.fnend)
	.size	AVS2HAL_StartDec_GetStrmAddr, .-AVS2HAL_StartDec_GetStrmAddr
	.align	2
	.global	AVS2HAL_WirteReg
	.type	AVS2HAL_WirteReg, %function
AVS2HAL_WirteReg:
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
	mov	r4, r1
	mov	r5, r2
	mov	r6, r0
	bl	AVS2HAL_StartDec_GetStrmAddr
	subs	r8, r0, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r1, [r6, #112]
	mov	r3, r5
	ldr	r7, [r6, #108]
	mov	r2, r4
	mov	r0, #8
	mul	r7, r1, r7
	sub	r7, r7, #1
	ubfx	r7, r7, #0, #20
	orr	r7, r7, #1073741824
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59
	mov	r0, #3
	bl	dprint_vfmw
	ldrb	r2, [r6, #4]	@ zero_extendqisi2
	ldrb	r1, [r6, #2]	@ zero_extendqisi2
	mov	r3, r5
	and	r2, r2, #1
	ldrb	r7, [r6, #1]	@ zero_extendqisi2
	and	r1, r1, #1
	strb	r8, [r6, #3]
	mov	r2, r2, asl #28
	and	r7, r7, #1
	orr	r0, r2, r1, asl #30
	mov	r2, r4
	orr	r1, r0, #245760
	mov	r0, #12
	orr	r1, r1, #15
	orr	r7, r1, r7, asl r0
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r7, .L59+4
	mov	r0, #3
	ldr	r1, .L59+8
	bl	dprint_vfmw
	movw	r1, #1228
	mla	r7, r1, r4, r7
	mov	r3, r5
	mov	r2, r4
	mov	r0, #16
	ldr	r8, [r7, #56]
	bic	r8, r8, #15
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L59+12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r7, #40]
	mov	r3, r5
	mov	r2, r4
	bic	r7, r7, #15
	mov	r0, #20
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+16
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #88]
	mov	r3, r5
	mov	r2, r4
	bic	r7, r7, #15
	mov	r0, #24
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+20
	mov	r0, #3
	bl	dprint_vfmw
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #60
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #64
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #68
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #72
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #76
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #80
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r5
	mov	r2, r4
	mov	r0, #84
	movt	r1, 48
	bl	MFDE_ConfigReg
	ldrb	r3, [r6, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L57
.L55:
	ldr	r7, [r6, #92]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #96
	bic	r7, r7, #255
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #260]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #100
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+28
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #268]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #104
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+32
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #272]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #108
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+36
	mov	r0, #3
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #10
	beq	.L58
.L56:
	ldr	r1, [r6, #100]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #4
	cmp	r1, #4096
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	mov	r3, r5
	mov	r2, r4
	mov	r1, #0
	mov	r0, #148
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L59+40
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r5
	mov	r2, r4
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L59+44
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r5
	mov	r2, r4
	mvn	r1, #0
	mov	r0, #32
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MFDE_ConfigReg
.L57:
	ldr	r1, .L59+48
	mov	r3, r5
	mov	r2, r4
	mov	r0, #92
	ldr	r7, [r1]
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+52
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #96]
	mov	r2, r4
	mov	r3, r5
	mov	r0, #112
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+56
	mov	r0, #3
	bl	dprint_vfmw
	b	.L55
.L58:
	ldr	r7, [r6, #276]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #116
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+60
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #280]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #120
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+64
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #284]
	mov	r2, r4
	mov	r3, r5
	mov	r0, #124
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L59+68
	mov	r0, #3
	bl	dprint_vfmw
	b	.L56
.L60:
	.align	2
.L59:
	.word	.LC4
	.word	g_HwMem
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC18
	.word	.LC19
	.word	g_TunnelLineNumber
	.word	.LC9
	.word	.LC10
	.word	.LC15
	.word	.LC16
	.word	.LC17
	UNWIND(.fnend)
	.size	AVS2HAL_WirteReg, .-AVS2HAL_WirteReg
	.align	2
	.global	AVS2HAL_V5R6C1_StartDec
	.type	AVS2HAL_V5R6C1_StartDec, %function
AVS2HAL_V5R6C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, .L82
	mov	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L62
	cmp	r2, #0
	ldrneb	r3, [r0, #4]	@ zero_extendqisi2
	strneb	r3, [r2, #1]
	beq	.L77
.L62:
	ldr	r3, [r4, #100]
	cmp	r3, #8192
	bhi	.L66
	ldr	r3, [r4, #104]
	cmp	r3, #8192
	bhi	.L66
	ldr	r0, [r4, #1140]
	sub	r0, r0, #1
	cmp	r0, #254
	bhi	.L78
	cmp	r1, #0
	beq	.L69
	cmp	r1, #1
	bne	.L79
	mov	r0, #0
	mov	r3, r1
	str	r0, [sp]
	ldr	r2, .L82+4
	ldr	r1, .L82+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L69:
	ldr	r5, .L82+12
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L80
.L71:
	mov	r1, #0
	mov	r0, r4
	bl	AVS2HAL_WirteReg
	ldr	r5, [r5, #56]
	mov	r0, r5
	bl	MEM_Phy2Vir
	subs	r6, r0, #0
	beq	.L81
	mov	r2, r6
	mov	r1, r4
	mov	r0, #0
	bl	AVS2HAL_WirtePicMsg
	add	r2, r5, #1280
	mov	r0, r4
	add	r1, r6, #1280
	str	r2, [r6, #252]
	bl	AVS2HAL_WirteSlicMsg
	mov	r0, #0
.L64:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L79:
	ldr	r1, .L82+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L80:
	mov	r0, #0
	str	r2, [fp, #-32]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-32]
	cmp	r0, #0
	str	r0, [r5]
	bne	.L71
	ldr	r1, .L82+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L66:
	ldr	r3, .L82+24
.L76:
	mov	r0, #0
	ldr	r2, .L82+4
	ldr	r1, .L82+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L78:
	ldr	r3, .L82+32
	b	.L76
.L81:
	ldr	r3, .L82+36
	ldr	r2, .L82+4
	ldr	r1, .L82+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L77:
	mov	r3, r2
	mov	r0, r2
	ldr	r1, .L82+40
	ldr	r2, .L82+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L83:
	.align	2
.L82:
	.word	g_HalDisable
	.word	.LANCHOR0+32
	.word	.LC25
	.word	g_HwMem
	.word	.LC24
	.word	.LC26
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC27
	.word	.LC20
	UNWIND(.fnend)
	.size	AVS2HAL_V5R6C1_StartDec, .-AVS2HAL_V5R6C1_StartDec
	.align	2
	.global	AVS2HAL_V5R6C1_InitHal
	.type	AVS2HAL_V5R6C1_InitHal, %function
AVS2HAL_V5R6C1_InitHal:
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
	.size	AVS2HAL_V5R6C1_InitHal, .-AVS2HAL_V5R6C1_InitHal
	.global	Avs2_BitMask
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.15158, %object
	.size	__func__.15158, 29
__func__.15158:
	.ascii	"AVS2HAL_StartDec_GetStrmAddr\000"
	.space	3
	.type	__func__.15197, %object
	.size	__func__.15197, 24
__func__.15197:
	.ascii	"AVS2HAL_V5R6C1_StartDec\000"
	.type	Avs2_BitMask, %object
	.size	Avs2_BitMask, 132
Avs2_BitMask:
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
	.word	33554431
	.word	67108863
	.word	134217727
	.word	268435455
	.word	536870911
	.word	1073741823
	.word	2147483647
	.word	-1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"Slice down message:\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"D%d  =  0x%x\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"Picture down message:\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"%s can not find stream_base_addr\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"VREG_V5R6C1_BASIC_CFG0 = 0x%x\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"VREG_V5R6C1_BASIC_CFG1 = 0x%x\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"VREG_V5R6C1_AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"VREG_V5R6C1_VAM_ADDR = 0x%x\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"VREG_V5R6C1_STREAM_BASE_ADDR = 0x%x\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"VREG_V5R6C1_PART_DEC_OVER_INT_LEVEL = 0x%x\012\000" )
.LC10:
	ASCII(.ascii	"VREG_V5R6C1_LINE_NUM_STADDR = 0x%x\012\000" )
.LC11:
	ASCII(.ascii	"VREG_V5R6C1_YSTADDR_1D = 0x%x\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"VREG_V5R6C1_YSTRIDE_1D = 0x%x\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"VREG_V5R6C1_UVOFFSET_1D = 0x%x\012\000" )
.LC14:
	ASCII(.ascii	"VREG_V5R6C1_HEAD_INF_OFFSET = 0x%x\012\000" )
.LC15:
	ASCII(.ascii	"VREG_V5R6C1_YSTRIDE_2BIT = 0x%x\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"VREG_V5R6C1_YOFFSET_2BIT = 0x%x\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"VREG_V5R6C1_UVOFFSET_2BIT = 0x%x\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"VREG_V5R6C1_REF_PIC_TYPE = 0x%x\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"VREG_V5R6C1_FF_APT_EN = 0x%x\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC22:
	ASCII(.ascii	"%s: %s\012\000" )
.LC23:
	ASCII(.ascii	"SliceNum out of range\000" )
	.space	2
.LC24:
	ASCII(.ascii	"VdhId is wrong! AVS2HAL_V5R6C1_StartDec\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC26:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC27:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
