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
	.file	"ctrl_case.c"
	.text
	.align	2
	.global	CASE_StopLowDelayCalc
	.type	CASE_StopLowDelayCalc, %function
CASE_StopLowDelayCalc:
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
	mov	r0, #22
	ldr	r1, .L2
	bl	dprint_vfmw
	ldr	r1, .L2+4
	ldr	r2, .L2+8
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r1, r4]
	str	r3, [r2, r4, asl #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	.word	g_LowDelayCalcStat
	.word	g_LowDelayCalcHandle
	UNWIND(.fnend)
	.size	CASE_StopLowDelayCalc, .-CASE_StopLowDelayCalc
	.align	2
	.global	CASE_ResetChan
	.type	CASE_ResetChan, %function
CASE_ResetChan:
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
	ldr	r5, .L5
	mov	r2, r1
	mov	r4, r0
	ldr	r1, .L5+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	bl	VCTRL_ResetChan
	ldr	r3, [r5, #16]
	mov	r4, r0
	mov	r0, #0
	blx	r3
	adds	r0, r4, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	CASE_ResetChan, .-CASE_ResetChan
	.align	2
	.global	CASE_StartChan
	.type	CASE_StartChan, %function
CASE_StartChan:
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
	ldr	r5, .L8
	mov	r2, r1
	mov	r4, r0
	ldr	r1, .L8+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	bl	VCTRL_EnableEsBuf
	mov	r0, r4
	bl	VCTRL_StartChan
	ldr	r3, [r5, #16]
	mov	r4, r0
	mov	r0, #0
	blx	r3
	adds	r0, r4, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	CASE_StartChan, .-CASE_StartChan
	.align	2
	.global	CASE_StopChan
	.type	CASE_StopChan, %function
CASE_StopChan:
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
	bl	VCTRL_StopChanWithCheck
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CASE_StopChan, .-CASE_StopChan
	.align	2
	.global	CASE_GetChanState
	.type	CASE_GetChanState, %function
CASE_GetChanState:
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
	ldr	r4, .L12
	mov	r5, r0
	mov	r6, r1
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VCTRL_GetChanState
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L13:
	.align	2
.L12:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CASE_GetChanState, .-CASE_GetChanState
	.align	2
	.global	CASE_ReleaseStream
	.type	CASE_ReleaseStream, %function
CASE_ReleaseStream:
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
	ldr	r5, .L15
	mov	r2, r1
	mov	r4, r0
	ldr	r1, .L15+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	bl	VCTRL_ReleaseStream
	ldr	r3, [r5, #16]
	mov	r4, r0
	mov	r0, #0
	blx	r3
	adds	r0, r4, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L16:
	.align	2
.L15:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	CASE_ReleaseStream, .-CASE_ReleaseStream
	.align	2
	.global	CASE_ExtraWakupThread
	.type	CASE_ExtraWakupThread, %function
CASE_ExtraWakupThread:
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
	ldr	r4, .L18
	mov	r2, r0
	mov	r3, r1
	mov	r0, #22
	ldr	r1, .L18+4
	bl	dprint_vfmw
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
	bl	VCTRL_ExtraWakeUpThread
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	UNWIND(.fnend)
	.size	CASE_ExtraWakupThread, .-CASE_ExtraWakupThread
	.align	2
	.global	CASE_ReportDemuxRelease
	.type	CASE_ReportDemuxRelease, %function
CASE_ReportDemuxRelease:
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
	ldr	r4, .L26
	mov	r5, r0
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r0, r5
	bl	VCTRL_IfEsBufEnable
	cmp	r0, #0
	beq	.L21
	mov	r0, r5
	bl	VCTRL_DisableEsBuf
.L21:
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L27:
	.align	2
.L26:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CASE_ReportDemuxRelease, .-CASE_ReportDemuxRelease
	.align	2
	.global	CASE_SetFrameRate
	.type	CASE_SetFrameRate, %function
CASE_SetFrameRate:
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
	beq	.L31
	ldr	r2, .L32
	mov	r3, #0
	ldr	r1, [r1]
	ldr	r2, [r2, r0, asl #2]
	str	r1, [r2, #1464]
.L30:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L31:
	mov	r0, r1
	movw	r3, #451
	ldr	r2, .L32+4
	ldr	r1, .L32+8
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L30
.L33:
	.align	2
.L32:
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetFrameRate, .-CASE_SetFrameRate
	.align	2
	.global	CASE_SetFrameBufferNum
	.type	CASE_SetFrameBufferNum, %function
CASE_SetFrameBufferNum:
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
	beq	.L38
	ldr	r3, .L39
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	addne	r2, r3, #290816
	ldrne	ip, [r1]
	movne	r0, #0
	mvneq	r0, #0
	strne	ip, [r2, #780]
	ldrne	r2, [r1]
	strne	r2, [r3, #1392]
	ldmfd	sp, {fp, sp, pc}
.L38:
	mov	r0, r1
	movw	r3, #481
	ldr	r2, .L39+4
	ldr	r1, .L39+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L40:
	.align	2
.L39:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+20
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetFrameBufferNum, .-CASE_SetFrameBufferNum
	.align	2
	.global	CASE_StartLowDelayCalc
	.type	CASE_StartLowDelayCalc, %function
CASE_StartLowDelayCalc:
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
	mov	r3, r0
	beq	.L44
	ldr	ip, .L45
	mov	lr, #1
	ldr	r2, .L45+4
	mov	r0, #0
	strb	lr, [ip, r3]
	ldr	r1, [r1]
	str	r1, [r2, r3, asl #2]
	ldmfd	sp, {fp, sp, pc}
.L44:
	mov	r0, r1
	movw	r3, #537
	ldr	r2, .L45+8
	ldr	r1, .L45+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L46:
	.align	2
.L45:
	.word	g_LowDelayCalcStat
	.word	g_LowDelayCalcHandle
	.word	.LANCHOR0+44
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_StartLowDelayCalc, .-CASE_StartLowDelayCalc
	.align	2
	.global	CASE_GetCapability
	.type	CASE_GetCapability, %function
CASE_GetCapability:
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
	mov	r2, r0
	ldr	r1, .L51
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L50
	mov	r1, r4
	mov	r0, #0
	bl	PDT_GetAttribute
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L50:
	mov	r0, r4
	mov	r3, #55
	ldr	r2, .L51+4
	ldr	r1, .L51+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L52:
	.align	2
.L51:
	.word	.LC3
	.word	.LANCHOR0+68
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetCapability, .-CASE_GetCapability
	.align	2
	.global	CASE_GetOutputFormat
	.type	CASE_GetOutputFormat, %function
CASE_GetOutputFormat:
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
	mov	r2, r0
	ldr	r1, .L57
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L56
	mov	r1, r4
	mov	r0, #1
	bl	PDT_GetAttribute
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L56:
	mov	r0, r4
	mov	r3, #65
	ldr	r2, .L57+4
	ldr	r1, .L57+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L58:
	.align	2
.L57:
	.word	.LC3
	.word	.LANCHOR0+88
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetOutputFormat, .-CASE_GetOutputFormat
	.align	2
	.global	CASE_GetChanMemSize
	.type	CASE_GetChanMemSize, %function
CASE_GetChanMemSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r5, r1
	mov	r2, r0
	ldr	r1, .L65
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r5, #0
	beq	.L64
	ldr	r6, .L65+4
	mov	r0, #0
	ldr	r3, [r6, #12]
	blx	r3
	mov	r3, #1
	sub	r2, fp, #40
	ldr	r1, [r5, #8]
	ldr	r0, [r5]
	bl	VCTRL_GetChanMemSize
	cmp	r0, #0
	bne	.L62
	ldr	r2, [fp, #-40]
	mov	r4, r0
	ldr	r3, [fp, #-36]
	stmia	r5, {r2, r3}
.L63:
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	mov	r0, r4
.L61:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L62:
	mvn	r2, #0
	ldr	r1, .L65+8
	mov	r0, #1
	mov	r4, r2
	bl	dprint_vfmw
	b	.L63
.L64:
	mov	r0, r5
	mov	r3, #83
	ldr	r2, .L65+12
	ldr	r1, .L65+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L61
.L66:
	.align	2
.L65:
	.word	.LC3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LANCHOR0+112
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetChanMemSize, .-CASE_GetChanMemSize
	.align	2
	.global	CASE_CreateChan
	.type	CASE_CreateChan, %function
CASE_CreateChan:
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
	mov	r2, r0
	ldr	r1, .L71
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L70
	mov	r3, #0
	mov	r2, #2
	ldr	r1, [r4, #8]
	ldr	r0, [r4]
	bl	VCTRL_CreateChan
	mov	r3, r0
	mov	r0, r0, asr #31
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L70:
	mov	r0, r4
	mov	r3, #128
	ldr	r2, .L71+4
	ldr	r1, .L71+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L72:
	.align	2
.L71:
	.word	.LC3
	.word	.LANCHOR0+132
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_CreateChan, .-CASE_CreateChan
	.align	2
	.global	CASE_DestroyChan
	.type	CASE_DestroyChan, %function
CASE_DestroyChan:
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
	mov	r2, r1
	mov	r5, r0
	ldr	r1, .L79
	mov	r0, #22
	bl	dprint_vfmw
	mov	r4, #500
	ldr	r6, .L79+4
	b	.L74
.L75:
	ldr	r3, [r6, #120]
	sub	r4, r4, #1
	blx	r3
.L74:
	mov	r1, #2
	mov	r0, r5
	bl	VCTRT_SetChanCtrlState
	adds	r3, r4, #0
	movne	r3, #1
	cmn	r0, #1
	mov	r0, #1
	movne	r3, #0
	cmp	r3, #0
	bne	.L75
	cmp	r4, #0
	ble	.L78
	mov	r0, r5
	bl	VCTRL_DestroyChan
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L78:
	mov	r0, r3
	mvn	r2, #0
	ldr	r1, .L79+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L80:
	.align	2
.L79:
	.word	.LC0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	UNWIND(.fnend)
	.size	CASE_DestroyChan, .-CASE_DestroyChan
	.align	2
	.global	CASE_ResetChanWithOption
	.type	CASE_ResetChanWithOption, %function
CASE_ResetChanWithOption:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L84
	ldr	r4, .L85
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_ResetChanWithOption
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L83:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L84:
	mov	r0, r5
	mov	r3, #194
	ldr	r2, .L85+4
	mvn	r4, #0
	ldr	r1, .L85+8
	bl	dprint_vfmw
	b	.L83
.L86:
	.align	2
.L85:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+148
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_ResetChanWithOption, .-CASE_ResetChanWithOption
	.align	2
	.global	CASE_GetChanConfig
	.type	CASE_GetChanConfig, %function
CASE_GetChanConfig:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L90
	ldr	r4, .L91
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_GetChanCfg
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L89:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L90:
	mov	r0, r5
	mov	r3, #249
	ldr	r2, .L91+4
	mvn	r4, #0
	ldr	r1, .L91+8
	bl	dprint_vfmw
	b	.L89
.L92:
	.align	2
.L91:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+176
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetChanConfig, .-CASE_GetChanConfig
	.align	2
	.global	CASE_ConfigChan
	.type	CASE_ConfigChan, %function
CASE_ConfigChan:
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
	subs	r6, r1, #0
	mov	r5, r0
	beq	.L97
	ldr	r4, .L99
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VCTRL_ConfigChan
	cmp	r0, #0
	beq	.L98
.L96:
	adds	r3, r0, #0
	ldr	r2, [r4, #16]
	mov	r0, #0
	movne	r3, #1
	rsb	r4, r3, #0
	blx	r2
.L95:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L98:
	mov	r0, r5
	bl	VCTRL_LoadDspCode
	b	.L96
.L97:
	mov	r0, r6
	movw	r3, #265
	ldr	r2, .L99+4
	mvn	r4, #0
	ldr	r1, .L99+8
	bl	dprint_vfmw
	b	.L95
.L100:
	.align	2
.L99:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+196
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_ConfigChan, .-CASE_ConfigChan
	.align	2
	.global	CASE_SetStreamIntf
	.type	CASE_SetStreamIntf, %function
CASE_SetStreamIntf:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L104
	ldr	r4, .L105
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_SetStreamInterface
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L103:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L104:
	mov	r0, r5
	mov	r3, #316
	ldr	r2, .L105+4
	mvn	r4, #0
	ldr	r1, .L105+8
	bl	dprint_vfmw
	b	.L103
.L106:
	.align	2
.L105:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+212
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetStreamIntf, .-CASE_SetStreamIntf
	.align	2
	.global	CASE_GetStreamSize
	.type	CASE_GetStreamSize, %function
CASE_GetStreamSize:
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
	subs	r4, r1, #0
	mov	r6, r0
	beq	.L110
	ldr	r5, .L111
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	mov	r1, r4
	mov	r0, r6
	bl	VCTRL_GetStreamSize
	ldr	r3, [r5, #16]
	mov	r4, r0
	mov	r0, #0
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L110:
	mov	r0, r4
	mov	r3, #332
	ldr	r2, .L111+4
	ldr	r1, .L111+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L112:
	.align	2
.L111:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+232
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetStreamSize, .-CASE_GetStreamSize
	.align	2
	.global	CASE_GetChanIDByMem
	.type	CASE_GetChanIDByMem, %function
CASE_GetChanIDByMem:
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
	beq	.L116
	ldr	r5, .L117
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	ldr	r0, [r4]
	bl	VCTRL_GetChanIDByMemAddr
	mov	r3, r0
	cmn	r3, #1
	str	r3, [r4]
	mov	r0, #0
	ldr	r2, [r5, #16]
	movne	r3, #0
	moveq	r3, #1
	rsb	r4, r3, #0
	blx	r2
.L115:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L116:
	mov	r0, r4
	movw	r3, #361
	ldr	r2, .L117+4
	mvn	r4, #0
	ldr	r1, .L117+8
	bl	dprint_vfmw
	b	.L115
.L118:
	.align	2
.L117:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+252
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetChanIDByMem, .-CASE_GetChanIDByMem
	.align	2
	.global	CASE_SetDiscardPicParam
	.type	CASE_SetDiscardPicParam, %function
CASE_SetDiscardPicParam:
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
	subs	r4, r1, #0
	mov	r6, r0
	beq	.L122
	ldr	r5, .L123
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	mov	r1, r4
	mov	r0, r6
	bl	VCTRL_SetDiscardPicParam
	ldr	r3, [r5, #16]
	mov	r4, r0
	mov	r0, #0
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L122:
	mov	r0, r4
	movw	r3, #378
	ldr	r2, .L123+4
	ldr	r1, .L123+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L124:
	.align	2
.L123:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetDiscardPicParam, .-CASE_SetDiscardPicParam
	.align	2
	.global	CASE_SetPtsToSeek
	.type	CASE_SetPtsToSeek, %function
CASE_SetPtsToSeek:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
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
	subs	r7, r1, #0
	mov	r6, r0
	beq	.L129
	ldr	r5, .L131
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	sub	r1, fp, #40
	mov	r0, r6
	mov	r3, #0
	mov	r2, #1
	str	r3, [fp, #-36]
	str	r2, [fp, #-40]
	str	r3, [fp, #-32]
	bl	VCTRL_ResetChanWithOption
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r4, r0, #0
	cmp	r4, #0
	beq	.L130
.L128:
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mov	r0, r4
.L127:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L130:
	mov	r1, r7
	mov	r0, r6
	bl	VCTRL_SeekPts
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r4, r0, #0
	b	.L128
.L129:
	mov	r0, r7
	movw	r3, #395
	ldr	r2, .L131+4
	ldr	r1, .L131+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L127
.L132:
	.align	2
.L131:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+296
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetPtsToSeek, .-CASE_SetPtsToSeek
	.align	2
	.global	CASE_SetTrickMode
	.type	CASE_SetTrickMode, %function
CASE_SetTrickMode:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L136
	ldr	r4, .L137
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_ConfigFFFBSpeed
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L135:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L136:
	mov	r0, r5
	movw	r3, #421
	ldr	r2, .L137+4
	mvn	r4, #0
	ldr	r1, .L137+8
	bl	dprint_vfmw
	b	.L135
.L138:
	.align	2
.L137:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+316
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetTrickMode, .-CASE_SetTrickMode
	.align	2
	.global	CASE_SetCtrlInfo
	.type	CASE_SetCtrlInfo, %function
CASE_SetCtrlInfo:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L142
	ldr	r4, .L143
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_ConfigPVRInfo
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L141:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L142:
	mov	r0, r5
	movw	r3, #437
	ldr	r2, .L143+4
	mvn	r4, #0
	ldr	r1, .L143+8
	bl	dprint_vfmw
	b	.L141
.L144:
	.align	2
.L143:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+336
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetCtrlInfo, .-CASE_SetCtrlInfo
	.align	2
	.global	CASE_AllocMemToDecoder
	.type	CASE_AllocMemToDecoder, %function
CASE_AllocMemToDecoder:
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
	subs	r4, r1, #0
	mov	r6, r0
	beq	.L152
	ldr	r5, .L154
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	mov	r1, r4
	mov	r0, r6
	bl	VCTRL_AllocMemToDecoder
	subs	r4, r0, #0
	bne	.L153
.L148:
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L153:
	ldr	r1, .L154+4
	mov	r0, #1
	bl	dprint_vfmw
	b	.L148
.L152:
	mov	r0, r4
	movw	r3, #462
	ldr	r2, .L154+8
	ldr	r1, .L154+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L155:
	.align	2
.L154:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LANCHOR0+356
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_AllocMemToDecoder, .-CASE_AllocMemToDecoder
	.align	2
	.global	CASE_GetUserDecFrame
	.type	CASE_GetUserDecFrame, %function
CASE_GetUserDecFrame:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L159
	ldr	r4, .L160
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_GetUsrdecFrame
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L158:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L159:
	mov	r0, r5
	movw	r3, #502
	ldr	r2, .L160+4
	mvn	r4, #0
	ldr	r1, .L160+8
	bl	dprint_vfmw
	b	.L158
.L161:
	.align	2
.L160:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+380
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_GetUserDecFrame, .-CASE_GetUserDecFrame
	.align	2
	.global	CASE_PutUserDecFrame
	.type	CASE_PutUserDecFrame, %function
CASE_PutUserDecFrame:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L165
	ldr	r4, .L166
	mov	r0, #0
	ldr	r3, [r4, #12]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_PutUsrdecFrame
	ldr	r3, [r4, #16]
	adds	r4, r0, #0
	mov	r0, #0
	movne	r4, #1
	rsb	r4, r4, #0
	blx	r3
.L164:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L165:
	mov	r0, r5
	movw	r3, #518
	ldr	r2, .L166+4
	mvn	r4, #0
	ldr	r1, .L166+8
	bl	dprint_vfmw
	b	.L164
.L167:
	.align	2
.L166:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+404
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_PutUserDecFrame, .-CASE_PutUserDecFrame
	.align	2
	.global	CASE_ReportOccupiedFrame
	.type	CASE_ReportOccupiedFrame, %function
CASE_ReportOccupiedFrame:
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
	subs	r3, r1, #0
	mov	r5, r0
	beq	.L175
	bl	VCTRL_ReportOccupiedFrame
	subs	r4, r0, #0
	bne	.L176
.L171:
	adds	r0, r4, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L176:
	mov	r2, r5
	ldr	r1, .L177
	mov	r0, #1
	bl	dprint_vfmw
	b	.L171
.L175:
	mov	r0, r3
	ldr	r2, .L177+4
	movw	r3, #562
	ldr	r1, .L177+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L178:
	.align	2
.L177:
	.word	.LC7
	.word	.LANCHOR0+428
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_ReportOccupiedFrame, .-CASE_ReportOccupiedFrame
	.align	2
	.global	CASE_SetImageOutputInfo
	.type	CASE_SetImageOutputInfo, %function
CASE_SetImageOutputInfo:
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
	subs	r3, r1, #0
	mov	r5, r0
	beq	.L186
	bl	VCTRL_ImageOutputEnable
	subs	r4, r0, #0
	bne	.L187
.L182:
	adds	r0, r4, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L187:
	mov	r2, r5
	ldr	r1, .L188
	mov	r0, #1
	bl	dprint_vfmw
	b	.L182
.L186:
	mov	r0, r3
	ldr	r2, .L188+4
	movw	r3, #581
	ldr	r1, .L188+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L189:
	.align	2
.L188:
	.word	.LC8
	.word	.LANCHOR0+456
	.word	.LC2
	UNWIND(.fnend)
	.size	CASE_SetImageOutputInfo, .-CASE_SetImageOutputInfo
	.align	2
	.global	CASE_HandleEntry
	.type	CASE_HandleEntry, %function
CASE_HandleEntry:
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
	cmp	r1, #5
	ldrne	ip, .L228
	bne	.L195
	b	.L227
.L223:
	ldr	r3, [ip, #16]
	add	ip, ip, #12
	cmp	r3, #0
	beq	.L191
	cmp	lr, r1
	beq	.L226
.L195:
	ldr	lr, [ip, #12]
	cmp	lr, #37
	bne	.L223
.L191:
	cmp	r1, #11
	cmpne	r1, #1
	bne	.L202
.L201:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L228+4
	bl	dprint_vfmw
.L224:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L202:
	cmp	r1, #12
	cmpne	r1, #0
	beq	.L201
	mov	r3, #0
	b	.L204
.L226:
	cmp	r1, #11
	cmpne	r1, #1
	bne	.L192
	mov	r1, r2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L227:
	ldr	r3, .L228+8
.L192:
	cmp	r1, #12
	cmpne	r1, #0
	beq	.L197
.L204:
	cmp	r0, #31
	bhi	.L200
	ldr	ip, .L228+12
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L200
	ldr	ip, [ip]
	cmp	ip, r0
	bne	.L200
.L197:
	cmp	r3, #0
	beq	.L201
	mov	r1, r2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L200:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L228+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L224
.L229:
	.align	2
.L228:
	.word	.LANCHOR0+480
	.word	.LC10
	.word	CASE_GetChanState
	.word	s_pstVfmwChan
	.word	.LC9
	UNWIND(.fnend)
	.size	CASE_HandleEntry, .-CASE_HandleEntry
	.global	VDEC_CID_HandlerTable
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14152, %object
	.size	__func__.14152, 18
__func__.14152:
	.ascii	"CASE_SetFrameRate\000"
	.space	2
	.type	__func__.14164, %object
	.size	__func__.14164, 23
__func__.14164:
	.ascii	"CASE_SetFrameBufferNum\000"
	.space	1
	.type	__func__.14183, %object
	.size	__func__.14183, 23
__func__.14183:
	.ascii	"CASE_StartLowDelayCalc\000"
	.space	1
	.type	__func__.14025, %object
	.size	__func__.14025, 19
__func__.14025:
	.ascii	"CASE_GetCapability\000"
	.space	1
	.type	__func__.14030, %object
	.size	__func__.14030, 21
__func__.14030:
	.ascii	"CASE_GetOutputFormat\000"
	.space	3
	.type	__func__.14039, %object
	.size	__func__.14039, 20
__func__.14039:
	.ascii	"CASE_GetChanMemSize\000"
	.type	__func__.14047, %object
	.size	__func__.14047, 16
__func__.14047:
	.ascii	"CASE_CreateChan\000"
	.type	__func__.14067, %object
	.size	__func__.14067, 25
__func__.14067:
	.ascii	"CASE_ResetChanWithOption\000"
	.space	3
	.type	__func__.14083, %object
	.size	__func__.14083, 19
__func__.14083:
	.ascii	"CASE_GetChanConfig\000"
	.space	1
	.type	__func__.14089, %object
	.size	__func__.14089, 16
__func__.14089:
	.ascii	"CASE_ConfigChan\000"
	.type	__func__.14104, %object
	.size	__func__.14104, 19
__func__.14104:
	.ascii	"CASE_SetStreamIntf\000"
	.space	1
	.type	__func__.14110, %object
	.size	__func__.14110, 19
__func__.14110:
	.ascii	"CASE_GetStreamSize\000"
	.space	1
	.type	__func__.14121, %object
	.size	__func__.14121, 20
__func__.14121:
	.ascii	"CASE_GetChanIDByMem\000"
	.type	__func__.14127, %object
	.size	__func__.14127, 24
__func__.14127:
	.ascii	"CASE_SetDiscardPicParam\000"
	.type	__func__.14135, %object
	.size	__func__.14135, 18
__func__.14135:
	.ascii	"CASE_SetPtsToSeek\000"
	.space	2
	.type	__func__.14141, %object
	.size	__func__.14141, 18
__func__.14141:
	.ascii	"CASE_SetTrickMode\000"
	.space	2
	.type	__func__.14147, %object
	.size	__func__.14147, 17
__func__.14147:
	.ascii	"CASE_SetCtrlInfo\000"
	.space	3
	.type	__func__.14158, %object
	.size	__func__.14158, 23
__func__.14158:
	.ascii	"CASE_AllocMemToDecoder\000"
	.space	1
	.type	__func__.14170, %object
	.size	__func__.14170, 21
__func__.14170:
	.ascii	"CASE_GetUserDecFrame\000"
	.space	3
	.type	__func__.14176, %object
	.size	__func__.14176, 21
__func__.14176:
	.ascii	"CASE_PutUserDecFrame\000"
	.space	3
	.type	__func__.14194, %object
	.size	__func__.14194, 25
__func__.14194:
	.ascii	"CASE_ReportOccupiedFrame\000"
	.space	3
	.type	__func__.14201, %object
	.size	__func__.14201, 24
__func__.14201:
	.ascii	"CASE_SetImageOutputInfo\000"
	.type	VDEC_CID_HandlerTable, %object
	.size	VDEC_CID_HandlerTable, 384
VDEC_CID_HandlerTable:
	.word	5
	.word	CASE_GetChanState
	.word	100
	.word	24
	.word	CASE_SetFrameRate
	.word	4
	.word	0
	.word	CASE_GetCapability
	.word	148
	.word	30
	.word	CASE_GetOutputFormat
	.word	16
	.word	11
	.word	CASE_GetChanMemSize
	.word	128
	.word	1
	.word	CASE_CreateChan
	.word	128
	.word	2
	.word	CASE_DestroyChan
	.word	0
	.word	8
	.word	CASE_ResetChan
	.word	0
	.word	14
	.word	CASE_ResetChanWithOption
	.word	12
	.word	3
	.word	CASE_GetChanConfig
	.word	140
	.word	6
	.word	CASE_StartChan
	.word	0
	.word	7
	.word	CASE_StopChan
	.word	0
	.word	4
	.word	CASE_ConfigChan
	.word	140
	.word	13
	.word	CASE_ReleaseStream
	.word	0
	.word	9
	.word	CASE_SetStreamIntf
	.word	12
	.word	10
	.word	CASE_GetStreamSize
	.word	4
	.word	19
	.word	CASE_ExtraWakupThread
	.word	0
	.word	12
	.word	CASE_GetChanIDByMem
	.word	4
	.word	18
	.word	CASE_SetDiscardPicParam
	.word	8
	.word	21
	.word	CASE_SetPtsToSeek
	.word	24
	.word	22
	.word	CASE_SetTrickMode
	.word	4
	.word	23
	.word	CASE_SetCtrlInfo
	.word	20
	.word	28
	.word	CASE_AllocMemToDecoder
	.word	72
	.word	29
	.word	CASE_SetFrameBufferNum
	.word	4
	.word	31
	.word	CASE_ReportDemuxRelease
	.word	0
	.word	16
	.word	CASE_GetUserDecFrame
	.word	72
	.word	17
	.word	CASE_PutUserDecFrame
	.word	72
	.word	25
	.word	CASE_StartLowDelayCalc
	.word	4
	.word	26
	.word	CASE_StopLowDelayCalc
	.word	4
	.word	35
	.word	CASE_ReportOccupiedFrame
	.word	536
	.word	34
	.word	CASE_SetImageOutputInfo
	.word	4
	.word	37
	.word	0
	.word	0
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"Not care param %p\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"Not care param %d %p\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"invalid condition: %s %d\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"Not care param %d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"call VCTRL_GetChanMemSize failed ret:%d\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"VCTRT_SetChanCtrlState ERR: %d\012\000" )
.LC6:
	ASCII(.ascii	"VCTRL_AllocMemToDecoder failed!\012 \000" )
	.space	2
.LC7:
	ASCII(.ascii	"VCTRL_ReportOccupiedFrame[Chan %d] failed!\012\000" )
.LC8:
	ASCII(.ascii	"VCTRL_ImageOutputEnable[Chan %d] failed!\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"Chan id: %d is invalid, Cmd ID:%d\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"Unsupport eCmdID %d\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
