#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"ctrl_case.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	CASE_StopLowDelayCalc
	.type	CASE_StopLowDelayCalc, %function
CASE_StopLowDelayCalc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC1
	mov	x2, x20
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x2, .LC2
	mov	w0, 0
	ldr	x1, .LC3
	strb	wzr, [x2, w19, sxtw]
	str	wzr, [x1, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_StopLowDelayCalc, .-CASE_StopLowDelayCalc
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC2:
	.xword	g_LowDelayCalcStat
	.align	3
.LC3:
	.xword	g_LowDelayCalcHandle
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ResetChan
	.type	CASE_ResetChan, %function
CASE_ResetChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC4
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, .LC5
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	mov	w0, w20
	bl	VCTRL_ResetChan
	mov	w20, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cmp	w20, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_ResetChan, .-CASE_ResetChan
	.align	3
.LC4:
	.xword	.LC0
	.align	3
.LC5:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_StartChan
	.type	CASE_StartChan, %function
CASE_StartChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC6
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, .LC7
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	mov	w0, w20
	bl	VCTRL_EnableEsBuf
	mov	w0, w20
	bl	VCTRL_StartChan
	mov	w20, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cmp	w20, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_StartChan, .-CASE_StartChan
	.align	3
.LC6:
	.xword	.LC0
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_StopChan
	.type	CASE_StopChan, %function
CASE_StopChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	VCTRL_StopChanWithCheck
	cmp	w0, wzr
	csetm	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_StopChan, .-CASE_StopChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetChanState
	.type	CASE_GetChanState, %function
CASE_GetChanState:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x19, .LC8
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	mov	x1, x21
	mov	w0, w20
	bl	VCTRL_GetChanState
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	CASE_GetChanState, .-CASE_GetChanState
	.align	3
.LC8:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ReleaseStream
	.type	CASE_ReleaseStream, %function
CASE_ReleaseStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC9
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, .LC10
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	mov	w0, w20
	bl	VCTRL_ReleaseStream
	mov	w20, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cmp	w20, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_ReleaseStream, .-CASE_ReleaseStream
	.align	3
.LC9:
	.xword	.LC0
	.align	3
.LC10:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ExtraWakupThread
	.type	CASE_ExtraWakupThread, %function
CASE_ExtraWakupThread:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC12
	mov	x3, x20
	mov	w2, w19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, .LC13
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	bl	VCTRL_ExtraWakeUpThread
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_ExtraWakupThread, .-CASE_ExtraWakupThread
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC13:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ReportDemuxRelease
	.type	CASE_ReportDemuxRelease, %function
CASE_ReportDemuxRelease:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC14
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	mov	w0, w20
	bl	VCTRL_IfEsBufEnable
	cbz	w0, .L9
	mov	w0, w20
	bl	VCTRL_DisableEsBuf
.L9:
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CASE_ReportDemuxRelease, .-CASE_ReportDemuxRelease
	.align	3
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetFrameRate
	.type	CASE_SetFrameRate, %function
CASE_SetFrameRate:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L17
	ldr	x1, .LC18
	mov	w0, 0
	ldr	w2, [x19]
	ldr	x1, [x1, w20, sxtw 3]
	str	w2, [x1, 1528]
.L16:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L17:
	ldr	x2, .LC15
	mov	w3, 451
	ldr	x1, .LC17
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L16
	.size	CASE_SetFrameRate, .-CASE_SetFrameRate
	.align	3
.LC15:
	.xword	.LANCHOR0
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC18:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetFrameBufferNum
	.type	CASE_SetFrameBufferNum, %function
CASE_SetFrameBufferNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L22
	ldr	x0, .LC21
	ldr	x1, [x0, w20, sxtw 3]
	cbz	x1, .L21
	add	x2, x1, 290816
	ldr	w3, [x19]
	mov	w0, 0
	str	w3, [x2, 1132]
	ldr	w2, [x19]
	str	w2, [x1, 1456]
.L20:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L21:
	mov	w0, -1
	b	.L20
.L22:
	ldr	x2, .LC19
	mov	w3, 481
	ldr	x1, .LC20
	mov	w0, 0
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L20
	.size	CASE_SetFrameBufferNum, .-CASE_SetFrameBufferNum
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	.LC16
	.align	3
.LC21:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_StartLowDelayCalc
	.type	CASE_StartLowDelayCalc, %function
CASE_StartLowDelayCalc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L26
	ldr	x2, .LC24
	mov	w3, 1
	ldr	x1, .LC25
	mov	w0, 0
	strb	w3, [x2, w20, sxtw]
	ldr	w2, [x19]
	str	w2, [x1, w20, sxtw 2]
.L25:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L26:
	ldr	x2, .LC22
	mov	w3, 537
	ldr	x1, .LC23
	mov	w0, 0
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L25
	.size	CASE_StartLowDelayCalc, .-CASE_StartLowDelayCalc
	.align	3
.LC22:
	.xword	.LANCHOR0
	.align	3
.LC23:
	.xword	.LC16
	.align	3
.LC24:
	.xword	g_LowDelayCalcStat
	.align	3
.LC25:
	.xword	g_LowDelayCalcHandle
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetCapability
	.type	CASE_GetCapability, %function
CASE_GetCapability:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC27
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	cbz	x19, .L30
	mov	x1, x19
	mov	w0, 0
	bl	PDT_GetAttribute
	mov	w0, 0
.L29:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L30:
	ldr	x2, .LC28
	mov	w3, 55
	ldr	x1, .LC29
	mov	w0, 0
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L29
	.size	CASE_GetCapability, .-CASE_GetCapability
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC28:
	.xword	.LANCHOR0
	.align	3
.LC29:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetOutputFormat
	.type	CASE_GetOutputFormat, %function
CASE_GetOutputFormat:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC30
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	cbz	x19, .L34
	mov	x1, x19
	mov	w0, 1
	bl	PDT_GetAttribute
	mov	w0, 0
.L33:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L34:
	ldr	x2, .LC31
	mov	w3, 65
	ldr	x1, .LC32
	mov	w0, 0
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L33
	.size	CASE_GetOutputFormat, .-CASE_GetOutputFormat
	.align	3
.LC30:
	.xword	.LC26
	.align	3
.LC31:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetChanMemSize
	.type	CASE_GetChanMemSize, %function
CASE_GetChanMemSize:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC33
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	cbz	x19, .L40
	ldr	x20, .LC36
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	ldr	w0, [x19]
	mov	w3, 1
	ldr	x1, [x19, 8]
	add	x2, x29, 32
	bl	VCTRL_GetChanMemSize
	cbnz	w0, .L38
	ldp	w1, w0, [x29, 32]
	stp	w1, w0, [x19]
	mov	w19, 0
.L39:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, w19
.L37:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L38:
	ldr	x1, .LC38
	mov	w2, -1
	mov	w0, 1
	mov	w19, w2
	bl	dprint_vfmw
	b	.L39
.L40:
	ldr	x2, .LC34
	mov	w3, 83
	ldr	x1, .LC35
	mov	w0, 0
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L37
	.size	CASE_GetChanMemSize, .-CASE_GetChanMemSize
	.align	3
.LC33:
	.xword	.LC26
	.align	3
.LC34:
	.xword	.LANCHOR0
	.align	3
.LC35:
	.xword	.LC16
	.align	3
.LC36:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC38:
	.xword	.LC37
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_CreateChan
	.type	CASE_CreateChan, %function
CASE_CreateChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC39
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	cbz	x19, .L44
	ldr	x1, [x19, 8]
	mov	w3, 0
	ldr	w0, [x19]
	mov	w2, 2
	bl	VCTRL_CreateChan
	mov	w1, w0
	asr	w0, w0, 31
	str	w1, [x19]
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L44:
	ldr	x2, .LC40
	mov	w3, 128
	ldr	x1, .LC41
	mov	w0, 0
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L43
	.size	CASE_CreateChan, .-CASE_CreateChan
	.align	3
.LC39:
	.xword	.LC26
	.align	3
.LC40:
	.xword	.LANCHOR0
	.align	3
.LC41:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_DestroyChan
	.type	CASE_DestroyChan, %function
CASE_DestroyChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	mov	w19, 500
	bl	_mcount
	ldr	x1, .LC42
	mov	x2, x21
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x21, .LC43
	b	.L46
	.p2align 3
.L47:
	ldr	x1, [x21, 240]
	sub	w19, w19, #1
	blr	x1
.L46:
	mov	w1, 2
	mov	w0, w20
	bl	VCTRT_SetChanCtrlState
	mov	w1, w0
	cmp	w19, wzr
	mov	w0, 1
	ccmn	w1, #1, 0, ne
	beq	.L47
	cmp	w19, wzr
	ble	.L50
	mov	w0, w20
	bl	VCTRL_DestroyChan
	cmp	w0, wzr
	csetm	w0, ne
.L49:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L50:
	ldr	x1, .LC45
	mov	w2, -1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L49
	.size	CASE_DestroyChan, .-CASE_DestroyChan
	.align	3
.LC42:
	.xword	.LC0
	.align	3
.LC43:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC45:
	.xword	.LC44
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ResetChanWithOption
	.type	CASE_ResetChanWithOption, %function
CASE_ResetChanWithOption:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L54
	ldr	x20, .LC48
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_ResetChanWithOption
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L53:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L54:
	ldr	x2, .LC46
	mov	w3, 194
	ldr	x1, .LC47
	mov	w0, 0
	add	x2, x2, 160
	mov	w19, -1
	bl	dprint_vfmw
	b	.L53
	.size	CASE_ResetChanWithOption, .-CASE_ResetChanWithOption
	.align	3
.LC46:
	.xword	.LANCHOR0
	.align	3
.LC47:
	.xword	.LC16
	.align	3
.LC48:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetChanConfig
	.type	CASE_GetChanConfig, %function
CASE_GetChanConfig:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L58
	ldr	x20, .LC51
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetChanCfg
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L57:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L58:
	ldr	x2, .LC49
	mov	w3, 249
	ldr	x1, .LC50
	mov	w0, 0
	add	x2, x2, 192
	mov	w19, -1
	bl	dprint_vfmw
	b	.L57
	.size	CASE_GetChanConfig, .-CASE_GetChanConfig
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC50:
	.xword	.LC16
	.align	3
.LC51:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ConfigChan
	.type	CASE_ConfigChan, %function
CASE_ConfigChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L63
	ldr	x20, .LC54
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_ConfigChan
	cbz	w0, .L64
.L62:
	ldr	x1, [x20, 32]
	cmp	w0, wzr
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L61:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L64:
	mov	w0, w21
	bl	VCTRL_LoadDspCode
	b	.L62
.L63:
	ldr	x2, .LC52
	mov	w3, 265
	ldr	x1, .LC53
	mov	w0, 0
	add	x2, x2, 216
	mov	w19, -1
	bl	dprint_vfmw
	b	.L61
	.size	CASE_ConfigChan, .-CASE_ConfigChan
	.align	3
.LC52:
	.xword	.LANCHOR0
	.align	3
.LC53:
	.xword	.LC16
	.align	3
.LC54:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetStreamIntf
	.type	CASE_SetStreamIntf, %function
CASE_SetStreamIntf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L68
	ldr	x20, .LC57
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_SetStreamInterface
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L67:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L68:
	ldr	x2, .LC55
	mov	w3, 316
	ldr	x1, .LC56
	mov	w0, 0
	add	x2, x2, 232
	mov	w19, -1
	bl	dprint_vfmw
	b	.L67
	.size	CASE_SetStreamIntf, .-CASE_SetStreamIntf
	.align	3
.LC55:
	.xword	.LANCHOR0
	.align	3
.LC56:
	.xword	.LC16
	.align	3
.LC57:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetStreamSize
	.type	CASE_GetStreamSize, %function
CASE_GetStreamSize:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L72
	ldr	x20, .LC60
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetStreamSize
	mov	w19, w0
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, w19
.L71:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L72:
	ldr	x2, .LC58
	mov	w3, 332
	ldr	x1, .LC59
	mov	w0, 0
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -1
	b	.L71
	.size	CASE_GetStreamSize, .-CASE_GetStreamSize
	.align	3
.LC58:
	.xword	.LANCHOR0
	.align	3
.LC59:
	.xword	.LC16
	.align	3
.LC60:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetChanIDByMem
	.type	CASE_GetChanIDByMem, %function
CASE_GetChanIDByMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L76
	ldr	x20, .LC63
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	ldr	w0, [x19]
	bl	VCTRL_GetChanIDByMemAddr
	str	w0, [x19]
	cmn	w0, #1
	mov	w0, 0
	ldr	x1, [x20, 32]
	csetm	w19, eq
	blr	x1
.L75:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L76:
	ldr	x2, .LC61
	mov	w3, 361
	ldr	x1, .LC62
	mov	w0, 0
	add	x2, x2, 280
	mov	w19, -1
	bl	dprint_vfmw
	b	.L75
	.size	CASE_GetChanIDByMem, .-CASE_GetChanIDByMem
	.align	3
.LC61:
	.xword	.LANCHOR0
	.align	3
.LC62:
	.xword	.LC16
	.align	3
.LC63:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetDiscardPicParam
	.type	CASE_SetDiscardPicParam, %function
CASE_SetDiscardPicParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L80
	ldr	x20, .LC66
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_SetDiscardPicParam
	mov	w19, w0
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, w19
.L79:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L80:
	ldr	x2, .LC64
	mov	w3, 378
	ldr	x1, .LC65
	mov	w0, 0
	add	x2, x2, 304
	bl	dprint_vfmw
	mov	w0, -1
	b	.L79
	.size	CASE_SetDiscardPicParam, .-CASE_SetDiscardPicParam
	.align	3
.LC64:
	.xword	.LANCHOR0
	.align	3
.LC65:
	.xword	.LC16
	.align	3
.LC66:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetPtsToSeek
	.type	CASE_SetPtsToSeek, %function
CASE_SetPtsToSeek:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L85
	ldr	x20, .LC69
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	str	wzr, [x29, 56]
	mov	w2, 1
	add	x1, x29, 48
	mov	w0, w22
	stp	w2, wzr, [x29, 48]
	bl	VCTRL_ResetChanWithOption
	cmp	w0, wzr
	csetm	w19, ne
	cbz	w19, .L86
.L84:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, w19
.L83:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L86:
	mov	x1, x21
	mov	w0, w22
	bl	VCTRL_SeekPts
	cmp	w0, wzr
	csetm	w19, ne
	b	.L84
.L85:
	ldr	x2, .LC67
	mov	w3, 395
	ldr	x1, .LC68
	mov	w0, 0
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L83
	.size	CASE_SetPtsToSeek, .-CASE_SetPtsToSeek
	.align	3
.LC67:
	.xword	.LANCHOR0
	.align	3
.LC68:
	.xword	.LC16
	.align	3
.LC69:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetTrickMode
	.type	CASE_SetTrickMode, %function
CASE_SetTrickMode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L90
	ldr	x20, .LC72
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_ConfigFFFBSpeed
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L89:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L90:
	ldr	x2, .LC70
	mov	w3, 421
	ldr	x1, .LC71
	mov	w0, 0
	add	x2, x2, 352
	mov	w19, -1
	bl	dprint_vfmw
	b	.L89
	.size	CASE_SetTrickMode, .-CASE_SetTrickMode
	.align	3
.LC70:
	.xword	.LANCHOR0
	.align	3
.LC71:
	.xword	.LC16
	.align	3
.LC72:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetCtrlInfo
	.type	CASE_SetCtrlInfo, %function
CASE_SetCtrlInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L94
	ldr	x20, .LC75
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_ConfigPVRInfo
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L93:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L94:
	ldr	x2, .LC73
	mov	w3, 437
	ldr	x1, .LC74
	mov	w0, 0
	add	x2, x2, 376
	mov	w19, -1
	bl	dprint_vfmw
	b	.L93
	.size	CASE_SetCtrlInfo, .-CASE_SetCtrlInfo
	.align	3
.LC73:
	.xword	.LANCHOR0
	.align	3
.LC74:
	.xword	.LC16
	.align	3
.LC75:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_AllocMemToDecoder
	.type	CASE_AllocMemToDecoder, %function
CASE_AllocMemToDecoder:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L102
	ldr	x20, .LC78
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_AllocMemToDecoder
	mov	w19, w0
	cbnz	w0, .L103
.L98:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, w19
.L97:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L103:
	ldr	x1, .LC80
	mov	w0, 1
	bl	dprint_vfmw
	b	.L98
.L102:
	ldr	x2, .LC76
	mov	w3, 462
	ldr	x1, .LC77
	mov	w0, 0
	add	x2, x2, 400
	bl	dprint_vfmw
	mov	w0, -1
	b	.L97
	.size	CASE_AllocMemToDecoder, .-CASE_AllocMemToDecoder
	.align	3
.LC76:
	.xword	.LANCHOR0
	.align	3
.LC77:
	.xword	.LC16
	.align	3
.LC78:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC80:
	.xword	.LC79
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_GetUserDecFrame
	.type	CASE_GetUserDecFrame, %function
CASE_GetUserDecFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L107
	ldr	x20, .LC83
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetUsrdecFrame
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L106:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L107:
	ldr	x2, .LC81
	mov	w3, 502
	ldr	x1, .LC82
	mov	w0, 0
	add	x2, x2, 424
	mov	w19, -1
	bl	dprint_vfmw
	b	.L106
	.size	CASE_GetUserDecFrame, .-CASE_GetUserDecFrame
	.align	3
.LC81:
	.xword	.LANCHOR0
	.align	3
.LC82:
	.xword	.LC16
	.align	3
.LC83:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_PutUserDecFrame
	.type	CASE_PutUserDecFrame, %function
CASE_PutUserDecFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L111
	ldr	x20, .LC86
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_PutUsrdecFrame
	cmp	w0, wzr
	ldr	x1, [x20, 32]
	mov	w0, 0
	csetm	w19, ne
	blr	x1
.L110:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L111:
	ldr	x2, .LC84
	mov	w3, 518
	ldr	x1, .LC85
	mov	w0, 0
	add	x2, x2, 448
	mov	w19, -1
	bl	dprint_vfmw
	b	.L110
	.size	CASE_PutUserDecFrame, .-CASE_PutUserDecFrame
	.align	3
.LC84:
	.xword	.LANCHOR0
	.align	3
.LC85:
	.xword	.LC16
	.align	3
.LC86:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_ReportOccupiedFrame
	.type	CASE_ReportOccupiedFrame, %function
CASE_ReportOccupiedFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L119
	mov	x1, x19
	mov	w0, w20
	bl	VCTRL_ReportOccupiedFrame
	mov	w19, w0
	cbnz	w0, .L120
.L115:
	cmp	w19, wzr
	csetm	w0, ne
.L114:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L120:
	ldr	x1, .LC90
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	b	.L115
.L119:
	ldr	x2, .LC87
	mov	w3, 562
	ldr	x1, .LC88
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, -1
	b	.L114
	.size	CASE_ReportOccupiedFrame, .-CASE_ReportOccupiedFrame
	.align	3
.LC87:
	.xword	.LANCHOR0
	.align	3
.LC88:
	.xword	.LC16
	.align	3
.LC90:
	.xword	.LC89
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_SetImageOutputInfo
	.type	CASE_SetImageOutputInfo, %function
CASE_SetImageOutputInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L128
	mov	x1, x19
	mov	w0, w20
	bl	VCTRL_ImageOutputEnable
	mov	w19, w0
	cbnz	w0, .L129
.L124:
	cmp	w19, wzr
	csetm	w0, ne
.L123:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L129:
	ldr	x1, .LC94
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	b	.L124
.L128:
	ldr	x2, .LC91
	mov	w3, 581
	ldr	x1, .LC92
	mov	w0, 0
	add	x2, x2, 504
	bl	dprint_vfmw
	mov	w0, -1
	b	.L123
	.size	CASE_SetImageOutputInfo, .-CASE_SetImageOutputInfo
	.align	3
.LC91:
	.xword	.LANCHOR0
	.align	3
.LC92:
	.xword	.LC16
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CASE_HandleEntry
	.type	CASE_HandleEntry, %function
CASE_HandleEntry:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 5
	beq	.L142
	ldr	x1, .LC96
	mov	w5, 1
	mov	w6, 24
	add	x1, x1, 528
	b	.L132
	.p2align 3
.L159:
	add	x0, x1, x0, lsl 3
	uxtw	x7, w5
	cmp	w20, w6
	lsl	x4, x7, 2
	sub	x4, x4, x7
	ldr	x6, [x0, 8]
	lsl	x4, x4, 3
	cbz	x6, .L133
	beq	.L134
	ldr	w6, [x1, x4]
.L132:
	uxtw	x4, w5
	cmp	w6, 37
	lsl	x0, x4, 2
	add	w5, w5, 1
	sub	x0, x0, x4
	bne	.L159
.L133:
	cmp	w20, 1
	ccmp	w20, 11, 4, ne
	beq	.L139
	cmp	w20, 12
	mov	x6, 0
	ccmp	w20, wzr, 4, ne
	cset	w0, ne
	cbz	w0, .L139
.L131:
	cmp	w21, 31
	bhi	.L138
	ldr	x0, .LC99
	ldr	x0, [x0, w21, sxtw 3]
	cbz	x0, .L138
	ldr	w0, [x0]
	cmp	w21, w0
	bne	.L138
	cbz	x6, .L139
.L141:
	mov	x1, x19
	mov	w0, w21
	blr	x6
.L160:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L134:
	cmp	w20, 1
	ccmp	w20, 11, 4, ne
	beq	.L141
	cmp	w20, wzr
	ccmp	w20, 12, 4, ne
	beq	.L141
	b	.L131
	.p2align 3
.L138:
	ldr	x1, .LC98
	mov	w3, w20
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L160
.L142:
	ldr	x6, .LC95
	b	.L131
.L139:
	ldr	x1, .LC101
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L160
	.size	CASE_HandleEntry, .-CASE_HandleEntry
	.align	3
.LC95:
	.xword	CASE_GetChanState
	.align	3
.LC96:
	.xword	.LANCHOR0
	.align	3
.LC98:
	.xword	.LC97
	.align	3
.LC99:
	.xword	s_pstVfmwChan
	.align	3
.LC101:
	.xword	.LC100
	.global	VDEC_CID_HandlerTable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11483, %object
	.size	__func__.11483, 18
__func__.11483:
	.string	"CASE_SetFrameRate"
	.zero	6
	.type	__func__.11495, %object
	.size	__func__.11495, 23
__func__.11495:
	.string	"CASE_SetFrameBufferNum"
	.zero	1
	.type	__func__.11514, %object
	.size	__func__.11514, 23
__func__.11514:
	.string	"CASE_StartLowDelayCalc"
	.zero	1
	.type	__func__.11356, %object
	.size	__func__.11356, 19
__func__.11356:
	.string	"CASE_GetCapability"
	.zero	5
	.type	__func__.11361, %object
	.size	__func__.11361, 21
__func__.11361:
	.string	"CASE_GetOutputFormat"
	.zero	3
	.type	__func__.11370, %object
	.size	__func__.11370, 20
__func__.11370:
	.string	"CASE_GetChanMemSize"
	.zero	4
	.type	__func__.11378, %object
	.size	__func__.11378, 16
__func__.11378:
	.string	"CASE_CreateChan"
	.type	__func__.11398, %object
	.size	__func__.11398, 25
__func__.11398:
	.string	"CASE_ResetChanWithOption"
	.zero	7
	.type	__func__.11414, %object
	.size	__func__.11414, 19
__func__.11414:
	.string	"CASE_GetChanConfig"
	.zero	5
	.type	__func__.11420, %object
	.size	__func__.11420, 16
__func__.11420:
	.string	"CASE_ConfigChan"
	.type	__func__.11435, %object
	.size	__func__.11435, 19
__func__.11435:
	.string	"CASE_SetStreamIntf"
	.zero	5
	.type	__func__.11441, %object
	.size	__func__.11441, 19
__func__.11441:
	.string	"CASE_GetStreamSize"
	.zero	5
	.type	__func__.11452, %object
	.size	__func__.11452, 20
__func__.11452:
	.string	"CASE_GetChanIDByMem"
	.zero	4
	.type	__func__.11458, %object
	.size	__func__.11458, 24
__func__.11458:
	.string	"CASE_SetDiscardPicParam"
	.type	__func__.11466, %object
	.size	__func__.11466, 18
__func__.11466:
	.string	"CASE_SetPtsToSeek"
	.zero	6
	.type	__func__.11472, %object
	.size	__func__.11472, 18
__func__.11472:
	.string	"CASE_SetTrickMode"
	.zero	6
	.type	__func__.11478, %object
	.size	__func__.11478, 17
__func__.11478:
	.string	"CASE_SetCtrlInfo"
	.zero	7
	.type	__func__.11489, %object
	.size	__func__.11489, 23
__func__.11489:
	.string	"CASE_AllocMemToDecoder"
	.zero	1
	.type	__func__.11501, %object
	.size	__func__.11501, 21
__func__.11501:
	.string	"CASE_GetUserDecFrame"
	.zero	3
	.type	__func__.11507, %object
	.size	__func__.11507, 21
__func__.11507:
	.string	"CASE_PutUserDecFrame"
	.zero	3
	.type	__func__.11525, %object
	.size	__func__.11525, 25
__func__.11525:
	.string	"CASE_ReportOccupiedFrame"
	.zero	7
	.type	__func__.11532, %object
	.size	__func__.11532, 24
__func__.11532:
	.string	"CASE_SetImageOutputInfo"
	.type	VDEC_CID_HandlerTable, %object
	.size	VDEC_CID_HandlerTable, 768
VDEC_CID_HandlerTable:
	.word	5
	.zero	4
	.xword	CASE_GetChanState
	.word	100
	.zero	4
	.word	24
	.zero	4
	.xword	CASE_SetFrameRate
	.word	4
	.zero	4
	.word	0
	.zero	4
	.xword	CASE_GetCapability
	.word	148
	.zero	4
	.word	30
	.zero	4
	.xword	CASE_GetOutputFormat
	.word	16
	.zero	4
	.word	11
	.zero	4
	.xword	CASE_GetChanMemSize
	.word	128
	.zero	4
	.word	1
	.zero	4
	.xword	CASE_CreateChan
	.word	128
	.zero	4
	.word	2
	.zero	4
	.xword	CASE_DestroyChan
	.word	0
	.zero	4
	.word	8
	.zero	4
	.xword	CASE_ResetChan
	.word	0
	.zero	4
	.word	14
	.zero	4
	.xword	CASE_ResetChanWithOption
	.word	12
	.zero	4
	.word	3
	.zero	4
	.xword	CASE_GetChanConfig
	.word	140
	.zero	4
	.word	6
	.zero	4
	.xword	CASE_StartChan
	.word	0
	.zero	4
	.word	7
	.zero	4
	.xword	CASE_StopChan
	.word	0
	.zero	4
	.word	4
	.zero	4
	.xword	CASE_ConfigChan
	.word	140
	.zero	4
	.word	13
	.zero	4
	.xword	CASE_ReleaseStream
	.word	0
	.zero	4
	.word	9
	.zero	4
	.xword	CASE_SetStreamIntf
	.word	24
	.zero	4
	.word	10
	.zero	4
	.xword	CASE_GetStreamSize
	.word	4
	.zero	4
	.word	19
	.zero	4
	.xword	CASE_ExtraWakupThread
	.word	0
	.zero	4
	.word	12
	.zero	4
	.xword	CASE_GetChanIDByMem
	.word	4
	.zero	4
	.word	18
	.zero	4
	.xword	CASE_SetDiscardPicParam
	.word	8
	.zero	4
	.word	21
	.zero	4
	.xword	CASE_SetPtsToSeek
	.word	24
	.zero	4
	.word	22
	.zero	4
	.xword	CASE_SetTrickMode
	.word	4
	.zero	4
	.word	23
	.zero	4
	.xword	CASE_SetCtrlInfo
	.word	20
	.zero	4
	.word	28
	.zero	4
	.xword	CASE_AllocMemToDecoder
	.word	72
	.zero	4
	.word	29
	.zero	4
	.xword	CASE_SetFrameBufferNum
	.word	4
	.zero	4
	.word	31
	.zero	4
	.xword	CASE_ReportDemuxRelease
	.word	0
	.zero	4
	.word	16
	.zero	4
	.xword	CASE_GetUserDecFrame
	.word	72
	.zero	4
	.word	17
	.zero	4
	.xword	CASE_PutUserDecFrame
	.word	72
	.zero	4
	.word	25
	.zero	4
	.xword	CASE_StartLowDelayCalc
	.word	4
	.zero	4
	.word	26
	.zero	4
	.xword	CASE_StopLowDelayCalc
	.word	4
	.zero	4
	.word	35
	.zero	4
	.xword	CASE_ReportOccupiedFrame
	.word	536
	.zero	4
	.word	34
	.zero	4
	.xword	CASE_SetImageOutputInfo
	.word	4
	.zero	4
	.word	37
	.zero	4
	.xword	0
	.word	0
	.zero	4
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"Not care param %p\n" )
	.zero	5
.LC11:
	ASCII(.string	"Not care param %d %p\n" )
	.zero	2
.LC16:
	ASCII(.string	"invalid condition: %s %d\n" )
	.zero	6
.LC26:
	ASCII(.string	"Not care param %d\n" )
	.zero	5
.LC37:
	ASCII(.string	"call VCTRL_GetChanMemSize failed ret:%d\n" )
	.zero	7
.LC44:
	ASCII(.string	"VCTRT_SetChanCtrlState ERR: %d\n" )
.LC79:
	ASCII(.string	"VCTRL_AllocMemToDecoder failed!\n " )
	.zero	6
.LC89:
	ASCII(.string	"VCTRL_ReportOccupiedFrame[Chan %d] failed!\n" )
	.zero	4
.LC93:
	ASCII(.string	"VCTRL_ImageOutputEnable[Chan %d] failed!\n" )
	.zero	6
.LC97:
	ASCII(.string	"Chan id: %d is invalid, Cmd ID:%d\n" )
	.zero	5
.LC100:
	ASCII(.string	"Unsupport eCmdID %d\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
