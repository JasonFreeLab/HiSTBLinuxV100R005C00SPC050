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
	.file	"drv_venc_hal.c"
	.text
	.align	2
	.type	DRV_VENC_HAL_SetDefaultAttrByStartQP, %function
DRV_VENC_HAL_SetDefaultAttrByStartQP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #25
	mov	r5, r0
	movls	r6, #0
	bls	.L2
	sub	r3, r1, #26
	cmp	r3, #3
	movls	r6, #1
	bls	.L2
	sub	r3, r1, #30
	cmp	r3, #4
	movls	r6, #2
	bls	.L2
	sub	r1, r1, #35
	cmp	r1, #7
	movcc	r6, #3
	movcs	r6, #4
.L2:
	cmp	r2, #0
	movw	r3, #2620
	mov	r2, #84
	mov	r0, r5
	moveq	r4, r3
	movne	r4, #0
	mla	r1, r2, r6, r4
	add	r1, r5, r1
	add	r1, r1, #524
	bl	memcpy
	mov	r2, #408
	mla	r1, r2, r6, r4
	add	r0, r5, #84
	add	r1, r5, r1
	add	r1, r1, #944
	bl	memcpy
	add	ip, r4, r6, lsl #5
	add	ip, r5, ip
	add	lr, r5, #492
	add	ip, ip, #2976
	add	ip, ip, #8
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_SetDefaultAttrByStartQP, .-DRV_VENC_HAL_SetDefaultAttrByStartQP
	.align	2
	.type	CfgSwL0Size, %function
