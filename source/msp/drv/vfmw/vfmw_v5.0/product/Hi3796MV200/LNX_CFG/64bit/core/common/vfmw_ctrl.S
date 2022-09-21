#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vfmw_ctrl.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetPrintLevel, %function
VfmwProc_SetPrintLevel:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC0
	ldr	w1, [x19]
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetPrintLevel, .-VfmwProc_SetPrintLevel
	.align	3
.LC0:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_OpenScdLowdly, %function
VfmwProc_OpenScdLowdly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	mov	w1, 1
	ldr	x2, .LC1
	lsl	x0, x0, 4
	ldr	x0, [x2, x0]
	str	w1, [x0, 48]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_OpenScdLowdly, .-VfmwProc_OpenScdLowdly
	.align	3
.LC1:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_CloseScdLowdly, %function
VfmwProc_CloseScdLowdly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x1, .LC2
	lsl	x0, x0, 4
	ldr	x0, [x1, x0]
	str	wzr, [x0, 48]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_CloseScdLowdly, .-VfmwProc_CloseScdLowdly
	.align	3
.LC2:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	cmp	w19, 31
	bhi	.L16
	ldr	x4, .LC7
	ldr	x0, [x4, w19, sxtw 3]
	cbz	x0, .L17
	ldr	w3, [x0, 32]
	cbz	w3, .L9
	cmp	w3, 1
	bne	.L18
	ldr	x3, [x4, 576]
	cbz	x3, .L19
.L12:
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L18:
	ldr	x2, .LC14
	mov	w4, w22
	ldr	x1, .LC16
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L6:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L9:
	ldr	x3, [x4, 568]
	cbnz	x3, .L12
	ldr	x1, .LC11
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
	.p2align 3
.L16:
	ldr	x3, .LC4
	mov	w2, 980
	ldr	x1, .LC6
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
.L17:
	ldr	x3, .LC9
	mov	w2, 981
	ldr	x1, .LC6
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
.L19:
	ldr	x1, .LC13
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
	.size	VCTRL_EventReport, .-VCTRL_EventReport
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC6:
	.xword	.LC5
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	.LANCHOR1
	.align	3
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetStandardObedience, %function
VfmwProc_SetStandardObedience:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC17
	ldr	x1, .LC19
	mov	w2, w3
	str	w3, [x4, 600]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetStandardObedience, .-VfmwProc_SetStandardObedience
	.align	3
.LC17:
	.xword	.LANCHOR0
	.align	3
.LC19:
	.xword	.LC18
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetClkSelect, %function
VfmwProc_SetClkSelect:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 4
	bhi	.L22
	ldr	x0, .LC20
	str	w3, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L22:
	ldr	x2, .LC20
	mov	w0, 32
	ldr	x1, .LC22
	ldr	w2, [x2]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetClkSelect, .-VfmwProc_SetClkSelect
	.align	3
.LC20:
	.xword	.LANCHOR2
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetCompressPara, %function
VfmwProc_SetCompressPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC23
	mov	x2, 16
	ldp	w20, w21, [x19]
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x3, 96]
	ldp	w23, w22, [x19, 8]
	ldr	w19, [x19, 16]
	blr	x3
	cbz	w21, .L76
	cbz	w23, .L77
	mov	w0, 1
	cmp	w22, 625
	stp	w0, w0, [x29, 64]
	beq	.L71
	bls	.L78
	cmp	w22, 750
	beq	.L32
	cmp	w22, 875
	bne	.L34
	mov	w0, 3
	str	w0, [x29, 72]
.L34:
	cmp	w19, 625
	beq	.L36
	bls	.L79
	cmp	w19, 750
	beq	.L39
	cmp	w19, 875
	bne	.L35
	mov	w0, 3
	str	w0, [x29, 76]
.L35:
	mov	w4, 1
	ldr	x1, .LC29
	mov	w6, w19
	mov	w5, w22
	mov	w3, w4
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	b	.L26
	.p2align 3
.L76:
	ldr	x1, .LC25
	mov	w3, -1
	mov	w2, w20
	mov	w0, 32
	stp	wzr, wzr, [x29, 64]
	stp	w3, w3, [x29, 72]
	bl	dprint_vfmw
.L26:
	ldr	x0, .LC30
	sxtw	x2, w20
	ldr	x1, [x0, w20, sxtw 3]
	cbz	x1, .L80
.L42:
	ldr	x1, .LC40
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L77:
	mov	w6, 1
	ldr	x1, .LC27
	mov	w2, w20
	mov	w5, -1
	mov	w4, 0
	mov	w3, w6
	mov	w0, 32
	stp	w6, wzr, [x29, 64]
	stp	w5, w5, [x29, 72]
	bl	dprint_vfmw
	ldr	x0, .LC30
	sxtw	x2, w20
	ldr	x1, [x0, w20, sxtw 3]
	cbnz	x1, .L42
.L80:
	lsl	x4, x2, 4
	add	x3, x0, 608
	add	x0, x3, x4
	ldr	w5, [x29, 76]
	ldp	w7, w6, [x29, 68]
	ldr	x1, .LC32
	mov	w2, w20
	str	w5, [x0, 12]
	ldr	w5, [x29, 64]
	stp	w7, w6, [x0, 4]
	str	w5, [x3, x4]
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x29, 64]
	mov	w0, 32
	ldr	x1, .LC34
	bl	dprint_vfmw
	ldr	w2, [x29, 68]
	mov	w0, 32
	ldr	x1, .LC36
	bl	dprint_vfmw
	ldp	w2, w3, [x29, 72]
	ldr	x1, .LC38
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L78:
	cmp	w22, 500
	bne	.L34
	str	wzr, [x29, 72]
	b	.L34
	.p2align 3
.L32:
	mov	w0, 2
.L71:
	str	w0, [x29, 72]
	b	.L34
	.p2align 3
.L79:
	cmp	w19, 500
	bne	.L35
	str	wzr, [x29, 76]
	b	.L35
	.p2align 3
.L39:
	mov	w0, 2
	str	w0, [x29, 76]
	b	.L35
	.p2align 3
.L36:
	mov	w0, 1
	str	w0, [x29, 76]
	b	.L35
	.size	VfmwProc_SetCompressPara, .-VfmwProc_SetCompressPara
	.align	3
.LC23:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTunnelLineNumber, %function
VfmwProc_SetTunnelLineNumber:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC42
	ldr	x1, .LC44
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTunnelLineNumber, .-VfmwProc_SetTunnelLineNumber
	.align	3
.LC42:
	.xword	g_TunnelLineNumber
	.align	3
.LC44:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSaveYuvBitWidth, %function
VfmwProc_SetSaveYuvBitWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	and	w0, w3, -3
	cmp	w0, 8
	bne	.L85
	ldr	x4, .LC47
	mov	w2, w3
	ldr	x1, .LC49
	mov	w0, 32
	str	w3, [x4, 4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	ldr	x1, .LC46
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSaveYuvBitWidth, .-VfmwProc_SetSaveYuvBitWidth
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC47:
	.xword	.LANCHOR2
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceImgPeriod, %function
VfmwProc_SetTraceImgPeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC50
	ldr	x1, .LC52
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceImgPeriod, .-VfmwProc_SetTraceImgPeriod
	.align	3
.LC50:
	.xword	g_TraceImgPeriod
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceFramePeriod, %function
VfmwProc_SetTraceFramePeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC53
	ldr	x1, .LC55
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceFramePeriod, .-VfmwProc_SetTraceFramePeriod
	.align	3
.LC53:
	.xword	g_TraceFramePeriod
	.align	3
.LC55:
	.xword	.LC54
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceBSPeriod, %function
VfmwProc_SetTraceBSPeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC56
	ldr	x1, .LC58
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceBSPeriod, .-VfmwProc_SetTraceBSPeriod
	.align	3
.LC56:
	.xword	g_TraceBsPeriod
	.align	3
.LC58:
	.xword	.LC57
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceCtrl, %function
VfmwProc_SetTraceCtrl:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC59
	ldr	x1, .LC61
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceCtrl, .-VfmwProc_SetTraceCtrl
	.align	3
.LC59:
	.xword	g_TraceCtrl
	.align	3
.LC61:
	.xword	.LC60
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStopDec, %function
VfmwProc_TestStopDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC62
	ldr	x1, .LC64
	mov	w2, w3
	str	w3, [x4, 1120]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopDec, .-VfmwProc_TestStopDec
	.align	3
.LC62:
	.xword	.LANCHOR0
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestTimeSequence, %function
VfmwProc_TestTimeSequence:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC65
	ldr	x1, .LC67
	mov	w2, w3
	str	w3, [x4, 1124]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestTimeSequence, .-VfmwProc_TestTimeSequence
	.align	3
.LC65:
	.xword	.LANCHOR0
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveEL, %function
VfmwProc_SaveEL:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L92
	ldr	x21, .LC68
	add	x20, x21, 1128
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L97
	ldr	x1, .LC78
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC69
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L92:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L97:
	ldr	x22, .LC69
	mov	x1, 50
	ldr	w0, [x21, 1384]
	ldr	x3, .LC70
	mov	w4, w0
	ldr	x2, .LC72
	add	w0, w0, 1
	ldr	x5, [x22, 136]
	add	x3, x3, 8
	str	w0, [x21, 1384]
	add	x0, x29, 56
	blr	x5
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 56
	blr	x3
	str	w19, [x21, 1388]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L95
	ldr	x1, .LC74
	mov	w3, w19
	add	x2, x29, 56
	mov	w0, 32
	bl	dprint_vfmw
	b	.L92
	.p2align 3
.L95:
	ldr	x1, .LC76
	add	x2, x29, 56
	mov	w0, 32
	bl	dprint_vfmw
	b	.L92
	.size	VfmwProc_SaveEL, .-VfmwProc_SaveEL
	.align	3
.LC68:
	.xword	.LANCHOR0
	.align	3
.LC69:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC70:
	.xword	.LANCHOR2
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetCurProcChan, %function
VfmwProc_SetCurProcChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 32
	bhi	.L101
	ldr	x4, .LC82
	mov	w2, w3
	ldr	x1, .LC84
	mov	w0, 32
	str	w3, [x4, 1392]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L101:
	ldr	x1, .LC81
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetCurProcChan, .-VfmwProc_SetCurProcChan
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	.LANCHOR0
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSaveFileAfterReset, %function
VfmwProc_SetSaveFileAfterReset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 1
	bls	.L105
	ldr	x1, .LC89
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L105:
	ldr	x4, .LC85
	mov	w2, w3
	ldr	x1, .LC87
	mov	w0, 32
	str	w3, [x4, 1396]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSaveFileAfterReset, .-VfmwProc_SetSaveFileAfterReset
	.align	3
.LC85:
	.xword	.LANCHOR0
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetUSE_FF_APT_EN, %function
VfmwProc_SetUSE_FF_APT_EN:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 1
	bls	.L109
	ldr	x1, .LC94
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L109:
	ldr	x4, .LC90
	mov	w2, w3
	ldr	x1, .LC92
	mov	w0, 32
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetUSE_FF_APT_EN, .-VfmwProc_SetUSE_FF_APT_EN
	.align	3
.LC90:
	.xword	USE_FF_APT_EN
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetVp9DecFrameNum, %function
VfmwProc_SetVp9DecFrameNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC95
	ldr	x1, .LC97
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetVp9DecFrameNum, .-VfmwProc_SetVp9DecFrameNum
	.align	3
.LC95:
	.xword	g_CfgVp9FrmNum
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDefaultOutputOrder, %function
VfmwProc_SetDefaultOutputOrder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 7
	bhi	.L114
	ldr	x1, .LC101
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, .LC102
	str	w19, [x0, 72]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	ldr	x1, .LC99
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetDefaultOutputOrder, .-VfmwProc_SetDefaultOutputOrder
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC102:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_0
	.type	VCTRL_Isr_0, %function
VCTRL_Isr_0:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_0, .-VCTRL_Isr_0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr
	.type	VCTRL_Scd_Isr, %function
VCTRL_Scd_Isr:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr, .-VCTRL_Scd_Isr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_MMU_ISR
	.type	VCTRL_MMU_ISR, %function
VCTRL_MMU_ISR:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_MMUIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_MMU_ISR, .-VCTRL_MMU_ISR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveReorderMetadata, %function
VfmwProc_SaveReorderMetadata:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L118
	ldr	x21, .LC103
	add	x20, x21, 1400
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L123
	ldr	x1, .LC111
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC104
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L118:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L123:
	ldr	x22, .LC104
	mov	w0, 24
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 1656]
	mov	x2, x0
	ldr	x3, .LC105
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 1656]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 1660]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L121
	ldr	x1, .LC107
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L118
	.p2align 3
.L121:
	ldr	x1, .LC109
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L118
	.size	VfmwProc_SaveReorderMetadata, .-VfmwProc_SaveReorderMetadata
	.align	3
.LC103:
	.xword	.LANCHOR0
	.align	3
.LC104:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC105:
	.xword	.LANCHOR2
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveMetadata, %function
VfmwProc_SaveMetadata:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bls	.L130
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L130:
	ldr	x20, .LC113
	mov	w1, w19
	mov	w0, 2
	ldr	x2, [x20, 48]
	blr	x2
	ldr	x22, .LC114
	add	x21, x22, 1664
	ldr	x0, [x21, w19, uxtw 3]
	cbz	x0, .L131
	ldr	x1, .LC120
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, [x21, w19, uxtw 3]
	ldr	x1, [x20, 72]
	blr	x1
	str	xzr, [x21, w19, uxtw 3]
.L129:
	ldr	x2, [x20, 56]
	mov	w1, w19
	mov	w0, 2
	blr	x2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L131:
	mov	w0, 23
	ldr	x23, [x20, 136]
	bl	VFMW_GetString
	mov	x2, x0
	ldr	w1, [x22, 1920]
	add	x0, x29, 72
	ldr	x3, .LC115
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x22, 1920]
	mov	x1, 50
	blr	x23
	ldr	x3, [x20, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x22, 1924]
	str	x0, [x21, w19, uxtw 3]
	cbz	x0, .L127
	ldr	x1, .LC117
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L129
.L127:
	ldr	x1, .LC119
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L129
	.size	VfmwProc_SaveMetadata, .-VfmwProc_SaveMetadata
	.align	3
.LC113:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LANCHOR2
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC120:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_Save1DYUV, %function
VfmwProc_Save1DYUV:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC122
	ldp	w21, w23, [x20]
	ldr	w24, [x20, 8]
	ldr	x1, [x19, 408]
	mov	w0, w21
	blr	x1
	mov	x20, x0
	cbz	x0, .L138
	mov	w0, 22
	ldr	x22, [x19, 136]
	bl	VFMW_GetString
	mov	x2, x0
	ldr	x3, .LC125
	mov	w4, w21
	mov	x1, 50
	add	x0, x29, 72
	add	x3, x3, 8
	blr	x22
	ldr	x3, [x19, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	mov	x21, x0
	cbz	x0, .L135
	ldr	x1, .LC126
	ldr	x5, [x1, 296]
	cbz	x5, .L136
	mov	w4, 1
	mov	w3, w24
	mov	w2, w23
	mov	x1, x20
	blr	x5
.L137:
	ldr	x1, [x19, 72]
	mov	x0, x21
	blr	x1
	ldr	x1, .LC130
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
.L134:
	ldr	x1, [x19, 312]
	mov	x0, x20
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L136:
	ldr	x1, .LC128
	mov	w2, 7391
	mov	w0, 0
	bl	dprint_vfmw
	b	.L137
	.p2align 3
.L138:
	ldr	x1, .LC124
	mov	w2, w21
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, [x19, 312]
	mov	x0, x20
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L135:
	ldr	x1, .LC132
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L134
	.size	VfmwProc_Save1DYUV, .-VfmwProc_Save1DYUV
	.align	3
.LC122:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC125:
	.xword	.LANCHOR2
	.align	3
.LC126:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveSeg, %function
VfmwProc_SaveSeg:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L139
	ldr	x21, .LC133
	add	x20, x21, 1928
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L144
	ldr	x1, .LC141
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC134
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L139:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L144:
	ldr	x22, .LC134
	mov	w0, 19
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 2184]
	mov	x2, x0
	ldr	x3, .LC135
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 2184]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 2188]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L142
	ldr	x1, .LC137
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L139
	.p2align 3
.L142:
	ldr	x1, .LC139
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L139
	.size	VfmwProc_SaveSeg, .-VfmwProc_SaveSeg
	.align	3
.LC133:
	.xword	.LANCHOR0
	.align	3
.LC134:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC135:
	.xword	.LANCHOR2
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_Savestream, %function
VfmwProc_Savestream:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L145
	ldr	x21, .LC143
	add	x20, x21, 2192
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L150
	ldr	x1, .LC151
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC144
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L145:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L150:
	ldr	x22, .LC144
	mov	w0, 18
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 2448]
	mov	x2, x0
	ldr	x3, .LC145
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 2448]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 2452]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L148
	ldr	x1, .LC147
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L145
	.p2align 3
.L148:
	ldr	x1, .LC149
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L145
	.size	VfmwProc_Savestream, .-VfmwProc_Savestream
	.align	3
.LC143:
	.xword	.LANCHOR0
	.align	3
.LC144:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC145:
	.xword	.LANCHOR2
	.align	3
.LC147:
	.xword	.LC146
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveYUV, %function
VfmwProc_SaveYUV:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19]
	cmp	w20, 31
	bls	.L161
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L161:
	ldr	x21, .LC153
	mov	w1, w20
	mov	w0, 2
	ldr	x2, [x21, 48]
	blr	x2
	ldr	x19, .LC154
	add	x22, x19, 2456
	ldr	x0, [x22, w20, uxtw 3]
	cbz	x0, .L162
	ldr	x1, .LC163
	mov	w0, 32
	add	x23, x19, 2720
	bl	dprint_vfmw
	ldr	x0, [x22, w20, uxtw 3]
	ldr	x1, [x21, 72]
	blr	x1
	str	xzr, [x22, w20, uxtw 3]
	ldr	x1, .LC155
	mov	w2, -1
	ldr	w0, [x19, 2736]
	str	w2, [x1, 76]
	add	x1, x19, 2560
	stp	xzr, xzr, [x1, 192]
	stp	xzr, xzr, [x1, 208]
	str	xzr, [x19, 2784]
	str	xzr, [x19, 2792]
	str	wzr, [x19, 2800]
	str	xzr, [x19, 2808]
	cbnz	w0, .L163
.L157:
	ldr	x2, [x21, 56]
	mov	w1, w20
	mov	w0, 2
	blr	x2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L163:
	ldr	x1, [x19, 2728]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x19, 2744]
	ldr	x1, [x19, 2728]
	ldr	w0, [x19, 2736]
	bl	MEM_DelMemRecord
	ldr	x3, [x21, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	b	.L157
	.p2align 3
.L162:
	mov	w0, 20
	ldr	x23, [x21, 136]
	bl	VFMW_GetString
	ldr	x24, .LC155
	ldr	w1, [x19, 2712]
	mov	x2, x0
	add	x3, x24, 8
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	str	w1, [x19, 2712]
	mov	x1, 100
	blr	x23
	ldr	x3, [x21, 64]
	mov	w2, 0
	mov	w1, 578
	add	x0, x29, 72
	blr	x3
	str	x0, [x22, w20, uxtw 3]
	cbz	x0, .L154
	add	x23, x19, 2720
	ldr	x3, [x21, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	mov	w1, 3
	mov	w0, 27
	str	w1, [x23, 28]
	bl	VFMW_GetString
	mov	w4, 0
	mov	x3, x23
	mov	w2, 47185920
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbz	w0, .L155
	ldr	x1, .LC157
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x22, w20, uxtw 3]
	ldr	x1, [x21, 72]
	blr	x1
	str	xzr, [x22, w20, uxtw 3]
	add	x2, x19, 2560
	mov	w0, -1
	stp	xzr, xzr, [x2, 192]
	stp	xzr, xzr, [x2, 208]
	str	xzr, [x19, 2784]
	str	xzr, [x19, 2792]
	str	wzr, [x19, 2800]
	str	w0, [x24, 76]
	b	.L157
.L154:
	ldr	x1, .LC161
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L157
	.p2align 3
.L155:
	ldr	w2, [x23, 24]
	ldr	x1, [x23, 8]
	ldr	w0, [x23, 16]
	bl	MEM_AddMemRecord
	ldr	x5, [x23, 8]
	lsr	w1, w20, 24
	mov	x0, 23592960
	and	w7, w20, 3
	add	x6, x5, 9437184
	str	x6, [x19, 2760]
	mov	x6, 25952256
	add	x0, x5, x0
	add	x6, x5, x6
	str	x6, [x19, 2776]
	mov	x6, 28311552
	mov	w3, w1
	add	x6, x5, x6
	str	w1, [x24, 76]
	ldr	x1, .LC159
	mov	w4, w7
	str	x5, [x19, 2768]
	add	x2, x29, 72
	str	x0, [x19, 2784]
	mov	w0, 32
	str	x6, [x19, 2808]
	add	x6, x5, 11796480
	add	x5, x5, 14155776
	str	w7, [x19, 2800]
	str	x6, [x19, 2752]
	str	x5, [x19, 2792]
	bl	dprint_vfmw
	b	.L157
	.size	VfmwProc_SaveYUV, .-VfmwProc_SaveYUV
	.align	3
.LC153:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC154:
	.xword	.LANCHOR0
	.align	3
.LC155:
	.xword	.LANCHOR2
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC163:
	.xword	.LC162
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetScdPrint, %function
VfmwProc_SetScdPrint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC166
	ldr	w0, [x20]
	mov	w2, 67108864
	mov	w1, 1
	ldr	w20, [x19]
	str	w2, [x19]
	bl	PrintScdRawState
	str	w20, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetScdPrint, .-VfmwProc_SetScdPrint
	.align	3
.LC166:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_PrintTracer, %function
VfmwProc_PrintTracer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC168
	mov	w0, 32
	ldr	w19, [x19]
	bl	dprint_vfmw
	mov	w0, w19
	bl	DBG_PrintTracer
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_PrintTracer, .-VfmwProc_PrintTracer
	.align	3
.LC168:
	.xword	.LC167
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSmmuIrqEnable, %function
VfmwProc_SetSmmuIrqEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cbnz	w0, .L166
	ldr	x19, .LC169
	ldr	w0, [x19, 80]
	cmp	w0, 1
	beq	.L169
	ldr	x1, .LC173
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x19, 80]
.L166:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L169:
	ldr	x1, .LC171
	mov	w0, 32
	bl	dprint_vfmw
	str	wzr, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSmmuIrqEnable, .-VfmwProc_SetSmmuIrqEnable
	.align	3
.LC169:
	.xword	.LANCHOR2
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSedOnlyEnable, %function
VfmwProc_SetSedOnlyEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x2, .LC174
	cbz	w0, .L173
	ldr	x1, .LC178
	mov	w3, 1
	mov	w0, 32
	str	w3, [x2, 84]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L173:
	ldr	x1, .LC176
	mov	w0, 32
	str	wzr, [x2, 84]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSedOnlyEnable, .-VfmwProc_SetSedOnlyEnable
	.align	3
.LC174:
	.xword	.LANCHOR2
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_OpenModuleLowly, %function
VfmwProc_OpenModuleLowly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 31
	bhi	.L177
	ldr	x5, .LC181
	mov	w2, w3
	ldr	x1, .LC182
	mov	w4, 1
	mov	w0, 32
	ldr	x3, [x5, w3, uxtw 3]
	str	w4, [x3, 1272]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L177:
	ldr	x1, .LC180
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_OpenModuleLowly, .-VfmwProc_OpenModuleLowly
	.align	3
.LC180:
	.xword	.LC179
	.align	3
.LC181:
	.xword	.LANCHOR0
	.align	3
.LC182:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_StopTask.part.9, %function
VCTRL_StopTask.part.9:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC183
	ldr	w0, [x20, 260]
	cmp	w0, 1
	beq	.L181
	ldr	x21, .LC184
	mov	w0, 10
	mov	w19, 49
	ldr	x1, [x21, 240]
	blr	x1
	b	.L182
	.p2align 3
.L189:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L188
.L182:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cmp	w1, 1
	bne	.L189
.L181:
	str	wzr, [x20, 264]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L188:
	str	wzr, [x20, 264]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StopTask.part.9, .-VCTRL_StopTask.part.9
	.align	3
.LC183:
	.xword	.LANCHOR0
	.align	3
.LC184:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_StartTask.part.10, %function
VCTRL_StartTask.part.10:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC185
	ldr	w0, [x20, 260]
	cmp	w0, 2
	beq	.L193
	ldr	x21, .LC186
	mov	w0, 10
	mov	w19, 49
	ldr	x1, [x21, 240]
	blr	x1
	b	.L194
	.p2align 3
.L201:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L200
.L194:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cmp	w1, 2
	bne	.L201
.L193:
	str	wzr, [x20, 264]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L200:
	str	wzr, [x20, 264]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StartTask.part.10, .-VCTRL_StartTask.part.10
	.align	3
.LC185:
	.xword	.LANCHOR0
	.align	3
.LC186:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_SetSendStreamAgainFlag.part.11, %function
VCTRL_SetSendStreamAgainFlag.part.11:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC187
	mov	w2, 1290
	ldr	x1, .LC188
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_SetSendStreamAgainFlag.part.11, .-VCTRL_SetSendStreamAgainFlag.part.11
	.align	3
.LC187:
	.xword	.LC8
	.align	3
.LC188:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_CanBeDecodedByHardWare.part.20, %function
VCTRL_CanBeDecodedByHardWare.part.20:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sub	w0, w19, #19
	cmp	w0, 1
	ccmp	w19, 14, 4, hi
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CanBeDecodedByHardWare.part.20, .-VCTRL_CanBeDecodedByHardWare.part.20
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_CloseModuleLowly, %function
VfmwProc_CloseModuleLowly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 31
	bhi	.L207
	ldr	x4, .LC190
	mov	w2, w3
	ldr	x1, .LC191
	mov	w0, 32
	ldr	x3, [x4, w3, uxtw 3]
	str	wzr, [x3, 1272]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L207:
	ldr	x1, .LC189
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_CloseModuleLowly, .-VfmwProc_CloseModuleLowly
	.align	3
.LC189:
	.xword	.LC179
	.align	3
.LC190:
	.xword	.LANCHOR0
	.align	3
.LC191:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC192
	ldr	x0, [x21]
	blr	x0
	ldr	x24, .LC193
	mov	w25, w0
	ldr	x1, [x24]
	cbz	x1, .L209
	mov	w0, 0
	blr	x1
.L210:
	mov	w0, 0
	mov	w20, 32
	mov	w22, 0
	mov	w19, 0
	bl	SCDDRV_PrepareSleep
	mov	w0, 0
	bl	VDMDRV_PrepareSleep
	ldr	x0, [x21]
	blr	x0
	mov	w26, w0
	b	.L221
	.p2align 3
.L211:
	bl	VDMDRV_GetSleepStage
	cmp	w0, 2
	mov	w19, 1
	mov	w23, w19
	beq	.L214
.L245:
	tst	w23, w22
	mov	w0, 10
	bne	.L214
	subs	w20, w20, #1
	beq	.L246
	ldr	x1, [x21, 240]
	blr	x1
	cmp	w19, 1
	ccmp	w22, 1, 0, eq
	beq	.L214
.L221:
	mov	w0, 0
	bl	SCDDRV_GetSleepStage
	cmp	w0, 2
	mov	w0, 0
	beq	.L211
	bl	VDMDRV_GetSleepStage
	cmp	w0, 2
	mov	w23, w19
	bne	.L245
	mov	w22, 1
	b	.L245
	.p2align 3
.L246:
	ldr	x0, [x21]
	blr	x0
	cmp	w26, w0
	sub	w2, w0, w26
	bls	.L217
	mvn	w26, w26
	add	w2, w26, w0
.L217:
	ldr	x1, .LC196
	mov	w4, w22
	mov	w3, w19
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w19, .L233
	ldr	x1, .LC202
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ForceSleep
.L233:
	cbnz	w22, .L214
	ldr	x1, .LC204
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	bl	VDMDRV_ForceSleep
.L214:
	ldr	x0, .LC197
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L247
.L223:
	ldr	x0, .LC198
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	beq	.L248
.L230:
	ldr	x0, [x21]
	blr	x0
	cmp	w25, w0
	sub	w2, w0, w25
	bls	.L232
	mvn	w25, w25
	add	w2, w25, w0
.L232:
	ldr	x1, .LC200
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L247:
	ldr	x1, [x24, 64]
	cbz	x1, .L224
	mov	w0, 0
	blr	x1
.L224:
	ldr	x1, [x24, 48]
	cbz	x1, .L225
	mov	w0, 0
	blr	x1
	ldr	x1, [x24, 16]
	cbz	x1, .L227
.L249:
	mov	w0, 0
	blr	x1
.L228:
	ldr	x1, [x24, 80]
	cbz	x1, .L223
	mov	w0, 0
	blr	x1
	ldr	x0, .LC198
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L230
	.p2align 2
.L248:
	mov	w0, 2
	str	w0, [x1, 8]
	bl	VCTRL_StopTask.part.9
	b	.L230
.L225:
	ldr	x1, .LC194
	mov	w2, 387
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x24, 16]
	cbnz	x1, .L249
	.p2align 2
.L227:
	ldr	x1, .LC194
	mov	w2, 392
	mov	w0, 0
	bl	dprint_vfmw
	b	.L228
	.p2align 3
.L209:
	ldr	x1, .LC194
	mov	w2, 289
	mov	w0, 0
	bl	dprint_vfmw
	b	.L210
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	3
.LC192:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC193:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC194:
	.xword	.LC127
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC197:
	.xword	g_HalDisable
	.align	3
.LC198:
	.xword	.LANCHOR0
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC204:
	.xword	.LC203
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestSuspend, %function
VfmwProc_TestSuspend:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC207
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	bl	VCTRL_Suspend
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestSuspend, .-VfmwProc_TestSuspend
	.align	3
.LC207:
	.xword	.LC206
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC208
	ldr	x0, [x20]
	blr	x0
	mov	w19, w0
	ldr	x0, .LC209
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L271
.L252:
	mov	w0, 0
	bl	SCDDRV_ExitSleep
	mov	w0, 0
	bl	VDMDRV_ExitSleep
	ldr	x0, .LC212
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	beq	.L272
.L262:
	ldr	x0, [x20]
	blr	x0
	cmp	w19, w0
	sub	w2, w0, w19
	bls	.L264
	mvn	w2, w19
	add	w2, w2, w0
.L264:
	ldr	x1, .LC214
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L271:
	ldr	x21, .LC210
	ldr	x1, [x21, 8]
	cbz	x1, .L273
	mov	w0, 0
	blr	x1
.L254:
	ldr	x1, [x21, 40]
	cbz	x1, .L274
	mov	w0, 0
	blr	x1
.L256:
	ldr	x1, [x21, 56]
	cbz	x1, .L257
	mov	w0, 0
	blr	x1
.L257:
	ldr	x1, [x21, 72]
	cbz	x1, .L258
	mov	w0, 0
	blr	x1
.L258:
	ldr	x1, [x21, 136]
	cbz	x1, .L259
	mov	w0, 0
	blr	x1
.L260:
	ldr	x0, [x21, 144]
	cbz	x0, .L261
	blr	x0
	b	.L252
	.p2align 3
.L272:
	str	w0, [x1, 8]
	bl	VCTRL_StartTask.part.10
	b	.L262
	.p2align 3
.L274:
	ldr	x1, .LC211
	mov	w2, 435
	mov	w0, 0
	bl	dprint_vfmw
	b	.L256
	.p2align 3
.L259:
	ldr	x1, .LC211
	mov	w2, 442
	mov	w0, 0
	bl	dprint_vfmw
	b	.L260
	.p2align 3
.L261:
	ldr	x1, .LC211
	mov	w2, 443
	mov	w0, 0
	bl	dprint_vfmw
	b	.L252
	.p2align 3
.L273:
	ldr	x1, .LC211
	mov	w2, 430
	mov	w0, 0
	bl	dprint_vfmw
	b	.L254
	.size	VCTRL_Resume, .-VCTRL_Resume
	.align	3
.LC208:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC209:
	.xword	g_HalDisable
	.align	3
.LC210:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC211:
	.xword	.LC127
	.align	3
.LC212:
	.xword	.LANCHOR0
	.align	3
.LC214:
	.xword	.LC213
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestResume, %function
VfmwProc_TestResume:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC216
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	bl	VCTRL_Resume
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResume, .-VfmwProc_TestResume
	.align	3
.LC216:
	.xword	.LC206
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ChanCtx_Init
	.type	ChanCtx_Init, %function
ChanCtx_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC220
	ldr	x0, .LC219
	mov	x2, 384
	mov	w1, 0
	ldr	x3, [x0, 96]
	mov	x0, x19
	blr	x3
	add	x0, x19, 128
	add	x1, x19, 256
	mov	w2, -1
	.p2align 2
.L277:
	str	w2, [x0], 4
	cmp	x0, x1
	bne	.L277
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ChanCtx_Init, .-ChanCtx_Init
	.align	3
.LC219:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC220:
	.xword	g_ChanCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RecordPosTime
	.type	VCTRL_RecordPosTime, %function
VCTRL_RecordPosTime:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 11
	bhi	.L285
	ldr	x22, .LC226
	uxtw	x20, w21
	ldrb	w0, [x22, x20]
	cmp	w0, 14
	mov	w19, w0
	bhi	.L286
	cmp	w21, 10
	beq	.L287
