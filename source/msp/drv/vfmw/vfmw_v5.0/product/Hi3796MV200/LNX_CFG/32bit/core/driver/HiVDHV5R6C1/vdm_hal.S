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
	.file	"vdm_hal.c"
	.text
	.align	2
	.type	VDMHAL_CalcPmvSlotLen.isra.0, %function
VDMHAL_CalcPmvSlotLen.isra.0:
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
	ldr	lr, .L10
	ldr	ip, [r1]
	ldr	r3, [r2]
	ldrb	r4, [lr]	@ zero_extendqisi2
	cmp	ip, #45
	cmple	r3, #36
	movle	lr, #64
	movgt	lr, #32
	cmp	r4, #1
	moveq	lr, #64
	cmp	r0, #16
	moveq	lr, r0
	beq	.L4
	cmp	r0, #17
	beq	.L9
.L4:
	mul	r0, ip, lr
	mul	r0, r3, r0
	add	r0, r0, #143
	bic	r0, r0, #127
	ldmfd	sp, {r4, fp, sp, pc}
.L9:
	mov	r0, #144
	mov	ip, #256
	mov	r3, r0
	str	ip, [r1]
	mov	lr, #64
	str	r0, [r2]
	ldr	ip, [r1]
	b	.L4
.L11:
	.align	2
.L10:
	.word	g_not_direct_8x8_inference_flag
	UNWIND(.fnend)
	.size	VDMHAL_CalcPmvSlotLen.isra.0, .-VDMHAL_CalcPmvSlotLen.isra.0
	.align	2
	.global	VDMHAL_V5R6C1_GetHalMemSize
	.type	VDMHAL_V5R6C1_GetHalMemSize, %function
VDMHAL_V5R6C1_GetHalMemSize:
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
	mov	r0, #6291456
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetHalMemSize, .-VDMHAL_V5R6C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V5R6C1_OpenHAL
	.type	VDMHAL_V5R6C1_OpenHAL, %function
