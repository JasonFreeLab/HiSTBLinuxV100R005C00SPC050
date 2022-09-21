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
	.file	"hevc.c"
	.text
	.align	2
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L3
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L3:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.global	__aeabi_idivmod
	.align	2
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.2, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.2:
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
	add	r3, r0, #40960
	ldr	ip, [r0, #2304]
	movw	r6, #2024
	ldr	r2, [r3, #2652]
	add	lr, r0, #45056
	str	r1, [fp, #-84]
	movw	r5, #15788
	ldr	r1, [lr, #1764]
	mov	r7, r0
	mla	ip, r6, r2, ip
	ldr	r6, [lr, #1768]
	ldr	r4, [r0, #2300]
	add	r1, r6, r1
	ldr	r2, [lr, #1772]
	str	r1, [fp, #-80]
	mov	lr, r1
	cmp	r1, r2
	ldr	ip, [ip, #32]
	str	r0, [fp, #-60]
	mov	r0, #1
	mla	r1, r5, ip, r4
	ldr	r10, [r1, #128]
	mov	r10, r0, asl r10
	bcs	.L6
	add	r9, lr, #11712
	ldr	r6, [r7, #2492]
	add	r9, r9, #24
	mov	r0, #0
	add	r2, r2, #46848
	add	r1, lr, #46848
	add	r9, r7, r9, lsl #2
	mov	ip, r0
	add	r2, r2, #9
	add	r1, r1, #9
	str	r0, [fp, #-64]
	mov	r0, r7
	add	r2, r7, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r7, r1
	str	r3, [fp, #-76]
	str	r2, [fp, #-56]
.L7:
	cmp	r6, #0
	beq	.L13
	ldr	r3, [fp, #-60]
	mov	r2, #0
	ldr	r8, [r9, #-1884]
	mov	r5, r2
	add	r4, r3, #2512
	str	r2, [fp, #-52]
	b	.L10
.L50:
	ldr	r3, [r4]
	ldr	r1, [r3, #52]
	cmp	r1, #0
	beq	.L9
	ldr	r0, [r3, #12]
	ldr	r1, [r9]
	cmp	r0, r1
	ldreqb	r3, [r3, #1]	@ zero_extendqisi2
	beq	.L48
.L9:
	add	r5, r5, #1
	add	r4, r4, #4
	cmp	r5, r6
	beq	.L49
.L10:
	cmp	r8, #0
	bne	.L50
	ldr	r7, [r4]
	mov	r1, r10
	ldr	r3, [r7, #52]
	cmp	r3, #0
	beq	.L9
	ldr	r0, [r7, #12]
	bl	__aeabi_idivmod
	ldr	r0, [r9]
	str	r1, [fp, #-48]
	mov	r1, r10
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-48]
	cmp	r3, r1
	bne	.L9
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
.L48:
	cmp	r3, #0
	add	r5, r5, #1
	ldr	r3, [fp, #-52]
	add	r4, r4, #4
	movne	r3, #1
	cmp	r5, r6
	str	r3, [fp, #-52]
	bne	.L10
.L49:
	ldr	r2, [fp, #-52]
	cmp	r2, #0
	beq	.L13
.L11:
	ldr	r3, [fp, #-56]
	add	r9, r9, #4
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L7
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-76]
	cmp	r2, #0
	beq	.L15
.L14:
	ldr	r2, [fp, #-60]
	mov	r7, #0
	ldr	r10, [fp, #-80]
	add	r4, r2, #46848
	ldr	r0, [fp, #-72]
	mov	r9, r2
	mov	r8, r4
	add	r4, r4, #28
	add	r8, r8, #9
.L19:
	cmp	r6, #0
	beq	.L20
	add	lr, r9, #2496
	mov	r5, #0
	add	lr, lr, #12
	mov	r2, r5
	str	r0, [fp, #-48]
	b	.L17
.L16:
	cmp	r2, r6
	beq	.L51
.L17:
	ldr	r1, [lr, #4]!
	add	r2, r2, #1
	ldr	ip, [r1, #52]
	cmp	ip, #0
	bne	.L16
	ldr	r0, [r4]
	ldr	ip, [r3, #2624]
	add	ip, ip, r0
	ldr	r0, [r1, #12]
	cmp	r0, ip
	bne	.L16
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #0
	movne	r5, #1
	cmp	r2, r6
	bne	.L17
.L51:
	cmp	r5, #0
	ldr	r0, [fp, #-48]
	beq	.L20
.L18:
	add	r7, r7, #1
	add	r4, r4, #4
	cmp	r10, r7
	add	r8, r8, #1
	bhi	.L19
	str	r0, [fp, #-72]
.L15:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	ldrne	r3, [fp, #-84]
	movne	r0, #0
	ldrne	r2, [fp, #-64]
	moveq	r0, #1
	strne	r2, [r3]
.L47:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	ldr	r2, [r3, #2624]
	ldr	ip, [r4]
	ldr	r1, [r9, #200]
	add	r2, r2, ip
	cmp	r2, r1
	blt	.L18
	ldrb	r1, [r8]	@ zero_extendqisi2
	cmp	r1, #0
	ldr	r1, [fp, #-64]
	movne	r0, #1
	movne	r1, r2
	str	r1, [fp, #-64]
	b	.L18
.L13:
	ldr	r3, [fp, #-76]
	ldr	r0, [r9, #-68]
	ldr	r2, [r3, #2624]
	ldr	r3, [fp, #-60]
	add	r2, r2, r0
	ldr	r1, [r3, #200]
	cmp	r2, r1
	blt	.L11
	ldr	r3, [fp, #-56]
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, [fp, #-64]
	cmp	r1, #0
	movne	r3, r2
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-72]
	movne	r3, #1
	str	r3, [fp, #-72]
	b	.L11
.L6:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	beq	.L47
	ldr	r1, [fp, #-60]
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-72]
	ldr	r6, [r1, #2492]
	b	.L14
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.2, .-HEVC_CheckThatAllRefPicsAreAvailable.part.2
	.align	2
	.type	HEVC_SetFrmRepeatCount.part.3, %function
HEVC_SetFrmRepeatCount.part.3:
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
	ldr	ip, [r0, #260]
	ldr	r2, [r0, #2488]
	ldr	r3, [r0, #256]
	add	r2, r2, ip
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1, #84]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #84]
	strls	r3, [r1, #84]
	ldrhi	r3, [r0, #260]
	ldrls	r3, [r0, #260]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #260]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.part.3, .-HEVC_SetFrmRepeatCount.part.3
	.global	__aeabi_uidiv
	.align	2
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 24
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
	ldr	r4, [fp, #8]
	str	r0, [fp, #-48]
	cmp	r4, #15
	ldr	r6, [fp, #4]
	bgt	.L57
	cmp	r4, #8
	mul	r9, r4, r4
	beq	.L90
	cmp	r9, #0
	movne	r10, r6
	beq	.L57
.L59:
	mov	r5, #0
	rsb	r7, r4, #1
	mov	r8, r5
.L65:
	cmp	r4, r8
	bgt	.L77
	rsb	lr, r4, r8
	sub	r2, r4, #1
	add	lr, lr, #1
.L66:
	cmp	r2, #0
	cmpge	r4, lr
	ble	.L63
	mla	r0, r2, r4, lr
	add	ip, r10, r5, lsl #2
	mov	r1, r5
.L64:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r5, r1
	str	r0, [ip], #4
	add	r3, r3, lr
	add	r0, r0, r7
	cmp	r2, #0
	cmpge	r4, r3
	bgt	.L64
	mov	r5, r1
.L63:
	cmp	r9, r5
	add	r8, r8, #1
	bhi	.L65
.L57:
	cmp	r4, #4
	ble	.L56
	mov	r3, r4, asr #2
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-64]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	mov	r0, r2
	str	r2, [fp, #-60]
	cmp	r0, #0
	ldrsb	r2, [r3, #8]
	add	r2, r2, #1
	beq	.L56
	add	r3, r1, #308
.L61:
	ldr	r1, .L91
	rsb	r7, r4, #1
	str	r3, [fp, #-52]
	mov	r3, #0
	add	r2, r1, r2, lsl #16
	str	r3, [fp, #-48]
	sub	r3, r2, #4
	str	r3, [fp, #-56]
.L75:
	ldr	r3, [fp, #-56]
	cmp	r4, #32
	ldr	r9, [fp, #-64]
	mov	r8, #0
	ldr	r5, [r3, #4]!
	mov	r1, r9
	str	r3, [fp, #-56]
	ldreq	r3, [fp, #-52]
	ldreq	r5, [r3]
	mov	r0, r5
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-48]
	mov	r3, r8
	mov	r2, r8
	mov	lr, r8
	mov	r10, ip, asl #4
	mla	r1, r4, r0, r5
	mls	r1, r9, r0, r1
	mov	r9, r1, asl #2
.L69:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L70
	mla	r1, r2, r4, lr
	add	r0, r3, r10
	rsb	lr, r3, lr
	add	r0, r6, r0, lsl #2
	add	r1, r1, r9
.L71:
	add	r3, r3, #1
	sub	r2, r2, #1
	add	r5, lr, r3
	str	r1, [r0], #4
	cmp	r5, #3
	mvn	ip, r2
	mov	ip, ip, lsr #31
	add	r1, r1, r7
	movgt	ip, #0
	cmp	ip, #0
	bne	.L71
.L70:
	cmp	r3, #15
	add	r8, r8, #1
	bhi	.L72
	cmp	r8, #3
	movle	r2, r8
	movle	lr, #0
	subgt	lr, r8, #3
	movgt	r2, #3
	b	.L69
.L72:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L75
.L56:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L77:
	mov	r2, r8
	mov	lr, #0
	b	.L66
.L90:
	add	r3, r0, #308
	cmp	r9, #0
	mov	r10, r3
	bne	.L59
	ldr	r2, [fp, #-48]
	mov	r1, #2
	str	r1, [fp, #-64]
	mov	r1, #4
	str	r1, [fp, #-60]
	ldrsb	r2, [r2, #10]
	add	r2, r2, #1
	b	.L61
.L92:
	.align	2
.L91:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	2
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r3, r0, #7
	add	r1, r0, #136
	mov	r7, r0
	mvn	r2, #0
.L94:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L94
	ldr	r6, .L98
	mov	r2, #0
	mov	r3, #2
	mov	r5, r2
	mov	r4, r3
	strb	r2, [r7, #12]
	strb	r3, [r7, #24]
	mov	r2, #1
	mov	r3, #3
	strb	r2, [r7, #16]
	strb	r3, [r7, #40]
	mov	r3, #4
	strb	r3, [r7, #72]
.L95:
	mov	r3, #0
	str	r5, [sp, #12]
	str	r4, [sp, #8]
	add	r5, r5, #1
	str	r4, [sp, #4]
	mov	r2, r3
	str	r6, [sp]
	mov	r1, r3
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	HEVC_InitSigLastScan
	cmp	r5, #7
	add	r6, r6, #65536
	bne	.L95
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L99:
	.align	2
.L98:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.global	__aeabi_idiv
	.align	2
	.global	HEVCGetDar
	.type	HEVCGetDar, %function
HEVCGetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #0
	mov	ip, r1
	moveq	r4, r0
	beq	.L101
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	movne	r4, #0
	bne	.L101
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #255
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	bne	.L101
	cmp	r0, #1
	moveq	r4, #5
	beq	.L101
	cmp	lr, #0
	str	r3, [fp, #-24]
	ldrne	r2, .L123
	addne	r1, r2, r0, lsl #3
	ldrne	ip, [r2, r0, asl #3]
	ldrne	r2, [r1, #4]
	mov	r0, ip, asl #10
	mov	r1, r2
	bl	__aeabi_idiv
	ldr	r3, [fp, #-24]
	ldr	r1, [fp, #4]
	mov	r4, r0
	mov	r0, r3, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r2, #2262
	mul	r0, r0, r4
	add	r4, r0, #1020
	cmp	r0, #0
	add	r4, r4, #3
	movlt	r0, r4
	mov	r0, r0, asr #10
	cmp	r0, r3
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r2
	bgt	.L105
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	bge	.L106
.L116:
	mov	r4, #4
.L101:
	ldr	r3, .L123+4
	mov	r2, r4
	ldr	r1, .L123+8
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L105:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	blt	.L116
.L106:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L107
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	blt	.L118
.L108:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r0, r0, #1360
	subgt	r0, r0, #1360
	addle	r0, r0, #5
	subgt	r0, r0, #5
	cmp	r3, r0
	movlt	r4, #2
	movge	r4, #1
	b	.L101
.L107:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	bge	.L108
.L118:
	mov	r4, #3
	b	.L101
.L124:
	.align	2
.L123:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVCGetDar, .-HEVCGetDar
	.align	2
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	ldr	r6, .L131
	mov	r7, r0
	ldr	r1, .L131+4
	mov	r0, #1
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r7, #160]
	cmn	r3, #1
	beq	.L129
	mov	r5, #0
	movw	r8, #52429
	add	r9, r7, #53248
	mov	r4, r5
	movt	r8, 52428
	mov	r10, r6
	b	.L128
.L127:
	ldr	r3, [r7, #160]
	add	r3, r3, #1
	cmp	r3, r4
	bls	.L129
.L128:
	ldr	r3, [r9, #3252]
	mov	r2, r4
	ldr	ip, [r6, #68]
	mov	r0, #1
	add	r3, r3, r5
	ldr	r1, .L131+8
	add	r5, r5, #100
	ldr	lr, [r3, #36]
	str	lr, [sp]
	blx	ip
	umull	r2, r3, r4, r8
	mov	r2, r3, lsr #3
	mov	r3, r2, asl #3
	add	r3, r3, r2, lsl #1
	cmp	r4, r3
	add	r4, r4, #1
	bne	.L127
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L131+12
	blx	r3
	ldr	r3, [r7, #160]
	add	r3, r3, #1
	cmp	r3, r4
	bhi	.L128
.L129:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L131+12
	blx	r3
	ldr	r3, [r6, #68]
	ldr	r1, .L131+16
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L132:
	.align	2
.L131:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	.word	.LC6
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
	.align	2
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #4)
	sub	sp, sp, #4
	ldr	r4, .L154
	add	r7, r0, #40960
	mov	r8, r0
	ldr	r1, .L154+4
	mov	r0, #1
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r7, #2736]
	mov	r0, #1
	ldr	r1, .L154+8
	blx	r3
	ldr	r3, [r7, #2736]
	cmp	r3, #0
	addne	r6, r8, #2304
	movne	r5, #0
	addne	r6, r6, #12
	movne	r9, r4
	beq	.L141
.L140:
	ldr	r3, [r6, #4]!
	mov	r2, r5
	mov	r0, #1
	ldr	r1, .L154+12
	ldr	ip, [r4, #68]
	add	r5, r5, r0
	blx	ip
	ldr	r3, [r6]
	ldr	r1, .L154+16
	mov	r0, #1
	cmp	r3, #0
	beq	.L138
	ldr	r2, [r3, #32]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [r6]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L138
	ldr	r1, [r3, #32]
	ldr	r0, [r8, #244]
	ldr	r10, [r9, #68]
	bl	FSP_GetLogicFs
	ldr	r1, .L154+20
	mov	r2, r0
	mov	r0, #1
	blx	r10
.L138:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r1, .L154+24
	blx	r3
	ldr	r3, [r7, #2736]
	cmp	r3, r5
	bhi	.L140
.L141:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r2, [r7, #2740]
	ldr	r1, .L154+28
	blx	r3
	ldr	r3, [r7, #2740]
	cmp	r3, #0
	addne	r6, r8, #2384
	ldrne	r9, .L154
	movne	r5, #0
	beq	.L136
.L145:
	ldr	r3, [r6, #4]!
	mov	r2, r5
	mov	r0, #1
	ldr	r1, .L154+32
	ldr	ip, [r4, #68]
	add	r5, r5, r0
	blx	ip
	ldr	r3, [r6]
	ldr	r1, .L154+16
	mov	r0, #1
	cmp	r3, #0
	beq	.L143
	ldr	r2, [r3, #32]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [r6]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L143
	ldr	r1, [r3, #32]
	ldr	r0, [r8, #244]
	ldr	r10, [r9, #68]
	bl	FSP_GetLogicFs
	ldr	r1, .L154+20
	mov	r2, r0
	mov	r0, #1
	blx	r10
.L143:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r1, .L154+24
	blx	r3
	ldr	r3, [r7, #2740]
	cmp	r3, r5
	bhi	.L145
.L136:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r1, .L154+36
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L155:
	.align	2
.L154:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC8
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LC4
	.word	.LC9
	.word	.LC14
	.word	.LC13
	UNWIND(.fnend)
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
	.align	2
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r7, .L163
	mov	r9, r0
	ldr	r1, .L163+4
	mov	r0, #1
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r3, [r9, #176]
	cmp	r3, #0
	addne	r6, r9, #57088
	movne	r8, #0
	addne	r6, r6, #224
	movne	r10, r7
	beq	.L160
.L159:
	ldrb	lr, [r6, #2]	@ zero_extendqisi2
	mov	r3, r6
	ldr	ip, [r7, #68]
	mov	r2, r8
	ldr	r1, .L163+8
	mov	r0, #1
	str	lr, [sp, #8]
	add	r5, r6, #280
	ldrb	lr, [r6, #1]	@ zero_extendqisi2
	mov	r4, #0
	str	lr, [sp, #4]
	ldr	lr, [r6, #4]
	str	lr, [sp]
	blx	ip
.L158:
	mov	r2, r4
	ldr	ip, [r7, #68]
	ldr	r3, [r5, #4]!
	add	r4, r4, #1
	ldr	r1, .L163+12
	mov	r0, #1
	blx	ip
	cmp	r4, #4
	bne	.L158
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L163+16
	add	r8, r8, r0
	blx	r3
	ldr	r3, [r9, #176]
	add	r6, r6, #584
	cmp	r3, r8
	bhi	.L159
.L160:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L163+20
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L164:
	.align	2
.L163:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	.word	.LC17
	.word	.LC18
	.word	.LC4
	.word	.LC16
	UNWIND(.fnend)
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	2
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r8, .L168
	mov	r4, r0
	ldr	r1, .L168+4
	mov	r5, r4
	mov	r0, #1
	ldr	r3, [r8, #68]
	add	r7, r4, #2848
	blx	r3
	ldr	r3, [r4, #2784]
	ldr	r2, [r5, #2788]!
	mov	r0, #1
	ldr	ip, [r8, #68]
	add	r6, r4, #2912
	ldr	r1, .L168+8
	add	r7, r7, #4
	blx	ip
	add	r6, r6, #4
	mov	r4, #0
.L166:
	ldr	r1, [r7, #4]!
	mov	r2, r4
	ldr	lr, [r6, #4]!
	add	r4, r4, #1
	ldr	r3, [r5, #4]!
	mov	r0, #1
	ldr	ip, [r8, #68]
	stmia	sp, {r1, lr}
	ldr	r1, .L168+12
	blx	ip
	cmp	r4, #16
	ldr	r3, .L168
	bne	.L166
	ldr	r3, [r3, #68]
	mov	r0, #1
	ldr	r1, .L168+16
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L169:
	.align	2
.L168:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
	.align	2
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r10, .L186
	mov	r7, r0
	ldr	r1, .L186+4
	mov	r0, #1
	ldr	r3, [r10, #68]
	blx	r3
	ldr	ip, [r7, #2508]
	ldr	r1, [r7, #2504]
	mov	r0, #1
	ldr	lr, [r7, #2500]
	ldr	r3, [r7, #2492]
	ldr	r2, [r7, #2488]
	stmia	sp, {r1, ip, lr}
	ldr	ip, [r10, #68]
	ldr	r1, .L186+8
	blx	ip
	ldr	r3, [r7, #2492]
	cmp	r3, #0
	addne	r4, r7, #2496
	movne	r5, #0
	addne	r4, r4, #12
	beq	.L175
.L174:
	ldr	r3, [r4, #4]!
	ldr	r2, [r10, #68]
	ldr	r0, [r7, #244]
	ldrb	lr, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #52]
	ldr	r6, [r3, #4]
	ldrb	r8, [r3, #1]	@ zero_extendqisi2
	str	r2, [fp, #-48]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	ldr	r1, [r3, #32]
	str	lr, [fp, #-52]
	str	r2, [fp, #-64]
	ldr	r9, [r3, #12]
	str	ip, [fp, #-68]
	str	r6, [fp, #-56]
	str	r8, [fp, #-60]
	bl	FSP_GetLogicFs
	ldr	r3, [r4]
	ldr	r1, [r3, #32]
	mov	r6, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #32]
	mov	r8, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDisplay
	ldr	r1, [r4]
	ldr	ip, [fp, #-68]
	mov	r2, r5
	add	r5, r5, #1
	ldr	lr, [r1, #268]
	mov	r3, r1
	str	lr, [sp, #40]
	ldr	r1, [r1, #32]
	ldr	lr, [fp, #-52]
	str	r9, [sp, #16]
	str	r1, [sp, #36]
	ldr	r1, [fp, #-64]
	ldr	r9, [fp, #-60]
	str	ip, [sp, #20]
	str	r1, [sp, #12]
	ldr	r1, [fp, #-56]
	str	r9, [sp, #8]
	str	lr, [sp]
	str	r1, [sp, #4]
	str	r8, [sp, #28]
	str	r6, [sp, #24]
	ldr	r1, .L186+12
	ldr	ip, [fp, #-48]
	str	r0, [sp, #32]
	mov	r0, #1
	blx	ip
	ldr	r3, [r7, #2492]
	cmp	r3, r5
	bhi	.L174
.L175:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L186+16
	blx	r3
	ldr	r3, [r7, #2492]
	cmp	r3, #0
	beq	.L173
	add	r5, r7, #2496
	ldr	r9, .L186
	add	r5, r5, #12
	mov	r6, #0
	b	.L182
.L185:
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r2, [r4, #512]
	mov	r0, #1
	ldr	r1, .L186+20
	blx	r3
	ldr	r3, [r9, #68]
	ldrsb	r2, [r4]
	mov	r0, #1
	ldr	r1, .L186+24
	blx	r3
	ldrsb	r2, [r4, #1]
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L186+28
	blx	r3
.L177:
	cmp	r8, #0
	ldr	r3, [r10, #68]
	mov	r2, r8
	ldr	r1, .L186+32
	mov	r0, #1
	beq	.L178
	blx	r3
	ldr	r2, [r8, #56]
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L186+36
	blx	r3
.L179:
	ldr	r4, [fp, #-48]
	mov	r0, #1
	ldr	r1, .L186+40
	cmp	r4, #0
	ldr	r3, [r10, #68]
	mov	r2, r4
	beq	.L180
	blx	r3
	ldr	r2, [r4, #56]
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L186+44
	blx	r3
.L181:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L186+16
	add	r6, r6, r0
	blx	r3
	ldr	r3, [r7, #2492]
	cmp	r3, r6
	bls	.L173
.L182:
	ldr	r3, [r5, #4]!
	ldr	r0, [r7, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #32]
	mov	r4, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #32]
	mov	r8, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDispPhyFs
	ldr	r3, [r10, #68]
	mov	r2, r6
	ldr	r1, .L186+48
	str	r0, [fp, #-48]
	mov	r0, #1
	blx	r3
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L186+52
	mov	r0, #1
	ldr	r3, [r9, #68]
	bne	.L185
	ldr	r1, .L186+56
	mov	r0, #1
	blx	r3
	b	.L177
.L180:
	ldr	r1, .L186+60
	mov	r0, #1
	blx	r3
	b	.L181
.L178:
	ldr	r1, .L186+64
	mov	r0, #1
	blx	r3
	b	.L179
.L173:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L186+68
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L187:
	.align	2
.L186:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC4
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC33
	.word	.LC34
	.word	.LC36
	.word	.LC37
	.word	.LC27
	.word	.LC28
	.word	.LC32
	.word	.LC38
	.word	.LC35
	.word	.LC26
	UNWIND(.fnend)
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	2
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
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
	cmp	r0, #9
	bls	.L190
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L190:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.align	2
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
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
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.align	2
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
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
	bics	r0, r0, #6
	subne	r0, r0, #8
	clzne	r0, r0
	movne	r0, r0, lsr #5
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.align	2
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
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
	sub	r0, r0, #16
	cmp	r0, #4
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.align	2
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
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
	add	r3, r0, #40960
	ldr	r3, [r3, #2028]
	cmp	r3, #0
	bne	.L198
	ldr	r2, [r0, #2308]
	ldr	r1, [r2, #708]
	cmp	r1, #1
	beq	.L202
.L200:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L198:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L202:
	ldr	r0, [r2, #704]
	cmp	r0, #0
	bne	.L200
	ldr	r3, [r2, #712]
	cmp	r3, #0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, [r2, #684]
	add	r3, r3, #1024
	cmp	r3, #2048
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.align	2
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
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
	add	r5, r0, #24576
	str	r3, [fp, #-52]
	mov	r7, r2
	ldr	r3, [r5, #2608]
	mov	r8, r1
	ldr	r2, [r5, #2604]
	ldr	r9, [r3, #68]
	ldr	r3, [r3, #72]
	ldr	r2, [r2, #148]
	str	r3, [fp, #-48]
	sub	r3, r9, #1
	cmp	r3, #9
	str	r2, [fp, #-56]
	bhi	.L231
	ldr	r3, [fp, #-48]
	sub	r3, r3, #1
	cmp	r3, #10
	bhi	.L232
	ldr	r6, .L233
	mov	r2, #512
	mov	r1, #0
	mov	r0, r8
	ldr	r3, [r6, #48]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #80
	mov	r1, #0
	mov	r0, r7
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #88
	mov	r1, #0
	ldr	r0, [fp, #-52]
	blx	r3
	cmp	r9, #0
	ble	.L212
	ldr	r3, [fp, #-56]
	mov	r2, #0
	mov	r1, r2
	mov	r0, r7
	sub	r10, r3, #4
.L211:
	str	r2, [r7, r1, asl #3]
	mov	r3, r2, asl r10
	ldr	ip, [r5, #2608]
	add	ip, ip, r1, lsl #1
	ldrsh	ip, [ip, #176]
	add	r2, ip, r2
	sub	ip, r2, #1
	str	ip, [r0, #4]
	mov	lr, r2, asl r10
	cmp	r3, lr
	bge	.L217
	cmp	r3, #255
	bhi	.L213
	uxtb	r4, r1
	add	ip, r8, r3
	b	.L215
.L216:
	cmp	r3, #256
	beq	.L213
.L215:
	add	r3, r3, #1
	strb	r4, [ip], #1
	cmp	r3, lr
	bne	.L216
.L217:
	add	r1, r1, #1
	add	r0, r0, #8
	cmp	r1, r9
	bne	.L211
.L212:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ble	.L209
	ldr	r3, [fp, #-56]
	mov	ip, #0
	ldr	r9, [fp, #-52]
	mov	lr, ip
	sub	r4, r3, #4
	mov	r7, r9
.L219:
	str	ip, [r9, lr, asl #3]
	mov	r3, ip, asl r4
	ldr	r2, [r5, #2608]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #216]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r7, #4]
	mov	r1, ip, asl r4
	cmp	r3, r1
	bge	.L224
	cmp	r3, #255
	bhi	.L220
	add	r2, r3, #255
	uxtb	r0, lr
	add	r2, r8, r2
	b	.L222
.L223:
	cmp	r3, #256
	beq	.L220
.L222:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L223
.L224:
	ldr	r3, [fp, #-48]
	add	lr, lr, #1
	add	r7, r7, #8
	cmp	lr, r3
	bne	.L219
.L209:
	mov	r0, #0
	b	.L205
.L213:
	ldr	ip, [r6, #68]
	mov	r0, #1
	ldr	r2, .L233+4
	ldr	r1, .L233+8
	blx	ip
	mvn	r0, #0
.L205:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldr	ip, [r6, #68]
	mov	r0, #1
	ldr	r2, .L233+4
	ldr	r1, .L233+12
	blx	ip
	mvn	r0, #0
	b	.L205
.L232:
	ldr	r1, .L233
	mov	r0, #11
	ldr	r3, [fp, #-48]
	str	r0, [sp]
	mov	r0, #1
	ldr	ip, [r1, #68]
	ldr	r2, .L233+4
	ldr	r1, .L233+16
	blx	ip
	mvn	r0, #0
	b	.L205
.L231:
	ldr	r1, .L233
	mov	r0, #10
	mov	r3, r9
	str	r0, [sp]
	ldr	r2, .L233+4
	mov	r0, #1
	ldr	ip, [r1, #68]
	ldr	r1, .L233+20
	blx	ip
	mvn	r0, #0
	b	.L205
.L234:
	.align	2
.L233:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+136
	.word	.LC41
	.word	.LC42
	.word	.LC40
	.word	.LC39
	UNWIND(.fnend)
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	2
	.global	HEVC_VPSEqual
	.type	HEVC_VPSEqual, %function
HEVC_VPSEqual:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r10, r0, #0
	ldreq	ip, .L262
	movweq	r3, #1365
	beq	.L259
	cmp	r1, #0
	beq	.L260
	ldr	r4, [r10, #12]
	add	lr, r10, #12288
	ldr	r3, [r10, #16]
	add	ip, r1, #12288
	ldr	r6, [r1, #16]
	add	r2, r10, #12416
	ldr	r5, [r1, #12]
	add	r0, r1, #12416
	ldr	r9, [r1, #20]
	mov	r7, r2
	cmp	r3, r6
	cmpeq	r4, r5
	ldr	r8, [r10, #20]
	ldrb	r5, [r10, #1]	@ zero_extendqisi2
	add	r2, r2, #20
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	moveq	r4, #1
	movne	r4, #0
	cmp	r8, r9
	movne	r4, #0
	andeq	r4, r4, #1
	cmp	r5, r3
	movne	r9, #0
	andeq	r9, r4, #1
	ldr	r6, [r1, #24]
	ldr	r3, [r10, #24]
	add	r0, r0, #20
	ldr	r5, [r10, #8]
	add	r7, r7, #52
	ldr	r4, [r1, #8]
	cmp	r3, r6
	movne	r3, #0
	andeq	r3, r9, #1
	ldr	r9, [ip, #424]
	cmp	r5, r4
	movne	r6, #0
	andeq	r6, r3, #1
	ldr	r5, [lr, #424]
	ldrb	r3, [ip, #148]	@ zero_extendqisi2
	ldrb	r4, [lr, #148]	@ zero_extendqisi2
	cmp	r5, r9
	movne	r5, #0
	andeq	r5, r6, #1
	ldr	r9, [lr, #420]
	ldr	r6, [ip, #420]
	cmp	r4, r3
	movne	r4, #0
	andeq	r4, r5, #1
	cmp	r9, r6
	movne	r3, #0
	andeq	r3, r4, #1
.L239:
	ldrb	r5, [r2, #1]!	@ zero_extendqisi2
	ldrb	r4, [r0, #1]!	@ zero_extendqisi2
	cmp	r5, r4
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r7
	bne	.L239
	ldrb	r2, [lr, #182]	@ zero_extendqisi2
	add	r7, r10, #80
	ldrb	r6, [ip, #182]	@ zero_extendqisi2
	sub	r0, r8, #1
	ldrb	r5, [lr, #181]	@ zero_extendqisi2
	add	r9, r1, #48
	ldrb	r4, [ip, #181]	@ zero_extendqisi2
	add	r8, r1, #80
	str	r7, [fp, #-56]
	cmp	r2, r6
	cmpeq	r5, r4
	ldrb	r7, [lr, #183]	@ zero_extendqisi2
	ldrb	r4, [ip, #183]	@ zero_extendqisi2
	mov	r5, #0
	ldrb	lr, [lr, #184]	@ zero_extendqisi2
	moveq	r2, #1
	ldrb	ip, [ip, #184]	@ zero_extendqisi2
	movne	r2, #0
	ldrb	r6, [r10, #7]	@ zero_extendqisi2
	cmp	r7, r4
	movne	r2, #0
	andeq	r2, r2, #1
	add	r4, r10, #112
	str	r4, [fp, #-52]
	ldrb	r4, [r1, #7]	@ zero_extendqisi2
	cmp	lr, ip
	movne	ip, #0
	andeq	ip, r2, #1
	add	r7, r1, #112
	str	r1, [fp, #-60]
	cmp	r6, r4
	movne	ip, #0
	andeq	ip, ip, #1
	ldr	r1, [fp, #-56]
	str	r0, [fp, #-48]
	and	r6, r3, ip
	add	r0, r10, #48
	ldr	r2, [fp, #-52]
	str	r10, [fp, #-52]
.L240:
	ldr	r3, [r1, #4]!
	add	r5, r5, #1
	ldr	r10, [r8, #4]!
	ldr	r4, [r0, #4]!
	ldr	lr, [r9, #4]!
	ldr	ip, [r2, #4]!
	cmp	r3, r10
	cmpeq	r4, lr
	ldr	r10, [r7, #4]!
	moveq	r3, #1
	movne	r3, #0
	cmp	ip, r10
	movne	r3, #0
	andeq	r3, r3, #1
	ldr	ip, [fp, #-48]
	and	r6, r6, r3
	cmp	r5, ip
	bls	.L240
	ldr	r10, [fp, #-52]
	ldr	r1, [fp, #-60]
	ldr	r8, [r10, #32]
	ldr	r3, [r1, #32]
	ldr	r4, [r10, #28]
	ldr	r2, [r1, #28]
	cmp	r8, r3
	cmpeq	r4, r2
	moveq	r3, #1
	movne	r3, #0
	cmp	r8, #0
	and	r6, r6, r3
	beq	.L241
	add	r7, r10, #148
	add	r5, r1, #148
	mov	r9, #1
.L242:
	mov	r0, r5
	mov	r2, r7
	mov	r3, #0
.L243:
	ldr	lr, [r2, #4]!
	add	r3, r3, #1
	ldr	ip, [r0, #4]!
	cmp	lr, ip
	movne	r6, #0
	andeq	r6, r6, #1
	cmp	r3, r4
	bls	.L243
	add	r9, r9, #1
	add	r7, r7, #4
	cmp	r9, r8
	add	r5, r5, #4
	bls	.L242
.L241:
	ldrb	r3, [r10, #6]	@ zero_extendqisi2
	ldrb	r2, [r1, #6]	@ zero_extendqisi2
	cmp	r2, r3
	movne	r6, #0
	andeq	r6, r6, #1
	cmp	r3, #0
	beq	.L244
	ldr	r3, [r10, #36]
	ldr	r2, [r10, #40]
	ldr	r4, [r1, #40]
	ldr	lr, [r1, #36]
	ldrb	r0, [r10, #5]	@ zero_extendqisi2
	cmp	r2, r4
	cmpeq	r3, lr
	ldrb	ip, [r1, #5]	@ zero_extendqisi2
	moveq	r3, #1
	movne	r3, #0
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	and	r6, r6, r3
	bne	.L261
.L245:
	ldr	r2, [r10, #48]
	ldr	r3, [r1, #48]
	cmp	r2, r3
	movne	r6, #0
	andeq	r6, r6, #1
.L244:
	eor	r6, r6, #1
	rsb	r0, r6, #0
.L237:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L261:
	ldr	r2, [r10, #44]
	ldr	r3, [r1, #44]
	cmp	r2, r3
	movne	r6, #0
	andeq	r6, r6, #1
	b	.L245
.L260:
	ldr	ip, .L262
	mov	r0, r1
	movw	r3, #1366
.L259:
	ldr	r2, .L262+4
	ldr	r1, .L262+8
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L237
.L263:
	.align	2
.L262:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC43
	.word	.LC44
	UNWIND(.fnend)
	.size	HEVC_VPSEqual, .-HEVC_VPSEqual
	.align	2
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #2292]
	mov	r5, r1
	ldr	r3, [r2, #24]
	mov	r0, r2
	ldr	r4, [r2, #28]
	rsb	r4, r4, r3
	bl	BsIsByteAligned
	cmp	r4, r5, asl #3
	movne	r3, #1
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, #0
	andne	r0, r3, #1
	eor	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.align	2
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	r3, .L272
	mov	r5, r1
	mov	r2, #32
	ldr	r1, [r0, #2292]
	sub	r0, fp, #52
	ldr	r3, [r3, #52]
	mov	r5, r5, asl #3
	blx	r3
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	rsb	r3, r2, r3
	cmp	r3, r5
	movcs	r0, #0
	bcc	.L271
.L266:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L271:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r0, #0
	moveq	r0, #1
	beq	.L266
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
	b	.L267
.L268:
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
.L267:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r4, r5
	mov	r1, #1
	movcs	r3, #0
	movcc	r3, #1
	cmp	r0, #0
	movne	r2, #0
	andeq	r2, r3, #1
	sub	r0, fp, #52
	cmp	r2, #0
	bne	.L268
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L273:
	.align	2
.L272:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	2
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r7, r1
	beq	.L282
	mov	r1, #8
	ldr	r0, [r0, #2292]
	bl	BsGet
	sub	r4, r7, #1
	add	r8, r7, #47
	mov	r3, r0
	cmp	r3, #0
	str	r0, [r7, #48]
	str	r0, [r7, #52]
	bne	.L276
.L287:
	add	r5, r4, #16
.L277:
	mov	r1, #8
	ldr	r0, [r6, #2292]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r5
	bne	.L277
.L278:
	cmp	r5, r8
	mov	r4, r5
	beq	.L283
.L289:
	ldr	r3, [r7, #52]
	cmp	r3, #0
	beq	.L287
.L276:
	cmp	r3, #1
	beq	.L288
	cmp	r3, #2
	addne	r5, r4, #16
	bne	.L278
	mov	r1, #32
	ldr	r0, [r6, #2292]
	bl	BsGet
	add	r5, r4, #16
	cmp	r5, r8
	strb	r0, [r4, #4]
	mov	r2, r0, lsr #24
	mov	r3, r0, lsr #16
	strb	r2, [r4, #1]
	mov	r0, r0, lsr #8
	strb	r3, [r4, #2]
	strb	r0, [r4, #3]
	mov	r4, r5
	bne	.L289
.L283:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L288:
	mov	r1, #16
	ldr	r0, [r6, #2292]
	bl	BsGet
	add	r5, r4, #16
	mov	r3, r0, lsr #8
	strb	r0, [r4, #2]
	strb	r3, [r4, #1]
	b	.L278
.L282:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.align	2
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L292
	ldr	r0, [r0, #2292]
	mov	r1, #1
	bl	BsGet
	mov	r3, r4
	strb	r0, [r5]
.L291:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L292:
	mvn	r3, #0
	b	.L291
	UNWIND(.fnend)
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.align	2
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r6, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L295
	mov	r1, #1
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r6, #4]
	ldr	r0, [r5, #2292]
	bl	BsToNextByte
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L295:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.align	2
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r1
	beq	.L299
	mov	r1, #1
	ldr	r0, [r0, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #2]
	cmp	r0, #0
	beq	.L300
.L298:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L300:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #4]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #3]
	b	.L298
.L299:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.align	2
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
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
	cmp	r2, #15
	mov	r8, r2
	mov	r5, r0
	mov	r7, r1
	addhi	r4, r1, #3
	addhi	r6, r1, #19
	bls	.L309
.L304:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r6
	bne	.L304
	sub	r0, r8, #16
	str	r0, [r7, #20]
	cmp	r0, #0
	movne	r4, #0
	beq	.L310
.L306:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r3, [r7, #20]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L306
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L310:
	str	r0, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L309:
	ldr	r3, .L311
	mov	r0, #1
	ldr	r1, .L311+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L312:
	.align	2
.L311:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	2
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
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
	add	r7, r0, #40960
	mov	r5, r0
	ldr	r3, [r7, #2736]
	cmp	r3, #0
	beq	.L314
	ldr	r4, [r0, #2320]
	cmp	r4, #0
	beq	.L315
	ldr	r2, [r4, #32]
	cmp	r2, #0
	addne	r6, r0, #2320
	movne	r4, #0
	bne	.L320
	b	.L358
.L321:
	ldr	r3, [ip, #520]
	cmp	r3, #0
	beq	.L322
	ldr	r3, [r7, #2736]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L359
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	beq	.L315
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L316
.L320:
	ldr	r1, [r2, #32]
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	bne	.L321
.L322:
	add	r3, r4, #580
	ldr	lr, .L363
	mov	r2, r4
	ldr	r1, .L363+4
	ldr	r3, [r5, r3, asl #2]
	mov	r0, #1
	ldr	r4, [lr, #68]
	ldr	r3, [r3, #32]
	str	ip, [sp]
	blx	r4
.L319:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L359:
	cmp	r3, #0
	beq	.L314
	ldr	r2, [r7, #2740]
	cmp	r2, #0
	beq	.L314
	ldr	r4, [r5, #2388]
	cmp	r4, #0
	beq	.L327
	ldr	r2, [r4, #32]
	cmp	r2, #0
	addne	r6, r5, #2384
	movne	r4, #0
	addne	r6, r6, #4
	bne	.L331
	b	.L360
.L332:
	ldr	r3, [r0, #520]
	cmp	r3, #0
	beq	.L333
	ldr	r3, [r7, #2740]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L314
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	beq	.L361
	ldr	r2, [r3, #32]
	cmp	r2, #0
	beq	.L362
.L331:
	ldr	r1, [r2, #32]
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L332
.L333:
	ldr	ip, .L363
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L363+8
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L353
.L314:
	mov	r0, #0
.L353:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L315:
	ldr	ip, .L363
	mov	r2, r4
	ldr	r1, .L363+12
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	b	.L319
.L358:
	mov	r4, r2
.L316:
	ldr	ip, .L363
	mov	r2, r4
	ldr	r1, .L363+16
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	b	.L319
.L361:
	ldr	r3, [r7, #2736]
.L327:
	ldr	ip, .L363
	mov	r2, r4
	ldr	r1, .L363+20
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L353
.L362:
	ldr	r3, [r7, #2736]
.L328:
	ldr	ip, .L363
	mov	r2, r4
	ldr	r1, .L363+24
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L353
.L360:
	mov	r4, r2
	b	.L328
.L364:
	.align	2
.L363:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC48
	.word	.LC51
	.word	.LC46
	.word	.LC47
	.word	.LC49
	.word	.LC50
	UNWIND(.fnend)
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
	.align	2
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mvn	r4, #0
	str	r4, [r1]
	ldr	r3, [r0, #2492]
	cmp	r3, #16
	bhi	.L366
	cmp	r3, #0
	addne	ip, r0, #2496
	mvnne	r4, #-2147483648
	addne	ip, ip, #12
	movne	r3, #0
	beq	.L368
.L371:
	ldr	r2, [ip, #4]!
	ldr	lr, [r2, #12]
	cmp	lr, r4
	bge	.L370
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	streq	r3, [r1]
	moveq	r4, lr
.L370:
	ldr	r2, [r0, #2492]
	add	r3, r3, #1
	cmp	r2, r3
	bhi	.L371
	ldr	r3, [r1]
	cmn	r3, #1
	beq	.L368
	ldr	r1, .L374
	mov	r0, #1
	str	r4, [sp]
	ldr	r2, .L374+4
	ldr	ip, [r1, #68]
	ldr	r1, .L374+8
	blx	ip
	mov	r0, #0
.L369:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L366:
	ldr	ip, .L374
	mov	r0, #1
	ldr	r2, .L374+4
	ldr	r1, .L374+12
	ldr	ip, [ip, #68]
	blx	ip
	mov	r0, r4
	b	.L369
.L368:
	ldr	r3, .L374
	mov	r0, #1
	ldr	r2, .L374+4
	ldr	r1, .L374+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L369
.L375:
	.align	2
.L374:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+156
	.word	.LC54
	.word	.LC52
	.word	.LC53
	UNWIND(.fnend)
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	2
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, [r0, #2488]
	mov	r4, r0
	cmp	r3, #16
	bhi	.L380
	ldr	r0, [r0, #244]
	bl	FSP_GetTotalValidFsNum
	subs	r3, r0, #0
	ble	.L379
	ldr	r2, [r4, #2488]
	add	r2, r2, #1
	cmp	r3, r2
	bcc	.L379
	ldr	r1, .L381
	mov	r3, r2
	str	r2, [r4, #2488]
	mov	r0, #13
	ldr	r2, .L381+4
	ldr	ip, [r1, #68]
	ldr	r1, .L381+8
	blx	ip
	mov	r0, #0
.L378:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L379:
	ldr	ip, .L381
	mov	r0, #1
	ldr	r2, .L381+4
	ldr	r1, .L381+12
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L378
.L380:
	ldr	r1, .L381
	mov	r5, #17
	ldr	r2, .L381+4
	mov	r0, #1
	str	r5, [sp]
	ldr	ip, [r1, #68]
	ldr	r1, .L381+16
	blx	ip
	str	r5, [r4, #2488]
	mvn	r0, #0
	b	.L378
.L382:
	.align	2
.L381:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+184
	.word	.LC56
	.word	.LC57
	.word	.LC55
	UNWIND(.fnend)
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	2
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
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
	add	r0, r0, #40960
	ldr	r3, [r0, #2648]
	sub	r2, r3, #16
	cmp	r2, #5
	bls	.L384
	ldr	r3, [r0, #2020]
	sub	r3, r3, #16
	cmp	r3, #5
	bls	.L395
	ldr	r3, [r0, #2636]
	cmp	r3, #1
	beq	.L387
	cmp	r3, #2
	beq	.L388
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #2028]
	ldmfd	sp, {fp, sp, pc}
.L384:
	str	r3, [r0, #2020]
	mov	r3, #0
	str	r3, [r0, #2028]
	ldmfd	sp, {fp, sp, pc}
.L387:
	ldr	r2, [r0, #2028]
	cmp	r2, #2
	beq	.L396
	str	r3, [r0, #2028]
	ldmfd	sp, {fp, sp, pc}
.L388:
	ldr	r3, [r0, #2028]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #2028]
	ldmfd	sp, {fp, sp, pc}
.L396:
	ldmfd	sp, {fp, sp, pc}
.L395:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.align	2
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
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
	add	r0, r0, #40960
	ldr	r0, [r0, #2648]
	cmp	r0, #15
	bhi	.L398
	tst	r0, #1
	bne	.L400
.L398:
	sub	r0, r0, #16
	cmp	r0, #7
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L400:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.align	2
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
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
	add	r1, r1, r0, lsl #6
	ldr	r0, [r1, #572]
	ldr	r3, [r1, #576]
	ldrb	ip, [r1, #564]	@ zero_extendqisi2
	ldrb	lr, [r1, #568]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r0, r0
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r0
	str	r3, [r2]
	ldr	r0, [r1, #572]
	ldrb	lr, [r1, #565]	@ zero_extendqisi2
	ldrb	r3, [r1, #577]	@ zero_extendqisi2
	and	r0, r0, #65280
	ldrb	ip, [r1, #569]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #4]
	ldr	r0, [r1, #568]
	ldrb	lr, [r1, #566]	@ zero_extendqisi2
	ldrb	r3, [r1, #578]	@ zero_extendqisi2
	and	r0, r0, #16711680
	ldrb	ip, [r1, #574]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #8]
	ldr	r0, [r1, #576]
	ldrb	r3, [r1, #571]	@ zero_extendqisi2
	ldrb	lr, [r1, #567]	@ zero_extendqisi2
	and	r0, r0, #-16777216
	ldrb	ip, [r1, #575]	@ zero_extendqisi2
	orr	r1, lr, r0
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #12]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.align	2
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #18
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1724]
	ldr	r3, [r0, #1740]
	ldrb	ip, [lr, #564]	@ zero_extendqisi2
	ldrb	r4, [r0, #1732]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1756]
	ldr	r3, [r0, #1772]
	ldrb	ip, [r0, #1748]	@ zero_extendqisi2
	ldrb	r4, [r0, #1764]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1724]
	ldrb	r4, [lr, #565]	@ zero_extendqisi2
	ldrb	r3, [r0, #1741]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1733]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1756]
	ldrb	r4, [r0, #1749]	@ zero_extendqisi2
	ldrb	r3, [r0, #1773]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1765]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1732]
	ldrb	r4, [lr, #566]	@ zero_extendqisi2
	ldrb	r3, [r0, #1742]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1726]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1764]
	ldrb	r4, [r0, #1750]	@ zero_extendqisi2
	ldrb	r3, [r0, #1774]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1758]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1740]
	ldrb	lr, [lr, #567]	@ zero_extendqisi2
	ldrb	r3, [r0, #1735]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1727]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1772]
	ldrb	lr, [r0, #1751]	@ zero_extendqisi2
	ldrb	r3, [r0, #1767]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1759]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1728]
	ldr	r3, [r0, #1744]
	ldrb	ip, [r0, #1720]	@ zero_extendqisi2
	ldrb	lr, [r0, #1736]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1760]
	ldr	r3, [r0, #1776]
	ldrb	ip, [r0, #1752]	@ zero_extendqisi2
	ldrb	lr, [r0, #1768]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1728]
	ldrb	lr, [r0, #1721]	@ zero_extendqisi2
	ldrb	r3, [r0, #1745]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1737]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1760]
	ldrb	lr, [r0, #1753]	@ zero_extendqisi2
	ldrb	r3, [r0, #1777]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1769]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1736]
	ldrb	lr, [r0, #1722]	@ zero_extendqisi2
	ldrb	r3, [r0, #1746]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1730]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1754]	@ zero_extendqisi2
	ldr	r1, [r0, #1768]
	ldrb	r3, [r0, #1778]	@ zero_extendqisi2
	ldrb	ip, [r0, #1762]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1744]
	ldrb	lr, [r0, #1723]	@ zero_extendqisi2
	ldrb	r3, [r0, #1739]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1731]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1776]
	ldrb	ip, [r0, #1755]	@ zero_extendqisi2
	ldrb	r3, [r0, #1771]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1763]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.align	2
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #6
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #964]
	ldr	r3, [r0, #996]
	ldrb	ip, [lr, #564]	@ zero_extendqisi2
	ldrb	r4, [r0, #980]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #972]
	ldr	r3, [r0, #1004]
	ldrb	ip, [r0, #956]	@ zero_extendqisi2
	ldrb	r4, [r0, #988]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #964]
	ldrb	r4, [lr, #565]	@ zero_extendqisi2
	ldrb	r3, [r0, #997]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #981]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #972]
	ldrb	r4, [r0, #957]	@ zero_extendqisi2
	ldrb	r3, [r0, #1005]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #989]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #980]
	ldrb	r4, [lr, #566]	@ zero_extendqisi2
	ldrb	r3, [r0, #998]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #966]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #988]
	ldrb	r4, [r0, #958]	@ zero_extendqisi2
	ldrb	r3, [r0, #1006]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #974]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #996]
	ldrb	lr, [lr, #567]	@ zero_extendqisi2
	ldrb	r3, [r0, #983]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #967]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1004]
	ldrb	lr, [r0, #959]	@ zero_extendqisi2
	ldrb	r3, [r0, #991]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #975]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #968]
	ldr	r3, [r0, #1000]
	ldrb	ip, [r0, #952]	@ zero_extendqisi2
	ldrb	lr, [r0, #984]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #976]
	ldr	r3, [r0, #1008]
	ldrb	ip, [r0, #960]	@ zero_extendqisi2
	ldrb	lr, [r0, #992]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #968]
	ldrb	lr, [r0, #953]	@ zero_extendqisi2
	ldrb	r3, [r0, #1001]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #985]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #976]
	ldrb	lr, [r0, #961]	@ zero_extendqisi2
	ldrb	r3, [r0, #1009]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #993]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #984]
	ldrb	lr, [r0, #954]	@ zero_extendqisi2
	ldrb	r3, [r0, #1002]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #970]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #962]	@ zero_extendqisi2
	ldr	r1, [r0, #992]
	ldrb	r3, [r0, #1010]	@ zero_extendqisi2
	ldrb	ip, [r0, #978]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1000]
	ldrb	lr, [r0, #955]	@ zero_extendqisi2
	ldrb	r3, [r0, #987]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #971]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1008]
	ldrb	ip, [r0, #963]	@ zero_extendqisi2
	ldrb	r3, [r0, #995]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #979]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.align	2
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #12
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1340]
	ldr	r3, [r0, #1356]
	ldrb	ip, [lr, #564]	@ zero_extendqisi2
	ldrb	r4, [r0, #1348]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1372]
	ldr	r3, [r0, #1388]
	ldrb	ip, [r0, #1364]	@ zero_extendqisi2
	ldrb	r4, [r0, #1380]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1340]
	ldrb	r4, [lr, #565]	@ zero_extendqisi2
	ldrb	r3, [r0, #1357]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1349]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1372]
	ldrb	r4, [r0, #1365]	@ zero_extendqisi2
	ldrb	r3, [r0, #1389]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1381]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1348]
	ldrb	r4, [lr, #566]	@ zero_extendqisi2
	ldrb	r3, [r0, #1358]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1342]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1380]
	ldrb	r4, [r0, #1366]	@ zero_extendqisi2
	ldrb	r3, [r0, #1390]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1374]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1356]
	ldrb	lr, [lr, #567]	@ zero_extendqisi2
	ldrb	r3, [r0, #1351]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1343]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1388]
	ldrb	lr, [r0, #1367]	@ zero_extendqisi2
	ldrb	r3, [r0, #1383]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1375]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1344]
	ldr	r3, [r0, #1360]
	ldrb	ip, [r0, #1336]	@ zero_extendqisi2
	ldrb	lr, [r0, #1352]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1376]
	ldr	r3, [r0, #1392]
	ldrb	ip, [r0, #1368]	@ zero_extendqisi2
	ldrb	lr, [r0, #1384]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1344]
	ldrb	lr, [r0, #1337]	@ zero_extendqisi2
	ldrb	r3, [r0, #1361]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1353]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1376]
	ldrb	lr, [r0, #1369]	@ zero_extendqisi2
	ldrb	r3, [r0, #1393]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1385]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1352]
	ldrb	lr, [r0, #1338]	@ zero_extendqisi2
	ldrb	r3, [r0, #1362]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1346]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1370]	@ zero_extendqisi2
	ldr	r1, [r0, #1384]
	ldrb	r3, [r0, #1394]	@ zero_extendqisi2
	ldrb	ip, [r0, #1378]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1360]
	ldrb	lr, [r0, #1339]	@ zero_extendqisi2
	ldrb	r3, [r0, #1355]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1347]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1392]
	ldrb	ip, [r0, #1371]	@ zero_extendqisi2
	ldrb	r3, [r0, #1387]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1379]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.align	2
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #204)
	sub	sp, sp, #204
	add	r0, r0, #24576
	mov	r6, r1
	ldr	ip, [r0, #2608]
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L440
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r4, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2604]
	cmp	r2, #0
	sub	r8, r2, #1
	sub	r2, r7, #1
	str	r2, [fp, #-240]
	ldr	r5, [r3, #72]
	ldr	r1, [r3, #148]
	ble	.L411
	ldr	r3, [fp, #-236]
	add	r2, ip, #214
	sub	r0, fp, #216
	add	lr, r3, #107
	add	lr, ip, lr, lsl #1
.L410:
	ldrsh	r3, [r2, #2]!
	cmp	r2, lr
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L410
.L411:
	cmp	r7, #0
	ble	.L409
	add	r3, r7, #87
	add	r2, ip, #174
	sub	r0, fp, #128
	add	ip, ip, r3, lsl #1
.L414:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L414
.L409:
	mov	r10, #1
	mov	r0, r5
	mov	r10, r10, asl r1
	mov	r1, r10
	bl	__aeabi_idiv
	mov	r1, r10
	mov	r9, r0
	mov	r0, r5
	bl	__aeabi_idivmod
	mov	r0, r6
	cmp	r1, #0
	addne	r9, r9, #1
	mov	r1, r9
	bl	__aeabi_idivmod
	mov	r0, r6
	mov	r5, r1
	mov	r1, r9
	bl	__aeabi_idiv
	cmp	r4, #0
	beq	.L452
	cmp	r8, #0
	mov	r3, #0
	blt	.L431
	sub	r10, fp, #212
	mov	r4, r3
	mov	r6, r3
	mov	r8, r3
	str	r3, [fp, #-232]
	str	r3, [fp, #-244]
.L417:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L434
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	r1, r2
	add	r8, r8, #1
	sub	lr, fp, #128
	mov	r6, r4
	add	r9, r3, r8
	b	.L420
.L432:
	mov	r6, r4
.L420:
	ldr	r3, [lr, #4]!
	add	r1, r1, #1
	add	r3, r3, #1
	add	ip, r2, r3
	cmp	r5, ip
	mla	r4, r8, r3, r4
	bge	.L418
	cmp	r0, r9
	blt	.L450
.L418:
	cmp	r1, r7
	mov	r2, ip
	bne	.L432
.L423:
	add	r2, ip, r3
	cmp	r5, r2
	bge	.L433
	cmp	r0, r9
	blt	.L453
.L433:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	r1, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, r1
	str	r2, [fp, #-244]
	bne	.L417
	rsb	r0, r9, r0
	mov	r2, ip
	rsb	r2, r2, r5
	mul	r3, r0, r3
	add	r3, r2, r3
	add	r6, r3, r6
.L440:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L452:
	cmp	r8, #0
	mov	r3, r4
	blt	.L431
	sub	r10, fp, #212
	mov	lr, r4
	mov	r6, r4
	mov	r8, r4
	str	r4, [fp, #-232]
	str	r4, [fp, #-244]
.L416:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L437
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r4, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L426
.L435:
	mov	r6, lr
.L426:
	ldr	r3, [r4, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r5, r1
	mla	lr, r8, r3, lr
	bge	.L424
	cmp	r0, r9
	blt	.L425
.L424:
	cmp	ip, r7
	mov	r2, r1
	bne	.L435
.L429:
	add	r2, r1, r3
	cmp	r5, r2
	bge	.L449
	cmp	r0, r9
	blt	.L454
.L449:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	bne	.L416
	rsb	r0, r9, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L415
.L450:
	ldr	r1, [fp, #-232]
	rsb	r0, r1, r0
	mul	r3, r0, r3
.L415:
	rsb	r2, r2, r5
	add	r3, r2, r3
	add	r6, r3, r6
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L425:
	cmp	r1, r5
	bgt	.L450
	mov	r1, r2
	b	.L449
.L434:
	ldr	r2, [fp, #-232]
	mov	ip, #0
	add	r9, r2, r8
	b	.L423
.L437:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L429
.L453:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, ip
	mul	r3, r0, r3
	b	.L415
.L454:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L415
.L431:
	mov	r2, r3
	mov	r6, r3
	b	.L415
	UNWIND(.fnend)
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.align	2
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #204)
	sub	sp, sp, #204
	add	r0, r0, #24576
	mov	r7, r1
	ldr	lr, [r0, #2608]
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L479
	ldr	r3, [lr, #72]
	ldr	r8, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2604]
	cmp	r2, #0
	ldr	r4, [r3, #72]
	ldr	ip, [r3, #148]
	ble	.L461
	ldr	r3, [fp, #-232]
	add	r2, lr, #214
	sub	r1, fp, #216
	add	r0, r3, #107
	add	r0, lr, r0, lsl #1
.L460:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L460
.L461:
	cmp	r8, #0
	ble	.L459
	add	r0, r8, #87
	add	r2, lr, #174
	sub	r1, fp, #128
	add	r0, lr, r0, lsl #1
.L464:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L464
.L459:
	mov	r5, #1
	mov	r0, r4
	mov	r5, r5, asl ip
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r5
	mov	r6, r0
	mov	r0, r4
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-232]
	cmp	r1, #0
	addne	r6, r6, #1
	cmp	r3, #0
	str	r6, [fp, #-240]
	ble	.L463
	mov	r9, #0
	ldr	r2, [fp, #-124]
	sub	r0, fp, #212
	mov	r10, r9
	mov	r3, r9
	mov	r1, r9
	mov	r6, r9
	mov	r4, r9
	add	r2, r2, #1
	str	r2, [fp, #-236]
.L465:
	cmp	r8, #0
	ble	.L475
	ldr	r6, [r0]
	ldr	r4, [fp, #-236]
	add	r6, r6, #1
	mla	ip, r6, r4, r3
	cmp	r7, ip
	blt	.L476
	mov	r5, #0
	mov	r1, r3
	mov	r2, r5
	mov	r3, ip
	sub	lr, fp, #124
	b	.L470
.L467:
	ldr	r4, [lr, #4]!
	mov	r1, r3
	add	r4, r4, #1
	mla	ip, r6, r4, r3
	cmp	ip, r7
	bgt	.L468
	mov	r3, ip
.L470:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r8
	bne	.L467
.L469:
	cmp	r3, r7
	bgt	.L474
	ldr	r2, [fp, #-232]
	add	r10, r10, #1
	add	r9, r9, r6
	add	r0, r0, #4
	cmp	r10, r2
	bne	.L465
.L474:
	mov	r3, r1
.L468:
	cmp	r4, #0
	beq	.L463
	rsb	r7, r3, r7
	mov	r1, r4
	mov	r0, r7
	bl	__aeabi_idiv
	ldr	r3, [fp, #-240]
	mov	r1, r4
	add	r4, r0, r9
	mov	r0, r7
	mul	r4, r4, r3
	bl	__aeabi_idivmod
	add	r1, r1, r5
	add	r0, r4, r1
.L479:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L475:
	mov	r5, #0
	b	.L469
.L476:
	ldr	r4, [fp, #-236]
	mov	r5, #0
	b	.L468
.L463:
	ldr	r3, .L481
	mov	r0, #1
	ldr	r1, .L481+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L479
.L482:
	.align	2
.L481:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC58
	UNWIND(.fnend)
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	2
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
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
	ldr	r4, .L506
	mov	r5, r0
	str	r0, [fp, #-60]
	mov	r2, #147456
	mov	r1, #0
	ldr	r3, [r4, #48]
	add	r10, r5, #24576
	ldr	r0, .L506+4
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #36864
	mov	r1, #0
	ldr	r0, .L506+8
	blx	r3
	add	r0, r5, #53760
	ldr	r3, [r4, #48]
	mov	r2, #880
	mov	r1, #0
	add	r0, r0, #248
	blx	r3
	add	r2, r5, #53248
	mov	r3, #0
	str	r2, [fp, #-56]
	str	r3, [r2, #756]
	ldr	r9, [r10, #2608]
	ldr	r1, [r10, #2604]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #240]
	cmp	r2, r3
	strne	r3, [fp, #-72]
	strne	r3, [fp, #-76]
	beq	.L483
.L491:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	add	r2, r2, #108
	streq	r2, [fp, #-80]
	beq	.L492
	mov	r1, r2
	str	r2, [fp, #-80]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-76]
	mov	r2, #0
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	mul	r1, r8, r1
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #756]
	str	r1, [fp, #-68]
.L490:
	add	r1, r2, #6720
	ldr	r0, [fp, #-60]
	add	r1, r1, #30
	add	r1, r0, r1, lsl #3
	str	r3, [r1, #8]
	ldrsh	r1, [r9, r7]
	cmp	r1, #0
	ldreq	r1, [fp, #-48]
	addeq	r1, r1, #88
	streq	r1, [fp, #-64]
	beq	.L486
	ldr	r2, [fp, #-48]
	mov	r5, #0
	ldr	r1, [fp, #-52]
	add	r2, r2, #88
	ldr	r0, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L487:
	ldrsh	r2, [r9, ip]
	cmp	r2, #0
	beq	.L489
	ldr	r2, .L506+4
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r2, r3, lsl #2
.L488:
	add	r1, lr, r3
	str	r1, [r2], #4
	ldr	r9, [r10, #2608]
	add	r3, r3, #1
	rsb	r1, r4, r3
	ldrsh	r0, [r9, ip]
	cmp	r0, r1
	bhi	.L488
.L489:
	ldrsh	r2, [r9, r7]
	add	r5, r5, #1
	add	r6, r6, r8
	cmp	r2, r5
	bhi	.L487
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #756]
.L486:
	ldr	r1, [fp, #-60]
	sub	ip, r3, #1
	ldr	r0, [fp, #-64]
	add	r1, r1, r2, lsl #3
	ldr	lr, [fp, #-48]
	add	r1, r1, #53760
	add	r2, r2, #1
	mov	r0, r0, asl #1
	add	lr, lr, #1
	str	ip, [r1, #252]
	ldr	r1, [fp, #-56]
	str	lr, [fp, #-48]
	str	r2, [r1, #756]
	ldr	r1, [r9, #68]
	ldrsh	r0, [r9, r0]
	cmp	r1, lr
	ldr	r1, [fp, #-52]
	add	r1, r1, r0
	str	r1, [fp, #-52]
	bhi	.L490
.L492:
	ldr	r2, [fp, #-80]
	ldr	r0, [fp, #-72]
	ldr	r1, [r9, #72]
	mov	r2, r2, asl #1
	add	r0, r0, #1
	cmp	r1, r0
	ldr	r1, [fp, #-76]
	ldrsh	r2, [r9, r2]
	str	r0, [fp, #-72]
	add	r2, r1, r2
	str	r2, [fp, #-76]
	bhi	.L491
.L483:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L507:
	.align	2
.L506:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+448
	.word	.LANCHOR3+592
	UNWIND(.fnend)
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	2
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
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
	ldr	r9, .L530
	add	r7, r0, #40960
	mov	r5, r0
	ldr	r1, .L530+4
	ldr	r2, [r7, #2268]
	mov	r0, #2
	ldr	ip, [r9, #68]
	add	r4, r5, #49152
	ldr	r3, [r7, #2052]
	add	r8, r5, #53248
	blx	ip
	ldr	r3, [r9, #68]
	ldr	r1, .L530+8
	mov	r0, #4
	blx	r3
	ldr	r3, [r7, #2264]
	mov	ip, #0
	add	r10, r5, #24576
	add	r1, r5, #2912
	add	r0, r5, #51456
	str	r3, [r4, #3492]
	add	r1, r1, #8
	ldr	r3, [r7, #2176]
	mov	r2, #64
	ldr	lr, [r7, #2180]
	add	r0, r0, #20
	rsb	lr, r3, lr
	str	lr, [r4, #3496]
	ldr	lr, [r7, #2268]
	str	lr, [r4, #3484]
	ldr	lr, [r7, #2052]
	str	lr, [r4, #3488]
	ldr	lr, [r7, #2216]
	str	lr, [r4, #3500]
	ldr	lr, [r7, #2204]
	rsb	r3, r3, lr
	str	r3, [r4, #3504]
	ldr	r3, [r7, #2212]
	rsb	r3, lr, r3
	str	r3, [r4, #3508]
	str	ip, [r5, #208]
	ldr	r3, [r8, #3248]
	str	r3, [r8, #528]
	ldr	r3, [r10, #2604]
	ldrb	ip, [r3, #12]	@ zero_extendqisi2
	strb	ip, [r4, #2204]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r4, #2205]
	ldrb	ip, [r3, #9]	@ zero_extendqisi2
	strb	ip, [r4, #2206]
	ldrb	ip, [r3, #8]	@ zero_extendqisi2
	strb	ip, [r4, #2207]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r4, #2208]
	ldr	ip, [r3, #64]
	str	ip, [r4, #2212]
	ldr	ip, [r3, #116]
	strb	ip, [r4, #2216]
	ldr	ip, [r3, #244]
	sub	ip, ip, #1
	str	ip, [r4, #2220]
	ldr	ip, [r3, #240]
	sub	ip, ip, #1
	str	ip, [r4, #2224]
	ldr	ip, [r7, #2024]
	str	ip, [r4, #2228]
	ldr	ip, [r10, #2608]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r4, #2232]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r4, #2236]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r4, #2237]
	ldr	ip, [r3, #200]
	str	ip, [r4, #2240]
	ldr	ip, [r3, #208]
	str	ip, [r4, #2244]
	ldr	ip, [r3, #188]
	str	ip, [r4, #2248]
	ldr	ip, [r3, #196]
	str	ip, [r4, #2252]
	ldr	ip, [r3, #172]
	str	ip, [r4, #2256]
	ldr	ip, [r3, #180]
	str	ip, [r4, #2260]
	ldr	ip, [r3, #216]
	str	ip, [r4, #2264]
	ldr	ip, [r3, #140]
	str	ip, [r4, #2268]
	ldr	ip, [r3, #148]
	str	ip, [r4, #2272]
	ldr	ip, [r3, #112]
	str	ip, [r4, #2276]
	ldr	lr, [r3, #104]
	ldr	ip, [r9, #52]
	str	lr, [r4, #2280]
	ldr	lr, [r3, #124]
	str	lr, [r4, #2284]
	ldr	lr, [r3, #120]
	str	lr, [r4, #2288]
	ldr	lr, [r3, #108]
	str	lr, [r4, #2292]
	ldr	r3, [r3, #100]
	str	r3, [r4, #2296]
	blx	ip
	ldr	ip, [r10, #2604]
	add	r3, r5, #53504
	add	r1, r5, #52992
	add	r1, r1, #32
	mov	r0, r5
	ldr	lr, [ip, #76]
	mov	r2, r3
	add	r3, r3, #112
	add	r2, r2, #32
	str	lr, [r4, #2388]
	ldr	ip, [ip, #72]
	str	ip, [r4, #2392]
	bl	HEVC_CalcTileInfo
	subs	r6, r0, #0
	bne	.L528
	ldr	r3, [r10, #2608]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r4, #2416]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r4, #2417]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r4, #2418]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r4, #2419]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r4, #2420]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r4, #2421]
	ldr	r2, [r10, #2604]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #148]
	rsb	r2, r1, r2
	str	r2, [r3, #88]
	ldr	r3, [r10, #2608]
	ldr	r2, [r3, #88]
	str	r2, [r4, #2424]
	ldr	r2, [r3, #52]
	str	r2, [r4, #2428]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r4, #2432]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r4, #2433]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r4, #2434]
	ldr	r2, [r3, #60]
	str	r2, [r4, #2436]
	ldr	r2, [r3, #64]
	str	r2, [r4, #2440]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r4, #2444]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r4, #2448]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r4, #2237]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r4, #2236]
	ldr	r3, [r7, #2068]
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	subs	r10, r0, #0
	beq	.L529
	ldr	r2, [r10, #520]
	ldr	r3, [r10, #524]
	cmp	r2, #0
	beq	.L513
	cmp	r3, #0
	beq	.L513
	add	r3, r5, #52736
	add	r2, r5, #52480
	add	r2, r2, #196
	ldr	r0, [r5, #244]
	mov	r1, r3
	add	r3, r3, #160
	add	r1, r1, #68
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r10, #520]
	add	r2, r5, #52736
	ldr	r3, [r3, #4]
	mov	r1, r2
	add	r2, r2, #72
	add	r1, r1, #152
	str	r3, [r4, #3484]
	ldr	r0, [r5, #244]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r7, #2052]
	str	r3, [r4, #3488]
	ldr	r3, [r10, #536]
	str	r3, [r4, #3740]
	ldr	r3, [r10, #524]
	ldr	r3, [r3, #12]
	str	r3, [r8, #748]
	ldr	r3, [r10, #524]
	ldr	r3, [r3, #44]
	str	r3, [r8, #752]
	ldr	ip, [r5, #2784]
	cmp	ip, #0
	str	ip, [r8, #520]
	beq	.L515
	add	r2, r5, #2848
	add	r3, r5, #53504
	add	r2, r2, #4
	add	r3, r3, #196
	mov	r0, r6
.L516:
	add	r0, r0, #1
	ldr	r1, [r2, #4]!
	cmp	r0, ip
	str	r1, [r3, #4]!
	bne	.L516
.L515:
	add	r8, r5, #51456
	mov	r6, #0
	add	r8, r8, #152
.L517:
	mov	r2, r8
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r6, #4
	add	r8, r8, #64
	bne	.L517
	add	r2, r5, #51712
	mov	r0, r6
	add	r2, r2, #152
	mov	r1, r5
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r5, #51712
	add	r2, r2, #216
	mov	r1, r5
	mov	r0, #5
	add	r8, r5, #51968
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r8, #24
	mov	r1, r5
	mov	r0, #0
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r5, #51968
	add	r2, r2, #88
	mov	r1, r5
	mov	r0, #1
	add	r8, r8, #152
	mov	r6, #2
	bl	HEVC_WriteQmatrix_16x16
.L518:
	mov	r2, r8
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r6, #6
	add	r8, r8, #64
	bne	.L518
	add	r2, r5, #52224
	mov	r1, r5
	add	r2, r2, #152
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r5, #52224
	add	r2, r2, #216
	mov	r1, r5
	mov	r0, #1
	add	r8, r5, #52480
	bl	HEVC_WriteQmatrix_32x32
	add	r8, r8, #24
	mov	r6, #0
.L519:
	mov	r2, r8
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_4x4
	cmp	r6, #6
	add	r8, r8, #16
	bne	.L519
	ldr	r1, [r5, #2252]
	mov	r0, #0
	ldr	r3, [r5, #2256]
	ldr	r2, [r5, #2244]
	ldr	ip, [r5, #2248]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3448]
	ldr	r1, [r5, #2268]
	ldr	r3, [r5, #2272]
	ldr	r2, [r5, #2260]
	ldr	ip, [r5, #2264]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3452]
	ldr	r3, [r7, #2052]
	str	r3, [r4, #3480]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L528:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r2, .L530+12
	ldr	r1, .L530+16
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L513:
	ldr	ip, [r9, #68]
	mov	r0, #1
	ldr	r1, .L530+20
	blx	ip
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L529:
	ldr	r2, [r7, #2068]
	mov	r0, #1
	ldr	r3, [r9, #68]
	ldr	r1, .L530+24
	ldr	r2, [r2, #32]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L531:
	.align	2
.L530:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LC60
	.word	.LANCHOR1+208
	.word	.LC61
	.word	.LC63
	.word	.LC62
	UNWIND(.fnend)
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.align	2
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
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
	add	r3, r0, #40960
	ldrb	r3, [r3, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #43520
	addne	r3, r0, #47104
	addeq	r3, r3, #16
	addne	r3, r3, #164
	ldr	ip, [r3, #160]
	ldr	lr, [r3, #164]
	cmp	ip, #16
	bhi	.L566
	cmp	lr, #16
	bhi	.L537
	cmp	ip, #0
	beq	.L538
	ldr	r3, [r0, #2320]
	cmp	r3, #0
	beq	.L551
	ldr	r3, [r3, #32]
	cmp	r3, #0
	addne	r1, r0, #2320
	movne	r2, #0
	bne	.L543
	b	.L567
.L544:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L539
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L540
.L543:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L544
.L538:
	cmp	lr, #0
	beq	.L563
	ldr	r3, [r0, #2388]
	cmp	r3, #0
	beq	.L554
	ldr	r3, [r3, #32]
	cmp	r3, #0
	addne	r0, r0, #2384
	movne	r2, #0
	addne	r0, r0, #4
	bne	.L549
	b	.L568
.L550:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L545
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L546
.L549:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L550
.L563:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L551:
	mov	r2, r3
.L539:
	ldr	r3, .L569
	mov	r0, #0
	ldr	r1, .L569+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L567:
	mov	r2, r3
.L540:
	ldr	r3, .L569
	mov	r0, #0
	ldr	r1, .L569+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L554:
	mov	r2, r3
.L545:
	ldr	r3, .L569
	mov	r0, #0
	ldr	r1, .L569+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L568:
	mov	r2, r3
.L546:
	ldr	r3, .L569
	mov	r0, #0
	ldr	r1, .L569+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L566:
	ldr	lr, .L569
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L569+20
	mov	r0, #0
	ldr	ip, [lr, #68]
	blx	ip
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L537:
	ldr	ip, .L569
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L569+24
	mov	r0, #0
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L570:
	.align	2
.L569:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC66
	.word	.LC67
	.word	.LC68
	.word	.LC69
	.word	.LC64
	.word	.LC65
	UNWIND(.fnend)
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.global	__aeabi_uidivmod
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r4, r0
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-112]
	ldrne	r1, [r4, #208]
	mvnne	r3, #0
	strne	r3, [fp, #-112]
	bne	.L646
	ldr	r0, [r4, #208]
	ldr	r3, [r4, #144]
	cmp	r0, r3
	bcs	.L648
	add	r9, r4, #53248
	mov	r5, #1360
	ldr	r7, [fp, #-112]
	mov	r2, r5
	ldr	r6, [r9, #3248]
	add	r8, r4, #40960
	ldr	r3, .L651
	mov	r1, r7
	mla	r6, r5, r0, r6
	ldr	r3, [r3, #48]
	mov	r0, r6
	blx	r3
	ldr	r3, .L651
	mov	r2, #64
	mov	r1, r7
	sub	r0, fp, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #208]
	ldr	r2, [r4, #144]
	add	r3, r3, #1
	str	r3, [r4, #208]
	cmp	r3, r2
	ldrcc	r2, [r9, #3248]
	ldrcs	r3, [fp, #-112]
	mlacc	r3, r5, r3, r2
	str	r3, [r6, #1356]
	ldr	r3, [r4, #216]
	ldr	r0, [r8, #2652]
	add	r1, r3, #14080
	add	r2, r3, #1
	add	r1, r1, #46
	str	r0, [r4, r1, asl #2]
	ldr	r3, [r4, #172]
	str	r2, [r4, #216]
	add	r3, r3, #1
	str	r3, [r4, #172]
	ldr	r2, [r9, #4056]
	mov	r0, r3, asl #5
	ldr	r1, [r8, #2636]
	sub	r3, r0, r3, asl #2
	str	r3, [fp, #-116]
	add	r3, r2, r3
	str	r1, [r3, #8]
	ldr	r2, [r4, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L577
	add	r0, r6, r1, lsl #2
.L578:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #60]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2316]
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0], #4
	ldr	r2, [r4, #2316]
	add	r3, r2, r3
	ldr	r3, [r3, #64]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2316]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L578
.L577:
	cmp	r3, #1
	addls	r3, r6, r3, lsl #2
	addls	r1, r6, #8
	movls	r2, #0
	bhi	.L583
.L582:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L582
.L583:
	ldrb	r3, [r8, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L649
.L581:
	add	r5, r4, #45056
	ldr	r3, [r5, #2372]
	cmp	r3, #0
	beq	.L584
	add	r0, r4, #2320
	add	r10, r6, #112
	add	lr, r6, #368
	mov	r1, #0
.L585:
	ldr	ip, [r0]
	sub	r7, fp, #44
	add	r1, r1, #1
	ldr	r2, [ip, #32]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	add	r3, r3, #13184
	add	r3, r3, #16
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	str	r3, [r2, #-64]
	ldr	r3, [ip, #16]
	str	r3, [r10, #4]!
	ldr	r3, [r0], #4
	ldr	r3, [r3, #32]
	ldr	r3, [r3, #28]
	str	r3, [lr, #4]!
	ldr	r3, [r5, #2372]
	cmp	r3, r1
	bhi	.L585
	ldr	r2, [r5, #2376]
	cmp	r2, #0
	beq	.L586
.L609:
	add	r1, r4, #2384
	add	r10, r6, #176
	add	r1, r1, #4
	add	lr, r6, #432
	mov	r0, #0
.L587:
	ldr	ip, [r1]
	sub	r7, fp, #44
	add	r0, r0, #1
	ldr	r2, [ip, #32]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	add	r3, r3, #13184
	add	r3, r3, #16
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	str	r3, [r2, #-64]
	ldr	r3, [ip, #16]
	str	r3, [r10, #4]!
	ldr	r3, [r1], #4
	ldr	r3, [r3, #32]
	ldr	r3, [r3, #28]
	str	r3, [lr, #4]!
	ldr	r2, [r5, #2376]
	cmp	r2, r0
	bhi	.L587
	ldr	r3, [r5, #2372]
.L586:
	cmp	r3, #0
	beq	.L588
	ldr	r1, [r6, #372]
	ldr	lr, [r8, #2024]
	add	r1, r1, #728
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	lr, r1
	blt	.L615
	add	ip, r6, #372
	mov	r0, #0
	b	.L590
.L591:
	ldr	r1, [ip, #4]!
	add	r1, r1, #728
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	r1, lr
	bgt	.L615
.L590:
	add	r0, r0, #1
	cmp	r0, r3
	bne	.L591
.L588:
	ldr	r1, [r5, #2272]
	cmp	r1, #0
	bne	.L644
	cmp	r2, #0
	beq	.L644
	ldr	r3, [r6, #436]
	ldr	ip, [r8, #2024]
	add	r3, r3, #728
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	ip, r3
	blt	.L589
	add	r0, r6, #436
	b	.L592
.L593:
	ldr	r3, [r0, #4]!
	add	r3, r3, #728
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, ip
	bgt	.L615
.L592:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L593
.L644:
	mov	r1, #1
.L589:
	strb	r1, [r6, #24]
	ldrb	r3, [r8, #2579]	@ zero_extendqisi2
	strb	r3, [r6, #25]
	ldr	r3, [r5, #2268]
	str	r3, [r6, #28]
	ldrb	r3, [r5, #2222]	@ zero_extendqisi2
	strb	r3, [r6, #32]
	ldr	r3, [r5, #2292]
	str	r3, [r6, #36]
	ldr	r3, [r5, #2272]
	cmp	r3, #0
	bne	.L594
	ldrb	r3, [r5, #2223]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L595
	ldr	r3, [r5, #2324]
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #436]
	mov	r7, r3
.L596:
	str	r7, [r6, #40]
	add	r10, r4, #24576
	ldr	r3, [r5, #2324]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #2223]	@ zero_extendqisi2
	strb	r3, [r6, #52]
	ldr	r3, [r5, #2328]
	str	r3, [r6, #44]
	ldr	r3, [r5, #2380]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #60]
	ldr	r3, [r5, #2384]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #56]
	ldrb	r2, [r5, #2219]	@ zero_extendqisi2
	strb	r2, [r6, #64]
	ldrb	r2, [r5, #2221]	@ zero_extendqisi2
	strb	r2, [r6, #65]
	ldr	r2, [r5, #2372]
	str	r2, [r6, #68]
	ldr	r2, [r5, #2376]
	str	r2, [r6, #72]
	ldr	r2, [r5, #2272]
	str	r2, [r6, #76]
	ldr	r2, [r8, #2656]
	str	r2, [r6, #80]
	ldr	r2, [r10, #2604]
	ldr	r0, [r8, #2656]
	ldr	r1, [r2, #240]
	bl	__aeabi_uidivmod
	str	r1, [r6, #84]
	ldr	r2, [r10, #2604]
	ldr	r0, [r8, #2656]
	ldr	r1, [r2, #240]
	bl	__aeabi_uidiv
	str	r0, [r6, #88]
	mov	r0, r4
	ldr	r1, [r8, #2656]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r6, #92]
	ldr	r2, [r5, #2336]
	str	r2, [r6, #96]
	ldr	r2, [r5, #2340]
	str	r2, [r6, #100]
	ldr	r2, [r5, #2348]
	str	r2, [r6, #104]
	ldr	r2, [r5, #2344]
	str	r2, [r6, #108]
	ldrb	r2, [r5, #2218]	@ zero_extendqisi2
	strb	r2, [r6, #112]
	ldrb	r2, [r5, #2217]	@ zero_extendqisi2
	strb	r2, [r6, #113]
	ldrb	r2, [r5, #2225]	@ zero_extendqisi2
	strb	r2, [r6, #114]
	ldrb	r2, [r5, #2226]	@ zero_extendqisi2
	strb	r2, [r6, #115]
	ldr	r3, [r10, #2608]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L601
	ldr	r2, [r5, #2272]
	cmp	r2, #1
	beq	.L602
.L601:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L650
.L645:
	add	r8, r4, #49152
.L604:
	ldrb	r3, [r5, #2219]	@ zero_extendqisi2
	ldr	r0, [fp, #-116]
	cmp	r3, #0
	subne	r3, fp, #44
	movne	r2, r7
	addne	r10, r3, r2, lsl #2
	ldrne	r3, [r10, #-64]
	strne	r3, [r6, #564]
	mov	r3, #0
	ldr	r2, [r9, #4056]
	ldr	r1, [r4, #2316]
	add	r2, r2, r0
	str	r1, [r2, #24]
	str	r3, [r4, #2316]
	ldrb	r2, [r8, #2421]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L624
	ldr	r0, [r4, #216]
	cmp	r0, #1
	ldreq	r2, [r6, #92]
	streq	r2, [r9, #1640]
	beq	.L608
	add	r1, r4, r0, lsl #3
	ldr	ip, [r6, #92]
	add	r1, r1, #54784
	add	r2, r0, #6848
	add	r2, r2, #11
	sub	ip, ip, #1
	str	ip, [r1, #92]
	sub	r3, r0, #1
	ldr	r1, [r6, #92]
	add	r2, r4, r2, lsl #3
	str	r1, [r2, #8]
.L608:
	ldr	r1, [r8, #2224]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r8, #2220]
	add	r3, r3, #54784
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #108]
	ldr	r1, [r6, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L624
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r6, #568]
.L624:
	ldr	r0, [fp, #-112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L615:
	mov	r1, #0
	b	.L589
.L594:
	cmp	r3, #1
	movne	r3, #0
	movne	r7, r3
	bne	.L596
.L595:
	ldr	r3, [r5, #2324]
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #372]
	mov	r7, r3
	b	.L596
.L649:
	ldr	r3, .L651
	add	r1, r4, #43520
	add	r0, r4, #47104
	add	r1, r1, #16
	movw	r2, #3732
	add	r0, r0, #164
	ldr	r3, [r3, #52]
	blx	r3
	b	.L581
.L650:
	ldr	r3, [r5, #2272]
	cmp	r3, #0
	bne	.L645
.L602:
	ldr	r0, [r5, #3804]
	add	r8, r4, #49152
	ldr	r3, .L651
	add	r1, r4, #49664
	add	r1, r1, #232
	mov	r2, #64
	str	r0, [r6, #580]
	add	r0, r6, #588
	ldr	ip, [r8, #740]
	ldr	r3, [r3, #52]
	str	ip, [r6, #584]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #48896
	mov	r2, #64
	add	r1, r1, #164
	add	r0, r6, #716
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #49920
	mov	r2, #128
	add	r1, r1, #40
	add	r0, r6, #844
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #49920
	add	r0, r6, #1088
	add	r1, r1, #168
	add	r0, r0, #12
	ldr	r3, [r3, #52]
	mov	r2, #128
	blx	r3
	ldr	r3, [r5, #2272]
	cmp	r3, #0
	bne	.L604
	ldr	r3, .L651
	add	r1, r4, #50176
	add	r1, r1, #40
	mov	r2, #64
	add	r0, r6, #652
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #49408
	mov	r2, #64
	add	r1, r1, #164
	add	r0, r6, #780
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #50176
	mov	r2, #128
	add	r1, r1, #104
	add	r0, r6, #972
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, .L651
	add	r1, r4, #50176
	add	r0, r6, #1216
	add	r1, r1, #232
	mov	r2, #128
	ldr	r3, [r3, #52]
	add	r0, r0, #12
	blx	r3
	b	.L604
.L584:
	ldr	r3, [r5, #2376]
	cmp	r3, #0
	bne	.L609
	b	.L644
.L648:
	ldr	ip, .L651
	mov	r2, r0
	ldr	r1, .L651+4
	mov	r0, #1
	mvn	lr, #0
	str	lr, [fp, #-112]
	ldr	ip, [ip, #68]
	blx	ip
	ldr	r1, [r4, #208]
.L646:
	ldr	r2, [r4, #172]
	sub	r1, r1, #1
	ldr	r3, [r4, #216]
	sub	r2, r2, #1
	str	r1, [r4, #208]
	sub	r3, r3, #1
	str	r2, [r4, #172]
	str	r3, [r4, #216]
	b	.L624
.L652:
	.align	2
.L651:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC70
	UNWIND(.fnend)
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	2
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.align	2
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.align	2
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
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
	add	ip, r0, #40960
	add	r1, r0, #49152
	mov	r2, r0
	add	lr, r0, #53248
	ldr	r3, [ip, #2044]
	mov	r0, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #3520]
	ldr	r3, [ip, #2048]
	str	r3, [r1, #3512]
	ldr	r3, [r2, #208]
	str	r3, [lr, #524]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.align	2
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r2, r0, #40960
	ldr	r1, [r0, #2304]
	movw	ip, #2024
	mov	r5, r2
	str	r2, [fp, #-48]
	ldr	r2, [r2, #2652]
	mov	lr, r0
	ldr	r3, [lr, #2300]
	mov	r6, lr
	str	r0, [fp, #-56]
	movw	r0, #15788
	mla	r1, ip, r2, r1
	add	lr, lr, #45056
	str	lr, [fp, #-52]
	mov	r9, #1
	mov	ip, lr
	ldr	lr, [lr, #1768]
	ldr	r2, [ip, #1764]
	ldr	ip, [ip, #1772]
	ldr	r1, [r1, #32]
	add	r10, lr, r2
	cmp	r10, ip
	mla	r3, r0, r1, r3
	ldr	r3, [r3, #128]
	mov	r9, r9, asl r3
	bcs	.L663
	add	r4, r10, #11712
	ldr	r7, [r5, #2024]
	add	r4, r4, #23
	mov	r5, r10
	str	r10, [fp, #-60]
	mov	lr, r6
	add	r4, r6, r4, lsl #2
	mov	r10, ip
	b	.L659
.L673:
	cmp	r10, r5
	bls	.L672
.L659:
	ldr	r6, [r4, #4]!
	mov	r1, r9
	mov	r0, r7
	mov	r8, r7
	ldr	r3, [r4, #-1884]
	cmp	r3, #0
	bne	.L658
	bl	__aeabi_idivmod
	mov	r0, r6
	mov	r8, r1
	mov	r1, r9
	bl	__aeabi_idivmod
	mov	r6, r1
.L658:
	cmp	r8, r6
	add	r5, r5, #1
	bne	.L673
	ldr	r10, [fp, #-60]
	mov	r0, #1
.L657:
	cmp	r10, #0
	beq	.L660
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	lr, [r2, #2624]
	ldr	r3, [r3, #1820]
	ldr	ip, [r2, #2024]
	add	r3, lr, r3
	cmp	ip, r3
	beq	.L667
	ldr	r3, [fp, #-56]
	mov	r1, #0
	add	r7, r3, #46848
	add	r7, r7, #28
	b	.L661
.L662:
	ldr	r3, [r7, #4]!
	add	r3, lr, r3
	cmp	r3, ip
	beq	.L667
.L661:
	add	r1, r1, #1
	cmp	r10, r1
	bne	.L662
.L660:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L667:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L672:
	ldr	r10, [fp, #-60]
	mov	r0, #0
	b	.L657
.L663:
	mov	r0, #0
	b	.L657
	UNWIND(.fnend)
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
	.align	2
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
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
	add	r3, r0, #40960
	str	r3, [fp, #-56]
	mov	ip, r0
	ldr	r3, [r3, #2636]
	cmp	r3, #1
	beq	.L676
	cmp	r3, #2
	beq	.L692
	cmp	r3, #0
	moveq	r3, #2
	beq	.L676
	ldr	ip, .L701
	mov	r0, #1
	ldr	r2, .L701+4
	ldr	r1, .L701+8
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L676:
	add	r8, ip, #43520
	add	r9, ip, #2320
	add	r8, r8, #172
	mov	r7, ip
	mov	r10, #0
	mov	ip, r3
.L689:
	ldr	r0, [r8, #4]!
	cmp	r0, #0
	beq	.L679
	ldr	r2, [r9]
	cmp	r2, #0
	bne	.L693
	mov	r1, r9
	mov	r3, r2
	b	.L681
.L683:
	ldr	r5, [r1, #4]!
	cmp	r5, #0
	bne	.L699
.L681:
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L683
	mov	r3, #255
.L682:
	ldr	r1, [r7, #2308]
	ldr	r1, [r1, #12]
	cmp	r1, #2
	bne	.L684
	ldr	r1, [fp, #-56]
	ldr	r5, [r1, #2068]
	add	r5, r5, #36
.L680:
	sxtb	r3, r3
	str	r3, [fp, #-48]
	mov	r3, r7
	mov	r6, r9
	mov	r7, ip
	mov	r4, #0
	mov	ip, r3
	b	.L690
.L686:
	ldr	r2, [r6, #4]!
.L690:
	cmp	r2, #0
	beq	.L700
.L685:
	ldr	r3, [r8]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L686
	mov	r3, ip
	mov	ip, r7
	mov	r7, r3
.L687:
	add	r10, r10, #1
	add	r9, r9, #68
	cmp	r10, ip
	bcc	.L689
.L692:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L679:
	ldr	r3, [r7, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L687
	mov	r3, #1
	str	r3, [r8]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #2068]
	add	r3, r3, #36
	str	r3, [r9]
	b	.L687
.L700:
	ldr	r3, [fp, #-48]
	mov	r0, #1
	ldr	r2, .L701
	str	r4, [sp]
	str	r3, [sp, #4]
	mov	r3, r10
	ldr	r2, [r2, #68]
	str	ip, [fp, #-52]
	ldr	r1, .L701+12
	mov	ip, r2
	ldr	r2, .L701+4
	blx	ip
	str	r5, [r6]
	ldr	ip, [fp, #-52]
	b	.L685
.L699:
	uxtb	r3, r3
	cmp	r3, #255
	bne	.L680
	b	.L682
.L693:
	mov	r5, r2
	mov	r3, #0
	b	.L680
.L684:
	ldr	ip, .L701
	mov	r3, r10
	ldr	r2, .L701+4
	mov	r0, #1
	ldr	r1, .L701+16
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L702:
	.align	2
.L701:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+228
	.word	.LC71
	.word	.LC73
	.word	.LC72
	UNWIND(.fnend)
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	2
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #156)
	sub	sp, sp, #156
	subs	r7, r0, #0
	beq	.L739
	ldr	r3, .L771
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r7, #2504]
	cmp	lr, #0
	beq	.L740
	mov	r0, #0
	add	r1, r7, #2576
	mov	r3, r0
	b	.L707
.L706:
	cmp	r3, lr
	beq	.L705
.L707:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L706
	ldr	ip, [r2, #52]
	cmp	ip, #0
	bne	.L706
	ldr	ip, [r2, #56]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #36
	addeq	ip, ip, r0, lsl #2
	addeq	r0, r0, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L707
.L705:
	ldr	r4, [r7, #2508]
	cmp	r4, #0
	beq	.L741
	add	r1, r7, #2640
	mov	ip, r0
	add	r1, r1, #4
	mov	r3, #0
	b	.L710
.L709:
	cmp	r3, r4
	beq	.L767
.L710:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L709
	ldr	lr, [r2, #52]
	cmp	lr, #0
	bne	.L709
	ldr	lr, [r2, #56]
	cmp	lr, #1
	subeq	lr, fp, #44
	addeq	r2, r2, #36
	addeq	lr, lr, ip, lsl #2
	addeq	ip, ip, #1
	streq	r2, [lr, #-136]
	cmp	r3, r4
	bne	.L710
.L767:
	rsb	r4, r0, ip
.L708:
	ldr	r5, [r7, #2500]
	cmp	r5, #0
	beq	.L742
	add	lr, r7, #2704
	mov	r9, ip
	add	lr, lr, #8
	mov	r2, #0
	b	.L713
.L712:
	cmp	r2, r5
	beq	.L768
.L713:
	ldr	r3, [lr, #4]!
	add	r2, r2, #1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L712
	ldr	r1, [r3, #52]
	cmp	r1, #1
	bne	.L712
	ldr	r1, [r3, #56]
	sub	r6, fp, #44
	add	r6, r6, r9, lsl #2
	add	r3, r3, #36
	cmp	r1, #0
	addeq	r9, r9, #1
	streq	r3, [r6, #-136]
	cmp	r2, r5
	bne	.L713
.L768:
	rsb	r5, r0, r9
	rsb	r5, r4, r5
.L711:
	cmp	r9, #0
	beq	.L769
	add	r3, r7, #40960
	str	r3, [fp, #-184]
	ldr	r3, [r3, #2636]
	cmp	r3, #0
	str	r3, [fp, #-188]
	beq	.L770
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #2744]
	ldr	r5, [r3, #2748]
	cmp	r4, #0
	str	r4, [r3, #2736]
	str	r5, [r3, #2740]
	beq	.L732
.L738:
	add	r1, r7, #45056
	add	r2, r7, #2304
	add	r8, r7, #46848
	add	r2, r2, #12
	ldrb	r10, [r1, #1952]	@ zero_extendqisi2
	add	r8, r8, #164
	str	r5, [fp, #-192]
	mov	r6, #0
	mov	r5, r10
	mov	r10, r4
	mov	r4, r2
.L725:
	cmp	r5, #0
	mov	r1, r9
	mov	r0, r6
	ldrne	r1, [r8]
	bne	.L724
	bl	__aeabi_uidivmod
.L724:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r3, r3, r1, lsl #2
	cmp	r10, r6
	add	r8, r8, #4
	ldr	r3, [r3, #-136]
	str	r3, [r4, #4]!
	bhi	.L725
	ldr	r3, [fp, #-188]
	ldr	r5, [fp, #-192]
	cmp	r3, #0
	bne	.L766
.L726:
	cmp	r5, #0
	beq	.L728
	add	r2, r7, #45056
	add	r6, r7, #47104
	add	r6, r6, #36
	add	r8, r7, #2384
	ldrb	r10, [r2, #1953]	@ zero_extendqisi2
	mov	r4, #0
.L731:
	cmp	r10, #0
	mov	r1, r9
	mov	r0, r4
	ldrne	r1, [r6]
	bne	.L730
	bl	__aeabi_uidivmod
.L730:
	sub	r3, fp, #44
	add	r4, r4, #1
	add	r3, r3, r1, lsl #2
	cmp	r4, r5
	add	r6, r6, #4
	ldr	r3, [r3, #-68]
	str	r3, [r8, #4]!
	bne	.L731
.L766:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #2736]
	ldr	r5, [r3, #2740]
.L727:
	cmp	r4, #16
	bhi	.L736
.L732:
	add	r4, r4, #576
	add	r2, r7, #2384
	add	r4, r4, #3
	add	r4, r7, r4, lsl #2
.L735:
	ldr	r3, [r7, #2320]
	str	r3, [r4, #4]!
	cmp	r4, r2
	bne	.L735
.L736:
	cmp	r5, #16
	bhi	.L734
	add	r5, r5, #596
	add	r2, r7, #2448
	add	r2, r2, #4
	add	r5, r7, r5, lsl #2
.L737:
	ldr	r3, [r7, #2388]
	str	r3, [r5, #4]!
	cmp	r5, r2
	bne	.L737
.L734:
	mov	r0, #0
.L765:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L770:
	cmp	r4, #0
	beq	.L717
	sub	r3, fp, #180
	ldr	r2, [fp, #-188]
	add	lr, r3, r0, lsl #2
	sub	r1, fp, #116
.L718:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r4
	str	r3, [r1, #4]!
	bne	.L718
.L717:
	cmp	r0, #0
	beq	.L719
	add	r1, r4, #16
	sub	lr, fp, #180
	mov	r2, #0
	add	r1, lr, r1, lsl #2
.L720:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r0
	str	r3, [r1, #4]!
	bne	.L720
	add	r4, r4, r2
.L719:
	cmp	r5, #0
	beq	.L721
	add	r4, r4, #16
	sub	r3, fp, #180
	add	ip, r3, ip, lsl #2
	mov	r2, #0
	add	r4, r3, r4, lsl #2
.L722:
	add	r2, r2, #1
	ldr	r3, [ip], #4
	cmp	r2, r5
	str	r3, [r4, #4]!
	bne	.L722
.L721:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #2744]
	ldr	r5, [r3, #2748]
	cmp	r4, #0
	str	r4, [r3, #2736]
	str	r5, [r3, #2740]
	bne	.L738
	b	.L726
.L769:
	ldr	r3, .L771
	add	r4, r7, #40960
	mov	r2, #136
	mov	r1, r9
	str	r9, [r4, #2736]
	add	r0, r7, #2320
	ldr	ip, [r3, #48]
	str	r9, [r4, #2740]
	blx	ip
	ldr	r2, [r7, #2308]
	ldr	r2, [r2, #12]
	cmp	r2, #2
	bne	.L734
	ldr	r2, [r4, #2068]
	mov	r3, #1
	mov	r0, r9
	str	r3, [r4, #2736]
	add	r3, r2, #36
	str	r3, [r7, #2320]
	b	.L765
.L740:
	mov	r0, lr
	b	.L705
.L741:
	mov	ip, r0
	b	.L708
.L742:
	mov	r9, ip
	b	.L711
.L728:
	ldr	r3, .L771
	add	r0, r7, #2384
	add	r0, r0, #4
	mov	r2, #68
	add	r1, r7, #2320
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #2736]
	str	r4, [r3, #2740]
	mov	r5, r4
	b	.L727
.L739:
	mvn	r0, #0
	b	.L765
.L772:
	.align	2
.L771:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	2
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #40960
	mov	r4, r0
	ldr	r2, [r3, #2636]
	cmp	r2, #2
	beq	.L778
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L779
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L780
	mov	r0, #1
	ldr	r1, .L780+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L778:
	mov	r0, #0
	str	r0, [r3, #2736]
	str	r0, [r3, #2740]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L779:
	ldr	r3, .L780
	mov	r0, #1
	ldr	r1, .L780+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L781:
	.align	2
.L780:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC75
	.word	.LC74
	UNWIND(.fnend)
	.size	HEVC_DecList, .-HEVC_DecList
	.align	2
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, r1, lsl #2
	mov	r4, r0
	ldr	r2, [r5, #2512]
	ldr	r3, [r2, #28]
	cmp	r3, #16
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r3, r3, #696
	mov	lr, #0
	add	r3, r3, #2
	ldr	ip, .L787
	ldr	r1, .L787+4
	mov	r0, #13
	str	lr, [r4, r3, asl #2]
	ldr	r3, [r2, #28]
	ldr	ip, [ip, #68]
	add	r3, r3, #712
	add	r3, r3, #2
	str	lr, [r4, r3, asl #2]
	ldr	r3, [r2, #28]
	add	r3, r3, #728
	add	r3, r3, #2
	str	lr, [r4, r3, asl #2]
	ldr	r3, [r2, #24]
	add	r3, r3, #524
	add	r3, r4, r3, lsl #2
	str	lr, [r3, #4]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	blx	ip
	ldr	r3, [r5, #2512]
	mov	r2, #16
	str	r2, [r3, #28]
	ldr	r3, [r4, #2788]
	sub	r3, r3, #1
	str	r3, [r4, #2788]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L788:
	.align	2
.L787:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC76
	UNWIND(.fnend)
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	2
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
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
	ldr	r3, [r0, #2492]
	mov	r6, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #2496
	mov	r4, #0
	add	r5, r5, #12
	b	.L792
.L791:
	ldr	r3, [r6, #2492]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L795
.L792:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L791
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r3, [r6, #2492]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L792
.L795:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.align	2
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r3, r0, #40960
	ldr	r2, [r0, #2304]
	movw	r4, #2024
	ldr	r1, [r3, #2652]
	movw	ip, #15788
	str	r3, [fp, #-68]
	mov	r9, r0
	ldr	r3, [r0, #2300]
	mov	r0, #1
	mla	r2, r4, r1, r2
	ldr	lr, [r9, #2492]
	cmp	lr, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r8, [r3, #128]
	mov	r3, r0, asl r8
	str	r3, [fp, #-48]
	beq	.L796
	add	r8, r9, #2512
	add	r3, r9, #46848
	add	r7, r9, #45056
	str	r9, [fp, #-56]
	mov	r9, r8
	mov	r2, #0
	add	r3, r3, #28
	str	r2, [fp, #-60]
	str	r3, [fp, #-72]
	str	r0, [fp, #-64]
.L813:
	ldr	r0, [r7, #1764]
	ldr	r2, [r7, #1768]
	ldr	r1, [r7, #1772]
	add	r2, r2, r0
	ldr	r5, [r9]
	cmp	r2, r1
	mov	r8, r2
	movcs	r4, #0
	ldrcs	r0, [r5, #12]
	bcs	.L799
	add	r6, r2, #11712
	ldr	r3, [fp, #-56]
	add	r6, r6, #24
	ldr	r10, [r5, #12]
	mov	r4, #0
	add	r6, r3, r6, lsl #2
.L805:
	ldr	r3, [r6, #-1884]
	cmp	r3, #0
	ldr	r3, [r5, #52]
	beq	.L800
	cmp	r3, #0
	beq	.L801
	ldr	r3, [r6]
	cmp	r3, r10
	beq	.L831
.L801:
	cmp	r4, #0
	bne	.L818
	ldr	r1, [r6]
	mov	r4, r10
	b	.L815
.L800:
	cmp	r3, #0
	beq	.L803
	ldr	r1, [fp, #-48]
	mov	r0, r10
	bl	__aeabi_idivmod
	ldr	r0, [r6]
	str	r1, [fp, #-52]
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	cmp	r3, r1
	beq	.L831
.L803:
	cmp	r4, #0
	bne	.L818
	ldr	r3, [r6]
	mov	r0, r10
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-52]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	mov	r0, r3
	mov	r4, r1
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
.L815:
	ldrb	r0, [r5, #1]	@ zero_extendqisi2
	rsb	r4, r1, r4
	clz	r4, r4
	cmp	r0, #0
	mov	r4, r4, lsr #5
	moveq	r4, #0
	cmp	r4, #0
	bne	.L832
.L818:
	mov	r0, r10
.L804:
	ldr	r3, [r7, #1772]
	add	r8, r8, #1
	add	r6, r6, #4
	mov	r10, r0
	cmp	r8, r3
	bcc	.L805
	ldr	r2, [r7, #1768]
	ldr	r1, [r7, #1764]
	add	r2, r2, r1
.L799:
	ldr	r3, [fp, #-68]
	cmp	r2, #0
	ldrne	r8, [fp, #-72]
	movne	r6, #0
	ldr	ip, [r3, #2624]
	beq	.L807
.L809:
	ldr	r3, [r5, #52]
	add	r6, r6, #1
	cmp	r3, #0
	bne	.L808
	ldr	r3, [r8]
	add	r3, ip, r3
	cmp	r3, r0
	beq	.L833
.L808:
	ldr	r3, [r7, #1768]
	add	r8, r8, #4
	ldr	r2, [r7, #1764]
	add	r3, r3, r2
	cmp	r6, r3
	bcc	.L809
.L807:
	eor	r4, r4, #1
	cmp	r0, ip
	moveq	r0, #0
	andne	r0, r4, #1
	cmp	r0, #0
	beq	.L811
	mov	r3, #0
	strb	r3, [r5, #1]
	ldr	r2, [r9]
	str	r3, [r2, #52]
	ldr	r2, [r9]
	ldr	r1, [r2, #8]
	cmp	r1, #1
	beq	.L811
	ldr	r1, [r2, #32]
	mov	r2, r3
	ldr	r3, [fp, #-56]
	ldr	r0, [r3, #244]
	bl	FSP_SetRef
.L811:
	ldr	r3, [fp, #-56]
	add	r9, r9, #4
	ldr	r2, [r3, #2492]
	ldr	r3, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-60]
	cmp	r3, r2
	bcc	.L813
.L796:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L832:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, r2
	strb	r1, [r5, #1]
	ldr	r3, [r9]
	str	r1, [r3, #52]
	ldr	r3, [r9]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r9]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r9]
	ldr	r0, [r5, #12]
	b	.L804
.L831:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, #1
	strb	r1, [r5, #1]
	ldr	r3, [r9]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r9]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r9]
	ldr	r0, [r5, #12]
	b	.L804
.L833:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, r2
	strb	r1, [r5, #1]
	ldr	r3, [r9]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r9]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r9]
	ldr	r3, [fp, #-68]
	ldr	r0, [r5, #12]
	ldr	ip, [r3, #2624]
	b	.L808
	UNWIND(.fnend)
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.align	2
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
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
	add	r3, r0, #40960
	ldr	r3, [r3, #2648]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L835
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.2
.L835:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.align	2
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
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
	ldr	r3, [r0, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #84]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_SetFrmRepeatCount.part.3
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.align	2
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #57088
	add	r4, r0, #68608
	add	r2, r2, #224
	add	r4, r4, #384
	mov	r5, #0
.L843:
	ldr	r3, [r2, #4]
	cmp	r3, #0
	bne	.L839
	cmp	r2, #0
	beq	.L840
	ldr	lr, [r0, #2492]
	cmp	lr, #0
	beq	.L840
	ldr	r1, [r0, #2512]
	cmp	r1, r2
	beq	.L839
	add	r1, r0, #2512
	b	.L841
.L842:
	ldr	ip, [r1, #4]!
	cmp	ip, r2
	beq	.L839
.L841:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L842
.L840:
	add	r5, r5, #1
.L839:
	add	r2, r2, #584
	cmp	r2, r4
	bne	.L843
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.align	2
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
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
	add	r10, r0, #45056
	mov	r5, r0
	ldr	r1, [r10, #1764]
	cmp	r1, #0
	beq	.L877
	add	r9, r0, #46848
	mov	r7, #0
	add	ip, r0, #40960
	mov	r6, r7
	mov	r8, r9
	add	r9, r9, #8
	add	r8, r8, #28
.L861:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L855
	ldr	r4, [r5, #2492]
	ldr	lr, [ip, #2624]
	ldr	r3, [r8]
	cmp	r4, #0
	add	lr, lr, r3
	beq	.L855
	ldr	r1, [r5, #2512]
	ldr	r3, [r1, #12]
	cmp	r3, lr
	addne	r2, r5, #2512
	movne	r3, #0
	bne	.L858
	b	.L909
.L860:
	ldr	r1, [r2, #4]!
	ldr	r0, [r1, #12]
	cmp	r0, lr
	beq	.L856
.L858:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L860
.L855:
	ldr	r1, [r10, #1764]
	add	r6, r6, #1
	add	r8, r8, #4
	cmp	r1, r6
	bhi	.L861
.L854:
	ldr	r2, [r5, #2488]
	str	r7, [r5, #2504]
	cmp	r2, r7
	addhi	r3, r7, #644
	movhi	r0, #0
	addhi	r3, r5, r3, lsl #2
	bls	.L866
.L865:
	add	r7, r7, #1
	str	r0, [r3, #4]!
	cmp	r7, r2
	bne	.L865
.L866:
	ldr	r8, [r10, #1768]
	add	r8, r1, r8
	cmp	r8, r6
	movls	r7, #0
	bls	.L864
	add	r9, r6, #11712
	add	r10, r6, #46848
	add	r9, r9, #7
	add	r10, r10, #8
	add	r10, r5, r10
	add	ip, r5, #40960
	add	r9, r5, r9, lsl #2
	mov	r7, #0
.L873:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L867
	ldr	r4, [r5, #2492]
	ldr	lr, [ip, #2624]
	ldr	r3, [r9]
	cmp	r4, #0
	add	lr, lr, r3
	beq	.L867
	ldr	r1, [r5, #2512]
	ldr	r3, [r1, #12]
	cmp	r3, lr
	addne	r2, r5, #2512
	movne	r3, #0
	bne	.L870
	b	.L910
.L872:
	ldr	r1, [r2, #4]!
	ldr	r0, [r1, #12]
	cmp	r0, lr
	beq	.L868
.L870:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L872
.L867:
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r8, r6
	bhi	.L873
.L913:
	ldr	r2, [r5, #2488]
.L864:
	cmp	r2, r7
	str	r7, [r5, #2508]
	bls	.L853
	add	r1, r7, #660
	mov	r3, #0
	add	r1, r1, #1
	add	r5, r5, r1, lsl #2
.L875:
	add	r7, r7, #1
	str	r3, [r5, #4]!
	cmp	r7, r2
	bne	.L875
.L853:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L909:
	mov	r3, #0
.L856:
	add	r4, r5, r3, lsl #2
	mov	r2, #1
	strb	r2, [r1, #1]
	ldr	r3, [r4, #2512]
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L911
.L859:
	mov	r2, #1
	str	r2, [r3, #56]
	ldr	r2, [r4, #2512]
	mov	r1, #0
	add	r3, r5, r7, lsl #2
	add	r7, r7, #1
	str	r1, [r2, #52]
	ldr	r2, [r4, #2512]
	str	r2, [r3, #2580]
	b	.L855
.L910:
	mov	r3, #0
.L868:
	add	r4, r5, r3, lsl #2
	mov	r2, #1
	strb	r2, [r1, #1]
	ldr	r3, [r4, #2512]
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L912
.L871:
	mov	r2, #1
	str	r2, [r3, #56]
	ldr	r2, [r4, #2512]
	add	r3, r7, #660
	mov	r1, #0
	add	r6, r6, #1
	add	r3, r3, #2
	cmp	r8, r6
	str	r1, [r2, #52]
	add	r7, r7, #1
	ldr	r2, [r4, #2512]
	add	r9, r9, #4
	str	r2, [r5, r3, asl #2]
	bhi	.L873
	b	.L913
.L911:
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	str	ip, [fp, #-48]
	bl	FSP_SetRef
	ldr	r3, [r4, #2512]
	ldr	ip, [fp, #-48]
	b	.L859
.L912:
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	str	ip, [fp, #-48]
	bl	FSP_SetRef
	ldr	r3, [r4, #2512]
	ldr	ip, [fp, #-48]
	b	.L871
.L877:
	mov	r7, r1
	mov	r6, r1
	b	.L854
	UNWIND(.fnend)
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.align	2
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
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
	add	r3, r0, #40960
	ldr	r2, [r0, #2304]
	movw	ip, #2024
	ldr	r3, [r3, #2652]
	add	r10, r0, #45056
	ldr	lr, [r0, #2300]
	movw	r4, #15788
	ldr	r5, [r10, #1768]
	mov	r1, #1
	mla	ip, ip, r3, r2
	ldr	r2, [r10, #1764]
	ldr	r3, [r10, #1772]
	add	r2, r2, r5
	sub	r2, r2, #1
	sub	r9, r3, #1
	cmp	r9, r2
	ldr	ip, [ip, #32]
	mla	r2, r4, ip, lr
	ldr	r8, [r2, #128]
	mov	r8, r1, asl r8
	ble	.L925
	add	r7, r3, #11712
	add	r3, r3, #46848
	add	r7, r7, #23
	add	r3, r3, #9
	add	r3, r0, r3
	sub	r8, r8, #1
	add	r7, r0, r7, lsl #2
	mov	r6, #0
	str	r6, [fp, #-48]
	mov	r6, r3
	str	r1, [fp, #-52]
.L921:
	ldrb	r3, [r6, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L916
	ldrb	r4, [r7, #-1884]	@ zero_extendqisi2
	ldr	lr, [r7]
	ldr	r5, [r0, #2492]
	cmp	r4, #0
	andeq	lr, lr, r8
	cmp	r5, #0
	ble	.L916
	add	r1, r0, #2496
	mov	r3, #0
	add	r1, r1, #12
	b	.L920
.L919:
	add	r3, r3, #1
	cmp	r3, r5
	beq	.L916
.L920:
	ldr	ip, [r1, #4]!
	cmp	r4, #0
	ldr	r2, [ip, #12]
	andeq	r2, r2, r8
	cmp	lr, r2
	bne	.L919
	ldr	r1, [fp, #-48]
	add	r3, r0, r3, lsl #2
	ldr	lr, [fp, #-52]
	add	r2, r0, r1, lsl #2
	add	r1, r1, #1
	strb	lr, [ip, #1]
	mov	ip, #0
	str	r1, [fp, #-48]
	ldr	r1, [r3, #2512]
	str	ip, [r1, #56]
	ldr	r1, [r3, #2512]
	str	lr, [r1, #52]
	ldr	r3, [r3, #2512]
	str	r3, [r2, #2716]
.L916:
	ldr	r3, [r10, #1764]
	sub	r9, r9, #1
	ldr	r2, [r10, #1768]
	sub	r7, r7, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r9
	blt	.L921
	ldr	r6, [fp, #-48]
	mov	r2, r6
.L915:
	ldr	r3, [r0, #2488]
	str	r2, [r0, #2500]
	cmp	r3, r6
	ble	.L914
	add	r1, r6, #676
	mov	r2, #0
	add	r1, r1, #2
	add	r0, r0, r1, lsl #2
.L923:
	add	r6, r6, #1
	str	r2, [r0, #4]!
	cmp	r6, r3
	bne	.L923
.L914:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L925:
	mov	r2, #0
	mov	r6, r2
	b	.L915
	UNWIND(.fnend)
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.align	2
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	subs	r6, r1, #0
	mov	r5, r0
	beq	.L933
	ldr	ip, [r0, #2784]
	cmp	ip, #0
	beq	.L942
	ldr	r4, [r0, #2792]
	cmp	r4, #0
	addne	r3, r0, #2784
	movne	r4, #0
	addne	r3, r3, #8
	bne	.L937
	b	.L935
.L940:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L935
.L937:
	add	r4, r4, #1
	cmp	r4, ip
	bne	.L940
.L942:
	mvn	r0, #6
.L946:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L935:
	ldr	r1, [r6, #32]
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	subs	r1, r0, #0
	beq	.L938
	ldr	r3, [r1, #520]
	cmp	r3, #0
	beq	.L938
	add	r2, r5, r4, lsl #2
	mov	r0, #1
	ldr	ip, .L947
	mov	r3, r4
	str	r0, [r2, #2792]
	mov	r0, #13
	ldr	lr, [r1, #520]
	ldr	ip, [ip, #68]
	ldr	r1, .L947+4
	ldr	lr, [lr, #4]
	str	lr, [r2, #2856]
	ldr	lr, [r6, #12]
	str	lr, [r2, #2920]
	ldr	r2, [r5, #2788]
	add	r2, r2, #1
	str	r2, [r5, #2788]
	ldr	r2, [r6, #268]
	blx	ip
	mov	r0, #0
	str	r4, [r6, #28]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L938:
	ldrb	ip, [r6, #1]	@ zero_extendqisi2
	ldr	r0, .L947
	ldr	r2, [r6, #32]
	ldr	r3, [r6, #12]
	ldr	r4, [r0, #68]
	mov	r0, #0
	str	r1, [sp, #4]
	str	ip, [sp]
	str	r0, [sp, #8]
	ldr	r1, .L947+8
	blx	r4
	mvn	r0, #6
	b	.L946
.L933:
	ldr	ip, .L947
	mov	r0, r6
	movw	r3, #8209
	ldr	r2, .L947+12
	ldr	r1, .L947+16
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #6
	b	.L946
.L948:
	.align	2
.L947:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC77
	.word	.LC78
	.word	.LC43
	.word	.LC44
	UNWIND(.fnend)
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	2
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r4, r1
	ldr	r0, [r0, #244]
	ldr	r1, [r1, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L950
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L969
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L956
	ldr	r2, [r4, #4]
	ldrb	r1, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L955
	cmp	r1, #1
	beq	.L955
.L966:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L969:
	ldr	r5, .L970
	mov	r0, #13
	ldr	r3, [r4, #32]
	ldr	r1, .L970+4
	str	r2, [sp]
	ldr	ip, [r5, #68]
	ldr	r2, .L970+8
	blx	ip
.L952:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L956
	ldr	ip, [r5, #68]
	mov	r0, #1
	ldr	r3, [r4, #12]
	ldr	r2, .L970+8
	ldr	r1, .L970+12
	blx	ip
	mvn	r0, #2
	b	.L966
.L950:
	ldr	r1, [r4, #8]
	mov	r2, r4
	ldr	r5, .L970
	mov	r0, #1
	ldr	lr, [r4, #32]
	ldr	r3, [r4, #12]
	ldr	ip, [r5, #68]
	stmia	sp, {r1, lr}
	ldr	r1, .L970+16
	blx	ip
	b	.L952
.L955:
	ldr	ip, .L970
	mov	r3, r4
	str	r1, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	ldr	r1, .L970+20
	ldr	ip, [ip, #68]
	ldr	r2, .L970+8
	blx	ip
	mvn	r0, #0
	b	.L966
.L956:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #8]
	b	.L966
.L971:
	.align	2
.L970:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC79
	.word	.LANCHOR1+244
	.word	.LC81
	.word	.LC80
	.word	.LC82
	UNWIND(.fnend)
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	2
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r1, #232]
	add	lr, r0, #24576
	mov	r2, #25600
	mov	r4, r1
	bic	r3, r3, #16128
	str	r2, [r1, #260]
	bic	r3, r3, #3
	ldr	r2, [r1, #16]
	str	r3, [r1, #232]
	ldr	r1, [lr, #2600]
	add	r1, r1, #12288
	ldr	r1, [r1, #180]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	moveq	ip, #0
	beq	.L973
	mov	ip, #256
	movt	ip, 1
	cmp	r1, ip
	movne	ip, #1
	bne	.L973
	add	r1, r0, #4096
	ldr	ip, [r1, #408]
	subs	ip, ip, #1
	movne	ip, #1
.L973:
	ldr	r1, [lr, #2604]
	ldrb	r1, [r1, #2633]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r1, #3072
	beq	.L974
	ldr	r1, [r4, #576]
	cmp	r1, #1
	cmpne	r1, #11
	moveq	r1, #1024
	bne	.L991
.L975:
	ldr	ip, [r4, #580]
	clz	ip, ip
	mov	ip, ip, lsr #5
.L974:
	and	r2, r2, #3
	ldr	lr, [r4, #4]
	orr	r3, r3, r2
	cmp	lr, #0
	orr	r3, r3, #8192
	orr	r3, r3, r1
	ldr	r1, [r4, #32]
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #232]
	ldrne	r3, [r4, #20]
	strne	r3, [r4, #272]
	ldr	r0, [r0, #244]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L992
	mov	r2, #504
	add	r1, r4, #72
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #17
	str	r3, [r5, #384]
	mov	r3, #1
	ldr	r2, [r4, #48]
	strb	r3, [r5, #379]
	cmp	r2, #0
	strb	r3, [r5, #377]
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r5, #372]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L991:
	bic	r1, r1, #8
	cmp	r1, #2
	moveq	r1, #2048
	movne	r1, #3072
	b	.L975
.L993:
	.align	2
.L992:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	2
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r6, r0, #40960
	add	r1, r0, #43008
	mov	r4, r0
	ldr	r5, [r6, #2068]
	mov	r2, #504
	ldr	r3, [r6, #2056]
	add	r1, r1, #24
	add	r0, r5, #72
	str	r3, [r5, #20]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L1016
	ldr	r2, [r5, #20]
	cmp	r2, #0
	str	r2, [r7, #200]
	bne	.L997
.L1002:
	ldrb	r3, [r6, #2016]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1017
.L999:
	mov	r2, #1
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	add	r3, r4, #50944
	ldr	r0, [r4, #244]
	add	r3, r3, #56
	str	r7, [sp]
	mov	r2, r4
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L1018
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #84]
	bcs	.L1019
.L1006:
	ldr	r2, [r4, #268]
	mov	r0, #0
	ldr	r3, [r4, #260]
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
.L996:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L997:
	ldr	r8, [r6, #2028]
	cmp	r8, #0
	beq	.L1020
.L1000:
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcs	.L1002
	ldr	r1, [r5, #32]
	mov	r2, #0
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #2308]
	ldr	ip, .L1021
	mov	r0, #1
	ldr	r3, [r7, #200]
	ldr	r1, [r2, #4]
	ldr	ip, [ip, #68]
	ldr	r2, .L1021+4
	str	r1, [sp]
	ldr	r1, .L1021+8
	blx	ip
	mvn	r0, #0
	b	.L996
.L1017:
	mov	r2, #1
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetRef
	b	.L999
.L1019:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.3
	b	.L1006
.L1020:
	ldr	r3, .L1021
	mov	r0, #1
	ldr	r2, .L1021+4
	ldr	r1, .L1021+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L1021+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1001
	mov	r3, r8
	mov	r2, r8
	mov	r1, #111
	ldr	r0, [r4, #244]
	blx	ip
.L1001:
	ldr	r2, [r7, #200]
	cmp	r2, #0
	bne	.L1000
	b	.L1002
.L1018:
	ldr	r3, .L1021
	mov	r0, #1
	ldr	r2, .L1021+4
	ldr	r1, .L1021+20
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r4, #244]
	ldr	r1, [r5, #32]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L996
.L1016:
	ldr	r3, .L1021
	ldr	r2, .L1021+4
	ldr	r1, .L1021+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L996
.L1022:
	.align	2
.L1021:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+268
	.word	.LC86
	.word	.LC84
	.word	g_event_report
	.word	.LC85
	.word	.LC83
	UNWIND(.fnend)
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	2
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	HEVC_OutputCurrPic
	subs	r5, r0, #0
	bne	.L1026
	add	r3, r4, #40960
	add	r1, r4, #49152
	mov	r2, #1
	mov	ip, #2
	ldr	r0, [r3, #2068]
	str	ip, [r0, #8]
	mov	r0, r5
	str	r2, [r1, #2200]
	ldr	r1, [r3, #2024]
	str	r1, [r4, #212]
	ldr	r3, [r3, #2068]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1026:
	ldr	r3, .L1027
	mov	r0, #1
	ldr	r2, .L1027+4
	ldr	r1, .L1027+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1028:
	.align	2
.L1027:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+288
	.word	.LC87
	UNWIND(.fnend)
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	2
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
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
	cmp	r1, #19
	bhi	.L1031
	mov	r3, #584
	mla	r1, r3, r1, r0
	add	r1, r1, #57088
	ldrb	r0, [r1, #225]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1031:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.align	2
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
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
	mov	r6, r0
	ldr	r0, [r0, #244]
	mov	r8, r1
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1037
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #216
	addne	r5, r0, #232
	movne	r7, #0
	beq	.L1042
.L1036:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L1035
	ldr	r0, [r6, #244]
	bl	FreeUsdByDec
	str	r7, [r4]
.L1035:
	cmp	r4, r5
	bne	.L1036
	ldr	r0, [r6, #244]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1042:
	ldr	r3, .L1043
	mov	r0, #1
	ldr	r1, .L1043+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1037:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1044:
	.align	2
.L1043:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC88
	UNWIND(.fnend)
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	2
	.global	HEVC_ArrangeVahbMem
	.type	HEVC_ArrangeVahbMem, %function
HEVC_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	r7, .L1053
	mov	r5, r1
	mov	r6, r2
	mov	r4, r0
	mov	r2, #32
	ldr	r3, [r7, #48]
	sub	r0, fp, #60
	mov	r1, #0
	blx	r3
	ldr	r2, [r4, #2308]
	str	r6, [fp, #-32]
	mov	r3, #0
	str	r5, [fp, #-52]
	ldr	r2, [r2, #28]
	str	r6, [fp, #-48]
	cmp	r2, #24
	str	r5, [fp, #-44]
	str	r6, [fp, #-40]
	str	r5, [fp, #-36]
	strb	r3, [fp, #-60]
	strb	r3, [fp, #-59]
	beq	.L1046
	ldr	r1, [r4, #2488]
	ldrb	r2, [fp, #12]	@ zero_extendqisi2
	strb	r3, [fp, #-55]
	mov	r3, #5
	strb	r1, [fp, #-56]
	strb	r3, [fp, #-54]
.L1049:
	sub	r1, fp, #60
	ldr	r0, [r4, #244]
	mov	r3, #0
	strb	r2, [fp, #-53]
	mov	r5, #1
	strb	r3, [fp, #-57]
	strb	r5, [fp, #-58]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L1047
	ldr	r1, [r4, #2308]
	sub	r3, fp, #64
	ldr	r0, [r4, #244]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	moveq	r0, r5
	bne	.L1052
.L1051:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1046:
	mov	r1, #5
	strb	r3, [fp, #-56]
	strb	r3, [fp, #-55]
	mov	r2, #1
	strb	r1, [fp, #-54]
	b	.L1049
.L1047:
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r1, .L1053+4
	blx	r3
	mvn	r0, #19
	b	.L1051
.L1052:
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r1, .L1053+8
	blx	r3
	mvn	r0, #19
	b	.L1051
.L1054:
	.align	2
.L1053:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC90
	.word	.LC89
	UNWIND(.fnend)
	.size	HEVC_ArrangeVahbMem, .-HEVC_ArrangeVahbMem
	.align	2
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
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
	add	ip, r0, #57088
	mov	r3, #0
	add	r5, r0, #40960
	add	ip, ip, #224
	mov	r6, r0
	mov	r7, r3
	strb	r3, [r5, #2017]
.L1060:
	ldr	r3, [ip, #4]
	cmp	r3, #0
	bne	.L1056
	cmp	ip, #0
	beq	.L1067
	ldr	lr, [r6, #2492]
	cmp	lr, #0
	beq	.L1067
	ldr	r2, [r6, #2512]
	cmp	r2, ip
	beq	.L1056
	add	r2, r6, #2512
	b	.L1058
.L1059:
	ldr	r1, [r2, #4]!
	cmp	r1, ip
	beq	.L1056
.L1058:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1059
.L1067:
	mov	r3, #584
	add	r0, r5, #2064
	mla	r7, r3, r7, r6
	mov	r2, #101
	mov	r3, #1
	str	r2, [r5, #2056]
	strb	r3, [r5, #2017]
	mov	r2, #504
	add	r1, r7, #57344
	add	r0, r0, #8
	add	r1, r1, #40
	mov	r4, ip
	bl	memcpy
	add	r2, r7, #57088
	str	r4, [r5, #2068]
	mov	r3, #0
	add	r7, r2, #224
	str	r3, [r5, #2272]
	str	r3, [r2, #244]
	strb	r3, [r2, #226]
	strb	r3, [r4]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #52]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #56]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #8]
	ldrb	r1, [r5, #2017]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1065
	ldr	r0, [r6, #244]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r6, #244]
	bl	FSP_GetLogicFs
	mvn	r3, r7
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L1062
	ldr	r3, [r6, #2308]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1070
.L1063:
	ldr	r8, .L1071
	add	r1, r4, #8
	ldr	r0, [r5, #2068]
	mov	r2, #504
	ldr	r3, [r8, #52]
	add	r0, r0, #72
	blx	r3
	ldr	r1, [r5, #2068]
	add	r0, r6, #43008
	ldr	r3, [r8, #52]
	add	r1, r1, #72
	mov	r2, #504
	add	r0, r0, #24
	blx	r3
	ldr	r3, [r5, #2068]
	mov	r0, #0
	str	r7, [r3, #32]
	ldrsb	r3, [r4, #4]
	str	r3, [r5, #2052]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1056:
	add	r7, r7, #1
	add	ip, ip, #584
	cmp	r7, #20
	bne	.L1060
.L1065:
	ldr	r3, .L1071
	mov	r0, #0
	ldr	r1, .L1071+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1070:
	add	r3, r6, #24576
	ldr	r8, [r0, #200]
	ldr	r0, [r0, #112]
	ldr	r2, [r3, #2604]
	ldr	r3, [r2, #76]
	ldr	r2, [r2, #72]
	mul	r8, r8, r3
	str	r2, [r4, #172]
	str	r3, [r4, #176]
	add	r0, r8, r0
	str	r0, [r4, #116]
	bl	MEM_Phy2Vir
	ldr	r3, [r4, #128]
	ldr	r1, [r4, #96]
	add	r3, r8, r3
	ldr	r2, [r4, #200]
	add	r8, r8, r1
	str	r3, [r4, #132]
	str	r8, [r4, #100]
	add	r8, r8, r2
	str	r8, [r4, #108]
	str	r0, [r4, #44]
	mov	r0, r3
	bl	MEM_Phy2Vir
	str	r0, [r4, #60]
	b	.L1063
.L1062:
	ldr	r2, .L1071
	mov	r0, r3
	strb	r3, [r5, #2017]
	ldr	r1, .L1071+8
	ldr	r3, [r2, #68]
	blx	r3
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1072:
	.align	2
.L1071:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC91
	.word	.LC92
	UNWIND(.fnend)
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	2
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	ldr	r0, [r0, #244]
	bl	FSP_GetFspType
	cmn	r0, #1
	mov	r4, r0
	movne	r4, #0
	bne	.L1077
	b	.L1080
.L1076:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1078
	cmp	r4, #64
	beq	.L1081
.L1077:
	mov	r1, r4
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1076
	ldr	r3, .L1082
	mov	r0, #1
	ldr	r1, .L1082+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1078:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1080:
	ldr	r3, .L1082
	mov	r0, #1
	ldr	r1, .L1082+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1081:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1083:
	.align	2
.L1082:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC94
	.word	.LC93
	UNWIND(.fnend)
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	2
	.global	HEVC_WaitVo
	.type	HEVC_WaitVo, %function
HEVC_WaitVo:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WaitVo, .-HEVC_WaitVo
	.align	2
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
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
	mov	r7, r0
	ldr	r0, [r0, #244]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1099
.L1086:
	add	r5, r7, #57600
	add	r8, r7, #68608
	add	r5, r5, #8
	add	r8, r8, #680
	mov	r6, #0
.L1089:
	sub	r4, r5, #16
	strb	r6, [r5, #-295]
	str	r6, [r5, #-292]
.L1088:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L1087
	ldr	r0, [r7, #244]
	bl	FreeUsdByDec
	str	r6, [r4]
.L1087:
	cmp	r4, r5
	bne	.L1088
	add	r5, r4, #584
	cmp	r5, r8
	bne	.L1089
	ldr	r2, [r7, #180]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r3, #0
	add	r7, r7, #2096
	mov	r1, r3
.L1091:
	add	r3, r3, #1
	str	r1, [r7, #4]!
	cmp	r3, r2
	bne	.L1091
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1099:
	add	r0, r7, #50944
	add	r0, r0, #56
	bl	ResetVoQueue
	b	.L1086
	UNWIND(.fnend)
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.align	2
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
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
	add	r6, r0, r1, lsl #2
	mov	r7, #0
	mov	r4, r1
	mov	r5, r0
	ldr	r3, [r6, #2512]
	str	r7, [r3, #4]
	ldr	r3, [r6, #2512]
	ldr	r0, [r0, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1101
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1102
	ldr	r3, [r6, #2512]
	mov	r2, r7
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetDisplay
.L1102:
	ldr	r3, [r6, #2512]
	mov	r2, #0
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
.L1101:
	ldr	r1, [r5, #2492]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #628
	addls	r3, r5, r3, lsl #2
	bhi	.L1105
.L1104:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1104
.L1105:
	add	r3, r1, #628
	mov	r2, #0
	str	r2, [r5, r3, asl #2]
	str	r1, [r5, #2492]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.align	2
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
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
	ldr	r3, [r0, #2492]
	mov	r5, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r7, #0
	mov	r4, r7
	mov	r6, r7
	b	.L1117
.L1116:
	ldr	r3, [r5, #2492]
	add	r4, r4, #1
	cmp	r4, r3
	mov	r7, r4
	bcs	.L1123
.L1117:
	add	r3, r4, #628
	ldr	r3, [r5, r3, asl #2]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1116
	mov	r1, r7
	mov	r0, r5
	strb	r6, [r3]
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r7
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1116
.L1123:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.align	2
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
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
	ldr	r5, [r0, #2492]
	mov	r7, r0
	cmp	r5, #0
	beq	.L1133
	mov	r6, #0
	mvn	r8, #0
	mov	r10, r6
	mov	r9, r6
	b	.L1132
.L1143:
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	cmpne	r3, #3
	ldr	r3, [r4, #2512]
	bne	.L1128
	ldr	r0, [r3, #8]
	cmp	r0, #1
	beq	.L1128
	str	r8, [r3, #32]
	mov	r2, #1
	ldr	r3, [r4, #2512]
	strb	r1, [r3, #1]
	ldr	r3, [r4, #2512]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2512]
.L1128:
	ldr	r3, [r3]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r10, r10, #1
	beq	.L1142
	add	r9, r9, #1
	cmp	r9, r5
	beq	.L1125
.L1132:
	add	r4, r7, r10, lsl #2
	ldr	r0, [r7, #244]
	ldr	r3, [r4, #2512]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1126
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1143
	ldr	r3, [r4, #2512]
	b	.L1128
.L1126:
	ldr	r3, [r4, #2512]
	ldr	r1, [r3, #8]
	cmp	r1, #1
	beq	.L1128
	str	r8, [r3, #32]
	mov	r2, #1
	ldr	r3, [r4, #2512]
	strb	r0, [r3, #1]
	ldr	r3, [r4, #2512]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2512]
	b	.L1128
.L1142:
	mov	r1, r10
	mov	r0, r7
	add	r9, r9, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r9, r5
	mov	r6, #1
	bne	.L1132
.L1125:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1133:
	mov	r6, r5
	b	.L1125
	UNWIND(.fnend)
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.align	2
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #2488]
	mov	r4, r0
	ldr	r2, [r0, #2492]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1147
.L1148:
	ldr	r3, [r4, #2512]
	mov	r5, #0
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r1, [r3, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetRef
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
.L1147:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1148
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.align	2
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
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
	mov	r7, r2
	mvn	r3, #-2147483648
	mov	r2, #0
	str	r2, [r7]
	str	r3, [r1]
	mov	r5, r1
	ldr	r2, [r0, #2492]
	mov	r6, r0
	ldr	r3, [r0, #2488]
	cmp	r2, r3
	bhi	.L1157
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1158:
	add	lr, r6, #2496
	mov	r3, #0
	add	lr, lr, #12
.L1154:
	ldr	r2, [lr, #4]!
	ldr	r4, [r5]
	ldr	ip, [r2, #12]
	cmp	r4, ip
	strgt	ip, [r5]
	strgt	r3, [r7]
	add	r3, r3, #1
	ldr	ip, [r6, #2492]
	cmp	ip, r3
	bhi	.L1154
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1157:
	ldr	ip, .L1159
	mov	r0, #1
	ldr	r1, .L1159+4
	ldr	ip, [ip, #68]
	blx	ip
	ldr	r2, [r6, #2488]
	cmp	r2, #0
	str	r2, [r6, #2492]
	bne	.L1158
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1160:
	.align	2
.L1159:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC95
	UNWIND(.fnend)
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	2
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #40960
	ldr	r5, [r0, #2304]
	movw	r6, #2024
	movw	r4, #15788
	ldr	ip, [r3, #2652]
	ldr	r3, [r0, #2300]
	ldr	lr, [fp, #4]
	mla	ip, r6, ip, r5
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #72]
	ldr	r3, [r3, #76]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1165
	cmp	r2, r3
	beq	.L1166
.L1165:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1166:
	ldr	r3, [r0, #168]
	cmp	r3, #0
	beq	.L1165
	ldr	r3, [r0, #2308]
	ldr	r0, [r3, #900]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.align	2
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0, #2316]
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L1178
	mov	r3, #0
	mov	r2, r4
	mov	r1, r3
.L1169:
	add	r3, r3, #1
	ldr	ip, [r2, #48]
	cmp	r3, lr
	add	r2, r2, #28
	add	r1, r1, ip
	bne	.L1169
.L1168:
	ldr	r2, [r0, #2292]
	mov	r3, lr, asl #5
	sub	lr, r3, lr, asl #2
	add	r4, r4, lr
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #60]
	ldr	r2, [r0, #2316]
	ldr	r3, [r0, #2292]
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, lr, asl #5
	cmp	ip, #0
	sub	r3, r3, lr, asl #2
	add	r4, ip, #7
	add	r3, r2, r3
	movlt	ip, r4
	ldr	r2, [r3, #52]
	add	r2, r2, ip, asr #3
	rsb	r2, r1, r2
	str	r2, [r3, #64]
	ldr	ip, [r0, #2316]
	ldr	r3, [r0, #2292]
	ldrb	r2, [ip, #1]	@ zero_extendqisi2
	ldr	lr, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, ip, r2
	ldr	r3, [r2, #48]
	add	r3, r1, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [r2, #56]
	ldr	r2, [r0, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #64]
	ldr	r1, [r3, #60]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #60]
	ldr	r2, [r0, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #64]
	bic	r2, r2, #3
	str	r2, [r3, #64]
	ldr	r3, [r0, #2316]
	ldr	r2, [r3, #8]
	sub	ip, r2, #1
	cmp	ip, #1
	bhi	.L1185
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	add	lr, r1, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1171
	add	r1, r1, #2
	mov	ip, #0
.L1172:
	sub	r2, r1, #1
	mov	lr, r2, asl #5
	sub	lr, lr, r2, asl #2
	add	r3, r3, lr
	str	ip, [r3, #60]
	ldr	r2, [r0, #2316]
	add	r2, r2, lr
	ldr	r3, [r2, #52]
	str	r3, [r2, #64]
	ldr	r2, [r0, #2316]
	add	r2, r2, lr
	ldr	r3, [r2, #48]
	mov	r3, r3, asl #3
	str	r3, [r2, #56]
	ldr	r3, [r0, #2316]
	add	r3, r3, lr
	ldr	r2, [r3, #64]
	ldr	r4, [r3, #60]
	and	r2, r2, #15
	add	r2, r4, r2, lsl #3
	str	r2, [r3, #60]
	ldr	r2, [r0, #2316]
	add	r3, r2, lr
	ldr	r2, [r3, #64]
	bic	r2, r2, #15
	str	r2, [r3, #64]
	ldr	r3, [r0, #2316]
	ldr	r2, [r3, #8]
	cmp	r1, #1
	cmpls	r1, r2
	add	r1, r1, #1
	movcc	lr, #1
	movcs	lr, #0
	cmp	lr, #0
	bne	.L1172
	sub	ip, r2, #1
.L1171:
	mov	r1, ip, asl #5
	ldr	lr, [r3, #12]
	sub	ip, r1, ip, asl #2
	add	r3, r3, ip
	ldr	r2, [r3, #56]
	rsb	r2, lr, r2
	str	r2, [r3, #56]
	ldr	lr, [r0, #2316]
	ldrb	r1, [lr, #1]	@ zero_extendqisi2
	ldr	r3, [lr, #8]
	cmp	r1, r3
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r3, r1
	add	r0, r0, #40960
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, lr, r3
.L1176:
	ldr	r2, [r3, #64]
	add	r1, r1, #1
	ldr	ip, [r0, #2048]
	add	r3, r3, #28
	cmp	r2, ip
	strcc	r2, [r0, #2048]
	ldr	r2, [lr, #8]
	cmp	r2, r1
	bhi	.L1176
	ldmfd	sp, {r4, fp, sp, pc}
.L1185:
	ldr	r3, .L1186
	mov	r0, #0
	ldr	r1, .L1186+4
	ldr	r3, [r3, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	r3
.L1178:
	mov	r1, lr
	b	.L1168
.L1187:
	.align	2
.L1186:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC96
	UNWIND(.fnend)
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	2
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
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
	add	r2, r0, #40960
	ldr	r3, [r0, #156]
	ldr	r2, [r2, #2652]
	cmp	r2, r3
	bge	.L1196
	movw	r3, #2024
	ldr	r1, [r0, #2304]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1197
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #152]
	cmp	r2, r3
	bge	.L1198
	ldr	r1, [r0, #2300]
	movw	r3, #15788
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1199
	ldr	r2, [r3, #52]
	ldr	r3, [r0, #148]
	cmp	r2, r3
	bcs	.L1200
	movw	r3, #12820
	ldr	r1, [r0, #2296]
	mul	r3, r3, r2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1201
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1196:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1197:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1198:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1199:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1200:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1201:
	ldr	r3, .L1202
	mov	r0, #1
	ldr	r1, .L1202+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1203:
	.align	2
.L1202:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LC102
	UNWIND(.fnend)
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
	.align	2
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #2316]
	ldr	r1, [r0, #200]
	ldr	r3, [r2, #16]
	cmn	r1, #-2147483647
	sub	ip, r3, #16
	beq	.L1236
	cmp	r3, #21
	cmpne	ip, #2
	addls	ip, r0, #40960
	ldrls	lr, [ip, #2624]
	bls	.L1210
.L1218:
	sub	r3, r3, #19
	add	ip, r0, #40960
	cmp	r3, #1
	movls	r1, #-2147483647
	strls	r1, [r0, #200]
	ldr	lr, [ip, #2624]
.L1210:
	cmp	lr, r1
	bge	.L1208
	ldr	r4, [r2, #16]
	sub	r3, r4, #8
	cmp	r3, #1
	bls	.L1237
.L1211:
	ldrb	r1, [r0, #7]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1212
	ldr	r4, [r0, #204]
	cmp	lr, r4
	bge	.L1212
	ldr	r5, [r2, #16]
	sub	r3, r5, #8
	cmp	r3, #1
	bls	.L1238
.L1212:
	ldrb	r3, [ip, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1213
	ldr	r2, [r2, #16]
	sub	r1, r2, #19
	cmp	r1, #1
	bls	.L1233
	cmp	r2, #21
	beq	.L1233
	sub	r2, r2, #16
	cmp	r2, #2
	strls	lr, [r0, #204]
	movls	r3, #1
	strlsb	r3, [r0, #7]
.L1213:
	ldr	r2, [r0, #216]
	ldrb	r3, [ip, #2577]	@ zero_extendqisi2
	cmp	r2, #0
	ldreq	r1, [ip, #2652]
	bne	.L1239
	ldr	r2, [r0, #272]
	cmp	r2, r1
	movne	r0, #1
	beq	.L1240
.L1231:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1236:
	cmp	ip, #5
	bhi	.L1234
	cmp	r3, #21
	cmpne	ip, #2
	bhi	.L1218
	add	ip, r0, #40960
	ldr	lr, [ip, #2624]
	str	lr, [r0, #200]
.L1208:
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1211
	ldr	r4, [r2, #16]
	sub	r3, r4, #8
	cmp	r3, #1
	bhi	.L1211
	ldr	r2, .L1241
	movw	r3, #9313
	str	r1, [sp, #4]
	mov	r0, #1
	str	r4, [sp, #8]
	str	lr, [sp]
	ldr	r1, .L1241+4
	ldr	ip, [r2, #68]
	ldr	r2, .L1241+8
	blx	ip
	mov	r0, #2
	b	.L1231
.L1239:
	add	r2, r2, #14080
	ldr	r1, [ip, #2652]
	add	r2, r2, #45
	ldr	r2, [r0, r2, asl #2]
	cmp	r1, r2
	ldr	r2, [r0, #272]
	movne	r3, #1
	cmp	r2, r1
	movne	r0, #1
	bne	.L1231
	b	.L1240
.L1238:
	ldr	r2, .L1241
	movw	r3, #9323
	stmia	sp, {r1, lr}
	mov	r0, #1
	str	r5, [sp, #12]
	str	r4, [sp, #8]
	ldr	r1, .L1241+12
	ldr	ip, [r2, #68]
	ldr	r2, .L1241+8
	blx	ip
.L1234:
	mov	r0, #2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1240:
	ldr	r0, [r0, #252]
	cmp	r0, lr
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1237:
	ldr	r2, .L1241
	movw	r3, #9305
	str	r1, [sp, #4]
	mov	r0, #1
	str	r4, [sp, #8]
	str	lr, [sp]
	ldr	r1, .L1241+16
	ldr	ip, [r2, #68]
	ldr	r2, .L1241+8
	blx	ip
	mov	r0, #2
	b	.L1231
.L1233:
	str	lr, [r0, #204]
	strb	r3, [r0, #7]
	b	.L1213
.L1242:
	.align	2
.L1241:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC104
	.word	.LANCHOR1+312
	.word	.LC105
	.word	.LC103
	UNWIND(.fnend)
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	2
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #1
	mov	r4, r0
	ldr	r0, [r0, #2292]
	bl	BsGet
	cmp	r0, #0
	beq	.L1248
	ldr	r0, [r4, #2292]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1247
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, .L1249
	ldr	r1, .L1249+4
	ldr	r3, [r3, #68]
	mov	r2, r0
	mov	r0, #19
	blx	r3
.L1247:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1248:
	ldr	r3, .L1249
	mov	r0, #1
	ldr	r1, .L1249+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1250:
	.align	2
.L1249:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC107
	.word	.LC106
	UNWIND(.fnend)
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	2
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
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
	add	r0, r0, #40960
	ldr	r0, [r0, #2648]
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.align	2
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
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
	add	r0, r0, #40960
	ldr	r0, [r0, #2648]
	sub	r0, r0, #19
	cmp	r0, #1
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.align	2
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	subs	r8, r2, #0
	mov	r5, r1
	mov	r4, r0
	str	r3, [fp, #-152]
	moveq	r1, #8
	bne	.L1292
.L1289:
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [fp, #-152]
	cmp	r3, #0
	str	r0, [r5, #284]
	ble	.L1256
	ldr	r3, [fp, #-152]
	add	r6, r5, #42
	add	r9, r3, #42
	mov	r7, r6
	add	r9, r5, r9
	b	.L1258
.L1257:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r7, #1]!
	cmp	r7, r9
	beq	.L1293
.L1258:
	cmp	r8, #0
	beq	.L1257
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r7, #-5]
	b	.L1257
.L1293:
	ldr	r3, [fp, #-152]
	cmp	r3, #7
	ldrle	r7, [fp, #-152]
	ble	.L1262
	b	.L1268
.L1261:
	cmp	r7, #8
	beq	.L1268
.L1262:
	mov	r1, #2
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r7, #1
	cmp	r0, #0
	beq	.L1261
	ldr	r3, .L1294
	mov	r0, #1
	ldr	r1, .L1294+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1256:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1268:
	add	r9, r5, #360
	add	r3, r5, #48
	mov	r7, #0
	b	.L1266
.L1265:
	ldr	r3, [fp, #-152]
	add	r7, r7, #1
	add	r9, r9, #4
	cmp	r3, r7
	mov	r3, r5
	ble	.L1256
.L1266:
	cmp	r8, #0
	beq	.L1290
	ldrb	r2, [r6, #-5]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1288
.L1290:
	add	r5, r3, #32
.L1263:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1265
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r9]
	b	.L1265
.L1288:
	mov	r1, #2
	ldr	r0, [r4, #2292]
	str	r3, [fp, #-156]
	bl	BsGet
	ldr	r3, [fp, #-156]
	mov	r1, #1
	add	r5, r3, #32
	mov	r10, r3
	str	r0, [r9, #-72]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r6, #199]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r9, #-48]
.L1264:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #1]!
	cmp	r10, r5
	bne	.L1264
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #205]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #211]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #217]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #223]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r4, #2292]
	bl	BsGet
	b	.L1263
.L1292:
	mov	r1, #2
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	ldr	r9, .L1294
	mov	r7, r5
	mov	r6, #0
	str	r0, [r5, #276]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r5]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r5, #272]
.L1255:
	mov	r3, r6
	ldr	ip, [r9, #72]
	ldr	r2, .L1294+8
	mov	r1, #100
	sub	r0, fp, #144
	add	r6, r6, #1
	blx	ip
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r6, #32
	strb	r0, [r7, #1]!
	bne	.L1255
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #33]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #34]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #35]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r5, #36]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r2, [r5, #272]
	add	r3, r4, #69632
	mov	r1, #8
	str	r2, [r3, #2824]
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	str	r2, [r3, #2828]
	ldrb	r2, [r5, #3]	@ zero_extendqisi2
	str	r2, [r3, #2832]
	b	.L1289
.L1295:
	.align	2
.L1294:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC109
	.word	.LC108
	UNWIND(.fnend)
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	2
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
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
	ldr	r9, .L1314
	add	r10, r0, #2176
	mov	r6, #0
	add	r3, r0, #2192
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1297:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1305
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #564
	mov	r4, #0
.L1303:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1312
	cmp	r6, #3
	beq	.L1313
	ldr	ip, .L1314+4
	cmp	r4, #2
	ldr	r1, .L1314+8
	movhi	r1, ip
	blx	r3
.L1299:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1303
.L1305:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1297
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1312:
	mov	r2, #16
	ldr	r1, .L1314+12
	mov	r0, r5
	blx	r3
	b	.L1299
.L1313:
	ldr	r0, .L1314+4
	cmp	r4, #0
	ldr	r1, .L1314+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1299
.L1315:
	.align	2
.L1314:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+328
	.word	.LANCHOR4
	.word	.LANCHOR1+392
	UNWIND(.fnend)
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	2
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
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
	add	lr, r0, r2, lsl #2
	mov	ip, r2, asl #3
	sub	r2, ip, r2, asl #1
	mov	r5, #0
	ldr	r7, [lr, #276]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L1317:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1317
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #564]
	orr	ip, lr, ip
	str	ip, [r3, #564]
.L1323:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1317
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #564]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #564]
	b	.L1323
	UNWIND(.fnend)
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.align	2
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
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
	add	r6, r0, #24576
	mov	r5, r0
	ldr	r3, [r6, #2604]
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1325
	ldrb	r3, [r3, #6]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r6, #2608]
	bne	.L1326
	ldrb	r3, [r3, #21]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1344
.L1327:
	ldr	r8, .L1345
	mov	r1, #0
	mov	r2, #1536
	add	r0, r5, #564
	add	r10, r5, #2176
	mov	r7, r1
	ldr	r3, [r8, #48]
	blx	r3
.L1329:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	movne	r9, r7, asl #3
	movne	r4, #0
	subne	r9, r9, r7, asl #1
	beq	.L1333
.L1330:
	add	r0, r9, r4
	ldr	r1, [r6, #2608]
	mov	r3, r4
	mov	r2, r7
	add	r1, r1, r0, lsl #6
	mov	r0, r5
	add	r1, r1, #308
	add	r4, r4, #1
	add	r1, r1, #1
	bl	HEVC_CalScalingList
	ldr	r3, [r10]
	cmp	r4, r3
	bcc	.L1330
.L1333:
	add	r7, r7, #1
	cmp	r7, #4
	bne	.L1329
	ldr	r1, [r6, #2608]
	add	r0, r5, #2192
	add	r0, r0, #4
	ldr	r3, [r8, #52]
	add	r1, r1, #1920
	mov	r2, #96
	add	r1, r1, #8
	blx	r3
.L1325:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1326:
	ldrb	r1, [r3, #21]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1327
	ldr	r8, .L1345
	mov	r2, #1536
	add	r0, r0, #564
	mov	r7, r1
	add	r10, r5, #2176
	ldr	r3, [r8, #48]
	blx	r3
.L1334:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	movne	r9, r7, asl #3
	movne	r4, #0
	subne	r9, r9, r7, asl #1
	beq	.L1338
.L1335:
	add	r0, r9, r4
	ldr	r1, [r6, #2604]
	mov	r3, r4
	mov	r2, r7
	add	r1, r1, r0, lsl #6
	mov	r0, r5
	add	r1, r1, #908
	add	r4, r4, #1
	add	r1, r1, #1
	bl	HEVC_CalScalingList
	ldr	r3, [r10]
	cmp	r4, r3
	bcc	.L1335
.L1338:
	add	r7, r7, #1
	cmp	r7, #4
	bne	.L1334
	ldr	r1, [r6, #2604]
	add	r0, r5, #2192
	ldr	r3, [r8, #52]
	mov	r2, #96
	add	r1, r1, #2528
	add	r0, r0, #4
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1344:
	bl	HEVC_SetDefaultScalingList
	b	.L1325
.L1346:
	.align	2
.L1345:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	2
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
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
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L1348
.L1350:
	.word	.L1354
	.word	.L1352
	.word	.L1352
	.word	.L1353
.L1352:
	ldr	r3, .L1358
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1354:
	ldr	r0, .L1358+4
	ldmfd	sp, {fp, sp, pc}
.L1353:
	ldr	r3, .L1358
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1348:
	ldr	r3, .L1358+8
	mov	r0, #1
	ldr	r1, .L1358+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1359:
	.align	2
.L1358:
	.word	.LANCHOR4+80
	.word	.LANCHOR4+64
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC110
	UNWIND(.fnend)
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	2
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r3
	mov	r7, r1
	mov	r8, r2
	moveq	ip, #1
	movne	ip, #0
	cmp	r0, #0
	orreq	ip, ip, #1
	mov	r6, r0
	cmp	ip, #0
	bne	.L1370
	sub	ip, r3, #1
	mov	r4, #1
	movs	ip, ip, asr #1
	beq	.L1362
.L1363:
	movs	ip, ip, asr #1
	add	r4, r4, #1
	bne	.L1363
.L1362:
	mov	r1, #1
	ldr	r0, [r6, #2292]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1367
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L1367
	mov	r9, r8
	mov	r5, #0
.L1368:
	mov	r1, r4
	ldr	r0, [r6, #2292]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #168]
	cmp	r3, r5
	bhi	.L1368
.L1367:
	ldr	r5, [r7, #60]
	cmp	r5, #0
	beq	.L1385
.L1366:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1385:
	mov	r1, #1
	ldr	r0, [r6, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1366
	ldr	r3, [r7, #172]
	cmp	r3, #0
	beq	.L1366
	add	r8, r8, #128
.L1369:
	mov	r1, r4
	ldr	r0, [r6, #2292]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #172]
	cmp	r3, r5
	bhi	.L1369
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1370:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.align	2
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #2292]
	bl	BsResidBits
	subs	r3, r0, #0
	ble	.L1388
	ldr	r2, [r4, #2316]
	ldr	r0, [r2, #12]
	add	r0, r0, #3
	cmp	r3, r0
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1388:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.align	2
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
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
	ldr	r0, [r0, #2292]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	ble	.L1392
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1392:
	ldr	ip, .L1393
	mov	r0, #1
	ldr	r1, .L1393+4
	ldr	ip, [ip, #68]
	blx	ip
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1394:
	.align	2
.L1393:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC111
	UNWIND(.fnend)
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	2
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
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
	mov	r1, #0
	mov	r6, r0
.L1407:
	ldr	r3, [r6, #2316]
	ldr	ip, [r3, #8]
	sub	ip, ip, #1
	mov	r0, ip, asl #2
	mov	ip, ip, asl #5
	rsb	r2, r0, ip
	add	r2, r3, r2
	add	r2, r2, #40
	ldr	r3, [r2, #8]
	ldr	r2, [r2, #4]
	sub	r3, r3, #1
	add	r3, r2, r3
.L1396:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r0, ip
	cmp	r4, #0
	bne	.L1408
	ldr	r2, [r6, #2316]
	add	r1, r1, #1
	add	lr, r2, r5
	ldr	r2, [r2, #44]
	cmp	r2, r3
	beq	.L1409
	ldr	r2, [lr, #44]
	cmp	r2, r3
	sub	r3, r3, #1
	bne	.L1396
	ldr	r1, [lr, #68]
	ldr	r0, [r6, #244]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2316]
	mov	r1, r4
	add	r5, r3, r5
	str	r4, [r5, #44]
	ldr	r2, [r6, #2316]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1407
.L1408:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1403
.L1404:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1403
	cmp	r3, #8
	bne	.L1404
	ldr	r3, .L1410
	mov	r0, #1
	ldr	r1, .L1410+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1409:
	ldr	r3, .L1410
	mov	r0, #1
	ldr	r1, .L1410+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1403:
	ldr	ip, [r6, #2316]
	mov	r2, #0
	add	r1, r3, r1, lsl #3
	mov	r0, r2
	str	r2, [ip, #4]
	ldr	r3, [r6, #2316]
	str	r1, [r3, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1411:
	.align	2
.L1410:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC113
	.word	.LC112
	UNWIND(.fnend)
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	2
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
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
	ldr	r6, [r0, #160]
	mov	r9, r0
	ldr	r3, [r0, #140]
	cmp	r6, #0
	blt	.L1413
	add	r7, r6, #1
	mov	r0, r3
	mov	r5, #100
	mov	r1, r7
	bl	__aeabi_uidivmod
	add	r2, r9, #53248
	ldr	r8, [r2, #3252]
	mla	r2, r5, r1, r8
	mov	r3, r1
	ldr	r2, [r2, #36]
	cmp	r2, #0
	beq	.L1414
	mov	r4, #0
	b	.L1416
.L1417:
	bl	__aeabi_uidivmod
	mla	r2, r5, r1, r8
	mov	r3, r1
	ldr	r2, [r2, #36]
	cmp	r2, #0
	beq	.L1414
.L1416:
	add	r4, r4, #1
	mov	r1, r7
	cmp	r4, r6
	add	r0, r3, r4
	ble	.L1417
.L1413:
	mvn	r0, #0
	str	r3, [r9, #140]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1414:
	cmp	r3, r7
	mov	r0, r3
	str	r3, [r9, #140]
	bcs	.L1427
	mov	r3, #100
	mov	r2, #1
	mla	r8, r3, r0, r8
	str	r2, [r8, #36]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1427:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.align	2
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r5, r1, #0
	mov	r7, r0
	beq	.L1436
	ldr	r6, .L1437
	add	r8, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #36]
	str	r3, [r5, #40]
.L1431:
	ldr	r3, [r4, #44]
	mov	r0, r7
	cmp	r3, #0
	beq	.L1430
	ldr	r1, [r4, #68]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #48]
	ldr	r3, [r4, #44]
	mov	r0, #7
	ldr	ip, [r6, #68]
	str	r1, [sp]
	ldr	r2, .L1437+4
	ldr	r1, .L1437+8
	blx	ip
	mov	r3, #0
	str	r3, [r4, #44]
	str	r3, [r4, #60]
	str	r3, [r4, #48]
.L1430:
	add	r4, r4, #28
	cmp	r4, r8
	bne	.L1431
	ldr	r3, [r6, #48]
	mov	r0, r5
	mov	r2, #100
	mov	r1, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L1436:
	ldr	ip, .L1437
	mov	r0, r5
	movw	r3, #10600
	ldr	r2, .L1437+12
	ldr	r1, .L1437+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	ip
.L1438:
	.align	2
.L1437:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+408
	.word	.LC114
	.word	.LC43
	.word	.LC44
	UNWIND(.fnend)
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	2
	.global	Hevc_InitDecBuffers
	.type	Hevc_InitDecBuffers, %function
Hevc_InitDecBuffers:
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
	add	r3, r0, #24576
	mov	r8, r0
	add	r0, r0, #2704
	add	r1, r8, #2640
	ldr	r3, [r3, #2604]
	add	r2, r8, #2496
	mov	lr, #0
	add	r1, r1, #4
	add	r2, r2, #12
	add	ip, r8, #2576
	ldr	r3, [r3, #236]
	mov	r6, #17
	add	r3, r3, #1
	cmp	r3, #17
	movhi	r3, #17
	str	r3, [r0, #-216]
	add	r0, r0, #8
	mov	r3, lr
	str	lr, [r8, #2492]
	str	lr, [r8, #2504]
	str	lr, [r8, #2508]
	str	lr, [r8, #2500]
	str	lr, [r8, #2496]
.L1442:
	subs	r6, r6, #1
	str	r3, [r0, #4]!
	str	r3, [ip, #4]!
	str	r3, [r1, #4]!
	str	r3, [r2, #4]!
	bne	.L1442
	add	r4, r8, #57344
	ldr	r10, .L1465
	add	r4, r4, #40
	mov	r7, r6
.L1443:
	ldr	r3, [r10, #48]
	mov	r2, #504
	mov	r0, r4
	mov	r1, #0
	blx	r3
	str	r7, [r4, #196]
	add	r7, r7, #1
	mov	r5, #0
	cmp	r7, #20
	sub	r3, r4, #72
	strb	r5, [r4, #-72]
	mov	r2, #20
	str	r3, [r4, #-4]
	mov	r9, #16
	str	r5, [r4, #-68]
	add	r4, r4, #584
	strb	r5, [r4, #-655]
	str	r5, [r4, #-644]
	strb	r5, [r4, #-654]
	str	r5, [r4, #-608]
	str	r2, [r4, #-632]
	str	r9, [r4, #-628]
	ldr	r3, .L1465
	bne	.L1443
	ldr	r3, [r3, #48]
	mov	r2, #200
	mov	r1, r5
	add	r0, r8, #2784
	blx	r3
	add	r2, r8, #2304
	add	r2, r2, #12
	add	r3, r8, #2384
	mov	r1, r5
	str	r9, [r8, #2784]
	str	r5, [r8, #2788]
.L1444:
	str	r1, [r2, #4]!
	cmp	r2, r3
	mov	r0, #0
	bne	.L1444
	add	r1, r8, #2448
	add	lr, r8, #40960
	add	r1, r1, #4
	mov	ip, r0
	str	r0, [lr, #2736]
.L1445:
	str	ip, [r3, #4]!
	cmp	r3, r1
	mov	r2, #0
	bne	.L1445
	str	r2, [lr, #2740]
	ldr	r1, [r8, #180]
	cmp	r1, r2
	movne	r3, r2
	addne	r2, r8, #2096
	movne	r0, r3
	beq	.L1450
.L1449:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L1449
.L1450:
	ldr	r3, [r8, #160]
	cmp	r3, #0
	beq	.L1464
	mov	r4, #0
	add	r7, r8, #53248
	mov	r5, r4
.L1452:
	ldr	r3, [r7, #4056]
	add	r4, r4, #1
	add	r3, r3, r6
	ldr	r3, [r3, #24]
	cmp	r3, #0
	mov	r1, r3
	beq	.L1451
	ldr	r2, [r8, #2316]
	cmp	r3, r2
	beq	.L1451
	ldr	r0, [r8, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r7, #4056]
	add	r3, r3, r6
	str	r5, [r3, #24]
.L1451:
	ldr	r3, [r8, #160]
	add	r6, r6, #28
	cmp	r3, r4
	bhi	.L1452
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1464:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1466:
	.align	2
.L1465:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Hevc_InitDecBuffers, .-Hevc_InitDecBuffers
	.align	2
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
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
	subs	r6, r0, #0
	beq	.L1478
	ldr	r3, [r6, #2492]
	add	r8, r6, #2496
	cmp	r3, #0
	addne	r8, r8, #12
	movne	r3, #0
	movne	ip, #1
	movne	r1, r8
	beq	.L1493
.L1472:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	ip, [r2, #2]
	ldr	r2, [r6, #2492]
	cmp	r2, r3
	bhi	.L1472
.L1473:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
.L1470:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1474
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L1474:
	ldr	r3, [r4, #2580]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1475
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L1475:
	ldr	r3, [r4, #2648]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1476
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L1476:
	ldr	r3, [r4, #2716]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1477
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L1477:
	subs	r7, r7, #1
	str	r5, [r4, #2716]
	str	r5, [r4, #2648]
	add	r4, r4, #4
	str	r5, [r4, #2576]
	str	r5, [r4, #2508]
	bne	.L1470
	mov	r0, r6
	bl	Hevc_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1493:
	add	r8, r8, #12
	b	.L1473
.L1478:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.align	2
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
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
	mov	r4, r0
	ldr	r0, [r0, #2316]
	cmp	r0, #0
	beq	.L1497
	ldr	r3, [r0, #48]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, .L1498
	mov	r0, #7
	ldr	r1, .L1498+4
	mov	r5, #0
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r4, #2316]
	ldr	ip, [r6, #52]
	ldr	r2, [r3, #48]
	ldr	r0, [r3, #72]
	ldr	r1, [r3, #44]
	rsb	r0, r2, r0
	blx	ip
	ldr	r3, [r4, #2316]
	mov	r0, #1
	ldr	r2, [r3, #96]
	ldr	r1, [r3, #68]
	str	r2, [r3, #68]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #60]
	ldr	r3, [r4, #2316]
	ldr	ip, [r3, #48]
	ldr	r2, [r3, #72]
	rsb	r2, ip, r2
	str	r2, [r3, #44]
	ldr	r3, [r4, #2316]
	ldr	ip, [r3, #48]
	ldr	r2, [r3, #80]
	rsb	r2, ip, r2
	str	r2, [r3, #52]
	ldr	r3, [r4, #2316]
	ldr	r2, [r3, #48]
	ldr	ip, [r3, #76]
	add	r2, r2, ip
	str	r2, [r3, #48]
	ldr	r3, [r4, #2316]
	str	r0, [r3, #8]
	ldr	r0, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2316]
	str	r5, [r3, #72]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #88]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #76]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1497:
	ldr	r3, .L1498
	ldr	r1, .L1498+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1499:
	.align	2
.L1498:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC116
	.word	.LC115
	UNWIND(.fnend)
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	2
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
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
	cmp	r1, #0
	beq	.L1505
	ldr	ip, [r0, #2492]
	cmp	ip, #0
	beq	.L1505
	ldr	r3, [r0, #2512]
	cmp	r3, r1
	beq	.L1507
	add	r0, r0, #2512
	mov	r3, #0
	b	.L1502
.L1503:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1507
.L1502:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1503
.L1505:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1507:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.align	2
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
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
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.align	2
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_u_v, .-HEVC_u_v
	.align	2
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_f_v, .-HEVC_f_v
	.align	2
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L1514
	ldr	ip, .L1515
	movw	r3, #61166
	mov	r2, r0
	movt	r3, 65535
	ldr	r1, .L1515+4
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1514:
	add	r4, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r4
	mov	r0, r5
	bl	BsShow
	mov	r1, r4
	sub	r4, r0, #1
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1516:
	.align	2
.L1515:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC117
	UNWIND(.fnend)
	.size	HEVC_ue_v, .-HEVC_ue_v
	.align	2
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
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
	mov	r5, r0
	ldr	r1, .L1541
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	mov	r1, #1
	str	r0, [r4, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4]
	cmp	r0, #0
	beq	.L1518
	ldr	r3, [r4, #16]
.L1519:
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L1536
.L1523:
	.word	.L1522
	.word	.L1524
	.word	.L1525
	.word	.L1526
	.word	.L1527
.L1518:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #1]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #8
	str	r0, [r4, #12]
	bhi	.L1539
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r3, r0
	str	r0, [r4, #16]
	b	.L1519
.L1527:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r4, #36]
	beq	.L1540
.L1535:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #52]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #56]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #60]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #64]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #68]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #72]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #52]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r3, #0
	str	r0, [r4, #76]
.L1521:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1522:
	mov	r1, #32
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #20]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r3, #0
	str	r0, [r4, #24]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1524:
	mov	r1, #32
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #28]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r3, #0
	str	r0, [r4, #32]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1525:
	ldr	r8, [r4, #12]
	mov	r3, #1
	movs	r8, r3, asl r8
	addne	r7, r4, #2128
	movne	r6, #0
	beq	.L1530
.L1529:
	ldr	r1, [r4, #8]
	add	r6, r6, #1
	ldr	r0, [r5, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	cmp	r8, r6
	str	r0, [r7, #4]!
	bne	.L1529
.L1530:
	ldr	r1, [r4, #8]
	add	r8, r4, r8, lsl #2
	mov	r3, #0
	mov	r2, #1
	mov	r2, r2, asl r1
	mov	r0, r3
	str	r2, [r8, #2132]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1526:
	mov	r1, #16
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #256
	str	r0, [r4, #80]
	bhi	.L1531
	cmp	r0, #0
	addne	r6, r4, #80
	movne	r7, #0
	beq	.L1536
.L1533:
	ldr	r1, [r4, #8]
	add	r7, r7, #1
	ldr	r0, [r5, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	str	r0, [r6, #4]!
	ldr	r1, [r4, #12]
	ldr	r0, [r5, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	str	r0, [r6, #1024]
	ldr	r3, [r4, #80]
	cmp	r3, r7
	bhi	.L1533
.L1536:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1540:
	mov	r1, #32
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #40]
	b	.L1535
.L1539:
	ldr	r3, .L1541+4
	mov	r2, r0
	ldr	r1, .L1541+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1521
.L1531:
	ldr	r3, .L1541+4
	mov	r0, #1
	ldr	r1, .L1541+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1521
.L1542:
	.align	2
.L1541:
	.word	.LC118
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC119
	.word	.LC120
	UNWIND(.fnend)
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	2
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L1552
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	mov	r1, #1
	str	r0, [r5, #12]
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	bne	.L1544
	mov	r1, #7
	ldr	r0, [r4, #2292]
	bl	BsGet
	sub	r3, r0, #3
	str	r0, [r5, #16]
	cmp	r3, #2
	bhi	.L1551
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #6
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r5, #7]
	bne	.L1547
	ldr	r3, [r5, #16]
	cmp	r3, #5
	beq	.L1547
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r5, #24]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r5, #28]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r5, #32]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r5, #36]
.L1547:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #40]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #8]
.L1544:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #9]
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1551:
	ldr	r3, .L1552+4
	mov	r2, r0
	ldr	r1, .L1552+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1553:
	.align	2
.L1552:
	.word	.LC121
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC122
	UNWIND(.fnend)
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	2
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r1
	mov	r6, r2
	mov	r4, r0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L1559
	ldr	r1, .L1565
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	str	r0, [r5, #4]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r3, [r5, #8]
	bne	.L1563
.L1557:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	bne	.L1564
.L1558:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1563:
	ldr	r1, [r6, #8]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r5, #8]
	b	.L1557
.L1564:
	ldr	r1, [r6, #12]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r5, #12]
	b	.L1558
.L1559:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1566:
	.align	2
.L1565:
	.word	.LC123
	UNWIND(.fnend)
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	2
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
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
	mov	r7, r1
	mov	r6, r0
	mov	r1, #4
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r7, #4]
	ldr	r0, [r6, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7]
	ldr	r0, [r6, #2292]
	bl	BsGet
	ldr	r1, .L1574
	strb	r0, [r7, #1]
	ldr	r0, [r6, #2292]
	bl	HEVC_ue_v
	cmp	r0, #15
	str	r0, [r7, #8]
	bgt	.L1568
	cmp	r0, #0
	addge	r5, r7, #8
	movge	r4, #0
	blt	.L1572
.L1571:
	ldr	r1, .L1574+4
	add	r4, r4, #1
	ldr	r0, [r6, #2292]
	bl	HEVC_ue_v
	str	r0, [r5, #4]!
	ldr	r3, [r7, #8]
	cmp	r3, r4
	bge	.L1571
.L1572:
	ldr	r0, [r6, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1568:
	ldr	r3, .L1574+8
	mov	r0, #1
	ldr	r1, .L1574+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1575:
	.align	2
.L1574:
	.word	.LC124
	.word	.LC126
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC125
	UNWIND(.fnend)
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	2
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
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
	mov	r5, r1
	mov	r6, r0
	ldr	r1, .L1609
	ldr	r0, [r0, #2292]
	mov	r8, r2
	bl	HEVC_ue_v
	cmp	r0, #15
	str	r0, [r5, #4]
	bhi	.L1604
	ldrb	r3, [r8, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1579
	ldrb	r0, [r5]	@ zero_extendqisi2
.L1580:
	cmp	r0, #0
	bne	.L1605
.L1581:
	mov	r1, #1
	ldr	r0, [r6, #2292]
	bl	BsGet
	strb	r0, [r5, #1]
	ldr	r1, [r8, #32]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r5, #16]
	ldr	r2, [r8, #48]
	cmp	r2, #31
	bhi	.L1606
.L1582:
	mov	r4, #0
	cmp	r4, #0
	mov	r9, r5
	mov	r7, #1
	beq	.L1607
.L1583:
	cmp	r4, #1
	beq	.L1608
.L1587:
	cmp	r7, #1
	bhi	.L1586
.L1585:
	add	r4, r4, #1
	add	r7, r7, #1
	cmp	r4, #0
	add	r9, r9, #16
	bne	.L1583
.L1607:
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1587
	ldr	r3, [r8, #48]
	cmn	r3, #1
	movne	r10, r9
	movne	r3, r4
	beq	.L1585
.L1599:
	ldr	r1, [r8, #28]
	add	r3, r3, #1
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	str	r3, [fp, #-48]
	str	r3, [fp, #-52]
	bl	BsGet
	str	r0, [r10, #20]
	ldr	r1, [r8, #28]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldr	r3, [fp, #-48]
	str	r0, [r10, #24]
	ldrb	r2, [r8, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1589
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1590
.L1589:
	ldr	r1, [r8, #28]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	str	r3, [fp, #-48]
	bl	BsGet
	str	r0, [r10, #28]
	ldr	r1, [r8, #28]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldr	r3, [fp, #-48]
	str	r0, [r10, #32]
.L1590:
	ldr	r2, [r8, #48]
	add	r10, r10, #32
	add	r2, r2, #1
	cmp	r2, r3
	bhi	.L1599
	b	.L1587
.L1586:
	ldr	r0, [r6, #2292]
	bl	BsToNextByte
	mov	r0, #0
.L1603:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1606:
	ldr	r3, .L1609+4
	mov	r0, #1
	ldr	r1, .L1609+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #0
	str	r3, [r8, #48]
	b	.L1582
.L1605:
	ldr	r1, [r8, #32]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r5, #8]
	ldr	r1, [r8, #36]
	ldr	r0, [r6, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r5, #12]
	b	.L1581
.L1579:
	mov	r1, #1
	ldr	r0, [r6, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5]
	b	.L1580
.L1604:
	ldr	r3, .L1609+4
	mov	r2, r0
	ldr	r1, .L1609+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1603
.L1608:
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1586
	ldr	r3, [r8, #48]
	cmn	r3, #1
	beq	.L1586
	mov	r10, r9
	mov	r3, #0
	b	.L1599
.L1610:
	.align	2
.L1609:
	.word	.LC127
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC129
	.word	.LC128
	UNWIND(.fnend)
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	2
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
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
	ldrb	r3, [r2, #9]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #0
	bne	.L1637
.L1612:
	ldr	r6, .L1640
	sub	r3, r6, #3456
	ldrh	r3, [r3, #-8]
	cmp	r3, #0
	beq	.L1615
	ldr	r1, [r6, #-3432]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r5, #12]
	ldr	r1, [r6, #-3428]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r6, #-3462]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #16]
	bne	.L1638
.L1615:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1637:
	mov	r1, #4
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #2
	str	r0, [r5, #4]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #8]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5]
	b	.L1612
.L1638:
	ldr	r1, [r6, #-3452]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r6, #-3462]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #20]
	beq	.L1615
	ldrb	r3, [r6, #-3461]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1615
	ldr	r1, .L1640+4
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	mov	r1, #1
	str	r0, [r5, #24]
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L1639
.L1616:
	ldr	r3, [r5, #24]
	cmp	r3, #255
	bhi	.L1619
	add	r8, r5, #28
	mov	r7, #0
	b	.L1618
.L1617:
	ldr	r3, [r5, #24]
	cmp	r3, r7
	bcc	.L1615
.L1618:
	ldr	r1, .L1640+8
	add	r7, r7, #1
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	str	r0, [r8, #4]!
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1617
	ldr	r1, [r6, #-3456]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r8, #1024]
	b	.L1617
.L1639:
	ldr	r1, [r6, #-3456]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r5, #28]
	b	.L1616
.L1619:
	ldr	r3, .L1640+12
	mov	r0, #1
	ldr	r1, .L1640+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1641:
	.align	2
.L1640:
	.word	.LANCHOR5
	.word	.LC130
	.word	.LC132
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC131
	UNWIND(.fnend)
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	2
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r6, r3, #0
	mov	r5, r0
	mov	r10, r1
	mov	r4, r2
	streq	r6, [r2]
	bne	.L1684
.L1645:
	ldr	r1, .L1692
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #16]
	bhi	.L1685
	ldr	r1, .L1692+4
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #20]
	bhi	.L1686
	ldr	r6, [r4, #16]
	add	r2, r0, r6
	str	r2, [r4, #24]
	cmp	r2, #16
	bhi	.L1670
	cmp	r6, #0
	addne	r10, r4, #68
	addne	r9, r4, #52
	movne	r7, #0
	movne	r8, r7
	beq	.L1672
.L1673:
	ldr	r1, .L1692+8
	add	r7, r7, #1
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	mov	r1, #1
	mvn	r0, r0
	add	r8, r8, r0
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4, #16]
	cmp	r6, r7
	bhi	.L1673
	ldr	r2, [r4, #24]
.L1672:
	cmp	r2, r6
	bls	.L1661
	add	r8, r6, #17
	add	r9, r6, #52
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L1674:
	ldr	r1, .L1692+12
	add	r6, r6, #1
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #24]
	cmp	r3, r6
	bhi	.L1674
.L1661:
	mov	r0, #0
.L1650:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1684:
	mov	r1, #1
	ldr	r0, [r0, #2292]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4]
	beq	.L1645
	ldr	r7, [r10, #228]
	cmp	r7, r6
	subne	r6, r6, #1
	movne	r3, #0
	strne	r3, [r4, #4]
	beq	.L1687
.L1649:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L1692+16
	mov	r9, #204
	mul	r9, r9, r6
	str	r0, [r4, #8]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #8]
	add	r2, r10, r9
	mov	r3, r3, asl #1
	rsb	r3, r3, #1
	add	r0, r0, #1
	str	r0, [r4, #12]
	ldr	r2, [r2, #2756]
	mul	r3, r3, r0
	cmp	r2, #16
	str	r3, [fp, #-60]
	bhi	.L1688
	add	r6, r9, #2800
	mov	r7, #0
	add	r6, r6, #4
	add	r8, r4, #35
	str	r4, [fp, #-56]
	add	r6, r10, r6
	str	r7, [fp, #-48]
	mov	r4, r7
	str	r7, [fp, #-52]
	b	.L1657
.L1652:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L1689
.L1653:
	add	r3, r10, r9
	strb	r0, [r8, #1]!
	add	r4, r4, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2756]
	cmp	r3, r4
	bcc	.L1690
.L1657:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #0
	bne	.L1652
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L1653
.L1689:
	add	r3, r10, r9
	ldr	r2, [fp, #-60]
	add	r1, r7, #18
	sub	ip, r0, #1
	ldr	r3, [r3, #2756]
	clz	ip, ip
	cmp	r3, r4
	mov	ip, ip, lsr #5
	ldrhi	r3, [r6]
	movls	r3, #0
	add	r3, r3, r2
	ldr	r2, [fp, #-56]
	cmp	r3, #0
	str	r3, [r2, r1, asl #2]
	add	r3, r2, r7
	add	r7, r7, #1
	strb	ip, [r3, #53]
	ldrlt	r3, [fp, #-52]
	ldrge	r3, [fp, #-48]
	addlt	r3, r3, #1
	addge	r3, r3, #1
	strlt	r3, [fp, #-52]
	strge	r3, [fp, #-48]
	b	.L1653
.L1690:
	ldr	r4, [fp, #-56]
	add	r3, r3, #1
	ldr	r1, [fp, #-48]
	cmp	r7, #16
	str	r3, [r4, #28]
	ldr	r3, [fp, #-52]
	str	r7, [r4, #24]
	str	r1, [r4, #20]
	str	r3, [r4, #16]
	bhi	.L1658
	cmp	r3, #16
	bhi	.L1658
	cmp	r1, #16
	bhi	.L1658
	cmp	r7, #1
	bls	.L1664
	mov	r3, r7
	add	r8, r4, #72
	sub	r7, r7, #1
	add	r6, r4, #53
	mov	r5, #0
.L1663:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L1666
.L1662:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L1662
.L1666:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L1663
.L1664:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L1661
	ldr	r3, [fp, #-52]
	add	r0, r4, #72
	mov	r1, #0
	add	r2, r3, #17
	add	r3, r3, #52
	add	r3, r4, r3
	add	r2, r4, r2, lsl #2
	add	r4, r4, #53
.L1667:
	ldr	r5, [r2]
	add	r1, r1, #1
	ldr	lr, [r0]
	cmp	r1, r6
	ldrb	ip, [r4]	@ zero_extendqisi2
	str	r5, [r0], #4
	ldrb	r5, [r3]	@ zero_extendqisi2
	strb	r5, [r4], #1
	str	lr, [r2], #-4
	strb	ip, [r3], #-1
	bne	.L1667
	b	.L1661
.L1687:
	ldr	r1, .L1692+20
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #1
	str	r2, [r4, #4]
	cmp	r7, r2
	bcc	.L1691
	sub	r3, r7, #1
	rsb	r6, r0, r3
	cmp	r6, r3
	bls	.L1649
	ldr	ip, .L1692+24
	mov	r2, r6
	ldr	r1, .L1692+28
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L1650
.L1658:
	ldr	r3, .L1692+24
	mov	r0, #1
	ldr	r1, .L1692+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1650
.L1685:
	ldr	r3, .L1692+24
	mov	r2, r0
	ldr	r1, .L1692+36
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1650
.L1691:
	ldr	ip, .L1692+24
	mov	r3, r7
	ldr	r1, .L1692+40
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L1650
.L1688:
	ldr	r3, .L1692+24
	mov	r0, #1
	ldr	r1, .L1692+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1650
.L1670:
	ldr	ip, .L1692+24
	mov	r3, #16
	ldr	r1, .L1692+48
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L1650
.L1686:
	ldr	r3, .L1692+24
	mov	r0, #1
	ldr	r2, [r4, #16]
	ldr	r1, .L1692+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1650
.L1693:
	.align	2
.L1692:
	.word	.LC139
	.word	.LC141
	.word	.LC144
	.word	.LC145
	.word	.LC136
	.word	.LC133
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC135
	.word	.LC138
	.word	.LC140
	.word	.LC134
	.word	.LC137
	.word	.LC143
	.word	.LC142
	UNWIND(.fnend)
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	2
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r3
	mov	r5, r0
	mov	r8, r1
	beq	.L1716
	cmp	r2, #0
	bne	.L1741
.L1699:
	mov	r4, r8
	mov	r6, #0
.L1713:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #40]
	cmp	r0, #0
	movne	r3, #1
	strneb	r3, [r4, #41]
	beq	.L1742
.L1701:
	ldrb	r2, [r4, #41]	@ zero_extendqisi2
	mov	r3, #0
	strb	r3, [r4, #42]
	cmp	r2, r3
	str	r3, [r4, #48]
	beq	.L1702
	ldr	r1, .L1749
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldrb	r3, [r4, #42]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r4, #44]
	beq	.L1704
.L1745:
	ldr	r2, [r4, #48]
	cmp	r2, #31
	bhi	.L1743
.L1706:
	mov	r2, r4
	mov	r10, #0
.L1715:
	cmp	r10, #0
	beq	.L1744
	cmp	r10, #1
	beq	.L1739
.L1712:
	add	r10, r10, #1
	add	r2, r2, #4
	cmp	r10, #2
	bne	.L1715
.L1711:
	add	r6, r6, #1
	add	r4, r4, #1280
	cmp	r7, r6
	add	r4, r4, #12
	bcs	.L1713
	mov	r0, #0
.L1738:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1702:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #42]
	cmp	r3, #0
	bne	.L1745
.L1704:
	ldr	r1, .L1749+4
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	mov	r2, r0
	cmp	r2, #31
	str	r0, [r4, #48]
	bls	.L1706
.L1743:
	ldr	r3, .L1749+8
	mov	r0, #1
	ldr	r1, .L1749+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #48]
	b	.L1706
.L1742:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #41]
	b	.L1701
.L1741:
	mov	r1, #1
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r8, #1]
	ldrh	r3, [r8]
	cmp	r3, #0
	beq	.L1699
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #2]
	cmp	r0, #0
	bne	.L1746
.L1697:
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #16]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldrb	r3, [r8, #2]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r8, #20]
	bne	.L1747
.L1698:
	mov	r1, #5
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r8, #28]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r8, #32]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r8, #36]
	b	.L1699
.L1716:
	mvn	r0, #0
	b	.L1738
.L1747:
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r8, #24]
	b	.L1698
.L1746:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r8, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r8, #3]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r8, #36]
	b	.L1697
.L1744:
	ldrb	r1, [r8]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1748
	mov	r9, r2
	str	r10, [fp, #-48]
	b	.L1729
.L1714:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	str	r2, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-48]
	add	r9, r9, #8
	ldr	r2, [fp, #-52]
	str	r0, [r9, #1068]
	ldr	r1, [r4, #48]
	cmp	r1, r3
	bcc	.L1712
.L1729:
	ldr	r3, [fp, #-48]
	ldr	r1, .L1749+16
	ldr	r0, [r5, #2292]
	add	r3, r3, #1
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	bl	HEVC_ue_v
	ldr	r1, .L1749+20
	str	r0, [r9, #52]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r2, [fp, #-52]
	str	r0, [r9, #308]
	ldrb	r1, [r8, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1714
	ldr	r1, .L1749+24
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1749+28
	str	r0, [r9, #564]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r2, [fp, #-52]
	str	r0, [r9, #820]
	b	.L1714
.L1748:
	add	r2, r2, #4
	mov	r10, #1
.L1739:
	ldrb	r1, [r8, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1711
	mov	r3, #0
	mov	r9, r2
	str	r3, [fp, #-48]
	b	.L1729
.L1750:
	.align	2
.L1749:
	.word	.LC146
	.word	.LC147
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC148
	.word	.LC149
	.word	.LC150
	.word	.LC151
	.word	.LC152
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #124)
	sub	sp, sp, #124
	mov	r6, r1
	mov	r7, r0
	mov	r1, #2
	ldr	r0, [r0, #2292]
	bl	BsGet
	cmp	r0, #3
	str	r0, [r6, #12]
	beq	.L1752
	ldr	r3, .L1804
	mov	r2, r0
	ldr	r1, .L1804+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
.L1752:
	mov	r1, #6
	ldr	r0, [r7, #2292]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r6, #16]
	bhi	.L1796
	mov	r1, #3
	ldr	r0, [r7, #2292]
	bl	BsGet
	cmp	r0, #8
	str	r0, [fp, #-152]
	bhi	.L1797
	ldr	r3, [fp, #-152]
	mov	r1, #1
	add	r3, r3, #1
	str	r3, [r6, #20]
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #1]
	ldr	r0, [r7, #2292]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	str	r0, [r6, #24]
	bne	.L1798
	add	r1, r6, #12416
	ldr	r3, [fp, #-152]
	add	r1, r1, #20
	mov	r2, #1
	mov	r0, r7
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L1799
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	ldr	r3, [fp, #-152]
	cmp	r3, #0
	addgt	r5, r6, #48
	ldrgt	r8, [fp, #-152]
	strb	r0, [r6, #7]
	bgt	.L1764
	b	.L1762
.L1761:
	add	r4, r4, #1
	cmp	r4, r8
	beq	.L1762
.L1764:
	ldr	r1, .L1804+8
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1804+12
	add	r0, r0, #1
	str	r0, [r5, #4]!
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1804+16
	str	r0, [r5, #32]
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	str	r0, [r5, #64]
	ldrb	r3, [r6, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1761
	ldr	r0, [fp, #-152]
	add	r2, r4, #1
	cmp	r0, r2
	ble	.L1762
	add	r3, r4, #13
	add	r3, r6, r3, lsl #2
.L1763:
	ldr	r1, [r6, #52]
	add	r2, r2, #1
	cmp	r2, r0
	str	r1, [r3, #4]!
	ldr	r1, [r6, #84]
	str	r1, [r3, #32]
	ldr	r1, [r6, #116]
	str	r1, [r3, #64]
	bne	.L1763
.L1762:
	mov	r1, #6
	ldr	r0, [r7, #2292]
	bl	BsGet
	ldr	r1, .L1804+20
	str	r0, [r6, #28]
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #32]
	bhi	.L1800
	cmp	r0, #1
	ble	.L1765
	ldr	r10, .L1804
	add	r9, r6, #148
	mov	r8, #1
.L1766:
	ldr	r3, [r6, #28]
	cmp	r3, #0
	movgt	r5, r9
	movgt	r4, #0
	ble	.L1768
.L1767:
	ldr	r2, .L1804+24
	mov	r3, r8
	str	r4, [sp]
	mov	r1, #100
	ldr	ip, [r10, #72]
	sub	r0, fp, #144
	blx	ip
	mov	r1, #1
	ldr	r0, [r7, #2292]
	add	r4, r4, r1
	bl	BsGet
	str	r0, [r5, #4]!
	ldr	r2, [r6, #28]
	cmp	r2, r4
	bgt	.L1767
.L1768:
	ldr	r3, [r6, #32]
	add	r8, r8, #1
	add	r9, r9, #4
	cmp	r3, r8
	bgt	.L1766
.L1765:
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #6]
	cmp	r0, #0
	beq	.L1774
	mov	r1, #32
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #40]
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #5]
	cmp	r0, #0
	bne	.L1801
.L1772:
	ldr	r1, .L1804+28
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #48]
	bcs	.L1802
	cmp	r0, #0
	ble	.L1774
	add	r8, r6, #8192
	mov	r3, #1
	ldr	r1, .L1804+32
	add	r5, r6, #4224
	str	r3, [r8, #148]
	add	r5, r5, #24
	ldr	r0, [r7, #2292]
	mov	r4, #0
	bl	HEVC_ue_v
	add	r3, r6, #4096
	str	r0, [r3, #148]
	ldr	r0, [r8, #148]
	ldr	r8, [fp, #-152]
.L1775:
	uxtb	r2, r0
	ldr	r1, .L1804+36
	mov	r3, r8
	mov	r0, r7
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L1804+32
	cmp	r0, #0
	bne	.L1803
	ldr	r2, [r6, #48]
	cmp	r2, r4
	ble	.L1774
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r1, #1
	str	r0, [r5], #4
	ldrle	r0, [r5, #4092]
	ble	.L1775
	ldr	r0, [r7, #2292]
	bl	BsGet
	str	r0, [r5, #4092]
	b	.L1775
.L1774:
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #3]
	cmp	r0, #0
	bne	.L1791
.L1771:
	mov	r0, #0
.L1754:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1780:
	ldr	r0, [r7, #2292]
	bl	BsGet
	strb	r0, [r6, #4]
.L1791:
	mov	r0, r7
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L1780
	b	.L1771
.L1803:
	ldr	r3, .L1804
	mov	r0, #1
	ldr	r1, .L1804+40
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1801:
	ldr	r1, .L1804+44
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v
	str	r0, [r6, #44]
	b	.L1772
.L1798:
	ldr	r3, .L1804
	mov	r0, #1
	ldr	r1, .L1804+48
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1754
.L1796:
	ldr	r3, .L1804
	mov	r0, #1
	ldr	r1, .L1804+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1754
.L1799:
	ldr	r3, .L1804
	mov	r0, #1
	ldr	r1, .L1804+56
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1754
.L1797:
	ldr	r3, .L1804
	mov	r2, r0
	ldr	r1, .L1804+60
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1754
.L1800:
	ldr	ip, .L1804
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1804+64
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L1754
.L1802:
	ldr	ip, .L1804
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1804+68
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L1754
.L1805:
	.align	2
.L1804:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC153
	.word	.LC159
	.word	.LC160
	.word	.LC161
	.word	.LC158
	.word	.LC163
	.word	.LC165
	.word	.LC167
	.word	.LANCHOR5-3464
	.word	.LC168
	.word	.LC164
	.word	.LC156
	.word	.LC154
	.word	.LC157
	.word	.LC155
	.word	.LC162
	.word	.LC166
	UNWIND(.fnend)
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	2
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
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
	mov	r1, #4
	mov	r4, r0
	ldr	r0, [r0, #2292]
	bl	BsGet
	cmp	r0, #15
	mov	r6, r0
	bhi	.L1812
	movw	r7, #12820
	ldr	r3, [r4, #2296]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L1813
	str	r0, [r2, #8]
	mov	r0, r4
	ldr	r1, [r4, #2296]
	add	r1, r1, r5
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L1814
	ldr	r3, [r4, #2296]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2296]
	strb	r2, [r3, r5]
.L1808:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1813:
	ldr	r9, .L1816
	mov	r0, r4
	ldr	r1, .L1816+4
	str	r6, [r9, #-1264]
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L1815
	ldr	ip, .L1816+8
	mov	r3, #1
	ldr	r0, [r4, #2296]
	mov	r2, r7
	ldr	r1, .L1816+4
	add	r0, r0, r5
	ldr	ip, [ip, #56]
	strb	r3, [r9, #-1270]
	strb	r3, [r9, #-1272]
	blx	ip
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1815:
	ldr	r3, .L1816+8
	mov	r2, r6
	ldr	r1, .L1816+12
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1808
.L1812:
	ldr	r3, .L1816+8
	mov	r0, #1
	ldr	r1, .L1816+16
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1808
.L1814:
	ldr	r3, .L1816+8
	mov	r2, r6
	ldr	r1, .L1816+20
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #2296]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2296]
	strb	r9, [r3, r5]
	b	.L1808
.L1817:
	.align	2
.L1816:
	.word	.LANCHOR6
	.word	.LANCHOR6-1272
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC170
	.word	.LC169
	.word	.LC171
	UNWIND(.fnend)
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	2
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r3, .L1867
	mov	r5, r0
	mov	r4, r1
	add	ip, r3, #16
	mov	r6, r2
	ldmia	r3, {r0, r1, r2, r3}
	sub	lr, fp, #60
	stmia	lr, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	sub	ip, fp, #28
	stmdb	ip, {r0, r1, r2, r3}
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4]
	cmp	r0, #0
	bne	.L1858
.L1820:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1]
	cmp	r0, #0
	bne	.L1859
.L1822:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	bne	.L1860
.L1824:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #6]
	cmp	r0, #0
	bne	.L1861
.L1826:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #10]
	cmp	r0, #0
	beq	.L1827
	ldr	r1, .L1867+4
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	str	r0, [r4, #60]
	ldr	r3, [r6, #64]
	cmp	r3, #3
	bhi	.L1862
	sub	r2, fp, #28
	ldr	r1, .L1867+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-32]
	mul	r0, r3, r0
	str	r0, [r4, #60]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	sub	r2, fp, #28
	ldr	r1, .L1867+12
	str	r0, [r4, #64]
	ldr	r3, [r6, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-32]
	mul	r0, r3, r0
	str	r0, [r4, #64]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	sub	r2, fp, #28
	ldr	r1, .L1867+16
	str	r0, [r4, #68]
	ldr	r3, [r6, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-16]
	mul	r0, r3, r0
	str	r0, [r4, #68]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	sub	r2, fp, #28
	str	r0, [r4, #72]
	ldr	r3, [r6, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-16]
	mul	r0, r3, r0
	str	r0, [r4, #72]
.L1827:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L1830
	mov	r1, #32
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #76]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #80]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	bne	.L1863
.L1831:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #13]
	cmp	r0, #0
	bne	.L1864
.L1830:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #14]
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1865
.L1829:
	mov	r0, r3
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1865:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #15]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #16]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L1867+20
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #88]
	bcs	.L1866
.L1832:
	ldr	r1, .L1867+24
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1867+28
	str	r0, [r4, #92]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1867+32
	str	r0, [r4, #96]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1867+36
	str	r0, [r4, #100]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	mov	r3, #0
	str	r0, [r4, #104]
	mov	r0, r3
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1861:
	ldr	r1, .L1867+40
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1867+44
	str	r0, [r4, #52]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	str	r0, [r4, #56]
	b	.L1826
.L1858:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r4, #24]
	bne	.L1820
	mov	r1, #16
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #28]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #32]
	b	.L1820
.L1860:
	mov	r1, #3
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #36]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	cmp	r0, #0
	beq	.L1824
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #40]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #44]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #48]
	b	.L1824
.L1859:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2]
	b	.L1822
.L1864:
	ldr	r3, [r6, #56]
	mov	r2, #1
	ldr	r1, .L1867+48
	mov	r0, r5
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L1830
	ldr	r3, .L1867+52
	mov	r0, #1
	ldr	r1, .L1867+56
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1829
.L1863:
	ldr	r1, .L1867+60
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	str	r0, [r4, #84]
	b	.L1831
.L1866:
	ldr	r3, .L1867+52
	mov	r0, #1
	ldr	r1, .L1867+64
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1832
.L1862:
	ldr	r3, .L1867+52
	mov	r0, #1
	ldr	r1, .L1867+68
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1829
.L1868:
	.align	2
.L1867:
	.word	.LANCHOR1+424
	.word	.LC174
	.word	.LC176
	.word	.LC177
	.word	.LC178
	.word	.LC181
	.word	.LC183
	.word	.LC184
	.word	.LC185
	.word	.LC186
	.word	.LC172
	.word	.LC173
	.word	.LANCHOR5-3464
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC180
	.word	.LC179
	.word	.LC182
	.word	.LC175
	UNWIND(.fnend)
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	2
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L1874
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1874:
	add	r6, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r6
	mov	r0, r5
	bl	BsShow
	mov	r1, r6
	sub	r0, r0, #1
	tst	r0, #1
	mov	r3, r0, asr #1
	mov	r0, r5
	addne	r4, r3, #1
	rsbeq	r4, r3, #0
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_se_v, .-HEVC_se_v
	.align	2
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
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
	mov	r9, r1
	mov	r5, r0
	ldr	r1, .L1887
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L1887+4
	str	r0, [r9]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r9, #4]
	bhi	.L1876
	cmp	r0, #0
	beq	.L1882
	add	r7, r9, #4096
	add	r8, r9, #12288
	add	r7, r7, #8
	add	r8, r8, #8
	add	r6, r9, #4
	mov	r4, #0
	b	.L1881
.L1880:
	ldr	r3, [r9, #4]
	add	r8, r8, #4
	cmp	r3, r4
	bls	.L1882
.L1881:
	mov	r1, #6
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #4]!
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L1887+8
	str	r0, [r7], #4
	ldr	r3, [r6]
	sub	r3, r3, #19
	cmp	r3, #1
	bls	.L1879
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	str	r0, [r7, #4092]
.L1879:
	cmp	r4, #0
	add	r4, r4, #1
	beq	.L1880
	ldr	r1, .L1887+12
	add	r8, r8, #4
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	str	r0, [r8, #-4]
	ldr	r3, [r9, #4]
	cmp	r3, r4
	bhi	.L1881
.L1882:
	ldr	r0, [r5, #2292]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1876:
	ldr	r3, .L1887+16
	mov	r0, #1
	ldr	r1, .L1887+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1888:
	.align	2
.L1887:
	.word	.LC187
	.word	.LC188
	.word	.LC190
	.word	.LC191
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC189
	UNWIND(.fnend)
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	2
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r6, r1
	moveq	r5, #1
	movne	r5, #0
	beq	.L1891
	ldr	r1, .L1892
	ldr	r0, [r0, #2292]
	bl	HEVC_se_v
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #1]
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1891:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1893:
	.align	2
.L1892:
	.word	.LC192
	UNWIND(.fnend)
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	2
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #2316]
	mov	r4, r0
	mov	r6, r1
	ldr	r7, [fp, #4]
	ldr	ip, [ip, #16]
	cmp	ip, #39
	beq	.L1939
	cmp	r3, #5
	beq	.L1921
	cmp	r3, #132
	beq	.L1922
	cmp	r7, #0
	movne	r5, #0
	beq	.L1916
.L1924:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r5, r7
	bne	.L1924
	b	.L1916
.L1921:
	add	r1, r6, #3136
	mov	r2, r7
	add	r1, r1, #12
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L1918
.L1916:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L1940
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1940:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L1941
.L1925:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #12]
	b	.L1926
.L1927:
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #16]
.L1926:
	ldr	r0, [r4, #2292]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L1927
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1939:
	cmp	r3, #47
	beq	.L1897
	bls	.L1942
	cmp	r3, #130
	beq	.L1906
	bls	.L1943
	cmp	r3, #133
	beq	.L1910
	cmp	r3, #134
	beq	.L1911
	cmp	r3, #131
	beq	.L1912
.L1896:
	cmp	r7, #0
	movne	r5, #0
	beq	.L1916
.L1919:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r5, r7
	bne	.L1919
	b	.L1916
.L1922:
	add	r1, r1, #23552
	add	r1, r1, #124
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1942:
	cmp	r3, #5
	beq	.L1921
	bls	.L1944
	cmp	r3, #23
	beq	.L1903
	cmp	r3, #45
	beq	.L1904
	cmp	r3, #6
	bne	.L1896
	add	r1, r1, #3264
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L1916
.L1918:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1941:
	ldr	r1, .L1945
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	str	r0, [r6, #8]
	b	.L1925
.L1903:
	add	r1, r1, #3328
	add	r1, r1, #8
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1910:
	mov	r3, r7
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1943:
	cmp	r3, #128
	beq	.L1908
	cmp	r3, #129
	bne	.L1896
	add	r1, r1, #3168
	add	r1, r1, #4
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1944:
	cmp	r3, #0
	beq	.L1901
	cmp	r3, #1
	bne	.L1896
	add	r1, r1, #1056
	add	r2, r2, #2624
	add	r1, r1, #12
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1912:
	add	r1, r1, #3312
	add	r1, r1, #12
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1911:
	add	r1, r1, #3328
	add	r1, r1, #4
	bl	HEVC_Sei_Region_Refresh_Info
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1901:
	ldr	r2, .L1945+4
	add	r1, r1, #24
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1906:
	ldr	r2, .L1945+4
	add	r1, r1, #3248
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1897:
	add	r1, r1, #3312
	add	r1, r1, #4
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1904:
	add	r1, r1, #3264
	add	r1, r1, #8
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1908:
	add	r1, r1, #6464
	mov	r2, r7
	add	r1, r1, #32
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L1916
	b	.L1918
.L1946:
	.align	2
.L1945:
	.word	.LC193
	.word	.LANCHOR5-3464
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	2
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r6, #0
	mov	r4, r0
	mov	r7, r1
	mov	r8, r2
	b	.L1948
.L1949:
	add	r6, r6, #255
	bl	BsSkip
.L1948:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2292]
	beq	.L1949
	bl	BsGet
	mov	r5, #0
	str	r0, [r7]
	add	r6, r0, r6
	b	.L1950
.L1951:
	add	r5, r5, #255
	bl	BsSkip
.L1950:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2292]
	beq	.L1951
	bl	BsGet
	mov	r3, r6
	mov	r2, r8
	mov	r1, r7
	str	r0, [r7, #4]
	add	r5, r0, r5
	mov	r0, r4
	str	r5, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L1954
.L1952:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1954:
	ldr	r3, .L1955
	mov	r0, #1
	ldr	r1, .L1955+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1952
.L1956:
	.align	2
.L1955:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC194
	UNWIND(.fnend)
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	2
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
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
	add	r6, r0, #3424
	add	r5, r0, #27136
	mov	r4, r0
	add	r6, r6, #4
	add	r5, r5, #52
	b	.L1961
.L1958:
	ldr	r0, [r4, #2292]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L1966
	bl	HEVC_More_Rbsp_Data
	subs	r7, r0, #0
	beq	.L1967
.L1961:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L1958
	ldr	r3, .L1968
	mov	r0, #1
	ldr	r1, .L1968+4
	mvn	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
.L1959:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1966:
	ldr	r3, .L1968
	mvn	r7, #0
	ldr	r1, .L1968+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1967:
	ldr	r0, [r4, #2292]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	beq	.L1959
	ldr	r3, .L1968
	mov	r2, r0
	ldr	r1, .L1968+12
	mov	r0, #1
	mvn	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1959
.L1969:
	.align	2
.L1968:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC195
	.word	.LC196
	.word	.LC197
	UNWIND(.fnend)
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	2
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
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
	mov	r4, r0
	mov	r7, r1
	ldr	r0, [r0, #2292]
	mov	r1, #1
	mov	r9, r2
	bl	BsGet
	add	r8, r7, #20480
	mov	r1, #1
	strb	r0, [r8, #2408]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	uxtb	r0, r0
	strb	r0, [r8, #2409]
	cmp	r0, #0
	ldr	r0, [r4, #2292]
	beq	.L1971
	bl	BsGet
	ldr	r1, .L1987
	strb	r0, [r8, #2410]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #63
	str	r0, [r8, #2416]
	bhi	.L1984
	ldrb	r6, [r8, #2410]	@ zero_extendqisi2
	cmp	r0, r6
	addcs	r5, r6, #5696
	addcs	r5, r5, #28
	addcs	r5, r7, r5, lsl #2
	bcc	.L1977
.L1976:
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r1, .L1987+4
	add	r6, r6, #1
	str	r0, [r5, #4]!
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	str	r0, [r5, #256]
	ldr	r3, [r8, #2416]
	cmp	r3, r6
	bcs	.L1976
.L1977:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r3, #0
	strb	r3, [r8, #2412]
	b	.L1975
.L1980:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L1985
.L1975:
	mov	r2, r9
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L1980
	ldr	r3, .L1987+8
	mov	r0, #1
	ldr	r1, .L1987+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1971:
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r8, #2411]
	cmp	r5, #0
	bne	.L1977
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r1, .L1987+16
	str	r0, [r8, #2932]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #63
	str	r0, [r8, #2936]
	addls	r6, r7, #23296
	addls	r6, r6, #120
	bhi	.L1986
.L1979:
	mov	r1, #6
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r6, #4]!
	ldr	r3, [r8, #2936]
	cmp	r3, r5
	bcs	.L1979
	b	.L1977
.L1985:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1984:
	ldr	r3, .L1987+8
	mov	r2, #64
	ldr	r1, .L1987+20
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1986:
	ldr	r3, .L1987+8
	mov	r0, #1
	ldr	r1, .L1987+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1988:
	.align	2
.L1987:
	.word	.LC198
	.word	.LC200
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC195
	.word	.LC201
	.word	.LC199
	.word	.LC202
	UNWIND(.fnend)
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	2
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r3, .L2026
	mov	r9, r1
	mov	r6, r0
	add	ip, r9, #1664
	add	r1, r1, #1264
	add	r0, r9, #1392
	ldr	r3, [r3, #52]
	add	r1, r1, #1
	add	r0, r0, #1
	mov	r2, #64
	mov	r4, ip
	blx	r3
	add	r3, r4, #4
	str	r3, [fp, #-76]
	add	r3, r6, #2176
	str	r3, [fp, #-48]
	add	r3, r9, #24
	str	r3, [fp, #-68]
	add	r3, r9, #49
	str	r3, [fp, #-72]
	mov	r3, #0
	str	r3, [fp, #-52]
.L1990:
	ldr	r2, [fp, #-48]
	ldr	r3, [r2, #4]!
	cmp	r3, #0
	str	r2, [fp, #-48]
	beq	.L2009
	ldr	r3, [fp, #-76]
	ldr	r7, [fp, #-72]
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-68]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-60]
.L2008:
	mov	r1, #1
	ldr	r0, [r6, #2292]
	bl	BsGet
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-48]
	ldr	r5, [r3, #-1904]
	ldr	r3, [fp, #-52]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	beq	.L1991
	cmp	r0, #0
	add	r4, r6, #308
	beq	.L2022
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	bls	.L2015
	ldr	r1, .L2026+4
	ldr	r0, [r6, #2292]
	bl	HEVC_se_v
	add	r3, r0, #7
	str	r0, [r9, #1660]
	cmp	r3, #254
	bhi	.L2023
	ldr	r3, [fp, #-64]
	add	r8, r0, #8
	str	r8, [r3]
.L2002:
	cmp	r5, #0
	ble	.L2001
	sub	r4, r4, #4
	mov	r10, #0
	b	.L2006
.L2005:
	mov	r8, r8, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r8
	cmp	r10, r5
	uxtb	r3, r3
	rsb	r8, r8, r3
	strb	r8, [r7, r2]
	beq	.L2001
.L2006:
	ldr	r1, .L2026+8
	add	r10, r10, #1
	ldr	r0, [r6, #2292]
	bl	HEVC_se_v
	add	r3, r8, r0
	add	r2, r0, #128
	add	r3, r3, #256
	cmp	r2, #255
	str	r0, [r9, #1664]
	mov	r8, r3, asr #31
	bls	.L2005
	ldr	r3, .L2026
	mov	r0, #1
	ldr	r1, .L2026+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L2020:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2010:
	ldr	r1, .L2026+16
	ldr	r0, [r6, #2292]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-60]
	cmp	r0, r3
	bhi	.L2012
	ldr	r2, [fp, #-60]
	uxtb	r0, r0
	ldr	r3, [fp, #-56]
	rsb	r1, r0, r2
	strb	r0, [r3, #1560]
	uxtb	r1, r1
	strb	r1, [r3, #1584]
.L1996:
	ldr	r3, [fp, #-60]
	cmp	r1, r3
	beq	.L2024
	ldr	r2, [fp, #-52]
	mov	r3, r2, asl #3
	sub	r3, r3, r2, asl #1
	add	r1, r3, r1
	add	r1, r9, r1, lsl #6
	add	r1, r1, #49
.L1999:
	cmp	r1, #0
	beq	.L2025
	ldr	r3, .L2026
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L2001:
	ldr	r3, [fp, #-48]
	add	r7, r7, #64
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-64]
	ldr	r3, [r3]
	add	r2, r2, #1
	add	r1, r1, #4
	str	r2, [fp, #-60]
	cmp	r3, r2
	str	r1, [fp, #-64]
	bhi	.L2008
.L2009:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #4
	ldr	r3, [fp, #-72]
	add	r2, r2, #6
	str	r2, [fp, #-68]
	add	r3, r3, #384
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-76]
	add	r3, r3, #24
	str	r3, [fp, #-76]
	bne	.L1990
	mov	r0, #0
	b	.L2020
.L2015:
	mov	r8, #8
	b	.L2002
.L2022:
	ldr	r1, .L2026+16
	ldr	r0, [r6, #2292]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-60]
	cmp	r0, r3
	bhi	.L2012
	ldr	r3, [fp, #-52]
	uxtb	r0, r0
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-56]
	cmp	r3, #1
	rsb	r1, r0, ip
	strb	r0, [r2, #1560]
	uxtb	r1, r1
	strb	r1, [r2, #1584]
	bls	.L1996
	cmp	ip, r1
	mov	r2, ip
	movne	r2, r3
	movne	r3, r3, asl #3
	subne	r3, r3, r2, asl #1
	ldr	r2, [fp, #-64]
	addne	r3, r3, r1
	moveq	r3, #16
	addne	r3, r9, r3, lsl #2
	ldrne	r3, [r3, #1668]
	str	r3, [r2]
	b	.L1996
.L2024:
	mov	r1, r3
	ldr	r0, [fp, #-52]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L1999
.L2023:
	ldr	r3, .L2026
	mov	r0, #1
	ldr	r1, .L2026+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2020
.L2025:
	ldr	r3, .L2026
	mov	r0, #1
	ldr	r1, .L2026+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2020
.L2012:
	ldr	r3, .L2026
	mov	r0, #1
	ldr	r1, .L2026+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2020
.L1991:
	cmp	r0, #0
	beq	.L2010
	ldr	r4, .L2026+32
	mov	r8, #8
	b	.L2002
.L2027:
	.align	2
.L2026:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC206
	.word	.LC208
	.word	.LC209
	.word	.LC203
	.word	.LC207
	.word	.LC205
	.word	.LC204
	.word	.LANCHOR0+65536
	UNWIND(.fnend)
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	2
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r1
	mov	r5, r0
	ldr	r1, .L2194
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r8, r0
	str	r0, [r4, #64]
	beq	.L2029
	cmp	r0, #3
	ldr	r3, .L2194+4
	bhi	.L2171
	mov	r2, r0
	ldr	r1, .L2194+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L2031:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2171:
	ldr	r1, .L2194+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2029:
	ldr	r1, .L2194+16
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #72]
	bhi	.L2172
	ldr	r1, .L2194+20
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #76]
	bhi	.L2173
	ldr	r2, [r4, #760]
	ldr	r3, [r4, #72]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L2035
	bgt	.L2036
	cmp	r2, #60
	beq	.L2037
	ble	.L2174
	cmp	r2, #90
	beq	.L2040
	cmp	r2, #93
	beq	.L2041
	cmp	r2, #63
	bne	.L2034
	mov	r2, #61440
	mov	r3, #245760
	b	.L2042
.L2036:
	cmp	r2, #156
	beq	.L2043
	bgt	.L2044
	cmp	r2, #150
	beq	.L2043
	cmp	r2, #153
	beq	.L2043
	cmp	r2, #123
	beq	.L2035
.L2034:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2044:
	cmp	r2, #183
	beq	.L2045
	cmp	r2, #186
	beq	.L2045
	cmp	r2, #180
	bne	.L2034
.L2045:
	mov	r2, #8912896
	mov	r3, #35651584
.L2042:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #236]
	bls	.L2047
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #236]
	bls	.L2047
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #236]
.L2047:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #80]
	beq	.L2050
	ldr	r1, .L2194+28
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #64]
	ldr	r6, .L2194+32
	ldr	r1, .L2194+36
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #456]
	mul	r0, r3, r0
	str	r0, [r4, #84]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #84]
	ldr	r1, [r4, #72]
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #456]
	mul	r0, r3, r0
	add	r2, r0, r2
	cmp	r1, r2
	str	r0, [r4, #88]
	bcc	.L2175
	ldr	r1, .L2194+40
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #64]
	ldr	r1, .L2194+44
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #472]
	mul	r0, r3, r0
	str	r0, [r4, #92]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #92]
	ldr	r1, [r4, #76]
	add	r6, r6, r3, lsl #2
	ldr	r3, [r6, #472]
	mul	r0, r3, r0
	add	r2, r0, r2
	cmp	r1, r2
	str	r0, [r4, #96]
	bcc	.L2176
.L2050:
	ldr	r1, .L2194+48
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #8
	str	r2, [r4, #100]
	cmp	r2, #8
	beq	.L2053
	cmp	r0, #6
	ldr	r3, .L2194+4
	bhi	.L2177
	ldr	r3, [r3, #68]
	mov	r0, #1
	ldr	r1, .L2194+52
	blx	r3
	ldr	r3, .L2194+56
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2053
	ldr	r0, [r4, #100]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-52]
	mov	r1, #119
	sub	r2, fp, #52
	str	r0, [fp, #-48]
	ldr	r0, [r5, #244]
	blx	ip
.L2053:
	ldr	r1, .L2194+60
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #8
	str	r2, [r4, #108]
	cmp	r2, #8
	beq	.L2057
	cmp	r0, #6
	ldr	r3, .L2194+4
	bhi	.L2178
	ldr	r3, [r3, #68]
	mov	r0, #1
	ldr	r1, .L2194+64
	blx	r3
	ldr	r3, .L2194+56
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2057
	ldr	r0, [r4, #108]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-52]
	mov	r1, #119
	sub	r2, fp, #52
	str	r0, [fp, #-48]
	ldr	r0, [r5, #244]
	blx	ip
.L2057:
	ldr	r3, [r4, #100]
	ldr	r1, .L2194+68
	str	r3, [r5, #192]
	ldr	r3, [r4, #108]
	str	r3, [r5, #196]
	ldr	r0, [r4, #108]
	ldr	ip, [r4, #100]
	mov	r3, r0, asl #3
	mov	r2, ip, asl #3
	sub	r3, r3, r0, asl #1
	sub	r2, r2, ip, asl #1
	sub	r3, r3, #48
	sub	r2, r2, #48
	str	r3, [r4, #112]
	str	r2, [r4, #104]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L2179
	add	r0, r0, #4
	mov	r1, #1
	str	r0, [r4, #128]
	mov	r6, r4
	str	r0, [r4, #132]
	mov	r7, #0
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #3]
	b	.L2067
.L2061:
	ldr	r3, [r4, #56]
	add	r7, r7, #1
	cmp	r3, r7
	bcc	.L2066
.L2067:
	ldr	r1, .L2194+72
	add	r6, r6, #4
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L2194+76
	add	r0, r0, #1
	str	r0, [r6, #376]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r1, .L2194+80
	ldr	r10, [r6, #376]
	str	r0, [r6, #408]
	ldr	r0, [r5, #2292]
	ldr	r9, [r4, #380]
	bl	HEVC_ue_v
	str	r0, [r6, #440]
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2061
	ldr	r1, [r4, #56]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #95
	addls	r7, r4, r7, lsl #2
	bhi	.L2066
.L2065:
	ldr	r2, [r4, #380]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #412]
	str	r2, [r7, #32]
	ldr	r2, [r4, #444]
	str	r2, [r7, #64]
	bls	.L2065
.L2066:
	ldr	r3, [r4, #236]
	cmp	r9, r10
	ldr	r1, .L2194+84
	movcc	r9, r10
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r4, #236]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #136]
	bhi	.L2180
	ldr	r1, .L2194+88
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #144]
	bhi	.L2181
	ldr	r3, [r4, #136]
	add	r3, r3, #3
	str	r3, [r4, #140]
	add	r6, r0, r3
	str	r6, [r4, #148]
	sub	r2, r6, #4
	cmp	r2, #2
	bhi	.L2182
	mov	r2, #1
	ldr	r7, [r4, #72]
	mov	r6, r2, asl r6
	mov	r3, r2, asl r3
	str	r6, [r4, #156]
	str	r6, [r4, #160]
	mov	r1, r6
	str	r6, [r4, #164]
	mov	r0, r7
	str	r3, [r4, #152]
	bl	__aeabi_uidivmod
	mov	r0, r7
	cmp	r1, #0
	mov	r1, r6
	beq	.L2070
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2071:
	ldr	r7, [r4, #76]
	mov	r1, r6
	str	r0, [r4, #240]
	mov	r0, r7
	bl	__aeabi_uidivmod
	mov	r0, r7
	cmp	r1, #0
	mov	r1, r6
	beq	.L2072
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2073:
	str	r0, [r4, #244]
	ldr	r1, .L2194+92
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #168]
	bhi	.L2183
	ldr	r1, .L2194+96
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #176]
	bhi	.L2184
	ldr	r3, [r4, #168]
	ldr	r2, [r4, #140]
	add	r3, r3, #2
	str	r3, [r4, #172]
	cmp	r3, r2
	bcs	.L2185
	add	r0, r0, r3
	str	r0, [r4, #180]
	cmp	r0, #5
	bhi	.L2077
	ldr	r3, [r4, #148]
	cmp	r0, r3
	bhi	.L2077
	ldr	r1, .L2194+100
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #148]
	ldr	r2, [r4, #172]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #200]
	bhi	.L2186
	ldr	r1, .L2194+104
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #148]
	ldr	r2, [r4, #172]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #208]
	bhi	.L2187
	ldr	r3, [r4, #200]
	add	r0, r0, #1
	mov	r1, #0
	str	r0, [r4, #212]
	add	r3, r3, #1
	str	r3, [r4, #204]
	str	r1, [r5, #228]
	mov	ip, #1
	ldr	r3, [r4, #172]
	ldr	r0, [r4, #160]
	ldr	r2, [r4, #144]
	mov	r3, ip, asl r3
	cmp	r3, r0, lsr r2
	bcc	.L2082
	b	.L2188
.L2107:
	mov	r8, r0
.L2082:
	str	r8, [r5, #228]
	add	r0, r8, #1
	ldr	r3, [r4, #172]
	ldr	r1, [r4, #160]
	add	r3, r8, r3
	ldr	r2, [r4, #144]
	mov	r3, ip, asl r3
	cmp	r3, r1, lsr r2
	bcc	.L2107
.L2081:
	mov	r6, #1
	add	r8, r8, r2
	str	r6, [r4, #224]
	mov	r3, #0
	str	r8, [r4, #216]
	mov	r1, r6
	str	r3, [r4, #220]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	cmp	r0, #0
	beq	.L2083
	mov	r1, r6
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #6]
	cmp	r0, #0
	bne	.L2189
.L2083:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #8]
	cmp	r6, #0
	bne	.L2084
	ldr	r2, [r4, #76]
	cmp	r2, #64
	bls	.L2190
.L2084:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #116]
	beq	.L2085
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #120]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L2194+108
	add	r0, r0, #1
	str	r0, [r4, #124]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r4, #184]
	bhi	.L2191
.L2086:
	ldr	r1, .L2194+112
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r4, #192]
	bhi	.L2192
.L2087:
	ldr	r2, [r4, #184]
	add	r2, r2, #3
	str	r2, [r4, #188]
	add	r0, r0, r2
	str	r0, [r4, #196]
	cmp	r0, #5
	bhi	.L2088
	ldr	r3, [r4, #148]
	cmp	r0, r3
	bhi	.L2088
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #9]
.L2085:
	ldr	r1, .L2194+116
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #228]
	bhi	.L2090
	cmp	r0, #0
	addne	r7, r4, #2720
	movne	r6, #0
	addne	r7, r7, #12
	bne	.L2095
	b	.L2096
.L2094:
	ldr	r3, [r4, #228]
	cmp	r3, r6
	bls	.L2096
.L2095:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #204
	cmp	r0, #0
	beq	.L2094
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+120
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2041:
	mov	r2, #245760
	mov	r3, #983040
	b	.L2042
.L2072:
	bl	__aeabi_uidiv
	b	.L2073
.L2070:
	bl	__aeabi_uidiv
	b	.L2071
.L2096:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #10]
	cmp	r0, #0
	beq	.L2093
	ldr	r1, .L2194+124
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #232]
	bhi	.L2099
	cmp	r0, #0
	addne	r8, r4, #244
	addne	r7, r4, #15
	movne	r6, #0
	beq	.L2093
.L2101:
	ldr	r1, [r4, #128]
	add	r6, r6, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #232]
	cmp	r3, r6
	bhi	.L2101
.L2093:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #13]
	cmp	r0, #0
	beq	.L2098
	mov	r2, r4
	add	r1, r4, #2624
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L2193
.L2098:
	ldr	ip, [r4, #76]
	ldr	r3, [r4, #72]
	ldr	r2, [r4, #2656]
	ldr	r1, [r4, #2652]
	ldr	r0, [r4, #2648]
	str	ip, [sp]
	bl	HEVCGetDar
	mov	r1, #1
	str	r0, [r4, #2644]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #14]
	cmp	r0, #0
	bne	.L2167
.L2104:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r4]
	b	.L2031
.L2103:
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #15]
.L2167:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2103
	b	.L2104
.L2174:
	cmp	r2, #0
	beq	.L2039
	cmp	r2, #30
	bne	.L2034
.L2039:
	mov	r2, #9216
	mov	r3, #36864
	b	.L2042
.L2190:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+128
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L2194+56
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L2031
	ldr	r0, [r5, #244]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	b	.L2031
.L2037:
	mov	r2, #30720
	mov	r3, #122880
	b	.L2042
.L2035:
	mov	r2, #557056
	mov	r3, #2228224
	b	.L2042
.L2043:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L2042
.L2040:
	mov	r2, #138240
	mov	r3, #552960
	b	.L2042
.L2189:
	add	r1, r4, #860
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L2083
	ldr	r3, .L2194+4
	mov	r0, r6
	ldr	r1, .L2194+132
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2077:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+136
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2192:
	ldr	r3, .L2194+4
	mov	r2, r0
	ldr	r1, .L2194+140
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r4, #192]
	b	.L2087
.L2191:
	ldr	r3, .L2194+4
	mov	r2, r0
	ldr	r1, .L2194+144
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2086
.L2188:
	mov	r8, r1
	b	.L2081
.L2172:
	ldr	r3, .L2194+4
	mov	r0, r8
	ldr	r1, .L2194+148
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2179:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+152
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2180:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+156
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2177:
	ldr	r1, .L2194+160
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2183:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+164
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2178:
	ldr	r1, .L2194+168
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2186:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+172
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2088:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+176
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2175:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+180
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2173:
	ldr	r3, .L2194+4
	mov	r0, r8
	ldr	r1, .L2194+184
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2181:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+188
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2182:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+192
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2185:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+196
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2184:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+200
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2187:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+204
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2090:
	ldr	r3, .L2194+4
	mov	r2, #64
	ldr	r1, .L2194+208
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2176:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+212
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2099:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+216
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2193:
	ldr	r3, .L2194+4
	mov	r0, #1
	ldr	r1, .L2194+220
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2031
.L2195:
	.align	2
.L2194:
	.word	.LC210
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC212
	.word	.LC211
	.word	.LC213
	.word	.LC215
	.word	.LC217
	.word	.LC218
	.word	.LANCHOR1
	.word	.LC219
	.word	.LC221
	.word	.LC222
	.word	.LC224
	.word	.LC226
	.word	g_event_report
	.word	.LC227
	.word	.LC229
	.word	.LC230
	.word	.LC232
	.word	.LC233
	.word	.LC234
	.word	.LC235
	.word	.LC237
	.word	.LC240
	.word	.LC242
	.word	.LC246
	.word	.LC248
	.word	.LC252
	.word	.LC254
	.word	.LC257
	.word	.LC259
	.word	.LC260
	.word	.LC251
	.word	.LC250
	.word	.LC245
	.word	.LC255
	.word	.LC253
	.word	.LC214
	.word	.LC231
	.word	.LC236
	.word	.LC225
	.word	.LC241
	.word	.LC228
	.word	.LC247
	.word	.LC256
	.word	.LC220
	.word	.LC216
	.word	.LC238
	.word	.LC239
	.word	.LC244
	.word	.LC243
	.word	.LC249
	.word	.LC258
	.word	.LC223
	.word	.LC261
	.word	.LC262
	UNWIND(.fnend)
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	2
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #404)
	sub	sp, sp, #404
	ldr	r5, .L2214
	mov	r4, r0
	movw	r2, #15788
	mov	r1, #0
	ldr	r0, .L2214+4
	ldr	r3, [r5, #48]
	blx	r3
	mov	r2, #384
	ldr	r3, [r5, #48]
	mov	r1, #0
	sub	r0, fp, #428
	ldr	r8, .L2214+8
	blx	r3
	ldr	r0, [r4, #2292]
	mov	r1, #4
	bl	BsGet
	ldr	r2, [r4, #148]
	cmp	r2, r0
	str	r0, [fp, #-440]
	bls	.L2207
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L2208
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r3, r7
	mov	r2, #1
	sub	r1, fp, #428
	mov	r9, r0
	mov	r0, r4
	bl	HEVC_DecPTL
	cmp	r0, #0
	bne	.L2209
	ldr	r1, .L2214+12
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	ldr	r2, [r4, #152]
	cmp	r0, r2
	mov	r10, r0
	bcs	.L2210
	movw	ip, #15788
	ldr	r2, [r4, #2300]
	mul	r6, ip, r0
	uxtb	r0, r9
	str	ip, [fp, #-444]
	ldr	r3, [fp, #-440]
	add	r2, r2, r6
	ldrb	r9, [r2, #1]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2211
	str	r3, [r2, #52]
	sub	r1, fp, #428
	ldr	lr, [r4, #2300]
	mov	r2, #384
	add	lr, lr, r6
	str	r7, [lr, #56]
	ldr	lr, [r4, #2300]
	add	lr, lr, r6
	strb	r0, [lr, #2]
	ldr	r0, [r4, #2300]
	ldr	r7, [r5, #52]
	add	r0, r0, r6
	add	r0, r0, #476
	blx	r7
	ldr	r2, [r4, #2300]
	mov	r0, r4
	add	r2, r2, r6
	str	r10, [r2, #60]
	ldr	r1, [r4, #2300]
	add	r1, r1, r6
	bl	HEVC_ProcessSPS
	ldr	ip, [fp, #-444]
	subs	r7, r0, #0
	bne	.L2212
	ldr	r3, [r4, #2300]
	mov	r1, #1
	add	r0, r4, #27136
	mov	r2, ip
	add	r0, r0, #52
	strb	r1, [r3, r6]
	ldr	r3, [r4, #2300]
	add	r3, r3, r6
	strb	r1, [r3, #1]
	ldr	r1, [r4, #2300]
	ldr	r3, [r5, #52]
	add	r1, r1, r6
	blx	r3
.L2198:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2211:
	str	r3, [r8, #-1220]
	sub	r1, fp, #428
	str	r7, [r8, #-1216]
	mov	r2, #384
	strb	r0, [r8, #-1270]
	sub	r0, r8, #796
	ldr	r7, [r5, #52]
	blx	r7
	ldr	r1, .L2214+4
	mov	r0, r4
	str	r10, [r8, #-1212]
	bl	HEVC_ProcessSPS
	ldr	ip, [fp, #-444]
	subs	r7, r0, #0
	bne	.L2213
	ldr	r0, [r4, #2300]
	mov	r3, #1
	mov	r2, ip
	strb	r3, [r8, #-1272]
	strb	r3, [r8, #-1271]
	add	r0, r0, r6
	ldr	r9, [r5, #56]
	ldr	r1, .L2214+4
	str	ip, [fp, #-440]
	blx	r9
	ldr	ip, [fp, #-440]
	add	r0, r4, #27136
	ldr	r1, [r4, #2300]
	add	r0, r0, #52
	ldr	r3, [r5, #52]
	mov	r2, ip
	add	r1, r1, r6
	blx	r3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2210:
	ldr	ip, [r5, #68]
	mov	r0, #1
	ldr	r1, .L2214+16
	blx	ip
	ldr	r2, [r4, #152]
	cmp	r10, r2
	bcc	.L2206
	ldr	r1, .L2214+20
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L2206
	str	r2, [fp, #-432]
	mov	r3, #8
	str	r10, [fp, #-436]
	sub	r2, fp, #436
	ldr	r0, [r4, #244]
	mov	r1, #109
	blx	ip
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2206:
	mvn	r7, #0
	b	.L2198
.L2207:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L2214+24
	mvn	r7, #0
	blx	r3
	b	.L2198
.L2208:
	ldr	r3, [r5, #68]
	mov	r2, #8
	ldr	r1, .L2214+28
	mov	r0, #1
	blx	r3
	mvn	r7, #0
	b	.L2198
.L2209:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L2214+32
	mvn	r7, #0
	blx	r3
	b	.L2198
.L2212:
	mov	r2, r10
	ldr	ip, [r5, #68]
	ldr	r1, .L2214+36
	mov	r0, #1
	blx	ip
	ldr	r3, [r4, #2300]
	mov	r2, #1
	mvn	r7, #0
	strb	r2, [r3, r6]
	ldr	r3, [r4, #2300]
	add	r6, r3, r6
	strb	r9, [r6, #1]
	b	.L2198
.L2213:
	ldr	r1, [r4, #2300]
	add	r0, r4, #27136
	mov	r2, ip
	add	r0, r0, #52
	add	r1, r1, r6
	ldr	ip, [r5, #52]
	blx	ip
	ldr	ip, [r5, #68]
	mov	r2, r10
	ldr	r1, .L2214+40
	mov	r0, #1
	mvn	r7, #0
	blx	ip
	b	.L2198
.L2215:
	.align	2
.L2214:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR6-1272
	.word	.LANCHOR6
	.word	.LC266
	.word	.LC267
	.word	g_event_report
	.word	.LC263
	.word	.LC264
	.word	.LC265
	.word	.LC269
	.word	.LC268
	UNWIND(.fnend)
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	2
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r1
	mov	r7, #1
	mov	r5, r0
	strb	r7, [r4, #16]
	str	r7, [r4, #68]
	str	r7, [r4, #72]
	ldr	r1, .L2344
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L2217
	ldr	r3, [r5, #152]
	cmp	r0, r3
	bge	.L2217
	ldr	r3, [r5, #2300]
	movw	r6, #15788
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2324
	mov	r1, r7
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L2344+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L2325
	ldr	r1, .L2344+8
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L2326
	ldr	r1, .L2344+12
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	add	r2, r0, #26
	str	r2, [r4, #48]
	ldr	r3, [r6, #104]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2327
	mov	r1, r7
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L2328
.L2226:
	str	r0, [r4, #56]
	ldr	r1, .L2344+16
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L2329
	ldr	r1, .L2344+20
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L2330
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L2331
	ldr	r3, [r6, #240]
	strh	r3, [r4, #176]	@ movhi
	ldr	r3, [r6, #244]
	strh	r3, [r4, #216]	@ movhi
.L2265:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L2270
.L2264:
	ldr	ip, [r6, #160]
	add	r1, r4, #174
	mov	r3, #0
.L2269:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L2268
	ldr	lr, [r6, #72]
	cmp	lr, #64
	bhi	.L2332
.L2268:
	cmp	r3, r0
	blt	.L2269
.L2270:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L2267
	ldr	r0, [r6, #160]
	ldrsh	r2, [r4, #216]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #107
	addhi	r3, r4, #216
	addhi	r1, r4, r1, lsl #1
	bhi	.L2273
	b	.L2271
.L2274:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L2271
.L2273:
	cmp	r3, r1
	bne	.L2274
.L2267:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L2333
.L2276:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L2279
	add	r1, r4, #260
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L2334
.L2279:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r1, .L2344+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L2280
	ldr	r3, [r6, #148]
	cmp	r2, r3
	bhi	.L2280
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	bne	.L2311
	b	.L2284
.L2283:
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #25]
.L2311:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2283
.L2284:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2328:
	ldr	r1, .L2344+28
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L2226
	ldr	r3, .L2344+32
	mov	r0, r7
	ldr	r1, .L2344+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2331:
	ldr	r1, .L2344+40
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L2335
	ldr	r1, .L2344+44
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L2336
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L2337
	cmp	r3, #11
	ble	.L2234
	ldr	ip, .L2344+32
	mov	r2, #11
	ldr	r1, .L2344+48
.L2321:
	ldr	ip, [ip, #68]
	mov	r0, #1
	blx	ip
	ldr	r3, .L2344+52
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2316
.L2318:
	mov	r3, #0
	ldr	r0, [r5, #244]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L2312:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2271:
	ldr	r3, .L2344+32
	ldr	r1, .L2344+56
.L2320:
	ldr	r3, [r3, #68]
	mov	r0, #1
	blx	r3
	ldr	r3, .L2344+52
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L2318
.L2316:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2332:
	ldr	r3, .L2344+32
	ldr	r1, .L2344+60
	b	.L2320
.L2327:
	ldr	ip, .L2344+32
	mov	r0, r7
	ldr	r1, .L2344+64
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2234:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L2248
	ldr	r3, [r4, #68]
	cmp	r3, #1
	addgt	r8, r4, #90
	movgt	r7, r0
	bgt	.L2246
	b	.L2338
.L2340:
	cmp	r3, r2
	bhi	.L2244
	ldr	r3, [r4, #68]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2339
.L2246:
	ldr	r1, .L2344+68
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #240]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2340
.L2244:
	ldr	ip, .L2344+32
	mov	r0, #1
	str	r2, [sp]
	mov	r2, r7
	ldr	r1, .L2344+72
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2337:
	mov	r3, r2
	ldr	ip, .L2344+32
	mov	r2, #10
	ldr	r1, .L2344+76
	b	.L2321
.L2333:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L2276
	ldr	r1, .L2344+80
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L2341
.L2278:
	ldr	r1, .L2344+84
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L2276
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+88
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L2276
.L2248:
	ldr	r7, [r4, #68]
	cmp	r7, #0
	addgt	r3, r4, #174
	movgt	r8, #0
	ble	.L2238
.L2256:
	ldr	r10, [r6, #240]
	add	r8, r8, #1
	mov	r1, r7
	str	r3, [fp, #-48]
	mul	r0, r10, r8
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r10, r0
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r8, r7
	rsb	r0, r0, r9
	strh	r0, [r3, #2]!	@ movhi
	bne	.L2256
.L2238:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r2, r4, #214
	movgt	r8, #0
	ble	.L2255
.L2257:
	ldr	r3, [r6, #244]
	add	r8, r8, #1
	mov	r1, r10
	str	r2, [fp, #-52]
	mul	r0, r3, r8
	str	r3, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	mov	r1, r10
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-52]
	cmp	r8, r10
	rsb	r0, r0, r9
	strh	r0, [r2, #2]!	@ movhi
	bne	.L2257
.L2255:
	cmp	r7, #1
	bne	.L2263
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L2264
.L2263:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L2265
.L2217:
	ldr	r3, .L2344+32
	mov	r2, r0
	ldr	r1, .L2344+92
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2324:
	ldr	r3, .L2344+32
	mov	r2, r0
	ldr	r1, .L2344+96
	mov	r0, r7
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2325:
	ldr	r3, .L2344+32
	mov	r0, r7
	ldr	r1, .L2344+100
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2326:
	ldr	r3, .L2344+32
	mov	r0, r7
	ldr	r1, .L2344+104
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2329:
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+108
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2330:
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+112
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2280:
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+116
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2316
.L2339:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L2242
.L2241:
	add	r8, r4, #130
	mov	r7, #0
	b	.L2253
.L2342:
	cmp	r3, r2
	bhi	.L2251
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2242
.L2253:
	ldr	r1, .L2344+120
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #244]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2342
.L2251:
	ldr	ip, .L2344+32
	mov	r0, #1
	str	r2, [sp]
	mov	r2, r7
	ldr	r1, .L2344+124
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2335:
	ldr	ip, .L2344+32
	mov	r3, #20
	ldr	r1, .L2344+128
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2341:
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+132
	ldr	r3, [r3, #68]
	blx	r3
	str	r7, [r4, #76]
	b	.L2278
.L2242:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2248
.L2249:
	ldr	r7, [r4, #68]
	ldrh	r3, [r6, #240]
	sub	r2, r7, #1
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #174]	@ movhi
	ble	.L2258
	add	r8, r7, #44
	add	r1, r4, #90
	add	lr, r4, #174
	add	r8, r4, r8, lsl #1
.L2259:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #174]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #174]	@ movhi
	bne	.L2259
.L2258:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L2343
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #244]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #214]	@ movhi
	ble	.L2261
	add	r8, r1, #64
	add	lr, r4, #214
	add	r1, r4, #130
	add	r8, r4, r8, lsl #1
.L2262:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #214]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #214]	@ movhi
	bne	.L2262
.L2261:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L2255
	ldr	ip, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+136
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2336:
	ldr	ip, .L2344+32
	mov	r2, r3
	ldr	r1, .L2344+140
	mov	r3, #22
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2334:
	ldr	r3, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+144
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2312
.L2338:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L2241
	b	.L2249
.L2343:
	ldr	ip, .L2344+32
	mov	r0, #1
	ldr	r1, .L2344+148
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2312
.L2345:
	.align	2
.L2344:
	.word	.LC270
	.word	.LC273
	.word	.LC275
	.word	.LC277
	.word	.LC281
	.word	.LC283
	.word	.LC304
	.word	.LC279
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC280
	.word	.LC285
	.word	.LC287
	.word	.LC290
	.word	g_event_report
	.word	.LC298
	.word	.LC297
	.word	.LC278
	.word	.LC291
	.word	.LC292
	.word	.LC289
	.word	.LC299
	.word	.LC301
	.word	.LC302
	.word	.LC271
	.word	.LC272
	.word	.LC274
	.word	.LC276
	.word	.LC282
	.word	.LC284
	.word	.LC305
	.word	.LC293
	.word	.LC294
	.word	.LC286
	.word	.LC300
	.word	.LC296
	.word	.LC288
	.word	.LC303
	.word	.LC295
	UNWIND(.fnend)
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	2
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
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
	ldr	r1, .L2356
	mov	r4, r0
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v
	ldr	r3, [r4, #156]
	cmp	r0, r3
	mov	r6, r0
	bcs	.L2352
	movw	r7, #2024
	ldr	r3, [r4, #2304]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2353
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2304]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2354
	ldr	r3, [r4, #2304]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2304]
	strb	r2, [r3, r5]
.L2348:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2353:
	ldr	r9, .L2356+4
	mov	r0, r4
	ldr	r1, .L2356+8
	str	r6, [r9, #-1244]
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2355
	ldr	ip, .L2356+12
	mov	r3, #1
	ldr	r0, [r4, #2304]
	mov	r2, r7
	ldr	r1, .L2356+8
	add	r0, r0, r5
	ldr	ip, [ip, #56]
	strb	r3, [r9, #-1271]
	strb	r3, [r9, #-1272]
	blx	ip
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2355:
	ldr	r3, .L2356+12
	mov	r2, r6
	ldr	r1, .L2356+16
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2348
.L2352:
	ldr	ip, .L2356+12
	mov	r2, r0
	ldr	r1, .L2356+20
	mov	r0, #1
	mvn	r8, #0
	ldr	ip, [ip, #68]
	blx	ip
	b	.L2348
.L2354:
	ldr	r3, .L2356+12
	mov	r2, r6
	ldr	r1, .L2356+16
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #2304]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2304]
	strb	r9, [r3, r5]
	b	.L2348
.L2357:
	.align	2
.L2356:
	.word	.LC306
	.word	.LANCHOR6
	.word	.LANCHOR6-1272
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC308
	.word	.LC307
	UNWIND(.fnend)
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	2
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	add	r5, r0, #40960
	ldr	r3, [r0, #2304]
	mov	r4, r0
	ldr	r2, [r5, #2652]
	movw	r0, #2024
	ldr	r1, [r5, #2636]
	ldr	r6, [r4, #2300]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r7, [r3, #32]
	beq	.L2424
	cmp	r1, #0
	bne	.L2362
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2362
.L2360:
	ldr	r1, .L2435
	add	r10, r4, #45056
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r10, #72]
	bhi	.L2425
	movw	r3, #15788
	mla	r9, r3, r7, r6
	ldr	r3, [r9, #64]
	cmp	r3, #0
	ldreq	r3, [r10, #76]
	bne	.L2426
.L2366:
	add	r3, r3, r0
	str	r3, [r10, #1104]
	ldr	r3, [r5, #2744]
	cmp	r3, #0
	beq	.L2367
	add	r6, r4, #45056
	mov	r7, #0
	add	r6, r6, #76
	mov	r8, r6
.L2368:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r7, #1
	str	r0, [r8, #4]!
	ldr	r2, [r5, #2744]
	cmp	r2, r7
	bhi	.L2368
	ldr	r3, [r9, #64]
	cmp	r3, #0
	beq	.L2369
	cmp	r2, #0
	addne	r8, r4, #45056
	movne	r7, #0
	addne	r8, r8, #140
	beq	.L2367
.L2373:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r7, #1
	str	r0, [r8, #4]!
	ldr	r2, [r5, #2744]
	cmp	r2, r7
	bhi	.L2373
.L2369:
	cmp	r2, #0
	beq	.L2367
	add	r8, r4, #45312
	mov	r7, #0
	add	r8, r8, #80
	str	r4, [fp, #-48]
	mov	r4, r6
	mov	r3, r8
	mov	r8, r7
	mov	r7, r3
	b	.L2384
.L2374:
	ldr	r1, [r10, #72]
	mov	r3, #1
	str	r0, [r4, #192]
	mov	r1, r3, asl r1
	str	r1, [r4, #1028]
.L2376:
	ldr	r1, [r9, #64]
	cmp	r1, #0
	beq	.L2378
	ldr	r1, [r4, #64]
	cmp	r1, #0
	bne	.L2379
	ldr	r0, [r10, #1104]
	mov	r3, #1
	str	r1, [r7, #964]
	mov	r0, r3, asl r0
	str	r1, [r7, #968]
	str	r0, [r7, #836]
	str	r0, [r7, #840]
.L2378:
	ldr	r1, [r5, #2744]
	add	r8, r8, #1
	add	r7, r7, #8
	cmp	r1, r8
	bls	.L2427
.L2384:
	ldr	r0, [r4, #4]!
	cmp	r0, #0
	beq	.L2374
	ldr	r3, [fp, #-48]
	ldr	r1, .L2435+4
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r4, #128]
	cmp	r1, #255
	bhi	.L2428
	ldr	lr, [r10, #72]
	mov	r3, #1
	ldr	r1, .L2435+8
	add	r0, r0, r3, asl lr
	ldr	r3, [fp, #-48]
	str	r0, [r4, #1028]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r4, #192]
	cmp	r1, #255
	bls	.L2376
	ldr	r3, .L2435+12
	mov	r2, r0
	ldr	r1, .L2435+16
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2424:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2360
.L2362:
	mov	r0, #0
.L2361:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2379:
	add	r3, r7, #832
	add	r1, r7, #128
	add	r2, r7, #960
	str	r9, [fp, #-56]
	ldr	r9, [fp, #-48]
	mov	r6, #0
	str	r8, [fp, #-52]
	mov	r8, r1
	str	r4, [fp, #-60]
	mov	r4, r7
	str	r7, [fp, #-64]
	mov	r7, r2
	str	r5, [fp, #-68]
	mov	r5, r3
.L2382:
	ldr	r1, .L2435+20
	add	r6, r6, #1
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v
	ldr	r1, .L2435+24
	add	r3, r0, #128
	str	r0, [r4]
	cmp	r3, #255
	bhi	.L2429
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v
	add	r3, r0, #512
	str	r0, [r8], #4
	cmp	r3, #1024
	bcs	.L2430
	ldr	r1, [r10, #1104]
	mov	r3, #1
	ldr	r2, [r4], #4
	cmp	r6, #2
	add	r3, r2, r3, asl r1
	str	r3, [r5, #4]!
	mov	r3, r3, asl #7
	mov	r3, r3, asr r1
	rsb	r3, r3, #128
	add	r3, r0, r3
	ssat	r3, #8, r3
	str	r3, [r7, #4]!
	bne	.L2382
	ldr	r8, [fp, #-52]
	ldr	r9, [fp, #-56]
	ldr	r4, [fp, #-60]
	ldr	r7, [fp, #-64]
	ldr	r5, [fp, #-68]
	b	.L2378
.L2427:
	ldr	r4, [fp, #-48]
.L2367:
	ldr	r6, [r5, #2636]
	cmp	r6, #0
	bne	.L2362
	ldr	r3, [r5, #2748]
	cmp	r3, #0
	beq	.L2362
	add	r7, r4, #45568
	add	r7, r7, #76
	mov	r8, r7
.L2385:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r5, #2748]
	cmp	r3, r6
	bhi	.L2385
	ldr	r2, [r9, #64]
	cmp	r2, #0
	bne	.L2431
.L2386:
	cmp	r3, #0
	beq	.L2362
	add	r8, r4, #45824
	mov	r3, #0
	add	r8, r8, #80
	str	r4, [fp, #-48]
	mov	r4, r3
	mov	r3, r5
	mov	r5, r7
	mov	r7, r8
	mov	r8, r3
	b	.L2400
.L2390:
	ldr	r1, [r10, #72]
	mov	r3, #1
	str	r0, [r5, #192]
	mov	r1, r3, asl r1
	str	r1, [r5, #836]
.L2392:
	ldr	r1, [r9, #64]
	cmp	r1, #0
	beq	.L2394
	ldr	r1, [r5, #64]
	cmp	r1, #0
	bne	.L2395
	ldr	r0, [r10, #1104]
	mov	r3, #1
	str	r1, [r7, #772]
	mov	r0, r3, asl r0
	str	r1, [r7, #776]
	str	r0, [r7, #644]
	str	r0, [r7, #648]
.L2394:
	ldr	r1, [r8, #2748]
	add	r4, r4, #1
	add	r7, r7, #8
	cmp	r1, r4
	bls	.L2362
.L2400:
	ldr	r0, [r5, #4]!
	cmp	r0, #0
	beq	.L2390
	ldr	r3, [fp, #-48]
	ldr	r1, .L2435+28
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r5, #128]
	cmp	r1, #255
	bhi	.L2432
	ldr	lr, [r10, #72]
	mov	r3, #1
	ldr	r1, .L2435+32
	add	r0, r0, r3, asl lr
	ldr	r3, [fp, #-48]
	str	r0, [r5, #836]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r5, #192]
	cmp	r1, #255
	bls	.L2392
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2395:
	add	r3, r7, #640
	add	r1, r7, #128
	add	r2, r7, #768
	str	r9, [fp, #-56]
	ldr	r9, [fp, #-48]
	mov	r6, #0
	str	r7, [fp, #-52]
	str	r5, [fp, #-60]
	mov	r5, r7
	str	r4, [fp, #-64]
	mov	r7, r2
	str	r8, [fp, #-68]
	mov	r4, r3
	mov	r8, r1
.L2398:
	ldr	r1, .L2435+40
	add	r6, r6, #1
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v
	ldr	r1, .L2435+44
	add	r3, r0, #128
	str	r0, [r5]
	cmp	r3, #255
	bhi	.L2433
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v
	add	r3, r0, #512
	str	r0, [r8], #4
	cmp	r3, #1024
	bcs	.L2434
	ldr	r1, [r10, #1104]
	mov	r3, #1
	ldr	r2, [r5], #4
	cmp	r6, #2
	add	r3, r2, r3, asl r1
	str	r3, [r4, #4]!
	mov	r3, r3, asl #7
	mov	r3, r3, asr r1
	rsb	r3, r3, #128
	add	r3, r0, r3
	ssat	r3, #8, r3
	str	r3, [r7, #4]!
	bne	.L2398
	sub	r4, fp, #64
	ldr	r7, [fp, #-52]
	ldr	r8, [fp, #-68]
	ldmia	r4, {r4, r5, r9}
	b	.L2394
.L2426:
	ldr	r1, .L2435+48
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	add	r2, r0, #7
	mov	r3, r0
	cmp	r2, #14
	str	r0, [r10, #76]
	bhi	.L2365
	ldr	r0, [r10, #72]
	b	.L2366
.L2429:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2430:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+56
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2431:
	cmp	r3, #0
	addne	r8, r4, #45568
	movne	r6, #0
	addne	r8, r8, #140
	beq	.L2362
.L2389:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r5, #2748]
	cmp	r3, r6
	bhi	.L2389
	b	.L2386
.L2428:
	ldr	r3, .L2435+12
	mov	r2, r0
	ldr	r1, .L2435+60
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2433:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+64
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2434:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+68
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2432:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+72
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2425:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+76
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2365:
	ldr	r3, .L2435+12
	mov	r0, #1
	ldr	r1, .L2435+80
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2361
.L2436:
	.align	2
.L2435:
	.word	.LC309
	.word	.LC313
	.word	.LC315
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC316
	.word	.LC317
	.word	.LC319
	.word	.LC321
	.word	.LC323
	.word	.LC324
	.word	.LC325
	.word	.LC327
	.word	.LC311
	.word	.LC318
	.word	.LC320
	.word	.LC314
	.word	.LC326
	.word	.LC328
	.word	.LC322
	.word	.LC310
	.word	.LC312
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	mov	r4, r0
	str	r1, [fp, #-92]
	mov	r1, #1
	ldr	r0, [r0, #2292]
	add	r10, r4, #40960
	bl	BsGet
	ldr	r9, [r10, #2648]
	sub	r3, r9, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-72]
	strb	r0, [r10, #2577]
	bne	.L2705
.L2438:
	ldr	r1, .L2748
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r10, #2652]
	ldr	r2, [r4, #156]
	blt	.L2440
	cmp	r0, r2
	bge	.L2440
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-88]
	bne	.L2706
	ldr	r1, [r10, #2652]
	movw	r5, #2024
	ldr	r2, [r4, #2304]
	movw	r6, #15788
	ldr	r3, [r4, #2300]
	mla	r5, r5, r1, r2
	ldrb	r1, [r5, #2]	@ zero_extendqisi2
	ldr	r2, [r5, #32]
	cmp	r1, #0
	mla	r6, r6, r2, r3
	bne	.L2707
.L2446:
	mov	r3, #0
	strb	r3, [r10, #2579]
.L2447:
	ldr	r7, [r6, #160]
	ldr	r3, [r6, #164]
	cmp	r7, #0
	beq	.L2449
	cmp	r3, #0
	beq	.L2449
	ldr	r0, [r6, #76]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r8, r0
	ldr	r0, [r6, #72]
	add	r0, r7, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	r7, [r6, #216]
	mov	r3, #1
	mov	r1, #0
	mov	r7, r7, asl r3
	mov	r7, r3, asl r7
	mul	r8, r0, r8
	cmp	r8, r3
	ble	.L2451
.L2452:
	add	r1, r1, #1
	cmp	r8, r3, asl r1
	bgt	.L2452
.L2451:
	ldrb	r3, [r10, #2577]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r2, #0
	beq	.L2708
.L2453:
	mul	r8, r7, r8
	ldrb	r7, [r10, #2579]	@ zero_extendqisi2
	str	r2, [r10, #2728]
	cmp	r7, #0
	str	r8, [r10, #2732]
	ldr	r3, [r4, #188]
	str	r3, [r10, #2624]
	beq	.L2709
.L2456:
	ldr	r3, [r5, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	streq	r3, [r10, #2716]
	bne	.L2710
.L2562:
	ldrb	r3, [r5, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2567
.L2573:
	ldr	r3, [r10, #2728]
	cmp	r3, #0
	bne	.L2711
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2575
	ldr	r2, [fp, #-72]
	cmp	r2, #0
	beq	.L2579
	ldr	r2, [fp, #-92]
	cmp	r2, #0
	strneb	r3, [r4]
	mov	r3, #1
	strb	r3, [r4, #2]
.L2578:
	ldr	r3, [r10, #2624]
	ldr	r2, [fp, #-72]
	cmp	r3, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	bne	.L2712
.L2579:
	mov	r3, #0
	strb	r3, [r4, #1]
.L2580:
	mov	r0, r4
	bl	HEVC_IsNewPic
	add	r3, r4, #45056
	str	r0, [r3, #68]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L2685:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2711:
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2579
	b	.L2578
.L2707:
	ldrb	r3, [r10, #2577]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2446
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2579]
	b	.L2447
.L2709:
	ldr	r3, [r5, #36]
	cmp	r3, #0
	ldrne	r8, .L2748+192
	beq	.L2461
.L2460:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [r8, #68]
	ldr	r1, .L2748+4
	add	r7, r7, #1
	mov	r2, r0
	mov	r0, #19
	blx	r3
	ldr	r3, [r5, #36]
	cmp	r3, r7
	bhi	.L2460
.L2461:
	ldr	r1, .L2748+8
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r10, #2636]
	bhi	.L2713
	ldrb	r3, [r5, #4]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r3, #1
	streqb	r3, [r10, #2576]
	bne	.L2714
.L2463:
	sub	r9, r9, #19
	cmp	r9, #1
	bhi	.L2715
	mov	r3, #0
	str	r3, [r10, #2624]
	str	r3, [r4, #188]
	ldr	r3, [r10, #2644]
	cmp	r3, #0
	streq	r3, [r10, #2628]
	streq	r3, [r4, #184]
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2696
.L2582:
	mov	r3, #0
	strb	r3, [r10, #2583]
	str	r3, [fp, #-96]
.L2584:
	ldr	r3, [r10, #2636]
	cmp	r3, #2
	beq	.L2506
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r10, #2584]
	cmp	r0, #0
	bne	.L2716
	ldr	r3, [r10, #2636]
	ldr	r2, [r5, #40]
	cmp	r3, #0
	str	r2, [r10, #2744]
	bne	.L2512
	ldr	r3, [r5, #44]
	str	r3, [r10, #2748]
.L2513:
	ldr	r3, [fp, #-96]
	cmp	r3, #0
	beq	.L2717
	ldr	r3, [fp, #-96]
	ldr	r2, [r3, #24]
	cmp	r2, #16
	bhi	.L2516
	cmp	r2, #0
	moveq	r3, r2
	beq	.L2518
	ldr	r3, [fp, #-96]
	add	r2, r2, #52
	add	r1, r3, #52
	add	r2, r3, r2
	mov	r3, #0
.L2520:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	addne	r3, r3, #1
	cmp	r1, r2
	bne	.L2520
	cmp	r3, #1
	movle	r2, #0
	movgt	r2, #1
.L2518:
	ldrb	r1, [r5, #22]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	beq	.L2718
	add	r2, r4, #46848
	add	r1, r4, #43520
	add	r2, r2, #160
	add	r1, r1, #16
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L2719
.L2514:
	ldr	r3, [r10, #2636]
	cmp	r3, #0
	beq	.L2586
.L2521:
	cmp	r3, #2
	beq	.L2506
.L2587:
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2720
.L2522:
	ldrb	r3, [r10, #2583]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #2636]
	beq	.L2532
	cmp	r3, #0
	beq	.L2721
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r10, #2587]
	beq	.L2527
.L2530:
	ldr	r3, [r10, #2744]
	cmp	r3, #1
	bls	.L2693
.L2528:
	ldr	r1, .L2748+12
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	ldrb	r2, [r10, #2587]	@ zero_extendqisi2
	cmp	r2, #0
	str	r0, [r10, #2688]
	bne	.L2533
	ldr	r1, [r10, #2684]
	sub	r1, r1, #1
.L2535:
	cmp	r1, r0
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	beq	.L2693
	ldr	ip, .L2748+192
	mov	r3, r0
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L2748+16
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2705:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2578]
	b	.L2438
.L2708:
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r10, #2656]
	cmp	r0, #0
	ldr	r2, [r6, #244]
	ldr	r3, [r6, #240]
	mul	r3, r3, r2
	blt	.L2455
	cmp	r3, r0
	bls	.L2455
	mul	r2, r7, r0
	b	.L2453
.L2710:
	ldr	r1, .L2748+20
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	str	r0, [r10, #2716]
	ldr	r3, [r5, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r6, #244]
	subeq	r3, r3, #1
	beq	.L2558
	cmp	r3, #256
	ldreq	r2, [r5, #68]
	ldreq	r3, [r5, #72]
	ldrne	r3, [r6, #244]
	ldrne	r2, [r5, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L2558:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r0, r3
	bhi	.L2722
	cmp	r0, #0
	beq	.L2562
	ldr	r1, .L2748+24
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r1, r0, #1
	str	r1, [r10, #2640]
	bhi	.L2723
	ldr	r3, [r10, #2716]
	cmp	r3, #0
	addne	r7, r4, #43520
	movne	r6, #0
	addne	r7, r7, #192
	bne	.L2566
	b	.L2562
.L2724:
	ldr	r1, [r10, #2640]
.L2566:
	ldr	r0, [r4, #2292]
	add	r6, r6, #1
	bl	BsGet
	str	r0, [r7, #4]!
	ldr	r3, [r10, #2716]
	cmp	r3, r6
	bhi	.L2724
	ldrb	r3, [r5, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2573
.L2567:
	ldr	r1, .L2748+28
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	cmp	r0, #256
	str	r0, [r10, #2720]
	bhi	.L2725
	ldr	r0, [r4, #2292]
	bl	BsResidBits
	ldr	r3, [r10, #2720]
	cmp	r0, r3
	bcc	.L2571
	cmp	r3, #0
	movne	r5, #0
	beq	.L2573
.L2574:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [r10, #2720]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r10, #2724]
	bhi	.L2574
	b	.L2573
.L2506:
	ldrb	r3, [r10, #2583]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2527
	mov	r3, #2
	mov	r2, #1
	strb	r2, [r10, #2587]
.L2532:
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2537
	cmp	r3, #1
	beq	.L2540
.L2537:
	ldrb	r2, [r5, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2526
	cmp	r3, #0
	bne	.L2526
.L2540:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r10, #2636]
	bne	.L2726
.L2526:
	cmp	r3, #2
	beq	.L2541
	ldr	r1, .L2748+32
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r10, #2692]
	bhi	.L2727
.L2541:
	ldr	r1, .L2748+36
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	str	r0, [r10, #2696]
	ldr	r2, [r5, #48]
	add	r2, r0, r2
	str	r2, [r10, #2632]
	ldr	r3, [r6, #104]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2728
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2729
.L2543:
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2694
	ldrb	r3, [r5, #19]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r10, #2588]
	bne	.L2730
.L2551:
	ldrb	r0, [r5, #20]	@ zero_extendqisi2
	strb	r0, [r10, #2589]
	ldr	r3, [r5, #76]
	str	r3, [r10, #2708]
	ldr	r3, [r5, #80]
	str	r3, [r10, #2712]
.L2548:
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2554
	ldr	r2, [r10, #2580]
	bic	r3, r2, #-16777216
	bic	r3, r3, #255
	adds	r3, r3, #0
	movne	r3, #1
.L2554:
	ldrb	r2, [r5, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2555
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L2731
.L2555:
	strb	r2, [r10, #2590]
	b	.L2456
.L2575:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	strneb	r2, [r4, #2]
	b	.L2579
.L2712:
	ldr	r3, [r10, #2648]
	cmp	r3, #21
	moveq	r3, #1
	streqb	r3, [r4, #1]
	bne	.L2579
	b	.L2580
.L2718:
	ldr	r3, [r10, #2636]
	cmp	r3, #0
	bne	.L2587
.L2586:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [r10, #2636]
	strb	r0, [r10, #2585]
	b	.L2521
.L2694:
	ldrb	r0, [r10, #2589]	@ zero_extendqisi2
	b	.L2548
.L2715:
	ldr	r1, [r6, #132]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r2, #1
	str	r0, [r10, #2664]
	mov	r8, r0
	ldr	r3, [r6, #128]
	ldr	r7, [r4, #184]
	mov	r3, r2, asl r3
	str	r0, [fp, #-104]
	str	r3, [fp, #-108]
	mov	r1, r3
	mov	r0, r7
	bl	__aeabi_uidivmod
	cmp	r1, r8
	rsb	r3, r1, r7
	bls	.L2465
	ldr	r0, [fp, #-108]
	ldr	r2, [fp, #-104]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	movcs	r2, r0
	addcs	r3, r3, r2
	bcc	.L2465
.L2466:
	ldr	r1, [r10, #2648]
	ldr	r0, [fp, #-104]
	sub	r2, r1, #16
	cmp	r2, #2
	movls	r3, #0
	add	r3, r3, r0
	str	r3, [r10, #2624]
	str	r3, [r4, #188]
	ldr	r0, [r10, #2644]
	cmp	r0, #0
	bne	.L2468
	cmp	r1, #15
	bls	.L2732
.L2469:
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
.L2470:
	sub	r1, r1, #7
	bics	r1, r1, #2
	andne	r2, r2, #1
	moveq	r2, #0
	cmp	r2, #0
	strne	r3, [r10, #2628]
	strne	r3, [r4, #184]
.L2468:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r10, #2580]
	cmp	r0, #0
	beq	.L2471
	ldr	r3, [r6, #228]
	cmp	r3, #1
	movhi	r1, #0
	movhi	r2, #1
	bls	.L2473
.L2475:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2475
	cmp	r1, #0
	bne	.L2733
.L2473:
	mov	r1, #0
	str	r1, [r10, #2668]
.L2478:
	mov	r2, #204
	add	r0, r4, #46592
	mla	r1, r2, r1, r6
	add	r0, r0, #212
	str	r0, [fp, #-96]
	add	r1, r1, #2720
	add	r1, r1, #12
	bl	memcpy
.L2474:
	ldrb	r3, [r6, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2479
	add	r3, r4, #45056
	str	r3, [fp, #-84]
	mov	r1, r3
	ldr	r3, [r6, #232]
	ldr	r2, [r1, #1768]
	cmp	r3, #0
	ldr	r3, [r1, #1764]
	add	r3, r2, r3
	str	r3, [fp, #-112]
	bne	.L2480
.L2483:
	mov	r9, #0
.L2481:
	ldr	r1, .L2748+40
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	ldr	ip, [fp, #-84]
	ldr	r1, [r10, #2672]
	str	r0, [r10, #2676]
	add	r0, r0, r1
	ldr	r2, [ip, #1764]
	ldr	r3, [ip, #1768]
	str	r0, [ip, #1780]
	add	lr, r3, r2
	add	lr, lr, r0
	cmp	lr, #16
	bhi	.L2734
	ldr	r3, [fp, #-112]
	cmp	r0, #0
	sub	r7, r3, #1
	add	r7, r0, r7
	beq	.L2499
	add	r3, r7, #11200
	add	r7, r7, #46848
	add	r3, r3, #49
	add	r7, r7, #9
	add	r7, r4, r7
	str	r7, [fp, #-64]
	mov	r3, r3, asl #2
	add	r8, r4, #44544
	add	ip, r3, #64
	str	ip, [fp, #-56]
	ldr	r7, [fp, #-56]
	add	r0, r4, #44800
	str	r8, [fp, #-48]
	add	lr, r4, #43520
	add	r8, r4, r7
	add	r7, r4, r3
	ldr	r3, [fp, #-48]
	mov	ip, r0
	str	r0, [fp, #-52]
	add	r0, r0, #128
	str	r0, [fp, #-60]
	add	r0, ip, #4
	add	ip, lr, #31
	add	lr, r3, #196
	ldr	r3, [fp, #-52]
	add	r2, r4, #43520
	str	r7, [fp, #-100]
	add	r2, r2, #46
	add	r3, r3, #68
	str	lr, [fp, #-48]
	str	r5, [fp, #-116]
	mov	lr, r3
	mov	r3, #0
	str	r6, [fp, #-76]
	mov	r7, lr
	str	r9, [fp, #-80]
	mov	r9, ip
	ldr	r5, [fp, #-64]
	str	r4, [fp, #-52]
	mov	r4, r3
	str	r10, [fp, #-64]
	mov	r10, r0
	str	r2, [fp, #-120]
	str	r3, [fp, #-68]
	str	r2, [fp, #-56]
	ldr	r6, [fp, #-100]
	b	.L2498
.L2737:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	ldreq	r0, [fp, #-80]
	bne	.L2735
.L2489:
	ldr	r2, [fp, #-76]
	add	r3, r2, r0
	add	r0, r0, #62
	ldrb	r1, [r3, #16]	@ zero_extendqisi2
	ldr	r3, [r2, r0, asl #2]
	strb	r1, [r5]
.L2492:
	ldr	r2, [fp, #-60]
	mov	r1, #1
	str	r3, [r2, #4]!
	ldr	r3, [fp, #-52]
	str	r2, [fp, #-60]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	cmp	r0, #0
	str	r3, [fp, #-56]
	bne	.L2736
	cmp	r4, #0
	streq	r4, [fp, #-68]
	beq	.L2496
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	ldr	r3, [r3, #2672]
	cmp	r3, r4
	moveq	r2, #0
	str	r2, [fp, #-68]
.L2496:
	mov	r3, #0
	str	r3, [r8]
.L2495:
	ldr	r3, [fp, #-84]
	add	r4, r4, #1
	ldr	r2, [fp, #-48]
	sub	r6, r6, #4
	sub	r8, r8, #4
	sub	r5, r5, #1
	ldr	r3, [r3, #1780]
	add	r2, r2, #4
	add	r10, r10, #4
	add	r9, r9, #1
	cmp	r3, r4
	str	r2, [fp, #-48]
	add	r7, r7, #4
	bls	.L2497
	ldr	r3, [fp, #-64]
	ldr	r1, [r3, #2672]
.L2498:
	cmp	r1, r4
	bhi	.L2737
	ldr	r3, [fp, #-76]
	ldr	r1, [r3, #132]
	ldr	r3, [fp, #-52]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-52]
	mov	r1, #1
	str	r0, [r10]
	str	r0, [fp, #-100]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-100]
	uxtb	r0, r0
	strb	r0, [r9]
	strb	r0, [r5]
	b	.L2492
.L2465:
	ldr	r2, [fp, #-104]
	cmp	r1, r2
	bcs	.L2466
	rsb	r1, r1, r2
	ldr	r2, [fp, #-108]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
	b	.L2466
.L2714:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2576]
	b	.L2463
.L2729:
	ldr	r1, .L2748+44
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r10, #2700]
	cmp	r3, #24
	bhi	.L2738
	ldr	r3, [r5, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L2739
	ldr	r1, .L2748+48
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r10, #2704]
	cmp	r3, #24
	bhi	.L2740
	ldr	r2, [r5, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L2543
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2440:
	ldr	r1, .L2748+192
	mov	r3, r0
	str	r2, [sp]
	mov	r0, #1
	ldr	r2, .L2748+56
	ldr	ip, [r1, #68]
	ldr	r1, .L2748+60
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2693:
	ldr	r3, [r10, #2636]
	b	.L2532
.L2479:
	ldrb	r3, [r6, #11]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r10, #2583]
	bne	.L2741
.L2504:
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2584
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r10, #2581]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2582]
	b	.L2584
.L2696:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r10, #2581]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2582]
	b	.L2582
.L2720:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2586]
	b	.L2522
.L2512:
	str	r0, [r10, #2748]
.L2511:
	cmp	r3, #2
	bne	.L2513
	b	.L2514
.L2716:
	ldr	r1, .L2748+64
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #1
	str	r2, [r10, #2680]
	cmp	r2, #16
	bhi	.L2742
	ldr	r3, [r10, #2636]
	str	r2, [r10, #2744]
	cmp	r3, #0
	movne	r2, #0
	strne	r2, [r10, #2684]
	strne	r2, [r10, #2748]
	bne	.L2511
	ldr	r1, .L2748+68
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	add	r2, r0, #1
	str	r2, [r10, #2684]
	cmp	r2, #16
	strls	r2, [r10, #2748]
	ldrls	r3, [r10, #2636]
	bls	.L2511
	ldr	ip, .L2748+192
	mov	r3, #16
	ldr	r1, .L2748+72
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2721:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [r10, #2636]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r10, #2587]
	beq	.L2541
	cmp	r0, #0
	bne	.L2530
	ldr	r2, [r10, #2748]
	cmp	r2, #1
	bhi	.L2528
	b	.L2532
.L2527:
	mov	r3, #2
	b	.L2537
.L2533:
	ldr	r1, [r10, #2680]
	sub	r1, r1, #1
	b	.L2535
.L2732:
	tst	r1, #1
	movne	r2, #1
	bne	.L2470
	b	.L2469
.L2480:
	ldr	r1, .L2748+76
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v
	str	r0, [r10, #2672]
	mov	r2, r0
	ldr	r3, [r6, #232]
	cmp	r0, r3
	bhi	.L2743
	cmp	r3, #1
	bls	.L2483
	mov	r9, #0
	mov	r2, #1
.L2484:
	add	r9, r9, #1
	cmp	r3, r2, asl r9
	bhi	.L2484
	str	r9, [fp, #-88]
	b	.L2481
.L2571:
	ldr	ip, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+80
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2736:
	ldr	r3, [fp, #-52]
	ldr	r1, .L2748+84
	ldr	r0, [r3, #2292]
	bl	HEVC_ue_v
	cmp	r4, #0
	str	r0, [r7]
	beq	.L2494
	ldr	r3, [fp, #-64]
	ldr	r3, [r3, #2672]
	cmp	r3, r4
	ldrne	r3, [fp, #-68]
	addne	r0, r0, r3
.L2494:
	str	r0, [r6]
	mov	r3, #1
	str	r0, [fp, #-68]
	str	r3, [r8]
	b	.L2495
.L2735:
	ldr	r3, [fp, #-52]
	ldr	r1, [fp, #-88]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-48]
	cmp	r0, #0
	str	r0, [r3]
	blt	.L2744
	ldr	r3, [fp, #-76]
	ldr	r1, [r3, #232]
	sub	r1, r1, #1
	cmp	r1, r0
	bcs	.L2489
	mov	r7, r4
.L2491:
	ldr	ip, .L2748+192
	mov	r3, r0
	str	r1, [sp]
	mov	r2, r7
	ldr	r1, .L2748+88
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2449:
	ldr	ip, .L2748+192
	mov	r2, r7
	ldr	r1, .L2748+92
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2731:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2590]
	b	.L2456
.L2730:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r10, #2588]
	cmp	r0, #0
	beq	.L2551
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r10, #2589]
	cmp	r0, #0
	bne	.L2548
	ldr	r1, .L2748+96
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r10, #2708]
	bhi	.L2745
.L2552:
	ldr	r1, .L2748+100
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r10, #2712]
	bls	.L2694
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+104
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r5, #80]
	ldrb	r0, [r10, #2589]	@ zero_extendqisi2
	str	r3, [r10, #2712]
	b	.L2548
.L2497:
	ldr	r2, [fp, #-112]
	cmp	r3, #0
	ldr	r5, [fp, #-116]
	add	r2, r2, #11712
	ldr	r6, [fp, #-76]
	ldr	r4, [fp, #-52]
	add	r2, r2, #23
	ldr	r10, [fp, #-64]
	beq	.L2499
	add	r2, r2, r3
	add	lr, r4, #44800
	add	lr, lr, #132
	mov	r7, #0
	add	r2, r4, r2, lsl #2
	ldr	r8, [fp, #-108]
	ldr	ip, [fp, #-120]
	ldr	r9, [fp, #-104]
	str	r4, [fp, #-48]
	b	.L2502
.L2747:
	ldr	r0, [r10, #2624]
	ldr	r4, [lr]
	rsb	r1, r9, r0
	add	r1, r1, r4
	ldr	r4, [r2, #-1948]
	mls	r1, r4, r8, r1
	rsb	r0, r0, r1
	str	r0, [r2, #-68]
	str	r1, [r2]
.L2501:
	add	r7, r7, #1
	add	lr, lr, #4
	cmp	r3, r7
	sub	r2, r2, #4
	bls	.L2746
.L2502:
	ldrb	r1, [ip, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2747
	ldr	r1, [lr]
	str	r1, [r2]
	ldr	r0, [r10, #2624]
	rsb	r1, r0, r1
	str	r1, [r2, #-68]
	b	.L2501
.L2706:
	ldr	r3, [r4, #216]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #188]
	add	r4, r4, #45056
	str	r3, [r10, #2624]
	bl	HEVC_IsNewPic
	ldr	r3, .L2748+192
	ldr	r1, .L2748+108
	ldr	r3, [r3, #68]
	str	r0, [r4, #68]
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2746:
	ldr	r4, [fp, #-48]
.L2487:
	ldr	r2, [fp, #-112]
	add	r2, r3, r2
	ldr	r3, [fp, #-84]
	cmp	r2, #16
	str	r2, [r3, #1772]
	bls	.L2479
	ldr	ip, .L2748+192
	mov	r3, #16
	ldr	r1, .L2748+112
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2749:
	.align	2
.L2748:
	.word	.LC329
	.word	.LC335
	.word	.LC334
	.word	.LC353
	.word	.LC354
	.word	.LC370
	.word	.LC372
	.word	.LC374
	.word	.LC356
	.word	.LC358
	.word	.LC341
	.word	.LC360
	.word	.LC363
	.word	.LC365
	.word	.LANCHOR1+488
	.word	.LC330
	.word	.LC346
	.word	.LC348
	.word	.LC349
	.word	.LC339
	.word	.LC376
	.word	.LC344
	.word	.LC343
	.word	.LC332
	.word	.LC366
	.word	.LC368
	.word	.LC369
	.word	.LC331
	.word	.LC345
	.word	.LC337
	.word	.LC338
	.word	.LC359
	.word	.LC333
	.word	.LC375
	.word	.LC336
	.word	.LC351
	.word	.LC357
	.word	.LC371
	.word	.LC367
	.word	.LC362
	.word	.LC361
	.word	.LC355
	.word	.LC364
	.word	.LC352
	.word	.LC373
	.word	.LC342
	.word	.LC350
	.word	.LC347
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC340
.L2471:
	add	r7, r4, #46592
	ldr	r3, [r6, #228]
	add	r7, r7, #212
	mov	r1, r6
	mov	r0, r4
	mov	r2, r7
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r7, [fp, #-96]
	beq	.L2474
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+116
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2741:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r10, #2583]
	b	.L2504
.L2733:
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r10, #2668]
	cmp	r0, #0
	ldr	r3, [r6, #228]
	mov	r1, r0
	sub	r3, r3, #1
	blt	.L2477
	cmp	r3, r0
	bcs	.L2478
.L2477:
	ldr	ip, .L2748+192
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L2748+120
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2728:
	ldr	ip, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+124
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2455:
	ldr	ip, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+128
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2725:
	ldr	r3, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+132
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2744:
	ldr	r6, [fp, #-76]
	mov	r7, r4
	ldr	r1, [r6, #232]
	sub	r1, r1, #1
	b	.L2491
.L2713:
	ldr	r3, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+136
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2516:
	ldr	ip, .L2748+192
	mov	r3, #16
	ldr	r1, .L2748+140
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2727:
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+144
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2722:
	ldr	ip, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+148
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2499:
	mov	r3, #0
	b	.L2487
.L2745:
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+152
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r5, #76]
	str	r3, [r10, #2708]
	b	.L2552
.L2739:
	ldr	ip, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+156
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2738:
	ldr	r3, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+160
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2726:
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+164
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2740:
	ldr	r3, .L2748+192
	mov	r2, r0
	ldr	r1, .L2748+168
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2719:
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+172
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2723:
	ldr	r3, .L2748+192
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L2748+176
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2734:
	ldr	ip, .L2748+192
	mov	lr, #16
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L2748+180
	ldr	ip, [ip, #68]
	str	lr, [sp, #4]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2717:
	ldr	r3, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+184
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2685
.L2742:
	ldr	ip, .L2748+192
	mov	r3, #16
	ldr	r1, .L2748+188
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
.L2743:
	ldr	ip, .L2748+192
	mov	r0, #1
	ldr	r1, .L2748+196
	ldr	ip, [ip, #68]
	blx	ip
	mvn	r0, #0
	b	.L2685
	UNWIND(.fnend)
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	2
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #2316]
	mov	r4, r0
	cmp	r1, #0
	beq	.L2751
	ldr	r0, [r0, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L2751:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.align	2
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
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
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.align	2
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #2316]
	mov	r4, r0
	cmp	r1, #0
	beq	.L2757
	ldr	r0, [r0, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L2757:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.align	2
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
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
	ldr	r3, [r0, #160]
	mov	r7, r0
	cmp	r3, #0
	beq	.L2765
	mov	r4, #0
	add	r8, r0, #53248
	mov	r5, r4
	mov	r6, r4
.L2764:
	ldr	r3, [r8, #4056]
	add	r5, r5, #1
	add	r3, r3, r4
	ldr	r1, [r3, #24]
	cmp	r1, #0
	beq	.L2763
	ldr	r0, [r7, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r8, #4056]
	add	r3, r3, r4
	str	r6, [r3, #24]
.L2763:
	ldr	r3, [r7, #160]
	add	r4, r4, #28
	cmp	r3, r5
	bhi	.L2764
.L2765:
	mov	r0, #0
	mov	r3, #2
	str	r0, [r7, #208]
	str	r0, [r7, #224]
	str	r0, [r7, #216]
	str	r3, [r7, #172]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r5, r0
	mov	r8, r1
	bl	HEVC_ClearAllSlice
	add	r9, r5, #2496
	mov	r4, r5
	add	r9, r9, #12
	mov	r6, #17
	mov	r7, #0
.L2776:
	ldr	r3, [r9, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L2772
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2772:
	ldr	r3, [r4, #2580]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2773
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2773:
	ldr	r3, [r4, #2648]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2774
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2774:
	ldr	r3, [r4, #2716]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2775
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2775:
	subs	r6, r6, #1
	str	r7, [r4, #2716]
	str	r7, [r4, #2648]
	add	r4, r4, #4
	str	r7, [r4, #2576]
	str	r7, [r4, #2508]
	bne	.L2776
	add	r7, r5, #24576
	ldr	r4, .L2818
	mov	r9, #0
	mov	r2, #200
	ldr	r3, [r7, #2604]
	mov	r1, r9
	add	r0, r5, #2784
	ldr	r3, [r3, #236]
	str	r9, [r5, #2492]
	add	r3, r3, #1
	str	r9, [r5, #2504]
	cmp	r3, #17
	str	r9, [r5, #2508]
	str	r9, [r5, #2500]
	movhi	r3, #17
	str	r9, [r5, #2496]
	str	r3, [r5, #2488]
	ldr	r3, [r4, #48]
	blx	r3
	add	r2, r5, #2304
	add	r2, r2, #12
	add	r3, r5, #2384
	mov	r0, r9
	mov	r1, #16
	str	r9, [r5, #2788]
	str	r1, [r5, #2784]
.L2779:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L2779
	add	r2, r5, #2448
	add	ip, r5, #40960
	add	r2, r2, #4
	mov	r0, r1
	str	r1, [ip, #2736]
.L2780:
	str	r0, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L2780
	cmp	r8, r1
	str	r1, [ip, #2740]
	bne	.L2781
	ldr	r3, [r5, #2308]
	ldr	r3, [r3, #892]
	cmp	r3, #1
	beq	.L2781
.L2782:
	ldr	r1, [r5, #180]
	cmp	r1, #0
	addne	r2, r5, #2096
	movne	r3, #0
	movne	r0, r3
	beq	.L2790
.L2789:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2789
.L2790:
	ldr	r3, [r5, #160]
	cmp	r3, #0
	addne	r8, r5, #53248
	movne	r4, #0
	movne	r7, r4
	beq	.L2788
.L2792:
	ldr	r3, [r8, #4056]
	add	r4, r4, #1
	add	r3, r3, r6
	ldr	r3, [r3, #24]
	cmp	r3, #0
	mov	r1, r3
	beq	.L2791
	ldr	r2, [r5, #2316]
	cmp	r3, r2
	beq	.L2791
	ldr	r0, [r5, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r8, #4056]
	add	r3, r3, r6
	str	r7, [r3, #24]
.L2791:
	ldr	r3, [r5, #160]
	add	r6, r6, #28
	cmp	r3, r4
	bhi	.L2792
.L2788:
	mov	r0, #0
.L2783:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2781:
	mov	r8, #20
	str	r8, [r5, #176]
	str	r8, [r5, #180]
	mov	r0, r5
	ldr	r1, [r7, #2604]
	ldr	r3, [r1, #240]
	ldr	ip, [r1, #244]
	ldr	r2, [r1, #148]
	str	r8, [sp, #8]
	mov	r1, r3, asl r2
	str	ip, [sp]
	mov	r2, ip, asl r2
	str	r8, [sp, #4]
	bl	HEVC_ArrangeVahbMem
	ldr	r3, [r5, #2308]
	ldr	r3, [r3, #892]
	cmp	r3, #1
	beq	.L2793
	cmp	r0, #1
	bne	.L2816
	ldr	r0, [r5, #244]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, r8
	ble	.L2817
.L2785:
	str	r0, [r5, #176]
	b	.L2782
.L2817:
	ldr	r0, [r5, #244]
	bl	FSP_GetTotalValidFsNum
	b	.L2785
.L2816:
	ldr	r3, [r4, #68]
	mov	r0, #0
	ldr	r2, .L2818+4
	ldr	r1, .L2818+8
	blx	r3
	mvn	r0, #4
	b	.L2783
.L2793:
	mvn	r0, #1
	b	.L2783
.L2819:
	.align	2
.L2818:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+516
	.word	.LC377
	UNWIND(.fnend)
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	2
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
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
	ldr	r3, [r0, #160]
	mov	r6, r0
	cmn	r3, #1
	beq	.L2824
	mov	r4, #0
	add	r7, r0, #53248
	mov	r5, r4
	b	.L2823
.L2822:
	ldr	r3, [r6, #160]
	add	r3, r3, #1
	cmp	r3, r5
	bls	.L2824
.L2823:
	ldr	r1, [r7, #3252]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #100
	ldr	r3, [r1, #36]
	cmp	r3, #1
	bne	.L2822
	ldr	r0, [r6, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #160]
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2823
.L2824:
	mov	r0, #0
	strb	r0, [r6, #4]
	str	r0, [r6, #140]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.align	2
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
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
	ldr	r6, .L2840
	mov	r4, r0
	ldr	r1, .L2840+4
	mov	r0, #22
	add	r5, r4, #57344
	ldr	r3, [r6, #68]
	mov	r8, #0
	blx	r3
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_ClearAllNal
	add	r0, r4, #50944
	add	r0, r0, #56
	add	r5, r5, #40
	bl	ResetVoQueue
	mov	r7, r8
	mov	r9, #20
.L2828:
	strb	r7, [r5, #-72]
	mov	r3, #16
	str	r7, [r5, #-68]
	mov	r0, r5
	strb	r7, [r5, #-71]
	mov	r2, #504
	str	r7, [r5, #-60]
	mov	r1, #0
	strb	r7, [r5, #-70]
	str	r9, [r5, #-48]
	str	r3, [r5, #-44]
	ldr	r3, [r6, #48]
	blx	r3
	str	r8, [r5, #196]
	add	r8, r8, #1
	sub	r3, r5, #72
	cmp	r8, #20
	str	r7, [r5, #-24]
	str	r3, [r5, #-4]
	add	r5, r5, #584
	bne	.L2828
	add	r3, r4, #2096
	add	r1, r4, #2176
	mov	r2, #0
.L2829:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L2829
	ldr	r3, [r4, #160]
	cmp	r3, #0
	addne	ip, r4, #53248
	movne	r3, #0
	movne	r0, r3
	movne	r1, r3
	beq	.L2833
.L2832:
	ldr	r2, [ip, #4056]
	add	r0, r0, #1
	str	r1, [r2, r3]
	ldr	r2, [ip, #4056]
	add	r2, r2, r3
	str	r1, [r2, #20]
	ldr	r2, [ip, #4056]
	add	r2, r2, r3
	add	r3, r3, #28
	str	r1, [r2, #24]
	ldr	r2, [r4, #160]
	cmp	r2, r0
	bhi	.L2832
.L2833:
	ldr	r3, [r6, #48]
	mov	r2, #200
	mov	r1, #0
	add	r0, r4, #2784
	blx	r3
	add	ip, r4, #2704
	add	r0, r4, #2640
	add	r1, r4, #2496
	add	ip, ip, #8
	add	r0, r0, #4
	add	r1, r1, #12
	add	lr, r4, #2576
	mov	r3, #16
	mov	r2, #17
	str	r3, [r4, #2784]
	mov	r3, #0
.L2831:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [r0, #4]!
	str	r3, [lr, #4]!
	str	r3, [r1, #4]!
	bne	.L2831
	add	r1, r4, #2304
	add	ip, r4, #2448
	add	r1, r1, #12
	add	ip, ip, #4
	add	r3, r4, #2384
	mov	r0, r2
	mov	lr, #17
	str	r2, [r4, #2492]
	str	r2, [r4, #2496]
	str	r2, [r4, #2500]
	str	r2, [r4, #2504]
	str	r2, [r4, #2508]
	str	lr, [r4, #2488]
.L2834:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	mov	r5, #0
	bne	.L2834
	add	r0, r4, #43520
	mov	r9, #2
	str	r5, [r4, #2316]
	mov	r1, r5
	str	r5, [r4, #208]
	movw	r2, #3732
	str	r5, [r4, #224]
	add	r0, r0, #16
	str	r5, [r4, #216]
	add	r7, r4, #2448
	str	r9, [r4, #172]
	add	r7, r7, #8
	ldr	r3, [r6, #48]
	mov	r8, #32
	blx	r3
	add	r1, r4, #40960
	add	r2, r4, #45056
	mov	r3, #1
	str	r9, [r1, #2636]
	mov	ip, #16
	str	r3, [r2, #68]
	mov	r1, r5
	strb	r3, [r4]
	mov	r2, r8
	strb	r3, [r4, #2]
	mov	lr, #20
	strb	r5, [r4, #3]
	mov	r3, #8
	strb	r5, [r4, #1]
	mov	r0, r7
	strb	r5, [r4, #7]
	mvn	r10, #-2147483648
	ldr	r6, [r6, #48]
	str	r9, [r4, #2192]
	mov	r9, #64
	str	r5, [r4, #168]
	movw	r5, #1025
	str	r6, [fp, #-48]
	mov	r6, #256
	str	r8, [r4, #304]
	mov	r8, #4
	str	lr, [r4, #176]
	str	lr, [r4, #180]
	mov	lr, #6
	str	r6, [r4, #284]
	str	r3, [r4, #192]
	str	r3, [r4, #196]
	str	r3, [r4, #296]
	str	r10, [r4, #200]
	str	ip, [r4, #276]
	str	ip, [r4, #300]
	str	r9, [r4, #280]
	str	r5, [r4, #288]
	str	r8, [r4, #292]
	str	lr, [r4, #2180]
	str	lr, [r4, #2184]
	str	lr, [r4, #2188]
	ldr	r6, [fp, #-48]
	blx	r6
	str	r7, [r4, #2292]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2841:
	.align	2
.L2840:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC378
	UNWIND(.fnend)
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
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
	add	r10, r0, #49152
	ldr	r3, .L2853
	movw	r2, #6936
	ldr	r7, [r10, #2192]
	mov	r4, r0
	mov	r5, r1
	movt	r2, 1
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	str	r7, [r10, #2192]
	mov	r3, #0
	str	r5, [r4, #2308]
	str	r3, [r4, #2312]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L2849
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #148]
	mov	r2, #200
	str	r3, [r4, #152]
	mov	r3, #210
	str	r1, [r4, #156]
	str	r2, [r4, #144]
	str	r3, [r4, #160]
.L2844:
	ldr	r0, [r5, #668]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L2850
	ldr	r3, [r4, #148]
	movw	lr, #12820
	ldr	r0, [r4, #2308]
	add	r7, r4, #53248
	ldr	ip, [r4, #156]
	mov	r6, #1360
	mov	r2, r3
	str	r3, [fp, #-48]
	ldr	r3, [r4, #152]
	ldr	r0, [r0, #664]
	mul	r2, lr, r2
	movw	lr, #15788
	add	r0, r1, r0
	movw	r1, #2024
	mul	r3, lr, r3
	add	lr, r0, r2
	mul	ip, r1, ip
	str	r0, [r4, #2296]
	add	r9, lr, r3
	str	lr, [r4, #2300]
	str	r9, [r4, #2304]
	add	r1, r9, ip
	str	r1, [r7, #3248]
	ldr	r8, [r4, #144]
	mla	r1, r6, r8, r1
	mov	r8, #100
	str	r1, [r7, #3252]
	ldr	r6, [r4, #160]
	mla	r6, r6, r8, r8
	add	r1, r1, r6
	str	r1, [r7, #4056]
	ldr	r5, [r5, #688]
	cmp	r5, #0
	beq	.L2851
.L2847:
	add	r1, r4, #24576
	sub	r3, r3, #15744
	sub	r2, r2, #12800
	sub	r3, r3, #44
	add	r3, lr, r3
	sub	r2, r2, #20
	str	r3, [r1, #2604]
	add	r2, r0, r2
	ldr	r3, [fp, #-48]
	sub	ip, ip, #2016
	sub	ip, ip, #8
	str	r2, [r1, #2600]
	add	ip, r9, ip
	str	ip, [r1, #2608]
	str	r3, [r2, #8]
	mov	r0, r4
	ldr	r3, [r1, #2608]
	ldr	r2, [r4, #152]
	str	r2, [r3, #28]
	ldr	r3, [r1, #2604]
	ldr	r2, [r4, #156]
	str	r2, [r3, #60]
	bl	HEVC_InitScalingOrderTable
	add	r3, r4, #69632
	mov	r2, #1
	mov	r0, r4
	str	r2, [r3, #2836]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #244]
	beq	.L2852
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_InitDecPara
	mov	r0, #0
	str	r0, [r10, #2200]
	movw	r2, #9999
	ldr	r3, [r4, #156]
	str	r2, [r4, #252]
	str	r3, [r4, #272]
.L2846:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2851:
	ldr	r3, .L2853
	mov	r1, r5
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2296]
	mov	r2, #1
	movw	ip, #15788
	mov	r1, r5
	strb	r2, [r3]
	ldr	r3, .L2853
	ldr	r2, [r4, #152]
	ldr	r0, [r4, #2300]
	ldr	r3, [r3, #48]
	mul	r2, ip, r2
	blx	r3
	ldr	r2, [r4, #156]
	ldr	r3, .L2853
	movw	ip, #2024
	mov	r1, r5
	ldr	r0, [r4, #2304]
	mul	r2, ip, r2
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r4, #144]
	ldr	r3, .L2853
	mov	ip, #1360
	mov	r1, r5
	ldr	r0, [r7, #3248]
	mul	r2, ip, r2
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, .L2853
	mov	r1, r5
	ldr	r0, [r7, #3252]
	mla	r2, r2, r8, r8
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #160]
	ldr	r2, .L2853
	mov	r1, r5
	ldr	r0, [r7, #4056]
	ldr	ip, [r2, #48]
	mov	r2, r3, asl #5
	sub	r2, r2, r3, asl #2
	blx	ip
	ldr	r3, [r4, #148]
	ldr	ip, [r4, #156]
	movw	r1, #12820
	ldr	r0, [r4, #2296]
	mov	r2, r3
	str	r3, [fp, #-48]
	ldr	r3, [r4, #152]
	mul	r2, r1, r2
	movw	r1, #2024
	mul	ip, r1, ip
	movw	r1, #15788
	ldr	r9, [r4, #2304]
	mul	r3, r1, r3
	ldr	lr, [r4, #2300]
	b	.L2847
.L2849:
	ldr	r3, [r5, #748]
	str	r3, [r4, #148]
	ldr	r3, [r5, #752]
	str	r3, [r4, #152]
	ldr	r3, [r5, #756]
	str	r3, [r4, #156]
	ldr	r3, [r5, #744]
	add	r2, r3, #5
	str	r2, [r4, #160]
	str	r3, [r4, #144]
	b	.L2844
.L2852:
	ldr	r3, .L2853
	mov	r0, #0
	ldr	r2, .L2853+4
	ldr	r1, .L2853+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #19
	b	.L2846
.L2850:
	ldr	r3, .L2853
	ldr	r2, .L2853+4
	ldr	r1, .L2853+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #19
	b	.L2846
.L2854:
	.align	2
.L2853:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+532
	.word	.LC380
	.word	.LC379
	UNWIND(.fnend)
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	2
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #40960
	mov	r5, r0
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #2068]
	cmp	r3, #0
	beq	.L2856
	ldr	r1, [r3, #32]
	mov	r2, #1
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #2068]
	mov	r3, #0
	str	r3, [r2, #4]
	str	r3, [r4, #2068]
.L2856:
	mov	r0, #0
	strb	r0, [r4, #2017]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.align	2
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	mov	r5, r1
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	cmp	r5, #0
	bne	.L2863
	add	r0, r4, #50944
	add	r0, r0, #56
	bl	ResetVoQueue
	ldr	r0, [r4, #244]
	bl	FSP_EmptyInstance
.L2862:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2863:
	add	r1, r4, #50944
	ldr	r0, [r4, #244]
	add	r1, r1, #56
	bl	FSP_ClearNotInVoQueue
	b	.L2862
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	add	r6, r0, #24576
	add	r4, r0, #40960
	mov	r5, r0
	ldr	r3, [r6, #2584]
	ldr	r2, [r6, #2604]
	ldr	r0, [r4, #2652]
	str	r3, [fp, #-48]
	ldr	r3, [r6, #2588]
	cmp	r0, #0
	str	r3, [fp, #-52]
	ldr	r3, [r2, #100]
	str	r3, [fp, #-64]
	ldr	r3, [r2, #108]
	str	r3, [fp, #-68]
	ldr	r3, [r6, #2592]
	str	r3, [fp, #-56]
	ldr	r3, [r6, #2596]
	str	r3, [fp, #-60]
	blt	.L2898
	ldr	r3, [r5, #156]
	cmp	r0, r3
	bge	.L2898
	ldr	lr, [r5, #2304]
	movw	r7, #2024
	movw	ip, #15788
	ldr	r3, [r5, #2300]
	ldr	r8, [r5, #2296]
	movw	r1, #12820
	mla	r7, r7, r0, lr
	ldr	r0, [r6, #2600]
	ldr	r0, [r0, #8]
	ldr	r10, [r7, #32]
	mul	r10, ip, r10
	add	r9, r3, r10
	ldr	ip, [r9, #52]
	mla	r1, r1, ip, r8
	ldr	ip, [r1, #8]
	cmp	r0, ip
	bne	.L2866
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2921
.L2866:
	mov	r2, #0
	strb	r2, [r1, #2]
	ldr	r0, [r5, #148]
	movw	r8, #12820
	ldr	ip, .L2927
	mov	r2, r8
	ldr	lr, [r5, #2296]
	mul	r0, r8, r0
	ldr	ip, [ip, #52]
	str	r3, [fp, #-72]
	sub	r0, r0, #12800
	sub	r0, r0, #20
	add	r0, lr, r0
	blx	ip
	ldr	r0, [r5, #148]
	ldr	r2, [r6, #2604]
	ldr	r3, [fp, #-72]
	mul	r8, r8, r0
	ldr	r1, [r5, #2296]
	sub	r8, r8, #12800
	sub	r8, r8, #20
	add	r8, r1, r8
	str	r8, [r6, #2600]
.L2867:
	ldr	r0, [r2, #60]
	ldr	r1, [r9, #60]
	cmp	r0, r1
	bne	.L2868
	ldrb	r1, [r3, r10]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L2922
.L2868:
	mov	r2, #0
	strb	r2, [r3, r10]
	ldr	r0, [r5, #152]
	movw	r8, #15788
	ldr	r3, .L2927
	mov	r2, r8
	ldr	ip, [r5, #2300]
	mov	r1, r9
	mul	r0, r8, r0
	ldr	r3, [r3, #52]
	sub	r0, r0, #15744
	sub	r0, r0, #44
	add	r0, ip, r0
	blx	r3
	ldr	r3, [r5, #152]
	ldr	r2, [r5, #2300]
	mul	r8, r8, r3
	sub	r8, r8, #15744
	sub	r8, r8, #44
	add	r2, r2, r8
	str	r2, [r6, #2604]
	ldr	r3, [r2, #60]
	str	r3, [r6, #2584]
	ldr	r3, [r2, #72]
	str	r3, [r6, #2588]
	ldr	r3, [r2, #76]
	str	r3, [r6, #2592]
	ldr	r3, [r2, #148]
	str	r3, [r6, #2596]
	ldr	r1, [r9, #236]
	ldr	r3, [r2, #236]
	subs	r3, r1, r3
	movne	r3, #1
	str	r3, [fp, #-76]
	str	r3, [fp, #-72]
.L2869:
	ldr	r3, [r2, #108]
	ldr	r2, [r2, #100]
	ldr	r1, [r5, #2308]
	cmp	r3, r2
	movcc	r3, r2
	str	r3, [r1, #896]
	ldr	r2, [r6, #2608]
	ldr	r3, [r7, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L2923
.L2870:
	ldrb	r3, [r7, #13]	@ zero_extendqisi2
	mov	r8, #0
	strb	r8, [r7, #1]
	cmp	r3, r8
	beq	.L2872
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, r8
	beq	.L2873
	ldr	r10, [r7, #68]
	cmp	r10, r8
	ble	.L2878
	add	ip, r7, #174
	str	r4, [fp, #-84]
	str	r5, [fp, #-80]
	mov	r4, ip
	str	r6, [fp, #-88]
.L2877:
	ldr	r6, [r9, #240]
	add	r8, r8, #1
	mov	r1, r10
	mul	r0, r6, r8
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r5, r0
	sub	r0, r8, #1
	mul	r0, r0, r6
	bl	__aeabi_uidiv
	cmp	r8, r10
	rsb	r0, r0, r5
	strh	r0, [r4, #2]!	@ movhi
	bne	.L2877
	ldr	r5, [fp, #-80]
	ldr	r4, [fp, #-84]
	ldr	r6, [fp, #-88]
.L2878:
	ldr	r10, [r7, #72]
	cmp	r10, #0
	ble	.L2879
	add	ip, r7, #214
	str	r4, [fp, #-84]
	mov	r8, #0
	str	r5, [fp, #-80]
	mov	r4, ip
	str	r6, [fp, #-88]
.L2880:
	ldr	r6, [r9, #244]
	add	r8, r8, #1
	mov	r1, r10
	mul	r0, r6, r8
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r5, r0
	sub	r0, r8, #1
	mul	r0, r0, r6
	bl	__aeabi_uidiv
	cmp	r8, r10
	rsb	r0, r0, r5
	strh	r0, [r4, #2]!	@ movhi
	bne	.L2880
	ldr	r5, [fp, #-80]
	ldr	r4, [fp, #-84]
	ldr	r6, [fp, #-88]
	b	.L2879
.L2898:
	mov	r0, #0
.L2920:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2872:
	ldr	r3, [r9, #240]
	strh	r3, [r7, #176]	@ movhi
	ldr	r3, [r9, #244]
	strh	r3, [r7, #216]	@ movhi
.L2879:
	ldr	r0, [r5, #156]
	movw	r8, #2024
	ldr	r3, .L2927
	mov	r2, r8
	ldr	ip, [r5, #2304]
	mov	r1, r7
	mul	r0, r8, r0
	ldr	r3, [r3, #52]
	sub	r0, r0, #2016
	sub	r0, r0, #8
	add	r0, ip, r0
	blx	r3
	ldr	r2, [r5, #156]
	ldr	r3, [r5, #2304]
	ldr	r1, [fp, #-48]
	mul	r8, r8, r2
	ldr	r2, [fp, #-72]
	sub	r8, r8, #2016
	sub	r8, r8, #8
	add	r8, r3, r8
	str	r8, [r6, #2608]
	ldr	r3, [r9, #60]
	cmp	r1, r3
	orrne	r2, r2, #1
	cmp	r2, #0
	bne	.L2886
	ldr	r3, [r5, #168]
	cmp	r3, #0
	beq	.L2886
	ldr	r3, [r9, #72]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bne	.L2886
.L2896:
	ldr	r3, [r9, #76]
	ldr	r2, [fp, #-56]
	cmp	r2, r3
	bne	.L2886
	ldr	r3, [r5, #2308]
	ldr	r2, [r3, #892]
	cmp	r2, #1
	bne	.L2888
.L2887:
	ldr	r3, [r3, #900]
	cmp	r3, #1
	beq	.L2924
.L2891:
	add	r3, r5, #69632
	ldr	r3, [r3, #2836]
	cmp	r3, #1
	beq	.L2925
.L2892:
	mov	r1, #1
	mov	r0, r5
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L2920
	cmp	r0, #0
	bne	.L2893
	ldr	r3, [r5, #2308]
.L2890:
	mov	r2, #0
	str	r2, [r3, #900]
.L2888:
	mov	r0, r5
	bl	HEVC_AllocFrameStore
	subs	r7, r0, #0
	bne	.L2926
	ldr	ip, [r4, #2648]
	mov	r0, #1
	ldr	r3, [r4, #2624]
	mvn	r1, #0
	ldr	r2, [r4, #2068]
	movw	r10, #43040
	str	ip, [r4, #2020]
	add	ip, r5, #43008
	str	r3, [r4, #2024]
	movw	lr, #43056
	strb	r0, [r4, #2017]
	add	r0, ip, #24
	str	r3, [r2, #12]
	mvn	r2, #0
	str	r1, [r4, #2048]
	mvn	r3, #0
	ldr	r1, [r6, #2604]
	ldr	r8, [r1, #72]
	str	r8, [r4, #2032]
	ldr	r8, [r1, #76]
	str	r8, [r4, #2036]
	ldr	r8, [r1, #240]
	ldr	r1, [r1, #244]
	str	r7, [r4, #2044]
	mul	r1, r1, r8
	str	r1, [r4, #2040]
	ldr	r1, [r5, #2308]
	ldrd	r8, [r1, #48]
	strd	r8, [r5, r10]
	ldrd	r8, [r1, #64]
	strd	r8, [ip, #40]
	ldrd	r8, [r1, #80]
	strd	r8, [r5, lr]
	ldr	ip, [r1, #96]
	str	ip, [r4, #2140]
	ldr	ip, [r1, #100]
	str	ip, [r4, #2144]
	ldr	ip, [r1, #104]
	str	ip, [r4, #2148]
	ldr	ip, [r1, #120]
	str	ip, [r4, #2152]
	strd	r2, [r1, #48]
	ldr	r2, [r6, #2604]
	ldr	r3, [r2, #72]
	str	r3, [r4, #2236]
	ldr	r3, [r2, #76]
	str	r3, [r4, #2240]
	ldr	r3, [r2, #2660]
	ldr	r1, [r2, #64]
	mov	r3, r3, asl #5
	subs	r1, r1, #1
	uxtb	r3, r3
	movne	r1, #1
	orr	r3, r3, r1, asl #2
	str	r3, [r4, #2232]
	ldr	r1, [r2, #2644]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2232]
	str	r7, [r4, #2220]
	str	r2, [r3, #232]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2220]
	str	r2, [r3, #220]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2136]
	str	r2, [r3, #136]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2132]
	str	r2, [r3, #132]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2236]
	str	r2, [r3, #236]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2240]
	str	r2, [r3, #240]
	ldr	r3, [r4, #2068]
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L2895
	ldr	r3, [r4, #2220]
	mov	r1, r7
	ldr	r2, [r0, #4]
	adds	r3, r3, #0
	ldr	r0, [r5, #244]
	movne	r3, #1
	bl	FSP_SetStoreType
.L2895:
	ldr	r3, [r6, #2604]
	mov	r5, #0
	ldr	lr, [r4, #2068]
	mov	r0, r5
	ldr	r2, [r3, #84]
	str	r2, [r4, #2412]
	ldr	r7, [r3, #88]
	str	r7, [r4, #2416]
	ldr	r1, [r3, #92]
	str	r1, [r4, #2420]
	ldr	r6, [r3, #96]
	str	r6, [r4, #2424]
	ldr	ip, [r3, #72]
	rsb	r2, r2, ip
	rsb	r2, r7, r2
	str	r2, [r4, #2244]
	ldr	ip, [r3, #76]
	rsb	r1, r1, ip
	rsb	r1, r6, r1
	str	r1, [r4, #2248]
	ldr	r1, [r3, #64]
	str	r1, [r4, #2300]
	ldr	r1, [r3, #100]
	str	r1, [r4, #2304]
	ldr	r3, [r3, #108]
	str	r3, [r4, #2308]
	ldr	r3, [lr, #252]
	str	r3, [r4, #2252]
	ldr	r3, [lr, #256]
	str	r3, [r4, #2256]
	str	r2, [lr, #244]
	ldr	r2, [r4, #2248]
	ldr	r3, [r4, #2068]
	str	r2, [r3, #248]
	ldr	r2, [r4, #2252]
	ldr	r3, [r4, #2068]
	str	r2, [r3, #252]
	ldr	r2, [r4, #2256]
	ldr	r3, [r4, #2068]
	str	r2, [r3, #256]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2304]
	str	r2, [r3, #304]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2308]
	str	r2, [r3, #308]
	str	r5, [r4, #2028]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2923:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2870
	ldr	r3, [r5, #168]
	cmp	r3, #0
	beq	.L2870
	ldr	r3, [r9, #72]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bne	.L2870
	ldr	r3, [r9, #76]
	ldr	r2, [fp, #-56]
	cmp	r2, r3
	bne	.L2870
	ldr	r3, [r9, #148]
	ldr	r2, [fp, #-60]
	cmp	r2, r3
	bne	.L2870
	ldr	r3, [r9, #60]
	ldr	r2, [fp, #-72]
	ldr	r1, [fp, #-48]
	cmp	r1, r3
	orrne	r2, r2, #1
	cmp	r2, #0
	beq	.L2896
.L2886:
	ldr	r3, [fp, #-76]
	mov	r0, r5
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-52]
	str	r3, [sp]
	ldr	r3, [fp, #-60]
	bl	HEVC_GetReRangeFlag
	ldr	r3, [r5, #2308]
	cmp	r0, #0
	bne	.L2887
	ldr	r2, [r3, #892]
	cmp	r2, #1
	bne	.L2890
	b	.L2887
.L2873:
	ldr	lr, [r7, #68]
	ldr	r3, [r9, #240]
	cmp	lr, #1
	add	r0, r7, lr, lsl #1
	strh	r3, [r0, #174]	@ movhi
	ble	.L2884
	add	lr, lr, #44
	add	r1, r7, #90
	add	ip, r7, #174
	add	lr, r7, lr, lsl #1
.L2883:
	ldrh	r2, [r1, #2]!
	cmp	r1, lr
	strh	r2, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #174]
	rsb	r3, r2, r3
	strh	r3, [r0, #174]	@ movhi
	bne	.L2883
.L2884:
	ldr	lr, [r7, #72]
	ldr	r3, [r9, #244]
	cmp	lr, #1
	add	r0, r7, lr, lsl #1
	strh	r3, [r0, #214]	@ movhi
	ble	.L2879
	add	lr, lr, #64
	add	r1, r7, #130
	add	ip, r7, #214
	add	lr, r7, lr, lsl #1
.L2885:
	ldrh	r2, [r1, #2]!
	cmp	r1, lr
	strh	r2, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #214]
	rsb	r3, r2, r3
	strh	r3, [r0, #214]	@ movhi
	bne	.L2885
	b	.L2879
.L2922:
	ldr	r0, [r5, #168]
	cmp	r0, #0
	beq	.L2868
	ldr	r0, [r9, #72]
	ldr	ip, [fp, #-52]
	cmp	ip, r0
	bne	.L2868
	ldr	r0, [r9, #76]
	ldr	ip, [fp, #-56]
	cmp	ip, r0
	bne	.L2868
	ldr	r0, [r9, #148]
	ldr	ip, [fp, #-60]
	cmp	ip, r0
	bne	.L2868
	str	r1, [fp, #-72]
	str	r1, [fp, #-76]
	b	.L2869
.L2921:
	ldr	r0, [r5, #168]
	cmp	r0, #0
	bne	.L2867
	b	.L2866
.L2926:
	ldr	r3, .L2927
	mov	r0, #1
	ldr	r1, .L2927+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2924:
	ldr	r1, [r9, #108]
	mov	r0, #31
	ldr	lr, [fp, #-68]
	ldr	ip, .L2927
	ldr	r3, [r9, #100]
	ldr	r2, [fp, #-64]
	ldr	ip, [ip, #68]
	str	r1, [sp, #4]
	str	lr, [sp]
	ldr	r1, .L2927+8
	blx	ip
	b	.L2891
.L2925:
	mov	r0, r5
	bl	HEVC_GetBackPicFromVOQueue
	b	.L2892
.L2893:
	ldr	r3, .L2927
	mov	r2, r0
	ldr	r1, .L2927+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L2920
.L2928:
	.align	2
.L2927:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC383
	.word	.LC381
	.word	.LC382
	UNWIND(.fnend)
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	2
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
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
	mov	r4, r0
	mov	r5, r1
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L2937
	cmn	r6, #3
	moveq	r0, #0
	bne	.L2938
.L2932:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2937:
	mov	r2, #1
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L2939
	add	r3, r4, #50944
	ldr	r0, [r4, #244]
	add	r3, r3, #56
	str	r7, [sp]
	mov	r2, r4
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2940
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	strcc	r6, [r7, #84]
	bcs	.L2941
.L2935:
	ldr	r2, [r4, #268]
	mov	r0, #0
	ldr	r3, [r4, #260]
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2941:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.3
	b	.L2935
.L2938:
	ldr	ip, .L2942
	mov	r3, r6
	movw	r2, #8468
	ldr	r1, .L2942+4
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	ldr	r1, [r5, #268]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	b	.L2932
.L2940:
	ldr	r3, .L2942
	mov	r2, r0
	ldr	r1, .L2942+8
	mov	r0, r6
	ldr	r3, [r3, #68]
	blx	r3
	mov	r2, r6
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L2932
.L2939:
	ldr	r3, .L2942
	ldr	r2, .L2942+12
	ldr	r1, .L2942+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2932
.L2943:
	.align	2
.L2942:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC386
	.word	.LC385
	.word	.LANCHOR1+548
	.word	.LC384
	UNWIND(.fnend)
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	2
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
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
	add	r6, r0, #40960
	mov	ip, #2
	mov	r5, #0
	mov	r3, #1
	ldr	r4, [r6, #2068]
	add	r1, r6, #2064
	mov	r7, r0
	mov	r2, #504
	add	r0, r4, #72
	add	r1, r1, #8
	str	ip, [r4, #4]
	strb	r3, [r4, #2]
	strb	r5, [r4, #1]
	ldr	r3, [r6, #2028]
	str	r3, [r4, #16]
	ldr	r3, [r6, #2056]
	str	r3, [r4, #20]
	bl	memcpy
	str	r5, [r4, #48]
	ldr	r3, [r6, #2056]
	mov	r2, r5
	ldr	r1, [r4, #32]
	str	r3, [r4, #40]
	ldr	r0, [r7, #244]
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	HEVC_OutputFrmToVO
	ldr	r3, .L2945
	str	r5, [r4, #4]
	mov	r1, r5
	mov	r2, #560
	ldr	r3, [r3, #48]
	mov	r6, r0
	add	r0, r7, #42752
	add	r0, r0, #224
	blx	r3
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2946:
	.align	2
.L2945:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	2
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	HEVC_DirectOutput
	add	r2, r4, #40960
	ldr	r1, [r4, #180]
	ldr	r3, [r2, #2052]
	cmp	r3, r1
	addne	r3, r3, #524
	movne	ip, #0
	addne	r4, r4, r3, lsl #2
	strne	ip, [r4, #4]
	strne	r1, [r2, #2052]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.align	2
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	ldr	r9, [r0, #2492]
	mov	r4, r0
	cmp	r9, #0
	beq	.L2950
	add	r6, r0, #2496
	mov	r7, #0
	add	r6, r6, #12
	mov	r3, r7
	mov	r1, r6
.L2952:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L2951
	ldr	r0, [r2, #12]
	ldr	r2, [r4, #212]
	cmp	r0, r2
	addgt	r7, r7, #1
.L2951:
	cmp	r3, r9
	bne	.L2952
	ldr	r8, .L2965
	mov	r5, #0
	mov	r9, r5
.L2957:
	ldr	r3, [r6, #4]!
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2953
	ldr	r1, [r3, #12]
	ldr	r2, [r4, #212]
	cmp	r1, r2
	ble	.L2954
	add	lr, r4, #40960
	add	ip, r4, #24576
	ldr	r10, [lr, #2644]
	ldr	r0, [ip, #2604]
	add	r0, r0, r10, lsl #2
	ldr	r0, [r0, #412]
	cmp	r0, r7
	bcs	.L2954
	ldr	r0, [lr, #2624]
	cmp	r1, r0
	blt	.L2955
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2955
.L2954:
	cmp	r2, #0
	bne	.L2956
	ldr	r1, [r3, #12]
	cmp	r1, #0
	blt	.L2964
.L2956:
	ldr	r3, [r4, #2492]
	add	r5, r5, #1
	cmp	r3, r5
	bhi	.L2957
.L2950:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2955:
	mov	r2, #1
	mov	r0, r4
	strb	r2, [r3, #2]
	sub	r7, r7, #1
	ldr	r1, [r6]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r6]
	ldr	r3, [r3, #12]
	str	r3, [r4, #212]
	mov	r9, r0
	b	.L2956
.L2953:
	ldr	r2, [r4, #212]
	b	.L2954
.L2964:
	ldr	r1, [r3, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	ldr	r3, [r4, #212]
	mov	r0, #31
	ldr	ip, [r8, #68]
	ldr	lr, [r2, #12]
	ldr	r1, .L2965+4
	ldr	r2, .L2965+8
	str	lr, [sp]
	blx	ip
	b	.L2956
.L2966:
	.align	2
.L2965:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC387
	.word	.LANCHOR1+568
	UNWIND(.fnend)
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	2
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
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
	add	r4, r0, r1, lsl #2
	mov	r2, #1
	mov	r6, r1
	mov	r5, r0
	ldr	r3, [r4, #2512]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2512]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #2512]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L2968
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L2968:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.align	2
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	sub	r1, fp, #24
	mov	r4, r0
	bl	HEVC_GetUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L2973
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L2974
.L2971:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L2973:
	ldr	r3, .L2975
	mov	r0, #1
	ldr	r2, .L2975+4
	ldr	r1, .L2975+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2971
.L2974:
	ldr	r3, .L2975
	mov	r0, #1
	ldr	r2, .L2975+4
	ldr	r1, .L2975+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2971
.L2976:
	.align	2
.L2975:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+592
	.word	.LC388
	.word	.LC389
	UNWIND(.fnend)
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	2
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
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
	subs	r4, r0, #0
	beq	.L2986
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	addne	r5, r4, #2496
	movne	r6, #0
	addne	r5, r5, #12
	movne	r8, #1
	bne	.L2984
	b	.L2985
.L2992:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L2991
.L2982:
	ldr	r3, [r4, #2492]
	cmp	r3, r6
	bls	.L2985
.L2984:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #244]
	add	r6, r6, #1
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2992
	ldr	r1, [r3, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L2982
	ldr	r3, [r5]
	ldr	r0, [r4, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2492]
	cmp	r3, r6
	bhi	.L2984
.L2985:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	bl	Hevc_InitDecBuffers
.L2978:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2991:
	ldr	r3, .L2993
	mov	r0, r7
	ldr	r2, .L2993+4
	ldr	r1, .L2993+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2986:
	mvn	r9, #0
	b	.L2978
.L2994:
	.align	2
.L2993:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+624
	.word	.LC390
	UNWIND(.fnend)
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	2
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r4, r0, #69632
	mov	r3, #0
	mov	r5, r0
	str	r3, [r4, #2816]
	ldr	r6, [r0, #2316]
	cmp	r6, r3
	beq	.L3017
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #40]
	ldr	r3, [r0, #2308]
	ldr	r2, [r3, #852]
	cmp	r2, #1
	beq	.L3018
.L3001:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3002
	ldr	r3, [r5, #2316]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L3003
	ldr	r0, [r3, #40]
	cmp	r0, #1
	beq	.L3002
.L3003:
	ldr	r0, [r1, #12]
	cmp	r0, #0
	ble	.L3004
	ldr	ip, [r1, #4]
	cmp	ip, #0
	beq	.L3004
	ldr	r0, [r1, #8]
	cmp	r0, #0
	bne	.L3019
.L3004:
	mov	r2, #1
	str	r2, [r3, #40]
	ldr	r1, [r1, #16]
	ldr	r0, [r5, #244]
	bl	SM_ReleaseStreamSeg
.L3000:
	ldr	r3, [r5, #2316]
	ldr	r0, [r3, #40]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L2999:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3018:
	ldr	r3, [r3, #892]
	cmp	r3, #0
	bne	.L3000
	b	.L3001
.L3019:
	mov	r0, r2, asl #5
	mov	lr, #0
	sub	r2, r0, r2, asl #2
	mov	r0, r5
	add	r3, r3, r2
	str	ip, [r3, #44]
	ldr	r3, [r5, #2316]
	ldr	r6, [r1, #12]
	ldr	ip, [r3, #8]
	mov	r2, ip, asl #5
	sub	r2, r2, ip, asl #2
	add	r3, r3, r2
	str	r6, [r3, #48]
	ldr	r3, [r5, #2316]
	ldr	r6, [r1, #8]
	ldr	ip, [r3, #8]
	mov	r2, ip, asl #5
	sub	r2, r2, ip, asl #2
	add	r3, r3, r2
	str	r6, [r3, #52]
	ldr	r3, [r5, #2316]
	ldr	ip, [r1, #16]
	ldr	r1, [r3, #8]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #68]
	ldr	r3, [r5, #2316]
	ldr	r1, [r3, #8]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	lr, [r3, #60]
	ldr	r2, [r5, #2316]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #2816]
	b	.L3000
.L3017:
	ldr	r3, [r1, #12]
	cmp	r3, #0
	ble	.L2997
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L2997
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L2997
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r4, r0
	beq	.L3020
	add	r3, r5, #53248
	mov	r0, #100
	mov	r2, #1
	ldr	r3, [r3, #3252]
	mla	r4, r0, r4, r3
	str	r4, [r5, #2316]
	ldr	r3, [r1, #4]
	str	r3, [r4, #44]
	ldr	r3, [r5, #2316]
	ldr	r0, [r1, #12]
	str	r0, [r3, #48]
	ldr	r3, [r5, #2316]
	ldr	r0, [r1, #16]
	str	r0, [r3, #68]
	ldr	r3, [r5, #2316]
	ldr	r0, [r1, #8]
	str	r0, [r3, #52]
	ldr	r3, [r5, #2316]
	str	r6, [r3, #60]
	ldr	r3, [r5, #2316]
	str	r2, [r3, #8]
	ldr	r3, [r5, #2316]
	strb	r6, [r3, #1]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	r3, [r5, #2316]
	str	r2, [r3, #40]
	b	.L3000
.L3002:
	ldr	r3, .L3021
	mov	r0, #1
	ldr	r1, .L3021+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2999
.L2997:
	ldr	r3, .L3021
	mov	r0, #1
	ldr	r1, .L3021+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2999
.L3020:
	ldr	r3, .L3021
	mov	r0, r6
	ldr	r1, .L3021+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_ClearAll
	mov	r0, r4
	b	.L2999
.L3022:
	.align	2
.L3021:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC393
	.word	.LC392
	.word	.LC391
	UNWIND(.fnend)
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	2
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #2492]
	mov	r4, r0
	cmp	r3, #0
	beq	.L3025
	add	r6, r0, #2496
	mov	r5, #0
	add	r6, r6, #12
	mov	r7, r5
	b	.L3027
.L3026:
	ldr	r3, [r4, #2492]
	cmp	r3, r5
	bls	.L3025
.L3027:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3026
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetRef
	ldr	r3, [r4, #2492]
	cmp	r3, r5
	bhi	.L3027
.L3025:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L3029
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3025
	b	.L3029
.L3031:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L3030
.L3029:
	ldr	r3, [r4, #2492]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L3031
	mov	r0, r3
.L3030:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.align	2
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	HEVC_FlushDPB
	subs	r3, r0, #0
	beq	.L3040
	ldr	ip, .L3044
	mov	r0, #0
	ldr	r2, .L3044+4
	ldr	r1, .L3044+8
	ldr	ip, [ip, #68]
	blx	ip
.L3040:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3045:
	.align	2
.L3044:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+652
	.word	.LC394
	UNWIND(.fnend)
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	2
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r6, .L3056
	mov	r4, r0
	b	.L3047
.L3049:
	str	lr, [sp]
	ldr	ip, [r6, #68]
	blx	ip
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L3055
.L3047:
	ldr	ip, [r4, #2492]
	mov	r0, #13
	ldr	lr, [r4, #2488]
	ldr	r2, .L3056+4
	cmp	ip, lr
	ldr	r1, .L3056+8
	ldr	r5, .L3056
	mov	r3, ip
	bcs	.L3049
.L3048:
	ldr	r5, .L3056
	b	.L3051
.L3052:
	str	lr, [sp]
	ldr	ip, [r5, #68]
	blx	ip
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L3050
	ldr	ip, [r4, #2492]
	ldr	lr, [r4, #2488]
.L3051:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L3056+4
	mov	r0, #1
	ldr	r1, .L3056+12
	ldr	r6, .L3056
	bcs	.L3052
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3055:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r2, .L3056+4
	ldr	r1, .L3056+16
	blx	r3
	ldr	ip, [r4, #2492]
	ldr	lr, [r4, #2488]
	b	.L3048
.L3050:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r2, .L3056+4
	ldr	r1, .L3056+20
	blx	r3
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVC_ClearDPB
.L3057:
	.align	2
.L3056:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+668
	.word	.LC395
	.word	.LC397
	.word	.LC396
	.word	.LC389
	UNWIND(.fnend)
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	2
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
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
	cmp	r1, #16
	mov	r7, r1
	mov	r6, r0
	mov	r4, r2
	bhi	.L3062
	ldr	r3, [r2, #52]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r2, r1
	str	r3, [r5, #2512]
	str	r1, [r3, #4]
	ldr	r3, [r5, #2512]
	ldr	r0, [r0, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r0, [r5, #2512]
	mov	r2, #504
	adds	r3, r3, #0
	add	r1, r4, #56
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r5, #2512]
	ldr	r0, [r4, #36]
	str	r0, [r3, #24]
	ldr	r0, [r5, #2512]
	add	r0, r0, #72
	bl	memcpy
	ldr	ip, [r5, #2512]
	ldr	lr, [r4, #40]
	add	r1, r7, #1
	ldr	r3, .L3064
	mov	r2, #4
	add	r0, r6, #2512
	str	lr, [ip, #40]
	str	lr, [ip, #20]
	ldr	ip, [r5, #2512]
	ldr	lr, [r4, #52]
	str	lr, [ip, #68]
	ldr	ip, [r5, #2512]
	ldr	lr, [r4, #12]
	str	lr, [ip, #44]
	str	lr, [ip, #16]
	ldr	ip, [r5, #2512]
	ldr	lr, [r4, #8]
	str	lr, [ip, #12]
	ldr	ip, [r5, #2512]
	ldr	lr, [r4, #8]
	str	lr, [ip, #36]
	bl	qsort
	ldr	r3, [r6, #2492]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #2492]
	ldr	r1, [r4, #52]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L3063
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3062:
	ldr	ip, .L3064+4
	mov	r3, r1
	ldr	r2, .L3064+8
	mov	r0, #0
	ldr	r1, .L3064+12
	ldr	ip, [ip, #68]
	blx	ip
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3063:
	ldr	ip, .L3064+4
	mov	r0, #0
	ldr	r2, .L3064+8
	ldr	r1, .L3064+16
	ldr	ip, [ip, #68]
	blx	ip
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3065:
	.align	2
.L3064:
	.word	compare_pic_by_poc_asc
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+692
	.word	.LC398
	.word	.LC399
	UNWIND(.fnend)
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	2
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r4, r0, #40960
	mov	r5, r0
	ldrb	r3, [r4, #2016]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3079
	ldr	r3, [r4, #2068]
	mov	r2, #2
	str	r2, [r3, #4]
.L3068:
	ldr	r3, [r4, #2068]
	mov	r2, #1
	mov	r0, r5
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2068]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r4, r0
	beq	.L3080
	cmn	r0, #3
	beq	.L3072
	mov	r0, r5
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3081
.L3072:
	mov	r0, #0
.L3069:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3079:
	bl	HEVC_SimpleSlideDPB
	add	r2, r5, #42752
	add	r2, r2, #224
	ldr	r1, [r5, #2492]
	mov	r0, r5
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L3068
	ldr	r1, .L3082
	movw	r3, #7642
	str	r0, [sp]
	mov	r0, #0
	ldr	r2, .L3082+4
	ldr	ip, [r1, #68]
	ldr	r1, .L3082+8
	blx	ip
	mvn	r0, #6
	b	.L3069
.L3081:
	ldr	r3, .L3082
	mov	r0, #0
	ldr	r2, .L3082+4
	ldr	r1, .L3082+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3069
.L3080:
	ldr	r3, .L3082
	mov	r0, #0
	ldr	r2, .L3082+4
	ldr	r1, .L3082+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L3069
.L3083:
	.align	2
.L3082:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+712
	.word	.LC400
	.word	.LC87
	.word	.LC401
	UNWIND(.fnend)
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	2
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
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
	ldr	r1, [r0, #2492]
	mov	r4, r0
	ldr	r3, [r0, #2488]
	cmp	r1, r3
	bcs	.L3096
.L3085:
	add	r2, r4, #42752
	mov	r0, r4
	add	r2, r2, #224
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3097
	add	r3, r4, #40960
	mov	r0, r4
	ldr	r1, [r3, #2068]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3098
	cmn	r0, #3
	beq	.L3091
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3099
.L3091:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3096:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3095
	ldr	r3, .L3100
	mov	r0, #0
	ldr	r2, .L3100+4
	ldr	r1, .L3100+8
	ldr	r3, [r3, #68]
	blx	r3
.L3095:
	ldr	r1, [r4, #2492]
	b	.L3085
.L3097:
	ldr	r3, .L3100
	mov	r0, #0
	ldr	r2, .L3100+4
	ldr	r1, .L3100+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3099:
	ldr	r3, .L3100
	mov	r0, r6
	ldr	r2, .L3100+4
	ldr	r1, .L3100+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3098:
	ldr	r3, .L3100
	mov	r0, r6
	ldr	r2, .L3100+4
	ldr	r1, .L3100+20
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3101:
	.align	2
.L3100:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+736
	.word	.LC402
	.word	.LC403
	.word	.LC87
	.word	.LC401
	UNWIND(.fnend)
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	2
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #49152
	mov	r4, r0
	ldr	r3, [r3, #2200]
	cmp	r3, #1
	beq	.L3103
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L3120
.L3103:
	ldr	r1, [r4, #2492]
	ldr	r3, [r4, #2488]
	cmp	r1, r3
	bcs	.L3121
.L3105:
	add	r2, r4, #42752
	mov	r0, r4
	add	r2, r2, #224
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L3122
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	bne	.L3108
.L3109:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3108:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3109
	ldr	r3, .L3123
	mov	r0, #1
	ldr	r2, .L3123+4
	ldr	r1, .L3123+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3121:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3119
	ldr	r3, .L3123
	mov	r0, #0
	ldr	r1, .L3123+12
	ldr	r3, [r3, #68]
	blx	r3
.L3119:
	ldr	r1, [r4, #2492]
	b	.L3105
.L3122:
	ldr	r3, .L3123
	mov	r2, r0
	ldr	r1, .L3123+16
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3120:
	ldr	r3, .L3123
	mov	r0, #0
	ldr	r2, .L3123+4
	ldr	r1, .L3123+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3124:
	.align	2
.L3123:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+760
	.word	.LC407
	.word	.LC405
	.word	.LC406
	.word	.LC404
	UNWIND(.fnend)
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	2
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
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
	add	r6, r0, #40960
	mov	r4, r0
	bl	HEVC_RemoveDummyFrame
	ldrb	r5, [r6, #2017]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3155
	ldr	r3, [r4, #2308]
	ldr	r2, [r6, #2056]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L3156
	ldr	r3, [r4, #2312]
	ldr	r2, [r6, #2068]
	add	r3, r3, #4096
	ldr	r3, [r3, #1036]
	str	r3, [r2, #576]
	ldr	r3, [r4, #2312]
	ldr	r2, [r6, #2068]
	add	r3, r3, #4096
	ldr	r3, [r3, #1040]
	str	r3, [r2, #580]
	ldr	r3, [r4, #248]
	cmp	r3, #2
	beq	.L3157
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	beq	.L3158
	cmp	r3, #1
	beq	.L3159
	cmp	r3, #0
	beq	.L3139
	ldr	r7, .L3162
.L3140:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r3, [r7, #68]
	ldr	r2, .L3162+4
	mov	r0, #1
	ldr	r1, .L3162+8
	blx	r3
.L3138:
	mov	r3, #0
	mov	r0, r5
	strb	r3, [r6, #2017]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3155:
	ldr	r3, .L3162
	mov	r0, #1
	ldr	r2, .L3162+4
	ldr	r1, .L3162+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3158:
	mov	r0, r4
	ldr	r7, .L3162
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L3160
.L3134:
	ldr	ip, [r7, #68]
	mov	r3, #7936
	mov	r2, r5
	ldr	r1, .L3162+16
	mov	r0, #14
	blx	ip
.L3132:
	cmn	r5, #1
	bne	.L3138
	b	.L3140
.L3156:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2308]
	ldr	r1, .L3162
	mov	r0, #1
	ldr	r2, [r6, #2056]
	ldr	r3, [r3, #4]
	ldr	ip, [r1, #68]
	ldr	r1, .L3162+20
	blx	ip
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3159:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	beq	.L3136
	ldr	r7, .L3162
	mov	r0, #0
	ldr	r2, .L3162+4
	ldr	r1, .L3162+24
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #0
	bne	.L3132
.L3139:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	bne	.L3137
.L3141:
	mov	r5, #0
	b	.L3138
.L3157:
	mov	r0, r4
	ldr	r7, .L3162
	bl	HEVC_DirectOutput
	ldr	r3, [r6, #2052]
	ldr	r2, [r4, #180]
	cmp	r3, r2
	addne	r3, r3, #524
	movne	r1, #0
	addne	r3, r4, r3, lsl #2
	strne	r1, [r3, #4]
	mov	r5, r0
	strne	r2, [r6, #2052]
	cmp	r0, #0
	bne	.L3161
.L3131:
	ldr	ip, [r7, #68]
	movw	r3, #7921
	mov	r2, r5
	ldr	r1, .L3162+16
	mov	r0, #14
	blx	ip
	b	.L3132
.L3136:
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #0
	bne	.L3141
	b	.L3139
.L3137:
	ldr	r7, .L3162
	mov	r0, #0
	ldr	r2, .L3162+4
	ldr	r1, .L3162+28
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3132
.L3161:
	ldr	r2, .L3162+4
	mov	r0, #0
	ldr	r1, .L3162+32
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3131
.L3160:
	ldr	r2, .L3162+4
	mov	r0, #0
	ldr	r1, .L3162+36
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3134
.L3163:
	.align	2
.L3162:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+784
	.word	.LC415
	.word	.LC408
	.word	.LC411
	.word	.LC409
	.word	.LC413
	.word	.LC414
	.word	.LC410
	.word	.LC412
	UNWIND(.fnend)
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	2
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 560
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #560)
	sub	sp, sp, #560
	add	r4, r0, #57088
	add	r4, r4, #224
	mov	r5, r0
	mov	r6, r1
	mov	r7, #0
.L3169:
	ldr	r2, [r4, #4]
	cmp	r2, #0
	bne	.L3165
	cmp	r4, #0
	beq	.L3166
	ldr	r3, [r5, #2492]
	cmp	r3, #0
	beq	.L3166
	ldr	r1, [r5, #2512]
	cmp	r4, r1
	beq	.L3165
	add	ip, r5, #2512
	b	.L3167
.L3168:
	ldr	lr, [ip, #4]!
	cmp	lr, r4
	beq	.L3165
.L3167:
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L3168
.L3166:
	mov	r8, #584
	mov	r2, #504
	mla	r8, r8, r7, r5
	sub	r0, fp, #540
	mov	r9, #1
	mov	r3, #101
	str	r6, [fp, #-588]
	add	r1, r8, #57344
	str	r3, [fp, #-556]
	add	r1, r1, #40
	strb	r9, [fp, #-595]
	strb	r9, [fp, #-596]
	bl	memcpy
	add	r3, r8, #57088
	cmp	r7, #19
	movw	r1, #57320
	movw	r2, #57312
	mov	r7, #0
	strb	r9, [r3, #226]
	str	r4, [fp, #-544]
	str	r7, [r8, r1]
	str	r7, [fp, #-340]
	strb	r9, [r8, r2]
	bgt	.L3170
	ldr	r0, [r5, #2492]
	cmp	r0, #0
	beq	.L3172
	add	r1, r5, #2496
	mov	ip, r7
	add	r1, r1, #12
	mvn	r2, #-2147483648
	mov	r8, r1
.L3175:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #12]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L3174
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r7, #1
.L3174:
	cmp	ip, r0
	bne	.L3175
	cmp	r7, #0
	beq	.L3172
	mov	r4, #0
	b	.L3176
.L3177:
	add	r4, r4, #1
	cmp	r4, r0
	beq	.L3207
.L3176:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #12]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L3177
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3177
	ldr	r1, [ip, #32]
	add	r4, r4, #628
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	ldr	r9, .L3210
	ldr	r2, [r5, r4, asl #2]
	mov	r3, r6
	ldr	r1, .L3210+4
	ldr	ip, [r9, #68]
	ldr	r2, [r2, #12]
	mov	r7, r0
	mov	r0, #1
	blx	ip
	cmp	r7, #0
	beq	.L3178
	ldr	r0, [r7, #520]
	cmp	r0, #0
	beq	.L3208
	mov	r1, #0
	ldr	r0, [r5, #244]
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	mvn	r2, r8
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3181
	ldr	r1, [fp, #-544]
	sub	r2, fp, #596
	mov	r0, r5
	str	r8, [r1, #32]
	ldr	r1, [r7, #520]
	str	r1, [r3, #520]
	ldr	r1, [r7, #524]
	str	r1, [r3, #524]
	ldr	r1, [r7, #528]
	str	r1, [r3, #528]
	ldrsb	r3, [r7, #4]
	ldr	r1, [r5, #2492]
	str	r3, [fp, #-560]
	bl	HEVC_InsertFrmInDPB
	subs	r4, r0, #0
	bne	.L3209
	ldr	r0, [r5, #244]
	mov	r1, r8
	mov	r2, r4
	bl	FSP_SetDisplay
	ldr	r3, [r5, #200]
	mov	r0, r4
	cmn	r3, #-2147483647
	streq	r6, [r5, #200]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3165:
	add	r7, r7, #1
	add	r4, r4, #584
	cmp	r7, #20
	bne	.L3169
.L3170:
	ldr	r3, .L3210
	mov	r0, #0
	ldr	r1, .L3210+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L3202:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3207:
	ldr	r9, .L3210
.L3178:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L3210+12
	blx	r3
	mvn	r0, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3181:
	ldr	r3, [fp, #-544]
	mov	r0, r2
	ldr	r1, .L3210+16
	strb	r2, [r3]
	ldr	r3, [r9, #68]
	blx	r3
	mvn	r0, #3
	b	.L3202
.L3209:
	ldr	r3, [fp, #-544]
	mov	r1, r8
	mov	r4, #0
	mov	r2, #1
	strb	r4, [r3]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
	mov	r0, r4
	ldr	r3, [r9, #68]
	ldr	r1, .L3210+20
	blx	r3
	mvn	r0, #0
	b	.L3202
.L3172:
	ldr	r2, .L3210
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4]
	ldr	r1, .L3210+24
	ldr	r3, [r2, #68]
	blx	r3
	mvn	r0, #0
	b	.L3202
.L3208:
	ldr	r3, [r9, #68]
	ldr	r1, .L3210+28
	blx	r3
	mov	r0, r5
	bl	HEVC_ClearDPB
	mvn	r0, #3
	b	.L3202
.L3211:
	.align	2
.L3210:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC419
	.word	.LC416
	.word	.LC417
	.word	.LC421
	.word	.LC422
	.word	.LC418
	.word	.LC420
	UNWIND(.fnend)
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	2
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	bl	HEVC_RemoveDummyFrame
	mov	r0, r4
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	ldr	r6, .L3222
	add	r5, r4, #40960
	bl	HEVC_RemoveUnUsedFrameStore
	b	.L3213
.L3216:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.2
	ldr	r1, .L3222+4
	cmp	r0, #0
	mov	r0, #1
	bne	.L3218
	ldr	r3, [r6, #68]
	ldr	r2, [fp, #-32]
	blx	r3
	ldr	r3, [r4, #2308]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L3214
	ldr	r1, [fp, #-32]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L3221
.L3213:
	ldr	r3, [r5, #2648]
	sub	r1, fp, #32
	mov	r0, r4
	ldr	r7, .L3222
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L3216
.L3218:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3214:
	ldr	lr, [fp, #-32]
	mov	r0, #1
	ldr	r3, [r5, #2624]
	ldr	ip, [r7, #68]
	ldr	r1, .L3222+8
	str	lr, [sp]
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3221:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3223:
	.align	2
.L3222:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC423
	.word	.LC424
	UNWIND(.fnend)
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	2
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, [r0, #2316]
	add	r5, r0, #40960
	mov	r4, r0
	ldr	r6, [r3, #16]
	sub	r2, r6, #16
	str	r6, [r5, #2648]
	cmp	r2, #4
	ldr	r3, [r3, #32]
	str	r3, [r5, #2644]
	bls	.L3225
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	bne	.L3225
	cmp	r6, #21
	beq	.L3273
.L3229:
	ldrb	r6, [r4, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3274
.L3230:
	ldr	r2, [r4, #208]
	ldr	r3, [r4, #144]
	cmp	r2, r3
	bcs	.L3275
	add	r6, r4, #45056
	ldr	r3, [r6, #68]
	cmp	r3, #1
	beq	.L3276
.L3233:
	ldrb	r3, [r5, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3277
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r6, #68]
	cmp	r3, #2
	beq	.L3240
	ldrb	r3, [r5, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3278
.L3241:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L3279
.L3244:
	ldr	r2, [r5, #2652]
	add	r3, r4, #4096
	mov	r1, #1
	mov	r0, #0
	str	r2, [r4, #272]
	ldr	r2, [r5, #2624]
	str	r1, [r4, #168]
	str	r2, [r4, #252]
	ldr	r2, [r3, #404]
	str	r2, [r5, #2060]
	ldr	r3, [r3, #408]
	str	r3, [r5, #2064]
.L3228:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3225:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L3272
	ldr	r6, [r5, #2648]
	cmp	r6, #21
	bne	.L3229
.L3273:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #252]
	cmp	r2, r3
	bcs	.L3229
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	beq	.L3229
.L3272:
	ldr	r3, .L3283
	mov	r0, #1
	ldr	r2, .L3283+4
	ldr	r1, .L3283+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3278:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L3280
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L3241
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r3, .L3283
	ldr	r1, .L3283+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3274:
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	beq	.L3230
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3230
	ldr	r3, .L3283
	mov	r0, r6
	ldr	r2, .L3283+4
	ldr	r1, .L3283+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3276:
	ldr	r2, [r4, #2308]
	ldr	r3, [r4, #220]
	add	r3, r3, #1
	str	r3, [r4, #220]
	ldr	r3, [r2, #8]
	cmp	r3, #2
	beq	.L3235
	ldr	r3, [r2, #12]
	mov	r0, r4
	cmp	r3, #2
	beq	.L3281
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	bne	.L3246
.L3235:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L3228
	cmp	r0, #0
	bne	.L3282
	mov	r0, r4
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L3233
	ldr	r3, .L3283
	mov	r0, #1
	ldr	r1, .L3283+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3240:
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	beq	.L3244
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
	b	.L3244
.L3281:
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	b	.L3235
.L3246:
	mvn	r0, #0
	b	.L3228
.L3277:
	ldr	r3, .L3283
	mov	r0, #1
	ldr	r1, .L3283+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3275:
	ldr	r5, .L3283
	mov	r0, #0
	ldr	r1, .L3283+28
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r4, #208]
	ldr	r2, [r4, #144]
	cmp	r3, r2
	bcc	.L3232
	ldr	r1, .L3283+32
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L3232
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #244]
	blx	ip
.L3232:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L3283+36
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3228
.L3280:
	ldr	r3, .L3283
	mov	r2, r0
	ldr	r1, .L3283+40
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3279:
	ldr	r3, .L3283
	mov	r0, #1
	ldr	r1, .L3283+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3282:
	ldr	r3, .L3283
	mov	r0, #1
	ldr	r1, .L3283+48
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3228
.L3284:
	.align	2
.L3283:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+804
	.word	.LC425
	.word	.LC433
	.word	.LC426
	.word	.LC430
	.word	.LC431
	.word	.LC427
	.word	g_event_report
	.word	.LC428
	.word	.LC432
	.word	.LC434
	.word	.LC429
	UNWIND(.fnend)
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	2
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [fp, #4]
	add	ip, r0, #40960
	mov	r4, r0
	mov	r5, r3
	cmp	r2, #0
	str	r1, [ip, #2056]
	ldr	r2, [fp, #8]
	beq	.L3286
	mov	ip, r2, asl #6
	ldr	r3, .L3296
	sub	r2, ip, r2, asl #3
	add	r2, r2, r3
	ldr	r2, [r2, #4]
	cmp	r2, #3
	beq	.L3294
	cmp	r2, #1
	beq	.L3286
.L3289:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r2, r0, #0
	bne	.L3295
	mov	r3, #1
	mov	r0, r2
	str	r3, [r4, #168]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3295:
	ldr	r3, .L3296+4
	mov	r0, #0
	ldr	r1, .L3296+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3286:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	b	.L3289
.L3294:
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3297:
	.align	2
.L3296:
	.word	g_VdmDrvParam+48
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC435
	UNWIND(.fnend)
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	2
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r3, [r0, #176]
	mov	r4, r0
	cmp	r3, #0
	beq	.L3301
	add	r3, r0, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3301
	add	r2, r0, #57088
	add	r0, r0, #68608
	add	r2, r2, #224
	add	r0, r0, #384
.L3309:
	ldr	r3, [r2, #4]
	cmp	r3, #0
	bne	.L3302
	cmp	r2, #0
	beq	.L3303
	ldr	lr, [r4, #2492]
	cmp	lr, #0
	beq	.L3303
	ldr	r1, [r4, #2512]
	cmp	r1, r2
	beq	.L3302
	add	r1, r4, #2512
	b	.L3304
.L3305:
	ldr	ip, [r1, #4]!
	cmp	ip, r2
	beq	.L3302
.L3304:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L3305
.L3303:
	ldr	r0, [r4, #244]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L3301
	cmn	r0, #1
	beq	.L3328
	add	r0, r4, #50944
	add	r0, r0, #56
	bl	IsVoQueueEmpty
	cmp	r0, #1
	bne	.L3327
	ldr	r5, .L3330
	mov	r0, #0
	ldr	r1, .L3330+4
	ldr	r3, [r5, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3308
	ldr	r3, [r5, #68]
	mov	r0, #0
	ldr	r1, .L3330+8
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearDPB
	mov	r0, #0
	b	.L3325
.L3301:
	mov	r0, #1
.L3325:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3302:
	add	r2, r2, #584
	cmp	r2, r0
	bne	.L3309
	add	r0, r4, #50944
	ldr	r5, .L3330
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #56
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r3, [r5, #68]
	ldr	r1, .L3330+12
	mov	r0, #0
	blx	r3
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #176]
	ldr	r0, [r4, #2492]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	blt	.L3329
.L3327:
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3329:
	str	r1, [sp]
	mov	r0, #0
	ldr	ip, [r5, #68]
	ldr	r2, .L3330+16
	ldr	r1, .L3330+20
	blx	ip
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3328:
	add	r1, r4, #50944
	ldr	r0, [r4, #244]
	add	r1, r1, #56
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	b	.L3325
.L3308:
	ldr	ip, [r5, #68]
	mov	r0, #0
	ldr	r3, [r4, #2488]
	ldr	r2, [r4, #2492]
	ldr	r1, .L3330+24
	blx	ip
	b	.L3327
.L3331:
	.align	2
.L3330:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC436
	.word	.LC437
	.word	.LC439
	.word	.LANCHOR1+820
	.word	.LC440
	.word	.LC438
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	2
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #172]
	mov	r4, r0
	cmp	r3, #2
	bhi	.L3333
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #224]
	mov	r0, #0
	cmp	r3, #524288
	ldr	r3, .L3390
	bhi	.L3384
	ldr	r1, .L3390+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L3378:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3333:
	ldr	r3, [r0, #264]
	add	r6, r0, #40960
	ldr	r1, [r0, #268]
	add	r3, r3, #1
	ldr	r2, [r0, #2308]
	cmp	r3, r1
	movlt	r3, r1
	str	r3, [r0, #264]
	str	r3, [r2, #600]
	ldr	r3, [r0, #264]
	ldr	r1, [r0, #268]
	rsb	r3, r1, r3
	str	r3, [r2, #604]
	bl	HEVC_IsRefForCurrPic
	strb	r0, [r6, #2016]
	ldr	r5, [r4, #232]
	ldr	r2, [r4, #248]
	ubfx	r5, r5, #16, #3
	cmp	r5, r2
	beq	.L3336
	sub	r1, r2, #2
	cmp	r1, #1
	movhi	r1, #0
	movls	r1, #1
	cmp	r5, #2
	moveq	r1, #0
	cmp	r1, #0
	beq	.L3336
	cmp	r5, #4
	cmpne	r5, #1
	bls	.L3385
.L3336:
	cmp	r5, #2
	str	r5, [r4, #248]
	beq	.L3338
	cmp	r5, #3
	beq	.L3339
	cmp	r5, #1
	beq	.L3386
	ldr	r3, [r4, #216]
	cmp	r3, #0
	beq	.L3381
	cmp	r5, #4
	beq	.L3387
.L3343:
	ldr	r2, [r6, #2028]
.L3344:
	cmp	r2, #2
	beq	.L3388
	cmp	r2, #1
	streqb	r2, [r4, #3]
.L3349:
	ldr	r7, .L3390
	mov	r0, #2
	ldr	r2, [r4, #220]
	ldr	r1, .L3390+8
	ldr	r3, [r7, #68]
	sub	r2, r2, #1
	blx	r3
	ldr	r5, [r4, #208]
	cmp	r5, #0
	beq	.L3389
	ldr	r1, [r6, #2044]
	add	r3, r4, #49152
	add	r0, r4, #53248
	clz	r2, r1
	mov	r2, r2, lsr #5
	str	r2, [r3, #3520]
	ldr	r2, [r6, #2048]
	str	r2, [r3, #3512]
	str	r5, [r0, #524]
	ldr	r3, [r4, #220]
	cmp	r3, #0
	beq	.L3380
	add	r2, r4, #51200
	add	r3, r1, #1
	add	r2, r2, #156
	str	r2, [r4, #2312]
	ldr	r2, [r6, #2060]
	str	r2, [r0, #3240]
	ldr	r2, [r6, #2064]
	str	r2, [r0, #3244]
	ldr	r1, [r6, #2028]
	str	r3, [r6, #2044]
	cmp	r1, #0
	bne	.L3380
	ldr	r2, [r0, #528]
	cmp	r2, #0
	beq	.L3355
.L3354:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3354
.L3353:
	ldr	r3, .L3390+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3380
	sub	r2, fp, #28
	ldr	r0, [r4, #244]
	mov	r3, #4
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	ip
.L3380:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3384:
	ldr	r1, .L3390+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3386:
	ldr	r3, [r6, #2028]
	cmp	r0, #0
	cmpeq	r3, #2
	beq	.L3381
.L3341:
	ldr	r3, [r4, #216]
	cmp	r3, #0
	bne	.L3343
	b	.L3381
.L3385:
	ldr	ip, .L3390
	mov	r3, r5
	ldr	r1, .L3390+20
	mov	r0, #1
	ldr	ip, [ip, #68]
	blx	ip
	str	r5, [r4, #248]
.L3339:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3338:
	ldr	r3, [r6, #2028]
	cmp	r3, #0
	beq	.L3341
	b	.L3381
.L3388:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3349
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #0
	bne	.L3349
	ldr	r3, .L3390+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3349
	ldr	ip, .L3390
	mov	r3, r0
	ldr	r2, [r6, #2024]
	mov	r0, #1
	ldr	r1, .L3390+28
	ldr	ip, [ip, #68]
	blx	ip
.L3381:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3378
.L3387:
	ldr	r2, [r6, #2028]
	cmp	r2, #0
	moveq	r3, #2
	streqb	r3, [r4, #3]
	beq	.L3349
	b	.L3344
.L3355:
	mov	r1, r2
	b	.L3353
.L3389:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r2, .L3390+32
	ldr	r1, .L3390+36
	blx	r3
	mvn	r0, #0
	b	.L3378
.L3391:
	.align	2
.L3390:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC442
	.word	.LC445
	.word	g_event_report
	.word	.LC441
	.word	.LC443
	.word	g_allow_B_before_P
	.word	.LC444
	.word	.LANCHOR1+844
	.word	.LC446
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
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
	ldr	r0, [r0, #2316]
	ldr	r3, [r0, #8]
	cmp	r3, #0
	ldrne	r1, [r4, #224]
	movne	r2, r0
	movne	r3, #0
	beq	.L3397
.L3396:
	ldr	ip, [r2, #48]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, ip
	str	r1, [r4, #224]
	ldr	ip, [r0, #8]
	cmp	ip, r3
	bhi	.L3396
.L3397:
	mov	r3, #0
	strb	r3, [r0, #1]
	ldr	r3, [r4, #2316]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L3532
.L3395:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2316]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L3398
.L3400:
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3399
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3401
	.word	.L3402
	.word	.L3403
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3404
	.word	.L3404
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3398
	.word	.L3405
	.word	.L3406
.L3532:
	mov	r2, #1
	strb	r2, [r4]
	b	.L3395
.L3406:
	add	r5, r4, #2448
	mov	r1, #32
	add	r5, r5, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L3422
	ldr	r6, .L3534
	mov	r3, #1
	strb	r3, [r4, #6]
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3423
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #244]
	blx	ip
.L3423:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3422
.L3528:
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L3521
	b	.L3519
.L3399:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L3517
	cmp	r0, #0
	beq	.L3518
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	beq	.L3530
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3530:
	ldr	r3, .L3534
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3519
.L3521:
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3519:
	mvn	r0, #0
.L3517:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3401:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3407
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3407:
	cmp	r5, #0
	bne	.L3533
.L3518:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3402:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3412
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3412:
	cmp	r5, #0
	beq	.L3518
	ldr	r3, .L3534+4
	mov	r0, #1
	ldr	r6, .L3534
	ldr	r1, .L3534+8
	b	.L3525
.L3403:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3414
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3414:
	cmp	r5, #0
	beq	.L3518
	ldr	r3, .L3534+4
	mov	r0, #1
	ldr	r6, .L3534
	ldr	r1, .L3534+12
.L3525:
	ldr	r3, [r3, #68]
	blx	r3
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3519
	sub	r2, fp, #36
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #244]
	blx	ip
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L3521
	b	.L3519
.L3404:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3415
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3415:
	cmp	r5, #0
	beq	.L3518
	ldr	r3, .L3534+4
	mov	r0, #1
	ldr	r1, .L3534+16
	ldr	r3, [r3, #68]
	blx	r3
	b	.L3530
.L3405:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3420
	cmp	r1, #0
	beq	.L3419
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3419:
	add	r3, r4, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3518
.L3420:
	add	r6, r4, #2448
	mov	r1, #32
	add	r6, r6, #8
	mov	r5, #0
	strb	r5, [r4, #5]
	mov	r0, r6
	bl	BsGet
	mov	r1, #32
	mov	r7, r0
	mov	r0, r6
	bl	BsGet
	ldr	r2, .L3534+20
	rev	lr, r7
	ldrb	ip, [r2, #866]	@ zero_extendqisi2
	ldrb	r3, [r2, #865]	@ zero_extendqisi2
	ldrb	r9, [r2, #862]	@ zero_extendqisi2
	ldrb	r8, [r2, #867]	@ zero_extendqisi2
	orr	ip, r3, ip, asl #8
	ldrb	r1, [r2, #861]	@ zero_extendqisi2
	ldrb	r7, [r2, #863]	@ zero_extendqisi2
	ldrb	r6, [r2, #868]	@ zero_extendqisi2
	orr	r1, r1, r9, asl #8
	ldrb	r3, [r2, #864]	@ zero_extendqisi2
	orr	ip, ip, r8, asl #16
	orr	r2, r1, r7, asl #16
	orr	r1, ip, r6, asl #24
	orr	r2, r2, r3, asl #24
	rev	r0, r0
	cmp	r0, r1
	cmpeq	lr, r2
	bne	.L3518
	ldr	r6, .L3534
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3421
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r4, #244]
	blx	ip
.L3421:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L3528
	b	.L3518
.L3398:
	ldr	r3, .L3534+4
	mov	r0, #22
	ldr	r1, .L3534+24
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r4, #2316]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L3424
	cmp	r1, #0
	beq	.L3518
.L3520:
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2316]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3422:
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	bne	.L3520
	b	.L3518
.L3424:
	ldr	r6, .L3534
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3425
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #244]
	blx	ip
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	beq	.L3426
.L3427:
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2316]
.L3426:
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3518
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L3518
.L3425:
	cmp	r1, #0
	bne	.L3427
	b	.L3518
.L3533:
	ldr	r3, .L3534+4
	mov	r0, #1
	ldr	r6, .L3534
	ldr	r1, .L3534+28
	b	.L3525
.L3535:
	.align	2
.L3534:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC448
	.word	.LC449
	.word	.LC450
	.word	.LANCHOR1
	.word	.LC451
	.word	.LC447
	UNWIND(.fnend)
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	2
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
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
	mov	r3, #0
	strb	r3, [r1, #1]
	mov	r2, r3
	ldr	r1, [r1, #32]
	ldr	r0, [r0, #244]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.align	2
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
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
	ldr	r8, .L3564
	mov	r4, r0
	mov	r3, #0
	mov	r7, r1
	add	r0, r0, #43520
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r7]
	mov	r6, r2
	ldr	r3, [r8, #48]
	movw	r2, #3732
	add	r0, r0, #16
	add	r5, r4, #40960
	blx	r3
	ldr	r3, [r4, #2316]
	mov	r0, r4
	mov	r1, #1
	ldr	r2, [r3, #16]
	str	r2, [r5, #2648]
	ldr	r3, [r3, #32]
	str	r3, [r5, #2644]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L3560
	add	r2, r4, #45056
	movw	r1, #2024
	movw	lr, #15788
	add	ip, r4, #24576
	ldr	r2, [r2, #68]
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	str	r2, [r7]
	ldr	r2, [r5, #2652]
	ldr	r0, [r4, #2304]
	ldr	r3, [r4, #2300]
	ldr	r8, [ip, #2604]
	mla	r0, r1, r2, r0
	ldr	r5, [r4, #2308]
	ldr	r1, [r8, #236]
	ldr	r9, [r8, #72]
	ldr	r7, [r5, #852]
	ldr	r8, [r8, #76]
	ldr	r0, [r0, #32]
	mla	r3, lr, r0, r3
	ldr	r2, [r3, #236]
	ldr	lr, [r3, #72]
	subs	r2, r2, r1
	ldr	r0, [r3, #76]
	movne	r2, #1
	cmp	r7, #1
	beq	.L3561
.L3540:
	cmp	lr, r9
	moveq	r1, r2
	orrne	r1, r2, #1
	cmp	r0, r8
	moveq	r3, r1
	orrne	r3, r1, #1
	cmp	r3, #0
	beq	.L3562
.L3542:
	mov	r3, #1
	str	r3, [r6]
.L3543:
	ldr	r3, [r4, #220]
	cmp	r3, #0
	beq	.L3559
	ldr	r3, .L3564+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3559
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #120
	blx	ip
.L3559:
	mov	r0, #0
.L3539:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3560:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L3564+8
	blx	r3
	ldr	r3, .L3564+4
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L3539
	sub	r2, fp, #36
	ldr	r0, [r4, #244]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	ip
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3562:
	ldr	r3, [r6]
	cmp	r3, #1
	bne	.L3559
	b	.L3543
.L3561:
	ldr	r1, [r3, #108]
	ldr	r3, [r3, #100]
	cmp	r1, r3
	movcc	r1, r3
	str	r1, [r5, #896]
	ldr	r1, [ip, #2604]
	ldr	ip, [r4, #2308]
	ldr	r3, [r1, #108]
	ldr	r1, [r1, #100]
	ldr	r5, [ip, #896]
	cmp	r3, r1
	movcc	r3, r1
	cmp	r3, #8
	movls	r1, #0
	movhi	r1, #1
	cmp	r5, #8
	movne	r1, #0
	cmp	r1, #0
	beq	.L3563
.L3541:
	cmp	lr, r9
	moveq	r1, r2
	orrne	r1, r2, #1
	mov	r2, #1
	cmp	r0, r8
	moveq	r3, r1
	orrne	r3, r1, #1
	str	r2, [ip, #900]
	cmp	r3, #0
	str	r2, [r6]
	bne	.L3542
	b	.L3543
.L3563:
	sub	r3, r3, #8
	cmp	r5, #8
	clz	r3, r3
	mov	r3, r3, lsr #5
	movle	r3, #0
	cmp	r3, #0
	beq	.L3540
	b	.L3541
.L3565:
	.align	2
.L3564:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC452
	UNWIND(.fnend)
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	2
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	cmp	r1, #0
	mov	ip, #0
	mov	r4, r0
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	str	ip, [fp, #-40]
	beq	.L3622
	ldr	r2, [r0, #2308]
	ldrb	lr, [r0, #4]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	lr, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r0, #232]
	ldr	r3, [r2]
	str	r3, [r0, #236]
	ldr	r3, [r2, #4]
	str	r3, [r0, #240]
	beq	.L3569
	ldr	r3, [r2, #852]
	cmp	r3, #1
	addne	r6, r0, #69632
	beq	.L3623
.L3570:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2316]
	str	r3, [r6, #2820]
	mov	r5, r0
.L3571:
	cmp	r5, #0
	mov	r3, #0
	strb	r3, [r4, #4]
	beq	.L3572
.L3590:
	mov	r0, #0
.L3619:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3623:
	ldr	r3, [r2, #892]
	add	r6, r0, #69632
	cmp	r3, #1
	bne	.L3570
	ldr	r3, [r6, #2816]
	cmp	r3, #1
	bne	.L3570
	ldr	r3, [r6, #2820]
	mov	r0, ip
	str	r3, [r4, #2316]
	str	ip, [r6, #2816]
	strb	ip, [r4, #4]
	b	.L3619
.L3572:
	ldr	r3, [r4, #2316]
	str	r5, [r3, #4]
	ldr	r3, [r4, #2316]
	ldr	r0, [r4, #2292]
	ldr	r1, [r3, #44]
	ldr	r2, [r3, #48]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2292]
	bl	BsSkip
	mov	r1, #1
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #24]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #16]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #28]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	sub	r0, r0, #1
	str	r0, [r6, #32]
	ldr	r6, [r4, #2316]
	ldr	r0, [r6, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L3624
.L3573:
	mov	r3, #0
	str	r3, [r6, #4]
	ldr	r3, [r4, #2316]
	add	r0, r4, #2448
	add	r0, r0, #8
	ldr	r1, [r3, #44]
	ldr	r2, [r3, #48]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2292]
	bl	BsSkip
	mov	r1, #1
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #24]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #16]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #28]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	sub	r0, r0, #1
	str	r0, [r5, #32]
.L3589:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	beq	.L3619
	cmp	r0, #0
	beq	.L3590
	ldr	r3, .L3629
	mov	r0, #22
	ldr	r1, .L3629+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3619
.L3569:
	ldr	r3, [r0, #2316]
	cmp	r3, #0
	movne	r5, #0
	mvneq	r5, #0
	cmp	r3, #0
	bne	.L3571
	ldr	r3, .L3629
	mov	r0, ip
	ldr	r1, .L3629+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L3619
.L3624:
	sub	r2, fp, #32
	sub	r1, fp, #36
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	cmp	r0, #0
	bne	.L3574
	ldr	r6, [fp, #-36]
	cmp	r6, #1
	beq	.L3625
.L3575:
	ldr	r5, [fp, #-32]
	cmp	r5, #1
	beq	.L3626
.L3587:
	ldr	r6, [r4, #2316]
	ldr	r0, [r6, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	beq	.L3589
	b	.L3573
.L3574:
	ldr	r3, .L3629
	mov	r0, r7
	ldr	r1, .L3629+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	beq	.L3588
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2316]
.L3588:
	ldr	r3, .L3629+16
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L3619
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L3619
.L3625:
	ldr	r3, [r4, #208]
	cmp	r3, #0
	bne	.L3576
	add	r3, r4, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3575
	ldr	r3, .L3629
	ldr	r2, .L3629+20
	ldr	r1, .L3629+24
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L3575
.L3626:
	add	r3, r4, #40960
	ldr	r3, [r3, #2648]
	sub	r3, r3, #16
	cmp	r3, #4
	bls	.L3627
.L3580:
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L3628
.L3583:
	ldr	r0, [r4, #244]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L3587
	sub	r3, fp, #40
	sub	r2, fp, #44
	sub	r1, fp, #48
	ldr	r0, [r4, #244]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2308]
	ldr	r2, [r3, #776]
	cmp	r2, #1
	bne	.L3587
	ldr	r1, [fp, #-44]
	ldr	r3, [fp, #-40]
	add	r0, r1, r3
	cmp	r0, #1
	bgt	.L3586
	cmp	r1, #0
	cmpeq	r3, #1
	beq	.L3586
	cmp	r1, #1
	cmpeq	r3, #0
	bne	.L3587
	add	ip, r4, #49152
	movw	r0, #1852
	ldrh	r3, [ip, r0]
	add	r3, r3, #12736
	add	r3, r3, #16
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	ldr	lr, [r3, #104]
	cmp	lr, #0
	beq	.L3587
	ldr	r3, [r4, #244]
	ldr	r1, .L3629+28
	ldr	r3, [r1, r3, asl #2]
	add	r3, r3, #229376
	str	lr, [r3, #700]
	ldrh	r3, [ip, r0]
	ldr	r0, [r4, #244]
	add	r3, r3, #12736
	add	r3, r3, #16
	ldr	r0, [r1, r0, asl #2]
	add	r3, r4, r3, lsl #2
	add	r0, r0, #229376
	ldr	r3, [r3, #4]
	ldr	r3, [r3, #32]
	str	r3, [r0, #704]
	ldr	r3, [r4, #244]
	ldr	r3, [r1, r3, asl #2]
	add	r3, r3, #229376
	str	r2, [r3, #712]
	b	.L3587
.L3576:
	ldr	r3, [r4, #2316]
	add	r0, r4, #2448
	mov	r2, #13
	add	r0, r0, #8
	ldr	r1, .L3629+32
	str	r5, [r3, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2292]
	bl	BsSkip
	ldr	r3, [r4, #2316]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r6, [r4, #5]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #256]
	mvn	r0, #1
	strb	r6, [r4, #4]
	add	r3, r3, #1
	str	r3, [r4, #256]
	b	.L3619
.L3627:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	beq	.L3580
	ldr	r3, .L3629
	mov	r0, r5
	ldr	r2, .L3629+36
	ldr	r1, .L3629+40
	ldr	r3, [r3, #68]
	blx	r3
	b	.L3580
.L3622:
	ldr	r3, .L3629
	mov	r0, r1
	ldr	r1, .L3629+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3619
.L3628:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3583
	ldr	r3, .L3629
	mov	r0, r5
	ldr	r2, .L3629+36
	ldr	r1, .L3629+48
	ldr	r3, [r3, #68]
	blx	r3
	b	.L3583
.L3586:
	add	r2, r4, #69632
	mov	r1, #0
	mov	r3, #1
	mvn	r0, #1
	str	r1, [r2, #2836]
	strb	r3, [r4, #4]
	b	.L3619
.L3630:
	.align	2
.L3629:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC457
	.word	.LC454
	.word	.LC456
	.word	g_event_report
	.word	.LANCHOR1+872
	.word	.LC455
	.word	s_pstVfmwChan
	.word	.LANCHOR1+856
	.word	.LANCHOR1+892
	.word	.LC425
	.word	.LC453
	.word	.LC426
	UNWIND(.fnend)
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	2
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #208]
	cmp	r0, #0
	bne	.L3633
	add	r3, r4, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3635
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3633:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3635:
	ldr	r3, .L3636
	ldr	r2, .L3636+4
	ldr	r1, .L3636+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3637:
	.align	2
.L3636:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+872
	.word	.LC455
	UNWIND(.fnend)
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	2
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
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
	add	r0, r0, #53248
	ldr	r2, [r0, #528]
	cmp	r2, #0
	beq	.L3641
	mov	r0, #0
.L3640:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L3640
	ldmfd	sp, {fp, sp, pc}
.L3641:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.align	2
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, [r0, #2492]
	mov	r4, r0
	cmp	r3, #0
	beq	.L3655
	add	r7, r0, #50944
	ldr	r8, .L3667
	add	r7, r7, #56
	mvn	r6, #0
	b	.L3654
.L3646:
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-52]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r2, [r4, #2492]
	cmp	r2, #0
	beq	.L3663
.L3654:
	sub	r1, fp, #48
	sub	r2, fp, #52
	mov	r0, r4
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-52]
	add	r3, r1, #628
	ldr	r5, [r4, r3, asl #2]
	cmp	r5, #0
	beq	.L3646
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3646
	mov	r1, r5
	mov	r0, r4
	mov	r9, #1
	strb	r9, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L3664
.L3653:
	ldr	r1, [fp, #-52]
	b	.L3646
.L3663:
	cmp	r6, #0
	bne	.L3655
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3664:
	mov	r2, r9
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L3665
	ldr	r3, [r4, #2492]
	mov	r2, r4
	mov	r1, #17
	cmp	r3, #1
	streq	r3, [r10, #244]
	mov	r3, r7
	ldr	r0, [r4, #244]
	str	r10, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r9, r0
	beq	.L3650
	mov	r3, r0
	ldr	ip, [r8, #68]
	ldr	r2, .L3667+4
	mov	r0, #0
	ldr	r1, .L3667+8
	mvn	r9, #0
	blx	ip
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r1, #1
	mov	r0, r4
	bl	HEVC_ClearAll
.L3650:
	ldr	r3, [r4, #2308]
	ldr	r2, [r3, #684]
	add	r2, r2, #2032
	add	r2, r2, #15
	cmp	r2, #4096
	movcc	r3, #0
	strcc	r3, [r10, #84]
	bcs	.L3666
.L3652:
	ldr	r1, [r4, #2492]
	ldr	r2, [r4, #268]
	ldr	r3, [r4, #260]
	cmp	r1, #1
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
	beq	.L3653
	mov	r6, r9
	ldr	r1, [fp, #-52]
	b	.L3646
.L3655:
	add	r0, r4, #50944
	add	r0, r0, #56
	bl	GetVoLastImageID
	mov	r6, r0
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3666:
	mov	r1, r10
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.3
	b	.L3652
.L3665:
	ldr	r1, .L3667+12
	mvn	r6, #0
	ldr	r3, [r8, #68]
	ldr	r2, .L3667+4
	blx	r3
	ldr	r1, [fp, #-52]
	b	.L3646
.L3668:
	.align	2
.L3667:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+916
	.word	.LC459
	.word	.LC458
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	2
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
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
	add	r0, r0, #24576
	ldr	r2, [r0, #2604]
	ldr	r3, [r2, #152]
	ldr	r2, [r2, #72]
	rsb	r0, r3, #0
	add	r3, r3, r2
	sub	r3, r3, #1
	and	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.align	2
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
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
	add	r0, r0, #24576
	ldr	r2, [r0, #2604]
	ldr	r3, [r2, #152]
	ldr	r2, [r2, #76]
	rsb	r0, r3, #0
	add	r3, r3, r2
	sub	r3, r3, #1
	and	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	g_hrd_parameters
	.global	s_TmpParam
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	SarTable.13630, %object
	.size	SarTable.13630, 136
SarTable.13630:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.13780, %object
	.size	__func__.13780, 18
__func__.13780:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.14161, %object
	.size	__func__.14161, 27
__func__.14161:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.14169, %object
	.size	__func__.14169, 21
__func__.14169:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.14401, %object
	.size	__func__.14401, 17
__func__.14401:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.14554, %object
	.size	__func__.14554, 16
__func__.14554:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.14921, %object
	.size	__func__.14921, 21
__func__.14921:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.14770, %object
	.size	__func__.14770, 19
__func__.14770:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.14775, %object
	.size	__func__.14775, 23
__func__.14775:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.15059, %object
	.size	__func__.15059, 14
__func__.15059:
	.ascii	"HEVC_IsNewPic\000"
	.space	2
	.type	quant8_inter_default, %object
	.size	quant8_inter_default, 64
quant8_inter_default:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	quant_ts_default, %object
	.size	quant_ts_default, 16
quant_ts_default:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	__func__.15340, %object
	.size	__func__.15340, 16
__func__.15340:
	.ascii	"HEVC_ReleaseNAL\000"
.LC0:
	.word	1
	.word	2
	.word	2
	.word	1
.LC1:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.14252, %object
	.size	__func__.14252, 27
__func__.14252:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.14633, %object
	.size	__func__.14633, 13
__func__.14633:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15391, %object
	.size	__func__.15391, 13
__func__.15391:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.14913, %object
	.size	__func__.14913, 19
__func__.14913:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.14880, %object
	.size	__func__.14880, 22
__func__.14880:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.14175, %object
	.size	__func__.14175, 30
__func__.14175:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.14893, %object
	.size	__func__.14893, 27
__func__.14893:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.15430, %object
	.size	__func__.15430, 14
__func__.15430:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.14180, %object
	.size	__func__.14180, 23
__func__.14180:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.14861, %object
	.size	__func__.14861, 20
__func__.14861:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.14780, %object
	.size	__func__.14780, 22
__func__.14780:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.14785, %object
	.size	__func__.14785, 21
__func__.14785:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.14790, %object
	.size	__func__.14790, 22
__func__.14790:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.14804, %object
	.size	__func__.14804, 19
__func__.14804:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.14207, %object
	.size	__func__.14207, 14
__func__.14207:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.15380, %object
	.size	__func__.15380, 23
__func__.15380:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.14507, %object
	.size	__func__.14507, 12
__func__.14507:
	.ascii	"HEVC_DecVDM\000"
	.type	g_HEVCNalTypeEOPIC, %object
	.size	g_HEVCNalTypeEOPIC, 13
g_HEVCNalTypeEOPIC:
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.space	3
	.type	__func__.15492, %object
	.size	__func__.15492, 20
__func__.15492:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.13725, %object
	.size	__func__.13725, 21
__func__.13725:
	.ascii	"HEVCDEC_DecodePacket\000"
	.space	3
	.type	__func__.15509, %object
	.size	__func__.15509, 21
__func__.15509:
	.ascii	"HEVCDEC_GetRemainImg\000"
	.data
	.align	2
.LANCHOR4 = . + 0
	.type	quant8_intra_default, %object
	.size	quant8_intra_default, 64
quant8_intra_default:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_quantTSDefault4x4, %object
	.size	g_quantTSDefault4x4, 16
g_quantTSDefault4x4:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	g_quantInterDefault8x8, %object
	.size	g_quantInterDefault8x8, 64
g_quantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_quantIntraDefault8x8, %object
	.size	g_quantIntraDefault8x8, 64
g_quantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"dar=%d\012\000" )
.LC3:
	ASCII(.ascii	"--------------- PrintNaluArraySlot START ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"--------------- PrintNaluArraySlot END ------------" )
	ASCII(.ascii	"---\012\000" )
.LC6:
	ASCII(.ascii	"NalArray[%d]=%p,is_valid=%d   \000" )
	.space	1
.LC7:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX START ---------" )
	ASCII(.ascii	"------\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"List0, size: %d\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"List1, size: %d\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"pListX[0][%d]:%p \000" )
	.space	2
.LC11:
	ASCII(.ascii	"pFrameStore:%p \000" )
.LC12:
	ASCII(.ascii	"pLogicFs:%p \000" )
	.space	3
.LC13:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX END -----------" )
	ASCII(.ascii	"----\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"pListX[1][%d]: %p\000" )
	.space	2
.LC15:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC16:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC18:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC19:
	ASCII(.ascii	"--------------- PrintAPCState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"APC.used_size:%d, APC.size:%d\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"%d: is_used=%d, idc=%d, poc=%d\012\000" )
.LC22:
	ASCII(.ascii	"--------------- PrintAPCState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC23:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"fs[%d]:%p non_existing:%d state:%d is_ref:%d displa" )
	ASCII(.ascii	"yed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d f" )
	ASCII(.ascii	"sp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC26:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC27:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC28:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC29:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC30:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC31:
	ASCII(.ascii	"s32DispState:%d\011\000" )
	.space	3
.LC32:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC33:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC34:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC35:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC36:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC37:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC38:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC39:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC42:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC43:
	ASCII(.ascii	"firmware/common/syntax/hevc.c\000" )
	.space	2
.LC44:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC46:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC51:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC57:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC58:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC60:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC66:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC67:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC68:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC74:
	ASCII(.ascii	"HEVC_InitListX error.\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC76:
	ASCII(.ascii	"release(apc=%d, pmvIdc=%d)\011\000" )
.LC77:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC79:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC80:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC82:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC83:
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC86:
	ASCII(.ascii	"%s: ImgErrorLevel = %d, OutErrThr:%d, discarded!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC87:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC88:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC89:
	ASCII(.ascii	"hevc partition fs memory fail!\012\000" )
.LC90:
	ASCII(.ascii	"ERROR: HEVC FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC91:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC92:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC93:
	ASCII(.ascii	"FSP_GetFspType -1\012\000" )
	.space	1
.LC94:
	ASCII(.ascii	"FSP_GetLogicFs return NULL\012\000" )
.LC95:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC96:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC97:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC98:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC99:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC100:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC101:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC102:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC104:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC105:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC106:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC107:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC108:
	ASCII(.ascii	"general_profile_compatibility_flag[][%d]\000" )
	.space	3
.LC109:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC110:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC111:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC112:
	ASCII(.ascii	"Panic: All zero data sequence in RBSP \012\000" )
.LC113:
	ASCII(.ascii	"nal_trail_zero_bit_num err\012\000" )
.LC114:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC115:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC116:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC117:
	ASCII(.ascii	"HEVC_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC118:
	ASCII(.ascii	"tone_map_id\000" )
.LC119:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC120:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC121:
	ASCII(.ascii	"frame_packing_arrangement_id\000" )
	.space	3
.LC122:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC123:
	ASCII(.ascii	"decoding_unit_idx\000" )
	.space	2
.LC124:
	ASCII(.ascii	"num_sps_ids_minus1\000" )
	.space	1
.LC125:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"active_seq_parameter_set_id\000" )
.LC127:
	ASCII(.ascii	"bp_seq_parameter_set_id\000" )
.LC128:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC129:
	ASCII(.ascii	"HEVC_Sei_Buf_Period cpb_cnt_minus1(%d) out of range" )
	ASCII(.ascii	"(0,31).\012\000" )
.LC130:
	ASCII(.ascii	"num_decoding_units_minus1\000" )
	.space	2
.LC131:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"num_nalus_in_du_minus1\000" )
	.space	1
.LC133:
	ASCII(.ascii	"delta_idx_minus1\000" )
	.space	3
.LC134:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC135:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC136:
	ASCII(.ascii	"abs_delta_rps_minus1\000" )
	.space	3
.LC137:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC138:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC139:
	ASCII(.ascii	"num_negative_pics\000" )
	.space	2
.LC140:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"num_positive_pics\000" )
	.space	2
.LC142:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC143:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC144:
	ASCII(.ascii	"delta_poc_s0_minus1\000" )
.LC145:
	ASCII(.ascii	"delta_poc_s1_minus1\000" )
.LC146:
	ASCII(.ascii	"elemental_duration_in_tc_minus1\000" )
.LC147:
	ASCII(.ascii	"cpb_cnt_minus1\000" )
	.space	1
.LC148:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC149:
	ASCII(.ascii	"bit_rate_value_minus1\000" )
	.space	2
.LC150:
	ASCII(.ascii	"cpb_size_value_minus1\000" )
	.space	2
.LC151:
	ASCII(.ascii	"cpb_size_du_value_minus1\000" )
	.space	3
.LC152:
	ASCII(.ascii	"bit_rate_du_value_minus1\000" )
	.space	3
.LC153:
	ASCII(.ascii	"vps_reserved_three_2bits(%d) not equal 0x3.\012\000" )
	.space	3
.LC154:
	ASCII(.ascii	"vps_max_layers_minus1 out of range(0,63).\012\000" )
	.space	1
.LC155:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC156:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC157:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC158:
	ASCII(.ascii	"vps_num_layer_sets_minus1\000" )
	.space	2
.LC159:
	ASCII(.ascii	"vps_max_dec_pic_buffering_minus1[i]\000" )
.LC160:
	ASCII(.ascii	"vps_num_reorder_pics[i]\000" )
.LC161:
	ASCII(.ascii	"vps_max_latency_increase_plus1[i]\000" )
	.space	2
.LC162:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC163:
	ASCII(.ascii	"layer_id_included_flag[%d][%d]\000" )
	.space	1
.LC164:
	ASCII(.ascii	"vps_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC165:
	ASCII(.ascii	"vps_num_hrd_parameters\000" )
	.space	1
.LC166:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range(0,%d).\012\000" )
.LC167:
	ASCII(.ascii	"hrd_layer_set_idx\000" )
	.space	2
.LC168:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC169:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC170:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC171:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC172:
	ASCII(.ascii	"chroma_sample_loc_type_top_field\000" )
	.space	3
.LC173:
	ASCII(.ascii	"chroma_sample_loc_type_bottom_field\000" )
.LC174:
	ASCII(.ascii	"def_disp_win_left_offset\000" )
	.space	3
.LC175:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC176:
	ASCII(.ascii	"def_disp_win_right_offset\000" )
	.space	2
.LC177:
	ASCII(.ascii	"def_disp_win_top_offset\000" )
.LC178:
	ASCII(.ascii	"def_disp_win_bottom_offset\000" )
	.space	1
.LC179:
	ASCII(.ascii	"vui_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC180:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC181:
	ASCII(.ascii	"min_spatial_segmentation_idc\000" )
	.space	3
.LC182:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC183:
	ASCII(.ascii	"max_bytes_per_pic_denom\000" )
.LC184:
	ASCII(.ascii	"max_bits_per_min_cu_denom\000" )
	.space	2
.LC185:
	ASCII(.ascii	"log2_max_mv_length_horizontal\000" )
	.space	2
.LC186:
	ASCII(.ascii	"log2_max_mv_length_vertical\000" )
.LC187:
	ASCII(.ascii	"sop_seq_parameter_set_id\000" )
	.space	3
.LC188:
	ASCII(.ascii	"num_entries_in_sop_minus1\000" )
	.space	2
.LC189:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC190:
	ASCII(.ascii	"sop_short_term_rps_idx\000" )
	.space	1
.LC191:
	ASCII(.ascii	"sop_poc_delta\000" )
	.space	2
.LC192:
	ASCII(.ascii	"recovery_poc_cnt\000" )
	.space	3
.LC193:
	ASCII(.ascii	"reserved_payload_extension_data\000" )
.LC194:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC195:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC196:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC197:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC198:
	ASCII(.ascii	"nesting_num_ops_minus1\000" )
	.space	1
.LC199:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC200:
	ASCII(.ascii	"nesting_op_idx\000" )
	.space	1
.LC201:
	ASCII(.ascii	"nesting_num_layers_minus1\000" )
	.space	2
.LC202:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC203:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta\000" )
	.space	2
.LC204:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC205:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC206:
	ASCII(.ascii	"scaling_list_dc_coef_minus8\000" )
.LC207:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC208:
	ASCII(.ascii	"scaling_list_delta_coef\000" )
.LC209:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC210:
	ASCII(.ascii	"chroma_format_idc\000" )
	.space	2
.LC211:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC212:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC213:
	ASCII(.ascii	"pic_width_in_luma_samples\000" )
	.space	2
.LC214:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC215:
	ASCII(.ascii	"pic_height_in_luma_samples\000" )
	.space	1
.LC216:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC217:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC218:
	ASCII(.ascii	"conf_win_left_offset\000" )
	.space	3
.LC219:
	ASCII(.ascii	"conf_win_right_offset\000" )
	.space	2
.LC220:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC221:
	ASCII(.ascii	"conf_win_top_offset\000" )
.LC222:
	ASCII(.ascii	"conf_win_bottom_offset\000" )
	.space	1
.LC223:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC224:
	ASCII(.ascii	"bit_depth_luma_minus8\000" )
	.space	2
.LC225:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,14).\012\000" )
.LC226:
	ASCII(.ascii	"bit_depth_luma(%d) not equal 8.\012\000" )
	.space	3
.LC227:
	ASCII(.ascii	"bit_depth_chroma_minus8\000" )
.LC228:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC229:
	ASCII(.ascii	"bit_depth_chroma(%d) not equal 8.\012\000" )
	.space	1
.LC230:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	2
.LC231:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC232:
	ASCII(.ascii	"sps_max_dec_pic_buffering_minus1\000" )
	.space	3
.LC233:
	ASCII(.ascii	"sps_num_reorder_pics\000" )
	.space	3
.LC234:
	ASCII(.ascii	"sps_max_latency_increase_plus1\000" )
	.space	1
.LC235:
	ASCII(.ascii	"log2_min_coding_block_size_minus3\000" )
	.space	2
.LC236:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC237:
	ASCII(.ascii	"log2_diff_max_min_coding_block_size\000" )
.LC238:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC239:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC240:
	ASCII(.ascii	"log2_min_transform_block_size_minus2\000" )
	.space	3
.LC241:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC242:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size\000" )
	.space	1
.LC243:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC244:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC245:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC246:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter\000" )
.LC247:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC248:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra\000" )
.LC249:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC250:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC251:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC252:
	ASCII(.ascii	"log2_min_pcm_luma_coding_block_size_minus3\000" )
	.space	1
.LC253:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC254:
	ASCII(.ascii	"log2_diff_max_min_pcm_luma_coding_block_size\000" )
	.space	3
.LC255:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC256:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC257:
	ASCII(.ascii	"num_short_term_ref_pic_sets\000" )
.LC258:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC259:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC260:
	ASCII(.ascii	"num_long_term_ref_pic_sps\000" )
	.space	2
.LC261:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC262:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC263:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC264:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC265:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC266:
	ASCII(.ascii	"sps_seq_parameter_set_id\000" )
	.space	3
.LC267:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC268:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC269:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC270:
	ASCII(.ascii	"pps_seq_parameter_set_id\000" )
	.space	3
.LC271:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC272:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC273:
	ASCII(.ascii	"num_ref_idx_l0_default_active_minus1\000" )
	.space	3
.LC274:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC275:
	ASCII(.ascii	"num_ref_idx_l1_default_active_minus1\000" )
	.space	3
.LC276:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC277:
	ASCII(.ascii	"init_qp_minus26\000" )
.LC278:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC279:
	ASCII(.ascii	"diff_cu_qp_delta_depth\000" )
	.space	1
.LC280:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC281:
	ASCII(.ascii	"pps_cb_qp_offset\000" )
	.space	3
.LC282:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC283:
	ASCII(.ascii	"pps_cr_qp_offset\000" )
	.space	3
.LC284:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC285:
	ASCII(.ascii	"num_tile_columns_minus1\000" )
.LC286:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC287:
	ASCII(.ascii	"num_tile_rows_minus1\000" )
	.space	3
.LC288:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC289:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC290:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC291:
	ASCII(.ascii	"column_width_minus1\000" )
.LC292:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC293:
	ASCII(.ascii	"row_height_minus1\000" )
	.space	2
.LC294:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC295:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC296:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC297:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC298:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC299:
	ASCII(.ascii	"pps_beta_offset_div2\000" )
	.space	3
.LC300:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC301:
	ASCII(.ascii	"pps_tc_offset_div2\000" )
	.space	1
.LC302:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC303:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC304:
	ASCII(.ascii	"log2_parallel_merge_level_minus2\000" )
	.space	3
.LC305:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC306:
	ASCII(.ascii	"pps_pic_parameter_set_id\000" )
	.space	3
.LC307:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC308:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC309:
	ASCII(.ascii	"luma_log2_weight_denom\000" )
	.space	1
.LC310:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC311:
	ASCII(.ascii	"delta_chroma_log2_weight_denom\000" )
	.space	1
.LC312:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC313:
	ASCII(.ascii	"delta_luma_weight_l0\000" )
	.space	3
.LC314:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC315:
	ASCII(.ascii	"luma_offset_l0\000" )
	.space	1
.LC316:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC317:
	ASCII(.ascii	"delta_chroma_weight_l0\000" )
	.space	1
.LC318:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC319:
	ASCII(.ascii	"delta_chroma_offset_l0\000" )
	.space	1
.LC320:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC321:
	ASCII(.ascii	"delta_luma_weight_l1\000" )
	.space	3
.LC322:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC323:
	ASCII(.ascii	"luma_offset_l1\000" )
	.space	1
.LC324:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC325:
	ASCII(.ascii	"delta_chroma_weight_l1\000" )
	.space	1
.LC326:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC327:
	ASCII(.ascii	"delta_chroma_offset_l1\000" )
	.space	1
.LC328:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC329:
	ASCII(.ascii	"slice_pic_parameter_set_id\000" )
	.space	1
.LC330:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC331:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC332:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC333:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC334:
	ASCII(.ascii	"slice_type\000" )
	.space	1
.LC335:
	ASCII(.ascii	"slice_reserved_flag: %d\012\000" )
	.space	3
.LC336:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC337:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC338:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC339:
	ASCII(.ascii	"num_long_term_sps\000" )
	.space	2
.LC340:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC341:
	ASCII(.ascii	"num_long_term_pics\000" )
	.space	1
.LC342:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC343:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC344:
	ASCII(.ascii	"delta_poc_msb_cycle_lt\000" )
	.space	1
.LC345:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC346:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC347:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC348:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC349:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC350:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC351:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC352:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC353:
	ASCII(.ascii	"collocated_ref_idx\000" )
	.space	1
.LC354:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC355:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC356:
	ASCII(.ascii	"five_minus_max_num_merge_cand\000" )
	.space	2
.LC357:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC358:
	ASCII(.ascii	"slice_qp_delta\000" )
	.space	1
.LC359:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC360:
	ASCII(.ascii	"slice_cb_qp_offset\000" )
	.space	1
.LC361:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC362:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC363:
	ASCII(.ascii	"slice_cr_qp_offset\000" )
	.space	1
.LC364:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC365:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC366:
	ASCII(.ascii	"slice_beta_offset_div2\000" )
	.space	1
.LC367:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC368:
	ASCII(.ascii	"slice_tc_offset_div2\000" )
	.space	3
.LC369:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC370:
	ASCII(.ascii	"num_entry_point_offsets\000" )
.LC371:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC372:
	ASCII(.ascii	"offset_len_minus1\000" )
	.space	2
.LC373:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC374:
	ASCII(.ascii	"slice_segment_header_extension_length\000" )
	.space	2
.LC375:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC376:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC377:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC378:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC379:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC380:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC381:
	ASCII(.ascii	"BitDepthChange ReRange FS Luma(%d-->%d),Chroma(%d -" )
	ASCII(.ascii	"->%d)\012\000" )
	.space	2
.LC382:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC383:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC384:
	ASCII(.ascii	"%s: pstLogicFsImage is NULL!\012\000" )
	.space	2
.LC385:
	ASCII(.ascii	"HEVC InsertVO Failed return %d, ClearAll\012\000" )
	.space	2
.LC386:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC387:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC388:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC389:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC390:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC391:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC392:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC393:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC394:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC395:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC396:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC397:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC398:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC399:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC400:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC401:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC402:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC403:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC404:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC405:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC406:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC407:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC408:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC409:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC410:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC411:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC412:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC413:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC414:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC415:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC416:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC417:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC418:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC419:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC420:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC421:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC422:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC423:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC424:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC425:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC426:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC427:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d, \012\000" )
	.space	2
.LC428:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC429:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC430:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC431:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC432:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC433:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC434:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC435:
	ASCII(.ascii	"HEVC_StorePicInDPB failed, ret = %d\012\000" )
	.space	3
.LC436:
	ASCII(.ascii	"Unkown Error: No available fs, try to remove unused" )
	ASCII(.ascii	" fs!\012\000" )
	.space	3
.LC437:
	ASCII(.ascii	"Remove failed, clear DPB!\012\000" )
	.space	1
.LC438:
	ASCII(.ascii	"Remove success! DPB: used %d, size %d.\012\000" )
.LC439:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC440:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC441:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM, but MaxBytes" )
	ASCII(.ascii	"Received exceed threshold!\012\000" )
	.space	1
.LC442:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC443:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC444:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC445:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC446:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC447:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC448:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC449:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC450:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC451:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC452:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC453:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC454:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC455:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC456:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC457:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC458:
	ASCII(.ascii	"%s pstLogicFsImage is NULL!\012\000" )
	.space	3
.LC459:
	ASCII(.ascii	"%s InsertVO err:%d, ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR2 = . + 458304
.LANCHOR3 = . + 605616
.LANCHOR5 = . + 646536
.LANCHOR6 = . + 654720
	.type	s_auiSigLastScan, %object
	.size	s_auiSigLastScan, 458752
s_auiSigLastScan:
	.space	458752
	.type	g_TsToRsMap, %object
	.size	g_TsToRsMap, 147456
g_TsToRsMap:
	.space	147456
	.type	g_IsDeced, %object
	.size	g_IsDeced, 36864
g_IsDeced:
	.space	36864
	.type	g_hrd_parameters, %object
	.size	g_hrd_parameters, 10376
g_hrd_parameters:
	.space	10376
	.type	s_TmpParam, %object
	.size	s_TmpParam, 15788
s_TmpParam:
	.space	15788
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