.L284:
	ldr	x0, .LC228
	ldr	x0, [x0, 8]
	blr	x0
	lsl	x1, x20, 4
	ldr	x2, .LC229
	sub	x1, x1, x20
	add	x19, x1, x19, sxtw
	ldrb	w1, [x22, x20]
	add	w1, w1, 1
	strb	w1, [x22, x20]
	str	w0, [x2, x19, lsl 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L286:
	strb	wzr, [x22, x20]
	cmp	w21, 10
	mov	w19, 0
	bne	.L284
.L287:
	ldr	x0, .LC227
	mov	w1, 1
	strb	w1, [x0, 2816]
	b	.L284
	.p2align 3
.L285:
	ldr	x2, .LC223
	mov	w4, w21
	ldr	x1, .LC225
	mov	w3, 693
	add	x2, x2, 24
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_RecordPosTime, .-VCTRL_RecordPosTime
	.align	3
.LC223:
	.xword	.LANCHOR1
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC226:
	.xword	g_TimeRecId
	.align	3
.LC227:
	.xword	.LANCHOR0
	.align	3
.LC228:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC229:
	.xword	g_TimeRecTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RecordData
	.type	VCTRL_RecordData, %function
VCTRL_RecordData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	uxtw	x19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 1
	bhi	.L293
	ldr	x3, .LC233
	ldrb	w0, [x3, x19]
	cmp	w0, 14
	bhi	.L292
	add	w4, w0, 1
	uxtb	w4, w4
.L291:
	lsl	x2, x19, 4
	ldr	x1, .LC234
	sub	x2, x2, x19
	strb	w4, [x3, x19]
	add	x0, x2, x0, sxtw
	str	w20, [x1, x0, lsl 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L292:
	mov	w4, 1
	mov	w0, 0
	b	.L291
	.p2align 3
.L293:
	ldr	x2, .LC230
	mov	w4, w19
	ldr	x1, .LC232
	mov	w3, 717
	add	x2, x2, 48
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_RecordData, .-VCTRL_RecordData
	.align	3
.LC230:
	.xword	.LANCHOR1
	.align	3
.LC232:
	.xword	.LC231
	.align	3
.LC233:
	.xword	g_DataRecId
	.align	3
.LC234:
	.xword	g_DataTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_1
	.type	VCTRL_Isr_1, %function
VCTRL_Isr_1:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_1, .-VCTRL_Isr_1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_2
	.type	VCTRL_Isr_2, %function
VCTRL_Isr_2:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 2
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_2, .-VCTRL_Isr_2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr_1
	.type	VCTRL_Scd_Isr_1, %function
VCTRL_Scd_Isr_1:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr_1, .-VCTRL_Scd_Isr_1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr_2
	.type	VCTRL_Scd_Isr_2, %function
VCTRL_Scd_Isr_2:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 2
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr_2, .-VCTRL_Scd_Isr_2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_InformVdmFree
	.type	VCTRL_InformVdmFree, %function
VCTRL_InformVdmFree:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC235
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_InformVdmFree, .-VCTRL_InformVdmFree
	.align	3
.LC235:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ExtraWakeUpThread
	.type	VCTRL_ExtraWakeUpThread, %function
VCTRL_ExtraWakeUpThread:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC236
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_ExtraWakeUpThread, .-VCTRL_ExtraWakeUpThread
	.align	3
.LC236:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetMoreGapEnable
	.type	VCTRL_SetMoreGapEnable, %function
VCTRL_SetMoreGapEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L306
	ldr	x0, .LC240
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L307
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L308
	cmp	w20, 1
	bhi	.L305
	str	w20, [x0, 1256]
	mov	w0, 0
.L302:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L305:
	str	wzr, [x0, 1256]
	mov	w0, -1
	b	.L302
	.p2align 3
.L308:
	ldr	x3, .LC243
	mov	w2, 905
	ldr	x1, .LC239
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L302
	.p2align 3
.L306:
	ldr	x3, .LC238
	mov	w2, 903
	ldr	x1, .LC239
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L302
.L307:
	ldr	x3, .LC241
	mov	w2, 904
	ldr	x1, .LC239
	bl	dprint_vfmw
	mov	w0, -1
	b	.L302
	.size	VCTRL_SetMoreGapEnable, .-VCTRL_SetMoreGapEnable
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC239:
	.xword	.LC5
	.align	3
.LC240:
	.xword	.LANCHOR0
	.align	3
.LC241:
	.xword	.LC8
	.align	3
.LC243:
	.xword	.LC242
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetCallBack
	.type	VCTRL_SetCallBack, %function
VCTRL_SetCallBack:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L317
	cbz	w19, .L313
	cmp	w19, 1
	beq	.L314
	ldr	x2, .LC248
	mov	w3, w19
	ldr	x1, .LC250
	mov	w0, 0
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
.L311:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L314:
	ldr	x1, .LC247
	mov	w0, 0
	str	x20, [x1, 576]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L313:
	ldr	x1, .LC247
	mov	w0, 0
	str	x20, [x1, 568]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L317:
	ldr	x3, .LC245
	mov	w2, 1022
	ldr	x1, .LC246
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L311
	.size	VCTRL_SetCallBack, .-VCTRL_SetCallBack
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC246:
	.xword	.LC5
	.align	3
.LC247:
	.xword	.LANCHOR0
	.align	3
.LC248:
	.xword	.LANCHOR1
	.align	3
.LC250:
	.xword	.LC249
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopTask
	.type	VCTRL_StopTask, %function
VCTRL_StopTask:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC251
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L320
	mov	w0, 2
	str	w0, [x1, 8]
	bl	VCTRL_StopTask.part.9
.L319:
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L320:
	mov	w0, -1
	b	.L319
	.size	VCTRL_StopTask, .-VCTRL_StopTask
	.align	3
.LC251:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StartTask
	.type	VCTRL_StartTask, %function
VCTRL_StartTask:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC253
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L323
	str	w0, [x1, 8]
	bl	VCTRL_StartTask.part.10
.L322:
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L323:
	mov	w0, -1
	b	.L322
	.size	VCTRL_StartTask, .-VCTRL_StartTask
	.align	3
.LC253:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetStreamInterface
	.type	VCTRL_SetStreamInterface, %function
VCTRL_SetStreamInterface:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L328
	ldr	x19, .LC258
	sxtw	x22, w21
	ldr	x0, [x19, w21, sxtw 3]
	cbz	x0, .L329
	ldr	x21, .LC260
	mov	x2, 24
	mov	x1, x20
	add	x0, x0, 184
	add	x19, x19, 2824
	ldr	x3, [x21, 104]
	blr	x3
	lsl	x0, x22, 2
	ldr	x3, [x21, 104]
	sub	x0, x0, x22
	mov	x2, 24
	mov	x1, x20
	add	x0, x19, x0, lsl 3
	blr	x3
	mov	w0, 0
.L326:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L329:
	ldr	x3, .LC259
	mov	w2, 1279
	ldr	x1, .LC257
	bl	dprint_vfmw
	mov	w0, -1
	b	.L326
.L328:
	ldr	x3, .LC256
	mov	w2, 1278
	ldr	x1, .LC257
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L326
	.size	VCTRL_SetStreamInterface, .-VCTRL_SetStreamInterface
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC257:
	.xword	.LC5
	.align	3
.LC258:
	.xword	.LANCHOR0
	.align	3
.LC259:
	.xword	.LC8
	.align	3
.LC260:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetSendStreamAgainFlag
	.type	VCTRL_SetSendStreamAgainFlag, %function
VCTRL_SetSendStreamAgainFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC262
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L333
	add	x2, x0, 503808
	mov	w0, 0
	str	w20, [x2, 1316]
.L332:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L333:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L332
	.size	VCTRL_SetSendStreamAgainFlag, .-VCTRL_SetSendStreamAgainFlag
	.align	3
.LC262:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetSendStreamAgainFlag
	.type	VCTRL_GetSendStreamAgainFlag, %function
VCTRL_GetSendStreamAgainFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC263
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L337
	add	x0, x0, 503808
	ldr	w0, [x0, 1316]
.L336:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L337:
	ldr	x3, .LC264
	mov	w2, 1297
	ldr	x1, .LC265
	bl	dprint_vfmw
	mov	w0, -1
	b	.L336
	.size	VCTRL_GetSendStreamAgainFlag, .-VCTRL_GetSendStreamAgainFlag
	.align	3
.LC263:
	.xword	.LANCHOR0
	.align	3
.LC264:
	.xword	.LC8
	.align	3
.LC265:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetStreamInterface
	.type	VCTRL_GetStreamInterface, %function
VCTRL_GetStreamInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC266
	sxtw	x2, w19
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L341
	ldr	x3, .LC267
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x4, x20, 2824
	mov	x2, 24
	add	x1, x1, 184
	ldr	x3, [x3, 120]
	add	x0, x4, x0, lsl 3
	blr	x3
	cbnz	w0, .L342
	ldr	x0, [x20, w19, sxtw 3]
	add	x0, x0, 184
.L339:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L341:
	mov	x0, 0
	b	.L339
	.p2align 3
.L342:
	ldr	x1, .LC269
	mov	w3, w19
	mov	w2, 1313
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, 0
	b	.L339
	.size	VCTRL_GetStreamInterface, .-VCTRL_GetStreamInterface
	.align	3
.LC266:
	.xword	.LANCHOR0
	.align	3
.LC267:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC269:
	.xword	.LC268
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetFrameInterface
	.type	VCTRL_SetFrameInterface, %function
VCTRL_SetFrameInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L347
	ldr	x0, .LC274
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L348
	ldr	x3, .LC276
	mov	x2, 24
	mov	x1, x19
	add	x0, x0, 232
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L345:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L348:
	ldr	x3, .LC275
	mov	w2, 1326
	ldr	x1, .LC273
	bl	dprint_vfmw
	mov	w0, -1
	b	.L345
.L347:
	ldr	x3, .LC272
	mov	w2, 1325
	ldr	x1, .LC273
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L345
	.size	VCTRL_SetFrameInterface, .-VCTRL_SetFrameInterface
	.align	3
.LC272:
	.xword	.LC271
	.align	3
.LC273:
	.xword	.LC5
	.align	3
.LC274:
	.xword	.LANCHOR0
	.align	3
.LC275:
	.xword	.LC8
	.align	3
.LC276:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetFrameInterface
	.type	VCTRL_GetFrameInterface, %function
VCTRL_GetFrameInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC277
	ldr	x1, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x1, 232
	cmp	x1, xzr
	csel	x0, x0, xzr, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetFrameInterface, .-VCTRL_GetFrameInterface
	.align	3
.LC277:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetStreamSize
	.type	VCTRL_GetStreamSize, %function
VCTRL_GetStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L357
	ldr	x0, .LC280
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L358
	ldr	w2, [x0, 4]
	cmp	w2, 1
	bne	.L359
	mov	x2, 34448
	mov	x1, x20
	movk	x2, 0x1, lsl 16
	add	x0, x0, x2
	bl	GetSegStreamSize
.L354:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L359:
	ldr	x3, .LC284
	mov	w2, 1355
	ldr	x1, .LC279
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L354
	.p2align 3
.L357:
	ldr	x3, .LC278
	mov	w2, 1353
	ldr	x1, .LC279
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L354
.L358:
	ldr	x3, .LC282
	mov	w2, 1354
	ldr	x1, .LC279
	bl	dprint_vfmw
	mov	w0, -1
	b	.L354
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
	.align	3
.LC278:
	.xword	.LC237
	.align	3
.LC279:
	.xword	.LC5
	.align	3
.LC280:
	.xword	.LANCHOR0
	.align	3
.LC282:
	.xword	.LC281
	.align	3
.LC284:
	.xword	.LC283
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckFreshRaw
	.type	VCTRL_CheckFreshRaw, %function
VCTRL_CheckFreshRaw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	stp	wzr, wzr, [x29, 40]
	bhi	.L367
	ldr	x0, .LC287
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L368
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L369
	add	x19, x0, 1656
	add	x1, x29, 40
	mov	x0, x19
	bl	GetRawStreamNum
	cbnz	w0, .L366
	add	x1, x29, 44
	mov	x0, x19
	bl	GetRawStreamSize
	cbnz	w0, .L366
	ldr	x1, .LC291
	mov	w0, 22
	ldp	w2, w3, [x29, 40]
	bl	dprint_vfmw
	ldr	w0, [x29, 40]
	cmp	w0, wzr
	ble	.L366
	ldr	w0, [x29, 44]
	cmp	w0, 3
	csetm	w0, le
.L362:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L366:
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L369:
	ldr	x3, .LC289
	mov	w2, 1372
	ldr	x1, .LC286
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L362
	.p2align 3
.L367:
	ldr	x3, .LC285
	mov	w2, 1370
	ldr	x1, .LC286
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L362
.L368:
	ldr	x3, .LC288
	mov	w2, 1371
	ldr	x1, .LC286
	bl	dprint_vfmw
	mov	w0, -1
	b	.L362
	.size	VCTRL_CheckFreshRaw, .-VCTRL_CheckFreshRaw
	.align	3
.LC285:
	.xword	.LC237
	.align	3
.LC286:
	.xword	.LC5
	.align	3
.LC287:
	.xword	.LANCHOR0
	.align	3
.LC288:
	.xword	.LC281
	.align	3
.LC289:
	.xword	.LC283
	.align	3
.LC291:
	.xword	.LC290
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckFreshSeg
	.type	VCTRL_CheckFreshSeg, %function
VCTRL_CheckFreshSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	stp	wzr, wzr, [x29, 40]
	bhi	.L375
	ldr	x0, .LC294
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L376
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L377
	mov	x3, 34448
	add	x2, x29, 44
	movk	x3, 0x1, lsl 16
	add	x1, x29, 40
	add	x0, x0, x3
	bl	GetFreshSegStream
	ldr	x1, .LC298
	mov	w0, 22
	ldp	w2, w3, [x29, 40]
	bl	dprint_vfmw
	ldr	w0, [x29, 40]
	cmp	w0, wzr
	csetm	w0, le
.L372:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L377:
	ldr	x3, .LC296
	mov	w2, 1398
	ldr	x1, .LC293
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L372
	.p2align 3
.L375:
	ldr	x3, .LC292
	mov	w2, 1396
	ldr	x1, .LC293
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L372
.L376:
	ldr	x3, .LC295
	mov	w2, 1397
	ldr	x1, .LC293
	bl	dprint_vfmw
	mov	w0, -1
	b	.L372
	.size	VCTRL_CheckFreshSeg, .-VCTRL_CheckFreshSeg
	.align	3
.LC292:
	.xword	.LC237
	.align	3
.LC293:
	.xword	.LC5
	.align	3
.LC294:
	.xword	.LANCHOR0
	.align	3
.LC295:
	.xword	.LC281
	.align	3
.LC296:
	.xword	.LC283
	.align	3
.LC298:
	.xword	.LC297
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetDiscardPicParam
	.type	VCTRL_SetDiscardPicParam, %function
VCTRL_SetDiscardPicParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L384
	cbz	x20, .L385
	ldr	x21, .LC303
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L386
	ldr	x3, .LC305
	mov	x1, x20
	mov	x2, 8
	add	x0, x0, 1528
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w0, [x1, 1528]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L383
	mov	w0, 0
	str	wzr, [x1, 1528]
.L380:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L383:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L384:
	ldr	x3, .LC299
	mov	w2, 1417
	ldr	x1, .LC300
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L380
.L386:
	ldr	x3, .LC304
	mov	w2, 1419
	ldr	x1, .LC300
	bl	dprint_vfmw
	mov	w0, -1
	b	.L380
.L385:
	ldr	x3, .LC302
	mov	w2, 1418
	ldr	x1, .LC300
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L380
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	3
.LC299:
	.xword	.LC237
	.align	3
.LC300:
	.xword	.LC5
	.align	3
.LC302:
	.xword	.LC301
	.align	3
.LC303:
	.xword	.LANCHOR0
	.align	3
.LC304:
	.xword	.LC8
	.align	3
.LC305:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetSyntaxCtx
	.type	VCTRL_GetSyntaxCtx, %function
VCTRL_GetSyntaxCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC306
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L389
	add	x0, x0, 507904
	add	x0, x0, 1400
.L388:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L389:
	mov	x0, 0
	b	.L388
	.size	VCTRL_GetSyntaxCtx, .-VCTRL_GetSyntaxCtx
	.align	3
.LC306:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetImageInterface
	.type	VCTRL_GetImageInterface, %function
VCTRL_GetImageInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC307
	ldr	x1, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x1, 208
	cmp	x1, xzr
	csel	x0, x0, xzr, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetImageInterface, .-VCTRL_GetImageInterface
	.align	3
.LC307:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	w23, w1
	mov	w21, w2
	mov	w25, w3
	mov	w26, w4
	bl	_mcount
	ldr	x19, .LC308
	cmp	w23, 31
	ccmp	w21, 31, 4, gt
	ldr	x22, [x19, w20, sxtw 3]
	ble	.L405
	cmp	w25, wzr
	ccmp	w26, wzr, 4, ne
	beq	.L406
	ldr	x24, .LC313
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 88
	ldr	x3, [x24, 96]
	blr	x3
	strb	wzr, [x29, 89]
	mov	w2, 1
	add	x1, x29, 88
	mov	w0, w20
	strb	wzr, [x29, 90]
	stp	w23, w21, [x29, 92]
	stp	w23, w21, [x29, 100]
	strb	wzr, [x29, 91]
	strb	w2, [x29, 88]
	bl	FSP_ConfigInstance
	mov	w21, w0
	cbnz	w0, .L397
	add	x3, x29, 84
	mov	w2, w26
	mov	w1, w25
	mov	w0, w20
	bl	FSP_ConfigFrameBuf
	cbnz	w0, .L407
	add	x23, x19, 3592
	mov	w0, w20
	mov	x1, x23
	bl	FSP_GetInstInfo
	ldrsb	w0, [x23, 2]
	mov	w1, 16
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x22, 520]
	cmp	w0, 2
	ble	.L408
	ldr	w0, [x23, 4]
	add	x20, x22, 452
	ldr	x3, [x24, 96]
	mov	x2, 64
	str	w0, [x22, 516]
	mov	w1, 0
	mov	x0, x20
	blr	x3
	ldr	w0, [x22, 520]
	cmp	w0, wzr
	ble	.L395
	sub	w4, w0, #1
	mov	w3, 88
	mov	x2, 104
	add	x1, x19, 3608
	mov	x0, x20
	umaddl	x2, w4, w3, x2
	add	x3, x23, x2
	.p2align 2
.L402:
	ldr	w2, [x1], 88
	str	w2, [x0], 4
	cmp	x1, x3
	bne	.L402
.L395:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L406:
	ldr	x1, .LC312
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L395
.L397:
	ldr	x1, .LC320
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L395
.L407:
	ldr	x1, .LC315
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L395
.L408:
	ldr	x2, .LC316
	mov	w3, 1571
	ldr	x1, .LC318
	mov	w0, 0
	add	x2, x2, 96
	mov	w21, -1
	bl	dprint_vfmw
	b	.L395
.L405:
	ldr	x1, .LC310
	mov	w3, w21
	mov	w2, w23
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L395
	.size	VCTRL_PartitionMemForStdUser, .-VCTRL_PartitionMemForStdUser
	.align	3
.LC308:
	.xword	.LANCHOR0
	.align	3
.LC310:
	.xword	.LC309
	.align	3
.LC312:
	.xword	.LC311
	.align	3
.LC313:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC315:
	.xword	.LC314
	.align	3
.LC316:
	.xword	.LANCHOR1
	.align	3
.LC318:
	.xword	.LC317
	.align	3
.LC320:
	.xword	.LC319
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_UnInstallChan
	.type	VCTRL_UnInstallChan, %function
VCTRL_UnInstallChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	FSP_DisableInstance
	mov	w0, w19
	bl	CloseUsdPool_WithMem
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_UnInstallChan, .-VCTRL_UnInstallChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DelAllFrameMemRecord
	.type	DelAllFrameMemRecord, %function
DelAllFrameMemRecord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	add	x20, x1, 2304
	bl	_mcount
	cbz	x19, .L428
	.p2align 2
.L423:
	ldr	w0, [x19]
	cmp	w0, 255
	beq	.L413
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_DelMemRecord
.L413:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L414
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_DelMemRecord
.L414:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L415
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_DelMemRecord
.L415:
	add	x19, x19, 72
	cmp	x19, x20
	bne	.L423
	mov	w0, 0
.L412:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L428:
	ldr	x3, .LC325
	mov	w2, 1610
	ldr	x1, .LC326
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L412
	.size	DelAllFrameMemRecord, .-DelAllFrameMemRecord
	.align	3
.LC325:
	.xword	.LC324
	.align	3
.LC326:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L453
	ldr	x20, [x19]
	cbz	x20, .L454
	ldr	w0, [x19, 32]
	cmp	w0, 1
	beq	.L434
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
.L435:
	ldr	w0, [x19, 36]
	cmp	w0, 1
	beq	.L455
.L433:
	ldr	x20, [x19, 8]
	cbz	x20, .L456
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
	ldr	w0, [x19, 40]
	cmp	w0, 1
	beq	.L457
.L438:
	ldr	x20, [x19, 16]
	cbz	x20, .L458
.L439:
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
	ldr	w0, [x19, 44]
	cmp	w0, 1
	bne	.L440
	ldr	w0, [x20, 16]
	cbnz	w0, .L459
.L440:
	ldr	x1, .LC340
	ldr	x0, [x20, 8]
	ldr	x1, [x1, 328]
	blr	x1
	mov	w0, 0
.L431:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L434:
	ldr	x1, [x19, 24]
	cbz	x1, .L460
	mov	w0, w21
	bl	DelAllFrameMemRecord
	cbz	w0, .L435
	ldr	x1, .LC335
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 36]
	cmp	w0, 1
	bne	.L433
	.p2align 2
.L455:
	ldr	w0, [x20, 16]
	cbz	w0, .L433
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	b	.L433
	.p2align 3
.L457:
	ldr	w0, [x20, 16]
	cbz	w0, .L438
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	b	.L438
	.p2align 3
.L456:
	ldr	x2, .LC327
	mov	w0, 0
	ldr	x1, .LC337
	add	x2, x2, 128
	bl	dprint_vfmw
	ldr	x20, [x19, 16]
	cbnz	x20, .L439
.L458:
	ldr	x2, .LC327
	mov	w0, 0
	ldr	x1, .LC339
	add	x2, x2, 128
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L459:
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	mov	w0, 0
	b	.L431
	.p2align 3
.L460:
	ldr	x2, .LC327
	mov	w0, 0
	ldr	x1, .LC333
	add	x2, x2, 128
	bl	dprint_vfmw
	b	.L435
	.p2align 3
.L454:
	ldr	x2, .LC327
	mov	w0, 0
	ldr	x1, .LC331
	add	x2, x2, 128
	bl	dprint_vfmw
	b	.L433
.L453:
	ldr	x2, .LC327
	mov	w0, 0
	ldr	x1, .LC329
	add	x2, x2, 128
	bl	dprint_vfmw
	mov	w0, -1
	b	.L431
	.size	VCTRL_FreeChanResource, .-VCTRL_FreeChanResource
	.align	3
.LC327:
	.xword	.LANCHOR1
	.align	3
.LC329:
	.xword	.LC328
	.align	3
.LC331:
	.xword	.LC330
	.align	3
.LC333:
	.xword	.LC332
	.align	3
.LC335:
	.xword	.LC334
	.align	3
.LC337:
	.xword	.LC336
	.align	3
.LC339:
	.xword	.LC338
	.align	3
.LC340:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCtxSize
	.type	VCTRL_GetChanCtxSize, %function
VCTRL_GetChanCtxSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 26
	beq	.L464
	mov	w0, 47200
	movk	w0, 0xf, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L464:
	mov	w0, 17280
	movk	w0, 0xb5, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCtxSize, .-VCTRL_GetChanCtxSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCfg
	.type	VCTRL_GetChanCfg, %function
VCTRL_GetChanCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L470
	cbz	x20, .L471
	ldr	x0, .LC345
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L472
	ldr	x3, .LC347
	mov	x2, 140
	add	x1, x1, 44
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L467:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L470:
	ldr	x3, .LC341
	mov	w2, 2639
	ldr	x1, .LC342
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L467
.L472:
	ldr	x3, .LC346
	mov	w2, 2641
	ldr	x1, .LC342
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L467
.L471:
	ldr	x3, .LC344
	mov	w2, 2640
	ldr	x1, .LC342
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L467
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	3
.LC341:
	.xword	.LC237
	.align	3
.LC342:
	.xword	.LC5
	.align	3
.LC344:
	.xword	.LC343
	.align	3
.LC345:
	.xword	.LANCHOR0
	.align	3
.LC346:
	.xword	.LC8
	.align	3
.LC347:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckCommonParameter
	.type	VCTRL_CheckCommonParameter, %function
VCTRL_CheckCommonParameter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC348
	ldr	w1, [x19, 8]
	ldr	x0, [x0, w20, sxtw 3]
	ldr	w2, [x0, 52]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 72]
	ldr	w1, [x19, 28]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 68]
	ldr	w1, [x19, 24]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 76]
	ldr	w1, [x19, 32]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 80]
	ldr	w1, [x19, 36]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 84]
	ldr	w1, [x19, 40]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 100]
	ldr	w1, [x19, 56]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 112]
	ldr	w1, [x19, 68]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 108]
	ldr	w1, [x19, 64]
	cmp	w2, w1
	bne	.L484
	ldr	w2, [x0, 104]
	ldr	w1, [x19, 60]
	cmp	w2, w1
	bne	.L484
	ldr	w1, [x0, 116]
	ldr	w0, [x19, 72]
	ldp	x19, x20, [sp, 16]
	cmp	w1, w0
	csetm	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L484:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CheckCommonParameter, .-VCTRL_CheckCommonParameter
	.align	3
.LC348:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x0, .LC349
	ldr	x19, [x0, w20, sxtw 3]
	ldr	w0, [x19, 600]
	cmp	w0, 21
	beq	.L490
	mov	x1, x21
	mov	w0, w20
	bl	VCTRL_CheckCommonParameter
	cbnz	w0, .L490
	ldr	w1, [x19, 52]
	cmp	w1, 1
	beq	.L491
	sub	w1, w1, #10
	cmp	w1, 2
	bhi	.L486
	ldr	w0, [x21, 12]
	ldr	w1, [x19, 56]
	cmp	w1, w0
	csetm	w0, ne
.L486:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L491:
	ldr	w1, [x19, 56]
	ldr	w0, [x21, 12]
	cmp	w1, w0
	bne	.L490
	ldr	w0, [x21, 16]
	ldr	w1, [x19, 60]
	ldr	x21, [sp, 32]
	cmp	w1, w0
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L490:
	mov	w0, -1
	b	.L486
	.size	VCTRL_CmpConfigParameter, .-VCTRL_CmpConfigParameter
	.align	3
.LC349:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckChanWH
	.type	VCTRL_CheckChanWH, %function
VCTRL_CheckChanWH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC350
	ldr	x2, .LC351
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w2, [x2]
	ldr	w3, [x0, 1332]
	cmp	w3, w2
	bgt	.L493
	ldr	x1, .LC352
	ldr	w3, [x0, 1336]
	mov	w0, 0
	ldr	w1, [x1]
	cmp	w3, w1
	ble	.L494
.L493:
	ldr	w1, [x20, 8]
	mov	w0, 0
	cmp	w1, wzr
	and	w3, w1, -3
	ccmp	w1, 20, 4, ne
	ccmp	w3, 13, 4, ne
	cset	w1, ne
	cbnz	w1, .L498
.L494:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L498:
	ldr	x3, .LC352
	ldr	x1, .LC354
	ldr	w3, [x3]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L494
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	3
.LC350:
	.xword	.LANCHOR0
	.align	3
.LC351:
	.xword	g_ChipMaxWidth
	.align	3
.LC352:
	.xword	g_ChipMaxHeight
	.align	3
.LC354:
	.xword	.LC353
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigChanCompress
	.type	VCTRL_ConfigChanCompress, %function
VCTRL_ConfigChanCompress:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 56]
	cmp	w0, 2
	ldr	x0, .LC355
	beq	.L504
	sbfiz	x1, x19, 4, 32
	add	x2, x0, 608
	add	x3, x2, x1
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w2, [x2, x1]
	ldr	w1, [x3, 4]
	str	w2, [x0, 1240]
	cmp	w1, 1
	str	w1, [x0, 1244]
	beq	.L505
	mov	w1, -1
	str	w1, [x0, 1248]
.L503:
	str	w1, [x0, 1252]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L505:
	ldp	w2, w1, [x3, 8]
	str	w2, [x0, 1248]
	b	.L503
	.p2align 3
.L504:
	ldr	x0, [x0, w19, sxtw 3]
	mov	w1, -1
	add	x2, x0, 1024
	stp	wzr, wzr, [x2, 216]
	stp	w1, w1, [x2, 224]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_ConfigChanCompress, .-VCTRL_ConfigChanCompress
	.align	3
.LC355:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC357
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L512
	ldr	w0, [x0, 600]
	sub	w2, w0, #10
	cmp	w2, 2
	bls	.L513
.L509:
	cmp	w0, 14
	ccmp	w0, 4, 4, ne
	beq	.L511
	mov	x1, x20
	mov	w0, w19
	bl	SM_SeekPts
	cmp	w0, wzr
	csetm	w0, ne
.L508:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L513:
	ldr	x1, .LC360
	ldr	w1, [x1, 2064]
	tbnz	x1, 0, .L509
.L511:
	mov	w0, -1
	b	.L508
.L512:
	ldr	x3, .LC358
	mov	w2, 3205
	ldr	x1, .LC359
	bl	dprint_vfmw
	mov	w0, -1
	b	.L508
	.size	VCTRL_SeekPts, .-VCTRL_SeekPts
	.align	3
.LC357:
	.xword	.LANCHOR0
	.align	3
.LC358:
	.xword	.LC8
	.align	3
.LC359:
	.xword	.LC5
	.align	3
.LC360:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReleaseStream
	.type	VCTRL_ReleaseStream, %function
VCTRL_ReleaseStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC361
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L517
	mov	w0, w19
	bl	SM_Reset
	cmp	w0, wzr
	csetm	w0, ne
.L516:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L517:
	ldr	x3, .LC362
	mov	w2, 3469
	ldr	x1, .LC363
	bl	dprint_vfmw
	mov	w0, -1
	b	.L516
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	3
.LC361:
	.xword	.LANCHOR0
	.align	3
.LC362:
	.xword	.LC8
	.align	3
.LC363:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ImageOutputEnable
	.type	VCTRL_ImageOutputEnable, %function
VCTRL_ImageOutputEnable:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L521
	ldr	x20, .LC366
	mov	w0, 4
	ldr	x1, [x20, 24]
	blr	x1
	ldr	x1, .LC367
	mov	w0, 4
	ldr	w2, [x21]
	ldr	x1, [x1, w19, sxtw 3]
	str	w2, [x1, 12]
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, 0
.L520:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L521:
	ldr	x3, .LC364
	mov	w2, 3583
	ldr	x1, .LC365
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L520
	.size	VCTRL_ImageOutputEnable, .-VCTRL_ImageOutputEnable
	.align	3
.LC364:
	.xword	.LC237
	.align	3
.LC365:
	.xword	.LC5
	.align	3
.LC366:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC367:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_TryToRelSpecialFrm
	.type	VCTRL_TryToRelSpecialFrm, %function
VCTRL_TryToRelSpecialFrm:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w24, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cmp	w24, 31
	bhi	.L556
	ldr	x19, .LC370
	ldr	x1, [x19, w24, sxtw 3]
	cbz	x1, .L557
	add	x0, x1, 507904
	ldr	w3, [x0, 1336]
	cbz	w3, .L526
	ldr	w0, [x0, 812]
	mov	w2, 0
	cmp	w21, w0
	bne	.L529
	b	.L558
	.p2align 3
.L530:
	add	x0, x0, 3122
	add	x0, x1, x0, lsl 4
	ldr	w0, [x0, 12]
	cmp	w21, w0
	beq	.L527
.L529:
	add	w2, w2, 1
	cmp	w3, w2
	mov	w20, w2
	sxtw	x0, w2
	add	x0, x0, 28672
	bne	.L530
.L526:
	mov	w0, -1
.L549:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L558:
	mov	w20, 0
	.p2align 2
.L527:
	add	x0, x1, 495616
	mov	w23, 1
	add	x0, x0, 3688
	ldr	w2, [x0, -88]
	cmp	w2, w21
	bne	.L534
	b	.L559
	.p2align 3
.L531:
	add	w23, w23, 1
	cmp	w23, 32
	beq	.L560
.L534:
	ldr	w2, [x0]
	add	x0, x0, 88
	cmp	w21, w2
	bne	.L531
.L537:
	ldr	x25, .LC371
	mov	w0, 3
	sub	w22, w3, #1
	sxtw	x23, w23
	ldr	x1, [x25, 24]
	blr	x1
	lsl	x0, x23, 2
	ldr	x3, [x19, w24, sxtw 3]
	sub	x0, x0, x23
	ldr	x2, [x25, 32]
	lsl	x1, x0, 2
	mov	w0, 3
	sub	x23, x1, x23
	add	x1, x3, x23, lsl 3
	add	x3, x1, 495616
	add	x1, x1, 499712
	strb	wzr, [x3, 3594]
	strb	wzr, [x1, 2314]
	blr	x2
	cmp	w22, w20
	bls	.L541
	sxtw	x21, w24
	uxtw	x23, w20
	.p2align 2
.L533:
	add	w20, w20, 1
	add	x23, x23, 28672
	add	x0, x23, 3122
	ldr	x3, [x19, x21, lsl 3]
	uxtw	x23, w20
	ldr	x4, [x25, 104]
	add	x1, x23, 28672
	add	x0, x3, x0, lsl 4
	add	x1, x1, 3122
	mov	x2, 16
	add	x0, x0, 8
	add	x1, x3, x1, lsl 4
	add	x1, x1, 8
	blr	x4
	cmp	w20, w22
	bcc	.L533
.L532:
	uxtw	x0, w22
	ldr	x4, [x19, w24, sxtw 3]
	add	x0, x0, 28672
	ldr	x3, [x25, 96]
	add	x0, x0, 3122
	mov	x2, 16
	mov	w1, 0
	add	x0, x4, x0, lsl 4
	add	x0, x0, 8
	blr	x3
	ldr	x1, [x19, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 507904
	ldr	w2, [x1, 1336]
	sub	w2, w2, #1
	str	w2, [x1, 1336]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L560:
	add	x2, x1, 475136
	ldr	x20, .LC372
	ldr	x1, .LC376
	mov	w3, 3740
	add	x20, x20, 152
	mov	w0, 1
	ldrsb	w4, [x2, 2171]
	mov	x2, x20
	bl	dprint_vfmw
	ldr	x6, [x19, w24, sxtw 3]
	add	x0, x6, 475136
	ldrsb	w0, [x0, 2171]
	cmp	w0, wzr
	ble	.L526
	ldr	x22, .LC374
	mov	w23, 0
	sxtw	x21, w24
	.p2align 2
.L536:
	sxtw	x4, w23
	mov	w0, 1
	lsl	x5, x4, 2
	mov	w3, 3743
	sub	x5, x5, x4
	mov	x2, x20
	lsl	x5, x5, 2
	mov	x1, x22
	sub	x4, x5, x4
	add	w23, w23, w0
	add	x4, x6, x4, lsl 3
	add	x4, x4, 495616
	ldr	w4, [x4, 3600]
	bl	dprint_vfmw
	ldr	x6, [x19, x21, lsl 3]
	add	x0, x6, 475136
	ldrsb	w0, [x0, 2171]
	cmp	w0, w23
	bgt	.L536
	b	.L526
.L559:
	mov	w23, 0
	b	.L537
.L556:
	ldr	x3, .LC368
	mov	w2, 3704
	ldr	x1, .LC369
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L549
.L541:
	mov	w22, w20
	b	.L532
.L557:
	ldr	x3, .LC368
	mov	w2, 3705
	ldr	x1, .LC369
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L549
	.size	VCTRL_TryToRelSpecialFrm, .-VCTRL_TryToRelSpecialFrm
	.align	3
.LC368:
	.xword	.LC237
	.align	3
.LC369:
	.xword	.LC5
	.align	3
.LC370:
	.xword	.LANCHOR0
	.align	3
.LC371:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC372:
	.xword	.LANCHOR1
	.align	3
.LC374:
	.xword	.LC373
	.align	3
.LC376:
	.xword	.LC375
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	sub	sp, sp, #640
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC379
	mov	w2, w19
	mov	w0, 2
	bl	dprint_vfmw
	cmp	w19, 31
	bhi	.L590
	ldr	x21, .LC382
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L591
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L592
	ldr	x22, .LC386
	mov	w0, 4
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 12]
	cmp	w1, 1
	bne	.L593
	add	x0, x0, 507904
	mov	x1, x20
	add	x0, x0, 1400
	bl	SYNTAX_ReceiveImage
	cmp	w0, 1
	mov	w24, w0
	beq	.L594
	mov	w0, 9
	mov	w23, -1
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L579
.L578:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, 4
	ldr	x2, [x22, 32]
	add	x1, x1, 524288
	ldrb	w1, [x1, 912]
	strb	w1, [x20, 392]
	blr	x2
.L588:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w23
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L594:
	ldr	w1, [x20, 192]
	mov	w0, -1
	str	w0, [x20, 188]
	cmp	w1, 1
	beq	.L595
.L568:
	mov	w0, 9
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L596
	ldr	x0, [x21, w19, sxtw 3]
	mov	w23, 0
	ldr	w1, [x20, 64]
	str	w1, [x0, 424]
	ldr	w1, [x20, 276]
	str	w1, [x0, 428]
	b	.L578
	.p2align 3
.L600:
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 72
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReceiveImage
	cmp	w0, 1
	bne	.L597
	ldr	w0, [x20, 184]
	ldr	w1, [x29, 256]
	cmp	w0, w1
	bge	.L571
	ldp	w0, w4, [x29, 92]
	ldp	w3, w2, [x29, 100]
	ldr	w1, [x29, 220]
	ldr	w23, [x29, 252]
	stp	w0, w4, [x20, 196]
	str	w1, [x20, 188]
	mov	w0, 3
	stp	w3, w2, [x20, 204]
	str	w0, [x20, 276]
	cbz	w23, .L576
	mov	w24, 1
	mov	w23, 0
	str	w24, [x20, 180]
.L576:
	mov	w0, 9
	bl	CHECK_REC_POS_ENABLE
	cbz	w0, .L577
	.p2align 2
.L579:
	ldr	x0, [x22]
	blr	x0
	mov	w3, w0
	ldr	x1, .LC396
	ldr	x0, .LC397
	add	x1, x1, 2072
	ldr	w2, [x0]
	ldr	w0, [x1, w19, sxtw 2]
	sub	w0, w3, w0
	cmp	w0, w2
	bhi	.L598
.L577:
	cbnz	w23, .L578
.L599:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w23, 0
	ldr	w1, [x20, 64]
	str	w1, [x0, 424]
	ldr	w1, [x20, 276]
	str	w1, [x0, 428]
	b	.L578
	.p2align 3
.L596:
	mov	w23, 0
	b	.L579
	.p2align 3
.L598:
	lsl	w2, w19, 24
	ldr	x0, .LC387
	add	w2, w2, 589824
	cmp	w24, 1
	str	w3, [x1, w19, sxtw 2]
	csinc	w2, w2, w2, ne
	add	x0, x0, 208
	mov	w1, 4018
	bl	DBG_AddTrace
	cbz	w23, .L599
	b	.L578
	.p2align 3
