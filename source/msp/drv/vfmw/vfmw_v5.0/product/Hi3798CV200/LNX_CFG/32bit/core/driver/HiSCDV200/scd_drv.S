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
	.file	"scd_drv.c"
	.text
	.align	2
	.type	GetFreeSegBufSize.part.4, %function
GetFreeSegBufSize.part.4:
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
	add	r0, r0, #163840
	mov	r3, #0
	str	r3, [r1]
	ldr	r3, [r0, #36]
	ldr	r2, [r0, #32]
	cmp	r3, r2
	bls	.L2
	ldr	r0, [r0, #28]
	sub	r2, r2, #1
	add	r2, r2, r0
	rsb	r3, r3, r2
.L3:
	cmp	r3, r0
	strle	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L2:
	ldrcs	r0, [r0, #28]
	subcc	r2, r2, #1
	ldrcc	r0, [r0, #28]
	rsbcc	r3, r3, r2
	subcs	r3, r0, #1
	b	.L3
	UNWIND(.fnend)
	.size	GetFreeSegBufSize.part.4, .-GetFreeSegBufSize.part.4
	.align	2
	.global	WriteCabacTabDsp
	.type	WriteCabacTabDsp, %function
WriteCabacTabDsp:
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
	beq	.L9
	ldr	r3, .L10
	mov	r2, #5120
	ldr	r1, .L10+4
	ldr	r3, [r3, #52]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L9:
	mov	r2, #64
	ldr	r1, .L10+8
	mov	r0, #22
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L11:
	.align	2
.L10:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC2
	UNWIND(.fnend)
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	2
	.global	SCDDRV_LoadDspCode
	.type	SCDDRV_LoadDspCode, %function
SCDDRV_LoadDspCode:
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
	subs	r4, r0, #0
	mov	r7, r1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r5, .L32
	ldr	r0, [r5]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L27
	cmp	r7, #1
	beq	.L28
	cmp	r7, #2
	beq	.L29
	mov	r0, r4
	ldr	r1, .L32+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L29:
	ldr	r6, .L32+8
	mov	r2, #17920
	ldr	r1, .L32+12
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r4
	ldr	r0, [r5, #4]
	bl	MEM_WritePhyWord
.L17:
	ldr	r0, [r5, #4]
	mov	r1, #4480
	mov	r4, #0
	add	r0, r0, #264
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	ldr	r1, [r5]
	add	r0, r0, #268
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	mov	r1, r4
	add	r0, r0, #256
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	mov	r1, #5
	add	r0, r0, #256
	bl	MEM_WritePhyWord
	b	.L20
.L30:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L21
.L20:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r0, [r5, #4]
	add	r0, r0, #260
	bl	MEM_ReadPhyWord
	tst	r0, #1
	beq	.L30
	cmp	r4, #1000
	bcs	.L21
	ldr	r2, .L32+16
	mov	r0, #0
	ldr	r1, .L32+20
	bl	dprint_vfmw
.L23:
	cmp	r7, #1
	beq	.L31
	cmp	r7, #2
	ldreq	r3, .L32+24
	moveq	r2, #1
	streq	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L21:
	ldr	r2, .L32+16
	mov	r0, #0
	ldr	r1, .L32+28
	bl	dprint_vfmw
	b	.L23
.L28:
	ldr	r6, .L32+8
	mov	r2, #17920
	ldr	r1, .L32+32
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r7
	ldr	r0, [r5, #4]
	bl	MEM_WritePhyWord
	b	.L17
.L31:
	ldr	r3, .L32+24
	mov	r2, #2
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L27:
	ldr	r2, [r5]
	ldr	r1, .L32+36
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L33:
	.align	2
.L32:
	.word	.LANCHOR0
	.word	.LC4
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+1552
	.word	.LANCHOR3
	.word	.LC6
	.word	g_DspDrvState
	.word	.LC5
	.word	.LANCHOR1
	.word	.LC3
	UNWIND(.fnend)
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	2
	.global	GetInstIDByRawArray
	.type	GetInstIDByRawArray, %function
GetInstIDByRawArray:
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
	ldr	ip, .L44
	mov	r3, #0
	b	.L37
.L35:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L43
.L37:
	ldr	r2, [ip, r3, asl #3]
	cmp	r2, #0
	add	r1, r2, #72
	beq	.L35
	cmp	r0, r1
	bne	.L35
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L43:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L45:
	.align	2
.L44:
	.word	.LANCHOR0+8
	UNWIND(.fnend)
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	2
	.global	SCDDRV_SetStateIdle
	.type	SCDDRV_SetStateIdle, %function
SCDDRV_SetStateIdle:
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
	ldr	r2, .L47
	mov	r3, r0, asl #6
	ldr	ip, .L47+4
	sub	r3, r3, r0, asl #2
	add	r3, r2, r3
	mov	r1, #0
	mov	r0, #1
	ldr	r2, [ip, #128]
	str	r1, [r3, #312]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r2
.L48:
	.align	2
.L47:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SetStateIdle, .-SCDDRV_SetStateIdle
	.align	2
	.global	SCDDRV_SetStateWork
	.type	SCDDRV_SetStateWork, %function
SCDDRV_SetStateWork:
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
	ldr	r3, .L50
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #2
	mov	r1, #1
	add	r0, r3, r0
	str	r1, [r0, #312]
	ldmfd	sp, {fp, sp, pc}
.L51:
	.align	2
.L50:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_SetStateWork, .-SCDDRV_SetStateWork
	.align	2
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
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
	ldr	r5, .L73
	mov	r7, r0, asl #2
	mov	r4, r0
	mov	r1, #3
	add	r8, r5, r7
	ldr	r0, [r8, #4]
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	ldr	r0, [r8, #4]
	ldr	r8, .L73+4
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	cmp	r4, #0
	ldr	lr, [r8]
	mov	r9, r0
	bne	.L56
	ldr	r6, [lr, #120]
	ands	r2, r6, #1
	orrne	r6, r6, #32
	strne	r6, [lr, #120]
	beq	.L70
.L56:
	mov	r3, #0
	movw	r2, #10000
	b	.L58
.L61:
	add	r3, r3, #1
	cmp	r3, r2
	beq	.L71
.L58:
	cmp	r4, #0
	ldr	ip, [lr, #372]
	bne	.L61
	tst	ip, #2
	beq	.L61
	movw	r2, #9999
	cmp	r3, r2
	bhi	.L72
.L63:
	bfc	r6, #5, #1
	str	r6, [lr, #120]
.L62:
	add	r5, r5, r7
	and	r1, r9, #1
	ldr	r0, [r5, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	mov	r1, #2
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L71:
	mov	r2, r4
	ldr	r1, .L73+8
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r4, #0
	bne	.L62
.L64:
	ldr	lr, [r8]
	b	.L63
.L70:
	ldr	r1, .L73+12
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L72:
	mov	r2, r4
	mov	r0, r4
	ldr	r1, .L73+8
	bl	dprint_vfmw
	b	.L64
.L74:
	.align	2
.L73:
	.word	.LANCHOR0
	.word	g_pstRegCrg
	.word	.LC8
	.word	.LC7
	UNWIND(.fnend)
	.size	ResetSCD, .-ResetSCD
	.align	2
	.global	SCDDRV_ResetSCD
	.type	SCDDRV_ResetSCD, %function
SCDDRV_ResetSCD:
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
	ldr	r4, .L79
	ldr	r3, [r4, #308]
	cmp	r3, r0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L79+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L77
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Reset_Module
.L78:
	ldr	r3, .L79+8
	mov	r2, #0
	mov	r0, #1
	str	r2, [r4, #312]
	ldr	r3, [r3, #128]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L77:
	mov	r0, #0
	bl	ResetSCD
	b	.L78
.L80:
	.align	2
.L79:
	.word	.LANCHOR0
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	2
	.global	SCDDRV_MaskInt
	.type	SCDDRV_MaskInt, %function
SCDDRV_MaskInt:
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
	ldr	r3, .L82
	mov	r1, #1
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MEM_WritePhyWord
.L83:
	.align	2
.L82:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_MaskInt, .-SCDDRV_MaskInt
	.align	2
	.global	SCDDRV_EnableInt
	.type	SCDDRV_EnableInt, %function
SCDDRV_EnableInt:
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
	ldr	r3, .L85
	mov	r1, #0
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MEM_WritePhyWord
.L86:
	.align	2
.L85:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_EnableInt, .-SCDDRV_EnableInt
	.align	2
	.global	ResetRawStreamArray
	.type	ResetRawStreamArray, %function
ResetRawStreamArray:
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
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, .L89
	movw	r2, #32792
	movt	r2, 1
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L90:
	.align	2
.L89:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetRawStreamArray, .-ResetRawStreamArray
	.align	2
	.global	SCDDRV_IsRawArrayFull
	.type	SCDDRV_IsRawArrayFull, %function
SCDDRV_IsRawArrayFull:
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
	add	r0, r0, #98304
	ldr	r3, [r0, #4]
	ldr	r0, [r0, #8]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	rsb	r0, r0, r3
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsRawArrayFull, .-SCDDRV_IsRawArrayFull
	.align	2
	.global	SCDDRV_InsertRawPacket
	.type	SCDDRV_InsertRawPacket, %function
SCDDRV_InsertRawPacket:
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
	ldr	r3, .L96
	ldr	r5, [r1, #4]
	add	r0, r3, r0, lsl #3
	ldr	r2, [r0, #8]
	cmp	r2, #0
	cmpne	r5, #0
	moveq	r5, #1
	movne	r5, #0
	beq	.L94
	add	r4, r2, #98304
	ldr	r0, [r4, #76]
	ldr	lr, [r4, #80]
	add	r3, r0, #1
	mov	ip, r3, asr #31
	mov	ip, ip, lsr #22
	add	r3, r3, ip
	ubfx	r3, r3, #0, #10
	rsb	r3, ip, r3
	cmp	r3, lr
	beq	.L95
	ldr	ip, .L96+4
	mov	r3, r0, asl #7
	add	r2, r2, #72
	sub	r0, r3, r0, asl #5
	add	r0, r2, r0
	mov	r2, #96
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #76]
	mov	r0, r5
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r4, #76]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L95:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L94:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L97:
	.align	2
.L96:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	2
	.global	GetRawState
	.type	GetRawState, %function
GetRawState:
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
	cmp	r0, #31
	bhi	.L101
	ldr	r3, .L103
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L101
	add	r2, r3, #98304
	ldr	r3, [r2, #76]
	ldr	r1, [r2, #80]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	cmp	r3, r1
	mvneq	r0, #3
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L101:
	mvn	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L104:
	.align	2
.L103:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	GetRawState, .-GetRawState
	.align	2
	.global	ShowRawPacket
	.type	ShowRawPacket, %function
ShowRawPacket:
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
	add	r4, r0, #98304
	mov	ip, r0
	ldr	r3, [r4, #16]
	ldr	r2, [r4, #4]
	cmp	r3, r2
	beq	.L107
	ldr	lr, .L108
	mov	r2, r3, asl #7
	sub	r3, r2, r3, asl #5
	mov	r0, r1
	mov	r2, #96
	add	r1, ip, r3
	ldr	r3, [lr, #52]
	blx	r3
	ldr	r3, [r4, #16]
	mov	r0, #0
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L107:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L109:
	.align	2
.L108:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ShowRawPacket, .-ShowRawPacket
	.align	2
	.global	GetFirstRawPacket
	.type	GetFirstRawPacket, %function
GetFirstRawPacket:
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
	mov	r4, r1
	beq	.L118
	add	r5, r0, #98304
	ldr	r3, [r5]
	ldr	r2, [r5, #4]
	cmp	r3, r2
	beq	.L114
	ldr	r8, [r5, #12]
	str	r3, [r5, #16]
	mov	r7, r8, asr #31
	mov	r6, r8
	mov	r9, r8
.L113:
	ldr	ip, .L119
	mov	r1, r3, asl #7
	sub	r1, r1, r3, asl #5
	mov	r2, #96
	add	r1, r0, r1
	mov	r0, r4
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r5, #16]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r5, #16]
.L112:
	ldrd	r2, [r4, #40]
	ldr	r0, [r4, #4]
	ldr	r1, [r4, #8]
	adds	r6, r6, r2
	add	r9, r0, r9
	adc	r7, r7, r3
	rsb	r8, r8, r1
	str	r9, [r4, #4]
	strd	r6, [r4, #40]
	str	r8, [r4, #8]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L114:
	mov	r9, #0
	str	r3, [r5, #16]
	mov	r8, r9
	mov	r6, #0
	mov	r7, #0
	b	.L112
.L118:
	mov	r5, #98304
	ldr	r3, [r5]
	ldr	r2, [r5, #4]
	cmp	r3, r2
	str	r3, [r5, #16]
	movne	r6, #0
	movne	r7, #0
	movne	r9, r0
	movne	r8, r0
	bne	.L113
	mov	r9, r0
	mov	r6, #0
	mov	r7, #0
	mov	r8, r0
	b	.L112
.L120:
	.align	2
.L119:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	2
	.global	SetFirstOffset
	.type	SetFirstOffset, %function
SetFirstOffset:
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
	beq	.L125
	add	r3, r0, #98304
	ldmia	r3, {r2, ip}
	cmp	r2, ip
	beq	.L124
	mov	ip, r2, asl #7
	ldr	lr, [r3, #12]
	sub	r2, ip, r2, asl #5
	add	r0, r0, r2
	add	r1, r1, lr
	ldr	r2, [r0, #8]
	cmp	r1, r2
	bge	.L125
	str	r1, [r3, #12]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L125:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L124:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetFirstOffset, .-SetFirstOffset
	.align	2
	.global	GetFirstOffset
	.type	GetFirstOffset, %function
GetFirstOffset:
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
	cmpne	r0, #0
	moveq	r2, #1
	movne	r2, #0
	beq	.L128
	add	r3, r0, #98304
	ldr	ip, [r3]
	ldr	r0, [r3, #4]
	cmp	ip, r0
	beq	.L129
	ldr	r3, [r3, #12]
	mov	r0, r2
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L128:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L129:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetFirstOffset, .-GetFirstOffset
	.align	2
	.global	DeleteRawPacket
	.type	DeleteRawPacket, %function
DeleteRawPacket:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r0
	mov	r8, r1
	moveq	r2, #1
	movne	r2, #0
	beq	.L146
	ldr	r0, .L158
	b	.L135
.L132:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L133
.L135:
	ldr	r3, [r0, r2, asl #3]
	mov	r6, r2, asl #3
	cmp	r3, #0
	add	r1, r3, #72
	beq	.L132
	cmp	r7, r1
	bne	.L132
	cmp	r2, #0
	blt	.L133
	add	r3, r7, #98304
	str	r3, [fp, #-48]
	mov	r2, r3
	ldr	r3, [r3]
	ldr	r2, [r2, #4]
	cmp	r3, r2
	addgt	r2, r2, #1024
	rsb	r2, r3, r2
	cmp	r2, r8
	bcc	.L157
	cmp	r8, #0
	mov	r5, r3
	beq	.L139
	ldr	r9, .L158+4
	mov	r10, #0
.L140:
	mov	r4, r5, asl #7
	ldr	r2, .L158+8
	sub	r4, r4, r5, asl #5
	ldr	r1, .L158+12
	add	r4, r7, r4
	mov	r0, #26
	add	r10, r10, #1
	add	r5, r5, #1
	ldmib	r4, {r3, lr}
	ubfx	r5, r5, #0, #10
	str	lr, [sp]
	bl	dprint_vfmw
	add	r2, r9, r6
	ldr	r1, [r4, #8]
	cmp	r10, r8
	ldr	r2, [r2, #8]
	add	r2, r2, #98304
	ldr	r3, [r2, #92]
	rsb	r3, r1, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r2, #92]
	bne	.L140
	ldr	r2, [fp, #-48]
	ldr	r3, [r2]
	add	ip, r10, r3
	str	ip, [r2]
	cmp	ip, #1024
	bge	.L144
.L145:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	str	r0, [r3, #12]
.L153:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L144:
	ldr	r3, [fp, #-48]
	sub	ip, ip, #1024
	str	ip, [r3]
	b	.L145
.L139:
	ldr	r2, [fp, #-48]
	cmp	r3, #1024
	str	r3, [r2]
	ldrge	r2, [fp, #-48]
	subge	r3, r3, #1024
	strge	r3, [r2]
.L143:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L146:
	mvn	r0, #0
	b	.L153
.L157:
	mov	r3, r8
	ldr	r1, .L158+16
	mov	r0, #26
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L133:
	mov	r2, #484
	ldr	r1, .L158+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L159:
	.align	2
.L158:
	.word	.LANCHOR0+8
	.word	.LANCHOR0
	.word	.LANCHOR3+20
	.word	.LC11
	.word	.LC10
	.word	.LC9
	UNWIND(.fnend)
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	2
	.global	GetRawNumOffset
	.type	GetRawNumOffset, %function
GetRawNumOffset:
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
	clz	ip, r0
	mov	ip, ip, lsr #5
	orrs	r6, ip, r1, lsr #31
	bne	.L167
	add	r8, r0, #98304
	cmp	ip, #0
	ldr	r7, [r8]
	ldr	lr, [r8, #12]
	mov	ip, r7, asl #7
	sub	ip, ip, r7, asl #5
	add	ip, r0, ip
	ldr	r5, [ip, #8]
	rsb	r5, lr, r5
	bne	.L162
	ldr	r6, [r8, #4]
	subs	r6, r6, r7
	addmi	r6, r6, #1024
.L162:
	cmp	r1, r5
	add	r6, r7, r6
	mov	ip, r7
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r7
	orrls	lr, lr, #1
	cmp	lr, #0
	bne	.L163
	mov	r4, r7
.L164:
	add	r4, r4, #1
	mov	ip, r4, asr #31
	mov	lr, ip, lsr #22
	add	ip, r4, lr
	ubfx	ip, ip, #0, #10
	rsb	ip, lr, ip
	mov	lr, ip, asl #7
	sub	lr, lr, ip, asl #5
	add	lr, r0, lr
	ldr	r9, [lr, #8]
	add	r5, r5, r9
	cmp	r1, r5
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r4
	orrls	lr, lr, #1
	cmp	lr, #0
	beq	.L164
	cmp	r7, r4
	rsbne	r5, r9, r5
	rsbne	r5, r5, r1
	strne	r5, [r3]
	beq	.L163
.L166:
	ldr	r3, [fp, #4]
	mov	r0, #0
	str	ip, [r3]
	ldr	r3, [r8]
	rsb	r4, r3, r4
	str	r4, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L163:
	str	r1, [r3]
	mov	r4, r7
	b	.L166
.L167:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawNumOffset, .-GetRawNumOffset
	.align	2
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	clz	r3, r0
	mov	r5, r0
	mov	r3, r3, lsr #5
	orrs	ip, r3, r1, lsr #31
	bne	.L174
	cmp	r3, #0
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	bne	.L174
	add	r4, r0, #98304
	ldr	r3, [r4, #20]
	ldr	ip, [r4, #12]
	rsb	r3, ip, r3
	movs	r6, r3, asr #31
	bne	.L179
	cmp	r1, r3
	bgt	.L174
	sub	r2, fp, #40
	sub	r3, fp, #44
	str	r2, [sp]
	sub	r2, fp, #48
	bl	GetRawNumOffset
	ldr	lr, [r4]
	ldr	r7, [fp, #-48]
	movw	r2, #677
	ldr	r8, [fp, #-44]
	mov	r0, #26
	add	lr, r7, lr
	ldr	r1, .L183
	mov	r3, r7
	mov	ip, lr, asr #31
	mov	ip, ip, lsr #22
	add	lr, lr, ip
	ubfx	lr, lr, #0, #10
	rsb	ip, ip, lr
	str	ip, [fp, #-40]
	mov	lr, ip, asl #7
	sub	ip, lr, ip, asl #5
	add	ip, r5, ip
	ldrb	lr, [ip, #2]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldr	ip, [ip, #8]
	str	r7, [sp, #4]
	str	r8, [sp]
	str	ip, [sp, #8]
	bl	dprint_vfmw
	ldr	r2, [fp, #-40]
	mov	r3, r2, asl #7
	sub	r3, r3, r2, asl #5
	add	r3, r5, r3
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L175
	ldr	r1, [fp, #-48]
.L176:
	mov	r0, r5
	bl	DeleteRawPacket
	ldmia	r4, {r2, r3}
	ldr	r1, [fp, #-44]
	cmp	r2, r3
	beq	.L182
	mov	r3, r2, asl #7
	ldr	r0, [r4, #12]
	sub	r3, r3, r2, asl #5
	add	r5, r5, r3
	add	r1, r1, r0
	ldr	r3, [r5, #8]
	cmp	r1, r3
	strlt	r1, [r4, #12]
	bge	.L174
.L179:
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L174:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L175:
	ldr	r1, [r3, #8]
	movw	r2, #682
	ldr	ip, [fp, #-44]
	mov	r0, #26
	ldr	r3, [fp, #-48]
	str	r1, [sp, #4]
	str	ip, [sp]
	ldr	r1, .L183+4
	bl	dprint_vfmw
	ldr	r1, [fp, #-48]
	str	r6, [fp, #-44]
	add	r1, r1, #1
	str	r1, [fp, #-48]
	b	.L176
.L182:
	mvn	r6, #2
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L184:
	.align	2
.L183:
	.word	.LC12
	.word	.LC13
	UNWIND(.fnend)
	.size	DeleteRawLen, .-DeleteRawLen
	.align	2
	.global	DeleteLastSendRaw
	.type	DeleteLastSendRaw, %function
DeleteLastSendRaw:
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
	cmp	r0, #31
	ldmhifd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L189
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L188
	add	r4, r0, #262144
	ldr	r1, [r4, #152]
	cmp	r1, #0
	ldmlefd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #72
	bl	DeleteRawPacket
	mov	r3, #0
	str	r3, [r4, #152]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L188:
	movw	r2, #709
	ldr	r1, .L189+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L190:
	.align	2
.L189:
	.word	.LANCHOR0
	.word	.LC14
	UNWIND(.fnend)
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	2
	.global	GetRawStreamSize
	.type	GetRawStreamSize, %function
GetRawStreamSize:
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
	addne	r0, r0, #98304
	ldrne	r3, [r0, #20]
	strne	r3, [r1]
	ldrne	r0, [r0, #12]
	rsbne	r0, r0, r3
	strne	r0, [r1]
	movne	r0, r0, asr #31
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawStreamSize, .-GetRawStreamSize
	.align	2
	.global	GetRawStreamNum
	.type	GetRawStreamNum, %function
GetRawStreamNum:
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
	beq	.L197
	add	r0, r0, #98304
	ldmia	r0, {r2, r3}
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1024
	strmi	r3, [r1]
	movpl	r0, #0
	movmi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L197:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawStreamNum, .-GetRawStreamNum
	.align	2
	.global	ConfigStreamSegArray
	.type	ConfigStreamSegArray, %function
ConfigStreamSegArray:
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
	mov	r7, r2
	mov	r6, r3
	mov	r5, r1
	mov	r8, r0
	beq	.L201
	cmp	r3, #262144
	movcs	r4, #0
	movcc	r4, #1
	cmp	r2, #0
	orreq	r4, r4, #1
	cmp	r4, #0
	bne	.L201
	ldr	r3, .L202
	movw	r2, #32824
	movt	r2, 2
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	ip, r8, #163840
	mov	r0, r4
	str	r5, [ip, #24]
	str	r7, [r8]
	str	r5, [ip, #32]
	str	r5, [ip, #36]
	str	r6, [ip, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L201:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L203:
	.align	2
.L202:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	2
	.global	ResetStreamSegArray
	.type	ResetStreamSegArray, %function
ResetStreamSegArray:
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
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L209
	mov	r2, #163840
	mov	r1, #0
	add	r0, r4, #8
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #163840
	mov	r3, #0
	ldr	r2, [r0, #24]
	str	r3, [r0, #8]
	str	r3, [r0, #12]
	str	r2, [r0, #32]
	str	r2, [r0, #36]
	str	r3, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L210:
	.align	2
.L209:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	2
	.global	GetSegBufFreeSize
	.type	GetSegBufFreeSize, %function
GetSegBufFreeSize:
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
	add	r0, r0, #163840
	ldr	r3, [r0, #36]
	ldr	r2, [r0, #32]
	cmp	r3, r2
	bhi	.L215
	ldrcs	r0, [r0, #28]
	subcc	r0, r2, #1
	rsbcc	r0, r3, r0
	subcs	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L215:
	ldr	r0, [r0, #28]
	sub	r2, r2, #1
	add	r0, r2, r0
	rsb	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegBufFreeSize, .-GetSegBufFreeSize
	.align	2
	.global	CheckData
	.type	CheckData, %function
CheckData:
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
	and	ip, r1, #31
	sub	r2, ip, #30
	sub	lr, ip, #1
	cmp	ip, #19
	cmpne	r2, #1
	movls	r3, #1
	movhi	r3, #0
	cmp	lr, #12
	orrls	r3, r3, #1
	cmp	r3, #0
	addne	r2, r0, #294912
	ldrne	r3, [r2, #840]
	addne	r3, r3, #1
	strne	r3, [r2, #840]
	add	r3, r1, #79
	sub	r2, r1, #1
	uxtb	r3, r3
	cmp	r3, #4
	uxtb	r2, r2
	movhi	r3, #0
	movls	r3, #1
	cmp	r2, #183
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L218
	add	r1, r1, #73
	uxtb	r1, r1
	cmp	r1, #3
	ldmhifd	sp, {fp, sp, pc}
.L218:
	add	r0, r0, #294912
	ldr	r3, [r0, #844]
	add	r3, r3, #1
	str	r3, [r0, #844]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckData, .-CheckData
	.align	2
	.global	CheckStartCodeCnt
	.type	CheckStartCodeCnt, %function
CheckStartCodeCnt:
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
	add	r0, r0, #294912
	ldr	r3, [r0, #848]
	cmp	r3, #2
	ldmlefd	sp, {fp, sp, pc}
	tst	r1, #31
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #860]
	ldr	r2, [r0, #856]
	rsb	r1, r2, r3
	cmp	r1, #1
	beq	.L234
.L225:
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r0, #852]
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
.L226:
	cmp	r3, #1
	cmpne	r3, #20
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #840]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, #840]
	ldr	r3, [r0, #844]
	add	r3, r3, #1
	str	r3, [r0, #844]
	ldmfd	sp, {fp, sp, pc}
.L234:
	ldr	r1, [r0, #852]
	rsb	r1, r1, r2
	cmp	r1, #1
	bne	.L225
	b	.L226
	UNWIND(.fnend)
	.size	CheckStartCodeCnt, .-CheckStartCodeCnt
	.align	2
	.global	CheckStream
	.type	CheckStream, %function
CheckStream:
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
	ldr	r3, .L255
	mov	r6, r1
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #536]
	cmp	r3, #0
	cmpne	r3, #3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r4, #294912
	ldr	r3, [r5, #848]
	cmp	r3, #199
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r2, [r0]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #0
	movne	r7, r2
	bne	.L239
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L253
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r7, [r0, #3]	@ zero_extendqisi2
	andeq	r2, r7, #31
	beq	.L239
	mov	r2, r1
.L253:
	mov	r7, r2
.L239:
	ldr	lr, [r5, #856]
	add	r3, r3, #1
	ldr	ip, [r5, #860]
	mov	r1, r7
	str	r3, [r5, #848]
	mov	r0, r4
	str	lr, [r5, #852]
	str	ip, [r5, #856]
	str	r2, [r5, #860]
	bl	CheckData
	mov	r1, r7
	mov	r0, r4
	bl	CheckStartCodeCnt
	ldr	r3, [r5, #848]
	cmp	r3, #199
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #840]
	ldr	r3, [r5, #844]
	rsb	r1, r3, r2
	cmp	r1, #49
	ble	.L240
	ldr	r1, [r4, #536]
	cmp	r1, #3
	beq	.L254
.L240:
	rsb	r3, r2, r3
	cmp	r3, #49
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #536]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L255+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r6
	mov	r2, r3
	mov	r1, #124
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L254:
	ldr	r3, .L255+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #0
	mov	r1, #124
	mov	r2, r3
	mov	r0, r6
	blx	ip
	ldr	r3, [r5, #844]
	ldr	r2, [r5, #840]
	b	.L240
.L256:
	.align	2
.L255:
	.word	s_pstVfmwChan
	.word	g_event_report
	UNWIND(.fnend)
	.size	CheckStream, .-CheckStream
	.align	2
	.global	InsertStreamSeg
	.type	InsertStreamSeg, %function
InsertStreamSeg:
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
	mov	r5, r0
	mov	r6, r1
	moveq	r7, #1
	movne	r7, #0
	beq	.L259
	add	r4, r0, #163840
	ldr	r3, [r4, #12]
	ldr	r1, [r4, #8]
	add	r3, r3, #1
	mov	r0, r3, asr #31
	mov	r0, r0, lsr #21
	add	r3, r3, r0
	ubfx	r3, r3, #0, #11
	rsb	r3, r0, r3
	cmp	r3, r1
	beq	.L260
	mov	r1, r2
	ldr	r0, [r6]
	bl	CheckStream
	ldr	r8, [r4, #12]
	ldr	r0, .L261
	mov	r1, r6
	mov	r2, #80
	mov	r3, r8, asl #6
	add	r8, r3, r8, lsl #4
	ldr	r3, [r0, #52]
	add	r0, r8, #8
	add	r8, r5, r8
	add	r0, r5, r0
	blx	r3
	ldr	r1, [r4, #12]
	mov	ip, #1
	mov	r0, r7
	add	r3, r1, ip
	mov	lr, r1, asl #6
	mov	r2, r3, asr #31
	add	lr, lr, r1, lsl #4
	add	r5, r5, lr
	mov	r2, r2, lsr #21
	add	r3, r3, r2
	strb	ip, [r5, #12]
	ubfx	r3, r3, #0, #11
	str	r1, [r8, #24]
	rsb	r3, r2, r3
	str	r3, [r4, #12]
	ldr	r1, [r6, #8]
	ldr	r3, [r6, #12]
	ldr	r2, [r4, #40]
	add	r3, r3, r1
	str	r3, [r4, #36]
	ldr	r1, [r6, #12]
	ldr	r3, [r4, #44]
	add	r1, r2, r1
	ldr	r2, [r4, #48]
	str	r1, [r4, #40]
	ldr	r1, [r6, #12]
	add	r2, r2, ip
	str	r2, [r4, #48]
	add	r3, r3, r1
	str	r3, [r4, #44]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L260:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L259:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L262:
	.align	2
.L261:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	2
	.global	SCDDRV_GetStreamSeg
	.type	SCDDRV_GetStreamSeg, %function
SCDDRV_GetStreamSeg:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r0, r1
	beq	.L270
	add	r4, r5, #163840
	ldr	r3, [r4, #8]
	ldr	r1, [r4, #12]
	cmp	r1, r3
	beq	.L272
	mov	ip, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, ip, r6
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	bne	.L267
	b	.L265
.L277:
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	beq	.L265
.L267:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #21
	add	r2, r2, r3
	ubfx	r2, r2, #0, #11
	rsb	r3, r3, r2
	cmp	r1, r3
	mov	ip, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, ip, r6
	bne	.L277
.L272:
	mvn	r0, #2
.L264:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L265:
	add	r6, ip, r6
	add	r1, r6, #8
	adds	r1, r5, r1
	beq	.L272
	ldr	r3, .L278
	add	r5, r5, r6
	mov	r2, #80
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #2
	strb	r3, [r5, #12]
	mov	r0, #26
	ldr	r3, [r5, #20]
	ldr	ip, [r4, #44]
	ldr	r2, [r4, #48]
	rsb	ip, r3, ip
	ldr	r1, .L278+4
	sub	r2, r2, #1
	bic	ip, ip, ip, asr #31
	str	ip, [r4, #44]
	bic	r2, r2, r2, asr #31
	str	r2, [r4, #48]
	ldrb	ip, [r5, #13]	@ zero_extendqisi2
	ldr	r2, [r5, #16]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L270:
	mvn	r0, #0
	b	.L264
.L279:
	.align	2
.L278:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	UNWIND(.fnend)
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	2
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
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
	subs	r5, r0, #0
	mov	r4, r1
	beq	.L300
	movw	r3, #63486
	sub	r2, r1, #2048
	movt	r3, 65535
	cmp	r2, r3
	bls	.L300
	cmn	r1, #1
	add	r6, r5, #163840
	beq	.L314
	ldr	r3, [r6, #8]
	ldr	r2, [r6, #12]
	cmp	r3, r2
	bne	.L311
	b	.L288
.L291:
	add	r3, r3, #1
	ubfx	r3, r3, #0, #11
	cmp	r3, r2
	beq	.L288
.L311:
	cmp	r4, r3
	bne	.L291
	mov	r2, r3, asl #6
	add	r3, r2, r3, lsl #4
	add	r2, r5, r3
	ldrsb	r2, [r2, #12]
	cmp	r2, #2
	addeq	r3, r3, #8
	addeq	r7, r5, r3
	beq	.L285
.L288:
	mvn	r0, #2
.L310:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L314:
	ldr	r9, [r6, #8]
	ldr	r3, [r6, #12]
	cmp	r9, r3
	beq	.L288
	mov	r3, r9, asl #6
	mov	r4, r9
	add	r9, r3, r9, lsl #4
	mov	r2, r4
	add	r7, r9, #8
	add	r9, r5, r9
	ldr	r1, .L316
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r9, #20]
	add	r7, r5, r7
	cmp	r3, #0
	movne	r8, #0
	beq	.L287
.L286:
	ldr	r3, [r9, #8]
	mov	r0, #0
	ldr	r1, .L316+4
	ldrb	r2, [r3, r8]	@ zero_extendqisi2
	add	r8, r8, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #20]
	cmp	r3, r8
	movhi	r3, #1
	movls	r3, #0
	cmp	r8, #15
	movhi	r3, #0
	cmp	r3, #0
	bne	.L286
.L287:
	ldr	r1, .L316+8
	mov	r0, #0
	bl	dprint_vfmw
.L285:
	cmp	r7, #0
	beq	.L288
	ldr	r3, [r7, #12]
	mov	r2, #0
	strb	r2, [r7, #4]
	mov	r0, #26
	ldr	r2, [r7, #8]
	str	r4, [sp, #4]
	ldrb	ip, [r7, #5]	@ zero_extendqisi2
	ldr	r1, .L316+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #8]
	cmp	r3, r4
	beq	.L296
.L293:
	ldr	r2, [r7, #12]
	mov	r0, #0
	ldr	r3, [r6, #40]
	rsb	r3, r2, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r6, #40]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L294:
	ldr	r2, [r6, #12]
	cmp	r2, r4
	beq	.L297
	ldrsb	r2, [r3, #12]
	cmp	r2, #0
	bne	.L315
.L301:
	add	r4, r4, #1
	ubfx	r4, r4, #0, #11
.L296:
	mov	r3, r4, asl #6
	cmp	r4, #2048
	add	r3, r3, r4, lsl #4
	add	r3, r5, r3
	bcc	.L294
	ldr	r2, .L316+16
	mov	r0, #1
	ldr	r1, .L316+20
	bl	dprint_vfmw
	ldr	r2, [r6, #12]
	cmp	r2, r4
	bne	.L301
.L297:
	ldr	r3, [r6, #36]
	str	r2, [r6, #8]
	str	r3, [r6, #32]
	b	.L293
.L315:
	str	r4, [r6, #8]
	ldr	r3, [r3, #16]
	str	r3, [r6, #32]
	b	.L293
.L300:
	mvn	r0, #0
	b	.L310
.L317:
	.align	2
.L316:
	.word	.LC16
	.word	.LC18
	.word	.LC17
	.word	.LC19
	.word	.LANCHOR3+36
	.word	.LC20
	UNWIND(.fnend)
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	2
	.global	GetSegStreamSize
	.type	GetSegStreamSize, %function
GetSegStreamSize:
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
	addne	r3, r0, #163840
	movne	r0, #0
	mvneq	r0, #0
	ldrne	r3, [r3, #40]
	strne	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegStreamSize, .-GetSegStreamSize
	.align	2
	.global	GetSegStreamNum
	.type	GetSegStreamNum, %function
GetSegStreamNum:
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
	add	r0, r0, #163840
	ldr	r3, [r0, #12]
	ldr	r0, [r0, #8]
	rsb	r0, r0, r3
	ubfx	r0, r0, #0, #11
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegStreamNum, .-GetSegStreamNum
	.align	2
	.global	GetFreshSegStream
	.type	GetFreshSegStream, %function
GetFreshSegStream:
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
	addne	r0, r0, #163840
	ldrne	r3, [r0, #48]
	strne	r3, [r1]
	ldrne	r3, [r0, #44]
	strne	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetFreshSegStream, .-GetFreshSegStream
	.align	2
	.global	SCDDRV_PrepareSleep
	.type	SCDDRV_PrepareSleep, %function
SCDDRV_PrepareSleep:
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
	ldr	r3, .L331
	mov	r2, r0, asl #2
	add	ip, r3, r2
	ldr	r1, [ip, #324]
	cmp	r1, #0
	bne	.L330
	rsb	r2, r2, r0, lsl #6
	add	r3, r3, r2
	ldr	r0, [r3, #312]
	cmp	r0, #0
	moveq	r3, #2
	movne	r3, #1
	movne	r0, r1
	str	r3, [ip, #324]
	ldmfd	sp, {fp, sp, pc}
.L330:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L332:
	.align	2
.L331:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	2
	.global	SCDDRV_GetSleepStage
	.type	SCDDRV_GetSleepStage, %function
SCDDRV_GetSleepStage:
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
	ldr	r3, .L334
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L335:
	.align	2
.L334:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	2
	.global	SCDDRV_ForceSleep
	.type	SCDDRV_ForceSleep, %function
SCDDRV_ForceSleep:
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
	ldr	r3, .L341
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #324]
	cmp	r3, #2
	movne	r3, #2
	strne	r3, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L342:
	.align	2
.L341:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	2
	.global	SCDDRV_ExitSleep
	.type	SCDDRV_ExitSleep, %function
SCDDRV_ExitSleep:
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
	ldr	r3, .L344
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L345:
	.align	2
.L344:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	2
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
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
	cmp	r0, #31
	bhi	.L348
	ldr	r3, .L349
	mov	r2, #432
	ldr	ip, .L349+4
	movt	r2, 4
	add	r4, r3, r0, lsl #3
	mov	r1, #0
	mvn	r5, #0
	ldr	r3, [ip, #48]
	ldr	r0, [r4, #8]
	blx	r3
	ldr	r3, [r4, #8]
	mov	r0, #0
	mvn	r4, #0
	add	r3, r3, #262144
	strd	r4, [r3, #240]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L348:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L350:
	.align	2
.L349:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_ClearInst, .-SM_ClearInst
	.align	2
	.global	SM_InstInit
	.type	SM_InstInit, %function
SM_InstInit:
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
	ldr	r4, .L354
	ldr	r6, .L354+4
	add	r5, r4, #256
.L352:
	mov	r2, #8
	mov	r0, r4
	ldr	r3, [r6, #48]
	add	r4, r4, r2
	mov	r1, #0
	blx	r3
	cmp	r4, r5
	bne	.L352
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L355:
	.align	2
.L354:
	.word	.LANCHOR0+8
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_InstInit, .-SM_InstInit
	.align	2
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
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
	subs	r8, r2, #0
	mov	r5, r0
	mov	r7, r1
	beq	.L358
	cmp	r8, #1
	bne	.L370
	movw	r3, #1306
	ldr	r2, .L372
	ldr	r1, .L372+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L358:
	ldr	r4, .L372+8
	mov	r3, #49152
	movt	r3, 63683
	ldr	r2, [r4, #304]
	str	r3, [r4, #4]
	cmp	r2, #1
	beq	.L363
	ldr	r3, .L372+12
	mov	r1, r8
	mov	r2, #60
	add	r0, r4, #264
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, .L372+16
	add	r3, r5, #15
	str	r5, [r4, #264]
	bic	r3, r3, #15
	str	r8, [r4, #324]
	str	r8, [r2, #56]
	rsb	r6, r5, r3
	mov	r0, r3
	str	r3, [r4, #276]
	str	r7, [r4, #268]
	bl	MEM_Phy2Vir
	add	r3, r5, #12288
	mov	r2, #12288
	add	r3, r3, r6
	str	r2, [r4, #280]
	str	r3, [r4, #288]
	add	r5, r5, #28672
	add	r5, r5, #127
	add	r5, r5, r6
	bic	r5, r5, #127
	str	r0, [r4, #272]
	mov	r0, r3
	bl	MEM_Phy2Vir
	mov	r3, #16384
	str	r5, [r4]
	str	r3, [r4, #292]
	str	r0, [r4, #284]
	mov	r0, r5
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4, #328]
	beq	.L371
	add	r6, r6, #46592
	ldr	r2, [r4, #4]
	ldr	r3, [r4, #336]
	cmp	r7, r6
	mov	r1, #17920
	str	r1, [r4, #332]
	str	r2, [r4, #296]
	str	r3, [r4, #300]
	blt	.L363
	ldr	r3, [r4, #272]
	cmp	r3, #0
	beq	.L363
	ldr	r3, [r4, #284]
	cmp	r3, #0
	beq	.L363
	mov	r3, #1
	mov	r0, r8
	str	r3, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L370:
	ldr	r2, .L372
	mov	r0, #0
	ldr	r1, .L372+20
	bl	dprint_vfmw
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L363:
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L371:
	ldr	r2, .L372
	ldr	r1, .L372+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L373:
	.align	2
.L372:
	.word	.LANCHOR3+56
	.word	.LC22
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LC21
	.word	.LC23
	UNWIND(.fnend)
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	2
	.global	SM_CloseSCDDrv
	.type	SM_CloseSCDDrv, %function
SM_CloseSCDDrv:
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
	ldr	ip, .L384
	mov	r3, #0
	mov	lr, r3
.L376:
	ldr	r2, [ip, r3, asl #3]
	add	r3, r3, #1
	cmp	r2, #0
	add	r1, r2, #262144
	beq	.L375
	ldr	r2, [r1, #220]
	cmp	r2, #0
	beq	.L375
	ldr	r2, [r1, #208]
	cmp	r2, #0
	strle	lr, [r1, #220]
.L375:
	cmp	r3, #32
	bne	.L376
	ldr	r2, .L384+4
	mov	r1, r0, asl #6
	ldr	ip, .L384+8
	sub	r3, r1, r0, asl #2
	add	r1, r2, r1
	ldr	r0, .L384+12
	mov	r4, #0
	mov	r2, #60
	str	r4, [r1, #56]
	add	r0, r0, r3
	mov	r1, r4
	ldr	r3, [ip, #48]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L385:
	.align	2
.L384:
	.word	.LANCHOR0+8
	.word	g_VfmwGlobalStat
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+264
	UNWIND(.fnend)
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	2
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
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
	clz	r3, r1
	mov	r7, r0
	mov	r6, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L400
	ldr	r2, .L401
	add	r3, r2, r0, lsl #3
	ldr	ip, [r3, #8]
	cmn	r2, #264
	cmpne	ip, #0
	moveq	r8, #1
	movne	r8, #0
	beq	.L392
	ldr	r3, [r1, #44]
	add	r4, ip, #262144
	str	r3, [r4, #288]
	ldr	r3, [r1, #12]
	ldr	r1, [ip, #16]
	cmp	r1, r3
	addeq	r5, ip, #4
	ldreq	r9, .L401+4
	beq	.L391
	cmp	r3, #0
	beq	.L392
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L392
	ldr	r0, [r2, #288]
	mov	r3, #2048
	ldr	r1, [r2, #284]
	ldr	r9, [r2, #276]
	ldr	r5, [r2, #272]
	ldr	lr, [r2, #280]
	ldr	r2, [r2, #292]
	str	r1, [r4, #180]
	str	r9, [r4, #176]
	str	r2, [r4, #188]
	str	r5, [r4, #168]
	str	lr, [r4, #172]
	str	r0, [r4, #184]
	str	r3, [r4, #192]
	ldr	r3, [r6, #12]
	ldr	r0, [r6]
	add	r1, r3, #3
	bic	r1, r1, #3
	rsb	r3, r3, r1
	add	r1, r1, #131072
	add	r2, r3, #131072
	str	r1, [r4, #196]
	add	r2, r0, r2
	str	r2, [r4, #164]
	ldr	r0, [r6, #16]
	rsb	r3, r3, r0
	sub	r3, r3, #132096
	str	r3, [r4, #200]
	cmp	r3, #262144
	blt	.L392
	ldr	r9, .L401+4
	add	r0, ip, #98304
	add	r5, ip, #4
	add	r0, r0, #96
	bl	ConfigStreamSegArray
	mov	r2, #68
	mov	r0, r5
	ldr	r3, [r9, #52]
	mov	r1, r6
	blx	r3
	str	r8, [r4, #208]
.L391:
	ldr	r3, [r9, #52]
	mov	r0, r5
	mov	r2, #68
	mov	r1, r6
	blx	r3
	mov	r3, #2
	str	r3, [r4, #276]
	mov	r0, #0
	ldr	r3, [r6, #8]
	str	r7, [r4, #204]
	cmp	r3, #2
	moveq	r3, #3
	streq	r3, [r4, #276]
.L388:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L392:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L400:
	str	r1, [sp]
	mov	r3, r0
	movw	r2, #1399
	ldr	r1, .L401+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L388
.L402:
	.align	2
.L401:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	UNWIND(.fnend)
	.size	SM_Config, .-SM_Config
	.align	2
	.global	SM_CfgBuf
	.type	SM_CfgBuf, %function
SM_CfgBuf:
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
	cmp	r0, #31
	bhi	.L411
	cmp	r1, #0
	bne	.L412
	ldr	r2, .L413
	add	r0, r2, r0, lsl #3
	ldr	r3, [r0, #8]
	cmn	r2, #264
	cmpne	r3, #0
	moveq	r1, #1
	movne	r1, #0
	beq	.L407
	add	r3, r3, #262144
	ldr	r0, [r3, #208]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, [r2, #276]
	mov	ip, #2048
	ldr	r6, [r2, #272]
	mov	r0, r1
	ldr	r5, [r2, #280]
	ldr	r4, [r2, #288]
	ldr	lr, [r2, #284]
	ldr	r2, [r2, #292]
	str	r1, [r3, #208]
	str	r7, [r3, #176]
	str	r6, [r3, #168]
	str	r5, [r3, #172]
	str	r4, [r3, #184]
	str	lr, [r3, #180]
	str	r2, [r3, #188]
	str	ip, [r3, #192]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L407:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L411:
	mov	r3, r0
	movw	r2, #1479
	ldr	r1, .L413+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L412:
	mov	r3, r1
	movw	r2, #1486
	ldr	r1, .L413+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L414:
	.align	2
.L413:
	.word	.LANCHOR0
	.word	.LC25
	.word	.LC26
	UNWIND(.fnend)
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	2
	.global	SM_Start
	.type	SM_Start, %function
SM_Start:
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
	ldr	r3, .L420
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L419
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L419
	add	r3, r3, #262144
	ldr	r0, [r3, #220]
	cmp	r0, #0
	bne	.L419
	mov	r2, #1
	str	r2, [r3, #220]
	ldmfd	sp, {fp, sp, pc}
.L419:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L421:
	.align	2
.L420:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_Start, .-SM_Start
	.align	2
	.global	SM_Stop
	.type	SM_Stop, %function
SM_Stop:
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
	ldr	r3, .L429
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r0, #262144
	ldr	r0, [r3, #220]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #208]
	cmp	r2, #0
	movle	r0, #0
	strle	r0, [r3, #220]
	mvngt	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L430:
	.align	2
.L429:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_Stop, .-SM_Stop
	.align	2
	.global	SM_GetInfo
	.type	SM_GetInfo, %function
SM_GetInfo:
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
	cmp	r0, #31
	bhi	.L438
	ldr	r3, .L446
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L445
	add	r2, r0, #262144
	cmn	r0, #72
	add	r0, r0, #98304
	ldr	r3, [r2, #220]
	strb	r3, [r1]
	ldr	r3, [r2, #268]
	str	r3, [r1, #20]
	beq	.L434
	ldr	r3, [r0, #76]
	ldr	ip, [r0, #72]
	subs	r3, r3, ip
	addmi	r3, r3, #1024
	strmi	r3, [r1, #4]
	strpl	r3, [r1, #4]
.L436:
	ldr	r3, [r0, #92]
	str	r3, [r1, #12]
	ldr	ip, [r0, #84]
	rsb	r3, ip, r3
	str	r3, [r1, #12]
.L434:
	ldr	r3, [r2, #108]
	adds	r0, r0, #96
	ldr	ip, [r2, #104]
	movne	r0, #0
	rsb	r3, ip, r3
	ubfx	r3, r3, #0, #11
	str	r3, [r1, #8]
	ldrne	r3, [r2, #136]
	strne	r3, [r1, #16]
	ldmfd	sp, {fp, sp, pc}
.L445:
	cmp	r1, #0
	beq	.L438
	strb	r0, [r1]
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L438:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L447:
	.align	2
.L446:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_GetInfo, .-SM_GetInfo
	.align	2
	.global	GetRawNumInFrame
	.type	GetRawNumInFrame, %function
GetRawNumInFrame:
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
	add	r6, r0, #98304
	mov	r4, #1
	ldr	r3, [r6]
	mov	ip, r3, asl #5
	mov	r5, r3, asl #7
	rsb	lr, ip, r5
	add	lr, r0, lr
	ldr	lr, [lr, #8]
	str	lr, [r2]
	str	r4, [r1]
	b	.L449
.L451:
	ldr	r4, [r1]
	add	r4, r4, #1
	str	r4, [r1]
	ldr	r4, [lr, #8]
	ldr	lr, [r2]
	add	lr, lr, r4
	str	lr, [r2]
	ldr	lr, [r6, #4]
	cmp	lr, r3
	beq	.L453
	ldr	lr, [r1]
	cmp	lr, #1024
	bhi	.L453
.L449:
	rsb	ip, ip, r5
	add	r3, r3, #1
	ubfx	r3, r3, #0, #10
	ldrb	r4, [r0, ip]	@ zero_extendqisi2
	mov	r5, r3, asl #7
	mov	ip, r3, asl #5
	cmp	r4, #0
	rsb	lr, ip, r5
	add	lr, r0, lr
	bne	.L451
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L453:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawNumInFrame, .-GetRawNumInFrame
	.align	2
	.global	AdjustRawPacketVP6A
	.type	AdjustRawPacketVP6A, %function
AdjustRawPacketVP6A:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r10, [r1]
	add	ip, r0, #98304
	cmp	r10, #0
	ldr	ip, [ip]
	beq	.L459
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	add	lr, r0, lr
	ldr	r4, [lr, #8]
	cmp	r4, #2
	bgt	.L460
	mov	lr, r4
	mov	r8, #3
	mov	r5, #0
	b	.L457
.L458:
	add	lr, r0, lr
	ldr	lr, [lr, #8]
	add	r4, r4, lr
	cmp	r4, #2
	bgt	.L462
.L457:
	add	ip, ip, #1
	add	r5, r5, #1
	ubfx	ip, ip, #0, #10
	cmp	r5, r10
	rsb	r8, lr, r8
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	bne	.L458
.L459:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L462:
	mov	r9, r8, asr #31
.L456:
	rsb	r6, r7, r6
	rsb	r5, r5, r10
	add	r6, r0, r6
	str	r5, [r1]
	sub	r4, r4, #3
	mov	r0, #0
	ldrd	r6, [r6, #40]
	adds	r8, r8, r6
	adc	r9, r9, r7
	strd	r8, [r2]
	str	r4, [r3]
	ldr	r3, [fp, #4]
	str	ip, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L460:
	mov	r8, #3
	mov	r9, #0
	mov	r5, #0
	b	.L456
	UNWIND(.fnend)
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.align	2
	.global	SM_CopyRawToSeg
	.type	SM_CopyRawToSeg, %function
SM_CopyRawToSeg:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	ldr	r3, .L502
	mov	r2, r0
	str	r0, [fp, #-84]
	add	r3, r3, r2, lsl #3
	mov	r2, #0
	mov	r5, r1
	mov	r0, #0
	ldr	r4, [r3, #8]
	mov	r1, #0
	str	r2, [fp, #-64]
	cmp	r4, r2
	strd	r0, [fp, #-52]
	beq	.L482
	cmn	r4, #72
	add	r8, r4, #98304
	add	r2, r8, #96
	str	r2, [fp, #-80]
	movne	r3, #0
	moveq	r3, #1
	cmn	r8, #96
	add	r2, r4, #72
	str	r2, [fp, #-76]
	movne	r9, #0
	moveq	r9, #1
	orr	r3, r9, r3
	cmp	r5, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L482
	ldr	r10, [r8, #76]
	ldr	r3, [r8, #72]
	cmp	r10, r3
	beq	.L497
	mov	r2, r3, asl #5
	mov	r7, r3, asl #7
	str	r2, [fp, #-72]
	mov	r1, #1
	mov	lr, r2
	rsb	r2, r2, r7
	add	r2, r4, r2
	str	r1, [fp, #-56]
	mov	r0, r7
	ldr	r6, [r2, #80]
	b	.L466
.L468:
	add	r1, r1, #1
	ldr	ip, [ip, #80]
	cmp	r1, #1024
	add	r6, r6, ip
	movls	r2, #0
	movhi	r2, #1
	cmp	r3, r10
	orreq	r2, r2, #1
	cmp	r2, #0
	bne	.L497
.L466:
	rsb	r2, lr, r0
	add	r3, r3, #1
	add	r2, r4, r2
	ubfx	r3, r3, #0, #10
	ldrb	r2, [r2, #72]	@ zero_extendqisi2
	mov	lr, r3, asl #5
	mov	r0, r3, asl #7
	cmp	r2, #0
	rsb	ip, lr, r0
	add	ip, r4, ip
	bne	.L468
	cmp	r9, #0
	str	r1, [fp, #-56]
	addne	r2, r4, #262144
	bne	.L479
	ldr	r10, .L502+4
	mov	r2, #163840
	mov	r1, r9
	add	r0, r8, #104
	ldr	r3, [r10, #48]
	blx	r3
	add	r2, r4, #262144
	ldr	r3, [r2, #120]
	str	r9, [r2, #104]
	str	r9, [r2, #108]
	str	r9, [r2, #112]
	str	r3, [r2, #128]
	str	r3, [r2, #132]
.L479:
	ldr	r3, [r2, #124]
	cmp	r3, r6
	blt	.L500
	ldr	r3, [fp, #-72]
	ldr	r0, [r4, #12]
	rsb	r3, r3, r7
	ldr	r9, [r2, #120]
	add	r3, r4, r3
	ldr	r2, [r8, #72]
	sub	r0, r0, #12
	ldr	r8, [r8, #96]
	ldr	r1, [r3, #80]
	clz	r0, r0
	str	r2, [fp, #-60]
	cmp	r1, #0
	mov	r0, r0, lsr #5
	ldrd	r2, [r3, #112]
	moveq	r0, #0
	cmp	r0, #0
	str	r1, [fp, #-64]
	strd	r2, [fp, #-52]
	bne	.L471
.L474:
	str	r9, [r5, #8]
	mov	r0, r9
	bl	MEM_Phy2Vir
	ldr	r3, [fp, #-72]
	mov	r1, #1
	ldr	ip, [fp, #-56]
	rsb	r7, r3, r7
	add	r7, r4, r7
	cmp	ip, #0
	str	r0, [r5]
	rsb	r3, r0, r8
	str	r3, [r5, #12]
	ldrd	r2, [r7, #136]
	strd	r2, [r5, #24]
	ldrd	r2, [r7, #136]
	strd	r2, [r5, #32]
	ldrd	r2, [r7, #120]
	strb	r1, [r5, #5]
	strd	r2, [r5, #40]
	ldrd	r2, [r7, #128]
	strd	r2, [r5, #48]
	ldr	r3, [r7, #92]
	str	r3, [r5, #56]
	ldr	r3, [r7, #96]
	str	r3, [r5, #60]
	ldr	r3, [r7, #100]
	str	r3, [r5, #64]
	ldr	r3, [r7, #104]
	str	r3, [r5, #68]
	beq	.L473
	cmp	r8, #0
	beq	.L497
	ldrd	r2, [fp, #-52]
	orrs	r3, r2, r3
	ldrne	r10, .L502+4
	movne	r7, #0
	bne	.L476
	b	.L497
.L477:
	cmp	r8, #0
	beq	.L497
	orrs	r3, r0, r1
	beq	.L497
.L476:
	mov	r0, #2
	add	r7, r7, #1
	bl	VCTRL_RecordPosTime
	ldr	r3, [r10, #52]
	ldr	r2, [fp, #-64]
	mov	r0, r8
	ldr	r1, [fp, #-52]
	blx	r3
	mov	r0, #3
	bl	VCTRL_RecordPosTime
	ldr	r1, [fp, #-64]
	mov	r0, #0
	bl	VCTRL_RecordData
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-64]
	add	r0, r2, #1
	ldr	ip, [fp, #-56]
	mov	r3, r2, asl #7
	ubfx	r0, r0, #0, #10
	sub	r2, r3, r2, asl #5
	str	r0, [fp, #-60]
	add	r2, r4, r2
	mov	r3, r0, asl #7
	sub	r3, r3, r0, asl #5
	add	r8, r8, r1
	ldrb	r0, [r2, #73]	@ zero_extendqisi2
	add	r3, r4, r3
	ldr	r2, [r5, #12]
	cmp	ip, r7
	strb	r0, [r5, #6]
	add	r1, r2, r1
	str	r1, [r5, #12]
	ldrd	r0, [r3, #112]
	ldr	r3, [r3, #80]
	strd	r0, [fp, #-52]
	str	r3, [fp, #-64]
	bhi	.L477
	ldr	r0, [r5]
.L473:
	cmp	r0, #0
	beq	.L501
	ldr	r2, [fp, #-84]
	mov	r1, r5
	ldr	r0, [fp, #-80]
	bl	InsertStreamSeg
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L500:
	mov	r2, r6
	ldr	r1, .L502+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L497
	movw	r2, #1713
	ldr	r1, .L502+12
	mov	r0, #0
	bl	dprint_vfmw
.L497:
	mvn	r0, #3
.L494:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L471:
	sub	r2, fp, #60
	sub	r3, fp, #64
	str	r2, [sp]
	sub	r1, fp, #56
	sub	r2, fp, #52
	ldr	r0, [fp, #-76]
	bl	AdjustRawPacketVP6A
	cmp	r0, #0
	beq	.L474
	b	.L497
.L482:
	mvn	r0, #0
	b	.L494
.L501:
	movw	r3, #1774
	ldr	r2, .L502+16
	ldr	r1, .L502+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L494
.L503:
	.align	2
.L502:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	.word	.LANCHOR3+72
	.word	.LC29
	UNWIND(.fnend)
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	2
	.global	SCDDRV_IsSCDByPass
	.type	SCDDRV_IsSCDByPass, %function
SCDDRV_IsSCDByPass:
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
	bics	r3, r0, #16
	beq	.L509
	sub	r3, r0, #2
	cmp	r0, #6
	cmpne	r3, #1
	movls	r3, #1
	movhi	r3, #0
	bls	.L508
	cmp	r0, #1
	beq	.L510
.L506:
	subs	r0, r0, #15
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L510:
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L506
.L509:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L508:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.align	2
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
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
	ldr	r5, .L513
	mov	r6, r0
	mov	r7, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r4, .L513+4
	mov	r0, #0
	ldr	r3, [r4, #16]
	blx	r3
	ldr	r3, [r4, #44]
	ldr	r2, [r5, r6, asl #2]
	ldr	r1, [r7, #12]
	ldr	r0, [r7]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L514:
	.align	2
.L513:
	.word	vfmw_save_seg_file
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	2
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
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
	ldr	r3, .L528
	mov	r7, r0
	mov	r6, r1
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #8]
	cmp	r4, #0
	cmpne	r1, #0
	beq	.L519
	add	r1, r4, #28
	ldr	r0, [r4, #12]
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L526
.L517:
	add	r0, r4, #98304
	mov	r1, r6
	add	r0, r0, #96
	add	r4, r4, #262144
	bl	SCDDRV_GetStreamSeg
	subs	r5, r0, #0
	beq	.L527
	ldr	r3, [r4, #268]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #268]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L526:
	mov	r1, r6
	mov	r0, r7
	bl	SM_CopyRawToSeg
	cmp	r0, #0
	beq	.L517
	add	r4, r4, #262144
	ldr	r1, .L528+4
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r3, [r4, #268]
	mvn	r0, #6
	add	r3, r3, #1
	str	r3, [r4, #268]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L527:
	mov	r0, r7
	mov	r1, r6
	str	r5, [r4, #268]
	bl	SCDDRV_SaveStreamSeg
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L519:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L529:
	.align	2
.L528:
	.word	.LANCHOR0
	.word	.LC30
	UNWIND(.fnend)
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	2
	.global	SM_ReleaseStreamSeg
	.type	SM_ReleaseStreamSeg, %function
SM_ReleaseStreamSeg:
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
	ldr	r3, .L532
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L531
	add	r0, r0, #98304
	add	r0, r0, #96
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseStreamSeg
.L531:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L533:
	.align	2
.L532:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	2
	.global	SM_GiveThreadEvent
	.type	SM_GiveThreadEvent, %function
SM_GiveThreadEvent:
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
	ldr	r3, .L535
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L536:
	.align	2
.L535:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	2
	.global	CalcInstBlockTime
	.type	CalcInstBlockTime, %function
CalcInstBlockTime:
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
	ldr	r3, .L542
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	cmp	r5, #0
	add	r3, r4, #262144
	mov	r1, r0
	bne	.L541
	ldr	r2, [r3, #236]
	cmp	r0, r2
	strls	r5, [r3, #232]
	rsbhi	r0, r2, r0
	strls	r1, [r3, #236]
	strhi	r0, [r3, #232]
	movls	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L541:
	mov	r2, #0
	str	r1, [r3, #236]
	mov	r0, r2
	str	r2, [r3, #232]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L543:
	.align	2
.L542:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	2
	.global	SCDDRV_IsChanDec
	.type	SCDDRV_IsChanDec, %function
SCDDRV_IsChanDec:
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
	ldr	r3, .L547
	ldr	r2, [r3, #312]
	cmp	r2, #1
	ldreq	r3, [r3, #308]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L548:
	.align	2
.L547:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_IsChanDec, .-SCDDRV_IsChanDec
	.align	2
	.global	SCDDRV_GetRawStreamStatus
	.type	SCDDRV_GetRawStreamStatus, %function
SCDDRV_GetRawStreamStatus:
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
	ldmeqfd	sp, {fp, sp, pc}
	add	r0, r0, #98304
	ldr	r3, [r0, #20]
	str	r3, [r1]
	ldr	ip, [r0, #12]
	rsb	r3, ip, r3
	str	r3, [r1]
	ldmia	r0, {r1, r3}
	subs	r3, r3, r1
	addmi	r3, r3, #1024
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_GetRawStreamStatus, .-SCDDRV_GetRawStreamStatus
	.align	2
	.global	GetFreeSegBufSize
	.type	GetFreeSegBufSize, %function
GetFreeSegBufSize:
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
	cmpne	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetFreeSegBufSize.part.4
	UNWIND(.fnend)
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.align	2
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
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
	mov	r6, r2
	mov	r4, r0
	mov	r5, r1
	bne	.L561
.L558:
	ldr	r3, [r5]
	add	r0, r4, #163840
	cmp	r3, #78
	subhi	r3, r3, #79
	movls	r3, #0
	str	r3, [r5]
	ldr	r3, [r0, #12]
	ldr	r2, [r0, #8]
	rsb	r3, r2, r3
	ubfx	r3, r3, #0, #11
	rsb	r3, r3, #2048
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L561:
	bl	GetFreeSegBufSize.part.4
	b	.L558
	UNWIND(.fnend)
	.size	SCDDRV_GetSegStreamStatus, .-SCDDRV_GetSegStreamStatus
	.align	2
	.global	SCDDRV_IsRawStreamNotEnough
	.type	SCDDRV_IsRawStreamNotEnough, %function
SCDDRV_IsRawStreamNotEnough:
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
	cmpne	r0, #3
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsRawStreamNotEnough, .-SCDDRV_IsRawStreamNotEnough
	.align	2
	.global	SCDDRV_IsFreeSegSlotNotEnough
	.type	SCDDRV_IsFreeSegSlotNotEnough, %function
SCDDRV_IsFreeSegSlotNotEnough:
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
	cmp	r0, #512
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsFreeSegSlotNotEnough, .-SCDDRV_IsFreeSegSlotNotEnough
	.align	2
	.global	SCDDRV_IsFreeSegBufNotEnough
	.type	SCDDRV_IsFreeSegBufNotEnough, %function
SCDDRV_IsFreeSegBufNotEnough:
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
	cmp	r0, r1, lsr #3
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsFreeSegBufNotEnough, .-SCDDRV_IsFreeSegBufNotEnough
	.align	2
	.global	SCDDRV_CheckConditionOfStartSCD
	.type	SCDDRV_CheckConditionOfStartSCD, %function
SCDDRV_CheckConditionOfStartSCD:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	r4, r1
	mov	r5, r3
	beq	.L570
	add	lr, r0, #98304
	ldr	r3, [lr, #20]
	str	r3, [r2]
	ldr	r1, [lr, #12]
	rsb	r3, r1, r3
	str	r3, [r2]
	ldmia	lr, {r3, ip}
	rsb	ip, r3, ip
	cmp	ip, #0
	blt	.L567
	moveq	ip, #1
	movne	ip, #0
.L568:
	ldr	r3, [r2]
	cmp	r3, #3
	orrls	ip, ip, #1
	cmp	ip, #0
	bne	.L570
	ldr	r2, [fp, #4]
	mov	r1, r5
	mov	r0, r4
	bl	SCDDRV_GetSegStreamStatus
	ldr	r3, [fp, #4]
	ldr	r3, [r3]
	cmp	r3, #512
	bls	.L571
	add	r4, r4, #163840
	ldr	r3, [r5]
	ldr	r2, [r4, #28]
	cmp	r3, r2, lsr #3
	mvnls	r0, #5
	movhi	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L567:
	cmn	ip, #1024
	movne	ip, #0
	moveq	ip, #1
	b	.L568
.L570:
	mvn	r0, #4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L571:
	mvn	r0, #5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_CheckConditionOfStartSCD, .-SCDDRV_CheckConditionOfStartSCD
	.align	2
	.global	SCDDRV_SetCtrlReg
	.type	SCDDRV_SetCtrlReg, %function
SCDDRV_SetCtrlReg:
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
	add	r3, r0, #262144
	ldr	ip, [r0, #12]
	mov	lr, #1
	strb	lr, [r1, #2]
	ldr	r2, [r3, #176]
	sub	r4, ip, #6
	clz	r4, r4
	cmp	ip, lr
	cmpne	ip, #15
	str	r2, [r1, #4]
	mov	r4, r4, lsr #5
	ldr	r2, [r3, #168]
	str	r2, [r1, #8]
	ldr	r2, [r3, #184]
	str	r2, [r1, #16]
	ldr	r5, [r3, #192]
	ldr	r2, [r3, #276]
	mul	r2, r2, r5
	str	r2, [r1, #20]
	ldr	r2, [r3, #120]
	str	r2, [r1, #24]
	ldr	r2, [r3, #124]
	ldr	r5, [r3, #120]
	add	r2, r2, r5
	str	r2, [r1, #28]
	ldr	r2, [r3, #132]
	strb	lr, [r1]
	add	r2, r2, #3
	bic	r2, r2, #3
	str	r2, [r1, #32]
	ldr	r2, [r0, #40]
	str	r4, [r1, #60]
	str	r2, [r1, #44]
	beq	.L578
	cmp	r4, #0
	bne	.L576
	sub	r2, ip, #2
	cmp	r2, lr
	bhi	.L574
.L576:
	strb	lr, [r1, #1]
	b	.L577
.L578:
	mov	ip, #0
.L574:
	mov	r2, #0
	strb	r2, [r1, #1]
.L577:
	mov	r2, #1
	str	ip, [r1, #36]
	str	r2, [r1, #40]
	str	r2, [r1, #48]
	str	r2, [r1, #52]
	ldr	r3, [r3, #424]
	str	r3, [r1, #56]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_SetCtrlReg, .-SCDDRV_SetCtrlReg
	.align	2
	.global	SCDDRV_RecordStartState
	.type	SCDDRV_RecordStartState, %function
SCDDRV_RecordStartState:
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
	add	r4, r0, #262144
	cmp	r1, r2
	str	r1, [r4, #248]
	movls	r3, #1
	str	r2, [r4, #252]
	movhi	r3, #0
	strb	r3, [r0, #2]
	mov	r1, #1
	ldr	r3, .L582
	mov	r2, #0
	str	r1, [r4, #212]
	strb	r2, [r0, #3]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r4, #272]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L583:
	.align	2
.L582:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	2
	.global	SCD_ConfigReg
	.type	SCD_ConfigReg, %function
SCD_ConfigReg:
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
	ldr	ip, .L591
	mov	r5, r0
	mov	r0, r3
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L590
	cmp	r5, #4
	beq	.L589
	ldr	r6, .L591+4
	mov	r4, r2, asl #2
.L586:
	add	r2, r6, r4
	ldr	r0, [r2, #4]
	add	r0, r5, r0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L590:
	mov	r3, r1
	mov	r2, r5
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Record_RegData
.L589:
	ldr	r6, .L591+4
	mov	r4, r2, asl #2
	cmp	r1, #0
	add	r3, r6, r4
	ldr	r0, [r3, #4]
	add	r0, r0, #4
	bne	.L587
	bl	MEM_ReadPhyWord
	uxth	r1, r0
	b	.L586
.L587:
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
	b	.L586
.L592:
	.align	2
.L591:
	.word	g_HalDisable
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	2
	.global	ParseMpeg4UniqueUpMsg
	.type	ParseMpeg4UniqueUpMsg, %function
ParseMpeg4UniqueUpMsg:
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
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r0, #1
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [r1]
	ldr	r3, [r2]
	ldrb	r0, [r1]	@ zero_extendqisi2
	mov	r3, r3, lsr #31
	bfi	r0, r3, #1, #1
	strb	r0, [r1]
	ldrh	r0, [r2, #10]
	ldrb	r3, [r1]	@ zero_extendqisi2
	bfi	r3, r0, #2, #1
	strb	r3, [r1]
	ldr	r3, [r2, #8]
	ldrb	r0, [r1]	@ zero_extendqisi2
	ubfx	r3, r3, #4, #3
	bfi	r0, r3, #3, #4
	strb	r0, [r1]
	ldr	r3, [r2, #8]
	ldrh	r2, [r1]
	and	r3, r3, #7
	bfi	r2, r3, #7, #4
	strh	r2, [r1]	@ movhi
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ParseMpeg4UniqueUpMsg, .-ParseMpeg4UniqueUpMsg
	.align	2
	.global	ConvertByteOrder
	.type	ConvertByteOrder, %function
ConvertByteOrder:
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
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, r2, r3, asl #24
	orr	r3, r3, r1
	orr	r0, r3, r0, asl #8
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ConvertByteOrder, .-ConvertByteOrder
	.align	2
	.global	CheckSegValid
	.type	CheckSegValid, %function
CheckSegValid:
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
	beq	.L602
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L604
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L604
	add	r1, r1, #163840
	ldr	r2, [r1, #36]
	ldr	r3, [r1, #32]
	cmp	r2, r3
	bhi	.L606
	ldrcs	r3, [r1, #28]
	subcc	r3, r3, #1
	rsbcc	r3, r2, r3
	subcs	r3, r3, #1
.L600:
	ldr	r2, [r0, #12]
	cmp	r2, r3
	mvnhi	r0, #6
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L606:
	ldr	r1, [r1, #28]
	sub	r3, r3, #1
	add	r3, r3, r1
	rsb	r3, r2, r3
	b	.L600
.L604:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L602:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckSegValid, .-CheckSegValid
	.align	2
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	mov	r4, r3
	mov	r5, r2
	sub	r3, fp, #44
	sub	r2, fp, #40
	str	r2, [sp]
	sub	r2, fp, #48
	mov	ip, #0
	mov	r6, r0
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	str	ip, [fp, #-40]
	bl	GetRawNumOffset
	ldr	r2, [fp, #-40]
	mov	r3, r2, asl #7
	sub	r3, r3, r2, asl #5
	add	r0, r6, r3
	ldrd	r6, [r0, #64]
	strd	r6, [r4, #24]
	ldrd	r8, [r0, #48]
	strd	r8, [r4, #40]
	ldrd	r2, [r0, #64]
	strd	r2, [r4, #32]
	ldrd	r2, [r0, #56]
	strd	r2, [r4, #48]
	ldr	r3, [r0, #20]
	str	r3, [r4, #56]
	ldr	r3, [r0, #24]
	str	r3, [r4, #60]
	ldr	r3, [r0, #28]
	str	r3, [r4, #64]
	ldr	r3, [r0, #32]
	str	r3, [r4, #68]
	ldrd	r0, [r5]
	cmp	r7, r1
	cmpeq	r6, r0
	beq	.L610
	strd	r6, [r5]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L610:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [r4, #24]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegPts, .-GetSegPts
	.align	2
	.global	IsVopHeader
	.type	IsVopHeader, %function
IsVopHeader:
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
	beq	.L616
	cmp	r0, #2
	movne	r0, #0
	beq	.L617
.L613:
	mov	r2, #0
	movt	r2, 65025
	cmp	r1, r2
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L616:
	mov	r3, #0
	movt	r3, 46593
	rsb	r0, r3, r1
	clz	r0, r0
	mov	r0, r0, lsr #5
	b	.L613
.L617:
	ubfx	r3, r1, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L613
	UNWIND(.fnend)
	.size	IsVopHeader, .-IsVopHeader
	.align	2
	.global	CorrectSegPhyAddr
	.type	CorrectSegPhyAddr, %function
CorrectSegPhyAddr:
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
	cmp	r1, r0
	orrcc	r0, r1, #-2147483648
	movcs	r0, r1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectSegPhyAddr, .-CorrectSegPhyAddr
	.align	2
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
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
	add	r5, r0, #262144
	sub	ip, r2, #1
	cmp	ip, #0
	add	r0, r0, #98304
	ldr	r3, [r5, #108]
	mov	lr, ip
	ldr	r9, [r5, #104]
	rsb	r9, r9, r3
	ubfx	r9, r9, #0, #11
	rsb	r9, r9, #2048
	blt	.L630
	ldr	r7, [r5, #276]
	mov	r6, #0
	mov	r10, r6
	ldr	r4, [r5, #120]
	ldr	r8, [r0, #96]
	movt	r6, 65025
	mov	r7, r7, asl #2
	ldr	r5, [r5, #224]
	movt	r10, 46593
	mla	r1, r7, ip, r1
	b	.L629
.L633:
	cmp	r5, #2
	beq	.L632
	cmp	r3, r6
	beq	.L627
.L628:
	sub	lr, lr, #1
	rsb	r1, r7, r1
	cmn	lr, #1
	mov	r2, ip
	beq	.L630
	sub	ip, ip, #1
.L629:
	ldr	r3, [r1]
	bic	r3, r3, #-2147483648
	cmp	r3, r4
	orrcc	r3, r3, #-2147483648
	cmp	r5, #1
	rsb	r3, r4, r3
	ldr	r3, [r8, r3]
	rsbeq	r2, r10, r3
	clzeq	r2, r2
	moveq	r2, r2, lsr #5
	bne	.L633
.L625:
	cmp	r3, r6
	beq	.L627
	cmp	r2, #1
	bne	.L628
.L627:
	cmp	r9, ip
	mov	r2, ip
	bcs	.L630
	sub	ip, ip, #1
	b	.L628
.L632:
	ubfx	r2, r3, #16, #8
	sub	r2, r2, #128
	cmp	r2, #3
	movhi	r2, #0
	movls	r2, #1
	b	.L625
.L630:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetNextVop, .-GetNextVop
	.align	2
	.global	SetPushRawOverState
	.type	SetPushRawOverState, %function
SetPushRawOverState:
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
	ldr	r3, [r0, #8]
	str	r1, [r0, #8]
	cmp	r1, #2
	cmpeq	r3, #3
	moveq	r3, #1
	movne	r3, #0
	mvneq	r3, #6
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetPushRawOverState, .-SetPushRawOverState
	.align	2
	.global	ProcessExceptionalStartCodeNum
	.type	ProcessExceptionalStartCodeNum, %function
ProcessExceptionalStartCodeNum:
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
	movw	r2, #2541
	mov	r4, r0
	mov	r3, r1
	mov	r0, #0
	ldr	r1, .L638
	bl	dprint_vfmw
	add	r0, r4, #72
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawPacket
.L639:
	.align	2
.L638:
	.word	.LC31
	UNWIND(.fnend)
	.size	ProcessExceptionalStartCodeNum, .-ProcessExceptionalStartCodeNum
	.global	__aeabi_uidiv
	.align	2
	.global	GetValidStartCodeNum
	.type	GetValidStartCodeNum, %function
GetValidStartCodeNum:
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
	ldr	r0, [r0, #24]
	bl	__aeabi_uidiv
	ldr	r3, [r4, #12]
	cmp	r0, r3
	movcs	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetValidStartCodeNum, .-GetValidStartCodeNum
	.align	2
	.global	ProcessNoSeg
	.type	ProcessNoSeg, %function
ProcessNoSeg:
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
	add	r3, r0, #262144
	mov	r4, r0
	ldr	r2, [r3, #248]
	ldr	r0, [r3, #252]
	ldr	r5, [r3, #156]
	cmp	r2, r0
	movle	r2, #0
	movgt	r2, #1
	cmp	r1, #0
	strb	r2, [r4]
	bne	.L642
	cmp	r5, #3
	subhi	r1, r5, #3
.L643:
	add	r0, r4, #72
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawLen
.L642:
	ldr	r2, [r3, #180]
	ldr	r3, [r3, #124]
	ldr	r1, [r2, #4]
	add	r3, r3, r3, lsl #1
	add	r2, r3, #3
	cmp	r3, #0
	bic	r1, r1, #-2147483648
	movlt	r3, r2
	rsb	r2, r1, r5
	cmp	r2, r3, asr #2
	bls	.L643
	ldr	r1, .L645
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r5
	add	r0, r4, #72
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawLen
.L646:
	.align	2
.L645:
	.word	.LC32
	UNWIND(.fnend)
	.size	ProcessNoSeg, .-ProcessNoSeg
	.align	2
	.global	ProcessNotMpeg4ScdUpMsg
	.type	ProcessNotMpeg4ScdUpMsg, %function
ProcessNotMpeg4ScdUpMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 120
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
	add	r5, r0, #262144
	str	r1, [fp, #-136]
	mov	r3, r0
	ldr	r1, [r5, #276]
	add	r9, r0, #98304
	str	r2, [fp, #-152]
	sub	r0, fp, #124
	ldr	r2, [r5, #180]
	add	r3, r3, #72
	str	r1, [fp, #-156]
	mov	r1, r1, asl #2
	str	r1, [fp, #-140]
	mov	lr, r1
	mov	r1, #0
	mov	ip, r2
	str	r2, [fp, #-160]
	mov	r8, r1
	mov	r2, #80
	str	r3, [fp, #-144]
	add	r10, ip, lr
	add	r3, r9, #96
	mov	r6, ip
	str	r3, [fp, #-132]
	mov	r7, r8
	bl	memset
	b	.L648
.L664:
	rsb	r3, r2, r3
	ldr	r1, [r9, #96]
	cmp	r3, #3
	rsb	r4, r4, r2
	add	r4, r1, r4
	str	r2, [fp, #-116]
	str	r3, [fp, #-112]
	mov	r2, #1
	str	r4, [fp, #-124]
	strb	r2, [fp, #-119]
	ble	.L663
	ldr	r1, [fp, #-132]
	sub	r0, fp, #124
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L657
	ldr	r1, [r6, #4]
	sub	r3, fp, #124
	add	r2, r5, #240
	ldr	r0, [fp, #-144]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	cmp	r0, #0
	bne	.L657
.L653:
	ldr	r3, [fp, #-140]
	ldr	r7, [fp, #-128]
	add	r6, r6, r3
	add	r8, r8, r3
.L648:
	ldr	r3, [fp, #-136]
	cmp	r7, r3
	beq	.L657
	ldr	r2, [r6]
	add	r1, r7, #1
	ldr	r4, [r5, #120]
	ldr	r3, [r10, r8]
	bic	r2, r2, #-2147483648
	cmp	r4, r2
	str	r1, [fp, #-128]
	bic	r3, r3, #-2147483648
	orrhi	r2, r2, #-2147483648
	cmp	r4, r3
	orrhi	r3, r3, #-2147483648
	cmp	r2, r3
	bls	.L664
	rsb	r4, r4, r3
	ldr	r3, [fp, #-152]
	ldr	lr, [r5, #120]
	rsb	r3, r2, r3
	ldr	r0, [r9, #96]
	add	r1, r4, r3
	rsb	lr, lr, r2
	cmp	r1, #3
	str	r2, [fp, #-116]
	str	r1, [fp, #-112]
	add	r2, r0, lr
	ldr	r0, [r5, #104]
	str	r2, [fp, #-124]
	ldr	r2, [r5, #108]
	ble	.L665
	rsb	r2, r0, r2
	str	r3, [fp, #-148]
	ubfx	r2, r2, #0, #11
	rsb	r2, r2, #2048
	cmp	r2, #2
	bls	.L657
	ldr	r1, [fp, #-132]
	sub	r0, fp, #124
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L657
	ldr	r3, [fp, #-148]
	cmp	r4, #0
	str	r3, [fp, #-112]
	bne	.L659
	mov	r3, #1
	strb	r3, [fp, #-119]
	ldr	r1, [r6, #4]
	add	r2, r5, #240
	ldr	r0, [fp, #-144]
	sub	r3, fp, #124
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	b	.L653
.L659:
	strb	r0, [fp, #-119]
	sub	r3, fp, #124
	ldr	r1, [r6, #4]
	add	r2, r5, #240
	ldr	r0, [fp, #-144]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	ldr	lr, [r5, #120]
	ldr	r7, [r9, #96]
	sub	r1, fp, #124
	ldr	r2, [r5, #204]
	mov	r3, #1
	ldr	r0, [fp, #-132]
	str	r4, [fp, #-112]
	str	lr, [fp, #-116]
	str	r7, [fp, #-124]
	strb	r3, [fp, #-119]
	bl	InsertStreamSeg
	b	.L653
.L665:
	mov	r3, r1
	movw	r2, #2641
	ldr	r1, .L666
	mov	r0, #0
	bl	dprint_vfmw
	b	.L653
.L663:
	movw	r2, #2610
	ldr	r1, .L666
	mov	r0, #0
	bl	dprint_vfmw
	b	.L653
.L657:
	cmp	r7, #0
	ble	.L647
	ldr	r3, [fp, #-156]
	ldr	r0, [fp, #-144]
	mul	r7, r3, r7
	ldr	r3, [fp, #-160]
	add	r7, r7, #1
	ldr	r1, [r3, r7, asl #2]
	bic	r1, r1, #-2147483648
	bl	DeleteRawLen
.L647:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L667:
	.align	2
.L666:
	.word	.LC33
	UNWIND(.fnend)
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	2
	.global	GetMeg4ModeFlag
	.type	GetMeg4ModeFlag, %function
GetMeg4ModeFlag:
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
	add	r10, r0, #262144
	subs	r7, r1, #0
	ldr	r6, [r10, #276]
	ldr	r4, [r10, #180]
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r9, .L690
	mov	r6, r6, asl #2
	mov	r5, #0
	movw	r8, #438
	b	.L679
.L675:
	add	r5, r5, #1
	add	r4, r4, r6
	cmp	r5, r7
	beq	.L688
.L679:
	ldr	r0, [r4]
	ldr	r3, [r10, #120]
	bic	r0, r0, #-2147483648
	cmp	r3, r0
	orrhi	r0, r0, #-2147483648
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L689
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, r0, asl #8
	cmp	r3, r8
	cmpne	r3, #288
	bic	r3, r3, #1020
	bic	r3, r3, #3
	moveq	r1, #1
	moveq	r2, #0
	streq	r1, [r10, #224]
	streq	r2, [r10, #228]
	cmp	r3, #32768
	bne	.L675
	ldr	r3, [r10, #224]
	cmp	r3, #1
	beq	.L676
.L678:
	add	r5, r5, #1
	mov	r3, #2
	cmp	r5, r7
	str	r3, [r10, #224]
	add	r4, r4, r6
	bne	.L679
.L688:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L676:
	ldr	r3, [r10, #228]
	add	r3, r3, #1
	str	r3, [r10, #228]
	cmp	r3, #30
	bls	.L675
	ldr	ip, [r9]
	cmp	ip, #0
	beq	.L678
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r10, #204]
	blx	ip
	b	.L678
.L689:
	movw	r3, #2696
	ldr	r2, .L690+4
	ldr	r1, .L690+8
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L691:
	.align	2
.L690:
	.word	g_event_report
	.word	.LANCHOR3+88
	.word	.LC34
	UNWIND(.fnend)
	.size	GetMeg4ModeFlag, .-GetMeg4ModeFlag
	.align	2
	.global	ProcessMpeg4ScdUpMsg
	.type	ProcessMpeg4ScdUpMsg, %function
ProcessMpeg4ScdUpMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #212)
	sub	sp, sp, #212
	add	r6, r0, #262144
	mov	r4, r0
	mov	r8, r1
	ldr	r3, [r6, #276]
	mov	r10, r2
	str	r1, [fp, #-240]
	sub	r0, fp, #204
	str	r2, [fp, #-236]
	mov	r1, #0
	mov	r9, r3
	str	r3, [fp, #-244]
	ldr	r3, [r6, #180]
	mov	r2, #80
	mov	r7, r3
	str	r3, [fp, #-248]
	bl	memset
	mov	r2, #80
	mov	r1, #0
	sub	r0, fp, #124
	bl	memset
	ldr	r0, [r6, #120]
	bl	MEM_Phy2Vir
	mov	r5, r0
	mov	r0, r10
	bl	MEM_Phy2Vir
	ldr	r3, .L735
	mov	r1, r5
	mov	r2, #4
	mov	r10, r9, asl #2
	mov	r5, r7
	ldr	r3, [r3, #52]
	mov	r9, r5
	blx	r3
	mov	r1, r8
	mov	r0, r4
	bl	GetMeg4ModeFlag
	add	ip, r4, #98304
	mov	r2, r8
	mov	r1, r7
	mov	r0, r4
	add	r3, r5, r10
	mov	r7, ip
	str	r3, [fp, #-220]
	str	ip, [fp, #-224]
	bl	GetNextVop
	mov	r8, #0
	add	r3, r4, #72
	add	r5, r5, #4
	str	r3, [fp, #-228]
	add	r3, r7, #96
	mov	r7, r8
	str	r3, [fp, #-212]
	str	r0, [fp, #-216]
	b	.L693
.L730:
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	beq	.L697
	ldr	r3, [fp, #-112]
	sub	r0, fp, #124
	ldr	r1, [fp, #-212]
	add	r4, r3, r4
	str	r4, [fp, #-112]
	bl	CheckSegValid
	subs	r4, r0, #0
	bne	.L701
	ldr	r2, [r6, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-212]
	bl	InsertStreamSeg
	ldr	r3, .L735
	mov	r1, r4
	mov	r2, #80
	ldr	ip, [r3, #48]
	str	r0, [fp, #-232]
	sub	r0, fp, #124
	blx	ip
	ldr	r3, [fp, #-232]
	cmp	r3, #0
	bne	.L701
.L702:
	ldr	r7, [fp, #-208]
	add	r9, r9, r10
	add	r5, r5, r10
	add	r8, r8, r10
.L693:
	ldr	r3, [fp, #-216]
	cmp	r7, r3
	beq	.L701
	ldr	r3, [fp, #-220]
	ldr	r2, [r5, #-4]
	ldr	r1, [r6, #120]
	ldr	r0, [r3, r8]
	bic	r2, r2, #-2147483648
	cmp	r1, r2
	add	r3, r7, #1
	bic	r0, r0, #-2147483648
	orrhi	r2, r2, #-2147483648
	cmp	r1, r0
	str	r3, [fp, #-208]
	orrhi	r0, r0, #-2147483648
	rsb	r4, r2, r0
	cmp	r4, #3
	bgt	.L730
	sub	r3, r4, #1
	cmp	r3, #2
	bls	.L731
	ldr	r3, [fp, #-236]
	rsb	r4, r1, r0
	ldr	r0, [fp, #-224]
	rsb	r1, r1, r2
	rsb	ip, r2, r3
	str	r2, [fp, #-196]
	add	r3, r4, ip
	ldr	r2, [r6, #108]
	ldr	r0, [r0, #96]
	cmp	r3, #3
	str	r3, [fp, #-192]
	add	r1, r0, r1
	str	r1, [fp, #-204]
	ldr	r1, [r6, #104]
	ble	.L732
	rsb	r2, r1, r2
	str	ip, [fp, #-232]
	ubfx	r2, r2, #0, #11
	rsb	r2, r2, #2048
	cmp	r2, #2
	bls	.L701
	ldr	r1, [fp, #-212]
	sub	r0, fp, #204
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L701
	cmp	r4, #0
	ldr	r3, [r6, #224]
	ldr	ip, [fp, #-232]
	bne	.L712
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	mov	r0, #1
	bfieq	r3, r4, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r2, [r5, #-4]
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r2, r2, lsr #31
	bfi	r1, r2, #1, #1
	strb	r1, [fp, #-132]
	ldrh	lr, [r5, #6]
	add	r2, r6, #240
	uxtb	r1, r1
	bfi	r1, lr, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	lr, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	lr, r1, #3, #4
	strb	lr, [fp, #-132]
	ldr	r1, [r5, #4]
	str	ip, [fp, #-192]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	strb	r0, [fp, #-199]
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	ldr	r0, [fp, #-228]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r6, #204]
	sub	r1, fp, #204
	ldr	r0, [fp, #-212]
	bl	InsertStreamSeg
	b	.L702
.L697:
	ldr	r3, [fp, #-224]
	sub	r0, fp, #204
	str	r2, [fp, #-196]
	str	r4, [fp, #-192]
	ldr	ip, [r3, #96]
	rsb	r3, r1, r2
	ldr	r1, [fp, #-212]
	add	r3, ip, r3
	str	r3, [fp, #-204]
	mov	r3, #1
	strb	r3, [fp, #-199]
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L701
	ldr	r3, [r6, #224]
	add	r2, r6, #240
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r1, [r5, #-4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ldr	r0, [fp, #-228]
	mov	r1, r1, lsr #31
	bfi	ip, r1, #1, #1
	strb	ip, [fp, #-132]
	uxtb	r1, ip
	ldrh	ip, [r5, #6]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r6, #204]
	sub	r1, fp, #204
	ldr	r0, [fp, #-212]
	bl	InsertStreamSeg
	cmp	r0, #0
	beq	.L702
.L701:
	cmp	r7, #0
	ble	.L733
	ldr	r3, [fp, #-244]
	ldr	r0, [fp, #-228]
	mul	r7, r3, r7
	ldr	r3, [fp, #-248]
	add	r7, r7, #1
	ldr	r1, [r3, r7, asl #2]
	bic	r1, r1, #-2147483648
	bl	DeleteRawLen
.L692:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L731:
	str	r2, [fp, #-232]
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-232]
	cmp	r0, #0
	beq	.L734
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r0, asl #8
	cmp	r3, #256
	beq	.L702
	ldr	r3, [r6, #224]
	mov	r0, #1
	cmp	r3, #1
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-52]
	sub	r3, fp, #124
	ldr	r1, [r5, #-4]
	ldrb	ip, [fp, #-52]	@ zero_extendqisi2
	mov	r1, r1, lsr #31
	bfi	ip, r1, #1, #1
	strb	ip, [fp, #-52]
	uxtb	r1, ip
	ldrh	ip, [r5, #6]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-52]
	ldr	r1, [r5, #4]
	ldrb	ip, [fp, #-52]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-52]
	ldr	r1, [r5, #4]
	ldrh	lr, [fp, #-52]
	and	r1, r1, #7
	ldr	ip, [r6, #120]
	bfi	lr, r1, #7, #4
	ldr	r1, [fp, #-224]
	rsb	ip, ip, r2
	str	r2, [fp, #-116]
	strb	r0, [fp, #-119]
	add	r2, r6, #240
	ldr	r1, [r1, #96]
	str	r4, [fp, #-112]
	add	ip, r1, ip
	strh	lr, [fp, #-52]	@ movhi
	str	ip, [fp, #-124]
	ldr	r1, [r9, #4]
	ldr	r0, [fp, #-228]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	b	.L702
.L712:
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	mov	r0, #0
	ldr	r2, [r5, #-4]
	sub	r3, fp, #204
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r2, r2, lsr #31
	bfi	r1, r2, #1, #1
	strb	r1, [fp, #-132]
	ldrh	lr, [r5, #6]
	add	r2, r6, #240
	uxtb	r1, r1
	bfi	r1, lr, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	lr, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	lr, r1, #3, #4
	strb	lr, [fp, #-132]
	ldr	r1, [r5, #4]
	str	ip, [fp, #-192]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	strb	r0, [fp, #-199]
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	ldr	r0, [fp, #-228]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r7, [fp, #-212]
	ldr	r2, [r6, #204]
	sub	r1, fp, #204
	mov	r0, r7
	bl	InsertStreamSeg
	ldr	r3, [fp, #-224]
	ldr	ip, [r6, #120]
	sub	r1, fp, #204
	ldr	r2, [r6, #204]
	mov	r0, r7
	ldr	lr, [r3, #96]
	mov	r3, #1
	str	r4, [fp, #-192]
	str	ip, [fp, #-196]
	str	lr, [fp, #-204]
	strb	r3, [fp, #-199]
	bl	InsertStreamSeg
	b	.L702
.L732:
	mov	r2, #2832
	ldr	r1, .L735+4
	mov	r0, #0
	bl	dprint_vfmw
	b	.L702
.L733:
	ldr	r3, [fp, #-216]
	ldr	r2, [fp, #-240]
	clz	r3, r3
	cmp	r2, #2048
	mov	r3, r3, lsr #5
	movls	r3, #0
	cmp	r3, #0
	beq	.L692
	ldr	r1, .L735+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r0, [fp, #-228]
	mov	r1, #1
	bl	DeleteRawPacket
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L734:
	movw	r3, #2804
	ldr	r2, .L735+12
	ldr	r1, .L735+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L692
.L736:
	.align	2
.L735:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC36
	.word	.LANCHOR3+104
	.word	.LC35
	UNWIND(.fnend)
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	2
	.global	SCDDRV_SaveRawStream
	.type	SCDDRV_SaveRawStream, %function
SCDDRV_SaveRawStream:
	UNWIND(.fnstart)
	@ args = 96, pretend = 8, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	UNWIND(.pad #8)
	sub	sp, sp, #8
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-12)
	sub	fp, ip, #12
	ldr	r5, .L748
	mov	r6, r0
	stmib	fp, {r2, r3}
	mov	r7, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L737
	ldr	r4, .L748+4
	mov	r0, #0
	ldr	r8, [r1, #12]
	ldr	r3, [r4, #16]
	blx	r3
	ldrb	r3, [fp, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L739
	add	r1, r7, #28
	mov	r0, r8
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L747
.L740:
	ldr	r2, [r5, r6, asl #2]
	ldr	r3, [r4, #44]
	ldr	r1, [fp, #12]
	ldr	r0, [fp, #44]
	blx	r3
.L739:
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
.L737:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L747:
	ldr	r3, [r4, #44]
	mov	r1, #4
	ldr	r2, [r5, r6, asl #2]
	add	r0, fp, #12
	blx	r3
	b	.L740
.L749:
	.align	2
.L748:
	.word	vfmw_save_str_file
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	2
	.global	FillEopRawStream
	.type	FillEopRawStream, %function
FillEopRawStream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #112)
	sub	sp, sp, #112
	ldr	r3, .L765
	mov	r5, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L765+4
	sub	r0, fp, #120
	ldr	r4, [r3, #8]
	bl	memcpy
	cmp	r5, #0
	beq	.L763
	ldr	r3, [r4, #12]
	cmp	r3, #16
	bhi	.L753
	mov	r1, #1
	movw	r0, #65406
	mov	r2, r1, asl r3
	bfi	r0, r1, #16, #16
	ands	r4, r2, r0
	bne	.L754
	tst	r2, #1
	beq	.L753
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	add	r1, r3, #15
	cmp	r1, r2
	bhi	.L764
	ldr	ip, .L765+8
	sub	r1, fp, #120
	ldr	r0, [r5, #40]
	mov	r2, #15
	ldr	ip, [ip, #52]
	add	r0, r3, r0
	blx	ip
	ldr	r3, [r5, #8]
	mov	r0, r4
	add	r3, r3, #15
	str	r3, [r5, #8]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L754:
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	cmp	r3, r2
	bhi	.L759
	mov	r0, #0
.L760:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L753:
	ldr	r2, .L765+12
	mov	r0, #0
	ldr	r1, .L765+16
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L760
.L759:
	mov	r1, #0
.L756:
	stmia	sp, {r1, r2}
	mov	r0, #0
	ldr	r2, .L765+12
	ldr	r1, .L765+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L760
.L764:
	mov	r1, #15
	b	.L756
.L763:
	mov	r0, r5
	ldr	r2, .L765+12
	ldr	r1, .L765+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L760
.L766:
	.align	2
.L765:
	.word	.LANCHOR0
	.word	.LANCHOR3+128
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+228
	.word	.LC38
	.word	.LC39
	.word	.LC37
	UNWIND(.fnend)
	.size	FillEopRawStream, .-FillEopRawStream
	.align	2
	.global	FillEosRawStream
	.type	FillEosRawStream, %function
FillEosRawStream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #112)
	sub	sp, sp, #112
	ldr	r3, .L789
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L789+4
	sub	r0, fp, #120
	ldr	r5, [r3, #8]
	bl	memcpy
	cmp	r4, #0
	beq	.L787
	ldr	r3, [r5, #12]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L770
.L772:
	.word	.L771
	.word	.L773
	.word	.L774
	.word	.L775
	.word	.L785
	.word	.L785
	.word	.L781
	.word	.L770
	.word	.L785
	.word	.L785
	.word	.L785
	.word	.L785
	.word	.L785
	.word	.L785
	.word	.L785
	.word	.L771
	.word	.L777
	.word	.L785
.L771:
	sub	r1, fp, #120
	mov	r5, #15
.L776:
	ldr	r3, [r4, #8]
	cmp	r5, r3
	bhi	.L788
	ldr	r3, .L789+8
	mov	r2, r5
	ldr	r0, [r4, #40]
	ldr	r3, [r3, #52]
	blx	r3
	str	r5, [r4, #8]
.L785:
	mov	r0, #0
.L783:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L781:
	mov	r5, #15
	sub	r1, fp, #100
	b	.L776
.L773:
	ldr	r3, [r5, #28]
	cmp	r3, #1
	bne	.L785
	sub	r1, fp, #100
	mov	r5, #15
	b	.L776
.L774:
	mov	r5, #19
	sub	r1, fp, #80
	b	.L776
.L775:
	mov	r5, #16
	sub	r1, fp, #60
	b	.L776
.L777:
	mov	r5, #16
	sub	r1, fp, #40
	b	.L776
.L770:
	ldr	r2, .L789+12
	mov	r0, #0
	ldr	r1, .L789+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L788:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, r5
	ldr	r2, .L789+12
	ldr	r1, .L789+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L783
.L787:
	mov	r0, r4
	ldr	r2, .L789+12
	ldr	r1, .L789+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L783
.L790:
	.align	2
.L789:
	.word	.LANCHOR0
	.word	.LANCHOR3+248
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+348
	.word	.LC38
	.word	.LC40
	.word	.LC37
	UNWIND(.fnend)
	.size	FillEosRawStream, .-FillEosRawStream
	.align	2
	.global	FillVC1ExtraData
	.type	FillVC1ExtraData, %function
FillVC1ExtraData:
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
	mov	r4, r1
	ldr	r1, [r0, #28]
	mov	r6, r0
	cmp	r1, #1
	beq	.L801
	ldr	r3, [r4, #76]
	ands	r5, r3, #128
	bne	.L802
	add	r7, r0, #262144
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #80]
	ldr	r0, [r7, #292]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L803
	ldr	r6, .L808
	ldr	r1, [r4, #40]
	ldr	r3, [r6, #56]
	add	r0, r1, r0
	blx	r3
	ldr	r3, [r6, #52]
	ldr	r2, [r7, #292]
	add	r1, r7, #296
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r2, [r7, #292]
	ldr	r3, [r4, #8]
	mov	r0, r5
	add	r3, r3, r2
	str	r3, [r4, #8]
.L795:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L802:
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #80]
	cmp	r2, #116
	add	r3, r2, #12
	movle	r0, #0
	movgt	r0, #1
	cmp	r3, r1
	movls	r5, r0
	orrhi	r5, r0, #1
	cmp	r5, #0
	bne	.L804
	ldr	r7, .L808
	ldr	r1, [r4, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r7, #52]
	add	r1, r4, #84
	mov	r2, #4
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r7, #52]
	mov	r2, #4
	add	r1, r4, #88
	add	r0, r0, r2
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r7, #48]
	mov	r1, r5
	mov	r2, #4
	add	r0, r0, #12
	blx	r3
	add	r3, r6, #262144
	mov	r2, #16
	add	r0, r3, #296
	str	r2, [r4, #8]
	str	r2, [r3, #292]
	ldr	r3, [r7, #52]
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #40]
	blx	r3
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L801:
	ldr	r2, [r4, #76]
	ands	r5, r2, #128
	bne	.L805
	ldrb	r0, [r4, #72]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L795
	add	r6, r6, #262144
	ldr	r2, [r4, #8]
	ldr	ip, [r4, #80]
	ldr	r0, [r6, #292]
	add	r3, r2, r0
	cmp	r3, ip
	bhi	.L806
	ldr	r7, .L808
	ldr	r1, [r4, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, r0
	blx	r3
	ldr	r3, [r7, #52]
	ldr	r2, [r6, #292]
	add	r1, r6, #296
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r2, [r6, #292]
	ldr	r3, [r4, #8]
	mov	r0, r5
	add	r3, r3, r2
	str	r3, [r4, #8]
	b	.L795
.L805:
	ldr	r2, [r4, #8]
	cmp	r2, #128
	bgt	.L807
	ldr	r1, .L808
	add	r3, r0, #262144
	add	r0, r3, #296
	str	r2, [r3, #292]
	ldr	r3, [r1, #52]
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L804:
	str	r1, [sp]
	mov	r0, #1
	mov	r1, #128
	ldr	r2, .L808+4
	str	r1, [sp, #4]
	ldr	r1, .L808+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L795
.L803:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L808+4
	ldr	r1, .L808+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L795
.L807:
	mov	r3, r2
	mov	r0, r1
	ldr	r2, .L808+4
	mov	r1, #128
	str	r1, [sp]
	ldr	r1, .L808+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L795
.L806:
	mov	r0, r1
	str	ip, [sp]
	ldr	r2, .L808+4
	ldr	r1, .L808+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L795
.L809:
	.align	2
.L808:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+368
	.word	.LC43
	.word	.LC42
	.word	.LC41
	UNWIND(.fnend)
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	2
	.global	FillDIVX3ExtraData
	.type	FillDIVX3ExtraData, %function
FillDIVX3ExtraData:
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
	ldr	r2, [r1, #8]
	mov	r4, r1
	ldr	r1, [r1, #80]
	add	r3, r2, #8
	cmp	r3, r1
	bhi	.L813
	ldr	r5, .L814
	ldr	r1, [r4, #40]
	ldr	r3, [r5, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r5, #52]
	mov	r2, #4
	add	r1, r4, #84
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r5, #52]
	mov	r2, #4
	add	r1, r4, #88
	add	r0, r0, r2
	blx	r3
	ldr	r3, [r4, #8]
	mov	r0, #0
	add	r3, r3, #8
	str	r3, [r4, #8]
.L812:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L813:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L814+4
	ldr	r1, .L814+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L812
.L815:
	.align	2
.L814:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+388
	.word	.LC44
	UNWIND(.fnend)
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	2
	.global	FillREAL8ExtraData
	.type	FillREAL8ExtraData, %function
FillREAL8ExtraData:
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
	ldr	r3, [r1, #76]
	mov	r6, r1
	ands	r5, r3, #128
	beq	.L817
	ldr	r3, [r1, #8]
	cmp	r3, #128
	bgt	.L821
	ldr	r2, .L823
	add	r4, r0, #262144
	add	r0, r4, #296
	str	r3, [r4, #292]
	ldr	r3, [r2, #52]
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L817:
	add	r4, r0, #262144
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #80]
	ldr	r0, [r4, #292]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L822
	ldr	r7, .L823
	ldr	r1, [r6, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, r0
	blx	r3
	ldr	r3, [r7, #52]
	ldr	r2, [r4, #292]
	add	r1, r4, #296
	ldr	r0, [r6, #40]
	blx	r3
	ldr	r2, [r4, #292]
	ldr	r3, [r6, #8]
	mov	r0, r5
	add	r3, r3, r2
	str	r3, [r6, #8]
.L819:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L822:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L823+4
	ldr	r1, .L823+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L819
.L821:
	mov	r1, #128
	ldr	r2, .L823+4
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L823+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L819
.L824:
	.align	2
.L823:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+408
	.word	.LC45
	.word	.LC41
	UNWIND(.fnend)
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	2
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
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
	clz	r3, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L831
	ldr	r2, [r1, #8]
	cmp	r2, #0
	ble	.L834
	ldr	r2, .L836
	add	r0, r2, r0, lsl #3
	ldr	r0, [r0, #8]
	ldr	r2, [r0, #12]
	cmp	r2, #5
	beq	.L828
	cmp	r2, #8
	beq	.L829
	cmp	r2, #1
	beq	.L835
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L829:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillREAL8ExtraData
.L828:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillDIVX3ExtraData
.L835:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillVC1ExtraData
.L831:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L834:
	mov	r3, r2
	ldr	r1, .L836+4
	ldr	r2, .L836+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L837:
	.align	2
.L836:
	.word	.LANCHOR0
	.word	.LC46
	.word	.LANCHOR3+428
	UNWIND(.fnend)
	.size	FillExtraData, .-FillExtraData
	.align	2
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	mov	r6, r1
	mov	r7, r0
	bl	VCTRL_GetStreamInterface
	ldr	r5, .L853
	mov	r2, #12
	mov	r1, #0
	ldr	r3, [r5, #48]
	mov	r4, r0
	sub	r0, fp, #144
	blx	r3
	cmp	r4, #0
	beq	.L850
	mov	r1, r4
	ldr	r3, [r5, #52]
	mov	r2, #12
	sub	r0, fp, #144
	blx	r3
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #132
	mov	r2, #96
	ldr	r6, .L853+4
	blx	r3
	ldr	r3, [r4, #8]
	mov	r8, r7, asl #3
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L841
	add	r4, r6, r8
	ldr	r3, [r4, #8]
	ldr	r3, [r3, #52]
	cmp	r3, #1
	beq	.L851
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r3, [r5, #24]
	mov	r1, r7
	mov	r0, #1
	blx	r3
	ldr	r3, [r4, #8]
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L844
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
.L844:
	ldr	r3, [r5, #28]
	mov	r0, #1
	mov	r1, r7
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
.L843:
	cmp	r4, #0
	mvnne	r4, #6
.L841:
	add	r6, r6, r8
	ldr	r0, [r6, #8]
	cmp	r0, #0
	movne	r0, r4
	beq	.L852
.L840:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L851:
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
	b	.L843
.L850:
	mov	r2, r7
	mov	r0, r4
	ldr	r1, .L853+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L840
.L852:
	mov	r3, r7
	movw	r2, #3771
	ldr	r1, .L853+12
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L840
.L854:
	.align	2
.L853:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC47
	.word	.LC48
	UNWIND(.fnend)
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	2
	.global	DeleteRawPacketInBuffer
	.type	DeleteRawPacketInBuffer, %function
DeleteRawPacketInBuffer:
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
	cmp	r0, #31
	mov	r8, r0
	bhi	.L871
	ldr	r10, .L875
	mov	r9, r0, asl #3
	add	r3, r10, r9
	ldr	r6, [r3, #8]
	cmp	r6, #0
	beq	.L867
	cmp	r1, #0
	beq	.L872
.L858:
	adds	r3, r6, #72
	str	r3, [fp, #-52]
	beq	.L867
	add	r3, r6, #98304
	str	r3, [fp, #-56]
	ldr	r7, [r3, #72]
	ldr	r4, [r3, #80]
	cmp	r7, r4
	addlt	r7, r7, #1024
	rsb	r3, r4, r7
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L867
	mov	r7, #0
	mov	r3, r9
	mov	r9, r7
	mov	r7, r3
	b	.L862
.L874:
	ldr	r3, [fp, #-48]
	cmp	r9, r3
	beq	.L873
.L862:
	mov	r5, r4, asl #7
	ldr	r2, .L875+4
	sub	r5, r5, r4, asl #5
	ldr	r1, .L875+8
	add	lr, r6, r5
	mov	r0, #26
	add	r4, r4, #1
	add	r9, r9, #1
	ldr	r3, [lr, #76]
	ubfx	r4, r4, #0, #10
	ldr	lr, [lr, #80]
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-52]
	mov	r0, r8
	add	r1, r3, r5
	bl	ReleaseRawStreamData
	add	r3, r10, r7
	ldr	r3, [r3, #8]
	cmp	r3, #0
	bne	.L874
	mvn	r0, #6
.L857:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L872:
	add	r3, r6, #262144
	ldr	r3, [r3, #220]
	cmp	r3, #0
	bne	.L858
.L867:
	mvn	r0, #0
	b	.L857
.L873:
	ldr	r3, [fp, #-56]
	ldr	r4, [r3, #80]
	add	r4, r4, r9
	cmp	r4, #1024
	strlt	r4, [r3, #80]
	subge	r4, r4, #1024
	ldrge	r3, [fp, #-56]
	movlt	r0, #0
	movge	r0, #0
	strge	r4, [r3, #80]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L871:
	mov	r2, r0
	ldr	r1, .L875+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L857
.L876:
	.align	2
.L875:
	.word	.LANCHOR0
	.word	.LANCHOR3+444
	.word	.LC50
	.word	.LC49
	UNWIND(.fnend)
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	2
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #212)
	sub	sp, sp, #212
	cmp	r0, #31
	mov	r7, r0
	bhi	.L888
	ldr	r6, .L899
	mov	r10, r0, asl #3
	add	r3, r6, r10
	ldr	r5, [r3, #8]
	cmp	r5, #0
	beq	.L879
	ldr	r3, [r6, #308]
	cmp	r3, r0
	bne	.L881
	mov	lr, #0
	movw	r3, #1211
	ldr	r2, .L899+4
	mov	r0, #22
	ldr	r1, .L899+8
	str	lr, [r6, #312]
	bl	dprint_vfmw
.L881:
	ldr	r8, .L899+12
	add	r4, r5, #262144
	mov	r2, #68
	add	r1, r5, #4
	sub	r0, fp, #240
	add	r9, r4, #296
	ldr	r3, [r8, #52]
	add	r6, r6, r10
	blx	r3
	ldr	ip, [r4, #220]
	ldr	r3, [r8, #52]
	mov	r1, r9
	sub	r0, fp, #172
	mov	r2, #128
	str	ip, [fp, #-248]
	ldr	ip, [r4, #292]
	str	ip, [fp, #-252]
	blx	r3
	ldr	r3, [r6, #8]
	cmp	r3, #0
	beq	.L882
	add	r3, r3, #262144
	ldr	r2, [r3, #220]
	cmp	r2, #0
	bne	.L897
.L882:
	adds	r6, r5, #72
	beq	.L883
.L898:
	add	r2, r5, #98304
	ldr	r3, [r2, #76]
	ldr	r1, [r2, #72]
	subs	r1, r3, r1
	addmi	r1, r1, #1024
.L887:
	mov	r0, r6
	bl	DeleteRawPacket
	mov	r1, #1
	mov	r0, r7
	bl	DeleteRawPacketInBuffer
	mov	r2, #432
	movt	r2, 4
	ldr	r3, [r8, #48]
	mov	r1, #0
	mov	r0, r5
	blx	r3
	mvn	r2, #0
	mvn	r3, #0
	mov	ip, #2
	strd	r2, [r4, #240]
	sub	r1, fp, #240
	str	ip, [r4, #276]
	mov	r0, r7
	bl	SM_Config
	ldr	r3, [fp, #-248]
	sub	r1, fp, #172
	mov	r0, r9
	sub	r3, r3, #1
	mov	r2, #128
	cmp	r3, #1
	movls	r3, #1
	movhi	r3, #0
	str	r3, [r4, #220]
	ldr	r3, [fp, #-252]
	str	r3, [r4, #292]
	ldr	r3, [r8, #52]
	blx	r3
	mov	r0, #0
.L895:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L897:
	ldr	r2, [r3, #208]
	cmp	r2, #0
	movle	r2, #0
	strle	r2, [r3, #220]
	adds	r6, r5, #72
	bne	.L898
.L883:
	ldr	r1, .L899+16
	movw	r3, #1229
	ldr	r2, .L899+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, r6
	b	.L887
.L888:
	mvn	r0, #0
	b	.L895
.L879:
	mov	r0, r5
	movw	r2, #1201
	ldr	r1, .L899+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L895
.L900:
	.align	2
.L899:
	.word	.LANCHOR0
	.word	.LANCHOR3+468
	.word	.LC52
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC53
	.word	.LC51
	UNWIND(.fnend)
	.size	SM_Reset, .-SM_Reset
	.align	2
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
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
	ldr	r8, .L943
	mov	r10, r0, asl #3
	ldr	r6, .L943+4
	add	r3, r8, r10
	mov	r5, r0
	mov	r9, r1
	mov	r2, #12
	ldr	r4, [r3, #8]
	sub	r0, fp, #56
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	cmp	r4, #0
	beq	.L934
	mov	r0, r5
	bl	VCTRL_GetStreamInterface
	subs	r7, r0, #0
	beq	.L936
	ldr	r3, [r6, #52]
	sub	r0, fp, #56
	mov	r2, #12
	mov	r1, r7
	blx	r3
	ldr	r3, [r7, #4]
	cmp	r3, #0
	beq	.L934
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L937
	ldr	r3, .L943+8
	mov	r0, #0
	ldr	r2, [r6, #16]
	ldr	r7, [r3, r5, asl #2]
	str	r3, [fp, #-64]
	cmp	r7, #0
	addne	r7, r7, #294912
	ldrne	r7, [r7, #836]
	blx	r2
	ldr	r3, [fp, #-64]
	ldr	r2, .L943+4
	ldr	r3, [r3, r5, asl #2]
	cmp	r3, #0
	beq	.L909
	add	r3, r3, #294912
	ldr	r3, [r3, #836]
	cmp	r3, r7
	bne	.L938
.L909:
	ldr	r3, [fp, #-52]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	add	r8, r8, r10
	blx	r3
	ldr	r3, [r6, #12]
	mov	r7, r0
	mov	r0, #0
	blx	r3
	ldr	r0, [r8, #8]
	cmp	r0, #0
	beq	.L939
.L907:
	cmp	r7, #0
	bne	.L934
	ldrb	r6, [r9, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L940
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L941
.L912:
	add	r4, r4, #98304
	ldr	r2, [r9, #8]
	mov	r0, #0
	ldr	r3, [r4, #92]
	add	r3, r3, r2
	str	r3, [r4, #92]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L941:
	mov	r1, r9
	mov	r0, r5
	bl	FillExtraData
	cmp	r0, #0
	beq	.L914
	mov	r2, r5
	ldr	r1, .L943+12
	mov	r0, r7
	bl	dprint_vfmw
	mov	r1, r9
	ldr	r0, [fp, #-56]
	bl	ReleaseRawStreamData
	cmp	r0, #0
	beq	.L934
	mov	r0, r7
	ldr	r1, .L943+16
	bl	dprint_vfmw
.L934:
	mvn	r0, #6
.L932:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L937:
	ldr	r3, [fp, #-52]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	blx	r3
	mov	r7, r0
	b	.L907
.L940:
	mov	r1, r9
	mov	r0, r5
	bl	FillEosRawStream
	cmp	r0, #0
	bne	.L942
	mov	r1, r6
	mov	r0, r5
	bl	VCTRL_SetLastFrameState
	b	.L912
.L914:
	add	r3, r4, #262144
	ldr	r3, [r3, #288]
	cmp	r3, #0
	beq	.L912
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L912
	mov	r0, r5
	mov	r1, r9
	bl	FillEopRawStream
	b	.L912
.L938:
	ldr	r3, [r2, #12]
	mov	r0, #0
	blx	r3
	mvn	r0, #6
	b	.L932
.L936:
	mov	r2, r5
	ldr	r1, .L943+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L932
.L942:
	mov	r2, r5
	mov	r0, r7
	ldr	r1, .L943+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L932
.L939:
	mov	r3, r5
	movw	r2, #3675
	ldr	r1, .L943+28
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L932
.L944:
	.align	2
.L943:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC57
	.word	.LC58
	.word	.LC54
	.word	.LC56
	.word	.LC55
	UNWIND(.fnend)
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	2
	.global	ReleaseSegArrayPackets
	.type	ReleaseSegArrayPackets, %function
ReleaseSegArrayPackets:
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
	cmp	r1, #2048
	mov	r4, r1
	mov	r7, r0
	mov	r5, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r1, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r0, #163840
	mov	r6, #2
.L948:
	mov	r3, r4, asl #6
	mov	r1, r4
	add	r3, r3, r4, lsl #4
	mov	r0, r7
	add	r3, r7, r3
	strb	r6, [r3, #12]
	ldr	ip, [r3, #20]
	ldr	r2, [r8, #44]
	ldr	r3, [r8, #48]
	rsb	r2, ip, r2
	sub	r3, r3, #1
	bic	r2, r2, r2, asr #31
	str	r2, [r8, #44]
	bic	r3, r3, r3, asr #31
	str	r3, [r8, #48]
	bl	ReleaseStreamSeg
	add	r3, r4, #1
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #21
	add	r3, r3, r4
	ubfx	r3, r3, #0, #11
	rsb	r4, r4, r3
	cmp	r5, r4
	bne	.L948
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.align	2
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
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
	ldrd	r2, [r1]
	add	r8, r0, #163840
	mov	r5, r0
	mov	r9, r1
	ldr	r4, [r8, #8]
	mov	r6, r2
	mov	r7, r3
	ldr	ip, [r8, #12]
	ldrd	r2, [r1, #8]
	str	r4, [r8, #16]
	strd	r2, [fp, #-52]
.L951:
	mov	r3, r4, asl #6
	cmp	r4, ip
	add	r3, r3, r4, lsl #4
	mov	r1, r4
	add	r3, r5, r3
	mov	r0, r5
	add	r10, r3, #40
	beq	.L962
	ldrsb	r2, [r3, #12]
	cmp	r2, #1
	bne	.L954
	ldrd	r2, [r3, #40]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	addeq	r3, r4, #1
	beq	.L961
	cmp	r7, r3
	add	r1, r4, #1
	cmpeq	r6, r2
	mov	r3, r1, asr #31
	bls	.L957
	str	r4, [r8, #16]
	mov	r4, r3, lsr #21
	add	r1, r1, r4
	ubfx	r1, r1, #0, #11
	rsb	r4, r4, r1
	b	.L951
.L954:
	bl	ReleaseStreamSeg
	ldr	ip, [r8, #12]
	add	r3, r4, #1
.L961:
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #21
	add	r3, r3, r4
	ubfx	r3, r3, #0, #11
	rsb	r4, r4, r3
	b	.L951
.L957:
	beq	.L963
	bcs	.L951
	ldr	ip, [r8, #16]
	mvn	r2, #0
	mov	r3, ip, asl #6
	add	r3, r3, ip, lsl #4
	add	r3, r5, r3
	ldrd	r0, [r3, #40]
	mvn	r3, #0
	cmp	r1, r3
	cmpeq	r0, r2
	streq	r4, [r8, #16]
	moveq	ip, r4
	beq	.L960
	cmp	r7, r1
	cmpeq	r6, r0
	bls	.L960
	subs	r6, r6, r0
	sbc	r7, r7, r1
	mov	r0, r6
	mov	r1, r7
	ldrd	r6, [fp, #-52]
	cmp	r7, r1
	cmpeq	r6, r0
	strcc	r4, [r8, #16]
	movcc	ip, r4
.L960:
	mov	r2, ip
	mov	r0, r5
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	ldr	r2, [r8, #16]
	mov	r0, #0
	mov	r3, r2, asl #6
	add	r3, r3, r2, lsl #4
	add	r5, r5, r3
	ldrd	r2, [r5, #40]
	strd	r2, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L962:
	mov	r2, r4
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L963:
	mov	r2, r4
	mov	r0, r5
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	ldrd	r2, [r10]
	mov	r0, #0
	strd	r2, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	SM_SeekPtsInSegArray, .-SM_SeekPtsInSegArray
	.align	2
	.global	SM_SeekPtsInRawArray
	.type	SM_SeekPtsInRawArray, %function
SM_SeekPtsInRawArray:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	ldr	ip, .L1000
	str	r2, [fp, #-64]
	mov	r8, r0
	add	ip, ip, r2, lsl #3
	str	r1, [fp, #-72]
	str	r3, [fp, #-76]
	ldr	r2, [ip, #8]
	cmp	r2, #0
	str	r2, [fp, #-68]
	beq	.L983
	cmp	r3, #1
	mov	r3, r1
	ldrd	r2, [r3, #8]
	ldrd	r0, [r1]
	strd	r2, [fp, #-92]
	movne	r3, #0
	strd	r0, [fp, #-60]
	strne	r3, [fp, #-80]
	beq	.L994
.L966:
	add	r9, r8, #98304
	mvn	r6, #0
	mvn	r7, #0
	strd	r6, [fp, #-52]
	ldr	r10, [r9]
	ldr	r1, [r9, #4]
	mov	r3, r10
	str	r10, [r9, #8]
.L967:
	mov	r0, r3, asl #5
	mov	lr, r3, asl #7
	add	r2, r3, #1
	cmp	r3, r1
	rsb	ip, r0, lr
	add	ip, r8, ip
	mov	r7, r2, asr #31
	beq	.L995
	ldrd	r4, [ip, #64]
	mov	ip, r7, lsr #22
	ldrd	r6, [fp, #-52]
	add	r2, r2, ip
	ubfx	r2, r2, #0, #10
	cmp	r5, r7
	cmpeq	r4, r6
	beq	.L996
	ldrd	r6, [fp, #-60]
	cmp	r7, r5
	cmpeq	r6, r4
	bls	.L973
	str	r3, [r9, #8]
	rsb	r3, ip, r2
	b	.L967
.L996:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #22
	add	r2, r2, r3
	ubfx	r2, r2, #0, #10
	rsb	r3, r3, r2
	b	.L967
.L995:
	cmp	r10, r3
	str	r10, [r9, #8]
	addgt	r3, r3, #1024
	mov	r0, r8
	rsb	r1, r10, r3
	bl	DeleteRawPacket
	ldr	r0, [fp, #-64]
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mvn	r0, #1
.L965:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L973:
	beq	.L997
	ldr	r2, [r9, #8]
	mvn	r5, #0
	mvn	r4, #0
	mov	r1, r2, asl #7
	sub	r1, r1, r2, asl #5
	add	r1, r8, r1
	ldrd	r0, [r1, #64]
	cmp	r1, r5
	cmpeq	r0, r4
	streq	r3, [r9, #8]
	moveq	r2, r3
	beq	.L979
	ldrd	r4, [fp, #-60]
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L998
.L979:
	cmp	r10, r2
	ldr	r3, [fp, #-76]
	addgt	r1, r2, #1024
	rsble	r1, r10, r2
	rsbgt	r1, r10, r1
	cmp	r3, #1
	beq	.L999
.L982:
	mov	r3, r2, asl #7
	mov	r0, r8
	sub	r2, r3, r2, asl #5
	add	r8, r8, r2
	ldrd	r2, [r8, #64]
.L993:
	ldr	ip, [fp, #-72]
	strd	r2, [ip]
	ldr	r3, [r9]
	str	r3, [r9, #8]
	bl	DeleteRawPacket
	ldr	r0, [fp, #-64]
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L994:
	ldr	r3, [fp, #-68]
	add	r3, r3, #262144
	ldr	r2, [r3, #160]
	cmp	r2, #1
	str	r2, [fp, #-80]
	moveq	r2, #3
	streq	r2, [r3, #160]
	b	.L966
.L998:
	subs	r4, r4, r0
	sbc	r5, r5, r1
	mov	r0, r4
	mov	r1, r5
	ldrd	r4, [fp, #-92]
	cmp	r5, r1
	cmpeq	r4, r0
	strcc	r3, [r9, #8]
	movcc	r2, r3
	b	.L979
.L997:
	cmp	r10, r3
	addgt	r3, r3, #1024
	rsb	r1, r10, r3
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	bne	.L977
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #262144
	ldr	r2, [r3, #152]
	cmp	r1, r2
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #160]
.L977:
	rsb	r0, r0, lr
	add	r3, r8, r0
	mov	r0, r8
	ldrd	r2, [r3, #64]
	b	.L993
.L999:
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #262144
	ldr	r0, [r3, #152]
	cmp	r1, r0
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #160]
	ldreq	r2, [r9, #8]
	b	.L982
.L983:
	mvn	r0, #0
	b	.L965
.L1001:
	.align	2
.L1000:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	2
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
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
	add	r7, r0, #98304
	mov	r5, r0
	ldr	r3, [r7, #76]
	subs	r6, r3, #1
	addmi	r6, r3, #1020
	addmi	r6, r6, #3
	subs	r8, r3, #2
	addmi	r8, r3, #1020
	addmi	r8, r8, #2
	mov	r1, r6, asl #7
	sub	r1, r1, r6, asl #5
	mov	r3, r8, asl #7
	add	r9, r0, r1
	sub	r8, r3, r8, asl #5
	add	r1, r1, #72
	add	r8, r0, r8
	ldr	r3, [r0, #60]
	add	r4, r0, r1
	ldr	r2, [r9, #80]
	ldr	r0, [r8, #80]
	add	r1, r0, r2
	cmp	r1, r3
	bgt	.L1005
	ldr	r3, .L1007
	add	r5, r5, #262144
	ldr	ip, [r8, #112]
	ldr	r1, [r9, #112]
	ldr	r3, [r3, #52]
	add	r0, r0, ip
	blx	r3
	ldr	r2, [r9, #80]
	ldr	r3, [r8, #80]
	mov	r1, r4
	add	r3, r3, r2
	str	r3, [r8, #80]
	ldr	r0, [r5, #204]
	bl	ReleaseRawStreamData
	mov	r0, #0
	str	r6, [r7, #76]
.L1006:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1005:
	str	r3, [sp]
	mov	r3, r2
	ldr	r1, .L1007+4
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1006
.L1008:
	.align	2
.L1007:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	UNWIND(.fnend)
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	2
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
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
	add	r7, r0, #98304
	add	r6, r0, #262144
	add	r7, r7, #96
	ldrsb	r5, [r0, #1]
	cmp	r7, #0
	mov	r8, r0
	ldr	r4, [r6, #124]
	ldrne	r9, [r6, #144]
	moveq	r10, r7
	ldrne	r10, [r6, #140]
	moveq	r9, r7
	cmp	r5, #0
	bne	.L1011
	add	r4, r4, r4, lsr #31
	cmp	r10, r4, asr #1
	movlt	r3, #1
	movge	r3, #0
	cmp	r9, #127
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L1023
	mov	r2, #1
	strb	r2, [r0, #1]
	ldr	r3, [r3]
	blx	r3
	str	r5, [r6, #232]
	str	r0, [r6, #236]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1011:
	ldr	r3, .L1023
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [r6, #236]
	cmp	r0, r2
	bls	.L1014
	rsb	r2, r2, r0
	str	r2, [r6, #232]
	cmp	r2, #1000
	ble	.L1022
	add	r3, r4, #3
	cmp	r4, #0
	movlt	r4, r3
	cmp	r10, r4, asr #2
	movlt	r3, #1
	movge	r3, #0
	cmp	r9, #63
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r1, .L1023+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r7
	mvn	r1, #0
	bl	ReleaseStreamSeg
	mov	r3, #0
	strb	r3, [r8, #1]
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1014:
	mov	r3, #0
	str	r0, [r6, #236]
	str	r3, [r6, #232]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1022:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1024:
	.align	2
.L1023:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC60
	UNWIND(.fnend)
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	2
	.global	SCDDRV_CanNotSelectInst
	.type	SCDDRV_CanNotSelectInst, %function
SCDDRV_CanNotSelectInst:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r3, .L1038
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L1028
	add	r2, r3, #262144
	ldr	r1, [r2, #220]
	cmp	r1, #0
	beq	.L1028
	ldr	r2, [r2, #212]
	cmp	r2, #1
	beq	.L1028
	add	r2, r3, #28
	ldr	ip, [r3, #12]
	sub	r3, fp, #24
	ldmia	r2, {r0, r1, r2}
	cmp	ip, #19
	stmia	r3, {r0, r1, r2}
	beq	.L1028
	mov	r1, r3
	mov	r0, ip
	bl	SCDDRV_IsSCDByPass
	adds	r0, r0, #0
	movne	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1028:
	mov	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1039:
	.align	2
.L1038:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	2
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
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
	ldr	r6, .L1056
	mov	r5, #0
	ldr	r7, .L1056+4
	b	.L1045
.L1044:
	bl	dprint_vfmw
.L1053:
	add	r4, r4, #262144
	mov	r3, #0
	str	r3, [r4, #216]
.L1041:
	add	r5, r5, #1
	cmp	r5, #32
	beq	.L1055
.L1045:
	ldr	r4, [r6, r5, asl #3]
	cmp	r4, #0
	beq	.L1041
	ldr	r3, [r4, #40]
	mov	r0, #0
	ldr	r1, .L1056+8
	cmp	r3, r0
	beq	.L1041
	ldr	ip, [r7]
	ldr	r3, [r7, #4]
	cmp	ip, #1
	mov	r2, ip
	bne	.L1044
	cmp	r3, #1
	beq	.L1053
	cmp	r3, #2
	addeq	r4, r4, #262144
	streq	ip, [r4, #216]
	bne	.L1044
	add	r5, r5, #1
	cmp	r5, #32
	bne	.L1045
.L1055:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1057:
	.align	2
.L1056:
	.word	.LANCHOR0+8
	.word	g_DspDrvState
	.word	.LC61
	UNWIND(.fnend)
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	2
	.global	SCDDRV_RecordGlobalState
	.type	SCDDRV_RecordGlobalState, %function
SCDDRV_RecordGlobalState:
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
	ldr	r3, .L1064
	mov	r4, r0
	mov	r4, r4, asl #6
	ldr	r3, [r3]
	blx	r3
	ldr	r3, .L1064+4
	add	ip, r3, r4
	mov	r2, r0
	ldr	r0, [ip, #48]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, [ip, #44]
	add	r4, r3, r4
	mov	r5, #0
	add	lr, r1, #49920
	str	r5, [r4, #48]
	add	lr, lr, #80
	cmp	r0, lr
	strhi	r0, [ip, #44]
	movhi	r1, r0
	rsb	r1, r1, r2
	ldrls	lr, [ip, #52]
	movhi	lr, #0
	cmp	r1, #1000
	rsb	r2, r0, r2
	add	r2, r2, lr
	str	r2, [r4, #52]
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, #1000
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	str	r5, [r4, #44]
	str	r0, [r4, #56]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1065:
	.align	2
.L1064:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	2
	.global	SCDDRV_MoveRawByOmxPath
	.type	SCDDRV_MoveRawByOmxPath, %function
SCDDRV_MoveRawByOmxPath:
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
	ldr	r3, .L1076
	add	r0, r3, r0, lsl #3
	ldr	r4, [r0, #8]
	ldr	r0, [r4, #52]
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	adds	r5, r4, #72
	beq	.L1069
	add	r2, r4, #98304
	ldr	r3, [r2, #76]
	ldr	r2, [r2, #72]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
.L1072:
	ldrsb	r5, [r4, #2]
	cmp	r5, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r4, #56]
	cmp	r2, r3
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	bl	SM_MoveRawData
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r5
	ldr	r1, .L1076+4
	bl	dprint_vfmw
	add	r4, r4, #262144
	ldr	r0, [r4, #204]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_Reset
.L1069:
	ldr	r1, .L1076+8
	bl	dprint_vfmw
	mov	r3, r5
	b	.L1072
.L1077:
	.align	2
.L1076:
	.word	.LANCHOR0
	.word	.LC62
	.word	.LC63
	UNWIND(.fnend)
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	2
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
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
	subs	r6, r0, #0
	bne	.L1086
	ldr	r4, .L1091
	movw	r3, #4413
	str	r6, [sp]
	mov	r0, #26
	ldr	r2, .L1091+4
	ldr	ip, [r4, #312]
	ldr	r1, .L1091+8
	str	ip, [sp, #4]
	bl	dprint_vfmw
	ldr	r5, [r4, #312]
	cmp	r5, #0
	beq	.L1090
	ldr	r7, .L1091+12
	movw	r3, #4423
	ldr	r2, .L1091+4
	mov	r0, #26
	ldr	r1, .L1091+8
	str	r5, [sp, #4]
	str	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [r7]
	blx	r3
	ldr	r3, [r4, #316]
	cmp	r0, r3
	strcc	r0, [r4, #316]
	bcc	.L1082
	rsb	r0, r3, r0
	cmp	r0, #2000
	bls	.L1082
	ldr	r2, [r4, #308]
	mov	r3, r6
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1091+16
	bl	dprint_vfmw
	ldr	r3, .L1091+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1083
	mov	r1, r6
	mov	r0, r6
	bl	VDH_Reset_Module
.L1084:
	mov	r5, #0
	ldr	r3, [r7, #128]
	str	r5, [r4, #312]
	mov	r0, #1
	blx	r3
	ldr	r0, [r4, #308]
	add	r4, r4, r0, lsl #3
	ldr	r3, [r4, #8]
	cmp	r3, r5
	addne	r3, r3, #262144
	strne	r5, [r3, #212]
	mov	r5, #0
	bl	DeleteLastSendRaw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1082:
	mov	r2, #0
	movw	r3, #4460
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1091+4
	mov	r5, #1
	ldr	r1, .L1091+24
	bl	dprint_vfmw
.L1079:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1090:
	str	r5, [sp]
	movw	r3, #4417
	ldr	r2, .L1091+4
	mov	r0, #26
	ldr	r1, .L1091+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1083:
	mov	r0, r6
	bl	ResetSCD
	b	.L1084
.L1086:
	mvn	r5, #0
	b	.L1079
.L1092:
	.align	2
.L1091:
	.word	.LANCHOR0
	.word	.LANCHOR3+480
	.word	.LC64
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC66
	.word	g_HalDisable
	.word	.LC67
	.word	.LC65
	UNWIND(.fnend)
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	2
	.global	SCDDRV_MarkReloadDsp
	.type	SCDDRV_MarkReloadDsp, %function
SCDDRV_MarkReloadDsp:
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
	ldmnefd	sp, {fp, sp, pc}
	add	r3, r1, #1
	cmp	r3, #32
	ldmhifd	sp, {fp, sp, pc}
	ldr	r3, .L1100
	cmn	r1, #1
	mov	r2, #1
	addne	r1, r3, r1, lsl #3
	str	r2, [r3, #320]
	mvnne	r2, #0
	ldrne	r3, [r1, #8]
	addne	r3, r3, #262144
	strne	r2, [r3, #216]
	ldmfd	sp, {fp, sp, pc}
.L1101:
	.align	2
.L1100:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_MarkReloadDsp, .-SCDDRV_MarkReloadDsp
	.align	2
	.global	SM_UpdateMatchMode
	.type	SM_UpdateMatchMode, %function
SM_UpdateMatchMode:
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
	ldmnefd	sp, {fp, sp, pc}
	cmp	r1, #31
	ldmhifd	sp, {fp, sp, pc}
	ldr	r3, .L1104
	mov	r2, #1
	add	r1, r3, r1, lsl #3
	ldr	r3, [r1, #8]
	add	r3, r3, #262144
	str	r2, [r3, #216]
	ldmfd	sp, {fp, sp, pc}
.L1105:
	.align	2
.L1104:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_UpdateMatchMode, .-SM_UpdateMatchMode
	.align	2
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
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
	ldr	r6, .L1116
	mov	r3, r0, asl #2
	rsb	r0, r3, r0, lsl #6
	add	r0, r6, r0
	ldr	r2, [r0, #312]
	cmp	r2, #1
	beq	.L1107
.L1109:
	mov	r0, #0
.L1108:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1107:
	ldr	r7, .L1116+4
	add	r6, r6, r3
	movw	r5, #41248
	movt	r5, 7
	ldr	r3, [r7]
	blx	r3
	mov	r4, r0
	b	.L1113
.L1112:
	subs	r5, r5, #1
	beq	.L1115
.L1113:
	ldr	r0, [r6, #4]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L1109
	ldr	r3, [r7]
	blx	r3
	cmp	r4, r0
	rsb	r2, r0, r4
	rsb	r3, r4, r0
	mvnhi	r3, r2
	cmp	r3, #1000
	bls	.L1112
	str	r3, [sp]
	mov	r2, r4
	mov	r3, r0
	ldr	r1, .L1116+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1108
.L1115:
	mvn	r0, #6
	b	.L1108
.L1117:
	.align	2
.L1116:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC68
	UNWIND(.fnend)
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	2
	.global	PrintScdVtrlReg
	.type	PrintScdVtrlReg, %function
PrintScdVtrlReg:
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
	ldr	r4, .L1119
	mov	r5, r0
	add	r4, r4, r0, lsl #2
	ldr	r0, [r4, #4]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	str	r0, [fp, #-52]
	ldr	r0, [r4, #4]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_ReadPhyWord
	str	r0, [fp, #-48]
	ldr	r0, [r4, #4]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	mov	r10, r0
	ldr	r0, [r4, #4]
	add	r0, r0, #2064
	bl	MEM_ReadPhyWord
	mov	r9, r0
	ldr	r0, [r4, #4]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	mov	r8, r0
	ldr	r0, [r4, #4]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_ReadPhyWord
	mov	r7, r0
	ldr	r0, [r4, #4]
	add	r0, r0, #2080
	bl	MEM_ReadPhyWord
	mov	r6, r0
	ldr	r0, [r4, #4]
	add	r0, r0, #2048
	bl	MEM_ReadPhyWord
	mov	r2, r5
	ldr	r1, .L1119+4
	mov	r4, r0
	mov	r0, #24
	bl	dprint_vfmw
	ldr	ip, [fp, #-52]
	ldr	r1, .L1119+8
	mov	r0, #24
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	ldr	r1, .L1119+12
	mov	r0, #24
	mov	r2, r3
	bl	dprint_vfmw
	mov	r2, r10
	ldr	r1, .L1119+16
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r9
	ldr	r1, .L1119+20
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r8
	ldr	r1, .L1119+24
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L1119+28
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r6
	ldr	r1, .L1119+32
	mov	r0, #24
	bl	dprint_vfmw
	sxtb	r2, r4
	ldr	r1, .L1119+36
	mov	r0, #24
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1120:
	.align	2
.L1119:
	.word	.LANCHOR0
	.word	.LC69
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	UNWIND(.fnend)
	.size	PrintScdVtrlReg, .-PrintScdVtrlReg
	.align	2
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #196)
	sub	sp, sp, #196
	ldr	r5, .L1163
	mov	r8, r0
	mov	r4, r1
	mov	r6, r2
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1122
	ldr	r3, .L1163+4
	sub	r0, fp, #232
	mov	r2, #188
	mov	r1, #0
	mov	r7, r0
	ldr	r3, [r3, #48]
	blx	r3
.L1123:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #4]
	cmp	r2, #1
	bne	.L1150
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	bne	.L1151
.L1126:
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	bne	.L1152
.L1128:
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	bne	.L1153
.L1130:
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	bne	.L1154
.L1132:
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	bne	.L1155
.L1134:
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L1135:
	ldr	r1, [r4, #52]
	ldr	ip, [r4, #44]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r2, [r4, #36]
	mov	r1, r1, asl #9
	ldrb	r0, [r5]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #8
	and	r2, r2, #15
	mov	r3, r3, asl #4
	cmp	r0, #1
	orr	r1, r1, r2
	and	r3, r3, #16
	orr	r1, r1, r3
	bne	.L1156
	ldr	r3, .L1163+8
	add	r3, r3, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2080
	bl	MEM_WritePhyWord
	ldr	r3, [r4, #44]
	cmp	r3, #0
	bne	.L1157
.L1138:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1158
	ldr	r3, .L1163+8
	mov	r1, #0
	ldr	r10, .L1163
	add	r3, r3, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r9, [r5]	@ zero_extendqisi2
	cmp	r9, #1
	beq	.L1142
.L1159:
	ldr	r2, [r4, #44]
	sub	r0, fp, #232
	mov	r3, #0
	str	r8, [fp, #-224]
	strb	r6, [fp, #-232]
	strb	r2, [fp, #-231]
	str	r3, [fp, #-228]
	bl	VDH_PostTask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1150:
	mov	r3, r1
	movw	r2, #2052
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	beq	.L1126
.L1151:
	mov	r3, r1
	movw	r2, #2056
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	beq	.L1128
.L1152:
	mov	r3, r1
	movw	r2, #2060
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	beq	.L1130
.L1153:
	mov	r3, r1
	mov	r2, #2064
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	beq	.L1132
.L1154:
	mov	r3, r1
	movw	r2, #2068
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	beq	.L1134
.L1155:
	mov	r3, r1
	movw	r2, #2072
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	b	.L1135
.L1158:
	mov	r3, #0
	movw	r2, #2076
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r9, [r5]	@ zero_extendqisi2
	ldr	r10, .L1163
	cmp	r9, #1
	bne	.L1159
.L1142:
	mov	r0, r6
	bl	PrintScdVtrlReg
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1160
	ldr	r3, .L1163+8
	mov	r1, #0
	add	r3, r3, r6, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
.L1145:
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #1
	and	r1, r1, #1
	bne	.L1161
	ldr	r3, .L1163+8
	add	r6, r3, r6, lsl #2
	ldr	r0, [r6, #4]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1156:
	mov	r3, r1
	mov	r2, #2080
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L1138
.L1157:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #60]
	cmp	r2, #1
	bne	.L1162
	ldr	r2, .L1163+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #4]
	bl	MEM_WritePhyWord
	b	.L1138
.L1122:
	mov	r0, r2
	mov	r7, #0
	bl	ResetSCD
	b	.L1123
.L1162:
	mov	r3, r1
	mov	r2, #0
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	b	.L1138
.L1161:
	mov	r3, r1
	mov	r0, r7
	mov	r2, #2048
	mov	r1, #1
	bl	VDH_Record_RegData
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1160:
	mov	r1, r9
	mov	r3, #0
	mov	r2, #2048
	mov	r0, r7
	bl	VDH_Record_RegData
	b	.L1145
.L1164:
	.align	2
.L1163:
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	2
	.global	PrintDownMsg
	.type	PrintDownMsg, %function
PrintDownMsg:
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
	mov	r7, r1
	mov	r6, r2
	ldr	r1, .L1170
	mov	r2, r3
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L1170+4
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r4
	ldr	r1, .L1170+8
	mov	r0, #24
	bl	dprint_vfmw
	cmp	r6, #0
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r6, r6, r6, lsl #1
	mov	r5, r7
	mov	r4, #0
.L1167:
	ldr	r3, [r7, r4, asl #2]
	mov	r2, r4
	ldr	r1, .L1170+12
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	add	r2, r4, #1
	ldr	r1, .L1170+12
	mov	r0, #24
	add	r5, r5, #12
	bl	dprint_vfmw
	ldr	r3, [r5, #-4]
	add	r2, r4, #2
	ldr	r1, .L1170+12
	mov	r0, #24
	add	r4, r4, #3
	bl	dprint_vfmw
	ldr	r1, .L1170+16
	mov	r0, #24
	bl	dprint_vfmw
	cmp	r4, r6
	bne	.L1167
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1171:
	.align	2
.L1170:
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC17
	UNWIND(.fnend)
	.size	PrintDownMsg, .-PrintDownMsg
	.align	2
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #108)
	sub	sp, sp, #108
	str	r0, [fp, #-144]
	mov	r4, r1
	str	r1, [fp, #-148]
	mov	r9, r2
	mov	r1, #0
	mov	r2, #96
	sub	r0, fp, #140
	mov	r10, r3
	bl	memset
	sub	r1, fp, #140
	mov	r0, r9
	bl	GetFirstRawPacket
	ldr	r6, [fp, #-132]
	cmp	r6, r4
	bgt	.L1173
	mov	r5, #0
	add	r7, r9, #98304
	mov	lr, r6
	mov	r8, r5
.L1176:
	cmp	lr, #0
	mov	r3, r5, asl #2
	add	ip, r10, r3
	mov	r2, #96
	sub	r0, fp, #140
	add	r3, r3, #12
	ble	.L1174
	ldr	r1, [fp, #4]
	ldr	r4, [fp, #-136]
	add	r3, r3, r1
	ldr	r1, [fp, #-136]
	str	r4, [r10, r5, asl #2]
	add	r5, r5, #3
	sub	r1, r1, #1
	str	r3, [ip, #8]
	add	r1, r1, lr
	str	r1, [ip, #4]
.L1174:
	ldr	r3, [fp, #-144]
	add	r8, r8, #1
	str	r6, [r3, #4]
	ldr	r1, [r7, #16]
	ldr	ip, [r7, #4]
	mov	r3, r1, asl #7
	cmp	r1, ip
	sub	r1, r3, r1, asl #5
	add	r1, r9, r1
	bne	.L1189
.L1175:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	bne	.L1177
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-148]
	ldr	r3, [r3, #4]
	sub	r2, r2, #16
	cmp	r3, r2
	blt	.L1182
.L1177:
	cmp	r8, #0
	beq	.L1181
	cmp	r5, #0
	ldr	lr, [fp, #-144]
	subgt	r5, r5, #-1073741823
	ldr	r0, [fp, #4]
	movgt	r3, #0
	mov	ip, #1
	strgt	r3, [r10, r5, asl #2]
	mov	r2, r8
	str	r8, [lr]
	mov	r1, r10
	ldr	r3, [fp, #12]
	str	ip, [lr, #8]
	bl	PrintDownMsg
	mov	r0, #0
.L1188:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1189:
	ldr	r3, .L1190
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r7, #16]
	ldr	lr, [fp, #-132]
	ldr	r1, [fp, #-148]
	add	r3, r3, #1
	add	r6, r6, lr
	cmp	r1, r6
	mov	r2, r3, asr #31
	movge	r1, #1
	movlt	r1, #0
	cmp	r8, #1024
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	movge	r1, #0
	cmp	r1, #0
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r7, #16]
	bne	.L1176
	b	.L1175
.L1173:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	bne	.L1181
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-148]
	ldr	r3, [r3, #4]
	sub	r2, r2, #16
	cmp	r3, r2
	bge	.L1181
	ldr	r5, [fp, #8]
	mov	r8, r5
.L1182:
	ldr	r2, [fp, #-148]
	cmp	r2, r6
	cmplt	r8, #1024
	bge	.L1177
	ldr	r1, [fp, #-148]
	ldr	r2, [fp, #-132]
	rsb	r3, r3, r1
	cmp	r2, r3
	blt	.L1177
	mov	r2, r5, asl #2
	ldr	ip, [fp, #-136]
	add	r0, r10, r2
	ldr	lr, [fp, #4]
	add	r2, r2, #12
	sub	r1, ip, #1
	str	ip, [r10, r5, asl #2]
	add	r1, r1, r3
	add	r2, r2, lr
	stmib	r0, {r1, r2}
	ldr	r1, [fp, #-144]
	add	r8, r8, #1
	str	r3, [fp, #-132]
	add	r5, r5, #3
	ldr	r2, [r1, #4]
	add	r3, r2, r3
	str	r3, [r1, #4]
	b	.L1177
.L1181:
	mvn	r0, #5
	b	.L1188
.L1191:
	.align	2
.L1190:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	WriteScdMsg, .-WriteScdMsg
	.align	2
	.global	SCDDRV_StartSCD
	.type	SCDDRV_StartSCD, %function
SCDDRV_StartSCD:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r4, r1, #262144
	mov	r7, r3
	ldr	r9, .L1194
	ldr	r3, [r4, #176]
	add	r6, r4, #152
	mov	r5, r1
	mov	r8, r0
	mov	r10, r2
	ldr	ip, [r9, #48]
	str	r3, [fp, #-48]
	mov	r2, #12
	ldr	r3, [r4, #168]
	mov	r1, #0
	mov	r0, r6
	str	r3, [fp, #-52]
	blx	ip
	ldr	ip, [r8, #44]
	add	r2, r5, #72
	ldr	r3, [fp, #-48]
	mov	r0, r6
	str	r7, [sp, #8]
	mov	r1, r10
	str	ip, [sp, #4]
	str	r3, [sp]
	ldr	r3, [fp, #-52]
	bl	WriteScdMsg
	subs	r5, r0, #0
	bne	.L1193
	ldr	r3, [r9]
	blx	r3
	ldr	r3, .L1194+4
	mov	r2, r7
	mov	r1, r8
	add	r7, r3, r7, lsl #6
	str	r0, [r7, #48]
	ldr	r0, [r4, #204]
	bl	WriteScdVtrlReg
.L1193:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1195:
	.align	2
.L1194:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	2
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #88)
	sub	sp, sp, #88
	sub	r3, fp, #28
	mov	r7, r1
	add	r1, r0, #98304
	mov	ip, #0
	sub	r2, fp, #100
	str	ip, [r3, #-68]!
	mov	r5, r0
	str	r2, [sp]
	add	r1, r1, #96
	add	r0, r0, #72
	sub	r2, fp, #104
	str	ip, [fp, #-104]
	str	ip, [fp, #-100]
	bl	SCDDRV_CheckConditionOfStartSCD
	subs	r4, r0, #0
	bne	.L1203
	add	r6, r5, #262144
	mov	r1, r7
	ldr	r0, [r6, #204]
	bl	SM_CfgBuf
	subs	r4, r0, #0
	bne	.L1204
	ldr	r2, [fp, #-100]
	mov	r0, r5
	ldr	r3, [r6, #276]
	sub	r1, fp, #92
	str	r2, [r6, #192]
	mul	r3, r3, r2
	mov	r3, r3, asl #2
	str	r3, [r6, #188]
	bl	SCDDRV_SetCtrlReg
	ldr	r2, [fp, #-96]
	mov	r3, r7
	sub	r0, fp, #92
	mov	r1, r5
	bl	SCDDRV_StartSCD
	cmp	r0, #0
	movne	r2, r0
	bne	.L1198
	ldr	r3, [fp, #-96]
	mov	r2, #1
	ldr	r1, [fp, #-104]
	mov	r4, #0
	cmp	r1, r3
	str	r3, [r6, #252]
	str	r1, [r6, #248]
	movls	r3, #1
	strlsb	r3, [r5, #2]
	ldr	r3, .L1205
	strhib	r0, [r5, #2]
	str	r2, [r6, #212]
	strb	r4, [r5, #3]
	ldr	r3, [r3]
	blx	r3
	mov	r2, r4
	str	r0, [r6, #272]
.L1198:
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1204:
	mov	r2, r4
	ldr	r1, .L1205+4
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1203:
	mov	r2, r4
	ldr	r1, .L1205+8
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1206:
	.align	2
.L1205:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC83
	.word	.LC82
	UNWIND(.fnend)
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	2
	.global	PrintScdStateReg
	.type	PrintScdStateReg, %function
PrintScdStateReg:
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
	mov	r2, r1
	mov	r0, #24
	ldr	r1, .L1208
	bl	dprint_vfmw
	ldr	r2, [r4]
	ldr	r1, .L1208+4
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1208+8
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #12]
	ldr	r1, .L1208+12
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #16]
	ldr	r1, .L1208+16
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L1208+20
	mov	r0, #24
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1209:
	.align	2
.L1208:
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC88
	.word	.LC89
	UNWIND(.fnend)
	.size	PrintScdStateReg, .-PrintScdStateReg
	.align	2
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
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
	ldr	r4, .L1211
	mov	r5, r0
	mov	r6, r1
	movw	r7, #2124
	add	r4, r4, r1, lsl #2
	ldr	r0, [r4, #4]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	and	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r4, #4]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #4]
	and	r3, r0, #1
	add	r0, r7, r2
	str	r3, [r5, #4]
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #4]
	mov	r3, r0, lsr #22
	add	r0, r7, r2
	str	r3, [r5, #8]
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #4]
	ubfx	r3, r0, #0, #22
	add	r0, r2, #2128
	str	r3, [r5, #12]
	bl	MEM_ReadPhyWord
	ldr	r3, [r4, #4]
	str	r0, [r5, #16]
	add	r0, r3, #2128
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	ldr	r3, [r4, #4]
	str	r0, [r5, #20]
	add	r0, r3, #2048
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	mov	r1, r6
	str	r0, [r5, #24]
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	PrintScdStateReg
.L1212:
	.align	2
.L1211:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	2
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
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
	add	r4, r0, #262144
	mov	r5, r0
	ldr	r3, [r4, #160]
	cmp	r3, #3
	mov	r3, #2
	streq	r3, [r4, #160]
	mvneq	r0, #6
	beq	.L1215
	str	r3, [r4, #160]
	sub	r0, fp, #56
	bl	ReadScdStateReg
	ldr	r6, [fp, #-44]
	movw	r3, #34464
	movt	r3, 1
	cmp	r6, r3
	bhi	.L1220
.L1216:
	ldr	r1, [r4, #276]
	ldr	r0, [fp, #-32]
	bl	__aeabi_uidiv
	cmp	r0, r6
	movcs	r0, r6
	cmp	r0, #1
	bls	.L1221
	ldr	r3, [r5, #12]
	mov	r4, #0
	sub	r1, r0, #1
	strb	r4, [r5]
	cmp	r3, #2
	mov	r0, r5
	ldr	r2, [fp, #-40]
	beq	.L1219
	bl	ProcessNotMpeg4ScdUpMsg
	mov	r0, r4
.L1215:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1220:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	bne	.L1216
	mov	r0, r5
	mov	r1, r6
	bl	ProcessExceptionalStartCodeNum
	mvn	r0, #6
	b	.L1215
.L1219:
	bl	ProcessMpeg4ScdUpMsg
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1221:
	mov	r1, r0
	mov	r0, r5
	bl	ProcessNoSeg
	b	.L1215
	UNWIND(.fnend)
	.size	ProcessScdReturn, .-ProcessScdReturn
	.align	2
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
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
	mov	r6, r0
	mov	r0, #26
	mov	r5, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, .L1231
	mov	r2, r6
	ldr	r1, .L1231+4
	mov	r0, #26
	add	r3, r3, r6, lsl #3
	ldr	r4, [r3, #8]
	bl	dprint_vfmw
	ldr	r1, .L1231+8
	mov	r0, #26
	add	r7, r4, #98304
	ldr	r2, [r7, #72]
	bl	dprint_vfmw
	ldr	r2, [r7, #76]
	ldr	r1, .L1231+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #80]
	ldr	r1, .L1231+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #84]
	ldr	r1, .L1231+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #88]
	ldr	r1, .L1231+24
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r5, #1
	beq	.L1224
.L1228:
	mov	r2, r6
	ldr	r1, .L1231+28
	mov	r0, #26
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1224:
	cmn	r4, #72
	beq	.L1225
	ldr	r5, [r7, #72]
	ldr	r7, [r7, #76]
	subs	r7, r7, r5
	addmi	r7, r7, #1024
	cmp	r7, #0
	ble	.L1228
	mov	r3, r5, asl #7
	add	r7, r5, r7
	sub	r3, r3, r5, asl #5
	add	r4, r4, r3
.L1227:
	ldr	r2, [r4, #76]
	mov	r0, #26
	ldr	r1, .L1231+32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrd	r2, [r4, #112]
	ldr	r1, .L1231+36
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #80]
	ldr	r1, .L1231+40
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #136]
	ldr	r1, .L1231+44
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r5, r7
	add	r4, r4, #96
	bne	.L1227
	b	.L1228
.L1225:
	movw	r3, #4676
	ldr	r2, .L1231+48
	ldr	r1, .L1231+52
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1228
.L1232:
	.align	2
.L1231:
	.word	.LANCHOR0
	.word	.LC90
	.word	.LC91
	.word	.LC92
	.word	.LC93
	.word	.LC94
	.word	.LC95
	.word	.LC96
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LANCHOR3+500
	.word	.LC101
	UNWIND(.fnend)
	.size	PrintScdRawState, .-PrintScdRawState
	.align	2
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
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
	UNWIND(.pad #204)
	sub	sp, sp, #204
	ldr	r8, .L1268
	mov	r9, r0, asl #3
	ldr	r7, .L1268+4
	add	r3, r8, r9
	sub	r6, fp, #140
	mov	r5, r0
	mov	r2, #96
	ldr	r4, [r3, #8]
	mov	r1, #0
	mov	r0, r6
	ldr	r3, [r7, #48]
	blx	r3
	cmp	r4, #0
	beq	.L1233
	ldr	r3, [r4, #12]
	cmp	r3, #20
	beq	.L1233
	mov	r3, r5, asl #24
	str	r3, [fp, #-152]
	b	.L1247
.L1267:
	add	r3, r8, r9
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L1237
	add	r2, r3, #98304
	ldr	r3, [r2, #76]
	ldr	r2, [r2, #80]
	add	r3, r3, #1
	mov	r1, r3, asr #31
	mov	r1, r1, lsr #22
	add	r3, r3, r1
	ubfx	r3, r3, #0, #10
	rsb	r3, r1, r3
	cmp	r3, r2
	beq	.L1237
	mov	r1, r6
	mov	r0, r5
	bl	ReadRawStreamData
	subs	r3, r0, #0
	str	r3, [fp, #-144]
	bne	.L1233
	add	r10, r4, #262144
	ldr	r2, [fp, #-132]
	ldr	r1, [r7]
	ldr	r0, [r10, #256]
	ldr	ip, [r10, #280]
	add	r0, r0, r2
	str	r0, [r10, #256]
	ldr	r0, [r10, #284]
	add	r2, r2, ip
	str	r2, [r10, #280]
	add	r2, r0, #1
	str	r2, [r10, #284]
	blx	r1
	ldr	r1, [r10, #260]
	cmp	r1, #0
	streq	r0, [r10, #260]
	beq	.L1240
	rsb	r1, r1, r0
	cmp	r1, #2000
	bls	.L1240
	str	r0, [fp, #-148]
	ldr	r0, [r10, #256]
	mov	r0, r0, asl #3
	bl	__aeabi_uidiv
	mov	r1, #1000
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-148]
	str	r3, [r10, #256]
	str	r2, [r10, #260]
	mul	r0, r1, r0
	mov	r0, r0, lsr #10
	str	r0, [r10, #264]
.L1240:
	ldrd	r2, [fp, #-76]
	mov	r0, #29
	ldr	r1, .L1268+8
	bl	dprint_vfmw
	ldr	r3, [fp, #-132]
	ldr	r2, [fp, #-136]
	mov	r0, #26
	ldr	r1, .L1268+12
	bl	dprint_vfmw
	ldrd	r2, [fp, #-76]
	mov	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1263
.L1241:
	mov	r1, r6
	mov	r0, r5
	bl	SCDDRV_InsertRawPacket
	cmp	r0, #0
	bne	.L1264
	mov	r3, #1
	strb	r3, [r4, #3]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1265
.L1245:
	mov	r2, #88
	sub	r1, fp, #132
	mov	r0, sp
	bl	memcpy
	ldmia	r6, {r2, r3}
	mov	r1, r4
	mov	r0, r5
	bl	SCDDRV_SaveRawStream
.L1247:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1266
.L1235:
	cmp	r5, #31
	bls	.L1267
.L1237:
	add	r4, r4, #262144
	ldr	r1, .L1268+16
	mov	r2, r5
	mov	r0, #23
	bl	dprint_vfmw
	mov	r1, #0
	ldr	r0, [r4, #204]
	bl	PrintScdRawState
.L1233:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1266:
	add	r3, r4, #262144
	ldr	r3, [r3, #144]
	cmp	r3, #8
	ble	.L1235
	b	.L1233
.L1265:
	ldr	r3, [r7]
	blx	r3
	ldr	r3, .L1268+20
	add	ip, r8, r5, lsl #2
	ldr	r2, [r3]
	ldr	r3, [ip, #340]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L1245
	str	r0, [ip, #340]
	movw	r1, #3041
	ldr	r2, [fp, #-152]
	ldr	r0, .L1268+24
	bl	DBG_AddTrace
	b	.L1245
.L1263:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [fp, #-76]
	b	.L1241
.L1264:
	ldr	r1, .L1268+28
	mov	r0, #0
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1269:
	.align	2
.L1268:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC102
	.word	.LC103
	.word	.LC105
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+520
	.word	.LC104
	UNWIND(.fnend)
	.size	FillRawData, .-FillRawData
	.align	2
	.global	SM_SeekPtsAfterFillNewRaw
	.type	SM_SeekPtsAfterFillNewRaw, %function
SM_SeekPtsAfterFillNewRaw:
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
	mov	r4, r2
	mov	r5, r0
	mov	r6, r1
	mov	r0, r2
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	FillRawData
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	mov	r3, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	SM_SeekPtsInRawArray
	UNWIND(.fnend)
	.size	SM_SeekPtsAfterFillNewRaw, .-SM_SeekPtsAfterFillNewRaw
	.align	2
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
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
	ldr	r3, .L1293
	mov	r5, r0
	mov	r6, r1
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #8]
	cmp	r4, #0
	beq	.L1283
	add	r7, r4, #98304
	add	r0, r7, #96
	bl	SM_SeekPtsInSegArray
	cmp	r0, #0
	bne	.L1273
.L1274:
	mov	r0, #0
.L1272:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1273:
	add	r8, r4, #72
	mov	r1, #0
	mov	r0, r5
	bl	DeleteRawPacketInBuffer
	mov	r0, r8
	mov	r3, #1
	mov	r2, r5
	mov	r1, r6
	bl	SM_SeekPtsInRawArray
	cmp	r0, #0
	beq	.L1274
	ldr	r2, [r7, #72]
	ldr	r0, [r7, #76]
	cmp	r2, r0
	addgt	r0, r0, #1024
	rsb	r0, r2, r0
	ldrd	r2, [r6, #16]
	mov	r1, r0, asr #31
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L1292
	subs	r2, r2, r0
	movw	r0, #1023
	sbc	r3, r3, r1
	and	r0, r0, r2
	mov	r1, #0
	mov	r7, r2, lsr #10
	and	r1, r1, r3
	orr	r7, r7, r3, asl #22
	orrs	r1, r0, r1
	addne	r7, r7, #1
	cmp	r7, #0
	movge	r4, #0
	blt	.L1282
.L1281:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r8
	add	r4, r4, #1
	bl	SM_SeekPtsAfterFillNewRaw
	cmp	r0, #0
	beq	.L1274
	cmp	r7, r4
	bge	.L1281
.L1282:
	mvn	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1283:
	mvn	r0, #0
	b	.L1272
.L1292:
	strd	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1293+4
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1272
.L1294:
	.align	2
.L1293:
	.word	.LANCHOR0
	.word	.LC106
	UNWIND(.fnend)
	.size	SM_SeekPts, .-SM_SeekPts
	.align	2
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
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
	mov	r0, #26
	mov	r6, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, .L1301
	mov	r2, r7
	ldr	r1, .L1301+4
	mov	r0, #26
	add	r3, r3, r7, lsl #3
	ldr	r5, [r3, #8]
	bl	dprint_vfmw
	ldr	r1, .L1301+8
	mov	r0, #26
	add	r4, r5, #262144
	add	r8, r5, #98304
	ldr	r2, [r4, #104]
	bl	dprint_vfmw
	ldr	r2, [r4, #108]
	ldr	r1, .L1301+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #116]
	ldr	r1, .L1301+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #120]
	ldr	r1, .L1301+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r8, #96]
	ldr	r1, .L1301+24
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #124]
	ldr	r1, .L1301+28
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #128]
	ldr	r1, .L1301+32
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #132]
	ldr	r1, .L1301+36
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, #1
	beq	.L1297
.L1298:
	mov	r2, r7
	ldr	r1, .L1301+40
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1297:
	ldr	r6, [r4, #104]
	ldr	r8, [r4, #108]
	rsb	r8, r6, r8
	ubfx	r8, r8, #0, #11
	cmp	r8, #0
	ble	.L1298
	mov	r4, r6, asl #6
	add	r8, r8, r6
	add	r4, r4, r6, lsl #4
	add	r4, r4, #98304
	add	r4, r4, #112
	add	r4, r5, r4
.L1299:
	ldr	r2, [r4]
	mov	r0, #26
	ldr	r1, .L1301+44
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #-8]
	ldr	r1, .L1301+48
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #4]
	ldr	r1, .L1301+52
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1301+56
	mov	r0, #26
	bl	dprint_vfmw
	ldrsb	r2, [r4, #-4]
	ldr	r1, .L1301+60
	mov	r0, #26
	bl	dprint_vfmw
	ldrb	r2, [r4, #-3]	@ zero_extendqisi2
	ldr	r1, .L1301+64
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #16]
	ldr	r1, .L1301+68
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, r8
	add	r4, r4, #80
	bne	.L1299
	b	.L1298
.L1302:
	.align	2
.L1301:
	.word	.LANCHOR0
	.word	.LC107
	.word	.LC108
	.word	.LC109
	.word	.LC110
	.word	.LC111
	.word	.LC112
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LC116
	.word	.LC117
	.word	.LC118
	.word	.LC119
	.word	.LC120
	.word	.LC121
	.word	.LC122
	.word	.LC123
	UNWIND(.fnend)
	.size	PrintScdSegState, .-PrintScdSegState
	.align	2
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
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
	ldr	r2, .L1316
	mov	r3, r0, asl #2
	str	r1, [fp, #-48]
	add	r1, r2, r3
	mov	r6, r0
	ldr	r2, [r1, #324]
	cmp	r2, #0
	beq	.L1304
	cmp	r2, #1
	beq	.L1305
.L1312:
	mvn	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1304:
	ldr	r2, .L1316
	rsb	r3, r3, r0, lsl #6
	ldr	r8, .L1316+4
	mov	r5, #32
	add	r3, r2, r3
	ldr	r9, .L1316+8
	ldr	r4, [r3, #308]
	b	.L1311
.L1307:
	subs	r5, r5, #1
	beq	.L1312
.L1311:
	add	r3, r4, #1
	mov	r1, r6
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #27
	add	r3, r3, r4
	and	r3, r3, #31
	rsb	r4, r4, r3
	mov	r0, r4
	bl	SCDDRV_CanNotSelectInst
	subs	r7, r0, #0
	bne	.L1307
	mov	r1, r7
	mov	r0, r4
	bl	PrintScdRawState
	mov	r1, r7
	mov	r0, r4
	bl	PrintScdSegState
	ldr	r3, .L1316
	ldr	r2, [r8]
	add	r3, r3, r4, lsl #3
	ldr	r7, [r3, #8]
	blx	r2
	mov	ip, #0
	add	r10, r7, #262144
	ldr	r1, [r10, #272]
	subs	r1, r0, r1
	bmi	.L1308
	ldrsh	lr, [r7, #2]
	cmp	lr, #1
	beq	.L1314
.L1308:
	str	r0, [r10, #272]
	ldrsb	r1, [r7]
	cmp	r1, #1
	strneb	ip, [r7, #1]
	beq	.L1315
.L1310:
	ldr	ip, [r9, r4, asl #2]
	mov	r1, r6
	mov	r0, r7
	add	ip, ip, #294912
	ldr	ip, [ip, #864]
	str	ip, [r10, #424]
	bl	CutStreamWithSCD
	cmn	r0, #6
	movne	r1, #0
	moveq	r1, #1
	cmp	r0, #0
	strb	r1, [r7]
	bne	.L1307
	ldr	r2, [fp, #-48]
	mov	r3, #1
	str	r0, [fp, #-52]
	mov	r1, r3
	ldr	r0, .L1316+12
	movw	lr, #4222
	str	r4, [r2]
	str	r3, [r10, #220]
	add	r2, r0, r4, lsl #2
	ldr	r3, .L1316+16
	mov	r0, r4
	str	lr, [sp]
	bl	RecordPOS
	ldr	ip, [fp, #-52]
	mov	r0, ip
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1314:
	cmp	r1, #199
	bls	.L1307
	b	.L1308
.L1315:
	mov	r0, r7
	bl	SCDDRV_ProcessSegFull
	b	.L1310
.L1305:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r1, #324]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1317:
	.align	2
.L1316:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0+468
	.word	.LANCHOR3+532
	UNWIND(.fnend)
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	2
	.type	SCDDRV_ActivateSCD.part.12, %function
SCDDRV_ActivateSCD.part.12:
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
	bl	SM_DoNextInstance
	cmp	r0, #0
	bne	.L1318
	mov	r0, r4, asl #6
	ldr	r3, .L1320
	sub	r0, r0, r4, asl #2
	ldr	r1, [fp, #-24]
	ldr	r2, .L1320+4
	add	r0, r3, r0
	mov	r3, #1
	add	r4, r0, #312
	str	r1, [r0, #308]
	str	r3, [r0, #312]
	ldr	r3, [r2]
	blx	r3
	mov	r3, #4480
	ldr	r2, .L1320+8
	ldr	r1, .L1320+12
	str	r0, [r4, #4]
	mov	r0, #26
	bl	dprint_vfmw
.L1318:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1321:
	.align	2
.L1320:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+552
	.word	.LC124
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
	.align	2
	.global	SCDDRV_ActivateSCD
	.type	SCDDRV_ActivateSCD, %function
SCDDRV_ActivateSCD:
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
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.12
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD, .-SCDDRV_ActivateSCD
	.align	2
	.global	SM_Wakeup
	.type	SM_Wakeup, %function
SM_Wakeup:
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
	ldr	r5, .L1335
	mov	r4, #0
	b	.L1326
.L1325:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L1334
.L1326:
	ldr	r3, [r5, r4, asl #3]
	cmp	r3, #0
	add	r2, r3, #262144
	beq	.L1325
	ldr	r3, [r2, #220]
	cmp	r3, #1
	bne	.L1325
	mov	r0, r4
	add	r4, r4, #1
	bl	FillRawData
	cmp	r4, #32
	bne	.L1326
.L1334:
	mov	r2, #1
	mov	r3, #0
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1335+4
	ldr	r1, .L1335+8
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_CheckDevice
	subs	r4, r0, #0
	beq	.L1327
	mov	r2, #0
	movw	r3, #4538
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1335+4
	ldr	r1, .L1335+12
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1327:
	str	r4, [sp]
	movw	r3, #4533
	ldr	r2, .L1335+4
	mov	r0, #26
	ldr	r1, .L1335+16
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.12
.L1336:
	.align	2
.L1335:
	.word	.LANCHOR0+8
	.word	.LANCHOR3+572
	.word	.LC125
	.word	.LC126
	.word	.LC127
	UNWIND(.fnend)
	.size	SM_Wakeup, .-SM_Wakeup
	.align	2
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
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
	ldr	r6, .L1354
	ldr	r4, .L1354+4
	mov	r7, r0, asl #2
	add	r8, r6, r7
	mov	r5, r0
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	ldr	r0, [r8, #4]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L1350
.L1338:
	ldr	r3, .L1354+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1343
	mov	r1, r5
	mov	r0, #0
	bl	VDH_Notify_ModuleIdle
.L1343:
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1350:
	ldr	r0, [r8, #4]
	mov	r10, r5, asl #6
	rsb	r8, r7, r10
	mov	r1, #1
	add	r0, r0, #2080
	add	r8, r6, r8
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	add	r3, r8, #304
	str	r3, [fp, #-60]
	mov	r2, r3
	ldr	r3, [r8, #304]
	ldr	ip, [r2, #4]
	add	r2, r6, ip, lsl #3
	ldr	r9, [r2, #8]
	cmp	r9, #0
	cmpne	r3, #0
	moveq	r3, #1
	movne	r3, #0
	str	r3, [fp, #-56]
	beq	.L1351
	ldr	r3, .L1354+12
	mov	r0, ip
	movw	r2, #4358
	mov	r1, #2
	str	r2, [sp]
	add	r2, r6, #596
	str	ip, [fp, #-64]
	bl	RecordPOS
	mov	r0, r5
	bl	SCDDRV_RecordGlobalState
	ldr	r3, [r8, #312]
	cmp	r3, #1
	beq	.L1352
.L1340:
	ldr	r3, [r4, #128]
	mov	r0, #1
	blx	r3
	ldr	r3, [r4, #128]
	mov	r0, #0
	blx	r3
	b	.L1338
.L1351:
	mov	r2, #0
	ldr	r3, [r4, #128]
	str	r2, [r8, #312]
	mov	r0, #1
	blx	r3
	b	.L1338
.L1352:
	add	r8, r9, #262144
	ldr	r3, [r8, #220]
	cmp	r3, #1
	beq	.L1353
.L1341:
	mov	r9, #0
	sub	r1, fp, #48
	str	r9, [r8, #212]
	mov	r0, r5
	bl	SM_DoNextInstance
	rsb	r7, r7, r10
	cmp	r0, r9
	bne	.L1342
	ldr	r1, [fp, #-48]
	add	r6, r6, r7
	mov	r2, #1
	ldr	r3, [r4]
	str	r2, [r6, #312]
	str	r1, [r6, #308]
	blx	r3
	str	r0, [r6, #316]
	b	.L1340
.L1342:
	add	r6, r6, r7
	ldr	r3, [r4, #128]
	mov	r0, #1
	str	r9, [r6, #312]
	blx	r3
	b	.L1340
.L1353:
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-56]
	ldr	r0, [r3, #4]
	bl	PrintScdRawState
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-56]
	ldr	r0, [r3, #4]
	bl	PrintScdSegState
	mov	r1, r5
	mov	r0, r9
	bl	ProcessScdReturn
	ldr	ip, [fp, #-64]
	mov	r0, ip
	bl	SCDDRV_MoveRawByOmxPath
	ldr	r9, [fp, #-60]
	ldr	r1, [fp, #-56]
	ldr	r0, [r9, #4]
	bl	PrintScdRawState
	ldr	r1, [fp, #-56]
	ldr	r0, [r9, #4]
	bl	PrintScdSegState
	b	.L1341
.L1355:
	.align	2
.L1354:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HalDisable
	.word	.LANCHOR3+584
	UNWIND(.fnend)
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.global	g_pScdDrvParamBase
	.global	s_ScdRegResetOKPhyAddr
	.global	s_ScdRegResetPhyAddr
	.global	s_ScdRegPhyBaseAddr
	.global	g_ScdDrvParam
	.global	s_SmIIS
	.global	ForceRelease
	.global	g_hex_flag
	.global	g_hex_len
	.global	g_hex_base_addr
	.global	g_hex_base_vir_addr
	.section	.rodata
	.align	2
.LANCHOR3 = . + 0
	.type	__func__.54298, %object
	.size	__func__.54298, 19
__func__.54298:
	.ascii	"SCDDRV_LoadDspCode\000"
	.space	1
	.type	__func__.54379, %object
	.size	__func__.54379, 16
__func__.54379:
	.ascii	"DeleteRawPacket\000"
	.type	__FUNCTION__.54489, %object
	.size	__FUNCTION__.54489, 17
__FUNCTION__.54489:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	__func__.54554, %object
	.size	__func__.54554, 14
__func__.54554:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
	.type	__func__.54638, %object
	.size	__func__.54638, 16
__func__.54638:
	.ascii	"SM_CopyRawToSeg\000"
	.type	__func__.54888, %object
	.size	__func__.54888, 16
__func__.54888:
	.ascii	"GetMeg4ModeFlag\000"
	.type	__func__.54915, %object
	.size	__func__.54915, 21
__func__.54915:
	.ascii	"ProcessMpeg4ScdUpMsg\000"
	.space	3
.LC0:
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-70
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	0
	.byte	0
	.byte	1
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.type	__func__.54958, %object
	.size	__func__.54958, 17
__func__.54958:
	.ascii	"FillEopRawStream\000"
	.space	3
.LC1:
	.byte	0
	.byte	0
	.byte	1
	.byte	11
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	98
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	__func__.54985, %object
	.size	__func__.54985, 17
__func__.54985:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.55009, %object
	.size	__func__.55009, 17
__func__.55009:
	.ascii	"FillVC1ExtraData\000"
	.space	3
	.type	__func__.55014, %object
	.size	__func__.55014, 19
__func__.55014:
	.ascii	"FillDIVX3ExtraData\000"
	.space	1
	.type	__func__.55019, %object
	.size	__func__.55019, 19
__func__.55019:
	.ascii	"FillREAL8ExtraData\000"
	.space	1
	.type	__func__.55027, %object
	.size	__func__.55027, 14
__func__.55027:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.54393, %object
	.size	__func__.54393, 24
__func__.54393:
	.ascii	"DeleteRawPacketInBuffer\000"
	.type	__FUNCTION__.54528, %object
	.size	__FUNCTION__.54528, 9
__FUNCTION__.54528:
	.ascii	"SM_Reset\000"
	.space	3
	.type	__func__.55180, %object
	.size	__func__.55180, 19
__func__.55180:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	__FUNCTION__.55247, %object
	.size	__FUNCTION__.55247, 17
__FUNCTION__.55247:
	.ascii	"PrintScdRawState\000"
	.space	3
	.type	__FUNCTION__.54948, %object
	.size	__FUNCTION__.54948, 12
__FUNCTION__.54948:
	.ascii	"FillRawData\000"
	.type	__FUNCTION__.55140, %object
	.size	__FUNCTION__.55140, 18
__FUNCTION__.55140:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.55186, %object
	.size	__func__.55186, 19
__func__.55186:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__func__.55206, %object
	.size	__func__.55206, 10
__func__.55206:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__FUNCTION__.55173, %object
	.size	__FUNCTION__.55173, 19
__FUNCTION__.55173:
	.ascii	"SM_SCDIntServeProc\000"
	.data
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 16368
	.type	g_avsp_firmware, %object
	.size	g_avsp_firmware, 17920
g_avsp_firmware:
	.word	0
	.word	16283648
	.word	16349954
	.word	9468936
	.word	-252085482
	.word	9468688
	.word	9468692
	.word	16284426
	.word	9468680
	.word	18807566
	.word	-258442240
	.word	10517258
	.word	18807566
	.word	-258442239
	.word	10517258
	.word	18807566
	.word	-258442238
	.word	10517258
	.word	18807566
	.word	-258442237
	.word	10517258
	.word	18807566
	.word	-258442236
	.word	10517258
	.word	18807566
	.word	-258442235
	.word	10517258
	.word	18807566
	.word	-258442234
	.word	10517258
	.word	18807566
	.word	-258442233
	.word	10517258
	.word	-251200754
	.word	10517258
	.word	17758990
	.word	33128448
	.word	24738824
	.word	-1879048192
	.word	16349954
	.word	0
	.word	18512896
	.word	33390592
	.word	24738817
	.word	-250447311
	.word	9468672
	.word	17988136
	.word	-795837688
	.word	12090128
	.word	18807566
	.word	24967950
	.word	-249398743
	.word	33259520
	.word	554859056
	.word	-258966784
	.word	19561007
	.word	-235307008
	.word	-1063027960
	.word	16349968
	.word	0
	.word	11041536
	.word	0
	.word	1073741824
	.word	33259520
	.word	554859057
	.word	9468672
	.word	0
	.word	-1342177280
	.word	0
	.word	33128448
	.word	-1592624595
	.word	-258966776
	.word	12090128
	.word	0
	.word	17988137
	.word	9468680
	.word	16349968
	.word	17988143
	.word	-258966784
	.word	0
	.word	33521664
	.word	-1879048192
	.word	0
	.word	-1610612736
	.word	-248874449
	.word	9468688
	.word	9468692
	.word	11041536
	.word	0
	.word	0
	.word	0
	.word	286948352
	.word	9467906
	.word	33128448
	.word	-1320519377
	.word	1630697896
	.word	33128448
	.word	-786269183
	.word	17988140
	.word	9468680
	.word	12090128
	.word	21953294
	.word	19400197
	.word	33128448
	.word	-1059883006
	.word	33062912
	.word	-1073741824
	.word	1358526466
	.word	-1342177280
	.word	-1879048192
	.word	17988009
	.word	1620081416
	.word	1354267408
	.word	21953294
	.word	19400216
	.word	33128448
	.word	-2133624830
	.word	33062912
	.word	-2147483648
	.word	-2131134462
	.word	19400222
	.word	33128448
	.word	0
	.word	19036462
	.word	33390592
	.word	33398784
	.word	1092253959
	.word	33128448
	.word	1362626056
	.word	17988013
	.word	9468680
	.word	12090128
	.word	21429006
	.word	1092253999
	.word	33128448
	.word	-250447444
	.word	9468680
	.word	12090128
	.word	24673282
	.word	-250447445
	.word	814775048
	.word	12090128
	.word	0
	.word	-785744896
	.word	556956675
	.word	33128448
	.word	-235298816
	.word	-235290624
	.word	25000964
	.word	-2147483648
	.word	33128448
	.word	-1050147328
	.word	18351619
	.word	18875907
	.word	554858927
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	-1845493760
	.word	23594500
	.word	18875906
	.word	554858927
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	872415232
	.word	-2147483648
	.word	18351646
	.word	24926480
	.word	-2124785392
	.word	-2147483648
	.word	0
	.word	19028272
	.word	20601264
	.word	554858927
	.word	10517258
	.word	546339592
	.word	0
	.word	-268435456
	.word	-1592100601
	.word	12090128
	.word	33128448
	.word	1634207232
	.word	18351619
	.word	18875907
	.word	554859050
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-771751936
	.word	23594500
	.word	18875906
	.word	554859050
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-1543503872
	.word	1073741824
	.word	18351646
	.word	24926480
	.word	1096440080
	.word	-2147483648
	.word	17988138
	.word	19028272
	.word	20601264
	.word	536870912
	.word	10517258
	.word	9468680
	.word	17988139
	.word	9468680
	.word	0
	.word	-1879048192
	.word	1366850566
	.word	33398784
	.word	17987886
	.word	33398784
	.word	33398784
	.word	-518882770
	.word	9468680
	.word	16349968
	.word	0
	.word	-536870912
	.word	1903720450
	.word	1092093440
	.word	17988010
	.word	9468680
	.word	12090128
	.word	18807566
	.word	33259520
	.word	293436421
	.word	25000967
	.word	-1055753810
	.word	9468680
	.word	12090128
	.word	0
	.word	33460224
	.word	33460224
	.word	33198080
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	0
	.word	0
	.word	1013760
	.word	18687
	.word	0
	.word	0
	.word	18688
	.word	0
	.word	0
	.word	103084
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	102700
	.word	0
	.word	18432
	.word	916608
	.word	0
	.word	1027074
	.word	0
	.word	1013760
	.word	18432
	.word	916620
	.word	908352
	.word	1027075
	.word	0
	.word	1013760
	.word	105964
	.word	0
	.word	1013760
	.word	0
	.word	1031171
	.word	916484
	.word	1031173
	.word	98348
	.word	1013760
	.word	904428
	.word	1027075
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	1027075
	.word	916484
	.word	1031173
	.word	0
	.word	1013760
	.word	1035269
	.word	1031168
	.word	916712
	.word	1031172
	.word	23807
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	98348
	.word	1013760
	.word	916484
	.word	1031170
	.word	1007616
	.word	1018885
	.word	18687
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	1018880
	.word	1007616
	.word	18432
	.word	20480
	.word	916688
	.word	1031175
	.word	23552
	.word	916696
	.word	1027078
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	108112
	.word	917096
	.word	1031174
	.word	917076
	.word	1027078
	.word	25600
	.word	1018887
	.word	23553
	.word	908752
	.word	19456
	.word	22528
	.word	1013760
	.word	108112
	.word	917096
	.word	1031175
	.word	917076
	.word	1027079
	.word	25601
	.word	108108
	.word	917076
	.word	222628
	.word	19456
	.word	917068
	.word	917072
	.word	1027086
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	23552
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	1013760
	.word	1027080
	.word	23552
	.word	0
	.word	1013760
	.word	19457
	.word	20480
	.word	916756
	.word	916908
	.word	916844
	.word	0
	.word	1027083
	.word	917068
	.word	1027082
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989193
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989194
	.word	1018891
	.word	113316
	.word	112296
	.word	1031179
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	23552
	.word	1013760
	.word	988170
	.word	23553
	.word	0
	.word	917068
	.word	1027085
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989195
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989196
	.word	1018894
	.word	113316
	.word	112296
	.word	1031182
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	988173
	.word	19456
	.word	917068
	.word	19456
	.word	917068
	.word	917064
	.word	1027086
	.word	0
	.word	0
	.word	1013760
	.word	1018894
	.word	23552
	.word	1027087
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	916712
	.word	23556
	.word	0
	.word	1027087
	.word	0
	.word	0
	.word	1013760
	.word	999424
	.word	999424
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	1900544
	.word	513
	.word	1537
	.word	352782197
	.word	352782197
	.word	65536
	.word	131074
	.word	4
	.word	0
	.word	65537
	.word	131073
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	2
	.word	327686
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131072
	.word	1
	.word	131072
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65538
	.word	1
	.word	0
	.word	0
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	131072
	.word	1
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	0
	.word	0
	.word	2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	524289
	.word	4196352
	.word	1048608
	.word	8396800
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	0
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	65537
	.word	65537
	.word	1
	.word	65536
	.word	1
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131073
	.word	33554688
	.word	1073741828
	.word	132096
	.word	65540
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_h264_firmware, %object
	.size	g_h264_firmware, 17920
g_h264_firmware:
	.word	0
	.word	823064910
	.word	8419328
	.word	9239400
	.word	16349184
	.word	285670144
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	0
	.word	8420384
	.word	8420386
	.word	8420387
	.word	8420388
	.word	8420389
	.word	8420390
	.word	8420391
	.word	8420393
	.word	8420394
	.word	8420395
	.word	8420392
	.word	8420396
	.word	8715424
	.word	8715428
	.word	8682668
	.word	8682542
	.word	8682671
	.word	268435456
	.word	8420385
	.word	-1342177280
	.word	24673452
	.word	-268435456
	.word	24673326
	.word	1610612736
	.word	17234198
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	1610612736
	.word	0
	.word	536870912
	.word	1610612736
	.word	24673326
	.word	-536870912
	.word	17234200
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	-536870912
	.word	268435456
	.word	536870912
	.word	1610612736
	.word	24673455
	.word	1610612736
	.word	24935457
	.word	1610612736
	.word	24706208
	.word	1610612736
	.word	0
	.word	536870912
	.word	16349184
	.word	17758488
	.word	8715034
	.word	9239322
	.word	0
	.word	17234228
	.word	17758984
	.word	17758980
	.word	268435456
	.word	0
	.word	-234913792
	.word	1342177280
	.word	21428994
	.word	23525654
	.word	21952790
	.word	20904718
	.word	17758520
	.word	0
	.word	17234288
	.word	18282794
	.word	18807142
	.word	-2147483648
	.word	19331382
	.word	17235072
	.word	18283652
	.word	0
	.word	8715418
	.word	0
	.word	9763996
	.word	33325056
	.word	-1610612736
	.word	18282774
	.word	824113430
	.word	9239710
	.word	17235098
	.word	1610612736
	.word	16349184
	.word	9239710
	.word	17235098
	.word	17758988
	.word	0
	.word	805306368
	.word	17235098
	.word	18283278
	.word	18807964
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	-1879048192
	.word	33128448
	.word	-1861813906
	.word	33128448
	.word	822540652
	.word	33128448
	.word	-536870912
	.word	0
	.word	-1073741824
	.word	24673280
	.word	805306368
	.word	16349184
	.word	17234704
	.word	19037185
	.word	-2129725162
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	805306368
	.word	24673296
	.word	805306368
	.word	16349184
	.word	17234706
	.word	19037201
	.word	-2129725088
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	17235098
	.word	17759388
	.word	18283678
	.word	8715424
	.word	9239714
	.word	9764004
	.word	14711981
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	21952864
	.word	-2147483648
	.word	16349184
	.word	17234228
	.word	17758984
	.word	0
	.word	17758980
	.word	268435456
	.word	33062912
	.word	-2147483648
	.word	-235175936
	.word	0
	.word	-235110400
	.word	-2147483648
	.word	16349184
	.word	17234288
	.word	17758978
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	20904718
	.word	17758520
	.word	0
	.word	19331382
	.word	17235072
	.word	0
	.word	0
	.word	8715420
	.word	16349184
	.word	17235100
	.word	17758982
	.word	0
	.word	17758988
	.word	33259520
	.word	-805306368
	.word	17235100
	.word	17758982
	.word	805306368
	.word	18282774
	.word	18807062
	.word	1879048192
	.word	17235100
	.word	17758988
	.word	0
	.word	0
	.word	805306368
	.word	17235100
	.word	18283278
	.word	18807558
	.word	0
	.word	805306368
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	1073741824
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420524
	.word	24706208
	.word	-2147483648
	.word	17759396
	.word	33521664
	.word	-536870912
	.word	17235104
	.word	17759396
	.word	18282774
	.word	18807062
	.word	-1879048192
	.word	16349184
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	17235104
	.word	18283278
	.word	18807970
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33390592
	.word	0
	.word	536870912
	.word	33390592
	.word	-2147483648
	.word	268435456
	.word	1879048192
	.word	268435456
	.word	268435456
	.word	8420524
	.word	0
	.word	0
	.word	8420398
	.word	0
	.word	16349184
	.word	17234708
	.word	8715430
	.word	17758498
	.word	0
	.word	8715432
	.word	17758488
	.word	18807562
	.word	1073741824
	.word	0
	.word	805306368
	.word	8419328
	.word	16940070
	.word	17758514
	.word	0
	.word	-250676968
	.word	-268435456
	.word	1342177280
	.word	17758488
	.word	-268435456
	.word	1610612736
	.word	0
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715104
	.word	268435456
	.word	-536870912
	.word	8715106
	.word	16349184
	.word	17234708
	.word	805306368
	.word	10516480
	.word	8715108
	.word	17235088
	.word	8715110
	.word	17234214
	.word	8715120
	.word	17234244
	.word	8715118
	.word	16940060
	.word	-268435456
	.word	-805306368
	.word	17464339
	.word	-268435456
	.word	-1073741824
	.word	17464340
	.word	-268435456
	.word	-1323894504
	.word	17464322
	.word	0
	.word	-268435456
	.word	-1610612736
	.word	17464324
	.word	-268435456
	.word	268435456
	.word	24673285
	.word	-2147483648
	.word	17758486
	.word	805306368
	.word	24673316
	.word	-512197595
	.word	-1055983330
	.word	805306368
	.word	17758488
	.word	805306368
	.word	24673286
	.word	286193958
	.word	805306368
	.word	17758486
	.word	805306368
	.word	-536870912
	.word	17464323
	.word	0
	.word	8715328
	.word	17235110
	.word	18282776
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234710
	.word	8715330
	.word	1090976934
	.word	0
	.word	286718232
	.word	18807144
	.word	-2147483648
	.word	17235112
	.word	8715332
	.word	1090976934
	.word	0
	.word	555153688
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234712
	.word	8715334
	.word	-2130248538
	.word	0
	.word	823589144
	.word	18807144
	.word	-2147483648
	.word	17235090
	.word	8715336
	.word	16940202
	.word	8715338
	.word	17235092
	.word	33259520
	.word	-1610612736
	.word	0
	.word	8715340
	.word	17235094
	.word	8715342
	.word	16940203
	.word	8715344
	.word	17235096
	.word	33259520
	.word	805306368
	.word	0
	.word	8715346
	.word	-1593672675
	.word	17464365
	.word	0
	.word	-268435456
	.word	-1342177280
	.word	822770723
	.word	0
	.word	-268435456
	.word	-1879048192
	.word	17464353
	.word	0
	.word	8715348
	.word	-251495381
	.word	0
	.word	-268435456
	.word	1628077098
	.word	0
	.word	-268435456
	.word	268435456
	.word	17464327
	.word	-536870912
	.word	17464354
	.word	18807064
	.word	33128448
	.word	0
	.word	33128448
	.word	536870912
	.word	1091500310
	.word	268435456
	.word	1073741824
	.word	536870912
	.word	1073741824
	.word	0
	.word	8715350
	.word	17235112
	.word	1092024672
	.word	18807144
	.word	-2147483648
	.word	16940070
	.word	17758514
	.word	0
	.word	-268435456
	.word	8715352
	.word	17235112
	.word	0
	.word	-1055459048
	.word	18807144
	.word	-2147483648
	.word	0
	.word	8715354
	.word	-1056506712
	.word	0
	.word	-787023592
	.word	18807144
	.word	-2147483648
	.word	0
	.word	554173952
	.word	17827336
	.word	1879048192
	.word	-251200684
	.word	0
	.word	8420526
	.word	822609408
	.word	17827352
	.word	1879048192
	.word	-1073741824
	.word	11566081
	.word	-250446847
	.word	33325056
	.word	-805306368
	.word	17988609
	.word	33325056
	.word	-805306368
	.word	20085934
	.word	554203411
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-2130151150
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-519538416
	.word	33128448
	.word	0
	.word	33128448
	.word	16808209
	.word	33128448
	.word	0
	.word	-805306368
	.word	1091074311
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-1593280239
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566082
	.word	17827329
	.word	0
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	33390592
	.word	-268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1073741824
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	805306368
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	286193948
	.word	0
	.word	33062912
	.word	-1073741824
	.word	-1342177280
	.word	-234881024
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	536870912
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1610612736
	.word	0
	.word	286193964
	.word	0
	.word	33062912
	.word	-1342177280
	.word	-1610612736
	.word	-536870912
	.word	-268435456
	.word	268435456
	.word	8420354
	.word	-1073741824
	.word	11566088
	.word	-1073741824
	.word	33259520
	.word	1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566089
	.word	0
	.word	33128448
	.word	268435456
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-805306368
	.word	-805306368
	.word	-1073741824
	.word	11566091
	.word	-1073741824
	.word	33521664
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	8420362
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	1879048192
	.word	1879048192
	.word	-1073741824
	.word	11566254
	.word	-268435456
	.word	33259520
	.word	-805306368
	.word	0
	.word	33521664
	.word	-805306368
	.word	16940206
	.word	0
	.word	1879048192
	.word	-1342177280
	.word	-1073741824
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	11566083
	.word	286193960
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	-1073741824
	.word	11566084
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566085
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33128448
	.word	1610612736
	.word	-2147483648
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566086
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	286193946
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	825392131
	.word	33325056
	.word	-805306368
	.word	0
	.word	0
	.word	8420358
	.word	286193956
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566087
	.word	24673455
	.word	-805306368
	.word	822609409
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	8420352
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420352
	.word	0
	.word	-1073741824
	.word	11566097
	.word	17827583
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566098
	.word	17827359
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566099
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566101
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-1342177280
	.word	-1073741824
	.word	11566103
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566104
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566106
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827330
	.word	1879048192
	.word	20380500
	.word	11566107
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	805306368
	.word	33062912
	.word	-1342177280
	.word	-805306368
	.word	11566109
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566105
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566100
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566102
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17234198
	.word	8420380
	.word	822541470
	.word	17759062
	.word	0
	.word	33521664
	.word	805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566108
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935452
	.word	805306368
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	33390592
	.word	268435456
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17235102
	.word	17759062
	.word	33521664
	.word	-536870912
	.word	-268435456
	.word	0
	.word	8420380
	.word	805306368
	.word	268435456
	.word	8420380
	.word	24673455
	.word	-1342177280
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420368
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420368
	.word	0
	.word	-1073741824
	.word	11566113
	.word	17758528
	.word	33062912
	.word	268435456
	.word	-1073741824
	.word	536870912
	.word	33128448
	.word	1610612736
	.word	1073741824
	.word	33128448
	.word	1610612736
	.word	1879048192
	.word	33128448
	.word	1610612736
	.word	-1879048192
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	-1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	33128448
	.word	-1879048192
	.word	-2147483648
	.word	33128448
	.word	-1879048192
	.word	268435456
	.word	33128448
	.word	-1073741824
	.word	1610612736
	.word	33128448
	.word	-1073741824
	.word	268435456
	.word	536870912
	.word	8944674
	.word	-536870912
	.word	0
	.word	8944674
	.word	-536870912
	.word	268435456
	.word	8944674
	.word	-1073741824
	.word	11566112
	.word	-268435456
	.word	33259520
	.word	268435456
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-1610612736
	.word	805306368
	.word	16349184
	.word	17758994
	.word	19037216
	.word	-2130249376
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935440
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	268435456
	.word	822609408
	.word	1092254728
	.word	0
	.word	1879048192
	.word	0
	.word	8420388
	.word	8420389
	.word	24673285
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566116
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673316
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566117
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940035
	.word	17464324
	.word	-268435456
	.word	-268435456
	.word	-2147483648
	.word	8420390
	.word	24673285
	.word	-1610612736
	.word	24673316
	.word	-1610612736
	.word	554335270
	.word	-2147483648
	.word	8420390
	.word	554335236
	.word	-268435456
	.word	-2147483648
	.word	268435456
	.word	0
	.word	8420356
	.word	285375524
	.word	17464326
	.word	0
	.word	8420391
	.word	1359641640
	.word	33390592
	.word	1342177280
	.word	-1073741824
	.word	17758528
	.word	33259520
	.word	268435456
	.word	17464329
	.word	33390592
	.word	536870912
	.word	822609408
	.word	1092254731
	.word	0
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	536870912
	.word	1879048192
	.word	16940041
	.word	285899786
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	24935446
	.word	1073741824
	.word	-1073741824
	.word	0
	.word	33259520
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940055
	.word	17464344
	.word	8420394
	.word	8944683
	.word	554335266
	.word	33128448
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566121
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935465
	.word	1610612736
	.word	-1073741824
	.word	11566122
	.word	285899810
	.word	33390592
	.word	1610612736
	.word	-1073741824
	.word	11566123
	.word	554335266
	.word	33390592
	.word	-1342177280
	.word	0
	.word	8420394
	.word	285899810
	.word	33128448
	.word	0
	.word	0
	.word	8420395
	.word	554335266
	.word	33390592
	.word	1073741824
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	1610612736
	.word	0
	.word	554335274
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	536870912
	.word	268435456
	.word	33128448
	.word	536870912
	.word	536870912
	.word	33128448
	.word	1073741824
	.word	1342177280
	.word	1879048192
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	-1342177280
	.word	0
	.word	554335275
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	-1342177280
	.word	0
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-1879048192
	.word	-1610612736
	.word	1879048192
	.word	-1610612736
	.word	1879048192
	.word	1610612736
	.word	17464354
	.word	286948379
	.word	33390592
	.word	293108762
	.word	-2147483648
	.word	1879048192
	.word	17464354
	.word	33390592
	.word	1879048192
	.word	-235044864
	.word	1879048192
	.word	-2147483648
	.word	536870912
	.word	-1073741824
	.word	24673282
	.word	-1073741824
	.word	-1073741824
	.word	17464362
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-268435456
	.word	285899810
	.word	17988635
	.word	33390592
	.word	536870912
	.word	-235044864
	.word	536870912
	.word	17464363
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	268435456
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	1342177280
	.word	24673324
	.word	-536870912
	.word	1359641640
	.word	33390592
	.word	-1342177280
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-536870912
	.word	-1073741824
	.word	11566254
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	1879048192
	.word	1073741824
	.word	33128448
	.word	1879048192
	.word	1610612736
	.word	33128448
	.word	1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	-1073741824
	.word	-1342177280
	.word	-1073741824
	.word	-1073741824
	.word	16940206
	.word	33259520
	.word	1342177280
	.word	24673299
	.word	-1073741824
	.word	16940066
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	-1073741824
	.word	-1073741824
	.word	11566115
	.word	805306368
	.word	33062912
	.word	268435456
	.word	-805306368
	.word	11566125
	.word	24935449
	.word	-1879048192
	.word	-1073741824
	.word	536870912
	.word	33259520
	.word	268435456
	.word	17827329
	.word	33128448
	.word	-1879048192
	.word	-805306368
	.word	-805306368
	.word	24673455
	.word	268435456
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420398
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420398
	.word	0
	.word	1073741824
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1073741824
	.word	11565056
	.word	19331386
	.word	20379926
	.word	33390592
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	11860806
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	9763660
	.word	11860814
	.word	10287952
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	0
	.word	0
	.word	11336518
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	11860812
	.word	19855676
	.word	0
	.word	805306368
	.word	11336526
	.word	10287952
	.word	268435456
	.word	8715074
	.word	0
	.word	1073741824
	.word	11565056
	.word	823064854
	.word	18282784
	.word	1879048192
	.word	554629398
	.word	18282848
	.word	1879048192
	.word	-251200684
	.word	17758502
	.word	1342177280
	.word	9468968
	.word	9993260
	.word	823064854
	.word	18282848
	.word	1879048192
	.word	0
	.word	0
	.word	33390592
	.word	-1342177280
	.word	16349184
	.word	-2129724670
	.word	18906285
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	18906285
	.word	-2129725072
	.word	18282782
	.word	18807144
	.word	-2147483648
	.word	1879048192
	.word	16349184
	.word	-2129724670
	.word	19331848
	.word	-268435456
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	17234694
	.word	17759362
	.word	0
	.word	9239686
	.word	17234694
	.word	17759360
	.word	18283276
	.word	33259520
	.word	-536870912
	.word	805306368
	.word	17235072
	.word	17758988
	.word	18283270
	.word	18283278
	.word	0
	.word	9239684
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	19331848
	.word	-268435456
	.word	-2129725072
	.word	18282794
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	287767304
	.word	0
	.word	8715016
	.word	0
	.word	536870912
	.word	10516480
	.word	8715042
	.word	277674784
	.word	546634532
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	-2147483648
	.word	33128448
	.word	-1073741824
	.word	-268435456
	.word	268435456
	.word	8715046
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715048
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715050
	.word	0
	.word	0
	.word	1073741824
	.word	11565056
	.word	20380502
	.word	24935443
	.word	-1879048192
	.word	1898379590
	.word	0
	.word	0
	.word	0
	.word	16349184
	.word	0
	.word	33390592
	.word	-1879048192
	.word	17235104
	.word	17759394
	.word	33259520
	.word	1610612736
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	1610612736
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17759394
	.word	0
	.word	805306368
	.word	10288280
	.word	1342177280
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234702
	.word	17759394
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235104
	.word	17759396
	.word	-1879048192
	.word	17235100
	.word	17758982
	.word	18283276
	.word	33259520
	.word	1342177280
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	805306368
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17758982
	.word	823590036
	.word	0
	.word	10288280
	.word	1073741824
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234694
	.word	17759388
	.word	18283276
	.word	0
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235100
	.word	17758982
	.word	805306368
	.word	-1879048192
	.word	19331386
	.word	0
	.word	10288272
	.word	19331388
	.word	0
	.word	805306368
	.word	19331374
	.word	0
	.word	11041962
	.word	0
	.word	9239700
	.word	19331390
	.word	0
	.word	805306368
	.word	11336850
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	0
	.word	1090520577
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17758538
	.word	20380498
	.word	18807090
	.word	0
	.word	33128448
	.word	-1055983284
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1090520576
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234226
	.word	20380498
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	1610612736
	.word	268435456
	.word	8420527
	.word	0
	.word	18875904
	.word	0
	.word	1091044864
	.word	546863104
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234772
	.word	0
	.word	17455440
	.word	16778756
	.word	33390592
	.word	-1342177280
	.word	1091044864
	.word	815298560
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17303041
	.word	17827336
	.word	33325056
	.word	-1879048192
	.word	17303072
	.word	33062912
	.word	268435456
	.word	285738497
	.word	18351620
	.word	-2147483648
	.word	0
	.word	17827352
	.word	33062912
	.word	1073741824
	.word	17303064
	.word	0
	.word	1091044864
	.word	815298560
	.word	17827352
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	536870912
	.word	1091044864
	.word	815298560
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	-536870912
	.word	1091044864
	.word	815298560
	.word	-2147483648
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	8420527
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	916484
	.word	1031168
	.word	1018880
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035272
	.word	0
	.word	1031172
	.word	0
	.word	1027080
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031171
	.word	1018883
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031176
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1027079
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031174
	.word	1018886
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031175
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1031176
	.word	0
	.word	1027080
	.word	0
	.word	1027080
	.word	16384
	.word	1035355
	.word	0
	.word	16384
	.word	0
	.word	0
	.word	1007616
	.word	0
	.word	0
	.word	589828
	.word	99972
	.word	622596
	.word	901164
	.word	1031182
	.word	0
	.word	109184
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	107044
	.word	100000
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	592016
	.word	100508
	.word	0
	.word	902272
	.word	1031178
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018891
	.word	17408
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031181
	.word	916612
	.word	1031181
	.word	916608
	.word	1031180
	.word	916608
	.word	1031180
	.word	1018894
	.word	1035295
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	1035312
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	983049
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	0
	.word	99972
	.word	916484
	.word	1031188
	.word	916524
	.word	1031184
	.word	916524
	.word	1031188
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	916484
	.word	1031184
	.word	0
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018897
	.word	0
	.word	0
	.word	902208
	.word	103044
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904400
	.word	69260
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	916612
	.word	1031188
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	1027092
	.word	16384
	.word	916544
	.word	1031186
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018899
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	1018900
	.word	916612
	.word	1031188
	.word	1035322
	.word	1018900
	.word	1035322
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	0
	.word	0
	.word	102028
	.word	592972
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	69260
	.word	69260
	.word	69260
	.word	606220
	.word	0
	.word	16384
	.word	66176
	.word	0
	.word	0
	.word	0
	.word	20480
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	66176
	.word	66176
	.word	0
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	1027096
	.word	0
	.word	1018905
	.word	0
	.word	1027096
	.word	1027096
	.word	1018905
	.word	0
	.word	1018905
	.word	0
	.word	1027097
	.word	1018905
	.word	0
	.word	1018905
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17409
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	17410
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17414
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031195
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031196
	.word	16384
	.word	0
	.word	17409
	.word	98308
	.word	98308
	.word	66176
	.word	66176
	.word	18432
	.word	590980
	.word	67204
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	18433
	.word	589832
	.word	66176
	.word	66176
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	606212
	.word	18432
	.word	916552
	.word	1031198
	.word	916556
	.word	1031198
	.word	1018910
	.word	17408
	.word	1018910
	.word	17408
	.word	1018910
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	0
	.word	17419
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	16384
	.word	0
	.word	17423
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	17423
	.word	589828
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16385
	.word	916488
	.word	1031215
	.word	16384
	.word	916608
	.word	1031215
	.word	0
	.word	16388
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16389
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	916864
	.word	1031202
	.word	1031215
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16391
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	1018920
	.word	1035374
	.word	0
	.word	17408
	.word	902532
	.word	903560
	.word	605256
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031208
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027110
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031206
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031206
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031206
	.word	1018917
	.word	990244
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027112
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031208
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031208
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031208
	.word	1018919
	.word	990246
	.word	1018920
	.word	16384
	.word	0
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1027113
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035376
	.word	1035376
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031215
	.word	17408
	.word	916868
	.word	1031211
	.word	29696
	.word	110208
	.word	1035376
	.word	988203
	.word	1035374
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16384
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	1035374
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031213
	.word	1018926
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	916864
	.word	1031215
	.word	1018927
	.word	16384
	.word	0
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031217
	.word	1018929
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	17408
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031225
	.word	1035372
	.word	0
	.word	1035372
	.word	1035372
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	18432
	.word	0
	.word	901124
	.word	901128
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031225
	.word	20480
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	916880
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	916484
	.word	1031224
	.word	1018935
	.word	16384
	.word	0
	.word	1018937
	.word	16384
	.word	0
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	0
	.word	916868
	.word	1031254
	.word	1035374
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	1018966
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031254
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031229
	.word	1018941
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	1031232
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027136
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	98348
	.word	99436
	.word	294916
	.word	0
	.word	0
	.word	1031233
	.word	0
	.word	1031233
	.word	16384
	.word	294916
	.word	0
	.word	16384
	.word	99436
	.word	294916
	.word	17408
	.word	901124
	.word	0
	.word	18432
	.word	49160
	.word	589828
	.word	0
	.word	16384
	.word	916544
	.word	1031234
	.word	1035374
	.word	0
	.word	916868
	.word	1031254
	.word	16384
	.word	916544
	.word	1031235
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	0
	.word	18432
	.word	50248
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	1031236
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	16384
	.word	916484
	.word	1031236
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	916544
	.word	1031238
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	1018953
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031241
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	18432
	.word	916872
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	1018953
	.word	1035376
	.word	1018953
	.word	1035376
	.word	983112
	.word	16384
	.word	902148
	.word	1031243
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031243
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	18432
	.word	916872
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	1018955
	.word	1035376
	.word	1018955
	.word	1035376
	.word	983114
	.word	16384
	.word	18432
	.word	901124
	.word	1031244
	.word	1031244
	.word	1018956
	.word	0
	.word	916612
	.word	1031244
	.word	130284
	.word	1031244
	.word	1018956
	.word	1018961
	.word	1035374
	.word	0
	.word	1027148
	.word	1035374
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027149
	.word	1035372
	.word	1035372
	.word	0
	.word	1027150
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027150
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983116
	.word	16384
	.word	0
	.word	916484
	.word	1031249
	.word	916652
	.word	1031249
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027152
	.word	1035372
	.word	1035372
	.word	0
	.word	1027153
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027153
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983119
	.word	0
	.word	1027155
	.word	16384
	.word	916544
	.word	1031249
	.word	16384
	.word	0
	.word	1035350
	.word	1018963
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027155
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	1018963
	.word	1035374
	.word	1018963
	.word	1035374
	.word	1035374
	.word	17408
	.word	916484
	.word	1031250
	.word	0
	.word	1027156
	.word	17408
	.word	916484
	.word	1031252
	.word	18432
	.word	916488
	.word	1031252
	.word	1018964
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031254
	.word	1035372
	.word	0
	.word	0
	.word	1031253
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	0
	.word	916872
	.word	1031253
	.word	1035372
	.word	1035372
	.word	0
	.word	1031254
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031255
	.word	1018967
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	0
	.word	916632
	.word	1031256
	.word	594960
	.word	0
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018969
	.word	595088
	.word	0
	.word	593936
	.word	906516
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	595092
	.word	71316
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	17409
	.word	591876
	.word	98944
	.word	592900
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	999424
	.word	17408
	.word	916484
	.word	1031260
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	1018975
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	916552
	.word	1031261
	.word	1018974
	.word	0
	.word	0
	.word	902208
	.word	902276
	.word	99460
	.word	0
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	0
	.word	16384
	.word	98560
	.word	0
	.word	999424
	.word	20480
	.word	0
	.word	20480
	.word	21504
	.word	22528
	.word	916688
	.word	1031264
	.word	916692
	.word	1031264
	.word	916696
	.word	1031264
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	108184
	.word	1031265
	.word	19456
	.word	104664
	.word	596248
	.word	108184
	.word	0
	.word	17408
	.word	916484
	.word	1031270
	.word	0
	.word	0
	.word	916544
	.word	1031270
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027172
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	904264
	.word	69260
	.word	0
	.word	1018982
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	904256
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	98308
	.word	916608
	.word	1031275
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027177
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	67204
	.word	904264
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	0
	.word	903300
	.word	904200
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	67204
	.word	1018987
	.word	0
	.word	592912
	.word	0
	.word	0
	.word	592912
	.word	69260
	.word	101592
	.word	595152
	.word	0
	.word	902244
	.word	0
	.word	0
	.word	595152
	.word	104084
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	590936
	.word	596184
	.word	916544
	.word	1031277
	.word	612440
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	1018990
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	595992
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	1018992
	.word	16384
	.word	0
	.word	999424
	.word	21504
	.word	22528
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	113280
	.word	0
	.word	102660
	.word	916544
	.word	1031282
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	104836
	.word	916872
	.word	1031280
	.word	104080
	.word	916804
	.word	1031285
	.word	70288
	.word	102660
	.word	295128
	.word	905472
	.word	104080
	.word	916628
	.word	1031284
	.word	0
	.word	905476
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018995
	.word	19456
	.word	16384
	.word	101008
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018997
	.word	19456
	.word	16384
	.word	299224
	.word	903504
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031286
	.word	1018998
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	7208960
	.word	513
	.word	1537
	.word	319365736
	.word	319365736
	.word	9437306
	.word	5046372
	.word	0
	.word	0
	.word	1
	.word	131
	.word	16
	.word	2
	.word	24
	.word	256
	.word	263
	.word	3
	.word	351
	.word	4
	.word	64
	.word	127
	.word	262143
	.word	1048575
	.word	4194303
	.word	2147483647
	.word	-2147483648
	.word	-16
	.word	15
	.word	-128
	.word	8192
	.word	1048576
	.word	96000
	.word	-8
	.word	-1
	.word	262144
	.word	-524288
	.word	65280000
	.word	196612
	.word	131074
	.word	65537
	.word	65537
	.word	0
	.word	0
	.word	0
	.word	0
	.word	8
	.word	8160
	.word	255
	.word	0
	.word	1
	.word	5
	.word	8
	.word	7
	.word	64
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_pScdDrvParamBase, %object
	.size	g_pScdDrvParamBase, 4
g_pScdDrvParamBase:
	.word	g_ScdDrvParam
	.type	g_hex_flag, %object
	.size	g_hex_flag, 4
g_hex_flag:
	.word	1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"line: %d, p = NULL is not expected value!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC4:
	ASCII(.ascii	"Warn: eVidStd = %d have not DSP vfmw bin file!!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC5:
	ASCII(.ascii	"%s failed!\012\000" )
.LC6:
	ASCII(.ascii	"%s success!\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"Ignore the reset request when the SCD[%d] clock is " )
	ASCII(.ascii	"closed.\012\000" )
.LC8:
	ASCII(.ascii	"SCD[%d]   ResetSCD ERROR!!!\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"line: %d Get SmID fail!\000" )
.LC10:
	ASCII(.ascii	"DelRaw err PacketNum = %d, DelNum = %d\012\000" )
.LC11:
	ASCII(.ascii	"%s release RawPhyAddr = 0x%x,Len = %d\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = " )
	ASCII(.ascii	"%d,Next Length = %d,is_extern_eop_flag = %d\012\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC13:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,Next Leng" )
	ASCII(.ascii	"th = %d\012\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"line: %d pSmInstArray is NULL!\012\000" )
.LC15:
	ASCII(.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast" )
	ASCII(.ascii	"Seg=%d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"-------- forece release seg[%d] -----------\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"0x%02x,\000" )
.LC19:
	ASCII(.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg" )
	ASCII(.ascii	"=%d StreamID=%d\012\000" )
.LC20:
	ASCII(.ascii	"Array out of bound in function %s\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"ScdId is wrong! %s error\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"%s,line: %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"%s: g_hex_base_vir_addr = NULL\012\000" )
.LC24:
	ASCII(.ascii	"line: %d, SmID = %d, pSmCfg = %p is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC25:
	ASCII(.ascii	"line: %d, SmID = %d is not expected!\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC27:
	ASCII(.ascii	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC28:
	ASCII(.ascii	"line: %d, delet raw failed!\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"[%s %d] VirAddr is null!!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"copy raw to seg fail\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"Line: %d, start code num from scd state reg: %d, re" )
	ASCII(.ascii	"lease raw packet anyway!\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"Error, discard raw packet!\012\000" )
.LC33:
	ASCII(.ascii	"Line: %d, The length of seg packet is invalid: %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC34:
	ASCII(.ascii	"[%s %d] pCurrentStartCodeVirAddr is null!!\012\000" )
.LC35:
	ASCII(.ascii	"[%s %d] pNextStartCodeVirAddr is null!!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"ValidSegNum = %d, FilteredSegNum = 0, release raw p" )
	ASCII(.ascii	"acket anyway!\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"%s: pRawPacket = NULL!\012\000" )
.LC38:
	ASCII(.ascii	"%s: unkown standard type = %d!\012\000" )
.LC39:
	ASCII(.ascii	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"%s: FlagLen(%d) > RawPacketLength(%d)\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, head" )
	ASCII(.ascii	"er_buf: %d)\012\000" )
.LC42:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, str_" )
	ASCII(.ascii	"buf: %d)\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf: %d, header_buf: %d)\012\000" )
.LC44:
	ASCII(.ascii	"Func: %s, buffer has no enough space, (act: %d, str" )
	ASCII(.ascii	"_buf: %d)\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf:%d)\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"%s: RawPacket Length %d <= 0\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReleaseRawStreamData pStreamIntf is NULL!\000" )
.LC48:
	ASCII(.ascii	"line: %d s_SmIIS[%d].pSmInstArray is NULL\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"SmID = %d is not expected!\012\000" )
.LC50:
	ASCII(.ascii	"%s release RawPhyAddr = 0x%x, Len = %d\012\000" )
.LC51:
	ASCII(.ascii	"line: %d, pSmInstArray is NULL!\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"%s %d force to clear SCDState = 0\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum !!\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000" )
	.space	3
.LC55:
	ASCII(.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"Chan %d FillEosRawStream failed!\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"Chan %d FillExtraData failed!\012\000" )
	.space	1
.LC58:
	ASCII(.ascii	"Release this packet failed!\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"(%d ms) not release stream seg, release anyway!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC61:
	ASCII(.ascii	"Error:now DspState[0]= %d,[1]= %d not except!!\012\000" )
.LC62:
	ASCII(.ascii	"Move raw data failed, force to reset scd.\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"SCD GetRawStreamNum Fail.\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\012\000" )
.LC67:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"scd time out: t_start,t_now,t_wait = %d,%d,%d\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"***Print Scd[%d] Vtrl Reg Now\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"DownMsgPhyAddr = %x\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"UpMsgPhyAddr = %x\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"UpLen = %x\012\000" )
.LC73:
	ASCII(.ascii	"BufferFirst = %x\012\000" )
	.space	2
.LC74:
	ASCII(.ascii	"BufferLast = %x\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"BufferIni = %x\012\000" )
.LC76:
	ASCII(.ascii	"ScdProtocol = %x\012\000" )
	.space	2
.LC77:
	ASCII(.ascii	"ScdStart = %x\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"***Print SCD[%d] Down Msg Now\012\000" )
	.space	1
.LC79:
	ASCII(.ascii	"DownMsgVirAddr = %x   \012\000" )
.LC80:
	ASCII(.ascii	"DownMsgPhyAddr = %x   \012\000" )
.LC81:
	ASCII(.ascii	"DownMsg[%d] = %x   \000" )
.LC82:
	ASCII(.ascii	"Cann't Start SCD, Ret = %d\012\000" )
.LC83:
	ASCII(.ascii	"SM_CfgBuf Err! ret =%d\012\000" )
.LC84:
	ASCII(.ascii	"***Print Scd[%d] State Reg\012\000" )
.LC85:
	ASCII(.ascii	"Scdover = %d \012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"ShortScdNum = %d \012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"ScdNum = %d \012\000" )
	.space	2
.LC88:
	ASCII(.ascii	"ScdRollAddr = %0x \012\000" )
.LC89:
	ASCII(.ascii	"SrcEaten = %d \012\000" )
.LC90:
	ASCII(.ascii	"********** SmID [%d] RawState begin **********\012\000" )
.LC91:
	ASCII(.ascii	"RawHead=%d\012\000" )
.LC92:
	ASCII(.ascii	"RawTail=%d\012\000" )
.LC93:
	ASCII(.ascii	"RawHistory=%d\012\000" )
	.space	1
.LC94:
	ASCII(.ascii	"RawFirstPacketOffset=%d\012\000" )
	.space	3
.LC95:
	ASCII(.ascii	"CurShowIndex=%d\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"********** SmID [%d] RawState end   **********\012\000" )
.LC97:
	ASCII(.ascii	"RawPhyAddr=0x%x\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"RawVirAddr=0x%x\012\000" )
	.space	3
.LC99:
	ASCII(.ascii	"RawLength=%d\012\000" )
	.space	2
.LC100:
	ASCII(.ascii	"RawPts=%ld\012\000" )
.LC101:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000" )
.LC102:
	ASCII(.ascii	"raw_pts: %lld\012\000" )
	.space	1
.LC103:
	ASCII(.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000" )
.LC104:
	ASCII(.ascii	"!!!push raw err!!!\012\000" )
.LC105:
	ASCII(.ascii	"Chan%d raw full\012\000" )
	.space	3
.LC106:
	ASCII(.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000" )
	.space	2
.LC107:
	ASCII(.ascii	"********** SmID [%d] SegState begin **********\012\000" )
.LC108:
	ASCII(.ascii	"SegHead=%d\012\000" )
.LC109:
	ASCII(.ascii	"SegTail=%d\012\000" )
.LC110:
	ASCII(.ascii	"SegCurrent=%d\012\000" )
	.space	1
.LC111:
	ASCII(.ascii	"SegBufPhyAddr=%p\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"SegBufVirAddr=%p\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"SegBufSize=%d\012\000" )
	.space	1
.LC114:
	ASCII(.ascii	"SegBufReadAddr=%p\012\000" )
	.space	1
.LC115:
	ASCII(.ascii	"SegBufWriteAddr=%pd\012\000" )
	.space	3
.LC116:
	ASCII(.ascii	"********** SmID [%d] SegState end   **********\012\000" )
.LC117:
	ASCII(.ascii	"SegPhyAddr=0x%x\012\000" )
	.space	3
.LC118:
	ASCII(.ascii	"SegVirAddr=0x%x\012\000" )
	.space	3
.LC119:
	ASCII(.ascii	"SegLength=%d\012\000" )
	.space	2
.LC120:
	ASCII(.ascii	"SegStreamID=%d\012\000" )
.LC121:
	ASCII(.ascii	"SegState=%d\012\000" )
	.space	3
.LC122:
	ASCII(.ascii	"SegIsLastSeg=%d\012\000" )
	.space	3
.LC123:
	ASCII(.ascii	"SegPts=%lld\012\000" )
	.space	3
.LC124:
	ASCII(.ascii	"%s,%d, active scd Success!\012\000" )
.LC125:
	ASCII(.ascii	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\012\000" )
.LC126:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000" )
	.space	2
.LC127:
	ASCII(.ascii	"%s,%d,find idle SCD(ID = %d)\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.space	4
	.type	s_ScdRegPhyBaseAddr, %object
	.size	s_ScdRegPhyBaseAddr, 4
s_ScdRegPhyBaseAddr:
	.space	4
	.type	s_SmIIS, %object
	.size	s_SmIIS, 256
s_SmIIS:
	.space	256
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 60
g_ScdDrvParam:
	.space	60
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.space	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 4
g_hex_base_vir_addr:
	.space	4
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.space	4
	.type	s_ScdRegResetPhyAddr, %object
	.size	s_ScdRegResetPhyAddr, 4
s_ScdRegResetPhyAddr:
	.space	4
	.type	last_rec_pos_time.54943, %object
	.size	last_rec_pos_time.54943, 128
last_rec_pos_time.54943:
	.space	128
	.type	LastRecPosTime.55137, %object
	.size	LastRecPosTime.55137, 128
LastRecPosTime.55137:
	.space	128
	.type	last_rec_pos_time.55171, %object
	.size	last_rec_pos_time.55171, 128
last_rec_pos_time.55171:
	.space	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.space	4
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
