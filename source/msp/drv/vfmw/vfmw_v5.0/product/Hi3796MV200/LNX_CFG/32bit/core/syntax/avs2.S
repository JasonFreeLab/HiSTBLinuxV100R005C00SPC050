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
	.file	"avs2.c"
	.text
	.align	2
	.type	AVS2_ue_v.isra.2, %function
AVS2_ue_v.isra.2:
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
	bls	.L5
	movw	r3, #61166
	mov	r2, r0
	movt	r3, 65535
	ldr	r1, .L6
	mov	r0, #1
	bl	dprint_vfmw
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5:
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
.L7:
	.align	2
.L6:
	.word	.LC0
	UNWIND(.fnend)
	.size	AVS2_ue_v.isra.2, .-AVS2_ue_v.isra.2
	.align	2
	.type	AVS2_se_v.isra.3, %function
AVS2_se_v.isra.3:
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
	bls	.L13
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L13:
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
	.size	AVS2_se_v.isra.3, .-AVS2_se_v.isra.3
	.align	2
	.type	AVS2_UpdateSceneBuf.part.7, %function
AVS2_UpdateSceneBuf.part.7:
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
	add	r4, r0, #18432
	add	r5, r0, #20224
	mov	r6, r0
	add	r4, r4, #144
	add	r5, r5, #16
	add	r7, r0, #8192
	b	.L18
.L16:
	add	r4, r4, #104
	cmp	r4, r5
	beq	.L23