.L595:
	ldr	w1, [x20, 180]
	cbz	w1, .L600
	ldp	w2, w3, [x20, 20]
	mov	w1, 3
	str	w24, [x20, 180]
	str	w0, [x20, 188]
	stp	w2, w3, [x20, 196]
	str	w1, [x20, 276]
	b	.L568
	.p2align 3
.L592:
	ldr	x3, .LC385
	mov	w2, 3882
	ldr	x1, .LC381
	mov	w0, 0
	mov	w23, -1
	bl	dprint_vfmw
	b	.L588
	.p2align 3
.L593:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w23, -1
	blr	x1
	ldr	x2, .LC387
	mov	w0, 0
	ldr	x1, .LC389
	add	x2, x2, 184
	bl	dprint_vfmw
	b	.L588
	.p2align 3
.L590:
	ldr	x3, .LC380
	mov	w2, 3878
	ldr	x1, .LC381
	mov	w0, 0
	mov	w23, -1
	bl	dprint_vfmw
	b	.L588
	.p2align 3
.L597:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w23, w0
	add	x0, x1, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReturnImage
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	b	.L588
.L571:
	bgt	.L601
	cbnz	w0, .L574
	ldr	x0, [x21, w19, sxtw 3]
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC387
	mov	w0, 1
	ldr	x1, .LC393
	ldr	w3, [x20, 184]
	add	x2, x2, 184
	bl	dprint_vfmw
	b	.L576
.L574:
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	ldr	w0, [x29, 252]
	cbz	w0, .L602
	ldr	x2, .LC387
	mov	w0, 1
	ldr	x1, .LC395
	ldr	w3, [x20, 184]
	add	x2, x2, 184
	bl	dprint_vfmw
	ldr	x3, [x22, 104]
	mov	x2, 632
	add	x1, x29, 72
	mov	x0, x20
	blr	x3
	ldp	w3, w4, [x29, 92]
	mov	w2, -1
	mov	w1, 3
	mov	w0, 1
	str	w2, [x20, 188]
	str	w0, [x20, 180]
	stp	w3, w4, [x20, 196]
	str	w1, [x20, 276]
	b	.L568
.L591:
	ldr	x3, .LC383
	mov	w2, 3879
	ldr	x1, .LC381
	mov	w23, -1
	bl	dprint_vfmw
	b	.L588
.L601:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC387
	mov	w0, 1
	ldr	x1, .LC391
	ldr	w3, [x20, 184]
	add	x2, x2, 184
	ldr	w4, [x29, 256]
	bl	dprint_vfmw
	b	.L576
.L602:
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 72
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC387
	mov	w0, 1
	ldr	x1, .LC395
	ldr	w3, [x20, 184]
	add	x2, x2, 184
	bl	dprint_vfmw
	b	.L576
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	3
.LC379:
	.xword	.LC378
	.align	3
.LC380:
	.xword	.LC237
	.align	3
.LC381:
	.xword	.LC5
	.align	3
.LC382:
	.xword	.LANCHOR0
	.align	3
.LC383:
	.xword	.LC8
	.align	3
.LC385:
	.xword	.LC384
	.align	3
.LC386:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC387:
	.xword	.LANCHOR1
	.align	3
.LC389:
	.xword	.LC388
	.align	3
.LC391:
	.xword	.LC390
	.align	3
.LC393:
	.xword	.LC392
	.align	3
.LC395:
	.xword	.LC394
	.align	3
.LC396:
	.xword	.LANCHOR3
	.align	3
.LC397:
	.xword	g_TraceImgPeriod
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	sub	sp, sp, #640
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L624
	ldr	x21, .LC401
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L625
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L626
	cbz	x20, .L627
	ldr	x1, .LC407
	mov	w2, w19
	ldr	w3, [x20, 148]
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x22, .LC408
	mov	w0, 4
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L628
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L629
	ldr	w1, [x20, 20]
	mov	w0, w19
	bl	VCTRL_TryToRelSpecialFrm
	cbz	w0, .L630
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
	ldr	w2, [x20, 188]
	cmn	w2, #1
	beq	.L612
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 72
	str	w2, [x29, 220]
	add	x0, x0, 507904
	add	x0, x0, 1400
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
.L612:
	mov	w0, 10
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L631
.L614:
	cmp	w23, 1
	csetm	w19, ne
	cbnz	w19, .L632
.L616:
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
.L605:
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L630:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w19, 0
	blr	x1
	ldr	x1, .LC414
	mov	w2, 4095
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x21, x22, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L632:
	ldr	x2, .LC417
	mov	w0, 0
	ldr	x1, .LC419
	add	x2, x2, 256
	bl	dprint_vfmw
	b	.L616
	.p2align 3
.L631:
	ldr	x0, [x22]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC415
	ldr	x0, .LC416
	add	x3, x3, 2200
	ldr	w1, [x0]
	ldr	w0, [x3, w19, sxtw 2]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L614
	lsl	w2, w19, 24
	ldr	x0, .LC417
	cmp	w23, 1
	add	w2, w2, 655360
	csinc	w2, w2, w2, ne
	mov	w1, 4125
	add	x0, x0, 232
	str	w4, [x3, w19, sxtw 2]
	bl	DBG_AddTrace
	b	.L614
	.p2align 3
.L629:
	ldr	x1, .LC412
	mov	w2, 4083
	mov	w0, 0
.L623:
	bl	dprint_vfmw
	mov	w19, -1
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	b	.L605
	.p2align 3
.L626:
	ldr	x3, .LC403
	mov	w2, 4066
	ldr	x1, .LC400
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L605
	.p2align 3
.L624:
	ldr	x3, .LC399
	mov	w2, 4064
	ldr	x1, .LC400
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L605
.L627:
	ldr	x3, .LC405
	mov	w2, 4067
	ldr	x1, .LC400
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L605
.L625:
	ldr	x3, .LC402
	mov	w2, 4065
	ldr	x1, .LC400
	mov	w19, -1
	bl	dprint_vfmw
	b	.L605
.L628:
	ldr	x1, .LC410
	mov	w2, 4074
	b	.L623
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	3
.LC399:
	.xword	.LC237
	.align	3
.LC400:
	.xword	.LC5
	.align	3
.LC401:
	.xword	.LANCHOR0
	.align	3
.LC402:
	.xword	.LC8
	.align	3
.LC403:
	.xword	.LC384
	.align	3
.LC405:
	.xword	.LC404
	.align	3
.LC407:
	.xword	.LC406
	.align	3
.LC408:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC410:
	.xword	.LC409
	.align	3
.LC412:
	.xword	.LC411
	.align	3
.LC414:
	.xword	.LC413
	.align	3
.LC415:
	.xword	.LANCHOR3
	.align	3
.LC416:
	.xword	g_TraceImgPeriod
	.align	3
.LC417:
	.xword	.LANCHOR1
	.align	3
.LC419:
	.xword	.LC418
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetVidStd
	.type	VCTRL_GetVidStd, %function
VCTRL_GetVidStd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L634
	ldr	x0, .LC421
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L634
	ldr	w1, [x0, 4]
	cmp	w1, 1
	beq	.L637
	ldr	x1, .LC425
	mov	w3, w19
	mov	w2, 4157
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 21
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L634:
	ldr	x1, .LC423
	mov	w2, 4150
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 21
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L637:
	ldr	w0, [x0, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
	.align	3
.LC421:
	.xword	.LANCHOR0
	.align	3
.LC423:
	.xword	.LC422
	.align	3
.LC425:
	.xword	.LC424
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetHDRConfigInfo
	.type	VCTRL_GetHDRConfigInfo, %function
VCTRL_GetHDRConfigInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC426
	ldr	x1, [x0, w20, sxtw 3]
	ldrb	w1, [x1, 44]
	strb	w1, [x19, 65]
	ldr	x1, [x0, w20, sxtw 3]
	ldrb	w1, [x1, 46]
	strb	w1, [x19, 66]
	ldr	x1, [x0, w20, sxtw 3]
	ldr	w1, [x1, 152]
	str	w1, [x19, 76]
	ldr	x1, [x0, w20, sxtw 3]
	ldr	w1, [x1, 156]
	str	w1, [x19, 68]
	ldr	x0, [x0, w20, sxtw 3]
	ldr	w0, [x0, 160]
	str	w0, [x19, 72]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetHDRConfigInfo, .-VCTRL_GetHDRConfigInfo
	.align	3
.LC426:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetDecParam
	.type	VCTRL_GetDecParam, %function
VCTRL_GetDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L662
	ldr	x0, .LC427
	ldr	x20, [x0, w19, sxtw 3]
	cbz	x20, .L662
	ldr	w0, [x20, 4]
	mov	x1, 0
	cmp	w0, 1
	bne	.L640
	ldr	w0, [x20, 8]
	cmp	w0, 1
	bne	.L640
	ldr	w3, [x20, 600]
	cmp	w3, 18
	bls	.L663
.L641:
	ldr	x2, .LC429
	mov	w0, 0
	ldr	x1, .LC431
	add	x2, x2, 280
	bl	dprint_vfmw
	mov	x1, 0
	b	.L640
	.p2align 3
.L662:
	mov	x1, 0
.L640:
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L663:
	ldr	x0, .LC428
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx643
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx643:
	.section	.rodata
	.align	0
	.align	2
.L643:
	.byte	(.L642 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L645 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L641 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L648 - .Lrtx643) / 4
	.byte	(.L641 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L641 - .Lrtx643) / 4
	.byte	(.L653 - .Lrtx643) / 4
	.byte	(.L654 - .Lrtx643) / 4
	.byte	(.L651 - .Lrtx643) / 4
	.byte	(.L656 - .Lrtx643) / 4
	.text
	.p2align 3
.L651:
	add	x0, x20, 507904
	ldr	x19, [x0, 1416]
.L657:
	cbz	x19, .L662
	ldr	x0, .LC432
	ldr	x0, [x0]
	blr	x0
	str	w0, [x20, 40]
	mov	x1, x19
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L648:
	add	x0, x20, 507904
	ldr	x19, [x0, 1432]
	b	.L657
	.p2align 3
.L653:
	add	x0, x20, 507904
	ldr	x19, [x0, 1640]
	b	.L657
	.p2align 3
.L654:
	add	x0, x20, 512000
	ldr	x19, [x0, 360]
	b	.L657
	.p2align 3
.L645:
	add	x0, x20, 507904
	ldr	x19, [x0, 2448]
	b	.L657
	.p2align 3
.L656:
	add	x0, x20, 507904
	ldr	x19, [x0, 1456]
	b	.L657
	.p2align 3
.L642:
	add	x0, x20, 507904
	ldr	x19, [x0, 2024]
	b	.L657
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	3
.LC427:
	.xword	.LANCHOR0
	.align	3
.LC428:
	.xword	.L643
	.align	3
.LC429:
	.xword	.LANCHOR1
	.align	3
.LC431:
	.xword	.LC430
	.align	3
.LC432:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsSedOnlyMode
	.type	VCTRL_IsSedOnlyMode, %function
VCTRL_IsSedOnlyMode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L672
	cbz	w20, .L667
	cmp	w20, 16
	beq	.L668
	mov	w0, 0
.L666:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L668:
	ldr	w0, [x19, 5188]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	uxtb	w0, w0
	ret
	.p2align 3
.L667:
	ldrb	w0, [x19, 1188]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L672:
	ldr	x1, .LC434
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L666
	.size	VCTRL_IsSedOnlyMode, .-VCTRL_IsSedOnlyMode
	.align	3
.LC434:
	.xword	.LC433
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ChanDecparamInValidFlag
	.type	VCTRL_ChanDecparamInValidFlag, %function
VCTRL_ChanDecparamInValidFlag:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L674
	ldr	x21, .LC435
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L674
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L677
	ldr	w22, [x0, 8]
	cmp	w22, 1
	beq	.L678
.L677:
	ldr	x1, .LC439
	mov	w2, w19
	mov	w0, 22
	mov	w20, 0
	bl	dprint_vfmw
.L676:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L674:
	ldr	x1, .LC437
	mov	w3, w19
	mov	w2, 4343
	mov	w0, 22
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L678:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L683
	ldr	x0, [x21, w19, sxtw 3]
	mov	w20, 0
	str	wzr, [x0, 444]
	str	wzr, [x0, 448]
	b	.L676
	.p2align 3
.L683:
	ldr	x23, [x21, w19, sxtw 3]
	ldr	x0, .LC440
	ldr	w20, [x23, 444]
	cbz	w20, .L684
	ldr	x0, [x0]
	blr	x0
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 448]
	cmp	w0, w2
	bls	.L681
	sub	w0, w0, w2
	mov	w20, 0
	cmp	w0, 40
	bls	.L676
.L681:
	mov	w20, w22
	str	wzr, [x1, 444]
	str	wzr, [x1, 448]
	b	.L676
.L684:
	ldr	x0, [x0]
	str	w22, [x23, 444]
	blr	x0
	str	w0, [x23, 448]
	b	.L676
	.size	VCTRL_ChanDecparamInValidFlag, .-VCTRL_ChanDecparamInValidFlag
	.align	3
.LC435:
	.xword	.LANCHOR0
	.align	3
.LC437:
	.xword	.LC436
	.align	3
.LC439:
	.xword	.LC438
	.align	3
.LC440:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ClearDecparam
	.type	VCTRL_ClearDecparam, %function
VCTRL_ClearDecparam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC441
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 600]
	cmp	w1, 18
	bhi	.L685
	ldr	x2, .LC442
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx688
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx688:
	.section	.rodata
	.align	0
	.align	2
.L688:
	.byte	(.L687 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L690 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L685 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L693 - .Lrtx688) / 4
	.byte	(.L685 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L685 - .Lrtx688) / 4
	.byte	(.L698 - .Lrtx688) / 4
	.byte	(.L699 - .Lrtx688) / 4
	.byte	(.L697 - .Lrtx688) / 4
	.byte	(.L701 - .Lrtx688) / 4
	.text
	.p2align 3
.L697:
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
.L685:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L693:
	add	x0, x0, 507904
	str	xzr, [x0, 1432]
	b	.L685
	.p2align 3
.L687:
	add	x0, x0, 507904
	str	xzr, [x0, 2024]
	b	.L685
	.p2align 3
.L701:
	add	x0, x0, 507904
	str	xzr, [x0, 1456]
	b	.L685
	.p2align 3
.L690:
	add	x0, x0, 507904
	str	xzr, [x0, 2448]
	b	.L685
	.p2align 3
.L699:
	add	x0, x0, 512000
	str	xzr, [x0, 360]
	b	.L685
	.p2align 3
.L698:
	add	x0, x0, 507904
	str	xzr, [x0, 1640]
	b	.L685
	.size	VCTRL_ClearDecparam, .-VCTRL_ClearDecparam
	.align	3
.LC441:
	.xword	.LANCHOR0
	.align	3
.LC442:
	.xword	.L688
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L712
	ldr	x20, .LC446
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L713
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L706
	ldr	x3, .LC449
	mov	w2, 4773
	ldr	x1, .LC445
	mov	w0, 0
	bl	dprint_vfmw
.L702:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L706:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L702
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 600]
	cbz	w1, .L707
	cmp	w1, 16
	bne	.L702
	add	x0, x0, 507904
	mov	w1, w21
	add	x0, x0, 1408
	bl	HEVCDEC_VDMProcSedOnly
	b	.L702
	.p2align 3
.L712:
	ldr	x3, .LC444
	mov	w2, 4771
	ldr	x1, .LC445
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L707:
	add	x0, x0, 507904
	mov	w1, w21
	add	x0, x0, 1408
	bl	H264DEC_VDMProcSedOnly
	b	.L702
	.p2align 3
.L713:
	ldr	x3, .LC447
	mov	w2, 4772
	ldr	x1, .LC445
	bl	dprint_vfmw
	b	.L702
	.size	VCTRL_VdmProcSedOnly, .-VCTRL_VdmProcSedOnly
	.align	3
.LC444:
	.xword	.LC443
	.align	3
.LC445:
	.xword	.LC5
	.align	3
.LC446:
	.xword	.LANCHOR0
	.align	3
.LC447:
	.xword	.LC384
	.align	3
.LC449:
	.xword	.LC448
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_FlushDecoder
	.type	VCTRL_FlushDecoder, %function
VCTRL_FlushDecoder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC450
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L742
	add	x0, x0, 507904
	ldr	w1, [x0, 1400]
	cmp	w1, 18
	bls	.L743
.L735:
	mov	w0, 0
.L716:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L743:
	ldr	x2, .LC453
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx718
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx718:
	.section	.rodata
	.align	0
	.align	2
.L718:
	.byte	(.L717 - .Lrtx718) / 4
	.byte	(.L719 - .Lrtx718) / 4
	.byte	(.L720 - .Lrtx718) / 4
	.byte	(.L721 - .Lrtx718) / 4
	.byte	(.L735 - .Lrtx718) / 4
	.byte	(.L722 - .Lrtx718) / 4
	.byte	(.L723 - .Lrtx718) / 4
	.byte	(.L735 - .Lrtx718) / 4
	.byte	(.L724 - .Lrtx718) / 4
	.byte	(.L725 - .Lrtx718) / 4
	.byte	(.L726 - .Lrtx718) / 4
	.byte	(.L726 - .Lrtx718) / 4
	.byte	(.L726 - .Lrtx718) / 4
	.byte	(.L727 - .Lrtx718) / 4
	.byte	(.L735 - .Lrtx718) / 4
	.byte	(.L728 - .Lrtx718) / 4
	.byte	(.L729 - .Lrtx718) / 4
	.byte	(.L730 - .Lrtx718) / 4
	.byte	(.L731 - .Lrtx718) / 4
	.text
	.p2align 3
.L731:
	add	x0, x0, 1408
	bl	AVS2DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L730:
	add	x0, x0, 1408
	bl	VP9DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L729:
	add	x0, x0, 1408
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L744
.L733:
	ldr	x1, .LC457
	mov	w0, 32
	bl	dprint_vfmw
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	mov	w0, 0
	b	.L716
	.p2align 3
.L728:
	add	x0, x0, 1408
	bl	MVC_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	x0, [x19, w20, sxtw 3]
	mov	w1, -1
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	MVC_FlushDPB
	cbz	w0, .L735
	ldr	x2, .LC458
	mov	w3, 4862
	ldr	x1, .LC460
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L716
	.p2align 3
.L727:
	add	x0, x0, 1408
	bl	VP8DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L726:
	add	x0, x0, 1408
	bl	VP6DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L725:
	add	x0, x0, 1408
	bl	REAL9DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L724:
	add	x0, x0, 1408
	bl	REAL8DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L723:
	add	x0, x0, 1408
	bl	AVSDEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L722:
	add	x0, x0, 1408
	bl	DIVX3DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L721:
	add	x0, x0, 1408
	bl	MPEG2DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L720:
	add	x0, x0, 1408
	bl	MPEG4DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L719:
	add	x0, x0, 1408
	bl	VC1DEC_GetRemainImg
	mov	w0, 0
	b	.L716
	.p2align 3
.L717:
	add	x0, x0, 1408
	bl	H264_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	x0, [x19, w20, sxtw 3]
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	FlushDPB
	cbz	w0, .L735
	ldr	x1, .LC455
	mov	w2, 4829
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L716
	.p2align 3
.L744:
	ldr	x1, .LC455
	mov	w2, 4839
	mov	w0, 0
	bl	dprint_vfmw
	b	.L733
.L742:
	ldr	x3, .LC451
	mov	w2, 4803
	ldr	x1, .LC452
	bl	dprint_vfmw
	mov	w0, -1
	b	.L716
	.size	VCTRL_FlushDecoder, .-VCTRL_FlushDecoder
	.align	3
.LC450:
	.xword	.LANCHOR0
	.align	3
.LC451:
	.xword	.LC8
	.align	3
.LC452:
	.xword	.LC5
	.align	3
.LC453:
	.xword	.L718
	.align	3
.LC455:
	.xword	.LC454
	.align	3
.LC457:
	.xword	.LC456
	.align	3
.LC458:
	.xword	.LANCHOR4
	.align	3
.LC460:
	.xword	.LC459
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L769
	ldr	x0, .LC463
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L770
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bne	.L771
	ldr	w2, [x1, 600]
	cmp	w2, 18
	bls	.L772
.L765:
	mov	w0, 0
	b	.L747
	.p2align 3
.L772:
	ldr	x3, .LC466
	ldrb	w2, [x3,w2,uxtw]
	adr	x3, .Lrtx751
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx751:
	.section	.rodata
	.align	0
	.align	2
.L751:
	.byte	(.L750 - .Lrtx751) / 4
	.byte	(.L752 - .Lrtx751) / 4
	.byte	(.L753 - .Lrtx751) / 4
	.byte	(.L754 - .Lrtx751) / 4
	.byte	(.L765 - .Lrtx751) / 4
	.byte	(.L755 - .Lrtx751) / 4
	.byte	(.L756 - .Lrtx751) / 4
	.byte	(.L765 - .Lrtx751) / 4
	.byte	(.L757 - .Lrtx751) / 4
	.byte	(.L758 - .Lrtx751) / 4
	.byte	(.L759 - .Lrtx751) / 4
	.byte	(.L759 - .Lrtx751) / 4
	.byte	(.L759 - .Lrtx751) / 4
	.byte	(.L760 - .Lrtx751) / 4
	.byte	(.L765 - .Lrtx751) / 4
	.byte	(.L761 - .Lrtx751) / 4
	.byte	(.L762 - .Lrtx751) / 4
	.byte	(.L763 - .Lrtx751) / 4
	.byte	(.L764 - .Lrtx751) / 4
	.text
	.p2align 3
.L764:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	AVS2DEC_GetImageBuffer
.L747:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L763:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	VP9DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L762:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	HEVCDEC_GetImageBuffer
	b	.L747
	.p2align 3
.L761:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	MVC_DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L760:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	VP8DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L759:
	ldr	x2, .LC467
	ldr	w2, [x2, 2064]
	tbz	x2, 0, .L747
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	VP6DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L758:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	REAL9DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L757:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	REAL8DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L756:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	AVSDEC_GetImageBuffer
	b	.L747
	.p2align 3
.L755:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	DIVX3DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L754:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	MPEG2DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L753:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	MPEG4DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L752:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	VC1DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L750:
	add	x0, x1, 507904
	add	x0, x0, 1408
	bl	H264DEC_GetImageBuffer
	b	.L747
	.p2align 3
.L771:
	ldr	x3, .LC465
	mov	w2, 4932
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L747
	.p2align 3
.L769:
	ldr	x3, .LC461
	mov	w2, 4930
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L747
.L770:
	ldr	x3, .LC464
	mov	w2, 4931
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L747
	.size	VCTRL_GetImageBuffer, .-VCTRL_GetImageBuffer
	.align	3
.LC461:
	.xword	.LC443
	.align	3
.LC462:
	.xword	.LC5
	.align	3
.LC463:
	.xword	.LANCHOR0
	.align	3
.LC464:
	.xword	.LC384
	.align	3
.LC465:
	.xword	.LC448
	.align	3
.LC466:
	.xword	.L751
	.align	3
.LC467:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigFFFBSpeed
	.type	VCTRL_ConfigFFFBSpeed, %function
VCTRL_ConfigFFFBSpeed:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L779
	ldr	x0, .LC470
	ldr	x2, [x0, w19, sxtw 3]
	cbz	x2, .L780
	ldr	w0, [x2, 4]
	cmp	w0, 1
	bne	.L781
	cbz	x20, .L782
	ldr	w1, [x20]
	mov	w0, 0
	str	w1, [x2, 1260]
.L775:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L781:
	ldr	x3, .LC474
	mov	w2, 5055
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L775
	.p2align 3
.L779:
	ldr	x3, .LC468
	mov	w2, 5053
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L775
.L780:
	ldr	x3, .LC472
	mov	w2, 5054
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L775
.L782:
	ldr	x3, .LC476
	mov	w2, 5056
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L775
	.size	VCTRL_ConfigFFFBSpeed, .-VCTRL_ConfigFFFBSpeed
	.align	3
.LC468:
	.xword	.LC237
	.align	3
.LC469:
	.xword	.LC5
	.align	3
.LC470:
	.xword	.LANCHOR0
	.align	3
.LC472:
	.xword	.LC471
	.align	3
.LC474:
	.xword	.LC473
	.align	3
.LC476:
	.xword	.LC475
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigPVRInfo
	.type	VCTRL_ConfigPVRInfo, %function
VCTRL_ConfigPVRInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L789
	ldr	x0, .LC479
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L790
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L791
	cbz	x20, .L792
	ldr	x3, .LC483
	mov	x2, 20
	mov	x1, x20
	add	x0, x0, 1296
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L785:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L791:
	ldr	x3, .LC481
	mov	w2, 5068
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L785
	.p2align 3
.L789:
	ldr	x3, .LC477
	mov	w2, 5066
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L785
.L792:
	ldr	x3, .LC482
	mov	w2, 5069
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L785
.L790:
	ldr	x3, .LC480
	mov	w2, 5067
	ldr	x1, .LC478
	bl	dprint_vfmw
	mov	w0, -1
	b	.L785
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	3
.LC477:
	.xword	.LC237
	.align	3
.LC478:
	.xword	.LC5
	.align	3
.LC479:
	.xword	.LANCHOR0
	.align	3
.LC480:
	.xword	.LC471
	.align	3
.LC481:
	.xword	.LC473
	.align	3
.LC482:
	.xword	.LC475
	.align	3
.LC483:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanDecable
	.type	VCTRL_IsChanDecable, %function
VCTRL_IsChanDecable:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC484
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L796
	add	x1, x29, 40
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L796
	ldr	w0, [x29, 48]
	cmp	w0, 16
	bgt	.L797
	ldr	w0, [x29, 56]
	cmp	w0, 524288
	ble	.L796
.L797:
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	csetm	w0, ne
	cbnz	w0, .L795
	ldr	x0, .LC485
	ldr	x0, [x0]
	blr	x0
	ldr	x1, [x20, w19, sxtw 3]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x1, 40]
	ldp	x29, x30, [sp], 64
	sub	w0, w0, w1
	cmp	w0, 50
	csetm	w0, hi
	ret
	.p2align 3
.L796:
	mov	w0, -1
.L795:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VCTRL_IsChanDecable, .-VCTRL_IsChanDecable
	.align	3
.LC484:
	.xword	.LANCHOR0
	.align	3
.LC485:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanSegEnough
	.type	VCTRL_IsChanSegEnough, %function
VCTRL_IsChanSegEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC486
	ldr	x0, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 432]
	cmp	w0, 1
	cset	w0, ne
	ret
	.size	VCTRL_IsChanSegEnough, .-VCTRL_IsChanSegEnough
	.align	3
.LC486:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanActive
	.type	VCTRL_IsChanActive, %function
VCTRL_IsChanActive:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L806
	ldr	x0, .LC487
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L806
	ldr	w1, [x0, 4]
	cbz	w1, .L806
	ldr	w1, [x0, 8]
	cbz	w1, .L806
	ldr	w1, [x0, 20]
	cbz	w1, .L806
	ldr	w0, [x0, 600]
	ldr	x19, [sp, 16]
	cmp	w0, 21
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L806:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IsChanActive, .-VCTRL_IsChanActive
	.align	3
.LC487:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	USERDEC_Init
	.type	USERDEC_Init, %function
USERDEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x3, .LC488
	mov	x2, 624
	mov	w1, 0
	mov	x0, x19
	ldr	w21, [x19, 608]
	ldr	x3, [x3, 96]
	blr	x3
	str	w21, [x19, 608]
	add	x0, x19, 8
	bl	ResetVoQueue
	str	x20, [x19]
	ldr	x3, .LC489
	mov	x0, 0
	b	.L810
	.p2align 3
.L808:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L822
.L810:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 507904
	add	x1, x1, 1408
	cbz	x2, .L808
	cmp	x19, x1
	bne	.L808
	cmn	w0, #1
	str	w0, [x19, 616]
	mov	w0, 1
	beq	.L813
.L817:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L822:
	mov	w0, -1
	str	w0, [x19, 616]
.L813:
	ldr	x1, .LC491
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L817
	.size	USERDEC_Init, .-USERDEC_Init
	.align	3
.LC488:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC489:
	.xword	.LANCHOR0
	.align	3
.LC491:
	.xword	.LC490
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	USERDEC_RecycleImage
	.type	USERDEC_RecycleImage, %function
USERDEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L825
	ldr	w0, [x19, 616]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 616]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L826
	ldr	w0, [x19, 616]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 616]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
.L824:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L826:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L825:
	mov	w0, -2
	b	.L824
	.size	USERDEC_RecycleImage, .-USERDEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetUsrdecFrame
	.type	VCTRL_GetUsrdecFrame, %function
VCTRL_GetUsrdecFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x23, .LC492
	ldr	x0, [x23, w20, sxtw 3]
	cbz	x0, .L841
	ldr	w1, [x0, 600]
	cmp	w1, 20
	bne	.L842
	ldr	w0, [x0, 520]
	cmp	w0, 2
	ble	.L843
	mov	w1, 1
	mov	w0, w20
	bl	FSP_NewLogicFs
	mov	w22, w0
	tbnz	w0, #31, .L844
	mov	w1, w0
	mov	w0, w20
	bl	FSP_GetLogicFs
	mov	x19, x0
	ldr	x1, .LC502
	mov	w2, w22
	mov	w0, 18
	bl	dprint_vfmw
	cbz	x19, .L845
	ldr	x0, [x19, 32]
	cbz	x0, .L834
	ldr	x1, [x19, 40]
	cbz	x1, .L834
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC506
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 8]
	str	w0, [x21, 40]
	ldr	x0, [x23, w20, sxtw 3]
	ldr	w0, [x0, 516]
	str	w0, [x21, 20]
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 20]
	str	w0, [x21, 24]
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 20]
	bl	MEM_Phy2Vir
	str	x0, [x21, 32]
	mov	w1, 0
.L829:
	mov	w0, w1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L842:
	ldr	x1, .LC496
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
	.p2align 3
.L843:
	ldr	x1, .LC498
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
	.p2align 3
.L834:
	ldr	x1, .LC508
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
	.p2align 3
.L844:
	ldr	x1, .LC500
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
.L841:
	ldr	x1, .LC494
	mov	w2, 5343
	ldr	x3, .LC493
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
.L845:
	ldr	x1, .LC504
	mov	w2, 5373
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, -1
	b	.L829
	.size	VCTRL_GetUsrdecFrame, .-VCTRL_GetUsrdecFrame
	.align	3
.LC492:
	.xword	.LANCHOR0
	.align	3
.LC493:
	.xword	.LC8
	.align	3
.LC494:
	.xword	.LC5
	.align	3
.LC496:
	.xword	.LC495
	.align	3
.LC498:
	.xword	.LC497
	.align	3
.LC500:
	.xword	.LC499
	.align	3
.LC502:
	.xword	.LC501
	.align	3
.LC504:
	.xword	.LC503
	.align	3
.LC506:
	.xword	.LC505
	.align	3
.LC508:
	.xword	.LC507
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitSyntaxCtx
	.type	InitSyntaxCtx, %function
InitSyntaxCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC509
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L865
	ldr	w0, [x1, 600]
	cmp	w0, 20
	bls	.L866
.L846:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L866:
	ldr	x2, .LC512
	ldrb	w0, [x2,w0,uxtw]
	adr	x2, .Lrtx850
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx850:
	.section	.rodata
	.align	0
	.align	2
.L850:
	.byte	(.L849 - .Lrtx850) / 4
	.byte	(.L851 - .Lrtx850) / 4
	.byte	(.L852 - .Lrtx850) / 4
	.byte	(.L853 - .Lrtx850) / 4
	.byte	(.L846 - .Lrtx850) / 4
	.byte	(.L854 - .Lrtx850) / 4
	.byte	(.L855 - .Lrtx850) / 4
	.byte	(.L846 - .Lrtx850) / 4
	.byte	(.L856 - .Lrtx850) / 4
	.byte	(.L857 - .Lrtx850) / 4
	.byte	(.L858 - .Lrtx850) / 4
	.byte	(.L858 - .Lrtx850) / 4
	.byte	(.L858 - .Lrtx850) / 4
	.byte	(.L859 - .Lrtx850) / 4
	.byte	(.L846 - .Lrtx850) / 4
	.byte	(.L860 - .Lrtx850) / 4
	.byte	(.L861 - .Lrtx850) / 4
	.byte	(.L862 - .Lrtx850) / 4
	.byte	(.L863 - .Lrtx850) / 4
	.byte	(.L846 - .Lrtx850) / 4
	.byte	(.L864 - .Lrtx850) / 4
	.text
	.p2align 3
.L864:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	USERDEC_Init
	b	.L846
	.p2align 3
.L863:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	AVS2DEC_Init
	b	.L846
	.p2align 3
.L862:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	VP9DEC_Init
	b	.L846
	.p2align 3
.L861:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	HEVCDEC_Init
	b	.L846
	.p2align 3
.L860:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	MVC_DEC_Init
	b	.L846
	.p2align 3
.L859:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	VP8DEC_Init
	b	.L846
	.p2align 3
.L858:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	VP6DEC_Init
	b	.L846
	.p2align 3
.L857:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	REAL9DEC_Init
	b	.L846
	.p2align 3
.L856:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	REAL8DEC_Init
	b	.L846
	.p2align 3
.L855:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	AVSDEC_Init
	b	.L846
	.p2align 3
.L854:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	DIVX3DEC_Init
	b	.L846
	.p2align 3
.L853:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	MPEG2DEC_Init
	b	.L846
	.p2align 3
.L852:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	MPEG4DEC_Init
	b	.L846
	.p2align 3
.L851:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	VC1DEC_Init
	b	.L846
	.p2align 3
.L849:
	add	x0, x1, 507904
	add	x1, x1, 608
	add	x0, x0, 1408
	bl	H264DEC_Init
	b	.L846
	.p2align 3
.L865:
	ldr	x3, .LC510
	mov	w2, 5428
	ldr	x1, .LC511
	mov	w0, 0
	bl	dprint_vfmw
	b	.L846
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	3
.LC509:
	.xword	.LANCHOR0
	.align	3
.LC510:
	.xword	.LC8
	.align	3
.LC511:
	.xword	.LC5
	.align	3
.LC512:
	.xword	.L850
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VarifyOption
	.type	VCTRL_VarifyOption, %function
VCTRL_VarifyOption:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 36]
	tbnz	w0, #31, .L868
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L868
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L868
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L868
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L874
	cmp	w0, 2
	mov	w0, 0
	bne	.L870
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L868
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L868
.L873:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L868
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L875
.L868:
	ldr	x1, .LC514
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
.L870:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L875:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L874:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L873
	b	.L868
	.size	VCTRL_VarifyOption, .-VCTRL_VarifyOption
	.align	3
.LC514:
	.xword	.LC513
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetMemSize_onDecode
	.type	VCTRL_GetMemSize_onDecode, %function
VCTRL_GetMemSize_onDecode:
	sub	sp, sp, #64
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	mov	x19, x1
	mov	w21, w0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldp	w5, w0, [x19, 36]
	mov	w4, 1
	cbz	w0, .L878
	mov	w4, 17
	add	w0, w5, 1
	cmp	w0, w4
	csel	w4, w0, w4, le
.L878:
	ldr	x1, .LC515
	sub	w0, w21, #27
	mov	w7, -2
	cmp	w0, 5
	csinv	w7, w7, wzr, ls
	ldr	x8, [x1, 128]
	cbz	x8, .L882
	ldr	w0, [x19, 60]
	mov	w6, 0
	ldr	x22, .LC518
	mov	w1, 2147483647
	add	w5, w5, w0
	ldp	w2, w3, [x19, 12]
	add	x0, x22, 2328
	add	w5, w5, 2
	str	x0, [sp]
	mov	w0, 1
	blr	x8
	cbnz	w0, .L882
	cmp	w21, 26
	beq	.L892
	mov	w1, 47200
	movk	w1, 0xf, lsl 16
	mov	w2, w1
.L883:
	ldr	w0, [x22, 2328]
	add	w3, w0, 16
	str	w3, [x20]
	ldr	w3, [x19, 168]
	cmp	w3, 1
	beq	.L884
	add	w0, w0, 307200
	add	w0, w0, 2576
	str	w0, [x20]
	ldr	w0, [x19, 56]
	add	w0, w0, 32768
	str	w0, [x20, 4]
