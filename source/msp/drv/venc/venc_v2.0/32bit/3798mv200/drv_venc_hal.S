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
	movw	r3, #2600
	mov	r2, #84
	mov	r0, r5
	moveq	r4, r3
	movne	r4, #0
	mla	r1, r2, r6, r4
	add	r1, r5, r1
	add	r1, r1, #520
	bl	memcpy
	mov	r2, #404
	mla	r1, r2, r6, r4
	add	r0, r5, #84
	add	r1, r5, r1
	add	r1, r1, #940
	bl	memcpy
	add	ip, r4, r6, lsl #5
	add	ip, r5, ip
	add	lr, r5, #488
	add	ip, ip, #2960
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_SetDefaultAttrByStartQP, .-DRV_VENC_HAL_SetDefaultAttrByStartQP
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
	bne	.L9
	ldr	r1, .L19
	add	r2, r0, #164
	add	r3, r0, #324
.L10:
	ldr	ip, [r1, #4]!
	str	ip, [r2, #4]!
	cmp	r2, r3
	bne	.L10
	ldr	r2, .L19+4
	add	ip, r0, #484
.L11:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, ip
	bne	.L11
	mov	r3, #4
	mov	r2, #32
	str	r3, [r0, #100]
	mov	r5, #9
	mov	r3, #0
	str	r2, [r0, #516]
	str	r3, [r0, #104]
	mov	r2, #7
	str	r3, [r0, #108]
	mov	r4, #11
	str	r3, [r0, #112]
	mov	lr, #14
	str	r3, [r0, #116]
	mov	ip, #18
	str	r3, [r0, #120]
	mov	r1, #25
	mov	r3, #255
	str	r2, [r0, #124]
	str	r2, [r0, #128]
	str	r2, [r0, #132]
	str	r5, [r0, #136]
	str	r4, [r0, #140]
	str	lr, [r0, #144]
	str	ip, [r0, #148]
	str	r1, [r0, #152]
	str	r3, [r0, #156]
	str	r3, [r0, #160]
	str	r3, [r0, #164]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L9:
	ldr	r1, .L19+8
	add	r2, r0, #164
	add	r3, r0, #324
.L13:
	ldr	ip, [r1, #4]!
	str	ip, [r2, #4]!
	cmp	r2, r3
	bne	.L13
	ldr	r2, .L19+12
	add	ip, r0, #484
.L14:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, ip
	bne	.L14
	mov	r3, #2
	mov	r2, #96
	mov	r1, #3
	str	r3, [r0, #100]
	str	r2, [r0, #516]
	mov	r3, #0
	mov	r2, #5
	str	r3, [r0, #104]
	str	r3, [r0, #108]
	mov	r4, #10
	str	r3, [r0, #112]
	mov	lr, #15
	str	r3, [r0, #116]
	mov	ip, #20
	mov	r3, #255
	str	r1, [r0, #120]
	str	r1, [r0, #124]
	str	r2, [r0, #128]
	str	r2, [r0, #132]
	str	r4, [r0, #136]
	str	lr, [r0, #140]
	str	ip, [r0, #144]
	str	r3, [r0, #148]
	str	r3, [r0, #152]
	str	r3, [r0, #156]
	str	r3, [r0, #160]
	str	r3, [r0, #164]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L20:
	.align	2
.L19:
	.word	.LANCHOR0-4
	.word	.LANCHOR0+156
	.word	.LANCHOR0+316
	.word	.LANCHOR0+476
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_SetDefaultAttrByProtocol, .-DRV_VENC_HAL_SetDefaultAttrByProtocol
	.global	__aeabi_uidiv
	.align	2
	.type	DRV_VENC_HAL_DirectCfgReg, %function
DRV_VENC_HAL_DirectCfgReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #84)
	sub	sp, sp, #84
	ldr	r3, .L87
	mov	r5, r0
	ldr	r2, [r0, #536]
	ldr	r1, [r0, #544]
	ldmia	r3, {r9, r10}
	add	r4, r10, #692
	mov	r0, r4
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	mov	r0, r4
	ldr	r1, [r5, #4]
	add	r4, r10, #4096
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	r3, [r5, #40]
	ldr	r2, [r5, #12]
	cmp	r3, #0
	bne	.L82
.L22:
	ldmib	r5, {r2, r3}
	cmp	r2, #0
	beq	.L83
.L25:
	mov	r3, #0
	mov	r2, #7
	str	r3, [r4, #2328]
	str	r3, [r4, #2324]
	str	r2, [r4, #2320]
.L27:
	ldr	r3, [r5, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	bhi	.L30
	ldr	ip, [r5, #4]
	cmp	ip, #0
	bne	.L30
	add	r3, r10, #7872
	add	r2, r10, #8064
	add	r2, r2, #44
	mov	r1, ip
	mov	r0, r3
	add	r3, r3, #12
	add	r0, r0, #40
	mov	lr, #28
	str	lr, [r5, #552]
	str	lr, [r5, #548]
	str	lr, [r5, #544]
	str	ip, [r10, #792]
	str	ip, [r5, #20]
	str	ip, [r4, #3752]
	str	ip, [r4, #3460]
.L31:
	str	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L31
	b	.L88
.L89:
	.align	2
.L87:
	.word	.LANCHOR1
.L88:
.L30:
	ldr	r2, [r5, #40]
	mov	r3, #11
	mov	lr, #0
	bfc	lr, #0, #1
	bfi	r3, r2, #10, #1
	orr	lr, lr, #2
	bfc	r3, #16, #1
	bfc	lr, #2, #1
	bfc	r3, #17, #1
	mov	ip, #0
	orr	r3, r3, #134217728
	mov	r7, #0
	bfc	r3, #30, #1
	str	r3, [r9, #4]
	ldr	r1, [r5, #4]
	bfc	r7, #0, #9
	ldr	r2, [r5, #40]
	bfc	r7, #16, #9
	subs	r3, r1, #2
	ldr	r0, [r4, #4056]
	ldr	r8, [r4, #2328]
	movne	r3, #1
	bfi	lr, r3, #3, #2
	bfi	lr, r2, #5, #1
	ldr	r3, [r4, #4052]
	ldr	r2, [r5, #536]
	bfi	lr, r0, #6, #1
	bfi	lr, r3, #7, #1
	ldr	r0, [r4, #2428]
	clz	r3, r2
	bfc	lr, #8, #1
	bfc	lr, #24, #1
	cmp	r1, #2
	bfi	lr, r0, #9, #1
	mov	r3, r3, lsr #5
	bfi	lr, r3, #10, #2
	ldr	r3, [r4, #2324]
	bfi	lr, r8, #12, #1
	ldr	r8, [r5, #44]
	bfi	lr, r2, #16, #1
	movne	r0, ip
	orr	lr, lr, #131072
	moveq	r0, #2
	bfi	lr, r3, #18, #2
	mov	r2, ip
	bfc	lr, #21, #1
	bfi	r2, ip, #0, #1
	bfc	lr, #22, #1
	mov	r3, ip
	bfc	lr, #25, #1
	mov	r1, ip
	bfi	lr, r0, #26, #2
	mov	r0, ip
	bfi	lr, r8, #28, #2
	bfi	r0, ip, #8, #2
	bfc	lr, #30, #1
	bfi	r2, ip, #1, #1
	bfc	lr, #31, #1
	str	lr, [r9, #20]
	str	r7, [r9, #24]
	bfi	r0, ip, #4, #4
	ldr	r8, [r5, #20]
	bfc	r1, #0, #5
	ldr	r7, [r5, #28]
	bfc	r1, #5, #5
	bfi	ip, r8, #17, #1
	add	lr, r4, #4096
	bfc	ip, #16, #1
	bfi	r2, r3, #2, #1
	bfi	ip, r7, #0, #16
	str	ip, [r9, #28]
	ldr	ip, [r5, #544]
	bfi	r0, r3, #0, #4
	ldr	r7, [r4, #3460]
	bfi	r2, r3, #3, #1
	bfi	r1, ip, #10, #6
	ldr	ip, [r4, #3444]
	bfi	r1, r7, #18, #1
	orr	r2, r2, #458752
	bfi	r1, ip, #19, #1
	str	r1, [r9, #32]
	str	r3, [r9, #36]
	mov	ip, r3
	str	r3, [r9, #40]
	bfi	ip, r3, #16, #9
	str	r0, [r9, #44]
	mov	r7, r3
	ldr	r8, [lr, #64]
	bfi	ip, r3, #0, #9
	ldr	r0, [lr, #68]
	mov	r1, r3
	bfi	r2, r8, #19, #2
	bfi	r2, r0, #21, #1
	bfi	r2, r3, #23, #1
	str	r2, [r9, #48]
	ldr	r2, [r5, #16]
	ldr	r3, [r5, #12]
	sub	r2, r2, #1
	bfi	r7, r2, #16, #13
	sub	r3, r3, #1
	bfi	r7, r3, #0, #13
	str	r7, [r9, #52]
	str	ip, [r9, #56]
	ldr	r3, [lr, #72]
	str	r3, [r9, #60]
	ldr	r2, [r4, #4068]
	ldr	r3, [r4, #4072]
	bfi	r1, r2, #4, #4
	bfi	r1, r3, #0, #4
	str	r1, [r9, #64]
	ldr	r3, [r5, #4]
	cmp	r3, #2
	beq	.L84
	cmp	r3, #0
	moveq	r3, #15
	moveq	r6, #0
	bfieq	r6, r3, #16, #6
	moveq	r3, #31
	bfieq	r6, r3, #0, #7
.L35:
	mov	r2, #3
	mov	r3, #0
	bfi	r3, r2, #0, #3
	mov	r1, #1
	bfi	r3, r1, #3, #2
	str	r6, [r9, #88]
	bfi	r3, r2, #5, #3
	str	r2, [r9, #92]
	bfi	r3, r2, #8, #3
	mov	r1, #1
	str	r1, [r9, #96]
	mov	lr, #0
	str	r3, [r9, #100]
	mov	r0, lr
	ldr	r7, [r5, #196]
	mov	r1, lr
	mov	ip, lr
	mov	r6, lr
	mov	r3, lr
	bfc	r3, #0, #1
	str	r7, [r9, #184]
	bfc	r3, #1, #1
	ldr	r7, [r5, #68]
	bfc	r3, #2, #1
	bfc	r3, #3, #3
	str	r7, [r9, #188]
	ldr	r7, [r5, #72]
	str	r7, [r9, #192]
	ldr	r7, [r5, #76]
	str	r7, [r9, #196]
	ldr	r8, [r5, #80]
	ldr	r7, [r5, #84]
	bfi	lr, r8, #16, #16
	bfi	lr, r7, #0, #16
	str	lr, [r9, #208]
	ldr	lr, [r5, #168]
	add	lr, r5, lr, lsl #2
	ldr	lr, [lr, #156]
	str	lr, [r9, #212]
	ldr	lr, [r5, #136]
	add	lr, r5, lr, lsl #2
	ldr	lr, [lr, #88]
	str	lr, [r9, #216]
	ldr	lr, [r5, #136]
	add	lr, r5, lr, lsl #2
	ldr	lr, [lr, #96]
	str	lr, [r9, #220]
	ldr	r7, [r5, #104]
	ldr	lr, [r5, #108]
	bfi	ip, r7, #0, #16
	bfi	ip, lr, #16, #16
	str	ip, [r9, #224]
	ldr	ip, [r5, #136]
	add	ip, r5, ip, lsl #2
	ldr	ip, [ip, #112]
	str	ip, [r9, #228]
	ldr	ip, [r5, #136]
	add	ip, r5, ip, lsl #2
	ldr	ip, [ip, #120]
	str	ip, [r9, #232]
	ldr	ip, [r5, #128]
	bfi	r6, ip, #0, #16
	str	r6, [r9, #236]
	ldr	ip, [r5, #136]
	cmp	ip, r0
	moveq	ip, #84
	movne	ip, #80
	add	ip, r5, ip
	ldr	ip, [ip, #8]
	str	ip, [r9, #240]
	ldr	ip, [r5, #136]
	cmp	ip, r0
	moveq	ip, #92
	movne	ip, #88
	add	ip, r5, ip
	ldr	ip, [ip, #8]
	str	ip, [r9, #244]
	ldr	lr, [r5, #108]
	ldr	ip, [r5, #104]
	bfi	r0, lr, #0, #16
	bfi	r0, ip, #16, #16
	str	r0, [r9, #248]
	ldr	r0, [r5, #136]
	cmp	r0, r1
	moveq	r0, #108
	movne	r0, #104
	add	r0, r5, r0
	ldr	r0, [r0, #8]
	str	r0, [r9, #252]
	ldr	r0, [r5, #136]
	cmp	r0, r1
	moveq	r0, #116
	movne	r0, #112
	add	r0, r5, r0
	ldr	r0, [r0, #8]
	str	r0, [r9, #256]
	ldr	ip, [r5, #128]
	ldr	r0, [r5, #132]
	bfi	r1, ip, #16, #16
	bfi	r1, r0, #0, #16
	str	r1, [r9, #260]
	ldr	r1, [r5, #136]
	cmp	r1, #0
	moveq	r1, #148
	movne	r1, #144
	add	r1, r5, r1
	ldr	r1, [r1, #4]
	str	r1, [r9, #264]
	ldr	r1, [r5, #136]
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #148]
	str	r1, [r9, #268]
	ldr	r1, [r5, #136]
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #140]
	str	r1, [r9, #276]
	ldr	r1, [r5, #136]
	cmp	r1, #0
	moveq	r1, #140
	movne	r1, #136
	add	r1, r5, r1
	ldr	r1, [r1, #4]
	str	r1, [r9, #280]
	ldr	r1, [r5, #200]
	str	r1, [r9, #284]
	ldr	r1, [r5, #332]
	str	r1, [r9, #288]
	ldr	r1, [r5, #328]
	str	r1, [r9, #292]
	ldr	r1, [r5, #60]
	cmp	r1, #2
	beq	.L36
	cmp	r1, #1
	beq	.L71
	cmp	r1, #0
	bfc	r3, #6, #4
	bfc	r3, #14, #1
	bne	.L37
	ldr	r2, [r5, #64]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L38:
	bfi	r3, r2, #16, #8
	str	r3, [r9, #296]
	ldr	r1, [r4, #2320]
	mov	r2, #0
	ldr	ip, [r4, #4048]
	mov	r0, #5
	mov	r3, r2
	bfi	r2, r1, #0, #3
	bfc	r3, #0, #1
	mov	r1, #0
	bfi	r1, r0, #24, #8
	bfi	r2, ip, #4, #1
	bfi	r1, r0, #16, #8
	bfc	r3, #1, #1
	mov	ip, #15
	bfc	r2, #5, #1
	bfi	r1, ip, #8, #8
	bfc	r3, #2, #1
	mov	r0, #0
	bfi	r1, ip, #0, #8
	orr	r2, r2, #30464
	orr	r3, r3, #24
	str	r2, [r9, #316]
	movt	r0, 100
	mov	r2, #3
	str	r2, [r9, #320]
	str	r3, [r9, #324]
	mov	r3, #500
	bfi	r0, r3, #0, #16
	str	r0, [r9, #328]
	str	r1, [r9, #332]
	mov	r0, #0
	ldr	r1, [r4, #2432]
	mov	r3, r0
	ldr	r2, [r10, #696]
	mov	ip, r0
	bfi	r0, r1, #0, #1
	ldr	r1, [r10, #692]
	bfi	r0, r2, #1, #1
	mov	r7, r3
	bfi	r0, r1, #2, #1
	mov	lr, r3
	orr	r0, r0, #8
	mov	r1, r3
	bfc	r0, #4, #1
	str	r0, [r9, #352]
	ldr	r6, [r5, #684]
	mov	r0, #128
	bfi	r7, r0, #0, #10
	mvn	r2, #127
	bfi	r1, r2, #0, #8
	mov	r8, #2
	str	r6, [r9, #392]
	bfi	r1, r2, #8, #8
	ldr	r6, [r4, #3436]
	bfi	lr, r2, #0, #8
	ldr	r0, [r4, #3440]
	bfi	r1, r2, #16, #8
	bfi	r3, r6, #0, #1
	ldr	r6, [r10, #784]
	bfi	r3, r0, #1, #1
	ldr	r0, [r4, #3456]
	bfi	r3, r6, #2, #1
	ldr	r6, [r10, #780]
	bfi	r3, r0, #4, #1
	ldr	r0, [r4, #3432]
	bfi	r3, r6, #8, #1
	ldr	r6, [r4, #3504]
	bfi	r3, r0, #9, #1
	ldr	r0, [r4, #3508]
	bfi	r3, r6, #10, #1
	ldr	r6, [r4, #3512]
	bfi	r3, r0, #11, #1
	ldr	r0, [r4, #3428]
	bfi	r3, r6, #12, #1
	ldr	r6, [r4, #3424]
	bfi	r3, r0, #13, #1
	ldr	r0, [r4, #3516]
	bfi	r3, r6, #14, #1
	mov	r6, ip
	bfi	r3, r0, #15, #1
	str	r3, [r9, #440]
	ldr	r3, [r10, #788]
	bfc	r6, #0, #1
	bfi	lr, r2, #8, #8
	bfc	r6, #1, #8
	bfi	ip, r3, #1, #1
	mov	r2, #128
	bfi	ip, r8, #16, #8
	bfi	r7, r2, #10, #10
	bfi	ip, r8, #24, #8
	str	ip, [r9, #444]
	str	r1, [r9, #464]
	movw	r0, #43691
	str	lr, [r9, #468]
	movt	r0, 43690
	str	r7, [r9, #472]
	mov	lr, #1
	str	r6, [r9, #476]
	mov	r3, #0
	ldr	r1, [r5, #168]
	mov	ip, r3
	mov	r2, r3
	str	r3, [fp, #-68]
	add	r1, r1, r8
	str	r3, [fp, #-72]
	str	r3, [fp, #-76]
	umull	r6, r7, r1, r0
	mov	r6, r7, lsr lr
	add	r6, r6, r6, lsl #1
	rsb	r1, r6, r1
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #156]
	str	r1, [r9, #480]
	ldr	r6, [r5, #168]
	add	r6, r6, lr
	umull	r0, r1, r6, r0
	mov	r1, r1, lsr lr
	add	r1, r1, r1, lsl #1
	rsb	r1, r1, r6
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #156]
	str	r1, [r9, #484]
	str	lr, [r9, #492]
	ldrb	r1, [r4, #3812]
	ldrb	r6, [r4, #3820]
	ldrb	r0, [r4, #3816]
	mov	lr, r1
	ldrb	r7, [r4, #3808]
	ldrb	r8, [r4, #3804]
	orr	r1, r0, r6
	orr	r1, lr, r1
	str	lr, [fp, #-52]
	orr	r1, r7, r1
	ldrb	lr, [r4, #3800]
	str	r8, [fp, #-56]
	orr	r1, r8, r1
	ldrb	r8, [r4, #3796]
	orr	r1, lr, r1
	str	r6, [fp, #-48]
	ldrb	r6, [r4, #3792]
	orr	r1, r8, r1
	str	r8, [fp, #-60]
	mov	r8, ip
	orr	r1, r6, r1
	bfi	r3, r1, #24, #1
	ldr	r1, [r4, #4044]
	str	r6, [fp, #-64]
	bfi	r3, r1, #23, #1
	ldr	r1, [r4, #4040]
	bfi	r3, r1, #22, #1
	ldr	r1, [r4, #4036]
	bfi	r3, r1, #21, #1
	ldr	r1, [r4, #4032]
	bfi	r3, r1, #20, #1
	ldr	r1, [r4, #4028]
	bfi	r3, r1, #19, #1
	ldr	r1, [r4, #4024]
	bfi	r3, r1, #18, #1
	ldr	r1, [r4, #4020]
	bfi	r3, r1, #17, #1
	ldr	r1, [r4, #4016]
	bfi	r3, r1, #16, #1
	ldr	r1, [r4, #3852]
	bfi	r3, r1, #15, #1
	ldr	r1, [r4, #3848]
	bfi	r3, r1, #14, #1
	ldr	r1, [r4, #3844]
	ldr	r6, [fp, #-48]
	bfi	r3, r1, #13, #1
	ldr	r1, [r4, #3840]
	str	ip, [fp, #-48]
	bfi	r3, r1, #12, #1
	ldr	r1, [r4, #3836]
	bfi	r3, r1, #11, #1
	ldr	r1, [r4, #3832]
	bfi	r3, r1, #10, #1
	ldr	r1, [r4, #3828]
	bfi	r3, r1, #9, #1
	ldr	r1, [r4, #3824]
	bfi	r3, r1, #8, #1
	ldr	r1, [fp, #-52]
	bfi	r3, r6, #7, #1
	mov	r6, ip
	bfi	r3, r0, #6, #1
	ldr	r0, [fp, #-56]
	bfi	r3, r1, #5, #1
	str	r2, [fp, #-52]
	bfi	r3, r7, #4, #1
	mov	r7, ip
	bfi	r3, r0, #3, #1
	ldr	r0, [fp, #-60]
	bfi	r3, lr, #2, #1
	mov	lr, ip
	bfi	r3, r0, #1, #1
	ldr	r0, [fp, #-64]
	str	r8, [fp, #-56]
	bfi	r3, r0, #0, #1
	str	r3, [r9, #512]
	ldr	r3, [r4, #3868]
	ldr	r1, [r4, #3864]
	ldr	r0, [r4, #3860]
	bfi	ip, r3, #24, #7
	bfi	ip, r1, #16, #7
	ldr	r3, [r4, #3856]
	bfi	ip, r0, #8, #7
	bfi	ip, r3, #0, #7
	str	ip, [r9, #516]
	ldr	r3, [r4, #3884]
	mov	ip, r2
	ldr	r1, [r4, #3880]
	ldr	r0, [r4, #3876]
	bfi	r2, r3, #24, #7
	bfi	r2, r1, #16, #7
	ldr	r3, [r4, #3872]
	bfi	r2, r0, #8, #7
	mov	r1, r8
	bfi	r2, r3, #0, #7
	str	r2, [r9, #520]
	ldr	r2, [r4, #3920]
	mov	r0, r8
	ldr	r3, [r4, #3888]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #524]
	ldr	r2, [r4, #3924]
	mov	r1, r8
	ldr	r3, [r4, #3892]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #528]
	ldr	r2, [r4, #3928]
	mov	r1, r8
	ldr	r3, [r4, #3896]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #532]
	ldr	r2, [r4, #3932]
	mov	r1, r8
	ldr	r3, [r4, #3900]
	bfi	r8, r2, #16, #10
	bfi	r8, r3, #0, #10
	str	r8, [r9, #536]
	ldr	r2, [r4, #3936]
	mov	r8, r7
	ldr	r3, [r4, #3904]
	bfi	r7, r2, #16, #10
	mov	r2, r6
	bfi	r7, r3, #0, #10
	str	r7, [r9, #540]
	ldr	r7, [r4, #3940]
	ldr	r3, [r4, #3908]
	bfi	r6, r7, #16, #10
	bfi	r6, r3, #0, #10
	str	r6, [r9, #544]
	ldr	r7, [r4, #3944]
	mov	r3, lr
	ldr	r6, [r4, #3912]
	bfi	lr, r7, #16, #10
	mov	r7, ip
	bfi	lr, r6, #0, #10
	str	lr, [r9, #548]
	ldr	r6, [r4, #3948]
	ldr	lr, [r4, #3916]
	bfi	r7, r6, #16, #10
	bfi	r7, lr, #0, #10
	str	r7, [r9, #552]
	ldr	r6, [r4, #3984]
	mov	r7, ip
	ldr	lr, [r4, #3952]
	bfi	r7, r6, #16, #9
	bfi	r7, lr, #0, #9
	str	r7, [r9, #556]
	ldr	r6, [r4, #3988]
	mov	r7, ip
	ldr	lr, [r4, #3956]
	bfi	r7, r6, #16, #9
	bfi	r7, lr, #0, #9
	str	r7, [r9, #560]
	ldr	r6, [r4, #3992]
	ldr	lr, [r4, #3960]
	bfi	ip, r6, #16, #9
	bfi	ip, lr, #0, #9
	str	ip, [r9, #564]
	ldr	lr, [r4, #3996]
	ldr	ip, [r4, #3964]
	bfi	r0, lr, #16, #9
	bfi	r0, ip, #0, #9
	str	r0, [r9, #568]
	ldr	ip, [r4, #4000]
	ldr	r0, [r4, #3968]
	bfi	r1, ip, #16, #9
	bfi	r1, r0, #0, #9
	str	r1, [r9, #572]
	ldr	r0, [r4, #4004]
	ldr	r1, [r4, #3972]
	bfi	r8, r0, #16, #9
	bfi	r8, r1, #0, #9
	str	r8, [r9, #576]
	ldr	r0, [r4, #4008]
	ldr	r1, [r4, #3976]
	bfi	r2, r0, #16, #9
	bfi	r2, r1, #0, #9
	str	r2, [r9, #580]
	ldr	r1, [r4, #4012]
	ldr	r2, [r4, #3980]
	bfi	r3, r1, #16, #9
	bfi	r3, r2, #0, #9
	str	r3, [r9, #584]
	ldr	r3, [r5, #4]
	ldr	r0, [r5, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r6, #16
	movne	r6, #64
	mov	r1, r6
	add	r0, r0, r6
	bl	__aeabi_uidiv
	ldr	r3, [r5, #16]
	mov	r1, r6
	mov	r7, r0
	sub	r0, r3, #1
	add	r0, r0, r6
	bl	__aeabi_uidiv
	mul	r1, r7, r0
	ldr	r0, [r5, #540]
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r8, r3
	mov	r2, r3
	mov	r6, r3
	str	r3, [fp, #-56]
	mov	r1, r3
	str	r3, [fp, #-60]
	mov	ip, r3
	str	r3, [fp, #-64]
	mov	lr, r3
	str	r3, [fp, #-68]
	str	r3, [fp, #-72]
	mov	r7, r3
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
	bfi	r3, r0, #0, #20
	str	r3, [r9, #588]
	ldr	r0, [r4, #2436]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2440]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #640]
	ldr	r0, [r10, #700]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2444]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #644]
	ldr	r0, [r4, #2448]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2452]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #648]
	ldr	r0, [r4, #2456]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #704]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #652]
	ldr	r0, [r4, #2460]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2464]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #656]
	ldr	r0, [r10, #708]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #712]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #660]
	ldr	r0, [r4, #2468]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2472]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #664]
	ldr	r0, [r10, #716]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #720]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #668]
	ldr	r0, [r4, #2476]
	mov	r3, r6
	bfi	lr, r0, #12, #4
	ldr	r0, [r4, #2480]
	bfi	lr, r0, #8, #4
	ldr	r0, [r4, #2484]
	bfi	lr, r0, #4, #4
	ldr	r0, [r4, #2488]
	bfi	lr, r0, #0, #4
	ldr	r0, [r4, #2492]
	bfi	lr, r0, #28, #4
	ldr	r0, [r10, #724]
	bfi	lr, r0, #24, #4
	ldr	r0, [r4, #2496]
	bfi	lr, r0, #20, #4
	ldr	r0, [r4, #2500]
	bfi	lr, r0, #16, #4
	str	lr, [r9, #672]
	ldr	r0, [r4, #2504]
	mov	lr, r8
	bfi	ip, r0, #12, #4
	ldr	r0, [r4, #2508]
	bfi	ip, r0, #8, #4
	ldr	r0, [r4, #2512]
	bfi	ip, r0, #4, #4
	ldr	r0, [r4, #2516]
	bfi	ip, r0, #0, #4
	ldr	r0, [r4, #2520]
	bfi	ip, r0, #28, #4
	ldr	r0, [r4, #2524]
	bfi	ip, r0, #24, #4
	ldr	r0, [r10, #728]
	bfi	ip, r0, #20, #4
	ldr	r0, [r4, #2528]
	bfi	ip, r0, #16, #4
	str	ip, [r9, #676]
	ldr	r0, [r4, #2532]
	mov	ip, r6
	bfi	r1, r0, #12, #4
	ldr	r0, [r4, #2536]
	bfi	r1, r0, #8, #4
	ldr	r0, [r4, #2540]
	bfi	r1, r0, #4, #4
	ldr	r0, [r4, #2544]
	bfi	r1, r0, #0, #4
	ldr	r0, [r4, #2548]
	bfi	r1, r0, #28, #4
	ldr	r0, [r4, #2552]
	bfi	r1, r0, #24, #4
	ldr	r0, [r10, #732]
	bfi	r1, r0, #20, #4
	ldr	r0, [r4, #2556]
	bfi	r1, r0, #16, #4
	str	r1, [r9, #680]
	ldr	r1, [r4, #2560]
	mov	r0, r8
	bfi	r2, r1, #12, #4
	ldr	r1, [r10, #736]
	bfi	r2, r1, #8, #4
	ldr	r1, [r4, #2564]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #2568]
	bfi	r2, r1, #0, #4
	ldr	r1, [r4, #2572]
	bfi	r2, r1, #28, #4
	ldr	r1, [r4, #2576]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #2580]
	bfi	r2, r1, #20, #4
	ldr	r1, [r4, #2584]
	bfi	r2, r1, #16, #4
	str	r2, [r9, #684]
	ldr	r2, [r4, #2588]
	mov	r1, r8
	bfi	r3, r2, #12, #4
	ldr	r2, [r4, #2592]
	bfi	r3, r2, #8, #4
	ldr	r2, [r10, #740]
	bfi	r3, r2, #4, #4
	ldr	r2, [r4, #2596]
	bfi	r3, r2, #0, #4
	ldr	r2, [r4, #2600]
	bfi	r3, r2, #28, #4
	ldr	r2, [r4, #2604]
	bfi	r3, r2, #24, #4
	ldr	r2, [r4, #2608]
	bfi	r3, r2, #20, #4
	ldr	r2, [r4, #2612]
	bfi	r3, r2, #16, #4
	str	r3, [r9, #688]
	ldr	r3, [r4, #2616]
	mov	r2, r6
	bfi	r2, r3, #12, #4
	ldr	r3, [r4, #2620]
	bfi	r2, r3, #8, #4
	ldr	r3, [r10, #744]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2624]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2628]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2632]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2636]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2640]
	bfi	r2, r3, #16, #4
	str	r2, [r9, #692]
	ldr	r3, [r4, #2644]
	mov	r2, r6
	bfi	r2, r3, #12, #4
	ldr	r3, [r10, #748]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2648]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2652]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2656]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2660]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2664]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2668]
	bfi	r2, r3, #16, #4
	str	r2, [r9, #696]
	ldr	r3, [r4, #2672]
	mov	r2, r8
	bfi	r7, r3, #12, #4
	ldr	r3, [r4, #2676]
	bfi	r7, r3, #8, #4
	ldr	r3, [r4, #2680]
	bfi	r7, r3, #4, #4
	ldr	r3, [r4, #2684]
	bfi	r7, r3, #0, #4
	ldr	r3, [r4, #2688]
	bfi	r7, r3, #28, #4
	ldr	r3, [r4, #2692]
	bfi	r7, r3, #24, #4
	ldr	r3, [r4, #2696]
	bfi	r7, r3, #20, #4
	ldr	r3, [r4, #2700]
	bfi	r7, r3, #16, #4
	str	r7, [r9, #700]
	ldr	r3, [r4, #2704]
	mov	r7, r8
	bfi	r6, r3, #12, #4
	ldr	r3, [r4, #2708]
	bfi	r6, r3, #8, #4
	ldr	r3, [r4, #2712]
	bfi	r6, r3, #4, #4
	ldr	r3, [r4, #2716]
	bfi	r6, r3, #0, #4
	ldr	r3, [r4, #2720]
	bfi	r6, r3, #28, #4
	ldr	r3, [r4, #2724]
	bfi	r6, r3, #24, #4
	ldr	r3, [r4, #2728]
	bfi	r6, r3, #20, #4
	ldr	r3, [r4, #2732]
	bfi	r6, r3, #16, #4
	str	r6, [r9, #704]
	ldr	r3, [r4, #2736]
	mov	r6, r8
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2740]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2744]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2748]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2752]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2756]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2760]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #708]
	ldr	r3, [r4, #2764]
	mov	r2, r8
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2768]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2772]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2776]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2780]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2784]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2788]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #712]
	ldr	r3, [r4, #2792]
	mov	r2, r8
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2796]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2800]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2804]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2808]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2812]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2816]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #716]
	ldr	r3, [r4, #3084]
	mov	r2, r8
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #3088]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #3092]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #3096]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #3100]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #3104]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #3108]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #720]
	ldr	r3, [r4, #3112]
	mov	r2, r8
	bfi	r6, r3, #0, #3
	ldr	r3, [r4, #3116]
	bfi	r6, r3, #3, #7
	ldr	r3, [r4, #3120]
	bfi	r6, r3, #10, #3
	ldr	r3, [r4, #3124]
	bfi	r6, r3, #13, #5
	ldr	r3, [r4, #3128]
	bfi	r6, r3, #18, #4
	ldr	r3, [r4, #3132]
	bfi	r6, r3, #22, #4
	ldr	r3, [r4, #3136]
	bfi	r6, r3, #26, #4
	str	r6, [r9, #724]
	ldr	r6, [r10, #760]
	mov	r3, r8
	bfi	r7, r6, #0, #3
	ldr	r6, [r4, #3140]
	bfi	r7, r6, #3, #7
	ldr	r6, [r4, #3144]
	bfi	r7, r6, #10, #3
	ldr	r6, [r4, #3148]
	bfi	r7, r6, #13, #5
	ldr	r6, [r4, #3152]
	bfi	r7, r6, #18, #4
	ldr	r6, [r4, #3156]
	bfi	r7, r6, #22, #4
	ldr	r6, [r4, #3160]
	bfi	r7, r6, #26, #4
	str	r7, [r9, #728]
	ldr	r6, [r4, #3164]
	mov	r7, r8
	bfi	r7, r6, #0, #3
	ldr	r6, [r4, #3168]
	bfi	r7, r6, #3, #7
	ldr	r6, [r4, #3172]
	bfi	r7, r6, #10, #3
	ldr	r6, [r4, #3176]
	bfi	r7, r6, #13, #5
	ldr	r6, [r4, #3180]
	bfi	r7, r6, #18, #4
	ldr	r6, [r4, #3184]
	bfi	r7, r6, #22, #4
	ldr	r6, [r4, #3188]
	bfi	r7, r6, #26, #4
	str	r7, [r9, #732]
	ldr	r6, [r4, #2820]
	mov	r7, r8
	bfi	r8, r6, #0, #4
	ldr	r6, [r4, #2824]
	bfi	r8, r6, #4, #4
	ldr	r6, [r4, #2828]
	bfi	r8, r6, #8, #4
	ldr	r6, [r4, #2832]
	bfi	r8, r6, #12, #4
	ldr	r6, [r4, #2836]
	bfi	r8, r6, #16, #4
	ldr	r6, [r4, #2840]
	bfi	r8, r6, #20, #4
	ldr	r6, [r4, #2844]
	bfi	r8, r6, #24, #4
	ldr	r6, [r4, #2848]
	bfi	r8, r6, #28, #4
	str	r8, [r9, #736]
	ldr	r6, [r4, #2852]
	bfi	r7, r6, #0, #4
	ldr	r6, [r4, #2856]
	bfi	r7, r6, #4, #4
	ldr	r6, [r4, #2860]
	bfi	r7, r6, #8, #4
	ldr	r6, [r4, #2864]
	bfi	r7, r6, #12, #4
	ldr	r6, [r4, #2868]
	bfi	r7, r6, #16, #4
	ldr	r6, [r4, #2872]
	bfi	r7, r6, #20, #4
	str	r7, [r9, #740]
	ldr	r6, [r4, #2876]
	mov	r7, ip
	bfi	ip, r6, #0, #10
	ldr	r6, [r4, #2880]
	bfi	ip, r6, #16, #5
	str	ip, [r9, #744]
	ldr	ip, [r10, #752]
	mov	r6, lr
	bfi	lr, ip, #0, #8
	ldr	ip, [r10, #756]
	bfi	lr, ip, #16, #5
	str	lr, [r9, #748]
	ldr	ip, [r4, #2884]
	mov	lr, r1
	bfi	r1, ip, #0, #10
	ldr	ip, [r4, #2888]
	bfi	r1, ip, #16, #5
	str	r1, [r9, #752]
	ldr	r1, [r4, #2892]
	mov	ip, r0
	bfi	r0, r1, #0, #8
	ldr	r1, [r4, #2896]
	bfi	r0, r1, #16, #5
	str	r0, [r9, #756]
	ldr	r1, [r4, #2900]
	mov	r0, r2
	bfi	r7, r1, #0, #10
	ldr	r1, [r4, #2904]
	bfi	r7, r1, #16, #5
	str	r7, [r9, #760]
	ldr	r7, [r4, #2908]
	mov	r1, r2
	bfi	r2, r7, #0, #8
	ldr	r7, [r4, #2912]
	bfi	r2, r7, #16, #5
	str	r2, [r9, #764]
	ldr	r7, [r4, #3192]
	mov	r2, r3
	bfi	r3, r7, #0, #4
	ldr	r7, [r4, #3196]
	bfi	r3, r7, #4, #4
	ldr	r7, [r4, #3200]
	bfi	r3, r7, #8, #4
	ldr	r7, [r4, #3204]
	bfi	r3, r7, #12, #4
	ldr	r7, [r4, #3208]
	bfi	r3, r7, #16, #4
	ldr	r7, [r4, #3212]
	bfi	r3, r7, #20, #4
	str	r3, [r9, #768]
	ldr	r7, [r10, #764]
	mov	r3, r6
	bfi	r3, r7, #0, #12
	ldr	r7, [r10, #768]
	bfi	r3, r7, #12, #12
	ldr	r7, [r4, #3216]
	bfi	r3, r7, #24, #8
	str	r3, [r9, #772]
	ldr	r8, [r4, #3220]
	mov	r3, r6
	bfc	r3, #14, #1
	str	r3, [fp, #-48]
	mov	r3, r6
	bfi	r3, r8, #0, #12
	ldr	r8, [r4, #3224]
	ldr	r7, [fp, #-48]
	bfi	r3, r8, #12, #12
	ldr	r8, [r4, #3228]
	bfc	r7, #15, #1
	str	r7, [fp, #-48]
	bfi	r3, r8, #24, #8
	str	r3, [r9, #776]
	ldr	r8, [r10, #772]
	mov	r7, r6
	mov	r3, r6
	bfc	r3, #0, #8
	bfi	r7, r8, #0, #12
	ldr	r8, [r4, #3232]
	orr	r3, r3, #65280
	bfi	r7, r8, #12, #12
	ldr	r8, [r4, #3236]
	movt	r3, 65280
	str	r3, [fp, #-52]
	mov	r3, r7
	bfi	r3, r8, #24, #8
	str	r3, [r9, #780]
	mov	r3, r6
	ldr	r8, [r4, #3240]
	bfi	r3, r8, #0, #8
	ldr	r8, [r4, #3244]
	bfi	r3, r8, #8, #8
	ldr	r8, [r4, #3248]
	bfi	r3, r8, #16, #8
	str	r3, [r9, #784]
	ldr	r8, [r4, #2916]
	mov	r3, r6
	bfi	r6, r8, #0, #1
	ldr	r8, [r4, #2920]
	bfi	r6, r8, #1, #3
	ldr	r8, [r4, #2924]
	bfi	r6, r8, #4, #6
	ldr	r8, [r4, #2928]
	bfi	r6, r8, #10, #5
	ldr	r8, [r4, #2932]
	bfi	r6, r8, #15, #6
	ldr	r8, [r4, #2936]
	bfi	r6, r8, #21, #5
	str	r6, [r9, #788]
	ldr	r6, [r4, #2940]
	mov	r8, lr
	mov	r7, r8
	bfi	lr, r6, #0, #1
	ldr	r6, [r4, #2944]
	bfi	lr, r6, #1, #3
	ldr	r6, [r4, #2948]
	bfi	lr, r6, #4, #6
	ldr	r6, [r4, #2952]
	bfi	lr, r6, #10, #5
	ldr	r6, [r4, #2956]
	bfi	lr, r6, #15, #6
	ldr	r6, [r4, #2960]
	bfi	lr, r6, #21, #5
	str	lr, [r9, #792]
	ldr	lr, [r4, #2964]
	mov	r6, ip
	bfi	ip, lr, #0, #1
	ldr	lr, [r4, #2968]
	bfi	ip, lr, #1, #3
	ldr	lr, [r4, #2972]
	bfi	ip, lr, #4, #6
	ldr	lr, [r4, #2976]
	bfi	ip, lr, #10, #5
	ldr	lr, [r4, #2980]
	bfi	ip, lr, #15, #6
	ldr	lr, [r4, #2984]
	bfi	ip, lr, #21, #5
	str	ip, [r9, #796]
	ldr	ip, [r4, #2988]
	mov	lr, r0
	bfi	r0, ip, #0, #1
	ldr	ip, [r4, #2992]
	bfi	r0, ip, #1, #3
	ldr	ip, [r4, #2996]
	bfi	r0, ip, #4, #6
	ldr	ip, [r4, #3000]
	bfi	r0, ip, #10, #5
	ldr	ip, [r4, #3004]
	bfi	r0, ip, #15, #6
	ldr	ip, [r4, #3008]
	bfi	r0, ip, #21, #5
	str	r0, [r9, #800]
	ldr	r0, [r4, #3012]
	mov	ip, r8
	bfi	r1, r0, #0, #1
	ldr	r0, [r4, #3016]
	bfi	r1, r0, #1, #3
	ldr	r0, [r4, #3020]
	bfi	r1, r0, #4, #6
	ldr	r0, [r4, #3024]
	bfi	r1, r0, #10, #5
	ldr	r0, [r4, #3028]
	bfi	r1, r0, #15, #6
	ldr	r0, [r4, #3032]
	bfi	r1, r0, #21, #5
	str	r1, [r9, #804]
	ldr	r0, [r4, #3036]
	mov	r1, r2
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #3040]
	bfi	r2, r0, #1, #3
	ldr	r0, [r4, #3044]
	bfi	r2, r0, #4, #6
	ldr	r0, [r4, #3048]
	bfi	r2, r0, #10, #5
	ldr	r0, [r4, #3052]
	bfi	r2, r0, #15, #6
	ldr	r0, [r4, #3056]
	bfi	r2, r0, #21, #5
	str	r2, [r9, #808]
	ldr	r2, [r4, #3060]
	mov	r0, r8
	bfi	r3, r2, #0, #1
	ldr	r2, [r4, #3064]
	bfi	r3, r2, #1, #3
	ldr	r2, [r4, #3068]
	bfi	r3, r2, #4, #6
	ldr	r2, [r4, #3072]
	bfi	r3, r2, #10, #5
	ldr	r2, [r4, #3076]
	bfi	r3, r2, #15, #6
	ldr	r2, [r4, #3080]
	bfi	r3, r2, #21, #5
	ldr	r2, [fp, #-48]
	str	r3, [r9, #812]
	ldr	r3, [r4, #2316]
	bfi	r2, r3, #20, #8
	ldr	r3, [r5, #40]
	bfi	r2, r3, #28, #1
	ldr	r3, [fp, #-52]
	str	r2, [r9, #1024]
	mov	r2, r8
	str	r8, [fp, #-52]
	str	r3, [r9, #1120]
	ldr	r3, [r4, #3572]
	bfi	r2, r3, #0, #1
	str	r2, [r9, #1536]
	ldr	r3, [r4, #3576]
	mov	r2, r8
	bfi	r2, r3, #0, #16
	str	r2, [r9, #1540]
	ldr	r3, [r4, #3580]
	mov	r2, r8
	bfi	r2, r3, #0, #16
	str	r2, [r9, #1544]
	ldr	r3, [r4, #3584]
	mov	r2, r8
	bfi	r2, r3, #0, #16
	str	r2, [r9, #1548]
	ldr	r3, [r4, #3588]
	mov	r2, r8
	bfi	lr, r3, #18, #9
	ldr	r3, [r4, #3592]
	bfi	lr, r3, #9, #9
	ldr	r3, [r4, #3596]
	bfi	lr, r3, #0, #9
	str	lr, [r9, #1556]
	ldr	r3, [r4, #3600]
	mov	lr, r8
	bfi	r6, r3, #16, #8
	ldr	r3, [r4, #3604]
	bfi	r6, r3, #8, #8
	ldr	r3, [r4, #3608]
	bfi	r6, r3, #0, #8
	str	r6, [r9, #1560]
	ldr	r3, [r4, #3612]
	mov	r6, r8
	bfi	r1, r3, #8, #4
	ldr	r3, [r4, #3616]
	bfi	r1, r3, #4, #4
	ldr	r3, [r4, #3620]
	bfi	r1, r3, #0, #4
	mov	r3, #3
	bfi	r1, r3, #20, #8
	mov	r3, r8
	mov	r8, #20
	bfi	r1, r8, #12, #8
	str	r1, [r9, #1564]
	mov	r1, r7
	ldr	r8, [r4, #3720]
	bfi	r1, r8, #0, #16
	mov	r8, r7
	bfc	r1, #16, #8
	bfc	r1, #24, #8
	str	r1, [r9, #1568]
	ldr	r1, [r4, #3736]
	bfi	r7, r1, #0, #8
	ldr	r1, [r4, #3732]
	bfi	r7, r1, #8, #8
	ldr	r1, [r4, #3728]
	bfi	r7, r1, #16, #8
	ldr	r1, [r4, #3724]
	bfi	r7, r1, #24, #8
	str	r7, [r9, #1572]
	ldr	r7, [r4, #3624]
	mov	r1, ip
	bfi	ip, r7, #24, #8
	ldr	r7, [r4, #3628]
	bfi	ip, r7, #16, #8
	ldr	r7, [r4, #3632]
	bfi	ip, r7, #8, #8
	ldr	r7, [r4, #3636]
	bfi	ip, r7, #0, #8
	str	ip, [r9, #1584]
	ldr	ip, [r4, #3640]
	mov	r7, r0
	bfi	r0, ip, #0, #8
	ldr	ip, [r4, #3644]
	bfi	r0, ip, #8, #8
	ldr	ip, [r4, #3648]
	bfi	r0, ip, #16, #1
	ldr	ip, [r4, #3764]
	bfi	r0, ip, #17, #1
	str	r0, [r9, #1588]
	ldr	ip, [r4, #3652]
	mov	r0, r2
	bfi	r7, ip, #0, #16
	ldr	ip, [r4, #3656]
	bfi	r7, ip, #16, #16
	str	r7, [r9, #1592]
	ldr	ip, [r10, #1180]
	mov	r7, r2
	bfi	r2, ip, #22, #9
	ldr	ip, [r10, #1184]
	bfi	r2, ip, #17, #5
	ldr	ip, [r10, #1188]
	bfi	r2, ip, #9, #8
	ldr	ip, [r10, #1208]
	bfi	r2, ip, #0, #9
	str	r2, [r9, #1596]
	ldr	r2, [r10, #1204]
	bfi	lr, r2, #8, #14
	ldr	r2, [r4, #3660]
	bfi	lr, r2, #0, #8
	str	lr, [r9, #1732]
	ldr	ip, [r10, #1192]
	mov	r2, r6
	bfi	r6, ip, #16, #8
	ldr	ip, [r10, #1196]
	bfi	r6, ip, #8, #8
	ldr	ip, [r10, #1200]
	bfi	r6, ip, #0, #8
	str	r6, [r9, #1736]
	ldr	lr, [r4, #3668]
	mov	ip, r3
	mov	r6, r8
	bfi	r3, lr, #17, #1
	ldr	lr, [r4, #3672]
	bfi	r3, lr, #12, #2
	ldr	lr, [r4, #3676]
	bfi	r3, lr, #4, #4
	ldr	lr, [r4, #3680]
	bfi	r3, lr, #0, #4
	str	r3, [r9, #1740]
	ldr	r3, [r4, #3684]
	mov	lr, #1
	bfi	r6, r3, #0, #10
	ldr	r3, [r4, #3688]
	bfi	r6, r3, #16, #9
	str	r6, [r9, #1744]
	ldr	r6, [r4, #3692]
	mov	r3, r8
	bfi	r3, lr, #0, #8
	mov	lr, r8
	bfi	lr, r6, #0, #10
	ldr	r6, [r4, #3696]
	str	r6, [fp, #-48]
	mov	r6, #1
	bfi	r3, r6, #8, #8
	ldr	r6, [fp, #-48]
	bfi	lr, r6, #16, #9
	str	lr, [r9, #1748]
	ldr	lr, [r4, #3700]
	movt	r3, 200
	ldr	r6, [r4, #3704]
	bfi	r8, lr, #0, #10
	mov	lr, r1
	bfi	r8, r6, #16, #9
	str	r8, [r9, #1752]
	ldr	r8, [r4, #3708]
	ldr	r6, [r4, #3712]
	bfi	r1, r8, #0, #10
	bfi	r1, r6, #16, #9
	str	r1, [r9, #1756]
	ldr	r1, [r4, #3716]
	mov	r6, r0
	bfi	r6, r1, #0, #16
	str	r6, [r9, #1776]
	ldr	r6, [r4, #3740]
	ldr	r1, [r4, #3744]
	bfi	r0, r6, #0, #13
	bfi	r0, r1, #13, #1
	str	r0, [r9, #1780]
	ldr	r1, [r4, #3748]
	mov	r0, r7
	bfi	r0, r1, #0, #18
	str	r0, [r9, #1784]
	ldr	r1, [r4, #3752]
	bfi	r7, r1, #0, #18
	str	r7, [r9, #1788]
	ldr	r0, [r4, #3776]
	ldr	r1, [r4, #3780]
	bfi	r2, r0, #16, #7
	bfi	r2, r1, #23, #7
	str	r2, [r9, #1792]
	ldr	r2, [r4, #3768]
	ldr	r1, [r4, #3772]
	bfi	ip, r2, #0, #8
	ldr	r2, [r4, #3756]
	bfi	ip, r1, #8, #8
	bfi	ip, r2, #16, #8
	str	ip, [r9, #1796]
	ldr	r2, [r4, #3760]
	ldr	r1, [r4, #3784]
	bfi	lr, r2, #12, #8
	ldr	r2, [r4, #3788]
	bfi	lr, r1, #8, #4
	bfi	lr, r2, #0, #8
	str	lr, [r9, #1800]
	str	r3, [r9, #1804]
	ldr	r2, [r5, #4]
	cmp	r2, #0
	bne	.L40
	mov	r1, #23
	mov	r3, #0
	bfi	r3, r1, #0, #5
	mov	r0, #15
	bfi	r3, r0, #5, #5
	bfi	r3, r1, #10, #5
	bfi	r3, r0, #15, #5
	bfi	r3, r2, #20, #1
	str	r3, [r9, #2052]
.L41:
	mov	r1, #16
	mov	r3, #0
	mov	r2, #0
	bfc	r3, #16, #16
	bfi	r2, r1, #6, #6
	bfc	r3, #0, #16
	mov	r0, #2
	mov	r1, #10
	str	r0, [r9, #2560]
	bfi	r2, r1, #0, #6
	str	r3, [r9, #2592]
	mov	r3, #0
	str	r2, [r9, #2596]
	mov	r8, #0
	ldr	r2, [r5, #552]
	ldr	r0, [r5, #548]
	bfi	r3, r2, #8, #6
	ldr	r1, [r4, #3380]
	orr	r3, r3, #64
	ldr	r2, [r4, #3352]
	bfi	r3, r0, #0, #6
	bfi	r3, r1, #16, #6
	bfi	r3, r2, #24, #4
	str	r3, [r9, #3076]
	ldr	r3, [r5, #4]
	ldr	r0, [r5, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r6, #16
	movne	r6, #64
	mov	r1, r6
	add	r0, r0, r6
	bl	__aeabi_uidiv
	ldr	r3, [r5, #16]
	mov	r1, r6
	mov	r7, r0
	sub	r0, r3, #1
	add	r0, r0, r6
	mov	r6, r8
	bl	__aeabi_uidiv
	mul	r1, r7, r0
	ldr	r0, [r5, #540]
	bl	__aeabi_uidiv
	mov	r7, r8
	mov	lr, r8
	mov	ip, r8
	mov	r1, r8
	mov	r2, r8
	mov	r3, r8
	str	r8, [fp, #-48]
	bfi	r8, r0, #0, #16
	ldr	r0, [r4, #3368]
	bfi	r8, r0, #16, #6
	str	r8, [r9, #3080]
	ldr	r0, [r10, #792]
	ldr	r8, [r4, #3360]
	bfi	lr, r0, #0, #6
	ldr	r0, [r4, #3372]
	bfi	lr, r8, #24, #6
	ldr	r8, [r4, #3364]
	bfi	lr, r8, #16, #6
	bfi	lr, r0, #8, #6
	str	lr, [r9, #3084]
	ldr	r0, [r10, #808]
	ldr	lr, [r10, #804]
	ldr	r8, [r10, #800]
	bfi	ip, r0, #24, #8
	bfi	ip, lr, #16, #8
	ldr	r0, [r10, #796]
	bfi	ip, r8, #8, #8
	bfi	ip, r0, #0, #8
	str	ip, [r9, #3088]
	ldr	ip, [r10, #824]
	ldr	r0, [r10, #820]
	bfi	r1, ip, #24, #8
	ldr	ip, [r10, #816]
	bfi	r1, r0, #16, #8
	ldr	r0, [r10, #812]
	bfi	r1, ip, #8, #8
	bfi	r1, r0, #0, #8
	str	r1, [r9, #3092]
	ldr	r0, [r10, #840]
	ldr	r1, [r10, #836]
	bfi	r2, r0, #24, #8
	ldr	r0, [r10, #832]
	bfi	r2, r1, #16, #8
	ldr	r1, [r10, #828]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r9, #3096]
	ldr	r1, [r10, #856]
	ldr	r2, [r10, #852]
	bfi	r3, r1, #24, #8
	ldr	r1, [r10, #848]
	bfi	r3, r2, #16, #8
	ldr	r2, [r10, #844]
	bfi	r3, r1, #8, #8
	bfi	r3, r2, #0, #8
	str	r3, [r9, #3072]
	ldr	r2, [r4, #3396]
	ldr	r3, [r4, #3400]
	bfi	r7, r2, #0, #4
	mov	r2, r6
	bfi	r7, r3, #4, #4
	str	r7, [r9, #3100]
	ldr	r3, [r4, #3344]
	bfi	r2, r3, #0, #4
	str	r2, [r9, #3104]
	ldr	r2, [r4, #3340]
	ldr	r3, [r4, #3348]
	bfi	r6, r2, #0, #4
	bfi	r6, r3, #4, #4
	str	r6, [r9, #3108]
	ldr	r3, [r5, #4]
	cmp	r3, #0
	ldrne	r2, [r10, #776]
	moveq	r2, #3
	movne	r3, #0
	bfi	r3, r2, #0, #4
	str	r3, [r9, #3112]
	ldr	r0, [r4, #3272]
	mov	r3, #0
	ldr	r2, [r4, #3276]
	mov	ip, r3
	mov	r1, r3
	bfi	r3, r0, #0, #2
	ldr	r0, [r4, #3280]
	bfi	r3, r2, #2, #2
	ldr	r2, [r4, #3284]
	bfi	r3, r0, #4, #2
	ldr	r0, [r4, #3288]
	bfi	r3, r2, #6, #2
	ldr	r2, [r4, #3292]
	bfi	r3, r0, #8, #2
	ldr	r0, [r4, #3296]
	bfi	r3, r2, #10, #2
	ldr	r2, [r4, #3300]
	bfi	r3, r0, #12, #2
	ldr	r0, [r4, #3304]
	bfi	r3, r2, #14, #2
	ldr	r2, [r4, #3308]
	bfi	r3, r0, #16, #2
	ldr	r0, [r4, #3312]
	bfi	r3, r2, #18, #2
	ldr	r2, [r4, #3316]
	bfi	r3, r0, #20, #2
	ldr	r0, [r4, #3320]
	bfi	r3, r2, #22, #2
	ldr	r2, [r4, #3324]
	bfi	r3, r0, #24, #2
	ldr	r0, [r4, #3328]
	bfi	r3, r2, #26, #2
	ldr	r2, [r4, #3332]
	bfi	r3, r0, #28, #2
	add	r0, r10, #1168
	bfi	r3, r2, #30, #2
	str	r3, [r9, #3116]
	ldr	lr, [r4, #3336]
	add	r0, r0, #8
	add	r2, r10, #856
	add	r3, r9, #3152
	bfi	ip, lr, #0, #5
	str	ip, [r9, #3120]
	ldr	ip, [r4, #3384]
	ldr	lr, [r4, #3388]
	bfi	r1, ip, #24, #4
	ldr	ip, [r4, #3392]
	bfi	r1, lr, #28, #4
	ldr	lr, [r4, #3356]
	bfi	r1, ip, #16, #6
	ldr	ip, [r4, #3376]
	bfi	r1, lr, #8, #4
	bfi	r1, ip, #0, #6
	str	r1, [r9, #3124]
.L45:
	ldr	r1, [r2, #4]!
	add	r3, r3, #4
	cmp	r2, r0
	str	r1, [r3, #-4]
	bne	.L45
	add	r3, r9, #4096
	mov	r2, #0
	mov	r1, r2
	mov	ip, r2
	bfi	r1, r2, #0, #16
	bfi	ip, r2, #0, #16
	mov	r0, r2
	bfi	r0, r2, #16, #16
	str	r2, [r9, #3660]
	bfi	r1, r2, #16, #16
	bfi	ip, r2, #16, #16
	bfi	r0, r2, #0, #16
	mov	r6, r2
	mov	lr, r2
	bfi	r6, r2, #0, #1
	bfi	lr, r2, #0, #1
	str	r6, [r3, #512]
	mov	r6, #13
	str	lr, [r3, #516]
	mov	lr, r2
	str	r2, [r3, #520]
	bfi	lr, r6, #0, #4
	str	lr, [r3, #524]
	mov	r6, #0
	str	r2, [r3, #528]
	mov	r2, #7
	str	r1, [r3, #532]
	mvn	r1, #0
	str	ip, [r3, #536]
	mov	lr, r6
	str	r0, [r3, #540]
	mov	r8, r6
	str	r1, [r3, #544]
	mov	ip, r6
	str	r2, [r3, #548]
	mov	r0, r6
	str	r1, [r3, #552]
	str	r2, [r3, #556]
	str	r1, [r3, #560]
	str	r2, [r3, #564]
	str	r1, [r3, #568]
	mov	r1, r6
	str	r2, [r3, #572]
	mov	r2, r6
	ldr	r7, [r4, #4064]
	bfi	r6, r7, #0, #1
	str	r6, [r3, #1212]
	ldr	r6, [r5, #172]
	mov	r7, lr
	str	r6, [r3, #1188]
	mov	r6, lr
	ldr	r10, [r5, #176]
	str	r10, [r3, #1192]
	ldr	r10, [r5, #180]
	str	r10, [r3, #1196]
	ldr	r10, [r5, #184]
	str	r10, [r3, #1200]
	ldr	r10, [r5, #188]
	str	r10, [r3, #1204]
	ldr	r10, [r5, #192]
	str	r10, [r3, #1208]
	ldr	r10, [r4, #3252]
	bfi	lr, r10, #0, #16
	ldr	r10, [r4, #3256]
	bfi	lr, r10, #16, #16
	str	lr, [r3, #1668]
	ldr	lr, [r4, #3268]
	movw	r10, #513
	bfi	r8, lr, #16, #16
	str	r8, [r3, #1672]
	ldr	lr, [r4, #3260]
	ldr	r8, [r4, #3264]
	bfi	ip, lr, #0, #16
	ldr	lr, .L90
	bfi	ip, r8, #16, #16
	str	ip, [r3, #1676]
	ldr	ip, [r5, #536]
	ldr	lr, [lr]
	ldr	r8, [r4, #4060]
	cmp	ip, r1
	add	r3, lr, #4096
	bfi	r0, r8, #8, #3
	movw	r8, #9729
	moveq	r8, r10
	bfi	r0, r8, #16, #16
	str	r0, [r3, #3584]
	ldr	ip, [r5, #632]
	ldr	r0, [r5, #636]
	bfi	r1, ip, #0, #5
	bfi	r1, r0, #16, #16
	str	r1, [r3, #3588]
	ldr	r0, [r4, #2420]
	ldr	r1, [r4, #2424]
	bfi	r2, r0, #0, #5
	bfi	r2, r1, #16, #16
	str	r2, [r3, #3628]
	ldr	r1, [r5, #632]
	ldr	r2, [r5, #672]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	r7, r2, #0, #16
	str	r7, [r3, #3592]
	ldr	r1, [r4, #2420]
	ldr	r2, [r4, #2416]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	r6, r2, #0, #16
	str	r6, [r3, #3632]
	ldr	r2, [r5, #4]
	cmp	r2, #2
	beq	.L85
	ldr	r2, [r5, #600]
	add	lr, lr, #8192
	str	r2, [lr, #4]
	ldr	r2, [r5, #604]
	str	r2, [lr, #8]
	ldr	r2, [r5, #608]
	str	r2, [lr, #12]
	ldr	r2, [r5, #612]
	str	r2, [lr, #16]
	ldr	r2, [r5, #616]
	str	r2, [lr, #20]
	ldr	r2, [r5, #620]
	str	r2, [lr, #24]
	ldr	r2, [r5, #624]
	str	r2, [lr, #28]
	ldr	r2, [r5, #628]
	str	r2, [lr, #32]
	ldr	r2, [r5, #632]
	ldr	r1, [lr, #36]
	sub	r2, r2, #1
	bfi	r1, r2, #16, #7
	str	r1, [lr, #36]
	ldr	r2, [r5, #632]
	ldr	r1, [lr, #36]
	mov	r2, r2, lsr #8
	sub	r2, r2, #1
	bfi	r1, r2, #8, #6
	str	r1, [lr, #36]
	ldr	r2, [r5, #632]
	ldr	r1, [lr, #36]
	mov	r2, r2, lsr #16
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [lr, #36]
.L54:
	ldr	r2, [r5, #4]
	cmp	r2, #2
	beq	.L86
	ldr	r3, [r4, #2352]
	str	r3, [lr, #44]
	ldr	r3, [r4, #2356]
	str	r3, [lr, #48]
	ldr	r3, [r4, #2360]
	str	r3, [lr, #52]
	ldr	r3, [r4, #2364]
	str	r3, [lr, #56]
	ldr	r3, [r4, #2368]
	str	r3, [lr, #60]
	ldr	r3, [r4, #2372]
	str	r3, [lr, #64]
	ldr	r3, [r4, #2376]
	str	r3, [lr, #68]
	ldr	r3, [r4, #2380]
	str	r3, [lr, #72]
	ldr	r3, [r4, #2348]
	ldr	r2, [lr, #76]
	sub	r3, r3, #1
	bfi	r2, r3, #16, #7
	str	r2, [lr, #76]
	ldr	r3, [r4, #2348]
	ldr	r2, [lr, #76]
	mov	r3, r3, lsr #8
	sub	r3, r3, #1
	bfi	r2, r3, #8, #6
	str	r2, [lr, #76]
	ldr	r3, [r4, #2348]
	ldr	r2, [lr, #76]
	mov	r3, r3, lsr #16
	sub	r3, r3, #1
	bfi	r2, r3, #0, #6
	str	r2, [lr, #76]
.L61:
	ldr	r3, [lr, #40]
	mov	ip, #0
	add	r6, r9, #8192
	add	r2, r4, #4096
	bfc	r3, #1, #24
	str	r3, [lr, #40]
	ldr	r0, [lr, #40]
	mov	r1, ip
	mov	r3, ip
	bfc	r3, #16, #8
	bfc	r0, #0, #1
	str	r0, [lr, #40]
	str	ip, [lr, #40]
	ldr	r0, [r5, #264]
	str	r0, [r6, #1028]
	ldr	r0, [r5, #48]
	bfi	r1, r0, #0, #1
	str	r1, [r6, #1040]
	ldr	r2, [r2, #76]
	mov	r0, #0
	mov	r1, r0
	mov	r7, r0
	str	r2, [r6, #1044]
	ldr	r2, [r5, #536]
	cmp	r2, ip
	mov	ip, #0
	bfieq	r3, r2, #0, #1
	orrne	r3, r3, #1
	str	r3, [r6, #1048]
	mvn	r2, #84
	ldr	r3, [r5, #676]
	bfi	ip, r2, #0, #8
	mov	r2, #85
	bfi	ip, r2, #8, #8
	mov	r2, r0
	str	r3, [r6, #1052]
	mov	r3, r0
	str	r0, [r6, #1056]
	str	r0, [r6, #1060]
	str	r0, [r6, #1064]
	str	ip, [r6, #1536]
	ldr	ip, [r4, #3404]
	ldr	lr, [r4, #3408]
	bfi	r1, ip, #0, #6
	ldr	ip, [r4, #3412]
	bfi	r1, lr, #8, #2
	ldr	lr, [r4, #3416]
	bfi	r1, ip, #10, #1
	ldr	ip, [r4, #3420]
	bfi	r1, lr, #12, #4
	bfi	r1, ip, #16, #5
	str	r1, [r6, #4048]
	ldr	r1, [r4, #3464]
	str	r1, [r6, #4052]
	ldr	r1, [r4, #3468]
	str	r1, [r6, #4056]
	ldr	ip, [r4, #3472]
	ldr	r1, [r4, #3476]
	bfi	r3, ip, #0, #16
	ldr	ip, [r4, #3480]
	bfi	r3, r1, #16, #2
	ldr	r1, [r4, #3484]
	bfi	r3, ip, #18, #2
	ldr	ip, [r4, #3488]
	bfi	r3, r1, #20, #4
	ldr	r1, [r4, #3496]
	bfi	r3, ip, #24, #1
	ldr	ip, [r4, #3500]
	bfi	r3, r1, #25, #2
	ldr	r1, [r4, #3492]
	bfi	r3, ip, #27, #1
	bfi	r3, r1, #28, #1
	str	r3, [r6, #4060]
	ldr	r1, [r4, #3532]
	ldr	r3, [r4, #3528]
	bfi	r2, r1, #0, #1
	ldr	r1, [r4, #3524]
	bfi	r2, r3, #2, #2
	ldr	r3, [r4, #3520]
	bfi	r2, r1, #4, #2
	ldr	r1, [r4, #3540]
	bfi	r2, r3, #6, #1
	ldr	r3, [r4, #3544]
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #24, #6
	str	r2, [r6, #4064]
	ldr	r2, [r4, #3548]
	ldr	r3, [r4, #3552]
	bfi	r0, r2, #0, #6
	ldr	r2, [r4, #3556]
	bfi	r0, r3, #8, #6
	ldr	r3, [r4, #3560]
	bfi	r0, r2, #16, #6
	bfi	r0, r3, #24, #6
	str	r0, [r6, #4068]
	ldr	r1, [r5, #4]
	ldr	r2, [r4, #3564]
	cmp	r1, r7
	ldr	r1, [r5, #16]
	ldr	r3, [r4, #3568]
	bfi	r7, r2, #0, #6
	ldr	r0, [r5, #540]
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #6
	bfi	r7, r3, #6, #25
	bl	__aeabi_uidiv
	add	r3, r4, #4096
	mov	r2, #0
	mov	r1, r2
	bfi	r7, r0, #6, #25
	str	r7, [r6, #4072]
	ldr	ip, [r5, #572]
	ldr	r0, [r5, #568]
	bfi	r2, ip, #10, #1
	ldr	ip, [r5, #564]
	bfi	r2, r0, #9, #1
	ldr	r0, [r3, #12]
	bfi	r2, ip, #8, #1
	ldr	ip, [r3, #16]
	bfi	r2, r0, #7, #1
	ldr	r0, [r4, #4088]
	bfi	r2, ip, #6, #1
	ldr	ip, [r4, #4084]
	bfi	r2, r0, #5, #1
	ldr	r0, [r3, #20]
	bfi	r2, ip, #4, #1
	ldr	ip, [r3, #24]
	bfi	r2, r0, #3, #1
	ldr	r0, [r3, #28]
	bfi	r2, ip, #2, #1
	ldr	ip, [r3, #32]
	bfi	r2, r0, #1, #1
	mov	r0, r1
	bfi	r2, ip, #0, #1
	str	r2, [r9, #504]
	ldr	lr, [r4, #4092]
	mov	r2, r1
	ldr	r6, [r3, #36]
	bfi	r2, r0, #1, #1
	bfi	r1, lr, #7, #1
	ldr	lr, [r3, #40]
	bfi	r1, r6, #6, #1
	ldr	r6, [r3, #44]
	bfi	r1, lr, #5, #1
	ldr	lr, [r3, #48]
	bfi	r1, r6, #4, #1
	ldr	r6, [r3, #52]
	bfi	r1, lr, #3, #1
	ldr	lr, [r3, #56]
	bfi	r1, r6, #2, #1
	ldr	r3, [r3, #60]
	bfi	r1, lr, #1, #1
	add	ip, r9, #61440
	bfi	r1, r3, #0, #1
	str	r1, [r9, #508]
	ldr	r3, [r4, #4076]
	bfc	r2, #2, #1
	ldr	lr, [r4, #4080]
	mov	r1, #3
	bfi	r0, r3, #0, #1
	ldr	r3, .L90
	bfi	r0, lr, #3, #1
	bfc	r2, #3, #1
	bfi	r0, r1, #16, #4
	str	r0, [ip]
	ldr	r3, [r3]
	mov	r1, #1
	str	r2, [ip, #32]
	mov	r2, #0
	ldr	r0, [r5, #576]
	add	r3, r3, #61440
	str	r0, [r3, #520]
	ldr	r0, [r5, #576]
	str	r0, [r3, #524]
	ldr	r0, [r5, #584]
	str	r0, [r3, #752]
	ldr	r0, [r5, #580]
	str	r0, [r3, #756]
	ldr	r0, [r5, #584]
	str	r0, [r3, #772]
	ldr	r0, [r5, #580]
	str	r0, [r3, #776]
	str	r2, [ip, #8]
	str	r2, [r9, #16]
	str	r1, [r9, #16]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L40:
	mov	r2, #15
	mov	r3, #0
	bfi	r3, r2, #0, #5
	bfi	r3, r2, #5, #5
	bfi	r3, r2, #10, #5
	bfi	r3, r2, #15, #5
	bfc	r3, #20, #1
	str	r3, [r9, #2052]
	b	.L41
.L71:
	mov	r2, #6
.L36:
	bfi	r3, r2, #6, #4
	bfc	r3, #14, #1
.L37:
	ldrb	r2, [r5, #64]
	b	.L38
.L82:
	cmp	r2, #1920
	movcs	r3, #3
	strcs	r3, [r4, #2316]
	bcs	.L22
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r4, #2316]
	ldmib	r5, {r2, r3}
	cmp	r2, #0
	bne	.L25
.L83:
	cmp	r3, #3
	clz	r3, r3
	movne	r2, #1
	moveq	r2, #0
	mov	r3, r3, lsr #5
	str	r2, [r4, #2324]
	str	r3, [r4, #2328]
	moveq	r2, #7
	movne	r2, #5
	str	r2, [r4, #2320]
	b	.L27
.L86:
	ldr	r2, [r4, #2424]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r4, #2384]
	ldrhi	r2, [r4, #2384]
	movls	r2, r1, asl r2
	str	r2, [r3, #3636]
	ldr	r2, [r4, #2424]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r4, #2388]
	ldrls	r1, [r4, #2388]
	movls	r2, r1, asl r2
	str	r2, [r3, #3640]
	ldr	r2, [r4, #2424]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r4, #2392]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #3644]
	ldr	r2, [r4, #2396]
	str	r2, [r3, #3648]
	ldr	r2, [r4, #2400]
	str	r2, [r3, #3652]
	ldr	r2, [r4, #2404]
	str	r2, [r3, #3656]
	ldr	r2, [r4, #2408]
	str	r2, [r3, #3660]
	ldr	r2, [r4, #2412]
	str	r2, [r3, #3664]
	b	.L61
.L84:
	ldr	r2, [r5, #16]
	ldr	r3, [r5, #12]
	mov	r2, r2, lsr #2
	sub	r2, r2, #16
	mov	r3, r3, lsr #2
	sub	r3, r3, #16
	mov	r2, r2, lsr #1
	cmp	r2, #32
	mov	r3, r3, lsr #1
	movcs	r2, #32
	cmp	r3, #72
	bic	r2, r2, #-2147483645
	movcs	r3, #72
	cmp	r2, #7
	bic	r3, r3, #-2147483645
	movls	r2, #7
	bls	.L33
	cmp	r2, #32
	movcs	r2, #32
	sub	r2, r2, #1
	and	r2, r2, #63
.L33:
	cmp	r3, #7
	movls	r3, #7
	bls	.L34
	cmp	r3, #72
	movcs	r3, #72
	sub	r3, r3, #1
	and	r3, r3, #127
.L34:
	mov	r6, #0
	bfi	r6, r2, #16, #6
	bfi	r6, r3, #0, #7
	b	.L35
.L85:
	ldr	r2, [r5, #636]
	add	lr, lr, #8192
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r5, #640]
	ldrhi	r2, [r5, #640]
	movls	r2, r1, asl r2
	str	r2, [r3, #3596]
	ldr	r2, [r5, #636]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r5, #644]
	ldrls	r1, [r5, #644]
	movls	r2, r1, asl r2
	str	r2, [r3, #3600]
	ldr	r2, [r5, #636]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r5, #648]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #3604]
	ldr	r2, [r5, #652]
	str	r2, [r3, #3608]
	ldr	r2, [r5, #656]
	str	r2, [r3, #3612]
	ldr	r2, [r5, #660]
	str	r2, [r3, #3616]
	ldr	r2, [r5, #664]
	str	r2, [r3, #3620]
	ldr	r2, [r5, #668]
	str	r2, [r3, #3624]
	b	.L54
.L91:
	.align	2
.L90:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_DirectCfgReg, .-DRV_VENC_HAL_DirectCfgReg
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ClrInt
	.type	DRV_VENC_HAL_V400R004C02_ClrInt, %function
DRV_VENC_HAL_V400R004C02_ClrInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L101
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L94
	bcc	.L95
	cmp	r0, #2
	bne	.L100
	ldr	r2, [r3, #12]
	orr	r2, r2, #134217728
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L100:
	mvn	r2, #0
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L95:
	ldr	r2, [r3, #12]
	orr	r2, r2, #1
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L94:
	ldr	r2, [r3, #12]
	orr	r2, r2, #1024
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L102:
	.align	2
.L101:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ClrInt, .-DRV_VENC_HAL_V400R004C02_ClrInt
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_DisableInt
	.type	DRV_VENC_HAL_V400R004C02_DisableInt, %function
DRV_VENC_HAL_V400R004C02_DisableInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L112
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L105
	bcc	.L106
	cmp	r0, #2
	bne	.L111
	ldr	r2, [r3, #4]
	bfc	r2, #27, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L111:
	mov	r2, #0
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L106:
	ldr	r2, [r3, #4]
	bfc	r2, #0, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L105:
	ldr	r2, [r3, #4]
	bfc	r2, #10, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L113:
	.align	2
.L112:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_DisableInt, .-DRV_VENC_HAL_V400R004C02_DisableInt
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.type	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, %function
DRV_VENC_HAL_V400R004C02_ReadReg_Smmu:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L115
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
.L116:
	.align	2
.L115:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, .-DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ReadReg
	.type	DRV_VENC_HAL_V400R004C02_ReadReg, %function
DRV_VENC_HAL_V400R004C02_ReadReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, .L122
	mov	r4, r0
	ldmia	r2, {r3, ip}
	ldr	r2, [r3]
	and	r2, r2, #1
	str	r2, [r0, #8]
	ldr	r2, [r3]
	ubfx	r2, r2, #1, #1
	str	r2, [r0, #12]
	ldr	r1, [r3]
	ubfx	r1, r1, #3, #1
	str	r1, [r0, #16]
	ldr	r0, [r3]
	orrs	r2, r1, r2
	ubfx	r2, r0, #27, #1
	str	r2, [r4]
	ldr	r2, [r3]
	ubfx	r2, r2, #10, #1
	str	r2, [r4, #4]
	bne	.L118
	add	r2, r3, #4096
	ldr	r0, [r2, #1644]
	bic	r0, r0, #-67108864
	str	r0, [r4, #24]
	ldr	r1, [ip, #4]
	cmp	r1, #0
	beq	.L121
	ldr	r3, [r2, #3712]
	mov	r3, r3, asl #3
	str	r3, [r4, #20]
	ldr	r5, [r2, #1540]
	ldr	r3, [r2, #1572]
	ubfx	r5, r5, #0, #19
	ubfx	r3, r3, #0, #17
	add	r5, r5, r3
	str	r5, [r4, #28]
	ldr	r3, [ip, #16]
	ldr	r1, [ip, #12]
	add	r3, r3, #7
	add	r1, r1, #7
	mov	r3, r3, lsr #3
	mov	r1, r1, lsr #3
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #24]
.L120:
	add	r3, r5, #3
	cmp	r5, #0
	movlt	r5, r3
	mov	r5, r5, asr #2
	str	r5, [r4, #28]
.L118:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L121:
	add	r3, r3, #8192
	ldr	r3, [r3, #132]
	mov	r3, r3, asl #3
	str	r3, [r4, #20]
	ldr	r3, [r2, #1544]
	ldr	r1, [r2, #1548]
	ldr	r5, [r2, #1576]
	ubfx	r2, r3, #0, #19
	ubfx	r3, r1, #0, #19
	add	r3, r2, r3
	ubfx	r5, r5, #0, #19
	add	r5, r3, r5
	str	r5, [r4, #28]
	ldr	r3, [ip, #16]
	ldr	r1, [ip, #12]
	add	r3, r3, #15
	add	r1, r1, #15
	mov	r3, r3, lsr #4
	mov	r1, r1, lsr #4
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #24]
	b	.L120
.L123:
	.align	2
.L122:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ReadReg, .-DRV_VENC_HAL_V400R004C02_ReadReg
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_CfgReg
	.type	DRV_VENC_HAL_V400R004C02_CfgReg, %function
DRV_VENC_HAL_V400R004C02_CfgReg:
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
	bne	.L189
	bl	DRV_VENC_HAL_DirectCfgReg
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L189:
	mov	r1, r0
	ldr	r9, [r0, #688]
	ldr	r0, .L196
	mov	r2, #692
	ldr	r3, .L196+4
	ldr	r10, [r0, #4]
	ldr	r0, [r0]
	add	r4, r10, r2
	ldr	r3, [r3, #4]
	str	r0, [fp, #-48]
	mov	r0, r10
	blx	r3
	mov	r0, r4
	ldr	r2, [r8, #536]
	ldr	r1, [r8, #544]
	bl	DRV_VENC_HAL_SetDefaultAttrByStartQP
	mov	r0, r4
	ldr	r1, [r8, #4]
	add	r4, r10, #4096
	bl	DRV_VENC_HAL_SetDefaultAttrByProtocol
	ldr	r3, [r8, #40]
	ldr	r2, [r8, #12]
	cmp	r3, #0
	bne	.L190
.L126:
	ldmib	r8, {r2, r3}
	cmp	r2, #0
	beq	.L191
	mov	r3, #0
	mov	r2, #7
	str	r3, [r4, #2328]
	str	r3, [r4, #2324]
	str	r2, [r4, #2320]
.L131:
	ldr	r3, [r8, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	bhi	.L134
	ldr	ip, [r8, #4]
	cmp	ip, #0
	bne	.L134
	add	r3, r10, #7872
	add	r2, r10, #8064
	ldr	r7, [fp, #-52]
	add	r2, r2, #44
	ldr	r5, [fp, #-132]
	mov	r0, r3
	add	r3, r3, #12
	add	r0, r0, #40
	mov	r1, ip
	mov	lr, #28
	str	lr, [r8, #552]
	str	lr, [r8, #548]
	str	lr, [r8, #544]
	str	ip, [r10, #792]
	str	ip, [r8, #20]
	str	ip, [r4, #3752]
	str	ip, [r4, #3460]
.L135:
	str	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L135
	str	r7, [fp, #-52]
	str	r5, [fp, #-132]
.L134:
	ldr	r2, [r8, #40]
	mov	r3, #11
	ldr	r7, [fp, #-48]
	mov	lr, #0
	bfi	r3, r2, #10, #1
	bfc	lr, #0, #1
	bfc	r3, #16, #1
	orr	lr, lr, #6
	bfc	r3, #17, #1
	mov	ip, #0
	orr	r3, r3, #134217728
	mov	r6, #0
	bfc	r3, #30, #1
	str	r3, [r7, #4]
	ldr	r3, [r8, #4]
	bfc	r6, #0, #9
	ldr	r0, [r8, #40]
	bfc	r6, #16, #9
	subs	r2, r3, #2
	mov	r1, ip
	bfc	r1, #0, #5
	movne	r2, #1
	bfi	lr, r2, #3, #2
	bfi	lr, r0, #5, #1
	ldr	r0, [r4, #4056]
	cmp	r3, #2
	ldr	r3, [r4, #4052]
	ldr	r2, [r8, #536]
	bfi	lr, r0, #6, #1
	bfi	lr, r3, #7, #1
	ldr	r0, [r4, #2428]
	clz	r3, r2
	bfc	lr, #8, #1
	bfc	lr, #24, #1
	bfc	r1, #5, #5
	bfi	lr, r0, #9, #1
	mov	r3, r3, lsr #5
	ldr	r0, [r4, #2328]
	bfi	lr, r3, #10, #2
	ldr	r3, [r4, #2324]
	bfi	lr, r0, #12, #1
	movne	r0, ip
	bfi	lr, r2, #16, #1
	moveq	r0, #2
	orr	lr, lr, #131072
	mov	r2, ip
	bfi	lr, r3, #18, #2
	bfi	r2, ip, #0, #1
	bfc	lr, #21, #1
	bfi	r2, ip, #1, #1
	bfc	lr, #22, #1
	mov	r3, ip
	bfc	lr, #25, #1
	bfi	r2, ip, #2, #1
	bfi	lr, r0, #26, #2
	ldr	r0, [r8, #44]
	bfi	r2, r3, #3, #1
	bfi	lr, r0, #28, #2
	mov	r0, ip
	bfc	lr, #30, #1
	bfi	r0, ip, #8, #2
	bfc	lr, #31, #1
	str	lr, [r7, #20]
	str	r6, [r9, #512]
	bfi	r0, ip, #4, #4
	ldr	r5, [r8, #20]
	add	lr, r4, #4096
	ldr	r6, [r8, #28]
	bfi	r0, r3, #0, #4
	bfi	ip, r5, #17, #1
	orr	r2, r2, #458752
	bfc	ip, #16, #1
	bfi	ip, r6, #0, #16
	str	ip, [r9, #516]
	ldr	ip, [r8, #544]
	mov	r6, r3
	ldr	r5, [r4, #3444]
	bfi	r1, ip, #10, #6
	ldr	ip, [r4, #3460]
	bfi	r1, ip, #18, #1
	mov	ip, r3
	bfi	r1, r5, #19, #1
	str	r1, [r7, #32]
	str	r3, [r7, #36]
	bfi	ip, r3, #16, #9
	str	r3, [r7, #40]
	bfi	ip, r3, #0, #9
	str	r0, [r9, #520]
	mov	r1, r3
	ldr	r5, [lr, #64]
	ldr	r0, [lr, #68]
	bfi	r2, r5, #19, #2
	bfi	r2, r0, #21, #1
	bfi	r2, r3, #23, #1
	str	r2, [r7, #48]
	ldr	r3, [r8, #16]
	ldr	r2, [r8, #12]
	sub	r3, r3, #1
	bfi	r6, r3, #16, #13
	sub	r2, r2, #1
	bfi	r6, r2, #0, #13
	str	r6, [r9]
	str	ip, [r7, #56]
	ldr	r3, [lr, #72]
	str	r3, [r7, #60]
	ldr	r2, [r4, #4068]
	ldr	r3, [r4, #4072]
	bfi	r1, r2, #4, #4
	bfi	r1, r3, #0, #4
	str	r1, [r7, #64]
	ldr	r3, [r8, #4]
	cmp	r3, #2
	beq	.L192
	cmp	r3, #0
	beq	.L193
	b	.L197
.L198:
	.align	2
.L196:
	.word	.LANCHOR1
	.word	venc_Osal_Func_Ptr_S
.L197:
.L139:
	mov	r2, #3
	mov	r3, #0
	bfi	r3, r2, #0, #3
	mov	r1, #1
	bfi	r3, r1, #3, #2
	ldr	r1, [fp, #-52]
	bfi	r3, r2, #5, #3
	str	r2, [r9, #20]
	bfi	r3, r2, #8, #3
	mov	lr, #0
	str	r1, [r9, #16]
	mov	r1, #1
	str	r1, [r9, #524]
	mov	r0, lr
	ldr	r1, [fp, #-48]
	mov	ip, lr
	mov	r6, lr
	str	r3, [r1, #100]
	mov	r1, lr
	ldr	r7, [r8, #196]
	mov	r3, lr
	bfc	r3, #0, #1
	bfc	r3, #1, #1
	str	r7, [r9, #128]
	bfc	r3, #2, #1
	ldr	r7, [r8, #68]
	bfc	r3, #3, #3
	str	r7, [r9, #132]
	ldr	r7, [r8, #72]
	str	r7, [r9, #136]
	ldr	r7, [r8, #76]
	str	r7, [r9, #140]
	ldr	r7, [r8, #80]
	ldr	r5, [r8, #84]
	bfi	lr, r7, #16, #16
	bfi	lr, r5, #0, #16
	str	lr, [r9, #152]
	ldr	lr, [r8, #168]
	add	lr, r8, lr, lsl #2
	ldr	lr, [lr, #156]
	str	lr, [r9, #156]
	ldr	lr, [r8, #136]
	add	lr, r8, lr, lsl #2
	ldr	lr, [lr, #88]
	str	lr, [r9, #160]
	ldr	lr, [r8, #136]
	add	lr, r8, lr, lsl #2
	ldr	lr, [lr, #96]
	str	lr, [r9, #164]
	ldr	r7, [r8, #104]
	ldr	lr, [r8, #108]
	bfi	ip, r7, #0, #16
	bfi	ip, lr, #16, #16
	str	ip, [r9, #168]
	ldr	ip, [r8, #136]
	add	ip, r8, ip, lsl #2
	ldr	ip, [ip, #112]
	str	ip, [r9, #172]
	ldr	ip, [r8, #136]
	add	ip, r8, ip, lsl #2
	ldr	ip, [ip, #120]
	str	ip, [r9, #176]
	ldr	ip, [r8, #128]
	bfi	r6, ip, #0, #16
	str	r6, [r9, #180]
	ldr	ip, [r8, #136]
	cmp	ip, r0
	moveq	ip, #84
	movne	ip, #80
	add	ip, r8, ip
	ldr	ip, [ip, #8]
	str	ip, [r9, #184]
	ldr	ip, [r8, #136]
	cmp	ip, r0
	moveq	ip, #92
	movne	ip, #88
	add	ip, r8, ip
	ldr	ip, [ip, #8]
	str	ip, [r9, #188]
	ldr	lr, [r8, #108]
	ldr	ip, [r8, #104]
	bfi	r0, lr, #0, #16
	bfi	r0, ip, #16, #16
	str	r0, [r9, #192]
	ldr	r0, [r8, #136]
	cmp	r0, r1
	moveq	r0, #108
	movne	r0, #104
	add	r0, r8, r0
	ldr	r0, [r0, #8]
	str	r0, [r9, #196]
	ldr	r0, [r8, #136]
	cmp	r0, r1
	moveq	r0, #116
	movne	r0, #112
	add	r0, r8, r0
	ldr	r0, [r0, #8]
	str	r0, [r9, #200]
	ldr	ip, [r8, #128]
	ldr	r0, [r8, #132]
	bfi	r1, ip, #16, #16
	bfi	r1, r0, #0, #16
	str	r1, [r9, #204]
	ldr	r1, [r8, #136]
	cmp	r1, #0
	moveq	r1, #148
	movne	r1, #144
	add	r1, r8, r1
	ldr	r1, [r1, #4]
	str	r1, [r9, #208]
	ldr	r1, [r8, #136]
	add	r1, r8, r1, lsl #2
	ldr	r1, [r1, #148]
	str	r1, [r9, #212]
	ldr	r1, [r8, #136]
	add	r1, r8, r1, lsl #2
	ldr	r1, [r1, #140]
	str	r1, [r9, #48]
	ldr	r1, [r8, #136]
	cmp	r1, #0
	moveq	r1, #140
	movne	r1, #136
	add	r1, r8, r1
	ldr	r1, [r1, #4]
	str	r1, [r9, #52]
	ldr	r1, [r8, #200]
	str	r1, [r9, #56]
	ldr	r1, [r8, #332]
	str	r1, [r9, #60]
	ldr	r1, [r8, #328]
	str	r1, [r9, #64]
	ldr	r1, [r8, #60]
	cmp	r1, #2
	beq	.L140
	cmp	r1, #1
	beq	.L177
	cmp	r1, #0
	bfc	r3, #6, #4
	bfc	r3, #14, #1
	bne	.L141
	ldr	r2, [r8, #64]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L142:
	bfi	r3, r2, #16, #8
	str	r3, [r9, #4]
	ldr	r1, [r4, #2320]
	mov	r2, #0
	ldr	ip, [r4, #4048]
	mov	r0, #5
	mov	r3, r2
	bfi	r2, r1, #0, #3
	bfc	r3, #0, #1
	mov	r1, #0
	bfi	r1, r0, #24, #8
	bfi	r2, ip, #4, #1
	bfi	r1, r0, #16, #8
	bfc	r3, #1, #1
	mov	ip, #15
	bfc	r2, #5, #1
	bfi	r1, ip, #8, #8
	bfc	r3, #2, #1
	mov	r0, #0
	bfi	r1, ip, #0, #8
	orr	r2, r2, #30464
	str	r1, [r9, #544]
	str	r2, [r9, #528]
	orr	r3, r3, #24
	mov	r2, #500
	str	r3, [r9, #532]
	movt	r0, 100
	mov	r3, #3
	bfi	r0, r2, #0, #16
	str	r3, [r9, #72]
	str	r0, [r9, #536]
	mov	ip, #0
	ldr	r0, [r4, #2432]
	mov	r3, ip
	ldr	r2, [r10, #696]
	mov	r1, ip
	bfi	ip, r0, #0, #1
	ldr	r0, [r10, #692]
	ldr	r7, [fp, #-48]
	bfi	ip, r2, #1, #1
	bfi	ip, r0, #2, #1
	mov	r5, r3
	orr	ip, ip, #8
	mov	lr, #128
	bfc	ip, #4, #1
	str	ip, [r7, #352]
	ldr	ip, [r8, #684]
	bfi	r5, lr, #0, #10
	mov	r0, r3
	mov	r6, r3
	mvn	r2, #127
	bfi	r0, r2, #0, #8
	str	ip, [r7, #392]
	bfi	r0, r2, #8, #8
	ldr	ip, [r4, #3436]
	bfi	r6, r2, #0, #8
	ldr	lr, [r4, #3440]
	bfi	r0, r2, #16, #8
	bfi	r3, ip, #0, #1
	ldr	ip, [r10, #784]
	bfi	r3, lr, #1, #1
	ldr	lr, [r4, #3456]
	bfi	r3, ip, #2, #1
	ldr	ip, [r10, #780]
	bfi	r3, lr, #4, #1
	ldr	lr, [r4, #3432]
	bfi	r3, ip, #8, #1
	ldr	ip, [r4, #3504]
	bfi	r3, lr, #9, #1
	ldr	lr, [r4, #3508]
	bfi	r3, ip, #10, #1
	ldr	ip, [r4, #3512]
	bfi	r3, lr, #11, #1
	ldr	lr, [r4, #3428]
	bfi	r3, ip, #12, #1
	ldr	ip, [r4, #3424]
	bfi	r3, lr, #13, #1
	ldr	lr, [r4, #3516]
	bfi	r3, ip, #14, #1
	mov	ip, r1
	bfi	r3, lr, #15, #1
	str	r3, [r7, #440]
	ldr	r3, [r10, #788]
	bfc	ip, #0, #1
	bfi	r6, r2, #8, #8
	str	r0, [r9, #1760]
	bfi	r1, r3, #1, #1
	mov	r3, #2
	bfi	r1, r3, #16, #8
	str	r6, [r9, #1764]
	mov	r3, #128
	bfc	ip, #1, #8
	bfi	r5, r3, #10, #10
	mov	r3, #2
	str	r5, [r9, #1768]
	bfi	r1, r3, #24, #8
	str	r1, [r9, #540]
	movw	r0, #43691
	str	ip, [r9, #32]
	movt	r0, 43690
	ldr	r1, [r8, #168]
	mov	r2, #1
	mov	r3, #0
	str	r3, [fp, #-64]
	add	r1, r1, #2
	mov	r5, r3
	str	r3, [fp, #-68]
	umull	r6, r7, r1, r0
	str	r3, [fp, #-72]
	str	r3, [fp, #-76]
	mov	lr, r7, lsr #1
	ldr	r7, [fp, #-48]
	add	lr, lr, lr, lsl #1
	rsb	r1, lr, r1
	add	r1, r8, r1, lsl #2
	ldr	r1, [r1, #156]
	str	r1, [r9, #216]
	ldr	lr, [r8, #168]
	add	lr, lr, #1
	umull	r0, r1, lr, r0
	mov	r1, r1, lsr #1
	add	r1, r1, r1, lsl #1
	rsb	r1, r1, lr
	add	r1, r8, r1, lsl #2
	ldr	r1, [r1, #156]
	str	r1, [r9, #220]
	str	r2, [r7, #492]
	ldrb	r1, [r4, #3812]
	ldrb	r6, [r4, #3820]
	ldrb	lr, [r4, #3816]
	mov	r0, r1
	ldrb	r7, [r4, #3808]
	orr	r1, lr, r6
	str	r0, [fp, #-56]
	orr	r1, r0, r1
	ldrb	r0, [r4, #3804]
	ldrb	r2, [r4, #3800]
	orr	r1, r7, r1
	ldrb	ip, [r4, #3796]
	orr	r1, r0, r1
	str	r6, [fp, #-52]
	orr	r1, r2, r1
	ldrb	r6, [r4, #3792]
	orr	r1, ip, r1
	orr	r1, r6, r1
	bfi	r3, r1, #24, #1
	ldr	r1, [r4, #4044]
	str	r6, [fp, #-60]
	bfi	r3, r1, #23, #1
	ldr	r1, [r4, #4040]
	bfi	r3, r1, #22, #1
	ldr	r1, [r4, #4036]
	bfi	r3, r1, #21, #1
	ldr	r1, [r4, #4032]
	bfi	r3, r1, #20, #1
	ldr	r1, [r4, #4028]
	bfi	r3, r1, #19, #1
	ldr	r1, [r4, #4024]
	bfi	r3, r1, #18, #1
	ldr	r1, [r4, #4020]
	bfi	r3, r1, #17, #1
	ldr	r1, [r4, #4016]
	bfi	r3, r1, #16, #1
	ldr	r1, [r4, #3852]
	bfi	r3, r1, #15, #1
	ldr	r1, [r4, #3848]
	bfi	r3, r1, #14, #1
	ldr	r1, [r4, #3844]
	ldr	r6, [fp, #-52]
	bfi	r3, r1, #13, #1
	ldr	r1, [r4, #3840]
	str	r5, [fp, #-52]
	bfi	r3, r1, #12, #1
	ldr	r1, [r4, #3836]
	bfi	r3, r1, #11, #1
	ldr	r1, [r4, #3832]
	bfi	r3, r1, #10, #1
	ldr	r1, [r4, #3828]
	bfi	r3, r1, #9, #1
	ldr	r1, [r4, #3824]
	bfi	r3, r1, #8, #1
	ldr	r1, [fp, #-56]
	bfi	r3, r6, #7, #1
	str	r5, [fp, #-56]
	bfi	r3, lr, #6, #1
	mov	r6, r5
	bfi	r3, r1, #5, #1
	mov	lr, r5
	bfi	r3, r7, #4, #1
	mov	r7, r5
	bfi	r3, r0, #3, #1
	bfi	r3, r2, #2, #1
	ldr	r2, [fp, #-60]
	bfi	r3, ip, #1, #1
	str	r7, [fp, #-60]
	bfi	r3, r2, #0, #1
	str	r3, [r9, #1024]
	ldr	r3, [r4, #3868]
	mov	r2, r7
	ldr	r1, [r4, #3864]
	mov	ip, r7
	ldr	r0, [r4, #3860]
	bfi	r5, r3, #24, #7
	bfi	r5, r1, #16, #7
	ldr	r3, [r4, #3856]
	bfi	r5, r0, #8, #7
	bfi	r5, r3, #0, #7
	str	r5, [r9, #1028]
	ldr	r3, [r4, #3884]
	mov	r5, ip
	ldr	r1, [r4, #3880]
	ldr	r0, [r4, #3876]
	bfi	r2, r3, #24, #7
	bfi	r2, r1, #16, #7
	ldr	r3, [r4, #3872]
	bfi	r2, r0, #8, #7
	mov	r1, r7
	bfi	r2, r3, #0, #7
	str	r2, [r9, #1032]
	ldr	r2, [r4, #3920]
	mov	r0, r7
	ldr	r3, [r4, #3888]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #1036]
	ldr	r2, [r4, #3924]
	mov	r1, r7
	ldr	r3, [r4, #3892]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #1040]
	ldr	r2, [r4, #3928]
	mov	r1, r7
	ldr	r3, [r4, #3896]
	bfi	r1, r2, #16, #10
	bfi	r1, r3, #0, #10
	str	r1, [r9, #1044]
	ldr	r2, [r4, #3932]
	mov	r1, r7
	ldr	r3, [r4, #3900]
	bfi	r7, r2, #16, #10
	bfi	r7, r3, #0, #10
	str	r7, [r9, #1048]
	ldr	r2, [r4, #3936]
	mov	r7, r6
	ldr	r3, [r4, #3904]
	bfi	r6, r2, #16, #10
	mov	r2, lr
	bfi	r6, r3, #0, #10
	str	r6, [r9, #1052]
	ldr	r6, [r4, #3940]
	ldr	r3, [r4, #3908]
	bfi	lr, r6, #16, #10
	bfi	lr, r3, #0, #10
	str	lr, [r9, #1056]
	ldr	r6, [r4, #3944]
	mov	r3, ip
	ldr	lr, [r4, #3912]
	bfi	r3, r6, #16, #10
	bfi	r3, lr, #0, #10
	str	r3, [r9, #1060]
	ldr	r6, [r4, #3948]
	mov	r3, ip
	ldr	lr, [r4, #3916]
	bfi	r3, r6, #16, #10
	bfi	r3, lr, #0, #10
	str	r3, [r9, #1064]
	ldr	r6, [r4, #3984]
	mov	r3, ip
	ldr	lr, [r4, #3952]
	bfi	r3, r6, #16, #9
	bfi	r3, lr, #0, #9
	str	r3, [r9, #1068]
	ldr	r6, [r4, #3988]
	mov	r3, ip
	ldr	lr, [r4, #3956]
	bfi	r3, r6, #16, #9
	bfi	r3, lr, #0, #9
	str	r3, [r9, #1072]
	ldr	r6, [r4, #3992]
	ldr	lr, [r4, #3960]
	bfi	ip, r6, #16, #9
	bfi	ip, lr, #0, #9
	str	ip, [r9, #1076]
	ldr	lr, [r4, #3996]
	ldr	ip, [r4, #3964]
	bfi	r0, lr, #16, #9
	bfi	r0, ip, #0, #9
	str	r0, [r9, #1080]
	ldr	ip, [r4, #4000]
	ldr	r0, [r4, #3968]
	bfi	r1, ip, #16, #9
	bfi	r1, r0, #0, #9
	str	r1, [r9, #1084]
	ldr	r0, [r4, #4004]
	ldr	r1, [r4, #3972]
	bfi	r7, r0, #16, #9
	bfi	r7, r1, #0, #9
	str	r7, [r9, #1088]
	ldr	r0, [r4, #4008]
	ldr	r1, [r4, #3976]
	bfi	r2, r0, #16, #9
	bfi	r2, r1, #0, #9
	str	r2, [r9, #1092]
	ldr	r1, [r4, #4012]
	ldr	r2, [r4, #3980]
	bfi	r5, r1, #16, #9
	bfi	r5, r2, #0, #9
	str	r5, [r9, #1096]
	ldr	r3, [r8, #4]
	ldr	r0, [r8, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r7, #16
	movne	r7, #64
	mov	r1, r7
	add	r0, r0, r7
	bl	__aeabi_uidiv
	ldr	r3, [r8, #16]
	mov	r1, r7
	mov	r6, r0
	sub	r0, r3, #1
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r1, r6, r0
	ldr	r0, [r8, #540]
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r7, r3
	mov	r2, r3
	str	r3, [fp, #-52]
	mov	r1, r3
	str	r3, [fp, #-60]
	mov	ip, r3
	str	r3, [fp, #-64]
	mov	lr, r3
	str	r3, [fp, #-68]
	mov	r6, r3
	str	r3, [fp, #-72]
	mov	r5, r3
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
	bfi	r3, r0, #0, #20
	ldr	r0, [fp, #-48]
	str	r3, [r0, #588]
	mov	r3, r2
	ldr	r0, [r4, #2436]
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2440]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #1536]
	ldr	r0, [r10, #700]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2444]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #1540]
	ldr	r0, [r4, #2448]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2452]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #1544]
	ldr	r0, [r4, #2456]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #704]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #1548]
	ldr	r0, [r4, #2460]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2464]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #1552]
	ldr	r0, [r10, #708]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #712]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #1556]
	ldr	r0, [r4, #2468]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2472]
	bfi	r3, r0, #0, #10
	str	r3, [r9, #1560]
	ldr	r0, [r10, #716]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r10, #720]
	bfi	r3, r0, #0, #8
	str	r3, [r9, #1564]
	ldr	r0, [r4, #2476]
	bfi	r6, r0, #12, #4
	ldr	r0, [r4, #2480]
	bfi	r6, r0, #8, #4
	ldr	r0, [r4, #2484]
	bfi	r6, r0, #4, #4
	ldr	r0, [r4, #2488]
	bfi	r6, r0, #0, #4
	ldr	r0, [r4, #2492]
	bfi	r6, r0, #28, #4
	ldr	r0, [r10, #724]
	bfi	r6, r0, #24, #4
	ldr	r0, [r4, #2496]
	bfi	r6, r0, #20, #4
	ldr	r0, [r4, #2500]
	bfi	r6, r0, #16, #4
	str	r6, [r9, #1568]
	ldr	r0, [r4, #2504]
	mov	r6, r7
	bfi	lr, r0, #12, #4
	ldr	r0, [r4, #2508]
	bfi	lr, r0, #8, #4
	ldr	r0, [r4, #2512]
	bfi	lr, r0, #4, #4
	ldr	r0, [r4, #2516]
	bfi	lr, r0, #0, #4
	ldr	r0, [r4, #2520]
	bfi	lr, r0, #28, #4
	ldr	r0, [r4, #2524]
	bfi	lr, r0, #24, #4
	ldr	r0, [r10, #728]
	bfi	lr, r0, #20, #4
	ldr	r0, [r4, #2528]
	bfi	lr, r0, #16, #4
	str	lr, [r9, #1572]
	ldr	r0, [r4, #2532]
	mov	lr, r7
	bfi	ip, r0, #12, #4
	ldr	r0, [r4, #2536]
	bfi	ip, r0, #8, #4
	ldr	r0, [r4, #2540]
	bfi	ip, r0, #4, #4
	ldr	r0, [r4, #2544]
	bfi	ip, r0, #0, #4
	ldr	r0, [r4, #2548]
	bfi	ip, r0, #28, #4
	ldr	r0, [r4, #2552]
	bfi	ip, r0, #24, #4
	ldr	r0, [r10, #732]
	bfi	ip, r0, #20, #4
	ldr	r0, [r4, #2556]
	bfi	ip, r0, #16, #4
	str	ip, [r9, #1576]
	ldr	r0, [r4, #2560]
	mov	ip, r7
	bfi	r1, r0, #12, #4
	ldr	r0, [r10, #736]
	bfi	r1, r0, #8, #4
	ldr	r0, [r4, #2564]
	bfi	r1, r0, #4, #4
	ldr	r0, [r4, #2568]
	bfi	r1, r0, #0, #4
	ldr	r0, [r4, #2572]
	bfi	r1, r0, #28, #4
	ldr	r0, [r4, #2576]
	bfi	r1, r0, #24, #4
	ldr	r0, [r4, #2580]
	bfi	r1, r0, #20, #4
	ldr	r0, [r4, #2584]
	bfi	r1, r0, #16, #4
	str	r1, [r9, #1580]
	ldr	r1, [r4, #2588]
	mov	r0, r7
	bfi	r2, r1, #12, #4
	ldr	r1, [r4, #2592]
	bfi	r2, r1, #8, #4
	ldr	r1, [r10, #740]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #2596]
	bfi	r2, r1, #0, #4
	ldr	r1, [r4, #2600]
	bfi	r2, r1, #28, #4
	ldr	r1, [r4, #2604]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #2608]
	bfi	r2, r1, #20, #4
	ldr	r1, [r4, #2612]
	bfi	r2, r1, #16, #4
	str	r2, [r9, #1584]
	ldr	r2, [r4, #2616]
	mov	r1, r7
	bfi	r5, r2, #12, #4
	ldr	r2, [r4, #2620]
	bfi	r5, r2, #8, #4
	ldr	r2, [r10, #744]
	bfi	r5, r2, #4, #4
	ldr	r2, [r4, #2624]
	bfi	r5, r2, #0, #4
	ldr	r2, [r4, #2628]
	bfi	r5, r2, #28, #4
	ldr	r2, [r4, #2632]
	bfi	r5, r2, #24, #4
	ldr	r2, [r4, #2636]
	bfi	r5, r2, #20, #4
	ldr	r2, [r4, #2640]
	bfi	r5, r2, #16, #4
	str	r5, [r9, #1588]
	ldr	r3, [r4, #2644]
	mov	r2, r7
	mov	r5, r7
	bfi	r2, r3, #12, #4
	ldr	r3, [r10, #748]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2648]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2652]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2656]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2660]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2664]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2668]
	bfi	r2, r3, #16, #4
	str	r2, [r9, #1592]
	ldr	r3, [r4, #2672]
	mov	r2, r7
	bfi	r2, r3, #12, #4
	ldr	r3, [r4, #2676]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2680]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2684]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2688]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2692]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2696]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2700]
	bfi	r2, r3, #16, #4
	str	r2, [r9, #1596]
	ldr	r3, [r4, #2704]
	mov	r2, r7
	bfi	r2, r3, #12, #4
	ldr	r3, [r4, #2708]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2712]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2716]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2720]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2724]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2728]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2732]
	bfi	r2, r3, #16, #4
	str	r2, [r9, #1600]
	ldr	r3, [r4, #2736]
	mov	r2, r7
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2740]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2744]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2748]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2752]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2756]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2760]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #1604]
	ldr	r3, [r4, #2764]
	mov	r2, r7
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2768]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2772]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2776]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2780]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2784]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2788]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #1608]
	ldr	r3, [r4, #2792]
	mov	r2, r7
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2796]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2800]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2804]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2808]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2812]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2816]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #1612]
	ldr	r3, [r4, #3084]
	mov	r2, r7
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #3088]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #3092]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #3096]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #3100]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #3104]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #3108]
	bfi	r2, r3, #26, #4
	str	r2, [r9, #1616]
	ldr	r3, [r4, #3112]
	mov	r2, r7
	bfi	r6, r3, #0, #3
	ldr	r3, [r4, #3116]
	bfi	r6, r3, #3, #7
	ldr	r3, [r4, #3120]
	bfi	r6, r3, #10, #3
	ldr	r3, [r4, #3124]
	bfi	r6, r3, #13, #5
	ldr	r3, [r4, #3128]
	bfi	r6, r3, #18, #4
	ldr	r3, [r4, #3132]
	bfi	r6, r3, #22, #4
	ldr	r3, [r4, #3136]
	bfi	r6, r3, #26, #4
	str	r6, [r9, #1620]
	ldr	r6, [r10, #760]
	mov	r3, r7
	bfi	r2, r6, #0, #3
	ldr	r6, [r4, #3140]
	bfi	r2, r6, #3, #7
	ldr	r6, [r4, #3144]
	bfi	r2, r6, #10, #3
	ldr	r6, [r4, #3148]
	bfi	r2, r6, #13, #5
	ldr	r6, [r4, #3152]
	bfi	r2, r6, #18, #4
	ldr	r6, [r4, #3156]
	bfi	r2, r6, #22, #4
	ldr	r6, [r4, #3160]
	bfi	r2, r6, #26, #4
	str	r2, [r9, #1624]
	ldr	r6, [r4, #3164]
	mov	r2, r7
	bfi	r2, r6, #0, #3
	ldr	r6, [r4, #3168]
	bfi	r2, r6, #3, #7
	ldr	r6, [r4, #3172]
	bfi	r2, r6, #10, #3
	ldr	r6, [r4, #3176]
	bfi	r2, r6, #13, #5
	ldr	r6, [r4, #3180]
	bfi	r2, r6, #18, #4
	ldr	r6, [r4, #3184]
	bfi	r2, r6, #22, #4
	ldr	r6, [r4, #3188]
	bfi	r2, r6, #26, #4
	str	r2, [r9, #1628]
	ldr	r6, [r4, #2820]
	mov	r2, r7
	bfi	r7, r6, #0, #4
	ldr	r6, [r4, #2824]
	bfi	r7, r6, #4, #4
	ldr	r6, [r4, #2828]
	bfi	r7, r6, #8, #4
	ldr	r6, [r4, #2832]
	bfi	r7, r6, #12, #4
	ldr	r6, [r4, #2836]
	bfi	r7, r6, #16, #4
	ldr	r6, [r4, #2840]
	bfi	r7, r6, #20, #4
	ldr	r6, [r4, #2844]
	bfi	r7, r6, #24, #4
	ldr	r6, [r4, #2848]
	bfi	r7, r6, #28, #4
	str	r7, [r9, #1632]
	ldr	r6, [r4, #2852]
	mov	r7, ip
	bfi	r2, r6, #0, #4
	ldr	r6, [r4, #2856]
	bfi	r2, r6, #4, #4
	ldr	r6, [r4, #2860]
	bfi	r2, r6, #8, #4
	ldr	r6, [r4, #2864]
	bfi	r2, r6, #12, #4
	ldr	r6, [r4, #2868]
	bfi	r2, r6, #16, #4
	ldr	r6, [r4, #2872]
	bfi	r2, r6, #20, #4
	str	r2, [r9, #1636]
	ldr	r6, [r4, #2876]
	mov	r2, r3
	bfi	ip, r6, #0, #10
	ldr	r6, [r4, #2880]
	bfi	ip, r6, #16, #5
	str	ip, [r9, #1640]
	ldr	ip, [r10, #752]
	mov	r6, lr
	bfi	lr, ip, #0, #8
	ldr	ip, [r10, #756]
	bfi	lr, ip, #16, #5
	str	lr, [r9, #1644]
	ldr	ip, [r4, #2884]
	mov	lr, r0
	bfi	r0, ip, #0, #10
	ldr	ip, [r4, #2888]
	bfi	r0, ip, #16, #5
	str	r0, [r9, #1648]
	ldr	r0, [r4, #2892]
	mov	ip, r1
	bfi	r7, r0, #0, #8
	ldr	r0, [r4, #2896]
	bfi	r7, r0, #16, #5
	str	r7, [r9, #1652]
	ldr	r7, [r4, #2900]
	mov	r0, r1
	bfi	r1, r7, #0, #10
	ldr	r7, [r4, #2904]
	bfi	r1, r7, #16, #5
	str	r1, [r9, #1656]
	ldr	r7, [r4, #2908]
	mov	r1, r5
	bfi	r5, r7, #0, #8
	ldr	r7, [r4, #2912]
	bfi	r5, r7, #16, #5
	str	r5, [r9, #1660]
	ldr	r7, [r4, #3192]
	bfi	r3, r7, #0, #4
	ldr	r7, [r4, #3196]
	bfi	r3, r7, #4, #4
	ldr	r7, [r4, #3200]
	bfi	r3, r7, #8, #4
	ldr	r7, [r4, #3204]
	bfi	r3, r7, #12, #4
	ldr	r7, [r4, #3208]
	bfi	r3, r7, #16, #4
	ldr	r7, [r4, #3212]
	bfi	r3, r7, #20, #4
	str	r3, [r9, #1664]
	ldr	r7, [r10, #764]
	bfi	r2, r7, #0, #12
	ldr	r7, [r10, #768]
	bfi	r2, r7, #12, #12
	ldr	r7, [r4, #3216]
	bfi	r2, r7, #24, #8
	str	r2, [r9, #1668]
	ldr	r3, [r4, #3220]
	mov	r2, r6
	mov	r7, r6
	bfc	r7, #14, #1
	bfi	r2, r3, #0, #12
	ldr	r3, [r4, #3224]
	bfc	r7, #15, #1
	bfi	r2, r3, #12, #12
	ldr	r3, [r4, #3228]
	bfi	r2, r3, #24, #8
	str	r2, [r9, #1672]
	mov	r2, r6
	ldr	r3, [r10, #772]
	bfc	r2, #0, #8
	mov	r5, r2
	mov	r2, r6
	bfi	r2, r3, #0, #12
	orr	r3, r5, #65280
	ldr	r5, [r4, #3232]
	movt	r3, 65280
	str	r3, [fp, #-56]
	bfi	r2, r5, #12, #12
	ldr	r5, [r4, #3236]
	mov	r3, r6
	bfi	r2, r5, #24, #8
	str	r2, [r9, #1676]
	ldr	r5, [r4, #3240]
	mov	r2, r6
	bfi	r2, r5, #0, #8
	ldr	r5, [r4, #3244]
	bfi	r2, r5, #8, #8
	ldr	r5, [r4, #3248]
	bfi	r2, r5, #16, #8
	str	r2, [r9, #1680]
	ldr	r5, [r4, #2916]
	mov	r2, r6
	bfi	r6, r5, #0, #1
	ldr	r5, [r4, #2920]
	bfi	r6, r5, #1, #3
	ldr	r5, [r4, #2924]
	bfi	r6, r5, #4, #6
	ldr	r5, [r4, #2928]
	bfi	r6, r5, #10, #5
	ldr	r5, [r4, #2932]
	bfi	r6, r5, #15, #6
	ldr	r5, [r4, #2936]
	bfi	r6, r5, #21, #5
	str	r6, [r9, #1684]
	ldr	r6, [r4, #2940]
	mov	r5, lr
	bfi	lr, r6, #0, #1
	ldr	r6, [r4, #2944]
	bfi	lr, r6, #1, #3
	ldr	r6, [r4, #2948]
	bfi	lr, r6, #4, #6
	ldr	r6, [r4, #2952]
	bfi	lr, r6, #10, #5
	ldr	r6, [r4, #2956]
	bfi	lr, r6, #15, #6
	ldr	r6, [r4, #2960]
	bfi	lr, r6, #21, #5
	str	lr, [r9, #1688]
	ldr	lr, [r4, #2964]
	mov	r6, ip
	bfi	ip, lr, #0, #1
	ldr	lr, [r4, #2968]
	bfi	ip, lr, #1, #3
	ldr	lr, [r4, #2972]
	bfi	ip, lr, #4, #6
	ldr	lr, [r4, #2976]
	bfi	ip, lr, #10, #5
	ldr	lr, [r4, #2980]
	bfi	ip, lr, #15, #6
	ldr	lr, [r4, #2984]
	bfi	ip, lr, #21, #5
	str	ip, [r9, #1692]
	ldr	lr, [r4, #2988]
	mov	ip, r0
	bfi	r0, lr, #0, #1
	ldr	lr, [r4, #2992]
	bfi	r0, lr, #1, #3
	ldr	lr, [r4, #2996]
	bfi	r0, lr, #4, #6
	ldr	lr, [r4, #3000]
	bfi	r0, lr, #10, #5
	ldr	lr, [r4, #3004]
	bfi	r0, lr, #15, #6
	ldr	lr, [r4, #3008]
	bfi	r0, lr, #21, #5
	str	r0, [r9, #1696]
	ldr	r0, [r4, #3012]
	mov	lr, r1
	bfi	r1, r0, #0, #1
	ldr	r0, [r4, #3016]
	bfi	r1, r0, #1, #3
	ldr	r0, [r4, #3020]
	bfi	r1, r0, #4, #6
	ldr	r0, [r4, #3024]
	bfi	r1, r0, #10, #5
	ldr	r0, [r4, #3028]
	bfi	r1, r0, #15, #6
	ldr	r0, [r4, #3032]
	bfi	r1, r0, #21, #5
	str	r1, [r9, #1700]
	ldr	r0, [r4, #3036]
	mov	r1, r3
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #3040]
	bfi	r2, r0, #1, #3
	ldr	r0, [r4, #3044]
	bfi	r2, r0, #4, #6
	ldr	r0, [r4, #3048]
	bfi	r2, r0, #10, #5
	ldr	r0, [r4, #3052]
	bfi	r2, r0, #15, #6
	ldr	r0, [r4, #3056]
	bfi	r2, r0, #21, #5
	str	r2, [r9, #1704]
	ldr	r2, [r4, #3060]
	mov	r0, r5
	bfi	r3, r2, #0, #1
	ldr	r2, [r4, #3064]
	bfi	r3, r2, #1, #3
	ldr	r2, [r4, #3068]
	bfi	r3, r2, #4, #6
	ldr	r2, [r4, #3072]
	bfi	r3, r2, #10, #5
	ldr	r2, [r4, #3076]
	bfi	r3, r2, #15, #6
	ldr	r2, [r4, #3080]
	bfi	r3, r2, #21, #5
	str	r3, [r9, #1708]
	ldr	r3, [r4, #2316]
	ldr	r2, [fp, #-56]
	bfi	r7, r3, #20, #8
	ldr	r3, [r8, #40]
	str	r5, [fp, #-56]
	str	r2, [r9, #12]
	bfi	r7, r3, #28, #1
	str	r7, [r9, #8]
	mov	r2, r5
	ldr	r3, [r4, #3572]
	mov	r7, r5
	bfi	r2, r3, #0, #1
	str	r2, [r9, #1824]
	ldr	r3, [r4, #3576]
	mov	r2, r5
	bfi	r2, r3, #0, #16
	str	r2, [r9, #1828]
	ldr	r3, [r4, #3580]
	mov	r2, r5
	bfi	r2, r3, #0, #16
	str	r2, [r9, #1832]
	ldr	r3, [r4, #3584]
	mov	r2, r5
	bfi	r6, r3, #0, #16
	str	r6, [r9, #1836]
	ldr	r3, [r4, #3588]
	mov	r6, r5
	ldr	r5, [r4, #3592]
	bfi	ip, r3, #18, #9
	ldr	r3, [r4, #3596]
	bfi	ip, r5, #9, #9
	bfi	ip, r3, #0, #9
	str	ip, [r9, #1844]
	ldr	r3, [r4, #3600]
	mov	ip, lr
	ldr	r5, [r4, #3604]
	bfi	lr, r3, #16, #8
	ldr	r3, [r4, #3608]
	bfi	lr, r5, #8, #8
	mov	r5, #20
	bfi	lr, r3, #0, #8
	str	lr, [r9, #1848]
	ldr	r3, [r4, #3612]
	ldr	lr, [r4, #3616]
	bfi	r1, r3, #8, #4
	ldr	r3, [r4, #3620]
	bfi	r1, lr, #4, #4
	mov	lr, r7
	bfi	r1, r3, #0, #4
	mov	r3, #3
	bfi	r1, r3, #20, #8
	mov	r3, r7
	bfi	r1, r5, #12, #8
	str	r1, [r9, #1852]
	ldr	r1, [r4, #3720]
	mov	r5, r0
	bfi	r7, r1, #0, #16
	bfc	r7, #16, #8
	bfc	r7, #24, #8
	str	r7, [r9, #1856]
	ldr	r1, [r4, #3736]
	mov	r7, r0
	bfi	r5, r1, #0, #8
	ldr	r1, [r4, #3732]
	bfi	r5, r1, #8, #8
	ldr	r1, [r4, #3728]
	bfi	r5, r1, #16, #8
	ldr	r1, [r4, #3724]
	bfi	r5, r1, #24, #8
	str	r5, [r9, #1860]
	ldr	r1, [r4, #3624]
	mov	r5, #1
	bfi	r0, r1, #24, #8
	ldr	r1, [r4, #3628]
	bfi	r0, r1, #16, #8
	ldr	r1, [r4, #3632]
	bfi	r0, r1, #8, #8
	ldr	r1, [r4, #3636]
	bfi	r0, r1, #0, #8
	str	r0, [r9, #1872]
	ldr	r1, [r4, #3640]
	mov	r0, r2
	bfi	r2, r1, #0, #8
	ldr	r1, [r4, #3644]
	bfi	r2, r1, #8, #8
	ldr	r1, [r4, #3648]
	bfi	r2, r1, #16, #1
	ldr	r1, [r4, #3764]
	bfi	r2, r1, #17, #1
	str	r2, [r9, #1876]
	ldr	r1, [r4, #3652]
	mov	r2, r6
	bfi	r0, r1, #0, #16
	ldr	r1, [r4, #3656]
	bfi	r0, r1, #16, #16
	str	r0, [r9, #1880]
	ldr	r1, [r10, #1180]
	bfi	ip, r1, #22, #9
	ldr	r1, [r10, #1184]
	bfi	ip, r1, #17, #5
	ldr	r1, [r10, #1188]
	bfi	ip, r1, #9, #8
	ldr	r1, [r10, #1208]
	bfi	ip, r1, #0, #9
	str	ip, [r9, #1884]
	ldr	r1, [r10, #1204]
	mov	ip, r6
	bfi	ip, r1, #8, #14
	ldr	r1, [r4, #3660]
	bfi	ip, r1, #0, #8
	str	ip, [r9, #1792]
	ldr	r0, [r10, #1192]
	mov	r1, r6
	bfi	lr, r0, #16, #8
	ldr	r0, [r10, #1196]
	bfi	lr, r0, #8, #8
	ldr	r0, [r10, #1200]
	bfi	lr, r0, #0, #8
	str	lr, [r9, #1796]
	ldr	ip, [r4, #3668]
	mov	lr, r6
	mov	r0, r6
	bfi	r3, ip, #17, #1
	ldr	ip, [r4, #3672]
	bfi	r3, ip, #12, #2
	ldr	ip, [r4, #3676]
	bfi	r3, ip, #4, #4
	ldr	ip, [r4, #3680]
	bfi	r3, ip, #0, #4
	str	r3, [r9, #1800]
	ldr	r3, [r4, #3684]
	mov	ip, r6
	bfi	lr, r3, #0, #10
	ldr	r3, [r4, #3688]
	bfi	lr, r3, #16, #9
	str	lr, [r9, #1808]
	ldr	lr, [r4, #3692]
	mov	r3, r6
	bfi	r3, r5, #0, #8
	bfi	ip, lr, #0, #10
	ldr	lr, [r4, #3696]
	bfi	r3, r5, #8, #8
	bfi	ip, lr, #16, #9
	str	ip, [r9, #1812]
	ldr	ip, [r4, #3700]
	movt	r3, 200
	ldr	lr, [r4, #3704]
	bfi	r7, ip, #0, #10
	mov	ip, r6
	bfi	r7, lr, #16, #9
	str	r7, [r9, #1816]
	ldr	r7, [r4, #3708]
	ldr	lr, [r4, #3712]
	bfi	r6, r7, #0, #10
	ldr	r7, [fp, #-48]
	bfi	r6, lr, #16, #9
	str	r6, [r9, #1820]
	ldr	lr, [r4, #3716]
	mov	r6, r2
	bfi	r6, lr, #0, #16
	str	r6, [r9, #1804]
	ldr	r6, [r4, #3740]
	ldr	lr, [r4, #3744]
	bfi	r2, r6, #0, #13
	bfi	r2, lr, #13, #1
	str	r2, [r9, #36]
	ldr	r2, [r4, #3748]
	mov	lr, r1
	bfi	lr, r2, #0, #18
	str	lr, [r9, #40]
	ldr	r2, [r4, #3752]
	mov	lr, r1
	bfi	lr, r2, #0, #18
	str	lr, [r9, #44]
	ldr	lr, [r4, #3776]
	ldr	r2, [r4, #3780]
	bfi	r1, lr, #16, #7
	bfi	r1, r2, #23, #7
	str	r1, [r7, #1792]
	ldr	r2, [r4, #3768]
	ldr	r1, [r4, #3772]
	bfi	r0, r2, #0, #8
	ldr	r2, [r4, #3756]
	bfi	r0, r1, #8, #8
	bfi	r0, r2, #16, #8
	str	r0, [r7, #1796]
	ldr	r2, [r4, #3760]
	ldr	r1, [r4, #3784]
	bfi	ip, r2, #12, #8
	ldr	r2, [r4, #3788]
	bfi	ip, r1, #8, #4
	bfi	ip, r2, #0, #8
	str	ip, [r7, #1800]
	str	r3, [r7, #1804]
	ldr	r2, [r8, #4]
	cmp	r2, #0
	bne	.L144
	mov	r1, #23
	mov	r3, #0
	bfi	r3, r1, #0, #5
	mov	r0, #15
	bfi	r3, r0, #5, #5
	bfi	r3, r1, #10, #5
	bfi	r3, r0, #15, #5
	bfi	r3, r2, #20, #1
	str	r3, [r9, #24]
.L145:
	mov	r1, #16
	mov	r2, #0
	mov	r3, #0
	bfc	r2, #16, #16
	bfi	r3, r1, #6, #6
	bfc	r2, #0, #16
	mov	r1, #10
	str	r2, [r9, #552]
	bfi	r3, r1, #0, #6
	mov	r2, #2
	str	r3, [r9, #556]
	mov	r3, #0
	str	r2, [r9, #548]
	ldr	r2, [r8, #552]
	ldr	r0, [r8, #548]
	bfi	r3, r2, #8, #6
	ldr	r1, [r4, #3380]
	orr	r3, r3, #64
	ldr	r2, [r4, #3352]
	bfi	r3, r0, #0, #6
	bfi	r3, r1, #16, #6
	bfi	r3, r2, #24, #4
	ldr	r2, [fp, #-48]
	str	r3, [r2, #3076]
	ldr	r3, [r8, #4]
	ldr	r0, [r8, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r7, #16
	movne	r7, #64
	mov	r1, r7
	add	r0, r0, r7
	bl	__aeabi_uidiv
	ldr	r3, [r8, #16]
	mov	r1, r7
	mov	r6, r0
	sub	r0, r3, #1
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r1, r6, r0
	ldr	r0, [r8, #540]
	bl	__aeabi_uidiv
	mov	r3, #0
	ldr	r5, [r4, #3368]
	mov	r6, r3
	mov	lr, r3
	mov	ip, r3
	mov	r1, r3
	str	r3, [fp, #-52]
	str	r3, [fp, #-56]
	mov	r2, r3
	mov	r7, r3
	bfi	r6, r0, #0, #16
	bfi	r6, r5, #16, #6
	ldr	r5, [fp, #-48]
	str	r6, [r5, #3080]
	mov	r6, r5
	ldr	r0, [r10, #792]
	bfi	lr, r0, #0, #6
	ldr	r0, [r4, #3360]
	bfi	lr, r0, #24, #6
	ldr	r0, [r4, #3364]
	bfi	lr, r0, #16, #6
	ldr	r0, [r4, #3372]
	bfi	lr, r0, #8, #6
	str	lr, [r5, #3084]
	ldr	r0, [r10, #808]
	ldr	lr, [r10, #804]
	ldr	r5, [r10, #800]
	bfi	ip, r0, #24, #8
	bfi	ip, lr, #16, #8
	ldr	r0, [r10, #796]
	bfi	ip, r5, #8, #8
	mov	r5, #0
	bfi	ip, r0, #0, #8
	str	ip, [r6, #3088]
	ldr	r0, [r10, #824]
	ldr	ip, [r10, #820]
	ldr	lr, [r10, #816]
	bfi	r1, r0, #24, #8
	bfi	r1, ip, #16, #8
	ldr	r0, [r10, #812]
	bfi	r1, lr, #8, #8
	bfi	r1, r0, #0, #8
	str	r1, [r6, #3092]
	ldr	r1, [r10, #840]
	ldr	r0, [r10, #836]
	bfi	r2, r1, #24, #8
	ldr	ip, [r10, #832]
	ldr	r1, [r10, #828]
	bfi	r2, r0, #16, #8
	bfi	r2, ip, #8, #8
	mov	r0, r6
	bfi	r2, r1, #0, #8
	str	r2, [r6, #3096]
	ldr	r1, [r10, #856]
	ldr	r2, [r10, #852]
	bfi	r3, r1, #24, #8
	ldr	r1, [r10, #848]
	bfi	r3, r2, #16, #8
	ldr	r2, [r10, #844]
	bfi	r3, r1, #8, #8
	mov	r1, r7
	bfi	r3, r2, #0, #8
	str	r3, [r6, #3072]
	ldr	r2, [r4, #3396]
	ldr	r3, [r4, #3400]
	bfi	r1, r2, #0, #4
	mov	r2, r1
	bfi	r2, r3, #4, #4
	str	r2, [r0, #3100]
	ldr	r3, [r4, #3344]
	bfi	r7, r3, #0, #4
	str	r7, [r6, #3104]
	ldr	r2, [r4, #3340]
	ldr	r3, [r4, #3348]
	bfi	r5, r2, #0, #4
	bfi	r5, r3, #4, #4
	str	r5, [r6, #3108]
	ldr	r3, [r8, #4]
	ldr	r6, [fp, #-48]
	cmp	r3, #0
	ldrne	r2, [r10, #776]
	moveq	r2, #3
	movne	r3, #0
	bfi	r3, r2, #0, #4
	str	r3, [r6, #3112]
	ldr	r1, [r4, #3272]
	mov	r3, #0
	ldr	r2, [r4, #3276]
	mov	ip, r3
	mov	r0, r3
	bfi	r3, r1, #0, #2
	ldr	r1, [r4, #3280]
	bfi	r3, r2, #2, #2
	ldr	r2, [r4, #3284]
	bfi	r3, r1, #4, #2
	ldr	r1, [r4, #3288]
	bfi	r3, r2, #6, #2
	ldr	r2, [r4, #3292]
	bfi	r3, r1, #8, #2
	ldr	r1, [r4, #3296]
	bfi	r3, r2, #10, #2
	ldr	r2, [r4, #3300]
	bfi	r3, r1, #12, #2
	ldr	r1, [r4, #3304]
	bfi	r3, r2, #14, #2
	ldr	r2, [r4, #3308]
	bfi	r3, r1, #16, #2
	ldr	r1, [r4, #3312]
	bfi	r3, r2, #18, #2
	ldr	r2, [r4, #3316]
	bfi	r3, r1, #20, #2
	ldr	r1, [r4, #3320]
	bfi	r3, r2, #22, #2
	ldr	r2, [r4, #3324]
	bfi	r3, r1, #24, #2
	ldr	r1, [r4, #3328]
	bfi	r3, r2, #26, #2
	ldr	r2, [r4, #3332]
	bfi	r3, r1, #28, #2
	ldr	r5, [fp, #-132]
	bfi	r3, r2, #30, #2
	str	r3, [r6, #3116]
	ldr	lr, [r4, #3336]
	add	r1, r9, #1088
	add	r1, r1, #12
	add	r2, r10, #856
	bfi	ip, lr, #0, #5
	str	ip, [r6, #3120]
	ldr	ip, [r4, #3384]
	add	r3, r10, #920
	ldr	lr, [r4, #3388]
	bfi	r0, ip, #24, #4
	ldr	ip, [r4, #3392]
	bfi	r0, lr, #28, #4
	ldr	lr, [r4, #3356]
	bfi	r0, ip, #16, #6
	ldr	ip, [r4, #3376]
	bfi	r0, lr, #8, #4
	bfi	r0, ip, #0, #6
	str	r0, [r6, #3124]
.L149:
	ldr	r0, [r2, #4]!
	cmp	r2, r3
	bfi	r5, r0, #0, #20
	str	r5, [r1, #4]!
	bne	.L149
	add	r0, r10, #1168
	add	r2, r9, #1264
	add	r0, r0, #8
	add	r2, r2, #12
.L150:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	bfi	r5, r1, #0, #20
	str	r5, [r2, #4]!
	bne	.L150
	ldr	ip, [fp, #-48]
	mov	r2, #0
	mov	r0, r2
	mov	r1, r2
	bfi	r0, r2, #0, #16
	bfi	r1, r2, #0, #16
	mov	r3, r2
	bfi	r3, r2, #16, #16
	str	r2, [ip, #3660]
	bfi	r0, r2, #16, #16
	str	r2, [r9, #572]
	bfi	r1, r2, #16, #16
	str	r0, [r9, #584]
	bfi	r3, r2, #0, #16
	str	r1, [r9, #588]
	mov	ip, r2
	str	r3, [r9, #592]
	mvn	r1, #0
	str	r2, [r9, #580]
	mov	r3, #7
	str	r1, [r9, #596]
	bfi	ip, r2, #0, #1
	str	r1, [r9, #604]
	mov	r0, r2
	str	ip, [r9, #564]
	bfi	r0, r2, #0, #1
	str	r1, [r9, #612]
	mov	lr, r2
	str	r0, [r9, #568]
	mov	r0, #13
	str	r1, [r9, #620]
	mov	ip, r2
	str	r0, [r9, #576]
	mov	r0, r2
	str	r3, [r9, #600]
	mov	r1, r2
	str	r3, [r9, #608]
	str	r3, [r9, #616]
	str	r3, [r9, #624]
	ldr	r3, [r4, #4064]
	bfi	lr, r3, #0, #1
	str	lr, [r9, #120]
	ldr	r3, [r8, #172]
	str	r3, [r9, #96]
	ldr	r3, [r8, #176]
	str	r3, [r9, #100]
	ldr	r3, [r8, #180]
	str	r3, [r9, #104]
	ldr	r3, [r8, #184]
	str	r3, [r9, #108]
	ldr	r3, [r8, #188]
	str	r3, [r9, #112]
	ldr	r3, [r8, #192]
	str	r3, [r9, #116]
	ldr	lr, [r4, #3252]
	ldr	r3, [r4, #3256]
	bfi	r0, lr, #0, #16
	bfi	r0, r3, #16, #16
	str	r0, [r9, #1728]
	ldr	r3, [r4, #3268]
	bfi	ip, r3, #16, #16
	str	ip, [r9, #1732]
	ldr	r0, [r4, #3260]
	ldr	r3, [r4, #3264]
	bfi	r1, r0, #0, #16
	bfi	r1, r3, #16, #16
	str	r1, [r9, #1736]
	ldr	r1, [r8, #4]
	ldr	r3, [r8, #688]
	cmp	r1, #2
	beq	.L194
	ldr	ip, [r8, #600]
	mov	r1, #0
	mov	r0, r1
	bfi	r0, r2, #0, #1
	str	ip, [r3, #256]
	ldr	r2, [r8, #604]
	str	r2, [r3, #260]
	ldr	r2, [r8, #608]
	str	r2, [r3, #264]
	ldr	r2, [r8, #612]
	str	r2, [r3, #268]
	ldr	r2, [r8, #616]
	str	r2, [r3, #272]
	ldr	r2, [r8, #620]
	str	r2, [r3, #276]
	ldr	r2, [r8, #624]
	str	r2, [r3, #280]
	ldr	r2, [r8, #628]
	str	r2, [r3, #284]
	ldr	r2, [r8, #632]
	str	r0, [r3, #292]
	sub	ip, r2, #1
	mov	r0, r2, lsr #8
	bfi	r1, ip, #16, #7
	sub	r0, r0, #1
	mov	r2, r2, lsr #16
	bfi	r1, r0, #8, #6
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #288]
.L159:
	ldr	r2, [r8, #4]
	cmp	r2, #2
	beq	.L195
	ldr	r2, [r4, #2352]
	mov	r1, #0
	str	r2, [r3, #296]
	ldr	r2, [r4, #2356]
	str	r2, [r3, #300]
	ldr	r2, [r4, #2360]
	str	r2, [r3, #304]
	ldr	r2, [r4, #2364]
	str	r2, [r3, #308]
	ldr	r2, [r4, #2368]
	str	r2, [r3, #312]
	ldr	r2, [r4, #2372]
	str	r2, [r3, #316]
	ldr	r2, [r4, #2376]
	str	r2, [r3, #320]
	ldr	r2, [r4, #2380]
	str	r2, [r3, #324]
	ldr	r2, [r4, #2348]
	sub	ip, r2, #1
	mov	r0, r2, lsr #8
	bfi	r1, ip, #16, #7
	sub	r0, r0, #1
	mov	r2, r2, lsr #16
	bfi	r1, r0, #8, #6
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #328]
.L166:
	ldr	r3, [fp, #-48]
	add	r2, r4, #4096
	ldr	r0, [r8, #264]
	mov	r1, #0
	add	r5, r3, #8192
	bfc	r1, #0, #1
	mov	r3, #0
	bfc	r3, #16, #8
	str	r0, [r9, #68]
	mov	ip, #0
	str	r1, [r5, #1040]
	mvn	r1, #84
	ldr	r2, [r2, #76]
	mov	r6, ip
	mov	r0, ip
	str	r2, [r5, #1044]
	ldr	r2, [r8, #536]
	cmp	r2, #0
	bfieq	r3, r2, #0, #1
	orrne	r3, r3, #1
	str	r3, [r9, #76]
	mov	r3, #0
	ldr	r2, [r8, #676]
	bfi	r3, r1, #0, #8
	str	ip, [r9, #84]
	mov	r1, #85
	str	ip, [r9, #88]
	bfi	r3, r1, #8, #8
	str	r2, [r9, #80]
	mov	r1, ip
	str	r3, [r9, #28]
	mov	r2, ip
	str	ip, [r9, #92]
	mov	r3, ip
	ldr	ip, [r4, #3404]
	ldr	lr, [r4, #3408]
	bfi	r1, ip, #0, #6
	ldr	ip, [r4, #3412]
	bfi	r1, lr, #8, #2
	ldr	lr, [r4, #3416]
	bfi	r1, ip, #10, #1
	ldr	ip, [r4, #3420]
	bfi	r1, lr, #12, #4
	bfi	r1, ip, #16, #5
	str	r1, [r5, #4048]
	ldr	r1, [r4, #3464]
	str	r1, [r5, #4052]
	ldr	r1, [r4, #3468]
	str	r1, [r5, #4056]
	ldr	ip, [r4, #3472]
	ldr	r1, [r4, #3476]
	bfi	r3, ip, #0, #16
	ldr	ip, [r4, #3480]
	bfi	r3, r1, #16, #2
	ldr	r1, [r4, #3484]
	bfi	r3, ip, #18, #2
	ldr	ip, [r4, #3488]
	bfi	r3, r1, #20, #4
	ldr	r1, [r4, #3496]
	bfi	r3, ip, #24, #1
	ldr	ip, [r4, #3500]
	bfi	r3, r1, #25, #2
	ldr	r1, [r4, #3492]
	bfi	r3, ip, #27, #1
	bfi	r3, r1, #28, #1
	str	r3, [r5, #4060]
	ldr	r1, [r4, #3532]
	ldr	r3, [r4, #3528]
	bfi	r2, r1, #0, #1
	ldr	r1, [r4, #3524]
	bfi	r2, r3, #2, #2
	ldr	r3, [r4, #3520]
	bfi	r2, r1, #4, #2
	ldr	r1, [r4, #3540]
	bfi	r2, r3, #6, #1
	ldr	r3, [r4, #3544]
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #24, #6
	str	r2, [r5, #4064]
	ldr	r2, [r4, #3548]
	ldr	r3, [r4, #3552]
	bfi	r0, r2, #0, #6
	ldr	r2, [r4, #3556]
	bfi	r0, r3, #8, #6
	ldr	r3, [r4, #3560]
	bfi	r0, r2, #16, #6
	bfi	r0, r3, #24, #6
	str	r0, [r5, #4068]
	ldr	r1, [r8, #4]
	ldr	r2, [r4, #3564]
	cmp	r1, r6
	ldr	r1, [r8, #16]
	ldr	r3, [r4, #3568]
	bfi	r6, r2, #0, #6
	ldr	r0, [r8, #540]
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #6
	bfi	r6, r3, #6, #25
	bl	__aeabi_uidiv
	add	r3, r4, #4096
	mov	r2, #0
	mov	r1, r2
	bfi	r6, r0, #6, #25
	str	r6, [r5, #4072]
	ldr	ip, [r8, #572]
	ldr	r0, [r8, #568]
	bfi	r2, ip, #10, #1
	ldr	ip, [r8, #564]
	bfi	r2, r0, #9, #1
	ldr	r0, [r3, #12]
	bfi	r2, ip, #8, #1
	ldr	ip, [r3, #16]
	bfi	r2, r0, #7, #1
	ldr	r0, [r4, #4088]
	bfi	r2, ip, #6, #1
	ldr	ip, [r4, #4084]
	bfi	r2, r0, #5, #1
	ldr	r0, [r3, #20]
	bfi	r2, ip, #4, #1
	ldr	ip, [r3, #24]
	ldr	r6, [fp, #-48]
	bfi	r2, r0, #3, #1
	ldr	r0, [r3, #28]
	bfi	r2, ip, #2, #1
	ldr	ip, [r3, #32]
	bfi	r2, r0, #1, #1
	mov	r0, r1
	bfi	r2, ip, #0, #1
	str	r2, [r6, #504]
	ldr	lr, [r4, #4092]
	mov	r2, r1
	ldr	r5, [r3, #36]
	bfi	r2, r0, #1, #1
	bfi	r1, lr, #7, #1
	ldr	lr, [r3, #40]
	bfi	r1, r5, #6, #1
	ldr	r5, [r3, #44]
	bfi	r1, lr, #5, #1
	ldr	lr, [r3, #48]
	bfi	r1, r5, #4, #1
	ldr	r5, [r3, #52]
	bfi	r1, lr, #3, #1
	ldr	lr, [r3, #56]
	bfi	r1, r5, #2, #1
	ldr	r3, [r3, #60]
	bfi	r1, lr, #1, #1
	add	ip, r6, #61440
	bfi	r1, r3, #0, #1
	str	r1, [r6, #508]
	ldr	r3, [r4, #4076]
	bfc	r2, #2, #1
	ldr	lr, [r4, #4080]
	mov	r1, #3
	bfi	r0, r3, #0, #1
	ldr	r3, .L199
	bfi	r0, lr, #3, #1
	bfc	r2, #3, #1
	bfi	r0, r1, #16, #4
	str	r0, [ip]
	ldr	r3, [r3]
	mov	r1, #1
	str	r2, [ip, #32]
	mov	r2, #0
	ldr	r0, [r8, #576]
	add	r3, r3, #61440
	str	r0, [r3, #520]
	ldr	r0, [r8, #576]
	str	r0, [r3, #524]
	ldr	r0, [r8, #584]
	str	r0, [r3, #752]
	ldr	r0, [r8, #580]
	str	r0, [r3, #756]
	ldr	r0, [r8, #584]
	str	r0, [r3, #772]
	ldr	r0, [r8, #580]
	str	r0, [r3, #776]
	mov	r0, #0
	str	r2, [ip, #8]
	str	r2, [r6, #16]
	str	r1, [r6, #16]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L193:
	mov	r3, #15
	mov	r2, #0
	bfi	r2, r3, #16, #6
	mov	r3, #31
	bfi	r2, r3, #0, #7
	str	r2, [fp, #-52]
	b	.L139
.L177:
	mov	r2, #6
.L140:
	bfi	r3, r2, #6, #4
	bfc	r3, #14, #1
.L141:
	ldrb	r2, [r8, #64]
	b	.L142
.L144:
	mov	r2, #15
	mov	r3, #0
	bfi	r3, r2, #0, #5
	bfi	r3, r2, #5, #5
	bfi	r3, r2, #10, #5
	bfi	r3, r2, #15, #5
	bfc	r3, #20, #1
	str	r3, [r9, #24]
	b	.L145
.L191:
	cmp	r3, #3
	clz	r3, r3
	movne	r2, #1
	moveq	r2, #0
	mov	r3, r3, lsr #5
	str	r2, [r4, #2324]
	str	r3, [r4, #2328]
	moveq	r2, #7
	movne	r2, #5
	str	r2, [r4, #2320]
	b	.L131
.L190:
	cmp	r2, #1920
	movcs	r3, #3
	strcs	r3, [r4, #2316]
	bcs	.L126
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r4, #2316]
	b	.L126
.L192:
	ldr	r2, [r8, #16]
	ldr	r3, [r8, #12]
	mov	r2, r2, lsr #2
	sub	r2, r2, #16
	mov	r3, r3, lsr #2
	sub	r3, r3, #16
	mov	r2, r2, lsr #1
	cmp	r2, #32
	mov	r3, r3, lsr #1
	movcs	r2, #32
	cmp	r3, #72
	bic	r2, r2, #-2147483645
	movcs	r3, #72
	cmp	r2, #7
	bic	r3, r3, #-2147483645
	movls	r2, #7
	bls	.L137
	cmp	r2, #32
	movcs	r2, #32
	sub	r2, r2, #1
	and	r2, r2, #63
.L137:
	cmp	r3, #7
	movls	r3, #7
	bls	.L138
	cmp	r3, #72
	movcs	r3, #72
	sub	r3, r3, #1
	and	r3, r3, #127
.L138:
	mov	r1, #0
	bfi	r1, r2, #16, #6
	bfi	r1, r3, #0, #7
	str	r1, [fp, #-52]
	b	.L139
.L195:
	ldr	r2, [r4, #2424]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r4, #2384]
	ldrhi	r2, [r4, #2384]
	movls	r2, r1, asl r2
	str	r2, [r3, #308]
	ldr	r2, [r4, #2424]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r4, #2388]
	ldrls	r1, [r4, #2388]
	movls	r2, r1, asl r2
	str	r2, [r3, #312]
	ldr	r2, [r4, #2424]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r4, #2392]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #316]
	ldr	r2, [r4, #2396]
	str	r2, [r3, #320]
	ldr	r2, [r4, #2400]
	str	r2, [r3, #324]
	ldr	r2, [r4, #2404]
	str	r2, [r3, #328]
	ldr	r2, [r4, #2408]
	str	r2, [r3, #332]
	ldr	r2, [r4, #2412]
	str	r2, [r3, #336]
	b	.L166
.L194:
	ldr	lr, [r8, #536]
	mov	r0, r2
	ldr	ip, [r4, #4060]
	movw	r1, #513
	cmp	lr, r2
	bfi	r0, ip, #8, #3
	movw	ip, #9729
	moveq	ip, r1
	bfi	r0, ip, #16, #16
	str	r0, [r3, #256]
	mov	r1, r2
	ldr	r0, [r8, #632]
	mov	ip, r2
	ldr	lr, [r8, #636]
	bfi	r1, r0, #0, #5
	mov	r0, r2
	bfi	r1, lr, #16, #16
	str	r1, [r3, #260]
	ldr	lr, [r4, #2420]
	ldr	r1, [r4, #2424]
	bfi	r2, lr, #0, #5
	bfi	r2, r1, #16, #16
	str	r2, [r3, #300]
	ldr	r1, [r8, #632]
	ldr	r2, [r8, #672]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	ip, r2, #0, #16
	str	ip, [r3, #264]
	ldr	r1, [r4, #2420]
	ldr	r2, [r4, #2416]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	r0, r2, #0, #16
	str	r0, [r3, #304]
	ldr	r2, [r8, #636]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r8, #640]
	ldrhi	r2, [r8, #640]
	movls	r2, r1, asl r2
	str	r2, [r3, #268]
	ldr	r2, [r8, #636]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r8, #644]
	ldrls	r1, [r8, #644]
	movls	r2, r1, asl r2
	str	r2, [r3, #272]
	ldr	r2, [r8, #636]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r8, #648]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #276]
	ldr	r2, [r8, #652]
	str	r2, [r3, #280]
	ldr	r2, [r8, #656]
	str	r2, [r3, #284]
	ldr	r2, [r8, #660]
	str	r2, [r3, #288]
	ldr	r2, [r8, #664]
	str	r2, [r3, #292]
	ldr	r2, [r8, #668]
	str	r2, [r3, #296]
	b	.L159
.L200:
	.align	2
.L199:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_CfgReg, .-DRV_VENC_HAL_V400R004C02_CfgReg
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_Init
	.type	DRV_VENC_HAL_V400R004C02_Init, %function
DRV_VENC_HAL_V400R004C02_Init:
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
	ldr	r3, .L224
	mov	r0, #0
	mov	r1, #63232
	movt	r0, 63688
	ldr	r4, .L224+4
	ldr	r3, [r3, #12]
	blx	r3
	cmp	r0, #0
	str	r0, [r4]
	beq	.L215
	ldr	r3, .L224
	movw	r0, #8272
	ldr	r3, [r3, #20]
	blx	r3
	ldr	r3, .L224
	movw	r2, #8272
	mov	r1, #0
	ldr	r3, [r3]
	str	r0, [r4, #4]
	blx	r3
	ldr	r5, [r4, #4]
	cmp	r5, #0
	beq	.L214
	ldr	r3, .L224
	mov	r2, #692
	mov	r1, #0
	mov	r0, r5
	mov	r7, #1280
	mov	r6, #720
	ldr	r3, [r3]
	blx	r3
	ldr	ip, [r4]
	mov	r3, #0
	add	r2, r5, #260
	add	r0, r5, #324
	mov	r1, r3
	mov	lr, #3
	str	ip, [r5]
	mov	r4, #10240
	mov	ip, #1
	str	r3, [r5, #4]
	str	r3, [r5, #20]
	str	r3, [r5, #24]
	str	r3, [r5, #32]
	str	r3, [r5, #36]
	str	r3, [r5, #48]
	str	r3, [r5, #60]
	str	r3, [r5, #64]
	str	r3, [r5, #136]
	str	r3, [r5, #168]
	str	r3, [r5, #172]
	str	r3, [r5, #176]
	str	r3, [r5, #180]
	str	r3, [r5, #184]
	str	r3, [r5, #188]
	str	r3, [r5, #192]
	str	lr, [r5, #8]
	str	lr, [r5, #44]
	str	r7, [r5, #12]
	str	r6, [r5, #16]
	str	r4, [r5, #28]
	str	ip, [r5, #40]
	str	ip, [r5, #56]
.L204:
	str	r1, [r2, #4]!
	cmp	r2, r0
	mov	r3, #0
	bne	.L204
	add	r10, r5, #7872
	add	r7, r5, #8064
	add	r4, r5, #7936
	add	ip, r5, #8000
	mov	r6, r10
	mov	r1, r7
	mov	lr, r4
	mov	r0, ip
	add	r10, r10, #12
	add	r7, r7, #44
	add	r6, r6, #44
	add	r4, r4, #12
	add	lr, lr, #44
	add	ip, ip, #12
	add	r0, r0, #44
	add	r1, r1, #12
	mov	r8, #7
	mov	r2, r3
	mov	r9, r3
	str	r3, [r5, #536]
	str	r3, [r5, #540]
	str	r3, [r5, #556]
	str	r3, [r5, #560]
	str	r3, [r5, #564]
	str	r3, [r5, #568]
	str	r3, [r5, #572]
	str	r3, [r5, #632]
	str	r3, [r5, #636]
	mov	r3, #28
	str	r5, [fp, #-48]
	str	r3, [r5, #544]
	mov	r3, #16
	str	r3, [r5, #548]
	mov	r3, #48
	str	r3, [r5, #552]
.L205:
	str	r9, [r10, #4]!
	mov	r5, #1
	str	r9, [r7, #4]!
	mov	r3, #0
	str	r5, [r6, #4]!
	mov	r5, #26
	str	r5, [r4, #4]!
	str	r8, [lr, #4]!
	str	r8, [ip, #4]!
	str	r2, [r0, #4]!
	str	r2, [r1, #4]!
	add	r2, r2, #5
	cmp	r2, #40
	bne	.L205
	ldr	r5, [fp, #-48]
	mov	ip, #1
	mov	lr, #256
	mov	r7, #4
	add	r1, r5, #7360
	add	r0, r5, #7424
	add	r2, r5, #4096
	add	r1, r1, #4
	add	r0, r0, #4
	mov	r6, #128
	mov	r4, #8
	str	lr, [r2, #2440]
	str	ip, [r2, #2432]
	mov	lr, #32
	str	ip, [r2, #2428]
	mov	r9, #3
	str	r3, [r2, #2476]
	mov	r8, #6
	str	r3, [r2, #2480]
	str	r3, [r2, #2484]
	str	r3, [r2, #2488]
	str	r3, [r2, #2504]
	str	r3, [r2, #2508]
	str	r3, [r2, #2512]
	str	r3, [r2, #2516]
	str	r3, [r2, #2532]
	str	r3, [r2, #2536]
	str	r3, [r2, #2540]
	str	r3, [r2, #2544]
	str	r3, [r2, #2560]
	str	r3, [r2, #2564]
	str	r3, [r2, #2568]
	str	r3, [r2, #2588]
	str	r3, [r2, #2592]
	str	r3, [r2, #2596]
	str	r3, [r2, #2616]
	str	r9, [r2, #2456]
	str	r8, [r2, #2880]
	str	r7, [r2, #2436]
	str	r7, [r2, #2448]
	str	r6, [r2, #2444]
	str	r6, [r2, #2452]
	str	r4, [r2, #2460]
	str	r4, [r2, #2468]
	str	lr, [r2, #2464]
	str	lr, [r2, #2472]
	str	lr, [r2, #2876]
	str	r3, [r2, #2620]
	str	r3, [r2, #2624]
	str	r3, [r2, #2644]
	str	r3, [r2, #2648]
	str	r3, [r2, #2652]
	str	r3, [r2, #2672]
	str	r3, [r2, #2676]
	str	r3, [r2, #2680]
	str	r3, [r2, #2684]
	str	r3, [r2, #2704]
	str	r3, [r2, #2708]
	str	r3, [r2, #2712]
	str	r3, [r2, #2716]
	str	ip, [r2, #3084]
	str	r3, [r2, #3088]
	str	r3, [r2, #3092]
	str	r3, [r2, #3096]
	str	r3, [r2, #3100]
	str	r3, [r2, #3104]
	str	r3, [r2, #3108]
	str	ip, [r2, #3112]
	str	r3, [r2, #3116]
	str	r3, [r2, #3120]
	str	r3, [r2, #3124]
	str	r3, [r2, #3128]
	str	r3, [r2, #3132]
	str	r3, [r2, #3136]
	str	r3, [r2, #3140]
	str	r3, [r2, #3144]
	str	r3, [r2, #3148]
	str	r3, [r2, #3152]
	str	r3, [r2, #3156]
	str	r3, [r2, #3160]
	str	ip, [r2, #3164]
	str	r3, [r2, #3168]
	str	r3, [r2, #3172]
	str	r3, [r2, #3176]
	str	r3, [r2, #3180]
	str	r3, [r2, #3184]
	str	r3, [r2, #3188]
	str	ip, [r2, #2736]
	str	r3, [r2, #2740]
	str	r3, [r2, #2744]
	str	r3, [r2, #2748]
	str	r3, [r2, #2752]
	str	r3, [r2, #2756]
	str	r3, [r2, #2760]
	str	r3, [r2, #3192]
	str	r3, [r2, #3196]
	str	r3, [r2, #3200]
	str	r3, [r2, #3204]
	str	r3, [r2, #3208]
	str	r3, [r2, #3212]
	str	r3, [r2, #3216]
	str	r3, [r2, #3220]
	str	r3, [r2, #3224]
	str	r3, [r2, #3228]
	str	r3, [r2, #3232]
	str	r3, [r2, #3236]
	str	r3, [r2, #3240]
	str	r3, [r2, #3244]
	str	r3, [r2, #3248]
	str	r3, [r2, #3252]
	str	r3, [r2, #3256]
	str	r3, [r2, #3260]
	str	r3, [r2, #3264]
	str	r3, [r2, #3268]
.L206:
	str	ip, [r1, #4]!
	cmp	r1, r0
	mov	lr, #1
	bne	.L206
	mov	r0, #0
	mov	r6, #4
	mov	r7, #8
	mov	r4, #10
	mov	r3, #12
	mov	r1, #48
	mov	r8, #51
	str	lr, [r2, #3436]
	str	lr, [r2, #3440]
	mov	r10, #35
	str	lr, [r2, #3444]
	mov	r9, #44
	str	lr, [r2, #3456]
	str	lr, [r2, #3412]
	str	r7, [r2, #3336]
	str	r7, [r2, #3388]
	str	r1, [r2, #3364]
	str	r1, [r2, #3360]
	str	r1, [r2, #3368]
	add	r1, r5, #856
	str	r4, [r2, #3556]
	str	r4, [r2, #3544]
	str	r1, [fp, #-48]
	mov	r1, #2
	str	r4, [r2, #3552]
	str	r4, [r2, #3540]
	str	r0, [r2, #3340]
	str	r0, [r2, #3348]
	str	r0, [r2, #3344]
	str	r0, [r2, #3356]
	str	r0, [r2, #3460]
	str	r0, [r2, #3504]
	str	r0, [r2, #3508]
	str	r0, [r2, #3512]
	str	r0, [r2, #3516]
	str	r0, [r2, #3408]
	str	r10, [r2, #3372]
	mov	r10, #20
	str	r8, [r2, #3376]
	str	r8, [r2, #3392]
	mov	r8, #5
	str	r6, [r2, #3384]
	str	r6, [r2, #3484]
	str	r6, [r2, #3416]
	str	r3, [r2, #3396]
	str	r3, [r2, #3400]
	str	r8, [r2, #3404]
	mov	r8, #6
	str	r9, [r2, #3380]
	mov	r9, #150
	str	r4, [r2, #3560]
	str	r0, [r2, #3572]
	str	r3, [r2, #3588]
	str	r7, [r2, #3592]
	str	r6, [r2, #3596]
	str	r3, [r2, #3600]
	mov	r3, #2
	str	r7, [r2, #3604]
	str	r6, [r2, #3608]
	str	r6, [r2, #3616]
	str	r0, [r2, #3664]
	str	r0, [r2, #3672]
	str	r0, [r2, #3680]
	str	r7, [r2, #3684]
	str	r7, [r2, #3688]
	str	r7, [r2, #3692]
	str	r7, [r2, #3696]
	str	r0, [r2, #3716]
	str	r3, [r2, #3352]
	str	r3, [r2, #3612]
	str	r3, [r2, #3676]
	mov	r3, #50
	str	r10, [r2, #3576]
	str	r3, [r2, #3580]
	mov	r3, #131
	str	r9, [r2, #3584]
	mov	r9, #160
	str	r8, [r2, #3620]
	mov	r8, #100
	str	r3, [r2, #3624]
	mov	r3, #127
	str	r9, [r2, #3628]
	mov	r9, #3
	str	r8, [r2, #3632]
	mov	r8, #16
	str	r3, [r2, #3636]
	mov	r3, #24
	str	r9, [r2, #3660]
	mov	r9, #5
	str	r8, [r2, #3700]
	str	r8, [r2, #3704]
	str	r3, [r2, #3708]
	str	r3, [r2, #3712]
	add	r3, r5, #1016
	str	r4, [r2, #3640]
	mov	r4, #60
	str	r4, [r2, #3756]
	movw	r4, #767
	str	r4, [r2, #3652]
	mov	r4, #15
	str	r4, [r2, #4068]
	str	r4, [r2, #4072]
	add	r4, r2, #4096
	str	r9, [r2, #3772]
	mov	r9, #11520
	str	r10, [r2, #3644]
	mov	r10, #2
	str	r10, [r2, #4060]
	mov	r10, #2304
	str	r0, [r2, #3740]
	movt	r9, 305
	str	r0, [r2, #3744]
	movt	r10, 61
	str	r0, [r2, #3748]
	str	r0, [r2, #3752]
	str	r0, [r2, #3764]
	str	r0, [r2, #3768]
	str	r0, [r2, #3776]
	str	r0, [r2, #3780]
	str	r0, [r2, #3760]
	str	r0, [r2, #3784]
	str	r0, [r2, #3788]
	str	r0, [r2, #4076]
	str	lr, [r2, #3648]
	str	lr, [r2, #4048]
	str	lr, [r2, #4052]
	str	lr, [r2, #4056]
	str	lr, [r2, #4064]
	str	lr, [r2, #4080]
	ldr	ip, .L224+8
	str	r0, [r4, #4]
	str	r0, [r4]
	str	r0, [r4, #8]
	str	r0, [r2, #4088]
	str	r0, [r2, #4084]
	str	r0, [r2, #4092]
	str	r0, [r4, #12]
	str	r0, [r4, #16]
	str	r0, [r4, #20]
	str	r1, [r4, #64]
	mov	r1, #3
	str	r0, [r4, #24]
	str	r0, [r4, #28]
	str	r0, [r4, #32]
	str	r0, [r4, #36]
	str	r0, [r4, #40]
	str	r0, [r4, #44]
	str	r0, [r4, #48]
	str	r0, [r4, #52]
	str	r0, [r4, #56]
	str	r0, [r4, #60]
	str	lr, [r4, #68]
	str	r9, [r4, #72]
	mov	r9, #64
	str	r10, [r4, #76]
	mov	r4, #7
	str	r1, [r5, #700]
	mov	r10, #11
	str	r6, [r5, #708]
	str	r8, [r5, #712]
	str	r6, [r5, #716]
	str	r8, [r5, #720]
	str	r6, [r5, #756]
	str	r8, [r5, #752]
	mov	r8, #14
	str	r0, [r5, #736]
	str	r0, [r5, #740]
	str	r0, [r5, #744]
	str	r0, [r5, #748]
	str	r0, [r5, #764]
	str	r0, [r5, #768]
	str	r0, [r5, #772]
	str	r6, [r5, #792]
	str	lr, [r5, #696]
	str	lr, [r5, #692]
	str	lr, [r5, #760]
	str	r9, [r5, #704]
	mov	r9, #25
	str	r1, [r5, #1184]
	str	r1, [r5, #1196]
	mov	r1, #9
	str	r1, [r5, #828]
	ldr	r1, [fp, #-48]
	str	r0, [r5, #796]
	str	r6, [r5, #776]
	mov	r6, #18
	str	r0, [r5, #800]
	str	r0, [r5, #804]
	str	r0, [r5, #808]
	str	r0, [r5, #812]
	mov	r0, #255
	str	r7, [r5, #1200]
	mov	r7, #96
	str	lr, [r5, #784]
	str	lr, [r5, #780]
	str	lr, [r5, #1180]
	movw	lr, #378
	str	r4, [r5, #816]
	str	r4, [r5, #820]
	str	r4, [r5, #824]
	mov	r4, #128
	str	r10, [r5, #832]
	str	r8, [r5, #836]
	str	r6, [r5, #840]
	str	r9, [r5, #844]
	str	r9, [r5, #1188]
	str	r0, [r5, #848]
	str	r0, [r5, #852]
	str	r0, [r5, #856]
	str	r7, [r5, #1208]
	str	lr, [r5, #1204]
	str	r4, [r5, #1192]
.L207:
	ldr	r0, [ip, #4]!
	str	r0, [r1, #4]!
	cmp	r1, r3
	bne	.L207
	add	ip, r5, #1168
	ldr	r1, .L224+12
	add	ip, ip, #8
.L208:
	ldr	r0, [r1, #4]!
	str	r0, [r3, #4]!
	cmp	r3, ip
	bne	.L208
	add	r4, r5, #1200
	add	r3, r5, #6400
	mov	r6, #3
	add	r4, r4, #12
	add	r3, r3, #12
	str	r4, [fp, #-48]
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r4, [fp, #-56]
	str	r3, [r2, #2328]
	str	r3, [r2, #2324]
	mov	r3, #7
	str	r3, [r2, #2320]
.L210:
	ldr	r4, [fp, #-48]
	movw	r2, #2600
	ldr	r3, .L224
	mov	r1, #0
	mov	r9, #0
	mov	r0, r4
	ldr	r3, [r3]
	blx	r3
	mov	r0, r4
	mov	r3, r4
	mov	r2, r4
	mov	r1, r9
	mov	lr, #4
	mov	r4, #64
	mov	ip, #1
.L209:
	add	r9, r9, #1
	str	r6, [r3, #8]
	cmp	r9, #5
	mov	r10, #32
	mov	r5, #96
	mov	r7, #384
	str	r5, [r2, #2468]
	mov	r8, #2
	str	lr, [r0, #420]
	mov	r5, #20
	str	r1, [r3, #44]
	add	r0, r0, #404
	str	r1, [r3, #72]
	add	r3, r3, #84
	str	r4, [r3, #-72]
	str	ip, [r3, #-80]
	str	r5, [r2, #2448]
	mov	r5, #8
	str	r6, [r2, #2444]
	str	r5, [r2, #2460]
	mov	r5, #16
	str	r4, [r2, #2452]
	str	lr, [r2, #2456]
	str	r1, [r3, #-28]
	str	r1, [r3, #-8]
	str	lr, [r3, #-60]
	str	r10, [r3, #-56]
	str	ip, [r0, #24]
	str	r1, [r0, #28]
	str	r7, [r2, #2464]
	str	r10, [r3, #-24]
	str	r1, [r3, #-52]
	str	r1, [r3, #-4]
	str	lr, [r3, #-20]
	str	ip, [r3, #-84]
	str	r8, [r2, #2440]
	add	r2, r2, r10
	str	ip, [r3, #-16]
	str	lr, [r3, #-68]
	str	r5, [r3, #-64]
	str	ip, [r0, #20]
	bne	.L209
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #2592
	add	r3, r3, #8
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L210
	mov	r3, #1
	ldr	r4, [fp, #-56]
	mov	ip, r3
	str	r3, [fp, #-48]
	mov	r3, #0
	str	r9, [fp, #-52]
	mov	r2, r3
	mov	lr, r10
	mov	r3, r8
	mov	r9, r2
	mov	r5, #128
	mov	r1, #64
.L211:
	mov	r7, #6
	str	r7, [r4, #824]
	ldr	r7, [fp, #-52]
	cmp	r9, #0
	mov	r10, #15
	mov	r6, #4
	str	ip, [r4, #8]
	mov	r0, #3
	str	r5, [r4, #12]
	mov	r8, #34
	str	r5, [r4, #28]
	str	r5, [r4, #60]
	str	r2, [r4, #424]
	str	r2, [r4]
	str	r2, [r4, #428]
	str	r2, [r4, #4]
	str	r2, [r4, #832]
	str	r1, [r4, #96]
	str	r1, [r4, #112]
	str	r1, [r4, #144]
	str	r1, [r4, #180]
	str	r1, [r4, #196]
	str	r1, [r4, #228]
	str	r7, [r4, #1228]
	str	ip, [r4, #380]
	str	lr, [r4, #408]
	str	r2, [r4, #388]
	str	r2, [r4, #384]
	str	r3, [r4, #2572]
	str	r1, [r4, #2580]
	str	r3, [r4, #2584]
	str	r10, [r4, #2576]
	str	r6, [r4, #2588]
	beq	.L223
	ldr	r7, [fp, #-48]
	str	r0, [r4, #392]
	cmp	r7, #1
	str	r0, [r4, #360]
	mov	r7, #256
	str	r0, [r4, #368]
	str	r0, [r4, #376]
	str	r0, [r4, #372]
	str	r0, [r4, #400]
	mov	r0, #16
	str	r2, [r4, #412]
	str	lr, [r4, #364]
	str	ip, [r4, #2048]
	str	r7, [r4, #2592]
	str	r8, [r4, #416]
	str	lr, [r4, #396]
	str	ip, [r4, #336]
	str	r3, [r4, #2568]
	str	ip, [r4, #404]
	str	r6, [r4, #352]
	str	r0, [r4, #356]
	bhi	.L214
.L213:
	ldr	r0, [fp, #-48]
	add	r4, r4, #2592
	add	r9, r9, #1
	add	r4, r4, #8
	add	r0, r0, #1
	str	r0, [fp, #-48]
	b	.L211
.L214:
	mov	r0, #0
.L202:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L215:
	mvn	r0, #0
	b	.L202
.L223:
	mov	r7, #256
	str	r6, [r4, #392]
	str	r7, [r4, #2592]
	mov	r7, #16
	str	r9, [r4, #412]
	str	lr, [r4, #364]
	str	ip, [r4, #2048]
	str	r6, [r4, #368]
	str	r0, [r4, #360]
	str	r8, [r4, #416]
	str	r0, [r4, #376]
	str	r0, [r4, #372]
	str	r0, [r4, #400]
	str	lr, [r4, #396]
	str	ip, [r4, #336]
	str	r3, [r4, #2568]
	str	ip, [r4, #404]
	str	r6, [r4, #352]
	str	r7, [r4, #356]
	b	.L213
.L225:
	.align	2
.L224:
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR0-4
	.word	.LANCHOR0+156
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_Init, .-DRV_VENC_HAL_V400R004C02_Init
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_Deinit
	.type	DRV_VENC_HAL_V400R004C02_Deinit, %function
DRV_VENC_HAL_V400R004C02_Deinit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L227
	ldr	r4, .L227+4
	ldr	r3, [r5, #16]
	ldr	r0, [r4]
	blx	r3
	ldr	r3, [r5, #24]
	ldr	r0, [r4, #4]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L228:
	.align	2
.L227:
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_Deinit, .-DRV_VENC_HAL_V400R004C02_Deinit
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
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
.LANCHOR1 = . + 0
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
