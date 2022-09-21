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
	str	w4, [x3, 1232]
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
	.type	VCTRL_CanBeDecodedByHardWare.part.19, %function
VCTRL_CanBeDecodedByHardWare.part.19:
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
	.size	VCTRL_CanBeDecodedByHardWare.part.19, .-VCTRL_CanBeDecodedByHardWare.part.19
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
	str	wzr, [x3, 1232]
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
	str	w20, [x0, 1216]
	mov	w0, 0
.L302:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L305:
	str	wzr, [x0, 1216]
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
	add	x2, x0, 290816
	mov	w0, 0
	str	w20, [x2, 1148]
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
	add	x0, x0, 290816
	ldr	w0, [x0, 1148]
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
	mov	x2, 34408
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
	add	x19, x0, 1616
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
	mov	x3, 34408
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
	add	x0, x0, 1488
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w0, [x1, 1488]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L383
	mov	w0, 0
	str	wzr, [x1, 1488]
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
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	mov	w0, 14920
	movk	w0, 0xc, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L464:
	mov	w0, 728
	movk	w0, 0xb2, lsl 16
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
	ldr	w3, [x0, 1292]
	cmp	w3, w2
	bgt	.L493
	ldr	x1, .LC352
	ldr	w3, [x0, 1296]
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
	str	w2, [x0, 1200]
	cmp	w1, 1
	str	w1, [x0, 1204]
	beq	.L505
	mov	w1, -1
	str	w1, [x0, 1208]
.L503:
	str	w1, [x0, 1212]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L505:
	ldp	w2, w1, [x3, 8]
	str	w2, [x0, 1208]
	b	.L503
	.p2align 3
.L504:
	ldr	x0, [x0, w19, sxtw 3]
	mov	w1, -1
	add	x2, x0, 1024
	stp	wzr, wzr, [x2, 176]
	stp	w1, w1, [x2, 184]
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
	ldr	x3, [x19, w24, sxtw 3]
	cbz	x3, .L557
	add	x0, x3, 294912
	ldr	w1, [x0, 1168]
	cbz	w1, .L526
	ldr	w0, [x0, 644]
	mov	w2, 0
	cmp	w21, w0
	bne	.L529
	b	.L558
	.p2align 3
.L530:
	add	x0, x0, 2088
	add	x0, x3, x0, lsl 4
	ldr	w0, [x0, 4]
	cmp	w21, w0
	beq	.L527
.L529:
	add	w2, w2, 1
	cmp	w1, w2
	mov	w20, w2
	sxtw	x0, w2
	add	x0, x0, 16384
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
	add	x0, x3, 282624
	mov	w23, 1
	add	x0, x0, 3520
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
	sub	w22, w1, #1
	mov	w0, 3
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
	add	x3, x1, 282624
	add	x1, x1, 286720
	strb	wzr, [x3, 3426]
	strb	wzr, [x1, 2146]
	blr	x2
	cmp	w22, w20
	bls	.L541
	sxtw	x21, w24
	uxtw	x23, w20
	.p2align 2
.L533:
	add	w20, w20, 1
	add	x23, x23, 16384
	add	x0, x23, 2088
	ldr	x3, [x19, x21, lsl 3]
	uxtw	x23, w20
	ldr	x4, [x25, 104]
	add	x1, x23, 16384
	mov	x2, 16
	add	x1, x1, 2088
	add	x0, x3, x0, lsl 4
	add	x1, x3, x1, lsl 4
	blr	x4
	cmp	w20, w22
	bcc	.L533
.L532:
	uxtw	x0, w22
	ldr	x4, [x19, w24, sxtw 3]
	add	x0, x0, 16384
	ldr	x3, [x25, 96]
	add	x0, x0, 2088
	mov	x2, 16
	mov	w1, 0
	add	x0, x4, x0, lsl 4
	blr	x3
	ldr	x1, [x19, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 294912
	ldr	w2, [x1, 1168]
	sub	w2, w2, #1
	str	w2, [x1, 1168]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L560:
	add	x2, x3, 262144
	ldr	x20, .LC372
	ldr	x1, .LC376
	mov	w3, 3740
	add	x20, x20, 152
	mov	w0, 1
	ldrsb	w4, [x2, 2003]
	mov	x2, x20
	bl	dprint_vfmw
	ldr	x6, [x19, w24, sxtw 3]
	add	x0, x6, 262144
	ldrsb	w0, [x0, 2003]
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
	add	x4, x4, 282624
	ldr	w4, [x4, 3432]
	bl	dprint_vfmw
	ldr	x6, [x19, x21, lsl 3]
	add	x0, x6, 262144
	ldrsb	w0, [x0, 2003]
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
	add	x0, x0, 294912
	mov	x1, x20
	add	x0, x0, 1232
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
	add	x1, x1, 311296
	ldrb	w1, [x1, 744]
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
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	add	x0, x1, 294912
	add	x0, x0, 1232
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
	add	x0, x0, 294912
	add	x0, x0, 1232
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	add	x0, x0, 294912
	add	x0, x0, 1232
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	add	x0, x0, 294912
	add	x0, x0, 1232
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
	ldr	w2, [x20, 188]
	cmn	w2, #1
	beq	.L612
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 72
	str	w2, [x29, 220]
	add	x0, x0, 294912
	add	x0, x0, 1232
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
	bhi	.L661
	ldr	x0, .LC427
	ldr	x20, [x0, w19, sxtw 3]
	cbz	x20, .L661
	ldr	w0, [x20, 4]
	mov	x1, 0
	cmp	w0, 1
	bne	.L640
	ldr	w0, [x20, 8]
	cmp	w0, 1
	bne	.L640
	ldr	w3, [x20, 600]
	cmp	w3, 17
	bls	.L662
.L641:
	ldr	x2, .LC429
	mov	w0, 0
	ldr	x1, .LC431
	add	x2, x2, 280
	bl	dprint_vfmw
	mov	x1, 0
	b	.L640
	.p2align 3
.L661:
	mov	x1, 0
.L640:
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L662:
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
	.text
	.p2align 3
.L651:
	add	x0, x20, 294912
	ldr	x19, [x0, 1248]
.L656:
	cbz	x19, .L661
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
.L653:
	add	x0, x20, 294912
	ldr	x19, [x0, 1472]
	b	.L656
	.p2align 3
.L645:
	add	x0, x20, 294912
	ldr	x19, [x0, 2280]
	b	.L656
	.p2align 3
.L654:
	add	x0, x20, 294912
	ldr	x19, [x0, 3680]
	b	.L656
	.p2align 3
.L642:
	add	x0, x20, 294912
	ldr	x19, [x0, 1856]
	b	.L656
	.p2align 3
.L648:
	add	x0, x20, 294912
	ldr	x19, [x0, 1264]
	b	.L656
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
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L665
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L665:
	ldr	x1, .LC434
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
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
	bhi	.L667
	ldr	x21, .LC435
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L667
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L670
	ldr	w22, [x0, 8]
	cmp	w22, 1
	beq	.L671
.L670:
	ldr	x1, .LC439
	mov	w2, w19
	mov	w0, 22
	mov	w20, 0
	bl	dprint_vfmw
.L669:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L667:
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
.L671:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L676
	ldr	x0, [x21, w19, sxtw 3]
	mov	w20, 0
	str	wzr, [x0, 444]
	str	wzr, [x0, 448]
	b	.L669
	.p2align 3
.L676:
	ldr	x23, [x21, w19, sxtw 3]
	ldr	x0, .LC440
	ldr	w20, [x23, 444]
	cbz	w20, .L677
	ldr	x0, [x0]
	blr	x0
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 448]
	cmp	w0, w2
	bls	.L674
	sub	w0, w0, w2
	mov	w20, 0
	cmp	w0, 40
	bls	.L669
.L674:
	mov	w20, w22
	str	wzr, [x1, 444]
	str	wzr, [x1, 448]
	b	.L669
.L677:
	ldr	x0, [x0]
	str	w22, [x23, 444]
	blr	x0
	str	w0, [x23, 448]
	b	.L669
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
	cmp	w1, 17
	bhi	.L678
	ldr	x2, .LC442
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx681
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx681:
	.section	.rodata
	.align	0
	.align	2
.L681:
	.byte	(.L680 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L683 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L678 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L686 - .Lrtx681) / 4
	.byte	(.L678 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.byte	(.L678 - .Lrtx681) / 4
	.byte	(.L691 - .Lrtx681) / 4
	.byte	(.L692 - .Lrtx681) / 4
	.byte	(.L690 - .Lrtx681) / 4
	.text
	.p2align 3
.L690:
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
.L678:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L686:
	add	x0, x0, 294912
	str	xzr, [x0, 1264]
	b	.L678
	.p2align 3
.L680:
	add	x0, x0, 294912
	str	xzr, [x0, 1856]
	b	.L678
	.p2align 3
.L692:
	add	x0, x0, 294912
	str	xzr, [x0, 3680]
	b	.L678
	.p2align 3
.L683:
	add	x0, x0, 294912
	str	xzr, [x0, 2280]
	b	.L678
	.p2align 3
.L691:
	add	x0, x0, 294912
	str	xzr, [x0, 1472]
	b	.L678
	.size	VCTRL_ClearDecparam, .-VCTRL_ClearDecparam
	.align	3
.LC441:
	.xword	.LANCHOR0
	.align	3
.LC442:
	.xword	.L681
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L699
	ldr	x0, .LC446
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L700
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L698
	ldr	x3, .LC449
	mov	w2, 4773
	ldr	x1, .LC445
	mov	w0, 0
	bl	dprint_vfmw
.L694:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L698:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L699:
	ldr	x3, .LC444
	mov	w2, 4771
	ldr	x1, .LC445
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L700:
	ldr	x3, .LC447
	mov	w2, 4772
	ldr	x1, .LC445
	bl	dprint_vfmw
	b	.L694
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
	cbz	x0, .L728
	add	x0, x0, 294912
	ldr	w1, [x0, 1232]
	cmp	w1, 17
	bls	.L729
.L721:
	mov	w0, 0
.L703:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L729:
	ldr	x2, .LC453
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx705
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx705:
	.section	.rodata
	.align	0
	.align	2
.L705:
	.byte	(.L704 - .Lrtx705) / 4
	.byte	(.L706 - .Lrtx705) / 4
	.byte	(.L707 - .Lrtx705) / 4
	.byte	(.L708 - .Lrtx705) / 4
	.byte	(.L721 - .Lrtx705) / 4
	.byte	(.L709 - .Lrtx705) / 4
	.byte	(.L710 - .Lrtx705) / 4
	.byte	(.L721 - .Lrtx705) / 4
	.byte	(.L711 - .Lrtx705) / 4
	.byte	(.L712 - .Lrtx705) / 4
	.byte	(.L713 - .Lrtx705) / 4
	.byte	(.L713 - .Lrtx705) / 4
	.byte	(.L713 - .Lrtx705) / 4
	.byte	(.L714 - .Lrtx705) / 4
	.byte	(.L721 - .Lrtx705) / 4
	.byte	(.L715 - .Lrtx705) / 4
	.byte	(.L716 - .Lrtx705) / 4
	.byte	(.L717 - .Lrtx705) / 4
	.text
	.p2align 3
.L717:
	add	x0, x0, 1240
	bl	VP9DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L716:
	add	x0, x0, 1240
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L730
.L719:
	ldr	x1, .LC457
	mov	w0, 32
	bl	dprint_vfmw
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	mov	w0, 0
	b	.L703
	.p2align 3
.L715:
	add	x0, x0, 1240
	bl	MVC_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	x0, [x19, w20, sxtw 3]
	mov	w1, -1
	add	x0, x0, 294912
	add	x0, x0, 1240
	bl	MVC_FlushDPB
	cbz	w0, .L721
	ldr	x2, .LC458
	mov	w3, 4862
	ldr	x1, .LC460
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L703
	.p2align 3
.L714:
	add	x0, x0, 1240
	bl	VP8DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L713:
	add	x0, x0, 1240
	bl	VP6DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L712:
	add	x0, x0, 1240
	bl	REAL9DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L711:
	add	x0, x0, 1240
	bl	REAL8DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L710:
	add	x0, x0, 1240
	bl	AVSDEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L709:
	add	x0, x0, 1240
	bl	DIVX3DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L708:
	add	x0, x0, 1240
	bl	MPEG2DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L707:
	add	x0, x0, 1240
	bl	MPEG4DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L706:
	add	x0, x0, 1240
	bl	VC1DEC_GetRemainImg
	mov	w0, 0
	b	.L703
	.p2align 3
.L704:
	add	x0, x0, 1240
	bl	H264_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	x0, [x19, w20, sxtw 3]
	add	x0, x0, 294912
	add	x0, x0, 1240
	bl	FlushDPB
	cbz	w0, .L721
	ldr	x1, .LC455
	mov	w2, 4829
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L703
	.p2align 3
.L730:
	ldr	x1, .LC455
	mov	w2, 4839
	mov	w0, 0
	bl	dprint_vfmw
	b	.L719
.L728:
	ldr	x3, .LC451
	mov	w2, 4803
	ldr	x1, .LC452
	bl	dprint_vfmw
	mov	w0, -1
	b	.L703
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
	.xword	.L705
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
	bhi	.L754
	ldr	x0, .LC463
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L755
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bne	.L756
	ldr	w2, [x1, 600]
	cmp	w2, 17
	bls	.L757
.L750:
	mov	w0, 0
	b	.L733
	.p2align 3
.L757:
	ldr	x3, .LC466
	ldrb	w2, [x3,w2,uxtw]
	adr	x3, .Lrtx737
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx737:
	.section	.rodata
	.align	0
	.align	2
.L737:
	.byte	(.L736 - .Lrtx737) / 4
	.byte	(.L738 - .Lrtx737) / 4
	.byte	(.L739 - .Lrtx737) / 4
	.byte	(.L740 - .Lrtx737) / 4
	.byte	(.L750 - .Lrtx737) / 4
	.byte	(.L741 - .Lrtx737) / 4
	.byte	(.L742 - .Lrtx737) / 4
	.byte	(.L750 - .Lrtx737) / 4
	.byte	(.L743 - .Lrtx737) / 4
	.byte	(.L744 - .Lrtx737) / 4
	.byte	(.L745 - .Lrtx737) / 4
	.byte	(.L745 - .Lrtx737) / 4
	.byte	(.L745 - .Lrtx737) / 4
	.byte	(.L746 - .Lrtx737) / 4
	.byte	(.L750 - .Lrtx737) / 4
	.byte	(.L747 - .Lrtx737) / 4
	.byte	(.L748 - .Lrtx737) / 4
	.byte	(.L749 - .Lrtx737) / 4
	.text
	.p2align 3
.L749:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	VP9DEC_GetImageBuffer
.L733:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L748:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	HEVCDEC_GetImageBuffer
	b	.L733
	.p2align 3
.L747:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	MVC_DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L746:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	VP8DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L745:
	ldr	x2, .LC467
	ldr	w2, [x2, 2064]
	tbz	x2, 0, .L733
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	VP6DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L744:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	REAL9DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L743:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	REAL8DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L742:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	AVSDEC_GetImageBuffer
	b	.L733
	.p2align 3
.L741:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	DIVX3DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L740:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	MPEG2DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L739:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	MPEG4DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L738:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	VC1DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L736:
	add	x0, x1, 294912
	add	x0, x0, 1240
	bl	H264DEC_GetImageBuffer
	b	.L733
	.p2align 3
.L756:
	ldr	x3, .LC465
	mov	w2, 4932
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L733
	.p2align 3
.L754:
	ldr	x3, .LC461
	mov	w2, 4930
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L733
.L755:
	ldr	x3, .LC464
	mov	w2, 4931
	ldr	x1, .LC462
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L733
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
	.xword	.L737
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
	bhi	.L764
	ldr	x0, .LC470
	ldr	x2, [x0, w19, sxtw 3]
	cbz	x2, .L765
	ldr	w0, [x2, 4]
	cmp	w0, 1
	bne	.L766
	cbz	x20, .L767
	ldr	w1, [x20]
	mov	w0, 0
	str	w1, [x2, 1220]
.L760:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L766:
	ldr	x3, .LC474
	mov	w2, 5055
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L760
	.p2align 3
.L764:
	ldr	x3, .LC468
	mov	w2, 5053
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L760
.L765:
	ldr	x3, .LC472
	mov	w2, 5054
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L760
.L767:
	ldr	x3, .LC476
	mov	w2, 5056
	ldr	x1, .LC469
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L760
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
	bhi	.L774
	ldr	x0, .LC479
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L775
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L776
	cbz	x20, .L777
	ldr	x3, .LC483
	mov	x2, 20
	mov	x1, x20
	add	x0, x0, 1256
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L770:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L776:
	ldr	x3, .LC481
	mov	w2, 5068
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L770
	.p2align 3
.L774:
	ldr	x3, .LC477
	mov	w2, 5066
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L770
.L777:
	ldr	x3, .LC482
	mov	w2, 5069
	ldr	x1, .LC478
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L770
.L775:
	ldr	x3, .LC480
	mov	w2, 5067
	ldr	x1, .LC478
	bl	dprint_vfmw
	mov	w0, -1
	b	.L770
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
	cbz	x0, .L781
	add	x1, x29, 40
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L781
	ldr	w0, [x29, 48]
	cmp	w0, 16
	bgt	.L782
	ldr	w0, [x29, 56]
	cmp	w0, 524288
	ble	.L781
.L782:
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	csetm	w0, ne
	cbnz	w0, .L780
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
.L781:
	mov	w0, -1
.L780:
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
	bhi	.L791
	ldr	x0, .LC487
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L791
	ldr	w1, [x0, 4]
	cbz	w1, .L791
	ldr	w1, [x0, 8]
	cbz	w1, .L791
	ldr	w1, [x0, 20]
	cbz	w1, .L791
	ldr	w0, [x0, 600]
	ldr	x19, [sp, 16]
	cmp	w0, 21
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L791:
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
	b	.L795
	.p2align 3
.L793:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L807
.L795:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 294912
	add	x1, x1, 1240
	cbz	x2, .L793
	cmp	x19, x1
	bne	.L793
	cmn	w0, #1
	str	w0, [x19, 616]
	mov	w0, 1
	beq	.L798
.L802:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L807:
	mov	w0, -1
	str	w0, [x19, 616]
.L798:
	ldr	x1, .LC491
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L802
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
	cbz	x19, .L810
	ldr	w0, [x19, 616]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 616]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L811
	ldr	w0, [x19, 616]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 616]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