.L885:
	str	w2, [x20, 8]
	ldr	w0, [x19, 44]
	cbnz	w0, .L893
	mov	w0, 62160
	movk	w0, 0x13, lsl 16
.L886:
	add	sp, x29, 0
	add	w1, w0, w1
	str	w1, [x20, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L893:
	ldrsw	x4, [x19, 20]
	mov	w0, 4000
	ldp	w7, w6, [x19, 28]
	lsl	x5, x4, 7
	mov	w3, 2208
	sub	x4, x5, x4
	cmp	w21, 26
	lsl	x4, x4, 5
	smaddl	x0, w7, w0, x4
	smaddl	x2, w6, w3, x0
	beq	.L888
	mov	w0, 62160
	movk	w0, 0x13, lsl 16
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L886
	.p2align 3
.L882:
	ldr	x1, .LC517
	mov	w2, 5591
	mov	w0, 0
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L884:
	ldr	w0, [x19, 56]
	add	w0, w0, 339968
	add	w0, w0, 2576
	str	w0, [x20, 4]
	b	.L885
	.p2align 3
.L892:
	mov	w1, 17280
	movk	w1, 0xb5, lsl 16
	mov	w2, w1
	b	.L883
	.p2align 3
.L888:
	mov	w5, 3992
	mov	w3, 2240
	and	x2, x2, 4294967295
	mov	w0, 62160
	smaddl	x4, w7, w5, x4
	movk	w0, 0x13, lsl 16
	smaddl	x6, w6, w3, x4
	cmp	x6, x2
	csel	x2, x6, x2, cs
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L886
	.size	VCTRL_GetMemSize_onDecode, .-VCTRL_GetMemSize_onDecode
	.align	3
.LC515:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC517:
	.xword	.LC516
	.align	3
.LC518:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w3
	mov	x19, x1
	mov	x22, x2
	bl	_mcount
	cmp	w20, 2
	beq	.L895
	ldr	x0, .LC520
	mov	w6, 16
	ldr	w2, [x19, 36]
	ldr	w4, [x19, 60]
	ldr	w3, [x0, 3560]
	ldr	w5, [x0, 3564]
	add	w0, w2, w3
	cmp	w0, w6
	add	w1, w4, w5
	csel	w0, w0, w6, le
	cmp	w0, wzr
	ccmp	w1, wzr, 1, ge
	blt	.L902
	str	w0, [x19, 36]
	str	w1, [x19, 60]
.L895:
	mov	x0, x19
	bl	VCTRL_VarifyOption
	cbnz	w0, .L898
	mov	x2, x22
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetMemSize_onDecode
.L897:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L898:
	mov	w0, -1
	b	.L897
	.p2align 3
.L902:
	ldr	x1, .LC522
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L897
	.size	VCTRL_GetChanMemSize, .-VCTRL_GetChanMemSize
	.align	3
.LC520:
	.xword	.LANCHOR3
	.align	3
.LC522:
	.xword	.LC521
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseDrivers
	.type	CloseDrivers, %function
CloseDrivers:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 96]
	cbz	w0, .L928
	ldr	w0, [x19, 112]
	cmp	w0, wzr
	cset	w21, ne
.L904:
	ldr	w20, [x19, 24]
	ldr	w22, [x19, 16]
	ldr	x23, [x19, 8]
	cbz	w20, .L905
	ldr	x0, .LC523
	ldr	x1, [x0, 120]
	cbz	x1, .L957
	mov	w0, 0
	blr	x1
	cbz	w21, .L908
.L909:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
.L905:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 88]
	ldr	w22, [x19, 80]
	ldr	x23, [x19, 72]
	cbz	w20, .L911
	ldr	x0, .LC523
	ldr	x1, [x0, 120]
	cbz	x1, .L958
	mov	w0, 0
	blr	x1
	cbz	w21, .L914
.L915:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
.L911:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 56]
	ldr	w22, [x19, 48]
	ldr	x23, [x19, 40]
	cbnz	w20, .L959
.L917:
	mov	x1, x23
	mov	w2, w20
	mov	w0, w22
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	w21, [x19, 144]
	ldr	w22, [x19, 136]
	ldr	x23, [x19, 128]
	cbnz	w21, .L960
.L920:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 216
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 240]
	ldr	w22, [x19, 232]
	ldr	x23, [x19, 224]
	cbnz	w21, .L961
.L921:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 208]
	ldr	w22, [x19, 200]
	ldr	x23, [x19, 192]
	cbnz	w21, .L962
.L922:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 152
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 176]
	ldr	w22, [x19, 168]
	ldr	x23, [x19, 160]
	cbnz	w21, .L963
.L923:
	mov	w2, w21
	mov	w0, w22
	mov	x1, x23
	add	x19, x19, 248
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 24]
	ldr	w21, [x19, 16]
	ldr	x22, [x19, 8]
	cbnz	w20, .L964
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC526
	ldr	w0, [x19, 584]
	cmp	w0, 1
	beq	.L965
.L925:
	ldr	w0, [x19, 588]
	cmp	w0, 1
	beq	.L966
.L926:
	ldr	w0, [x19, 592]
	add	x19, x19, 256
	cmp	w0, 1
	beq	.L967
.L927:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L959:
	mov	w0, 0
	bl	SM_CloseSCDDrv
	cbz	w21, .L918
.L919:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, x2
	ldr	x3, [x3, 96]
	blr	x3
	b	.L917
	.p2align 3
.L960:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 120
	ldr	x3, [x3, 96]
	blr	x3
	b	.L920
	.p2align 3
.L964:
	mov	x1, x22
	mov	w0, w21
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC526
	ldr	w0, [x19, 584]
	cmp	w0, 1
	bne	.L925
.L965:
	ldr	x1, .LC524
	mov	w0, 0
	ldr	x21, [x1, 400]
	bl	VFMW_GetString
	ldr	x2, .LC527
	mov	x1, x0
	mov	w0, 127
	add	x2, x2, 3568
	blr	x21
	str	wzr, [x19, 584]
	ldr	w0, [x19, 588]
	cmp	w0, 1
	bne	.L926
	.p2align 2
.L966:
	ldr	x1, .LC524
	mov	w0, 4
	add	x19, x19, 256
	ldr	x21, [x1, 400]
	bl	VFMW_GetString
	ldr	x2, .LC527
	mov	x1, x0
	mov	w0, 136
	add	x2, x2, 3568
	blr	x21
	str	wzr, [x19, 332]
	ldr	w0, [x19, 336]
	cmp	w0, 1
	bne	.L927
.L967:
	ldr	x1, .LC524
	mov	w0, 13
	ldr	x20, [x1, 400]
	bl	VFMW_GetString
	ldr	x2, .LC527
	mov	x1, x0
	mov	w0, 181
	add	x2, x2, 3568
	blr	x20
	str	wzr, [x19, 336]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L963:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L923
	.p2align 3
.L962:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 184
	ldr	x3, [x3, 96]
	blr	x3
	b	.L922
	.p2align 3
.L961:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L921
	.p2align 3
.L957:
	ldr	x1, .LC525
	mov	w2, 5935
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L909
	.p2align 2
.L908:
	ldr	w0, [x19, 16]
	ldr	x1, [x19, 8]
	bl	MEM_ReleaseMemBlock
	b	.L909
	.p2align 3
.L958:
	ldr	x1, .LC525
	mov	w2, 5956
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L915
	.p2align 2
.L914:
	ldr	w0, [x19, 80]
	ldr	x1, [x19, 72]
	bl	MEM_ReleaseMemBlock
	b	.L915
	.p2align 3
.L928:
	mov	w21, 0
	b	.L904
	.p2align 3
.L918:
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_ReleaseMemBlock
	b	.L919
	.size	CloseDrivers, .-CloseDrivers
	.align	3
.LC523:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC524:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC525:
	.xword	.LC127
	.align	3
.LC526:
	.xword	.LANCHOR0
	.align	3
.LC527:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 120
	bl	_mcount
	mov	x2, x20
	mov	w1, 65536
	mov	w0, -121438208
	bl	MEM_MapRegisterAddr
	cbnz	w0, .L969
	ldr	w2, [x19, 144]
	add	x20, x19, 216
	ldr	x1, [x19, 128]
	ldr	w0, [x19, 136]
	bl	MEM_AddMemRecord
	mov	w0, 53248
	mov	x2, x20
	mov	w1, 4096
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_MapRegisterAddr
	cbz	w0, .L999
	mov	w2, 53248
	ldr	x1, .LC530
	movk	w2, 0xf8c3, lsl 16
.L992:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC531
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
.L993:
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
.L972:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L999:
	ldr	w2, [x20, 24]
	add	x21, x19, 184
	ldr	x1, [x20, 8]
	ldr	w0, [x20, 16]
	bl	MEM_AddMemRecord
	mov	w0, 49152
	mov	x2, x21
	mov	w1, 4096
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_MapRegisterAddr
	cbnz	w0, .L973
	ldr	w2, [x19, 208]
	ldr	x1, [x19, 192]
	ldr	w0, [x19, 200]
	bl	MEM_AddMemRecord
	ldr	x20, .LC531
	mov	w0, 15
	ldr	x22, [x20, 136]
	bl	VFMW_GetString
	mov	w3, 0
	mov	x2, x0
	mov	x1, 20
	add	x0, x29, 96
	blr	x22
	ldr	x22, .LC532
	ldr	x0, [x22, 96]
	cbz	x0, .L975
	blr	x0
	cmp	w0, wzr
	mov	w2, w0
	ble	.L975
	mov	w21, 3
	mov	w4, 0
	mov	x3, x19
	mov	w1, 0
	add	x0, x29, 96
	str	w21, [x19, 28]
	bl	MEM_AllocMemBlock
	cbnz	w0, .L976
	ldr	w2, [x19, 24]
	ldr	x1, [x19, 8]
	ldr	w0, [x19, 16]
	bl	MEM_AddMemRecord
	ldr	x3, [x20, 96]
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	str	wzr, [x29, 128]
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 24]
	ldr	x1, [x22, 112]
	stp	w2, w0, [x29, 120]
	cbz	x1, .L977
	add	x0, x29, 120
	blr	x1
	cbnz	w0, .L977
	str	w21, [x19, 92]
	mov	w0, 16
	add	x22, x19, 64
	ldr	x23, [x20, 136]
	bl	VFMW_GetString
	mov	w3, 0
	mov	x2, x0
	mov	x1, 20
	add	x0, x29, 96
	blr	x23
	mov	w4, 1
	mov	x3, x22
	mov	w2, 10240
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L978
	ldr	w2, [x19, 88]
	add	x23, x19, 32
	ldr	x1, [x19, 72]
	ldr	w0, [x19, 80]
	bl	MEM_AddMemRecord
	ldr	x2, .LC533
	mov	w0, 0
	ldr	w1, [x19, 80]
	str	w1, [x2, 1212]
	ldr	w1, [x19, 80]
	add	w1, w1, 4096
	add	w1, w1, 1024
	str	w1, [x2, 1216]
	bl	VDMDRV_Init
	ldr	x22, [x20, 136]
	mov	w0, 17
	bl	VFMW_GetString
	mov	x2, x0
	mov	w3, 0
	mov	x1, 20
	add	x0, x29, 96
	blr	x22
	str	w21, [x19, 60]
	mov	w2, 61440
	mov	w4, 0
	mov	x3, x23
	movk	w2, 0xa, lsl 16
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1000
	ldr	w2, [x19, 56]
	ldr	x1, [x19, 40]
	ldr	w0, [x19, 48]
	bl	MEM_AddMemRecord
	ldr	w0, [x19, 48]
	mov	w2, 0
	ldr	w1, [x19, 56]
	bl	SM_OpenSCDDrv
	cbnz	w0, .L981
	bl	SM_InstInit
	ldr	x25, .LC542
	mov	w0, 0
	ldr	x22, [x20, 392]
	ldrsw	x24, [x25, 88]
	bl	VFMW_GetString
	ldr	x21, .LC543
	mov	x3, x0
	ldr	x1, .LC544
	mov	x2, x24
	add	x21, x21, 3568
	mov	w0, 127
	mov	x4, x21
	blr	x22
	cbnz	w0, .L1001
	ldr	x22, .LC551
	mov	w0, 4
	ldrsw	x27, [x25, 88]
	mov	w24, 1
	add	x22, x22, 256
	ldr	x26, [x20, 392]
	str	w24, [x22, 328]
	bl	VFMW_GetString
	ldr	x1, .LC552
	mov	x3, x0
	mov	x4, x21
	mov	x2, x27
	mov	w0, 136
	blr	x26
	cbnz	w0, .L1002
	mov	w0, 13
	ldrsw	x26, [x25, 88]
	str	w24, [x22, 332]
	ldr	x25, [x20, 392]
	bl	VFMW_GetString
	ldr	x1, .LC553
	mov	x3, x0
	mov	x4, x21
	mov	x2, x26
	mov	w0, 181
	blr	x25
	cbnz	w0, .L1003
	str	w24, [x22, 336]
	b	.L972
	.p2align 3
.L969:
	ldr	x1, .LC530
	mov	w2, -121438208
	b	.L992
	.p2align 3
.L975:
	ldr	x1, .LC535
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L972
.L973:
	ldr	x1, .LC530
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC531
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	b	.L993
.L977:
	ldr	x1, .LC539
.L995:
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L972
.L1001:
	ldr	x1, .LC550
	mov	w2, 127
.L994:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L972
.L1002:
	ldr	x1, .LC550
	mov	w2, 136
	b	.L994
.L981:
	ldr	x1, .LC548
	mov	w2, 0
	b	.L994
.L1000:
	ldr	x1, .LC546
	mov	w2, 0
	b	.L994
.L976:
	ldr	x1, .LC537
	b	.L995
.L978:
	ldr	x1, .LC541
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x22
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L972
.L1003:
	ldr	x1, .LC550
	mov	w2, 181
	b	.L994
	.size	OpenDrivers, .-OpenDrivers
	.align	3
.LC530:
	.xword	.LC529
	.align	3
.LC531:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC532:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC533:
	.xword	g_HwMem
	.align	3
.LC535:
	.xword	.LC534
	.align	3
.LC537:
	.xword	.LC536
	.align	3
.LC539:
	.xword	.LC538
	.align	3
.LC541:
	.xword	.LC540
	.align	3
.LC542:
	.xword	.LANCHOR2
	.align	3
.LC543:
	.xword	.LANCHOR3
	.align	3
.LC544:
	.xword	VCTRL_Isr_0
	.align	3
.LC546:
	.xword	.LC545
	.align	3
.LC548:
	.xword	.LC547
	.align	3
.LC550:
	.xword	.LC549
	.align	3
.LC551:
	.xword	.LANCHOR0
	.align	3
.LC552:
	.xword	VCTRL_Scd_Isr
	.align	3
.LC553:
	.xword	VCTRL_MMU_ISR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OpenVfmw
	.type	VCTRL_OpenVfmw, %function
VCTRL_OpenVfmw:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC556
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x22, .LC557
	ldr	w19, [x22, 256]
	cbnz	w19, .L1035
	ldr	x21, .LC558
	mov	w1, 1024
	ldr	x2, [x20, 160]
	add	x24, x21, 3576
	str	xzr, [x29, 72]
	mov	x0, x24
	blr	x2
	ldr	x1, .LC560
	mov	x0, x24
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L1007
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1027
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1036
	ldr	x3, [x20, 168]
	mov	w2, 0
	mov	x1, 0
	blr	x3
	mov	w2, w0
	str	w0, [x21, 3560]
	add	w0, w2, 4096
	mov	w1, 10000
	add	w0, w0, 904
	cmp	w0, w1
	bhi	.L1012
.L1042:
	mov	w0, 5000
	mov	w1, -5000
	cmp	w2, w0
	csel	w0, w2, w0, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
.L1008:
	str	w0, [x21, 3560]
.L1010:
	add	x24, x21, 3576
	ldr	x2, [x20, 160]
	mov	w1, 1024
	mov	x0, x24
	str	xzr, [x29, 72]
	blr	x2
	ldr	x1, .LC571
	mov	x0, x24
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L1013
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1014
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1037
	ldr	x3, [x20, 168]
	mov	w2, 0
	mov	x1, 0
	blr	x3
	mov	w2, w0
	str	w0, [x21, 3564]
	add	w0, w2, 4096
	mov	w1, 10000
	add	w0, w0, 904
	cmp	w0, w1
	bhi	.L1018
.L1041:
	mov	w19, 5000
	mov	w0, -5000
	cmp	w2, w19
	csel	w19, w2, w19, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
.L1014:
	str	w19, [x21, 3564]
.L1016:
	ldr	x24, .LC574
	str	xzr, [x29, 72]
	ldr	w0, [x24, 248]
	cbz	w0, .L1019
	ldr	x2, .LC575
	and	w4, w0, 1
	ubfx	x3, x0, 1, 1
	ubfx	x1, x0, 2, 1
	strb	w4, [x24, 252]
	ubfx	x0, x0, 3, 1
	strb	w3, [x2, 92]
	strb	w1, [x24, 253]
	strb	w0, [x24, 254]
.L1020:
	ldr	x3, [x20, 96]
	mov	x2, 344
	mov	w1, 0
	add	x0, x22, 256
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 256
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	x1, .LC578
	mov	w2, 134217728
	add	x0, x29, 64
	str	x1, [x24, 256]
	mov	w1, 75497472
	stp	w2, w1, [x29, 64]
	bl	MEM_InitMemManager
	bl	FSP_Init
	ldr	x19, .LC579
	ldr	x3, [x20, 96]
	mov	x2, 384
	mov	w1, 0
	mov	x0, x19
	blr	x3
	add	x0, x19, 128
	add	x1, x19, 256
	mov	w2, -1
	.p2align 2
.L1024:
	str	w2, [x0], 4
	cmp	x1, x0
	bne	.L1024
	ldr	x3, [x20, 96]
	mov	x2, 128
	mov	w1, 0
	add	x0, x24, 264
	add	x19, x22, 288
	blr	x3
	ldr	x3, [x20, 104]
	mov	x2, 24
	add	x1, x23, 8
	add	x0, x22, 384
	blr	x3
	mov	x0, x19
	bl	OpenDrivers
	cbnz	w0, .L1035
	ldr	x2, [x20, 248]
	mov	w1, 1
	blr	x2
	ldr	x2, .LC582
	add	x0, x22, 272
	ldr	x1, .LC584
	ldr	x3, [x20, 384]
	blr	x3
	cbnz	w0, .L1038
	mov	w1, 1
	str	w1, [x22, 256]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1019:
	add	x21, x21, 3576
	ldr	x2, [x20, 160]
	mov	w1, 1024
	mov	x0, x21
	blr	x2
	ldr	x1, .LC577
	mov	x0, x21
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L1020
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1039
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1040
	ldr	x3, [x20, 168]
	mov	x1, 0
	mov	w2, 0
	blr	x3
	mov	w1, w0
	str	w0, [x24, 248]
.L1022:
	ldr	x2, .LC575
	and	w4, w1, 1
	ubfx	x3, x1, 1, 1
	ubfx	x0, x1, 2, 1
	strb	w4, [x24, 252]
	ubfx	x1, x1, 3, 1
	strb	w3, [x2, 92]
	strb	w0, [x24, 253]
	strb	w1, [x24, 254]
	b	.L1020
.L1013:
	ldr	w2, [x21, 3564]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1041
.L1018:
	ldr	x1, .LC573
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x21, 3564]
	mov	w1, 5000
	mov	w0, -5000
	cmp	w19, w1
	csel	w19, w19, w1, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
	b	.L1014
.L1007:
	ldr	w2, [x21, 3560]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1042
.L1012:
	ldr	x1, .LC569
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w0, [x21, 3560]
	mov	w2, 5000
	mov	w1, -5000
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
	b	.L1008
.L1027:
	mov	w0, 0
	b	.L1008
.L1039:
	ldr	w1, [x24, 248]
	b	.L1022
.L1038:
	mov	x0, x19
	bl	CloseDrivers
.L1035:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
.L1037:
	ldr	x2, .LC565
	mov	w3, 6846
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 48
	bl	dprint_vfmw
	b	.L1016
.L1036:
	ldr	x2, .LC565
	mov	w3, 6800
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L1010
.L1040:
	ldr	x2, .LC565
	mov	w3, 6902
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 72
	bl	dprint_vfmw
	b	.L1020
	.size	VCTRL_OpenVfmw, .-VCTRL_OpenVfmw
	.align	3
.LC556:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC557:
	.xword	.LANCHOR0
	.align	3
.LC558:
	.xword	.LANCHOR3
	.align	3
.LC560:
	.xword	.LC559
	.align	3
.LC562:
	.xword	.LC561
	.align	3
.LC564:
	.xword	.LC563
	.align	3
.LC565:
	.xword	.LANCHOR4
	.align	3
.LC567:
	.xword	.LC566
	.align	3
.LC569:
	.xword	.LC568
	.align	3
.LC571:
	.xword	.LC570
	.align	3
.LC573:
	.xword	.LC572
	.align	3
.LC574:
	.xword	.LANCHOR5
	.align	3
.LC575:
	.xword	.LANCHOR2
	.align	3
.LC577:
	.xword	.LC576
	.align	3
.LC578:
	.xword	VCTRL_EventReport
	.align	3
.LC579:
	.xword	g_ChanCtx
	.align	3
.LC582:
	.xword	VFMW_CTRL_thread_proc
	.align	3
.LC584:
	.xword	.LC583
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetNextDecodeMode
	.type	GetNextDecodeMode, %function
GetNextDecodeMode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w19, w2
	mov	w22, w1
	bl	_mcount
	add	w20, w19, 7
	mov	w0, 21846
	lsl	w3, w19, 1
	movk	w0, 0x5555, lsl 16
	cmp	w19, wzr
	csel	w20, w20, w19, lt
	ldr	x1, .LC588
	smull	x0, w3, w0
	asr	w20, w20, 3
	mov	w5, w22
	lsr	x0, x0, 32
	mov	w4, w19
	sub	w3, w0, w3, asr 31
	mov	w2, w20
	mov	w0, 30
	bl	dprint_vfmw
	cmp	w21, 3
	beq	.L1048
	cmp	w19, w22
	mov	w19, w21
	blt	.L1049
.L1045:
	ldr	x1, .LC594
	mov	w3, w19
	mov	w2, w21
	mov	w0, 30
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1049:
	ldr	x1, .LC592
	mov	w0, 30
	mov	w19, 3
	bl	dprint_vfmw
	b	.L1045
	.p2align 3
.L1048:
	cmp	w20, w22
	mov	w19, w21
	ble	.L1045
	ldr	x1, .LC590
	mov	w0, 30
	mov	w19, 0
	bl	dprint_vfmw
	b	.L1045
	.size	GetNextDecodeMode, .-GetNextDecodeMode
	.align	3
.LC588:
	.xword	.LC587
	.align	3
.LC590:
	.xword	.LC589
	.align	3
.LC592:
	.xword	.LC591
	.align	3
.LC594:
	.xword	.LC593
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanIDByCtx
	.type	VCTRL_GetChanIDByCtx, %function
VCTRL_GetChanIDByCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC595
	mov	x0, 0
	b	.L1053
	.p2align 3
.L1051:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1059
.L1053:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 507904
	add	x1, x1, 1408
	cbz	x2, .L1051
	cmp	x19, x1
	bne	.L1051
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1059:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanIDByCtx, .-VCTRL_GetChanIDByCtx
	.align	3
.LC595:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanIDByMemAddr
	.type	VCTRL_GetChanIDByMemAddr, %function
VCTRL_GetChanIDByMemAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x6, .LC596
	mov	x5, 0
.L1065:
	ldr	x4, [x6, x5, lsl 3]
	mov	w0, w5
	cbz	x4, .L1061
	add	x4, x4, 503808
	add	x1, x4, 1352
	add	x4, x4, 3656
	.p2align 2
.L1064:
	ldr	w2, [x1]
	cmp	w2, w19
	bhi	.L1062
	ldr	w3, [x1, -20]
	add	w2, w2, w3
	cmp	w19, w2
	bcc	.L1063
.L1062:
	add	x1, x1, 72
	cmp	x1, x4
	bne	.L1064
.L1061:
	add	x5, x5, 1
	cmp	x5, 32
	bne	.L1065
	mov	w0, -1
.L1063:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	3
.LC596:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecChanProcessPts
	.type	DecChanProcessPts, %function
DecChanProcessPts:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC597
	ldr	x4, [x21, w20, sxtw 3]
	ldr	w1, [x4, 52]
	cmp	w1, 1
	beq	.L1097
	sub	w0, w1, #2
	cmp	w0, 1
	ccmp	w1, 6, 4, hi
	bne	.L1074
.L1085:
	add	x2, x19, 8
	add	x0, x4, 1200
	bl	IsNewpicSeg
	cbnz	w0, .L1075
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	ldr	x1, [x0, 672]
	beq	.L1095
	cmn	x1, #1
	beq	.L1077
.L1095:
	str	x1, [x0, 664]
.L1077:
	ldr	x3, [x0, 688]
	mov	x2, -1
	ldr	x1, [x0, 704]
	str	x2, [x0, 672]
	str	x3, [x0, 680]
	str	x1, [x0, 696]
	cbnz	x1, .L1078
	ldr	x1, [x19, 64]
	str	x1, [x0, 696]
.L1078:
	ldr	w6, [x0, 724]
	ldr	w5, [x0, 728]
	ldr	w4, [x0, 732]
	ldr	w3, [x0, 740]
	ldr	x1, .LC599
	ldr	x2, [x0, 664]
	str	w6, [x0, 712]
	str	w5, [x0, 716]
	str	w4, [x0, 720]
	str	w3, [x0, 736]
	mov	w0, 29
	bl	dprint_vfmw
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	bne	.L1079
	ldr	x1, [x19, 40]
	.p2align 2
.L1096:
	str	x1, [x0, 672]
.L1081:
	ldr	x1, [x19, 56]
	str	x1, [x0, 688]
	ldr	x1, [x19, 64]
	str	x1, [x0, 704]
	ldr	w1, [x19, 72]
	str	w1, [x0, 724]
	ldr	w1, [x19, 76]
	str	w1, [x0, 728]
	ldr	w1, [x19, 80]
	str	w1, [x0, 732]
	ldr	w1, [x19, 84]
	str	w1, [x0, 740]
.L1080:
	ldr	x2, [x0, 680]
	mov	w0, 29
	ldr	x1, .LC601
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1097:
	add	x0, x4, 507904
	ldr	x0, [x0, 1408]
	ldrsb	w1, [x0, 596]
	cmp	w1, 1
	beq	.L1085
	.p2align 2
.L1074:
	ldr	x2, [x19, 40]
	cmn	x2, #1
	beq	.L1098
	str	x2, [x4, 664]
.L1084:
	ldr	x3, [x19, 56]
	mov	w0, 29
	str	x3, [x4, 680]
	ldr	x1, .LC603
	ldr	x5, [x19, 64]
	str	x5, [x4, 696]
	ldr	w5, [x19, 72]
	str	w5, [x4, 712]
	ldr	w5, [x19, 76]
	str	w5, [x4, 716]
	ldr	w5, [x19, 80]
	str	w5, [x4, 720]
	ldr	w5, [x19, 84]
	str	w5, [x4, 736]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1098:
	ldr	x2, [x4, 664]
	b	.L1084
	.p2align 3
.L1075:
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	beq	.L1080
.L1079:
	ldr	x1, [x19, 40]
	cmn	x1, #1
	bne	.L1096
	b	.L1081
	.size	DecChanProcessPts, .-DecChanProcessPts
	.align	3
.LC597:
	.xword	.LANCHOR0
	.align	3
.LC599:
	.xword	.LC598
	.align	3
.LC601:
	.xword	.LC600
	.align	3
.LC603:
	.xword	.LC602
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecChanCheckDecParam
	.type	DecChanCheckDecParam, %function
DecChanCheckDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC604
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 600]
	sub	w1, w0, #10
	cmp	w1, 2
	bhi	.L1100
	ldr	x1, .LC605
	ldr	w1, [x1, 2064]
	tbz	x1, 0, .L1101
.L1100:
	and	w1, w0, -17
	cmp	w1, 4
	ccmp	w0, 14, 4, ne
	beq	.L1101
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbnz	x0, .L1103
.L1101:
	mov	w0, 0
.L1102:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1103:
	mov	w0, -2
	b	.L1102
	.size	DecChanCheckDecParam, .-DecChanCheckDecParam
	.align	3
.LC604:
	.xword	.LANCHOR0
	.align	3
.LC605:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1144
	ldr	x21, .LC608
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1145
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1146
	ldr	w1, [x0, 24]
	cbnz	w1, .L1147
	ldr	x23, .LC613
	str	wzr, [x0, 432]
	ldr	x0, [x23]
	blr	x0
	ldr	x22, .LC614
	mov	w2, w0
	ldr	x0, .LC615
	add	x1, x22, 392
	ldr	w3, [x0]
	ldr	w0, [x1, w19, sxtw 2]
	sub	w0, w2, w0
	cmp	w0, w3
	mov	w0, w19
	bls	.L1116
	str	w2, [x1, w19, sxtw 2]
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	beq	.L1148
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1126
	mov	w20, w0
.L1127:
	ldr	x1, [x21, w19, sxtw 3]
	add	x0, x1, 475136
	ldr	w3, [x0, 2200]
	cmp	w3, 1
	beq	.L1149
	cmp	w3, 3
	beq	.L1150
	add	x24, x1, 744
	ldrb	w0, [x24, 1]
	cbnz	w0, .L1120
	ldr	w0, [x1, 1536]
	cbz	w0, .L1151
.L1120:
	ldr	x2, [x24, 40]
	mov	w0, 29
	ldr	x3, [x24, 56]
	ldr	x1, .LC627
	bl	dprint_vfmw
	mov	x1, x24
	mov	w0, w19
	bl	DecChanProcessPts
	mov	w0, 3
	bl	CHECK_REC_POS_ENABLE
	cmp	w20, 1
	ccmp	w0, wzr, 4, eq
	bne	.L1152
.L1122:
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x24
	add	x2, x1, 507904
	ldr	w1, [x1, 600]
	add	x2, x2, 1408
	bl	DecodeStream
	mov	w0, 4
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1123
.L1124:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1116:
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	bne	.L1153
.L1133:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1153:
	mov	w0, w19
	mov	w20, -3
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1133
	mov	w20, 0
	b	.L1127
	.p2align 3
.L1148:
	ldr	x1, .LC617
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1123:
	ldr	x0, [x23]
	add	x22, x22, 520
	blr	x0
	mov	w1, w0
	ldr	x2, .LC629
	ldr	w0, [x22, w19, sxtw 2]
	ldr	w2, [x2]
	sub	w0, w1, w0
	cmp	w0, w2
	bls	.L1124
	mov	w0, w19
	str	w1, [x22, w19, sxtw 2]
	bl	VCTRL_GetDecParam
	cbz	x0, .L1124
	ldr	x0, .LC628
	lsl	w2, w19, 24
	add	w2, w2, 262144
	mov	w1, 6550
	add	x0, x0, 88
	mov	w20, 0
	bl	DBG_AddTrace
	b	.L1133
.L1149:
	ldr	x1, .LC621
	mov	w0, 31
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1126:
	ldr	x1, .LC619
	mov	w2, w19
	mov	w0, 23
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1146:
	ldr	x3, .LC610
	mov	w2, 6450
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1147:
	ldr	x3, .LC612
	mov	w2, 6451
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1151:
	add	x1, x1, 752
	mov	w0, w19
	bl	SM_ReadSegStream
	cbz	w0, .L1120
	cmp	w20, 1
	beq	.L1154
.L1121:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 1
	mov	w20, -4
	str	w1, [x0, 432]
	b	.L1133
	.p2align 3
.L1144:
	ldr	x3, .LC606
	mov	w2, 6448
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1133
	.p2align 3
.L1152:
	ldr	x0, .LC628
	lsl	w2, w19, 24
	add	w2, w2, 196608
	mov	w1, 6532
	add	x0, x0, 88
	bl	DBG_AddTrace
	b	.L1122
.L1145:
	ldr	x3, .LC609
	mov	w2, 6449
	ldr	x1, .LC607
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1133
.L1150:
	ldr	w2, [x1, 1488]
	mov	w0, 31
	ldr	x1, .LC623
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1133
.L1154:
	ldr	x1, .LC625
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1121
	.size	DecChanSyntax, .-DecChanSyntax
	.align	3
.LC606:
	.xword	.LC237
	.align	3
.LC607:
	.xword	.LC5
	.align	3
.LC608:
	.xword	.LANCHOR0
	.align	3
.LC609:
	.xword	.LC384
	.align	3
.LC610:
	.xword	.LC448
	.align	3
.LC612:
	.xword	.LC611
	.align	3
.LC613:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC614:
	.xword	.LANCHOR5
	.align	3
.LC615:
	.xword	g_TraceBsPeriod
	.align	3
.LC617:
	.xword	.LC616
	.align	3
.LC619:
	.xword	.LC618
	.align	3
.LC621:
	.xword	.LC620
	.align	3
.LC623:
	.xword	.LC622
	.align	3
.LC625:
	.xword	.LC624
	.align	3
.LC627:
	.xword	.LC626
	.align	3
.LC628:
	.xword	.LANCHOR4
	.align	3
.LC629:
	.xword	g_TraceFramePeriod
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecSyntax
	.type	DecSyntax, %function
DecSyntax:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x0, x30
	bl	_mcount
	ldr	x22, .LC632
	ldr	x23, .LC633
	mov	x0, 0
	b	.L1158
	.p2align 3
.L1182:
	ldr	w1, [x1, 20]
	str	w1, [x2, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1181
.L1158:
	ldr	x1, [x22, x0, lsl 3]
	add	x2, x23, 648
	cbnz	x1, .L1182
	add	x1, x23, 648
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1158
.L1181:
	ldr	x24, .LC634
	mov	w20, -1
	.p2align 2
.L1159:
	ldr	w3, [x23, 648]
	add	x1, x23, 652
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L1160:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L1183
.L1162:
	ldr	w2, [x1]
	add	x1, x1, 4
	cmp	w3, w2
	bge	.L1160
	mov	w19, w0
	add	w0, w0, 1
	cmp	w0, 32
	mov	w3, w2
	bne	.L1162
.L1183:
	add	x2, x23, 648
	add	x0, x22, 256
	add	w1, w19, 1
	cmp	w3, wzr
	sxtw	x21, w19
	str	wzr, [x2, w19, sxtw 2]
	str	w1, [x0, 28]
	ble	.L1163
	ldr	x0, [x22, w19, sxtw 3]
	cbz	x0, .L1159
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1159
	ldr	w1, [x0, 76]
	cmp	w1, wzr
	ble	.L1165
	ldr	w0, [x0, 80]
	cbz	w0, .L1184
.L1165:
	mov	w21, 500
	b	.L1170
	.p2align 3
.L1168:
	subs	w21, w21, #1
	cbnz	w0, .L1159
	beq	.L1159
.L1170:
	mov	w0, w19
	bl	DecChanSyntax
	cmn	w0, #1
	mov	w20, w0
	bne	.L1168
	ldr	x4, [x23, 256]
	cbz	x4, .L1169
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w19
	blr	x4
.L1169:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
.L1184:
	add	x1, x29, 72
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L1185
.L1166:
	ldr	x20, [x22, x21, lsl 3]
	ldr	w1, [x29, 84]
	ldr	w2, [x20, 76]
	ldr	w0, [x20, 616]
	bl	GetNextDecodeMode
	str	w0, [x20, 616]
	ldr	x1, [x22, x21, lsl 3]
	ldr	w0, [x1, 616]
	cbz	w0, .L1167
	str	wzr, [x1, 608]
	str	wzr, [x1, 612]
	b	.L1165
.L1163:
	str	wzr, [x0, 28]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
.L1167:
	ldr	w0, [x1, 72]
	str	w0, [x1, 608]
	str	w0, [x1, 612]
	b	.L1165
.L1185:
	ldr	x3, [x24, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	blr	x3
	b	.L1166
	.size	DecSyntax, .-DecSyntax
	.align	3
.LC632:
	.xword	.LANCHOR0
	.align	3
.LC633:
	.xword	.LANCHOR5
	.align	3
.LC634:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RunProcess
	.type	VCTRL_RunProcess, %function
VCTRL_RunProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VCTRL_RecordPosTime
	ldr	x20, .LC637
	ldrb	w0, [x20, 2816]
	cmp	w0, 1
	beq	.L1195
.L1187:
	ldr	w0, [x20, 1124]
	mov	w1, 100
	str	w1, [x20, 280]
	cmp	w0, wzr
	ldr	x21, .LC638
	ble	.L1188
	ldr	x1, [x21, 240]
	blr	x1
.L1188:
	ldr	x1, [x21, 24]
	mov	w0, 0
	mov	w22, 0
	blr	x1
	bl	SM_Wakeup
	ldr	w0, [x20, 1120]
	mov	w1, 101
	str	w1, [x20, 280]
	cbz	w0, .L1196
.L1189:
	mov	w0, 102
	mov	w19, 0
	str	w0, [x20, 280]
	bl	VDMDRV_WakeUpVdm
	.p2align 2
.L1190:
	mov	w0, w19
	mov	w1, 0
	add	w19, w19, 1
	bl	DeleteRawPacketInBuffer
	cmp	w19, 32
	bne	.L1190
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	mov	w1, 105
	mov	w0, 1
	str	w1, [x20, 280]
	bl	VCTRL_RecordPosTime
	ldr	x3, [x21, 264]
	mov	w2, 10
	mov	w1, 0
	mov	w0, 0
	blr	x3
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1196:
	bl	DecSyntax
	mov	w22, w0
	b	.L1189
.L1195:
	mov	w0, 11
	bl	VCTRL_RecordPosTime
	strb	wzr, [x20, 2816]
	b	.L1187
	.size	VCTRL_RunProcess, .-VCTRL_RunProcess
	.align	3
.LC637:
	.xword	.LANCHOR0
	.align	3
.LC638:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VFMW_CTRL_thread_proc
	.type	VFMW_CTRL_thread_proc, %function
VFMW_CTRL_thread_proc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x0, x30
	mov	w21, 2
	bl	_mcount
	ldr	x20, .LC639
	ldr	x25, .LC641
	ldr	x22, .LC645
	ldr	x26, .LC643
	ldr	x23, .LC647
	ldr	x24, .LC648
.L1198:
.L1205:
	mov	x1, x25
	mov	w0, 2
	str	wzr, [x20, 280]
	bl	dprint_vfmw
	str	w21, [x20, 260]
	ldr	w0, [x20, 264]
	cmp	w0, 2
	bne	.L1220
	b	.L1203
	.p2align 3
.L1222:
	str	w21, [x20, 280]
	bl	VCTRL_RunProcess
	mov	x1, x22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x20, 264]
	cmp	w0, 2
	beq	.L1203
.L1220:
	cmp	w0, 3
	bne	.L1222
.L1201:
	ldr	x1, .LC650
	mov	w2, 6
	mov	w0, 2
	str	w2, [x20, 280]
	bl	dprint_vfmw
	str	wzr, [x20, 260]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1203:
	mov	w2, 4
	mov	x1, x26
	mov	w0, 2
	str	w2, [x20, 280]
	mov	w27, 5
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x20, 260]
	b	.L1200
	.p2align 3
