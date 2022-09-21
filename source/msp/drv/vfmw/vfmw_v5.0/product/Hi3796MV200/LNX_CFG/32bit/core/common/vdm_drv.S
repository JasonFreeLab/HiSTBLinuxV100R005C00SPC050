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
	.file	"vdm_drv.c"
	.text
	.align	2
	.type	VDMDRV_AdjustErrRatio, %function
VDMDRV_AdjustErrRatio:
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
	ldr	r4, .L17
	mov	r7, r0, asl #3
	mov	r5, r0, asl #6
	rsb	ip, r7, r5
	subs	r3, r1, #0
	add	ip, r4, ip
	mov	r6, r2
	add	r2, ip, #8
	ldr	r8, [ip, #8]
	beq	.L7
	cmp	r3, #2
	bls	.L14
	ldr	r1, [r2, #4]
	sub	r3, fp, #36
	ldr	r2, [ip, #48]
	str	r0, [r3, #-12]!
	mov	r0, r3
	str	r1, [fp, #-44]
	str	r2, [fp, #-40]
	bl	PostPro_GetErrRatio
	ldr	r9, .L17+4
	cmp	r0, #0
	mov	ip, r0
	str	r0, [r6]
	bne	.L15
.L6:
	rsb	r5, r7, r5
	ldr	r3, [r9, r8, asl #2]
	add	r4, r4, r5
	add	r3, r3, #475136
	ldr	r1, [r4, #12]
	ldr	r2, [r3, #988]
	sub	r0, r1, #8
	cmp	r1, #5
	cmpne	r0, #1
	add	r2, r2, #1
	str	r2, [r3, #988]
	movls	r3, #0
	bhi	.L16
.L7:
	str	r3, [r6]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L14:
	mov	ip, #100
	mov	r2, r8
	str	ip, [r6]
	mov	r0, #1
	ldr	r1, .L17+8
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L16:
	ldr	r3, [r6]
	cmp	r3, #100
	movge	r3, #100
	bic	r3, r3, r3, asr #31
	b	.L7
.L15:
	ldr	r3, [r9, r8, asl #2]
	mov	r2, r8
	ldr	r1, .L17+12
	mov	r0, #1
	add	r3, r3, #475136
	ldr	r3, [r3, #988]
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L6
.L18:
	.align	2
.L17:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMDRV_AdjustErrRatio, .-VDMDRV_AdjustErrRatio
	.align	2
	.global	VDMDRV_Init
	.type	VDMDRV_Init, %function
VDMDRV_Init:
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
	ldr	r3, .L20
	mov	r6, r0, asl #6
	ldr	r4, .L20+4
	mov	r5, r0
	sub	r0, r6, r0, asl #3
	mov	r2, #56
	add	r0, r4, r0
	ldr	r3, [r3, #48]
	mov	r1, #0
	add	r4, r4, r5, lsl #2
	blx	r3
	ldr	r2, .L20+8
	mov	r3, #0
	str	r3, [r4, #56]
	add	r2, r2, r6
	str	r3, [r4, #60]
	str	r3, [r2, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L21:
	.align	2
.L20:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	VDMDRV_Init, .-VDMDRV_Init
	.align	2
	.global	VDMDRV_Reset
	.type	VDMDRV_Reset, %function
VDMDRV_Reset:
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
	ldr	r1, .L23
	mov	r3, r0, asl #6
	ldr	ip, .L23+4
	sub	r0, r3, r0, asl #3
	mov	r2, #56
	ldr	r3, [r1, #48]
	add	r0, ip, r0
	mov	r1, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L24:
	.align	2
.L23:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_Reset, .-VDMDRV_Reset
	.align	2
	.global	VDMDRV_SetPriority
	.type	VDMDRV_SetPriority, %function
VDMDRV_SetPriority:
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
	ldr	r5, .L37
	mov	r4, #0
	sub	r6, r0, #4
	mov	lr, r4
	mov	r7, r4
.L32:
	mov	ip, #0
	mov	r1, r6
	mov	r3, ip
.L27:
	ldr	r2, [r1, #4]!
	cmp	r2, ip
	movgt	lr, r3
	add	r3, r3, #1
	movgt	ip, r2
	cmp	r3, #32
	bne	.L27
	cmp	ip, #0
	ble	.L36
	add	r4, r4, #1
	str	lr, [r5, #4]!
	cmp	r4, #32
	str	r7, [r0, lr, asl #2]
	bne	.L32
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L36:
	cmp	r4, #31
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, .L37+4
	mov	r2, r4, asl #2
	mvn	r1, #0
.L30:
	add	r4, r4, #1
	add	r3, r0, r2
	cmp	r4, #32
	add	r2, r2, #4
	str	r1, [r3, #196]
	bne	.L30
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L38:
	.align	2
.L37:
	.word	.LANCHOR0+192
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_SetPriority, .-VDMDRV_SetPriority
	.align	2
	.global	VDMDRV_AdjustPriorityAfterDec
	.type	VDMDRV_AdjustPriorityAfterDec, %function
VDMDRV_AdjustPriorityAfterDec:
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
	ldr	r5, .L52
	add	ip, r5, #196
	ldr	r3, [r5, #196]
	cmp	r3, r0
	beq	.L48
	mov	r3, #1
	mov	r2, ip
	b	.L44
.L41:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L50
.L44:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	bne	.L41
	cmp	r3, #30
	bgt	.L51
.L40:
	add	r6, r3, #1
	mov	lr, r3
	mov	r6, r6, asl #2
.L45:
	ldr	r0, [ip, r6]
	add	r6, ip, r6
	cmp	r0, #0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r3, #2
	mov	r2, r2, asl #2
	b	.L43
.L47:
	ldr	r0, [ip, r2]
	add	r2, r2, #4
	cmp	r0, #0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L43:
	ldr	r4, [ip, lr, asl #2]
	add	r1, r5, r0, lsl #2
	add	r3, r3, #1
	ldr	r7, [r1, #68]
	add	r1, r5, r4, lsl #2
	ldr	r1, [r1, #68]
	cmp	r7, r1
	strge	r0, [ip, lr, asl #2]
	strge	r4, [r6]
	cmp	r3, #30
	add	r6, ip, r2
	mov	lr, r3
	ble	.L47
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L50:
	mov	r3, #0
	mov	r6, #4
	mov	lr, r3
	b	.L45
.L48:
	mov	r3, #0
	b	.L40
.L51:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L53:
	.align	2
.L52:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_AdjustPriorityAfterDec, .-VDMDRV_AdjustPriorityAfterDec
	.align	2
	.global	VDMDRV_PrepareSleep
	.type	VDMDRV_PrepareSleep, %function
VDMDRV_PrepareSleep:
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
	ldr	r1, .L58
	add	ip, r1, r0, lsl #2
	ldr	r3, [ip, #56]
	cmp	r3, #0
	bne	.L57
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #3
	ldr	r0, [r1, r0]
	cmp	r0, #0
	moveq	r3, #2
	movne	r0, r3
	movne	r3, #1
	str	r3, [ip, #56]
	ldmfd	sp, {fp, sp, pc}
.L57:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L59:
	.align	2
.L58:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_PrepareSleep, .-VDMDRV_PrepareSleep
	.align	2
	.global	VDMDRV_GetSleepStage
	.type	VDMDRV_GetSleepStage, %function
VDMDRV_GetSleepStage:
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
	ldr	r3, .L61
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #56]
	ldmfd	sp, {fp, sp, pc}
.L62:
	.align	2
.L61:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_GetSleepStage, .-VDMDRV_GetSleepStage
	.align	2
	.global	VDMDRV_ForceSleep
	.type	VDMDRV_ForceSleep, %function
VDMDRV_ForceSleep:
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
	ldr	r3, .L68
	add	r4, r3, r0, lsl #2
	ldr	r2, [r4, #56]
	cmp	r2, #2
	beq	.L64
	ldr	ip, .L68+4
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #3
	mov	r1, #0
	add	r0, r3, r0
	mov	r2, #56
	ldr	r3, [ip, #48]
	blx	r3
	mov	r3, #2
	str	r3, [r4, #56]
.L64:
	ldr	r1, .L68+8
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L69:
	.align	2
.L68:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	VDMDRV_ForceSleep, .-VDMDRV_ForceSleep
	.align	2
	.global	VDMDRV_ExitSleep
	.type	VDMDRV_ExitSleep, %function
VDMDRV_ExitSleep:
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
	ldr	r3, .L71
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #56]
	ldmfd	sp, {fp, sp, pc}
.L72:
	.align	2
.L71:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_ExitSleep, .-VDMDRV_ExitSleep
	.align	2
	.global	VDMDRV_StartRepair
	.type	VDMDRV_StartRepair, %function
VDMDRV_StartRepair:
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
	mov	r0, #8
	mov	r4, r1
	mov	r6, r2
	bl	VCTRL_RecordPosTime
	ldr	r3, .L76
	ldr	r3, [r3, #116]
	cmp	r3, #0
	beq	.L74
	mov	r1, r6
	mov	r0, r4
	blx	r3
.L75:
	mov	r3, r4, asl #6
	ldr	r2, .L76+4
	sub	r1, r3, r4, asl #3
	str	r5, [r2, r1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L74:
	mov	r0, r3
	mov	r2, #296
	ldr	r1, .L76+8
	bl	dprint_vfmw
	b	.L75
.L77:
	.align	2
.L76:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_StartRepair, .-VDMDRV_StartRepair
	.align	2
	.global	VDMDRV_StartDec
	.type	VDMDRV_StartDec, %function
VDMDRV_StartDec:
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
	mov	r0, #8
	mov	r5, r1
	bl	VCTRL_RecordPosTime
	ldr	r3, .L81
	ldr	r3, [r3, #120]
	cmp	r3, #0
	beq	.L79
	mov	r1, r5
	mov	r0, r4
	blx	r3
.L80:
	mov	r3, r4, asl #6
	ldr	r2, .L81+4
	sub	r0, r3, r4, asl #3
	mov	r3, #1
	str	r3, [r2, r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L79:
	mov	r0, r3
	movw	r2, #305
	ldr	r1, .L81+8
	bl	dprint_vfmw
	b	.L80
.L82:
	.align	2
.L81:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_StartDec, .-VDMDRV_StartDec
	.align	2
	.global	VDMDRV_IsChanDec
	.type	VDMDRV_IsChanDec, %function
VDMDRV_IsChanDec:
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
	ldr	r3, .L84
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #324]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L85:
	.align	2
.L84:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_IsChanDec, .-VDMDRV_IsChanDec
	.align	2
	.global	VDMDRV_SetChanIsDec
	.type	VDMDRV_SetChanIsDec, %function
VDMDRV_SetChanIsDec:
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
	ldr	r3, .L87
	add	r1, r1, #1
	add	r3, r3, r0, lsl #2
	str	r1, [r3, #324]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_AdjustPriorityAfterDec
.L88:
	.align	2
.L87:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_SetChanIsDec, .-VDMDRV_SetChanIsDec
	.align	2
	.global	VDMDRV_ClearChanIsDec
	.type	VDMDRV_ClearChanIsDec, %function
VDMDRV_ClearChanIsDec:
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
	ldr	r3, .L90
	add	r0, r0, #64
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #68]
	ldmfd	sp, {fp, sp, pc}
.L91:
	.align	2
.L90:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_ClearChanIsDec, .-VDMDRV_ClearChanIsDec
	.align	2
	.global	VDMDRV_ParamInit
	.type	VDMDRV_ParamInit, %function
VDMDRV_ParamInit:
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
	ldr	r3, .L99
	mov	r0, #1
	add	r1, r3, #128
.L94:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	strne	r0, [r2, #16]
	cmp	r3, r1
	bne	.L94
	ldmfd	sp, {fp, sp, pc}
.L100:
	.align	2
.L99:
	.word	s_pstVfmwChan-4
	UNWIND(.fnend)
	.size	VDMDRV_ParamInit, .-VDMDRV_ParamInit
	.align	2
	.global	VDMDRV_ChnDecReady
	.type	VDMDRV_ChnDecReady, %function
VDMDRV_ChnDecReady:
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
	mov	r0, r1
	mov	r4, r1
	mov	r6, r2
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L105
	ldr	r3, .L108
	add	r3, r3, r4, lsl #2
	ldr	r5, [r3, #324]
	cmp	r5, #0
	bne	.L106
	str	r5, [r6]
	mov	r0, r4
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	str	r0, [r6]
	beq	.L107
.L103:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L105:
	mov	r3, r4
	ldr	r2, .L108+4
	ldr	r1, .L108+8
	mov	r5, #1
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L106:
	mov	r2, r4
	ldr	r1, .L108+12
	mov	r5, #1
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L107:
	mov	r2, r4
	ldr	r1, .L108+16
	mov	r0, #22
	mov	r5, #1
	bl	dprint_vfmw
	b	.L103
.L109:
	.align	2
.L108:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	.LC4
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	VDMDRV_ChnDecReady, .-VDMDRV_ChnDecReady
	.align	2
	.global	PostPro_CopyYuvByProtocol
	.type	PostPro_CopyYuvByProtocol, %function
PostPro_CopyYuvByProtocol:
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
	sub	r3, r3, #1
	cmp	r3, #11
	ldrls	pc, [pc, r3, asl #2]
	b	.L111
.L113:
	.word	.L112
	.word	.L114
	.word	.L111
	.word	.L111
	.word	.L111
	.word	.L111
	.word	.L111
	.word	.L111
	.word	.L111
	.word	.L115
	.word	.L115
	.word	.L115
.L115:
	ldr	r0, [r0]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PostPro_CopyYuv_Vp6
.L114:
	ldr	r0, [r0]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PostPro_CopyYuv_Mpeg4
.L112:
	ldr	r0, [r0]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PostPro_CopyYuv_Vc1
.L111:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_CopyYuvByProtocol, .-PostPro_CopyYuvByProtocol
	.align	2
	.global	VDMDRV_GetMb0QpInCurrPic
	.type	VDMDRV_GetMb0QpInCurrPic, %function
VDMDRV_GetMb0QpInCurrPic:
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
	ldr	r2, .L117
	mov	r3, #180
	mla	r0, r3, r0, r2
	ldr	r0, [r0, #460]
	and	r0, r0, #31
	ldmfd	sp, {fp, sp, pc}
.L118:
	.align	2
.L117:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_GetMb0QpInCurrPic, .-VDMDRV_GetMb0QpInCurrPic
	.align	2
	.global	VDMDRV_GetSwitchRounding
	.type	VDMDRV_GetSwitchRounding, %function
VDMDRV_GetSwitchRounding:
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
	ldr	r2, .L120
	mov	r3, #180
	mla	r0, r3, r0, r2
	ldr	r0, [r0, #464]
	and	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L121:
	.align	2
.L120:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_GetSwitchRounding, .-VDMDRV_GetSwitchRounding
	.align	2
	.global	VDMDRV_MMUIntServeProc
	.type	VDMDRV_MMUIntServeProc, %function
VDMDRV_MMUIntServeProc:
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
	ldr	r7, .L143
	ldr	r4, .L143+4
	mov	r5, r0
	mov	r0, #0
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r3, [r4, #104]
	cmp	r3, #0
	beq	.L128
	mov	r1, r5
	mov	r0, #5
	blx	r3
	ldr	r3, [r4, #104]
	cmp	r3, #0
	mov	r8, r0
	beq	.L128
	mov	r1, r5
	mov	r0, #6
	blx	r3
	ldr	ip, [r4, #104]
	and	r9, r8, #7
	cmp	ip, #0
	moveq	r6, ip
	mov	r10, r0
	beq	.L123
	mov	r1, r5
	mov	r0, #7
	blx	ip
	mov	r6, r0
.L123:
	cmp	r9, #0
	beq	.L128
	cmp	r10, #0
	bne	.L141
	cmp	r6, #0
	bne	.L142
.L128:
	ldr	r3, [r4, #92]
	cmp	r3, #0
	beq	.L129
	mov	r0, r5
	blx	r3
.L130:
	ldr	r3, [r7, #16]
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L129:
	mov	r0, r3
	movw	r2, #1317
	ldr	r1, .L143+8
	bl	dprint_vfmw
	b	.L130
.L142:
	mov	r3, r6
	mov	r2, r8
	ldr	r1, .L143+12
	mov	r0, #32
	bl	dprint_vfmw
	b	.L128
.L141:
	mov	r3, r10
	mov	r2, r8
	ldr	r1, .L143+16
	mov	r0, #32
	bl	dprint_vfmw
	cmp	r6, #0
	beq	.L128
	b	.L142
.L144:
	.align	2
.L143:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LC3
	.word	.LC8
	.word	.LC7
	UNWIND(.fnend)
	.size	VDMDRV_MMUIntServeProc, .-VDMDRV_MMUIntServeProc
	.align	2
	.global	VDMDRV_IsVdmInISR
	.type	VDMDRV_IsVdmInISR, %function
VDMDRV_IsVdmInISR:
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
	.size	VDMDRV_IsVdmInISR, .-VDMDRV_IsVdmInISR
	.align	2
	.global	VDMDRV_SetStateIdle
	.type	VDMDRV_SetStateIdle, %function
VDMDRV_SetStateIdle:
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
	ldr	r2, .L147
	mov	r3, r0, asl #6
	sub	r0, r3, r0, asl #3
	mov	r1, #0
	str	r1, [r2, r0]
	ldmfd	sp, {fp, sp, pc}
.L148:
	.align	2
.L147:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_SetStateIdle, .-VDMDRV_SetStateIdle
	.align	2
	.global	VDMDRV_IsVdmIdle
	.type	VDMDRV_IsVdmIdle, %function
VDMDRV_IsVdmIdle:
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
	ldr	r2, .L150
	mov	r3, r0, asl #6
	sub	r0, r3, r0, asl #3
	ldr	r0, [r2, r0]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L151:
	.align	2
.L150:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_IsVdmIdle, .-VDMDRV_IsVdmIdle
	.align	2
	.global	VDMDRV_GetCurrChanID
	.type	VDMDRV_GetCurrChanID, %function
VDMDRV_GetCurrChanID:
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
	ldr	r3, .L153
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #3
	add	r0, r3, r0
	ldr	r0, [r0, #8]
	ldmfd	sp, {fp, sp, pc}
.L154:
	.align	2
.L153:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_GetCurrChanID, .-VDMDRV_GetCurrChanID
	.align	2
	.global	VDMDRV_WaitVdmReadyIfNoIsr
	.type	VDMDRV_WaitVdmReadyIfNoIsr, %function
VDMDRV_WaitVdmReadyIfNoIsr:
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
	ldr	r6, .L164
	mov	r5, r0
	mov	r4, #0
	b	.L157
.L159:
	add	r4, r4, #1
	cmp	r4, #400
	beq	.L158
.L157:
	ldr	r3, [r6, #128]
	mov	r0, r5
	cmp	r3, #0
	beq	.L159
	blx	r3
	cmp	r0, #0
	beq	.L159
.L158:
	cmp	r4, #400
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L165:
	.align	2
.L164:
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	VDMDRV_WaitVdmReadyIfNoIsr, .-VDMDRV_WaitVdmReadyIfNoIsr
	.align	2
	.global	VDMDRV_AvsFirstFldNeedRepair
	.type	VDMDRV_AvsFirstFldNeedRepair, %function
VDMDRV_AvsFirstFldNeedRepair:
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
	cmp	r0, #6
	beq	.L170
.L169:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L170:
	ldrb	r3, [r1, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L169
	ldr	r3, .L171
	mov	r1, #1744
	mla	r2, r1, r2, r3
	ldr	r3, [r2, #676]
	cmp	r3, #0
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L172:
	.align	2
.L171:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_AvsFirstFldNeedRepair, .-VDMDRV_AvsFirstFldNeedRepair
	.align	2
	.global	VDMDRV_AvsSecondFldNeedRepair
	.type	VDMDRV_AvsSecondFldNeedRepair, %function
VDMDRV_AvsSecondFldNeedRepair:
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
	cmp	r0, #6
	beq	.L177
.L176:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L177:
	ldrb	r3, [r1, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L176
	ldr	r3, .L178
	mov	r1, #1744
	mla	r2, r1, r2, r3
	ldr	r3, [r2, #916]
	cmp	r3, #0
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L179:
	.align	2
.L178:
	.word	.LANCHOR0+632
	UNWIND(.fnend)
	.size	VDMDRV_AvsSecondFldNeedRepair, .-VDMDRV_AvsSecondFldNeedRepair
	.align	2
	.global	VDMDRV_IsMpeg4NvopCopy
	.type	VDMDRV_IsMpeg4NvopCopy, %function
VDMDRV_IsMpeg4NvopCopy:
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
	subs	r4, r1, #0
	beq	.L184
	cmp	r0, #2
	ldreqb	r0, [r4, #158]	@ zero_extendqisi2
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L184:
	ldr	r1, .L185
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L186:
	.align	2
.L185:
	.word	.LC9
	UNWIND(.fnend)
	.size	VDMDRV_IsMpeg4NvopCopy, .-VDMDRV_IsMpeg4NvopCopy
	.align	2
	.global	VDMDRV_IsVc1SkpicCopy
	.type	VDMDRV_IsVc1SkpicCopy, %function
VDMDRV_IsVc1SkpicCopy:
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
	subs	r4, r1, #0
	beq	.L191
	cmp	r0, #1
	ldreqb	r0, [r4, #1]	@ zero_extendqisi2
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L191:
	ldr	r1, .L192
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L193:
	.align	2
.L192:
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMDRV_IsVc1SkpicCopy, .-VDMDRV_IsVc1SkpicCopy
	.align	2
	.global	VDMDRV_IsVp6NvopCopy
	.type	VDMDRV_IsVp6NvopCopy, %function
VDMDRV_IsVp6NvopCopy:
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
	subs	r4, r1, #0
	beq	.L198
	sub	r0, r0, #10
	cmp	r0, #2
	ldrlsb	r0, [r4, #1]	@ zero_extendqisi2
	subls	r0, r0, #1
	clzls	r0, r0
	movls	r0, r0, lsr #5
	movhi	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L198:
	ldr	r1, .L199
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L200:
	.align	2
.L199:
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMDRV_IsVp6NvopCopy, .-VDMDRV_IsVp6NvopCopy
	.align	2
	.global	VDMDRV_IsVp9RptFrmCopy
	.type	VDMDRV_IsVp9RptFrmCopy, %function
VDMDRV_IsVp9RptFrmCopy:
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
	subs	r4, r1, #0
	beq	.L205
	cmp	r0, #17
	addeq	r0, r4, #262144
	ldreqb	r0, [r0, #1028]	@ zero_extendqisi2
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L205:
	ldr	r1, .L206
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L207:
	.align	2
.L206:
	.word	.LC12
	UNWIND(.fnend)
	.size	VDMDRV_IsVp9RptFrmCopy, .-VDMDRV_IsVp9RptFrmCopy
	.align	2
	.global	VDMDRV_IsCopy
	.type	VDMDRV_IsCopy, %function
VDMDRV_IsCopy:
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
	subs	r4, r1, #0
	beq	.L216
	sub	r0, r0, #1
	cmp	r0, #11
	ldrls	pc, [pc, r0, asl #2]
	b	.L215
.L212:
	.word	.L214
	.word	.L213
	.word	.L215
	.word	.L215
	.word	.L215
	.word	.L215
	.word	.L215
	.word	.L215
	.word	.L215
	.word	.L214
	.word	.L214
	.word	.L214
.L214:
	ldrb	r0, [r4, #1]	@ zero_extendqisi2
	sub	r0, r0, #1
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L213:
	ldrb	r0, [r4, #158]	@ zero_extendqisi2
	sub	r0, r0, #1
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L215:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L216:
	ldr	r1, .L217
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L218:
	.align	2
.L217:
	.word	.LC13
	UNWIND(.fnend)
	.size	VDMDRV_IsCopy, .-VDMDRV_IsCopy
	.align	2
	.global	VDMDRV_DoBeforeDec
	.type	VDMDRV_DoBeforeDec, %function
VDMDRV_DoBeforeDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 216
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #228)
	sub	sp, sp, #228
	ldr	r3, .L238
	mov	r5, r0
	mov	r4, r1
	mov	r6, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [fp, #-252]
	beq	.L220
	ldr	r3, .L238+4
	sub	r0, fp, #232
	mov	r2, #188
	mov	r1, #0
	str	r0, [fp, #-252]
	ldr	r3, [r3, #48]
	blx	r3
.L220:
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L235
	mov	r3, r5, asl #3
	mov	r0, r4
	str	r3, [fp, #-248]
	mov	r7, r5, asl #6
	mov	r8, r3
	bl	VCTRL_GetVidStd
	ldr	r3, .L238+8
	rsb	r8, r8, r7
	ldr	r9, .L238+12
	ldr	r3, [r3]
	add	r8, r9, r8
	add	r8, r8, #8
	cmp	r3, #0
	str	r0, [r8, #4]
	mov	r2, r0
	beq	.L223
	ldr	r1, [r6]
	sub	r0, fp, #244
	str	r4, [fp, #-244]
	str	r2, [fp, #-240]
	str	r1, [fp, #-236]
	blx	r3
	cmp	r0, #1
	mov	r10, r0
	beq	.L222
	ldr	r2, [r8, #4]
.L223:
	ldr	r3, [fp, #-248]
	mov	r0, r2
	ldr	r1, [r6]
	rsb	r8, r3, r7
	bl	VDMDRV_IsCopy
	add	r8, r9, r8
	add	r3, r8, #4
	str	r3, [fp, #-256]
	subs	r10, r0, #0
	bne	.L236
	ldr	r0, [r8, #12]
	ldr	r1, [r6]
	bl	VCTRL_IsSedOnlyMode
	cmp	r0, #0
	streq	r10, [r8, #52]
	movne	r3, #1
	strne	r3, [r8, #52]
	ldr	r3, .L238+16
	ldr	r8, [r3, #124]
	cmp	r8, #0
	beq	.L229
	ldr	r3, [fp, #-248]
	mov	r2, r5
	ldr	r1, [r6]
	rsb	r3, r3, r7
	add	r6, r9, r3
	ldr	r3, [fp, #-252]
	ldr	r0, [r6, #12]
	blx	r8
	subs	r8, r0, #0
	beq	.L237
.L229:
	ldr	r1, .L238+20
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r2, [fp, #-256]
	mov	r1, #2
	mov	r0, r5
	bl	VDMDRV_AdjustErrRatio
	ldr	r3, [fp, #-248]
	mov	r0, r4
	mov	r2, #0
	rsb	r7, r3, r7
	mov	r3, r5
	add	r7, r9, r7
	add	r4, r4, #64
	ldr	r1, [r7, #4]
	add	r9, r9, r4, lsl #2
	bl	VCTRL_VdmPostProc
	ldr	r3, .L238+4
	mov	r0, r7
	mov	r2, #56
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	mov	r3, #0
	str	r3, [r9, #68]
.L222:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L236:
	mov	r0, r6
	ldr	r3, [r8, #12]
	ldr	r2, [fp, #-252]
	mov	r1, r5
	bl	PostPro_CopyYuvByProtocol
	subs	r10, r0, #0
	movne	r10, #0
	bne	.L222
	ldr	r2, [fp, #-256]
	mov	r1, r10
	mov	r0, r5
	bl	VDMDRV_AdjustErrRatio
	ldr	r2, [fp, #-252]
	mov	r1, r5
	mov	r0, #2
	bl	VDMDRV_StartRepair
	ldr	r3, .L238+4
	add	r5, r5, #1
	ldr	r3, [r3]
	blx	r3
	ldr	r3, .L238+24
	ldr	r1, .L238+12
	add	r7, r3, r7
	add	r1, r1, r4, lsl #2
	str	r5, [r1, #324]
	mov	r2, r0
	mov	r0, r4
	str	r2, [r8, #20]
	str	r2, [r7, #4]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r2, .L238+28
	mov	r0, r4
	movw	r1, #535
	ldr	r3, .L238+32
	add	r2, r2, r4, lsl #2
	str	r1, [sp]
	mov	r1, #7
	bl	RecordPOS
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L237:
	ldr	r1, [fp, #-252]
	mov	r0, r5
	bl	VDMDRV_StartDec
	ldr	r3, .L238+4
	add	r5, r5, #1
	mov	r10, r8
	ldr	r3, [r3]
	blx	r3
	ldr	r3, .L238+24
	ldr	r1, .L238+12
	add	r7, r3, r7
	add	r1, r1, r4, lsl #2
	str	r5, [r1, #324]
	mov	r2, r0
	mov	r0, r4
	str	r2, [r6, #20]
	str	r2, [r7, #4]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r2, .L238+28
	mov	r0, r4
	movw	r1, #569
	ldr	r3, .L238+32
	add	r2, r2, r4, lsl #2
	str	r1, [sp]
	mov	r1, #5
	bl	RecordPOS
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L235:
	mov	r2, r4
	ldr	r1, .L238+36
	mov	r0, #22
	mov	r10, #1
	bl	dprint_vfmw
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L239:
	.align	2
.L238:
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	.word	AcceleratorCharacter
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	.word	.LC15
	.word	g_VfmwGlobalStat
	.word	.LANCHOR0+2376
	.word	.LANCHOR1+20
	.word	.LC14
	UNWIND(.fnend)
	.size	VDMDRV_DoBeforeDec, .-VDMDRV_DoBeforeDec
	.align	2
	.global	VDMDRV_ActivateVDH
	.type	VDMDRV_ActivateVDH, %function
VDMDRV_ActivateVDH:
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
	ldr	r9, .L246
	mov	r5, r0, asl #6
	ldr	r6, .L246+4
	sub	r5, r5, r0, asl #3
	mov	r8, r0
	mov	r0, #5
	ldr	r3, [r9, #12]
	add	r7, r5, #48
	blx	r3
	ldr	r3, [r6, #196]
	add	r7, r6, r7
	cmp	r3, #0
	blt	.L241
	add	r5, r6, r5
	add	r4, r6, #196
	add	r6, r6, #320
	b	.L242
.L245:
	cmp	r4, r6
	beq	.L241
	ldr	r3, [r4, #4]!
	cmp	r3, #0
	blt	.L241
.L242:
	mov	r1, r3
	mov	r2, r7
	mov	r0, r8
	str	r3, [r5, #8]
	bl	VDMDRV_ChnDecReady
	cmp	r0, #0
	bne	.L245
	mov	r2, r7
	ldr	r1, [r5, #8]
	mov	r0, r8
	bl	VDMDRV_DoBeforeDec
	cmp	r0, #0
	bne	.L245
.L241:
	ldr	r3, [r9, #16]
	mov	r0, #5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L247:
	.align	2
.L246:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_ActivateVDH, .-VDMDRV_ActivateVDH
	.align	2
	.global	VDMDRV_AfterDec
	.type	VDMDRV_AfterDec, %function
VDMDRV_AfterDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 360
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #372)
	sub	sp, sp, #372
	ldr	r8, .L300
	str	r1, [fp, #-392]
	mov	r7, r0
	mov	r2, #148
	mov	r1, #0
	ldr	r3, [r8, #48]
	sub	r0, fp, #380
	blx	r3
	ldr	r3, .L300+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L249
	sub	r4, fp, #232
	ldr	r3, [r8, #48]
	mov	r2, #188
	mov	r1, #0
	mov	r0, r4
	blx	r3
	str	r4, [fp, #-240]
.L249:
	mov	r3, r7, asl #3
	ldr	r5, .L300+8
	mov	r6, r7, asl #6
	str	r3, [fp, #-396]
	rsb	r10, r3, r6
	mov	r2, #136
	add	r4, r5, r10
	ldr	r3, [r8, #48]
	mov	r1, #0
	sub	r0, fp, #376
	blx	r3
	ldr	r2, [r4, #8]
	add	ip, r4, #8
	str	ip, [fp, #-400]
	ldr	ip, .L300+12
	add	r9, r4, #24
	ldr	r1, [r4, #4]
	mov	r0, #2
	ldrb	lr, [fp, #-392]	@ zero_extendqisi2
	ldr	ip, [ip, r2, asl #2]
	ldr	r3, [r9, #4]
	ldr	r2, [r5, r10]
	ldr	ip, [ip, #1168]
	str	r1, [sp]
	ldr	r1, .L300+16
	strb	lr, [fp, #-236]
	str	ip, [fp, #-380]
	bl	dprint_vfmw
	ldr	r3, [r5, r10]
	ldr	r10, .L300
	cmp	r3, #2
	beq	.L251
	cmp	r3, #3
	beq	.L252
	cmp	r3, #1
	beq	.L290
	ldr	r1, [fp, #-392]
	mov	r0, #0
	ldr	r2, [r4, #8]
	str	r1, [sp]
	ldr	r1, .L300+20
	bl	dprint_vfmw
	ldr	r3, [r4, #8]
	mov	r2, #0
	add	r3, r3, #64
	add	r5, r5, r3, lsl #2
	str	r2, [r5, #68]
.L248:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L290:
	ldr	r3, [r9, #4]
	add	r10, r4, #4
	cmp	r3, #1
	beq	.L291
	mov	r2, r10
	mov	r1, #3
	mov	r0, r7
	bl	VDMDRV_AdjustErrRatio
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L255
	ldr	r2, .L300+24
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L255
	sub	r2, fp, #44
	ldr	r0, [r4, #8]
	mov	r1, #114
	str	r3, [r2, #-340]!
	mov	r3, #4
	blx	ip
.L255:
	ldr	r3, [fp, #-380]
	cmp	r3, #1
	beq	.L292
.L256:
	ldr	r3, [fp, #-396]
	ldr	r2, .L300+12
	rsb	r4, r3, r6
	ldr	r3, .L300+8
	add	r4, r5, r4
	add	r9, r4, #8
	ldr	r0, [r4, #8]
	ldr	r2, [r2, r0, asl #2]
	add	r2, r2, #475136
	add	r2, r2, #944
	ldrsb	r2, [r2]
	cmp	r2, #0
	ldreq	r1, [r4, #4]
	bne	.L293
.L267:
	ldr	r3, [fp, #-380]
	cmp	r3, #1
	bne	.L259
	ldr	r3, [fp, #-396]
	ldr	r4, .L300+8
	rsb	r6, r3, r6
	add	r5, r5, r6
	ldr	r3, [r5, #44]
	cmp	r3, #2
	beq	.L294
	sub	r2, fp, #376
	mov	r3, r7
	bl	VCTRL_VdmPostProc
	ldr	r0, [r5, #8]
	bl	VCTRL_ClearDecparam
	ldr	r3, [r5, #8]
	mov	ip, #0
	ldr	r6, [r8, #48]
	add	r3, r3, #64
	mov	r0, r5
	mov	r1, ip
	mov	r2, #56
	add	r4, r4, r3, lsl #2
	str	ip, [r4, #68]
	blx	r6
	mov	r0, r7
	bl	VDMDRV_ActivateVDH
	b	.L248
.L252:
	sub	r2, fp, #376
	mov	r3, r7
	ldr	r1, [r4, #4]
	mov	r6, #0
	ldr	r0, [r4, #8]
	str	r6, [r9, #4]
	bl	VCTRL_VdmPostProc
	ldr	r0, [r4, #8]
	bl	VCTRL_ClearDecparam
	ldr	r3, [r4, #8]
	ldr	ip, [r10, #48]
	mov	r1, r6
	add	r3, r3, #64
	mov	r2, #56
	mov	r0, r4
	add	r5, r5, r3, lsl #2
	str	r6, [r5, #68]
	blx	ip
	mov	r0, r7
	bl	VDMDRV_ActivateVDH
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L251:
	ldr	r3, [fp, #-400]
	add	r10, r4, #4
	ldr	r1, [r4, #48]
	ldr	r0, [r3, #4]
	mov	r3, #0
	str	r3, [r9, #4]
	cmp	r0, #6
	beq	.L295
.L264:
	bl	VDMDRV_IsCopy
	subs	r4, r0, #0
	bne	.L296
	ldr	r3, [fp, #-396]
	sub	r2, fp, #376
	rsb	r6, r3, r6
	mov	r3, r7
	add	r6, r5, r6
	ldr	r1, [r6, #4]
	ldr	r0, [r6, #8]
	bl	VCTRL_VdmPostProc
	ldr	r0, [r6, #8]
	bl	VCTRL_ClearDecparam
	ldr	r3, [r6, #8]
	ldr	ip, [r8, #48]
	mov	r0, r6
	mov	r1, r4
	mov	r2, #56
	add	r5, r5, r3, lsl #2
	str	r4, [r5, #324]
	blx	ip
	mov	r0, r7
	bl	VDMDRV_ActivateVDH
	b	.L248
.L291:
	str	r3, [fp, #-392]
	mov	r2, r7
	ldr	r3, [fp, #-400]
	ldr	r1, [r4, #48]
	ldr	r0, [r3, #4]
	bl	PostPro_SetFullRepair
	ldr	r3, [fp, #-392]
	mov	r2, r10
	mov	r0, r7
	mov	r1, r3
	bl	VDMDRV_AdjustErrRatio
	mov	r3, #0
	mov	r0, r3
	ldrb	r2, [fp, #-236]	@ zero_extendqisi2
	ldr	r1, .L300+28
	str	r3, [r9, #4]
	bl	dprint_vfmw
	b	.L255
.L295:
	ldrb	r2, [r1, #17]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L264
	mov	r3, #1744
	mla	r3, r3, r7, r5
	ldr	r3, [r3, #1548]
	cmp	r3, #0
	ble	.L264
	ldr	r3, .L300+32
	ldr	ip, [r3, #136]
	cmp	ip, #0
	beq	.L266
	ldr	lr, [fp, #-240]
	mov	r3, r7
	str	lr, [sp]
	blx	ip
	cmp	r0, #0
	bne	.L266
	mov	r1, r7
	ldr	r2, [fp, #-240]
	mov	r0, #3
	bl	VDMDRV_StartRepair
	ldr	r2, .L300+36
	ldr	r0, [r4, #8]
	movw	ip, #765
	ldr	r3, .L300+40
	mov	r1, #7
	add	r2, r6, r2
	str	ip, [sp]
	bl	RecordPOS
	b	.L248
.L293:
	ldr	r1, [r4, #48]
	ldr	r0, [r9, #4]
	str	r3, [fp, #-392]
	bl	PostPro_GetRepairStratage
	ldr	r1, [r4, #4]
	ldr	r3, [fp, #-392]
	cmp	r1, #0
	cmpne	r0, #1
	moveq	r2, #1
	movne	r2, #0
	beq	.L297
	ldr	r0, [r9, #4]
	ldr	r1, [r4, #48]
	cmp	r0, #6
	beq	.L298
.L272:
	mov	r4, #2
.L262:
	ldr	r3, .L300+32
	ldr	ip, [r3, #136]
	cmp	ip, #0
	beq	.L266
	ldr	lr, [fp, #-240]
	mov	r3, r7
	str	lr, [sp]
	blx	ip
	cmp	r0, #0
	beq	.L299
.L266:
	ldr	r3, [fp, #-396]
	mov	r2, r10
	mov	r0, r7
	mov	r1, #2
	rsb	r6, r3, r6
	bl	VDMDRV_AdjustErrRatio
	add	r4, r5, r6
	mov	r3, r7
	sub	r2, fp, #376
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	VCTRL_VdmPostProc
	ldr	r0, [r4, #8]
	bl	VCTRL_ClearDecparam
	ldr	r3, [r4, #8]
	mov	r2, #0
	str	r2, [r5, r6]
	add	r3, r3, #64
	add	r5, r5, r3, lsl #2
	str	r2, [r5, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L259:
	mov	r3, r7
	sub	r2, fp, #376
	bl	VCTRL_VdmPostProc
	ldr	r3, [fp, #-396]
	rsb	r6, r3, r6
	add	r6, r5, r6
.L288:
	ldr	r0, [r6, #8]
	bl	VCTRL_ClearDecparam
	ldr	r3, [r6, #8]
	mov	ip, #0
	mov	r2, #56
	add	r3, r3, #64
	mov	r1, ip
	ldr	r4, [r8, #48]
	mov	r0, r6
	add	r5, r5, r3, lsl #2
	str	ip, [r5, #68]
	blx	r4
	mov	r0, r7
	bl	VDMDRV_ActivateVDH
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L296:
	mov	r2, r10
	mov	r0, r7
	mov	r1, #0
	bl	VDMDRV_AdjustErrRatio
	ldr	r3, [fp, #-396]
	sub	r2, fp, #376
	rsb	r6, r3, r6
	mov	r3, r7
	add	r6, r5, r6
	ldr	r1, [r6, #4]
	ldr	r0, [r6, #8]
	bl	VCTRL_VdmPostProc
	b	.L288
.L292:
	mov	r2, r10
	mov	r1, #0
	mov	r0, r7
	bl	VDMDRV_AdjustErrRatio
	b	.L256
.L294:
	mov	r3, r7
	sub	r2, fp, #376
	bl	VCTRL_VdmPostProc
	b	.L248
.L298:
	ldrb	ip, [r1, #17]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L272
	mov	r2, #1744
	mla	r3, r2, r7, r3
	ldr	r3, [r3, #1548]
	cmp	r3, #0
	movgt	r2, #1
	movle	r2, #0
	movle	r4, #2
	movgt	r4, #3
	b	.L262
.L299:
	mov	r1, r7
	mov	r0, r4
	ldr	r2, [fp, #-240]
	bl	VDMDRV_StartRepair
	ldr	r3, [fp, #-396]
	ldr	r2, .L300+36
	movw	r1, #734
	rsb	r3, r3, r6
	add	r5, r5, r3
	add	r2, r6, r2
	ldr	r3, .L300+44
	ldr	r0, [r5, #8]
	str	r1, [sp]
	mov	r1, #7
	bl	RecordPOS
	b	.L248
.L297:
	ldr	r0, [r4, #8]
	b	.L267
.L301:
	.align	2
.L300:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HalDisable
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC16
	.word	.LC18
	.word	g_event_report
	.word	.LC17
	.word	g_vdm_hal_fun_ptr
	.word	g_VfmwGlobalStat+4
	.word	.LANCHOR1+72
	.word	.LANCHOR1+40
	UNWIND(.fnend)
	.size	VDMDRV_AfterDec, .-VDMDRV_AfterDec
	.align	2
	.global	VDMDRV_CheckDevice
	.type	VDMDRV_CheckDevice, %function
VDMDRV_CheckDevice:
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
	ldr	r4, .L337
	mov	r7, r0, asl #3
	mov	r6, r0, asl #6
	mov	r5, r0
	rsb	r8, r7, r6
	add	r9, r4, r8
	ldr	r0, [r9, #8]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L333
.L303:
	rsb	r3, r7, r6
	add	r8, r4, r3
	ldr	r3, [r4, r3]
	cmp	r3, #0
	bne	.L334
.L304:
	add	r4, r4, r5, lsl #2
	ldr	r0, [r4, #56]
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	cmp	r0, #1
	beq	.L335
.L309:
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L334:
	ldr	r3, .L337+4
	ldr	r3, [r3]
	blx	r3
	add	r2, r8, #16
	ldr	r3, [r2, #4]
	str	r0, [r8, #24]
	cmp	r0, r3
	bcc	.L307
	clz	r9, r3
	rsb	r3, r3, r0
	mov	r9, r9, lsr #5
	orrs	r9, r9, r3, lsr #31
	bne	.L307
	cmp	r3, #1000
	bls	.L309
	ldr	r2, [r8, #8]
	mov	r0, #1
	ldr	r1, .L337+8
	bl	dprint_vfmw
	ldr	r3, .L337+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L312
	ldr	r0, [r8, #8]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #101
	blx	ip
.L312:
	ldr	r3, .L337+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L313
	mov	r1, r5
	mov	r0, #1
	bl	VDH_Reset_Module
.L314:
	rsb	r3, r7, r6
	mov	r1, #1
	add	r3, r4, r3
	add	r2, r3, #32
	str	r1, [r3, #28]
	ldr	r3, [r3, #36]
	cmp	r3, r1
	moveq	r3, #0
	streq	r3, [r2, #4]
	beq	.L317
	mov	r0, r5
	mov	r1, #0
	bl	VDMDRV_AfterDec
.L317:
	rsb	r6, r7, r6
	mov	r2, #0
	add	r3, r4, r6
	mov	r0, r2
	add	r1, r3, #24
	str	r2, [r4, r6]
	ldr	r3, [r3, #8]
	str	r2, [r1, #4]
	add	r3, r3, #64
	add	r4, r4, r3, lsl #2
	str	r2, [r4, #68]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L307:
	str	r0, [r2, #4]
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L335:
	mov	r3, #2
	str	r3, [r4, #56]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L333:
	ldr	r3, [r4, r8]
	cmp	r3, #0
	beq	.L304
	ldr	r2, .L337+20
	ldr	r2, [r2, #132]
	cmp	r2, #0
	beq	.L305
	mov	r0, r5
	blx	r2
	ldr	r3, [r4, r8]
	cmp	r0, #0
	bne	.L336
.L305:
	rsb	r10, r7, r6
	ldr	r1, .L337+24
	add	r9, r4, r10
	mov	r0, #1
	mov	r8, #0
	ldr	r2, [r9, #8]
	bl	dprint_vfmw
	ldr	r2, [r4, r10]
	movw	r1, #903
	ldr	r0, .L337+28
	str	r8, [r9, #36]
	bl	DBG_AddTrace
	ldr	r3, .L337+4
	mov	r0, r9
	mov	r1, r8
	mov	r2, #56
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r9, #8]
	add	r3, r3, #64
	add	r3, r4, r3, lsl #2
	str	r8, [r3, #68]
	b	.L303
.L313:
	ldr	r3, .L337+20
	ldr	r3, [r3, #76]
	cmp	r3, #0
	beq	.L315
	mov	r0, r5
	blx	r3
	b	.L314
.L336:
	mov	r0, #1
	ldr	r2, [r9, #8]
	ldr	r1, .L337+32
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r9, #36]
	b	.L303
.L315:
	mov	r0, r3
	movw	r2, #935
	ldr	r1, .L337+36
	bl	dprint_vfmw
	b	.L314
.L338:
	.align	2
.L337:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	g_event_report
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC20
	.word	.LANCHOR1+104
	.word	.LC19
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_CheckDevice, .-VDMDRV_CheckDevice
	.align	2
	.global	VDMDRV_WakeUpVdm
	.type	VDMDRV_WakeUpVdm, %function
VDMDRV_WakeUpVdm:
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
	bl	VDMDRV_CheckDevice
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_ActivateVDH
	UNWIND(.fnend)
	.size	VDMDRV_WakeUpVdm, .-VDMDRV_WakeUpVdm
	.global	__aeabi_uidiv
	.align	2
	.global	VDMDRV_IsrProcess
	.type	VDMDRV_IsrProcess, %function
VDMDRV_IsrProcess:
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
	subs	r4, r0, #0
	ble	.L342
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L433
	ldr	r1, .L433+4
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L342:
	mov	r0, #9
	mov	r10, r4, asl #6
	bl	VCTRL_RecordPosTime
	mov	r3, r4, asl #3
	str	r3, [fp, #-48]
	mov	r0, #0
	mov	r5, r3
	ldr	r3, .L433+8
	ldr	r6, .L433+12
	ldr	r3, [r3, #12]
	blx	r3
	rsb	r3, r5, r10
	add	r3, r6, r3
	ldr	r3, [r3, #8]
	cmp	r3, #0
	blt	.L385
	ldr	r2, .L433+16
	ldr	r8, [r2, r3, asl #2]
	cmp	r8, #0
	streq	r8, [fp, #-52]
	ldrne	r3, [r8, #1168]
	strne	r3, [fp, #-52]
.L344:
	ldr	r7, .L433+20
	ldr	r5, [r7, #156]
	cmp	r5, #0
	beq	.L387
	mov	r1, r4
	mov	r0, #2
	blx	r5
	ldr	r5, [r7, #156]
	cmp	r5, #0
	mov	r8, r0
	beq	.L388
	mov	r1, r4
	mov	r0, #1
	blx	r5
	ldr	r9, [r7, #156]
	cmp	r9, #0
	mov	r5, r0
	beq	.L345
	mov	r1, r4
	mov	r0, #3
	blx	r9
	mov	r9, r0
.L345:
	ldr	r3, [r7, #160]
	cmp	r3, #0
	beq	.L346
	mov	r1, r4
	mov	r0, #2
	blx	r3
	cmp	r8, #1
	beq	.L347
	ldr	r3, [fp, #-52]
	cmp	r0, #1
	cmpeq	r3, #1
	beq	.L347
.L381:
	cmp	r8, #0
	beq	.L423
.L353:
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r10
	add	r6, r6, r3
	ldr	r0, [r6, #8]
	bl	VCTRL_InformVdmFree
	ldr	r3, .L433+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L354
	mov	r1, r4
	mov	r0, #1
	bl	VDH_Notify_ModuleIdle
.L354:
	ldr	r3, .L433+8
	mov	r0, #0
	ldr	r3, [r3, #16]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L423:
	cmp	r9, #1
	cmpeq	r5, #1
	beq	.L353
	ldr	r3, [r7, #132]
	cmp	r3, #0
	beq	.L352
	mov	r0, r4
	blx	r3
	cmp	r0, #0
	bne	.L353
.L352:
	ldr	r3, [r7, #156]
	cmp	r3, #0
	beq	.L351
	mov	r1, r4
	mov	r0, #1
	blx	r3
	cmp	r0, #0
	bne	.L353
.L351:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	rsb	r3, r3, r10
	str	r2, [r6, r3]
	b	.L353
.L346:
	cmp	r8, #1
	bne	.L381
.L347:
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r10
	add	r3, r6, r3
	ldr	r3, [r3, #8]
	cmp	r3, #0
	blt	.L357
	ldr	r2, .L433+16
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	beq	.L357
	ldr	r2, [r7, #160]
	ldr	r5, [r3, #1168]
	cmp	r2, #0
	moveq	r8, r2
	beq	.L358
	mov	r1, r4
	mov	r0, #1
	blx	r2
	mov	r8, r0
.L358:
	ldr	r3, [r7, #156]
	cmp	r3, #0
	beq	.L359
	mov	r1, r4
	mov	r0, #1
	blx	r3
	cmp	r5, #1
	beq	.L424
.L357:
	mov	r3, #1
	str	r3, [fp, #-52]
.L356:
	ldr	r3, [r7, #144]
	cmp	r3, #0
	beq	.L363
	mov	r0, r4
	blx	r3
.L364:
	ldr	r3, [r7, #88]
	cmp	r3, #0
	beq	.L365
	mov	r0, r4
	blx	r3
.L366:
	ldr	r3, [fp, #-48]
	movw	ip, #1245
	ldr	r2, .L433+28
	mov	r1, #6
	rsb	r0, r3, r10
	ldr	r3, .L433+32
	add	r0, r6, r0
	ldr	r7, .L433+36
	ldr	r0, [r0, #8]
	str	ip, [sp]
	add	r2, r2, r0, lsl #2
	bl	RecordPOS
	ldr	r3, .L433+8
	ldr	r3, [r3]
	blx	r3
	add	r1, r7, r10
	ldr	r2, [r1, #4]
	cmp	r2, #0
	beq	.L368
	ldr	r5, [r7, r4, asl #6]
	add	r9, r7, r10
	add	r3, r5, #49920
	ldr	lr, [r9, #32]
	add	r3, r3, #80
	cmp	r2, r3
	rsb	r3, r2, r0
	strhi	r2, [r7, r4, asl #6]
	ldrls	ip, [r1, #8]
	mov	r1, #180
	mla	r1, r1, r4, r6
	movhi	r5, r2
	rsb	r5, r5, r0
	movhi	ip, #0
	ldr	r2, [r9, #28]
	cmp	r5, #1000
	add	r3, r3, ip
	str	r3, [r9, #8]
	add	r2, r2, #1
	str	r2, [r9, #28]
	ldr	r8, [r1, #476]
	mov	r1, #0
	str	r1, [r9, #4]
	ldr	r1, .L433+12
	add	r8, lr, r8, lsr #10
	str	r8, [r9, #32]
	bcc	.L368
	ldr	r0, [fp, #-48]
	rsb	r0, r0, r10
	add	r1, r1, r0
	ldr	r1, [r1, #16]
	cmp	r1, #0
	ldreq	r0, [r9, #12]
	bne	.L425
.L373:
	mov	ip, #1000
	mov	r1, r5
	mul	r0, ip, r0
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r9, r7, r10
	str	ip, [fp, #-56]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-60]
	mov	r1, r5
	ldr	ip, [fp, #-56]
	str	r0, [r9, #20]
	mul	r0, ip, r3
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-64]
	mov	r1, r5
	str	r0, [r9, #16]
	mul	r0, ip, r2
	bl	__aeabi_uidiv
	mov	r3, #0
	str	r8, [r9, #36]
	str	r5, [r9, #40]
	str	r3, [r9, #32]
	str	r3, [r7, r4, asl #6]
	str	r3, [r9, #28]
	str	r0, [r9, #24]
.L368:
	ldr	r3, [fp, #-48]
	ldr	r0, .L433+12
	rsb	r3, r3, r10
	add	r1, r6, r3
	add	r7, r1, #32
	ldr	r2, [r1, #36]
	ldr	r5, [r1, #8]
	cmp	r2, #1
	beq	.L426
	ldr	r2, [r1, #52]
	cmp	r2, #1
	beq	.L427
	ldr	r2, [r0, r3]
	cmp	r2, #0
	beq	.L377
	ldr	r7, [r1, #48]
	cmp	r7, #0
	beq	.L428
.L377:
	mov	r0, r5
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L429
	mov	r0, r5
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L430
	mov	r1, #1
	mov	r0, r4
	bl	VDMDRV_AfterDec
.L384:
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r10
	add	r3, r6, r3
	ldr	r0, [r3, #8]
	bl	VCTRL_InformVdmFree
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	beq	.L431
.L380:
	ldr	r3, .L433+8
	mov	r0, #0
	ldr	r3, [r3, #16]
	blx	r3
	mov	r3, #180
	mla	r4, r3, r4, r6
	mov	r0, #1
	ldr	r1, [r4, #476]
	bl	VCTRL_RecordData
	mov	r0, #10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VCTRL_RecordPosTime
.L387:
	mov	r8, r5
	mov	r9, r5
	b	.L345
.L385:
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L344
.L429:
	mov	r3, r5
	movw	r2, #1190
	ldr	r1, .L433+40
	mov	r0, #0
	bl	dprint_vfmw
.L375:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	rsb	r3, r3, r10
	add	r1, r6, r3
	str	r2, [r6, r3]
	ldr	r3, [r1, #8]
	add	r3, r3, #64
	add	r3, r6, r3, lsl #2
	str	r2, [r3, #68]
	b	.L384
.L424:
	sub	r2, r0, #1
	sub	r3, r8, #1
	clz	r2, r2
	clz	r3, r3
	mov	r2, r2, lsr #5
	mov	r3, r3, lsr #5
	tst	r2, r3
	bne	.L362
	cmp	r0, #0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	bne	.L382
	cmp	r8, #0
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r2, #0
	beq	.L357
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r10
	add	r3, r6, r3
	add	r3, r3, #40
	ldr	r2, [r3, #4]
	cmp	r2, #2
	beq	.L432
.L362:
	ldr	r3, [fp, #-48]
	mov	r2, #1
	str	r2, [fp, #-52]
	rsb	r3, r3, r10
	add	r3, r6, r3
	str	r2, [r3, #44]
	b	.L356
.L425:
	mov	r0, r8
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-56]
	str	r0, [r9, #12]
	b	.L373
.L359:
	cmp	r5, #1
	bne	.L357
	cmp	r8, #1
	bne	.L357
.L382:
	ldr	r3, [fp, #-48]
	mov	r2, #2
	mov	r1, #0
	str	r1, [fp, #-52]
	rsb	r3, r3, r10
	add	r3, r6, r3
	str	r2, [r3, #44]
	b	.L356
.L363:
	mov	r0, r3
	movw	r2, #1241
	ldr	r1, .L433+44
	bl	dprint_vfmw
	b	.L364
.L365:
	mov	r0, r3
	movw	r2, #1243
	ldr	r1, .L433+44
	bl	dprint_vfmw
	b	.L366
.L431:
	ldr	r3, .L433+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L380
	ldr	r0, [fp, #-52]
	mov	r1, r4
	bl	VDH_Notify_ModuleIdle
	b	.L380
.L426:
	movw	r2, #1161
	ldr	r1, .L433+48
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #4]
	b	.L375
.L427:
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_VdmProcSedOnly
	b	.L375
.L430:
	mov	r3, r5
	movw	r2, #1196
	ldr	r1, .L433+52
	bl	dprint_vfmw
	b	.L375
.L428:
	ldr	r1, .L433+56
	mov	r0, r7
	bl	dprint_vfmw
	mov	r0, r5
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L375
	mov	r2, r7
	mov	r0, r5
	mov	r3, r4
	mov	r1, #100
	bl	VCTRL_VdmPostProc
	b	.L375
.L432:
	mov	r2, #3
	str	r5, [fp, #-52]
	str	r2, [r3, #4]
	b	.L356
.L388:
	mov	r9, r5
	b	.L345
.L434:
	.align	2
.L433:
	.word	.LANCHOR1+124
	.word	.LC22
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	g_vdm_hal_fun_ptr
	.word	g_HalDisable
	.word	.LANCHOR0+2504
	.word	.LANCHOR1+144
	.word	g_VfmwGlobalStat
	.word	.LC25
	.word	.LC3
	.word	.LC23
	.word	.LC26
	.word	.LC24
	UNWIND(.fnend)
	.size	VDMDRV_IsrProcess, .-VDMDRV_IsrProcess
	.align	2
	.global	VDMDRV_ResetVDH
	.type	VDMDRV_ResetVDH, %function
VDMDRV_ResetVDH:
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
	ldr	r4, .L440
	ldr	r3, [r4, #8]
	cmp	r3, r0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L440+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L437
	mov	r1, #0
	mov	r0, #1
	bl	VDH_Reset_Module
.L438:
	mov	r3, #0
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L437:
	ldr	r3, .L440+8
	ldr	r3, [r3, #76]
	cmp	r3, #0
	beq	.L439
	mov	r0, #0
	blx	r3
	b	.L438
.L439:
	mov	r0, r3
	movw	r2, #1590
	ldr	r1, .L440+12
	bl	dprint_vfmw
	b	.L438
.L441:
	.align	2
.L440:
	.word	.LANCHOR0
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_ResetVDH, .-VDMDRV_ResetVDH
	.align	2
	.global	VDMDRV_MarkReloadDsp
	.type	VDMDRV_MarkReloadDsp, %function
VDMDRV_MarkReloadDsp:
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
	subs	lr, r0, #0
	mov	ip, r1
	bne	.L442
	add	r3, r1, #1
	cmp	r3, #32
	bhi	.L442
	ldr	r3, .L449
	cmn	r1, #1
	mov	r2, #1
	str	r2, [r3, #40]
	beq	.L442
	ldr	r4, .L449+4
	mvn	r5, #0
	movw	r3, #1619
	ldr	r2, .L449+8
	ldr	r1, .L449+12
	mov	r0, #22
	ldr	ip, [r4, ip, asl #2]
	str	r5, [ip, #28]
	ldr	ip, [r4]
	ldr	ip, [ip, #28]
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	dprint_vfmw
.L442:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L450:
	.align	2
.L449:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LANCHOR1+164
	.word	.LC27
	UNWIND(.fnend)
	.size	VDMDRV_MarkReloadDsp, .-VDMDRV_MarkReloadDsp
	.align	2
	.global	VDMDRV_UpdateMatchMode
	.type	VDMDRV_UpdateMatchMode, %function
VDMDRV_UpdateMatchMode:
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
	cmp	r0, #0
	mov	ip, r1
	bne	.L451
	cmp	r1, #31
	bls	.L453
.L451:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L453:
	ldr	lr, .L454
	mov	r5, #1
	mov	r3, #1632
	ldr	r2, .L454+4
	ldr	r1, .L454+8
	mov	r0, #22
	ldr	r4, [lr, ip, asl #2]
	str	r5, [r4, #28]
	ldr	lr, [lr, ip, asl #2]
	str	ip, [sp, #4]
	ldr	ip, [lr, #28]
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L455:
	.align	2
.L454:
	.word	s_pstVfmwChan
	.word	.LANCHOR1+188
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMDRV_UpdateMatchMode, .-VDMDRV_UpdateMatchMode
	.global	g_VdmExtParam
	.global	g_DspDrvState
	.global	g_VdmDrvParam
	.global	USE_FF_APT_EN
	.global	g_ChanCtx
	.global	g_BackUp
	.global	g_DecReport
	.global	g_RepairParam
	.global	g_HwMem
	.global	g_UpMsg
	.global	CapItem
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.14670, %object
	.size	__func__.14670, 19
__func__.14670:
	.ascii	"VDMDRV_ChnDecReady\000"
	.space	1
	.type	__FUNCTION__.14711, %object
	.size	__FUNCTION__.14711, 19
__FUNCTION__.14711:
	.ascii	"VDMDRV_DoBeforeDec\000"
	.space	1
	.type	__FUNCTION__.14748, %object
	.size	__FUNCTION__.14748, 29
__FUNCTION__.14748:
	.ascii	"VDMDRV_AfterDecProcessNormal\000"
	.space	3
	.type	__FUNCTION__.14760, %object
	.size	__FUNCTION__.14760, 29
__FUNCTION__.14760:
	.ascii	"VDMDRV_AfterDecProcessRepair\000"
	.space	3
	.type	__FUNCTION__.14798, %object
	.size	__FUNCTION__.14798, 19
__FUNCTION__.14798:
	.ascii	"VDMDRV_CheckDevice\000"
	.space	1
	.type	__func__.14848, %object
	.size	__func__.14848, 18
__func__.14848:
	.ascii	"VDMDRV_IsrProcess\000"
	.space	2
	.type	__FUNCTION__.14849, %object
	.size	__FUNCTION__.14849, 18
__FUNCTION__.14849:
	.ascii	"VDMDRV_IsrProcess\000"
	.space	2
	.type	__func__.14938, %object
	.size	__func__.14938, 21
__func__.14938:
	.ascii	"VDMDRV_MarkReloadDsp\000"
	.space	3
	.type	__func__.14943, %object
	.size	__func__.14943, 23
__func__.14943:
	.ascii	"VDMDRV_UpdateMatchMode\000"
	.data
	.align	2
	.type	USE_FF_APT_EN, %object
	.size	USE_FF_APT_EN, 4
USE_FF_APT_EN:
	.word	1
	.type	CapItem, %object
	.size	CapItem, 924
CapItem:
	.word	176
	.word	144
	.word	4
	.word	10
	.word	11
	.word	12
	.word	524288
	.word	352
	.word	288
	.word	4
	.word	10
	.word	11
	.word	12
	.word	786432
	.word	720
	.word	576
	.word	4
	.word	10
	.word	11
	.word	12
	.word	1048576
	.word	1280
	.word	736
	.word	4
	.word	10
	.word	11
	.word	12
	.word	2097152
	.word	1920
	.word	1088
	.word	4
	.word	10
	.word	11
	.word	12
	.word	3145728
	.word	176
	.word	144
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	352
	.word	288
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	720
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	736
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	5632
	.word	4224
	.word	1
	.word	3
	.word	3
	.word	3
	.word	16777216
	.word	1280
	.word	800
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	800
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1488
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	1280
	.word	1488
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	2160
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	1280
	.word	2176
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	2160
	.word	2176
	.word	4
	.word	11
	.word	11
	.word	11
	.word	4194304
	.word	4096
	.word	2304
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	2304
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	4096
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	8388608
	.word	8192
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	4096
	.word	8192
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	8192
	.word	8192
	.word	1
	.word	3
	.word	3
	.word	3
	.word	20971520
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	17
	.word	26
	.word	26
	.word	26
	.word	2097152
	.word	192
	.word	192
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	384
	.word	320
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	768
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	768
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	4096
	.word	2304
	.word	4
	.word	4
	.word	4
	.word	4
	.word	16777216
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"Chan %d: CorrectType = %d ErrRatio = %d \012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"Chan %d: Current frame:%d  ErrRatio = %d\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"====== forece VDM sleep! ======\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"The channel %d is decoding\012\000" )
.LC6:
	ASCII(.ascii	"The channel %d DEC PARAM is not ready\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"SMMU_READ_ERR  MODULE : VFMW \011 SMMU INT STATE: 0" )
	ASCII(.ascii	"x%x \011 read_err_addr  = 0x%x\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"SMMU_WRITE_ERR MODULE : VFMW \011 SMMU INT STATE: 0" )
	ASCII(.ascii	"x%x \011 write_err_addr = 0x%x\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"VDMHAL_V200_IsMpeg4NvopCopy point of picture para n" )
	ASCII(.ascii	"ull, wait forever!!!\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"VDMDRV_IsVc1SkpicCopy point of picture para null, w" )
	ASCII(.ascii	"ait forever!!!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"VDMDRV_IsVp6NvopCopy point of picture para null, wa" )
	ASCII(.ascii	"it forever!!!\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"VDMDRV_IsVp9RptFrmCopy point of picture para null, " )
	ASCII(.ascii	"wait forever!!!\012\000" )
.LC13:
	ASCII(.ascii	"VDMDRV_IsProtocolCopy point of picture para null, w" )
	ASCII(.ascii	"ait forever!!!\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"The channel %d DEC PARAM is not ready(pDecParam == " )
	ASCII(.ascii	"NULL)\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"VDM Start Fail 2 !\012\000" )
.LC16:
	ASCII(.ascii	"isr begin: *pVdmStateMachine = %d, timeout = %d, Er" )
	ASCII(.ascii	"rRatio = %d\012\000" )
.LC17:
	ASCII(.ascii	"ISR process vdm timeout! FromInt = %d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"Chan %d VdmStateMachine=%d Error! FromInt = %d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC19:
	ASCII(.ascii	"Chan %d Mfde Running VdmStateMachine = %d, but DecP" )
	ASCII(.ascii	"aram = NULL!\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"Chan %d VdmStateMachine = %d, but DecParam = NULL, " )
	ASCII(.ascii	"Reset VDH MFDE!\012\000" )
.LC21:
	ASCII(.ascii	"Chan %d VDM Time Out(%d ms), Reset VDM!\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC23:
	ASCII(.ascii	"Line %d, ISR called, ChanResetFlag = 1!!\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"vdm state machine = %d, but DecParam is null!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"line :%d ISR called but chan %d is not active!\012\000" )
.LC26:
	ASCII(.ascii	"line :%d ISR called chan %d is active! But Dec Para" )
	ASCII(.ascii	"m in CTX is NULL!!!\012\000" )
.LC27:
	ASCII(.ascii	"%s,%d, i = %d, MatchVdhIdPlus1 = %d\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"%s,%d, MatchVdhIdPlus1 = %d,chanId = %d\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_VdmDrvParam, %object
	.size	g_VdmDrvParam, 56
g_VdmDrvParam:
	.space	56
	.type	s_eVdmDrvSleepState, %object
	.size	s_eVdmDrvSleepState, 4
s_eVdmDrvSleepState:
	.space	4
	.type	g_DspDrvState, %object
	.size	g_DspDrvState, 8
g_DspDrvState:
	.space	8
	.type	g_ChanCtx, %object
	.size	g_ChanCtx, 384
g_ChanCtx:
	.space	384
	.type	g_BackUp, %object
	.size	g_BackUp, 180
g_BackUp:
	.space	180
	.type	g_RepairParam, %object
	.size	g_RepairParam, 1744
g_RepairParam:
	.space	1744
	.type	last_rec_pos_time.14708, %object
	.size	last_rec_pos_time.14708, 128
last_rec_pos_time.14708:
	.space	128
	.type	LastRecPosTime.14845, %object
	.size	LastRecPosTime.14845, 128
LastRecPosTime.14845:
	.space	128
	.type	g_VdmExtParam, %object
	.size	g_VdmExtParam, 268
g_VdmExtParam:
	.space	268
	.type	g_DecReport, %object
	.size	g_DecReport, 820
g_DecReport:
	.space	820
	.type	g_HwMem, %object
	.size	g_HwMem, 1228
g_HwMem:
	.space	1228
	.type	g_UpMsg, %object
	.size	g_UpMsg, 3200
g_UpMsg:
	.space	3200
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
