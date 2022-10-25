#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_drv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VDMDRV_AdjustErrRatio, %function
VDMDRV_AdjustErrRatio:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x22, .LC0
	add	x1, x22, x19, lsl 6
	ldr	w24, [x1, 8]
	cbz	w20, .L3
	cmp	w20, 2
	bls	.L15
	add	x0, x29, 80
	ldr	w2, [x1, 12]
	ldr	x1, [x1, 48]
	str	w2, [x29, 68]
	str	w19, [x0, -16]!
	str	x1, [x29, 72]
	bl	PostPro_GetErrRatio
	str	w0, [x21]
	ldr	x20, .LC3
	cbnz	w0, .L16
.L6:
	add	x19, x22, x19, lsl 6
	ldr	x1, [x20, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 507904
	ldr	w3, [x19, 12]
	sub	w4, w3, #8
	ldr	w2, [x1, 1388]
	cmp	w4, 1
	ccmp	w3, 5, 4, hi
	add	w2, w2, 1
	cset	w3, eq
	str	w2, [x1, 1388]
	cbz	w3, .L17
	str	w0, [x21]
.L18:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L15:
	ldr	x1, .LC2
	mov	w4, 100
	mov	w3, w20
	mov	w2, w24
	str	w4, [x21]
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3:
	str	wzr, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L17:
	ldr	w0, [x21]
	mov	w1, 100
	cmp	w0, w1
	csel	w0, w0, w1, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	str	w0, [x21]
	b	.L18
	.p2align 3
.L16:
	ldr	x3, [x20, w24, sxtw 3]
	mov	w4, w0
	ldr	x1, .LC5
	mov	w2, w24
	add	x3, x3, 507904
	mov	w0, 1
	ldr	w3, [x3, 1388]
	bl	dprint_vfmw
	b	.L6
	.size	VDMDRV_AdjustErrRatio, .-VDMDRV_AdjustErrRatio
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC3:
	.xword	s_pstVfmwChan
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_Init
	.type	VDMDRV_Init, %function
VDMDRV_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	sxtw	x19, w0
	mov	x0, x30
	lsl	x20, x19, 6
	bl	_mcount
	ldr	x21, .LC7
	ldr	x0, .LC6
	mov	x2, 64
	mov	w1, 0
	add	x19, x21, x19, lsl 2
	ldr	x3, [x0, 96]
	add	x0, x21, x20
	blr	x3
	str	wzr, [x19, 64]
	ldr	x0, .LC8
	str	wzr, [x19, 72]
	add	x20, x0, x20
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMDRV_Init, .-VDMDRV_Init
	.align	3
.LC6:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_Reset
	.type	VDMDRV_Reset, %function
VDMDRV_Reset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sbfiz	x19, x19, 6, 32
	bl	_mcount
	ldr	x3, .LC9
	mov	x2, 64
	ldr	x0, .LC10
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, x19
	blr	x3
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_Reset, .-VDMDRV_Reset
	.align	3
.LC9:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetPriority
	.type	VDMDRV_SetPriority, %function
VDMDRV_SetPriority:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x6, .LC13
	mov	w4, 0
	mov	w3, 0
	add	x5, x6, 208
	.p2align 2
.L28:
	mov	x0, 0
	mov	w2, 0
	.p2align 2
.L23:
	ldr	w1, [x19, x0, lsl 2]
	cmp	w1, w2
	ble	.L22
	mov	w3, w0
	mov	w2, w1
.L22:
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L23
	cmp	w2, wzr
	ble	.L33
	str	w3, [x5], 4
	add	w4, w4, 1
	str	wzr, [x19, w3, sxtw 2]
	cmp	w4, 32
	bne	.L28
.L21:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L33:
	cmp	w4, 31
	add	x1, x6, 80
	mov	w2, -1
	bgt	.L21
	.p2align 2
.L29:
	add	x0, x1, x4, sxtw 2
	add	w4, w4, 1
	cmp	w4, 32
	str	w2, [x0, 128]
	bne	.L29
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_SetPriority, .-VDMDRV_SetPriority
	.align	3
.LC13:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AdjustPriorityAfterDec
	.type	VDMDRV_AdjustPriorityAfterDec, %function
VDMDRV_AdjustPriorityAfterDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x8, .LC14
	ldr	w0, [x8, 208]
	cmp	w19, w0
	beq	.L44
	add	x2, x8, 212
	mov	x0, 1
	b	.L40
	.p2align 3
.L36:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L44
.L40:
	ldr	w3, [x2]
	mov	w1, w0
	add	x2, x2, 4
	cmp	w3, w19
	bne	.L36
	cmp	w0, 30
	bgt	.L34
	add	x3, x0, 1
	lsl	x3, x3, 2
.L35:
	add	x2, x8, 208
	add	x7, x2, x3
	ldr	w3, [x2, x3]
	tbz	w3, #31, .L41
	b	.L34
	.p2align 3
.L43:
	add	x7, x2, x3, lsl 2
	ldr	w3, [x2, x3, lsl 2]
	tbnz	w3, #31, .L34
.L41:
	add	x4, x8, 80
	ldr	w5, [x2, x0, lsl 2]
	add	w1, w1, 1
	ldr	w6, [x4, w3, sxtw 2]
	ldr	w4, [x4, w5, sxtw 2]
	cmp	w6, w4
	blt	.L42
	str	w3, [x2, x0, lsl 2]
	str	w5, [x7]
.L42:
	cmp	w1, 30
	sxtw	x0, w1
	add	x3, x0, 1
	ble	.L43
.L34:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L44:
	mov	x3, 4
	mov	x0, 0
	mov	w1, 0
	b	.L35
	.size	VDMDRV_AdjustPriorityAfterDec, .-VDMDRV_AdjustPriorityAfterDec
	.align	3
.LC14:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_PrepareSleep
	.type	VDMDRV_PrepareSleep, %function
VDMDRV_PrepareSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC17
	sxtw	x0, w19
	add	x2, x1, x0, lsl 2
	ldr	w3, [x2, 64]
	cbnz	w3, .L50
	lsl	x0, x0, 6
	ldr	w0, [x1, x0]
	cbz	w0, .L51
	mov	w1, 1
	mov	w0, 0
	str	w1, [x2, 64]
.L48:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L51:
	mov	w1, 2
	str	w1, [x2, 64]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L50:
	mov	w0, -1
	b	.L48
	.size	VDMDRV_PrepareSleep, .-VDMDRV_PrepareSleep
	.align	3
.LC17:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetSleepStage
	.type	VDMDRV_GetSleepStage, %function
VDMDRV_GetSleepStage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC18
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 64]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_GetSleepStage, .-VDMDRV_GetSleepStage
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ForceSleep
	.type	VDMDRV_ForceSleep, %function
VDMDRV_ForceSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC19
	sxtw	x0, w19
	add	x19, x3, x0, lsl 2
	ldr	w1, [x19, 64]
	cmp	w1, 2
	beq	.L54
	ldr	x4, .LC20
	add	x0, x3, x0, lsl 6
	mov	x2, 64
	mov	w1, 0
	ldr	x3, [x4, 96]
	blr	x3
	mov	w0, 2
	str	w0, [x19, 64]
.L54:
	ldr	x1, .LC22
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ForceSleep, .-VDMDRV_ForceSleep
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ExitSleep
	.type	VDMDRV_ExitSleep, %function
VDMDRV_ExitSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC23
	add	x19, x0, x19, sxtw 2
	str	wzr, [x19, 64]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ExitSleep, .-VDMDRV_ExitSleep
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_StartRepair
	.type	VDMDRV_StartRepair, %function
VDMDRV_StartRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	mov	w0, 8
	bl	VCTRL_RecordPosTime
	ldr	x0, .LC24
	ldr	x3, [x0, 232]
	cbz	x3, .L60
	mov	x1, x21
	mov	w0, w19
	sbfiz	x19, x19, 6, 32
	blr	x3
	ldr	x0, .LC27
	str	w20, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L60:
	ldr	x1, .LC26
	mov	w2, 296
	mov	w0, 0
	sbfiz	x19, x19, 6, 32
	bl	dprint_vfmw
	ldr	x0, .LC27
	str	w20, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMDRV_StartRepair, .-VDMDRV_StartRepair
	.align	3