CfgSwL0Size:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #4]
	ldr	r1, .L14
	cmp	r2, #2
	ldr	ip, [r0, #688]
	ldr	r1, [r1]
	beq	.L13
	cmp	r2, #0
	moveq	r2, #15
	moveq	r3, #0
	bfieq	r3, r2, #16, #6
	moveq	r2, #31
	bfieq	r3, r2, #0, #7
.L10:
	ldr	r2, [r0, #56]
	cmp	r2, #0
	strne	r3, [ip, #80]
	streq	r3, [r1, #124]
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r2, #19
	mov	r3, #0
	bfi	r3, r2, #16, #6
	mov	r2, #27
	bfi	r3, r2, #0, #7
	b	.L10
.L15:
	.align	2
.L14:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	CfgSwL0Size, .-CfgSwL0Size
	.align	2
	.type	DRV_VENC_HAL_SetDefaultAttrByProtocol, %function
DRV_VENC_HAL_SetDefaultAttrByProtocol:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	bne	.L17
	ldr	r1, .L27
	add	r2, r0, #168
	add	r3, r0, #328
.L18:
	ldr	ip, [r1, #4]!
	str	ip, [r2, #4]!
	cmp	r2, r3
	bne	.L18
	ldr	r2, .L27+4
	add	ip, r0, #488
.L19:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, ip
	bne	.L19
	mov	r3, #4
	mov	r2, #32
	str	r3, [r0, #100]
	mov	r5, #9
	mov	r3, #0
	str	r2, [r0, #520]
	str	r3, [r0, #108]
	mov	r2, #7
	str	r3, [r0, #112]
	mov	r4, #11
	str	r3, [r0, #116]
	mov	lr, #14
	str	r3, [r0, #120]
	mov	ip, #18
	str	r3, [r0, #124]
	mov	r1, #25
	mov	r3, #255
	str	r2, [r0, #128]
	str	r2, [r0, #132]
	str	r2, [r0, #136]
	str	r5, [r0, #140]
	str	r4, [r0, #144]
	str	lr, [r0, #148]
	str	ip, [r0, #152]
	str	r1, [r0, #156]
	str	r3, [r0, #160]
	str	r3, [r0, #164]
	str	r3, [r0, #168]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L17:
	ldr	r1, .L27+8
	add	r2, r0, #168
	add	r3, r0, #328
.L21:
	ldr	ip, [r1, #4]!
	str	ip, [r2, #4]!
	cmp	r2, r3
	bne	.L21
	ldr	r2, .L27+12
	add	ip, r0, #488
.L22:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, ip
	bne	.L22
	mov	r3, #2
	mov	r2, #96
	mov	r1, #3
	str	r3, [r0, #100]
	str	r2, [r0, #520]
	mov	r3, #0
	mov	r2, #5
	str	r3, [r0, #108]
	str	r3, [r0, #112]
	mov	r4, #10
	str	r3, [r0, #116]
	mov	lr, #15
	str	r3, [r0, #120]
	mov	ip, #20
	mov	r3, #255
	str	r1, [r0, #124]
	str	r1, [r0, #128]
	str	r2, [r0, #132]
	str	r2, [r0, #136]
	str	r4, [r0, #140]
	str	lr, [r0, #144]
	str	ip, [r0, #148]
	str	r3, [r0, #152]
	str	r3, [r0, #156]
	str	r3, [r0, #160]
	str	r3, [r0, #164]
	str	r3, [r0, #168]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L28:
	.align	2
.L27:
	.word	.LANCHOR1-4
	.word	.LANCHOR1+156
	.word	.LANCHOR1+316
	.word	.LANCHOR1+476
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_SetDefaultAttrByProtocol, .-DRV_VENC_HAL_SetDefaultAttrByProtocol
	.align	2
	.type	CfgStrFmt.isra.6, %function
CfgStrFmt.isra.6:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #60]
	mov	r3, #0
	ldr	ip, .L36
	bfi	r3, r1, #14, #1
	cmp	r2, #0
	ldr	lr, [r0, #688]
	ldr	ip, [ip]
	bne	.L30
	ldr	r1, [r0, #64]
	clz	r1, r1
	mov	r1, r1, lsr #5
	bfi	r3, r1, #16, #8
.L31:
	bfi	r3, r2, #6, #4
	ldr	r2, [r0, #56]
	bfc	r3, #3, #3
	bfc	r3, #2, #1
	cmp	r2, #0
	bfc	r3, #1, #1
	bfc	r3, #0, #1
	strne	r3, [lr, #236]
	streq	r3, [ip, #284]
	ldmfd	sp, {fp, sp, pc}
.L30:
	cmp	r2, #2
	ldr	r1, [r0, #64]
	moveq	r2, #3
	bfi	r3, r1, #16, #8
	beq	.L31
	cmp	r2, #1
	moveq	r2, #6
	movne	r2, #0
	b	.L31
.L37:
	.align	2
.L36:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	CfgStrFmt.isra.6, .-CfgStrFmt.isra.6
	.align	2
	.type	CfgVcpiMode.isra.7, %function
CfgVcpiMode.isra.7:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r3, #2912]
	mov	ip, #0
	ldr	lr, [r0, #4]
	ldr	r4, .L42
	bfi	ip, r5, #31, #1
	cmp	lr, #2
	bfc	ip, #28, #2
	ldr	r5, [r4]
	moveq	r4, #1
	bfieq	ip, r4, #26, #2
	beq	.L40
	cmp	lr, #0
	bfieq	ip, lr, #26, #2
	orrne	ip, ip, #201326592
.L40:
	ldr	r4, [r3, #2616]
	subs	lr, lr, #2
	ldr	r6, [r3, #2600]
	bfi	ip, r4, #30, #1
	ldr	r7, [r3, #2604]
	ldr	r4, [r0, #536]
	bfi	ip, r1, #18, #2
	bfi	ip, r6, #21, #1
	ldr	r6, [r3]
	clz	r1, r4
	bfi	ip, r7, #17, #1
	bfi	ip, r4, #16, #1
	ldr	r4, [r3, #2584]
	bfi	ip, r2, #12, #1
	mov	r1, r1, lsr #5
	bfi	ip, r1, #10, #2
	ldr	r2, [r3, #2636]
	bfi	ip, r6, #9, #1
	ldr	r1, [r3, #2640]
	bfi	ip, r4, #8, #1
	ldr	r4, [r0, #40]
	bfi	ip, r2, #7, #1
	ldr	r2, [r0, #56]
	bfi	ip, r1, #6, #1
	movne	lr, #1
	bfi	ip, r4, #5, #1
	ldr	r1, [r3, #2436]
	bfi	ip, lr, #2, #2
	adds	r3, r2, #0
	bfc	ip, #15, #1
	movne	r3, #1
	bfi	ip, r3, #4, #1
	orr	ip, ip, #2
	bfi	ip, r1, #0, #1
	str	ip, [r5, #28]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L43:
	.align	2
.L42:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	CfgVcpiMode.isra.7, .-CfgVcpiMode.isra.7
	.align	2
	.global	DRV_VENC_HAL_V500R001_ClrInt
	.type	DRV_VENC_HAL_V500R001_ClrInt, %function
DRV_VENC_HAL_V500R001_ClrInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L53
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L46
	bcc	.L47
	cmp	r0, #2
	bne	.L52
	ldr	r2, [r3, #4]
	orr	r2, r2, #64
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L52:
	mvn	r2, #0
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L47:
	ldr	r2, [r3, #4]
	orr	r2, r2, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L46:
	ldr	r2, [r3, #4]
	orr	r2, r2, #2
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_ClrInt, .-DRV_VENC_HAL_V500R001_ClrInt
	.align	2
	.global	DRV_VENC_HAL_V500R001_DisableInt
	.type	DRV_VENC_HAL_V500R001_DisableInt, %function
DRV_VENC_HAL_V500R001_DisableInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L64
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L57
	bcc	.L58
	cmp	r0, #2
	bne	.L63
	ldr	r2, [r3]
	bfc	r2, #6, #1
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L63:
	mov	r2, #0
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L58:
	ldr	r2, [r3]
	bfc	r2, #0, #1
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L57:
	ldr	r2, [r3]
	bfc	r2, #1, #1
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L65:
	.align	2
.L64:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_DisableInt, .-DRV_VENC_HAL_V500R001_DisableInt
	.align	2
	.global	DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.type	DRV_VENC_HAL_V500R001_ReadReg_Smmu, %function
DRV_VENC_HAL_V500R001_ReadReg_Smmu:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L67
	mov	r2, r0
	mvn	ip, #0
	mov	r0, #0
	ldr	r3, [r3]
	add	r3, r3, #61440
	ldr	r1, [r3, #40]
	and	r1, r1, #1
	str	r1, [r2]
	ldr	r1, [r3, #40]
	ubfx	r1, r1, #1, #1
	str	r1, [r2, #4]
	ldr	r1, [r3, #40]
	ubfx	r1, r1, #2, #1
	str	r1, [r2, #8]
	ldr	r1, [r3, #40]
	ubfx	r1, r1, #3, #1
	str	r1, [r2, #12]
	ldr	r1, [r3, #24]
	and	r1, r1, #1
	str	r1, [r2, #16]
	ldr	r1, [r3, #24]
	ubfx	r1, r1, #1, #1
	str	r1, [r2, #20]
	ldr	r1, [r3, #24]
	ubfx	r1, r1, #2, #1
	str	r1, [r2, #24]
	ldr	r1, [r3, #24]
	ubfx	r1, r1, #3, #1
	str	r1, [r2, #28]
	ldr	r1, [r3, #864]
	str	r1, [r2, #32]
	ldr	r1, [r3, #848]
	str	r1, [r2, #40]
	ldr	r1, [r3, #832]
	str	r1, [r2, #36]
	ldr	r1, [r3, #816]
	str	r1, [r2, #44]
	str	ip, [r3, #28]
	ldmfd	sp, {fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_ReadReg_Smmu, .-DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.align	2
	.global	DRV_VENC_HAL_V500R001_ReadReg
	.type	DRV_VENC_HAL_V500R001_ReadReg, %function
DRV_VENC_HAL_V500R001_ReadReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L74
	mov	r2, r0
	ldmia	r1, {r3, ip}
	add	r3, r3, #12288
	ldr	r1, [r3, #4]
	and	r1, r1, #1
	str	r1, [r0, #8]
	ldr	r1, [r3, #4]
	ubfx	r1, r1, #2, #1
	str	r1, [r0, #12]
	ldr	r0, [r3, #4]
	ubfx	r0, r0, #6, #1
	str	r0, [r2]
	ldr	r0, [r3, #4]
	ubfx	r0, r0, #1, #1
	str	r0, [r2, #4]
	ldr	r0, [r3, #4]
	ubfx	r0, r0, #3, #1
	str	r0, [r2, #16]
	orrs	r1, r0, r1
	bne	.L70
	ldr	r1, [ip, #4]
	cmp	r1, #0
	beq	.L73
	ldr	r1, [r3, #1984]
	mov	r1, r1, asl #3
	str	r1, [r2, #20]
	ldr	r1, [r3, #2756]
	ldr	ip, [r3, #2788]
	ubfx	r0, r1, #0, #19
	ubfx	r1, ip, #0, #17
	add	r1, r0, r1
.L72:
	add	r0, r1, #3
	cmp	r1, #0
	movlt	r1, r0
	mov	r1, r1, asr #2
	str	r1, [r2, #28]
.L70:
	ldr	ip, [r3, #2116]
	mov	r0, #0
	ldr	r1, [r3, #2120]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #32]
	ldr	ip, [r3, #2124]
	ldr	r1, [r3, #2128]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #36]
	ldr	ip, [r3, #2132]
	ldr	r1, [r3, #2136]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #40]
	ldr	ip, [r3, #2140]
	ldr	r1, [r3, #2144]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #44]
	ldr	ip, [r3, #2148]
	ldr	r1, [r3, #2152]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #48]
	ldr	ip, [r3, #2156]
	ldr	r1, [r3, #2160]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #52]
	ldr	ip, [r3, #2164]
	ldr	r1, [r3, #2168]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #56]
	ldr	ip, [r3, #2172]
	ldr	r1, [r3, #2176]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #60]
	ldr	ip, [r3, #2180]
	ldr	r1, [r3, #2184]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #64]
	ldr	ip, [r3, #2188]
	ldr	r1, [r3, #2192]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #68]
	ldr	ip, [r3, #2196]
	ldr	r1, [r3, #2200]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #72]
	ldr	ip, [r3, #2204]
	ldr	r1, [r3, #2208]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #76]
	ldr	ip, [r3, #2212]
	ldr	r1, [r3, #2216]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #80]
	ldr	ip, [r3, #2220]
	ldr	r1, [r3, #2224]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #84]
	ldr	ip, [r3, #2228]
	ldr	r1, [r3, #2232]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #88]
	ldr	ip, [r3, #2236]
	ldr	r1, [r3, #2240]
	bic	ip, ip, #-536870912
	and	r1, r1, #127
	rsb	r1, r1, ip
	str	r1, [r2, #92]
	ldr	r1, [r3, #2120]
	mov	r1, r1, lsr #31
	str	r1, [r2, #96]
	ldr	r1, [r3, #2128]
	mov	r1, r1, lsr #31
	str	r1, [r2, #100]
	ldr	r1, [r3, #2136]
	mov	r1, r1, lsr #31
	str	r1, [r2, #104]
	ldr	r1, [r3, #2144]
	mov	r1, r1, lsr #31
	str	r1, [r2, #108]
	ldr	r1, [r3, #2152]
	mov	r1, r1, lsr #31
	str	r1, [r2, #112]
	ldr	r1, [r3, #2160]
	mov	r1, r1, lsr #31
	str	r1, [r2, #116]
	ldr	r1, [r3, #2168]
	mov	r1, r1, lsr #31
	str	r1, [r2, #120]
	ldr	r1, [r3, #2176]
	mov	r1, r1, lsr #31
	str	r1, [r2, #124]
	ldr	r1, [r3, #2184]
	mov	r1, r1, lsr #31
	str	r1, [r2, #128]
	ldr	r1, [r3, #2192]
	mov	r1, r1, lsr #31
	str	r1, [r2, #132]
	ldr	r1, [r3, #2200]
	mov	r1, r1, lsr #31
	str	r1, [r2, #136]
	ldr	r1, [r3, #2208]
	mov	r1, r1, lsr #31
	str	r1, [r2, #140]
	ldr	r1, [r3, #2216]
	mov	r1, r1, lsr #31
	str	r1, [r2, #144]
	ldr	r1, [r3, #2224]
	mov	r1, r1, lsr #31
	str	r1, [r2, #148]
	ldr	r1, [r3, #2232]
	mov	r1, r1, lsr #31
	str	r1, [r2, #152]
	ldr	r3, [r3, #2240]
	mov	r3, r3, lsr #31
	str	r3, [r2, #156]
	ldmfd	sp, {fp, sp, pc}
.L73:
	ldr	r1, [r3, #2112]
	mov	r1, r1, asl #3
	str	r1, [r2, #20]
	ldr	r0, [r3, #2760]
	ldr	lr, [r3, #2764]
	ldr	r1, [r3, #2792]
	ubfx	ip, r0, #0, #19
	ubfx	r0, lr, #0, #19
	add	r0, ip, r0
	ubfx	r1, r1, #0, #19
	add	r1, r0, r1
	b	.L72
.L75:
	.align	2
.L74:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_ReadReg, .-DRV_VENC_HAL_V500R001_ReadReg
	.global	__aeabi_uidiv
	.align	2
	.global	DRV_VENC_HAL_V500R001_CfgReg
	.type	DRV_VENC_HAL_V500R001_CfgReg, %function
DRV_VENC_HAL_V500R001_CfgReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	ldr	r3, [r0, #56]
	mov	r8, r0
	cmp	r3, #0
	ldr	r3, .L160
	bne	.L154
	ldr	r2, [r0, #536]
	ldr	r1, [r0, #544]
	ldr	r0, [r3, #4]
	str	r3, [fp, #-56]
	add	r4, r0, #692
	add	r5, r0, #6528
	str	r0, [fp, #-48]
	mov	r6, r0
	mov	r0, r4
	ldr	r9, [r3]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	mov	r0, r4
	ldr	r1, [r8, #4]
	add	r5, r5, #40
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	r3, [r8, #40]
	ldr	r2, [r8, #12]
	cmp	r3, #0
	bne	.L153
	add	r4, r6, #4096
.L110:
	ldmib	r8, {r2, r3}
	cmp	r2, #0
	beq	.L155
	b	.L161
.L162:
	.align	2
.L160:
	.word	.LANCHOR0
.L161:
.L113:
	mov	r3, #0
	mov	r2, #7
	str	r3, [r4, #2372]
	str	r3, [r4, #2368]
	str	r2, [r4, #2364]
.L115:
	ldr	r3, [r8, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	bhi	.L116
	ldr	r2, [r8, #4]
	cmp	r2, #0
	bne	.L116
	mov	r1, #28
	str	r1, [r8, #552]
	str	r1, [r8, #548]
	add	r3, r4, #4096
	str	r1, [r8, #544]
	ldr	r1, [fp, #-48]
	str	r2, [r1, #792]
	str	r2, [r8, #20]
	str	r2, [r3, #1612]
	str	r2, [r3, #1196]
	str	r2, [r3, #1192]
	str	r2, [r3, #940]
	str	r2, [r3, #432]
	str	r2, [r4, #3616]
	str	r2, [r3, #1584]
.L116:
	mov	r3, r5
	mov	r2, #207
	mov	r0, r8
	str	r2, [r9]
	ldr	r2, [r4, #2372]
	ldr	r1, [r4, #2368]
	bl	CfgVcpiMode.isra.7
	add	r3, r4, #4096
	mov	r1, #0
	ldr	r2, [r3, #1184]
	mov	ip, r1
	ldr	lr, [r3, #1188]
	mov	r5, r1
	mov	r0, r1
	bfi	r1, r2, #16, #9
	bfi	r1, lr, #0, #9
	str	r1, [r9, #32]
	ldr	lr, [r8, #20]
	mov	r2, r5
	ldr	r7, [r8, #28]
	mov	r1, r5
	bfi	r5, lr, #17, #1
	bfc	r1, #16, #1
	orr	r5, r5, #65536
	mov	lr, #4
	bfi	r5, r7, #0, #16
	str	r5, [r9, #40]
	ldr	r7, [r8, #544]
	bfi	r1, lr, #13, #3
	ldr	r10, [r3, #840]
	bfi	r1, lr, #10, #3
	bfi	r0, r7, #10, #6
	ldr	r7, [r3, #844]
	bfi	r0, r10, #5, #5
	ldr	r10, [r4, #3616]
	bfi	r0, r7, #0, #5
	ldr	r7, [r4, #3600]
	bfi	r0, r10, #18, #1
	mov	r5, #3
	bfi	r0, r7, #19, #1
	str	r0, [r9, #44]
	ldr	r7, [r3, #824]
	bfi	r1, r5, #7, #3
	mov	r5, #1
	bfi	r1, r5, #5, #2
	bfi	r1, lr, #2, #3
	mov	r0, ip
	str	r7, [r9, #16]
	bfi	r1, r5, #0, #2
	ldr	r7, [r3, #1000]
	mov	lr, ip
	ldr	r10, [r3, #1004]
	mov	r5, ip
	bfi	ip, r7, #8, #2
	ldr	r7, [r3, #1008]
	bfi	ip, r10, #4, #4
	bfi	ip, r7, #0, #4
	str	ip, [r9, #48]
	ldr	r7, [r3, #1764]
	ldr	ip, [r3, #1760]
	bfi	r2, r7, #21, #1
	ldr	r7, [r3, #1612]
	bfi	r2, ip, #19, #2
	ldr	ip, [r3, #1640]
	orr	r2, r2, #458752
	ldr	r10, [r3, #1616]
	bfi	r2, r7, #2, #1
	ldr	r7, [r3, #1620]
	bfi	r2, ip, #23, #1
	ldr	ip, [r3, #1624]
	bfi	r2, r10, #3, #1
	bfi	r2, r7, #1, #1
	bfi	r2, ip, #0, #1
	str	r2, [r9, #52]
	str	r1, [r9, #68]
	mov	ip, #0
	ldr	r1, [r8, #16]
	ldr	r2, [r8, #12]
	sub	r1, r1, #1
	bfi	r0, r1, #16, #13
	sub	r2, r2, #1
	bfi	r0, r2, #0, #13
	str	r0, [r9, #36]
	ldr	r2, [r3, #784]
	ldr	r0, [r3, #788]
	ldr	r1, [r3, #832]
	bfi	lr, r2, #31, #1
	ldr	r2, [r3, #836]
	bfi	lr, r0, #30, #1
	sub	r1, r1, #1
	mov	r0, ip
	bfi	lr, r1, #16, #9
	sub	r2, r2, #1
	bfi	lr, r2, #0, #9
	str	lr, [r9, #20]
	ldr	r2, [r3, #1768]
	str	r2, [r9, #24]
	ldr	r1, [r3, #1668]
	ldr	r2, [r3, #1672]
	bfi	r5, r1, #4, #4
	mov	r1, ip
	bfi	r5, r2, #0, #4
	str	r5, [r9, #56]
	ldr	r2, [r3, #1396]
	add	r5, r4, #4096
	cmp	r2, #1
	ldrne	r2, [r3, #1020]
	moveq	r3, #3
	movne	r3, #0
	bfine	r3, r2, #0, #2
	str	r3, [r9, #60]
	ldr	lr, [r5, #1028]
	mov	r2, ip
	mov	r3, ip
	str	r3, [fp, #-52]
	bfi	ip, lr, #0, #1
	mov	lr, r3
	bfc	ip, #1, #1
	str	ip, [r9, #64]
	ldr	r6, [r5, #932]
	mov	ip, r3
	ldr	r10, [r5, #936]
	bfi	r3, r6, #12, #4
	ldr	r6, [r5, #948]
	bfi	r3, r10, #8, #4
	ldr	r10, [r4, #2364]
	bfi	r3, r6, #4, #1
	ldr	r6, [r5, #952]
	bfi	r3, r10, #0, #3
	mov	r10, r1
	bfi	r3, r6, #5, #1
	str	r3, [r9, #72]
	ldr	r6, [r5, #900]
	bfc	r10, #4, #2
	ldr	r3, [r5, #908]
	bfc	r10, #2, #2
	bfi	r1, r6, #12, #1
	str	r2, [fp, #-64]
	bfi	r1, r3, #4, #2
	mov	r6, r2
	orr	r1, r1, #3
	str	r1, [r9, #76]
	ldr	r1, [r5, #1224]
	mov	r3, r2
	ldr	r7, [r5, #940]
	orr	r10, r10, #2
	str	r2, [fp, #-60]
	bfi	r2, r1, #4, #1
	ldr	r1, [r5, #944]
	bfi	r2, r7, #2, #1
	ldr	r7, [r5, #1196]
	bfi	r2, r1, #3, #1
	ldr	r1, [r5, #1192]
	bfi	r2, r1, #1, #1
	mov	r1, r0
	bfi	r2, r7, #0, #1
	str	r2, [r9, #80]
	ldr	r7, [r5, #1200]
	mov	r2, r0
	bfi	r0, r7, #16, #16
	ldr	r7, [r5, #1204]
	bfi	r0, r7, #0, #16
	str	r0, [r9, #84]
	ldr	r7, [r5, #1208]
	mov	r0, r8
	bfi	lr, r7, #24, #8
	ldr	r7, [r5, #1212]
	bfi	lr, r7, #16, #8
	ldr	r7, [r5, #1216]
	bfi	lr, r7, #8, #8
	ldr	r7, [r5, #1220]
	bfi	lr, r7, #0, #8
	ldr	r7, [fp, #-48]
	str	lr, [r9, #88]
	ldr	lr, [r7, #788]
	ldr	r7, [r5, #1600]
	bfi	r6, lr, #1, #1
	ldr	lr, [r5, #1596]
	bfi	r6, r7, #16, #8
	mov	r7, r6
	bfi	r7, lr, #24, #8
	str	r7, [r9, #92]
	ldr	r7, [fp, #-48]
	ldr	lr, [r7, #692]
	mov	r6, r7
	ldr	r7, [r7, #696]
	bfi	ip, lr, #2, #1
	ldr	lr, [r4, #2476]
	bfi	ip, r7, #1, #1
	ldr	r7, [r5, #1228]
	bfi	ip, lr, #0, #1
	ldr	lr, [r5, #1232]
	bfi	ip, r7, #3, #1
	bfi	ip, lr, #4, #1
	str	ip, [r9, #96]
	str	r10, [r9, #100]
	ldr	ip, [r4, #3584]
	ldr	lr, [r4, #3588]
	bfi	r3, ip, #0, #1
	ldr	ip, [r6, #784]
	bfi	r3, lr, #1, #1
	ldr	lr, [r4, #3612]
	bfi	r3, ip, #2, #1
	ldr	ip, [r4, #3580]
	bfi	r3, lr, #4, #1
	ldr	lr, [r6, #780]
	bfi	r3, ip, #9, #1
	ldr	ip, [r4, #3632]
	bfi	r3, lr, #8, #1
	ldr	lr, [r4, #3688]
	bfi	r3, ip, #3, #1
	ldr	ip, [r4, #3572]
	bfi	r3, lr, #15, #1
	ldr	lr, [r4, #3576]
	bfi	r3, ip, #14, #1
	ldr	ip, [r4, #3684]
	bfi	r3, lr, #13, #1
	ldr	lr, [r4, #3680]
	ldr	r7, [r4, #3676]
	bfi	r3, ip, #12, #1
	bfi	r3, lr, #11, #1
	ldr	ip, [r4, #3620]
	bfi	r3, r7, #10, #1
	mov	r6, r1
	bfi	r3, ip, #18, #1
	str	r3, [r9, #104]
	ldr	ip, [r5, #1584]
	mov	r7, r1
	ldr	r3, [r5, #1588]
	bfi	r6, ip, #8, #1
	bfi	r6, r3, #0, #8
	str	r6, [r9, #108]
	ldr	r3, [r5, #1592]
	bfi	r7, r3, #0, #1
	str	r7, [r9, #112]
	ldr	ip, [r5, #1756]
	ldr	r3, [r5, #1752]
	bfi	r1, ip, #0, #1
	ldr	ip, [r5, #1748]
	bfi	r1, r3, #1, #1
	ldr	r3, [r5, #1744]
	bfi	r1, ip, #2, #1
	ldr	ip, [r5, #1740]
	bfi	r1, r3, #3, #1
	ldr	r3, [r5, #1736]
	bfi	r1, ip, #4, #1
	ldr	ip, [r5, #1732]
	bfi	r1, r3, #5, #1
	ldr	r3, [r5, #1692]
	bfi	r1, ip, #6, #1
	bfi	r1, r3, #7, #1
	str	r1, [r9, #116]
	ldr	r3, [r5, #1728]
	ldr	r1, [r5, #1724]
	bfi	r2, r3, #0, #1
	ldr	r3, [r5, #1720]
	bfi	r2, r1, #1, #1
	ldr	r1, [r5, #1716]
	bfi	r2, r3, #2, #1
	ldr	r3, [r5, #1684]
	bfi	r2, r1, #3, #1
	ldr	r1, [r5, #1688]
	bfi	r2, r3, #4, #1
	ldr	r3, [r5, #1712]
	bfi	r2, r1, #5, #1
	ldr	r1, [r5, #1708]
	bfi	r2, r3, #6, #1
	ldr	r3, [r5, #1696]
	bfi	r2, r1, #7, #1
	ldr	r1, [r5, #1704]
	bfi	r2, r3, #8, #1
	ldr	r3, [r5, #1700]
	bfi	r2, r1, #9, #1
	bfi	r2, r3, #10, #1
	str	r2, [r9, #120]
	bl	CfgSwL0Size
	mov	r2, #1
	mov	r3, #0
	bfi	r3, r2, #16, #6
	bfi	r3, r2, #0, #7
	str	r3, [r9, #128]
	ldr	r3, [r8, #168]
	movw	r2, #43691
	movt	r2, 43690
	mov	r1, #0
	mov	lr, r1
	str	r1, [fp, #-52]
	add	r3, r8, r3, lsl #2
	mov	r10, r1
	mov	ip, r1
	mov	r0, r8
	ldr	r3, [r3, #156]
	str	r3, [r9, #132]
	ldr	r3, [r8, #168]
	add	r3, r3, #2
	umull	r6, r7, r3, r2
	mov	r6, r7, lsr #1
	add	r6, r6, r6, lsl #1
	rsb	r3, r6, r3
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #156]
	str	r3, [r9, #136]
	ldr	r3, [r8, #168]
	add	r3, r3, #1
	mov	r6, r3
	umull	r2, r3, r3, r2
	mov	r3, r3, lsr #1
	add	r3, r3, r3, lsl #1
	rsb	r3, r3, r6
	mov	r6, r1
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #156]
	str	r3, [r9, #140]
	ldr	r3, [r8, #196]
	str	r3, [r9, #144]
	ldr	r3, [r8, #68]
	str	r3, [r9, #148]
	ldr	r3, [r8, #72]
	str	r3, [r9, #152]
	ldr	r3, [r8, #76]
	str	r3, [r9, #156]
	ldr	r2, [r8, #80]
	ldr	r3, [r8, #84]
	bfi	r6, r2, #16, #16
	mov	r2, r6
	bfi	r2, r3, #0, #16
	str	r2, [r9, #168]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #88]
	str	r3, [r9, #172]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #96]
	str	r3, [r9, #176]
	ldr	r2, [r8, #104]
	ldr	r3, [r8, #108]
	bfi	lr, r2, #0, #16
	bfi	lr, r3, #16, #16
	str	lr, [r9, #180]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #112]
	str	r3, [r9, #184]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #120]
	str	r3, [r9, #188]
	ldr	r3, [r8, #128]
	bfi	r10, r3, #0, #16
	str	r10, [r9, #192]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #84
	movne	r3, #80
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r9, #196]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #92
	movne	r3, #88
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r9, #200]
	ldr	r2, [r8, #104]
	ldr	r3, [r8, #108]
	bfi	ip, r2, #16, #16
	bfi	ip, r3, #0, #16
	str	ip, [r9, #204]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #108
	movne	r3, #104
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r9, #208]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #116
	movne	r3, #112
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r9, #212]
	ldr	r2, [r8, #128]
	ldr	r3, [r8, #132]
	bfi	r1, r2, #16, #16
	bfi	r1, r3, #0, #16
	str	r1, [r9, #216]
	ldr	r3, [r8, #136]
	cmp	r3, #0
	moveq	r3, #148
	movne	r3, #144
	add	r3, r8, r3
	ldr	r3, [r3, #4]
	str	r3, [r9, #220]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #148]
	str	r3, [r9, #252]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #140]
	str	r3, [r9, #260]
	ldr	r3, [r8, #136]
	cmp	r3, #0
	moveq	r3, #140
	movne	r3, #136
	add	r3, r8, r3
	ldr	r3, [r3, #4]
	str	r3, [r9, #264]
	ldr	r3, [r8, #200]
	str	r3, [r9, #268]
	ldr	r3, [r8, #332]
	str	r3, [r9, #272]
	ldr	r3, [r8, #328]
	str	r3, [r9, #276]
	ldr	r3, [fp, #-48]
	add	r3, r3, #8192
	ldr	r1, [r3, #1420]
	bl	CfgStrFmt.isra.6
	mov	r3, #168
	mov	r2, #0
	bfi	r2, r3, #0, #16
	mov	r3, #0
	movt	r2, 424
	str	r2, [r9, #296]
	ldrb	r2, [r5, #512]
	mov	r7, r3
	ldrb	lr, [r5, #520]
	ldrb	ip, [r5, #516]
	str	r2, [fp, #-52]
	ldr	r0, [fp, #-52]
	orr	r2, ip, lr
	ldrb	r1, [r5, #508]
	ldrb	r6, [r5, #504]
	orr	r2, r0, r2
	ldrb	r10, [r5, #500]
	orr	r2, r1, r2
	ldrb	r0, [r5, #496]
	orr	r2, r6, r2
	str	r1, [fp, #-60]
	orr	r2, r10, r2
	ldrb	r1, [r5, #492]
	orr	r2, r0, r2
	str	r0, [fp, #-64]
	mov	r0, r7
	orr	r2, r1, r2
	str	r1, [fp, #-68]
	bfi	r3, r2, #24, #1
	ldr	r1, [r5, #744]
	ldr	r2, [r5, #740]
	bfi	r3, r1, #23, #1
	ldr	r1, [r5, #736]
	bfi	r3, r2, #22, #1
	ldr	r2, [r5, #732]
	bfi	r3, r1, #21, #1
	ldr	r1, [r5, #728]
	bfi	r3, r2, #20, #1
	ldr	r2, [r5, #724]
	bfi	r3, r1, #19, #1
	ldr	r1, [r5, #720]
	bfi	r3, r2, #18, #1
	ldr	r2, [r5, #716]
	bfi	r3, r1, #17, #1
	ldr	r1, [r5, #552]
	bfi	r3, r2, #16, #1
	ldr	r2, [r5, #548]
	bfi	r3, r1, #15, #1
	ldr	r1, [r5, #544]
	bfi	r3, r2, #14, #1
	ldr	r2, [r5, #540]
	bfi	r3, r1, #13, #1
	ldr	r1, [r5, #536]
	bfi	r3, r2, #12, #1
	ldr	r2, [r5, #532]
	bfi	r3, r1, #11, #1
	ldr	r1, [r5, #528]
	bfi	r3, r2, #10, #1
	ldr	r2, [r5, #524]
	bfi	r3, r1, #9, #1
	ldr	r1, [fp, #-52]
	bfi	r3, r2, #8, #1
	str	r7, [fp, #-52]
	bfi	r3, lr, #7, #1
	mov	r2, r7
	bfi	r3, ip, #6, #1
	mov	lr, r7
	bfi	r3, r1, #5, #1
	ldr	r1, [fp, #-60]
	mov	ip, r7
	bfi	r3, r1, #4, #1
	mov	r1, r7
	bfi	r3, r6, #3, #1
	mov	r6, r7
	bfi	r3, r10, #2, #1
	ldr	r10, [fp, #-64]
	str	r7, [fp, #-60]
	bfi	r3, r10, #1, #1
	ldr	r10, [fp, #-68]
	str	r7, [fp, #-64]
	bfi	r3, r10, #0, #1
	str	r3, [r9, #512]
	ldr	r3, [r5, #568]
	ldr	r10, [r5, #564]
	bfi	r7, r3, #24, #7
	ldr	r3, [r5, #556]
	bfi	r7, r10, #16, #7
	ldr	r10, [r5, #560]
	bfi	r7, r10, #8, #7
	mov	r10, r2
	bfi	r7, r3, #0, #7
	str	r7, [r9, #516]
	ldr	r3, [r5, #584]
	ldr	r7, [r5, #580]
	bfi	r2, r3, #24, #7
	ldr	r3, [r5, #572]
	bfi	r2, r7, #16, #7
	ldr	r7, [r5, #576]
	str	r10, [fp, #-68]
	bfi	r2, r7, #8, #7
	mov	r7, lr
	bfi	r2, r3, #0, #7
	str	r2, [r9, #520]
	ldr	r2, [r5, #620]
	ldr	r3, [r5, #588]
	bfi	lr, r2, #16, #10
	bfi	lr, r3, #0, #10
	str	lr, [r9, #524]
	ldr	r2, [r5, #624]
	mov	lr, ip
	ldr	r3, [r5, #592]
	bfi	ip, r2, #16, #10
	bfi	ip, r3, #0, #10
	str	ip, [r9, #528]
	ldr	r2, [r5, #628]
	mov	ip, r0
	ldr	r3, [r5, #596]
	bfi	r0, r2, #16, #10
	bfi	r0, r3, #0, #10
	str	r0, [r9, #532]
	ldr	r2, [r5, #632]
	mov	r0, r1
	ldr	r3, [r5, #600]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #536]
	ldr	r2, [r5, #636]
	mov	r1, r6
	ldr	r3, [r5, #604]
	bfi	r6, r2, #16, #10
	bfi	r6, r3, #0, #10
	str	r6, [r9, #540]
	ldr	r2, [r5, #640]
	mov	r6, r10
	ldr	r3, [r5, #608]
	bfi	r6, r2, #16, #10
	bfi	r6, r3, #0, #10
	str	r6, [r9, #544]
	ldr	r2, [r5, #644]
	mov	r6, r10
	mov	r3, r10
	bfi	r6, r2, #16, #10
	ldr	r2, [r5, #612]
	bfi	r6, r2, #0, #10
	str	r6, [r9, #548]
	ldr	r2, [r5, #648]
	mov	r6, r10
	bfi	r6, r2, #16, #10
	ldr	r2, [r5, #616]
	bfi	r6, r2, #0, #10
	str	r6, [r9, #552]
	ldr	r2, [r5, #684]
	bfi	r10, r2, #16, #9
	ldr	r2, [r5, #652]
	bfi	r10, r2, #0, #9
	str	r10, [r9, #556]
	ldr	r2, [r5, #688]
	ldr	r10, [r5, #656]
	bfi	r7, r2, #16, #9
	mov	r2, r3
	bfi	r7, r10, #0, #9
	str	r7, [r9, #560]
	ldr	r10, [r5, #692]
	ldr	r7, [r5, #660]
	bfi	lr, r10, #16, #9
	bfi	lr, r7, #0, #9
	str	lr, [r9, #564]
	ldr	r7, [r5, #696]
	ldr	lr, [r5, #664]
	bfi	ip, r7, #16, #9
	bfi	ip, lr, #0, #9
	str	ip, [r9, #568]
	ldr	lr, [r5, #700]
	ldr	ip, [r5, #668]
	bfi	r0, lr, #16, #9
	bfi	r0, ip, #0, #9
	str	r0, [r9, #572]
	ldr	ip, [r5, #704]
	ldr	r0, [r5, #672]
	bfi	r1, ip, #16, #9
	bfi	r1, r0, #0, #9
	str	r1, [r9, #576]
	ldr	r0, [r5, #708]
	ldr	r1, [r5, #676]
	bfi	r2, r0, #16, #9
	bfi	r2, r1, #0, #9
	str	r2, [r9, #580]
	ldr	r1, [r5, #712]
	ldr	r2, [r5, #680]
	bfi	r3, r1, #16, #9
	bfi	r3, r2, #0, #9
	str	r3, [r9, #584]
	ldr	r3, [r8, #4]
	ldr	r0, [r8, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r7, #16
	movne	r7, #32
	mov	r1, r7
	add	r0, r0, r7
	bl	__aeabi_uidiv
	ldr	r3, [r8, #16]
	mov	r1, r7
	mov	r10, r0
	sub	r0, r3, #1
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r1, r10, r0
	ldr	r0, [r8, #540]
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r1, r3
	mov	r2, r3
	str	r3, [fp, #-52]
	mov	r7, r3
	str	r3, [fp, #-60]
	mov	r10, r3
	str	r3, [fp, #-64]
	mov	ip, r3
	str	r3, [fp, #-68]
	mov	lr, r3
	str	r3, [fp, #-72]
	mov	r6, r3
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	str	r3, [fp, #-84]
	str	r3, [fp, #-88]
	str	r3, [fp, #-92]
	str	r3, [fp, #-96]
	str	r3, [fp, #-100]
	str	r3, [fp, #-104]
	str	r3, [fp, #-108]
	str	r3, [fp, #-112]
	str	r3, [fp, #-116]
	str	r3, [fp, #-120]
	str	r3, [fp, #-124]
	str	r3, [fp, #-128]
	str	r3, [fp, #-132]
	bfi	r3, r0, #0, #20
	str	r3, [r9, #588]
	ldr	r0, [r5, #1244]
	mov	r3, r2
	bfi	r3, r0, #0, #4
	str	r3, [r9, #592]
	ldr	r3, [fp, #-48]
	ldr	r0, [r3, #700]
	bfi	r7, r0, #16, #5
	ldr	r0, [r4, #2488]
	bfi	r7, r0, #0, #8
	ldr	r0, [r4, #2864]
	bfi	r7, r0, #24, #4
	str	r7, [r9, #604]
	ldr	r0, [r4, #3128]
	mov	r7, r2
	bfi	r10, r0, #0, #3
	ldr	r0, [r4, #3132]
	bfi	r10, r0, #3, #7
	ldr	r0, [r4, #3136]
	bfi	r10, r0, #10, #3
	ldr	r0, [r4, #3144]
	bfi	r10, r0, #18, #4
	ldr	r0, [r4, #3152]
	bfi	r10, r0, #26, #4
	str	r10, [r9, #608]
	ldr	r0, [r4, #2960]
	mov	r10, r2
	bfi	r10, r0, #0, #1
	ldr	r0, [r4, #2964]
	bfi	r10, r0, #1, #3
	ldr	r0, [r4, #2976]
	bfi	r10, r0, #15, #6
	ldr	r0, [r4, #2980]
	bfi	r10, r0, #21, #5
	str	r10, [r9, #612]
	ldr	r0, [r4, #2500]
	mov	r10, r3
	bfi	r7, r0, #16, #5
	ldr	r0, [r3, #704]
	bfi	r7, r0, #0, #8
	ldr	r0, [r4, #2872]
	bfi	r7, r0, #24, #4
	str	r7, [r9, #620]
	ldr	r0, [r4, #3156]
	mov	r7, r1
	bfi	r2, r0, #0, #3
	ldr	r0, [r4, #3160]
	bfi	r2, r0, #3, #7
	ldr	r0, [r4, #3164]
	bfi	r2, r0, #10, #3
	ldr	r0, [r4, #3172]
	bfi	r2, r0, #18, #4
	ldr	r0, [r4, #3180]
	bfi	r2, r0, #26, #4
	str	r2, [r9, #624]
	ldr	r2, [r4, #2984]
	mov	r0, r1
	bfi	r0, r2, #0, #1
	ldr	r2, [r4, #2988]
	bfi	r0, r2, #1, #3
	ldr	r2, [r4, #3000]
	bfi	r0, r2, #15, #6
	ldr	r2, [r4, #3004]
	bfi	r0, r2, #21, #5
	str	r0, [r9, #628]
	ldr	r2, [r3, #716]
	mov	r0, r1
	bfi	r7, r2, #16, #5
	ldr	r2, [r3, #720]
	bfi	r7, r2, #0, #8
	ldr	r2, [r4, #2888]
	bfi	r7, r2, #24, #4
	str	r7, [r9, #636]
	ldr	r2, [r4, #3208]
	mov	r7, r1
	bfi	r0, r2, #0, #3
	ldr	r2, [r4, #3212]
	bfi	r0, r2, #3, #7
	ldr	r2, [r4, #3216]
	bfi	r0, r2, #10, #3
	ldr	r2, [r4, #3224]
	bfi	r0, r2, #18, #4
	ldr	r2, [r4, #3232]
	bfi	r0, r2, #26, #4
	str	r0, [r9, #640]
	ldr	r3, [r4, #3032]
	mov	r2, r1
	mov	r0, r1
	bfi	r2, r3, #0, #1
	ldr	r3, [r4, #3036]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #3048]
	bfi	r2, r3, #15, #6
	ldr	r3, [r4, #3052]
	bfi	r2, r3, #21, #5
	str	r2, [r9, #644]
	ldr	r3, [r10, #752]
	mov	r2, r1
	bfi	r7, r3, #0, #8
	ldr	r3, [r10, #756]
	bfi	r7, r3, #16, #5
	ldr	r3, [r4, #2896]
	bfi	r7, r3, #24, #4
	str	r7, [r9, #652]
	ldr	r3, [r4, #2780]
	mov	r7, r1
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2784]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2788]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2796]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2804]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #656]
	ldr	r3, [r4, #3056]
	mov	r2, r1
	bfi	r2, r3, #0, #1
	ldr	r3, [r4, #3060]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #3072]
	bfi	r2, r3, #15, #6
	ldr	r3, [r4, #3076]
	bfi	r2, r3, #21, #5
	str	r2, [r9, #660]
	ldr	r3, [r10, #708]
	mov	r2, r1
	bfi	r7, r3, #16, #5
	ldr	r3, [r10, #712]
	bfi	r7, r3, #0, #8
	ldr	r3, [r4, #2880]
	bfi	r7, r3, #24, #4
	str	r7, [r9, #668]
	ldr	r3, [r10, #760]
	mov	r10, r1
	mov	r7, r1
	bfi	lr, r3, #0, #3
	ldr	r3, [r4, #3184]
	bfi	lr, r3, #3, #7
	ldr	r3, [r4, #3188]
	bfi	lr, r3, #10, #3
	ldr	r3, [r4, #3196]
	bfi	lr, r3, #18, #4
	ldr	r3, [r4, #3204]
	bfi	lr, r3, #26, #4
	str	lr, [r9, #672]
	ldr	r3, [r4, #3008]
	mov	lr, r1
	bfi	r2, r3, #0, #1
	ldr	r3, [r4, #3012]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #3024]
	bfi	r2, r3, #15, #6
	ldr	r3, [r4, #3028]
	bfi	r2, r3, #21, #5
	str	r2, [r9, #676]
	ldr	r3, [r4, #2936]
	mov	r2, r1
	bfi	lr, r3, #0, #8
	ldr	r3, [r4, #2940]
	bfi	lr, r3, #16, #5
	ldr	r3, [r4, #2904]
	bfi	lr, r3, #24, #4
	str	lr, [r9, #684]
	ldr	r3, [r4, #2808]
	mov	lr, r1
	bfi	ip, r3, #0, #3
	ldr	r3, [r4, #2812]
	bfi	ip, r3, #3, #7
	ldr	r3, [r4, #2816]
	bfi	ip, r3, #10, #3
	ldr	r3, [r4, #2824]
	bfi	ip, r3, #18, #4
	ldr	r3, [r4, #2832]
	bfi	ip, r3, #26, #4
	str	ip, [r9, #688]
	ldr	r3, [r4, #3080]
	mov	ip, r1
	bfi	r0, r3, #0, #1
	ldr	r3, [r4, #3084]
	bfi	r0, r3, #1, #3
	ldr	r3, [r4, #3096]
	bfi	r0, r3, #15, #6
	ldr	r3, [r4, #3100]
	bfi	r0, r3, #21, #5
	str	r0, [r9, #692]
	ldr	r3, [r4, #2952]
	mov	r0, r1
	bfi	r0, r3, #0, #8
	ldr	r3, [r4, #2956]
	bfi	r0, r3, #16, #5
	ldr	r3, [r4, #2912]
	bfi	r0, r3, #24, #4
	str	r0, [r9, #700]
	ldr	r3, [r4, #2836]
	mov	r0, r1
	bfi	r10, r3, #0, #3
	ldr	r3, [r4, #2840]
	bfi	r10, r3, #3, #7
	ldr	r3, [r4, #2844]
	bfi	r10, r3, #10, #3
	ldr	r3, [r4, #2852]
	bfi	r10, r3, #18, #4
	ldr	r3, [r4, #2860]
	bfi	r10, r3, #26, #4
	str	r10, [r9, #704]
	ldr	r3, [r4, #3104]
	mov	r10, r1
	bfi	r10, r3, #0, #1
	ldr	r3, [r4, #3108]
	bfi	r10, r3, #1, #3
	ldr	r3, [r4, #3120]
	bfi	r10, r3, #15, #6
	ldr	r3, [r4, #3124]
	bfi	r10, r3, #21, #5
	str	r10, [r9, #708]
	ldr	r3, [r4, #2532]
	ldr	r10, [fp, #-48]
	bfi	r6, r3, #0, #4
	ldr	r3, [r4, #2528]
	bfi	r6, r3, #4, #4
	ldr	r3, [r4, #2524]
	bfi	r6, r3, #8, #4
	ldr	r3, [r4, #2544]
	bfi	r6, r3, #16, #4
	ldr	r3, [r4, #2540]
	bfi	r6, r3, #20, #4
	ldr	r3, [r10, #724]
	bfi	r6, r3, #24, #4
	str	r6, [r9, #712]
	ldr	r3, [r4, #2612]
	mov	r6, r1
	bfi	r6, r3, #0, #4
	ldr	r3, [r4, #2608]
	bfi	r6, r3, #4, #4
	ldr	r3, [r10, #736]
	bfi	r6, r3, #8, #4
	ldr	r3, [r4, #2628]
	bfi	r6, r3, #16, #4
	ldr	r3, [r4, #2624]
	bfi	r6, r3, #20, #4
	ldr	r3, [r4, #2620]
	bfi	r6, r3, #24, #4
	str	r6, [r9, #716]
	ldr	r3, [r4, #2696]
	mov	r6, r10
	bfi	r1, r3, #0, #4
	ldr	r3, [r4, #2692]
	bfi	r1, r3, #4, #4
	ldr	r3, [r10, #748]
	bfi	r1, r3, #8, #4
	ldr	r3, [r4, #2712]
	bfi	r1, r3, #16, #4
	ldr	r3, [r4, #2708]
	bfi	r1, r3, #20, #4
	ldr	r3, [r4, #2704]
	bfi	r1, r3, #24, #4
	str	r1, [r9, #720]
	ldr	r1, [r4, #2552]
	mov	r3, r2
	bfi	r3, r1, #8, #4
	ldr	r1, [r4, #2556]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #2560]
	bfi	r3, r1, #0, #4
	ldr	r1, [r4, #2568]
	bfi	r3, r1, #24, #4
	ldr	r1, [r6, #728]
	mov	r10, r3
	mov	r3, r6
	mov	r6, r10
	bfi	r6, r1, #20, #4
	ldr	r1, [r4, #2572]
	bfi	r6, r1, #16, #4
	str	r6, [r9, #724]
	ldr	r10, [r4, #2636]
	mov	r1, r2
	mov	r6, lr
	bfi	r2, r10, #8, #4
	ldr	r10, [r3, #740]
	bfi	r2, r10, #4, #4
	ldr	r10, [r4, #2640]
	bfi	r2, r10, #0, #4
	ldr	r10, [r4, #2648]
	bfi	r2, r10, #24, #4
	ldr	r10, [r4, #2652]
	bfi	r2, r10, #20, #4
	ldr	r10, [r4, #2656]
	bfi	r2, r10, #16, #4
	str	r2, [r9, #728]
	ldr	r10, [r4, #2720]
	mov	r2, r7
	bfi	r7, r10, #8, #4
	ldr	r10, [r4, #2724]
	bfi	r7, r10, #4, #4
	ldr	r10, [r4, #2728]
	bfi	r7, r10, #0, #4
	ldr	r10, [r4, #2736]
	bfi	r7, r10, #24, #4
	ldr	r10, [r4, #2740]
	bfi	r7, r10, #20, #4
	ldr	r10, [r4, #2744]
	bfi	r7, r10, #16, #4
	str	r7, [r9, #732]
	ldr	r7, [r4, #2580]
	mov	r10, r1
	bfi	lr, r7, #8, #4
	ldr	r7, [r4, #2584]
	bfi	lr, r7, #4, #4
	ldr	r7, [r4, #2588]
	bfi	lr, r7, #0, #4
	ldr	r7, [r4, #2596]
	bfi	lr, r7, #24, #4
	ldr	r7, [r3, #732]
	bfi	lr, r7, #20, #4
	ldr	r7, [r4, #2600]
	bfi	lr, r7, #16, #4
	str	lr, [r9, #736]
	ldr	lr, [r4, #2664]
	mov	r7, ip
	bfi	ip, lr, #8, #4
	ldr	lr, [r3, #744]
	bfi	ip, lr, #4, #4
	ldr	lr, [r4, #2668]
	bfi	ip, lr, #0, #4
	ldr	lr, [r4, #2676]
	bfi	ip, lr, #24, #4
	ldr	lr, [r4, #2680]
	bfi	ip, lr, #20, #4
	ldr	lr, [r4, #2684]
	bfi	ip, lr, #16, #4
	str	ip, [r9, #740]
	ldr	ip, [r4, #2752]
	mov	lr, r0
	bfi	r0, ip, #8, #4
	ldr	ip, [r4, #2756]
	bfi	r0, ip, #4, #4
	ldr	ip, [r4, #2760]
	bfi	r0, ip, #0, #4
	ldr	ip, [r4, #2768]
	bfi	r0, ip, #24, #4
	ldr	ip, [r4, #2772]
	bfi	r0, ip, #20, #4
	ldr	ip, [r4, #2776]
	bfi	r0, ip, #16, #4
	str	r0, [r9, #744]
	ldr	r0, [r4, #3236]
	mov	ip, r1
	bfi	ip, r0, #0, #4
	ldr	r0, [r4, #3240]
	bfi	ip, r0, #4, #4
	ldr	r0, [r4, #3244]
	bfi	ip, r0, #8, #4
	ldr	r0, [r4, #3248]
	bfi	ip, r0, #12, #4
	ldr	r0, [r4, #3252]
	bfi	ip, r0, #16, #4
	ldr	r0, [r4, #3256]
	bfi	ip, r0, #20, #4
	str	ip, [r9, #748]
	mov	ip, r3
	ldr	r3, [r3, #764]
	bfi	r10, r3, #0, #12
	ldr	r3, [ip, #768]
	bfi	r10, r3, #12, #12
	ldr	r3, [r4, #3260]
	bfi	r10, r3, #24, #8
	str	r10, [r9, #752]
	ldr	r3, [r4, #3264]
	mov	r10, r1
	bfi	r6, r3, #0, #12
	ldr	r3, [r4, #3268]
	str	ip, [fp, #-48]
	bfi	r6, r3, #12, #12
	ldr	r3, [r4, #3272]
	bfi	r6, r3, #24, #8
	str	r6, [r9, #756]
	ldr	r3, [ip, #772]
	mov	r6, r1
	mov	ip, r1
	bfi	r6, r3, #0, #12
	ldr	r3, [r4, #3276]
	bfi	r6, r3, #12, #12
	ldr	r3, [r4, #3280]
	bfi	r6, r3, #24, #8
	str	r6, [r9, #760]
	ldr	r0, [r4, #3284]
	mov	r3, r1
	mov	r6, r7
	bfi	r10, r0, #0, #8
	ldr	r0, [r4, #3288]
	bfi	r10, r0, #8, #8
	ldr	r0, [r4, #3292]
	bfi	r10, r0, #16, #8
	str	r10, [r9, #764]
	ldr	r0, [r5, #1464]
	mov	r10, r7
	bfi	r1, r0, #14, #1
	ldr	r0, [r5, #1468]
	bfi	r1, r0, #15, #1
	ldr	r0, [r8, #40]
	bfi	r1, r0, #28, #1
	ldr	r0, [r4, #2360]
	bfi	r1, r0, #20, #8
	str	r1, [r9, #1024]
	ldr	r1, [r5, #1484]
	mov	r0, r2
	bfi	r2, r1, #0, #8
	ldr	r1, [r5, #1480]
	bfi	r2, r1, #8, #8
	ldr	r1, [r5, #1476]
	bfi	r2, r1, #16, #8
	ldr	r1, [r5, #1472]
	bfi	r2, r1, #24, #8
	str	r2, [r9, #1028]
	ldr	r2, [r4, #3752]
	mov	r1, r7
	bfi	r6, r2, #0, #1
	str	r6, [r9, #1536]
	ldr	r2, [r4, #3756]
	mov	r6, r7
	bfi	r6, r2, #0, #16
	str	r6, [r9, #1540]
	ldr	r2, [r4, #3760]
	mov	r6, r7
	bfi	r6, r2, #0, #16
	str	r6, [r9, #1544]
	ldr	r2, [r4, #3764]
	mov	r6, r7
	bfi	r6, r2, #0, #16
	str	r6, [r9, #1548]
	ldr	r2, [r4, #3812]
	mov	r6, r7
	bfi	lr, r2, #16, #1
	ldr	r2, [r4, #3816]
	bfi	lr, r2, #0, #16
	str	lr, [r9, #1552]
	ldr	lr, [r4, #3768]
	mov	r2, r7
	bfi	r7, lr, #18, #9
	ldr	lr, [r4, #3772]
	bfi	r7, lr, #9, #9
	ldr	lr, [r4, #3776]
	bfi	r7, lr, #0, #9
	str	r7, [r9, #1556]
	ldr	r7, [r4, #3780]
	mov	lr, r3
	bfi	lr, r7, #16, #8
	ldr	r7, [r4, #3784]
	bfi	lr, r7, #8, #8
	ldr	r7, [r4, #3788]
	bfi	lr, r7, #0, #8
	str	lr, [r9, #1560]
	ldr	lr, [r4, #3792]
	mov	r7, r3
	bfi	r3, lr, #8, #4
	ldr	lr, [r4, #3796]
	bfi	r3, lr, #4, #4
	ldr	lr, [r4, #3800]
	bfi	r3, lr, #0, #4
	ldr	lr, [r4, #3808]
	bfi	r3, lr, #12, #8
	ldr	lr, [r4, #3804]
	bfi	r3, lr, #20, #8
	str	r3, [r9, #1564]
	ldr	r3, [r5, #416]
	ldr	lr, [fp, #-48]
	bfi	ip, r3, #0, #8
	ldr	r3, [r5, #412]
	bfi	ip, r3, #8, #8
	ldr	r3, [r5, #408]
	bfi	ip, r3, #16, #8
	ldr	r3, [r5, #404]
	bfi	ip, r3, #24, #8
	str	ip, [r9, #1572]
	ldr	r3, [r4, #3820]
	mov	ip, r0
	bfi	r0, r3, #24, #8
	ldr	r3, [r4, #3824]
	bfi	r0, r3, #16, #8
	ldr	r3, [r4, #3828]
	bfi	r0, r3, #8, #8
	ldr	r3, [r4, #3832]
	bfi	r0, r3, #0, #8
	str	r0, [r9, #1576]
	ldr	r3, [r4, #3884]
	mov	r0, r10
	bfi	r10, r3, #0, #8
	ldr	r3, [r5, #444]
	bfi	r10, r3, #17, #1
	str	r10, [r9, #1580]
	ldr	r3, [r4, #3896]
	mov	r10, r1
	bfi	r0, r3, #0, #16
	ldr	r3, [r4, #3900]
	bfi	r0, r3, #16, #16
	str	r0, [r9, #1584]
	ldr	r3, [lr, #1184]
	mov	r0, r7
	bfi	r1, r3, #22, #9
	ldr	r3, [lr, #1188]
	bfi	r1, r3, #17, #5
	ldr	r3, [lr, #1192]
	bfi	r1, r3, #9, #8
	ldr	r3, [lr, #1212]
	bfi	r1, r3, #0, #9
	str	r1, [r9, #1588]
	ldr	r3, [lr, #1208]
	mov	r1, r6
	bfi	r1, r3, #8, #14
	ldr	r3, [r5, #328]
	bfi	r1, r3, #0, #8
	str	r1, [r9, #1592]
	ldr	r3, [lr, #1196]
	bfi	r6, r3, #16, #8
	ldr	r3, [lr, #1200]
	bfi	r6, r3, #8, #8
	ldr	r3, [lr, #1204]
	mov	lr, r7
	bfi	r6, r3, #0, #8
	str	r6, [r9, #1596]
	ldr	r1, [r5, #336]
	mov	r3, r2
	mov	r6, r7
	bfi	r2, r1, #18, #1
	ldr	r1, [r5, #340]
	bfi	r2, r1, #12, #2
	ldr	r1, [r5, #348]
	bfi	r2, r1, #4, #4
	ldr	r1, [r5, #352]
	bfi	r2, r1, #0, #4
	str	r2, [r9, #1600]
	ldr	r2, [r5, #356]
	mov	r1, r7
	bfi	lr, r2, #0, #10
	ldr	r2, [r5, #360]
	bfi	lr, r2, #16, #9
	str	lr, [r9, #1604]
	ldr	r2, [r5, #364]
	mov	lr, r7
	bfi	r1, r2, #0, #10
	ldr	r2, [r5, #368]
	bfi	r1, r2, #16, #9
	str	r1, [r9, #1608]
	ldr	r2, [r5, #372]
	mov	r1, r7
	bfi	r1, r2, #0, #10
	ldr	r2, [r5, #376]
	bfi	r1, r2, #16, #9
	str	r1, [r9, #1612]
	ldr	r2, [r5, #380]
	mov	r1, r7
	bfi	ip, r2, #0, #10
	ldr	r2, [r5, #384]
	bfi	ip, r2, #16, #9
	str	ip, [r9, #1616]
	ldr	ip, [r5, #388]
	mov	r2, r7
	bfi	r6, ip, #0, #16
	mov	ip, r7
	str	r6, [r9, #1620]
	mov	r6, r7
	ldr	r7, [r5, #420]
	bfi	r6, r7, #0, #13
	ldr	r7, [r5, #424]
	bfi	r6, r7, #13, #1
	str	r6, [r9, #1624]
	ldr	r7, [r5, #428]
	mov	r6, r10
	bfi	r6, r7, #0, #18
	str	r6, [r9, #1628]
	ldr	r7, [r5, #432]
	mov	r6, r10
	bfi	r6, r7, #0, #18
	str	r6, [r9, #1632]
	ldr	r6, [r5, #456]
	bfi	r10, r6, #16, #7
	ldr	r6, [r5, #460]
	bfi	r10, r6, #23, #7
	str	r10, [r9, #1636]
	ldr	r10, [r5, #440]
	ldr	r6, [r5, #464]
	bfi	r3, r10, #12, #8
	ldr	r10, [r5, #468]
	bfi	r3, r6, #8, #4
	ldr	r6, [r5, #472]
	bfi	r3, r10, #0, #8
	ldr	r10, [r5, #476]
	bfi	r3, r6, #20, #8
	mov	r6, lr
	bfi	r3, r10, #28, #4
	str	r3, [r9, #1640]
	ldr	r3, [r5, #448]
	ldr	r10, [r5, #452]
	bfi	r6, r3, #0, #8
	ldr	r3, [r5, #436]
	bfi	r6, r10, #8, #8
	bfi	r6, r3, #16, #8
	str	r6, [r9, #1644]
	ldr	r3, [r5, #480]
	ldr	r7, [r5, #484]
	bfi	lr, r3, #0, #8
	ldr	r3, [r5, #488]
	bfi	lr, r7, #8, #8
	bfi	lr, r3, #16, #16
	str	lr, [r9, #1648]
	ldr	lr, [r4, #3836]
	ldr	r3, [r4, #3840]
	bfi	r0, lr, #24, #8
	ldr	lr, [r4, #3844]
	bfi	r0, r3, #16, #8
	ldr	r3, [r4, #3848]
	bfi	r0, lr, #8, #8
	bfi	r0, r3, #0, #8
	str	r0, [r9, #1652]
	ldr	r0, [r4, #3852]
	ldr	r3, [r4, #3856]
	bfi	r1, r0, #24, #8
	ldr	r0, [r4, #3860]
	bfi	r1, r3, #16, #8
	ldr	r3, [r4, #3864]
	bfi	r1, r0, #8, #8
	bfi	r1, r3, #0, #8
	str	r1, [r9, #1656]
	ldr	r1, [r4, #3868]
	ldr	r3, [r4, #3872]
	bfi	r2, r1, #28, #4
	ldr	r1, [r4, #3876]
	bfi	r2, r3, #23, #5
	ldr	r3, [r4, #3880]
	bfi	r2, r1, #14, #9
	bfi	r2, r3, #0, #14
	str	r2, [r9, #1660]
	ldr	r3, [r8, #552]
	ldr	r2, [r5, #848]
	mov	r5, #0
	bfi	ip, r3, #8, #6
	ldr	r3, [r8, #548]
	bfi	ip, r2, #16, #1
	bfi	ip, r3, #0, #6
	str	ip, [r9, #2304]
	ldr	r1, [r8, #16]
	ldr	r3, [r8, #4]
	ldr	r0, [r8, #540]
	cmp	r3, #0
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #5
	bl	__aeabi_uidiv
	ldr	r6, [fp, #-48]
	mov	r3, #0
	mov	r1, r5
	mov	r2, r5
	mov	ip, r5
	mov	lr, r5
	mov	r7, r1
	bfi	r3, r0, #6, #25
	ldr	r0, [r6, #792]
	bfi	r3, r0, #0, #6
	str	r3, [r9, #2308]
	ldr	r3, [r4, #3460]
	mov	r0, r5
	bfi	r5, r3, #0, #16
	str	r5, [r9, #2312]
	ldr	r5, [r4, #3432]
	mov	r3, r1
	ldr	r10, [r4, #3436]
	bfi	r1, r5, #8, #6
	ldr	r5, [r4, #3408]
	bfi	r1, r5, #16, #4
	mov	r5, r2
	bfi	r1, r10, #0, #6
	str	r1, [r9, #2316]
	ldr	r10, [r4, #3420]
	mov	r1, r2
	ldr	r6, [r4, #3400]
	bfi	r2, r10, #8, #6
	ldr	r10, [r4, #3736]
	bfi	r2, r6, #16, #4
	bfi	r2, r10, #0, #6
	str	r2, [r9, #2320]
	ldr	r10, [r4, #3420]
	mov	r2, ip
	ldr	r6, [r4, #3404]
	bfi	ip, r10, #8, #6
	ldr	r10, [r4, #3724]
	bfi	ip, r6, #16, #4
	bfi	ip, r10, #0, #6
	str	ip, [r9, #2324]
	ldr	r10, [r4, #3416]
	mov	ip, r0
	ldr	r6, [r4, #3396]
	bfi	r0, r10, #8, #6
	ldr	r10, [r4, #3732]
	bfi	r0, r6, #16, #4
	ldr	r6, [fp, #-48]
	bfi	r0, r10, #0, #6
	str	r0, [r9, #2328]
	mov	r0, lr
	ldr	r10, [r6, #796]
	ldr	r6, [r6, #776]
	bfi	lr, r10, #8, #6
	ldr	r10, [r4, #3720]
	bfi	lr, r6, #16, #4
	bfi	lr, r10, #0, #6
	str	lr, [r9, #2332]
	ldr	r10, [r4, #3412]
	mov	lr, r3
	ldr	r6, [r4, #3428]
	bfi	r3, r10, #16, #4
	ldr	r10, [r4, #3728]
	bfi	r3, r6, #8, #6
	bfi	r3, r10, #0, #6
	str	r3, [r9, #2336]
	ldr	r10, [r4, #3440]
	mov	r3, r7
	ldr	r6, [r4, #3444]
	bfi	r7, r10, #16, #4
	ldr	r10, [r4, #3448]
	bfi	r7, r6, #20, #4
	ldr	r6, [r4, #3740]
	bfi	r7, r10, #8, #6
	ldr	r10, [fp, #-48]
	bfi	r7, r6, #0, #6
	str	r7, [r9, #2340]
	mov	r6, r5
	ldr	r7, [r10, #812]
	bfi	r5, r7, #24, #8
	mov	r7, r10
	ldr	r7, [r7, #808]
	ldr	r10, [r10, #804]
	bfi	r5, r7, #16, #8
	ldr	r7, [fp, #-48]
	bfi	r5, r10, #8, #8
	mov	r10, r1
	ldr	r7, [r7, #800]
	bfi	r5, r7, #0, #8
	ldr	r7, [fp, #-48]
	str	r5, [r9, #2344]
	ldr	r5, [r7, #828]
	ldr	r7, [r7, #824]
	bfi	r1, r5, #24, #8
	bfi	r1, r7, #16, #8
	ldr	r7, [fp, #-48]
	ldr	r5, [r7, #816]
	ldr	r7, [r7, #820]
	bfi	r1, r7, #8, #8
	ldr	r7, [fp, #-48]
	bfi	r1, r5, #0, #8
	str	r1, [r9, #2348]
	mov	r1, r2
	ldr	r5, [r7, #844]
	ldr	r7, [r7, #840]
	bfi	r2, r5, #24, #8
	bfi	r2, r7, #16, #8
	ldr	r7, [fp, #-48]
	ldr	r5, [r7, #832]
	ldr	r7, [r7, #836]
	bfi	r2, r7, #8, #8
	ldr	r7, [fp, #-48]
	bfi	r2, r5, #0, #8
	str	r2, [r9, #2352]
	mov	r2, ip
	ldr	r5, [r7, #860]
	ldr	r7, [r7, #856]
	bfi	ip, r5, #24, #8
	bfi	ip, r7, #16, #8
	ldr	r7, [fp, #-48]
	ldr	r5, [r7, #848]
	ldr	r7, [r7, #852]
	bfi	ip, r7, #8, #8
	bfi	ip, r5, #0, #8
	str	ip, [r9, #2356]
	ldr	r5, [r4, #3320]
	mov	ip, r0
	ldr	r7, [r4, #3324]
	bfi	r0, r5, #0, #2
	ldr	r5, [r4, #3328]
	bfi	r0, r7, #2, #2
	ldr	r7, [r4, #3332]
	bfi	r0, r5, #4, #2
	ldr	r5, [r4, #3336]
	bfi	r0, r7, #6, #2
	ldr	r7, [r4, #3340]
	bfi	r0, r5, #8, #2
	ldr	r5, [r4, #3344]
	bfi	r0, r7, #10, #2
	ldr	r7, [r4, #3348]
	bfi	r0, r5, #12, #2
	ldr	r5, [r4, #3352]
	bfi	r0, r7, #14, #2
	ldr	r7, [r4, #3356]
	bfi	r0, r5, #16, #2
	ldr	r5, [r4, #3360]
	bfi	r0, r7, #18, #2
	ldr	r7, [r4, #3364]
	bfi	r0, r5, #20, #2
	ldr	r5, [r4, #3368]
	bfi	r0, r7, #22, #2
	ldr	r7, [r4, #3372]
	bfi	r0, r5, #24, #2
	ldr	r5, [r4, #3380]
	bfi	r0, r7, #26, #2
	ldr	r7, [r4, #3376]
	bfi	r0, r7, #28, #2
	mov	r7, lr
	bfi	r0, r5, #30, #2
	str	r0, [r9, #2360]
	ldr	r0, [r4, #3384]
	mov	r5, r3
	bfi	lr, r0, #0, #5
	str	lr, [r9, #2364]
	ldr	lr, [r4, #3452]
	ldr	r0, [r4, #3456]
	bfi	r3, lr, #0, #4
	mov	lr, r6
	bfi	r3, r0, #4, #4
	ldr	r0, [fp, #-48]
	str	r3, [r9, #2368]
	ldr	r3, [r0, #864]
	bfi	r6, r3, #0, #20
	str	r6, [r9, #2372]
	ldr	r3, [r0, #868]
	mov	r6, r0
	mov	r0, r10
	bfi	r10, r3, #0, #20
	str	r10, [r9, #2376]
	ldr	r10, [r6, #872]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2380]
	ldr	r10, [r6, #876]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2384]
	ldr	r10, [r6, #880]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2388]
	ldr	r10, [r6, #884]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2392]
	ldr	r10, [r6, #888]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2396]
	ldr	r10, [r6, #892]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2400]
	ldr	r10, [r6, #896]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2404]
	ldr	r10, [r6, #900]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2408]
	ldr	r10, [r6, #904]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2412]
	ldr	r10, [r6, #908]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2416]
	ldr	r10, [r6, #912]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2420]
	ldr	r10, [r6, #916]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2424]
	ldr	r10, [r6, #920]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2428]
	ldr	r10, [r6, #924]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2432]
	ldr	r10, [r6, #928]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2436]
	ldr	r10, [r6, #932]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2440]
	ldr	r10, [r6, #936]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2444]
	ldr	r10, [r6, #940]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2448]
	ldr	r10, [r6, #944]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2452]
	ldr	r10, [r6, #948]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2456]
	ldr	r10, [r6, #952]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2460]
	ldr	r10, [r6, #956]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2464]
	ldr	r10, [r6, #960]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2468]
	ldr	r10, [r6, #964]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2472]
	ldr	r10, [r6, #968]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2476]
	ldr	r10, [r6, #972]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2480]
	ldr	r10, [r6, #976]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2484]
	ldr	r10, [r6, #980]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2488]
	ldr	r10, [r6, #984]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2492]
	ldr	r10, [r6, #988]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2496]
	ldr	r10, [r6, #992]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2500]
	ldr	r10, [r6, #996]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2504]
	ldr	r10, [r6, #1000]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2508]
	ldr	r10, [r6, #1004]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2512]
	ldr	r10, [r6, #1008]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2516]
	ldr	r10, [r6, #1012]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2520]
	ldr	r10, [r6, #1016]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2524]
	ldr	r10, [r6, #1020]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2528]
	ldr	r10, [r6, #1024]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2532]
	ldr	r10, [r6, #1028]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2536]
	ldr	r10, [r6, #1032]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2540]
	ldr	r10, [r6, #1036]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2544]
	ldr	r10, [r6, #1040]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2548]
	ldr	r10, [r6, #1044]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2552]
	ldr	r10, [r6, #1048]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2556]
	ldr	r10, [r6, #1052]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2560]
	ldr	r10, [r6, #1056]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2564]
	ldr	r10, [r6, #1060]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2568]
	ldr	r10, [r6, #1064]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2572]
	ldr	r10, [r6, #1068]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2576]
	ldr	r10, [r6, #1072]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2580]
	ldr	r10, [r6, #1076]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2584]
	ldr	r10, [r6, #1080]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2588]
	ldr	r10, [r6, #1084]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2592]
	ldr	r10, [r6, #1088]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2596]
	ldr	r10, [r6, #1092]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2600]
	ldr	r10, [r6, #1096]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2604]
	ldr	r10, [r6, #1100]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2608]
	ldr	r10, [r6, #1104]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2612]
	ldr	r10, [r6, #1108]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2616]
	ldr	r10, [r6, #1112]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2620]
	ldr	r10, [r6, #1116]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2624]
	ldr	r10, [r6, #1120]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2628]
	ldr	r10, [r6, #1124]
	mov	r0, r3
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2632]
	ldr	r10, [r6, #1128]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2636]
	ldr	r10, [r6, #1132]
	mov	r1, r2
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2640]
	ldr	r10, [r6, #1136]
	mov	r2, ip
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2644]
	ldr	r10, [r6, #1140]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2648]
	ldr	r10, [r6, #1144]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2652]
	ldr	r10, [r6, #1148]
	mov	r5, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2656]
	ldr	r10, [r6, #1152]
	mov	lr, r0
	bfi	r0, r10, #0, #20
	str	r0, [r9, #2660]
	ldr	r10, [r6, #1156]
	mov	r0, r3
	str	r0, [fp, #-48]
	bfi	r3, r10, #0, #20
	str	r3, [r9, #2664]
	ldr	r10, [r6, #1160]
	mov	r3, r1
	bfi	r1, r10, #0, #20
	str	r1, [r9, #2668]
	ldr	r10, [r6, #1164]
	mov	r1, r2
	str	r1, [fp, #-52]
	bfi	r2, r10, #0, #20
	str	r2, [r9, #2672]
	ldr	r10, [r6, #1168]
	add	r2, r4, #4096
	bfi	ip, r10, #0, #20
	str	ip, [r9, #2676]
	ldr	r10, [r6, #1172]
	mov	ip, r7
	bfi	r7, r10, #0, #20
	str	r7, [r9, #2680]
	ldr	r10, [r6, #1176]
	mov	r7, r5
	bfi	r5, r10, #0, #20
	str	r5, [r9, #2684]
	ldr	r10, [r6, #1180]
	mov	r5, lr
	mov	r6, lr
	bfi	lr, r10, #0, #20
	str	lr, [r9, #2688]
	ldr	r10, [r4, #3668]
	ldr	lr, [r4, #3672]
	bfi	r0, r10, #8, #2
	ldr	r10, [r4, #3480]
	bfi	r0, lr, #12, #1
	bfi	r0, r10, #0, #5
	str	r0, [r9, #2692]
	ldr	r10, [r4, #3476]
	mov	r0, r3
	ldr	lr, [r4, #3656]
	bfi	r3, r10, #16, #4
	ldr	r10, [r4, #3468]
	bfi	r3, lr, #12, #4
	ldr	lr, [r4, #3472]
	bfi	r3, r10, #9, #2
	ldr	r10, [r4, #3464]
	bfi	r3, lr, #8, #1
	bfi	r3, r10, #0, #6
	str	r3, [r9, #2696]
	ldr	lr, [r4, #3636]
	mov	r10, r1
	add	r3, r9, #4096
	str	lr, [r9, #2700]
	ldr	lr, [r4, #3640]
	str	lr, [r9, #2704]
	ldr	lr, [r4, #3644]
	bfi	r1, lr, #0, #16
	ldr	lr, [r4, #3664]
	bfc	r1, #20, #1
	bfi	r1, lr, #21, #1
	ldr	lr, [r4, #3652]
	bfi	r1, lr, #18, #2
	ldr	lr, [r4, #3648]
	bfi	r1, lr, #16, #2
	str	r1, [r9, #2708]
	ldr	r1, [r2, #1608]
	mov	lr, r0
	bfi	ip, r1, #4, #2
	ldr	r1, [r2, #956]
	bfi	ip, r1, #1, #1
	ldr	r1, [r2, #1628]
	bfi	ip, r1, #2, #1
	str	ip, [r9, #3328]
	ldr	ip, [r2, #1308]
	mov	r1, r7
	bfi	r7, ip, #16, #16
	ldr	ip, [r2, #1312]
	bfi	r7, ip, #0, #16
	str	r7, [r9, #3332]
	ldr	ip, [r2, #1632]
	mov	r7, r6
	bfi	r6, ip, #6, #6
	ldr	ip, [r2, #1636]
	bfi	r6, ip, #0, #6
	str	r6, [r9, #3336]
	ldr	r6, [r2, #1292]
	mov	ip, r5
	bfi	r5, r6, #31, #1
	ldr	r6, [r2, #1296]
	bfi	r5, r6, #0, #17
	str	r5, [r9, #3340]
	ldr	r6, [r2, #1300]
	mov	r5, r0
	bfi	lr, r6, #16, #11
	ldr	r6, [r2, #1304]
	bfi	lr, r6, #0, #10
	str	lr, [r9, #3344]
	ldr	lr, [r2, #1404]
	mov	r6, r1
	bfi	r0, lr, #3, #1
	ldr	lr, [r2, #1408]
	bfi	r0, lr, #2, #1
	ldr	lr, [r2, #1412]
	bfi	r0, lr, #1, #1
	ldr	lr, [r2, #1400]
	bfi	r0, lr, #0, #1
	str	r0, [r9, #3840]
	ldr	r0, [r2, #1416]
	bfi	r10, r0, #4, #1
	str	r10, [r9, #3844]
	ldr	lr, [r2, #1060]
	mov	r0, r1
	mov	r10, r1
	bfi	r6, lr, #0, #1
	str	r6, [r3]
	ldr	lr, [r2, #1068]
	mov	r6, r7
	bfi	r1, lr, #15, #1
	ldr	lr, [r2, #1072]
	bfi	r1, lr, #14, #1
	ldr	lr, [r2, #1076]
	bfi	r1, lr, #13, #1
	ldr	lr, [r2, #1080]
	bfi	r1, lr, #12, #1
	ldr	lr, [r2, #1084]
	bfi	r1, lr, #8, #4
	ldr	lr, [r2, #1088]
	bfi	r1, lr, #4, #4
	ldr	lr, [r2, #1092]
	bfi	r1, lr, #0, #4
	str	r1, [r3, #4]
	ldr	r1, [r2, #1096]
	mov	lr, ip
	bfi	r7, r1, #0, #4
	str	r7, [r3, #8]
	ldr	r1, [r2, #1108]
	mov	r7, r5
	bfi	ip, r1, #0, #8
	ldr	r1, [r2, #1104]
	bfi	ip, r1, #8, #8
	ldr	r1, [r2, #1100]
	bfi	ip, r1, #16, #8
	str	ip, [r3, #12]
	ldr	r1, [r2, #1116]
	mov	ip, r0
	bfi	r5, r1, #0, #16
	mvn	r1, #0
	str	r5, [r3, #16]
	str	r1, [r3, #20]
	str	r1, [r3, #24]
	mov	r1, #7
	str	r1, [r3, #28]
	mvn	r1, #0
	str	r1, [r3, #32]
	mov	r1, #7
	str	r1, [r3, #36]
	mov	r1, r0
	ldr	r5, [r2, #1180]
	bfi	r0, r5, #3, #1
	ldr	r5, [r2, #1176]
	bfi	r0, r5, #2, #1
	ldr	r5, [r2, #1172]
	bfi	r0, r5, #1, #1
	mov	r5, r1
	orr	r0, r0, #1
	str	r0, [r3, #40]
	ldr	r0, [r2, #1424]
	str	r0, [r3, #256]
	ldr	r0, [r2, #1428]
	str	r0, [r3, #260]
	ldr	r0, [r2, #1432]
	str	r0, [r3, #264]
	ldr	r0, [r2, #1436]
	str	r0, [r3, #268]
	ldr	r0, [r2, #1440]
	str	r0, [r3, #272]
	ldr	r0, [r2, #1444]
	str	r0, [r3, #276]
	ldr	r0, [r2, #1396]
	bfi	r10, r0, #0, #1
	str	r10, [r3, #280]
	ldr	r0, [r2, #1660]
	bfi	r6, r0, #0, #8
	ldr	r0, [r2, #1664]
	bfi	r6, r0, #8, #8
	str	r6, [r3, #512]
	ldr	r0, [r4, #3296]
	mov	r6, lr
	bfi	lr, r0, #0, #16
	ldr	r0, [r4, #3300]
	bfi	lr, r0, #16, #16
	str	lr, [r3, #1280]
	ldr	r0, [r4, #3312]
	mov	lr, r7
	bfi	r7, r0, #16, #16
	str	r7, [r3, #1284]
	ldr	r7, [r4, #3304]
	mov	r0, ip
	bfi	ip, r7, #0, #16
	ldr	r7, [r4, #3308]
	bfi	ip, r7, #16, #16
	str	ip, [r3, #1288]
	ldr	r7, [r4, #3316]
	mov	ip, r1
	bfi	r5, r7, #0, #3
	str	r5, [r3, #1296]
	ldr	r5, [r2, #1364]
	movw	r7, #9729
	ldr	r2, [r8, #536]
	bfi	r1, r5, #8, #3
	movw	r5, #513
	cmp	r2, r6
	movne	r5, r7
	bfi	r1, r5, #16, #16
	str	r1, [r3, #2560]
	ldr	r2, [r8, #632]
	ldr	r1, [r8, #636]
	bfi	r6, r2, #0, #5
	ldr	r2, [fp, #-56]
	bfi	r6, r1, #16, #16
	str	r6, [r3, #2564]
	ldr	r1, [r8, #632]
	ldr	r5, [r8, #672]
	rsb	r1, r1, #16
	ldr	r2, [r2]
	mov	r1, r5, asl r1
	bfi	lr, r1, #0, #16
	str	lr, [r3, #2568]
	ldr	lr, [r4, #2464]
	ldr	r1, [r4, #2468]
	bfi	r0, lr, #0, #5
	bfi	r0, r1, #16, #16
	str	r0, [r3, #2604]
	ldr	r1, [r4, #2464]
	ldr	r0, [r4, #2460]
	rsb	r1, r1, #16
	mov	r1, r0, asl r1
	bfi	ip, r1, #0, #16
	str	ip, [r3, #2608]
	ldr	r1, [r8, #4]
	cmp	r1, #2
	bne	.L124
	ldr	r1, [r8, #636]
	cmp	r1, #31
	addhi	r2, r2, #4096
	addls	r2, r2, #4096
	ldrls	r0, [r8, #640]
	rsbls	r1, r1, #32
	ldrhi	r1, [r8, #640]
	movls	r1, r0, asl r1
	str	r1, [r2, #2572]
	ldr	r1, [r8, #636]
	cmp	r1, #63
	rsbls	r1, r1, #64
	ldrhi	r1, [r8, #644]
	ldrls	r0, [r8, #644]
	movls	r1, r0, asl r1
	str	r1, [r2, #2576]
	ldr	r1, [r8, #636]
	cmp	r1, #64
	rsbhi	r1, r1, #96
	ldrhi	r0, [r8, #648]
	movhi	r1, r0, asl r1
	strhi	r1, [r2, #2580]
	ldr	r1, [r8, #652]
	str	r1, [r2, #2584]
	ldr	r1, [r8, #656]
	str	r1, [r2, #2588]
	ldr	r1, [r8, #660]
	str	r1, [r2, #2592]
	ldr	r1, [r8, #664]
	str	r1, [r2, #2596]
	ldr	r1, [r8, #668]
	str	r1, [r2, #2600]
	ldr	r1, [r8, #4]
.L124:
	cmp	r1, #0
	bne	.L130
	ldr	r2, [r8, #600]
	str	r2, [r3, #2816]
	ldr	r2, [r8, #604]
	str	r2, [r3, #2820]
	ldr	r2, [r8, #608]
	str	r2, [r3, #2824]
	ldr	r2, [r8, #612]
	str	r2, [r3, #2828]
	ldr	r2, [r8, #616]
	str	r2, [r3, #2832]
	ldr	r2, [r8, #620]
	str	r2, [r3, #2836]
	ldr	r2, [r8, #624]
	str	r2, [r3, #2840]
	ldr	r2, [r8, #628]
	str	r2, [r3, #2844]
	ldr	r2, [r8, #632]
	ldr	r1, [r3, #2848]
	sub	r2, r2, #1
	bfi	r1, r2, #16, #7
	str	r1, [r3, #2848]
	ldr	r2, [r8, #632]
	ldr	r1, [r3, #2848]
	mov	r2, r2, lsr #8
	sub	r2, r2, #1
	bfi	r1, r2, #8, #6
	str	r1, [r3, #2848]
	ldr	r2, [r8, #632]
	ldr	r1, [r3, #2848]
	mov	r2, r2, lsr #16
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #2848]
.L130:
	add	r0, r4, #4096
	mov	r1, #0
	bfc	r1, #0, #1
	ldr	r2, [fp, #-56]
	ldr	r0, [r0, #1392]
	bfi	r1, r0, #1, #24
	str	r1, [r3, #2852]
	ldr	r1, [r8, #4]
	ldr	r2, [r2]
	cmp	r1, #2
	bne	.L131
	ldr	r1, [r4, #2468]
	cmp	r1, #31
	addhi	r2, r2, #4096
	addls	r2, r2, #4096
	ldrls	r0, [r4, #2428]
	rsbls	r1, r1, #32
	ldrhi	r1, [r4, #2428]
	movls	r1, r0, asl r1
	str	r1, [r2, #2612]
	ldr	r1, [r4, #2468]
	cmp	r1, #63
	rsbls	r1, r1, #64
	ldrhi	r1, [r4, #2432]
	ldrls	r0, [r4, #2432]
	movls	r1, r0, asl r1
	str	r1, [r2, #2616]
	ldr	r1, [r4, #2468]
	cmp	r1, #64
	rsbhi	r1, r1, #96
	ldrhi	r0, [r4, #2436]
	movhi	r1, r0, asl r1
	strhi	r1, [r2, #2620]
	ldr	r1, [r4, #2440]
	str	r1, [r2, #2624]
	ldr	r1, [r4, #2444]
	str	r1, [r2, #2628]
	ldr	r1, [r4, #2448]
	str	r1, [r2, #2632]
	ldr	r1, [r4, #2452]
	str	r1, [r2, #2636]
	ldr	r1, [r4, #2456]
	str	r1, [r2, #2640]
	ldr	r1, [r8, #4]
.L131:
	cmp	r1, #0
	bne	.L137
	ldr	r2, [r4, #2396]
	str	r2, [r3, #2856]
	ldr	r2, [r4, #2400]
	str	r2, [r3, #2860]
	ldr	r2, [r4, #2404]
	str	r2, [r3, #2864]
	ldr	r2, [r4, #2408]
	str	r2, [r3, #2868]
	ldr	r2, [r4, #2412]
	str	r2, [r3, #2872]
	ldr	r2, [r4, #2416]
	str	r2, [r3, #2876]
	ldr	r2, [r4, #2420]
	str	r2, [r3, #2880]
	ldr	r2, [r4, #2424]
	str	r2, [r3, #2884]
	ldr	r2, [r4, #2392]
	ldr	r1, [r3, #2888]
	sub	r2, r2, #1
	bfi	r1, r2, #16, #7
	str	r1, [r3, #2888]
	ldr	r2, [r4, #2392]
	ldr	r1, [r3, #2888]
	mov	r2, r2, lsr #8
	sub	r2, r2, #1
	bfi	r1, r2, #8, #6
	str	r1, [r3, #2888]
	ldr	r2, [r4, #2392]
	ldr	r1, [r3, #2888]
	mov	r2, r2, lsr #16
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #2888]
.L137:
	ldr	r0, [r8, #48]
	add	r2, r4, #4096
	mov	r1, #0
	bfi	r1, r0, #0, #1
	str	r1, [r3, #3072]
	ldr	r2, [r2, #1772]
	str	r2, [r3, #3076]
	ldr	r2, [r8, #536]
	cmp	r2, #0
	ldrne	r2, [r3, #3216]
	ldreq	r1, [r3, #3216]
	orrne	r2, r2, #65536
	bfieq	r1, r2, #16, #1
	strne	r2, [r3, #3216]
	streq	r1, [r3, #3216]
	ldr	r2, [r3, #3216]
	orr	r2, r2, #256
	str	r2, [r3, #3216]
	ldr	r2, [r3, #3216]
	tst	r2, #65536
	beq	.L140
	ldrb	r1, [r8, #340]
	ldr	r2, [r3, #3216]
	bfi	r2, r1, #0, #8
	str	r2, [r3, #3216]
	ldr	r2, [r8, #344]
	str	r2, [r3, #3220]
	ldr	r2, [r8, #348]
	str	r2, [r3, #3224]
	ldr	r2, [r8, #352]
	str	r2, [r3, #3228]
	ldr	r2, [r8, #356]
	str	r2, [r3, #3232]
	ldr	r2, [r8, #360]
	str	r2, [r3, #3236]
	ldr	r2, [r8, #364]
	str	r2, [r3, #3240]
	ldr	r2, [r8, #368]
	str	r2, [r3, #3244]
	ldr	r2, [r8, #372]
	str	r2, [r3, #3248]
	ldr	r2, [r8, #376]
	str	r2, [r3, #3252]
	ldr	r2, [r8, #380]
	str	r2, [r3, #3256]
	ldr	r2, [r8, #384]
	str	r2, [r3, #3260]
	ldr	r2, [r8, #388]
	str	r2, [r3, #3264]
	ldr	r2, [r8, #392]
	str	r2, [r3, #3268]
	ldr	r2, [r8, #396]
	str	r2, [r3, #3272]
	ldr	r2, [r8, #400]
	str	r2, [r3, #3276]
	ldr	r2, [r8, #404]
	str	r2, [r3, #3280]
	ldr	r2, [r8, #408]
	str	r2, [r3, #3284]
	ldr	r2, [r8, #412]
	str	r2, [r3, #3288]
	ldr	r2, [r8, #416]
	str	r2, [r3, #3292]
	ldr	r2, [r8, #420]
	str	r2, [r3, #3296]
	ldr	r2, [r8, #424]
	str	r2, [r3, #3300]
	ldr	r2, [r8, #428]
	str	r2, [r3, #3304]
	ldr	r2, [r8, #432]
	str	r2, [r3, #3308]
	ldr	r2, [r8, #436]
	str	r2, [r3, #3312]
	ldr	r2, [r8, #440]
	str	r2, [r3, #3316]
	ldr	r2, [r8, #444]
	str	r2, [r3, #3320]
	ldr	r2, [r8, #448]
	str	r2, [r3, #3324]
	ldr	r2, [r8, #452]
	str	r2, [r3, #3328]
	ldr	r2, [r8, #456]
	str	r2, [r3, #3332]
	ldr	r2, [r8, #460]
	str	r2, [r3, #3336]
	ldr	r2, [r8, #464]
	str	r2, [r3, #3340]
	ldr	r2, [r8, #468]
	str	r2, [r3, #3344]
	ldr	r2, [r8, #472]
	str	r2, [r3, #3348]
	ldr	r2, [r8, #476]
	str	r2, [r3, #3352]
	ldr	r2, [r8, #480]
	str	r2, [r3, #3356]
	ldr	r2, [r8, #484]
	str	r2, [r3, #3360]
	ldr	r2, [r8, #488]
	str	r2, [r3, #3364]
	ldr	r2, [r8, #492]
	str	r2, [r3, #3368]
	ldr	r2, [r8, #496]
	str	r2, [r3, #3372]
	ldr	r2, [r8, #500]
	str	r2, [r3, #3376]
	ldr	r2, [r8, #504]
	str	r2, [r3, #3380]
	ldr	r2, [r8, #508]
	str	r2, [r3, #3384]
	ldr	r2, [r8, #512]
	str	r2, [r3, #3388]
	ldr	r2, [r8, #516]
	str	r2, [r3, #3392]
	ldr	r2, [r8, #520]
	str	r2, [r3, #3396]
	ldr	r2, [r8, #524]
	str	r2, [r3, #3400]
	ldr	r2, [r8, #528]
	str	r2, [r3, #3404]
	ldr	r2, [r8, #532]
	str	r2, [r3, #3408]
.L140:
	ldr	r2, [r8, #200]
	mov	r1, #0
	add	r4, r4, #4096
	mov	r5, #0
	mov	lr, r5
	mov	ip, #0
	str	r2, [r3, #3148]
	mov	r2, #9
	ldr	r6, [r8, #204]
	bfi	r1, r2, #24, #8
	bfc	r5, #0, #1
	bfc	lr, #0, #1
	bfc	ip, #0, #1
	mov	r0, #0
	str	r6, [r3, #3152]
	mov	r6, #0
	ldr	r7, [r8, #208]
	bfc	r0, #0, #1
	add	r2, r9, #61440
	bfc	r5, #1, #1
	bfc	lr, #1, #1
	bfc	ip, #1, #1
	str	r7, [r3, #3156]
	bfc	r0, #1, #1
	ldr	r7, [r8, #212]
	bfc	r5, #2, #1
	bfc	lr, #2, #1
	bfc	ip, #2, #1
	bfc	r0, #2, #1
	bfc	r5, #3, #1
	str	r7, [r3, #3160]
	mov	r7, #7
	ldr	r10, [r8, #216]
	bfi	r1, r7, #16, #8
	bfc	r1, #8, #8
	bfc	lr, #3, #1
	bfc	ip, #3, #1
	bfc	r0, #3, #1
	str	r10, [r3, #3164]
	mov	r10, r6
	ldr	r7, [r8, #220]
	bfc	r10, #0, #1
	str	r7, [r3, #3168]
	mov	r7, #1
	bfi	r1, r7, #0, #8
	ldr	r7, [r8, #224]
	str	r7, [r3, #3172]
	ldr	r7, [r8, #228]
	str	r7, [r3, #3176]
	ldr	r7, [r8, #232]
	str	r7, [r3, #3180]
	ldr	r7, [r8, #236]
	str	r7, [r3, #3184]
	ldr	r7, [r8, #240]
	str	r7, [r3, #3188]
	ldr	r7, [r8, #244]
	str	r7, [r3, #3192]
	ldr	r7, [r8, #248]
	str	r7, [r3, #3196]
	ldr	r7, [r8, #252]
	str	r7, [r3, #3200]
	ldr	r7, [r8, #256]
	str	r7, [r3, #3204]
	ldr	r7, [r8, #260]
	str	r7, [r3, #3208]
	ldr	r7, [r8, #336]
	str	r7, [r3, #3212]
	ldr	r7, [r8, #264]
	str	r7, [r3, #3084]
	ldr	r7, [r8, #268]
	str	r7, [r3, #3088]
	ldr	r7, [r8, #272]
	str	r7, [r3, #3092]
	ldr	r7, [r8, #276]
	str	r7, [r3, #3096]
	ldr	r7, [r8, #280]
	str	r7, [r3, #3100]
	ldr	r7, [r8, #284]
	str	r7, [r3, #3104]
	ldr	r7, [r8, #288]
	str	r7, [r3, #3108]
	ldr	r7, [r8, #292]
	str	r7, [r3, #3112]
	ldr	r7, [r8, #296]
	str	r7, [r3, #3116]
	ldr	r7, [r8, #300]
	str	r7, [r3, #3120]
	ldr	r7, [r8, #304]
	str	r7, [r3, #3124]
	ldr	r7, [r8, #308]
	str	r7, [r3, #3128]
	ldr	r7, [r8, #312]
	str	r7, [r3, #3132]
	ldr	r7, [r8, #316]
	str	r7, [r3, #3136]
	ldr	r7, [r8, #320]
	str	r7, [r3, #3140]
	ldr	r7, [r8, #324]
	str	r7, [r3, #3144]
	mov	r7, #3
	ldr	r3, [r4, #1676]
	ldr	r4, [r4, #1680]
	bfi	r6, r3, #0, #1
	ldr	r3, [fp, #-56]
	bfi	r6, r4, #3, #1
	mov	r4, #0
	bfi	r6, r7, #16, #4
	str	r6, [r2]
	ldr	r3, [r3]
	str	r10, [r2, #8]
	str	r5, [r2, #16]
	add	r3, r3, #61440
	str	lr, [r2, #28]
	str	ip, [r2, #32]
	str	r0, [r2, #44]
	mov	r0, #0
	str	r1, [r2, #1328]
	str	r4, [r9, #4]
	ldr	r2, [r8, #576]
	str	r2, [r3, #520]
	ldr	r2, [r8, #576]
	str	r2, [r3, #524]
	ldr	r2, [r8, #584]
	str	r2, [r3, #752]
	ldr	r2, [r8, #580]
	str	r2, [r3, #756]
	ldr	r2, [r8, #584]
	str	r2, [r3, #772]
	ldr	r2, [r8, #580]
	str	r2, [r3, #776]
	mov	r3, #1
	str	r3, [r9, #8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L154:
	mov	r0, r3
	str	r3, [fp, #-56]
	ldr	r10, [r0, #4]
	mov	r2, #692
	ldr	r0, [r0]
	mov	r1, r8
	ldr	r3, .L163
	add	r5, r10, r2
	ldr	r4, [r8, #688]
	add	r6, r10, #6528
	str	r0, [fp, #-60]
	mov	r0, r10
	ldr	r3, [r3, #4]
	add	r6, r6, #40
	blx	r3
	mov	r0, r5
	ldr	r2, [r8, #536]
	ldr	r1, [r8, #544]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	mov	r0, r5
	ldr	r1, [r8, #4]
	add	r5, r10, #4096
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	r3, [r8, #40]
	ldr	r2, [r8, #12]
	cmp	r3, #0
	bne	.L156
	b	.L164
.L165:
	.align	2
.L163:
	.word	venc_Osal_Func_Ptr_S
.L164:
.L78:
	ldmib	r8, {r2, r3}
	cmp	r2, #0
	beq	.L157
	mov	r3, #0
	mov	r2, #7
	str	r3, [r5, #2372]
	str	r3, [r5, #2368]
	str	r2, [r5, #2364]
.L83:
	ldr	r3, [r8, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	bhi	.L84
	ldr	r3, [r8, #4]
	cmp	r3, #0
	bne	.L84
	add	r2, r5, #4096
	mov	r1, #28
	str	r1, [r8, #552]
	str	r1, [r8, #548]
	str	r1, [r8, #544]
	str	r3, [r10, #792]
	str	r3, [r8, #20]
	str	r3, [r2, #1612]
	str	r3, [r2, #1196]
	str	r3, [r2, #1192]
	str	r3, [r2, #940]
	str	r3, [r2, #432]
	str	r3, [r5, #3616]
	str	r3, [r2, #1584]
.L84:
	ldr	r9, [fp, #-60]
	mov	r1, #0
	ldr	ip, [r8, #684]
	add	r7, r5, #4096
	mov	r2, r1
	bfc	r2, #16, #1
	mov	r0, #207
	mov	r3, r1
	str	ip, [r9, #280]
	mov	ip, #3
	str	r0, [r9]
	mov	r0, #4
	bfi	r2, r0, #13, #3
	ldr	lr, [r7, #824]
	bfi	r2, r0, #10, #3
	bfi	r2, ip, #7, #3
	mov	ip, #1
	bfi	r2, ip, #5, #2
	str	lr, [r9, #16]
	bfi	r2, r0, #2, #3
	ldr	lr, [r7, #784]
	ldr	r0, [r7, #788]
	bfi	r2, ip, #0, #2
	ldr	ip, [r7, #832]
	bfi	r1, lr, #31, #1
	ldr	lr, [r7, #836]
	bfi	r1, r0, #30, #1
	sub	ip, ip, #1
	mov	r0, r3
	bfi	r1, ip, #16, #9
	sub	lr, lr, #1
	bfi	r1, lr, #0, #9
	str	r1, [r9, #20]
	ldr	r1, [r7, #1768]
	str	r1, [r9, #24]
	ldr	ip, [r7, #1764]
	ldr	r1, [r7, #1760]
	bfi	r3, ip, #21, #1
	ldr	ip, [r7, #1612]
	bfi	r3, r1, #19, #2
	ldr	r1, [r7, #1640]
	orr	r3, r3, #458752
	ldr	lr, [r7, #1616]
	bfi	r3, ip, #2, #1
	ldr	ip, [r7, #1620]
	bfi	r3, r1, #23, #1
	ldr	r1, [r7, #1624]
	bfi	r3, lr, #3, #1
	bfi	r3, ip, #1, #1
	bfi	r3, r1, #0, #1
	str	r3, [r9, #52]
	ldr	r1, [r7, #1668]
	ldr	r3, [r7, #1672]
	bfi	r0, r1, #4, #4
	bfi	r0, r3, #0, #4
	str	r0, [r9, #56]
	str	r2, [r9, #68]
	ldr	r3, [r8, #4]
	ldr	r0, [r8, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r9, #16
	movne	r9, #32
	mov	r1, r9
	add	r0, r0, r9
	bl	__aeabi_uidiv
	ldr	r3, [r8, #16]
	mov	r1, r9
	str	r0, [fp, #-48]
	sub	r0, r3, #1
	add	r0, r0, r9
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-48]
	mul	r1, r2, r0
	ldr	r0, [r8, #540]
	bl	__aeabi_uidiv
	ldr	r9, [fp, #-60]
	mov	r1, #0
	mov	r3, r6
	mov	r2, r1
	bfi	r1, r0, #0, #20
	str	r1, [r9, #588]
	ldr	r1, [r7, #1244]
	mov	r0, r8
	bfi	r2, r1, #0, #4
	str	r2, [r9, #592]
	ldr	r2, [r5, #2372]
	ldr	r1, [r5, #2368]
	bl	CfgVcpiMode.isra.7
	ldr	r2, [r7, #1184]
	ldr	r1, [r7, #1188]
	mov	r3, #0
	bfi	r3, r2, #16, #9
	mov	r2, #0
	bfi	r3, r1, #0, #9
	str	r3, [r4]
	ldr	r1, [r8, #20]
	mov	r3, r2
	ldr	ip, [r8, #28]
	mov	r0, r2
	bfi	r2, r1, #17, #1
	mov	r1, r3
	orr	r2, r2, #65536
	bfi	r2, ip, #0, #16
	str	r2, [r4, #8]
	ldr	r2, [r8, #544]
	ldr	ip, [r7, #840]
	bfi	r3, r2, #10, #6
	ldr	r2, [r7, #844]
	bfi	r3, ip, #5, #5
	ldr	ip, [r5, #3616]
	bfi	r3, r2, #0, #5
	ldr	r2, [r5, #3600]
	bfi	r3, ip, #18, #1
	add	ip, r5, #4096
	bfi	r3, r2, #19, #1
	str	r3, [r4, #12]
	ldr	r3, [r7, #1000]
	ldr	r2, [r7, #1004]
	bfi	r0, r3, #8, #2
	ldr	r3, [r7, #1008]
	bfi	r0, r2, #4, #4
	bfi	r0, r3, #0, #4
	str	r0, [r4, #16]
	ldr	r2, [r8, #16]
	mov	r0, #0
	ldr	r3, [r8, #12]
	mov	lr, r0
	sub	r2, r2, #1
	mov	r6, r0
	bfi	r1, r2, #16, #13
	sub	r3, r3, #1
	bfi	r1, r3, #0, #13
	str	r1, [r4, #4]
	ldr	r3, [r7, #1396]
	mov	r1, r0
	cmp	r3, #1
	ldrne	r2, [r7, #1020]
	movne	r3, #0
	moveq	r3, #3
	mov	r7, ip
	bfine	r3, r2, #0, #2
	str	r3, [r4, #20]
	ldr	ip, [ip, #1028]
	mov	r2, r0
	mov	r3, r0
	bfi	r0, ip, #0, #1
	mov	ip, r7
	bfc	r0, #1, #1
	str	r0, [r4, #24]
	ldr	r0, [r7, #932]
	mov	r7, r3
	ldr	r9, [ip, #936]
	str	r0, [fp, #-48]
	ldr	r0, [fp, #-48]
	bfi	r3, r0, #12, #4
	ldr	r0, [ip, #948]
	bfi	r3, r9, #8, #4
	ldr	r9, [r5, #2364]
	bfi	r3, r0, #4, #1
	ldr	r0, [ip, #952]
	bfi	r3, r9, #0, #3
	mov	r9, r1
	bfi	r3, r0, #5, #1
	str	r3, [r4, #28]
	ldr	r0, [ip, #900]
	bfc	r9, #4, #2
	ldr	r3, [ip, #908]
	bfc	r9, #2, #2
	bfi	r1, r0, #12, #1
	str	r2, [fp, #-64]
	bfi	r1, r3, #4, #2
	str	r2, [fp, #-68]
	orr	r1, r1, #3
	str	r1, [r4, #32]
	mov	r1, ip
	ldr	ip, [ip, #1224]
	str	r1, [fp, #-48]
	mov	r3, r2
	bfi	r2, ip, #4, #1
	ldr	ip, [fp, #-48]
	ldr	r0, [r1, #940]
	orr	r9, r9, #2
	ldr	r1, [ip, #944]
	bfi	r2, r0, #2, #1
	ldr	r0, [ip, #1192]
	bfi	r2, r1, #3, #1
	mov	r1, lr
	bfi	r2, r0, #1, #1
	ldr	r0, [ip, #1196]
	bfi	r2, r0, #0, #1
	mov	r0, ip
	str	r2, [r4, #36]
	mov	r2, lr
	ldr	r0, [r0, #1200]
	ldr	ip, [ip, #1204]
	bfi	r6, r0, #16, #16
	mov	r0, r8
	bfi	r6, ip, #0, #16
	ldr	ip, [fp, #-48]
	str	r6, [r4, #40]
	ldr	r6, [ip, #1208]
	bfi	lr, r6, #24, #8
	ldr	r6, [ip, #1212]
	bfi	lr, r6, #16, #8
	ldr	r6, [ip, #1216]
	bfi	lr, r6, #8, #8
	ldr	r6, [ip, #1220]
	bfi	lr, r6, #0, #8
	str	lr, [r4, #44]
	ldr	lr, [r10, #788]
	ldr	r6, [ip, #1600]
	bfi	r7, lr, #1, #1
	ldr	lr, [ip, #1596]
	bfi	r7, r6, #16, #8
	mov	r6, r3
	bfi	r7, lr, #24, #8
	str	r7, [r4, #48]
	ldr	lr, [r10, #692]
	ldr	r7, [r10, #696]
	bfi	r6, lr, #2, #1
	ldr	lr, [r5, #2476]
	bfi	r6, r7, #1, #1
	str	r6, [fp, #-52]
	ldr	r7, [ip, #1228]
	mov	r6, ip
	ldr	ip, [fp, #-52]
	bfi	ip, lr, #0, #1
	ldr	lr, [r6, #1232]
	bfi	ip, r7, #3, #1
	str	r9, [r4, #56]
	bfi	ip, lr, #4, #1
	str	ip, [fp, #-52]
	str	ip, [r4, #52]
	ldr	ip, [r5, #3584]
	ldr	lr, [r5, #3588]
	bfi	r3, ip, #0, #1
	ldr	ip, [r10, #784]
	bfi	r3, lr, #1, #1
	ldr	lr, [r5, #3612]
	bfi	r3, ip, #2, #1
	ldr	ip, [r5, #3580]
	bfi	r3, lr, #4, #1
	ldr	lr, [r10, #780]
	bfi	r3, ip, #9, #1
	ldr	ip, [r5, #3632]
	bfi	r3, lr, #8, #1
	ldr	lr, [r5, #3688]
	bfi	r3, ip, #3, #1
	ldr	ip, [r5, #3572]
	bfi	r3, lr, #15, #1
	ldr	lr, [r5, #3576]
	bfi	r3, ip, #14, #1
	ldr	ip, [r5, #3684]
	bfi	r3, lr, #13, #1
	ldr	lr, [r5, #3680]
	ldr	r7, [r5, #3676]
	bfi	r3, ip, #12, #1
	bfi	r3, lr, #11, #1
	ldr	ip, [r5, #3620]
	bfi	r3, r7, #10, #1
	mov	lr, r1
	bfi	r3, ip, #18, #1
	str	r3, [r4, #60]
	ldr	ip, [r6, #1584]
	ldr	r3, [r6, #1588]
	bfi	lr, ip, #8, #1
	mov	ip, r1
	bfi	lr, r3, #0, #8
	str	lr, [r4, #64]
	ldr	r3, [r6, #1592]
	bfi	ip, r3, #0, #1
	str	ip, [r4, #68]
	ldr	ip, [r6, #1756]
	ldr	r3, [r6, #1752]
	bfi	r1, ip, #0, #1
	ldr	ip, [r6, #1748]
	bfi	r1, r3, #1, #1
	ldr	r3, [r6, #1744]
	bfi	r1, ip, #2, #1
	ldr	ip, [r6, #1740]
	bfi	r1, r3, #3, #1
	ldr	r3, [r6, #1736]
	bfi	r1, ip, #4, #1
	ldr	ip, [r6, #1732]
	bfi	r1, r3, #5, #1
	ldr	r3, [r6, #1692]
	bfi	r1, ip, #6, #1
	bfi	r1, r3, #7, #1
	str	r1, [r4, #72]
	ldr	r3, [r6, #1728]
	ldr	r1, [r6, #1724]
	bfi	r2, r3, #0, #1
	ldr	r3, [r6, #1720]
	bfi	r2, r1, #1, #1
	ldr	r1, [r6, #1716]
	bfi	r2, r3, #2, #1
	ldr	r3, [r6, #1684]
	bfi	r2, r1, #3, #1
	ldr	r1, [r6, #1688]
	bfi	r2, r3, #4, #1
	ldr	r3, [r6, #1712]
	bfi	r2, r1, #5, #1
	ldr	r1, [r6, #1708]
	bfi	r2, r3, #6, #1
	ldr	r3, [r6, #1696]
	bfi	r2, r1, #7, #1
	ldr	r1, [r6, #1704]
	bfi	r2, r3, #8, #1
	ldr	r3, [r6, #1700]
	bfi	r2, r1, #9, #1
	bfi	r2, r3, #10, #1
	str	r2, [r4, #76]
	bl	CfgSwL0Size
	mov	r2, #1
	mov	r3, #0
	bfi	r3, r2, #16, #6
	bfi	r3, r2, #0, #7
	ldr	r2, [fp, #-60]
	mov	lr, #0
	str	lr, [fp, #-52]
	mov	r1, lr
	mov	r9, lr
	str	r3, [r2, #128]
	movw	r2, #43691
	ldr	r3, [r8, #168]
	movt	r2, 43690
	mov	ip, lr
	mov	r0, r8
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #156]
	str	r3, [r4, #88]
	ldr	r3, [r8, #168]
	add	r3, r3, #2
	umull	r6, r7, r3, r2
	mov	r7, r7, lsr #1
	add	r7, r7, r7, lsl #1
	rsb	r7, r7, r3
	add	r7, r8, r7, lsl #2
	ldr	r3, [r7, #156]
	str	r3, [r4, #92]
	ldr	r7, [r8, #168]
	add	r7, r7, #1
	umull	r2, r3, r7, r2
	mov	r3, r3, lsr #1
	add	r3, r3, r3, lsl #1
	rsb	r3, r3, r7
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #156]
	str	r3, [r4, #96]
	ldr	r3, [r8, #196]
	str	r3, [r4, #100]
	ldr	r3, [r8, #68]
	str	r3, [r4, #104]
	ldr	r3, [r8, #72]
	str	r3, [r4, #108]
	ldr	r3, [r8, #76]
	str	r3, [r4, #112]
	ldr	r2, [r8, #80]
	ldr	r3, [r8, #84]
	bfi	lr, r2, #16, #16
	bfi	lr, r3, #0, #16
	str	lr, [r4, #124]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #88]
	str	r3, [r4, #128]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #96]
	str	r3, [r4, #132]
	ldr	r2, [r8, #104]
	ldr	r3, [r8, #108]
	bfi	ip, r2, #0, #16
	mov	r2, r1
	bfi	ip, r3, #16, #16
	str	ip, [r4, #136]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #112]
	str	r3, [r4, #140]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #120]
	str	r3, [r4, #144]
	ldr	r3, [r8, #128]
	bfi	r2, r3, #0, #16
	str	r2, [r4, #148]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #84
	movne	r3, #80
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r4, #152]
	ldr	r3, [r8, #136]
	cmp	r3, r1
	moveq	r3, #92
	movne	r3, #88
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r4, #156]
	ldr	r2, [r8, #104]
	ldr	r3, [r8, #108]
	bfi	r1, r2, #16, #16
	bfi	r1, r3, #0, #16
	str	r1, [r4, #160]
	ldr	r3, [r8, #136]
	cmp	r3, r9
	moveq	r3, #108
	movne	r3, #104
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r4, #164]
	ldr	r3, [r8, #136]
	cmp	r3, r9
	moveq	r3, #116
	movne	r3, #112
	add	r3, r8, r3
	ldr	r3, [r3, #8]
	str	r3, [r4, #168]
	ldr	r2, [r8, #128]
	ldr	r3, [r8, #132]
	bfi	r9, r2, #16, #16
	bfi	r9, r3, #0, #16
	str	r9, [r4, #172]
	ldr	r3, [r8, #136]
	cmp	r3, #0
	moveq	r3, #148
	movne	r3, #144
	add	r3, r8, r3
	ldr	r3, [r3, #4]
	str	r3, [r4, #176]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #148]
	str	r3, [r4, #208]
	ldr	r3, [r8, #136]
	add	r3, r8, r3, lsl #2
	ldr	r3, [r3, #140]
	str	r3, [r4, #216]
	ldr	r3, [r8, #136]
	cmp	r3, #0
	moveq	r3, #140
	movne	r3, #136
	add	r3, r8, r3
	ldr	r3, [r3, #4]
	str	r3, [r4, #220]
	ldr	r3, [r8, #200]
	str	r3, [r4, #224]
	ldr	r3, [r8, #332]
	str	r3, [r4, #228]
	ldr	r3, [r8, #328]
	str	r3, [r4, #232]
	add	r3, r10, #8192
	ldr	r1, [r3, #1420]
	bl	CfgStrFmt.isra.6
	ldr	r1, [fp, #-48]
	ldrb	r3, [r1, #520]
	ldrb	r0, [r1, #516]
	ldrb	r7, [r1, #512]
	ldrb	lr, [r1, #508]
	mov	ip, r3
	ldrb	r6, [r1, #504]
	orr	r2, r0, ip
	orr	r2, r7, r2
	ldrb	r9, [r1, #500]
	orr	r2, lr, r2
	mov	r3, #0
	str	r6, [fp, #-52]
	orr	r2, r6, r2
	ldrb	r6, [r1, #496]
	orr	r2, r9, r2
	ldrb	r1, [r1, #492]
	orr	r2, r6, r2
	str	r3, [fp, #-72]
	str	r6, [fp, #-64]
	orr	r2, r1, r2
	ldr	r6, [fp, #-48]
	bfi	r3, r2, #24, #1
	str	r1, [fp, #-68]
	ldr	r1, [r6, #744]
	ldr	r2, [r6, #740]
	bfi	r3, r1, #23, #1
	ldr	r1, [r6, #736]
	bfi	r3, r2, #22, #1
	ldr	r2, [r6, #732]
	bfi	r3, r1, #21, #1
	ldr	r1, [r6, #728]
	bfi	r3, r2, #20, #1
	ldr	r2, [r6, #724]
	bfi	r3, r1, #19, #1
	ldr	r1, [r6, #720]
	bfi	r3, r2, #18, #1
	ldr	r2, [r6, #716]
	bfi	r3, r1, #17, #1
	ldr	r1, [r6, #552]
	bfi	r3, r2, #16, #1
	ldr	r2, [r6, #548]
	bfi	r3, r1, #15, #1
	ldr	r1, [r6, #544]
	bfi	r3, r2, #14, #1
	ldr	r2, [r6, #540]
	bfi	r3, r1, #13, #1
	ldr	r1, [r6, #536]
	bfi	r3, r2, #12, #1
	ldr	r2, [r6, #532]
	bfi	r3, r1, #11, #1
	ldr	r1, [r6, #528]
	bfi	r3, r2, #10, #1
	ldr	r2, [r6, #524]
	bfi	r3, r1, #9, #1
	bfi	r3, r2, #8, #1
	mov	r2, #0
	bfi	r3, ip, #7, #1
	ldr	ip, [fp, #-52]
	bfi	r3, r0, #6, #1
	mov	r1, r2
	bfi	r3, r7, #5, #1
	mov	r6, r2
	bfi	r3, lr, #4, #1
	mov	r0, r2
	bfi	r3, ip, #3, #1
	ldr	ip, [fp, #-64]
	bfi	r3, r9, #2, #1
	mov	r7, r2
	bfi	r3, ip, #1, #1
	ldr	ip, [fp, #-68]
	mov	r9, r2
	mov	lr, r2
	bfi	r3, ip, #0, #1
	str	r3, [r4, #256]
	ldr	ip, [fp, #-48]
	str	r2, [fp, #-68]
	str	lr, [fp, #-76]
	ldr	r3, [ip, #568]
	ldr	ip, [fp, #-48]
	bfi	r1, r3, #24, #7
	str	r9, [fp, #-80]
	ldr	r3, [ip, #564]
	bfi	r1, r3, #16, #7
	ldr	r3, [ip, #556]
	ldr	ip, [ip, #560]
	bfi	r1, ip, #8, #7
	mov	ip, r1
	ldr	r1, [fp, #-48]
	bfi	ip, r3, #0, #7
	str	ip, [r4, #260]
	ldr	r3, [r1, #584]
	ldr	ip, [r1, #580]
	bfi	r2, r3, #24, #7
	ldr	r3, [r1, #572]
	bfi	r2, ip, #16, #7
	ldr	ip, [r1, #576]
	bfi	r2, ip, #8, #7
	mov	ip, r6
	bfi	r2, r3, #0, #7
	str	r2, [r4, #264]
	ldr	r2, [r1, #620]
	ldr	r3, [r1, #588]
	bfi	r6, r2, #16, #10
	bfi	r6, r3, #0, #10
	str	r6, [r4, #268]
	ldr	r6, [r1, #624]
	mov	r3, r0
	ldr	r2, [r1, #592]
	bfi	r0, r6, #16, #10
	bfi	r0, r2, #0, #10
	str	r0, [r4, #272]
	ldr	r6, [r1, #628]
	mov	r0, r7
	ldr	r2, [r1, #596]
	bfi	r7, r6, #16, #10
	mov	r6, r1
	bfi	r7, r2, #0, #10
	str	r7, [r4, #276]
	ldr	r7, [r1, #632]
	ldr	r2, [r1, #600]
	bfi	lr, r7, #16, #10
	mov	r7, r9
	bfi	lr, r2, #0, #10
	str	lr, [r4, #280]
	ldr	lr, [r1, #636]
	ldr	r2, [r1, #604]
	mov	r1, r9
	bfi	r1, lr, #16, #10
	mov	lr, ip
	bfi	r1, r2, #0, #10
	str	r1, [r4, #284]
	ldr	r1, [r6, #640]
	ldr	r2, [r6, #608]
	bfi	r9, r1, #16, #10
	bfi	r9, r2, #0, #10
	str	r9, [r4, #288]
	ldr	r1, [r6, #644]
	mov	r9, r6
	ldr	r2, [r6, #612]
	bfi	lr, r1, #16, #10
	mov	r1, ip
	bfi	lr, r2, #0, #10
	str	lr, [r4, #292]
	ldr	lr, [r6, #648]
	ldr	r2, [r6, #616]
	mov	r6, ip
	bfi	r6, lr, #16, #10
	bfi	r6, r2, #0, #10
	str	r6, [r4, #296]
	mov	r6, r9
	ldr	r9, [r9, #684]
	ldr	lr, [r6, #652]
	mov	r6, ip
	bfi	r6, r9, #16, #9
	mov	r2, ip
	bfi	r6, lr, #0, #9
	str	r6, [r4, #300]
	ldr	r6, [fp, #-48]
	mov	lr, ip
	ldr	r9, [r6, #656]
	ldr	r6, [r6, #688]
	bfi	ip, r6, #16, #9
	ldr	r6, [fp, #-48]
	bfi	ip, r9, #0, #9
	str	ip, [r4, #304]
	mov	r9, r3
	ldr	ip, [r6, #660]
	ldr	r6, [r6, #692]
	bfi	r3, r6, #16, #9
	ldr	r6, [fp, #-48]
	bfi	r3, ip, #0, #9
	str	r3, [r4, #308]
	mov	r3, r0
	ldr	ip, [r6, #664]
	ldr	r6, [r6, #696]
	bfi	r0, r6, #16, #9
	mov	r6, r7
	bfi	r0, ip, #0, #9
	ldr	ip, [fp, #-48]
	str	r0, [r4, #312]
	ldr	r0, [ip, #668]
	ldr	ip, [ip, #700]
	bfi	r6, ip, #16, #9
	ldr	ip, [fp, #-48]
	bfi	r6, r0, #0, #9
	str	r6, [r4, #316]
	mov	r6, r7
	ldr	r0, [ip, #672]
	ldr	ip, [ip, #704]
	bfi	r6, ip, #16, #9
	bfi	r6, r0, #0, #9
	str	r6, [r4, #320]
	ldr	r6, [fp, #-48]
	mov	r0, r7
	ldr	ip, [r6, #708]
	bfi	r7, ip, #16, #9
	ldr	ip, [r6, #676]
	mov	r6, r1
	bfi	r7, ip, #0, #9
	str	r7, [r4, #324]
	ldr	ip, [fp, #-48]
	mov	r7, r1
	ldr	ip, [ip, #712]
	bfi	r6, ip, #16, #9
	ldr	ip, [fp, #-48]
	ldr	ip, [ip, #680]
	bfi	r6, ip, #0, #9
	str	r6, [r4, #328]
	ldr	ip, [r10, #700]
	mov	r6, r1
	bfi	r1, ip, #16, #5
	ldr	ip, [r5, #2488]
	bfi	r1, ip, #0, #8
	ldr	ip, [r5, #2864]
	bfi	r1, ip, #24, #4
	str	r1, [r4, #332]
	ldr	ip, [r5, #3128]
	mov	r1, r2
	bfi	r2, ip, #0, #3
	ldr	ip, [r5, #3132]
	bfi	r2, ip, #3, #7
	ldr	ip, [r5, #3136]
	bfi	r2, ip, #10, #3
	ldr	ip, [r5, #3144]
	bfi	r2, ip, #18, #4
	ldr	ip, [r5, #3152]
	bfi	r2, ip, #26, #4
	str	r2, [r4, #336]
	ldr	r2, [r5, #2960]
	ldr	ip, [r5, #2976]
	bfi	lr, r2, #0, #1
	ldr	r2, [r5, #2964]
	bfi	lr, r2, #1, #3
	ldr	r2, [r5, #2980]
	bfi	lr, ip, #15, #6
	mov	ip, r0
	bfi	lr, r2, #21, #5
	str	lr, [r4, #340]
	ldr	r2, [r5, #2500]
	ldr	lr, [r10, #704]
	bfi	r9, r2, #16, #5
	ldr	r2, [r5, #2872]
	bfi	r9, lr, #0, #8
	bfi	r9, r2, #24, #4
	str	r9, [r4, #344]
	ldr	lr, [r5, #3156]
	mov	r2, r3
	ldr	r9, [r5, #3160]
	bfi	r3, lr, #0, #3
	ldr	lr, [r5, #3164]
	bfi	r3, r9, #3, #7
	ldr	r9, [r5, #3172]
	bfi	r3, lr, #10, #3
	ldr	lr, [r5, #3180]
	bfi	r3, r9, #18, #4
	mov	r9, r0
	bfi	r3, lr, #26, #4
	str	r3, [r4, #348]
	ldr	r3, [r5, #2984]
	ldr	lr, [r5, #2988]
	bfi	ip, r3, #0, #1
	mov	r3, ip
	bfi	r3, lr, #1, #3
	mov	lr, r3
	ldr	r3, [r5, #3004]
	ldr	ip, [r5, #3000]
	bfi	lr, ip, #15, #6
	bfi	lr, r3, #21, #5
	str	lr, [r4, #352]
	ldr	r3, [r10, #716]
	mov	lr, r0
	ldr	ip, [r10, #720]
	bfi	lr, r3, #16, #5
	ldr	r3, [r5, #2888]
	bfi	lr, ip, #0, #8
	bfi	lr, r3, #24, #4
	str	lr, [r4, #356]
	ldr	ip, [r5, #3208]
	mov	r3, r0
	ldr	lr, [r5, #3212]
	bfi	r0, ip, #0, #3
	ldr	ip, [r5, #3216]
	bfi	r0, lr, #3, #7
	ldr	lr, [r5, #3224]
	bfi	r0, ip, #10, #3
	ldr	ip, [r5, #3232]
	bfi	r0, lr, #18, #4
	bfi	r0, ip, #26, #4
	str	r0, [r4, #360]
	ldr	r0, [r5, #3032]
	ldr	ip, [r5, #3036]
	ldr	lr, [r5, #3048]
	bfi	r7, r0, #0, #1
	bfi	r7, ip, #1, #3
	ldr	r0, [r5, #3052]
	bfi	r7, lr, #15, #6
	mov	lr, r6
	bfi	r7, r0, #21, #5
	str	r7, [r4, #364]
	ldr	r0, [r10, #752]
	mov	r7, r6
	ldr	ip, [r10, #756]
	bfi	lr, r0, #0, #8
	ldr	r0, [r5, #2896]
	bfi	lr, ip, #16, #5
	bfi	lr, r0, #24, #4
	str	lr, [r4, #368]
	ldr	r0, [r5, #2780]
	mov	lr, r2
	ldr	ip, [r5, #2784]
	bfi	r1, r0, #0, #3
	ldr	r0, [r5, #2788]
	bfi	r1, ip, #3, #7
	ldr	ip, [r5, #2796]
	bfi	r1, r0, #10, #3
	ldr	r0, [r5, #2804]
	bfi	r1, ip, #18, #4
	bfi	r1, r0, #26, #4
	str	r1, [r4, #372]
	ldr	r1, [r5, #3056]
	ldr	r0, [r5, #3060]
	ldr	ip, [r5, #3072]
	bfi	r6, r1, #0, #1
	bfi	r6, r0, #1, #3
	ldr	r1, [r5, #3076]
	bfi	r6, ip, #15, #6
	mov	ip, r2
	bfi	r6, r1, #21, #5
	str	r6, [r4, #376]
	ldr	r1, [r10, #708]
	mov	r6, r3
	ldr	r0, [r10, #712]
	bfi	ip, r1, #16, #5
	ldr	r1, [r5, #2880]
	bfi	ip, r0, #0, #8
	bfi	ip, r1, #24, #4
	str	ip, [r4, #380]
	ldr	r1, [r10, #760]
	mov	ip, r2
	ldr	r0, [r5, #3184]
	bfi	r2, r1, #0, #3
	ldr	r1, [r5, #3188]
	bfi	r2, r0, #3, #7
	ldr	r0, [r5, #3196]
	bfi	r2, r1, #10, #3
	ldr	r1, [r5, #3204]
	bfi	r2, r0, #18, #4
	mov	r0, r9
	bfi	r2, r1, #26, #4
	str	r2, [r4, #384]
	ldr	r2, [r5, #3008]
	ldr	r1, [r5, #3012]
	bfi	r9, r2, #0, #1
	ldr	r2, [r5, #3028]
	bfi	r9, r1, #1, #3
	ldr	r1, [r5, #3024]
	bfi	r9, r1, #15, #6
	mov	r1, r3
	bfi	r9, r2, #21, #5
	str	r9, [r4, #388]
	ldr	r2, [r5, #2936]
	ldr	r9, [r5, #2940]
	bfi	r6, r2, #0, #8
	ldr	r2, [r5, #2904]
	bfi	r6, r9, #16, #5
	bfi	r6, r2, #24, #4
	str	r6, [r4, #392]
	ldr	r6, [r5, #2808]
	mov	r2, r3
	ldr	r9, [r5, #2812]
	bfi	r3, r6, #0, #3
	ldr	r6, [r5, #2816]
	bfi	r3, r9, #3, #7
	ldr	r9, [r5, #2824]
	bfi	r3, r6, #10, #3
	mov	r6, r7
	bfi	r3, r9, #18, #4
	ldr	r9, [r5, #2832]
	bfi	r3, r9, #26, #4
	str	r3, [r4, #396]
	ldr	r9, [r5, #3084]
	mov	r3, r7
	str	r9, [fp, #-64]
	ldr	r9, [r5, #3080]
	bfi	r6, r9, #0, #1
	ldr	r9, [fp, #-64]
	bfi	r6, r9, #1, #3
	ldr	r9, [r5, #3100]
	str	r9, [fp, #-64]
	ldr	r9, [r5, #3096]
	bfi	r6, r9, #15, #6
	ldr	r9, [fp, #-64]
	bfi	r6, r9, #21, #5
	str	r6, [r4, #400]
	str	r7, [fp, #-64]
	mov	r6, r7
	ldr	r9, [r5, #2952]
	bfi	r6, r9, #0, #8
	ldr	r9, [r5, #2956]
	bfi	r6, r9, #16, #5
	ldr	r9, [r5, #2912]
	bfi	r6, r9, #24, #4
	str	r6, [r4, #404]
	ldr	r9, [r5, #2836]
	bfi	r7, r9, #0, #3
	ldr	r9, [r5, #2840]
	bfi	r7, r9, #3, #7
	ldr	r9, [r5, #2844]
	bfi	r7, r9, #10, #3
	ldr	r9, [r5, #2852]
	bfi	r7, r9, #18, #4
	ldr	r9, [r5, #2860]
	bfi	r7, r9, #26, #4
	str	r7, [r4, #408]
	ldr	r7, [r5, #3104]
	mov	r9, lr
	bfi	r9, r7, #0, #1
	mov	r7, r9
	ldr	r9, [r5, #3108]
	bfi	r7, r9, #1, #3
	mov	r9, r7
	ldr	r7, [r5, #3124]
	mov	r6, r7
	ldr	r7, [r5, #3120]
	bfi	r9, r7, #15, #6
	mov	r7, lr
	bfi	r9, r6, #21, #5
	str	r9, [r4, #412]
	ldr	r9, [r5, #2532]
	bfi	lr, r9, #0, #4
	ldr	r9, [r5, #2528]
	bfi	lr, r9, #4, #4
	ldr	r9, [r5, #2524]
	bfi	lr, r9, #8, #4
	ldr	r9, [r5, #2544]
	bfi	lr, r9, #16, #4
	ldr	r9, [r5, #2540]
	bfi	lr, r9, #20, #4
	ldr	r9, [r10, #724]
	bfi	lr, r9, #24, #4
	str	lr, [r4, #416]
	ldr	lr, [r5, #2612]
	ldr	r9, [r5, #2608]
	bfi	ip, lr, #0, #4
	ldr	lr, [r10, #736]
	bfi	ip, r9, #4, #4
	ldr	r9, [r5, #2624]
	bfi	ip, lr, #8, #4
	ldr	lr, [r5, #2628]
	bfi	ip, lr, #16, #4
	ldr	lr, [r5, #2620]
	bfi	ip, r9, #20, #4
	bfi	ip, lr, #24, #4
	str	ip, [r4, #420]
	ldr	ip, [r5, #2696]
	mov	lr, r0
	ldr	r9, [r5, #2692]
	bfi	r0, ip, #0, #4
	ldr	ip, [r10, #748]
	bfi	r0, r9, #4, #4
	bfi	r0, ip, #8, #4
	ldr	ip, [r5, #2712]
	bfi	r0, ip, #16, #4
	ldr	ip, [r5, #2704]
	ldr	r9, [r5, #2708]
	bfi	r0, r9, #20, #4
	bfi	r0, ip, #24, #4
	str	r0, [r4, #424]
	ldr	r0, [r5, #2552]
	mov	ip, r1
	ldr	r9, [r5, #2556]
	bfi	r1, r0, #8, #4
	ldr	r0, [r5, #2560]
	bfi	r1, r9, #4, #4
	ldr	r9, [r10, #728]
	bfi	r1, r0, #0, #4
	ldr	r0, [r5, #2568]
	bfi	r1, r0, #24, #4
	ldr	r0, [r5, #2572]
	bfi	r1, r9, #20, #4
	bfi	r1, r0, #16, #4
	str	r1, [r4, #428]
	ldr	r1, [r5, #2636]
	mov	r0, r2
	ldr	r9, [r10, #740]
	bfi	r2, r1, #8, #4
	ldr	r1, [r5, #2640]
	bfi	r2, r9, #4, #4
	ldr	r9, [r5, #2652]
	bfi	r2, r1, #0, #4
	ldr	r1, [r5, #2648]
	bfi	r2, r1, #24, #4
	ldr	r1, [r5, #2656]
	bfi	r2, r9, #20, #4
	bfi	r2, r1, #16, #4
	str	r2, [r4, #432]
	ldr	r2, [r5, #2720]
	mov	r1, r3
	ldr	r9, [r5, #2724]
	bfi	r3, r2, #8, #4
	ldr	r2, [r5, #2728]
	bfi	r3, r9, #4, #4
	ldr	r9, [r5, #2740]
	bfi	r3, r2, #0, #4
	ldr	r2, [r5, #2736]
	bfi	r3, r2, #24, #4
	ldr	r2, [r5, #2744]
	bfi	r3, r9, #20, #4
	mov	r9, r7
	bfi	r3, r2, #16, #4
	str	r3, [r4, #436]
	ldr	r3, [r5, #2580]
	mov	r2, r7
	bfi	r9, r3, #8, #4
	ldr	r3, [r5, #2588]
	mov	r6, r9
	ldr	r9, [r5, #2584]
	bfi	r6, r9, #4, #4
	mov	r9, r6
	bfi	r9, r3, #0, #4
	ldr	r3, [r5, #2596]
	bfi	r9, r3, #24, #4
	ldr	r3, [r5, #2600]
	mov	r6, r9
	ldr	r9, [r10, #732]
	bfi	r6, r9, #20, #4
	mov	r9, r6
	bfi	r9, r3, #16, #4
	str	r9, [r4, #440]
	mov	r6, r7
	ldr	r3, [r5, #2664]
	ldr	r9, [r10, #744]
	bfi	r6, r3, #8, #4
	ldr	r3, [r5, #2668]
	bfi	r6, r9, #4, #4
	ldr	r9, [r5, #2676]
	bfi	r6, r3, #0, #4
	ldr	r3, [r5, #2684]
	bfi	r6, r9, #24, #4
	ldr	r9, [r5, #2680]
	bfi	r6, r9, #20, #4
	bfi	r6, r3, #16, #4
	str	r6, [r4, #444]
	ldr	r3, [r5, #2752]
	mov	r6, r7
	ldr	r9, [r5, #2756]
	bfi	r6, r3, #8, #4
	ldr	r3, [r5, #2760]
	bfi	r6, r9, #4, #4
	ldr	r9, [r5, #2768]
	bfi	r6, r3, #0, #4
	ldr	r3, [r5, #2776]
	bfi	r6, r9, #24, #4
	ldr	r9, [r5, #2772]
	bfi	r6, r9, #20, #4
	bfi	r6, r3, #16, #4
	str	r6, [r4, #448]
	ldr	r3, [r5, #3236]
	mov	r6, lr
	ldr	r9, [r5, #3240]
	bfi	r7, r3, #0, #4
	ldr	r3, [r5, #3244]
	bfi	r7, r9, #4, #4
	ldr	r9, [r5, #3252]
	bfi	r7, r3, #8, #4
	ldr	r3, [r5, #3248]
	bfi	r7, r3, #12, #4
	ldr	r3, [r5, #3256]
	bfi	r7, r9, #16, #4
	bfi	r7, r3, #20, #4
	str	r7, [r4, #452]
	ldr	r3, [r10, #764]
	ldr	r9, [r10, #768]
	bfi	r6, r3, #0, #12
	ldr	r3, [r5, #3260]
	bfi	r6, r9, #12, #12
	mov	r9, lr
	bfi	r6, r3, #24, #8
	str	r6, [r4, #456]
	ldr	r3, [r5, #3264]
	ldr	r7, [r5, #3268]
	bfi	lr, r3, #0, #12
	ldr	r3, [r5, #3272]
	bfi	lr, r7, #12, #12
	bfi	lr, r3, #24, #8
	str	lr, [r4, #460]
	ldr	r3, [r10, #772]
	mov	lr, ip
	ldr	r7, [r5, #3276]
	bfi	ip, r3, #0, #12
	ldr	r3, [r5, #3280]
	bfi	ip, r7, #12, #12
	bfi	ip, r3, #24, #8
	str	ip, [r4, #464]
	ldr	r3, [r5, #3284]
	ldr	r7, [r5, #3288]
	bfi	r0, r3, #0, #8
	ldr	r3, [r5, #3292]
	ldr	r6, [fp, #-48]
	bfi	r0, r7, #8, #8
	bfi	r0, r3, #16, #8
	str	r0, [r4, #468]
	mov	r3, r1
	ldr	ip, [r8, #40]
	ldr	r0, [r6, #1464]
	ldr	r7, [r6, #1468]
	bfi	r1, r0, #14, #1
	ldr	r0, [r5, #2360]
	bfi	r1, r7, #15, #1
	bfi	r1, ip, #28, #1
	bfi	r1, r0, #20, #8
	str	r1, [r4, #480]
	ldr	r1, [r6, #1484]
	mov	r0, r2
	ldr	r7, [r6, #1480]
	ldr	ip, [r6, #1476]
	bfi	r2, r1, #0, #8
	bfi	r2, r7, #8, #8
	ldr	r1, [r6, #1472]
	bfi	r2, ip, #16, #8
	mov	r6, r9
	bfi	r2, r1, #24, #8
	str	r2, [r4, #484]
	ldr	r2, [r5, #3752]
	mov	r7, r9
	mov	ip, r9
	mov	r1, r9
	bfi	r6, r2, #0, #1
	str	r6, [r4, #488]
	ldr	r2, [r5, #3756]
	mov	r6, r9
	bfi	r7, r2, #0, #16
	str	r7, [r4, #492]
	ldr	r2, [r5, #3760]
	mov	r7, r9
	bfi	r7, r2, #0, #16
	str	r7, [r4, #496]
	ldr	r7, [r5, #3764]
	mov	r2, r9
	bfi	ip, r7, #0, #16
	str	ip, [r4, #500]
	ldr	ip, [r5, #3812]
	ldr	r7, [r5, #3816]
	bfi	r9, ip, #16, #1
	bfi	r9, r7, #0, #16
	str	r9, [r4, #504]
	ldr	ip, [r5, #3768]
	mov	r7, r3
	ldr	r9, [r5, #3772]
	bfi	lr, ip, #18, #9
	ldr	ip, [r5, #3776]
	bfi	lr, r9, #9, #9
	bfi	lr, ip, #0, #9
	str	lr, [r4, #508]
	ldr	ip, [r5, #3780]
	mov	lr, r3
	ldr	r9, [r5, #3784]
	bfi	r7, ip, #16, #8
	mov	ip, r7
	bfi	ip, r9, #8, #8
	mov	r7, ip
	ldr	ip, [r5, #3788]
	mov	r9, r7
	bfi	r9, ip, #0, #8
	str	r9, [r4, #512]
	ldr	ip, [r5, #3792]
	ldr	r9, [r5, #3796]
	bfi	r3, ip, #8, #4
	ldr	ip, [r5, #3800]
	bfi	r3, r9, #4, #4
	ldr	r9, [r5, #3808]
	bfi	r3, ip, #0, #4
	ldr	ip, [r5, #3804]
	bfi	r3, r9, #12, #8
	ldr	r9, [fp, #-48]
	bfi	r3, ip, #20, #8
	str	r3, [r4, #516]
	ldr	r3, [r9, #416]
	ldr	ip, [r9, #412]
	bfi	r0, r3, #0, #8
	mov	r3, r9
	ldr	r9, [r9, #408]
	mov	r7, r3
	bfi	r0, ip, #8, #8
	ldr	r3, [r3, #404]
	bfi	r0, r9, #16, #8
	bfi	r0, r3, #24, #8
	str	r0, [r4, #524]
	ldr	r3, [r5, #3820]
	mov	r0, r1
	ldr	ip, [r5, #3824]
	ldr	r9, [r5, #3828]
	bfi	r1, r3, #24, #8
	bfi	r1, ip, #16, #8
	ldr	r3, [r5, #3832]
	bfi	r1, r9, #8, #8
	mov	ip, r6
	bfi	r1, r3, #0, #8
	str	r1, [r4, #528]
	ldr	r1, [r5, #3884]
	mov	r9, r2
	ldr	r3, [r7, #444]
	bfi	r6, r1, #0, #8
	bfi	r6, r3, #17, #1
	str	r6, [r4, #532]
	ldr	r1, [r5, #3896]
	mov	r6, r2
	ldr	r3, [r5, #3900]
	bfi	r6, r1, #0, #16
	bfi	r6, r3, #16, #16
	str	r6, [r4, #536]
	ldr	r3, [r10, #1184]
	ldr	r1, [r10, #1188]
	ldr	r6, [r10, #1192]
	bfi	r2, r3, #22, #9
	bfi	r2, r1, #17, #5
	ldr	r3, [r10, #1212]
	bfi	r2, r6, #9, #8
	mov	r1, lr
	bfi	r2, r3, #0, #9
	str	r2, [r4, #540]
	ldr	r2, [r10, #1208]
	mov	r6, lr
	ldr	r3, [r7, #328]
	bfi	r1, r2, #8, #14
	bfi	r1, r3, #0, #8
	str	r1, [r4, #544]
	ldr	r3, [r10, #1196]
	mov	r1, lr
	ldr	r2, [r10, #1200]
	bfi	r1, r3, #16, #8
	ldr	r3, [r10, #1204]
	bfi	r1, r2, #8, #8
	mov	r2, r1
	bfi	r2, r3, #0, #8
	str	r2, [r4, #548]
	ldr	r3, [r7, #336]
	ldr	r2, [r7, #340]
	ldr	r1, [r7, #348]
	bfi	lr, r3, #18, #1
	bfi	lr, r2, #12, #2
	ldr	r3, [r7, #352]
	bfi	lr, r1, #4, #4
	bfi	lr, r3, #0, #4
	str	lr, [r4, #552]
	ldr	r1, [r7, #356]
	mov	lr, r0
	ldr	r2, [r7, #360]
	mov	r3, r0
	bfi	lr, r1, #0, #10
	bfi	lr, r2, #16, #9
	str	lr, [r4, #556]
	ldr	r1, [r7, #364]
	mov	lr, r0
	ldr	r2, [r7, #368]
	bfi	lr, r1, #0, #10
	bfi	lr, r2, #16, #9
	str	lr, [r4, #560]
	ldr	r1, [r7, #372]
	mov	lr, r0
	ldr	r2, [r7, #376]
	bfi	r0, r1, #0, #10
	bfi	r0, r2, #16, #9
	str	r0, [r4, #564]
	ldr	r1, [r7, #380]
	mov	r0, ip
	ldr	r2, [r7, #384]
	bfi	ip, r1, #0, #10
	mov	r1, r9
	bfi	ip, r2, #16, #9
	str	ip, [r4, #568]
	ldr	r2, [r7, #388]
	mov	ip, r9
	bfi	ip, r2, #0, #16
	str	ip, [r4, #572]
	mov	ip, r7
	str	ip, [fp, #-48]
	ldr	ip, [ip, #420]
	mov	r2, r9
	ldr	r7, [r7, #424]
	bfi	r9, ip, #0, #13
	mov	ip, r6
	bfi	r9, r7, #13, #1
	ldr	r7, [fp, #-48]
	str	r9, [r4, #576]
	ldr	r9, [r7, #428]
	bfi	r6, r9, #0, #18
	str	r6, [r4, #580]
	ldr	r9, [r7, #432]
	mov	r6, r3
	bfi	r6, r9, #0, #18
	str	r6, [r4, #584]
	ldr	r9, [r7, #456]
	mov	r6, r3
	bfi	r6, r9, #16, #7
	ldr	r9, [r7, #460]
	bfi	r6, r9, #23, #7
	str	r6, [r4, #588]
	ldr	r6, [r7, #440]
	ldr	r9, [r7, #464]
	bfi	r3, r6, #12, #8
	bfi	r3, r9, #8, #4
	ldr	r9, [r7, #472]
	ldr	r6, [r7, #468]
	bfi	r3, r6, #0, #8
	ldr	r6, [r7, #476]
	bfi	r3, r9, #20, #8
	bfi	r3, r6, #28, #4
	str	r3, [r4, #592]
	ldr	r3, [r7, #448]
	mov	r6, r7
	ldr	r9, [r7, #452]
	mov	r7, lr
	bfi	r7, r3, #0, #8
	ldr	r3, [r6, #436]
	bfi	r7, r9, #8, #8
	bfi	r7, r3, #16, #8
	str	r7, [r4, #596]
	ldr	r3, [r6, #480]
	str	r7, [fp, #-52]
	ldr	r7, [r6, #484]
	bfi	lr, r3, #0, #8
	ldr	r3, [r6, #488]
	bfi	lr, r7, #8, #8
	bfi	lr, r3, #16, #16
	str	lr, [r4, #600]
	ldr	lr, [r5, #3836]
	ldr	r3, [r5, #3840]
	bfi	r0, lr, #24, #8
	ldr	lr, [r5, #3844]
	bfi	r0, r3, #16, #8
	ldr	r3, [r5, #3848]
	bfi	r0, lr, #8, #8
	bfi	r0, r3, #0, #8
	str	r0, [r4, #604]
	ldr	r0, [r5, #3852]
	ldr	r3, [r5, #3856]
	bfi	r1, r0, #24, #8
	ldr	r0, [r5, #3860]
	bfi	r1, r3, #16, #8
	ldr	r3, [r5, #3864]
	bfi	r1, r0, #8, #8
	bfi	r1, r3, #0, #8
	str	r1, [r4, #608]
	ldr	r1, [r5, #3868]
	ldr	r3, [r5, #3872]
	bfi	r2, r1, #28, #4
	ldr	r1, [r5, #3876]
	bfi	r2, r3, #23, #5
	ldr	r3, [r5, #3880]
	bfi	r2, r1, #14, #9
	bfi	r2, r3, #0, #14
	str	r2, [r4, #612]
	ldr	r3, [r8, #552]
	ldr	r2, [r6, #848]
	mov	r6, #0
	bfi	ip, r3, #8, #6
	ldr	r3, [r8, #548]
	bfi	ip, r2, #16, #1
	bfi	ip, r3, #0, #6
	str	ip, [r4, #624]
	ldr	r3, [r8, #4]
	ldr	r1, [r8, #16]
	cmp	r3, #0
	ldr	r0, [r8, #540]
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #5
	bl	__aeabi_uidiv
	ldr	r2, [r10, #792]
	mov	r3, #0
	mov	lr, r6
	mov	ip, r6
	mov	r1, r6
	bfi	r3, r0, #6, #25
	mov	r0, r6
	bfi	r3, r2, #0, #6
	str	r3, [r4, #628]
	ldr	r3, [r5, #3460]
	mov	r2, r6
	bfi	r6, r3, #0, #16
	str	r6, [r4, #632]
	ldr	r3, [r5, #3432]
	mov	r6, r0
	ldr	r7, [r5, #3408]
	ldr	r9, [r5, #3436]
	bfi	r0, r3, #8, #6
	bfi	r0, r7, #16, #4
	mov	r3, lr
	bfi	r0, r9, #0, #6
	str	r0, [r4, #636]
	ldr	r7, [r5, #3420]
	mov	r0, lr
	ldr	r9, [r5, #3400]
	bfi	lr, r7, #8, #6
	ldr	r7, [r5, #3736]
	bfi	lr, r9, #16, #4
	bfi	lr, r7, #0, #6
	str	lr, [r4, #640]
	ldr	r7, [r5, #3420]
	mov	lr, ip
	ldr	r9, [r5, #3404]
	bfi	ip, r7, #8, #6
	ldr	r7, [r5, #3724]
	bfi	ip, r9, #16, #4
	bfi	ip, r7, #0, #6
	str	ip, [r4, #644]
	ldr	r7, [r5, #3416]
	mov	ip, r1
	ldr	r9, [r5, #3396]
	bfi	r1, r7, #8, #6
	ldr	r7, [r5, #3732]
	bfi	r1, r9, #16, #4
	bfi	r1, r7, #0, #6
	str	r1, [r4, #648]
	ldr	r7, [r10, #796]
	mov	r1, r2
	ldr	r9, [r10, #776]
	bfi	r2, r7, #8, #6
	ldr	r7, [r5, #3720]
	bfi	r2, r9, #16, #4
	bfi	r2, r7, #0, #6
	str	r2, [r4, #652]
	ldr	r7, [r5, #3412]
	mov	r2, r6
	ldr	r9, [r5, #3428]
	bfi	r6, r7, #16, #4
	ldr	r7, [r5, #3728]
	bfi	r6, r9, #8, #6
	bfi	r6, r7, #0, #6
	str	r6, [r4, #656]
	ldr	r6, [r5, #3440]
	mov	r7, r3
	ldr	r9, [r5, #3448]
	bfi	r3, r6, #16, #4
	ldr	r6, [r5, #3444]
	bfi	r3, r6, #20, #4
	ldr	r6, [r5, #3740]
	bfi	r3, r9, #8, #6
	bfi	r3, r6, #0, #6
	str	r3, [r4, #660]
	ldr	r6, [r10, #812]
	mov	r3, r0
	ldr	r9, [r10, #804]
	bfi	r0, r6, #24, #8
	ldr	r6, [r10, #808]
	bfi	r0, r6, #16, #8
	ldr	r6, [r10, #800]
	bfi	r0, r9, #8, #8
	bfi	r0, r6, #0, #8
	str	r0, [r4, #664]
	ldr	r6, [r10, #828]
	mov	r0, lr
	ldr	r9, [r10, #820]
	bfi	lr, r6, #24, #8
	ldr	r6, [r10, #824]
	bfi	lr, r6, #16, #8
	ldr	r6, [r10, #816]
	bfi	lr, r9, #8, #8
	bfi	lr, r6, #0, #8
	str	lr, [r4, #668]
	ldr	lr, [r10, #844]
	mov	r6, ip
	ldr	r9, [r10, #836]
	bfi	ip, lr, #24, #8
	ldr	lr, [r10, #840]
	bfi	ip, lr, #16, #8
	ldr	lr, [r10, #832]
	bfi	ip, r9, #8, #8
	bfi	ip, lr, #0, #8
	str	ip, [r4, #672]
	ldr	ip, [r10, #860]
	mov	lr, r1
	ldr	r9, [r10, #852]
	bfi	r1, ip, #24, #8
	ldr	ip, [r10, #856]
	bfi	r1, ip, #16, #8
	ldr	ip, [r10, #848]
	bfi	r1, r9, #8, #8
	bfi	r1, ip, #0, #8
	str	r1, [r4, #676]
	ldr	r1, [r5, #3320]
	mov	ip, r2
	ldr	r9, [r5, #3324]
	bfi	r2, r1, #0, #2
	ldr	r1, [r5, #3328]
	bfi	r2, r9, #2, #2
	ldr	r9, [r5, #3332]
	bfi	r2, r1, #4, #2
	ldr	r1, [r5, #3336]
	bfi	r2, r9, #6, #2
	ldr	r9, [r5, #3340]
	bfi	r2, r1, #8, #2
	ldr	r1, [r5, #3344]
	bfi	r2, r9, #10, #2
	ldr	r9, [r5, #3348]
	bfi	r2, r1, #12, #2
	ldr	r1, [r5, #3352]
	bfi	r2, r9, #14, #2
	ldr	r9, [r5, #3356]
	bfi	r2, r1, #16, #2
	ldr	r1, [r5, #3360]
	bfi	r2, r9, #18, #2
	ldr	r9, [r5, #3364]
	bfi	r2, r1, #20, #2
	ldr	r1, [r5, #3368]
	bfi	r2, r9, #22, #2
	ldr	r9, [r5, #3376]
	bfi	r2, r1, #24, #2
	ldr	r1, [r5, #3372]
	bfi	r2, r1, #26, #2
	ldr	r1, [r5, #3380]
	bfi	r2, r9, #28, #2
	bfi	r2, r1, #30, #2
	str	r2, [r4, #680]
	ldr	r2, [r5, #3384]
	mov	r1, r7
	bfi	r7, r2, #0, #5
	str	r7, [r4, #684]
	ldr	r9, [r5, #3452]
	mov	r2, r3
	ldr	r7, [r5, #3456]
	bfi	r3, r9, #0, #4
	bfi	r3, r7, #4, #4
	str	r3, [r4, #688]
	ldr	r7, [r10, #864]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #692]
	ldr	r7, [r10, #868]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #696]
	ldr	r7, [r10, #872]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #700]
	ldr	r7, [r10, #876]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #704]
	ldr	r7, [r10, #880]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #708]
	ldr	r7, [r10, #884]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #712]
	ldr	r7, [r10, #888]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #716]
	ldr	r7, [r10, #892]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #720]
	ldr	r7, [r10, #896]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #724]
	ldr	r7, [r10, #900]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #728]
	ldr	r7, [r10, #904]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #732]
	ldr	r7, [r10, #908]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #736]
	ldr	r7, [r10, #912]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #740]
	ldr	r7, [r10, #916]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #744]
	ldr	r7, [r10, #920]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #748]
	ldr	r7, [r10, #924]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #752]
	ldr	r7, [r10, #928]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #756]
	ldr	r7, [r10, #932]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #760]
	ldr	r7, [r10, #936]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #764]
	ldr	r7, [r10, #940]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #768]
	ldr	r7, [r10, #944]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #772]
	ldr	r7, [r10, #948]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #776]
	ldr	r7, [r10, #952]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #780]
	ldr	r7, [r10, #956]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #784]
	ldr	r7, [r10, #960]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #788]
	ldr	r7, [r10, #964]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #792]
	ldr	r7, [r10, #968]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #796]
	ldr	r7, [r10, #972]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #800]
	ldr	r7, [r10, #976]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #804]
	ldr	r7, [r10, #980]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #808]
	ldr	r7, [r10, #984]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #812]
	ldr	r7, [r10, #988]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #816]
	ldr	r7, [r10, #992]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #820]
	ldr	r7, [r10, #996]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #824]
	ldr	r7, [r10, #1000]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #828]
	ldr	r7, [r10, #1004]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #832]
	ldr	r7, [r10, #1008]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #836]
	ldr	r7, [r10, #1012]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #840]
	ldr	r7, [r10, #1016]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #844]
	ldr	r7, [r10, #1020]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #848]
	ldr	r7, [r10, #1024]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #852]
	ldr	r7, [r10, #1028]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #856]
	ldr	r7, [r10, #1032]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #860]
	ldr	r7, [r10, #1036]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #864]
	ldr	r7, [r10, #1040]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #868]
	ldr	r7, [r10, #1044]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #872]
	ldr	r7, [r10, #1048]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #876]
	ldr	r7, [r10, #1052]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #880]
	ldr	r7, [r10, #1056]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #884]
	ldr	r7, [r10, #1060]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #888]
	ldr	r7, [r10, #1064]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #892]
	ldr	r7, [r10, #1068]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #896]
	ldr	r7, [r10, #1072]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #900]
	ldr	r7, [r10, #1076]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #904]
	ldr	r7, [r10, #1080]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #908]
	ldr	r7, [r10, #1084]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #912]
	ldr	r7, [r10, #1088]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #916]
	ldr	r7, [r10, #1092]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #920]
	ldr	r7, [r10, #1096]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #924]
	ldr	r7, [r10, #1100]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #928]
	ldr	r7, [r10, #1104]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #932]
	ldr	r7, [r10, #1108]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #936]
	ldr	r7, [r10, #1112]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #940]
	ldr	r7, [r10, #1116]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #944]
	ldr	r7, [r10, #1120]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #948]
	ldr	r7, [r10, #1124]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #952]
	ldr	r7, [r10, #1128]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #956]
	ldr	r7, [r10, #1132]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #960]
	ldr	r7, [r10, #1136]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #964]
	ldr	r7, [r10, #1140]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #968]
	ldr	r7, [r10, #1144]
	mov	r3, r0
	bfi	r0, r7, #0, #20
	str	r0, [r4, #972]
	ldr	r7, [r10, #1148]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #976]
	ldr	r7, [r10, #1152]
	mov	r6, lr
	bfi	lr, r7, #0, #20
	str	lr, [r4, #980]
	ldr	r7, [r10, #1156]
	mov	lr, ip
	bfi	ip, r7, #0, #20
	str	ip, [r4, #984]
	ldr	r7, [r10, #1160]
	mov	ip, r1
	bfi	r1, r7, #0, #20
	str	r1, [r4, #988]
	ldr	r7, [r10, #1164]
	mov	r1, r2
	bfi	r2, r7, #0, #20
	str	r2, [r4, #992]
	ldr	r7, [r10, #1168]
	mov	r2, r3
	bfi	r3, r7, #0, #20
	str	r3, [r4, #996]
	ldr	r7, [r10, #1172]
	add	r3, r5, #4096
	bfi	r0, r7, #0, #20
	str	r0, [r4, #1000]
	ldr	r7, [r10, #1176]
	mov	r0, r6
	bfi	r6, r7, #0, #20
	str	r6, [r4, #1004]
	ldr	r9, [r10, #1180]
	mov	r7, lr
	mov	r6, lr
	str	r2, [fp, #-48]
	bfi	lr, r9, #0, #20
	str	lr, [r4, #1008]
	ldr	r10, [r5, #3668]
	mov	lr, ip
	ldr	r9, [r5, #3672]
	bfi	ip, r10, #8, #2
	ldr	r10, [r5, #3480]
	bfi	ip, r9, #12, #1
	bfi	ip, r10, #0, #5
	str	ip, [r4, #1012]
	ldr	r10, [r5, #3476]
	mov	ip, r1
	ldr	r9, [r5, #3656]
	bfi	r1, r10, #16, #4
	ldr	r10, [r5, #3468]
	bfi	r1, r9, #12, #4
	ldr	r9, [r5, #3472]
	bfi	r1, r10, #9, #2
	ldr	r10, [r5, #3464]
	bfi	r1, r9, #8, #1
	bfi	r1, r10, #0, #6
	str	r1, [r4, #1016]
	ldr	r10, [r5, #3636]
	mov	r1, r2
	str	r10, [r4, #1020]
	mov	r10, r2
	ldr	r9, [r5, #3640]
	str	r9, [r4, #1024]
	ldr	r9, [r5, #3644]
	bfi	r2, r9, #0, #16
	ldr	r9, [r5, #3664]
	bfc	r2, #20, #1
	bfi	r2, r9, #21, #1
	ldr	r9, [r5, #3652]
	bfi	r2, r9, #18, #2
	ldr	r9, [r5, #3648]
	bfi	r2, r9, #16, #2
	str	r2, [r4, #1028]
	ldr	r2, [r3, #1608]
	mov	r9, r10
	bfi	r0, r2, #4, #2
	ldr	r2, [r3, #956]
	bfi	r0, r2, #1, #1
	ldr	r2, [r3, #1628]
	bfi	r0, r2, #2, #1
	str	r0, [r4, #1040]
	ldr	r0, [r3, #1308]
	mov	r2, r7
	bfi	r7, r0, #16, #16
	ldr	r0, [r3, #1312]
	bfi	r7, r0, #0, #16
	str	r7, [r4, #1044]
	ldr	r7, [r3, #1632]
	mov	r0, r6
	bfi	r6, r7, #6, #6
	ldr	r7, [r3, #1636]
	bfi	r6, r7, #0, #6
	str	r6, [r4, #1048]
	ldr	r7, [r3, #1292]
	mov	r6, lr
	bfi	lr, r7, #31, #1
	ldr	r7, [r3, #1296]
	bfi	lr, r7, #0, #17
	str	lr, [r4, #1052]
	ldr	r7, [r3, #1300]
	mov	lr, ip
	bfi	ip, r7, #16, #11
	ldr	r7, [r3, #1304]
	bfi	ip, r7, #0, #10
	str	ip, [r4, #1056]
	ldr	r7, [r3, #1404]
	mvn	ip, #0
	bfi	r1, r7, #3, #1
	ldr	r7, [r3, #1408]
	bfi	r1, r7, #2, #1
	ldr	r7, [r3, #1412]
	bfi	r1, r7, #1, #1
	ldr	r7, [r3, #1400]
	bfi	r1, r7, #0, #1
	str	r1, [r4, #1060]
	ldr	r1, [r3, #1416]
	mov	r7, #7
	bfi	r9, r1, #4, #1
	str	r9, [r4, #1064]
	ldr	r9, [r3, #1060]
	mov	r1, r10
	bfi	r10, r9, #0, #1
	str	r10, [r4, #1068]
	ldr	r9, [r3, #1068]
	mov	r10, r2
	bfi	r2, r9, #15, #1
	ldr	r9, [r3, #1072]
	bfi	r2, r9, #14, #1
	ldr	r9, [r3, #1076]
	bfi	r2, r9, #13, #1
	ldr	r9, [r3, #1080]
	bfi	r2, r9, #12, #1
	ldr	r9, [r3, #1084]
	bfi	r2, r9, #8, #4
	ldr	r9, [r3, #1088]
	bfi	r2, r9, #4, #4
	ldr	r9, [r3, #1092]
	bfi	r2, r9, #0, #4
	str	r2, [r4, #1072]
	ldr	r2, [r3, #1096]
	mov	r9, r0
	bfi	r0, r2, #0, #4
	str	r0, [r4, #1076]
	ldr	r2, [r3, #1108]
	mov	r0, r6
	bfi	r6, r2, #0, #8
	ldr	r2, [r3, #1104]
	bfi	r6, r2, #8, #8
	ldr	r2, [r3, #1100]
	bfi	r6, r2, #16, #8
	str	r6, [r4, #1080]
	ldr	r2, [r3, #1116]
	mov	r6, r1
	str	ip, [r4, #1088]
	bfi	lr, r2, #0, #16
	str	ip, [r4, #1092]
	str	lr, [r4, #1084]
	mov	r2, r1
	str	ip, [r4, #1100]
	mov	lr, r1
	str	r7, [r4, #1096]
	mov	ip, r1
	str	r7, [r4, #1104]
	ldr	r7, [r3, #1180]
	bfi	r1, r7, #3, #1
	ldr	r7, [r3, #1176]
	bfi	r1, r7, #2, #1
	ldr	r7, [r3, #1172]
	bfi	r1, r7, #1, #1
	orr	r1, r1, #1
	str	r1, [r4, #1108]
	ldr	r1, [r3, #1424]
	str	r1, [r4, #1112]
	movw	r1, #9729
	ldr	r7, [r3, #1428]
	str	r7, [r4, #1116]
	ldr	r7, [r3, #1432]
	str	r7, [r4, #1120]
	ldr	r7, [r3, #1436]
	str	r7, [r4, #1124]
	ldr	r7, [r3, #1440]
	str	r7, [r4, #1128]
	ldr	r7, [r3, #1444]
	str	r7, [r4, #1132]
	ldr	r7, [r3, #1396]
	bfi	r10, r7, #0, #1
	str	r10, [r4, #1136]
	ldr	r7, [r3, #1660]
	bfi	r9, r7, #0, #8
	ldr	r7, [r3, #1664]
	bfi	r9, r7, #8, #8
	str	r9, [r4, #1140]
	ldr	r9, [r5, #3296]
	mov	r7, r0
	bfi	r0, r9, #0, #16
	ldr	r9, [r5, #3300]
	bfi	r0, r9, #16, #16
	str	r0, [r4, #1144]
	ldr	r0, [r5, #3312]
	mov	r9, lr
	bfi	lr, r0, #16, #16
	str	lr, [r4, #1148]
	ldr	lr, [r5, #3304]
	mov	r0, ip
	bfi	ip, lr, #0, #16
	ldr	lr, [r5, #3308]
	bfi	ip, lr, #16, #16
	str	ip, [r4, #1152]
	ldr	lr, [r5, #3316]
	mov	ip, r6
	bfi	r6, lr, #0, #3
	str	r6, [r4, #1156]
	ldr	lr, [r3, #1364]
	ldr	r3, [r8, #536]
	bfi	r2, lr, #8, #3
	movw	lr, #513
	cmp	r3, r7
	moveq	r1, lr
	bfi	r2, r1, #16, #16
	str	r2, [r4, #1172]
	ldr	r2, [r8, #632]
	ldr	r3, [r8, #636]
	bfi	r7, r2, #0, #5
	bfi	r7, r3, #16, #16
	str	r7, [r4, #1176]
	ldr	r2, [r8, #672]
	ldr	r3, [r8, #632]
	rsb	r3, r3, #16
	mov	r3, r2, asl r3
	bfi	r9, r3, #0, #16
	str	r9, [r4, #1180]
	ldr	r2, [r5, #2464]
	ldr	r3, [r5, #2468]
	bfi	r0, r2, #0, #5
	bfi	r0, r3, #16, #16
	str	r0, [r4, #1216]
	ldr	r2, [r5, #2460]
	ldr	r3, [r5, #2464]
	rsb	r3, r3, #16
	mov	r3, r2, asl r3
	bfi	ip, r3, #0, #16
	str	ip, [r4, #1220]
	ldr	r2, [r8, #4]
	ldr	r3, [r8, #688]
	cmp	r2, #2
	bne	.L92
	ldr	r2, [r8, #636]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r8, #640]
	ldrhi	r2, [r8, #640]
	movls	r2, r1, asl r2
	str	r2, [r3, #1184]
	ldr	r2, [r8, #636]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r8, #644]
	ldrls	r1, [r8, #644]
	movls	r2, r1, asl r2
	str	r2, [r3, #1188]
	ldr	r2, [r8, #636]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r8, #648]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #1192]
	ldr	r2, [r8, #652]
	str	r2, [r3, #1196]
	ldr	r2, [r8, #656]
	str	r2, [r3, #1200]
	ldr	r2, [r8, #660]
	str	r2, [r3, #1204]
	ldr	r2, [r8, #664]
	str	r2, [r3, #1208]
	ldr	r2, [r8, #668]
	str	r2, [r3, #1212]
	ldr	r2, [r8, #4]
.L92:
	cmp	r2, #0
	beq	.L158
.L98:
	add	r2, r5, #4096
	mov	r3, #0
	ldr	r2, [r2, #1392]
	bfi	r3, r2, #1, #24
	bfc	r3, #0, #1
	str	r3, [r4, #1292]
	ldr	r2, [r8, #4]
	ldr	r3, [r8, #688]
	cmp	r2, #2
	bne	.L99
	ldr	r2, [r5, #2468]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r5, #2428]
	ldrhi	r2, [r5, #2428]
	movls	r2, r1, asl r2
	str	r2, [r3, #1224]
	ldr	r2, [r5, #2468]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r5, #2432]
	ldrls	r1, [r5, #2432]
	movls	r2, r1, asl r2
	str	r2, [r3, #1228]
	ldr	r2, [r5, #2468]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r5, #2436]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #1232]
	ldr	r2, [r5, #2440]
	str	r2, [r3, #1236]
	ldr	r2, [r5, #2444]
	str	r2, [r3, #1240]
	ldr	r2, [r5, #2448]
	str	r2, [r3, #1244]
	ldr	r2, [r5, #2452]
	str	r2, [r3, #1248]
	ldr	r2, [r5, #2456]
	str	r2, [r3, #1252]
	ldr	r2, [r8, #4]
.L99:
	cmp	r2, #0
	beq	.L159
.L105:
	ldr	r1, [r8, #48]
	add	r3, r5, #4096
	mov	r2, #0
	bfi	r2, r1, #0, #1
	str	r2, [r4, #1332]
	ldr	r3, [r3, #1772]
	str	r3, [r4, #1336]
	ldr	r3, [r8, #52]
	cmp	r3, #0
	moveq	r2, #0
	bfieq	r2, r3, #16, #1
	movne	r2, #65536
	orr	r2, r2, #256
	tst	r2, #65536
	beq	.L108
	ldr	r1, [r8, #344]
	ldr	r3, [r8, #340]
	str	r1, [r4, #1476]
	bfi	r2, r3, #0, #8
	ldr	r3, [r8, #348]
	str	r3, [r4, #1480]
	ldr	r3, [r8, #352]
	str	r3, [r4, #1484]
	ldr	r3, [r8, #356]
	str	r3, [r4, #1488]
	ldr	r3, [r8, #360]
	str	r3, [r4, #1492]
	ldr	r3, [r8, #364]
	str	r3, [r4, #1496]
	ldr	r3, [r8, #368]
	str	r3, [r4, #1500]
	ldr	r3, [r8, #372]
	str	r3, [r4, #1504]
	ldr	r3, [r8, #376]
	str	r3, [r4, #1508]
	ldr	r3, [r8, #380]
	str	r3, [r4, #1512]
	ldr	r3, [r8, #384]
	str	r3, [r4, #1516]
	ldr	r3, [r8, #388]
	str	r3, [r4, #1520]
	ldr	r3, [r8, #392]
	str	r3, [r4, #1524]
	ldr	r3, [r8, #396]
	str	r3, [r4, #1528]
	ldr	r3, [r8, #400]
	str	r3, [r4, #1532]
	ldr	r3, [r8, #404]
	str	r3, [r4, #1536]
	ldr	r3, [r8, #408]
	str	r3, [r4, #1540]
	ldr	r3, [r8, #412]
	str	r3, [r4, #1544]
	ldr	r3, [r8, #416]
	str	r3, [r4, #1548]
	ldr	r3, [r8, #420]
	str	r3, [r4, #1552]
	ldr	r3, [r8, #424]
	str	r3, [r4, #1556]
	ldr	r3, [r8, #428]
	str	r3, [r4, #1560]
	ldr	r3, [r8, #432]
	str	r3, [r4, #1564]
	ldr	r3, [r8, #436]
	str	r3, [r4, #1568]
	ldr	r3, [r8, #440]
	str	r3, [r4, #1572]
	ldr	r3, [r8, #444]
	str	r3, [r4, #1576]
	ldr	r3, [r8, #448]
	str	r3, [r4, #1580]
	ldr	r3, [r8, #452]
	str	r3, [r4, #1584]
	ldr	r3, [r8, #456]
	str	r3, [r4, #1588]
	ldr	r3, [r8, #460]
	str	r3, [r4, #1592]
	ldr	r3, [r8, #464]
	str	r3, [r4, #1596]
	ldr	r3, [r8, #468]
	str	r3, [r4, #1600]
	ldr	r3, [r8, #472]
	str	r3, [r4, #1604]
	ldr	r3, [r8, #476]
	str	r3, [r4, #1608]
	ldr	r3, [r8, #480]
	str	r3, [r4, #1612]
	ldr	r3, [r8, #484]
	str	r3, [r4, #1616]
	ldr	r3, [r8, #488]
	str	r3, [r4, #1620]
	ldr	r3, [r8, #492]
	str	r3, [r4, #1624]
	ldr	r3, [r8, #496]
	str	r3, [r4, #1628]
	ldr	r3, [r8, #500]
	str	r3, [r4, #1632]
	ldr	r3, [r8, #504]
	str	r3, [r4, #1636]
	ldr	r3, [r8, #508]
	str	r3, [r4, #1640]
	ldr	r3, [r8, #512]
	str	r3, [r4, #1644]
	ldr	r3, [r8, #516]
	str	r3, [r4, #1648]
	ldr	r3, [r8, #520]
	str	r3, [r4, #1652]
	ldr	r3, [r8, #524]
	str	r3, [r4, #1656]
	ldr	r3, [r8, #528]
	str	r3, [r4, #1660]
	ldr	r3, [r8, #532]
	str	r3, [r4, #1664]
.L108:
	str	r2, [r4, #1472]
	mov	r6, #9
	ldr	r3, [r8, #200]
	mov	r2, #0
	bfi	r2, r6, #24, #8
	add	r5, r5, #4096
	mov	lr, #0
	mov	r6, #0
	str	r3, [r4, #1404]
	mov	ip, lr
	ldr	r3, [r8, #204]
	bfc	lr, #0, #1
	bfc	ip, #0, #1
	mov	r0, #0
	mov	r1, #0
	bfc	r0, #0, #1
	str	r3, [r4, #1408]
	bfc	r1, #0, #1
	ldr	r7, [r8, #208]
	bfc	lr, #1, #1
	ldr	r3, [fp, #-60]
	bfc	ip, #1, #1
	bfc	r0, #1, #1
	bfc	r1, #1, #1
	str	r7, [r4, #1412]
	add	r3, r3, #61440
	ldr	r7, [r8, #212]
	bfc	lr, #2, #1
	bfc	ip, #2, #1
	bfc	r0, #2, #1
	bfc	r1, #2, #1
	bfc	lr, #3, #1
	str	r7, [r4, #1416]
	mov	r7, #7
	ldr	r10, [r8, #216]
	bfi	r2, r7, #16, #8
	bfc	r2, #8, #8
	bfc	ip, #3, #1
	bfc	r0, #3, #1
	bfc	r1, #3, #1
	str	r10, [r4, #1420]
	mov	r10, r6
	ldr	r7, [r8, #220]
	bfc	r10, #0, #1
	str	r7, [r4, #1424]
	mov	r7, #1
	ldr	r9, [r8, #224]
	bfi	r2, r7, #0, #8
	str	r9, [r4, #1428]
	ldr	r9, [r8, #228]
	str	r9, [r4, #1432]
	ldr	r9, [r8, #232]
	str	r9, [r4, #1436]
	ldr	r9, [r8, #236]
	str	r9, [r4, #1440]
	ldr	r9, [r8, #240]
	str	r9, [r4, #1444]
	ldr	r9, [r8, #244]
	str	r9, [r4, #1448]
	ldr	r9, [r8, #248]
	str	r9, [r4, #1452]
	ldr	r9, [r8, #252]
	str	r9, [r4, #1456]
	ldr	r9, [r8, #256]
	str	r9, [r4, #1460]
	ldr	r9, [r8, #260]
	str	r9, [r4, #1464]
	ldr	r9, [r8, #336]
	str	r9, [r4, #1468]
	ldr	r9, [r8, #264]
	str	r9, [r4, #1340]
	ldr	r9, [r8, #268]
	str	r9, [r4, #1344]
	ldr	r9, [r8, #272]
	str	r9, [r4, #1348]
	ldr	r9, [r8, #276]
	str	r9, [r4, #1352]
	ldr	r9, [r8, #280]
	str	r9, [r4, #1356]
	ldr	r9, [r8, #284]
	str	r9, [r4, #1360]
	ldr	r9, [r8, #288]
	str	r9, [r4, #1364]
	ldr	r9, [r8, #292]
	str	r9, [r4, #1368]
	ldr	r9, [r8, #296]
	str	r9, [r4, #1372]
	ldr	r9, [r8, #300]
	str	r9, [r4, #1376]
	ldr	r9, [r8, #304]
	str	r9, [r4, #1380]
	ldr	r9, [r8, #308]
	str	r9, [r4, #1384]
	ldr	r9, [r8, #312]
	str	r9, [r4, #1388]
	ldr	r9, [r8, #316]
	str	r9, [r4, #1392]
	ldr	r9, [r8, #320]
	str	r9, [r4, #1396]
	ldr	r9, [r8, #324]
	str	r9, [r4, #1400]
	mov	r9, #3
	ldr	r4, [r5, #1676]
	ldr	r5, [r5, #1680]
	bfi	r6, r4, #0, #1
	ldr	r4, [fp, #-56]
	bfi	r6, r5, #3, #1
	mov	r5, #0
	bfi	r6, r9, #16, #4
	str	r6, [r3]
	str	r10, [r3, #8]
	str	lr, [r3, #16]
	str	ip, [r3, #28]
	str	r0, [r3, #32]
	mov	r0, #0
	str	r1, [r3, #44]
	str	r2, [r3, #1328]
	ldr	r2, [fp, #-60]
	ldr	r4, [r4]
	str	r5, [r2, #4]
	add	r4, r4, #61440
	ldr	r3, [r8, #576]
	str	r3, [r4, #520]
	ldr	r3, [r8, #576]
	str	r3, [r4, #524]
	ldr	r3, [r8, #584]
	str	r3, [r4, #752]
	ldr	r3, [r8, #580]
	str	r3, [r4, #756]
	ldr	r3, [r8, #584]
	str	r3, [r4, #772]
	ldr	r3, [r8, #580]
	str	r3, [r4, #776]
	str	r7, [r2, #8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L159:
	ldr	r3, [r5, #2392]
	sub	r0, r3, #1
	mov	r1, r3, lsr #8
	bfi	r2, r0, #16, #7
	sub	r1, r1, #1
	mov	r3, r3, lsr #16
	sub	r3, r3, #1
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #0, #6
	str	r2, [r4, #1328]
	ldr	r3, [r5, #2396]
	str	r3, [r4, #1296]
	ldr	r3, [r5, #2400]
	str	r3, [r4, #1300]
	ldr	r3, [r5, #2404]
	str	r3, [r4, #1304]
	ldr	r3, [r5, #2408]
	str	r3, [r4, #1308]
	ldr	r3, [r5, #2412]
	str	r3, [r4, #1312]
	ldr	r3, [r5, #2416]
	str	r3, [r4, #1316]
	ldr	r3, [r5, #2420]
	str	r3, [r4, #1320]
	ldr	r3, [r5, #2424]
	str	r3, [r4, #1324]
	b	.L105
.L158:
	ldr	r3, [r8, #632]
	sub	r0, r3, #1
	mov	r1, r3, lsr #8
	bfi	r2, r0, #16, #7
	sub	r1, r1, #1
	mov	r3, r3, lsr #16
	sub	r3, r3, #1
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #0, #6
	str	r2, [r4, #1288]
	ldr	r3, [r8, #600]
	str	r3, [r4, #1256]
	ldr	r3, [r8, #604]
	str	r3, [r4, #1260]
	ldr	r3, [r8, #608]
	str	r3, [r4, #1264]
	ldr	r3, [r8, #612]
	str	r3, [r4, #1268]
	ldr	r3, [r8, #616]
	str	r3, [r4, #1272]
	ldr	r3, [r8, #620]
	str	r3, [r4, #1276]
	ldr	r3, [r8, #624]
	str	r3, [r4, #1280]
	ldr	r3, [r8, #628]
	str	r3, [r4, #1284]
	b	.L98
.L153:
	ldr	r3, [fp, #-48]
	cmp	r2, #1920
	add	r4, r3, #4096
	movcs	r3, #3
	strcs	r3, [r4, #2360]
	bcs	.L110
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r4, #2360]
	ldmib	r8, {r2, r3}
	cmp	r2, #0
	bne	.L113
.L155:
	cmp	r3, #3
	clz	r3, r3
	movne	r2, #1
	moveq	r2, #0
	mov	r3, r3, lsr #5
	str	r2, [r4, #2368]
	str	r3, [r4, #2372]
	moveq	r2, #7
	movne	r2, #5
	str	r2, [r4, #2364]
	b	.L115
.L157:
	cmp	r3, #3
	clz	r3, r3
	movne	r2, #1
	moveq	r2, #0
	mov	r3, r3, lsr #5
	str	r2, [r5, #2368]
	str	r3, [r5, #2372]
	moveq	r2, #7
	movne	r2, #5
	str	r2, [r5, #2364]
	b	.L83
.L156:
	cmp	r2, #1920
	movcs	r3, #3
	strcs	r3, [r5, #2360]
	bcs	.L78
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r5, #2360]
	b	.L78
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_CfgReg, .-DRV_VENC_HAL_V500R001_CfgReg
	.align	2
	.global	DRV_VENC_HAL_V500R001_Init
	.type	DRV_VENC_HAL_V500R001_Init, %function
DRV_VENC_HAL_V500R001_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, .L189
	mov	r0, #0
	mov	r1, #63232
	movt	r0, 63688
	ldr	r4, .L189+4
	ldr	r3, [r3, #12]
	blx	r3
	cmp	r0, #0
	str	r0, [r4]
	beq	.L180
	ldr	r3, .L189
	movw	r0, #9968
	ldr	r3, [r3, #20]
	blx	r3
	ldr	r3, .L189
	movw	r2, #9968
	mov	r1, #0
	ldr	r3, [r3]
	str	r0, [r4, #4]
	blx	r3
	ldr	r9, [r4, #4]
	cmp	r9, #0
	beq	.L179
	ldr	r3, .L189
	mov	r2, #692
	mov	r1, #0
	mov	r0, r9
	mov	r6, #1280
	mov	r5, #720
	ldr	r3, [r3]
	blx	r3
	ldr	ip, [r4]
	mov	r3, #0
	add	r2, r9, #260
	add	r0, r9, #324
	mov	r1, r3
	mov	lr, #3
	str	ip, [r9]
	mov	r4, #10240
	mov	ip, #1
	str	r3, [r9, #4]
	str	r3, [r9, #20]
	str	r3, [r9, #24]
	str	r3, [r9, #32]
	str	r3, [r9, #36]
	str	r3, [r9, #48]
	str	r3, [r9, #60]
	str	r3, [r9, #64]
	str	r3, [r9, #136]
	str	r3, [r9, #168]
	str	r3, [r9, #172]
	str	r3, [r9, #176]
	str	r3, [r9, #180]
	str	r3, [r9, #184]
	str	r3, [r9, #188]
	str	r3, [r9, #192]
	str	lr, [r9, #8]
	str	lr, [r9, #44]
	str	r6, [r9, #12]
	str	r5, [r9, #16]
	str	r4, [r9, #28]
	str	ip, [r9, #40]
	str	ip, [r9, #56]
.L169:
	str	r1, [r2, #4]!
	cmp	r2, r0
	mov	r3, #0
	bne	.L169
	add	r5, r9, #8704
	add	lr, r9, #8768
	add	r0, r9, #8832
	add	r7, r9, #8640
	add	r6, r9, #8896
	mov	r4, r5
	mov	ip, lr
	mov	r1, r0
	add	r7, r7, #40
	add	r6, r6, #8
	add	r5, r5, #8
	add	r4, r4, #40
	add	lr, lr, #8
	add	ip, ip, #40
	add	r0, r0, #8
	add	r1, r1, #40
	mov	r8, #7
	mov	r2, r3
	mov	r10, r3
	str	r3, [r9, #536]
	str	r3, [r9, #540]
	str	r3, [r9, #556]
	str	r3, [r9, #560]
	str	r3, [r9, #564]
	str	r3, [r9, #568]
	str	r3, [r9, #572]
	str	r3, [r9, #632]
	str	r3, [r9, #636]
	mov	r3, #28
	str	r9, [fp, #-48]
	str	r3, [r9, #544]
	mov	r3, #16
	str	r3, [r9, #548]
	mov	r3, #48
	str	r3, [r9, #552]
.L170:
	str	r10, [r7, #4]!
	mov	r9, #1
	str	r10, [r6, #4]!
	mov	r3, #0
	str	r9, [r5, #4]!
	mov	r9, #26
	str	r9, [r4, #4]!
	str	r8, [lr, #4]!
	str	r8, [ip, #4]!
	str	r2, [r0, #4]!
	str	r2, [r1, #4]!
	add	r2, r2, #5
	cmp	r2, #40
	bne	.L170
	ldr	r9, [fp, #-48]
	mov	ip, #1
	mov	lr, #256
	mov	r6, #4
	add	r1, r9, #7360
	add	r0, r9, #7424
	add	r2, r9, #4096
	add	r1, r1, #52
	add	r0, r0, #52
	mov	r5, #128
	mov	r4, #8
	str	lr, [r2, #2484]
	str	ip, [r2, #2476]
	mov	lr, #32
	str	r3, [r2, #2472]
	mov	r8, #3
	str	r3, [r2, #2520]
	mov	r7, #6
	str	r3, [r2, #2524]
	str	r3, [r2, #2528]
	str	r3, [r2, #2532]
	str	r3, [r2, #2548]
	str	r3, [r2, #2552]
	str	r3, [r2, #2556]
	str	r3, [r2, #2560]
	str	r3, [r2, #2576]
	str	r3, [r2, #2580]
	str	r3, [r2, #2584]
	str	r3, [r2, #2588]
	str	r3, [r2, #2604]
	str	r3, [r2, #2608]
	str	r3, [r2, #2612]
	str	r3, [r2, #2632]
	str	r3, [r2, #2636]
	str	r3, [r2, #2640]
	str	r3, [r2, #2660]
	str	r8, [r2, #2500]
	str	r7, [r2, #2924]
	str	r6, [r2, #2480]
	str	r6, [r2, #2492]
	str	r5, [r2, #2488]
	str	r5, [r2, #2496]
	str	r4, [r2, #2504]
	str	r4, [r2, #2512]
	str	lr, [r2, #2508]
	str	lr, [r2, #2516]
	str	lr, [r2, #2920]
	str	r3, [r2, #2664]
	str	r3, [r2, #2668]
	str	r3, [r2, #2688]
	str	r3, [r2, #2692]
	str	r3, [r2, #2696]
	str	r3, [r2, #2716]
	str	r3, [r2, #2720]
	str	r3, [r2, #2724]
	str	r3, [r2, #2728]
	str	r3, [r2, #2748]
	str	r3, [r2, #2752]
	str	r3, [r2, #2756]
	str	r3, [r2, #2760]
	str	ip, [r2, #3128]
	str	r3, [r2, #3132]
	str	r3, [r2, #3136]
	str	r3, [r2, #3140]
	str	r3, [r2, #3144]
	str	r3, [r2, #3148]
	str	r3, [r2, #3152]
	str	ip, [r2, #3156]
	str	r3, [r2, #3160]
	str	r3, [r2, #3164]
	str	r3, [r2, #3168]
	str	r3, [r2, #3172]
	str	r3, [r2, #3176]
	str	r3, [r2, #3180]
	str	r3, [r2, #3184]
	str	r3, [r2, #3188]
	str	r3, [r2, #3192]
	str	r3, [r2, #3196]
	str	r3, [r2, #3200]
	str	r3, [r2, #3204]
	str	ip, [r2, #3208]
	str	r3, [r2, #3212]
	str	r3, [r2, #3216]
	str	r3, [r2, #3220]
	str	r3, [r2, #3224]
	str	r3, [r2, #3228]
	str	r3, [r2, #3232]
	str	ip, [r2, #2780]
	str	r3, [r2, #2784]
	str	r3, [r2, #2788]
	str	r3, [r2, #2792]
	str	r3, [r2, #2796]
	str	r3, [r2, #2800]
	str	r3, [r2, #2804]
	str	r3, [r2, #3236]
	str	r3, [r2, #3240]
	str	r3, [r2, #3244]
	str	r3, [r2, #3248]
	str	r3, [r2, #3252]
	str	r3, [r2, #3256]
	str	r3, [r2, #3260]
	str	r3, [r2, #3264]
	str	r3, [r2, #3268]
	str	r3, [r2, #3272]
	str	r3, [r2, #3276]
	str	r3, [r2, #3280]
	str	r3, [r2, #3284]
	str	r3, [r2, #3288]
	str	r3, [r2, #3292]
	str	r3, [r2, #3296]
	str	r3, [r2, #3300]
	str	r3, [r2, #3304]
	str	r3, [r2, #3308]
	str	r3, [r2, #3312]
	str	r3, [r2, #2864]
	str	r3, [r2, #2960]
	str	r3, [r2, #2964]
	str	r3, [r2, #2976]
	str	r3, [r2, #2980]
	str	r3, [r2, #2872]
	str	r3, [r2, #2984]
	str	r3, [r2, #2988]
	str	r3, [r2, #3000]
	str	r3, [r2, #3004]
	str	r3, [r2, #2888]
	str	r3, [r2, #3032]
	str	r3, [r2, #3036]
	str	r3, [r2, #3048]
	str	r3, [r2, #3052]
	str	r3, [r2, #2896]
	str	r3, [r2, #2880]
	str	r3, [r2, #3008]
	str	r3, [r2, #3012]
	str	r3, [r2, #3024]
	str	r3, [r2, #3028]
	str	r3, [r2, #2936]
	str	r3, [r2, #2940]
	str	r3, [r2, #2904]
	str	r3, [r2, #2808]
	str	r3, [r2, #2812]
	str	r3, [r2, #2816]
	str	r3, [r2, #2824]
	str	r3, [r2, #2832]
	str	r3, [r2, #3080]
	str	r3, [r2, #3084]
	str	r3, [r2, #3096]
	str	r3, [r2, #3100]
	str	r3, [r2, #3316]
.L171:
	str	ip, [r1, #4]!
	cmp	r1, r0
	mov	r4, #1
	bne	.L171
	ldr	r3, .L189+8
	mov	r8, #4
	mov	r7, #12
	mov	r0, #48
	mov	r6, #50
	mov	r1, #8
	str	r3, [fp, #-52]
	mov	ip, #44
	mov	r3, #0
	str	r1, [r2, #3384]
	str	r1, [r2, #3444]
	add	lr, r9, #860
	mov	r1, #10
	str	r3, [r2, #3396]
	str	r3, [r2, #3612]
	mov	r10, #20
	str	r3, [r2, #3404]
	mov	r5, #3
	str	r3, [r2, #3400]
	str	r3, [r2, #3616]
	str	r3, [r2, #3412]
	str	r3, [r2, #3728]
	str	r3, [r2, #3676]
	str	r3, [r2, #3580]
	str	r3, [r2, #3744]
	str	r3, [r2, #3624]
	str	lr, [fp, #-48]
	mov	lr, #3
	str	r3, [r2, #3628]
	str	r0, [r2, #3416]
	str	r0, [r2, #3424]
	str	r0, [r2, #3420]
	mov	r0, #2592
	str	r1, [r2, #3732]
	str	r1, [r2, #3724]
	str	r1, [r2, #3736]
	str	r1, [r2, #3436]
	str	r1, [r2, #3720]
	str	lr, [r2, #3392]
	mov	lr, #2
	str	r7, [r2, #3452]
	str	lr, [r2, #3388]
	mov	lr, #51
	str	r7, [r2, #3456]
	str	ip, [r2, #3432]
	movw	ip, #21845
	str	lr, [r2, #3428]
	str	r8, [r2, #3440]
	str	r8, [r2, #3484]
	str	r8, [r2, #3488]
	str	lr, [r2, #3448]
	mov	lr, #5
	str	r0, [r2, #3460]
	mov	r0, #70
	str	r6, [r2, #3508]
	str	r6, [r2, #3540]
	str	r3, [r2, #3592]
	str	r3, [r2, #3692]
	str	r3, [r2, #3696]
	str	r3, [r2, #3472]
	str	lr, [r2, #3464]
	mov	lr, #60
	str	r3, [r2, #3468]
	str	r3, [r2, #3632]
	str	r3, [r2, #3680]
	str	ip, [r2, #3500]
	str	ip, [r2, #3504]
	mov	ip, #80
	str	lr, [r2, #3512]
	str	lr, [r2, #3544]
	mov	lr, #8
	str	r0, [r2, #3516]
	str	r0, [r2, #3548]
	mov	r0, #120
	str	ip, [r2, #3520]
	str	ip, [r2, #3552]
	mov	ip, #140
	str	r0, [r2, #3524]
	str	r0, [r2, #3556]
	mov	r0, #160
	str	ip, [r2, #3528]
	str	ip, [r2, #3560]
	mov	ip, #180
	str	r0, [r2, #3532]
	str	r0, [r2, #3564]
	str	r8, [r2, #3492]
	str	r8, [r2, #3496]
	str	r8, [r2, #3656]
	str	r8, [r2, #3476]
	str	r4, [r2, #3584]
	str	r4, [r2, #3588]
	str	r4, [r2, #3596]
	str	r4, [r2, #3600]
	str	ip, [r2, #3536]
	str	ip, [r2, #3568]
	mov	ip, #150
	str	ip, [r2, #3764]
	add	ip, r2, #4096
	str	r3, [r2, #3684]
	str	r3, [r2, #3688]
	str	r3, [r2, #3572]
	str	r3, [r2, #3576]
	str	r3, [r2, #3620]
	str	r3, [r2, #3748]
	str	r3, [r2, #3752]
	str	r10, [r2, #3756]
	str	r6, [r2, #3760]
	mov	r6, #6
	str	r3, [r2, #3812]
	str	r3, [r2, #3816]
	str	r7, [r2, #3768]
	str	lr, [r2, #3772]
	str	r7, [r2, #3780]
	mov	r7, #15
	str	lr, [r2, #3784]
	mov	lr, #2
	str	r3, [r2, #3836]
	str	lr, [r2, #3792]
	mov	lr, #3
	str	r3, [r2, #3840]
	str	r3, [r2, #3844]
	str	r3, [r2, #3848]
	str	r3, [r2, #3852]
	str	r3, [r2, #3856]
	str	r3, [r2, #3860]
	str	r3, [r2, #3864]
	str	r3, [r2, #3868]
	str	r3, [r2, #3872]
	str	r3, [r2, #3876]
	str	r3, [r2, #3880]
	str	r8, [r2, #3776]
	str	r8, [r2, #3788]
	str	r8, [r2, #3796]
	str	r6, [r2, #3800]
	str	r3, [ip, #392]
	str	r3, [ip, #396]
	str	r10, [r2, #3808]
	str	lr, [r2, #3804]
	mov	lr, #5
	str	r7, [ip, #408]
	str	lr, [ip, #416]
	str	lr, [ip, #412]
	movw	lr, #511
	str	r7, [ip, #404]
	str	lr, [ip, #400]
	mov	lr, #100
	str	r0, [r2, #3824]
	mov	r0, #131
	str	lr, [r2, #3828]
	mov	lr, #3
	str	r0, [r2, #3820]
	mov	r0, #127
	str	r0, [r2, #3832]
	add	r0, r9, #1020
	str	r6, [ip, #352]
	mov	r6, #24
	str	r3, [ip, #320]
	str	r3, [ip, #324]
	str	lr, [ip, #328]
	mov	lr, #2
	str	r3, [ip, #332]
	str	r3, [ip, #344]
	str	lr, [ip, #348]
	mov	lr, #8
	str	r3, [ip, #388]
	str	lr, [ip, #356]
	str	lr, [ip, #360]
	str	lr, [ip, #364]
	str	lr, [ip, #368]
	mov	lr, #60
	str	r3, [ip, #420]
	str	r3, [ip, #424]
	str	r3, [ip, #428]
	str	r3, [ip, #432]
	str	lr, [ip, #436]
	mov	lr, #16
	str	r4, [ip, #340]
	str	lr, [ip, #372]
	str	lr, [ip, #376]
	mov	lr, #5
	str	r6, [ip, #380]
	str	r6, [ip, #384]
	mvn	r6, #0
	str	r3, [ip, #444]
	str	r3, [ip, #448]
	str	lr, [ip, #452]
	mov	lr, #8
	str	r3, [ip, #456]
	str	r3, [ip, #460]
	str	r3, [ip, #440]
	str	r3, [ip, #464]
	str	r3, [ip, #468]
	str	lr, [ip, #472]
	str	lr, [ip, #476]
	mov	lr, #3
	str	r3, [ip, #480]
	str	r3, [ip, #484]
	str	r10, [ip, #488]
	str	r1, [r2, #3884]
	movw	r1, #767
	str	r1, [r2, #3896]
	add	r1, r9, #8192
	str	r10, [r2, #3888]
	mov	r10, #7
	str	r4, [r2, #3892]
	str	r3, [r1, #780]
	str	r3, [r1, #784]
	str	r3, [r1, #788]
	str	r3, [r1, #808]
	str	r3, [r1, #812]
	str	r3, [r1, #820]
	str	r3, [r1, #824]
	str	r3, [r1, #840]
	str	r3, [r1, #844]
	str	r3, [r1, #892]
	str	r4, [r1, #792]
	str	r4, [r1, #796]
	str	r4, [r1, #828]
	str	r4, [r1, #832]
	str	r4, [r1, #836]
	str	r3, [r1, #896]
	str	r3, [r1, #900]
	str	r3, [r1, #908]
	str	r3, [r1, #904]
	str	r3, [r1, #912]
	str	r3, [r1, #924]
	str	r3, [r1, #1420]
	str	r3, [r1, #928]
	str	r3, [r1, #992]
	str	r3, [r1, #988]
	str	r3, [r1, #1520]
	str	r3, [r1, #1524]
	str	r3, [r1, #1528]
	str	r3, [r1, #1532]
	str	r3, [r1, #1536]
	str	r3, [r1, #1540]
	str	r3, [r1, #1544]
	str	r3, [r1, #1548]
	str	r3, [r1, #952]
	str	r3, [r1, #960]
	str	r3, [r1, #964]
	str	r3, [r1, #968]
	str	r3, [r1, #972]
	str	r3, [r1, #976]
	str	r3, [r1, #800]
	str	r3, [r1, #984]
	str	r3, [r1, #1000]
	str	r3, [r1, #1004]
	str	r3, [r1, #1008]
	str	lr, [r1, #1020]
	str	r3, [r1, #1024]
	str	r4, [r1, #956]
	str	r4, [r1, #980]
	str	r4, [r1, #996]
	str	r10, [r1, #932]
	str	r10, [r1, #936]
	str	r3, [r1, #1060]
	str	r3, [r1, #1064]
	str	r3, [r1, #1068]
	str	r3, [r1, #1072]
	str	r3, [r1, #1076]
	str	r3, [r1, #1080]
	str	r3, [r1, #1084]
	str	r3, [r1, #1088]
	str	r3, [r1, #1092]
	str	r3, [r1, #1096]
	str	r3, [r1, #1108]
	str	r3, [r1, #1104]
	str	r3, [r1, #1100]
	str	r3, [r1, #1112]
	str	r3, [r1, #1116]
	str	r3, [r1, #1120]
	str	r3, [r1, #1124]
	str	r3, [r1, #1128]
	str	r3, [r1, #1132]
	str	r10, [r1, #1140]
	str	r10, [r1, #1148]
	str	r10, [r1, #1156]
	str	r10, [r1, #1164]
	str	r3, [r1, #1184]
	str	r3, [r1, #1188]
	str	r6, [r1, #1136]
	str	r6, [r1, #1144]
	str	r4, [r1, #1028]
	str	r4, [r1, #1168]
	str	r4, [r1, #1172]
	str	r4, [r1, #1176]
	str	r4, [r1, #1180]
	str	r6, [r1, #1152]
	str	r6, [r1, #1160]
	mov	r6, #23040
	movt	r6, 610
	str	r3, [r1, #1192]
	mov	lr, r6
	mov	r6, #100
	str	r6, [r1, #1200]
	mov	r6, #2304
	str	r7, [r1, #1216]
	movt	r6, 61
	str	r7, [r1, #1220]
	str	r7, [r1, #1308]
	str	r7, [r1, #1312]
	str	r3, [r1, #1196]
	str	r3, [r1, #940]
	str	r3, [r1, #1232]
	str	r3, [r1, #1252]
	str	r3, [r1, #1256]
	str	r3, [r1, #1260]
	str	r3, [r1, #1264]
	str	r3, [r1, #1268]
	str	r3, [r1, #1292]
	str	r3, [r1, #1296]
	str	r3, [r1, #1300]
	str	r3, [r1, #1304]
	str	r3, [r1, #1336]
	str	r3, [r1, #1344]
	str	r4, [r1, #1224]
	str	r6, [fp, #-56]
	mov	r6, #2
	str	r4, [r1, #944]
	str	r6, [r1, #1600]
	str	r6, [r1, #1596]
	str	r6, [r1, #1340]
	mov	r6, #3
	str	r4, [r1, #1228]
	str	r6, [r1, #1348]
	str	r6, [r1, #1352]
	mov	r6, #5
	str	r4, [r1, #1272]
	str	r6, [r1, #1208]
	str	r6, [r1, #1212]
	mov	r6, #500
	str	r3, [r1, #1356]
	str	r3, [r1, #1360]
	str	r6, [r1, #1204]
	mov	r6, #255
	str	r3, [r1, #1400]
	str	r5, [r1, #1244]
	mov	r5, #2
	str	r3, [r1, #1412]
	str	r3, [r1, #1408]
	str	r3, [r1, #1404]
	str	r3, [r1, #1416]
	str	r3, [r1, #1424]
	str	r3, [r1, #1428]
	str	r3, [r1, #1432]
	str	r3, [r1, #1436]
	str	r3, [r1, #1440]
	str	r3, [r1, #1444]
	str	r3, [r1, #1392]
	str	r3, [r1, #1388]
	str	r3, [r1, #1468]
	str	r3, [r1, #1456]
	str	r3, [r1, #1460]
	str	r3, [r1, #1552]
	str	r3, [r1, #1568]
	str	r3, [r1, #1572]
	str	r3, [r1, #1576]
	str	r3, [r1, #1580]
	str	r3, [r1, #1584]
	str	r3, [r1, #1588]
	str	r3, [r1, #1288]
	str	r3, [r1, #1592]
	str	r3, [r1, #1464]
	str	r3, [r1, #1484]
	str	r4, [r1, #848]
	str	r4, [r1, #948]
	str	r4, [r1, #1012]
	str	r3, [r1, #1476]
	str	r7, [r1, #1632]
	mov	r7, #171
	str	r5, [r1, #1364]
	str	r3, [r1, #1608]
	str	r3, [r1, #1628]
	str	r3, [r1, #1612]
	str	r3, [r1, #1616]
	str	r3, [r1, #1620]
	str	r3, [r1, #1624]
	str	r3, [r1, #1644]
	str	r3, [r1, #1640]
	str	r3, [r1, #1652]
	str	r7, [r1, #1660]
	mov	r7, #85
	str	r6, [r1, #1480]
	str	r7, [r1, #1664]
	mov	r7, #9
	str	r6, [r1, #1472]
	str	r7, [r1, #1636]
	str	r4, [r1, #1016]
	str	r4, [r1, #1396]
	mov	r1, #3
	str	r10, [ip, #1672]
	str	r1, [ip, #1668]
	mov	r1, #64
	str	r3, [ip, #1676]
	str	r3, [ip, #1700]
	str	r3, [ip, #1696]
	str	r3, [ip, #1704]
	str	r3, [ip, #1688]
	str	r3, [ip, #1684]
	str	r3, [ip, #1692]
	str	r3, [ip, #1708]
	str	r3, [ip, #1712]
	str	r3, [ip, #1716]
	str	r3, [ip, #1720]
	str	r3, [ip, #1724]
	str	r4, [ip, #1680]
	str	r3, [ip, #1728]
	str	lr, [ip, #1768]
	ldr	lr, [fp, #-56]
	str	r3, [ip, #1732]
	str	r3, [ip, #1736]
	str	r3, [ip, #1740]
	str	r5, [ip, #1760]
	str	r3, [ip, #1744]
	str	r3, [ip, #1748]
	str	r3, [ip, #1752]
	str	r3, [ip, #1756]
	str	lr, [ip, #1772]
	mov	lr, #3
	str	r4, [ip, #1764]
	mov	ip, #3
	str	r3, [r9, #736]
	str	ip, [r9, #700]
	mov	ip, #16
	str	r3, [r9, #740]
	str	ip, [r9, #712]
	str	ip, [r9, #720]
	str	ip, [r9, #752]
	mov	ip, #25
	str	r3, [r9, #744]
	str	r3, [r9, #748]
	str	r3, [r9, #764]
	str	r3, [r9, #768]
	str	r3, [r9, #772]
	str	r3, [r9, #800]
	str	r3, [r9, #804]
	str	r3, [r9, #808]
	str	r3, [r9, #812]
	str	r3, [r9, #816]
	mov	r3, #35
	str	r10, [r9, #820]
	str	r8, [r9, #708]
	str	r8, [r9, #716]
	str	r8, [r9, #756]
	str	r8, [r9, #792]
	ldr	r5, .L189+8
	str	r4, [r9, #696]
	str	lr, [r9, #1188]
	str	lr, [r9, #1200]
	mov	lr, #8
	str	lr, [r9, #1204]
	mov	lr, #11
	str	lr, [r9, #836]
	mov	lr, #14
	str	lr, [r9, #840]
	mov	lr, #18
	str	lr, [r9, #844]
	ldr	lr, [fp, #-48]
	str	r1, [r9, #704]
	mov	r1, #96
	str	r10, [r9, #824]
	str	r7, [r9, #832]
	movw	r7, #378
	str	r10, [r9, #828]
	mov	r10, #128
	str	r4, [r9, #692]
	str	r4, [r9, #760]
	str	r6, [r9, #852]
	str	r6, [r9, #856]
	str	r6, [r9, #860]
	str	r8, [r9, #776]
	str	r4, [r9, #784]
	str	r4, [r9, #780]
	str	r4, [r9, #1184]
	str	ip, [r9, #848]
	str	ip, [r9, #1192]
	str	r3, [r9, #796]
	str	r1, [r9, #1212]
	str	r7, [r9, #1208]
	str	r10, [r9, #1196]
.L172:
	ldr	r3, [r5, #4]!
	str	r3, [lr, #4]!
	cmp	lr, r0
	bne	.L172
	add	ip, r9, #1168
	ldr	r3, .L189+12
	add	ip, ip, #12
.L173:
	ldr	r1, [r3, #4]!
	str	r1, [r0, #4]!
	cmp	r0, ip
	bne	.L173
	add	r3, r9, #6400
	mov	r7, #3
	add	r4, r9, #1216
	add	r3, r3, #56
	mov	r1, #7
	str	r3, [fp, #-52]
	str	r4, [fp, #-48]
	mov	r3, #0
	str	r1, [r2, #2364]
	str	r3, [r2, #2372]
	str	r3, [r2, #2368]
	str	r4, [fp, #-56]
.L175:
	ldr	r4, [fp, #-48]
	movw	r2, #2620
	ldr	r3, .L189
	mov	r1, #0
	mov	r9, #0
	mov	r0, r4
	ldr	r3, [r3]
	blx	r3
	mov	r1, r4
	mov	r3, r4
	mov	r2, r4
	mov	r0, r9
	mov	lr, #4
	mov	r4, #64
	mov	ip, #1
.L174:
	add	r9, r9, #1
	str	r7, [r3, #8]
	cmp	r9, #5
	mov	r8, #32
	mov	r5, #96
	mov	r10, #2
	str	r5, [r2, #2488]
	mov	r6, #16
	str	lr, [r1, #420]
	mov	r5, #20
	str	r0, [r3, #44]
	add	r1, r1, #408
	str	r0, [r3, #72]
	add	r3, r3, #84
	str	r4, [r3, #-72]
	str	ip, [r3, #-80]
	str	r5, [r2, #2468]
	mov	r5, #8
	str	r7, [r2, #2464]
	str	r5, [r2, #2480]
	mov	r5, #384
	str	r4, [r2, #2472]
	str	lr, [r2, #2476]
	str	r0, [r3, #-28]
	str	r0, [r3, #-8]
	str	lr, [r3, #-60]
	str	r8, [r3, #-56]
	str	ip, [r1, #20]
	str	r0, [r1, #24]
	str	r5, [r2, #2484]
	mov	r5, #35
	str	r8, [r3, #-24]
	str	r0, [r3, #-52]
	str	r0, [r3, #-4]
	str	lr, [r3, #-20]
	str	ip, [r3, #-84]
	str	r10, [r2, #2460]
	add	r2, r2, r8
	str	ip, [r3, #-16]
	str	lr, [r3, #-68]
	str	r6, [r3, #-64]
	str	ip, [r1, #16]
	str	r5, [r1, #32]
	bne	.L174
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #2608
	add	r3, r3, #12
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L175
	ldr	r4, [fp, #-56]
	mov	r3, #1
	mov	r2, #0
	str	r3, [fp, #-48]
	str	r9, [fp, #-52]
	mov	r0, r3
	mov	r9, r2
	mov	r3, r2
	mov	ip, r8
	mov	lr, r10
	mov	r5, #128
	mov	r2, #64
.L176:
	mov	r7, #6
	str	r7, [r4, #828]
	ldr	r7, [fp, #-52]
	cmp	r9, #0
	mov	r10, #15
	mov	r6, #4
	str	r10, [r4, #2596]
	mov	r1, #3
	mov	r10, #38
	str	r0, [r4, #8]
	str	r5, [r4, #12]
	mov	r8, #34
	str	r5, [r4, #28]
	str	r5, [r4, #60]
	str	r3, [r4, #424]
	str	r3, [r4]
	str	r3, [r4, #428]
	str	r3, [r4, #4]
	str	r3, [r4, #836]
	str	r2, [r4, #96]
	str	r2, [r4, #112]
	str	r2, [r4, #144]
	str	r2, [r4, #180]
	str	r2, [r4, #196]
	str	r2, [r4, #228]
	str	r7, [r4, #1236]
	str	r0, [r4, #380]
	str	ip, [r4, #408]
	str	r3, [r4, #388]
	str	r3, [r4, #384]
	str	lr, [r4, #2592]
	str	r2, [r4, #2600]
	str	lr, [r4, #2604]
	str	r6, [r4, #2608]
	str	r10, [r4, #2072]
	beq	.L188
	ldr	r7, [fp, #-48]
	str	r1, [r4, #392]
	cmp	r7, #1
	str	r1, [r4, #360]
	mov	r7, #256
	str	r1, [r4, #368]
	str	r1, [r4, #376]
	str	r1, [r4, #372]
	str	r1, [r4, #400]
	mov	r1, #16
	str	r3, [r4, #412]
	str	ip, [r4, #364]
	str	r0, [r4, #2064]
	str	r7, [r4, #2612]
	str	r8, [r4, #416]
	str	ip, [r4, #396]
	str	r0, [r4, #336]
	str	lr, [r4, #2588]
	str	r0, [r4, #404]
	str	r6, [r4, #352]
	str	r1, [r4, #356]
	bhi	.L179
.L178:
	ldr	r1, [fp, #-48]
	add	r4, r4, #2608
	add	r9, r9, #1
	add	r4, r4, #12
	add	r1, r1, #1
	str	r1, [fp, #-48]
	b	.L176
.L179:
	mov	r0, #0
.L167:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L180:
	mvn	r0, #0
	b	.L167
.L188:
	mov	r7, #256
	str	r6, [r4, #392]
	str	r7, [r4, #2612]
	mov	r7, #16
	str	r9, [r4, #412]
	str	ip, [r4, #364]
	str	r0, [r4, #2064]
	str	r1, [r4, #360]
	str	r6, [r4, #368]
	str	r1, [r4, #376]
	str	r1, [r4, #372]
	str	r1, [r4, #400]
	str	ip, [r4, #396]
	str	r0, [r4, #336]
	str	lr, [r4, #2588]
	str	r0, [r4, #404]
	str	r6, [r4, #352]
	str	r8, [r4, #416]
	str	r7, [r4, #356]
	b	.L178
.L190:
	.align	2
.L189:
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR1-4
	.word	.LANCHOR1+156
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_Init, .-DRV_VENC_HAL_V500R001_Init
	.align	2
	.global	DRV_VENC_HAL_V500R001_Deinit
	.type	DRV_VENC_HAL_V500R001_Deinit, %function
DRV_VENC_HAL_V500R001_Deinit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L192
	ldr	r4, .L192+4
	ldr	r3, [r5, #16]
	ldr	r0, [r4]
	blx	r3
	ldr	r3, [r5, #24]
	ldr	r0, [r4, #4]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L193:
	.align	2
.L192:
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_Deinit, .-DRV_VENC_HAL_V500R001_Deinit
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	g_h264LambdaSsd, %object
	.size	g_h264LambdaSsd, 160
g_h264LambdaSsd:
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	4
	.word	5
	.word	7
	.word	9
	.word	11
	.word	14
	.word	17
	.word	22
	.word	27
	.word	34
	.word	43
	.word	54
	.word	69
	.word	86
	.word	109
	.word	137
	.word	173
	.word	218
	.word	274
	.word	345
	.word	435
	.word	548
	.word	691
	.word	870
	.word	1097
	.word	1382
	.word	1741
	.word	2193
	.word	2763
	.word	3482
	.word	4095
	.word	4095
	.word	4095
	.type	g_h264LambdaSad, %object
	.size	g_h264LambdaSad, 160
g_h264LambdaSad:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	4
	.word	4
	.word	4
	.word	5
	.word	6
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	13
	.word	14
	.word	16
	.word	18
	.word	20
	.word	23
	.word	25
	.word	29
	.word	32
	.word	36
	.word	40
	.word	45
	.word	51
	.word	57
	.word	64
	.word	72
	.word	81
	.word	91
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 160
g_h265LambdaSsd:
	.word	18
	.word	22
	.word	28
	.word	36
	.word	45
	.word	57
	.word	72
	.word	91
	.word	115
	.word	145
	.word	183
	.word	231
	.word	291
	.word	367
	.word	463
	.word	583
	.word	735
	.word	926
	.word	1167
	.word	1470
	.word	1853
	.word	2334
	.word	2941
	.word	3706
	.word	4669
	.word	5883
	.word	7412
	.word	9338
	.word	11766
	.word	14824
	.word	18677
	.word	23532
	.word	29649
	.word	37355
	.word	47065
	.word	59298
	.word	74711
	.word	94130
	.word	118596
	.word	131071
	.type	g_h265LambdaSad, %object
	.size	g_h265LambdaSad, 160
g_h265LambdaSad:
	.word	193
	.word	216
	.word	243
	.word	273
	.word	306
	.word	344
	.word	386
	.word	433
	.word	487
	.word	546
	.word	613
	.word	688
	.word	773
	.word	867
	.word	974
	.word	1093
	.word	1227
	.word	1377
	.word	1546
	.word	1735
	.word	1948
	.word	2186
	.word	2454
	.word	2755
	.word	3092
	.word	3471
	.word	3896
	.word	4373
	.word	4908
	.word	5510
	.word	6184
	.word	6942
	.word	7792
	.word	8746
	.word	9817
	.word	11020
	.word	12369
	.word	13884
	.word	15584
	.word	17493
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_pRegBase, %object
	.size	g_pRegBase, 4
g_pRegBase:
	.space	4
	.type	g_pHalRegInfo, %object
	.size	g_pHalRegInfo, 4
g_pHalRegInfo:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