.L1223:
	ldr	x1, [x24, 240]
	blr	x1
.L1200:
	mov	x1, x23
	mov	w0, 22
	str	w27, [x20, 280]
	bl	dprint_vfmw
	ldr	w1, [x20, 264]
	mov	w0, 10
	cmp	w1, 1
	beq	.L1205
	cmp	w1, 3
	bne	.L1223
	b	.L1201
	.size	VFMW_CTRL_thread_proc, .-VFMW_CTRL_thread_proc
	.align	3
.LC639:
	.xword	.LANCHOR0
	.align	3
.LC641:
	.xword	.LC640
	.align	3
.LC643:
	.xword	.LC642
	.align	3
.LC645:
	.xword	.LC644
	.align	3
.LC647:
	.xword	.LC646
	.align	3
.LC648:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC650:
	.xword	.LC649
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanVoQue
	.type	VCTRL_GetChanVoQue, %function
VCTRL_GetChanVoQue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC652
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1243
	ldr	w1, [x0, 600]
	cmp	w1, 20
	bls	.L1244
.L1243:
	mov	x0, 0
.L1225:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1244:
	ldr	x2, .LC653
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1227
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1227:
	.section	.rodata
	.align	0
	.align	2
.L1227:
	.byte	(.L1241 - .Lrtx1227) / 4
	.byte	(.L1228 - .Lrtx1227) / 4
	.byte	(.L1229 - .Lrtx1227) / 4
	.byte	(.L1230 - .Lrtx1227) / 4
	.byte	(.L1243 - .Lrtx1227) / 4
	.byte	(.L1231 - .Lrtx1227) / 4
	.byte	(.L1232 - .Lrtx1227) / 4
	.byte	(.L1243 - .Lrtx1227) / 4
	.byte	(.L1233 - .Lrtx1227) / 4
	.byte	(.L1234 - .Lrtx1227) / 4
	.byte	(.L1235 - .Lrtx1227) / 4
	.byte	(.L1235 - .Lrtx1227) / 4
	.byte	(.L1235 - .Lrtx1227) / 4
	.byte	(.L1236 - .Lrtx1227) / 4
	.byte	(.L1243 - .Lrtx1227) / 4
	.byte	(.L1237 - .Lrtx1227) / 4
	.byte	(.L1238 - .Lrtx1227) / 4
	.byte	(.L1239 - .Lrtx1227) / 4
	.byte	(.L1240 - .Lrtx1227) / 4
	.byte	(.L1243 - .Lrtx1227) / 4
	.byte	(.L1241 - .Lrtx1227) / 4
	.text
	.p2align 3
.L1241:
	add	x0, x0, 507904
	ldr	x19, [sp, 16]
	add	x0, x0, 1416
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1228:
	add	x0, x0, 561152
	add	x0, x0, 1648
	b	.L1225
	.p2align 3
.L1238:
	add	x0, x0, 516096
	add	x0, x0, 144
	b	.L1225
	.p2align 3
.L1237:
	add	x0, x0, 507904
	add	x0, x0, 2320
	b	.L1225
	.p2align 3
.L1236:
	add	x0, x0, 516096
	add	x0, x0, 1448
	b	.L1225
	.p2align 3
.L1235:
	add	x0, x0, 520192
	add	x0, x0, 1880
	b	.L1225
	.p2align 3
.L1240:
	add	x0, x0, 524288
	add	x0, x0, 3184
	b	.L1225
	.p2align 3
.L1239:
	add	x0, x0, 786432
	add	x0, x0, 1352
	b	.L1225
	.p2align 3
.L1230:
	add	x0, x0, 593920
	add	x0, x0, 3672
	b	.L1225
	.p2align 3
.L1229:
	add	x0, x0, 528384
	add	x0, x0, 3648
	b	.L1225
	.p2align 3
.L1234:
	add	x0, x0, 561152
	add	x0, x0, 2592
	b	.L1225
	.p2align 3
.L1233:
	add	x0, x0, 561152
	add	x0, x0, 2616
	b	.L1225
	.p2align 3
.L1232:
	add	x0, x0, 524288
	add	x0, x0, 1288
	b	.L1225
	.p2align 3
.L1231:
	add	x0, x0, 548864
	add	x0, x0, 2560
	b	.L1225
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	3
.LC652:
	.xword	.LANCHOR0
	.align	3
.LC653:
	.xword	.L1227
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_FindOccupiedFrame
	.type	VCTRL_FindOccupiedFrame, %function
VCTRL_FindOccupiedFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1261
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1255
	add	x2, x29, 48
	add	x1, x29, 40
	str	wzr, [x29, 40]
	str	wzr, [x2, -4]!
	bl	GetQueueImgNum
	ldr	w2, [x29, 40]
	mov	w0, -1
	cbz	w2, .L1247
	cmp	w2, 32
	bhi	.L1262
.L1249:
	ldr	x1, .LC658
	ldrh	w0, [x20, 4]
	ldr	x5, [x1, w19, sxtw 3]
	and	x0, x0, 63
	add	x0, x0, 2
	add	x6, x5, 507904
	ldr	x4, [x20, x0, lsl 3]
	ldr	w3, [x6, 1336]
	cmp	w3, 32
	bhi	.L1250
	mov	w1, 1
	b	.L1252
	.p2align 3
.L1253:
	ldrh	w0, [x20, 4]
	cmp	w3, 33
	add	w0, w0, w1
	add	w1, w1, 1
	and	x0, x0, 63
	add	x0, x0, 2
	ldr	x4, [x20, x0, lsl 3]
	beq	.L1250
.L1252:
	ubfiz	x0, x3, 4, 32
	ldr	w4, [x4, 20]
	add	x0, x5, x0
	add	w3, w3, 1
	add	x0, x0, 507904
	cmp	w1, w2
	str	wzr, [x0, 808]
	str	w4, [x0, 812]
	str	xzr, [x0, 816]
	str	w3, [x6, 1336]
	bcc	.L1253
	mov	w0, 0
.L1247:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1250:
	ldr	x1, .LC660
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1247
	.p2align 3
.L1262:
	ldr	x1, .LC657
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 40]
	cbnz	w2, .L1249
	mov	w0, 0
	b	.L1247
.L1255:
	mov	w0, -1
	b	.L1247
.L1261:
	ldr	x3, .LC654
	mov	w2, 3489
	ldr	x1, .LC655
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1247
	.size	VCTRL_FindOccupiedFrame, .-VCTRL_FindOccupiedFrame
	.align	3
.LC654:
	.xword	.LC237
	.align	3
.LC655:
	.xword	.LC5
	.align	3
.LC657:
	.xword	.LC656
	.align	3
.LC658:
	.xword	.LANCHOR0
	.align	3
.LC660:
	.xword	.LC659
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReportOccupiedFrame
	.type	VCTRL_ReportOccupiedFrame, %function
VCTRL_ReportOccupiedFrame:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w22, 31
	bhi	.L1280
	cbz	x19, .L1281
	mov	w0, w22
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1273
	ldr	x21, .LC665
	add	x23, x29, 80
	mov	w0, 4
	str	wzr, [x29, 72]
	ldr	x1, [x21, 24]
	str	wzr, [x23, -4]!
	blr	x1
	mov	x2, x23
	add	x1, x29, 72
	mov	x0, x20
	bl	GetQueueImgNum
	ldr	w2, [x29, 72]
	cbnz	w2, .L1282
	ldr	x6, .LC667
	ldr	x4, [x6, w22, sxtw 3]
	add	x0, x4, 507904
	ldr	w0, [x0, 1336]
	cbz	w0, .L1271
	mov	w2, 0
	sxtw	x0, w22
	.p2align 2
.L1272:
	sxtw	x3, w2
	add	w2, w2, 1
	add	x1, x3, 28672
	lsl	x3, x3, 4
	add	x1, x1, 3122
	add	x5, x19, x3
	lsl	x1, x1, 4
	sxth	w2, w2
	add	x4, x4, x1
	ldr	w4, [x4, 12]
	str	w4, [x5, 4]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, x1
	ldr	x1, [x1, 16]
	str	x1, [x5, 8]
	str	wzr, [x19, x3]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, 507904
	ldr	w1, [x1, 1336]
	cmp	w2, w1
	bcc	.L1272
	str	w1, [x19, 528]
	b	.L1271
	.p2align 3
.L1282:
	cmp	w2, 32
	bhi	.L1283
.L1268:
	mov	w0, 0
	.p2align 2
.L1270:
	ldrh	w1, [x20, 4]
	sbfiz	x3, x0, 4, 32
	add	w5, w0, 1
	add	x4, x19, x3
	add	w0, w1, w0
	and	x1, x0, 63
	sxth	w0, w5
	add	x1, x1, 2
	cmp	w2, w0
	ldr	x1, [x20, x1, lsl 3]
	ldr	w5, [x1, 20]
	str	w5, [x4, 4]
	ldr	x1, [x1, 504]
	str	x1, [x4, 8]
	str	wzr, [x19, x3]
	bhi	.L1270
	uxth	w1, w2
.L1269:
	ldrh	w0, [x20, 4]
	add	w0, w1, w0
	and	w0, w0, 63
	strh	w0, [x20, 4]
	str	w2, [x19, 528]
.L1271:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, 0
.L1265:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1283:
	ldr	x1, .LC666
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 72]
	cbnz	w2, .L1268
	mov	w2, 0
	mov	w1, 0
	b	.L1269
.L1273:
	mov	w0, -1
	b	.L1265
.L1280:
	ldr	x3, .LC661
	mov	w2, 3605
	ldr	x1, .LC662
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1265
.L1281:
	ldr	x3, .LC664
	mov	w2, 3606
	ldr	x1, .LC662
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1265
	.size	VCTRL_ReportOccupiedFrame, .-VCTRL_ReportOccupiedFrame
	.align	3
.LC661:
	.xword	.LC237
	.align	3
.LC662:
	.xword	.LC5
	.align	3
.LC664:
	.xword	.LC663
	.align	3
.LC665:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC666:
	.xword	.LC656
	.align	3
.LC667:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x22, x1
	mov	x21, x2
	mov	x23, x3
	bl	_mcount
	ldr	x20, .LC668
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1293
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	cbz	x0, .L1287
	mov	x1, x21
	mov	x2, x23
	bl	GetQueueImgNum
	ldr	x1, [x20, w19, sxtw 3]
	ldr	w0, [x1, 600]
	cbz	w0, .L1294
	cmp	w0, 16
	beq	.L1295
	cmp	w0, 17
	beq	.L1296
	cmp	w0, 15
	beq	.L1297
	cmp	w0, 18
	beq	.L1298
	mov	w0, 2
	str	w0, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1294:
	add	x1, x1, 536576
	ldr	w0, [x1, 1016]
	str	w0, [x22]
.L1284:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1287:
	str	wzr, [x23]
	str	wzr, [x21]
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1298:
	mov	w0, 5
	str	w0, [x22]
	b	.L1284
	.p2align 3
.L1295:
	add	x1, x1, 512000
	ldr	w0, [x1, 680]
	str	w0, [x22]
	b	.L1284
	.p2align 3
.L1296:
	mov	w0, 9
	str	w0, [x22]
	b	.L1284
	.p2align 3
.L1297:
	add	x1, x1, 11632640
	ldr	w0, [x1, 2200]
	str	w0, [x22]
	b	.L1284
	.p2align 3
.L1293:
	ldr	x3, .LC669
	mov	w2, 6662
	ldr	x1, .LC670
	bl	dprint_vfmw
	b	.L1284
	.size	VCTRL_GetChanImgNum, .-VCTRL_GetChanImgNum
	.align	3
.LC668:
	.xword	.LANCHOR0
	.align	3
.LC669:
	.xword	.LC8
	.align	3
.LC670:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanState
	.type	VCTRL_GetChanState, %function
VCTRL_GetChanState:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L1309
	cbz	x19, .L1310
	ldr	x21, .LC678
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L1311
	ldr	x0, .LC681
	mov	x2, 100
	mov	w1, 0
	str	wzr, [x29, 68]
	stp	wzr, wzr, [x29, 60]
	ldr	x3, [x0, 96]
	mov	x0, x19
	blr	x3
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1216]
	str	w0, [x19, 32]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1220]
	str	w0, [x19, 36]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1224]
	str	w0, [x19, 44]
	ldr	x5, [x21, w20, sxtw 3]
	add	x0, x5, 475136
	ldrsb	w0, [x0, 2171]
	cmp	w0, wzr
	ble	.L1307
	mov	x2, 40546
	sub	w4, w0, #1
	mov	w3, 88
	movk	x2, 0x7, lsl 16
	add	x0, x5, 495616
	mov	w1, 0
	umaddl	x2, w4, w3, x2
	add	x0, x0, 3594
	add	x3, x5, x2
	.p2align 2
.L1306:
	ldrsb	w2, [x0], 88
	cmp	w2, 3
	csinc	w1, w1, w1, ne
	cmp	x0, x3
	bne	.L1306
.L1304:
	str	w1, [x19, 84]
	add	x3, x29, 68
	add	x2, x29, 64
	mov	w0, w20
	ldr	x4, [x21, w20, sxtw 3]
	add	x1, x29, 60
	sxtw	x22, w20
	add	x4, x4, 475136
	ldrsb	w4, [x4, 2171]
	str	w4, [x19, 92]
	bl	VCTRL_GetChanImgNum
	ldr	x2, .LC682
	lsl	x0, x22, 4
	add	x22, x0, x22, lsl 2
	add	x1, x29, 72
	add	x2, x2, 776
	mov	w0, w20
	ldp	w4, w3, [x29, 64]
	add	x2, x2, x22, lsl 4
	sub	x2, x2, x22
	add	w3, w4, w3
	str	w3, [x19, 48]
	ldr	w3, [x2, 20]
	str	w3, [x19, 96]
	ldr	w2, [x2, 8]
	str	w2, [x19, 20]
	bl	SM_GetInfo
	ldp	w1, w2, [x29, 88]
	ldr	w0, [x29, 80]
	cmp	w2, 10
	stp	w1, w0, [x19, 52]
	cset	w0, gt
	str	w0, [x19, 80]
	mov	x0, 62848
	ldr	x1, [x21, w20, sxtw 3]
	movk	x0, 0x7, lsl 16
	add	x0, x1, x0
	ldrb	w0, [x0, 3616]
	and	w0, w0, 1
	str	w0, [x19, 88]
.L1299:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1309:
	ldr	x3, .LC674
	mov	w2, 1456
	ldr	x1, .LC675
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1311:
	ldr	x3, .LC680
	mov	w2, 1459
	ldr	x1, .LC675
	bl	dprint_vfmw
	b	.L1299
.L1307:
	mov	w1, 0
	b	.L1304
.L1310:
	ldr	x3, .LC677
	mov	w2, 1458
	ldr	x1, .LC675
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1299
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	3
.LC674:
	.xword	.LC673
	.align	3
.LC675:
	.xword	.LC5
	.align	3
.LC677:
	.xword	.LC676
	.align	3
.LC678:
	.xword	.LANCHOR0
	.align	3
.LC680:
	.xword	.LC679
	.align	3
.LC681:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC682:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanWidth
	.type	VCTRL_GetChanWidth, %function
VCTRL_GetChanWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1316
	ldr	x0, .LC686
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1317
	ldr	w0, [x0, 1332]
.L1314:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1316:
	ldr	x3, .LC684
	mov	w2, 6726
	ldr	x1, .LC685
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1314
.L1317:
	ldr	x3, .LC687
	mov	w2, 6727
	ldr	x1, .LC685
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1314
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	3
.LC684:
	.xword	.LC237
	.align	3
.LC685:
	.xword	.LC5
	.align	3
.LC686:
	.xword	.LANCHOR0
	.align	3
.LC687:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanHeight
	.type	VCTRL_GetChanHeight, %function
VCTRL_GetChanHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1322
	ldr	x0, .LC690
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1323
	ldr	w0, [x0, 1336]
.L1320:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1322:
	ldr	x3, .LC688
	mov	w2, 6734
	ldr	x1, .LC689
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1320
.L1323:
	ldr	x3, .LC691
	mov	w2, 6735
	ldr	x1, .LC689
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1320
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	3
.LC688:
	.xword	.LC237
	.align	3
.LC689:
	.xword	.LC5
	.align	3
.LC690:
	.xword	.LANCHOR0
	.align	3
.LC691:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCapLevel
	.type	VCTRL_GetChanCapLevel, %function
VCTRL_GetChanCapLevel:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1328
	ldr	x0, .LC694
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1327
	ldr	w0, [x0, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1328:
	ldr	x3, .LC692
	mov	w2, 6742
	ldr	x1, .LC693
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1327:
	mov	w0, 33
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	3
.LC692:
	.xword	.LC237
	.align	3
.LC693:
	.xword	.LC5
	.align	3
.LC694:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetVdecExtra
	.type	VCTRL_SetVdecExtra, %function
VCTRL_SetVdecExtra:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x20, .LC695
	add	w0, w21, 4096
	mov	w1, 10000
	add	w0, w0, 904
	mov	w2, w21
	cmp	w0, w1
	str	w21, [x20, 3560]
	bhi	.L1334
.L1330:
	mov	w3, 5000
	mov	w1, -5000
	cmp	w2, w3
	add	w0, w19, 4096
	csel	w2, w2, w3, le
	add	w0, w0, 904
	cmp	w2, w1
	mov	w3, 10000
	csel	w2, w2, w1, ge
	str	w19, [x20, 3564]
	cmp	w0, w3
	str	w2, [x20, 3560]
	bhi	.L1335
.L1331:
	mov	w2, 5000
	mov	w0, -5000
	cmp	w19, w2
	csel	w19, w19, w2, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
	str	w19, [x20, 3564]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1334:
	ldr	x1, .LC697
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x20, 3560]
	b	.L1330
	.p2align 3
.L1335:
	ldr	x1, .LC699
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x20, 3564]
	b	.L1331
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	3
.LC695:
	.xword	.LANCHOR3
	.align	3
.LC697:
	.xword	.LC696
	.align	3
.LC699:
	.xword	.LC698
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VfmwProcGetHandler
	.type	VfmwProcGetHandler, %function
VfmwProcGetHandler:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L1340
	ldr	x3, .LC702
	mov	w1, 1
	ldr	x0, .LC700
	add	x3, x3, 104
	b	.L1338
	.p2align 3
.L1339:
	ldr	w4, [x3, x4]
	add	w1, w1, 1
	ubfiz	x2, x1, 4, 32
	cmp	w4, w19
	add	x2, x3, x2
	beq	.L1337
	ldr	x0, [x2, 8]
.L1338:
	ubfiz	x4, x1, 4, 32
	cbnz	x0, .L1339
.L1337:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1340:
	ldr	x0, .LC701
	b	.L1337
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	3
.LC700:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC701:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC702:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1351
	cbz	w19, .L1348
	ldr	x4, .LC706
	mov	w0, 1
	ldr	x5, .LC704
	add	x4, x4, 104
	b	.L1344
	.p2align 3
.L1349:
	ldr	w6, [x4, x6]
	add	w0, w0, 1
	ubfiz	x3, x0, 4, 32
	cmp	w19, w6
	add	x3, x4, x3
	beq	.L1343
	ldr	x5, [x3, 8]
.L1344:
	ubfiz	x6, x0, 4, 32
	cbnz	x5, .L1349
	ldr	x1, .LC708
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
.L1351:
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1348:
	ldr	x5, .LC705
.L1343:
	mov	x0, x20
	blr	x5
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	3
.LC704:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC705:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC706:
	.xword	.LANCHOR4
	.align	3
.LC708:
	.xword	.LC707
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetLastFrameIdPlus2
	.type	VCTRL_GetLastFrameIdPlus2, %function
VCTRL_GetLastFrameIdPlus2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1356
	ldr	x0, .LC712
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1355
	ldr	w0, [x0, 436]
.L1354:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1356:
	ldr	x3, .LC710
	mov	w2, 7981
	ldr	x1, .LC711
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1354
.L1355:
	mov	w0, -1
	b	.L1354
	.size	VCTRL_GetLastFrameIdPlus2, .-VCTRL_GetLastFrameIdPlus2
	.align	3
.LC710:
	.xword	.LC237
	.align	3
.LC711:
	.xword	.LC5
	.align	3
.LC712:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetLastFrameIdPlus2
	.type	VCTRL_SetLastFrameIdPlus2, %function
VCTRL_SetLastFrameIdPlus2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1363
	ldr	x0, .LC715
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1357
	str	w20, [x0, 436]
.L1357:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1363:
	ldr	x3, .LC713
	mov	w2, 7993
	ldr	x1, .LC714
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameIdPlus2, .-VCTRL_SetLastFrameIdPlus2
	.align	3
.LC713:
	.xword	.LC237
	.align	3
.LC714:
	.xword	.LC5
	.align	3
.LC715:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetLastFrameState
	.type	VCTRL_SetLastFrameState, %function
VCTRL_SetLastFrameState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1370
	ldr	x0, .LC718
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1364
	str	w20, [x0, 440]
.L1364:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1370:
	ldr	x3, .LC716
	mov	w2, 8005
	ldr	x1, .LC717
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	3
.LC716:
	.xword	.LC237
	.align	3
.LC717:
	.xword	.LC5
	.align	3
.LC718:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReportLastFrame
	.type	VCTRL_ReportLastFrame, %function
VCTRL_ReportLastFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	w20, w1
	mov	x0, x30
	bl	_mcount
	cbz	w20, .L1378
	cmp	w20, 1
	mov	w0, 3
	mov	w1, 4
	csel	w0, w0, w1, eq
	cmp	w19, 31
	bhi	.L1385
.L1375:
	ldr	x21, .LC721
	ldr	x1, [x21, w19, sxtw 3]
	cbz	x1, .L1376
	str	w0, [x1, 440]
.L1376:
	ldr	x0, .LC722
	ldr	x4, [x0, 256]
	cbz	x4, .L1377
	add	x2, x29, 64
	mov	w3, 4
	mov	w1, 115
	mov	w0, w19
	str	w20, [x2, -8]!
	blr	x4
.L1377:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w20
	ldr	x1, .LC724
	mov	w2, w19
	mov	w0, 1
	ldr	w4, [x4, 440]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1378:
	cmp	w19, 31
	mov	w0, 2
	bls	.L1375
.L1385:
	ldr	x3, .LC719
	mov	w2, 8005
	ldr	x1, .LC720
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, .LC721
	b	.L1376
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	3
.LC719:
	.xword	.LC237
	.align	3
.LC720:
	.xword	.LC5
	.align	3
.LC721:
	.xword	.LANCHOR0
	.align	3
.LC722:
	.xword	.LANCHOR5
	.align	3
.LC724:
	.xword	.LC723
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OutputLastFrame
	.type	VCTRL_OutputLastFrame, %function
VCTRL_OutputLastFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC725
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 507904
	ldr	w1, [x0, 1400]
	cmp	w1, 18
	bls	.L1412
.L1407:
	mov	w19, -1
.L1404:
	mov	w0, w20
	mov	w1, 1
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC728
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1412:
	ldr	x2, .LC726
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1389
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1389:
	.section	.rodata
	.align	0
	.align	2
.L1389:
	.byte	(.L1388 - .Lrtx1389) / 4
	.byte	(.L1390 - .Lrtx1389) / 4
	.byte	(.L1391 - .Lrtx1389) / 4
	.byte	(.L1392 - .Lrtx1389) / 4
	.byte	(.L1407 - .Lrtx1389) / 4
	.byte	(.L1393 - .Lrtx1389) / 4
	.byte	(.L1394 - .Lrtx1389) / 4
	.byte	(.L1407 - .Lrtx1389) / 4
	.byte	(.L1395 - .Lrtx1389) / 4
	.byte	(.L1396 - .Lrtx1389) / 4
	.byte	(.L1397 - .Lrtx1389) / 4
	.byte	(.L1397 - .Lrtx1389) / 4
	.byte	(.L1397 - .Lrtx1389) / 4
	.byte	(.L1398 - .Lrtx1389) / 4
	.byte	(.L1407 - .Lrtx1389) / 4
	.byte	(.L1399 - .Lrtx1389) / 4
	.byte	(.L1400 - .Lrtx1389) / 4
	.byte	(.L1401 - .Lrtx1389) / 4
	.byte	(.L1402 - .Lrtx1389) / 4
	.text
	.p2align 3
.L1388:
	add	x0, x0, 1408
	bl	H264DEC_GetRemainImg
	mov	w19, w0
	.p2align 2
.L1387:
	cmn	w19, #1
	beq	.L1404
	cbnz	w19, .L1413
	mov	w0, w20
	mov	w1, 0
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC730
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1390:
	add	x0, x0, 1408
	bl	VC1DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1391:
	add	x0, x0, 1408
	bl	MPEG4DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1392:
	add	x0, x0, 1408
	bl	MPEG2DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1393:
	add	x0, x0, 1408
	bl	DIVX3DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1394:
	add	x0, x0, 1408
	bl	AVSDEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1395:
	add	x0, x0, 1408
	bl	REAL8DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1396:
	add	x0, x0, 1408
	bl	REAL9DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1397:
	add	x0, x0, 1408
	bl	VP6DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1398:
	add	x0, x0, 1408
	bl	VP8DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1399:
	add	x0, x0, 1408
	bl	MVC_DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1400:
	add	x0, x0, 1408
	bl	HEVCDEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1401:
	add	x0, x0, 1408
	bl	VP9DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1402:
	add	x0, x0, 1408
	bl	AVS2DEC_GetRemainImg
	mov	w19, w0
	b	.L1387
	.p2align 3
.L1413:
	mov	w1, w19
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC732
	sub	w2, w19, #2
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	3
.LC725:
	.xword	.LANCHOR0
	.align	3
.LC726:
	.xword	.L1389
	.align	3
.LC728:
	.xword	.LC727
	.align	3
.LC730:
	.xword	.LC729
	.align	3
.LC732:
	.xword	.LC731
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x23, x2
	mov	w22, w3
	bl	_mcount
	ldr	x21, .LC733
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1453
	ldr	w1, [x0, 600]
	ldr	w24, [x0, 1272]
	cmp	w1, 18
	bls	.L1454
.L1414:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1454:
	ldr	x2, .LC736
	ldrh	w1, [x2,w1,uxtw #1]
	adr	x2, .Lrtx1418
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx1418:
	.section	.rodata
	.align	0
	.align	2
.L1418:
	.2byte	(.L1417 - .Lrtx1418) / 4
	.2byte	(.L1419 - .Lrtx1418) / 4
	.2byte	(.L1420 - .Lrtx1418) / 4
	.2byte	(.L1421 - .Lrtx1418) / 4
	.2byte	(.L1414 - .Lrtx1418) / 4
	.2byte	(.L1422 - .Lrtx1418) / 4
	.2byte	(.L1423 - .Lrtx1418) / 4
	.2byte	(.L1414 - .Lrtx1418) / 4
	.2byte	(.L1424 - .Lrtx1418) / 4
	.2byte	(.L1425 - .Lrtx1418) / 4
	.2byte	(.L1426 - .Lrtx1418) / 4
	.2byte	(.L1426 - .Lrtx1418) / 4
	.2byte	(.L1426 - .Lrtx1418) / 4
	.2byte	(.L1427 - .Lrtx1418) / 4
	.2byte	(.L1414 - .Lrtx1418) / 4
	.2byte	(.L1428 - .Lrtx1418) / 4
	.2byte	(.L1429 - .Lrtx1418) / 4
	.2byte	(.L1430 - .Lrtx1418) / 4
	.2byte	(.L1431 - .Lrtx1418) / 4
	.text
	.p2align 3
.L1431:
	add	x0, x0, 507904
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1408
	bl	AVS2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w0, [x0, 1408]
	cmp	w0, 1
	beq	.L1455
.L1439:
	cmp	w24, 1
	beq	.L1414
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1456]
	b	.L1414
	.p2align 3
.L1430:
	add	x0, x0, 507904
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1408
	bl	VP9DEC_VDMPostProc
	cmp	w24, 1
	beq	.L1414
.L1451:
	ldr	x0, [x21, w19, sxtw 3]
.L1452:
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1429:
	add	x0, x0, 507904
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1408
	bl	HEVCDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w0, [x0, 1419]
	cmp	w0, 1
	beq	.L1456
.L1434:
	cmp	w24, 1
	beq	.L1414
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 512000
	str	xzr, [x0, 360]
	b	.L1414
	.p2align 3
.L1428:
	add	x0, x0, 507904
	mov	w1, w20
	mov	w2, 1
	add	x0, x0, 1408
	bl	MVC_DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w1, [x0, 1409]
	cmp	w1, 1
	beq	.L1457
	str	xzr, [x0, 1640]
	b	.L1414
	.p2align 3
.L1427:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1408
	bl	VP8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
	b	.L1414
	.p2align 3
.L1426:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1408
	bl	VP6DEC_VDMPostProc
	b	.L1451
	.p2align 3
.L1425:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1408
	bl	REAL9DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
	b	.L1414
	.p2align 3
.L1424:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1408
	bl	REAL8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
	b	.L1414
	.p2align 3
.L1423:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1408
	bl	AVSDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w1, [x0, 1408]
	cmp	w1, 1
	beq	.L1458
	str	xzr, [x0, 1432]
	b	.L1414
	.p2align 3
.L1422:
	mov	w0, w22
	bl	VDMDRV_GetSwitchRounding
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1408
	bl	DIVX3DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1416]
	b	.L1414
	.p2align 3
.L1421:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1408
	bl	MPEG2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 598016
	ldrb	w1, [x1, 202]
	cmp	w1, 1
	bne	.L1452
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 598016
	strb	wzr, [x1, 202]
	b	.L1452
	.p2align 3
.L1420:
	add	x0, x0, 507904
	mov	w1, w20
	mov	x2, x23
	add	x0, x0, 1408
	bl	MPEG4DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 532480
	ldrb	w1, [x1, 196]
	cmp	w1, 1
	beq	.L1459
.L1437:
	add	x0, x0, 507904
	str	xzr, [x0, 2448]
	b	.L1414
	.p2align 3
.L1419:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1408
	bl	VC1DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 520192
	ldrb	w1, [x1, 3935]
	cmp	w1, 1
	bne	.L1452
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 520192
	strb	wzr, [x1, 3935]
	b	.L1452
	.p2align 3
.L1417:
	add	x0, x0, 507904
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1408
	bl	H264DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 520192
	ldrb	w0, [x0, 4048]
	cmp	w0, 1
	beq	.L1460
.L1432:
	cmp	w24, 1
	beq	.L1414
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 2024]
	b	.L1414
	.p2align 3
.L1458:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1408]
	str	xzr, [x0, 1432]
	b	.L1414
	.p2align 3
.L1457:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1409]
	str	xzr, [x0, 1640]
	b	.L1414
	.p2align 3
.L1453:
	ldr	x3, .LC734
	mov	w2, 4566
	ldr	x1, .LC735
	bl	dprint_vfmw
	b	.L1414
	.p2align 3
.L1459:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 532480
	strb	wzr, [x1, 196]
	b	.L1437
.L1460:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 520192
	strb	wzr, [x0, 4048]
	b	.L1432
.L1456:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1419]
	b	.L1434
.L1455:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1408]
	b	.L1439
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	3
.LC733:
	.xword	.LANCHOR0
	.align	3
.LC734:
	.xword	.LC8
	.align	3
.LC735:
	.xword	.LC5
	.align	3
.LC736:
	.xword	.L1418
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	cmp	w19, 31
	bhi	.L1469
	ldr	x0, .LC739
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1470
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L1465
	ldr	x3, .LC741
	mov	w2, 4757
	ldr	x1, .LC738
	mov	w0, 0
	bl	dprint_vfmw
.L1461:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1465:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L1461
	mov	w3, w22
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	bl	VCTRL_PostProc
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1469:
	ldr	x3, .LC737
	mov	w2, 4755
	ldr	x1, .LC738
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1470:
	ldr	x3, .LC740
	mov	w2, 4756
	ldr	x1, .LC738
	bl	dprint_vfmw
	b	.L1461
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	3
.LC737:
	.xword	.LC443
	.align	3
.LC738:
	.xword	.LC5
	.align	3
.LC739:
	.xword	.LANCHOR0
	.align	3
.LC740:
	.xword	.LC384
	.align	3
.LC741:
	.xword	.LC448
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SvdecLastFrame
	.type	VCTRL_SvdecLastFrame, %function
VCTRL_SvdecLastFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	w1, w20, 2
	mov	w0, w19
	bl	VCTRL_ReportLastFrame
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_YuvFormat
	.type	Get_YuvFormat, %function
Get_YuvFormat:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 6
	bls	.L1490
	ldr	x1, .LC744
	mov	w3, w19
	mov	w2, 8712
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 13
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1490:
	ldr	x0, .LC742
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1475
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1475:
	.section	.rodata
	.align	0
	.align	2
.L1475:
	.byte	(.L1474 - .Lrtx1475) / 4
	.byte	(.L1476 - .Lrtx1475) / 4
	.byte	(.L1477 - .Lrtx1475) / 4
	.byte	(.L1478 - .Lrtx1475) / 4
	.byte	(.L1479 - .Lrtx1475) / 4
	.byte	(.L1480 - .Lrtx1475) / 4
	.byte	(.L1481 - .Lrtx1475) / 4
	.text
	.p2align 3
.L1480:
	cmp	w20, 1
	mov	w1, 12
	mov	w0, 13
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1481:
	cmp	w20, 1
	mov	w0, 7
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1474:
	cmp	w20, 1
	mov	w0, 6
	csel	w0, wzr, w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1476:
	cmp	w20, 1
	mov	w1, 8
	mov	w0, 2
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1477:
	cmp	w20, 1
	mov	w1, 10
	mov	w0, 4
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1478:
	cmp	w20, 1
	mov	w1, 9
	mov	w0, 3
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1479:
	cmp	w20, 1
	mov	w1, 11
	mov	w0, 5
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	3
.LC742:
	.xword	.L1475
	.align	3