.L18:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	sub	r3, r3, #5
	cmp	r3, #1
	bhi	.L16
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	tst	r3, #2
	and	r2, r3, #1
	beq	.L16
	ldr	r3, [r7, #2416]
	cmp	r3, r4
	beq	.L16
	cmp	r2, #0
	strb	r2, [r4, #6]
	bne	.L16
	strb	r2, [r4, #5]
	add	r4, r4, #104
	ldr	r1, [r4, #-48]
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	cmp	r4, r5
	bne	.L18
.L23:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_UpdateSceneBuf.part.7, .-AVS2_UpdateSceneBuf.part.7
	.align	2
	.global	AVS2_SkipToNextStartCode
	.type	AVS2_SkipToNextStartCode, %function
AVS2_SkipToNextStartCode:
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
	mov	r5, r0
	bl	BsToNextByte
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L27
	b	.L28
.L33:
	bl	BsSkip
	cmp	r4, r6
	beq	.L28
.L27:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L33
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L28:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SkipToNextStartCode, .-AVS2_SkipToNextStartCode
	.align	2
	.global	AVS2_DumpDpbStatus
	.type	AVS2_DumpDpbStatus, %function
AVS2_DumpDpbStatus:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r4, r0
	mov	r6, r1
	mov	r0, #32
	ldr	r1, .L43
	sub	r6, r6, #1
	bl	dprint_vfmw
	ldr	r1, .L43+4
	mov	r0, #32
	clz	r6, r6
	bl	dprint_vfmw
	add	r4, r4, #18432
	ldr	r7, .L43+8
	mov	r8, #0
	add	r4, r4, #150
	mov	r6, r6, lsr #5
	mov	r5, r8
.L37:
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	moveq	r3, r6
	orrne	r3, r6, #1
	cmp	r3, #0
	beq	.L35
	ldr	lr, [r4, #74]
	mov	r0, #32
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	add	r8, r8, #1
	ldr	r3, .L43+12
	str	lr, [sp, #28]
	cmp	r2, #6
	ldr	lr, [r4, #54]
	ldrls	r3, [r7, r2, asl #2]
	mov	r2, r5
	ldr	r1, .L43+16
	str	lr, [sp, #24]
	ldr	lr, [r4, #50]
	str	lr, [sp, #20]
	ldrsh	lr, [r4, #-4]
	str	lr, [sp, #16]
	ldrsh	lr, [r4, #-6]
	str	lr, [sp, #12]
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
.L35:
	add	r5, r5, #1
	add	r4, r4, #104
	cmp	r5, #16
	bne	.L37
	mov	r2, r8
	ldr	r1, .L43+20
	mov	r0, #32
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L44:
	.align	2
.L43:
	.word	.LC2
	.word	.LC3
	.word	.LANCHOR0
	.word	.LC1
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	AVS2_DumpDpbStatus, .-AVS2_DumpDpbStatus
	.align	2
	.global	AVS2_ClearPacket
	.type	AVS2_ClearPacket, %function
AVS2_ClearPacket:
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
	add	r4, r0, #16384
	mov	r5, r0
	ldr	r0, [r0, #4]
	ldr	r1, [r4, #2052]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #2038]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4, #2118]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #2124]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, [r4, #2132]
	ldr	r0, [r5, #4]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_ReleaseStreamSeg
	UNWIND(.fnend)
	.size	AVS2_ClearPacket, .-AVS2_ClearPacket
	.align	2
	.global	AVS2_ClearPicSlice
	.type	AVS2_ClearPicSlice, %function
AVS2_ClearPicSlice:
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
	ldr	r3, [r0, #1216]
	mov	r5, r0
	cmp	r3, #0
	movne	r6, r0
	movne	r4, #0
	bne	.L53
	b	.L54
.L52:
	ldr	r3, [r5, #1216]
	add	r6, r6, #36
	cmp	r3, r4
	bls	.L54
.L53:
	ldr	r1, [r6, #1248]
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	mov	r3, r4, asl #5
	add	r3, r3, r4, lsl #2
	add	r4, r4, #1
	add	r3, r5, r3
	add	r3, r3, #1216
	ldrh	r3, [r3, #28]
	cmp	r3, #256
	bne	.L52
	ldr	r3, [r6, #1232]
	cmp	r3, #0
	beq	.L52
	ldr	r1, [r6, #1252]
	add	r6, r6, #36
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r5, #1216]
	cmp	r3, r4
	bhi	.L53
.L54:
	mov	r3, #0
	str	r3, [r5, #1216]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ClearPicSlice, .-AVS2_ClearPicSlice
	.align	2
	.global	AVS2_ClearDpb
	.type	AVS2_ClearDpb, %function
AVS2_ClearDpb:
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
	add	r4, r0, #18432
	add	r5, r0, #20224
	mov	r6, r0
	add	r4, r4, #200
	add	r5, r5, #72
	mov	r7, #0
	b	.L62
.L61:
	add	r4, r4, #104
	cmp	r4, r5
	beq	.L67
.L62:
	ldrb	r3, [r4, #-50]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L61
	ldr	r1, [r4]
	mov	r2, #0
	ldr	r0, [r6, #4]
	add	r4, r4, #104
	bl	FSP_ClearLogicFs
	strb	r7, [r4, #-154]
	cmp	r4, r5
	bne	.L62
.L67:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ClearDpb, .-AVS2_ClearDpb
	.align	2
	.global	AVS2_SequenceDisplayExtension
	.type	AVS2_SequenceDisplayExtension, %function
AVS2_SequenceDisplayExtension:
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
	add	r5, r0, #44
	add	r4, r0, #16384
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #412]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #416]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #420]
	bne	.L74
.L69:
	mov	r1, #14
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #436]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r4, #440]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #444]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #448]
	beq	.L75
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L74:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #424]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #428]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #432]
	b	.L69
.L75:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #452]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #456]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SequenceDisplayExtension, .-AVS2_SequenceDisplayExtension
	.align	2
	.global	AVS2_CopyrightExtension
	.type	AVS2_CopyrightExtension, %function
AVS2_CopyrightExtension:
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
	add	r4, r0, #44
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #7
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #20
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_CopyrightExtension, .-AVS2_CopyrightExtension
	.align	2
	.global	AVS2_CameraParametersExtension
	.type	AVS2_CameraParametersExtension, %function
AVS2_CameraParametersExtension:
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
	add	r4, r0, #44
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #7
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_CameraParametersExtension, .-AVS2_CameraParametersExtension
	.align	2
	.global	AVS2_TemporalScalabilityExtension
	.type	AVS2_TemporalScalabilityExtension, %function
AVS2_TemporalScalabilityExtension:
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
	add	r5, r0, #44
	mov	r1, #4
	add	r7, r0, #16384
	mov	r4, r0
	mov	r0, r5
	bl	BsGet
	mov	r0, r5
	mov	r1, #3
	bl	BsGet
	cmp	r0, #0
	str	r0, [r7, #1532]
	beq	.L83
	add	r4, r4, #17664
	mov	r6, #0
	add	r4, r4, #252
.L80:
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #18
	add	r6, r6, #1
	str	r0, [r4, #4]!
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #28]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #60]
	ldr	r3, [r7, #1532]
	cmp	r3, r6
	bhi	.L80
.L83:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_TemporalScalabilityExtension, .-AVS2_TemporalScalabilityExtension
	.align	2
	.global	AVS2_PictureDisplayExtension
	.type	AVS2_PictureDisplayExtension, %function
AVS2_PictureDisplayExtension:
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
	add	r4, r0, #44
	add	r7, r0, #12288
	mov	r5, r0
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	ldr	r3, [r7, #2096]
	cmp	r3, #1
	add	r3, r5, #16384
	beq	.L101
	ldr	r2, [r3, #636]
	cmp	r2, #0
	bne	.L102
.L86:
	mov	r3, #1
	str	r3, [r7, #2084]
.L88:
	add	r5, r5, #17664
	mov	r6, #0
	add	r5, r5, #224
.L90:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	add	r6, r6, r1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	ldr	r3, [r7, #2084]
	cmp	r6, r3
	bcc	.L90
	mov	r0, r4
	bl	AVS2_SkipToNextStartCode
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L102:
	ldr	r3, [r3, #644]
	cmp	r3, #1
	beq	.L89
.L87:
	mov	r3, #2
	str	r3, [r7, #2084]
	b	.L88
.L101:
	ldr	r2, [r3, #644]
	cmp	r2, #1
	bne	.L86
	ldr	r3, [r3, #640]
	cmp	r3, #1
	bne	.L87
.L89:
	mov	r3, #3
	str	r3, [r7, #2084]
	b	.L88
	UNWIND(.fnend)
	.size	AVS2_PictureDisplayExtension, .-AVS2_PictureDisplayExtension
	.align	2
	.global	AVS2_MasteringMetadataExtension
	.type	AVS2_MasteringMetadataExtension, %function
AVS2_MasteringMetadataExtension:
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
	add	r4, r0, #44
	add	r5, r0, #17920
	mov	r6, r0
	mov	r1, #4
	mov	r0, r4
	mov	r7, r5
	bl	BsGet
	add	r5, r5, #92
	add	r7, r7, #104
.L104:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	cmp	r5, r7
	bne	.L104
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	add	r5, r6, #16384
	mov	r1, #1
	str	r0, [r5, #1656]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #1660]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #1664]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #1668]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #1672]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #1676]
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r3, #1
	mov	r0, r3
	str	r3, [r5, #1624]
	str	r3, [r5, #1628]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_MasteringMetadataExtension, .-AVS2_MasteringMetadataExtension
	.align	2
	.global	AVS2_Extension
	.type	AVS2_Extension, %function
AVS2_Extension:
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
	add	r4, r0, #44
	mov	r1, #32
	mov	r5, r0
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #4
	bl	BsShow
	sub	r0, r0, #2
	cmp	r0, #10
	ldrls	pc, [pc, r0, asl #2]
	b	.L107
.L109:
	.word	.L108
	.word	.L110
	.word	.L111
	.word	.L107
	.word	.L107
	.word	.L112
	.word	.L107
	.word	.L107
	.word	.L113
	.word	.L114
	.word	.L115
.L107:
	mov	r0, r4
	mov	r1, #4
	bl	BsSkip
.L115:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L114:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_CameraParametersExtension
.L108:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SequenceDisplayExtension
.L110:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_TemporalScalabilityExtension
.L111:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_CopyrightExtension
.L112:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_PictureDisplayExtension
.L113:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_MasteringMetadataExtension
	UNWIND(.fnend)
	.size	AVS2_Extension, .-AVS2_Extension
	.align	2
	.global	AVS2_User_Data
	.type	AVS2_User_Data, %function
AVS2_User_Data:
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
	add	r4, r0, #44
	mov	r5, r0
	ldr	r1, .L123
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #32
	bl	BsGet
	b	.L118
.L121:
	ldr	r3, [r5, #68]
	ldr	r2, [r5, #60]
	add	ip, r3, #8
	cmp	ip, r2, asl #3
	bhi	.L122
	bl	BsGet
.L118:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r4
	bne	.L121
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L122:
	str	r2, [sp]
	mov	r0, #1
	ldr	r2, .L123+4
	ldr	r1, .L123+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L124:
	.align	2
.L123:
	.word	.LC6
	.word	.LANCHOR0+28
	.word	.LC7
	UNWIND(.fnend)
	.size	AVS2_User_Data, .-AVS2_User_Data
	.align	2
	.global	AVS2_WriteSliceMsg
	.type	AVS2_WriteSliceMsg, %function
AVS2_WriteSliceMsg:
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
	ldr	r2, [r0, #1216]
	mov	r4, r0
	cmp	r2, #255
	bhi	.L131
	add	r6, r0, #44
	mov	r1, #24
	mov	r0, r6
	bl	BsSkip
	mov	r0, r6
	mov	r1, #8
	bl	BsGet
	cmp	r0, #143
	mov	r7, r0
	bhi	.L132
	add	r5, r4, #12288
	mov	r1, #144
	ldr	r2, [r5, #2164]
	ldr	r3, [r5, #2112]
	cmp	r3, r1, asl r2
	bhi	.L133
.L129:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	ldr	r2, [r5, #2164]
	ldr	r3, [r5, #2104]
	mov	r1, #255
	cmp	r3, r1, asl r2
	mov	r8, r0
	bhi	.L134
.L130:
	ldr	r2, [r4, #1216]
	add	r5, r5, #4480
	mov	r0, #1
	add	r9, r4, #16384
	add	r6, r2, r0
	mov	r3, r2, asl #5
	add	r3, r3, r2, lsl #2
	add	r3, r4, r3
	add	r2, r3, #1216
	mov	lr, r3
	mov	ip, r3
	strh	r8, [r2, #4]	@ movhi
	strh	r7, [r2, #6]	@ movhi
	ldrh	r2, [r5, #16]
	mla	r2, r2, r7, r8
	str	r2, [lr, #1224]!
	ldr	r2, [r9, #2044]
	str	r2, [lr, #4]
	ldr	r2, [r9, #2124]
	str	r2, [r3, #1232]
	ldr	r2, [r9, #2048]
	str	r2, [ip, #1236]!
	ldr	r2, [r9, #2128]
	str	r2, [ip, #4]
	ldrb	r2, [r9, #2038]	@ zero_extendqisi2
	strb	r2, [r3, #1244]
	ldrb	r2, [r9, #2118]	@ zero_extendqisi2
	strb	r2, [r3, #1245]
	ldr	r2, [r9, #2052]
	str	r2, [r3, #1248]
	ldr	r2, [r9, #2132]
	str	r2, [r3, #1252]
	ldr	r3, [r4, #12]
	str	r6, [r4, #1216]
	orr	r3, r3, #32768
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L131:
	mov	r3, #256
	ldr	r1, .L135
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L132:
	mov	r2, r0
	ldr	r1, .L135+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L134:
	mov	r0, r6
	mov	r1, #2
	bl	BsGet
	add	r8, r8, r0, lsl #8
	b	.L130
.L133:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	add	r7, r7, r0, lsl #7
	b	.L129
.L136:
	.align	2
.L135:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	AVS2_WriteSliceMsg, .-AVS2_WriteSliceMsg
	.align	2
	.global	AVS2_Head_GetRefConfigSet
	.type	AVS2_Head_GetRefConfigSet, %function
AVS2_Head_GetRefConfigSet:
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
	mov	r6, r1
	mov	r5, r0
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	str	r0, [r5]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #4]
	addne	r7, r5, #4
	movne	r4, #0
	beq	.L142
.L141:
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #4]
	cmp	r3, r4
	bhi	.L141
.L142:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #36]
	addne	r7, r5, #36
	movne	r4, #0
	beq	.L140
.L143:
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #36]
	cmp	r3, r4
	bhi	.L143
.L140:
	mov	r0, r6
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	AVS2_Head_GetRefConfigSet, .-AVS2_Head_GetRefConfigSet
	.align	2
	.global	AVS2_WeightQuantMatrix
	.type	AVS2_WeightQuantMatrix, %function
AVS2_WeightQuantMatrix:
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
	add	r8, r0, #16
	mov	r5, r0
	mov	r4, r1
	mov	r6, r2
.L148:
	add	r7, r5, #4
.L147:
	mov	r0, r6
	bl	AVS2_ue_v.isra.2
	strb	r0, [r5], #1
	cmp	r5, r7
	bne	.L147
	cmp	r5, r8
	bne	.L148
	add	r7, r4, #64
.L150:
	add	r5, r4, #8
.L149:
	mov	r0, r6
	bl	AVS2_ue_v.isra.2
	strb	r0, [r4], #1
	cmp	r4, r5
	bne	.L149
	cmp	r4, r7
	bne	.L150
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_WeightQuantMatrix, .-AVS2_WeightQuantMatrix
	.align	2
	.global	AVS2_SetupWqMatrix84DataIdx01
	.type	AVS2_SetupWqMatrix84DataIdx01, %function
AVS2_SetupWqMatrix84DataIdx01:
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
	ldr	r5, .L183
	mov	r4, r0
	mov	r2, #6
	sub	r0, fp, #36
	mov	r1, #0
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r3, [r4, #2716]
	cmp	r3, #0
	beq	.L181
	cmp	r3, #1
	beq	.L182
	cmp	r3, #2
	beq	.L177
.L179:
	add	r2, r4, #2480
	add	r2, r2, #5
.L157:
	ldr	r3, [r4, #2720]
	cmp	r3, #0
	beq	.L169
	cmp	r3, #1
	beq	.L170
	ldr	r0, .L183+4
	add	lr, r0, #64
	b	.L162
.L169:
	ldr	r0, .L183+8
	add	lr, r0, #64
.L162:
	add	r5, r4, #2496
	add	r5, r5, #5
.L163:
	add	ip, r2, #4
	mov	r1, lr
.L164:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	sub	r6, fp, #28
	add	r3, r6, r3
	ldrb	r3, [r3, #-8]	@ zero_extendqisi2
	strb	r3, [r2, #1]!
	cmp	ip, r2
	bne	.L164
	cmp	ip, r5
	add	lr, lr, #4
	mov	r2, ip
	bne	.L163
	mov	lr, #0
.L167:
	add	r2, lr, #2496
	add	r1, r0, lr
	mov	ip, r2
	add	r2, r2, #5
	add	ip, ip, #13
	add	r2, r4, r2
	add	ip, r4, ip
.L166:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	sub	r5, fp, #28
	add	r3, r5, r3
	ldrb	r3, [r3, #-8]	@ zero_extendqisi2
	strb	r3, [r2, #1]!
	cmp	ip, r2
	bne	.L166
	add	lr, lr, #8
	cmp	lr, #64
	bne	.L167
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L181:
	mov	r2, #6
	ldr	r3, [r5, #52]
	sub	r0, fp, #36
	ldr	r1, .L183+12
	blx	r3
	add	r2, r4, #2480
	add	r2, r2, #5
	b	.L157
.L182:
	add	r2, r4, #2464
	ldr	r0, .L183+16
	sub	r1, fp, #36
	mov	lr, r2
	add	r2, r2, #9
	add	lr, lr, #15
.L159:
	ldrb	ip, [r2, #1]!	@ zero_extendqisi2
	ldrb	r3, [r0], #1	@ zero_extendqisi2
	cmp	r2, lr
	add	r3, r3, ip
	strb	r3, [r1], #1
	bne	.L159
	b	.L179
.L177:
	add	r0, r4, #2464
	add	r2, r4, #2480
	ldr	ip, .L183+20
	add	r0, r0, #15
	add	r2, r2, #5
	sub	r3, fp, #36
.L161:
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	r1, [ip], #1	@ zero_extendqisi2
	cmp	r0, r2
	add	r1, r1, lr
	strb	r1, [r3], #1
	bne	.L161
	b	.L157
.L170:
	ldr	r0, .L183+24
	add	lr, r0, #64
	b	.L162
.L184:
	.align	2
.L183:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+204
	.word	.LANCHOR0+44
	.word	.LANCHOR0+284
	.word	.LANCHOR0+292
	.word	.LANCHOR0+300
	.word	.LANCHOR0+124
	UNWIND(.fnend)
	.size	AVS2_SetupWqMatrix84DataIdx01, .-AVS2_SetupWqMatrix84DataIdx01
	.align	2
	.global	AVS2_SetupWqMatrix84
	.type	AVS2_SetupWqMatrix84, %function
AVS2_SetupWqMatrix84:
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
	ldr	r3, [r0, #2696]
	mov	r4, r0
	cmp	r3, #0
	beq	.L190
	ldr	r3, [r0, #2700]
	cmp	r3, #0
	bne	.L187
	ldr	r3, [r0, #88]
	add	r0, r0, #2480
	ldr	r5, .L191
	add	r0, r0, #6
	cmp	r3, #0
	mov	r2, #16
	bne	.L188
	ldr	r3, [r5, #52]
	ldr	r1, .L191+4
	blx	r3
	add	r0, r4, #2496
	ldr	r3, [r5, #52]
	add	r0, r0, #6
	mov	r2, #64
	ldr	r1, .L191+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L187:
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SetupWqMatrix84DataIdx01
.L190:
	ldr	r5, .L191
	add	r0, r0, #2480
	mov	r2, #16
	mov	r1, #64
	add	r0, r0, #6
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #2496
	mov	r2, #64
	ldr	r3, [r5, #48]
	add	r0, r0, #6
	mov	r1, r2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L188:
	add	r1, r4, #108
	ldr	r3, [r5, #52]
	blx	r3
	add	r0, r4, #2496
	ldr	r3, [r5, #52]
	add	r0, r0, #6
	add	r1, r4, #124
	mov	r2, #64
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L192:
	.align	2
.L191:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+308
	.word	.LANCHOR0+324
	UNWIND(.fnend)
	.size	AVS2_SetupWqMatrix84, .-AVS2_SetupWqMatrix84
	.align	2
	.global	AVS2_ALF_ParameterSet
	.type	AVS2_ALF_ParameterSet, %function
AVS2_ALF_ParameterSet:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 608
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #612)
	sub	sp, sp, #612
	ldr	r6, [r0, #252]
	mov	r5, r0
	mov	r4, r1
	cmp	r6, #1
	beq	.L255
.L194:
	ldr	r3, [r5, #256]
	cmp	r3, #1
	beq	.L256
	ldr	r3, [r5, #260]
	cmp	r3, #1
	beq	.L225
.L227:
	mov	r0, #1
.L250:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L258:
	add	r2, r3, #1088
	cmp	r2, #2160
	bcs	.L220
	add	r3, r5, #904
	add	r0, r5, #936
	mov	r2, #64
.L221:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	sub	r2, r2, r1, asl #1
	bne	.L221
	ldr	r1, [r5, #260]
	ldr	r3, [r5, #940]
	cmp	r1, #1
	add	r2, r3, r2
	str	r2, [r5, #940]
	bne	.L227
.L225:
	mov	r0, r4
	mov	r7, r5
	bl	AVS2_se_v.isra.3
	mov	r6, #0
	mov	r3, r0
	str	r0, [r7, #944]!
	b	.L226
.L230:
	bl	AVS2_se_v.isra.3
	add	r6, r6, #1
	cmp	r6, #8
	mov	r3, r0
	str	r0, [r7, #4]!
	beq	.L257
.L226:
	add	r1, r3, #64
	mov	r0, r4
	cmp	r1, #127
	bls	.L230
	mov	r2, r6
	ldr	r1, .L262
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L256:
	mov	r0, r4
	mov	r7, r5
	bl	AVS2_se_v.isra.3
	mov	r6, #0
	mov	r3, r0
	str	r0, [r7, #908]!
	b	.L224
.L222:
	bl	AVS2_se_v.isra.3
	add	r6, r6, #1
	cmp	r6, #8
	mov	r3, r0
	str	r0, [r7, #4]!
	beq	.L258
.L224:
	add	r1, r3, #64
	mov	r0, r4
	cmp	r1, #127
	bls	.L222
	mov	r2, r6
	ldr	r1, .L262+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L255:
	mov	r0, r1
	bl	AVS2_ue_v.isra.2
	cmp	r0, #15
	str	r0, [r5, #264]
	bhi	.L195
	cmn	r0, #1
	beq	.L259
	add	r3, r5, #268
	sub	r7, fp, #624
	str	r6, [fp, #-644]
	mov	r8, #0
	mov	r6, r3
	str	r3, [fp, #-648]
.L209:
	cmp	r8, #0
	movle	r3, #0
	movgt	r3, #1
	cmp	r0, #15
	cmpne	r8, #0
	ble	.L199
	mov	r0, r4
	bl	AVS2_ue_v.isra.2
	sub	r3, r0, #1
	str	r0, [r6]
	cmp	r3, #14
	bhi	.L260
.L201:
	mov	r0, r4
	mov	r9, r7
	bl	AVS2_se_v.isra.3
	mov	r10, #0
	str	r6, [fp, #-640]
	mov	r3, r0
	str	r0, [r9, #4]!
	b	.L208
.L205:
	ldr	ip, [r6]
	cmp	ip, #63
	bhi	.L206
	bl	AVS2_se_v.isra.3
	add	r10, r10, #1
	cmp	r10, #8
	mov	r3, r0
	str	r0, [r9, #4]!
	beq	.L261
.L208:
	cmn	r3, #64
	mov	r0, r4
	bge	.L205
.L206:
	mov	r2, r10
	ldr	r1, .L262+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L199:
	cmp	r3, #0
	ldrne	r3, [fp, #-644]
	strne	r3, [r6]
	b	.L201
.L195:
	mov	r2, r0
	ldr	r1, .L262+12
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L260:
	mov	r2, r0
	ldr	r1, .L262+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L259:
	mov	r0, #0
	strb	r0, [fp, #-636]
.L210:
	sub	r2, fp, #636
	mov	r3, r0
	add	r0, r2, r0
	sub	r2, fp, #44
	add	r1, r2, r3
.L218:
	add	r3, r3, #1
	ldrb	r2, [r1, #-592]	@ zero_extendqisi2
	cmp	r3, #15
	strb	r2, [r0], #1
	ble	.L218
.L217:
	ldr	r6, .L262+20
	add	r7, r5, #332
	ldr	r9, .L262+24
	add	r8, r6, #16
.L219:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	sub	r1, fp, #44
	mov	r2, #36
	mov	r0, r7
	add	r3, r1, r3
	ldr	ip, [r9, #52]
	add	r7, r7, r2
	ldrb	r1, [r3, #-592]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	add	r1, r3, r1, lsl #2
	sub	r3, fp, #620
	add	r1, r3, r1
	blx	ip
	cmp	r6, r8
	bne	.L219
	b	.L194
.L257:
	add	r2, r3, #1088
	cmp	r2, #2160
	bcs	.L228
	add	r3, r5, #940
	add	r0, r5, #972
	mov	r2, #64
.L229:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	sub	r2, r2, r1, asl #1
	bne	.L229
	ldr	r3, [r5, #976]
	mov	r0, #1
	add	r2, r3, r2
	str	r2, [r5, #976]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L261:
	cmn	r3, #1088
	blt	.L203
	ldr	r2, [fp, #-640]
	add	r6, r6, #4
	ldr	r2, [r2]
	cmp	r2, #1072
	bcs	.L203
	add	r0, r7, #32
	mov	r3, r7
	mov	r1, #64
.L204:
	ldr	r2, [r3, #4]!
	cmp	r0, r3
	sub	r1, r1, r2, asl #1
	bne	.L204
	ldr	r0, [r5, #264]
	add	r8, r8, #1
	ldr	r3, [r7, #36]
	add	ip, r0, #1
	cmp	r8, ip
	add	r1, r3, r1
	str	r1, [r7, #36]!
	bcc	.L209
	cmp	ip, #1
	mov	r0, #0
	strb	r0, [fp, #-636]
	bls	.L210
	mov	r8, #1
	mov	lr, r0
.L211:
	ldr	r3, [fp, #-648]
	ldr	r7, [r3, #4]!
	cmp	r7, #1
	str	r3, [fp, #-648]
	subeq	r3, fp, #44
	addeq	r3, r3, lr
	beq	.L215
	sub	r1, fp, #44
	sub	r6, r7, #1
	mov	r3, lr
	mov	r2, #0
	add	r1, r1, lr
	b	.L216
.L212:
	ldrb	r0, [r1, #-592]	@ zero_extendqisi2
.L216:
	add	r2, r2, #1
	add	r3, r3, #1
	cmp	r2, r6
	strb	r0, [r1, #-591]
	uxtb	r3, r3
	sub	r1, fp, #44
	add	r1, r1, r3
	bne	.L212
	add	lr, lr, #1
	sub	r7, r7, #2
	sub	r3, fp, #44
	uxtab	lr, r7, lr
	uxtb	lr, lr
	add	r3, r3, lr
	ldrb	r0, [r3, #-592]	@ zero_extendqisi2
.L215:
	add	r8, r8, #1
	add	lr, lr, #1
	cmp	r8, ip
	add	r0, r0, #1
	uxtb	lr, lr
	strb	r0, [r3, #-591]
	subne	r3, fp, #44
	addne	r3, r3, lr
	ldrneb	r0, [r3, #-592]	@ zero_extendqisi2
	bne	.L211
.L213:
	cmp	lr, #15
	mov	r0, lr
	ble	.L210
	b	.L217
.L220:
	mov	r2, r3
	ldr	r1, .L262+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L203:
	mov	r2, r3
	ldr	r1, .L262+32
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L228:
	mov	r2, r3
	ldr	r1, .L262+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L250
.L263:
	.align	2
.L262:
	.word	.LC17
	.word	.LC15
	.word	.LC13
	.word	.LC10
	.word	.LC11
	.word	.LANCHOR0+387
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC12
	.word	.LC16
	UNWIND(.fnend)
	.size	AVS2_ALF_ParameterSet, .-AVS2_ALF_ParameterSet
	.global	__aeabi_uidiv
	.align	2
	.global	AVS2_DeriveMaxDpbNum
	.type	AVS2_DeriveMaxDpbNum, %function
AVS2_DeriveMaxDpbNum:
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
	ldr	r2, [r0, #4]
	mov	r5, r0
	cmp	r2, #34
	movls	r3, #15
	strlsb	r3, [r0, #2412]
	ldmlsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r0, #24]
	cmp	r2, #74
	ldr	r1, [r0, #16]
	add	r3, r3, #7
	movls	r0, #13369344
	add	r1, r1, #7
	bic	r3, r3, #7
	bic	r1, r1, #7
	mul	r4, r1, r3
	mov	r1, r4
	bls	.L272
	cmp	r2, #90
	movls	r0, #56623104
	movhi	r0, #213909504
.L272:
	bl	__aeabi_uidiv
	mov	r1, #57344
	movt	r1, 31
	cmp	r0, #16
	movcs	r0, #16
	sub	r3, r0, #1
	cmp	r4, r1
	uxtb	r3, r3
	movhi	r1, #6
	movls	r1, #7
	cmp	r1, r3
	movcc	r1, r3
	strb	r1, [r5, #2412]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_DeriveMaxDpbNum, .-AVS2_DeriveMaxDpbNum
	.align	2
	.global	AVS2_IntraPictureHeader
	.type	AVS2_IntraPictureHeader, %function
AVS2_IntraPictureHeader:
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
	ldr	r8, .L369
	ldr	r3, [r0, #12]
	add	r9, r0, #16640
	mov	r7, r0
	add	r5, r0, #44
	add	r9, r9, #204
	mov	r2, #16
	bic	r3, r3, #262144
	mov	r1, #0
	str	r3, [r7, #12]
	add	r0, r9, #268
	ldr	r3, [r8, #48]
	add	r4, r7, #16384
	blx	r3
	mov	r1, #32
	mov	r0, r5
	add	r6, r7, #12288
	bl	BsGet
	mov	r0, r5
	mov	r1, #32
	bl	BsGet
	str	r0, [r4, #556]
	ldr	r3, [r6, #2088]
	cmp	r3, #72
	beq	.L349
.L274:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #564]
	beq	.L350
.L275:
	ldr	r3, [r6, #2176]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #600]
	beq	.L351
.L278:
	mov	r3, #0
	str	r3, [r4, #604]
.L279:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #608]
	ldr	r3, [r6, #2156]
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [r4, #612]
	beq	.L352
.L281:
	ldr	r3, [r6, #2152]
	cmp	r3, #0
	bne	.L282
	ldr	r3, [r4, #600]
	cmp	r3, #0
	beq	.L283
	ldr	r3, [r4, #604]
	cmp	r3, #1
	beq	.L283
.L282:
	mov	r3, #0
	str	r3, [r4, #616]
.L284:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #620]
	beq	.L285
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	mov	r2, #68
	mov	r3, r0, asl #6
	str	r0, [r4, #624]
	add	r1, r3, r0, lsl #2
	ldr	r3, [r8, #52]
	add	r1, r7, r1
	add	r0, r9, #980
	add	r1, r1, #14592
	blx	r3
	ldr	r3, [r6, #2152]
	cmp	r3, #1
	beq	.L353
.L287:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #632]
	ldr	r3, [r6, #2096]
	cmp	r3, #1
	beq	.L354
	ldr	r3, [r6, #2100]
	cmp	r3, #1
	beq	.L355
	cmp	r0, #0
	beq	.L322
.L290:
	mov	r3, #1
	str	r3, [r4, #636]
.L293:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #640]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #644]
	ldr	r8, [r6, #2100]
	cmp	r8, #1
	movne	r3, #1
	strne	r3, [r4, #648]
	beq	.L356
.L295:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #652]
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #405]	@ zero_extendqisi2
	mov	r8, r8, asl #3
	sub	r8, r8, #1
	cmp	r8, r0
	str	r0, [r4, #656]
	bcc	.L357
.L296:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #668]
	beq	.L358
.L298:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #692]
	movne	r3, #0
	strne	r3, [r4, #696]
	strne	r3, [r4, #700]
	beq	.L359
.L304:
	mov	r8, #2
	strb	r8, [r4, #461]
	ldr	r3, [r6, #2168]
	cmp	r3, #0
	streq	r3, [r4, #688]
	streq	r3, [r4, #684]
	bne	.L360
.L345:
	ldr	r3, [r6, #2292]
	cmp	r3, #1
	beq	.L361
	mov	r3, #0
	str	r3, [r4, #712]
	str	r3, [r4, #716]
	str	r3, [r4, #720]
.L316:
	ldr	r3, [r4, #716]
	cmp	r3, #0
	beq	.L362
.L315:
	mov	r1, r5
	mov	r0, r9
	bl	AVS2_ALF_ParameterSet
	subs	r5, r0, #0
	beq	.L363
.L317:
	ldr	r3, [r4, #600]
	cmp	r3, #0
	bne	.L364
.L347:
	str	r3, [r4, #592]
.L320:
	add	r0, r7, #14336
	mov	r5, #1
	mov	r3, #0
	add	r0, r0, #36
	strb	r3, [r4, #460]
	str	r5, [r4, #596]
	bl	AVS2_SetupWqMatrix84
	ldr	r3, [r7, #12]
	mov	r0, r5
	orr	r3, r3, #262144
	str	r3, [r7, #12]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L361:
	add	r6, r7, #16896
	mov	r8, r6
	add	r6, r6, #196
	add	r8, r8, #208
.L314:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r6, r8
	bne	.L314
	ldr	r3, [r4, #712]
	cmp	r3, #0
	bne	.L315
	b	.L316
.L285:
	mov	r1, r5
	add	r0, r9, #980
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r6, #2152]
	cmp	r3, #1
	bne	.L287
.L353:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	str	r0, [r4, #628]
	b	.L287
.L364:
	ldr	r3, [r4, #604]
	cmp	r3, #1
	moveq	r3, #5
	streq	r3, [r4, #592]
	beq	.L320
	mov	r3, #6
	b	.L347
.L362:
	ldr	r3, [r4, #720]
	cmp	r3, #0
	beq	.L317
	b	.L315
.L283:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	cmp	r0, #63
	str	r0, [r4, #616]
	bls	.L284
	mov	r2, r0
	ldr	r1, .L369+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #63
	str	r3, [r4, #616]
	b	.L284
.L351:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #600]
	bne	.L278
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #604]
	b	.L279
.L360:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #684]
	streq	r0, [r4, #688]
	beq	.L345
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #688]
	beq	.L365
	cmp	r0, #2
	bne	.L345
	mov	r2, r5
	add	r1, r9, #30
	add	r0, r9, #14
	bl	AVS2_WeightQuantMatrix
	b	.L345
.L359:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #696]
	cmp	r3, #32
	bhi	.L366
.L303:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #700]
	cmp	r3, #32
	bls	.L304
	mov	r2, r0
	ldr	r1, .L369+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #700]
	b	.L304
.L358:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #672]
	streq	r0, [r4, #676]
	streq	r0, [r4, #680]
	beq	.L298
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #676]
	cmp	r3, #16
	bhi	.L367
.L300:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #680]
	cmp	r3, #16
	bls	.L298
	mov	r2, r0
	ldr	r1, .L369+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #680]
	b	.L298
.L357:
	mov	r2, r0
	str	r8, [sp]
	mov	r3, r8
	ldr	r1, .L369+16
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #656]
	b	.L296
.L355:
	cmp	r0, #0
	beq	.L322
.L289:
	ldr	r1, .L369+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #632]
.L322:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #636]
	b	.L293
.L354:
	str	r3, [r4, #632]
	ldr	r3, [r6, #2100]
	cmp	r3, #1
	bne	.L290
	b	.L289
.L363:
	ldr	r2, .L369+24
	mov	r0, #1
	ldr	r1, .L369+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L349:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #572]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #556]
	str	r0, [r4, #560]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #556]
	b	.L274
.L356:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #648]
	mov	r0, r5
	bl	BsGet
	b	.L295
.L352:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #612]
	b	.L281
.L350:
	mov	r1, #24
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #568]
	b	.L275
.L366:
	mov	r2, r0
	ldr	r1, .L369+32
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #696]
	b	.L303
.L367:
	mov	r2, r0
	ldr	r1, .L369+36
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #676]
	b	.L300
.L365:
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #704]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #704]
	cmp	r3, #1
	str	r0, [r4, #708]
	beq	.L368
.L308:
	cmp	r3, #2
	bne	.L345
	add	r8, r7, #16640
	mov	r10, r8
	add	r8, r8, #211
	add	r10, r10, #217
.L310:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L310
	b	.L345
.L368:
	add	r8, r7, #16640
	mov	r10, r8
	add	r8, r8, #205
	add	r10, r10, #211
.L309:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L309
	ldr	r3, [r4, #704]
	b	.L308
.L370:
	.align	2
.L369:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	.LC24
	.word	.LC22
	.word	.LC20
	.word	.LC19
	.word	.LANCHOR0+404
	.word	.LC25
	.word	.LC23
	.word	.LC21
	UNWIND(.fnend)
	.size	AVS2_IntraPictureHeader, .-AVS2_IntraPictureHeader
	.align	2
	.global	AVS2_InterPictureHeader
	.type	AVS2_InterPictureHeader, %function
AVS2_InterPictureHeader:
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
	ldr	r3, [r0, #12]
	add	r5, r0, #44
	mov	r7, r0
	bic	r3, r3, #262144
	mov	r1, #32
	str	r3, [r7, #12]
	mov	r0, r5
	bl	BsGet
	mov	r0, r5
	mov	r1, #32
	add	r4, r7, #16384
	bl	BsGet
	add	r6, r7, #12288
	str	r0, [r4, #556]
	ldr	r3, [r6, #2088]
	cmp	r3, #72
	beq	.L444
.L372:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #576]
	beq	.L445
	ldr	r3, [r6, #2176]
	cmp	r0, #1
	cmpeq	r3, #0
	movne	r0, #0
	moveq	r0, #1
	strne	r0, [r4, #580]
	beq	.L446
.L376:
	cmp	r3, #0
	mov	r3, #0
	str	r3, [r4, #584]
	beq	.L447
.L377:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #608]
	ldr	r3, [r6, #2156]
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [r4, #612]
	beq	.L448
.L379:
	ldr	r3, [r6, #2152]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #616]
	beq	.L449
.L381:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #620]
	bne	.L450
	add	r9, r7, #16640
	mov	r1, r5
	add	r9, r9, #204
	add	r0, r9, #980
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r6, #2152]
	cmp	r3, #1
	beq	.L451
.L384:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	subs	r3, r0, #1
	str	r0, [r4, #632]
	ldr	r2, [r6, #2096]
	movne	r3, #1
	cmp	r2, #1
	movne	r3, #0
	cmp	r3, #0
	beq	.L385
	ldr	r1, .L465
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r4, #632]
	ldr	r3, [r6, #2100]
	cmp	r3, #1
	beq	.L389
.L386:
	mov	r3, #1
	str	r3, [r4, #636]
.L390:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #640]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #644]
	ldr	r8, [r6, #2100]
	cmp	r8, #1
	beq	.L452
.L391:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #652]
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #405]	@ zero_extendqisi2
	mov	r8, r8, asl #3
	sub	r8, r8, #1
	cmp	r8, r0
	str	r0, [r4, #656]
	bcc	.L453
.L392:
	ldr	r3, [r4, #576]
	cmp	r3, #2
	bne	.L393
	ldr	r3, [r4, #636]
	cmp	r3, #1
	beq	.L394
.L393:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #664]
.L394:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #588]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #668]
	beq	.L454
.L396:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #692]
	movne	r3, #0
	strne	r3, [r4, #696]
	strne	r3, [r4, #700]
	beq	.L455
.L402:
	mov	r8, #2
	strb	r8, [r4, #461]
	ldr	r3, [r6, #2168]
	cmp	r3, #0
	streq	r3, [r4, #684]
	bne	.L456
.L424:
	ldr	r3, [r6, #2292]
	cmp	r3, #1
	beq	.L457
	mov	r3, #0
	str	r3, [r4, #712]
	str	r3, [r4, #716]
	str	r3, [r4, #720]
.L414:
	ldr	r3, [r4, #716]
	cmp	r3, #0
	bne	.L413
	ldr	r3, [r4, #720]
	cmp	r3, #0
	bne	.L413
.L415:
	ldr	r2, [r4, #576]
	cmp	r2, #1
	beq	.L458
	cmp	r2, #2
	beq	.L421
	cmp	r2, #3
	bne	.L426
.L421:
	ldrb	r3, [r4, #1444]	@ zero_extendqisi2
	str	r2, [r4, #592]
	strb	r3, [r4, #460]
	sub	r3, r3, #1
	cmp	r3, #6
	bhi	.L459
.L422:
	add	r0, r7, #14336
	mov	r3, #0
	add	r0, r0, #36
	str	r3, [r4, #596]
	bl	AVS2_SetupWqMatrix84
	ldr	r3, [r7, #12]
	mov	r5, #1
	orr	r3, r3, #262144
	mov	r0, r5
	str	r3, [r7, #12]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L450:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	ldr	r3, .L465+4
	add	r9, r7, #16640
	mov	r2, #68
	add	r9, r9, #204
	ldr	r3, [r3, #52]
	mov	r1, r0, asl #6
	str	r0, [r4, #624]
	add	r1, r1, r0, lsl #2
	add	r0, r9, #980
	add	r1, r7, r1
	add	r1, r1, #14592
	blx	r3
	ldr	r3, [r6, #2152]
	cmp	r3, #1
	bne	.L384
.L451:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	str	r0, [r4, #628]
	b	.L384
.L447:
	ldr	r3, [r4, #576]
	cmp	r3, #2
	beq	.L377
	ldr	r3, [r4, #580]
	cmp	r3, #0
	bne	.L377
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #584]
	b	.L377
.L457:
	add	r6, r7, #16896
	mov	r8, r6
	add	r6, r6, #196
	add	r8, r8, #208
.L412:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r6, r8
	bne	.L412
	ldr	r3, [r4, #712]
	cmp	r3, #0
	beq	.L414
.L413:
	mov	r1, r5
	mov	r0, r9
	bl	AVS2_ALF_ParameterSet
	subs	r5, r0, #0
	bne	.L415
	ldr	r2, .L465+8
	mov	r0, #1
	ldr	r1, .L465+12
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L458:
	ldr	r3, [r4, #580]
	cmp	r3, #0
	streq	r2, [r4, #592]
	strneb	r2, [r4, #460]
	ldreq	r3, [r4, #1444]
	movne	r3, #4
	strne	r3, [r4, #592]
	streqb	r3, [r4, #460]
.L426:
	ldrb	r3, [r4, #460]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #6
	bls	.L422
.L459:
	mov	r3, #7
	ldr	r2, .L465+8
	ldr	r1, .L465+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r5, #0
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L385:
	ldr	r3, [r6, #2100]
	cmp	r3, #1
	beq	.L460
	cmp	r0, #0
	bne	.L386
.L423:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #636]
	b	.L390
.L456:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #684]
	streq	r0, [r4, #688]
	beq	.L424
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #688]
	beq	.L461
	cmp	r0, #2
	bne	.L424
	mov	r2, r5
	add	r1, r9, #30
	add	r0, r9, #14
	bl	AVS2_WeightQuantMatrix
	b	.L424
.L455:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #696]
	cmp	r3, #32
	bhi	.L462
.L401:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #700]
	cmp	r3, #32
	bls	.L402
	mov	r2, r0
	ldr	r1, .L465+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #700]
	b	.L402
.L449:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	cmp	r0, #63
	str	r0, [r4, #616]
	bls	.L381
	mov	r2, r0
	ldr	r1, .L465+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #63
	str	r3, [r4, #616]
	b	.L381
.L454:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #672]
	streq	r0, [r4, #676]
	streq	r0, [r4, #680]
	beq	.L396
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #676]
	cmp	r3, #16
	bhi	.L463
.L398:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #680]
	cmp	r3, #16
	bls	.L396
	mov	r2, r0
	ldr	r1, .L465+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #680]
	b	.L396
.L453:
	mov	r2, r0
	str	r8, [sp]
	mov	r3, r8
	ldr	r1, .L465+32
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #656]
	b	.L392
.L460:
	cmp	r0, #0
	beq	.L423
.L389:
	ldr	r1, .L465+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #632]
	b	.L423
.L445:
	mov	r2, r0
	ldr	r1, .L465+40
	mov	r0, #1
	mov	r5, r2
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L462:
	mov	r2, r0
	ldr	r1, .L465+44
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #696]
	b	.L401
.L444:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #572]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #556]
	str	r0, [r4, #560]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #556]
	b	.L372
.L452:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #648]
	mov	r0, r5
	bl	BsGet
	b	.L391
.L448:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #612]
	b	.L379
.L446:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #580]
	ldr	r3, [r6, #2176]
	b	.L376
.L463:
	mov	r2, r0
	ldr	r1, .L465+48
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #676]
	b	.L398
.L461:
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #704]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #704]
	cmp	r3, #1
	str	r0, [r4, #708]
	beq	.L464
.L406:
	cmp	r3, #2
	bne	.L424
	add	r8, r7, #16640
	mov	r10, r8
	add	r8, r8, #211
	add	r10, r10, #217
.L408:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L408
	b	.L424
.L464:
	add	r8, r7, #16640
	mov	r10, r8
	add	r8, r8, #205
	add	r10, r10, #211
.L407:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L407
	ldr	r3, [r4, #704]
	b	.L406
.L466:
	.align	2
.L465:
	.word	.LC28
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+428
	.word	.LC25
	.word	.LC35
	.word	.LC34
	.word	.LC27
	.word	.LC32
	.word	.LC30
	.word	.LC29
	.word	.LC26
	.word	.LC33
	.word	.LC31
	UNWIND(.fnend)
	.size	AVS2_InterPictureHeader, .-AVS2_InterPictureHeader
	.align	2
	.global	AVS2_SequenceHeader
	.type	AVS2_SequenceHeader, %function
AVS2_SequenceHeader:
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
	ldr	r1, .L517
	mov	r7, r0
	mov	r0, #7
	add	r6, r7, #44
	bl	dprint_vfmw
	ldr	r3, [r7, #12]
	mov	r1, #32
	mov	r0, r6
	bic	r3, r3, #65536
	str	r3, [r7, #12]
	bl	BsGet
	mov	r0, r6
	mov	r1, #8
	add	r5, r7, #12288
	bl	BsGet
	bic	r3, r0, #2
	str	r0, [r5, #2088]
	cmp	r3, #32
	cmpne	r0, #18
	movne	r8, #1
	moveq	r8, #0
	bne	.L505
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2092]
	beq	.L506
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2096]
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r5, #2096]
	cmp	r0, #1
	cmpeq	r3, #1
	str	r0, [r5, #2100]
	beq	.L507
.L471:
	mov	r1, #14
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2104]
	beq	.L508
	mov	r1, #14
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2112]
	beq	.L509
	ldr	r1, [r5, #2104]
	add	r2, r0, #7
	str	r0, [r5, #2116]
	bic	r2, r2, #7
	add	r3, r1, #7
	str	r2, [r5, #2112]
	str	r1, [r5, #2108]
	bic	r3, r3, #7
	mov	r1, #2
	str	r3, [r5, #2104]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	mov	r4, r0
	str	r0, [r5, #2120]
	beq	.L474
	mov	r2, r0
	ldr	r1, .L517+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L506:
	mov	r2, r0
	ldr	r1, .L517+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L505:
	mov	r2, r0
	ldr	r1, .L517+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L509:
	mov	r2, r0
	ldr	r1, .L517+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L508:
	mov	r2, r0
	ldr	r1, .L517+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L474:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	add	r0, r0, #3
	mov	r2, r0, asl #1
	str	r2, [r5, #2124]
	bic	r3, r2, #2
	cmp	r3, #8
	bne	.L510
	ldr	r2, [r5, #2088]
	cmp	r2, #34
	beq	.L511
	add	r9, r7, #16384
	mov	r2, r3
	mov	r1, #0
	str	r1, [r5, #2128]
	strb	r3, [r9, #405]
.L479:
	ldr	r3, [r7, #36]
	mov	r1, #4
	mov	r0, r6
	str	r2, [r3, #900]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #2132]
	beq	.L512
.L480:
	mov	r1, #4
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #2136]
	beq	.L513
.L481:
	mov	r1, #18
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2140]
	mov	r0, r6
	bl	BsGet
	mov	r1, #12
	str	r0, [r5, #2144]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2148]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2152]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2144]
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	str	r0, [r5, #2156]
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #2160]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2164]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r5, #2168]
	beq	.L514
.L483:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2176]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2180]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2184]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2188]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2272]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2276]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2280]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2284]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2288]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2292]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2296]
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #2144]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #32
	str	r0, [r5, #2300]
	bhi	.L485
	cmp	r0, #0
	addne	r8, r7, #14592
	movne	r4, #0
	beq	.L490
.L489:
	mov	r0, r8
	mov	r1, r6
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r5, #2300]
	add	r4, r4, #1
	add	r8, r8, #68
	cmp	r3, r4
	bhi	.L489
.L490:
	ldr	r3, [r5, #2152]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r9, #384]
	beq	.L515
.L491:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #1
	add	r1, r5, #2080
	movw	lr, #2408
	add	r1, r1, #8
	movw	ip, #2410
	str	r0, [r9, #388]
	add	r0, r7, #14336
	ldr	r4, [r5, #2164]
	add	r0, r0, #40
	ldr	r2, [r5, #2104]
	mov	r3, r3, asl r4
	sub	r2, r2, #1
	uxth	r3, r3
	add	r2, r3, r2
	uxth	r2, r2
	mov	r2, r2, asr r4
	strh	r2, [r1, lr]	@ movhi
	ldr	r2, [r5, #2112]
	sub	r2, r2, #1
	add	r3, r3, r2
	uxth	r3, r3
	mov	r3, r3, asr r4
	strh	r3, [r1, ip]	@ movhi
	bl	AVS2_DeriveMaxDpbNum
	add	r3, r7, #8192
	ldr	r2, [r3, #2508]
	cmp	r2, #0
	beq	.L492
	ldr	r3, [r3, #2516]
	cmp	r3, #0
	beq	.L492
	ldr	r1, [r5, #2104]
	cmp	r2, r1
	beq	.L516
.L495:
	mov	r3, #1
	str	r3, [r7, #20]
.L494:
	ldr	r3, [r7, #12]
	mov	r0, #1
	orr	r3, r3, #65536
	str	r3, [r7, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L510:
	mov	r0, r4
	ldr	r1, .L517+24
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L492:
	mov	r3, #0
	str	r3, [r7, #20]
	b	.L494
.L507:
	ldr	r1, .L517+28
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r5, #2100]
	b	.L471
.L513:
	ldr	r1, .L517+32
	mov	r0, #1
	bl	dprint_vfmw
	b	.L481
.L512:
	ldr	r1, .L517+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L480
.L515:
	mov	r1, #5
	mov	r0, r6
	bl	BsGet
	str	r0, [r9, #384]
	b	.L491
.L485:
	mov	r2, r0
	mov	r3, #32
	ldr	r1, .L517+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L511:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	add	r9, r7, #16384
	add	r2, r0, #3
	str	r0, [r5, #2128]
	mov	r2, r2, asl #1
	uxtb	r2, r2
	strb	r2, [r9, #405]
	and	r3, r2, #252
	cmp	r3, #8
	ldr	r3, [r5, #2124]
	bne	.L478
	cmp	r2, r3
	bcs	.L479
.L478:
	ldr	r1, .L517+44
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L514:
	mov	r1, r0
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r5, #2172]
	bne	.L483
	add	r0, r7, #14336
	mov	r2, r6
	add	r1, r0, #160
	add	r0, r0, #144
	bl	AVS2_WeightQuantMatrix
	b	.L483
.L516:
	ldr	r2, [r5, #2112]
	cmp	r3, r2
	bne	.L495
	b	.L494
.L518:
	.align	2
.L517:
	.word	.LC36
	.word	.LC42
	.word	.LC38
	.word	.LC37
	.word	.LC41
	.word	.LC40
	.word	.LC43
	.word	.LC39
	.word	.LC46
	.word	.LC45
	.word	.LC47
	.word	.LC44
	UNWIND(.fnend)
	.size	AVS2_SequenceHeader, .-AVS2_SequenceHeader
	.align	2
	.global	AVS2_AllocateVHB
	.type	AVS2_AllocateVHB, %function
AVS2_AllocateVHB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r5, r0, #12288
	mov	r4, r0
	mov	r3, #0
	ldr	r0, [r5, #2096]
	str	r3, [fp, #-56]
	ldr	r1, [r5, #2104]
	cmp	r0, #1
	str	r3, [fp, #-52]
	movw	r0, #510
	str	r3, [fp, #-48]
	add	r2, r1, #15
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	mov	r2, r2, lsr #4
	ldr	r3, [r5, #2112]
	sub	ip, r2, #2
	addne	r3, r3, #31
	addeq	r3, r3, #15
	movne	r3, r3, lsr #5
	moveq	r3, r3, lsr #4
	movne	r3, r3, asl #1
	cmp	ip, r0
	bhi	.L522
	sub	ip, r3, #2
	cmp	ip, r0
	bhi	.L522
	ldr	r2, [r4, #36]
	ldr	r6, [r2, #724]
	ldr	r3, [r2, #28]
	cmp	r6, #0
	bne	.L525
	cmp	r3, #25
	beq	.L549
.L526:
	add	r3, r4, #16384
	mov	r8, #0
	ldrb	r7, [r3, #404]	@ zero_extendqisi2
	add	r7, r7, #1
	mov	r6, r7
.L531:
	ldr	r3, .L552
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #36]
	ldr	r0, [r5, #2104]
	ldr	r1, [r5, #2112]
	ldr	ip, [r3, #28]
	add	r2, r0, #15
	add	r3, r1, #15
	bic	r2, r2, #15
	cmp	ip, #24
	bic	r3, r3, #15
	str	r0, [fp, #-44]
	str	r1, [fp, #-40]
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L537
	uxtb	r6, r6
	strb	r7, [fp, #-55]
	strb	r8, [fp, #-54]
.L542:
	sub	r1, fp, #56
	ldr	r0, [r4, #4]
	strb	r6, [fp, #-53]
	bl	FSP_ConfigInstance
	subs	r6, r0, #0
	bne	.L538
	ldr	r1, [r4, #36]
	sub	r3, fp, #36
	ldr	r0, [r4, #4]
	str	r6, [r3, #-24]!
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L550
	cmp	r0, #0
	moveq	r6, #1
	streq	r6, [r4, #24]
	beq	.L546
	ldr	r1, .L552+4
	mov	r0, r6
	bl	dprint_vfmw
	b	.L546
.L522:
	ldr	r1, .L552+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
.L546:
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L525:
	cmp	r3, #25
	bne	.L526
	ldr	r0, [r2, #684]
	ldr	r3, [r5, #2112]
	cmp	r1, r0
	ldr	ip, [r2, #688]
	bhi	.L534
	cmp	r3, ip
	bhi	.L534
	ldr	r3, [r2, #712]
	ldr	r6, [r2, #708]
	cmp	r3, #0
	add	r7, r6, #2
	bne	.L551
.L544:
	mov	r6, #1
	b	.L536
.L538:
	ldr	r1, .L552+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L549:
	ldr	r0, [r2, #684]
	ldr	r3, [r5, #2112]
	cmp	r1, r0
	ldr	ip, [r2, #688]
	bhi	.L528
	cmp	r3, ip
	bhi	.L528
	ldr	r6, [r4, #24]
	cmp	r6, #1
	beq	.L546
	ldr	r1, [r2, #712]
	ldr	r3, [r2, #708]
	cmp	r1, #0
	add	r7, r3, #2
	beq	.L544
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
.L536:
	ldrb	r8, [r2, #732]	@ zero_extendqisi2
	b	.L531
.L537:
	mov	r3, #0
	strb	r8, [fp, #-54]
	mov	r6, #1
	strb	r3, [fp, #-55]
	b	.L542
.L534:
	stmia	sp, {r0, ip}
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L552+16
	bl	dprint_vfmw
	mov	r6, #0
	b	.L546
.L551:
	add	r6, r6, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L536
.L528:
	stmia	sp, {r0, ip}
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L552+20
	bl	dprint_vfmw
	b	.L546
.L550:
	add	r0, r4, #17920
	mov	r6, #3
	add	r0, r0, #144
	bl	ResetVoQueue
	b	.L546
.L553:
	.align	2
.L552:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC51
	.word	.LC48
	.word	.LC52
	.word	.LC50
	.word	.LC49
	UNWIND(.fnend)
	.size	AVS2_AllocateVHB, .-AVS2_AllocateVHB
	.align	2
	.global	AVS2_OutputOneFrame
	.type	AVS2_OutputOneFrame, %function
AVS2_OutputOneFrame:
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
	ldr	r6, [r1, #56]
	mov	r4, r0
	ldr	r0, [r0, #4]
	mov	r1, r6
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L560
	mov	r2, #1
	mov	r1, r6
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	add	r3, r4, #17920
	ldr	r0, [r4, #4]
	add	r3, r3, #144
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #18
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L556
	ldr	r0, [r4, #4]
	mov	r2, #0
	mov	r1, r6
	bl	FSP_SetDisplay
	mov	r2, r6
	ldr	r1, .L561
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
.L556:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L560:
	movw	r2, #2186
	ldr	r1, .L561+4
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L562:
	.align	2
.L561:
	.word	.LC54
	.word	.LC53
	UNWIND(.fnend)
	.size	AVS2_OutputOneFrame, .-AVS2_OutputOneFrame
	.align	2
	.global	AVS2_DisplayFrameInPOI
	.type	AVS2_DisplayFrameInPOI, %function
AVS2_DisplayFrameInPOI:
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
	add	r2, r0, #10432
	add	r3, r0, #18432
	mov	r7, #0
	add	r3, r3, #154
	mov	r4, r0
	ldrsh	r0, [r2, #6]
	mov	r2, r7
.L565:
	ldrsh	r1, [r3]
	cmp	r1, r0
	bgt	.L564
	ldrb	r1, [r3, #-6]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L564
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	add	lr, r7, #1
	sub	ip, fp, #44
	cmp	r1, #0
	add	ip, ip, r7
	uxtbne	r7, lr
	strneb	r2, [ip, #-16]
.L564:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L565
	cmp	r7, #0
	beq	.L563
	sub	r3, fp, #60
	mov	r8, #0
	add	r6, r3, r7
	mov	r9, r8
	mov	r5, #104
.L567:
	cmp	r7, #0
	ble	.L570
	sub	r2, fp, #60
	movw	ip, #32767
.L569:
	ldrb	r1, [r2], #1	@ zero_extendqisi2
	mla	r3, r5, r1, r4
	add	r3, r3, #18432
	add	r3, r3, #144
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L568
	ldrsh	r3, [r3, #2]
	cmp	r3, ip
	movle	r9, r1
	movle	ip, r3
.L568:
	cmp	r2, r6
	bne	.L569
	movw	r3, #32767
	cmp	ip, r3
	beq	.L570
	mul	r1, r5, r9
	mov	r3, #1
	mov	r0, r4
	add	r10, r4, r1
	add	r1, r1, #18432
	add	r10, r10, #18432
	add	r1, r1, #144
	add	r1, r4, r1
	strb	r3, [r10, #148]
	bl	AVS2_OutputOneFrame
	ldrsh	r2, [r10, #146]
	ldr	r1, .L579
	mov	r0, #13
	bl	dprint_vfmw
.L570:
	add	r8, r8, #1
	uxtb	r3, r8
	cmp	r3, r7
	bcc	.L567
.L563:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L580:
	.align	2
.L579:
	.word	.LC55
	UNWIND(.fnend)
	.size	AVS2_DisplayFrameInPOI, .-AVS2_DisplayFrameInPOI
	.align	2
	.global	AVS2_UpdateSceneBuf
	.type	AVS2_UpdateSceneBuf, %function
AVS2_UpdateSceneBuf:
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
	add	r3, r0, #12288
	ldr	r3, [r3, #996]
	sub	r3, r3, #5
	cmp	r3, #1
	ldmhifd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2_UpdateSceneBuf.part.7
	UNWIND(.fnend)
	.size	AVS2_UpdateSceneBuf, .-AVS2_UpdateSceneBuf
	.align	2
	.global	AVS2_UpdateRefBuf
	.type	AVS2_UpdateRefBuf, %function
AVS2_UpdateRefBuf:
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
	add	r7, r0, #12288
	mov	r9, r0
	ldr	r1, .L597
	mov	r0, #13
	ldr	r2, [r7, #1880]
	bl	dprint_vfmw
	ldr	r3, [r7, #1880]
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r10, r9, #14144
	add	r6, r9, #18432
	add	r10, r10, #24
	add	r6, r6, #144
	add	r8, r9, #8192
	mov	r5, #0
.L589:
	add	r3, r8, #2240
	ldr	r4, [r10, #4]!
	add	r3, r3, #4
	ldr	r1, .L597+4
	mov	r2, r5
	mov	r0, #13
	ldrh	r3, [r3, #2]
	rsb	r4, r4, r3
	sxth	r4, r4
	mov	r3, r4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r3, #0
	b	.L588
.L585:
	add	r3, r3, #1
	add	r1, r1, #104
	cmp	r3, #16
	beq	.L587
.L588:
	ldrsh	r2, [r1]
	cmp	r2, r4
	bne	.L585
	ldrb	r2, [r1, #6]	@ zero_extendqisi2
	and	r0, r2, #2
	cmp	r2, #0
	uxtb	r0, r0
	beq	.L585
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	sub	r2, r2, #5
	cmp	r2, #1
	bhi	.L586
	cmp	r0, #0
	strb	r0, [r1, #6]
	bne	.L585
	mov	r1, #104
	mov	r2, r0
	mla	r3, r1, r3, r9
.L596:
	add	r1, r3, #18432
	strb	r0, [r1, #149]
	ldr	r1, [r1, #200]
	ldr	r0, [r9, #4]
	bl	FSP_SetRef
.L587:
	ldr	r3, [r7, #1880]
	add	r5, r5, #1
	cmp	r5, r3
	bcc	.L589
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L586:
	mov	r2, #104
	mov	r0, #0
	mla	r3, r2, r3, r9
	mov	r2, r0
	b	.L596
.L598:
	.align	2
.L597:
	.word	.LC56
	.word	.LC57
	UNWIND(.fnend)
	.size	AVS2_UpdateRefBuf, .-AVS2_UpdateRefBuf
	.align	2
	.global	AVS2_RefreshBuf
	.type	AVS2_RefreshBuf, %function
AVS2_RefreshBuf:
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
	add	r5, r0, #18432
	mov	r6, r0
	add	r5, r5, #200
	mov	r4, #0
	mov	r7, #104
	b	.L603
.L601:
	cmp	r4, #16
	add	r5, r5, #104
	beq	.L605
.L603:
	mla	r3, r7, r4, r6
	ldrb	r2, [r5, #-50]	@ zero_extendqisi2
	add	r4, r4, #1
	cmp	r2, #0
	add	r3, r3, #18432
	add	r3, r3, #144
	beq	.L601
	ldrh	r3, [r3, #4]
	cmp	r3, #1
	bne	.L601
	and	r2, r2, #2
	uxtb	r2, r2
	strb	r2, [r5, #-50]
	cmp	r2, #0
	bne	.L601
	ldr	r1, [r5]
	add	r5, r5, #104
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	cmp	r4, #16
	bne	.L603
.L605:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_RefreshBuf, .-AVS2_RefreshBuf
	.align	2
	.global	AVS2_SetPicInfo
	.type	AVS2_SetPicInfo, %function
AVS2_SetPicInfo:
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
	add	r4, r0, #12288
	add	r1, r0, #10432
	add	r6, r0, #8192
	movw	lr, #2244
	ldr	r3, [r4, #1012]
	uxth	r5, r3
	strh	r5, [r1, #6]	@ movhi
	ldr	r2, [r4, #1020]
	ldr	ip, [r4, #788]
	add	r3, r2, r3
	rsb	r3, ip, r3
	strh	r3, [r1, #8]	@ movhi
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ble	.L608
	ldrsh	r2, [r6, lr]
	sxth	r3, r5
	cmp	r2, r3
	ble	.L608
	add	r2, r0, #18432
	ldr	lr, [r6, #2504]
	add	r0, r0, #20224
	mov	r1, r2
	add	r0, r0, #16
	add	r2, r2, #144
	add	r1, r1, #146
.L610:
	ldrh	r3, [r1, #-2]
	cmp	lr, #0
	add	r1, r1, #104
	sub	r3, r3, #256
	strh	r3, [r1, #-106]	@ movhi
	ldrh	r3, [r2, #2]
	ldrh	ip, [r2, #10]
	sub	r3, r3, #256
	strh	r3, [r2, #2]	@ movhi
	sub	ip, ip, #256
	strh	ip, [r2, #10]	@ movhi
	sxth	r3, r3
	mov	r3, r3, asl #1
	strh	r3, [r2, #8]	@ movhi
	bne	.L609
	ldr	ip, [r4, #1052]
	add	r3, r3, #1
	cmp	ip, #0
	streqh	r3, [r2, #8]	@ movhi
.L609:
	add	r2, r2, #104
	cmp	r2, r0
	bne	.L610
.L608:
	movw	r3, #2244
	strh	r5, [r6, r3]	@ movhi
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SetPicInfo, .-AVS2_SetPicInfo
	.align	2
	.global	AVS2_VarifyDecMode
	.type	AVS2_VarifyDecMode, %function
AVS2_VarifyDecMode:
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
	ldr	r3, [r0, #36]
	mov	r5, r0
	ldr	r4, [r3, #8]
	cmp	r4, #2
	beq	.L615
	cmp	r4, #3
	moveq	r6, #0
	beq	.L614
	cmp	r4, #1
	movne	r6, #1
	beq	.L631
.L614:
	str	r4, [r5, #32]
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L631:
	add	r6, r0, #12288
	ldr	r3, [r6, #996]
	cmp	r3, #2
	beq	.L632
.L622:
	mov	r6, r4
.L618:
	ldr	r3, [r5, #32]
	cmp	r3, #1
	beq	.L614
	mov	r0, r5
	bl	AVS2_ClearDpb
	b	.L614
.L615:
	add	r3, r0, #12288
	ldr	r6, [r3, #1000]
	adds	r6, r6, #0
	movne	r6, #1
	b	.L614
.L632:
	ldr	r3, [r6, #1844]
	cmp	r3, #0
	bne	.L622
	bl	AVS2_DisplayFrameInPOI
	ldr	r3, [r6, #1880]
	cmp	r3, #0
	bne	.L633
.L619:
	mov	r0, r5
	mov	r6, #0
	bl	AVS2_RefreshBuf
	b	.L618
.L633:
	mov	r0, r5
	bl	AVS2_UpdateRefBuf
	b	.L619
	UNWIND(.fnend)
	.size	AVS2_VarifyDecMode, .-AVS2_VarifyDecMode
	.align	2
	.global	AVS2_VarifyFrame
	.type	AVS2_VarifyFrame, %function
AVS2_VarifyFrame:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r3, r0, #18432
	add	r3, r3, #150
	mov	r2, #0
	b	.L638
.L635:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	beq	.L648
.L638:
	ldrb	lr, [r3]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L635
	ldr	r5, [r1, #56]
	ldr	r4, [r3, #50]
	cmp	r5, r4
	beq	.L636
	ldr	r6, [r1, #100]
	ldr	r4, [r3, #54]
	cmp	r6, r4
	beq	.L640
	ldr	r6, [r1, #80]
	ldr	r4, [r3, #74]
	cmp	r6, r4
	bne	.L635
	ldrb	r4, [r3, #-1]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L642
	tst	lr, #2
	beq	.L635
.L642:
	mov	r4, r5
	b	.L637
.L648:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L640:
	mov	r4, r5
.L636:
	ldr	r6, [r1, #80]
.L637:
	mov	ip, #104
	movw	r9, #18656
	mla	ip, ip, r2, r0
	ldrsh	r3, [r1]
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	movw	r8, #18632
	ldr	r10, [r1, #60]
	movw	r7, #18576
	add	r5, ip, #18432
	ldr	r1, .L649
	mov	r0, #1
	ldr	r9, [ip, r9]
	mov	lr, r5
	add	r5, r5, #200
	str	r9, [sp, #36]
	ldr	r5, [r5, #4]
	str	r5, [sp, #32]
	ldr	r5, [ip, r8]
	str	r5, [sp, #28]
	ldrsh	ip, [ip, r7]
	str	ip, [sp, #24]
	ldrb	ip, [lr, #149]	@ zero_extendqisi2
	str	ip, [sp, #20]
	ldrb	ip, [lr, #150]	@ zero_extendqisi2
	str	ip, [sp, #16]
	ldrb	ip, [lr, #151]	@ zero_extendqisi2
	str	r6, [sp, #8]
	str	r4, [sp]
	str	ip, [sp, #12]
	str	r10, [sp, #4]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L650:
	.align	2
.L649:
	.word	.LC58
	UNWIND(.fnend)
	.size	AVS2_VarifyFrame, .-AVS2_VarifyFrame
	.align	2
	.global	AVS2_ReleaseFrameBuf
	.type	AVS2_ReleaseFrameBuf, %function
AVS2_ReleaseFrameBuf:
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
	add	r4, r0, #8192
	ldr	r3, [r4, #2416]
	cmp	r3, #0
	beq	.L652
	ldr	r1, [r3, #56]
	mov	r2, #0
	ldr	r0, [r0, #4]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2416]
	mov	r2, #0
	strb	r2, [r3, #6]
.L652:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ReleaseFrameBuf, .-AVS2_ReleaseFrameBuf
	.align	2
	.global	AVS2_SetupFrameBuf
	.type	AVS2_SetupFrameBuf, %function
AVS2_SetupFrameBuf:
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
	add	r7, r0, #12288
	mov	r6, r0
	ldr	r3, [r7, #996]
	cmp	r3, #6
	beq	.L657
.L661:
	add	r3, r6, #16384
	ldrb	r3, [r3, #2198]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r6, #18432
	movne	r3, #1
	addne	r2, r2, #254
	beq	.L658
.L666:
	ldrb	r1, [r2]	@ zero_extendqisi2
	add	r2, r2, #104
	cmp	r1, #0
	beq	.L658
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L666
.L665:
	ldr	r2, .L693
	mov	r0, #1
	ldr	r1, .L693+4
	mov	r5, #0
	bl	dprint_vfmw
.L667:
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L657:
	add	r3, r0, #18432
	add	r0, r0, #10432
	add	r3, r3, #150
	add	r0, r0, #4
	add	lr, r6, #8192
	mov	r2, #0
	b	.L663
.L660:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	beq	.L661
.L663:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L660
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #6
	bne	.L660
	ldrsh	ip, [r3, #-6]
	mov	r8, lr
	ldrsh	r1, [r0, #2]
	cmp	ip, r1
	bne	.L660
	mov	r3, #104
	movw	r1, #18632
	mul	r2, r3, r2
	add	r4, r2, #18432
	add	r2, r6, r2
	add	r4, r4, #144
	add	r4, r6, r4
	str	r4, [lr, #2416]
	cmp	r4, #0
	ldr	r9, [r2, r1]
	bne	.L662
	b	.L661
.L658:
	mov	r4, #104
	add	r8, r6, #8192
	mla	r3, r4, r3, r6
	mov	r1, #1
	add	r4, r3, #18432
	add	r4, r4, #144
	str	r4, [r8, #2416]
	ldr	r0, [r6, #4]
	bl	FSP_NewLogicFs
	cmp	r4, #0
	mov	r9, r0
	beq	.L665
.L662:
	mov	r1, r9
	ldr	r0, [r6, #4]
	bl	FSP_GetLogicFs
	mvn	r5, r9
	mov	r5, r5, lsr #31
	cmp	r0, #0
	moveq	r5, #0
	cmp	r5, #0
	beq	.L690
	mov	r1, r9
	ldr	r0, [r6, #4]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L691
	str	r9, [r4, #56]
	mov	r1, r9
	ldr	r3, [r5, #112]
	add	r9, r5, #608
	str	r3, [r4, #88]
	ldr	r3, [r5, #116]
	str	r3, [r4, #92]
	ldr	r3, [r5, #140]
	str	r3, [r4, #96]
	ldr	r2, [r5, #36]
	ldr	r3, [r5, #40]
	rsb	r3, r2, r3
	str	r3, [r4, #84]
	ldr	r3, [r5, #36]
	str	r3, [r4, #60]
	ldr	r3, [r5, #40]
	str	r3, [r4, #64]
	ldr	r0, [r6, #4]
	bl	FSP_GetPmvAddr
	add	ip, r5, #592
	add	r1, r8, #2240
	mov	lr, #0
	add	r1, r1, #4
	str	r0, [r4, #80]
	ldr	r0, [r5, #212]
	str	r0, [r4, #100]
	ldr	r0, [r5, #144]
	str	r0, [r4, #68]
	ldr	r10, [r5, #36]
	ldr	r0, [r5, #44]
	rsb	r0, r10, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #48]
	ldr	r10, [r5, #44]
	rsb	r0, r10, r0
	str	r0, [r4, #76]
	ldr	r0, [r6, #28]
	str	r0, [r5, #176]
	ldrb	r0, [r7, #809]	@ zero_extendqisi2
	str	r0, [r5, #168]
	ldrb	r0, [r7, #809]	@ zero_extendqisi2
	str	r0, [r5, #172]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #56]
	strd	r2, [ip, #-8]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #72]
	strd	r2, [ip]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #88]
	strd	r2, [r9, #-8]
	mvn	r2, #0
	ldr	r0, [r6, #36]
	mvn	r3, #0
	ldr	r0, [r0, #104]
	str	r0, [r5]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #108]
	str	r0, [r5, #4]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #112]
	str	r0, [r5, #8]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #128]
	str	r0, [r5, #12]
	ldr	r0, [r7, #1040]
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r5, #52]
	ldr	r0, [r6, #36]
	strd	r2, [r0, #56]
	ldrh	r3, [r1, #2]
	strh	r3, [r4]	@ movhi
	ldrh	r3, [r1, #4]
	strh	r3, [r4, #2]	@ movhi
	sxth	r3, r3
	ldr	r2, [r7, #996]
	mov	r3, r3, asl #1
	strb	r2, [r4, #7]
	ldr	r2, [r7, #1844]
	strb	lr, [r4, #4]
	strb	r2, [r4, #5]
	ldrh	r1, [r1, #2]
	ldr	r2, [r7, #1020]
	strh	r3, [r4, #8]	@ movhi
	add	r2, r2, r1
	strh	r2, [r4, #10]	@ movhi
	ldr	r2, [r8, #2504]
	cmp	r2, lr
	ldr	r2, [r7, #1052]
	bne	.L671
	cmp	r2, #0
	addeq	r3, r3, #1
	streqh	r3, [r4, #8]	@ movhi
	ldreq	r2, [r7, #1052]
.L671:
	strb	r2, [r4, #12]
	mov	r1, r4
	ldr	r3, [r7, #1040]
	mov	r2, #0
	mov	r0, r6
	strb	r3, [r4, #13]
	ldr	r3, [r7, #1044]
	strb	r2, [r4, #6]
	strb	r3, [r4, #14]
	bl	AVS2_VarifyFrame
	subs	r5, r0, #0
	beq	.L692
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #4
	bhi	.L673
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	mov	r5, #1
	strb	r5, [r4, #6]
	cmp	r3, #0
	beq	.L667
.L674:
	mov	r2, #1
	ldr	r0, [r6, #4]
	mov	r5, r2
	ldr	r1, [r4, #56]
	bl	FSP_SetRef
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L690:
	ldr	r2, .L693
	mov	r0, #1
	ldr	r1, .L693+8
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L673:
	cmp	r3, #6
	moveq	r3, #2
	movne	r3, #3
	strb	r3, [r4, #6]
	b	.L674
.L692:
	ldrsh	r2, [r4]
	mov	r0, #1
	ldr	r1, .L693+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	AVS2_ReleaseFrameBuf
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L691:
	ldr	r2, .L693
	mov	r0, #1
	ldr	r1, .L693+16
	bl	dprint_vfmw
	b	.L667
.L694:
	.align	2
.L693:
	.word	.LANCHOR0+452
	.word	.LC59
	.word	.LC60
	.word	.LC62
	.word	.LC61
	UNWIND(.fnend)
	.size	AVS2_SetupFrameBuf, .-AVS2_SetupFrameBuf
	.align	2
	.global	AVS2_SetupRefFrame
	.type	AVS2_SetupRefFrame, %function
AVS2_SetupRefFrame:
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
	add	r3, r0, #10560
	add	r2, r0, #10624
	add	r3, r3, #48
	add	r2, r2, #44
	mov	r7, r0
	mov	r1, #0
.L696:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L696
	add	r6, r7, #12288
	ldr	r2, [r6, #996]
	cmp	r2, #4
	beq	.L733
	ldr	r3, [r6, #1848]
	sub	r1, r3, #1
	cmp	r1, #6
	bhi	.L701
	cmp	r3, #0
	beq	.L702
	add	r5, r7, #14080
	add	r10, r7, #18432
	mov	r9, #0
	add	r5, r5, #56
	add	r10, r10, #150
	add	r8, r7, #8192
	mov	r4, r9
.L707:
	add	r2, r8, #2240
	ldr	r3, [r5, #4]!
	add	r2, r2, #4
	ldrh	r2, [r2, #2]
	rsb	r3, r3, r2
	sxth	r2, r2
	sxth	r3, r3
	cmp	r2, r3
	beq	.L703
	mov	r1, r10
	mov	r2, #0
	b	.L706
.L704:
	add	r2, r2, #1
	add	r1, r1, #104
	cmp	r2, #16
	beq	.L705
.L706:
	ldrb	r0, [r1]	@ zero_extendqisi2
	tst	r0, #1
	beq	.L704
	ldrsh	r0, [r1, #-6]
	cmp	r0, r3
	bne	.L704
	ldrb	r0, [r1, #-1]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L704
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #6
	beq	.L704
	mov	r1, #104
	cmp	r2, #15
	mla	r2, r1, r2, r7
	add	r1, r8, r9, lsl #2
	add	r9, r9, #1
	add	r2, r2, #18432
	add	r2, r2, #144
	str	r2, [r1, #2420]
	bgt	.L705
.L703:
	ldr	r3, [r6, #1848]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L707
.L735:
	cmp	r9, r3
	bcc	.L708
	ldr	r2, [r6, #996]
.L702:
	bic	r2, r2, #2
	cmp	r2, #1
	bne	.L710
	ldr	r2, [r6, #988]
	cmp	r2, #1
	beq	.L734
.L710:
	mov	r0, #1
.L699:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L705:
	add	r2, r8, #2240
	ldr	r1, .L737
	add	r2, r2, #4
	mov	r0, #1
	add	r4, r4, #1
	ldrsh	r2, [r2, #2]
	bl	dprint_vfmw
	ldr	r3, [r6, #1848]
	cmp	r4, r3
	bcc	.L707
	b	.L735
.L733:
	add	r3, r7, #18432
	mov	r2, #0
	add	r3, r3, #150
.L700:
	ldrb	r1, [r3]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L698
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	sub	r1, r1, #5
	cmp	r1, #1
	bls	.L736
.L698:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L700
	ldr	r1, .L737+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L708:
	mov	r2, r9
	ldr	r1, .L737+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L734:
	add	r3, r7, r3, lsl #2
	add	r2, r7, #18432
	add	r3, r3, #8320
	add	r7, r7, #20224
	add	r3, r3, #44
	add	r2, r2, #144
	add	r7, r7, #16
.L712:
	ldrb	r1, [r2, #6]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L711
	ldrb	r1, [r2, #7]	@ zero_extendqisi2
	sub	r1, r1, #5
	cmp	r1, #1
	strls	r2, [r3, #2244]
.L711:
	add	r2, r2, #104
	cmp	r2, r7
	bne	.L712
	b	.L710
.L701:
	mov	r1, #7
	ldr	r2, .L737+12
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L737+16
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L736:
	mov	r3, #104
	add	r1, r7, #8192
	mla	r3, r3, r2, r7
	mov	r0, #1
	add	r3, r3, #18432
	add	r3, r3, #144
	str	r3, [r1, #2420]
	b	.L699
.L738:
	.align	2
.L737:
	.word	.LC64
	.word	.LC63
	.word	.LC65
	.word	.LANCHOR0+472
	.word	.LC66
	UNWIND(.fnend)
	.size	AVS2_SetupRefFrame, .-AVS2_SetupRefFrame
	.align	2
	.global	AVS2_SetupHalConfig
	.type	AVS2_SetupHalConfig, %function
AVS2_SetupHalConfig:
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
	ldr	r2, [r0, #36]
	add	r6, r0, #8192
	mov	r4, r0
	add	r3, r0, #10624
	movw	ip, #2412
	ldr	r1, [r2, #592]
	add	r3, r3, #56
	ldr	r7, [r6, #2420]
	movw	r0, #2414
	add	r5, r4, #12288
	strb	r1, [r4, #78]
	ldr	r1, [r2, #624]
	strb	r1, [r4, #80]
	ldr	r2, [r2, #644]
	strb	r2, [r4, #77]
	ldr	r1, [r6, #2416]
	ldr	r2, [r1, #60]
	str	r2, [r4, #168]
	ldr	r2, [r1, #88]
	str	r2, [r4, #336]
	ldr	r2, [r1, #92]
	str	r2, [r4, #340]
	ldr	r2, [r1, #84]
	str	r2, [r4, #344]
	ldr	r2, [r1, #96]
	str	r2, [r4, #348]
	ldr	r2, [r1, #100]
	str	r2, [r4, #172]
	ldr	r2, [r1, #68]
	str	r2, [r4, #352]
	ldr	r2, [r1, #72]
	str	r2, [r4, #356]
	ldr	r2, [r1, #76]
	str	r2, [r4, #360]
	ldr	r2, [r6, #2508]
	str	r2, [r4, #176]
	ldr	r2, [r6, #2516]
	str	r2, [r4, #180]
	ldrh	r2, [r3, ip]
	str	r2, [r4, #184]
	ldrh	r3, [r3, r0]
	str	r3, [r4, #188]
	ldr	r3, [r5, #1052]
	str	r3, [r4, #196]
	ldrb	r2, [r5, #809]	@ zero_extendqisi2
	strb	r2, [r4, #76]
	ldr	r2, [r5, #1060]
	str	r2, [r4, #200]
	ldr	r2, [r5, #1056]
	str	r2, [r4, #204]
	ldr	r2, [r5, #996]
	str	r2, [r4, #208]
	ldr	r2, [r6, #2504]
	cmp	r2, #1
	movne	r3, #0
	strne	r3, [r4, #212]
	beq	.L762
.L742:
	ldr	r3, [r5, #792]
	str	r3, [r4, #216]
	ldr	r3, [r6, #2680]
	str	r3, [r4, #220]
	ldr	r3, [r6, #2524]
	str	r3, [r4, #224]
	ldr	r3, [r6, #2684]
	str	r3, [r4, #228]
	ldr	r3, [r6, #2584]
	str	r3, [r4, #232]
	ldr	r3, [r6, #2592]
	str	r3, [r4, #236]
	ldr	r3, [r6, #2588]
	str	r3, [r4, #240]
	ldrb	r3, [r5, #864]	@ zero_extendqisi2
	str	r3, [r4, #244]
	ldr	r3, [r6, #2676]
	str	r3, [r4, #248]
	ldr	r2, [r5, #1120]
	ldr	r3, [r5, #1124]
	ldr	r0, [r5, #1116]
	mov	r2, r2, asl #1
	orr	r3, r2, r3, asl #2
	orr	r3, r3, r0
	str	r3, [r4, #252]
	ldr	r3, [r6, #2692]
	str	r3, [r4, #256]
	ldr	r3, [r6, #2696]
	str	r3, [r4, #260]
	ldr	r3, [r6, #2568]
	str	r3, [r4, #192]
	ldr	r3, [r6, #2688]
	str	r3, [r4, #264]
	ldr	r3, [r6, #2572]
	str	r3, [r4, #268]
	ldr	r3, [r5, #1088]
	str	r3, [r4, #284]
	ldr	r3, [r5, #1104]
	str	r3, [r4, #272]
	ldr	r3, [r5, #1100]
	str	r3, [r4, #276]
	ldr	r3, [r5, #1096]
	str	r3, [r4, #280]
	ldr	r3, [r5, #1084]
	str	r3, [r4, #288]
	ldr	r3, [r5, #1080]
	str	r3, [r4, #292]
	ldr	r3, [r5, #1076]
	str	r3, [r4, #296]
	ldr	r3, [r5, #1072]
	str	r3, [r4, #300]
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	str	r3, [r4, #304]
	ldrb	r3, [r1, #13]	@ zero_extendqisi2
	str	r3, [r4, #308]
	ldrb	r3, [r1, #14]	@ zero_extendqisi2
	str	r3, [r4, #312]
	ldr	r0, [r5, #1000]
	cmp	r0, #0
	bne	.L743
	add	ip, r4, #10560
	mov	r3, r4
	add	ip, ip, #52
	mov	r2, r7
	b	.L746
.L763:
	ldr	r2, [ip, #4]!
.L746:
	cmp	r2, #0
	add	r0, r0, #1
	beq	.L744
	ldrb	lr, [r2, #12]	@ zero_extendqisi2
	str	lr, [r3, #392]
	ldrb	lr, [r2, #13]	@ zero_extendqisi2
	str	lr, [r3, #420]
	ldrb	lr, [r2, #14]	@ zero_extendqisi2
	str	lr, [r3, #448]
	ldr	r2, [r2, #60]
	str	r2, [r3, #476]
.L744:
	cmp	r0, #7
	add	r3, r3, #4
	bne	.L763
.L745:
	ldr	r3, [r1, #80]
	cmp	r7, #0
	ldr	r8, .L765
	add	r1, r4, #13440
	streq	r7, [r4, #320]
	add	r1, r1, #44
	str	r3, [r4, #316]
	mov	r2, #576
	ldrne	r3, [r7, #80]
	add	r0, r4, #568
	add	r9, r4, #10624
	add	r9, r9, #56
	strne	r3, [r4, #320]
	ldr	r3, [r8, #52]
	blx	r3
	add	r1, r4, #14016
	add	r0, r4, #1136
	ldr	r3, [r8, #52]
	add	r1, r1, #44
	add	r0, r0, #8
	mov	r2, #72
	blx	r3
	ldr	r10, [r5, #1000]
	cmp	r10, #0
	beq	.L764
	ldrb	r3, [r5, #865]	@ zero_extendqisi2
	str	r3, [r4, #324]
	ldr	r3, [r6, #2700]
	str	r3, [r4, #328]
	ldr	r3, [r5, #988]
	str	r3, [r4, #332]
.L750:
	ldr	r3, [r8, #48]
	mov	r2, #28
	mov	r1, #0
	add	r0, r4, #364
	blx	r3
.L751:
	add	r1, r9, #2480
	ldr	r3, [r8, #52]
	add	r1, r1, #6
	mov	r2, #16
	add	r0, r4, #81
	blx	r3
	add	r1, r9, #2496
	add	r1, r1, #6
	ldr	r3, [r8, #52]
	add	r0, r4, #97
	mov	r2, #64
	blx	r3
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L743:
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	str	r3, [r4, #392]
	ldrb	r3, [r1, #13]	@ zero_extendqisi2
	str	r3, [r4, #420]
	ldrb	r3, [r1, #14]	@ zero_extendqisi2
	str	r3, [r4, #448]
	ldr	r3, [r1, #60]
	str	r3, [r4, #476]
	b	.L745
.L764:
	add	r3, r4, #10432
	ldr	ip, [r8, #52]
	add	r1, r3, #16
	mov	r2, #14
	add	r0, r4, #504
	add	r3, r3, #4
	str	r3, [fp, #-48]
	blx	ip
	ldr	r3, [fp, #-48]
	mov	r2, #14
	ldr	ip, [r8, #52]
	add	r0, r4, #520
	add	r1, r3, #40
	blx	ip
	ldr	r3, [fp, #-48]
	ldr	ip, [r8, #52]
	mov	r2, #14
	add	r1, r3, #26
	add	r0, r4, #536
	blx	ip
	ldr	r3, [fp, #-48]
	mov	r2, #14
	add	r0, r4, #552
	add	r1, r3, #54
	ldr	r3, [r8, #52]
	blx	r3
	movw	r2, #550
	movw	r3, #566
	movw	r0, #518
	movw	r1, #534
	strh	r10, [r4, r0]	@ movhi
	strh	r10, [r4, r1]	@ movhi
	strh	r10, [r4, r2]	@ movhi
	strh	r10, [r4, r3]	@ movhi
	ldrb	r2, [r5, #865]	@ zero_extendqisi2
	ldr	r3, [r5, #1000]
	str	r2, [r4, #324]
	cmp	r3, #0
	ldr	r3, [r6, #2700]
	str	r3, [r4, #328]
	ldr	r3, [r5, #988]
	str	r3, [r4, #332]
	bne	.L750
	ldrb	r3, [r7, #46]	@ zero_extendqisi2
	str	r3, [r4, #364]
	ldrb	r3, [r7, #47]	@ zero_extendqisi2
	str	r3, [r4, #368]
	ldrb	r3, [r7, #48]	@ zero_extendqisi2
	str	r3, [r4, #372]
	ldrb	r3, [r7, #49]	@ zero_extendqisi2
	str	r3, [r4, #376]
	ldrb	r3, [r7, #50]	@ zero_extendqisi2
	str	r3, [r4, #380]
	ldrb	r3, [r7, #51]	@ zero_extendqisi2
	str	r3, [r4, #384]
	ldrb	r3, [r7, #52]	@ zero_extendqisi2
	str	r3, [r4, #388]
	b	.L751
.L762:
	cmp	r3, #1
	movne	r3, #2
	str	r3, [r4, #212]
	b	.L742
.L766:
	.align	2
.L765:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	AVS2_SetupHalConfig, .-AVS2_SetupHalConfig
	.global	__aeabi_idiv
	.align	2
	.global	AVS2_CalDistance
	.type	AVS2_CalDistance, %function
AVS2_CalDistance:
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
	add	r3, r0, #8192
	str	r3, [fp, #-52]
	mov	r6, r0
	mov	r2, r3
	ldr	r3, [r3, #2420]
	ldr	r2, [r2, #2416]
	cmp	r3, #0
	addeq	r6, r0, #12288
	ldreqb	r3, [r6, #864]	@ zero_extendqisi2
	beq	.L769
	add	ip, r6, #12288
	ldrb	r3, [ip, #864]	@ zero_extendqisi2
	sub	r1, r3, #1
	cmp	r1, #6
	bhi	.L769
	add	r3, r2, #16
	add	r7, r2, #30
	mov	r4, #1
	mov	lr, #16384
	mov	r1, r3
	mov	r0, r7
.L772:
	strh	r4, [r1, #2]!	@ movhi
	cmp	r1, r7
	strh	lr, [r0, #2]!	@ movhi
	bne	.L772
	ldrb	r1, [ip, #864]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L773
	add	r8, r6, #10560
	ldrsh	r1, [r2, #2]
	add	r8, r8, #48
	add	r10, r2, #45
	add	r4, r2, #18
	str	r6, [fp, #-64]
	mov	r5, #0
	mov	r6, r2
	mov	r9, ip
	str	r1, [fp, #-48]
	str	r3, [fp, #-56]
	str	r7, [fp, #-60]
.L778:
	ldr	r1, [r8, #4]!
	ldr	r3, [fp, #-48]
	ldrb	r0, [r1, #12]	@ zero_extendqisi2
	strb	r0, [r10, #1]!
	ldrsh	r0, [r1, #2]
	cmp	r0, r3
	ldrltsh	r0, [r1, #8]
	ldrgesh	r1, [r1, #8]
	ldrltsh	r1, [r6, #8]
	ldrgesh	r0, [r6, #8]
	rsb	r0, r0, r1
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	r1, r1, lsr #23
	add	r0, r0, r1
	ubfx	r0, r0, #0, #9
	rsb	r1, r1, r0
	mov	r0, #16384
	mov	lr, r0
	uxth	r1, r1
	strh	r1, [r4]	@ movhi
	cmp	r1, #0
	sxth	r1, r1
	moveq	r3, #1
	streqh	r3, [r4]	@ movhi
	beq	.L777
	bl	__aeabi_idiv
	uxth	lr, r0
.L777:
	strh	lr, [r7, #2]!	@ movhi
	add	r5, r5, #1
	ldrb	r1, [r9, #864]	@ zero_extendqisi2
	add	r4, r4, #2
	cmp	r1, r5
	bhi	.L778
	ldr	r0, [r9, #988]
	ldr	r2, [fp, #-52]
	cmp	r0, #1
	ldr	r3, [fp, #-56]
	ldr	r7, [fp, #-60]
	ldr	r6, [fp, #-64]
	ldr	r2, [r2, #2420]
	beq	.L785
.L786:
	add	lr, r6, #10432
	add	r4, r2, #16
	add	r1, r2, #30
	mov	r2, #7
	mov	ip, lr
	mov	r0, lr
	mov	r6, lr
	add	ip, ip, #42
	add	lr, lr, #14
	add	r0, r0, #28
	add	r6, r6, #56
.L783:
	ldrh	r5, [r3, #2]!
	subs	r2, r2, #1
	strh	r5, [lr, #2]!	@ movhi
	ldrh	r5, [r4, #2]!
	strh	r5, [ip, #2]!	@ movhi
	ldrh	r5, [r7, #2]!
	strh	r5, [r0, #2]!	@ movhi
	ldrh	r5, [r1, #2]!
	strh	r5, [r6, #2]!	@ movhi
	bne	.L783
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L769:
	mov	r1, #7
	ldr	r2, .L800
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L800+4
	bl	dprint_vfmw
.L767:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L785:
	cmp	r1, #1
	beq	.L799
.L780:
	add	r5, r6, #10432
	add	r8, r2, #16
	add	r2, r2, #30
	mov	r0, #7
	mov	r4, r5
	mov	lr, r5
	mov	ip, r5
	add	r4, r4, #42
	add	r5, r5, #14
	add	lr, lr, #28
	add	ip, ip, #56
.L782:
	ldrh	r9, [r3, #2]!
	subs	r0, r0, #1
	strh	r9, [r5, #2]!	@ movhi
	ldrh	r9, [r8, #2]!
	strh	r9, [r4, #2]!	@ movhi
	ldrh	r9, [r7, #2]!
	strh	r9, [lr, #2]!	@ movhi
	ldrh	r9, [r2, #2]!
	strh	r9, [ip, #2]!	@ movhi
	bne	.L782
	add	r1, r6, r1, lsl #1
	movw	r0, #2254
	add	r1, r1, #8192
	movw	r3, #2268
	mov	ip, #1
	mov	r2, #16384
	strh	ip, [r1, r0]	@ movhi
	strh	r2, [r1, r3]	@ movhi
	b	.L767
.L773:
	ldr	r0, [ip, #988]
	ldr	r2, [fp, #-52]
	cmp	r0, #1
	ldr	r2, [r2, #2420]
	bne	.L786
	b	.L780
.L799:
	add	lr, r6, #10432
	mov	r3, #7
	mov	r4, #16384
	mov	ip, lr
	mov	r0, lr
	mov	r2, lr
	add	ip, ip, #42
	add	lr, lr, #14
	add	r0, r0, #28
	add	r2, r2, #56
.L781:
	subs	r3, r3, #1
	strh	r1, [lr, #2]!	@ movhi
	strh	r1, [ip, #2]!	@ movhi
	strh	r4, [r0, #2]!	@ movhi
	strh	r4, [r2, #2]!	@ movhi
	bne	.L781
	b	.L767
.L801:
	.align	2
.L800:
	.word	.LANCHOR0+492
	.word	.LC67
	UNWIND(.fnend)
	.size	AVS2_CalDistance, .-AVS2_CalDistance
	.align	2
	.global	AVS2_SetImgFormat
	.type	AVS2_SetImgFormat, %function
AVS2_SetImgFormat:
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
	add	r5, r0, #8192
	add	r10, r0, #12288
	mov	r6, r0
	ldr	r3, [r5, #2500]
	ldr	r7, [r10, #996]
	cmp	r3, #1
	ldr	r3, [r10, #816]
	str	r3, [fp, #-52]
	beq	.L808
	ldr	r3, [r10, #1036]
	subs	r3, r3, #1
	movne	r3, #1
	str	r3, [fp, #-48]
.L803:
	ldr	r3, [r5, #2536]
	ldr	r0, [r6, #4]
	sub	r3, r3, #1
	ldr	r9, [r10, #1044]
	cmp	r3, #3
	ldrls	r2, .L813
	movhi	r8, #0
	addls	r3, r2, r3, lsl #2
	ldrls	r8, [r3, #512]
	ldr	r3, [r5, #2416]
	ldr	r1, [r3, #56]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L811
	ldr	r3, [r4, #64]
	mov	r1, r8
	bfi	r3, r8, #14, #3
	str	r3, [r4, #64]
	ldr	ip, [fp, #-52]
	mov	r2, r3, lsr #8
	ldrb	lr, [r4, #66]	@ zero_extendqisi2
	bfi	r3, ip, #5, #3
	bfi	r2, r9, #4, #2
	and	r3, r3, #227
	bfi	r3, r7, #0, #2
	uxtb	r2, r2
	strb	r3, [r4, #64]
	orr	r2, r2, #12
	ldr	r3, [fp, #-48]
	bfi	r2, r3, #0, #2
	strb	r2, [r4, #65]
	ldr	r3, [r5, #2416]
	ldrb	r3, [r3, #15]	@ zero_extendqisi2
	bfi	lr, r3, #1, #1
	strb	lr, [r4, #66]
	ldr	r3, [r5, #2252]
	str	r7, [r4, #56]
	str	r7, [r4, #60]
	str	r3, [r4, #152]
	bl	SetAspectRatio
	ldr	r3, [r5, #2416]
	ldrb	r3, [r3, #16]	@ zero_extendqisi2
	str	r3, [r4, #120]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #596]
	str	r3, [r4, #124]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #600]
	str	r3, [r4, #128]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #604]
	str	r3, [r4, #132]
	ldr	r3, [r5, #2508]
	str	r3, [r4, #68]
	ldr	r3, [r5, #2516]
	str	r3, [r4, #72]
	ldr	r2, [r5, #2512]
	str	r2, [r4, #76]
	ldr	r2, [r5, #2520]
	str	r2, [r4, #80]
	ldr	r2, [r10, #812]
	str	r2, [r4, #108]
	ldr	r2, [r6, #36]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L812
.L806:
	mov	r3, #18
	str	r3, [r4, #296]
	ldr	r1, [r10, #1040]
	mov	r2, #1
	mov	r3, #8
	strb	r2, [r4, #291]
	cmp	r1, r2
	strb	r2, [r4, #289]
	str	r3, [r4, #300]
	moveq	r2, #0
	movne	r2, #4
	str	r3, [r4, #308]
	strb	r2, [r4, #284]
	str	r3, [r4, #304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L808:
	mov	r3, #0
	str	r3, [fp, #-48]
	b	.L803
.L812:
	ldr	r0, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	add	lr, r4, #512
	mov	r3, r3, lsr #4
	mov	r1, r0, asl #4
	add	r5, ip, r0
	mul	r1, r3, r1
	add	r6, r1, ip
	str	r6, [r4, #40]
	ldrd	r2, [lr, #-8]
	add	r0, r6, r0
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [lr]
	str	r6, [r4, #24]
	str	r0, [r4, #32]
	str	r5, [r4, #28]
	str	ip, [r4, #20]
	b	.L806
.L811:
	movw	r2, #3053
	ldr	r1, .L813+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L814:
	.align	2
.L813:
	.word	.LANCHOR0
	.word	.LC68
	UNWIND(.fnend)
	.size	AVS2_SetImgFormat, .-AVS2_SetImgFormat
	.align	2
	.global	AVS2_SimpleDirectProcess
	.type	AVS2_SimpleDirectProcess, %function
AVS2_SimpleDirectProcess:
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
	add	r3, r0, #8192
	mov	r2, #1
	mov	r6, r0
	ldr	r4, [r3, #2416]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	strb	r2, [r4, #4]
	cmp	r3, #6
	beq	.L818
	mov	r1, r4
	bl	AVS2_OutputOneFrame
.L817:
	mov	r5, #0
	ldr	r1, [r4, #56]
	strb	r5, [r4, #5]
	mov	r2, r5
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	strb	r5, [r4, #6]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L818:
	mov	r2, #0
	ldr	r1, [r4, #56]
	ldr	r0, [r0, #4]
	bl	FSP_SetDisplay
	b	.L817
	UNWIND(.fnend)
	.size	AVS2_SimpleDirectProcess, .-AVS2_SimpleDirectProcess
	.align	2
	.global	AVS2_DispOrderProcess
	.type	AVS2_DispOrderProcess, %function
AVS2_DispOrderProcess:
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
	add	r3, r0, #8192
	mov	r4, r0
	ldr	r2, [r3, #2416]
	ldrb	r1, [r2, #7]	@ zero_extendqisi2
	cmp	r1, #6
	beq	.L822
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L821
	ldr	r1, [r0, #36]
	ldr	r1, [r1, #12]
	cmp	r1, #0
	beq	.L823
.L821:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_DisplayFrameInPOI
.L823:
	mov	r5, #1
	strb	r5, [r2, #4]
	ldr	r1, [r3, #2416]
	bl	AVS2_OutputOneFrame
	strb	r5, [r4, #1]
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_DisplayFrameInPOI
.L822:
	mov	r1, #1
	strb	r1, [r2, #4]
	ldr	r3, [r3, #2416]
	mov	r2, #0
	ldr	r0, [r0, #4]
	ldr	r1, [r3, #56]
	bl	FSP_SetDisplay
	b	.L821
	UNWIND(.fnend)
	.size	AVS2_DispOrderProcess, .-AVS2_DispOrderProcess
	.align	2
	.global	AVS2_DecOrderProcess
	.type	AVS2_DecOrderProcess, %function
AVS2_DecOrderProcess:
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
	add	r2, r0, #8192
	mov	ip, #1
	ldr	r1, [r2, #2416]
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	strb	ip, [r1, #4]
	cmp	r2, #6
	beq	.L826
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2_OutputOneFrame
.L826:
	ldr	r1, [r1, #56]
	mov	r2, #0
	ldr	r0, [r0, #4]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetDisplay
	UNWIND(.fnend)
	.size	AVS2_DecOrderProcess, .-AVS2_DecOrderProcess
	.align	2
	.global	AVS2_UpdateFrameBuf
	.type	AVS2_UpdateFrameBuf, %function
AVS2_UpdateFrameBuf:
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
	add	r3, r0, #12288
	mov	r4, r0
	ldr	r3, [r3, #996]
	sub	r3, r3, #5
	cmp	r3, #1
	bls	.L829
.L828:
	mov	r0, r4
	bl	AVS2_UpdateRefBuf
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_RefreshBuf
.L829:
	bl	AVS2_UpdateSceneBuf.part.7
	b	.L828
	UNWIND(.fnend)
	.size	AVS2_UpdateFrameBuf, .-AVS2_UpdateFrameBuf
	.align	2
	.global	AVS2_FlushFrameInDpb
	.type	AVS2_FlushFrameInDpb, %function
AVS2_FlushFrameInDpb:
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
	add	r7, r0, #18432
	add	r7, r7, #148
	mov	r8, #0
	mov	r4, r0
	mov	r2, r8
	mov	r3, r7
.L832:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L831
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	add	ip, r8, #1
	sub	r0, fp, #44
	cmp	r1, #0
	add	r0, r0, r8
	uxtbne	r8, ip
	strneb	r2, [r0, #-16]
.L831:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L832
	cmp	r8, #0
	beq	.L833
	sub	r3, fp, #60
	mov	r9, #0
	add	r6, r3, r8
	mov	r10, r9
	mov	r5, #104
.L834:
	cmp	r8, #0
	ble	.L837
	sub	r2, fp, #60
	movw	ip, #32767
.L836:
	ldrb	r1, [r2], #1	@ zero_extendqisi2
	mla	r3, r5, r1, r4
	add	r3, r3, #18432
	add	r3, r3, #144
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L835
	ldrsh	r3, [r3, #2]
	cmp	r3, ip
	movle	r10, r1
	movle	ip, r3
.L835:
	cmp	r2, r6
	bne	.L836
	movw	r3, #32767
	cmp	ip, r3
	beq	.L837
	mul	r1, r5, r10
	mov	r3, #1
	mov	r0, r4
	add	r2, r4, r1
	add	r1, r1, #18432
	add	r2, r2, #18432
	add	r1, r1, #144
	add	r1, r4, r1
	add	r2, r2, #144
	strb	r3, [r2, #4]
	str	r2, [fp, #-64]
	bl	AVS2_OutputOneFrame
	ldr	r2, [fp, #-64]
	mov	r0, #13
	ldr	r1, .L852
	ldrsh	r2, [r2, #2]
	bl	dprint_vfmw
.L837:
	add	r9, r9, #1
	uxtb	r3, r9
	cmp	r8, r3
	bhi	.L834
.L833:
	add	r4, r4, #20224
	add	r4, r4, #20
	b	.L839
.L838:
	add	r7, r7, #104
	cmp	r7, r4
	beq	.L851
.L839:
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L838
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	add	r7, r7, #104
	cmp	r3, #0
	ldreqb	r3, [r7, #-102]	@ zero_extendqisi2
	andeq	r3, r3, #2
	streqb	r3, [r7, #-102]
	cmp	r7, r4
	bne	.L839
.L851:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L853:
	.align	2
.L852:
	.word	.LC55
	UNWIND(.fnend)
	.size	AVS2_FlushFrameInDpb, .-AVS2_FlushFrameInDpb
	.align	2
	.global	AVS2_FlushPreSizeImg
	.type	AVS2_FlushPreSizeImg, %function
AVS2_FlushPreSizeImg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
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
	sub	r3, fp, #20
	mov	r4, #0
	mov	r5, r0
	str	r4, [r3, #-4]!
	sub	r2, fp, #28
	ldr	r0, [r0, #4]
	sub	r1, fp, #32
	str	r4, [fp, #-32]
	str	r4, [fp, #-28]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5, #36]
	ldr	r3, [r3, #724]
	cmp	r3, #1
	movne	r0, #1
	beq	.L859
.L855:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L859:
	ldr	r3, [fp, #-24]
	cmp	r3, r4
	ble	.L860
.L858:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L860:
	ldr	r3, [fp, #-28]
	cmp	r3, #32
	bgt	.L858
	ldr	r4, [r5, #40]
	clz	r0, r4
	mov	r0, r0, lsr #5
	b	.L855
	UNWIND(.fnend)
	.size	AVS2_FlushPreSizeImg, .-AVS2_FlushPreSizeImg
	.align	2
	.global	AVS2_ArrangeFrameBuf
	.type	AVS2_ArrangeFrameBuf, %function
AVS2_ArrangeFrameBuf:
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
	ldr	r3, [r0, #20]
	mov	r4, r0
	cmp	r3, #0
	beq	.L862
	bl	AVS2_FlushPreSizeImg
	cmp	r0, #0
	bne	.L863
.L865:
	mov	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L863:
	mov	r0, r4
	bl	AVS2_ClearDpb
	add	r1, r4, #17920
	add	r1, r1, #144
	ldr	r0, [r4, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r3, #0
	str	r3, [r4, #20]
.L862:
	mov	r3, #0
	mov	r0, r4
	str	r3, [r4, #24]
	bl	AVS2_AllocateVHB
	cmp	r0, #3
	mov	r4, r0
	beq	.L865
	cmp	r0, #0
	beq	.L873
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L873:
	ldr	r1, .L874
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L875:
	.align	2
.L874:
	.word	.LC69
	UNWIND(.fnend)
	.size	AVS2_ArrangeFrameBuf, .-AVS2_ArrangeFrameBuf
	.align	2
	.global	AVS2_ParseHeader
	.type	AVS2_ParseHeader, %function
AVS2_ParseHeader:
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
	add	r5, r0, #44
	mov	r3, #0
	mov	r4, r0
	str	r3, [r0, #8]
	mov	r1, #32
	mov	r0, r5
	bl	BsShow
	uxtb	r6, r0
	sub	r3, r6, #176
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L877
.L879:
	.word	.L878
	.word	.L880
	.word	.L881
	.word	.L882
	.word	.L877
	.word	.L883
	.word	.L882
	.word	.L880
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L884
.L884:
	mov	r1, #32
	mov	r0, r5
	bl	BsSkip
	mov	r1, #32
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L915
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L890
	mvn	r3, #0
	mov	r5, #1
	str	r3, [r4, #28]
	mov	r0, r4
	strb	r5, [r4]
	bl	AVS2_ClearPacket
	b	.L886
.L878:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L915
	ldr	r3, [r4, #28]
	mov	r0, r4
	cmn	r3, #1
	beq	.L916
	bl	AVS2_FlushFrameInDpb
.L888:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_SequenceHeader
	mov	r0, r4
	bl	AVS2_ClearPacket
.L886:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L880:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L915
	cmp	r6, #177
	beq	.L917
	ldr	r1, .L922
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r5, .L922+4
.L899:
	ldr	r3, [r5]
	tst	r3, #1
	beq	.L918
.L895:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L881:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_User_Data
	mov	r0, r4
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L882:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L915
	tst	r3, #65536
	beq	.L890
	ldr	r3, [r4, #20]
	cmp	r3, #1
	beq	.L891
	ldr	r3, [r4, #24]
	cmp	r3, #0
	bne	.L892
.L891:
	mov	r0, r4
	bl	AVS2_ArrangeFrameBuf
	cmp	r0, #1
	mov	r5, r0
	beq	.L892
	cmp	r0, #3
	moveq	r3, #1
	streq	r3, [r4, #8]
	beq	.L886
.L913:
	mov	r0, r4
	bl	AVS2_ClearPacket
	b	.L886
.L883:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_Extension
	mov	r0, r4
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L877:
	cmp	r6, #143
	bhi	.L890
	ldr	r3, [r4, #12]
	and	r3, r3, #327680
	cmp	r3, #327680
	beq	.L919
.L890:
	mov	r0, r4
	mov	r5, #0
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L915:
	mov	r5, #1
	orr	r3, r3, #16384
	str	r5, [r4, #8]
	mov	r0, r5
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L917:
	ldr	r5, .L922+4
	ldr	r3, [r5]
	tst	r3, #1
	beq	.L920
.L898:
	ldr	r1, .L922+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L899
.L892:
	ldr	r3, [r4, #28]
	cmp	r6, #179
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #28]
	beq	.L921
	bl	AVS2_InterPictureHeader
	b	.L895
.L918:
	mov	r0, r4
	bl	AVS2_ClearDpb
	b	.L895
.L916:
	bl	AVS2_ClearDpb
	b	.L888
.L919:
	mov	r0, r4
	bl	AVS2_WriteSliceMsg
	subs	r5, r0, #0
	bne	.L886
	b	.L913
.L920:
	mov	r0, r4
	bl	AVS2_FlushFrameInDpb
	b	.L898
.L921:
	bl	AVS2_IntraPictureHeader
	b	.L895
.L923:
	.align	2
.L922:
	.word	.LC71
	.word	g_StandardObedience
	.word	.LC70
	UNWIND(.fnend)
	.size	AVS2_ParseHeader, .-AVS2_ParseHeader
	.align	2
	.global	AVS2_DecodeArbiter
	.type	AVS2_DecodeArbiter, %function
AVS2_DecodeArbiter:
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
	ldr	r5, [r0, #12]
	mov	r4, r0
	and	r3, r5, #376832
	cmp	r3, #376832
	beq	.L927
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L927:
	add	r1, r0, #14336
	add	r0, r0, #10624
	add	r1, r1, #36
	movw	r2, #3692
	add	r0, r0, #56
	bic	r5, r5, #311296
	bl	memcpy
	mov	r0, #1
	str	r5, [r4, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_DecodeArbiter, .-AVS2_DecodeArbiter
	.align	2
	.global	AVS2_PrepareDecode
	.type	AVS2_PrepareDecode, %function
AVS2_PrepareDecode:
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
	bl	AVS2_SetPicInfo
	ldr	r3, [r4, #1216]
	sub	r2, r3, #1
	cmp	r2, #255
	bhi	.L943
	mov	r0, r4
	bl	AVS2_VarifyDecMode
	cmp	r0, #0
	bne	.L944
.L942:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L944:
	mov	r0, r4
	bl	AVS2_SetupFrameBuf
	cmp	r0, #0
	beq	.L942
	add	r3, r4, #12288
	ldr	r3, [r3, #1000]
	cmp	r3, #0
	bne	.L933
	mov	r0, r4
	bl	AVS2_SetupRefFrame
	cmp	r0, #0
	beq	.L935
	mov	r0, r4
	bl	AVS2_CalDistance
.L933:
	mov	r0, r4
	bl	AVS2_SetupHalConfig
	cmp	r0, #0
	beq	.L935
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L943:
	ldr	r2, .L945
	mov	r0, #1
	ldr	r1, .L945+4
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L935:
	mov	r0, r4
	bl	AVS2_ReleaseFrameBuf
	b	.L942
.L946:
	.align	2
.L945:
	.word	.LANCHOR0+528
	.word	.LC72
	UNWIND(.fnend)
	.size	AVS2_PrepareDecode, .-AVS2_PrepareDecode
	.align	2
	.global	AVS2_StartDecode
	.type	AVS2_StartDecode, %function
AVS2_StartDecode:
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
	ldr	r3, [r0, #36]
	add	r2, r0, #76
	str	r2, [r0, #40]
	ldr	r2, [r3, #592]
	strb	r2, [r0, #78]
	ldr	r3, [r3, #644]
	strb	r3, [r0, #77]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_StartDecode, .-AVS2_StartDecode
	.align	2
	.global	AVS2_PostProcess
	.type	AVS2_PostProcess, %function
AVS2_PostProcess:
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
	bl	AVS2_SetImgFormat
	ldr	r3, [r4, #36]
	ldr	r2, [r3, #8]
	cmp	r2, #2
	beq	.L954
	ldr	r2, [r3, #24]
	cmp	r2, #0
	beq	.L955
	sub	r3, r2, #1
	cmp	r3, #1
	bls	.L953
	ldr	r1, .L956
	mov	r0, #1
	bl	dprint_vfmw
.L953:
	mov	r0, r4
	bl	AVS2_DecOrderProcess
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_UpdateFrameBuf
.L955:
	mov	r0, r4
	bl	AVS2_DispOrderProcess
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_UpdateFrameBuf
.L954:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SimpleDirectProcess
.L957:
	.align	2
.L956:
	.word	.LC73
	UNWIND(.fnend)
	.size	AVS2_PostProcess, .-AVS2_PostProcess
	.align	2
	.global	AVS2DEC_Init
	.type	AVS2DEC_Init, %function
AVS2DEC_Init:
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
	add	r5, r0, #16384
	ldr	r3, .L962
	mov	r4, r0
	movw	r2, #20240
	ldr	r7, [r5, #2024]
	mov	r6, r1
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	mov	r0, r4
	str	r7, [r5, #2024]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #4]
	beq	.L961
	add	r0, r4, #17920
	add	r0, r0, #144
	bl	ResetVoQueue
	str	r6, [r4, #36]
	mov	r2, #0
	mvn	r3, #0
	str	r2, [r6, #888]
	mov	r0, #1
	str	r3, [r4, #28]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L961:
	ldr	r2, .L962+4
	mov	r0, #0
	ldr	r1, .L962+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L963:
	.align	2
.L962:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+548
	.word	.LC74
	UNWIND(.fnend)
	.size	AVS2DEC_Init, .-AVS2DEC_Init
	.align	2
	.global	AVS2DEC_Destroy
	.type	AVS2DEC_Destroy, %function
AVS2DEC_Destroy:
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
	.size	AVS2DEC_Destroy, .-AVS2DEC_Destroy
	.align	2
	.global	AVS2DEC_GetImageBuffer
	.type	AVS2DEC_GetImageBuffer, %function
AVS2DEC_GetImageBuffer:
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
	ldr	r0, [r0, #4]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L971
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L971:
	add	r1, r4, #17920
	ldr	r0, [r4, #4]
	add	r1, r1, #144
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2DEC_GetImageBuffer, .-AVS2DEC_GetImageBuffer
	.align	2
	.global	AVS2DEC_Decode
	.type	AVS2DEC_Decode, %function
AVS2DEC_Decode:
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
	ldr	r2, [r1, #16]
	mov	r5, r1
	add	r0, r0, #44
	ldr	r1, [r1]
	bl	BsInit
	ldr	r3, .L981
	add	r0, r4, #18176
	mov	r1, r5
	mov	r2, #160
	add	r0, r0, #240
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, r4
	str	r3, [r4, #16]
	bl	AVS2_ParseHeader
	cmp	r0, #3
	beq	.L978
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r5, [r4, #12]
	and	r3, r5, #376832
	cmp	r3, #376832
	beq	.L979
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L978:
	ldr	r3, [r4, #16]
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L979:
	add	r1, r4, #14336
	add	r0, r4, #10624
	add	r1, r1, #36
	movw	r2, #3692
	add	r0, r0, #56
	bic	r5, r5, #311296
	bl	memcpy
	str	r5, [r4, #12]
	mov	r0, r4
	bl	AVS2_PrepareDecode
	subs	r5, r0, #0
	beq	.L980
	ldr	r3, [r4, #36]
	add	r2, r4, #76
	str	r2, [r4, #40]
	mov	r0, #1
	ldr	r2, [r3, #592]
	strb	r2, [r4, #78]
	ldr	r3, [r3, #644]
	strb	r3, [r4, #77]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L980:
	mov	r0, r4
	bl	AVS2_ClearPicSlice
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L982:
	.align	2
.L981:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	AVS2DEC_Decode, .-AVS2DEC_Decode
	.align	2
	.global	AVS2DEC_VDMPostProc
	.type	AVS2DEC_VDMPostProc, %function
AVS2DEC_VDMPostProc:
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
	add	ip, r0, #8192
	ldrb	lr, [r0, #79]	@ zero_extendqisi2
	cmp	r2, #0
	mov	r4, r0
	ldr	ip, [ip, #2416]
	mov	r5, r1
	strb	lr, [ip, #15]
	ldrb	r2, [r0, #78]	@ zero_extendqisi2
	strb	r2, [ip, #16]
	beq	.L984
	mov	ip, r3, asl #6
	ldr	r2, .L994
	sub	r3, ip, r3, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L992
	cmp	r3, #1
	beq	.L984
.L987:
	ldr	r3, [r4, #36]
	mov	r0, r4
	ldr	r3, [r3, #4]
	cmp	r3, r5
	blt	.L993
	bl	AVS2_PostProcess
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L984:
	mov	r0, r4
	bl	AVS2_ClearPicSlice
	b	.L987
.L993:
	bl	AVS2_ClearPicSlice
	mov	r0, r4
	bl	AVS2_ReleaseFrameBuf
	ldr	r3, [r4, #36]
	mov	r2, r5
	ldr	r1, .L994+4
	mov	r0, #1
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L992:
	bl	AVS2_ClearPicSlice
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L995:
	.align	2
.L994:
	.word	g_VdmDrvParam+40
	.word	.LC75
	UNWIND(.fnend)
	.size	AVS2DEC_VDMPostProc, .-AVS2DEC_VDMPostProc
	.align	2
	.global	AVS2DEC_RecycleImage
	.type	AVS2DEC_RecycleImage, %function
AVS2DEC_RecycleImage:
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
	mov	r2, #0
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #4]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L997
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #4]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
.L997:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2DEC_RecycleImage, .-AVS2DEC_RecycleImage
	.align	2
	.global	AVS2DEC_GetRemainImg
	.type	AVS2DEC_GetRemainImg, %function
AVS2DEC_GetRemainImg:
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
	bl	AVS2_FlushFrameInDpb
	add	r0, r4, #17920
	add	r0, r0, #144
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	GetVoLastImageID
	UNWIND(.fnend)
	.size	AVS2DEC_GetRemainImg, .-AVS2DEC_GetRemainImg
	.align	2
	.global	AVS2DEC_ClearCurPic
	.type	AVS2DEC_ClearCurPic, %function
AVS2DEC_ClearCurPic:
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
	bl	AVS2_ClearPicSlice
	mov	r0, r4
	bl	AVS2_ReleaseFrameBuf
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2DEC_ClearCurPic, .-AVS2DEC_ClearCurPic
	.global	AVS2_WqM4x4IdxModel2
	.global	AVS2_WqM4x4IdxModel1
	.global	AVS2_WqM4x4IdxModel0
	.global	AVS2_WqM8x8IdxModel2
	.global	AVS2_WqM8x8IdxModel1
	.global	AVS2_WqM8x8IdxModel0
	.global	AVS2_WQM_8x8Default
	.global	AVS2_WQM_4x4Default
	.global	AVS2_WeightQuantParamBase2
	.global	AVS2_WeightQuantParamBase1
	.global	AVS2_WeightQuantParamDefault
	.global	Avs2_AlfRegionTable
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	CSWTCH.30, %object
	.size	CSWTCH.30, 28
CSWTCH.30:
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.type	__func__.14685, %object
	.size	__func__.14685, 15
__func__.14685:
	.ascii	"AVS2_User_Data\000"
	.space	1
	.type	AVS2_WqM8x8IdxModel0, %object
	.size	AVS2_WqM8x8IdxModel0, 64
AVS2_WqM8x8IdxModel0:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel0, %object
	.size	AVS2_WqM4x4IdxModel0, 16
AVS2_WqM4x4IdxModel0:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	2
	.byte	1
	.byte	5
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel1, %object
	.size	AVS2_WqM8x8IdxModel1, 64
AVS2_WqM8x8IdxModel1:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel1, %object
	.size	AVS2_WqM4x4IdxModel1, 16
AVS2_WqM4x4IdxModel1:
	.byte	0
	.byte	4
	.byte	4
	.byte	5
	.byte	3
	.byte	2
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel2, %object
	.size	AVS2_WqM8x8IdxModel2, 64
AVS2_WqM8x8IdxModel2:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel2, %object
	.size	AVS2_WqM4x4IdxModel2, 16
AVS2_WqM4x4IdxModel2:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WeightQuantParamDefault, %object
	.size	AVS2_WeightQuantParamDefault, 6
AVS2_WeightQuantParamDefault:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.space	2
	.type	AVS2_WeightQuantParamBase1, %object
	.size	AVS2_WeightQuantParamBase1, 6
AVS2_WeightQuantParamBase1:
	.byte	67
	.byte	71
	.byte	71
	.byte	80
	.byte	80
	.byte	106
	.space	2
	.type	AVS2_WeightQuantParamBase2, %object
	.size	AVS2_WeightQuantParamBase2, 6
AVS2_WeightQuantParamBase2:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.space	2
	.type	AVS2_WQM_4x4Default, %object
	.size	AVS2_WQM_4x4Default, 16
AVS2_WQM_4x4Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	64
	.byte	68
	.byte	76
	.byte	80
	.byte	72
	.byte	76
	.byte	84
	.byte	96
	.type	AVS2_WQM_8x8Default, %object
	.size	AVS2_WQM_8x8Default, 64
AVS2_WQM_8x8Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	68
	.byte	72
	.byte	76
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	84
	.byte	92
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	80
	.byte	88
	.byte	100
	.byte	64
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	100
	.byte	112
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	112
	.byte	-128
	.byte	76
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	116
	.byte	-124
	.byte	-104
	.byte	96
	.byte	100
	.byte	104
	.byte	116
	.byte	124
	.byte	-116
	.byte	-92
	.byte	-68
	.byte	104
	.byte	108
	.byte	116
	.byte	-128
	.byte	-104
	.byte	-84
	.byte	-64
	.byte	-40
	.type	Avs2_AlfRegionTable, %object
	.size	Avs2_AlfRegionTable, 16
Avs2_AlfRegionTable:
	.byte	0
	.byte	1
	.byte	4
	.byte	5
	.byte	15
	.byte	2
	.byte	3
	.byte	6
	.byte	14
	.byte	11
	.byte	10
	.byte	7
	.byte	13
	.byte	12
	.byte	9
	.byte	8
	.type	__func__.14832, %object
	.size	__func__.14832, 24
__func__.14832:
	.ascii	"AVS2_IntraPictureHeader\000"
	.type	__func__.14850, %object
	.size	__func__.14850, 24
__func__.14850:
	.ascii	"AVS2_InterPictureHeader\000"
	.type	__func__.14987, %object
	.size	__func__.14987, 19
__func__.14987:
	.ascii	"AVS2_SetupFrameBuf\000"
	.space	1
	.type	__func__.15006, %object
	.size	__func__.15006, 19
__func__.15006:
	.ascii	"AVS2_SetupRefFrame\000"
	.space	1
	.type	__func__.15037, %object
	.size	__func__.15037, 17
__func__.15037:
	.ascii	"AVS2_CalDistance\000"
	.space	3
	.type	CSWTCH.74, %object
	.size	CSWTCH.74, 16
CSWTCH.74:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	__func__.15145, %object
	.size	__func__.15145, 19
__func__.15145:
	.ascii	"AVS2_PrepareDecode\000"
	.space	1
	.type	__func__.15162, %object
	.size	__func__.15162, 13
__func__.15162:
	.ascii	"AVS2DEC_Init\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"AVS2_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"Unkown\000" )
	.space	1
.LC2:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	" ----> Dump Dpb Status:\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"Pic %2d, Type %6s, Occupied %d, Ref %d, Disp %d, DO" )
	ASCII(.ascii	"I %d, POI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x\012" )
	ASCII(.ascii	"\000" )
.LC5:
	ASCII(.ascii	" ----> Dump End: Totoal Occupied Frame %d\012\012\000" )
.LC6:
	ASCII(.ascii	"User Data:\012\000" )
.LC7:
	ASCII(.ascii	"%s: cosume TotalPos(%d > %d)!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"Slice num out of slot: %d > %d\012\000" )
.LC9:
	ASCII(.ascii	"Stream ERROR: slice_vertical_position %d out of ran" )
	ASCII(.ascii	"ge [0, 0x8F].\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"Stream ERROR: alf_filter_num_minus1 %d > 15.\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"ALF ERROR: alf_region_distance %d out of range [1, " )
	ASCII(.ascii	"15].\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"ALF ERROR: alf_coef_luma_8 %d out of range [-1088, " )
	ASCII(.ascii	"1071].\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"ALF ERROR: alf_coef_luma_%d %d out of range [-64, 6" )
	ASCII(.ascii	"3].\012\000" )
.LC14:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma0_8 %d out of range [-108" )
	ASCII(.ascii	"8, 1071].\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma0_%d %d out of range [-64" )
	ASCII(.ascii	", 63].\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma1_8 %d out of range [-108" )
	ASCII(.ascii	"8, 1071].\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma1_%d %d out of range [-64" )
	ASCII(.ascii	", 63].\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"Intra stream ERROR: picture_output_delay out of ran" )
	ASCII(.ascii	"ge [0, 63], force 63.\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"Intra stream ERROR: force progressive_frame to 0 fo" )
	ASCII(.ascii	"r field_coded_sequence = 1\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"Intra stream ERROR: picture_qp %d out of range [0, " )
	ASCII(.ascii	"%d], force %d.\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"Intra stream ERROR: alpha_c_offset %d out of range " )
	ASCII(.ascii	"[-8, 8], force 0.\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"Intra stream ERROR: beta_offset %d out of range [-8" )
	ASCII(.ascii	", 8], force 0.\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"Intra stream ERROR: chroma_quant_param_delta_cb %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"Intra stream ERROR: chroma_quant_param_delta_cr %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"%s call AVS2_alf_parameter_set failed\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"Inter stream ERROR: picture_coding_type should not " )
	ASCII(.ascii	"equal 0.\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"Inter stream ERROR: picture_output_delay out of ran" )
	ASCII(.ascii	"ge [0, 63], force 63.\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"Inter stream ERROR: force progressive_frame to 1 fo" )
	ASCII(.ascii	"r progressive_sequence = 1\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"Inter stream ERROR: force progressive_frame to 0 fo" )
	ASCII(.ascii	"r field_coded_sequence = 1\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"Inter stream ERROR: picture_qp %d out of range [0, " )
	ASCII(.ascii	"%d], force %d.\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"Inter stream ERROR: alpha_c_offset %d out of range " )
	ASCII(.ascii	"[-8, 8], force 0.\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"Inter stream ERROR: beta_offset %d out of range [-8" )
	ASCII(.ascii	", 8], force 0.\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"Inter stream ERROR: chroma_quant_param_delta_cb %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"Inter stream ERROR: chroma_quant_param_delta_cr %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"%s ERROR: ucRefPicNum out of range [1, %d].\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"Sequence Header:\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"Stream ERROR: profile_id 0x%x unsupport.\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"Stream ERROR: level_id should not equal 0.\012\000" )
.LC39:
	ASCII(.ascii	"Stream ERROR: field_coded_sequence should be 0 when" )
	ASCII(.ascii	" progressive_sequence = 1\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"Stream ERROR: horizontal_size should not equal 0.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC41:
	ASCII(.ascii	"Stream ERROR: vertical_size should not equal 0.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC42:
	ASCII(.ascii	"Stream ERROR: chroma_format %d not support, only 4:" )
	ASCII(.ascii	"2:0 now.\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"Stream ERROR: sample_precision %d should equal to 8" )
	ASCII(.ascii	"/10\012\000" )
.LC44:
	ASCII(.ascii	"AVS2 sequence ERROR: ucBitDepth %d should equal to " )
	ASCII(.ascii	"8/10, and not less than sample_precision %d\012\000" )
.LC45:
	ASCII(.ascii	"Stream ERROR: aspect_ratio = 0 is forbidden!\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"Stream ERROR: frame_rate_code = 0 is forbidden!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC47:
	ASCII(.ascii	"Stream ERROR: num_of_rcs %d out of range [0, %d]\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC48:
	ASCII(.ascii	"MbWidth = %d, MbHeight = %d, don't support!\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"avs2 actual frame size(%dx%d) exeed max config(%dx%" )
	ASCII(.ascii	"d)\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"avs2 actual frame size(%dx%d) exceed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC51:
	ASCII(.ascii	"ERROR: partition fs memory failed!\012\000" )
.LC52:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance failed!\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"ERROR: AVS2_OutputOneFrame is err(%d)\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"Dump frame, POI: %d\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"NumOfRemovedPicture: %d\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"Target removal DOI[%d]: %d\012\000" )
.LC58:
	ASCII(.ascii	"Conflict: cur frame(Type %d, DOI %d, FspID %d, FsPh" )
	ASCII(.ascii	"y 0x%x, PmvPhy 0x%x) with frame(Type %d, Occupied %" )
	ASCII(.ascii	"d, UsedAsRef %d, DOI %d, FspID %d, FsPhy 0x%x, PmvP" )
	ASCII(.ascii	"hy 0x%x)\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"%s: Can't find non-occupied frame memory buffer!!!\012" )
	ASCII(.ascii	"\000" )
.LC60:
	ASCII(.ascii	"%s ERROR: get frame store fail!\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"%s ERROR: get image pointer fail!\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"Varify current frame DOI %d failed!\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"Can't find G or GB picture for the reference of S p" )
	ASCII(.ascii	"icture.\012\000" )
.LC64:
	ASCII(.ascii	"CurPic Doi %d cant find ref frame TargetDoi %d\012\000" )
.LC65:
	ASCII(.ascii	"Found ref num %d < num_of_reference_picture %d\012\000" )
.LC66:
	ASCII(.ascii	"%s ERROR: num_of_reference_picture %d out of range " )
	ASCII(.ascii	"[1, %d].\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"%s ERROR: pstRefFrmMem[0] = NULL or ucRefPicNum %d " )
	ASCII(.ascii	"out of range [1, %d].\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"line: %d pImage is null\012\000" )
	.space	3
.LC69:
	ASCII(.ascii	"ERROR: allocate vhb\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"AVS2_VIDEO_SEQUENCE_END_CODE\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"AVS2_VIDEO_EDIT_CODE\012\000" )
	.space	2
.LC72:
	ASCII(.ascii	"%s SliceNum %d invalid.\012\000" )
	.space	3
.LC73:
	ASCII(.ascii	"AVS2 unsupport output order %d, force dec order out" )
	ASCII(.ascii	"put.\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"%s get chan id failed!\012\000" )
.LC75:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC76:
	ASCII(.ascii	"I_PIC\000" )
	.space	2
.LC77:
	ASCII(.ascii	"P_PIC\000" )
	.space	2
.LC78:
	ASCII(.ascii	"B_PIC\000" )
	.space	2
.LC79:
	ASCII(.ascii	"F_PIC\000" )
	.space	2
.LC80:
	ASCII(.ascii	"S_PIC\000" )
	.space	2
.LC81:
	ASCII(.ascii	"G_PIC\000" )
	.space	2
.LC82:
	ASCII(.ascii	"GB_PIC\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
