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
	.file	"postprocess.c"
	.text
	.align	2
	.global	PostPro_GetRepairStratage
	.type	PostPro_GetRepairStratage, %function
PostPro_GetRepairStratage:
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
	cmp	r0, #0
	beq	.L4
	cmp	r0, #15
	beq	.L4
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L4:
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_GetRepairStratage, .-PostPro_GetRepairStratage
	.align	2
	.global	PostPro_CopyYuv_Mpeg4
	.type	PostPro_CopyYuv_Mpeg4, %function
PostPro_CopyYuv_Mpeg4:
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
	mov	r5, #1744
	mul	r5, r5, r1
	add	r3, r0, #12288
	ldr	r9, .L12
	ldr	lr, [r3, #2288]
	add	ip, r9, r5
	ldr	r4, .L12+4
	ldr	r10, [r3, #2372]
	add	r6, ip, #48
	str	lr, [ip, #8]
	ldr	lr, [r0, #220]
	ldr	r8, [r4, #136]
	ldr	r4, [r3, #2300]
	str	lr, [ip, #20]
	ldr	lr, [r0, #228]
	ldr	r3, [r3, #2304]
	str	r6, [fp, #-48]
	mov	r6, #0
	str	lr, [ip, #24]
	cmp	r8, r6
	ldrh	lr, [r0, #164]
	str	r4, [fp, #-52]
	mov	r4, #1
	str	lr, [ip, #28]
	ldrh	r7, [r0, #166]
	strb	r10, [r9, r5]
	mov	r9, #4
	str	r3, [ip, #16]
	smulbb	lr, r7, lr
	ldr	r3, [fp, #-48]
	ldr	r5, [fp, #-52]
	str	r9, [ip, #64]
	str	r7, [ip, #32]
	sub	lr, lr, #1
	str	r5, [ip, #12]
	str	r6, [r3, #4]
	strh	lr, [ip, #74]	@ movhi
	str	r6, [ip, #40]
	strh	r6, [ip, #72]	@ movhi
	str	r4, [ip, #36]
	str	r4, [ip, #44]
	str	r4, [ip, #56]
	ldrb	r3, [r0, #159]	@ zero_extendqisi2
	moveq	r0, r4
	strb	r3, [ip, #1]
	beq	.L10
	str	r2, [sp]
	mov	r3, r1
	mov	r2, r6
	mov	r1, r0
	mov	r0, #2
	blx	r8
	subs	r0, r0, r6
	movne	r0, #1
.L10:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L13:
	.align	2
.L12:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Mpeg4, .-PostPro_CopyYuv_Mpeg4
	.align	2
	.global	PostPro_CopyYuv_Vc1
	.type	PostPro_CopyYuv_Vc1, %function
PostPro_CopyYuv_Vc1:
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
	ldrh	r3, [r0, #74]
	sub	ip, r3, #1
	cmp	ip, #2048
	movcc	r10, #16
	bcc	.L15
	sub	ip, r3, #2048
	sub	ip, ip, #1
	cmp	ip, #2048
	movcc	r10, #32
	bcs	.L22
.L15:
	mov	r5, #1744
	add	lr, r0, #12288
	mul	r5, r5, r1
	ldr	r8, .L23
	ldr	r9, [lr, #268]
	mov	r4, #0
	ldr	r3, [lr, #272]
	add	ip, r8, r5
	ldr	r7, .L23+4
	smulbb	r6, r3, r9
	str	r9, [ip, #28]
	ldr	r9, [lr, #272]
	str	r10, [ip, #60]
	sub	r6, r6, #1
	ldr	r10, [lr, #176]
	str	r9, [ip, #32]
	ldr	r9, [lr, #108]
	strh	r6, [ip, #74]	@ movhi
	ldr	r6, [lr, #100]
	str	r9, [ip, #24]
	ldr	r9, [lr, #228]
	ldr	r7, [r7, #136]
	str	r6, [ip, #20]
	mov	r6, #4
	str	r9, [ip, #8]
	cmp	r7, r4
	ldr	r9, [lr, #180]
	str	r6, [ip, #64]
	str	r10, [ip, #12]
	str	r9, [ip, #16]
	ldr	r9, [lr, #260]
	mov	lr, #1
	str	r4, [ip, #52]
	str	r4, [ip, #40]
	strb	r9, [r8, r5]
	strh	r4, [ip, #72]	@ movhi
	str	r4, [ip, #48]
	str	lr, [ip, #36]
	str	lr, [ip, #44]
	str	lr, [ip, #56]
	ldrb	r3, [r0, #71]	@ zero_extendqisi2
	moveq	r0, lr
	strb	r3, [ip, #1]
	beq	.L16
	str	r2, [sp]
	mov	r3, r1
	mov	r2, r4
	mov	r1, r0
	mov	r0, lr
	blx	r7
	subs	r0, r0, r4
	movne	r0, #1
.L16:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L22:
	sub	ip, r3, #4096
	sub	ip, ip, #1
	cmp	ip, #2048
	movcc	r10, #48
	bcc	.L15
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	r10, #16
	movcc	r10, #64
	b	.L15
.L24:
	.align	2
.L23:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vc1, .-PostPro_CopyYuv_Vc1
	.align	2
	.global	PostPro_CopyYuv_Vp6
	.type	PostPro_CopyYuv_Vp6, %function
PostPro_CopyYuv_Vp6:
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
	mov	r6, #1744
	mul	r6, r6, r1
	ldr	r8, .L28
	ldr	lr, [r0, #176]
	mov	r5, #0
	mov	r4, #1
	mov	r9, #4
	add	ip, r8, r6
	ldr	r7, .L28+4
	str	lr, [ip, #8]
	ldr	lr, [r0, #184]
	ldr	r7, [r7, #136]
	str	lr, [ip, #20]
	cmp	r7, r5
	ldr	lr, [r0, #188]
	str	lr, [ip, #24]
	ldrh	lr, [r0, #54]
	str	lr, [ip, #28]
	ldrh	r10, [r0, #56]
	str	r4, [ip, #36]
	str	r4, [ip, #44]
	smulbb	lr, r10, lr
	str	r10, [ip, #32]
	str	r5, [ip, #40]
	strh	r5, [ip, #72]	@ movhi
	str	r5, [ip, #48]
	sub	lr, lr, #1
	strh	lr, [ip, #74]	@ movhi
	ldr	lr, [r0, #212]
	str	r4, [ip, #56]
	str	r9, [ip, #64]
	strb	lr, [r8, r6]
	str	r5, [ip, #52]
	ldr	r3, [r0, #192]
	str	r3, [ip, #12]
	ldr	r3, [r0, #196]
	str	r3, [ip, #16]
	ldrb	r3, [r0, #52]	@ zero_extendqisi2
	moveq	r0, r4
	strb	r3, [ip, #1]
	beq	.L26
	str	r2, [sp]
	mov	r3, r1
	mov	r2, r5
	mov	r1, r0
	mov	r0, #10
	blx	r7
	subs	r0, r0, r5
	movne	r0, #1
.L26:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L29:
	.align	2
.L28:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vp6, .-PostPro_CopyYuv_Vp6
	.align	2
	.global	PostPro_CopyYuv_Vp9
	.type	PostPro_CopyYuv_Vp9, %function
PostPro_CopyYuv_Vp9:
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
	mov	r3, #1744
	mul	r8, r3, r1
	add	r5, r0, #270336
	ldr	r9, .L33
	ldr	lr, [r5, #2088]
	ldr	r10, [r5, #2092]
	add	r4, r9, r8
	ldr	r3, [r5, #2440]
	add	ip, r4, #24
	ldr	r6, [r5, #2448]
	ldr	r7, [r5, #2456]
	str	r1, [fp, #-56]
	str	r0, [fp, #-52]
	mov	r0, #22
	str	r2, [fp, #-60]
	mov	r2, lr
	ldr	r1, .L33+4
	str	r3, [r4, #8]
	mov	r3, r10
	str	r6, [r4, #20]
	mov	r6, #1
	str	r7, [r4, #24]
	mov	r7, #0
	str	lr, [r4, #28]
	str	r10, [r4, #32]
	str	r6, [r4, #36]
	str	r7, [r4, #40]
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, [fp, #-48]
	mov	r2, #6
	ldr	r0, .L33+8
	ldr	lr, [r4, #32]
	ldr	ip, [ip, #4]
	ldr	r1, [r5, #2468]
	strh	r7, [r4, #72]	@ movhi
	smulbb	lr, lr, ip
	ldr	ip, [r0, #136]
	ldrb	r0, [r5, #2081]	@ zero_extendqisi2
	cmp	ip, r7
	str	r7, [r4, #48]
	sub	lr, lr, #1
	str	r6, [r4, #56]
	strb	r0, [r4, #1]
	moveq	r0, r6
	strb	r1, [r9, r8]
	strh	lr, [r4, #74]	@ movhi
	str	r2, [r4, #64]
	str	r6, [r4, #44]
	str	r7, [r4, #52]
	beq	.L31
	ldr	r2, [fp, #-60]
	mov	r0, #17
	ldr	r3, [fp, #-56]
	ldr	r1, [fp, #-52]
	str	r2, [sp]
	mov	r2, r7
	blx	ip
	subs	r0, r0, r7
	movne	r0, #1
.L31:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	g_RepairParam
	.word	.LC0
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vp9, .-PostPro_CopyYuv_Vp9
	.align	2
	.global	PostPro_GetHevcMbGroupOfTile
	.type	PostPro_GetHevcMbGroupOfTile, %function
PostPro_GetHevcMbGroupOfTile:
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
	ldr	ip, .L70
	mov	lr, r3, asl #6
	mov	r7, r0
	sub	r3, lr, r3, asl #3
	mov	r6, #0
	add	ip, ip, r3
	str	r6, [r0, #44]
	mov	r5, r1
	ldr	r0, .L70+4
	ldr	r1, [ip, #8]
	str	r6, [r7, #56]
	ldr	r3, [r7, #28]
	ldr	r0, [r0, r1, asl #2]
	ldr	r4, [r7, #32]
	add	r0, r0, #294912
	str	r2, [fp, #-48]
	add	r0, r0, #888
	mul	r4, r4, r3
	bl	HEVC_CalcTileMap
	ldr	r3, [r5, #12]
	cmp	r3, r6
	beq	.L42
	mov	lr, r6
	ldr	r8, .L70+8
	ldr	r6, .L70+12
	mov	r0, r5
	mov	r1, #1
.L41:
	ldrh	ip, [r0, #16]
	ldrh	r2, [r0, #18]
	cmp	ip, r2
	mov	r3, ip
	bls	.L40
	b	.L39
.L68:
	ldrh	ip, [r0, #16]
.L40:
	cmp	r4, ip
	blt	.L43
	cmp	r4, r2
	ldrge	r2, [r6, r3, asl #2]
	strgeb	r1, [r8, r2]
.L43:
	ldrh	r2, [r0, #18]
	add	r3, r3, #1
	cmp	r2, r3
	bcs	.L68
.L39:
	ldr	r3, [r5, #12]
	add	lr, lr, #1
	add	r0, r0, #4
	cmp	r3, lr
	bhi	.L41
.L42:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #2488]
	cmp	r3, #0
	beq	.L38
	ldr	r6, [fp, #-48]
	mov	r10, #0
	ldr	lr, .L70+8
	mov	r9, r10
	str	r4, [fp, #-48]
	mov	r8, r6
.L45:
	ldr	r0, [r8, #3580]
	ldr	ip, [r8, #3584]
	cmp	r0, ip
	bhi	.L50
	ldr	r3, .L70+12
	mov	r4, r0, asl #2
	ldr	r5, [r3, r0, asl #2]
	ldrb	r3, [lr, r5]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, .L70+12
	movne	r3, r0
	addne	r2, r2, r4
	bne	.L49
	b	.L48
.L51:
	ldr	r1, [r2, #4]!
	ldrb	r1, [lr, r1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L48
.L49:
	add	r3, r3, #1
	cmp	r3, ip
	bls	.L51
.L50:
	ldr	r3, [r6, #2488]
	add	r10, r10, #1
	add	r8, r8, #8
	cmp	r3, r10
	bhi	.L45
	ldr	r4, [fp, #-48]
.L38:
	ldr	lr, .L70+8
	mov	ip, #0
.L57:
	cmp	ip, r4
	bcs	.L58
	ldrb	r3, [lr, ip]	@ zero_extendqisi2
	cmp	r3, #1
	addeq	ip, ip, #1
	ldreq	r0, [r7, #44]
	beq	.L53
	add	r1, ip, lr
	mov	r2, ip
	b	.L55
.L54:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L56
	mov	r2, r3
.L55:
	add	r3, r2, #1
	cmp	r4, r3
	bhi	.L54
.L56:
	ldr	r1, [r7, #44]
	add	r0, r1, #1
	add	r1, r7, r1, lsl #2
	strh	ip, [r1, #72]	@ movhi
	mov	ip, r3
	strh	r2, [r1, #74]	@ movhi
	str	r0, [r7, #44]
.L53:
	cmp	r0, #199
	ble	.L57
	ldr	r1, .L70+16
	mov	r0, #1
	bl	dprint_vfmw
	sub	r4, r4, #1
	mov	r3, #0
	strh	r4, [r7, #74]	@ movhi
	strh	r3, [r7, #72]	@ movhi
	mov	r3, #1
	str	r3, [r7, #44]
.L58:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L48:
	ldr	r3, .L70+12
	add	r4, r3, r4
	b	.L47
.L69:
	ldr	r5, [r4, #4]!
.L47:
	strb	r9, [lr, r5]
	add	r0, r0, #1
	ldr	r3, [r8, #3584]
	cmp	r3, r0
	bcs	.L69
	b	.L50
.L71:
	.align	2
.L70:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_IsDeced
	.word	g_TsToRsMap
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroupOfTile, .-PostPro_GetHevcMbGroupOfTile
	.align	2
	.global	PostPro_GetHevcMbGroupOfNoTile
	.type	PostPro_GetHevcMbGroupOfNoTile, %function
PostPro_GetHevcMbGroupOfNoTile:
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
	ldr	r2, .L90
	mov	ip, r3, asl #6
	mov	r9, r0
	sub	ip, ip, r3, asl #3
	mov	r4, #0
	add	r2, r2, ip
	str	r4, [r0, #44]
	ldr	r0, .L90+4
	mov	r8, r1
	ldr	r2, [r2, #8]
	mvn	r6, #0
	ldr	r3, [r9, #28]
	mov	r7, r6
	str	r4, [r9, #56]
	ldr	r5, [r9, #32]
	ldr	r0, [r0, r2, asl #2]
	add	r0, r0, #294912
	mul	r5, r5, r3
	add	r0, r0, #888
	bl	HEVC_CalcTileMap
	ldr	r3, [r8, #12]
	mov	lr, r4
	mov	r2, r8
	add	r0, r5, r6
	str	r0, [fp, #-48]
	add	r1, r8, r3, lsl #2
	uxth	r10, r5
	mov	r3, r1
	strh	r10, [r1, #18]	@ movhi
	strh	r10, [r1, #16]	@ movhi
	b	.L81
.L88:
	cmp	r0, r6
	movlt	r6, r7
	add	r3, r6, #1
	cmp	r0, r3
	ble	.L75
	ldr	r3, [r9, #44]
	cmp	r3, #199
	bgt	.L85
	add	r4, r7, r7, lsr #31
	sub	r1, r6, #100
	add	r6, r9, r3, lsl #2
	add	r3, r3, #1
	sxth	r7, r4
	strh	r4, [r6, #72]	@ movhi
	cmp	r1, r7
	sub	r4, r0, #1
	strgth	r1, [r6, #72]	@ movhi
	strh	r4, [r6, #74]	@ movhi
	str	r3, [r9, #44]
.L75:
	ldr	r3, [r8, #12]
	sub	r1, r3, #1
	cmp	lr, r1
	beq	.L86
.L83:
	add	lr, lr, #1
	mov	r6, ip
	cmp	lr, r3
	mov	r7, r0
	add	r2, r2, #4
	bhi	.L87
.L81:
	ldrh	r0, [r2, #16]
	ldrh	ip, [r2, #18]
	cmp	r0, r5
	cmple	ip, r5
	movgt	r3, #1
	movle	r3, #0
	cmp	r0, ip
	orrgt	r3, r3, #1
	cmp	r3, #0
	beq	.L88
	ldr	r3, [r8, #12]
	add	lr, lr, #1
	add	r2, r2, #4
	cmp	lr, r3
	bls	.L81
.L87:
	mov	r0, #0
.L77:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L86:
	ldrh	r1, [r2, #18]
	ldr	r4, [fp, #-48]
	cmp	r1, r4
	bge	.L83
	ldr	r3, [r9, #44]
	cmp	r3, #199
	bgt	.L89
	add	r2, r9, r3, lsl #2
	sub	r10, r10, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r10, [r2, #74]	@ movhi
	strh	r1, [r2, #72]	@ movhi
	str	r3, [r9, #44]
	b	.L77
.L85:
	ldr	r2, .L90+8
	mov	r0, #1
	ldr	r1, .L90+12
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L89:
	ldr	r2, .L90+8
	mov	r0, #1
	ldr	r1, .L90+16
	bl	dprint_vfmw
	mov	r0, #1
	b	.L77
.L91:
	.align	2
.L90:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC3
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroupOfNoTile, .-PostPro_GetHevcMbGroupOfNoTile
	.align	2
	.global	PostPro_GetHevcMbGroup
	.type	PostPro_GetHevcMbGroup, %function
PostPro_GetHevcMbGroup:
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
	ldr	ip, [r1, #12]
	mov	r4, r0
	sub	lr, ip, #1
	cmp	lr, #199
	bhi	.L97
	ldr	ip, [r0, #68]
	cmp	ip, #0
	bne	.L98
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	PostPro_GetHevcMbGroupOfNoTile
.L98:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	PostPro_GetHevcMbGroupOfTile
.L97:
	mov	r2, ip
	ldr	r1, .L99
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L100:
	.align	2
.L99:
	.word	.LC4
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroup, .-PostPro_GetHevcMbGroup
	.align	2
	.global	PostPro_GetHEVCRepairParam
	.type	PostPro_GetHEVCRepairParam, %function
PostPro_GetHEVCRepairParam:
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
	mov	r4, r1
	ldr	r1, [r1, #1288]
	mov	r6, #1
	mov	r5, r0
	add	r1, r1, #336
	ldr	r1, [r4, r1, asl #2]
	str	r1, [r0, #8]
	ldr	r1, [r4, #2492]
	ldr	r1, [r1, #372]
	add	r1, r1, #336
	ldr	r1, [r4, r1, asl #2]
	str	r1, [r0, #20]
	ldr	r1, [r4, #1292]
	add	r1, r4, r1, lsl #2
	ldr	r1, [r1, #1476]
	str	r1, [r0, #24]
	ldr	r1, [r4, #76]
	mov	ip, r6, asl r1
	str	r1, [r0, #64]
	ldrb	lr, [r4]	@ zero_extendqisi2
	strb	lr, [r0]
	ldr	lr, [r4, #196]
	sub	lr, lr, #1
	add	lr, lr, ip
	mov	lr, lr, lsr r1
	str	lr, [r0, #28]
	ldr	lr, [r4, #192]
	sub	lr, lr, #1
	add	ip, lr, ip
	mov	ip, ip, lsr r1
	str	ip, [r0, #32]
	ldrb	r1, [r4, #225]	@ zero_extendqisi2
	str	r6, [r0, #36]
	str	r1, [r0, #68]
	ldr	r1, [r4, #12]
	clz	r1, r1
	mov	r1, r1, lsr #5
	str	r1, [r0, #40]
	ldr	r1, [r4, #1340]
	cmp	r1, #0
	streq	r1, [r2, #12]
	bne	.L114
.L103:
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L115
.L104:
	mov	r3, #0
	str	r3, [r5, #52]
	ldr	r3, [r4, #1296]
	str	r3, [r5, #12]
	ldr	r3, [r4, #1300]
	str	r3, [r5, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L115:
	ldr	ip, [r4, #1472]
	cmp	ip, #0
	beq	.L104
	ldr	r2, [r4, #1344]
	cmp	r0, r2
	addeq	r1, r4, #1344
	moveq	r3, #0
	bne	.L105
.L107:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L104
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L107
.L105:
	str	r2, [r5, #20]
	b	.L104
.L114:
	mov	r1, r2
	mov	r2, r4
	bl	PostPro_GetHevcMbGroup
	b	.L103
	UNWIND(.fnend)
	.size	PostPro_GetHEVCRepairParam, .-PostPro_GetHEVCRepairParam
	.align	2
	.global	PostPro_GetVp9MbGroup
	.type	PostPro_GetVp9MbGroup, %function
PostPro_GetVp9MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L129
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #18]	@ movhi
	strh	r8, [ip, #16]	@ movhi
	b	.L125
.L133:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L121
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L121
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L130
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #72]	@ movhi
	strh	r6, [r10, #74]	@ movhi
	str	r2, [r0, #44]
.L121:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L131
.L127:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L132
.L125:
	ldrh	ip, [r3, #16]
	ldrh	r4, [r3, #18]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L133
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L125
.L132:
	mov	r3, #0
.L118:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L131:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #18]
	cmp	r6, r9
	bge	.L127
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L134
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #74]	@ movhi
	strh	r6, [r1, #72]	@ movhi
	str	r2, [r0, #44]
	b	.L118
.L129:
	ldr	r1, .L135
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L130:
	movw	r2, #1140
	ldr	r1, .L135+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L118
.L134:
	movw	r2, #1154
	ldr	r1, .L135+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L118
.L136:
	.align	2
.L135:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetVp9MbGroup, .-PostPro_GetVp9MbGroup
	.align	2
	.global	PostPro_GetVP9RepairParam
	.type	PostPro_GetVP9RepairParam, %function
PostPro_GetVP9RepairParam:
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
	add	ip, r1, #270336
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	ldr	r6, [ip, #2440]
	mov	r4, #6
	str	r6, [r0, #8]
	ldr	r2, [ip, #2448]
	str	r2, [r0, #20]
	ldr	r2, [ip, #2456]
	str	r2, [r0, #24]
	ldr	r2, [ip, #2088]
	str	r2, [r0, #28]
	ldr	r2, [ip, #2092]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #2468]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetVp9MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetVP9RepairParam, .-PostPro_GetVP9RepairParam
	.align	2
	.global	PostPro_GetMp24MbGroup
	.type	PostPro_GetMp24MbGroup, %function
PostPro_GetMp24MbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L158
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	str	r3, [r0, #44]
	str	r3, [r0, #56]
	mul	r4, r4, r2
	ldr	r3, [r1, #12]
	cmp	r3, #0
	add	ip, r1, r3, lsl #2
	mov	r2, ip
	uxth	lr, r4
	strh	lr, [ip, #18]	@ movhi
	str	lr, [fp, #-52]
	strh	lr, [r2, #16]	@ movhi
	bne	.L159
.L141:
	mvn	r6, #0
	mov	r3, r1
	add	r2, r4, r6
	mov	r5, r6
	mov	ip, #0
	str	r2, [fp, #-48]
	b	.L150
.L163:
	cmp	r2, lr
	movle	r7, #0
	movgt	r7, #1
	cmp	r2, r5
	orrlt	r7, r7, #1
	cmp	r7, #0
	bne	.L142
	cmp	r2, r6
	movlt	r6, r5
	add	r7, r6, #1
	cmp	r7, r2
	beq	.L146
	add	r5, r5, r5, lsr #31
	sub	r8, r2, #1
	cmp	r5, r8
	bge	.L146
	ldr	r7, [r0, #44]
	cmp	r7, #199
	bgt	.L160
	add	r9, r0, r7, lsl #2
	sxth	r10, r5
	cmp	r6, r10
	add	r7, r7, #1
	strh	r5, [r9, #72]	@ movhi
	strh	r8, [r9, #74]	@ movhi
	strgth	r6, [r9, #72]	@ movhi
	str	r7, [r0, #44]
.L146:
	ldr	r7, [r1, #12]
	sub	r5, r7, #1
	cmp	r5, ip
	beq	.L161
.L152:
	add	ip, ip, #1
	mov	r6, lr
	cmp	ip, r7
	mov	r5, r2
	add	r3, r3, #4
	bhi	.L162
.L150:
	ldrh	r2, [r3, #16]
	ldrh	lr, [r3, #18]
	cmp	r2, r4
	cmple	lr, r4
	ble	.L163
.L142:
	ldr	r7, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r7
	bls	.L150
.L162:
	mov	r3, #0
.L157:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L161:
	add	r5, r1, ip, lsl #2
	ldr	r6, [fp, #-48]
	ldrh	r5, [r5, #18]
	cmp	r5, r6
	bge	.L152
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L164
	add	r1, r0, r3, lsl #2
	ldr	r2, [fp, #-52]
	strh	r5, [r1, #72]	@ movhi
	sub	ip, r2, #1
	add	r2, r3, #1
	strh	ip, [r1, #74]	@ movhi
	mov	r3, #0
	str	r2, [r0, #44]
	b	.L157
.L159:
	sub	r3, r3, #1
	sub	r2, r4, #10
	add	r3, r1, r3, lsl #2
	ldrh	ip, [r3, #18]
	cmp	ip, r2
	subge	r2, lr, #1
	strgeh	r2, [r3, #18]	@ movhi
	b	.L141
.L158:
	ldr	r1, .L165
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L160:
	movw	r2, #1501
	ldr	r1, .L165+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L157
.L164:
	movw	r2, #1532
	ldr	r1, .L165+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L157
.L166:
	.align	2
.L165:
	.word	.LC4
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetMp24MbGroup, .-PostPro_GetMp24MbGroup
	.align	2
	.global	PostPro_GetMPEG2RepairParam
	.type	PostPro_GetMPEG2RepairParam, %function
PostPro_GetMPEG2RepairParam:
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
	mov	r3, r0
	ldr	r0, [r1, #188]
	mov	ip, #0
	str	r0, [r3, #8]
	ldr	r0, [r1, #184]
	str	r0, [r3, #20]
	ldr	r0, [r1, #224]
	str	r0, [r3, #24]
	ldrh	r0, [r1, #150]
	str	r0, [r3, #28]
	ldrh	r0, [r1, #146]
	str	r0, [r3, #32]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	str	ip, [r3, #40]
	sub	r0, r0, #3
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r3, #36]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L171
	cmp	r0, #2
	beq	.L171
	cmp	r0, #3
	streq	ip, [r3, #52]
.L169:
	add	ip, r1, #45056
	mov	r1, r2
	mov	lr, #4
	mov	r0, r3
	ldr	r2, [ip, #240]
	str	lr, [r3, #64]
	strb	r2, [r3]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PostPro_GetMp24MbGroup
.L171:
	str	r0, [r3, #52]
	b	.L169
	UNWIND(.fnend)
	.size	PostPro_GetMPEG2RepairParam, .-PostPro_GetMPEG2RepairParam
	.align	2
	.global	PostPro_GetMPEG4RepairParam
	.type	PostPro_GetMPEG4RepairParam, %function
PostPro_GetMPEG4RepairParam:
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
	ldr	r7, [r1, #212]
	mov	ip, r1
	add	r5, r1, #12288
	mov	r1, r2
	mov	lr, #0
	mov	r6, #1
	str	r7, [r0, #8]
	mov	r4, #4
	ldr	r2, [ip, #220]
	str	r2, [r0, #20]
	ldr	r2, [ip, #228]
	str	r2, [r0, #24]
	ldrh	r2, [ip, #164]
	str	r2, [r0, #28]
	ldrh	r2, [ip, #166]
	str	r6, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [r5, #2372]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetMPEG4RepairParam, .-PostPro_GetMPEG4RepairParam
	.align	2
	.global	PostPro_GetREAL8RepairParam
	.type	PostPro_GetREAL8RepairParam, %function
PostPro_GetREAL8RepairParam:
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
	ldr	r6, [r1, #56]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #52]
	str	r2, [r0, #20]
	ldr	r2, [ip, #68]
	str	r2, [r0, #24]
	ldr	r2, [ip, #4]
	str	r2, [r0, #28]
	ldr	r2, [ip, #8]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #76]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetREAL8RepairParam, .-PostPro_GetREAL8RepairParam
	.align	2
	.global	PostPro_GetREAL9RepairParam
	.type	PostPro_GetREAL9RepairParam, %function
PostPro_GetREAL9RepairParam:
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
	ldr	r6, [r1, #52]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #48]
	str	r2, [r0, #20]
	ldr	r2, [ip, #64]
	str	r2, [r0, #24]
	ldr	r2, [ip, #4]
	str	r2, [r0, #28]
	ldr	r2, [ip, #8]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #72]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetREAL9RepairParam, .-PostPro_GetREAL9RepairParam
	.align	2
	.global	PostPro_GetVc1MbGroup
	.type	PostPro_GetVc1MbGroup, %function
PostPro_GetVc1MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L188
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #18]	@ movhi
	strh	r8, [ip, #16]	@ movhi
	b	.L184
.L192:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L180
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L180
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L189
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #72]	@ movhi
	strh	r6, [r10, #74]	@ movhi
	str	r2, [r0, #44]
.L180:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L190
.L186:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L191
.L184:
	ldrh	ip, [r3, #16]
	ldrh	r4, [r3, #18]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L192
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L184
.L191:
	mov	r3, #0
.L177:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L190:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #18]
	cmp	r6, r9
	bge	.L186
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L193
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #74]	@ movhi
	strh	r6, [r1, #72]	@ movhi
	str	r2, [r0, #44]
	b	.L177
.L188:
	ldr	r1, .L194
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L189:
	movw	r2, #1596
	ldr	r1, .L194+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L177
.L193:
	mov	r2, #1616
	ldr	r1, .L194+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L177
.L195:
	.align	2
.L194:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetVc1MbGroup, .-PostPro_GetVc1MbGroup
	.align	2
	.global	PostPro_GetVC1RepairParam
	.type	PostPro_GetVC1RepairParam, %function
PostPro_GetVC1RepairParam:
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
	add	r6, r1, #12288
	mov	r5, r1
	mov	r7, #0
	mov	r4, r0
	ldr	r3, [r6, #228]
	mov	r1, r2
	str	r3, [r0, #8]
	ldr	r3, [r6, #100]
	str	r3, [r0, #20]
	ldr	r3, [r6, #108]
	str	r3, [r0, #24]
	ldrh	r3, [r5, #78]
	add	r3, r3, #1
	str	r3, [r0, #28]
	ldrh	r3, [r5, #80]
	add	r3, r3, #1
	str	r3, [r0, #32]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	str	r7, [r0, #40]
	tst	r3, #253
	moveq	r3, #1
	movne	r3, r7
	str	r3, [r0, #36]
	bl	PostPro_GetVc1MbGroup
	ldr	r2, [r4, #36]
	ldrb	r3, [r5, #68]	@ zero_extendqisi2
	cmp	r2, #1
	streq	r7, [r4, #52]
	and	r3, r3, #3
	str	r3, [r4, #48]
	beq	.L198
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L200
.L198:
	mov	r3, #4
	str	r3, [r4, #64]
	ldr	r3, [r6, #260]
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L200:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r3, #1
	streq	r3, [r4, #52]
	beq	.L198
	cmp	r3, #1
	moveq	r3, #2
	streq	r3, [r4, #52]
	b	.L198
	UNWIND(.fnend)
	.size	PostPro_GetVC1RepairParam, .-PostPro_GetVC1RepairParam
	.align	2
	.global	PostPro_GetVp6MbGroup
	.type	PostPro_GetVp6MbGroup, %function
PostPro_GetVp6MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L214
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #18]	@ movhi
	strh	r8, [ip, #16]	@ movhi
	b	.L210
.L218:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L206
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L206
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L215
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #72]	@ movhi
	strh	r6, [r10, #74]	@ movhi
	str	r2, [r0, #44]
.L206:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L216
.L212:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L217
.L210:
	ldrh	ip, [r3, #16]
	ldrh	r4, [r3, #18]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L218
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L210
.L217:
	mov	r3, #0
.L203:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L216:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #18]
	cmp	r6, r9
	bge	.L212
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L219
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #74]	@ movhi
	strh	r6, [r1, #72]	@ movhi
	str	r2, [r0, #44]
	b	.L203
.L214:
	ldr	r1, .L220
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L215:
	movw	r2, #1681
	ldr	r1, .L220+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L203
.L219:
	movw	r2, #1701
	ldr	r1, .L220+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L203
.L221:
	.align	2
.L220:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetVp6MbGroup, .-PostPro_GetVp6MbGroup
	.align	2
	.global	PostPro_GetVP6RepairParam
	.type	PostPro_GetVP6RepairParam, %function
PostPro_GetVP6RepairParam:
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
	ldr	r3, [r1, #176]
	mov	r5, r1
	mov	r4, r0
	mov	r6, #0
	mov	r1, r2
	mov	r2, #1
	str	r3, [r0, #8]
	ldr	r3, [r5, #184]
	str	r3, [r0, #20]
	ldr	r3, [r5, #188]
	str	r3, [r0, #24]
	ldrh	r3, [r5, #54]
	str	r3, [r0, #28]
	ldrh	r3, [r5, #56]
	str	r2, [r0, #36]
	str	r6, [r0, #40]
	str	r3, [r0, #32]
	bl	PostPro_GetVp6MbGroup
	str	r6, [r4, #48]
	str	r6, [r4, #52]
	mov	r2, #4
	ldr	r3, [r5, #212]
	str	r2, [r4, #64]
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_GetVP6RepairParam, .-PostPro_GetVP6RepairParam
	.align	2
	.global	PostPro_GetVp8MbGroup
	.type	PostPro_GetVp8MbGroup, %function
PostPro_GetVp8MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L236
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #18]	@ movhi
	strh	r8, [ip, #16]	@ movhi
	b	.L232
.L240:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L228
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L228
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L237
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #72]	@ movhi
	strh	r6, [r10, #74]	@ movhi
	str	r2, [r0, #44]
.L228:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L238
.L234:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L239
.L232:
	ldrh	ip, [r3, #16]
	ldrh	r4, [r3, #18]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L240
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L232
.L239:
	mov	r3, #0
.L225:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L238:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #18]
	cmp	r6, r9
	bge	.L234
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L241
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #74]	@ movhi
	strh	r6, [r1, #72]	@ movhi
	str	r2, [r0, #44]
	b	.L225
.L236:
	ldr	r1, .L242
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L237:
	movw	r2, #1765
	ldr	r1, .L242+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L225
.L241:
	movw	r2, #1785
	ldr	r1, .L242+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L225
.L243:
	.align	2
.L242:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetVp8MbGroup, .-PostPro_GetVp8MbGroup
	.align	2
	.global	PostPro_GetVP8RepairParam
	.type	PostPro_GetVP8RepairParam, %function
PostPro_GetVP8RepairParam:
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
	ldr	r6, [r1, #3120]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #3132]
	str	r2, [r0, #20]
	ldr	r2, [ip, #3136]
	str	r2, [r0, #24]
	ldr	r2, [ip, #2788]
	str	r2, [r0, #28]
	ldr	r2, [ip, #2792]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #3144]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetVp8MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetVP8RepairParam, .-PostPro_GetVP8RepairParam
	.align	2
	.global	PostPro_GetAvsMbGroup
	.type	PostPro_GetAvsMbGroup, %function
PostPro_GetAvsMbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L256
	ldr	lr, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	mvn	r7, #0
	str	r3, [r0, #56]
	mov	ip, r3
	ldr	r2, [r1, #12]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #18]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #16]	@ movhi
	b	.L252
.L259:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L250
	ldr	r7, [r8, #44]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #72]	@ movhi
	strh	r5, [r10, #74]	@ movhi
	ldr	r5, [r8, #36]
	str	r7, [r8, #44]
	cmp	r5, #0
	bne	.L250
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #872
	ldrge	r9, [fp, #-60]
.L250:
	ldr	r5, [r1, #12]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L257
.L254:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L258
.L252:
	ldrh	r2, [r3, #16]
	ldrh	lr, [r3, #18]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L259
	ldr	r5, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L252
.L258:
	mov	r2, #0
.L247:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L257:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #18]
	cmp	r6, r7
	bge	.L254
	ldr	r1, [r0, #44]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #72]	@ movhi
	strh	r3, [r1, #74]	@ movhi
	str	ip, [r0, #44]
	b	.L247
.L256:
	ldr	r1, .L260
	mov	r0, #0
	bl	dprint_vfmw
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L261:
	.align	2
.L260:
	.word	.LC4
	UNWIND(.fnend)
	.size	PostPro_GetAvsMbGroup, .-PostPro_GetAvsMbGroup
	.align	2
	.global	PostPro_GetAVSRepairParam
	.type	PostPro_GetAVSRepairParam, %function
PostPro_GetAVSRepairParam:
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
	add	ip, r1, #12288
	mov	r3, r0
	mov	r6, #0
	ldr	r5, [ip, #2164]
	str	r5, [r0, #8]
	ldr	r10, [ip, #2156]
	str	r10, [r0, #20]
	ldr	r7, [ip, #2168]
	str	r7, [r0, #24]
	ldrh	r8, [r1, #60]
	str	r8, [r0, #28]
	ldrh	r4, [r1, #62]
	str	r4, [r0, #32]
	mov	r9, r4, lsr #1
	ldrb	lr, [r1, #17]	@ zero_extendqisi2
	str	r6, [r0, #40]
	sub	lr, lr, #3
	clz	lr, lr
	mov	lr, lr, lsr #5
	str	lr, [r0, #36]
	ldr	r0, [r2, #4]
	str	r10, [r3, #892]
	add	r5, r0, r5
	str	r5, [r3, #880]
	ldr	r0, [r2, #4]
	str	lr, [r3, #908]
	str	r4, [r3, #904]
	add	r0, r0, r0, lsl #3
	str	r8, [r3, #900]
	str	r6, [r3, #912]
	mla	r0, r9, r0, r7
	str	r0, [r3, #896]
	ldrb	r1, [r1, #17]	@ zero_extendqisi2
	cmp	r1, #3
	streq	r6, [r3, #52]
	beq	.L264
	cmp	r1, #1
	streq	r1, [r3, #52]
.L264:
	ldr	ip, [ip, #2604]
	mov	r1, r2
	mov	r0, r3
	mov	r2, #4
	str	r2, [r3, #64]
	strb	ip, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_GetAvsMbGroup
	UNWIND(.fnend)
	.size	PostPro_GetAVSRepairParam, .-PostPro_GetAVSRepairParam
	.align	2
	.global	PostPro_GetAvs2MbGroup
	.type	PostPro_GetAvs2MbGroup, %function
PostPro_GetAvs2MbGroup:
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
	ldr	r2, [r1, #12]
	mov	r8, r0
	cmp	r2, #200
	bhi	.L279
	cmp	r2, #0
	beq	.L280
	ldr	r3, [r0, #28]
	mov	lr, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	lr, [r0, #56]
	mov	r7, r6
	ldr	r2, [r1, #12]
	mul	r5, r5, r3
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	mov	r2, ip
	uxth	r0, r5
	strh	r0, [ip, #18]	@ movhi
	strh	r0, [ip, #16]	@ movhi
	b	.L275
.L284:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L271
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L271
	ldr	r2, [r8, #44]
	cmp	r2, #199
	bgt	.L281
	add	r10, r8, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #72]	@ movhi
	strh	r6, [r10, #74]	@ movhi
	str	r2, [r8, #44]
.L271:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L282
.L277:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L283
.L275:
	ldrh	ip, [r3, #16]
	ldrh	r4, [r3, #18]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L284
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L275
.L283:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L280:
	mov	r3, #1
	mov	r0, r2
	str	r3, [r8, #56]
	str	r3, [r8, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L282:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #18]
	cmp	r6, r9
	bge	.L277
	ldr	r2, [r8, #44]
	cmp	r2, #199
	bgt	.L285
	add	r1, r8, r2, lsl #2
	sub	r3, r0, #1
	add	r2, r2, #1
	mov	r0, #0
	strh	r3, [r1, #74]	@ movhi
	strh	r6, [r1, #72]	@ movhi
	str	r2, [r8, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L279:
	ldr	r1, .L286
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L281:
	movw	r2, #1933
	ldr	r1, .L286+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L285:
	movw	r2, #1947
	ldr	r1, .L286+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L287:
	.align	2
.L286:
	.word	.LC4
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetAvs2MbGroup, .-PostPro_GetAvs2MbGroup
	.align	2
	.global	PostPro_GetDivx3MbGroup
	.type	PostPro_GetDivx3MbGroup, %function
PostPro_GetDivx3MbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #3
	bhi	.L299
	ldr	lr, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	mvn	r7, #0
	str	r3, [r0, #56]
	mov	ip, r3
	ldr	r2, [r1, #12]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #18]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #16]	@ movhi
	b	.L295
.L302:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L293
	ldr	r7, [r8, #44]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #72]	@ movhi
	strh	r5, [r10, #74]	@ movhi
	ldr	r5, [r8, #36]
	str	r7, [r8, #44]
	cmp	r5, #0
	bne	.L293
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #872
	ldrge	r9, [fp, #-60]
.L293:
	ldr	r5, [r1, #12]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L300
.L297:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L301
.L295:
	ldrh	r2, [r3, #16]
	ldrh	lr, [r3, #18]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L302
	ldr	r5, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L295
.L301:
	mov	r2, #0
.L290:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L300:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #18]
	cmp	r6, r7
	bge	.L297
	ldr	r1, [r0, #44]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #72]	@ movhi
	strh	r3, [r1, #74]	@ movhi
	str	ip, [r0, #44]
	b	.L290
.L299:
	ldr	r1, .L303
	mov	r0, #0
	bl	dprint_vfmw
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L304:
	.align	2
.L303:
	.word	.LC4
	UNWIND(.fnend)
	.size	PostPro_GetDivx3MbGroup, .-PostPro_GetDivx3MbGroup
	.align	2
	.global	PostPro_GetDIVX3RepairParam
	.type	PostPro_GetDIVX3RepairParam, %function
PostPro_GetDIVX3RepairParam:
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
	ldr	r6, [r1, #128]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #124]
	str	r2, [r0, #20]
	ldr	r2, [ip, #152]
	str	r2, [r0, #24]
	ldr	r2, [ip, #8]
	str	r2, [r0, #28]
	ldr	r2, [ip, #12]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #160]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetDivx3MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetDIVX3RepairParam, .-PostPro_GetDIVX3RepairParam
	.align	2
	.global	PostPro_BubbleSort
	.type	PostPro_BubbleSort, %function
PostPro_BubbleSort:
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
	ldr	r8, [r0, #12]
	cmp	r8, #1
	bls	.L318
	mov	r7, #1
.L311:
	mov	r4, #0
	rsb	lr, r7, r8
	mov	r2, r4
	mov	r3, r0
	b	.L312
.L310:
	ldrh	r1, [r3, #16]
	ldrh	ip, [r3, #20]
	cmp	r1, ip
	bls	.L309
	ldrh	r6, [r3, #18]
	mov	r4, #1
	ldrh	r5, [r3, #22]
	strh	ip, [r3, #16]	@ movhi
	strh	r1, [r3, #20]	@ movhi
	strh	r6, [r3, #22]	@ movhi
	strh	r5, [r3, #18]	@ movhi
.L309:
	add	r3, r3, #4
.L312:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L310
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r7, r7, #1
	cmp	r8, r7
	movls	r4, #0
	andhi	r4, r4, #1
	cmp	r4, #0
	bne	.L311
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L318:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_BubbleSort, .-PostPro_BubbleSort
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	PostPro_GetH264MbOfMBAFF
	.type	PostPro_GetH264MbOfMBAFF, %function
PostPro_GetH264MbOfMBAFF:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 832
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #836)
	sub	sp, sp, #836
	ldr	r3, [r1, #12]
	ldr	r2, [r0, #28]
	mov	r9, r1
	cmp	r3, #0
	mov	r10, r0
	mov	r4, r3
	str	r3, [fp, #-856]
	ldr	r3, [r0, #32]
	mov	r6, r2, asl #1
	str	r2, [fp, #-868]
	str	r3, [fp, #-872]
	beq	.L332
	sub	lr, fp, #844
	mov	r3, r1
	add	r1, lr, #2
	mov	r2, #0
.L321:
	ldrh	ip, [r3, #16]
	add	r2, r2, #1
	ldrh	r0, [r3, #18]
	cmp	r2, r4
	add	r3, r3, #4
	strh	ip, [r1, #-2]	@ movhi
	strh	r0, [r1], #4	@ movhi
	bne	.L321
	ldrh	r8, [lr]
	cmp	r6, #0
	ldrh	r3, [lr, #2]
	bic	r8, r8, #1
	orr	r3, r3, #1
	str	r3, [fp, #-848]
	uxth	r8, r8
	strh	r3, [lr, #2]	@ movhi
	strh	r8, [lr]	@ movhi
	beq	.L333
	mov	r5, #0
	sub	r3, r6, #2
	mov	r7, r5
	str	r3, [fp, #-852]
	str	lr, [fp, #-876]
	uxth	r3, r6
	str	r3, [fp, #-864]
.L329:
	mov	r1, r6
	mov	r0, r8
	bl	__aeabi_uidivmod
	ldr	r0, [fp, #-848]
	mov	r4, r1
	cmp	r4, #1
	mov	r1, r6
	bls	.L323
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #-852]
	cmp	r3, r1
	bls	.L324
	str	r1, [fp, #-860]
	mov	r0, r8
	mov	r1, r6
	mov	r4, r4, lsr #1
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r8, r0
	ldr	r0, [fp, #-848]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-860]
	mov	r2, r2, lsr #1
	cmp	r0, r8
	mov	r3, r0
	beq	.L325
	ldr	r1, [fp, #-864]
	add	ip, r5, #1
	cmp	ip, #199
	smulbb	r0, r8, r1
	add	r1, r9, r5, lsl #2
	uxth	r0, r0
	add	r4, r0, r4
	uxth	r4, r4
	strh	r4, [r1, #16]	@ movhi
	ldr	lr, [r10, #28]
	sub	lr, lr, #1
	add	r0, r0, lr
	strh	r0, [r1, #18]	@ movhi
	bhi	.L326
	ldr	r0, [fp, #-864]
	add	lr, r5, #2
	add	ip, r9, ip, lsl #2
	cmp	lr, #199
	uxth	r2, r2
	smulbb	r3, r3, r0
	ldr	r0, [r10, #28]
	add	r4, r4, r0
	strh	r4, [r1, #20]	@ movhi
	uxth	r3, r3
	add	r0, r2, r3
	strh	r0, [ip, #18]	@ movhi
	bhi	.L326
	ldr	r0, [r10, #28]
	add	r5, r5, #3
	add	lr, r9, lr, lsl #2
	cmp	r5, #199
	add	r3, r3, r0
	uxth	r3, r3
	strh	r3, [r1, #24]	@ movhi
	add	r2, r3, r2
	strh	r2, [lr, #18]	@ movhi
	bhi	.L326
.L327:
	ldr	r3, [fp, #-856]
	add	r7, r7, #1
	cmp	r7, r3
	beq	.L322
.L330:
	ldr	r2, [fp, #-876]
	ldrh	r3, [r2, #6]
	ldrh	r8, [r2, #4]
	orr	r3, r3, #1
	str	r3, [fp, #-848]
	bic	r8, r8, #1
	strh	r8, [r2, #4]	@ movhi
	mov	r1, r3
	mov	r3, r2
	strh	r1, [r3, #6]	@ movhi
	add	r3, r3, #4
	str	r3, [fp, #-876]
	b	.L329
.L324:
	mov	r1, r6
	mov	r0, r8
	bl	__aeabi_uidiv
	add	r2, r9, r5, lsl #2
	add	r3, r5, #1
	cmp	r3, #199
	smulbb	r0, r0, r6
	uxth	r0, r0
	add	r4, r0, r4, lsr #1
	uxth	r4, r4
	strh	r4, [r2, #16]	@ movhi
	ldr	r1, [r10, #28]
	sub	r1, r1, #1
	add	r0, r0, r1
	strh	r0, [r2, #18]	@ movhi
	bhi	.L326
	ldr	r1, [r10, #28]
	add	r5, r5, #2
	add	r3, r9, r3, lsl #2
	cmp	r5, #199
	add	r4, r4, r1
	strh	r4, [r2, #20]	@ movhi
	ldr	r2, [fp, #-848]
	strh	r2, [r3, #18]	@ movhi
	bls	.L327
.L326:
	ldr	r2, [fp, #-868]
	mov	r1, #1
	ldr	r3, [fp, #-872]
	mov	r0, r9
	str	r1, [r9, #12]
	mul	r3, r3, r2
	mov	r2, #0
	strh	r2, [r9, #16]	@ movhi
	sub	r3, r3, #1
	strh	r3, [r9, #18]	@ movhi
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_BubbleSort
.L323:
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-852]
	cmp	r2, r1
	bls	.L328
	add	r4, r9, r5, lsl #2
	str	r1, [fp, #-860]
	ldr	r0, [fp, #-848]
	mov	r1, r6
	strh	r8, [r4, #16]	@ movhi
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-860]
	add	r1, r5, #1
	cmp	r1, #199
	ubfx	r2, r3, #1, #16
	smulbb	r0, r0, r6
	uxth	r0, r0
	add	r3, r2, r0
	strh	r3, [r4, #18]	@ movhi
	bhi	.L326
	ldr	r3, [r10, #28]
	add	r5, r5, #2
	add	r1, r9, r1, lsl #2
	cmp	r5, #199
	add	r0, r0, r3
	uxth	r3, r0
	strh	r3, [r4, #20]	@ movhi
	add	r3, r3, r2
	strh	r3, [r1, #18]	@ movhi
	bhi	.L326
	ldr	r3, [fp, #-856]
	add	r7, r7, #1
	cmp	r7, r3
	bne	.L330
.L322:
	str	r5, [r9, #12]
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_BubbleSort
.L328:
	add	r2, r9, r5, lsl #2
	add	r5, r5, #1
	cmp	r5, #199
	mov	r3, r2
	strh	r8, [r2, #16]	@ movhi
	ldr	r2, [fp, #-848]
	strh	r2, [r3, #18]	@ movhi
	bls	.L327
	b	.L326
.L325:
	smulbb	r3, r0, r6
	add	r1, r5, #1
	add	ip, r9, r5, lsl #2
	cmp	r1, #199
	uxth	r3, r3
	add	r4, r3, r4
	add	r2, r3, r2
	uxth	r4, r4
	uxth	r2, r2
	strh	r4, [ip, #16]	@ movhi
	strh	r2, [ip, #18]	@ movhi
	bhi	.L326
	ldr	r3, [r10, #28]
	add	r5, r5, #2
	add	r1, r9, r1, lsl #2
	cmp	r5, #199
	add	r4, r4, r3
	strh	r4, [ip, #20]	@ movhi
	ldr	r3, [r10, #28]
	add	r2, r2, r3
	strh	r2, [r1, #18]	@ movhi
	bls	.L327
	b	.L326
.L332:
	ldr	r5, [fp, #-856]
	b	.L322
.L333:
	mov	r5, r6
	b	.L322
	UNWIND(.fnend)
	.size	PostPro_GetH264MbOfMBAFF, .-PostPro_GetH264MbOfMBAFF
	.align	2
	.global	PostPro_GetH264MbGroup
	.type	PostPro_GetH264MbGroup, %function
PostPro_GetH264MbGroup:
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
	ldr	r3, [r1, #12]
	mov	r7, r1
	mov	r8, r0
	sub	ip, r3, #1
	cmp	ip, #199
	bhi	.L359
	ldr	r3, [r0, #28]
	cmp	r2, #0
	ldr	r4, [r0, #32]
	mul	r4, r4, r3
	bne	.L360
.L344:
	mov	ip, #0
	str	ip, [r8, #44]
	str	ip, [r8, #56]
	mvn	r5, #0
	ldr	r2, [r7, #12]
	add	r3, r4, r5
	uxth	r10, r4
	str	r3, [fp, #-48]
	mov	r6, r5
	mov	r3, r7
	add	r1, r7, r2, lsl #2
	strh	r10, [r1, #18]	@ movhi
	strh	r10, [r1, #16]	@ movhi
	b	.L352
.L364:
	cmp	r2, r5
	movlt	r5, r6
	add	r0, r5, #1
	cmp	r2, r0
	ble	.L347
	ldr	r9, [r8, #44]
	cmp	r9, #199
	bgt	.L361
	add	lr, r6, r6, lsr #31
	sub	r0, r5, #100
	add	r5, r8, r9, lsl #2
	add	r9, r9, #1
	sxth	r6, lr
	strh	lr, [r5, #72]	@ movhi
	cmp	r0, r6
	sub	lr, r2, #1
	strgth	r0, [r5, #72]	@ movhi
	strh	lr, [r5, #74]	@ movhi
	str	r9, [r8, #44]
.L347:
	ldr	r0, [r7, #12]
	sub	lr, r0, #1
	cmp	lr, ip
	beq	.L362
.L354:
	add	ip, ip, #1
	mov	r5, r1
	cmp	ip, r0
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L363
.L352:
	ldrh	r2, [r3, #16]
	ldrh	r1, [r3, #18]
	cmp	r2, r4
	cmple	r1, r4
	movgt	r9, #1
	movle	r9, #0
	cmp	r2, r1
	orrgt	r9, r9, #1
	cmp	r9, #0
	beq	.L364
	ldr	r0, [r7, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r0
	bls	.L352
.L363:
	mov	r0, #0
.L343:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L362:
	add	lr, r7, ip, lsl #2
	ldrh	r5, [lr, #18]
	ldr	lr, [fp, #-48]
	cmp	r5, lr
	bge	.L354
	ldr	r3, [r8, #44]
	cmp	r3, #199
	bgt	.L365
	add	r2, r8, r3, lsl #2
	sub	r10, r10, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r10, [r2, #74]	@ movhi
	strh	r5, [r2, #72]	@ movhi
	str	r3, [r8, #44]
	b	.L343
.L360:
	bl	PostPro_GetH264MbOfMBAFF
	b	.L344
.L359:
	mov	r2, r3
	ldr	r1, .L366
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L361:
	movw	r2, #1396
	ldr	r1, .L366+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	b	.L343
.L365:
	mov	r2, #1424
	ldr	r1, .L366+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	b	.L343
.L367:
	.align	2
.L366:
	.word	.LC4
	.word	.LC6
	UNWIND(.fnend)
	.size	PostPro_GetH264MbGroup, .-PostPro_GetH264MbGroup
	.align	2
	.global	PostPro_GetH264RepairParam
	.type	PostPro_GetH264RepairParam, %function
PostPro_GetH264RepairParam:
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
	ldr	r3, [r1, #308]
	mov	r4, r1
	mov	r5, r0
	mov	r1, r2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #8]
	ldr	r3, [r4, #944]
	ldr	r0, [r3, #1640]
	add	r3, r4, r0, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r5, #20]
	ldr	r3, [r4, #316]
	add	r3, r3, #146
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r5, #24]
	ldr	r3, [r4, #44]
	str	r3, [r5, #28]
	ldr	r3, [r4, #36]
	str	r3, [r5, #32]
	ldrb	r3, [r4]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r5, #36]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r5, #40]
	ldr	r6, [r4, #936]
	cmp	r6, #0
	beq	.L369
	ldr	r3, [r4, #1116]
	cmp	r3, r0
	addne	ip, r4, #1104
	movne	r3, #0
	addne	ip, ip, #12
	bne	.L372
	b	.L406
.L373:
	ldr	lr, [ip, #4]!
	cmp	lr, r0
	beq	.L370
.L372:
	add	r3, r3, #1
	cmp	r3, r6
	bne	.L373
.L369:
	ldr	r2, [r4, #48]
	ldrsb	r3, [r4, #2]
	cmp	r2, #0
	ldrneb	r2, [r4]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r1, #12]
	bne	.L407
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L408
.L377:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L386
	cmp	r3, #1
	beq	.L404
	cmp	r3, #2
	beq	.L404
	cmp	r3, #3
	bne	.L383
.L386:
	mov	r3, #0
	str	r3, [r5, #52]
.L383:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	mov	r2, #4
	str	r2, [r5, #64]
	strb	r3, [r5]
	ldr	r3, [r4, #720]
	str	r3, [r5, #12]
	ldr	r3, [r4, #724]
	str	r3, [r5, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L404:
	str	r3, [r5, #52]
	b	.L383
.L406:
	mov	r3, #0
.L370:
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1052]
	str	r3, [r5, #48]
	b	.L369
.L407:
	mov	r0, r5
	bl	PostPro_GetH264MbGroup
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	bne	.L377
.L408:
	ldr	ip, [r4, #580]
	cmp	ip, #0
	beq	.L377
	ldr	r2, [r4, #324]
	cmp	r0, r2
	addeq	r1, r4, #324
	moveq	r3, #0
	bne	.L378
.L380:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L377
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L380
.L378:
	str	r2, [r5, #20]
	b	.L377
	UNWIND(.fnend)
	.size	PostPro_GetH264RepairParam, .-PostPro_GetH264RepairParam
	.align	2
	.global	PostPro_GetMVCRepairParam
	.type	PostPro_GetMVCRepairParam, %function
PostPro_GetMVCRepairParam:
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
	ldr	r3, [r1, #308]
	mov	r4, r1
	mov	r5, r0
	mov	r1, r2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #8]
	ldr	r3, [r4, #944]
	ldr	r0, [r3, #1640]
	add	r3, r4, r0, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r5, #20]
	ldr	r3, [r4, #316]
	add	r3, r3, #146
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r5, #24]
	ldr	r3, [r4, #44]
	str	r3, [r5, #28]
	ldr	r3, [r4, #36]
	str	r3, [r5, #32]
	ldrb	r3, [r4]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r5, #36]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r5, #40]
	ldr	r6, [r4, #936]
	cmp	r6, #0
	beq	.L410
	ldr	r3, [r4, #1116]
	cmp	r3, r0
	addne	ip, r4, #1104
	movne	r3, #0
	addne	ip, ip, #12
	bne	.L413
	b	.L447
.L414:
	ldr	lr, [ip, #4]!
	cmp	lr, r0
	beq	.L411
.L413:
	add	r3, r3, #1
	cmp	r3, r6
	bne	.L414
.L410:
	ldr	r2, [r4, #48]
	ldrsb	r3, [r4, #2]
	cmp	r2, #0
	ldrneb	r2, [r4]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r1, #12]
	bne	.L448
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L449
.L418:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L427
	cmp	r3, #1
	beq	.L445
	cmp	r3, #2
	beq	.L445
	cmp	r3, #3
	bne	.L424
.L427:
	mov	r3, #0
	str	r3, [r5, #52]
.L424:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	mov	r2, #4
	str	r2, [r5, #64]
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L445:
	str	r3, [r5, #52]
	b	.L424
.L447:
	mov	r3, #0
.L411:
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1052]
	str	r3, [r5, #48]
	b	.L410
.L448:
	mov	r0, r5
	bl	PostPro_GetH264MbGroup
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	bne	.L418
.L449:
	ldr	ip, [r4, #580]
	cmp	ip, #0
	beq	.L418
	ldr	r2, [r4, #324]
	cmp	r0, r2
	addeq	r1, r4, #324
	moveq	r3, #0
	bne	.L419
.L421:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L418
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L421
.L419:
	str	r2, [r5, #20]
	b	.L418
	UNWIND(.fnend)
	.size	PostPro_GetMVCRepairParam, .-PostPro_GetMVCRepairParam
	.align	2
	.global	PostPro_GetRepairParam
	.type	PostPro_GetRepairParam, %function
PostPro_GetRepairParam:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r3
	mov	r4, r1
	mov	r3, #0
	str	r0, [r1, #4]
	str	r3, [r1, #44]
	str	r3, [r1, #916]
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L451
.L453:
	.word	.L452
	.word	.L454
	.word	.L455
	.word	.L456
	.word	.L451
	.word	.L457
	.word	.L458
	.word	.L451
	.word	.L459
	.word	.L460
	.word	.L461
	.word	.L461
	.word	.L461
	.word	.L462
	.word	.L451
	.word	.L463
	.word	.L464
	.word	.L465
.L465:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetVP9RepairParam
.L466:
	ldr	r8, [r4, #44]
	ldr	r3, [r4, #28]
	ldr	r6, [r4, #32]
	cmp	r8, #0
	mul	r6, r6, r3
	beq	.L467
	mov	r8, #0
	mov	r5, r4
	mov	r9, r8
.L468:
	ldrsh	r3, [r5, #72]
	mov	r0, #22
	ldrsh	r2, [r5, #74]
	add	r9, r9, #1
	ldr	r1, .L479
	add	r5, r5, #4
	bl	dprint_vfmw
	ldrsh	r3, [r5, #70]
	ldrsh	r2, [r5, #68]
	ldr	r1, [r4, #44]
	rsb	r3, r2, r3
	cmp	r1, r9
	add	r3, r3, #1
	add	r8, r8, r3
	bhi	.L468
.L467:
	ldr	r1, [r4, #916]
	cmp	r1, #0
	beq	.L469
	add	r0, r4, #944
	mov	r2, #0
	add	r0, r0, #2
.L470:
	ldrsh	r3, [r0]
	add	r2, r2, #1
	ldrsh	ip, [r0, #-2]
	cmp	r2, r1
	add	r0, r0, #4
	rsb	ip, ip, r3
	add	ip, ip, #1
	add	r8, r8, ip
	bne	.L470
.L469:
	cmp	r6, #0
	moveq	r4, r6
	beq	.L471
	mov	r0, #100
	mov	r1, r6
	mul	r0, r0, r8
	bl	__aeabi_uidiv
	cmp	r0, #100
	movcc	r4, r0
	movcs	r4, #100
.L471:
	mov	ip, #0
	mov	r3, r8
	mov	r2, r6
	ldr	r1, .L479+4
	str	ip, [r7, #12]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L452:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetH264RepairParam
	b	.L466
.L454:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetVC1RepairParam
	b	.L466
.L455:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetMPEG4RepairParam
	b	.L466
.L456:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetMPEG2RepairParam
	b	.L466
.L457:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetDIVX3RepairParam
	b	.L466
.L458:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetAVSRepairParam
	b	.L466
.L459:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetREAL8RepairParam
	b	.L466
.L460:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetREAL9RepairParam
	b	.L466
.L461:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetVP6RepairParam
	b	.L466
.L462:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetVP8RepairParam
	b	.L466
.L463:
	mov	r1, r2
	mov	r0, r4
	mov	r2, r7
	bl	PostPro_GetMVCRepairParam
	b	.L466
.L464:
	mov	r1, r2
	ldr	r3, [fp, #4]
	mov	r2, r7
	mov	r0, r4
	bl	PostPro_GetHEVCRepairParam
	b	.L466
.L451:
	mov	r3, #860
	ldr	r2, .L479+8
	ldr	r1, .L479+12
	mov	r0, #0
	bl	dprint_vfmw
	b	.L466
.L480:
	.align	2
.L479:
	.word	.LC8
	.word	.LC9
	.word	.LANCHOR0+32
	.word	.LC7
	UNWIND(.fnend)
	.size	PostPro_GetRepairParam, .-PostPro_GetRepairParam
	.align	2
	.global	PostPro_GetErrRatio
	.type	PostPro_GetErrRatio, %function
PostPro_GetErrRatio:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r3, r0, #0
	beq	.L486
	ldr	ip, .L487
	mov	r2, #12
	ldr	r5, [r3]
	mov	r1, #0
	ldr	r4, .L487+4
	sub	r0, fp, #48
	ldr	ip, [ip, #48]
	ldr	r7, [r3, #4]
	ldr	r8, [r3, #8]
	blx	ip
	mov	r3, #820
	ldr	r1, .L487+8
	mla	r4, r3, r5, r4
	ldr	r6, .L487+12
	ldr	r3, [r1, #140]
	mov	r2, #1744
	str	r7, [fp, #-48]
	cmp	r3, #0
	str	r5, [fp, #-40]
	mla	r6, r2, r5, r6
	str	r4, [fp, #-44]
	beq	.L484
	sub	r0, fp, #48
	blx	r3
.L485:
	mov	r3, r4
	mov	r2, r8
	mov	r1, r6
	str	r5, [sp]
	mov	r0, r7
	bl	PostPro_GetRepairParam
	ldr	r1, .L487+16
	mov	r4, r0
	mov	r2, r0
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L484:
	mov	r0, r3
	mov	r2, #98
	ldr	r1, .L487+20
	bl	dprint_vfmw
	b	.L485
.L486:
	ldr	r1, .L487+24
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L488:
	.align	2
.L487:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_DecReport
	.word	g_vdm_hal_fun_ptr
	.word	g_RepairParam
	.word	.LC12
	.word	.LC11
	.word	.LC10
	UNWIND(.fnend)
	.size	PostPro_GetErrRatio, .-PostPro_GetErrRatio
	.align	2
	.global	PostPro_SetFullRepair
	.type	PostPro_SetFullRepair, %function
PostPro_SetFullRepair:
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
	mov	ip, #820
	mul	ip, ip, r2
	ldr	r4, .L490
	ldr	r8, .L490+4
	mov	lr, r2
	mov	r9, #1744
	str	r2, [sp]
	add	r3, r4, ip
	mov	r2, r1
	mov	r6, #0
	mov	r7, #1
	mla	r1, r9, lr, r8
	str	r6, [r3, #12]
	str	r7, [r4, ip]
	bl	PostPro_GetRepairParam
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L491:
	.align	2
.L490:
	.word	g_DecReport
	.word	g_RepairParam
	UNWIND(.fnend)
	.size	PostPro_SetFullRepair, .-PostPro_SetFullRepair
	.align	2
	.global	PostPro_SetDecReport
	.type	PostPro_SetDecReport, %function
PostPro_SetDecReport:
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
	ldr	r3, .L511
	mov	r5, r0
	mov	r4, r2
	mov	r6, r1
	mov	r0, r2
	mov	r1, #0
	mov	r2, #820
	ldr	r3, [r3, #48]
	blx	r3
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L493
.L495:
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L493
	.word	.L504
	.word	.L500
	.word	.L493
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L504
	.word	.L493
	.word	.L504
	.word	.L504
	.word	.L504
.L500:
	ldrb	r3, [r6, #17]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L510
.L504:
	mov	r3, #0
	mov	r2, #1
	strh	r3, [r4, #16]	@ movhi
	str	r2, [r4, #12]
	strh	r3, [r4, #18]	@ movhi
.L508:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L493:
	movw	r3, #2274
	ldr	r2, .L511+4
	ldr	r1, .L511+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L508
.L510:
	mov	r3, #0
	mov	r2, #2
	strh	r3, [r4, #16]	@ movhi
	str	r2, [r4, #12]
	strh	r3, [r4, #18]	@ movhi
	ldrh	r2, [r6, #60]
	ldrh	r3, [r6, #62]
	mul	r3, r3, r2
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	strh	r3, [r4, #20]	@ movhi
	ldrh	r2, [r6, #60]
	ldrh	r3, [r6, #62]
	mul	r3, r3, r2
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	strh	r3, [r4, #22]	@ movhi
	b	.L508
.L512:
	.align	2
.L511:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+56
	.word	.LC7
	UNWIND(.fnend)
	.size	PostPro_SetDecReport, .-PostPro_SetDecReport
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14314, %object
	.size	__func__.14314, 31
__func__.14314:
	.ascii	"PostPro_GetHevcMbGroupOfNoTile\000"
	.space	1
	.type	__func__.14257, %object
	.size	__func__.14257, 23
__func__.14257:
	.ascii	"PostPro_GetRepairParam\000"
	.space	1
	.type	__func__.14534, %object
	.size	__func__.14534, 21
__func__.14534:
	.ascii	"PostPro_SetDecReport\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeig" )
	ASCII(.ascii	"ht=%d\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM " )
	ASCII(.ascii	"- 1)\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"DecSliceNum(=%d) out of range!\012\000" )
.LC5:
	ASCII(.ascii	"DecSliceNum out of range!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"%s %d VidStd Err!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0" )
	ASCII(.ascii	"].MbGroup[i].StartMbn=%d\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"total_mbs=%d,err_mbs=%d\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"PostPro_GetErrRatio: pParam = NULL\012\000" )
.LC11:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"err_ratio=%d\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