.LC744:
	.xword	.LC743
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 40]
	mov	w0, w21
	bl	FSP_GetLogicIdByPhyAddr
	cmn	w0, #1
	mov	w22, w0
	beq	.L1500
	ldr	w0, [x20, 4]
	cmp	w0, 1
	beq	.L1494
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_ClearLogicFs
	mov	w0, 0
.L1493:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1494:
	ldr	w0, [x20, 48]
	bl	MEM_Phy2Vir
	cbz	x0, .L1501
.L1495:
	mov	w1, w22
	mov	w0, w21
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1502
	str	w22, [x0, 148]
	mov	w23, 1
	ldr	x0, [x20, 64]
	str	x0, [x19, 576]
	ldr	x0, [x20, 64]
	str	x0, [x19, 584]
	ldr	x0, [x20, 64]
	str	x0, [x19, 592]
	ldr	x0, [x20, 64]
	str	x0, [x19, 600]
	stp	w23, wzr, [x19]
	stp	wzr, wzr, [x19, 8]
	ldr	w0, [x20, 40]
	str	w0, [x19, 20]
	str	w0, [x19, 36]
	ldr	w1, [x20, 48]
	str	w1, [x19, 24]
	str	w1, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 504]
	ldr	w0, [x19, 24]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w0, [x19, 20]
	mov	x2, 4
	ldr	w1, [x20, 44]
	ldr	w3, [x19, 24]
	add	w1, w0, w1
	str	w1, [x19, 28]
	ldr	x4, .LC751
	ldr	w0, [x20, 44]
	str	wzr, [x19, 52]
	add	w0, w3, w0
	str	w0, [x19, 32]
	ldr	w0, [x20, 12]
	str	w0, [x19, 68]
	ldr	w0, [x20, 16]
	str	w0, [x19, 72]
	ldr	w0, [x20, 12]
	str	w0, [x19, 76]
	lsr	w1, w0, 1
	ldr	w0, [x20, 16]
	stp	w0, w1, [x19, 80]
	lsr	w0, w0, 1
	str	w0, [x19, 88]
	mov	w1, 0
	add	x0, x19, 64
	ldr	w3, [x20, 44]
	ldr	x4, [x4, 96]
	stp	wzr, w3, [x19, 108]
	str	wzr, [x19, 152]
	lsr	w3, w3, 1
	str	w23, [x19, 164]
	str	w3, [x19, 116]
	blr	x4
	ldrb	w0, [x19, 65]
	ldrb	w1, [x19, 64]
	and	w0, w0, -4
	and	w1, w1, 224
	orr	w0, w0, 12
	bfi	w1, w23, 5, 3
	bfi	w0, w23, 4, 2
	strb	w1, [x19, 64]
	strb	w0, [x19, 65]
	ldr	w0, [x20, 24]
	str	w0, [x19, 212]
	bl	MEM_Phy2Vir
	str	x0, [x19, 520]
	ldr	w1, [x20]
	ldr	w0, [x20, 8]
	bl	Get_YuvFormat
	cmp	w0, 13
	beq	.L1503
	str	w0, [x19, 388]
	mov	w24, 20
	mov	w2, w23
	mov	w1, w22
	ldr	w3, [x20, 56]
	mov	w0, w21
	str	w3, [x19, 364]
	ldr	w3, [x20, 60]
	str	w3, [x19, 360]
	ldr	w3, [x20, 52]
	str	w3, [x19, 368]
	str	w24, [x19, 296]
	bl	FSP_SetDisplay
	ldr	x2, .LC754
	mov	x4, x19
	mov	w1, w24
	mov	w0, w21
	ldr	x2, [x2, w21, sxtw 3]
	add	x2, x2, 507904
	add	x3, x2, 1416
	add	x2, x2, 1408
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w0, 0
	beq	.L1493
	ldr	x1, [x19, 544]
	mov	w0, w21
	bl	FreeUsdByDec
	str	xzr, [x19, 544]
	ldr	x1, [x19, 552]
	mov	w0, w21
	bl	FreeUsdByDec
	str	xzr, [x19, 552]
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L1493
	.p2align 3
.L1501:
	ldr	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1495
	ldr	x1, .LC748
	mov	w0, 0
	ldr	w2, [x20, 48]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1493
.L1500:
	ldr	x1, .LC746
	mov	w0, 0
	ldr	w2, [x20, 40]
	bl	dprint_vfmw
	mov	w0, w22
	b	.L1493
.L1503:
	ldr	x1, .LC753
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1493
.L1502:
	ldr	x1, .LC750
	mov	w2, 5249
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1493
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
	.align	3
.LC746:
	.xword	.LC745
	.align	3
.LC748:
	.xword	.LC747
	.align	3
.LC750:
	.xword	.LC749
	.align	3
.LC751:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC753:
	.xword	.LC752
	.align	3
.LC754:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PutUsrdecFrame
	.type	VCTRL_PutUsrdecFrame, %function
VCTRL_PutUsrdecFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x20, .LC755
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1512
	cbz	x21, .L1513
	ldr	w2, [x0, 600]
	cmp	w2, 20
	bne	.L1514
	ldr	x3, .LC762
	mov	x1, x21
	mov	x2, 72
	add	x0, x0, 528
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 528
	bl	VDH_PutUsrdecFrame
	cbnz	w0, .L1515
.L1506:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1514:
	ldr	x1, .LC761
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1506
	.p2align 3
.L1515:
	ldr	x1, .LC764
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1506
.L1513:
	ldr	x3, .LC759
	mov	w2, 5402
	ldr	x1, .LC757
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1506
.L1512:
	ldr	x3, .LC756
	mov	w2, 5401
	ldr	x1, .LC757
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1506
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	3
.LC755:
	.xword	.LANCHOR0
	.align	3
.LC756:
	.xword	.LC8
	.align	3
.LC757:
	.xword	.LC5
	.align	3
.LC759:
	.xword	.LC758
	.align	3
.LC761:
	.xword	.LC760
	.align	3
.LC762:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC764:
	.xword	.LC763
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetHardware
	.type	VCTRL_ResetHardware, %function
VCTRL_ResetHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	SCDDRV_ResetSCD
	mov	w0, w19
	bl	VDMDRV_ResetVDH
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_ResetHardware, .-VCTRL_ResetHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CanBeDecodedByHardWare
	.type	VCTRL_CanBeDecodedByHardWare, %function
VCTRL_CanBeDecodedByHardWare:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 4
	mov	w0, 0
	ccmp	w19, 7, 4, ne
	beq	.L1518
	mov	w0, w19
	bl	VCTRL_CanBeDecodedByHardWare.part.20
.L1518:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CanBeDecodedByHardWare, .-VCTRL_CanBeDecodedByHardWare
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanOpenAndRun
	.type	VCTRL_IsChanOpenAndRun, %function
VCTRL_IsChanOpenAndRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4]
	cmp	w0, 1
	beq	.L1523
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1523:
	ldr	w0, [x19, 8]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IsChanOpenAndRun, .-VCTRL_IsChanOpenAndRun
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 31
	bhi	.L1575
	ldr	x20, .LC767
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L1576
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1528
	ldr	w0, [x0, 600]
	cmp	w0, 21
	beq	.L1528
	cmp	w0, 7
	ccmp	w0, 4, 4, ne
	beq	.L1524
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	cbz	w0, .L1524
	mov	x19, 0
	mov	w22, 0
	.p2align 2
.L1533:
	cmp	w19, 31
	bhi	.L1532
	ldr	x0, [x20, x19, lsl 3]
	cbz	x0, .L1532
	ldr	w1, [x0, 4]
	cbz	w1, .L1532
	ldr	w1, [x0, 8]
	cbz	w1, .L1532
	ldr	w1, [x0, 20]
	cbz	w1, .L1532
	ldr	w1, [x0, 600]
	cmp	w1, 21
	mov	w0, w1
	beq	.L1532
	cmp	w1, 4
	ccmp	w1, 7, 4, ne
	beq	.L1532
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	cmp	w0, wzr
	csinc	w22, w22, w22, eq
	.p2align 2
.L1532:
	add	x19, x19, 1
	cmp	x19, 32
	bne	.L1533
	cmp	w22, 1
	beq	.L1577
.L1534:
	mov	x0, x20
	add	x3, x20, 256
	mov	w2, 0
	.p2align 2
.L1541:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L1540
	ldr	w1, [x1, 600]
	cmp	w1, 6
	csinc	w2, w2, wzr, ne
.L1540:
	cmp	x3, x0
	bne	.L1541
	cmp	w2, 1
	beq	.L1578
.L1542:
	ldr	x0, [x20, w21, sxtw 3]
	ldr	w0, [x0, 600]
	cmp	w0, 1
	bne	.L1524
	ldr	x0, .LC772
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1579
	ldr	x0, .LC773
	ldr	x1, [x0, 56]
	cbz	x1, .L1524
	mov	w0, 0
	blr	x1
	b	.L1524
	.p2align 3
.L1528:
	ldr	x1, .LC771
	mov	w2, 8781
	mov	w0, 0
	bl	dprint_vfmw
.L1524:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1575:
	ldr	x1, .LC766
	mov	w2, 8769
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1577:
	ldr	x19, .LC772
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1580
	mov	w1, 0
	mov	w0, w22
	bl	VDH_Need_Module
.L1537:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1538
	ldr	x0, .LC773
	ldr	x1, [x0, 40]
	cbz	x1, .L1581
	mov	w0, 0
	blr	x1
	b	.L1534
.L1578:
	ldr	x0, .LC772
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1582
	mov	w1, 0
	mov	w0, 3
	bl	VDH_Need_Module
	b	.L1542
.L1582:
	ldr	x0, .LC773
	ldr	x1, [x0, 24]
	cbz	x1, .L1583
	mov	w0, 0
	blr	x1
	b	.L1542
.L1580:
	ldr	x0, .LC773
	ldr	x1, [x0, 8]
	cbz	x1, .L1584
	mov	w0, 0
	blr	x1
	b	.L1537
.L1576:
	ldr	x1, .LC769
	mov	w2, 8775
	bl	dprint_vfmw
	b	.L1524
.L1579:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_Need_Module
	b	.L1524
.L1538:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Need_Module
	b	.L1534
.L1581:
	ldr	x1, .LC774
	mov	w2, 8830
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1534
.L1583:
	ldr	x1, .LC774
	mov	w2, 8861
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1542
.L1584:
	ldr	x1, .LC774
	mov	w2, 8816
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1537
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	3
.LC766:
	.xword	.LC765
	.align	3
.LC767:
	.xword	.LANCHOR0
	.align	3
.LC769:
	.xword	.LC768
	.align	3
.LC771:
	.xword	.LC770
	.align	3
.LC772:
	.xword	g_HalDisable
	.align	3
.LC773:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC774:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StartChan
	.type	VCTRL_StartChan, %function
VCTRL_StartChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L1596
	ldr	x19, .LC778
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L1597
	ldr	w21, [x0, 4]
	cmp	w21, 1
	bne	.L1598
	ldr	w0, [x0, 600]
	cmp	w0, 21
	beq	.L1599
	mov	w0, w20
	bl	SM_Start
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 8]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 12]
	ldr	x0, [x19, w20, sxtw 3]
	str	wzr, [x0, 24]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 16]
	ldr	x1, [x19, w20, sxtw 3]
	ldr	w0, [x1, 20]
	cbnz	w0, .L1591
	str	w21, [x1, 20]
	mov	x1, 0
	ldr	x0, .LC783
	ldr	x5, .LC784
	b	.L1594
	.p2align 3
.L1601:
	ldr	w4, [x2, 20]
	str	w4, [x3, x1, lsl 2]
	ldr	w2, [x2, 20]
	str	w2, [x5, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	beq	.L1600
.L1594:
	ldr	x2, [x19, x1, lsl 3]
	add	x3, x0, 1672
	cbnz	x2, .L1601
	add	x2, x0, 1672
	str	wzr, [x5, x1, lsl 2]
	str	wzr, [x2, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	bne	.L1594
	.p2align 2
.L1600:
	add	x0, x0, 1672
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
.L1591:
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	bl	VCTRL_OpenHardware
	ldr	x19, .LC785
	ldr	x0, .LC786
	mov	x2, 12
	mov	w1, 0
	ldr	x3, [x19, 96]
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 720
	ldr	x0, .LC787
	mov	w1, 0
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 2
	ldr	x0, .LC788
	mov	w1, 0
	blr	x3
	ldr	x0, .LC789
	mov	x2, 120
	ldr	x3, [x19, 96]
	mov	w1, 0
	blr	x3
	mov	w0, 0
.L1587:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1598:
	ldr	x3, .LC780
	mov	w2, 2509
	ldr	x1, .LC777
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1587
.L1596:
	ldr	x3, .LC776
	mov	w2, 2507
	ldr	x1, .LC777
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1587
.L1599:
	ldr	x3, .LC782
	mov	w2, 2510
	ldr	x1, .LC777
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1587
.L1597:
	ldr	x3, .LC779
	mov	w2, 2508
	ldr	x1, .LC777
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1587
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	3
.LC776:
	.xword	.LC237
	.align	3
.LC777:
	.xword	.LC5
	.align	3
.LC778:
	.xword	.LANCHOR0
	.align	3
.LC779:
	.xword	.LC281
	.align	3
.LC780:
	.xword	.LC473
	.align	3
.LC782:
	.xword	.LC781
	.align	3
.LC783:
	.xword	.LANCHOR6
	.align	3
.LC784:
	.xword	g_ChanCtx
	.align	3
.LC785:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC786:
	.xword	g_TimeRecId
	.align	3
.LC787:
	.xword	g_TimeRecTable
	.align	3
.LC788:
	.xword	g_DataRecId
	.align	3
.LC789:
	.xword	g_DataTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStartChan, %function
VfmwProc_TestStartChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC792
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	3
.LC792:
	.xword	.LC791
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	mov	x0, x30
	mov	w24, 0
	mov	w22, 0
	bl	_mcount
	ldr	x19, .LC793
	mov	w0, 0
	add	x23, x19, 256
	b	.L1612
	.p2align 3
.L1654:
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1651
.L1604:
	add	x19, x19, 8
	cmp	x19, x23
	beq	.L1652
.L1612:
	ldr	x20, [x19]
	cbz	x20, .L1604
	ldr	w21, [x20, 600]
	cbnz	w0, .L1605
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1653
.L1605:
	cmp	w22, wzr
	ccmp	w21, 1, 0, eq
	beq	.L1654
.L1608:
	cmp	w24, wzr
	ccmp	w21, 6, 0, eq
	bne	.L1604
	ldr	w1, [x20, 4]
	cmp	w1, 1
	bne	.L1604
	ldr	w26, [x20, 8]
.L1632:
	cmp	w26, 1
	add	x19, x19, 8
	csinc	w24, w24, wzr, ne
	cmp	x19, x23
	bne	.L1612
	.p2align 2
.L1652:
	cbnz	w0, .L1613
	ldr	x19, .LC794
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1618
	mov	w0, w25
	bl	SCDDRV_ResetSCD
	mov	w0, w25
	bl	VDMDRV_ResetVDH
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1618
	mov	w1, 0
	mov	w0, 1
	bl	VDH_UnNeed_Module
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1621
.L1660:
	ldr	x0, .LC795
	ldr	x1, [x0, 48]
	cbz	x1, .L1655
	mov	w0, 0
	blr	x1
.L1624:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle
.L1613:
	cbnz	w24, .L1625
	ldr	x0, .LC794
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1656
	mov	w1, 0
	mov	w0, 3
	bl	VDH_UnNeed_Module
.L1625:
	cbnz	w22, .L1603
	ldr	x0, .LC794
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1657
	ldr	x0, .LC795
	ldr	x1, [x0, 64]
	cbz	x1, .L1603
	mov	w0, 0
	blr	x1
.L1603:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1653:
	ldr	w26, [x20, 8]
	cmp	w26, 1
	beq	.L1658
.L1607:
	cmp	w21, 1
	ccmp	w22, wzr, 0, eq
	bne	.L1608
.L1631:
	cmp	w26, 1
	csinc	w22, w22, wzr, ne
	cmp	w21, 6
	ccmp	w24, wzr, 0, eq
	beq	.L1632
	b	.L1604
	.p2align 3
.L1658:
	cmp	w21, 4
	ccmp	w21, 7, 4, ne
	beq	.L1607
	mov	w0, w21
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	cmp	w0, wzr
	cset	w0, ne
	b	.L1607
.L1618:
	ldr	x0, .LC795
	ldr	x1, [x0, 16]
	cbz	x1, .L1659
	mov	w0, 0
	blr	x1
.L1620:
	mov	w0, 0
	bl	VDMDRV_SetStateIdle
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1660
.L1621:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_UnNeed_Module
	b	.L1613
.L1657:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_UnNeed_Module
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1656:
	ldr	x0, .LC795
	ldr	x1, [x0, 32]
	cbz	x1, .L1661
	mov	w0, 0
	blr	x1
	b	.L1625
.L1655:
	ldr	x1, .LC796
	mov	w2, 8959
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1624
.L1659:
	ldr	x1, .LC796
	mov	w2, 8944
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1620
.L1661:
	ldr	x1, .LC796
	mov	w2, 8977
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1625
.L1651:
	ldr	w26, [x20, 8]
	b	.L1631
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	3
.LC793:
	.xword	.LANCHOR0
	.align	3
.LC794:
	.xword	g_HalDisable
	.align	3
.LC795:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC796:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopChan
	.type	VCTRL_StopChan, %function
VCTRL_StopChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1668
	ldr	x20, .LC800
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1669
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1667
	str	w1, [x0, 24]
	mov	w0, w19
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 12]
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 8]
	bl	SM_Stop
	cbnz	w0, .L1667
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	str	wzr, [x1, 24]
	bl	VCTRL_CloseHardware
	mov	w0, 0
.L1664:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1667:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1668:
	ldr	x3, .LC798
	mov	w2, 2601
	ldr	x1, .LC799
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1664
.L1669:
	ldr	x3, .LC802
	mov	w2, 2602
	ldr	x1, .LC799
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1664
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	3
.LC798:
	.xword	.LC237
	.align	3
.LC799:
	.xword	.LC5
	.align	3
.LC800:
	.xword	.LANCHOR0
	.align	3
.LC802:
	.xword	.LC801
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopChanWithCheck
	.type	VCTRL_StopChanWithCheck, %function
VCTRL_StopChanWithCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x19, .LC803
	b	.L1672
	.p2align 3
.L1676:
	ldr	x1, [x19, 240]
	mov	w0, 10
	add	w20, w20, 1
	blr	x1
	cmp	w20, 50
	beq	.L1674
.L1672:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, w22
	bl	VCTRL_StopChan
	mov	w21, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cbnz	w21, .L1676
	cmp	w20, 49
	bgt	.L1674
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1674:
	ldr	x1, .LC805
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
	.align	3
.LC803:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC805:
	.xword	.LC804
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetChanWithOption
	.type	VCTRL_ResetChanWithOption, %function
VCTRL_ResetChanWithOption:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	sxtw	x21, w0
	mov	x0, x30
	mov	x23, x1
	mov	x19, x21
	bl	_mcount
	ldr	x20, .LC806
	ldr	x1, [x20, w21, sxtw 3]
	cbz	x1, .L1704
	ldr	w0, [x23]
	cmp	w0, 1
	bhi	.L1705
	mov	w0, w21
	ldr	w22, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x24, .LC811
	ldr	x0, .LC812
	lsl	x2, x21, 4
	ldr	x1, [x20, w21, sxtw 3]
	add	x21, x2, x21, lsl 2
	add	x0, x0, 776
	ldr	x3, [x24, 96]
	add	x0, x0, x21, lsl 4
	mov	x2, 300
	str	wzr, [x1, 444]
	sub	x0, x0, x21
	str	wzr, [x1, 448]
	mov	w1, 0
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1706
	add	x0, x0, 503808
	str	wzr, [x0, 1316]
.L1682:
	ldr	x1, [x24, 24]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	ldr	x1, [x24, 32]
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	ldr	w2, [x23, 4]
	str	w2, [x1, 1264]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w0, [x0, 600]
	add	x1, x1, 1408
	bl	ReleaseCurPic
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 456
	ldr	x3, [x24, 96]
	mov	w1, 0
	add	x0, x0, 744
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x1, -1
	ldr	w2, [x0, 1488]
	str	x1, [x0, 664]
	cmp	w2, 1
	str	x1, [x0, 672]
	str	wzr, [x0, 1200]
	beq	.L1707
.L1683:
	ldr	w0, [x0, 600]
	cmp	w0, 20
	beq	.L1684
	ldr	w0, [x23, 8]
	cbz	w0, .L1708
.L1684:
	mov	w0, w19
	bl	FSP_EmptyInstance
.L1685:
	mov	w0, w19
	bl	InitUsdPool
	ldr	w0, [x23]
	cbz	w0, .L1709
.L1686:
	ldr	w0, [x20, 1396]
	cbz	w0, .L1687
	add	x20, x20, 2192
	str	w19, [x29, 76]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1689
	mov	w0, 512
	add	x1, x29, 76
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1689
	add	x1, x29, 76
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1689:
	ldr	x1, .LC814
	mov	w0, 32
	bl	dprint_vfmw
.L1687:
	cbnz	w22, .L1710
.L1691:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1679:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1709:
	mov	w0, w19
	bl	SM_Reset
	b	.L1686
	.p2align 3
.L1710:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1691
	.p2align 3
.L1707:
	add	x1, x0, 507904
	str	wzr, [x0, 1536]
	str	wzr, [x1, 1340]
	b	.L1683
	.p2align 3
.L1708:
	mov	w0, w19
	bl	FSP_ResetInstance
	b	.L1685
	.p2align 3
.L1705:
	ldr	x1, .LC810
	mov	w2, 3362
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1706:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1682
.L1704:
	ldr	x3, .LC807
	mov	w2, 3358
	ldr	x1, .LC808
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1679
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	3
.LC806:
	.xword	.LANCHOR0
	.align	3
.LC807:
	.xword	.LC8
	.align	3
.LC808:
	.xword	.LC5
	.align	3
.LC810:
	.xword	.LC809
	.align	3
.LC811:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC812:
	.xword	.LANCHOR5
	.align	3
.LC814:
	.xword	.LC813
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetChan
	.type	VCTRL_ResetChan, %function
VCTRL_ResetChan:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC817
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1734
	mov	w0, w19
	ldr	w21, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x22, .LC820
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, 4
	ldr	x2, [x22, 24]
	str	wzr, [x1, 444]
	str	wzr, [x1, 448]
	blr	x2
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 1488]
	cmp	w1, 1
	beq	.L1735
.L1714:
	sxtw	x3, w19
	ldr	x0, .LC821
	lsl	x1, x3, 4
	ldr	x4, [x22, 96]
	add	x3, x1, x3, lsl 2
	add	x0, x0, 776
	mov	x2, 300
	mov	w1, 0
	add	x0, x0, x3, lsl 4
	sub	x0, x0, x3
	blr	x4
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1736
	add	x0, x0, 503808
	str	wzr, [x0, 1316]
.L1716:
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	str	wzr, [x1, 1264]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 456
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 744
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, -1
	add	x1, x0, 507904
	str	x2, [x0, 664]
	str	x2, [x0, 672]
	str	wzr, [x0, 1200]
	str	wzr, [x1, 1360]
	str	wzr, [x1, 1364]
	str	wzr, [x1, 1368]
	ldr	w2, [x0, 1488]
	cmp	w2, 1
	beq	.L1737
.L1717:
	ldr	w0, [x0, 600]
	cmp	w0, 20
	mov	w0, w19
	beq	.L1718
	bl	FSP_ResetInstance
.L1719:
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	InitUsdPool
	mov	w0, w19
	bl	SM_Reset
	ldr	w0, [x20, 1396]
	cbz	w0, .L1720
	add	x20, x20, 2192
	str	w19, [x29, 60]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1722
	mov	w0, 512
	add	x1, x29, 60
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1722
	add	x1, x29, 60
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1722:
	ldr	x1, .LC822
	mov	w0, 32
	bl	dprint_vfmw
.L1720:
	cbnz	w21, .L1738
.L1724:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1713:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1738:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1724
	.p2align 3
.L1718:
	bl	FSP_EmptyInstance
	b	.L1719
	.p2align 3
.L1737:
	str	wzr, [x0, 1536]
	str	wzr, [x1, 1340]
	b	.L1717
	.p2align 3
.L1735:
	add	x1, x0, 507904
	ldr	w2, [x0, 600]
	ldr	w1, [x1, 1400]
	cmp	w1, w2
	bne	.L1714
	str	wzr, [x0, 12]
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	b	.L1714
	.p2align 3
.L1736:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1716
.L1734:
	ldr	x3, .LC818
	mov	w2, 3758
	ldr	x1, .LC819
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1713
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	3
.LC817:
	.xword	.LANCHOR0
	.align	3
.LC818:
	.xword	.LC8
	.align	3
.LC819:
	.xword	.LC5
	.align	3
.LC820:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC821:
	.xword	.LANCHOR5
	.align	3
.LC822:
	.xword	.LC813
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	x28, x1
	mov	w20, w2
	bl	_mcount
	ldr	x22, .LC825
	mov	x2, 56
	mov	w1, 0
	add	x0, x29, 168
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x4, [x22, 96]
	mov	x2, 96
	mov	w1, 0
	add	x0, x29, 224
	blr	x4
	ldr	x4, [x22, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 120
	blr	x4
	ldr	x4, [x22, 96]
	mov	x2, 12
	mov	w1, 0
	add	x0, x29, 104
	blr	x4
	ldr	x24, .LC826
	str	x28, [x24, 1800]
	cbz	x28, .L1810
	ldr	w0, [x28, 36]
	tbnz	w0, #31, .L1742
	ldr	w0, [x28, 12]
	cmp	w0, 31
	ble	.L1742
	ldr	w0, [x28, 16]
	cmp	w0, 31
	ble	.L1742
	ldr	w1, [x28, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L1742
	ldr	w0, [x28, 44]
	cmp	w0, 1
	beq	.L1811
	cmp	w0, 2
	bne	.L1744
	ldr	w0, [x28, 20]
	cmp	w0, wzr
	ble	.L1742
	ldr	w0, [x28, 24]
	cmp	w0, wzr
	ble	.L1742
.L1808:
	ldr	w0, [x28, 28]
	cmp	w0, wzr
	ble	.L1742
	ldr	w0, [x28, 32]
	cmp	w0, wzr
	bgt	.L1744
.L1742:
	ldr	x1, .LC829
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1823:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L1744:
	ldr	w0, [x28, 168]
	cmp	w0, 1
	bls	.L1746
	str	wzr, [x28, 168]
.L1746:
	mov	w4, 17280
	mov	w23, 1
	cmp	w19, 26
	mov	w3, w20
	movk	w4, 0xb5, lsl 16
	mov	w20, 47200
	add	x2, x29, 104
	mov	x1, x28
	mov	w0, w19
	movk	w20, 0xf, lsl 16
	stp	w23, w23, [x28, 192]
	csel	w20, w20, w4, ne
	bl	VCTRL_GetChanMemSize
	cbnz	w0, .L1812
	ldr	x3, [x22, 96]
	add	x21, x28, 72
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 56]
	cbz	x0, .L1750
	ldr	w0, [x21, 64]
	cbnz	w0, .L1751
.L1750:
	mov	w0, 3
	str	w0, [x29, 164]
	mov	w0, 7
	bl	VFMW_GetString
	ldr	w2, [x29, 112]
	mov	w4, 1
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1813
	ldr	w0, [x29, 152]
	ldr	w2, [x29, 160]
	ldr	x1, [x29, 144]
	bl	MEM_AddMemRecord
	ldr	w0, [x29, 152]
	str	w0, [x29, 272]
	ldr	x0, [x29, 144]
	str	x0, [x29, 280]
	ldr	w0, [x29, 160]
	str	w0, [x29, 288]
	mov	w0, 1
	str	w0, [x29, 128]
.L1754:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 8]
	cbnz	x0, .L1814
.L1783:
	ldr	w0, [x28, 168]
	cmp	w0, 1
	beq	.L1757
	mov	w0, 3
	str	w0, [x29, 164]
	mov	w0, 8
	bl	VFMW_GetString
	ldr	w2, [x29, 104]
	mov	w4, 0
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1815
	ldr	w0, [x29, 152]
	ldr	w2, [x29, 160]
	ldr	x1, [x29, 144]
	bl	MEM_AddMemRecord
	ldr	w0, [x29, 152]
	str	w0, [x29, 224]
	ldr	x0, [x29, 144]
	str	x0, [x29, 232]
	ldr	w0, [x29, 160]
	str	w0, [x29, 240]
	mov	w0, 1
	str	w0, [x29, 120]
.L1761:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 32]
	cbz	x0, .L1785
	ldr	w0, [x21, 40]
	cbnz	w0, .L1765
.L1785:
	mov	w1, 3
	mov	w0, 9
	str	w1, [x29, 164]
	bl	VFMW_GetString
	ldr	w2, [x29, 108]
	mov	w4, 0
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1816
	ldr	w2, [x29, 160]
	ldr	x1, [x29, 144]
	ldr	w0, [x29, 152]
	bl	MEM_AddMemRecord
	ldr	w3, [x29, 152]
	mov	w0, 1
	ldr	w1, [x29, 160]
	ldr	x2, [x29, 144]
	str	w0, [x29, 124]
	str	w3, [x29, 248]
	str	x2, [x29, 256]
	str	w1, [x29, 264]
.L1805:
	ldr	x1, [x22, 24]
	mov	w0, 0
	blr	x1
	ldr	x26, .LC844
	ldr	x0, [x26]
	cbz	x0, .L1788
	add	x0, x26, 8
	mov	w21, 1
	b	.L1776
	.p2align 3
.L1817:
	add	w21, w21, 1
	cmp	w21, 32
	beq	.L1777
.L1776:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbnz	x1, .L1817
	cmp	w21, 31
	bhi	.L1777
.L1774:
	sxtw	x23, w20
	ldr	x3, [x22, 96]
	ldr	x0, [x29, 280]
	sub	x2, x23, #204800
	sub	x2, x2, #1544
	mov	w1, 0
	str	x0, [x26, w21, sxtw 3]
	sxtw	x27, w21
	blr	x3
	ldr	x0, [x26, w21, sxtw 3]
	mov	x1, x28
	ldr	x3, [x22, 104]
	mov	x2, 208
	add	x0, x0, 1320
	blr	x3
	ldr	x0, [x26, w21, sxtw 3]
	ldr	x3, .LC847
	str	w19, [x0, 36]
	str	w20, [x0, 1228]
	ldr	x0, [x26, w21, sxtw 3]
	str	w21, [x0]
	str	w19, [x0, 636]
	str	wzr, [x0, 1256]
	ldr	x0, [x26, w21, sxtw 3]
	ldr	w1, [x28]
	str	w1, [x0, 32]
	mov	w1, 21
	ldr	x0, [x26, w21, sxtw 3]
	add	x2, x0, 507904
	str	w1, [x0, 600]
	str	w1, [x2, 1400]
	lsl	x1, x27, 4
	str	wzr, [x0, 28]
	ldr	x0, [x26, w21, sxtw 3]
	ldr	w4, [x28, 200]
	add	x2, x0, 507904
	str	w4, [x2, 1384]
	add	x2, x0, 1576
	str	x2, [x3, x1]
	mov	w1, 30
	str	w1, [x0, 1568]
	add	x1, x0, 475136
	add	x1, x1, 2168
	mov	w0, w21
	ldr	w3, [x28, 192]
	str	w3, [x2, 72]
	ldr	w3, [x28, 196]
	str	w3, [x2, 76]
	bl	FSP_EnableInstance
	cbnz	w0, .L1818
	mov	w0, w21
	mov	w20, 0
	mov	w25, 255
	bl	VCTRL_ResetChan
	ldr	x0, [x26, w21, sxtw 3]
	ldp	w2, w1, [x29, 120]
	str	w2, [x0, 360]
	str	w1, [x0, 364]
	add	x1, x0, 503808
	ldr	w2, [x29, 128]
	str	w2, [x0, 368]
	add	x2, x1, 1280
	add	x0, x0, 507904
	stp	wzr, wzr, [x2, 12]
	stp	wzr, wzr, [x2, 20]
	str	wzr, [x1, 1308]
	str	wzr, [x1, 1312]
	ldr	w1, [x28, 168]
	str	w1, [x0, 1348]
	str	wzr, [x0, 1340]
	.p2align 2
.L1779:
	uxtw	x1, w20
	ldr	x4, [x26, x27, lsl 3]
	lsl	x19, x1, 6
	ldr	x3, [x22, 96]
	add	x19, x19, x1, lsl 3
	mov	x2, 72
	add	x0, x19, 503808
	mov	w1, 0
	add	x0, x4, x0
	add	w20, w20, 1
	add	x0, x0, 1320
	blr	x3
	ldr	x0, [x26, x27, lsl 3]
	cmp	w20, 32
	add	x1, x0, x19
	add	x1, x1, 503808
	str	w25, [x1, 1320]
	str	w25, [x1, 1324]
	str	w25, [x1, 1328]
	bne	.L1779
	ldr	x3, [x22, 96]
	add	x0, x0, 503808
	mov	x2, 1248
	mov	w1, 0
	add	x0, x0, 3624
	add	x24, x24, 1808
	blr	x3
	ldr	x0, [x26, x27, lsl 3]
	mov	x2, 24
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 507904
	add	x0, x0, 776
	blr	x3
	str	wzr, [x24, x27, lsl 2]
	ldr	x0, [x26, x27, lsl 3]
	ldr	w6, [x29, 272]
	ldr	x3, [x29, 232]
	add	x5, x0, 475136
	str	x3, [x0, 272]
	str	w6, [x0, 344]
	ldr	x3, [x29, 256]
	ldr	x6, [x29, 280]
	ldr	w1, [x29, 224]
	ldr	w2, [x29, 240]
	str	x3, [x0, 304]
	str	x6, [x0, 336]
	ldr	w4, [x29, 248]
	ldr	w3, [x29, 264]
	ldr	w6, [x29, 288]
	str	w1, [x0, 280]
	str	w2, [x0, 288]
	str	w4, [x0, 312]
	str	w1, [x0, 388]
	str	w2, [x0, 392]
	str	w3, [x0, 320]
	str	w6, [x0, 352]
	str	wzr, [x5, 2200]
	ldr	w5, [x0, 1488]
	cmp	w5, 1
	beq	.L1780
	sub	w2, w2, #307200
	str	w1, [x0, 376]
	sub	w2, w2, #2576
	str	w4, [x0, 384]
	add	w1, w2, w1
	str	w2, [x0, 380]
	add	w4, w1, 12288
	add	w2, w1, 45056
	add	w1, w1, 15
	add	w4, w4, 2575
	and	w1, w1, -16
	add	w2, w2, 2575
	mov	w6, 14848
	mov	w5, 32768
	and	w4, w4, -16
	and	w2, w2, -16
	str	w1, [x0, 400]
	mov	w1, 262144
	str	w3, [x0, 396]
	str	w6, [x0, 404]
	str	w5, [x0, 412]
	str	w4, [x0, 408]
	str	w2, [x0, 416]
	str	w1, [x0, 420]
.L1781:
	ldr	x1, [x26, w21, sxtw 3]
	mov	w0, w21
	str	w21, [x1]
	ldr	x1, [x26, w21, sxtw 3]
	add	x2, x1, 458752
	str	w21, [x1, 256]
	str	w21, [x1, 260]
	str	w21, [x2, 1808]
	bl	SM_ClearInst
	ldr	x2, [x26, w21, sxtw 3]
	sub	x1, x23, #200704
	sub	x1, x1, #3592
	mov	w0, w21
	ldr	x2, [x2, 336]
	add	x1, x2, x1
	bl	OpenUsdPool_WithMem
	ldr	x1, [x26, w21, sxtw 3]
	mov	w2, 1
	mov	w0, w21
	str	w2, [x1, 4]
	bl	VDMDRV_ClearChanIsDec
	bl	VDMDRV_ParamInit
	ldr	x19, [x26, w21, sxtw 3]
	ldr	x0, [x22]
	add	x19, x19, 507904
	blr	x0
	ldr	x1, [x22, 32]
	str	w0, [x19, 1356]
	mov	w0, 0
	blr	x1
	mov	w0, w21