VDMHAL_V5R6C1_OpenHAL:
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
	subs	r3, r0, #0
	beq	.L23
	ldmia	r3, {r6, r7}
	ldr	r8, [r3, #8]
	cmp	r6, #0
	beq	.L24
	cmp	r7, #6291456
	blt	.L25
	cmp	r8, #0
	bgt	.L26
	ldr	r4, .L27
	mov	r2, #268
	ldr	r10, .L27+4
	mov	r1, #0
	ldr	r5, .L27+8
	mla	r0, r2, r8, r4
	ldr	r3, [r10, #48]
	blx	r3
	movw	r2, #1228
	mul	r9, r2, r8
	mov	r1, #4
	str	r1, [r4]
	mov	r1, #0
	ldr	r3, [r10, #48]
	add	r4, r5, r9
	mov	r0, r4
	blx	r3
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L27+12
	mov	r3, r0
	mov	r2, r0
	str	r3, [r5, r9]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L27+16
	mov	r3, r0
	mov	r2, r0
	str	r3, [r4, #8]
	mov	r0, #22
	bl	dprint_vfmw
	add	ip, r6, #1020
	add	ip, ip, #3
	add	r3, r9, #36
	bic	ip, ip, #1020
	add	r1, r9, #876
	bic	ip, ip, #3
	add	r3, r5, r3
	add	r1, r5, r1
	add	r0, r7, r6
	mov	r2, ip
	rsb	r0, ip, r0
	mov	lr, #1024
	str	ip, [r4, #16]
	str	r0, [r4, #20]
	str	lr, [r4, #24]
.L19:
	str	r2, [r3, #4]!
	cmp	r3, r1
	add	r2, r2, #1280
	bne	.L19
	add	r3, ip, #274432
	add	ip, ip, #266240
	add	r1, ip, #41728
	movw	r2, #1228
	add	r1, r1, #255
	mov	r9, #210
	mla	r2, r2, r8, r5
	bic	r1, r1, #32512
	bic	r1, r1, #255
	add	ip, ip, #3072
	add	lr, r1, #4390912
	add	r5, r1, #1769472
	add	r10, lr, #37888
	add	r8, r5, #5248
	cmp	r8, r10
	rsbcs	r6, r6, r8
	rsbcc	r6, r6, r10
	add	r10, r1, #1081344
	cmp	r7, r6
	add	r10, r10, #12288
	str	r6, [fp, #-48]
	add	r6, r1, #2129920
	str	ip, [r2, #1088]
	add	ip, r1, #3178496
	str	r3, [r2, #1108]
	add	r3, r1, #4194304
	str	r1, [r2, #1156]
	mov	r0, #0
	str	r1, [r2, #1092]
	add	ip, ip, #12288
	str	r1, [r2, #1096]
	add	r3, r3, #45056
	str	r1, [r2, #1100]
	add	r5, r5, #2048
	str	r9, [r2, #1064]
	add	r9, r1, #45056
	str	r10, [r2, #1148]
	add	r10, r1, #4325376
	str	r9, [r2, #1144]
	add	r9, r1, #589824
	add	r1, r1, #1179648
	add	r6, r6, #12288
	add	r1, r1, #2048
	str	ip, [r2, #1160]
	str	r3, [r2, #1192]
	add	ip, r10, #47104
	add	r3, r9, #2048
	add	r10, r10, #50176
	str	ip, [r2, #1176]
	add	ip, lr, #33792
	str	r6, [r2, #1152]
	add	lr, lr, #1024
	str	r10, [r2, #1180]
	str	ip, [r2, #1184]
	str	r9, [r2, #1104]
	str	r9, [r2, #1112]
	str	r3, [r2, #1116]
	str	lr, [r2, #1204]
	str	lr, [r2, #1188]
	str	r1, [r2, #1120]
	str	r1, [r2, #1124]
	str	r8, [r2, #1136]
	str	r5, [r2, #1128]
	str	r5, [r2, #1132]
	str	r0, [r2, #1168]
	str	r0, [r2, #1140]
	bcc	.L20
	mov	r0, r4
	bl	H264HAL_V5R6C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V5R6C1_InitHal
	cmp	r0, #0
	mvnne	r0, #0
	bne	.L15
	adds	r0, r5, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L15:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L26:
	ldr	r1, .L27+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	mov	r3, r7
	ldr	r2, [fp, #-48]
	ldr	r1, .L27+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L15
.L24:
	mov	r0, r6
	ldr	r3, .L27+28
	ldr	r2, .L27+32
	ldr	r1, .L27+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L15
.L25:
	ldr	r3, .L27+40
	mov	r0, #0
	ldr	r2, .L27+32
	ldr	r1, .L27+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L15
.L23:
	ldr	r3, .L27+44
	ldr	r2, .L27+32
	ldr	r1, .L27+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L15
.L28:
	.align	2
.L27:
	.word	g_VdmExtParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LC5
	.word	.LC6
	.word	.LC4
	.word	.LC7
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC1
	.word	.LC3
	.word	.LC0
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_OpenHAL, .-VDMHAL_V5R6C1_OpenHAL
	.align	2
	.global	VDMHAL_V5R6C1_CloseHAL
	.type	VDMHAL_V5R6C1_CloseHAL, %function
VDMHAL_V5R6C1_CloseHAL:
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
	.size	VDMHAL_V5R6C1_CloseHAL, .-VDMHAL_V5R6C1_CloseHAL
	.align	2
	.global	VDMHAL_V5R6C1_CalcFsSize
	.type	VDMHAL_V5R6C1_CalcFsSize, %function
VDMHAL_V5R6C1_CalcFsSize:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 24
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
	sub	lr, r1, #32
	mov	ip, r1
	movw	r1, #8160
	cmp	lr, r1
	mov	r7, r0
	mov	r8, r2
	bhi	.L31
	sub	r2, r2, #32
	mov	r4, r8
	cmp	r2, r1
	bhi	.L31
	sub	r2, fp, #44
	add	r6, r8, #15
	add	r5, ip, #15
	sub	r1, fp, #52
	mov	r6, r6, asr #4
	ldr	r0, [fp, #4]
	str	r6, [r2, #-4]!
	mov	r5, r5, asr #4
	str	r3, [fp, #-60]
	str	ip, [fp, #-56]
	str	r5, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #4]
	ldr	ip, [fp, #-56]
	cmp	r3, #16
	ldr	r3, [fp, #-60]
	mov	r10, r0
	beq	.L51
	ldr	r2, [fp, #4]
	ldr	r9, .L56
	sub	r2, r2, #17
	cmp	r2, #1
	bls	.L52
	mov	r2, #0
	mov	r5, r5, asl #4
	mov	r1, r2
	add	r5, r5, #255
	add	r4, r8, #31
	str	r2, [fp, #-60]
	ldr	r2, [r9, r7, asl #2]
	bic	r5, r5, #255
	bic	r4, r4, #31
	str	r1, [fp, #-64]
.L35:
	ldr	r1, [r2, #1136]
	cmp	r1, #1
	movne	ip, #0
	strne	ip, [fp, #-56]
	movne	r8, ip
	beq	.L53
.L37:
	cmp	r3, #1
	beq	.L54
	ldr	r0, [fp, #-60]
	add	r1, r8, r8, lsl #1
	ldr	r3, [fp, #-64]
	mul	r4, r4, r5
	mul	r3, r3, r0
	add	r0, r4, r4, lsl #1
	add	r3, r3, r3, lsl #1
	mov	r6, r0, lsr #1
	add	r3, r6, r3, lsr #1
	add	r6, r3, r1, lsr #1
.L39:
	add	r3, r2, #471040
	ldr	r1, [r3, #888]
	cmp	r1, #0
	beq	.L55
.L40:
	add	r0, r2, #475136
	ldr	r1, [fp, #4]
	str	r6, [r0, #360]
	cmp	r1, #17
	ldr	r0, [fp, #-56]
	add	r1, r10, r10, lsr #31
	str	ip, [r3, #3240]
	mov	r1, r1, asr #1
	str	r1, [r3, #3276]
	str	r0, [r3, #3236]
	beq	.L41
	ldr	r1, [r3, #896]
	mov	r5, r5, asl #4
	cmp	r1, #32
	movge	r1, #32
	str	r1, [r3, #3280]
	ldr	r1, [r2, #568]
	str	r5, [r3, #3228]
	mov	r5, r5, lsr #1
	cmp	r1, #2
	str	r5, [r3, #3232]
	ldreq	r1, [r3, #900]
	streq	r1, [r3, #3280]
	ldr	r1, [fp, #4]
	sub	r1, r1, #16
	cmp	r1, #2
	add	r1, r4, r8
	str	r1, [r3, #3260]
	bls	.L43
.L44:
	ldr	r3, [r9, r7, asl #2]
	mov	r0, #1024
	add	r6, r6, #1056
	add	r2, r3, #475136
	add	r1, r10, r6
	str	r10, [r2, #364]
	str	r0, [r2, #372]
	ldrsb	r3, [r3, #44]
	cmp	r3, #1
	ldr	r3, [fp, #8]
	addeq	r1, r1, r0
	cmp	r3, #0
	beq	.L50
	str	r6, [r3, #4]
	mov	r2, #1024
	ldr	r3, [r9, r7, asl #2]
	mov	r0, #0
	ldr	ip, [fp, #8]
	add	r3, r3, #471040
	ldr	r3, [r3, #896]
	str	r10, [ip, #12]
	str	r3, [ip, #8]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #471040
	ldr	r3, [r3, #3280]
	str	r1, [ip]
	str	r2, [ip, #20]
	str	r3, [ip, #16]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #475136
	str	r6, [r3, #368]
.L33:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L41:
	mov	r5, r5, asl #4
	mov	r0, #1
	str	r5, [r3, #3228]
	add	r1, r4, r8
	mov	r5, r5, lsr r0
	str	r0, [r3, #3280]
	str	r5, [r3, #3232]
	str	r1, [r3, #3260]
.L43:
	ldr	r2, [r2, #1444]
	cmp	r2, #8
	ble	.L44
	ldr	r0, [fp, #-60]
	add	r8, r8, r8, lsl #1
	ldr	r1, [fp, #-64]
	add	r4, r4, r4, lsl #1
	mov	r8, r8, lsr #1
	add	r4, r8, r4, lsr #1
	str	r4, [r3, #3252]
	mul	r2, r0, r1
	mov	r1, r1, asl #5
	mov	r0, #31
	str	r1, [r3, #3244]
	ldr	r1, .L56+4
	str	r2, [r3, #3256]
	bl	dprint_vfmw
	b	.L44
.L55:
	ldr	r3, .L56+8
	movw	r0, #15512
	movt	r0, 7
	add	r0, r2, r0
	mov	r2, #1248
	str	ip, [fp, #-68]
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r9, r7, asl #2]
	ldr	ip, [fp, #-68]
	add	r3, r2, #471040
	b	.L40
.L54:
	mov	r3, r6, asl #5
	add	r6, r3, r6, lsl #4
	mul	r4, r4, r5
	mul	r6, r5, r6
	b	.L39
.L53:
	add	r1, ip, #2032
	add	ip, ip, #4080
	add	r1, r1, #15
	add	ip, ip, #14
	cmp	r1, #0
	movge	ip, r1
	adds	r1, r8, #63
	addmi	r8, r8, #126
	movpl	r8, r1
	mov	ip, ip, asr #11
	mov	r8, r8, asr #6
	mov	r1, ip, asl #4
	str	r1, [fp, #-56]
	mov	r8, r8, asl #5
	mul	r8, r1, r8
	mov	ip, r8
	b	.L37
.L51:
	ldr	r9, .L56
	add	r5, ip, #255
	bic	r5, r5, #255
	ldr	r2, [r9, r7, asl #2]
	ldr	r1, [r2, #1444]
	cmp	r1, #8
	ble	.L48
	add	r1, r8, #31
	mov	r0, r5, lsr #2
	bic	r1, r1, #31
	str	r0, [fp, #-64]
	str	r1, [fp, #-60]
	b	.L35
.L48:
	mov	r1, #0
	str	r1, [fp, #-60]
	str	r1, [fp, #-64]
	b	.L35
.L52:
	ldr	r2, [r9, r7, asl #2]
	add	r5, ip, #255
	add	r4, r8, #63
	bic	r5, r5, #255
	bic	r4, r4, #63
	ldr	r1, [r2, #1444]
	cmp	r1, #8
	ble	.L48
	mov	r1, r5, lsr #2
	str	r4, [fp, #-60]
	str	r1, [fp, #-64]
	b	.L35
.L31:
	ldr	r3, .L56+12
	mov	r0, #0
	ldr	r2, .L56+16
	ldr	r1, .L56+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L50:
	ldr	r0, [fp, #8]
	b	.L33
.L57:
	.align	2
.L56:
	.word	s_pstVfmwChan
	.word	.LC9
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalcFsSize, .-VDMHAL_V5R6C1_CalcFsSize
	.align	2
	.global	VDMHAL_V5R6C1_GetRpuSize
	.type	VDMHAL_V5R6C1_GetRpuSize, %function
VDMHAL_V5R6C1_GetRpuSize:
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
	mov	r0, #1024
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetRpuSize, .-VDMHAL_V5R6C1_GetRpuSize
	.align	2
	.global	VDMHAL_V5R6C1_CalcFsNum
	.type	VDMHAL_V5R6C1_CalcFsNum, %function
VDMHAL_V5R6C1_CalcFsNum:
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
	cmp	r3, #0
	mov	r2, r0
	beq	.L64
	cmp	r1, #17
	ldr	ip, .L66
	beq	.L65
	ldr	lr, [ip, r0, asl #2]
	add	r0, lr, #471040
	ldr	r1, [r0, #896]
	cmp	r1, #32
	movge	r1, #32
	str	r1, [r0, #3280]
	ldr	r1, [lr, #568]
	cmp	r1, #2
	ldreq	r1, [r0, #900]
	streq	r1, [r0, #3280]
.L63:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #0
	add	r1, r1, #471040
	ldr	r1, [r1, #896]
	str	r1, [r3, #8]
	ldr	r2, [ip, r2, asl #2]
	add	r2, r2, #471040
	ldr	r2, [r2, #3280]
	str	r2, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L65:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #1
	add	r1, r1, #471040
	str	r0, [r1, #3280]
	b	.L63
.L64:
	ldr	r2, .L66+4
	mov	r0, #1
	ldr	r1, .L66+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L67:
	.align	2
.L66:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+52
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalcFsNum, .-VDMHAL_V5R6C1_CalcFsNum
	.align	2
	.global	VDMHAL_V5R6C1_DynamicAllocFrame
	.type	VDMHAL_V5R6C1_DynamicAllocFrame, %function
VDMHAL_V5R6C1_DynamicAllocFrame:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r6, .L91
	mov	r8, r1
	mov	r4, r0
	mov	r7, r2
	mov	r5, r3
	ldr	r1, [r6, r0, asl #2]
	add	r1, r1, #471040
	add	r1, r1, #920
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	bne	.L89
.L69:
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #0
	mov	r1, #255
	add	r2, r2, #471040
	add	r2, r2, #920
.L70:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L70
	cmp	r8, #1920
	cmple	r7, #1088
	bgt	.L73
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L91
	ldr	r2, [r3, #36]
	cmp	r2, #24
	beq	.L73
	add	r3, r3, #475136
	ldr	r3, [r3, #996]
	cmp	r3, #0
	beq	.L90
.L73:
	ldr	r2, [r5, #8]
	ldr	r3, [r6, r4, asl #2]
.L72:
	ldr	r1, [r3, #1392]
	add	r3, r3, #471040
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #900]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L91
	ldr	r2, [r3, #568]
	subs	r0, r0, #17
	movne	r0, #1
	cmp	r2, #2
	movne	r0, #0
	cmp	r0, #0
	addne	r3, r3, #471040
	mov	r0, #1
	ldrne	r3, [r3, #900]
	strne	r3, [r5, #16]
	ldrne	r3, [r1, r4, asl #2]
	add	r1, r3, #475136
	add	r2, r3, #442368
	mov	r3, #0
	str	r3, [r1, #400]
	mov	r3, r7
	str	r0, [r2, #2056]
	mov	r2, r8
	str	r0, [r1, #940]
	mov	r0, #31
	ldr	ip, [r5, #8]
	ldr	lr, [r5, #16]
	ldr	r1, .L91+4
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L91+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L75
	ldr	r0, [r5, #12]
	mov	r3, #28
	ldr	r10, [r5, #8]
	sub	r2, fp, #72
	ldr	r9, [r5, #4]
	mov	r1, #121
	ldr	lr, [r5, #16]
	ldr	r5, [r5, #20]
	str	r0, [fp, #-60]
	mov	r0, r4
	str	r8, [fp, #-52]
	str	r7, [fp, #-48]
	str	r10, [fp, #-72]
	str	r9, [fp, #-68]
	str	lr, [fp, #-64]
	str	r5, [fp, #-56]
	blx	ip
.L75:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L91+12
	mov	r2, #528
	add	r0, r0, #475136
	add	r0, r0, #408
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #0
	mov	r0, r4
	add	r3, r3, #475136
	str	r2, [r3, #936]
	bl	FSP_ClearContextAll
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L89:
	ldr	r1, .L91+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L69
.L90:
	ldr	r2, [r5, #8]
	add	r2, r2, #4
	str	r2, [r5, #8]
	ldr	r3, [r1, r4, asl #2]
	b	.L72
.L92:
	.align	2
.L91:
	.word	s_pstVfmwChan
	.word	.LC12
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_DynamicAllocFrame, .-VDMHAL_V5R6C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R6C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R6C1_DynamicAllocFrame_Only:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	ip, .L98
	ldr	lr, [r3, #8]
	mov	r4, r3
	mov	r7, r0
	mov	r3, r2
	ldr	ip, [ip, r0, asl #2]
	mov	r6, r1
	mov	r5, r2
	mov	r0, #31
	add	ip, ip, #471040
	mov	r2, r1
	ldr	r1, .L98+4
	str	lr, [ip, #900]
	ldr	ip, [r4, #8]
	ldr	lr, [r4, #16]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L98+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L93
	ldr	r9, [r4, #8]
	mov	r0, r7
	ldr	r10, [r4, #4]
	mov	r3, #28
	ldr	r8, [r4, #16]
	sub	r2, fp, #72
	ldr	r7, [r4, #12]
	mov	r1, #122
	ldr	lr, [r4, #20]
	str	r6, [fp, #-52]
	str	r5, [fp, #-48]
	str	r9, [fp, #-72]
	str	r10, [fp, #-68]
	str	r8, [fp, #-64]
	str	r7, [fp, #-60]
	str	lr, [fp, #-56]
	blx	ip
.L93:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L99:
	.align	2
.L98:
	.word	s_pstVfmwChan
	.word	.LC13
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_DynamicAllocFrame_Only, .-VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem_Normal
	.type	VDMHAL_V5R6C1_ArrangeMem_Normal, %function
VDMHAL_V5R6C1_ArrangeMem_Normal:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 48
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
	cmp	r1, #20
	mov	r4, r0
	mov	r6, r1
	mov	r0, #0
	mov	r8, r2
	mov	r9, r3
	str	r0, [fp, #-68]
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r0, [fp, #-56]
	str	r0, [fp, #-52]
	str	r0, [fp, #-48]
	bhi	.L136
	ldr	r5, .L145
	ldr	r1, [r5, r4, asl #2]
	add	r2, r1, #471040
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #892]
	cmp	r3, #2
	str	r2, [fp, #-72]
	beq	.L137
	bics	r3, r6, #16
	moveq	r3, #1
	movne	r3, #0
	cmp	r6, #18
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L138
.L105:
	sub	r3, r6, #17
	clz	r3, r3
	mov	r3, r3, lsr #5
.L106:
	ldr	ip, [r1, #1148]
	mov	r2, r3
	str	r3, [r1, #1136]
	mov	r0, #1
	ldr	r3, [r1, #1140]
	str	ip, [sp, #4]
	ldr	ip, [r1, #1144]
	ldr	r1, .L145+4
	str	ip, [sp]
	bl	dprint_vfmw
.L104:
	sub	r7, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r6
	mov	r0, r4
	mov	r3, r7
	bl	VDMHAL_V5R6C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r7, [sp, #4]
	mov	r2, r9
	str	r6, [sp]
	mov	r1, r8
	mov	r10, r0
	mov	r0, r4
	bl	VDMHAL_V5R6C1_CalcFsSize
	orrs	r3, r0, r10
	bne	.L139
	ldr	r1, [fp, #-72]
	ldr	ip, [r5, r4, asl #2]
	ldr	r6, [fp, #-68]
	add	r3, ip, #471040
	ldr	r2, .L145
	cmp	r1, r6
	ldr	r10, [r3, #896]
	ldr	r1, [r3, #912]
	beq	.L140
.L109:
	str	r1, [sp, #4]
	mov	r3, r6
	ldr	r2, .L145+8
	mov	r0, #31
	ldr	r1, .L145+12
	str	r10, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, r4, asl #2]
	mov	r1, r8
	mov	r0, r4
	add	r3, r3, #471040
	ldr	r2, [r3, #888]
	str	r6, [r3, #892]
	mov	r3, r7
	cmp	r2, #0
	mov	r2, r9
	beq	.L141
	bl	VDMHAL_V5R6C1_DynamicAllocFrame_Only
.L112:
	ldr	ip, [r5, r4, asl #2]
	mov	r3, r10
	mov	r2, r6
	ldr	r1, .L145+16
	add	ip, ip, #471040
	mov	r0, #31
	ldr	ip, [ip, #912]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L145+20
	ldr	r4, [r5, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #475136
	blx	r3
	mov	r3, #2
	str	r0, [r4, #376]
.L102:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L140:
	cmp	r1, #1
	beq	.L109
	ldr	r0, [r3, #888]
	cmp	r0, #1
	beq	.L109
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L142
	add	r1, ip, #475136
	cmp	r10, #0
	movw	r0, #15512
	ldr	r1, [r1, #360]
	movt	r0, 7
	movne	r2, ip
	str	r1, [fp, #-72]
	add	r1, ip, r0
	str	r1, [fp, #-80]
	beq	.L143
.L114:
	add	r2, r2, #471040
	ldr	r2, [r2, #900]
	cmp	r2, #30
	bgt	.L144
.L115:
	str	r2, [r3, #3272]
	mov	r0, #8
	str	r3, [fp, #-76]
	ldr	r3, .L145+20
	str	ip, [fp, #-84]
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r1, [r5, r4, asl #2]
	ldr	r3, [fp, #-76]
	add	r10, r1, #475136
	ldr	ip, [fp, #-84]
	ldr	r2, [r10, #400]
	cmp	r2, #0
	beq	.L120
	ldr	r2, [r3, #3284]
	movw	r7, #53049
	movw	r0, #15976
	movt	r7, 1
	add	r7, r2, r7
	add	r1, r1, #471040
	mov	lr, r2, asl #4
	movt	r0, 7
	sub	lr, lr, r2, asl #2
	ldr	r6, [r3, #3280]
	add	r0, lr, r0
	add	r2, r2, #1
	add	r1, r1, #952
	add	r0, ip, r0
	add	r7, ip, r7, lsl #2
	mov	lr, #0
	mov	r9, #1
	mov	r8, r2
	str	ip, [fp, #-76]
	str	r4, [fp, #-84]
.L119:
	ldr	r2, [r1]
	add	ip, r8, lr
	ldr	r4, [r1, #-20]
	add	lr, lr, #1
	add	r2, r2, #1020
	strb	r9, [r0, #8]
	add	r2, r2, #3
	add	r0, r0, #12
	str	r4, [r0, #-8]
	bic	r2, r2, #1020
	ldr	r4, [fp, #-72]
	bic	r2, r2, #3
	str	r2, [r0, #-12]
	add	r2, r2, r4
	str	r2, [r7, #4]!
	str	ip, [r3, #3284]
	ldr	r2, [r1, #-28]
	cmp	r2, #255
	beq	.L117
	ldr	ip, [r3, #3292]
	add	r4, ip, #1
	mov	r2, ip, asl #4
	sub	r2, r2, ip, asl #2
	ldr	ip, [r1, #16]
	add	r2, r3, r2
	str	ip, [r2, #4072]
	str	r4, [r3, #3292]
.L117:
	ldr	r2, [r3, #3288]
	cmp	r2, r6
	bcs	.L118
	ldr	r4, [r1, #-24]
	ldr	ip, [fp, #-76]
	cmp	r4, #255
	add	ip, ip, r2, lsl #3
	add	r2, r2, #1
	ldrne	r4, [r1, #32]
	add	ip, ip, #471040
	strneb	r9, [ip, #3436]
	strne	r4, [ip, #3432]
	strne	r2, [r3, #3288]
.L118:
	ldr	r2, [r10, #400]
	add	r1, r1, #72
	cmp	lr, r2
	bcc	.L119
	ldr	r4, [fp, #-84]
.L120:
	ldr	r3, .L145+20
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	ldr	r2, .L145+20
	mov	r1, #1
	add	r3, r3, #475136
	mov	r0, #8
	str	r1, [r3, #404]
	ldr	r2, [r2, #16]
	blx	r2
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L141:
	bl	VDMHAL_V5R6C1_DynamicAllocFrame
	b	.L112
.L138:
	cmp	r9, #2160
	cmplt	r8, #3840
	movge	r3, #1
	bge	.L106
	b	.L105
.L137:
	mvn	r3, #0
	str	r0, [r1, #1136]
	str	r0, [r1, #1140]
	str	r3, [r1, #1144]
	str	r3, [r1, #1148]
	b	.L104
.L143:
	ldr	r1, .L145+24
	mov	r0, #31
	str	r3, [fp, #-88]
	str	r2, [fp, #-84]
	str	ip, [fp, #-76]
	bl	dprint_vfmw
	ldr	r2, [fp, #-84]
	ldr	ip, [fp, #-76]
	ldr	r3, [fp, #-88]
	ldr	r2, [r2, r4, asl #2]
	b	.L114
.L144:
	ldr	r1, .L145+28
	mov	r0, #31
	str	r3, [fp, #-84]
	str	ip, [fp, #-76]
	bl	dprint_vfmw
	ldr	r1, [r5, r4, asl #2]
	mov	r0, #30
	mov	r2, r0
	ldr	r3, [fp, #-84]
	add	r1, r1, #471040
	ldr	ip, [fp, #-76]
	str	r0, [r1, #900]
	b	.L115
.L136:
	ldr	r3, .L145+32
	ldr	r2, .L145+36
	ldr	r1, .L145+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L102
.L139:
	ldr	r1, .L145+44
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L102
.L142:
	ldr	r3, .L145+48
	mov	r0, r1
	ldr	r2, .L145+52
	ldr	r1, .L145+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L102
.L146:
	.align	2
.L145:
	.word	s_pstVfmwChan
	.word	.LC15
	.word	.LANCHOR0+108
	.word	.LC17
	.word	.LC18
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LC21
	.word	.LC14
	.word	.LANCHOR0+76
	.word	.LC1
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+140
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem_Normal, .-VDMHAL_V5R6C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem_Specific
	.type	VDMHAL_V5R6C1_ArrangeMem_Specific, %function
VDMHAL_V5R6C1_ArrangeMem_Specific:
	UNWIND(.fnstart)
	@ args = 28, pretend = 0, frame = 40
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
	subs	r6, r2, #0
	mov	r4, r3
	mov	r10, r1
	ldr	r3, [fp, #12]
	ldr	r7, [fp, #28]
	beq	.L212
	ldr	r2, [fp, #4]
	sub	r1, r2, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L150
	ldr	r1, [fp, #8]
	sub	r1, r1, #32
	cmp	r1, r2
	bhi	.L150
	cmp	r7, #0
	beq	.L213
	ldr	lr, .L221
	cmp	r3, #20
	str	r0, [fp, #-60]
	mov	r2, #1232
	mov	r1, #0
	mov	r0, r7
	ldr	r8, [lr, #48]
	movge	r3, #20
	str	r3, [fp, #-56]
	blx	r8
	ldr	r3, [fp, #8]
	sub	r2, fp, #44
	mov	r0, r10
	add	r1, r3, #15
	ldr	r3, [fp, #4]
	add	r8, r3, #15
	mov	r5, r1, asr #4
	sub	r1, fp, #52
	str	r5, [r2, #-4]!
	mov	r8, r8, asr #4
	str	r8, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #-56]
	ldr	ip, [fp, #-60]
	mul	r1, r3, r0
	mov	r9, r0
	cmp	r1, r4
	ldrge	r3, .L221+4
	bge	.L211
	add	r2, r6, #1020
	rsb	r1, r1, r4
	add	r2, r2, #3
	cmp	r10, #16
	bic	r4, r2, #1020
	add	r2, r0, r0, lsr #31
	bic	r4, r4, #3
	str	r3, [r7, #56]
	rsb	r3, r6, r4
	mov	r2, r2, asr #1
	str	r3, [fp, #-68]
	rsb	r3, r3, r1
	str	r2, [r7, #52]
	str	r3, [fp, #-72]
	beq	.L214
	sub	r3, r10, #17
	cmp	r3, #1
	bls	.L215
	mov	r8, r8, asl #4
	ldr	r3, [fp, #8]
	add	r8, r8, #255
	cmp	ip, #0
	bic	r8, r8, #255
	add	r3, r3, #31
	bic	r3, r3, #31
	str	r3, [fp, #-56]
	mov	r3, r8, asl #4
	str	r3, [r7, #4]
	mov	r3, r8, asl #3
	str	r3, [r7, #8]
	blt	.L188
	ldr	r3, .L221+8
	mov	r2, #0
	str	r2, [fp, #-60]
	str	r2, [fp, #-64]
.L183:
	ldr	r3, [r3, ip, asl #2]
	ldr	r3, [r3, #1136]
	cmp	r3, #1
	movne	r2, #0
	movne	r1, r2
	movne	r3, r2
	beq	.L216
.L158:
	ldr	r0, [fp, #20]
	str	r1, [r7, #12]
	cmp	r0, #1
	str	r2, [r7, #16]
	beq	.L217
	ldr	r1, [fp, #-64]
	add	r5, r3, r3, lsl #1
	ldr	r2, [fp, #-60]
	mul	r2, r2, r1
	ldr	r1, [fp, #-56]
	mul	r1, r8, r1
	add	r2, r2, r2, lsl #1
	add	r2, r2, r2, lsr #31
	add	r1, r1, r1, lsl #1
	mov	r2, r2, asr #1
	add	r2, r2, r1, asr #1
	add	r5, r2, r5, lsr #1
.L160:
	ldr	r2, [fp, #24]
	cmp	r2, #0
	blt	.L161
	mov	r0, r2
	str	r3, [fp, #-80]
	bl	VCTRL_GetChanWidth
	str	r0, [fp, #-76]
	ldr	r0, [fp, #24]
	bl	VCTRL_GetChanHeight
	ldr	ip, [fp, #-76]
	cmn	r0, #1
	cmnne	ip, #1
	moveq	r3, #1
	movne	r3, #0
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-80]
	beq	.L218
	ldr	r2, [fp, #20]
	add	ip, ip, #15
	bic	ip, ip, #15
	add	r1, r0, #15
	cmp	r2, #1
	add	r2, ip, #255
	bic	r1, r1, #15
	bic	r2, r2, #255
	beq	.L219
	ldr	r0, .L221+8
	ldr	lr, [fp, #24]
	ldr	r0, [r0, lr, asl #2]
	ldr	r0, [r0, #1136]
	cmp	r0, #1
	beq	.L165
	adds	r0, r1, #63
	ldr	lr, [fp, #-76]
	addmi	r0, r1, #126
	mov	r0, r0, asr #6
.L166:
	ldr	r1, [fp, #-60]
	ldr	ip, [fp, #-64]
	mul	r2, r0, r2
	mul	r1, r1, ip
	mov	r0, r2, asl #7
	sub	r2, r0, r2, asl #5
	add	r1, r1, r1, lsl #1
	add	r1, r1, r1, lsr #31
	add	r2, r2, r1, asr #1
	add	lr, r2, lr
.L164:
	cmp	r5, lr
	ldrgt	r3, .L221+12
	bgt	.L211
	ldr	ip, [fp, #24]
.L161:
	ldr	r2, [fp, #-56]
	mul	r8, r8, r2
	sub	r2, r10, #16
	cmp	r2, #1
	add	r2, r8, r3
	str	r2, [r7, #36]
	bls	.L220
	ldr	r3, [fp, #16]
	cmp	r3, #0
	beq	.L170
	cmp	r10, #3
	cmpne	r10, #0
	strne	ip, [fp, #-56]
	beq	.L168
.L210:
	cmp	r3, #32
	mov	r1, r5
	ldr	r0, [fp, #-72]
	movlt	r8, r3
	movge	r8, #32
	bl	__aeabi_idiv
	ldr	ip, [fp, #-56]
	cmp	r8, r0
	movge	r3, r0
	movlt	r3, r8
	cmp	r3, #0
	str	r3, [r7, #48]
	ldrne	r0, [r7, #60]
	movne	r1, r7
	movne	r2, #0
	beq	.L169
.L174:
	add	r2, r2, #1
	str	r4, [r1, #464]
	cmp	r2, r3
	add	r4, r4, r5
	add	r1, r1, #12
	bne	.L174
	ldr	r2, [fp, #-68]
	mov	r1, #0
	mla	r5, r3, r5, r2
	add	r2, r0, r3
	add	r0, r7, #76
	str	r2, [r7, #60]
	add	r2, r5, r6
.L176:
	add	r1, r1, #1
	str	r2, [r0, #4]!
	cmp	r1, r3
	add	r2, r2, #32
	bne	.L176
	ldr	lr, [r7, #56]
	add	r5, r5, r3, lsl #5
	add	r6, r5, r6
	cmp	lr, #0
	beq	.L181
	ldr	r4, [r7, #64]
	mov	r0, r7
	mov	r1, r6
	mov	r2, #0
.L180:
	add	r2, r2, #1
	str	r1, [r0, #208]
	cmp	r2, lr
	add	r1, r1, r9
	add	r0, r0, #8
	bne	.L180
	add	r2, r4, lr
	str	r2, [r7, #64]
.L181:
	mla	r9, lr, r9, r5
	cmp	ip, #0
	str	r9, [r7]
	blt	.L179
	ldr	r2, .L221+8
	ldr	r2, [r2, ip, asl #2]
	cmp	r2, #0
	beq	.L179
	cmp	r3, #0
	add	r6, r9, r6
	beq	.L179
	mov	r1, r7
	mov	r2, #0
.L182:
	add	r2, r2, #1
	str	r6, [r1, #848]
	cmp	r2, r3
	add	r6, r6, #1024
	add	r1, r1, #12
	bne	.L182
.L179:
	mov	r0, #0
	add	r9, r9, r3, lsl #10
	str	r9, [r7]
.L208:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldr	r1, [fp, #16]
	mov	r2, r3, lsr #1
	ldr	r0, [fp, #-64]
	add	r3, r3, r3, lsl #1
	cmp	r1, #0
	ldr	r1, [fp, #-60]
	add	r8, r8, r8, lsl #1
	mov	r3, r3, lsr #1
	mla	r2, r1, r0, r2
	add	r8, r3, r8, asr #1
	mov	r3, r1, asl #4
	str	r8, [r7, #28]
	str	r3, [r7, #20]
	str	r2, [r7, #32]
	bne	.L168
.L170:
	mov	r3, #0
	str	r3, [r7, #48]
.L169:
	ldr	r3, .L221+16
.L211:
	ldr	r2, .L221+20
	mov	r0, #0
	ldr	r1, .L221+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L168:
	str	ip, [fp, #-56]
	ldr	r3, [fp, #16]
	b	.L210
.L214:
	ldr	r3, [fp, #4]
	cmp	ip, #0
	add	r8, r3, #255
	bic	r8, r8, #255
	blt	.L155
	ldr	r3, .L221+8
	str	ip, [fp, #-56]
	ldr	r0, [r3, ip, asl #2]
	str	r3, [fp, #-60]
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	IsMain10Profile
	ldr	ip, [fp, #-56]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	beq	.L185
	ldr	r1, [fp, #8]
	cmp	r8, #0
	add	r2, r8, #3
	add	r1, r1, #31
	movge	r2, r8
	bic	r1, r1, #31
	str	r1, [fp, #-64]
	ldr	r1, [fp, #8]
	mov	r2, r2, asr #2
	str	r2, [fp, #-60]
	str	r1, [fp, #-56]
	b	.L156
.L217:
	mov	r5, r5, asl #4
	mul	r5, r8, r5
	add	r5, r5, r5, lsl #1
	b	.L160
.L215:
	ldr	r3, [fp, #4]
	cmp	ip, #0
	add	r8, r3, #255
	ldr	r3, [fp, #8]
	bic	r8, r8, #255
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [fp, #-56]
	blt	.L186
	ldr	r3, .L221+8
	ldr	r2, [r3, ip, asl #2]
	ldr	r2, [r2, #1444]
	cmp	r2, #8
	ble	.L187
	ldr	r1, [fp, #-56]
	cmp	r8, #0
	add	r2, r8, #3
	movge	r2, r8
	mov	r2, r2, asr #2
	str	r1, [fp, #-64]
	str	r2, [fp, #-60]
.L156:
	mov	r2, r8, asl #4
	str	r2, [r7, #4]
	mov	r2, r8, asl #3
	str	r2, [r7, #8]
	b	.L183
.L186:
	ldr	r3, [fp, #-56]
	str	r3, [fp, #8]
.L155:
	ldr	r3, [fp, #8]
	mov	r2, #0
	mov	r0, r8, asl #4
	mov	r1, r2
	str	r0, [r7, #4]
	mov	r0, r8, asl #3
	str	r3, [fp, #-56]
	mov	r3, r2
	str	r2, [fp, #-60]
	str	r2, [fp, #-64]
	str	r0, [r7, #8]
	b	.L158
.L216:
	sub	r2, r10, #17
	ldr	r3, [fp, #4]
	clz	r2, r2
	mov	r2, r2, lsr #5
	cmp	r3, #1920
	orrgt	r2, r2, #1
	cmp	r2, #0
	moveq	r1, r2
	moveq	r3, r2
	beq	.L158
	add	r3, r3, #2032
	ldr	r2, [fp, #4]
	add	r3, r3, #15
	cmp	r3, #0
	add	r1, r2, #4080
	add	r1, r1, #14
	ldr	r2, [fp, #8]
	movge	r1, r3
	ldr	r3, [fp, #8]
	mov	r1, r1, asr #11
	adds	r3, r3, #63
	addmi	r2, r2, #126
	movpl	r2, r3
	mov	r1, r1, asl #4
	mov	r3, r2, asr #6
	mov	r3, r3, asl #5
	mul	r3, r1, r3
	mov	r2, r3
	b	.L158
.L219:
	mul	lr, r1, r2
	add	lr, lr, lr, lsl #1
	b	.L164
.L188:
	mov	r2, #0
	str	r2, [fp, #-60]
	mov	r1, r2
	str	r2, [fp, #-64]
	mov	r3, r2
	b	.L158
.L165:
	add	lr, ip, #2032
	adds	r0, r1, #63
	add	lr, lr, #15
	addmi	r0, r1, #126
	add	ip, ip, #4080
	cmp	lr, #0
	add	ip, ip, #14
	mov	r0, r0, asr #6
	movge	ip, lr
	mov	ip, ip, asr #11
	mov	lr, r0, asl #7
	sub	lr, lr, r0, asl #5
	mov	r1, ip, asl #4
	mul	lr, r1, lr
	mov	lr, lr, lsr #1
	b	.L166
.L185:
	ldr	r1, [fp, #8]
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r1, [fp, #-56]
	b	.L156
.L187:
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-60]
	b	.L156
.L150:
	ldr	r3, .L221+28
	b	.L211
.L212:
	mov	r0, r6
	ldr	r3, .L221+32
	ldr	r2, .L221+20
	ldr	r1, .L221+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L208
.L218:
	ldr	r1, .L221+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L208
.L213:
	mov	r0, r7
	ldr	r3, .L221+40
	ldr	r2, .L221+20
	ldr	r1, .L221+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L208
.L222:
	.align	2
.L221:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	s_pstVfmwChan
	.word	.LC26
	.word	.LC27
	.word	.LANCHOR0+176
	.word	.LC1
	.word	.LC8
	.word	.LC22
	.word	.LC25
	.word	.LC23
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem_Specific, .-VDMHAL_V5R6C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem
	.type	VDMHAL_V5R6C1_ArrangeMem, %function
VDMHAL_V5R6C1_ArrangeMem:
	UNWIND(.fnstart)
	@ args = 20, pretend = 0, frame = 8
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
	ldr	r4, [fp, #16]
	mov	r10, r0
	mov	r5, r2
	cmn	r4, #2
	mov	r6, r3
	ldmib	fp, {r7, ip}
	ldr	r8, [fp, #12]
	ldr	r9, [fp, #20]
	beq	.L226
	cmp	r4, #0
	blt	.L227
	mov	r0, r4
	str	ip, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r3, .L230
	ldr	r1, [fp, #-48]
	ldr	ip, [fp, #-52]
	ldr	r3, [r3, r4, asl #2]
	ldr	r3, [r3, #1384]
	cmp	r3, #1
	beq	.L229
.L225:
	mov	r3, r1
	str	r9, [sp, #24]
	mov	r1, r0
	str	r4, [sp, #20]
	mov	r2, r10
	str	r8, [sp, #16]
	str	ip, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V5R6C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L227:
	mov	r0, #21
	b	.L225
.L226:
	mov	r0, #16
	b	.L225
.L229:
	mov	r1, r0
	str	r9, [fp, #12]
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V5R6C1_ArrangeMem_Normal
.L231:
	.align	2
.L230:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem, .-VDMHAL_V5R6C1_ArrangeMem
	.align	2
	.global	VDMHAL_V5R6C1_ResetVdm
	.type	VDMHAL_V5R6C1_ResetVdm, %function
VDMHAL_V5R6C1_ResetVdm:
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
	subs	r5, r0, #0
	mov	r0, #0
	ble	.L233
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L250
	ldr	r1, .L250+4
	bl	dprint_vfmw
.L232:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L233:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L248
	movw	r10, #1228
	ldr	r6, .L250+8
	mul	r10, r10, r5
	ldr	r3, [r6, r10]
	add	r2, r3, #61440
	ldr	r7, [r3, #36]
	ldr	r3, [r2, #2052]
	tst	r3, #3
	str	r3, [fp, #-48]
	beq	.L232
	ldr	r4, .L250+12
	mov	r9, r6
	mov	r8, #0
	ldr	r3, [r4, #112]
	blx	r3
	ldr	r3, [r9, r10]!
	add	r3, r3, #61440
	ldr	r1, [r3, #2060]
	uxtb	r2, r1
	str	r1, [fp, #-48]
	orr	r2, r2, #2
	strb	r2, [fp, #-48]
	ldr	r2, [fp, #-48]
	str	r2, [r3, #2060]
	b	.L238
.L249:
	add	r8, r8, #1
	cmp	r8, #1000
	beq	.L239
.L238:
	ldr	r3, [r4, #116]
	mov	r0, #30
	blx	r3
	ldr	r2, [r9]
	add	r2, r2, #61440
	ldr	r2, [r2, #2064]
	tst	r2, #2
	str	r2, [fp, #-48]
	beq	.L249
	cmp	r8, #1000
	bge	.L239
	mov	r3, r5
	ldr	r2, .L250
	ldr	r1, .L250+16
	mov	r0, #0
	bl	dprint_vfmw
.L241:
	movw	r3, #1228
	ldr	r1, [r4, #112]
	mul	r5, r3, r5
	ldr	r2, [r6, r5]
	add	r2, r2, #61440
	ldr	r3, [r2, #2060]
	str	r3, [fp, #-48]
	bfc	r3, #1, #1
	strb	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	str	r3, [r2, #2060]
	blx	r1
	ldr	r3, [r6, r5]
	str	r7, [r3, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L239:
	mov	r3, r5
	ldr	r2, .L250
	ldr	r1, .L250+20
	mov	r0, #0
	bl	dprint_vfmw
	b	.L241
.L248:
	ldr	r1, .L250+24
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L251:
	.align	2
.L250:
	.word	.LANCHOR0+212
	.word	.LC28
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ResetVdm, .-VDMHAL_V5R6C1_ResetVdm
	.align	2
	.global	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R6C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R6C1_SetSmmuPageTableAddr:
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
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, .L258
	mov	r4, r0
	ldr	ip, [r3, #188]
	cmp	ip, #0
	beq	.L252
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	ip
	cmp	r4, #0
	bne	.L254
	ldr	r3, .L258+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L252:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L254:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L258+8
	ldr	r1, .L258+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L258+8
	ldr	r1, .L258+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L258+8
	ldr	r1, .L258+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L259:
	.align	2
.L258:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+236
	.word	.LC32
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_SetSmmuPageTableAddr, .-VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V5R6C1_EnableSmmu
	.type	VDMHAL_V5R6C1_EnableSmmu, %function
VDMHAL_V5R6C1_EnableSmmu:
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
	ldr	r3, .L261
	mov	r2, #8
	movt	r2, 3
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L262:
	.align	2
.L261:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_EnableSmmu, .-VDMHAL_V5R6C1_EnableSmmu
	.align	2
	.global	VDMHAL_V5R6C1_GlbResetX
	.type	VDMHAL_V5R6C1_GlbResetX, %function
VDMHAL_V5R6C1_GlbResetX:
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
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L282
	cmp	r4, #0
	ble	.L283
	mov	r2, #1
	mov	r3, r4
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L287
	ldr	r1, .L287+4
	bl	dprint_vfmw
	ldrb	r5, [fp, #-32]	@ zero_extendqisi2
	and	r5, r5, #3
	cmp	r5, #1
	beq	.L284
.L263:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L283:
	movw	r5, #1228
	ldr	r7, .L287+8
	mul	r5, r5, r4
	ldr	r3, [r7, r5]
	add	r3, r3, #61440
	ldr	r3, [r3, #2052]
	and	r2, r3, #3
	cmp	r2, #1
	str	r3, [fp, #-32]
	bne	.L263
	ldr	r6, .L287+12
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r7, r5]
	add	r3, r3, #61440
	ldr	r1, [r3, #2060]
	uxtb	r2, r1
	str	r1, [fp, #-32]
	orr	r2, r2, #1
	strb	r2, [fp, #-32]
	ldr	r2, [fp, #-32]
	str	r2, [r3, #2060]
	b	.L278
.L284:
	ldr	r6, .L287+12
	ldr	r3, [r6, #112]
	blx	r3
	mov	r3, r4
	ldr	r2, .L287
	mov	r0, #32
	ldr	r1, .L287+4
	str	r5, [sp]
	bl	dprint_vfmw
	ldrb	ip, [fp, #-32]	@ zero_extendqisi2
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L287
	mov	r0, #32
	ldr	r1, .L287+16
	orr	ip, ip, #1
	strb	ip, [fp, #-32]
	bl	dprint_vfmw
.L278:
	ldr	r3, .L287+8
	movw	r7, #1228
	mov	r5, #0
	mla	r7, r7, r4, r3
	b	.L273
.L270:
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r3, [fp, #-32]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L272
.L285:
	add	r5, r5, #1
	cmp	r5, #1000
	beq	.L274
.L273:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	cmp	r4, #0
	mov	ip, #1
	mov	r3, r4
	ldr	r2, .L287
	mov	r0, #32
	ldr	r1, .L287+4
	bgt	.L270
	ldr	r3, [r7]
	add	r3, r3, #61440
	ldr	r3, [r3, #2064]
	str	r3, [fp, #-32]
	ldrb	r3, [fp, #-32]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L285
.L272:
	cmp	r5, #1000
	bge	.L274
	mov	r3, r4
	ldr	r2, .L287
	ldr	r1, .L287+20
	mov	r0, #0
	bl	dprint_vfmw
.L276:
	cmp	r4, #0
	ble	.L286
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L287
	ldr	r1, .L287+4
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L287
	ldr	r1, .L287+16
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L274:
	mov	r3, r4
	ldr	r2, .L287
	ldr	r1, .L287+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L276
.L286:
	movw	r3, #1228
	ldr	r2, .L287+8
	mul	r4, r3, r4
	ldr	r2, [r2, r4]
	add	r2, r2, #61440
	ldr	r3, [r2, #2060]
	str	r3, [fp, #-32]
	bfc	r3, #0, #1
	strb	r3, [fp, #-32]
	ldr	r3, [fp, #-32]
	str	r3, [r2, #2060]
	b	.L263
.L282:
	mov	r3, #0
	ldr	r2, .L287
	movt	r3, 63683
	ldr	r1, .L287+28
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L288:
	.align	2
.L287:
	.word	.LANCHOR0+272
	.word	.LC34
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	.word	.LC36
	.word	.LC35
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GlbResetX, .-VDMHAL_V5R6C1_GlbResetX
	.align	2
	.global	VDMHAL_V5R6C1_GlbReset
	.type	VDMHAL_V5R6C1_GlbReset, %function
VDMHAL_V5R6C1_GlbReset:
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
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L291
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V5R6C1_GlbResetX
.L291:
	mov	r3, #0
	ldr	r2, .L292
	movt	r3, 63683
	ldr	r1, .L292+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L293:
	.align	2
.L292:
	.word	.LANCHOR0+296
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GlbReset, .-VDMHAL_V5R6C1_GlbReset
	.align	2
	.global	VDMHAL_V5R6C1_ClearIntState
	.type	VDMHAL_V5R6C1_ClearIntState, %function
VDMHAL_V5R6C1_ClearIntState:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r7, .L310
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L310+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L307
	movw	r6, #1228
	ldr	r9, .L310+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L308
.L298:
	cmp	r4, #1
	beq	.L309
.L305:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L307:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L310+12
	ldr	r2, .L310+16
	bl	dprint_vfmw
.L294:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L309:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L305
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L294
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L294
.L308:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L298
.L299:
	ldr	r1, .L310+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L311:
	.align	2
.L310:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+320
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ClearIntState, .-VDMHAL_V5R6C1_ClearIntState
	.align	2
	.global	VDMHAL_V5R6C1_ClearMMUIntState
	.type	VDMHAL_V5R6C1_ClearMMUIntState, %function
VDMHAL_V5R6C1_ClearMMUIntState:
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
	subs	r3, r0, #0
	bgt	.L317
	movw	r2, #1228
	ldr	r5, .L319
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L318
.L315:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L317:
	mov	r0, #0
	ldr	r2, .L319+4
	str	r0, [sp]
	ldr	r1, .L319+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L318:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L315
.L316:
	ldr	r1, .L319+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L320:
	.align	2
.L319:
	.word	g_HwMem
	.word	.LANCHOR0+348
	.word	.LC28
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ClearMMUIntState, .-VDMHAL_V5R6C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V5R6C1_MaskInt
	.type	VDMHAL_V5R6C1_MaskInt, %function
VDMHAL_V5R6C1_MaskInt:
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
	subs	r3, r0, #0
	bgt	.L326
	movw	r2, #1228
	ldr	r5, .L328
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L327
.L324:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L326:
	mov	r0, #0
	ldr	r2, .L328+4
	str	r0, [sp]
	ldr	r1, .L328+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L327:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L324
.L325:
	ldr	r1, .L328+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L329:
	.align	2
.L328:
	.word	g_HwMem
	.word	.LANCHOR0+380
	.word	.LC28
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_MaskInt, .-VDMHAL_V5R6C1_MaskInt
	.align	2
	.global	VDMHAL_V5R6C1_GetIntMaskCfg
	.type	VDMHAL_V5R6C1_GetIntMaskCfg, %function
VDMHAL_V5R6C1_GetIntMaskCfg:
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
	cmp	r0, #1
	mvneq	r0, #5
	mvnne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetIntMaskCfg, .-VDMHAL_V5R6C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V5R6C1_EnableInt
	.type	VDMHAL_V5R6C1_EnableInt, %function
VDMHAL_V5R6C1_EnableInt:
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
	ldr	r2, .L344
	mov	r3, r0, asl #6
	ldr	r1, .L344+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L342
	movw	r5, #1228
	ldr	r6, .L344+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L343
.L337:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L342:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L344+12
	ldr	r2, .L344+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L343:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L337
.L338:
	ldr	r1, .L344+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L345:
	.align	2
.L344:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+404
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_EnableInt, .-VDMHAL_V5R6C1_EnableInt
	.align	2
	.global	VDMHAL_V5R6C1_CheckReg
	.type	VDMHAL_V5R6C1_CheckReg, %function
VDMHAL_V5R6C1_CheckReg:
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
	subs	r5, r1, #0
	mov	r7, r0
	bgt	.L363
	movw	r4, #1228
	ldr	r6, .L365
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L364
.L349:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L355
.L357:
	.word	.L360
	.word	.L358
	.word	.L359
	.word	.L361
	.word	.L351
	.word	.L353
	.word	.L354
.L361:
	mov	r3, #40
.L356:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L360:
	mov	r3, #28
	b	.L356
.L359:
	mov	r3, #36
	b	.L356
.L358:
	mov	r3, #32
	b	.L356
.L354:
	movw	r3, #62272
	b	.L356
.L351:
	movw	r3, #61480
	b	.L356
.L353:
	movw	r3, #62304
	b	.L356
.L355:
	mov	r3, r7
	ldr	r2, .L365+4
	ldr	r1, .L365+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L364:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L350
	str	r8, [r6, r4]
	b	.L349
.L363:
	mov	r3, r5
	ldr	r2, .L365+4
	ldr	r1, .L365+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L350:
	ldr	r2, .L365+4
	ldr	r1, .L365+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L366:
	.align	2
.L365:
	.word	g_HwMem
	.word	.LANCHOR0+428
	.word	.LC40
	.word	.LC38
	.word	.LC39
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CheckReg, .-VDMHAL_V5R6C1_CheckReg
	.align	2
	.global	VDMHAL_V5R6C1_ReadMMUMask
	.type	VDMHAL_V5R6C1_ReadMMUMask, %function
VDMHAL_V5R6C1_ReadMMUMask:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r0, #0
	ble	.L370
	mov	r1, #1
	ldr	r2, .L371
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L371+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L370:
	movw	r0, #1228
	ldr	r2, .L371+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L372:
	.align	2
.L371:
	.word	.LANCHOR0+452
	.word	.LC34
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ReadMMUMask, .-VDMHAL_V5R6C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V5R6C1_WriteMMUMask
	.type	VDMHAL_V5R6C1_WriteMMUMask, %function
VDMHAL_V5R6C1_WriteMMUMask:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r1, #0
	ble	.L376
	mov	r1, #1
	ldr	r2, .L377
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L377+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L376:
	movw	r1, #1228
	ldr	r2, .L377+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L378:
	.align	2
.L377:
	.word	.LANCHOR0+480
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteMMUMask, .-VDMHAL_V5R6C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V5R6C1_PrepareDec
	.type	VDMHAL_V5R6C1_PrepareDec, %function
VDMHAL_V5R6C1_PrepareDec:
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
	subs	r7, r1, #0
	mov	r4, r0
	mov	r5, r2
	mov	r6, r3
	beq	.L399
	cmp	r2, #0
	bgt	.L400
	sub	r1, r0, #6
	mov	r2, #0
	clz	r1, r1
	mov	r0, r2
	mov	r1, r1, lsr #5
	bl	SCD_ConfigReg
	mov	r3, r6
	mov	r2, #0
	mov	r1, #1
	mov	r0, #8
	bl	SCD_ConfigReg
	cmp	r4, #18
	ldrls	pc, [pc, r4, asl #2]
	b	.L381
.L384:
	.word	.L394
	.word	.L385
	.word	.L386
	.word	.L387
	.word	.L381
	.word	.L388
	.word	.L389
	.word	.L381
	.word	.L390
	.word	.L391
	.word	.L392
	.word	.L392
	.word	.L392
	.word	.L393
	.word	.L381
	.word	.L394
	.word	.L395
	.word	.L396
	.word	.L397
.L394:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V5R6C1_StartDec
.L395:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V5R6C1_StartDec
.L396:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V5R6C1_StartDec
.L397:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS2HAL_V5R6C1_StartDec
.L385:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V5R6C1_StartDec
.L386:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V5R6C1_StartDec
.L387:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V5R6C1_StartDec
.L388:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V5R6C1_StartDec
.L389:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V5R6C1_StartDec
.L390:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V5R6C1_StartDec
.L391:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V5R6C1_StartDec
.L392:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V5R6C1_StartDec
.L393:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V5R6C1_StartDec
.L399:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L401
	ldr	r1, .L401+4
	bl	dprint_vfmw
.L381:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L400:
	mov	r3, r2
	mov	r0, #0
	ldr	r2, .L401
	str	r0, [sp]
	ldr	r1, .L401+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L402:
	.align	2
.L401:
	.word	.LANCHOR0+508
	.word	.LC41
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_PrepareDec, .-VDMHAL_V5R6C1_PrepareDec
	.align	2
	.global	VDMHAL_V5R6C1_IsVdmReady
	.type	VDMHAL_V5R6C1_IsVdmReady, %function
VDMHAL_V5R6C1_IsVdmReady:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	movw	r2, #1228
	mul	r2, r2, r0
	ldr	r3, .L410
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L408
	cmp	r0, #0
	ble	.L409
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L410+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L410+8
	bl	dprint_vfmw
	mov	r0, #0
.L405:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L409:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L408:
	mov	r0, r3
	ldr	r2, .L410+4
	ldr	r3, .L410+12
	ldr	r1, .L410+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L405
.L411:
	.align	2
.L410:
	.word	g_HwMem
	.word	.LANCHOR0+536
	.word	.LC34
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdmReady, .-VDMHAL_V5R6C1_IsVdmReady
	.align	2
	.global	VDMHAL_V5R6C1_IsVdmRun
	.type	VDMHAL_V5R6C1_IsVdmRun, %function
VDMHAL_V5R6C1_IsVdmRun:
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
	movw	r2, #1228
	mul	r2, r2, r0
	ldr	r3, .L419
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L417
	cmp	r0, #0
	ble	.L418
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L419+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L419+8
	bl	dprint_vfmw
	mov	r0, r4
.L414:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L418:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L417:
	ldr	r1, .L419+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L414
.L420:
	.align	2
.L419:
	.word	g_HwMem
	.word	.LANCHOR0+564
	.word	.LC34
	.word	.LC43
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdmRun, .-VDMHAL_V5R6C1_IsVdmRun
	.align	2
	.global	VDMHAL_V5R6C1_IsVdhDecOver
	.type	VDMHAL_V5R6C1_IsVdhDecOver, %function
VDMHAL_V5R6C1_IsVdhDecOver:
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
	movw	r2, #1228
	ldr	r3, .L431
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L429
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	r4, #2
	beq	.L426
	cmp	r4, #3
	beq	.L426
	cmp	r4, #1
	beq	.L430
	mov	r3, r4
	ldr	r2, .L431+4
	ldr	r1, .L431+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L426:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L430:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L429:
	mov	r0, r3
	ldr	r2, .L431+4
	ldr	r3, .L431+12
	ldr	r1, .L431+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L432:
	.align	2
.L431:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC40
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdhDecOver, .-VDMHAL_V5R6C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V5R6C1_IsVdhPartDecOver
	.type	VDMHAL_V5R6C1_IsVdhPartDecOver, %function
VDMHAL_V5R6C1_IsVdhPartDecOver:
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
	movw	r2, #1228
	ldr	r3, .L443
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L441
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	r4, #1
	beq	.L437
	cmp	r4, #2
	bne	.L442
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L442:
	mov	r3, r4
	ldr	r2, .L443+4
	ldr	r1, .L443+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L437:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L441:
	mov	r0, r3
	ldr	r2, .L443+4
	ldr	r3, .L443+12
	ldr	r1, .L443+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L444:
	.align	2
.L443:
	.word	g_HwMem
	.word	.LANCHOR0+616
	.word	.LC40
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdhPartDecOver, .-VDMHAL_V5R6C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V5R6C1_UpdateHardwareInfo
	.type	VDMHAL_V5R6C1_UpdateHardwareInfo, %function
VDMHAL_V5R6C1_UpdateHardwareInfo:
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
	subs	r4, r0, #0
	bgt	.L446
	ldr	r2, .L480
	ldr	r0, [r2]
	cmp	r0, #1
	addne	r3, r2, #124
	bne	.L450
	b	.L463
.L474:
	cmp	r2, r3
	beq	.L473
.L450:
	ldr	r0, [r2, #4]!
	cmp	r0, #1
	bne	.L474
.L463:
	mov	r5, r0
.L447:
	movw	r6, #1228
	ldr	r8, .L480+4
	mul	r6, r6, r4
	ldr	r7, [r8, r6]
	cmp	r7, #0
	beq	.L475
.L451:
	mov	r2, #180
	ldr	r1, .L480+8
	mul	r2, r2, r4
	mov	r3, r4, asl #6
	sub	r3, r3, r4, asl #3
	ldr	r0, [r7, #12]
	ldr	r6, .L480+12
	add	r3, r3, r1
	ldr	r1, [r3, #4]
	add	r3, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [r7, #28]
	cmp	r1, #1
	str	r2, [r3, #4]
	beq	.L476
	cmp	r5, #1
	beq	.L477
	add	r2, r7, #4096
	cmp	r5, #0
	ldr	ip, [r2]
	ldr	r0, [r2, #12]
	ldr	r1, [r7, #208]
	ldr	r2, [r7, #212]
	str	ip, [r3, #16]
	str	r0, [r3, #20]
	str	r1, [r3, #8]
	str	r2, [r3, #12]
	bne	.L456
	ldr	lr, [r7, #176]
	ldr	ip, [r7, #180]
	ldr	r0, [r7, #184]
	ldr	r1, [r7, #188]
	ldr	r2, [r7, #192]
	str	lr, [r3, #24]
	str	ip, [r3, #28]
	str	r0, [r3, #32]
	str	r1, [r3, #36]
	str	r2, [r3, #40]
.L456:
	mov	lr, #180
	add	r1, r7, #33024
	mul	lr, lr, r4
	add	r2, lr, #48
	add	lr, lr, #176
	add	r2, r6, r2
	add	lr, r6, lr
.L457:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, lr
	bne	.L457
	cmp	r5, #0
	bne	.L478
	mov	r3, #180
	add	r7, r7, #32768
	mla	r4, r3, r4, r6
	ldr	r2, [r7, #384]
	ldr	r3, [r7, #388]
	mov	r0, r5
	str	r2, [r4, #48]
	str	r3, [r4, #44]
.L468:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L478:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L473:
	mov	r5, #0
	b	.L447
.L476:
	add	r1, r7, #4096
	mov	r0, #0
	ldr	r1, [r1, #12]
	ubfx	ip, r1, #0, #20
	str	r1, [r3, #20]
	ldr	r1, [r7, #176]
	str	ip, [r3, #20]
	str	r1, [r3, #24]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L477:
	movw	r3, #1228
	ubfx	r7, r2, #0, #17
	mla	r3, r3, r4, r8
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L479
	sub	r3, r7, #1
	movw	r1, #1228
	cmp	r3, #199
	mov	r2, #180
	subls	r3, r7, #-1073741823
	mul	r1, r1, r4
	movls	r3, r3, asl #4
	movhi	r3, #0
	addls	lr, r3, #8
	ldr	r0, [ip, r3]
	movhi	lr, #8
	mla	r3, r2, r4, r6
	ldr	r7, [r8, r1]
	str	r0, [r3, #16]
	ldr	r0, [r7, #208]
	ldr	r1, [ip, lr]
	ldr	r2, [r7, #212]
	str	r0, [r3, #8]
	str	r1, [r3, #20]
	str	r2, [r3, #12]
	b	.L456
.L475:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L452
	str	r7, [r8, r6]
	b	.L451
.L446:
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L480+16
	ldr	r1, .L480+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L468
.L452:
	ldr	r1, .L480+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L468
.L479:
	ldr	r3, .L480+28
	ldr	r2, .L480+16
	ldr	r1, .L480+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L468
.L481:
	.align	2
.L480:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_VdmDrvParam+48
	.word	g_BackUp
	.word	.LANCHOR0+648
	.word	.LC28
	.word	.LC37
	.word	.LC44
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_UpdateHardwareInfo, .-VDMHAL_V5R6C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V5R6C1_ReadMsgSlot
	.type	VDMHAL_V5R6C1_ReadMsgSlot, %function
VDMHAL_V5R6C1_ReadMsgSlot:
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
	mov	r3, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L486
	cmp	r2, #800
	bhi	.L487
	ldr	r3, .L488
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L487:
	mov	r0, r4
	ldr	r1, .L488+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L486:
	mov	r2, r0
	ldr	r1, .L488+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L489:
	.align	2
.L488:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ReadMsgSlot, .-VDMHAL_V5R6C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V5R6C1_WriteMsgSlot
	.type	VDMHAL_V5R6C1_WriteMsgSlot, %function
VDMHAL_V5R6C1_WriteMsgSlot:
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
	moveq	r4, #1
	movne	r4, #0
	beq	.L491
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L491
	ldr	r3, .L494
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L491:
	ldr	r1, .L494+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L495:
	.align	2
.L494:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteMsgSlot, .-VDMHAL_V5R6C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V5R6C1_CfgRpMsg
	.type	VDMHAL_V5R6C1_CfgRpMsg, %function
VDMHAL_V5R6C1_CfgRpMsg:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	mov	r7, r0
	ldr	r0, [r1, #48]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-60]
	beq	.L540
	ldr	r2, [r7, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L541
	ldr	r0, [r7, #28]
	ldr	r3, [r7, #64]
	ldr	r2, [r7, #32]
	mov	r0, r0, asl r3
	cmp	r0, #1920
	add	r1, r0, #255
	mov	r3, r2, asl r3
	bic	r1, r1, #255
	bgt	.L503
	ldr	ip, [r7, #4]
	cmp	ip, #17
	beq	.L503
	mov	r2, #0
	strb	r2, [r7]
	strb	r2, [r7, #1]
.L502:
	cmp	ip, #16
	beq	.L504
.L543:
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r1, r2
.L527:
	ldr	r0, [r7, #20]
	ldr	ip, [fp, #-60]
	str	r0, [ip]
	ldr	r0, [r7, #20]
	add	r0, r3, r0
	str	r0, [ip, #4]
	ldr	r0, [r7, #8]
	str	r0, [ip, #8]
	ldr	r0, [r7, #8]
	add	r3, r3, r0
	str	r3, [ip, #12]
	ldr	ip, [fp, #-60]
	mov	r0, #0	@ movhi
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, r1, asl #4
	str	r1, [ip, #16]
	str	r2, [ip, #20]
	mov	r1, r0	@ movhi
	ldr	r2, [r7, #28]
	ldr	r3, [r7, #32]
	sub	r2, r2, #1
	sub	r3, r3, #1
	bfi	r0, r2, #0, #9
	bfi	r1, r3, #0, #9
	strh	r0, [fp, #-52]	@ movhi
	strh	r1, [fp, #-50]	@ movhi
	ldr	r3, [fp, #-52]
	str	r3, [ip, #24]
	ldr	r3, [r7, #52]
	ldr	r1, [r7, #56]
	sub	r3, r3, #1
	ldr	r2, [r7, #28]
	cmp	r3, #1
	ldr	r3, [r7, #32]
	str	r2, [fp, #-76]
	addls	r3, r3, r3, lsr #31
	movls	r3, r3, asr #1
	cmp	r1, #0
	str	r3, [fp, #-84]
	movne	r3, #0
	strne	r3, [fp, #-64]
	beq	.L542
.L509:
	cmp	r1, #1
	beq	.L525
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L526:
	ldr	ip, [r7, #64]
	mov	r0, #0
	ldrb	r1, [fp, #-49]	@ zero_extendqisi2
	ldrb	lr, [r7]	@ zero_extendqisi2
	sub	ip, ip, #4
	ldrb	r2, [fp, #-50]	@ zero_extendqisi2
	bfi	r1, ip, #0, #2
	ldr	ip, [r7, #52]
	bfi	r2, lr, #0, #1
	ldr	lr, [fp, #-80]
	and	ip, ip, #3
	strh	r3, [fp, #-52]	@ movhi
	bfi	r1, lr, #2, #4
	bfi	r2, ip, #4, #2
	ldrb	lr, [r7, #1]	@ zero_extendqisi2
	mov	r3, r2
	bfi	r3, ip, #6, #2
	bfi	r1, lr, #6, #1
	strb	r3, [fp, #-50]
	strb	r1, [fp, #-49]
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-60]
	str	r3, [r2, #28]
.L538:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L503:
	ldrb	lr, [r7]	@ zero_extendqisi2
	mov	r2, #0
	ldr	ip, [r7, #4]
	cmp	lr, #1
	strb	r2, [r7, #1]
	bne	.L502
	add	r2, r0, #2032
	adds	lr, r3, #63
	add	r2, r2, #15
	add	r0, r0, #4080
	add	r0, r0, #14
	addmi	lr, r3, #126
	cmp	r2, #0
	movlt	r2, r0
	mov	r0, lr, asr #6
	mov	r2, r2, asr #11
	cmp	ip, #16
	mov	r0, r0, asl #5
	mov	r2, r2, asl #4
	mul	r2, r2, r0
	bne	.L543
.L504:
	mov	r0, #10
	str	r0, [fp, #-80]
	mla	r3, r1, r3, r2
	b	.L527
.L542:
	ldr	r3, [r7, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L510
	cmp	r3, #5
	moveq	r4, #4
	beq	.L510
	cmp	r3, #4
	moveq	r4, #8
	bne	.L544
.L510:
	ldr	r8, [r7, #44]
	cmp	r8, #0
	movle	r3, #0
	ldrle	r1, [r7, #56]
	strle	r3, [fp, #-64]
	ble	.L509
	ldr	r2, [fp, #-84]
	mov	r6, #0
	ldr	r3, [fp, #-76]
	str	r6, [fp, #-72]
	str	r6, [fp, #-64]
	mul	r3, r3, r2
	str	r7, [fp, #-56]
	sub	r2, r4, #1
	str	r2, [fp, #-88]
	str	r3, [fp, #-92]
	sub	r3, r3, #1
	str	r3, [fp, #-96]
	b	.L513
.L547:
	ldrsh	r0, [r5, #70]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r10, r3
	str	r3, [fp, #-72]
	ldrgt	r10, [fp, #-88]
	bgt	.L516
.L515:
	ldr	r3, [fp, #-56]
	add	r6, r6, #1
	ldr	r8, [r3, #44]
	cmp	r6, r8
	bge	.L545
	cmp	r6, #199
	bgt	.L546
.L513:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r5, r3, r6, lsl #2
	ldrsh	r7, [r5, #74]
	ldrh	r3, [r5, #72]
	sub	r0, r7, #1
	add	r0, r0, r4
	str	r3, [fp, #-68]
	bl	__aeabi_uidiv
	cmp	r6, #0
	mul	r10, r4, r0
	bgt	.L547
	ldr	r2, [fp, #-72]
	cmp	r10, r2
	movgt	r2, #0
	movle	r2, #1
	cmp	r6, #0
	moveq	r2, #0
	cmp	r2, #0
	bne	.L515
.L518:
	ldrsh	r0, [fp, #-68]
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-92]
	ldr	r5, [fp, #-96]
	cmp	r3, r10
	ldr	r3, [fp, #-64]
	movhi	r5, r10
	add	r3, r3, #1
	str	r3, [fp, #-64]
	mul	r8, r4, r0
	cmp	r8, r5
	movgt	r8, #0
	cmp	r3, #252
	bgt	.L548
	ldr	r7, [fp, #-76]
	mov	r0, r8
	mov	r1, r7
	bl	__aeabi_uidivmod
	mov	r0, r8
	mov	r3, #0	@ movhi
	bfi	r3, r1, #0, #9
	mov	r1, r7
	strh	r3, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	mov	r3, #0	@ movhi
	ldr	r2, [fp, #-64]
	ldr	r9, [fp, #-60]
	mov	r1, r7
	add	r2, r2, #5
	mov	r8, r2, asl #3
	add	r8, r8, #4
	bfi	r3, r0, #0, #9
	strh	r3, [fp, #-46]	@ movhi
	ldr	r3, [fp, #-48]
	mov	r0, r5
	str	r3, [r9, r2, asl #3]
	bl	__aeabi_uidivmod
	mov	r0, r5
	mov	r3, #0	@ movhi
	bfi	r3, r1, #0, #9
	mov	r1, r7
	strh	r3, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	mov	r3, #0	@ movhi
	bfi	r3, r0, #0, #9
	strh	r3, [fp, #-46]	@ movhi
	ldr	r3, [fp, #-48]
	str	r3, [r9, r8]
	b	.L515
.L519:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r7, r4, r0
	ldrsh	r0, [r5, #76]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	add	r2, r0, #1
	bhi	.L520
	cmp	r7, r2
	mov	r1, r4
	beq	.L520
	ldrsh	r0, [r5, #70]
	add	r0, r0, r10
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	bhi	.L549
.L520:
	cmp	r9, #198
	mov	r6, r9
	add	r5, r5, #4
	bgt	.L550
	ldrsh	r7, [r5, #74]
.L516:
	add	r9, r6, #1
	mov	r1, r4
	cmp	r9, r8
	add	r0, r10, r7
	blt	.L519
	ldr	r3, [fp, #-88]
	add	r0, r3, r7
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L518
.L550:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r3, r3, r9, lsl #2
	ldrsh	r0, [r3, #74]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L518
.L548:
	ldr	r7, [fp, #-56]
	mov	r1, #1
	str	r1, [r7, #56]
.L525:
	ldr	r3, [fp, #-76]
	mov	lr, #0	@ movhi
	mov	ip, lr	@ movhi
	str	r1, [r7, #44]
	sub	r2, r3, #1
	ldr	r3, [fp, #-84]
	ldr	r1, [fp, #-60]
	sub	r0, r3, #1
	mov	r3, #0
	bfi	lr, r3, #0, #9
	bfi	ip, r3, #0, #9
	strh	lr, [fp, #-52]	@ movhi
	strh	ip, [fp, #-50]	@ movhi
	mov	ip, #0	@ movhi
	ldr	lr, [fp, #-52]
	bfi	ip, r2, #0, #9
	mov	r2, #0	@ movhi
	strh	ip, [fp, #-52]	@ movhi
	bfi	r2, r0, #0, #9
	strh	r2, [fp, #-50]	@ movhi
	ldr	r2, [fp, #-52]
	str	lr, [r1, #48]
	str	r2, [r1, #52]
	b	.L526
.L549:
	mov	r10, r7
	b	.L518
.L545:
	mov	r7, r3
	ldr	r1, [r3, #56]
	b	.L509
.L546:
	ldr	r7, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L551
	mov	r3, #2176
	str	r6, [sp]
	ldr	r2, .L551+4
	str	r0, [fp, #-64]
	bl	dprint_vfmw
	ldr	r1, [r7, #56]
	b	.L509
.L544:
	ldr	r1, .L551+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L510
.L541:
	ldr	r1, .L551+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L538
.L540:
	ldr	r3, .L551+16
	ldr	r2, .L551+20
	ldr	r1, .L551+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L538
.L552:
	.align	2
.L551:
	.word	.LC51
	.word	.LANCHOR0+708
	.word	.LC50
	.word	.LC49
	.word	.LC48
	.word	.LANCHOR0+684
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CfgRpMsg, .-VDMHAL_V5R6C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V5R6C1_CfgRpReg
	.type	VDMHAL_V5R6C1_CfgRpReg, %function
VDMHAL_V5R6C1_CfgRpReg:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r6, r3, #0
	mov	r0, #0
	str	r0, [fp, #-32]
	bgt	.L587
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L588
.L556:
	ldr	r4, .L590
	ldr	r3, [r1, #48]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L589
	movw	r1, #1228
	ldr	r2, .L590+4
	mul	r1, r1, r6
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L559:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r6
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L561:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L563:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L565:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L567:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L569:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L571:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L573:
	movw	r3, #1228
	movw	r1, #3075
	mul	r6, r3, r6
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r6]
	str	r1, [r3, #84]
.L576:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L589:
	mov	r2, #16
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L590+4
	beq	.L559
	mov	r2, #12
	mov	r1, #2
	ldr	r0, [fp, #4]
	movw	r5, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r5, 48
	str	r5, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L561
	mov	r3, r5
	mov	r2, #60
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L563
	mov	r3, r5
	mov	r2, #64
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L565
	mov	r3, r5
	mov	r2, #68
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L567
	mov	r3, r5
	mov	r2, #72
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L569
	mov	r3, r5
	mov	r2, #76
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L571
	mov	r3, r5
	mov	r2, #80
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L590+4
	beq	.L573
	ldr	r0, [fp, #4]
	mov	r3, r5
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L588:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L557
	ldr	r1, [fp, #-40]
	str	r3, [r1]
	b	.L556
.L587:
	str	r0, [sp]
	ldr	r2, .L590+8
	ldr	r1, .L590+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L576
.L557:
	ldr	r1, .L590+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L576
.L591:
	.align	2
.L590:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0+732
	.word	.LC28
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CfgRpReg, .-VDMHAL_V5R6C1_CfgRpReg
	.align	2
	.global	VDMHAL_V5R6C1_MakeDecReport
	.type	VDMHAL_V5R6C1_MakeDecReport, %function
VDMHAL_V5R6C1_MakeDecReport:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r3, r0, #0
	beq	.L621
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L622
	movw	r3, #1228
	ldr	r7, .L630
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L596
	ldr	r3, .L630+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L599
	b	.L611
.L624:
	cmp	r3, r1
	beq	.L623
.L599:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L624
.L611:
	mov	r4, r2
.L597:
	ldr	r3, .L630+8
	mov	r2, #820
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L630+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L600
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L600:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L625
.L601:
	cmp	r2, #200
	bhi	.L626
.L603:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r7, [r7, #40]
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L627
	ldr	r8, .L630+16
	mov	r3, #3200
	ldr	r2, [r5, #12]
	mla	r4, r3, r6, r8
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V5R6C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	cmp	ip, #0
	movne	r3, r4
	movne	r2, r5
	movne	r1, #0
	beq	.L608
.L607:
	ldr	r0, [r3, #4]
	add	r1, r1, #1
	cmp	r1, ip
	add	r3, r3, #16
	add	r2, r2, #4
	strh	r0, [r2, #12]	@ movhi
	ldr	r0, [r3, #-8]
	strh	r0, [r2, #14]	@ movhi
	bne	.L607
.L608:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L628
.L594:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L625:
	cmp	r4, #1
	beq	.L629
	ldr	r1, .L630+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L601
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L601
	mov	r3, #1
	strh	r1, [r5, #16]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #18]	@ movhi
	str	r3, [r5, #12]
	b	.L594
.L623:
	mov	r4, #0
	b	.L597
.L628:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L630+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L630+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L609:
	ldr	r1, [r6, #4]
	ldr	lr, [r6, #12]
	mov	r2, r4
	ldr	ip, [r6, #8]
	mov	r0, #6
	ldr	r3, [r6]
	add	r4, r4, #4
	str	r1, [sp]
	add	r6, r6, #16
	str	lr, [sp, #8]
	str	ip, [sp, #4]
	ldr	r1, .L630+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L609
	ldr	r1, .L630+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L626:
	mov	r3, #200
	ldr	r1, .L630+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L603
.L629:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L601
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #16]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #18]	@ movhi
	b	.L594
.L627:
	ldr	r3, .L630+44
	ldr	r2, .L630+48
	ldr	r1, .L630+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L594
.L596:
	ldr	r3, .L630+56
	ldr	r2, .L630+48
	ldr	r1, .L630+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L594
.L622:
	mov	r0, r5
	ldr	r3, .L630+60
	ldr	r2, .L630+48
	ldr	r1, .L630+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L594
.L621:
	ldr	r3, .L630+64
	ldr	r2, .L630+48
	ldr	r1, .L630+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L594
.L631:
	.align	2
.L630:
	.word	g_HwMem
	.word	g_DSPState
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC54
	.word	.LC44
	.word	.LANCHOR0+756
	.word	.LC1
	.word	.LC42
	.word	.LC53
	.word	.LC52
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_MakeDecReport, .-VDMHAL_V5R6C1_MakeDecReport
	.align	2
	.global	VDMHAL_V5R6C1_PrepareRepair
	.type	VDMHAL_V5R6C1_PrepareRepair, %function
VDMHAL_V5R6C1_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	movw	r4, #1228
	mul	r4, r4, r3
	ldr	r5, .L647
	cmp	r3, #0
	mov	r6, r3
	mov	r7, r0
	add	r8, r4, r5
	bgt	.L643
	ldr	r3, [r4, r5]
	cmp	r3, #0
	beq	.L644
.L635:
	cmp	r2, #0
	beq	.L645
	cmp	r2, #1
	movne	r0, #0
	beq	.L646
.L634:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L645:
	ldr	r4, .L647+4
	mov	r3, #1744
	mla	r3, r3, r6, r4
	ldr	r0, [r3, #44]
	cmp	r0, #0
	ble	.L638
	cmp	r7, #6
	bne	.L639
	ldrb	r0, [r1, #17]	@ zero_extendqisi2
	cmp	r0, #1
	moveq	r2, r0
	str	r2, [r3, #924]
.L639:
	ldr	r3, [fp, #4]
	mov	r2, r1
	mov	r0, r7
	mov	r1, r8
	str	r3, [sp]
	mov	r3, r6
	bl	VDMHAL_V5R6C1_CfgRpReg
	mov	r0, #1744
	mov	r1, r8
	mov	r2, r6
	mla	r0, r0, r6, r4
	bl	VDMHAL_V5R6C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L646:
	cmp	r7, #6
	bne	.L641
	ldrb	r3, [r1, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L641
	mov	r4, #1744
	ldr	r5, .L647+4
	mul	r4, r4, r6
	add	ip, r5, r4
	ldr	r3, [ip, #916]
	cmp	r3, #0
	ble	.L641
	ldr	r3, [fp, #4]
	mov	lr, #2
	mov	r2, r1
	mov	r0, r7
	mov	r1, r8
	str	r3, [sp]
	mov	r3, r6
	str	lr, [ip, #924]
	bl	VDMHAL_V5R6C1_CfgRpReg
	add	r0, r4, #872
	mov	r2, r6
	add	r0, r5, r0
	mov	r1, r8
	bl	VDMHAL_V5R6C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L644:
	mov	r0, #0
	str	r2, [fp, #-44]
	movt	r0, 63683
	str	r1, [fp, #-40]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L636
	str	r3, [r4, r5]
	ldr	r1, [fp, #-40]
	ldr	r2, [fp, #-44]
	b	.L635
.L643:
	mov	r0, #0
	ldr	r2, .L647+8
	str	r0, [sp]
	ldr	r1, .L647+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L634
.L641:
	ldr	r1, .L647+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L634
.L638:
	mov	r0, r2
	ldr	r1, .L647+20
	str	r2, [fp, #-40]
	bl	dprint_vfmw
	ldr	r2, [fp, #-40]
	mov	r0, r2
	b	.L634
.L636:
	ldr	r1, .L647+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L634
.L648:
	.align	2
.L647:
	.word	g_HwMem
	.word	g_RepairParam
	.word	.LANCHOR0+784
	.word	.LC28
	.word	.LC61
	.word	.LC60
	.word	.LC59
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_PrepareRepair, .-VDMHAL_V5R6C1_PrepareRepair
	.align	2
	.global	VDMHAL_V5R6C1_StartHwRepair
	.type	VDMHAL_V5R6C1_StartHwRepair, %function
VDMHAL_V5R6C1_StartHwRepair:
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
	ldr	r6, .L679
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L673
	cmp	r0, #0
	ble	.L674
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L679+4
	mov	r0, #32
	ldr	r1, .L679+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L675
.L657:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L679+4
	ldr	r1, .L679+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L669
.L652:
	cmp	r4, #0
	beq	.L676
	mov	r3, r5, asl #6
	ldr	r2, .L679+12
	sub	r3, r3, r5, asl #3
	mov	r1, #1
	add	r3, r2, r3
	str	r1, [r4, #4]
	mov	r0, r4
	ldr	r3, [r3, #8]
	strb	r1, [r4, #2]
	strb	r5, [r4]
	str	r3, [r4, #8]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	VDH_PostTask
.L674:
	movw	r3, #1228
	ldr	r4, .L679+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L655:
	movw	r3, #1228
	ldr	r2, .L679+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L664:
	movw	r3, #1228
	mov	r2, #0
	mul	r5, r3, r5
	mov	r1, #1
	ldr	r3, [r4, r5]
	str	r2, [r3]
	ldr	r3, [r4, r5]
	str	r1, [r3]
	ldr	r3, [r4, r5]
	str	r2, [r3]
.L649:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L673:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L677
	cmp	r5, #0
	ldrle	r4, .L679+16
	bgt	.L657
	b	.L655
.L677:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L652
	ldr	r3, .L679+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L678
.L661:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L679+24
	ldr	r1, .L679+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L679+24
	ldr	r1, .L679+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L679+24
	ldr	r1, .L679+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L649
.L675:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L652
.L669:
	ldr	r3, .L679+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L661
.L676:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L679+24
	ldr	r1, .L679+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L678:
	ldr	r4, .L679+16
	b	.L664
.L680:
	.align	2
.L679:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_StartHwRepair, .-VDMHAL_V5R6C1_StartHwRepair
	.align	2
	.global	VDMHAL_V5R6C1_CalVdhClkSkip
	.type	VDMHAL_V5R6C1_CalVdhClkSkip, %function
VDMHAL_V5R6C1_CalVdhClkSkip:
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
	ldr	r9, .L711
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L703
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L683
.L710:
	mov	r3, r10
	ldr	r2, .L711+4
	ldr	r1, .L711+8
	mov	r0, #1
	bl	dprint_vfmw
.L685:
	cmp	r4, r9
	beq	.L709
.L702:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L709
.L683:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L710
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L686
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L686:
	ldr	r3, .L711+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1464]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L704
.L689:
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L704
	.word	.L698
	.word	.L698
	.word	.L704
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L698
	.word	.L704
	.word	.L699
	.word	.L698
	.word	.L698
.L698:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L702
.L709:
	mov	r2, r7, asl #8
	movw	r3, #23813
	sub	r7, r2, r7, asl #6
	movt	r3, 56143
	umull	r2, r3, r7, r3
	mov	r0, r3, lsr #21
	rsb	r0, r0, #32
	cmp	r0, #25
	movge	r0, #25
	bic	r0, r0, r0, asr #31
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L699:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L685
.L704:
	mov	r7, #0
	b	.L685
.L703:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L712:
	.align	2
.L711:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC63
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalVdhClkSkip, .-VDMHAL_V5R6C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V5R6C1_GetVdmClk
	.type	VDMHAL_V5R6C1_GetVdmClk, %function
VDMHAL_V5R6C1_GetVdmClk:
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
	mov	r3, r0, asl #6
	ldr	r2, .L721
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L714
.L716:
	.word	.L714
	.word	.L717
	.word	.L718
	.word	.L719
.L714:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L718:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L717:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L719:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L722:
	.align	2
.L721:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetVdmClk, .-VDMHAL_V5R6C1_GetVdmClk
	.align	2
	.global	VDMHAL_V5R6C1_StartHwDecode
	.type	VDMHAL_V5R6C1_StartHwDecode, %function
VDMHAL_V5R6C1_StartHwDecode:
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
	subs	r4, r0, #0
	mov	r3, #8
	mov	r5, r1
	str	r3, [fp, #-48]
	ble	.L724
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L757
	ldr	r1, .L757+4
	bl	dprint_vfmw
.L723:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L724:
	ldr	r6, .L757+8
	sub	r0, fp, #48
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	r7, [fp, #-48]
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r7, r7, #0
	movne	r7, #1
	cmp	r3, #1
	bne	.L753
	ldr	r3, .L757+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	ubfx	r1, r3, #8, #2
	cmp	r1, r7
	bfine	r3, r7, #8, #2
	strne	r3, [r2, #120]
.L727:
	mov	r1, r7
	mov	r0, r4
	bl	VDMHAL_V5R6C1_GetVdmClk
	ldr	r7, .L757+16
	mov	r3, r4, asl #6
	ldr	r2, .L757+20
	sub	r3, r3, r4, asl #3
	ldrb	r1, [r6]	@ zero_extendqisi2
	add	r3, r7, r3
	cmp	r1, #1
	ldr	r8, [r3, #8]
	ldr	r3, [r2, r8, asl #2]
	ldr	r9, [r3, #1168]
	bne	.L754
	ldr	r3, .L757+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L730:
	mov	r2, r4
	mov	r3, r5
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r10, .L757+8
	cmp	r2, #1
	bne	.L755
	movw	r2, #1228
	ldr	r3, .L757+24
	mul	r2, r2, r4
	ldr	r5, .L757+28
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r5, r2]
	moveq	r1, #15
	movne	r1, #0
	str	r3, [r2, #156]
.L732:
	movw	r2, #1228
	cmp	r9, #1
	mul	r2, r2, r4
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r5, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L734:
	movw	r2, #1228
	mul	r2, r2, r4
	ldr	r2, [r5, r2]
	str	r3, [r2, #36]
.L736:
	ldr	r6, .L757+32
	mov	r0, #30
	ldr	r3, [r6, #116]
	blx	r3
	ldr	r3, [r6, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r4
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r4, r1, r4, r7
	ldr	ip, .L757+36
	mov	r1, #4
	ldr	r0, [r5, r3]
	str	r2, [r0]
	ldr	r0, [r5, r3]
	str	lr, [r0]
	ldr	r3, [r5, r3]
	str	r2, [r3]
	ldr	r0, [r4, #8]
	ldr	r2, [ip, r0, asl #2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L723
.L755:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r5
	bl	VDH_Record_RegData
	ldr	r3, .L757+24
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #15
	movne	r1, #0
	cmp	r2, #1
	ldreq	r5, .L757+28
	beq	.L732
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r5
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r9, #1
	ldrb	r2, [r6]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r5, .L757+28
	beq	.L734
	mov	r0, r5
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r5, .L757+28
	beq	.L736
	cmp	r5, #0
	beq	.L756
	mov	r3, #1
	str	r8, [r5, #8]
	strb	r4, [r5]
	mov	r0, r5
	str	r3, [r5, #4]
	bl	VDH_PostTask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L754:
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r5
	bl	VDH_Record_RegData
	b	.L730
.L753:
	mov	r2, #0
	mov	r3, r7
	mov	r1, r2
	mov	r0, r5
	bl	VDH_Record_RegData
	b	.L727
.L756:
	mov	r3, r5
	mov	r0, r5
	ldr	r2, .L757
	ldr	r1, .L757+40
	bl	dprint_vfmw
	b	.L723
.L758:
	.align	2
.L757:
	.word	.LANCHOR0+884
	.word	.LC28
	.word	g_HalDisable
	.word	g_pstRegCrg
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	mask_mmu_err_int
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_StartHwDecode, .-VDMHAL_V5R6C1_StartHwDecode
	.align	2
	.global	VDMHAL_V5R6C1_GetCharacter
	.type	VDMHAL_V5R6C1_GetCharacter, %function
VDMHAL_V5R6C1_GetCharacter:
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
	ldr	r1, .L760
	mov	r0, #15
	ldr	r3, .L760+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L761:
	.align	2
.L760:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetCharacter, .-VDMHAL_V5R6C1_GetCharacter
	.align	2
	.global	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R6C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R6C1_WriteBigTitle1DYuv:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 88
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
	mov	r6, r3
	ubfx	r3, r3, #29, #2
	mov	r8, r1
	cmp	r3, #1
	mov	r1, #0
	str	r0, [fp, #-108]
	mov	r5, r2
	str	r1, [fp, #-92]
	moveq	r4, r1
	str	r1, [fp, #-88]
	str	r1, [fp, #-84]
	str	r1, [fp, #-80]
	str	r1, [fp, #-76]
	str	r1, [fp, #-72]
	str	r1, [fp, #-68]
	str	r1, [fp, #-64]
	str	r1, [fp, #-60]
	str	r1, [fp, #-56]
	str	r1, [fp, #-52]
	str	r1, [fp, #-48]
	beq	.L763
	cmp	r3, #2
	moveq	r4, #1
	movne	r4, #2
.L763:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L762
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L852
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L766
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L852+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L766
	add	r6, r6, #15
	add	r5, r5, #15
	bic	r3, r6, #15
	str	r3, [fp, #-100]
	bic	r5, r5, #15
	mov	r2, r3
	adds	r3, r3, #31
	addmi	r3, r2, #62
	add	r6, r5, #255
	bic	r6, r6, #255
	cmp	r4, #0
	cmpne	r4, #3
	mov	r3, r3, asr #5
	mov	r2, r6, asl #4
	str	r2, [fp, #-104]
	mla	r3, r3, r6, r8
	str	r3, [fp, #-116]
	bne	.L767
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L852+8
	mov	r3, r3, lsr #1
	ldr	r4, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r9, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r9, [fp, #-96]
	beq	.L769
.L768:
	cmp	r5, #0
	beq	.L771
	ldr	r2, [fp, #-96]
	mov	r7, #0
	and	r10, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L770:
	mov	r1, r7, lsr #8
	add	r0, r9, r7
	add	r0, r4, r0
	add	r7, r7, #256
	add	r1, r10, r1, lsl #12
	ldr	r3, [r6, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r7
	bhi	.L770
.L771:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L768
.L769:
	ldr	r3, [fp, #-100]
	mov	r0, r4
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	blx	ip
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L772
	ldr	r3, [fp, #-104]
	mov	r8, #0
	ldr	r9, [fp, #-116]
	str	r8, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L773:
	cmp	r5, #0
	beq	.L776
	ldr	r2, [fp, #-96]
	mov	r7, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L774:
	mov	r1, r7, lsr #8
	add	r0, r8, r7
	add	r0, r4, r0
	add	r7, r7, #256
	add	r1, r10, r1, lsl #11
	ldr	r3, [r6, #52]
	add	r1, r9, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r7
	bhi	.L774
.L776:
	ldr	r3, [fp, #-96]
	add	r8, r8, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L773
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L850
.L778:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L779
	ldr	ip, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-128]
	blx	ip
	ldr	ip, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-120]
	blx	ip
.L779:
	ldr	r3, [fp, #-124]
.L849:
	ldr	r2, [fp, #-112]
	ldr	r5, [fp, #-108]
	ldr	ip, [r6, #44]
	mul	r4, r3, r2
	ldr	r0, [fp, #-120]
	mov	r2, r5
	mov	r1, r4
	blx	ip
	mov	r2, r5
	ldr	ip, [r6, #44]
	mov	r1, r4
	ldr	r0, [fp, #-128]
	blx	ip
	ldr	r1, [fp, #-88]
	ldr	r0, [fp, #-84]
	bl	MEM_ReleaseMemBlock
	mov	r2, #24
	ldr	ip, [r6, #48]
	mov	r1, #0
	sub	r0, fp, #92
	blx	ip
	ldr	r1, [fp, #-64]
	ldr	r0, [fp, #-60]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r6, #48]
	sub	r0, fp, #68
	mov	r2, #24
	mov	r1, #0
	blx	r3
.L762:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L766:
	ldr	r1, .L852+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L767:
	subs	r3, r4, #1
	ldr	r1, [fp, #-100]
	ldr	r2, [fp, #-64]
	movne	r3, #1
	cmp	r1, r3
	str	r3, [fp, #-124]
	add	r3, r2, #2097152
	str	r3, [fp, #-128]
	mov	r3, r5, lsr #1
	str	r3, [fp, #-132]
	mov	r3, r1, lsr #1
	str	r3, [fp, #-112]
	ldrhi	r3, [fp, #-124]
	str	r2, [fp, #-120]
	ldr	r6, .L852+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L786
.L788:
	cmp	r5, #0
	beq	.L789
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L787:
	mov	r1, r4, lsr #8
	add	r0, r4, r10
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r9, r1, lsl #12
	ldr	r3, [r6, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L787
.L789:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L788
.L786:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	mov	r1, r1, lsr #1
	blx	ip
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L790
	ldr	r3, [fp, #-104]
	mov	r8, #0
	ldr	r9, [fp, #-116]
	str	r8, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L791:
	cmp	r5, #0
	beq	.L794
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L792:
	mov	r1, r4, lsr #8
	add	r0, r8, r4
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r10, r1, lsl #11
	ldr	r3, [r6, #52]
	add	r1, r9, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L792
.L794:
	ldr	r3, [fp, #-96]
	add	r8, r8, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L791
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L851
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L797
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L802
.L803:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L803
.L802:
	ldr	ip, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-128]
	blx	ip
	ldr	ip, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-120]
	blx	ip
.L797:
	ldr	r3, [fp, #-132]
	b	.L849
.L850:
	ldr	r2, [fp, #-120]
	add	r4, r4, #1
	ldr	r7, [fp, #-124]
	mov	r3, #0
	ldr	r8, [fp, #-112]
.L780:
	cmp	r7, #0
	moveq	lr, r2
	beq	.L783
	sub	r0, r2, #-67108863
	add	lr, r2, r7
	sub	r0, r0, #65011712
	mov	r1, r4
.L781:
	ldrb	ip, [r1, #-1]	@ zero_extendqisi2
	strb	ip, [r0, #1]!
	ldrb	ip, [r1], #2	@ zero_extendqisi2
	strb	ip, [r2], #1
	cmp	r2, lr
	bne	.L781
.L783:
	add	r3, r3, #1
	mov	r2, lr
	cmp	r3, r8
	add	r4, r4, r5
	bne	.L780
	b	.L779
.L851:
	ldr	r3, [fp, #-124]
	ldr	r4, [fp, #-120]
	ldr	lr, [fp, #-132]
	mla	r2, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	mov	r3, #0
	add	r2, r2, #1
.L798:
	cmp	lr, #0
	beq	.L801
	mov	r1, r3, lsr #1
	mov	r0, r2
	mul	r1, lr, r1
	sub	ip, r1, #-67108863
	add	r9, r1, lr
	sub	ip, ip, #65011712
	add	r9, r4, r9
	add	ip, r4, ip
	add	r1, r4, r1
.L799:
	ldrb	r8, [r0, #-1]	@ zero_extendqisi2
	strb	r8, [ip, #1]!
	ldrb	r8, [r0], #2	@ zero_extendqisi2
	strb	r8, [r1], #1
	cmp	r1, r9
	bne	.L799
.L801:
	add	r3, r3, #2
	add	r2, r2, r5
	cmp	r7, r3
	bhi	.L798
	b	.L797
.L772:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L778
	b	.L779
.L790:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L797
	cmp	r3, #0
	beq	.L802
	b	.L797
.L853:
	.align	2
.L852:
	.word	.LC64
	.word	.LC66
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteBigTitle1DYuv, .-VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.align	2
	.global	CRG_ConfigReg
	.type	CRG_ConfigReg, %function
CRG_ConfigReg:
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
	ldr	ip, .L861
	mov	lr, r2
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L860
	cmp	r0, #0
	bne	.L856
	ldr	r3, .L861+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L856:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L861+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L860:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L862:
	.align	2
.L861:
	.word	g_HalDisable
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	2
	.global	MFDE_ConfigReg
	.type	MFDE_ConfigReg, %function
MFDE_ConfigReg:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	ip, .L869
	mov	lr, r3
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L867
	cmp	r2, #0
	ble	.L868
	mov	r3, r2
	str	ip, [sp]
	ldr	r2, .L869+4
	mov	r0, #32
	ldr	r1, .L869+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L868:
	movw	r3, #1228
	ldr	ip, .L869+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L867:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L870:
	.align	2
.L869:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.59384, %object
	.size	__func__.59384, 22
__func__.59384:
	.ascii	"VDMHAL_V5R6C1_OpenHAL\000"
	.space	2
	.type	__func__.59458, %object
	.size	__func__.59458, 25
__func__.59458:
	.ascii	"VDMHAL_V5R6C1_CalcFsSize\000"
	.space	3
	.type	__func__.59484, %object
	.size	__func__.59484, 24
__func__.59484:
	.ascii	"VDMHAL_V5R6C1_CalcFsNum\000"
	.type	__func__.59527, %object
	.size	__func__.59527, 32
__func__.59527:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.59528, %object
	.size	__FUNCTION__.59528, 32
__FUNCTION__.59528:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Normal\000"
	.type	__func__.59470, %object
	.size	__func__.59470, 33
__func__.59470:
	.ascii	"VDMHAL_V5R6C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.59610, %object
	.size	__func__.59610, 34
__func__.59610:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.59632, %object
	.size	__func__.59632, 23
__func__.59632:
	.ascii	"VDMHAL_V5R6C1_ResetVdm\000"
	.space	1
	.type	__func__.59642, %object
	.size	__func__.59642, 35
__func__.59642:
	.ascii	"VDMHAL_V5R6C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.59662, %object
	.size	__func__.59662, 24
__func__.59662:
	.ascii	"VDMHAL_V5R6C1_GlbResetX\000"
	.type	__func__.59652, %object
	.size	__func__.59652, 23
__func__.59652:
	.ascii	"VDMHAL_V5R6C1_GlbReset\000"
	.space	1
	.type	__func__.59674, %object
	.size	__func__.59674, 28
__func__.59674:
	.ascii	"VDMHAL_V5R6C1_ClearIntState\000"
	.type	__func__.59680, %object
	.size	__func__.59680, 31
__func__.59680:
	.ascii	"VDMHAL_V5R6C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.59686, %object
	.size	__func__.59686, 22
__func__.59686:
	.ascii	"VDMHAL_V5R6C1_MaskInt\000"
	.space	2
	.type	__func__.59699, %object
	.size	__func__.59699, 24
__func__.59699:
	.ascii	"VDMHAL_V5R6C1_EnableInt\000"
	.type	__func__.59708, %object
	.size	__func__.59708, 23
__func__.59708:
	.ascii	"VDMHAL_V5R6C1_CheckReg\000"
	.space	1
	.type	__func__.59722, %object
	.size	__func__.59722, 26
__func__.59722:
	.ascii	"VDMHAL_V5R6C1_ReadMMUMask\000"
	.space	2
	.type	__func__.59727, %object
	.size	__func__.59727, 27
__func__.59727:
	.ascii	"VDMHAL_V5R6C1_WriteMMUMask\000"
	.space	1
	.type	__func__.59759, %object
	.size	__func__.59759, 25
__func__.59759:
	.ascii	"VDMHAL_V5R6C1_PrepareDec\000"
	.space	3
	.type	__func__.59764, %object
	.size	__func__.59764, 25
__func__.59764:
	.ascii	"VDMHAL_V5R6C1_IsVdmReady\000"
	.space	3
	.type	__func__.59769, %object
	.size	__func__.59769, 23
__func__.59769:
	.ascii	"VDMHAL_V5R6C1_IsVdmRun\000"
	.space	1
	.type	__func__.59775, %object
	.size	__func__.59775, 27
__func__.59775:
	.ascii	"VDMHAL_V5R6C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.59785, %object
	.size	__func__.59785, 31
__func__.59785:
	.ascii	"VDMHAL_V5R6C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.59800, %object
	.size	__func__.59800, 33
__func__.59800:
	.ascii	"VDMHAL_V5R6C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.59873, %object
	.size	__func__.59873, 23
__func__.59873:
	.ascii	"VDMHAL_V5R6C1_CfgRpMsg\000"
	.space	1
	.type	__func__.59850, %object
	.size	__func__.59850, 24
__func__.59850:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.59884, %object
	.size	__func__.59884, 23
__func__.59884:
	.ascii	"VDMHAL_V5R6C1_CfgRpReg\000"
	.space	1
	.type	__func__.59897, %object
	.size	__func__.59897, 28
__func__.59897:
	.ascii	"VDMHAL_V5R6C1_MakeDecReport\000"
	.type	__func__.59936, %object
	.size	__func__.59936, 28
__func__.59936:
	.ascii	"VDMHAL_V5R6C1_PrepareRepair\000"
	.type	__func__.60124, %object
	.size	__func__.60124, 15
__func__.60124:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.59943, %object
	.size	__func__.59943, 28
__func__.59943:
	.ascii	"VDMHAL_V5R6C1_StartHwRepair\000"
	.type	__func__.59982, %object
	.size	__func__.59982, 28
__func__.59982:
	.ascii	"VDMHAL_V5R6C1_CalVdhClkSkip\000"
	.type	__func__.60006, %object
	.size	__func__.60006, 28
__func__.60006:
	.ascii	"VDMHAL_V5R6C1_StartHwDecode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pOpenParam = NULL error!\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"MemBaseAddr = 0 error!\000" )
	.space	1
.LC3:
	ASCII(.ascii	"VDMHAL_V5R6C1_OpenHAL: Size error!\000" )
	.space	1
.LC4:
	ASCII(.ascii	"VdhId is wrong!!!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"BPDRegVirAddr %p\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"!!!!!! HAL memory not enouph! need %d, have %d\012\000" )
.LC8:
	ASCII(.ascii	"image size out of range\000" )
.LC9:
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC/VP9/AVS2 10 bit\012\000" )
.LC10:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC11:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V5R6C1_ArrangeMe" )
	ASCII(.ascii	"m!\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"Report arrange frame buffer: wxh %dx%d, FsNum %d, P" )
	ASCII(.ascii	"mvNum %d\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"Report arrange frame buffer only: wxh %dx%d, FsNum " )
	ASCII(.ascii	"%d, PmvNum %d\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"VidStd Invalid\000" )
	.space	1
.LC15:
	ASCII(.ascii	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d" )
	ASCII(.ascii	", UVCompRatio %d\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"VDMHAL_V5R6C1_CalcFsSize err!\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: " )
	ASCII(.ascii	"%#x\012\000" )
.LC18:
	ASCII(.ascii	"DFS, report event. Size: 0x%x, Num: %d, RefChanged:" )
	ASCII(.ascii	" %d\012\000" )
.LC19:
	ASCII(.ascii	"pVdmMemArrange is NULL\000" )
	.space	1
.LC20:
	ASCII(.ascii	"DFS, no ref frame!\012\000" )
.LC21:
	ASCII(.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"VDMHAL_V5R6C1_ArrangeMem Mem addr is NULL\000" )
	.space	2
.LC23:
	ASCII(.ascii	"'pVdmMemArrange' is NULL\000" )
	.space	3
.LC24:
	ASCII(.ascii	"MemSize not enough for pmv slot\000" )
.LC25:
	ASCII(.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight" )
	ASCII(.ascii	" failed!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"ImgSlotLen > ChanSlotLen\000" )
	.space	3
.LC27:
	ASCII(.ascii	"cann't allocate img slot\000" )
	.space	3
.LC28:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC29:
	ASCII(.ascii	"VDMHAL_V5R6C1_ResetVdm: map vdm register fail, vir(" )
	ASCII(.ascii	"reg) = (%p)\012\000" )
.LC30:
	ASCII(.ascii	"%s module id %d failed!\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"%s module id %d success!\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"%s: map vdm register 0x%x failed!\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"%s VdhId %d failed!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%s VdhId %d success!\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC38:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC39:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC40:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC41:
	ASCII(.ascii	"%s: pDecParam(%p) = NULL\012\000" )
	.space	2
.LC42:
	ASCII(.ascii	"VDM register not mapped yet!\000" )
	.space	3
.LC43:
	ASCII(.ascii	"VDM register not mapped yet!\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"can NOT map vir addr for up-msg\000" )
.LC45:
	ASCII(.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"WriteMsgSlot error!\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC49:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC50:
	ASCII(.ascii	"align_mb error\012\000" )
.LC51:
	ASCII(.ascii	"[%s][%d]sclie_num is wrong! %d \012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC53:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC54:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC59:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC60:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC62:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC65:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC66:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
