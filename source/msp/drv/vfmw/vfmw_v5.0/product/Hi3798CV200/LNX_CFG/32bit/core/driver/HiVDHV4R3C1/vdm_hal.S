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
	.global	VDMHAL_V4R3C1_GetHalMemSize
	.type	VDMHAL_V4R3C1_GetHalMemSize, %function
VDMHAL_V4R3C1_GetHalMemSize:
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
	.size	VDMHAL_V4R3C1_GetHalMemSize, .-VDMHAL_V4R3C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V4R3C1_OpenHAL
	.type	VDMHAL_V4R3C1_OpenHAL, %function
VDMHAL_V4R3C1_OpenHAL:
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
	bl	H264HAL_V4R3C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V4R3C1_InitHal
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
	.size	VDMHAL_V4R3C1_OpenHAL, .-VDMHAL_V4R3C1_OpenHAL
	.align	2
	.global	VDMHAL_V4R3C1_CloseHAL
	.type	VDMHAL_V4R3C1_CloseHAL, %function
VDMHAL_V4R3C1_CloseHAL:
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
	.size	VDMHAL_V4R3C1_CloseHAL, .-VDMHAL_V4R3C1_CloseHAL
	.align	2
	.global	VDMHAL_V4R3C1_CalcFsSize
	.type	VDMHAL_V4R3C1_CalcFsSize, %function
