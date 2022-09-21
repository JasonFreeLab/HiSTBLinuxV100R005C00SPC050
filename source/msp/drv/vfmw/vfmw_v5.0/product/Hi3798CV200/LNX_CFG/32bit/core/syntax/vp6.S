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
	.file	"vp6.c"
	.text
	.align	2
	.global	Vp6_Vfmw_DecodeBool
	.type	Vp6_Vfmw_DecodeBool, %function
Vp6_Vfmw_DecodeBool:
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
	mov	r7, r1
	ldmib	r1, {r1, r5}
	mov	r6, r0
	ldr	r3, [r7, #12]
	sub	r4, r1, #1
	mul	r2, r4, r2
	mov	r4, r2, lsr #8
	add	r4, r4, #1
	mov	r2, r4, asl #16
	cmp	r5, r2
	rsbcs	r4, r4, r1
	rsbcs	r5, r2, r5
	movcs	r8, #1
	movcc	r8, #0
	cmp	r4, #127
	bls	.L6
	b	.L9
.L5:
	cmp	r4, #127
	bhi	.L11
.L6:
	subs	r3, r3, #1
	mov	r4, r4, asl #1
	mov	r5, r5, asl #1
	bne	.L5
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	cmp	r4, #127
	mov	r3, #8
	orr	r5, r5, r0
	bls	.L6
.L11:
	str	r3, [r7, #12]
.L9:
	stmib	r7, {r4, r5}
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_DecodeBool, .-Vp6_Vfmw_DecodeBool
	.align	2
	.global	Vp6_Vfmw_DecodeBool128
	.type	Vp6_Vfmw_DecodeBool128, %function
Vp6_Vfmw_DecodeBool128:
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
	ldr	r5, [r1, #4]
	mov	r4, r1
	ldr	r2, [r1, #8]
	add	r3, r5, #1
	ldr	r1, [r1, #12]
	mov	r3, r3, lsr #1
	mov	r6, r3, asl #16
	cmp	r2, r6
	rsbcs	r3, r3, r5
	rsbcs	r2, r6, r2
	movcs	r7, #1
	movcc	r5, r3, asl #1
	movcs	r5, r3, asl r7
	movcs	r6, r2, asl r7
	movcc	r6, r2, asl #1
	movcc	r7, #0
	subs	r1, r1, #1
	bne	.L15
	mov	r1, #8
	bl	BsGet
	mov	r1, #8
	orr	r6, r6, r0
.L15:
	str	r1, [r4, #12]
	mov	r0, r7
	stmib	r4, {r5, r6}
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_DecodeBool128, .-Vp6_Vfmw_DecodeBool128
	.align	2
	.global	Vp6_Vfmw_BoolRead
	.type	Vp6_Vfmw_BoolRead, %function
Vp6_Vfmw_BoolRead:
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
	subs	r4, r2, #1
	mov	r5, #0
	mov	r6, r0
	mov	r7, r1
	bmi	.L17
.L18:
	mov	r1, r7
	mov	r0, r6
	bl	Vp6_Vfmw_DecodeBool128
	orr	r5, r5, r0, asl r4
	subs	r4, r4, #1
	bcs	.L18
.L17:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_BoolRead, .-Vp6_Vfmw_BoolRead
	.align	2
	.global	Vp6_Vfmw_StartDecode
	.type	Vp6_Vfmw_StartDecode, %function
Vp6_Vfmw_StartDecode:
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
	mov	r4, r1
	mov	r2, #0
	mov	r3, #255
	stmia	r1, {r2, r3}
	mov	r3, #8
	mov	r1, #24
	str	r3, [r4, #12]
	bl	BsGet
	str	r0, [r4, #8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_StartDecode, .-Vp6_Vfmw_StartDecode
	.align	2
	.global	VP6_ArrangeVHBMem
	.type	VP6_ArrangeVHBMem, %function
VP6_ArrangeVHBMem:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r3, [r4, #244]
	ldr	r2, [r4, #248]
	cmp	r3, #2
	bls	.L24
	sub	r0, r2, #3
	movw	r1, #509
	cmp	r3, #512
	cmpls	r0, r1
	bhi	.L24
	ldr	r1, [r5]
	ldr	r0, [r1, #724]
	cmp	r0, #0
	ldr	r0, [r1, #28]
	bne	.L27
	cmp	r0, #25
	beq	.L51
.L28:
	mov	r6, #3
	mov	r7, r2, asl #4
	mov	r8, r3, asl #4
	mov	r9, r6
	mov	r10, #5
.L33:
	ldr	r3, .L53
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5]
	str	r7, [fp, #-60]
	str	r8, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r3, #24
	str	r8, [fp, #-48]
	beq	.L39
	uxtb	r6, r6
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L44:
	sub	r1, fp, #64
	ldr	r0, [r4, #752]
	strb	r6, [fp, #-61]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L40
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #752]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L52
	cmp	r0, #0
	moveq	r0, #1
	streq	r0, [r4, #32]
	beq	.L48
.L42:
	ldr	r1, .L53+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L24:
	ldr	r1, .L53+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L48:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L27:
	cmp	r0, #25
	bne	.L28
	ldr	r0, [r1, #684]
	mov	r2, r2, asl #4
	ldr	ip, [r1, #688]
	mov	r3, r3, asl #4
	cmp	r2, r0
	bhi	.L36
	cmp	r3, ip
	bhi	.L36
	ldr	r0, [r1, #712]
	mov	r7, r2
	ldr	r2, [r1, #708]
	mov	r8, r3
	cmp	r0, #0
	add	r9, r2, #2
	beq	.L46
	add	r6, r2, #1
	cmp	r6, #17
	movge	r6, #17
.L38:
	ldrb	r10, [r1, #732]	@ zero_extendqisi2
	b	.L33
.L40:
	ldr	r1, .L53+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L39:
	mov	r6, #1
	strb	r10, [fp, #-62]
	strb	r6, [fp, #-63]
	b	.L44
.L51:
	ldr	r7, [r1, #684]
	mov	r2, r2, asl #4
	ldr	r8, [r1, #688]
	mov	r3, r3, asl #4
	cmp	r2, r7
	bhi	.L30
	cmp	r3, r8
	bhi	.L30
	ldr	r0, [r4, #32]
	cmp	r0, #1
	beq	.L48
	ldr	r2, [r1, #712]
	ldr	r3, [r1, #708]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L46
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L38
.L36:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L53+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L46:
	mov	r6, #1
	b	.L38
.L30:
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L53+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L52:
	add	r0, r5, #12672
	add	r0, r0, #16
	bl	ResetVoQueue
	b	.L42
.L54:
	.align	2
.L53:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC0
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	VP6_ArrangeVHBMem, .-VP6_ArrangeVHBMem
	.align	2
	.global	VP6_GetImageBuffer
	.type	VP6_GetImageBuffer, %function
VP6_GetImageBuffer:
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
	add	r4, r0, #12288
	mov	r6, r0
	mov	r1, #1
	ldr	r0, [r4, #752]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #44]
	blt	.L61
	mov	r1, r0
	ldr	r0, [r4, #752]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L62
	ldr	r2, [r4, #44]
	mov	r0, #18
	ldr	r1, .L63
	bl	dprint_vfmw
	ldr	r3, [r5, #28]
	cmp	r3, #0
	beq	.L60
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L60
	ldr	r3, [r3, #24]
	mov	r0, #18
	ldr	r1, .L63+4
	str	r3, [r4, #60]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #28]
	str	r3, [r4, #64]
	ldr	r3, [r5, #32]
	ldr	r2, [r5, #28]
	ldr	r3, [r3, #8]
	ldr	r2, [r2, #8]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L60:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L61:
	ldr	r1, .L63+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #48]
	ldr	r0, [r4, #752]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	mov	r5, #0
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #12672
	str	r5, [r4, #28]
	add	r1, r1, #16
	str	r0, [r4, #52]
	str	r0, [r4, #48]
	ldr	r0, [r4, #752]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L62:
	movw	r2, #633
	ldr	r1, .L63+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L64:
	.align	2
.L63:
	.word	.LC6
	.word	.LC7
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	VP6_GetImageBuffer, .-VP6_GetImageBuffer
	.align	2
	.global	VP6DEC_GetImageBuffer
	.type	VP6DEC_GetImageBuffer, %function
VP6DEC_GetImageBuffer:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r0, [r4, #752]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #752]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L71
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L71:
	add	r1, r5, #12672
	ldr	r0, [r4, #752]
	add	r1, r1, #16
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6DEC_GetImageBuffer, .-VP6DEC_GetImageBuffer
	.align	2
	.global	VP6_BuildScanOrder
	.type	VP6_BuildScanOrder, %function
VP6_BuildScanOrder:
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
	add	r5, r0, #1088
	mov	r4, #1
	mov	lr, #0
	strb	lr, [r0, #960]
.L73:
	mov	r2, r5
	mov	r3, #1
.L75:
	ldrb	ip, [r2, #1]!	@ zero_extendqisi2
	cmp	ip, lr
	addeq	ip, r0, r4
	addeq	r4, r4, #1
	streqb	r3, [ip, #960]
	add	r3, r3, #1
	cmp	r3, #64
	bne	.L75
	add	lr, lr, #1
	cmp	lr, #16
	bne	.L73
	add	r5, r0, #1020
	add	r4, r0, #956
	add	r5, r5, #3
	add	r4, r4, #3
	mov	lr, #0
.L76:
	mov	r3, #0
	mov	ip, r4
	mov	r2, r3
.L77:
	ldrb	r0, [ip, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r3, r0
	movcc	r3, r0
	cmp	r2, lr
	bls	.L77
	uxtb	r3, r3
	strb	r3, [r5, #1]!
	ldr	r2, [r1, #16]
	add	lr, lr, #1
	cmp	r2, #6
	addhi	r3, r3, #1
	strhib	r3, [r5]
	cmp	lr, #64
	bne	.L76
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildScanOrder, .-VP6_BuildScanOrder
	.global	__aeabi_idiv
	.global	__aeabi_uidiv
	.align	2
	.global	VP6_BuildModeTree
	.type	VP6_BuildModeTree, %function
VP6_BuildModeTree:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	mov	r9, #0
	mov	r10, #100
	mov	r7, r9
	add	r2, r0, #404
	add	r3, r0, #464
	str	r0, [fp, #-128]
	str	r0, [fp, #-132]
	str	r2, [fp, #-140]
	str	r3, [fp, #-136]
.L84:
	ldr	r3, [fp, #-128]
	ldr	r8, [fp, #-140]
	ldr	r9, [fp, #-132]
	str	r3, [fp, #-92]
	str	r3, [fp, #-88]
.L90:
	mov	r4, #0
	sub	r1, fp, #84
	mov	r2, r4
	mov	r0, r8
.L87:
	cmp	r7, r2
	add	r2, r2, #1
	subeq	r3, fp, #84
	add	r1, r1, #4
	ldrneb	r3, [r0]	@ zero_extendqisi2
	moveq	ip, #0
	streq	ip, [r3, r7, asl #2]
	add	r0, r0, #1
	ldreq	r3, [r1, #-4]
	smulbbne	r3, r3, r10
	add	r4, r4, r3
	strne	r3, [r1, #-4]
	cmp	r2, #10
	bne	.L87
	ldr	r2, [fp, #-88]
	add	r8, r8, #20
	add	r9, r9, #90
	add	r2, r2, #20
	ldrb	r0, [r2, #394]	@ zero_extendqisi2
	ldrb	r3, [r2, #384]	@ zero_extendqisi2
	str	r2, [fp, #-88]
	mvn	r1, r0
	rsb	r0, r0, r0, lsl #8
	rsb	r1, r3, r1
	bl	__aeabi_idiv
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-84]
	add	r1, r4, #1
	ldr	r6, [fp, #-76]
	mov	ip, r3
	ldr	r3, [fp, #-68]
	add	r6, r2, r6
	ldr	lr, [fp, #-92]
	str	ip, [fp, #-96]
	add	ip, ip, r3
	add	r4, ip, r6
	str	r2, [fp, #-124]
	add	lr, lr, #10
	str	ip, [fp, #-104]
	sub	r3, r0, #1
	rsb	r0, r4, r4, lsl #8
	strb	r3, [lr, #-6]
	str	lr, [fp, #-92]
	bl	__aeabi_uidiv
	add	r1, r4, #1
	add	r3, r0, #1
	rsb	r0, r6, r6, lsl #8
	strb	r3, [r9, #-46]
	bl	__aeabi_uidiv
	ldr	lr, [fp, #-64]
	ldr	r3, [fp, #-80]
	ldr	r1, [fp, #-52]
	ldr	r5, [fp, #-56]
	ldr	ip, [fp, #-48]
	ldr	r4, [fp, #-60]
	add	r5, r3, r5
	add	ip, r1, ip
	str	r3, [fp, #-120]
	add	r4, lr, r4
	add	r3, ip, #1
	str	r1, [fp, #-108]
	add	r1, ip, r5
	add	ip, r4, #1
	str	r3, [fp, #-112]
	add	r1, r1, ip
	str	ip, [fp, #-116]
	str	lr, [fp, #-100]
	add	r0, r0, #1
	strb	r0, [r9, #-45]
	rsb	r0, r5, r5, lsl #8
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-124]
	add	r1, r6, #1
	add	lr, r0, #1
	rsb	r0, r2, r2, lsl #8
	strb	lr, [r9, #-44]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-96]
	ldr	ip, [fp, #-104]
	add	r1, ip, #1
	add	r2, r0, #1
	rsb	r0, r3, r3, lsl #8
	strb	r2, [r9, #-43]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-120]
	add	r1, r5, #1
	add	r2, r0, #1
	rsb	r0, r3, r3, lsl #8
	strb	r2, [r9, #-42]
	bl	__aeabi_uidiv
	ldr	r5, [fp, #-112]
	add	r1, r5, r4
	add	r3, r0, #1
	rsb	r0, r4, r4, lsl #8
	strb	r3, [r9, #-41]
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-116]
	ldr	lr, [fp, #-100]
	mov	r1, ip
	add	r3, r0, #1
	rsb	r0, lr, lr, lsl #8
	strb	r3, [r9, #-40]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-108]
	mov	r1, r5
	add	r3, r0, #1
	rsb	r0, r2, r2, lsl #8
	strb	r3, [r9, #-39]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-136]
	cmp	r8, r3
	add	r0, r0, #1
	strb	r0, [r9, #-38]
	bne	.L90
	ldr	r3, [fp, #-128]
	add	r7, r7, #1
	cmp	r7, #10
	add	r3, r3, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-132]
	add	r3, r3, #9
	str	r3, [fp, #-132]
	bne	.L84
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildModeTree, .-VP6_BuildModeTree
	.align	2
	.global	VP6_ConfigureContexts
	.type	VP6_ConfigureContexts, %function
VP6_ConfigureContexts:
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
	add	r7, r0, #1184
	add	lr, r0, #516
	add	r7, r7, #5
	add	lr, lr, #2
	add	r0, r0, #540
.L93:
	ldr	r6, .L101
	sub	r5, r7, #33
	add	r4, lr, #6
	sub	r8, lr, #5
.L98:
	sub	ip, r5, #5
	mov	r1, r8
	mov	r2, r6
.L94:
	ldmia	r2, {r3, r9}
	add	r2, r2, #24
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	mul	r3, r3, r10
	add	r3, r3, #128
	add	r3, r9, r3, asr #8
	cmp	r3, #255
	movge	r3, #255
	cmp	r3, #1
	movlt	r3, #1
	cmp	r1, lr
	strb	r3, [ip, #1]!
	bne	.L94
	mov	r2, r5
	mov	r3, lr
.L95:
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r4, r3
	strb	r1, [r2, #1]!
	bne	.L95
	add	r5, r5, #11
	add	r6, r6, #8
	cmp	r7, r5
	bne	.L98
	add	lr, lr, #11
	add	r7, r7, #33
	cmp	lr, r0
	bne	.L93
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L102:
	.align	2
.L101:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP6_ConfigureContexts, .-VP6_ConfigureContexts
	.align	2
	.global	VP6_ConfigureEntropyDecoder
	.type	VP6_ConfigureEntropyDecoder, %function
VP6_ConfigureEntropyDecoder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
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
	mov	lr, r2
	str	r2, [fp, #-100]
	mov	r9, r1
	ldr	r2, .L151
	mov	r1, #128
	str	r0, [fp, #-72]
	sub	r0, fp, #56
	str	r3, [fp, #-64]
	add	r8, lr, #76
	ldr	ip, [r2, #48]
	mov	r2, #11
	blx	ip
	mov	r3, #0
	str	r3, [fp, #-68]
.L104:
	ldr	r3, [fp, #-68]
	mov	r4, #0
	add	r5, r3, #512
	sub	r6, r3, #1
	ldr	r3, .L151+4
	add	r5, r5, #2
	add	r6, r3, r6
	ldr	r3, [fp, #-72]
	add	r5, r3, r5
.L108:
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L105
	mov	r10, #0
	mov	r7, #6
.L106:
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r7
	subs	r7, r7, #1
	bcs	.L106
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r2, #1
	movne	r2, #0
	add	r3, r3, r2
	sub	r2, fp, #56
	uxtb	r3, r3
	strb	r3, [r2, r4]
	strb	r3, [r5]
.L107:
	add	r4, r4, #1
	add	r5, r5, #1
	cmp	r4, #11
	bne	.L108
	ldr	r3, [fp, #-68]
	add	r3, r3, #11
	str	r3, [fp, #-68]
	cmp	r3, #22
	bne	.L104
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	bne	.L110
	ldr	r3, .L151
	mov	r2, #28
	ldr	r0, [fp, #-72]
	ldr	r1, .L151+8
	ldr	r3, [r3, #52]
	add	r0, r0, #536
	blx	r3
.L110:
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L114
	ldr	r3, [fp, #-72]
	ldr	r4, .L151+12
	add	r5, r3, #1088
	add	r5, r5, #1
	add	r6, r4, #63
.L113:
	ldrb	r2, [r4, #1]!	@ zero_extendqisi2
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L111
	mov	r10, #0
	mov	r7, #3
.L112:
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r7
	subs	r7, r7, #1
	bcs	.L112
	strb	r10, [r5]
.L111:
	cmp	r4, r6
	add	r5, r5, #1
	bne	.L113
	ldr	r1, [fp, #-100]
	ldr	r0, [fp, #-72]
	bl	VP6_BuildScanOrder
.L114:
	mov	r3, #0
	str	r3, [fp, #-68]
.L118:
	ldr	r3, [fp, #-68]
	sub	r5, r3, #1
	add	r6, r3, #536
	add	r7, r3, #13
	ldr	r3, .L151+16
	add	r5, r3, r5
	ldr	r3, [fp, #-72]
	add	r6, r3, r6
	ldr	r3, .L151+16
	add	r7, r3, r7
.L117:
	ldrb	r2, [r5, #1]!	@ zero_extendqisi2
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L115
	mov	r10, #0
	mov	r4, #6
.L116:
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r4
	subs	r4, r4, #1
	bcs	.L116
	mov	r10, r10, asl #1
	ands	r10, r10, #255
	moveq	r3, #1
	movne	r3, #0
	add	r3, r10, r3
	strb	r3, [r6]
.L115:
	cmp	r5, r7
	add	r6, r6, #1
	bne	.L117
	ldr	r3, [fp, #-68]
	add	r3, r3, #14
	str	r3, [fp, #-68]
	cmp	r3, #28
	bne	.L118
	mov	r3, #0
	str	r3, [fp, #-92]
.L127:
	ldr	r3, [fp, #-92]
	add	r2, r3, #396
	str	r2, [fp, #-96]
	str	r3, [fp, #-88]
	str	r3, [fp, #-84]
.L129:
	ldr	r3, [fp, #-84]
	add	r2, r3, #66
	str	r2, [fp, #-76]
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-88]
	sub	r3, r3, #1
	str	r3, [fp, #-80]
.L126:
	ldr	r3, [fp, #-68]
	mov	r4, #0
	ldr	r2, [fp, #-80]
	add	r5, r3, #564
	add	r6, r2, r3
	ldr	r3, .L151+20
	add	r6, r3, r6
	ldr	r3, [fp, #-72]
	add	r5, r3, r5
.L123:
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L120
	mov	r10, #0
	mov	r7, #6
.L121:
	mov	r1, r8
	mov	r0, r9
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r7
	subs	r7, r7, #1
	bcs	.L121
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r2, #1
	movne	r2, #0
	add	r3, r3, r2
	sub	r2, fp, #56
	uxtb	r3, r3
	strb	r3, [r2, r4]
	strb	r3, [r5]
.L122:
	add	r4, r4, #1
	add	r5, r5, #1
	cmp	r4, #11
	bne	.L123
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-76]
	add	r3, r3, #11
	str	r3, [fp, #-68]
	cmp	r3, r2
	bne	.L126
	ldr	r2, [fp, #-88]
	ldr	r3, [fp, #-84]
	sub	r2, r2, #132
	str	r2, [fp, #-88]
	ldr	r2, [fp, #-96]
	add	r3, r3, #198
	str	r3, [fp, #-84]
	cmp	r3, r2
	bne	.L129
	ldr	r3, [fp, #-92]
	add	r3, r3, #66
	str	r3, [fp, #-92]
	cmp	r3, #198
	bne	.L127
	ldr	r1, [fp, #-100]
	ldr	r0, [fp, #-72]
	bl	VP6_ConfigureContexts
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L120:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	subeq	r3, fp, #56
	ldreqb	r3, [r3, r4]	@ zero_extendqisi2
	streqb	r3, [r5]
	b	.L122
.L105:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	subeq	r3, fp, #56
	ldreqb	r3, [r3, r4]	@ zero_extendqisi2
	streqb	r3, [r5]
	b	.L107
.L152:
	.align	2
.L151:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+120
	.word	.LANCHOR0+144
	.word	.LANCHOR0+596
	.word	.LANCHOR0+172
	.word	.LANCHOR0+200
	UNWIND(.fnend)
	.size	VP6_ConfigureEntropyDecoder, .-VP6_ConfigureEntropyDecoder
	.align	2
	.global	VP6_decodeModeDiff
	.type	VP6_decodeModeDiff, %function
VP6_decodeModeDiff:
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
	add	r5, r1, #76
	mov	r2, #205
	mov	r7, r0
	mov	r1, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	mov	r2, #171
	mov	r1, r5
	mov	r6, r0, asl #1
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	rsb	r6, r6, #1
	cmp	r0, #0
	beq	.L163
	mov	r2, #199
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	movne	r8, #0
	movne	r4, #6
	beq	.L164
.L160:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r4
	subs	r4, r4, #1
	bcs	.L160
	mul	r0, r8, r6
	mov	r0, r0, asl #2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L164:
	mov	r2, #140
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L157
	mov	r0, r6, asl #4
	sub	r0, r0, r6, asl #2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L163:
	mov	r1, r5
	mov	r0, r7
	mov	r2, #83
	bl	Vp6_Vfmw_DecodeBool
	rsb	r0, r0, #3
	mov	r0, r6, asl r0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	mov	r2, #125
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L158
	mov	r0, r6, asl #4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L158:
	mov	r1, r5
	mov	r0, r7
	mov	r2, #104
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	movne	r0, r6, asl #4
	addne	r0, r0, r6, lsl #2
	moveq	r0, r6, asl #5
	subeq	r0, r0, r6, asl #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_decodeModeDiff, .-VP6_decodeModeDiff
	.align	2
	.global	VP6_DecodeModeProbs
	.type	VP6_DecodeModeProbs, %function
VP6_DecodeModeProbs:
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
	add	r9, r0, #412
	add	r9, r9, #1
	add	r7, r2, #76
	mov	r6, r2
	mov	r5, r1
	mov	r8, #0
	str	r0, [fp, #-48]
.L172:
	mov	r2, #174
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L166
	mov	r10, #0
	mov	r4, #3
.L167:
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r4
	subs	r4, r4, #1
	bcs	.L167
	mov	r3, r10, asl #4
	add	r0, r8, #20
	add	r1, r3, r10, lsl #2
	mov	r2, r9
	add	r3, r8, r1
	add	r0, r1, r0
	ldr	r1, .L186
	add	r3, r1, r3
	add	r0, r1, r0
.L168:
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	r3, r3, #2
	strb	r1, [r2, #1]!
	ldrb	r1, [r3, #-1]	@ zero_extendqisi2
	cmp	r3, r0
	strb	r1, [r2, #-10]
	bne	.L168
.L166:
	mov	r2, #254
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L173
	sub	r10, r9, #412
	mov	r4, #0
	sub	r10, r10, #1
.L171:
	mov	r1, r6
	mov	r0, r5
	bl	VP6_decodeModeDiff
	ldrb	r3, [r10, #414]	@ zero_extendqisi2
	adds	r0, r3, r0
	movmi	r0, #0
	bmi	.L169
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
.L169:
	strb	r0, [r10, #414]
	mov	r1, r6
	mov	r0, r5
	bl	VP6_decodeModeDiff
	ldrb	r3, [r10, #404]	@ zero_extendqisi2
	adds	r0, r3, r0
	movmi	r0, #0
	bmi	.L170
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
.L170:
	add	r4, r4, #1
	strb	r0, [r10, #404]
	cmp	r4, #10
	add	r10, r10, #1
	bne	.L171
.L173:
	add	r8, r8, #320
	add	r9, r9, #20
	cmp	r8, #960
	bne	.L172
	mov	r1, r6
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VP6_BuildModeTree
.L187:
	.align	2
.L186:
	.word	.LANCHOR0+660
	UNWIND(.fnend)
	.size	VP6_DecodeModeProbs, .-VP6_DecodeModeProbs
	.align	2
	.global	VP6_ConfigureMvEntropyDecoder
	.type	VP6_ConfigureMvEntropyDecoder, %function
VP6_ConfigureMvEntropyDecoder:
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
	ldr	r3, .L227
	add	r4, r2, #76
	mov	r5, r1
	add	r8, r3, #34
	mov	r7, r0
	mov	r6, r3
	str	r0, [fp, #-52]
.L196:
	ldrb	r2, [r6]	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L192
	mov	r10, #0
	mov	r9, #6
.L190:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L190
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r3, #1
	strb	r3, [r7, #2]
.L192:
	ldrb	r2, [r6, #1]	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L195
	mov	r10, #0
	mov	r9, #6
.L193:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L193
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r3, #1
	strb	r3, [r7]
.L195:
	add	r6, r6, #17
	add	r7, r7, #1
	cmp	r6, r8
	bne	.L196
	ldr	r3, [fp, #-52]
	add	r8, r3, #488
	mov	r3, #0
	add	r8, r8, #3
	str	r3, [fp, #-48]
.L197:
	ldr	r3, [fp, #-48]
	sub	r6, r8, #7
	add	r7, r3, #1
	ldr	r3, .L227
	add	r7, r3, r7
.L203:
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L199
	mov	r10, #0
	mov	r9, #6
.L200:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L200
	mov	r2, r10, asl #1
	ands	r2, r2, #255
	strneb	r2, [r6]
	moveq	r3, #1
	streqb	r3, [r6]
.L199:
	add	r6, r6, #1
	cmp	r8, r6
	bne	.L203
	ldr	r3, [fp, #-48]
	add	r8, r8, #7
	add	r3, r3, #17
	str	r3, [fp, #-48]
	cmp	r3, #34
	bne	.L197
	ldr	r3, [fp, #-52]
	add	r8, r3, #504
	mov	r3, #0
	add	r8, r8, #2
	str	r3, [fp, #-48]
.L204:
	ldr	r3, [fp, #-48]
	sub	r6, r8, #8
	add	r7, r3, #8
	ldr	r3, .L227
	add	r7, r3, r7
.L210:
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L206
	mov	r10, #0
	mov	r9, #6
.L207:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L207
	mov	r2, r10, asl #1
	ands	r2, r2, #255
	strneb	r2, [r6]
	moveq	r3, #1
	streqb	r3, [r6]
.L206:
	add	r6, r6, #1
	cmp	r8, r6
	bne	.L210
	ldr	r3, [fp, #-48]
	add	r8, r8, #8
	add	r3, r3, #17
	str	r3, [fp, #-48]
	cmp	r3, #34
	bne	.L204
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L228:
	.align	2
.L227:
	.word	.LANCHOR0+1620
	UNWIND(.fnend)
	.size	VP6_ConfigureMvEntropyDecoder, .-VP6_ConfigureMvEntropyDecoder
	.align	2
	.global	VP6_BoolTreeToHuffCodes
	.type	VP6_BoolTreeToHuffCodes, %function
VP6_BoolTreeToHuffCodes:
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
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	smulbb	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #44]
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	ldrb	r2, [r0]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1]
	ldrb	ip, [r0]	@ zero_extendqisi2
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	rsb	ip, ip, #255
	mul	r3, r3, ip
	mov	r3, r3, lsr #8
	str	r3, [r1, #4]
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	lr, [r0, #4]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #8]
	ldrb	r2, [r0, #4]	@ zero_extendqisi2
	ldrb	lr, [r0, #5]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	mul	ip, lr, r2
	mov	ip, ip, lsr #8
	str	ip, [r1, #12]
	ldrb	ip, [r0, #5]	@ zero_extendqisi2
	rsb	ip, ip, #255
	mul	r2, ip, r2
	mov	r2, r2, lsr #8
	str	r2, [r1, #16]
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	ldrb	r2, [r0, #6]	@ zero_extendqisi2
	rsb	ip, ip, #255
	ldrb	lr, [r0, #7]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #20]
	ldrb	r2, [r0, #7]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #24]
	ldrb	ip, [r0, #6]	@ zero_extendqisi2
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	rsb	ip, ip, #255
	ldrb	lr, [r0, #9]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #28]
	ldrb	r2, [r0, #9]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #32]
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	ldrb	ip, [r0, #10]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	mul	r2, ip, r3
	mov	r2, r2, lsr #8
	str	r2, [r1, #36]
	ldrb	r2, [r0, #10]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #40]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BoolTreeToHuffCodes, .-VP6_BoolTreeToHuffCodes
	.align	2
	.global	VP6_ZerosBoolTreeToHuffCodes
	.type	VP6_ZerosBoolTreeToHuffCodes, %function
VP6_ZerosBoolTreeToHuffCodes:
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
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	smulbb	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	r2, r2, lsr #8
	str	r2, [r1]
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #4]
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	ldrb	ip, [r0]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r2, r3, lsr #8
	mul	r3, lr, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #8]
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #12]
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r4, [r0, #4]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	ip, [r0, #5]	@ zero_extendqisi2
	ldrb	lr, [r0, #6]	@ zero_extendqisi2
	mul	r3, r4, r3
	mov	r3, r3, lsr #8
	mul	r3, ip, r3
	mov	r2, r3, lsr #8
	mul	r3, lr, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #16]
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #20]
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	lr, [r0, #4]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	r2, [r0, #5]	@ zero_extendqisi2
	ldrb	ip, [r0, #7]	@ zero_extendqisi2
	mul	r3, lr, r3
	rsb	r2, r2, #255
	mov	r3, r3, lsr #8
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	mul	r2, ip, r3
	mov	r2, r2, lsr #8
	str	r2, [r1, #24]
	ldrb	r2, [r0, #7]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #28]
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	ldrb	r2, [r0]	@ zero_extendqisi2
	rsb	r0, r3, #255
	rsb	r3, r2, #255
	mul	r3, r3, r0
	mov	r3, r3, lsr #8
	str	r3, [r1, #32]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_ZerosBoolTreeToHuffCodes, .-VP6_ZerosBoolTreeToHuffCodes
	.align	2
	.global	VP6_InsertSorted
	.type	VP6_InsertSorted, %function
VP6_InsertSorted:
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
	ldr	r5, [r2]
	mov	r7, r1, asl #4
	cmn	r5, #1
	beq	.L232
	mov	r3, r5, asl #4
	sub	r7, r7, r1, asl #2
	sub	r3, r3, r5, asl #2
	add	r7, r0, r7
	add	r3, r0, r3
	ldr	r6, [r7, #8]
	ldr	ip, [r3, #8]
	cmp	r6, ip
	bls	.L233
	mov	r4, r5
	b	.L235
.L243:
	add	r3, r0, r3
	ldr	lr, [r3, #8]
	cmp	lr, r6
	bcs	.L242
	mov	r4, ip
.L235:
	ldr	ip, [r3, #4]
	cmn	ip, #1
	mov	r3, ip, asl #4
	sub	r3, r3, ip, asl #2
	bne	.L243
.L234:
	mov	r3, r4, asl #4
	sub	r4, r3, r4, asl #2
	add	r0, r0, r4
	str	r1, [r0, #4]
	str	ip, [r7, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L242:
	cmp	r5, ip
	bne	.L234
.L237:
	str	r1, [r2]
	str	ip, [r7, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L232:
	sub	r7, r7, r1, asl #2
	add	r7, r0, r7
.L233:
	mov	ip, r5
	b	.L237
	UNWIND(.fnend)
	.size	VP6_InsertSorted, .-VP6_InsertSorted
	.align	2
	.global	VP6_BuildHuffTree
	.type	VP6_BuildHuffTree, %function
VP6_BuildHuffTree:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 376
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #380)
	sub	sp, sp, #380
	subs	r10, r2, #0
	mov	r9, r0
	mov	r0, #0
	str	r0, [fp, #-408]
	beq	.L249
	sub	r6, fp, #404
	sub	r1, r1, #4
	mov	r5, #1
	mvn	r4, #0
	mov	ip, r6
.L248:
	mov	r2, r0, asl #4
	sub	r3, fp, #44
	sub	r2, r2, r0, asl #2
	ldr	lr, [r1, #4]!
	add	r2, r3, r2
	cmp	lr, #0
	ldrb	r3, [r2, #-360]	@ zero_extendqisi2
	moveq	lr, #1
	streq	r5, [r1]
	orr	r3, r3, #1
	bfi	r3, r0, #1, #4
	add	r0, r0, #1
	cmp	r0, r10
	bfc	r3, #5, #3
	strb	r3, [r2, #-360]
	stmib	ip, {r4, lr}
	add	ip, ip, #12
	bne	.L248
	cmp	r10, #1
	bls	.L249
	sub	r7, fp, #408
	mov	r4, #1
.L250:
	mov	r1, r4
	mov	r2, r7
	mov	r0, r6
	add	r4, r4, #1
	bl	VP6_InsertSorted
	cmp	r4, r10
	bne	.L250
	ldr	r1, [fp, #-408]
.L246:
	mov	r2, r1, asl #2
	mov	r1, r1, asl #4
	rsb	r3, r2, r1
	sub	r0, fp, #44
	add	r3, r0, r3
	ldr	r3, [r3, #-356]
	cmn	r3, #1
	beq	.L244
	mov	r5, r10, asl #4
	sub	r8, r10, #2
	sub	r6, fp, #404
	sub	r5, r5, r10, asl #2
	add	r8, r8, r10
	add	r9, r9, r10, lsl #1
	and	r8, r8, #15
	add	r5, r6, r5
	sub	r7, fp, #408
	mov	r4, r10
	str	r6, [fp, #-416]
.L252:
	mov	ip, r4, asl #4
	rsb	lr, r2, r1
	sub	ip, ip, r4, asl #2
	sub	r2, fp, #44
	add	ip, r2, ip
	mov	r0, r3, asl #4
	sub	r3, r0, r3, asl #2
	add	lr, r2, lr
	ldrb	r1, [ip, #-360]	@ zero_extendqisi2
	add	r3, r2, r3
	rsb	r10, r4, r8
	ldr	r0, [lr, #-352]
	and	r1, r1, #254
	ldrb	lr, [lr, #-360]	@ zero_extendqisi2
	bfi	r1, r10, #1, #4
	ldrb	r10, [r3, #-360]	@ zero_extendqisi2
	strb	r1, [ip, #-360]
	mvn	r6, #0
	ldr	ip, [r3, #-352]
	mov	r1, r4
	str	r6, [r5, #4]
	mov	r2, r7
	add	r0, ip, r0
	str	r0, [r5, #8]
	ldr	r3, [r3, #-356]
	add	r4, r4, #1
	ldr	r0, [fp, #-416]
	add	r5, r5, #12
	strb	r10, [r9, #-3]
	sub	r9, r9, #2
	strb	lr, [r9, #-2]
	str	r3, [fp, #-408]
	bl	VP6_InsertSorted
	ldr	r1, [fp, #-408]
	sub	r0, fp, #44
	mov	r2, r1, asl #2
	mov	r1, r1, asl #4
	rsb	r3, r2, r1
	add	r3, r0, r3
	ldr	r3, [r3, #-356]
	cmp	r3, r6
	bne	.L252
.L244:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L249:
	mov	r1, #0
	b	.L246
	UNWIND(.fnend)
	.size	VP6_BuildHuffTree, .-VP6_BuildHuffTree
	.align	2
	.global	VP6_BuildHuffLookupTable
	.type	VP6_BuildHuffLookupTable, %function
VP6_BuildHuffLookupTable:
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
	mov	r4, #0
.L261:
	mov	r2, #0
	mov	lr, r2
.L260:
	rsb	r3, lr, #5
	add	r5, r0, r2, lsl #1
	mov	r3, r4, asr r3
	add	ip, lr, #1
	tst	r3, #1
	mov	lr, ip
	ldrneb	r3, [r5, #1]	@ zero_extendqisi2
	ldreqb	r3, [r0, r2, asl #1]	@ zero_extendqisi2
	and	r5, r3, #1
	ubfx	r2, r3, #1, #4
	bfi	r3, r5, #0, #1
	bfi	r3, r2, #1, #4
	eor	r3, r3, #1
	cmp	ip, #5
	movhi	r3, #0
	andls	r3, r3, #1
	cmp	r3, #0
	bne	.L260
	ldrb	r3, [r1, r4]	@ zero_extendqisi2
	bfi	r3, r2, #4, #4
	bfi	r3, ip, #1, #3
	bfi	r3, r5, #0, #1
	strb	r3, [r1, r4]
	add	r4, r4, #1
	cmp	r4, #64
	bne	.L261
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildHuffLookupTable, .-VP6_BuildHuffLookupTable
	.align	2
	.global	VP6_BuildTreeTab
	.type	VP6_BuildTreeTab, %function
VP6_BuildTreeTab:
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
	add	r6, r0, #9088
	add	r7, r0, #9920
	add	r6, r6, #30
	add	r7, r7, #62
	mov	r1, #0
.L265:
	sub	r5, r6, #432
.L274:
	sub	r4, r5, #96
.L272:
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	add	r3, r0, r1
	add	ip, r1, #1
	mov	r2, r4
	add	ip, r0, ip
	add	r1, r1, #2
	strb	lr, [r3, #1218]
	mov	r3, #0
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1218]
	b	.L270
.L268:
	ldrb	lr, [r2]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #11
	addne	r1, r1, #2
	addeq	r1, r1, #6
	add	r2, r2, #2
	strb	lr, [ip, #1218]
	ldrb	lr, [r2, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1219]
.L270:
	add	r3, r3, #1
	add	ip, r0, r1
	cmp	r3, #12
	bne	.L268
	add	r4, r4, #24
	cmp	r4, r5
	bne	.L272
	add	r5, r4, #144
	cmp	r6, r5
	bne	.L274
	add	r6, r4, #576
	cmp	r6, r7
	bne	.L265
	add	r4, r0, #9408
	add	r5, r0, #9472
	add	r4, r4, #46
	add	r5, r5, #30
	mov	r1, #768
.L273:
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	add	r3, r0, r1
	add	ip, r1, #1
	mov	r2, r4
	add	ip, r0, ip
	add	r1, r1, #2
	strb	lr, [r3, #1218]
	mov	r3, #0
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1218]
	b	.L279
.L277:
	ldrb	lr, [r2]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #11
	addne	r1, r1, #2
	addeq	r1, r1, #6
	add	r2, r2, #2
	strb	lr, [ip, #1218]
	ldrb	lr, [r2, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1219]
.L279:
	add	r3, r3, #1
	add	ip, r0, r1
	cmp	r3, #12
	bne	.L277
	add	r4, r4, #24
	cmp	r4, r5
	bne	.L273
	add	r4, r0, #8512
	add	r5, r0, #8576
	add	r4, r4, #20
	add	r5, r5, #12
	mov	ip, #832
.L278:
	mov	r1, r4
	mov	r3, #0
.L284:
	ldrb	lr, [r1]	@ zero_extendqisi2
	add	r2, r0, ip
	cmp	r3, #5
	cmpne	r3, #11
	addeq	ip, ip, #6
	strb	lr, [r2, #1218]
	ldrb	lr, [r1, #1]	@ zero_extendqisi2
	strb	lr, [r2, #1219]
	beq	.L281
	cmp	r3, #13
	beq	.L289
	add	ip, ip, #2
.L281:
	add	r3, r3, #1
	add	r1, r1, #2
	cmp	r3, #14
	bne	.L284
.L283:
	add	r4, r4, #28
	cmp	r4, r5
	bne	.L278
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L289:
	add	ip, ip, #30
	b	.L283
	UNWIND(.fnend)
	.size	VP6_BuildTreeTab, .-VP6_BuildTreeTab
	.align	2
	.global	VP6_ConvertBoolToHuff
	.type	VP6_ConvertBoolToHuff, %function
VP6_ConvertBoolToHuff:
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
	add	r6, r0, #6592
	mov	r7, r0
	add	r6, r6, #4
	ldr	r1, .L297
	mov	r0, #22
	add	r5, r7, #9408
	bl	dprint_vfmw
	add	r5, r5, #44
	add	r0, r7, #512
	mov	r1, r6
	add	r0, r0, #2
	bl	VP6_BoolTreeToHuffCodes
	mov	r2, #12
	mov	r1, r6
	mov	r0, r5
	bl	VP6_BuildHuffTree
	add	r4, r7, #6592
	add	r1, r7, #9472
	mov	r0, r5
	add	r4, r4, #52
	add	r1, r1, #28
	add	r6, r7, #9472
	bl	VP6_BuildHuffLookupTable
	add	r6, r6, #4
	add	r0, r7, #524
	mov	r1, r4
	add	r0, r0, #1
	bl	VP6_BoolTreeToHuffCodes
	add	r5, r7, #6656
	mov	r2, #12
	mov	r1, r4
	mov	r0, r6
	add	r5, r5, #36
	bl	VP6_BuildHuffTree
	add	r4, r7, #8512
	add	r1, r7, #9536
	mov	r0, r6
	add	r4, r4, #20
	add	r1, r1, #28
	bl	VP6_BuildHuffLookupTable
	mov	r1, r5
	add	r0, r7, #536
	bl	VP6_ZerosBoolTreeToHuffCodes
	mov	r2, #9
	mov	r1, r5
	mov	r0, r4
	bl	VP6_BuildHuffTree
	add	r5, r7, #6720
	add	r1, r7, #11904
	mov	r0, r4
	add	r5, r5, #28
	add	r1, r1, #28
	add	r4, r7, #8512
	bl	VP6_BuildHuffLookupTable
	add	r4, r4, #48
	add	r0, r7, #548
	mov	r1, r5
	add	r0, r0, #2
	bl	VP6_ZerosBoolTreeToHuffCodes
	mov	r1, r5
	mov	r0, r4
	mov	r2, #9
	bl	VP6_BuildHuffTree
	add	r3, r7, #760
	mov	r0, r4
	add	r1, r7, #11968
	mov	r4, r3
	add	r3, r7, #6784
	add	r1, r1, #28
	mov	r5, r3
	add	r3, r7, #8576
	mov	r6, r3
	add	r3, r7, #9600
	mov	r8, r3
	add	r3, r7, #1152
	mov	r9, r3
	bl	VP6_BuildHuffLookupTable
	add	r3, r4, #2
	str	r7, [fp, #-72]
	str	r3, [fp, #-52]
	add	r3, r5, #20
	str	r3, [fp, #-60]
	add	r3, r6, #12
	str	r3, [fp, #-64]
	add	r3, r8, #28
	str	r3, [fp, #-56]
	add	r3, r9, #6
	str	r3, [fp, #-68]
.L291:
	ldr	r3, [fp, #-52]
	ldr	r9, [fp, #-56]
	sub	r10, r3, #198
	ldr	r8, [fp, #-64]
	ldr	r3, [fp, #-60]
	str	r3, [fp, #-48]
.L295:
	ldr	r7, [fp, #-48]
	add	r6, r10, #66
	mov	r5, r9
	mov	r4, r8
.L292:
	mov	r1, r7
	mov	r0, r10
	bl	VP6_BoolTreeToHuffCodes
	mov	r1, r7
	mov	r0, r4
	mov	r2, #12
	bl	VP6_BuildHuffTree
	add	r10, r10, #11
	mov	r1, r5
	mov	r0, r4
	bl	VP6_BuildHuffLookupTable
	cmp	r10, r6
	add	r7, r7, #48
	add	r5, r5, #64
	add	r4, r4, #24
	bne	.L292
	ldr	r3, [fp, #-52]
	add	r8, r8, #144
	add	r9, r9, #384
	cmp	r3, r10
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L295
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-52]
	add	r2, r2, #864
	str	r2, [fp, #-60]
	ldr	r2, [fp, #-68]
	add	r3, r3, #198
	str	r3, [fp, #-52]
	cmp	r3, r2
	ldr	r3, [fp, #-64]
	add	r3, r3, #432
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-56]
	add	r3, r3, #1152
	str	r3, [fp, #-56]
	bne	.L291
	ldr	r7, [fp, #-72]
	mov	r0, r7
	bl	VP6_BuildTreeTab
	ldr	r1, .L297+4
	mov	r0, #22
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L298:
	.align	2
.L297:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	VP6_ConvertBoolToHuff, .-VP6_ConvertBoolToHuff
	.align	2
	.global	VP6_IntraFrmHeader
	.type	VP6_IntraFrmHeader, %function
VP6_IntraFrmHeader:
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
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L338
	mov	r0, #22
	add	r8, r4, #8192
	bl	dprint_vfmw
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	uxtb	r3, r0
	mov	r0, r5
	str	r3, [r8, #4084]
	bl	BsGet
	ldr	r2, [r8, #4084]
	cmp	r2, #8
	uxtb	r0, r0
	str	r0, [r8, #4088]
	bhi	.L334
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	cmp	r6, #0
	bne	.L335
	ldrb	r3, [r8, #4070]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L303
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	add	r9, r4, #12288
	mov	r2, #255
	mov	r3, #8
	str	r6, [r9, #48]
	mov	r1, #24
	str	r2, [r9, #52]
	str	r3, [r9, #60]
	str	r0, [r9, #28]
	mov	r0, r5
	bl	BsGet
	str	r0, [r9, #56]
.L304:
	add	r4, r4, #12288
	mov	r10, #0
	add	r4, r4, #48
	mov	r6, #7
.L305:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L305
	mov	r7, #0
	mov	r6, #7
	uxtb	r10, r10
	str	r10, [r9]
.L306:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L306
	ldr	r10, [r9]
	uxtb	r3, r7
	mov	r6, #7
	mov	r7, #0
	str	r3, [r9, #4]
	mov	r3, r3, asl #1
	mov	r10, r10, asl #1
	str	r3, [fp, #-48]
	str	r3, [r9, #12]
	str	r10, [r9, #8]
.L307:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L307
	uxtb	r2, r7
	mov	r6, #7
	mov	r7, #0
	mov	r2, r2, asl #1
	str	r2, [r9, #16]
.L308:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L308
	uxtb	r3, r7
	mov	r1, r4
	mov	r0, r5
	mov	r3, r3, asl #1
	str	r3, [r9, #20]
	bl	Vp6_Vfmw_DecodeBool128
	mov	r1, r4
	mov	r6, r0
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	ldr	r3, [r8, #3872]
	ldr	r2, [r8, #3868]
	cmp	r10, r3
	orr	r0, r0, r6, asl #1
	strb	r0, [r8, #4071]
	bne	.L310
	ldr	r1, [fp, #-48]
	cmp	r1, r2
	beq	.L311
.L310:
	ldr	r1, [fp, #-48]
	mov	r0, #22
	str	r10, [sp, #4]
	str	r1, [sp]
	ldr	r1, .L338+4
	bl	dprint_vfmw
.L311:
	ldr	r3, [r8, #4088]
	ldr	r2, [fp, #-48]
	cmp	r3, #0
	str	r10, [r8, #3872]
	str	r2, [r8, #3868]
	moveq	r2, #14
	streqb	r2, [r8, #4074]
	streq	r3, [r9, #32]
	bne	.L336
.L320:
	ldr	r1, .L338+8
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L334:
	ldr	r1, .L338+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L303:
	add	r9, r4, #12288
	mov	ip, #255
	mov	r2, #8
	mov	r1, #24
	str	r3, [r9, #48]
	mov	r0, r5
	str	ip, [r9, #52]
	str	r2, [r9, #60]
	bl	BsGet
	str	r0, [r9, #56]
	b	.L304
.L335:
	ldr	r1, .L338+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L336:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L313
	mov	r7, #0
	mov	r6, #4
	mov	r3, #2
	str	r3, [r9, #32]
.L314:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L314
	ldr	r3, [r8, #4084]
	mov	r9, #0
	mov	r6, #2
	cmp	r3, #7
	movhi	r3, r9
	movls	r3, #5
	mov	r7, r7, asl r3
	strb	r7, [r8, #4072]
.L316:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r9, r9, r0, asl r6
	subs	r6, r6, #1
	bcs	.L316
	strb	r9, [r8, #4073]
.L317:
	ldr	r3, [r8, #4084]
	cmp	r3, #7
	bls	.L337
	mov	r7, #0
	mov	r6, #3
.L319:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L319
	strb	r7, [r8, #4074]
	b	.L320
.L337:
	mov	r3, #16
	strb	r3, [r8, #4074]
	b	.L320
.L313:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	streq	r0, [r9, #32]
	movne	r3, #1
	strne	r3, [r9, #32]
	b	.L317
.L339:
	.align	2
.L338:
	.word	.LC10
	.word	.LC13
	.word	.LC14
	.word	.LC11
	.word	.LC12
	UNWIND(.fnend)
	.size	VP6_IntraFrmHeader, .-VP6_IntraFrmHeader
	.align	2
	.global	VP6_InterFrmHeader
	.type	VP6_InterFrmHeader, %function
VP6_InterFrmHeader:
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
	add	r4, r0, #8192
	mov	r5, r0
	mov	r7, r1
	ldr	r2, [r4, #3936]
	cmp	r2, #0
	beq	.L362
	ldrb	r3, [r4, #4070]	@ zero_extendqisi2
	ldr	r1, [r4, #3940]
	cmp	r3, #0
	str	r2, [r4, #4084]
	str	r1, [r4, #4088]
	bne	.L363
	add	r6, r0, #12288
	mov	ip, #255
	mov	r2, #8
	mov	r1, #24
	str	r3, [r6, #48]
	mov	r0, r7
	str	ip, [r6, #52]
	str	r2, [r6, #60]
	bl	BsGet
	str	r0, [r6, #56]
.L344:
	add	r5, r5, #12288
	mov	r0, r7
	add	r5, r5, #48
	mov	r1, r5
	bl	Vp6_Vfmw_DecodeBool128
	str	r0, [r6, #36]
	ldr	r3, [r4, #3940]
	str	r0, [r4, #3892]
	cmp	r3, #0
	bne	.L364
	mov	r2, #14
	mov	r0, #1
	strb	r2, [r4, #4074]
	str	r3, [r6, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L363:
	mov	r1, #16
	mov	r0, r7
	bl	BsGet
	add	r6, r5, #12288
	mov	r3, #0
	mov	r2, #255
	str	r3, [r6, #48]
	mov	r1, #24
	mov	r3, #8
	str	r2, [r6, #52]
	str	r3, [r6, #60]
	str	r0, [r6, #28]
	mov	r0, r7
	bl	BsGet
	str	r0, [r6, #56]
	b	.L344
.L364:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r6, #40]
	bne	.L365
.L346:
	ldr	r3, [r4, #3936]
	cmp	r3, #7
	bhi	.L366
	mov	r3, #16
	mov	r0, #1
	strb	r3, [r4, #4074]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L366:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	bne	.L367
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L365:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r0, r0, r8, asl #1
	str	r0, [r6, #40]
	b	.L346
.L367:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L348
	mov	r9, #0
	mov	r8, #4
	mov	r3, #2
	str	r3, [r6, #32]
.L349:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r9, r9, r0, asl r8
	subs	r8, r8, #1
	bcs	.L349
	mov	r8, #0
	mov	r6, #2
	strb	r9, [r4, #4072]
.L350:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r6
	subs	r6, r6, #1
	bcs	.L350
	strb	r8, [r4, #4073]
.L351:
	mov	r8, #0
	mov	r6, #3
.L353:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r6
	subs	r6, r6, #1
	bcs	.L353
	strb	r8, [r4, #4074]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L362:
	ldr	r3, [r4, #4084]
	mov	r0, #1
	ldr	r1, .L368
	bl	dprint_vfmw
	mvn	r0, #87
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L348:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	streq	r0, [r6, #32]
	movne	r3, #1
	strne	r3, [r6, #32]
	b	.L351
.L369:
	.align	2
.L368:
	.word	.LC15
	UNWIND(.fnend)
	.size	VP6_InterFrmHeader, .-VP6_InterFrmHeader
	.align	2
	.global	VP6_GetPictureHeader
	.type	VP6_GetPictureHeader, %function
VP6_GetPictureHeader:
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
	mov	r7, r0
	mov	r6, r1
	beq	.L376
	ldr	r1, .L379
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, #1
	mov	r0, r6
	add	r4, r7, #8192
	bl	BsGet
	mov	r1, #6
	uxtb	r3, r0
	mov	r0, r6
	str	r3, [r4, #4092]
	strb	r3, [r4, #3888]
	bl	BsGet
	ldr	r1, .L379+4
	add	r2, r7, #12224
	mov	ip, r0
	uxtb	r3, r0
	ldr	r0, .L379+8
	add	r1, r1, r3
	mov	r3, r3, asl #1
	strb	ip, [r4, #4068]
	add	r5, r0, #128
	ldrb	r8, [r1, #1656]	@ zero_extendqisi2
	ldrh	lr, [r0, r3]
	mov	r1, #1
	ldrh	r3, [r5, r3]
	mov	r0, r6
	strb	r8, [r4, #4069]
	strh	lr, [r2, #48]	@ movhi
	strh	r3, [r2, #50]	@ movhi
	bl	BsGet
	ldr	r3, [r4, #4092]
	mov	r1, r6
	cmp	r3, #0
	strb	r0, [r4, #4070]
	mov	r0, r7
	beq	.L377
	bl	VP6_InterFrmHeader
	mov	r5, r0
	cmp	r5, #1
	beq	.L378
.L375:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L377:
	bl	VP6_IntraFrmHeader
	mov	r5, r0
	cmp	r5, #1
	bne	.L375
.L378:
	add	r1, r7, #12288
	mov	r0, r6
	add	r1, r1, #48
	add	r7, r7, #12288
	bl	Vp6_Vfmw_DecodeBool128
	ldr	r1, .L379+12
	str	r0, [r7, #44]
	mov	r0, #22
	ldrb	r3, [r4, #4068]	@ zero_extendqisi2
	str	r3, [r7, #24]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	ldr	r1, .L379+16
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L380:
	.align	2
.L379:
	.word	.LC17
	.word	.LANCHOR0
	.word	.LANCHOR0+1720
	.word	.LC18
	.word	.LC16
	UNWIND(.fnend)
	.size	VP6_GetPictureHeader, .-VP6_GetPictureHeader
	.align	2
	.global	VP6DEC_Init
	.type	VP6DEC_Init, %function
VP6DEC_Init:
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
	ldr	r6, .L385
	add	r5, r0, #12288
	mov	r2, #13056
	mov	r7, r1
	ldr	r8, [r5, #744]
	mov	r1, #0
	ldr	r3, [r6, #48]
	mov	r4, r0
	blx	r3
	add	r0, r4, #12672
	add	r0, r0, #16
	str	r8, [r5, #744]
	bl	ResetVoQueue
	str	r7, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #752]
	beq	.L384
	ldr	r3, [r6, #48]
	movw	r2, #12408
	mov	r1, #0
	add	r0, r4, #244
	blx	r3
	mov	r2, #1024
	mov	r3, #0
	str	r2, [r5, #60]
	str	r3, [r5, #32]
	mov	r0, #22
	ldr	r3, [r4]
	ldr	r1, .L385+4
	ldr	r3, [r3, #8]
	str	r3, [r5, #24]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L384:
	ldr	r1, .L385+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L386:
	.align	2
.L385:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LC19
	UNWIND(.fnend)
	.size	VP6DEC_Init, .-VP6DEC_Init
	.align	2
	.global	VP6DEC_Destroy
	.type	VP6DEC_Destroy, %function
VP6DEC_Destroy:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6DEC_Destroy, .-VP6DEC_Destroy
	.align	2
	.global	VP6_DecodeDecide
	.type	VP6_DecodeDecide, %function
VP6_DecodeDecide:
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
	add	r4, r0, #12288
	mov	r6, r0
	ldr	r5, [r4, #32]
	cmp	r5, #0
	beq	.L414
	ldr	r3, [r4, #24]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r0]
	ldr	r2, [r3, #8]
	bls	.L415
.L392:
	str	r2, [r4, #24]
	cmp	r2, #4
	ldrls	pc, [pc, r2, asl #2]
	b	.L397
.L398:
	.word	.L396
	.word	.L396
	.word	.L393
	.word	.L395
	.word	.L396
.L416:
	ldr	r1, .L418
	mov	r0, #18
	bl	dprint_vfmw
.L395:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L415:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L392
	ldr	r1, .L418+4
	mov	r0, #2
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #48]
	mov	r5, #0
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #28]
	str	r0, [r4, #52]
	str	r0, [r4, #48]
	ldr	r3, [r6]
	ldr	r2, [r3, #8]
	b	.L392
.L414:
	ldr	r1, .L418+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L393:
	ldrb	r2, [r4, #36]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L416
.L394:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L417
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L403
	ldr	r3, [r6]
	ldr	r2, [r5, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L403
	ldr	r1, .L418+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L396:
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L394
	ldr	r3, [r4, #28]
	cmp	r3, #0
	bne	.L394
	ldr	r2, .L418+16
	mov	r0, #18
	ldr	r1, .L418+20
	bl	dprint_vfmw
	b	.L395
.L397:
	ldr	r1, .L418+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L403:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L417:
	movw	r3, #2139
	ldr	r2, .L418+28
	ldr	r1, .L418+32
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L419:
	.align	2
.L418:
	.word	.LC23
	.word	.LC22
	.word	.LC21
	.word	.LC28
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LANCHOR0+1976
	.word	.LC27
	UNWIND(.fnend)
	.size	VP6_DecodeDecide, .-VP6_DecodeDecide
	.align	2
	.global	VP6_Set_DecParam
	.type	VP6_Set_DecParam, %function
VP6_Set_DecParam:
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
	add	r6, r0, #12288
	mov	r4, r0
	add	r5, r0, #8
	ldr	r8, [r0, #228]
	ldrb	r3, [r6, #36]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L445
	ldr	r3, .L446
	mov	r2, #220
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, #240]
	mov	r2, #0
	strb	r2, [r4, #9]
	str	r3, [r4, #72]
	ldrb	r3, [r6, #216]	@ zero_extendqisi2
	str	r3, [r4, #76]
	ldrb	r3, [r6, #218]	@ zero_extendqisi2
	str	r3, [r4, #80]
	ldr	r3, [r6, #288]
	str	r3, [r4, #84]
	ldr	r3, [r6, #276]
	str	r3, [r4, #96]
	ldrb	r3, [r6, #220]	@ zero_extendqisi2
	str	r3, [r4, #100]
	ldrb	r3, [r6, #221]	@ zero_extendqisi2
	str	r3, [r4, #104]
	ldrb	r3, [r6, #222]	@ zero_extendqisi2
	str	r3, [r4, #108]
	ldr	r3, [r6, #284]
	str	r3, [r4, #120]
	ldrb	r3, [r6, #217]	@ zero_extendqisi2
	strb	r3, [r4, #8]
	ldrh	r3, [r6, #228]
	str	r3, [r4, #88]
	ldrh	r3, [r6, #230]
	str	r3, [r4, #92]
	ldr	r3, [r6, #236]
	str	r3, [r4, #116]
	ldr	r3, [r6, #232]
	str	r3, [r4, #112]
	ldr	r3, [r6, #248]
	strh	r3, [r4, #62]	@ movhi
	ldr	r3, [r6, #244]
	strh	r3, [r4, #64]	@ movhi
	ldr	r1, [r6, #44]
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #52]
	mov	r7, r0
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #48]
	mov	r9, r0
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	cmp	r7, #0
	cmpne	r9, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L429
	ldr	r3, [r7, #28]
	cmp	r3, #0
	beq	.L430
	ldr	r3, [r3, #8]
	str	r3, [r4, #184]
	ldr	r3, [r7, #8]
	str	r3, [r4, #196]
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #188]
	ldr	r3, [r9, #28]
	add	r9, r4, #12608
	add	r9, r9, #44
	cmp	r3, #0
	mov	r0, r9
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #192]
	ldr	r3, [r6, #60]
	str	r3, [r4, #200]
	ldr	r3, [r6, #64]
	str	r3, [r4, #204]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #60]
	str	r3, [r4, #208]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #44]
	str	r3, [r4, #212]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #48]
	str	r3, [r4, #216]
	ldr	r3, [r6, #300]
	str	r3, [r4, #172]
	ldr	r3, [r6, #296]
	str	r3, [r4, #176]
	ldr	r3, [r6, #304]
	str	r3, [r4, #180]
	ldr	r7, [r8]
	bl	BsPos
	mov	r3, r0
	add	r0, r0, #7
	cmp	r3, #0
	movlt	r3, r0
	add	r7, r7, r3, asr #3
	mov	r0, r7
	bl	MEM_Vir2Phy
	bic	r3, r0, #15
	mov	r0, r7
	sub	r3, r3, #16
	str	r3, [r4, #68]
	bl	MEM_Vir2Phy
	ldrb	r7, [r6, #218]	@ zero_extendqisi2
	cmp	r7, #0
	and	r0, r0, #15
	mov	r0, r0, asl #3
	bne	.L435
	ldr	r3, [r6, #236]
	cmp	r3, #0
	bne	.L436
.L435:
	mov	r3, #16
	str	r0, [r4, #128]
	str	r3, [r4, #132]
	mov	r0, r9
	ldr	r9, [r6, #272]
	bl	BsPos
	mov	r7, #0
	str	r7, [r4, #144]
	str	r7, [r4, #140]
	mov	r9, r9, asl #3
	str	r7, [r4, #136]
	rsb	r0, r0, r9
	str	r0, [r4, #124]
	ldr	r3, [r8]
	ldr	r10, [r6, #272]
	add	r10, r3, r10
	mov	r0, r10
	bl	MEM_Vir2Phy
	mov	r9, r0
	mov	r0, r10
	bl	MEM_Vir2Phy
	and	r9, r9, #15
	ldr	r3, [r4, #68]
	mov	r9, r9, asl #3
	str	r9, [r4, #152]
	bic	r0, r0, #15
	rsb	r0, r3, r0
	str	r0, [r4, #156]
	ldr	r3, [r6, #272]
	ldr	r2, [r8, #8]
	str	r7, [r4, #168]
	mov	r3, r3, asl #3
	str	r7, [r4, #164]
	rsb	r3, r3, r2, lsl #3
	str	r7, [r4, #160]
	str	r3, [r4, #148]
.L437:
	add	r9, r4, #4992
	add	r3, r4, #5120
	add	r3, r3, #54
	str	r3, [r4, #52]
	mov	r3, r9
	add	r3, r3, #22
	str	r3, [r4, #44]
	add	r10, r4, #4416
	ldr	r3, [r4]
	add	r8, r4, #4288
	add	r7, r4, #3312
	add	r6, r4, #3376
	add	lr, r4, #3248
	add	ip, r4, #2544
	add	r0, r4, #2480
	add	r1, r4, #3184
	add	r2, r4, #6656
	add	r10, r10, #22
	add	r9, r9, #54
	str	r10, [r4, #40]
	str	r9, [r4, #48]
	add	r8, r8, #54
	add	r7, r7, #6
	str	r8, [r4, #36]
	str	r7, [r4, #28]
	add	r6, r6, #6
	add	lr, lr, #6
	str	r6, [r4, #32]
	str	lr, [r4, #24]
	add	ip, ip, #6
	add	r0, r0, #6
	str	ip, [r4, #16]
	str	r0, [r4, #12]
	add	r1, r1, #6
	add	r2, r2, #54
	str	r1, [r4, #20]
	str	r2, [r4, #56]
	mov	r0, #1
	ldr	r3, [r3, #592]
	str	r3, [r4, #220]
	ldr	r3, [r4]
	ldr	r3, [r3, #644]
	str	r5, [r4, #4]
	str	r3, [r4, #224]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L429:
	ldr	r1, .L446+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L445:
	str	r3, [r0, #72]
	mov	r3, #1
	strb	r3, [r0, #9]
	ldr	r1, [r6, #44]
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #52]
	mov	r7, r0
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #48]
	mov	r8, r0
	ldr	r0, [r6, #752]
	bl	FSP_GetLogicFs
	cmp	r7, #0
	cmpne	r8, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L429
	ldr	r3, [r7, #28]
	cmp	r3, #0
	beq	.L430
	ldr	r3, [r3, #8]
	str	r3, [r4, #184]
	ldr	r3, [r7, #8]
	str	r3, [r4, #196]
	ldr	r3, [r0, #28]
	mov	r0, #1
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #188]
	ldr	r3, [r8, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r5, [r4, #4]
	str	r3, [r4, #192]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L436:
	str	r0, [r4, #128]
	mov	r3, #16
	mov	r0, r9
	str	r3, [r4, #132]
	ldr	r6, [r8, #8]
	bl	BsPos
	str	r7, [r4, #144]
	str	r7, [r4, #140]
	mov	r6, r6, asl #3
	str	r7, [r4, #136]
	str	r7, [r4, #156]
	str	r7, [r4, #152]
	str	r7, [r4, #148]
	str	r7, [r4, #168]
	str	r7, [r4, #164]
	str	r7, [r4, #160]
	rsb	r0, r0, r6
	str	r0, [r4, #124]
	b	.L437
.L430:
	ldr	r1, .L446+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L447:
	.align	2
.L446:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC29
	.word	.LC30
	UNWIND(.fnend)
	.size	VP6_Set_DecParam, .-VP6_Set_DecParam
	.align	2
	.global	VP6_CfgTable
	.type	VP6_CfgTable, %function
VP6_CfgTable:
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
	ldr	r5, .L473
	add	r4, r0, #2240
	add	r7, r0, #2288
	add	r4, r4, #2
	add	r7, r7, #2
	add	r6, r0, #4
	mov	r9, r0
	mov	r3, #0
	str	r1, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
.L449:
	mov	r1, r6
	mov	r0, r4
	ldr	r3, [r5, #52]
	mov	r2, #10
	add	r4, r4, #16
	blx	r3
	cmp	r4, r7
	add	r6, r6, #10
	bne	.L449
	add	r3, r9, #2944
	add	r7, r9, #2304
	add	r3, r3, #2
	add	r7, r7, #2
	add	r8, r9, #44
	str	r9, [fp, #-68]
	mov	r10, r3
.L450:
	add	r6, r7, #160
	mov	r9, r8
.L451:
	mov	r1, r9
	mov	r0, r7
	ldr	ip, [r5, #52]
	mov	r2, #9
	add	r7, r7, #16
	blx	ip
	cmp	r7, r6
	add	r9, r9, #9
	ldr	r4, .L473
	bne	.L451
	cmp	r7, r10
	add	r8, r8, #90
	bne	.L450
	ldr	r9, [fp, #-68]
	mov	r1, #0
	ldr	r3, [r4, #48]
	mov	r2, #16
	sub	r0, fp, #60
	mov	r6, r1
	blx	r3
	ldrb	r10, [r9]	@ zero_extendqisi2
	ldrb	r8, [r9, #2]	@ zero_extendqisi2
	mov	r0, r7
	ldrb	r7, [r9, #484]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	lr, [r9, #485]	@ zero_extendqisi2
	mov	r2, #16
	ldrb	ip, [r9, #486]	@ zero_extendqisi2
	ldrb	r3, [r9, #487]	@ zero_extendqisi2
	strb	r10, [fp, #-60]
	strb	r8, [fp, #-59]
	ldrb	r10, [r9, #488]	@ zero_extendqisi2
	ldrb	r8, [r9, #489]	@ zero_extendqisi2
	strb	r7, [fp, #-58]
	ldrb	r7, [r9, #490]	@ zero_extendqisi2
	strb	lr, [fp, #-57]
	strb	ip, [fp, #-56]
	strb	r3, [fp, #-55]
	strb	r10, [fp, #-54]
	strb	r8, [fp, #-53]
	strb	r7, [fp, #-52]
	ldr	r3, [r4, #52]
	blx	r3
	mov	r1, r6
	ldr	r3, [r4, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r3
	ldrb	lr, [r9]	@ zero_extendqisi2
	ldrb	ip, [r9, #498]	@ zero_extendqisi2
	add	r0, r9, #2960
	ldrb	r3, [r9, #499]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	r10, [r9, #500]	@ zero_extendqisi2
	mov	r2, #16
	ldrb	r8, [r9, #501]	@ zero_extendqisi2
	add	r0, r0, #2
	ldrb	r7, [r9, #502]	@ zero_extendqisi2
	strb	lr, [fp, #-60]
	strb	ip, [fp, #-59]
	ldrb	lr, [r9, #503]	@ zero_extendqisi2
	ldrb	ip, [r9, #504]	@ zero_extendqisi2
	strb	r3, [fp, #-58]
	ldrb	r3, [r9, #505]	@ zero_extendqisi2
	strb	lr, [fp, #-54]
	strb	ip, [fp, #-53]
	strb	r10, [fp, #-57]
	strb	r8, [fp, #-56]
	strb	r7, [fp, #-55]
	strb	r3, [fp, #-52]
	strb	r6, [fp, #-51]
	strb	r6, [fp, #-50]
	ldr	r3, [r4, #52]
	blx	r3
	mov	r1, r6
	ldr	r3, [r4, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r3
	ldrb	lr, [r9, #1]	@ zero_extendqisi2
	ldrb	ip, [r9, #3]	@ zero_extendqisi2
	add	r0, r9, #2976
	ldrb	r3, [r9, #491]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	r10, [r9, #492]	@ zero_extendqisi2
	mov	r2, #16
	ldrb	r8, [r9, #493]	@ zero_extendqisi2
	add	r0, r0, #2
	ldrb	r7, [r9, #494]	@ zero_extendqisi2
	strb	lr, [fp, #-60]
	strb	ip, [fp, #-59]
	ldrb	lr, [r9, #495]	@ zero_extendqisi2
	ldrb	ip, [r9, #496]	@ zero_extendqisi2
	strb	r3, [fp, #-58]
	ldrb	r3, [r9, #497]	@ zero_extendqisi2
	strb	lr, [fp, #-54]
	strb	ip, [fp, #-53]
	strb	r10, [fp, #-57]
	strb	r8, [fp, #-56]
	strb	r7, [fp, #-55]
	strb	r3, [fp, #-52]
	ldr	r3, [r4, #52]
	blx	r3
	mov	r1, r6
	ldr	r3, [r4, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r3
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	ldrb	lr, [r9, #508]	@ zero_extendqisi2
	add	r0, r9, #2992
	ldrb	r2, [r9, #509]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	r8, [r9, #506]	@ zero_extendqisi2
	add	r0, r0, #2
	ldrb	r7, [r9, #507]	@ zero_extendqisi2
	str	r2, [fp, #-68]
	mov	r2, #16
	ldrb	r10, [r9, #510]	@ zero_extendqisi2
	ldrb	ip, [r9, #511]	@ zero_extendqisi2
	strb	r6, [fp, #-51]
	strb	r6, [fp, #-50]
	strb	r3, [fp, #-60]
	ldrb	r6, [r9, #512]	@ zero_extendqisi2
	ldrb	r3, [r9, #513]	@ zero_extendqisi2
	strb	lr, [fp, #-57]
	ldrb	lr, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [fp, #-52]
	strb	r8, [fp, #-59]
	ldr	r3, [r4, #52]
	strb	r7, [fp, #-58]
	strb	lr, [fp, #-56]
	strb	r10, [fp, #-55]
	strb	ip, [fp, #-54]
	strb	r6, [fp, #-53]
	blx	r3
	ldr	r3, [fp, #-64]
	ldr	r3, [r3, #72]
	cmp	r3, #0
	bne	.L453
	add	r6, r9, #4096
	add	r7, r9, #1152
	mov	r4, r6
	add	r6, r6, #2
	add	r4, r4, #50
.L454:
	mov	r1, r7
	mov	r0, r6
	ldr	r3, [r5, #52]
	mov	r2, #11
	add	r6, r6, #16
	blx	r3
	cmp	r6, r4
	add	r7, r7, #11
	bne	.L454
	add	r6, r9, #1184
	add	r7, r9, #4160
	add	r6, r6, #1
	add	r7, r7, #34
.L455:
	mov	r1, r6
	mov	r0, r4
	ldr	r3, [r5, #52]
	mov	r2, #11
	add	r4, r4, #16
	blx	r3
	cmp	r4, r7
	add	r6, r6, #11
	ldr	r10, .L473
	bne	.L455
	add	r0, r9, #4736
	ldr	r3, [r10, #52]
	mov	r2, #14
	add	r1, r9, #536
	add	r0, r0, #34
	add	r8, r9, #4480
	blx	r3
	add	ip, r9, #5056
	add	r1, r9, #548
	add	r0, r9, #4736
	ldr	r3, [r10, #52]
	add	r1, r1, #2
	add	r0, r0, #50
	mov	r2, #14
	mov	r4, ip
	blx	r3
	add	r3, r4, #2
	str	r3, [fp, #-64]
	add	r3, r9, #564
	add	r8, r8, #2
	str	r9, [fp, #-68]
	mov	r10, r3
.L462:
	sub	r4, r8, #288
	mov	r7, r10
.L465:
	add	r9, r4, #48
	mov	r6, r7
.L463:
	mov	r1, r6
	mov	r0, r4
	ldr	r3, [r5, #52]
	mov	r2, #11
	add	r4, r4, #16
	blx	r3
	cmp	r9, r4
	add	r6, r6, #66
	bne	.L463
	cmp	r9, r8
	add	r7, r7, #11
	mov	r4, r9
	bne	.L465
	ldr	r3, [fp, #-64]
	add	r8, r8, #288
	add	r10, r10, #198
	cmp	r8, r3
	bne	.L462
	ldr	r9, [fp, #-68]
.L461:
	add	r0, r9, #3008
	ldr	r3, [r5, #52]
	add	r1, r9, #960
	mov	r2, #64
	add	r0, r0, #2
	blx	r3
	add	r0, r9, #3072
	ldr	r3, [r5, #52]
	add	r1, r9, #1024
	mov	r2, #64
	add	r0, r0, #2
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L453:
	add	r1, r9, #9472
	add	r0, r9, #4800
	ldr	r3, [r4, #52]
	add	r1, r1, #28
	mov	r2, #128
	add	r0, r0, #2
	blx	r3
	add	ip, r9, #9600
	ldr	r3, [r4, #52]
	add	r1, r9, #11904
	mov	r4, ip
	add	r0, r9, #6464
	add	ip, r9, #7232
	mov	r2, #128
	add	r1, r1, #28
	add	r0, r0, #2
	mov	r6, ip
	add	r8, r9, #5696
	blx	r3
	add	r3, r4, #28
	add	r8, r8, #2
	add	r2, r6, #2
	mov	r10, r3
	str	r2, [fp, #-64]
	str	r9, [fp, #-68]
.L456:
	sub	r4, r8, #768
	mov	r7, r10
.L460:
	add	r6, r4, #256
	mov	r9, r7
.L457:
	ldr	r3, [r5, #52]
	mov	r2, #64
	mov	r1, r9
	mov	r0, r4
	add	r4, r4, r2
	blx	r3
	cmp	r6, r4
	add	r9, r9, #64
	ldr	r3, .L473
	bne	.L457
	cmp	r6, r8
	add	r7, r7, #384
	mov	r4, r6
	bne	.L460
	ldr	r2, [fp, #-64]
	add	r8, r6, #768
	add	r10, r10, #1152
	cmp	r8, r2
	bne	.L456
	ldr	r9, [fp, #-68]
	mov	r2, #960
	ldr	r3, [r3, #52]
	add	r1, r9, #1216
	add	r0, r9, #3136
	add	r1, r1, #2
	add	r0, r0, #2
	blx	r3
	b	.L461
.L474:
	.align	2
.L473:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP6_CfgTable, .-VP6_CfgTable
	.align	2
	.global	VP6_BuildTables
	.type	VP6_BuildTables, %function
VP6_BuildTables:
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
	mov	r4, r1
	mov	r6, r2
	mov	r5, r0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L480
	ldr	r3, [r1, #24]
	cmp	r3, #0
	bne	.L484
	ldr	r7, .L486
	mov	r2, #80
	ldr	r1, .L486+4
	add	r0, r0, #404
	ldr	r3, [r7, #52]
	blx	r3
	mov	r2, #2
	ldr	r3, [r7, #52]
	add	r0, r5, r2
	ldr	r1, .L486+8
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #14
	ldr	r1, .L486+12
	add	r0, r5, #484
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #2
	ldr	r1, .L486+16
	mov	r0, r5
	blx	r3
	add	r0, r5, #496
	ldr	r3, [r7, #52]
	mov	r2, #16
	ldr	r1, .L486+20
	add	r0, r0, #2
	blx	r3
	ldr	r1, .L486+24
	ldr	r3, [r7, #52]
	mov	r2, #64
	add	r0, r5, #1088
	blx	r3
	mov	r1, r4
	mov	r0, r5
	bl	VP6_BuildScanOrder
.L478:
	ldr	r3, [r4, #24]
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VP6_ConfigureEntropyDecoder
	ldr	r3, [r4, #72]
	cmp	r3, #0
	bne	.L485
.L479:
	mov	r1, r4
	mov	r0, r5
	bl	VP6_CfgTable
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L484:
	mov	r2, r1
	mov	r1, r6
	bl	VP6_DecodeModeProbs
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	bl	VP6_ConfigureMvEntropyDecoder
	b	.L478
.L485:
	mov	r0, r5
	bl	VP6_ConvertBoolToHuff
	b	.L479
.L480:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L487:
	.align	2
.L486:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1996
	.word	.LANCHOR0+2076
	.word	.LANCHOR0+2080
	.word	.LANCHOR0+2096
	.word	.LANCHOR0+2100
	.word	.LANCHOR0+2116
	UNWIND(.fnend)
	.size	VP6_BuildTables, .-VP6_BuildTables
	.align	2
	.global	IsFrameSizeChanged
	.type	IsFrameSizeChanged, %function
IsFrameSizeChanged:
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
	add	r3, r0, #8192
	add	r0, r0, #12288
	ldr	r1, [r3, #3948]
	ldr	r2, [r0]
	cmp	r1, r2
	beq	.L491
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L491:
	ldr	r3, [r3, #3952]
	ldr	r0, [r0, #4]
	subs	r0, r3, r0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsFrameSizeChanged, .-IsFrameSizeChanged
	.align	2
	.global	VP6DEC_Decode
	.type	VP6DEC_Decode, %function
VP6DEC_Decode:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r3, [r1]
	mov	r4, r0
	str	r3, [r0, #232]
	ldr	r2, [r1, #8]
	str	r2, [r0, #236]
	ldr	r2, [r1, #12]
	cmp	r2, #0
	str	r2, [r0, #240]
	bne	.L493
	add	r5, r0, #12288
	mov	r3, #3
	strb	r3, [r5, #36]
.L494:
	mov	r0, r4
	bl	VP6_DecodeDecide
	cmp	r0, #1
	mov	r6, r0
	beq	.L515
	ldr	r1, .L542
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
.L496:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L493:
	cmp	r2, #2
	ble	.L537
	add	r5, r0, #12608
	add	r6, r0, #244
	add	r5, r5, #44
	mov	r1, r3
	mov	r0, r5
	bl	BsInit
	add	r3, r4, #232
	mov	r1, r5
	mov	r0, r6
	str	r3, [r4, #228]
	bl	VP6_GetPictureHeader
	cmp	r0, #1
	mov	r7, r0
	beq	.L497
	ldr	r1, .L542+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L515:
	mov	r0, r4
	bl	VP6_GetImageBuffer
	cmp	r0, #1
	mov	r8, r0
	beq	.L516
	mov	r0, r6
	ldr	r1, .L542+8
	bl	dprint_vfmw
	mov	r6, #0
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L537:
	ldr	r1, .L542+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L497:
	add	r1, r4, #12480
	mov	r2, r5
	mov	r0, r6
	add	r1, r1, #24
	bl	VP6_BuildTables
	cmp	r0, #1
	bne	.L538
	add	r5, r4, #12288
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L499
	ldr	r2, [r5, #96]
	ldr	r3, [r5, #244]
	cmp	r2, r3
	bne	.L499
	ldr	r2, [r5, #100]
	ldr	r3, [r5, #248]
	cmp	r2, r3
	beq	.L494
.L499:
	ldr	r6, .L542+16
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L501
	ldr	r0, [r5, #244]
	mov	r3, #8
	ldr	r8, [r5, #100]
	sub	r2, fp, #52
	ldr	r7, [r5, #96]
	mov	r1, #2
	ldr	lr, [r5, #248]
	strh	r0, [fp, #-46]	@ movhi
	strh	r8, [fp, #-52]	@ movhi
	strh	r7, [fp, #-50]	@ movhi
	strh	lr, [fp, #-48]	@ movhi
	ldr	r0, [r5, #752]
	blx	ip
.L501:
	ldr	r0, [r5, #752]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	bne	.L502
	sub	r3, fp, #44
	sub	r2, fp, #56
	sub	r1, fp, #60
	ldr	r0, [r5, #752]
	str	ip, [r3, #-8]!
	str	ip, [fp, #-60]
	str	ip, [fp, #-56]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	bne	.L502
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	bgt	.L505
	ldr	r3, [fp, #-56]
	cmp	r3, #32
	bgt	.L505
	ldr	r7, [r4, #4]
	cmp	r7, #0
	bne	.L505
	ldr	r3, [r5, #100]
	cmp	r3, #0
	beq	.L502
	ldr	r1, [r5, #244]
	ldr	r0, [r5, #756]
	cmp	r1, r0
	beq	.L502
	ldr	r0, [r5, #248]
	ldr	ip, [r5, #760]
	cmp	r0, ip
	beq	.L502
	ldr	ip, [r5, #96]
	stmib	sp, {r0, r1}
	mov	r0, r2
	ldr	r1, .L542+20
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r6]
	ldr	r2, [r5, #244]
	ldr	r3, [r5, #248]
	cmp	ip, #0
	str	r2, [r5, #756]
	str	r3, [r5, #760]
	beq	.L502
	mov	r3, r7
	mov	r2, r7
	mov	r1, #120
	ldr	r0, [r5, #752]
	blx	ip
.L502:
	mov	r2, #1
	ldr	r1, [r5, #48]
	ldr	r0, [r5, #752]
	mov	r7, #0
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #52]
	add	r6, r4, #12672
	ldr	r0, [r5, #752]
	add	r6, r6, #16
	bl	FSP_ClearLogicFs
	str	r7, [r5, #48]
	str	r7, [r5, #52]
	ldr	r0, [r5, #752]
	bl	FSP_GetNullLogicFs
	str	r7, [r5, #28]
	mov	r1, r6
	str	r0, [r5, #52]
	str	r0, [r5, #48]
	ldr	r0, [r5, #752]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [r5, #248]
	ldr	r3, [r5, #244]
	cmp	r2, #512
	bhi	.L509
	cmp	r3, #512
	bhi	.L509
	ldr	r3, [r4]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L511
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L539
.L511:
	ldr	r0, [r5, #752]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L536
.L513:
	mov	r0, r4
	bl	VP6_ArrangeVHBMem
	cmp	r0, #1
	beq	.L494
	ldr	r1, .L542+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
	b	.L496
.L516:
	mov	r2, r0
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_SetRef
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetFsImagePtr
	subs	lr, r0, #0
	beq	.L540
	ldr	r0, [r4]
	add	ip, lr, #592
	add	r10, lr, #608
	mov	r9, #0
	mvn	r2, #0
	mvn	r3, #0
	ldrd	r6, [r0, #56]
	mov	r0, #29
	ldr	r1, .L542+28
	strd	r6, [ip, #-8]
	ldr	r6, [r4]
	ldrd	r6, [r6, #72]
	strd	r6, [ip]
	ldr	r6, [r4]
	ldrd	r6, [r6, #88]
	strd	r6, [r10, #-8]
	ldr	r6, [r4]
	ldr	r6, [r6, #104]
	str	r6, [lr]
	ldr	r6, [r4]
	ldr	r6, [r6, #108]
	str	r6, [lr, #4]
	ldr	r6, [r4]
	ldr	r6, [r6, #112]
	str	r6, [lr, #8]
	ldr	r6, [r4]
	ldr	r6, [r6, #128]
	str	r9, [lr, #52]
	str	r6, [lr, #12]
	ldr	lr, [r4]
	strd	r2, [lr, #56]
	ldrd	r6, [ip]
	ldrd	r2, [ip, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	VP6_Set_DecParam
	cmp	r0, #1
	mov	r6, r0
	beq	.L518
	mov	r0, r8
	ldr	r1, .L542+32
	mov	r6, r9
	bl	dprint_vfmw
	b	.L496
.L518:
	ldrb	r3, [r5, #36]	@ zero_extendqisi2
	add	r1, r4, #12480
	cmp	r3, #0
	ldr	r3, .L542+36
	beq	.L541
	ldr	r7, [r5, #84]
	add	r0, r4, #12352
	ldr	r4, [r5, #88]
	add	r1, r1, #24
	ldr	r3, [r3, #52]
	add	r0, r0, #4
	mov	r2, #148
	blx	r3
	str	r7, [r5, #84]
	str	r4, [r5, #88]
.L520:
	ldr	r1, .L542+40
	mov	r0, #22
	bl	dprint_vfmw
	b	.L496
.L538:
	mov	r0, r7
	ldr	r1, .L542+44
	bl	dprint_vfmw
	mov	r6, #0
	b	.L496
.L509:
	ldr	r1, .L542+48
	mov	r0, #18
	bl	dprint_vfmw
	mov	r6, #0
	b	.L496
.L541:
	add	r0, r4, #12352
	add	r1, r1, #24
	mov	r2, #148
	ldr	r3, [r3, #52]
	add	r0, r0, #4
	blx	r3
	b	.L520
.L540:
	movw	r2, #2756
	ldr	r1, .L542+52
	mov	r0, #22
	mov	r6, lr
	bl	dprint_vfmw
	b	.L496
.L539:
	ldr	r3, [r5, #32]
	cmp	r3, #0
	bne	.L513
.L536:
	mov	r0, r6
	bl	ResetVoQueue
	b	.L513
.L505:
	mvn	r6, #1
	b	.L496
.L543:
	.align	2
.L542:
	.word	.LC37
	.word	.LC32
	.word	.LC38
	.word	.LC31
	.word	g_event_report
	.word	.LC34
	.word	.LC36
	.word	.LC39
	.word	.LC40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC41
	.word	.LC33
	.word	.LC35
	.word	.LC5
	UNWIND(.fnend)
	.size	VP6DEC_Decode, .-VP6DEC_Decode
	.align	2
	.global	VP6_SetImgFormat
	.type	VP6_SetImgFormat, %function
VP6_SetImgFormat:
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
	add	r5, r0, #12288
	mov	r6, r0
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldrb	r2, [r5, #36]	@ zero_extendqisi2
	mov	ip, #1
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	mov	r7, #5
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	mov	lr, #0
	bfi	r1, r2, #0, #2
	mov	r8, #10
	and	r3, r3, #252
	and	r1, r1, #227
	orr	r3, r3, #12
	bfi	r1, r7, #5, #3
	bfi	r3, ip, #4, #2
	strb	r1, [r4, #64]
	strb	r3, [r4, #65]
	and	r2, r2, #3
	ldr	r3, [r4, #64]
	mov	r7, #8
	mov	r1, lr
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	ldrb	r9, [r5, #223]	@ zero_extendqisi2
	mov	r3, r3, lsr #16
	bfi	r3, r9, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #224]
	str	r2, [r4, #56]
	str	r2, [r4, #60]
	str	r3, [r4, #120]
	strb	ip, [r4, #291]
	strb	ip, [r4, #289]
	strb	lr, [r4, #284]
	str	r8, [r4, #296]
	str	r7, [r4, #300]
	str	r7, [r4, #308]
	str	r7, [r4, #304]
	bl	SetAspectRatio
	ldr	r2, [r5, #248]
	mov	r2, r2, asl #4
	str	r2, [r4, #68]
	ldr	r3, [r5, #244]
	mov	r3, r3, asl #4
	str	r3, [r4, #72]
	ldr	r1, [r6]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L550
.L546:
	str	r2, [r4, #76]
	mov	r2, r2, lsr #1
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r2, [r4, #84]
	str	r3, [r4, #88]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L550:
	ldr	lr, [r4, #112]
	mov	ip, r3, lsr #4
	ldr	r5, [r4, #36]
	add	r7, r4, #512
	mov	r1, lr, asl #4
	add	r8, r5, lr
	mul	ip, ip, r1
	add	r6, ip, r5
	str	r6, [r4, #40]
	ldrd	r0, [r7, #-8]
	add	lr, r6, lr
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r7]
	str	r6, [r4, #24]
	str	lr, [r4, #32]
	str	r8, [r4, #28]
	str	r5, [r4, #20]
	b	.L546
	UNWIND(.fnend)
	.size	VP6_SetImgFormat, .-VP6_SetImgFormat
	.align	2
	.global	VP6DEC_VDMPostProc
	.type	VP6DEC_VDMPostProc, %function
VP6DEC_VDMPostProc:
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
	mov	r6, r0
	mov	r2, r1
	mov	r5, r1
	mov	r0, #22
	ldr	r1, .L587
	bl	dprint_vfmw
	ldr	r3, [r6, #4]
	add	r4, r6, #12288
	mov	r1, r6
	mov	r0, #10
	ldrb	r2, [r3, #52]	@ zero_extendqisi2
	strb	r2, [r4, #223]
	ldr	r3, [r3, #212]
	str	r3, [r4, #224]
	bl	ReleasePacket
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L580
	cmp	r5, #0
	blt	.L554
	cmp	r5, #100
	movlt	r2, r5
	movge	r2, #100
	str	r2, [r7, #152]
	ldr	r3, [r6]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L581
.L555:
	mov	r0, r6
	bl	VP6_SetImgFormat
	ldr	r3, [r4, #24]
	mov	r2, #1
	str	r2, [r4, #28]
	cmp	r3, #2
	beq	.L582
.L556:
	ldr	r1, [r4, #44]
	str	r1, [r4, #56]
.L557:
	cmn	r1, #1
	beq	.L558
	mov	r2, #1
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L583
	add	r3, r6, #12672
	ldr	r0, [r4, #752]
	add	r3, r3, #16
	str	r7, [sp]
	mov	r2, r6
	mov	r1, #10
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r5, r0
	bne	.L584
.L558:
	ldr	r3, [r4, #52]
	ldr	r2, [r4, #48]
	cmp	r3, r2
	beq	.L560
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L561
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldr	r1, [r4, #44]
.L561:
	str	r1, [r4, #52]
	mov	r2, #1
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L585
	ldr	r3, [r4, #48]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L564
.L586:
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldr	r1, [r4, #44]
.L564:
	ldr	r0, [r4, #752]
	mov	r2, #1
	str	r1, [r4, #48]
	bl	FSP_SetRef
	mov	r0, #1
.L578:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L585:
	ldr	r3, [r4, #40]
	cmp	r3, #0
	moveq	r0, #1
	beq	.L578
	ldr	r3, [r4, #48]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	bne	.L586
	b	.L564
.L554:
	mov	r3, #0
	str	r3, [r7, #152]
	b	.L555
.L582:
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L556
	mvn	r3, #0
	ldr	r1, [r4, #44]
	mov	r2, #0
	str	r3, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, [r4, #56]
	b	.L557
.L584:
	mov	r2, #0
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	add	r10, r7, #544
	bl	FSP_SetRef
	add	r6, r7, #560
	ldr	r1, [r7, #544]
	mov	r8, #0
	ldr	r0, [r4, #752]
	mov	r9, #0
	bl	FreeUsdByDec
	strd	r8, [r10]
	ldr	r1, [r7, #552]
	ldr	r0, [r4, #752]
	bl	FreeUsdByDec
	strd	r8, [r6, #-8]
	mov	r2, #0
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, .L587+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L560:
	mov	r1, r3
	ldr	r0, [r4, #752]
	bl	FSP_GetRef
	subs	r2, r0, #0
	bne	.L579
	ldr	r3, [r4, #52]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L561
	mov	r1, r3
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
.L579:
	ldr	r1, [r4, #44]
	b	.L561
.L581:
	ldr	r1, .L587+8
	mov	r0, #1
	bl	dprint_vfmw
	add	r5, r7, #544
	mov	r2, #0
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	add	r6, r7, #560
	bl	FSP_SetRef
	ldr	r1, [r7, #544]
	ldr	r0, [r4, #752]
	mov	r8, #0
	bl	FreeUsdByDec
	mov	r9, #0
	strd	r8, [r5]
	mov	r5, #0
	ldr	r1, [r7, #552]
	ldr	r0, [r4, #752]
	bl	FreeUsdByDec
	strd	r8, [r6, #-8]
	mov	r2, r5
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	mov	r2, #1
	ldr	r1, [r4, #48]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #28]
	mov	r3, r0
	mvn	r0, #0
	str	r3, [r4, #52]
	str	r3, [r4, #48]
	b	.L578
.L583:
	mov	r2, r7
	ldr	r1, .L587+12
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L578
.L580:
	ldr	r1, .L587+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L578
.L588:
	.align	2
.L587:
	.word	.LC42
	.word	.LC46
	.word	.LC44
	.word	.LC45
	.word	.LC43
	UNWIND(.fnend)
	.size	VP6DEC_VDMPostProc, .-VP6DEC_VDMPostProc
	.align	2
	.global	VP6DEC_RecycleImage
	.type	VP6DEC_RecycleImage, %function
VP6DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r4, r0, #12288
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L592
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #752]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #752]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L592:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6DEC_RecycleImage, .-VP6DEC_RecycleImage
	.align	2
	.global	VP6DEC_GetRemainImg
	.type	VP6DEC_GetRemainImg, %function
VP6DEC_GetRemainImg:
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
	add	r0, r0, #12672
	add	r0, r0, #16
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetVoLastImageID
	UNWIND(.fnend)
	.size	VP6DEC_GetRemainImg, .-VP6DEC_GetRemainImg
	.global	DefaultScanBands
	.global	ZrlUpdateProbs
	.global	ScanBandUpdateProbs
	.global	ZeroRunProbDefaults
	.global	VP6_AcUpdateProbs
	.global	VP6_DcUpdateProbs
	.global	DefaultSignProbs
	.global	DefaultIsShortProbs
	.global	DefaultMvLongProbs
	.global	DefaultMvShortProbs
	.global	VP6_MvUpdateProbs
	.global	VP6_BaselineXmittedProbs
	.global	VP6_ModeVq
	.global	VP6_DcNodeEqs
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	VP6_DcNodeEqs, %object
	.size	VP6_DcNodeEqs, 120
VP6_DcNodeEqs:
	.word	122
	.word	133
	.word	133
	.word	51
	.word	142
	.word	-16
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	78
	.word	171
	.word	169
	.word	71
	.word	221
	.word	-30
	.word	139
	.word	117
	.word	214
	.word	44
	.word	246
	.word	-3
	.word	168
	.word	79
	.word	210
	.word	38
	.word	203
	.word	17
	.type	VP6_DcUpdateProbs, %object
	.size	VP6_DcUpdateProbs, 22
VP6_DcUpdateProbs:
	.byte	-110
	.byte	-1
	.byte	-75
	.byte	-49
	.byte	-24
	.byte	-13
	.byte	-18
	.byte	-5
	.byte	-12
	.byte	-6
	.byte	-7
	.byte	-77
	.byte	-1
	.byte	-42
	.byte	-16
	.byte	-6
	.byte	-1
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.space	2
	.type	ZeroRunProbDefaults, %object
	.size	ZeroRunProbDefaults, 28
ZeroRunProbDefaults:
	.byte	-58
	.byte	-59
	.byte	-60
	.byte	-110
	.byte	-58
	.byte	-52
	.byte	-87
	.byte	-114
	.byte	-126
	.byte	-120
	.byte	-107
	.byte	-107
	.byte	-65
	.byte	-7
	.byte	-121
	.byte	-55
	.byte	-75
	.byte	-102
	.byte	98
	.byte	117
	.byte	-124
	.byte	126
	.byte	-110
	.byte	-87
	.byte	-72
	.byte	-16
	.byte	-10
	.byte	-2
	.type	ZrlUpdateProbs, %object
	.size	ZrlUpdateProbs, 28
ZrlUpdateProbs:
	.byte	-37
	.byte	-10
	.byte	-18
	.byte	-7
	.byte	-24
	.byte	-17
	.byte	-7
	.byte	-1
	.byte	-8
	.byte	-3
	.byte	-17
	.byte	-12
	.byte	-15
	.byte	-8
	.byte	-58
	.byte	-24
	.byte	-5
	.byte	-3
	.byte	-37
	.byte	-15
	.byte	-3
	.byte	-1
	.byte	-8
	.byte	-7
	.byte	-12
	.byte	-18
	.byte	-5
	.byte	-1
	.type	VP6_AcUpdateProbs, %object
	.size	VP6_AcUpdateProbs, 396
VP6_AcUpdateProbs:
	.byte	-29
	.byte	-10
	.byte	-26
	.byte	-9
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-47
	.byte	-25
	.byte	-25
	.byte	-7
	.byte	-7
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-14
	.byte	-15
	.byte	-5
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-15
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-50
	.byte	-53
	.byte	-29
	.byte	-17
	.byte	-9
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-49
	.byte	-57
	.byte	-36
	.byte	-20
	.byte	-13
	.byte	-4
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-44
	.byte	-37
	.byte	-26
	.byte	-13
	.byte	-12
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-20
	.byte	-19
	.byte	-9
	.byte	-4
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-16
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-26
	.byte	-23
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-18
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-5
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-17
	.byte	-29
	.byte	-25
	.byte	-12
	.byte	-3
	.byte	-13
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-24
	.byte	-22
	.byte	-32
	.byte	-28
	.byte	-14
	.byte	-7
	.byte	-14
	.byte	-4
	.byte	-5
	.byte	-5
	.byte	-1
	.byte	-21
	.byte	-7
	.byte	-18
	.byte	-16
	.byte	-5
	.byte	-1
	.byte	-7
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-7
	.byte	-3
	.byte	-5
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-6
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-13
	.byte	-12
	.byte	-6
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-8
	.byte	-6
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	ScanBandUpdateProbs, %object
	.size	ScanBandUpdateProbs, 64
ScanBandUpdateProbs:
	.byte	-1
	.byte	-124
	.byte	-124
	.byte	-97
	.byte	-103
	.byte	-105
	.byte	-95
	.byte	-86
	.byte	-92
	.byte	-94
	.byte	-120
	.byte	110
	.byte	103
	.byte	114
	.byte	-127
	.byte	118
	.byte	124
	.byte	125
	.byte	-124
	.byte	-120
	.byte	114
	.byte	110
	.byte	-114
	.byte	-121
	.byte	-122
	.byte	123
	.byte	-113
	.byte	126
	.byte	-103
	.byte	-73
	.byte	-90
	.byte	-95
	.byte	-85
	.byte	-76
	.byte	-77
	.byte	-92
	.byte	-53
	.byte	-38
	.byte	-31
	.byte	-39
	.byte	-41
	.byte	-50
	.byte	-53
	.byte	-39
	.byte	-27
	.byte	-15
	.byte	-8
	.byte	-13
	.byte	-3
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	VP6_ModeVq, %object
	.size	VP6_ModeVq, 960
VP6_ModeVq:
	.byte	9
	.byte	15
	.byte	32
	.byte	25
	.byte	7
	.byte	19
	.byte	9
	.byte	21
	.byte	1
	.byte	12
	.byte	14
	.byte	12
	.byte	3
	.byte	18
	.byte	14
	.byte	23
	.byte	3
	.byte	10
	.byte	0
	.byte	4
	.byte	48
	.byte	39
	.byte	1
	.byte	2
	.byte	11
	.byte	27
	.byte	29
	.byte	44
	.byte	7
	.byte	27
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	21
	.byte	32
	.byte	1
	.byte	2
	.byte	4
	.byte	10
	.byte	32
	.byte	43
	.byte	6
	.byte	23
	.byte	2
	.byte	3
	.byte	1
	.byte	19
	.byte	1
	.byte	6
	.byte	12
	.byte	21
	.byte	0
	.byte	7
	.byte	69
	.byte	83
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	10
	.byte	29
	.byte	3
	.byte	12
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	20
	.byte	1
	.byte	4
	.byte	18
	.byte	36
	.byte	43
	.byte	48
	.byte	13
	.byte	35
	.byte	0
	.byte	2
	.byte	0
	.byte	5
	.byte	3
	.byte	12
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	70
	.byte	44
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	37
	.byte	46
	.byte	8
	.byte	26
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	15
	.byte	0
	.byte	1
	.byte	8
	.byte	21
	.byte	74
	.byte	53
	.byte	22
	.byte	42
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	-115
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	11
	.byte	24
	.byte	1
	.byte	11
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	19
	.byte	4
	.byte	10
	.byte	24
	.byte	45
	.byte	21
	.byte	37
	.byte	9
	.byte	29
	.byte	0
	.byte	3
	.byte	1
	.byte	7
	.byte	11
	.byte	25
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	46
	.byte	42
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	54
	.byte	51
	.byte	10
	.byte	30
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	28
	.byte	32
	.byte	0
	.byte	0
	.byte	3
	.byte	10
	.byte	75
	.byte	51
	.byte	14
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	100
	.byte	46
	.byte	0
	.byte	1
	.byte	3
	.byte	9
	.byte	21
	.byte	37
	.byte	5
	.byte	20
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	1
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	27
	.byte	29
	.byte	0
	.byte	1
	.byte	9
	.byte	25
	.byte	53
	.byte	51
	.byte	12
	.byte	34
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	80
	.byte	38
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	69
	.byte	33
	.byte	5
	.byte	16
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	16
	.byte	20
	.byte	0
	.byte	0
	.byte	2
	.byte	8
	.byte	104
	.byte	49
	.byte	15
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-62
	.byte	16
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	9
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	41
	.byte	22
	.byte	1
	.byte	0
	.byte	1
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	98
	.byte	25
	.byte	4
	.byte	10
	.byte	123
	.byte	37
	.byte	6
	.byte	4
	.byte	1
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	12
	.byte	10
	.byte	0
	.byte	2
	.byte	26
	.byte	14
	.byte	14
	.byte	12
	.byte	0
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	55
	.byte	17
	.byte	1
	.byte	9
	.byte	0
	.byte	36
	.byte	5
	.byte	7
	.byte	1
	.byte	3
	.byte	-47
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	5
	.byte	4
	.byte	5
	.byte	0
	.byte	121
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	4
	.byte	1
	.byte	4
	.byte	2
	.byte	2
	.byte	0
	.byte	1
	.byte	-81
	.byte	5
	.byte	0
	.byte	1
	.byte	0
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	2
	.byte	3
	.byte	0
	.byte	102
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-23
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	34
	.byte	16
	.byte	112
	.byte	21
	.byte	1
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	2
	.byte	5
	.byte	0
	.byte	2
	.byte	-97
	.byte	35
	.byte	2
	.byte	2
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	5
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	75
	.byte	39
	.byte	5
	.byte	7
	.byte	2
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	11
	.byte	2
	.byte	16
	.byte	1
	.byte	4
	.byte	7
	.byte	10
	.byte	0
	.byte	2
	.byte	-44
	.byte	21
	.byte	0
	.byte	1
	.byte	0
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	4
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-84
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	22
	.byte	1
	.byte	1
	.byte	0
	.byte	17
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	-123
	.byte	6
	.byte	1
	.byte	2
	.byte	1
	.byte	70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-5
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	4
	.byte	1
	.byte	4
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	0
	.byte	4
	.byte	49
	.byte	46
	.byte	3
	.byte	4
	.byte	7
	.byte	31
	.byte	42
	.byte	41
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	1
	.byte	7
	.byte	1
	.byte	4
	.byte	2
	.byte	4
	.byte	0
	.byte	1
	.byte	26
	.byte	25
	.byte	1
	.byte	1
	.byte	2
	.byte	10
	.byte	67
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	0
	.byte	14
	.byte	0
	.byte	2
	.byte	31
	.byte	26
	.byte	1
	.byte	6
	.byte	103
	.byte	46
	.byte	1
	.byte	2
	.byte	2
	.byte	10
	.byte	33
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	14
	.byte	31
	.byte	9
	.byte	13
	.byte	14
	.byte	54
	.byte	22
	.byte	29
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	4
	.byte	18
	.byte	6
	.byte	13
	.byte	1
	.byte	5
	.byte	0
	.byte	1
	.byte	85
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	9
	.byte	69
	.byte	40
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	0
	.byte	31
	.byte	28
	.byte	0
	.byte	0
	.byte	3
	.byte	14
	.byte	-126
	.byte	34
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	3
	.byte	3
	.byte	0
	.byte	1
	.byte	-85
	.byte	25
	.byte	0
	.byte	0
	.byte	1
	.byte	5
	.byte	25
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	17
	.byte	21
	.byte	68
	.byte	29
	.byte	6
	.byte	15
	.byte	13
	.byte	22
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	3
	.byte	14
	.byte	4
	.byte	10
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	51
	.byte	39
	.byte	0
	.byte	1
	.byte	2
	.byte	12
	.byte	91
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	1
	.byte	81
	.byte	25
	.byte	0
	.byte	0
	.byte	2
	.byte	9
	.byte	106
	.byte	26
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-116
	.byte	37
	.byte	0
	.byte	1
	.byte	1
	.byte	8
	.byte	24
	.byte	33
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	14
	.byte	23
	.byte	1
	.byte	3
	.byte	11
	.byte	53
	.byte	90
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	2
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	123
	.byte	29
	.byte	0
	.byte	0
	.byte	1
	.byte	7
	.byte	57
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	13
	.byte	14
	.byte	0
	.byte	0
	.byte	4
	.byte	20
	.byte	-81
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-54
	.byte	23
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	2
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	VP6_MvUpdateProbs, %object
	.size	VP6_MvUpdateProbs, 34
VP6_MvUpdateProbs:
	.byte	-19
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-6
	.byte	-6
	.byte	-4
	.byte	-25
	.byte	-13
	.byte	-11
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-5
	.byte	-5
	.byte	-2
	.space	2
	.type	VP6_LoopFilterLimitValues, %object
	.size	VP6_LoopFilterLimitValues, 64
VP6_LoopFilterLimitValues:
	.byte	14
	.byte	14
	.byte	13
	.byte	13
	.byte	12
	.byte	12
	.byte	10
	.byte	10
	.byte	10
	.byte	10
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.type	DcQuantTab, %object
	.size	DcQuantTab, 128
DcQuantTab:
	.short	188
	.short	188
	.short	188
	.short	188
	.short	180
	.short	172
	.short	172
	.short	172
	.short	172
	.short	172
	.short	168
	.short	164
	.short	164
	.short	160
	.short	160
	.short	160
	.short	160
	.short	140
	.short	140
	.short	140
	.short	140
	.short	132
	.short	132
	.short	132
	.short	132
	.short	128
	.short	128
	.short	128
	.short	108
	.short	108
	.short	104
	.short	104
	.short	100
	.short	100
	.short	96
	.short	96
	.short	92
	.short	92
	.short	76
	.short	76
	.short	76
	.short	76
	.short	72
	.short	72
	.short	68
	.short	64
	.short	64
	.short	64
	.short	64
	.short	64
	.short	60
	.short	44
	.short	44
	.short	44
	.short	40
	.short	40
	.short	36
	.short	32
	.short	28
	.short	20
	.short	12
	.short	12
	.short	8
	.short	8
	.type	AcQuantTab, %object
	.size	AcQuantTab, 128
AcQuantTab:
	.short	376
	.short	368
	.short	360
	.short	352
	.short	344
	.short	328
	.short	312
	.short	296
	.short	280
	.short	264
	.short	248
	.short	232
	.short	216
	.short	212
	.short	208
	.short	204
	.short	200
	.short	196
	.short	192
	.short	188
	.short	184
	.short	180
	.short	176
	.short	172
	.short	168
	.short	160
	.short	156
	.short	148
	.short	144
	.short	140
	.short	136
	.short	132
	.short	128
	.short	124
	.short	120
	.short	116
	.short	112
	.short	108
	.short	104
	.short	100
	.short	96
	.short	92
	.short	88
	.short	84
	.short	80
	.short	76
	.short	72
	.short	68
	.short	64
	.short	60
	.short	56
	.short	52
	.short	48
	.short	44
	.short	40
	.short	36
	.short	32
	.short	28
	.short	24
	.short	20
	.short	16
	.short	12
	.short	8
	.short	4
	.type	__FUNCTION__.14408, %object
	.size	__FUNCTION__.14408, 17
__FUNCTION__.14408:
	.ascii	"VP6_DecodeDecide\000"
	.space	3
	.type	VP6_BaselineXmittedProbs, %object
	.size	VP6_BaselineXmittedProbs, 80
VP6_BaselineXmittedProbs:
	.byte	42
	.byte	2
	.byte	7
	.byte	42
	.byte	22
	.byte	3
	.byte	2
	.byte	5
	.byte	1
	.byte	0
	.byte	69
	.byte	1
	.byte	1
	.byte	44
	.byte	6
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	1
	.byte	8
	.byte	0
	.byte	0
	.byte	2
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	-27
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	35
	.byte	1
	.byte	6
	.byte	34
	.byte	0
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	122
	.byte	1
	.byte	1
	.byte	46
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	DefaultIsShortProbs, %object
	.size	DefaultIsShortProbs, 2
DefaultIsShortProbs:
	.byte	-94
	.byte	-92
	.space	2
	.type	DefaultMvShortProbs, %object
	.size	DefaultMvShortProbs, 14
DefaultMvShortProbs:
	.byte	-31
	.byte	-110
	.byte	-84
	.byte	-109
	.byte	-42
	.byte	39
	.byte	-100
	.byte	-52
	.byte	-86
	.byte	119
	.byte	-21
	.byte	-116
	.byte	-26
	.byte	-28
	.space	2
	.type	DefaultSignProbs, %object
	.size	DefaultSignProbs, 2
DefaultSignProbs:
	.byte	-128
	.byte	-128
	.space	2
	.type	DefaultMvLongProbs, %object
	.size	DefaultMvLongProbs, 16
DefaultMvLongProbs:
	.byte	-9
	.byte	-46
	.byte	-121
	.byte	68
	.byte	-118
	.byte	-36
	.byte	-17
	.byte	-10
	.byte	-12
	.byte	-72
	.byte	-55
	.byte	44
	.byte	-83
	.byte	-35
	.byte	-17
	.byte	-3
	.type	DefaultScanBands, %object
	.size	DefaultScanBands, 64
DefaultScanBands:
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	3
	.byte	3
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	6
	.byte	6
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	8
	.byte	8
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	10
	.byte	10
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	14
	.byte	14
	.byte	14
	.byte	14
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"image_size_in_mb abnormal(%d x %d)\012\000" )
.LC1:
	ASCII(.ascii	"vp6 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"enter VP6_ConvertBoolToHuff\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"leave VP6_ConvertBoolToHuff\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"enter VP6_IntraFrmHeader\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"error: Vp3VersionNo %d > CURRENT_DECODE_VERSION(8)\012" )
	ASCII(.ascii	"\000" )
.LC12:
	ASCII(.ascii	"error: bitstream error!\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"We have a new size image!\012 The old size is %d x " )
	ASCII(.ascii	"%d, and the new is %d x %d\012\000" )
.LC14:
	ASCII(.ascii	"leave VP6_IntraFrmHeader\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"VP6_InterFrmHeader VersionNo fault,old:%d,new:%d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC16:
	ASCII(.ascii	"[ERR]VP6_GetPictureHeader invalid param!\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"VP6_GetPictureHeader enter!\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"VP6_GetPictureHeader leave!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC20:
	ASCII(.ascii	"VP6DEC_Init leave\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"----------------- vp6 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"-----I_MODE, but FrameType is %d-----\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"P-frm\000" )
	.space	2
.LC25:
	ASCII(.ascii	"-----cur framtype is %s, but refnum=%d-----\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"error: DecMode illegal\012\000" )
.LC27:
	ASCII(.ascii	"%s %d NULL == pFwdImg!!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC29:
	ASCII(.ascii	"VP6_Set_DecParam but logic fs is null!\012\000" )
.LC30:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC31:
	ASCII(.ascii	"Error! Truncated packet\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"[ERR]VP6_GetPictureHeader Error!\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"[ERR] VP6_DecodeDecide Error!\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC35:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC36:
	ASCII(.ascii	"VP6_ArrangeVHBMem err\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"VP6_DecodeDecide err\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"VP6DEC_GetImageBuffer err\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"VP6_PrePare_decode Error!\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"leave VP6DEC_Decode\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC45:
	ASCII(.ascii	"line: %d pToQueImg is null!\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