.LC24:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC27:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_StartDec
	.type	VDMDRV_StartDec, %function
VDMDRV_StartDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w0, 8
	bl	VCTRL_RecordPosTime
	ldr	x0, .LC28
	ldr	x2, [x0, 240]
	cbz	x2, .L63
	mov	x1, x20
	mov	w0, w19
	sbfiz	x19, x19, 6, 32
	blr	x2
	ldr	x0, .LC30
	mov	w1, 1
	str	w1, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	ldr	x1, .LC29
	mov	w2, 305
	mov	w0, 0
	sbfiz	x19, x19, 6, 32
	bl	dprint_vfmw
	ldr	x0, .LC30
	mov	w1, 1
	str	w1, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_StartDec, .-VDMDRV_StartDec
	.align	3
.LC28:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC29:
	.xword	.LC25
	.align	3
.LC30:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsChanDec
	.type	VDMDRV_IsChanDec, %function
VDMDRV_IsChanDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC31
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 336]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_IsChanDec, .-VDMDRV_IsChanDec
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetChanIsDec
	.type	VDMDRV_SetChanIsDec, %function
VDMDRV_SetChanIsDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	w20, w20, 1
	ldr	x1, .LC32
	mov	w0, w19
	add	x19, x1, x19, sxtw 2
	str	w20, [x19, 336]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_SetChanIsDec, .-VDMDRV_SetChanIsDec
	.align	3
.LC32:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ClearChanIsDec
	.type	VDMDRV_ClearChanIsDec, %function
VDMDRV_ClearChanIsDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC33
	add	x19, x0, x19, sxtw 2
	str	wzr, [x19, 336]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ClearChanIsDec, .-VDMDRV_ClearChanIsDec
	.align	3
.LC33:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ParamInit
	.type	VDMDRV_ParamInit, %function
VDMDRV_ParamInit:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC36
	mov	w3, 1
	add	x2, x0, 256
	.p2align 2
.L70:
	ldr	x1, [x0]
	add	x0, x0, 8
	cmp	x0, x2
	cbz	x1, .L69
	str	w3, [x1, 16]
.L69:
	bne	.L70
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_ParamInit, .-VDMDRV_ParamInit
	.align	3
.LC36:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ChnDecReady
	.type	VDMDRV_ChnDecReady, %function
VDMDRV_ChnDecReady:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	mov	w0, w19
	bl	VCTRL_IsChanActive
	cbnz	w0, .L79
	ldr	x0, .LC41
	add	x0, x0, x19, sxtw 2
	ldr	w20, [x0, 336]
	cbnz	w20, .L80
	mov	w0, w19
	str	xzr, [x21]
	bl	VCTRL_GetDecParam
	str	x0, [x21]
	cbz	x0, .L81
.L77:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L79:
	ldr	x2, .LC38
	mov	w3, w19
	ldr	x1, .LC40
	mov	w0, 22
	mov	w20, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L80:
	ldr	x1, .LC43
	mov	w2, w19
	mov	w0, 22
	mov	w20, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L81:
	ldr	x1, .LC45
	mov	w2, w19
	mov	w0, 22
	mov	w20, 1
	bl	dprint_vfmw
	b	.L77
	.size	VDMDRV_ChnDecReady, .-VDMDRV_ChnDecReady
	.align	3
.LC38:
	.xword	.LANCHOR1
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC41:
	.xword	.LANCHOR0
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC45:
	.xword	.LC44
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuvByProtocol
	.type	PostPro_CopyYuvByProtocol, %function
PostPro_CopyYuvByProtocol:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w19, w3
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	sub	w3, w19, #1
	cmp	w3, 11
	bls	.L89
.L88:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L89:
	ldr	x0, .LC46
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx85
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx85:
	.section	.rodata
	.align	0
	.align	2
.L85:
	.byte	(.L84 - .Lrtx85) / 4
	.byte	(.L86 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L88 - .Lrtx85) / 4
	.byte	(.L87 - .Lrtx85) / 4
	.byte	(.L87 - .Lrtx85) / 4
	.byte	(.L87 - .Lrtx85) / 4
	.text
	.p2align 3
.L87:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Vp6
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L86:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Mpeg4
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L84:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Vc1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_CopyYuvByProtocol, .-PostPro_CopyYuvByProtocol
	.align	3
.LC46:
	.xword	.L85
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetMb0QpInCurrPic
	.type	VDMDRV_GetMb0QpInCurrPic, %function
VDMDRV_GetMb0QpInCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC47
	lsl	x1, x0, 2
	ldr	x19, [sp, 16]
	sub	x0, x1, x0
	lsl	x1, x0, 4
	sub	x0, x1, x0
	ldp	x29, x30, [sp], 32
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 472]
	and	w0, w0, 31
	ret
	.size	VDMDRV_GetMb0QpInCurrPic, .-VDMDRV_GetMb0QpInCurrPic
	.align	3
.LC47:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetSwitchRounding
	.type	VDMDRV_GetSwitchRounding, %function
VDMDRV_GetSwitchRounding:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC48
	lsl	x1, x0, 2
	ldr	x19, [sp, 16]
	sub	x0, x1, x0
	lsl	x1, x0, 4
	sub	x0, x1, x0
	ldp	x29, x30, [sp], 32
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 476]
	and	w0, w0, 1
	ret
	.size	VDMDRV_GetSwitchRounding, .-VDMDRV_GetSwitchRounding
	.align	3
.LC48:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_MMUIntServeProc
	.type	VDMDRV_MMUIntServeProc, %function
VDMDRV_MMUIntServeProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC49
	mov	w0, 0
	ldr	x1, [x21, 24]
	blr	x1
	ldr	x19, .LC50
	ldr	x2, [x19, 208]
	cbz	x2, .L96
	mov	w1, w20
	mov	w0, 5
	blr	x2
	mov	w22, w0
	ldr	x2, [x19, 208]
	cbz	x2, .L111
	mov	w1, w20
	mov	w0, 6
	and	w23, w22, 15
	mov	w24, 0
	blr	x2
	mov	w25, w0
	ldr	x2, [x19, 208]
	cbz	x2, .L93
	mov	w1, w20
	mov	w0, 7
	blr	x2
	mov	w24, w0
.L93:
	cbz	w23, .L96
	tbnz	x22, 2, .L112
	tbnz	x22, 3, .L113
	.p2align 2
.L96:
	ldr	x1, [x19, 184]
	cbz	x1, .L99
	mov	w0, w20
	blr	x1
.L100:
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L99:
	ldr	x1, .LC55
	mov	w2, 1317
	mov	w0, 0
	bl	dprint_vfmw
	b	.L100
	.p2align 3
.L113:
	ldr	x1, .LC54
	mov	w3, w24
	mov	w2, w22
	mov	w0, 32
	bl	dprint_vfmw
	b	.L96
	.p2align 3
.L112:
	ldr	x1, .LC52
	mov	w3, w25
	mov	w2, w22
	mov	w0, 32
	bl	dprint_vfmw
	tbz	x22, 3, .L96
	b	.L113
.L111:
	and	w23, w0, 15
	mov	w25, 0
	mov	w24, 0
	b	.L93
	.size	VDMDRV_MMUIntServeProc, .-VDMDRV_MMUIntServeProc
	.align	3
.LC49:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC50:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC55:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsVdmInISR
	.type	VDMDRV_IsVdmInISR, %function
VDMDRV_IsVdmInISR:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_IsVdmInISR, .-VDMDRV_IsVdmInISR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetStateIdle
	.type	VDMDRV_SetStateIdle, %function
VDMDRV_SetStateIdle:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sbfiz	x19, x19, 6, 32
	bl	_mcount
	ldr	x0, .LC56
	str	wzr, [x0, x19]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_SetStateIdle, .-VDMDRV_SetStateIdle
	.align	3