.L809:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L811:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L810:
	mov	w0, -2
	b	.L809
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
	cbz	x0, .L826
	ldr	w1, [x0, 600]
	cmp	w1, 20
	bne	.L827
	ldr	w0, [x0, 520]
	cmp	w0, 2
	ble	.L828
	mov	w1, 1
	mov	w0, w20
	bl	FSP_NewLogicFs
	mov	w22, w0
	tbnz	w0, #31, .L829
	mov	w1, w0
	mov	w0, w20
	bl	FSP_GetLogicFs
	mov	x19, x0
	ldr	x1, .LC502
	mov	w2, w22
	mov	w0, 18
	bl	dprint_vfmw
	cbz	x19, .L830
	ldr	x0, [x19, 32]
	cbz	x0, .L819
	ldr	x1, [x19, 40]
	cbz	x1, .L819
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
.L814:
	mov	w0, w1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L827:
	ldr	x1, .LC496
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
	.p2align 3
.L828:
	ldr	x1, .LC498
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
	.p2align 3
.L819:
	ldr	x1, .LC508
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
	.p2align 3
.L829:
	ldr	x1, .LC500
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
.L826:
	ldr	x1, .LC494
	mov	w2, 5343
	ldr	x3, .LC493
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
.L830:
	ldr	x1, .LC504
	mov	w2, 5373
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, -1
	b	.L814
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
	cbz	x1, .L849
	ldr	w0, [x1, 600]
	cmp	w0, 20
	bls	.L850
.L831:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L850:
	ldr	x2, .LC512
	ldrb	w0, [x2,w0,uxtw]
	adr	x2, .Lrtx835
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx835:
	.section	.rodata
	.align	0
	.align	2
.L835:
	.byte	(.L834 - .Lrtx835) / 4
	.byte	(.L836 - .Lrtx835) / 4
	.byte	(.L837 - .Lrtx835) / 4
	.byte	(.L838 - .Lrtx835) / 4
	.byte	(.L831 - .Lrtx835) / 4
	.byte	(.L839 - .Lrtx835) / 4
	.byte	(.L840 - .Lrtx835) / 4
	.byte	(.L831 - .Lrtx835) / 4
	.byte	(.L841 - .Lrtx835) / 4
	.byte	(.L842 - .Lrtx835) / 4
	.byte	(.L843 - .Lrtx835) / 4
	.byte	(.L843 - .Lrtx835) / 4
	.byte	(.L843 - .Lrtx835) / 4
	.byte	(.L844 - .Lrtx835) / 4
	.byte	(.L831 - .Lrtx835) / 4
	.byte	(.L845 - .Lrtx835) / 4
	.byte	(.L846 - .Lrtx835) / 4
	.byte	(.L847 - .Lrtx835) / 4
	.byte	(.L831 - .Lrtx835) / 4
	.byte	(.L831 - .Lrtx835) / 4
	.byte	(.L848 - .Lrtx835) / 4
	.text
	.p2align 3
.L848:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	USERDEC_Init
	b	.L831
	.p2align 3
.L847:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	VP9DEC_Init
	b	.L831
	.p2align 3
.L846:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	HEVCDEC_Init
	b	.L831
	.p2align 3
.L845:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	MVC_DEC_Init
	b	.L831
	.p2align 3
.L844:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	VP8DEC_Init
	b	.L831
	.p2align 3
.L843:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	VP6DEC_Init
	b	.L831
	.p2align 3
.L842:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	REAL9DEC_Init
	b	.L831
	.p2align 3
.L841:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	REAL8DEC_Init
	b	.L831
	.p2align 3
.L840:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	AVSDEC_Init
	b	.L831
	.p2align 3
.L839:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	DIVX3DEC_Init
	b	.L831
	.p2align 3
.L838:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	MPEG2DEC_Init
	b	.L831
	.p2align 3
.L837:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	MPEG4DEC_Init
	b	.L831
	.p2align 3
.L836:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	VC1DEC_Init
	b	.L831
	.p2align 3
.L834:
	add	x0, x1, 294912
	add	x1, x1, 608
	add	x0, x0, 1240
	bl	H264DEC_Init
	b	.L831
	.p2align 3
.L849:
	ldr	x3, .LC510
	mov	w2, 5428
	ldr	x1, .LC511
	mov	w0, 0
	bl	dprint_vfmw
	b	.L831
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
	.xword	.L835
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
	tbnz	w0, #31, .L852
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L852
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L852
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L852
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L858
	cmp	w0, 2
	mov	w0, 0
	bne	.L854
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L852
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L852
.L857:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L852
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L859
.L852:
	ldr	x1, .LC514
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
.L854:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L859:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L858:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L857
	b	.L852
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
	cbz	w0, .L862
	mov	w4, 17
	add	w0, w5, 1
	cmp	w0, w4
	csel	w4, w0, w4, le
.L862:
	ldr	x1, .LC515
	sub	w0, w21, #27
	mov	w7, -2
	cmp	w0, 5
	csinv	w7, w7, wzr, ls
	ldr	x8, [x1, 128]
	cbz	x8, .L866
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
	cbnz	w0, .L866
	cmp	w21, 26
	beq	.L876
	mov	w1, 14920
	movk	w1, 0xc, lsl 16
	mov	w2, w1
.L867:
	ldr	w0, [x22, 2328]
	add	w3, w0, 16
	str	w3, [x20]
	ldr	w3, [x19, 168]
	cmp	w3, 1
	beq	.L868
	add	w0, w0, 307200
	add	w0, w0, 2576
	str	w0, [x20]
	ldr	w0, [x19, 56]
	add	w0, w0, 32768
	str	w0, [x20, 4]
.L869:
	str	w2, [x20, 8]
	ldr	w0, [x19, 44]
	cbnz	w0, .L877
	mov	w0, 61264
	movk	w0, 0x9, lsl 16
.L870:
	add	sp, x29, 0
	add	w1, w0, w1
	str	w1, [x20, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L877:
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
	beq	.L872
	mov	w0, 61264
	movk	w0, 0x9, lsl 16
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L870
	.p2align 3
.L866:
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
.L868:
	ldr	w0, [x19, 56]
	add	w0, w0, 339968
	add	w0, w0, 2576
	str	w0, [x20, 4]
	b	.L869
	.p2align 3
.L876:
	mov	w1, 728
	movk	w1, 0xb2, lsl 16
	mov	w2, w1
	b	.L867
	.p2align 3
.L872:
	mov	w5, 3992
	mov	w3, 2240
	and	x2, x2, 4294967295
	mov	w0, 61264
	smaddl	x4, w7, w5, x4
	movk	w0, 0x9, lsl 16
	smaddl	x6, w6, w3, x4
	cmp	x6, x2
	csel	x2, x6, x2, cs
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L870
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
	beq	.L879
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
	blt	.L886
	str	w0, [x19, 36]
	str	w1, [x19, 60]
.L879:
	mov	x0, x19
	bl	VCTRL_VarifyOption
	cbnz	w0, .L882
	mov	x2, x22
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetMemSize_onDecode
.L881:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L882:
	mov	w0, -1
	b	.L881
	.p2align 3
.L886:
	ldr	x1, .LC522
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L881
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
	cbz	w0, .L912
	ldr	w0, [x19, 112]
	cmp	w0, wzr
	cset	w21, ne
.L888:
	ldr	w20, [x19, 24]
	ldr	w22, [x19, 16]
	ldr	x23, [x19, 8]
	cbz	w20, .L889
	ldr	x0, .LC523
	ldr	x1, [x0, 120]
	cbz	x1, .L941
	mov	w0, 0
	blr	x1
	cbz	w21, .L892
.L893:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
.L889:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 88]
	ldr	w22, [x19, 80]
	ldr	x23, [x19, 72]
	cbz	w20, .L895
	ldr	x0, .LC523
	ldr	x1, [x0, 120]
	cbz	x1, .L942
	mov	w0, 0
	blr	x1
	cbz	w21, .L898
.L899:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
.L895:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 56]
	ldr	w22, [x19, 48]
	ldr	x23, [x19, 40]
	cbnz	w20, .L943
.L901:
	mov	x1, x23
	mov	w2, w20
	mov	w0, w22
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	w21, [x19, 144]
	ldr	w22, [x19, 136]
	ldr	x23, [x19, 128]
	cbnz	w21, .L944
.L904:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 216
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 240]
	ldr	w22, [x19, 232]
	ldr	x23, [x19, 224]
	cbnz	w21, .L945
.L905:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 208]
	ldr	w22, [x19, 200]
	ldr	x23, [x19, 192]
	cbnz	w21, .L946
.L906:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 152
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 176]
	ldr	w22, [x19, 168]
	ldr	x23, [x19, 160]
	cbnz	w21, .L947
.L907:
	mov	w2, w21
	mov	w0, w22
	mov	x1, x23
	add	x19, x19, 248
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 24]
	ldr	w21, [x19, 16]
	ldr	x22, [x19, 8]
	cbnz	w20, .L948
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC526
	ldr	w0, [x19, 584]
	cmp	w0, 1
	beq	.L949
.L909:
	ldr	w0, [x19, 588]
	cmp	w0, 1
	beq	.L950
.L910:
	ldr	w0, [x19, 592]
	add	x19, x19, 256
	cmp	w0, 1
	beq	.L951
.L911:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L943:
	mov	w0, 0
	bl	SM_CloseSCDDrv
	cbz	w21, .L902
.L903:
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, x2
	ldr	x3, [x3, 96]
	blr	x3
	b	.L901
	.p2align 3
.L944:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 120
	ldr	x3, [x3, 96]
	blr	x3
	b	.L904
	.p2align 3
.L948:
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
	bne	.L909
.L949:
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
	bne	.L910
	.p2align 2
.L950:
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
	bne	.L911
.L951:
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
.L947:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L907
	.p2align 3
.L946:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 184
	ldr	x3, [x3, 96]
	blr	x3
	b	.L906
	.p2align 3
.L945:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC524
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L905
	.p2align 3
.L941:
	ldr	x1, .LC525
	mov	w2, 5935
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L893
	.p2align 2
.L892:
	ldr	w0, [x19, 16]
	ldr	x1, [x19, 8]
	bl	MEM_ReleaseMemBlock
	b	.L893
	.p2align 3
.L942:
	ldr	x1, .LC525
	mov	w2, 5956
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L899
	.p2align 2
.L898:
	ldr	w0, [x19, 80]
	ldr	x1, [x19, 72]
	bl	MEM_ReleaseMemBlock
	b	.L899
	.p2align 3
.L912:
	mov	w21, 0
	b	.L888
	.p2align 3
.L902:
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_ReleaseMemBlock
	b	.L903
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
	cbnz	w0, .L953
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
	cbz	w0, .L983
	mov	w2, 53248
	ldr	x1, .LC530
	movk	w2, 0xf8c3, lsl 16
.L976:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC531
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
.L977:
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
.L956:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L983:
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
	cbnz	w0, .L957
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
	cbz	x0, .L959
	blr	x0
	cmp	w0, wzr
	mov	w2, w0
	ble	.L959
	mov	w21, 3
	mov	w4, 0
	mov	x3, x19
	mov	w1, 0
	add	x0, x29, 96
	str	w21, [x19, 28]
	bl	MEM_AllocMemBlock
	cbnz	w0, .L960
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
	cbz	x1, .L961
	add	x0, x29, 120
	blr	x1
	cbnz	w0, .L961
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
	mov	w2, 16384
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L962
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
	cbnz	w0, .L984
	ldr	w2, [x19, 56]
	ldr	x1, [x19, 40]
	ldr	w0, [x19, 48]
	bl	MEM_AddMemRecord
	ldr	w0, [x19, 48]
	mov	w2, 0
	ldr	w1, [x19, 56]
	bl	SM_OpenSCDDrv
	cbnz	w0, .L965
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
	cbnz	w0, .L985
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
	cbnz	w0, .L986
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
	cbnz	w0, .L987
	str	w24, [x22, 336]
	b	.L956
	.p2align 3
.L953:
	ldr	x1, .LC530
	mov	w2, -121438208
	b	.L976
	.p2align 3
.L959:
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
	b	.L956
.L957:
	ldr	x1, .LC530
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC531
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	b	.L977
.L961:
	ldr	x1, .LC539
.L979:
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
	b	.L956
.L985:
	ldr	x1, .LC550
	mov	w2, 127
.L978:
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
	b	.L956
.L986:
	ldr	x1, .LC550
	mov	w2, 136
	b	.L978
.L965:
	ldr	x1, .LC548
	mov	w2, 0
	b	.L978
.L984:
	ldr	x1, .LC546
	mov	w2, 0
	b	.L978
.L960:
	ldr	x1, .LC537
	b	.L979
.L962:
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
	b	.L956
.L987:
	ldr	x1, .LC550
	mov	w2, 181
	b	.L978
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
	cbnz	w19, .L1019
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
	cbz	x0, .L991
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1011
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1020
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
	bhi	.L996
.L1026:
	mov	w0, 5000
	mov	w1, -5000
	cmp	w2, w0
	csel	w0, w2, w0, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
.L992:
	str	w0, [x21, 3560]
.L994:
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
	cbz	x0, .L997
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L998
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1021
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
	bhi	.L1002
.L1025:
	mov	w19, 5000
	mov	w0, -5000
	cmp	w2, w19
	csel	w19, w2, w19, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
.L998:
	str	w19, [x21, 3564]
.L1000:
	ldr	x24, .LC574
	str	xzr, [x29, 72]
	ldr	w0, [x24, 248]
	cbz	w0, .L1003
	ldr	x2, .LC575
	and	w4, w0, 1
	ubfx	x3, x0, 1, 1
	ubfx	x1, x0, 2, 1
	strb	w4, [x24, 252]
	ubfx	x0, x0, 3, 1
	strb	w3, [x2, 92]
	strb	w1, [x24, 253]
	strb	w0, [x24, 254]
.L1004:
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
.L1008:
	str	w2, [x0], 4
	cmp	x1, x0
	bne	.L1008
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
	cbnz	w0, .L1019
	ldr	x2, [x20, 248]
	mov	w1, 1
	blr	x2
	ldr	x2, .LC582
	add	x0, x22, 272
	ldr	x1, .LC584
	ldr	x3, [x20, 384]
	blr	x3
	cbnz	w0, .L1022
	mov	w1, 1
	str	w1, [x22, 256]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1003:
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
	cbz	x0, .L1004
	ldr	x1, .LC562
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1023
	ldr	x1, .LC564
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1024
	ldr	x3, [x20, 168]
	mov	x1, 0
	mov	w2, 0
	blr	x3
	mov	w1, w0
	str	w0, [x24, 248]
.L1006:
	ldr	x2, .LC575
	and	w4, w1, 1
	ubfx	x3, x1, 1, 1
	ubfx	x0, x1, 2, 1
	strb	w4, [x24, 252]
	ubfx	x1, x1, 3, 1
	strb	w3, [x2, 92]
	strb	w0, [x24, 253]
	strb	w1, [x24, 254]
	b	.L1004
.L997:
	ldr	w2, [x21, 3564]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1025
.L1002:
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
	b	.L998
.L991:
	ldr	w2, [x21, 3560]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1026
.L996:
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
	b	.L992
.L1011:
	mov	w0, 0
	b	.L992
.L1023:
	ldr	w1, [x24, 248]
	b	.L1006
.L1022:
	mov	x0, x19
	bl	CloseDrivers
.L1019:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
.L1021:
	ldr	x2, .LC565
	mov	w3, 6846
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 48
	bl	dprint_vfmw
	b	.L1000
.L1020:
	ldr	x2, .LC565
	mov	w3, 6800
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L994
.L1024:
	ldr	x2, .LC565
	mov	w3, 6902
	ldr	x1, .LC567
	mov	w0, 22
	add	x2, x2, 72
	bl	dprint_vfmw
	b	.L1004
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
	beq	.L1032
	cmp	w19, w22
	mov	w19, w21
	blt	.L1033
.L1029:
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
.L1033:
	ldr	x1, .LC592
	mov	w0, 30
	mov	w19, 3
	bl	dprint_vfmw
	b	.L1029
	.p2align 3
.L1032:
	cmp	w20, w22
	mov	w19, w21
	ble	.L1029
	ldr	x1, .LC590
	mov	w0, 30
	mov	w19, 0
	bl	dprint_vfmw
	b	.L1029
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
	b	.L1037
	.p2align 3
.L1035:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1043
.L1037:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 294912
	add	x1, x1, 1240
	cbz	x2, .L1035
	cmp	x19, x1
	bne	.L1035
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1043:
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
.L1049:
	ldr	x4, [x6, x5, lsl 3]
	mov	w0, w5
	cbz	x4, .L1045
	add	x4, x4, 290816
	add	x1, x4, 1184
	add	x4, x4, 3488
	.p2align 2
.L1048:
	ldr	w2, [x1]
	cmp	w2, w19
	bhi	.L1046
	ldr	w3, [x1, -20]
	add	w2, w2, w3
	cmp	w19, w2
	bcc	.L1047
.L1046:
	add	x1, x1, 72
	cmp	x1, x4
	bne	.L1048
