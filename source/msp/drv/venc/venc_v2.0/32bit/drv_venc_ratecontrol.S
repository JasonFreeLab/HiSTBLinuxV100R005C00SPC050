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
	.file	"drv_venc_ratecontrol.c"
	.text
	.align	2
	.global	VEDU_DRV_RCCalcMinQPForVBR
	.type	VEDU_DRV_RCCalcMinQPForVBR, %function
VEDU_DRV_RCCalcMinQPForVBR:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #20]
	cmp	r3, #0
	bne	.L9
	ldr	r3, [r0, #84]
	movw	r1, #34079
	movt	r1, 20971
	mov	ip, #200
	smull	r4, r5, r3, r1
	mov	r2, r3, asr #31
	rsb	r2, r2, r5, asr #6
	mls	r3, ip, r2, r3
	cmp	r3, #0
	ldrne	r3, [r0, #580]
	beq	.L10
	cmp	r3, #19
	movle	r3, #20
	bgt	.L11
.L6:
	str	r3, [r0, #580]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L11:
	cmp	r3, #30
	movge	r3, #30
	str	r3, [r0, #580]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L10:
	ldr	r4, [r0, #568]
	ldr	r2, [r0, #580]
	add	r4, r4, #200
	str	r3, [r0, #568]
	add	r3, r2, #1
	umull	r4, r5, r4, r1
	cmp	r3, r5, lsr #6
	subhi	r3, r2, #1
	cmp	r3, #19
	movle	r3, #20
	ble	.L6
	b	.L11
.L9:
	ldr	r3, [r0, #184]
	add	r3, r3, #5
	str	r3, [r0, #580]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcMinQPForVBR, .-VEDU_DRV_RCCalcMinQPForVBR
	.align	2
	.global	VEDU_DRV_RCGetVBRMaxBitRate
	.type	VEDU_DRV_RCGetVBRMaxBitRate, %function
VEDU_DRV_RCGetVBRMaxBitRate:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #12]
	cmp	r3, #1280
	movhi	r3, #8388608
	strhi	r3, [r0, #584]
	ldmhifd	sp, {fp, sp, pc}
	cmp	r3, #720
	movhi	r3, #5242880
	strhi	r3, [r0, #584]
	ldmhifd	sp, {fp, sp, pc}
	cmp	r3, #352
	movhi	r3, #3072
	movls	r3, #1536
	str	r3, [r0, #584]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetVBRMaxBitRate, .-VEDU_DRV_RCGetVBRMaxBitRate
	.align	2
	.global	VEDU_DRV_RCGetRecodingQP
	.type	VEDU_DRV_RCGetRecodingQP, %function
VEDU_DRV_RCGetRecodingQP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #272]
	add	r2, r3, #128
	str	r2, [r0, #104]
	str	r3, [r0, #172]
	mov	r3, r3, lsr #6
	str	r3, [r0, #180]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetRecodingQP, .-VEDU_DRV_RCGetRecodingQP
	.global	__aeabi_uidiv
	.align	2
	.global	VEDU_DRV_RCInitInfo
	.type	VEDU_DRV_RCInitInfo, %function
VEDU_DRV_RCInitInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #188]
	mov	r4, r0
	ldr	r5, [r0, #36]
	mov	ip, #1
	ldr	lr, [r0, #192]
	cmp	r3, #4
	ldr	r1, [r0, #28]
	mov	r6, #0
	mov	r2, r5, asl #3
	movlt	r3, #4
	add	r2, r2, r5, lsl #1
	cmp	r3, lr
	str	r1, [r4, #552]
	mov	r0, r5
	movge	r3, lr
	mov	r2, r2, lsr #3
	str	r3, [r4, #208]
	str	r2, [r4, #220]
	str	r2, [r4, #224]
	str	ip, [r4, #212]
	str	ip, [r4, #228]
	str	r6, [r4, #216]
	bl	__aeabi_uidiv
	ldr	r1, [r4, #40]
	ldr	ip, [r4, #76]
	str	r5, [r4, #560]
	cmp	ip, r6
	str	r1, [r4, #556]
	strne	r6, [r4, #84]
	umull	r2, r3, r0, r1
	mov	r9, r0, asr #31
	mov	r8, r0
	str	r0, [r4, #96]
	mla	r3, r1, r9, r3
	strd	r2, [r4, #88]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCInitInfo, .-VEDU_DRV_RCInitInfo
	.align	2
	.global	VEDU_DRV_RCInitInstantBits
	.type	VEDU_DRV_RCInitInstantBits, %function
VEDU_DRV_RCInitInstantBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L29
	add	r4, r0, #276
	ldr	r1, [r0, #28]
	mov	r5, r0
	mov	r3, #0
	mov	r2, #260
	str	r3, [r5, #544]
	mov	r0, r4
	str	r1, [r5, #536]
	mov	r1, r3
	str	r3, [r5, #540]
	str	r3, [r5, #548]
	ldr	r3, [ip]
	blx	r3
	ldrd	r0, [r5, #88]
	mov	r3, #0
	mvn	r2, #0
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L24
	ldr	r0, [r5, #96]
	ldr	r6, [r5, #208]
.L25:
	mul	r3, r0, r6
	ldr	r1, [r5, #536]
	ldr	ip, [r5, #540]
	cmp	r1, #1
	add	ip, r3, ip
	str	ip, [r5, #540]
	str	r3, [r5, #276]
	bls	.L26
	mov	r2, r4
	mov	r3, #1
.L27:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L27
	sub	r3, r3, #2
	mla	r3, r3, r0, r0
	add	ip, ip, r3
	str	ip, [r5, #540]
.L26:
	str	ip, [r5, #548]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L24:
	ldr	r1, [r5, #40]
	ldr	r6, [r5, #208]
	sub	r1, r1, #1
	add	r1, r1, r6
	bl	__aeabi_uidiv
	b	.L25
.L30:
	.align	2
.L29:
	.word	venc_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VEDU_DRV_RCInitInstantBits, .-VEDU_DRV_RCInitInstantBits
	.align	2
	.global	VEDU_DRV_RCInitFrameBits
	.type	VEDU_DRV_RCInitFrameBits, %function
VEDU_DRV_RCInitFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #176]
	mov	r4, r0
	mvn	r2, #0
	str	r2, [r0, #260]
	str	r2, [r0, #264]
	str	r3, [r0, #232]
	mov	r0, r3
	str	r3, [r4, #236]
	ldr	r1, [r4, #208]
	bl	__aeabi_uidiv
	str	r0, [r4, #240]
	str	r0, [r4, #244]
	str	r0, [r4, #248]
	str	r0, [r4, #252]
	str	r0, [r4, #256]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCInitFrameBits, .-VEDU_DRV_RCInitFrameBits
	.align	2
	.global	VEDU_DRV_EflRcInitQp
	.type	VEDU_DRV_EflRcInitQp, %function
VEDU_DRV_EflRcInitQp:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r2, r2, lsl #1
	mov	r3, #100
	mul	r0, r3, r0
	mul	r1, r1, r2
	mov	r1, r1, lsr #1
	bl	__aeabi_uidiv
	cmp	r0, #170
	bhi	.L34
	sub	r3, r0, #121
	cmp	r3, #49
	bls	.L35
	sub	r3, r0, #81
	cmp	r3, #39
	bls	.L36
	sub	r3, r0, #41
	cmp	r3, #39
	bls	.L37
	sub	r3, r0, #16
	cmp	r3, #24
	bls	.L38
	sub	r3, r0, #6
	cmp	r3, #9
	bls	.L39
	sub	r0, r0, #3
	cmp	r0, #3
	movcc	r0, #40
	movcs	r0, #43
	ldmfd	sp, {fp, sp, pc}
.L35:
	mov	r0, #15
	ldmfd	sp, {fp, sp, pc}
.L34:
	mov	r0, #7
	ldmfd	sp, {fp, sp, pc}
.L37:
	mov	r0, #25
	ldmfd	sp, {fp, sp, pc}
.L36:
	mov	r0, #20
	ldmfd	sp, {fp, sp, pc}
.L38:
	mov	r0, #30
	ldmfd	sp, {fp, sp, pc}
.L39:
	mov	r0, #38
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_EflRcInitQp, .-VEDU_DRV_EflRcInitQp
	.align	2
	.global	VEDU_DRV_RCModifyQPDeltaOfIP
	.type	VEDU_DRV_RCModifyQPDeltaOfIP, %function
VEDU_DRV_RCModifyQPDeltaOfIP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r1, #0
	ldrd	r2, [r5, #88]
	mvn	r0, #0
	ldr	r6, [r5, #24]
	cmp	r3, r1
	ldr	r1, [r5, #40]
	cmpeq	r2, r0
	bls	.L42
	ldr	r1, [r5, #96]
	mov	r3, r1, asl #4
	add	r1, r3, r1, lsl #2
.L43:
	cmp	r1, r6
	ldr	r4, [r5, #216]
	bcc	.L45
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L45:
	rsb	r0, r1, r6
	mov	r0, r0, asl #8
	bl	__aeabi_uidiv
	ldr	r2, [r5, #100]
	mvn	r3, #255
	ldr	r1, .L50
	bic	r2, r2, r2, asr #31
	cmp	r0, r3
	movlt	r0, r3
	cmp	r2, #3264
	movge	r2, #3264
	cmp	r0, #256
	mov	r2, r2, lsr #6
	movge	r0, #256
	add	r3, r4, r0, asr #6
	ldr	r2, [r1, r2, asl #2]
	bic	r3, r3, r3, asr #31
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r5, #216]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L42:
	mov	r0, r2, asl #4
	add	r1, r1, #19
	add	r0, r0, r2, lsl #2
	bl	__aeabi_uidiv
	mov	r1, r0
	b	.L43
.L51:
	.align	2
.L50:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VEDU_DRV_RCModifyQPDeltaOfIP, .-VEDU_DRV_RCModifyQPDeltaOfIP
	.align	2
	.global	VEDU_DRV_RcModifyQPForLargeFrmBits
	.type	VEDU_DRV_RcModifyQPForLargeFrmBits, %function
VEDU_DRV_RcModifyQPForLargeFrmBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #24]
	ldr	r1, [r0, #108]
	ldr	r3, [r0, #28]
	ldr	ip, [r0, #588]
	cmp	r2, r1
	rsb	r3, ip, r3
	movcc	r0, #0
	movcs	r0, #1
	cmp	r3, #10
	movhi	r0, #0
	cmp	r0, #0
	beq	.L53
	cmp	r3, #0
	ble	.L54
	mul	r1, r1, r3
	mov	r0, #0
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L53:
	cmp	r3, #0
	ldmlefd	sp, {fp, sp, pc}
	add	ip, r1, r1, lsl #1
	cmp	r2, ip, lsr #1
	ldmccfd	sp, {fp, sp, pc}
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L54:
	bne	.L56
	mov	r0, r3
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L56:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RcModifyQPForLargeFrmBits, .-VEDU_DRV_RcModifyQPForLargeFrmBits
	.align	2
	.global	VEDU_DRV_RCCalcQPDeltaByFrameBits
	.type	VEDU_DRV_RCCalcQPDeltaByFrameBits, %function
VEDU_DRV_RCCalcQPDeltaByFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0, #24]
	ldr	r5, [r0, #108]
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits
	cmp	r4, r5
	mov	r6, r0
	bcc	.L60
	rsb	r0, r5, r4
	mov	r1, r5
	mov	r0, r0, asl #6
	bl	__aeabi_uidiv
.L61:
	add	r0, r0, r6
	mvn	r3, #53
	cmp	r0, r3
	movlt	r0, r3
	cmp	r0, #256
	movge	r0, #256
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L60:
	rsb	r4, r4, r5
	mov	r1, r5
	mov	r0, r4, asl #6
	sub	r0, r0, r4, asl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L61
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcQPDeltaByFrameBits, .-VEDU_DRV_RCCalcQPDeltaByFrameBits
	.align	2
	.global	VEDU_DRV_RCCalcQPDeltaByInstantBits
	.type	VEDU_DRV_RCCalcQPDeltaByInstantBits, %function
VEDU_DRV_RCCalcQPDeltaByInstantBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #36]
	ldr	r7, [r0, #548]
	ldr	r6, [r0, #540]
	mov	r1, r5
	mov	r0, r7, asl #5
	bl	__aeabi_uidiv
	mov	r1, r5
	mov	r4, r0
	mov	r0, r6, asl #5
	bl	__aeabi_uidiv
	usat	r4, #6, r4
	ldr	r3, .L67
	cmp	r6, r7
	mov	r2, r5, lsr #4
	add	r4, r3, r4, lsl #2
	ldr	r1, [r4, #208]
	usat	r0, #6, r0
	add	r3, r3, r0, lsl #2
	ldr	r3, [r3, #208]
	rsb	r0, r1, r3
	bls	.L63
	rsb	r3, r2, r5
	cmp	r7, r3
	bls	.L63
	mov	r3, r0, asl #3
	mvn	r2, #127
	sub	r0, r3, r0, asl #1
	cmp	r0, r2
	movlt	r0, r2
	cmp	r0, #256
	movge	r0, #256
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L63:
	cmp	r6, r7
	bcs	.L66
	add	r5, r2, r5
	cmp	r7, r5
	bcs	.L66
	mov	r0, r0, asl #2
	mvn	r3, #127
	cmp	r0, r3
	movlt	r0, r3
	cmp	r0, #256
	movge	r0, #256
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L66:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcQPDeltaByInstantBits, .-VEDU_DRV_RCCalcQPDeltaByInstantBits
	.global	__aeabi_idiv
	.align	2
	.global	VEDU_DRV_RCCalculateCurQP
	.type	VEDU_DRV_RCCalculateCurQP, %function
VEDU_DRV_RCCalculateCurQP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, [r0, #228]
	mov	r5, r0
	cmp	r6, #0
	bne	.L80
.L70:
	mov	r0, r5
	bl	VEDU_DRV_RCCalcQPDeltaByFrameBits
	mov	r4, r0
	mov	r0, r5
	bl	VEDU_DRV_RCCalcQPDeltaByInstantBits
	ldr	r2, [r5, #540]
	ldr	r1, [r5, #36]
	cmp	r2, r1
	add	r4, r4, r0
	bls	.L71
	rsb	r2, r1, r2
	mov	r0, r2, asl #7
	sub	r0, r0, r2, asl #5
	bl	__aeabi_uidiv
.L72:
	ldr	r1, [r5, #220]
	mvn	ip, #63
	ldr	r2, [r5, #224]
	cmp	r0, ip
	mov	r3, #100
	rsb	r2, r1, r2
	movge	r7, r0
	movlt	r7, ip
	mul	r0, r3, r2
	mov	r0, r0, asl #2
	bl	__aeabi_idiv
	mvn	r2, #31
	ldr	r1, [r5, #172]
	cmp	r0, r2
	movlt	r0, r2
	cmp	r7, #64
	addle	r4, r4, r7
	addgt	r4, r4, #64
	cmp	r0, #32
	addle	r4, r4, r0
	addgt	r4, r4, #32
	cmp	r6, #0
	add	r3, r4, r1
	str	r3, [r5, #172]
	beq	.L73
	ldr	r2, [r5, #104]
	cmp	r3, r2
	addcc	r3, r3, r2
	movcc	r3, r3, lsr #1
.L73:
	ldmib	r5, {r1, r2}
	mov	r2, r2, asl #6
	mov	r1, r1, asl #6
	cmp	r3, r1
	movlt	r3, r1
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r5, #172]
	mov	r3, r3, lsr #6
	str	r3, [r5, #180]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L71:
	rsb	r2, r2, r1
	mov	r0, r2, asl #6
	add	r0, r0, r2, lsl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L72
.L80:
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	r6, [r5, #228]
	b	.L70
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalculateCurQP, .-VEDU_DRV_RCCalculateCurQP
	.align	2
	.global	VEDU_DRV_RCCalcQPDeltaByBitRate
	.type	VEDU_DRV_RCCalcQPDeltaByBitRate, %function
VEDU_DRV_RCCalcQPDeltaByBitRate:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, r1
	bls	.L82
	rsb	r0, r1, r0
	mov	r3, r0, asl #7
	sub	r0, r3, r0, asl #5
	bl	__aeabi_uidiv
.L83:
	mvn	r3, #63
	cmp	r0, r3
	movlt	r0, r3
	cmp	r0, #64
	movge	r0, #64
	ldmfd	sp, {fp, sp, pc}
.L82:
	rsb	r0, r0, r1
	mov	r3, r0, asl #6
	add	r0, r3, r0, lsl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L83
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcQPDeltaByBitRate, .-VEDU_DRV_RCCalcQPDeltaByBitRate
	.align	2
	.global	VEDU_DRV_RCCalcQPDeltaByWaterline
	.type	VEDU_DRV_RCCalcQPDeltaByWaterline, %function
VEDU_DRV_RCCalcQPDeltaByWaterline:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #220]
	mov	r3, #100
	ldr	r0, [r0, #224]
	rsb	r0, r1, r0
	mul	r0, r3, r0
	mov	r0, r0, asl #2
	bl	__aeabi_idiv
	mvn	r3, #31
	cmp	r0, r3
	movlt	r0, r3
	cmp	r0, #32
	movge	r0, #32
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcQPDeltaByWaterline, .-VEDU_DRV_RCCalcQPDeltaByWaterline
	.align	2
	.global	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits
	.type	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits, %function
VEDU_DRV_RCCalcVBRQPDeltaByInstantBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #540]
	mov	r2, #100
	ldr	ip, [r0, #584]
	mov	r1, #95
	mul	r3, r2, r3
	mul	r2, r1, ip
	cmp	r3, r2
	bls	.L90
	mov	r0, #192
	ldmfd	sp, {fp, sp, pc}
.L90:
	mov	r2, #90
	mul	r2, r2, ip
	cmp	r3, r2
	bls	.L91
	mov	r0, #128
	ldmfd	sp, {fp, sp, pc}
.L91:
	mov	r0, #85
	mul	r0, r0, ip
	cmp	r3, r0
	movhi	r0, #64
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits, .-VEDU_DRV_RCCalcVBRQPDeltaByInstantBits
	.align	2
	.global	VEDU_DRV_RCCalcVBRQPDeltaByPicBits
	.type	VEDU_DRV_RCCalcVBRQPDeltaByPicBits, %function
VEDU_DRV_RCCalcVBRQPDeltaByPicBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #84]
	mov	r3, r0
	cmp	ip, #200
	beq	.L93
	ldr	r2, [r0, #576]
	ldr	lr, [r0, #572]
	rsb	r1, lr, r2
	cmp	r1, #0
	ble	.L94
	mov	r0, r1, asl #3
	add	r0, r0, r1, lsl #1
	cmp	r2, r0
	movlt	r0, #64
	movge	r0, #0
.L95:
	mov	r2, #0
	cmp	ip, #1000
	str	lr, [r3, #576]
	str	r2, [r3, #572]
	streq	r2, [r3, #84]
	ldmfd	sp, {fp, sp, pc}
.L93:
	ldr	r1, [r0, #572]
	mov	r2, #0
	mov	r0, r2
	str	r2, [r3, #572]
	str	r1, [r3, #576]
	ldmfd	sp, {fp, sp, pc}
.L94:
	rsb	r1, r1, #0
	mov	r0, r1, asl #3
	add	r1, r0, r1, lsl #1
	cmp	r2, r1
	movge	r0, #0
	mvnlt	r0, #63
	b	.L95
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcVBRQPDeltaByPicBits, .-VEDU_DRV_RCCalcVBRQPDeltaByPicBits
	.align	2
	.global	VEDU_DRV_RCGetQPDeltaForVBR
	.type	VEDU_DRV_RCGetQPDeltaForVBR, %function
VEDU_DRV_RCGetQPDeltaForVBR:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #540]
	mov	r2, #100
	ldr	ip, [r0, #584]
	mov	r1, #95
	mul	r3, r2, r3
	mul	r2, r1, ip
	cmp	r3, r2
	movhi	r4, #192
	bhi	.L101
	mov	r2, #90
	mul	r2, r2, ip
	cmp	r3, r2
	movhi	r4, #128
	bls	.L107
.L101:
	ldr	r1, [r0, #84]
	movw	r2, #34079
	movt	r2, 20971
	mov	ip, #200
	smull	r2, r3, r1, r2
	mov	r2, r1, asr #31
	rsb	r2, r2, r3, asr #6
	mls	r3, ip, r2, r1
	cmp	r3, #0
	movne	r0, #0
	bne	.L102
	bl	VEDU_DRV_RCCalcVBRQPDeltaByPicBits
.L102:
	add	r0, r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L107:
	mov	r4, #85
	mul	r4, r4, ip
	cmp	r3, r4
	movhi	r4, #64
	movls	r4, #0
	b	.L101
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetQPDeltaForVBR, .-VEDU_DRV_RCGetQPDeltaForVBR
	.align	2
	.global	VEDU_DRV_RCUpdateFrameBits
	.type	VEDU_DRV_RCUpdateFrameBits, %function
VEDU_DRV_RCUpdateFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #228]
	cmp	r3, #0
	beq	.L109
	ldr	r3, [r0, #260]
	ldr	r2, [r0, #24]
	add	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	str	r3, [r0, #260]
	add	r3, r3, #58
	str	r2, [r0, r3, asl #2]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L109:
	ldr	r2, [r0, #264]
	add	r2, r2, #1
	cmp	r2, #4
	strls	r2, [r0, #264]
	strhi	r3, [r0, #264]
	movls	r3, r2
	ldr	r2, [r0, #24]
	add	r3, r3, #60
	str	r2, [r0, r3, asl #2]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateFrameBits, .-VEDU_DRV_RCUpdateFrameBits
	.align	2
	.global	VEDU_DRV_RCCalcTimeOfP
	.type	VEDU_DRV_RCCalcTimeOfP, %function
VEDU_DRV_RCCalcTimeOfP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #236]
	mov	r4, r0
	add	r3, r0, #236
	add	ip, r0, #256
	ldr	r0, [r0, #232]
	mov	r1, #0
	add	r0, r2, r0
.L117:
	ldr	r2, [r3, #4]!
	cmp	r3, ip
	add	r1, r1, r2
	bne	.L117
	cmp	r0, #0
	cmpne	r1, #0
	beq	.L120
	mov	r1, r1, asl #1
	add	r0, r0, r0, lsl #2
	bl	__aeabi_idiv
	cmp	r0, #2
	movle	r0, #3
	bgt	.L123
.L119:
	str	r0, [r4, #208]
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #212]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L123:
	cmp	r0, #5
	movge	r0, #5
	b	.L119
.L120:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalcTimeOfP, .-VEDU_DRV_RCCalcTimeOfP
	.align	2
	.global	VEDU_DRV_RCGetTimeOfP
	.type	VEDU_DRV_RCGetTimeOfP, %function
VEDU_DRV_RCGetTimeOfP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	VEDU_DRV_RCUpdateFrameBits
	mov	r0, r4
	bl	VEDU_DRV_RCCalcTimeOfP
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetTimeOfP, .-VEDU_DRV_RCGetTimeOfP
	.align	2
	.global	ModifyInfoForBitRatesChange
	.type	ModifyInfoForBitRatesChange, %function
ModifyInfoForBitRatesChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #36]
	mov	r4, r0
	ldr	r1, [r0, #28]
	mov	r0, r5
	bl	__aeabi_uidiv
	ldr	r1, [r4, #40]
	str	r5, [r4, #560]
	umull	r2, r3, r0, r1
	mov	r7, r0, asr #31
	mov	r6, r0
	str	r0, [r4, #96]
	mla	r3, r1, r7, r3
	strd	r2, [r4, #88]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ModifyInfoForBitRatesChange, .-ModifyInfoForBitRatesChange
	.align	2
	.global	VEDU_DRV_EflRCGetCurTimeOfP
	.type	VEDU_DRV_EflRCGetCurTimeOfP, %function
VEDU_DRV_EflRCGetCurTimeOfP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #44]
	mov	r2, r0
	cmp	r3, #0
	beq	.L127
	ldr	r0, [r0, #208]
	ldr	r3, [r2, #188]
	ldr	r1, [r2, #192]
	cmp	r3, r0
	movlt	r3, r0
	cmp	r3, r1
	movlt	r0, r3
	movge	r0, r1
	str	r0, [r2, #208]
	ldmfd	sp, {fp, sp, pc}
.L127:
	ldr	r0, [r0, #212]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_EflRCGetCurTimeOfP, .-VEDU_DRV_EflRCGetCurTimeOfP
	.align	2
	.global	VEDU_DRV_EflRCCalcTargetFrameBits
	.type	VEDU_DRV_EflRCCalcTargetFrameBits, %function
VEDU_DRV_EflRCCalcTargetFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #40]
	mov	r4, r0
	ldr	r3, [r0, #556]
	mov	lr, r1
	cmp	r3, ip
	beq	.L134
	ldr	r2, [r0, #96]
	str	ip, [r0, #556]
	mov	r1, r2, asr #31
	umull	r2, r3, ip, r2
	mla	r3, ip, r1, r3
	strd	r2, [r4, #88]
.L131:
	umull	r0, r1, r2, lr
	mov	r7, #0
	mvn	r6, #0
	mla	r1, lr, r3, r1
	cmp	r1, r7
	cmpeq	r0, r6
	bls	.L133
	ldr	r3, .L135
	ldr	r0, .L135+4
	ldr	r3, [r3, #8]
	blx	r3
	ldr	ip, [r4, #40]
	mvn	r0, #0
.L133:
	ldr	r1, [r4, #208]
	sub	r1, r1, #1
	add	r1, r1, ip
	bl	__aeabi_uidiv
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L134:
	ldrd	r2, [r0, #88]
	b	.L131
.L136:
	.align	2
.L135:
	.word	venc_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	VEDU_DRV_EflRCCalcTargetFrameBits, .-VEDU_DRV_EflRCCalcTargetFrameBits
	.align	2
	.global	VEDU_DRV_RCGetTargetFrameBits
	.type	VEDU_DRV_RCGetTargetFrameBits, %function
VEDU_DRV_RCGetTargetFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #36]
	mov	r4, r0
	ldr	r3, [r0, #560]
	cmp	r3, r5
	ldreq	r0, [r0, #96]
	beq	.L139
	ldr	r1, [r4, #28]
	mov	r0, r5
	bl	__aeabi_uidiv
	str	r5, [r4, #560]
	str	r0, [r4, #96]
.L139:
	ldr	r2, [r4, #40]
	mov	r9, r0, asr #31
	ldr	r3, [r4, #44]
	mov	r8, r0
	umull	r6, r7, r0, r2
	cmp	r3, #0
	ldreq	r1, [r4, #212]
	mla	r7, r2, r9, r7
	strd	r6, [r4, #88]
	bne	.L144
	cmp	r2, #1000
	mulcs	r0, r0, r1
	bcc	.L145
.L143:
	adds	r3, r3, #0
	str	r0, [r4, #176]
	movne	r3, #1
	str	r3, [r4, #228]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L144:
	ldr	r1, [r4, #188]
	ldr	lr, [r4, #208]
	ldr	ip, [r4, #192]
	cmp	r1, lr
	movlt	r1, lr
	cmp	r1, ip
	movge	r1, ip
	cmp	r2, #1000
	str	r1, [r4, #208]
	mulcs	r0, r0, r1
	bcs	.L143
.L145:
	mov	r0, r4
	bl	VEDU_DRV_EflRCCalcTargetFrameBits
	ldr	r3, [r4, #44]
	b	.L143
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetTargetFrameBits, .-VEDU_DRV_RCGetTargetFrameBits
	.align	2
	.global	VEDU_DRV_RCofFirstFrame
	.type	VEDU_DRV_RCofFirstFrame, %function
VEDU_DRV_RCofFirstFrame:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	VEDU_DRV_RCInitInfo
	mov	r0, r4
	bl	VEDU_DRV_RCInitInstantBits
	mov	r0, r4
	bl	VEDU_DRV_RCGetTargetFrameBits
	ldr	r5, [r4, #176]
	mvn	r3, #0
	ldr	r1, [r4, #208]
	str	r3, [r4, #260]
	str	r3, [r4, #264]
	mov	r0, r5
	str	r5, [r4, #232]
	str	r5, [r4, #236]
	bl	__aeabi_uidiv
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #12]
	mov	r3, r0
	mov	r0, r5
	str	r3, [r4, #240]
	str	r3, [r4, #244]
	str	r3, [r4, #248]
	str	r3, [r4, #252]
	str	r3, [r4, #256]
	bl	VEDU_DRV_EflRcInitQp
	ldr	r2, [r4, #216]
	mov	r3, r0, asl #6
	rsb	r0, r2, r0
	add	r1, r3, #128
	str	r3, [r4, #172]
	str	r1, [r4, #104]
	str	r0, [r4, #180]
	str	r0, [r4, #184]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCofFirstFrame, .-VEDU_DRV_RCofFirstFrame
	.align	2
	.global	ModifyInfoForGopChange
	.type	ModifyInfoForGopChange, %function
ModifyInfoForGopChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #96]
	str	r1, [r0, #556]
	mov	r5, r2, asr #31
	mov	r4, r2
	umull	r2, r3, r1, r2
	mla	r3, r1, r5, r3
	strd	r2, [r0, #88]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	ModifyInfoForGopChange, .-ModifyInfoForGopChange
	.align	2
	.global	VEDU_DRV_RCModifyQPForSpecialScene
	.type	VEDU_DRV_RCModifyQPForSpecialScene, %function
VEDU_DRV_RCModifyQPForSpecialScene:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #76]
	cmp	r3, #0
	beq	.L149
	ldr	r3, [r0, #180]
	add	r3, r3, #1
	cmp	r3, #22
	movle	r3, #23
	bgt	.L159
.L150:
	str	r3, [r0, #180]
	mov	r3, #0
	str	r3, [r0, #76]
.L149:
	ldr	r3, [r0, #72]
	cmp	r3, #0
	ldrne	r3, [r0, #180]
	addne	r3, r3, #1
	strne	r3, [r0, #180]
	ldmfd	sp, {fp, sp, pc}
.L159:
	cmp	r3, #35
	movge	r3, #35
	b	.L150
	UNWIND(.fnend)
	.size	VEDU_DRV_RCModifyQPForSpecialScene, .-VEDU_DRV_RCModifyQPForSpecialScene
	.align	2
	.global	VENC_DRV_RcOpenOneFrm
	.type	VENC_DRV_RcOpenOneFrm, %function
VENC_DRV_RcOpenOneFrm:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #268]
	mov	r4, r0
	cmp	r3, #0
	bne	.L168
	ldr	r3, [r0, #20]
	cmp	r3, #0
	bne	.L169
	ldr	r3, [r0, #28]
	str	r3, [r0, #536]
	bl	VEDU_DRV_RCCalculateCurQP
	mov	r0, r4
	bl	VEDU_DRV_RCGetTimeOfP
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	bl	VEDU_DRV_RCGetTargetFrameBits
.L164:
	mov	r0, r4
	bl	VEDU_DRV_RCModifyQPForSpecialScene
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L169:
	bl	VEDU_DRV_RCofFirstFrame
	b	.L164
.L168:
	ldr	r3, [r0, #272]
	mov	r0, #0
	add	r2, r3, #128
	str	r2, [r4, #104]
	str	r3, [r4, #172]
	mov	r3, r3, lsr #6
	str	r3, [r4, #180]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VENC_DRV_RcOpenOneFrm, .-VENC_DRV_RcOpenOneFrm
	.align	2
	.global	VEDU_DRV_RCUpdateWaterline
	.type	VEDU_DRV_RCUpdateWaterline, %function
VEDU_DRV_RCUpdateWaterline:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #268]
	cmp	r3, #0
	ldrne	r1, [r0, #544]
	ldrne	r2, [r0, #224]
	ldrne	r3, [r0, #176]
	addne	r1, r0, r1, lsl #2
	ldreq	r2, [r0, #224]
	addne	r2, r3, r2
	ldreq	r3, [r0, #176]
	ldrne	r1, [r1, #276]
	rsbne	r2, r1, r2
	ldr	r1, [r0, #24]
	rsb	r3, r3, r2
	add	r3, r3, r1
	str	r3, [r0, #224]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateWaterline, .-VEDU_DRV_RCUpdateWaterline
	.align	2
	.global	VEDU_DRV_RCUpdateInstantBits
	.type	VEDU_DRV_RCUpdateInstantBits, %function
VEDU_DRV_RCUpdateInstantBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, [r0, #536]
	mov	r4, r0
	ldr	r3, [r0, #552]
	cmp	r6, r3
	beq	.L181
	ldr	r5, [r0, #36]
	ldr	r1, [r0, #28]
	mov	r0, r5
	bl	__aeabi_uidiv
	add	r3, r4, #272
	add	r2, r4, #532
.L176:
	str	r0, [r3, #4]!
	cmp	r3, r2
	bne	.L176
	mov	r1, #0
	mov	r2, #1
	mov	r3, r1
	str	r5, [r4, #540]
	str	r6, [r4, #552]
	str	r1, [r4, #544]
.L175:
	ldr	r1, [r4, #268]
	add	r3, r4, r3, lsl #2
	cmp	r1, #0
	ldr	r1, [r4, #24]
	streq	r5, [r4, #548]
	cmp	r6, r2
	ldr	r0, [r3, #276]
	add	r5, r5, r1
	movls	r2, #0
	rsb	r5, r0, r5
	str	r5, [r4, #540]
	str	r1, [r3, #276]
	str	r2, [r4, #544]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L181:
	ldr	r3, [r0, #544]
	ldr	r5, [r0, #540]
	add	r2, r3, #1
	b	.L175
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateInstantBits, .-VEDU_DRV_RCUpdateInstantBits
	.align	2
	.global	VEDU_DRV_RCUpdateInfo
	.type	VEDU_DRV_RCUpdateInfo, %function
VEDU_DRV_RCUpdateInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #268]
	mov	r3, r0
	cmp	r2, #0
	beq	.L183
	ldr	r2, [r0, #544]
	cmp	r2, #0
	ldreq	r2, [r0, #536]
	sub	r2, r2, #1
	str	r2, [r0, #544]
	ldr	r1, [r3, #224]
	add	r0, r0, r2, lsl #2
	ldr	r2, [r3, #176]
	ldr	r0, [r0, #276]
	add	r1, r2, r1
	rsb	r1, r0, r1
.L186:
	ldr	ip, [r3, #24]
	rsb	r2, r2, r1
	mov	r0, r3
	add	r2, r2, ip
	str	r2, [r3, #224]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VEDU_DRV_RCUpdateInstantBits
.L183:
	ldr	r2, [r0, #176]
	ldr	r1, [r0, #224]
	b	.L186
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateInfo, .-VEDU_DRV_RCUpdateInfo
	.align	2
	.global	ModifyInfoForFrmRateChange
	.type	ModifyInfoForFrmRateChange, %function
ModifyInfoForFrmRateChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #536]
	mov	r4, r0
	ldr	r3, [r0, #552]
	cmp	r3, r5
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, [r0, #36]
	ldr	r1, [r0, #28]
	mov	r0, r6
	bl	__aeabi_uidiv
	add	r3, r4, #272
	add	r2, r4, #532
.L189:
	str	r0, [r3, #4]!
	cmp	r3, r2
	bne	.L189
	mov	r3, #0
	str	r6, [r4, #540]
	str	r5, [r4, #552]
	str	r3, [r4, #544]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ModifyInfoForFrmRateChange, .-ModifyInfoForFrmRateChange
	.align	2
	.global	VEDU_DRV_RCIsNeedRecoding
	.type	VEDU_DRV_RCIsNeedRecoding, %function
VEDU_DRV_RCIsNeedRecoding:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #68]
	mov	r3, r0
	cmp	r2, #0
	bne	.L194
	ldr	r2, [r0, #268]
	cmp	r2, #0
	bne	.L194
	ldr	r2, [r0, #44]
	cmp	r2, #0
	bne	.L197
	ldr	r1, [r0, #176]
	ldr	r2, [r0, #24]
	cmp	r2, r1, asl #1
	movhi	r2, #1
	movls	r2, #0
.L196:
	eor	r0, r2, #1
	str	r2, [r3, #268]
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L197:
	ldr	r2, [r0, #176]
	ldr	r1, [r0, #24]
	add	r2, r2, r2, lsl #1
	cmp	r1, r2, lsr #1
	movhi	r2, #1
	movls	r2, #0
	b	.L196
.L194:
	mov	r2, #0
	mvn	r0, #0
	str	r2, [r3, #268]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCIsNeedRecoding, .-VEDU_DRV_RCIsNeedRecoding
	.align	2
	.global	VEDU_DRV_RCStartQPChange
	.type	VEDU_DRV_RCStartQPChange, %function
VEDU_DRV_RCStartQPChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #176]
	mov	r2, #0
	ldr	ip, [r0, #24]
	cmp	r3, ip
	bhi	.L199
.L200:
	mov	r1, r3, asl #7
	add	r2, r2, #1
	add	r3, r1, r3, lsl #4
	mov	r3, r3, asr #7
	cmp	r3, ip
	bls	.L200
	mov	r2, r2, asl #6
.L199:
	ldr	r1, [r0, #4]
	ldr	ip, [r0, #172]
	ldr	r3, [r0, #8]
	add	r2, r2, ip
	mov	r1, r1, asl #6
	cmp	r2, r1
	mov	r3, r3, asl #6
	movlt	r2, r1
	cmp	r2, r3
	movge	r2, r3
	cmp	ip, r2
	str	r2, [r0, #272]
	movne	r0, #0
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCStartQPChange, .-VEDU_DRV_RCStartQPChange
	.align	2
	.global	D_VENC_RC_CLIP3
	.type	D_VENC_RC_CLIP3, %function
D_VENC_RC_CLIP3:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, r1
	movlt	r0, r1
	cmp	r0, r2
	movge	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	D_VENC_RC_CLIP3, .-D_VENC_RC_CLIP3
	.align	2
	.global	VEDU_DRV_RCUpdateIMBInfo
	.type	VEDU_DRV_RCUpdateIMBInfo, %function
VEDU_DRV_RCUpdateIMBInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #80]
	mov	r4, r0
	ldr	r8, [r0, #136]
	mov	r2, r0
	cmp	r3, #1
	ldr	r7, [r0, #132]
	ldr	r6, [r0, #128]
	add	ip, r0, #140
	ldreq	r3, [r0, #144]
	mov	r1, #6
	ldrne	r3, [r0, #116]
	streq	r3, [r0, #116]
	mov	r0, #0
	ldr	r5, [r4, #124]
	ldr	lr, [r4, #120]
	str	r8, [r4, #140]
	str	r7, [r4, #136]
	str	r6, [r4, #132]
	str	r5, [r4, #128]
	str	lr, [r4, #124]
	str	r3, [r2, #120]!
	b	.L209
.L213:
	ldr	r3, [r2, #4]!
.L209:
	cmp	r3, #0
	add	r0, r0, r3
	subeq	r1, r1, #1
	cmp	r2, ip
	bne	.L213
	cmp	r1, #0
	moveq	r0, r1
	beq	.L210
	bl	__aeabi_idiv
.L210:
	str	r0, [r4, #144]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateIMBInfo, .-VEDU_DRV_RCUpdateIMBInfo
	.align	2
	.global	VENC_DRV_RcCloseOneFrm
	.type	VENC_DRV_RcCloseOneFrm, %function
VENC_DRV_RcCloseOneFrm:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #60]
	cmp	r0, #0
	bne	.L215
	ldr	r0, [r4, #64]
	cmp	r0, #0
	bne	.L215
	str	r0, [r4, #20]
	ldr	lr, [r4, #32]
	ldr	ip, [r2]
	rsb	ip, lr, ip
	str	ip, [r2]
	ldr	r2, [r4, #44]
	cmp	r2, #0
	ldreq	r2, [r3]
	movne	r2, r0
	addeq	r2, r2, #1
	str	r2, [r3]
	ldr	r3, [r1]
	ldr	r2, [r4, #24]
	cmp	r3, #0
	beq	.L226
	ldr	ip, [r1, #12]
	ldr	lr, [r1, #16]
	cmp	ip, lr
	ldrhi	lr, [r1, #8]
	ldrls	ip, [r1, #8]
	ldrhi	r0, [r3, lr, asl #2]
	addhi	r3, r3, lr, lsl #2
	addls	r3, r3, ip, lsl #2
	rsbhi	r0, r0, ip
	add	r0, r0, r2
	str	r0, [r1, #12]
	str	r2, [r3]
	ldmib	r1, {r2, r3}
	add	r3, r3, #1
	str	r3, [r1, #8]
	cmp	r3, r2
	rsbcs	r3, r2, r3
	strcs	r3, [r1, #8]
.L226:
	mov	r0, r4
	bl	VEDU_DRV_RCUpdateIMBInfo
	ldr	r3, [r4, #44]
	ldr	r2, [r4, #176]
	mov	r0, #0
	cmp	r3, #0
	ldr	r3, [r4, #172]
	str	r2, [r4, #108]
	strne	r3, [r4, #100]
	streq	r3, [r4, #104]
	ldr	r3, [r4, #24]
	str	r3, [r4, #112]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L215:
	ldr	r3, [r4, #48]
	ldr	r2, [r4, #52]
	clz	r3, r3
	ldr	r0, [r4, #56]
	cmp	r2, #0
	mov	r3, r3, lsr #5
	str	r3, [r4, #48]
	ldr	r3, [r4, #20]
	subne	r2, r2, #1
	moveq	r2, #2
	sub	r0, r0, #1
	cmp	r3, #0
	str	r0, [r4, #56]
	str	r2, [r4, #52]
	beq	.L237
.L219:
	ldr	r3, [r4, #112]
	mvn	r0, #0
	str	r3, [r4, #24]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L237:
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L219
	ldr	r0, [r1, #12]
	ldr	ip, [r1, #16]
	cmp	r0, ip
	strls	r3, [r1, #12]
	ldrhi	r3, [r1, #8]
	ldrls	r0, [r1, #8]
	ldrhi	ip, [r2, r3, asl #2]
	addhi	r2, r2, r3, lsl #2
	addls	r2, r2, r0, lsl #2
	mov	r3, #0
	rsbhi	r0, ip, r0
	strhi	r0, [r1, #12]
	str	r3, [r2]
	ldmib	r1, {r2, r3}
	add	r3, r3, #1
	str	r3, [r1, #8]
	cmp	r3, r2
	rsbcs	r3, r2, r3
	strcs	r3, [r1, #8]
	b	.L219
	UNWIND(.fnend)
	.size	VENC_DRV_RcCloseOneFrm, .-VENC_DRV_RcCloseOneFrm
	.align	2
	.global	VENC_DRV_EflRcAverage
	.type	VENC_DRV_EflRcAverage, %function
VENC_DRV_EflRcAverage:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	lr, r1, #0
	ble	.L243
	sub	ip, r0, #4
	mov	r0, #0
	mov	r3, r0
	mov	r1, lr
.L241:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	cmp	r2, #0
	add	r0, r0, r2
	subeq	r1, r1, #1
	cmp	r3, lr
	bne	.L241
.L239:
	cmp	r1, #0
	beq	.L244
	bl	__aeabi_idiv
	ldmfd	sp, {fp, sp, pc}
.L244:
	mov	r0, r1
	ldmfd	sp, {fp, sp, pc}
.L243:
	mov	r1, lr
	mov	r0, #0
	b	.L239
	UNWIND(.fnend)
	.size	VENC_DRV_EflRcAverage, .-VENC_DRV_EflRcAverage
	.align	2
	.global	VENC_DRV_CalRCRatio
	.type	VENC_DRV_CalRCRatio, %function
VENC_DRV_CalRCRatio:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, r1
	bhi	.L249
	rsb	r0, r0, r1
	mov	r3, #100
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L249:
	rsb	r0, r1, r0
	mov	r3, #100
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VENC_DRV_CalRCRatio, .-VENC_DRV_CalRCRatio
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	MaxIPropDeltaQP, %object
	.size	MaxIPropDeltaQP, 208
MaxIPropDeltaQP:
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	9
	.word	9
	.word	8
	.word	8
	.word	7
	.word	7
	.word	6
	.word	6
	.word	5
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	TabLnx, %object
	.size	TabLnx, 256
TabLnx:
	.word	0
	.word	-1216
	.word	-972
	.word	-830
	.word	-729
	.word	-651
	.word	-587
	.word	-533
	.word	-486
	.word	-445
	.word	-408
	.word	-374
	.word	-344
	.word	-316
	.word	-290
	.word	-265
	.word	-243
	.word	-221
	.word	-201
	.word	-182
	.word	-164
	.word	-147
	.word	-131
	.word	-115
	.word	-100
	.word	-86
	.word	-72
	.word	-59
	.word	-46
	.word	-34
	.word	-22
	.word	-11
	.word	0
	.word	10
	.word	21
	.word	31
	.word	41
	.word	50
	.word	60
	.word	69
	.word	78
	.word	86
	.word	95
	.word	103
	.word	111
	.word	119
	.word	127
	.word	134
	.word	142
	.word	149
	.word	156
	.word	163
	.word	170
	.word	177
	.word	183
	.word	190
	.word	196
	.word	202
	.word	208
	.word	214
	.word	220
	.word	226
	.word	232
	.word	237
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"u32BitsPerGop > 0xffffffff!\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