VDMHAL_V4R3C1_CalcFsSize:
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
	beq	.L49
	ldr	r2, [fp, #4]
	ldr	r9, .L55
	cmp	r2, #17
	beq	.L50
	add	r4, r8, #31
	ldr	r0, [r9, r7, asl #2]
	mov	r5, r5, asl #4
	bic	r4, r4, #31
	add	r5, r5, #255
	mov	r2, #0
	bic	r1, r5, #255
	str	r2, [fp, #-60]
	str	r1, [fp, #-56]
	str	r2, [fp, #-64]
.L35:
	ldr	r2, [r0, #1136]
	cmp	r2, #1
	movne	r5, #0
	movne	ip, r5
	movne	r8, r5
	beq	.L51
.L37:
	cmp	r3, #1
	beq	.L52
	ldr	r3, [fp, #-56]
	add	r2, r8, r8, lsl #1
	ldr	r1, [fp, #-60]
	mul	r4, r4, r3
	ldr	r3, [fp, #-64]
	mul	r3, r3, r1
	add	r1, r4, r4, lsl #1
	mov	r6, r1, lsr #1
	add	r3, r3, r3, lsl #1
	add	r3, r6, r3, lsr #1
	add	r6, r3, r2, lsr #1
.L39:
	add	r2, r0, #290816
	ldr	r1, [r2, #768]
	cmp	r1, #0
	beq	.L53
.L40:
	ldr	r3, [fp, #4]
	add	r1, r0, #294912
	cmp	r3, #17
	add	r3, r10, r10, lsr #31
	str	r6, [r1, #240]
	mov	r3, r3, asr #1
	str	ip, [r2, #3116]
	str	r5, [r2, #3120]
	str	r3, [r2, #3156]
	beq	.L41
	ldr	r3, [r2, #776]
	ldr	r1, [fp, #-56]
	cmp	r3, #32
	ldr	ip, [fp, #4]
	mov	r5, r1, asl #4
	movge	r3, #32
	cmp	ip, #16
	str	r5, [r2, #3108]
	add	r1, r4, r8
	mov	r5, r5, lsr #1
	str	r3, [r2, #3160]
	str	r5, [r2, #3112]
	str	r1, [r2, #3140]
	beq	.L54
.L43:
	ldr	r3, [r9, r7, asl #2]
	mov	r0, #1024
	add	r6, r6, #1056
	add	r2, r3, #294912
	add	r1, r10, r6
	str	r10, [r2, #244]
	str	r0, [r2, #252]
	ldrsb	r3, [r3, #44]
	cmp	r3, #1
	ldr	r3, [fp, #8]
	addeq	r1, r1, r0
	cmp	r3, #0
	beq	.L47
	str	r6, [r3, #4]
	mov	r2, #1024
	ldr	r3, [r9, r7, asl #2]
	mov	r0, #0
	ldr	ip, [fp, #8]
	add	r3, r3, #290816
	ldr	r3, [r3, #776]
	str	r10, [ip, #12]
	str	r3, [ip, #8]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #290816
	ldr	r3, [r3, #3160]
	str	r1, [ip]
	str	r2, [ip, #20]
	str	r3, [ip, #16]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #294912
	str	r6, [r3, #248]
.L33:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L54:
	ldr	r3, [r0, #1444]
	cmp	r3, #8
	ble	.L43
	ldr	r1, [fp, #-64]
	add	r8, r8, r8, lsl #1
	ldr	r0, [fp, #-60]
	add	r4, r4, r4, lsl #1
	mul	r3, r0, r1
	mov	r0, r1, asl #5
	mov	r1, r8, lsr #1
	str	r0, [r2, #3124]
	add	r4, r1, r4, lsr #1
	mov	r0, #31
	ldr	r1, .L55+4
	str	r4, [r2, #3132]
	str	r3, [r2, #3136]
	bl	dprint_vfmw
	b	.L43
.L53:
	ldr	r3, .L55+8
	add	r0, r2, #3104
	mov	r2, #1248
	str	ip, [fp, #-68]
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r0, [r9, r7, asl #2]
	ldr	ip, [fp, #-68]
	add	r2, r0, #290816
	b	.L40
.L41:
	ldr	r3, [fp, #-56]
	add	r4, r4, r8
	str	r4, [r2, #3140]
	mov	r5, r3, asl #4
	mov	r3, #1
	str	r5, [r2, #3108]
	str	r3, [r2, #3160]
	mov	r5, r5, lsr r3
	str	r5, [r2, #3112]
	b	.L43
.L52:
	mov	r3, r6, asl #5
	add	r6, r3, r6, lsl #4
	ldr	r3, [fp, #-56]
	mul	r4, r4, r3
	mul	r6, r3, r6
	b	.L39
.L51:
	add	r2, ip, #508
	add	ip, ip, #1020
	add	r2, r2, #3
	add	ip, ip, #2
	cmp	r2, #0
	movge	ip, r2
	adds	r2, r8, #63
	addmi	r8, r8, #126
	movpl	r8, r2
	mov	ip, ip, asr #9
	mov	r8, r8, asr #6
	mov	ip, ip, asl #4
	mov	r8, r8, asl #5
	mul	r8, ip, r8
	mov	r5, r8
	b	.L37
.L49:
	ldr	r9, .L55
	add	r5, ip, #255
	bic	r2, r5, #255
	str	r2, [fp, #-56]
	ldr	r0, [r9, r7, asl #2]
	ldr	r2, [r0, #1444]
	cmp	r2, #8
	ble	.L45
	ldr	r1, [fp, #-56]
	add	r2, r8, #31
	bic	r2, r2, #31
	str	r2, [fp, #-60]
	mov	r1, r1, lsr #2
	str	r1, [fp, #-64]
	b	.L35
.L45:
	mov	r2, #0
	str	r2, [fp, #-60]
	str	r2, [fp, #-64]
	b	.L35
.L50:
	add	r5, ip, #255
	add	r4, r8, #63
	mov	r2, #0
	bic	r1, r5, #255
	str	r2, [fp, #-60]
	bic	r4, r4, #63
	str	r1, [fp, #-56]
	ldr	r0, [r9, r7, asl #2]
	str	r2, [fp, #-64]
	b	.L35
.L31:
	ldr	r3, .L55+12
	mov	r0, #0
	ldr	r2, .L55+16
	ldr	r1, .L55+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L47:
	ldr	r0, [fp, #8]
	b	.L33
.L56:
	.align	2
.L55:
	.word	s_pstVfmwChan
	.word	.LC9
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalcFsSize, .-VDMHAL_V4R3C1_CalcFsSize
	.align	2
	.global	VDMHAL_V4R3C1_GetRpuSize
	.type	VDMHAL_V4R3C1_GetRpuSize, %function
VDMHAL_V4R3C1_GetRpuSize:
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
	.size	VDMHAL_V4R3C1_GetRpuSize, .-VDMHAL_V4R3C1_GetRpuSize
	.align	2
	.global	VDMHAL_V4R3C1_CalcFsNum
	.type	VDMHAL_V4R3C1_CalcFsNum, %function
VDMHAL_V4R3C1_CalcFsNum:
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
	beq	.L63
	cmp	r1, #17
	ldr	ip, .L65
	beq	.L64
	ldr	lr, [ip, r0, asl #2]
	add	r0, lr, #290816
	ldr	r1, [r0, #776]
	cmp	r1, #32
	movge	r1, #32
	str	r1, [r0, #3160]
	ldr	r1, [lr, #568]
	cmp	r1, #2
	ldreq	r1, [r0, #780]
	streq	r1, [r0, #3160]
.L62:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #0
	add	r1, r1, #290816
	ldr	r1, [r1, #776]
	str	r1, [r3, #8]
	ldr	r2, [ip, r2, asl #2]
	add	r2, r2, #290816
	ldr	r2, [r2, #3160]
	str	r2, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L64:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #1
	add	r1, r1, #290816
	str	r0, [r1, #3160]
	b	.L62
.L63:
	ldr	r2, .L65+4
	mov	r0, #1
	ldr	r1, .L65+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L66:
	.align	2
.L65:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+52
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalcFsNum, .-VDMHAL_V4R3C1_CalcFsNum
	.align	2
	.global	VDMHAL_V4R3C1_DynamicAllocFrame
	.type	VDMHAL_V4R3C1_DynamicAllocFrame, %function
VDMHAL_V4R3C1_DynamicAllocFrame:
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
	ldr	r6, .L90
	mov	r8, r1
	mov	r4, r0
	mov	r7, r2
	mov	r5, r3
	ldr	r1, [r6, r0, asl #2]
	add	r1, r1, #290816
	add	r1, r1, #800
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	bne	.L88
.L68:
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #0
	mov	r1, #255
	add	r2, r2, #290816
	add	r2, r2, #800
.L69:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L69
	cmp	r8, #1920
	cmple	r7, #1088
	bgt	.L72
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L90
	ldr	r2, [r3, #36]
	cmp	r2, #24
	beq	.L72
	add	r3, r3, #294912
	ldr	r3, [r3, #876]
	cmp	r3, #0
	beq	.L89
.L72:
	ldr	r2, [r5, #8]
	ldr	r3, [r6, r4, asl #2]
.L71:
	ldr	r1, [r3, #1392]
	add	r3, r3, #290816
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #780]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L90
	ldr	r2, [r3, #568]
	subs	r0, r0, #17
	movne	r0, #1
	cmp	r2, #2
	movne	r0, #0
	cmp	r0, #0
	addne	r3, r3, #290816
	mov	r0, #1
	ldrne	r3, [r3, #780]
	strne	r3, [r5, #16]
	ldrne	r3, [r1, r4, asl #2]
	add	r1, r3, #294912
	add	r2, r3, #262144
	mov	r3, #0
	str	r3, [r1, #280]
	mov	r3, r7
	str	r0, [r2, #1936]
	mov	r2, r8
	str	r0, [r1, #820]
	mov	r0, #31
	ldr	ip, [r5, #8]
	ldr	lr, [r5, #16]
	ldr	r1, .L90+4
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L90+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L74
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
.L74:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L90+12
	mov	r2, #528
	add	r0, r0, #294912
	add	r0, r0, #288
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #0
	mov	r0, r4
	add	r3, r3, #294912
	str	r2, [r3, #816]
	bl	FSP_ClearContextAll
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L88:
	ldr	r1, .L90+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L68
.L89:
	ldr	r2, [r5, #8]
	add	r2, r2, #4
	str	r2, [r5, #8]
	ldr	r3, [r1, r4, asl #2]
	b	.L71
.L91:
	.align	2
.L90:
	.word	s_pstVfmwChan
	.word	.LC12
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_DynamicAllocFrame, .-VDMHAL_V4R3C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.type	VDMHAL_V4R3C1_DynamicAllocFrame_Only, %function
VDMHAL_V4R3C1_DynamicAllocFrame_Only:
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
	ldr	ip, .L97
	ldr	lr, [r3, #8]
	mov	r4, r3
	mov	r7, r0
	mov	r3, r2
	ldr	ip, [ip, r0, asl #2]
	mov	r6, r1
	mov	r5, r2
	mov	r0, #31
	add	ip, ip, #290816
	mov	r2, r1
	ldr	r1, .L97+4
	str	lr, [ip, #780]
	ldr	ip, [r4, #8]
	ldr	lr, [r4, #16]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L97+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L92
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
.L92:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L98:
	.align	2
.L97:
	.word	s_pstVfmwChan
	.word	.LC13
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_DynamicAllocFrame_Only, .-VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem_Normal
	.type	VDMHAL_V4R3C1_ArrangeMem_Normal, %function
VDMHAL_V4R3C1_ArrangeMem_Normal:
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
	bhi	.L129
	ldr	r5, .L137
	ldr	r1, [r5, r4, asl #2]
	add	r2, r1, #290816
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #772]
	cmp	r3, #2
	str	r2, [fp, #-72]
	beq	.L130
	ldr	ip, [r1, #1148]
	mov	r2, #1
	ldr	r3, [r1, #1140]
	mov	r0, r2
	str	r2, [r1, #1136]
	str	ip, [sp, #4]
	ldr	ip, [r1, #1144]
	ldr	r1, .L137+4
	str	ip, [sp]
	bl	dprint_vfmw
.L103:
	sub	r7, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r6
	mov	r0, r4
	mov	r3, r7
	bl	VDMHAL_V4R3C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r7, [sp, #4]
	mov	r2, r9
	str	r6, [sp]
	mov	r1, r8
	mov	r10, r0
	mov	r0, r4
	bl	VDMHAL_V4R3C1_CalcFsSize
	orrs	r3, r0, r10
	bne	.L131
	ldr	r1, [fp, #-72]
	ldr	ip, [r5, r4, asl #2]
	ldr	r6, [fp, #-68]
	add	r3, ip, #290816
	ldr	r2, .L137
	cmp	r1, r6
	ldr	r10, [r3, #776]
	ldr	r1, [r3, #792]
	beq	.L132
.L106:
	str	r1, [sp, #4]
	mov	r3, r6
	ldr	r2, .L137+8
	mov	r0, #31
	ldr	r1, .L137+12
	str	r10, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, r4, asl #2]
	mov	r1, r8
	mov	r0, r4
	add	r3, r3, #290816
	ldr	r2, [r3, #768]
	str	r6, [r3, #772]
	mov	r3, r7
	cmp	r2, #0
	mov	r2, r9
	beq	.L133
	bl	VDMHAL_V4R3C1_DynamicAllocFrame_Only
.L109:
	ldr	ip, [r5, r4, asl #2]
	mov	r3, r10
	mov	r2, r6
	ldr	r1, .L137+16
	add	ip, ip, #290816
	mov	r0, #31
	ldr	ip, [ip, #792]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L137+20
	ldr	r4, [r5, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #294912
	blx	r3
	mov	r3, #2
	str	r0, [r4, #256]
.L101:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L132:
	cmp	r1, #1
	beq	.L106
	ldr	r0, [r3, #768]
	cmp	r0, #1
	beq	.L106
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L134
	add	r1, ip, #294912
	cmp	r10, #0
	add	r0, r3, #3104
	str	r0, [fp, #-80]
	ldr	r1, [r1, #240]
	movne	r2, ip
	str	r1, [fp, #-72]
	beq	.L135
.L111:
	add	r2, r2, #290816
	ldr	r2, [r2, #780]
	cmp	r2, #30
	bgt	.L136
.L112:
	str	r2, [r3, #3152]
	mov	r0, #8
	str	r3, [fp, #-76]
	ldr	r3, .L137+20
	str	ip, [fp, #-84]
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r1, [r5, r4, asl #2]
	ldr	r3, [fp, #-76]
	add	r10, r1, #294912
	ldr	ip, [fp, #-84]
	ldr	r2, [r10, #280]
	cmp	r2, #0
	beq	.L117
	ldr	r2, [r3, #3164]
	movw	r7, #7963
	ldr	r0, [r3, #3160]
	movt	r7, 1
	add	r7, r2, r7
	add	r1, r1, #290816
	add	r1, r1, #832
	mov	lr, #0
	mov	r6, r0
	mov	r0, r2, asl #4
	sub	r0, r0, r2, asl #2
	add	r2, r2, #1
	add	r0, r0, #290816
	add	r7, ip, r7, lsl #2
	add	r0, r0, #3568
	mov	r9, #1
	add	r0, ip, r0
	mov	r8, r2
	str	ip, [fp, #-76]
	str	r4, [fp, #-84]
.L116:
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
	str	ip, [r3, #3164]
	ldr	r2, [r1, #-28]
	cmp	r2, #255
	beq	.L114
	ldr	ip, [r3, #3172]
	add	r4, ip, #1
	mov	r2, ip, asl #4
	sub	r2, r2, ip, asl #2
	ldr	ip, [r1, #16]
	add	r2, r3, r2
	str	ip, [r2, #3952]
	str	r4, [r3, #3172]
.L114:
	ldr	r2, [r3, #3168]
	cmp	r2, r6
	bcs	.L115
	ldr	r4, [r1, #-24]
	ldr	ip, [fp, #-76]
	cmp	r4, #255
	add	ip, ip, r2, lsl #3
	add	r2, r2, #1
	ldrne	r4, [r1, #32]
	add	ip, ip, #290816
	strneb	r9, [ip, #3316]
	strne	r4, [ip, #3312]
	strne	r2, [r3, #3168]
.L115:
	ldr	r2, [r10, #280]
	add	r1, r1, #72
	cmp	lr, r2
	bcc	.L116
	ldr	r4, [fp, #-84]
.L117:
	ldr	r3, .L137+20
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	ldr	r2, .L137+20
	mov	r1, #1
	add	r3, r3, #294912
	mov	r0, #8
	str	r1, [r3, #284]
	ldr	r2, [r2, #16]
	blx	r2
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L133:
	bl	VDMHAL_V4R3C1_DynamicAllocFrame
	b	.L109
.L130:
	mvn	r3, #0
	str	r0, [r1, #1136]
	str	r0, [r1, #1140]
	str	r3, [r1, #1144]
	str	r3, [r1, #1148]
	b	.L103
.L135:
	ldr	r1, .L137+24
	mov	r0, #31
	str	r3, [fp, #-88]
	str	r2, [fp, #-84]
	str	ip, [fp, #-76]
	bl	dprint_vfmw
	ldr	r2, [fp, #-84]
	ldr	ip, [fp, #-76]
	ldr	r3, [fp, #-88]
	ldr	r2, [r2, r4, asl #2]
	b	.L111
.L136:
	ldr	r1, .L137+28
	mov	r0, #31
	str	r3, [fp, #-84]
	str	ip, [fp, #-76]
	bl	dprint_vfmw
	ldr	r1, [r5, r4, asl #2]
	mov	r0, #30
	mov	r2, r0
	ldr	r3, [fp, #-84]
	add	r1, r1, #290816
	ldr	ip, [fp, #-76]
	str	r0, [r1, #780]
	b	.L112
.L129:
	ldr	r3, .L137+32
	ldr	r2, .L137+36
	ldr	r1, .L137+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L101
.L131:
	ldr	r1, .L137+44
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L101
.L134:
	ldr	r3, .L137+48
	mov	r0, r1
	ldr	r2, .L137+52
	ldr	r1, .L137+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L101
.L138:
	.align	2
.L137:
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
	.size	VDMHAL_V4R3C1_ArrangeMem_Normal, .-VDMHAL_V4R3C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem_Specific
	.type	VDMHAL_V4R3C1_ArrangeMem_Specific, %function
VDMHAL_V4R3C1_ArrangeMem_Specific:
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
	subs	r5, r2, #0
	str	r3, [fp, #-56]
	mov	r9, r1
	ldmib	fp, {r7, r10}
	ldr	r3, [fp, #12]
	ldr	r6, [fp, #28]
	beq	.L195
	sub	r1, r7, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L142
	sub	r1, r10, #32
	cmp	r1, r2
	bhi	.L142
	cmp	r6, #0
	beq	.L196
	ldr	lr, .L203
	cmp	r3, #20
	str	r0, [fp, #-64]
	mov	r2, #1232
	mov	r1, #0
	mov	r0, r6
	ldr	r4, [lr, #48]
	movge	r3, #20
	str	r3, [fp, #-60]
	blx	r4
	sub	r2, fp, #44
	add	r1, r10, #15
	add	r8, r7, #15
	mov	r0, r9
	mov	r3, r1, asr #4
	sub	r1, fp, #52
	str	r3, [r2, #-4]!
	mov	r8, r8, asr #4
	str	r3, [fp, #-80]
	str	r8, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #-60]
	ldr	ip, [fp, #-64]
	mul	r1, r3, r0
	mov	r2, r0
	ldr	r0, [fp, #-56]
	cmp	r1, r0
	str	r1, [fp, #-76]
	ldrge	r3, .L203+4
	bge	.L193
	add	r4, r5, #1020
	add	r1, r2, r2, lsr #31
	add	r4, r4, #3
	cmp	r9, #16
	bic	r4, r4, #1020
	str	r3, [r6, #56]
	bic	r4, r4, #3
	mov	r3, r1, asr #1
	rsb	r1, r5, r4
	str	r3, [r6, #52]
	str	r1, [fp, #-64]
	beq	.L197
	cmp	r9, #17
	beq	.L198
	mov	r8, r8, asl #4
	add	r1, r10, #63
	add	r8, r8, #255
	add	r3, r10, #31
	bic	r8, r8, #255
	bic	r3, r3, #31
	str	r3, [fp, #-60]
	mov	r3, #0
	str	r3, [fp, #-68]
	str	r3, [fp, #-72]
.L148:
	add	r3, r7, #508
	add	r7, r7, #1020
	add	r3, r3, #3
	add	r7, r7, #2
	cmp	r3, #0
	add	r10, r1, #63
	ldr	r0, [fp, #20]
	movlt	r3, r7
	cmp	r1, #0
	mov	r3, r3, asr #9
	movlt	r1, r10
	cmp	r0, #1
	mov	r10, r3, asl #9
	mov	r1, r1, asr #6
	mov	r3, r3, asl #4
	mov	r0, r8, asl #4
	mul	r10, r1, r10
	str	r3, [r6, #12]
	str	r0, [r6, #4]
	mov	r3, r8, asl #3
	str	r3, [r6, #8]
	str	r10, [r6, #16]
	beq	.L199
	ldr	r1, [fp, #-68]
	add	r7, r10, r10, lsl #1
	ldr	r3, [fp, #-72]
	mul	r3, r3, r1
	ldr	r1, [fp, #-60]
	mul	r1, r8, r1
	add	r3, r3, r3, lsl #1
	add	r3, r3, r3, lsr #31
	add	r1, r1, r1, lsl #1
	mov	r3, r3, asr #1
	add	r3, r3, r1, asr #1
	add	r7, r3, r7, lsr #1
.L152:
	ldr	r3, [fp, #24]
	cmp	r3, #0
	blt	.L153
	mov	r0, r3
	str	r2, [fp, #-84]
	bl	VCTRL_GetChanWidth
	str	r0, [fp, #-80]
	ldr	r0, [fp, #24]
	bl	VCTRL_GetChanHeight
	ldr	r1, [fp, #-80]
	ldr	r2, [fp, #-84]
	cmn	r0, #1
	cmnne	r1, #1
	beq	.L200
	ldr	r3, [fp, #20]
	add	r1, r1, #15
	bic	r1, r1, #15
	cmp	r3, #1
	add	ip, r1, #255
	add	r3, r0, #15
	bic	ip, ip, #255
	bic	r3, r3, #15
	beq	.L201
	add	r0, r1, #508
	adds	lr, r3, #63
	add	r0, r0, #3
	addmi	lr, r3, #126
	cmp	r0, #0
	add	r1, r1, #1020
	add	r1, r1, #2
	ldr	r3, [fp, #-72]
	movge	r1, r0
	mov	r0, lr, asr #6
	ldr	lr, [fp, #-68]
	mul	ip, r0, ip
	mul	lr, r3, lr
	mov	r3, r1, asr #9
	mov	r1, r0, asl #7
	mov	r3, r3, asl #4
	sub	r0, r1, r0, asl #5
	mul	r0, r3, r0
	add	lr, lr, lr, lsl #1
	mov	r3, ip, asl #7
	add	lr, lr, lr, lsr #31
	sub	ip, r3, ip, asl #5
	add	ip, ip, lr, asr #1
	add	r0, ip, r0, lsr #1
.L156:
	cmp	r7, r0
	ldrgt	r3, .L203+8
	bgt	.L193
	ldr	ip, [fp, #24]
.L153:
	ldr	r3, [fp, #-60]
	cmp	ip, #0
	cmpge	r9, #16
	mul	r3, r8, r3
	mvn	r8, ip
	mov	r8, r8, lsr #31
	add	r1, r10, r3
	str	r1, [r6, #36]
	str	r3, [fp, #-60]
	bne	.L158
	ldr	r1, .L203+12
	str	r2, [fp, #-84]
	str	ip, [fp, #-80]
	ldr	r0, [r1, ip, asl #2]
	add	r0, r0, #294912
	add	r0, r0, #888
	bl	IsMain10Profile
	ldr	ip, [fp, #-80]
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	bne	.L202
.L158:
	ldr	r3, [fp, #16]
	cmp	r3, #0
	streq	r3, [r6, #48]
	beq	.L161
	cmp	r9, #3
	cmpne	r9, #0
	sub	r9, r9, #16
	ldr	r1, [fp, #-76]
	movne	r3, #1
	moveq	r3, #0
	cmp	r9, #1
	movls	r9, #0
	andhi	r9, r3, #1
	ldr	r3, [fp, #-56]
	cmp	r9, #0
	str	ip, [fp, #-60]
	rsb	r0, r1, r3
	ldr	r3, [fp, #-64]
	str	r2, [fp, #-56]
	rsb	r0, r3, r0
	ldr	r3, [fp, #16]
	beq	.L162
	cmp	r3, #32
	mov	r1, r7
	movlt	r9, r3
	movge	r9, #32
	bl	__aeabi_idiv
	ldr	r2, [fp, #-56]
	ldr	ip, [fp, #-60]
	cmp	r9, r0
	movlt	r3, r9
	movge	r3, r0
	str	r3, [r6, #48]
	b	.L163
.L162:
	cmp	r3, #32
	mov	r1, r7
	movlt	r9, r3
	movge	r9, #32
	bl	__aeabi_idiv
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-56]
	cmp	r9, r0
	movlt	r3, r9
	movge	r3, r0
	str	r3, [r6, #48]
.L163:
	cmp	r3, #0
	ldrne	lr, [r6, #60]
	movne	r0, r6
	movne	r1, #0
	beq	.L161
.L166:
	add	r1, r1, #1
	str	r4, [r0, #464]
	cmp	r3, r1
	add	r4, r4, r7
	add	r0, r0, #12
	bne	.L166
	ldr	r1, [fp, #-64]
	mov	r0, #0
	mla	r7, r3, r7, r1
	add	r1, r3, lr
	add	lr, r6, #76
	str	r1, [r6, #60]
	add	r1, r7, r5
.L168:
	add	r0, r0, #1
	str	r1, [lr, #4]!
	cmp	r3, r0
	add	r1, r1, #32
	bne	.L168
	ldr	r4, [r6, #56]
	add	r7, r7, r3, lsl #5
	add	r5, r7, r5
	cmp	r4, #0
	beq	.L173
	ldr	r9, [r6, #64]
	mov	lr, r6
	mov	r0, r5
	mov	r1, #0
.L172:
	add	r1, r1, #1
	str	r0, [lr, #208]
	cmp	r4, r1
	add	r0, r0, r2
	add	lr, lr, #8
	bne	.L172
	add	r1, r9, r4
	str	r1, [r6, #64]
.L173:
	mla	r2, r4, r2, r7
	cmp	r8, #0
	str	r2, [r6]
	beq	.L171
	ldr	r1, .L203+12
	ldr	r1, [r1, ip, asl #2]
	cmp	r1, #0
	beq	.L171
	cmp	r3, #0
	add	r5, r2, r5
	beq	.L171
	mov	r0, r6
	mov	r1, #0
.L174:
	add	r1, r1, #1
	str	r5, [r0, #848]
	cmp	r1, r3
	add	r5, r5, #1024
	add	r0, r0, #12
	bne	.L174
.L171:
	mov	r0, #0
	add	r2, r2, r3, lsl #10
	str	r2, [r6]
.L190:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L197:
	cmp	ip, #0
	add	r8, r7, #255
	bic	r8, r8, #255
	blt	.L192
	ldr	r3, .L203+12
	str	r2, [fp, #-68]
	str	ip, [fp, #-60]
	ldr	r0, [r3, ip, asl #2]
	add	r0, r0, #294912
	add	r0, r0, #888
	bl	IsMain10Profile
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-68]
	cmp	r0, #0
	beq	.L192
	cmp	r8, #0
	add	r3, r8, #3
	add	r1, r10, #31
	str	r10, [fp, #-60]
	movge	r3, r8
	bic	r1, r1, #31
	mov	r3, r3, asr #2
	str	r1, [fp, #-68]
	str	r3, [fp, #-72]
	add	r1, r10, #63
	b	.L148
.L199:
	ldr	r3, [fp, #-80]
	mov	r7, r3, asl #4
	mul	r7, r8, r7
	add	r7, r7, r7, lsl #1
	b	.L152
.L192:
	mov	r3, #0
	add	r1, r10, #63
	str	r3, [fp, #-68]
	str	r3, [fp, #-72]
	str	r10, [fp, #-60]
	b	.L148
.L161:
	ldr	r3, .L203+16
.L193:
	ldr	r2, .L203+20
	mov	r0, #0
	ldr	r1, .L203+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L201:
	mul	r0, r3, ip
	add	r0, r0, r0, lsl #1
	b	.L156
.L198:
	add	r1, r10, #63
	add	r8, r7, #255
	mov	r3, #0
	bic	r0, r1, #63
	str	r3, [fp, #-68]
	bic	r8, r8, #255
	str	r0, [fp, #-60]
	str	r3, [fp, #-72]
	b	.L148
.L142:
	ldr	r3, .L203+28
	b	.L193
.L202:
	ldr	r1, [fp, #-68]
	add	r3, r3, r3, lsl #1
	str	r2, [fp, #-60]
	ldr	r2, [fp, #-72]
	mov	r3, r3, asr #1
	mul	lr, r2, r1
	add	r1, r10, r10, lsl #1
	mov	r0, r2, asl #5
	str	r0, [r6, #20]
	add	r3, r3, r1, lsr #1
	mov	r0, #0
	add	lr, lr, r10, lsr #1
	str	r3, [r6, #28]
	str	lr, [r6, #32]
	ldr	r1, .L203+32
	bl	dprint_vfmw
	ldr	ip, [fp, #-80]
	ldr	r2, [fp, #-60]
	b	.L158
.L195:
	mov	r0, r5
	ldr	r3, .L203+36
	ldr	r2, .L203+20
	ldr	r1, .L203+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L190
.L200:
	ldr	r1, .L203+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L190
.L196:
	mov	r0, r6
	ldr	r3, .L203+44
	ldr	r2, .L203+20
	ldr	r1, .L203+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L190
.L204:
	.align	2
.L203:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	.LC26
	.word	s_pstVfmwChan
	.word	.LC27
	.word	.LANCHOR0+176
	.word	.LC1
	.word	.LC8
	.word	.LC9
	.word	.LC22
	.word	.LC25
	.word	.LC23
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ArrangeMem_Specific, .-VDMHAL_V4R3C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem
	.type	VDMHAL_V4R3C1_ArrangeMem, %function
VDMHAL_V4R3C1_ArrangeMem:
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
	beq	.L208
	cmp	r4, #0
	blt	.L209
	mov	r0, r4
	str	ip, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r3, .L212
	ldr	r1, [fp, #-48]
	ldr	ip, [fp, #-52]
	ldr	r3, [r3, r4, asl #2]
	ldr	r3, [r3, #1384]
	cmp	r3, #1
	beq	.L211
.L207:
	mov	r3, r1
	str	r9, [sp, #24]
	mov	r1, r0
	str	r4, [sp, #20]
	mov	r2, r10
	str	r8, [sp, #16]
	str	ip, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V4R3C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L209:
	mov	r0, #21
	b	.L207
.L208:
	mov	r0, #16
	b	.L207
.L211:
	mov	r1, r0
	str	r9, [fp, #12]
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V4R3C1_ArrangeMem_Normal
.L213:
	.align	2
.L212:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ArrangeMem, .-VDMHAL_V4R3C1_ArrangeMem
	.align	2
	.global	VDMHAL_V4R3C1_ResetVdm
	.type	VDMHAL_V4R3C1_ResetVdm, %function
VDMHAL_V4R3C1_ResetVdm:
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
	subs	r6, r0, #0
	mov	r0, #0
	ble	.L215
	mov	r3, r6
	str	r0, [sp]
	ldr	r2, .L229
	ldr	r1, .L229+4
	bl	dprint_vfmw
.L214:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L215:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L227
	movw	r3, #1228
	ldr	r8, .L229+8
	mul	r3, r3, r6
	ldr	r5, .L229+12
	ldr	r2, [r5]
	ldr	r3, [r8, r3]
	ldr	r9, [r3, #36]
	ldr	r7, [r2, #120]
	tst	r7, #1
	beq	.L214
	ldr	r10, .L229+16
	mov	r3, #2
	bfi	r7, r3, #8, #2
	str	r7, [r2, #120]
	mov	r4, #0
	orr	r7, r7, #64
	ldr	r3, [r10, #112]
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	b	.L219
.L228:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L220
.L219:
	ldr	r3, [r10, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r2, [r3, #372]
	tst	r2, #4
	beq	.L228
	cmp	r4, #1000
	bge	.L220
	mov	r3, r6
	ldr	r2, .L229
	ldr	r1, .L229+20
	mov	r0, #0
	bl	dprint_vfmw
.L222:
	ldr	r2, [r5]
	bfc	r7, #6, #1
	ldr	r3, [r10, #112]
	str	r7, [r2, #120]
	bfc	r7, #8, #2
	blx	r3
	movw	r3, #1228
	mul	r6, r3, r6
	ldr	r3, [r5]
	str	r7, [r3, #120]
	ldr	r3, [r8, r6]
	str	r9, [r3, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	mov	r3, r6
	ldr	r2, .L229
	ldr	r1, .L229+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L222
.L227:
	ldr	r1, .L229+28
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L230:
	.align	2
.L229:
	.word	.LANCHOR0+212
	.word	.LC28
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ResetVdm, .-VDMHAL_V4R3C1_ResetVdm
	.align	2
	.global	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.type	VDMHAL_V4R3C1_SetSmmuPageTableAddr, %function
VDMHAL_V4R3C1_SetSmmuPageTableAddr:
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
	ldr	r3, .L237
	mov	r4, r0
	ldr	ip, [r3, #188]
	cmp	ip, #0
	beq	.L231
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	ip
	cmp	r4, #0
	bne	.L233
	ldr	r3, .L237+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L231:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L233:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L237+8
	ldr	r1, .L237+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L237+8
	ldr	r1, .L237+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L237+8
	ldr	r1, .L237+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L238:
	.align	2
.L237:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+236
	.word	.LC32
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_SetSmmuPageTableAddr, .-VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V4R3C1_EnableSmmu
	.type	VDMHAL_V4R3C1_EnableSmmu, %function
VDMHAL_V4R3C1_EnableSmmu:
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
	ldr	r3, .L240
	mov	r2, #8
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L241:
	.align	2
.L240:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_EnableSmmu, .-VDMHAL_V4R3C1_EnableSmmu
	.align	2
	.global	VDMHAL_V4R3C1_GlbResetX
	.type	VDMHAL_V4R3C1_GlbResetX, %function
VDMHAL_V4R3C1_GlbResetX:
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
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L254
	ldr	r5, .L256
	ldr	r3, [r5]
	ldr	r6, [r3, #120]
	tst	r6, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r8, .L256+4
	mov	r2, #2
	bfi	r6, r2, #8, #2
	str	r6, [r3, #120]
	mov	r4, #0
	orr	r6, r6, #16
	ldr	r3, [r8, #112]
	blx	r3
	ldr	r3, [r5]
	str	r6, [r3, #120]
	b	.L246
.L255:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L247
.L246:
	ldr	r2, [r8, #116]
	mov	r0, #30
	blx	r2
	ldr	r2, [r5]
	ldr	r2, [r2, #372]
	tst	r2, #1
	beq	.L255
	cmp	r4, #1000
	bge	.L247
	mov	r3, r7
	ldr	r2, .L256+8
	ldr	r1, .L256+12
	mov	r0, #0
	bl	dprint_vfmw
.L249:
	ldr	r2, [r5]
	bfc	r6, #4, #1
	ldr	r3, [r8, #112]
	str	r6, [r2, #120]
	bfc	r6, #8, #2
	blx	r3
	ldr	r3, [r5]
	str	r6, [r3, #120]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L247:
	mov	r3, r7
	ldr	r2, .L256+8
	ldr	r1, .L256+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L249
.L254:
	mov	r3, #0
	ldr	r2, .L256+8
	movt	r3, 63683
	ldr	r1, .L256+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L257:
	.align	2
.L256:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC35
	.word	.LC34
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GlbResetX, .-VDMHAL_V4R3C1_GlbResetX
	.align	2
	.global	VDMHAL_V4R3C1_GlbReset
	.type	VDMHAL_V4R3C1_GlbReset, %function
VDMHAL_V4R3C1_GlbReset:
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
	beq	.L260
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V4R3C1_GlbResetX
.L260:
	mov	r3, #0
	ldr	r2, .L261
	movt	r3, 63683
	ldr	r1, .L261+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L262:
	.align	2
.L261:
	.word	.LANCHOR0+296
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GlbReset, .-VDMHAL_V4R3C1_GlbReset
	.align	2
	.global	VDMHAL_V4R3C1_ClearIntState
	.type	VDMHAL_V4R3C1_ClearIntState, %function
VDMHAL_V4R3C1_ClearIntState:
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
	ldr	r7, .L279
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L279+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L276
	movw	r6, #1228
	ldr	r9, .L279+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L277
.L267:
	cmp	r4, #1
	beq	.L278
.L274:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L276:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L279+12
	ldr	r2, .L279+16
	bl	dprint_vfmw
.L263:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L278:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L274
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L263
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L263
.L277:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L267
.L268:
	ldr	r1, .L279+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L280:
	.align	2
.L279:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+320
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ClearIntState, .-VDMHAL_V4R3C1_ClearIntState
	.align	2
	.global	VDMHAL_V4R3C1_ClearMMUIntState
	.type	VDMHAL_V4R3C1_ClearMMUIntState, %function
VDMHAL_V4R3C1_ClearMMUIntState:
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
	bgt	.L286
	movw	r2, #1228
	ldr	r5, .L288
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L287
.L284:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L286:
	mov	r0, #0
	ldr	r2, .L288+4
	str	r0, [sp]
	ldr	r1, .L288+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L287:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L284
.L285:
	ldr	r1, .L288+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L289:
	.align	2
.L288:
	.word	g_HwMem
	.word	.LANCHOR0+348
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ClearMMUIntState, .-VDMHAL_V4R3C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V4R3C1_MaskInt
	.type	VDMHAL_V4R3C1_MaskInt, %function
VDMHAL_V4R3C1_MaskInt:
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
	bgt	.L295
	movw	r2, #1228
	ldr	r5, .L297
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L296
.L293:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L295:
	mov	r0, #0
	ldr	r2, .L297+4
	str	r0, [sp]
	ldr	r1, .L297+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L296:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L293
.L294:
	ldr	r1, .L297+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L298:
	.align	2
.L297:
	.word	g_HwMem
	.word	.LANCHOR0+380
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_MaskInt, .-VDMHAL_V4R3C1_MaskInt
	.align	2
	.global	VDMHAL_V4R3C1_GetIntMaskCfg
	.type	VDMHAL_V4R3C1_GetIntMaskCfg, %function
VDMHAL_V4R3C1_GetIntMaskCfg:
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
	.size	VDMHAL_V4R3C1_GetIntMaskCfg, .-VDMHAL_V4R3C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V4R3C1_EnableInt
	.type	VDMHAL_V4R3C1_EnableInt, %function
VDMHAL_V4R3C1_EnableInt:
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
	ldr	r2, .L313
	mov	r3, r0, asl #6
	ldr	r1, .L313+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L311
	movw	r5, #1228
	ldr	r6, .L313+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L312
.L306:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L311:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L313+12
	ldr	r2, .L313+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L312:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L306
.L307:
	ldr	r1, .L313+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L314:
	.align	2
.L313:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+404
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_EnableInt, .-VDMHAL_V4R3C1_EnableInt
	.align	2
	.global	VDMHAL_V4R3C1_CheckReg
	.type	VDMHAL_V4R3C1_CheckReg, %function
VDMHAL_V4R3C1_CheckReg:
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
	bgt	.L332
	movw	r4, #1228
	ldr	r6, .L334
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L333
.L318:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L324
.L326:
	.word	.L329
	.word	.L327
	.word	.L328
	.word	.L330
	.word	.L320
	.word	.L322
	.word	.L323
.L330:
	mov	r3, #40
.L325:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L329:
	mov	r3, #28
	b	.L325
.L328:
	mov	r3, #36
	b	.L325
.L327:
	mov	r3, #32
	b	.L325
.L323:
	movw	r3, #62272
	b	.L325
.L320:
	movw	r3, #61480
	b	.L325
.L322:
	movw	r3, #62304
	b	.L325
.L324:
	mov	r3, r7
	ldr	r2, .L334+4
	ldr	r1, .L334+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L333:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L319
	str	r8, [r6, r4]
	b	.L318
.L332:
	mov	r3, r5
	ldr	r2, .L334+4
	ldr	r1, .L334+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L319:
	ldr	r2, .L334+4
	ldr	r1, .L334+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L335:
	.align	2
.L334:
	.word	g_HwMem
	.word	.LANCHOR0+428
	.word	.LC39
	.word	.LC37
	.word	.LC38
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CheckReg, .-VDMHAL_V4R3C1_CheckReg
	.align	2
	.global	VDMHAL_V4R3C1_ReadMMUMask
	.type	VDMHAL_V4R3C1_ReadMMUMask, %function
VDMHAL_V4R3C1_ReadMMUMask:
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
	ble	.L339
	mov	r1, #1
	ldr	r2, .L340
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L340+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L339:
	movw	r0, #1228
	ldr	r2, .L340+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L341:
	.align	2
.L340:
	.word	.LANCHOR0+452
	.word	.LC40
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ReadMMUMask, .-VDMHAL_V4R3C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V4R3C1_WriteMMUMask
	.type	VDMHAL_V4R3C1_WriteMMUMask, %function
VDMHAL_V4R3C1_WriteMMUMask:
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
	ble	.L345
	mov	r1, #1
	ldr	r2, .L346
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L346+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L345:
	movw	r1, #1228
	ldr	r2, .L346+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L347:
	.align	2
.L346:
	.word	.LANCHOR0+480
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteMMUMask, .-VDMHAL_V4R3C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V4R3C1_PrepareDec
	.type	VDMHAL_V4R3C1_PrepareDec, %function
VDMHAL_V4R3C1_PrepareDec:
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
	beq	.L367
	cmp	r2, #0
	bgt	.L368
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
	cmp	r4, #17
	ldrls	pc, [pc, r4, asl #2]
	b	.L350
.L353:
	.word	.L363
	.word	.L354
	.word	.L355
	.word	.L356
	.word	.L350
	.word	.L357
	.word	.L358
	.word	.L350
	.word	.L359
	.word	.L360
	.word	.L361
	.word	.L361
	.word	.L361
	.word	.L362
	.word	.L350
	.word	.L363
	.word	.L364
	.word	.L365
.L363:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V4R3C1_StartDec
.L364:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V4R3C1_StartDec
.L365:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V4R3C1_StartDec
.L354:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V4R3C1_StartDec
.L355:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V4R3C1_StartDec
.L356:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V4R3C1_StartDec
.L357:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V4R3C1_StartDec
.L358:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V4R3C1_StartDec
.L359:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V4R3C1_StartDec
.L360:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V4R3C1_StartDec
.L361:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V4R3C1_StartDec
.L362:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V4R3C1_StartDec
.L367:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L369
	ldr	r1, .L369+4
	bl	dprint_vfmw
.L350:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L368:
	mov	r3, r2
	mov	r0, #0
	ldr	r2, .L369
	str	r0, [sp]
	ldr	r1, .L369+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L370:
	.align	2
.L369:
	.word	.LANCHOR0+508
	.word	.LC41
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_PrepareDec, .-VDMHAL_V4R3C1_PrepareDec
	.align	2
	.global	VDMHAL_V4R3C1_IsVdmReady
	.type	VDMHAL_V4R3C1_IsVdmReady, %function
VDMHAL_V4R3C1_IsVdmReady:
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
	ldr	r3, .L378
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L376
	cmp	r0, #0
	ble	.L377
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L378+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L378+8
	bl	dprint_vfmw
	mov	r0, #0
.L373:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L377:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L376:
	mov	r0, r3
	ldr	r2, .L378+4
	ldr	r3, .L378+12
	ldr	r1, .L378+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L373
.L379:
	.align	2
.L378:
	.word	g_HwMem
	.word	.LANCHOR0+536
	.word	.LC40
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdmReady, .-VDMHAL_V4R3C1_IsVdmReady
	.align	2
	.global	VDMHAL_V4R3C1_IsVdmRun
	.type	VDMHAL_V4R3C1_IsVdmRun, %function
VDMHAL_V4R3C1_IsVdmRun:
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
	ldr	r3, .L387
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L385
	cmp	r0, #0
	ble	.L386
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L387+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L387+8
	bl	dprint_vfmw
	mov	r0, r4
.L382:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L386:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L385:
	ldr	r1, .L387+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L382
.L388:
	.align	2
.L387:
	.word	g_HwMem
	.word	.LANCHOR0+564
	.word	.LC40
	.word	.LC43
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdmRun, .-VDMHAL_V4R3C1_IsVdmRun
	.align	2
	.global	VDMHAL_V4R3C1_IsVdhDecOver
	.type	VDMHAL_V4R3C1_IsVdhDecOver, %function
VDMHAL_V4R3C1_IsVdhDecOver:
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
	ldr	r3, .L399
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L397
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	r4, #2
	beq	.L394
	cmp	r4, #3
	beq	.L394
	cmp	r4, #1
	beq	.L398
	mov	r3, r4
	ldr	r2, .L399+4
	ldr	r1, .L399+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L394:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L398:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L397:
	mov	r0, r3
	ldr	r2, .L399+4
	ldr	r3, .L399+12
	ldr	r1, .L399+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L400:
	.align	2
.L399:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdhDecOver, .-VDMHAL_V4R3C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V4R3C1_IsVdhPartDecOver
	.type	VDMHAL_V4R3C1_IsVdhPartDecOver, %function
VDMHAL_V4R3C1_IsVdhPartDecOver:
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
	ldr	r3, .L411
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L409
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	r4, #1
	beq	.L405
	cmp	r4, #2
	bne	.L410
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L410:
	mov	r3, r4
	ldr	r2, .L411+4
	ldr	r1, .L411+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L405:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L409:
	mov	r0, r3
	ldr	r2, .L411+4
	ldr	r3, .L411+12
	ldr	r1, .L411+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L412:
	.align	2
.L411:
	.word	g_HwMem
	.word	.LANCHOR0+616
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdhPartDecOver, .-VDMHAL_V4R3C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V4R3C1_UpdateHardwareInfo
	.type	VDMHAL_V4R3C1_UpdateHardwareInfo, %function
VDMHAL_V4R3C1_UpdateHardwareInfo:
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
	bgt	.L414
	ldr	r2, .L462
	ldr	r3, [r2]
	cmp	r3, #1
	addne	r1, r2, #124
	bne	.L418
	b	.L415
.L458:
	cmp	r2, r1
	beq	.L457
.L418:
	ldr	r3, [r2, #4]!
	cmp	r3, #1
	bne	.L458
.L415:
	movw	r3, #1228
	ldr	r7, .L462+4
	mul	r3, r3, r4
	ldr	r3, [r7, r3]
	cmp	r3, #0
	beq	.L459
	mov	r2, #180
	ldr	r0, [r3, #12]
	mul	r2, r2, r4
	ldr	r6, .L462+8
	mov	r5, #1
	add	r1, r6, r2
	str	r0, [r6, r2]
	ldr	r8, [r3, #28]
	str	r8, [r1, #4]
.L421:
	movw	r3, #1228
	ubfx	r8, r8, #0, #17
	mla	r3, r3, r4, r7
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L460
	movw	r1, #1228
	sub	r3, r8, #1
	mul	r1, r1, r4
	cmp	r3, #199
	subls	r3, r8, #-1073741823
	mov	r2, #180
	mla	r2, r2, r4, r6
	movls	r3, r3, asl #4
	movhi	r3, #0
	addls	r0, r3, #8
	ldr	lr, [ip, r3]
	movhi	r0, #8
	ldr	r3, [r7, r1]
	str	lr, [r2, #16]
	ldr	lr, [r3, #208]
	ldr	r0, [ip, r0]
	ldr	r1, [r3, #212]
	str	lr, [r2, #8]
	str	r0, [r2, #20]
	str	r1, [r2, #12]
	b	.L425
.L457:
	movw	r3, #1228
	ldr	r7, .L462+4
	mul	r3, r3, r4
	ldr	r3, [r7, r3]
	cmp	r3, #0
	beq	.L461
	mov	r2, #180
	ldr	r0, [r3, #12]
	mul	r2, r2, r4
	ldr	r6, .L462+8
	mov	r5, #0
	add	r1, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [r3, #28]
	str	r2, [r1, #4]
.L422:
	mov	r2, #180
	add	r1, r3, #4096
	mla	r2, r2, r4, r6
	ldr	lr, [r1]
	ldr	ip, [r1, #20]
	cmp	r5, #0
	ldr	r0, [r3, #208]
	ldr	r1, [r3, #212]
	str	lr, [r2, #16]
	str	ip, [r2, #20]
	str	r0, [r2, #8]
	str	r1, [r2, #12]
	bne	.L425
	ldr	r7, [r3, #176]
	ldr	lr, [r3, #180]
	ldr	ip, [r3, #184]
	ldr	r0, [r3, #188]
	ldr	r1, [r3, #192]
	str	r7, [r2, #24]
	str	lr, [r2, #28]
	str	ip, [r2, #32]
	str	r0, [r2, #36]
	str	r1, [r2, #40]
.L425:
	mov	lr, #180
	add	r1, r3, #33024
	mul	lr, lr, r4
	add	r2, lr, #48
	add	lr, lr, #176
	add	r2, r6, r2
	add	lr, r6, lr
.L426:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, lr
	bne	.L426
	cmp	r5, #0
	movne	r0, #0
	bne	.L447
	mov	r2, #180
	add	r3, r3, #32768
	mla	r4, r2, r4, r6
	ldr	r2, [r3, #384]
	ldr	r3, [r3, #388]
	mov	r0, r5
	str	r2, [r4, #48]
	str	r3, [r4, #44]
.L447:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L414:
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L462+12
	ldr	r1, .L462+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L447
.L459:
	mov	r5, #1
.L429:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L420
	movw	r1, #1228
	mov	r2, #180
	mul	r1, r1, r4
	ldr	r6, .L462+8
	mul	r2, r2, r4
	cmp	r5, #1
	str	r3, [r7, r1]
	add	r1, r6, r2
	ldr	r0, [r3, #12]
	str	r0, [r6, r2]
	ldr	r8, [r3, #28]
	str	r8, [r1, #4]
	bne	.L422
	b	.L421
.L461:
	mov	r5, r3
	b	.L429
.L460:
	ldr	r3, .L462+20
	ldr	r2, .L462+12
	ldr	r1, .L462+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L447
.L420:
	ldr	r1, .L462+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L447
.L463:
	.align	2
.L462:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_BackUp
	.word	.LANCHOR0+648
	.word	.LC28
	.word	.LC44
	.word	.LC1
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_UpdateHardwareInfo, .-VDMHAL_V4R3C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V4R3C1_ReadMsgSlot
	.type	VDMHAL_V4R3C1_ReadMsgSlot, %function
VDMHAL_V4R3C1_ReadMsgSlot:
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
	beq	.L468
	cmp	r2, #800
	bhi	.L469
	ldr	r3, .L470
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L469:
	mov	r0, r4
	ldr	r1, .L470+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L468:
	mov	r2, r0
	ldr	r1, .L470+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L471:
	.align	2
.L470:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ReadMsgSlot, .-VDMHAL_V4R3C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V4R3C1_WriteMsgSlot
	.type	VDMHAL_V4R3C1_WriteMsgSlot, %function
VDMHAL_V4R3C1_WriteMsgSlot:
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
	beq	.L473
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L473
	ldr	r3, .L476
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L473:
	ldr	r1, .L476+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L477:
	.align	2
.L476:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteMsgSlot, .-VDMHAL_V4R3C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V4R3C1_CfgRpMsg
	.type	VDMHAL_V4R3C1_CfgRpMsg, %function
VDMHAL_V4R3C1_CfgRpMsg:
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
	str	r3, [fp, #-68]
	beq	.L515
	ldr	r2, [r7, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L516
	ldr	r1, [r7, #28]
	ldr	r0, [r7, #64]
	ldrb	ip, [r7]	@ zero_extendqisi2
	mov	r1, r1, asl r0
	ldr	r3, [r7, #32]
	add	r2, r1, #255
	cmp	ip, #1
	bic	r2, r2, #255
	mov	r3, r3, asl r0
	movne	r1, #0
	mov	lr, r2, asl #4
	beq	.L517
.L482:
	ldr	r0, [r7, #4]
	cmp	r0, #16
	beq	.L483
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r2, r1
.L504:
	ldr	r2, [r7, #20]
	ldr	r4, [fp, #-68]
	mov	ip, #0	@ movhi
	mov	r0, ip	@ movhi
	str	r2, [r4]
	ldr	r2, [r7, #20]
	add	r2, r3, r2
	str	r2, [r4, #4]
	ldr	r2, [r7, #8]
	str	r2, [r4, #8]
	ldr	r2, [r7, #8]
	add	r3, r3, r2
	str	r3, [r4, #12]
	str	lr, [r4, #16]
	str	r1, [r4, #20]
	ldr	r2, [r7, #28]
	ldr	r3, [r7, #32]
	sub	r2, r2, #1
	sub	r3, r3, #1
	bfi	ip, r2, #0, #9
	bfi	r0, r3, #0, #9
	strh	ip, [fp, #-52]	@ movhi
	strh	r0, [fp, #-50]	@ movhi
	ldr	r3, [fp, #-52]
	str	r3, [r4, #24]
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
	strne	r3, [fp, #-60]
	beq	.L518
.L486:
	cmp	r1, #1
	beq	.L502
	ldr	r3, [fp, #-60]
	sub	r3, r3, #1
	uxth	r3, r3
.L503:
	ldrb	r1, [r7]	@ zero_extendqisi2
	mov	r0, #0
	ldrb	r2, [fp, #-50]	@ zero_extendqisi2
	ldr	ip, [r7, #52]
	ldr	lr, [r7, #64]
	bfi	r2, r1, #0, #1
	ldrb	r1, [fp, #-49]	@ zero_extendqisi2
	and	ip, ip, #3
	sub	lr, lr, #4
	bfi	r2, ip, #4, #2
	bfi	r1, lr, #0, #2
	strh	r3, [fp, #-52]	@ movhi
	mov	r3, r2
	bfi	r3, ip, #6, #2
	mov	r2, r1
	ldr	r1, [fp, #-80]
	strb	r3, [fp, #-50]
	bfi	r2, r1, #2, #4
	strb	r2, [fp, #-49]
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-68]
	str	r3, [r2, #28]
.L513:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L518:
	ldr	r3, [r7, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L487
	cmp	r3, #5
	moveq	r4, #4
	beq	.L487
	cmp	r3, #4
	moveq	r4, #8
	bne	.L519
.L487:
	ldr	r8, [r7, #44]
	cmp	r8, #0
	movle	r3, #0
	ldrle	r1, [r7, #56]
	strle	r3, [fp, #-60]
	ble	.L486
	ldr	r2, [fp, #-84]
	mov	r6, #0
	ldr	r3, [fp, #-76]
	str	r6, [fp, #-72]
	str	r6, [fp, #-60]
	mul	r3, r3, r2
	str	r7, [fp, #-56]
	sub	r2, r4, #1
	str	r2, [fp, #-88]
	str	r3, [fp, #-92]
	sub	r3, r3, #1
	str	r3, [fp, #-96]
	b	.L490
.L522:
	ldrsh	r0, [r5, #70]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r10, r3
	str	r3, [fp, #-72]
	ldrgt	r10, [fp, #-88]
	bgt	.L493
.L492:
	ldr	r3, [fp, #-56]
	add	r6, r6, #1
	ldr	r8, [r3, #44]
	cmp	r6, r8
	bge	.L520
	cmp	r6, #199
	bgt	.L521
.L490:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r5, r3, r6, lsl #2
	ldrsh	r7, [r5, #74]
	ldrh	r3, [r5, #72]
	sub	r0, r7, #1
	add	r0, r0, r4
	str	r3, [fp, #-64]
	bl	__aeabi_uidiv
	cmp	r6, #0
	mul	r10, r4, r0
	bgt	.L522
	ldr	r2, [fp, #-72]
	cmp	r10, r2
	movgt	r2, #0
	movle	r2, #1
	cmp	r6, #0
	moveq	r2, #0
	cmp	r2, #0
	bne	.L492
.L495:
	ldrsh	r0, [fp, #-64]
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-92]
	ldr	r5, [fp, #-96]
	cmp	r3, r10
	ldr	r3, [fp, #-60]
	movhi	r5, r10
	add	r3, r3, #1
	str	r3, [fp, #-60]
	mul	r8, r4, r0
	cmp	r8, r5
	movgt	r8, #0
	cmp	r3, #252
	bgt	.L523
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
	ldr	r2, [fp, #-60]
	ldr	r9, [fp, #-68]
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
	b	.L492
.L496:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r7, r4, r0
	ldrsh	r0, [r5, #76]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	add	r2, r0, #1
	bhi	.L497
	cmp	r7, r2
	mov	r1, r4
	beq	.L497
	ldrsh	r0, [r5, #70]
	add	r0, r0, r10
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	bhi	.L524
.L497:
	cmp	r9, #198
	mov	r6, r9
	add	r5, r5, #4
	bgt	.L525
	ldrsh	r7, [r5, #74]
.L493:
	add	r9, r6, #1
	mov	r1, r4
	cmp	r9, r8
	add	r0, r10, r7
	blt	.L496
	ldr	r3, [fp, #-88]
	add	r0, r3, r7
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L495
.L525:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r3, r3, r9, lsl #2
	ldrsh	r0, [r3, #74]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L495
.L483:
	mla	r3, r2, r3, r1
	mov	r2, #10
	str	r2, [fp, #-80]
	b	.L504
.L517:
	add	r0, r1, #508
	adds	ip, r3, #63
	add	r0, r0, #3
	addmi	ip, r3, #126
	add	r1, r1, #1020
	cmp	r0, #0
	add	r1, r1, #2
	movge	r1, r0
	mov	r0, ip, asr #6
	mov	r1, r1, asr #9
	mov	r0, r0, asl #5
	mov	r1, r1, asl #4
	mul	r1, r1, r0
	b	.L482
.L523:
	ldr	r7, [fp, #-56]
	mov	r1, #1
	str	r1, [r7, #56]
.L502:
	ldr	r3, [fp, #-76]
	mov	lr, #0	@ movhi
	mov	ip, lr	@ movhi
	str	r1, [r7, #44]
	sub	r2, r3, #1
	ldr	r3, [fp, #-84]
	ldr	r1, [fp, #-68]
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
	b	.L503
.L524:
	mov	r10, r7
	b	.L495
.L520:
	mov	r7, r3
	ldr	r1, [r3, #56]
	b	.L486
.L521:
	ldr	r7, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L526
	movw	r3, #2158
	str	r6, [sp]
	ldr	r2, .L526+4
	str	r0, [fp, #-60]
	bl	dprint_vfmw
	ldr	r1, [r7, #56]
	b	.L486
.L519:
	ldr	r1, .L526+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L487
.L516:
	ldr	r1, .L526+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L513
.L515:
	ldr	r3, .L526+16
	ldr	r2, .L526+20
	ldr	r1, .L526+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L513
.L527:
	.align	2
.L526:
	.word	.LC51
	.word	.LANCHOR0+708
	.word	.LC50
	.word	.LC49
	.word	.LC48
	.word	.LANCHOR0+684
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CfgRpMsg, .-VDMHAL_V4R3C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V4R3C1_CfgRpReg
	.type	VDMHAL_V4R3C1_CfgRpReg, %function
VDMHAL_V4R3C1_CfgRpReg:
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
	bgt	.L562
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L563
.L531:
	ldr	r4, .L565
	ldr	r3, [r1, #48]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L564
	movw	r1, #1228
	ldr	r2, .L565+4
	mul	r1, r1, r6
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L534:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r6
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L536:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L538:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L540:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L542:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L544:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L546:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L548:
	movw	r3, #1228
	movw	r1, #3075
	mul	r6, r3, r6
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r6]
	str	r1, [r3, #84]
.L551:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L564:
	mov	r2, #16
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L565+4
	beq	.L534
	mov	r2, #12
	mov	r1, #2
	ldr	r0, [fp, #4]
	movw	r5, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r5, 48
	str	r5, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L536
	mov	r3, r5
	mov	r2, #60
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L538
	mov	r3, r5
	mov	r2, #64
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L540
	mov	r3, r5
	mov	r2, #68
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L542
	mov	r3, r5
	mov	r2, #72
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L544
	mov	r3, r5
	mov	r2, #76
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L546
	mov	r3, r5
	mov	r2, #80
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L565+4
	beq	.L548
	ldr	r0, [fp, #4]
	mov	r3, r5
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L563:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L532
	ldr	r1, [fp, #-40]
	str	r3, [r1]
	b	.L531
.L562:
	str	r0, [sp]
	ldr	r2, .L565+8
	ldr	r1, .L565+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L551
.L532:
	ldr	r1, .L565+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L551
.L566:
	.align	2
.L565:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0+732
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CfgRpReg, .-VDMHAL_V4R3C1_CfgRpReg
	.align	2
	.global	VDMHAL_V4R3C1_MakeDecReport
	.type	VDMHAL_V4R3C1_MakeDecReport, %function
VDMHAL_V4R3C1_MakeDecReport:
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
	beq	.L596
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L597
	movw	r3, #1228
	ldr	r7, .L605
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L571
	ldr	r3, .L605+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L574
	b	.L586
.L599:
	cmp	r3, r1
	beq	.L598
.L574:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L599
.L586:
	mov	r4, r2
.L572:
	ldr	r3, .L605+8
	mov	r2, #820
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L605+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L575
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L575:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L600
.L576:
	cmp	r2, #200
	bhi	.L601
.L578:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r7, [r7, #40]
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L602
	ldr	r8, .L605+16
	mov	r3, #3200
	ldr	r2, [r5, #12]
	mla	r4, r3, r6, r8
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V4R3C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	cmp	ip, #0
	movne	r3, r4
	movne	r2, r5
	movne	r1, #0
	beq	.L583
.L582:
	ldr	r0, [r3, #4]
	add	r1, r1, #1
	cmp	r1, ip
	add	r3, r3, #16
	add	r2, r2, #4
	strh	r0, [r2, #12]	@ movhi
	ldr	r0, [r3, #-8]
	strh	r0, [r2, #14]	@ movhi
	bne	.L582
.L583:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L603
.L569:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L600:
	cmp	r4, #1
	beq	.L604
	ldr	r1, .L605+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L576
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L576
	mov	r3, #1
	strh	r1, [r5, #16]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #18]	@ movhi
	str	r3, [r5, #12]
	b	.L569
.L598:
	mov	r4, #0
	b	.L572
.L603:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L605+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L605+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L584:
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
	ldr	r1, .L605+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L584
	ldr	r1, .L605+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L601:
	mov	r3, #200
	ldr	r1, .L605+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L578
.L604:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L576
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #16]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #18]	@ movhi
	b	.L569
.L602:
	ldr	r3, .L605+44
	ldr	r2, .L605+48
	ldr	r1, .L605+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L569
.L571:
	ldr	r3, .L605+56
	ldr	r2, .L605+48
	ldr	r1, .L605+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L569
.L597:
	mov	r0, r5
	ldr	r3, .L605+60
	ldr	r2, .L605+48
	ldr	r1, .L605+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L569
.L596:
	ldr	r3, .L605+64
	ldr	r2, .L605+48
	ldr	r1, .L605+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L569
.L606:
	.align	2
.L605:
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
	.size	VDMHAL_V4R3C1_MakeDecReport, .-VDMHAL_V4R3C1_MakeDecReport
	.align	2
	.global	VDMHAL_V4R3C1_PrepareRepair
	.type	VDMHAL_V4R3C1_PrepareRepair, %function
VDMHAL_V4R3C1_PrepareRepair:
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
	ldr	r5, .L622
	cmp	r3, #0
	mov	r6, r3
	mov	r7, r0
	add	r8, r4, r5
	bgt	.L618
	ldr	r3, [r4, r5]
	cmp	r3, #0
	beq	.L619
.L610:
	cmp	r2, #0
	beq	.L620
	cmp	r2, #1
	movne	r0, #0
	beq	.L621
.L609:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L620:
	ldr	r4, .L622+4
	mov	r3, #1744
	mla	r3, r3, r6, r4
	ldr	r0, [r3, #44]
	cmp	r0, #0
	ble	.L613
	cmp	r7, #6
	bne	.L614
	ldrb	r0, [r1, #17]	@ zero_extendqisi2
	cmp	r0, #1
	moveq	r2, r0
	str	r2, [r3, #924]
.L614:
	ldr	r3, [fp, #4]
	mov	r2, r1
	mov	r0, r7
	mov	r1, r8
	str	r3, [sp]
	mov	r3, r6
	bl	VDMHAL_V4R3C1_CfgRpReg
	mov	r0, #1744
	mov	r1, r8
	mov	r2, r6
	mla	r0, r0, r6, r4
	bl	VDMHAL_V4R3C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L621:
	cmp	r7, #6
	bne	.L616
	ldrb	r3, [r1, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L616
	mov	r4, #1744
	ldr	r5, .L622+4
	mul	r4, r4, r6
	add	ip, r5, r4
	ldr	r3, [ip, #916]
	cmp	r3, #0
	ble	.L616
	ldr	r3, [fp, #4]
	mov	lr, #2
	mov	r2, r1
	mov	r0, r7
	mov	r1, r8
	str	r3, [sp]
	mov	r3, r6
	str	lr, [ip, #924]
	bl	VDMHAL_V4R3C1_CfgRpReg
	add	r0, r4, #872
	mov	r2, r6
	add	r0, r5, r0
	mov	r1, r8
	bl	VDMHAL_V4R3C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L619:
	mov	r0, #0
	str	r2, [fp, #-44]
	movt	r0, 63683
	str	r1, [fp, #-40]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L611
	str	r3, [r4, r5]
	ldr	r1, [fp, #-40]
	ldr	r2, [fp, #-44]
	b	.L610
.L618:
	mov	r0, #0
	ldr	r2, .L622+8
	str	r0, [sp]
	ldr	r1, .L622+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L616:
	ldr	r1, .L622+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L609
.L613:
	mov	r0, r2
	ldr	r1, .L622+20
	str	r2, [fp, #-40]
	bl	dprint_vfmw
	ldr	r2, [fp, #-40]
	mov	r0, r2
	b	.L609
.L611:
	ldr	r1, .L622+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L623:
	.align	2
.L622:
	.word	g_HwMem
	.word	g_RepairParam
	.word	.LANCHOR0+784
	.word	.LC28
	.word	.LC61
	.word	.LC60
	.word	.LC59
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_PrepareRepair, .-VDMHAL_V4R3C1_PrepareRepair
	.align	2
	.global	VDMHAL_V4R3C1_StartHwRepair
	.type	VDMHAL_V4R3C1_StartHwRepair, %function
VDMHAL_V4R3C1_StartHwRepair:
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
	ldr	r6, .L654
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L648
	cmp	r0, #0
	ble	.L649
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L654+4
	mov	r0, #32
	ldr	r1, .L654+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L650
.L632:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L654+4
	ldr	r1, .L654+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L644
.L627:
	cmp	r4, #0
	beq	.L651
	mov	r3, r5, asl #6
	ldr	r2, .L654+12
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
.L649:
	movw	r3, #1228
	ldr	r4, .L654+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L630:
	movw	r3, #1228
	ldr	r2, .L654+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L639:
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
.L624:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L648:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L652
	cmp	r5, #0
	ldrle	r4, .L654+16
	bgt	.L632
	b	.L630
.L652:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L627
	ldr	r3, .L654+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L653
.L636:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L654+24
	ldr	r1, .L654+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L654+24
	ldr	r1, .L654+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L654+24
	ldr	r1, .L654+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L624
.L650:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L627
.L644:
	ldr	r3, .L654+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L636
.L651:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L654+24
	ldr	r1, .L654+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L653:
	ldr	r4, .L654+16
	b	.L639
.L655:
	.align	2
.L654:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_StartHwRepair, .-VDMHAL_V4R3C1_StartHwRepair
	.align	2
	.global	VDMHAL_V4R3C1_CalVdhClkSkip
	.type	VDMHAL_V4R3C1_CalVdhClkSkip, %function
VDMHAL_V4R3C1_CalVdhClkSkip:
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
	ldr	r9, .L686
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L678
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L658
.L685:
	mov	r3, r10
	ldr	r2, .L686+4
	ldr	r1, .L686+8
	mov	r0, #1
	bl	dprint_vfmw
.L660:
	cmp	r4, r9
	beq	.L684
.L677:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L684
.L658:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L685
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L661
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L661:
	ldr	r3, .L686+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1464]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L679
.L664:
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L679
	.word	.L673
	.word	.L673
	.word	.L679
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L673
	.word	.L679
	.word	.L674
	.word	.L673
	.word	.L673
.L673:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L677
.L684:
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
.L674:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L660
.L679:
	mov	r7, #0
	b	.L660
.L678:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L687:
	.align	2
.L686:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC63
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalVdhClkSkip, .-VDMHAL_V4R3C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V4R3C1_GetVdmClk
	.type	VDMHAL_V4R3C1_GetVdmClk, %function
VDMHAL_V4R3C1_GetVdmClk:
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
	ldr	r2, .L696
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L689
.L691:
	.word	.L689
	.word	.L692
	.word	.L693
	.word	.L694
.L689:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L693:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L692:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L694:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L697:
	.align	2
.L696:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GetVdmClk, .-VDMHAL_V4R3C1_GetVdmClk
	.align	2
	.global	VDMHAL_V4R3C1_StartHwDecode
	.type	VDMHAL_V4R3C1_StartHwDecode, %function
VDMHAL_V4R3C1_StartHwDecode:
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
	subs	r5, r0, #0
	mov	r4, r1
	ble	.L699
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L736
	ldr	r1, .L736+4
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L699:
	ldr	r6, .L736+8
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L733
	ldr	r2, .L736+12
	mov	r0, #500
	ldr	r8, .L736+16
	ldr	r1, [r2]
	ldr	r3, [r1, #120]
	tst	r3, #768
	bfcne	r3, #8, #2
	strne	r3, [r1, #120]
	mov	r3, r5, asl #6
	ldr	r1, .L736+20
	sub	r3, r3, r5, asl #3
	add	r3, r8, r3
	ldr	r7, [r3, #8]
	str	r0, [r3, #16]
	ldr	r3, [r1, r7, asl #2]
	ldr	r9, [r3, #1168]
.L703:
	ldr	r2, [r2]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L705:
	mov	r2, r5
	mov	r3, r4
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r10, .L736+8
	cmp	r2, #1
	bne	.L734
	movw	r2, #1228
	ldr	r3, .L736+24
	mul	r2, r2, r5
	ldr	r4, .L736+28
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r4, r2]
	moveq	r1, #7
	movne	r1, #0
	str	r3, [r2, #156]
.L707:
	movw	r2, #1228
	cmp	r9, #1
	mul	r2, r2, r5
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r4, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L709:
	movw	r2, #1228
	mul	r2, r2, r5
	ldr	r2, [r4, r2]
	str	r3, [r2, #36]
.L711:
	ldr	r6, .L736+32
	mov	r0, #30
	ldr	r3, [r6, #116]
	blx	r3
	ldr	r3, [r6, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r5
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r5, r1, r5, r8
	ldr	ip, .L736+36
	mov	r1, #4
	ldr	r0, [r4, r3]
	str	r2, [r0]
	ldr	r0, [r4, r3]
	str	lr, [r0]
	ldr	r3, [r4, r3]
	str	r2, [r3]
	ldr	r0, [r5, #8]
	ldr	r2, [ip, r0, asl #2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDEC_Lowdelay_Event_Time
.L734:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r4
	bl	VDH_Record_RegData
	ldr	r3, .L736+24
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #7
	movne	r1, #0
	cmp	r2, #1
	ldreq	r4, .L736+28
	beq	.L707
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r4
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r9, #1
	ldrb	r2, [r6]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r4, .L736+28
	beq	.L709
	mov	r0, r4
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r4, .L736+28
	beq	.L711
	cmp	r4, #0
	beq	.L735
	mov	r3, #1
	str	r7, [r4, #8]
	strb	r5, [r4]
	mov	r0, r4
	str	r3, [r4, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_PostTask
.L733:
	mov	r3, #0
	mov	r0, r1
	mov	r2, r3
	mov	r1, r3
	bl	VDH_Record_RegData
	ldr	r8, .L736+16
	mov	r3, r5, asl #6
	ldr	r2, .L736+20
	sub	r3, r3, r5, asl #3
	ldrb	r0, [r6]	@ zero_extendqisi2
	add	r3, r8, r3
	mov	r1, #500
	cmp	r0, #1
	ldr	r7, [r3, #8]
	str	r1, [r3, #16]
	ldr	r3, [r2, r7, asl #2]
	ldreq	r2, .L736+12
	ldr	r9, [r3, #1168]
	beq	.L703
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L705
.L735:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L736
	ldr	r1, .L736+40
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L737:
	.align	2
.L736:
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
	.size	VDMHAL_V4R3C1_StartHwDecode, .-VDMHAL_V4R3C1_StartHwDecode
	.align	2
	.global	VDMHAL_V4R3C1_GetCharacter
	.type	VDMHAL_V4R3C1_GetCharacter, %function
VDMHAL_V4R3C1_GetCharacter:
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
	ldr	r1, .L739
	mov	r0, #15
	ldr	r3, .L739+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L740:
	.align	2
.L739:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GetCharacter, .-VDMHAL_V4R3C1_GetCharacter
	.align	2
	.global	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.type	VDMHAL_V4R3C1_WriteBigTitle1DYuv, %function
VDMHAL_V4R3C1_WriteBigTitle1DYuv:
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
	beq	.L742
	cmp	r3, #2
	moveq	r4, #1
	movne	r4, #2
.L742:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L741
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L831
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L745
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L831+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L745
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
	bne	.L746
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L831+8
	mov	r3, r3, lsr #1
	ldr	r4, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r9, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r9, [fp, #-96]
	beq	.L748
.L747:
	cmp	r5, #0
	beq	.L750
	ldr	r2, [fp, #-96]
	mov	r7, #0
	and	r10, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L749:
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
	bhi	.L749
.L750:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L747
.L748:
	ldr	r3, [fp, #-100]
	mov	r0, r4
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	blx	ip
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L751
	ldr	r3, [fp, #-104]
	mov	r8, #0
	ldr	r9, [fp, #-116]
	str	r8, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L752:
	cmp	r5, #0
	beq	.L755
	ldr	r2, [fp, #-96]
	mov	r7, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L753:
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
	bhi	.L753
.L755:
	ldr	r3, [fp, #-96]
	add	r8, r8, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L752
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L829
.L757:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L758
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
.L758:
	ldr	r3, [fp, #-124]
.L828:
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
.L741:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L745:
	ldr	r1, .L831+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L746:
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
	ldr	r6, .L831+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L765
.L767:
	cmp	r5, #0
	beq	.L768
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L766:
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
	bhi	.L766
.L768:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L767
.L765:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	mov	r1, r1, lsr #1
	blx	ip
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L769
	ldr	r3, [fp, #-104]
	mov	r8, #0
	ldr	r9, [fp, #-116]
	str	r8, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L770:
	cmp	r5, #0
	beq	.L773
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L771:
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
	bhi	.L771
.L773:
	ldr	r3, [fp, #-96]
	add	r8, r8, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L770
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L830
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L776
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L781
.L782:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L782
.L781:
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
.L776:
	ldr	r3, [fp, #-132]
	b	.L828
.L829:
	ldr	r2, [fp, #-120]
	add	r4, r4, #1
	ldr	r7, [fp, #-124]
	mov	r3, #0
	ldr	r8, [fp, #-112]
.L759:
	cmp	r7, #0
	moveq	lr, r2
	beq	.L762
	sub	r0, r2, #-67108863
	add	lr, r2, r7
	sub	r0, r0, #65011712
	mov	r1, r4
.L760:
	ldrb	ip, [r1, #-1]	@ zero_extendqisi2
	strb	ip, [r0, #1]!
	ldrb	ip, [r1], #2	@ zero_extendqisi2
	strb	ip, [r2], #1
	cmp	r2, lr
	bne	.L760
.L762:
	add	r3, r3, #1
	mov	r2, lr
	cmp	r3, r8
	add	r4, r4, r5
	bne	.L759
	b	.L758
.L830:
	ldr	r3, [fp, #-124]
	ldr	r4, [fp, #-120]
	ldr	lr, [fp, #-132]
	mla	r2, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	mov	r3, #0
	add	r2, r2, #1
.L777:
	cmp	lr, #0
	beq	.L780
	mov	r1, r3, lsr #1
	mov	r0, r2
	mul	r1, lr, r1
	sub	ip, r1, #-67108863
	add	r9, r1, lr
	sub	ip, ip, #65011712
	add	r9, r4, r9
	add	ip, r4, ip
	add	r1, r4, r1
.L778:
	ldrb	r8, [r0, #-1]	@ zero_extendqisi2
	strb	r8, [ip, #1]!
	ldrb	r8, [r0], #2	@ zero_extendqisi2
	strb	r8, [r1], #1
	cmp	r1, r9
	bne	.L778
.L780:
	add	r3, r3, #2
	add	r2, r2, r5
	cmp	r7, r3
	bhi	.L777
	b	.L776
.L751:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L757
	b	.L758
.L769:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L776
	cmp	r3, #0
	beq	.L781
	b	.L776
.L832:
	.align	2
.L831:
	.word	.LC64
	.word	.LC66
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteBigTitle1DYuv, .-VDMHAL_V4R3C1_WriteBigTitle1DYuv
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
	ldr	ip, .L840
	mov	lr, r2
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L839
	cmp	r0, #0
	bne	.L835
	ldr	r3, .L840+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L835:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L840+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L839:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L841:
	.align	2
.L840:
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
	ldr	ip, .L848
	mov	lr, r3
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L846
	cmp	r2, #0
	ble	.L847
	mov	r3, r2
	str	ip, [sp]
	ldr	r2, .L848+4
	mov	r0, #32
	ldr	r1, .L848+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L847:
	movw	r3, #1228
	ldr	ip, .L848+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L846:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L849:
	.align	2
.L848:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.56846, %object
	.size	__func__.56846, 22
__func__.56846:
	.ascii	"VDMHAL_V4R3C1_OpenHAL\000"
	.space	2
	.type	__func__.56920, %object
	.size	__func__.56920, 25
__func__.56920:
	.ascii	"VDMHAL_V4R3C1_CalcFsSize\000"
	.space	3
	.type	__func__.56946, %object
	.size	__func__.56946, 24
__func__.56946:
	.ascii	"VDMHAL_V4R3C1_CalcFsNum\000"
	.type	__func__.56988, %object
	.size	__func__.56988, 32
__func__.56988:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.56989, %object
	.size	__FUNCTION__.56989, 32
__FUNCTION__.56989:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Normal\000"
	.type	__func__.56932, %object
	.size	__func__.56932, 33
__func__.56932:
	.ascii	"VDMHAL_V4R3C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.57069, %object
	.size	__func__.57069, 34
__func__.57069:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.57092, %object
	.size	__func__.57092, 23
__func__.57092:
	.ascii	"VDMHAL_V4R3C1_ResetVdm\000"
	.space	1
	.type	__func__.57102, %object
	.size	__func__.57102, 35
__func__.57102:
	.ascii	"VDMHAL_V4R3C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.57123, %object
	.size	__func__.57123, 24
__func__.57123:
	.ascii	"VDMHAL_V4R3C1_GlbResetX\000"
	.type	__func__.57112, %object
	.size	__func__.57112, 23
__func__.57112:
	.ascii	"VDMHAL_V4R3C1_GlbReset\000"
	.space	1
	.type	__func__.57135, %object
	.size	__func__.57135, 28
__func__.57135:
	.ascii	"VDMHAL_V4R3C1_ClearIntState\000"
	.type	__func__.57141, %object
	.size	__func__.57141, 31
__func__.57141:
	.ascii	"VDMHAL_V4R3C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.57147, %object
	.size	__func__.57147, 22
__func__.57147:
	.ascii	"VDMHAL_V4R3C1_MaskInt\000"
	.space	2
	.type	__func__.57160, %object
	.size	__func__.57160, 24
__func__.57160:
	.ascii	"VDMHAL_V4R3C1_EnableInt\000"
	.type	__func__.57169, %object
	.size	__func__.57169, 23
__func__.57169:
	.ascii	"VDMHAL_V4R3C1_CheckReg\000"
	.space	1
	.type	__func__.57183, %object
	.size	__func__.57183, 26
__func__.57183:
	.ascii	"VDMHAL_V4R3C1_ReadMMUMask\000"
	.space	2
	.type	__func__.57188, %object
	.size	__func__.57188, 27
__func__.57188:
	.ascii	"VDMHAL_V4R3C1_WriteMMUMask\000"
	.space	1
	.type	__func__.57219, %object
	.size	__func__.57219, 25
__func__.57219:
	.ascii	"VDMHAL_V4R3C1_PrepareDec\000"
	.space	3
	.type	__func__.57224, %object
	.size	__func__.57224, 25
__func__.57224:
	.ascii	"VDMHAL_V4R3C1_IsVdmReady\000"
	.space	3
	.type	__func__.57229, %object
	.size	__func__.57229, 23
__func__.57229:
	.ascii	"VDMHAL_V4R3C1_IsVdmRun\000"
	.space	1
	.type	__func__.57235, %object
	.size	__func__.57235, 27
__func__.57235:
	.ascii	"VDMHAL_V4R3C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.57245, %object
	.size	__func__.57245, 31
__func__.57245:
	.ascii	"VDMHAL_V4R3C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.57260, %object
	.size	__func__.57260, 33
__func__.57260:
	.ascii	"VDMHAL_V4R3C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.57333, %object
	.size	__func__.57333, 23
__func__.57333:
	.ascii	"VDMHAL_V4R3C1_CfgRpMsg\000"
	.space	1
	.type	__func__.57310, %object
	.size	__func__.57310, 24
__func__.57310:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.57344, %object
	.size	__func__.57344, 23
__func__.57344:
	.ascii	"VDMHAL_V4R3C1_CfgRpReg\000"
	.space	1
	.type	__func__.57357, %object
	.size	__func__.57357, 28
__func__.57357:
	.ascii	"VDMHAL_V4R3C1_MakeDecReport\000"
	.type	__func__.57396, %object
	.size	__func__.57396, 28
__func__.57396:
	.ascii	"VDMHAL_V4R3C1_PrepareRepair\000"
	.type	__func__.57583, %object
	.size	__func__.57583, 15
__func__.57583:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.57403, %object
	.size	__func__.57403, 28
__func__.57403:
	.ascii	"VDMHAL_V4R3C1_StartHwRepair\000"
	.type	__func__.57442, %object
	.size	__func__.57442, 28
__func__.57442:
	.ascii	"VDMHAL_V4R3C1_CalVdhClkSkip\000"
	.type	__func__.57465, %object
	.size	__func__.57465, 28
__func__.57465:
	.ascii	"VDMHAL_V4R3C1_StartHwDecode\000"
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
	ASCII(.ascii	"VDMHAL_V4R3C1_OpenHAL: Size error!\000" )
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
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC 10 bit\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC11:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V4R3C1_ArrangeMe" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_CalcFsSize err!\012\000" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_ArrangeMem Mem addr is NULL\000" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_ResetVdm: map vdm register fail, vir(" )
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
	ASCII(.ascii	"%s VdhId %d failed!\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"%s VdhId %d success!\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC37:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC38:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC39:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC40:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
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
