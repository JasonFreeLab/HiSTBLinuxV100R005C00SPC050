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
	.file	"aoe_engine.c"
	.text
	.align	2
	.type	ENGINECheckAipData, %function
ENGINECheckAipData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #32]
	ldr	r2, [r0, #36]
	ldr	r0, [r0, #40]
	cmp	r3, #0
	cmpne	r2, #0
	beq	.L2
	cmp	r3, #0
	moveq	lr, r3
	beq	.L3
	mov	r1, #0
	mov	r4, #1
	mov	lr, r1
.L5:
	mov	ip, r4, asl r1
	tst	ip, r3
	beq	.L6
	ands	ip, ip, r0
	mov	lr, #1
	beq	.L23
.L6:
	add	r1, r1, #1
	cmp	r1, #8
	bne	.L5
.L3:
	cmp	r2, #0
	movne	r3, #0
	movne	ip, #1
	beq	.L9
.L8:
	mov	r1, ip, asl r3
	tst	r1, r2
	beq	.L11
	tst	r1, r0
	beq	.L24
	orr	lr, lr, #2
.L11:
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L8
.L9:
	and	r0, lr, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L2:
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L23:
	mov	lr, ip
	b	.L3
.L24:
	bic	lr, lr, #2
	b	.L9
	UNWIND(.fnend)
	.size	ENGINECheckAipData, .-ENGINECheckAipData
	.align	2
	.type	ENGINECheckAopSpace, %function
ENGINECheckAopSpace:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #64]
	ldr	lr, [r0, #48]
	cmp	r3, #0
	ldr	r0, [r0, #52]
	beq	.L40
	cmp	lr, #0
	beq	.L27
	mov	r2, #0
	mov	r4, #1
	mov	ip, r2
.L29:
	mov	r1, r4, asl r2
	tst	r1, lr
	beq	.L31
	ands	r1, r1, r3
	mov	ip, #1
	beq	.L46
.L31:
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L29
.L30:
	cmp	r0, #0
	beq	.L39
.L37:
	mov	r2, #0
	mov	r4, #1
.L33:
	mov	r1, r4, asl r2
	tst	r1, r0
	beq	.L36
	tst	r1, r3
	beq	.L47
	orr	ip, ip, #2
.L36:
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L33
.L34:
	cmp	lr, #0
	bne	.L39
	and	r0, ip, #2
	ldmfd	sp, {r4, fp, sp, pc}
.L27:
	cmp	r0, #0
	movne	ip, lr
	ldmeqfd	sp, {r4, fp, sp, pc}
	b	.L37
.L40:
	mov	r0, r3
	ldmfd	sp, {r4, fp, sp, pc}
.L39:
	and	r0, ip, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L46:
	mov	ip, r1
	b	.L30
.L47:
	bic	ip, ip, #2
	b	.L34
	UNWIND(.fnend)
	.size	ENGINECheckAopSpace, .-ENGINECheckAopSpace
	.align	2
	.type	ENGINEDestroyChn, %function
ENGINEDestroyChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L50
	ldr	r1, [r4, #76]
	cmp	r1, #0
	beq	.L51
	mov	r0, #26
	bl	HI_ADSP_FREE
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L50
.L51:
	ldr	r1, [r4, #136]
	cmp	r1, #0
	beq	.L50
	mov	r0, #26
	bl	HI_ADSP_FREE
	mov	r3, #0
	str	r3, [r4, #136]
.L50:
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
	UNWIND(.fnend)
	.size	ENGINEDestroyChn, .-ENGINEDestroyChn
	.align	2
	.type	ENGINEOutRawFrame, %function
ENGINEOutRawFrame:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	mov	r6, r2
	bl	AIP_GetRingIn
	mov	r4, r0
	mov	r0, r5
	bl	AOP_GetRingOut
	cmp	r0, #0
	cmpne	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r0
	mov	r2, r6
	mov	r0, r4
	mov	r3, #3
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RBUF_CopyData
	UNWIND(.fnend)
	.size	ENGINEOutRawFrame, .-ENGINEOutRawFrame
	.global	__aeabi_uidiv
	.align	2
	.type	ENGINEMixData, %function
ENGINEMixData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	mov	r5, r1
	mov	r4, r0
	sub	r1, fp, #72
	mov	r0, r5
	mov	ip, #0
	mov	r6, r2
	ldr	r7, [r4, #4]
	ldr	r8, [r4]
	str	ip, [fp, #-72]
	str	ip, [fp, #-68]
	str	ip, [fp, #-64]
	str	ip, [fp, #-60]
	str	ip, [fp, #-56]
	str	ip, [fp, #-52]
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	str	ip, [fp, #-40]
	bl	AIP_QueryFiFoInfo
	ldr	r0, [r4, #112]
	ldr	r3, [fp, #-52]
	ldr	r9, [fp, #-56]
	cmp	r3, r0
	bcc	.L60
	cmp	r9, r0
	ldr	r1, [r4, #116]
	bcc	.L64
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-68]
	ldr	r1, [fp, #-72]
	mov	r3, r8
	add	r1, r1, r2
	mul	r2, r7, r0
	mov	r0, r6
	bl	UTIL_MixerPro
.L63:
	ldr	r1, [r4, #112]
	mov	r0, r5
	bl	AIP_ReadDataComplete
.L60:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L64:
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-68]
	ldr	r1, [fp, #-72]
	mov	r3, r8
	add	r1, r1, r2
	mul	r2, r7, r0
	mov	r0, r6
	bl	UTIL_MixerPro
	ldr	r0, [r4, #112]
	ldr	r1, [r4, #116]
	rsb	r0, r9, r0
	bl	__aeabi_uidiv
	mov	r3, r8
	ldr	r1, [fp, #-72]
	mul	r2, r7, r0
	add	r0, r6, r9
	bl	UTIL_MixerPro
	b	.L63
	UNWIND(.fnend)
	.size	ENGINEMixData, .-ENGINEMixData
	.align	2
	.type	ENGINECheckRbfInData, %function
ENGINECheckRbfInData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r1, #12]
	ldr	r4, [r1, #112]
	cmp	r3, #0
	beq	.L66
	bl	AIP_QueryBusy
	cmp	r4, r0
	bls	.L69
.L68:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L66:
	ldr	r4, [r1, #140]
	bl	AIP_QueryFiFoBusy
	cmp	r4, r0
	bhi	.L68
.L69:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	ENGINECheckRbfInData, .-ENGINECheckRbfInData
	.align	2
	.global	ENGINECreateAVC
	.type	ENGINECreateAVC, %function
ENGINECreateAVC:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #48)
	sub	sp, sp, #48
	mov	r4, r0
	mov	r5, r1
	sub	r0, fp, #76
	sub	r1, fp, #64
	movw	r2, #48000
	mov	r3, #2
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	bl	iMedia_AVC_GetSize
	ldr	r1, [fp, #-76]
	mov	r0, #26
	str	r1, [r4, #80]
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #76]
	beq	.L75
	ldr	r6, .L76
	mov	r1, #0
	ldr	r2, [fp, #-76]
	ldr	r3, [r6, #20]
	blx	r3
	ldr	r7, [r5, #72]
	ldr	lr, [r5, #72]
	mov	ip, #0
	ldr	r1, [r5, #76]
	ubfx	r7, r7, #0, #13
	ldr	r0, [r5, #76]
	ubfx	lr, lr, #13, #13
	ubfx	r1, r1, #6, #6
	ldr	r2, [r5, #76]
	rsb	r3, r1, #0
	strh	lr, [fp, #-44]
	and	r2, r2, #63
	strh	ip, [fp, #-48]
	uxth	r3, r3
	strh	r3, [fp, #-40]
	strh	ip, [fp, #-30]
	rsb	r2, r2, #0
	sxth	r3, r3
	ubfx	r0, r0, #12, #4
	cmn	r3, #31
	strh	r2, [fp, #-36]
	strh	r0, [fp, #-38]
	mov	r2, #20
	movwge	r3, #65528
	mvnlt	r3, #39
	movtge	r3, 65535
	strh	r7, [fp, #-46]
	rsbge	r3, r1, r3
	add	r0, r4, #88
	sub	r1, fp, #48
	strh	r3, [fp, #-42]
	ldr	r3, [r6, #24]
	blx	r3
	ldr	r3, [r6, #32]
	blx	r3
	sub	r3, fp, #48
	ldr	r2, [r4, #80]
	add	r0, r4, #72
	ldr	r1, [r4, #76]
	bl	iMedia_AVC_Init
	ldr	r3, [r6, #36]
	mov	r5, r0
	blx	r3
	cmp	r5, #0
	bne	.L74
	mov	r0, r5
	str	r5, [r4, #84]
.L71:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L75:
	mvn	r0, #0
	b	.L71
.L74:
	mov	r0, #26
	ldr	r1, [r4, #76]
	bl	HI_ADSP_FREE
	mvn	r0, #0
	b	.L71
.L77:
	.align	2
.L76:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINECreateAVC, .-ENGINECreateAVC
	.align	2
	.type	ENGINECreateChn, %function
ENGINECreateChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r3, .L102
	ldr	r6, .L102+4
	mov	r2, #28
	mov	r1, #0
	mov	r7, r0
	ldr	r5, [r3, r0, asl #2]
	sub	r0, fp, #72
	ldr	r3, [r6, #20]
	blx	r3
	sub	r0, fp, #72
	ldr	r1, [r5]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L79
	ldr	r1, [r5]
	sub	r0, fp, #68
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L79
	ldr	r1, [r5]
	sub	r0, fp, #64
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L79
	ldr	r1, [r5]
	sub	r0, fp, #60
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	subs	r8, r0, #0
	bne	.L79
	mov	r1, #192
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L79
	mov	r1, r8
	ldr	r3, [r6, #20]
	mov	r2, #192
	blx	r3
	ldr	r3, [r6, #24]
	mov	r2, #28
	sub	r1, fp, #72
	mov	r0, r4
	blx	r3
	ldr	r1, [r4]
	ldr	r0, [r4, #4]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r4, #8]
	movw	r2, #19923
	movw	r1, #48000
	cmp	r3, r1
	movt	r2, 4194
	add	r3, r3, r3, lsl #2
	umull	r2, r3, r3, r2
	mov	r3, r3, lsr #6
	beq	.L100
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
.L84:
	mul	r3, r0, r3
	ldr	r1, [r4]
	ldr	r0, [r4, #4]
	str	r3, [r4, #112]
	bl	UTIL_CalcFrameSize
	ldr	r9, [r4, #112]
	mov	r1, r0
	str	r0, [r4, #116]
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r8, [r4, #12]
	cmp	r8, #0
	mov	r3, r0
	str	r0, [r4, #16]
	beq	.L101
.L85:
	mov	r0, r4
	mov	r3, #1
	str	r7, [r4, #108]
	str	r3, [r4, #120]
.L99:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L101:
	ldr	r10, [r4, #4]
	mov	r2, #28
	ldr	lr, [r4]
	add	r1, r4, #136
	ldr	ip, [r4, #8]
	add	r0, r4, #164
	str	r9, [r4, #140]
	str	r3, [r4, #144]
	str	r10, [r4, #152]
	ldr	r3, [r6, #24]
	str	lr, [r4, #148]
	str	ip, [r4, #156]
	str	r8, [r4, #136]
	str	r8, [r4, #160]
	blx	r3
	ldr	r3, [r4, #168]
	ldr	r6, [r4, #140]
	mov	r0, #26
	ldr	r9, .L102+4
	add	r6, r3, r6
	mov	r1, r6
	bl	HI_ADSP_MALLOC
	subs	r10, r0, #0
	beq	.L86
	ldr	r3, [r9, #20]
	mov	r2, r6
	mov	r1, r8
	blx	r3
	ldr	r2, [r4, #12]
	ldr	r3, [r4, #140]
	cmp	r2, #0
	str	r10, [r4, #136]
	add	r10, r10, r3
	str	r10, [r4, #164]
	bne	.L85
	mov	r1, r5
	mov	r0, r4
	bl	ENGINECreateAVC
	cmp	r0, #0
	beq	.L85
.L86:
	mov	r0, r4
	bl	ENGINEDestroyChn
	mov	r0, #0
	b	.L99
.L79:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L100:
	tst	r3, #255
	bicne	r3, r3, #255
	addne	r3, r3, #256
	b	.L84
.L103:
	.align	2
.L102:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINECreateChn, .-ENGINECreateChn
	.align	2
	.global	ENGINE_Process
	.type	ENGINE_Process, %function
ENGINE_Process:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	ldr	r10, .L344
	mov	r7, #0
	add	r9, r10, #24
	b	.L212
.L121:
	add	r7, r7, #1
	add	r9, r9, #4
	cmp	r7, #6
	beq	.L322
.L212:
	ldr	r3, [r10], #4
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #2, #1
	cmp	r2, #0
	bne	.L316
	ldr	r1, [r3, #4]
	ands	r1, r1, #3
	beq	.L107
	cmp	r1, #1
	beq	.L108
	ldr	r2, [r3, #4]
	mov	r1, #4
	bfi	r2, r1, #3, #4
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, r1
	str	r2, [r3, #4]
.L316:
	ldr	r4, [r9]
	cmp	r4, #0
	beq	.L121
.L120:
	ldr	r6, [r4, #120]
.L213:
	cmp	r6, #1
	bne	.L121
	ldr	r3, [r4]
	mov	ip, #0
	ldr	r8, [r10, #-4]
	mov	r5, ip
	str	r3, [fp, #-148]
	ldr	r3, [r4, #4]
	str	r3, [fp, #-156]
	ldr	r2, [r8, #12]
	ldr	r3, [r4, #16]
	str	r7, [fp, #-136]
	mov	r7, ip
	uxth	r2, r2
	str	r4, [fp, #-144]
	str	ip, [fp, #-120]
	str	r3, [fp, #-152]
	mov	r4, r2
	str	ip, [fp, #-132]
	str	ip, [fp, #-124]
	str	ip, [fp, #-128]
	str	r8, [fp, #-140]
	b	.L128
.L123:
	add	r7, r7, #1
	cmp	r7, #8
	beq	.L323
.L128:
	mov	r8, r6, asl r7
	tst	r8, r4
	beq	.L123
	sub	r1, fp, #76
	mov	r0, r7
	bl	AOP_GetChnStatus
	ldr	r1, [fp, #-76]
	cmp	r1, #1
	bne	.L123
	ldr	r1, [fp, #-72]
	cmp	r1, #1
	ldr	r1, [fp, #-68]
	ldreq	r3, [fp, #-128]
	ldrne	r3, [fp, #-124]
	orreq	r3, r3, r8
	orrne	r3, r3, r8
	streq	r3, [fp, #-128]
	strne	r3, [fp, #-124]
	ldr	r3, [fp, #-148]
	cmp	r3, r1
	beq	.L324
.L126:
	ldr	r3, [fp, #-120]
	orr	r3, r3, r8
	str	r3, [fp, #-120]
.L127:
	ldr	r1, [fp, #-60]
	mov	r0, r7
	ldr	r3, [fp, #-152]
	add	r7, r7, #1
	mul	r1, r1, r3
	bl	AOP_QueryRbfFree
	cmp	r0, #0
	orrne	r5, r5, r8
	cmp	r7, #8
	bne	.L128
.L323:
	mov	r2, r4
	ldr	r4, [fp, #-144]
	ldr	r8, [fp, #-140]
	mov	r3, #0
	ldr	r7, [fp, #-136]
	mov	ip, r5
	str	r2, [r4, #44]
	mov	r5, r3
	ldr	r2, [fp, #-128]
	mov	r6, #1
	str	ip, [r4, #64]
	str	r3, [r4, #32]
	str	r2, [r4, #48]
	ldr	r2, [fp, #-124]
	str	r3, [r4, #36]
	str	r3, [r4, #40]
	str	r2, [r4, #52]
	ldr	r2, [fp, #-132]
	str	r2, [r4, #56]
	ldr	r2, [fp, #-120]
	str	r2, [r4, #60]
	ldr	r3, [r8, #8]
	str	r7, [fp, #-120]
	mov	r7, r4
	uxth	r3, r3
	str	r3, [r4, #28]
	b	.L139
.L129:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L138
.L326:
	ldr	r3, [r7, #28]
.L139:
	mov	r4, r6, asl r5
	tst	r3, r4
	beq	.L129
	sub	r1, fp, #76
	mov	r0, r5
	bl	AIP_GetChnStatus
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	beq	.L325
	ldr	r3, [r7, #12]
	cmp	r3, #0
	bne	.L129
	mov	r1, r7
	mov	r0, r5
	bl	ENGINECheckRbfInData
	cmp	r0, #0
	beq	.L129
	ldr	r3, [r7, #40]
	add	r5, r5, #1
	orr	r3, r3, r4
	str	r3, [r7, #40]
	ldr	r3, [fp, #-72]
	cmp	r3, #1
	ldrne	r3, [r7, #36]
	ldreq	r3, [r7, #32]
	orrne	r3, r3, r4
	orreq	r4, r3, r4
	strne	r3, [r7, #36]
	streq	r4, [r7, #32]
	cmp	r5, #8
	bne	.L326
.L138:
	ldr	r3, [r8, #4]
	mov	r4, r7
	ldr	r7, [fp, #-120]
	tst	r3, #4096
	beq	.L145
	ldr	r3, [r8, #4]
	bfc	r3, #12, #1
	str	r3, [r8, #4]
	ldr	r1, [r8, #72]
	ubfx	r1, r1, #0, #13
	strh	r1, [fp, #-74]
	ldr	ip, [r8, #72]
	ubfx	ip, ip, #13, #13
	strh	ip, [fp, #-72]
	ldr	r0, [r8, #76]
	ubfx	r0, r0, #6, #6
	rsb	r2, r0, #0
	uxth	r2, r2
	strh	r2, [fp, #-68]
	ldr	lr, [r8, #76]
	sxth	r2, r2
	ubfx	lr, lr, #12, #4
	strh	lr, [fp, #-66]
	ldr	r3, [r8, #76]
	cmn	r2, #31
	and	r3, r3, #63
	movwge	r5, #65528
	rsb	r3, r3, #0
	movtge	r5, 65535
	mvnlt	r0, #39
	rsbge	r5, r0, r5
	strlth	r0, [fp, #-70]
	uxth	r3, r3
	strgeh	r5, [fp, #-70]
	strh	r3, [fp, #-64]
	ldrsh	r5, [r4, #90]
	ldr	r0, [r8, #4]
	cmp	r5, r1
	ubfx	r1, r0, #11, #1
	str	r1, [r4, #84]
	beq	.L327
.L143:
	ldr	r2, .L344+4
	sub	r1, fp, #44
	add	r5, r4, #88
	mov	r3, #0
	strh	r3, [r1, #-32]!
	ldr	ip, [r2, #24]
	mov	r0, r5
	mov	r2, #20
	strh	r3, [fp, #-58]
	blx	ip
	ldr	r3, .L344+4
	ldr	r3, [r3, #32]
	blx	r3
	mov	r3, r5
	ldr	r2, [r4, #80]
	add	r0, r4, #72
	ldr	r1, [r4, #76]
	bl	iMedia_AVC_Init
	ldr	r3, .L344+4
	ldr	r3, [r3, #36]
	blx	r3
.L145:
	ldr	r4, [r9]
	ldr	r5, [r4, #12]
	cmp	r5, #0
	bne	.L328
	ldr	r3, [r4, #132]
	sub	r2, r3, #1
	cmp	r2, #1
	bls	.L168
	mov	r6, r5
	str	r5, [fp, #-120]
	mov	r8, r5
	mov	ip, #1
	str	r7, [fp, #-128]
	b	.L171
.L169:
	add	r8, r8, #1
	cmp	r8, #8
	beq	.L329
.L171:
	ldr	r1, [r4, #28]
	mov	r7, ip, asl r8
	tst	r7, r1
	beq	.L169
	sub	r1, fp, #76
	mov	r0, r8
	str	ip, [fp, #-124]
	bl	AIP_GetChnStatus
	ldr	r1, [fp, #-76]
	ldr	ip, [fp, #-124]
	cmp	r1, #0
	orrne	r5, r5, r7
	bne	.L169
	ldr	r1, [fp, #-68]
	add	r8, r8, #1
	ldr	r3, [fp, #-120]
	cmp	r1, #1
	orreq	r6, r6, r7
	cmp	r8, #8
	orr	r3, r3, r7
	str	r3, [fp, #-120]
	bne	.L171
.L329:
	ldr	r2, [r4, #128]
	mov	r3, #0
	ldr	r7, [fp, #-128]
	mov	r8, #1
	str	r4, [fp, #-124]
	str	r2, [fp, #-128]
	ldr	r2, [fp, #-120]
	str	r2, [r4, #128]
	mov	r4, r3
	mov	r3, r6
	mov	r6, r5
	mov	r5, r3
	b	.L173
.L172:
	add	r4, r4, #1
	cmp	r4, #8
	beq	.L330
.L173:
	ands	r3, r5, r8, asl r4
	beq	.L172
	mov	r0, r4
	add	r4, r4, #1
	bl	AIP_FlushCutoffFlag
	cmp	r4, #8
	bne	.L173
.L330:
	ldr	r4, [fp, #-124]
	mov	r3, r5
	mov	r5, r6
	cmp	r5, #0
	mov	r6, r3
	ldrne	r3, [r4, #132]
	bne	.L168
	ldr	r3, [fp, #-120]
	ldr	r2, [fp, #-128]
	rsb	r3, r2, r3
	cmp	r3, r6
	strhi	r5, [r4, #124]
	movhi	r3, #2
	strhi	r3, [r4, #132]
	bls	.L331
.L216:
	ldr	r3, [r4, #124]
	cmp	r3, #2
	bne	.L177
.L215:
	bl	AOE_GetWKBuf
	ldr	r3, .L344+4
	mov	r2, #28
	sub	r1, fp, #104
	ldr	r3, [r3, #24]
	str	r0, [fp, #-104]
	sub	r0, fp, #76
	ldr	ip, [r4, #112]
	str	ip, [fp, #-100]
	ldr	ip, [r4, #16]
	str	ip, [fp, #-96]
	ldr	ip, [r4, #4]
	str	ip, [fp, #-88]
	ldr	ip, [r4]
	str	ip, [fp, #-92]
	ldr	ip, [r4, #8]
	str	ip, [fp, #-84]
	ldr	ip, [r4, #12]
	str	ip, [fp, #-80]
	blx	r3
	bl	AOE_GetWKBuf
	str	r0, [fp, #-76]
	ldr	r3, [r4, #84]
	cmp	r3, #0
	bne	.L178
.L181:
	mov	r5, #0
	mov	r6, #1
.L179:
	ldr	r2, [r4, #48]
	mov	r3, r6, asl r5
	mov	r0, r5
	add	r5, r5, #1
	tst	r3, r2
	bne	.L182
	ldr	r2, [r4, #52]
	tst	r3, r2
	beq	.L183
.L182:
	bl	AOP_Flush
.L183:
	cmp	r5, #8
	bne	.L179
	mov	r3, #0
	str	r3, [r4, #132]
	str	r3, [r4, #124]
	b	.L177
.L108:
	ldr	r4, [r9]
	cmp	r4, #0
	beq	.L121
	ldr	r6, [r4, #120]
	cmp	r6, #1
	beq	.L332
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L213
.L214:
	ldr	r2, [r3, #4]
	bfc	r2, #3, #4
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L120
.L107:
	ldr	r0, [r9]
	cmp	r0, #0
	beq	.L333
	ldr	r2, [r0, #120]
	cmp	r2, #0
	beq	.L334
.L114:
	mov	r2, #1
	str	r2, [r0, #120]
.L113:
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #2, #1
	cmp	r2, #0
	ldreq	r1, [r3, #4]
	bfieq	r1, r2, #3, #4
	streq	r1, [r3, #4]
	ldreq	r2, [r3, #4]
	orreq	r2, r2, #4
	streq	r2, [r3, #4]
	b	.L316
.L322:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L325:
	ldr	r3, [fp, #-72]
	mov	r1, r7
	mov	r0, r5
	cmp	r3, #1
	ldreq	r3, [r7, #32]
	ldrne	r3, [r7, #36]
	orreq	r3, r3, r4
	orrne	r3, r3, r4
	streq	r3, [r7, #32]
	strne	r3, [r7, #36]
	bl	ENGINECheckRbfInData
	cmp	r0, #0
	ldrne	r3, [r7, #40]
	orrne	r4, r3, r4
	strne	r4, [r7, #40]
	b	.L129
.L168:
	cmp	r3, #1
	beq	.L215
	cmp	r3, #2
	beq	.L216
.L177:
	mov	r0, r4
	bl	ENGINECheckAopSpace
	cmp	r0, #0
	beq	.L121
	mov	r0, r4
	bl	ENGINECheckAipData
	cmp	r0, #0
	beq	.L121
	mov	r3, #3
	str	r3, [fp, #-76]
	ldr	r5, [r4, #12]
	cmp	r5, #0
	beq	.L335
.L190:
	ldr	r3, [r4, #132]
	cmp	r3, #2
	bne	.L121
.L195:
	ldr	r3, [r4, #124]
	cmp	r5, #0
	add	r3, r3, #1
	str	r3, [r4, #124]
	bne	.L121
.L317:
	ldr	r3, [r4, #84]
	ldr	r6, [r4, #136]
	cmp	r3, #0
	bne	.L336
.L199:
	ldr	r6, [r4, #48]
	cmp	r5, #0
	str	r6, [fp, #-112]
	ldr	r3, [r4, #52]
	str	r3, [fp, #-108]
	bne	.L121
	sub	r3, fp, #112
	str	r7, [fp, #-120]
	str	r9, [fp, #-124]
	mov	r7, r3
.L211:
	cmp	r6, #0
	beq	.L210
	mov	r5, #0
	mov	r9, #1
	b	.L209
.L205:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L210
.L209:
	mov	r8, r9, asl r5
	tst	r8, r6
	beq	.L205
	mov	r0, r5
	bl	AOP_WriteBuffProcTryCnt
	sub	r1, fp, #76
	mov	r0, r5
	bl	AOP_GetChnStatus
	ldr	r3, [r4, #64]
	tst	r8, r3
	beq	.L205
	mov	r0, r5
	sub	r8, fp, #104
	bl	AOP_WriteBuffProcOKCnt
	ldr	r3, [r4, #68]
	mov	r2, #28
	add	r1, r4, #136
	cmp	r3, #0
	mov	r0, r8
	beq	.L207
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L337
.L207:
	ldr	r3, .L344+4
	ldr	r3, [r3, #24]
	blx	r3
.L208:
	mov	r1, r8
	mov	r0, r5
	bl	AOP_WriteRbfData
	mov	r0, r5
	bl	AOP_ProcDelayCompensation
	b	.L205
.L328:
	mov	r5, #0
	str	r5, [fp, #-112]
	str	r5, [fp, #-104]
	ldr	r3, [r4, #44]
	tst	r3, #1
	bne	.L147
	mov	r6, #1
	mov	r2, r6
.L151:
	ands	r1, r3, r2, asl r6
	bne	.L338
	add	r6, r6, #1
	cmp	r6, #8
	bne	.L151
	ldr	r3, [r4, #28]
	tst	r3, #1
	bne	.L121
	mov	r1, #1
.L150:
	mov	r5, #1
	mov	r2, r5
	b	.L154
.L153:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L121
.L154:
	ands	r0, r3, r2, asl r5
	beq	.L153
	sub	r3, r5, #8
	clz	r3, r3
	mov	r3, r3, lsr #5
.L149:
	orrs	r3, r3, r1
	bne	.L121
.L221:
	sub	r1, fp, #76
	mov	r0, r5
	bl	AIP_GetChnStatus
	ldr	r8, [fp, #-76]
	ldr	r3, [r4, #12]
	cmp	r8, #0
	bne	.L155
	cmp	r3, #2
	str	r8, [r4, #20]
	str	r8, [r4, #24]
	beq	.L121
.L156:
	mov	r0, r4
	bl	ENGINECheckAopSpace
	cmp	r0, #0
	beq	.L121
	mov	r0, r4
	bl	ENGINECheckAipData
	cmp	r0, #0
	beq	.L121
	mov	r0, r5
	ldr	r2, [r4, #112]
	mov	r1, r6
	bl	ENGINEOutRawFrame
	mov	r0, r6
	bl	AOP_ProcDelayCompensation
	b	.L121
.L334:
	bl	ENGINEDestroyChn
	mov	r0, r7
	bl	ENGINECreateChn
	cmp	r0, #0
	str	r0, [r9]
	ldr	r3, [r10, #-4]
	bne	.L114
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L121
.L318:
	ldr	r2, [r3, #4]
	mov	r1, #3
	bfi	r2, r1, #3, #4
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L121
.L332:
	str	r2, [r4, #120]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L214
	b	.L120
.L324:
	ldr	r1, [fp, #-64]
	ldr	r3, [fp, #-156]
	cmp	r3, r1
	bne	.L126
	ldr	r3, [fp, #-132]
	orr	r3, r3, r8
	str	r3, [fp, #-132]
	b	.L127
.L327:
	ldrsh	r1, [r4, #92]
	cmp	r1, ip
	bne	.L143
	ldrsh	r1, [r4, #96]
	cmp	r1, r2
	bne	.L143
	ldrh	r2, [r4, #100]
	cmp	r3, r2
	bne	.L143
	ldrsh	r3, [r4, #98]
	cmp	r3, lr
	beq	.L145
	b	.L143
.L210:
	sub	r3, fp, #108
	cmp	r7, r3
	beq	.L339
	ldr	r6, [r7, #4]!
	b	.L211
.L155:
	cmp	r3, #2
	bne	.L156
	mov	r0, r4
	bl	ENGINECheckAopSpace
	subs	r8, r8, #1
	movne	r8, #1
	cmp	r0, #0
	movne	r0, r8
	orreq	r0, r8, #1
	cmp	r0, #0
	bne	.L121
	ldr	r8, [r4, #20]
	str	r8, [fp, #-112]
	ldr	r3, [r4, #24]
	orrs	r2, r3, r8
	str	r3, [fp, #-104]
	beq	.L340
.L157:
	cmp	r8, #0
	beq	.L160
	ldr	ip, [r4, #112]
	cmp	ip, r8
	str	ip, [fp, #-120]
	bhi	.L161
	mov	r0, r4
	bl	ENGINECheckAipData
	ldr	ip, [fp, #-120]
	cmp	r0, #0
	beq	.L121
.L162:
	mov	r2, ip
	mov	r0, r5
	mov	r1, r6
	str	ip, [fp, #-120]
	bl	ENGINEOutRawFrame
	ldr	r8, [fp, #-112]
	ldr	ip, [fp, #-120]
	rsb	r8, ip, r8
	str	r8, [fp, #-112]
	cmp	r8, #0
	bne	.L163
	ldr	r3, [r4, #112]
	cmp	ip, r3
	bcs	.L163
	ldr	r2, [fp, #-104]
	rsb	r5, ip, r3
	cmp	r5, r2
	bls	.L341
.L163:
	mov	r0, r6
	bl	AOP_ProcDelayCompensation
	ldr	r2, [fp, #-112]
	ldr	r8, [fp, #-104]
.L165:
	str	r2, [r4, #20]
	str	r8, [r4, #24]
	b	.L121
.L331:
	mov	r3, #1
	str	r3, [r4, #132]
	b	.L215
.L333:
	mov	r0, r7
	bl	ENGINECreateChn
	cmp	r0, #0
	str	r0, [r9]
	beq	.L342
	mov	r3, #1
	str	r3, [r0, #120]
	ldr	r3, [r10, #-4]
	b	.L113
.L338:
	ldr	r3, [r4, #28]
	sub	r1, r6, #8
	clz	r1, r1
	tst	r3, #1
	mov	r1, r1, lsr #5
	beq	.L150
	mov	r3, #0
	mov	r5, r3
	b	.L149
.L178:
	ldr	r3, .L344+4
	mov	r1, #0
	ldr	r2, [r4, #112]
	mov	r5, #6
	ldr	r0, [fp, #-104]
	ldr	r3, [r3, #20]
	blx	r3
.L180:
	ldr	r3, .L344+4
	ldr	r3, [r3, #32]
	blx	r3
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-104]
	ldr	r0, [r4, #72]
	bl	iMedia_AVC_Apply
	ldr	r3, .L344+4
	ldr	r3, [r3, #36]
	blx	r3
	subs	r5, r5, #1
	bne	.L180
	b	.L181
.L339:
	ldr	r7, [fp, #-120]
	ldr	r9, [fp, #-124]
	b	.L121
.L335:
	ldr	r3, .L344+4
	mov	r1, r5
	ldr	r2, [r4, #140]
	mov	r6, r5
	ldr	r0, [r4, #136]
	mov	r8, #1
	ldr	r3, [r3, #20]
	blx	r3
.L189:
	ldr	r3, [r4, #28]
	mov	r0, r6
	sub	r1, fp, #76
	ands	r3, r3, r8, asl r6
	beq	.L186
	ldr	r5, [r4, #12]
	cmp	r5, #0
	bne	.L190
	bl	AIP_GetPcmType
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	bls	.L343
.L186:
	add	r6, r6, #1
	cmp	r6, #8
	bne	.L189
	ldr	r5, [r4, #12]
	cmp	r5, #0
	subeq	r8, fp, #44
	moveq	r3, #3
	moveq	r6, #1
	streq	r3, [r8, #-32]!
	beq	.L194
	b	.L190
.L192:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L193
.L194:
	ldr	r3, [r4, #28]
	ands	r3, r3, r6, asl r5
	beq	.L192
	mov	r1, r8
	mov	r0, r5
	bl	AIP_GetPcmType
	ldr	r3, [fp, #-76]
	cmp	r3, #2
	bne	.L192
	mov	r1, r5
	ldr	r2, [r4, #136]
	mov	r0, r4
	bl	ENGINEMixData
.L193:
	ldr	r3, [r4, #132]
	ldr	r5, [r4, #12]
	cmp	r3, #2
	beq	.L195
	cmp	r5, #0
	bne	.L121
	b	.L317
.L336:
	bl	AOE_GetWKBuf
	ldr	r3, .L344+4
	ldr	r3, [r3, #32]
	mov	r5, r0
	blx	r3
	mov	r2, r5
	mov	r1, r6
	ldr	r0, [r4, #72]
	bl	iMedia_AVC_Apply
	ldr	r3, .L344+4
	ldr	r3, [r3, #36]
	blx	r3
	ldr	r3, .L344+4
	mov	r1, r5
	mov	r0, r6
	ldr	r2, [r4, #112]
	ldr	r3, [r3, #24]
	blx	r3
	ldr	r5, [r4, #12]
	b	.L199
.L343:
	ldr	r2, [r4, #136]
	mov	r1, r6
	mov	r0, r4
	bl	ENGINEMixData
	b	.L186
.L147:
	ldr	r3, [r4, #28]
	ands	r1, r3, #1
	bne	.L227
	mov	r6, r1
	b	.L150
.L342:
	ldr	r3, [r10, #-4]
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L121
	b	.L318
.L337:
	ldr	r3, .L344+4
	sub	r8, fp, #104
	add	r1, r4, #164
	mov	r0, r8
	ldr	r3, [r3, #24]
	blx	r3
	b	.L208
.L160:
	ldr	r2, [fp, #-104]
	cmp	r2, #0
	beq	.L165
	ldr	r3, [r4, #112]
	mov	r0, r6
	cmp	r2, r3
	movcc	r5, r2
	movcs	r5, r3
	bl	AOP_GetRingOut
	cmp	r0, #0
	beq	.L166
	mov	r1, r8
	mov	r2, r5
	bl	RBUF_WriteDataDma
.L166:
	ldr	r3, [fp, #-104]
	ldr	r2, [fp, #-112]
	rsb	r8, r5, r3
	b	.L165
.L340:
	mov	r0, r5
	bl	AIP_QueryBusy
	cmp	r0, #3
	bls	.L121
	sub	r2, fp, #104
	sub	r1, fp, #112
	mov	r0, r5
	bl	AIP_GetCompressInfo
	ldr	r8, [fp, #-112]
	ldr	r3, [fp, #-104]
	cmp	r8, #0
	bne	.L159
	cmp	r3, #0
	bne	.L159
	mov	r0, r5
	bl	AIP_GetRingIn
	bl	RBUF_Flush
	ldr	r8, [fp, #-112]
	ldr	r3, [fp, #-104]
.L159:
	str	r8, [r4, #20]
	str	r3, [r4, #24]
	b	.L157
.L161:
	mov	r0, r5
	bl	AIP_QueryBusy
	cmp	r0, r8
	bcc	.L121
	mov	ip, r8
	b	.L162
.L227:
	mov	r6, r5
	b	.L221
.L341:
	mov	r0, r6
	bl	AOP_GetRingOut
	cmp	r0, #0
	beq	.L164
	mov	r1, r8
	mov	r2, r5
	bl	RBUF_WriteDataDma
.L164:
	ldr	r3, [fp, #-104]
	rsb	r5, r5, r3
	str	r5, [fp, #-104]
	b	.L163
.L345:
	.align	2
.L344:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINE_Process, .-ENGINE_Process
	.align	2
	.global	ENGINE_Init
	.type	ENGINE_Init, %function
ENGINE_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L349
	mov	r4, r0
	ldr	r8, .L349+4
	mov	r7, #0
	add	r6, r5, #24
.L347:
	str	r4, [r5], #4
	mov	r2, #128
	ldr	r3, [r8, #20]
	mov	r0, r4
	mov	r1, #0
	add	r4, r4, #128
	blx	r3
	ldr	r3, [r4, #-124]
	cmp	r5, r6
	mov	r2, #1
	orr	r3, r3, #4
	str	r3, [r4, #-124]
	ldr	r3, [r4, #-124]
	bfi	r3, r2, #0, #2
	str	r3, [r4, #-124]
	str	r7, [r5, #20]
	bne	.L347
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L350:
	.align	2
.L349:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINE_Init, .-ENGINE_Init
	.align	2
	.global	ENGINE_DeInit
	.type	ENGINE_DeInit, %function
ENGINE_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L354
	mov	r6, #0
	add	r5, r4, #24
.L352:
	ldr	r0, [r4, #4]!
	bl	ENGINEDestroyChn
	cmp	r4, r5
	str	r6, [r4]
	bne	.L352
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L355:
	.align	2
.L354:
	.word	.LANCHOR0+20
	UNWIND(.fnend)
	.size	ENGINE_DeInit, .-ENGINE_DeInit
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stEneRm, %object
	.size	g_stEneRm, 48
g_stEneRm:
	.space	48
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