.L1804:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L1814:
	ldr	w0, [x21, 16]
	cbz	w0, .L1783
	ldr	x3, [x22, 104]
	mov	x2, 24
	mov	x1, x21
	add	x0, x29, 224
	blr	x3
	ldr	w0, [x28, 168]
	ldr	w2, [x29, 240]
	cmp	w0, 1
	beq	.L1763
	ldr	w4, [x29, 104]
	cmp	w2, w4
	blt	.L1819
.L1763:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_AddMemRecord
	b	.L1761
	.p2align 3
.L1757:
	str	wzr, [x29, 120]
	str	wzr, [x29, 224]
	str	xzr, [x29, 232]
	str	wzr, [x29, 240]
	b	.L1761
.L1811:
	ldr	w0, [x28, 20]
	cmp	w0, wzr
	bgt	.L1808
	b	.L1742
	.p2align 3
.L1780:
	sub	w1, w3, #307200
	mov	w3, 14848
	sub	w1, w1, #2576
	str	w4, [x0, 384]
	add	w2, w1, w4
	str	w1, [x0, 396]
	str	w3, [x0, 404]
	add	w1, w2, 45056
	add	w3, w2, 12288
	add	w4, w2, 15
	and	w2, w4, -16
	add	w3, w3, 2575
	add	w1, w1, 2575
	mov	w5, 32768
	and	w3, w3, -16
	and	w1, w1, -16
	str	w2, [x0, 400]
	mov	w2, 262144
	str	wzr, [x0, 376]
	str	wzr, [x0, 380]
	str	w5, [x0, 412]
	str	w3, [x0, 408]
	str	w1, [x0, 416]
	str	w2, [x0, 420]
	b	.L1781
.L1751:
	ldr	x3, [x22, 104]
	mov	x2, 24
	add	x1, x28, 120
	add	x0, x29, 272
	blr	x3
	ldr	w0, [x29, 112]
	ldr	w2, [x29, 288]
	cmp	w2, w0
	blt	.L1820
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_AddMemRecord
	b	.L1754
.L1765:
	mov	x2, 24
	add	x0, x29, 224
	ldr	x3, [x22, 104]
	add	x1, x28, 96
	add	x0, x0, x2
	blr	x3
	ldr	x1, [x29, 256]
	cbz	x1, .L1770
	ldr	w0, [x29, 108]
	ldr	w2, [x29, 264]
	cmp	w2, w0
	blt	.L1770
	ldr	w0, [x29, 248]
	bl	MEM_AddMemRecord
	b	.L1805
.L1816:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1821
.L1767:
	ldr	w0, [x29, 120]
	cmp	w0, 1
	beq	.L1822
.L1768:
	ldr	x1, .LC841
	mov	w2, 1909
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1815:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1824
.L1759:
	ldr	x1, .LC837
	mov	w2, 1975
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1788:
	mov	w21, 0
	b	.L1774
.L1812:
	ldr	x1, .LC831
	mov	w2, 2132
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1804
.L1818:
	ldr	x1, .LC849
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	bl	FSP_DisableInstance
	mov	w0, w21
	bl	CloseUsdPool_WithMem
	ldr	x1, [x26, w21, sxtw 3]
	mov	w0, w21
	str	xzr, [x26, w21, sxtw 3]
	add	x5, x1, 507904
	add	x2, x1, 503808
	ldr	w6, [x1, 364]
	add	x2, x2, 1320
	ldr	w3, [x1, 360]
	ldr	w4, [x1, 368]
	ldr	w5, [x5, 1348]
	stp	w5, w3, [x29, 200]
	stp	w6, w4, [x29, 208]
	add	x3, x1, 296
	add	x4, x1, 264
	add	x1, x1, 328
	str	x2, [x29, 192]
	stp	x4, x3, [x29, 168]
	str	x1, [x29, 184]
	bl	VDMDRV_ClearChanIsDec
	ldr	x1, [x22, 32]
	mov	w0, 0
	blr	x1
	add	x1, x29, 168
	mov	w0, w21
	bl	VCTRL_FreeChanResource
	mov	w0, -1
	b	.L1804
	.p2align 3
.L1777:
	ldr	x1, .LC846
	mov	w2, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1804
.L1813:
	ldr	x1, .LC833
	mov	w2, 2033
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1770:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1825
.L1772:
	ldr	w0, [x29, 120]
	cmp	w0, 1
	beq	.L1826
.L1773:
	ldr	x1, .LC843
	mov	w2, 1938
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1822:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 224]
	ldr	w2, [x29, 240]
	ldr	x1, [x29, 232]
	bl	MEM_DelMemRecord
	b	.L1768
.L1824:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1759
.L1820:
	ldr	x1, .LC835
	mov	w2, 2049
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1821:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1767
.L1819:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1827
.L1764:
	ldr	x1, .LC839
	mov	w3, w2
	mov	w0, 1
	mov	w2, 2007
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1826:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 224]
	ldr	w2, [x29, 240]
	ldr	x1, [x29, 232]
	bl	MEM_DelMemRecord
	b	.L1773
.L1810:
	ldr	x1, .LC828
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1823
.L1825:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1772
.L1827:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x29, 288]
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	ldr	w4, [x29, 104]
	ldr	w2, [x29, 240]
	b	.L1764
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	3
.LC825:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC826:
	.xword	.LANCHOR6
	.align	3
.LC828:
	.xword	.LC827
	.align	3
.LC829:
	.xword	.LC513
	.align	3
.LC831:
	.xword	.LC830
	.align	3
.LC833:
	.xword	.LC832
	.align	3
.LC835:
	.xword	.LC834
	.align	3
.LC837:
	.xword	.LC836
	.align	3
.LC839:
	.xword	.LC838
	.align	3
.LC841:
	.xword	.LC840
	.align	3
.LC843:
	.xword	.LC842
	.align	3
.LC844:
	.xword	.LANCHOR0
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC847:
	.xword	s_SmIIS
	.align	3
.LC849:
	.xword	.LC848
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w19, w0
	mov	x0, x30
	mov	x24, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1872
	ldr	x21, .LC853
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1873
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L1874
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_CheckChanWH
	mov	w20, w0
	cbnz	w0, .L1875
	ldr	x22, .LC858
	add	x23, x22, 1936
	mov	x1, x23
	bl	PDT_GetAttribute
	ldr	w0, [x22, 1956]
	ldr	w2, [x24, 8]
	cmp	w0, 20
	bhi	.L1835
	cmp	w0, w2
	beq	.L1836
	add	x0, x22, 1960
	add	x3, x22, 2084
	.p2align 2
.L1838:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 20
	bhi	.L1835
	cmp	w1, w2
	beq	.L1836
	cmp	x3, x0
	bne	.L1838
.L1836:
	cmp	w2, 8
	str	wzr, [x29, 88]
	beq	.L1876
.L1839:
	cmp	w2, 9
	beq	.L1877
.L1860:
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_CmpConfigParameter
	cbz	w0, .L1878
	ldr	x23, .LC863
	mov	x2, 140
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x24
	ldr	x3, [x23, 104]
	add	x0, x0, 44
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	mov	x2, 72
	ldr	w1, [x24, 24]
	str	w1, [x0, 20]
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x24, 8]
	ldr	x3, [x23, 96]
	str	w1, [x0, 600]
	ldr	w1, [x24, 96]
	str	w1, [x0, 1496]
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w0, [x0, 384]
	str	w0, [x29, 104]
	bl	MEM_Phy2Vir
	str	x0, [x29, 88]
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w0, [x24, 84]
	ldr	w3, [x24, 24]
	ldr	w2, [x1, 396]
	cmp	w0, 1
	str	w2, [x29, 108]
	add	x1, x1, 507904
	ldr	w2, [x24, 8]
	str	w2, [x29, 100]
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	strb	w3, [x29, 96]
	str	w2, [x29, 112]
	beq	.L1879
	str	wzr, [x1, 1396]
.L1844:
	ldr	w1, [x24, 80]
	ldr	w0, [x24, 8]
	str	wzr, [x29, 128]
	str	w1, [x29, 136]
	cbnz	w0, .L1880
.L1871:
	ldr	w0, [x24, 52]
.L1846:
	str	w0, [x29, 132]
	add	x3, x21, 256
	mov	w1, 0
	mov	x0, x21
	.p2align 2
.L1848:
	ldr	x2, [x0], 8
	cmp	x2, xzr
	csinc	w1, w1, w1, eq
	cmp	x3, x0
	bne	.L1848
	cmp	w1, 1
	ldr	x25, .LC864
	ble	.L1881
.L1849:
	str	wzr, [x29, 132]
.L1850:
	ldr	x0, [x21, w19, sxtw 3]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	beq	.L1882
.L1851:
	ldr	x3, [x23, 104]
	add	x26, x24, 12
	mov	x2, 12
	mov	x1, x26
	add	x0, x29, 116
	blr	x3
	add	x1, x29, 88
	mov	w0, w19
	bl	SM_Config
	ldr	x3, [x23, 96]
	mov	x2, 1
	mov	w1, 0
	add	x0, x29, 80
	blr	x3
	ldr	w0, [x24, 84]
	cmp	w0, 1
	beq	.L1883
.L1852:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x25, 72]
	ldr	w2, [x0, 344]
	cmp	w1, 7
	str	w2, [x0, 1232]
	ldr	w2, [x0, 352]
	str	w2, [x0, 1236]
	ldr	w2, [x0, 376]
	str	w2, [x0, 624]
	ldr	w2, [x0, 380]
	str	w2, [x0, 628]
	ldr	w2, [x0, 400]
	str	w2, [x0, 640]
	ldr	w2, [x0, 404]
	str	w2, [x0, 644]
	ldr	w2, [x0, 408]
	str	w2, [x0, 648]
	ldr	w2, [x0, 412]
	str	w2, [x0, 652]
	ldr	w2, [x0, 416]
	str	w2, [x0, 656]
	ldr	w2, [x0, 420]
	str	w2, [x0, 660]
	ldr	w2, [x24, 28]
	str	w2, [x0, 612]
	ldr	w2, [x24, 28]
	str	w2, [x0, 608]
	ldr	w2, [x24, 36]
	str	w2, [x0, 616]
	beq	.L1884
.L1853:
	str	w1, [x0, 632]
	mov	w25, 1
	ldr	w1, [x24, 44]
	str	w1, [x0, 620]
	ldr	w1, [x24, 128]
	str	w1, [x0, 1284]
	ldr	w1, [x24, 136]
	str	w1, [x0, 1564]
	str	w25, [x0, 1288]
	str	w25, [x0, 1292]
	ldr	w1, [x24, 72]
	cmp	w1, w25
	cset	w1, eq
	str	w1, [x0, 1268]
	ldr	w1, [x24, 76]
	str	w1, [x0, 1272]
	ldr	w1, [x24, 48]
	str	w1, [x0, 1276]
	ldr	w1, [x29, 132]
	str	w1, [x0, 1280]
	str	wzr, [x0, 1536]
	str	wzr, [x0, 1556]
	add	x0, x0, 507904
	ldrsb	w1, [x24, 1]
	strb	w1, [x0, 1344]
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_ConfigChanCompress
	ldr	x0, [x21, w19, sxtw 3]
	mov	x2, 12
	ldr	x3, [x23, 104]
	mov	x1, x26
	add	x0, x0, 1204
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w2, [x0, 600]
	ldr	w0, [x1, 1400]
	cmp	w0, w2
	beq	.L1854
	mov	w0, w19
	bl	VCTRL_ResetChan
	ldr	w1, [x24, 8]
	ldr	x0, [x21, w19, sxtw 3]
	cmp	w1, 20
	beq	.L1855
	ldr	w2, [x0, 600]
	add	x1, x0, 507904
.L1854:
	ldr	x4, .LC867
	mov	x0, 0
	str	w2, [x1, 1400]
	b	.L1859
	.p2align 3
.L1886:
	ldr	w3, [x1, 20]
	str	w3, [x2, x0, lsl 2]
	ldr	w1, [x1, 20]
	str	w1, [x4, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1885
.L1859:
	ldr	x1, [x21, x0, lsl 3]
	add	x2, x22, 2088
	cbnz	x1, .L1886
	add	x1, x22, 2088
	str	wzr, [x4, x0, lsl 2]
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1859
.L1885:
	add	x0, x22, 2088
	bl	VDMDRV_SetPriority
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1878:
	ldr	x1, .LC862
	mov	w20, 0
	bl	dprint_vfmw
.L1869:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1835:
	ldr	x1, .LC860
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1880:
	cmp	w0, 16
	mov	w0, 0
	beq	.L1871
	b	.L1846
	.p2align 3
.L1877:
	add	x0, x29, 88
	bl	REAL9DEC_Support
	ldr	w0, [x29, 88]
	cbnz	w0, .L1860
.L1840:
	mov	w20, -1
	b	.L1869
	.p2align 3
.L1881:
	ldr	w0, [x25, 84]
	cbnz	w0, .L1850
	b	.L1849
.L1876:
	add	x0, x29, 88
	bl	REAL8DEC_Support
	ldr	w0, [x29, 88]
	cbz	w0, .L1840
	ldr	w2, [x24, 8]
	b	.L1839
.L1882:
	str	wzr, [x29, 132]
	b	.L1851
.L1879:
	ldr	w2, [x24, 88]
	stp	w0, w2, [x29, 140]
	ldr	w2, [x24, 92]
	ldr	w0, [x24, 132]
	str	w2, [x29, 148]
	str	w0, [x1, 1396]
	b	.L1844
.L1884:
	ldr	w1, [x24, 40]
	b	.L1853
.L1874:
	ldr	x3, .LC855
	mov	w2, 2969
	ldr	x1, .LC852
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1869
.L1883:
	strb	w0, [x29, 80]
	add	x1, x29, 80
	mov	w0, w19
	bl	FSP_ConfigAttribute
	b	.L1852
.L1875:
	ldr	x1, .LC857
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1869
.L1855:
	ldr	w3, [x0, 388]
	ldr	w4, [x0, 392]
	ldr	w1, [x0, 1332]
	ldr	w2, [x0, 1336]
	mov	w0, w19
	bl	VCTRL_PartitionMemForStdUser
	cbnz	w0, .L1856
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w2, [x0, 600]
	b	.L1854
.L1872:
	ldr	x3, .LC851
	mov	w2, 2967
	ldr	x1, .LC852
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1869
.L1873:
	ldr	x3, .LC854
	mov	w2, 2968
	ldr	x1, .LC852
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1869
.L1856:
	ldr	x1, .LC866
	mov	w0, w25
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1869
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	3
.LC851:
	.xword	.LC237
	.align	3
.LC852:
	.xword	.LC5
	.align	3
.LC853:
	.xword	.LANCHOR0
	.align	3
.LC854:
	.xword	.LC8
	.align	3
.LC855:
	.xword	.LC242
	.align	3
.LC857:
	.xword	.LC856
	.align	3
.LC858:
	.xword	.LANCHOR6
	.align	3
.LC860:
	.xword	.LC859
	.align	3
.LC862:
	.xword	.LC861
	.align	3
.LC863:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC864:
	.xword	.LANCHOR2
	.align	3
.LC866:
	.xword	.LC865
	.align	3
.LC867:
	.xword	g_ChanCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDropStreamThread, %function
VfmwProc_SetDropStreamThread:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC873
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC874
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1887
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 64]
	bl	VCTRL_ConfigChan
.L1887:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	3
.LC873:
	.xword	.LC872
	.align	3
.LC874:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDecMode, %function
VfmwProc_SetDecMode:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC876
	lsr	w20, w3, 24
	and	w19, w3, 7
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC877
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1892
	ldr	x1, .LC879
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1892:
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 68]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	3
.LC876:
	.xword	.LC875
	.align	3
.LC877:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC879:
	.xword	.LC878
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDecOrderOutput, %function
VfmwProc_SetDecOrderOutput:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC881
	lsr	w20, w3, 24
	and	w19, w3, 3
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC882
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1893
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 72]
	bl	VCTRL_ConfigChan
.L1893:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	3
.LC881:
	.xword	.LC880
	.align	3
.LC882:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetErrorThread, %function
VfmwProc_SetErrorThread:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC884
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC885
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1895
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 60]
	bl	VCTRL_ConfigChan
.L1895:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	3
.LC884:
	.xword	.LC883
	.align	3
.LC885:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestResetChan, %function
VfmwProc_TestResetChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC887
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	3
.LC887:
	.xword	.LC886
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC888
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	cmp	w19, 31
	bhi	.L1909
	ldr	x21, .LC893
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1910
	ldr	w22, [x0, 4]
	cmp	w22, 1
	bne	.L1911
	str	wzr, [x0, 8]
	mov	w0, 0
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, w19
	bl	SCDDRV_IsChanDec
	cbnz	w0, .L1912
.L1903:
	ldr	x1, [x20, 24]
	mov	w0, 0
	sxtw	x22, w19
	blr	x1
	ldr	x2, .LC898
	mov	w0, 4
	ldr	x1, [x20, 24]
	str	wzr, [x2, w19, sxtw 2]
	blr	x1
	mov	w0, w19
	bl	VCTRL_StopChan
	ldr	x1, [x20, 32]
	cbnz	w0, .L1913
	mov	w0, 4
	lsl	x22, x22, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	x1, .LC899
	mov	w0, 4
	ldr	x2, [x20, 24]
	add	x1, x1, 264
	str	wzr, [x1, w19, sxtw 2]
	blr	x2
	mov	w0, w19
	bl	FSP_DisableInstance
	mov	w0, w19
	bl	CloseUsdPool_WithMem
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	ldr	x3, .LC900
	add	x4, x1, 507904
	add	x2, x1, 503808
	ldr	w5, [x1, 368]
	add	x2, x2, 1320
	str	w5, [x29, 116]
	ldr	w4, [x4, 1348]
	ldr	w5, [x1, 360]
	str	w4, [x29, 104]
	add	x4, x1, 264
	str	w5, [x29, 108]
	ldr	w5, [x1, 364]
	str	x4, [x29, 72]
	add	x4, x1, 296
	str	xzr, [x3, x22]
	add	x1, x1, 328
	str	w5, [x29, 112]
	stp	x4, x1, [x29, 80]
	str	x2, [x29, 96]
	str	xzr, [x21, w19, sxtw 3]
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w19
	add	x21, x21, 608
	bl	SCDDRV_ResetSCD
	mov	w0, w19
	bl	VDMDRV_ResetVDH
	str	wzr, [x21, x22]
	add	x1, x21, x22
	ldr	x3, [x20, 32]
	mov	w2, -1
	mov	w0, 4
	stp	wzr, w2, [x1, 4]
	str	w2, [x1, 12]
	blr	x3
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x20, 48]
	mov	w1, w19
	mov	w0, 1
	blr	x2
	add	x1, x29, 72
	mov	w0, w19
	bl	VCTRL_FreeChanResource
	ldr	x2, [x20, 56]
	mov	w0, 1
	mov	w1, w19
	blr	x2
	mov	w0, 0
.L1900:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1912:
	mov	w0, w19
	ldr	x23, [x20, 264]
	bl	SCDDRV_IsChanDec
	cmp	w0, wzr
	mov	w2, 500
	cset	w1, eq
	mov	w0, w22
	blr	x23
	b	.L1903
	.p2align 3
.L1911:
	ldr	x2, .LC890
	mov	w3, 2410
	ldr	x4, .LC897
	mov	w0, 0
	ldr	x1, .LC892
	add	x2, x2, 792
.L1908:
	bl	dprint_vfmw
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1913:
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1900
	.p2align 3
.L1909:
	ldr	x2, .LC890
	mov	w3, 2389
	ldr	x4, .LC889
	mov	w0, 0
	ldr	x1, .LC892
	add	x2, x2, 792
	b	.L1908
.L1910:
	ldr	x2, .LC890
	mov	w3, 2398
	ldr	x4, .LC895
	ldr	x1, .LC892
	add	x2, x2, 792
	b	.L1908
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	3
.LC888:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC889:
	.xword	.LC237
	.align	3
.LC890:
	.xword	.LANCHOR4
	.align	3
.LC892:
	.xword	.LC891
	.align	3
.LC893:
	.xword	.LANCHOR0
	.align	3
.LC895:
	.xword	.LC894
	.align	3
.LC897:
	.xword	.LC896
	.align	3
.LC898:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC899:
	.xword	.LANCHOR5
	.align	3
.LC900:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CloseVfmw
	.type	VCTRL_CloseVfmw, %function
VCTRL_CloseVfmw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC903
	ldr	w0, [x20, 256]
	cmp	w0, 1
	bne	.L1921
	mov	x19, 0
	.p2align 2
.L1917:
	ldr	x1, [x20, x19, lsl 3]
	mov	w0, w19
	add	x19, x19, 1
	cbz	x1, .L1916
	bl	VCTRL_DestroyChan
.L1916:
	cmp	x19, 32
	bne	.L1917
	bl	FSP_Exit
	ldr	x21, .LC904
	ldr	w1, [x20, 260]
	mov	w2, 3
	str	w2, [x20, 264]
	cbz	w1, .L1919
	ldr	x1, [x21, 240]
	mov	w0, 10
	mov	w19, 49
	blr	x1
	b	.L1920
	.p2align 3
.L1931:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L1919
.L1920:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cbnz	w1, .L1931
.L1919:
	ldr	x0, .LC905
	mov	x2, 128
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 264
	blr	x3
	add	x0, x20, 288
	bl	CloseDrivers
	str	wzr, [x20, 256]
	mov	w0, 0
.L1930:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1921:
	mov	w0, -1
	b	.L1930
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	3
.LC903:
	.xword	.LANCHOR0
	.align	3
.LC904:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC905:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestRestartChan, %function
VfmwProc_TestRestartChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StopChan
	mov	w3, w0
	ldr	x1, .LC908
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC909
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC910
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	3
.LC908:
	.xword	.LC907
	.align	3
.LC909:
	.xword	.LC886
	.align	3
.LC910:
	.xword	.LC791
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStopChan, %function
VfmwProc_TestStopChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StopChan
	mov	w3, w0
	ldr	x1, .LC911
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	3
.LC911:
	.xword	.LC907
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_InitDspCode
	.type	VCTRL_InitDspCode, %function
VCTRL_InitDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 6
	beq	.L1944
	mov	w19, 2
	cmp	w20, wzr
	csel	w19, w19, wzr, eq
.L1935:
	ldr	x0, .LC912
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1946
	mov	w1, w19
	mov	w0, 0
	bl	VDH_Require_DspCode
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1946:
	ldr	x20, .LC913
	ldr	x1, [x20, 8]
	cbz	x1, .L1947
	mov	w0, 0
	blr	x1
.L1938:
	ldr	x1, [x20, 40]
	cbz	x1, .L1948
	mov	w0, 0
	blr	x1
.L1940:
	ldr	x1, [x20, 24]
	cbz	x1, .L1949
	mov	w0, 0
	blr	x1
.L1942:
	mov	w1, w19
	mov	w0, 0
	bl	SCDDRV_LoadDspCode
	mov	w0, w21
	bl	VCTRL_CloseHardware
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1944:
	mov	w19, 1
	b	.L1935
	.p2align 3
.L1947:
	ldr	x1, .LC914
	mov	w2, 3264
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1938
	.p2align 3
.L1948:
	ldr	x1, .LC914
	mov	w2, 3265
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1940
	.p2align 3
.L1949:
	ldr	x1, .LC914
	mov	w2, 3266
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1942
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	3
.LC912:
	.xword	g_HalDisable
	.align	3
.LC913:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC914:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC915
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 600]
	cbnz	w1, .L1962
	ldr	w21, [x0, 1276]
	mov	w0, 0
	cmp	w21, wzr
	cset	w3, eq
	cmp	w1, 6
	cset	w2, ne
	tst	w3, w2
	beq	.L1981
.L1968:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1962:
	cmp	w1, 6
	mov	w3, 1
	cset	w2, ne
	mov	w21, 0
	tst	w3, w2
	mov	w0, 0
	bne	.L1968
.L1981:
	ldr	x20, .LC916
	add	x0, x20, 268
	add	x3, x20, 392
	ldr	w2, [x20, 264]
	cbz	w2, .L1953
	b	.L1952
	.p2align 3
.L1983:
	beq	.L1982
.L1953:
	ldr	w2, [x0]
	add	x0, x0, 4
	cmp	x3, x0
	cbz	w2, .L1983
.L1952:
	cmp	w2, 1
	beq	.L1984
	cmp	w1, 6
	mov	w0, 0
	beq	.L1968
	ldr	x1, .LC920
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1968
	.p2align 3
.L1982:
	mov	w0, w19
	bl	VCTRL_InitDspCode
	cmp	w21, 1
	beq	.L1985
	add	x20, x20, 264
	mov	w1, 2
	mov	w0, 0
	str	w1, [x20, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1985:
	add	x20, x20, 264
	mov	w0, 0
	str	w21, [x20, w19, sxtw 2]
	b	.L1968
	.p2align 3
.L1984:
	cmp	w21, 1
	mov	w0, 0
	beq	.L1968
	ldr	x1, .LC918
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1968
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	3
.LC915:
	.xword	.LANCHOR0
	.align	3
.LC916:
	.xword	.LANCHOR5
	.align	3
.LC918:
	.xword	.LC917
	.align	3
.LC920:
	.xword	.LC919
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetChanFsPartitionState
	.type	VCTRL_SetChanFsPartitionState, %function
VCTRL_SetChanFsPartitionState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, .LC923
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 475136
	str	w19, [x0, 2200]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	3
.LC923:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetCurChanFsSize
	.type	VCTRL_GetCurChanFsSize, %function
VCTRL_GetCurChanFsSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC924
	ldr	x0, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x0, 503808
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 1292]
	ret
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	3
.LC924:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRT_SetChanCtrlState
	.type	VCTRT_SetChanCtrlState, %function
VCTRT_SetChanCtrlState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 1
	beq	.L1990
	cbz	w19, .L1991
	cmp	w19, 2
	bne	.L1999
	ldr	x0, .LC925
	add	x0, x0, 1808
	ldr	w1, [x0, w20, sxtw 2]
	cmp	w1, 1
	beq	.L1995