.L1045:
	add	x5, x5, 1
	cmp	x5, 32
	bne	.L1049
	mov	w0, -1
.L1047:
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
	beq	.L1081
	sub	w0, w1, #2
	cmp	w0, 1
	ccmp	w1, 6, 4, hi
	bne	.L1058
.L1069:
	add	x2, x19, 8
	add	x0, x4, 1160
	bl	IsNewpicSeg
	cbnz	w0, .L1059
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	ldr	x1, [x0, 672]
	beq	.L1079
	cmn	x1, #1
	beq	.L1061
.L1079:
	str	x1, [x0, 664]
.L1061:
	ldr	x3, [x0, 688]
	mov	x2, -1
	ldr	x1, [x0, 704]
	str	x2, [x0, 672]
	str	x3, [x0, 680]
	str	x1, [x0, 696]
	cbnz	x1, .L1062
	ldr	x1, [x19, 56]
	str	x1, [x0, 696]
.L1062:
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
	bne	.L1063
	ldr	x1, [x19, 32]
	.p2align 2
.L1080:
	str	x1, [x0, 672]
.L1065:
	ldr	x1, [x19, 48]
	str	x1, [x0, 688]
	ldr	x1, [x19, 56]
	str	x1, [x0, 704]
	ldr	w1, [x19, 64]
	str	w1, [x0, 724]
	ldr	w1, [x19, 68]
	str	w1, [x0, 728]
	ldr	w1, [x19, 72]
	str	w1, [x0, 732]
	ldr	w1, [x19, 76]
	str	w1, [x0, 740]
.L1064:
	ldr	x2, [x0, 680]
	mov	w0, 29
	ldr	x1, .LC601
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1081:
	add	x0, x4, 294912
	ldr	x0, [x0, 1240]
	ldrsb	w1, [x0, 556]
	cmp	w1, 1
	beq	.L1069
	.p2align 2
.L1058:
	ldr	x2, [x19, 32]
	cmn	x2, #1
	beq	.L1082
	str	x2, [x4, 664]
.L1068:
	ldr	x3, [x19, 48]
	mov	w0, 29
	str	x3, [x4, 680]
	ldr	x1, .LC603
	ldr	x5, [x19, 56]
	str	x5, [x4, 696]
	ldr	w5, [x19, 64]
	str	w5, [x4, 712]
	ldr	w5, [x19, 68]
	str	w5, [x4, 716]
	ldr	w5, [x19, 72]
	str	w5, [x4, 720]
	ldr	w5, [x19, 76]
	str	w5, [x4, 736]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1082:
	ldr	x2, [x4, 664]
	b	.L1068
	.p2align 3
.L1059:
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	beq	.L1064
.L1063:
	ldr	x1, [x19, 32]
	cmn	x1, #1
	bne	.L1080
	b	.L1065
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
	bhi	.L1084
	ldr	x1, .LC605
	ldr	w1, [x1, 2064]
	tbz	x1, 0, .L1085
.L1084:
	and	w1, w0, -17
	cmp	w1, 4
	ccmp	w0, 14, 4, ne
	beq	.L1085
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbnz	x0, .L1087
.L1085:
	mov	w0, 0
.L1086:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1087:
	mov	w0, -2
	b	.L1086
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
	bhi	.L1128
	ldr	x21, .LC608
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1129
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1130
	ldr	w1, [x0, 24]
	cbnz	w1, .L1131
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
	bls	.L1100
	str	w2, [x1, w19, sxtw 2]
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	beq	.L1132
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1110
	mov	w20, w0
.L1111:
	ldr	x1, [x21, w19, sxtw 3]
	add	x0, x1, 262144
	ldr	w3, [x0, 2032]
	cmp	w3, 1
	beq	.L1133
	cmp	w3, 3
	beq	.L1134
	add	x24, x1, 744
	ldrb	w0, [x24, 1]
	cbnz	w0, .L1104
	ldr	w0, [x1, 1496]
	cbz	w0, .L1135
.L1104:
	ldr	x2, [x24, 32]
	mov	w0, 29
	ldr	x3, [x24, 48]
	ldr	x1, .LC627
	bl	dprint_vfmw
	mov	x1, x24
	mov	w0, w19
	bl	DecChanProcessPts
	mov	w0, 3
	bl	CHECK_REC_POS_ENABLE
	cmp	w20, 1
	ccmp	w0, wzr, 4, eq
	bne	.L1136
.L1106:
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x24
	add	x2, x1, 294912
	ldr	w1, [x1, 600]
	add	x2, x2, 1240
	bl	DecodeStream
	mov	w0, 4
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1107
.L1108:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1100:
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	bne	.L1137
.L1117:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1137:
	mov	w0, w19
	mov	w20, -3
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1117
	mov	w20, 0
	b	.L1111
	.p2align 3
.L1132:
	ldr	x1, .LC617
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1107:
	ldr	x0, [x23]
	add	x22, x22, 520
	blr	x0
	mov	w1, w0
	ldr	x2, .LC629
	ldr	w0, [x22, w19, sxtw 2]
	ldr	w2, [x2]
	sub	w0, w1, w0
	cmp	w0, w2
	bls	.L1108
	mov	w0, w19
	str	w1, [x22, w19, sxtw 2]
	bl	VCTRL_GetDecParam
	cbz	x0, .L1108
	ldr	x0, .LC628
	lsl	w2, w19, 24
	add	w2, w2, 262144
	mov	w1, 6550
	add	x0, x0, 88
	mov	w20, 0
	bl	DBG_AddTrace
	b	.L1117
.L1133:
	ldr	x1, .LC621
	mov	w0, 31
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1110:
	ldr	x1, .LC619
	mov	w2, w19
	mov	w0, 23
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1130:
	ldr	x3, .LC610
	mov	w2, 6450
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1131:
	ldr	x3, .LC612
	mov	w2, 6451
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1135:
	add	x1, x1, 752
	mov	w0, w19
	bl	SM_ReadSegStream
	cbz	w0, .L1104
	cmp	w20, 1
	beq	.L1138
.L1105:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 1
	mov	w20, -4
	str	w1, [x0, 432]
	b	.L1117
	.p2align 3
.L1128:
	ldr	x3, .LC606
	mov	w2, 6448
	ldr	x1, .LC607
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1117
	.p2align 3
.L1136:
	ldr	x0, .LC628
	lsl	w2, w19, 24
	add	w2, w2, 196608
	mov	w1, 6532
	add	x0, x0, 88
	bl	DBG_AddTrace
	b	.L1106
.L1129:
	ldr	x3, .LC609
	mov	w2, 6449
	ldr	x1, .LC607
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1117
.L1134:
	ldr	w2, [x1, 1448]
	mov	w0, 31
	ldr	x1, .LC623
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1117
.L1138:
	ldr	x1, .LC625
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1105
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
	b	.L1142
	.p2align 3
.L1166:
	ldr	w1, [x1, 20]
	str	w1, [x2, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1165
.L1142:
	ldr	x1, [x22, x0, lsl 3]
	add	x2, x23, 648
	cbnz	x1, .L1166
	add	x1, x23, 648
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1142
.L1165:
	ldr	x24, .LC634
	mov	w20, -1
	.p2align 2
.L1143:
	ldr	w3, [x23, 648]
	add	x1, x23, 652
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L1144:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L1167
.L1146:
	ldr	w2, [x1]
	add	x1, x1, 4
	cmp	w3, w2
	bge	.L1144
	mov	w19, w0
	add	w0, w0, 1
	cmp	w0, 32
	mov	w3, w2
	bne	.L1146
.L1167:
	add	x2, x23, 648
	add	x0, x22, 256
	add	w1, w19, 1
	cmp	w3, wzr
	sxtw	x21, w19
	str	wzr, [x2, w19, sxtw 2]
	str	w1, [x0, 28]
	ble	.L1147
	ldr	x0, [x22, w19, sxtw 3]
	cbz	x0, .L1143
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1143
	ldr	w1, [x0, 76]
	cmp	w1, wzr
	ble	.L1149
	ldr	w0, [x0, 80]
	cbz	w0, .L1168
.L1149:
	mov	w21, 500
	b	.L1154
	.p2align 3
.L1152:
	subs	w21, w21, #1
	cbnz	w0, .L1143
	beq	.L1143
.L1154:
	mov	w0, w19
	bl	DecChanSyntax
	cmn	w0, #1
	mov	w20, w0
	bne	.L1152
	ldr	x4, [x23, 256]
	cbz	x4, .L1153
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w19
	blr	x4
.L1153:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
.L1168:
	add	x1, x29, 72
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L1169
.L1150:
	ldr	x20, [x22, x21, lsl 3]
	ldr	w1, [x29, 84]
	ldr	w2, [x20, 76]
	ldr	w0, [x20, 616]
	bl	GetNextDecodeMode
	str	w0, [x20, 616]
	ldr	x1, [x22, x21, lsl 3]
	ldr	w0, [x1, 616]
	cbz	w0, .L1151
	str	wzr, [x1, 608]
	str	wzr, [x1, 612]
	b	.L1149
.L1147:
	str	wzr, [x0, 28]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
.L1151:
	ldr	w0, [x1, 72]
	str	w0, [x1, 608]
	str	w0, [x1, 612]
	b	.L1149
.L1169:
	ldr	x3, [x24, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	blr	x3
	b	.L1150
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
	beq	.L1179
.L1171:
	ldr	w0, [x20, 1124]
	mov	w1, 100
	str	w1, [x20, 280]
	cmp	w0, wzr
	ldr	x21, .LC638
	ble	.L1172
	ldr	x1, [x21, 240]
	blr	x1
.L1172:
	ldr	x1, [x21, 24]
	mov	w0, 0
	mov	w22, 0
	blr	x1
	bl	SM_Wakeup
	ldr	w0, [x20, 1120]
	mov	w1, 101
	str	w1, [x20, 280]
	cbz	w0, .L1180
.L1173:
	mov	w0, 102
	mov	w19, 0
	str	w0, [x20, 280]
	bl	VDMDRV_WakeUpVdm
	.p2align 2
.L1174:
	mov	w0, w19
	mov	w1, 0
	add	w19, w19, 1
	bl	DeleteRawPacketInBuffer
	cmp	w19, 32
	bne	.L1174
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
.L1180:
	bl	DecSyntax
	mov	w22, w0
	b	.L1173
.L1179:
	mov	w0, 11
	bl	VCTRL_RecordPosTime
	strb	wzr, [x20, 2816]
	b	.L1171
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
.L1182:
.L1189:
	mov	x1, x25
	mov	w0, 2
	str	wzr, [x20, 280]
	bl	dprint_vfmw
	str	w21, [x20, 260]
	ldr	w0, [x20, 264]
	cmp	w0, 2
	bne	.L1204
	b	.L1187
	.p2align 3
.L1206:
	str	w21, [x20, 280]
	bl	VCTRL_RunProcess
	mov	x1, x22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x20, 264]
	cmp	w0, 2
	beq	.L1187
.L1204:
	cmp	w0, 3
	bne	.L1206
.L1185:
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
.L1187:
	mov	w2, 4
	mov	x1, x26
	mov	w0, 2
	str	w2, [x20, 280]
	mov	w27, 5
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x20, 260]
	b	.L1184
	.p2align 3
.L1207:
	ldr	x1, [x24, 240]
	blr	x1
.L1184:
	mov	x1, x23
	mov	w0, 22
	str	w27, [x20, 280]
	bl	dprint_vfmw
	ldr	w1, [x20, 264]
	mov	w0, 10
	cmp	w1, 1
	beq	.L1189
	cmp	w1, 3
	bne	.L1207
	b	.L1185
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
	cbz	x0, .L1226
	ldr	w1, [x0, 600]
	cmp	w1, 20
	bls	.L1227
.L1226:
	mov	x0, 0
.L1209:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1227:
	ldr	x2, .LC653
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1211
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1211:
	.section	.rodata
	.align	0
	.align	2
.L1211:
	.byte	(.L1224 - .Lrtx1211) / 4
	.byte	(.L1212 - .Lrtx1211) / 4
	.byte	(.L1213 - .Lrtx1211) / 4
	.byte	(.L1214 - .Lrtx1211) / 4
	.byte	(.L1226 - .Lrtx1211) / 4
	.byte	(.L1215 - .Lrtx1211) / 4
	.byte	(.L1216 - .Lrtx1211) / 4
	.byte	(.L1226 - .Lrtx1211) / 4
	.byte	(.L1217 - .Lrtx1211) / 4
	.byte	(.L1218 - .Lrtx1211) / 4
	.byte	(.L1219 - .Lrtx1211) / 4
	.byte	(.L1219 - .Lrtx1211) / 4
	.byte	(.L1219 - .Lrtx1211) / 4
	.byte	(.L1220 - .Lrtx1211) / 4
	.byte	(.L1226 - .Lrtx1211) / 4
	.byte	(.L1221 - .Lrtx1211) / 4
	.byte	(.L1222 - .Lrtx1211) / 4
	.byte	(.L1223 - .Lrtx1211) / 4
	.byte	(.L1226 - .Lrtx1211) / 4
	.byte	(.L1226 - .Lrtx1211) / 4
	.byte	(.L1224 - .Lrtx1211) / 4
	.text
	.p2align 3
.L1224:
	add	x0, x0, 294912
	ldr	x19, [sp, 16]
	add	x0, x0, 1248
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1222:
	add	x0, x0, 299008
	add	x0, x0, 3160
	b	.L1209
	.p2align 3
.L1221:
	add	x0, x0, 294912
	add	x0, x0, 2152
	b	.L1209
	.p2align 3
.L1220:
	add	x0, x0, 303104
	add	x0, x0, 1280
	b	.L1209
	.p2align 3
.L1219:
	add	x0, x0, 307200
	add	x0, x0, 1712
	b	.L1209
	.p2align 3
.L1223:
	add	x0, x0, 569344
	add	x0, x0, 2656
	b	.L1209
	.p2align 3
.L1212:
	add	x0, x0, 348160
	add	x0, x0, 1464
	b	.L1209
	.p2align 3
.L1214:
	add	x0, x0, 380928
	add	x0, x0, 3488
	b	.L1209
	.p2align 3
.L1213:
	add	x0, x0, 315392
	add	x0, x0, 3448
	b	.L1209
	.p2align 3
.L1218:
	add	x0, x0, 348160
	add	x0, x0, 2424
	b	.L1209
	.p2align 3
.L1217:
	add	x0, x0, 348160
	add	x0, x0, 2448
	b	.L1209
	.p2align 3
.L1216:
	add	x0, x0, 311296
	add	x0, x0, 1120
	b	.L1209
	.p2align 3
.L1215:
	add	x0, x0, 335872
	add	x0, x0, 2392
	b	.L1209
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	3
.LC652:
	.xword	.LANCHOR0
	.align	3
.LC653:
	.xword	.L1211
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
	bhi	.L1244
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1238
	add	x2, x29, 48
	add	x1, x29, 40
	str	wzr, [x29, 40]
	str	wzr, [x2, -4]!
	bl	GetQueueImgNum
	ldr	w2, [x29, 40]
	mov	w0, -1
	cbz	w2, .L1230
	cmp	w2, 32
	bhi	.L1245
.L1232:
	ldr	x1, .LC658
	ldrh	w0, [x20, 4]
	ldr	x5, [x1, w19, sxtw 3]
	and	x0, x0, 63
	add	x0, x0, 2
	add	x6, x5, 294912
	ldr	x4, [x20, x0, lsl 3]
	ldr	w3, [x6, 1168]
	cmp	w3, 32
	bhi	.L1233
	mov	w1, 1
	b	.L1235
	.p2align 3
.L1236:
	ldrh	w0, [x20, 4]
	cmp	w3, 33
	add	w0, w0, w1
	add	w1, w1, 1
	and	x0, x0, 63
	add	x0, x0, 2
	ldr	x4, [x20, x0, lsl 3]
	beq	.L1233
.L1235:
	ubfiz	x0, x3, 4, 32
	ldr	w4, [x4, 20]
	add	x0, x5, x0
	add	w3, w3, 1
	add	x0, x0, 294912
	cmp	w1, w2
	str	wzr, [x0, 640]
	str	w4, [x0, 644]
	str	xzr, [x0, 648]
	str	w3, [x6, 1168]
	bcc	.L1236
	mov	w0, 0
.L1230:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1233:
	ldr	x1, .LC660
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1230
	.p2align 3
.L1245:
	ldr	x1, .LC657
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 40]
	cbnz	w2, .L1232
	mov	w0, 0
	b	.L1230
.L1238:
	mov	w0, -1
	b	.L1230
.L1244:
	ldr	x3, .LC654
	mov	w2, 3489
	ldr	x1, .LC655
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1230
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
	bhi	.L1263
	cbz	x19, .L1264
	mov	w0, w22
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1256
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
	cbnz	w2, .L1265
	ldr	x6, .LC667
	ldr	x4, [x6, w22, sxtw 3]
	add	x0, x4, 294912
	ldr	w0, [x0, 1168]
	cbz	w0, .L1254
	mov	w2, 0
	sxtw	x0, w22
	.p2align 2
.L1255:
	sxtw	x3, w2
	add	w2, w2, 1
	add	x1, x3, 16384
	lsl	x3, x3, 4
	add	x1, x1, 2088
	add	x5, x19, x3
	lsl	x1, x1, 4
	sxth	w2, w2
	add	x4, x4, x1
	ldr	w4, [x4, 4]
	str	w4, [x5, 4]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, x1
	ldr	x1, [x1, 8]
	str	x1, [x5, 8]
	str	wzr, [x19, x3]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, 294912
	ldr	w1, [x1, 1168]
	cmp	w2, w1
	bcc	.L1255
	str	w1, [x19, 528]
	b	.L1254
	.p2align 3
.L1265:
	cmp	w2, 32
	bhi	.L1266