.LC56:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsVdmIdle
	.type	VDMDRV_IsVdmIdle, %function
VDMDRV_IsVdmIdle:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sbfiz	x19, x19, 6, 32
	bl	_mcount
	ldr	x0, .LC57
	ldr	w0, [x0, x19]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_IsVdmIdle, .-VDMDRV_IsVdmIdle
	.align	3
.LC57:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetCurrChanID
	.type	VDMDRV_GetCurrChanID, %function
VDMDRV_GetCurrChanID:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sbfiz	x19, x19, 6, 32
	bl	_mcount
	ldr	x0, .LC58
	add	x19, x0, x19
	ldr	w0, [x19, 8]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_GetCurrChanID, .-VDMDRV_GetCurrChanID
	.align	3
.LC58:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_WaitVdmReadyIfNoIsr
	.type	VDMDRV_WaitVdmReadyIfNoIsr, %function
VDMDRV_WaitVdmReadyIfNoIsr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x20, .LC59
	b	.L120
	.p2align 3
.L122:
	add	w19, w19, 1
	cmp	w19, 400
	beq	.L121
.L120:
	ldr	x1, [x20, 256]
	mov	w0, w21
	cbz	x1, .L122
	blr	x1
	cbz	w0, .L122
.L121:
	cmp	w19, 399
	ldr	x21, [sp, 32]
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMDRV_WaitVdmReadyIfNoIsr, .-VDMDRV_WaitVdmReadyIfNoIsr
	.align	3
.LC59:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AvsFirstFldNeedRepair
	.type	VDMDRV_AvsFirstFldNeedRepair, %function
VDMDRV_AvsFirstFldNeedRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 6
	mov	w0, 0
	beq	.L131
.L128:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L131:
	ldrb	w1, [x21, 17]
	mov	w0, 0
	cmp	w1, 1
	bne	.L128
	lsl	x0, x20, 3
	ldr	x1, .LC60
	sub	x0, x0, x20
	lsl	x0, x0, 3
	sub	x0, x0, x20
	lsl	x0, x0, 1
	sub	x20, x0, x20
	add	x20, x1, x20, lsl 4
	ldr	w0, [x20, 692]
	cmp	w0, wzr
	cset	w0, gt
	b	.L128
	.size	VDMDRV_AvsFirstFldNeedRepair, .-VDMDRV_AvsFirstFldNeedRepair
	.align	3
.LC60:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AvsSecondFldNeedRepair
	.type	VDMDRV_AvsSecondFldNeedRepair, %function
VDMDRV_AvsSecondFldNeedRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 6
	mov	w0, 0
	beq	.L136
.L133:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L136:
	ldrb	w1, [x21, 17]
	mov	w0, 0
	cmp	w1, 1
	bne	.L133
	lsl	x0, x20, 3
	ldr	x1, .LC61
	sub	x0, x0, x20
	lsl	x0, x0, 3
	sub	x0, x0, x20
	lsl	x0, x0, 1
	sub	x20, x0, x20
	add	x20, x1, x20, lsl 4
	ldr	w0, [x20, 1564]
	cmp	w0, wzr
	cset	w0, gt
	b	.L133
	.size	VDMDRV_AvsSecondFldNeedRepair, .-VDMDRV_AvsSecondFldNeedRepair
	.align	3
.LC61:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsMpeg4NvopCopy
	.type	VDMDRV_IsMpeg4NvopCopy, %function
VDMDRV_IsMpeg4NvopCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L141
	cmp	w20, 2
	mov	w0, 0
	beq	.L142
.L139:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L142:
	ldrb	w0, [x19, 166]
	ldp	x19, x20, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L141:
	ldr	x1, .LC63
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L139
	.size	VDMDRV_IsMpeg4NvopCopy, .-VDMDRV_IsMpeg4NvopCopy
	.align	3
.LC63:
	.xword	.LC62
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsVc1SkpicCopy
	.type	VDMDRV_IsVc1SkpicCopy, %function
VDMDRV_IsVc1SkpicCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L147
	cmp	w20, 1
	mov	w0, 0
	beq	.L148
.L145:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L148:
	ldrb	w0, [x19, 1]
	ldp	x19, x20, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L147:
	ldr	x1, .LC65
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L145
	.size	VDMDRV_IsVc1SkpicCopy, .-VDMDRV_IsVc1SkpicCopy
	.align	3
.LC65:
	.xword	.LC64
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsVp6NvopCopy
	.type	VDMDRV_IsVp6NvopCopy, %function
VDMDRV_IsVp6NvopCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L153
	sub	w19, w19, #10
	mov	w0, 0
	cmp	w19, 2
	bhi	.L151
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	cset	w0, eq
.L151:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L153:
	ldr	x1, .LC67
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L151
	.size	VDMDRV_IsVp6NvopCopy, .-VDMDRV_IsVp6NvopCopy
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsVp9RptFrmCopy
	.type	VDMDRV_IsVp9RptFrmCopy, %function
VDMDRV_IsVp9RptFrmCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L158
	cmp	w20, 17
	mov	w0, 0
	beq	.L159
.L156:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L159:
	add	x19, x19, 262144
	ldrb	w0, [x19, 1028]
	ldp	x19, x20, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L158:
	ldr	x1, .LC69
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L156
	.size	VDMDRV_IsVp9RptFrmCopy, .-VDMDRV_IsVp9RptFrmCopy
	.align	3
.LC69:
	.xword	.LC68
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsCopy
	.type	VDMDRV_IsCopy, %function
VDMDRV_IsCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L168
	sub	w0, w19, #1
	cmp	w0, 11
	bls	.L169
.L167:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L169:
	ldr	x1, .LC72
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx164
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx164:
	.section	.rodata
	.align	0
	.align	2
.L164:
	.byte	(.L166 - .Lrtx164) / 4
	.byte	(.L165 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L167 - .Lrtx164) / 4
	.byte	(.L166 - .Lrtx164) / 4
	.byte	(.L166 - .Lrtx164) / 4
	.byte	(.L166 - .Lrtx164) / 4
	.text
	.p2align 3
.L166:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	cset	w0, eq
.L162:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L165:
	ldrb	w0, [x20, 166]
	ldp	x19, x20, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L168:
	ldr	x1, .LC71
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L162
	.size	VDMDRV_IsCopy, .-VDMDRV_IsCopy
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC72:
	.xword	.L164
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_DoBeforeDec
	.type	VDMDRV_DoBeforeDec, %function
VDMDRV_DoBeforeDec:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	mov	w23, w1
	mov	x21, x2
	bl	_mcount
	mov	x26, 0
	ldr	x0, .LC73
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L171
	ldr	x3, .LC74
	add	x0, x29, 112
	mov	x2, 188
	mov	w1, 0
	mov	x26, x0
	ldr	x3, [x3, 96]
	blr	x3
.L171:
	ldr	x0, [x21]
	cbz	x0, .L187
	mov	w0, w23
	sxtw	x24, w22
	bl	VCTRL_GetVidStd
	ldr	x20, .LC77
	ldr	x1, .LC78
	add	x25, x20, x24, lsl 6
	ldr	x1, [x1]
	str	w0, [x25, 12]
	cbz	x1, .L174
	ldr	x2, [x21]
	stp	w23, w0, [x29, 96]
	str	x2, [x29, 104]
	add	x0, x29, 96
	blr	x1
	cmp	w0, 1
	mov	w19, w0
	beq	.L173
	ldr	w0, [x25, 12]
.L174:
	ldr	x1, [x21]
	lsl	x27, x24, 6
	add	x25, x20, x27
	add	x28, x25, 4
	bl	VDMDRV_IsCopy
	mov	w19, w0
	cbz	w0, .L176
	ldr	w3, [x25, 12]
	mov	x2, x26
	mov	x0, x21
	mov	w1, w22
	bl	PostPro_CopyYuvByProtocol
	mov	w19, w0
	cbz	w0, .L188
	mov	w19, 0
