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
	.file	"aoe_aip.c"
	.text
	.align	2
	.type	AIPDestroyChn, %function
AIPDestroyChn:
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
	ldr	r0, [r4, #124]
	mov	r3, #0
	str	r3, [r4, #148]
	cmp	r0, r3
	beq	.L3
	bl	RBUF_Destroy
.L3:
	ldr	r0, [r4, #128]
	cmp	r0, #0
	beq	.L4
	bl	RBUF_Destroy
.L4:
	ldr	r0, [r4, #140]
	cmp	r0, #0
	beq	.L5
	bl	FADE_Destroy
.L5:
	ldr	r0, [r4, #132]
	cmp	r0, #0
	beq	.L6
	bl	LSRC_Destroy
.L6:
	ldr	r0, [r4, #136]
	cmp	r0, #0
	beq	.L7
	ldr	r3, [r4, #236]
	cmp	r3, #2
	beq	.L32
.L8:
	bl	ResamplerFree
.L7:
	ldr	r1, [r4, #212]
	cmp	r1, #0
	beq	.L9
	mov	r0, #26
	bl	HI_ADSP_FREE
.L9:
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
.L32:
	ldr	r1, [r4, #144]
	cmp	r1, #0
	beq	.L8
	mov	r0, #26
	bl	HI_ADSP_FREE
	b	.L7
	UNWIND(.fnend)
	.size	AIPDestroyChn, .-AIPDestroyChn
	.align	2
	.type	AIPGainPcmData, %function
AIPGainPcmData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, .L46
	mov	r4, #0
	mov	r6, r0
	mov	r2, #20
	str	r4, [fp, #-48]
	ldr	r3, [r3, #24]
	mov	r5, r1
	str	r4, [fp, #-44]
	add	r1, r6, #152
	str	r4, [fp, #-40]
	sub	r0, fp, #48
	str	r4, [fp, #-36]
	str	r4, [fp, #-32]
	blx	r3
	ldr	r3, [r6, #172]
	ldr	r2, [fp, #-44]
	ldr	r1, [fp, #-32]
	add	r2, r3, r2
	cmp	r2, #120
	subhi	r4, r2, #121
	ldr	r2, [fp, #-40]
	str	r4, [fp, #-44]
	add	r3, r3, r2
	ldr	r2, [fp, #-36]
	cmp	r3, #120
	subhi	r3, r3, #121
	movls	r3, #0
	cmp	r4, #121
	str	r3, [fp, #-40]
	ldr	r3, [r6, #176]
	add	r2, r3, r2
	add	r3, r3, r1
	str	r2, [fp, #-36]
	str	r3, [fp, #-32]
	beq	.L45
.L38:
	sub	r2, fp, #48
	mov	r0, r5
	mov	r1, #0
	bl	UTIL_LRGainProcess
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L45:
	ldr	r1, [fp, #-40]
	cmp	r2, #0
	cmpeq	r1, #121
	movne	r2, #1
	moveq	r2, #0
	cmp	r3, #0
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r3, #0
	bne	.L38
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L47:
	.align	2
.L46:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIPGainPcmData, .-AIPGainPcmData
	.align	2
	.global	AIP_GetPcmType
	.type	AIP_GetPcmType, %function
AIP_GetPcmType:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L51
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r3, [r3]
	moveq	r3, #3
	ubfxne	r3, r3, #11, #3
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L52:
	.align	2
.L51:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetPcmType, .-AIP_GetPcmType
	.global	__aeabi_uidiv
	.align	2
	.global	AIPFadeoutChnData
	.type	AIPFadeoutChnData, %function
AIPFadeoutChnData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r4, r0
	sub	r1, fp, #64
	ldr	r0, [r0, #128]
	mov	r3, #0
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	str	r3, [fp, #-36]
	str	r3, [fp, #-32]
	bl	RBUF_QueryInfo
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	beq	.L53
	ldr	r6, [r4, #112]
	ldr	r0, [fp, #-48]
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r5, r0
	ldr	r0, [fp, #-44]
	bl	__aeabi_uidiv
	mov	r2, #8
	mov	r1, #2
	mov	r6, r0
	ldr	r0, [r4, #140]
	bl	FADE_Active
	ldr	r3, [r4, #72]
	ldr	r2, [r4, #68]
	ldr	r1, [r4, #76]
	ldr	r0, [r4, #140]
	bl	FADE_Flush
	ldr	r1, [fp, #-64]
	ldr	r3, [fp, #-60]
	mov	r2, r5
	ldr	r0, [r4, #140]
	add	r1, r1, r3
	bl	FADE_OutProcess
	rsb	r2, r5, r6
	ldr	r0, [r4, #140]
	ldr	r1, [fp, #-64]
	bl	FADE_OutProcess
.L53:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AIPFadeoutChnData, .-AIPFadeoutChnData
	.align	2
	.global	AIPGetRbfFiFoAttr
	.type	AIPGetRbfFiFoAttr, %function
AIPGetRbfFiFoAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L63
	mov	r4, r1
	ldr	r5, [r3, r0, asl #2]
	add	r0, r1, #68
	ldr	r1, [r5, #4]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L62
	ldr	r1, [r5, #4]
	add	r0, r4, #72
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L62
	ldr	r1, [r5, #4]
	add	r0, r4, #76
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L62
	ldr	r1, [r5, #4]
	add	r0, r4, #80
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	cmp	r0, #0
	bne	.L62
	ldr	r1, [r5, #4]
	sub	r0, fp, #32
	ubfx	r1, r1, #10, #6
	bl	AOE_REG_ReadBufLatencyMs
	subs	r6, r0, #0
	bne	.L62
	ldr	r1, [r4, #68]
	ldr	r0, [r4, #72]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #76]
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [fp, #-32]
	bl	UTIL_LatencyMs2ByteSize
	ldr	r3, [fp, #-32]
	add	r1, r5, #68
	str	r7, [r4, #112]
	add	r5, r5, #72
	str	r6, [r4, #88]
	str	r6, [r4, #108]
	str	r3, [r4, #120]
	str	r3, [r4, #84]
	str	r1, [r4, #100]
	str	r5, [r4, #104]
	str	r0, [r4, #96]
	str	r0, [r4, #116]
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L62:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L64:
	.align	2
.L63:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetRbfFiFoAttr, .-AIPGetRbfFiFoAttr
	.align	2
	.global	AIPGetRbfInAttr
	.type	AIPGetRbfInAttr, %function
AIPGetRbfInAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L81
	mov	r4, r1
	ldr	r5, [r3, r0, asl #2]
	add	r0, r1, #16
	ldr	r1, [r5]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L68
	ldr	r1, [r5]
	add	r0, r4, #20
	ubfx	r1, r1, #2, #3
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L68
	ldr	r1, [r5]
	add	r0, r4, #24
	ubfx	r1, r1, #5, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	beq	.L71
	ldr	r3, [r5]
	ubfx	r3, r3, #5, #4
	cmp	r3, #15
	beq	.L80
.L71:
	ldr	r1, [r5]
	add	r0, r4, #28
	ubfx	r1, r1, #9, #2
	bl	AOE_REG_ReadDataFormat
	subs	r6, r0, #0
	bne	.L68
	ldr	r3, [r4, #28]
	cmp	r3, #0
	bne	.L75
	ldr	r1, [r5]
	mov	r0, r4
	ubfx	r1, r1, #11, #3
	bl	AOE_REG_ReadPcmType
	cmp	r0, #0
	bne	.L68
.L75:
	ldr	r3, [r5]
	ldr	r1, [r4, #16]
	ubfx	r3, r3, #14, #1
	ldr	r0, [r4, #20]
	str	r3, [r4, #4]
	bl	UTIL_CalcFrameSize
	mov	r2, #0
	mov	r3, #1
	str	r2, [fp, #-36]
	str	r3, [r4, #32]
	str	r2, [fp, #-32]
	ldr	r3, [r5, #16]
	str	r3, [fp, #-36]
	ldr	r1, [fp, #-36]
	ldr	r3, [r5, #20]
	str	r1, [r4, #36]
	str	r3, [fp, #-32]
	ldr	r3, [r5, #24]
	bic	r3, r3, #-16777216
	str	r3, [r4, #40]
	ldr	r1, [r5, #24]
	tst	r1, #16777216
	bne	.L73
	add	r1, r5, #28
	add	r2, r5, #36
	str	r1, [r4, #44]
	str	r2, [r4, #48]
.L76:
	ldr	r2, [r5, #24]
	mov	ip, #0
	str	r0, [r4, #56]
	mov	r1, #16
	ubfx	r2, r2, #24, #1
	str	r3, [r4, #60]
	mov	r0, r6
	mov	r3, #8
	str	r2, [r4, #52]
	str	ip, [r4, #64]
	str	r1, [r4, #8]
	str	r3, [r4, #12]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L73:
	str	r2, [fp, #-36]
	str	r2, [fp, #-32]
	ldr	r1, [r5, #28]
	str	r1, [fp, #-36]
	ldr	ip, [fp, #-36]
	ldr	r1, [r5, #32]
	str	ip, [r4, #44]
	str	r1, [fp, #-32]
	str	r2, [fp, #-36]
	str	r2, [fp, #-32]
	ldr	r2, [r5, #36]
	str	r2, [fp, #-36]
	ldr	r1, [fp, #-36]
	ldr	r2, [r5, #40]
	str	r1, [r4, #48]
	str	r2, [fp, #-32]
	b	.L76
.L80:
	ldr	r3, [r5, #12]
	movw	r2, #56928
	movt	r2, 2
	bic	r3, r3, #-16777216
	str	r3, [r4, #24]
	sub	r3, r3, #4000
	cmp	r3, r2
	bhi	.L68
	ldr	r3, [r4, #20]
	cmp	r3, #2
	bhi	.L68
	ldr	r3, [r4, #16]
	cmp	r3, #16
	beq	.L71
.L68:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L82:
	.align	2
.L81:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetRbfInAttr, .-AIPGetRbfInAttr
	.align	2
	.global	AIPGetChnCreateAttr
	.type	AIPGetChnCreateAttr, %function
AIPGetChnCreateAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	mov	r5, r1
	bl	AIPGetRbfInAttr
	cmp	r0, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AIPGetRbfFiFoAttr
	UNWIND(.fnend)
	.size	AIPGetChnCreateAttr, .-AIPGetChnCreateAttr
	.align	2
	.global	AIPIsChnAttrChange
	.type	AIPIsChnAttrChange, %function
AIPIsChnAttrChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	ldr	r3, .L86
	add	r2, r0, #8
	sub	r1, fp, #152
	ldr	r5, [r3, r2, asl #2]
	bl	AIPGetChnCreateAttr
	ldr	lr, [fp, #-132]
	ldr	r3, [fp, #-136]
	ldr	r0, [r5, #20]
	ldr	ip, [r5, #16]
	subs	r4, r0, lr
	ldr	r2, [r5, #24]
	ldr	r0, [fp, #-128]
	movne	r4, #1
	cmp	ip, r3
	moveq	lr, r4
	addne	lr, r4, #1
	ldr	r3, [r5, #28]
	cmp	r2, r0
	moveq	ip, lr
	addne	ip, lr, #1
	ldr	r4, [fp, #-124]
	ldr	r0, [r5]
	ldr	lr, [fp, #-152]
	cmp	r3, r4
	moveq	r1, ip
	addne	r1, ip, #1
	ldr	r4, [r5, #4]
	ldr	ip, [fp, #-148]
	cmp	r0, lr
	moveq	r2, r1
	addne	r2, r1, #1
	ldr	lr, [r5, #36]
	ldr	r1, [fp, #-116]
	cmp	r4, ip
	moveq	r3, r2
	addne	r3, r2, #1
	ldr	ip, [r5, #40]
	ldr	r2, [fp, #-112]
	cmp	lr, r1
	moveq	r0, r3
	addne	r0, r3, #1
	ldr	r1, [r5, #52]
	ldr	r3, [fp, #-100]
	cmp	ip, r2
	moveq	r4, r0
	addne	r4, r0, #1
	ldr	r2, [r5, #68]
	ldr	r0, [fp, #-84]
	cmp	r1, r3
	moveq	lr, r4
	addne	lr, r4, #1
	ldr	r6, [fp, #-80]
	ldr	r3, [r5, #72]
	cmp	r2, r0
	moveq	ip, lr
	addne	ip, lr, #1
	ldr	r4, [fp, #-76]
	ldr	r0, [r5, #76]
	cmp	r3, r6
	moveq	r1, ip
	addne	r1, ip, #1
	ldr	lr, [r5, #80]
	ldr	ip, [fp, #-72]
	cmp	r0, r4
	moveq	r2, r1
	addne	r2, r1, #1
	ldr	r0, [r5, #84]
	ldr	r1, [fp, #-68]
	cmp	lr, ip
	moveq	r3, r2
	addne	r3, r2, #1
	cmp	r0, r1
	moveq	r0, r3
	addne	r0, r3, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L87:
	.align	2
.L86:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPIsChnAttrChange, .-AIPIsChnAttrChange
	.align	2
	.global	AIPCreateChn
	.type	AIPCreateChn, %function
AIPCreateChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #244)
	sub	sp, sp, #244
	ldr	r3, .L156
	sub	r1, fp, #160
	mov	r4, #0
	mov	r7, r0
	str	r4, [fp, #-268]
	ldr	r5, [r3, r0, asl #2]
	str	r4, [fp, #-264]
	str	r4, [fp, #-260]
	str	r4, [fp, #-256]
	str	r4, [fp, #-252]
	bl	AIPGetChnCreateAttr
	subs	r6, r0, #0
	movne	r0, r4
	bne	.L152
	mov	r1, #308
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L90
	ldr	r8, .L156+4
	mov	r2, #308
	mov	r1, r6
	ldr	r3, [r8, #20]
	blx	r3
	ldr	r3, [r8, #24]
	sub	r1, fp, #160
	mov	r2, #124
	mov	r0, r4
	blx	r3
	str	r7, [r4, #232]
	sub	r1, fp, #128
	sub	r0, fp, #256
	bl	RBUF_Create_EXT
	ldr	r3, [fp, #-256]
	cmp	r3, #0
	beq	.L90
	ldr	r2, [fp, #-132]
	str	r3, [r4, #124]
	cmp	r2, #0
	beq	.L153
	str	r6, [r5, #60]
	ldr	r3, [r5, #64]
	bfi	r3, r6, #0, #16
	str	r3, [r5, #64]
.L92:
	mov	r1, #768
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #212]
	beq	.L90
	ldr	r3, [fp, #-132]
	cmp	r3, #0
	bne	.L94
	ldr	ip, [fp, #-136]
	ldr	r2, [fp, #-84]
	cmp	ip, r2
	beq	.L95
	cmp	ip, #32000
	beq	.L96
	bls	.L154
	movw	r3, #22664
	movt	r3, 1
	cmp	ip, r3
	beq	.L96
	bhi	.L100
	movw	r3, #44100
	cmp	ip, r3
	bne	.L96
	ldr	lr, [fp, #-88]
	mov	r0, #2
	ldr	r3, [fp, #-92]
	sub	r1, fp, #244
	str	r0, [r4, #236]
	sub	r0, fp, #248
	str	ip, [fp, #-244]
	str	r2, [fp, #-240]
	str	lr, [fp, #-232]
	str	r3, [fp, #-236]
	bl	iMedia_ASRC_GetSize
	cmp	r0, #0
	bne	.L90
	ldr	r1, [fp, #-248]
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #144]
	beq	.L90
	ldr	r7, [fp, #-88]
	mov	r1, r0
	ldr	r6, [fp, #-92]
	sub	r3, fp, #228
	ldr	lr, [fp, #-136]
	sub	r0, fp, #268
	ldr	ip, [fp, #-84]
	ldr	r2, [fp, #-248]
	str	r7, [fp, #-216]
	str	r6, [fp, #-220]
	str	lr, [fp, #-228]
	str	ip, [fp, #-224]
	bl	iMedia_ASRC_Init
	cmp	r0, #0
	bne	.L90
	ldr	r0, [fp, #-268]
	b	.L107
.L154:
	movw	r3, #12000
	cmp	ip, r3
	beq	.L96
.L96:
	mov	r3, #1
	mov	r1, r2
	str	r3, [r4, #236]
	mov	r0, ip
	ldr	r3, [fp, #-92]
	mov	ip, #0
	ldr	r2, [fp, #-88]
	str	ip, [sp]
	bl	ResamplerCreate
	cmp	r0, #0
	str	r0, [fp, #-268]
	beq	.L90
.L107:
	ldr	r2, [fp, #-84]
	str	r0, [r4, #136]
.L95:
	ldr	ip, [fp, #-88]
	mov	r1, r2
	ldr	r3, [fp, #-92]
	sub	r0, fp, #264
	str	ip, [sp]
	bl	LSRC_Create
	ldr	r3, [fp, #-264]
	cmp	r3, #0
	beq	.L90
	str	r3, [r4, #132]
	mov	r6, #0
	str	r6, [r5, #80]
	ldr	r3, [r4]
	cmp	r3, r6
	beq	.L94
	ldr	r3, [fp, #-140]
	sub	r0, fp, #260
	ldr	r2, [fp, #-144]
	ldr	r1, [fp, #-136]
	bl	FADE_Create
	ldr	r3, [fp, #-260]
	cmp	r3, r6
	beq	.L90
	str	r3, [r4, #140]
	str	r6, [r4, #200]
.L94:
	mov	r3, #0
	mov	r2, #3
	mov	r1, #256
	str	r3, [r4, #152]
	str	r3, [r4, #156]
	str	r3, [r4, #160]
	str	r3, [r4, #184]
	str	r1, [r4, #284]
	str	r2, [r4, #288]
	ldr	r1, [r4, #68]
	ldr	r0, [r4, #72]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r4, #76]
	movw	r2, #19923
	movw	r1, #48000
	cmp	r3, r1
	movt	r2, 4194
	add	r3, r3, r3, lsl #2
	umull	r2, r3, r3, r2
	mov	r3, r3, lsr #6
	beq	.L155
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
.L106:
	mul	r3, r0, r3
	ldr	r1, [r4, #68]
	ldr	r0, [r4, #72]
	str	r3, [r4, #216]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #84]
	ldr	r3, [r4, #76]
	movw	ip, #19923
	movt	ip, 4194
	ldr	r1, [r4, #68]
	mul	r3, r3, r2
	umull	r2, r3, r3, ip
	mov	r3, r3, lsr #6
	mul	r3, r3, r0
	ldr	r0, [r4, #72]
	str	r3, [r4, #228]
	bl	UTIL_CalcFrameSize
	ldr	r1, [r4, #16]
	str	r0, [r4, #220]
	ldr	r0, [r4, #20]
	bl	UTIL_CalcFrameSize
	mov	r3, #1
	mov	r1, r3
	str	r3, [r4, #148]
	mov	r2, #8
	str	r0, [r4, #224]
	ldr	r0, [r4, #140]
	bl	FADE_Active
	mov	r0, r4
.L152:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L153:
	sub	r0, fp, #252
	sub	r1, fp, #72
	bl	RBUF_Create
	ldr	r0, [fp, #-252]
	cmp	r0, #0
	beq	.L90
	str	r0, [r4, #128]
	sub	r1, fp, #196
	bl	RBUF_QueryInfo
	ldrh	r2, [fp, #-184]
	ldr	r3, [r5, #64]
	bfi	r3, r2, #0, #16
	str	r3, [r5, #64]
	b	.L92
.L155:
	ands	r2, r3, #255
	addne	r3, r3, #256
	rsbne	r3, r2, r3
	b	.L106
.L100:
	b	.L96
.L90:
	mov	r0, r4
	bl	AIPDestroyChn
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L157:
	.align	2
.L156:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIPCreateChn, .-AIPCreateChn
	.align	2
	.global	AIPFlushChnCtx
	.type	AIPFlushChnCtx, %function
AIPFlushChnCtx:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #136]
	cmp	r0, #0
	beq	.L159
	ldr	r3, [r4, #236]
	cmp	r3, #2
	beq	.L169
	bl	ResampleFlush
.L159:
	ldr	r0, [r4, #132]
	cmp	r0, #0
	beq	.L161
	bl	LSRC_Flush
.L161:
	ldr	r0, [r4, #140]
	mov	r3, #0
	str	r3, [r4, #208]
	cmp	r0, r3
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r2, #8
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	FADE_Active
.L169:
	bl	iMedia_ASRC_Flush
	b	.L159
	UNWIND(.fnend)
	.size	AIPFlushChnCtx, .-AIPFlushChnCtx
	.align	2
	.global	AIPFlushChnRufIn
	.type	AIPFlushChnRufIn, %function
AIPFlushChnRufIn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #124]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AIPFlushChnRufIn, .-AIPFlushChnRufIn
	.align	2
	.global	AIPFlushChnFifo
	.type	AIPFlushChnFifo, %function
AIPFlushChnFifo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #128]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AIPFlushChnFifo, .-AIPFlushChnFifo
	.align	2
	.global	AIPFlushChn
	.type	AIPFlushChn, %function
AIPFlushChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	tst	r1, #1
	mov	r4, r1
	mov	r5, r0
	bne	.L193
.L175:
	tst	r4, #2
	beq	.L176
	ldr	r0, [r5, #124]
	cmp	r0, #0
	beq	.L176
	bl	RBUF_Flush
.L176:
	tst	r4, #4
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r5, #128]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	RBUF_Flush
.L193:
	bl	AIPFlushChnCtx
	b	.L175
	UNWIND(.fnend)
	.size	AIPFlushChn, .-AIPFlushChn
	.align	2
	.global	AIPWriteMuteFrame
	.type	AIPWriteMuteFrame, %function
AIPWriteMuteFrame:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #128]
	ldr	r5, [r4, #216]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	bl	RBUF_QueryFree
	cmp	r5, r0
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	mov	r2, r5
	ldr	r0, [r4, #128]
	mov	r1, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	RBUF_WriteData
	UNWIND(.fnend)
	.size	AIPWriteMuteFrame, .-AIPWriteMuteFrame
	.align	2
	.global	AIPGetChnCmd
	.type	AIPGetChnCmd, %function
AIPGetChnCmd:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L208
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #8]
	tst	r2, #8
	movne	r0, #4
	beq	.L207
.L199:
	str	r0, [r1]
	ldmfd	sp, {fp, sp, pc}
.L207:
	ldr	r2, [r3, #8]
	and	r2, r2, #3
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L200
.L201:
	.word	.L206
	.word	.L202
	.word	.L203
	.word	.L204
.L206:
	mov	r0, #0
	b	.L199
.L204:
	mov	r0, #3
	b	.L199
.L203:
	mov	r0, #2
	b	.L199
.L202:
	mov	r0, #1
	b	.L199
.L200:
	ldr	r2, [r3, #8]
	mov	ip, #4
	mov	r0, ip
	bfi	r2, ip, #4, #4
	str	r2, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
	b	.L199
.L209:
	.align	2
.L208:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetChnCmd, .-AIPGetChnCmd
	.align	2
	.global	AIPAckChnCmd
	.type	AIPAckChnCmd, %function
AIPAckChnCmd:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L212
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #8]
	tst	r2, #8
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r3, #8]
	bfi	r2, r1, #4, #4
	str	r2, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
	ldmfd	sp, {fp, sp, pc}
.L213:
	.align	2
.L212:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPAckChnCmd, .-AIPAckChnCmd
	.align	2
	.global	IsDataEnoughForFadeout
	.type	IsDataEnoughForFadeout, %function
IsDataEnoughForFadeout:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #124]
	bl	RBUF_QueryBusy
	ldr	r1, [r4, #16]
	mov	r5, r0
	ldr	r0, [r4, #20]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #24]
	mov	r1, r0
	mov	r0, r5
	bl	UTIL_LatencyMs
	mov	r5, r0
	ldr	r0, [r4, #128]
	bl	RBUF_QueryBusy
	ldr	r1, [r4, #68]
	mov	r6, r0
	ldr	r0, [r4, #72]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #76]
	mov	r1, r0
	mov	r0, r6
	bl	UTIL_LatencyMs
	ldr	r1, [r4, #76]
	mov	r6, r0
	ldr	r0, [r4, #208]
	bl	__aeabi_uidiv
	mov	r3, #1000
	mla	r0, r3, r0, r6
	cmp	r0, #4
	cmpls	r5, #4
	movls	r0, #1
	movhi	r0, #0
	eor	r0, r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	IsDataEnoughForFadeout, .-IsDataEnoughForFadeout
	.align	2
	.global	AIPStopChnCmdProc
	.type	AIPStopChnCmdProc, %function
AIPStopChnCmdProc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L225
	add	r3, r0, #8
	mov	r7, r0
	ldr	r5, [r6, r0, asl #2]
	ldr	r4, [r6, r3, asl #2]
	cmp	r4, #0
	cmpne	r5, #0
	moveq	r8, #1
	movne	r8, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r4, #148]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r2, r5
	bls	.L223
.L218:
	ldr	r3, [r2, #8]
	ubfx	r3, r3, #3, #1
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r1, [r2, #8]
	bfi	r1, r3, #4, #4
	str	r1, [r2, #8]
	ldr	r3, [r2, #8]
	orr	r3, r3, #8
	str	r3, [r2, #8]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L223:
	mov	r0, r4
	bl	IsDataEnoughForFadeout
	cmp	r0, #0
	bne	.L224
	mov	r1, #4
	mov	r0, r4
	bl	AIPFlushChn
	mov	r3, #1
	str	r3, [r4, #240]
.L220:
	mov	r1, #3
	mov	r0, r4
	bl	AIPFlushChn
	mov	r0, r4
	bl	AIPWriteMuteFrame
	mov	r3, #0
	ldr	r2, [r6, r7, asl #2]
	str	r3, [r4, #148]
	str	r3, [r5, #80]
	b	.L218
.L224:
	mov	r0, r4
	bl	AIPFadeoutChnData
	str	r8, [r4, #240]
	b	.L220
.L226:
	.align	2
.L225:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPStopChnCmdProc, .-AIPStopChnCmdProc
	.align	2
	.global	AIFlushChnCmdProc
	.type	AIFlushChnCmdProc, %function
AIFlushChnCmdProc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L235
	add	r3, r0, #8
	mov	r6, r0
	ldr	r4, [r5, r3, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, [r4, #148]
	cmp	r7, #1
	beq	.L233
	cmp	r7, #2
	beq	.L234
.L231:
	ldr	r2, [r5, r6, asl #2]
	ldr	r3, [r2, #8]
	ubfx	r3, r3, #3, #1
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #8]
	bfi	r1, r3, #4, #4
	str	r1, [r2, #8]
	ldr	r3, [r2, #8]
	orr	r3, r3, #8
	str	r3, [r2, #8]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L233:
	mov	r0, r4
	bl	AIPFadeoutChnData
	mov	r1, #3
	mov	r0, r4
	bl	AIPFlushChn
	mov	r0, r4
	bl	AIPWriteMuteFrame
	mov	r1, r7
	ldr	r0, [r4, #140]
	mov	r2, #8
	bl	FADE_Active
	b	.L231
.L234:
	mov	r0, r4
	mov	r1, #7
	bl	AIPFlushChn
	b	.L231
.L236:
	.align	2
.L235:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIFlushChnCmdProc, .-AIFlushChnCmdProc
	.align	2
	.global	AIPPauseChnCmdProc
	.type	AIPPauseChnCmdProc, %function
AIPPauseChnCmdProc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L243
	add	r3, r0, #8
	mov	r6, r0
	ldr	r4, [r5, r3, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, [r4, #148]
	cmp	r7, #1
	beq	.L242
.L240:
	ldr	r2, [r5, r6, asl #2]
	ldr	r3, [r2, #8]
	ubfx	r3, r3, #3, #1
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #8]
	bfi	r1, r3, #4, #4
	str	r1, [r2, #8]
	ldr	r3, [r2, #8]
	orr	r3, r3, #8
	str	r3, [r2, #8]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L242:
	mov	r0, r4
	bl	AIPFadeoutChnData
	mov	r1, r7
	mov	r0, r4
	bl	AIPFlushChn
	mov	r3, #2
	str	r3, [r4, #148]
	b	.L240
.L244:
	.align	2
.L243:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPPauseChnCmdProc, .-AIPPauseChnCmdProc
	.align	2
	.global	AIPStartChnCmdProc
	.type	AIPStartChnCmdProc, %function
AIPStartChnCmdProc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L258
	add	r7, r0, #8
	mov	r6, r0
	ldr	r5, [r4, r7, asl #2]
	cmp	r5, #0
	beq	.L254
	ldr	r3, [r5, #148]
	cmp	r3, #0
	beq	.L256
	cmp	r3, #2
	beq	.L255
.L250:
	ldr	r2, [r4, r6, asl #2]
	ldr	r3, [r2, #8]
	ubfx	r3, r3, #3, #1
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #8]
	bfi	r1, r3, #4, #4
	str	r1, [r2, #8]
	ldr	r3, [r2, #8]
	orr	r3, r3, #8
	str	r3, [r2, #8]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L256:
	bl	AIPIsChnAttrChange
	cmp	r0, #0
	bne	.L257
.L255:
	mov	r1, #1
	ldr	r0, [r5, #140]
	str	r1, [r5, #148]
	mov	r2, #8
	bl	FADE_Active
	ldr	r0, [r4, r7, asl #2]
.L247:
	cmp	r0, #0
	bne	.L250
	ldr	r3, [r4, r6, asl #2]
	ldr	r2, [r3, #8]
	tst	r2, #8
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r3, #8]
	mov	r1, #1
	bfi	r2, r1, #4, #4
	str	r2, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L257:
	ldr	r0, [r4, r7, asl #2]
	bl	AIPDestroyChn
	mov	r0, r6
.L254:
	bl	AIPCreateChn
	str	r0, [r4, r7, asl #2]
	b	.L247
.L259:
	.align	2
.L258:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPStartChnCmdProc, .-AIPStartChnCmdProc
	.align	2
	.global	AIP_Init
	.type	AIP_Init, %function
AIP_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L263
	mov	r4, r0
	ldr	r8, .L263+4
	mov	r7, #0
	add	r6, r5, #32
.L261:
	str	r4, [r5, #4]!
	mov	r2, #96
	ldr	r3, [r8, #20]
	mov	r1, #0
	mov	r0, r4
	blx	r3
	ldr	r3, [r4, #8]
	mov	r1, #121
	cmp	r5, r6
	orr	r3, r3, #8
	str	r3, [r4, #8]
	ldr	r3, [r4, #8]
	mov	r2, #3
	bfi	r3, r1, #8, #7
	str	r3, [r4, #8]
	ldr	r3, [r4]
	bfi	r3, r2, #11, #3
	str	r3, [r4], #96
	str	r7, [r5, #32]
	bne	.L261
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L264:
	.align	2
.L263:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIP_Init, .-AIP_Init
	.align	2
	.global	AIP_DeInit
	.type	AIP_DeInit, %function
AIP_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L268
	mov	r6, #0
	add	r5, r4, #32
.L266:
	ldr	r0, [r4, #4]!
	bl	AIPDestroyChn
	cmp	r4, r5
	str	r6, [r4]
	bne	.L266
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L269:
	.align	2
.L268:
	.word	.LANCHOR0+28
	UNWIND(.fnend)
	.size	AIP_DeInit, .-AIP_DeInit
	.align	2
	.global	AIP_Process
	.type	AIP_Process, %function
AIP_Process:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #108)
	sub	sp, sp, #108
	ldr	r6, .L406
	ldr	r10, .L406+4
	movw	r7, #19923
	movt	r7, 4194
	mov	r5, #0
.L327:
	sub	r1, fp, #80
	mov	r0, r5
	bl	AIPGetChnCmd
	cmp	r0, #4
	beq	.L271
	ldr	r3, [fp, #-80]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L271
.L273:
	.word	.L272
	.word	.L274
	.word	.L275
	.word	.L276
.L276:
	mov	r0, r5
	bl	AIFlushChnCmdProc
.L271:
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	beq	.L277
	ldr	r3, [r4, #148]
	cmp	r3, #1
	beq	.L394
.L277:
	add	r5, r5, #1
	cmp	r5, #8
	bne	.L327
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L275:
	mov	r0, r5
	bl	AIPPauseChnCmdProc
	b	.L271
.L272:
	mov	r0, r5
	bl	AIPStartChnCmdProc
	b	.L271
.L274:
	mov	r0, r5
	bl	AIPStopChnCmdProc
	b	.L271
.L394:
	ldr	r2, [r4, #28]
	cmp	r2, #0
	bne	.L277
	ldr	r3, [r6, #-32]
	str	r2, [r4, #152]
	ldr	r2, [r3, #48]
	uxtb	r2, r2
	str	r2, [r4, #156]
	ldr	r2, [r3, #48]
	ubfx	r2, r2, #8, #8
	str	r2, [r4, #160]
	ldr	r2, [r3, #76]
	uxtb	r2, r2
	str	r2, [r4, #172]
	ldr	r2, [r3, #76]
	tst	r2, #2048
	ldr	r2, [r3, #76]
	ubfxeq	r2, r2, #8, #3
	streq	r2, [r4, #176]
	beq	.L279
	tst	r2, #2048
	ldrne	r2, [r3, #76]
	ubfxne	r2, r2, #8, #3
	rsbne	r2, r2, #0
	strne	r2, [r4, #176]
.L279:
	ldr	r2, [r3, #48]
	ubfx	r2, r2, #16, #1
	str	r2, [r4, #180]
	ldr	r2, [r3, #48]
	ubfx	r2, r2, #17, #3
	str	r2, [r4, #184]
	ldr	r2, [r3, #48]
	ubfx	r2, r2, #23, #2
	str	r2, [r4, #188]
	cmp	r2, #1
	ldrne	r2, [r3, #48]
	moveq	r2, #256
	movne	r2, r2, lsr #25
	rsbne	r2, r2, #0
	str	r2, [r4, #284]
	ldr	r2, [r3, #48]
	ubfx	r2, r2, #20, #3
	str	r2, [r4, #288]
	ldr	r2, [r3, #8]
	tst	r2, #1610612736
	ldr	r2, [r3, #8]
	ubfxeq	r2, r2, #24, #5
	streq	r2, [r4, #204]
	beq	.L283
	ubfx	r2, r2, #29, #2
	cmp	r2, #1
	ldreq	r2, [r3, #8]
	ubfxeq	r2, r2, #24, #5
	rsbeq	r2, r2, #0
	streq	r2, [r4, #204]
.L283:
	ldr	r2, [r3]
	ubfx	r2, r2, #14, #1
	str	r2, [r4, #4]
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #22, #1
	str	r2, [r4, #244]
	ldr	r1, [r3, #76]
	cmp	r2, #1
	ubfx	r2, r1, #24, #1
	str	r2, [r4, #248]
	ldr	r0, [r3, #76]
	ubfx	r0, r0, #12, #4
	str	r0, [r4, #252]
	ldr	r3, [r3, #76]
	ubfx	r3, r3, #16, #8
	str	r3, [r4, #256]
	beq	.L326
	cmp	r2, #0
	ldr	r3, [r4, #260]
	bne	.L285
	cmp	r3, #1
	streq	r2, [r4, #260]
.L295:
	ldr	r9, [r4, #208]
	ldr	r1, [r4, #220]
	ldr	r8, [r4, #216]
	mul	r3, r9, r1
	cmp	r3, r8
	bcc	.L296
	ldr	r0, [r4, #128]
	cmp	r0, #0
	beq	.L326
	mov	r1, r8
	bl	RBUF_CheckFree
	cmp	r0, #0
	beq	.L326
	cmp	r8, #0
	beq	.L326
	ldr	r2, [r4, #216]
	ldr	r1, [r4, #212]
	ldr	r0, [r4, #128]
	bl	RBUF_WriteData
	ldr	r1, [r4, #220]
	ldr	r0, [r4, #216]
	bl	__aeabi_uidiv
	ldr	r3, [r4, #208]
	rsb	r0, r0, r3
	str	r0, [r4, #208]
.L326:
	ldr	r4, [r6]
	ldr	r8, [r6, #-32]
	ldr	r0, [r4, #128]
	bl	RBUF_QueryBusy
	ldr	r2, [r4, #76]
	ldr	r1, [r4, #220]
	bl	UTIL_LatencyMs
	ldr	r3, [r8, #4]
	bfi	r3, r0, #16, #6
	str	r3, [r8, #4]
	b	.L277
.L285:
	cmp	r3, #0
	beq	.L288
	ldr	r3, [r4, #264]
.L289:
	ldr	r8, [r4, #216]
	str	r3, [fp, #-112]
	mov	r1, r8
	bl	AOP_QueryRbfFree
	cmp	r0, #0
	beq	.L295
	ldr	r0, [r4, #124]
	sub	r1, fp, #112
	bl	RBUF_QueryBusy_ProvideRptr
	cmp	r8, r0
	bhi	.L295
	bl	AOE_GetWKBuf
	ldr	r1, [r4, #224]
	str	r8, [fp, #-104]
	mov	r9, r0
	mov	r0, r8
	str	r9, [fp, #-108]
	bl	__aeabi_uidiv
	ldr	ip, [r4, #20]
	mov	r1, r9
	ldr	lr, [r4, #28]
	sub	r3, fp, #112
	ldr	r9, [r4, #24]
	mov	r2, r8
	str	ip, [fp, #-92]
	sub	r8, fp, #108
	ldr	ip, [r4, #16]
	str	r9, [fp, #-88]
	str	lr, [fp, #-84]
	str	ip, [fp, #-96]
	str	r0, [fp, #-100]
	ldr	r0, [r4, #124]
	bl	RBUF_ReadDataDma
	ldr	r3, [r4, #188]
	cmp	r3, #1
	beq	.L395
.L292:
	mov	r1, r8
	mov	r0, r4
	bl	AIPGainPcmData
	ldr	r1, [r4, #184]
	ldr	r2, [r4, #68]
	sub	r3, r1, #1
	cmp	r3, #6
	bls	.L396
.L293:
	ldr	r3, [r4, #180]
	cmp	r3, #1
	beq	.L397
.L294:
	mov	r1, r8
	ldr	r0, [r4, #252]
	bl	AOP_WriteRbfData
	ldr	r3, [fp, #-112]
	str	r3, [r4, #264]
	b	.L295
.L296:
	ldr	r3, [r4, #28]
	ldr	r2, [r4, #76]
	cmp	r3, #0
	ldr	ip, [r4, #72]
	ldr	r3, [r4, #68]
	movne	r9, r8
	beq	.L398
.L299:
	ldr	r0, [r4, #124]
	bl	RBUF_QueryBusy
	cmp	r0, r9
	bcc	.L326
	cmp	r9, #0
	beq	.L326
	ldr	r0, [r4, #128]
	cmp	r0, #0
	beq	.L326
	mov	r1, r8
	bl	RBUF_CheckFree
	cmp	r0, #0
	beq	.L326
	cmp	r8, #0
	beq	.L326
	bl	AOE_GetWKBuf
	ldr	r1, [r4, #224]
	str	r9, [fp, #-104]
	mov	r8, r0
	mov	r0, r9
	str	r8, [fp, #-108]
	bl	__aeabi_uidiv
	ldr	r3, [r4, #20]
	mov	r1, r8
	ldr	lr, [r4, #28]
	mov	r2, r9
	ldr	r8, [r4, #24]
	str	r3, [fp, #-92]
	mov	r3, #0
	ldr	ip, [r4, #16]
	str	r8, [fp, #-88]
	str	lr, [fp, #-84]
	str	ip, [fp, #-96]
	str	r0, [fp, #-100]
	ldr	r0, [r4, #124]
	bl	RBUF_ReadDataDma
	ldr	r3, [r4, #28]
	cmp	r3, #0
	beq	.L399
.L306:
	ldr	r3, [r4, #180]
	cmp	r3, #1
	beq	.L400
.L321:
	ldr	r2, [r4, #220]
	ldr	r3, [r4, #208]
	ldr	r8, [r4, #216]
	mul	r2, r3, r2
	cmp	r2, #0
	bne	.L401
.L322:
	cmp	r8, #0
	ldr	r3, [fp, #-104]
	beq	.L324
	cmp	r8, r3
	movcs	r8, r3
	cmp	r8, #0
	beq	.L324
	mov	r2, r8
	ldr	r1, [fp, #-108]
	ldr	r0, [r4, #128]
	bl	RBUF_WriteData
	ldr	r3, [fp, #-104]
.L324:
	subs	r9, r3, r8
	beq	.L325
	ldr	r1, [fp, #-108]
	mov	r2, r9
	ldr	r3, [r10, #24]
	add	r1, r1, r8
	ldr	r0, [r4, #212]
	blx	r3
.L325:
	mov	r0, r9
	ldr	r1, [r4, #220]
	bl	__aeabi_uidiv
	str	r0, [r4, #208]
	b	.L326
.L398:
	mov	r0, r8
	str	r3, [fp, #-128]
	str	ip, [fp, #-124]
	str	r2, [fp, #-120]
	bl	__aeabi_uidiv
	ldr	lr, [r4, #132]
	ldr	ip, [fp, #-124]
	ldr	r2, [fp, #-120]
	ldr	r3, [fp, #-128]
	str	ip, [sp]
	mov	r1, r2
	rsb	r9, r9, r0
	mov	r0, lr
	bl	LSRC_UpdateChange
	ldr	r1, [r4, #204]
	ldr	r0, [r4, #132]
	bl	LSRC_SetSpeedAdjust
	mov	r1, r9
	ldr	r0, [r4, #132]
	bl	LSRC_GetMinInputNum
	ldr	r3, [r4, #136]
	cmp	r3, #0
	beq	.L300
	ldr	r2, [r4, #236]
	cmp	r2, #2
	beq	.L402
	mov	r1, r0
	mov	r0, r3
	bl	ResamplerGetMinInputNum
.L300:
	tst	r0, #3
	bicne	r0, r0, #3
	addne	r0, r0, #4
.L302:
	ldr	r9, [r4, #224]
	mul	r9, r9, r0
	b	.L299
.L288:
	ldr	r1, [r4, #68]
	ldr	r0, [r4, #72]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r4, #256]
	ldr	r2, [r4, #24]
	sub	r1, fp, #80
	mul	r2, r3, r2
	mul	r2, r0, r2
	ldr	r0, [r4, #124]
	umull	r2, r3, r2, r7
	mov	r8, r3, lsr #6
	bl	RBUF_QueryInfo
	ldr	r1, [fp, #-52]
	ldr	r2, [fp, #-76]
	cmp	r8, r1
	ldr	r0, [fp, #-68]
	movcs	r8, r1
	add	r3, r8, r2
	cmp	r3, r0
	rsbcs	r3, r0, r2
	mov	r2, #1
	addcs	r3, r3, r8
	ldr	r0, [r4, #252]
	str	r3, [r4, #264]
	str	r2, [r4, #260]
	b	.L289
.L402:
	ldr	r3, [r4, #24]
	ldr	r1, [r4, #76]
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	cmp	r0, #0
	addne	r0, r0, #1
	bne	.L300
	b	.L302
.L399:
	ldr	r3, [r4, #72]
	ldr	r2, [fp, #-92]
	ldr	r9, [r4, #68]
	cmp	r3, r2
	subeq	r8, fp, #108
	beq	.L308
	str	r3, [fp, #-120]
	bls	.L309
	bl	AOE_GetWKBuf
	ldr	r3, [fp, #-120]
	sub	r8, fp, #108
	mov	r2, r8
	mov	r1, r0
	mov	r0, r3
	bl	UTIL_UpmixPcmData
.L308:
	ldr	r3, [fp, #-96]
	cmp	r9, r3
	beq	.L310
	bl	AOE_GetWKBuf
	mov	r2, r8
	mov	r1, r0
	mov	r0, r9
	bl	UTIL_UnifyBitDepthPcmData
.L310:
	ldr	r3, [r4, #136]
	ldr	r9, [r4, #76]
	cmp	r3, #0
	beq	.L314
	bl	AOE_GetWKBuf
	ldr	r3, [r4, #236]
	cmp	r3, #2
	beq	.L403
	ldr	lr, [fp, #-88]
	mov	r2, r0
	mov	ip, #1
	ldr	r3, [fp, #-100]
	str	r0, [fp, #-120]
	ldr	r1, [fp, #-108]
	ldr	r0, [r4, #136]
	stmib	sp, {r9, ip}
	str	lr, [sp]
	bl	ResamplerProcessFrame
	ldr	r3, [fp, #-92]
	ldr	ip, [fp, #-120]
	mov	r2, r0
.L313:
	mov	r0, r3
	ldr	r1, [fp, #-96]
	str	ip, [fp, #-108]
	str	r2, [fp, #-100]
	str	r9, [fp, #-88]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-100]
	mul	r0, r3, r0
	str	r0, [fp, #-104]
.L314:
	ldr	r0, [r4, #132]
	ldr	r3, [r4, #232]
	ldr	r2, .L406+8
	cmp	r0, #0
	ldr	r9, [r2, r3, asl #2]
	beq	.L316
	bl	LSRC_CheckDoSRC
	cmp	r0, #0
	beq	.L316
	ldr	r3, [fp, #-100]
	str	r3, [fp, #-120]
	bl	AOE_GetWKBuf
	ldr	r3, [fp, #-120]
	ldr	r1, [fp, #-108]
	mov	r2, r0
	str	r0, [fp, #-120]
	ldr	r0, [r4, #132]
	bl	LSRC_ProcessFrame
	ldr	ip, [fp, #-120]
	ldr	r1, [fp, #-96]
	str	ip, [fp, #-108]
	str	r0, [fp, #-100]
	ldr	r0, [fp, #-92]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-100]
	ldr	r2, [r9, #80]
	add	r2, r2, #1
	str	r2, [r9, #80]
	mul	r0, r3, r0
	str	r0, [fp, #-104]
.L316:
	ldr	r3, [r4, #188]
	cmp	r3, #1
	beq	.L404
.L318:
	mov	r1, r8
	mov	r0, r4
	bl	AIPGainPcmData
	ldr	r1, [r4, #184]
	ldr	r2, [r4, #68]
	sub	r3, r1, #1
	cmp	r3, #6
	bls	.L405
.L319:
	ldr	r0, [r4, #140]
	cmp	r0, #0
	beq	.L306
	ldr	r2, [fp, #-96]
	ldr	r1, [fp, #-88]
	ldr	r3, [fp, #-92]
	bl	FADE_Flush
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [r4, #140]
	bl	FADE_InProcess
	b	.L306
.L401:
	ldr	r1, [r4, #212]
	rsb	r8, r2, r8
	ldr	r0, [r4, #128]
	bl	RBUF_WriteData
	b	.L322
.L400:
	ldr	r3, [r10, #20]
	mov	r1, #0
	ldr	r2, [fp, #-104]
	ldr	r0, [fp, #-108]
	blx	r3
	b	.L321
.L309:
	bl	AOE_GetWKBuf
	ldr	r3, [fp, #-120]
	sub	r8, fp, #108
	mov	r2, r8
	mov	r1, r0
	mov	r0, r3
	bl	UTIL_DownmixPcmData
	b	.L308
.L403:
	ldr	r1, [fp, #-92]
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-108]
	str	r0, [fp, #-76]
	mul	r3, r3, r1
	str	r2, [fp, #-80]
	ldr	r2, [r10, #32]
	str	r0, [fp, #-124]
	str	r3, [fp, #-72]
	blx	r2
	sub	r1, fp, #80
	ldr	r0, [r4, #136]
	bl	iMedia_ASRC_Apply
	ldr	r3, [r10, #36]
	blx	r3
	ldr	r3, [fp, #-92]
	ldr	r0, [fp, #-68]
	mov	r1, r3
	str	r3, [fp, #-120]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-120]
	ldr	ip, [fp, #-124]
	mov	r2, r0
	b	.L313
.L397:
	ldr	r3, [r10, #20]
	mov	r1, #0
	ldr	r2, [fp, #-104]
	ldr	r0, [fp, #-108]
	blx	r3
	b	.L294
.L405:
	mov	r0, r8
	bl	UTIL_ChannelModeProcess
	b	.L319
.L404:
	add	r1, r4, #268
	mov	r0, r8
	bl	UTIL_DRE_16BIT_Process
	b	.L318
.L396:
	mov	r0, r8
	bl	UTIL_ChannelModeProcess
	b	.L293
.L395:
	add	r1, r4, #268
	mov	r0, r8
	bl	UTIL_DRE_16BIT_Process
	b	.L292
.L407:
	.align	2
.L406:
	.word	.LANCHOR0+28
	.word	g_AdspOsalFunc
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_Process, .-AIP_Process
	.align	2
	.global	AIP_GetChnStatus
	.type	AIP_GetChnStatus, %function
AIP_GetChnStatus:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L411
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	streq	r3, [r1]
	ldrne	r2, [r3, #148]
	strne	r2, [r1]
	ldrne	r2, [r3, #4]
	strne	r2, [r1, #4]
	ldrne	r3, [r3, #240]
	strne	r3, [r1, #8]
	ldmfd	sp, {fp, sp, pc}
.L412:
	.align	2
.L411:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetChnStatus, .-AIP_GetChnStatus
	.align	2
	.global	AIP_FlushCutoffFlag
	.type	AIP_FlushCutoffFlag, %function
AIP_FlushCutoffFlag:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L418
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	movne	r2, #0
	strne	r2, [r3, #240]
	ldmfd	sp, {fp, sp, pc}
.L419:
	.align	2
.L418:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_FlushCutoffFlag, .-AIP_FlushCutoffFlag
	.align	2
	.global	AIP_QueryFiFoInfo
	.type	AIP_QueryFiFoInfo, %function
AIP_QueryFiFoInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L427
	add	r2, r0, #8
	mov	r0, r1
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	beq	.L424
	ldr	r2, [r3, #244]
	cmp	r2, #0
	beq	.L425
	ldr	r2, [r3, #148]
	cmp	r2, #1
	beq	.L426
	ldr	r3, .L427+4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #20]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L425:
	ldr	r0, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryInfo
.L426:
	ldr	r0, [r3, #124]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryInfo
.L424:
	ldr	ip, .L427+4
	mov	r1, r3
	mov	r2, #36
	ldr	r3, [ip, #20]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L428:
	.align	2
.L427:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIP_QueryFiFoInfo, .-AIP_QueryFiFoInfo
	.align	2
	.global	AIP_QueryFiFoBusy
	.type	AIP_QueryFiFoBusy, %function
AIP_QueryFiFoBusy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L433
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #244]
	cmp	r3, #0
	beq	.L432
	ldr	r0, [r0, #124]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L432:
	ldr	r0, [r0, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L434:
	.align	2
.L433:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_QueryFiFoBusy, .-AIP_QueryFiFoBusy
	.align	2
	.global	AIP_QueryBusy
	.type	AIP_QueryBusy, %function
AIP_QueryBusy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L441
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L436
	ldr	r0, [r3, #124]
	cmp	r0, #0
	beq	.L436
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L436:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L442:
	.align	2
.L441:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_QueryBusy, .-AIP_QueryBusy
	.align	2
	.global	AIP_ReadDataComplete
	.type	AIP_ReadDataComplete, %function
AIP_ReadDataComplete:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L450
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	ldr	r5, [r3, r0, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #244]
	cmp	r3, #0
	beq	.L449
	ldr	r0, [r4, #124]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	RBUF_ReadDataComplete
.L449:
	ldr	r0, [r4, #128]
	bl	RBUF_ReadDataComplete
	ldr	r0, [r4, #128]
	bl	RBUF_QueryBusy
	ldr	r2, [r4, #76]
	ldr	r1, [r4, #220]
	bl	UTIL_LatencyMs
	ldr	r3, [r5, #4]
	bfi	r3, r0, #16, #6
	str	r3, [r5, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L451:
	.align	2
.L450:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_ReadDataComplete, .-AIP_ReadDataComplete
	.align	2
	.global	AIP_UnderFlowCalc
	.type	AIP_UnderFlowCalc, %function
AIP_UnderFlowCalc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L457
	add	r2, r0, #8
	ldr	r1, [r3, r2, asl #2]
	ldr	r2, [r3, r0, asl #2]
	cmp	r1, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r2, #64]
	ldr	r1, [r2, #64]
	mov	r3, r3, lsr #16
	add	r3, r3, #1
	uxth	r3, r3
	bfi	r1, r3, #16, #16
	str	r1, [r2, #64]
	ldmfd	sp, {fp, sp, pc}
.L458:
	.align	2
.L457:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_UnderFlowCalc, .-AIP_UnderFlowCalc
	.align	2
	.global	AIP_GetRingIn
	.type	AIP_GetRingIn, %function
AIP_GetRingIn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L462
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #124]
	ldmfd	sp, {fp, sp, pc}
.L463:
	.align	2
.L462:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetRingIn, .-AIP_GetRingIn
	.align	2
	.global	AIP_GetCompressInfo
	.type	AIP_GetCompressInfo, %function
AIP_GetCompressInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L468
	add	r0, r0, #8
	mov	lr, r1
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	streq	r3, [r1]
	streq	r3, [r2]
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [r3, #124]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_GetCompressInfo
.L469:
	.align	2
.L468:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetCompressInfo, .-AIP_GetCompressInfo
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stAipRm, %object
	.size	g_stAipRm, 64
g_stAipRm:
	.space	64
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
