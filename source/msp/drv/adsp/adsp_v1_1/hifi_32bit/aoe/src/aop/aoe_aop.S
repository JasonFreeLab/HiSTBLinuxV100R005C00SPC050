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
	.file	"aoe_aop.c"
	.text
	.align	2
	.type	AOPCalcSize, %function
AOPCalcSize:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r5, r0
	ldr	r1, [r1]
	ldr	r0, [r4, #4]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r4, #8]
	movw	r1, #19923
	movt	r1, 4194
	mul	r3, r3, r5
	umull	r2, r3, r3, r1
	mov	r3, r3, lsr #6
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
	mul	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AOPCalcSize, .-AOPCalcSize
	.align	2
	.global	AOP_Flush
	.type	AOP_Flush, %function
AOP_Flush:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AOP_Flush, .-AOP_Flush
	.align	2
	.global	AOPFlushChnBuf
	.type	AOPFlushChnBuf, %function
AOPFlushChnBuf:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #112]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AOPFlushChnBuf, .-AOPFlushChnBuf
	.align	2
	.global	AOP_ProcDelayCompensation
	.type	AOP_ProcDelayCompensation, %function
AOP_ProcDelayCompensation:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	r3, .L31
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	cmp	r4, #0
	beq	.L10
	ldr	r2, [r4, #116]
	cmp	r2, #0
	beq	.L10
	ldr	r2, [r4, #128]
	cmp	r2, #1
	beq	.L29
	ldr	r5, [r4, #120]
	ldr	r7, [r3, r0, asl #2]
	cmp	r5, #9
	bhi	.L30
.L10:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L30:
	add	r6, r4, #48
	sub	r1, fp, #64
	ldr	r0, [r4, #112]
	bl	RBUF_QueryInfo
	mov	r1, r6
	mov	r0, r5
	mov	r5, r6
	bl	AOPCalcSize
	mov	r1, r5
	mov	r6, r0
	mov	r0, #10
	bl	AOPCalcSize
	ldr	r2, [fp, #-44]
	cmp	r6, r2
	bcc	.L10
	add	r6, r6, r0
	subs	r2, r6, r2
	beq	.L10
	ldr	r3, [fp, #-36]
	mov	r1, #0
	ldr	r0, [r4, #112]
	cmp	r2, r3
	movcs	r2, r3
	bl	RBUF_WriteData
	ldr	r3, [r7, #100]
	add	r3, r3, #1
	str	r3, [r7, #100]
	b	.L10
.L29:
	ldr	r5, [r3, r0, asl #2]
	mov	r3, #0
	str	r3, [fp, #-64]
	sub	r1, fp, #64
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	str	r3, [fp, #-36]
	str	r3, [fp, #-32]
	ldr	r3, [r5, #4]
	orr	r3, r3, #1048576
	str	r3, [r5, #4]
	ldr	r0, [r4, #112]
	bl	RBUF_QueryInfo
	ldr	r0, [r4, #112]
	cmp	r0, #0
	beq	.L13
	bl	RBUF_Flush
.L13:
	add	r6, r4, #48
	ldr	r0, [r4, #124]
	mov	r1, r6
	bl	AOPCalcSize
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #120]
	bl	AOPCalcSize
	ldr	r3, [fp, #-44]
	mov	r1, #0
	cmp	r7, r3
	mov	r2, r0
	addls	r2, r0, r3
	ldr	r3, [fp, #-36]
	rsbls	r2, r7, r2
	ldr	r0, [r4, #112]
	cmp	r2, r3
	movcs	r2, r3
	bl	RBUF_WriteData
	ldr	r3, [r5, #100]
	mov	r2, #0
	add	r3, r3, #1
	str	r3, [r5, #100]
	ldr	r3, [r4, #120]
	str	r2, [r4, #128]
	str	r3, [r4, #124]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L32:
	.align	2
.L31:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_ProcDelayCompensation, .-AOP_ProcDelayCompensation
	.align	2
	.global	AOP_DestroyChn
	.type	AOP_DestroyChn, %function
AOP_DestroyChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L37
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #108]
	cmp	r3, #1
	beq	.L36
.L35:
	ldr	r0, [r4, #112]
	bl	RBUF_Destroy
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
.L36:
	bl	CAST_Destroy
	b	.L35
.L38:
	.align	2
.L37:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_DestroyChn, .-AOP_DestroyChn
	.align	2
	.global	AOP_Init
	.type	AOP_Init, %function
AOP_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L42
	mov	r8, r0
	ldr	r9, .L42+4
	mov	r4, r0
	add	r7, r5, #32
	mov	r6, #0
.L40:
	str	r4, [r5, #4]!
	mov	r0, r4
	ldr	r3, [r9, #20]
	mov	r2, #128
	mov	r1, #0
	add	r4, r4, #128
	blx	r3
	ldr	r3, [r4, #-124]
	cmp	r5, r7
	orr	r3, r3, #4
	str	r3, [r4, #-124]
	str	r6, [r5, #32]
	bne	.L40
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	CAST_Init
.L43:
	.align	2
.L42:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_Init, .-AOP_Init
	.align	2
	.global	AOP_DeInit
	.type	AOP_DeInit, %function
AOP_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L47
	mov	r4, #0
	mov	r6, r4
.L45:
	mov	r0, r4
	add	r4, r4, #1
	bl	AOP_DestroyChn
	cmp	r4, #8
	str	r6, [r5, #4]!
	bne	.L45
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	CAST_DeInit
.L48:
	.align	2
.L47:
	.word	.LANCHOR0+28
	UNWIND(.fnend)
	.size	AOP_DeInit, .-AOP_DeInit
	.align	2
	.global	AOP_Process
	.type	AOP_Process, %function
AOP_Process:
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
	ldr	r7, .L97
	mov	r6, #0
	ldr	r9, .L97+4
	mov	r8, r6
	add	r5, r7, #36
	b	.L74
.L68:
	add	r6, r6, #1
	add	r5, r5, #4
	cmp	r6, #8
	beq	.L94
.L74:
	ldr	r4, [r7, #4]!
	ldr	r10, [r4, #4]
	ubfx	r10, r10, #2, #1
	cmp	r10, #0
	bne	.L66
	ldr	r3, [r4, #4]
	ands	r3, r3, #3
	beq	.L52
	cmp	r3, #1
	beq	.L53
	ldr	r3, [r4, #4]
	mov	r2, #4
	bfi	r3, r2, #3, #4
	str	r3, [r4, #4]
	ldr	r3, [r4, #4]
	orr	r3, r3, r2
	str	r3, [r4, #4]
.L66:
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L68
.L67:
	ldr	r3, [r4, #116]
	cmp	r3, #1
	bne	.L68
	ldr	r10, [r7]
	add	r6, r6, #1
	str	r8, [r4, #20]
	add	r5, r5, #4
	ldr	r1, [r4, #48]
	ldr	r3, [r10, #12]
	ldr	r0, [r4, #52]
	uxtb	r3, r3
	str	r3, [r4, #24]
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #8, #8
	str	r3, [r4, #28]
	ldr	r3, [r10, #12]
	tst	r3, #524288
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #16, #3
	rsbne	r3, r3, #0
	str	r3, [r4, #32]
	str	r3, [r4, #36]
	ldr	r3, [r10, #12]
	tst	r3, #1073741824
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #24, #6
	rsbne	r3, r3, #0
	str	r3, [r4, #40]
	ldr	r3, [r10, #12]
	mov	r3, r3, lsr #31
	str	r3, [r4, #44]
	ldr	r3, [r10, #4]
	ubfx	r3, r3, #8, #1
	str	r3, [r4, #104]
	ldr	r3, [r10]
	mov	r3, r3, lsr #20
	str	r3, [r4, #100]
	str	r3, [fp, #-120]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-120]
	ldr	r2, [r4, #56]
	mov	r1, r0
	mov	r0, r3
	bl	UTIL_LatencyMs2ByteSize
	add	r1, r4, #68
	str	r0, [r4, #96]
	ldr	r0, [r4, #112]
	bl	RBUF_UpdateAttr
	ldr	r3, [r10, #4]
	ldr	r2, [r4, #124]
	ubfx	r3, r3, #21, #9
	str	r3, [r4, #120]
	cmp	r3, r2
	movne	r3, #1
	strne	r3, [r4, #128]
	cmp	r6, #8
	bne	.L74
.L94:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L53:
	mov	r0, r6
	bl	AOP_DestroyChn
	str	r10, [r5]
	ldr	r3, [r7]
.L65:
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L68
.L62:
	ldr	r2, [r3, #4]
	bfc	r2, #3, #4
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L66
.L52:
	str	r3, [fp, #-116]
	sub	r0, fp, #100
	ldr	r1, [r4]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L57
	ldr	r1, [r4]
	sub	r0, fp, #96
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L57
	ldr	r1, [r4]
	sub	r0, fp, #92
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L57
	ldr	r1, [r4]
	sub	r0, fp, #88
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	cmp	r0, #0
	bne	.L57
	ldr	r1, [r4]
	sub	r0, fp, #112
	mov	r1, r1, lsr #20
	bl	AOE_REG_ReadBufLatencyMs
	subs	r10, r0, #0
	bne	.L57
	ldr	r3, [r4]
	ldr	r1, [fp, #-100]
	ldr	r0, [fp, #-96]
	ubfx	r3, r3, #10, #1
	str	r3, [fp, #-84]
	bl	UTIL_CalcFrameSize
	mov	r3, #1
	str	r3, [fp, #-80]
	ldr	r3, [r4, #24]
	str	r10, [fp, #-108]
	ubfx	r3, r3, #24, #1
	str	r10, [fp, #-104]
	str	r3, [fp, #-60]
	cmp	r3, #0
	ldr	r3, [r4, #16]
	str	r3, [fp, #-108]
	ldr	r2, [fp, #-108]
	ldr	r3, [r4, #20]
	str	r2, [fp, #-76]
	str	r3, [fp, #-104]
	ldr	r3, [r4, #24]
	bic	r3, r3, #-16777216
	str	r3, [fp, #-72]
	beq	.L55
	str	r10, [fp, #-108]
	str	r10, [fp, #-104]
	ldr	r3, [r4, #28]
	str	r3, [fp, #-108]
	ldr	r3, [r4, #32]
	ldr	r2, [fp, #-108]
	str	r3, [fp, #-104]
	str	r10, [fp, #-108]
	str	r10, [fp, #-104]
	ldr	r3, [r4, #36]
	str	r2, [fp, #-68]
	str	r3, [fp, #-108]
	ldr	r2, [fp, #-108]
	ldr	r3, [r4, #40]
	str	r2, [fp, #-64]
	str	r3, [fp, #-104]
.L56:
	ldr	r3, [fp, #-112]
	mov	r1, r0
	ldr	r2, [fp, #-92]
	str	r0, [fp, #-56]
	mov	r0, r3
	str	r3, [fp, #-48]
	bl	UTIL_LatencyMs2ByteSize
	sub	r1, fp, #80
	str	r0, [fp, #-52]
	sub	r0, fp, #116
	bl	RBUF_Create
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	beq	.L57
	mov	r1, #132
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L58
	ldr	r3, [r9, #20]
	mov	r2, #132
	mov	r1, #0
	blx	r3
	ldr	r3, [r9, #24]
	mov	r2, #56
	sub	r1, fp, #100
	add	r0, r4, #48
	blx	r3
	ldr	r3, [fp, #-116]
	str	r3, [r4, #112]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #524288
	bne	.L95
.L59:
	str	r8, [r4, #108]
.L76:
	mov	r3, #121
	str	r8, [r4, #20]
	str	r8, [r4, #32]
	mov	r2, #1
	str	r8, [r4, #36]
	str	r8, [r4]
	str	r8, [r4, #12]
	str	r8, [r4, #16]
	str	r8, [r4, #124]
	str	r8, [r4, #120]
	str	r3, [r4, #24]
	str	r3, [r4, #28]
	str	r3, [r4, #4]
	str	r3, [r4, #8]
	str	r2, [r4, #116]
	str	r4, [r5]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L62
	b	.L67
.L96:
.L63:
.L64:
	mov	r1, r4
	mov	r0, #26
	bl	HI_ADSP_FREE
.L58:
	ldr	r0, [fp, #-116]
	bl	RBUF_Destroy
.L57:
	str	r8, [r5]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L65
	ldr	r2, [r3, #4]
	mov	r1, #1
	bfi	r2, r1, #3, #4
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L62
	b	.L66
.L55:
	add	r3, r4, #28
	add	r4, r4, #36
	str	r3, [fp, #-68]
	str	r4, [fp, #-64]
	b	.L56
.L95:
	ldr	ip, [r3, #4]
	ubfx	ip, ip, #18, #1
	cmp	ip, #1
	bne	.L59
	ldr	lr, [r4, #56]
	add	r1, r4, #68
	ldr	r3, [r4, #52]
	mov	r0, r6
	ldr	r2, [r4, #48]
	str	ip, [r4, #108]
	str	lr, [sp]
	bl	CAST_Create
	subs	r10, r0, #0
	beq	.L96
	ldr	r1, [r4, #112]
	mov	r0, r6
	bl	CAST_SetAopBuf
	str	r10, [r4, #112]
	b	.L76
.L98:
	.align	2
.L97:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_Process, .-AOP_Process
	.align	2
	.global	AOP_GetChnStatus
	.type	AOP_GetChnStatus, %function
AOP_GetChnStatus:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L102
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	streq	r3, [r1]
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #116]
	str	r2, [r1]
	ldr	r2, [r3, #64]
	str	r2, [r1, #4]
	ldr	r2, [r3, #92]
	str	r2, [r1, #16]
	ldr	r2, [r3, #48]
	str	r2, [r1, #8]
	ldr	r2, [r3, #52]
	str	r2, [r1, #12]
	ldr	r2, [r3, #104]
	str	r2, [r1, #20]
	ldr	r2, [r3, #108]
	str	r2, [r1, #24]
	ldr	r3, [r3, #120]
	str	r3, [r1, #28]
	ldmfd	sp, {fp, sp, pc}
.L103:
	.align	2
.L102:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_GetChnStatus, .-AOP_GetChnStatus
	.align	2
	.global	AOP_QueryRbfFree
	.type	AOP_QueryRbfFree, %function
AOP_QueryRbfFree:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L112
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L105
	ldr	r2, [r3, #116]
	cmp	r2, #0
	beq	.L105
	ldr	r0, [r3, #112]
	cmp	r0, #0
	beq	.L105
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_CheckFree
.L105:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L113:
	.align	2
.L112:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_QueryRbfFree, .-AOP_QueryRbfFree
	.align	2
	.global	AOP_WriteBuffProcTryCnt
	.type	AOP_WriteBuffProcTryCnt, %function
AOP_WriteBuffProcTryCnt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L119
	add	r2, r0, #8
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r3, #108]
	cmp	r3, #1
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CAST_FiFoTryCnt
.L120:
	.align	2
.L119:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_WriteBuffProcTryCnt, .-AOP_WriteBuffProcTryCnt
	.align	2
	.global	AOP_WriteBuffProcOKCnt
	.type	AOP_WriteBuffProcOKCnt, %function
AOP_WriteBuffProcOKCnt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L126
	add	r2, r0, #8
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r3, #108]
	cmp	r3, #1
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CAST_FiFoFreeCnt
.L127:
	.align	2
.L126:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_WriteBuffProcOKCnt, .-AOP_WriteBuffProcOKCnt
	.align	2
	.global	AOP_WriteRbfData
	.type	AOP_WriteRbfData, %function
AOP_WriteRbfData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L158
	add	r0, r0, #8
	mov	r5, r1
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L129
	ldr	r3, [r4, #116]
	cmp	r3, #0
	beq	.L129
	ldr	r3, [r1, #24]
	cmp	r3, #0
	beq	.L154
.L131:
	ldr	r3, [r4, #108]
	ldr	r0, [r4, #112]
	cmp	r3, #1
	ldmia	r5, {r1, r2}
	beq	.L155
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	RBUF_WriteDataDma
.L129:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L154:
	ldr	r2, [r1, #12]
	ldr	r3, [r4, #48]
	cmp	r2, r3
	beq	.L153
	bl	AOE_GetWKBuf
	mov	r2, r5
	mov	r1, r0
	ldr	r0, [r4, #48]
	bl	UTIL_UnifyBitDepthPcmData
.L153:
	ldr	r2, [r5, #16]
	ldr	r3, [r4, #52]
	cmp	r2, r3
	beq	.L134
	bl	AOE_GetWKBuf
	mov	r2, r5
	mov	r1, r0
	ldr	r0, [r4, #52]
	bl	UTIL_UpmixPcmData
.L134:
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L136
	bl	AOE_GetWKBuf
	ldr	r3, .L158+4
	mov	r1, #0
	ldr	r2, [r5, #4]
	ldr	r3, [r3, #20]
	mov	r6, r0
	blx	r3
	str	r6, [r5]
.L136:
	ldr	r3, [r4, #24]
	ldr	r2, [r4, #4]
	cmp	r3, r2
	beq	.L156
.L137:
	ldr	r2, [r4, #108]
	cmp	r2, #1
	beq	.L138
	bl	AOE_GetWKBuf
	ldr	r7, .L158+4
	add	r6, r4, #20
	ldr	r2, [r5, #4]
	ldr	r1, [r5]
	ldr	r3, [r7, #24]
	mov	r8, r0
	blx	r3
	str	r8, [r5]
	mov	r3, r6
	ldr	r1, [r4, #40]
	mov	r2, r4
	mov	r0, r5
	bl	UTIL_LRFadeGainProcess
	ldr	r3, [r7, #24]
	mov	r1, r6
	mov	r2, #20
	mov	r0, r4
	blx	r3
	b	.L131
.L155:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	RBUF_WriteData
.L156:
	ldr	r1, [r4, #32]
	ldr	r2, [r4, #12]
	cmp	r1, r2
	bne	.L137
.L138:
	cmp	r3, #121
	bne	.L140
	ldr	r3, [r4, #28]
	cmp	r3, #121
	beq	.L157
.L140:
	bl	AOE_GetWKBuf
	ldr	r3, .L158+4
	ldmia	r5, {r1, r2}
	ldr	r3, [r3, #24]
	mov	r6, r0
	blx	r3
	str	r6, [r5]
	add	r2, r4, #20
	ldr	r1, [r4, #40]
	mov	r0, r5
	bl	UTIL_LRGainProcess
	b	.L131
.L157:
	ldr	r3, [r4, #32]
	cmp	r3, #0
	bne	.L140
	ldr	r3, [r4, #36]
	cmp	r3, #0
	bne	.L140
	ldr	r3, [r4, #40]
	cmp	r3, #0
	beq	.L131
	b	.L140
.L159:
	.align	2
.L158:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_WriteRbfData, .-AOP_WriteRbfData
	.align	2
	.global	AOP_GetRingOut
	.type	AOP_GetRingOut, %function
AOP_GetRingOut:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L163
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #112]
	ldmfd	sp, {fp, sp, pc}
.L164:
	.align	2
.L163:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_GetRingOut, .-AOP_GetRingOut
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stAopRm, %object
	.size	g_stAopRm, 64
g_stAopRm:
	.space	64
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