.L1251:
	mov	w0, 0
	.p2align 2
.L1253:
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
	bhi	.L1253
	uxth	w1, w2
.L1252:
	ldrh	w0, [x20, 4]
	add	w0, w1, w0
	and	w0, w0, 63
	strh	w0, [x20, 4]
	str	w2, [x19, 528]
.L1254:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, 0
.L1248:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1266:
	ldr	x1, .LC666
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 72]
	cbnz	w2, .L1251
	mov	w2, 0
	mov	w1, 0
	b	.L1252
.L1256:
	mov	w0, -1
	b	.L1248
.L1263:
	ldr	x3, .LC661
	mov	w2, 3605
	ldr	x1, .LC662
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1248
.L1264:
	ldr	x3, .LC664
	mov	w2, 3606
	ldr	x1, .LC662
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1248
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
	cbz	x0, .L1276
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	cbz	x0, .L1270
	mov	x2, x23
	mov	x1, x21
	bl	GetQueueImgNum
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w3, [x0, 600]
	cbz	w3, .L1277
	cmp	w3, 16
	beq	.L1278
	cmp	w3, 17
	beq	.L1279
	cmp	w3, 15
	beq	.L1280
	cmp	w3, 18
	beq	.L1281
	mov	w0, 2
	str	w0, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1277:
	add	x0, x0, 323584
	ldr	w0, [x0, 848]
	str	w0, [x22]
.L1267:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1270:
	str	wzr, [x23]
	str	wzr, [x21]
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1278:
	add	x0, x0, 294912
	ldr	w0, [x0, 4000]
	str	w0, [x22]
	b	.L1267
	.p2align 3
.L1279:
	mov	w0, 9
	str	w0, [x22]
	b	.L1267
	.p2align 3
.L1280:
	add	x0, x0, 11419648
	ldr	w0, [x0, 2032]
	str	w0, [x22]
	b	.L1267
	.p2align 3
.L1281:
	ldr	x2, .LC671
	mov	w0, 32
	ldr	x1, .LC673
	add	x2, x2, 104
	bl	dprint_vfmw
	b	.L1267
	.p2align 3
.L1276:
	ldr	x3, .LC669
	mov	w2, 6662
	ldr	x1, .LC670
	bl	dprint_vfmw
	b	.L1267
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
	.align	3
.LC671:
	.xword	.LANCHOR4
	.align	3
.LC673:
	.xword	.LC672
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
	bhi	.L1292
	cbz	x19, .L1293
	ldr	x21, .LC681
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L1294
	ldr	x0, .LC684
	mov	x2, 100
	mov	w1, 0
	str	wzr, [x29, 68]
	stp	wzr, wzr, [x29, 60]
	ldr	x3, [x0, 96]
	mov	x0, x19
	blr	x3
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1176]
	str	w0, [x19, 32]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1180]
	str	w0, [x19, 36]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1184]
	str	w0, [x19, 44]
	ldr	x5, [x21, w20, sxtw 3]
	add	x0, x5, 262144
	ldrsb	w0, [x0, 2003]
	cmp	w0, wzr
	ble	.L1290
	mov	x2, 23994
	sub	w4, w0, #1
	mov	w3, 88
	movk	x2, 0x4, lsl 16
	add	x0, x5, 282624
	mov	w1, 0
	umaddl	x2, w4, w3, x2
	add	x0, x0, 3426
	add	x3, x5, x2
	.p2align 2
.L1289:
	ldrsb	w2, [x0], 88
	cmp	w2, 3
	csinc	w1, w1, w1, ne
	cmp	x0, x3
	bne	.L1289
.L1287:
	str	w1, [x19, 84]
	add	x3, x29, 68
	add	x2, x29, 64
	mov	w0, w20
	ldr	x4, [x21, w20, sxtw 3]
	add	x1, x29, 60
	sxtw	x22, w20
	add	x4, x4, 262144
	ldrsb	w4, [x4, 2003]
	str	w4, [x19, 92]
	bl	VCTRL_GetChanImgNum
	ldr	x2, .LC685
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
	mov	x0, 46296
	ldr	x1, [x21, w20, sxtw 3]
	movk	x0, 0x4, lsl 16
	add	x0, x1, x0
	ldrb	w0, [x0, 3600]
	and	w0, w0, 1
	str	w0, [x19, 88]
.L1282:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1292:
	ldr	x3, .LC677
	mov	w2, 1456
	ldr	x1, .LC678
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1294:
	ldr	x3, .LC683
	mov	w2, 1459
	ldr	x1, .LC678
	bl	dprint_vfmw
	b	.L1282
.L1290:
	mov	w1, 0
	b	.L1287
.L1293:
	ldr	x3, .LC680
	mov	w2, 1458
	ldr	x1, .LC678
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1282
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	3
.LC677:
	.xword	.LC676
	.align	3
.LC678:
	.xword	.LC5
	.align	3
.LC680:
	.xword	.LC679
	.align	3
.LC681:
	.xword	.LANCHOR0
	.align	3
.LC683:
	.xword	.LC682
	.align	3
.LC684:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC685:
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
	bhi	.L1299
	ldr	x0, .LC689
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1300
	ldr	w0, [x0, 1292]
.L1297:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1299:
	ldr	x3, .LC687
	mov	w2, 6726
	ldr	x1, .LC688
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1297
.L1300:
	ldr	x3, .LC690
	mov	w2, 6727
	ldr	x1, .LC688
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1297
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	3
.LC687:
	.xword	.LC237
	.align	3
.LC688:
	.xword	.LC5
	.align	3
.LC689:
	.xword	.LANCHOR0
	.align	3
.LC690:
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
	bhi	.L1305
	ldr	x0, .LC693
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1306
	ldr	w0, [x0, 1296]
.L1303:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1305:
	ldr	x3, .LC691
	mov	w2, 6734
	ldr	x1, .LC692
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1303
.L1306:
	ldr	x3, .LC694
	mov	w2, 6735
	ldr	x1, .LC692
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1303
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	3
.LC691:
	.xword	.LC237
	.align	3
.LC692:
	.xword	.LC5
	.align	3
.LC693:
	.xword	.LANCHOR0
	.align	3
.LC694:
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
	bhi	.L1311
	ldr	x0, .LC697
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1310
	ldr	w0, [x0, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1311:
	ldr	x3, .LC695
	mov	w2, 6742
	ldr	x1, .LC696
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1310:
	mov	w0, 33
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	3
.LC695:
	.xword	.LC237
	.align	3
.LC696:
	.xword	.LC5
	.align	3
.LC697:
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
	ldr	x20, .LC698
	add	w0, w21, 4096
	mov	w1, 10000
	add	w0, w0, 904
	mov	w2, w21
	cmp	w0, w1
	str	w21, [x20, 3560]
	bhi	.L1317
.L1313:
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
	bhi	.L1318
.L1314:
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
.L1317:
	ldr	x1, .LC700
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x20, 3560]
	b	.L1313
	.p2align 3
.L1318:
	ldr	x1, .LC702
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x20, 3564]
	b	.L1314
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	3
.LC698:
	.xword	.LANCHOR3
	.align	3
.LC700:
	.xword	.LC699
	.align	3
.LC702:
	.xword	.LC701
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
	cbz	w19, .L1323
	ldr	x3, .LC705
	mov	w1, 1
	ldr	x0, .LC703
	add	x3, x3, 128
	b	.L1321
	.p2align 3
.L1322:
	ldr	w4, [x3, x4]
	add	w1, w1, 1
	ubfiz	x2, x1, 4, 32
	cmp	w4, w19
	add	x2, x3, x2
	beq	.L1320
	ldr	x0, [x2, 8]
.L1321:
	ubfiz	x4, x1, 4, 32
	cbnz	x0, .L1322
.L1320:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1323:
	ldr	x0, .LC704
	b	.L1320
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	3
.LC703:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC704:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC705:
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
	cbz	x20, .L1334
	cbz	w19, .L1331
	ldr	x4, .LC709
	mov	w0, 1
	ldr	x5, .LC707
	add	x4, x4, 128
	b	.L1327
	.p2align 3
.L1332:
	ldr	w6, [x4, x6]
	add	w0, w0, 1
	ubfiz	x3, x0, 4, 32
	cmp	w19, w6
	add	x3, x4, x3
	beq	.L1326
	ldr	x5, [x3, 8]
.L1327:
	ubfiz	x6, x0, 4, 32
	cbnz	x5, .L1332
	ldr	x1, .LC711
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
.L1334:
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1331:
	ldr	x5, .LC708
.L1326:
	mov	x0, x20
	blr	x5
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	3
.LC707:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC708:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC709:
	.xword	.LANCHOR4
	.align	3
.LC711:
	.xword	.LC710
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
	bhi	.L1339
	ldr	x0, .LC715
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1338
	ldr	w0, [x0, 436]
.L1337:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1339:
	ldr	x3, .LC713
	mov	w2, 7981
	ldr	x1, .LC714
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1337
.L1338:
	mov	w0, -1
	b	.L1337
	.size	VCTRL_GetLastFrameIdPlus2, .-VCTRL_GetLastFrameIdPlus2
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
	bhi	.L1346
	ldr	x0, .LC718
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1340
	str	w20, [x0, 436]
.L1340:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1346:
	ldr	x3, .LC716
	mov	w2, 7993
	ldr	x1, .LC717
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameIdPlus2, .-VCTRL_SetLastFrameIdPlus2
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
	bhi	.L1353
	ldr	x0, .LC721
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1347
	str	w20, [x0, 440]
.L1347:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1353:
	ldr	x3, .LC719
	mov	w2, 8005
	ldr	x1, .LC720
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	3
.LC719:
	.xword	.LC237
	.align	3
.LC720:
	.xword	.LC5
	.align	3
.LC721:
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
	cbz	w20, .L1361
	cmp	w20, 1
	mov	w0, 3
	mov	w1, 4
	csel	w0, w0, w1, eq
	cmp	w19, 31
	bhi	.L1368
.L1358:
	ldr	x21, .LC724
	ldr	x1, [x21, w19, sxtw 3]
	cbz	x1, .L1359
	str	w0, [x1, 440]
.L1359:
	ldr	x0, .LC725
	ldr	x4, [x0, 256]
	cbz	x4, .L1360
	add	x2, x29, 64
	mov	w3, 4
	mov	w1, 115
	mov	w0, w19
	str	w20, [x2, -8]!
	blr	x4
.L1360:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w20
	ldr	x1, .LC727
	mov	w2, w19
	mov	w0, 1
	ldr	w4, [x4, 440]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1361:
	cmp	w19, 31
	mov	w0, 2
	bls	.L1358
.L1368:
	ldr	x3, .LC722
	mov	w2, 8005
	ldr	x1, .LC723
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, .LC724
	b	.L1359
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	3
.LC722:
	.xword	.LC237
	.align	3
.LC723:
	.xword	.LC5
	.align	3
.LC724:
	.xword	.LANCHOR0
	.align	3
.LC725:
	.xword	.LANCHOR5
	.align	3
.LC727:
	.xword	.LC726
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
	ldr	x0, .LC728
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 294912
	ldr	w1, [x0, 1232]
	cmp	w1, 17
	bls	.L1394
.L1389:
	mov	w19, -1
.L1386:
	mov	w0, w20
	mov	w1, 1
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC731
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1394:
	ldr	x2, .LC729
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1372
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1372:
	.section	.rodata
	.align	0
	.align	2
.L1372:
	.byte	(.L1371 - .Lrtx1372) / 4
	.byte	(.L1373 - .Lrtx1372) / 4
	.byte	(.L1374 - .Lrtx1372) / 4
	.byte	(.L1375 - .Lrtx1372) / 4
	.byte	(.L1389 - .Lrtx1372) / 4
	.byte	(.L1376 - .Lrtx1372) / 4
	.byte	(.L1377 - .Lrtx1372) / 4
	.byte	(.L1389 - .Lrtx1372) / 4
	.byte	(.L1378 - .Lrtx1372) / 4
	.byte	(.L1379 - .Lrtx1372) / 4
	.byte	(.L1380 - .Lrtx1372) / 4
	.byte	(.L1380 - .Lrtx1372) / 4
	.byte	(.L1380 - .Lrtx1372) / 4
	.byte	(.L1381 - .Lrtx1372) / 4
	.byte	(.L1389 - .Lrtx1372) / 4
	.byte	(.L1382 - .Lrtx1372) / 4
	.byte	(.L1383 - .Lrtx1372) / 4
	.byte	(.L1384 - .Lrtx1372) / 4
	.text
	.p2align 3
.L1371:
	add	x0, x0, 1240
	bl	H264DEC_GetRemainImg
	mov	w19, w0
	.p2align 2
.L1370:
	cmn	w19, #1
	beq	.L1386
	cbnz	w19, .L1395
	mov	w0, w20
	mov	w1, 0
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC733
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1373:
	add	x0, x0, 1240
	bl	VC1DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1374:
	add	x0, x0, 1240
	bl	MPEG4DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1375:
	add	x0, x0, 1240
	bl	MPEG2DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1376:
	add	x0, x0, 1240
	bl	DIVX3DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1377:
	add	x0, x0, 1240
	bl	AVSDEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1378:
	add	x0, x0, 1240
	bl	REAL8DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1379:
	add	x0, x0, 1240
	bl	REAL9DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1380:
	add	x0, x0, 1240
	bl	VP6DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1381:
	add	x0, x0, 1240
	bl	VP8DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1382:
	add	x0, x0, 1240
	bl	MVC_DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1383:
	add	x0, x0, 1240
	bl	HEVCDEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1384:
	add	x0, x0, 1240
	bl	VP9DEC_GetRemainImg
	mov	w19, w0
	b	.L1370
	.p2align 3
.L1395:
	mov	w1, w19
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC735
	sub	w2, w19, #2
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	3
.LC728:
	.xword	.LANCHOR0
	.align	3
.LC729:
	.xword	.L1372
	.align	3
.LC731:
	.xword	.LC730
	.align	3
.LC733:
	.xword	.LC732
	.align	3
.LC735:
	.xword	.LC734
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
	ldr	x21, .LC736
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1430
	ldr	w1, [x0, 600]
	ldr	w24, [x0, 1232]
	cmp	w1, 17
	bls	.L1431
.L1396:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1431:
	ldr	x2, .LC739
	ldrh	w1, [x2,w1,uxtw #1]
	adr	x2, .Lrtx1400
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx1400:
	.section	.rodata
	.align	0
	.align	2
.L1400:
	.2byte	(.L1399 - .Lrtx1400) / 4
	.2byte	(.L1401 - .Lrtx1400) / 4
	.2byte	(.L1402 - .Lrtx1400) / 4
	.2byte	(.L1403 - .Lrtx1400) / 4
	.2byte	(.L1396 - .Lrtx1400) / 4
	.2byte	(.L1404 - .Lrtx1400) / 4
	.2byte	(.L1405 - .Lrtx1400) / 4
	.2byte	(.L1396 - .Lrtx1400) / 4
	.2byte	(.L1406 - .Lrtx1400) / 4
	.2byte	(.L1407 - .Lrtx1400) / 4
	.2byte	(.L1408 - .Lrtx1400) / 4
	.2byte	(.L1408 - .Lrtx1400) / 4
	.2byte	(.L1408 - .Lrtx1400) / 4
	.2byte	(.L1409 - .Lrtx1400) / 4
	.2byte	(.L1396 - .Lrtx1400) / 4
	.2byte	(.L1410 - .Lrtx1400) / 4
	.2byte	(.L1411 - .Lrtx1400) / 4
	.2byte	(.L1412 - .Lrtx1400) / 4
	.text
	.p2align 3
.L1412:
	add	x0, x0, 294912
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1240
	bl	VP9DEC_VDMPostProc
	cmp	w24, 1
	beq	.L1396
.L1428:
	ldr	x0, [x21, w19, sxtw 3]
.L1429:
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1411:
	add	x0, x0, 294912
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1240
	bl	HEVCDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	ldrb	w0, [x0, 1249]
	cmp	w0, 1
	beq	.L1432
.L1415:
	cmp	w24, 1
	beq	.L1396
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 3680]
	b	.L1396
	.p2align 3
.L1410:
	add	x0, x0, 294912
	mov	w1, w20
	mov	w2, 1
	add	x0, x0, 1240
	bl	MVC_DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	ldrb	w1, [x0, 1241]
	cmp	w1, 1
	beq	.L1433
	str	xzr, [x0, 1472]
	b	.L1396
	.p2align 3
.L1409:
	add	x0, x0, 294912
	mov	w1, w20
	add	x0, x0, 1240
	bl	VP8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
	b	.L1396
	.p2align 3
.L1408:
	add	x0, x0, 294912
	mov	w1, w20
	add	x0, x0, 1240
	bl	VP6DEC_VDMPostProc
	b	.L1428
	.p2align 3
.L1407:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 294912
	add	x0, x0, 1240
	bl	REAL9DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
	b	.L1396
	.p2align 3
.L1406:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 294912
	add	x0, x0, 1240
	bl	REAL8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
	b	.L1396
	.p2align 3
.L1405:
	add	x0, x0, 294912
	mov	w1, w20
	add	x0, x0, 1240
	bl	AVSDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	ldrb	w1, [x0, 1240]
	cmp	w1, 1
	beq	.L1434
	str	xzr, [x0, 1264]
	b	.L1396
	.p2align 3
.L1404:
	mov	w0, w22
	bl	VDMDRV_GetSwitchRounding
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 294912
	add	x0, x0, 1240
	bl	DIVX3DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 1248]
	b	.L1396
	.p2align 3
.L1403:
	add	x0, x0, 294912
	mov	w1, w20
	add	x0, x0, 1240
	bl	MPEG2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 385024
	ldrb	w1, [x1, 18]
	cmp	w1, 1
	bne	.L1429
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 385024
	strb	wzr, [x1, 18]
	b	.L1429
	.p2align 3
