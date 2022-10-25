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
	.type	GetFreeSegBufSize.part.5, %function
GetFreeSegBufSize.part.5:
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
	add	r0, r0, #327680
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
	.size	GetFreeSegBufSize.part.5, .-GetFreeSegBufSize.part.5
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
	ldr	r5, .L27
	ldr	r0, [r5]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L22
	cmp	r7, #1
	beq	.L23
	cmp	r7, #2
	beq	.L24
	mov	r0, r4
	ldr	r1, .L27+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L24:
	ldr	r6, .L27+8
	mov	r2, #17920
	ldr	r1, .L27+12
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r4
	ldr	r0, [r5, #4]
	bl	MEM_WritePhyWord
.L12:
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
	b	.L15
.L25:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L16
.L15:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r0, [r5, #4]
	add	r0, r0, #260
	bl	MEM_ReadPhyWord
	tst	r0, #1
	beq	.L25
	cmp	r4, #1000
	bcs	.L16
	ldr	r2, .L27+16
	mov	r0, #0
	ldr	r1, .L27+20
	bl	dprint_vfmw
.L18:
	cmp	r7, #1
	beq	.L26
	cmp	r7, #2
	ldreq	r3, .L27+24
	moveq	r2, #1
	streq	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L16:
	ldr	r2, .L27+16
	mov	r0, #0
	ldr	r1, .L27+28
	bl	dprint_vfmw
	b	.L18
.L23:
	ldr	r6, .L27+8
	mov	r2, #17920
	ldr	r1, .L27+32
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r7
	ldr	r0, [r5, #4]
	bl	MEM_WritePhyWord
	b	.L12
.L26:
	ldr	r3, .L27+24
	mov	r2, #2
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L22:
	ldr	r2, [r5]
	ldr	r1, .L27+36
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L28:
	.align	2
.L27:
	.word	.LANCHOR0
	.word	.LC3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+1552
	.word	.LANCHOR3
	.word	.LC5
	.word	g_DspDrvState
	.word	.LC4
	.word	.LANCHOR1
	.word	.LC2
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
	ldr	ip, .L39
	mov	r3, #0
	b	.L32
.L30:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L38
.L32:
	ldr	r2, [ip, r3, asl #3]
	cmp	r2, #0
	add	r1, r2, #72
	beq	.L30
	cmp	r0, r1
	bne	.L30
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L38:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L40:
	.align	2
.L39:
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
	ldr	r2, .L42
	mov	r3, r0, asl #6
	ldr	ip, .L42+4
	sub	r3, r3, r0, asl #2
	add	r3, r2, r3
	mov	r1, #0
	mov	r0, #1
	ldr	r2, [ip, #128]
	str	r1, [r3, #312]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r2
.L43:
	.align	2
.L42:
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
	ldr	r3, .L45
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #2
	mov	r1, #1
	add	r0, r3, r0
	str	r1, [r0, #312]
	ldmfd	sp, {fp, sp, pc}
.L46:
	.align	2
.L45:
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
	ldr	r5, .L68
	mov	r7, r0, asl #2
	mov	r4, r0
	mov	r1, #3
	add	r8, r5, r7
	ldr	r0, [r8, #4]
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	ldr	r0, [r8, #4]
	ldr	r8, .L68+4
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	cmp	r4, #0
	ldr	lr, [r8]
	mov	r9, r0
	bne	.L51
	ldr	r6, [lr, #120]
	ands	r2, r6, #1
	orrne	r6, r6, #32
	strne	r6, [lr, #120]
	beq	.L65
.L51:
	mov	r3, #0
	movw	r2, #10000
	b	.L53
.L56:
	add	r3, r3, #1
	cmp	r3, r2
	beq	.L66
.L53:
	cmp	r4, #0
	ldr	ip, [lr, #372]
	bne	.L56
	tst	ip, #2
	beq	.L56
	movw	r2, #9999
	cmp	r3, r2
	bhi	.L67
.L58:
	bfc	r6, #5, #1
	str	r6, [lr, #120]
.L57:
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
.L66:
	mov	r2, r4
	ldr	r1, .L68+8
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r4, #0
	bne	.L57
.L59:
	ldr	lr, [r8]
	b	.L58
.L65:
	ldr	r1, .L68+12
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L67:
	mov	r2, r4
	mov	r0, r4
	ldr	r1, .L68+8
	bl	dprint_vfmw
	b	.L59
.L69:
	.align	2
.L68:
	.word	.LANCHOR0
	.word	g_pstRegCrg
	.word	.LC7
	.word	.LC6
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
	ldr	r4, .L74
	ldr	r3, [r4, #308]
	cmp	r3, r0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L74+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L72
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Reset_Module
.L73:
	ldr	r3, .L74+8
	mov	r2, #0
	mov	r0, #1
	str	r2, [r4, #312]
	ldr	r3, [r3, #128]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L72:
	mov	r0, #0
	bl	ResetSCD
	b	.L73
.L75:
	.align	2
.L74:
	.word	.LANCHOR0
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
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
	ldr	r3, .L81
	ldr	r5, [r1, #4]
	add	r0, r3, r0, lsl #3
	ldr	r2, [r0, #8]
	cmp	r2, #0
	cmpne	r5, #0
	moveq	r5, #1
	movne	r5, #0
	beq	.L79
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
	beq	.L80
	ldr	ip, .L81+4
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
.L80:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L79:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L82:
	.align	2
.L81:
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
	bhi	.L86
	ldr	r3, .L88
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L86
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
.L86:
	mvn	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L89:
	.align	2
.L88:
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
	beq	.L92
	ldr	lr, .L93
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
.L92:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L94:
	.align	2
.L93:
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
	beq	.L103
	add	r5, r0, #98304
	ldr	r3, [r5]
	ldr	r2, [r5, #4]
	cmp	r3, r2
	beq	.L99
	ldr	r8, [r5, #12]
	str	r3, [r5, #16]
	mov	r7, r8, asr #31
	mov	r6, r8
	mov	r9, r8
.L98:
	ldr	ip, .L104
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
.L97:
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
.L99:
	mov	r9, #0
	str	r3, [r5, #16]
	mov	r8, r9
	mov	r6, #0
	mov	r7, #0
	b	.L97
.L103:
	mov	r5, #98304
	ldr	r3, [r5]
	ldr	r2, [r5, #4]
	cmp	r3, r2
	str	r3, [r5, #16]
	movne	r6, #0
	movne	r7, #0
	movne	r9, r0
	movne	r8, r0
	bne	.L98
	mov	r9, r0
	mov	r6, #0
	mov	r7, #0
	mov	r8, r0
	b	.L97
.L105:
	.align	2
.L104:
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
	beq	.L110
	add	r3, r0, #98304
	ldmia	r3, {r2, ip}
	cmp	r2, ip
	beq	.L109
	mov	ip, r2, asl #7
	ldr	lr, [r3, #12]
	sub	r2, ip, r2, asl #5
	add	r0, r0, r2
	add	r1, r1, lr
	ldr	r2, [r0, #8]
	cmp	r1, r2
	bge	.L110
	str	r1, [r3, #12]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L110:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L109:
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
	beq	.L113
	add	r3, r0, #98304
	ldr	ip, [r3]
	ldr	r0, [r3, #4]
	cmp	ip, r0
	beq	.L114
	ldr	r3, [r3, #12]
	mov	r0, r2
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L113:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L114:
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
	beq	.L131
	ldr	r0, .L143
	b	.L120
.L117:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L118
.L120:
	ldr	r3, [r0, r2, asl #3]
	mov	r6, r2, asl #3
	cmp	r3, #0
	add	r1, r3, #72
	beq	.L117
	cmp	r7, r1
	bne	.L117
	cmp	r2, #0
	blt	.L118
	add	r3, r7, #98304
	str	r3, [fp, #-48]
	mov	r2, r3
	ldr	r3, [r3]
	ldr	r2, [r2, #4]
	cmp	r3, r2
	addgt	r2, r2, #1024
	rsb	r2, r3, r2
	cmp	r2, r8
	bcc	.L142
	cmp	r8, #0
	mov	r5, r3
	beq	.L124
	ldr	r9, .L143+4
	mov	r10, #0
.L125:
	mov	r4, r5, asl #7
	ldr	r2, .L143+8
	sub	r4, r4, r5, asl #5
	ldr	r1, .L143+12
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
	bne	.L125
	ldr	r2, [fp, #-48]
	ldr	r3, [r2]
	add	ip, r10, r3
	str	ip, [r2]
	cmp	ip, #1024
	bge	.L129
.L130:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	str	r0, [r3, #12]
.L138:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L129:
	ldr	r3, [fp, #-48]
	sub	ip, ip, #1024
	str	ip, [r3]
	b	.L130
.L124:
	ldr	r2, [fp, #-48]
	cmp	r3, #1024
	str	r3, [r2]
	ldrge	r2, [fp, #-48]
	subge	r3, r3, #1024
	strge	r3, [r2]
.L128:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L131:
	mvn	r0, #0
	b	.L138
.L142:
	mov	r3, r8
	ldr	r1, .L143+16
	mov	r0, #26
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L138
.L118:
	movw	r2, #525
	ldr	r1, .L143+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L138
.L144:
	.align	2
.L143:
	.word	.LANCHOR0+8
	.word	.LANCHOR0
	.word	.LANCHOR3+20
	.word	.LC10
	.word	.LC9
	.word	.LC8
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
	bne	.L152
	add	r8, r0, #98304
	cmp	ip, #0
	ldr	r7, [r8]
	ldr	lr, [r8, #12]
	mov	ip, r7, asl #7
	sub	ip, ip, r7, asl #5
	add	ip, r0, ip
	ldr	r5, [ip, #8]
	rsb	r5, lr, r5
	bne	.L147
	ldr	r6, [r8, #4]
	subs	r6, r6, r7
	addmi	r6, r6, #1024
.L147:
	cmp	r1, r5
	add	r6, r7, r6
	mov	ip, r7
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r7
	orrls	lr, lr, #1
	cmp	lr, #0
	bne	.L148
	mov	r4, r7
.L149:
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
	beq	.L149
	cmp	r7, r4
	rsbne	r5, r9, r5
	rsbne	r5, r5, r1
	strne	r5, [r3]
	beq	.L148
.L151:
	ldr	r3, [fp, #4]
	mov	r0, #0
	str	ip, [r3]
	ldr	r3, [r8]
	rsb	r4, r3, r4
	str	r4, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L148:
	str	r1, [r3]
	mov	r4, r7
	b	.L151
.L152:
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
	bne	.L159
	cmp	r3, #0
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	bne	.L159
	add	r4, r0, #98304
	ldr	r3, [r4, #20]
	ldr	ip, [r4, #12]
	rsb	r3, ip, r3
	movs	r6, r3, asr #31
	bne	.L158
	cmp	r1, r3
	bgt	.L159
	sub	r2, fp, #40
	sub	r3, fp, #44
	str	r2, [sp]
	sub	r2, fp, #48
	bl	GetRawNumOffset
	ldr	lr, [r4]
	ldr	r7, [fp, #-48]
	movw	r2, #718
	ldr	r8, [fp, #-44]
	mov	r0, #26
	add	lr, r7, lr
	ldr	r1, .L161
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
	ldr	r1, [fp, #-48]
	mov	r0, r5
	bl	DeleteRawPacket
	ldr	r3, [r4]
	ldr	r1, [r4, #4]
	ldr	r2, [fp, #-44]
	cmp	r3, r1
	mvneq	r6, #2
	beq	.L158
	mov	r1, r3, asl #7
	ldr	r0, [r4, #12]
	sub	r3, r1, r3, asl #5
	add	r5, r5, r3
	add	r2, r2, r0
	ldr	r3, [r5, #8]
	cmp	r2, r3
	strlt	r2, [r4, #12]
	bge	.L159
.L158:
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L159:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L162:
	.align	2
.L161:
	.word	.LC11
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
	ldr	r3, .L167
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L166
	add	r4, r0, #425984
	ldr	r1, [r4, #152]
	cmp	r1, #0
	ldmlefd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #72
	bl	DeleteRawPacket
	mov	r3, #0
	str	r3, [r4, #152]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L166:
	movw	r2, #742
	ldr	r1, .L167+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L168:
	.align	2
.L167:
	.word	.LANCHOR0
	.word	.LC12
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
	beq	.L175
	add	r0, r0, #98304
	ldmia	r0, {r2, r3}
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1024
	strmi	r3, [r1]
	movpl	r0, #0
	movmi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L175:
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
	beq	.L179
	cmp	r3, #262144
	movcs	r4, #0
	movcc	r4, #1
	cmp	r2, #0
	orreq	r4, r4, #1
	cmp	r4, #0
	bne	.L179
	ldr	r3, .L180
	mov	r2, #56
	movt	r2, 5
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	ip, r8, #327680
	mov	r0, r4
	str	r5, [ip, #24]
	str	r7, [r8]
	str	r5, [ip, #32]
	str	r5, [ip, #36]
	str	r6, [ip, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L179:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L181:
	.align	2
.L180:
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
	ldr	r3, .L187
	mov	r2, #327680
	mov	r1, #0
	add	r0, r4, #8
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #327680
	mov	r3, #0
	ldr	r2, [r0, #24]
	str	r3, [r0, #8]
	str	r3, [r0, #12]
	str	r2, [r0, #32]
	str	r2, [r0, #36]
	str	r3, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L188:
	.align	2
.L187:
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
	add	r0, r0, #327680
	ldr	r3, [r0, #36]
	ldr	r2, [r0, #32]
	cmp	r3, r2
	bhi	.L193
	ldrcs	r0, [r0, #28]
	subcc	r0, r2, #1
	rsbcc	r0, r3, r0
	subcs	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L193:
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
	addne	r2, r0, #475136
	ldrne	r3, [r2, #960]
	addne	r3, r3, #1
	strne	r3, [r2, #960]
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
	bne	.L196
	add	r1, r1, #73
	uxtb	r1, r1
	cmp	r1, #3
	ldmhifd	sp, {fp, sp, pc}
.L196:
	add	r0, r0, #475136
	ldr	r3, [r0, #964]
	add	r3, r3, #1
	str	r3, [r0, #964]
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
	add	r0, r0, #475136
	ldr	r3, [r0, #968]
	cmp	r3, #2
	ldmlefd	sp, {fp, sp, pc}
	tst	r1, #31
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #980]
	ldr	r2, [r0, #976]
	rsb	r1, r2, r3
	cmp	r1, #1
	beq	.L212
.L203:
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r0, #972]
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
.L204:
	cmp	r3, #1
	cmpne	r3, #20
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #960]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, #960]
	ldr	r3, [r0, #964]
	add	r3, r3, #1
	str	r3, [r0, #964]
	ldmfd	sp, {fp, sp, pc}
.L212:
	ldr	r1, [r0, #972]
	rsb	r1, r1, r2
	cmp	r1, #1
	bne	.L203
	b	.L204
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
	ldr	r3, .L233
	mov	r6, r1
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #536]
	cmp	r3, #0
	cmpne	r3, #3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r4, #475136
	ldr	r3, [r5, #968]
	cmp	r3, #199
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r2, [r0]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #0
	movne	r7, r2
	bne	.L217
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L231
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r7, [r0, #3]	@ zero_extendqisi2
	andeq	r2, r7, #31
	beq	.L217
	mov	r2, r1
.L231:
	mov	r7, r2
.L217:
	ldr	lr, [r5, #976]
	add	r3, r3, #1
	ldr	ip, [r5, #980]
	mov	r1, r7
	str	r3, [r5, #968]
	mov	r0, r4
	str	lr, [r5, #972]
	str	ip, [r5, #976]
	str	r2, [r5, #980]
	bl	CheckData
	mov	r1, r7
	mov	r0, r4
	bl	CheckStartCodeCnt
	ldr	r3, [r5, #968]
	cmp	r3, #199
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #960]
	ldr	r3, [r5, #964]
	rsb	r1, r3, r2
	cmp	r1, #49
	ble	.L218
	ldr	r1, [r4, #536]
	cmp	r1, #3
	beq	.L232
.L218:
	rsb	r3, r2, r3
	cmp	r3, #49
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #536]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L233+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r6
	mov	r2, r3
	mov	r1, #124
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L232:
	ldr	r3, .L233+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #0
	mov	r1, #124
	mov	r2, r3
	mov	r0, r6
	blx	ip
	ldr	r3, [r5, #964]
	ldr	r2, [r5, #960]
	b	.L218
.L234:
	.align	2
.L233:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r6, r1
	beq	.L238
	add	r4, r0, #327680
	ldr	r3, [r4, #12]
	ldr	r1, [r4, #8]
	add	r3, r3, #1
	mov	ip, r3, asr #31
	mov	ip, ip, lsr #20
	add	r3, r3, ip
	ubfx	r3, r3, #0, #12
	rsb	r3, ip, r3
	cmp	r3, r1
	beq	.L239
	mov	r1, r2
	ldr	r0, [r6]
	bl	CheckStream
	ldr	r7, [r4, #12]
	ldr	r0, .L243
	mov	r2, #80
	mov	r1, r6
	mov	r3, r7, asl #6
	add	r7, r3, r7, lsl #4
	ldr	r3, [r0, #52]
	add	r0, r7, #8
	add	r7, r5, r7
	add	r0, r5, r0
	blx	r3
	ldr	r1, [r4, #12]
	mov	ip, #1
	add	r3, r1, ip
	mov	r0, r1, asl #6
	mov	r2, r3, asr #31
	add	r0, r0, r1, lsl #4
	add	r5, r5, r0
	mov	r2, r2, lsr #20
	add	r3, r3, r2
	strb	ip, [r5, #12]
	ubfx	r3, r3, #0, #12
	str	r1, [r7, #28]
	rsb	r3, r2, r3
	str	r3, [r4, #12]
	ldrsb	r3, [r6, #5]
	cmp	r3, #2
	beq	.L237
	ldr	r1, [r6, #12]
	ldr	r3, [r6, #16]
	ldr	r2, [r4, #40]
	add	r3, r3, r1
	str	r3, [r4, #36]
	ldr	r1, [r6, #16]
	ldr	r3, [r4, #44]
	add	r2, r2, r1
	str	r2, [r4, #40]
	ldr	r2, [r6, #16]
	add	r3, r3, r2
	str	r3, [r4, #44]
.L237:
	ldr	r3, [r4, #48]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #48]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L239:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L238:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L244:
	.align	2
.L243:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r0, r1
	beq	.L254
	add	r4, r5, #327680
	ldr	r3, [r4, #8]
	ldr	r1, [r4, #12]
	cmp	r1, r3
	beq	.L256
	mov	r6, r3, asl #4
	mov	r7, r3, asl #6
	add	r2, r6, r7
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	bne	.L249
	b	.L247
.L261:
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	beq	.L247
.L249:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #20
	add	r2, r2, r3
	ubfx	r2, r2, #0, #12
	rsb	r3, r3, r2
	cmp	r1, r3
	mov	r6, r3, asl #4
	mov	r7, r3, asl #6
	add	r2, r6, r7
	bne	.L261
.L256:
	mvn	r0, #2
.L246:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L247:
	add	r8, r6, r7
	add	r1, r8, #8
	adds	r1, r5, r1
	beq	.L256
	ldr	r3, .L262
	mov	r2, #80
	add	r6, r6, r7
	add	r6, r5, r6
	ldr	r3, [r3, #52]
	blx	r3
	add	r3, r5, r8
	mov	r0, #2
	ldrsb	r1, [r3, #13]
	strb	r0, [r3, #12]
	cmp	r1, r0
	ldr	r3, [r3, #24]
	ldr	r1, [r4, #44]
	mov	r0, #26
	ldr	r2, [r4, #48]
	rsbne	r1, r3, r1
	sub	r2, r2, #1
	bic	r1, r1, r1, asr #31
	str	r1, [r4, #44]
	bic	r2, r2, r2, asr #31
	str	r2, [r4, #48]
	ldrb	ip, [r6, #14]	@ zero_extendqisi2
	ldr	r2, [r6, #20]
	ldr	r1, .L262+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L254:
	mvn	r0, #0
	b	.L246
.L263:
	.align	2
.L262:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
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
	beq	.L287
	movw	r3, #61438
	sub	r2, r1, #4096
	movt	r3, 65535
	cmp	r2, r3
	bls	.L287
	cmn	r1, #1
	add	r6, r5, #327680
	beq	.L302
	ldr	r3, [r6, #8]
	ldr	r2, [r6, #12]
	cmp	r3, r2
	bne	.L298
	b	.L272
.L275:
	add	r3, r3, #1
	ubfx	r3, r3, #0, #12
	cmp	r3, r2
	beq	.L272
.L298:
	cmp	r4, r3
	bne	.L275
	mov	r2, r3, asl #6
	add	r3, r2, r3, lsl #4
	add	r2, r5, r3
	ldrsb	r2, [r2, #12]
	cmp	r2, #2
	addeq	r3, r3, #8
	addeq	r7, r5, r3
	beq	.L269
.L272:
	mvn	r0, #2
.L297:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L302:
	ldr	r9, [r6, #8]
	ldr	r3, [r6, #12]
	cmp	r9, r3
	beq	.L272
	mov	r3, r9, asl #6
	mov	r4, r9
	add	r9, r3, r9, lsl #4
	mov	r2, r4
	add	r7, r9, #8
	add	r9, r5, r9
	ldr	r1, .L304
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r9, #24]
	add	r7, r5, r7
	cmp	r3, #0
	movne	r8, #0
	beq	.L271
.L270:
	ldr	r3, [r9, #8]
	mov	r0, #0
	ldr	r1, .L304+4
	ldrb	r2, [r3, r8]	@ zero_extendqisi2
	add	r8, r8, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #24]
	cmp	r3, r8
	movhi	r3, #1
	movls	r3, #0
	cmp	r8, #15
	movhi	r3, #0
	cmp	r3, #0
	bne	.L270
.L271:
	ldr	r1, .L304+8
	mov	r0, #0
	bl	dprint_vfmw
.L269:
	cmp	r7, #0
	beq	.L272
	ldr	r3, [r7, #16]
	mov	r2, #0
	strb	r2, [r7, #4]
	mov	r0, #26
	ldr	r2, [r7, #12]
	str	r4, [sp, #4]
	ldrb	ip, [r7, #6]	@ zero_extendqisi2
	ldr	r1, .L304+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #8]
	cmp	r3, r4
	beq	.L282
.L277:
	ldrsb	r3, [r7, #5]
	cmp	r3, #2
	beq	.L301
.L283:
	ldr	r2, [r7, #16]
	ldr	r3, [r6, #40]
	rsb	r3, r2, r3
.L281:
	bic	r3, r3, r3, asr #31
	mov	r0, #0
	str	r3, [r6, #40]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L278:
	ldr	r2, [r6, #12]
	cmp	r2, r4
	beq	.L284
	ldrsb	r2, [r3, #12]
	cmp	r2, #0
	bne	.L303
.L288:
	add	r4, r4, #1
	ubfx	r4, r4, #0, #12
.L282:
	mov	r3, r4, asl #6
	cmp	r4, #4096
	add	r3, r3, r4, lsl #4
	add	r3, r5, r3
	bcc	.L278
	ldr	r2, .L304+16
	mov	r0, #1
	ldr	r1, .L304+20
	bl	dprint_vfmw
	ldr	r2, [r6, #12]
	cmp	r2, r4
	bne	.L288
.L284:
	ldr	r3, [r6, #36]
	str	r2, [r6, #8]
	str	r3, [r6, #32]
	ldrsb	r3, [r7, #5]
	cmp	r3, #2
	bne	.L283
.L301:
	ldr	r3, [r6, #40]
	b	.L281
.L303:
	str	r4, [r6, #8]
	ldrsb	r2, [r7, #5]
	cmp	r2, #2
	ldrne	r3, [r3, #20]
	strne	r3, [r6, #32]
	bne	.L277
	b	.L301
.L287:
	mvn	r0, #0
	b	.L297
.L305:
	.align	2
.L304:
	.word	.LC14
	.word	.LC16
	.word	.LC15
	.word	.LC17
	.word	.LANCHOR3+36
	.word	.LC18
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
	addne	r3, r0, #327680
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
	add	r0, r0, #327680
	ldr	r3, [r0, #12]
	ldr	r0, [r0, #8]
	rsb	r0, r0, r3
	ubfx	r0, r0, #0, #12
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
	addne	r0, r0, #327680
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
	ldr	r3, .L319
	mov	r2, r0, asl #2
	add	ip, r3, r2
	ldr	r1, [ip, #324]
	cmp	r1, #0
	bne	.L318
	rsb	r2, r2, r0, lsl #6
	add	r3, r3, r2
	ldr	r0, [r3, #312]
	cmp	r0, #0
	moveq	r3, #2
	movne	r3, #1
	movne	r0, r1
	str	r3, [ip, #324]
	ldmfd	sp, {fp, sp, pc}
.L318:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L320:
	.align	2
.L319:
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
	ldr	r3, .L322
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L323:
	.align	2
.L322:
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
	ldr	r3, .L329
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #324]
	cmp	r3, #2
	movne	r3, #2
	strne	r3, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L330:
	.align	2
.L329:
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
	ldr	r3, .L332
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #324]
	ldmfd	sp, {fp, sp, pc}
.L333:
	.align	2
.L332:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	2
	.global	ResetLastUnfinishedSegInfo
	.type	ResetLastUnfinishedSegInfo, %function
ResetLastUnfinishedSegInfo:
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
	ldr	r2, .L335
	add	r3, r0, #425984
	add	r0, r3, #428
	add	r6, r3, #436
	mov	ip, #0
	mvn	lr, #0
	ldr	r4, [r2, #48]
	mov	r5, #1
	str	lr, [r3, #432]
	mov	r1, ip
	strh	lr, [r0]	@ movhi
	mov	r2, #80
	str	lr, [r3, #440]
	add	r0, r3, #472
	strh	lr, [r6]	@ movhi
	str	r5, [r3, #448]
	str	ip, [r3, #452]
	str	ip, [r3, #456]
	str	ip, [r3, #460]
	str	ip, [r3, #464]
	str	ip, [r3, #444]
	mov	r3, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	bx	r3
.L336:
	.align	2
.L335:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetLastUnfinishedSegInfo, .-ResetLastUnfinishedSegInfo
	.align	2
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
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
	bhi	.L339
	ldr	r5, .L340
	movw	r2, #49704
	ldr	r6, .L340+4
	mov	r1, #0
	add	r5, r5, r0, lsl #3
	movt	r2, 6
	mov	r4, r1
	ldr	r3, [r6, #48]
	ldr	r0, [r5, #8]
	blx	r3
	ldr	r3, [r5, #8]
	mvn	ip, #0
	mov	lr, #1
	add	r3, r3, #425984
	mov	r1, r4
	add	r2, r3, #428
	add	r7, r3, #436
	str	ip, [r3, #432]
	add	r0, r3, #472
	strh	ip, [r2]	@ movhi
	mov	r2, #80
	str	ip, [r3, #440]
	ldr	r6, [r6, #48]
	strh	ip, [r7]	@ movhi
	str	lr, [r3, #448]
	str	r4, [r3, #452]
	str	r4, [r3, #456]
	str	r4, [r3, #460]
	str	r4, [r3, #464]
	str	r4, [r3, #444]
	blx	r6
	ldr	r3, [r5, #8]
	mov	r0, r4
	mvn	r5, #0
	add	r3, r3, #425984
	mvn	r4, #0
	strd	r4, [r3, #240]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L339:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L341:
	.align	2
.L340:
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
	ldr	r4, .L345
	ldr	r6, .L345+4
	add	r5, r4, #256
.L343:
	mov	r2, #8
	mov	r0, r4
	ldr	r3, [r6, #48]
	add	r4, r4, r2
	mov	r1, #0
	blx	r3
	cmp	r4, r5
	bne	.L343
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L346:
	.align	2
.L345:
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
	beq	.L349
	cmp	r8, #1
	bne	.L361
	movw	r3, #1366
	ldr	r2, .L363
	ldr	r1, .L363+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L349:
	ldr	r4, .L363+8
	mov	r3, #49152
	movt	r3, 63683
	ldr	r2, [r4, #304]
	str	r3, [r4, #4]
	cmp	r2, #1
	beq	.L354
	ldr	r3, .L363+12
	mov	r1, r8
	mov	r2, #60
	add	r0, r4, #264
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, .L363+16
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
	add	r5, r5, #45056
	add	r5, r5, #127
	add	r5, r5, r6
	bic	r5, r5, #127
	str	r0, [r4, #272]
	mov	r0, r3
	bl	MEM_Phy2Vir
	mov	r3, #32768
	str	r5, [r4]
	str	r3, [r4, #292]
	str	r0, [r4, #284]
	mov	r0, r5
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4, #328]
	beq	.L362
	add	r6, r6, #62976
	ldr	r2, [r4, #4]
	ldr	r3, [r4, #336]
	cmp	r7, r6
	mov	r1, #17920
	str	r1, [r4, #332]
	str	r2, [r4, #296]
	str	r3, [r4, #300]
	blt	.L354
	ldr	r3, [r4, #272]
	cmp	r3, #0
	beq	.L354
	ldr	r3, [r4, #284]
	cmp	r3, #0
	beq	.L354
	mov	r3, #1
	mov	r0, r8
	str	r3, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L361:
	ldr	r2, .L363
	mov	r0, #0
	ldr	r1, .L363+20
	bl	dprint_vfmw
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L354:
	mvn	r0, #6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L362:
	ldr	r2, .L363
	ldr	r1, .L363+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L364:
	.align	2
.L363:
	.word	.LANCHOR3+56
	.word	.LC20
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LC19
	.word	.LC21
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
	ldr	ip, .L375
	mov	r3, #0
	mov	lr, r3
.L367:
	ldr	r2, [ip, r3, asl #3]
	add	r3, r3, #1
	cmp	r2, #0
	add	r1, r2, #425984
	beq	.L366
	ldr	r2, [r1, #220]
	cmp	r2, #0
	beq	.L366
	ldr	r2, [r1, #208]
	cmp	r2, #0
	strle	lr, [r1, #220]
.L366:
	cmp	r3, #32
	bne	.L367
	ldr	r2, .L375+4
	mov	r1, r0, asl #6
	ldr	ip, .L375+8
	sub	r3, r1, r0, asl #2
	add	r1, r2, r1
	ldr	r0, .L375+12
	mov	r4, #0
	mov	r2, #60
	str	r4, [r1, #56]
	add	r0, r0, r3
	mov	r1, r4
	ldr	r3, [ip, #48]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L376:
	.align	2
.L375:
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
	bne	.L391
	ldr	r2, .L392
	add	r3, r2, r0, lsl #3
	ldr	ip, [r3, #8]
	cmn	r2, #264
	cmpne	ip, #0
	moveq	r8, #1
	movne	r8, #0
	beq	.L383
	ldr	r3, [r1, #44]
	add	r4, ip, #425984
	str	r3, [r4, #288]
	ldr	r3, [r1, #12]
	ldr	r1, [ip, #16]
	cmp	r1, r3
	addeq	r5, ip, #4
	ldreq	r9, .L392+4
	beq	.L382
	cmp	r3, #0
	beq	.L383
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L383
	ldr	r0, [r2, #288]
	mov	r3, #4096
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
	blt	.L383
	ldr	r9, .L392+4
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
.L382:
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
.L379:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L383:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L391:
	str	r1, [sp]
	mov	r3, r0
	movw	r2, #1459
	ldr	r1, .L392+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L379
.L393:
	.align	2
.L392:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC22
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
	bhi	.L402
	cmp	r1, #0
	bne	.L403
	ldr	r2, .L404
	add	r0, r2, r0, lsl #3
	ldr	r3, [r0, #8]
	cmn	r2, #264
	cmpne	r3, #0
	moveq	r1, #1
	movne	r1, #0
	beq	.L398
	add	r3, r3, #425984
	ldr	r0, [r3, #208]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, [r2, #276]
	mov	ip, #4096
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
.L398:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L402:
	mov	r3, r0
	movw	r2, #1539
	ldr	r1, .L404+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L403:
	mov	r3, r1
	movw	r2, #1546
	ldr	r1, .L404+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L405:
	.align	2
.L404:
	.word	.LANCHOR0
	.word	.LC23
	.word	.LC24
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
	ldr	r3, .L411
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L410
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L410
	add	r3, r3, #425984
	ldr	r0, [r3, #220]
	cmp	r0, #0
	bne	.L410
	mov	r2, #1
	str	r2, [r3, #220]
	ldmfd	sp, {fp, sp, pc}
.L410:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L412:
	.align	2
.L411:
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
	ldr	r3, .L420
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r0, #425984
	ldr	r0, [r3, #220]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #208]
	cmp	r2, #0
	movle	r0, #0
	strle	r0, [r3, #220]
	mvngt	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L421:
	.align	2
.L420:
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
	bhi	.L429
	ldr	r3, .L437
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L436
	add	r2, r0, #425984
	cmn	r0, #72
	add	r0, r0, #98304
	ldr	r3, [r2, #220]
	strb	r3, [r1]
	ldr	r3, [r2, #268]
	str	r3, [r1, #20]
	beq	.L425
	ldr	r3, [r0, #76]
	ldr	ip, [r0, #72]
	subs	r3, r3, ip
	addmi	r3, r3, #1024
	strmi	r3, [r1, #4]
	strpl	r3, [r1, #4]
.L427:
	ldr	r3, [r0, #92]
	str	r3, [r1, #12]
	ldr	ip, [r0, #84]
	rsb	r3, ip, r3
	str	r3, [r1, #12]
.L425:
	ldr	r3, [r2, #108]
	adds	r0, r0, #96
	ldr	ip, [r2, #104]
	movne	r0, #0
	rsb	r3, ip, r3
	ubfx	r3, r3, #0, #12
	str	r3, [r1, #8]
	ldrne	r3, [r2, #136]
	strne	r3, [r1, #16]
	ldmfd	sp, {fp, sp, pc}
.L436:
	cmp	r1, #0
	beq	.L429
	strb	r0, [r1]
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L429:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L438:
	.align	2
.L437:
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
	b	.L440
.L442:
	ldr	r4, [r1]
	add	r4, r4, #1
	str	r4, [r1]
	ldr	r4, [lr, #8]
	ldr	lr, [r2]
	add	lr, lr, r4
	str	lr, [r2]
	ldr	lr, [r6, #4]
	cmp	lr, r3
	beq	.L444
	ldr	lr, [r1]
	cmp	lr, #1024
	bhi	.L444
.L440:
	rsb	ip, ip, r5
	add	r3, r3, #1
	ubfx	r3, r3, #0, #10
	ldrb	r4, [r0, ip]	@ zero_extendqisi2
	mov	r5, r3, asl #7
	mov	ip, r3, asl #5
	cmp	r4, #0
	rsb	lr, ip, r5
	add	lr, r0, lr
	bne	.L442
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L444:
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
	beq	.L450
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	add	lr, r0, lr
	ldr	r4, [lr, #8]
	cmp	r4, #2
	bgt	.L451
	mov	lr, r4
	mov	r8, #3
	mov	r5, #0
	b	.L448
.L449:
	add	lr, r0, lr
	ldr	lr, [lr, #8]
	add	r4, r4, lr
	cmp	r4, #2
	bgt	.L453
.L448:
	add	ip, ip, #1
	add	r5, r5, #1
	ubfx	ip, ip, #0, #10
	cmp	r5, r10
	rsb	r8, lr, r8
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	bne	.L449
.L450:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L453:
	mov	r9, r8, asr #31
.L447:
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
.L451:
	mov	r8, #3
	mov	r9, #0
	mov	r5, #0
	b	.L447
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
	ldr	r3, .L493
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
	beq	.L473
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
	bne	.L473
	ldr	r10, [r8, #76]
	ldr	r3, [r8, #72]
	cmp	r10, r3
	beq	.L488
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
	b	.L457
.L459:
	add	r1, r1, #1
	ldr	ip, [ip, #80]
	cmp	r1, #1024
	add	r6, r6, ip
	movls	r2, #0
	movhi	r2, #1
	cmp	r3, r10
	orreq	r2, r2, #1
	cmp	r2, #0
	bne	.L488
.L457:
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
	bne	.L459
	cmp	r9, #0
	str	r1, [fp, #-56]
	addne	r2, r4, #425984
	bne	.L470
	ldr	r10, .L493+4
	mov	r2, #327680
	mov	r1, r9
	add	r0, r8, #104
	ldr	r3, [r10, #48]
	blx	r3
	add	r2, r4, #425984
	ldr	r3, [r2, #120]
	str	r9, [r2, #104]
	str	r9, [r2, #108]
	str	r9, [r2, #112]
	str	r3, [r2, #128]
	str	r3, [r2, #132]
.L470:
	ldr	r3, [r2, #124]
	cmp	r3, r6
	blt	.L491
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
	bne	.L462
.L465:
	str	r9, [r5, #12]
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
	str	r3, [r5, #16]
	ldrd	r2, [r7, #136]
	strd	r2, [r5, #24]
	ldrd	r2, [r7, #136]
	strd	r2, [r5, #32]
	ldrd	r2, [r7, #120]
	strb	r1, [r5, #6]
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
	beq	.L464
	cmp	r8, #0
	beq	.L488
	ldrd	r2, [fp, #-52]
	orrs	r3, r2, r3
	ldrne	r10, .L493+4
	movne	r7, #0
	bne	.L467
	b	.L488
.L468:
	cmp	r8, #0
	beq	.L488
	orrs	r3, r0, r1
	beq	.L488
.L467:
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
	ldr	r2, [r5, #16]
	cmp	ip, r7
	strb	r0, [r5, #7]
	add	r1, r2, r1
	str	r1, [r5, #16]
	ldrd	r0, [r3, #112]
	ldr	r3, [r3, #80]
	strd	r0, [fp, #-52]
	str	r3, [fp, #-64]
	bhi	.L468
	ldr	r0, [r5]
.L464:
	cmp	r0, #0
	beq	.L492
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
.L491:
	mov	r2, r6
	ldr	r1, .L493+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L488
	movw	r2, #1773
	ldr	r1, .L493+12
	mov	r0, #0
	bl	dprint_vfmw
.L488:
	mvn	r0, #3
.L485:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L462:
	sub	r2, fp, #60
	sub	r3, fp, #64
	str	r2, [sp]
	sub	r1, fp, #56
	sub	r2, fp, #52
	ldr	r0, [fp, #-76]
	bl	AdjustRawPacketVP6A
	cmp	r0, #0
	beq	.L465
	b	.L488
.L473:
	mvn	r0, #0
	b	.L485
.L492:
	movw	r3, #1834
	ldr	r2, .L493+16
	ldr	r1, .L493+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L485
.L494:
	.align	2
.L493:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	.word	.LC26
	.word	.LANCHOR3+72
	.word	.LC27
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
	beq	.L501
	sub	r3, r0, #2
	cmp	r3, #1
	bls	.L500
	cmp	r0, #18
	cmpne	r0, #6
	moveq	r3, #1
	movne	r3, #0
	beq	.L500
	cmp	r0, #1
	beq	.L502
.L497:
	subs	r0, r0, #15
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L500:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L502:
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L497
.L501:
	mov	r0, r3
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
	ldr	r5, .L511
	mov	r6, r0
	mov	r4, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrsb	r3, [r1, #5]
	cmp	r3, #2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, .L511+4
	mov	r0, #0
	ldr	r3, [r7, #16]
	blx	r3
	ldr	r3, [r7, #44]
	ldr	r2, [r5, r6, asl #2]
	ldr	r1, [r4, #16]
	ldr	r0, [r4]
	blx	r3
	ldr	r3, [r7, #12]
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L512:
	.align	2
.L511:
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
	ldr	r3, .L526
	mov	r7, r0
	mov	r6, r1
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #8]
	cmp	r4, #0
	cmpne	r1, #0
	beq	.L517
	add	r1, r4, #28
	ldr	r0, [r4, #12]
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L524
.L515:
	add	r0, r4, #98304
	mov	r1, r6
	add	r0, r0, #96
	add	r4, r4, #425984
	bl	SCDDRV_GetStreamSeg
	subs	r5, r0, #0
	beq	.L525
	ldr	r3, [r4, #268]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #268]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L524:
	mov	r1, r6
	mov	r0, r7
	bl	SM_CopyRawToSeg
	cmp	r0, #0
	beq	.L515
	add	r4, r4, #425984
	ldr	r1, .L526+4
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r3, [r4, #268]
	mvn	r0, #6
	add	r3, r3, #1
	str	r3, [r4, #268]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L525:
	mov	r0, r7
	mov	r1, r6
	str	r5, [r4, #268]
	bl	SCDDRV_SaveStreamSeg
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L517:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L527:
	.align	2
.L526:
	.word	.LANCHOR0
	.word	.LC28
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
	ldr	r3, .L530
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #8]
	cmp	r0, #0
	beq	.L529
	add	r0, r0, #98304
	add	r0, r0, #96
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseStreamSeg
.L529:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L531:
	.align	2
.L530:
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
	ldr	r3, .L533
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L534:
	.align	2
.L533:
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
	ldr	r3, .L540
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	cmp	r5, #0
	add	r3, r4, #425984
	mov	r1, r0
	bne	.L539
	ldr	r2, [r3, #236]
	cmp	r0, r2
	strls	r5, [r3, #232]
	rsbhi	r0, r2, r0
	strls	r1, [r3, #236]
	strhi	r0, [r3, #232]
	movls	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L539:
	mov	r2, #0
	str	r1, [r3, #236]
	mov	r0, r2
	str	r2, [r3, #232]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L541:
	.align	2
.L540:
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
	ldr	r3, .L545
	ldr	r2, [r3, #312]
	cmp	r2, #1
	ldreq	r3, [r3, #308]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L546:
	.align	2
.L545:
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
	b	GetFreeSegBufSize.part.5
	UNWIND(.fnend)
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.align	2
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
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
	ldr	r5, [fp, #4]
	cmp	r2, #0
	cmpne	r0, #0
	mov	r4, r3
	mov	r6, r1
	mov	r3, #0
	mov	r7, r2
	mov	r8, r0
	str	r3, [r5]
	bne	.L560
.L556:
	ldr	lr, [r7]
	add	r3, r6, #79
	add	r0, r8, #327680
	cmp	lr, r3
	movwcs	r3, #65457
	movcc	lr, #0
	movtcs	r3, 65535
	rsbcs	r3, r6, r3
	addcs	lr, r3, lr
	str	lr, [r7]
	ldr	ip, [r0, #28]
	rsb	ip, ip, ip, lsl #3
	add	r3, ip, #7
	cmp	ip, #0
	movlt	ip, r3
	cmp	r6, ip, asr #3
	addcs	lr, lr, r6
	strcs	lr, [r7]
	movcs	r3, #1
	strcs	r3, [r5]
	ldr	r2, [r0, #12]
	ldr	r3, [r0, #8]
	rsb	r2, r3, r2
	ubfx	r2, r2, #0, #12
	rsb	r2, r2, #4096
	str	r2, [r4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L560:
	mov	r1, r2
	bl	GetFreeSegBufSize.part.5
	b	.L556
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
	cmp	r0, #1024
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
	@ args = 12, pretend = 0, frame = 0
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
	mov	r4, r1
	beq	.L569
	add	lr, r0, #98304
	ldr	r0, [lr, #20]
	str	r0, [r3]
	ldr	r1, [lr, #12]
	rsb	r0, r1, r0
	str	r0, [r3]
	ldmia	lr, {r1, ip}
	rsb	ip, r1, ip
	cmp	ip, #0
	blt	.L566
	moveq	ip, #1
	movne	ip, #0
.L567:
	ldr	r3, [r3]
	cmp	r3, #3
	orrls	ip, ip, #1
	cmp	ip, #0
	bne	.L569
	ldr	r3, [fp, #12]
	mov	r1, r2
	mov	r0, r4
	str	r3, [sp]
	ldmib	fp, {r2, r3}
	bl	SCDDRV_GetSegStreamStatus
	ldr	r3, [fp, #8]
	ldr	r3, [r3]
	cmp	r3, #1024
	bls	.L570
	add	r4, r4, #327680
	ldr	r3, [fp, #4]
	ldr	r2, [r4, #28]
	ldr	r3, [r3]
	cmp	r3, r2, lsr #3
	mvnls	r0, #5
	movhi	r0, #0
.L565:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L566:
	cmn	ip, #1024
	movne	ip, #0
	moveq	ip, #1
	b	.L567
.L569:
	mvn	r0, #4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L570:
	mvn	r0, #5
	b	.L565
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
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #12]
	cmp	r2, #18
	beq	.L578
	sub	lr, r2, #6
	cmp	r2, #1
	cmpne	r2, #15
	clz	lr, lr
	moveq	r5, #1
	movne	r5, #0
	mov	lr, lr, lsr #5
	mov	r4, lr
.L573:
	add	r3, r0, #425984
	mov	ip, #1
	strb	ip, [r1, #2]
	ldr	ip, [r3, #176]
	str	ip, [r1, #4]
	ldr	ip, [r3, #168]
	str	ip, [r1, #8]
	ldr	ip, [r3, #184]
	str	ip, [r1, #16]
	ldr	r6, [r3, #192]
	ldr	ip, [r3, #276]
	mul	ip, ip, r6
	str	ip, [r1, #20]
	ldr	ip, [r3, #120]
	str	ip, [r1, #24]
	ldr	ip, [r3, #124]
	ldr	r6, [r3, #120]
	add	ip, ip, r6
	str	ip, [r1, #28]
	ldr	ip, [r3, #448]
	cmp	ip, #1
	ldreq	ip, [r3, #132]
	ldrne	ip, [r3, #444]
	addeq	ip, ip, #3
	biceq	ip, ip, #3
	cmp	r5, #0
	str	ip, [r1, #32]
	mov	ip, #1
	strb	ip, [r1]
	ldr	r0, [r0, #40]
	str	r4, [r1, #60]
	str	r0, [r1, #44]
	bne	.L579
	sub	r0, r2, #2
	cmp	r0, ip
	orrls	lr, lr, #1
	cmp	lr, #0
	strneb	ip, [r1, #1]
	beq	.L576
.L577:
	str	r2, [r1, #36]
	mov	r2, #1
	str	r2, [r1, #40]
	str	r2, [r1, #48]
	str	r2, [r1, #52]
	ldr	r3, [r3, #424]
	str	r3, [r1, #56]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L579:
	mov	r2, #0
.L576:
	mov	r0, #0
	strb	r0, [r1, #1]
	b	.L577
.L578:
	mov	r4, #1
	mov	r5, #0
	mov	lr, r4
	mov	r2, #6
	b	.L573
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
	add	r4, r0, #425984
	cmp	r1, r2
	str	r1, [r4, #248]
	movls	r3, #1
	str	r2, [r4, #252]
	movhi	r3, #0
	strb	r3, [r0, #2]
	mov	r1, #1
	ldr	r3, .L586
	mov	r2, #0
	str	r1, [r4, #212]
	strb	r2, [r0, #3]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r4, #272]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L587:
	.align	2
.L586:
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
	ldr	ip, .L595
	mov	r5, r0
	mov	r0, r3
	ldrb	ip, [ip]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L594
	cmp	r5, #4
	beq	.L593
	ldr	r6, .L595+4
	mov	r4, r2, asl #2
.L590:
	add	r2, r6, r4
	ldr	r0, [r2, #4]
	add	r0, r5, r0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L594:
	mov	r3, r1
	mov	r2, r5
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Record_RegData
.L593:
	ldr	r6, .L595+4
	mov	r4, r2, asl #2
	cmp	r1, #0
	add	r3, r6, r4
	ldr	r0, [r3, #4]
	add	r0, r0, #4
	bne	.L591
	bl	MEM_ReadPhyWord
	uxth	r1, r0
	b	.L590
.L591:
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
	b	.L590
.L596:
	.align	2
.L595:
	.word	g_HalDisable
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCD_ConfigReg, .-SCD_ConfigReg
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
	ldr	r5, .L656
	mov	r9, r0
	mov	r4, r1
	mov	r7, r2
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L598
	ldr	r3, .L656+4
	sub	r0, fp, #232
	mov	r2, #188
	mov	r1, #0
	mov	r8, r0
	ldr	r3, [r3, #48]
	blx	r3
.L599:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #4]
	cmp	r2, #1
	bne	.L636
	ldr	r6, .L656+8
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L601:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	bne	.L637
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L603:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	bne	.L638
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L605:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	bne	.L639
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
.L607:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	bne	.L640
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L609:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	bne	.L641
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L611:
	mov	r10, r9, asl #3
	ldr	r3, .L656+8
	add	r2, r6, r10
	ldr	r2, [r2, #8]
	add	r2, r2, #425984
	ldr	r1, [r2, #448]
	cmp	r1, #1
	beq	.L642
	ldr	r1, [r2, #432]
	mov	r0, #3
	movt	r0, 768
	cmp	r1, r0
	beq	.L643
.L617:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L644
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L622:
	add	r10, r6, r10
	ldrb	r1, [r5]	@ zero_extendqisi2
	ldr	r2, .L656+8
	ldr	r3, [r10, #8]
	cmp	r1, #1
	add	r3, r3, #425984
	add	r3, r3, #428
	ldrh	r1, [r3]
	bne	.L645
	add	r2, r2, r7, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L616:
	ldr	r2, [r4, #52]
	ldr	ip, [r4, #44]
	ldr	r0, [r4, #36]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	mov	r2, r2, asl #9
	orr	r2, r2, ip, asl #8
	ldr	r3, [r4, #48]
	ldrb	ip, [r5]	@ zero_extendqisi2
	and	r0, r0, #15
	orr	r0, r2, r0
	mov	r1, r1, asl #4
	cmp	ip, #1
	orr	r2, r0, r3, asl #13
	and	r1, r1, #16
	orr	r1, r2, r1
	bne	.L646
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #2080
	bl	MEM_WritePhyWord
	ldr	r3, [r4, #44]
	cmp	r3, #0
	bne	.L647
.L626:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L648
	add	r3, r6, r7, lsl #2
	mov	r1, #0
	ldr	r10, .L656
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r5, [r5]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L630
.L651:
	ldr	r2, [r4, #44]
	sub	r0, fp, #232
	mov	r3, #0
	str	r9, [fp, #-224]
	strb	r7, [fp, #-232]
	strb	r2, [fp, #-231]
	str	r3, [fp, #-228]
	bl	VDH_PostTask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L643:
	add	r2, r2, #428
	ldrh	r2, [r2]
	cmp	r2, #0
	bne	.L617
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L649
	add	r3, r3, r7, lsl #2
	mov	r1, #3
	ldr	r0, [r3, #4]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L619:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L650
	add	r3, r6, r7, lsl #2
	mov	r1, #0
	ldr	r0, [r3, #4]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L616
.L644:
	mov	r3, r1
	movw	r2, #2108
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L622
.L648:
	mov	r3, #0
	movw	r2, #2076
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldrb	r5, [r5]	@ zero_extendqisi2
	ldr	r10, .L656
	cmp	r5, #1
	bne	.L651
.L630:
	add	r6, r6, r7, lsl #2
	mov	r1, #0
	ldr	r0, [r6, #4]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	ldrb	r3, [r10]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #1
	and	r1, r1, #1
	bne	.L652
	ldr	r0, [r6, #4]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L646:
	mov	r3, r1
	mov	r2, #2080
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L626
.L647:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #60]
	cmp	r2, #1
	bne	.L653
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #4]
	bl	MEM_WritePhyWord
	b	.L626
.L641:
	mov	r3, r1
	movw	r2, #2072
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L611
.L640:
	mov	r3, r1
	movw	r2, #2068
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L609
.L639:
	mov	r3, r1
	mov	r2, #2064
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L607
.L638:
	mov	r3, r1
	movw	r2, #2060
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L605
.L637:
	mov	r3, r1
	movw	r2, #2056
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L603
.L636:
	mov	r3, r1
	movw	r2, #2052
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldr	r6, .L656+8
	b	.L601
.L645:
	mov	r3, r1
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L616
.L598:
	mov	r0, r2
	mov	r8, #0
	bl	ResetSCD
	b	.L599
.L653:
	mov	r3, r1
	mov	r2, #0
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L626
.L652:
	mov	r3, r1
	mov	r0, r8
	mov	r1, r5
	mov	r2, #2048
	bl	VDH_Record_RegData
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L642:
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L654
	add	r3, r3, r7, lsl #2
	mvn	r1, #0
	ldr	r0, [r3, #4]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L614:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L655
	add	r3, r6, r7, lsl #2
	mvn	r1, #0
	ldr	r0, [r3, #4]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L616
.L654:
	mvn	r3, #0
	movw	r2, #2108
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L614
.L655:
	mvn	r3, #0
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L616
.L649:
	mov	r3, #3
	movw	r2, #2108
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L619
.L650:
	mov	r3, #0
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L616
.L657:
	.align	2
.L656:
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	2
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #148)
	sub	sp, sp, #148
	mov	r0, r0, asl #3
	mov	r9, r1
	str	r1, [fp, #-152]
	mov	r4, r0
	mov	r7, r2
	str	r2, [fp, #-164]
	mov	r1, #0
	str	r0, [fp, #-176]
	mov	r2, #96
	sub	r0, fp, #140
	mov	r6, r3
	str	r3, [fp, #-160]
	bl	memset
	ldr	r3, .L716
	mov	r2, #16384
	mov	r1, #0
	mov	r8, #0
	add	r3, r3, r4
	ldr	r3, [r3, #8]
	mov	r0, r3
	str	r3, [fp, #-180]
	ldr	r3, .L716+4
	add	r0, r0, #425984
	str	r0, [fp, #-184]
	mov	r5, r0
	add	r0, r0, #552
	ldr	r3, [r3, #48]
	add	r4, r5, #440
	str	r0, [fp, #-148]
	blx	r3
	mov	r0, r6
	sub	r1, fp, #140
	bl	GetFirstRawPacket
	ldr	r3, [fp, #-132]
	ldr	r2, [fp, #4]
	add	r5, r5, #436
	cmp	r3, r7
	mov	r0, r3
	str	r8, [r2]
	str	r8, [r2, #4]
	str	r8, [r2, #8]
	str	r8, [r9, #4]
	bgt	.L659
	add	r9, r6, #98304
	str	r4, [fp, #-172]
	mov	r10, r8
	mov	ip, r3
	mov	r4, r3
	str	r8, [fp, #-144]
	str	r5, [fp, #-168]
.L662:
	ldr	r3, [fp, #4]
	mov	r1, r10, asl #2
	ldr	lr, [fp, #-144]
	cmp	ip, #0
	add	r6, r3, r1
	ldr	r3, [fp, #8]
	add	r1, r1, #12
	mov	r5, r8, asl #4
	add	r1, r1, r3
	ldr	r3, [fp, #-148]
	add	lr, lr, #1
	mov	r2, #96
	sub	r0, fp, #140
	add	r3, r3, r5
	str	lr, [fp, #-144]
	ble	.L660
	ldr	r7, [fp, #-136]
	add	r8, r8, #1
	sub	lr, r7, #1
	str	lr, [fp, #-156]
	ldr	lr, [fp, #4]
	str	r7, [lr, r10, asl #2]
	add	r10, r10, #3
	ldr	lr, [fp, #-156]
	str	r1, [r6, #8]
	add	lr, lr, ip
	ldr	r1, [fp, #-148]
	str	lr, [r6, #4]
	ldrd	r6, [fp, #-100]
	strd	r6, [r1, r5]
	ldrd	r6, [fp, #-100]
	ldr	r1, [fp, #-132]
	subs	r6, r6, #1
	sbc	r7, r7, #0
	adds	r6, r6, r1
	adc	r7, r7, r1, asr #31
	strd	r6, [r3, #8]
	mov	r3, #0
	str	r3, [fp, #-132]
.L660:
	ldr	r3, [fp, #-152]
	str	r4, [r3, #4]
	ldr	r1, [r9, #16]
	ldr	ip, [r9, #4]
	mov	r3, r1, asl #7
	cmp	r1, ip
	sub	r1, r3, r1, asl #5
	ldr	r3, [fp, #-160]
	add	r1, r3, r1
	bne	.L713
.L661:
	ldr	r3, [fp, #12]
	mov	r0, r4
	ldr	r5, [fp, #-168]
	cmp	r3, #0
	ldr	r4, [fp, #-172]
	bne	.L663
	ldr	r2, [fp, #-132]
	cmp	r2, #0
	bne	.L681
.L663:
	ldr	r3, [fp, #-144]
	cmp	r3, #0
	beq	.L680
	cmp	r10, #0
	subgt	r3, r10, #-1073741823
	ldrgt	r1, [fp, #4]
	movgt	r2, #0
	strgt	r2, [r1, r3, asl #2]
	ldr	r2, [fp, #-176]
	ldr	r3, .L716
	add	r3, r3, r2
	ldr	r2, [fp, #-152]
	ldr	r3, [r3, #8]
	ldr	r2, [r2, #4]
	add	r3, r3, #425984
	add	r0, r3, #436
	cmp	r2, #6
	ldr	ip, [r3, #440]
	add	r1, r3, #428
	movge	r2, #6
	cmp	r2, #5
	str	ip, [r3, #432]
	ldrh	r3, [r0]
	strh	r3, [r1]	@ movhi
	bls	.L714
.L683:
	mov	r7, #2
	mov	r2, #4
.L667:
	cmp	r8, #0
	ldrgt	r3, [fp, #-148]
	addgt	r9, r3, r8, lsl #4
	ble	.L676
.L679:
	ldr	r0, [r9, #-8]
	ldr	ip, [r9, #-16]
	add	r3, r0, #1
	rsb	ip, ip, r3
	cmp	ip, r2
	movcc	lr, ip
	movcs	lr, r2
	cmp	r2, #0
	beq	.L672
	cmp	lr, #0
	beq	.L675
	add	r6, r4, lr
.L674:
	ldrb	r1, [r3, #-1]!	@ zero_extendqisi2
	strb	r1, [r4], #1
	cmp	r4, r6
	bne	.L674
	subs	r2, r2, lr
	beq	.L672
.L675:
	subs	r8, r8, #1
	sub	r9, r9, #16
	bne	.L679
.L676:
	ldr	r2, [fp, #-152]
	mov	r0, #0
	ldr	r1, [fp, #-144]
	mov	r3, #1
	str	r3, [r2, #8]
	str	r1, [r2]
.L711:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L672:
	cmp	r7, #0
	beq	.L676
	rsb	ip, lr, ip
	rsb	r3, lr, r0
	cmp	ip, r7
	movcs	ip, r7
	cmp	ip, #0
	beq	.L677
	add	r3, r3, #1
	add	r1, r5, ip
.L678:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	strb	r2, [r5], #1
	cmp	r5, r1
	bne	.L678
	subs	r7, r7, ip
	beq	.L676
	mov	r2, #0
	b	.L675
.L713:
	ldr	r3, .L716+4
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r9, #16]
	ldr	ip, [fp, #-132]
	ldr	r1, [fp, #-164]
	add	r3, r3, #1
	add	r4, r4, ip
	ldr	r0, [fp, #-144]
	cmp	r1, r4
	mov	r2, r3, asr #31
	movge	r1, #1
	movlt	r1, #0
	cmp	r0, #1024
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	movge	r1, #0
	cmp	r1, #0
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r9, #16]
	bne	.L662
	b	.L661
.L714:
	cmp	r2, #1
	beq	.L715
	rsbs	r0, r2, #6
	rsb	lr, r2, #5
	beq	.L683
	ldr	r3, [fp, #-180]
	movw	ip, #33206
	add	lr, r4, lr
	movt	ip, 6
	add	ip, r3, ip
	mov	r3, #2
.L669:
	subs	r0, r0, #1
	rsb	r6, r3, #3
	sub	r7, r3, #1
	ldrb	r1, [lr], #-1	@ zero_extendqisi2
	movne	r3, #1
	moveq	r3, #0
	cmp	r6, #1
	movhi	r3, #0
	andls	r3, r3, #1
	cmp	r3, #0
	strb	r1, [ip, #-1]!
	mov	r3, r7
	bne	.L669
	cmp	r7, #0
	bne	.L712
	cmp	r0, #0
	rsb	r2, r2, #3
	beq	.L685
	ldr	r3, [fp, #-184]
	rsb	ip, r0, r2
	add	ip, r4, ip
	add	r1, r3, #444
	add	r3, r4, r2
.L670:
	ldrb	r2, [r3], #-1	@ zero_extendqisi2
	cmp	r3, ip
	strb	r2, [r1, #-1]!
	bne	.L670
	rsb	r2, r0, #4
	b	.L667
.L659:
	ldr	r3, [fp, #12]
	cmp	r3, #0
	bne	.L680
	cmp	r0, #0
	beq	.L680
	ldr	r8, [fp, #12]
	mov	r2, r0
	mov	r10, r8
	str	r8, [fp, #-144]
.L681:
	ldr	r3, [fp, #-152]
	ldr	r1, [fp, #-164]
	ldr	r3, [r3, #4]
	sub	r1, r1, #16
	cmp	r3, r1
	bge	.L663
	ldr	r1, [fp, #-164]
	ldr	ip, [fp, #-144]
	cmp	r1, r0
	cmplt	ip, #1024
	bge	.L663
	rsb	r3, r3, r1
	cmp	r3, r2
	bgt	.L663
	ldr	r2, [fp, #-136]
	mov	r1, r10, asl #2
	ldr	r0, [fp, #4]
	add	ip, r1, #12
	ldr	lr, [fp, #4]
	add	r1, r0, r1
	ldr	r0, [fp, #8]
	str	r3, [fp, #-132]
	str	r2, [lr, r10, asl #2]
	sub	r2, r2, #1
	add	r3, r2, r3
	ldrd	r6, [fp, #-100]
	str	r3, [r1, #4]
	add	ip, ip, r0
	ldr	r3, [fp, #-148]
	mov	r0, r8, asl #4
	str	ip, [r1, #8]
	add	r10, r10, #3
	add	ip, r3, r0
	mov	r1, #0
	strd	r6, [r3, r0]
	add	r8, r8, #1
	ldr	r3, [fp, #-144]
	ldr	r0, [fp, #-132]
	add	r3, r3, #1
	str	r3, [fp, #-144]
	ldrd	r2, [fp, #-100]
	subs	r2, r2, #1
	sbc	r3, r3, #0
	adds	r2, r2, r0
	adc	r3, r3, r0, asr #31
	ldr	r0, [fp, #-152]
	strd	r2, [ip, #8]
	ldr	r2, [fp, #-132]
	ldr	r3, [r0, #4]
	str	r1, [fp, #-132]
	add	r3, r3, r2
	mov	r2, r0
	str	r3, [r0, #4]
	b	.L663
.L677:
	mov	r2, ip
	b	.L675
.L685:
.L712:
	mov	r2, #4
	b	.L667
.L715:
	ldr	r6, [fp, #-184]
	mov	r7, #0
	ldrb	ip, [r6, #436]	@ zero_extendqisi2
	ldrb	lr, [r6, #443]	@ zero_extendqisi2
	ldrb	r0, [r6, #442]	@ zero_extendqisi2
	ldrb	r1, [r6, #441]	@ zero_extendqisi2
	ldrb	r3, [r6, #440]	@ zero_extendqisi2
	strb	ip, [r6, #437]
	strb	lr, [r6, #436]
	strb	r0, [r6, #443]
	strb	r1, [r6, #442]
	strb	r3, [r6, #441]
	b	.L667
.L680:
	mvn	r0, #5
	b	.L711
.L717:
	.align	2
.L716:
	.word	.LANCHOR0
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
	add	r4, r1, #425984
	str	r3, [fp, #-52]
	mov	r7, r0
	ldr	r3, [r4, #168]
	mov	r8, r2
	ldr	r0, [r4, #204]
	add	r5, r1, #72
	ldr	r9, [r4, #176]
	add	r6, r4, #152
	str	r3, [fp, #-48]
	bl	VCTRL_IfEsBufEnable
	cmp	r0, #0
	beq	.L722
	ldr	r10, .L723
	mov	r2, #12
	mov	r1, #0
	mov	r0, r6
	ldr	r3, [r10, #48]
	blx	r3
	ldr	lr, [r7, #44]
	ldr	r1, [fp, #-48]
	mov	r3, r5
	ldr	r0, [r4, #204]
	mov	r2, r8
	str	r9, [sp, #4]
	str	r1, [sp]
	mov	r1, r6
	str	lr, [sp, #8]
	bl	WriteScdMsg
	subs	r5, r0, #0
	movne	r0, r5
	bne	.L720
	ldr	r3, [r10]
	blx	r3
	ldr	ip, [fp, #-52]
	ldr	r3, .L723+4
	mov	r1, r7
	add	r10, r3, ip, lsl #6
	mov	r2, ip
	str	r0, [r10, #48]
	ldr	r0, [r4, #204]
	bl	WriteScdVtrlReg
	mov	r0, r5
.L720:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L722:
	ldr	r2, [r4, #204]
	mov	r0, #1
	ldr	r1, .L723+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L720
.L724:
	.align	2
.L723:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LC29
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	add	r4, r0, #425984
	mov	r7, r1
	add	r1, r0, #98304
	ldr	r2, [r4, #456]
	sub	ip, fp, #104
	sub	r3, fp, #112
	mov	r6, r0
	stmib	sp, {r3, ip}
	add	r1, r1, #96
	sub	ip, fp, #108
	add	r0, r0, #72
	str	ip, [sp]
	sub	r3, fp, #116
	mov	ip, #0
	str	ip, [fp, #-116]
	str	ip, [fp, #-112]
	str	ip, [fp, #-108]
	str	ip, [fp, #-104]
	bl	SCDDRV_CheckConditionOfStartSCD
	subs	r5, r0, #0
	bne	.L736
	ldr	r3, [fp, #-104]
	cmp	r3, #0
	bne	.L737
.L728:
	mov	r1, r7
	ldr	r0, [r4, #204]
	bl	SM_CfgBuf
	subs	r5, r0, #0
	bne	.L738
	ldr	r2, [fp, #-112]
	mov	r0, r6
	ldr	r3, [r4, #276]
	sub	r1, fp, #100
	str	r2, [r4, #192]
	mul	r2, r3, r2
	mov	r2, r2, asl #2
	str	r2, [r4, #188]
	bl	SCDDRV_SetCtrlReg
	mov	r3, r7
	sub	r0, fp, #100
	ldr	r2, [fp, #-108]
	mov	r1, r6
	bl	SCDDRV_StartSCD
	cmp	r0, #0
	movne	r5, r0
	bne	.L727
	ldr	r3, [fp, #-108]
	mov	r5, #0
	ldr	r2, [fp, #-116]
	cmp	r2, r3
	str	r3, [r4, #252]
	str	r2, [r4, #248]
	mov	r2, #1
	movls	r3, #1
	strlsb	r3, [r6, #2]
	ldr	r3, .L739
	strhib	r0, [r6, #2]
	str	r2, [r4, #212]
	strb	r5, [r6, #3]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r4, #272]
.L727:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L738:
	mov	r2, r5
	ldr	r1, .L739+4
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L737:
	ldr	r0, .L739
	add	r2, r4, #428
	add	ip, r4, #436
	mvn	r3, #0
	mov	lr, #1
	str	r3, [r4, #432]
	ldr	r8, [r0, #48]
	mov	r1, r5
	strh	r3, [r2]	@ movhi
	add	r0, r4, #472
	str	r3, [r4, #440]
	mov	r2, #80
	strh	r3, [ip]	@ movhi
	str	r5, [r4, #452]
	str	r5, [r4, #456]
	str	r5, [r4, #460]
	str	r5, [r4, #464]
	str	r5, [r4, #444]
	str	lr, [r4, #448]
	blx	r8
	b	.L728
.L736:
	mov	r2, r5
	ldr	r1, .L739+8
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L740:
	.align	2
.L739:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	UNWIND(.fnend)
	.size	CutStreamWithSCD, .-CutStreamWithSCD
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
	ldr	r4, .L742
	mov	r5, r0
	movw	r6, #2124
	add	r4, r4, r1, lsl #2
	ldr	r0, [r4, #4]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	and	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r4, #4]
	add	r0, r6, r0
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #4]
	mov	r3, r0, lsr #22
	add	r0, r6, r2
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
	ldr	r3, [r4, #4]
	str	r0, [r5, #24]
	add	r0, r3, #2128
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	str	r0, [r5, #28]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L743:
	.align	2
.L742:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	ReadScdStateReg, .-ReadScdStateReg
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
	ldr	r3, [r2, #4]
	ldrb	r0, [r1]	@ zero_extendqisi2
	mov	r3, r3, lsr #30
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
	beq	.L753
	ldr	r3, [r0, #12]
	cmp	r3, #0
	beq	.L755
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L755
	add	r1, r1, #327680
	ldr	r2, [r1, #36]
	ldr	r3, [r1, #32]
	cmp	r2, r3
	bhi	.L757
	ldrcs	r3, [r1, #28]
	subcc	r3, r3, #1
	rsbcc	r3, r2, r3
	subcs	r3, r3, #1
.L751:
	ldr	r2, [r0, #16]
	cmp	r2, r3
	mvnhi	r0, #6
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L757:
	ldr	r1, [r1, #28]
	sub	r3, r3, #1
	add	r3, r3, r1
	rsb	r3, r2, r3
	b	.L751
.L755:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L753:
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
	beq	.L761
	strd	r6, [r5]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L761:
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
	beq	.L767
	cmp	r0, #2
	movne	r0, #0
	beq	.L768
.L764:
	mov	r2, #0
	movt	r2, 65025
	cmp	r1, r2
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L767:
	mov	r3, #0
	movt	r3, 46593
	rsb	r0, r3, r1
	clz	r0, r0
	mov	r0, r0, lsr #5
	b	.L764
.L768:
	ubfx	r3, r1, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L764
	UNWIND(.fnend)
	.size	IsVopHeader, .-IsVopHeader
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
	add	r10, r0, #425984
	sub	r3, r2, #1
	cmp	r3, #0
	add	r0, r0, #98304
	ldr	lr, [r10, #108]
	mov	ip, r3
	ldr	r8, [r10, #104]
	rsb	r8, r8, lr
	ubfx	r8, r8, #0, #12
	rsb	r8, r8, #4096
	blt	.L777
	ldr	r5, [r10, #276]
	mov	r4, #0
	mov	r9, r4
	ldr	r7, [r0, #96]
	ldr	r6, [r10, #120]
	movt	r4, 65025
	mov	r5, r5, asl #2
	ldr	lr, [r10, #224]
	movt	r9, 46593
	mla	r1, r5, r3, r1
	b	.L776
.L780:
	cmp	lr, #2
	beq	.L779
	cmp	r2, r4
	beq	.L774
.L775:
	sub	ip, ip, #1
	rsb	r1, r5, r1
	cmn	ip, #1
	mov	r2, r3
	beq	.L777
	sub	r3, r3, #1
.L776:
	ldr	r2, [r1]
	cmp	lr, #1
	rsb	r2, r6, r2
	ldr	r2, [r7, r2]
	rsbeq	r0, r9, r2
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	bne	.L780
.L772:
	cmp	r2, r4
	beq	.L774
	cmp	r0, #1
	bne	.L775
.L774:
	cmp	r8, r3
	mov	r2, r3
	bcs	.L777
	sub	r3, r3, #1
	b	.L775
.L779:
	ubfx	r0, r2, #16, #8
	sub	r0, r0, #128
	cmp	r0, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L772
.L777:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetNextVop, .-GetNextVop
	.align	2
	.global	CorrectRollPhyAddr
	.type	CorrectRollPhyAddr, %function
CorrectRollPhyAddr:
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
	cmp	r1, r2
	rsbcc	r1, r2, r1
	addcc	r0, r1, r0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectRollPhyAddr, .-CorrectRollPhyAddr
	.align	2
	.global	CorrectSegNextAddr
	.type	CorrectSegNextAddr, %function
CorrectSegNextAddr:
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
	cmp	r0, r1
	movcc	r0, r1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectSegNextAddr, .-CorrectSegNextAddr
	.align	2
	.global	SetLastUnfinishedSegInfo
	.type	SetLastUnfinishedSegInfo, %function
SetLastUnfinishedSegInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 88
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
	add	r4, r0, #425984
	mov	r5, r0
	mov	r9, r1
	ldr	r8, [r4, #276]
	mov	r7, r2
	mov	r1, #0
	mov	r2, #80
	sub	r0, fp, #124
	ldr	r6, [r4, #180]
	bl	memset
	mul	ip, r8, r9
	add	r10, r5, #98304
	add	r8, r4, #472
	add	r1, r10, #96
	str	r1, [fp, #-128]
	add	r2, r4, #240
	add	ip, ip, #1
	add	r0, r5, #72
	mov	r3, r8
	ldr	r1, [r6, ip, asl #2]
	mov	r9, ip, asl #2
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r3, .L798
	mov	r2, #80
	mov	r1, r8
	sub	r0, fp, #124
	ldr	r3, [r3, #52]
	blx	r3
	add	ip, r6, r9
	ldr	r2, [r4, #120]
	ldr	ip, [ip, #-4]
	str	ip, [r4, #452]
	ldr	r3, [r7, #28]
	cmp	r2, r3
	movcs	r3, r2
	cmp	ip, r3
	str	r3, [r4, #444]
	bls	.L786
	mov	r1, #1
	str	r1, [r4, #460]
	ldr	r0, [r7, #28]
	rsb	r6, r2, r3
	ldr	r1, [r7, #16]
	cmp	r2, r0
	addhi	r1, r0, r1
	rsbhi	r1, r2, r1
	str	r1, [r4, #464]
	rsb	lr, ip, r1
	add	r1, lr, r6
	str	r1, [r4, #456]
	ldr	r5, [r5, #44]
	cmp	r5, #1
	beq	.L797
.L789:
	mov	r3, #0
	str	r3, [r4, #448]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L786:
	rsb	r3, ip, r3
	mov	r1, #0
	cmp	r3, #3
	str	r1, [r4, #460]
	str	r1, [r4, #464]
	str	r3, [r4, #456]
	movls	r1, #0
	ldr	r0, [r5, #44]
	movhi	r1, #1
	cmp	r0, #1
	movne	r1, #0
	cmp	r1, #0
	beq	.L789
	ldr	r5, [r10, #96]
	rsb	lr, r2, ip
	sub	r1, fp, #124
	ldr	r0, [fp, #-128]
	ldr	r2, [r4, #204]
	add	lr, r5, lr
	str	ip, [fp, #-112]
	mov	r5, #1
	mov	ip, #2
	str	lr, [fp, #-124]
	str	r3, [fp, #-108]
	strb	r5, [fp, #-118]
	strb	ip, [fp, #-119]
	bl	InsertStreamSeg
	b	.L789
.L797:
	ldr	r3, [r4, #108]
	ldr	r0, [r4, #104]
	rsb	r3, r0, r3
	ubfx	r3, r3, #0, #12
	rsb	r3, r3, #4096
	cmp	r1, #3
	cmphi	r3, #3
	bls	.L789
	ldr	r8, [fp, #-128]
	rsb	r7, r2, ip
	ldr	r3, [r10, #96]
	sub	r1, fp, #124
	ldr	r2, [r4, #204]
	mov	r0, r8
	add	r3, r3, r7
	str	ip, [fp, #-112]
	mov	r7, #2
	mov	ip, #0
	str	r3, [fp, #-124]
	strb	ip, [fp, #-118]
	str	lr, [fp, #-108]
	strb	r7, [fp, #-119]
	bl	InsertStreamSeg
	ldr	ip, [r10, #96]
	sub	r1, fp, #124
	ldr	r3, [r4, #120]
	mov	r0, r8
	ldr	r2, [r4, #204]
	strb	r7, [fp, #-119]
	str	ip, [fp, #-124]
	str	r6, [fp, #-108]
	strb	r5, [fp, #-118]
	str	r3, [fp, #-112]
	bl	InsertStreamSeg
	b	.L789
.L799:
	.align	2
.L798:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SetLastUnfinishedSegInfo, .-SetLastUnfinishedSegInfo
	.align	2
	.global	ProcessSegRoll
	.type	ProcessSegRoll, %function
ProcessSegRoll:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r5, r0, #425984
	mov	r4, r1
	add	r6, r0, #98304
	ldr	r1, [r5, #180]
	add	r9, r6, #96
	ldr	ip, [r5, #452]
	ldr	lr, [r5, #104]
	ldr	r7, [r1]
	rsb	r2, ip, r2
	ldr	r1, [r5, #108]
	ldr	r8, [r5, #120]
	str	ip, [r4, #12]
	rsb	r1, lr, r1
	ldr	r10, [r5, #120]
	rsb	r7, r8, r7
	ldr	lr, [r6, #96]
	add	r0, r2, r7
	rsb	ip, r10, ip
	cmp	r0, #3
	add	ip, lr, ip
	str	ip, [r4]
	ldrsb	ip, [fp, #4]
	ubfx	r1, r1, #0, #12
	rsb	r1, r1, #4096
	str	r0, [r4, #16]
	str	ip, [fp, #-56]
	bls	.L806
	cmp	r1, #2
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	bls	.L805
	mov	r1, r9
	mov	r0, r4
	bl	CheckSegValid
	subs	r10, r0, #0
	bne	.L805
	ldr	r2, [fp, #-48]
	cmp	r7, #0
	ldr	r3, [fp, #-52]
	str	r2, [r4, #16]
	beq	.L807
	strb	r3, [r4, #5]
	mov	r1, r4
	strb	r10, [r4, #6]
	mov	r0, r9
	ldr	r2, [r5, #204]
	bl	InsertStreamSeg
	str	r8, [r4, #12]
	ldr	r1, [r5, #120]
	mov	r2, #1
	ldr	r3, [r6, #96]
	mov	r0, r9
	rsb	r8, r1, r8
	str	r7, [r4, #16]
	add	r8, r3, r8
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	str	r8, [r4]
	mov	r1, r4
	strb	r2, [r4, #6]
	strb	r3, [r4, #5]
	ldr	r2, [r5, #204]
	bl	InsertStreamSeg
.L802:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L807:
	strb	r3, [r4, #5]
	mov	r0, r9
	mov	r3, #1
	mov	r1, r4
	strb	r3, [r4, #6]
	ldr	r2, [r5, #204]
	bl	InsertStreamSeg
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L806:
	mov	r3, r0
	movw	r2, #2842
	ldr	r1, .L808
	mov	r0, #0
	bl	dprint_vfmw
	mov	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L805:
	mvn	r10, #3
	b	.L802
.L809:
	.align	2
.L808:
	.word	.LC32
	UNWIND(.fnend)
	.size	ProcessSegRoll, .-ProcessSegRoll
	.align	2
	.global	ProcessLastUnfinishedSeg
	.type	ProcessLastUnfinishedSeg, %function
ProcessLastUnfinishedSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	add	r4, r0, #425984
	mov	r6, r2
	mov	r8, r1
	mov	r5, r0
	mov	r2, #80
	sub	r0, fp, #116
	mov	r1, #0
	bl	memset
	ldr	r3, [r6, #28]
	ldr	r0, [r4, #120]
	ldr	r7, [r6, #16]
	cmp	r0, r3
	addhi	r3, r3, r7
	rsbhi	r7, r0, r3
	cmp	r8, #0
	bne	.L812
	ldr	r3, [r4, #248]
	ldr	r2, [r4, #252]
	cmp	r3, r2
	movle	r3, #0
	movgt	r3, #1
	strb	r3, [r5]
	ldr	r2, [r4, #452]
	cmp	r2, #0
	ldreq	r1, [r4, #156]
	beq	.L814
	ldr	ip, [r4, #460]
	ldr	r3, [r4, #456]
	ldr	r1, [r4, #156]
	cmp	ip, #0
	add	r3, r1, r3
	str	r3, [r4, #456]
	bne	.L815
	ldr	r3, [r6, #28]
	cmp	r2, r3
	strhi	r7, [r4, #464]
	movhi	r3, #1
	strhi	r3, [r4, #460]
.L815:
	mov	r3, #0
	str	r3, [r4, #448]
	ldr	r3, [r6, #28]
	cmp	r3, r0
	movcc	r3, r0
	str	r3, [r4, #444]
.L814:
	add	r0, r5, #72
	bl	DeleteRawLen
.L816:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L812:
	mov	r6, #0
	strb	r6, [r5]
	ldr	r0, [r4, #452]
	cmp	r0, r6
	beq	.L816
	ldr	r3, .L824
	add	r1, r4, #472
	mov	r2, #80
	sub	r0, fp, #116
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r1, [r4, #460]
	cmp	r1, #1
	beq	.L822
	ldr	r0, [r4, #180]
	ldr	r3, [r4, #452]
	ldr	r2, [r0]
	cmp	r2, r3
	bcc	.L818
	add	r5, r5, #98304
	ldr	r2, [r4, #120]
	str	r3, [fp, #-104]
	mov	ip, #1
	ldr	r1, [r5, #96]
	rsb	r2, r2, r3
	add	r2, r1, r2
	str	r2, [fp, #-116]
	ldr	r2, [r0]
	strb	ip, [fp, #-110]
	rsb	r3, r3, r2
	strb	ip, [fp, #-111]
	cmp	r3, #3
	str	r3, [fp, #-100]
	bls	.L823
	add	r5, r5, #96
	sub	r0, fp, #116
	mov	r1, r5
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L821
	ldr	r2, [r4, #204]
	sub	r1, fp, #116
	mov	r0, r5
	bl	InsertStreamSeg
	b	.L816
.L818:
	str	r6, [sp]
	mov	r2, r7
	sub	r1, fp, #116
	mov	r0, r5
	mov	r3, #1
	bl	ProcessSegRoll
	b	.L816
.L822:
	ldr	r2, [r4, #464]
	mov	r3, r1
	str	r1, [sp]
	mov	r0, r5
	sub	r1, fp, #116
	bl	ProcessSegRoll
	b	.L816
.L823:
	movw	r2, #2931
	ldr	r1, .L824+4
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, r6
	b	.L816
.L821:
	mvn	r0, #3
	b	.L816
.L825:
	.align	2
.L824:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	UNWIND(.fnend)
	.size	ProcessLastUnfinishedSeg, .-ProcessLastUnfinishedSeg
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
	movw	r2, #2970
	mov	r4, r0
	mov	r3, r1
	mov	r0, #0
	ldr	r1, .L830
	bl	dprint_vfmw
	add	r0, r4, #72
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawPacket
.L831:
	.align	2
.L830:
	.word	.LC33
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
	add	r5, r0, #425984
	str	r1, [fp, #-136]
	mov	r4, r0
	ldr	r1, [r5, #276]
	add	r10, r0, #98304
	str	r2, [fp, #-152]
	ldr	r2, [r5, #180]
	str	r1, [fp, #-160]
	mov	r9, r1, asl #2
	mov	r1, #0
	str	r0, [fp, #-156]
	mov	ip, r2
	str	r2, [fp, #-164]
	mov	r3, ip
	mov	r8, r1
	sub	r0, fp, #124
	mov	r2, #80
	add	ip, ip, r9
	mov	r6, r3
	str	ip, [fp, #-140]
	add	r3, r10, #96
	mov	r7, r8
	str	r3, [fp, #-132]
	bl	memset
	add	r3, r4, #72
	str	r3, [fp, #-144]
	b	.L834
.L853:
	rsb	r3, r2, r4
	ldr	r0, [r5, #120]
	ldr	r1, [r10, #96]
	cmp	r3, #3
	rsb	r0, r0, r2
	str	r2, [fp, #-112]
	str	r3, [fp, #-108]
	add	r2, r1, r0
	mov	r1, #1
	str	r2, [fp, #-124]
	strb	r1, [fp, #-118]
	bls	.L852
	ldr	r1, [fp, #-132]
	sub	r0, fp, #124
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L841
	strb	r0, [fp, #-119]
	sub	r3, fp, #124
	ldr	r1, [r6, #4]
	add	r2, r5, #240
	ldr	r0, [fp, #-144]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	cmp	r0, #0
	bne	.L841
.L837:
	ldr	r7, [fp, #-128]
	add	r6, r6, r9
	add	r8, r8, r9
.L834:
	ldr	r3, [fp, #-136]
	cmp	r7, r3
	beq	.L841
	add	r3, r7, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-140]
	ldr	r2, [r6]
	ldr	r4, [r3, r8]
	cmp	r2, r4
	bls	.L853
	ldr	r3, [fp, #-152]
	ldr	r1, [r5, #120]
	ldr	r0, [r10, #96]
	ldr	r3, [r3, #16]
	rsb	r4, r1, r4
	rsb	r1, r1, r2
	str	r2, [fp, #-112]
	rsb	r3, r2, r3
	add	r1, r0, r1
	add	ip, r3, r4
	str	r1, [fp, #-124]
	cmp	ip, #3
	str	ip, [fp, #-108]
	ldr	r2, [r5, #108]
	ldr	r1, [r5, #104]
	bls	.L854
	rsb	r2, r1, r2
	str	r3, [fp, #-148]
	ubfx	r2, r2, #0, #12
	rsb	r2, r2, #4096
	cmp	r2, #2
	bls	.L841
	ldr	r1, [fp, #-132]
	sub	r0, fp, #124
	bl	CheckSegValid
	subs	ip, r0, #0
	bne	.L841
	ldr	r3, [fp, #-148]
	cmp	r4, #0
	str	r3, [fp, #-108]
	bne	.L843
	strb	r4, [fp, #-119]
	mov	r2, #1
	strb	r2, [fp, #-118]
	sub	r3, fp, #124
	ldr	r1, [r6, #4]
	add	r2, r5, #240
	ldr	r0, [fp, #-144]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	b	.L837
.L843:
	strb	ip, [fp, #-118]
	sub	r3, fp, #124
	strb	ip, [fp, #-119]
	add	r2, r5, #240
	ldr	r1, [r6, #4]
	ldr	r0, [fp, #-144]
	bic	r1, r1, #-1073741824
	str	ip, [fp, #-148]
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-132]
	bl	InsertStreamSeg
	ldr	lr, [r5, #120]
	ldr	r7, [r10, #96]
	sub	r1, fp, #124
	ldr	ip, [fp, #-148]
	mov	r3, #1
	ldr	r2, [r5, #204]
	ldr	r0, [fp, #-132]
	str	r4, [fp, #-108]
	strb	ip, [fp, #-119]
	str	lr, [fp, #-112]
	str	r7, [fp, #-124]
	strb	r3, [fp, #-118]
	bl	InsertStreamSeg
	b	.L837
.L854:
	mov	r3, ip
	movw	r2, #3044
	ldr	r1, .L858
	mov	r0, #0
	bl	dprint_vfmw
	b	.L837
.L852:
	movw	r2, #3012
	ldr	r1, .L858
	mov	r0, #0
	bl	dprint_vfmw
	b	.L837
.L841:
	cmp	r7, #0
	ble	.L855
	ldr	r3, [fp, #-152]
	ldr	r3, [r3, #12]
	sub	r1, r3, #1
	cmp	r1, r7
	bhi	.L856
.L845:
	cmp	r1, r7
	beq	.L857
.L847:
	ldr	r2, [fp, #-152]
	mov	r1, #0
	ldr	r0, [fp, #-156]
	bl	SetLastUnfinishedSegInfo
.L833:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L855:
	blt	.L847
	ldr	r3, [fp, #-152]
	ldr	r3, [r3, #12]
	sub	r1, r3, #1
	b	.L845
.L856:
	ldr	r3, [fp, #-160]
	add	r6, r5, #436
	ldr	r2, .L858+4
	mov	ip, #0
	mvn	lr, #0
	mov	r1, ip
	mul	r3, r3, r7
	ldr	r4, [r2, #48]
	ldr	r2, [fp, #-164]
	add	r7, r5, #428
	mov	r8, #1
	add	r0, r5, #472
	add	r3, r3, #1
	ldr	r9, [r2, r3, asl #2]
	mov	r2, #80
	str	lr, [r5, #432]
	bic	r9, r9, #-1073741824
	strh	lr, [r7]	@ movhi
	str	lr, [r5, #440]
	strh	lr, [r6]	@ movhi
	str	ip, [r5, #452]
	str	ip, [r5, #456]
	str	ip, [r5, #460]
	str	ip, [r5, #464]
	str	ip, [r5, #444]
	str	r8, [r5, #448]
	blx	r4
	mov	r1, r9
	ldr	r0, [fp, #-144]
	bl	DeleteRawLen
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L857:
	ldr	r4, [r5, #156]
	ldr	r0, [fp, #-156]
	ldr	r2, [fp, #-152]
	bl	SetLastUnfinishedSegInfo
	mov	r1, r4
	ldr	r0, [fp, #-144]
	bl	DeleteRawLen
	b	.L833
.L859:
	.align	2
.L858:
	.word	.LC32
	.word	vfmw_Osal_Func_Ptr_S
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
	add	r10, r0, #425984
	subs	r7, r1, #0
	ldr	r6, [r10, #276]
	ldr	r4, [r10, #180]
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r9, .L881
	mov	r6, r6, asl #2
	mov	r5, #0
	movw	r8, #438
	b	.L870
.L866:
	add	r5, r5, #1
	add	r4, r4, r6
	cmp	r5, r7
	beq	.L879
.L870:
	ldr	r0, [r4]
	bl	MEM_Phy2Vir
	mov	ip, #1
	mov	r1, #0
	cmp	r0, #0
	beq	.L880
	ldrb	lr, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	mov	lr, lr, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, lr, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, r0, asl #8
	bic	r2, r3, #1020
	cmp	r3, r8
	cmpne	r3, #288
	bic	r2, r2, #3
	streq	ip, [r10, #224]
	streq	r1, [r10, #228]
	cmp	r2, #32768
	bne	.L866
	ldr	r3, [r10, #224]
	cmp	r3, #1
	beq	.L867
.L869:
	add	r5, r5, #1
	mov	r3, #2
	cmp	r5, r7
	str	r3, [r10, #224]
	add	r4, r4, r6
	bne	.L870
.L879:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L867:
	ldr	r3, [r10, #228]
	add	r3, r3, #1
	str	r3, [r10, #228]
	cmp	r3, #30
	bls	.L866
	ldr	ip, [r9]
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	cmp	ip, r3
	beq	.L869
	ldr	r0, [r10, #204]
	blx	ip
	b	.L869
.L880:
	movw	r3, #3113
	ldr	r2, .L881+4
	ldr	r1, .L881+8
	mov	r0, ip
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L882:
	.align	2
.L881:
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
	add	r5, r0, #425984
	mov	r6, r0
	mov	r8, r1
	ldr	r3, [r5, #276]
	mov	r10, r2
	str	r0, [fp, #-248]
	sub	r0, fp, #204
	str	r1, [fp, #-236]
	mov	r1, #0
	mov	r9, r3
	str	r3, [fp, #-240]
	ldr	r3, [r5, #180]
	mov	r9, r9, asl #2
	str	r2, [fp, #-232]
	mov	r2, #80
	mov	r7, r3
	str	r3, [fp, #-244]
	bl	memset
	mov	r2, #80
	mov	r1, #0
	sub	r0, fp, #124
	bl	memset
	ldr	r0, [r5, #120]
	bl	MEM_Phy2Vir
	mov	r4, r0
	ldr	r0, [r10, #16]
	bl	MEM_Phy2Vir
	ldr	r3, .L926
	mov	r1, r4
	mov	r2, #4
	mov	r4, r7
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	GetMeg4ModeFlag
	add	r3, r6, #98304
	mov	r2, r8
	mov	r1, r7
	mov	r0, r6
	mov	r7, r3
	str	r3, [fp, #-220]
	add	r3, r4, r9
	str	r3, [fp, #-216]
	bl	GetNextVop
	mov	r8, #0
	add	r3, r7, #96
	mov	r7, r8
	str	r3, [fp, #-208]
	add	r3, r6, #72
	str	r3, [fp, #-224]
	str	r0, [fp, #-212]
	b	.L884
.L919:
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L886
	ldr	r3, [fp, #-108]
	sub	r0, fp, #124
	ldr	r1, [fp, #-208]
	add	r6, r3, r6
	str	r6, [fp, #-108]
	bl	CheckSegValid
	subs	r6, r0, #0
	bne	.L890
	ldr	r2, [r5, #204]
	sub	r1, fp, #124
	ldr	r0, [fp, #-208]
	strb	r6, [fp, #-119]
	bl	InsertStreamSeg
	ldr	r3, .L926
	mov	r1, r6
	mov	r2, #80
	ldr	ip, [r3, #48]
	str	r0, [fp, #-228]
	sub	r0, fp, #124
	blx	ip
	ldr	r3, [fp, #-228]
	cmp	r3, #0
	bne	.L890
.L891:
	add	r4, r4, r9
	add	r8, r8, r9
	mov	r7, r10
.L884:
	ldr	r3, [fp, #-212]
	cmp	r7, r3
	beq	.L890
	ldr	r3, [fp, #-216]
	add	r10, r7, #1
	ldr	r2, [r4]
	ldr	r0, [r3, r8]
	rsb	r6, r2, r0
	cmp	r6, #3
	bgt	.L919
	sub	r3, r6, #1
	cmp	r3, #2
	bls	.L920
	ldr	r3, [fp, #-232]
	ldr	r1, [fp, #-220]
	str	r2, [fp, #-192]
	ldr	ip, [r3, #16]
	ldr	r3, [r5, #120]
	rsb	ip, r2, ip
	ldr	lr, [r1, #96]
	rsb	r6, r3, r0
	rsb	r1, r3, r2
	add	r3, ip, r6
	add	r1, lr, r1
	cmp	r3, #3
	str	r1, [fp, #-204]
	str	r3, [fp, #-188]
	ldr	r2, [r5, #108]
	ldr	r1, [r5, #104]
	bls	.L921
	rsb	r2, r1, r2
	str	ip, [fp, #-228]
	ubfx	r2, r2, #0, #12
	rsb	r2, r2, #4096
	cmp	r2, #2
	bls	.L890
	ldr	r1, [fp, #-208]
	sub	r0, fp, #204
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L890
	cmp	r6, #0
	ldr	r3, [r5, #224]
	ldr	ip, [fp, #-228]
	bne	.L901
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	mov	lr, #0
	mov	r2, #1
	bfieq	r3, r6, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	ldr	r3, [r4, #4]
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r3, r3, lsr #30
	bfi	r1, r3, #1, #1
	strb	r1, [fp, #-132]
	ldrh	r0, [r4, #10]
	sub	r3, fp, #204
	uxtb	r1, r1
	bfi	r1, r0, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	r0, r1, #3, #4
	strb	r0, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrh	r0, [fp, #-132]
	and	r1, r1, #7
	strb	r2, [fp, #-198]
	str	ip, [fp, #-188]
	bfi	r0, r1, #7, #4
	strb	lr, [fp, #-199]
	add	r2, r5, #240
	strh	r0, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	ldr	r0, [fp, #-224]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #204
	ldr	r0, [fp, #-208]
	bl	InsertStreamSeg
	b	.L891
.L886:
	ldr	r3, [r5, #120]
	sub	r0, fp, #204
	str	r2, [fp, #-192]
	rsb	r2, r3, r2
	ldr	r3, [fp, #-220]
	ldr	r1, [fp, #-208]
	str	r6, [fp, #-188]
	ldr	r3, [r3, #96]
	add	r2, r3, r2
	mov	r3, #1
	str	r2, [fp, #-204]
	strb	r3, [fp, #-198]
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L890
	ldr	r3, [r5, #224]
	add	r2, r5, #240
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r1, [r4, #4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ldr	r0, [fp, #-224]
	mov	r1, r1, lsr #30
	bfi	ip, r1, #1, #1
	strb	ip, [fp, #-132]
	uxtb	r1, ip
	ldrh	ip, [r4, #10]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #204
	ldr	r0, [fp, #-208]
	mov	r3, #0
	strb	r3, [fp, #-199]
	bl	InsertStreamSeg
	cmp	r0, #0
	beq	.L891
.L890:
	cmp	r7, #0
	ble	.L889
	ldr	r3, [fp, #-232]
	ldr	r3, [r3, #12]
	sub	r3, r3, #1
	cmp	r7, r3
	bcc	.L922
	beq	.L923
.L889:
	ldr	r3, [fp, #-212]
	ldr	r2, [fp, #-236]
	clz	r3, r3
	cmp	r2, #1024
	mov	r3, r3, lsr #5
	movls	r3, #0
	cmp	r3, #0
	bne	.L924
.L909:
	ldr	r1, .L926
	add	r2, r5, #428
	add	r6, r5, #436
	mov	r3, #0
	mvn	ip, #0
	mov	lr, #1
	str	ip, [r5, #432]
	add	r0, r5, #472
	strh	ip, [r2]	@ movhi
	mov	r2, #80
	ldr	r4, [r1, #48]
	mov	r1, r3
	str	ip, [r5, #440]
	strh	ip, [r6]	@ movhi
	str	r3, [r5, #452]
	str	r3, [r5, #456]
	str	r3, [r5, #460]
	str	r3, [r5, #464]
	str	r3, [r5, #444]
	str	lr, [r5, #448]
	blx	r4
.L883:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L920:
	str	r2, [fp, #-228]
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-228]
	subs	ip, r0, #0
	beq	.L925
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	ldrb	r0, [ip]	@ zero_extendqisi2
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	mov	r3, r1, asl #16
	orr	r3, r3, r0, asl #24
	orr	r3, r3, ip, asl #8
	cmp	r3, #256
	beq	.L891
	ldr	r3, [r5, #224]
	mov	r0, #1
	cmp	r3, #1
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-52]
	sub	r3, fp, #124
	ldr	r1, [r4, #4]
	ldrb	ip, [fp, #-52]	@ zero_extendqisi2
	mov	r1, r1, lsr #30
	bfi	ip, r1, #1, #1
	strb	ip, [fp, #-52]
	uxtb	r1, ip
	ldrh	ip, [r4, #10]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-52]
	ldr	r1, [r4, #8]
	ldrb	ip, [fp, #-52]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-52]
	ldr	r1, [r4, #8]
	ldrh	lr, [fp, #-52]
	and	r1, r1, #7
	ldr	ip, [r5, #120]
	bfi	lr, r1, #7, #4
	ldr	r1, [fp, #-220]
	rsb	ip, ip, r2
	str	r2, [fp, #-112]
	strb	r0, [fp, #-118]
	add	r2, r5, #240
	ldr	r1, [r1, #96]
	str	r6, [fp, #-108]
	add	ip, r1, ip
	strh	lr, [fp, #-52]	@ movhi
	str	ip, [fp, #-124]
	ldr	r1, [r4, #4]
	ldr	r0, [fp, #-224]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	b	.L891
.L901:
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	mov	r7, #0
	add	r2, r5, #240
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r1, [r4, #4]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	mov	r1, r1, lsr #30
	bfi	r0, r1, #1, #1
	strb	r0, [fp, #-132]
	ldrh	lr, [r4, #10]
	uxtb	r1, r0
	ldr	r0, [fp, #-224]
	bfi	r1, lr, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	lr, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	lr, r1, #3, #4
	strb	lr, [fp, #-132]
	ldr	r1, [r4, #8]
	str	ip, [fp, #-188]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	strb	r7, [fp, #-198]
	bfi	ip, r1, #7, #4
	strb	r7, [fp, #-199]
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #204]
	sub	r1, fp, #204
	ldr	r0, [fp, #-208]
	bl	InsertStreamSeg
	ldr	r3, [fp, #-220]
	ldr	ip, [r5, #120]
	sub	r1, fp, #204
	ldr	r2, [r5, #204]
	ldr	lr, [r3, #96]
	mov	r3, #1
	ldr	r0, [fp, #-208]
	strb	r7, [fp, #-199]
	str	r6, [fp, #-188]
	str	ip, [fp, #-192]
	str	lr, [fp, #-204]
	strb	r3, [fp, #-198]
	bl	InsertStreamSeg
	b	.L891
.L921:
	movw	r2, #3253
	ldr	r1, .L926+4
	mov	r0, #0
	bl	dprint_vfmw
	b	.L891
.L922:
	ldr	r3, [fp, #-240]
	add	lr, r5, #436
	ldr	r2, .L926
	add	r6, r5, #428
	mov	ip, #0
	mov	r8, #1
	mul	r3, r3, r7
	ldr	r4, [r2, #48]
	ldr	r2, [fp, #-244]
	mvn	r7, #0
	mov	r1, ip
	add	r0, r5, #472
	add	r3, r3, #1
	ldr	r9, [r2, r3, asl #2]
	mov	r2, #80
	str	r7, [r5, #432]
	bic	r9, r9, #-1073741824
	strh	r7, [r6]	@ movhi
	str	r7, [r5, #440]
	strh	r7, [lr]	@ movhi
	str	ip, [r5, #452]
	str	ip, [r5, #456]
	str	ip, [r5, #460]
	str	ip, [r5, #464]
	str	ip, [r5, #444]
	str	r8, [r5, #448]
	blx	r4
	mov	r1, r9
	ldr	r0, [fp, #-224]
	bl	DeleteRawLen
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L924:
	ldr	r1, .L926+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r0, [fp, #-224]
	mov	r1, #1
	bl	DeleteRawPacket
	b	.L909
.L923:
	ldr	r4, [r5, #156]
	mov	r1, r7
	ldr	r0, [fp, #-248]
	ldr	r2, [fp, #-232]
	bl	SetLastUnfinishedSegInfo
	mov	r1, r4
	ldr	r0, [fp, #-224]
	bl	DeleteRawLen
	b	.L883
.L925:
	movw	r2, #3223
	ldr	r1, .L926+12
	bl	dprint_vfmw
	b	.L883
.L927:
	.align	2
.L926:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	.word	.LC36
	.word	.LC35
	UNWIND(.fnend)
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	2
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r4, r0, #425984
	mov	r5, r0
	ldr	r3, [r4, #160]
	cmp	r3, #3
	mov	r3, #2
	streq	r3, [r4, #160]
	mvneq	r0, #6
	beq	.L930
	str	r3, [r4, #160]
	sub	r0, fp, #60
	bl	ReadScdStateReg
	ldr	r6, [fp, #-48]
	movw	r3, #34464
	movt	r3, 1
	cmp	r6, r3
	bls	.L931
	ldr	r3, [r5, #12]
	cmp	r3, #0
	beq	.L936
.L931:
	ldr	r1, [r4, #276]
	ldr	r0, [fp, #-36]
	bl	__aeabi_uidiv
	cmp	r0, r6
	movcc	r7, r0
	movcs	r7, r6
	cmp	r6, r7
	bhi	.L937
.L933:
	sub	r2, fp, #60
	mov	r1, r7
	mov	r0, r5
	bl	ProcessLastUnfinishedSeg
	clz	r3, r7
	mov	r3, r3, lsr #5
	cmp	r0, #0
	moveq	r4, r3
	orrne	r4, r3, #1
	cmp	r4, #0
	bne	.L930
	ldr	r3, [r5, #12]
	sub	r2, fp, #60
	sub	r1, r7, #1
	mov	r0, r5
	cmp	r3, #2
	beq	.L934
	bl	ProcessNotMpeg4ScdUpMsg
	mov	r0, r4
.L930:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L937:
	ldrsb	r3, [r5, #2]
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r5, #2]
	b	.L933
.L934:
	bl	ProcessMpeg4ScdUpMsg
	mov	r0, r4
	b	.L930
.L936:
	mov	r0, r5
	mov	r1, r6
	bl	ProcessExceptionalStartCodeNum
	mvn	r0, #6
	b	.L930
	UNWIND(.fnend)
	.size	ProcessScdReturn, .-ProcessScdReturn
	.align	2
	.global	SCDDRV_SaveRawStream
	.type	SCDDRV_SaveRawStream, %function
SCDDRV_SaveRawStream:
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
	ldr	r6, .L946
	mov	r7, r0
	mov	r8, r1
	mov	r5, r2
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r4, .L946+4
	mov	r0, #0
	ldr	r9, [r1, #12]
	ldr	r3, [r4, #16]
	blx	r3
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L940
	add	r1, r8, #28
	mov	r0, r9
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L945
.L941:
	ldr	r2, [r6, r7, asl #2]
	ldr	r3, [r4, #44]
	ldr	r1, [r5, #8]
	ldr	r0, [r5, #40]
	blx	r3
.L940:
	ldr	r3, [r4, #12]
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L945:
	ldr	r3, [r4, #44]
	mov	r1, #4
	ldr	r2, [r6, r7, asl #2]
	add	r0, r5, #8
	blx	r3
	b	.L941
.L947:
	.align	2
.L946:
	.word	vfmw_save_str_file
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	2
	.global	NeedReadStream
	.type	NeedReadStream, %function
NeedReadStream:
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
	ldr	r3, [r1, #52]
	cmp	r3, #0
	beq	.L950
	add	r1, r1, #425984
	ldr	r3, [r1, #144]
	cmp	r3, #8
	bgt	.L951
	ldr	r2, .L952
	cmp	r3, #0
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, r0, asl #2]
	add	r2, r2, #475136
	ldr	r0, [r2, #996]
	cmp	r0, #1
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {fp, sp, pc}
.L951:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L950:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L953:
	.align	2
.L952:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	NeedReadStream, .-NeedReadStream
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
	ldr	r3, .L969
	mov	r5, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L969+4
	sub	r0, fp, #120
	ldr	r4, [r3, #8]
	bl	memcpy
	cmp	r5, #0
	beq	.L967
	ldr	r3, [r4, #12]
	cmp	r3, #18
	bhi	.L957
	mov	r2, #1
	movw	r4, #65406
	mov	r2, r2, asl r3
	movt	r4, 5
	and	r4, r4, r2
	cmp	r4, #0
	bne	.L958
	tst	r2, #1
	beq	.L957
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	add	r1, r3, #15
	cmp	r1, r2
	bhi	.L968
	ldr	ip, .L969+8
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
.L958:
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	cmp	r3, r2
	bhi	.L963
	mov	r0, #0
.L964:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L957:
	ldr	r2, .L969+12
	mov	r0, #0
	ldr	r1, .L969+16
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L964
.L963:
	mov	r1, #0
.L960:
	stmia	sp, {r1, r2}
	mov	r0, #0
	ldr	r2, .L969+12
	ldr	r1, .L969+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L964
.L968:
	mov	r1, #15
	b	.L960
.L967:
	mov	r0, r5
	ldr	r2, .L969+12
	ldr	r1, .L969+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L964
.L970:
	.align	2
.L969:
	.word	.LANCHOR0
	.word	.LANCHOR3+104
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+204
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
	ldr	r3, .L993
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L993+4
	sub	r0, fp, #120
	ldr	r5, [r3, #8]
	bl	memcpy
	cmp	r4, #0
	beq	.L991
	ldr	r3, [r5, #12]
	cmp	r3, #18
	ldrls	pc, [pc, r3, asl #2]
	b	.L974
.L976:
	.word	.L975
	.word	.L977
	.word	.L978
	.word	.L979
	.word	.L989
	.word	.L989
	.word	.L985
	.word	.L974
	.word	.L989
	.word	.L989
	.word	.L989
	.word	.L989
	.word	.L989
	.word	.L989
	.word	.L989
	.word	.L975
	.word	.L981
	.word	.L989
	.word	.L985
.L975:
	sub	r1, fp, #120
	mov	r5, #15
.L980:
	ldr	r3, [r4, #8]
	cmp	r5, r3
	bhi	.L992
	ldr	r3, .L993+8
	mov	r2, r5
	ldr	r0, [r4, #40]
	ldr	r3, [r3, #52]
	blx	r3
	str	r5, [r4, #8]
.L989:
	mov	r0, #0
.L987:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L985:
	mov	r5, #15
	sub	r1, fp, #100
	b	.L980
.L977:
	ldr	r3, [r5, #28]
	cmp	r3, #1
	bne	.L989
	sub	r1, fp, #100
	mov	r5, #15
	b	.L980
.L978:
	mov	r5, #19
	sub	r1, fp, #80
	b	.L980
.L979:
	mov	r5, #16
	sub	r1, fp, #60
	b	.L980
.L981:
	mov	r5, #16
	sub	r1, fp, #40
	b	.L980
.L974:
	ldr	r2, .L993+12
	mov	r0, #0
	ldr	r1, .L993+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L992:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, r5
	ldr	r2, .L993+12
	ldr	r1, .L993+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L987
.L991:
	mov	r0, r4
	ldr	r2, .L993+12
	ldr	r1, .L993+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L987
.L994:
	.align	2
.L993:
	.word	.LANCHOR0
	.word	.LANCHOR3+224
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+324
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
	beq	.L1005
	ldr	r3, [r4, #76]
	ands	r5, r3, #128
	bne	.L1006
	add	r7, r0, #425984
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #80]
	ldr	r0, [r7, #292]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L1007
	ldr	r6, .L1012
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
.L999:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1006:
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
	bne	.L1008
	ldr	r7, .L1012
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
	add	r3, r6, #425984
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
.L1005:
	ldr	r2, [r4, #76]
	ands	r5, r2, #128
	bne	.L1009
	ldrb	r0, [r4, #72]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L999
	add	r6, r6, #425984
	ldr	r2, [r4, #8]
	ldr	ip, [r4, #80]
	ldr	r0, [r6, #292]
	add	r3, r2, r0
	cmp	r3, ip
	bhi	.L1010
	ldr	r7, .L1012
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
	b	.L999
.L1009:
	ldr	r2, [r4, #8]
	cmp	r2, #128
	bgt	.L1011
	ldr	r1, .L1012
	add	r3, r0, #425984
	add	r0, r3, #296
	str	r2, [r3, #292]
	ldr	r3, [r1, #52]
	ldr	r2, [r4, #8]
	ldr	r1, [r4, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1008:
	str	r1, [sp]
	mov	r0, #1
	mov	r1, #128
	ldr	r2, .L1012+4
	str	r1, [sp, #4]
	ldr	r1, .L1012+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L999
.L1007:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1012+4
	ldr	r1, .L1012+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L999
.L1011:
	mov	r3, r2
	mov	r0, r1
	ldr	r2, .L1012+4
	mov	r1, #128
	str	r1, [sp]
	ldr	r1, .L1012+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L999
.L1010:
	mov	r0, r1
	str	ip, [sp]
	ldr	r2, .L1012+4
	ldr	r1, .L1012+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L999
.L1013:
	.align	2
.L1012:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+344
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
	bhi	.L1017
	ldr	r5, .L1018
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
.L1016:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1017:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1018+4
	ldr	r1, .L1018+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1016
.L1019:
	.align	2
.L1018:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+364
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
	beq	.L1021
	ldr	r3, [r1, #8]
	cmp	r3, #128
	bgt	.L1025
	ldr	r2, .L1027
	add	r4, r0, #425984
	add	r0, r4, #296
	str	r3, [r4, #292]
	ldr	r3, [r2, #52]
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1021:
	add	r4, r0, #425984
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #80]
	ldr	r0, [r4, #292]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L1026
	ldr	r7, .L1027
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
.L1023:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1026:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1027+4
	ldr	r1, .L1027+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1023
.L1025:
	mov	r1, #128
	ldr	r2, .L1027+4
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L1027+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1023
.L1028:
	.align	2
.L1027:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+384
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
	bne	.L1035
	ldr	r2, [r1, #8]
	cmp	r2, #0
	ble	.L1038
	ldr	r2, .L1040
	add	r0, r2, r0, lsl #3
	ldr	r0, [r0, #8]
	ldr	r2, [r0, #12]
	cmp	r2, #5
	beq	.L1032
	cmp	r2, #8
	beq	.L1033
	cmp	r2, #1
	beq	.L1039
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1033:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillREAL8ExtraData
.L1032:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillDIVX3ExtraData
.L1039:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillVC1ExtraData
.L1035:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1038:
	mov	r3, r2
	ldr	r1, .L1040+4
	ldr	r2, .L1040+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1041:
	.align	2
.L1040:
	.word	.LANCHOR0
	.word	.LC46
	.word	.LANCHOR3+404
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
	ldr	r5, .L1057
	mov	r2, #12
	mov	r1, #0
	ldr	r3, [r5, #48]
	mov	r4, r0
	sub	r0, fp, #144
	blx	r3
	cmp	r4, #0
	beq	.L1054
	mov	r1, r4
	ldr	r3, [r5, #52]
	mov	r2, #12
	sub	r0, fp, #144
	blx	r3
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #132
	mov	r2, #96
	ldr	r6, .L1057+4
	blx	r3
	ldr	r3, [r4, #8]
	mov	r8, r7, asl #3
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L1045
	add	r4, r6, r8
	ldr	r3, [r4, #8]
	ldr	r3, [r3, #52]
	cmp	r3, #1
	beq	.L1055
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
	beq	.L1048
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
.L1048:
	ldr	r3, [r5, #28]
	mov	r0, #1
	mov	r1, r7
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
.L1047:
	cmp	r4, #0
	mvnne	r4, #6
.L1045:
	add	r6, r6, r8
	ldr	r0, [r6, #8]
	cmp	r0, #0
	movne	r0, r4
	beq	.L1056
.L1044:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1055:
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
	b	.L1047
.L1054:
	mov	r2, r7
	mov	r0, r4
	ldr	r1, .L1057+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1044
.L1056:
	mov	r3, r7
	movw	r2, #4188
	ldr	r1, .L1057+12
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1044
.L1058:
	.align	2
.L1057:
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
	bhi	.L1075
	ldr	r10, .L1079
	mov	r9, r0, asl #3
	add	r3, r10, r9
	ldr	r6, [r3, #8]
	cmp	r6, #0
	beq	.L1071
	cmp	r1, #0
	beq	.L1076
.L1062:
	adds	r3, r6, #72
	str	r3, [fp, #-52]
	beq	.L1071
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
	beq	.L1071
	mov	r7, #0
	mov	r3, r9
	mov	r9, r7
	mov	r7, r3
	b	.L1066
.L1078:
	ldr	r3, [fp, #-48]
	cmp	r9, r3
	beq	.L1077
.L1066:
	mov	r5, r4, asl #7
	ldr	r2, .L1079+4
	sub	r5, r5, r4, asl #5
	ldr	r1, .L1079+8
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
	bne	.L1078
	mvn	r0, #6
.L1061:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1076:
	add	r3, r6, #425984
	ldr	r3, [r3, #220]
	cmp	r3, #0
	bne	.L1062
.L1071:
	mvn	r0, #0
	b	.L1061
.L1077:
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
.L1075:
	mov	r2, r0
	ldr	r1, .L1079+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1061
.L1080:
	.align	2
.L1079:
	.word	.LANCHOR0
	.word	.LANCHOR3+420
	.word	.LC10
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
	mov	r10, r0
	bhi	.L1092
	ldr	r5, .L1102
	mov	r8, r0, asl #3
	add	r3, r5, r8
	ldr	r6, [r3, #8]
	cmp	r6, #0
	beq	.L1083
	ldr	r3, [r5, #308]
	cmp	r3, r0
	beq	.L1084
	ldr	r9, .L1102+4
.L1085:
	add	r4, r6, #425984
	ldr	r3, [r9, #52]
	mov	r2, #68
	add	r1, r6, #4
	sub	r0, fp, #240
	add	r7, r4, #296
	blx	r3
	ldr	ip, [r4, #220]
	add	r5, r5, r8
	ldr	r3, [r9, #52]
	mov	r1, r7
	sub	r0, fp, #172
	str	ip, [fp, #-248]
	mov	r2, #128
	ldr	ip, [r4, #292]
	str	ip, [fp, #-252]
	blx	r3
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L1086
	add	r3, r3, #425984
	ldr	r2, [r3, #220]
	cmp	r2, #0
	bne	.L1100
.L1086:
	adds	r5, r6, #72
	beq	.L1087
.L1101:
	add	r2, r6, #98304
	ldr	r3, [r2, #76]
	ldr	r1, [r2, #72]
	subs	r1, r3, r1
	addmi	r1, r1, #1024
.L1091:
	mov	r0, r5
	mov	r5, #0
	bl	DeleteRawPacket
	mov	r1, #1
	mov	r0, r10
	bl	DeleteRawPacketInBuffer
	movw	r2, #49704
	mov	r0, r6
	movt	r2, 6
	ldr	r3, [r9, #48]
	mov	r1, r5
	ldrb	r6, [r4, #204]	@ zero_extendqisi2
	blx	r3
	add	r2, r4, #428
	add	r0, r4, #436
	mvn	r3, #0
	mov	ip, #1
	str	r3, [r4, #432]
	mov	r1, r5
	strh	r3, [r2]	@ movhi
	mov	r2, #80
	str	r3, [r4, #440]
	sxtb	r6, r6
	strh	r3, [r0]	@ movhi
	add	r0, r4, #472
	str	ip, [r4, #448]
	ldr	r3, [r9, #48]
	str	r5, [r4, #452]
	str	r5, [r4, #456]
	str	r5, [r4, #460]
	str	r5, [r4, #464]
	str	r5, [r4, #444]
	blx	r3
	mvn	r2, #0
	mvn	r3, #0
	mov	ip, #2
	strd	r2, [r4, #240]
	sub	r1, fp, #240
	str	ip, [r4, #276]
	mov	r0, r10
	str	r6, [r4, #204]
	bl	SM_Config
	ldr	r3, [fp, #-248]
	ldr	r2, [fp, #-252]
	sub	r1, fp, #172
	sub	r3, r3, #1
	mov	r0, r7
	cmp	r3, #1
	str	r2, [r4, #292]
	mov	r2, #128
	movhi	r3, #0
	movls	r3, #1
	str	r3, [r4, #220]
	ldr	r3, [r9, #52]
	blx	r3
	mov	r0, r5
.L1099:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1100:
	ldr	r2, [r3, #208]
	cmp	r2, #0
	movle	r2, #0
	strle	r2, [r3, #220]
	adds	r5, r6, #72
	bne	.L1101
.L1087:
	ldr	r1, .L1102+8
	movw	r3, #1284
	ldr	r2, .L1102+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, r5
	b	.L1091
.L1084:
	mov	r3, r0, asl #6
	ldr	r9, .L1102+4
	sub	r3, r3, r0, asl #2
	mov	r1, #0
	add	r3, r5, r3
	mov	r0, #1
	ldr	r2, [r9, #128]
	str	r1, [r3, #312]
	blx	r2
	movw	r3, #1266
	ldr	r2, .L1102+12
	mov	r0, #22
	ldr	r1, .L1102+16
	bl	dprint_vfmw
	b	.L1085
.L1092:
	mvn	r0, #0
	b	.L1099
.L1083:
	mov	r0, r6
	movw	r2, #1256
	ldr	r1, .L1102+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1099
.L1103:
	.align	2
.L1102:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC52
	.word	.LANCHOR3+444
	.word	.LC51
	.word	.LC50
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
	ldr	r8, .L1146
	mov	r10, r0, asl #3
	ldr	r6, .L1146+4
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
	beq	.L1137
	mov	r0, r5
	bl	VCTRL_GetStreamInterface
	subs	r7, r0, #0
	beq	.L1139
	ldr	r3, [r6, #52]
	sub	r0, fp, #56
	mov	r2, #12
	mov	r1, r7
	blx	r3
	ldr	r3, [r7, #4]
	cmp	r3, #0
	beq	.L1137
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1140
	ldr	r3, .L1146+8
	mov	r0, #0
	ldr	r2, [r6, #16]
	ldr	r7, [r3, r5, asl #2]
	str	r3, [fp, #-64]
	cmp	r7, #0
	addne	r7, r7, #475136
	ldrne	r7, [r7, #956]
	blx	r2
	ldr	r3, [fp, #-64]
	ldr	r2, .L1146+4
	ldr	r3, [r3, r5, asl #2]
	cmp	r3, #0
	beq	.L1112
	add	r3, r3, #475136
	ldr	r3, [r3, #956]
	cmp	r3, r7
	bne	.L1141
.L1112:
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
	beq	.L1142
.L1110:
	cmp	r7, #0
	bne	.L1137
	ldrb	r6, [r9, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L1143
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1144
.L1115:
	add	r4, r4, #98304
	ldr	r2, [r9, #8]
	mov	r0, #0
	ldr	r3, [r4, #92]
	add	r3, r3, r2
	str	r3, [r4, #92]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1144:
	mov	r1, r9
	mov	r0, r5
	bl	FillExtraData
	cmp	r0, #0
	beq	.L1117
	mov	r2, r5
	ldr	r1, .L1146+12
	mov	r0, r7
	bl	dprint_vfmw
	mov	r1, r9
	ldr	r0, [fp, #-56]
	bl	ReleaseRawStreamData
	cmp	r0, #0
	beq	.L1137
	mov	r0, r7
	ldr	r1, .L1146+16
	bl	dprint_vfmw
.L1137:
	mvn	r0, #6
.L1135:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1140:
	ldr	r3, [fp, #-52]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	blx	r3
	mov	r7, r0
	b	.L1110
.L1143:
	mov	r1, r9
	mov	r0, r5
	bl	FillEosRawStream
	cmp	r0, #0
	bne	.L1145
	mov	r1, r6
	mov	r0, r5
	bl	VCTRL_SetLastFrameState
	b	.L1115
.L1117:
	add	r3, r4, #425984
	ldr	r3, [r3, #288]
	cmp	r3, #0
	beq	.L1115
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1115
	mov	r0, r5
	mov	r1, r9
	bl	FillEopRawStream
	b	.L1115
.L1141:
	ldr	r3, [r2, #12]
	mov	r0, #0
	blx	r3
	mvn	r0, #6
	b	.L1135
.L1139:
	mov	r2, r5
	ldr	r1, .L1146+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1135
.L1145:
	mov	r2, r5
	mov	r0, r7
	ldr	r1, .L1146+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1135
.L1142:
	mov	r3, r5
	movw	r2, #4092
	ldr	r1, .L1146+28
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1135
.L1147:
	.align	2
.L1146:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC56
	.word	.LC57
	.word	.LC53
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	ReadRawStreamData, .-ReadRawStreamData
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
	UNWIND(.pad #116)
	sub	sp, sp, #116
	ldr	r8, .L1192
	mov	r9, r0, asl #3
	ldr	r6, .L1192+4
	add	r3, r8, r9
	mov	r4, r0
	mov	r2, #96
	mov	r1, #0
	ldr	r5, [r3, #8]
	sub	r0, fp, #140
	ldr	r3, [r6, #48]
	blx	r3
	cmp	r5, #0
	beq	.L1148
	ldr	r3, [r5, #12]
	cmp	r3, #20
	beq	.L1148
	ldr	r7, .L1192+8
	mov	r3, r4, asl #24
	str	r3, [fp, #-152]
.L1163:
	ldr	r3, [r5, #52]
	cmp	r3, #0
	beq	.L1150
	add	r3, r5, #425984
	ldr	r3, [r3, #144]
	cmp	r3, #8
	ble	.L1188
.L1148:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1188:
	ldr	r2, [r7, r4, asl #2]
	cmp	r3, #0
	add	r2, r2, #475136
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, #996]
	cmp	r2, #1
	orrne	r3, r3, #1
	cmp	r3, #0
	beq	.L1148
.L1150:
	cmp	r4, #31
	bhi	.L1154
	add	r3, r8, r9
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L1154
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
	beq	.L1154
	sub	r1, fp, #140
	mov	r0, r4
	bl	ReadRawStreamData
	subs	r3, r0, #0
	str	r3, [fp, #-144]
	bne	.L1148
	add	r10, r5, #425984
	ldr	r2, [fp, #-132]
	ldr	r1, [r6]
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
	beq	.L1157
	rsb	r1, r1, r0
	cmp	r1, #2000
	bls	.L1157
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
.L1157:
	ldrd	r2, [fp, #-76]
	mov	r0, #29
	ldr	r1, .L1192+12
	bl	dprint_vfmw
	ldr	r3, [fp, #-132]
	ldr	r2, [fp, #-136]
	mov	r0, #26
	ldr	r1, .L1192+16
	bl	dprint_vfmw
	ldrd	r2, [fp, #-76]
	mov	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1189
.L1158:
	sub	r1, fp, #140
	mov	r0, r4
	bl	SCDDRV_InsertRawPacket
	cmp	r0, #0
	bne	.L1190
	mov	r3, #1
	strb	r3, [r5, #3]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1191
.L1161:
	sub	r2, fp, #140
	mov	r1, r5
	mov	r0, r4
	bl	SCDDRV_SaveRawStream
	ldr	r3, [r7, r4, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #996]
	cmp	r3, #1
	bne	.L1163
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1154:
	mov	r2, r4
	ldr	r1, .L1192+20
	mov	r0, #23
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1191:
	ldr	r3, [r6]
	blx	r3
	add	ip, r8, r4, lsl #2
	ldr	r2, .L1192+24
	ldr	r3, [ip, #340]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L1161
	str	r0, [ip, #340]
	movw	r1, #3489
	ldr	r2, [fp, #-152]
	ldr	r0, .L1192+28
	bl	DBG_AddTrace
	b	.L1161
.L1189:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [fp, #-76]
	b	.L1158
.L1190:
	ldr	r1, .L1192+32
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1148
.L1193:
	.align	2
.L1192:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC58
	.word	.LC59
	.word	.LC61
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+456
	.word	.LC60
	UNWIND(.fnend)
	.size	FillRawData, .-FillRawData
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
	cmp	r1, #4096
	mov	r4, r1
	mov	r7, r0
	mov	r5, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r1, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r0, #327680
	mov	r6, #2
.L1197:
	mov	r3, r4, asl #6
	mov	r1, r4
	add	r3, r3, r4, lsl #4
	mov	r0, r7
	add	r3, r7, r3
	strb	r6, [r3, #12]
	ldr	ip, [r3, #24]
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
	mov	r4, r4, lsr #20
	add	r3, r3, r4
	ubfx	r3, r3, #0, #12
	rsb	r4, r4, r3
	cmp	r5, r4
	bne	.L1197
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
	add	r8, r0, #327680
	mov	r5, r0
	mov	r9, r1
	ldr	r4, [r8, #8]
	mov	r6, r2
	mov	r7, r3
	ldr	ip, [r8, #12]
	ldrd	r2, [r1, #8]
	str	r4, [r8, #16]
	strd	r2, [fp, #-52]
.L1200:
	mov	r3, r4, asl #6
	cmp	r4, ip
	add	r3, r3, r4, lsl #4
	mov	r1, r4
	add	r3, r5, r3
	mov	r0, r5
	add	r10, r3, #40
	beq	.L1211
	ldrsb	r2, [r3, #12]
	cmp	r2, #1
	bne	.L1203
	ldrd	r2, [r3, #40]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	addeq	r3, r4, #1
	beq	.L1210
	cmp	r7, r3
	add	r1, r4, #1
	cmpeq	r6, r2
	mov	r3, r1, asr #31
	bls	.L1206
	str	r4, [r8, #16]
	mov	r4, r3, lsr #20
	add	r1, r1, r4
	ubfx	r1, r1, #0, #12
	rsb	r4, r4, r1
	b	.L1200
.L1203:
	bl	ReleaseStreamSeg
	ldr	ip, [r8, #12]
	add	r3, r4, #1
.L1210:
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #20
	add	r3, r3, r4
	ubfx	r3, r3, #0, #12
	rsb	r4, r4, r3
	b	.L1200
.L1206:
	beq	.L1212
	bcs	.L1200
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
	beq	.L1209
	cmp	r7, r1
	cmpeq	r6, r0
	bls	.L1209
	subs	r6, r6, r0
	sbc	r7, r7, r1
	mov	r0, r6
	mov	r1, r7
	ldrd	r6, [fp, #-52]
	cmp	r7, r1
	cmpeq	r6, r0
	strcc	r4, [r8, #16]
	movcc	ip, r4
.L1209:
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
.L1211:
	mov	r2, r4
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1212:
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
	ldr	ip, .L1249
	str	r2, [fp, #-64]
	mov	r8, r0
	add	ip, ip, r2, lsl #3
	str	r1, [fp, #-72]
	str	r3, [fp, #-76]
	ldr	r2, [ip, #8]
	cmp	r2, #0
	str	r2, [fp, #-68]
	beq	.L1232
	cmp	r3, #1
	mov	r3, r1
	ldrd	r2, [r3, #8]
	ldrd	r0, [r1]
	strd	r2, [fp, #-92]
	movne	r3, #0
	strd	r0, [fp, #-60]
	strne	r3, [fp, #-80]
	beq	.L1243
.L1215:
	add	r9, r8, #98304
	mvn	r6, #0
	mvn	r7, #0
	strd	r6, [fp, #-52]
	ldr	r10, [r9]
	ldr	r1, [r9, #4]
	mov	r3, r10
	str	r10, [r9, #8]
.L1216:
	mov	r0, r3, asl #5
	mov	lr, r3, asl #7
	add	r2, r3, #1
	cmp	r3, r1
	rsb	ip, r0, lr
	add	ip, r8, ip
	mov	r7, r2, asr #31
	beq	.L1244
	ldrd	r4, [ip, #64]
	mov	ip, r7, lsr #22
	ldrd	r6, [fp, #-52]
	add	r2, r2, ip
	ubfx	r2, r2, #0, #10
	cmp	r5, r7
	cmpeq	r4, r6
	beq	.L1245
	ldrd	r6, [fp, #-60]
	cmp	r7, r5
	cmpeq	r6, r4
	bls	.L1222
	str	r3, [r9, #8]
	rsb	r3, ip, r2
	b	.L1216
.L1245:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #22
	add	r2, r2, r3
	ubfx	r2, r2, #0, #10
	rsb	r3, r3, r2
	b	.L1216
.L1244:
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
.L1214:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1222:
	beq	.L1246
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
	beq	.L1228
	ldrd	r4, [fp, #-60]
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L1247
.L1228:
	cmp	r10, r2
	ldr	r3, [fp, #-76]
	addgt	r1, r2, #1024
	rsble	r1, r10, r2
	rsbgt	r1, r10, r1
	cmp	r3, #1
	beq	.L1248
.L1231:
	mov	r3, r2, asl #7
	mov	r0, r8
	sub	r2, r3, r2, asl #5
	add	r8, r8, r2
	ldrd	r2, [r8, #64]
.L1242:
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
.L1243:
	ldr	r3, [fp, #-68]
	add	r3, r3, #425984
	ldr	r2, [r3, #160]
	cmp	r2, #1
	str	r2, [fp, #-80]
	moveq	r2, #3
	streq	r2, [r3, #160]
	b	.L1215
.L1247:
	subs	r4, r4, r0
	sbc	r5, r5, r1
	mov	r0, r4
	mov	r1, r5
	ldrd	r4, [fp, #-92]
	cmp	r5, r1
	cmpeq	r4, r0
	strcc	r3, [r9, #8]
	movcc	r2, r3
	b	.L1228
.L1246:
	cmp	r10, r3
	addgt	r3, r3, #1024
	rsb	r1, r10, r3
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	bne	.L1226
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #425984
	ldr	r2, [r3, #152]
	cmp	r1, r2
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #160]
.L1226:
	rsb	r0, r0, lr
	add	r3, r8, r0
	mov	r0, r8
	ldrd	r2, [r3, #64]
	b	.L1242
.L1248:
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #425984
	ldr	r0, [r3, #152]
	cmp	r1, r0
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #160]
	ldreq	r2, [r9, #8]
	b	.L1231
.L1232:
	mvn	r0, #0
	b	.L1214
.L1250:
	.align	2
.L1249:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
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
	ldr	r3, .L1274
	mov	r5, r0
	mov	r6, r1
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #8]
	cmp	r4, #0
	beq	.L1264
	add	r7, r4, #98304
	add	r0, r7, #96
	bl	SM_SeekPtsInSegArray
	cmp	r0, #0
	bne	.L1254
.L1255:
	mov	r0, #0
.L1253:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1254:
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
	beq	.L1255
	ldr	r2, [r7, #72]
	ldr	r0, [r7, #76]
	cmp	r2, r0
	addgt	r0, r0, #1024
	rsb	r0, r2, r0
	ldrd	r2, [r6, #16]
	mov	r1, r0, asr #31
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L1273
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
	blt	.L1263
.L1262:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r8
	add	r4, r4, #1
	bl	SM_SeekPtsAfterFillNewRaw
	cmp	r0, #0
	beq	.L1255
	cmp	r7, r4
	bge	.L1262
.L1263:
	mvn	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1264:
	mvn	r0, #0
	b	.L1253
.L1273:
	strd	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1274+4
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1253
.L1275:
	.align	2
.L1274:
	.word	.LANCHOR0
	.word	.LC62
	UNWIND(.fnend)
	.size	SM_SeekPts, .-SM_SeekPts
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
	bgt	.L1279
	ldr	r3, .L1281
	add	r5, r5, #425984
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
.L1280:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1279:
	str	r3, [sp]
	mov	r3, r2
	ldr	r1, .L1281+4
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1280
.L1282:
	.align	2
.L1281:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC63
	UNWIND(.fnend)
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	2
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
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
	add	r8, r0, #98304
	adds	ip, r8, #96
	add	r4, r0, #425984
	ldrsb	r6, [r0, #1]
	mov	r7, r0
	ldrne	r10, [r4, #144]
	moveq	r9, ip
	ldrne	r9, [r4, #140]
	moveq	r10, ip
	cmp	r6, #0
	ldr	r5, [r4, #124]
	bne	.L1285
	add	r5, r5, r5, lsr #31
	cmp	r9, r5, asr #1
	movlt	r3, #1
	movge	r3, #0
	cmp	r10, #127
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	bne	.L1303
.L1283:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1285:
	ldr	r6, .L1304
	str	ip, [fp, #-48]
	ldr	r3, [r6]
	blx	r3
	ldr	r2, [r4, #236]
	ldr	ip, [fp, #-48]
	cmp	r0, r2
	bls	.L1288
	rsb	r2, r2, r0
	str	r2, [r4, #232]
	cmp	r2, #1000
	ble	.L1283
	add	r3, r5, #3
	cmp	r5, #0
	movlt	r5, r3
	cmp	r9, r5, asr #2
	movlt	r3, #1
	movge	r3, #0
	cmp	r10, #63
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	beq	.L1283
	cmp	r9, #0
	bne	.L1291
	ldr	r3, [r4, #456]
	cmp	r3, #0
	beq	.L1291
	ldr	r1, .L1304+4
	mov	r0, r9
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	r0, [r4, #204]
	bl	SM_Reset
	ldr	ip, [fp, #-48]
	cmp	ip, #0
	beq	.L1292
	ldr	r3, [r6, #48]
	add	r0, r8, #104
	mov	r2, #327680
	mov	r1, r9
	blx	r3
	ldr	r3, [r4, #120]
	str	r9, [r4, #104]
	str	r9, [r4, #108]
	str	r9, [r4, #112]
	str	r3, [r4, #128]
	str	r3, [r4, #132]
	b	.L1292
.L1288:
	mov	r3, #0
	str	r0, [r4, #236]
	str	r3, [r4, #232]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1291:
	ldr	r1, .L1304+8
	mov	r0, #0
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, [fp, #-48]
	mvn	r1, #0
	mov	r0, ip
	bl	ReleaseStreamSeg
.L1292:
	mov	r3, #0
	strb	r3, [r7, #1]
	strb	r3, [r7]
	b	.L1283
.L1303:
	ldr	r3, .L1304
	mov	r2, #1
	strb	r2, [r0, #1]
	ldr	r3, [r3]
	blx	r3
	str	r6, [r4, #232]
	str	r0, [r4, #236]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1305:
	.align	2
.L1304:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC64
	.word	.LC65
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
	ldr	r3, .L1319
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L1309
	add	r2, r3, #425984
	ldr	r1, [r2, #220]
	cmp	r1, #0
	beq	.L1309
	ldr	r2, [r2, #212]
	cmp	r2, #1
	beq	.L1309
	add	r2, r3, #28
	ldr	ip, [r3, #12]
	sub	r3, fp, #24
	ldmia	r2, {r0, r1, r2}
	cmp	ip, #19
	stmia	r3, {r0, r1, r2}
	beq	.L1309
	mov	r1, r3
	mov	r0, ip
	bl	SCDDRV_IsSCDByPass
	adds	r0, r0, #0
	movne	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1309:
	mov	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1320:
	.align	2
.L1319:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
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
	ldr	r2, .L1340
	mov	r3, r0, asl #2
	str	r1, [fp, #-48]
	add	r1, r2, r3
	mov	r6, r0
	ldr	r2, [r1, #324]
	cmp	r2, #0
	beq	.L1322
	cmp	r2, #1
	beq	.L1323
.L1332:
	mvn	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1322:
	ldr	r2, .L1340
	rsb	r3, r3, r0, lsl #6
	ldr	r8, .L1340+4
	mov	r5, #32
	add	r3, r2, r3
	ldr	r9, .L1340+8
	ldr	r4, [r3, #308]
	b	.L1331
.L1325:
	subs	r5, r5, #1
	beq	.L1332
.L1331:
	add	r3, r4, #1
	mov	r1, r6
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #27
	add	r3, r3, r4
	and	r3, r3, #31
	rsb	r4, r4, r3
	mov	r0, r4
	bl	SCDDRV_CanNotSelectInst
	cmp	r0, #0
	bne	.L1325
	ldr	r3, .L1340
	ldr	r2, [r8]
	add	r3, r3, r4, lsl #3
	ldr	r7, [r3, #8]
	blx	r2
	add	r10, r7, #425984
	ldr	r1, [r10, #272]
	subs	r1, r0, r1
	bmi	.L1337
	ldrsh	ip, [r7, #2]
	cmp	ip, #1
	beq	.L1338
.L1327:
	str	r0, [r10, #272]
	ldrsb	r1, [r7]
	cmp	r1, #1
	movne	r1, #0
	strneb	r1, [r7, #1]
	beq	.L1339
.L1330:
	ldr	ip, [r9, r4, asl #2]
	mov	r1, r6
	mov	r0, r7
	add	ip, ip, #475136
	ldr	ip, [ip, #984]
	str	ip, [r10, #424]
	bl	CutStreamWithSCD
	cmn	r0, #6
	movne	r1, #0
	moveq	r1, #1
	cmp	r0, #0
	strb	r1, [r7]
	bne	.L1325
	ldr	r2, [fp, #-48]
	mov	r3, #1
	str	r0, [fp, #-52]
	mov	r1, r3
	ldr	r0, .L1340+12
	movw	lr, #4646
	str	r4, [r2]
	str	r3, [r10, #220]
	add	r2, r0, r4, lsl #2
	ldr	r3, .L1340+16
	mov	r0, r4
	str	lr, [sp]
	bl	RecordPOS
	ldr	ip, [fp, #-52]
	mov	r0, ip
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1338:
	cmp	r1, #500
	bcc	.L1325
	b	.L1327
.L1337:
	str	r0, [r10, #272]
	ldrsh	r1, [r7, #2]
	cmp	r1, #1
	bne	.L1327
	b	.L1325
.L1339:
	mov	r0, r7
	bl	SCDDRV_ProcessSegFull
	b	.L1330
.L1323:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r1, #324]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1341:
	.align	2
.L1340:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0+468
	.word	.LANCHOR3+468
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
	bne	.L1342
	mov	r0, r4, asl #6
	ldr	r3, .L1344
	sub	r0, r0, r4, asl #2
	ldr	r1, [fp, #-24]
	ldr	r2, .L1344+4
	add	r0, r3, r0
	mov	r3, #1
	add	r4, r0, #312
	str	r1, [r0, #308]
	str	r3, [r0, #312]
	ldr	r3, [r2]
	blx	r3
	movw	r3, #4851
	ldr	r2, .L1344+8
	ldr	r1, .L1344+12
	str	r0, [r4, #4]
	mov	r0, #26
	bl	dprint_vfmw
.L1342:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1345:
	.align	2
.L1344:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+488
	.word	.LC66
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
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
	ldr	r3, .L1352
	mov	r4, r0
	mov	r4, r4, asl #6
	ldr	r3, [r3]
	blx	r3
	ldr	r3, .L1352+4
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
.L1353:
	.align	2
.L1352:
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
	ldr	r3, .L1364
	add	r0, r3, r0, lsl #3
	ldr	r4, [r0, #8]
	ldr	r0, [r4, #52]
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	adds	r5, r4, #72
	beq	.L1357
	add	r2, r4, #98304
	ldr	r3, [r2, #76]
	ldr	r2, [r2, #72]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
.L1360:
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
	ldr	r1, .L1364+4
	bl	dprint_vfmw
	add	r4, r4, #425984
	ldr	r0, [r4, #204]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_Reset
.L1357:
	ldr	r1, .L1364+8
	bl	dprint_vfmw
	mov	r3, r5
	b	.L1360
.L1365:
	.align	2
.L1364:
	.word	.LANCHOR0
	.word	.LC67
	.word	.LC68
	UNWIND(.fnend)
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	2
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
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
	ldr	r6, .L1383
	ldr	r4, .L1383+4
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
	bne	.L1379
.L1367:
	ldr	r3, .L1383+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1372
	mov	r1, r5
	mov	r0, #0
	bl	VDH_Notify_ModuleIdle
.L1372:
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1379:
	ldr	r0, [r8, #4]
	mov	r9, r5, asl #6
	rsb	r8, r7, r9
	mov	r1, #1
	add	r8, r6, r8
	add	r0, r0, #2080
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r10, [r8, #308]
	ldr	r3, [r8, #304]
	add	r2, r6, r10, lsl #3
	ldr	ip, [r2, #8]
	cmp	ip, #0
	cmpne	r3, #0
	beq	.L1380
	ldr	r3, .L1383+12
	movw	r2, #4734
	mov	r1, #2
	str	r2, [sp]
	mov	r0, r10
	add	r2, r6, #596
	str	ip, [fp, #-56]
	bl	RecordPOS
	mov	r0, r5
	bl	SCDDRV_RecordGlobalState
	ldr	r3, [r8, #312]
	ldr	ip, [fp, #-56]
	cmp	r3, #1
	beq	.L1381
.L1369:
	ldr	r3, [r4, #128]
	mov	r0, #1
	blx	r3
	ldr	r3, [r4, #128]
	mov	r0, #0
	blx	r3
	b	.L1367
.L1380:
	mov	r2, #0
	ldr	r3, [r4, #128]
	str	r2, [r8, #312]
	mov	r0, #1
	blx	r3
	b	.L1367
.L1381:
	add	r8, ip, #425984
	ldr	r3, [r8, #220]
	cmp	r3, #1
	beq	.L1382
.L1370:
	mov	r10, #0
	sub	r1, fp, #48
	str	r10, [r8, #212]
	mov	r0, r5
	bl	SM_DoNextInstance
	rsb	r7, r7, r9
	cmp	r0, r10
	bne	.L1371
	ldr	r1, [fp, #-48]
	add	r6, r6, r7
	mov	r2, #1
	ldr	r3, [r4]
	str	r2, [r6, #312]
	str	r1, [r6, #308]
	blx	r3
	str	r0, [r6, #316]
	b	.L1369
.L1371:
	add	r6, r6, r7
	ldr	r3, [r4, #128]
	mov	r0, #1
	str	r10, [r6, #312]
	blx	r3
	b	.L1369
.L1382:
	mov	r0, ip
	mov	r1, r5
	bl	ProcessScdReturn
	mov	r0, r10
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1370
.L1384:
	.align	2
.L1383:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HalDisable
	.word	.LANCHOR3+508
	UNWIND(.fnend)
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
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
	bne	.L1393
	ldr	r4, .L1398
	movw	r3, #4784
	str	r6, [sp]
	mov	r0, #26
	ldr	r2, .L1398+4
	ldr	ip, [r4, #312]
	ldr	r1, .L1398+8
	str	ip, [sp, #4]
	bl	dprint_vfmw
	ldr	r5, [r4, #312]
	cmp	r5, #0
	beq	.L1397
	ldr	r7, .L1398+12
	movw	r3, #4794
	ldr	r2, .L1398+4
	mov	r0, #26
	ldr	r1, .L1398+8
	str	r5, [sp, #4]
	str	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [r7]
	blx	r3
	ldr	r3, [r4, #316]
	cmp	r0, r3
	strcc	r0, [r4, #316]
	bcc	.L1389
	rsb	r0, r3, r0
	cmp	r0, #2000
	bls	.L1389
	ldr	r2, [r4, #308]
	mov	r3, r6
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1398+16
	bl	dprint_vfmw
	ldr	r3, .L1398+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1390
	mov	r1, r6
	mov	r0, r6
	bl	VDH_Reset_Module
.L1391:
	mov	r5, #0
	ldr	r3, [r7, #128]
	str	r5, [r4, #312]
	mov	r0, #1
	blx	r3
	ldr	r0, [r4, #308]
	add	r4, r4, r0, lsl #3
	ldr	r3, [r4, #8]
	cmp	r3, r5
	addne	r3, r3, #425984
	strne	r5, [r3, #212]
	mov	r5, #0
	bl	DeleteLastSendRaw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1389:
	mov	r2, #0
	movw	r3, #4831
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1398+4
	mov	r5, #1
	ldr	r1, .L1398+24
	bl	dprint_vfmw
.L1386:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1397:
	str	r5, [sp]
	movw	r3, #4788
	ldr	r2, .L1398+4
	mov	r0, #26
	ldr	r1, .L1398+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1390:
	mov	r0, r6
	bl	ResetSCD
	b	.L1391
.L1393:
	mvn	r5, #0
	b	.L1386
.L1399:
	.align	2
.L1398:
	.word	.LANCHOR0
	.word	.LANCHOR3+528
	.word	.LC69
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
	.word	g_HalDisable
	.word	.LC72
	.word	.LC70
	UNWIND(.fnend)
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
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
	ldr	r5, .L1413
	mov	r4, #0
	b	.L1404
.L1403:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L1412
.L1404:
	ldr	r3, [r5, r4, asl #3]
	cmp	r3, #0
	add	r2, r3, #425984
	beq	.L1403
	ldr	r3, [r2, #220]
	cmp	r3, #1
	bne	.L1403
	mov	r0, r4
	add	r4, r4, #1
	bl	FillRawData
	cmp	r4, #32
	bne	.L1404
.L1412:
	mov	r2, #1
	mov	r3, #0
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1413+4
	ldr	r1, .L1413+8
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_CheckDevice
	subs	r4, r0, #0
	beq	.L1405
	mov	r2, #0
	movw	r3, #4880
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1413+4
	ldr	r1, .L1413+12
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1405:
	str	r4, [sp]
	movw	r3, #4875
	ldr	r2, .L1413+4
	mov	r0, #26
	ldr	r1, .L1413+16
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.12
.L1414:
	.align	2
.L1413:
	.word	.LANCHOR0+8
	.word	.LANCHOR3+548
	.word	.LC73
	.word	.LC74
	.word	.LC75
	UNWIND(.fnend)
	.size	SM_Wakeup, .-SM_Wakeup
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
	ldr	r4, .L1416
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
	ldr	r1, .L1416+4
	mov	r4, r0
	mov	r0, #24
	bl	dprint_vfmw
	ldr	ip, [fp, #-52]
	ldr	r1, .L1416+8
	mov	r0, #24
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	ldr	r1, .L1416+12
	mov	r0, #24
	mov	r2, r3
	bl	dprint_vfmw
	mov	r2, r10
	ldr	r1, .L1416+16
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r9
	ldr	r1, .L1416+20
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r8
	ldr	r1, .L1416+24
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L1416+28
	mov	r0, #24
	bl	dprint_vfmw
	mov	r2, r6
	ldr	r1, .L1416+32
	mov	r0, #24
	bl	dprint_vfmw
	sxtb	r2, r4
	ldr	r1, .L1416+36
	mov	r0, #24
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1417:
	.align	2
.L1416:
	.word	.LANCHOR0
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	UNWIND(.fnend)
	.size	PrintScdVtrlReg, .-PrintScdVtrlReg
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
	ldr	r1, .L1419
	bl	dprint_vfmw
	ldr	r2, [r4]
	ldr	r1, .L1419+4
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1419+8
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #12]
	ldr	r1, .L1419+12
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #16]
	ldr	r1, .L1419+16
	mov	r0, #24
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L1419+20
	mov	r0, #24
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1420:
	.align	2
.L1419:
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC88
	.word	.LC89
	.word	.LC90
	UNWIND(.fnend)
	.size	PrintScdStateReg, .-PrintScdStateReg
	.align	2
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
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
	mov	r0, #26
	mov	r4, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, .L1430
	mov	r2, r6
	ldr	r1, .L1430+4
	mov	r0, #26
	add	r3, r3, r6, lsl #3
	ldr	r8, [r3, #8]
	bl	dprint_vfmw
	ldr	r1, .L1430+8
	mov	r0, #26
	add	r5, r8, #98304
	ldr	r2, [r5, #72]
	bl	dprint_vfmw
	ldr	r2, [r5, #76]
	ldr	r1, .L1430+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r5, #80]
	ldr	r1, .L1430+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r5, #84]
	ldr	r1, .L1430+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r5, #88]
	ldr	r1, .L1430+24
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r4, #1
	beq	.L1423
.L1427:
	mov	r2, r6
	ldr	r1, .L1430+28
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1423:
	cmn	r8, #72
	beq	.L1424
	ldr	r4, [r5, #72]
	ldr	r7, [r5, #76]
	subs	r7, r7, r4
	addmi	r7, r7, #1024
	cmp	r7, #0
	ble	.L1427
	mov	r3, r4, asl #7
	mov	r5, #0
	sub	r3, r3, r4, asl #5
	add	r4, r8, r3
.L1426:
	ldr	r2, [r4, #76]
	mov	r0, #26
	ldr	r1, .L1430+32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrd	r2, [r4, #112]
	ldr	r1, .L1430+36
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #80]
	ldr	r1, .L1430+40
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #136]
	ldr	r1, .L1430+44
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r5, r7
	add	r4, r4, #96
	bne	.L1426
	b	.L1427
.L1424:
	movw	r3, #4953
	ldr	r2, .L1430+48
	ldr	r1, .L1430+52
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1427
.L1431:
	.align	2
.L1430:
	.word	.LANCHOR0
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
	.word	.LC101
	.word	.LANCHOR3+560
	.word	.LC102
	UNWIND(.fnend)
	.size	PrintScdRawState, .-PrintScdRawState
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
	mov	r4, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, .L1438
	mov	r2, r7
	ldr	r1, .L1438+4
	mov	r0, #26
	add	r3, r3, r7, lsl #3
	ldr	r5, [r3, #8]
	bl	dprint_vfmw
	ldr	r1, .L1438+8
	mov	r0, #26
	add	r6, r5, #425984
	add	r8, r5, #98304
	ldr	r2, [r6, #104]
	bl	dprint_vfmw
	ldr	r2, [r6, #108]
	ldr	r1, .L1438+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r6, #116]
	ldr	r1, .L1438+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r6, #120]
	ldr	r1, .L1438+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r8, #96]
	ldr	r1, .L1438+24
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r6, #124]
	ldr	r1, .L1438+28
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r6, #128]
	ldr	r1, .L1438+32
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r6, #132]
	ldr	r1, .L1438+36
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r4, #1
	beq	.L1434
.L1435:
	mov	r2, r7
	ldr	r1, .L1438+40
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1434:
	ldr	r4, [r6, #104]
	ldr	r8, [r6, #108]
	rsb	r8, r4, r8
	ubfx	r8, r8, #0, #12
	cmp	r8, #0
	ble	.L1435
	mov	r3, r4, asl #6
	mov	r6, #0
	add	r4, r3, r4, lsl #4
	add	r4, r4, #98304
	add	r4, r4, #116
	add	r4, r5, r4
.L1436:
	ldr	r2, [r4]
	mov	r0, #26
	ldr	r1, .L1438+44
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #-12]
	ldr	r1, .L1438+48
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #4]
	ldr	r1, .L1438+52
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1438+56
	mov	r0, #26
	bl	dprint_vfmw
	ldrsb	r2, [r4, #-8]
	ldr	r1, .L1438+60
	mov	r0, #26
	bl	dprint_vfmw
	ldrb	r2, [r4, #-6]	@ zero_extendqisi2
	ldr	r1, .L1438+64
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #12]
	ldr	r1, .L1438+68
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r8, r6
	add	r4, r4, #80
	bne	.L1436
	b	.L1435
.L1439:
	.align	2
.L1438:
	.word	.LANCHOR0
	.word	.LC103
	.word	.LC104
	.word	.LC105
	.word	.LC106
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
	UNWIND(.fnend)
	.size	PrintScdSegState, .-PrintScdSegState
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
	.type	__func__.52935, %object
	.size	__func__.52935, 19
__func__.52935:
	.ascii	"SCDDRV_LoadDspCode\000"
	.space	1
	.type	__func__.53007, %object
	.size	__func__.53007, 16
__func__.53007:
	.ascii	"DeleteRawPacket\000"
	.type	__FUNCTION__.53117, %object
	.size	__FUNCTION__.53117, 17
__FUNCTION__.53117:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	__func__.53186, %object
	.size	__func__.53186, 14
__func__.53186:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
	.type	__func__.53270, %object
	.size	__func__.53270, 16
__func__.53270:
	.ascii	"SM_CopyRawToSeg\000"
	.type	__func__.53601, %object
	.size	__func__.53601, 16
__func__.53601:
	.ascii	"GetMeg4ModeFlag\000"
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
	.type	__func__.53675, %object
	.size	__func__.53675, 17
__func__.53675:
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
	.type	__func__.53703, %object
	.size	__func__.53703, 17
__func__.53703:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.53728, %object
	.size	__func__.53728, 17
__func__.53728:
	.ascii	"FillVC1ExtraData\000"
	.space	3
	.type	__func__.53733, %object
	.size	__func__.53733, 19
__func__.53733:
	.ascii	"FillDIVX3ExtraData\000"
	.space	1
	.type	__func__.53738, %object
	.size	__func__.53738, 19
__func__.53738:
	.ascii	"FillREAL8ExtraData\000"
	.space	1
	.type	__func__.53746, %object
	.size	__func__.53746, 14
__func__.53746:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.53021, %object
	.size	__func__.53021, 24
__func__.53021:
	.ascii	"DeleteRawPacketInBuffer\000"
	.type	__FUNCTION__.53160, %object
	.size	__FUNCTION__.53160, 9
__FUNCTION__.53160:
	.ascii	"SM_Reset\000"
	.space	3
	.type	__FUNCTION__.53665, %object
	.size	__FUNCTION__.53665, 12
__FUNCTION__.53665:
	.ascii	"FillRawData\000"
	.type	__FUNCTION__.53859, %object
	.size	__FUNCTION__.53859, 18
__FUNCTION__.53859:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.53896, %object
	.size	__func__.53896, 19
__func__.53896:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__FUNCTION__.53883, %object
	.size	__FUNCTION__.53883, 19
__FUNCTION__.53883:
	.ascii	"SM_SCDIntServeProc\000"
	.space	1
	.type	__func__.53890, %object
	.size	__func__.53890, 19
__func__.53890:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	__func__.53905, %object
	.size	__func__.53905, 10
__func__.53905:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__FUNCTION__.53925, %object
	.size	__FUNCTION__.53925, 17
__FUNCTION__.53925:
	.ascii	"PrintScdRawState\000"
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
	ASCII(.ascii	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC3:
	ASCII(.ascii	"Warn: eVidStd = %d have not DSP vfmw bin file!!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC4:
	ASCII(.ascii	"%s failed!\012\000" )
.LC5:
	ASCII(.ascii	"%s success!\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"Ignore the reset request when the SCD[%d] clock is " )
	ASCII(.ascii	"closed.\012\000" )
.LC7:
	ASCII(.ascii	"SCD[%d]   ResetSCD ERROR!!!\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"line: %d Get SmID fail!\000" )
.LC9:
	ASCII(.ascii	"DelRaw err PacketNum = %d, DelNum = %d\012\000" )
.LC10:
	ASCII(.ascii	"%s release RawPhyAddr = 0x%x, Len = %d\012\000" )
.LC11:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = " )
	ASCII(.ascii	"%d,Next Length = %d,is_extern_eop_flag = %d\012\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC12:
	ASCII(.ascii	"line: %d pSmInstArray is NULL!\012\000" )
.LC13:
	ASCII(.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast" )
	ASCII(.ascii	"Seg=%d\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"-------- forece release seg[%d] -----------\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"0x%02x,\000" )
.LC17:
	ASCII(.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg" )
	ASCII(.ascii	"=%d StreamID=%d\012\000" )
.LC18:
	ASCII(.ascii	"Array out of bound in function %s\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"ScdId is wrong! %s error\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"%s,line: %d\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"%s: g_hex_base_vir_addr = NULL\012\000" )
.LC22:
	ASCII(.ascii	"line: %d, SmID = %d, pSmCfg = %p is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC23:
	ASCII(.ascii	"line: %d, SmID = %d is not expected!\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC25:
	ASCII(.ascii	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC26:
	ASCII(.ascii	"line: %d, delet raw failed!\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"[%s %d] VirAddr is null!!\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"copy raw to seg fail\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"InstID = %d EsRelease!\012\000" )
.LC30:
	ASCII(.ascii	"Cann't Start SCD, Ret = %d\012\000" )
.LC31:
	ASCII(.ascii	"SM_CfgBuf Err! ret =%d\012\000" )
.LC32:
	ASCII(.ascii	"Line: %d, The length of seg packet is invalid: %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC33:
	ASCII(.ascii	"Line: %d, start code num from scd state reg: %d, re" )
	ASCII(.ascii	"lease raw packet anyway!\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"[%s %d] pCurrentStartCodeVirAddr is null!!\012\000" )
.LC35:
	ASCII(.ascii	"Line: %d, pNextStartCodeVirAddr is null!\012\000" )
	.space	2
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
	ASCII(.ascii	"line: %d, pScdInstance is NULL!\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"%s %d force to clear SCDState = 0\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum !!\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000" )
	.space	3
.LC54:
	ASCII(.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"Chan %d FillEosRawStream failed!\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"Chan %d FillExtraData failed!\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"Release this packet failed!\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"raw_pts: %lld\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000" )
.LC60:
	ASCII(.ascii	"!!!push raw err!!!\012\000" )
.LC61:
	ASCII(.ascii	"Chan%d raw full\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000" )
	.space	2
.LC64:
	ASCII(.ascii	"scd buffer is full, reset scd!\012\000" )
.LC65:
	ASCII(.ascii	"(%d ms) not release stream seg, release anyway!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC66:
	ASCII(.ascii	"%s,%d, active scd Success!\012\000" )
.LC67:
	ASCII(.ascii	"Move raw data failed, force to reset scd.\012\000" )
	.space	1
.LC68:
	ASCII(.ascii	"SCD GetRawStreamNum Fail.\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\012\000" )
.LC72:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000" )
	.space	3
.LC73:
	ASCII(.ascii	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\012\000" )
.LC74:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000" )
	.space	2
.LC75:
	ASCII(.ascii	"%s,%d,find idle SCD(ID = %d)\012\000" )
	.space	2
.LC76:
	ASCII(.ascii	"***Print Scd[%d] Vtrl Reg Now\012\000" )
	.space	1
.LC77:
	ASCII(.ascii	"DownMsgPhyAddr = %x\012\000" )
	.space	3
.LC78:
	ASCII(.ascii	"UpMsgPhyAddr = %x\012\000" )
	.space	1
.LC79:
	ASCII(.ascii	"UpLen = %x\012\000" )
.LC80:
	ASCII(.ascii	"BufferFirst = %x\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"BufferLast = %x\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"BufferIni = %x\012\000" )
.LC83:
	ASCII(.ascii	"ScdProtocol = %x\012\000" )
	.space	2
.LC84:
	ASCII(.ascii	"ScdStart = %x\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"***Print Scd[%d] State Reg\012\000" )
.LC86:
	ASCII(.ascii	"Scdover = %d \012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"ShortScdNum = %d \012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"ScdNum = %d \012\000" )
	.space	2
.LC89:
	ASCII(.ascii	"ScdRollAddr = %0x \012\000" )
.LC90:
	ASCII(.ascii	"SrcEaten = %d \012\000" )
.LC91:
	ASCII(.ascii	"********** SmID [%d] RawState begin **********\012\000" )
.LC92:
	ASCII(.ascii	"RawHead=%d\012\000" )
.LC93:
	ASCII(.ascii	"RawTail=%d\012\000" )
.LC94:
	ASCII(.ascii	"RawHistory=%d\012\000" )
	.space	1
.LC95:
	ASCII(.ascii	"RawFirstPacketOffset=%d\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"CurShowIndex=%d\012\000" )
	.space	3
.LC97:
	ASCII(.ascii	"********** SmID [%d] RawState end   **********\012\000" )
.LC98:
	ASCII(.ascii	"RawPhyAddr=0x%x\012\000" )
	.space	3
.LC99:
	ASCII(.ascii	"RawVirAddr=0x%x\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"RawLength=%d\012\000" )
	.space	2
.LC101:
	ASCII(.ascii	"RawPts=%ld\012\000" )
.LC102:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000" )
.LC103:
	ASCII(.ascii	"********** SmID [%d] SegState begin **********\012\000" )
.LC104:
	ASCII(.ascii	"SegHead=%d\012\000" )
.LC105:
	ASCII(.ascii	"SegTail=%d\012\000" )
.LC106:
	ASCII(.ascii	"SegCurrent=%d\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"SegBufPhyAddr=%p\012\000" )
	.space	2
.LC108:
	ASCII(.ascii	"SegBufVirAddr=%p\012\000" )
	.space	2
.LC109:
	ASCII(.ascii	"SegBufSize=%d\012\000" )
	.space	1
.LC110:
	ASCII(.ascii	"SegBufReadAddr=%p\012\000" )
	.space	1
.LC111:
	ASCII(.ascii	"SegBufWriteAddr=%pd\012\000" )
	.space	3
.LC112:
	ASCII(.ascii	"********** SmID [%d] SegState end   **********\012\000" )
.LC113:
	ASCII(.ascii	"SegPhyAddr=0x%x\012\000" )
	.space	3
.LC114:
	ASCII(.ascii	"SegVirAddr=0x%x\012\000" )
	.space	3
.LC115:
	ASCII(.ascii	"SegLength=%d\012\000" )
	.space	2
.LC116:
	ASCII(.ascii	"SegStreamID=%d\012\000" )
.LC117:
	ASCII(.ascii	"SegState=%d\012\000" )
	.space	3
.LC118:
	ASCII(.ascii	"SegIsLastSeg=%d\012\000" )
	.space	3
.LC119:
	ASCII(.ascii	"SegPts=%lld\012\000" )
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
	.type	last_rec_pos_time.53660, %object
	.size	last_rec_pos_time.53660, 128
last_rec_pos_time.53660:
	.space	128
	.type	LastRecPosTime.53856, %object
	.size	LastRecPosTime.53856, 128
LastRecPosTime.53856:
	.space	128
	.type	last_rec_pos_time.53881, %object
	.size	last_rec_pos_time.53881, 128
last_rec_pos_time.53881:
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
