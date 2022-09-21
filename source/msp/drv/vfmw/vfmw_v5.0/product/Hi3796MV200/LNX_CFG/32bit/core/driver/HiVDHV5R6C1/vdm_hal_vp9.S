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
	.file	"vdm_hal_vp9.c"
	.text
	.align	2
	.global	VP9HAL_V5R6C1_InitHal
	.type	VP9HAL_V5R6C1_InitHal, %function
VP9HAL_V5R6C1_InitHal:
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
	.size	VP9HAL_V5R6C1_InitHal, .-VP9HAL_V5R6C1_InitHal
	.align	2
	.global	VP9HAL_V5R6C1_CfgReg
	.type	VP9HAL_V5R6C1_CfgReg, %function
VP9HAL_V5R6C1_CfgReg:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	ip, .L27
	mov	r10, r1
	mov	r4, r2, asl #6
	ldr	lr, .L27+4
	sub	r4, r4, r2, asl #3
	ldrb	ip, [ip]	@ zero_extendqisi2
	mov	r6, r0
	mov	r0, #0
	add	lr, lr, r4
	subs	r1, ip, #1
	str	r0, [fp, #-48]
	ldr	lr, [lr, #8]
	mov	r4, r3
	movne	r1, #1
	cmp	r3, r0
	movne	ip, #0
	andeq	ip, r1, #1
	cmp	ip, r0
	bne	.L22
	ldr	r3, .L27+8
	ldr	r9, [r3, lr, asl #2]
	cmp	r9, #0
	ldrne	r9, [r9, #1168]
	cmp	r1, #0
	strneb	r9, [r4, #1]
	cmp	r2, #0
	bgt	.L23
	bne	.L19
	ldr	r3, [r10]
	cmp	r3, #0
	beq	.L24
.L11:
	add	r6, r6, #270336
	ldr	r0, [r10, #1196]
	ldr	r1, [fp, #-48]
	mov	r3, r4
	ldr	r5, [r6, #2088]
	bic	r0, r0, #15
	ldr	ip, [r6, #2092]
	mov	r2, #0
	str	r0, [r6, #2352]
	mov	r0, #8
	ldr	lr, [r10, #1200]
	mov	r8, #3
	mul	ip, r5, ip
	bic	lr, lr, #15
	str	lr, [r6, #2356]
	mov	r5, r2
	movw	r7, #3075
	sub	ip, ip, #1
	movt	r7, 48
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-48]
	mov	r1, r1, lsr #24
	and	r1, r1, #191
	bfc	r1, #7, #1
	strb	r1, [fp, #-45]
	ldr	ip, [fp, #-48]
	mov	r1, ip
	str	ip, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+12
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	mov	r3, #0
	bfi	r3, r9, #4, #1
	strh	r8, [fp, #-46]	@ movhi
	strb	r3, [fp, #-45]
	mov	ip, #0
	ldr	r1, [r6, #2488]
	uxtb	r3, r3
	bfi	r3, r5, #5, #1
	strb	r3, [fp, #-45]
	bfi	ip, r1, #4, #1
	mov	r0, #14
	and	ip, ip, #16
	uxtb	r1, r3
	orr	ip, ip, #64
	ldr	r3, [r6, #2468]
	strb	r0, [fp, #-48]
	mov	r2, r5
	bfi	r1, r3, #6, #1
	mvn	ip, ip, asl #25
	strb	r5, [r6, #2081]
	mvn	ip, ip, lsr #25
	bfi	r1, r5, #7, #1
	strb	ip, [fp, #-47]
	strb	r1, [fp, #-45]
	mov	r3, r4
	ldr	ip, [fp, #-48]
	mov	r0, #12
	mov	r1, ip
	str	ip, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+16
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	ip, [r10, #56]
	mov	r3, r4
	mov	r2, r5
	bic	ip, ip, #15
	mov	r0, #16
	str	ip, [fp, #-56]
	mov	r1, ip
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+20
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	ip, [r10, #40]
	mov	r3, r4
	mov	r2, r5
	bic	ip, ip, #15
	mov	r0, #20
	str	ip, [fp, #-56]
	mov	r1, ip
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+24
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	ip, [r6, #2128]
	mov	r3, r4
	mov	r2, r5
	mov	r0, #24
	mov	r1, ip
	str	ip, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+28
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	ip, [r10, #1164]
	mov	r3, r4
	mov	r2, r5
	bic	ip, ip, #15
	mov	r0, #128
	str	ip, [fp, #-56]
	mov	r1, ip
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L27+32
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r10, [r10, #1168]
	mov	r3, r4
	mov	r2, r5
	mov	r0, #132
	mov	r1, r10
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L27+36
	mov	r0, r8
	bl	dprint_vfmw
	mov	r3, r4
	mov	r2, r5
	mov	r1, r5
	mov	r0, #152
	str	r5, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+40
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r6, #2088]
	mov	r2, r5
	mov	r3, r4
	cmp	r1, #256
	mov	r0, #4
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	mov	r1, r7
	mov	r2, r5
	mov	r3, r4
	mov	r0, #60
	str	r7, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r4
	mov	r2, r5
	mov	r1, r7
	mov	r0, #84
	bl	MFDE_ConfigReg
	cmp	r9, #1
	beq	.L25
.L13:
	ldr	r5, [r6, #2440]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #96
	bic	r5, r5, #15
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+44
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2096]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #100
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+48
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2108]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #104
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+52
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2504]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #108
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+56
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2508]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #116
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+60
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2512]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #120
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+64
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r5, [r6, #2516]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #124
	mov	r1, r5
	str	r5, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+68
	mov	r0, #3
	bl	dprint_vfmw
	cmp	r9, #1
	beq	.L26
.L14:
	mov	r0, #32
	mov	r3, r4
	mov	r2, #0
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L4:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L24:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L12
	str	r3, [r10]
	b	.L11
.L25:
	mov	r2, r5
	mov	r3, r4
	mov	r1, #60
	mov	r0, #92
	bl	MFDE_ConfigReg
	mov	r0, r8
	mov	r2, #60
	ldr	r1, .L27+72
	bl	dprint_vfmw
	b	.L13
.L26:
	ldr	r5, [r6, #2496]
	mov	r3, r4
	mov	r2, #0
	mov	r0, #112
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L27+76
	mov	r0, #3
	bl	dprint_vfmw
	b	.L14
.L23:
	mov	r0, #0
	mov	r3, r2
	str	r0, [sp]
	ldr	r2, .L27+80
	ldr	r1, .L27+84
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L19:
	ldr	r1, .L27+88
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L22:
	ldr	r2, .L27+80
	ldr	r1, .L27+92
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L12:
	ldr	r1, .L27+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4
.L28:
	.align	2
.L27:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC12
	.word	.LC20
	.word	.LANCHOR0
	.word	.LC1
	.word	.LC2
	.word	.LC0
	.word	.LC3
	UNWIND(.fnend)
	.size	VP9HAL_V5R6C1_CfgReg, .-VP9HAL_V5R6C1_CfgReg
	.align	2
	.global	VP9HAL_V5R6C1_CfgFrameMsg
	.type	VP9HAL_V5R6C1_CfgFrameMsg, %function
VP9HAL_V5R6C1_CfgFrameMsg:
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
	mov	r5, r0
	ldr	r0, [r1, #56]
	mov	r10, r1
	bl	MEM_Phy2Vir
	subs	r4, r0, #0
	beq	.L40
	ldr	r3, [r5]
	mov	r0, #4
	ldr	r1, .L44
	add	r6, r5, #270336
	str	r3, [r4]
	ldr	r2, [r4]
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	ldr	r1, .L44+4
	mov	r0, #4
	str	r3, [r4, #4]
	ldr	r2, [r4, #4]
	bl	dprint_vfmw
	ldr	r3, [r5, #8]
	ldr	r1, .L44+8
	mov	r0, #4
	str	r3, [r4, #8]
	ldr	r2, [r4, #8]
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	ldr	r1, .L44+12
	mov	r0, #4
	str	r3, [r4, #12]
	ldr	r2, [r4, #12]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	ldr	r1, .L44+16
	mov	r0, #4
	str	r3, [r4, #16]
	ldr	r2, [r4, #16]
	bl	dprint_vfmw
	ldr	r3, [r5, #20]
	ldr	r1, .L44+20
	mov	r0, #4
	str	r3, [r4, #20]
	ldr	r2, [r4, #20]
	bl	dprint_vfmw
	ldr	r3, [r5, #24]
	ldr	r1, .L44+24
	mov	r0, #4
	str	r3, [r4, #24]
	ldr	r2, [r4, #24]
	bl	dprint_vfmw
	ldr	r3, [r5, #28]
	ldr	r1, .L44+28
	mov	r0, #4
	str	r3, [r4, #28]
	ldr	r2, [r4, #28]
	bl	dprint_vfmw
	ldr	r3, [r5, #32]
	ldr	r1, .L44+32
	mov	r0, #4
	str	r3, [r4, #32]
	ldr	r2, [r4, #32]
	bl	dprint_vfmw
	ldr	r3, [r5, #36]
	ldr	r1, .L44+36
	mov	r0, #4
	str	r3, [r4, #36]
	ldr	r2, [r4, #36]
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	ldr	r1, .L44+40
	mov	r0, #4
	str	r3, [r4, #40]
	ldr	r2, [r4, #40]
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	ldr	r1, .L44+44
	mov	r0, #4
	str	r3, [r4, #44]
	ldr	r2, [r4, #44]
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	ldr	r1, .L44+48
	mov	r0, #4
	str	r3, [r4, #48]
	ldr	r2, [r4, #48]
	bl	dprint_vfmw
	ldr	r3, [r5, #52]
	ldr	r1, .L44+52
	mov	r0, #4
	str	r3, [r4, #52]
	ldr	r2, [r4, #52]
	bl	dprint_vfmw
	ldr	r3, [r5, #56]
	ldr	r1, .L44+56
	mov	r0, #4
	str	r3, [r4, #56]
	ldr	r2, [r4, #56]
	bl	dprint_vfmw
	ldr	r3, [r5, #60]
	ldr	r1, .L44+60
	mov	r0, #4
	str	r3, [r4, #60]
	ldr	r2, [r4, #60]
	bl	dprint_vfmw
	ldr	r3, [r5, #64]
	ldr	r1, .L44+64
	mov	r0, #4
	str	r3, [r4, #64]
	ldr	r2, [r4, #64]
	bl	dprint_vfmw
	ldr	r3, [r5, #68]
	ldr	r1, .L44+68
	mov	r0, #4
	str	r3, [r4, #68]
	ldr	r2, [r4, #68]
	bl	dprint_vfmw
	ldr	r3, [r5, #72]
	ldr	r1, .L44+72
	mov	r0, #4
	str	r3, [r4, #72]
	ldr	r2, [r4, #72]
	bl	dprint_vfmw
	ldr	r3, [r5, #76]
	ldr	r1, .L44+76
	mov	r0, #4
	str	r3, [r4, #76]
	ldr	r2, [r4, #76]
	bl	dprint_vfmw
	ldr	r3, [r5, #80]
	ldr	r1, .L44+80
	mov	r0, #4
	str	r3, [r4, #80]
	ldr	r2, [r4, #80]
	bl	dprint_vfmw
	ldr	r3, [r5, #84]
	ldr	r1, .L44+84
	mov	r0, #4
	str	r3, [r4, #84]
	ldr	r2, [r4, #84]
	bl	dprint_vfmw
	ldr	r3, [r5, #88]
	ldr	r1, .L44+88
	mov	r0, #4
	str	r3, [r4, #88]
	ldr	r2, [r4, #88]
	bl	dprint_vfmw
	ldr	r3, [r5, #92]
	ldr	r1, .L44+92
	mov	r0, #4
	str	r3, [r4, #92]
	ldr	r2, [r4, #92]
	bl	dprint_vfmw
	ldr	r3, [r5, #96]
	ldr	r1, .L44+96
	mov	r0, #4
	str	r3, [r4, #96]
	ldr	r2, [r4, #96]
	bl	dprint_vfmw
	ldr	r3, [r5, #100]
	ldr	r1, .L44+100
	mov	r0, #4
	str	r3, [r4, #100]
	ldr	r2, [r4, #100]
	bl	dprint_vfmw
	ldr	r3, [r5, #104]
	ldr	r1, .L44+104
	mov	r0, #4
	str	r3, [r4, #104]
	ldr	r2, [r4, #104]
	bl	dprint_vfmw
	ldr	r3, [r5, #108]
	ldr	r1, .L44+108
	mov	r0, #4
	str	r3, [r4, #108]
	ldr	r2, [r4, #108]
	bl	dprint_vfmw
	ldr	r3, [r5, #112]
	ldr	r1, .L44+112
	mov	r0, #4
	str	r3, [r4, #112]
	ldr	r2, [r4, #112]
	bl	dprint_vfmw
	ldr	r3, [r5, #116]
	ldr	r1, .L44+116
	mov	r0, #4
	str	r3, [r4, #116]
	ldr	r2, [r4, #116]
	bl	dprint_vfmw
	ldr	r3, [r5, #120]
	ldr	r1, .L44+120
	mov	r0, #4
	str	r3, [r4, #120]
	ldr	r2, [r4, #120]
	bl	dprint_vfmw
	ldr	r3, [r6, #2440]
	ldr	r1, .L44+124
	mov	r0, #4
	str	r3, [r4, #128]
	ldr	r2, [r4, #128]
	bl	dprint_vfmw
	ldr	r3, [r6, #2444]
	ldr	r1, .L44+128
	mov	r0, #4
	str	r3, [r4, #132]
	ldr	r2, [r4, #132]
	bl	dprint_vfmw
	ldr	r3, [r6, #2448]
	ldr	r1, .L44+132
	mov	r0, #4
	str	r3, [r4, #136]
	ldr	r2, [r4, #136]
	bl	dprint_vfmw
	ldr	r3, [r6, #2452]
	ldr	r1, .L44+136
	mov	r0, #4
	str	r3, [r4, #140]
	ldr	r2, [r4, #140]
	bl	dprint_vfmw
	ldr	r3, [r10, #1144]
	ldr	r1, .L44+140
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #144]
	ldr	r2, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r10, #1148]
	ldr	r1, .L44+144
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #148]
	ldr	r2, [r4, #148]
	bl	dprint_vfmw
	ldr	r3, [r10, #1152]
	ldr	r1, .L44+148
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #152]
	ldr	r2, [r4, #152]
	bl	dprint_vfmw
	ldr	r7, [r10, #1196]
	ldr	r1, .L44+152
	mov	r0, #4
	bic	r7, r7, #15
	str	r7, [r4, #156]
	ldr	r2, [r4, #156]
	bl	dprint_vfmw
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L33
	ldr	r7, .L44+156
	movw	r1, #1029
	mov	r2, #4608
	movt	r1, 4
	add	r1, r5, r1
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r10, #1160]
	ldr	r1, .L44+160
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #160]
	ldr	r2, [r4, #160]
	bl	dprint_vfmw
	ldr	r9, [r10, #1200]
	ldr	r1, .L44+164
	mov	r0, #4
	bic	r9, r9, #15
	str	r9, [r4, #164]
	ldr	r2, [r4, #164]
	bl	dprint_vfmw
	mov	r0, r9
	bl	MEM_Phy2Vir
	subs	r9, r0, #0
	beq	.L33
	movw	r1, #5637
	ldr	r3, [r7, #52]
	mov	r2, #4608
	movt	r1, 4
	add	r1, r5, r1
	blx	r3
	ldr	r3, [r6, #2456]
	ldr	r1, .L44+168
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #168]
	ldr	r2, [r4, #168]
	bl	dprint_vfmw
	ldr	r3, [r10, #1192]
	ldr	r1, .L44+172
	mov	r0, #4
	bic	r3, r3, #15
	str	r3, [r4, #172]
	ldr	r2, [r4, #172]
	bl	dprint_vfmw
	ldr	r3, [r5, #180]
	ldr	r1, .L44+176
	mov	r0, #4
	str	r3, [r4, #180]
	ldr	r2, [r4, #180]
	bl	dprint_vfmw
	ldr	r3, [r5, #184]
	ldr	r1, .L44+180
	mov	r0, #4
	str	r3, [r4, #184]
	ldr	r2, [r4, #184]
	bl	dprint_vfmw
	ldr	r3, [r5, #188]
	ldr	r1, .L44+184
	mov	r0, #4
	str	r3, [r4, #188]
	ldr	r2, [r4, #188]
	bl	dprint_vfmw
	ldr	r3, [r5, #192]
	ldr	r1, .L44+188
	mov	r0, #4
	str	r3, [r4, #192]
	ldr	r2, [r4, #192]
	bl	dprint_vfmw
	ldr	r3, [r5, #196]
	ldr	r1, .L44+192
	mov	r0, #4
	str	r3, [r4, #196]
	ldr	r2, [r4, #196]
	bl	dprint_vfmw
	ldr	r3, [r5, #200]
	ldr	r1, .L44+196
	mov	r0, #4
	str	r3, [r4, #200]
	ldr	r2, [r4, #200]
	bl	dprint_vfmw
	ldr	r3, [r5, #204]
	ldr	r1, .L44+200
	mov	r0, #4
	str	r3, [r4, #204]
	ldr	r2, [r4, #204]
	bl	dprint_vfmw
	ldr	r3, [r5, #208]
	ldr	r1, .L44+204
	mov	r0, #4
	str	r3, [r4, #208]
	ldr	r2, [r4, #208]
	bl	dprint_vfmw
	ldr	r3, [r5, #212]
	ldr	r1, .L44+208
	mov	r0, #4
	str	r3, [r4, #212]
	ldr	r2, [r4, #212]
	bl	dprint_vfmw
	ldr	r3, [r5, #216]
	ldr	r1, .L44+212
	mov	r0, #4
	str	r3, [r4, #216]
	ldr	r2, [r4, #216]
	bl	dprint_vfmw
	ldr	r3, [r5, #220]
	ldr	r1, .L44+216
	mov	r0, #4
	str	r3, [r4, #220]
	ldr	r2, [r4, #220]
	bl	dprint_vfmw
	ldr	r3, [r5, #224]
	ldr	r1, .L44+220
	mov	r0, #4
	str	r3, [r4, #224]
	ldr	r2, [r4, #224]
	bl	dprint_vfmw
	ldr	r3, [r5, #228]
	ldr	r1, .L44+224
	mov	r0, #4
	str	r3, [r4, #228]
	ldr	r2, [r4, #228]
	bl	dprint_vfmw
	ldr	r3, [r5, #232]
	ldr	r1, .L44+228
	mov	r0, #4
	str	r3, [r4, #232]
	ldr	r2, [r4, #232]
	bl	dprint_vfmw
	ldr	r3, [r5, #236]
	ldr	r1, .L44+232
	mov	r0, #4
	str	r3, [r4, #236]
	ldr	r2, [r4, #236]
	bl	dprint_vfmw
	ldr	r3, [r5, #240]
	ldr	r1, .L44+236
	mov	r0, #4
	str	r3, [r4, #240]
	ldr	r2, [r4, #240]
	bl	dprint_vfmw
	ldr	r3, [r5, #244]
	ldr	r1, .L44+240
	mov	r0, #4
	str	r3, [r4, #244]
	ldr	r2, [r4, #244]
	bl	dprint_vfmw
	ldr	r3, [r5, #248]
	ldr	r1, .L44+244
	mov	r0, #4
	str	r3, [r4, #248]
	ldr	r2, [r4, #248]
	bl	dprint_vfmw
	ldr	r3, [r10, #60]
	ldr	r1, .L44+248
	mov	r0, #4
	str	r3, [r4, #252]
	ldr	r2, [r4, #252]
	bl	dprint_vfmw
	ldr	r3, [r6, #2520]
	ldr	r1, .L44
	mov	r0, #4
	add	r3, r3, #255
	bic	r3, r3, #255
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	mov	r3, r3, asl r0
	str	r3, [r4, #256]
	ldr	r2, [r4, #256]
	bl	dprint_vfmw
	ldr	r0, [r6, #2520]
	ldr	ip, [r6, #2532]
	add	r3, r0, #255
	ldr	lr, [r6, #2468]
	add	r1, ip, #63
	bic	r2, r3, #255
	bic	r3, r1, #63
	cmp	lr, #1
	mul	r3, r3, r2
	add	r3, r3, r3, lsl #1
	mov	r3, r3, asr #1
	beq	.L41
.L34:
	str	r3, [r4, #260]
	mov	r0, #4
	ldr	r2, [r4, #260]
	ldr	r1, .L44+4
	bl	dprint_vfmw
	ldr	r2, [r6, #2520]
	ldr	r3, [r6, #2532]
	mov	r0, #4
	add	r2, r2, #255
	ldr	r1, .L44+8
	add	r3, r3, #63
	bic	r2, r2, #255
	bic	r3, r3, #63
	mul	r3, r3, r2
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	str	r3, [r4, #264]
	ldr	r2, [r4, #264]
	bl	dprint_vfmw
	ldr	r3, [r6, #2524]
	ldr	r1, .L44+12
	mov	r0, #4
	add	r3, r3, #255
	bic	r3, r3, #255
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	mov	r3, r3, asl r0
	str	r3, [r4, #268]
	ldr	r2, [r4, #268]
	bl	dprint_vfmw
	ldr	r2, [r6, #2524]
	ldr	r3, [r6, #2536]
	add	r2, r2, #255
	ldr	r1, [r6, #2468]
	add	r3, r3, #63
	bic	r2, r2, #255
	bic	r3, r3, #63
	cmp	r1, #1
	mul	r3, r3, r2
	add	r3, r3, r3, lsl #1
	mov	r3, r3, asr #1
	beq	.L42
.L35:
	str	r3, [r4, #272]
	mov	r0, #4
	ldr	r2, [r4, #272]
	ldr	r1, .L44+16
	bl	dprint_vfmw
	ldr	r2, [r6, #2524]
	ldr	r3, [r6, #2536]
	mov	r0, #4
	add	r2, r2, #255
	ldr	r1, .L44+20
	add	r3, r3, #63
	bic	r2, r2, #255
	bic	r3, r3, #63
	mul	r3, r3, r2
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	str	r3, [r4, #276]
	ldr	r2, [r4, #276]
	bl	dprint_vfmw
	ldr	r3, [r6, #2528]
	ldr	r1, .L44+24
	mov	r0, #4
	add	r3, r3, #255
	bic	r3, r3, #255
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	mov	r3, r3, asl r0
	str	r3, [r4, #280]
	ldr	r2, [r4, #280]
	bl	dprint_vfmw
	ldr	r2, [r6, #2528]
	ldr	r3, [r6, #2540]
	add	r2, r2, #255
	ldr	r1, [r6, #2468]
	add	r3, r3, #63
	bic	r2, r2, #255
	bic	r3, r3, #63
	cmp	r1, #1
	mul	r3, r3, r2
	add	r3, r3, r3, lsl #1
	mov	r3, r3, asr #1
	beq	.L43
.L36:
	str	r3, [r4, #284]
	mov	r0, #4
	ldr	r2, [r4, #284]
	ldr	r1, .L44+28
	bl	dprint_vfmw
	ldr	r2, [r6, #2528]
	ldr	r3, [r6, #2540]
	mov	r0, #4
	add	r2, r2, #255
	ldr	r1, .L44+32
	add	r3, r3, #63
	bic	r2, r2, #255
	bic	r3, r3, #63
	mul	r3, r3, r2
	cmp	r3, #0
	add	r2, r3, #3
	movlt	r3, r2
	mov	r3, r3, asr #2
	str	r3, [r4, #288]
	ldr	r2, [r4, #288]
	bl	dprint_vfmw
	mov	r0, r8
	ldr	r3, [r7, #140]
	mov	r2, #4608
	ldr	r1, [r6, #2352]
	blx	r3
	mov	r0, r9
	ldr	r3, [r7, #140]
	mov	r2, #4608
	ldr	r1, [r6, #2356]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L41:
	add	r2, r0, #2032
	cmp	r1, #0
	add	r2, r2, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	r2, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, r2
	mov	r0, r0, asr #11
	mov	r2, r1, asl #7
	sub	r1, r2, r1, asl #5
	mov	r0, r0, asl #4
	mul	r1, r0, r1
	add	r3, r3, r1, lsr #1
	b	.L34
.L43:
	ldr	r0, [r6, #2520]
	ldr	ip, [r6, #2532]
	add	r2, r0, #2032
	add	r0, r0, #4080
	add	r2, r2, #15
	adds	r1, ip, #63
	addmi	r1, ip, #126
	add	r0, r0, #14
	cmp	r2, #0
	mov	r1, r1, asr #6
	movlt	r2, r0
	mov	r2, r2, asr #11
	mov	r0, r1, asl #7
	sub	r1, r0, r1, asl #5
	mov	r2, r2, asl #4
	mul	r2, r2, r1
	add	r3, r3, r2, lsr #1
	b	.L36
.L42:
	ldr	r0, [r6, #2520]
	ldr	ip, [r6, #2532]
	add	r2, r0, #2032
	add	r0, r0, #4080
	add	r2, r2, #15
	adds	r1, ip, #63
	addmi	r1, ip, #126
	add	r0, r0, #14
	cmp	r2, #0
	mov	r1, r1, asr #6
	movlt	r2, r0
	mov	r2, r2, asr #11
	mov	r0, r1, asl #7
	sub	r1, r0, r1, asl #5
	mov	r2, r2, asl #4
	mul	r2, r2, r1
	add	r3, r3, r2, lsr #1
	b	.L35
.L33:
	ldr	r2, .L44+252
	mov	r0, #0
	ldr	r1, .L44+256
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L40:
	ldr	r3, .L44+260
	ldr	r2, .L44+252
	ldr	r1, .L44+264
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L45:
	.align	2
.L44:
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
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC63
	.word	.LC64
	.word	.LC65
	.word	.LC66
	.word	.LC67
	.word	.LC68
	.word	.LC69
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
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
	.word	.LANCHOR0+24
	.word	.LC62
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	VP9HAL_V5R6C1_CfgFrameMsg, .-VP9HAL_V5R6C1_CfgFrameMsg
	.align	2
	.global	VP9HAL_V5R6C1_CfgTileMsg
	.type	VP9HAL_V5R6C1_CfgTileMsg, %function
VP9HAL_V5R6C1_CfgTileMsg:
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
	ldr	r7, [r1, #60]
	mov	r5, r0
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r9, r0, #0
	beq	.L55
	add	r8, r5, #262144
	ldr	r2, [r8, #1024]
	sub	r3, r2, #1
	cmp	r3, #1024
	bcs	.L56
.L49:
	cmp	r2, #0
	movne	r4, r9
	movne	r6, #0
	beq	.L53
.L52:
	ldr	r3, [r5, #1024]
	mov	r0, #4
	ldr	r1, .L57
	add	r5, r5, #256
	add	r4, r4, #256
	str	r3, [r4, #-256]
	ldr	r2, [r4, #-256]
	bl	dprint_vfmw
	ldr	r3, [r5, #772]
	ldr	r1, .L57+4
	mov	r0, #4
	str	r3, [r4, #-252]
	ldr	r2, [r4, #-252]
	bl	dprint_vfmw
	ldr	r3, [r5, #776]
	ldr	r1, .L57+8
	mov	r0, #4
	str	r3, [r4, #-248]
	ldr	r2, [r4, #-248]
	bl	dprint_vfmw
	ldr	r3, [r5, #780]
	ldr	r1, .L57+12
	mov	r0, #4
	str	r3, [r4, #-244]
	ldr	r2, [r4, #-244]
	bl	dprint_vfmw
	ldr	r3, [r5, #784]
	ldr	r1, .L57+16
	mov	r0, #4
	str	r3, [r4, #-240]
	ldr	r2, [r4, #-240]
	bl	dprint_vfmw
	ldr	r3, [r5, #788]
	ldr	r1, .L57+20
	mov	r0, #4
	str	r3, [r4, #-236]
	ldr	r2, [r4, #-236]
	bl	dprint_vfmw
	ldr	r3, [r5, #792]
	ldr	r1, .L57+24
	mov	r0, #4
	str	r3, [r4, #-232]
	ldr	r2, [r4, #-232]
	bl	dprint_vfmw
	ldr	r3, [r5, #796]
	ldr	r1, .L57+28
	mov	r0, #4
	str	r3, [r4, #-228]
	ldr	r2, [r4, #-228]
	bl	dprint_vfmw
	ldr	r3, [r5, #800]
	ldr	r1, .L57+32
	mov	r0, #4
	str	r3, [r4, #-224]
	ldr	r2, [r4, #-224]
	bl	dprint_vfmw
	ldr	r3, [r5, #804]
	ldr	r1, .L57+36
	mov	r0, #4
	str	r3, [r4, #-220]
	ldr	r2, [r4, #-220]
	bl	dprint_vfmw
	ldr	r3, [r5, #808]
	ldr	r1, .L57+40
	mov	r0, #4
	str	r3, [r4, #-216]
	ldr	r2, [r4, #-216]
	bl	dprint_vfmw
	ldr	r3, [r5, #812]
	ldr	r1, .L57+44
	mov	r0, #4
	str	r3, [r4, #-212]
	ldr	r2, [r4, #-212]
	bl	dprint_vfmw
	ldr	r3, [r5, #1020]
	ldr	r1, .L57+48
	mov	r0, #4
	str	r3, [r4, #-4]
	ldr	r2, [r4, #-4]
	bl	dprint_vfmw
	cmp	r6, #0
	strgt	r7, [r4, #-260]
	add	r6, r6, #1
	ldr	r3, [r8, #1024]
	add	r7, r7, #256
	cmp	r6, r3
	bcc	.L52
	cmp	r3, #1
	bls	.L53
	add	r3, r9, r3, lsl #8
	mov	r2, #0
	mov	r0, r2
	str	r2, [r3, #-4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L56:
	ldr	r1, .L57+52
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r2, [r8, #1024]
	b	.L49
.L53:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L55:
	ldr	r3, .L57+56
	ldr	r2, .L57+60
	ldr	r1, .L57+64
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L58:
	.align	2
.L57:
	.word	.LC87
	.word	.LC88
	.word	.LC89
	.word	.LC90
	.word	.LC91
	.word	.LC92
	.word	.LC93
	.word	.LC94
	.word	.LC95
	.word	.LC96
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC86
	.word	.LC21
	.word	.LANCHOR0+52
	.word	.LC22
	UNWIND(.fnend)
	.size	VP9HAL_V5R6C1_CfgTileMsg, .-VP9HAL_V5R6C1_CfgTileMsg
	.align	2
	.global	VP9HAL_V5R6C1_CalcSize
	.type	VP9HAL_V5R6C1_CalcSize, %function
VP9HAL_V5R6C1_CalcSize:
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
	add	r4, r0, #270336
	ldr	r0, [r4, #2480]
	ldr	r6, [r4, #2472]
	ldr	r5, [r4, #2088]
	ldr	r7, [r4, #2092]
	ldr	r8, [r4, #2468]
	bl	GetCompressRatio
	mov	r5, r5, asl #6
	mov	r7, r7, asl #6
	add	r9, r7, #63
	mov	r10, r0
	ldr	r0, [r4, #2484]
	bl	GetCompressRatio
	add	r2, r5, #255
	bic	r2, r2, #255
	bic	lr, r9, #63
	mov	r1, r2, asl #4
	mov	ip, r2, asl #3
	mul	r1, r10, r1
	add	r3, r1, #7
	cmp	r1, #0
	movlt	r1, r3
	mov	r1, r1, asr #3
	str	r1, [r4, #2096]
	mov	r1, r1, lsr #4
	mul	r3, lr, r1
	str	r3, [r4, #2108]
	mul	r0, r0, ip
	cmp	r0, #0
	add	ip, r0, #7
	movlt	r0, ip
	cmp	r6, #0
	cmpeq	r8, #1
	mov	r0, r0, asr #3
	str	r0, [r4, #2104]
	movne	r6, #0
	moveq	r6, #1
	strne	r6, [r4, #2500]
	strne	r6, [r4, #2504]
	bne	.L61
	add	r1, r5, #2032
	add	r5, r5, #4080
	add	r1, r1, #15
	add	r5, r5, #14
	cmp	r1, #0
	movlt	r1, r5
	cmp	r9, #0
	addlt	r9, r7, #126
	mov	r1, r1, asr #11
	mov	r9, r9, asr #6
	mov	r5, r1, asl #4
	str	r5, [r4, #2500]
	mov	r1, r9, asl #5
	mul	r1, r5, r1
	add	r3, r3, r1
	str	r3, [r4, #2108]
	str	r1, [r4, #2504]
.L61:
	add	r1, r2, #3
	cmp	r2, #0
	add	r3, r3, r3, lsl #1
	movlt	r2, r1
	mov	r3, r3, lsr #1
	str	r3, [r4, #2512]
	mov	r3, r2, asr #2
	mov	r3, r3, asl #5
	str	r3, [r4, #2508]
	mov	r3, r3, lsr #5
	mul	r3, lr, r3
	str	r3, [r4, #2516]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9HAL_V5R6C1_CalcSize, .-VP9HAL_V5R6C1_CalcSize
	.align	2
	.global	VP9HAL_V5R6C1_StartDec
	.type	VP9HAL_V5R6C1_StartDec, %function
VP9HAL_V5R6C1_StartDec:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r5, .L75
	cmp	r1, #0
	movw	r4, #1228
	mov	r6, r0
	mov	r7, r2
	mla	r4, r4, r1, r5
	bgt	.L73
	bne	.L71
	add	r1, r0, #270336
	ldr	r3, [r1, #2088]
	cmp	r3, #512
	bhi	.L67
	ldr	r3, [r1, #2092]
	cmp	r3, #512
	bhi	.L67
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L74
.L69:
	mov	r0, r6
	bl	VP9HAL_V5R6C1_CalcSize
	mov	r3, r7
	mov	r2, #0
	mov	r1, r4
	mov	r0, r6
	bl	VP9HAL_V5R6C1_CfgReg
	mov	r2, #0
	mov	r1, r4
	mov	r0, r6
	bl	VP9HAL_V5R6C1_CfgFrameMsg
	mov	r1, r4
	mov	r0, r6
	mov	r2, #0
	bl	VP9HAL_V5R6C1_CfgTileMsg
	mov	r0, #0
.L64:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L74:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L70
	str	r3, [r5]
	b	.L69
.L73:
	mov	r0, #0
	mov	r3, r1
	str	r0, [sp]
	ldr	r2, .L75+4
	ldr	r1, .L75+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L67:
	ldr	r3, .L75+12
	mov	r0, #0
	ldr	r2, .L75+4
	ldr	r1, .L75+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L71:
	ldr	r1, .L75+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L70:
	ldr	r1, .L75+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L64
.L76:
	.align	2
.L75:
	.word	g_HwMem
	.word	.LANCHOR0+80
	.word	.LC1
	.word	.LC101
	.word	.LC22
	.word	.LC100
	.word	.LC3
	UNWIND(.fnend)
	.size	VP9HAL_V5R6C1_StartDec, .-VP9HAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14995, %object
	.size	__func__.14995, 21
__func__.14995:
	.ascii	"VP9HAL_V5R6C1_CfgReg\000"
	.space	3
	.type	__func__.15012, %object
	.size	__func__.15012, 26
__func__.15012:
	.ascii	"VP9HAL_V5R6C1_CfgFrameMsg\000"
	.space	2
	.type	__func__.15023, %object
	.size	__func__.15023, 25
__func__.15023:
	.ascii	"VP9HAL_V5R6C1_CfgTileMsg\000"
	.space	3
	.type	__func__.15044, %object
	.size	__func__.15044, 23
__func__.15044:
	.ascii	"VP9HAL_V5R6C1_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC2:
	ASCII(.ascii	"VdhId is wrong! VP9HAL_V5R6C1_CfgReg\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC4:
	ASCII(.ascii	"BASIC_CFG0 = 0x%x\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"BASIC_CFG1 = 0x%x\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"VAM_ADDR = 0x%x\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"STREAM_BASE_ADDR = 0x%x\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"PPFD_BUF_ADDR = 0x%x\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"PPFD_BUF_LEN = 0x%x\012\000" )
	.space	3
.LC11:
	ASCII(.ascii	"FF_APT_EN = 0x%x\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"DEC_OVER_INT_LEVEL=0x%x\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"YSTADDR_1D = 0x%x\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"YSTRIDE_1D = 0x%x\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"UVOFFSET_1D = 0x%x\012\000" )
.LC16:
	ASCII(.ascii	"HEAD_INF_OFFSET = 0x%x\012\000" )
.LC17:
	ASCII(.ascii	"HEVC_VFMW_YSTRIDE_2BIT = 0x%x\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"HEVC_VFMW_YOFFSET_2BIT = 0x%x\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"HEVC_VFMW_UVOFFSET_2BIT = 0x%x\012\000" )
.LC20:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"%s: %s\012\000" )
.LC23:
	ASCII(.ascii	"PicMsg D[0] = 0x%x\012\000" )
.LC24:
	ASCII(.ascii	"PicMsg D[1] = 0x%x\012\000" )
.LC25:
	ASCII(.ascii	"PicMsg D[2] = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"PicMsg D[3] = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"PicMsg D[4] = 0x%x\012\000" )
.LC28:
	ASCII(.ascii	"PicMsg D[5] = 0x%x\012\000" )
.LC29:
	ASCII(.ascii	"PicMsg D[6] = 0x%x\012\000" )
.LC30:
	ASCII(.ascii	"PicMsg D[7] = 0x%x\012\000" )
.LC31:
	ASCII(.ascii	"PicMsg D[8] = 0x%x\012\000" )
.LC32:
	ASCII(.ascii	"PicMsg D[9] = 0x%x\012\000" )
.LC33:
	ASCII(.ascii	"PicMsg D[10] = 0x%x\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"PicMsg D[11] = 0x%x\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"PicMsg D[12] = 0x%x\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"PicMsg D[13] = 0x%x\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"PicMsg D[14] = 0x%x\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"PicMsg D[15] = 0x%x\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"PicMsg D[16] = 0x%x\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"PicMsg D[17] = 0x%x\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"PicMsg D[18] = 0x%x\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"PicMsg D[19] = 0x%x\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"PicMsg D[20] = 0x%x\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"PicMsg D[21] = 0x%x\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"PicMsg D[22] = 0x%x\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"PicMsg D[23] = 0x%x\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"PicMsg D[24] = 0x%x\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"PicMsg D[25] = 0x%x\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"PicMsg D[26] = 0x%x\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"PicMsg D[27] = 0x%x\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"PicMsg D[28] = 0x%x\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"PicMsg D[29] = 0x%x\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"PicMsg D[30] = 0x%x\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"PicMsg D[32] = 0x%x\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"PicMsg D[33] = 0x%x\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"PicMsg D[34] = 0x%x\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"PicMsg D[35] = 0x%x\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"PicMsg D[36] = 0x%x\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"PicMsg D[37] = 0x%x\012\000" )
	.space	3
.LC60:
	ASCII(.ascii	"PicMsg D[38] = 0x%x\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"PicMsg D[39] = 0x%x\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"%s: pu8Vir = NULL\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"PicMsg D[40] = 0x%x\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"PicMsg D[41] = 0x%x\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"PicMsg D[42] = 0x%x\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"PicMsg D[43] = 0x%x\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"PicMsg D[45] = 0x%x\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"PicMsg D[46] = 0x%x\012\000" )
	.space	3
.LC69:
	ASCII(.ascii	"PicMsg D[47] = 0x%x\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"PicMsg D[48] = 0x%x\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"PicMsg D[49] = 0x%x\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"PicMsg D[50] = 0x%x\012\000" )
	.space	3
.LC73:
	ASCII(.ascii	"PicMsg D[51] = 0x%x\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"PicMsg D[52] = 0x%x\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"PicMsg D[53] = 0x%x\012\000" )
	.space	3
.LC76:
	ASCII(.ascii	"PicMsg D[54] = 0x%x\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"PicMsg D[55] = 0x%x\012\000" )
	.space	3
.LC78:
	ASCII(.ascii	"PicMsg D[56] = 0x%x\012\000" )
	.space	3
.LC79:
	ASCII(.ascii	"PicMsg D[57] = 0x%x\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"PicMsg D[58] = 0x%x\012\000" )
	.space	3
.LC81:
	ASCII(.ascii	"PicMsg D[59] = 0x%x\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"PicMsg D[60] = 0x%x\012\000" )
	.space	3
.LC83:
	ASCII(.ascii	"PicMsg D[61] = 0x%x\012\000" )
	.space	3
.LC84:
	ASCII(.ascii	"PicMsg D[62] = 0x%x\012\000" )
	.space	3
.LC85:
	ASCII(.ascii	"PicMsg D[63] = 0x%x\012\000" )
	.space	3
.LC86:
	ASCII(.ascii	"ERROR: pVp9DecParam->TotalTileNum(%d) out of [0-102" )
	ASCII(.ascii	"4]\012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"TileMsg D[0] = 0x%x\012\000" )
	.space	3
.LC88:
	ASCII(.ascii	"TileMsg D[1] = 0x%x\012\000" )
	.space	3
.LC89:
	ASCII(.ascii	"TileMsg D[2] = 0x%x\012\000" )
	.space	3
.LC90:
	ASCII(.ascii	"TileMsg D[3] = 0x%x\012\000" )
	.space	3
.LC91:
	ASCII(.ascii	"TileMsg D[4] = 0x%x\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"TileMsg D[5] = 0x%x\012\000" )
	.space	3
.LC93:
	ASCII(.ascii	"TileMsg D[6] = 0x%x\012\000" )
	.space	3
.LC94:
	ASCII(.ascii	"TileMsg D[7] = 0x%x\012\000" )
	.space	3
.LC95:
	ASCII(.ascii	"TileMsg D[8] = 0x%x\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"TileMsg D[9] = 0x%x\012\000" )
	.space	3
.LC97:
	ASCII(.ascii	"TileMsg D[10] = 0x%x\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"TileMsg D[11] = 0x%x\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"TileMsg D[63] = 0x%x\012\000" )
	.space	2
.LC100:
	ASCII(.ascii	"VdhId is wrong! VP9HAL_V5R6C1_StartDec\012\000" )
.LC101:
	ASCII(.ascii	"picture width out of range\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