.L1402:
	add	x0, x0, 294912
	mov	w1, w20
	mov	x2, x23
	add	x0, x0, 1240
	bl	MPEG4DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 315392
	ldrb	w1, [x1, 4092]
	cmp	w1, 1
	beq	.L1435
.L1418:
	add	x0, x0, 294912
	str	xzr, [x0, 2280]
	b	.L1396
	.p2align 3
.L1401:
	add	x0, x0, 294912
	mov	w1, w20
	add	x0, x0, 1240
	bl	VC1DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 307200
	ldrb	w1, [x1, 3751]
	cmp	w1, 1
	bne	.L1429
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 307200
	strb	wzr, [x1, 3751]
	b	.L1429
	.p2align 3
.L1399:
	add	x0, x0, 294912
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1240
	bl	H264DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 307200
	ldrb	w0, [x0, 3880]
	cmp	w0, 1
	beq	.L1436
.L1413:
	cmp	w24, 1
	beq	.L1396
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	str	xzr, [x0, 1856]
	b	.L1396
	.p2align 3
.L1434:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	strb	wzr, [x0, 1240]
	str	xzr, [x0, 1264]
	b	.L1396
	.p2align 3
.L1433:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	strb	wzr, [x0, 1241]
	str	xzr, [x0, 1472]
	b	.L1396
	.p2align 3
.L1430:
	ldr	x3, .LC737
	mov	w2, 4566
	ldr	x1, .LC738
	bl	dprint_vfmw
	b	.L1396
	.p2align 3
.L1435:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 315392
	strb	wzr, [x1, 4092]
	b	.L1418
.L1436:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 307200
	strb	wzr, [x0, 3880]
	b	.L1413
.L1432:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	strb	wzr, [x0, 1249]
	b	.L1415
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	3
.LC736:
	.xword	.LANCHOR0
	.align	3
.LC737:
	.xword	.LC8
	.align	3
.LC738:
	.xword	.LC5
	.align	3
.LC739:
	.xword	.L1400
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
	bhi	.L1445
	ldr	x0, .LC742
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1446
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L1441
	ldr	x3, .LC744
	mov	w2, 4757
	ldr	x1, .LC741
	mov	w0, 0
	bl	dprint_vfmw
.L1437:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1441:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L1437
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
.L1445:
	ldr	x3, .LC740
	mov	w2, 4755
	ldr	x1, .LC741
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1446:
	ldr	x3, .LC743
	mov	w2, 4756
	ldr	x1, .LC741
	bl	dprint_vfmw
	b	.L1437
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	3
.LC740:
	.xword	.LC443
	.align	3
.LC741:
	.xword	.LC5
	.align	3
.LC742:
	.xword	.LANCHOR0
	.align	3
.LC743:
	.xword	.LC384
	.align	3
.LC744:
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
	bls	.L1466
	ldr	x1, .LC747
	mov	w3, w19
	mov	w2, 8712
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 13
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1466:
	ldr	x0, .LC745
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1451
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1451:
	.section	.rodata
	.align	0
	.align	2
.L1451:
	.byte	(.L1450 - .Lrtx1451) / 4
	.byte	(.L1452 - .Lrtx1451) / 4
	.byte	(.L1453 - .Lrtx1451) / 4
	.byte	(.L1454 - .Lrtx1451) / 4
	.byte	(.L1455 - .Lrtx1451) / 4
	.byte	(.L1456 - .Lrtx1451) / 4
	.byte	(.L1457 - .Lrtx1451) / 4
	.text
	.p2align 3
.L1456:
	cmp	w20, 1
	mov	w1, 12
	mov	w0, 13
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1457:
	cmp	w20, 1
	mov	w0, 7
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1450:
	cmp	w20, 1
	mov	w0, 6
	csel	w0, wzr, w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1452:
	cmp	w20, 1
	mov	w1, 8
	mov	w0, 2
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1453:
	cmp	w20, 1
	mov	w1, 10
	mov	w0, 4
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1454:
	cmp	w20, 1
	mov	w1, 9
	mov	w0, 3
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1455:
	cmp	w20, 1
	mov	w1, 11
	mov	w0, 5
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	3
.LC745:
	.xword	.L1451
	.align	3
.LC747:
	.xword	.LC746
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
	beq	.L1476
	ldr	w0, [x20, 4]
	cmp	w0, 1
	beq	.L1470
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_ClearLogicFs
	mov	w0, 0
.L1469:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1470:
	ldr	w0, [x20, 48]
	bl	MEM_Phy2Vir
	cbz	x0, .L1477
.L1471:
	mov	w1, w22
	mov	w0, w21
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1478
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
	ldr	x4, .LC754
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
	beq	.L1479
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
	ldr	x2, .LC757
	mov	x4, x19
	mov	w1, w24
	mov	w0, w21
	ldr	x2, [x2, w21, sxtw 3]
	add	x2, x2, 294912
	add	x3, x2, 1248
	add	x2, x2, 1240
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w0, 0
	beq	.L1469
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
	b	.L1469
	.p2align 3
.L1477:
	ldr	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1471
	ldr	x1, .LC751
	mov	w0, 0
	ldr	w2, [x20, 48]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1469
.L1476:
	ldr	x1, .LC749
	mov	w0, 0
	ldr	w2, [x20, 40]
	bl	dprint_vfmw
	mov	w0, w22
	b	.L1469
.L1479:
	ldr	x1, .LC756
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1469
.L1478:
	ldr	x1, .LC753
	mov	w2, 5249
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1469
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
	.align	3
.LC749:
	.xword	.LC748
	.align	3
.LC751:
	.xword	.LC750
	.align	3
.LC753:
	.xword	.LC752
	.align	3
.LC754:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC756:
	.xword	.LC755
	.align	3
.LC757:
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
	ldr	x20, .LC758
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1488
	cbz	x21, .L1489
	ldr	w2, [x0, 600]
	cmp	w2, 20
	bne	.L1490
	ldr	x3, .LC765
	mov	x1, x21
	mov	x2, 72
	add	x0, x0, 528
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 528
	bl	VDH_PutUsrdecFrame
	cbnz	w0, .L1491
.L1482:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1490:
	ldr	x1, .LC764
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1482
	.p2align 3
.L1491:
	ldr	x1, .LC767
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1482
.L1489:
	ldr	x3, .LC762
	mov	w2, 5402
	ldr	x1, .LC760
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1482
.L1488:
	ldr	x3, .LC759
	mov	w2, 5401
	ldr	x1, .LC760
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1482
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	3
.LC758:
	.xword	.LANCHOR0
	.align	3
.LC759:
	.xword	.LC8
	.align	3
.LC760:
	.xword	.LC5
	.align	3
.LC762:
	.xword	.LC761
	.align	3
.LC764:
	.xword	.LC763
	.align	3
.LC765:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC767:
	.xword	.LC766
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
	beq	.L1494
	mov	w0, w19
	bl	VCTRL_CanBeDecodedByHardWare.part.19
.L1494:
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
	beq	.L1499
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1499:
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
	bhi	.L1551
	ldr	x20, .LC770
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L1552
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1504
	ldr	w0, [x0, 600]
	cmp	w0, 21
	beq	.L1504
	cmp	w0, 7
	ccmp	w0, 4, 4, ne
	beq	.L1500
	bl	VCTRL_CanBeDecodedByHardWare.part.19
	cbz	w0, .L1500
	mov	x19, 0
	mov	w22, 0
	.p2align 2
.L1509:
	cmp	w19, 31
	bhi	.L1508
	ldr	x0, [x20, x19, lsl 3]
	cbz	x0, .L1508
	ldr	w1, [x0, 4]
	cbz	w1, .L1508
	ldr	w1, [x0, 8]
	cbz	w1, .L1508
	ldr	w1, [x0, 20]
	cbz	w1, .L1508
	ldr	w1, [x0, 600]
	cmp	w1, 21
	mov	w0, w1
	beq	.L1508
	cmp	w1, 4
	ccmp	w1, 7, 4, ne
	beq	.L1508
	bl	VCTRL_CanBeDecodedByHardWare.part.19
	cmp	w0, wzr
	csinc	w22, w22, w22, eq
	.p2align 2
.L1508:
	add	x19, x19, 1
	cmp	x19, 32
	bne	.L1509
	cmp	w22, 1
	beq	.L1553
.L1510:
	mov	x0, x20
	add	x3, x20, 256
	mov	w2, 0
	.p2align 2
.L1517:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L1516
	ldr	w1, [x1, 600]
	cmp	w1, 6
	csinc	w2, w2, wzr, ne
.L1516:
	cmp	x3, x0
	bne	.L1517
	cmp	w2, 1
	beq	.L1554
.L1518:
	ldr	x0, [x20, w21, sxtw 3]
	ldr	w0, [x0, 600]
	cmp	w0, 1
	bne	.L1500
	ldr	x0, .LC775
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1555
	ldr	x0, .LC776
	ldr	x1, [x0, 56]
	cbz	x1, .L1500
	mov	w0, 0
	blr	x1
	b	.L1500
	.p2align 3
.L1504:
	ldr	x1, .LC774
	mov	w2, 8781
	mov	w0, 0
	bl	dprint_vfmw
.L1500:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1551:
	ldr	x1, .LC769
	mov	w2, 8769
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1553:
	ldr	x19, .LC775
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1556
	mov	w1, 0
	mov	w0, w22
	bl	VDH_Need_Module
.L1513:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1514
	ldr	x0, .LC776
	ldr	x1, [x0, 40]
	cbz	x1, .L1557
	mov	w0, 0
	blr	x1
	b	.L1510
.L1554:
	ldr	x0, .LC775
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1558
	mov	w1, 0
	mov	w0, 3
	bl	VDH_Need_Module
	b	.L1518
.L1558:
	ldr	x0, .LC776
	ldr	x1, [x0, 24]
	cbz	x1, .L1559
	mov	w0, 0
	blr	x1
	b	.L1518
.L1556:
	ldr	x0, .LC776
	ldr	x1, [x0, 8]
	cbz	x1, .L1560
	mov	w0, 0
	blr	x1
	b	.L1513
.L1552:
	ldr	x1, .LC772
	mov	w2, 8775
	bl	dprint_vfmw
	b	.L1500
.L1555:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_Need_Module
	b	.L1500
.L1514:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Need_Module
	b	.L1510
.L1557:
	ldr	x1, .LC777
	mov	w2, 8830
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1510
.L1559:
	ldr	x1, .LC777
	mov	w2, 8861
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1518
.L1560:
	ldr	x1, .LC777
	mov	w2, 8816
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1513
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	3
.LC769:
	.xword	.LC768
	.align	3
.LC770:
	.xword	.LANCHOR0
	.align	3
.LC772:
	.xword	.LC771
	.align	3
.LC774:
	.xword	.LC773
	.align	3
.LC775:
	.xword	g_HalDisable
	.align	3
.LC776:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC777:
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
	bhi	.L1572
	ldr	x19, .LC781
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L1573
	ldr	w21, [x0, 4]
	cmp	w21, 1
	bne	.L1574
	ldr	w0, [x0, 600]
	cmp	w0, 21
	beq	.L1575
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
	cbnz	w0, .L1567
	str	w21, [x1, 20]
	mov	x1, 0
	ldr	x0, .LC786
	ldr	x5, .LC787
	b	.L1570
	.p2align 3
.L1577:
	ldr	w4, [x2, 20]
	str	w4, [x3, x1, lsl 2]
	ldr	w2, [x2, 20]
	str	w2, [x5, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	beq	.L1576
.L1570:
	ldr	x2, [x19, x1, lsl 3]
	add	x3, x0, 1672
	cbnz	x2, .L1577
	add	x2, x0, 1672
	str	wzr, [x5, x1, lsl 2]
	str	wzr, [x2, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	bne	.L1570
	.p2align 2
.L1576:
	add	x0, x0, 1672
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
.L1567:
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	bl	VCTRL_OpenHardware
	ldr	x19, .LC788
	ldr	x0, .LC789
	mov	x2, 12
	mov	w1, 0
	ldr	x3, [x19, 96]
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 720
	ldr	x0, .LC790
	mov	w1, 0
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 2
	ldr	x0, .LC791
	mov	w1, 0
	blr	x3
	ldr	x0, .LC792
	mov	x2, 120
	ldr	x3, [x19, 96]
	mov	w1, 0
	blr	x3
	mov	w0, 0
.L1563:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1574:
	ldr	x3, .LC783
	mov	w2, 2509
	ldr	x1, .LC780
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1563
.L1572:
	ldr	x3, .LC779
	mov	w2, 2507
	ldr	x1, .LC780
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1563
.L1575:
	ldr	x3, .LC785
	mov	w2, 2510
	ldr	x1, .LC780
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1563
.L1573:
	ldr	x3, .LC782
	mov	w2, 2508
	ldr	x1, .LC780
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1563
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	3
.LC779:
	.xword	.LC237
	.align	3
.LC780:
	.xword	.LC5
	.align	3
.LC781:
	.xword	.LANCHOR0
	.align	3
.LC782:
	.xword	.LC281
	.align	3
.LC783:
	.xword	.LC473
	.align	3
.LC785:
	.xword	.LC784
	.align	3
.LC786:
	.xword	.LANCHOR6
	.align	3
.LC787:
	.xword	g_ChanCtx
	.align	3
.LC788:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC789:
	.xword	g_TimeRecId
	.align	3
.LC790:
	.xword	g_TimeRecTable
	.align	3
.LC791:
	.xword	g_DataRecId
	.align	3
.LC792:
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
	ldr	x1, .LC795
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	3
.LC795:
	.xword	.LC794
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
	ldr	x19, .LC796
	mov	w0, 0
	add	x23, x19, 256
	b	.L1588
	.p2align 3
.L1630:
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1627
.L1580:
	add	x19, x19, 8
	cmp	x19, x23
	beq	.L1628
.L1588:
	ldr	x20, [x19]
	cbz	x20, .L1580
	ldr	w21, [x20, 600]
	cbnz	w0, .L1581
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1629
.L1581:
	cmp	w22, wzr
	ccmp	w21, 1, 0, eq
	beq	.L1630
.L1584:
	cmp	w24, wzr
	ccmp	w21, 6, 0, eq
	bne	.L1580
	ldr	w1, [x20, 4]
	cmp	w1, 1
	bne	.L1580
	ldr	w26, [x20, 8]
.L1608:
	cmp	w26, 1
	add	x19, x19, 8
	csinc	w24, w24, wzr, ne
	cmp	x19, x23
	bne	.L1588
	.p2align 2
.L1628:
	cbnz	w0, .L1589
	ldr	x19, .LC797
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1594
	mov	w0, w25
	bl	SCDDRV_ResetSCD
	mov	w0, w25
	bl	VDMDRV_ResetVDH
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1594
	mov	w1, 0
	mov	w0, 1
	bl	VDH_UnNeed_Module
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1597
.L1636:
	ldr	x0, .LC798
	ldr	x1, [x0, 48]
	cbz	x1, .L1631
	mov	w0, 0
	blr	x1
.L1600:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle
.L1589:
	cbnz	w24, .L1601
	ldr	x0, .LC797
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1632
	mov	w1, 0
	mov	w0, 3
	bl	VDH_UnNeed_Module
.L1601:
	cbnz	w22, .L1579
	ldr	x0, .LC797
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1633
	ldr	x0, .LC798
	ldr	x1, [x0, 64]
	cbz	x1, .L1579
	mov	w0, 0
	blr	x1
.L1579:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1629:
	ldr	w26, [x20, 8]
	cmp	w26, 1
	beq	.L1634
.L1583:
	cmp	w21, 1
	ccmp	w22, wzr, 0, eq
	bne	.L1584
.L1607:
	cmp	w26, 1
	csinc	w22, w22, wzr, ne
	cmp	w21, 6
	ccmp	w24, wzr, 0, eq
	beq	.L1608
	b	.L1580
	.p2align 3
.L1634:
	cmp	w21, 4
	ccmp	w21, 7, 4, ne
	beq	.L1583
	mov	w0, w21
	bl	VCTRL_CanBeDecodedByHardWare.part.19
	cmp	w0, wzr
	cset	w0, ne
	b	.L1583
.L1594:
	ldr	x0, .LC798
	ldr	x1, [x0, 16]
	cbz	x1, .L1635
	mov	w0, 0
	blr	x1
.L1596:
	mov	w0, 0
	bl	VDMDRV_SetStateIdle
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1636
.L1597:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_UnNeed_Module
	b	.L1589
.L1633:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_UnNeed_Module
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1632:
	ldr	x0, .LC798
	ldr	x1, [x0, 32]
	cbz	x1, .L1637
	mov	w0, 0
	blr	x1
	b	.L1601
.L1631:
	ldr	x1, .LC799
	mov	w2, 8959
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1600
.L1635:
	ldr	x1, .LC799
	mov	w2, 8944
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1596
.L1637:
	ldr	x1, .LC799
	mov	w2, 8977
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1601
.L1627:
	ldr	w26, [x20, 8]
	b	.L1607
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	3
.LC796:
	.xword	.LANCHOR0
	.align	3
.LC797:
	.xword	g_HalDisable
	.align	3
.LC798:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC799:
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
	bhi	.L1644
	ldr	x20, .LC803
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1645
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1643
	str	w1, [x0, 24]
	mov	w0, w19
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 12]
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 8]
	bl	SM_Stop
	cbnz	w0, .L1643
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
.L1640:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1643:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1644:
	ldr	x3, .LC801
	mov	w2, 2601
	ldr	x1, .LC802
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1640
.L1645:
	ldr	x3, .LC805
	mov	w2, 2602
	ldr	x1, .LC802
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1640
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	3
.LC801:
	.xword	.LC237
	.align	3
.LC802:
	.xword	.LC5
	.align	3
.LC803:
	.xword	.LANCHOR0
	.align	3