.L173:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L176:
	ldr	w0, [x25, 12]
	ldr	x1, [x21]
	bl	VCTRL_IsSedOnlyMode
	uxtb	w0, w0
	cbz	w0, .L189
	mov	w0, 1
	str	w0, [x25, 56]
.L178:
	ldr	x0, .LC81
	ldr	x4, [x0, 248]
	cbz	x4, .L180
	lsl	x25, x24, 6
	ldr	x1, [x21]
	add	x21, x20, x25
	mov	x3, x26
	mov	w2, w22
	ldr	w0, [x21, 12]
	blr	x4
	cbz	w0, .L190
.L180:
	ldr	x1, .LC83
	mov	w0, 0
	add	x24, x20, x24, lsl 6
	add	x20, x20, x23, sxtw 2
	bl	dprint_vfmw
	mov	x2, x28
	mov	w0, w22
	mov	w1, 2
	bl	VDMDRV_AdjustErrRatio
	ldr	w1, [x24, 4]
	mov	w3, w22
	mov	w0, w23
	mov	x2, 0
	bl	VCTRL_VdmPostProc
	ldr	x3, .LC74
	mov	x2, 64
	mov	w1, 0
	mov	x0, x24
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x20, 336]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L189:
	str	wzr, [x25, 56]
	b	.L178
	.p2align 3
.L190:
	mov	x1, x26
	mov	w0, w22
	sxtw	x24, w23
	add	w22, w22, 1
	bl	VDMDRV_StartDec
	mov	w19, 0
	ldr	x0, .LC74
	ldr	x0, [x0]
	blr	x0
	mov	w1, w0
	ldr	x3, .LC79
	add	x2, x20, x24, lsl 2
	mov	w0, w23
	str	w1, [x21, 20]
	add	x25, x3, x25
	str	w22, [x2, 336]
	str	w1, [x25, 4]
	bl	VDMDRV_AdjustPriorityAfterDec
	add	x2, x20, 2392
	ldr	x3, .LC80
	add	x2, x2, x24, lsl 2
	mov	w0, w23
	mov	w4, 569
	mov	w1, 5
	bl	RecordPOS
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L188:
	mov	w0, w22
	mov	x2, x28
	mov	w1, 0
	sxtw	x21, w23
	bl	VDMDRV_AdjustErrRatio
	mov	x2, x26
	mov	w1, w22
	mov	w0, 2
	add	w22, w22, 1
	bl	VDMDRV_StartRepair
	ldr	x0, .LC74
	ldr	x0, [x0]
	blr	x0
	mov	w1, w0
	ldr	x0, .LC79
	add	x2, x20, x21, lsl 2
	str	w1, [x25, 20]
	add	x27, x0, x27
	mov	w0, w23
	str	w22, [x2, 336]
	str	w1, [x27, 4]
	bl	VDMDRV_AdjustPriorityAfterDec
	add	x2, x20, 2392
	ldr	x3, .LC80
	add	x2, x2, x21, lsl 2
	mov	w0, w23
	mov	w4, 535
	mov	w1, 7
	bl	RecordPOS
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L187:
	ldr	x1, .LC76
	mov	w2, w23
	mov	w0, 22
	mov	w19, 1
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.size	VDMDRV_DoBeforeDec, .-VDMDRV_DoBeforeDec
	.align	3
.LC73:
	.xword	g_HalDisable
	.align	3
.LC74:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	.LANCHOR0
	.align	3
.LC78:
	.xword	AcceleratorCharacter
	.align	3
.LC79:
	.xword	g_VfmwGlobalStat
	.align	3
.LC80:
	.xword	.LANCHOR2
	.align	3
.LC81:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ActivateVDH
	.type	VDMDRV_ActivateVDH, %function
VDMDRV_ActivateVDH:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w22, w0
	mov	x0, x30
	sbfiz	x20, x22, 6, 32
	bl	_mcount
	ldr	x25, .LC86
	ldr	x24, .LC85
	mov	w0, 5
	add	x21, x20, 48
	ldr	x1, [x25, 24]
	add	x21, x24, x21
	blr	x1
	ldr	w0, [x24, 208]
	tbnz	w0, #31, .L192
	add	x19, x24, 212
	add	x23, x24, 336
	add	x20, x24, x20
	b	.L193
	.p2align 3
.L196:
	cmp	x19, x23
	beq	.L192
	ldr	w0, [x19], 4
	tbnz	w0, #31, .L192
.L193:
	mov	w1, w0
	str	w0, [x20, 8]
	mov	x2, x21
	mov	w0, w22
	bl	VDMDRV_ChnDecReady
	cbnz	w0, .L196
	ldr	w1, [x20, 8]
	mov	x2, x21
	mov	w0, w22
	bl	VDMDRV_DoBeforeDec
	cbnz	w0, .L196
.L192:
	ldr	x1, [x25, 32]
	mov	w0, 5
	blr	x1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMDRV_ActivateVDH, .-VDMDRV_ActivateVDH
	.align	3
.LC85:
	.xword	.LANCHOR0
	.align	3
.LC86:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AfterDec
	.type	VDMDRV_AfterDec, %function
VDMDRV_AfterDec:
	stp	x29, x30, [sp, -464]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w24, w0
	mov	x0, x30
	uxtb	w25, w1
	bl	_mcount
	ldr	x22, .LC88
	mov	x2, 160
	mov	w1, 0
	add	x0, x29, 112
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x0, .LC89
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L199
	add	x19, x29, 272
	ldr	x3, [x22, 96]
	mov	x2, 188
	mov	w1, 0
	mov	x0, x19
	blr	x3
	str	x19, [x29, 256]
.L199:
	ldr	x3, [x22, 96]
	add	x28, x29, 116
	mov	x2, 136
	mov	w1, 0
	mov	x0, x28
	sxtw	x21, w24
	lsl	x23, x21, 6
	blr	x3
	ldr	x20, .LC91
	ldr	x26, .LC90
	mov	w0, 2
	add	x19, x20, x23
	ldr	x1, .LC93
	ldr	w2, [x20, x23]
	add	x27, x19, 4
	strb	w25, [x29, 264]
	ldrsw	x3, [x19, 8]
	ldr	w4, [x19, 4]
	ldr	x3, [x26, x3, lsl 3]
	ldr	w3, [x3, 1272]
	str	w3, [x29, 112]
	ldr	w3, [x19, 28]
	bl	dprint_vfmw
	ldr	w3, [x20, x23]
	cmp	w3, 2
	beq	.L201
	cmp	w3, 3
	beq	.L202
	cmp	w3, 1
	beq	.L241
	ldr	x1, .LC101
	mov	w4, w25
	ldr	w2, [x19, 8]
	mov	w0, 0
	bl	dprint_vfmw
	ldrsw	x0, [x19, 8]
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 336]
.L198:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 464
	ret
	.p2align 3
.L241:
	ldr	w23, [x19, 28]
	cmp	w23, 1
	beq	.L242
	mov	w1, 3
	mov	x2, x27
	mov	w0, w24
	bl	VDMDRV_AdjustErrRatio
	ldr	w1, [x19, 4]
	cbz	w1, .L205
	ldr	x0, .LC96
	ldr	x4, [x0]
	cbz	x4, .L205
	ldr	w0, [x19, 8]
	mov	w3, 4
	str	w1, [x29, 104]
	add	x2, x29, 104
	mov	w1, 114
	blr	x4
.L205:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L243
.L206:
	add	x19, x20, x21, lsl 6
	ldr	w0, [x19, 8]
	ldr	x1, [x26, w0, sxtw 3]
	add	x1, x1, 507904
	ldrsb	w1, [x1, 1344]
	cbnz	w1, .L244
	ldr	w1, [x19, 4]
.L217:
	ldr	w2, [x29, 112]
	cmp	w2, 1
	bne	.L209
	add	x21, x20, x21, lsl 6
	mov	w3, w24
	ldr	w2, [x21, 44]
	cmp	w2, 2
	add	x2, x29, 116
	beq	.L245
