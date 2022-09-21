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
	.type	VDMHAL_UpdateParam, %function
VDMHAL_UpdateParam:
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
	ldr	r3, [r2, #28]
	ldr	ip, [r2, #64]
	mov	r3, r3, asl ip
	cmp	r3, #1920
	ldmgtfd	sp, {fp, sp, pc}
	ldr	r3, [r2, #4]
	cmp	r3, #17
	ldmeqfd	sp, {fp, sp, pc}
	mov	ip, #0
	mov	r3, #1
	strb	ip, [r2]
	strb	r3, [r2, #1]
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L12
.L15:
	.word	.L25
	.word	.L16
	.word	.L17
	.word	.L18
	.word	.L12
	.word	.L19
	.word	.L20
	.word	.L12
	.word	.L21
	.word	.L22
	.word	.L23
	.word	.L23
	.word	.L23
	.word	.L24
	.word	.L12
	.word	.L25
	.word	.L26
	.word	.L27
.L25:
	mov	r2, #0
	mov	r3, #1
	strb	r2, [r1, #4]
	strb	r3, [r1, #17]
.L12:
	ldmfd	sp, {fp, sp, pc}
.L24:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #3144]
	strb	r3, [r1, #2778]
	ldmfd	sp, {fp, sp, pc}
.L26:
	mov	r2, #0
	mov	r3, #1
	strb	r2, [r1]
	strb	r3, [r1, #5]
	ldmfd	sp, {fp, sp, pc}
.L27:
	add	r1, r1, #270336
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #2468]
	strb	r3, [r1, #2081]
	ldmfd	sp, {fp, sp, pc}
.L16:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #260]
	strb	r3, [r1, #71]
	ldmfd	sp, {fp, sp, pc}
.L17:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #2372]
	strb	r3, [r1, #159]
	ldmfd	sp, {fp, sp, pc}
.L18:
	add	r2, r1, #45056
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #240]
	strb	r3, [r1, #144]
	ldmfd	sp, {fp, sp, pc}
.L19:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #160]
	strb	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L20:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #2604]
	strb	r3, [r1, #48]
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #76]
	strb	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L22:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #72]
	strb	r3, [r1, #1]
	ldmfd	sp, {fp, sp, pc}
.L23:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #212]
	strb	r3, [r1, #52]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_UpdateParam, .-VDMHAL_UpdateParam
	.align	2
	.global	VDMHAL_V5R2C1_GetHalMemSize
	.type	VDMHAL_V5R2C1_GetHalMemSize, %function
VDMHAL_V5R2C1_GetHalMemSize:
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
	.size	VDMHAL_V5R2C1_GetHalMemSize, .-VDMHAL_V5R2C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V5R2C1_OpenHAL
	.type	VDMHAL_V5R2C1_OpenHAL, %function
VDMHAL_V5R2C1_OpenHAL:
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
	beq	.L42
	ldmia	r3, {r6, r7}
	ldr	r8, [r3, #8]
	cmp	r6, #0
	beq	.L43
	cmp	r7, #6291456
	blt	.L44
	cmp	r8, #0
	bgt	.L45
	ldr	r4, .L46
	mov	r2, #268
	ldr	r10, .L46+4
	mov	r1, #0
	ldr	r5, .L46+8
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
	ldr	r1, .L46+12
	mov	r3, r0
	mov	r2, r0
	str	r3, [r5, r9]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L46+16
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
.L38:
	str	r2, [r3, #4]!
	cmp	r3, r1
	add	r2, r2, #1280
	bne	.L38
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
	bcc	.L39
	mov	r0, r4
	bl	H264HAL_V5R2C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V5R2C1_InitHal
	cmp	r0, #0
	mvnne	r0, #0
	bne	.L34
	adds	r0, r5, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L34:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L45:
	ldr	r1, .L46+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L39:
	mov	r3, r7
	ldr	r2, [fp, #-48]
	ldr	r1, .L46+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L34
.L43:
	mov	r0, r6
	ldr	r3, .L46+28
	ldr	r2, .L46+32
	ldr	r1, .L46+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L34
.L44:
	ldr	r3, .L46+40
	mov	r0, #0
	ldr	r2, .L46+32
	ldr	r1, .L46+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L34
.L42:
	ldr	r3, .L46+44
	ldr	r2, .L46+32
	ldr	r1, .L46+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L34
.L47:
	.align	2
.L46:
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
	.size	VDMHAL_V5R2C1_OpenHAL, .-VDMHAL_V5R2C1_OpenHAL
	.align	2
	.global	VDMHAL_V5R2C1_CloseHAL
	.type	VDMHAL_V5R2C1_CloseHAL, %function
VDMHAL_V5R2C1_CloseHAL:
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
	.size	VDMHAL_V5R2C1_CloseHAL, .-VDMHAL_V5R2C1_CloseHAL
	.align	2
	.global	VDMHAL_V5R2C1_CalcFsSize
	.type	VDMHAL_V5R2C1_CalcFsSize, %function
VDMHAL_V5R2C1_CalcFsSize:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 32
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
	sub	lr, r1, #32
	mov	ip, r1
	movw	r1, #8160
	cmp	lr, r1
	mov	r8, r0
	mov	r9, r2
	str	r3, [fp, #-64]
	ldr	r6, [fp, #8]
	bhi	.L50
	sub	r3, r2, #32
	mov	r4, r2
	cmp	r3, r1
	bhi	.L50
	add	r7, r2, #15
	sub	r2, fp, #44
	add	r5, ip, #15
	sub	r1, fp, #52
	mov	r7, r7, asr #4
	ldr	r0, [fp, #4]
	str	r7, [r2, #-4]!
	mov	r5, r5, asr #4
	str	ip, [fp, #-56]
	str	r5, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r2, [fp, #4]
	ldr	ip, [fp, #-56]
	cmp	r2, #16
	mov	r3, r0
	beq	.L77
	ldr	r2, [fp, #4]
	ldr	r10, .L82
	cmp	r2, #17
	beq	.L78
	mov	r5, r5, asl #4
	mov	r2, #0
	add	r5, r5, #255
	mov	r1, r2
	add	r4, r9, #31
	str	r2, [fp, #-68]
	bic	r2, r5, #255
	str	r2, [fp, #-56]
	ldr	r2, [r10, r8, asl #2]
	bic	r4, r4, #31
	str	r1, [fp, #-72]
.L54:
	ldr	r1, [r2, #1136]
	cmp	r1, #1
	beq	.L79
.L76:
	mov	r5, #0
	str	r5, [fp, #-60]
	mov	r9, r5
.L57:
	ldr	r1, [fp, #-64]
	cmp	r1, #1
	beq	.L80
	ldr	r0, [fp, #-72]
	ldr	r1, [fp, #-68]
	ldr	ip, [fp, #-56]
	mul	r1, r1, r0
	add	r0, r9, r9, lsl #1
	mul	r4, r4, ip
	add	r1, r1, r1, lsl #1
	add	r7, r4, r4, lsl #1
	mov	r1, r1, lsr #1
	add	r1, r1, r7, lsr #1
	add	r7, r1, r0, lsr #1
.L59:
	add	ip, r2, #471040
	ldr	r1, [ip, #888]
	cmp	r1, #0
	beq	.L81
.L60:
	add	r0, r2, #475136
	ldr	r1, [fp, #4]
	str	r7, [r0, #360]
	cmp	r1, #17
	ldr	r0, [fp, #-60]
	add	r1, r3, r3, lsr #31
	str	r5, [ip, #3240]
	mov	r1, r1, asr #1
	str	r1, [ip, #3276]
	str	r0, [ip, #3236]
	beq	.L61
	ldr	r1, [ip, #896]
	ldr	r0, [fp, #4]
	ldr	lr, [fp, #-56]
	cmp	r1, #32
	sub	r0, r0, #16
	movge	r1, #32
	cmp	r0, #1
	mov	r5, lr, asl #4
	str	r1, [ip, #3280]
	str	r5, [ip, #3228]
	add	r1, r4, r9
	mov	r5, r5, lsr #1
	str	r1, [ip, #3260]
	str	r5, [ip, #3232]
	bls	.L62
.L63:
	ldr	r2, [r10, r8, asl #2]
	mov	r0, #1024
	add	r7, r7, #1056
	add	r1, r2, #475136
	add	ip, r3, r7
	str	r3, [r1, #364]
	str	r0, [r1, #372]
	ldrsb	r2, [r2, #44]
	cmp	r2, #1
	addeq	ip, ip, r0
	cmp	r6, #0
	beq	.L71
	str	r7, [r6, #4]
	mov	r1, #1024
	ldr	r2, [r10, r8, asl #2]
	mov	r0, #0
	add	r2, r2, #471040
	ldr	r2, [r2, #896]
	str	r3, [r6, #12]
	str	r2, [r6, #8]
	ldr	r3, [r10, r8, asl #2]
	add	r3, r3, #471040
	ldr	r3, [r3, #3280]
	str	ip, [r6]
	str	r1, [r6, #20]
	str	r3, [r6, #16]
	ldr	r3, [r10, r8, asl #2]
	add	r3, r3, #475136
	str	r7, [r3, #368]
.L75:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L81:
	ldr	ip, .L82+4
	movw	r0, #15512
	movt	r0, 7
	add	r0, r2, r0
	mov	r2, #1248
	str	r3, [fp, #-64]
	ldr	ip, [ip, #48]
	blx	ip
	ldr	r2, [r10, r8, asl #2]
	ldr	r3, [fp, #-64]
	add	ip, r2, #471040
	b	.L60
.L61:
	ldr	r1, [fp, #-56]
	mov	r0, #1
	str	r0, [ip, #3280]
	mov	r5, r1, asl #4
	add	r1, r4, r9
	str	r5, [ip, #3228]
	str	r1, [ip, #3260]
	mov	r5, r5, lsr r0
	str	r5, [ip, #3232]
.L62:
	ldr	r2, [r2, #1444]
	cmp	r2, #8
	ble	.L63
	str	r3, [fp, #-56]
	add	r9, r9, r9, lsl #1
	ldr	r3, [fp, #-72]
	add	r4, r4, r4, lsl #1
	ldr	r2, [fp, #-68]
	mov	r9, r9, lsr #1
	add	r4, r9, r4, lsr #1
	mov	r0, #31
	mov	r1, r3, asl #4
	str	r4, [ip, #3252]
	mul	r2, r3, r2
	str	r1, [ip, #3244]
	ldr	r1, .L82+8
	str	r2, [ip, #3256]
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	b	.L63
.L80:
	mov	r1, r7, asl #5
	add	r7, r1, r7, lsl #4
	ldr	r1, [fp, #-56]
	mul	r4, r4, r1
	mul	r7, r1, r7
	b	.L59
.L79:
	ldr	r1, [fp, #4]
	sub	r5, r1, #17
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	ip, #1920
	orrgt	r5, r5, #1
	cmp	r5, #0
	streq	r5, [fp, #-60]
	moveq	r9, r5
	beq	.L57
	add	r9, r9, #63
	b	.L66
.L77:
	ldr	r10, .L82
	add	r5, ip, #255
	bic	r2, r5, #255
	str	r2, [fp, #-56]
	ldr	r2, [r10, r8, asl #2]
	ldr	r1, [r2, #1444]
	cmp	r1, #8
	ble	.L67
	ldr	r0, [fp, #-56]
	add	r1, r9, #31
	bic	r1, r1, #31
	str	r1, [fp, #-68]
	mov	r0, r0, lsr #2
	str	r0, [fp, #-72]
	b	.L54
.L78:
	add	r5, ip, #255
	add	r9, r9, #63
	bic	r2, r5, #255
	str	r2, [fp, #-56]
	ldr	r2, [r10, r8, asl #2]
	bic	r4, r9, #63
	ldr	r1, [r2, #1444]
	cmp	r1, #8
	ble	.L68
	ldr	r1, [fp, #-56]
	str	r4, [fp, #-68]
	mov	r1, r1, lsr #2
	str	r1, [fp, #-72]
.L56:
	ldr	r1, [r2, #1136]
	cmp	r1, #1
	bne	.L76
.L66:
	add	r1, ip, #2032
	add	ip, ip, #4080
	add	r1, r1, #15
	add	ip, ip, #14
	cmp	r1, #0
	movge	ip, r1
	add	r1, r9, #63
	cmp	r9, #0
	mov	ip, ip, asr #11
	movlt	r9, r1
	mov	r1, ip, asl #9
	mov	r9, r9, asr #6
	mov	r0, ip, asl #4
	str	r0, [fp, #-60]
	mul	r9, r9, r1
	mov	r5, r9
	b	.L57
.L67:
	mov	r1, #0
	str	r1, [fp, #-68]
	str	r1, [fp, #-72]
	b	.L54
.L50:
	ldr	r3, .L82+12
	mov	r0, #0
	ldr	r2, .L82+16
	ldr	r1, .L82+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L71:
	mov	r0, r6
	b	.L75
.L68:
	mov	r1, #0
	str	r1, [fp, #-68]
	str	r1, [fp, #-72]
	b	.L56
.L83:
	.align	2
.L82:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC8
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalcFsSize, .-VDMHAL_V5R2C1_CalcFsSize
	.align	2
	.global	VDMHAL_V5R2C1_GetRpuSize
	.type	VDMHAL_V5R2C1_GetRpuSize, %function
VDMHAL_V5R2C1_GetRpuSize:
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
	.size	VDMHAL_V5R2C1_GetRpuSize, .-VDMHAL_V5R2C1_GetRpuSize
	.align	2
	.global	VDMHAL_V5R2C1_CalcFsNum
	.type	VDMHAL_V5R2C1_CalcFsNum, %function
VDMHAL_V5R2C1_CalcFsNum:
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
	beq	.L90
	cmp	r1, #17
	ldr	ip, .L92
	beq	.L91
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
.L89:
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
.L91:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #1
	add	r1, r1, #471040
	str	r0, [r1, #3280]
	b	.L89
.L90:
	ldr	r2, .L92+4
	mov	r0, #1
	ldr	r1, .L92+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L93:
	.align	2
.L92:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+52
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalcFsNum, .-VDMHAL_V5R2C1_CalcFsNum
	.align	2
	.global	VDMHAL_V5R2C1_DynamicAllocFrame
	.type	VDMHAL_V5R2C1_DynamicAllocFrame, %function
VDMHAL_V5R2C1_DynamicAllocFrame:
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
	ldr	r6, .L117
	mov	r8, r1
	mov	r4, r0
	mov	r7, r2
	mov	r5, r3
	ldr	r1, [r6, r0, asl #2]
	add	r1, r1, #471040
	add	r1, r1, #920
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	bne	.L115
.L95:
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #0
	mov	r1, #255
	add	r2, r2, #471040
	add	r2, r2, #920
.L96:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L96
	cmp	r8, #1920
	cmple	r7, #1088
	bgt	.L99
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L117
	ldr	r2, [r3, #36]
	cmp	r2, #24
	beq	.L99
	add	r3, r3, #475136
	ldr	r3, [r3, #996]
	cmp	r3, #0
	beq	.L116
.L99:
	ldr	r2, [r5, #8]
	ldr	r3, [r6, r4, asl #2]
.L98:
	ldr	r1, [r3, #1392]
	add	r3, r3, #471040
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #900]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L117
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
	ldr	r1, .L117+4
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L117+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L101
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
.L101:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L117+12
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
.L115:
	ldr	r1, .L117+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L95
.L116:
	ldr	r2, [r5, #8]
	add	r2, r2, #4
	str	r2, [r5, #8]
	ldr	r3, [r1, r4, asl #2]
	b	.L98
.L118:
	.align	2
.L117:
	.word	s_pstVfmwChan
	.word	.LC12
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_DynamicAllocFrame, .-VDMHAL_V5R2C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R2C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R2C1_DynamicAllocFrame_Only:
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
	ldr	ip, .L124
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
	ldr	r1, .L124+4
	str	lr, [ip, #900]
	ldr	ip, [r4, #8]
	ldr	lr, [r4, #16]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L124+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L119
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
.L119:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L125:
	.align	2
.L124:
	.word	s_pstVfmwChan
	.word	.LC13
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_DynamicAllocFrame_Only, .-VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem_Normal
	.type	VDMHAL_V5R2C1_ArrangeMem_Normal, %function
VDMHAL_V5R2C1_ArrangeMem_Normal:
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
	bhi	.L163
	ldr	r5, .L170
	ldr	r1, [r5, r4, asl #2]
	add	r2, r1, #471040
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #892]
	cmp	r3, #2
	str	r2, [fp, #-72]
	beq	.L164
	bics	r3, r6, #16
	moveq	r3, #1
	movne	r3, #0
	cmp	r6, #18
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L165
.L131:
	cmp	r6, #17
	beq	.L148
	ldr	r3, [r1, #1136]
.L132:
	ldr	ip, [r1, #1148]
	mov	r2, r3
	str	r3, [r1, #1136]
	mov	r0, #1
	ldr	r3, [r1, #1140]
	str	ip, [sp, #4]
	ldr	ip, [r1, #1144]
	ldr	r1, .L170+4
	str	ip, [sp]
	bl	dprint_vfmw
.L130:
	sub	r7, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r6
	mov	r0, r4
	mov	r3, r7
	bl	VDMHAL_V5R2C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r7, [sp, #4]
	mov	r2, r9
	str	r6, [sp]
	mov	r1, r8
	mov	r10, r0
	mov	r0, r4
	bl	VDMHAL_V5R2C1_CalcFsSize
	orrs	r3, r0, r10
	bne	.L166
	ldr	r1, [fp, #-72]
	ldr	ip, [r5, r4, asl #2]
	ldr	r6, [fp, #-68]
	add	r3, ip, #471040
	ldr	r2, .L170
	cmp	r1, r6
	ldr	r10, [r3, #896]
	ldr	r1, [r3, #912]
	bne	.L135
	cmp	r1, #1
	beq	.L135
	ldr	r0, [r3, #888]
	cmp	r0, #1
	beq	.L135
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L167
	add	r1, ip, #475136
	cmp	r10, #0
	movw	r0, #15512
	ldr	r1, [r1, #360]
	movt	r0, 7
	movne	r2, ip
	str	r1, [fp, #-72]
	add	r1, ip, r0
	str	r1, [fp, #-80]
	beq	.L168
.L140:
	add	r2, r2, #471040
	ldr	r2, [r2, #900]
	cmp	r2, #30
	bgt	.L169
.L141:
	str	r2, [r3, #3272]
	mov	r0, #8
	str	r3, [fp, #-76]
	ldr	r3, .L170+8
	str	ip, [fp, #-84]
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r1, [r5, r4, asl #2]
	ldr	r3, [fp, #-76]
	add	r10, r1, #475136
	ldr	ip, [fp, #-84]
	ldr	r2, [r10, #400]
	cmp	r2, #0
	beq	.L146
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
.L145:
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
	beq	.L143
	ldr	ip, [r3, #3292]
	add	r4, ip, #1
	mov	r2, ip, asl #4
	sub	r2, r2, ip, asl #2
	ldr	ip, [r1, #16]
	add	r2, r3, r2
	str	ip, [r2, #4072]
	str	r4, [r3, #3292]
.L143:
	ldr	r2, [r3, #3288]
	cmp	r2, r6
	bcs	.L144
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
.L144:
	ldr	r2, [r10, #400]
	add	r1, r1, #72
	cmp	lr, r2
	bcc	.L145
	ldr	r4, [fp, #-84]
.L146:
	ldr	r3, .L170+8
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	ldr	r2, .L170+8
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
.L135:
	str	r1, [sp, #4]
	mov	r3, r6
	ldr	r2, .L170+12
	mov	r0, #31
	ldr	r1, .L170+16
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
	bne	.L137
	bl	VDMHAL_V5R2C1_DynamicAllocFrame
.L138:
	ldr	ip, [r5, r4, asl #2]
	mov	r3, r10
	mov	r2, r6
	ldr	r1, .L170+20
	add	ip, ip, #471040
	mov	r0, #31
	ldr	ip, [ip, #912]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L170+8
	ldr	r4, [r5, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #475136
	blx	r3
	mov	r3, #2
	str	r0, [r4, #376]
.L128:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L165:
	cmp	r9, #2160
	cmplt	r8, #3840
	blt	.L131
.L148:
	mov	r3, #1
	b	.L132
.L137:
	bl	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	b	.L138
.L164:
	mvn	r3, #0
	str	r0, [r1, #1136]
	str	r0, [r1, #1140]
	str	r3, [r1, #1144]
	str	r3, [r1, #1148]
	b	.L130
.L168:
	ldr	r1, .L170+24
	mov	r0, #31
	str	r3, [fp, #-88]
	str	r2, [fp, #-84]
	str	ip, [fp, #-76]
	bl	dprint_vfmw
	ldr	r2, [fp, #-84]
	ldr	ip, [fp, #-76]
	ldr	r3, [fp, #-88]
	ldr	r2, [r2, r4, asl #2]
	b	.L140
.L169:
	ldr	r1, .L170+28
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
	b	.L141
.L163:
	ldr	r3, .L170+32
	ldr	r2, .L170+36
	ldr	r1, .L170+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L128
.L166:
	ldr	r1, .L170+44
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L128
.L167:
	ldr	r3, .L170+48
	mov	r0, r1
	ldr	r2, .L170+52
	ldr	r1, .L170+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L128
.L171:
	.align	2
.L170:
	.word	s_pstVfmwChan
	.word	.LC15
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+108
	.word	.LC17
	.word	.LC18
	.word	.LC20
	.word	.LC21
	.word	.LC14
	.word	.LANCHOR0+76
	.word	.LC1
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+140
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ArrangeMem_Normal, .-VDMHAL_V5R2C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem_Specific
	.type	VDMHAL_V5R2C1_ArrangeMem_Specific, %function
VDMHAL_V5R2C1_ArrangeMem_Specific:
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
	beq	.L237
	ldr	r2, [fp, #4]
	sub	r1, r2, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L175
	ldr	r1, [fp, #8]
	sub	r1, r1, #32
	cmp	r1, r2
	bhi	.L175
	cmp	r7, #0
	beq	.L238
	ldr	lr, .L246
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
	ldrge	r3, .L246+4
	bge	.L236
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
	beq	.L239
	cmp	r10, #17
	beq	.L240
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
	blt	.L213
	ldr	r3, .L246+8
	mov	r2, #0
	str	r2, [fp, #-60]
	str	r2, [fp, #-64]
.L208:
	ldr	r3, [r3, ip, asl #2]
	ldr	r3, [r3, #1136]
	cmp	r3, #1
	movne	r2, #0
	movne	r1, r2
	movne	r3, r2
	beq	.L241
.L183:
	ldr	r0, [fp, #20]
	str	r1, [r7, #12]
	cmp	r0, #1
	str	r2, [r7, #16]
	beq	.L242
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
.L185:
	ldr	r2, [fp, #24]
	cmp	r2, #0
	blt	.L186
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
	beq	.L243
	ldr	r2, [fp, #20]
	add	ip, ip, #15
	bic	ip, ip, #15
	add	r1, r0, #15
	cmp	r2, #1
	add	r2, ip, #255
	bic	r1, r1, #15
	bic	r2, r2, #255
	beq	.L244
	ldr	r0, .L246+8
	ldr	lr, [fp, #24]
	ldr	r0, [r0, lr, asl #2]
	ldr	r0, [r0, #1136]
	cmp	r0, #1
	beq	.L190
	adds	r0, r1, #63
	ldr	lr, [fp, #-76]
	addmi	r0, r1, #126
	mov	r0, r0, asr #6
.L191:
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
.L189:
	cmp	r5, lr
	ldrgt	r3, .L246+12
	bgt	.L236
	ldr	ip, [fp, #24]
.L186:
	ldr	r2, [fp, #-56]
	mul	r8, r8, r2
	sub	r2, r10, #16
	cmp	r2, #1
	add	r2, r8, r3
	str	r2, [r7, #36]
	bls	.L245
	ldr	r3, [fp, #16]
	cmp	r3, #0
	beq	.L195
	cmp	r10, #3
	cmpne	r10, #0
	strne	ip, [fp, #-56]
	beq	.L193
.L235:
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
	beq	.L194
.L199:
	add	r2, r2, #1
	str	r4, [r1, #464]
	cmp	r2, r3
	add	r4, r4, r5
	add	r1, r1, #12
	bne	.L199
	ldr	r2, [fp, #-68]
	mov	r1, #0
	mla	r5, r3, r5, r2
	add	r2, r0, r3
	add	r0, r7, #76
	str	r2, [r7, #60]
	add	r2, r5, r6
.L201:
	add	r1, r1, #1
	str	r2, [r0, #4]!
	cmp	r1, r3
	add	r2, r2, #32
	bne	.L201
	ldr	lr, [r7, #56]
	add	r5, r5, r3, lsl #5
	add	r6, r5, r6
	cmp	lr, #0
	beq	.L206
	ldr	r4, [r7, #64]
	mov	r0, r7
	mov	r1, r6
	mov	r2, #0
.L205:
	add	r2, r2, #1
	str	r1, [r0, #208]
	cmp	r2, lr
	add	r1, r1, r9
	add	r0, r0, #8
	bne	.L205
	add	r2, r4, lr
	str	r2, [r7, #64]
.L206:
	mla	r9, lr, r9, r5
	cmp	ip, #0
	str	r9, [r7]
	blt	.L204
	ldr	r2, .L246+8
	ldr	r2, [r2, ip, asl #2]
	cmp	r2, #0
	beq	.L204
	cmp	r3, #0
	add	r6, r9, r6
	beq	.L204
	mov	r1, r7
	mov	r2, #0
.L207:
	add	r2, r2, #1
	str	r6, [r1, #848]
	cmp	r2, r3
	add	r6, r6, #1024
	add	r1, r1, #12
	bne	.L207
.L204:
	mov	r0, #0
	add	r9, r9, r3, lsl #10
	str	r9, [r7]
.L233:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L245:
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
	bne	.L193
.L195:
	mov	r3, #0
	str	r3, [r7, #48]
.L194:
	ldr	r3, .L246+16
.L236:
	ldr	r2, .L246+20
	mov	r0, #0
	ldr	r1, .L246+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L193:
	str	ip, [fp, #-56]
	ldr	r3, [fp, #16]
	b	.L235
.L239:
	ldr	r3, [fp, #4]
	cmp	ip, #0
	add	r8, r3, #255
	bic	r8, r8, #255
	blt	.L180
	ldr	r3, .L246+8
	str	ip, [fp, #-56]
	ldr	r0, [r3, ip, asl #2]
	str	r3, [fp, #-60]
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	IsMain10Profile
	ldr	ip, [fp, #-56]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	beq	.L210
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
	b	.L181
.L242:
	mov	r5, r5, asl #4
	mul	r5, r8, r5
	add	r5, r5, r5, lsl #1
	b	.L185
.L240:
	ldr	r3, [fp, #4]
	cmp	ip, #0
	add	r8, r3, #255
	ldr	r3, [fp, #8]
	bic	r8, r8, #255
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [fp, #-56]
	blt	.L211
	ldr	r3, .L246+8
	ldr	r2, [r3, ip, asl #2]
	ldr	r2, [r2, #1444]
	cmp	r2, #8
	ble	.L212
	ldr	r1, [fp, #-56]
	cmp	r8, #0
	add	r2, r8, #3
	movge	r2, r8
	mov	r2, r2, asr #2
	str	r1, [fp, #-64]
	str	r2, [fp, #-60]
.L181:
	mov	r2, r8, asl #4
	str	r2, [r7, #4]
	mov	r2, r8, asl #3
	str	r2, [r7, #8]
	b	.L208
.L211:
	ldr	r3, [fp, #-56]
	str	r3, [fp, #8]
.L180:
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
	b	.L183
.L241:
	sub	r2, r10, #17
	ldr	r3, [fp, #4]
	clz	r2, r2
	mov	r2, r2, lsr #5
	cmp	r3, #1920
	orrgt	r2, r2, #1
	cmp	r2, #0
	moveq	r1, r2
	moveq	r3, r2
	beq	.L183
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
	b	.L183
.L244:
	mul	lr, r1, r2
	add	lr, lr, lr, lsl #1
	b	.L189
.L213:
	mov	r2, #0
	str	r2, [fp, #-60]
	mov	r1, r2
	str	r2, [fp, #-64]
	mov	r3, r2
	b	.L183
.L190:
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
	b	.L191
.L210:
	ldr	r1, [fp, #8]
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r1, [fp, #-56]
	b	.L181
.L212:
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-60]
	b	.L181
.L175:
	ldr	r3, .L246+28
	b	.L236
.L237:
	mov	r0, r6
	ldr	r3, .L246+32
	ldr	r2, .L246+20
	ldr	r1, .L246+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L233
.L243:
	ldr	r1, .L246+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L233
.L238:
	mov	r0, r7
	ldr	r3, .L246+40
	ldr	r2, .L246+20
	ldr	r1, .L246+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L233
.L247:
	.align	2
.L246:
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
	.size	VDMHAL_V5R2C1_ArrangeMem_Specific, .-VDMHAL_V5R2C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem
	.type	VDMHAL_V5R2C1_ArrangeMem, %function
VDMHAL_V5R2C1_ArrangeMem:
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
	beq	.L251
	cmp	r4, #0
	blt	.L252
	mov	r0, r4
	str	ip, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r3, .L255
	ldr	r1, [fp, #-48]
	ldr	ip, [fp, #-52]
	ldr	r3, [r3, r4, asl #2]
	ldr	r3, [r3, #1384]
	cmp	r3, #1
	beq	.L254
.L250:
	mov	r3, r1
	str	r9, [sp, #24]
	mov	r1, r0
	str	r4, [sp, #20]
	mov	r2, r10
	str	r8, [sp, #16]
	str	ip, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V5R2C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L252:
	mov	r0, #21
	b	.L250
.L251:
	mov	r0, #16
	b	.L250
.L254:
	mov	r1, r0
	str	r9, [fp, #12]
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V5R2C1_ArrangeMem_Normal
.L256:
	.align	2
.L255:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ArrangeMem, .-VDMHAL_V5R2C1_ArrangeMem
	.align	2
	.global	VDMHAL_V5R2C1_ResetVdm
	.type	VDMHAL_V5R2C1_ResetVdm, %function
VDMHAL_V5R2C1_ResetVdm:
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
	ble	.L258
	mov	r3, r6
	str	r0, [sp]
	ldr	r2, .L272
	ldr	r1, .L272+4
	bl	dprint_vfmw
.L257:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L258:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L270
	movw	r3, #1228
	ldr	r8, .L272+8
	mul	r3, r3, r6
	ldr	r5, .L272+12
	ldr	r2, [r5]
	ldr	r3, [r8, r3]
	ldr	r9, [r3, #36]
	ldr	r7, [r2, #120]
	tst	r7, #1
	beq	.L257
	ldr	r10, .L272+16
	mov	r3, #2
	bfi	r7, r3, #8, #2
	str	r7, [r2, #120]
	mov	r4, #0
	orr	r7, r7, #64
	ldr	r3, [r10, #112]
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	b	.L262
.L271:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L263
.L262:
	ldr	r3, [r10, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r2, [r3, #372]
	tst	r2, #4
	beq	.L271
	cmp	r4, #1000
	bge	.L263
	mov	r3, r6
	ldr	r2, .L272
	ldr	r1, .L272+20
	mov	r0, #0
	bl	dprint_vfmw
.L265:
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
.L263:
	mov	r3, r6
	ldr	r2, .L272
	ldr	r1, .L272+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L265
.L270:
	ldr	r1, .L272+28
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L273:
	.align	2
.L272:
	.word	.LANCHOR0+212
	.word	.LC28
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ResetVdm, .-VDMHAL_V5R2C1_ResetVdm
	.align	2
	.global	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R2C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R2C1_SetSmmuPageTableAddr:
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
	ldr	r3, .L280
	mov	r4, r0
	ldr	ip, [r3, #188]
	cmp	ip, #0
	beq	.L274
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	ip
	cmp	r4, #0
	bne	.L276
	ldr	r3, .L280+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L274:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L276:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L280+8
	ldr	r1, .L280+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L280+8
	ldr	r1, .L280+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L280+8
	ldr	r1, .L280+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L281:
	.align	2
.L280:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+236
	.word	.LC32
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_SetSmmuPageTableAddr, .-VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V5R2C1_EnableSmmu
	.type	VDMHAL_V5R2C1_EnableSmmu, %function
VDMHAL_V5R2C1_EnableSmmu:
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
	ldr	r3, .L283
	mov	r2, #8
	movt	r2, 3
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L284:
	.align	2
.L283:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_EnableSmmu, .-VDMHAL_V5R2C1_EnableSmmu
	.align	2
	.global	VDMHAL_V5R2C1_GlbResetX
	.type	VDMHAL_V5R2C1_GlbResetX, %function
VDMHAL_V5R2C1_GlbResetX:
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
	beq	.L297
	ldr	r5, .L299
	ldr	r3, [r5]
	ldr	r6, [r3, #120]
	tst	r6, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r8, .L299+4
	mov	r2, #2
	bfi	r6, r2, #8, #2
	str	r6, [r3, #120]
	mov	r4, #0
	orr	r6, r6, #16
	ldr	r3, [r8, #112]
	blx	r3
	ldr	r3, [r5]
	str	r6, [r3, #120]
	b	.L289
.L298:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L290
.L289:
	ldr	r2, [r8, #116]
	mov	r0, #30
	blx	r2
	ldr	r2, [r5]
	ldr	r2, [r2, #372]
	tst	r2, #1
	beq	.L298
	cmp	r4, #1000
	bge	.L290
	mov	r3, r7
	ldr	r2, .L299+8
	ldr	r1, .L299+12
	mov	r0, #0
	bl	dprint_vfmw
.L292:
	ldr	r2, [r5]
	bfc	r6, #4, #1
	ldr	r3, [r8, #112]
	str	r6, [r2, #120]
	bfc	r6, #8, #2
	blx	r3
	ldr	r3, [r5]
	str	r6, [r3, #120]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L290:
	mov	r3, r7
	ldr	r2, .L299+8
	ldr	r1, .L299+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L292
.L297:
	mov	r3, #0
	ldr	r2, .L299+8
	movt	r3, 63683
	ldr	r1, .L299+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L300:
	.align	2
.L299:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC35
	.word	.LC34
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GlbResetX, .-VDMHAL_V5R2C1_GlbResetX
	.align	2
	.global	VDMHAL_V5R2C1_GlbReset
	.type	VDMHAL_V5R2C1_GlbReset, %function
VDMHAL_V5R2C1_GlbReset:
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
	beq	.L303
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V5R2C1_GlbResetX
.L303:
	mov	r3, #0
	ldr	r2, .L304
	movt	r3, 63683
	ldr	r1, .L304+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L305:
	.align	2
.L304:
	.word	.LANCHOR0+296
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GlbReset, .-VDMHAL_V5R2C1_GlbReset
	.align	2
	.global	VDMHAL_V5R2C1_ClearIntState
	.type	VDMHAL_V5R2C1_ClearIntState, %function
VDMHAL_V5R2C1_ClearIntState:
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
	ldr	r7, .L322
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L322+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L319
	movw	r6, #1228
	ldr	r9, .L322+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L320
.L310:
	cmp	r4, #1
	beq	.L321
.L317:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L319:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L322+12
	ldr	r2, .L322+16
	bl	dprint_vfmw
.L306:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L321:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L317
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L306
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L306
.L320:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L310
.L311:
	ldr	r1, .L322+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L323:
	.align	2
.L322:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+320
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ClearIntState, .-VDMHAL_V5R2C1_ClearIntState
	.align	2
	.global	VDMHAL_V5R2C1_ClearMMUIntState
	.type	VDMHAL_V5R2C1_ClearMMUIntState, %function
VDMHAL_V5R2C1_ClearMMUIntState:
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
	bgt	.L329
	movw	r2, #1228
	ldr	r5, .L331
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L330
.L327:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L329:
	mov	r0, #0
	ldr	r2, .L331+4
	str	r0, [sp]
	ldr	r1, .L331+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L330:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L327
.L328:
	ldr	r1, .L331+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L332:
	.align	2
.L331:
	.word	g_HwMem
	.word	.LANCHOR0+348
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ClearMMUIntState, .-VDMHAL_V5R2C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V5R2C1_MaskInt
	.type	VDMHAL_V5R2C1_MaskInt, %function
VDMHAL_V5R2C1_MaskInt:
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
	bgt	.L338
	movw	r2, #1228
	ldr	r5, .L340
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L339
.L336:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L338:
	mov	r0, #0
	ldr	r2, .L340+4
	str	r0, [sp]
	ldr	r1, .L340+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L339:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L336
.L337:
	ldr	r1, .L340+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L341:
	.align	2
.L340:
	.word	g_HwMem
	.word	.LANCHOR0+380
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_MaskInt, .-VDMHAL_V5R2C1_MaskInt
	.align	2
	.global	VDMHAL_V5R2C1_GetIntMaskCfg
	.type	VDMHAL_V5R2C1_GetIntMaskCfg, %function
VDMHAL_V5R2C1_GetIntMaskCfg:
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
	.size	VDMHAL_V5R2C1_GetIntMaskCfg, .-VDMHAL_V5R2C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V5R2C1_EnableInt
	.type	VDMHAL_V5R2C1_EnableInt, %function
VDMHAL_V5R2C1_EnableInt:
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
	ldr	r2, .L356
	mov	r3, r0, asl #6
	ldr	r1, .L356+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1168]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L354
	movw	r5, #1228
	ldr	r6, .L356+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L355
.L349:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L354:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L356+12
	ldr	r2, .L356+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L355:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L349
.L350:
	ldr	r1, .L356+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L357:
	.align	2
.L356:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+404
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_EnableInt, .-VDMHAL_V5R2C1_EnableInt
	.align	2
	.global	VDMHAL_V5R2C1_CheckReg
	.type	VDMHAL_V5R2C1_CheckReg, %function
VDMHAL_V5R2C1_CheckReg:
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
	bgt	.L375
	movw	r4, #1228
	ldr	r6, .L377
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L376
.L361:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L367
.L369:
	.word	.L372
	.word	.L370
	.word	.L371
	.word	.L373
	.word	.L363
	.word	.L365
	.word	.L366
.L373:
	mov	r3, #40
.L368:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L372:
	mov	r3, #28
	b	.L368
.L371:
	mov	r3, #36
	b	.L368
.L370:
	mov	r3, #32
	b	.L368
.L366:
	movw	r3, #62272
	b	.L368
.L363:
	movw	r3, #61480
	b	.L368
.L365:
	movw	r3, #62304
	b	.L368
.L367:
	mov	r3, r7
	ldr	r2, .L377+4
	ldr	r1, .L377+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L362
	str	r8, [r6, r4]
	b	.L361
.L375:
	mov	r3, r5
	ldr	r2, .L377+4
	ldr	r1, .L377+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L362:
	ldr	r2, .L377+4
	ldr	r1, .L377+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L378:
	.align	2
.L377:
	.word	g_HwMem
	.word	.LANCHOR0+428
	.word	.LC39
	.word	.LC37
	.word	.LC38
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CheckReg, .-VDMHAL_V5R2C1_CheckReg
	.align	2
	.global	VDMHAL_V5R2C1_ReadMMUMask
	.type	VDMHAL_V5R2C1_ReadMMUMask, %function
VDMHAL_V5R2C1_ReadMMUMask:
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
	ble	.L382
	mov	r1, #1
	ldr	r2, .L383
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L383+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L382:
	movw	r0, #1228
	ldr	r2, .L383+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L384:
	.align	2
.L383:
	.word	.LANCHOR0+452
	.word	.LC40
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ReadMMUMask, .-VDMHAL_V5R2C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V5R2C1_WriteMMUMask
	.type	VDMHAL_V5R2C1_WriteMMUMask, %function
VDMHAL_V5R2C1_WriteMMUMask:
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
	ble	.L388
	mov	r1, #1
	ldr	r2, .L389
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L389+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L388:
	movw	r1, #1228
	ldr	r2, .L389+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L390:
	.align	2
.L389:
	.word	.LANCHOR0+480
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteMMUMask, .-VDMHAL_V5R2C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V5R2C1_PrepareDec
	.type	VDMHAL_V5R2C1_PrepareDec, %function
VDMHAL_V5R2C1_PrepareDec:
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
	beq	.L410
	cmp	r2, #0
	bgt	.L411
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
	b	.L393
.L396:
	.word	.L406
	.word	.L397
	.word	.L398
	.word	.L399
	.word	.L393
	.word	.L400
	.word	.L401
	.word	.L393
	.word	.L402
	.word	.L403
	.word	.L404
	.word	.L404
	.word	.L404
	.word	.L405
	.word	.L393
	.word	.L406
	.word	.L407
	.word	.L408
.L406:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V5R2C1_StartDec
.L407:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V5R2C1_StartDec
.L408:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V5R2C1_StartDec
.L397:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V5R2C1_StartDec
.L398:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V5R2C1_StartDec
.L399:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V5R2C1_StartDec
.L400:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V5R2C1_StartDec
.L401:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V5R2C1_StartDec
.L402:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V5R2C1_StartDec
.L403:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V5R2C1_StartDec
.L404:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V5R2C1_StartDec
.L405:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V5R2C1_StartDec
.L410:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L412
	ldr	r1, .L412+4
	bl	dprint_vfmw
.L393:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L411:
	mov	r3, r2
	mov	r0, #0
	ldr	r2, .L412
	str	r0, [sp]
	ldr	r1, .L412+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L413:
	.align	2
.L412:
	.word	.LANCHOR0+508
	.word	.LC41
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_PrepareDec, .-VDMHAL_V5R2C1_PrepareDec
	.align	2
	.global	VDMHAL_V5R2C1_IsVdmReady
	.type	VDMHAL_V5R2C1_IsVdmReady, %function
VDMHAL_V5R2C1_IsVdmReady:
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
	ldr	r3, .L421
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L419
	cmp	r0, #0
	ble	.L420
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L421+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L421+8
	bl	dprint_vfmw
	mov	r0, #0
.L416:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L420:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L419:
	mov	r0, r3
	ldr	r2, .L421+4
	ldr	r3, .L421+12
	ldr	r1, .L421+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L416
.L422:
	.align	2
.L421:
	.word	g_HwMem
	.word	.LANCHOR0+536
	.word	.LC40
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdmReady, .-VDMHAL_V5R2C1_IsVdmReady
	.align	2
	.global	VDMHAL_V5R2C1_IsVdmRun
	.type	VDMHAL_V5R2C1_IsVdmRun, %function
VDMHAL_V5R2C1_IsVdmRun:
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
	ldr	r3, .L430
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L428
	cmp	r0, #0
	ble	.L429
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L430+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L430+8
	bl	dprint_vfmw
	mov	r0, r4
.L425:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L429:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L428:
	ldr	r1, .L430+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L425
.L431:
	.align	2
.L430:
	.word	g_HwMem
	.word	.LANCHOR0+564
	.word	.LC40
	.word	.LC43
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdmRun, .-VDMHAL_V5R2C1_IsVdmRun
	.align	2
	.global	VDMHAL_V5R2C1_IsVdhDecOver
	.type	VDMHAL_V5R2C1_IsVdhDecOver, %function
VDMHAL_V5R2C1_IsVdhDecOver:
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
	ldr	r3, .L442
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L440
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	r4, #2
	beq	.L437
	cmp	r4, #3
	beq	.L437
	cmp	r4, #1
	beq	.L441
	mov	r3, r4
	ldr	r2, .L442+4
	ldr	r1, .L442+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L437:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L441:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L440:
	mov	r0, r3
	ldr	r2, .L442+4
	ldr	r3, .L442+12
	ldr	r1, .L442+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L443:
	.align	2
.L442:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdhDecOver, .-VDMHAL_V5R2C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V5R2C1_IsVdhPartDecOver
	.type	VDMHAL_V5R2C1_IsVdhPartDecOver, %function
VDMHAL_V5R2C1_IsVdhPartDecOver:
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
	ldr	r3, .L454
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L452
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	r4, #1
	beq	.L448
	cmp	r4, #2
	bne	.L453
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L453:
	mov	r3, r4
	ldr	r2, .L454+4
	ldr	r1, .L454+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L448:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L452:
	mov	r0, r3
	ldr	r2, .L454+4
	ldr	r3, .L454+12
	ldr	r1, .L454+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L455:
	.align	2
.L454:
	.word	g_HwMem
	.word	.LANCHOR0+616
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdhPartDecOver, .-VDMHAL_V5R2C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V5R2C1_UpdateHardwareInfo
	.type	VDMHAL_V5R2C1_UpdateHardwareInfo, %function
VDMHAL_V5R2C1_UpdateHardwareInfo:
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
	bgt	.L457
	ldr	r2, .L491
	ldr	r0, [r2]
	cmp	r0, #1
	addne	r3, r2, #124
	bne	.L461
	b	.L474
.L485:
	cmp	r2, r3
	beq	.L484
.L461:
	ldr	r0, [r2, #4]!
	cmp	r0, #1
	bne	.L485
.L474:
	mov	r5, r0
.L458:
	movw	r6, #1228
	ldr	r8, .L491+4
	mul	r6, r6, r4
	ldr	r7, [r8, r6]
	cmp	r7, #0
	beq	.L486
.L462:
	mov	r2, #180
	ldr	r1, .L491+8
	mul	r2, r2, r4
	mov	r3, r4, asl #6
	sub	r3, r3, r4, asl #3
	ldr	r0, [r7, #12]
	ldr	r6, .L491+12
	add	r3, r3, r1
	ldr	r1, [r3, #4]
	add	r3, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [r7, #28]
	cmp	r1, #1
	str	r2, [r3, #4]
	beq	.L487
	cmp	r5, #1
	beq	.L488
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
	bne	.L467
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
.L467:
	mov	lr, #180
	add	r1, r7, #33024
	mul	lr, lr, r4
	add	r2, lr, #48
	add	lr, lr, #176
	add	r2, r6, r2
	add	lr, r6, lr
.L468:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, lr
	bne	.L468
	cmp	r5, #0
	bne	.L489
	mov	r3, #180
	add	r7, r7, #32768
	mla	r4, r3, r4, r6
	ldr	r2, [r7, #384]
	ldr	r3, [r7, #388]
	mov	r0, r5
	str	r2, [r4, #48]
	str	r3, [r4, #44]
.L479:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L489:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L484:
	mov	r5, #0
	b	.L458
.L487:
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
.L488:
	movw	r3, #1228
	ubfx	r7, r2, #0, #17
	mla	r3, r3, r4, r8
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L490
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
	b	.L467
.L486:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L463
	str	r7, [r8, r6]
	b	.L462
.L457:
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L491+16
	ldr	r1, .L491+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L479
.L463:
	ldr	r1, .L491+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L479
.L490:
	ldr	r3, .L491+28
	ldr	r2, .L491+16
	ldr	r1, .L491+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L479
.L492:
	.align	2
.L491:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_VdmDrvParam+48
	.word	g_BackUp
	.word	.LANCHOR0+648
	.word	.LC28
	.word	.LC36
	.word	.LC44
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_UpdateHardwareInfo, .-VDMHAL_V5R2C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V5R2C1_ReadMsgSlot
	.type	VDMHAL_V5R2C1_ReadMsgSlot, %function
VDMHAL_V5R2C1_ReadMsgSlot:
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
	beq	.L497
	cmp	r2, #800
	bhi	.L498
	ldr	r3, .L499
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L498:
	mov	r0, r4
	ldr	r1, .L499+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L497:
	mov	r2, r0
	ldr	r1, .L499+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L500:
	.align	2
.L499:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ReadMsgSlot, .-VDMHAL_V5R2C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V5R2C1_WriteMsgSlot
	.type	VDMHAL_V5R2C1_WriteMsgSlot, %function
VDMHAL_V5R2C1_WriteMsgSlot:
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
	beq	.L502
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L502
	ldr	r3, .L505
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L502:
	ldr	r1, .L505+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L506:
	.align	2
.L505:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteMsgSlot, .-VDMHAL_V5R2C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V5R2C1_CfgRpMsg
	.type	VDMHAL_V5R2C1_CfgRpMsg, %function
VDMHAL_V5R2C1_CfgRpMsg:
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
	beq	.L546
	ldr	r2, [r7, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L547
	ldr	r1, [r7, #28]
	ldr	r3, [r7, #64]
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r0, [r7, #32]
	mov	r1, r1, asl r3
	cmp	r2, #1
	add	r2, r1, #255
	bic	r2, r2, #255
	mov	r3, r0, asl r3
	movne	r1, #0
	beq	.L548
.L511:
	ldr	r0, [r7, #4]
	cmp	r0, #16
	beq	.L512
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r2, r1
.L535:
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
	moveq	r2, r2, asl #4
	str	r2, [ip, #16]
	str	r1, [ip, #20]
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
	beq	.L549
.L517:
	cmp	r1, #1
	beq	.L533
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L534:
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
.L544:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L549:
	ldr	r3, [r7, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L518
	cmp	r3, #5
	moveq	r4, #4
	beq	.L518
	cmp	r3, #4
	moveq	r4, #8
	bne	.L550
.L518:
	ldr	r8, [r7, #44]
	cmp	r8, #0
	movle	r3, #0
	ldrle	r1, [r7, #56]
	strle	r3, [fp, #-64]
	ble	.L517
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
	b	.L521
.L553:
	ldrsh	r0, [r5, #70]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r10, r3
	str	r3, [fp, #-72]
	ldrgt	r10, [fp, #-88]
	bgt	.L524
.L523:
	ldr	r3, [fp, #-56]
	add	r6, r6, #1
	ldr	r8, [r3, #44]
	cmp	r6, r8
	bge	.L551
	cmp	r6, #199
	bgt	.L552
.L521:
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
	bgt	.L553
	ldr	r2, [fp, #-72]
	cmp	r10, r2
	movgt	r2, #0
	movle	r2, #1
	cmp	r6, #0
	moveq	r2, #0
	cmp	r2, #0
	bne	.L523
.L526:
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
	bgt	.L554
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
	b	.L523
.L527:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r7, r4, r0
	ldrsh	r0, [r5, #76]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	add	r2, r0, #1
	bhi	.L528
	cmp	r7, r2
	mov	r1, r4
	beq	.L528
	ldrsh	r0, [r5, #70]
	add	r0, r0, r10
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r7, r0
	bhi	.L555
.L528:
	cmp	r9, #198
	mov	r6, r9
	add	r5, r5, #4
	bgt	.L556
	ldrsh	r7, [r5, #74]
.L524:
	add	r9, r6, #1
	mov	r1, r4
	cmp	r9, r8
	add	r0, r10, r7
	blt	.L527
	ldr	r3, [fp, #-88]
	add	r0, r3, r7
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L526
.L556:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r3, r3, r9, lsl #2
	ldrsh	r0, [r3, #74]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r10, r4, r0
	b	.L526
.L512:
	mov	r0, #10
	str	r0, [fp, #-80]
	mla	r3, r2, r3, r1
	b	.L535
.L548:
	add	r0, r1, #2032
	adds	ip, r3, #63
	add	r0, r0, #15
	addmi	ip, r3, #126
	add	r1, r1, #4080
	cmp	r0, #0
	add	r1, r1, #14
	movge	r1, r0
	mov	r0, ip, asr #6
	mov	r1, r1, asr #11
	mov	r0, r0, asl #5
	mov	r1, r1, asl #4
	mul	r1, r1, r0
	b	.L511
.L554:
	ldr	r7, [fp, #-56]
	mov	r1, #1
	str	r1, [r7, #56]
.L533:
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
	b	.L534
.L555:
	mov	r10, r7
	b	.L526
.L551:
	mov	r7, r3
	ldr	r1, [r3, #56]
	b	.L517
.L552:
	ldr	r7, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L557
	movw	r3, #2196
	str	r6, [sp]
	ldr	r2, .L557+4
	str	r0, [fp, #-64]
	bl	dprint_vfmw
	ldr	r1, [r7, #56]
	b	.L517
.L550:
	ldr	r1, .L557+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L518
.L547:
	ldr	r1, .L557+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L544
.L546:
	ldr	r3, .L557+16
	ldr	r2, .L557+20
	ldr	r1, .L557+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L544
.L558:
	.align	2
.L557:
	.word	.LC51
	.word	.LANCHOR0+708
	.word	.LC50
	.word	.LC49
	.word	.LC48
	.word	.LANCHOR0+684
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CfgRpMsg, .-VDMHAL_V5R2C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V5R2C1_CfgRpReg
	.type	VDMHAL_V5R2C1_CfgRpReg, %function
VDMHAL_V5R2C1_CfgRpReg:
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
	bgt	.L593
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L594
.L562:
	ldr	r4, .L596
	ldr	r3, [r1, #48]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L595
	movw	r1, #1228
	ldr	r2, .L596+4
	mul	r1, r1, r6
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L565:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r6
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L567:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L569:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L571:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L573:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L575:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L577:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L579:
	movw	r3, #1228
	movw	r1, #3075
	mul	r6, r3, r6
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r6]
	str	r1, [r3, #84]
.L582:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L595:
	mov	r2, #16
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L596+4
	beq	.L565
	mov	r2, #12
	mov	r1, #2
	ldr	r0, [fp, #4]
	movw	r5, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r5, 48
	str	r5, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L567
	mov	r3, r5
	mov	r2, #60
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L569
	mov	r3, r5
	mov	r2, #64
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L571
	mov	r3, r5
	mov	r2, #68
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L573
	mov	r3, r5
	mov	r2, #72
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L575
	mov	r3, r5
	mov	r2, #76
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L577
	mov	r3, r5
	mov	r2, #80
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L596+4
	beq	.L579
	ldr	r0, [fp, #4]
	mov	r3, r5
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L594:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L563
	ldr	r1, [fp, #-40]
	str	r3, [r1]
	b	.L562
.L593:
	str	r0, [sp]
	ldr	r2, .L596+8
	ldr	r1, .L596+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L563:
	ldr	r1, .L596+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L597:
	.align	2
.L596:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0+732
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CfgRpReg, .-VDMHAL_V5R2C1_CfgRpReg
	.align	2
	.global	VDMHAL_V5R2C1_MakeDecReport
	.type	VDMHAL_V5R2C1_MakeDecReport, %function
VDMHAL_V5R2C1_MakeDecReport:
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
	beq	.L627
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L628
	movw	r3, #1228
	ldr	r7, .L636
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L602
	ldr	r3, .L636+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L605
	b	.L617
.L630:
	cmp	r3, r1
	beq	.L629
.L605:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L630
.L617:
	mov	r4, r2
.L603:
	ldr	r3, .L636+8
	mov	r2, #820
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L636+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L606
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L606:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L631
.L607:
	cmp	r2, #200
	bhi	.L632
.L609:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r7, [r7, #40]
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L633
	ldr	r8, .L636+16
	mov	r3, #3200
	ldr	r2, [r5, #12]
	mla	r4, r3, r6, r8
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V5R2C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	cmp	ip, #0
	movne	r3, r4
	movne	r2, r5
	movne	r1, #0
	beq	.L614
.L613:
	ldr	r0, [r3, #4]
	add	r1, r1, #1
	cmp	r1, ip
	add	r3, r3, #16
	add	r2, r2, #4
	strh	r0, [r2, #12]	@ movhi
	ldr	r0, [r3, #-8]
	strh	r0, [r2, #14]	@ movhi
	bne	.L613
.L614:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L634
.L600:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L631:
	cmp	r4, #1
	beq	.L635
	ldr	r1, .L636+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L607
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L607
	mov	r3, #1
	strh	r1, [r5, #16]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #18]	@ movhi
	str	r3, [r5, #12]
	b	.L600
.L629:
	mov	r4, #0
	b	.L603
.L634:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L636+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L636+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L615:
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
	ldr	r1, .L636+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L615
	ldr	r1, .L636+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L632:
	mov	r3, #200
	ldr	r1, .L636+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L609
.L635:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L607
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #16]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #18]	@ movhi
	b	.L600
.L633:
	ldr	r3, .L636+44
	ldr	r2, .L636+48
	ldr	r1, .L636+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L600
.L602:
	ldr	r3, .L636+56
	ldr	r2, .L636+48
	ldr	r1, .L636+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L600
.L628:
	mov	r0, r5
	ldr	r3, .L636+60
	ldr	r2, .L636+48
	ldr	r1, .L636+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L600
.L627:
	ldr	r3, .L636+64
	ldr	r2, .L636+48
	ldr	r1, .L636+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L600
.L637:
	.align	2
.L636:
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
	.size	VDMHAL_V5R2C1_MakeDecReport, .-VDMHAL_V5R2C1_MakeDecReport
	.align	2
	.global	VDMHAL_V5R2C1_PrepareRepair
	.type	VDMHAL_V5R2C1_PrepareRepair, %function
VDMHAL_V5R2C1_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	movw	r4, #1228
	mul	r4, r4, r3
	ldr	r8, .L653
	ldr	r7, .L653+4
	cmp	r3, #0
	mov	r6, #1744
	mov	r5, r3
	mov	r9, r0
	mov	r10, r1
	add	ip, r4, r7
	mla	r6, r6, r3, r8
	bgt	.L649
	ldr	r3, [r4, r7]
	cmp	r3, #0
	beq	.L650
.L641:
	cmp	r2, #0
	beq	.L651
	cmp	r2, #1
	movne	r0, #0
	beq	.L652
.L640:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L651:
	mov	r3, #1744
	mla	r8, r3, r5, r8
	ldr	r3, [r8, #44]
	cmp	r3, #0
	ble	.L644
	cmp	r9, #6
	bne	.L645
	ldrb	r3, [r10, #17]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r2, r3
	str	r2, [r8, #924]
.L645:
	mov	r2, r6
	mov	r1, r10
	mov	r0, r9
	str	ip, [fp, #-48]
	bl	VDMHAL_UpdateParam
	ldr	r3, [fp, #4]
	ldr	ip, [fp, #-48]
	mov	r2, r10
	mov	r0, r9
	str	r3, [sp]
	mov	r3, r5
	mov	r1, ip
	bl	VDMHAL_V5R2C1_CfgRpReg
	ldr	ip, [fp, #-48]
	mov	r2, r5
	mov	r0, r6
	mov	r1, ip
	bl	VDMHAL_V5R2C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L652:
	cmp	r9, #6
	str	ip, [fp, #-48]
	bne	.L647
	ldrb	r3, [r10, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L647
	mov	r4, #1744
	ldr	r7, .L653
	mul	r4, r4, r5
	add	r8, r8, r4
	ldr	r3, [r8, #916]
	cmp	r3, #0
	ble	.L647
	mov	r2, r6
	mov	r1, r10
	mov	r0, r9
	mov	r3, #2
	str	r3, [r8, #924]
	bl	VDMHAL_UpdateParam
	ldr	r3, [fp, #4]
	ldr	ip, [fp, #-48]
	mov	r2, r10
	mov	r0, r9
	str	r3, [sp]
	mov	r3, r5
	mov	r1, ip
	bl	VDMHAL_V5R2C1_CfgRpReg
	ldr	ip, [fp, #-48]
	add	r0, r4, #872
	mov	r2, r5
	add	r0, r7, r0
	mov	r1, ip
	bl	VDMHAL_V5R2C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L650:
	mov	r0, #0
	str	r2, [fp, #-52]
	movt	r0, 63683
	str	ip, [fp, #-48]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L642
	str	r3, [r4, r7]
	ldr	ip, [fp, #-48]
	ldr	r2, [fp, #-52]
	b	.L641
.L649:
	mov	r0, #0
	ldr	r2, .L653+8
	str	r0, [sp]
	ldr	r1, .L653+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L640
.L647:
	ldr	r1, .L653+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L640
.L644:
	mov	r0, r2
	ldr	r1, .L653+20
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	mov	r0, r2
	b	.L640
.L642:
	ldr	r1, .L653+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L640
.L654:
	.align	2
.L653:
	.word	g_RepairParam
	.word	g_HwMem
	.word	.LANCHOR0+784
	.word	.LC28
	.word	.LC61
	.word	.LC60
	.word	.LC59
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_PrepareRepair, .-VDMHAL_V5R2C1_PrepareRepair
	.align	2
	.global	VDMHAL_V5R2C1_StartHwRepair
	.type	VDMHAL_V5R2C1_StartHwRepair, %function
VDMHAL_V5R2C1_StartHwRepair:
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
	ldr	r6, .L685
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L679
	cmp	r0, #0
	ble	.L680
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L685+4
	mov	r0, #32
	ldr	r1, .L685+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L681
.L663:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L685+4
	ldr	r1, .L685+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L675
.L658:
	cmp	r4, #0
	beq	.L682
	mov	r3, r5, asl #6
	ldr	r2, .L685+12
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
.L680:
	movw	r3, #1228
	ldr	r4, .L685+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L661:
	movw	r3, #1228
	ldr	r2, .L685+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L670:
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
.L655:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L679:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L683
	cmp	r5, #0
	ldrle	r4, .L685+16
	bgt	.L663
	b	.L661
.L683:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L658
	ldr	r3, .L685+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L684
.L667:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L685+24
	ldr	r1, .L685+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L685+24
	ldr	r1, .L685+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L685+24
	ldr	r1, .L685+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L655
.L681:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L658
.L675:
	ldr	r3, .L685+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L667
.L682:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L685+24
	ldr	r1, .L685+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L684:
	ldr	r4, .L685+16
	b	.L670
.L686:
	.align	2
.L685:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_StartHwRepair, .-VDMHAL_V5R2C1_StartHwRepair
	.align	2
	.global	VDMHAL_V5R2C1_CalVdhClkSkip
	.type	VDMHAL_V5R2C1_CalVdhClkSkip, %function
VDMHAL_V5R2C1_CalVdhClkSkip:
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
	ldr	r9, .L717
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L709
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L689
.L716:
	mov	r3, r10
	ldr	r2, .L717+4
	ldr	r1, .L717+8
	mov	r0, #1
	bl	dprint_vfmw
.L691:
	cmp	r4, r9
	beq	.L715
.L708:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L715
.L689:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L716
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L692
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L692:
	ldr	r3, .L717+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1464]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L710
.L695:
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L710
	.word	.L704
	.word	.L704
	.word	.L710
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L704
	.word	.L710
	.word	.L705
	.word	.L704
	.word	.L704
.L704:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L708
.L715:
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
.L705:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L691
.L710:
	mov	r7, #0
	b	.L691
.L709:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L718:
	.align	2
.L717:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC63
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalVdhClkSkip, .-VDMHAL_V5R2C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V5R2C1_GetVdmClk
	.type	VDMHAL_V5R2C1_GetVdmClk, %function
VDMHAL_V5R2C1_GetVdmClk:
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
	ldr	r2, .L727
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L720
.L722:
	.word	.L720
	.word	.L723
	.word	.L724
	.word	.L725
.L720:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L724:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L723:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L725:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L728:
	.align	2
.L727:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GetVdmClk, .-VDMHAL_V5R2C1_GetVdmClk
	.align	2
	.global	VDMHAL_V5R2C1_StartHwDecode
	.type	VDMHAL_V5R2C1_StartHwDecode, %function
VDMHAL_V5R2C1_StartHwDecode:
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
	bgt	.L769
	mov	r1, r5, asl #6
	ldr	r6, .L775
	sub	r1, r1, r5, asl #3
	ldr	r9, .L775+4
	add	r1, r6, r1
	ldr	r8, [r1, #8]
	ldr	r3, [r9, r8, asl #2]
	ldr	r2, [r3, #1460]
	cmp	r2, #1
	beq	.L770
.L753:
	mov	r10, #0
.L732:
	ldr	r7, .L775+8
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L771
	ldr	r3, .L775+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	ubfx	r1, r3, #8, #2
	cmp	r10, r1
	bfine	r3, r10, #8, #2
	strne	r3, [r2, #120]
.L736:
	mov	r1, r10
	mov	r0, r5
	bl	VDMHAL_V5R2C1_GetVdmClk
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r3, [r9, r8, asl #2]
	cmp	r2, #1
	ldr	r9, [r3, #1168]
	bne	.L772
	ldr	r3, .L775+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L739:
	mov	r2, r5
	mov	r3, r4
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r10, .L775+8
	cmp	r2, #1
	bne	.L773
	movw	r2, #1228
	ldr	r3, .L775+16
	mul	r2, r2, r5
	ldr	r4, .L775+20
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r4, r2]
	moveq	r1, #15
	movne	r1, #0
	str	r3, [r2, #156]
.L741:
	movw	r2, #1228
	cmp	r9, #1
	mul	r2, r2, r5
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r4, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L743:
	movw	r2, #1228
	mul	r2, r2, r5
	ldr	r2, [r4, r2]
	str	r3, [r2, #36]
.L745:
	ldr	r7, .L775+24
	mov	r0, #30
	ldr	r3, [r7, #116]
	blx	r3
	ldr	r3, [r7, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r5
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r5, r1, r5, r6
	ldr	ip, .L775+28
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
.L771:
	mov	r2, #0
	mov	r3, r10
	mov	r1, r2
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L736
.L769:
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L775+32
	ldr	r1, .L775+36
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L773:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r4
	bl	VDH_Record_RegData
	ldr	r3, .L775+16
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #15
	movne	r1, #0
	cmp	r2, #1
	ldreq	r4, .L775+20
	beq	.L741
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r4
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r9, #1
	ldrb	r2, [r7]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r4, .L775+20
	beq	.L743
	mov	r0, r4
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r4, .L775+20
	beq	.L745
	cmp	r4, #0
	beq	.L774
	mov	r3, #1
	str	r8, [r4, #8]
	strb	r5, [r4]
	mov	r0, r4
	str	r3, [r4, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_PostTask
.L772:
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L739
.L770:
	ldr	r3, [r3, #536]
	cmp	r3, #17
	bne	.L753
	ldr	r3, .L775+40
	ldr	r3, [r3, r8, asl #2]
	ldr	r2, [r3, #40]
	cmp	r2, #3840
	bge	.L733
	ldr	r3, [r3, #44]
	cmp	r3, #2160
	blt	.L753
.L733:
	ldr	r3, .L775+24
	movw	r0, #12320
	movt	r0, 63650
	ldr	r3, [r3, #152]
	blx	r3
	ldr	r3, .L775+44
	ldr	r3, [r3]
	ldr	r3, [r3, #196]
	mov	r3, r3, lsr #24
	cmp	r3, #3
	beq	.L754
	cmp	r3, #2
	beq	.L755
	mov	r2, #221
	cmp	r3, #1
	mov	r1, r2
	movt	r2, 137
	movt	r1, 113
	moveq	r3, r2
	movne	r3, r1
.L734:
	str	r3, [r0]
	mov	r10, #2
	b	.L732
.L774:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L775+32
	ldr	r1, .L775+48
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L754:
	mov	r3, #221
	movt	r3, 113
	b	.L734
.L755:
	mov	r3, #221
	movt	r3, 125
	b	.L734
.L776:
	.align	2
.L775:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HalDisable
	.word	g_pstRegCrg
	.word	mask_mmu_err_int
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+884
	.word	.LC28
	.word	s_pFspInst
	.word	g_pstRegSysCtrl
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_StartHwDecode, .-VDMHAL_V5R2C1_StartHwDecode
	.align	2
	.global	VDMHAL_V5R2C1_GetCharacter
	.type	VDMHAL_V5R2C1_GetCharacter, %function
VDMHAL_V5R2C1_GetCharacter:
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
	ldr	r1, .L778
	mov	r0, #15
	ldr	r3, .L778+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L779:
	.align	2
.L778:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GetCharacter, .-VDMHAL_V5R2C1_GetCharacter
	.align	2
	.global	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R2C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R2C1_WriteBigTitle1DYuv:
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
	beq	.L781
	cmp	r3, #2
	moveq	r4, #1
	movne	r4, #2
.L781:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L780
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L870
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L784
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L870+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L784
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
	bne	.L785
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L870+8
	mov	r3, r3, lsr #1
	ldr	r4, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r9, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r9, [fp, #-96]
	beq	.L787
.L786:
	cmp	r5, #0
	beq	.L789
	ldr	r2, [fp, #-96]
	mov	r7, #0
	and	r10, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L788:
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
	bhi	.L788
.L789:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L786
.L787:
	ldr	r3, [fp, #-100]
	mov	r0, r4
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
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
	mov	r7, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L792:
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
	beq	.L868
.L796:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L797
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
	ldr	r3, [fp, #-124]
.L867:
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
.L780:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L784:
	ldr	r1, .L870+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L785:
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
	ldr	r6, .L870+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L804
.L806:
	cmp	r5, #0
	beq	.L807
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L805:
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
	bhi	.L805
.L807:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L806
.L804:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	ip, [r6, #44]
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	mov	r1, r1, lsr #1
	blx	ip
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L808
	ldr	r3, [fp, #-104]
	mov	r8, #0
	ldr	r9, [fp, #-116]
	str	r8, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L809:
	cmp	r5, #0
	beq	.L812
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r10, r3, r10, lsl #8
.L810:
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
	bhi	.L810
.L812:
	ldr	r3, [fp, #-96]
	add	r8, r8, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L809
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L869
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L815
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L820
.L821:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L821
.L820:
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
.L815:
	ldr	r3, [fp, #-132]
	b	.L867
.L868:
	ldr	r2, [fp, #-120]
	add	r4, r4, #1
	ldr	r7, [fp, #-124]
	mov	r3, #0
	ldr	r8, [fp, #-112]
.L798:
	cmp	r7, #0
	moveq	lr, r2
	beq	.L801
	sub	r0, r2, #-67108863
	add	lr, r2, r7
	sub	r0, r0, #65011712
	mov	r1, r4
.L799:
	ldrb	ip, [r1, #-1]	@ zero_extendqisi2
	strb	ip, [r0, #1]!
	ldrb	ip, [r1], #2	@ zero_extendqisi2
	strb	ip, [r2], #1
	cmp	r2, lr
	bne	.L799
.L801:
	add	r3, r3, #1
	mov	r2, lr
	cmp	r3, r8
	add	r4, r4, r5
	bne	.L798
	b	.L797
.L869:
	ldr	r3, [fp, #-124]
	ldr	r4, [fp, #-120]
	ldr	lr, [fp, #-132]
	mla	r2, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	mov	r3, #0
	add	r2, r2, #1
.L816:
	cmp	lr, #0
	beq	.L819
	mov	r1, r3, lsr #1
	mov	r0, r2
	mul	r1, lr, r1
	sub	ip, r1, #-67108863
	add	r9, r1, lr
	sub	ip, ip, #65011712
	add	r9, r4, r9
	add	ip, r4, ip
	add	r1, r4, r1
.L817:
	ldrb	r8, [r0, #-1]	@ zero_extendqisi2
	strb	r8, [ip, #1]!
	ldrb	r8, [r0], #2	@ zero_extendqisi2
	strb	r8, [r1], #1
	cmp	r1, r9
	bne	.L817
.L819:
	add	r3, r3, #2
	add	r2, r2, r5
	cmp	r7, r3
	bhi	.L816
	b	.L815
.L790:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L796
	b	.L797
.L808:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L815
	cmp	r3, #0
	beq	.L820
	b	.L815
.L871:
	.align	2
.L870:
	.word	.LC64
	.word	.LC66
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteBigTitle1DYuv, .-VDMHAL_V5R2C1_WriteBigTitle1DYuv
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
	ldr	ip, .L879
	mov	lr, r2
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L878
	cmp	r0, #0
	bne	.L874
	ldr	r3, .L879+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L874:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L879+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L878:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L880:
	.align	2
.L879:
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
	ldr	ip, .L887
	mov	lr, r3
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L885
	cmp	r2, #0
	ble	.L886
	mov	r3, r2
	str	ip, [sp]
	ldr	r2, .L887+4
	mov	r0, #32
	ldr	r1, .L887+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L886:
	movw	r3, #1228
	ldr	ip, .L887+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L885:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L888:
	.align	2
.L887:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.55505, %object
	.size	__func__.55505, 22
__func__.55505:
	.ascii	"VDMHAL_V5R2C1_OpenHAL\000"
	.space	2
	.type	__func__.55579, %object
	.size	__func__.55579, 25
__func__.55579:
	.ascii	"VDMHAL_V5R2C1_CalcFsSize\000"
	.space	3
	.type	__func__.55605, %object
	.size	__func__.55605, 24
__func__.55605:
	.ascii	"VDMHAL_V5R2C1_CalcFsNum\000"
	.type	__func__.55648, %object
	.size	__func__.55648, 32
__func__.55648:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.55649, %object
	.size	__FUNCTION__.55649, 32
__FUNCTION__.55649:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Normal\000"
	.type	__func__.55591, %object
	.size	__func__.55591, 33
__func__.55591:
	.ascii	"VDMHAL_V5R2C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.55731, %object
	.size	__func__.55731, 34
__func__.55731:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.55754, %object
	.size	__func__.55754, 23
__func__.55754:
	.ascii	"VDMHAL_V5R2C1_ResetVdm\000"
	.space	1
	.type	__func__.55764, %object
	.size	__func__.55764, 35
__func__.55764:
	.ascii	"VDMHAL_V5R2C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.55785, %object
	.size	__func__.55785, 24
__func__.55785:
	.ascii	"VDMHAL_V5R2C1_GlbResetX\000"
	.type	__func__.55774, %object
	.size	__func__.55774, 23
__func__.55774:
	.ascii	"VDMHAL_V5R2C1_GlbReset\000"
	.space	1
	.type	__func__.55797, %object
	.size	__func__.55797, 28
__func__.55797:
	.ascii	"VDMHAL_V5R2C1_ClearIntState\000"
	.type	__func__.55803, %object
	.size	__func__.55803, 31
__func__.55803:
	.ascii	"VDMHAL_V5R2C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.55809, %object
	.size	__func__.55809, 22
__func__.55809:
	.ascii	"VDMHAL_V5R2C1_MaskInt\000"
	.space	2
	.type	__func__.55822, %object
	.size	__func__.55822, 24
__func__.55822:
	.ascii	"VDMHAL_V5R2C1_EnableInt\000"
	.type	__func__.55831, %object
	.size	__func__.55831, 23
__func__.55831:
	.ascii	"VDMHAL_V5R2C1_CheckReg\000"
	.space	1
	.type	__func__.55845, %object
	.size	__func__.55845, 26
__func__.55845:
	.ascii	"VDMHAL_V5R2C1_ReadMMUMask\000"
	.space	2
	.type	__func__.55850, %object
	.size	__func__.55850, 27
__func__.55850:
	.ascii	"VDMHAL_V5R2C1_WriteMMUMask\000"
	.space	1
	.type	__func__.55881, %object
	.size	__func__.55881, 25
__func__.55881:
	.ascii	"VDMHAL_V5R2C1_PrepareDec\000"
	.space	3
	.type	__func__.55886, %object
	.size	__func__.55886, 25
__func__.55886:
	.ascii	"VDMHAL_V5R2C1_IsVdmReady\000"
	.space	3
	.type	__func__.55891, %object
	.size	__func__.55891, 23
__func__.55891:
	.ascii	"VDMHAL_V5R2C1_IsVdmRun\000"
	.space	1
	.type	__func__.55897, %object
	.size	__func__.55897, 27
__func__.55897:
	.ascii	"VDMHAL_V5R2C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.55907, %object
	.size	__func__.55907, 31
__func__.55907:
	.ascii	"VDMHAL_V5R2C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.55922, %object
	.size	__func__.55922, 33
__func__.55922:
	.ascii	"VDMHAL_V5R2C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.55995, %object
	.size	__func__.55995, 23
__func__.55995:
	.ascii	"VDMHAL_V5R2C1_CfgRpMsg\000"
	.space	1
	.type	__func__.55972, %object
	.size	__func__.55972, 24
__func__.55972:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.56006, %object
	.size	__func__.56006, 23
__func__.56006:
	.ascii	"VDMHAL_V5R2C1_CfgRpReg\000"
	.space	1
	.type	__func__.56019, %object
	.size	__func__.56019, 28
__func__.56019:
	.ascii	"VDMHAL_V5R2C1_MakeDecReport\000"
	.type	__func__.56088, %object
	.size	__func__.56088, 28
__func__.56088:
	.ascii	"VDMHAL_V5R2C1_PrepareRepair\000"
	.type	__func__.56278, %object
	.size	__func__.56278, 15
__func__.56278:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.56095, %object
	.size	__func__.56095, 28
__func__.56095:
	.ascii	"VDMHAL_V5R2C1_StartHwRepair\000"
	.type	__func__.56134, %object
	.size	__func__.56134, 28
__func__.56134:
	.ascii	"VDMHAL_V5R2C1_CalVdhClkSkip\000"
	.type	__func__.56160, %object
	.size	__func__.56160, 28
__func__.56160:
	.ascii	"VDMHAL_V5R2C1_StartHwDecode\000"
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
	ASCII(.ascii	"VDMHAL_V5R2C1_OpenHAL: Size error!\000" )
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
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC/VP9 10 bit\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC11:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V5R2C1_ArrangeMe" )
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
	ASCII(.ascii	"VDMHAL_V5R2C1_CalcFsSize err!\012\000" )
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
	ASCII(.ascii	"VDMHAL_V5R2C1_ArrangeMem Mem addr is NULL\000" )
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
	ASCII(.ascii	"VDMHAL_V5R2C1_ResetVdm: map vdm register fail, vir(" )
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