.LC805:
	.xword	.LC804
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
	ldr	x19, .LC806
	b	.L1648
	.p2align 3
.L1652:
	ldr	x1, [x19, 240]
	mov	w0, 10
	add	w20, w20, 1
	blr	x1
	cmp	w20, 50
	beq	.L1650
.L1648:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, w22
	bl	VCTRL_StopChan
	mov	w21, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cbnz	w21, .L1652
	cmp	w20, 49
	bgt	.L1650
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1650:
	ldr	x1, .LC808
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
.LC806:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC808:
	.xword	.LC807
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
	ldr	x20, .LC809
	ldr	x1, [x20, w21, sxtw 3]
	cbz	x1, .L1680
	ldr	w0, [x23]
	cmp	w0, 1
	bhi	.L1681
	mov	w0, w21
	ldr	w22, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x24, .LC814
	ldr	x0, .LC815
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
	cbz	x0, .L1682
	add	x0, x0, 290816
	str	wzr, [x0, 1148]
.L1658:
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
	str	w2, [x1, 1224]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 294912
	ldr	w0, [x0, 600]
	add	x1, x1, 1240
	bl	ReleaseCurPic
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 416
	ldr	x3, [x24, 96]
	mov	w1, 0
	add	x0, x0, 744
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x1, -1
	ldr	w2, [x0, 1448]
	str	x1, [x0, 664]
	cmp	w2, 1
	str	x1, [x0, 672]
	str	wzr, [x0, 1160]
	beq	.L1683
.L1659:
	ldr	w0, [x0, 600]
	cmp	w0, 20
	beq	.L1660
	ldr	w0, [x23, 8]
	cbz	w0, .L1684
.L1660:
	mov	w0, w19
	bl	FSP_EmptyInstance
.L1661:
	mov	w0, w19
	bl	InitUsdPool
	ldr	w0, [x23]
	cbz	w0, .L1685
.L1662:
	ldr	w0, [x20, 1396]
	cbz	w0, .L1663
	add	x20, x20, 2192
	str	w19, [x29, 76]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1665
	mov	w0, 512
	add	x1, x29, 76
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1665
	add	x1, x29, 76
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1665:
	ldr	x1, .LC817
	mov	w0, 32
	bl	dprint_vfmw
.L1663:
	cbnz	w22, .L1686
.L1667:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1655:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1685:
	mov	w0, w19
	bl	SM_Reset
	b	.L1662
	.p2align 3
.L1686:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1667
	.p2align 3
.L1683:
	add	x1, x0, 294912
	str	wzr, [x0, 1496]
	str	wzr, [x1, 1172]
	b	.L1659
	.p2align 3
.L1684:
	mov	w0, w19
	bl	FSP_ResetInstance
	b	.L1661
	.p2align 3
.L1681:
	ldr	x1, .LC813
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
.L1682:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1658
.L1680:
	ldr	x3, .LC810
	mov	w2, 3358
	ldr	x1, .LC811
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1655
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	3
.LC809:
	.xword	.LANCHOR0
	.align	3
.LC810:
	.xword	.LC8
	.align	3
.LC811:
	.xword	.LC5
	.align	3
.LC813:
	.xword	.LC812
	.align	3
.LC814:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC815:
	.xword	.LANCHOR5
	.align	3
.LC817:
	.xword	.LC816
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
	ldr	x20, .LC820
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1710
	mov	w0, w19
	ldr	w21, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x22, .LC823
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, 4
	ldr	x2, [x22, 24]
	str	wzr, [x1, 444]
	str	wzr, [x1, 448]
	blr	x2
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 1448]
	cmp	w1, 1
	beq	.L1711
.L1690:
	sxtw	x3, w19
	ldr	x0, .LC824
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
	cbz	x0, .L1712
	add	x0, x0, 290816
	str	wzr, [x0, 1148]
.L1692:
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	str	wzr, [x1, 1224]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 416
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 744
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, -1
	add	x1, x0, 294912
	str	x2, [x0, 664]
	str	x2, [x0, 672]
	str	wzr, [x0, 1160]
	str	wzr, [x1, 1192]
	str	wzr, [x1, 1196]
	str	wzr, [x1, 1200]
	ldr	w2, [x0, 1448]
	cmp	w2, 1
	beq	.L1713
.L1693:
	ldr	w0, [x0, 600]
	cmp	w0, 20
	mov	w0, w19
	beq	.L1694
	bl	FSP_ResetInstance
.L1695:
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	InitUsdPool
	mov	w0, w19
	bl	SM_Reset
	ldr	w0, [x20, 1396]
	cbz	w0, .L1696
	add	x20, x20, 2192
	str	w19, [x29, 60]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1698
	mov	w0, 512
	add	x1, x29, 60
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1698
	add	x1, x29, 60
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1698:
	ldr	x1, .LC825
	mov	w0, 32
	bl	dprint_vfmw
.L1696:
	cbnz	w21, .L1714
.L1700:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1689:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1714:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1700
	.p2align 3
.L1694:
	bl	FSP_EmptyInstance
	b	.L1695
	.p2align 3
.L1713:
	str	wzr, [x0, 1496]
	str	wzr, [x1, 1172]
	b	.L1693
	.p2align 3
.L1711:
	add	x1, x0, 294912
	ldr	w2, [x0, 600]
	ldr	w1, [x1, 1232]
	cmp	w1, w2
	bne	.L1690
	str	wzr, [x0, 12]
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	b	.L1690
	.p2align 3
.L1712:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1692
.L1710:
	ldr	x3, .LC821
	mov	w2, 3758
	ldr	x1, .LC822
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1689
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	3
.LC820:
	.xword	.LANCHOR0
	.align	3
.LC821:
	.xword	.LC8
	.align	3
.LC822:
	.xword	.LC5
	.align	3
.LC823:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC824:
	.xword	.LANCHOR5
	.align	3
.LC825:
	.xword	.LC816
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
	ldr	x22, .LC828
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
	ldr	x24, .LC829
	str	x28, [x24, 1800]
	cbz	x28, .L1786
	ldr	w0, [x28, 36]
	tbnz	w0, #31, .L1718
	ldr	w0, [x28, 12]
	cmp	w0, 31
	ble	.L1718
	ldr	w0, [x28, 16]
	cmp	w0, 31
	ble	.L1718
	ldr	w1, [x28, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L1718
	ldr	w0, [x28, 44]
	cmp	w0, 1
	beq	.L1787
	cmp	w0, 2
	bne	.L1720
	ldr	w0, [x28, 20]
	cmp	w0, wzr
	ble	.L1718
	ldr	w0, [x28, 24]
	cmp	w0, wzr
	ble	.L1718
.L1784:
	ldr	w0, [x28, 28]
	cmp	w0, wzr
	ble	.L1718
	ldr	w0, [x28, 32]
	cmp	w0, wzr
	bgt	.L1720
.L1718:
	ldr	x1, .LC832
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1799:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L1720:
	ldr	w0, [x28, 168]
	cmp	w0, 1
	bls	.L1722
	str	wzr, [x28, 168]
.L1722:
	mov	w4, 728
	mov	w23, 1
	cmp	w19, 26
	mov	w3, w20
	movk	w4, 0xb2, lsl 16
	mov	w20, 14920
	add	x2, x29, 104
	mov	x1, x28
	mov	w0, w19
	movk	w20, 0xc, lsl 16
	stp	w23, w23, [x28, 192]
	csel	w20, w20, w4, ne
	bl	VCTRL_GetChanMemSize
	cbnz	w0, .L1788
	ldr	x3, [x22, 96]
	add	x21, x28, 72
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 56]
	cbz	x0, .L1726
	ldr	w0, [x21, 64]
	cbnz	w0, .L1727
.L1726:
	mov	w0, 3
	str	w0, [x29, 164]
	mov	w0, 7
	bl	VFMW_GetString
	ldr	w2, [x29, 112]
	mov	w4, 1
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1789
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
.L1730:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 8]
	cbnz	x0, .L1790
.L1759:
	ldr	w0, [x28, 168]
	cmp	w0, 1
	beq	.L1733
	mov	w0, 3
	str	w0, [x29, 164]
	mov	w0, 8
	bl	VFMW_GetString
	ldr	w2, [x29, 104]
	mov	w4, 0
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1791
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
.L1737:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 136
	blr	x3
	ldr	x0, [x21, 32]
	cbz	x0, .L1761
	ldr	w0, [x21, 40]
	cbnz	w0, .L1741
.L1761:
	mov	w1, 3
	mov	w0, 9
	str	w1, [x29, 164]
	bl	VFMW_GetString
	ldr	w2, [x29, 108]
	mov	w4, 0
	add	x3, x29, 136
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1792
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
.L1781:
	ldr	x1, [x22, 24]
	mov	w0, 0
	blr	x1
	ldr	x26, .LC847
	ldr	x0, [x26]
	cbz	x0, .L1764
	add	x0, x26, 8
	mov	w21, 1
	b	.L1752
	.p2align 3
.L1793:
	add	w21, w21, 1
	cmp	w21, 32
	beq	.L1753
.L1752:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbnz	x1, .L1793
	cmp	w21, 31
	bhi	.L1753
.L1750:
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
	add	x0, x0, 1280
	blr	x3
	ldr	x0, [x26, w21, sxtw 3]
	ldr	x3, .LC850
	str	w19, [x0, 36]
	str	w20, [x0, 1188]
	ldr	x0, [x26, w21, sxtw 3]
	str	w21, [x0]
	str	w19, [x0, 636]
	str	wzr, [x0, 1216]
	ldr	x0, [x26, w21, sxtw 3]
	ldr	w1, [x28]
	str	w1, [x0, 32]
	mov	w1, 21
	ldr	x0, [x26, w21, sxtw 3]
	add	x2, x0, 294912
	str	w1, [x0, 600]
	str	w1, [x2, 1232]
	lsl	x1, x27, 4
	str	wzr, [x0, 28]
	ldr	x0, [x26, w21, sxtw 3]
	ldr	w4, [x28, 200]
	add	x2, x0, 294912
	str	w4, [x2, 1216]
	add	x2, x0, 1536
	str	x2, [x3, x1]
	mov	w1, 30
	str	w1, [x0, 1528]
	add	x1, x0, 262144
	add	x1, x1, 2000
	mov	w0, w21
	ldr	w3, [x28, 192]
	str	w3, [x2, 72]
	ldr	w3, [x28, 196]
	str	w3, [x2, 76]
	bl	FSP_EnableInstance
	cbnz	w0, .L1794
	mov	w0, w21
	mov	w20, 0
	mov	w25, 255
	bl	VCTRL_ResetChan
	ldr	x0, [x26, w21, sxtw 3]
	ldp	w2, w1, [x29, 120]
	str	w2, [x0, 360]
	str	w1, [x0, 364]
	add	x1, x0, 290816
	ldr	w2, [x29, 128]
	str	w2, [x0, 368]
	add	x2, x1, 1024
	add	x0, x0, 294912
	stp	wzr, wzr, [x2, 100]
	stp	wzr, wzr, [x2, 108]
	str	wzr, [x1, 1140]
	str	wzr, [x1, 1144]
	ldr	w1, [x28, 168]
	str	w1, [x0, 1180]
	str	wzr, [x0, 1172]
	.p2align 2
.L1755:
	uxtw	x1, w20
	ldr	x0, [x26, x27, lsl 3]
	lsl	x19, x1, 6
	ldr	x4, [x22, 96]
	add	x19, x19, x1, lsl 3
	mov	x2, 72
	add	x3, x19, 290816
	mov	w1, 0
	add	x3, x3, 1152
	add	w20, w20, 1
	add	x0, x0, x3
	blr	x4
	ldr	x0, [x26, x27, lsl 3]
	cmp	w20, 32
	add	x1, x0, x19
	add	x1, x1, 290816
	str	w25, [x1, 1152]
	str	w25, [x1, 1156]
	str	w25, [x1, 1160]
	bne	.L1755
	ldr	x3, [x22, 96]
	add	x0, x0, 290816
	mov	x2, 1248
	mov	w1, 0
	add	x0, x0, 3456
	add	x24, x24, 1808
	blr	x3
	ldr	x0, [x26, x27, lsl 3]
	mov	x2, 24
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 294912
	add	x0, x0, 608
	blr	x3
	str	wzr, [x24, x27, lsl 2]
	ldr	x0, [x26, x27, lsl 3]
	ldr	w6, [x29, 272]
	ldr	x3, [x29, 232]
	add	x5, x0, 262144
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
	str	wzr, [x5, 2032]
	ldr	w5, [x0, 1448]
	cmp	w5, 1
	beq	.L1756
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
.L1757:
	ldr	x1, [x26, w21, sxtw 3]
	mov	w0, w21
	str	w21, [x1]
	ldr	x1, [x26, w21, sxtw 3]
	add	x2, x1, 262144
	str	w21, [x1, 256]
	str	w21, [x1, 260]
	str	w21, [x2, 1768]
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
	add	x19, x19, 294912
	blr	x0
	ldr	x1, [x22, 32]
	str	w0, [x19, 1188]
	mov	w0, 0
	blr	x1
	mov	w0, w21
.L1780:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L1790:
	ldr	w0, [x21, 16]
	cbz	w0, .L1759
	ldr	x3, [x22, 104]
	mov	x2, 24
	mov	x1, x21
	add	x0, x29, 224
	blr	x3
	ldr	w0, [x28, 168]
	ldr	w2, [x29, 240]
	cmp	w0, 1
	beq	.L1739
	ldr	w4, [x29, 104]
	cmp	w2, w4
	blt	.L1795
.L1739:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_AddMemRecord
	b	.L1737
	.p2align 3
.L1733:
	str	wzr, [x29, 120]
	str	wzr, [x29, 224]
	str	xzr, [x29, 232]
	str	wzr, [x29, 240]
	b	.L1737
.L1787:
	ldr	w0, [x28, 20]
	cmp	w0, wzr
	bgt	.L1784
	b	.L1718
	.p2align 3
.L1756:
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
	b	.L1757
.L1727:
	ldr	x3, [x22, 104]
	mov	x2, 24
	add	x1, x28, 120
	add	x0, x29, 272
	blr	x3
	ldr	w0, [x29, 112]
	ldr	w2, [x29, 288]
	cmp	w2, w0
	blt	.L1796
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_AddMemRecord
	b	.L1730
.L1741:
	mov	x2, 24
	add	x0, x29, 224
	ldr	x3, [x22, 104]
	add	x1, x28, 96
	add	x0, x0, x2
	blr	x3
	ldr	x1, [x29, 256]
	cbz	x1, .L1746
	ldr	w0, [x29, 108]
	ldr	w2, [x29, 264]
	cmp	w2, w0
	blt	.L1746
	ldr	w0, [x29, 248]
	bl	MEM_AddMemRecord
	b	.L1781
.L1792:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1797
.L1743:
	ldr	w0, [x29, 120]
	cmp	w0, 1
	beq	.L1798
.L1744:
	ldr	x1, .LC844
	mov	w2, 1909
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1791:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1800
.L1735:
	ldr	x1, .LC840
	mov	w2, 1975
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1764:
	mov	w21, 0
	b	.L1750
.L1788:
	ldr	x1, .LC834
	mov	w2, 2132
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1780
.L1794:
	ldr	x1, .LC852
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
	add	x5, x1, 294912
	add	x2, x1, 290816
	ldr	w6, [x1, 364]
	add	x2, x2, 1152
	ldr	w3, [x1, 360]
	ldr	w4, [x1, 368]
	ldr	w5, [x5, 1180]
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
	b	.L1780
	.p2align 3
.L1753:
	ldr	x1, .LC849
	mov	w2, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1780
.L1789:
	ldr	x1, .LC836
	mov	w2, 2033
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1746:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1801
.L1748:
	ldr	w0, [x29, 120]
	cmp	w0, 1
	beq	.L1802
.L1749:
	ldr	x1, .LC846
	mov	w2, 1938
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1798:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 224]
	ldr	w2, [x29, 240]
	ldr	x1, [x29, 232]
	bl	MEM_DelMemRecord
	b	.L1744
.L1800:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1735
.L1796:
	ldr	x1, .LC838
	mov	w2, 2049
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1797:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1743
.L1795:
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L1803
.L1740:
	ldr	x1, .LC842
	mov	w3, w2
	mov	w0, 1
	mov	w2, 2007
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1802:
	ldr	w0, [x29, 224]
	ldr	x1, [x29, 232]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 224]
	ldr	w2, [x29, 240]
	ldr	x1, [x29, 232]
	bl	MEM_DelMemRecord
	b	.L1749
.L1786:
	ldr	x1, .LC831
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1799
.L1801:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 272]
	ldr	w2, [x29, 288]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	b	.L1748
.L1803:
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x29, 288]
	ldr	w0, [x29, 272]
	ldr	x1, [x29, 280]
	bl	MEM_DelMemRecord
	ldr	w4, [x29, 104]
	ldr	w2, [x29, 240]
	b	.L1740
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	3
.LC828:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC829:
	.xword	.LANCHOR6
	.align	3
.LC831:
	.xword	.LC830
	.align	3
.LC832:
	.xword	.LC513
	.align	3
.LC834:
	.xword	.LC833
	.align	3
.LC836:
	.xword	.LC835
	.align	3
.LC838:
	.xword	.LC837
	.align	3
.LC840:
	.xword	.LC839
	.align	3
.LC842:
	.xword	.LC841
	.align	3
.LC844:
	.xword	.LC843
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC847:
	.xword	.LANCHOR0
	.align	3
.LC849:
	.xword	.LC848
	.align	3
.LC850:
	.xword	s_SmIIS
	.align	3
