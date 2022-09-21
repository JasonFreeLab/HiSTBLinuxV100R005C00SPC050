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
	.file	"pq_mng_dm_alg.c"
	.global	__aeabi_idiv
	.text
	.align	2
	.global	DM_Blend
	.type	DM_Blend, %function
DM_Blend:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r3, #0
	mov	ip, r1
	beq	.L3
	rsb	r4, r2, r3
	add	lr, r3, r3, lsr #31
	mov	r1, r3
	mul	ip, ip, r4
	mla	r0, r2, r0, ip
	add	r0, r0, lr, asr #1
	bl	__aeabi_idiv
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	DM_Blend, .-DM_Blend
	.align	2
	.global	DM_GetDetRatio
	.type	DM_GetDetRatio, %function
DM_GetDetRatio:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #160]
	cmp	r3, #0
	movgt	r0, #15
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	DM_GetDetRatio, .-DM_GetDetRatio
	.align	2
	.global	DM_GetDMParaFlag
	.type	DM_GetDMParaFlag, %function
DM_GetDMParaFlag:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrh	r3, [r1]
	cmp	r3, r0
	bhi	.L13
	ldrh	r3, [r1, #2]
	cmp	r3, r0
	bhi	.L14
	ldrh	r3, [r1, #4]
	cmp	r3, r0
	bhi	.L15
	ldrh	r3, [r1, #6]
	cmp	r3, r0
	movhi	r3, #3
	bhi	.L9
	ldrb	r0, [r2, #4]
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r3, #0
.L9:
	ldrb	r0, [r2, r3]
	ldmfd	sp, {fp, sp, pc}
.L14:
	mov	r3, #1
	b	.L9
.L15:
	mov	r3, #2
	b	.L9
	UNWIND(.fnend)
	.size	DM_GetDMParaFlag, .-DM_GetDMParaFlag
	.align	2
	.global	PQ_MNG_ALG_UpdateDMCfg
	.type	PQ_MNG_ALG_UpdateDMCfg, %function
PQ_MNG_ALG_UpdateDMCfg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #160]
	mov	r3, #0
	mov	r5, r0
	cmp	r2, #720
	mov	r4, r1
	add	r6, r0, #180
	str	r3, [fp, #-36]
	str	r3, [fp, #-32]
	str	r3, [fp, #-44]
	strb	r3, [fp, #-40]
	bgt	.L18
	ldrb	r1, [r0, #165]
	cmp	r1, #1
	beq	.L47
.L18:
	ldrb	r2, [r5, #164]
.L30:
	mov	r3, #44
	smulbb	r3, r2, r3
	add	r5, r6, r3
	ldrh	r3, [r6, r3]
	strh	r3, [r4, #82]
	ldrh	r3, [r5, #2]
	strh	r3, [r4, #84]
	ldrh	r3, [r5, #4]
	strh	r3, [r4, #92]
	ldrh	r3, [r5, #6]
	strh	r3, [r4, #94]
	ldrb	r3, [r5, #8]
	strb	r3, [r4, #282]
	ldrb	r3, [r5, #9]
	strb	r3, [r4, #283]
	ldrh	ip, [r5, #10]
	strh	ip, [r4, #102]
	ldrh	r1, [r5, #12]
	strh	r1, [r4, #104]
	ldrh	r0, [r5, #14]
	strh	r0, [r4, #106]
	ldrh	r2, [r5, #16]
	strh	r2, [r4, #108]
	ldrb	r3, [r5, #20]
	cmp	r3, #1
	beq	.L48
.L45:
	strb	r3, [r4, #281]
	mov	r2, #62
	ldrb	r3, [r5, #19]
	add	r0, r4, #114
	strb	r3, [r4, #280]
	ldrb	r3, [r5, #18]
	strb	r3, [r4, #100]
	ldr	r1, [r5, #40]
	bl	memcpy
	ldrh	r0, [r5, #22]
	movw	r1, #286
	add	r3, r4, #288
	ldr	r2, .L49
	strh	r0, [r4, r1]
	mov	r0, #0
	ldrh	r1, [r5, #24]
	ldr	r2, [r2]
	strh	r1, [r3]
	ldrb	r3, [r5, #26]
	strb	r3, [r4, #284]
	ldrb	r3, [r5, #27]
	strb	r3, [r4, #285]
	ldrb	r3, [r5, #28]
	strb	r3, [r4, #86]
	ldrh	r3, [r5, #30]
	strh	r3, [r4, #88]
	ldrh	r3, [r5, #32]
	strh	r3, [r4, #90]
	ldrh	r3, [r5, #34]
	strh	r3, [r4, #96]
	ldrh	r3, [r5, #36]
	strb	r2, [r4, #80]
	strh	r3, [r4, #98]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L47:
	cmp	r2, r3
	movgt	ip, #15
	movle	ip, r3
	cmp	r0, r3
	beq	.L20
	ldr	r0, .L49+4
	ldr	r2, [r0]
	cmp	r2, #31
	addls	r1, r2, #1
	str	r1, [r0]
	movhi	r2, r3
	add	r2, r2, #2
	add	r2, r5, r2, lsl #2
	mov	r3, r2
	str	ip, [r3, #4]!
	ldr	r1, [r5, #140]
	str	r3, [r5, #152]
	cmp	r1, #0
	ldreqh	r7, [r2, #4]
	beq	.L25
	movle	r0, #0
	ble	.L24
	mov	r2, #0
	add	lr, r5, #12
	mov	r0, r2
.L27:
	ldr	ip, [r3], #-4
	add	r2, r2, #1
	cmp	r3, lr
	add	r0, r0, ip
	addcc	r3, r5, #136
	cmp	r2, r1
	bne	.L27
.L24:
	bl	__aeabi_idiv
	uxth	r7, r0
.L25:
	mov	r2, #8
	add	r1, r5, #166
	sub	r0, fp, #36
	bl	memcpy
	add	r1, r5, #174
	sub	r0, fp, #44
	mov	r2, #5
	bl	memcpy
	ldrh	r3, [fp, #-36]
	cmp	r3, r7
	bhi	.L37
.L34:
	ldrh	r3, [fp, #-34]
	cmp	r3, r7
	bhi	.L38
	ldrh	r3, [fp, #-32]
	cmp	r3, r7
	bhi	.L39
	ldrh	r3, [fp, #-30]
	cmp	r3, r7
	subhi	r3, fp, #41
	bhi	.L28
	ldrb	r2, [fp, #-40]
	b	.L30
.L48:
	sxth	ip, ip
	sxth	r0, r0
	sxth	r1, r1
	sxth	r2, r2
	cmp	r1, r2
	cmpgt	ip, r0
	movle	r3, #0
	b	.L45
.L39:
	sub	r3, fp, #42
.L28:
	ldrb	r2, [r3]
	b	.L30
.L20:
	mov	r2, #8
	mov	r1, #166
	sub	r0, fp, #36
	movw	r7, #65535
	bl	memcpy
	mov	r2, #5
	mov	r1, #174
	sub	r0, fp, #44
	bl	memcpy
	b	.L34
.L37:
	sub	r3, fp, #44
	b	.L28
.L38:
	sub	r3, fp, #43
	b	.L28
.L50:
	.align	2
.L49:
	.word	.LANCHOR1
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_UpdateDMCfg, .-PQ_MNG_ALG_UpdateDMCfg
	.global	g_u32DmStr
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_u32DmStr, %object
	.size	g_u32DmStr, 4
g_u32DmStr:
	.word	8
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	i.4685, %object
	.size	i.4685, 4
i.4685:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
