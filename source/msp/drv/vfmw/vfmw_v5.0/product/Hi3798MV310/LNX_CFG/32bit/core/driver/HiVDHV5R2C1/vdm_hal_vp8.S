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
	.file	"vdm_hal_vp8.c"
	.text
	.align	2
	.global	VP8HAL_V5R2C1_InitHal
	.type	VP8HAL_V5R2C1_InitHal, %function
VP8HAL_V5R2C1_InitHal:
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
	.size	VP8HAL_V5R2C1_InitHal, .-VP8HAL_V5R2C1_InitHal
	.align	2
	.global	VP8HAL_V5R2C1_CfgReg
	.type	VP8HAL_V5R2C1_CfgReg, %function
VP8HAL_V5R2C1_CfgReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r4, r2, #0
	mov	r6, r0
	mov	r7, r1
	mov	r0, #0
	mov	r5, r3
	str	r0, [fp, #-40]
	bgt	.L10
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L11
.L5:
	ldr	lr, [r6, #2792]
	mov	r3, r5
	ldr	ip, [r6, #2788]
	mov	r2, r4
	ldr	r1, [fp, #-40]
	mov	r0, #8
	mul	ip, ip, lr
	sub	ip, ip, #1
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-40]
	mov	r1, r1, lsr #24
	and	r1, r1, #191
	bfc	r1, #7, #1
	strb	r1, [fp, #-37]
	ldr	r8, [fp, #-40]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r6, #3148]
	ldr	r2, [r6, #2788]
	mov	r3, #0
	bfi	r3, r1, #4, #1
	mov	r1, #12
	and	r3, r3, #16
	strb	r1, [fp, #-40]
	mov	r2, r2, asl #4
	orr	r3, r3, #64
	cmp	r2, #1920
	mov	r2, #8192	@ movhi
	mvn	r3, r3, asl #25
	strh	r2, [fp, #-38]	@ movhi
	ldrhi	ip, [r6, #3144]
	movls	lr, #1
	movls	ip, #0
	mvn	r3, r3, lsr #25
	strb	r3, [fp, #-39]
	movhi	r3, #0
	strhib	r3, [r6, #2778]
	movhi	lr, r3
	mov	r2, r4
	mov	r3, r5
	mov	r0, #12
	strlsb	lr, [r6, #2778]
	andhi	ip, ip, #1
	strls	ip, [r6, #3144]
	ldrb	r1, [fp, #-37]	@ zero_extendqisi2
	bfi	r1, lr, #5, #1
	bfi	r1, ip, #6, #1
	bfc	r1, #7, #1
	strb	r1, [fp, #-37]
	ldr	r8, [fp, #-40]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12+4
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #56]
	mov	r3, r5
	mov	r2, r4
	bic	r8, r8, #15
	mov	r0, #16
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12+8
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #40]
	mov	r3, r5
	mov	r2, r4
	bic	r8, r8, #15
	mov	r0, #20
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12+12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r6, #2816]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #24
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12+16
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #1164]
	mov	r3, r5
	mov	r2, r4
	bic	r8, r8, #15
	mov	r0, #128
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L12+20
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r7, #1168]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #132
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L12+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r6, #2788]
	mov	r3, r5
	mov	r2, r4
	cmp	r1, #256
	mov	r0, #4
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	ldr	r7, [r6, #3120]
	mov	r3, r5
	mov	r2, r4
	bic	r7, r7, #15
	mov	r0, #96
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L12+28
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #2796]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #100
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L12+32
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r7, [r6, #3152]
	mov	r3, r5
	mov	r2, r4
	mov	r0, #104
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L12+36
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r5
	mov	r2, r4
	ldr	r1, [r6, #3160]
	mov	r0, #108
	bl	MFDE_ConfigReg
	mov	r0, #32
	mov	r3, r5
	mov	r2, r4
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L4:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L11:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L6
	str	r3, [r7]
	b	.L5
.L10:
	str	r0, [sp]
	mov	r3, r4
	ldr	r2, .L12+40
	ldr	r1, .L12+44
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L6:
	ldr	r1, .L12+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L13:
	.align	2
.L12:
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LANCHOR0
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VP8HAL_V5R2C1_CfgReg, .-VP8HAL_V5R2C1_CfgReg
	.align	2
	.global	VP8HAL_V5R2C1_CfgDnMsg
	.type	VP8HAL_V5R2C1_CfgDnMsg, %function
VP8HAL_V5R2C1_CfgDnMsg:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r4, r0
	ldr	r0, [r1, #56]
	mov	r9, r1
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L22
	ldr	r3, [r4, #2800]
	mov	r5, #0
	ldr	r2, [r4, #2804]
	mov	r0, #4
	and	r3, r3, #1
	str	r5, [fp, #-40]
	bfi	r3, r2, #1, #2
	strb	r3, [fp, #-40]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24
	str	r2, [r8]
	bl	dprint_vfmw
	ldr	r2, [r4, #2812]
	ldr	r3, [r4, #2808]
	mov	r0, #4
	ldr	r1, .L24+4
	rsb	r2, r3, r2, lsl #1
	add	r2, r2, #1
	str	r2, [r8, #4]
	bl	dprint_vfmw
	ldr	r2, [r4, #2788]
	ldr	r3, [r4, #2792]
	mov	r0, #0	@ movhi
	sub	r2, r2, #1
	mov	r1, r0	@ movhi
	sub	r3, r3, #1
	bfi	r0, r2, #0, #9
	bfi	r1, r3, #0, #9
	strh	r0, [fp, #-40]	@ movhi
	strh	r1, [fp, #-38]	@ movhi
	mov	r0, #4
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+8
	str	r2, [r8, #8]
	bl	dprint_vfmw
	ldrb	r2, [r4, #2752]	@ zero_extendqisi2
	ldrb	r3, [r4, #2753]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r1, [r4, #2754]	@ zero_extendqisi2
	and	r3, r3, #1
	str	r5, [fp, #-40]
	bfi	r3, r1, #1, #2
	strb	r2, [fp, #-40]
	strb	r3, [fp, #-39]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+12
	str	r2, [r8, #12]
	bl	dprint_vfmw
	ldrb	r3, [r4, #2755]	@ zero_extendqisi2
	ldrb	r2, [r4, #2756]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r1, [r4, #2757]	@ zero_extendqisi2
	and	r3, r3, #1
	bfi	r3, r2, #1, #1
	ldrb	r2, [r4, #2758]	@ zero_extendqisi2
	bfi	r3, r1, #2, #1
	str	r5, [fp, #-40]
	bfi	r3, r2, #3, #1
	strb	r3, [fp, #-40]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+16
	str	r2, [r8, #16]
	bl	dprint_vfmw
	ldrb	r3, [r4, #2760]	@ zero_extendqisi2
	ldrb	r2, [r4, #2761]	@ zero_extendqisi2
	mov	r0, #4
	and	r3, r3, #1
	str	r5, [fp, #-40]
	bfi	r3, r2, #1, #2
	ldrb	r2, [r4, #2762]	@ zero_extendqisi2
	strb	r3, [fp, #-40]
	ldrh	r3, [fp, #-40]
	ldrb	ip, [r4, #2763]	@ zero_extendqisi2
	bfi	r3, r2, #3, #6
	ldrb	r2, [r4, #2764]	@ zero_extendqisi2
	strh	r3, [fp, #-40]	@ movhi
	mov	r3, r3, lsr #8
	ldr	r1, .L24+20
	bfi	r3, ip, #1, #3
	bfi	r3, r2, #4, #3
	strb	r3, [fp, #-39]
	ldr	r2, [fp, #-40]
	str	r2, [r8, #20]
	bl	dprint_vfmw
	ldrb	r3, [r4, #2765]	@ zero_extendqisi2
	ldrb	r1, [r4, #2766]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r2, [r4, #2767]	@ zero_extendqisi2
	and	r3, r3, #1
	bfi	r3, r1, #1, #4
	str	r5, [fp, #-40]
	ldrb	ip, [r4, #2768]	@ zero_extendqisi2
	bfi	r3, r2, #5, #1
	strb	r3, [fp, #-40]
	ldrh	r1, [fp, #-40]
	ldrb	lr, [r4, #2769]	@ zero_extendqisi2
	bfi	r1, ip, #6, #4
	ldrb	r2, [fp, #-38]	@ zero_extendqisi2
	ldrb	ip, [r4, #2772]	@ zero_extendqisi2
	mov	r3, r1, lsr #8
	bfi	r2, ip, #0, #4
	bfi	r3, lr, #2, #1
	ldrb	ip, [r4, #2773]	@ zero_extendqisi2
	ldrb	lr, [r4, #2770]	@ zero_extendqisi2
	bfi	r2, ip, #4, #1
	ldrb	ip, [r4, #2771]	@ zero_extendqisi2
	strb	r2, [fp, #-38]
	bfi	r3, lr, #3, #4
	ldrh	r2, [fp, #-38]
	bfi	r3, ip, #7, #1
	ldrb	lr, [r4, #2774]	@ zero_extendqisi2
	strh	r1, [fp, #-40]	@ movhi
	bfi	r2, lr, #5, #4
	strb	r3, [fp, #-39]
	strh	r2, [fp, #-38]	@ movhi
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+24
	str	r2, [r8, #24]
	bl	dprint_vfmw
	ldrb	r2, [r4, #2759]	@ zero_extendqisi2
	str	r5, [fp, #-40]
	mov	r3, #0
	bfi	r3, r2, #0, #7
	strb	r3, [fp, #-40]
	ldr	r2, [fp, #-40]
	mov	r0, #4
	ldr	r1, .L24+28
	str	r2, [r8, #28]
	bl	dprint_vfmw
	ldr	r2, [r4, #2784]
	ldr	r1, .L24+32
	mov	r0, #4
	str	r2, [r8, #32]
	bl	dprint_vfmw
	ldrb	r2, [r4, #2779]	@ zero_extendqisi2
	ldrb	r1, [r4, #2780]	@ zero_extendqisi2
	mov	r3, #0
	str	r5, [fp, #-40]
	mov	r0, #4
	bfi	r3, r1, #0, #6
	strb	r2, [fp, #-40]
	strb	r3, [fp, #-38]
	mov	r5, #0
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+36
	str	r2, [r8, #36]
	bl	dprint_vfmw
	ldr	r2, [r4, #2824]
	ldrb	r3, [r4, #2780]	@ zero_extendqisi2
	ldr	r0, [r4, #2820]
	cmp	r3, r2
	ldr	r1, .L24+40
	addhi	r2, r2, #128
	add	r0, r3, r0
	rsbls	r2, r3, r2
	rsbhi	r2, r3, r2
	mov	r3, r5
	bfi	r3, r0, #0, #25
	str	r3, [fp, #-40]
	mov	r0, #4
	mov	r3, r3, lsr #24
	ldrhi	r6, [r4, #2828]
	ldrls	r6, [r4, #2828]
	bfi	r3, r2, #1, #7
	strb	r3, [fp, #-37]
	subhi	r6, r6, #16
	ldr	r2, [fp, #-40]
	str	r2, [r8, #64]
	bl	dprint_vfmw
	ldr	r1, .L24+44
	mov	r2, r5
	mov	r0, #4
	bfi	r2, r6, #0, #24
	str	r2, [fp, #-40]
	str	r2, [r8, #68]
	bl	dprint_vfmw
	ldr	r1, [r4, #2832]
	mov	r3, r5
	ldr	r2, [r4, #2836]
	bfi	r3, r1, #0, #25
	str	r3, [fp, #-40]
	ldr	r1, .L24+48
	mov	r0, #4
	mov	r3, r3, lsr #24
	bfi	r3, r2, #1, #7
	strb	r3, [fp, #-37]
	ldr	r2, [fp, #-40]
	str	r2, [r8, #72]
	bl	dprint_vfmw
	ldr	r2, [r4, #2840]
	mov	r3, r5
	ldr	r1, .L24+52
	bfi	r3, r2, #0, #24
	mov	r0, #4
	str	r3, [fp, #-40]
	mov	r2, r3
	str	r3, [r8, #76]
	bl	dprint_vfmw
	ldr	ip, [r4, #3040]
	ldr	r1, [r4, #3044]
	mov	r0, #4
	ldr	r2, [r4, #3048]
	ldr	r3, [r4, #3052]
	strb	ip, [fp, #-40]
	strb	r1, [fp, #-39]
	strb	r3, [fp, #-37]
	strb	r2, [fp, #-38]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+56
	str	r2, [r8, #80]
	bl	dprint_vfmw
	ldr	ip, [r4, #3056]
	ldr	r1, [r4, #3060]
	mov	r0, #4
	ldr	r2, [r4, #3064]
	ldr	r3, [r4, #3068]
	strb	ip, [fp, #-40]
	strb	r1, [fp, #-39]
	strb	r3, [fp, #-37]
	strb	r2, [fp, #-38]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+60
	str	r2, [r8, #84]
	bl	dprint_vfmw
	ldr	ip, [r4, #3072]
	ldr	r1, [r4, #3076]
	mov	r0, #4
	ldr	r2, [r4, #3080]
	ldr	r3, [r4, #3084]
	strb	ip, [fp, #-40]
	strb	r1, [fp, #-39]
	strb	r3, [fp, #-37]
	strb	r2, [fp, #-38]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+64
	str	r2, [r8, #88]
	bl	dprint_vfmw
	ldr	ip, [r4, #3088]
	ldr	r1, [r4, #3092]
	mov	r0, #4
	ldr	r2, [r4, #3096]
	ldr	r3, [r4, #3100]
	strb	ip, [fp, #-40]
	strb	r1, [fp, #-39]
	strb	r3, [fp, #-37]
	strb	r2, [fp, #-38]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+68
	str	r2, [r8, #92]
	bl	dprint_vfmw
	ldr	ip, [r4, #3104]
	ldr	r3, [r4, #3116]
	mov	r0, #4
	ldr	r1, [r4, #3108]
	ldr	r2, [r4, #3112]
	strb	ip, [fp, #-40]
	strb	r3, [fp, #-37]
	strb	r1, [fp, #-39]
	strb	r2, [fp, #-38]
	ldr	r2, [fp, #-40]
	ldr	r1, .L24+72
	str	r2, [r8, #96]
	bl	dprint_vfmw
	ldr	r2, [r4, #3140]
	ldr	r1, .L24+76
	mov	r0, #4
	str	r2, [r8, #100]
	bl	dprint_vfmw
	ldr	r2, [r4, #3120]
	ldr	r1, .L24+80
	mov	r0, #4
	str	r2, [r8, #128]
	bl	dprint_vfmw
	ldr	r2, [r4, #3124]
	ldr	r1, .L24+84
	mov	r0, #4
	str	r2, [r8, #132]
	bl	dprint_vfmw
	ldr	r2, [r4, #3128]
	ldr	r1, .L24+88
	mov	r0, #4
	str	r2, [r8, #136]
	bl	dprint_vfmw
	ldr	r2, [r4, #3132]
	ldr	r1, .L24+92
	mov	r0, #4
	str	r2, [r8, #140]
	bl	dprint_vfmw
	ldr	r2, [r9, #1144]
	ldr	r1, .L24+96
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r8, #144]
	bl	dprint_vfmw
	ldr	r2, [r9, #1148]
	ldr	r1, .L24+100
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r8, #148]
	bl	dprint_vfmw
	ldr	r2, [r9, #1152]
	ldr	r1, .L24+104
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r8, #152]
	bl	dprint_vfmw
	ldr	r6, [r9, #1188]
	ldr	r1, .L24+108
	mov	r0, #4
	bic	r6, r6, #15
	str	r6, [r8, #156]
	str	r6, [fp, #-40]
	mov	r2, r6
	bl	dprint_vfmw
	mov	r0, r6
	bl	MEM_Phy2Vir
	cmp	r0, r5
	beq	.L23
	ldr	r3, .L24+112
	mov	r2, #2752
	mov	r1, r4
	add	r7, r4, #2832
	add	r6, r8, #252
	add	r7, r7, #12
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r9, #1160]
	ldr	r1, .L24+116
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r8, #160]
	bl	dprint_vfmw
	mov	r0, r8
	bl	MEM_Vir2Phy
	ldr	r1, .L24+120
	add	r2, r0, #256
	mov	r0, #4
	str	r2, [r8, #252]
	bl	dprint_vfmw
.L20:
	ldr	r1, [r7, #4]!
	mov	r3, #0
	ldr	ip, [r4, #2880]
	add	r2, r5, #64
	bfi	r3, r1, #0, #25
	str	r3, [fp, #-40]
	ldr	r1, .L24+124
	mov	r0, #4
	mov	r3, r3, lsr #24
	add	r8, r6, #16
	bfi	r3, ip, #1, #7
	strb	r3, [fp, #-37]
	ldr	r3, [fp, #-40]
	str	r3, [r6, #4]
	bl	dprint_vfmw
	ldr	r1, [r4, #2912]
	add	r2, r5, #65
	mov	r3, #0
	mov	r0, #4
	bfi	r3, r1, #0, #24
	ldr	r1, .L24+124
	str	r3, [fp, #-40]
	str	r3, [r6, #8]
	bl	dprint_vfmw
	ldr	r2, [r4, #2944]
	mov	r3, #0
	ldr	ip, [r4, #2976]
	bfi	r3, r2, #0, #25
	str	r3, [fp, #-40]
	add	r2, r5, #66
	ldr	r1, .L24+124
	mov	r3, r3, lsr #24
	mov	r0, #4
	bfi	r3, ip, #1, #7
	strb	r3, [fp, #-37]
	ldr	r3, [fp, #-40]
	str	r3, [r6, #12]
	bl	dprint_vfmw
	ldr	r1, [r4, #3008]
	add	r2, r5, #67
	mov	r0, #4
	mov	r3, #0
	add	r5, r5, #4
	bfi	r3, r1, #0, #24
	ldr	r1, .L24+124
	str	r3, [fp, #-40]
	add	r4, r4, r0
	str	r3, [r6, #16]
	mov	r6, r8
	bl	dprint_vfmw
	cmp	r5, #32
	bne	.L20
	mov	r0, #0
.L16:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L22:
	ldr	r3, .L24+128
	ldr	r2, .L24+132
	ldr	r1, .L24+136
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L16
.L23:
	ldr	r2, .L24+132
	ldr	r1, .L24+140
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L16
.L25:
	.align	2
.L24:
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC41
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC12
	.word	.LANCHOR0+24
	.word	.LC13
	.word	.LC42
	UNWIND(.fnend)
	.size	VP8HAL_V5R2C1_CfgDnMsg, .-VP8HAL_V5R2C1_CfgDnMsg
	.align	2
	.global	VP8HAL_V5R2C1_StartDec
	.type	VP8HAL_V5R2C1_StartDec, %function
VP8HAL_V5R2C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	movw	r4, #1228
	mul	r4, r4, r1
	ldr	r7, .L35
	cmp	r1, #0
	mov	r5, r1
	mov	r6, r0
	add	r8, r4, r7
	bgt	.L33
	ldr	r3, [r0, #2788]
	cmp	r3, #512
	bhi	.L30
	ldr	r3, [r0, #2792]
	cmp	r3, #512
	bhi	.L30
	ldr	r3, [r4, r7]
	cmp	r3, #0
	beq	.L34
.L31:
	mov	r3, r2
	mov	r1, r8
	mov	r2, r5
	mov	r0, r6
	bl	VP8HAL_V5R2C1_CfgReg
	mov	r2, r5
	mov	r1, r8
	mov	r0, r6
	bl	VP8HAL_V5R2C1_CfgDnMsg
	mov	r0, #0
.L28:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L34:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L32
	str	r3, [r4, r7]
	ldr	r2, [fp, #-40]
	b	.L31
.L33:
	mov	r0, #0
	mov	r3, r1
	str	r0, [sp]
	ldr	r2, .L35+4
	ldr	r1, .L35+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L28
.L30:
	ldr	r3, .L35+12
	mov	r0, #0
	ldr	r2, .L35+4
	ldr	r1, .L35+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L28
.L32:
	ldr	r1, .L35+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L28
.L36:
	.align	2
.L35:
	.word	g_HwMem
	.word	.LANCHOR0+48
	.word	.LC0
	.word	.LC46
	.word	.LC13
	.word	.LC1
	UNWIND(.fnend)
	.size	VP8HAL_V5R2C1_StartDec, .-VP8HAL_V5R2C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14646, %object
	.size	__func__.14646, 21
__func__.14646:
	.ascii	"VP8HAL_V5R2C1_CfgReg\000"
	.space	3
	.type	__func__.14669, %object
	.size	__func__.14669, 23
__func__.14669:
	.ascii	"VP8HAL_V5R2C1_CfgDnMsg\000"
	.space	1
	.type	__func__.14655, %object
	.size	__func__.14655, 23
__func__.14655:
	.ascii	"VP8HAL_V5R2C1_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC1:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC2:
	ASCII(.ascii	"BASIC_CFG0 = 0x%x\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"BASIC_CFG1 = 0x%x\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"VAM_ADDR = 0x%x\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"STREAM_BASE_ADDR = 0x%x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"PPFD_BUF_ADDR = 0x%x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"PPFD_BUF_LEN = 0x%x\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"YSTADDR_1D = 0x%x\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"YSTRIDE_1D = 0x%x\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"UVOFFSET_1D = 0x%x\012\000" )
.LC12:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC13:
	ASCII(.ascii	"%s: %s\012\000" )
.LC14:
	ASCII(.ascii	"D0 = 0x%x\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"D1 = 0x%x\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"D2 = 0x%x\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"D3 = 0x%x\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"D4 = 0x%x\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"D5 = 0x%x\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"D6 = 0x%x\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"D7 = 0x%x\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"D8 = 0x%x\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"D9 = 0x%x\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"D16 = 0x%x\012\000" )
.LC25:
	ASCII(.ascii	"D17 = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"D18 = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"D19 = 0x%x\012\000" )
.LC28:
	ASCII(.ascii	"D20 = 0x%x\012\000" )
.LC29:
	ASCII(.ascii	"D21 = 0x%x\012\000" )
.LC30:
	ASCII(.ascii	"D22 = 0x%x\012\000" )
.LC31:
	ASCII(.ascii	"D23 = 0x%x\012\000" )
.LC32:
	ASCII(.ascii	"D24 = 0x%x\012\000" )
.LC33:
	ASCII(.ascii	"D25 = 0x%x\012\000" )
.LC34:
	ASCII(.ascii	"D32 = 0x%x\012\000" )
.LC35:
	ASCII(.ascii	"D33 = 0x%x\012\000" )
.LC36:
	ASCII(.ascii	"D34 = 0x%x\012\000" )
.LC37:
	ASCII(.ascii	"D35 = 0x%x\012\000" )
.LC38:
	ASCII(.ascii	"D36 = 0x%x\012\000" )
.LC39:
	ASCII(.ascii	"D37 = 0x%x\012\000" )
.LC40:
	ASCII(.ascii	"D38 = 0x%x\012\000" )
.LC41:
	ASCII(.ascii	"D39 = 0x%x\012\000" )
.LC42:
	ASCII(.ascii	"%s: u8Tmp = NULL\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"D40 = 0x%x\012\000" )
.LC44:
	ASCII(.ascii	"D63 = 0x%x\012\000" )
.LC45:
	ASCII(.ascii	"D%d = 0x%x\012\000" )
.LC46:
	ASCII(.ascii	"picture width out of range\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