.L239:
	bl	VCTRL_VdmPostProc
	ldr	w0, [x21, 8]
	bl	VCTRL_ClearDecparam
	mov	x2, 64
	mov	w1, 0
	mov	x0, x21
	ldrsw	x3, [x21, 8]
	ldr	x4, [x22, 96]
	b	.L238
	.p2align 3
.L202:
	ldp	w1, w0, [x19, 4]
	mov	w3, w24
	mov	x2, x28
	str	wzr, [x19, 28]
	bl	VCTRL_VdmPostProc
	ldr	w0, [x19, 8]
	bl	VCTRL_ClearDecparam
	ldrsw	x3, [x19, 8]
	mov	x2, 64
	ldr	x4, [x22, 96]
	mov	w1, 0
	mov	x0, x19
.L238:
	add	x20, x20, x3, lsl 2
	str	wzr, [x20, 336]
	blr	x4
	mov	w0, w24
	bl	VDMDRV_ActivateVDH
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 464
	ret
	.p2align 3
.L201:
	ldr	w0, [x19, 12]
	str	wzr, [x19, 28]
	cmp	w0, 6
	ldr	x1, [x19, 48]
	beq	.L246
.L214:
	bl	VDMDRV_IsCopy
	cbnz	w0, .L247
	add	x21, x20, x21, lsl 6
	mov	w3, w24
	add	x2, x29, 116
	ldp	w1, w0, [x21, 4]
	b	.L239
	.p2align 3
.L242:
	ldr	x1, [x19, 48]
	mov	w2, w24
	ldr	w0, [x19, 12]
	bl	PostPro_SetFullRepair
	mov	x2, x27
	mov	w1, w23
	mov	w0, w24
	bl	VDMDRV_AdjustErrRatio
	str	wzr, [x19, 28]
	ldrb	w2, [x29, 264]
	mov	w0, 0
	ldr	x1, .LC95
	bl	dprint_vfmw
	b	.L205
	.p2align 3
.L246:
	ldrb	w2, [x1, 17]
	cmp	w2, 1
	bne	.L214
	lsl	x3, x21, 3
	sub	x3, x3, x21
	lsl	x3, x3, 3
	sub	x3, x3, x21
	lsl	x3, x3, 1
	sub	x3, x3, x21
	add	x3, x20, x3, lsl 4
	ldr	w3, [x3, 1564]
	cmp	w3, wzr
	ble	.L214
	ldr	x3, .LC97
	ldr	x5, [x3, 272]
	cbz	x5, .L216
	ldr	x4, [x29, 256]
	mov	w3, w24
	blr	x5
	cbnz	w0, .L216
	ldr	x2, [x29, 256]
	mov	w1, w24
	mov	w0, 3
	bl	VDMDRV_StartRepair
	ldr	x2, .LC99
	mov	w4, 765
	ldr	x3, .LC98
	mov	w1, 7
	add	x2, x23, x2
	ldr	w0, [x19, 8]
	add	x3, x3, 56
	add	x2, x2, 4
	bl	RecordPOS
	b	.L198
	.p2align 3
.L244:
	ldr	x1, [x19, 48]
	ldr	w0, [x19, 12]
	bl	PostPro_GetRepairStratage
	cmp	w0, 1
	ldr	w1, [x19, 4]
	cset	w2, eq
	cmp	w1, wzr
	cset	w0, eq
	orr	w2, w2, w0
	cbnz	w2, .L248
	ldr	w0, [x19, 12]
	ldr	x1, [x19, 48]
	mov	w19, 2
	cmp	w0, 6
	beq	.L249
.L212:
	ldr	x3, .LC97
	ldr	x5, [x3, 272]
	cbz	x5, .L216
	ldr	x4, [x29, 256]
	mov	w3, w24
	blr	x5
	cbz	w0, .L250
.L216:
	lsl	x21, x21, 6
	mov	x2, x27
	add	x19, x20, x21
	mov	w0, w24
	mov	w1, 2
	bl	VDMDRV_AdjustErrRatio
	ldp	w1, w0, [x19, 4]
	mov	w3, w24
	add	x2, x29, 116
	bl	VCTRL_VdmPostProc
	ldr	w0, [x19, 8]
	bl	VCTRL_ClearDecparam
	str	wzr, [x20, x21]
	ldrsw	x0, [x19, 8]
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 336]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 464
	ret
	.p2align 3
.L209:
	mov	w3, w24
	add	x2, x29, 116
	add	x21, x20, x21, lsl 6
	b	.L239
	.p2align 3
.L247:
	mov	x2, x27
	mov	w0, w24
	mov	w1, 0
	add	x21, x20, x21, lsl 6
	bl	VDMDRV_AdjustErrRatio
	mov	w3, w24
	add	x2, x29, 116
	ldp	w1, w0, [x21, 4]
	b	.L239
	.p2align 3
.L243:
	mov	x2, x27
	mov	w1, 0
	mov	w0, w24
	bl	VDMDRV_AdjustErrRatio
	b	.L206
	.p2align 3
.L245:
	bl	VCTRL_VdmPostProc
	b	.L198
	.p2align 3
.L249:
	ldrb	w3, [x1, 17]
	cmp	w3, 1
	bne	.L212
	lsl	x2, x21, 3
	sub	x2, x2, x21
	lsl	x2, x2, 3
	sub	x2, x2, x21
	lsl	x2, x2, 1
	sub	x2, x2, x21
	add	x2, x20, x2, lsl 4
	ldr	w3, [x2, 1564]
	cmp	w3, wzr
	mov	w3, 3
	cset	w2, gt
	csel	w19, w19, w3, le
	b	.L212
	.p2align 3
.L250:
	ldr	x2, [x29, 256]
	mov	w1, w24
	mov	w0, w19
	bl	VDMDRV_StartRepair
	lsl	x2, x21, 6
	ldr	x0, .LC99
	add	x20, x20, x2
	ldr	x3, .LC98
	add	x2, x2, x0
	mov	w4, 734
	mov	w1, 7
	add	x3, x3, 24
	ldr	w0, [x20, 8]
	add	x2, x2, 4
	bl	RecordPOS
	b	.L198
.L248:
	ldr	w0, [x19, 8]
	b	.L217
	.size	VDMDRV_AfterDec, .-VDMDRV_AfterDec
	.align	3
.LC88:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC89:
	.xword	g_HalDisable
	.align	3
.LC90:
	.xword	s_pstVfmwChan
	.align	3
.LC91:
	.xword	.LANCHOR0
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC96:
	.xword	g_event_report
	.align	3
.LC97:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC98:
	.xword	.LANCHOR2
	.align	3
.LC99:
	.xword	g_VfmwGlobalStat
	.align	3
.LC101:
	.xword	.LC100
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_CheckDevice
	.type	VDMDRV_CheckDevice, %function
VDMDRV_CheckDevice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	lsl	x22, x19, 6
	mov	x21, x19
	bl	_mcount
	ldr	x20, .LC102
	add	x23, x20, x22
	ldr	w0, [x23, 8]
	bl	VCTRL_GetDecParam
	cbz	x0, .L281
.L252:
	lsl	x0, x19, 6
	add	x22, x20, x0
	ldr	w0, [x20, x0]
	cbnz	w0, .L282
.L253:
	add	x19, x20, x19, lsl 2
	mov	w0, 0
	ldr	w1, [x19, 64]
	cbz	w1, .L275
	cmp	w1, 1
	beq	.L283
.L258:
	mov	w0, 1
.L275:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L282:
	ldr	x0, .LC109
	ldr	x0, [x0]
	blr	x0
	str	w0, [x22, 24]
	ldr	w1, [x22, 20]
	cmp	w0, w1
	bcc	.L256
	sub	w3, w0, w1
	cmp	w1, wzr
	ccmp	w3, wzr, 1, ne
	blt	.L256
	cmp	w3, 1000
	bls	.L258
	ldr	x1, .LC111
	mov	w0, 1
	ldr	w2, [x22, 8]
	bl	dprint_vfmw
	ldr	x0, .LC112
	ldr	x4, [x0]
	cbz	x4, .L259
	ldr	w0, [x22, 8]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 101
	blr	x4
