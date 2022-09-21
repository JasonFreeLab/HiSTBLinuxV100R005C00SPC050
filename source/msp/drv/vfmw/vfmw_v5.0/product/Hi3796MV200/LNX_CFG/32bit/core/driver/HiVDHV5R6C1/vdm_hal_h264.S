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
	.file	"vdm_hal_h264.c"
	.text
	.align	2
	.global	Write_V5R6C1_CabacTab
	.type	Write_V5R6C1_CabacTab, %function
Write_V5R6C1_CabacTab:
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
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L5
	ldr	r3, .L6
	mov	r2, #5120
	ldr	r1, .L6+4
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r2, #114
	ldr	r1, .L6+8
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC0
	UNWIND(.fnend)
	.size	Write_V5R6C1_CabacTab, .-Write_V5R6C1_CabacTab
	.align	2
	.global	H264HAL_V5R6C1_InitHal
	.type	H264HAL_V5R6C1_InitHal, %function
H264HAL_V5R6C1_InitHal:
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
	ldr	r0, [r0, #1088]
	bl	Write_V5R6C1_CabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r1, .L13
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L14:
	.align	2
.L13:
	.word	.LC1
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_InitHal, .-H264HAL_V5R6C1_InitHal
	.align	2
	.global	Get_V5R6C1_VirAddr
	.type	Get_V5R6C1_VirAddr, %function
Get_V5R6C1_VirAddr:
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
	.size	Get_V5R6C1_VirAddr, .-Get_V5R6C1_VirAddr
	.align	2
	.global	Get_V5R6C1_PhyAddr
	.type	Get_V5R6C1_PhyAddr, %function
Get_V5R6C1_PhyAddr:
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
	.size	Get_V5R6C1_PhyAddr, .-Get_V5R6C1_PhyAddr
	.align	2
	.global	H264HAL_V5R6C1_CutSliceChain
	.type	H264HAL_V5R6C1_CutSliceChain, %function
H264HAL_V5R6C1_CutSliceChain:
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
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L20
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {fp, sp, pc}
.L20:
	ldr	r3, .L21
	ldr	r2, .L21+4
	ldr	r1, .L21+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L22:
	.align	2
.L21:
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC3
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_CutSliceChain, .-H264HAL_V5R6C1_CutSliceChain
	.align	2
	.global	Write_V5R6C1_Qmatrix
	.type	Write_V5R6C1_Qmatrix, %function
Write_V5R6C1_Qmatrix:
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
	subs	r9, r1, #0
	mov	r8, r0
	mov	r10, r2
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	sub	r6, r3, #4
	sub	r7, r0, #4
	mov	r4, #0
.L25:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L28
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	bl	dprint_vfmw
	ldr	r3, [r6]
	rsb	r2, r8, r5
	ldr	r1, .L28+4
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, r9
	bne	.L25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L29:
	.align	2
.L28:
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	Write_V5R6C1_Qmatrix, .-Write_V5R6C1_Qmatrix
	.align	2
	.global	H264HAL_SetSliceMsgStreamAddrInfo
	.type	H264HAL_SetSliceMsgStreamAddrInfo, %function
H264HAL_SetSliceMsgStreamAddrInfo:
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
	add	r9, r1, #4
	add	r7, r3, #4
	add	r5, r2, #4
	mov	r6, r2
	mov	r4, #0
	str	r0, [fp, #-52]
.L33:
	ldr	r8, [r9, #4]!
	sub	r3, r7, #4
	mov	r2, r4
	ldr	r1, .L35
	cmp	r8, #0
	mov	r0, #4
	add	ip, r4, #1
	beq	.L31
	ldr	r8, [r9, #16]
	mov	r2, ip
	ldr	r3, [r9, #8]
	ldr	r1, [fp, #-52]
	add	r10, r3, r8, lsl #3
	str	ip, [fp, #-56]
	and	r10, r10, #127
	ldr	lr, [r1, #736]
	str	r8, [sp, #4]
	bic	r8, r8, #15
	str	r3, [sp]
	bic	r3, lr, #15
	ldr	r1, .L35+4
	str	r3, [fp, #-48]
	mov	r3, r10
	bl	dprint_vfmw
	str	r10, [r5]
	ldr	ip, [fp, #-56]
	mov	r3, r7
	ldr	lr, [r6, #4]
	mov	r0, #4
	ldr	r1, .L35
	mov	r2, ip
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	ip, [r9]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L35
	mov	r0, #4
	str	ip, [r5, #4]
	ldr	ip, [r5, #4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	mov	r2, r4
	ldr	r1, .L35
	rsb	r8, r3, r8
	str	r8, [r6]
	ldr	ip, [r5, #-4]
	sub	r3, r7, #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
.L32:
	add	r4, r4, #3
	add	r5, r5, #12
	cmp	r4, #6
	add	r6, r6, #12
	add	r7, r7, #12
	bne	.L33
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L31:
	str	r8, [r6]
	ldr	ip, [r5, #-4]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5]
	ldr	ip, [r6, #4]
	mov	r3, r7
	add	r2, r4, #1
	ldr	r1, .L35
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5, #4]
	ldr	ip, [r5, #4]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L35
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L32
.L36:
	.align	2
.L35:
	.word	.LC7
	.word	.LC6
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.align	2
	.global	H264HAL_SetSliceMsgMvAddrInfo
	.type	H264HAL_SetSliceMsgMvAddrInfo, %function
H264HAL_SetSliceMsgMvAddrInfo:
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
	ldrb	r1, [r1]	@ zero_extendqisi2
	ldr	ip, .L50
	mov	r5, r3
	mov	r4, r2
	mov	r7, r0
	add	ip, ip, r1, lsl #2
	ldr	r3, [ip, #32]
	cmp	r3, #2
	movne	r3, #0
	movne	r2, r3
	beq	.L49
.L38:
	str	r2, [r4, #32]
	mov	r0, #4
	add	r2, r5, #32
	str	r3, [r4, #36]
	ldr	r1, .L50+4
	ldr	r3, [r4, #32]
	bl	dprint_vfmw
	ldr	r3, [r4, #36]
	add	r2, r5, #36
	ldr	r1, .L50+8
	mov	r0, #4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L49:
	ldr	r2, [r6, #2788]
	mov	r0, #4
	ldr	r1, .L50+12
	bl	dprint_vfmw
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L39
	ldrb	r3, [r6, #2778]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L40
.L41:
	ldr	r2, [r6, #2788]
	mov	r3, #0
	add	r2, r2, #146
	ldr	r2, [r7, r2, asl #2]
	bic	r2, r2, #15
	b	.L38
.L39:
	ldr	r3, [r6, #2776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L41
	ldrb	r3, [r6, #2776]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L41
	ldr	r1, [r6, #2788]
	mov	r3, #0
	ldr	r0, [r7, #716]
	add	r1, r1, #146
	ldr	r2, [r7, r1, asl #2]
	add	r2, r2, r0
	bic	r2, r2, #15
	b	.L38
.L40:
	ldr	r2, [r6, #2788]
	ldr	r3, [r7, #716]
	add	r2, r2, #146
	ldr	r2, [r7, r2, asl #2]
	add	r3, r2, r3
	bic	r2, r2, #15
	bic	r3, r3, #15
	b	.L38
.L51:
	.align	2
.L50:
	.word	.LANCHOR0
	.word	.LC9
	.word	.LC10
	.word	.LC8
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgMvAddrInfo, .-H264HAL_SetSliceMsgMvAddrInfo
	.global	__aeabi_idiv
	.align	2
	.global	H264HAL_SetSliceMsgEndMbInSlice
	.type	H264HAL_SetSliceMsgEndMbInSlice, %function
H264HAL_SetSliceMsgEndMbInSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	ip, [r1, #4056]
	cmp	ip, #0
	movne	r0, r3
	beq	.L60
.L54:
	mov	r1, #0
	str	r0, [r2, #176]
	mov	r0, r1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L60:
	ldr	r0, [r0, #740]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #262144
	str	r2, [fp, #-16]
	addgt	r1, r1, #1
	addle	r1, r1, #1
	movwgt	r0, #65535
	suble	r0, r0, #1
	movtgt	r0, 3
	bl	__aeabi_idiv
	ldr	r2, [fp, #-16]
	b	.L54
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgEndMbInSlice, .-H264HAL_SetSliceMsgEndMbInSlice
	.align	2
	.global	H264HAL_SetSliceMsgRefPicFrame
	.type	H264HAL_SetSliceMsgRefPicFrame, %function
H264HAL_SetSliceMsgRefPicFrame:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
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
	ldr	lr, [fp, #4]
	str	r3, [fp, #-56]
	mov	r10, r0
	str	r2, [fp, #-52]
	add	r2, lr, #3
	add	r9, r1, lr, lsl #2
	mov	r3, lr, asl #3
	add	r3, r3, #20
	str	r3, [fp, #-48]
	ldr	r3, [r9, #52]
	mov	ip, r2, asl #2
	cmp	r3, #0
	beq	.L61
	mov	r4, lr, asl #10
	mov	r5, #0
	add	r4, r4, lr, lsl #7
	mov	r7, r5
	add	r4, r1, r4
	mov	r8, r5
	b	.L67
.L65:
	cmp	r6, #3
	beq	.L74
.L66:
	ldr	r3, [r9, #52]
	cmp	r3, r5
	bls	.L75
.L67:
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	and	r3, r5, #7
	ldr	r2, [r10, #48]
	and	r6, r5, #3
	ldr	r0, .L77
	add	r4, r4, #36
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1591]	@ zero_extendqisi2
	add	r5, r5, #1
	add	r1, r0, r1, lsl #2
	cmp	r2, #1
	ldr	r2, [r4, #1608]
	ldr	r1, [r1, #44]
	moveq	r0, #8
	movne	r0, #0
	cmp	r3, #7
	and	r1, r1, #3
	mov	r2, r2, asl #1
	orr	r1, r0, r1
	and	r2, r2, #31
	mov	r3, r3, asl #2
	add	r0, r6, r6, lsl #2
	orr	r8, r8, r1, asl r3
	orr	r7, r7, r2, asl r0
	bne	.L65
	ldr	r2, [fp, #-52]
	mov	r0, #4
	ldr	r3, [fp, #-56]
	ldr	r1, .L77+4
	str	r8, [r2, ip, asl #2]
	add	r3, r3, ip, lsl #2
	ldr	lr, [r2, ip, asl #2]
	mov	r2, ip
	add	ip, ip, #1
	str	ip, [fp, #-60]
	mov	r8, #0
	str	lr, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	ldr	ip, [fp, #-60]
	bne	.L66
.L74:
	ldr	r1, [fp, #-52]
	str	ip, [fp, #-60]
	ldr	ip, [fp, #-48]
	ldr	r0, [fp, #-56]
	str	r7, [r1, ip, asl #2]
	add	r3, r0, ip, lsl #2
	ldr	lr, [r1, ip, asl #2]
	mov	r2, ip
	ldr	r1, .L77+4
	mov	r0, #4
	add	ip, ip, #1
	str	ip, [fp, #-48]
	str	lr, [sp]
	mov	r7, #0
	bl	dprint_vfmw
	ldr	r3, [r9, #52]
	ldr	ip, [fp, #-60]
	cmp	r3, r5
	bhi	.L67
.L75:
	tst	r3, #7
	bne	.L76
.L61:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L76:
	ldr	r4, [fp, #-52]
	mov	r2, ip
	ldr	r5, [fp, #-56]
	mov	r0, #4
	ldr	r1, .L77+4
	str	r8, [r4, ip, asl #2]
	add	r3, r5, ip, lsl #2
	ldr	lr, [r4, ip, asl #2]
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	ldr	r1, .L77+4
	mov	r0, #4
	str	r7, [r4, r3, asl #2]
	mov	r2, r3
	ldr	ip, [r4, r3, asl #2]
	add	r3, r5, r3, lsl #2
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L78:
	.align	2
.L77:
	.word	.LANCHOR0
	.word	.LC11
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicFrame, .-H264HAL_SetSliceMsgRefPicFrame
	.align	2
	.global	H264HAL_SetSliceMsgRefPicField
	.type	H264HAL_SetSliceMsgRefPicField, %function
H264HAL_SetSliceMsgRefPicField:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
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
	ldr	lr, [fp, #4]
	str	r3, [fp, #-56]
	add	r10, lr, #3
	str	r0, [fp, #-48]
	add	ip, r1, lr, lsl #2
	mov	r9, lr, asl #3
	str	r2, [fp, #-52]
	mov	r10, r10, asl #2
	ldr	r3, [ip, #52]
	add	r9, r9, #20
	cmp	r3, #0
	beq	.L79
	mov	r4, lr, asl #10
	mov	r5, #0
	mov	r3, ip
	add	r4, r4, lr, lsl #7
	mov	ip, r9
	add	r4, r1, r4
	mov	r7, r5
	mov	r8, r5
	mov	r9, r3
	b	.L99
.L82:
	cmp	r3, #2
	beq	.L90
	and	r6, r5, #3
	and	r3, r5, #7
.L89:
	cmp	r3, #7
	beq	.L113
.L97:
	cmp	r6, #3
	beq	.L114
.L98:
	ldr	r3, [r9, #52]
	add	r5, r5, #1
	add	r4, r4, #36
	cmp	r3, r5
	bls	.L115
.L99:
	ldrb	r3, [r4, #1624]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L82
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L83
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r0, [r4, #1628]	@ zero_extendqisi2
	ldr	r1, [r2, #48]
	ldrb	r2, [r4, #1629]	@ zero_extendqisi2
	add	r1, r1, r0, lsl #1
	cmp	r2, #1
	ldr	r2, .L117
	add	r1, r2, r1, lsl #2
	moveq	lr, #8
	movne	lr, #0
	cmp	r0, #1
	ldr	r2, [r1, #76]
	mov	r0, r3, asl #2
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, lr
	orr	r2, r1, r2
	orr	r8, r8, r2, asl r0
.L86:
	ldr	r2, [r4, #1644]
	and	r6, r5, #3
	cmp	r3, #7
	add	r1, r6, r6, lsl #2
	mov	r2, r2, asl #1
	and	r2, r2, #31
	orr	r7, r7, r2, asl r1
	bne	.L97
.L113:
	ldr	r2, [fp, #-52]
	mov	r0, #4
	ldr	r3, [fp, #-56]
	ldr	r1, .L117+4
	str	r8, [r2, r10, asl #2]
	add	r3, r3, r10, lsl #2
	ldr	lr, [r2, r10, asl #2]
	mov	r2, r10
	str	ip, [fp, #-60]
	add	r10, r10, #1
	mov	r8, #0
	str	lr, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	ldr	ip, [fp, #-60]
	bne	.L98
.L114:
	ldr	r2, [fp, #-52]
	mov	r0, #4
	ldr	r3, [fp, #-56]
	ldr	r1, .L117+4
	str	r7, [r2, ip, asl #2]
	add	r3, r3, ip, lsl #2
	ldr	lr, [r2, ip, asl #2]
	mov	r2, ip
	mov	r7, #0
	add	ip, ip, #1
	str	ip, [fp, #-60]
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	ip, [fp, #-60]
	b	.L98
.L90:
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L91
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r0, [r4, #1630]	@ zero_extendqisi2
	ldr	r1, [r2, #48]
	ldrb	r2, [r4, #1631]	@ zero_extendqisi2
	add	r1, r1, r0, lsl #1
	cmp	r2, #1
	ldr	r2, .L117
	add	r1, r2, r1, lsl #2
	moveq	lr, #8
	movne	lr, #0
	cmp	r0, #1
	ldr	r2, [r1, #76]
	mov	r0, r3, asl #2
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, lr
	orr	r2, r1, r2
	orr	r8, r8, r2, asl r0
.L94:
	ldr	r2, [r4, #1644]
	and	r6, r5, #3
	add	r1, r6, r6, lsl #2
	mov	r2, r2, asl #1
	and	r2, r2, #30
	orr	r2, r2, #1
	orr	r7, r7, r2, asl r1
	b	.L89
.L115:
	tst	r3, #7
	mov	r9, ip
	bne	.L116
.L79:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L83:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1629]	@ zero_extendqisi2
	ldr	r2, [r2, #48]
	cmp	r0, #1
	ldr	r0, .L117
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1628]	@ zero_extendqisi2
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #76]
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, r0
	orr	r2, r1, r2
	mov	r0, r3, asl #2
	orr	r8, r8, r2, asl r0
	b	.L86
.L91:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1631]	@ zero_extendqisi2
	ldr	r2, [r2, #48]
	cmp	r0, #1
	ldr	r0, .L117
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1630]	@ zero_extendqisi2
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #76]
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, r0
	orr	r2, r1, r2
	mov	r0, r3, asl #2
	orr	r8, r8, r2, asl r0
	b	.L94
.L116:
	ldr	r4, [fp, #-52]
	mov	r2, r10
	ldr	r5, [fp, #-56]
	mov	r0, #4
	ldr	r1, .L117+4
	str	r8, [r4, r10, asl #2]
	add	r3, r5, r10, lsl #2
	ldr	ip, [r4, r10, asl #2]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r7, [r4, r9, asl #2]
	ldr	ip, [r4, r9, asl #2]
	add	r3, r5, r9, lsl #2
	mov	r2, r9
	ldr	r1, .L117+4
	mov	r0, #4
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L118:
	.align	2
.L117:
	.word	.LANCHOR0
	.word	.LC11
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicField, .-H264HAL_SetSliceMsgRefPicField
	.align	2
	.global	H264HAL_SetSliceMsgRefPicInfo
	.type	H264HAL_SetSliceMsgRefPicInfo, %function
H264HAL_SetSliceMsgRefPicInfo:
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
	ldrb	ip, [r0]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	ip, #0
	mov	r6, r2
	mov	r7, r3
	bne	.L120
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicFrame
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r3, .L125
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #32]
	cmp	r3, #2
	beq	.L124
.L119:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L120:
	mov	ip, #0
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicField
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r1, .L125
	add	r1, r1, r3, lsl #2
	ldr	r3, [r1, #32]
	cmp	r3, #2
	bne	.L119
	mov	ip, #1
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicField
	b	.L119
.L124:
	mov	ip, #1
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicFrame
	b	.L119
.L126:
	.align	2
.L125:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicInfo, .-H264HAL_SetSliceMsgRefPicInfo
	.align	2
	.global	H264HAL_SetSliceMsgAPCInfo
	.type	H264HAL_SetSliceMsgAPCInfo, %function
H264HAL_SetSliceMsgAPCInfo:
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
	mov	r5, r1
	mov	r8, r2
	ldr	r2, [r5, #3928]!
	mov	r7, r3
	mov	r4, #0
	and	r3, r2, #31
	mov	r6, #36
.L128:
	add	r4, r4, #1
	and	r0, r4, #3
	cmp	r4, #32
	add	r2, r0, r0, lsl #2
	beq	.L131
	ldr	ip, [r5, #4]!
	cmp	r0, #3
	and	r0, ip, #31
	orr	r3, r3, r0, asl r2
	bne	.L128
	str	r3, [r8, r6, asl #2]
	mov	r2, r6
	ldr	ip, [r8, r6, asl #2]
	add	r3, r7, r6, lsl #2
	ldr	r1, .L132
	mov	r0, #4
	add	r6, r6, #1
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	b	.L128
.L131:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L133:
	.align	2
.L132:
	.word	.LC11
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgAPCInfo, .-H264HAL_SetSliceMsgAPCInfo
	.align	2
	.global	H264HAL_SetSliceMsgWPInfo
	.type	H264HAL_SetSliceMsgWPInfo, %function
H264HAL_SetSliceMsgWPInfo:
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
	ldr	r1, [r0, #300]
	mov	r8, r2
	str	r3, [fp, #-52]
	cmp	r1, #0
	beq	.L135
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, .L169
	add	r3, r2, r3, lsl #2
	str	r2, [fp, #-48]
	ldr	r3, [r3, #32]
	cmp	r3, #1
	beq	.L136
.L135:
	ldr	r3, [r0, #304]
	cmp	r3, #1
	beq	.L167
.L134:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L167:
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, .L169
	add	r3, r2, r3, lsl #2
	str	r2, [fp, #-48]
	ldr	r3, [r3, #32]
	cmp	r3, #2
	bne	.L134
.L136:
	ldr	r2, [r4, #44]
	mov	r0, #4
	ldr	r1, .L169+4
	mov	r6, r8
	bl	dprint_vfmw
	ldr	r7, [fp, #-52]
	mov	r9, r4
	mov	r5, r4
	mov	r10, #0
.L139:
	ldr	r0, [r5, #88]
	add	r3, r7, #256
	ldrb	r1, [r5, #856]	@ zero_extendqisi2
	add	r2, r10, #64
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #80]
	add	r5, r5, #4
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L169+8
	orr	r0, r0, ip
	str	r0, [r6, #256]
	ldr	ip, [r6, #256]
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r0, [r5, #212]
	ldrb	r1, [r5, #980]	@ zero_extendqisi2
	add	r3, r7, #512
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #84]
	add	r2, r10, #128
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L169+8
	orr	r0, r0, ip
	str	r0, [r6, #512]
	ldr	ip, [r6, #512]
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r0, [r5, #1108]	@ zero_extendqisi2
	ldr	r1, [r5, #340]
	add	r3, r7, #768
	add	r2, r10, #192
	add	r10, r10, #1
	ubfx	r1, r1, #0, #9
	orr	r1, r1, r0, asl #9
	str	r1, [r6, #768]
	ldr	ip, [r6, #768]
	mov	r0, #4
	ldr	r1, .L169+8
	add	r6, r6, r0
	add	r7, r7, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r10, r3
	bls	.L139
	ldr	r2, [r4, #80]
	mov	r0, #4
	ldr	r1, .L169+12
	add	r6, r4, #84
	bl	dprint_vfmw
	add	r5, r4, #852
	mov	r7, #0
.L140:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L169+16
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #4]!
	ldr	r1, .L169+20
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r7, r3
	bls	.L140
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #32]
	cmp	r3, #2
	beq	.L141
.L144:
	ldr	r2, [r4, #84]
	mov	r0, #4
	ldr	r1, .L169+24
	add	r6, r4, #212
	bl	dprint_vfmw
	add	r5, r4, #980
	mov	r7, #0
.L142:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L169+28
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #4]!
	ldr	r1, .L169+32
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r7, r3
	bls	.L142
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #32]
	cmp	r3, #2
	beq	.L168
.L145:
	add	r6, r4, #1104
	add	r7, r4, #340
	add	r6, r6, #4
	mov	r5, #0
.L147:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L169+36
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L169+40
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r5, r3
	bls	.L147
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #32]
	cmp	r3, #2
	bne	.L134
	add	r6, r4, #1488
	add	r7, r4, #724
	add	r6, r6, #4
	mov	r5, #0
.L149:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L169+44
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L169+48
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r2, [r4, #40]
	cmp	r5, r2
	bls	.L149
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [fp, #-48]
	add	r10, r1, r3, lsl #2
	ldr	r3, [r10, #32]
	cmp	r3, #2
	bne	.L134
	ldr	r1, .L169+52
	mov	r0, #4
	ldr	r5, [fp, #-52]
	bl	dprint_vfmw
	mov	r6, #0
.L150:
	ldr	r7, [r9, #472]
	add	r3, r5, #384
	ldrb	ip, [r9, #1240]	@ zero_extendqisi2
	add	r2, r6, #96
	ldr	lr, [r4, #80]
	ubfx	r7, r7, #0, #9
	ldr	r1, .L169+8
	mov	r0, #4
	mov	ip, ip, asl #12
	and	lr, lr, #7
	orr	ip, ip, r7, asl #3
	orr	ip, ip, lr
	str	ip, [r8, #384]
	ldr	ip, [r8, #384]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r9, #600]
	ldrb	r0, [r9, #1368]	@ zero_extendqisi2
	add	r3, r5, #640
	ldr	lr, [r4, #84]
	ubfx	ip, ip, #0, #9
	add	r2, r6, #160
	ldr	r1, .L169+8
	mov	r0, r0, asl #12
	and	lr, lr, #7
	orr	ip, r0, ip, asl #3
	mov	r0, #4
	orr	ip, ip, lr
	str	ip, [r8, #640]
	ldr	ip, [r8, #640]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r9, #728]
	ldrb	lr, [r9, #1496]	@ zero_extendqisi2
	mov	r0, #4
	ubfx	ip, ip, #0, #9
	add	r3, r5, #896
	add	r2, r6, #224
	ldr	r1, .L169+8
	orr	ip, ip, lr, asl #9
	str	ip, [r8, #896]
	ldr	ip, [r8, #896]
	add	r9, r9, r0
	add	r8, r8, r0
	add	r5, r5, r0
	add	r6, r6, #1
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r6, r3
	bls	.L150
	b	.L134
.L168:
	add	r6, r4, #1360
	add	r7, r4, #596
	add	r6, r6, #4
	mov	r5, #0
.L146:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L169+56
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L169+60
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r5, r3
	bls	.L146
	b	.L145
.L141:
	add	r6, r4, #1232
	add	r7, r4, #468
	add	r6, r6, #4
	mov	r5, #0
.L143:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L169+64
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L169+68
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r5, r3
	bls	.L143
	b	.L144
.L170:
	.align	2
.L169:
	.word	.LANCHOR0
	.word	.LC12
	.word	.LC11
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC19
	.word	.LC20
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC21
	.word	.LC22
	.word	.LC17
	.word	.LC18
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgWPInfo, .-H264HAL_SetSliceMsgWPInfo
	.align	2
	.global	H264HAL_CheckParaValid
	.type	H264HAL_CheckParaValid, %function
H264HAL_CheckParaValid:
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
	cmp	r1, #0
	bgt	.L178
	cmp	r0, #0
	beq	.L179
	ldr	r3, [r0, #44]
	cmp	r3, #512
	bhi	.L176
	ldr	r3, [r0, #36]
	cmp	r3, #512
	bhi	.L176
	ldr	r0, [r0, #944]
	cmp	r0, #0
	movne	r0, #0
	beq	.L180
.L173:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L178:
	mov	r0, #0
	mov	r3, r1
	str	r0, [sp]
	ldr	r2, .L181
	ldr	r1, .L181+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L173
.L176:
	ldr	r3, .L181+8
	mov	r0, #0
	ldr	r2, .L181
	ldr	r1, .L181+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L173
.L179:
	ldr	r3, .L181+16
	ldr	r2, .L181
	ldr	r1, .L181+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L173
.L180:
	ldr	r3, .L181+20
	ldr	r2, .L181
	ldr	r1, .L181+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L173
.L182:
	.align	2
.L181:
	.word	.LANCHOR0+108
	.word	.LC28
	.word	.LC30
	.word	.LC3
	.word	.LC29
	.word	.LC31
	UNWIND(.fnend)
	.size	H264HAL_CheckParaValid, .-H264HAL_CheckParaValid
	.align	2
	.global	H264HAL_GetVdmRegVirAddr
	.type	H264HAL_GetVdmRegVirAddr, %function
H264HAL_GetVdmRegVirAddr:
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
	mov	r4, r0
	beq	.L190
	cmp	r1, #1
	moveq	r0, #0
	movteq	r0, 63941
	bne	.L192
.L185:
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L188
.L189:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L192:
	ldr	r1, .L193
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L190:
	mov	r0, #0
	movt	r0, 63683
	b	.L185
.L188:
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	bne	.L189
	ldr	r1, .L193+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L194:
	.align	2
.L193:
	.word	.LC32
	.word	.LC33
	UNWIND(.fnend)
	.size	H264HAL_GetVdmRegVirAddr, .-H264HAL_GetVdmRegVirAddr
	.align	2
	.global	H264HAL_V5R6C1_CfgVdmReg
	.type	H264HAL_V5R6C1_CfgVdmReg, %function
H264HAL_V5R6C1_CfgVdmReg:
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
	ldr	r4, .L221
	mov	lr, r2, asl #6
	mov	r6, r2
	sub	lr, lr, r2, asl #3
	ldr	ip, .L221+4
	ldrb	r2, [r4]	@ zero_extendqisi2
	mov	r5, r0
	add	ip, ip, lr
	mov	r9, r1
	subs	r2, r2, #1
	mov	r7, r3
	ldr	r1, [ip, #8]
	movne	r2, #1
	cmp	r3, #0
	movne	r0, #0
	andeq	r0, r2, #1
	cmp	r0, #0
	bne	.L219
	ldr	r3, .L221+8
	mov	r0, #8
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldrne	r8, [r4, #1168]
	moveq	r3, r4
	moveq	r8, r4
	uxtbne	r3, r8
	andne	r4, r3, #1
	cmp	r2, #0
	strneb	r3, [r7, #1]
	mov	r3, #0
	ldr	lr, [r5, #1184]
	mov	r2, r6
	ldr	ip, [r5, #740]
	cmp	lr, #1
	str	r3, [fp, #-48]
	ldr	r1, [fp, #-48]
	movne	lr, r3
	moveq	lr, #3
	cmp	ip, #262144
	mov	r3, r7
	suble	ip, ip, #1
	movwgt	ip, #65535
	ubfxle	ip, ip, #0, #20
	movtgt	ip, 3
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-48]
	mov	ip, r1, lsr #24
	mov	r1, r1, lsr #16
	and	ip, ip, #62
	and	r1, r1, #191
	orr	ip, ip, #65
	bfc	r1, #7, #1
	and	ip, ip, #253
	strb	r1, [fp, #-46]
	bfi	ip, lr, #2, #2
	strb	ip, [fp, #-45]
	ldr	r10, [fp, #-48]
	mov	r1, r10
	str	r10, [r5, #956]
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+12
	mov	r0, #3
	bl	dprint_vfmw
	ldrb	r2, [r5, #16]	@ zero_extendqisi2
	ldrb	ip, [r5, #2]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r0, [r5, #3]	@ zero_extendqisi2
	bfi	r3, r2, #4, #1
	bfi	r3, ip, #6, #1
	mov	r1, #0
	cmp	r0, r1
	mov	r2, #0
	mvn	r3, r3, asl #25
	bfi	r2, r1, #0, #4
	mvn	r3, r3, lsr #25
	strb	r2, [fp, #-48]
	strb	r3, [fp, #-47]
	mov	r2, #1
	mov	r3, #0
	strh	r2, [fp, #-46]	@ movhi
	bfi	r3, r4, #4, #1
	strb	r3, [fp, #-45]
	beq	.L201
	ldr	r3, [r5, #44]
	mov	r3, r3, asl #4
	cmp	r3, #1920
	bhi	.L202
.L201:
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	mov	r1, #0
	mov	r2, r1
	strb	r1, [r5, #4]
	bfc	r3, #5, #1
	strb	r3, [fp, #-45]
.L203:
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	mov	r10, #0
	strb	r10, [r5, #17]
	mov	r3, r7
	bfi	r1, r2, #6, #1
	mov	r0, #12
	bfi	r1, r10, #7, #1
	strb	r1, [fp, #-45]
	ldr	r4, [fp, #-48]
	mov	r2, r6
	mov	r1, r4
	str	r4, [r5, #960]
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L221+16
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r9, #56]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #16
	str	r4, [r5, #964]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L221+20
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r9, #40]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #20
	str	r4, [r5, #968]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L221+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r5, #736]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #24
	str	r4, [r5, #972]
	mov	r1, r4
	str	r4, [fp, #-48]
	bl	MFDE_ConfigReg
	ldr	r1, .L221+28
	mov	r2, r4
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	cmp	r3, #256
	movhi	r1, r10
	bhi	.L204
	cmp	r3, #119
	ldrhi	r1, [r5, #1180]
	movls	r1, #1
	clzhi	r1, r1
	movhi	r1, r1, lsr #5
.L204:
	movw	r4, #3075
	mov	r3, r7
	movt	r4, 48
	mov	r2, r6
	mov	r0, #4
	bl	SCD_ConfigReg
	mov	r1, r4
	mov	r3, r7
	mov	r2, r6
	mov	r0, #60
	str	r4, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #84
	bl	MFDE_ConfigReg
	cmp	r8, #1
	beq	.L220
.L205:
	ldr	r1, [r5, #308]
	mov	ip, #0
	mov	r3, r7
	mov	r2, r6
	mov	r0, #96
	mov	r4, ip
	add	r1, r5, r1, lsl #2
	str	ip, [fp, #-56]
	mov	r8, ip
	ldr	r10, [r1, #324]
	bic	r10, r10, #15
	str	r10, [r5, #1008]
	mov	r1, r10
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+32
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r10, [r5, #720]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #100
	mov	r1, r10
	str	r10, [r5, #1012]
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+36
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r10, [r5, #320]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #104
	mov	r1, r10
	str	r10, [r5, #1016]
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+40
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r10, [r5, #732]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #108
	mov	r1, r10
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+44
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r10, [r9, #1164]
	mov	r3, r7
	mov	r2, r6
	bic	r10, r10, #15
	mov	r0, #128
	str	r10, [r5, #1032]
	mov	r1, r10
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L221+48
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r9, #1168]
	ldr	ip, [fp, #-56]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #132
	str	ip, [fp, #-48]
	strh	r1, [fp, #-48]	@ movhi
	ldr	r9, [fp, #-48]
	mov	r1, r9
	str	r9, [r5, #1036]
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L221+52
	mov	r0, #3
	bl	dprint_vfmw
	add	ip, r5, #1040
	add	ip, ip, #8
.L206:
	ldr	r0, [ip, #4]!
	and	r0, r0, #3
	orr	r8, r8, r0, asl r4
	add	r4, r4, #2
	cmp	r4, #32
	bne	.L206
	mov	r3, r7
	mov	r2, r6
	mov	r1, r8
	mov	r0, #148
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L221+56
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r7
	mov	r2, r6
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L221+60
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, r4
	mov	r3, r7
	mov	r2, r6
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L197:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L202:
	ldrb	r2, [r5, #4]	@ zero_extendqisi2
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	and	r2, r2, #1
	bfi	r3, r1, #5, #1
	strb	r3, [fp, #-45]
	b	.L203
.L220:
	ldr	r1, .L221+64
	mov	r3, r7
	mov	r2, r6
	mov	r0, #92
	ldr	r4, [r1]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L221+68
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r5, #308]
	mov	r2, r6
	mov	r3, r7
	mov	r0, #112
	add	r1, r5, r1, lsl #2
	ldr	r4, [r1, #452]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L221+72
	mov	r0, #3
	bl	dprint_vfmw
	b	.L205
.L219:
	ldr	r2, .L221+76
	mov	r0, #0
	ldr	r1, .L221+80
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L197
.L222:
	.align	2
.L221:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	g_TunnelLineNumber
	.word	.LC40
	.word	.LC41
	.word	.LANCHOR0+132
	.word	.LC34
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_CfgVdmReg, .-H264HAL_V5R6C1_CfgVdmReg
	.align	2
	.global	H264HAL_FindNextSlicePara
	.type	H264HAL_FindNextSlicePara, %function
H264HAL_FindNextSlicePara:
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
	cmp	r2, r1
	ldr	lr, [r0, #48]
	str	r2, [r3]
	ldmgefd	sp, {fp, sp, pc}
	ldr	r0, [r0, #4056]
	cmp	r0, #0
	beq	.L227
	ldr	ip, [r0, #48]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
	add	r2, r2, #1
	b	.L226
.L228:
	ldr	r0, [r0, #4056]
	cmp	r0, #0
	beq	.L227
	ldr	ip, [r0, #48]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
.L226:
	cmp	r2, r1
	str	r2, [r3]
	add	r2, r2, #1
	bne	.L228
	ldmfd	sp, {fp, sp, pc}
.L227:
	movw	r2, #882
	ldr	r1, .L232
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L233:
	.align	2
.L232:
	.word	.LC50
	UNWIND(.fnend)
	.size	H264HAL_FindNextSlicePara, .-H264HAL_FindNextSlicePara
	.align	2
	.global	H264HAL_V5R6C1_SetPicMsg
	.type	H264HAL_V5R6C1_SetPicMsg, %function
H264HAL_V5R6C1_SetPicMsg:
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
	mov	r5, r0
	mov	r0, r2
	str	r2, [fp, #-48]
	str	r1, [fp, #-52]
	mov	r4, r3
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L266
	ldrb	r8, [r5]	@ zero_extendqisi2
	mov	r0, #4
	ldr	r3, [r5, #48]
	ldr	r1, [r5, #52]
	ldr	r6, [r5, #56]
	add	ip, r3, r8, lsl #1
	ldr	r8, .L269
	ldr	lr, [r5, #60]
	mov	r1, r1, asl #28
	ldr	r3, [r5, #44]
	add	r8, r8, ip, lsl #2
	ldr	ip, [r5, #36]
	orr	r1, r1, r6, asl #27
	ldr	r6, [r5, #32]
	orr	r1, r1, lr, asl #26
	ldr	r9, [r8, #188]
	sub	ip, ip, #1
	sub	r3, r3, #1
	cmp	r6, #0
	orr	r3, r1, r3
	ldrb	r8, [r5, #1]	@ zero_extendqisi2
	orr	lr, r3, ip, asl #16
	ldr	r10, [fp, #-48]
	orr	ip, lr, r9, asl #14
	movne	r6, #-2147483648
	cmp	r8, #1
	orr	ip, ip, r6
	mov	r2, r10
	ldr	r1, .L269+4
	moveq	r6, #33554432
	movne	r6, #0
	orr	ip, ip, r6
	str	ip, [r7]
	ldr	r3, [r7]
	bl	dprint_vfmw
	ldr	r3, [r5, #312]
	add	r2, r10, #4
	ldr	r1, .L269+8
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	bl	dprint_vfmw
	ldr	r3, [r5, #64]
	add	r2, r10, #8
	ldr	r1, .L269+12
	mov	r0, #4
	str	r3, [r7, #8]
	ldr	r3, [r7, #8]
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	cmp	r3, #0
	bne	.L267
	ldr	r6, [fp, #-48]
	mov	r0, #4
	str	r3, [r7, #12]
	ldr	r1, .L269+16
	add	r2, r6, #12
	str	r3, [r7, #16]
	ldr	r3, [r7, #12]
.L264:
	bl	dprint_vfmw
	add	r2, r6, #16
	ldr	r3, [r7, #16]
	mov	r0, #4
	ldr	r1, .L269+20
	bic	r4, r4, #15
	bl	dprint_vfmw
	ldr	r6, [fp, #-52]
	ldr	r8, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L269+24
	ldr	r3, [r6, #1144]
	add	r2, r8, #20
	bic	r3, r3, #15
	str	r3, [r7, #20]
	ldr	r3, [r7, #20]
	bl	dprint_vfmw
	ldr	r3, [r6, #1148]
	add	r2, r8, #24
	ldr	r1, .L269+28
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r7, #24]
	ldr	r3, [r7, #24]
	bl	dprint_vfmw
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r6, [fp, #-48]
	mov	r0, #4
	cmp	r3, #2
	ldreq	r2, [r5, #316]
	ldrne	r3, [r5, #316]
	ldreq	r1, [r5, #716]
	addne	r3, r3, #146
	ldrne	r3, [r5, r3, asl #2]
	addeq	r2, r2, #146
	ldreq	r3, [r5, r2, asl #2]
	add	r2, r6, #28
	addeq	r3, r3, r1
	ldr	r1, .L269+32
	bic	r3, r3, #15
	str	r3, [r7, #28]
	ldr	r3, [r7, #28]
	bl	dprint_vfmw
	ldr	r3, [fp, #-52]
	add	r2, r6, #32
	ldr	r1, .L269+36
	mov	r0, #4
	ldr	r3, [r3, #1152]
	bic	r3, r3, #15
	str	r3, [r7, #32]
	ldr	r3, [r7, #32]
	bl	dprint_vfmw
	str	r4, [r7, #36]
	add	r2, r6, #36
	ldr	r3, [r7, #36]
	ldr	r1, .L269+40
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r4, [r5, #936]
	cmp	r4, #0
	ldreq	r3, [fp, #-48]
	rsbeq	r10, r7, r3
	beq	.L243
	ldr	r3, [fp, #-48]
	add	r9, r5, #740
	add	r8, r7, #40
	mov	r6, #0
	rsb	r10, r7, r3
.L244:
	ldr	lr, [r9, #4]!
	mov	r3, r8
	add	r2, r6, #10
	mov	r0, #4
	ldr	r1, .L269+44
	add	r6, r6, #1
	add	lr, r5, lr, lsl #2
	ldr	lr, [lr, #324]
	bic	lr, lr, #15
	str	lr, [r3], r10
	ldr	ip, [r8]
	add	r8, r8, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r4, [r5, #936]
	cmp	r4, r6
	bhi	.L244
	cmp	r4, #15
	bhi	.L248
.L243:
	add	r2, r4, #10
	add	r6, r7, r2, lsl #2
.L247:
	ldr	lr, [r5, #744]
	mov	r3, r6
	add	r4, r4, #1
	mov	r0, #4
	ldr	r1, .L269+44
	add	lr, r5, lr, lsl #2
	ldr	lr, [lr, #324]
	bic	lr, lr, #15
	str	lr, [r3], r10
	ldr	ip, [r6]
	add	r6, r6, r0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r4, #15
	add	r2, r4, #10
	bls	.L247
.L248:
	ldr	r3, [fp, #-52]
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r1, .L269+48
	ldr	r3, [r3, #1088]
	add	r2, r2, #104
	bic	r3, r3, #15
	str	r3, [r7, #104]
	ldr	r3, [r7, #104]
	bl	dprint_vfmw
	ldr	r6, [r5, #936]
	cmp	r6, #0
	beq	.L268
	add	ip, r5, #804
	ldr	r3, [fp, #-48]
	add	r9, r7, #108
	add	r8, r7, #112
	str	r7, [fp, #-60]
	mov	r4, #0
	mov	r6, ip
	mov	r7, r10
	add	r3, r3, #108
	str	r3, [fp, #-56]
.L250:
	ldr	r0, [r6, #4]!
	mov	r3, r9
	mov	r10, r4, asl #1
	ldr	r1, .L269+44
	add	r2, r10, #27
	add	r4, r4, #1
	str	r0, [r3], r7
	mov	r0, #4
	ldr	lr, [r8, #-4]
	add	r9, r9, #8
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	lr, [r6, #64]
	mov	r3, r8
	add	r2, r10, #28
	ldr	r1, .L269+44
	mov	r0, #4
	str	lr, [r3], r7
	add	r8, r8, #8
	ldr	lr, [r9, #-4]
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #936]
	cmp	r3, r4
	bhi	.L250
	cmp	r3, #15
	ldr	r7, [fp, #-60]
	mov	r6, r3
	bhi	.L252
.L249:
	ldr	r3, [fp, #-56]
	mov	ip, r6, asl #1
	add	r9, ip, #27
	add	r4, r7, r6, lsl #3
	rsb	r10, r7, r3
	ldr	r3, [fp, #-48]
	str	r5, [fp, #-56]
	mov	r8, #0
	add	r3, r3, #112
	mov	r5, r6
	mov	r6, r3
.L251:
	str	r8, [r4, #108]
	add	r3, r10, r4
	ldr	lr, [r4, #108]
	mov	r2, r9
	ldr	r1, .L269+44
	mov	r0, #4
	add	r5, r5, #1
	str	lr, [sp]
	bl	dprint_vfmw
	str	r8, [r4, #112]
	ldr	lr, [r4, #112]
	rsb	r3, r7, r6
	add	r3, r3, r4
	add	r2, r9, #1
	ldr	r1, .L269+44
	mov	r0, #4
	str	lr, [sp]
	add	r4, r4, #8
	bl	dprint_vfmw
	cmp	r5, #15
	add	r9, r9, #2
	bls	.L251
	ldr	r5, [fp, #-56]
.L252:
	ldr	r3, [fp, #-52]
	add	r0, r5, #76
	ldr	r2, [fp, #-48]
	mov	r1, #56
	ldr	ip, [r3, #1160]
	add	r2, r2, #256
	add	r3, r7, #256
	bic	ip, ip, #15
	str	ip, [r7, #236]
	bl	Write_V5R6C1_Qmatrix
	mov	r0, #0
.L236:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L267:
	ldr	r3, [r5, #68]
	mov	r0, #4
	ldr	r6, [fp, #-48]
	ldr	r1, .L269+16
	str	r3, [r7, #12]
	add	r2, r6, #12
	ldr	ip, [r5, #72]
	ldr	r3, [r7, #12]
	str	ip, [r7, #16]
	b	.L264
.L268:
	ldr	r3, [fp, #-48]
	add	r3, r3, #108
	str	r3, [fp, #-56]
	b	.L249
.L266:
	ldr	r3, .L269+52
	ldr	r2, .L269+56
	ldr	r1, .L269+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L236
.L270:
	.align	2
.L269:
	.word	.LANCHOR0
	.word	.LC52
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC62
	.word	.LC63
	.word	.LC51
	.word	.LANCHOR0+160
	.word	.LC3
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_SetPicMsg, .-H264HAL_V5R6C1_SetPicMsg
	.align	2
	.global	H264HAL_V5R6C1_SetSliceMsg
	.type	H264HAL_V5R6C1_SetSliceMsg, %function
H264HAL_V5R6C1_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r0
	mov	r0, r3
	mov	r6, r3
	mov	r4, r2
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L284
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	ip, [r4, #48]
	ldr	r3, [r4, #32]
	add	r2, r6, #24
	ldr	lr, [r4, #36]
	ubfx	ip, ip, #0, #20
	ldr	r1, .L286
	mov	r0, #4
	and	lr, lr, #3
	orr	r3, ip, r3, asl #26
	orr	r3, r3, lr, asl #24
	str	r3, [r5, #24]
	ldr	r3, [r5, #24]
	bl	dprint_vfmw
	ldr	r3, .L286+4
	ldrb	lr, [r4, #3]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L275
	cmp	lr, #0
	beq	.L285
.L275:
	ldr	ip, [r4, #40]
	add	r2, r6, #28
	ldr	r1, [r4, #56]
	mov	r0, #4
	ldrb	r10, [r4]	@ zero_extendqisi2
	and	r3, ip, #31
	ldr	r8, .L286+8
	ldr	ip, [r4, #52]
	mov	r1, r1, asl #8
	ldr	r9, [r4, #44]
	add	r10, r8, r10, lsl #2
	orr	r1, r1, ip, asl #2
	and	r9, r9, #31
	orr	ip, r1, r3, asl #21
	ldr	r1, [r10, #32]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	orr	ip, ip, r9, asl #16
	orr	ip, ip, r1
	ldr	r1, .L286+12
	orr	r3, ip, r3, asl #15
	orr	r3, r3, lr, asl #14
	str	r3, [r5, #28]
	ldr	r3, [r5, #28]
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgMvAddrInfo
	ldr	ip, [r4, #60]
	ldrb	r9, [r4, #4]	@ zero_extendqisi2
	add	r2, r6, #40
	and	ip, ip, #31
	ldr	r3, [r4, #64]
	ldr	r1, .L286+16
	mov	r0, #4
	mov	ip, ip, asl #5
	and	lr, r3, #31
	orr	r3, ip, r9, asl #16
	orr	r3, r3, lr
	str	r3, [r5, #40]
	ldr	r3, [r5, #40]
	bl	dprint_vfmw
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #72]
	add	r2, r6, #44
	and	ip, ip, #15
	ldr	lr, [r4, #76]
	and	r3, r3, #15
	ldr	r1, .L286+20
	mov	ip, ip, asl #16
	mov	r0, #4
	orr	r3, ip, r3, asl #8
	orr	r3, r3, lr
	str	r3, [r5, #44]
	ldr	r3, [r5, #44]
	bl	dprint_vfmw
	ldr	r3, [r4, #4056]
	cmp	r3, #0
	beq	.L276
	ldr	r0, [fp, #16]
.L277:
	ldr	r3, [fp, #8]
	str	r0, [r5, #176]
	bic	r3, r3, #15
	str	r3, [r5, #252]
	ldrb	r3, [r4]	@ zero_extendqisi2
	add	r8, r8, r3, lsl #2
	ldr	r0, [r8, #32]
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgRefPicInfo
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgAPCInfo
	mov	r0, r7
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	bl	H264HAL_SetSliceMsgWPInfo
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L285:
	ldr	r1, [r7, #40]
	movw	r2, #1620
	ldr	r3, [r7, #44]
	mul	r3, r3, r1
	cmp	r3, r2
	bls	.L275
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L276:
	ldr	r0, [r7, #740]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #262144
	addgt	r1, r1, #1
	addle	r1, r1, #1
	movwgt	r0, #65535
	suble	r0, r0, #1
	movtgt	r0, 3
	bl	__aeabi_idiv
	b	.L277
.L284:
	ldr	r3, .L286+24
	ldr	r2, .L286+28
	ldr	r1, .L286+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L287:
	.align	2
.L286:
	.word	.LC64
	.word	g_not_direct_8x8_inference_flag
	.word	.LANCHOR0
	.word	.LC65
	.word	.LC66
	.word	.LC67
	.word	.LC2
	.word	.LANCHOR0+220
	.word	.LC3
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_SetSliceMsg, .-H264HAL_V5R6C1_SetSliceMsg
	.align	2
	.global	H264HAL_V5R6C1_StartDec
	.type	H264HAL_V5R6C1_StartDec, %function
H264HAL_V5R6C1_StartDec:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	r9, .L324
	movw	r3, #1228
	str	r1, [fp, #-88]
	mov	r4, r2
	mov	r10, r0
	mla	r3, r3, r1, r9
	str	r3, [fp, #-84]
	bl	H264HAL_CheckParaValid
	cmn	r0, #1
	beq	.L318
	ldr	r6, [fp, #-88]
	ldr	r5, [fp, #-84]
	mov	r1, r6
	mov	r0, r5
	bl	H264HAL_GetVdmRegVirAddr
	cmn	r0, #1
	beq	.L318
	ldr	r3, .L324+4
	mov	r0, #3
	ldr	r1, .L324+8
	ldr	ip, [r3]
	add	r2, ip, #1
	str	r2, [r3]
	bl	dprint_vfmw
	mov	r3, r4
	mov	r2, r6
	mov	r1, r5
	mov	r0, r10
	bl	H264HAL_V5R6C1_CfgVdmReg
	cmn	r0, #1
	beq	.L318
	ldr	r3, [r5, #60]
	mov	r1, r5
	ldr	r2, [r5, #56]
	mov	r0, r10
	bl	H264HAL_V5R6C1_SetPicMsg
	ldr	r3, [r10, #1184]
	ldr	r6, [r10, #944]
	cmp	r3, #1
	beq	.L319
	ldr	r4, [r6, #48]
	cmp	r4, #0
	streq	r4, [fp, #-92]
	bne	.L320
.L295:
	ldr	r2, [fp, #-88]
	movw	r3, #307
	ldr	r1, [r10, #940]
	mov	ip, #0
	mov	r4, ip
	mul	r3, r3, r2
	ldr	r2, [fp, #-92]
	add	r0, r2, #5
	str	r0, [fp, #-60]
	str	r3, [fp, #-56]
	add	r3, r3, r2
	str	r3, [fp, #-76]
.L297:
	ldr	r3, [fp, #-60]
	cmp	r4, r1
	ldr	r2, [fp, #-56]
	add	r8, r3, r4
	ldr	r3, [fp, #-76]
	add	r2, r2, r8
	add	r3, r3, r4
	add	r2, r2, #10
	add	r3, r3, #14
	bge	.L321
	ldr	r3, [r9, r3, asl #2]
	cmp	r4, #0
	ldr	r7, [r6, #48]
	movgt	r5, #1
	movle	r5, #0
	str	r3, [fp, #-64]
	cmp	r7, ip
	movhi	r5, #0
	andls	r5, r5, #1
	ldr	r3, [r9, r2, asl #2]
	cmp	r5, #0
	str	r3, [fp, #-68]
	bne	.L297
	sub	r3, fp, #48
	add	r2, r4, #1
	mov	r0, r6
	bl	H264HAL_FindNextSlicePara
	mov	ip, r7
	subs	r3, r0, #0
	str	r3, [fp, #-72]
	beq	.L318
	ldr	r4, [fp, #-48]
	ldr	r2, [r10, #940]
	ldr	r3, [fp, #-56]
	ldr	r1, [fp, #-60]
	cmp	r2, r4
	cmpne	r8, #140
	add	r3, r3, r4
	add	r3, r3, r1
	add	r3, r3, #10
	beq	.L322
	ldr	r2, [fp, #-72]
	ldr	r1, .L324
	ldr	r2, [r2, #48]
	ldr	r1, [r1, r3, asl #2]
	sub	r3, r2, #1
.L300:
	ldr	r0, [fp, #-64]
	mov	r2, r6
	str	r3, [sp, #12]
	str	r1, [sp, #4]
	str	r0, [sp]
	mov	r0, r10
	ldr	r3, [fp, #-68]
	str	r7, [sp, #8]
	ldr	r1, [fp, #-84]
	str	ip, [fp, #-80]
	bl	H264HAL_V5R6C1_SetSliceMsg
	ldr	r6, [fp, #-72]
	cmp	r0, #0
	bne	.L301
	ldr	r1, [r10, #940]
	ldr	ip, [fp, #-80]
	b	.L297
.L322:
	ldr	r2, [r10, #36]
	mov	r1, r5
	ldr	r3, [r10, #44]
	str	r5, [r6, #4056]
	ldr	r4, [r10, #940]
	mul	r3, r3, r2
	sub	r3, r3, #1
	b	.L300
.L321:
	cmp	r1, #0
	ble	.L303
	ldr	r0, [fp, #-92]
	movw	r3, #307
	ldr	r2, [fp, #-88]
	mla	r3, r3, r2, r0
	add	r1, r3, r1
	add	r1, r1, #14
	ldr	r0, [r9, r1, asl #2]
	bl	H264HAL_V5R6C1_CutSliceChain
	mov	r0, #0
.L290:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L303:
	ldr	r1, .L324+12
	mov	r0, #1
	bl	dprint_vfmw
.L318:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L319:
	ldr	r2, [r10, #940]
	cmp	r2, #1
	ble	.L293
.L294:
	add	r3, r3, #1
	ldr	r6, [r6, #4056]
	cmp	r3, r2
	bne	.L294
.L293:
	ldr	r2, [fp, #-88]
	movw	lr, #1228
	ldr	r3, [r10, #44]
	mov	r4, #0
	ldr	ip, [r10, #36]
	mov	r0, r10
	mla	lr, lr, r2, r9
	ldr	r1, [fp, #-84]
	mul	ip, r3, ip
	mov	r2, r6
	ldr	r3, [lr, #60]
	sub	ip, ip, #1
	str	ip, [sp, #12]
	ldr	ip, [r6, #48]
	str	r4, [sp, #4]
	str	r4, [sp]
	str	ip, [sp, #8]
	bl	H264HAL_V5R6C1_SetSliceMsg
	cmp	r0, #0
	beq	.L290
	movw	r2, #1185
	ldr	r1, .L324+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L290
.L320:
	ldr	r3, [r6, #12]
	mov	r0, #0
	ldr	ip, [r6, #20]
	mov	r7, #1
	str	r0, [r6, #48]
	mov	r2, r6
	str	r3, [fp, #-56]
	str	ip, [fp, #-72]
	ldr	r3, [r6, #16]
	ldr	ip, [fp, #-84]
	str	r0, [r6, #12]
	str	r0, [r6, #16]
	str	r0, [r6, #20]
	mov	r1, ip
	ldr	r8, [r6, #8]
	ldr	r5, [r6, #28]
	str	r7, [r6, #8]
	str	r0, [r6, #28]
	str	r3, [fp, #-60]
	sub	r3, r4, #1
	str	r3, [fp, #-68]
	ldr	r3, [r6, #24]
	str	r0, [r6, #24]
	ldr	lr, [ip, #64]
	str	r3, [fp, #-64]
	ldr	r3, [ip, #60]
	str	r0, [sp, #8]
	ldr	r0, [ip, #56]
	str	lr, [sp, #4]
	ldr	lr, [fp, #-68]
	mov	ip, r0
	mov	r0, r10
	str	ip, [sp]
	str	lr, [sp, #12]
	bl	H264HAL_V5R6C1_SetSliceMsg
	ldr	ip, [fp, #-72]
	cmp	r0, #0
	bne	.L323
	ldr	r3, [fp, #-56]
	str	r4, [r6, #48]
	str	r8, [r6, #8]
	str	r3, [r6, #12]
	ldr	r3, [fp, #-60]
	str	ip, [r6, #20]
	str	r5, [r6, #28]
	str	r3, [r6, #16]
	ldr	r3, [fp, #-64]
	str	r7, [fp, #-92]
	str	r3, [r6, #24]
	ldr	r6, [r10, #944]
	b	.L295
.L301:
	movw	r2, #1272
	ldr	r1, .L324+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L323:
	mov	r0, r7
	movw	r2, #1219
	ldr	r1, .L324+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L290
.L325:
	.align	2
.L324:
	.word	g_HwMem
	.word	.LANCHOR1
	.word	.LC68
	.word	.LC70
	.word	.LC69
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_StartDec, .-H264HAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14992, %object
	.size	__func__.14992, 29
__func__.14992:
	.ascii	"H264HAL_V5R6C1_CutSliceChain\000"
	.space	3
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.type	g_ListStructFrame, %object
	.size	g_ListStructFrame, 32
g_ListStructFrame:
	.word	0
	.word	1
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.type	g_ListStructField, %object
	.size	g_ListStructField, 32
g_ListStructField:
	.word	0
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.type	__func__.15126, %object
	.size	__func__.15126, 23
__func__.15126:
	.ascii	"H264HAL_CheckParaValid\000"
	.space	1
	.type	__func__.15148, %object
	.size	__func__.15148, 25
__func__.15148:
	.ascii	"H264HAL_V5R6C1_CfgVdmReg\000"
	.space	3
	.type	__func__.15174, %object
	.size	__func__.15174, 25
__func__.15174:
	.ascii	"H264HAL_V5R6C1_SetPicMsg\000"
	.space	3
	.type	g_StructTrans, %object
	.size	g_StructTrans, 32
g_StructTrans:
	.word	0
	.word	3
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.type	__func__.15204, %object
	.size	__func__.15204, 27
__func__.15204:
	.ascii	"H264HAL_V5R6C1_SetSliceMsg\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"line: %d, p = NULL is not expected value!\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"H264HAL_V5R6C1_InitHal return error.\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC3:
	ASCII(.ascii	"%s: %s\012\000" )
.LC4:
	ASCII(.ascii	"qmatrix[%d] = 0x%x\012\000" )
.LC5:
	ASCII(.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,by" )
	ASCII(.ascii	"tespos = 0x%x\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"slicemsg g_pListX[1][0]->frame_store->pmv_address_i" )
	ASCII(.ascii	"dc = %d\012\000" )
.LC9:
	ASCII(.ascii	"slicemsg D[6] addr 0x%x = 0x%x\012\000" )
.LC10:
	ASCII(.ascii	"slicemsg D[7] addr 0x%x = 0x%x\012\000" )
.LC11:
	ASCII(.ascii	"slicemsg D[%d] address 0x%x = 0x%x\012\000" )
.LC12:
	ASCII(.ascii	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31" )
	ASCII(.ascii	" list0size = %d\012\000" )
.LC13:
	ASCII(.ascii	"luma_lg = %d\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"wp_weight_l0_y = %d\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"wp_offset_l0_y = %d\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"chroma_lg = %d\012\000" )
.LC17:
	ASCII(.ascii	"wp_weight_l1_y = %d\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"wp_offset_l1_y = %d\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"wp_weight_l0_u = %d\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"wp_offset_l0_u = %d\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"wp_weight_l1_u = %d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"wp_offset_l1_u = %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"wp_weight_l0_v = %d\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"wp_offset_l0_v = %d\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"wp_weight_l1_v = %d\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"wp_offset_l1_v = %d\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~" )
	ASCII(.ascii	"D63 list1size = %d\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC29:
	ASCII(.ascii	"point of picture para null\012\000" )
.LC30:
	ASCII(.ascii	"picture width out of range\012\000" )
.LC31:
	ASCII(.ascii	"point of fst slice para null\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"VdhId is wrong! H264HAL_V200R003_StartDec\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC34:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"BASIC_V5R6C1_CFG0 = 0x%x\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"BASIC_V5R6C1_CFG1 = 0x%x\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"AVM_V5R6C1_ADDR = 0x%x\012\000" )
.LC38:
	ASCII(.ascii	"VAM_V5R6C1_ADDR = 0x%x\012\000" )
.LC39:
	ASCII(.ascii	"STREAM_V5R6C1_BASE_ADDR = 0x%x\012\000" )
.LC40:
	ASCII(.ascii	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"YSTADDR_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"YSTRIDE_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"UVOFFSET_V5R6C1_1D = 0x%x\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"HEAD_INF_OFFSET_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"PPFD_V5R6C1_BUF_ADDR = 0x%x\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"PPFD_V5R6C1_BUF_LEN = 0x%x\012\000" )
.LC48:
	ASCII(.ascii	"REF_V5R6C1_PIC_TYPE = 0x%x\012\000" )
.LC49:
	ASCII(.ascii	"FF_V5R6C1_APT_EN = 0x%x\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"line %d pSlicePara is NULL!\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"picmsg D[1] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"picmsg D[2] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"picmsg D[3] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"picmsg D[4] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"picmsg D[5] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"picmsg D[6] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"picmsg D[7] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"picmsg D[8] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"picmsg D[9] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"picmsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"picmsg D[26] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"slicemsg D[4] addr 0x%x = 0x%x\012\000" )
.LC65:
	ASCII(.ascii	"slicemsg D[5] addr 0x%x = 0x%x\012\000" )
.LC66:
	ASCII(.ascii	"slicemsg D[8] addr 0x%x = 0x%x\012\000" )
.LC67:
	ASCII(.ascii	"slicemsg D[9] addr 0x%x = 0x%x\012\000" )
.LC68:
	ASCII(.ascii	"\012\012***********************H264HAL_V200R003_Sta" )
	ASCII(.ascii	"rtDec is Now %d***********************\012\000" )
	.space	3
.LC69:
	ASCII(.ascii	"line %d Set slice msg not wrong!\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"!!! no slice to dec, add up msg report.\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.15226, %object
	.size	StartCnt.15226, 4
StartCnt.15226:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