.L1997:
	str	w19, [x0, w20, sxtw 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1999:
	mov	w0, 0
.L1989:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1991:
	ldr	x1, .LC925
	mov	w0, 0
	add	x1, x1, 1808
	str	wzr, [x1, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1990:
	ldr	x0, .LC925
	add	x0, x0, 1808
	ldr	w1, [x0, w20, sxtw 2]
	cbz	w1, .L1997
.L1995:
	mov	w0, -1
	b	.L1989
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	3
.LC925:
	.xword	.LANCHOR6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_AddFrameBufMemoryRecord
	.type	VCTRL_AddFrameBufMemoryRecord, %function
VCTRL_AddFrameBufMemoryRecord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 255
	beq	.L2001
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_AddMemRecord
.L2001:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L2002
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_AddMemRecord
.L2002:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L2000
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_AddMemRecord
.L2000:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_AddFrameBufMemoryRecord, .-VCTRL_AddFrameBufMemoryRecord
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetSingleFrameBufToChan
	.type	VCTRL_SetSingleFrameBufToChan, %function
VCTRL_SetSingleFrameBufToChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC927
	ldr	w4, [x20, 12]
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	add	x0, x0, 503808
	ldr	w5, [x1, 768]
	cmp	w5, w4
	beq	.L2014
	ldr	w2, [x0, 1288]
	cbz	w2, .L2043
.L2014:
	ldr	w0, [x0, 3680]
	cbz	w0, .L2016
	ldr	w0, [x1, 800]
	cbz	w0, .L2044
.L2016:
	ldr	x22, .LC933
	mov	w0, 8
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x4, [x21, w19, sxtw 3]
	add	x2, x4, 503808
	ldr	w0, [x2, 1320]
	cmp	w0, 255
	beq	.L2024
	add	x2, x2, 1392
	mov	x1, 1
	b	.L2018
	.p2align 3
.L2046:
	add	w1, w1, 1
	cmp	w1, 32
	beq	.L2045
.L2018:
	ldr	w3, [x2]
	add	x2, x2, 72
	cmp	w3, 255
	bne	.L2046
.L2017:
	lsl	x0, x1, 6
	ldr	x3, [x22, 104]
	add	x0, x0, x1, lsl 3
	mov	x2, 72
	add	x0, x0, 503808
	mov	x1, x20
	add	x0, x4, x0
	add	x0, x0, 1320
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x20
	add	x1, x1, 507904
	ldr	w2, [x1, 800]
	add	w2, w2, 1
	str	w2, [x1, 800]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 804]
	cbnz	w0, .L2047
.L2022:
	mov	w19, 0
.L2021:
	ldr	x1, [x22, 32]
	mov	w0, 8
	blr	x1
	mov	w0, w19
.L2037:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2044:
	ldr	w5, [x20, 8]
	cmp	w5, 255
	bne	.L2016
	ldr	x2, .LC928
	mov	w4, 0
	ldr	x1, .LC932
	mov	w3, 9091
	add	x2, x2, 816
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2037
	.p2align 3
.L2045:
	ldr	x2, .LC928
	ldr	x1, .LC937
.L2040:
	mov	w3, w19
	add	x2, x2, 816
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2021
	.p2align 3
.L2047:
	mov	x1, x20
	mov	w0, w19
	bl	FSP_SetSingleFrameBuf
	cbz	w0, .L2022
	ldr	x2, .LC928
	ldr	x1, .LC935
	b	.L2040
.L2024:
	mov	x1, 0
	b	.L2017
.L2043:
	ldr	x2, .LC928
	mov	w3, 9081
	ldr	x1, .LC930
	mov	w0, 1
	add	x2, x2, 816
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2037
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	3
.LC927:
	.xword	.LANCHOR0
	.align	3
.LC928:
	.xword	.LANCHOR4
	.align	3
.LC930:
	.xword	.LC929
	.align	3
.LC932:
	.xword	.LC931
	.align	3
.LC933:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC935:
	.xword	.LC934
	.align	3
.LC937:
	.xword	.LC936
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_AllocMemToDecoder
	.type	VCTRL_AllocMemToDecoder, %function
VCTRL_AllocMemToDecoder:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC938
	add	x3, x21, 1808
	ldr	w0, [x3, w19, sxtw 2]
	cbz	w0, .L2057
	ldr	x2, .LC945
	mov	w3, w19
	ldr	x1, .LC947
	mov	w0, 0
	add	x2, x2, 848
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2057:
	ldr	x4, .LC939
	mov	x1, x20
	mov	w5, 1
	mov	x2, 72
	add	x0, x29, 56
	str	w5, [x3, w19, sxtw 2]
	ldr	x4, [x4, 104]
	blr	x4
	add	x1, x29, 56
	mov	w0, w19
	bl	VCTRL_SetSingleFrameBufToChan
	mov	w20, w0
	cbnz	w0, .L2050
	ldr	x0, .LC940
	ldr	x0, [x0, w19, sxtw 3]
	add	x2, x0, 475136
.L2051:
	ldr	x1, .LC944
	add	x21, x21, 1808
	mov	w3, 2
	mov	w0, 31
	str	w3, [x2, 2200]
	bl	dprint_vfmw
	str	wzr, [x21, w19, sxtw 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2050:
	ldr	x22, .LC940
	ldr	x0, [x22, w19, sxtw 3]
	add	x1, x0, 503808
	add	x2, x0, 475136
	ldr	w0, [x1, 1292]
	cbz	w0, .L2051
	ldr	x1, .LC942
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	mov	w1, 3
	add	x2, x0, 475136
	str	w1, [x2, 2200]
	b	.L2051
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	3
.LC938:
	.xword	.LANCHOR6
	.align	3
.LC939:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC940:
	.xword	.LANCHOR0
	.align	3
.LC942:
	.xword	.LC941
	.align	3
.LC944:
	.xword	.LC943
	.align	3
.LC945:
	.xword	.LANCHOR4
	.align	3
.LC947:
	.xword	.LC946
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetImageWidth
	.type	VCTRL_GetImageWidth, %function
VCTRL_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC949
	ldr	x0, [x0, w19, sxtw 3]
	add	x0, x0, 507904
	ldr	w1, [x0, 1400]
	cmp	w1, 2
	beq	.L2060
	cmp	w1, 16
	beq	.L2061
	cbz	w1, .L2066
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2066:
	add	x0, x0, 1408
	bl	H264DEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2061:
	add	x0, x0, 1408
	bl	HEVCDEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2060:
	add	x0, x0, 1408
	bl	MPEG4DEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetImageWidth, .-VCTRL_GetImageWidth
	.align	3
.LC949:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetImageHeight
	.type	VCTRL_GetImageHeight, %function
VCTRL_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC950
	ldr	x0, [x0, w19, sxtw 3]
	add	x0, x0, 507904
	ldr	w1, [x0, 1400]
	cmp	w1, 2
	beq	.L2069
	cmp	w1, 16
	beq	.L2070
	cbz	w1, .L2075
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2075:
	add	x0, x0, 1408
	bl	H264DEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2070:
	add	x0, x0, 1408
	bl	HEVCDEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2069:
	add	x0, x0, 1408
	bl	MPEG4DEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetImageHeight, .-VCTRL_GetImageHeight
	.align	3
.LC950:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetFsSize
	.type	VCTRL_GetFsSize, %function
VCTRL_GetFsSize:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	bl	_mcount
	ldr	x3, .LC951
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC952
	ldr	x6, [x0, 104]
	cbz	x6, .L2077
	ldr	x4, .LC953
	add	x5, x29, 56
	mov	w3, 0
	mov	w2, w21
	mov	w1, w20
	mov	w0, w19
	ldr	x4, [x4, w19, sxtw 3]
	add	x4, x4, 507904
	ldr	w4, [x4, 1400]
	blr	x6
.L2077:
	ldr	w0, [x29, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	3
.LC951:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC952:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC953:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_EnableEsBuf
	.type	VCTRL_EnableEsBuf, %function
VCTRL_EnableEsBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC954
	mov	w1, 1
	add	x0, x0, 2216
	str	w1, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	3
.LC954:
	.xword	.LANCHOR6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_DisableEsBuf
	.type	VCTRL_DisableEsBuf, %function
VCTRL_DisableEsBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC956
	add	x0, x0, 2216
	str	wzr, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	3
.LC956:
	.xword	.LANCHOR6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IfEsBufEnable
	.type	VCTRL_IfEsBufEnable, %function
VCTRL_IfEsBufEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC958
	add	x0, x0, 2216
	ldr	w0, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
	.align	3
.LC958:
	.xword	.LANCHOR6
	.global	g_EsBufValidFlag
	.global	g_StopDec
	.global	g_SleepTime
	.global	s_VfmwSavePath
	.global	MemRecord_YUV
	.global	pPixelArray
	.global	pVl_2bit
	.global	pUl_2bit
	.global	pY_2bit
	.global	pVl
	.global	pUl
	.global	pY
	.global	pOption
	.global	g_eVdmVersion
	.global	g_VdmCharacter
	.global	g_StandardObedience
	.global	g_CurProcChan
	.global	g_ResetCreateNewSave
	.global	g_SaveYUVBitWidth
	.global	save_yuv_with_crop
	.global	save_el_chan_num
	.global	vfmw_save_el_file
	.global	save_metadata_reorder_chan_num
	.global	vfmw_save_metadata_reorder_file
	.global	save_metadata_chan_num
	.global	vfmw_save_metadata_file
	.global	save_yuv_chan_num
	.global	vfmw_save_yuv_file
	.global	save_seg_chan_num
	.global	vfmw_save_seg_file
	.global	save_str_chan_num
	.global	vfmw_save_str_file
	.global	g_not_allow_H264FullPictureRepair_flag
	.global	g_not_direct_8x8_inference_flag
	.global	g_allow_B_before_P
	.global	extra_cmd
	.global	extra_disp
	.global	extra_ref
	.global	g_VfmwGlobalStat
	.global	g_VfmwChanStat
	.global	s_pstVfmwChan
	.global	AcceleratorCharacter
	.global	g_event_report
	.global	g_IsrFlag
	.global	g_VfmwCompressPara
	.global	g_DSPState
	.global	g_ClkSelect
	.global	mask_mmu_err_int
	.global	g_apple_airplay_mirrorinig_flag
	.global	g_IRQ_FLAG
	.global	g_SedOnlyEnable
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.53306, %object
	.size	__func__.53306, 18
__func__.53306:
	.string	"VCTRL_EventReport"
	.zero	6
	.type	__func__.53242, %object
	.size	__func__.53242, 20
__func__.53242:
	.string	"VCTRL_RecordPosTime"
	.zero	4
	.type	__func__.53247, %object
	.size	__func__.53247, 17
__func__.53247:
	.string	"VCTRL_RecordData"
	.zero	7
	.type	__func__.53318, %object
	.size	__func__.53318, 18
__func__.53318:
	.string	"VCTRL_SetCallBack"
	.zero	6
	.type	__FUNCTION__.53424, %object
	.size	__FUNCTION__.53424, 29
__FUNCTION__.53424:
	.string	"VCTRL_PartitionMemForStdUser"
	.zero	3
	.type	__func__.53448, %object
	.size	__func__.53448, 23
__func__.53448:
	.string	"VCTRL_FreeChanResource"
	.zero	1
	.type	__func__.53702, %object
	.size	__func__.53702, 25
__func__.53702:
	.string	"VCTRL_TryToRelSpecialFrm"
	.zero	7
	.type	__func__.53719, %object
	.size	__func__.53719, 19
__func__.53719:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.53727, %object
	.size	__FUNCTION__.53727, 19
__FUNCTION__.53727:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.53737, %object
	.size	__FUNCTION__.53737, 23
__FUNCTION__.53737:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.53738, %object
	.size	__func__.53738, 23
__func__.53738:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.53772, %object
	.size	__func__.53772, 18
__func__.53772:
	.string	"VCTRL_GetDecParam"
	.align	3
.LANCHOR4 = . + 0
	.type	__FUNCTION__.53909, %object
	.size	__FUNCTION__.53909, 19
__FUNCTION__.53909:
	.string	"VCTRL_FlushDecoder"
	.zero	5
	.type	__FUNCTION__.54202, %object
	.size	__FUNCTION__.54202, 18
__FUNCTION__.54202:
	.string	"GetExtraRefFrmNum"
	.zero	6
	.type	__FUNCTION__.54208, %object
	.size	__FUNCTION__.54208, 19
__FUNCTION__.54208:
	.string	"GetExtraDispFrmNum"
	.zero	5
	.type	__FUNCTION__.54214, %object
	.size	__FUNCTION__.54214, 16
__FUNCTION__.54214:
	.string	"GetExtraCtrlCmd"
	.type	__FUNCTION__.54152, %object
	.size	__FUNCTION__.54152, 14
__FUNCTION__.54152:
	.string	"DecChanSyntax"
	.zero	2
	.type	g_ProcCommandTable, %object
	.size	g_ProcCommandTable, 688
g_ProcCommandTable:
	.word	0
	.zero	4
	.xword	VfmwProc_SetPrintLevel
	.word	2
	.zero	4
	.xword	VfmwProc_SetErrorThread
	.word	3
	.zero	4
	.xword	VfmwProc_SetDefaultOutputOrder
	.word	4
	.zero	4
	.xword	VfmwProc_SetDecOrderOutput
	.word	5
	.zero	4
	.xword	VfmwProc_SetDecMode
	.word	7
	.zero	4
	.xword	VfmwProc_SetDropStreamThread
	.word	8
	.zero	4
	.xword	VfmwProc_SetVp9DecFrameNum
	.word	11
	.zero	4
	.xword	VfmwProc_SetUSE_FF_APT_EN
	.word	12
	.zero	4
	.xword	VfmwProc_SetSaveFileAfterReset
	.word	13
	.zero	4
	.xword	VfmwProc_SetCurProcChan
	.word	256
	.zero	4
	.xword	VfmwProc_PrintTracer
	.word	257
	.zero	4
	.xword	VfmwProc_SetScdPrint
	.word	512
	.zero	4
	.xword	VfmwProc_Savestream
	.word	513
	.zero	4
	.xword	VfmwProc_SaveSeg
	.word	514
	.zero	4
	.xword	VfmwProc_SaveYUV
	.word	516
	.zero	4
	.xword	VfmwProc_Save1DYUV
	.word	528
	.zero	4
	.xword	VfmwProc_SaveMetadata
	.word	544
	.zero	4
	.xword	VfmwProc_SaveReorderMetadata
	.word	560
	.zero	4
	.xword	VfmwProc_SaveEL
	.word	768
	.zero	4
	.xword	VfmwProc_TestSuspend
	.word	769
	.zero	4
	.xword	VfmwProc_TestResume
	.word	896
	.zero	4
	.xword	VfmwProc_TestStopChan
	.word	897
	.zero	4
	.xword	VfmwProc_TestResetChan
	.word	898
	.zero	4
	.xword	VfmwProc_TestStartChan
	.word	899
	.zero	4
	.xword	VfmwProc_TestRestartChan
	.word	1024
	.zero	4
	.xword	VfmwProc_TestTimeSequence
	.word	1026
	.zero	4
	.xword	VfmwProc_TestStopDec
	.word	1280
	.zero	4
	.xword	VfmwProc_SetTraceCtrl
	.word	1281
	.zero	4
	.xword	VfmwProc_SetTraceBSPeriod
	.word	1282
	.zero	4
	.xword	VfmwProc_SetTraceFramePeriod
	.word	1283
	.zero	4
	.xword	VfmwProc_SetTraceImgPeriod
	.word	1285
	.zero	4
	.xword	VfmwProc_SetSaveYuvBitWidth
	.word	1536
	.zero	4
	.xword	VfmwProc_OpenModuleLowly
	.word	1537
	.zero	4
	.xword	VfmwProc_CloseModuleLowly
	.word	1538
	.zero	4
	.xword	VfmwProc_SetTunnelLineNumber
	.word	1539
	.zero	4
	.xword	VfmwProc_OpenScdLowdly
	.word	1540
	.zero	4
	.xword	VfmwProc_CloseScdLowdly
	.word	1541
	.zero	4
	.xword	VfmwProc_SetSedOnlyEnable
	.word	1792
	.zero	4
	.xword	VfmwProc_SetSmmuIrqEnable
	.word	2048
	.zero	4
	.xword	VfmwProc_SetCompressPara
	.word	2304
	.zero	4
	.xword	VfmwProc_SetClkSelect
	.word	2305
	.zero	4
	.xword	VfmwProc_SetStandardObedience
	.word	65535
	.zero	4
	.xword	0
	.type	__func__.53532, %object
	.size	__func__.53532, 18
__func__.53532:
	.string	"VCTRL_DestroyChan"
	.zero	6
	.type	__func__.54602, %object
	.size	__func__.54602, 30
__func__.54602:
	.string	"VCTRL_SetSingleFrameBufToChan"
	.zero	2
	.type	__func__.54614, %object
	.size	__func__.54614, 24
__func__.54614:
	.string	"VCTRL_AllocMemToDecoder"
	.data
	.align	3
.LANCHOR2 = . + 0
	.type	g_ClkSelect, %object
	.size	g_ClkSelect, 4
g_ClkSelect:
	.word	-1
	.type	g_SaveYUVBitWidth, %object
	.size	g_SaveYUVBitWidth, 4
g_SaveYUVBitWidth:
	.word	8
	.type	s_VfmwSavePath, %object
	.size	s_VfmwSavePath, 64
s_VfmwSavePath:
	.byte	47
	.byte	109
	.byte	110
	.byte	116
	.byte	0
	.zero	59
	.type	g_DefaultOutputOrder, %object
	.size	g_DefaultOutputOrder, 4
g_DefaultOutputOrder:
	.word	7
	.type	save_yuv_chan_num, %object
	.size	save_yuv_chan_num, 4
save_yuv_chan_num:
	.word	-1
	.type	mask_mmu_err_int, %object
	.size	mask_mmu_err_int, 4
mask_mmu_err_int:
	.word	1
	.type	g_SedOnlyEnable, %object
	.size	g_SedOnlyEnable, 4
g_SedOnlyEnable:
	.word	1
	.type	g_IRQ_FLAG, %object
	.size	g_IRQ_FLAG, 4
g_IRQ_FLAG:
	.word	128
	.type	g_not_direct_8x8_inference_flag, %object
	.size	g_not_direct_8x8_inference_flag, 1
g_not_direct_8x8_inference_flag:
	.byte	1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"InstID out of range" )
	.zero	4
.LC5:
	ASCII(.string	"vfmw_ctrl.c,L%d: %s\n" )
	.zero	3
.LC8:
	ASCII(.string	"Chan inactive" )
	.zero	2
.LC10:
	ASCII(.string	"s_VfmwCTrl.event_report_vdec = NULL\n" )
	.zero	3
.LC12:
	ASCII(.string	"s_VfmwCTrl.event_report_omxvdec = NULL\n" )
.LC15:
	ASCII(.string	"%s Unkown Adapter Type: %d, Len: %d\n" )
	.zero	3
.LC18:
	ASCII(.string	"Set standard obedience: %d\n" )
	.zero	4
.LC21:
	ASCII(.string	"g_ClkSelect(%d) set error! dat = %d not support\n" )
	.zero	7
.LC24:
	ASCII(.string	"ChanID:%d, Compress Disable!" )
	.zero	3
.LC26:
	ASCII(.string	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d\n" )
	.zero	1
.LC28:
	ASCII(.string	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d, YRatio: 0.%d, UVRatio: 0.%d\n" )
	.zero	4
.LC31:
	ASCII(.string	"ChanID:%d; " )
	.zero	4
.LC33:
	ASCII(.string	"VCmpEnable:%d; " )
.LC35:
	ASCII(.string	"LossCmpEnable:%d; " )
	.zero	5
.LC37:
	ASCII(.string	"YCmpRatio:%d, YCmpRatio:%d\n" )
	.zero	4
.LC39:
	ASCII(.string	"ChanID %d Already Create! Can not be set!!\n" )
	.zero	4
.LC43:
	ASCII(.string	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleLowlyEnable = 1 ------\n" )
	.zero	6
.LC45:
	ASCII(.string	"ERROR: g_SaveYUVBitWidth should be 8 or 10! (not to be %d)\n" )
	.zero	4
.LC48:
	ASCII(.string	"------ g_SaveYUVBitWidth = %d ------\n" )
	.zero	2
.LC51:
	ASCII(.string	"------ g_TraceImgPeriod = %x ------\n" )
	.zero	3
.LC54:
	ASCII(.string	"------ g_TraceFramePeriod = %x ------\n" )
	.zero	1
.LC57:
	ASCII(.string	"------ g_TraceBsPeriod = %x ------\n" )
	.zero	4
.LC60:
	ASCII(.string	"------ g_TraceCtrl = %x ------\n" )
.LC63:
	ASCII(.string	"------ dec stop = %d ------\n" )
	.zero	3
.LC66:
	ASCII(.string	"------ dec task delay %d ms ------\n" )
	.zero	4
.LC71:
	ASCII(.string	"%s/vfmw_el_save_%d.dat" )
	.zero	1
.LC73:
	ASCII(.string	"OK create file '%s' for channel %d el stream save\n" )
	.zero	5
.LC75:
	ASCII(.string	"failed create file '%s' for el stream save!\n" )
	.zero	3
.LC77:
	ASCII(.string	">>>> close el stream saving >>>>\n" )
	.zero	6
.LC80:
	ASCII(.string	"NO SUCH CHANNEL : %d\n" )
	.zero	2
.LC83:
	ASCII(.string	"Pay attention to  CHANNEL : %d\n" )
.LC86:
	ASCII(.string	"ResetCreateNewSave = %d\n" )
	.zero	7
.LC88:
	ASCII(.string	"ResetCreateNewSave can NOT be set to %d, must be 0 or 1\n" )
	.zero	7
.LC91:
	ASCII(.string	"USE_FF_APT_EN = %d\n" )
	.zero	4
.LC93:
	ASCII(.string	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\n" )
	.zero	4
.LC96:
	ASCII(.string	"g_CfgVp9FrmNum = %d\n" )
	.zero	3
.LC98:
	ASCII(.string	"Invalid output order %d\n" )
	.zero	7
.LC100:
	ASCII(.string	"set default output order %d\n" )
	.zero	3
.LC106:
	ASCII(.string	"OK create file '%s' for channel %d metadata_reorder stream save\n" )
	.zero	7
.LC108:
	ASCII(.string	"failed create file '%s' for metadata_reorder stream save!\n" )
	.zero	5
.LC110:
	ASCII(.string	">>>> close metadata stream saving >>>>\n" )
.LC116:
	ASCII(.string	"OK create file '%s' for channel %d metadata stream save\n" )
	.zero	7
.LC118:
	ASCII(.string	"failed create file '%s' for metadata stream save!\n" )
	.zero	5
.LC123:
	ASCII(.string	"address '0x%x' is not valid!\n" )
	.zero	2
.LC127:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC129:
	ASCII(.string	"1d image has been saved to '%s'\n" )
	.zero	7
.LC131:
	ASCII(.string	"open file '%s' fail!\n" )
	.zero	2
.LC136:
	ASCII(.string	"OK create file '%s' for channel %d seg stream save\n" )
	.zero	4
.LC138:
	ASCII(.string	"failed create file '%s' for seg stream save!\n" )
	.zero	2
.LC140:
	ASCII(.string	">>>> close seg stream saving >>>>\n" )
	.zero	5
.LC146:
	ASCII(.string	"OK create file '%s' for channel %d raw stream save\n" )
	.zero	4
.LC148:
	ASCII(.string	"failed create file '%s' for raw stream save!\n" )
	.zero	2
.LC150:
	ASCII(.string	">>>> close raw stream saving >>>>\n" )
	.zero	5
.LC156:
	ASCII(.string	"Failed to alloc VFMW_DumpImageTmp size %d!\n" )
	.zero	4
.LC158:
	ASCII(.string	"OK create file '%s' for chan %d yuv save.(crop %d)\n" )
	.zero	4
.LC160:
	ASCII(.string	"failed create file '%s' for yuv save!\n" )
	.zero	1
.LC162:
	ASCII(.string	"OK close yuv save.\n" )
	.zero	4
.LC167:
	ASCII(.string	"print memory tracer...\n" )
.LC170:
	ASCII(.string	"unmask vfmw mmu err int!\n" )
	.zero	6
.LC172:
	ASCII(.string	"mask vfmw mmu err int!\n" )
.LC175:
	ASCII(.string	"Disable SedOnly Func\n" )
	.zero	2
.LC177:
	ASCII(.string	"Enable SedOnly Func\n" )
	.zero	3
.LC179:
	ASCII(.string	"The channel number is to Large.\n" )
	.zero	7
.LC195:
	ASCII(.string	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSleep=%d)!\n" )
	.zero	5
.LC199:
	ASCII(.string	"Vfmw suspend totally take %d ms\n" )
	.zero	7
.LC201:
	ASCII(.string	"Force scd %d sleep.\n" )
	.zero	3
.LC203:
	ASCII(.string	"Force vdm %d sleep.\n" )
	.zero	3
.LC206:
	ASCII(.string	"proc cmd need no param:%p\n" )
	.zero	5
.LC213:
	ASCII(.string	"Vfmw resume totally take %d ms\n" )
.LC224:
	ASCII(.string	"%s,%d,pos(%d) error!\n" )
	.zero	2
.LC231:
	ASCII(.string	"%s, %d, pos(%d) error!\n" )
.LC237:
	ASCII(.string	"ChanID out of range" )
	.zero	4
.LC242:
	ASCII(.string	"can NOT config a not-opened Chan" )
	.zero	7
.LC244:
	ASCII(.string	"event_report null!" )
	.zero	5
.LC249:
	ASCII(.string	"%s Unkown Adapter Type: %d\n" )
	.zero	4
.LC255:
	ASCII(.string	"pstStreamParam is NULL" )
	.zero	1
.LC268:
	ASCII(.string	"L: %d, Stream Interface Error!!, ChanID: %d\n" )
	.zero	3
.LC271:
	ASCII(.string	"pstStreamIntf is NULL" )
	.zero	2
.LC281:
	ASCII(.string	"This Chan has not been created!!!" )
	.zero	6
.LC283:
	ASCII(.string	"can NOT get a not-opened Chan's information of bitstream" )
	.zero	7
.LC290:
	ASCII(.string	"Raw FreshNum=%d, FreshSize=%d\n" )
	.zero	1
.LC297:
	ASCII(.string	"Seg FreshNum=%d, FreshSize=%d\n" )
	.zero	1
.LC301:
	ASCII(.string	"pArgs is null" )
	.zero	2
.LC309:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC311:
	ASCII(.string	"no mem to arrange for soft dec\n" )
.LC314:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC317:
	ASCII(.string	"%s: L%d : vdm chan memory is too small to support user decoder\n" )
.LC319:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC324:
	ASCII(.string	"parameter err, null pointer!!!" )
	.zero	1
.LC328:
	ASCII(.string	"%s FATAL: pstChan = NULL!\n" )
	.zero	5
.LC330:
	ASCII(.string	"%s FATAL: pChanMem_vdh = NULL!\n" )
.LC332:
	ASCII(.string	"%s FATAL: pChanMem_frm = NULL!\n" )
.LC334:
	ASCII(.string	"DelAllFrameMemRecord err in VCTRL_FreeChanResource !\n" )
	.zero	2
.LC336:
	ASCII(.string	"%s FATAL: pChanMem_scd = NULL!\n" )
.LC338:
	ASCII(.string	"%s FATAL: pChanMem_ctx = NULL!\n" )
.LC343:
	ASCII(.string	"pstCfg is null" )
	.zero	1
.LC353:
	ASCII(.string	"Chip not support beyond %dx%d when Std != H264/VP8/MVC/USER.\n" )
	.zero	2
.LC373:
	ASCII(.string	"%s,%d,s_pstVfmwChan[chanID]->FspInst.stDecFsRec[i].PhyFS.PhyAddr = 0x%x\n" )
	.zero	7
.LC375:
	ASCII(.string	"%s,%d,can't find special frame match DecFs Num = %d\n" )
	.zero	3
.LC378:
	ASCII(.string	"call VCTRL_GetChanImage, ChanID = %d,\n" )
	.zero	1
.LC384:
	ASCII(.string	"This channel is not opened" )
	.zero	5
.LC388:
	ASCII(.string	"%s cannot output!\n" )
	.zero	5
.LC390:
	ASCII(.string	"%s: view_0 id(%d) > view_1 id(%d), error!\n" )
	.zero	5
.LC392:
	ASCII(.string	"%s: continuous view0 id(%d)!\n" )
	.zero	2
.LC394:
	ASCII(.string	"%s: continuous view1 id(%d)!\n" )
	.zero	2
.LC404:
	ASCII(.string	"pImage is NULL" )
	.zero	1
.LC406:
	ASCII(.string	"call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\n" )
	.zero	4
.LC409:
	ASCII(.string	"vdm_ctrl.c,L%d: Chan inactive\n" )
	.zero	1
.LC411:
	ASCII(.string	"vdm_ctrl.c,L%d: This channel is not opened\n" )
	.zero	4
.LC413:
	ASCII(.string	"vdm_ctrl.c,L%d: VCTRL_TryToRelSpecialFrm success!\n" )
	.zero	5
.LC418:
	ASCII(.string	"%s call SYNTAX_ReleaseImage failed\n" )
	.zero	4
.LC422:
	ASCII(.string	"vfmw_ctrl.c, line %d: ChanID out of range\n" )
	.zero	5
.LC424:
	ASCII(.string	"vfmw_ctrl.c, line %d: Chan %d is not open or not running\n" )
	.zero	6
.LC430:
	ASCII(.string	"%s VidStd=%d Error!\n" )
	.zero	3
.LC433:
	ASCII(.string	"Get DecParam Type Failure!\n" )
	.zero	4
.LC436:
	ASCII(.string	"vfmw_ctrl.c, line %d: ChanID out of range is %d\n" )
	.zero	7
.LC438:
	ASCII(.string	"Chan %d is not open or not running\n" )
	.zero	4
.LC443:
	ASCII(.string	"ChanId out of range" )
	.zero	4
.LC448:
	ASCII(.string	"This channel is not running" )
	.zero	4
.LC454:
	ASCII(.string	"line: %d Flush DPB failed!\n" )
	.zero	4
.LC456:
	ASCII(.string	"VCTRL_FlushDecoder\n" )
	.zero	4
.LC459:
	ASCII(.string	"fuction return value is null,%s %d MVC_OK != MVC_FlushDPB!!\n" )
	.zero	3
.LC471:
	ASCII(.string	"chan not create" )
.LC473:
	ASCII(.string	"can NOT start a not-opened Chan" )
.LC475:
	ASCII(.string	"NULL == pArgs" )
	.zero	2
.LC490:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC495:
	ASCII(.string	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan[ChanID]->eVidStd!\n" )
	.zero	1
.LC497:
	ASCII(.string	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\n" )
	.zero	4
.LC499:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC501:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC503:
	ASCII(.string	"line: %d, pLf is NULL!\n" )
.LC505:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC507:
	ASCII(.string	"VCTRL_GetUsrdecFrame get LogicFs fail!\n" )
.LC513:
	ASCII(.string	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal.\n" )
	.zero	2
.LC516:
	ASCII(.string	"VCTRL_GetChanMemSizeByOption L%d: arrange return failure\n" )
	.zero	6
.LC521:
	ASCII(.string	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32DisplayFrameNum(%d), extra_disp(%d)\n" )
	.zero	3
.LC529:
	ASCII(.string	"MEM_MapRegisterAddr reg 0x%x failed!\n" )
	.zero	2
.LC534:
	ASCII(.string	"VDMHAL_GetHalMemSize Vdh %d failed!\n" )
	.zero	3
.LC536:
	ASCII(.string	"MEM_AllocMemBlock Vdh %d failed!\n" )
	.zero	6
.LC538:
	ASCII(.string	"VDMHAL_OpenHAL Vdh %d failed!\n" )
	.zero	1
.LC540:
	ASCII(.string	"MEM_AllocMemBlock VFMW_VP9Prob %d failed!\n" )
	.zero	5
.LC545:
	ASCII(.string	"MEM_AllocMemBlock Scd %d failed!\n" )
	.zero	6
.LC547:
	ASCII(.string	"SM_OpenSCDDrv Scd %d failed!\n" )
	.zero	2
.LC549:
	ASCII(.string	"Register irq %d failed!\n" )
	.zero	7
.LC559:
	ASCII(.string	"extra_ref=" )
	.zero	5
.LC561:
	ASCII(.string	"=" )
	.zero	6
.LC563:
	ASCII(.string	" " )
	.zero	6
.LC566:
	ASCII(.string	"fuction return value is null,%s %d unknow error!!\n" )
	.zero	5
.LC568:
	ASCII(.string	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	6
.LC570:
	ASCII(.string	"extra_disp=" )
	.zero	4
.LC572:
	ASCII(.string	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
	.zero	5
.LC576:
	ASCII(.string	"extra_cmd=" )
	.zero	5
.LC583:
	ASCII(.string	"HI_VFMW_VideoDecode" )
	.zero	4
.LC587:
	ASCII(.string	"(safe,warn,danger) :amount = %d,%d,%d,%d\n" )
	.zero	6
.LC589:
	ASCII(.string	"strm_ctrl: I->IPB\n" )
	.zero	5
.LC591:
	ASCII(.string	"strm_ctrl: IPB->I\n" )
	.zero	5
.LC593:
	ASCII(.string	"(CurrMode,NextMode) = %d,%d\n" )
	.zero	3
.LC598:
	ASCII(.string	"pic_pts: %lld\n" )
	.zero	1
.LC600:
	ASCII(.string	"pic_usertag: %lld\n" )
	.zero	5
.LC602:
	ASCII(.string	"pic_pts: %lld pic_usertag = %lld\n" )
	.zero	6
.LC611:
	ASCII(.string	"Syntax is stopped from This channel" )
	.zero	4
.LC616:
	ASCII(.string	"[%d] vdm busy\n" )
	.zero	1
.LC618:
	ASCII(.string	"[%d] no frame\n" )
	.zero	1
.LC620:
	ASCII(.string	"DFS, Wait Partition\n" )
	.zero	3
.LC622:
	ASCII(.string	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %d, eFspPartitionState: %d\n" )
	.zero	2
.LC624:
	ASCII(.string	"[%d] no stream\n" )
.LC626:
	ASCII(.string	"seg_pts: %lld, seg_usertag = %lld\n" )
	.zero	5
.LC640:
	ASCII(.string	"Thread running...\n" )
	.zero	5
.LC642:
	ASCII(.string	"Thread stopped!\n" )
	.zero	7
.LC644:
	ASCII(.string	"thread running...\n" )
	.zero	5
.LC646:
	ASCII(.string	"thread stopped...\n" )
	.zero	5
.LC649:
	ASCII(.string	"Thread killed!\n" )
.LC656:
	ASCII(.string	"ERROR:ReadNum = %d larger than VFMW_MAX_RESERVE_NUM(%d)\n" )
	.zero	7
.LC659:
	ASCII(.string	"The array of occupied frames is overflow, s_pstVfmwChan[%d]->specialFrameNum = %d" )
	.zero	6
.LC663:
	ASCII(.string	"pSpecialFrmInfo = null!!!" )
	.zero	6
.LC673:
	ASCII(.string	"ChanID out of range!" )
	.zero	3
.LC676:
	ASCII(.string	"pstChanState = NULL" )
	.zero	4
.LC679:
	ASCII(.string	"s_pstVfmwChan = NULL" )
	.zero	3
.LC696:
	ASCII(.string	"SetVdecExtra ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	1
.LC698:
	ASCII(.string	"SetVdecExtra ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
.LC707:
	ASCII(.string	"Command \"%d\" not registerd!\n" )
	.zero	3
.LC723:
	ASCII(.string	"Chan %d Report Last Frame, Value=%d, LastFrameState=%d\n" )
.LC727:
	ASCII(.string	"Last frame output failed!\n" )
	.zero	5
.LC729:
	ASCII(.string	"Last frame output successed!\n" )
	.zero	2
.LC731:
	ASCII(.string	"Last frame already output, image id: %d!\n" )
	.zero	6
.LC743:
	ASCII(.string	"line %d can not know YuvFormat = %d\n" )
	.zero	3
.LC745:
	ASCII(.string	"userdec frame(phy=%#x) address error!\n" )
	.zero	1
.LC747:
	ASCII(.string	"can not map vir addr for usrdat frame(cbphy=%#x)\n" )
	.zero	6
.LC749:
	ASCII(.string	"line: %d, pLogic is Null!\n" )
	.zero	5
.LC752:
	ASCII(.string	"eYuvFormat %d is not support!!\n" )
.LC758:
	ASCII(.string	"pUsrdecFrame == NULL" )
	.zero	3
.LC760:
	ASCII(.string	"VCTRL_PutUsrdecFrame: VidStd is %d\n" )
	.zero	4
.LC763:
	ASCII(.string	"VCTRL_PutUsrdecFrame return err\n" )
	.zero	7
.LC765:
	ASCII(.string	"L:%d ChanID out of range\n" )
	.zero	6
.LC768:
	ASCII(.string	"L:%d This Chan has not been created!!!\n" )
.LC770:
	ASCII(.string	"L:%d WARNING: vidio std not setted!\n" )
	.zero	3
.LC781:
	ASCII(.string	"WARNING: vidio std not setted!" )
	.zero	1
.LC791:
	ASCII(.string	"start chan %d: VCTRL_StartChan return %d\n" )
	.zero	6
.LC801:
	ASCII(.string	"This Chan has not been created or has been destroyed !" )
	.zero	1
.LC804:
	ASCII(.string	"VCTRL_StopChanWithCheck fail!\n" )
	.zero	1
.LC809:
	ASCII(.string	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\n" )
	.zero	6
.LC813:
	ASCII(.string	"-------------------------------------------------------------------------\n" )
	.zero	5
.LC827:
	ASCII(.string	"Param Invalid of PChanOption is NULL\n" )
	.zero	2
.LC830:
	ASCII(.string	"line %d VCTRL_GetChanMemSize failed!\n" )
	.zero	2
.LC832:
	ASCII(.string	"L: %d : part we can NOT alloc buffer for channel context\n" )
	.zero	6
.LC834:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel context\n" )
	.zero	6
.LC836:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh\n" )
	.zero	2
.LC838:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh, %#x < %#x\n" )
	.zero	7
.LC840:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel scd\n" )
	.zero	2
.LC842:
	ASCII(.string	"L: %d : can NOT alloc buffer for SCD\n" )
	.zero	2
.LC845:
	ASCII(.string	"vfmw have max(%d) channels opened, can NOT create more channels\n" )
	.zero	7
.LC848:
	ASCII(.string	"Chan:%d can NOT enable FSP instance\n" )
	.zero	3
.LC856:
	ASCII(.string	"VCTRL_CheckChanWH return err.\n" )
	.zero	1
.LC859:
	ASCII(.string	"VFMW didn't support std %d.\n" )
	.zero	3
.LC861:
	ASCII(.string	"VCTRL_ConfigChan with same config paramater.\n" )
	.zero	2
.LC865:
	ASCII(.string	"can NOT VCTRL_PartitionMemForStdUser\n" )
	.zero	2
.LC872:
	ASCII(.string	"chan %d: new StrmOFThr = %d\n" )
	.zero	3
.LC875:
	ASCII(.string	"chan %d: new DecMode = %d\n" )
	.zero	5
.LC878:
	ASCII(.string	"chan %d: GetChanCfg failed!\n" )
	.zero	3
.LC880:
	ASCII(.string	"chan %d: new DecOrderOutput = %d\n" )
	.zero	6
.LC883:
	ASCII(.string	"chan %d: new ChanErrThr = %d\n" )
	.zero	2
.LC886:
	ASCII(.string	"reset chan %d: VCTRL_ResetChan return %d\n" )
	.zero	6
.LC891:
	ASCII(.string	"%s:L%d: %s\n" )
	.zero	4
.LC894:
	ASCII(.string	"This Chan has not been created or has been destroyed !!!" )
	.zero	7
.LC896:
	ASCII(.string	"can NOT stop a not-opened Chan" )
	.zero	1
.LC907:
	ASCII(.string	"stop chan %d: VCTRL_StopChan return %d\n" )
.LC917:
	ASCII(.string	"WARNNING: dsp in lowdelay state, we can not supported  avs in the same time!!!\n" )
.LC919:
	ASCII(.string	"WARNNING: dsp in avs state, we can not supported  lowdelay in the same time!!!\n" )
.LC929:
	ASCII(.string	"%s, %d, actul size = 0x%x, except size= 0x%x\n" )
	.zero	2
.LC931:
	ASCII(.string	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\n" )
	.zero	1
.LC934:
	ASCII(.string	"%s: Chan %d set single frame failed!\n" )
	.zero	2
.LC936:
	ASCII(.string	"%s: Chan %d no frame buffer store!\n" )
	.zero	4
.LC941:
	ASCII(.string	"DFS, request frame store fail!, chanid: %d\n" )
	.zero	4
.LC943:
	ASCII(.string	"DFS, set decoding thread state to success!\n " )
	.zero	3
.LC946:
	ASCII(.string	"%s set chan %d ctrl state CHAN_FRAME_STORE_ALLOC failed!\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
.LANCHOR3 = . + 4352
.LANCHOR5 = . + 8704
.LANCHOR6 = . + 17408
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 256
s_pstVfmwChan:
	.zero	256
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 344
s_VfmwCTrl:
	.zero	344
	.type	g_StandardObedience, %object
	.size	g_StandardObedience, 4
g_StandardObedience:
	.zero	4
	.zero	4
	.type	g_VfmwCompressPara, %object
	.size	g_VfmwCompressPara, 512
g_VfmwCompressPara:
	.zero	512
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.zero	4
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.zero	4
	.type	vfmw_save_el_file, %object
	.size	vfmw_save_el_file, 256
vfmw_save_el_file:
	.zero	256
	.type	save_file_cnt.54343, %object
	.size	save_file_cnt.54343, 4
save_file_cnt.54343:
	.zero	4
	.type	save_el_chan_num, %object
	.size	save_el_chan_num, 4
save_el_chan_num:
	.zero	4
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.zero	4
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.zero	4
	.type	vfmw_save_metadata_reorder_file, %object
	.size	vfmw_save_metadata_reorder_file, 256
vfmw_save_metadata_reorder_file:
	.zero	256
	.type	save_file_cnt.54337, %object
	.size	save_file_cnt.54337, 4
save_file_cnt.54337:
	.zero	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.zero	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 256
vfmw_save_metadata_file:
	.zero	256
	.type	save_file_cnt.54331, %object
	.size	save_file_cnt.54331, 4
save_file_cnt.54331:
	.zero	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.zero	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 256
vfmw_save_seg_file:
	.zero	256
	.type	save_file_cnt.54309, %object
	.size	save_file_cnt.54309, 4
save_file_cnt.54309:
	.zero	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.zero	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 256
vfmw_save_str_file:
	.zero	256
	.type	save_file_cnt.54303, %object
	.size	save_file_cnt.54303, 4
save_file_cnt.54303:
	.zero	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.zero	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 256
vfmw_save_yuv_file:
	.zero	256
	.type	save_file_cnt.54316, %object
	.size	save_file_cnt.54316, 4
save_file_cnt.54316:
	.zero	4
	.zero	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 32
MemRecord_YUV:
	.zero	32
	.type	pVl, %object
	.size	pVl, 8
pVl:
	.zero	8
	.type	pUl, %object
	.size	pUl, 8
pUl:
	.zero	8
	.type	pY, %object
	.size	pY, 8
pY:
	.zero	8
	.type	pVl_2bit, %object
	.size	pVl_2bit, 8
pVl_2bit:
	.zero	8
	.type	pUl_2bit, %object
	.size	pUl_2bit, 8
pUl_2bit:
	.zero	8
	.type	pY_2bit, %object
	.size	pY_2bit, 8
pY_2bit:
	.zero	8
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.zero	4
	.zero	4
	.type	pPixelArray, %object
	.size	pPixelArray, 8
pPixelArray:
	.zero	8
	.type	g_IsrFlag, %object
	.size	g_IsrFlag, 1
g_IsrFlag:
	.zero	1
	.zero	7
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 768
s_StreamIntf:
	.zero	768
	.type	FspInstInfo.53420, %object
	.size	FspInstInfo.53420, 2824
FspInstInfo.53420:
	.zero	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.53724, %object
	.size	last_rec_pos_time.53724, 128
last_rec_pos_time.53724:
	.zero	128
	.type	last_rec_pos_time.53734, %object
	.size	last_rec_pos_time.53734, 128
last_rec_pos_time.53734:
	.zero	128
	.type	MemArrange.54029, %object
	.size	MemArrange.54029, 1232
MemArrange.54029:
	.zero	1232
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.zero	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
	.zero	4
	.type	g_VfmwIrqHandle, %object
	.size	g_VfmwIrqHandle, 4
g_VfmwIrqHandle:
	.zero	4
	.zero	4
	.type	cmdline, %object
	.size	cmdline, 1024
cmdline:
	.zero	1024
	.type	extra_cmd, %object
	.size	extra_cmd, 4
extra_cmd:
	.zero	4
	.type	g_allow_B_before_P, %object
	.size	g_allow_B_before_P, 1
g_allow_B_before_P:
	.zero	1
	.type	g_not_allow_H264FullPictureRepair_flag, %object
	.size	g_not_allow_H264FullPictureRepair_flag, 1
g_not_allow_H264FullPictureRepair_flag:
	.zero	1
	.type	g_apple_airplay_mirrorinig_flag, %object
	.size	g_apple_airplay_mirrorinig_flag, 1
g_apple_airplay_mirrorinig_flag:
	.zero	1
	.zero	1
	.type	g_event_report, %object
	.size	g_event_report, 8
g_event_report:
	.zero	8
	.type	g_DSPState, %object
	.size	g_DSPState, 128
g_DSPState:
	.zero	128
	.type	last_rec_pos_time.54147, %object
	.size	last_rec_pos_time.54147, 128
last_rec_pos_time.54147:
	.zero	128
	.type	last_rec_pos_decparam_time.54148, %object
	.size	last_rec_pos_decparam_time.54148, 128
last_rec_pos_decparam_time.54148:
	.zero	128
	.type	ChanPriTab.54097, %object
	.size	ChanPriTab.54097, 128
ChanPriTab.54097:
	.zero	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 9600
g_VfmwChanStat:
	.zero	9600
	.type	PrioArray.53537, %object
	.size	PrioArray.53537, 128
PrioArray.53537:
	.zero	128
	.type	pOption, %object
	.size	pOption, 8
pOption:
	.zero	8
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.zero	128
	.type	Capability.53593, %object
	.size	Capability.53593, 148
Capability.53593:
	.zero	148
	.zero	4
	.type	PrioArray.53592, %object
	.size	PrioArray.53592, 128
PrioArray.53592:
	.zero	128
	.type	g_EsBufValidFlag, %object
	.size	g_EsBufValidFlag, 128
g_EsBufValidFlag:
	.zero	128
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.zero	4
	.zero	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 64
g_VfmwGlobalStat:
	.zero	64
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 8
AcceleratorCharacter:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