.L259:
	ldr	x0, .LC113
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L260
	mov	w1, w21
	mov	w0, 1
	bl	VDH_Reset_Module
.L261:
	add	x0, x20, x19, lsl 6
	mov	w2, 1
	ldr	w1, [x0, 36]
	str	w2, [x0, 28]
	cmp	w1, w2
	bne	.L263
	str	wzr, [x0, 36]
.L264:
	lsl	x19, x19, 6
	mov	w0, 0
	add	x1, x20, x19
	str	wzr, [x20, x19]
	ldrsw	x19, [x1, 8]
	str	wzr, [x1, 28]
	add	x19, x20, x19, lsl 2
	str	wzr, [x19, 336]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L256:
	str	w0, [x22, 20]
	mov	w0, 1
	b	.L275
	.p2align 3
.L283:
	mov	w2, 2
	str	w2, [x19, 64]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L281:
	ldr	w3, [x20, x22]
	cbz	w3, .L253
	ldr	x0, .LC103
	ldr	x1, [x0, 264]
	cbz	x1, .L254
	mov	w0, w19
	blr	x1
	ldr	w3, [x20, x22]
	cbnz	w0, .L284
.L254:
	lsl	x23, x19, 6
	ldr	x1, .LC107
	add	x22, x20, x23
	mov	w0, 1
	ldr	w2, [x22, 8]
	bl	dprint_vfmw
	str	wzr, [x22, 36]
	ldr	x0, .LC108
	mov	w1, 903
	ldr	w2, [x20, x23]
	add	x0, x0, 88
	bl	DBG_AddTrace
	ldr	x3, .LC109
	mov	x2, 64
	mov	w1, 0
	mov	x0, x22
	ldr	x3, [x3, 96]
	blr	x3
	ldrsw	x0, [x22, 8]
	add	x0, x20, x0, lsl 2
	str	wzr, [x0, 336]
	b	.L252
	.p2align 3
.L263:
	mov	w1, 0
	mov	w0, w21
	bl	VDMDRV_AfterDec
	b	.L264
	.p2align 3
.L260:
	ldr	x0, .LC103
	ldr	x1, [x0, 152]
	cbz	x1, .L262
	mov	w0, w21
	blr	x1
	b	.L261
	.p2align 3
.L284:
	ldr	x1, .LC105
	mov	w0, 1
	ldr	w2, [x23, 8]
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x23, 36]
	b	.L252
.L262:
	ldr	x1, .LC114
	mov	w2, 935
	mov	w0, 0
	bl	dprint_vfmw
	b	.L261
	.size	VDMDRV_CheckDevice, .-VDMDRV_CheckDevice
	.align	3
.LC102:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC105:
	.xword	.LC104
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	.LANCHOR2
	.align	3
.LC109:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC112:
	.xword	g_event_report
	.align	3
.LC113:
	.xword	g_HalDisable
	.align	3
.LC114:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_WakeUpVdm
	.type	VDMDRV_WakeUpVdm, %function
VDMDRV_WakeUpVdm:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_CheckDevice
	cbz	w0, .L287
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L287:
	bl	VDMDRV_ActivateVDH
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_WakeUpVdm, .-VDMDRV_WakeUpVdm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsrProcess
	.type	VDMDRV_IsrProcess, %function
VDMDRV_IsrProcess:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L289
	ldr	x2, .LC115
	mov	w3, w19
	ldr	x1, .LC117
	mov	w4, 0
	add	x2, x2, 112
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L289:
	mov	w0, 9
	sxtw	x20, w19
	bl	VCTRL_RecordPosTime
	ldr	x23, .LC118
	mov	w0, 0
	ldr	x1, [x23, 24]
	blr	x1
	ldr	x21, .LC119
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	tbnz	w0, #31, .L335
	ldr	x1, .LC120
	ldr	x0, [x1, w0, sxtw 3]
	cbz	x0, .L335
	ldr	x22, .LC121
	ldr	w25, [x0, 1272]
	ldr	x2, [x22, 312]
	cbz	x2, .L336
.L376:
	mov	w1, w19
	mov	w0, 2
	blr	x2
	mov	w24, w0
	ldr	x2, [x22, 312]
	cbz	x2, .L337
	mov	w1, w19
	mov	w0, 1
	mov	w27, 0
	blr	x2
	mov	w26, w0
	ldr	x2, [x22, 312]
	cbz	x2, .L292
	mov	w1, w19
	mov	w0, 3
	blr	x2
	mov	w27, w0
.L292:
	ldr	x2, [x22, 320]
	cbz	x2, .L293
	mov	w1, w19
	mov	w0, 2
	blr	x2
	cmp	w24, 1
	beq	.L294
	cmp	w25, 1
	ccmp	w0, 1, 0, eq
	bne	.L333
.L294:
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	tbnz	w0, #31, .L306
	ldr	x1, .LC120
	ldr	x0, [x1, w0, sxtw 3]
	cbz	x0, .L306
	ldr	x2, [x22, 320]
	ldr	w24, [x0, 1272]
	cbz	x2, .L339
	mov	w1, w19
	mov	w0, 1
	blr	x2
	mov	w25, w0
.L304:
	ldr	x2, [x22, 312]
	cbz	x2, .L305
	mov	w1, w19
	mov	w0, 1
	blr	x2
	cmp	w24, 1
	beq	.L369
.L306:
	mov	w24, 1
.L303:
	ldr	x1, [x22, 288]
	cbz	x1, .L310
	mov	w0, w19
	blr	x1
.L311:
	ldr	x1, [x22, 176]
	cbz	x1, .L312
	mov	w0, w19
	blr	x1
.L313:
	lsl	x22, x20, 6
	ldr	x3, .LC115
	add	x0, x21, x22
	add	x2, x21, 2520
	mov	w4, 1245
	add	x3, x3, 136
	mov	w1, 6
	ldr	w0, [x0, 8]
	add	x2, x2, x0, sxtw 2
	bl	RecordPOS
	ldr	x0, [x23]
	blr	x0
	ldr	x4, .LC124
	add	x3, x4, x22
	ldr	w1, [x3, 4]
	cbz	w1, .L315
	ldr	w5, [x4, x22]
	add	w2, w5, 49152
	add	w2, w2, 848
	cmp	w1, w2
	bhi	.L316
	ldr	w2, [x3, 8]
.L317:
	lsl	x3, x20, 2
	sub	w1, w0, w1
	sub	w0, w0, w5
	sub	x5, x3, x20
	lsl	x3, x5, 4
	lsl	x7, x20, 6
	sub	x3, x3, x5
	add	w1, w1, w2
	add	x2, x4, x7
	cmp	w0, 999
	add	x3, x21, x3, lsl 2
	ldp	w5, w6, [x2, 28]
	ldr	w3, [x3, 488]
	add	w5, w5, 1
	stp	wzr, w1, [x2, 4]
	add	w6, w6, w3, lsr 10
	stp	w5, w6, [x2, 28]
	bls	.L315
	add	x7, x21, x7
	ldr	w3, [x7, 16]
	cbnz	w3, .L319
	ldr	w7, [x2, 12]
.L320:
	lsl	w2, w1, 6
	lsl	w3, w7, 6
	sub	w2, w2, w1
	sub	w3, w3, w7
	lsl	w2, w2, 1
	lsl	w3, w3, 1
	sub	w2, w2, w1
	lsl	w1, w5, 6
	sub	w1, w1, w5
	sub	w3, w3, w7
	lsl	w1, w1, 1
	lsl	w3, w3, 3
	sub	w1, w1, w5
	lsl	x5, x20, 6
	lsl	w2, w2, 3
	lsl	w1, w1, 3
	udiv	w3, w3, w0
	str	wzr, [x4, x5]
	add	x4, x4, x5
	stp	wzr, w6, [x4, 32]
	str	w0, [x4, 40]
	udiv	w2, w2, w0
	stp	w2, w3, [x4, 16]
	udiv	w1, w1, w0
	stp	w1, wzr, [x4, 24]