.LC852:
	.xword	.LC851
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
	mov	w20, w0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L1834
	ldr	x22, .LC856
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L1835
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L1836
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_CheckChanWH
	mov	w21, w0
	cbnz	w0, .L1837
	ldr	x19, .LC861
	add	x24, x19, 1936
	mov	x1, x24
	bl	PDT_GetAttribute
	ldr	w0, [x19, 1956]
	ldr	w2, [x23, 8]
	cmp	w0, 20
	bhi	.L1811
	cmp	w0, w2
	beq	.L1812
	add	x0, x19, 1960
	add	x3, x19, 2084
	.p2align 2
.L1814:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 20
	bhi	.L1811
	cmp	w1, w2
	beq	.L1812
	cmp	x0, x3
	bne	.L1814
.L1812:
	cmp	w2, 8
	str	wzr, [x29, 88]
	beq	.L1838
.L1815:
	cmp	w2, 9
	beq	.L1839
.L1829:
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_CmpConfigParameter
	cbz	w0, .L1840
	ldr	x24, .LC866
	mov	x2, 140
	ldr	x0, [x22, w20, sxtw 3]
	mov	x1, x23
	ldr	x3, [x24, 104]
	add	x0, x0, 44
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	mov	x2, 72
	ldr	w1, [x23, 24]
	str	w1, [x0, 20]
	ldr	x0, [x22, w20, sxtw 3]
	ldr	w1, [x23, 8]
	ldr	x3, [x24, 96]
	str	w1, [x0, 600]
	ldr	w1, [x23, 96]
	str	w1, [x0, 1456]
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	ldr	w0, [x0, 384]
	str	w0, [x29, 104]
	bl	MEM_Phy2Vir
	str	x0, [x29, 88]
	ldr	x1, [x22, w20, sxtw 3]
	ldr	w0, [x23, 84]
	ldr	w3, [x23, 24]
	ldr	w2, [x1, 396]
	cmp	w0, 1
	str	w2, [x29, 108]
	add	x1, x1, 294912
	ldr	w2, [x23, 8]
	str	w2, [x29, 100]
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	strb	w3, [x29, 96]
	str	w2, [x29, 112]
	beq	.L1841
	str	wzr, [x1, 1228]
.L1820:
	ldr	w0, [x23, 80]
	add	x26, x23, 12
	ldr	x3, [x24, 104]
	mov	x2, 12
	mov	x1, x26
	str	w0, [x29, 136]
	stp	wzr, wzr, [x29, 128]
	add	x0, x29, 116
	blr	x3
	add	x1, x29, 88
	mov	w0, w20
	bl	SM_Config
	ldr	x3, [x24, 96]
	mov	x2, 1
	mov	w1, 0
	add	x0, x29, 80
	blr	x3
	ldr	w2, [x23, 84]
	cmp	w2, 1
	beq	.L1842
.L1821:
	ldr	x0, [x22, w20, sxtw 3]
	ldr	x1, .LC867
	ldr	w2, [x0, 344]
	str	w2, [x0, 1192]
	ldr	w2, [x0, 352]
	str	w2, [x0, 1196]
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
	ldr	w1, [x1, 72]
	ldr	w2, [x23, 28]
	str	w2, [x0, 612]
	cmp	w1, 7
	ldr	w2, [x23, 28]
	str	w2, [x0, 608]
	ldr	w2, [x23, 36]
	str	w2, [x0, 616]
	beq	.L1843
.L1822:
	str	w1, [x0, 632]
	mov	w25, 1
	ldr	w1, [x23, 44]
	str	w1, [x0, 620]
	ldr	w1, [x23, 128]
	str	w1, [x0, 1244]
	ldr	w1, [x23, 136]
	str	w1, [x0, 1524]
	str	w25, [x0, 1248]
	str	w25, [x0, 1252]
	ldr	w1, [x23, 72]
	cmp	w1, w25
	cset	w1, eq
	str	w1, [x0, 1228]
	ldr	w1, [x23, 76]
	str	w1, [x0, 1232]
	ldr	w1, [x23, 48]
	str	w1, [x0, 1236]
	ldr	w1, [x29, 132]
	str	w1, [x0, 1240]
	str	wzr, [x0, 1496]
	str	wzr, [x0, 1516]
	add	x0, x0, 294912
	ldrsb	w1, [x23, 1]
	strb	w1, [x0, 1176]
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_ConfigChanCompress
	ldr	x0, [x22, w20, sxtw 3]
	mov	x2, 12
	ldr	x3, [x24, 104]
	mov	x1, x26
	add	x0, x0, 1164
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	add	x1, x0, 294912
	ldr	w2, [x0, 600]
	ldr	w0, [x1, 1232]
	cmp	w0, w2
	beq	.L1823
	mov	w0, w20
	bl	VCTRL_ResetChan
	ldr	w1, [x23, 8]
	ldr	x0, [x22, w20, sxtw 3]
	cmp	w1, 20
	beq	.L1824
	ldr	w2, [x0, 600]
	add	x1, x0, 294912
.L1823:
	ldr	x4, .LC870
	mov	x0, 0
	str	w2, [x1, 1232]
	b	.L1828
	.p2align 3
.L1845:
	ldr	w3, [x1, 20]
	str	w3, [x2, x0, lsl 2]
	ldr	w1, [x1, 20]
	str	w1, [x4, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1844
.L1828:
	ldr	x1, [x22, x0, lsl 3]
	add	x2, x19, 2088
	cbnz	x1, .L1845
	add	x1, x19, 2088
	str	wzr, [x4, x0, lsl 2]
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1828
.L1844:
	add	x0, x19, 2088
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1840:
	ldr	x1, .LC865
	mov	w21, 0
	bl	dprint_vfmw
.L1833:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1811:
	ldr	x1, .LC863
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1839:
	add	x0, x29, 88
	bl	REAL9DEC_Support
	ldr	w0, [x29, 88]
	cbnz	w0, .L1829
.L1816:
	mov	w21, -1
	b	.L1833
.L1838:
	add	x0, x29, 88
	bl	REAL8DEC_Support
	ldr	w0, [x29, 88]
	cbz	w0, .L1816
	ldr	w2, [x23, 8]
	b	.L1815
.L1843:
	ldr	w1, [x23, 40]
	b	.L1822
.L1841:
	ldr	w2, [x23, 88]
	stp	w0, w2, [x29, 140]
	ldr	w2, [x23, 92]
	ldr	w0, [x23, 132]
	str	w2, [x29, 148]
	str	w0, [x1, 1228]
	b	.L1820
.L1836:
	ldr	x3, .LC858
	mov	w2, 2969
	ldr	x1, .LC855
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1833
.L1842:
	add	x1, x29, 80
	mov	w0, w20
	strb	w2, [x29, 80]
	bl	FSP_ConfigAttribute
	b	.L1821
.L1837:
	ldr	x1, .LC860
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1833
.L1824:
	ldr	w3, [x0, 388]
	ldr	w4, [x0, 392]
	ldr	w1, [x0, 1292]
	ldr	w2, [x0, 1296]
	mov	w0, w20
	bl	VCTRL_PartitionMemForStdUser
	cbnz	w0, .L1825
	ldr	x0, [x22, w20, sxtw 3]
	add	x1, x0, 294912
	ldr	w2, [x0, 600]
	b	.L1823
.L1834:
	ldr	x3, .LC854
	mov	w2, 2967
	ldr	x1, .LC855
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1833
.L1835:
	ldr	x3, .LC857
	mov	w2, 2968
	ldr	x1, .LC855
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1833
.L1825:
	ldr	x1, .LC869
	mov	w0, w25
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1833
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	3
.LC854:
	.xword	.LC237
	.align	3
.LC855:
	.xword	.LC5
	.align	3
.LC856:
	.xword	.LANCHOR0
	.align	3
.LC857:
	.xword	.LC8
	.align	3
.LC858:
	.xword	.LC242
	.align	3
.LC860:
	.xword	.LC859
	.align	3
.LC861:
	.xword	.LANCHOR6
	.align	3
.LC863:
	.xword	.LC862
	.align	3
.LC865:
	.xword	.LC864
	.align	3
.LC866:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC867:
	.xword	.LANCHOR2
	.align	3
.LC869:
	.xword	.LC868
	.align	3
.LC870:
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
	ldr	x1, .LC875
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC876
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1846
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 64]
	bl	VCTRL_ConfigChan
.L1846:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	3
.LC875:
	.xword	.LC874
	.align	3
.LC876:
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
	ldr	x1, .LC878
	lsr	w20, w3, 24
	and	w19, w3, 7
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC879
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1851
	ldr	x1, .LC881
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1851:
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 68]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	3
.LC878:
	.xword	.LC877
	.align	3
.LC879:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC881:
	.xword	.LC880
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
	ldr	x1, .LC883
	lsr	w20, w3, 24
	and	w19, w3, 3
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC884
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1852
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 72]
	bl	VCTRL_ConfigChan
.L1852:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	3
.LC883:
	.xword	.LC882
	.align	3
.LC884:
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
	ldr	x1, .LC886
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC887
	mov	w1, 0
	mov	x2, 140
	add	x0, x29, 32
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 32
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1854
	add	x1, x29, 32
	mov	w0, w20
	str	w19, [x29, 60]
	bl	VCTRL_ConfigChan
.L1854:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 176
	ret
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	3
.LC886:
	.xword	.LC885
	.align	3
.LC887:
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
	ldr	x1, .LC889
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	3
.LC889:
	.xword	.LC888
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
	ldr	x20, .LC890
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	cmp	w19, 31
	bhi	.L1868
	ldr	x21, .LC895
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1869
	ldr	w22, [x0, 4]
	cmp	w22, 1
	bne	.L1870
	str	wzr, [x0, 8]
	mov	w0, 0
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, w19
	bl	SCDDRV_IsChanDec
	cbnz	w0, .L1871
.L1862:
	ldr	x1, [x20, 24]
	mov	w0, 0
	sxtw	x22, w19
	blr	x1
	ldr	x2, .LC900
	mov	w0, 4
	ldr	x1, [x20, 24]
	str	wzr, [x2, w19, sxtw 2]
	blr	x1
	mov	w0, w19
	bl	VCTRL_StopChan
	ldr	x1, [x20, 32]
	cbnz	w0, .L1872
	mov	w0, 4
	lsl	x22, x22, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	x1, .LC901
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
	ldr	x3, .LC902
	add	x4, x1, 294912
	add	x2, x1, 290816
	ldr	w5, [x1, 368]
	add	x2, x2, 1152
	str	w5, [x29, 116]
	ldr	w4, [x4, 1180]
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
.L1859:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1871:
	mov	w0, w19
	ldr	x23, [x20, 264]
	bl	SCDDRV_IsChanDec
	cmp	w0, wzr
	mov	w2, 500
	cset	w1, eq
	mov	w0, w22
	blr	x23
	b	.L1862
	.p2align 3
.L1870:
	ldr	x2, .LC892
	mov	w3, 2410
	ldr	x4, .LC899
	mov	w0, 0
	ldr	x1, .LC894
	add	x2, x2, 816
.L1867:
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
.L1872:
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1859
	.p2align 3
.L1868:
	ldr	x2, .LC892
	mov	w3, 2389
	ldr	x4, .LC891
	mov	w0, 0
	ldr	x1, .LC894
	add	x2, x2, 816
	b	.L1867
.L1869:
	ldr	x2, .LC892
	mov	w3, 2398
	ldr	x4, .LC897
	ldr	x1, .LC894
	add	x2, x2, 816
	b	.L1867
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	3
.LC890:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC891:
	.xword	.LC237
	.align	3
.LC892:
	.xword	.LANCHOR4
	.align	3
.LC894:
	.xword	.LC893
	.align	3
.LC895:
	.xword	.LANCHOR0
	.align	3
.LC897:
	.xword	.LC896
	.align	3
.LC899:
	.xword	.LC898
	.align	3
.LC900:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC901:
	.xword	.LANCHOR5
	.align	3
.LC902:
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
	ldr	x20, .LC905
	ldr	w0, [x20, 256]
	cmp	w0, 1
	bne	.L1880
	mov	x19, 0
	.p2align 2
.L1876:
	ldr	x1, [x20, x19, lsl 3]
	mov	w0, w19
	add	x19, x19, 1
	cbz	x1, .L1875
	bl	VCTRL_DestroyChan
.L1875:
	cmp	x19, 32
	bne	.L1876
	bl	FSP_Exit
	ldr	x21, .LC906
	ldr	w1, [x20, 260]
	mov	w2, 3
	str	w2, [x20, 264]
	cbz	w1, .L1878
	ldr	x1, [x21, 240]
	mov	w0, 10
	mov	w19, 49
	blr	x1
	b	.L1879
	.p2align 3
.L1890:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L1878
.L1879:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cbnz	w1, .L1890
.L1878:
	ldr	x0, .LC907
	mov	x2, 128
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 264
	blr	x3
	add	x0, x20, 288
	bl	CloseDrivers
	str	wzr, [x20, 256]
	mov	w0, 0
.L1889:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1880:
	mov	w0, -1
	b	.L1889
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	3
.LC905:
	.xword	.LANCHOR0
	.align	3
.LC906:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC907:
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
	ldr	x1, .LC910
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC911
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC912
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	3
.LC910:
	.xword	.LC909
	.align	3
.LC911:
	.xword	.LC888
	.align	3
.LC912:
	.xword	.LC794
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
	ldr	x1, .LC913
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	3
.LC913:
	.xword	.LC909
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
	beq	.L1903
	mov	w19, 2
	cmp	w20, wzr
	csel	w19, w19, wzr, eq
.L1894:
	ldr	x0, .LC914
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1905
	mov	w1, w19
	mov	w0, 0
	bl	VDH_Require_DspCode
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1905:
	ldr	x20, .LC915
	ldr	x1, [x20, 8]
	cbz	x1, .L1906
	mov	w0, 0
	blr	x1
.L1897:
	ldr	x1, [x20, 40]
	cbz	x1, .L1907
	mov	w0, 0
	blr	x1
.L1899:
	ldr	x1, [x20, 24]
	cbz	x1, .L1908
	mov	w0, 0
	blr	x1
.L1901:
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
.L1903:
	mov	w19, 1
	b	.L1894
	.p2align 3
.L1906:
	ldr	x1, .LC916
	mov	w2, 3264
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1897
	.p2align 3
.L1907:
	ldr	x1, .LC916
	mov	w2, 3265
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1899
	.p2align 3
.L1908:
	ldr	x1, .LC916
	mov	w2, 3266
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1901
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	3
.LC914:
	.xword	g_HalDisable
	.align	3
.LC915:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC916:
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
	ldr	x0, .LC917
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 600]
	cbnz	w1, .L1921
	ldr	w21, [x0, 1236]
	mov	w0, 0
	cmp	w21, wzr
	cset	w3, eq
	cmp	w1, 6
	cset	w2, ne
	tst	w3, w2
	beq	.L1940
.L1927:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1921:
	cmp	w1, 6
	mov	w3, 1
	cset	w2, ne
	mov	w21, 0
	tst	w3, w2
	mov	w0, 0
	bne	.L1927
.L1940:
	ldr	x20, .LC918
	add	x0, x20, 268
	add	x3, x20, 392
	ldr	w2, [x20, 264]
	cbz	w2, .L1912
	b	.L1911
	.p2align 3
.L1942:
	beq	.L1941
.L1912:
	ldr	w2, [x0]
	add	x0, x0, 4
	cmp	x3, x0
	cbz	w2, .L1942
.L1911:
	cmp	w2, 1
	beq	.L1943
	cmp	w1, 6
	mov	w0, 0
	beq	.L1927
	ldr	x1, .LC922
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1927
	.p2align 3
.L1941:
	mov	w0, w19
	bl	VCTRL_InitDspCode
	cmp	w21, 1
	beq	.L1944
	add	x20, x20, 264
	mov	w1, 2
	mov	w0, 0
	str	w1, [x20, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1944:
	add	x20, x20, 264
	mov	w0, 0
	str	w21, [x20, w19, sxtw 2]
	b	.L1927
	.p2align 3
.L1943:
	cmp	w21, 1
	mov	w0, 0
	beq	.L1927
	ldr	x1, .LC920
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1927
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	3
.LC917:
	.xword	.LANCHOR0
	.align	3
.LC918:
	.xword	.LANCHOR5
	.align	3
.LC920:
	.xword	.LC919
	.align	3
.LC922:
	.xword	.LC921
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
	ldr	x0, .LC925
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 262144
	str	w19, [x0, 2032]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	3
.LC925:
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
	ldr	x0, .LC926
	ldr	x0, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x0, 290816
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 1124]
	ret
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	3
.LC926:
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
	beq	.L1949
	cbz	w19, .L1950
	cmp	w19, 2
	bne	.L1958
	ldr	x0, .LC927
	add	x0, x0, 1808
	ldr	w1, [x0, w20, sxtw 2]
	cmp	w1, 1
	beq	.L1954
