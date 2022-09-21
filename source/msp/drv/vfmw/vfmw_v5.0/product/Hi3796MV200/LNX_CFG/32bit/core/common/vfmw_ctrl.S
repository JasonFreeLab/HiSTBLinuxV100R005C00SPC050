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
	.file	"vfmw_ctrl.c"
	.text
	.align	2
	.type	VfmwProc_SetPrintLevel, %function
VfmwProc_SetPrintLevel:
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
	ldr	r3, .L2
	ldr	r2, [r0]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	VfmwProc_SetPrintLevel, .-VfmwProc_SetPrintLevel
	.align	2
	.type	VfmwProc_OpenScdLowdly, %function
VfmwProc_OpenScdLowdly:
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
	ldr	r3, .L5
	mov	r2, #1
	ldr	r1, [r0]
	ldr	r3, [r3, r1, asl #3]
	str	r2, [r3, #40]
	ldmfd	sp, {fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	s_SmIIS
	UNWIND(.fnend)
	.size	VfmwProc_OpenScdLowdly, .-VfmwProc_OpenScdLowdly
	.align	2
	.type	VfmwProc_CloseScdLowdly, %function
VfmwProc_CloseScdLowdly:
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
	ldr	r3, .L8
	mov	r2, #0
	ldr	r1, [r0]
	ldr	r3, [r3, r1, asl #3]
	str	r2, [r3, #40]
	ldmfd	sp, {fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	s_SmIIS
	UNWIND(.fnend)
	.size	VfmwProc_CloseScdLowdly, .-VfmwProc_CloseScdLowdly
	.align	2
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
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
	cmp	r0, #31
	bhi	.L22
	ldr	lr, .L26
	ldr	ip, [lr, r0, asl #2]
	cmp	ip, #0
	beq	.L23
	ldr	ip, [ip, #32]
	cmp	ip, #0
	beq	.L15
	cmp	ip, #1
	bne	.L24
	ldr	r3, [lr, #372]
	cmp	r3, #0
	beq	.L25
.L18:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L24:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, ip
	ldr	r2, .L26+4
	ldr	r1, .L26+8
	bl	dprint_vfmw
.L12:
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L15:
	ldr	r3, [lr, #368]
	cmp	r3, #0
	bne	.L18
	mov	r0, r3
	ldr	r1, .L26+12
	bl	dprint_vfmw
	b	.L12
.L25:
	mov	r0, r3
	ldr	r1, .L26+16
	bl	dprint_vfmw
	b	.L12
.L22:
	ldr	r3, .L26+20
	mov	r2, #980
	ldr	r1, .L26+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L12
.L23:
	mov	r0, ip
	ldr	r3, .L26+28
	movw	r2, #981
	ldr	r1, .L26+24
	bl	dprint_vfmw
	b	.L12
.L27:
	.align	2
.L26:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	.LC5
	.word	.LC3
	.word	.LC4
	.word	.LC0
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_EventReport, .-VCTRL_EventReport
	.align	2
	.type	VfmwProc_SetStandardObedience, %function
VfmwProc_SetStandardObedience:
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
	ldr	ip, .L29
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L29+4
	mov	r2, r3
	str	r3, [ip, #392]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L30:
	.align	2
.L29:
	.word	.LANCHOR0
	.word	.LC6
	UNWIND(.fnend)
	.size	VfmwProc_SetStandardObedience, .-VfmwProc_SetStandardObedience
	.align	2
	.type	VfmwProc_SetClkSelect, %function
VfmwProc_SetClkSelect:
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
	ldr	r3, [r0]
	ldr	r2, .L35
	cmp	r3, #4
	strls	r3, [r2]
	ldmlsfd	sp, {fp, sp, pc}
	ldr	r1, .L35+4
	mov	r0, #32
	ldr	r2, [r2]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L36:
	.align	2
.L35:
	.word	.LANCHOR2
	.word	.LC7
	UNWIND(.fnend)
	.size	VfmwProc_SetClkSelect, .-VfmwProc_SetClkSelect
	.align	2
	.type	VfmwProc_SetCompressPara, %function
VfmwProc_SetCompressPara:
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
	ldr	ip, .L81
	ldr	r5, [r0, #4]
	mov	r3, r0
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #52
	ldr	ip, [ip, #48]
	ldr	r4, [r3]
	ldr	r7, [r3, #8]
	ldr	r8, [r3, #12]
	ldr	r6, [r3, #16]
	blx	ip
	cmp	r5, #0
	beq	.L73
	cmp	r7, #0
	beq	.L74
	movw	r3, #625
	cmp	r8, r3
	mov	r3, #1
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L68
	bls	.L75
	movw	r3, #750
	cmp	r8, r3
	beq	.L46
	movw	r3, #875
	cmp	r8, r3
	moveq	r3, #3
	streq	r3, [fp, #-44]
.L48:
	movw	r3, #625
	cmp	r6, r3
	beq	.L50
.L80:
	bls	.L76
	movw	r3, #750
	cmp	r6, r3
	moveq	r3, #2
	streq	r3, [fp, #-40]
	beq	.L49
	movw	r3, #875
	cmp	r6, r3
	moveq	r3, #3
	streq	r3, [fp, #-40]
	b	.L49
.L74:
	mvn	r3, #0
	mov	r2, #1
	str	r7, [fp, #-48]
	str	r2, [fp, #-52]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
.L49:
	ldr	r1, [fp, #-48]
	cmp	r1, #1
	beq	.L77
	cmp	r1, #0
	beq	.L78
.L39:
	mov	r2, r4
	ldr	r1, .L81+4
	mov	r0, #32
	bl	dprint_vfmw
.L56:
	ldr	r3, .L81+8
	ldr	r2, [r3, r4, asl #2]
	cmp	r2, #0
	beq	.L79
.L57:
	mov	r2, r4
	ldr	r1, .L81+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L73:
	mvn	r3, #0
	str	r5, [fp, #-52]
	str	r5, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	b	.L39
.L75:
	cmp	r8, #500
	moveq	r3, #0
	streq	r3, [fp, #-44]
	movw	r3, #625
	cmp	r6, r3
	bne	.L80
.L50:
	mov	r3, #1
	str	r3, [fp, #-40]
	b	.L49
.L76:
	cmp	r6, #500
	moveq	r3, #0
	streq	r3, [fp, #-40]
	b	.L49
.L46:
	mov	r3, #2
.L68:
	str	r3, [fp, #-44]
	b	.L48
.L78:
	str	r1, [sp]
	mov	r3, #1
	mov	r2, r4
	ldr	r1, .L81+16
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L81+8
	ldr	r2, [r3, r4, asl #2]
	cmp	r2, #0
	bne	.L57
.L79:
	ldr	lr, [fp, #-44]
	add	r3, r3, r4, lsl #4
	ldr	ip, [fp, #-40]
	mov	r2, r4
	ldr	r6, [fp, #-52]
	mov	r0, #32
	ldr	r5, [fp, #-48]
	str	lr, [r3, #404]
	str	ip, [r3, #408]
	str	r6, [r3, #396]
	str	r5, [r3, #400]
	ldr	r1, .L81+20
	bl	dprint_vfmw
	ldr	r2, [fp, #-52]
	ldr	r1, .L81+24
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	ldr	r1, .L81+28
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [fp, #-40]
	ldr	r2, [fp, #-44]
	mov	r0, #32
	ldr	r1, .L81+32
	bl	dprint_vfmw
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L77:
	mov	r3, r1
	str	r1, [sp]
	str	r6, [sp, #8]
	mov	r2, r4
	str	r8, [sp, #4]
	mov	r0, #32
	ldr	r1, .L81+36
	bl	dprint_vfmw
	b	.L56
.L82:
	.align	2
.L81:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LANCHOR0
	.word	.LC15
	.word	.LC9
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC8
	UNWIND(.fnend)
	.size	VfmwProc_SetCompressPara, .-VfmwProc_SetCompressPara
	.align	2
	.type	VfmwProc_SetTunnelLineNumber, %function
VfmwProc_SetTunnelLineNumber:
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
	ldr	ip, .L84
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L84+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L85:
	.align	2
.L84:
	.word	g_TunnelLineNumber
	.word	.LC16
	UNWIND(.fnend)
	.size	VfmwProc_SetTunnelLineNumber, .-VfmwProc_SetTunnelLineNumber
	.align	2
	.type	VfmwProc_SetSaveYuvBitWidth, %function
VfmwProc_SetSaveYuvBitWidth:
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
	ldr	r3, [r0]
	bic	r2, r3, #2
	cmp	r2, #8
	bne	.L88
	ldr	ip, .L89
	mov	r2, r3
	ldr	r1, .L89+4
	mov	r0, #32
	str	r3, [ip, #4]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L88:
	mov	r2, r3
	ldr	r1, .L89+8
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L90:
	.align	2
.L89:
	.word	.LANCHOR2
	.word	.LC18
	.word	.LC17
	UNWIND(.fnend)
	.size	VfmwProc_SetSaveYuvBitWidth, .-VfmwProc_SetSaveYuvBitWidth
	.align	2
	.type	VfmwProc_SetTraceImgPeriod, %function
VfmwProc_SetTraceImgPeriod:
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
	ldr	ip, .L92
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L92+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L93:
	.align	2
.L92:
	.word	g_TraceImgPeriod
	.word	.LC19
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceImgPeriod, .-VfmwProc_SetTraceImgPeriod
	.align	2
	.type	VfmwProc_SetTraceFramePeriod, %function
VfmwProc_SetTraceFramePeriod:
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
	ldr	ip, .L95
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L95+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L96:
	.align	2
.L95:
	.word	g_TraceFramePeriod
	.word	.LC20
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceFramePeriod, .-VfmwProc_SetTraceFramePeriod
	.align	2
	.type	VfmwProc_SetTraceBSPeriod, %function
VfmwProc_SetTraceBSPeriod:
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
	ldr	ip, .L98
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L98+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L99:
	.align	2
.L98:
	.word	g_TraceBsPeriod
	.word	.LC21
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceBSPeriod, .-VfmwProc_SetTraceBSPeriod
	.align	2
	.type	VfmwProc_SetTraceCtrl, %function
VfmwProc_SetTraceCtrl:
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
	ldr	ip, .L101
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L101+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L102:
	.align	2
.L101:
	.word	g_TraceCtrl
	.word	.LC22
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceCtrl, .-VfmwProc_SetTraceCtrl
	.align	2
	.type	VfmwProc_TestStopDec, %function
VfmwProc_TestStopDec:
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
	ldr	ip, .L104
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L104+4
	mov	r2, r3
	str	r3, [ip, #908]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L105:
	.align	2
.L104:
	.word	.LANCHOR0
	.word	.LC23
	UNWIND(.fnend)
	.size	VfmwProc_TestStopDec, .-VfmwProc_TestStopDec
	.align	2
	.type	VfmwProc_TestTimeSequence, %function
VfmwProc_TestTimeSequence:
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
	ldr	ip, .L107
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L107+4
	mov	r2, r3
	str	r3, [ip, #912]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L108:
	.align	2
.L107:
	.word	.LANCHOR0
	.word	.LC24
	UNWIND(.fnend)
	.size	VfmwProc_TestTimeSequence, .-VfmwProc_TestTimeSequence
	.align	2
	.type	VfmwProc_SaveEL, %function
VfmwProc_SaveEL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L109
	ldr	r6, .L115
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #916]
	cmp	r7, #0
	beq	.L114
	ldr	r1, .L115+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L115+8
	ldr	r0, [r5, #916]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #916]
.L109:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L114:
	ldr	r2, [r6, #1044]
	mov	r1, #50
	ldr	r8, .L115+8
	sub	r0, fp, #88
	add	ip, r2, #1
	ldr	r3, .L115+12
	str	r2, [sp]
	ldr	r9, [r8, #68]
	ldr	r2, .L115+16
	str	ip, [r6, #1044]
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1048]
	cmp	r0, #0
	str	r0, [r5, #916]
	beq	.L112
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L115+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L109
.L112:
	sub	r2, fp, #88
	ldr	r1, .L115+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L109
.L116:
	.align	2
.L115:
	.word	.LANCHOR0
	.word	.LC28
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC25
	.word	.LC26
	.word	.LC27
	UNWIND(.fnend)
	.size	VfmwProc_SaveEL, .-VfmwProc_SaveEL
	.align	2
	.type	VfmwProc_SetCurProcChan, %function
VfmwProc_SetCurProcChan:
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
	ldr	r3, [r0]
	cmp	r3, #32
	bhi	.L119
	ldr	ip, .L120
	mov	r2, r3
	ldr	r1, .L120+4
	mov	r0, #32
	str	r3, [ip, #1052]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L119:
	mov	r2, r3
	ldr	r1, .L120+8
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L121:
	.align	2
.L120:
	.word	.LANCHOR0
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VfmwProc_SetCurProcChan, .-VfmwProc_SetCurProcChan
	.align	2
	.type	VfmwProc_SetSaveFileAfterReset, %function
VfmwProc_SetSaveFileAfterReset:
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
	ldr	r3, [r0]
	cmp	r3, #1
	bls	.L124
	mov	r2, r3
	ldr	r1, .L125
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L124:
	ldr	ip, .L125+4
	mov	r2, r3
	ldr	r1, .L125+8
	mov	r0, #32
	str	r3, [ip, #1056]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L126:
	.align	2
.L125:
	.word	.LC32
	.word	.LANCHOR0
	.word	.LC31
	UNWIND(.fnend)
	.size	VfmwProc_SetSaveFileAfterReset, .-VfmwProc_SetSaveFileAfterReset
	.align	2
	.type	VfmwProc_SetUSE_FF_APT_EN, %function
VfmwProc_SetUSE_FF_APT_EN:
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
	ldr	r3, [r0]
	cmp	r3, #1
	bls	.L129
	mov	r2, r3
	ldr	r1, .L130
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L129:
	ldr	ip, .L130+4
	mov	r2, r3
	ldr	r1, .L130+8
	mov	r0, #32
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L131:
	.align	2
.L130:
	.word	.LC34
	.word	USE_FF_APT_EN
	.word	.LC33
	UNWIND(.fnend)
	.size	VfmwProc_SetUSE_FF_APT_EN, .-VfmwProc_SetUSE_FF_APT_EN
	.align	2
	.type	VfmwProc_SetVp9DecFrameNum, %function
VfmwProc_SetVp9DecFrameNum:
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
	ldr	ip, .L133
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L133+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L134:
	.align	2
.L133:
	.word	g_CfgVp9FrmNum
	.word	.LC35
	UNWIND(.fnend)
	.size	VfmwProc_SetVp9DecFrameNum, .-VfmwProc_SetVp9DecFrameNum
	.align	2
	.type	VfmwProc_SetDefaultOutputOrder, %function
VfmwProc_SetDefaultOutputOrder:
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
	ldr	r4, [r0]
	cmp	r4, #7
	mov	r2, r4
	bhi	.L137
	ldr	r1, .L138
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L138+4
	str	r4, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L137:
	ldr	r1, .L138+8
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L139:
	.align	2
.L138:
	.word	.LC37
	.word	.LANCHOR2
	.word	.LC36
	UNWIND(.fnend)
	.size	VfmwProc_SetDefaultOutputOrder, .-VfmwProc_SetDefaultOutputOrder
	.align	2
	.global	VCTRL_Isr_0
	.type	VCTRL_Isr_0, %function
VCTRL_Isr_0:
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
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_0, .-VCTRL_Isr_0
	.align	2
	.global	VCTRL_Scd_Isr
	.type	VCTRL_Scd_Isr, %function
VCTRL_Scd_Isr:
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
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr, .-VCTRL_Scd_Isr
	.align	2
	.global	VCTRL_MMU_ISR
	.type	VCTRL_MMU_ISR, %function
VCTRL_MMU_ISR:
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
	bl	VDMDRV_MMUIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_MMU_ISR, .-VCTRL_MMU_ISR
	.align	2
	.type	VfmwProc_SaveReorderMetadata, %function
VfmwProc_SaveReorderMetadata:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L143
	ldr	r6, .L149
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1060]
	cmp	r7, #0
	beq	.L148
	ldr	r1, .L149+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L149+8
	ldr	r0, [r5, #1060]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1060]
.L143:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L148:
	ldr	r8, .L149+8
	mov	r0, #24
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1188]
	mov	r1, #50
	ldr	r3, .L149+12
	add	ip, r2, #1
	str	ip, [r6, #1188]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1192]
	cmp	r0, #0
	str	r0, [r5, #1060]
	beq	.L146
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L149+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L143
.L146:
	sub	r2, fp, #88
	ldr	r1, .L149+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L143
.L150:
	.align	2
.L149:
	.word	.LANCHOR0
	.word	.LC40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC38
	.word	.LC39
	UNWIND(.fnend)
	.size	VfmwProc_SaveReorderMetadata, .-VfmwProc_SaveReorderMetadata
	.align	2
	.type	VfmwProc_SaveMetadata, %function
VfmwProc_SaveMetadata:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bls	.L157
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	ldr	r5, .L159
	mov	r1, r4
	ldr	r7, .L159+4
	mov	r0, #2
	add	r6, r7, r4, lsl #2
	ldr	r3, [r5, #24]
	blx	r3
	ldr	r8, [r6, #1196]
	cmp	r8, #0
	beq	.L158
	ldr	r1, .L159+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [r5, #36]
	ldr	r0, [r6, #1196]
	blx	r3
	mov	r3, #0
	str	r3, [r6, #1196]
.L156:
	ldr	r3, [r5, #28]
	mov	r1, r4
	mov	r0, #2
	blx	r3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L158:
	mov	r0, #23
	ldr	r9, [r5, #68]
	bl	VFMW_GetString
	ldr	r2, [r7, #1324]
	ldr	r3, .L159+12
	mov	r1, #50
	add	ip, r2, #1
	str	ip, [r7, #1324]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	mov	r2, r8
	sub	r0, fp, #88
	ldr	r3, [r5, #32]
	mov	r1, #66
	blx	r3
	sub	r2, fp, #88
	str	r4, [r7, #1328]
	cmp	r0, #0
	str	r0, [r6, #1196]
	beq	.L154
	mov	r3, r4
	ldr	r1, .L159+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L156
.L154:
	ldr	r1, .L159+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L156
.L160:
	.align	2
.L159:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC40
	.word	.LANCHOR2+8
	.word	.LC41
	.word	.LC42
	UNWIND(.fnend)
	.size	VfmwProc_SaveMetadata, .-VfmwProc_SaveMetadata
	.align	2
	.type	VfmwProc_Save1DYUV, %function
VfmwProc_Save1DYUV:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, .L168
	ldmia	r0, {r5, r7}
	mov	r3, r0
	ldr	r8, [r3, #8]
	ldr	r1, [r4, #204]
	mov	r0, r5
	blx	r1
	subs	r6, r0, #0
	beq	.L167
	mov	r0, #22
	ldr	r9, [r4, #68]
	bl	VFMW_GetString
	str	r5, [sp]
	mov	r1, #50
	ldr	r3, .L168+4
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	sub	r0, fp, #88
	ldr	r3, [r4, #32]
	mov	r2, #0
	mov	r1, #66
	blx	r3
	subs	r5, r0, #0
	beq	.L164
	ldr	r3, .L168+8
	ldr	ip, [r3, #148]
	cmp	ip, #0
	beq	.L165
	mov	lr, #1
	mov	r3, r8
	mov	r2, r7
	mov	r1, r6
	str	lr, [sp]
	blx	ip
.L166:
	mov	r0, r5
	ldr	r3, [r4, #36]
	blx	r3
	sub	r2, fp, #88
	ldr	r1, .L168+12
	mov	r0, #32
	bl	dprint_vfmw
.L163:
	ldr	r3, [r4, #156]
	mov	r0, r6
	blx	r3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L165:
	mov	r0, ip
	movw	r2, #7391
	ldr	r1, .L168+16
	bl	dprint_vfmw
	b	.L166
.L167:
	mov	r2, r5
	ldr	r1, .L168+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L163
.L164:
	sub	r2, fp, #88
	ldr	r1, .L168+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L163
.L169:
	.align	2
.L168:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	g_vdm_hal_fun_ptr
	.word	.LC45
	.word	.LC44
	.word	.LC43
	.word	.LC46
	UNWIND(.fnend)
	.size	VfmwProc_Save1DYUV, .-VfmwProc_Save1DYUV
	.align	2
	.type	VfmwProc_SaveSeg, %function
VfmwProc_SaveSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L170
	ldr	r6, .L176
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1332]
	cmp	r7, #0
	beq	.L175
	ldr	r1, .L176+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L176+8
	ldr	r0, [r5, #1332]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1332]
.L170:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L175:
	ldr	r8, .L176+8
	mov	r0, #19
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1460]
	mov	r1, #50
	ldr	r3, .L176+12
	add	ip, r2, #1
	str	ip, [r6, #1460]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1464]
	cmp	r0, #0
	str	r0, [r5, #1332]
	beq	.L173
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L176+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L170
.L173:
	sub	r2, fp, #88
	ldr	r1, .L176+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L170
.L177:
	.align	2
.L176:
	.word	.LANCHOR0
	.word	.LC49
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC47
	.word	.LC48
	UNWIND(.fnend)
	.size	VfmwProc_SaveSeg, .-VfmwProc_SaveSeg
	.align	2
	.type	VfmwProc_Savestream, %function
VfmwProc_Savestream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L178
	ldr	r6, .L184
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1468]
	cmp	r7, #0
	beq	.L183
	ldr	r1, .L184+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L184+8
	ldr	r0, [r5, #1468]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1468]
.L178:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L183:
	ldr	r8, .L184+8
	mov	r0, #18
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1596]
	mov	r1, #50
	ldr	r3, .L184+12
	add	ip, r2, #1
	str	ip, [r6, #1596]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1600]
	cmp	r0, #0
	str	r0, [r5, #1468]
	beq	.L181
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L184+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L178
.L181:
	sub	r2, fp, #88
	ldr	r1, .L184+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L178
.L185:
	.align	2
.L184:
	.word	.LANCHOR0
	.word	.LC52
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC50
	.word	.LC51
	UNWIND(.fnend)
	.size	VfmwProc_Savestream, .-VfmwProc_Savestream
	.align	2
	.type	VfmwProc_SaveYUV, %function
VfmwProc_SaveYUV:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
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
	ldr	r6, [r0]
	cmp	r6, #31
	bls	.L196
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L196:
	ldr	r7, .L199
	mov	r1, r6
	ldr	r4, .L199+4
	mov	r0, #2
	add	r8, r4, r6, lsl #2
	ldr	r3, [r7, #24]
	blx	r3
	ldr	r5, [r8, #1604]
	cmp	r5, #0
	beq	.L197
	ldr	r1, .L199+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [r7, #36]
	ldr	r0, [r8, #1604]
	mov	r5, #0
	blx	r3
	ldr	r0, [r4, #1744]
	ldr	r3, .L199+12
	mvn	r2, #0
	cmp	r0, r5
	str	r5, [r8, #1604]
	str	r5, [r4, #1760]
	str	r2, [r3, #76]
	str	r5, [r4, #1764]
	str	r5, [r4, #1768]
	str	r5, [r4, #1772]
	str	r5, [r4, #1776]
	str	r5, [r4, #1780]
	str	r5, [r4, #1788]
	str	r5, [r4, #1784]
	bne	.L198
.L192:
	ldr	r3, [r7, #28]
	mov	r1, r6
	mov	r0, #2
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L198:
	ldr	r1, [r4, #1740]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [r4, #1752]
	ldr	r1, [r4, #1740]
	ldr	r0, [r4, #1744]
	bl	MEM_DelMemRecord
	mov	r1, r5
	ldr	r3, [r7, #48]
	mov	r2, #24
	ldr	r0, .L199+16
	blx	r3
	b	.L192
.L197:
	mov	r0, #20
	ldr	r10, [r7, #68]
	bl	VFMW_GetString
	ldr	r3, [r4, #1732]
	ldr	r9, .L199+12
	mov	r1, #100
	add	r2, r3, #1
	str	r2, [r4, #1732]
	str	r3, [sp]
	add	r3, r9, #8
	mov	r2, r0
	sub	r0, fp, #144
	blx	r10
	sub	r0, fp, #144
	ldr	r3, [r7, #32]
	mov	r2, r5
	movw	r1, #578
	blx	r3
	cmp	r0, #0
	str	r0, [r8, #1604]
	beq	.L189
	mov	r2, #24
	mov	r1, r5
	ldr	r3, [r7, #48]
	ldr	r0, .L199+16
	blx	r3
	mov	r0, #27
	mov	r3, #3
	str	r3, [r4, #1756]
	bl	VFMW_GetString
	str	r5, [sp]
	ldr	r3, .L199+16
	mov	r2, #47185920
	mov	r1, r5
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	beq	.L190
	ldr	r1, .L199+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #36]
	ldr	r0, [r8, #1604]
	blx	r3
	mvn	r3, #0
	str	r5, [r8, #1604]
	str	r5, [r4, #1760]
	str	r5, [r4, #1764]
	str	r5, [r4, #1768]
	str	r5, [r4, #1772]
	str	r5, [r4, #1776]
	str	r5, [r4, #1780]
	str	r5, [r4, #1784]
	str	r3, [r9, #76]
	b	.L192
.L189:
	sub	r2, fp, #144
	ldr	r1, .L199+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L192
.L190:
	ldr	r2, [r4, #1752]
	mov	r5, r6, lsr #24
	ldr	r1, [r4, #1740]
	ldr	r0, [r4, #1744]
	bl	MEM_AddMemRecord
	ldr	ip, [r4, #1740]
	and	lr, r6, #3
	sub	r2, fp, #144
	ldr	r1, .L199+28
	mov	r3, r5
	str	lr, [sp]
	mov	r0, #32
	add	r8, ip, #9437184
	add	r10, ip, #11796480
	str	ip, [r4, #1768]
	str	r8, [r4, #1764]
	add	r8, ip, #14155776
	str	r10, [r4, #1760]
	add	r10, ip, #23592960
	str	r8, [r4, #1780]
	add	r8, ip, #25952256
	str	r10, [r4, #1776]
	add	ip, ip, #28311552
	str	r8, [r4, #1772]
	str	ip, [r4, #1788]
	str	r5, [r9, #76]
	str	lr, [r4, #1784]
	bl	dprint_vfmw
	b	.L192
.L200:
	.align	2
.L199:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC56
	.word	.LANCHOR2
	.word	.LANCHOR0+1736
	.word	.LC53
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	VfmwProc_SaveYUV, .-VfmwProc_SaveYUV
	.align	2
	.type	VfmwProc_SetScdPrint, %function
VfmwProc_SetScdPrint:
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
	ldr	r4, .L202
	mov	r1, #1
	ldr	r0, [r0]
	mov	r3, #67108864
	ldr	r5, [r4]
	str	r3, [r4]
	bl	PrintScdRawState
	str	r5, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L203:
	.align	2
.L202:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	VfmwProc_SetScdPrint, .-VfmwProc_SetScdPrint
	.align	2
	.type	VfmwProc_PrintTracer, %function
VfmwProc_PrintTracer:
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
	ldr	r1, .L205
	ldr	r4, [r0]
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DBG_PrintTracer
.L206:
	.align	2
.L205:
	.word	.LC57
	UNWIND(.fnend)
	.size	VfmwProc_PrintTracer, .-VfmwProc_PrintTracer
	.align	2
	.type	VfmwProc_SetSmmuIrqEnable, %function
VfmwProc_SetSmmuIrqEnable:
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
	ldr	r4, [r0]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r5, .L211
	ldr	r3, [r5, #80]
	cmp	r3, #1
	beq	.L210
	ldr	r1, .L211+4
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r5, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L210:
	ldr	r1, .L211+8
	mov	r0, #32
	bl	dprint_vfmw
	str	r4, [r5, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L212:
	.align	2
.L211:
	.word	.LANCHOR2
	.word	.LC59
	.word	.LC58
	UNWIND(.fnend)
	.size	VfmwProc_SetSmmuIrqEnable, .-VfmwProc_SetSmmuIrqEnable
	.align	2
	.type	VfmwProc_SetSedOnlyEnable, %function
VfmwProc_SetSedOnlyEnable:
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
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L215
	ldr	r3, .L216
	mov	r2, #1
	ldr	r1, .L216+4
	mov	r0, #32
	str	r2, [r3, #84]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L215:
	ldr	r2, .L216
	mov	r0, #32
	ldr	r1, .L216+8
	str	r3, [r2, #84]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L217:
	.align	2
.L216:
	.word	.LANCHOR2
	.word	.LC61
	.word	.LC60
	UNWIND(.fnend)
	.size	VfmwProc_SetSedOnlyEnable, .-VfmwProc_SetSedOnlyEnable
	.align	2
	.type	VfmwProc_CloseModuleLowly, %function
VfmwProc_CloseModuleLowly:
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
	ldr	r3, [r0]
	cmp	r3, #31
	bhi	.L220
	ldr	lr, .L221
	mov	r2, r3
	mov	ip, #0
	ldr	r1, .L221+4
	mov	r0, #32
	ldr	r3, [lr, r3, asl #2]
	str	ip, [r3, #1168]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L220:
	ldr	r1, .L221+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L222:
	.align	2
.L221:
	.word	.LANCHOR0
	.word	.LC16
	.word	.LC62
	UNWIND(.fnend)
	.size	VfmwProc_CloseModuleLowly, .-VfmwProc_CloseModuleLowly
	.align	2
	.type	VfmwProc_OpenModuleLowly, %function
VfmwProc_OpenModuleLowly:
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
	ldr	r3, [r0]
	cmp	r3, #31
	bhi	.L225
	ldr	lr, .L226
	mov	r2, r3
	mov	ip, #1
	ldr	r1, .L226+4
	mov	r0, #32
	ldr	r3, [lr, r3, asl #2]
	str	ip, [r3, #1168]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L225:
	ldr	r1, .L226+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L227:
	.align	2
.L226:
	.word	.LANCHOR0
	.word	.LC16
	.word	.LC62
	UNWIND(.fnend)
	.size	VfmwProc_OpenModuleLowly, .-VfmwProc_OpenModuleLowly
	.align	2
	.type	VCTRL_StopTask.part.9, %function
VCTRL_StopTask.part.9:
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
	ldr	r5, .L240
	ldr	r3, [r5, #132]
	cmp	r3, #1
	beq	.L231
	ldr	r6, .L240+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #120]
	blx	r3
	b	.L232
.L239:
	ldr	r3, [r6, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L238
.L232:
	ldr	r3, [r5, #132]
	mov	r0, #10
	cmp	r3, #1
	bne	.L239
.L231:
	mov	r0, #0
.L230:
	mov	r3, #0
	str	r3, [r5, #136]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L238:
	mvn	r0, #0
	b	.L230
.L241:
	.align	2
.L240:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StopTask.part.9, .-VCTRL_StopTask.part.9
	.align	2
	.type	VCTRL_StartTask.part.10, %function
VCTRL_StartTask.part.10:
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
	ldr	r5, .L254
	ldr	r3, [r5, #132]
	cmp	r3, #2
	beq	.L245
	ldr	r6, .L254+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #120]
	blx	r3
	b	.L246
.L253:
	ldr	r3, [r6, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L252
.L246:
	ldr	r3, [r5, #132]
	mov	r0, #10
	cmp	r3, #2
	bne	.L253
.L245:
	mov	r0, #0
.L244:
	mov	r3, #0
	str	r3, [r5, #136]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L252:
	mvn	r0, #0
	b	.L244
.L255:
	.align	2
.L254:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StartTask.part.10, .-VCTRL_StartTask.part.10
	.align	2
	.type	VCTRL_SetSendStreamAgainFlag.part.11, %function
VCTRL_SetSendStreamAgainFlag.part.11:
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
	ldr	r3, .L257
	movw	r2, #1290
	ldr	r1, .L257+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L258:
	.align	2
.L257:
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetSendStreamAgainFlag.part.11, .-VCTRL_SetSendStreamAgainFlag.part.11
	.align	2
	.type	VCTRL_CanBeDecodedByHardWare.part.20, %function
VCTRL_CanBeDecodedByHardWare.part.20:
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
	sub	r3, r0, #19
	cmp	r0, #14
	cmpne	r3, #1
	movls	r0, #1
	movhi	r0, #0
	eor	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_CanBeDecodedByHardWare.part.20, .-VCTRL_CanBeDecodedByHardWare.part.20
	.align	2
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
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
	ldr	r6, .L314
	ldr	r8, .L314+4
	ldr	r3, [r6]
	blx	r3
	ldr	r3, [r8]
	cmp	r3, #0
	mov	r9, r0
	beq	.L261
	mov	r0, #0
	blx	r3
.L262:
	mov	r0, #0
	mov	r4, #32
	mov	r5, r0
	bl	SCDDRV_PrepareSleep
	mov	r0, r5
	mov	r7, r5
	bl	VDMDRV_PrepareSleep
	ldr	r3, [r6]
	blx	r3
	mov	r10, r0
.L271:
	mov	r0, #0
	bl	SCDDRV_GetSleepStage
	cmp	r0, #2
	bne	.L306
	mov	r0, #0
	bl	VDMDRV_GetSleepStage
	cmp	r0, #2
	bne	.L307
.L266:
	ldr	r3, .L314+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L308
.L273:
	ldr	r3, .L314+12
	ldr	r2, [r3, #128]
	cmp	r2, #1
	beq	.L309
.L279:
	ldr	r3, [r6]
	blx	r3
	ldr	r1, .L314+16
	cmp	r9, r0
	rsbls	r2, r9, r0
	mvnhi	r9, r9
	addhi	r2, r9, r0
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L306:
	mov	r0, #0
	str	r7, [fp, #-48]
	bl	VDMDRV_GetSleepStage
	ldr	r3, [fp, #-48]
	cmp	r0, #2
	bne	.L282
	mov	r5, #1
	mov	r2, r5
.L283:
	tst	r2, r3
	bne	.L266
	subs	r4, r4, #1
	beq	.L310
	ldr	r3, [r6, #120]
	mov	r0, #10
	blx	r3
	eor	r3, r5, #1
	eor	r2, r7, #1
	orrs	r3, r3, r2
	bne	.L271
	ldr	r3, .L314+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L273
.L308:
	ldr	r3, [r8, #32]
	cmp	r3, #0
	beq	.L274
	mov	r0, #0
	blx	r3
.L274:
	ldr	r3, [r8, #24]
	cmp	r3, #0
	beq	.L311
	mov	r0, #0
	blx	r3
	ldr	r3, [r8, #8]
	cmp	r3, #0
	beq	.L276
.L313:
	mov	r0, #0
	blx	r3
.L277:
	ldr	r3, [r8, #40]
	cmp	r3, #0
	beq	.L273
	mov	r0, #0
	blx	r3
	ldr	r3, .L314+12
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L279
.L309:
	mov	r2, #2
	str	r2, [r3, #136]
	bl	VCTRL_StopTask.part.9
	b	.L279
.L307:
	mov	r7, #1
	mov	r3, r7
.L282:
	mov	r2, r5
	b	.L283
.L310:
	ldr	r3, [r6]
	blx	r3
	str	r5, [sp]
	mov	r3, r7
	ldr	r1, .L314+20
	cmp	r10, r0
	rsbls	r2, r10, r0
	mvnhi	r10, r10
	addhi	r2, r10, r0
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r7, #1
	beq	.L312
	mov	r2, #0
	ldr	r1, .L314+24
	mov	r0, r2
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_ForceSleep
	cmp	r5, #1
	beq	.L266
.L288:
	mov	r2, #0
	ldr	r1, .L314+28
	mov	r0, r2
	bl	dprint_vfmw
	mov	r0, #0
	bl	VDMDRV_ForceSleep
	b	.L266
.L312:
	cmp	r5, #1
	bne	.L288
	b	.L266
.L311:
	mov	r0, r3
	movw	r2, #387
	ldr	r1, .L314+32
	bl	dprint_vfmw
	ldr	r3, [r8, #8]
	cmp	r3, #0
	bne	.L313
.L276:
	mov	r0, r3
	mov	r2, #392
	ldr	r1, .L314+32
	bl	dprint_vfmw
	b	.L277
.L261:
	mov	r0, r3
	movw	r2, #289
	ldr	r1, .L314+32
	bl	dprint_vfmw
	b	.L262
.L315:
	.align	2
.L314:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	g_HalDisable
	.word	.LANCHOR0
	.word	.LC64
	.word	.LC65
	.word	.LC66
	.word	.LC63
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	2
	.type	VfmwProc_TestSuspend, %function
VfmwProc_TestSuspend:
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
	ldr	r1, .L317
	mov	r2, r0
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_Suspend
.L318:
	.align	2
.L317:
	.word	.LC67
	UNWIND(.fnend)
	.size	VfmwProc_TestSuspend, .-VfmwProc_TestSuspend
	.align	2
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
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
	ldr	r5, .L343
	ldr	r3, [r5]
	blx	r3
	ldr	r3, .L343+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	mov	r4, r0
	beq	.L339
.L320:
	mov	r0, #0
	bl	SCDDRV_ExitSleep
	mov	r0, #0
	bl	VDMDRV_ExitSleep
	ldr	r3, .L343+8
	ldr	r2, [r3, #128]
	cmp	r2, #1
	beq	.L340
.L330:
	ldr	r3, [r5]
	blx	r3
	ldr	r1, .L343+12
	cmp	r4, r0
	rsbls	r2, r4, r0
	mvnhi	r2, r4
	addhi	r2, r2, r0
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L339:
	ldr	r6, .L343+16
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L341
	mov	r0, #0
	blx	r3
.L322:
	ldr	r3, [r6, #20]
	cmp	r3, #0
	beq	.L342
	mov	r0, #0
	blx	r3
.L324:
	ldr	r3, [r6, #28]
	cmp	r3, #0
	beq	.L325
	mov	r0, #0
	blx	r3
.L325:
	ldr	r3, [r6, #36]
	cmp	r3, #0
	beq	.L326
	mov	r0, #0
	blx	r3
.L326:
	ldr	r3, [r6, #68]
	cmp	r3, #0
	beq	.L327
	mov	r0, #0
	blx	r3
.L328:
	ldr	r0, [r6, #72]
	cmp	r0, #0
	beq	.L329
	blx	r0
	b	.L320
.L340:
	str	r2, [r3, #136]
	bl	VCTRL_StartTask.part.10
	b	.L330
.L342:
	mov	r0, r3
	movw	r2, #435
	ldr	r1, .L343+20
	bl	dprint_vfmw
	b	.L324
.L327:
	mov	r0, r3
	movw	r2, #442
	ldr	r1, .L343+20
	bl	dprint_vfmw
	b	.L328
.L329:
	movw	r2, #443
	ldr	r1, .L343+20
	bl	dprint_vfmw
	b	.L320
.L341:
	mov	r0, r3
	movw	r2, #430
	ldr	r1, .L343+20
	bl	dprint_vfmw
	b	.L322
.L344:
	.align	2
.L343:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HalDisable
	.word	.LANCHOR0
	.word	.LC68
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_Resume, .-VCTRL_Resume
	.align	2
	.type	VfmwProc_TestResume, %function
VfmwProc_TestResume:
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
	ldr	r1, .L346
	mov	r2, r0
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_Resume
.L347:
	.align	2
.L346:
	.word	.LC67
	UNWIND(.fnend)
	.size	VfmwProc_TestResume, .-VfmwProc_TestResume
	.align	2
	.global	ChanCtx_Init
	.type	ChanCtx_Init, %function
ChanCtx_Init:
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
	ldr	r3, .L351
	mov	r2, #384
	mov	r1, #0
	ldr	r0, .L351+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, .L351+8
	mvn	r1, #0
	add	r2, r3, #128
.L349:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L349
	ldmfd	sp, {fp, sp, pc}
.L352:
	.align	2
.L351:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_ChanCtx
	.word	g_ChanCtx+124
	UNWIND(.fnend)
	.size	ChanCtx_Init, .-ChanCtx_Init
	.align	2
	.global	VCTRL_RecordPosTime
	.type	VCTRL_RecordPosTime, %function
VCTRL_RecordPosTime:
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
	cmp	r0, #11
	mov	r4, r0
	bhi	.L360
	ldr	r6, .L361
	ldrb	r3, [r6, r0]	@ zero_extendqisi2
	cmp	r3, #14
	movhi	r3, #0
	strhib	r3, [r6, r0]
	cmp	r0, #10
	mov	r5, r3
	ldreq	r3, .L361+4
	moveq	r2, #1
	streqb	r2, [r3, #1792]
	ldr	r3, .L361+8
	ldr	r3, [r3, #4]
	blx	r3
	rsb	r3, r4, r4, lsl #4
	ldr	r1, .L361+12
	add	r3, r3, r5
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	add	r2, r2, #1
	strb	r2, [r6, r4]
	str	r0, [r1, r3, asl #2]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L360:
	str	r0, [sp]
	movw	r3, #693
	ldr	r2, .L361+16
	mov	r0, #32
	ldr	r1, .L361+20
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L362:
	.align	2
.L361:
	.word	g_TimeRecId
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_TimeRecTable
	.word	.LANCHOR1+20
	.word	.LC69
	UNWIND(.fnend)
	.size	VCTRL_RecordPosTime, .-VCTRL_RecordPosTime
	.align	2
	.global	VCTRL_RecordData
	.type	VCTRL_RecordData, %function
VCTRL_RecordData:
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
	cmp	r0, #1
	bhi	.L368
	ldr	ip, .L369
	rsb	r2, r0, r0, lsl #4
	ldr	r4, .L369+4
	ldrb	r3, [ip, r0]	@ zero_extendqisi2
	cmp	r3, #14
	addls	lr, r3, #1
	movhi	r3, #0
	add	r3, r2, r3
	uxtbls	lr, lr
	movhi	lr, #1
	str	r1, [r4, r3, asl #2]
	strb	lr, [ip, r0]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L368:
	str	r0, [sp]
	movw	r3, #717
	ldr	r2, .L369+8
	mov	r0, #32
	ldr	r1, .L369+12
	bl	dprint_vfmw
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L370:
	.align	2
.L369:
	.word	g_DataRecId
	.word	g_DataTable
	.word	.LANCHOR1+40
	.word	.LC70
	UNWIND(.fnend)
	.size	VCTRL_RecordData, .-VCTRL_RecordData
	.align	2
	.global	VCTRL_Isr_1
	.type	VCTRL_Isr_1, %function
VCTRL_Isr_1:
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
	mov	r0, #1
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_1, .-VCTRL_Isr_1
	.align	2
	.global	VCTRL_Isr_2
	.type	VCTRL_Isr_2, %function
VCTRL_Isr_2:
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
	mov	r0, #2
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_2, .-VCTRL_Isr_2
	.align	2
	.global	VCTRL_Scd_Isr_1
	.type	VCTRL_Scd_Isr_1, %function
VCTRL_Scd_Isr_1:
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
	mov	r0, #1
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr_1, .-VCTRL_Scd_Isr_1
	.align	2
	.global	VCTRL_Scd_Isr_2
	.type	VCTRL_Scd_Isr_2, %function
VCTRL_Scd_Isr_2:
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
	mov	r0, #2
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr_2, .-VCTRL_Scd_Isr_2
	.align	2
	.global	VCTRL_InformVdmFree
	.type	VCTRL_InformVdmFree, %function
VCTRL_InformVdmFree:
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
	ldr	r3, .L376
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L377:
	.align	2
.L376:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_InformVdmFree, .-VCTRL_InformVdmFree
	.align	2
	.global	VCTRL_ExtraWakeUpThread
	.type	VCTRL_ExtraWakeUpThread, %function
VCTRL_ExtraWakeUpThread:
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
	ldr	r3, .L379
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L380:
	.align	2
.L379:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_ExtraWakeUpThread, .-VCTRL_ExtraWakeUpThread
	.align	2
	.global	VCTRL_SetMoreGapEnable
	.type	VCTRL_SetMoreGapEnable, %function
VCTRL_SetMoreGapEnable:
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
	bhi	.L387
	ldr	r3, .L390
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L388
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L389
	cmp	r1, #1
	strls	r1, [r3, #1152]
	movls	r0, #0
	movhi	r2, #0
	strhi	r2, [r3, #1152]
	mvnhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L389:
	ldr	r3, .L390+4
	movw	r2, #905
	ldr	r1, .L390+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L387:
	ldr	r3, .L390+12
	movw	r2, #903
	ldr	r1, .L390+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L388:
	mov	r0, r3
	mov	r2, #904
	ldr	r3, .L390+16
	ldr	r1, .L390+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L391:
	.align	2
.L390:
	.word	.LANCHOR0
	.word	.LC72
	.word	.LC1
	.word	.LC71
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetMoreGapEnable, .-VCTRL_SetMoreGapEnable
	.align	2
	.global	VCTRL_SetCallBack
	.type	VCTRL_SetCallBack, %function
VCTRL_SetCallBack:
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
	beq	.L400
	cmp	r0, #0
	beq	.L396
	cmp	r0, #1
	bne	.L401
	ldr	r3, .L402
	mov	r0, #0
	str	r1, [r3, #372]
	ldmfd	sp, {fp, sp, pc}
.L401:
	mov	r3, r0
	ldr	r2, .L402+4
	ldr	r1, .L402+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L396:
	ldr	r3, .L402
	str	r1, [r3, #368]
	ldmfd	sp, {fp, sp, pc}
.L400:
	mov	r0, r1
	ldr	r3, .L402+12
	movw	r2, #1022
	ldr	r1, .L402+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L403:
	.align	2
.L402:
	.word	.LANCHOR0
	.word	.LANCHOR1+60
	.word	.LC74
	.word	.LC73
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetCallBack, .-VCTRL_SetCallBack
	.align	2
	.global	VCTRL_StopTask
	.type	VCTRL_StopTask, %function
VCTRL_StopTask:
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
	ldr	r3, .L406
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L405
	mov	r2, #2
	str	r2, [r3, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StopTask.part.9
.L405:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L407:
	.align	2
.L406:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_StopTask, .-VCTRL_StopTask
	.align	2
	.global	VCTRL_StartTask
	.type	VCTRL_StartTask, %function
VCTRL_StartTask:
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
	ldr	r3, .L410
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L409
	str	r2, [r3, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StartTask.part.10
.L409:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L411:
	.align	2
.L410:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_StartTask, .-VCTRL_StartTask
	.align	2
	.global	VCTRL_SetStreamInterface
	.type	VCTRL_SetStreamInterface, %function
VCTRL_SetStreamInterface:
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
	mov	r4, r0
	beq	.L416
	ldr	r3, .L418
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L417
	ldr	r5, .L418+4
	mov	r2, #12
	add	r0, r0, #184
	ldr	r3, [r5, #52]
	blx	r3
	mov	r3, r4, asl #4
	ldr	r0, .L418+8
	sub	r4, r3, r4, asl #2
	mov	r1, r6
	ldr	r3, [r5, #52]
	add	r0, r0, r4
	mov	r2, #12
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L417:
	ldr	r3, .L418+12
	movw	r2, #1279
	ldr	r1, .L418+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L416:
	mov	r0, r6
	ldr	r3, .L418+20
	movw	r2, #1278
	ldr	r1, .L418+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L419:
	.align	2
.L418:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1796
	.word	.LC2
	.word	.LC1
	.word	.LC75
	UNWIND(.fnend)
	.size	VCTRL_SetStreamInterface, .-VCTRL_SetStreamInterface
	.align	2
	.global	VCTRL_SetSendStreamAgainFlag
	.type	VCTRL_SetSendStreamAgainFlag, %function
VCTRL_SetSendStreamAgainFlag:
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
	ldr	r3, .L423
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L422
	add	r3, r3, #471040
	mov	r0, #0
	str	r1, [r3, #916]
	ldmfd	sp, {fp, sp, pc}
.L422:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_SetSendStreamAgainFlag.part.11
.L424:
	.align	2
.L423:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_SetSendStreamAgainFlag, .-VCTRL_SetSendStreamAgainFlag
	.align	2
	.global	VCTRL_GetSendStreamAgainFlag
	.type	VCTRL_GetSendStreamAgainFlag, %function
VCTRL_GetSendStreamAgainFlag:
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
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L428
	add	r0, r0, #471040
	ldr	r0, [r0, #916]
	ldmfd	sp, {fp, sp, pc}
.L428:
	ldr	r3, .L429+4
	movw	r2, #1297
	ldr	r1, .L429+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L430:
	.align	2
.L429:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_GetSendStreamAgainFlag, .-VCTRL_GetSendStreamAgainFlag
	.align	2
	.global	VCTRL_GetStreamInterface
	.type	VCTRL_GetStreamInterface, %function
VCTRL_GetStreamInterface:
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
	ldr	r5, .L437
	mov	r4, r0
	ldr	r1, [r5, r0, asl #2]
	cmp	r1, #0
	beq	.L435
	ldr	r3, .L437+4
	mov	ip, r0, asl #4
	ldr	r0, .L437+8
	sub	ip, ip, r4, asl #2
	add	r1, r1, #184
	mov	r2, #12
	add	r0, r0, ip
	ldr	r3, [r3, #60]
	blx	r3
	cmp	r0, #0
	bne	.L436
	ldr	r1, [r5, r4, asl #2]
	add	r0, r1, #184
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L436:
	mov	r3, r4
	movw	r2, #1313
	ldr	r1, .L437+12
	mov	r0, #0
	bl	dprint_vfmw
.L435:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L438:
	.align	2
.L437:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1796
	.word	.LC76
	UNWIND(.fnend)
	.size	VCTRL_GetStreamInterface, .-VCTRL_GetStreamInterface
	.align	2
	.global	VCTRL_SetFrameInterface
	.type	VCTRL_SetFrameInterface, %function
VCTRL_SetFrameInterface:
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
	subs	r3, r1, #0
	beq	.L443
	ldr	r3, .L445
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L444
	ldr	r3, .L445+4
	mov	r2, #12
	add	r0, r0, #208
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L444:
	ldr	r3, .L445+8
	movw	r2, #1326
	ldr	r1, .L445+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L443:
	mov	r0, r3
	movw	r2, #1325
	ldr	r3, .L445+16
	ldr	r1, .L445+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L446:
	.align	2
.L445:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC77
	UNWIND(.fnend)
	.size	VCTRL_SetFrameInterface, .-VCTRL_SetFrameInterface
	.align	2
	.global	VCTRL_GetFrameInterface
	.type	VCTRL_GetFrameInterface, %function
VCTRL_GetFrameInterface:
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
	ldr	r3, .L450
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #208
	ldmfd	sp, {fp, sp, pc}
.L451:
	.align	2
.L450:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetFrameInterface, .-VCTRL_GetFrameInterface
	.align	2
	.global	VCTRL_GetStreamSize
	.type	VCTRL_GetStreamSize, %function
VCTRL_GetStreamSize:
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
	bhi	.L457
	ldr	r3, .L460
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L458
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L459
	add	r0, r0, #99328
	add	r0, r0, #544
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetSegStreamSize
.L459:
	ldr	r3, .L460+4
	movw	r2, #1355
	ldr	r1, .L460+8
	mov	r0, #0
	bl	dprint_vfmw
.L454:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L457:
	ldr	r3, .L460+12
	movw	r2, #1353
	ldr	r1, .L460+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L454
.L458:
	ldr	r3, .L460+16
	movw	r2, #1354
	ldr	r1, .L460+8
	bl	dprint_vfmw
	b	.L454
.L461:
	.align	2
.L460:
	.word	.LANCHOR0
	.word	.LC79
	.word	.LC1
	.word	.LC71
	.word	.LC78
	UNWIND(.fnend)
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
	.align	2
	.global	VCTRL_CheckFreshRaw
	.type	VCTRL_CheckFreshRaw, %function
VCTRL_CheckFreshRaw:
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
	cmp	r0, #31
	mov	r3, #0
	str	r3, [fp, #-28]
	str	r3, [fp, #-24]
	bhi	.L469
	ldr	r2, .L472
	ldr	r0, [r2, r0, asl #2]
	cmp	r0, #0
	beq	.L470
	ldr	r2, [r0, #4]
	cmp	r2, #1
	bne	.L471
	add	r4, r0, #1536
	sub	r1, fp, #28
	add	r4, r4, #8
	mov	r0, r4
	bl	GetRawStreamNum
	cmp	r0, #0
	bne	.L468
	mov	r0, r4
	sub	r1, fp, #24
	bl	GetRawStreamSize
	cmp	r0, #0
	bne	.L468
	ldr	r3, [fp, #-24]
	mov	r0, #22
	ldr	r2, [fp, #-28]
	ldr	r1, .L472+4
	bl	dprint_vfmw
	ldr	r3, [fp, #-28]
	cmp	r3, #0
	ble	.L468
	ldr	r0, [fp, #-24]
	cmp	r0, #3
	movgt	r0, #0
	mvnle	r0, #0
.L464:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L468:
	mvn	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L471:
	mov	r0, r3
	movw	r2, #1372
	ldr	r3, .L472+8
	ldr	r1, .L472+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L464
.L469:
	mov	r0, r3
	movw	r2, #1370
	ldr	r3, .L472+16
	ldr	r1, .L472+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L464
.L470:
	ldr	r3, .L472+20
	movw	r2, #1371
	ldr	r1, .L472+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L464
.L473:
	.align	2
.L472:
	.word	.LANCHOR0
	.word	.LC80
	.word	.LC79
	.word	.LC1
	.word	.LC71
	.word	.LC78
	UNWIND(.fnend)
	.size	VCTRL_CheckFreshRaw, .-VCTRL_CheckFreshRaw
	.align	2
	.global	VCTRL_CheckFreshSeg
	.type	VCTRL_CheckFreshSeg, %function
VCTRL_CheckFreshSeg:
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
	cmp	r0, #31
	mov	r2, #0
	str	r2, [fp, #-20]
	str	r2, [fp, #-16]
	bhi	.L479
	ldr	r3, .L482
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L480
	ldr	r1, [r0, #4]
	cmp	r1, #1
	bne	.L481
	add	r0, r0, #99328
	sub	r2, fp, #16
	add	r0, r0, #544
	sub	r1, fp, #20
	bl	GetFreshSegStream
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	mov	r0, #22
	ldr	r1, .L482+4
	bl	dprint_vfmw
	ldr	r0, [fp, #-20]
	cmp	r0, #0
	movgt	r0, #0
	mvnle	r0, #0
.L476:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L481:
	mov	r0, r2
	ldr	r3, .L482+8
	movw	r2, #1398
	ldr	r1, .L482+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L476
.L479:
	mov	r0, r2
	ldr	r3, .L482+16
	movw	r2, #1396
	ldr	r1, .L482+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L476
.L480:
	ldr	r3, .L482+20
	movw	r2, #1397
	ldr	r1, .L482+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L476
.L483:
	.align	2
.L482:
	.word	.LANCHOR0
	.word	.LC81
	.word	.LC79
	.word	.LC1
	.word	.LC71
	.word	.LC78
	UNWIND(.fnend)
	.size	VCTRL_CheckFreshSeg, .-VCTRL_CheckFreshSeg
	.align	2
	.global	VCTRL_SetDiscardPicParam
	.type	VCTRL_SetDiscardPicParam, %function
VCTRL_SetDiscardPicParam:
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
	mov	r4, r0
	mov	r0, r1
	bhi	.L490
	cmp	r1, #0
	beq	.L491
	ldr	r5, .L493
	ldr	r0, [r5, r4, asl #2]
	cmp	r0, #0
	beq	.L492
	ldr	r3, .L493+4
	mov	r2, #8
	add	r0, r0, #1424
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r5, r4, asl #2]
	mov	r0, #0
	ldr	r3, [r2, #1424]
	sub	r3, r3, #1
	cmp	r3, #1
	strhi	r0, [r2, #1424]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L490:
	ldr	r3, .L493+8
	movw	r2, #1417
	ldr	r1, .L493+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L492:
	ldr	r3, .L493+16
	movw	r2, #1419
	ldr	r1, .L493+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L491:
	ldr	r3, .L493+20
	movw	r2, #1418
	ldr	r1, .L493+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L494:
	.align	2
.L493:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
	.word	.LC1
	.word	.LC2
	.word	.LC82
	UNWIND(.fnend)
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	2
	.global	VCTRL_GetSyntaxCtx
	.type	VCTRL_GetSyntaxCtx, %function
VCTRL_GetSyntaxCtx:
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
	ldr	r3, .L498
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #475136
	addne	r0, r0, #1000
	ldmfd	sp, {fp, sp, pc}
.L499:
	.align	2
.L498:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetSyntaxCtx, .-VCTRL_GetSyntaxCtx
	.align	2
	.global	VCTRL_GetImageInterface
	.type	VCTRL_GetImageInterface, %function
VCTRL_GetImageInterface:
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
	ldr	r3, .L503
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #196
	ldmfd	sp, {fp, sp, pc}
.L504:
	.align	2
.L503:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageInterface, .-VCTRL_GetImageInterface
	.align	2
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 32
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
	ldr	r9, .L522
	cmp	r2, #31
	cmpgt	r1, #31
	mov	r5, r2
	mov	r6, r1
	mov	r8, r0
	movle	r2, #1
	movgt	r2, #0
	ldr	r4, [r9, r0, asl #2]
	ble	.L518
	ldr	r1, [fp, #4]
	cmp	r1, #0
	cmpne	r3, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L519
	ldr	r10, .L522+4
	mov	r2, #20
	mov	r1, r7
	sub	r0, fp, #64
	str	r3, [fp, #-72]
	ldr	ip, [r10, #48]
	blx	ip
	sub	r1, fp, #64
	mov	r0, r8
	str	r5, [fp, #-56]
	mov	r2, #1
	str	r5, [fp, #-48]
	str	r6, [fp, #-60]
	str	r6, [fp, #-52]
	strb	r7, [fp, #-63]
	strb	r7, [fp, #-62]
	strb	r7, [fp, #-61]
	strb	r2, [fp, #-64]
	bl	FSP_ConfigInstance
	subs	r5, r0, #0
	bne	.L509
	ldr	r3, [fp, #-72]
	mov	r0, r8
	ldr	r2, [fp, #4]
	mov	r1, r3
	sub	r3, fp, #68
	bl	FSP_ConfigFrameBuf
	subs	r6, r0, #0
	bne	.L520
	mov	r0, r8
	ldr	r1, .L522+8
	bl	FSP_GetInstInfo
	movw	r3, #2182
	ldrsb	r3, [r9, r3]
	cmp	r3, #16
	movge	r3, #16
	cmp	r3, #2
	str	r3, [r4, #460]
	ble	.L521
	ldr	ip, [r9, #2184]
	mov	r2, #64
	ldr	r3, [r10, #48]
	mov	r1, r5
	add	r0, r4, #392
	str	ip, [r4, #456]
	blx	r3
	ldr	r0, [r4, #460]
	cmp	r0, #0
	ble	.L507
	ldr	r2, .L522+8
	add	r4, r4, #388
	mov	r3, r5
.L514:
	ldr	r1, [r2, #16]
	add	r3, r3, #1
	cmp	r3, r0
	add	r2, r2, #88
	str	r1, [r4, #4]!
	bne	.L514
.L507:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L519:
	mov	r0, r2
	ldr	r1, .L522+12
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L507
.L509:
	mov	r0, r7
	ldr	r1, .L522+16
	bl	dprint_vfmw
.L517:
	mvn	r5, #0
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L520:
	mov	r0, r5
	ldr	r1, .L522+20
	bl	dprint_vfmw
	b	.L517
.L521:
	mov	r0, r6
	movw	r3, #1571
	ldr	r2, .L522+24
	ldr	r1, .L522+28
	bl	dprint_vfmw
	b	.L517
.L518:
	mov	r3, r5
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L522+32
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L507
.L523:
	.align	2
.L522:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+2180
	.word	.LC84
	.word	.LC87
	.word	.LC85
	.word	.LANCHOR1+80
	.word	.LC86
	.word	.LC83
	UNWIND(.fnend)
	.size	VCTRL_PartitionMemForStdUser, .-VCTRL_PartitionMemForStdUser
	.align	2
	.global	VCTRL_UnInstallChan
	.type	VCTRL_UnInstallChan, %function
VCTRL_UnInstallChan:
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
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_UnInstallChan, .-VCTRL_UnInstallChan
	.align	2
	.global	DelAllFrameMemRecord
	.type	DelAllFrameMemRecord, %function
DelAllFrameMemRecord:
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
	movne	r4, r1
	addne	r5, r4, #2304
	beq	.L542
.L531:
	ldr	r3, [r4]
	cmp	r3, #255
	beq	.L528
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #24]
	ldr	r0, [r4, #32]
	bl	MEM_DelMemRecord
.L528:
	ldr	r3, [r4, #4]
	cmp	r3, #255
	beq	.L529
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #48]
	bl	MEM_DelMemRecord
.L529:
	ldr	r3, [r4, #8]
	cmp	r3, #255
	beq	.L530
	ldr	r2, [r4, #20]
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #64]
	bl	MEM_DelMemRecord
.L530:
	add	r4, r4, #72
	cmp	r4, r5
	bne	.L531
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L542:
	mov	r0, r1
	ldr	r3, .L543
	movw	r2, #1610
	ldr	r1, .L543+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L544:
	.align	2
.L543:
	.word	.LC88
	.word	.LC1
	UNWIND(.fnend)
	.size	DelAllFrameMemRecord, .-DelAllFrameMemRecord
	.align	2
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
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
	subs	r5, r1, #0
	beq	.L569
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L570
	ldr	r3, [r5, #16]
	cmp	r3, #1
	beq	.L550
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
.L551:
	ldr	r3, [r5, #20]
	cmp	r3, #1
	beq	.L571
.L549:
	ldr	r4, [r5, #4]
	cmp	r4, #0
	beq	.L572
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
	ldr	r3, [r5, #24]
	cmp	r3, #1
	beq	.L573
.L554:
	ldr	r4, [r5, #8]
	cmp	r4, #0
	beq	.L574
.L555:
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
	ldr	r3, [r5, #28]
	cmp	r3, #1
	bne	.L556
	ldr	r0, [r4, #8]
	cmp	r0, #0
	bne	.L575
.L556:
	ldr	r3, .L577
	ldr	r0, [r4, #4]
	ldr	r3, [r3, #164]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L550:
	ldr	r1, [r5, #12]
	cmp	r1, #0
	beq	.L576
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	beq	.L551
	ldr	r1, .L577+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #20]
	cmp	r3, #1
	bne	.L549
.L571:
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L549
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	b	.L549
.L573:
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L554
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	b	.L554
.L572:
	mov	r0, r4
	ldr	r2, .L577+8
	ldr	r1, .L577+12
	bl	dprint_vfmw
	ldr	r4, [r5, #8]
	cmp	r4, #0
	bne	.L555
.L574:
	ldr	r2, .L577+8
	mov	r0, r4
	ldr	r1, .L577+16
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L575:
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L576:
	mov	r0, r1
	ldr	r2, .L577+8
	ldr	r1, .L577+20
	bl	dprint_vfmw
	b	.L551
.L570:
	mov	r0, r4
	ldr	r2, .L577+8
	ldr	r1, .L577+24
	bl	dprint_vfmw
	b	.L549
.L569:
	mov	r0, r5
	ldr	r2, .L577+8
	ldr	r1, .L577+28
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L578:
	.align	2
.L577:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC92
	.word	.LANCHOR1+112
	.word	.LC93
	.word	.LC94
	.word	.LC91
	.word	.LC90
	.word	.LC89
	UNWIND(.fnend)
	.size	VCTRL_FreeChanResource, .-VCTRL_FreeChanResource
	.align	2
	.global	VCTRL_GetChanCtxSize
	.type	VCTRL_GetChanCtxSize, %function
VCTRL_GetChanCtxSize:
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
	cmp	r0, #26
	movweq	r3, #45800
	movwne	r3, #13616
	movteq	r3, 180
	movtne	r3, 15
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_GetChanCtxSize, .-VCTRL_GetChanCtxSize
	.align	2
	.global	VCTRL_GetChanCfg
	.type	VCTRL_GetChanCfg, %function
VCTRL_GetChanCfg:
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
	mov	r3, r1
	bhi	.L587
	cmp	r1, #0
	beq	.L588
	ldr	r2, .L590
	ldr	r1, [r2, r0, asl #2]
	cmp	r1, #0
	beq	.L589
	ldr	ip, .L590+4
	add	r1, r1, #44
	mov	r0, r3
	mov	r2, #140
	ldr	r3, [ip, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L587:
	ldr	r3, .L590+8
	movw	r2, #2639
	ldr	r1, .L590+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L589:
	mov	r0, r1
	ldr	r3, .L590+16
	movw	r2, #2641
	ldr	r1, .L590+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L588:
	mov	r0, r1
	ldr	r3, .L590+20
	mov	r2, #2640
	ldr	r1, .L590+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L591:
	.align	2
.L590:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
	.word	.LC1
	.word	.LC2
	.word	.LC95
	UNWIND(.fnend)
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	2
	.global	VCTRL_CheckCommonParameter
	.type	VCTRL_CheckCommonParameter, %function
VCTRL_CheckCommonParameter:
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
	ldr	r3, .L604
	ldr	r2, [r1, #8]
	ldr	r3, [r3, r0, asl #2]
	ldr	r0, [r3, #52]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #72]
	ldr	r2, [r1, #28]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #68]
	ldr	r2, [r1, #24]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #76]
	ldr	r2, [r1, #32]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #80]
	ldr	r2, [r1, #36]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #84]
	ldr	r2, [r1, #40]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #100]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #112]
	ldr	r2, [r1, #68]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #108]
	ldr	r2, [r1, #64]
	cmp	r0, r2
	bne	.L603
	ldr	r0, [r3, #104]
	ldr	r2, [r1, #60]
	cmp	r0, r2
	bne	.L603
	ldr	r3, [r3, #116]
	ldr	r0, [r1, #72]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L603:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L605:
	.align	2
.L604:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_CheckCommonParameter, .-VCTRL_CheckCommonParameter
	.align	2
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
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
	ldr	r3, .L613
	mov	r5, r1
	ldr	r4, [r3, r0, asl #2]
	ldr	r3, [r4, #536]
	cmp	r3, #21
	beq	.L611
	bl	VCTRL_CheckCommonParameter
	cmp	r0, #0
	bne	.L611
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L612
	sub	r3, r3, #10
	cmp	r3, #2
	ldmhifd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #56]
	ldr	r0, [r5, #12]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L612:
	ldr	r2, [r4, #56]
	ldr	r3, [r5, #12]
	cmp	r2, r3
	bne	.L611
	ldr	r3, [r4, #60]
	ldr	r0, [r5, #16]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L611:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L614:
	.align	2
.L613:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_CmpConfigParameter, .-VCTRL_CmpConfigParameter
	.align	2
	.global	VCTRL_CheckChanWH
	.type	VCTRL_CheckChanWH, %function
VCTRL_CheckChanWH:
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
	ldr	r3, .L620
	ldr	r2, .L620+4
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r2]
	ldr	r0, [r3, #1228]
	ldr	r3, [r3, #1232]
	cmp	r0, r2
	bgt	.L616
	ldr	r0, .L620+8
	ldr	r0, [r0]
	cmp	r3, r0
	ble	.L618
.L616:
	ldr	r0, [r1, #8]
	cmp	r0, #20
	cmpne	r0, #0
	bic	r0, r0, #2
	movne	r3, #1
	moveq	r3, #0
	cmp	r0, #13
	moveq	r0, #0
	andne	r0, r3, #1
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, .L620+8
	mov	r0, #0
	ldr	r1, .L620+12
	ldr	r3, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L618:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L621:
	.align	2
.L620:
	.word	.LANCHOR0
	.word	g_ChipMaxWidth
	.word	g_ChipMaxHeight
	.word	.LC96
	UNWIND(.fnend)
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	2
	.global	VCTRL_ConfigChanCompress
	.type	VCTRL_ConfigChanCompress, %function
VCTRL_ConfigChanCompress:
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
	ldr	r3, [r1, #56]
	cmp	r3, #2
	ldr	r3, .L628
	beq	.L627
	add	r2, r3, r0, lsl #4
	ldr	r3, [r3, r0, asl #2]
	ldr	r1, [r2, #400]
	ldr	r0, [r2, #396]
	cmp	r1, #1
	str	r1, [r3, #1140]
	ldreq	r1, [r2, #404]
	mvnne	r2, #0
	ldreq	r2, [r2, #408]
	str	r0, [r3, #1136]
	strne	r2, [r3, #1144]
	streq	r1, [r3, #1144]
	str	r2, [r3, #1148]
	ldmfd	sp, {fp, sp, pc}
.L627:
	ldr	r3, [r3, r0, asl #2]
	mov	r1, #0
	mvn	r2, #0
	str	r1, [r3, #1136]
	str	r1, [r3, #1140]
	str	r2, [r3, #1144]
	str	r2, [r3, #1148]
	ldmfd	sp, {fp, sp, pc}
.L629:
	.align	2
.L628:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_ConfigChanCompress, .-VCTRL_ConfigChanCompress
	.align	2
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
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
	ldr	r3, .L638
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L636
	ldr	r3, [r3, #536]
	sub	r2, r3, #10
	cmp	r2, #2
	bls	.L637
.L633:
	cmp	r3, #14
	cmpne	r3, #4
	beq	.L635
	bl	SM_SeekPts
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L637:
	ldr	r2, .L638+4
	ldr	r2, [r2, #-3180]
	tst	r2, #1
	bne	.L633
.L635:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L636:
	mov	r0, r3
	movw	r2, #3205
	ldr	r3, .L638+8
	ldr	r1, .L638+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L639:
	.align	2
.L638:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SeekPts, .-VCTRL_SeekPts
	.align	2
	.global	VCTRL_ReleaseStream
	.type	VCTRL_ReleaseStream, %function
VCTRL_ReleaseStream:
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
	ldr	r3, .L644
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L643
	bl	SM_Reset
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L643:
	mov	r0, r3
	movw	r2, #3469
	ldr	r3, .L644+4
	ldr	r1, .L644+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L645:
	.align	2
.L644:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	2
	.global	VCTRL_ImageOutputEnable
	.type	VCTRL_ImageOutputEnable, %function
VCTRL_ImageOutputEnable:
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
	mov	r4, r0
	mov	r6, r1
	bhi	.L649
	ldr	r5, .L650
	mov	r0, #4
	ldr	r3, [r5, #12]
	blx	r3
	ldr	r3, .L650+4
	ldr	r2, [r6]
	mov	r0, #4
	ldr	r3, [r3, r4, asl #2]
	str	r2, [r3, #12]
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L649:
	ldr	r3, .L650+8
	movw	r2, #3583
	ldr	r1, .L650+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L651:
	.align	2
.L650:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_ImageOutputEnable, .-VCTRL_ImageOutputEnable
	.align	2
	.global	VCTRL_TryToRelSpecialFrm
	.type	VCTRL_TryToRelSpecialFrm, %function
VCTRL_TryToRelSpecialFrm:
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
	cmp	r0, #31
	mov	r4, r0
	bhi	.L687
	ldr	r5, .L692
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L688
	add	r3, r0, #475136
	ldr	ip, [r3, #936]
	cmp	ip, #0
	beq	.L656
	ldr	r3, [r3, #412]
	cmp	r1, r3
	movne	r2, #0
	bne	.L659
	b	.L689
.L662:
	add	r3, r3, #412
	ldr	r3, [r0, r3]
	cmp	r1, r3
	beq	.L657
.L659:
	add	r2, r2, #1
	cmp	r2, ip
	mov	r3, r2, asl #4
	mov	r6, r2
	add	r3, r3, #475136
	bne	.L662
.L656:
	mvn	r0, #0
.L680:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L689:
	mov	r6, #0
.L657:
	add	r3, r0, #462848
	ldr	r3, [r3, #3200]
	cmp	r3, r1
	movwne	r3, #7384
	movne	r7, #1
	movtne	r3, 7
	addne	r3, r0, r3
	bne	.L666
	b	.L690
.L663:
	add	r7, r7, #1
	cmp	r7, #32
	beq	.L691
.L666:
	ldr	r2, [r3]
	add	r3, r3, #88
	cmp	r2, r1
	bne	.L663
.L660:
	ldr	r9, .L692+4
	mov	r0, #3
	sub	r8, ip, #1
	ldr	r3, [r9, #12]
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	mov	r0, #88
	movw	r2, #7288
	movw	r3, #10104
	movt	r2, 7
	mla	r7, r0, r7, r1
	movt	r3, 7
	mov	r1, #0
	ldr	ip, [r9, #16]
	mov	r0, #3
	add	r2, r7, r2
	add	r3, r7, r3
	strb	r1, [r2, #2]
	strb	r1, [r3, #2]
	blx	ip
	cmp	r8, r6
	bls	.L672
	mov	r7, r6, asl #4
.L665:
	add	r6, r6, #1
	add	r0, r7, #475136
	ldr	r1, [r5, r4, asl #2]
	add	r0, r0, #408
	mov	r7, r6, asl #4
	ldr	ip, [r9, #52]
	add	r3, r7, #475136
	add	r0, r1, r0
	add	r3, r3, #408
	mov	r2, #16
	add	r1, r1, r3
	blx	ip
	cmp	r8, r6
	bhi	.L665
.L664:
	mov	r3, r8, asl #4
	ldr	r0, [r5, r4, asl #2]
	add	r3, r3, #475136
	ldr	ip, [r9, #48]
	add	r3, r3, #408
	mov	r2, #16
	add	r0, r0, r3
	mov	r1, #0
	blx	ip
	ldr	r3, [r5, r4, asl #2]
	mov	r0, #0
	add	r3, r3, #475136
	ldr	r2, [r3, #936]
	sub	r2, r2, #1
	str	r2, [r3, #936]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L691:
	add	r0, r0, #442368
	movw	r6, #2027
	movw	r3, #3740
	ldr	r2, .L692+8
	ldrsb	ip, [r0, r6]
	mov	r0, #1
	ldr	r1, .L692+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r5, r4, asl #2]
	add	r3, ip, #442368
	ldrsb	r3, [r3, r6]
	cmp	r3, #0
	movgt	r6, #0
	ble	.L656
.L668:
	mov	r2, #88
	movw	r3, #3743
	mla	ip, r2, r6, ip
	mov	r0, #1
	ldr	r2, .L692+8
	add	r6, r6, r0
	ldr	r1, .L692+16
	add	ip, ip, #462848
	ldr	ip, [ip, #3200]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r5, r4, asl #2]
	movw	r3, #51179
	movt	r3, 6
	add	r3, ip, r3
	ldrsb	r3, [r3]
	cmp	r3, r6
	bgt	.L668
	b	.L656
.L690:
	mov	r7, #0
	b	.L660
.L687:
	ldr	r3, .L692+20
	movw	r2, #3704
	ldr	r1, .L692+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L680
.L672:
	mov	r8, r6
	b	.L664
.L688:
	ldr	r3, .L692+20
	movw	r2, #3705
	ldr	r1, .L692+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L680
.L693:
	.align	2
.L692:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+136
	.word	.LC98
	.word	.LC97
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_TryToRelSpecialFrm, .-VCTRL_TryToRelSpecialFrm
	.align	2
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 632
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #640)
	sub	sp, sp, #640
	mov	r4, r0
	mov	r2, r0
	mov	r5, r1
	mov	r0, #2
	ldr	r1, .L735
	bl	dprint_vfmw
	cmp	r4, #31
	bhi	.L723
	ldr	r6, .L735+4
	ldr	r0, [r6, r4, asl #2]
	cmp	r0, #0
	beq	.L724
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L725
	ldr	r8, .L735+8
	mov	r0, #4
	ldr	r3, [r8, #12]
	blx	r3
	ldr	r0, [r6, r4, asl #2]
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L726
	add	r0, r0, #475136
	mov	r1, r5
	add	r0, r0, #1000
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	mov	r9, r0
	beq	.L727
	mov	r0, #9
	mvn	r7, #0
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L712
.L711:
	ldr	r3, [r6, r4, asl #2]
	mov	r0, #4
	ldr	r2, [r8, #16]
	add	r3, r3, #491520
	ldrb	r3, [r3, #436]	@ zero_extendqisi2
	strb	r3, [r5, #392]
	blx	r2
.L720:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L727:
	ldr	r2, [r5, #192]
	mvn	r3, #0
	str	r3, [r5, #188]
	cmp	r2, #1
	beq	.L728
.L701:
	mov	r0, #9
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L729
.L713:
	ldr	r2, [r5, #64]
	mov	r7, #0
	ldr	r3, [r6, r4, asl #2]
	str	r2, [r3, #364]
	ldr	r2, [r5, #276]
	str	r2, [r3, #368]
	b	.L711
.L729:
	mov	r7, #0
.L712:
	ldr	r3, [r8]
	blx	r3
	ldr	r3, .L735+12
	ldr	r1, .L735+16
	add	r3, r3, r4, lsl #2
	ldr	r2, [r3, #-3176]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bhi	.L730
.L710:
	cmp	r7, #0
	bne	.L711
	b	.L713
.L730:
	mov	r2, r4, asl #24
	movw	r1, #4018
	add	r2, r2, #589824
	ldr	r0, .L735+20
	cmp	r9, #1
	addeq	r2, r2, #1
	str	ip, [r3, #-3176]
	bl	DBG_AddTrace
	b	.L710
.L728:
	ldr	r2, [r5, #180]
	cmp	r2, #0
	beq	.L731
	ldr	r0, [r5, #24]
	mov	r2, #3
	ldr	r1, [r5, #20]
	str	r3, [r5, #188]
	str	r9, [r5, #180]
	str	r0, [r5, #200]
	str	r1, [r5, #196]
	str	r2, [r5, #276]
	b	.L701
.L725:
	ldr	r3, .L735+24
	movw	r2, #3882
	ldr	r1, .L735+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L720
.L726:
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	ldr	r2, .L735+32
	ldr	r1, .L735+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L720
.L731:
	ldr	r0, [r6, r4, asl #2]
	sub	r1, fp, #668
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	bne	.L732
	ldr	r3, [r5, #184]
	ldr	r2, [fp, #-484]
	cmp	r3, r2
	bge	.L704
	ldr	r7, [fp, #-488]
	mov	r3, #3
	ldr	lr, [fp, #-644]
	mov	r9, #1
	cmp	r7, #0
	ldr	ip, [fp, #-648]
	ldr	r0, [fp, #-640]
	ldr	r1, [fp, #-636]
	movne	r7, #0
	ldr	r2, [fp, #-520]
	str	lr, [r5, #200]
	str	ip, [r5, #196]
	str	r0, [r5, #204]
	str	r1, [r5, #208]
	str	r2, [r5, #188]
	str	r3, [r5, #276]
	strne	r9, [r5, #180]
.L709:
	mov	r0, #9
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L712
	cmp	r7, #0
	bne	.L711
	b	.L713
.L723:
	ldr	r3, .L735+40
	movw	r2, #3878
	ldr	r1, .L735+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L720
.L732:
	ldr	r3, [r6, r4, asl #2]
	mov	r7, r0
	add	r0, r3, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReturnImage
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	b	.L720
.L704:
	ldr	r0, [r6, r4, asl #2]
	bgt	.L733
	cmp	r3, #0
	bne	.L707
	add	r0, r0, #475136
	mvn	r7, #0
	add	r0, r0, #1000
	mvn	r9, #1
	bl	SYNTAX_ReturnImage
	ldr	r0, [r6, r4, asl #2]
	mov	r1, r5
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r5, #184]
	ldr	r2, .L735+32
	mov	r0, #1
	ldr	r1, .L735+44
	bl	dprint_vfmw
	b	.L709
.L707:
	add	r0, r0, #475136
	mov	r1, r5
	add	r0, r0, #1000
	ldr	r7, .L735+4
	bl	SYNTAX_ReleaseImage
	ldr	r3, [fp, #-488]
	cmp	r3, #0
	beq	.L734
	ldr	r3, [r5, #184]
	mov	r0, #1
	ldr	r2, .L735+32
	ldr	r1, .L735+48
	bl	dprint_vfmw
	sub	r1, fp, #668
	ldr	r3, [r8, #52]
	mov	r2, #632
	mov	r0, r5
	blx	r3
	ldr	r3, [fp, #-644]
	ldr	r1, [fp, #-648]
	mvn	r0, #0
	mov	r2, #3
	str	r0, [r5, #188]
	str	r3, [r5, #200]
	mov	r3, #1
	str	r1, [r5, #196]
	str	r2, [r5, #276]
	str	r3, [r5, #180]
	b	.L701
.L724:
	ldr	r3, .L735+52
	movw	r2, #3879
	ldr	r1, .L735+28
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L720
.L733:
	add	r0, r0, #475136
	mvn	r7, #0
	add	r0, r0, #1000
	mvn	r9, #1
	bl	SYNTAX_ReturnImage
	ldr	r0, [r6, r4, asl #2]
	mov	r1, r5
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReleaseImage
	ldr	ip, [fp, #-484]
	ldr	r3, [r5, #184]
	mov	r0, #1
	ldr	r2, .L735+32
	ldr	r1, .L735+56
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L709
.L734:
	ldr	r0, [r7, r4, asl #2]
	sub	r1, fp, #668
	mvn	r7, #0
	mvn	r9, #1
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r5, #184]
	ldr	r2, .L735+32
	mov	r0, #1
	ldr	r1, .L735+48
	bl	dprint_vfmw
	b	.L709
.L736:
	.align	2
.L735:
	.word	.LC99
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	g_TraceImgPeriod
	.word	.LANCHOR1+184
	.word	.LC100
	.word	.LC1
	.word	.LANCHOR1+164
	.word	.LC101
	.word	.LC71
	.word	.LC103
	.word	.LC104
	.word	.LC2
	.word	.LC102
	UNWIND(.fnend)
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	2
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 632
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #636)
	sub	sp, sp, #636
	cmp	r0, #31
	mov	r4, r0
	mov	r7, r1
	bhi	.L758
	ldr	r8, .L766
	ldr	r0, [r8, r0, asl #2]
	cmp	r0, #0
	beq	.L759
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L760
	cmp	r1, #0
	beq	.L761
	ldr	r6, .L766+4
	mov	r2, r4
	ldr	r3, [r1, #148]
	mov	r0, #2
	ldr	r1, .L766+8
	bl	dprint_vfmw
	ldr	r3, [r6, #12]
	mov	r0, #4
	blx	r3
	ldr	r0, [r8, r4, asl #2]
	cmp	r0, #0
	movweq	r2, #4074
	ldreq	r1, .L766+12
	beq	.L757
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L762
	ldr	r1, [r7, #20]
	mov	r0, r4
	bl	VCTRL_TryToRelSpecialFrm
	subs	r5, r0, #0
	beq	.L763
	ldr	r0, [r8, r4, asl #2]
	mov	r1, r7
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r7, #188]
	cmn	r3, #1
	mov	r5, r0
	beq	.L746
	ldr	r0, [r8, r4, asl #2]
	sub	r1, fp, #668
	str	r3, [fp, #-520]
	add	r0, r0, #475136
	add	r0, r0, #1000
	bl	SYNTAX_ReleaseImage
	mov	r5, r0
.L746:
	mov	r0, #10
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L764
.L748:
	subs	r4, r5, #1
	mvnne	r4, #0
	cmp	r4, #0
	bne	.L765
.L750:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
.L739:
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L763:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
	movw	r2, #4095
	ldr	r1, .L766+16
	mov	r0, r5
	bl	dprint_vfmw
	mov	r4, r5
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L765:
	ldr	r2, .L766+20
	mov	r0, #0
	ldr	r1, .L766+24
	bl	dprint_vfmw
	b	.L750
.L764:
	ldr	r3, [r6]
	blx	r3
	ldr	r3, .L766+28
	ldr	r1, .L766+32
	add	r3, r3, r4, lsl #2
	ldr	r2, [r3, #-3048]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bls	.L748
	mov	r2, r4, asl #24
	movw	r1, #4125
	add	r2, r2, #655360
	ldr	r0, .L766+36
	cmp	r5, #1
	addeq	r2, r2, #1
	str	ip, [r3, #-3048]
	bl	DBG_AddTrace
	b	.L748
.L762:
	ldr	r1, .L766+40
	movw	r2, #4083
	mov	r0, #0
.L757:
	bl	dprint_vfmw
	ldr	r3, [r6, #16]
	mov	r0, #4
	mvn	r4, #0
	blx	r3
	b	.L739
.L760:
	ldr	r3, .L766+44
	movw	r2, #4066
	ldr	r1, .L766+48
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L739
.L758:
	ldr	r3, .L766+52
	mov	r2, #4064
	ldr	r1, .L766+48
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L739
.L761:
	mov	r0, r1
	ldr	r3, .L766+56
	movw	r2, #4067
	ldr	r1, .L766+48
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L739
.L759:
	ldr	r3, .L766+60
	movw	r2, #4065
	ldr	r1, .L766+48
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L739
.L767:
	.align	2
.L766:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC106
	.word	.LC107
	.word	.LC109
	.word	.LANCHOR1+228
	.word	.LC110
	.word	.LANCHOR3
	.word	g_TraceImgPeriod
	.word	.LANCHOR1+204
	.word	.LC108
	.word	.LC100
	.word	.LC1
	.word	.LC71
	.word	.LC105
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	2
	.global	VCTRL_GetVidStd
	.type	VCTRL_GetVidStd, %function
VCTRL_GetVidStd:
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
	bhi	.L769
	ldr	r3, .L773
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L769
	ldr	r2, [r3, #4]
	cmp	r2, #1
	beq	.L772
	mov	r3, r0
	movw	r2, #4157
	ldr	r1, .L773+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #21
	ldmfd	sp, {fp, sp, pc}
.L769:
	movw	r2, #4150
	ldr	r1, .L773+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #21
	ldmfd	sp, {fp, sp, pc}
.L772:
	ldr	r0, [r3, #536]
	ldmfd	sp, {fp, sp, pc}
.L774:
	.align	2
.L773:
	.word	.LANCHOR0
	.word	.LC112
	.word	.LC111
	UNWIND(.fnend)
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
	.align	2
	.global	VCTRL_GetHDRConfigInfo
	.type	VCTRL_GetHDRConfigInfo, %function
VCTRL_GetHDRConfigInfo:
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
	ldr	r3, .L776
	ldr	r2, [r3, r0, asl #2]
	ldrb	r2, [r2, #44]	@ zero_extendqisi2
	strb	r2, [r1, #65]
	ldr	r2, [r3, r0, asl #2]
	ldrb	r2, [r2, #46]	@ zero_extendqisi2
	strb	r2, [r1, #66]
	ldr	r2, [r3, r0, asl #2]
	ldr	r2, [r2, #152]
	str	r2, [r1, #76]
	ldr	r2, [r3, r0, asl #2]
	ldr	r2, [r2, #156]
	str	r2, [r1, #68]
	ldr	r3, [r3, r0, asl #2]
	ldr	r3, [r3, #160]
	str	r3, [r1, #72]
	ldmfd	sp, {fp, sp, pc}
.L777:
	.align	2
.L776:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetHDRConfigInfo, .-VCTRL_GetHDRConfigInfo
	.align	2
	.global	VCTRL_GetDecParam
	.type	VCTRL_GetDecParam, %function
VCTRL_GetDecParam:
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
	bhi	.L800
	ldr	r3, .L803
	ldr	r5, [r3, r0, asl #2]
	cmp	r5, #0
	moveq	r3, r5
	beq	.L779
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L802
.L800:
	mov	r3, #0
.L779:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L802:
	ldr	r3, [r5, #8]
	cmp	r3, #1
	bne	.L800
	ldr	r3, [r5, #536]
	cmp	r3, #18
	ldrls	pc, [pc, r3, asl #2]
	b	.L780
.L782:
	.word	.L781
	.word	.L790
	.word	.L784
	.word	.L790
	.word	.L780
	.word	.L790
	.word	.L787
	.word	.L780
	.word	.L790
	.word	.L790
	.word	.L790
	.word	.L790
	.word	.L790
	.word	.L790
	.word	.L780
	.word	.L792
	.word	.L793
	.word	.L790
	.word	.L795
.L790:
	add	r3, r5, #475136
	ldr	r4, [r3, #1012]
.L796:
	cmp	r4, #0
	moveq	r3, r4
	beq	.L779
	ldr	r3, .L803+4
	ldr	r3, [r3]
	blx	r3
	mov	r3, r4
	str	r0, [r5, #40]
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L787:
	add	r3, r5, #475136
	ldr	r4, [r3, #1024]
	b	.L796
.L792:
	add	r3, r5, #475136
	ldr	r4, [r3, #1236]
	b	.L796
.L793:
	add	r3, r5, #475136
	ldr	r4, [r3, #3860]
	b	.L796
.L784:
	add	r3, r5, #475136
	ldr	r4, [r3, #2044]
	b	.L796
.L795:
	add	r3, r5, #475136
	ldr	r4, [r3, #1048]
	b	.L796
.L781:
	add	r3, r5, #475136
	ldr	r4, [r3, #1368]
	b	.L796
.L780:
	ldr	r2, .L803+8
	mov	r0, #0
	ldr	r1, .L803+12
	bl	dprint_vfmw
	mov	r3, #0
	b	.L779
.L804:
	.align	2
.L803:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+252
	.word	.LC113
	UNWIND(.fnend)
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	2
	.global	VCTRL_IsSedOnlyMode
	.type	VCTRL_IsSedOnlyMode, %function
VCTRL_IsSedOnlyMode:
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
	beq	.L813
	cmp	r0, #0
	beq	.L808
	cmp	r0, #16
	bne	.L814
	add	r0, r4, #4096
	ldrb	r0, [r0, #1084]	@ zero_extendqisi2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L814:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L808:
	ldrb	r0, [r4, #1184]	@ zero_extendqisi2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L813:
	ldr	r1, .L815
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L816:
	.align	2
.L815:
	.word	.LC114
	UNWIND(.fnend)
	.size	VCTRL_IsSedOnlyMode, .-VCTRL_IsSedOnlyMode
	.align	2
	.global	VCTRL_ChanDecparamInValidFlag
	.type	VCTRL_ChanDecparamInValidFlag, %function
VCTRL_ChanDecparamInValidFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r0, #31
	mov	r2, r0
	bhi	.L818
	ldr	r5, .L829
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L818
	ldr	r1, [r3, #4]
	cmp	r1, #1
	bne	.L821
	ldr	r6, [r3, #8]
	cmp	r6, #1
	beq	.L822
.L821:
	ldr	r1, .L829+4
	mov	r0, #22
	mov	r4, #0
	bl	dprint_vfmw
.L820:
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L818:
	mov	r3, r2
	ldr	r1, .L829+8
	movw	r2, #4343
	mov	r0, #22
	bl	dprint_vfmw
	mov	r4, #0
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L822:
	str	r0, [fp, #-40]
	bl	VCTRL_GetDecParam
	ldr	r2, [fp, #-40]
	subs	r7, r0, #0
	beq	.L827
	ldr	r2, [r5, r2, asl #2]
	mov	r3, #0
	mov	r4, r3
	str	r3, [r2, #384]
	str	r3, [r2, #388]
	b	.L820
.L827:
	ldr	r8, [r5, r2, asl #2]
	ldr	r4, [r8, #384]
	cmp	r4, #0
	beq	.L828
	ldr	r3, .L829+12
	str	r2, [fp, #-40]
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [fp, #-40]
	ldr	r3, [r5, r2, asl #2]
	ldr	r2, [r3, #388]
	cmp	r0, r2
	bls	.L825
	rsb	r0, r2, r0
	cmp	r0, #40
	movls	r4, r7
	bls	.L820
.L825:
	str	r7, [r3, #384]
	mov	r4, r6
	str	r7, [r3, #388]
	b	.L820
.L828:
	ldr	r3, .L829+12
	str	r6, [r8, #384]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r8, #388]
	b	.L820
.L830:
	.align	2
.L829:
	.word	.LANCHOR0
	.word	.LC116
	.word	.LC115
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_ChanDecparamInValidFlag, .-VCTRL_ChanDecparamInValidFlag
	.align	2
	.global	VCTRL_ClearDecparam
	.type	VCTRL_ClearDecparam, %function
VCTRL_ClearDecparam:
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
	ldr	r3, .L848
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #536]
	cmp	r2, #18
	ldrls	pc, [pc, r2, asl #2]
	b	.L831
.L834:
	.word	.L833
	.word	.L843
	.word	.L836
	.word	.L843
	.word	.L831
	.word	.L843
	.word	.L839
	.word	.L831
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L831
	.word	.L844
	.word	.L845
	.word	.L843
	.word	.L847
.L843:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1012]
	ldmfd	sp, {fp, sp, pc}
.L844:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1236]
.L831:
	ldmfd	sp, {fp, sp, pc}
.L839:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1024]
	ldmfd	sp, {fp, sp, pc}
.L833:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1368]
	ldmfd	sp, {fp, sp, pc}
.L847:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1048]
	ldmfd	sp, {fp, sp, pc}
.L836:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #2044]
	ldmfd	sp, {fp, sp, pc}
.L845:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #3860]
	ldmfd	sp, {fp, sp, pc}
.L849:
	.align	2
.L848:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_ClearDecparam, .-VCTRL_ClearDecparam
	.align	2
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
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
	mov	r4, r0
	mov	r6, r1
	ldrhi	r3, .L863
	movwhi	r2, #4771
	bhi	.L860
	ldr	r5, .L863+4
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L862
	ldr	r3, [r3, #8]
	cmp	r3, #1
	beq	.L853
	ldr	r3, .L863+8
	movw	r2, #4773
.L860:
	ldr	r1, .L863+12
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L853:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, r4, asl #2]
	ldr	r3, [r0, #536]
	cmp	r3, #0
	beq	.L855
	cmp	r3, #16
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r0, r0, #475136
	mov	r1, r6
	add	r0, r0, #1008
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCDEC_VDMProcSedOnly
.L855:
	add	r0, r0, #475136
	mov	r1, r6
	add	r0, r0, #1008
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264DEC_VDMProcSedOnly
.L862:
	mov	r0, r3
	movw	r2, #4772
	ldr	r3, .L863+16
	ldr	r1, .L863+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L864:
	.align	2
.L863:
	.word	.LC117
	.word	.LANCHOR0
	.word	.LC118
	.word	.LC1
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_VdmProcSedOnly, .-VCTRL_VdmProcSedOnly
	.align	2
	.global	VCTRL_FlushDecoder
	.type	VCTRL_FlushDecoder, %function
VCTRL_FlushDecoder:
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
	ldr	r4, .L896
	mov	r5, r0
	ldr	r0, [r4, r0, asl #2]
	cmp	r0, #0
	beq	.L893
	add	r0, r0, #475136
	ldr	r2, [r0, #1000]
	cmp	r2, #18
	ldrls	pc, [pc, r2, asl #2]
	b	.L886
.L869:
	.word	.L868
	.word	.L870
	.word	.L871
	.word	.L872
	.word	.L886
	.word	.L873
	.word	.L874
	.word	.L886
	.word	.L875
	.word	.L876
	.word	.L877
	.word	.L877
	.word	.L877
	.word	.L878
	.word	.L886
	.word	.L879
	.word	.L880
	.word	.L881
	.word	.L882
.L882:
	add	r0, r0, #1008
	bl	AVS2DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L868:
	add	r0, r0, #1008
	bl	H264_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	r0, [r4, r5, asl #2]
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	FlushDPB
	cmp	r0, #0
	bne	.L894
.L886:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L870:
	add	r0, r0, #1008
	bl	VC1DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L871:
	add	r0, r0, #1008
	bl	MPEG4DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L872:
	add	r0, r0, #1008
	bl	MPEG2DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L873:
	add	r0, r0, #1008
	bl	DIVX3DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L874:
	add	r0, r0, #1008
	bl	AVSDEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L875:
	add	r0, r0, #1008
	bl	REAL8DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L876:
	add	r0, r0, #1008
	bl	REAL9DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L877:
	add	r0, r0, #1008
	bl	VP6DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L878:
	add	r0, r0, #1008
	bl	VP8DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L879:
	add	r0, r0, #1008
	bl	MVC_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	r0, [r4, r5, asl #2]
	mvn	r1, #0
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	MVC_FlushDPB
	cmp	r0, #0
	beq	.L886
	movw	r3, #4862
	ldr	r2, .L896+4
	ldr	r1, .L896+8
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L880:
	add	r0, r0, #1008
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L895
.L884:
	ldr	r1, .L896+12
	mov	r0, #32
	bl	dprint_vfmw
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L881:
	add	r0, r0, #1008
	bl	VP9DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L895:
	movw	r2, #4839
	ldr	r1, .L896+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L884
.L894:
	movw	r2, #4829
	ldr	r1, .L896+16
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L893:
	ldr	r3, .L896+20
	movw	r2, #4803
	ldr	r1, .L896+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L897:
	.align	2
.L896:
	.word	.LANCHOR0
	.word	.LANCHOR1+272
	.word	.LC121
	.word	.LC120
	.word	.LC119
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_FlushDecoder, .-VCTRL_FlushDecoder
	.align	2
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
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
	bhi	.L922
	ldr	r3, .L925
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L923
	ldr	r0, [r3, #8]
	cmp	r0, #1
	bne	.L924
	ldr	r2, [r3, #536]
	cmp	r2, #18
	ldrls	pc, [pc, r2, asl #2]
	b	.L918
.L904:
	.word	.L903
	.word	.L905
	.word	.L906
	.word	.L907
	.word	.L918
	.word	.L908
	.word	.L909
	.word	.L918
	.word	.L910
	.word	.L911
	.word	.L912
	.word	.L912
	.word	.L912
	.word	.L913
	.word	.L918
	.word	.L914
	.word	.L915
	.word	.L916
	.word	.L917
.L917:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_GetImageBuffer
.L903:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageBuffer
.L905:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_GetImageBuffer
.L906:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageBuffer
.L907:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_GetImageBuffer
.L908:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_GetImageBuffer
.L909:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_GetImageBuffer
.L910:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_GetImageBuffer
.L911:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_GetImageBuffer
.L912:
	ldr	r2, .L925+4
	ldr	r2, [r2, #-3180]
	tst	r2, #1
	ldmeqfd	sp, {fp, sp, pc}
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_GetImageBuffer
.L913:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_GetImageBuffer
.L914:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_GetImageBuffer
.L915:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageBuffer
.L916:
	add	r0, r3, #475136
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_GetImageBuffer
.L918:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L924:
	ldr	r3, .L925+8
	movw	r2, #4932
	ldr	r1, .L925+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L922:
	ldr	r3, .L925+16
	movw	r2, #4930
	ldr	r1, .L925+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L923:
	mov	r0, r3
	movw	r2, #4931
	ldr	r3, .L925+20
	ldr	r1, .L925+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L926:
	.align	2
.L925:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	.LC118
	.word	.LC1
	.word	.LC117
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_GetImageBuffer, .-VCTRL_GetImageBuffer
	.align	2
	.global	VCTRL_ConfigFFFBSpeed
	.type	VCTRL_ConfigFFFBSpeed, %function
VCTRL_ConfigFFFBSpeed:
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
	bhi	.L933
	ldr	r3, .L937
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L934
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L935
	cmp	r1, #0
	beq	.L936
	ldr	r2, [r1]
	mov	r0, #0
	str	r2, [r3, #1156]
	ldmfd	sp, {fp, sp, pc}
.L935:
	ldr	r3, .L937+4
	movw	r2, #5055
	ldr	r1, .L937+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L933:
	ldr	r3, .L937+12
	movw	r2, #5053
	ldr	r1, .L937+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L934:
	mov	r0, r3
	movw	r2, #5054
	ldr	r3, .L937+16
	ldr	r1, .L937+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L936:
	mov	r0, r1
	ldr	r3, .L937+20
	mov	r2, #5056
	ldr	r1, .L937+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L938:
	.align	2
.L937:
	.word	.LANCHOR0
	.word	.LC123
	.word	.LC1
	.word	.LC71
	.word	.LC122
	.word	.LC124
	UNWIND(.fnend)
	.size	VCTRL_ConfigFFFBSpeed, .-VCTRL_ConfigFFFBSpeed
	.align	2
	.global	VCTRL_ConfigPVRInfo
	.type	VCTRL_ConfigPVRInfo, %function
VCTRL_ConfigPVRInfo:
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
	bhi	.L945
	ldr	r3, .L949
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L946
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L947
	cmp	r1, #0
	beq	.L948
	ldr	r3, .L949+4
	add	r0, r0, #1184
	mov	r2, #20
	add	r0, r0, #8
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L947:
	ldr	r3, .L949+8
	movw	r2, #5068
	ldr	r1, .L949+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L945:
	ldr	r3, .L949+16
	movw	r2, #5066
	ldr	r1, .L949+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L948:
	mov	r0, r1
	ldr	r3, .L949+20
	movw	r2, #5069
	ldr	r1, .L949+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L946:
	ldr	r3, .L949+24
	movw	r2, #5067
	ldr	r1, .L949+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L950:
	.align	2
.L949:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC123
	.word	.LC1
	.word	.LC71
	.word	.LC124
	.word	.LC122
	UNWIND(.fnend)
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	2
	.global	VCTRL_IsChanDecable
	.type	VCTRL_IsChanDecable, %function
VCTRL_IsChanDecable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	ldr	r5, .L957
	mov	r4, r0
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L954
	sub	r1, fp, #44
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L954
	ldr	r3, [fp, #-36]
	cmp	r3, #16
	bgt	.L955
	ldr	r3, [fp, #-28]
	cmp	r3, #524288
	ble	.L954
.L955:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	subs	r0, r0, #1
	mvnne	r0, #0
	cmp	r0, #0
	bne	.L953
	ldr	r3, .L957+4
	ldr	r3, [r3]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	ldr	r3, [r3, #40]
	rsb	r0, r3, r0
	cmp	r0, #50
	movls	r0, #0
	mvnhi	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L954:
	mvn	r0, #0
.L953:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L958:
	.align	2
.L957:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_IsChanDecable, .-VCTRL_IsChanDecable
	.align	2
	.global	VCTRL_IsChanSegEnough
	.type	VCTRL_IsChanSegEnough, %function
VCTRL_IsChanSegEnough:
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
	ldr	r3, .L960
	ldr	r3, [r3, r0, asl #2]
	ldr	r0, [r3, #372]
	subs	r0, r0, #1
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L961:
	.align	2
.L960:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_IsChanSegEnough, .-VCTRL_IsChanSegEnough
	.align	2
	.global	VCTRL_IsChanActive
	.type	VCTRL_IsChanActive, %function
VCTRL_IsChanActive:
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
	bhi	.L968
	ldr	r3, .L969
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L968
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L968
	ldr	r2, [r3, #8]
	cmp	r2, #0
	beq	.L968
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L968
	ldr	r0, [r3, #536]
	cmp	r0, #21
	movne	r0, #0
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L968:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L970:
	.align	2
.L969:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_IsChanActive, .-VCTRL_IsChanActive
	.align	2
	.global	USERDEC_Init
	.type	USERDEC_Init, %function
USERDEC_Init:
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
	ldr	r3, .L988
	mov	r4, r0
	ldr	r6, [r0, #352]
	mov	r2, #368
	mov	r5, r1
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	str	r6, [r4, #352]
	add	r0, r4, #8
	bl	ResetVoQueue
	ldr	ip, .L988+4
	mov	r2, #0
	str	r5, [r4]
	b	.L975
.L972:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L987
.L975:
	ldr	r1, [ip], #4
	cmp	r1, #0
	add	r3, r1, #475136
	add	r3, r3, #1008
	beq	.L972
	cmp	r4, r3
	bne	.L972
	cmn	r2, #1
	str	r2, [r4, #360]
	beq	.L973
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L987:
	mvn	r3, #0
	str	r3, [r4, #360]
.L973:
	ldr	r1, .L988+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L989:
	.align	2
.L988:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC125
	UNWIND(.fnend)
	.size	USERDEC_Init, .-USERDEC_Init
	.align	2
	.global	USERDEC_RecycleImage
	.type	USERDEC_RecycleImage, %function
USERDEC_RecycleImage:
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
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L992
	mov	r2, #0
	ldr	r0, [r4, #360]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #360]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L993
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #360]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #360]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L993:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L992:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	USERDEC_RecycleImage, .-USERDEC_RecycleImage
	.align	2
	.global	VCTRL_GetUsrdecFrame
	.type	VCTRL_GetUsrdecFrame, %function
VCTRL_GetUsrdecFrame:
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
	ldr	r7, .L1013
	mov	r6, r0
	mov	r5, r1
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L1008
	ldr	r2, [r3, #536]
	cmp	r2, #20
	bne	.L1009
	ldr	r3, [r3, #460]
	cmp	r3, #2
	ble	.L1010
	mov	r1, #1
	bl	FSP_NewLogicFs
	subs	r8, r0, #0
	blt	.L1011
	mov	r1, r8
	mov	r0, r6
	bl	FSP_GetLogicFs
	mov	r2, r8
	ldr	r1, .L1013+4
	mov	r4, r0
	mov	r0, #18
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L1012
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L1001
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L1001
	ldr	r2, [r2, #8]
	mov	r0, #18
	ldr	r3, [r3, #8]
	ldr	r1, .L1013+8
	bl	dprint_vfmw
	ldr	r3, [r4, #28]
	ldr	r3, [r3, #8]
	str	r3, [r5, #40]
	ldr	r3, [r7, r6, asl #2]
	ldr	r3, [r3, #456]
	str	r3, [r5, #20]
	ldr	r3, [r4, #28]
	ldr	r3, [r3, #20]
	str	r3, [r5, #24]
	ldr	r3, [r4, #28]
	ldr	r0, [r3, #20]
	bl	MEM_Phy2Vir
	mov	r3, #0
	mov	r2, r3
	str	r3, [r5, #36]
	str	r0, [r5, #32]
.L996:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1009:
	ldr	r1, .L1013+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1010:
	ldr	r1, .L1013+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1001:
	ldr	r1, .L1013+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1011:
	ldr	r1, .L1013+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1008:
	mov	r0, r3
	movw	r2, #5343
	ldr	r3, .L1013+28
	ldr	r1, .L1013+32
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1012:
	movw	r2, #5373
	ldr	r1, .L1013+36
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L996
.L1014:
	.align	2
.L1013:
	.word	.LANCHOR0
	.word	.LC129
	.word	.LC131
	.word	.LC126
	.word	.LC127
	.word	.LC132
	.word	.LC128
	.word	.LC2
	.word	.LC1
	.word	.LC130
	UNWIND(.fnend)
	.size	VCTRL_GetUsrdecFrame, .-VCTRL_GetUsrdecFrame
	.align	2
	.global	InitSyntaxCtx
	.type	InitSyntaxCtx, %function
InitSyntaxCtx:
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
	ldr	r3, .L1035
	ldr	r1, [r3, r0, asl #2]
	cmp	r1, #0
	beq	.L1034
	ldr	r3, [r1, #536]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L1015
.L1019:
	.word	.L1018
	.word	.L1020
	.word	.L1021
	.word	.L1022
	.word	.L1015
	.word	.L1023
	.word	.L1024
	.word	.L1015
	.word	.L1025
	.word	.L1026
	.word	.L1027
	.word	.L1027
	.word	.L1027
	.word	.L1028
	.word	.L1015
	.word	.L1029
	.word	.L1030
	.word	.L1031
	.word	.L1032
	.word	.L1015
	.word	.L1033
.L1033:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_Init
.L1018:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_Init
.L1020:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_Init
.L1021:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_Init
.L1022:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_Init
.L1023:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_Init
.L1024:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_Init
.L1025:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_Init
.L1026:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_Init
.L1027:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_Init
.L1028:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_Init
.L1029:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_Init
.L1030:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_Init
.L1031:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_Init
.L1032:
	add	r0, r1, #475136
	add	r1, r1, #544
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_Init
.L1015:
	ldmfd	sp, {fp, sp, pc}
.L1034:
	mov	r0, r1
	ldr	r3, .L1035+4
	movw	r2, #5428
	ldr	r1, .L1035+8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L1036:
	.align	2
.L1035:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	2
	.global	VCTRL_VarifyOption
	.type	VCTRL_VarifyOption, %function
VCTRL_VarifyOption:
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
	ldr	r3, [r0, #36]
	cmp	r3, #0
	blt	.L1038
	ldr	r3, [r0, #12]
	cmp	r3, #31
	ble	.L1038
	ldr	r3, [r0, #16]
	cmp	r3, #31
	ble	.L1038
	ldr	r3, [r0, #56]
	cmp	r3, #262144
	blt	.L1038
	ldr	r3, [r0, #44]
	cmp	r3, #1
	beq	.L1044
	cmp	r3, #2
	bne	.L1042
	ldr	r3, [r0, #20]
	cmp	r3, #0
	ble	.L1038
	ldr	r3, [r0, #24]
	cmp	r3, #0
	ble	.L1038
.L1043:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ble	.L1038
	ldr	r3, [r0, #32]
	cmp	r3, #0
	bgt	.L1042
.L1038:
	ldr	r1, .L1045
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1042:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1044:
	ldr	r3, [r0, #20]
	cmp	r3, #0
	bgt	.L1043
	b	.L1038
.L1046:
	.align	2
.L1045:
	.word	.LC133
	UNWIND(.fnend)
	.size	VCTRL_VarifyOption, .-VCTRL_VarifyOption
	.align	2
	.global	VCTRL_GetMemSize_onDecode
	.type	VCTRL_GetMemSize_onDecode, %function
VCTRL_GetMemSize_onDecode:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, [r1, #40]
	mov	r4, r1
	mov	r6, r0
	cmp	r3, #0
	mov	r5, r2
	ldr	r1, [r1, #36]
	moveq	r0, #1
	beq	.L1049
	add	r0, r1, #1
	cmp	r0, #17
	movge	r0, #17
.L1049:
	ldr	r3, .L1062
	sub	r2, r6, #27
	cmp	r2, #6
	ldr	r2, [r4, #60]
	ldr	ip, [r3, #64]
	mvncc	lr, #1
	mvncs	lr, #0
	cmp	ip, #0
	beq	.L1053
	ldr	r8, .L1062+4
	add	r1, r2, r1
	ldr	r3, [r4, #16]
	add	r1, r1, #2
	ldr	r2, [r4, #12]
	mov	r7, #0
	str	r1, [sp, #4]
	mvn	r1, #-2147483648
	str	r0, [sp]
	mov	r0, #1
	str	lr, [sp, #12]
	str	r8, [sp, #16]
	str	r7, [sp, #8]
	blx	ip
	cmp	r0, r7
	bne	.L1053
	ldr	r3, .L1062+8
	cmp	r6, #26
	movwne	ip, #13616
	movweq	ip, #45800
	ldr	r2, [r3, #-2920]
	movtne	ip, 15
	movteq	ip, 180
	add	r3, r2, #16
	str	r3, [r5]
	ldr	r3, [r4, #168]
	cmp	r3, #1
	addne	r2, r2, #307200
	ldreq	r3, [r4, #56]
	addne	r2, r2, #2576
	strne	r2, [r5]
	ldrne	r3, [r4, #56]
	addeq	r3, r3, #339968
	addeq	r3, r3, #2576
	str	ip, [r5, #8]
	addne	r3, r3, #32768
	str	r3, [r5, #4]
	ldr	r3, [r4, #44]
	cmp	r3, #0
	movweq	r3, #58792
	movteq	r3, 19
	beq	.L1057
	ldr	r2, [r4, #20]
	movw	r0, #4060
	ldr	r7, [r4, #28]
	mov	r3, #4000
	ldr	lr, [r4, #32]
	mov	r1, #2208
	mul	r2, r0, r2
	mla	r3, r3, r7, r2
	mla	r3, r1, lr, r3
	cmp	r3, #0
	movcc	r3, #0
	cmp	r6, #26
	beq	.L1058
	movw	r2, #58792
	movt	r2, 19
	cmp	r3, r2
	movcc	r3, r2
.L1057:
	mov	r0, #0
	add	r3, r3, ip
	str	r3, [r5, #8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1053:
	movw	r2, #5591
	ldr	r1, .L1062+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1058:
	movw	r1, #3992
	mov	r0, #2240
	mla	r2, r1, r7, r2
	movw	r1, #58792
	movt	r1, 19
	mla	lr, r0, lr, r2
	cmp	lr, r1
	movcc	lr, r1
	cmp	lr, r3
	movcs	r3, lr
	b	.L1057
.L1063:
	.align	2
.L1062:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR3-2920
	.word	.LANCHOR3
	.word	.LC134
	UNWIND(.fnend)
	.size	VCTRL_GetMemSize_onDecode, .-VCTRL_GetMemSize_onDecode
	.align	2
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
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
	cmp	r3, #2
	mov	r5, r0
	mov	r4, r1
	mov	r6, r2
	beq	.L1065
	ldr	r1, .L1073
	ldr	r2, [r4, #36]
	ldr	r0, [r4, #60]
	ldr	r3, [r1, #-1688]
	ldr	lr, [r1, #-1684]
	add	r1, r2, r3
	cmp	r1, #16
	add	ip, r0, lr
	movge	r1, #16
	orrs	r7, r1, ip
	strpl	r1, [r4, #36]
	strpl	ip, [r4, #60]
	bmi	.L1072
.L1065:
	mov	r0, r4
	bl	VCTRL_VarifyOption
	cmp	r0, #0
	bne	.L1067
	mov	r2, r6
	mov	r1, r4
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_GetMemSize_onDecode
.L1072:
	stmia	sp, {r0, lr}
	mov	r0, #32
	ldr	r1, .L1073+4
	bl	dprint_vfmw
.L1067:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1074:
	.align	2
.L1073:
	.word	.LANCHOR3
	.word	.LC135
	UNWIND(.fnend)
	.size	VCTRL_GetChanMemSize, .-VCTRL_GetChanMemSize
	.align	2
	.global	CloseDrivers
	.type	CloseDrivers, %function
CloseDrivers:
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
	ldr	r5, [r0, #72]
	mov	r4, r0
	cmp	r5, #0
	beq	.L1076
	ldr	r5, [r0, #88]
	adds	r5, r5, #0
	movne	r5, #1
.L1076:
	ldr	r6, [r4, #16]
	ldr	r7, [r4, #8]
	cmp	r6, #0
	ldr	r8, [r4, #4]
	beq	.L1077
	ldr	r3, .L1132
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1078
	mov	r0, #0
	blx	r3
.L1079:
	cmp	r5, #0
	beq	.L1121
.L1080:
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
.L1077:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #64]
	ldr	r7, [r4, #56]
	cmp	r6, #0
	ldr	r8, [r4, #52]
	beq	.L1081
	ldr	r3, .L1132
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1082
	mov	r0, #0
	blx	r3
.L1083:
	cmp	r5, #0
	beq	.L1122
.L1084:
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #48
	ldr	r3, [r3, #48]
	blx	r3
.L1081:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #40]
	ldr	r7, [r4, #32]
	cmp	r6, #0
	ldr	r8, [r4, #28]
	bne	.L1123
.L1085:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	r5, [r4, #112]
	ldr	r6, [r4, #104]
	cmp	r5, #0
	ldr	r7, [r4, #100]
	bne	.L1124
.L1088:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #184]
	ldr	r6, [r4, #176]
	cmp	r5, #0
	ldr	r7, [r4, #172]
	bne	.L1125
.L1089:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #160]
	ldr	r6, [r4, #152]
	cmp	r5, #0
	ldr	r7, [r4, #148]
	bne	.L1126
.L1090:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #136]
	ldr	r6, [r4, #128]
	cmp	r5, #0
	ldr	r7, [r4, #124]
	bne	.L1127
.L1091:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #208]
	ldr	r6, [r4, #200]
	cmp	r5, #0
	ldr	r7, [r4, #196]
	bne	.L1128
.L1092:
	ldr	r4, .L1132+8
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r3, [r4, #376]
	cmp	r3, #1
	beq	.L1129
	ldr	r3, [r4, #380]
	ldr	r5, .L1132+8
	cmp	r3, #1
	beq	.L1130
.L1094:
	ldr	r3, [r4, #384]
	ldr	r4, .L1132+8
	cmp	r3, #1
	beq	.L1131
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1123:
	mov	r0, #0
	bl	SM_CloseSCDDrv
	cmp	r5, #0
	beq	.L1086
.L1087:
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, r2
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1085
.L1124:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #96
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1088
.L1128:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1132+4
	add	r0, r4, #192
	mov	r2, #24
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1092
.L1127:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #120
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1091
.L1126:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #144
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1090
.L1125:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1132+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #168
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1089
.L1078:
	mov	r0, r3
	movw	r2, #5935
	ldr	r1, .L1132+12
	bl	dprint_vfmw
	b	.L1079
.L1082:
	mov	r0, r3
	movw	r2, #5956
	ldr	r1, .L1132+12
	bl	dprint_vfmw
	b	.L1083
.L1131:
	ldr	r3, .L1132+4
	mov	r0, #13
	ldr	r5, [r3, #200]
	bl	VFMW_GetString
	ldr	r2, .L1132+16
	mov	r1, r0
	mov	r0, #181
	blx	r5
	mov	r3, #0
	mov	r0, #0
	str	r3, [r4, #384]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1122:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #56]
	bl	MEM_ReleaseMemBlock
	b	.L1084
.L1121:
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_ReleaseMemBlock
	b	.L1080
.L1129:
	ldr	r3, .L1132+4
	mov	r0, #0
	ldr	r5, [r3, #200]
	bl	VFMW_GetString
	ldr	r2, .L1132+16
	mov	r1, r0
	mov	r0, #127
	blx	r5
	mov	r3, #0
	str	r3, [r4, #376]
	ldr	r3, [r4, #380]
	ldr	r5, .L1132+8
	cmp	r3, #1
	bne	.L1094
.L1130:
	ldr	r3, .L1132+4
	mov	r0, #4
	ldr	r6, [r3, #200]
	bl	VFMW_GetString
	ldr	r2, .L1132+16
	mov	r1, r0
	mov	r0, #136
	blx	r6
	mov	r3, #0
	str	r3, [r5, #380]
	b	.L1094
.L1086:
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #32]
	bl	MEM_ReleaseMemBlock
	b	.L1087
.L1133:
	.align	2
.L1132:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC44
	.word	.LANCHOR3-1680
	UNWIND(.fnend)
	.size	CloseDrivers, .-CloseDrivers
	.align	2
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
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
	add	r4, r0, #96
	mov	r9, r0
	mov	r0, #0
	mov	r1, #65536
	mov	r2, r4
	movt	r0, 63683
	bl	MEM_MapRegisterAddr
	subs	r5, r0, #0
	bne	.L1135
	ldr	r2, [r9, #112]
	add	r4, r9, #168
	ldr	r1, [r9, #100]
	ldr	r0, [r9, #104]
	bl	MEM_AddMemRecord
	mov	r0, #53248
	mov	r2, r4
	movt	r0, 63683
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	subs	r6, r0, #0
	beq	.L1164
	mov	r2, #53248
	ldr	r1, .L1169
	movt	r2, 63683
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r3, .L1169+4
	mov	r1, r5
	mov	r0, r4
.L1159:
	mov	r2, #24
.L1154:
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r9
	bl	CloseDrivers
	mvn	r0, #0
.L1138:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1164:
	ldr	r2, [r9, #184]
	add	r8, r9, #144
	ldr	r1, [r9, #172]
	ldr	r0, [r9, #176]
	bl	MEM_AddMemRecord
	mov	r0, #49152
	mov	r2, r8
	movt	r0, 63683
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	subs	r5, r0, #0
	bne	.L1139
	ldr	r4, .L1169+4
	ldr	r2, [r9, #160]
	ldr	r1, [r9, #148]
	ldr	r0, [r9, #152]
	bl	MEM_AddMemRecord
	mov	r0, #15
	ldr	r6, [r4, #68]
	bl	VFMW_GetString
	ldr	r7, .L1169+8
	mov	r3, r5
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r6
	ldr	r3, [r7, #48]
	cmp	r3, #0
	beq	.L1141
	blx	r3
	subs	r2, r0, #0
	ble	.L1141
	str	r5, [sp]
	mov	r6, #3
	mov	r3, r9
	str	r6, [r9, #20]
	mov	r1, r5
	sub	r0, fp, #84
	bl	MEM_AllocMemBlock
	subs	r8, r0, #0
	bne	.L1165
	ldr	r2, [r9, #16]
	ldr	r1, [r9, #4]
	ldr	r0, [r9, #8]
	bl	MEM_AddMemRecord
	ldr	r3, [r4, #48]
	mov	r2, #20
	mov	r1, r8
	sub	r0, fp, #64
	blx	r3
	ldr	r3, [r7, #56]
	ldr	r1, [r9, #8]
	ldr	r2, [r9, #16]
	cmp	r3, #0
	str	r8, [fp, #-56]
	str	r1, [fp, #-64]
	str	r2, [fp, #-60]
	beq	.L1144
	sub	r0, fp, #64
	blx	r3
	subs	r7, r0, #0
	bne	.L1144
	str	r6, [r9, #68]
	mov	r0, #16
	ldr	r5, [r4, #68]
	bl	VFMW_GetString
	add	r8, r9, #48
	mov	r3, r7
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r5
	mov	r1, #1
	mov	r3, r8
	str	r1, [sp]
	mov	r2, #10240
	mov	r1, r7
	sub	r0, fp, #84
	bl	MEM_AllocMemBlock
	subs	r5, r0, #0
	bne	.L1166
	add	r3, r9, #24
	ldr	r1, [r9, #52]
	ldr	r2, [r9, #64]
	ldr	r0, [r9, #56]
	mov	r8, r3
	str	r3, [fp, #-92]
	bl	MEM_AddMemRecord
	ldr	r2, .L1169+12
	mov	r0, r5
	ldr	r3, [r9, #56]
	str	r3, [r2, #1196]
	ldr	r3, [r9, #56]
	add	r3, r3, #5120
	str	r3, [r2, #1200]
	bl	VDMDRV_Init
	mov	r0, #17
	ldr	r7, [r4, #68]
	bl	VFMW_GetString
	mov	r3, r5
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r7
	str	r6, [r9, #44]
	mov	r1, r5
	str	r5, [sp]
	sub	r0, fp, #84
	mov	r3, r8
	mov	r2, #716800
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L1146
	ldr	r2, [r9, #40]
	ldr	r1, [r9, #28]
	ldr	r0, [r9, #32]
	bl	MEM_AddMemRecord
	mov	r2, #0
	ldr	r1, [r9, #40]
	ldr	r0, [r9, #32]
	bl	SM_OpenSCDDrv
	subs	r6, r0, #0
	bne	.L1147
	ldr	r5, .L1169+16
	bl	SM_InstInit
	mov	r0, r6
	ldr	r7, [r4, #196]
	ldr	r4, .L1169+20
	ldr	r8, [r5, #88]
	bl	VFMW_GetString
	ldr	r1, .L1169+24
	str	r4, [sp]
	mov	r2, r8
	ldr	r8, .L1169+4
	mov	r3, r0
	mov	r0, #127
	blx	r7
	subs	r3, r0, #0
	str	r3, [fp, #-96]
	bne	.L1167
	ldr	r2, [r5, #88]
	mov	r0, #4
	ldr	r6, .L1169+28
	mov	r7, #1
	ldr	r10, [r8, #196]
	str	r2, [fp, #-88]
	str	r7, [r6, #376]
	bl	VFMW_GetString
	str	r4, [sp]
	ldr	r2, [fp, #-88]
	ldr	r1, .L1169+32
	mov	r3, r0
	mov	r0, #136
	blx	r10
	subs	r3, r0, #0
	str	r3, [fp, #-88]
	bne	.L1168
	mov	r0, #13
	ldr	r10, [r5, #88]
	str	r7, [r6, #380]
	ldr	r5, [r8, #196]
	bl	VFMW_GetString
	str	r4, [sp]
	mov	r2, r10
	ldr	r1, .L1169+36
	mov	r3, r0
	mov	r0, #181
	blx	r5
	cmp	r0, #0
	streq	r7, [r6, #384]
	beq	.L1138
	ldr	r1, .L1169+40
	mov	r2, #181
	ldr	r4, [fp, #-88]
.L1156:
	mov	r0, r4
	bl	dprint_vfmw
	ldr	r3, [r8, #48]
	mov	r1, r4
.L1157:
	ldr	r0, [fp, #-92]
.L1160:
	mov	r2, #24
	blx	r3
	mov	r0, r9
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1138
.L1135:
	mov	r2, #0
	ldr	r1, .L1169
	movt	r2, 63683
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, .L1169+4
	mov	r0, r4
	mov	r2, #24
	mov	r1, #0
	b	.L1154
.L1141:
	mov	r2, #0
	ldr	r1, .L1169+44
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	mov	r0, r8
.L1155:
	mov	r2, #24
	mov	r1, #0
	blx	r3
	mov	r0, r9
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1138
.L1139:
	mov	r2, #49152
	ldr	r1, .L1169
	movt	r2, 63683
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, .L1169+4
	mov	r1, r6
	mov	r0, r8
	b	.L1159
.L1167:
	ldr	r1, .L1169+40
	mov	r2, #127
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, [r8, #48]
	mov	r1, r6
	b	.L1157
.L1144:
	mov	r2, #0
	ldr	r1, .L1169+48
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	mov	r2, #24
	mov	r1, #0
.L1161:
	mov	r0, r9
	blx	r3
	mov	r0, r9
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1138
.L1168:
	mov	r2, #136
	ldr	r1, .L1169+40
	ldr	r4, [fp, #-96]
	b	.L1156
.L1147:
	ldr	r1, .L1169+52
	mov	r2, #0
.L1158:
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	ldr	r0, [fp, #-92]
	b	.L1155
.L1146:
	mov	r2, #0
	ldr	r1, .L1169+56
	b	.L1158
.L1165:
	mov	r2, r5
	ldr	r1, .L1169+60
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	mov	r1, r5
	mov	r2, #24
	b	.L1161
.L1166:
	ldr	r1, .L1169+64
	mov	r2, r7
	mov	r0, r7
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	mov	r1, r7
	mov	r0, r8
	b	.L1160
.L1170:
	.align	2
.L1169:
	.word	.LC136
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	g_HwMem
	.word	.LANCHOR2
	.word	.LANCHOR3-1680
	.word	VCTRL_Isr_0
	.word	.LANCHOR0
	.word	VCTRL_Scd_Isr
	.word	VCTRL_MMU_ISR
	.word	.LC143
	.word	.LC137
	.word	.LC139
	.word	.LC142
	.word	.LC141
	.word	.LC138
	.word	.LC140
	UNWIND(.fnend)
	.size	OpenDrivers, .-OpenDrivers
	.align	2
	.global	VCTRL_OpenVfmw
	.type	VCTRL_OpenVfmw, %function
VCTRL_OpenVfmw:
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
	ldr	r4, .L1206
	mov	r7, r0
	mov	r2, #8
	sub	r0, fp, #52
	mov	r1, #0
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, .L1206+4
	ldr	r5, [r3, #128]
	cmp	r5, #0
	bne	.L1201
	mov	r1, #1024
	ldr	r3, [r4, #80]
	str	r5, [fp, #-56]
	ldr	r0, .L1206+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1206+12
	ldr	r0, .L1206+8
	blx	r3
	ldr	r6, .L1206+16
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1174
	ldr	r3, [r4, #92]
	sub	r0, fp, #56
	ldr	r1, .L1206+20
	blx	r3
	cmp	r0, #0
	beq	.L1193
	sub	r0, fp, #56
	ldr	r3, [r4, #92]
	ldr	r1, .L1206+24
	blx	r3
	cmp	r0, #0
	beq	.L1202
	mov	r2, r5
	ldr	r3, [r4, #84]
	mov	r1, r5
	blx	r3
	mov	r2, r0
	str	r0, [r6, #-1688]
.L1178:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r8, #5000
	cmp	r3, r1
	bhi	.L1179
	cmp	r2, r8
	movw	r3, #60536
.L1200:
	movt	r3, 65535
	movge	r2, r8
	cmp	r2, r3
	movlt	r2, r3
.L1175:
	str	r2, [r6, #-1688]
.L1177:
	mov	r8, #0
	ldr	r3, [r4, #80]
	mov	r1, #1024
	str	r8, [fp, #-56]
	ldr	r0, .L1206+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1206+28
	ldr	r0, .L1206+8
	blx	r3
	ldr	r10, .L1206
	ldr	r9, .L1206+16
	cmp	r0, r8
	str	r0, [fp, #-56]
	beq	.L1180
	ldr	r3, [r10, #92]
	sub	r0, fp, #56
	ldr	r1, .L1206+20
	blx	r3
	cmp	r0, r8
	beq	.L1181
	sub	r0, fp, #56
	ldr	r3, [r10, #92]
	ldr	r1, .L1206+24
	blx	r3
	cmp	r0, r8
	beq	.L1203
	mov	r2, r8
	ldr	r3, [r10, #84]
	mov	r1, r8
	blx	r3
	mov	r2, r0
	str	r0, [r9, #-1684]
.L1184:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r8, #5000
	cmp	r3, r1
	bhi	.L1185
	cmp	r2, r8
	movw	r3, #60536
	movt	r3, 65535
	movlt	r5, r2
	movge	r5, r8
	cmp	r5, r3
	movlt	r5, r3
.L1181:
	str	r5, [r6, #-1684]
.L1183:
	ldr	r5, [r6, #-652]
	mov	r3, #0
	ldr	r8, .L1206+16
	cmp	r5, r3
	str	r3, [fp, #-56]
	beq	.L1186
	ldr	r2, .L1206+32
	ubfx	r1, r5, #1, #1
	and	r0, r5, #1
	ubfx	r3, r5, #2, #1
	strb	r0, [r8, #-648]
	ubfx	r5, r5, #3, #1
	strb	r1, [r2, #92]
	strb	r3, [r8, #-647]
	strb	r5, [r8, #-646]
.L1187:
	ldr	r5, .L1206+4
	mov	r2, #264
	ldr	r3, [r4, #48]
	mov	r1, #0
	add	r0, r5, #128
	ldr	r8, .L1206
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #128
	mov	r1, #0
	mov	r0, r5
	blx	r3
	ldr	r2, .L1206+36
	sub	r0, fp, #52
	mov	r1, #134217728
	mov	r3, #75497472
	str	r1, [fp, #-52]
	str	r2, [r6, #-644]
	str	r3, [fp, #-48]
	bl	MEM_InitMemManager
	bl	FSP_Init
	bl	ChanCtx_Init
	ldr	r3, [r4, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L1206+40
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r7, #8
	mov	r2, #24
	add	r0, r5, #224
	blx	r3
	add	r0, r5, #152
	bl	OpenDrivers
	cmp	r0, #0
	bne	.L1201
	ldr	r3, [r8, #124]
	mov	r1, #1
	blx	r3
	ldr	r3, [r8, #192]
	ldr	r2, .L1206+44
	add	r0, r5, #140
	ldr	r1, .L1206+48
	blx	r3
	cmp	r0, #0
	moveq	r3, #1
	streq	r3, [r5, #128]
	bne	.L1204
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1186:
	ldr	r3, [r4, #80]
	mov	r1, #1024
	ldr	r0, .L1206+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1206+52
	ldr	r0, .L1206+8
	blx	r3
	ldr	r9, .L1206
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1187
	ldr	r3, [r9, #92]
	sub	r0, fp, #56
	ldr	r1, .L1206+20
	blx	r3
	cmp	r0, #0
	ldreq	r0, [r8, #-652]
	beq	.L1189
	sub	r0, fp, #56
	ldr	r3, [r9, #92]
	ldr	r1, .L1206+24
	blx	r3
	cmp	r0, #0
	beq	.L1205
	ldr	r3, [r9, #84]
	mov	r2, r5
	mov	r1, r5
	blx	r3
	str	r0, [r8, #-652]
.L1189:
	ldr	r2, .L1206+32
	ubfx	r1, r0, #1, #1
	and	ip, r0, #1
	ubfx	r3, r0, #2, #1
	strb	ip, [r6, #-648]
	ubfx	r0, r0, #3, #1
	strb	r1, [r2, #92]
	strb	r3, [r6, #-647]
	strb	r0, [r6, #-646]
	b	.L1187
.L1180:
	ldr	r2, [r9, #-1684]
	b	.L1184
.L1174:
	ldr	r2, [r6, #-1688]
	b	.L1178
.L1185:
	ldr	r1, .L1206+56
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r5, [r6, #-1684]
	movw	r3, #60536
	cmp	r5, r8
	movt	r3, 65535
	movge	r5, r8
	cmp	r5, r3
	movlt	r5, r3
	b	.L1181
.L1179:
	ldr	r1, .L1206+60
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r2, [r6, #-1688]
	movw	r3, #60536
	cmp	r2, r8
	b	.L1200
.L1193:
	mov	r2, r5
	b	.L1175
.L1204:
	add	r0, r5, #152
	bl	CloseDrivers
.L1201:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1202:
	movw	r3, #6800
	ldr	r2, .L1206+64
	ldr	r1, .L1206+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1177
.L1203:
	movw	r3, #6846
	ldr	r2, .L1206+72
	ldr	r1, .L1206+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1183
.L1205:
	movw	r3, #6902
	ldr	r2, .L1206+76
	ldr	r1, .L1206+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1187
.L1207:
	.align	2
.L1206:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR3-1676
	.word	.LC144
	.word	.LANCHOR3
	.word	.LC145
	.word	.LC146
	.word	.LC149
	.word	.LANCHOR2
	.word	VCTRL_EventReport
	.word	.LANCHOR3-640
	.word	VFMW_CTRL_thread_proc
	.word	.LC152
	.word	.LC151
	.word	.LC150
	.word	.LC148
	.word	.LANCHOR1+292
	.word	.LC147
	.word	.LANCHOR1+312
	.word	.LANCHOR1+332
	UNWIND(.fnend)
	.size	VCTRL_OpenVfmw, .-VCTRL_OpenVfmw
	.align	2
	.global	GetNextDecodeMode
	.type	GetNextDecodeMode, %function
GetNextDecodeMode:
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
	movw	r6, #21846
	mov	r3, r2, asl #1
	cmp	r2, #0
	movt	r6, 21845
	add	r5, r2, #7
	smull	r6, r7, r3, r6
	movge	r5, r2
	mov	r5, r5, asr #3
	str	r2, [sp]
	mov	r6, r0
	str	r1, [sp, #4]
	mov	r4, r2
	mov	r8, r1
	sub	r3, r7, r3, asr #31
	ldr	r1, .L1216
	mov	r2, r5
	mov	r0, #30
	bl	dprint_vfmw
	cmp	r6, #3
	beq	.L1214
	cmp	r4, r8
	movge	r4, r6
	blt	.L1215
.L1210:
	mov	r2, r6
	mov	r3, r4
	ldr	r1, .L1216+4
	mov	r0, #30
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1215:
	ldr	r1, .L1216+8
	mov	r0, #30
	bl	dprint_vfmw
.L1213:
	mov	r4, #3
	b	.L1210
.L1214:
	cmp	r5, r8
	ble	.L1213
	ldr	r1, .L1216+12
	mov	r0, #30
	bl	dprint_vfmw
	mov	r4, #0
	b	.L1210
.L1217:
	.align	2
.L1216:
	.word	.LC153
	.word	.LC156
	.word	.LC155
	.word	.LC154
	UNWIND(.fnend)
	.size	GetNextDecodeMode, .-GetNextDecodeMode
	.align	2
	.global	VCTRL_GetChanIDByCtx
	.type	VCTRL_GetChanIDByCtx, %function
VCTRL_GetChanIDByCtx:
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
	ldr	ip, .L1228
	mov	r2, #0
	b	.L1221
.L1219:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L1227
.L1221:
	ldr	r1, [ip], #4
	cmp	r1, #0
	add	r3, r1, #475136
	add	r3, r3, #1008
	beq	.L1219
	cmp	r0, r3
	bne	.L1219
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L1227:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1229:
	.align	2
.L1228:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetChanIDByCtx, .-VCTRL_GetChanIDByCtx
	.align	2
	.global	VCTRL_GetChanIDByMemAddr
	.type	VCTRL_GetChanIDByMemAddr, %function
VCTRL_GetChanIDByMemAddr:
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
	ldr	r4, .L1242
	mov	lr, #0
.L1235:
	ldr	r2, [r4], #4
	cmp	r2, #0
	beq	.L1231
	movw	r1, #15544
	add	r3, r2, #471040
	movt	r1, 7
	add	r3, r3, #952
	add	r1, r2, r1
.L1234:
	ldr	r2, [r3]
	cmp	r2, r0
	bhi	.L1232
	ldr	ip, [r3, #-20]
	add	r2, r2, ip
	cmp	r0, r2
	bcc	.L1236
.L1232:
	add	r3, r3, #72
	cmp	r3, r1
	bne	.L1234
.L1231:
	add	lr, lr, #1
	cmp	lr, #32
	bne	.L1235
	mvn	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L1236:
	mov	r0, lr
	ldmfd	sp, {r4, fp, sp, pc}
.L1243:
	.align	2
.L1242:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	2
	.global	DecChanProcessPts
	.type	DecChanProcessPts, %function
DecChanProcessPts:
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
	ldr	r6, .L1266
	mov	r4, r1
	mov	r5, r0
	ldr	ip, [r6, r0, asl #2]
	ldr	r1, [ip, #52]
	cmp	r1, #1
	beq	.L1261
	sub	r3, r1, #2
	cmp	r1, #6
	cmpne	r3, #1
	bls	.L1257
.L1246:
	ldrd	r2, [r4, #32]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1262
	add	r1, ip, #608
	strd	r2, [r1, #-8]
.L1256:
	ldrd	r8, [r4, #48]
	add	r5, ip, #624
	add	lr, ip, #640
	ldr	r1, .L1266+4
	mov	r0, #29
	strd	r8, [r5, #-8]
	ldrd	r6, [r4, #56]
	strd	r6, [lr, #-8]
	ldr	lr, [r4, #64]
	str	lr, [ip, #648]
	ldr	lr, [r4, #68]
	str	lr, [ip, #652]
	ldr	lr, [r4, #72]
	str	lr, [ip, #656]
	ldr	lr, [r4, #76]
	str	lr, [ip, #672]
	strd	r8, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1261:
	add	r3, ip, #475136
	ldr	r3, [r3, #1008]
	ldr	r1, [r3, #556]
	sxtb	r1, r1
	cmp	r1, #1
	bne	.L1246
.L1257:
	add	r0, ip, #1088
	add	r2, r4, #8
	add	r0, r0, #8
	bl	IsNewpicSeg
	cmp	r0, #0
	bne	.L1247
	ldr	ip, [r6, r5, asl #2]
	add	lr, ip, #608
	ldr	r3, [ip, #52]
	cmp	r3, #3
	beq	.L1263
	ldrd	r2, [lr]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1264
	strd	r2, [lr, #-8]
.L1249:
	add	r7, ip, #624
	mvn	r0, #0
	mvn	r1, #0
	strd	r0, [lr]
	ldrd	r0, [r7]
	add	lr, ip, #640
	strd	r0, [r7, #-8]
	ldrd	r0, [lr]
	orrs	r7, r0, r1
	strd	r0, [lr, #-8]
	ldreqd	r0, [r4, #56]
	streqd	r0, [lr, #-8]
.L1251:
	ldr	r1, [ip, #676]
	mov	r0, #29
	ldr	r8, [ip, #660]
	ldr	r7, [ip, #664]
	ldr	lr, [ip, #668]
	str	r1, [ip, #672]
	str	r8, [ip, #648]
	ldr	r1, .L1266+8
	str	r7, [ip, #652]
	str	lr, [ip, #656]
	bl	dprint_vfmw
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	beq	.L1265
.L1252:
	ldrd	r2, [r4, #32]
	mvn	r7, #0
	mvn	r6, #0
	cmp	r3, r7
	cmpeq	r2, r6
	addne	r0, r1, #608
	strned	r2, [r0]
.L1254:
	ldrd	r2, [r4, #48]
	add	r0, r1, #624
	add	ip, r1, #640
	strd	r2, [r0]
	ldrd	r2, [r4, #56]
	strd	r2, [ip]
	ldr	r3, [r4, #64]
	str	r3, [r1, #660]
	ldr	r3, [r4, #68]
	str	r3, [r1, #664]
	ldr	r3, [r4, #72]
	str	r3, [r1, #668]
	ldr	r3, [r4, #76]
	str	r3, [r1, #676]
.L1253:
	ldrd	r2, [r0, #-8]
	mov	r0, #29
	ldr	r1, .L1266+12
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1265:
	ldrd	r2, [r4, #32]
	add	lr, r1, #608
	add	ip, r1, #624
	add	r0, r1, #640
	strd	r2, [lr]
	ldrd	r2, [r4, #48]
	strd	r2, [ip]
	ldrd	r2, [r4, #56]
	strd	r2, [r0]
	ldr	r3, [r4, #64]
	str	r3, [r1, #660]
	ldr	r3, [r4, #68]
	str	r3, [r1, #664]
	ldr	r3, [r4, #72]
	str	r3, [r1, #668]
	ldr	r3, [r4, #76]
	str	r3, [r1, #676]
.L1247:
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	addeq	r0, r1, #624
	bne	.L1252
	b	.L1253
.L1262:
	add	r3, ip, #608
	ldrd	r2, [r3, #-8]
	b	.L1256
.L1263:
	ldrd	r2, [lr]
	strd	r2, [lr, #-8]
	b	.L1249
.L1264:
	ldrd	r2, [lr, #-8]
	b	.L1249
.L1267:
	.align	2
.L1266:
	.word	.LANCHOR0
	.word	.LC159
	.word	.LC157
	.word	.LC158
	UNWIND(.fnend)
	.size	DecChanProcessPts, .-DecChanProcessPts
	.align	2
	.global	DecChanCheckDecParam
	.type	DecChanCheckDecParam, %function
DecChanCheckDecParam:
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
	ldr	r3, .L1276
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #536]
	sub	r3, r2, #10
	cmp	r3, #2
	bhi	.L1269
	ldr	r3, .L1276+4
	ldr	r3, [r3, #-3180]
	ands	r3, r3, #1
	beq	.L1270
.L1269:
	bic	r3, r2, #16
	cmp	r3, #4
	cmpne	r2, #14
	movne	r3, #1
	moveq	r3, #0
	beq	.L1270
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	mvnne	r3, #1
	moveq	r3, #0
.L1270:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1277:
	.align	2
.L1276:
	.word	.LANCHOR0
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	DecChanCheckDecParam, .-DecChanCheckDecParam
	.align	2
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
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
	mov	r4, r0
	bhi	.L1317
	ldr	r6, .L1327
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1318
	ldr	r2, [r0, #8]
	cmp	r2, #1
	bne	.L1319
	ldr	r5, [r0, #24]
	cmp	r5, #0
	bne	.L1320
	ldr	r9, .L1327+4
	mov	r8, r4, asl #2
	str	r5, [r0, #372]
	ldr	r7, .L1327+8
	ldr	r3, [r9]
	blx	r3
	add	r2, r7, r8
	ldr	r3, [r2, #-512]
	mov	r1, r0
	ldr	r0, .L1327+12
	rsb	r3, r3, r1
	ldr	r0, [r0]
	cmp	r3, r0
	mov	r0, r4
	bls	.L1284
	str	r1, [r2, #-512]
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	bne	.L1285
	mov	r2, r4
	ldr	r1, .L1327+16
	mov	r0, #23
	bl	dprint_vfmw
.L1301:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1284:
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	beq	.L1301
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	mvnne	r10, #2
	bne	.L1301
.L1295:
	ldr	r2, [r6, r4, asl #2]
	add	r3, r2, #442368
	ldr	r3, [r3, #2056]
	cmp	r3, #1
	beq	.L1321
	cmp	r3, #3
	beq	.L1322
	ldrb	r3, [r2, #681]	@ zero_extendqisi2
	add	r10, r2, #680
	cmp	r3, #0
	addne	r2, r2, #688
	bne	.L1288
	ldr	r3, [r2, #1432]
	add	r2, r2, #688
	cmp	r3, #0
	beq	.L1323
.L1288:
	ldrd	r0, [r2, #40]
	ldrd	r2, [r2, #24]
	strd	r0, [fp, #-60]
	mov	r0, #29
	strd	r2, [fp, #-52]
	ldrd	r2, [fp, #-60]
	ldr	r1, .L1327+20
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	bl	dprint_vfmw
	mov	r1, r10
	mov	r0, r4
	bl	DecChanProcessPts
	mov	r0, #3
	bl	CHECK_REC_POS_ENABLE
	adds	r0, r0, #0
	movne	r0, #1
	cmp	r5, #1
	movne	r0, #0
	cmp	r0, #0
	bne	.L1324
.L1290:
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r10
	add	r2, r3, #475136
	add	r2, r2, #1008
	ldr	r1, [r3, #536]
	bl	DecodeStream
	mov	r0, #4
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1325
.L1315:
	mov	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1285:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	moveq	r5, r0
	beq	.L1295
	mov	r2, r4
	ldr	r1, .L1327+24
	mov	r0, #23
	mvn	r10, #2
	bl	dprint_vfmw
	b	.L1301
.L1325:
	ldr	r3, [r9]
	add	r7, r7, r8
	blx	r3
	ldr	r1, .L1327+28
	ldr	r3, [r7, #-384]
	ldr	r1, [r1]
	rsb	r3, r3, r0
	mov	r2, r0
	cmp	r3, r1
	bls	.L1315
	mov	r0, r4
	str	r2, [r7, #-384]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L1315
	mov	r2, r4, asl #24
	movw	r1, #6550
	add	r2, r2, #262144
	ldr	r0, .L1327+32
	bl	DBG_AddTrace
	b	.L1315
.L1319:
	ldr	r3, .L1327+36
	movw	r2, #6450
	ldr	r1, .L1327+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1301
.L1320:
	ldr	r3, .L1327+44
	movw	r2, #6451
	ldr	r1, .L1327+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1301
.L1323:
	mov	r1, r2
	mov	r0, r4
	str	r2, [fp, #-52]
	bl	SM_ReadSegStream
	ldr	r2, [fp, #-52]
	cmp	r0, #0
	beq	.L1288
	cmp	r5, #1
	beq	.L1326
.L1289:
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #1
	mvn	r10, #3
	str	r2, [r3, #372]
	b	.L1301
.L1317:
	ldr	r3, .L1327+48
	movw	r2, #6448
	ldr	r1, .L1327+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1301
.L1324:
	mov	r2, r4, asl #24
	movw	r1, #6532
	add	r2, r2, #196608
	ldr	r0, .L1327+32
	bl	DBG_AddTrace
	b	.L1290
.L1318:
	ldr	r3, .L1327+52
	movw	r2, #6449
	ldr	r1, .L1327+40
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1301
.L1321:
	ldr	r1, .L1327+56
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r10, #2
	b	.L1301
.L1322:
	ldr	r2, [r2, #1384]
	mov	r0, #31
	ldr	r1, .L1327+60
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1301
.L1326:
	mov	r2, r4
	ldr	r1, .L1327+64
	mov	r0, #23
	bl	dprint_vfmw
	b	.L1289
.L1328:
	.align	2
.L1327:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	g_TraceBsPeriod
	.word	.LC161
	.word	.LC166
	.word	.LC162
	.word	g_TraceFramePeriod
	.word	.LANCHOR1+348
	.word	.LC118
	.word	.LC1
	.word	.LC160
	.word	.LC71
	.word	.LC100
	.word	.LC163
	.word	.LC164
	.word	.LC165
	UNWIND(.fnend)
	.size	DecChanSyntax, .-DecChanSyntax
	.align	2
	.global	DecSyntax
	.type	DecSyntax, %function
DecSyntax:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r0, .L1358
	ldr	r1, .L1358+4
	sub	r3, r0, #128
.L1332:
	ldr	r2, [r1, #4]!
	add	r3, r3, #4
	cmp	r2, #0
	ldrne	r2, [r2, #20]
	str	r2, [r3, #-4]
	cmp	r3, r0
	bne	.L1332
	ldr	r7, .L1358+8
	mvn	ip, #0
	ldr	r6, .L1358+12
	mov	r8, #0
	ldr	r10, .L1358+16
	mov	r9, r7
.L1333:
	mov	r3, #0
	ldr	r0, [r6, #-256]
	mov	r4, r3
	ldr	r1, .L1358+20
	b	.L1334
.L1336:
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	movlt	r0, r2
	movlt	r4, r3
.L1334:
	add	r3, r3, #1
	cmp	r3, #32
	bne	.L1336
	add	r3, r6, r4, lsl #2
	cmp	r0, #0
	add	r2, r4, #1
	mov	r1, #0
	str	r8, [r3, #-256]
	str	r2, [r7, #148]
	ldr	r3, .L1358+8
	ble	.L1337
	ldr	r3, [r9, r4, asl #2]
	cmp	r3, r1
	beq	.L1333
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bne	.L1333
	ldr	r2, [r3, #76]
	cmp	r2, r1
	ble	.L1339
	ldr	r5, [r3, #80]
	cmp	r5, r1
	beq	.L1356
.L1339:
	mov	r5, #500
	b	.L1344
.L1342:
	cmp	r0, #0
	bne	.L1333
	subs	r5, r5, #1
	beq	.L1333
.L1344:
	mov	r0, r4
	bl	DecChanSyntax
	cmn	r0, #1
	mov	ip, r0
	bne	.L1342
	ldr	r5, [r6, #-644]
	cmp	r5, #0
	beq	.L1350
	mov	r3, #0
	str	r0, [fp, #-72]
	mov	r2, r3
	mov	r0, r4
	mov	r1, #102
	blx	r5
	ldr	ip, [fp, #-72]
.L1350:
	mov	r0, ip
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1356:
	mov	r0, r4
	sub	r1, fp, #68
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L1357
.L1340:
	ldr	r5, [r7, r4, asl #2]
	ldr	r1, [fp, #-56]
	ldr	r2, [r5, #76]
	ldr	r0, [r5, #552]
	bl	GetNextDecodeMode
	ldr	r3, [r7, r4, asl #2]
	str	r0, [r5, #552]
	ldr	r2, [r3, #552]
	cmp	r2, #0
	strne	r8, [r3, #548]
	strne	r8, [r3, #544]
	ldreq	r2, [r3, #72]
	streq	r2, [r3, #548]
	streq	r2, [r3, #544]
	b	.L1339
.L1337:
	mov	r0, ip
	str	r1, [r3, #148]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1357:
	mov	r1, r5
	sub	r0, fp, #68
	ldr	r3, [r10, #48]
	mov	r2, #24
	blx	r3
	b	.L1340
.L1359:
	.align	2
.L1358:
	.word	.LANCHOR3-128
	.word	.LANCHOR0-4
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-256
	UNWIND(.fnend)
	.size	DecSyntax, .-DecSyntax
	.align	2
	.global	VCTRL_RunProcess
	.type	VCTRL_RunProcess, %function
VCTRL_RunProcess:
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
	ldr	r5, .L1371
	mov	r0, #0
	bl	VCTRL_RecordPosTime
	ldrb	r3, [r5, #1792]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1369
.L1361:
	ldr	r0, [r5, #912]
	mov	r3, #100
	ldr	r6, .L1371+4
	cmp	r0, #0
	str	r3, [r5, #144]
	ble	.L1362
	ldr	r3, [r6, #120]
	blx	r3
.L1362:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	bl	SM_Wakeup
	ldr	r3, [r5, #908]
	mov	r2, #101
	str	r2, [r5, #144]
	cmp	r3, #0
	movne	r7, #0
	beq	.L1370
.L1363:
	mov	r3, #102
	str	r3, [r5, #144]
	bl	VDMDRV_WakeUpVdm
	mov	r4, #0
.L1364:
	mov	r0, r4
	mov	r1, #0
	add	r4, r4, #1
	bl	DeleteRawPacketInBuffer
	cmp	r4, #32
	bne	.L1364
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	mov	r0, #1
	mov	r3, #105
	str	r3, [r5, #144]
	bl	VCTRL_RecordPosTime
	mov	r1, #0
	ldr	r3, [r6, #132]
	mov	r0, r1
	mov	r2, #10
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1370:
	bl	DecSyntax
	mov	r7, r0
	b	.L1363
.L1369:
	mov	r0, #11
	bl	VCTRL_RecordPosTime
	mov	r3, #0
	strb	r3, [r5, #1792]
	b	.L1361
.L1372:
	.align	2
.L1371:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_RunProcess, .-VCTRL_RunProcess
	.align	2
	.global	VFMW_CTRL_thread_proc
	.type	VFMW_CTRL_thread_proc, %function
VFMW_CTRL_thread_proc:
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
	ldr	r4, .L1400
	ldr	r6, .L1400+4
.L1374:
.L1381:
	ldr	r1, .L1400+8
	mov	r0, #2
	mov	r3, #0
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r5, #2
	str	r5, [r4, #132]
	cmp	r3, r5
	bne	.L1396
	b	.L1379
.L1398:
	str	r5, [r4, #144]
	bl	VCTRL_RunProcess
	ldr	r1, .L1400+12
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	cmp	r3, #2
	beq	.L1379
.L1396:
	cmp	r3, #3
	bne	.L1398
.L1377:
	ldr	r1, .L1400+16
	mov	r0, #2
	mov	r3, #6
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #132]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1379:
	ldr	r1, .L1400+20
	mov	r0, #2
	mov	r3, #4
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r4, #132]
	b	.L1376
.L1399:
	ldr	r3, [r6, #120]
	blx	r3
.L1376:
	ldr	r1, .L1400+24
	mov	r0, #22
	mov	r3, #5
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r0, #10
	cmp	r3, #1
	beq	.L1381
	cmp	r3, #3
	bne	.L1399
	b	.L1377
.L1401:
	.align	2
.L1400:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC167
	.word	.LC169
	.word	.LC171
	.word	.LC168
	.word	.LC170
	UNWIND(.fnend)
	.size	VFMW_CTRL_thread_proc, .-VFMW_CTRL_thread_proc
	.align	2
	.global	VCTRL_GetChanVoQue
	.type	VCTRL_GetChanVoQue, %function
VCTRL_GetChanVoQue:
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
	ldr	r3, .L1422
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L1420
	ldr	r2, [r3, #536]
	cmp	r2, #20
	ldrls	pc, [pc, r2, asl #2]
	b	.L1421
.L1405:
	.word	.L1419
	.word	.L1406
	.word	.L1407
	.word	.L1408
	.word	.L1421
	.word	.L1409
	.word	.L1410
	.word	.L1421
	.word	.L1411
	.word	.L1412
	.word	.L1413
	.word	.L1413
	.word	.L1413
	.word	.L1414
	.word	.L1421
	.word	.L1415
	.word	.L1416
	.word	.L1417
	.word	.L1418
	.word	.L1421
	.word	.L1419
.L1419:
	add	r0, r3, #475136
	add	r0, r0, #1016
	ldmfd	sp, {fp, sp, pc}
.L1406:
	movw	r0, #1128
	movt	r0, 8
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1407:
	add	r0, r3, #495616
	add	r0, r0, #3152
	ldmfd	sp, {fp, sp, pc}
.L1408:
	add	r0, r3, #561152
	add	r0, r0, #3184
	ldmfd	sp, {fp, sp, pc}
.L1409:
	add	r0, r3, #516096
	add	r0, r0, #2064
	ldmfd	sp, {fp, sp, pc}
.L1410:
	add	r0, r3, #491520
	add	r0, r0, #816
	ldmfd	sp, {fp, sp, pc}
.L1411:
	movw	r0, #6200
	movt	r0, 8
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1412:
	add	r0, r3, #528384
	add	r0, r0, #2096
	ldmfd	sp, {fp, sp, pc}
.L1413:
	add	r0, r3, #487424
	add	r0, r0, #1408
	ldmfd	sp, {fp, sp, pc}
.L1414:
	add	r0, r3, #483328
	add	r0, r0, #1024
	ldmfd	sp, {fp, sp, pc}
.L1415:
	movw	r0, #17976
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1416:
	movw	r0, #23560
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1417:
	add	r0, r3, #753664
	add	r0, r0, #936
	ldmfd	sp, {fp, sp, pc}
.L1418:
	add	r0, r3, #491520
	add	r0, r0, #2688
	ldmfd	sp, {fp, sp, pc}
.L1421:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1420:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1423:
	.align	2
.L1422:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	2
	.global	VCTRL_FindOccupiedFrame
	.type	VCTRL_FindOccupiedFrame, %function
VCTRL_FindOccupiedFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r0, #31
	mov	r6, r0
	bhi	.L1440
	bl	VCTRL_GetChanVoQue
	subs	r7, r0, #0
	beq	.L1435
	sub	r2, fp, #36
	mov	r3, #0
	sub	r1, fp, #44
	str	r3, [fp, #-44]
	str	r3, [r2, #-4]!
	bl	GetQueueImgNum
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	beq	.L1435
	cmp	r2, #32
	bhi	.L1428
.L1431:
	ldr	r3, .L1442
	ldrh	r1, [r7, #4]
	ldr	ip, [r3, r6, asl #2]
	and	r1, r1, #63
	add	lr, ip, #475136
	add	r1, r7, r1, lsl #2
	ldr	r3, [lr, #936]
	ldr	r1, [r1, #12]
	cmp	r3, #32
	bhi	.L1429
	add	ip, ip, r3, lsl #4
	mov	r4, #0
	add	ip, ip, #475136
	mov	r5, #0
	mov	r0, #1
	add	ip, ip, #412
	mov	r8, #0
	b	.L1432
.L1433:
	ldrh	r1, [r7, #4]
	cmp	r3, #33
	add	r1, r1, r0
	add	r0, r0, #1
	and	r1, r1, #63
	add	r1, r7, r1, lsl #2
	ldr	r1, [r1, #12]
	beq	.L1429
.L1432:
	ldr	r1, [r1, #20]
	cmp	r0, r2
	strd	r4, [ip, #4]
	add	r3, r3, #1
	str	r8, [ip, #-4]
	add	ip, ip, #16
	str	r1, [ip, #-16]
	str	r3, [lr, #936]
	bcc	.L1433
.L1439:
	mov	r0, #0
.L1441:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1435:
	mvn	r0, #0
.L1426:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1429:
	mov	r2, r6
	ldr	r1, .L1442+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1441
.L1428:
	mov	r3, #32
	ldr	r1, .L1442+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	bne	.L1431
	b	.L1439
.L1440:
	ldr	r3, .L1442+12
	movw	r2, #3489
	ldr	r1, .L1442+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1426
.L1443:
	.align	2
.L1442:
	.word	.LANCHOR0
	.word	.LC173
	.word	.LC172
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_FindOccupiedFrame, .-VCTRL_FindOccupiedFrame
	.align	2
	.global	VCTRL_ReportOccupiedFrame
	.type	VCTRL_ReportOccupiedFrame, %function
VCTRL_ReportOccupiedFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r0, #31
	mov	r7, r0
	mov	r4, r1
	bhi	.L1461
	cmp	r1, #0
	beq	.L1462
	bl	VCTRL_GetChanVoQue
	subs	r5, r0, #0
	mvneq	r0, #0
	beq	.L1446
	ldr	r6, .L1464
	sub	r8, fp, #36
	mov	r3, #0
	mov	r0, #4
	str	r3, [r8, #-4]!
	ldr	r2, [r6, #12]
	str	r3, [fp, #-44]
	blx	r2
	mov	r2, r8
	sub	r1, fp, #44
	mov	r0, r5
	bl	GetQueueImgNum
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	beq	.L1448
	cmp	r2, #32
	bhi	.L1463
.L1449:
	mov	ip, #0
	mov	r1, ip
	mov	lr, ip
.L1451:
	ldrh	r3, [r5, #4]
	add	r0, r4, r1, lsl #4
	add	ip, ip, #1
	mov	r7, #0
	add	r3, r3, r1
	and	r3, r3, #63
	uxth	ip, ip
	add	r3, r5, r3, lsl #2
	ldr	r3, [r3, #12]
	ldr	r8, [r3, #20]
	str	r8, [r0, #4]
	ldr	r3, [r3, #504]
	str	r7, [r0, #12]
	str	r3, [r0, #8]
	str	lr, [r4, r1, asl #4]
	sxth	r1, ip
	cmp	r1, r2
	bcc	.L1451
	uxth	r3, r2
.L1450:
	ldrh	r1, [r5, #4]
	add	r3, r3, r1
	and	r3, r3, #63
	strh	r3, [r5, #4]	@ movhi
	str	r2, [r4, #528]
.L1452:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
	mov	r0, #0
.L1446:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1448:
	ldr	ip, .L1464+4
	ldr	r3, [ip, r7, asl #2]
	add	r1, r3, #475136
	ldr	r1, [r1, #936]
	cmp	r1, #0
	beq	.L1452
	mov	r0, r2
	mov	lr, r2
.L1453:
	mov	r1, r0, asl #4
	add	r5, r0, #29696
	add	r3, r3, r1
	add	r1, r4, r1
	add	r3, r3, #475136
	add	r5, r5, #26
	add	r3, r3, #408
	mov	r8, #0
	add	r2, r2, #1
	ldr	r3, [r3, #4]
	uxth	r2, r2
	str	r3, [r1, #4]
	ldr	r3, [ip, r7, asl #2]
	ldr	r3, [r3, r5, asl #4]
	str	r8, [r1, #12]
	str	r3, [r1, #8]
	str	lr, [r4, r0, asl #4]
	sxth	r0, r2
	ldr	r3, [ip, r7, asl #2]
	add	r1, r3, #475136
	ldr	r1, [r1, #936]
	cmp	r0, r1
	bcc	.L1453
	str	r1, [r4, #528]
	b	.L1452
.L1463:
	mov	r3, #32
	ldr	r1, .L1464+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	moveq	r3, r2
	bne	.L1449
	b	.L1450
.L1461:
	ldr	r3, .L1464+12
	movw	r2, #3605
	ldr	r1, .L1464+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1446
.L1462:
	mov	r0, r1
	ldr	r3, .L1464+20
	movw	r2, #3606
	ldr	r1, .L1464+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1446
.L1465:
	.align	2
.L1464:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC172
	.word	.LC71
	.word	.LC1
	.word	.LC174
	UNWIND(.fnend)
	.size	VCTRL_ReportOccupiedFrame, .-VCTRL_ReportOccupiedFrame
	.align	2
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
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
	ldr	r4, .L1479
	mov	r5, r0
	mov	r6, r1
	mov	r7, r2
	mov	r8, r3
	ldr	ip, [r4, r0, asl #2]
	cmp	ip, #0
	beq	.L1475
	bl	VCTRL_GetChanVoQue
	subs	r3, r0, #0
	beq	.L1468
	mov	r2, r8
	mov	r1, r7
	bl	GetQueueImgNum
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [r3, #536]
	cmp	r2, #0
	beq	.L1476
	cmp	r2, #16
	beq	.L1477
	cmp	r2, #17
	moveq	r3, #9
	streq	r3, [r6]
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r2, #15
	beq	.L1478
	cmp	r2, #18
	moveq	r3, #5
	movne	r3, #2
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1476:
	add	r3, r3, #499712
	ldr	r3, [r3, #3144]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1468:
	str	r3, [r8]
	str	r3, [r7]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1477:
	add	r3, r3, #475136
	ldr	r3, [r3, #4032]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1478:
	add	r3, r3, #11534336
	add	r3, r3, #61440
	ldr	r3, [r3, #3896]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1475:
	mov	r0, ip
	ldr	r3, .L1479+4
	movw	r2, #6662
	ldr	r1, .L1479+8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1480:
	.align	2
.L1479:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_GetChanImgNum, .-VCTRL_GetChanImgNum
	.align	2
	.global	VCTRL_GetChanState
	.type	VCTRL_GetChanState, %function
VCTRL_GetChanState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	cmp	r0, #31
	mov	r6, r0
	mov	r4, r1
	bhi	.L1491
	cmp	r1, #0
	beq	.L1492
	ldr	r7, .L1494
	ldr	r0, [r7, r0, asl #2]
	cmp	r0, #0
	beq	.L1493
	ldr	r3, .L1494+4
	mov	r5, #0
	mov	r1, r5
	mov	r2, #100
	str	r5, [fp, #-56]
	mov	r0, r4
	ldr	r3, [r3, #48]
	str	r5, [fp, #-60]
	str	r5, [fp, #-64]
	blx	r3
	ldr	r2, [r7, r6, asl #2]
	movw	r3, #2027
	ldr	r2, [r2, #1112]
	str	r2, [r4, #32]
	ldr	r2, [r7, r6, asl #2]
	ldr	r2, [r2, #1116]
	str	r2, [r4, #36]
	ldr	r2, [r7, r6, asl #2]
	ldr	r2, [r2, #1120]
	str	r2, [r4, #44]
	ldr	r1, [r7, r6, asl #2]
	add	r2, r1, #442368
	ldrsb	r0, [r2, r3]
	cmp	r0, r5
	ble	.L1489
	movw	r3, #7290
	mov	r2, r5
	movt	r3, 7
	add	r3, r1, r3
	mov	r1, r5
.L1488:
	ldrsb	ip, [r3]
	add	r2, r2, #1
	add	r3, r3, #88
	cmp	ip, #3
	addeq	r1, r1, #1
	cmp	r2, r0
	bne	.L1488
.L1486:
	str	r1, [r4, #84]
	movw	lr, #2027
	ldr	ip, [r7, r6, asl #2]
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	add	ip, ip, #442368
	mov	r0, r6
	ldrsb	ip, [ip, lr]
	str	ip, [r4, #92]
	bl	VCTRL_GetChanImgNum
	ldr	ip, .L1494+8
	mov	r3, #300
	ldr	r0, [fp, #-56]
	ldr	r2, [fp, #-60]
	sub	r1, fp, #52
	mla	r3, r3, r6, ip
	add	r2, r2, r0
	str	r2, [r4, #48]
	mov	r0, r6
	ldr	r2, [r3, #-108]
	str	r2, [r4, #96]
	ldr	r3, [r3, #-120]
	str	r3, [r4, #20]
	bl	SM_GetInfo
	ldr	r3, [fp, #-32]
	ldr	r1, [fp, #-36]
	ldr	r2, [fp, #-44]
	cmp	r3, #10
	str	r1, [r4, #52]
	movle	r3, #0
	movgt	r3, #1
	str	r2, [r4, #56]
	str	r3, [r4, #80]
	ldr	r3, [r7, r6, asl #2]
	add	r3, r3, #491520
	ldrb	r3, [r3, #496]	@ zero_extendqisi2
	and	r3, r3, #1
	str	r3, [r4, #88]
.L1481:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1491:
	ldr	r3, .L1494+12
	mov	r2, #1456
	ldr	r1, .L1494+16
	mov	r0, #0
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1493:
	ldr	r3, .L1494+20
	movw	r2, #1459
	ldr	r1, .L1494+16
	bl	dprint_vfmw
	b	.L1481
.L1489:
	mov	r1, r5
	b	.L1486
.L1492:
	mov	r0, r1
	ldr	r3, .L1494+24
	movw	r2, #1458
	ldr	r1, .L1494+16
	bl	dprint_vfmw
	b	.L1481
.L1495:
	.align	2
.L1494:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	.LC175
	.word	.LC1
	.word	.LC177
	.word	.LC176
	UNWIND(.fnend)
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	2
	.global	VCTRL_GetChanWidth
	.type	VCTRL_GetChanWidth, %function
VCTRL_GetChanWidth:
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
	bhi	.L1500
	ldr	r3, .L1502
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1501
	ldr	r0, [r0, #1228]
	ldmfd	sp, {fp, sp, pc}
.L1500:
	ldr	r3, .L1502+4
	movw	r2, #6726
	ldr	r1, .L1502+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1501:
	ldr	r3, .L1502+12
	movw	r2, #6727
	ldr	r1, .L1502+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1503:
	.align	2
.L1502:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	2
	.global	VCTRL_GetChanHeight
	.type	VCTRL_GetChanHeight, %function
VCTRL_GetChanHeight:
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
	bhi	.L1508
	ldr	r3, .L1510
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1509
	ldr	r0, [r0, #1232]
	ldmfd	sp, {fp, sp, pc}
.L1508:
	ldr	r3, .L1510+4
	movw	r2, #6734
	ldr	r1, .L1510+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1509:
	ldr	r3, .L1510+12
	movw	r2, #6735
	ldr	r1, .L1510+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1511:
	.align	2
.L1510:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	2
	.global	VCTRL_GetChanCapLevel
	.type	VCTRL_GetChanCapLevel, %function
VCTRL_GetChanCapLevel:
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
	bhi	.L1516
	ldr	r3, .L1517
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #36]
	moveq	r0, #33
	ldmfd	sp, {fp, sp, pc}
.L1516:
	ldr	r3, .L1517+4
	movw	r2, #6742
	ldr	r1, .L1517+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1518:
	.align	2
.L1517:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	2
	.global	VCTRL_SetVdecExtra
	.type	VCTRL_SetVdecExtra, %function
VCTRL_SetVdecExtra:
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
	add	r3, r0, #4992
	ldr	r5, .L1526
	add	r3, r3, #8
	movw	r2, #10000
	cmp	r3, r2
	mov	r4, r1
	str	r0, [r5, #-1688]
	bhi	.L1524
.L1520:
	movw	r1, #5000
	cmp	r0, r1
	movw	r2, #60536
	add	r3, r4, #4992
	movge	r0, r1
	movt	r2, 65535
	cmp	r0, r2
	add	r3, r3, #8
	movw	r1, #10000
	str	r4, [r5, #-1684]
	movlt	r0, r2
	cmp	r3, r1
	str	r0, [r5, #-1688]
	ldr	r6, .L1526
	bhi	.L1525
.L1521:
	movw	r2, #5000
	cmp	r4, r2
	movw	r3, #60536
	movge	r4, r2
	movt	r3, 65535
	cmp	r4, r3
	movlt	r4, r3
	str	r4, [r5, #-1684]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1524:
	mov	r2, r0
	ldr	r1, .L1526+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r0, [r5, #-1688]
	b	.L1520
.L1525:
	mov	r2, r4
	ldr	r1, .L1526+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r4, [r6, #-1684]
	b	.L1521
.L1527:
	.align	2
.L1526:
	.word	.LANCHOR3
	.word	.LC178
	.word	.LC179
	UNWIND(.fnend)
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	2
	.global	VfmwProcGetHandler
	.type	VfmwProcGetHandler, %function
VfmwProcGetHandler:
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
	subs	r1, r0, #0
	ldrne	r3, .L1540
	bne	.L1532
	b	.L1538
.L1533:
	ldr	r2, [r3, #8]!
	cmp	r2, r1
	beq	.L1539
.L1532:
	ldr	r0, [r3, #12]
	cmp	r0, #0
	bne	.L1533
	ldmfd	sp, {fp, sp, pc}
.L1539:
	ldmfd	sp, {fp, sp, pc}
.L1538:
	ldr	r0, .L1540+4
	ldmfd	sp, {fp, sp, pc}
.L1541:
	.align	2
.L1540:
	.word	.LANCHOR1+364
	.word	VfmwProc_SetPrintLevel
	UNWIND(.fnend)
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	2
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
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
	beq	.L1549
	cmp	r0, #0
	ldrne	r3, .L1555
	bne	.L1547
	b	.L1554
.L1548:
	ldr	lr, [r3, #8]!
	cmp	r0, lr
	beq	.L1545
.L1547:
	ldr	ip, [r3, #12]
	cmp	ip, #0
	bne	.L1548
	mov	r2, r0
	ldr	r1, .L1555+4
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1554:
	ldr	ip, .L1555+8
.L1545:
	mov	r0, r1
	blx	ip
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1549:
	mvn	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1556:
	.align	2
.L1555:
	.word	.LANCHOR1+364
	.word	.LC180
	.word	VfmwProc_SetPrintLevel
	UNWIND(.fnend)
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	2
	.global	VCTRL_GetLastFrameIdPlus2
	.type	VCTRL_GetLastFrameIdPlus2, %function
VCTRL_GetLastFrameIdPlus2:
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
	bhi	.L1561
	ldr	r3, .L1562
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #376]
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1561:
	ldr	r3, .L1562+4
	movw	r2, #7981
	ldr	r1, .L1562+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1563:
	.align	2
.L1562:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_GetLastFrameIdPlus2, .-VCTRL_GetLastFrameIdPlus2
	.align	2
	.global	VCTRL_SetLastFrameIdPlus2
	.type	VCTRL_SetLastFrameIdPlus2, %function
VCTRL_SetLastFrameIdPlus2:
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
	bhi	.L1570
	ldr	r3, .L1571
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #376]
	ldmfd	sp, {fp, sp, pc}
.L1570:
	ldr	r3, .L1571+4
	movw	r2, #7993
	ldr	r1, .L1571+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L1572:
	.align	2
.L1571:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameIdPlus2, .-VCTRL_SetLastFrameIdPlus2
	.align	2
	.global	VCTRL_SetLastFrameState
	.type	VCTRL_SetLastFrameState, %function
VCTRL_SetLastFrameState:
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
	bhi	.L1579
	ldr	r3, .L1580
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #380]
	ldmfd	sp, {fp, sp, pc}
.L1579:
	ldr	r3, .L1580+4
	movw	r2, #8005
	ldr	r1, .L1580+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L1581:
	.align	2
.L1580:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	2
	.global	VCTRL_ReportLastFrame
	.type	VCTRL_ReportLastFrame, %function
VCTRL_ReportLastFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	subs	r5, r1, #0
	mov	r4, r0
	moveq	r2, #2
	beq	.L1584
	cmp	r5, #1
	moveq	r2, #3
	movne	r2, #4
.L1584:
	cmp	r4, #31
	bhi	.L1596
	ldr	r6, .L1597
	ldr	r3, [r6, r4, asl #2]
	cmp	r3, #0
	strne	r2, [r3, #380]
.L1587:
	ldr	r3, .L1597+4
	ldr	ip, [r3, #-644]
	cmp	ip, #0
	beq	.L1588
	sub	r2, fp, #28
	mov	r3, #4
	mov	r1, #115
	mov	r0, r4
	str	r5, [r2, #-4]!
	blx	ip
.L1588:
	ldr	ip, [r6, r4, asl #2]
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L1597+8
	mov	r0, #1
	ldr	ip, [ip, #380]
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1596:
	ldr	r3, .L1597+12
	movw	r2, #8005
	ldr	r1, .L1597+16
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r6, .L1597
	b	.L1587
.L1598:
	.align	2
.L1597:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	.LC181
	.word	.LC71
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	2
	.global	VCTRL_OutputLastFrame
	.type	VCTRL_OutputLastFrame, %function
VCTRL_OutputLastFrame:
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
	ldr	r3, .L1626
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	add	r0, r3, #475136
	ldr	r2, [r0, #1000]
	cmp	r2, #18
	ldrls	pc, [pc, r2, asl #2]
	b	.L1620
.L1602:
	.word	.L1601
	.word	.L1603
	.word	.L1604
	.word	.L1605
	.word	.L1620
	.word	.L1606
	.word	.L1607
	.word	.L1620
	.word	.L1608
	.word	.L1609
	.word	.L1610
	.word	.L1610
	.word	.L1610
	.word	.L1611
	.word	.L1620
	.word	.L1612
	.word	.L1613
	.word	.L1614
	.word	.L1615
.L1615:
	add	r0, r0, #1008
	bl	AVS2DEC_GetRemainImg
	mov	r4, r0
.L1600:
	cmn	r4, #1
	beq	.L1617
	cmp	r4, #0
	bne	.L1625
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1626+4
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1601:
	add	r0, r0, #1008
	bl	H264DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1603:
	add	r0, r0, #1008
	bl	VC1DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1604:
	add	r0, r0, #1008
	bl	MPEG4DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1605:
	add	r0, r0, #1008
	bl	MPEG2DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1606:
	add	r0, r0, #1008
	bl	DIVX3DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1607:
	add	r0, r0, #1008
	bl	AVSDEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1608:
	add	r0, r0, #1008
	bl	REAL8DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1609:
	add	r0, r0, #1008
	bl	REAL9DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1610:
	add	r0, r0, #1008
	bl	VP6DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1611:
	add	r0, r0, #1008
	bl	VP8DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1612:
	add	r0, r0, #1008
	bl	MVC_DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1613:
	add	r0, r0, #1008
	bl	HEVCDEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1614:
	add	r0, r0, #1008
	bl	VP9DEC_GetRemainImg
	mov	r4, r0
	b	.L1600
.L1625:
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	sub	r2, r4, #2
	ldr	r1, .L1626+8
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1620:
	mvn	r4, #0
.L1617:
	mov	r0, r5
	mov	r1, #1
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1626+12
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1627:
	.align	2
.L1626:
	.word	.LANCHOR0
	.word	.LC183
	.word	.LC184
	.word	.LC182
	UNWIND(.fnend)
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	2
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r5, .L1674
	mov	r4, r0
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1666
	ldr	lr, [r0, #536]
	ldr	r6, [r0, #1168]
	cmp	lr, #18
	ldrls	pc, [pc, lr, asl #2]
	b	.L1628
.L1632:
	.word	.L1631
	.word	.L1633
	.word	.L1634
	.word	.L1635
	.word	.L1628
	.word	.L1636
	.word	.L1637
	.word	.L1628
	.word	.L1638
	.word	.L1639
	.word	.L1640
	.word	.L1640
	.word	.L1640
	.word	.L1641
	.word	.L1628
	.word	.L1642
	.word	.L1643
	.word	.L1644
	.word	.L1645
.L1643:
	add	r0, r0, #475136
	str	r3, [sp, #4]
	add	r0, r0, #1008
	mov	r3, r2
	str	r6, [sp]
	mov	r2, #1
	bl	HEVCDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r7, .L1674
	add	r3, r3, #475136
	ldrb	r3, [r3, #1019]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1667
.L1648:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #475136
	strne	r2, [r3, #3860]
.L1628:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1645:
	add	r0, r0, #475136
	mov	r2, r6
	add	r0, r0, #1008
	ldr	r7, .L1674
	bl	AVS2DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #475136
	ldrb	r3, [r3, #1008]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1668
.L1653:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #475136
	strne	r2, [r3, #1048]
	b	.L1628
.L1631:
	add	r0, r0, #475136
	str	r3, [sp, #4]
	add	r0, r0, #1008
	mov	r3, r2
	str	r6, [sp]
	mov	r2, #1
	bl	H264DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r7, .L1674
	add	r3, r3, #487424
	ldrb	r3, [r3, #2280]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1669
.L1646:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #475136
	strne	r2, [r3, #1368]
	b	.L1628
.L1633:
	add	r0, r0, #475136
	ldr	r6, .L1674
	add	r0, r0, #1008
	bl	VC1DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #487424
	ldrb	r2, [r2, #1463]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1670
.L1654:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1012]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1634:
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	MPEG4DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1674
	add	r2, r3, #495616
	ldrb	r2, [r2, #3540]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1671
.L1651:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #2044]
	b	.L1628
.L1635:
	add	r0, r0, #475136
	ldr	r6, .L1674
	add	r0, r0, #1008
	bl	MPEG2DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #561152
	ldrb	r2, [r2, #3554]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1654
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #561152
	strb	r1, [r2, #3554]
	b	.L1654
.L1636:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetSwitchRounding
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #475136
	add	r0, r0, #1008
	bl	DIVX3DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1012]
	b	.L1628
.L1637:
	add	r0, r0, #475136
	ldr	r6, .L1674
	add	r0, r0, #1008
	bl	AVSDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #475136
	ldrb	r2, [r3, #1008]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1672
.L1652:
	mov	r2, #0
	str	r2, [r3, #1024]
	b	.L1628
.L1638:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #475136
	add	r0, r0, #1008
	bl	REAL8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1012]
	b	.L1628
.L1639:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #475136
	add	r0, r0, #1008
	bl	REAL9DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1012]
	b	.L1628
.L1640:
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	VP6DEC_VDMPostProc
.L1665:
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1012]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1641:
	add	r0, r0, #475136
	add	r0, r0, #1008
	bl	VP8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1012]
	b	.L1628
.L1642:
	add	r0, r0, #475136
	mov	r2, #1
	add	r0, r0, #1008
	bl	MVC_DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1674
	add	r3, r3, #475136
	ldrb	r2, [r3, #1009]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1673
.L1655:
	mov	r2, #0
	str	r2, [r3, #1236]
	b	.L1628
.L1644:
	add	r0, r0, #475136
	mov	r2, r6
	add	r0, r0, #1008
	bl	VP9DEC_VDMPostProc
	cmp	r6, #1
	bne	.L1665
	b	.L1628
.L1666:
	ldr	r3, .L1674+4
	movw	r2, #4566
	ldr	r1, .L1674+8
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1673:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #475136
	mov	r3, r2
	strb	r1, [r2, #1009]
	b	.L1655
.L1672:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #475136
	mov	r3, r2
	strb	r1, [r2, #1008]
	b	.L1652
.L1671:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #495616
	strb	r1, [r2, #3540]
	b	.L1651
.L1670:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #487424
	strb	r1, [r2, #1463]
	b	.L1654
.L1667:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	strb	r2, [r3, #1019]
	b	.L1648
.L1669:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #487424
	strb	r2, [r3, #2280]
	b	.L1646
.L1668:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	strb	r2, [r3, #1008]
	b	.L1653
.L1675:
	.align	2
.L1674:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	2
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
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
	mov	r6, r2
	mov	r7, r3
	mov	r4, r0
	mov	r5, r1
	ldrhi	r3, .L1683
	movwhi	r2, #4755
	bhi	.L1681
	ldr	ip, .L1683+4
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L1682
	ldr	ip, [ip, #8]
	cmp	ip, #1
	beq	.L1679
	ldr	r3, .L1683+8
	movw	r2, #4757
.L1681:
	ldr	r1, .L1683+12
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1679:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_PostProc
.L1682:
	mov	r0, ip
	ldr	r3, .L1683+16
	movw	r2, #4756
	ldr	r1, .L1683+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1684:
	.align	2
.L1683:
	.word	.LC117
	.word	.LANCHOR0
	.word	.LC118
	.word	.LC1
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	2
	.global	VCTRL_SvdecLastFrame
	.type	VCTRL_SvdecLastFrame, %function
VCTRL_SvdecLastFrame:
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
	add	r1, r1, #2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_ReportLastFrame
	UNWIND(.fnend)
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.align	2
	.global	Get_YuvFormat
	.type	Get_YuvFormat, %function
Get_YuvFormat:
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
	cmp	r1, #6
	ldrls	pc, [pc, r1, asl #2]
	b	.L1687
.L1689:
	.word	.L1688
	.word	.L1690
	.word	.L1691
	.word	.L1692
	.word	.L1693
	.word	.L1694
	.word	.L1695
.L1695:
	cmp	r0, #1
	moveq	r0, #1
	movne	r0, #7
	ldmfd	sp, {fp, sp, pc}
.L1688:
	cmp	r0, #1
	moveq	r0, #0
	movne	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L1690:
	cmp	r0, #1
	moveq	r0, #2
	movne	r0, #8
	ldmfd	sp, {fp, sp, pc}
.L1691:
	cmp	r0, #1
	moveq	r0, #4
	movne	r0, #10
	ldmfd	sp, {fp, sp, pc}
.L1692:
	cmp	r0, #1
	moveq	r0, #3
	movne	r0, #9
	ldmfd	sp, {fp, sp, pc}
.L1693:
	cmp	r0, #1
	moveq	r0, #5
	movne	r0, #11
	ldmfd	sp, {fp, sp, pc}
.L1694:
	cmp	r0, #1
	moveq	r0, #13
	movne	r0, #12
	ldmfd	sp, {fp, sp, pc}
.L1687:
	mov	r3, r1
	movw	r2, #8712
	ldr	r1, .L1704
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #13
	ldmfd	sp, {fp, sp, pc}
.L1705:
	.align	2
.L1704:
	.word	.LC185
	UNWIND(.fnend)
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	2
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
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
	mov	r5, r1
	ldr	r1, [r1, #40]
	mov	r8, r0
	bl	FSP_GetLogicIdByPhyAddr
	cmn	r0, #1
	mov	r7, r0
	beq	.L1714
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L1709
	mov	r1, r0
	mov	r2, #0
	mov	r0, r8
	bl	FSP_ClearLogicFs
	mov	r0, #0
.L1708:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1709:
	ldr	r0, [r5, #48]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L1715
.L1710:
	mov	r1, r7
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1716
	str	r7, [r4, #148]
	add	ip, r4, #576
	ldrd	r2, [r5, #64]
	add	r0, r4, #592
	add	r1, r4, #608
	mov	r6, #0
	mov	r9, #1
	strd	r2, [ip]
	ldrd	r2, [r5, #64]
	strd	r2, [r0, #-8]
	ldrd	r2, [r5, #64]
	strd	r2, [r0]
	ldrd	r2, [r5, #64]
	strd	r2, [r1, #-8]
	str	r9, [r4]
	str	r6, [r4, #4]
	str	r6, [r4, #8]
	str	r6, [r4, #12]
	ldr	r3, [r5, #40]
	str	r3, [r4, #20]
	mov	r0, r3
	str	r3, [r4, #36]
	ldr	r3, [r5, #48]
	str	r3, [r4, #24]
	str	r3, [r4, #40]
	bl	MEM_Phy2Vir
	str	r6, [r4, #508]
	str	r0, [r4, #504]
	ldr	r0, [r4, #24]
	bl	MEM_Phy2Vir
	str	r6, [r4, #516]
	ldr	lr, [r4, #20]
	mov	r1, r6
	ldr	r10, [r4, #24]
	mov	r2, #4
	ldr	ip, .L1718
	str	r0, [r4, #512]
	add	r0, r4, #64
	ldr	r3, [r5, #44]
	add	lr, r3, lr
	str	lr, [r4, #28]
	ldr	r3, [r5, #44]
	str	r6, [r4, #52]
	add	r3, r3, r10
	str	r3, [r4, #32]
	ldr	r3, [r5, #12]
	ldr	ip, [ip, #48]
	str	r3, [r4, #68]
	ldr	r3, [r5, #16]
	str	r3, [r4, #72]
	ldr	r3, [r5, #12]
	mov	lr, r3, lsr r9
	str	r3, [r4, #76]
	ldr	r3, [r5, #16]
	str	lr, [r4, #84]
	str	r3, [r4, #80]
	mov	r3, r3, lsr r9
	str	r3, [r4, #88]
	ldr	r3, [r5, #44]
	str	r6, [r4, #108]
	str	r6, [r4, #152]
	str	r3, [r4, #112]
	mov	r3, r3, lsr r9
	str	r9, [r4, #164]
	str	r3, [r4, #116]
	blx	ip
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	ldrb	r2, [r4, #64]	@ zero_extendqisi2
	and	r3, r3, #252
	orr	r3, r3, #12
	and	r2, r2, #224
	bfi	r3, r9, #4, #2
	bfi	r2, r9, #5, #3
	strb	r3, [r4, #65]
	strb	r2, [r4, #64]
	ldr	r0, [r5, #24]
	str	r0, [r4, #212]
	bl	MEM_Phy2Vir
	str	r6, [r4, #524]
	str	r0, [r4, #520]
	ldr	r1, [r5]
	ldr	r0, [r5, #8]
	bl	Get_YuvFormat
	cmp	r0, #13
	beq	.L1717
	str	r0, [r4, #388]
	mov	r2, r9
	ldr	r3, [r5, #56]
	mov	r9, #20
	mov	r1, r7
	mov	r0, r8
	str	r3, [r4, #364]
	ldr	r3, [r5, #60]
	str	r3, [r4, #360]
	ldr	r3, [r5, #52]
	str	r9, [r4, #296]
	str	r3, [r4, #368]
	bl	FSP_SetDisplay
	ldr	r3, .L1718+4
	str	r4, [sp]
	mov	r1, r9
	mov	r0, r8
	ldr	r2, [r3, r8, asl #2]
	add	r2, r2, #475136
	add	r3, r2, #1016
	add	r2, r2, #1008
	bl	InsertImgToVoQueue
	cmp	r0, #1
	moveq	r0, r6
	beq	.L1708
	add	r9, r4, #544
	ldr	r1, [r4, #544]
	mov	r0, r8
	add	r5, r4, #560
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	mov	r0, r8
	strd	r2, [r9]
	ldr	r1, [r4, #552]
	strd	r2, [fp, #-52]
	bl	FreeUsdByDec
	ldrd	r2, [fp, #-52]
	mov	r0, r8
	mov	r1, r7
	strd	r2, [r5, #-8]
	mov	r2, r6
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L1708
.L1715:
	ldr	r3, [r5, #4]
	cmp	r3, #1
	bne	.L1710
	ldr	r2, [r5, #48]
	ldr	r1, .L1718+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1708
.L1714:
	ldr	r2, [r5, #40]
	mov	r0, #0
	ldr	r1, .L1718+12
	bl	dprint_vfmw
	mov	r0, r7
	b	.L1708
.L1717:
	mov	r2, r0
	ldr	r1, .L1718+16
	mov	r0, r9
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1708
.L1716:
	movw	r2, #5249
	ldr	r1, .L1718+20
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1708
.L1719:
	.align	2
.L1718:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC187
	.word	.LC186
	.word	.LC189
	.word	.LC188
	UNWIND(.fnend)
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
	.align	2
	.global	VCTRL_PutUsrdecFrame
	.type	VCTRL_PutUsrdecFrame, %function
VCTRL_PutUsrdecFrame:
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
	ldr	r5, .L1731
	mov	r4, r0
	mov	r0, r1
	ldr	r3, [r5, r4, asl #2]
	cmp	r3, #0
	beq	.L1728
	cmp	r1, #0
	beq	.L1729
	ldr	r2, [r3, #536]
	cmp	r2, #20
	bne	.L1730
	ldr	ip, .L1731+4
	add	r0, r3, #464
	mov	r2, #72
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	mov	r0, r4
	add	r1, r1, #464
	bl	VDH_PutUsrdecFrame
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1731+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1730:
	ldr	r1, .L1731+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1729:
	ldr	r3, .L1731+16
	movw	r2, #5402
	ldr	r1, .L1731+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1728:
	mov	r0, r3
	movw	r2, #5401
	ldr	r3, .L1731+24
	ldr	r1, .L1731+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1732:
	.align	2
.L1731:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC192
	.word	.LC191
	.word	.LC190
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	2
	.global	VCTRL_ResetHardware
	.type	VCTRL_ResetHardware, %function
VCTRL_ResetHardware:
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
	bl	SCDDRV_ResetSCD
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VDMDRV_ResetVDH
	UNWIND(.fnend)
	.size	VCTRL_ResetHardware, .-VCTRL_ResetHardware
	.align	2
	.global	VCTRL_CanBeDecodedByHardWare
	.type	VCTRL_CanBeDecodedByHardWare, %function
VCTRL_CanBeDecodedByHardWare:
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
	cmp	r0, #4
	cmpne	r0, #7
	beq	.L1735
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_CanBeDecodedByHardWare.part.20
.L1735:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_CanBeDecodedByHardWare, .-VCTRL_CanBeDecodedByHardWare
	.align	2
	.global	VCTRL_IsChanOpenAndRun
	.type	VCTRL_IsChanOpenAndRun, %function
VCTRL_IsChanOpenAndRun:
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
	ldr	r3, [r0, #4]
	cmp	r3, #1
	ldreq	r0, [r0, #8]
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_IsChanOpenAndRun, .-VCTRL_IsChanOpenAndRun
	.align	2
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
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
	mov	r6, r0
	movwhi	r2, #8769
	ldrhi	r1, .L1785
	bhi	.L1775
	ldr	r5, .L1785+4
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1776
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L1742
	ldr	r0, [r0, #536]
	cmp	r0, #21
	beq	.L1742
	cmp	r0, #4
	cmpne	r0, #7
	moveq	r7, #1
	movne	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r4, r7
.L1748:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L1747
	ldr	r3, [r5, r4, asl #2]
	ldr	r0, [r3, #536]
	cmp	r0, #4
	cmpne	r0, #7
	beq	.L1747
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	cmp	r0, #0
	addne	r7, r7, #1
.L1747:
	add	r4, r4, #1
	cmp	r4, #32
	bne	.L1748
	cmp	r7, #1
	beq	.L1777
.L1749:
	ldr	r3, .L1785+8
	mov	r1, #0
	add	r0, r3, #128
.L1756:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1755
	ldr	r2, [r2, #536]
	cmp	r2, #6
	moveq	r1, #1
.L1755:
	cmp	r3, r0
	bne	.L1756
	cmp	r1, #1
	beq	.L1778
.L1757:
	ldr	r3, [r5, r6, asl #2]
	ldr	r3, [r3, #536]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, .L1785+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1779
	ldr	r3, .L1785+16
	ldr	r3, [r3, #28]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1742:
	ldr	r1, .L1785+20
	movw	r2, #8781
.L1775:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1777:
	ldr	r4, .L1785+12
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1780
	mov	r0, r7
	mov	r1, #0
	bl	VDH_Need_Module
.L1752:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1753
	ldr	r3, .L1785+16
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L1781
	mov	r0, #0
	blx	r3
	b	.L1749
.L1778:
	ldr	r3, .L1785+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1782
	mov	r1, #0
	mov	r0, #3
	bl	VDH_Need_Module
	b	.L1757
.L1782:
	ldr	r3, .L1785+16
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L1783
	mov	r0, #0
	blx	r3
	b	.L1757
.L1780:
	ldr	r3, .L1785+16
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1784
	mov	r0, #0
	blx	r3
	b	.L1752
.L1776:
	movw	r2, #8775
	ldr	r1, .L1785+24
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1779:
	mov	r1, #0
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Need_Module
.L1753:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Need_Module
	b	.L1749
.L1781:
	mov	r0, r3
	movw	r2, #8830
	ldr	r1, .L1785+28
	bl	dprint_vfmw
	b	.L1749
.L1783:
	mov	r0, r3
	movw	r2, #8861
	ldr	r1, .L1785+28
	bl	dprint_vfmw
	b	.L1757
.L1784:
	mov	r0, r3
	movw	r2, #8816
	ldr	r1, .L1785+28
	bl	dprint_vfmw
	b	.L1752
.L1786:
	.align	2
.L1785:
	.word	.LC193
	.word	.LANCHOR0
	.word	.LANCHOR0-4
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC195
	.word	.LC194
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	2
	.global	VCTRL_StartChan
	.type	VCTRL_StartChan, %function
VCTRL_StartChan:
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
	mov	r5, r0
	bhi	.L1798
	ldr	r4, .L1802
	ldr	r3, [r4, r0, asl #2]
	cmp	r3, #0
	beq	.L1799
	ldr	r6, [r3, #4]
	cmp	r6, #1
	bne	.L1800
	ldr	r3, [r3, #536]
	cmp	r3, #21
	beq	.L1801
	bl	SM_Start
	ldr	r3, [r4, r5, asl #2]
	mov	r2, #0
	str	r6, [r3, #8]
	ldr	r3, [r4, r5, asl #2]
	str	r6, [r3, #12]
	ldr	r3, [r4, r5, asl #2]
	str	r2, [r3, #24]
	ldr	r3, [r4, r5, asl #2]
	str	r6, [r3, #16]
	ldr	r2, [r4, r5, asl #2]
	ldr	r3, [r2, #20]
	cmp	r3, #0
	bne	.L1793
	ldr	r3, .L1802+4
	sub	ip, r4, #4
	ldr	r1, .L1802+8
	add	r4, r3, #128
	str	r6, [r2, #20]
.L1796:
	ldr	r2, [ip, #4]!
	add	r3, r3, #4
	add	r1, r1, #4
	cmp	r2, #0
	streq	r2, [r3, #-4]
	ldrne	lr, [r2, #20]
	strne	lr, [r3, #-4]
	ldrne	r2, [r2, #20]
	cmp	r3, r4
	str	r2, [r1, #-4]
	bne	.L1796
	ldr	r0, .L1802+4
	bl	VDMDRV_SetPriority
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
.L1793:
	ldr	r4, .L1802+12
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	bl	VCTRL_OpenHardware
	mov	r2, #12
	ldr	r3, [r4, #48]
	mov	r1, #0
	ldr	r0, .L1802+16
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #720
	mov	r1, #0
	ldr	r0, .L1802+20
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #2
	mov	r1, #0
	ldr	r0, .L1802+24
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #120
	mov	r1, #0
	ldr	r0, .L1802+28
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1800:
	ldr	r3, .L1802+32
	movw	r2, #2509
	ldr	r1, .L1802+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1798:
	ldr	r3, .L1802+40
	movw	r2, #2507
	ldr	r1, .L1802+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1801:
	ldr	r3, .L1802+44
	movw	r2, #2510
	ldr	r1, .L1802+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1799:
	mov	r0, r3
	movw	r2, #2508
	ldr	r3, .L1802+48
	ldr	r1, .L1802+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1803:
	.align	2
.L1802:
	.word	.LANCHOR0
	.word	.LANCHOR4+1288
	.word	g_ChanCtx
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_TimeRecId
	.word	g_TimeRecTable
	.word	g_DataRecId
	.word	g_DataTable
	.word	.LC123
	.word	.LC1
	.word	.LC71
	.word	.LC196
	.word	.LC78
	UNWIND(.fnend)
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	2
	.type	VfmwProc_TestStartChan, %function
VfmwProc_TestStartChan:
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
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StartChan
	mov	r2, r4
	ldr	r1, .L1805
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1806:
	.align	2
.L1805:
	.word	.LC197
	UNWIND(.fnend)
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	2
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
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
	ldr	r5, .L1868
	mov	r8, #0
	mov	r10, r0
	mov	r7, r8
	add	r9, r5, #128
	mov	r1, r8
	b	.L1817
.L1858:
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1856
.L1813:
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1808
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1837
.L1808:
	cmp	r5, r9
	beq	.L1857
.L1817:
	ldr	r4, [r5, #4]!
	cmp	r4, #0
	beq	.L1808
	cmp	r1, #0
	ldr	r6, [r4, #536]
	beq	.L1858
	cmp	r7, #0
	cmpeq	r6, #1
	bne	.L1813
	ldr	r3, [r4, #4]
	cmp	r3, #1
	bne	.L1808
.L1836:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	moveq	r7, #1
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1808
.L1837:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	moveq	r8, #1
	cmp	r5, r9
	bne	.L1817
.L1857:
	cmp	r1, #0
	beq	.L1859
.L1818:
	cmp	r8, #0
	bne	.L1830
	ldr	r3, .L1868+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1860
	mov	r1, r8
	mov	r0, #3
	bl	VDH_UnNeed_Module
.L1830:
	cmp	r7, #0
	bne	.L1807
.L1865:
	ldr	r3, .L1868+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1861
	ldr	r3, .L1868+8
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L1807
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1856:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L1862
.L1812:
	cmp	r7, #0
	cmpeq	r6, #1
	beq	.L1836
	b	.L1813
.L1862:
	cmp	r6, #7
	cmpne	r6, #4
	beq	.L1812
	mov	r0, r6
	bl	VCTRL_CanBeDecodedByHardWare.part.20
	adds	r1, r0, #0
	movne	r1, #1
	b	.L1812
.L1859:
	ldr	r4, .L1868+4
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1823
	mov	r0, r10
	str	r1, [fp, #-48]
	bl	SCDDRV_ResetSCD
	mov	r0, r10
	bl	VDMDRV_ResetVDH
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [fp, #-48]
	cmp	r3, #1
	beq	.L1823
	mov	r0, #1
	bl	VDH_UnNeed_Module
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1826
.L1867:
	ldr	r3, .L1868+8
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L1863
	mov	r0, #0
	blx	r3
.L1829:
	mov	r0, #0
	bl	SCDDRV_SetStateIdle
	b	.L1818
.L1860:
	ldr	r3, .L1868+8
	mov	r0, r8
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L1864
	blx	r3
	cmp	r7, #0
	beq	.L1865
.L1807:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1861:
	mov	r1, r7
	mov	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_UnNeed_Module
.L1823:
	ldr	r3, .L1868+8
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L1866
	mov	r0, #0
	blx	r3
.L1825:
	mov	r0, #0
	bl	VDMDRV_SetStateIdle
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1867
.L1826:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_UnNeed_Module
	b	.L1818
.L1863:
	mov	r0, r3
	movw	r2, #8959
	ldr	r1, .L1868+12
	bl	dprint_vfmw
	b	.L1829
.L1864:
	movw	r2, #8977
	ldr	r1, .L1868+12
	bl	dprint_vfmw
	b	.L1830
.L1866:
	mov	r0, r3
	movw	r2, #8944
	ldr	r1, .L1868+12
	bl	dprint_vfmw
	b	.L1825
.L1869:
	.align	2
.L1868:
	.word	.LANCHOR0-4
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	2
	.global	VCTRL_StopChan
	.type	VCTRL_StopChan, %function
VCTRL_StopChan:
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
	mov	r4, r0
	bhi	.L1876
	ldr	r6, .L1878
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1877
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L1875
	str	r2, [r3, #24]
	mov	r3, #0
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #12]
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #8]
	bl	SM_Stop
	subs	r5, r0, #0
	bne	.L1875
	mov	r1, r5
	mov	r0, r4
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r5, [r3, #24]
	bl	VCTRL_CloseHardware
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1875:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1876:
	ldr	r3, .L1878+4
	movw	r2, #2601
	ldr	r1, .L1878+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1877:
	mov	r0, r3
	movw	r2, #2602
	ldr	r3, .L1878+12
	ldr	r1, .L1878+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1879:
	.align	2
.L1878:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC1
	.word	.LC198
	UNWIND(.fnend)
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	2
	.global	VCTRL_StopChanWithCheck
	.type	VCTRL_StopChanWithCheck, %function
VCTRL_StopChanWithCheck:
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
	ldr	r5, .L1887
	mov	r7, r0
	mov	r4, #0
	mov	r8, r5
	b	.L1882
.L1886:
	add	r4, r4, #1
	ldr	r3, [r8, #120]
	blx	r3
	cmp	r4, #50
	beq	.L1884
.L1882:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r7
	bl	VCTRL_StopChan
	ldr	r3, [r5, #16]
	mov	r6, r0
	mov	r0, #0
	blx	r3
	cmp	r6, #0
	mov	r0, #10
	bne	.L1886
	cmp	r4, #49
	bgt	.L1884
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1884:
	ldr	r1, .L1887+4
	mvn	r6, #0
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1888:
	.align	2
.L1887:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC199
	UNWIND(.fnend)
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
	.align	2
	.global	VCTRL_ResetChanWithOption
	.type	VCTRL_ResetChanWithOption, %function
VCTRL_ResetChanWithOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r5, .L1922
	mov	r4, r0
	mov	r6, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L1916
	ldr	r2, [r1]
	cmp	r2, #1
	bhi	.L1917
	ldr	r9, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r7, .L1922+4
	mov	r8, #0
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #300
	ldr	r0, .L1922+8
	mov	r1, r8
	ldr	ip, [r7, #48]
	str	r8, [r3, #384]
	str	r8, [r3, #388]
	mla	r0, r2, r4, r0
	blx	ip
	ldr	r3, [r5, r4, asl #2]
	cmp	r3, r8
	addne	r3, r3, #471040
	strne	r8, [r3, #916]
	beq	.L1918
.L1894:
	ldr	r3, [r7, #12]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	VCTRL_FindOccupiedFrame
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
	ldr	r2, [r6, #4]
	ldr	r3, [r5, r4, asl #2]
	mov	r0, r4
	str	r2, [r3, #1160]
	bl	InitSyntaxCtx
	ldr	r3, [r5, r4, asl #2]
	add	r1, r3, #475136
	ldr	r0, [r3, #536]
	add	r1, r1, #1008
	bl	ReleaseCurPic
	ldr	r0, [r5, r4, asl #2]
	ldr	r3, [r7, #48]
	mov	r2, #416
	mov	r1, #0
	add	r0, r0, #680
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	mvn	r0, #0
	mvn	r1, #0
	add	r2, r3, #608
	mov	ip, #0
	strd	r0, [r2, #-8]
	strd	r0, [r2]
	mov	r0, r4
	ldr	r2, [r3, #1384]
	str	ip, [r3, #1096]
	cmp	r2, #1
	streq	ip, [r3, #1432]
	addeq	r2, r3, #475136
	streq	ip, [r2, #940]
	ldr	r3, [r3, #536]
	cmp	r3, #20
	beq	.L1896
	ldr	r3, [r6, #8]
	cmp	r3, #0
	beq	.L1919
.L1896:
	bl	FSP_EmptyInstance
.L1897:
	mov	r0, r4
	bl	InitUsdPool
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L1920
.L1898:
	ldr	r2, [r5, #1056]
	ldr	r3, .L1922
	cmp	r2, #0
	beq	.L1899
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-40]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1901
	mov	r0, #512
	sub	r1, fp, #40
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1901
	sub	r1, fp, #40
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1901:
	ldr	r1, .L1922+12
	mov	r0, #32
	bl	dprint_vfmw
.L1899:
	cmp	r9, #0
	bne	.L1921
.L1903:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1891:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1920:
	mov	r0, r4
	bl	SM_Reset
	b	.L1898
.L1921:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1903
.L1919:
	bl	FSP_ResetInstance
	b	.L1897
.L1917:
	movw	r2, #3362
	ldr	r1, .L1922+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1918:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1894
.L1916:
	mov	r0, r3
	movw	r2, #3358
	ldr	r3, .L1922+20
	ldr	r1, .L1922+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1891
.L1923:
	.align	2
.L1922:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-128
	.word	.LC201
	.word	.LC200
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	2
	.global	VCTRL_ResetChan
	.type	VCTRL_ResetChan, %function
VCTRL_ResetChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r5, .L1951
	mov	r4, r0
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L1947
	ldr	r8, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r7, .L1951+4
	mov	r6, #0
	ldr	r3, [r5, r4, asl #2]
	mov	r0, #4
	ldr	r2, [r7, #12]
	str	r6, [r3, #384]
	str	r6, [r3, #388]
	blx	r2
	ldr	r3, [r5, r4, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L1948
.L1927:
	ldr	r0, .L1951+8
	mov	r2, #300
	ldr	r3, [r7, #48]
	mov	r1, #0
	mla	r0, r2, r4, r0
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	cmp	r3, #0
	addne	r3, r3, #471040
	movne	r2, #0
	strne	r2, [r3, #916]
	beq	.L1949
.L1929:
	ldr	r3, [r5, r4, asl #2]
	mov	r6, #0
	mov	r0, r4
	str	r6, [r3, #1160]
	bl	InitSyntaxCtx
	ldr	r0, [r5, r4, asl #2]
	mov	r1, r6
	ldr	r3, [r7, #48]
	mov	r2, #416
	add	r0, r0, #680
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	mvn	r3, #0
	mvn	r2, #0
	add	r0, r1, #475136
	add	ip, r1, #608
	strd	r2, [ip, #-8]
	strd	r2, [ip]
	str	r6, [r1, #1096]
	str	r6, [r0, #968]
	str	r6, [r0, #960]
	str	r6, [r0, #964]
	ldr	r3, [r1, #1384]
	cmp	r3, #1
	streq	r6, [r1, #1432]
	streq	r6, [r0, #940]
	mov	r0, r4
	ldr	r3, [r1, #536]
	cmp	r3, #20
	beq	.L1931
	bl	FSP_ResetInstance
.L1932:
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	InitUsdPool
	mov	r0, r4
	bl	SM_Reset
	ldr	r2, [r5, #1056]
	ldr	r3, .L1951
	cmp	r2, #0
	beq	.L1933
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-40]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1935
	mov	r0, #512
	sub	r1, fp, #40
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1935
	sub	r1, fp, #40
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1935:
	ldr	r1, .L1951+12
	mov	r0, #32
	bl	dprint_vfmw
.L1933:
	cmp	r8, #0
	bne	.L1950
.L1937:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1926:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1950:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1937
.L1931:
	bl	FSP_EmptyInstance
	b	.L1932
.L1948:
	add	r2, r3, #475136
	ldr	r1, [r3, #536]
	ldr	r2, [r2, #1000]
	cmp	r2, r1
	bne	.L1927
	str	r6, [r3, #12]
	mov	r0, r4
	bl	VCTRL_FindOccupiedFrame
	b	.L1927
.L1949:
	bl	VCTRL_SetSendStreamAgainFlag.part.11
	b	.L1929
.L1947:
	mov	r0, r3
	movw	r2, #3758
	ldr	r3, .L1951+16
	ldr	r1, .L1951+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1926
.L1952:
	.align	2
.L1951:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-128
	.word	.LC201
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	2
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
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
	UNWIND(.pad #204)
	sub	sp, sp, #204
	ldr	r6, .L2042
	mov	r7, r1
	mov	r9, r0
	mov	r1, #0
	mov	r4, r2
	ldr	r3, [r6, #48]
	mov	r2, #36
	sub	r0, fp, #176
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #96
	mov	r1, #0
	sub	r0, fp, #140
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #216
	blx	r3
	ldr	ip, [r6, #48]
	sub	r0, fp, #228
	mov	r2, #12
	mov	r1, #0
	blx	ip
	ldr	r3, .L2042+4
	cmp	r7, #0
	str	r7, [r3, #1416]
	beq	.L2025
	ldr	r1, [r7, #36]
	cmp	r1, #0
	blt	.L1956
	ldr	r3, [r7, #12]
	cmp	r3, #31
	ble	.L1956
	ldr	r3, [r7, #16]
	cmp	r3, #31
	ble	.L1956
	ldr	r3, [r7, #56]
	cmp	r3, #262144
	blt	.L1956
	ldr	r1, [r7, #44]
	cmp	r1, #1
	beq	.L2026
	cmp	r1, #2
	bne	.L1958
	ldr	r3, [r7, #20]
	cmp	r3, #0
	ble	.L1956
	ldr	r3, [r7, #24]
	cmp	r3, #0
	ble	.L1956
.L2022:
	ldr	r3, [r7, #28]
	cmp	r3, #0
	ble	.L1956
	ldr	r3, [r7, #32]
	cmp	r3, #0
	bgt	.L1958
.L1956:
	ldr	r1, .L2042+8
	mov	r0, #0
	bl	dprint_vfmw
.L1996:
	mvn	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1958:
	ldr	r3, [r7, #168]
	movw	ip, #13616
	movt	ip, 15
	sub	r2, fp, #228
	cmp	r3, #1
	movw	lr, #45800
	mov	r1, r7
	mov	r0, r9
	movhi	r3, #0
	strhi	r3, [r7, #168]
	cmp	r9, #26
	mov	r3, r4
	mov	r4, #1
	str	r4, [r7, #192]
	str	r4, [r7, #196]
	movt	lr, 180
	movne	lr, ip
	str	lr, [fp, #-232]
	bl	VCTRL_GetChanMemSize
	subs	r10, r0, #0
	bne	.L2027
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, r10
	sub	r0, fp, #200
	blx	r3
	ldrd	r2, [r7, #128]
	ldr	r5, .L2042
	orrs	r3, r2, r3
	beq	.L1964
	ldr	r3, [r7, #136]
	cmp	r3, #0
	bne	.L1965
.L1964:
	mov	r0, #7
	mov	r3, #3
	mov	r4, #1
	str	r3, [fp, #-180]
	bl	VFMW_GetString
	ldr	r2, [fp, #-220]
	sub	r3, fp, #200
	str	r4, [sp]
	mov	r1, #0
	bl	MEM_AllocMemBlock
	subs	r5, r0, #0
	bne	.L2028
	ldr	r2, [fp, #-184]
	ldr	r1, [fp, #-196]
	ldr	r0, [fp, #-192]
	bl	MEM_AddMemRecord
	ldr	r1, [fp, #-192]
	ldr	r2, [fp, #-196]
	ldr	r3, [fp, #-184]
	str	r5, [fp, #-80]
	str	r4, [fp, #-208]
	str	r1, [fp, #-92]
	str	r2, [fp, #-84]
	str	r3, [fp, #-76]
.L1968:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #200
	blx	r3
	ldrd	r2, [r7, #80]
	ldr	r1, .L2042
	orrs	r3, r2, r3
	bne	.L2029
.L1997:
	ldr	r3, [r7, #168]
	cmp	r3, #1
	beq	.L1971
	mov	r0, #8
	mov	r3, #3
	str	r3, [fp, #-180]
	bl	VFMW_GetString
	mov	r3, #0
	ldr	r2, [fp, #-228]
	mov	r1, r3
	str	r3, [sp]
	sub	r3, fp, #200
	bl	MEM_AllocMemBlock
	subs	r4, r0, #0
	bne	.L2030
	ldr	r2, [fp, #-184]
	ldr	r1, [fp, #-196]
	ldr	r0, [fp, #-192]
	bl	MEM_AddMemRecord
	ldr	r0, [fp, #-192]
	ldr	r1, [fp, #-196]
	mov	r3, #1
	ldr	r2, [fp, #-184]
	str	r4, [fp, #-128]
	str	r0, [fp, #-140]
	str	r1, [fp, #-132]
	str	r2, [fp, #-124]
	str	r3, [fp, #-216]
.L1975:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #200
	blx	r3
	ldrd	r2, [r7, #104]
	ldr	r1, .L2042
	orrs	r3, r2, r3
	beq	.L1999
	ldr	r3, [r7, #112]
	cmp	r3, #0
	bne	.L1979
.L1999:
	mov	r0, #9
	mov	r3, #3
	str	r3, [fp, #-180]
	bl	VFMW_GetString
	mov	r1, #0
	ldr	r2, [fp, #-224]
	sub	r3, fp, #200
	str	r1, [sp]
	bl	MEM_AllocMemBlock
	subs	r10, r0, #0
	bne	.L2031
	ldr	r2, [fp, #-184]
	ldr	r1, [fp, #-196]
	ldr	r0, [fp, #-192]
	bl	MEM_AddMemRecord
	ldr	ip, [fp, #-192]
	ldr	r0, [fp, #-196]
	mov	r2, #1
	ldr	r1, [fp, #-184]
	str	r10, [fp, #-104]
	str	ip, [fp, #-116]
	str	r0, [fp, #-108]
	str	r1, [fp, #-100]
	str	r2, [fp, #-212]
.L2019:
	ldr	r5, .L2042+12
	mov	r0, #0
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L1988
	mov	r3, r5
	mov	r4, #1
	b	.L1990
.L2032:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L1991
.L1990:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	bne	.L2032
	cmp	r4, #31
	bhi	.L1991
.L1988:
	ldr	r10, [fp, #-232]
	mov	r1, #0
	ldr	r0, [fp, #-84]
	mov	r8, r1
	sub	r2, r10, #205824
	ldr	r3, [r6, #48]
	sub	r2, r2, #520
	str	r0, [r5, r4, asl #2]
	blx	r3
	ldr	r0, [r5, r4, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #208
	mov	r1, r7
	add	r0, r0, #1216
	blx	r3
	ldr	r0, [r5, r4, asl #2]
	mov	lr, #21
	ldr	r2, .L2042+16
	mov	ip, #30
	movw	r1, #51176
	str	r9, [r0, #36]
	movt	r1, 6
	ldr	r3, [r5, r4, asl #2]
	str	r10, [r0, #1124]
	mov	r0, r4
	str	r4, [r3]
	str	r9, [r3, #572]
	str	r8, [r3, #1152]
	ldr	r3, [r5, r4, asl #2]
	ldr	r9, [r7]
	str	r9, [r3, #32]
	ldr	r3, [r5, r4, asl #2]
	add	r9, r3, #475136
	str	lr, [r3, #536]
	str	lr, [r9, #1000]
	str	r8, [r3, #28]
	ldr	r3, [r5, r4, asl #2]
	ldr	r9, [r7, #200]
	add	lr, r3, #475136
	add	r1, r3, r1
	str	r9, [lr, #984]
	add	lr, r3, #1472
	str	ip, [r3, #1464]
	str	lr, [r2, r4, asl #3]
	ldr	r2, [r7, #192]
	ldr	r9, .L2042+12
	str	r2, [r3, #1536]
	ldr	r2, [r7, #196]
	str	r2, [r3, #1540]
	bl	FSP_EnableInstance
	subs	r10, r0, #0
	bne	.L2033
	mov	r0, r4
	mov	r8, r10
	bl	VCTRL_ResetChan
	ldr	r1, [r9, r4, asl #2]
	ldr	lr, [fp, #-216]
	ldr	ip, [fp, #-212]
	add	r2, r1, #471040
	ldr	r9, [fp, #-208]
	add	r0, r1, #475136
	str	lr, [r1, #300]
	str	ip, [r1, #304]
	str	r9, [r1, #308]
	str	r10, [r2, #892]
	str	r10, [r2, #896]
	str	r10, [r2, #904]
	str	r10, [r2, #908]
	str	r10, [r2, #900]
	str	r10, [r2, #912]
	ldr	r2, [r7, #168]
	str	r10, [r0, #940]
	str	r2, [r0, #948]
.L1993:
	mov	r7, r8, asl #6
	ldr	r0, [r5, r4, asl #2]
	add	r7, r7, r8, lsl #3
	mov	r2, #72
	add	r3, r7, #471040
	mov	r1, #0
	add	r3, r3, #920
	ldr	ip, [r6, #48]
	add	r0, r0, r3
	add	r8, r8, #1
	blx	ip
	ldr	r1, [r5, r4, asl #2]
	cmp	r8, #32
	mov	r2, #255
	add	r3, r1, r7
	ldr	r9, .L2042
	add	r3, r3, #471040
	ldr	r7, .L2042+12
	str	r2, [r3, #920]
	str	r2, [r3, #924]
	str	r2, [r3, #928]
	bne	.L1993
	movw	r0, #15512
	ldr	r3, [r9, #48]
	mov	r2, #1248
	movt	r0, 7
	add	r0, r1, r0
	mov	r1, #0
	blx	r3
	ldr	r0, [r7, r4, asl #2]
	ldr	r3, [r9, #48]
	mov	r2, #24
	add	r0, r0, #475136
	mov	r1, #0
	add	r0, r0, #376
	blx	r3
	ldr	r3, [r7, r4, asl #2]
	ldr	r8, [fp, #-132]
	mov	r0, #0
	ldr	r7, [fp, #-108]
	add	ip, r3, #442368
	ldr	lr, [fp, #-92]
	ldr	r2, .L2042+4
	ldr	r1, [fp, #-124]
	add	r9, r2, r4, lsl #2
	str	r8, [r3, #232]
	ldr	r2, [fp, #-140]
	str	r7, [r3, #256]
	str	lr, [r3, #284]
	ldr	r10, [fp, #-84]
	ldr	r8, [fp, #-116]
	ldr	r7, [fp, #-100]
	ldr	lr, [fp, #-76]
	str	r10, [r3, #280]
	str	r2, [r3, #236]
	str	lr, [r3, #292]
	str	r2, [r3, #328]
	str	r1, [r3, #244]
	str	r1, [r3, #332]
	str	r8, [r3, #260]
	str	r7, [r3, #268]
	str	r0, [ip, #2056]
	ldr	ip, [r3, #1384]
	str	r0, [r9, #1420]
	cmp	ip, #1
	beq	.L1994
	sub	r1, r1, #307200
	str	r2, [r3, #316]
	sub	r1, r1, #2576
	str	r1, [r3, #320]
	add	r2, r1, r2
	str	r8, [r3, #324]
	add	r0, r2, #14848
	add	r1, r2, #47616
	add	r0, r0, #15
	add	r1, r1, #15
	add	r2, r2, #15
	str	r7, [r3, #336]
.L2023:
	bic	r2, r2, #15
	str	r2, [r3, #340]
	mov	r2, #262144
	str	r2, [r3, #360]
	ldr	r2, [r5, r4, asl #2]
	bic	r0, r0, #15
	bic	r1, r1, #15
	str	r0, [r3, #348]
	str	r1, [r3, #356]
	mov	r0, #14848
	mov	r1, #32768
	str	r0, [r3, #344]
	str	r1, [r3, #352]
	mov	r0, r4
	str	r4, [r2]
	mov	r10, r4
	ldr	r2, [r5, r4, asl #2]
	add	r1, r2, #425984
	str	r4, [r2, #220]
	str	r4, [r2, #224]
	str	r4, [r1, #1676]
	bl	SM_ClearInst
	ldr	r2, [r5, r4, asl #2]
	ldr	r3, [fp, #-232]
	mov	r0, r4
	sub	r1, r3, #203776
	ldr	r2, [r2, #280]
	sub	r1, r1, #520
	add	r1, r2, r1
	bl	OpenUsdPool_WithMem
	ldr	r2, [r5, r4, asl #2]
	mov	r1, #1
	mov	r0, r4
	str	r1, [r2, #4]
	bl	VDMDRV_ClearChanIsDec
	bl	VDMDRV_ParamInit
	ldr	r2, [r6]
	ldr	r4, [r5, r4, asl #2]
	blx	r2
	ldr	r2, [r6, #16]
	add	r4, r4, #475136
	str	r0, [r4, #956]
	mov	r0, #0
	blx	r2
.L2018:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2029:
	ldr	r3, [r7, #88]
	cmp	r3, #0
	beq	.L1997
	ldr	r3, [r1, #52]
	mov	r2, #24
	sub	r0, fp, #140
	add	r1, r7, #72
	blx	r3
	ldr	r3, [r7, #168]
	ldr	r2, [fp, #-124]
	cmp	r3, #1
	beq	.L1977
	ldr	r3, [fp, #-228]
	cmp	r2, r3
	blt	.L2034
.L1977:
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-140]
	bl	MEM_AddMemRecord
	b	.L1975
.L1971:
	mov	r3, #0
	mov	r0, #0
	mov	r1, #0
	str	r3, [fp, #-140]
	str	r3, [fp, #-124]
	str	r3, [fp, #-216]
	strd	r0, [fp, #-132]
	b	.L1975
.L2026:
	ldr	r3, [r7, #20]
	cmp	r3, #0
	bgt	.L2022
	b	.L1956
.L1994:
	sub	r7, r7, #307200
	str	r0, [r3, #316]
	sub	r7, r7, #2576
	str	r0, [r3, #320]
	add	r2, r7, r8
	str	r7, [r3, #336]
	add	r0, r2, #14848
	add	r1, r2, #47616
	add	r0, r0, #15
	add	r1, r1, #15
	add	r2, r2, #15
	str	r8, [r3, #324]
	b	.L2023
.L1965:
	ldr	r3, [r5, #52]
	mov	r2, #24
	add	r1, r7, #120
	sub	r0, fp, #92
	blx	r3
	ldr	r2, [fp, #-76]
	ldr	r3, [fp, #-220]
	cmp	r2, r3
	blt	.L2035
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_AddMemRecord
	b	.L1968
.L1979:
	ldr	r3, [r1, #52]
	mov	r2, #24
	add	r1, r7, #96
	sub	r0, fp, #116
	blx	r3
	ldrd	r0, [fp, #-108]
	orrs	r3, r0, r1
	beq	.L1984
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-224]
	cmp	r2, r3
	blt	.L1984
	mov	r1, r0
	ldr	r0, [fp, #-116]
	bl	MEM_AddMemRecord
	b	.L2019
.L2031:
	ldr	r3, [fp, #-208]
	cmp	r3, #1
	beq	.L2036
.L1981:
	ldr	r3, [fp, #-216]
	cmp	r3, #1
	beq	.L2037
.L1982:
	movw	r2, #1909
	ldr	r1, .L2042+20
	mov	r0, #1
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L2018
.L2030:
	ldr	r3, [fp, #-208]
	cmp	r3, #1
	beq	.L2038
.L1973:
	movw	r2, #1975
	ldr	r1, .L2042+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1996
.L2027:
	movw	r2, #2132
	ldr	r1, .L2042+28
	mov	r0, #0
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L2018
.L1991:
	mov	r2, #32
	ldr	r1, .L2042+32
	mov	r0, #1
	mvn	r10, #0
	bl	dprint_vfmw
	ldr	r2, [r6, #16]
	mov	r0, #0
	blx	r2
	b	.L2018
.L2033:
	mov	r2, r4
	ldr	r1, .L2042+36
	mov	r0, #1
	mvn	r10, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r2, [r9, r4, asl #2]
	str	r8, [r9, r4, asl #2]
	mov	r0, r4
	add	ip, r2, #475136
	add	r1, r2, #471040
	ldr	r7, [r2, #308]
	add	lr, r2, #228
	ldr	r6, [r2, #300]
	add	r1, r1, #920
	ldr	r5, [r2, #304]
	ldr	r9, [ip, #948]
	add	ip, r2, #252
	str	r1, [fp, #-164]
	add	r2, r2, #276
	str	lr, [fp, #-176]
	str	ip, [fp, #-172]
	str	r2, [fp, #-168]
	str	r9, [fp, #-160]
	str	r7, [fp, #-148]
	str	r6, [fp, #-156]
	str	r5, [fp, #-152]
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, .L2042
	mov	r0, r8
	ldr	r2, [r3, #16]
	blx	r2
	sub	r1, fp, #176
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	b	.L2018
.L2028:
	mov	r0, r4
	movw	r2, #2033
	ldr	r1, .L2042+40
	bl	dprint_vfmw
	b	.L1996
.L1984:
	ldr	r3, [fp, #-208]
	cmp	r3, #1
	beq	.L2039
.L1986:
	ldr	r3, [fp, #-216]
	cmp	r3, #1
	beq	.L2040
.L1987:
	movw	r2, #1938
	ldr	r1, .L2042+44
	mov	r0, #1
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L2018
.L2037:
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-140]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-124]
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-140]
	bl	MEM_DelMemRecord
	b	.L1982
.L2036:
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_DelMemRecord
	b	.L1981
.L2038:
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_DelMemRecord
	b	.L1973
.L2035:
	mov	r0, r4
	movw	r2, #2049
	ldr	r1, .L2042+48
	bl	dprint_vfmw
	b	.L1996
.L2034:
	ldr	r1, [fp, #-208]
	cmp	r1, #1
	beq	.L2041
.L1978:
	str	r3, [sp]
	mov	r0, #1
	mov	r3, r2
	ldr	r1, .L2042+52
	movw	r2, #2007
	bl	dprint_vfmw
	b	.L1996
.L2040:
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-140]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-124]
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-140]
	bl	MEM_DelMemRecord
	b	.L1987
.L2025:
	mov	r0, r7
	ldr	r1, .L2042+56
	bl	dprint_vfmw
	b	.L1996
.L2039:
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_DelMemRecord
	b	.L1986
.L2041:
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-84]
	ldr	r0, [fp, #-92]
	bl	MEM_DelMemRecord
	ldr	r2, [fp, #-124]
	ldr	r3, [fp, #-228]
	b	.L1978
.L2043:
	.align	2
.L2042:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR4
	.word	.LC133
	.word	.LANCHOR0
	.word	s_SmIIS
	.word	.LC208
	.word	.LC206
	.word	.LC203
	.word	.LC210
	.word	.LC211
	.word	.LC204
	.word	.LC209
	.word	.LC205
	.word	.LC207
	.word	.LC202
	UNWIND(.fnend)
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	2
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
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
	cmp	r0, #31
	mov	r5, r0
	mov	r9, r1
	bhi	.L2090
	ldr	r6, .L2100
	ldr	r2, [r6, r0, asl #2]
	cmp	r2, #0
	beq	.L2091
	ldr	r2, [r2, #4]
	cmp	r2, #1
	bne	.L2092
	bl	VCTRL_CheckChanWH
	subs	r7, r0, #0
	bne	.L2093
	ldr	r4, .L2100+4
	ldr	r1, .L2100+8
	bl	PDT_GetAttribute
	ldr	r2, [r9, #8]
	ldr	r1, [r4, #1568]
	cmp	r1, #20
	bhi	.L2051
	cmp	r1, r2
	beq	.L2052
	ldr	ip, .L2100+12
	add	r1, r4, #1568
.L2054:
	ldr	r3, [r1, #4]!
	cmp	r3, #20
	bhi	.L2051
	cmp	r3, r2
	beq	.L2052
	cmp	r1, ip
	bne	.L2054
.L2052:
	cmp	r2, #8
	mov	r1, #0
	str	r1, [fp, #-112]
	beq	.L2094
.L2055:
	cmp	r2, #9
	beq	.L2095
.L2076:
	mov	r1, r9
	mov	r0, r5
	bl	VCTRL_CmpConfigParameter
	subs	r2, r0, #0
	beq	.L2096
	ldr	r8, .L2100+16
	mov	r2, #140
	ldr	r0, [r6, r5, asl #2]
	mov	r1, r9
	ldr	ip, [r8, #52]
	add	r0, r0, #44
	blx	ip
	ldr	lr, [r9, #24]
	ldr	ip, [r6, r5, asl #2]
	mov	r1, #0
	mov	r2, #68
	sub	r0, fp, #112
	str	lr, [ip, #20]
	ldr	ip, [r6, r5, asl #2]
	ldr	lr, [r9, #8]
	ldr	r4, [r8, #48]
	str	lr, [ip, #536]
	ldr	lr, [r9, #96]
	str	lr, [ip, #1392]
	blx	r4
	ldr	r2, [r6, r5, asl #2]
	ldr	r2, [r2, #324]
	mov	r0, r2
	str	r2, [fp, #-100]
	bl	MEM_Phy2Vir
	ldr	r2, [r6, r5, asl #2]
	ldr	ip, [r9, #84]
	mov	r1, #49152
	ldr	lr, [r9, #8]
	movt	r1, 63683
	cmp	ip, #1
	ldr	r4, [r9, #24]
	str	r0, [fp, #-112]
	ldr	r0, [r2, #336]
	addeq	r2, r2, #475136
	str	r1, [fp, #-92]
	addne	r2, r2, #475136
	ldreq	r1, [r9, #132]
	movne	r1, #0
	str	r0, [fp, #-96]
	str	lr, [fp, #-104]
	ldreq	r0, [r9, #92]
	ldreq	lr, [r9, #88]
	streq	ip, [fp, #-64]
	streq	r0, [fp, #-56]
	streq	lr, [fp, #-60]
	strb	r4, [fp, #-108]
	str	r1, [r2, #996]
	mov	r2, #0
	ldr	r1, [r9, #8]
	ldr	r0, [r9, #80]
	cmp	r1, r2
	str	r2, [fp, #-76]
	str	r0, [fp, #-68]
	bne	.L2097
.L2089:
	ldr	r2, [r9, #52]
.L2062:
	ldr	r4, .L2100+20
	mov	r0, #0
	str	r2, [fp, #-72]
	add	r10, r4, #128
	mov	r2, r4
.L2064:
	ldr	r3, [r2, #4]!
	cmp	r3, #0
	addne	r0, r0, #1
	cmp	r2, r10
	bne	.L2064
	cmp	r0, #1
	ldr	r3, .L2100+24
	ble	.L2098
.L2065:
	mov	r2, #0
	str	r2, [fp, #-72]
.L2066:
	ldr	r2, [r6, r5, asl #2]
	sub	r0, fp, #88
	str	r3, [fp, #-124]
	add	r3, r9, #12
	ldr	ip, [r8, #52]
	ldrsb	r2, [r2, #44]
	mov	r1, r3
	str	r3, [fp, #-120]
	cmp	r2, #1
	moveq	r2, #0
	streq	r2, [fp, #-72]
	mov	r2, #12
	blx	ip
	sub	r1, fp, #112
	mov	r0, r5
	bl	SM_Config
	mov	r2, #1
	sub	r0, fp, #116
	ldr	ip, [r8, #48]
	mov	r1, #0
	blx	ip
	ldr	r2, [r9, #84]
	ldr	r3, [fp, #-124]
	cmp	r2, #1
	beq	.L2099
.L2068:
	ldr	r2, [r6, r5, asl #2]
	ldr	r1, [r3, #72]
	ldr	r3, [r2, #320]
	cmp	r1, #7
	ldr	ip, [r2, #284]
	ldr	lr, [r2, #292]
	str	r3, [r2, #564]
	ldr	r3, [r2, #356]
	ldr	r0, [r2, #316]
	str	ip, [r2, #1128]
	str	r3, [fp, #-124]
	ldr	r3, [r2, #340]
	str	lr, [r2, #1132]
	str	r0, [r2, #560]
	str	r3, [r2, #576]
	ldr	r3, [fp, #-124]
	ldr	ip, [r2, #344]
	ldr	lr, [r2, #348]
	str	r3, [r2, #592]
	ldr	r0, [r2, #352]
	ldr	r3, [r2, #360]
	str	ip, [r2, #580]
	mov	ip, #0
	str	lr, [r2, #584]
	str	r3, [r2, #596]
	add	r3, r2, #475136
	str	r0, [r2, #588]
	ldr	r0, [r9, #28]
	str	r0, [r2, #548]
	ldr	r0, [r9, #28]
	str	r0, [r2, #544]
	ldr	r0, [r9, #36]
	str	r0, [r2, #552]
	ldreq	r1, [r9, #40]
	str	r1, [r2, #568]
	mov	r1, r9
	ldr	r0, [r9, #44]
	str	r0, [r2, #556]
	mov	r0, r5
	ldr	lr, [r9, #128]
	str	lr, [r2, #1180]
	ldr	lr, [r9, #136]
	str	lr, [fp, #-124]
	mov	lr, #1
	str	lr, [r2, #1184]
	str	lr, [r2, #1188]
	ldr	lr, [fp, #-124]
	str	lr, [r2, #1460]
	ldr	lr, [r9, #72]
	sub	lr, lr, #1
	clz	lr, lr
	mov	lr, lr, lsr #5
	str	lr, [r2, #1164]
	ldr	lr, [r9, #76]
	str	lr, [r2, #1168]
	ldr	lr, [r9, #48]
	str	lr, [r2, #1172]
	ldr	lr, [fp, #-72]
	str	ip, [r2, #1432]
	str	ip, [r2, #1452]
	str	lr, [r2, #1176]
	ldrb	r2, [r9, #1]	@ zero_extendqisi2
	strb	r2, [r3, #944]
	bl	VCTRL_ConfigChanCompress
	ldr	r0, [r6, r5, asl #2]
	mov	r2, #12
	ldr	r8, [r8, #52]
	add	r0, r0, #1088
	ldr	r1, [fp, #-120]
	add	r0, r0, r2
	blx	r8
	ldr	lr, [r6, r5, asl #2]
	add	r0, lr, #475136
	ldr	r6, [lr, #536]
	ldr	r2, [r0, #1000]
	cmp	r2, r6
	beq	.L2070
	mov	r0, r5
	bl	VCTRL_ResetChan
	ldr	r3, [r9, #8]
	ldr	r2, .L2100
	cmp	r3, #20
	ldr	lr, [r2, r5, asl #2]
	beq	.L2071
	ldr	r6, [lr, #536]
	add	r0, lr, #475136
.L2070:
	ldr	r1, .L2100+28
	ldr	r2, .L2100+32
	str	r6, [r0, #1000]
.L2075:
	ldr	r3, [r4, #4]!
	add	r1, r1, #4
	add	r2, r2, #4
	cmp	r3, #0
	streq	r3, [r1, #-4]
	ldrne	r0, [r3, #20]
	strne	r0, [r1, #-4]
	ldrne	r3, [r3, #20]
	cmp	r4, r10
	str	r3, [r2, #-4]
	bne	.L2075
	ldr	r0, .L2100+28
	bl	VDMDRV_SetPriority
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2096:
	ldr	r1, .L2100+36
	mov	r7, r2
	bl	dprint_vfmw
.L2086:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2051:
	ldr	r1, .L2100+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2097:
	cmp	r1, #16
	beq	.L2089
	b	.L2062
.L2095:
	sub	r0, fp, #112
	bl	REAL9DEC_Support
	ldr	r2, [fp, #-112]
	cmp	r2, #0
	bne	.L2076
.L2056:
	mvn	r7, #0
	b	.L2086
.L2094:
	sub	r0, fp, #112
	bl	REAL8DEC_Support
	ldr	r2, [fp, #-112]
	cmp	r2, #0
	beq	.L2056
	ldr	r2, [r9, #8]
	b	.L2055
.L2092:
	ldr	r3, .L2100+44
	movw	r2, #2969
	ldr	r1, .L2100+48
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2086
.L2098:
	ldr	r2, [r3, #84]
	cmp	r2, #0
	bne	.L2066
	b	.L2065
.L2099:
	sub	r1, fp, #116
	mov	r0, r5
	strb	r2, [fp, #-116]
	bl	FSP_ConfigAttribute
	ldr	r3, [fp, #-124]
	b	.L2068
.L2093:
	ldr	r1, .L2100+52
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2086
.L2071:
	ldr	r3, [lr, #328]
	mov	r0, r5
	ldr	r2, [lr, #1232]
	ldr	r1, [lr, #1228]
	ldr	lr, [lr, #332]
	str	lr, [sp]
	bl	VCTRL_PartitionMemForStdUser
	cmp	r0, #0
	bne	.L2072
	ldr	r3, .L2100
	ldr	lr, [r3, r5, asl #2]
	add	r0, lr, #475136
	ldr	r6, [lr, #536]
	b	.L2070
.L2090:
	ldr	r3, .L2100+56
	movw	r2, #2967
	ldr	r1, .L2100+48
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2086
.L2091:
	mov	r0, r2
	ldr	r3, .L2100+60
	movw	r2, #2968
	ldr	r1, .L2100+48
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2086
.L2072:
	mov	r0, #1
	ldr	r1, .L2100+64
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2086
.L2101:
	.align	2
.L2100:
	.word	.LANCHOR0
	.word	.LANCHOR4
	.word	.LANCHOR4+1548
	.word	.LANCHOR4+1692
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0-4
	.word	.LANCHOR2
	.word	.LANCHOR4+1696
	.word	g_ChanCtx
	.word	.LC214
	.word	.LC213
	.word	.LC72
	.word	.LC1
	.word	.LC212
	.word	.LC71
	.word	.LC2
	.word	.LC215
	UNWIND(.fnend)
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	2
	.type	VfmwProc_SetDropStreamThread, %function
VfmwProc_SetDropStreamThread:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #144)
	sub	sp, sp, #144
	ldr	r4, [r0]
	ldr	r1, .L2104
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2104+4
	mov	r2, #140
	mov	r1, #0
	sub	r0, fp, #160
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #160
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2102
	sub	r1, fp, #160
	mov	r0, r4
	str	r5, [fp, #-128]
	bl	VCTRL_ConfigChan
.L2102:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2105:
	.align	2
.L2104:
	.word	.LC216
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	2
	.type	VfmwProc_SetDecMode, %function
VfmwProc_SetDecMode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #144)
	sub	sp, sp, #144
	ldr	r4, [r0]
	ldr	r1, .L2110
	mov	r0, #32
	and	r5, r4, #7
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2110+4
	mov	r2, #140
	mov	r1, #0
	sub	r0, fp, #160
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #160
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	beq	.L2109
	mov	r2, r4
	ldr	r1, .L2110+8
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2109:
	sub	r1, fp, #160
	mov	r0, r4
	str	r5, [fp, #-124]
	bl	VCTRL_ConfigChan
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2111:
	.align	2
.L2110:
	.word	.LC217
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC218
	UNWIND(.fnend)
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	2
	.type	VfmwProc_SetDecOrderOutput, %function
VfmwProc_SetDecOrderOutput:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #144)
	sub	sp, sp, #144
	ldr	r4, [r0]
	ldr	r1, .L2114
	mov	r0, #32
	and	r5, r4, #3
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2114+4
	mov	r2, #140
	mov	r1, #0
	sub	r0, fp, #160
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #160
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2112
	sub	r1, fp, #160
	mov	r0, r4
	str	r5, [fp, #-120]
	bl	VCTRL_ConfigChan
.L2112:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2115:
	.align	2
.L2114:
	.word	.LC219
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	2
	.type	VfmwProc_SetErrorThread, %function
VfmwProc_SetErrorThread:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #144)
	sub	sp, sp, #144
	ldr	r4, [r0]
	ldr	r1, .L2118
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2118+4
	mov	r2, #140
	mov	r1, #0
	sub	r0, fp, #160
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #160
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2116
	sub	r1, fp, #160
	mov	r0, r4
	str	r5, [fp, #-132]
	bl	VCTRL_ConfigChan
.L2116:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2119:
	.align	2
.L2118:
	.word	.LC220
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	2
	.type	VfmwProc_TestResetChan, %function
VfmwProc_TestResetChan:
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
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L2121
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2122:
	.align	2
.L2121:
	.word	.LC221
	UNWIND(.fnend)
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	2
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
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
	ldr	r5, .L2138
	mov	r4, r0
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r4, #31
	ldrhi	ip, .L2138+4
	movwhi	r3, #2389
	bhi	.L2133
	ldr	r6, .L2138+8
	ldr	r7, [r6, r4, asl #2]
	cmp	r7, #0
	beq	.L2134
	ldr	r8, [r7, #4]
	cmp	r8, #1
	bne	.L2135
	mov	r0, #0
	str	r0, [r7, #8]
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, r4
	bl	SCDDRV_IsChanDec
	cmp	r0, #0
	bne	.L2136
.L2128:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r2, .L2138+12
	ldr	r3, [r5, #12]
	mov	r8, #0
	mov	r0, #4
	ldr	r7, .L2138
	str	r8, [r2, r4, asl #2]
	blx	r3
	mov	r0, r4
	bl	VCTRL_StopChan
	ldr	r3, [r7, #16]
	subs	r5, r0, #0
	mov	r0, #4
	bne	.L2137
	blx	r3
	mov	r0, r4
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	r3, .L2138+16
	ldr	r2, [r7, #12]
	mov	r0, #4
	add	r3, r3, r4, lsl #2
	str	r5, [r3, #-640]
	blx	r2
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r5, [r6, r4, asl #2]
	add	ip, r3, #475136
	add	lr, r3, #228
	ldr	r1, [r3, #304]
	add	r2, r3, #471040
	ldr	r9, [r3, #308]
	add	r2, r2, #920
	ldr	r8, [r3, #300]
	add	r6, r6, r4, lsl #4
	ldr	r10, [ip, #948]
	add	ip, r3, #252
	add	r3, r3, #276
	str	r3, [fp, #-72]
	ldr	r3, .L2138+20
	str	lr, [fp, #-80]
	str	ip, [fp, #-76]
	str	r5, [r3, r4, asl #3]
	str	r1, [fp, #-56]
	str	r2, [fp, #-68]
	str	r10, [fp, #-64]
	str	r9, [fp, #-52]
	str	r8, [fp, #-60]
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r4
	bl	SCDDRV_ResetSCD
	mov	r0, r4
	bl	VDMDRV_ResetVDH
	ldr	r2, [r7, #16]
	mvn	r3, #0
	str	r5, [r6, #396]
	str	r3, [r6, #408]
	mov	r0, #4
	str	r3, [r6, #404]
	str	r5, [r6, #400]
	blx	r2
	ldr	r3, [r7, #16]
	mov	r0, r5
	blx	r3
	ldr	r3, [r7, #24]
	mov	r1, r4
	mov	r0, #1
	blx	r3
	sub	r1, fp, #80
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	mov	r0, #1
	ldr	r3, [r7, #28]
	mov	r1, r4
	blx	r3
	mov	r0, r5
.L2125:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2136:
	mov	r0, r4
	ldr	r7, [r5, #132]
	bl	SCDDRV_IsChanDec
	mov	r2, #500
	clz	r1, r0
	mov	r0, r8
	mov	r1, r1, lsr #5
	blx	r7
	b	.L2128
.L2135:
	ldr	ip, .L2138+24
	movw	r3, #2410
.L2133:
	ldr	r2, .L2138+28
	mov	r0, #0
	ldr	r1, .L2138+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2137:
	blx	r3
	ldr	r3, [r7, #16]
	mov	r0, r8
	blx	r3
	mvn	r0, #0
	b	.L2125
.L2134:
	ldr	ip, .L2138+36
	movw	r3, #2398
	ldr	r2, .L2138+28
	mov	r0, r7
	ldr	r1, .L2138+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, r7
	blx	r3
	mvn	r0, #0
	b	.L2125
.L2139:
	.align	2
.L2138:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
	.word	.LANCHOR0
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR3
	.word	s_SmIIS
	.word	.LC224
	.word	.LANCHOR1+708
	.word	.LC222
	.word	.LC223
	UNWIND(.fnend)
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	2
	.global	VCTRL_CloseVfmw
	.type	VCTRL_CloseVfmw, %function
VCTRL_CloseVfmw:
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
	ldr	r6, .L2158
	ldr	r3, [r6, #128]
	cmp	r3, #1
	bne	.L2147
	sub	r5, r6, #4
	mov	r4, #0
.L2143:
	ldr	r3, [r5, #4]!
	mov	r0, r4
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L2142
	bl	VCTRL_DestroyChan
.L2142:
	cmp	r4, #32
	bne	.L2143
	bl	FSP_Exit
	ldr	r3, [r6, #132]
	mov	r2, #3
	ldr	r5, .L2158+4
	cmp	r3, #0
	str	r2, [r6, #136]
	beq	.L2145
	mov	r0, #10
	ldr	r3, [r5, #120]
	mov	r4, #49
	blx	r3
	b	.L2146
.L2157:
	ldr	r3, [r5, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L2145
.L2146:
	ldr	r3, [r6, #132]
	mov	r0, #10
	cmp	r3, #0
	bne	.L2157
.L2145:
	ldr	r3, [r5, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L2158+8
	blx	r3
	ldr	r0, .L2158+12
	bl	CloseDrivers
	mov	r3, #0
	mov	r0, r3
	str	r3, [r6, #128]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2147:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2159:
	.align	2
.L2158:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-640
	.word	.LANCHOR0+152
	UNWIND(.fnend)
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	2
	.type	VfmwProc_TestRestartChan, %function
VfmwProc_TestRestartChan:
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
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StopChan
	mov	r2, r4
	ldr	r1, .L2161
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L2161+4
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_StartChan
	mov	r2, r4
	ldr	r1, .L2161+8
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2162:
	.align	2
.L2161:
	.word	.LC225
	.word	.LC221
	.word	.LC197
	UNWIND(.fnend)
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	2
	.type	VfmwProc_TestStopChan, %function
VfmwProc_TestStopChan:
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
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StopChan
	mov	r2, r4
	ldr	r1, .L2164
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2165:
	.align	2
.L2164:
	.word	.LC225
	UNWIND(.fnend)
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	2
	.global	VCTRL_InitDspCode
	.type	VCTRL_InitDspCode, %function
VCTRL_InitDspCode:
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
	cmp	r1, #6
	mov	r5, r0
	moveq	r4, #1
	beq	.L2167
	cmp	r1, #0
	moveq	r4, #2
	movne	r4, #0
.L2167:
	ldr	r3, .L2181
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2177
	mov	r1, r4
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Require_DspCode
.L2177:
	ldr	r6, .L2181+4
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L2178
	mov	r0, #0
	blx	r3
.L2170:
	ldr	r3, [r6, #20]
	cmp	r3, #0
	beq	.L2179
	mov	r0, #0
	blx	r3
.L2172:
	ldr	r3, [r6, #12]
	cmp	r3, #0
	beq	.L2180
	mov	r0, #0
	blx	r3
.L2174:
	mov	r1, r4
	mov	r0, #0
	bl	SCDDRV_LoadDspCode
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_CloseHardware
.L2178:
	mov	r0, r3
	mov	r2, #3264
	ldr	r1, .L2181+8
	bl	dprint_vfmw
	b	.L2170
.L2179:
	mov	r0, r3
	movw	r2, #3265
	ldr	r1, .L2181+8
	bl	dprint_vfmw
	b	.L2172
.L2180:
	mov	r0, r3
	movw	r2, #3266
	ldr	r1, .L2181+8
	bl	dprint_vfmw
	b	.L2174
.L2182:
	.align	2
.L2181:
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	2
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
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
	ldr	r3, .L2209
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	ldr	r1, [r3, #536]
	cmp	r1, #0
	movne	r3, #1
	movne	r6, #0
	ldreq	r6, [r3, #1172]
	clzeq	r3, r6
	moveq	r3, r3, lsr #5
.L2184:
	cmp	r1, #6
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	beq	.L2205
.L2196:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2205:
	ldr	r7, .L2209+4
	ldr	r4, [r7, #-640]
	cmp	r4, #0
	bne	.L2185
	sub	r3, r7, #640
	sub	r2, r7, #516
	b	.L2186
.L2207:
	cmp	r3, r2
	beq	.L2206
.L2186:
	ldr	r4, [r3, #4]!
	cmp	r4, #0
	beq	.L2207
.L2185:
	cmp	r4, #1
	beq	.L2208
	cmp	r1, #6
	beq	.L2196
	ldr	r1, .L2209+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2206:
	mov	r0, r5
	add	r5, r7, r5, lsl #2
	bl	VCTRL_InitDspCode
	cmp	r6, #1
	mov	r0, r4
	streq	r6, [r5, #-640]
	movne	r3, #2
	strne	r3, [r5, #-640]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2208:
	cmp	r6, #1
	beq	.L2196
	ldr	r1, .L2209+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2210:
	.align	2
.L2209:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	.LC227
	.word	.LC226
	UNWIND(.fnend)
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	2
	.global	VCTRL_SetChanFsPartitionState
	.type	VCTRL_SetChanFsPartitionState, %function
VCTRL_SetChanFsPartitionState:
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
	ldr	r3, .L2212
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #442368
	str	r1, [r3, #2056]
	ldmfd	sp, {fp, sp, pc}
.L2213:
	.align	2
.L2212:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	2
	.global	VCTRL_GetCurChanFsSize
	.type	VCTRL_GetCurChanFsSize, %function
VCTRL_GetCurChanFsSize:
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
	ldr	r3, .L2215
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #471040
	ldr	r0, [r3, #892]
	ldmfd	sp, {fp, sp, pc}
.L2216:
	.align	2
.L2215:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	2
	.global	VCTRT_SetChanCtrlState
	.type	VCTRT_SetChanCtrlState, %function
VCTRT_SetChanCtrlState:
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
	cmp	r1, #1
	beq	.L2219
	bcc	.L2220
	cmp	r1, #2
	bne	.L2227
	ldr	r3, .L2228
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #1420]
	cmp	r3, #1
	beq	.L2224
	mov	r3, #0
	str	r1, [r0, #1420]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2227:
	mov	r3, #0
.L2218:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2220:
	ldr	r2, .L2228
	mov	r1, #0
	mov	r3, r1
	add	r0, r2, r0, lsl #2
	str	r1, [r0, #1420]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2219:
	ldr	r3, .L2228
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #1420]
	cmp	r3, #0
	bne	.L2224
	str	r1, [r0, #1420]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2224:
	mvn	r3, #0
	b	.L2218
.L2229:
	.align	2
.L2228:
	.word	.LANCHOR4
	UNWIND(.fnend)
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	2
	.global	VCTRL_AddFrameBufMemoryRecord
	.type	VCTRL_AddFrameBufMemoryRecord, %function
VCTRL_AddFrameBufMemoryRecord:
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
	ldr	r3, [r0]
	mov	r4, r0
	cmp	r3, #255
	beq	.L2231
	ldr	r2, [r0, #12]
	ldr	r1, [r0, #24]
	ldr	r0, [r0, #32]
	bl	MEM_AddMemRecord
.L2231:
	ldr	r3, [r4, #4]
	cmp	r3, #255
	beq	.L2232
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #48]
	bl	MEM_AddMemRecord
.L2232:
	ldr	r3, [r4, #8]
	cmp	r3, #255
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r4, #20]
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #64]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MEM_AddMemRecord
	UNWIND(.fnend)
	.size	VCTRL_AddFrameBufMemoryRecord, .-VCTRL_AddFrameBufMemoryRecord
	.align	2
	.global	VCTRL_SetSingleFrameBufToChan
	.type	VCTRL_SetSingleFrameBufToChan, %function
VCTRL_SetSingleFrameBufToChan:
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
	ldr	r6, .L2274
	mov	r5, r0
	mov	r4, r1
	ldr	r1, [r1, #12]
	ldr	r2, [r6, r0, asl #2]
	add	r3, r2, #475136
	add	r2, r2, #471040
	ldr	r0, [r3, #368]
	cmp	r0, r1
	beq	.L2241
	ldr	ip, [r2, #888]
	cmp	ip, #0
	beq	.L2269
.L2241:
	ldr	r2, [r2, #3280]
	cmp	r2, #0
	beq	.L2243
	ldr	r2, [r3, #400]
	cmp	r2, #0
	beq	.L2270
.L2243:
	ldr	r7, .L2274+4
	mov	r0, #8
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r0, [r6, r5, asl #2]
	add	r2, r0, #471040
	ldr	r3, [r2, #920]
	cmp	r3, #255
	beq	.L2251
	add	r2, r2, #992
	mov	ip, #1
	b	.L2245
.L2272:
	add	ip, ip, #1
	cmp	ip, #32
	beq	.L2271
.L2245:
	ldr	lr, [r2]
	add	r2, r2, #72
	cmp	lr, #255
	bne	.L2272
.L2244:
	mov	r2, ip, asl #6
	ldr	r3, [r7, #52]
	add	ip, r2, ip, lsl #3
	mov	r1, r4
	add	ip, ip, #471040
	mov	r2, #72
	add	ip, ip, #920
	add	r0, r0, ip
	blx	r3
	ldr	r3, [r6, r5, asl #2]
	mov	r0, r4
	add	r3, r3, #475136
	ldr	r2, [r3, #400]
	add	r2, r2, #1
	str	r2, [r3, #400]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	r3, [r6, r5, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #404]
	cmp	r3, #0
	bne	.L2273
.L2249:
	mov	r4, #0
.L2248:
	ldr	r3, [r7, #16]
	mov	r0, #8
	blx	r3
	mov	r0, r4
.L2264:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2270:
	ldr	r3, [r4, #8]
	cmp	r3, #255
	bne	.L2243
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #9091
	ldr	r2, .L2274+8
	ldr	r1, .L2274+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2264
.L2271:
	mov	r3, r5
	ldr	r2, .L2274+8
	ldr	r1, .L2274+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2248
.L2273:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_SetSingleFrameBuf
	cmp	r0, #0
	beq	.L2249
	mov	r3, r5
	ldr	r2, .L2274+8
	ldr	r1, .L2274+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2248
.L2251:
	mov	ip, #0
	b	.L2244
.L2269:
	str	r0, [sp, #4]
	movw	r3, #9081
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L2274+8
	ldr	r1, .L2274+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2264
.L2275:
	.align	2
.L2274:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+728
	.word	.LC229
	.word	.LC231
	.word	.LC230
	.word	.LC228
	UNWIND(.fnend)
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	2
	.global	VCTRL_AllocMemToDecoder
	.type	VCTRL_AllocMemToDecoder, %function
VCTRL_AllocMemToDecoder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #72)
	sub	sp, sp, #72
	ldr	r4, .L2285
	mov	r7, r0, asl #2
	mov	r5, r0
	add	r3, r4, r7
	ldr	r8, [r3, #1420]
	cmp	r8, #0
	bne	.L2277
	ldr	ip, .L2285+4
	mov	lr, #1
	mov	r2, #72
	str	lr, [r3, #1420]
	sub	r0, fp, #108
	ldr	r3, [ip, #52]
	blx	r3
	sub	r1, fp, #108
	mov	r0, r5
	bl	VCTRL_SetSingleFrameBufToChan
	subs	r6, r0, #0
	bne	.L2278
	ldr	r3, .L2285+8
	ldr	r1, [r3, r5, asl #2]
.L2279:
	add	r3, r1, #442368
	mov	r2, #2
	ldr	r1, .L2285+12
	mov	r0, #31
	str	r2, [r3, #2056]
	add	r4, r4, r7
	bl	dprint_vfmw
	mov	r0, r6
	mov	r3, #0
	str	r3, [r4, #1420]
.L2284:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2278:
	ldr	r9, .L2285+8
	ldr	r1, [r9, r5, asl #2]
	add	r3, r1, #471040
	ldr	r3, [r3, #892]
	cmp	r3, #0
	beq	.L2279
	mov	r2, r5
	ldr	r1, .L2285+16
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r9, r5, asl #2]
	mov	r2, #3
	add	r3, r1, #442368
	str	r2, [r3, #2056]
	b	.L2279
.L2277:
	mov	r3, r0
	ldr	r2, .L2285+20
	ldr	r1, .L2285+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2284
.L2286:
	.align	2
.L2285:
	.word	.LANCHOR4
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC233
	.word	.LC232
	.word	.LANCHOR1+760
	.word	.LC234
	UNWIND(.fnend)
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	2
	.global	VCTRL_GetImageWidth
	.type	VCTRL_GetImageWidth, %function
VCTRL_GetImageWidth:
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
	ldr	r3, .L2295
	ldr	r0, [r3, r0, asl #2]
	add	r0, r0, #475136
	ldr	r3, [r0, #1000]
	cmp	r3, #2
	beq	.L2289
	cmp	r3, #16
	beq	.L2290
	cmp	r3, #0
	beq	.L2294
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2294:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageWidth
.L2290:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageWidth
.L2289:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageWidth
.L2296:
	.align	2
.L2295:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageWidth, .-VCTRL_GetImageWidth
	.align	2
	.global	VCTRL_GetImageHeight
	.type	VCTRL_GetImageHeight, %function
VCTRL_GetImageHeight:
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
	ldr	r3, .L2305
	ldr	r0, [r3, r0, asl #2]
	add	r0, r0, #475136
	ldr	r3, [r0, #1000]
	cmp	r3, #2
	beq	.L2299
	cmp	r3, #16
	beq	.L2300
	cmp	r3, #0
	beq	.L2304
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2304:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageHeight
.L2300:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageHeight
.L2299:
	add	r0, r0, #1008
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageHeight
.L2306:
	.align	2
.L2305:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageHeight, .-VCTRL_GetImageHeight
	.align	2
	.global	VCTRL_GetFsSize
	.type	VCTRL_GetFsSize, %function
VCTRL_GetFsSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	ldr	r3, .L2312
	mov	r5, r0
	mov	r6, r1
	mov	r7, r2
	sub	r0, fp, #52
	ldr	r3, [r3, #48]
	mov	r2, #24
	mov	r1, #0
	blx	r3
	ldr	r3, .L2312+4
	ldr	r4, [r3, #52]
	cmp	r4, #0
	beq	.L2308
	ldr	ip, .L2312+8
	sub	r3, fp, #52
	str	r3, [sp, #4]
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	ldr	ip, [ip, r5, asl #2]
	mov	r3, #0
	add	ip, ip, #475136
	ldr	ip, [ip, #1000]
	str	ip, [sp]
	blx	r4
.L2308:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2313:
	.align	2
.L2312:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	2
	.global	VCTRL_EnableEsBuf
	.type	VCTRL_EnableEsBuf, %function
VCTRL_EnableEsBuf:
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
	ldr	r3, .L2315
	mov	r2, #1
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1824]
	ldmfd	sp, {fp, sp, pc}
.L2316:
	.align	2
.L2315:
	.word	.LANCHOR4
	UNWIND(.fnend)
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	2
	.global	VCTRL_DisableEsBuf
	.type	VCTRL_DisableEsBuf, %function
VCTRL_DisableEsBuf:
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
	ldr	r3, .L2318
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1824]
	ldmfd	sp, {fp, sp, pc}
.L2319:
	.align	2
.L2318:
	.word	.LANCHOR4
	UNWIND(.fnend)
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	2
	.global	VCTRL_IfEsBufEnable
	.type	VCTRL_IfEsBufEnable, %function
VCTRL_IfEsBufEnable:
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
	ldr	r3, .L2321
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #1824]
	ldmfd	sp, {fp, sp, pc}
.L2322:
	.align	2
.L2321:
	.word	.LANCHOR4
	UNWIND(.fnend)
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
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
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.55975, %object
	.size	__func__.55975, 18
__func__.55975:
	.ascii	"VCTRL_EventReport\000"
	.space	2
	.type	__func__.55911, %object
	.size	__func__.55911, 20
__func__.55911:
	.ascii	"VCTRL_RecordPosTime\000"
	.type	__func__.55916, %object
	.size	__func__.55916, 17
__func__.55916:
	.ascii	"VCTRL_RecordData\000"
	.space	3
	.type	__func__.55987, %object
	.size	__func__.55987, 18
__func__.55987:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__FUNCTION__.56093, %object
	.size	__FUNCTION__.56093, 29
__FUNCTION__.56093:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__func__.56117, %object
	.size	__func__.56117, 23
__func__.56117:
	.ascii	"VCTRL_FreeChanResource\000"
	.space	1
	.type	__func__.56371, %object
	.size	__func__.56371, 25
__func__.56371:
	.ascii	"VCTRL_TryToRelSpecialFrm\000"
	.space	3
	.type	__func__.56388, %object
	.size	__func__.56388, 19
__func__.56388:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__FUNCTION__.56396, %object
	.size	__FUNCTION__.56396, 19
__FUNCTION__.56396:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__FUNCTION__.56406, %object
	.size	__FUNCTION__.56406, 23
__FUNCTION__.56406:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.56407, %object
	.size	__func__.56407, 23
__func__.56407:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.56441, %object
	.size	__func__.56441, 18
__func__.56441:
	.ascii	"VCTRL_GetDecParam\000"
	.space	2
	.type	__FUNCTION__.56578, %object
	.size	__FUNCTION__.56578, 19
__FUNCTION__.56578:
	.ascii	"VCTRL_FlushDecoder\000"
	.space	1
	.type	__FUNCTION__.56871, %object
	.size	__FUNCTION__.56871, 18
__FUNCTION__.56871:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__FUNCTION__.56877, %object
	.size	__FUNCTION__.56877, 19
__FUNCTION__.56877:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__FUNCTION__.56883, %object
	.size	__FUNCTION__.56883, 16
__FUNCTION__.56883:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__FUNCTION__.56821, %object
	.size	__FUNCTION__.56821, 14
__FUNCTION__.56821:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	g_ProcCommandTable, %object
	.size	g_ProcCommandTable, 344
g_ProcCommandTable:
	.word	0
	.word	VfmwProc_SetPrintLevel
	.word	2
	.word	VfmwProc_SetErrorThread
	.word	3
	.word	VfmwProc_SetDefaultOutputOrder
	.word	4
	.word	VfmwProc_SetDecOrderOutput
	.word	5
	.word	VfmwProc_SetDecMode
	.word	7
	.word	VfmwProc_SetDropStreamThread
	.word	8
	.word	VfmwProc_SetVp9DecFrameNum
	.word	11
	.word	VfmwProc_SetUSE_FF_APT_EN
	.word	12
	.word	VfmwProc_SetSaveFileAfterReset
	.word	13
	.word	VfmwProc_SetCurProcChan
	.word	256
	.word	VfmwProc_PrintTracer
	.word	257
	.word	VfmwProc_SetScdPrint
	.word	512
	.word	VfmwProc_Savestream
	.word	513
	.word	VfmwProc_SaveSeg
	.word	514
	.word	VfmwProc_SaveYUV
	.word	516
	.word	VfmwProc_Save1DYUV
	.word	528
	.word	VfmwProc_SaveMetadata
	.word	544
	.word	VfmwProc_SaveReorderMetadata
	.word	560
	.word	VfmwProc_SaveEL
	.word	768
	.word	VfmwProc_TestSuspend
	.word	769
	.word	VfmwProc_TestResume
	.word	896
	.word	VfmwProc_TestStopChan
	.word	897
	.word	VfmwProc_TestResetChan
	.word	898
	.word	VfmwProc_TestStartChan
	.word	899
	.word	VfmwProc_TestRestartChan
	.word	1024
	.word	VfmwProc_TestTimeSequence
	.word	1026
	.word	VfmwProc_TestStopDec
	.word	1280
	.word	VfmwProc_SetTraceCtrl
	.word	1281
	.word	VfmwProc_SetTraceBSPeriod
	.word	1282
	.word	VfmwProc_SetTraceFramePeriod
	.word	1283
	.word	VfmwProc_SetTraceImgPeriod
	.word	1285
	.word	VfmwProc_SetSaveYuvBitWidth
	.word	1536
	.word	VfmwProc_OpenModuleLowly
	.word	1537
	.word	VfmwProc_CloseModuleLowly
	.word	1538
	.word	VfmwProc_SetTunnelLineNumber
	.word	1539
	.word	VfmwProc_OpenScdLowdly
	.word	1540
	.word	VfmwProc_CloseScdLowdly
	.word	1541
	.word	VfmwProc_SetSedOnlyEnable
	.word	1792
	.word	VfmwProc_SetSmmuIrqEnable
	.word	2048
	.word	VfmwProc_SetCompressPara
	.word	2304
	.word	VfmwProc_SetClkSelect
	.word	2305
	.word	VfmwProc_SetStandardObedience
	.word	65535
	.word	0
	.type	__func__.56201, %object
	.size	__func__.56201, 18
__func__.56201:
	.ascii	"VCTRL_DestroyChan\000"
	.space	2
	.type	__func__.57271, %object
	.size	__func__.57271, 30
__func__.57271:
	.ascii	"VCTRL_SetSingleFrameBufToChan\000"
	.space	2
	.type	__func__.57283, %object
	.size	__func__.57283, 24
__func__.57283:
	.ascii	"VCTRL_AllocMemToDecoder\000"
	.data
	.align	2
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
	.space	59
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"InstID out of range\000" )
.LC1:
	ASCII(.ascii	"vfmw_ctrl.c,L%d: %s\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"Chan inactive\000" )
	.space	2
.LC3:
	ASCII(.ascii	"s_VfmwCTrl.event_report_vdec = NULL\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"s_VfmwCTrl.event_report_omxvdec = NULL\012\000" )
.LC5:
	ASCII(.ascii	"%s Unkown Adapter Type: %d, Len: %d\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"Set standard obedience: %d\012\000" )
.LC7:
	ASCII(.ascii	"g_ClkSelect(%d) set error! dat = %d not support\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC8:
	ASCII(.ascii	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d, YRatio: 0.%d" )
	ASCII(.ascii	", UVRatio: 0.%d\012\000" )
.LC9:
	ASCII(.ascii	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"ChanID:%d, Compress Disable!\000" )
	.space	3
.LC11:
	ASCII(.ascii	"ChanID:%d; \000" )
.LC12:
	ASCII(.ascii	"VCmpEnable:%d; \000" )
.LC13:
	ASCII(.ascii	"LossCmpEnable:%d; \000" )
	.space	1
.LC14:
	ASCII(.ascii	"YCmpRatio:%d, YCmpRatio:%d\012\000" )
.LC15:
	ASCII(.ascii	"ChanID %d Already Create! Can not be set!!\012\000" )
.LC16:
	ASCII(.ascii	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleL" )
	ASCII(.ascii	"owlyEnable = 1 ------\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"ERROR: g_SaveYUVBitWidth should be 8 or 10! (not to" )
	ASCII(.ascii	" be %d)\012\000" )
.LC18:
	ASCII(.ascii	"------ g_SaveYUVBitWidth = %d ------\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"------ g_TraceImgPeriod = %x ------\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"------ g_TraceFramePeriod = %x ------\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"------ g_TraceBsPeriod = %x ------\012\000" )
.LC22:
	ASCII(.ascii	"------ g_TraceCtrl = %x ------\012\000" )
.LC23:
	ASCII(.ascii	"------ dec stop = %d ------\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"------ dec task delay %d ms ------\012\000" )
.LC25:
	ASCII(.ascii	"%s/vfmw_el_save_%d.dat\000" )
	.space	1
.LC26:
	ASCII(.ascii	"OK create file '%s' for channel %d el stream save\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC27:
	ASCII(.ascii	"failed create file '%s' for el stream save!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	">>>> close el stream saving >>>>\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"NO SUCH CHANNEL : %d\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"Pay attention to  CHANNEL : %d\012\000" )
.LC31:
	ASCII(.ascii	"ResetCreateNewSave = %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"ResetCreateNewSave can NOT be set to %d, must be 0 " )
	ASCII(.ascii	"or 1\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"USE_FF_APT_EN = %d\012\000" )
.LC34:
	ASCII(.ascii	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\012" )
	ASCII(.ascii	"\000" )
.LC35:
	ASCII(.ascii	"g_CfgVp9FrmNum = %d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"Invalid output order %d\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"set default output order %d\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"OK create file '%s' for channel %d metadata_reorder" )
	ASCII(.ascii	" stream save\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"failed create file '%s' for metadata_reorder stream" )
	ASCII(.ascii	" save!\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	">>>> close metadata stream saving >>>>\012\000" )
.LC41:
	ASCII(.ascii	"OK create file '%s' for channel %d metadata stream " )
	ASCII(.ascii	"save\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"failed create file '%s' for metadata stream save!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC43:
	ASCII(.ascii	"address '0x%x' is not valid!\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"1d image has been saved to '%s'\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"open file '%s' fail!\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"OK create file '%s' for channel %d seg stream save\012" )
	ASCII(.ascii	"\000" )
.LC48:
	ASCII(.ascii	"failed create file '%s' for seg stream save!\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	">>>> close seg stream saving >>>>\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"OK create file '%s' for channel %d raw stream save\012" )
	ASCII(.ascii	"\000" )
.LC51:
	ASCII(.ascii	"failed create file '%s' for raw stream save!\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	">>>> close raw stream saving >>>>\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"Failed to alloc VFMW_DumpImageTmp size %d!\012\000" )
.LC54:
	ASCII(.ascii	"OK create file '%s' for chan %d yuv save.(crop %d)\012" )
	ASCII(.ascii	"\000" )
.LC55:
	ASCII(.ascii	"failed create file '%s' for yuv save!\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"OK close yuv save.\012\000" )
.LC57:
	ASCII(.ascii	"print memory tracer...\012\000" )
.LC58:
	ASCII(.ascii	"unmask vfmw mmu err int!\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"mask vfmw mmu err int!\012\000" )
.LC60:
	ASCII(.ascii	"Disable SedOnly Func\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"Enable SedOnly Func\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"The channel number is to Large.\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"Force vdm %d sleep.\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"Vfmw suspend totally take %d ms\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSlee" )
	ASCII(.ascii	"p=%d)!\012\000" )
	.space	1
.LC66:
	ASCII(.ascii	"Force scd %d sleep.\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"proc cmd need no param:%p\012\000" )
	.space	1
.LC68:
	ASCII(.ascii	"Vfmw resume totally take %d ms\012\000" )
.LC69:
	ASCII(.ascii	"%s,%d,pos(%d) error!\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"%s, %d, pos(%d) error!\012\000" )
.LC71:
	ASCII(.ascii	"ChanID out of range\000" )
.LC72:
	ASCII(.ascii	"can NOT config a not-opened Chan\000" )
	.space	3
.LC73:
	ASCII(.ascii	"event_report null!\000" )
	.space	1
.LC74:
	ASCII(.ascii	"%s Unkown Adapter Type: %d\012\000" )
.LC75:
	ASCII(.ascii	"pstStreamParam is NULL\000" )
	.space	1
.LC76:
	ASCII(.ascii	"L: %d, Stream Interface Error!!, ChanID: %d\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"pstStreamIntf is NULL\000" )
	.space	2
.LC78:
	ASCII(.ascii	"This Chan has not been created!!!\000" )
	.space	2
.LC79:
	ASCII(.ascii	"can NOT get a not-opened Chan's information of bits" )
	ASCII(.ascii	"tream\000" )
	.space	3
.LC80:
	ASCII(.ascii	"Raw FreshNum=%d, FreshSize=%d\012\000" )
	.space	1
.LC81:
	ASCII(.ascii	"Seg FreshNum=%d, FreshSize=%d\012\000" )
	.space	1
.LC82:
	ASCII(.ascii	"pArgs is null\000" )
	.space	2
.LC83:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC84:
	ASCII(.ascii	"no mem to arrange for soft dec\012\000" )
.LC85:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"%s: L%d : vdm chan memory is too small to support u" )
	ASCII(.ascii	"ser decoder\012\000" )
.LC87:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC88:
	ASCII(.ascii	"parameter err, null pointer!!!\000" )
	.space	1
.LC89:
	ASCII(.ascii	"%s FATAL: pstChan = NULL!\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"%s FATAL: pChanMem_vdh = NULL!\012\000" )
.LC91:
	ASCII(.ascii	"%s FATAL: pChanMem_frm = NULL!\012\000" )
.LC92:
	ASCII(.ascii	"DelAllFrameMemRecord err in VCTRL_FreeChanResource " )
	ASCII(.ascii	"!\012\000" )
	.space	2
.LC93:
	ASCII(.ascii	"%s FATAL: pChanMem_scd = NULL!\012\000" )
.LC94:
	ASCII(.ascii	"%s FATAL: pChanMem_ctx = NULL!\012\000" )
.LC95:
	ASCII(.ascii	"pstCfg is null\000" )
	.space	1
.LC96:
	ASCII(.ascii	"Chip not support beyond %dx%d when Std != H264/VP8/" )
	ASCII(.ascii	"MVC/USER.\012\000" )
	.space	2
.LC97:
	ASCII(.ascii	"%s,%d,s_pstVfmwChan[chanID]->FspInst.stDecFsRec[i]." )
	ASCII(.ascii	"PhyFS.PhyAddr = 0x%x\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"%s,%d,can't find special frame match DecFs Num = %d" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC99:
	ASCII(.ascii	"call VCTRL_GetChanImage, ChanID = %d,\012\000" )
	.space	1
.LC100:
	ASCII(.ascii	"This channel is not opened\000" )
	.space	1
.LC101:
	ASCII(.ascii	"%s cannot output!\012\000" )
	.space	1
.LC102:
	ASCII(.ascii	"%s: view_0 id(%d) > view_1 id(%d), error!\012\000" )
	.space	1
.LC103:
	ASCII(.ascii	"%s: continuous view0 id(%d)!\012\000" )
	.space	2
.LC104:
	ASCII(.ascii	"%s: continuous view1 id(%d)!\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"pImage is NULL\000" )
	.space	1
.LC106:
	ASCII(.ascii	"call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\012" )
	ASCII(.ascii	"\000" )
.LC107:
	ASCII(.ascii	"vdm_ctrl.c,L%d: Chan inactive\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"vdm_ctrl.c,L%d: This channel is not opened\012\000" )
.LC109:
	ASCII(.ascii	"vdm_ctrl.c,L%d: VCTRL_TryToRelSpecialFrm success!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC110:
	ASCII(.ascii	"%s call SYNTAX_ReleaseImage failed\012\000" )
.LC111:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: ChanID out of range\012\000" )
	.space	1
.LC112:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: Chan %d is not open or not ru" )
	ASCII(.ascii	"nning\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"%s VidStd=%d Error!\012\000" )
	.space	3
.LC114:
	ASCII(.ascii	"Get DecParam Type Failure!\012\000" )
.LC115:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: ChanID out of range is %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC116:
	ASCII(.ascii	"Chan %d is not open or not running\012\000" )
.LC117:
	ASCII(.ascii	"ChanId out of range\000" )
.LC118:
	ASCII(.ascii	"This channel is not running\000" )
.LC119:
	ASCII(.ascii	"line: %d Flush DPB failed!\012\000" )
.LC120:
	ASCII(.ascii	"VCTRL_FlushDecoder\012\000" )
.LC121:
	ASCII(.ascii	"fuction return value is null,%s %d MVC_OK != MVC_Fl" )
	ASCII(.ascii	"ushDPB!!\012\000" )
	.space	3
.LC122:
	ASCII(.ascii	"chan not create\000" )
.LC123:
	ASCII(.ascii	"can NOT start a not-opened Chan\000" )
.LC124:
	ASCII(.ascii	"NULL == pArgs\000" )
	.space	2
.LC125:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC126:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan" )
	ASCII(.ascii	"[ChanID]->eVidStd!\012\000" )
	.space	1
.LC127:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32" )
	ASCII(.ascii	"UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\012\000" )
.LC128:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC130:
	ASCII(.ascii	"line: %d, pLf is NULL!\012\000" )
.LC131:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame get LogicFs fail!\012\000" )
.LC133:
	ASCII(.ascii	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"VCTRL_GetChanMemSizeByOption L%d: arrange return fa" )
	ASCII(.ascii	"ilure\012\000" )
	.space	2
.LC135:
	ASCII(.ascii	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32Dis" )
	ASCII(.ascii	"playFrameNum(%d), extra_disp(%d)\012\000" )
	.space	3
.LC136:
	ASCII(.ascii	"MEM_MapRegisterAddr reg 0x%x failed!\012\000" )
	.space	2
.LC137:
	ASCII(.ascii	"VDMHAL_GetHalMemSize Vdh %d failed!\012\000" )
	.space	3
.LC138:
	ASCII(.ascii	"MEM_AllocMemBlock Vdh %d failed!\012\000" )
	.space	2
.LC139:
	ASCII(.ascii	"VDMHAL_OpenHAL Vdh %d failed!\012\000" )
	.space	1
.LC140:
	ASCII(.ascii	"MEM_AllocMemBlock VFMW_VP9Prob %d failed!\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"MEM_AllocMemBlock Scd %d failed!\012\000" )
	.space	2
.LC142:
	ASCII(.ascii	"SM_OpenSCDDrv Scd %d failed!\012\000" )
	.space	2
.LC143:
	ASCII(.ascii	"Register irq %d failed!\012\000" )
	.space	3
.LC144:
	ASCII(.ascii	"extra_ref=\000" )
	.space	1
.LC145:
	ASCII(.ascii	"=\000" )
	.space	2
.LC146:
	ASCII(.ascii	" \000" )
	.space	2
.LC147:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC148:
	ASCII(.ascii	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC149:
	ASCII(.ascii	"extra_disp=\000" )
.LC150:
	ASCII(.ascii	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC151:
	ASCII(.ascii	"extra_cmd=\000" )
	.space	1
.LC152:
	ASCII(.ascii	"HI_VFMW_VideoDecode\000" )
.LC153:
	ASCII(.ascii	"(safe,warn,danger) :amount = %d,%d,%d,%d\012\000" )
	.space	2
.LC154:
	ASCII(.ascii	"strm_ctrl: I->IPB\012\000" )
	.space	1
.LC155:
	ASCII(.ascii	"strm_ctrl: IPB->I\012\000" )
	.space	1
.LC156:
	ASCII(.ascii	"(CurrMode,NextMode) = %d,%d\012\000" )
	.space	3
.LC157:
	ASCII(.ascii	"pic_pts: %lld\012\000" )
	.space	1
.LC158:
	ASCII(.ascii	"pic_usertag: %lld\012\000" )
	.space	1
.LC159:
	ASCII(.ascii	"pic_pts: %lld pic_usertag = %lld\012\000" )
	.space	2
.LC160:
	ASCII(.ascii	"Syntax is stopped from This channel\000" )
.LC161:
	ASCII(.ascii	"[%d] vdm busy\012\000" )
	.space	1
.LC162:
	ASCII(.ascii	"[%d] no frame\012\000" )
	.space	1
.LC163:
	ASCII(.ascii	"DFS, Wait Partition\012\000" )
	.space	3
.LC164:
	ASCII(.ascii	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %" )
	ASCII(.ascii	"d, eFspPartitionState: %d\012\000" )
	.space	2
.LC165:
	ASCII(.ascii	"[%d] no stream\012\000" )
.LC166:
	ASCII(.ascii	"seg_pts: %lld, seg_usertag = %lld\012\000" )
	.space	1
.LC167:
	ASCII(.ascii	"Thread running...\012\000" )
	.space	1
.LC168:
	ASCII(.ascii	"Thread stopped!\012\000" )
	.space	3
.LC169:
	ASCII(.ascii	"thread running...\012\000" )
	.space	1
.LC170:
	ASCII(.ascii	"thread stopped...\012\000" )
	.space	1
.LC171:
	ASCII(.ascii	"Thread killed!\012\000" )
.LC172:
	ASCII(.ascii	"ERROR:ReadNum = %d larger than VFMW_MAX_RESERVE_NUM" )
	ASCII(.ascii	"(%d)\012\000" )
	.space	3
.LC173:
	ASCII(.ascii	"The array of occupied frames is overflow, s_pstVfmw" )
	ASCII(.ascii	"Chan[%d]->specialFrameNum = %d\000" )
	.space	2
.LC174:
	ASCII(.ascii	"pSpecialFrmInfo = null!!!\000" )
	.space	2
.LC175:
	ASCII(.ascii	"ChanID out of range!\000" )
	.space	3
.LC176:
	ASCII(.ascii	"pstChanState = NULL\000" )
.LC177:
	ASCII(.ascii	"s_pstVfmwChan = NULL\000" )
	.space	3
.LC178:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_ref = %d is out of [ -500" )
	ASCII(.ascii	"0, 5000 ]!\012\000" )
	.space	1
.LC179:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_disp = %d is out of [ -50" )
	ASCII(.ascii	"00, 5000 ]!\012\000" )
.LC180:
	ASCII(.ascii	"Command \"%d\" not registerd!\012\000" )
	.space	3
.LC181:
	ASCII(.ascii	"Chan %d Report Last Frame, Value=%d, LastFrameState" )
	ASCII(.ascii	"=%d\012\000" )
.LC182:
	ASCII(.ascii	"Last frame output failed!\012\000" )
	.space	1
.LC183:
	ASCII(.ascii	"Last frame output successed!\012\000" )
	.space	2
.LC184:
	ASCII(.ascii	"Last frame already output, image id: %d!\012\000" )
	.space	2
.LC185:
	ASCII(.ascii	"line %d can not know YuvFormat = %d\012\000" )
	.space	3
.LC186:
	ASCII(.ascii	"userdec frame(phy=%#x) address error!\012\000" )
	.space	1
.LC187:
	ASCII(.ascii	"can not map vir addr for usrdat frame(cbphy=%#x)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC188:
	ASCII(.ascii	"line: %d, pLogic is Null!\012\000" )
	.space	1
.LC189:
	ASCII(.ascii	"eYuvFormat %d is not support!!\012\000" )
.LC190:
	ASCII(.ascii	"pUsrdecFrame == NULL\000" )
	.space	3
.LC191:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame: VidStd is %d\012\000" )
.LC192:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame return err\012\000" )
	.space	3
.LC193:
	ASCII(.ascii	"L:%d ChanID out of range\012\000" )
	.space	2
.LC194:
	ASCII(.ascii	"L:%d This Chan has not been created!!!\012\000" )
.LC195:
	ASCII(.ascii	"L:%d WARNING: vidio std not setted!\012\000" )
	.space	3
.LC196:
	ASCII(.ascii	"WARNING: vidio std not setted!\000" )
	.space	1
.LC197:
	ASCII(.ascii	"start chan %d: VCTRL_StartChan return %d\012\000" )
	.space	2
.LC198:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !\000" )
	.space	1
.LC199:
	ASCII(.ascii	"VCTRL_StopChanWithCheck fail!\012\000" )
	.space	1
.LC200:
	ASCII(.ascii	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\012\000" )
	.space	2
.LC201:
	ASCII(.ascii	"---------------------------------------------------" )
	ASCII(.ascii	"----------------------\012\000" )
	.space	1
.LC202:
	ASCII(.ascii	"Param Invalid of PChanOption is NULL\012\000" )
	.space	2
.LC203:
	ASCII(.ascii	"line %d VCTRL_GetChanMemSize failed!\012\000" )
	.space	2
.LC204:
	ASCII(.ascii	"L: %d : part we can NOT alloc buffer for channel co" )
	ASCII(.ascii	"ntext\012\000" )
	.space	2
.LC205:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel context\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC206:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh\012\000" )
	.space	2
.LC207:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh, %#x <" )
	ASCII(.ascii	" %#x\012\000" )
	.space	3
.LC208:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel scd\012\000" )
	.space	2
.LC209:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for SCD\012\000" )
	.space	2
.LC210:
	ASCII(.ascii	"vfmw have max(%d) channels opened, can NOT create m" )
	ASCII(.ascii	"ore channels\012\000" )
	.space	3
.LC211:
	ASCII(.ascii	"Chan:%d can NOT enable FSP instance\012\000" )
	.space	3
.LC212:
	ASCII(.ascii	"VCTRL_CheckChanWH return err.\012\000" )
	.space	1
.LC213:
	ASCII(.ascii	"VFMW didn't support std %d.\012\000" )
	.space	3
.LC214:
	ASCII(.ascii	"VCTRL_ConfigChan with same config paramater.\012\000" )
	.space	2
.LC215:
	ASCII(.ascii	"can NOT VCTRL_PartitionMemForStdUser\012\000" )
	.space	2
.LC216:
	ASCII(.ascii	"chan %d: new StrmOFThr = %d\012\000" )
	.space	3
.LC217:
	ASCII(.ascii	"chan %d: new DecMode = %d\012\000" )
	.space	1
.LC218:
	ASCII(.ascii	"chan %d: GetChanCfg failed!\012\000" )
	.space	3
.LC219:
	ASCII(.ascii	"chan %d: new DecOrderOutput = %d\012\000" )
	.space	2
.LC220:
	ASCII(.ascii	"chan %d: new ChanErrThr = %d\012\000" )
	.space	2
.LC221:
	ASCII(.ascii	"reset chan %d: VCTRL_ResetChan return %d\012\000" )
	.space	2
.LC222:
	ASCII(.ascii	"%s:L%d: %s\012\000" )
.LC223:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !!!\000" )
	.space	3
.LC224:
	ASCII(.ascii	"can NOT stop a not-opened Chan\000" )
	.space	1
.LC225:
	ASCII(.ascii	"stop chan %d: VCTRL_StopChan return %d\012\000" )
.LC226:
	ASCII(.ascii	"WARNNING: dsp in lowdelay state, we can not support" )
	ASCII(.ascii	"ed  avs in the same time!!!\012\000" )
.LC227:
	ASCII(.ascii	"WARNNING: dsp in avs state, we can not supported  l" )
	ASCII(.ascii	"owdelay in the same time!!!\012\000" )
.LC228:
	ASCII(.ascii	"%s, %d, actul size = 0x%x, except size= 0x%x\012\000" )
	.space	2
.LC229:
	ASCII(.ascii	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\012\000" )
	.space	1
.LC230:
	ASCII(.ascii	"%s: Chan %d set single frame failed!\012\000" )
	.space	2
.LC231:
	ASCII(.ascii	"%s: Chan %d no frame buffer store!\012\000" )
.LC232:
	ASCII(.ascii	"DFS, request frame store fail!, chanid: %d\012\000" )
.LC233:
	ASCII(.ascii	"DFS, set decoding thread state to success!\012 \000" )
	.space	3
.LC234:
	ASCII(.ascii	"%s set chan %d ctrl state CHAN_FRAME_STORE_ALLOC fa" )
	ASCII(.ascii	"iled!\012\000" )
	.bss
	.align	3
.LANCHOR0 = . + 0
.LANCHOR3 = . + 8184
.LANCHOR4 = . + 16368
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 128
s_pstVfmwChan:
	.space	128
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 264
s_VfmwCTrl:
	.space	264
	.type	g_StandardObedience, %object
	.size	g_StandardObedience, 4
g_StandardObedience:
	.space	4
	.type	g_VfmwCompressPara, %object
	.size	g_VfmwCompressPara, 512
g_VfmwCompressPara:
	.space	512
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.space	4
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.space	4
	.type	vfmw_save_el_file, %object
	.size	vfmw_save_el_file, 128
vfmw_save_el_file:
	.space	128
	.type	save_file_cnt.57012, %object
	.size	save_file_cnt.57012, 4
save_file_cnt.57012:
	.space	4
	.type	save_el_chan_num, %object
	.size	save_el_chan_num, 4
save_el_chan_num:
	.space	4
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.space	4
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.space	4
	.type	vfmw_save_metadata_reorder_file, %object
	.size	vfmw_save_metadata_reorder_file, 128
vfmw_save_metadata_reorder_file:
	.space	128
	.type	save_file_cnt.57006, %object
	.size	save_file_cnt.57006, 4
save_file_cnt.57006:
	.space	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.space	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 128
vfmw_save_metadata_file:
	.space	128
	.type	save_file_cnt.57000, %object
	.size	save_file_cnt.57000, 4
save_file_cnt.57000:
	.space	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.56978, %object
	.size	save_file_cnt.56978, 4
save_file_cnt.56978:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	save_file_cnt.56972, %object
	.size	save_file_cnt.56972, 4
save_file_cnt.56972:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_file_cnt.56985, %object
	.size	save_file_cnt.56985, 4
save_file_cnt.56985:
	.space	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 24
MemRecord_YUV:
	.space	24
	.type	pVl, %object
	.size	pVl, 4
pVl:
	.space	4
	.type	pUl, %object
	.size	pUl, 4
pUl:
	.space	4
	.type	pY, %object
	.size	pY, 4
pY:
	.space	4
	.type	pVl_2bit, %object
	.size	pVl_2bit, 4
pVl_2bit:
	.space	4
	.type	pUl_2bit, %object
	.size	pUl_2bit, 4
pUl_2bit:
	.space	4
	.type	pY_2bit, %object
	.size	pY_2bit, 4
pY_2bit:
	.space	4
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.space	4
	.type	pPixelArray, %object
	.size	pPixelArray, 4
pPixelArray:
	.space	4
	.type	g_IsrFlag, %object
	.size	g_IsrFlag, 1
g_IsrFlag:
	.space	1
	.space	3
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 384
s_StreamIntf:
	.space	384
	.type	FspInstInfo.56089, %object
	.size	FspInstInfo.56089, 2824
FspInstInfo.56089:
	.space	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.space	4
	.type	last_rec_pos_time.56393, %object
	.size	last_rec_pos_time.56393, 128
last_rec_pos_time.56393:
	.space	128
	.type	last_rec_pos_time.56403, %object
	.size	last_rec_pos_time.56403, 128
last_rec_pos_time.56403:
	.space	128
	.type	MemArrange.56698, %object
	.size	MemArrange.56698, 1232
MemArrange.56698:
	.space	1232
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.space	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
	.space	4
	.type	g_VfmwIrqHandle, %object
	.size	g_VfmwIrqHandle, 4
g_VfmwIrqHandle:
	.space	4
	.type	cmdline, %object
	.size	cmdline, 1024
cmdline:
	.space	1024
	.type	extra_cmd, %object
	.size	extra_cmd, 4
extra_cmd:
	.space	4
	.type	g_allow_B_before_P, %object
	.size	g_allow_B_before_P, 1
g_allow_B_before_P:
	.space	1
	.type	g_not_allow_H264FullPictureRepair_flag, %object
	.size	g_not_allow_H264FullPictureRepair_flag, 1
g_not_allow_H264FullPictureRepair_flag:
	.space	1
	.type	g_apple_airplay_mirrorinig_flag, %object
	.size	g_apple_airplay_mirrorinig_flag, 1
g_apple_airplay_mirrorinig_flag:
	.space	1
	.space	1
	.type	g_event_report, %object
	.size	g_event_report, 4
g_event_report:
	.space	4
	.type	g_DSPState, %object
	.size	g_DSPState, 128
g_DSPState:
	.space	128
	.type	last_rec_pos_time.56816, %object
	.size	last_rec_pos_time.56816, 128
last_rec_pos_time.56816:
	.space	128
	.type	last_rec_pos_decparam_time.56817, %object
	.size	last_rec_pos_decparam_time.56817, 128
last_rec_pos_decparam_time.56817:
	.space	128
	.type	ChanPriTab.56766, %object
	.size	ChanPriTab.56766, 128
ChanPriTab.56766:
	.space	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 9600
g_VfmwChanStat:
	.space	9600
	.type	PrioArray.56206, %object
	.size	PrioArray.56206, 128
PrioArray.56206:
	.space	128
	.type	pOption, %object
	.size	pOption, 4
pOption:
	.space	4
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.space	128
	.type	Capability.56262, %object
	.size	Capability.56262, 148
Capability.56262:
	.space	148
	.type	PrioArray.56261, %object
	.size	PrioArray.56261, 128
PrioArray.56261:
	.space	128
	.type	g_EsBufValidFlag, %object
	.size	g_EsBufValidFlag, 128
g_EsBufValidFlag:
	.space	128
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.space	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 64
g_VfmwGlobalStat:
	.space	64
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 4
AcceleratorCharacter:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