.L315:
	lsl	x0, x20, 6
	add	x22, x21, x0
	ldr	w1, [x22, 36]
	ldr	w25, [x22, 8]
	cmp	w1, 1
	beq	.L370
	ldr	w1, [x22, 56]
	cmp	w1, 1
	beq	.L371
	ldr	w2, [x21, x0]
	cbz	w2, .L324
	ldr	x0, [x22, 48]
	cbz	x0, .L372
.L324:
	mov	w0, w25
	bl	VCTRL_IsChanActive
	cbnz	w0, .L373
	mov	w0, w25
	bl	VCTRL_GetDecParam
	cbz	x0, .L374
	mov	w1, 1
	mov	w0, w19
	bl	VDMDRV_AfterDec
.L332:
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	bl	VCTRL_InformVdmFree
	cmp	w24, 1
	beq	.L375
.L327:
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	lsl	x0, x20, 2
	sub	x20, x0, x20
	mov	w0, 1
	lsl	x1, x20, 4
	sub	x20, x1, x20
	add	x21, x21, x20, lsl 2
	ldr	w1, [x21, 488]
	bl	VCTRL_RecordData
	mov	w0, 10
	bl	VCTRL_RecordPosTime
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L293:
	cmp	w24, 1
	beq	.L294
.L333:
	cbnz	w24, .L329
	cmp	w26, 1
	ccmp	w27, 1, 0, eq
	beq	.L329
	ldr	x1, [x22, 264]
	cbz	x1, .L299
	mov	w0, w19
	blr	x1
	cbnz	w0, .L329
.L299:
	ldr	x2, [x22, 312]
	cbz	x2, .L298
	mov	w1, w19
	mov	w0, 1
	blr	x2
	cbnz	w0, .L329
.L298:
	lsl	x0, x20, 6
	str	wzr, [x21, x0]
.L329:
	add	x20, x21, x20, lsl 6
	ldr	w0, [x20, 8]
	bl	VCTRL_InformVdmFree
	ldr	x0, .LC122
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L301
	mov	w1, w19
	mov	w0, 1
	bl	VDH_Notify_ModuleIdle
.L301:
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L335:
	ldr	x22, .LC121
	mov	w25, 0
	ldr	x2, [x22, 312]
	cbnz	x2, .L376
.L336:
	mov	w26, 0
	mov	w24, 0
	mov	w27, 0
	b	.L292
	.p2align 3
.L373:
	ldr	x1, .LC130
	mov	w3, w25
	mov	w2, 1190
	mov	w0, 0
	bl	dprint_vfmw
.L322:
	lsl	x0, x20, 6
	add	x1, x21, x0
	str	wzr, [x21, x0]
	ldrsw	x0, [x1, 8]
	add	x0, x21, x0, lsl 2
	str	wzr, [x0, 336]
	b	.L332
	.p2align 3
.L316:
	str	w1, [x4, x22]
	mov	w5, w1
	mov	w2, 0
	b	.L317
	.p2align 3
.L369:
	cmp	w0, 1
	cset	w2, eq
	cmp	w25, 1
	cset	w1, eq
	tst	w2, w1
	beq	.L307
.L309:
	add	x0, x21, x20, lsl 6
	mov	w1, 1
	mov	w24, w1
	str	w1, [x0, 44]
	b	.L303
	.p2align 3
.L319:
	udiv	w7, w6, w3
	str	w7, [x2, 12]
	b	.L320
	.p2align 3
.L305:
	cmp	w24, 1
	bne	.L306
	cmp	w25, 1
	bne	.L306
.L330:
	add	x0, x21, x20, lsl 6
	mov	w1, 2
	mov	w24, 0
	str	w1, [x0, 44]
	b	.L303
	.p2align 3
.L339:
	mov	w25, 0
	b	.L304
	.p2align 3
.L312:
	ldr	x1, .LC123
	mov	w2, 1243
	mov	w0, 0
	bl	dprint_vfmw
	b	.L313
	.p2align 3
.L310:
	ldr	x1, .LC123
	mov	w2, 1241
	mov	w0, 0
	bl	dprint_vfmw
	b	.L311
	.p2align 3
.L375:
	ldr	x0, .LC122
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L327
	mov	w1, w19
	mov	w0, w24
	bl	VDH_Notify_ModuleIdle
	b	.L327
	.p2align 3
.L370:
	ldr	x1, .LC126
	mov	w2, 1161
	mov	w0, 0
	bl	dprint_vfmw
	str	wzr, [x22, 36]
	b	.L322
	.p2align 3
.L307:
	cmp	w0, wzr
	cset	w0, eq
	tst	w1, w0
	bne	.L330
	cmp	w25, wzr
	cset	w0, eq
	tst	w2, w0
	beq	.L306
	add	x0, x21, x20, lsl 6
	ldr	w1, [x0, 44]
	cmp	w1, 2
	bne	.L309
	mov	w1, 3
	str	w1, [x0, 44]
	b	.L303
	.p2align 3
.L371:
	mov	w1, w19
	mov	w0, w25
	bl	VCTRL_VdmProcSedOnly
	b	.L322
.L374:
	ldr	x1, .LC132
	mov	w3, w25
	mov	w2, 1196
	bl	dprint_vfmw
	b	.L322
.L372:
	ldr	x1, .LC128
	bl	dprint_vfmw
	mov	w0, w25
	bl	VCTRL_GetDecParam
	cbz	x0, .L322
	mov	w3, w19
	mov	x2, 0
	mov	w1, 100
	mov	w0, w25
	bl	VCTRL_VdmPostProc
	b	.L322
.L337:
	mov	w26, 0
	mov	w27, 0
	b	.L292
	.size	VDMDRV_IsrProcess, .-VDMDRV_IsrProcess
	.align	3
.LC115:
	.xword	.LANCHOR2
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC118:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC120:
	.xword	s_pstVfmwChan
	.align	3
.LC121:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC122:
	.xword	g_HalDisable
	.align	3
.LC123:
	.xword	.LC25
	.align	3
.LC124:
	.xword	g_VfmwGlobalStat
	.align	3
.LC126:
	.xword	.LC125
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
	.global	VDMDRV_ResetVDH
	.type	VDMDRV_ResetVDH, %function
VDMDRV_ResetVDH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC134
	ldr	w0, [x19, 8]
	cmp	w20, w0
	beq	.L382
.L377:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L382:
	ldr	x0, .LC135
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L379
	mov	w1, 0
	mov	w0, 1
	bl	VDH_Reset_Module
	str	wzr, [x19]
	b	.L377
	.p2align 3
.L379:
	ldr	x0, .LC136
	ldr	x1, [x0, 152]
	cbz	x1, .L381
	mov	w0, 0
	blr	x1
	str	wzr, [x19]
	b	.L377
.L381:
	ldr	x1, .LC137
	mov	w2, 1590
	mov	w0, 0
	bl	dprint_vfmw
	str	wzr, [x19]
	b	.L377
	.size	VDMDRV_ResetVDH, .-VDMDRV_ResetVDH
	.align	3
.LC134:
	.xword	.LANCHOR0
	.align	3
.LC135:
	.xword	g_HalDisable
	.align	3
.LC136:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC137:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_MarkReloadDsp
	.type	VDMDRV_MarkReloadDsp, %function
VDMDRV_MarkReloadDsp:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbnz	w20, .L383
	add	w0, w19, 1
	cmp	w0, 32
	bhi	.L383
	ldr	x0, .LC138
	mov	w1, 1
	cmn	w19, #1
	str	w1, [x0, 40]
	beq	.L383
	ldr	x5, .LC139
	mov	w7, -1
	ldr	x2, .LC140
	mov	w4, 0
	ldr	x1, .LC142
	mov	w3, 1619
	ldr	x6, [x5, w19, sxtw 3]
	add	x2, x2, 160
	mov	w0, 22
	str	w7, [x6, 28]
	ldr	x5, [x5]
	ldr	w5, [x5, 28]
	bl	dprint_vfmw
.L383:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_MarkReloadDsp, .-VDMDRV_MarkReloadDsp
	.align	3
.LC138:
	.xword	.LANCHOR0
	.align	3