.L1956:
	str	w19, [x0, w20, sxtw 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1958:
	mov	w0, 0
.L1948:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1950:
	ldr	x1, .LC927
	mov	w0, 0
	add	x1, x1, 1808
	str	wzr, [x1, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1949:
	ldr	x0, .LC927
	add	x0, x0, 1808
	ldr	w1, [x0, w20, sxtw 2]
	cbz	w1, .L1956
.L1954:
	mov	w0, -1
	b	.L1948
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	3
.LC927:
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
	beq	.L1960
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_AddMemRecord
.L1960:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L1961
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_AddMemRecord
.L1961:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L1959
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_AddMemRecord
.L1959:
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
	ldr	x21, .LC929
	ldr	w4, [x20, 12]
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 294912
	add	x0, x0, 290816
	ldr	w5, [x1, 600]
	cmp	w5, w4
	beq	.L1973
	ldr	w2, [x0, 1120]
	cbz	w2, .L2002
.L1973:
	ldr	w0, [x0, 3512]
	cbz	w0, .L1975
	ldr	w0, [x1, 632]
	cbz	w0, .L2003
.L1975:
	ldr	x22, .LC935
	mov	w0, 8
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x4, [x21, w19, sxtw 3]
	add	x2, x4, 290816
	ldr	w0, [x2, 1152]
	cmp	w0, 255
	beq	.L1983
	add	x2, x2, 1224
	mov	x1, 1
	b	.L1977
	.p2align 3
.L2005:
	add	w1, w1, 1
	cmp	w1, 32
	beq	.L2004
.L1977:
	ldr	w3, [x2]
	add	x2, x2, 72
	cmp	w3, 255
	bne	.L2005
.L1976:
	lsl	x0, x1, 6
	ldr	x3, [x22, 104]
	add	x0, x0, x1, lsl 3
	mov	x2, 72
	add	x0, x0, 290816
	mov	x1, x20
	add	x0, x0, 1152
	add	x0, x4, x0
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x20
	add	x1, x1, 294912
	ldr	w2, [x1, 632]
	add	w2, w2, 1
	str	w2, [x1, 632]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 294912
	ldr	w0, [x0, 636]
	cbnz	w0, .L2006
.L1981:
	mov	w19, 0
.L1980:
	ldr	x1, [x22, 32]
	mov	w0, 8
	blr	x1
	mov	w0, w19
.L1996:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2003:
	ldr	w5, [x20, 8]
	cmp	w5, 255
	bne	.L1975
	ldr	x2, .LC930
	mov	w4, 0
	ldr	x1, .LC934
	mov	w3, 9091
	add	x2, x2, 840
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1996
	.p2align 3
.L2004:
	ldr	x2, .LC930
	ldr	x1, .LC939
.L1999:
	mov	w3, w19
	add	x2, x2, 840
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1980
	.p2align 3
.L2006:
	mov	x1, x20
	mov	w0, w19
	bl	FSP_SetSingleFrameBuf
	cbz	w0, .L1981
	ldr	x2, .LC930
	ldr	x1, .LC937
	b	.L1999
.L1983:
	mov	x1, 0
	b	.L1976
.L2002:
	ldr	x2, .LC930
	mov	w3, 9081
	ldr	x1, .LC932
	mov	w0, 1
	add	x2, x2, 840
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1996
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	3
.LC929:
	.xword	.LANCHOR0
	.align	3
.LC930:
	.xword	.LANCHOR4
	.align	3
.LC932:
	.xword	.LC931
	.align	3
.LC934:
	.xword	.LC933
	.align	3
.LC935:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC937:
	.xword	.LC936
	.align	3
.LC939:
	.xword	.LC938
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
	ldr	x21, .LC940
	add	x3, x21, 1808
	ldr	w0, [x3, w19, sxtw 2]
	cbz	w0, .L2016
	ldr	x2, .LC947
	mov	w3, w19
	ldr	x1, .LC949
	mov	w0, 0
	add	x2, x2, 872
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2016:
	ldr	x4, .LC941
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
	cbnz	w0, .L2009
	ldr	x0, .LC942
	ldr	x0, [x0, w19, sxtw 3]
	add	x2, x0, 262144
.L2010:
	ldr	x1, .LC946
	add	x21, x21, 1808
	mov	w3, 2
	mov	w0, 31
	str	w3, [x2, 2032]
	bl	dprint_vfmw
	str	wzr, [x21, w19, sxtw 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2009:
	ldr	x22, .LC942
	ldr	x0, [x22, w19, sxtw 3]
	add	x1, x0, 290816
	add	x2, x0, 262144
	ldr	w0, [x1, 1124]
	cbz	w0, .L2010
	ldr	x1, .LC944
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	mov	w1, 3
	add	x2, x0, 262144
	str	w1, [x2, 2032]
	b	.L2010
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	3
.LC940:
	.xword	.LANCHOR6
	.align	3
.LC941:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC942:
	.xword	.LANCHOR0
	.align	3
.LC944:
	.xword	.LC943
	.align	3
.LC946:
	.xword	.LC945
	.align	3
.LC947:
	.xword	.LANCHOR4
	.align	3
.LC949:
	.xword	.LC948
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
	ldr	x0, .LC951
	ldr	x0, [x0, w19, sxtw 3]
	add	x0, x0, 294912
	ldr	w1, [x0, 1232]
	cmp	w1, 2
	beq	.L2019
	cmp	w1, 16
	beq	.L2020
	cbz	w1, .L2025
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2025:
	add	x0, x0, 1240
	bl	H264DEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2020:
	add	x0, x0, 1240
	bl	HEVCDEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2019:
	add	x0, x0, 1240
	bl	MPEG4DEC_GetImageWidth
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetImageWidth, .-VCTRL_GetImageWidth
	.align	3
.LC951:
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
	ldr	x0, .LC952
	ldr	x0, [x0, w19, sxtw 3]
	add	x0, x0, 294912
	ldr	w1, [x0, 1232]
	cmp	w1, 2
	beq	.L2028
	cmp	w1, 16
	beq	.L2029
	cbz	w1, .L2034
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2034:
	add	x0, x0, 1240
	bl	H264DEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2029:
	add	x0, x0, 1240
	bl	HEVCDEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2028:
	add	x0, x0, 1240
	bl	MPEG4DEC_GetImageHeight
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetImageHeight, .-VCTRL_GetImageHeight
	.align	3
.LC952:
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
	ldr	x3, .LC953
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC954
	ldr	x6, [x0, 104]
	cbz	x6, .L2036
	ldr	x4, .LC955
	add	x5, x29, 56
	mov	w3, 0
	mov	w2, w21
	mov	w1, w20
	mov	w0, w19
	ldr	x4, [x4, w19, sxtw 3]
	add	x4, x4, 294912
	ldr	w4, [x4, 1232]
	blr	x6
.L2036:
	ldr	w0, [x29, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	3
.LC953:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC954:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC955:
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
	ldr	x0, .LC956
	mov	w1, 1
	add	x0, x0, 2216
	str	w1, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	3
.LC956:
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
	ldr	x0, .LC958
	add	x0, x0, 2216
	str	wzr, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	3
.LC958:
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
	ldr	x0, .LC960
	add	x0, x0, 2216
	ldr	w0, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
	.align	3
.LC960:
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
	.type	__func__.51948, %object
	.size	__func__.51948, 18
__func__.51948:
	.string	"VCTRL_EventReport"
	.zero	6
	.type	__func__.51884, %object
	.size	__func__.51884, 20
__func__.51884:
	.string	"VCTRL_RecordPosTime"
	.zero	4
	.type	__func__.51889, %object
	.size	__func__.51889, 17
__func__.51889:
	.string	"VCTRL_RecordData"
	.zero	7
	.type	__func__.51960, %object
	.size	__func__.51960, 18
__func__.51960:
	.string	"VCTRL_SetCallBack"
	.zero	6
	.type	__FUNCTION__.52066, %object
	.size	__FUNCTION__.52066, 29
__FUNCTION__.52066:
	.string	"VCTRL_PartitionMemForStdUser"
	.zero	3
	.type	__func__.52090, %object
	.size	__func__.52090, 23
__func__.52090:
	.string	"VCTRL_FreeChanResource"
	.zero	1
	.type	__func__.52344, %object
	.size	__func__.52344, 25
__func__.52344:
	.string	"VCTRL_TryToRelSpecialFrm"
	.zero	7
	.type	__func__.52361, %object
	.size	__func__.52361, 19
__func__.52361:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.52369, %object
	.size	__FUNCTION__.52369, 19
__FUNCTION__.52369:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.52379, %object
	.size	__FUNCTION__.52379, 23
__FUNCTION__.52379:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.52380, %object
	.size	__func__.52380, 23
__func__.52380:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.52413, %object
	.size	__func__.52413, 18
__func__.52413:
	.string	"VCTRL_GetDecParam"
	.align	3
.LANCHOR4 = . + 0
	.type	__FUNCTION__.52538, %object
	.size	__FUNCTION__.52538, 19
__FUNCTION__.52538:
	.string	"VCTRL_FlushDecoder"
	.zero	5
	.type	__FUNCTION__.52828, %object
	.size	__FUNCTION__.52828, 18
__FUNCTION__.52828:
	.string	"GetExtraRefFrmNum"
	.zero	6
	.type	__FUNCTION__.52834, %object
	.size	__FUNCTION__.52834, 19
__FUNCTION__.52834:
	.string	"GetExtraDispFrmNum"
	.zero	5
	.type	__FUNCTION__.52840, %object
	.size	__FUNCTION__.52840, 16
__FUNCTION__.52840:
	.string	"GetExtraCtrlCmd"
	.type	__FUNCTION__.52778, %object
	.size	__FUNCTION__.52778, 14
__FUNCTION__.52778:
	.string	"DecChanSyntax"
	.zero	2
	.type	__func__.52808, %object
	.size	__func__.52808, 20
__func__.52808:
	.string	"VCTRL_GetChanImgNum"
	.zero	4
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
	.type	__func__.52174, %object
	.size	__func__.52174, 18
__func__.52174:
	.string	"VCTRL_DestroyChan"
	.zero	6
	.type	__func__.53227, %object
	.size	__func__.53227, 30
__func__.53227:
	.string	"VCTRL_SetSingleFrameBufToChan"
	.zero	2
	.type	__func__.53239, %object
	.size	__func__.53239, 24
__func__.53239:
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
.LC672:
	ASCII(.string	"%s not support std %d\n" )
	.zero	1
.LC676:
	ASCII(.string	"ChanID out of range!" )
	.zero	3
.LC679:
	ASCII(.string	"pstChanState = NULL" )
	.zero	4
.LC682:
	ASCII(.string	"s_pstVfmwChan = NULL" )
	.zero	3
.LC699:
	ASCII(.string	"SetVdecExtra ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	1
.LC701:
	ASCII(.string	"SetVdecExtra ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
.LC710:
	ASCII(.string	"Command \"%d\" not registerd!\n" )
	.zero	3
.LC726:
	ASCII(.string	"Chan %d Report Last Frame, Value=%d, LastFrameState=%d\n" )
.LC730:
	ASCII(.string	"Last frame output failed!\n" )
	.zero	5
.LC732:
	ASCII(.string	"Last frame output successed!\n" )
	.zero	2
.LC734:
	ASCII(.string	"Last frame already output, image id: %d!\n" )
	.zero	6
.LC746:
	ASCII(.string	"line %d can not know YuvFormat = %d\n" )
	.zero	3
.LC748:
	ASCII(.string	"userdec frame(phy=%#x) address error!\n" )
	.zero	1
.LC750:
	ASCII(.string	"can not map vir addr for usrdat frame(cbphy=%#x)\n" )
	.zero	6
.LC752:
	ASCII(.string	"line: %d, pLogic is Null!\n" )
	.zero	5
.LC755:
	ASCII(.string	"eYuvFormat %d is not support!!\n" )
.LC761:
	ASCII(.string	"pUsrdecFrame == NULL" )
	.zero	3
.LC763:
	ASCII(.string	"VCTRL_PutUsrdecFrame: VidStd is %d\n" )
	.zero	4
.LC766:
	ASCII(.string	"VCTRL_PutUsrdecFrame return err\n" )
	.zero	7
.LC768:
	ASCII(.string	"L:%d ChanID out of range\n" )
	.zero	6
.LC771:
	ASCII(.string	"L:%d This Chan has not been created!!!\n" )
.LC773:
	ASCII(.string	"L:%d WARNING: vidio std not setted!\n" )
	.zero	3
.LC784:
	ASCII(.string	"WARNING: vidio std not setted!" )
	.zero	1
.LC794:
	ASCII(.string	"start chan %d: VCTRL_StartChan return %d\n" )
	.zero	6
.LC804:
	ASCII(.string	"This Chan has not been created or has been destroyed !" )
	.zero	1
.LC807:
	ASCII(.string	"VCTRL_StopChanWithCheck fail!\n" )
	.zero	1
.LC812:
	ASCII(.string	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\n" )
	.zero	6
.LC816:
	ASCII(.string	"-------------------------------------------------------------------------\n" )
	.zero	5
.LC830:
	ASCII(.string	"Param Invalid of PChanOption is NULL\n" )
	.zero	2
.LC833:
	ASCII(.string	"line %d VCTRL_GetChanMemSize failed!\n" )
	.zero	2
.LC835:
	ASCII(.string	"L: %d : part we can NOT alloc buffer for channel context\n" )
	.zero	6
.LC837:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel context\n" )
	.zero	6
.LC839:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh\n" )
	.zero	2
.LC841:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh, %#x < %#x\n" )
	.zero	7
.LC843:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel scd\n" )
	.zero	2
.LC845:
	ASCII(.string	"L: %d : can NOT alloc buffer for SCD\n" )
	.zero	2
.LC848:
	ASCII(.string	"vfmw have max(%d) channels opened, can NOT create more channels\n" )
	.zero	7
.LC851:
	ASCII(.string	"Chan:%d can NOT enable FSP instance\n" )
	.zero	3
.LC859:
	ASCII(.string	"VCTRL_CheckChanWH return err.\n" )
	.zero	1
.LC862:
	ASCII(.string	"VFMW didn't support std %d.\n" )
	.zero	3
.LC864:
	ASCII(.string	"VCTRL_ConfigChan with same config paramater.\n" )
	.zero	2
.LC868:
	ASCII(.string	"can NOT VCTRL_PartitionMemForStdUser\n" )
	.zero	2
.LC874:
	ASCII(.string	"chan %d: new StrmOFThr = %d\n" )
	.zero	3
.LC877:
	ASCII(.string	"chan %d: new DecMode = %d\n" )
	.zero	5
.LC880:
	ASCII(.string	"chan %d: GetChanCfg failed!\n" )
	.zero	3
.LC882:
	ASCII(.string	"chan %d: new DecOrderOutput = %d\n" )
	.zero	6
.LC885:
	ASCII(.string	"chan %d: new ChanErrThr = %d\n" )
	.zero	2
.LC888:
	ASCII(.string	"reset chan %d: VCTRL_ResetChan return %d\n" )
	.zero	6
.LC893:
	ASCII(.string	"%s:L%d: %s\n" )
	.zero	4
.LC896:
	ASCII(.string	"This Chan has not been created or has been destroyed !!!" )
	.zero	7
.LC898:
	ASCII(.string	"can NOT stop a not-opened Chan" )
	.zero	1
.LC909:
	ASCII(.string	"stop chan %d: VCTRL_StopChan return %d\n" )
.LC919:
	ASCII(.string	"WARNNING: dsp in lowdelay state, we can not supported  avs in the same time!!!\n" )
.LC921:
	ASCII(.string	"WARNNING: dsp in avs state, we can not supported  lowdelay in the same time!!!\n" )
.LC931:
	ASCII(.string	"%s, %d, actul size = 0x%x, except size= 0x%x\n" )
	.zero	2
.LC933:
	ASCII(.string	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\n" )
	.zero	1
.LC936:
	ASCII(.string	"%s: Chan %d set single frame failed!\n" )
	.zero	2
.LC938:
	ASCII(.string	"%s: Chan %d no frame buffer store!\n" )
	.zero	4
.LC943:
	ASCII(.string	"DFS, request frame store fail!, chanid: %d\n" )
	.zero	4
.LC945:
	ASCII(.string	"DFS, set decoding thread state to success!\n " )
	.zero	3
.LC948:
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
	.type	save_file_cnt.52969, %object
	.size	save_file_cnt.52969, 4
save_file_cnt.52969:
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
	.type	save_file_cnt.52963, %object
	.size	save_file_cnt.52963, 4
save_file_cnt.52963:
	.zero	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.zero	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 256
vfmw_save_metadata_file:
	.zero	256
	.type	save_file_cnt.52957, %object
	.size	save_file_cnt.52957, 4
save_file_cnt.52957:
	.zero	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.zero	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 256
vfmw_save_seg_file:
	.zero	256
	.type	save_file_cnt.52935, %object
	.size	save_file_cnt.52935, 4
save_file_cnt.52935:
	.zero	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.zero	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 256
vfmw_save_str_file:
	.zero	256
	.type	save_file_cnt.52929, %object
	.size	save_file_cnt.52929, 4
save_file_cnt.52929:
	.zero	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.zero	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 256
vfmw_save_yuv_file:
	.zero	256
	.type	save_file_cnt.52942, %object
	.size	save_file_cnt.52942, 4
save_file_cnt.52942:
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
	.type	FspInstInfo.52062, %object
	.size	FspInstInfo.52062, 2824
FspInstInfo.52062:
	.zero	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.52366, %object
	.size	last_rec_pos_time.52366, 128
last_rec_pos_time.52366:
	.zero	128
	.type	last_rec_pos_time.52376, %object
	.size	last_rec_pos_time.52376, 128
last_rec_pos_time.52376:
	.zero	128
	.type	MemArrange.52655, %object
	.size	MemArrange.52655, 1232
MemArrange.52655:
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
	.type	last_rec_pos_time.52773, %object
	.size	last_rec_pos_time.52773, 128
last_rec_pos_time.52773:
	.zero	128
	.type	last_rec_pos_decparam_time.52774, %object
	.size	last_rec_pos_decparam_time.52774, 128
last_rec_pos_decparam_time.52774:
	.zero	128
	.type	ChanPriTab.52723, %object
	.size	ChanPriTab.52723, 128
ChanPriTab.52723:
	.zero	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 9600
g_VfmwChanStat:
	.zero	9600
	.type	PrioArray.52179, %object
	.size	PrioArray.52179, 128
PrioArray.52179:
	.zero	128
	.type	pOption, %object
	.size	pOption, 8
pOption:
	.zero	8
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.zero	128
	.type	Capability.52235, %object
	.size	Capability.52235, 148
Capability.52235:
	.zero	148
	.zero	4
	.type	PrioArray.52234, %object
	.size	PrioArray.52234, 128
PrioArray.52234:
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