.LC139:
	.xword	s_pstVfmwChan
	.align	3
.LC140:
	.xword	.LANCHOR2
	.align	3
.LC142:
	.xword	.LC141
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_UpdateMatchMode
	.type	VDMDRV_UpdateMatchMode, %function
VDMDRV_UpdateMatchMode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbnz	w20, .L390
	cmp	w19, 31
	bls	.L392
.L390:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L392:
	ldr	x4, .LC143
	mov	w7, 1
	ldr	x2, .LC144
	mov	w5, w19
	ldr	x1, .LC146
	mov	w3, 1632
	ldr	x6, [x4, w19, sxtw 3]
	add	x2, x2, 184
	mov	w0, 22
	str	w7, [x6, 28]
	ldr	x4, [x4, w19, sxtw 3]
	ldr	w4, [x4, 28]
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_UpdateMatchMode, .-VDMDRV_UpdateMatchMode
	.align	3
.LC143:
	.xword	s_pstVfmwChan
	.align	3
.LC144:
	.xword	.LANCHOR2
	.align	3
.LC146:
	.xword	.LC145
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
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11493, %object
	.size	__func__.11493, 19
__func__.11493:
	.string	"VDMDRV_ChnDecReady"
	.align	3
.LANCHOR2 = . + 0
	.type	__FUNCTION__.11534, %object
	.size	__FUNCTION__.11534, 19
__FUNCTION__.11534:
	.string	"VDMDRV_DoBeforeDec"
	.zero	5
	.type	__FUNCTION__.11571, %object
	.size	__FUNCTION__.11571, 29
__FUNCTION__.11571:
	.string	"VDMDRV_AfterDecProcessNormal"
	.zero	3
	.type	__FUNCTION__.11583, %object
	.size	__FUNCTION__.11583, 29
__FUNCTION__.11583:
	.string	"VDMDRV_AfterDecProcessRepair"
	.zero	3
	.type	__FUNCTION__.11621, %object
	.size	__FUNCTION__.11621, 19
__FUNCTION__.11621:
	.string	"VDMDRV_CheckDevice"
	.zero	5
	.type	__func__.11671, %object
	.size	__func__.11671, 18
__func__.11671:
	.string	"VDMDRV_IsrProcess"
	.zero	6
	.type	__FUNCTION__.11672, %object
	.size	__FUNCTION__.11672, 18
__FUNCTION__.11672:
	.string	"VDMDRV_IsrProcess"
	.zero	6
	.type	__func__.11761, %object
	.size	__func__.11761, 21
__func__.11761:
	.string	"VDMDRV_MarkReloadDsp"
	.zero	3
	.type	__func__.11766, %object
	.size	__func__.11766, 23
__func__.11766:
	.string	"VDMDRV_UpdateMatchMode"
	.data
	.align	3
	.type	USE_FF_APT_EN, %object
	.size	USE_FF_APT_EN, 4
USE_FF_APT_EN:
	.word	1
	.zero	4
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
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"Chan %d: CorrectType = %d ErrRatio = %d \n" )
	.zero	6
.LC4:
	ASCII(.string	"Chan %d: Current frame:%d  ErrRatio = %d\n" )
	.zero	6
.LC21:
	ASCII(.string	"====== forece VDM sleep! ======\n" )
	.zero	7
.LC25:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC39:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC42:
	ASCII(.string	"The channel %d is decoding\n" )
	.zero	4
.LC44:
	ASCII(.string	"The channel %d DEC PARAM is not ready\n" )
	.zero	1
.LC51:
	ASCII(.string	"SMMU_READ_ERR  MODULE : VFMW \t SMMU INT STATE: 0x%x \t read_err_addr  = 0x%x\n" )
	.zero	3
.LC53:
	ASCII(.string	"SMMU_WRITE_ERR MODULE : VFMW \t SMMU INT STATE: 0x%x \t write_err_addr = 0x%x\n" )
	.zero	3
.LC62:
	ASCII(.string	"VDMHAL_V200_IsMpeg4NvopCopy point of picture para null, wait forever!!!\n" )
	.zero	7
.LC64:
	ASCII(.string	"VDMDRV_IsVc1SkpicCopy point of picture para null, wait forever!!!\n" )
	.zero	5
.LC66:
	ASCII(.string	"VDMDRV_IsVp6NvopCopy point of picture para null, wait forever!!!\n" )
	.zero	6
.LC68:
	ASCII(.string	"VDMDRV_IsVp9RptFrmCopy point of picture para null, wait forever!!!\n" )
	.zero	4
.LC70:
	ASCII(.string	"VDMDRV_IsProtocolCopy point of picture para null, wait forever!!!\n" )
	.zero	5
.LC75:
	ASCII(.string	"The channel %d DEC PARAM is not ready(pDecParam == NULL)\n" )
	.zero	6
.LC82:
	ASCII(.string	"VDM Start Fail 2 !\n" )
	.zero	4
.LC92:
	ASCII(.string	"isr begin: *pVdmStateMachine = %d, timeout = %d, ErrRatio = %d\n" )
.LC94:
	ASCII(.string	"ISR process vdm timeout! FromInt = %d\n" )
	.zero	1
.LC100:
	ASCII(.string	"Chan %d VdmStateMachine=%d Error! FromInt = %d.\n" )
	.zero	7
.LC104:
	ASCII(.string	"Chan %d Mfde Running VdmStateMachine = %d, but DecParam = NULL!\n" )
	.zero	7
.LC106:
	ASCII(.string	"Chan %d VdmStateMachine = %d, but DecParam = NULL, Reset VDH MFDE!\n" )
	.zero	4
.LC110:
	ASCII(.string	"Chan %d VDM Time Out(%d ms), Reset VDM!\n" )
	.zero	7
.LC116:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC125:
	ASCII(.string	"Line %d, ISR called, ChanResetFlag = 1!!\n" )
	.zero	6
.LC127:
	ASCII(.string	"vdm state machine = %d, but DecParam is null!\n" )
	.zero	1
.LC129:
	ASCII(.string	"line :%d ISR called but chan %d is not active!\n" )
.LC131:
	ASCII(.string	"line :%d ISR called chan %d is active! But Dec Param in CTX is NULL!!!\n" )
.LC141:
	ASCII(.string	"%s,%d, i = %d, MatchVdhIdPlus1 = %d\n" )
	.zero	3
.LC145:
	ASCII(.string	"%s,%d, MatchVdhIdPlus1 = %d,chanId = %d\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_VdmDrvParam, %object
	.size	g_VdmDrvParam, 64
g_VdmDrvParam:
	.zero	64
	.type	s_eVdmDrvSleepState, %object
	.size	s_eVdmDrvSleepState, 4
s_eVdmDrvSleepState:
	.zero	4
	.zero	4
	.type	g_DspDrvState, %object
	.size	g_DspDrvState, 8
g_DspDrvState:
	.zero	8
	.type	g_ChanCtx, %object
	.size	g_ChanCtx, 384
g_ChanCtx:
	.zero	384
	.type	g_BackUp, %object
	.size	g_BackUp, 180
g_BackUp:
	.zero	180
	.zero	4
	.type	g_RepairParam, %object
	.size	g_RepairParam, 1744
g_RepairParam:
	.zero	1744
	.type	last_rec_pos_time.11531, %object
	.size	last_rec_pos_time.11531, 128
last_rec_pos_time.11531:
	.zero	128
	.type	LastRecPosTime.11668, %object
	.size	LastRecPosTime.11668, 128
LastRecPosTime.11668:
	.zero	128
	.type	g_VdmExtParam, %object
	.size	g_VdmExtParam, 268
g_VdmExtParam:
	.zero	268
	.zero	4
	.type	g_DecReport, %object
	.size	g_DecReport, 820
g_DecReport:
	.zero	820
	.zero	4
	.type	g_HwMem, %object
	.size	g_HwMem, 1256
g_HwMem:
	.zero	1256
	.type	g_UpMsg, %object
	.size	g_UpMsg, 3200
g_UpMsg:
	.zero	3200
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
