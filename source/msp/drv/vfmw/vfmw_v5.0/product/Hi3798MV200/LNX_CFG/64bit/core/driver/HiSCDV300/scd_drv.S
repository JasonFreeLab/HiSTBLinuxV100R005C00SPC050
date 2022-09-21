#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"scd_drv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	SCDDRV_SaveStreamSeg.part.4, %function
SCDDRV_SaveStreamSeg.part.4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x19, .LC2
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	x2, .LC3
	ldr	x3, [x19, 88]
	ldr	w1, [x20, 20]
	ldr	x2, [x2, w21, sxtw 3]
	ldr	x0, [x20]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_SaveStreamSeg.part.4, .-SCDDRV_SaveStreamSeg.part.4
	.align	3
.LC2:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC3:
	.xword	vfmw_save_seg_file
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	GetFreeSegBufSize.part.5, %function
GetFreeSegBufSize.part.5:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x0, x19, 360448
	str	wzr, [x20]
	ldp	w2, w3, [x0, 32]
	cmp	w3, w2
	sub	w2, w2, #1
	bls	.L3
	ldr	w0, [x0, 28]
	add	w2, w0, w2
	sub	w2, w2, w3
.L4:
	cmp	w2, w0
	bgt	.L2
	str	w2, [x20]
.L2:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3:
	bcs	.L5
	sub	w2, w2, w3
	ldr	w0, [x0, 28]
	b	.L4
	.p2align 3
.L5:
	ldr	w0, [x0, 28]
	sub	w2, w0, #1
	b	.L4
	.size	GetFreeSegBufSize.part.5, .-GetFreeSegBufSize.part.5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_LoadDspCode
	.type	SCDDRV_LoadDspCode, %function
SCDDRV_LoadDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	w19, .L23
.L8:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L23:
	ldr	x20, .LC4
	ldr	w0, [x20]
	bl	MEM_Phy2Vir
	cbz	x0, .L24
	cmp	w22, 1
	beq	.L25
	cmp	w22, 2
	beq	.L26
	ldr	x1, .LC11
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L26:
	ldr	x21, .LC7
	mov	x2, 17920
	ldr	x1, .LC9
	ldr	x3, [x21, 104]
	add	x1, x1, 512
	blr	x3
	ldr	w0, [x20, 8]
	mov	w1, 0
	bl	MEM_WritePhyWord
.L13:
	ldr	w0, [x20, 8]
	mov	w1, 4480
	mov	w19, 0
	add	w0, w0, 264
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 8]
	ldr	w1, [x20]
	add	w0, w0, 268
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 8]
	mov	w1, 0
	add	w0, w0, 256
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 8]
	mov	w1, 5
	add	w0, w0, 256
	bl	MEM_WritePhyWord
	b	.L16
	.p2align 3
.L27:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L17
.L16:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	w0, [x20, 8]
	add	w0, w0, 260
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L27
	cmp	w19, 999
	bhi	.L17
	ldr	x2, .LC12
	mov	w0, 0
	ldr	x1, .LC16
	bl	dprint_vfmw
.L19:
	cmp	w22, 1
	beq	.L28
	cmp	w22, 2
	bne	.L8
	ldr	x0, .LC17
	mov	w1, 1
	str	w1, [x0]
	b	.L8
	.p2align 3
.L17:
	ldr	x2, .LC12
	mov	w0, 0
	ldr	x1, .LC14
	bl	dprint_vfmw
	b	.L19
	.p2align 3
.L25:
	ldr	x21, .LC7
	mov	x2, 17920
	ldr	x1, .LC8
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w0, [x20, 8]
	mov	w1, w22
	bl	MEM_WritePhyWord
	b	.L13
	.p2align 3
.L28:
	ldr	x0, .LC17
	mov	w1, 2
	str	w1, [x0]
	b	.L8
.L24:
	ldr	x1, .LC6
	ldr	w2, [x20]
	bl	dprint_vfmw
	b	.L8
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	3
.LC4:
	.xword	.LANCHOR0
	.align	3
.LC6:
	.xword	.LC5
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	.LANCHOR1
	.align	3
.LC9:
	.xword	.LANCHOR2
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC12:
	.xword	.LANCHOR3
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC17:
	.xword	g_DspDrvState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetInstIDByRawArray
	.type	GetInstIDByRawArray, %function
GetInstIDByRawArray:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC20
	mov	x0, 0
	b	.L32
	.p2align 3
.L30:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L38
.L32:
	add	x1, x3, x0, lsl 4
	ldr	x1, [x1, 16]
	add	x2, x1, 80
	cmp	x19, x2
	cbz	x1, .L30
	bne	.L30
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L38:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	3
.LC20:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetStateIdle
	.type	SCDDRV_SetStateIdle, %function
SCDDRV_SetStateIdle:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x3, .LC21
	lsl	x1, x0, 6
	ldr	x2, .LC22
	add	x0, x1, x0, lsl 3
	add	x1, x3, x0
	mov	w0, 1
	ldr	x2, [x2, 256]
	str	wzr, [x1, 584]
	blr	x2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateIdle, .-SCDDRV_SetStateIdle
	.align	3
.LC21:
	.xword	.LANCHOR0
	.align	3
.LC22:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetStateWork
	.type	SCDDRV_SetStateWork, %function
SCDDRV_SetStateWork:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC23
	lsl	x1, x0, 6
	add	x0, x1, x0, lsl 3
	mov	w1, 1
	add	x0, x2, x0
	str	w1, [x0, 584]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateWork, .-SCDDRV_SetStateWork
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	sxtw	x23, w0
	mov	x0, x30
	mov	x19, x23
	bl	_mcount
	ldr	x20, .LC24
	mov	w1, 3
	add	x22, x20, x23, lsl 2
	ldr	w0, [x22, 8]
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	ldr	w0, [x22, 8]
	add	w0, w0, 2076
	bl	MEM_ReadPhyWord
	ldr	x22, .LC25
	mov	w24, w0
	ldr	x2, [x22]
	cbnz	w23, .L43
	ldr	w21, [x2, 120]
	tbz	x21, 0, .L59
	orr	w21, w21, 32
	str	w21, [x2, 120]
.L43:
	mov	w0, 0
	mov	w3, 10000
	b	.L47
	.p2align 3
.L50:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L60
.L47:
	ldr	w1, [x2, 372]
	cbnz	w19, .L50
	tbz	x1, 1, .L50
	mov	w1, 9999
	cmp	w0, w1
	bhi	.L61
.L52:
	and	w21, w21, -33
	str	w21, [x2, 120]
.L51:
	add	x20, x20, x23, lsl 2
	and	w1, w24, 1
	ldr	w0, [x20, 8]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 8]
	mov	w1, 2
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L60:
	ldr	x1, .LC29
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w19, .L51
	b	.L53
	.p2align 3
.L61:
	ldr	x1, .LC29
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
.L53:
	ldr	x2, [x22]
	b	.L52
	.p2align 3
.L59:
	ldr	x1, .LC27
	mov	w2, 0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ResetSCD, .-ResetSCD
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	g_pstRegCrg
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ResetSCD
	.type	SCDDRV_ResetSCD, %function
SCDDRV_ResetSCD:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC30
	ldr	w0, [x19, 580]
	cmp	w20, w0
	beq	.L66
.L62:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L66:
	ldr	x0, .LC31
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L64
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L65:
	ldr	x1, .LC32
	mov	w0, 1
	str	wzr, [x19, 584]
	ldr	x1, [x1, 256]
	blr	x1
	b	.L62
	.p2align 3
.L64:
	mov	w0, 0
	bl	ResetSCD
	b	.L65
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC31:
	.xword	g_HalDisable
	.align	3
.LC32:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsRawArrayFull
	.type	SCDDRV_IsRawArrayFull, %function
SCDDRV_IsRawArrayFull:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 98304
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldp	w0, w2, [x1, 4]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	cmp	w0, w2
	cset	w0, eq
	ret
	.size	SCDDRV_IsRawArrayFull, .-SCDDRV_IsRawArrayFull
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_InsertRawPacket
	.type	SCDDRV_InsertRawPacket, %function
SCDDRV_InsertRawPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC33
	add	x19, x0, x19, sxtw 4
	ldr	w0, [x20, 4]
	cmp	w0, wzr
	ldr	x0, [x19, 16]
	ccmp	x0, xzr, 4, ne
	beq	.L70
	add	x0, x0, 80
	add	x19, x0, 98304
	ldp	w3, w1, [x19, 4]
	add	w2, w3, 1
	asr	w4, w2, 31
	lsr	w4, w4, 22
	add	w2, w2, w4
	and	w2, w2, 1023
	sub	w2, w2, w4
	cmp	w2, w1
	beq	.L71
	sxtw	x3, w3
	ldr	x5, .LC34
	lsl	x4, x3, 2
	mov	x2, 96
	sub	x3, x4, x3
	mov	x1, x20
	ldr	x4, [x5, 104]
	add	x0, x0, x3, lsl 5
	blr	x4
	ldr	w1, [x19, 4]
	mov	w0, 0
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	str	w1, [x19, 4]
.L69:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L71:
	mov	w0, -4
	b	.L69
.L70:
	mov	w0, -1
	b	.L69
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	3
.LC33:
	.xword	.LANCHOR0
	.align	3
.LC34:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawState
	.type	GetRawState, %function
GetRawState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L75
	ldr	x0, .LC35
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L75
	add	x2, x0, 80
	mov	w0, -4
	add	x2, x2, 98304
	ldp	w1, w3, [x2, 4]
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	cmp	w1, w3
	csel	w0, w0, wzr, eq
.L73:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L75:
	mov	w0, -4
	b	.L73
	.size	GetRawState, .-GetRawState
	.align	3
.LC35:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ShowRawPacket
	.type	ShowRawPacket, %function
ShowRawPacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 98304
	mov	x21, x1
	bl	_mcount
	ldr	w2, [x19, 4]
	ldr	w0, [x19, 16]
	cmp	w0, w2
	beq	.L79
	sxtw	x0, w0
	ldr	x1, .LC36
	lsl	x3, x0, 2
	mov	x2, 96
	sub	x3, x3, x0
	mov	x0, x21
	ldr	x4, [x1, 104]
	add	x1, x20, x3, lsl 5
	blr	x4
	ldr	w1, [x19, 16]
	mov	w0, 0
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	str	w1, [x19, 16]
.L78:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L79:
	mov	w0, -3
	b	.L78
	.size	ShowRawPacket, .-ShowRawPacket
	.align	3
.LC36:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFirstRawPacket
	.type	GetFirstRawPacket, %function
GetFirstRawPacket:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x23, .L81
	add	x20, x23, 98304
	ldp	w1, w0, [x20]
	cmp	w1, w0
	beq	.L82
	ldr	w24, [x20, 12]
	str	w1, [x20, 16]
	mov	w21, w24
	sxtw	x22, w24
.L83:
	sxtw	x1, w1
	ldr	x3, .LC37
	lsl	x0, x1, 2
	mov	x2, 96
	sub	x1, x0, x1
	mov	x0, x19
	ldr	x3, [x3, 104]
	add	x1, x23, x1, lsl 5
	blr	x3
	ldr	w0, [x20, 16]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	str	w0, [x20, 16]
.L84:
	ldp	w1, w0, [x19, 4]
	ldr	x2, [x19, 40]
	add	w1, w1, w21
	sub	w0, w0, w24
	add	x2, x2, x22
	str	x2, [x19, 40]
	stp	w1, w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L82:
	mov	x22, 0
	mov	w21, 0
	mov	w24, 0
	str	w1, [x20, 16]
	b	.L84
	.p2align 3
.L81:
	mov	x20, 98304
	mov	x22, 0
	mov	w21, 0
	mov	w24, 0
	ldp	w1, w0, [x20]
	str	w1, [x20, 16]
	cmp	w1, w0
	beq	.L84
	b	.L83
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	3
.LC37:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetFirstOffset
	.type	SetFirstOffset, %function
SetFirstOffset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L91
	add	x3, x19, 98304
	ldp	w0, w2, [x3]
	cmp	w0, w2
	beq	.L90
	sxtw	x0, w0
	ldr	w4, [x3, 12]
	lsl	x2, x0, 2
	sub	x0, x2, x0
	add	w1, w20, w4
	add	x0, x19, x0, lsl 5
	ldr	w0, [x0, 8]
	cmp	w1, w0
	bge	.L91
	mov	w0, 0
	str	w1, [x3, 12]
.L88:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L91:
	mov	w0, -1
	b	.L88
	.p2align 3
.L90:
	mov	w0, -3
	b	.L88
	.size	SetFirstOffset, .-SetFirstOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFirstOffset
	.type	GetFirstOffset, %function
GetFirstOffset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L94
	add	x0, x19, 98304
	ldp	w2, w1, [x0]
	cmp	w2, w1
	beq	.L95
	ldr	w1, [x0, 12]
	mov	w0, 0
	str	w1, [x20]
.L93:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L94:
	mov	w0, -1
	b	.L93
	.p2align 3
.L95:
	mov	w0, -3
	b	.L93
	.size	GetFirstOffset, .-GetFirstOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawPacket
	.type	DeleteRawPacket, %function
DeleteRawPacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	x26, xzr
	ccmp	w20, wzr, 4, ne
	beq	.L112
	ldr	x27, .LC38
	mov	x0, 0
	b	.L100
	.p2align 3
.L98:
	cmp	x0, 32
	beq	.L101
.L100:
	add	x1, x27, x0, lsl 4
	mov	w3, w0
	add	x0, x0, 1
	ldr	x1, [x1, 16]
	add	x2, x1, 80
	cmp	x26, x2
	cbz	x1, .L98
	bne	.L98
	tbnz	w3, #31, .L101
	add	x23, x26, 98304
	ldp	w0, w2, [x23]
	cmp	w0, w2
	bgt	.L123
.L120:
	sub	w2, w2, w0
	cmp	w2, w20
	bcc	.L124
	mov	w24, w0
	cbz	w20, .L106
	ldr	x21, .LC43
	add	x27, x27, 16
	ldr	x22, .LC45
	mov	w25, 0
	add	x21, x21, 24
	add	x27, x27, x3, sxtw 4
	.p2align 2
.L107:
	uxtw	x19, w24
	mov	x2, x21
	lsl	x0, x19, 2
	mov	x1, x22
	sub	x19, x0, x19
	mov	w0, 26
	add	w25, w25, 1
	add	w24, w24, 1
	add	x19, x26, x19, lsl 5
	and	w24, w24, 1023
	ldp	w3, w4, [x19, 4]
	bl	dprint_vfmw
	ldr	x1, [x27]
	ldr	w2, [x19, 8]
	add	x1, x1, 98304
	ldr	w0, [x1, 100]
	subs	w0, w0, w2
	csel	w0, w0, wzr, pl
	cmp	w20, w25
	str	w0, [x1, 100]
	bne	.L107
	ldr	w0, [x23]
	add	w20, w20, w0
	str	w20, [x23]
	cmp	w20, 1023
	ble	.L110
	sub	w20, w20, #1024
	str	w20, [x23]
.L110:
	str	wzr, [x23, 12]
.L121:
	mov	w0, 0
.L118:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L123:
	add	w2, w2, 1024
	b	.L120
.L106:
	cmp	w0, 1023
	str	w0, [x23]
	ble	.L121
	sub	w0, w0, #1024
	str	w0, [x23]
	b	.L121
	.p2align 3
.L112:
	mov	w0, -1
	b	.L118
.L124:
	ldr	x1, .LC42
	mov	w3, w20
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, -1
	b	.L118
	.p2align 3
.L101:
	ldr	x1, .LC40
	mov	w2, 525
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L118
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	3
.LC38:
	.xword	.LANCHOR0
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC43:
	.xword	.LANCHOR3
	.align	3
.LC45:
	.xword	.LC44
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawNumOffset
	.type	GetRawNumOffset, %function
GetRawNumOffset:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w1
	mov	x19, x2
	mov	x21, x3
	mov	x20, x4
	bl	_mcount
	cmp	x22, xzr
	ccmp	w23, wzr, 1, ne
	blt	.L132
	add	x8, x22, 98304
	ldr	w7, [x8]
	ldr	w4, [x8, 12]
	sxtw	x1, w7
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 8]
	sub	w4, w0, w4
	cbz	x22, .L133
	ldr	w1, [x8, 4]
	sub	w1, w1, w7
	add	w0, w1, 1024
	cmp	w1, wzr
	csel	w1, w0, w1, lt
.L127:
	add	w1, w7, w1
	cmp	w23, w4
	ccmp	w1, w7, 0, ge
	mov	w0, w7
	bls	.L134
	mov	w6, w7
	b	.L129
	.p2align 3
.L135:
	mov	w4, w2
.L129:
	add	w6, w6, 1
	asr	w0, w6, 31
	lsr	w2, w0, 22
	add	w0, w6, w2
	and	w0, w0, 1023
	sub	w0, w0, w2
	sxtw	x2, w0
	lsl	x5, x2, 2
	sub	x5, x5, x2
	add	x5, x22, x5, lsl 5
	ldr	w2, [x5, 8]
	add	w2, w4, w2
	cmp	w23, w2
	cset	w5, lt
	cmp	w1, w6
	cset	w3, ls
	orr	w3, w5, w3
	cbz	w3, .L135
	cmp	w7, w6
	beq	.L128
	sub	w4, w23, w4
	str	w4, [x21]
.L131:
	str	w0, [x20]
	mov	w0, 0
	ldr	w1, [x8]
	sub	w6, w6, w1
	str	w6, [x19]
.L126:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L134:
	mov	w6, w7
	.p2align 2
.L128:
	str	w23, [x21]
	b	.L131
	.p2align 3
.L133:
	mov	w1, 0
	b	.L127
.L132:
	mov	w0, -1
	b	.L126
	.size	GetRawNumOffset, .-GetRawNumOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cmp	x19, xzr
	ccmp	w22, wzr, 1, ne
	blt	.L139
	stp	wzr, wzr, [x29, 52]
	cbz	x19, .L139
	add	x20, x19, 98304
	ldr	w1, [x20, 12]
	ldr	w0, [x20, 20]
	sub	w0, w0, w1
	asr	w21, w0, 31
	cbnz	w21, .L138
	cmp	w22, w0
	bgt	.L139
	add	x4, x29, 60
	add	x3, x29, 56
	add	x2, x29, 52
	mov	w1, w22
	mov	x0, x19
	bl	GetRawNumOffset
	ldp	w5, w4, [x29, 52]
	ldr	w1, [x20]
	mov	w3, w5
	add	w1, w5, w1
	asr	w0, w1, 31
	lsr	w0, w0, 22
	add	w1, w1, w0
	and	w1, w1, 1023
	sub	w0, w1, w0
	str	w0, [x29, 60]
	ldr	x1, .LC49
	sxtw	x6, w0
	lsl	x2, x6, 2
	sub	x0, x2, x6
	mov	w2, 718
	add	x0, x19, x0, lsl 5
	ldrb	w7, [x0, 2]
	ldr	w6, [x0, 8]
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w1, [x29, 52]
	mov	x0, x19
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	beq	.L140
	sxtw	x0, w0
	ldr	w2, [x20, 12]
	lsl	x1, x0, 2
	ldr	w3, [x29, 56]
	sub	x0, x1, x0
	add	w1, w3, w2
	add	x19, x19, x0, lsl 5
	ldr	w0, [x19, 8]
	cmp	w1, w0
	blt	.L144
.L139:
	mov	w21, -1
.L138:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L144:
	str	w1, [x20, 12]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L140:
	mov	w21, -3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DeleteRawLen, .-DeleteRawLen
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteLastSendRaw
	.type	DeleteLastSendRaw, %function
DeleteLastSendRaw:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L145
	ldr	x0, .LC50
	ubfiz	x19, x19, 4, 32
	add	x0, x0, 16
	ldr	x0, [x0, x19]
	cbz	x0, .L148
	add	x19, x0, 458752
	ldr	w1, [x19, 160]
	cmp	w1, wzr
	ble	.L145
	add	x0, x0, 80
	bl	DeleteRawPacket
	str	wzr, [x19, 160]
.L145:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L148:
	ldr	x1, .LC52
	mov	w2, 742
	bl	dprint_vfmw
	b	.L145
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	3
.LC50:
	.xword	.LANCHOR0
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawStreamSize
	.type	GetRawStreamSize, %function
GetRawStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L151
	add	x19, x19, 98304
	ldr	w2, [x19, 20]
	str	w2, [x20]
	ldr	w0, [x19, 12]
	sub	w0, w2, w0
	str	w0, [x20]
	asr	w0, w0, 31
.L150:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L151:
	mov	w0, -1
	b	.L150
	.size	GetRawStreamSize, .-GetRawStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawStreamNum
	.type	GetRawStreamNum, %function
GetRawStreamNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L155
	add	x19, x19, 98304
	ldp	w2, w0, [x19]
	subs	w0, w0, w2
	bmi	.L154
	str	w0, [x20]
	mov	w0, 0
.L153:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L154:
	add	w2, w0, 1024
	str	w2, [x20]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L155:
	mov	w0, -1
	b	.L153
	.size	GetRawStreamNum, .-GetRawStreamNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ConfigStreamSegArray
	.type	ConfigStreamSegArray, %function
ConfigStreamSegArray:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	x22, x2
	mov	w21, w3
	bl	_mcount
	cmp	x20, xzr
	ccmp	w19, wzr, 4, ne
	beq	.L159
	mov	w0, 262143
	cmp	x22, xzr
	ccmp	w21, w0, 0, ne
	bls	.L159
	ldr	x3, .LC54
	mov	x2, 32824
	movk	x2, 0x5, lsl 16
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x20, 360448
	mov	w0, 0
	str	w19, [x1, 24]
	str	x22, [x20]
	stp	w21, w19, [x1, 28]
	str	w19, [x1, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L159:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	3
.LC54:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetStreamSegArray
	.type	ResetStreamSegArray, %function
ResetStreamSegArray:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L160
	ldr	x3, .LC55
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	add	x0, x19, 8
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x19, 360448
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L160:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	3
.LC55:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegBufFreeSize
	.type	GetSegBufFreeSize, %function
GetSegBufFreeSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 360448
	ldp	w0, w2, [x1, 32]
	cmp	w2, w0
	sub	w0, w0, #1
	bhi	.L169
	sub	w0, w0, w2
	bcc	.L167
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L167:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L169:
	ldr	w1, [x1, 28]
	ldr	x19, [sp, 16]
	add	w0, w0, w1
	sub	w0, w0, w2
	ldp	x29, x30, [sp], 32
	ret
	.size	GetSegBufFreeSize, .-GetSegBufFreeSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckData
	.type	CheckData, %function
CheckData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	uxtb	w20, w1
	bl	_mcount
	and	w0, w20, 31
	sub	w1, w0, #30
	sub	w2, w0, #1
	uxtb	w1, w1
	cmp	w1, 1
	ccmp	w0, 19, 4, hi
	ccmp	w2, 12, 0, ne
	bhi	.L171
	add	x1, x19, 507904
	ldr	w0, [x1, 1360]
	add	w0, w0, 1
	str	w0, [x1, 1360]
.L171:
	sub	w2, w20, #1
	add	w0, w20, 79
	uxtb	w2, w2
	uxtb	w0, w0
	cmp	w2, 183
	ccmp	w0, 4, 0, ls
	bls	.L172
	add	w20, w20, 73
	uxtb	w20, w20
	cmp	w20, 3
	bls	.L172
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L172:
	add	x0, x19, 507904
	ldr	w1, [x0, 1364]
	add	w1, w1, 1
	str	w1, [x0, 1364]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CheckData, .-CheckData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckStartCodeCnt
	.type	CheckStartCodeCnt, %function
CheckStartCodeCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	uxtb	w20, w1
	bl	_mcount
	add	x0, x19, 507904
	ldr	w1, [x0, 1368]
	cmp	w1, 2
	ble	.L177
	and	w20, w20, 31
	cbz	w20, .L177
	ldr	w2, [x0, 1376]
	ldr	w1, [x0, 1380]
	sub	w3, w1, w2
	cmp	w3, 1
	beq	.L188
.L179:
	cmp	w1, w2
	beq	.L189
.L177:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L189:
	ldr	w2, [x0, 1372]
	cmp	w1, w2
	bne	.L177
.L180:
	cmp	w1, 20
	ccmp	w1, 1, 4, ne
	beq	.L177
	ldr	w1, [x0, 1360]
	cmp	w1, wzr
	ble	.L181
	sub	w1, w1, #1
	str	w1, [x0, 1360]
.L181:
	ldr	w1, [x0, 1364]
	add	w1, w1, 1
	str	w1, [x0, 1364]
	b	.L177
	.p2align 3
.L188:
	ldr	w3, [x0, 1372]
	sub	w3, w2, w3
	cmp	w3, 1
	bne	.L179
	b	.L180
	.size	CheckStartCodeCnt, .-CheckStartCodeCnt
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckStream
	.type	CheckStream, %function
CheckStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x0, .LC56
	ldr	x19, [x0, w21, sxtw 3]
	cbz	x19, .L190
	ldr	w0, [x19, 600]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	bne	.L190
	add	x20, x19, 507904
	ldr	w0, [x20, 1368]
	cmp	w0, 199
	bgt	.L190
	ldrb	w1, [x22]
	cbz	w1, .L208
.L198:
	mov	w3, 0
	mov	w22, 0
.L194:
	add	x4, x20, 1280
	ldr	w2, [x20, 1376]
	ldr	w1, [x20, 1380]
	add	w0, w0, 1
	stp	w1, w3, [x4, 96]
	stp	w0, w2, [x4, 88]
	mov	w1, w22
	mov	x0, x19
	bl	CheckData
	mov	x0, x19
	mov	w1, w22
	bl	CheckStartCodeCnt
	ldr	w0, [x20, 1368]
	cmp	w0, 199
	ble	.L190
	ldr	w1, [x20, 1360]
	ldr	w0, [x20, 1364]
	sub	w2, w1, w0
	cmp	w2, 49
	bgt	.L209
.L195:
	sub	w0, w0, w1
	cmp	w0, 49
	ble	.L190
	ldr	w0, [x19, 600]
	cbnz	w0, .L190
	ldr	x0, .LC57
	ldr	x4, [x0]
	cbz	x4, .L190
	mov	w3, 0
	mov	x2, 0
	mov	w1, 124
	mov	w0, w21
	blr	x4
.L190:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L208:
	ldrb	w1, [x22, 1]
	cbnz	w1, .L198
	ldrb	w1, [x22, 2]
	cmp	w1, 1
	bne	.L198
	ldrb	w22, [x22, 3]
	and	w3, w22, 31
	b	.L194
	.p2align 3
.L209:
	ldr	w2, [x19, 600]
	cmp	w2, 3
	bne	.L195
	ldr	x0, .LC57
	ldr	x4, [x0]
	cbz	x4, .L190
	mov	w1, 124
	mov	w3, 0
	mov	x2, 0
	mov	w0, w21
	blr	x4
	ldr	w1, [x20, 1360]
	ldr	w0, [x20, 1364]
	b	.L195
	.size	CheckStream, .-CheckStream
	.align	3
.LC56:
	.xword	s_pstVfmwChan
	.align	3
.LC57:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertStreamSeg
	.type	InsertStreamSeg, %function
InsertStreamSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	mov	w20, w2
	bl	_mcount
	cmp	x21, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L213
	add	x19, x21, 360448
	ldp	w1, w0, [x19, 8]
	add	w0, w0, 1
	asr	w3, w0, 31
	lsr	w3, w3, 20
	add	w0, w0, w3
	and	w0, w0, 4095
	sub	w0, w0, w3
	cmp	w0, w1
	beq	.L214
	ldr	x0, [x22]
	mov	w1, w20
	bl	CheckStream
	ldrsw	x20, [x19, 12]
	ldr	x3, .LC58
	mov	x2, 88
	lsl	x0, x20, 2
	mov	x1, x22
	sub	x0, x0, x20
	lsl	x0, x0, 2
	ldr	x3, [x3, 104]
	sub	x20, x0, x20
	add	x20, x21, x20, lsl 3
	add	x0, x20, 8
	blr	x3
	ldr	w3, [x19, 12]
	mov	w5, 1
	add	w1, w3, 1
	sxtw	x4, w3
	asr	w2, w1, 31
	lsl	x0, x4, 2
	lsr	w2, w2, 20
	sub	x0, x0, x4
	add	w1, w1, w2
	lsl	x0, x0, 2
	and	w1, w1, 4095
	sub	x0, x0, x4
	sub	w1, w1, w2
	add	x21, x21, x0, lsl 3
	strb	w5, [x21, 16]
	str	w3, [x20, 32]
	str	w1, [x19, 12]
	ldrsb	w0, [x22, 9]
	cmp	w0, 2
	beq	.L212
	ldp	w1, w2, [x22, 16]
	ldp	w0, w3, [x19, 40]
	add	w2, w1, w2
	str	w2, [x19, 36]
	ldr	w1, [x22, 20]
	add	w1, w0, w1
	str	w1, [x19, 40]
	ldr	w0, [x22, 20]
	add	w0, w3, w0
	str	w0, [x19, 44]
.L212:
	ldr	w1, [x19, 48]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 48]
.L211:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L213:
	mov	w0, -1
	b	.L211
	.p2align 3
.L214:
	mov	w0, -4
	b	.L211
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	3
.LC58:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetStreamSeg
	.type	SCDDRV_GetStreamSeg, %function
SCDDRV_GetStreamSeg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	bl	_mcount
	cmp	x21, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L227
	add	x22, x21, 360448
	ldp	w19, w1, [x22, 8]
	cmp	w19, w1
	beq	.L229
	sxtw	x20, w19
	lsl	x0, x20, 2
	b	.L234
	.p2align 3
.L222:
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 20
	add	w0, w0, w19
	and	w0, w0, 4095
	sub	w19, w0, w19
	cmp	w19, w1
	sxtw	x20, w19
	lsl	x0, x20, 2
	beq	.L229
.L234:
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 3
	ldrsb	w0, [x0, 16]
	cmp	w0, 1
	bne	.L222
	lsl	x23, x20, 2
	sub	x23, x23, x20
	lsl	x23, x23, 2
	sub	x23, x23, x20
	add	x23, x21, x23, lsl 3
	adds	x1, x23, 8
	beq	.L229
	ldr	x3, .LC59
	mov	x2, 88
	mov	x0, x24
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 88
	mov	w1, 2
	smaddl	x19, w19, w0, x21
	ldrsb	w0, [x19, 17]
	strb	w1, [x19, 16]
	cmp	w0, 2
	ldr	w2, [x22, 44]
	ldr	w3, [x23, 28]
	beq	.L226
	sub	w2, w2, w3
.L226:
	lsl	x0, x20, 2
	ldr	w1, [x22, 48]
	sub	x0, x0, x20
	cmp	w2, wzr
	lsl	x0, x0, 2
	csel	w2, w2, wzr, ge
	sub	x20, x0, x20
	subs	w1, w1, #1
	csel	w1, w1, wzr, pl
	mov	w0, 26
	add	x21, x21, x20, lsl 3
	stp	w2, w1, [x22, 44]
	ldr	x1, .LC61
	ldrb	w4, [x19, 18]
	ldr	w2, [x21, 24]
	bl	dprint_vfmw
	mov	w0, 0
.L219:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L229:
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L227:
	mov	w0, -1
	b	.L219
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	3
.LC59:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC61:
	.xword	.LC60
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	x20, .L259
	sub	w1, w22, #4096
	mov	w0, -4098
	cmp	w1, w0
	bls	.L259
	cmn	w22, #1
	add	x24, x20, 360448
	beq	.L273
	ldp	w0, w1, [x24, 8]
	cmp	w0, w1
	bne	.L269
	b	.L244
	.p2align 3
.L247:
	add	w0, w0, 1
	and	w0, w0, 4095
	cmp	w0, w1
	beq	.L244
.L269:
	cmp	w22, w0
	bne	.L247
	uxtw	x0, w0
	lsl	x21, x0, 2
	sub	x21, x21, x0
	lsl	x21, x21, 2
	sub	x0, x21, x0
	add	x0, x20, x0, lsl 3
	add	x21, x0, 8
	ldrsb	w1, [x0, 16]
	cmp	w1, 2
	beq	.L241
.L244:
	mov	w0, -3
.L268:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L273:
	ldp	w22, w0, [x24, 8]
	cmp	w22, w0
	beq	.L244
	sxtw	x23, w22
	ldr	x1, .LC63
	lsl	x3, x23, 2
	mov	w2, w22
	sub	x3, x3, x23
	mov	w0, 0
	lsl	x3, x3, 2
	sub	x23, x3, x23
	bl	dprint_vfmw
	add	x23, x20, x23, lsl 3
	add	x21, x23, 8
	ldr	w0, [x23, 28]
	cbz	w0, .L243
	ldr	x26, .LC67
	mov	x25, 0
	mov	w19, 0
	.p2align 2
.L242:
	ldr	x2, [x23, 8]
	mov	x1, x26
	mov	w0, 0
	add	w19, w19, 1
	ldrb	w2, [x2, x25]
	add	x25, x25, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 28]
	cmp	w0, w19
	ccmp	w19, 15, 2, hi
	bls	.L242
.L243:
	ldr	x1, .LC65
	mov	w0, 0
	bl	dprint_vfmw
.L241:
	cbz	x21, .L244
	ldrb	w4, [x21, 10]
	mov	w5, w22
	ldr	x1, .LC69
	mov	w0, 26
	ldp	w2, w3, [x21, 16]
	strb	wzr, [x21, 8]
	bl	dprint_vfmw
	ldr	w19, [x24, 8]
	cmp	w22, w19
	beq	.L274
.L249:
	ldrsb	w0, [x21, 9]
	cmp	w0, 2
	beq	.L272
	ldr	w1, [x21, 20]
	ldr	w0, [x24, 40]
	sub	w1, w0, w1
.L253:
	cmp	w1, wzr
	mov	w0, 0
	csel	w1, w1, wzr, ge
	str	w1, [x24, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L272:
	ldr	w1, [x24, 40]
	b	.L253
	.p2align 3
.L274:
	ldr	x22, .LC70
	ldr	x23, .LC72
	add	x22, x22, 40
	b	.L254
	.p2align 3
.L250:
	ldr	w2, [x24, 12]
	lsl	x0, x0, 2
	sub	x0, x0, x1
	cmp	w19, w2
	add	x0, x20, x0, lsl 3
	beq	.L256
	ldrsb	w1, [x0, 16]
	cbnz	w1, .L275
.L251:
	add	w19, w19, 1
	and	w19, w19, 4095
.L254:
	uxtw	x1, w19
	cmp	w19, 4095
	lsl	x0, x1, 2
	sub	x0, x0, x1
	bls	.L250
	mov	x2, x22
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x24, 12]
	cmp	w19, w2
	bne	.L251
	.p2align 2
.L256:
	ldr	w0, [x24, 36]
	str	w2, [x24, 8]
	str	w0, [x24, 32]
	b	.L249
	.p2align 3
.L275:
	str	w19, [x24, 8]
	ldrsb	w1, [x21, 9]
	cmp	w1, 2
	beq	.L272
	ldr	w0, [x0, 24]
	str	w0, [x24, 32]
	b	.L249
.L259:
	mov	w0, -1
	b	.L268
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC70:
	.xword	.LANCHOR3
	.align	3
.LC72:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegStreamSize
	.type	GetSegStreamSize, %function
GetSegStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L278
	add	x19, x19, 360448
	mov	w0, 0
	ldr	w1, [x19, 40]
	str	w1, [x20]
.L277:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L278:
	mov	w0, -1
	b	.L277
	.size	GetSegStreamSize, .-GetSegStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegStreamNum
	.type	GetSegStreamNum, %function
GetSegStreamNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 360448
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x1, 12]
	ldr	w1, [x1, 8]
	sub	w0, w0, w1
	and	w0, w0, 4095
	ret
	.size	GetSegStreamNum, .-GetSegStreamNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFreshSegStream
	.type	GetFreshSegStream, %function
GetFreshSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	cbz	x19, .L280
	add	x19, x19, 360448
	ldr	w0, [x19, 48]
	str	w0, [x21]
	ldr	w0, [x19, 44]
	str	w0, [x20]
.L280:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetFreshSegStream, .-GetFreshSegStream
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_PrepareSleep
	.type	SCDDRV_PrepareSleep, %function
SCDDRV_PrepareSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC74
	sxtw	x0, w19
	add	x2, x1, x0, lsl 2
	ldr	w3, [x2, 600]
	cbnz	w3, .L288
	lsl	x3, x0, 6
	add	x0, x3, x0, lsl 3
	add	x0, x1, x0
	ldr	w0, [x0, 584]
	cbz	w0, .L289
	mov	w1, 1
	mov	w0, 0
	str	w1, [x2, 600]
.L286:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L289:
	mov	w1, 2
	str	w1, [x2, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L288:
	mov	w0, -1
	b	.L286
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	3
.LC74:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetSleepStage
	.type	SCDDRV_GetSleepStage, %function
SCDDRV_GetSleepStage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC75
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	3
.LC75:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ForceSleep
	.type	SCDDRV_ForceSleep, %function
SCDDRV_ForceSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC76
	add	x0, x0, x19, sxtw 2
	ldr	w1, [x0, 600]
	cmp	w1, 2
	beq	.L291
	mov	w1, 2
	str	w1, [x0, 600]
.L291:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	3
.LC76:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ExitSleep
	.type	SCDDRV_ExitSleep, %function
SCDDRV_ExitSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC77
	add	x19, x0, x19, sxtw 2
	str	wzr, [x19, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	3
.LC77:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetLastUnfinishedSegInfo
	.type	ResetLastUnfinishedSegInfo, %function
ResetLastUnfinishedSegInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 458752
	ldr	x1, .LC78
	add	x6, x0, 256
	mov	w3, -1
	mov	w5, 1
	mov	x2, 88
	strh	w3, [x0, 460]
	add	x0, x0, 504
	strh	w3, [x0, -36]
	str	w3, [x0, -40]
	ldr	x4, [x1, 96]
	mov	w1, 0
	stp	w3, wzr, [x6, 216]
	stp	w5, wzr, [x6, 224]
	str	wzr, [x0, -16]
	str	wzr, [x0, -12]
	str	wzr, [x0, -8]
	blr	x4
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetLastUnfinishedSegInfo, .-ResetLastUnfinishedSegInfo
	.align	3
.LC78:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L300
	ldr	x20, .LC80
	sbfiz	x19, x19, 4, 32
	ldr	x21, .LC79
	mov	x2, 16976
	add	x20, x20, 16
	movk	x2, 0x7, lsl 16
	mov	w1, 0
	ldr	x3, [x21, 96]
	ldr	x0, [x20, x19]
	blr	x3
	ldr	x3, [x20, x19]
	mov	w4, -1
	ldr	x5, [x21, 96]
	mov	w6, 1
	add	x3, x3, 458752
	mov	x2, 88
	add	x7, x3, 256
	mov	w1, 0
	add	x0, x3, 504
	strh	w4, [x3, 460]
	strh	w4, [x3, 468]
	str	w4, [x3, 464]
	stp	w4, wzr, [x7, 216]
	stp	w6, wzr, [x7, 224]
	str	wzr, [x3, 488]
	str	wzr, [x3, 492]
	str	wzr, [x3, 496]
	blr	x5
	ldr	x1, [x20, x19]
	mov	x2, -1
	mov	w0, 0
	add	x1, x1, 458752
	str	x2, [x1, 272]
.L299:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L300:
	mov	w0, -1
	b	.L299
	.size	SM_ClearInst, .-SM_ClearInst
	.align	3
.LC79:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC80:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_InstInit
	.type	SM_InstInit, %function
SM_InstInit:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC82
	ldr	x21, .LC83
	add	x19, x20, 16
	add	x20, x20, 528
	.p2align 2
.L302:
	ldr	x3, [x21, 96]
	mov	x0, x19
	mov	x2, 16
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	cmp	x19, x20
	bne	.L302
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_InstInit, .-SM_InstInit
	.align	3
.LC82:
	.xword	.LANCHOR0
	.align	3
.LC83:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	w20, w2
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cbz	w20, .L306
	cmp	w20, 1
	ldr	x2, .LC85
	bne	.L318
	ldr	x1, .LC89
	mov	w3, 1366
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -7
	b	.L308
	.p2align 3
.L306:
	ldr	x21, .LC90
	mov	w1, 49152
	movk	w1, 0xf8c3, lsl 16
	add	x20, x21, 528
	ldr	w0, [x20, 48]
	str	w1, [x21, 8]
	cmp	w0, 1
	beq	.L311
	ldr	x3, .LC91
	mov	x2, 72
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	str	w19, [x21, 528]
	ldr	x2, .LC92
	add	w1, w19, 15
	and	w1, w1, -16
	str	w23, [x20, 4]
	mov	w0, w1
	str	w1, [x20, 16]
	str	wzr, [x2, 56]
	sub	w22, w1, w19
	str	wzr, [x21, 600]
	bl	MEM_Phy2Vir
	str	x0, [x20, 8]
	add	w1, w19, 12288
	mov	w2, 12288
	add	w1, w1, w22
	str	w2, [x20, 20]
	str	w1, [x20, 32]
	mov	w0, w1
	add	w19, w19, 45056
	add	w19, w19, 127
	bl	MEM_Phy2Vir
	add	w19, w19, w22
	str	x0, [x20, 24]
	and	w19, w19, -128
	mov	w0, 32768
	str	w0, [x20, 36]
	mov	w0, w19
	str	w19, [x21]
	bl	MEM_Phy2Vir
	str	x0, [x21, 608]
	cbz	x0, .L319
	add	w22, w22, 61440
	ldr	w2, [x21, 8]
	add	w22, w22, 1536
	ldr	w0, [x21, 624]
	mov	w1, 17920
	cmp	w23, w22
	stp	w2, w0, [x20, 40]
	str	w1, [x21, 616]
	blt	.L311
	ldr	x0, [x20, 8]
	cbz	x0, .L311
	ldr	x0, [x20, 24]
	cbz	x0, .L311
	mov	w1, 1
	mov	w0, 0
	str	w1, [x20, 48]
.L308:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L318:
	ldr	x1, .LC87
	add	x2, x2, 64
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L311:
	mov	w0, -7
	b	.L308
.L319:
	ldr	x2, .LC85
	ldr	x1, .LC94
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L308
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	3
.LC85:
	.xword	.LANCHOR3
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC90:
	.xword	.LANCHOR0
	.align	3
.LC91:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC92:
	.xword	g_VfmwGlobalStat
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CloseSCDDrv
	.type	SM_CloseSCDDrv, %function
SM_CloseSCDDrv:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x4, .LC96
	add	x0, x4, 16
	add	x3, x4, 528
	b	.L322
	.p2align 3
.L321:
	cmp	x0, x3
	beq	.L330
.L322:
	ldr	x1, [x0]
	add	x0, x0, 16
	add	x2, x1, 458752
	cbz	x1, .L321
	ldr	w1, [x2, 248]
	cbz	w1, .L321
	ldr	w1, [x2, 236]
	cmp	w1, wzr
	bgt	.L321
	str	wzr, [x2, 248]
	cmp	x0, x3
	bne	.L322
.L330:
	sxtw	x1, w19
	ldr	x3, .LC97
	lsl	x0, x1, 6
	ldr	x5, .LC98
	add	x3, x3, x0
	add	x4, x4, 528
	add	x0, x0, x1, lsl 3
	mov	x2, 72
	ldr	x5, [x5, 96]
	mov	w1, 0
	add	x0, x4, x0
	str	wzr, [x3, 56]
	blr	x5
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	3
.LC96:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	g_VfmwGlobalStat
	.align	3
.LC98:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w21, 31
	ccmp	x19, xzr, 4, ls
	beq	.L345
	ldr	x1, .LC102
	add	x0, x1, x21, sxtw 4
	ldr	x5, [x0, 16]
	cbz	x5, .L337
	add	x22, x5, 458752
	ldr	w0, [x19, 48]
	str	w0, [x22, 320]
	ldr	w2, [x5, 24]
	ldr	w0, [x19, 16]
	cmp	w2, w0
	beq	.L346
	cbz	w0, .L337
	ldr	x0, [x19]
	cbz	x0, .L337
	ldr	w2, [x1, 544]
	ldr	w6, [x1, 548]
	ldr	x0, [x1, 536]
	stp	w6, w2, [x22, 192]
	str	x0, [x22, 184]
	mov	w6, 262143
	ldr	w3, [x1, 560]
	ldr	w0, [x1, 564]
	ldr	x2, [x1, 552]
	str	w0, [x22, 212]
	mov	w0, 4096
	str	w3, [x22, 208]
	str	w0, [x22, 216]
	str	x2, [x22, 200]
	ldr	w3, [x19, 16]
	ldr	x2, [x19]
	add	w1, w3, 3
	and	w1, w1, -4
	sub	w3, w1, w3
	add	w1, w1, 131072
	str	w1, [x22, 220]
	sxtw	x0, w3
	add	x0, x0, 131072
	add	x2, x2, x0
	str	x2, [x22, 176]
	ldr	w0, [x19, 20]
	sub	w3, w0, w3
	sub	w3, w3, #131072
	sub	w3, w3, #1024
	str	w3, [x22, 224]
	cmp	w3, w6
	ble	.L337
	add	x0, x5, 98304
	add	x20, x5, 8
	add	x0, x0, 104
	bl	ConfigStreamSegArray
	ldr	x23, .LC103
	mov	x2, 72
	mov	x1, x19
	mov	x0, x20
	ldr	x3, [x23, 104]
	blr	x3
	str	wzr, [x22, 236]
.L336:
	ldr	x3, [x23, 104]
	mov	x2, 72
	mov	x1, x19
	mov	x0, x20
	blr	x3
	mov	w0, 2
	str	w0, [x22, 308]
	ldr	w0, [x19, 12]
	cmp	w0, 2
	beq	.L347
.L338:
	mov	w0, 0
	str	w21, [x22, 232]
.L333:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L347:
	mov	w0, 3
	str	w0, [x22, 308]
	b	.L338
	.p2align 3
.L346:
	add	x20, x5, 8
	ldr	x23, .LC103
	b	.L336
	.p2align 3
.L337:
	mov	w0, -1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L345:
	ldr	x1, .LC101
	mov	x4, x19
	mov	w3, w21
	mov	w2, 1459
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L333
	.size	SM_Config, .-SM_Config
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC102:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CfgBuf
	.type	SM_CfgBuf, %function
SM_CfgBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L356
	cbnz	w20, .L357
	ldr	x1, .LC109
	add	x19, x1, x19, sxtw 4
	ldr	x2, [x19, 16]
	cbz	x2, .L352
	add	x2, x2, 458752
	ldr	w0, [x2, 236]
	cbz	w0, .L350
	add	x0, x1, 528
	ldr	w4, [x0, 32]
	ldr	x6, [x0, 8]
	ldr	x3, [x0, 24]
	ldp	w7, w5, [x0, 16]
	ldr	w0, [x0, 36]
	stp	w4, w0, [x2, 208]
	mov	w0, 4096
	str	x6, [x2, 184]
	str	w0, [x2, 216]
	mov	w0, 0
	stp	w5, w7, [x2, 192]
	str	x3, [x2, 200]
	str	wzr, [x2, 236]
.L350:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L356:
	ldr	x1, .LC106
	mov	w3, w19
	mov	w2, 1539
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L350
	.p2align 3
.L357:
	ldr	x1, .LC108
	mov	w3, w20
	mov	w2, 1546
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L350
.L352:
	mov	w0, -1
	b	.L350
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC109:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Start
	.type	SM_Start, %function
SM_Start:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC111
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L362
	ldr	w1, [x0, 28]
	cbz	w1, .L362
	add	x1, x0, 458752
	ldr	w0, [x1, 248]
	cbnz	w0, .L362
	mov	w2, 1
	str	w2, [x1, 248]
.L359:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L362:
	mov	w0, -7
	b	.L359
	.size	SM_Start, .-SM_Start
	.align	3
.LC111:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Stop
	.type	SM_Stop, %function
SM_Stop:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC112
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L365
	add	x1, x0, 458752
	ldr	w0, [x1, 248]
	cbz	w0, .L364
	ldr	w0, [x1, 236]
	cmp	w0, wzr
	bgt	.L366
	mov	w0, 0
	str	wzr, [x1, 248]
.L364:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L366:
	mov	w0, -7
	b	.L364
	.p2align 3
.L365:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Stop, .-SM_Stop
	.align	3
.LC112:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_GetInfo
	.type	SM_GetInfo, %function
SM_GetInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L377
	ldr	x0, .LC113
	add	x20, x0, x20, sxtw 4
	ldr	x0, [x20, 16]
	cbz	x0, .L383
	add	x2, x0, 458752
	adds	x1, x0, 80
	ldr	w3, [x2, 248]
	strb	w3, [x19]
	ldr	w2, [x2, 300]
	str	w2, [x19, 20]
	beq	.L373
	add	x3, x1, 98304
	ldr	w2, [x3, 4]
	ldr	w3, [x3]
	subs	w2, w2, w3
	bmi	.L384
	str	w2, [x19, 4]
.L375:
	add	x1, x1, 98304
	ldr	w2, [x1, 20]
	str	w2, [x19, 12]
	ldr	w1, [x1, 12]
	sub	w2, w2, w1
	str	w2, [x19, 12]
.L373:
	add	x0, x0, 98304
	add	x0, x0, 104
	add	x2, x0, 360448
	ldp	w3, w1, [x2, 8]
	sub	w1, w1, w3
	and	w1, w1, 4095
	str	w1, [x19, 8]
	cbz	x0, .L378
	ldr	w1, [x2, 40]
	mov	w0, 0
	str	w1, [x19, 16]
.L382:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L384:
	add	w2, w2, 1024
	str	w2, [x19, 4]
	b	.L375
	.p2align 3
.L383:
	cbz	x19, .L377
	strb	wzr, [x19]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L378:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L377:
	mov	w0, -1
	b	.L382
	.size	SM_GetInfo, .-SM_GetInfo
	.align	3
.LC113:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawNumInFrame
	.type	GetRawNumInFrame, %function
GetRawNumInFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x21, x2
	bl	_mcount
	add	x2, x20, 98304
	mov	w3, 1
	ldr	w0, [x2]
	uxtw	x5, w0
	lsl	x1, x5, 2
	sub	x1, x1, x5
	add	x1, x20, x1, lsl 5
	ldr	w1, [x1, 8]
	str	w1, [x21]
	str	w3, [x19]
	b	.L386
	.p2align 3
.L388:
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	ldr	w1, [x21]
	ldr	w3, [x4, 8]
	add	w3, w1, w3
	str	w3, [x21]
	ldr	w1, [x2, 4]
	cmp	w0, w1
	beq	.L390
	ldr	w1, [x19]
	cmp	w1, 1024
	bhi	.L390
.L386:
	lsl	x3, x5, 2
	add	w0, w0, 1
	sub	x3, x3, x5
	and	w0, w0, 1023
	lsl	x3, x3, 5
	uxtw	x5, w0
	lsl	x4, x5, 2
	ldrb	w1, [x20, x3]
	sub	x4, x4, x5
	add	x4, x20, x4, lsl 5
	cbnz	w1, .L388
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L390:
	mov	w0, -4
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetRawNumInFrame, .-GetRawNumInFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AdjustRawPacketVP6A
	.type	AdjustRawPacketVP6A, %function
AdjustRawPacketVP6A:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x1
	mov	x22, x0
	mov	x0, x30
	mov	x19, x4
	mov	x21, x2
	mov	x20, x3
	bl	_mcount
	add	x0, x22, 98304
	ldr	w4, [x23]
	ldr	w5, [x0]
	cbz	w4, .L396
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w6, [x0, 8]
	cmp	w6, 2
	bgt	.L397
	mov	w0, w6
	mov	w3, 3
	mov	w2, 0
	b	.L394
	.p2align 3
.L395:
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 8]
	add	w6, w6, w0
	cmp	w6, 2
	bgt	.L399
.L394:
	add	w2, w2, 1
	add	w5, w5, 1
	cmp	w2, w4
	sub	w3, w3, w0
	and	w5, w5, 1023
	bne	.L395
.L396:
	mov	w0, -4
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L399:
	sxtw	x3, w3
.L393:
	lsl	x0, x7, 2
	sub	w2, w4, w2
	sub	x7, x0, x7
	str	w2, [x23]
	sub	w6, w6, #3
	mov	w0, 0
	add	x22, x22, x7, lsl 5
	ldr	x1, [x22, 40]
	add	x3, x1, x3
	str	x3, [x21]
	str	w6, [x20]
	str	w5, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L397:
	mov	x3, 3
	mov	w2, 0
	b	.L393
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CopyRawToSeg
	.type	SM_CopyRawToSeg, %function
SM_CopyRawToSeg:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	x26, x1
	str	w19, [x29, 100]
	bl	_mcount
	ldr	x0, .LC114
	mov	x1, x19
	add	x0, x0, x1, sxtw 4
	ldr	x28, [x0, 16]
	cbz	x28, .L421
	add	x22, x28, 80
	add	x25, x28, 98304
	add	x0, x25, 104
	cmp	x22, xzr
	ccmp	x0, xzr, 4, ne
	str	x0, [x29, 104]
	ccmp	x26, xzr, 4, ne
	beq	.L421
	add	x0, x22, 98304
	ldp	w23, w4, [x0]
	cmp	w4, w23
	beq	.L441
	uxtw	x1, w23
	mov	w0, w23
	lsl	x2, x1, 2
	mov	x3, x1
	sub	x2, x2, x1
	mov	w21, 1
	add	x1, x22, x2, lsl 5
	ldr	w27, [x1, 8]
	b	.L403
	.p2align 3
.L405:
	add	w21, w21, 1
	ldr	w1, [x2, 8]
	cmp	w21, 1024
	ccmp	w4, w0, 4, ls
	add	w27, w27, w1
	beq	.L441
.L403:
	lsl	x2, x3, 2
	add	w0, w0, 1
	sub	x1, x2, x3
	and	w0, w0, 1023
	lsl	x1, x1, 5
	uxtw	x3, w0
	lsl	x2, x3, 2
	ldrb	w1, [x22, x1]
	sub	x2, x2, x3
	add	x2, x22, x2, lsl 5
	cbnz	w1, .L405
	ldr	x0, [x29, 104]
	cbz	x0, .L418
	ldr	x0, .LC115
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	ldr	x3, [x0, 96]
	add	x0, x25, 112
	blr	x3
	add	x0, x25, 104
	add	x0, x0, 360448
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L418:
	add	x0, x25, 104
	add	x0, x0, 360448
	ldr	w1, [x0, 28]
	cmp	w1, w27
	blt	.L443
	sxtw	x19, w23
	ldr	w1, [x28, 20]
	lsl	x2, x19, 2
	ldr	x24, [x25, 104]
	sub	x2, x2, x19
	cmp	w1, 12
	add	x1, x22, 98304
	ldr	w0, [x0, 24]
	add	x2, x22, x2, lsl 5
	ldr	w23, [x1]
	ldr	w25, [x2, 8]
	ldr	x28, [x2, 40]
	ccmp	w25, wzr, 4, eq
	beq	.L408
	cbz	w21, .L441
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w25, [x1, 8]
	cmp	w25, 2
	bgt	.L422
	mov	w6, 3
	mov	w2, 0
	mov	w5, w25
	b	.L411
	.p2align 3
.L412:
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w5, [x1, 8]
	add	w25, w25, w5
	cmp	w25, 2
	bgt	.L444
.L411:
	add	w2, w2, 1
	add	w23, w23, 1
	cmp	w2, w21
	sub	w6, w6, w5
	and	w23, w23, 1023
	bne	.L412
	.p2align 2
.L441:
	mov	w0, -4
.L438:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L444:
	sxtw	x6, w6
.L409:
	lsl	x1, x20, 2
	sub	w21, w21, w2
	sub	x1, x1, x20
	sub	w25, w25, #3
	add	x1, x22, x1, lsl 5
	ldr	x28, [x1, 40]
	add	x28, x28, x6
	.p2align 2
.L408:
	str	w0, [x26, 16]
	bl	MEM_Phy2Vir
	str	x0, [x26]
	lsl	x1, x19, 2
	sub	x2, x24, x0
	sub	x1, x1, x19
	str	w2, [x26, 20]
	mov	w3, 1
	add	x1, x22, x1, lsl 5
	ldr	x2, [x1, 64]
	str	x2, [x26, 32]
	ldr	x2, [x1, 64]
	str	x2, [x26, 40]
	ldr	x2, [x1, 48]
	str	x2, [x26, 48]
	strb	w3, [x26, 10]
	ldr	x2, [x1, 56]
	str	x2, [x26, 56]
	ldr	w2, [x1, 20]
	str	w2, [x26, 64]
	ldr	w2, [x1, 24]
	str	w2, [x26, 68]
	ldr	w2, [x1, 28]
	str	w2, [x26, 72]
	ldr	w1, [x1, 32]
	str	w1, [x26, 76]
	cbz	w21, .L413
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L441
	ldr	x0, .LC115
	mov	w19, 0
	uxtw	x20, w23
	str	x0, [x29, 112]
	b	.L415
	.p2align 3
.L416:
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L441
.L415:
	sxtw	x2, w25
	mov	w0, 2
	str	x2, [x29, 120]
	add	w23, w23, 1
	bl	VCTRL_RecordPosTime
	and	w23, w23, 1023
	ldp	x0, x2, [x29, 112]
	mov	x1, x28
	add	w19, w19, 1
	ldr	x6, [x0, 104]
	mov	x0, x24
	add	x24, x24, x2
	blr	x6
	mov	w0, 3
	bl	VCTRL_RecordPosTime
	mov	w1, w25
	mov	w0, 0
	bl	VCTRL_RecordData
	lsl	x2, x20, 2
	ldr	w1, [x26, 20]
	sub	x2, x2, x20
	uxtw	x20, w23
	lsl	x0, x20, 2
	add	w25, w1, w25
	add	x2, x22, x2, lsl 5
	sub	x0, x0, x20
	cmp	w21, w19
	add	x0, x22, x0, lsl 5
	ldrb	w1, [x2, 1]
	strb	w1, [x26, 11]
	str	w25, [x26, 20]
	ldr	w25, [x0, 8]
	ldr	x28, [x0, 40]
	bne	.L416
	ldr	x0, [x26]
.L413:
	cbz	x0, .L445
	ldr	w2, [x29, 100]
	mov	x1, x26
	ldr	x0, [x29, 104]
	bl	InsertStreamSeg
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L443:
	ldr	x1, .LC117
	mov	w2, w27
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	cbz	w0, .L441
	ldr	x1, .LC119
	mov	w2, 1773
	mov	w0, 0
	bl	dprint_vfmw
	b	.L441
.L421:
	mov	w0, -1
	b	.L438
.L422:
	mov	x6, 3
	mov	w2, 0
	b	.L409
.L445:
	ldr	x2, .LC120
	mov	w3, 1834
	ldr	x1, .LC122
	mov	w0, 1
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -4
	b	.L438
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC120:
	.xword	.LANCHOR3
	.align	3
.LC122:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsSCDByPass
	.type	SCDDRV_IsSCDByPass, %function
SCDDRV_IsSCDByPass:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	tst	w19, -17
	beq	.L450
	sub	w0, w19, #2
	cmp	w0, 1
	bls	.L450
	cmp	w19, 6
	mov	w0, 0
	ccmp	w19, 18, 4, ne
	cset	w1, eq
	cbnz	w1, .L447
	cmp	w19, 1
	beq	.L453
.L448:
	cmp	w19, 15
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L450:
	mov	w0, 0
.L447:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L453:
	ldr	w1, [x20]
	cbz	w1, .L448
	b	.L447
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC123
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L454
	ldrsb	w0, [x20, 9]
	cmp	w0, 2
	beq	.L454
	mov	x1, x20
	mov	w0, w19
	bl	SCDDRV_SaveStreamSeg.part.4
.L454:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	3
.LC123:
	.xword	vfmw_save_seg_file
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x0, .LC124
	cmp	x21, xzr
	add	x0, x0, x22, sxtw 4
	ldr	x19, [x0, 16]
	ccmp	x19, xzr, 4, ne
	beq	.L466
	ldr	w0, [x19, 20]
	add	x1, x19, 36
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbz	w0, .L464
	mov	x1, x21
	mov	w0, w22
	bl	SM_CopyRawToSeg
	cbnz	w0, .L476
.L464:
	add	x0, x19, 98304
	mov	x1, x21
	add	x0, x0, 104
	add	x19, x19, 458752
	bl	SCDDRV_GetStreamSeg
	cbnz	w0, .L465
	ldr	x0, .LC127
	str	wzr, [x19, 300]
	ldr	x0, [x0, w22, sxtw 3]
	cbz	x0, .L467
	ldrsb	w0, [x21, 9]
	mov	w20, 0
	cmp	w0, 2
	beq	.L463
	mov	x1, x21
	mov	w0, w22
	bl	SCDDRV_SaveStreamSeg.part.4
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L465:
	mov	w20, w0
	ldr	w0, [x19, 300]
	add	w0, w0, 1
	str	w0, [x19, 300]
.L463:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L476:
	ldr	x1, .LC126
	add	x19, x19, 458752
	mov	w0, 26
	mov	w20, -7
	bl	dprint_vfmw
	ldr	w0, [x19, 300]
	add	w0, w0, 1
	str	w0, [x19, 300]
	b	.L463
	.p2align 3
.L467:
	mov	w20, 0
	b	.L463
	.p2align 3
.L466:
	mov	w20, -1
	b	.L463
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	3
.LC124:
	.xword	.LANCHOR0
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC127:
	.xword	vfmw_save_seg_file
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReleaseStreamSeg
	.type	SM_ReleaseStreamSeg, %function
SM_ReleaseStreamSeg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC128
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L479
	add	x0, x0, 98304
	mov	w1, w20
	add	x0, x0, 104
	bl	ReleaseStreamSeg
.L478:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L479:
	mov	w0, -1
	b	.L478
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	3
.LC128:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_GiveThreadEvent
	.type	SM_GiveThreadEvent, %function
SM_GiveThreadEvent:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC129
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	3
.LC129:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcInstBlockTime
	.type	CalcInstBlockTime, %function
CalcInstBlockTime:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC130
	ldr	x0, [x0]
	blr	x0
	mov	w3, w0
	add	x1, x19, 458752
	cbnz	w20, .L485
	ldr	w2, [x1, 264]
	cmp	w0, w2
	bhi	.L486
	str	wzr, [x1, 260]
	mov	w0, 0
	str	w3, [x1, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L486:
	sub	w0, w0, w2
	str	w0, [x1, 260]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L485:
	str	wzr, [x1, 260]
	mov	w0, 0
	str	w3, [x1, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsChanDec
	.type	SCDDRV_IsChanDec, %function
SCDDRV_IsChanDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC131
	add	x0, x0, 528
	ldr	w1, [x0, 56]
	cmp	w1, 1
	beq	.L490
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L490:
	ldr	w0, [x0, 52]
	cmp	w0, w19
	ldr	x19, [sp, 16]
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsChanDec, .-SCDDRV_IsChanDec
	.align	3
.LC131:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetRawStreamStatus
	.type	SCDDRV_GetRawStreamStatus, %function
SCDDRV_GetRawStreamStatus:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cbz	x19, .L491
	add	x0, x19, 98304
	ldr	w3, [x0, 20]
	str	w3, [x20]
	ldr	w1, [x0, 12]
	sub	w3, w3, w1
	str	w3, [x20]
	ldr	w1, [x0, 4]
	ldr	w0, [x0]
	subs	w1, w1, w0
	bmi	.L497
.L496:
	str	w1, [x21]
.L491:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L497:
	add	w1, w1, 1024
	b	.L496
	.size	SCDDRV_GetRawStreamStatus, .-SCDDRV_GetRawStreamStatus
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFreeSegBufSize
	.type	GetFreeSegBufSize, %function
GetFreeSegBufSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L498
	mov	x1, x20
	mov	x0, x19
	bl	GetFreeSegBufSize.part.5
.L498:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x4
	mov	x22, x2
	mov	w20, w1
	mov	x21, x3
	bl	_mcount
	cmp	x19, xzr
	str	wzr, [x23]
	ccmp	x22, xzr, 4, ne
	bne	.L505
.L501:
	ldr	w1, [x22]
	add	w0, w20, 79
	mov	w3, 0
	cmp	w1, w0
	bcc	.L502
	sub	w1, w1, w20
	sub	w3, w1, #79
.L502:
	add	x0, x19, 360448
	str	w3, [x22]
	ldr	w2, [x0, 28]
	lsl	w1, w2, 3
	sub	w1, w1, w2
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	cmp	w20, w1, asr 3
	bcc	.L503
	add	w20, w3, w20
	str	w20, [x22]
	mov	w1, 1
	str	w1, [x23]
.L503:
	ldr	w1, [x0, 12]
	mov	w2, 4096
	ldr	w0, [x0, 8]
	sub	w0, w1, w0
	and	w0, w0, 4095
	sub	w0, w2, w0
	str	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L505:
	mov	x1, x22
	mov	x0, x19
	bl	GetFreeSegBufSize.part.5
	b	.L501
	.size	SCDDRV_GetSegStreamStatus, .-SCDDRV_GetSegStreamStatus
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsRawStreamNotEnough
	.type	SCDDRV_IsRawStreamNotEnough, %function
SCDDRV_IsRawStreamNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	ccmp	w19, 3, 0, ne
	cset	w0, ls
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsRawStreamNotEnough, .-SCDDRV_IsRawStreamNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsFreeSegSlotNotEnough
	.type	SCDDRV_IsFreeSegSlotNotEnough, %function
SCDDRV_IsFreeSegSlotNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1024
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsFreeSegSlotNotEnough, .-SCDDRV_IsFreeSegSlotNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsFreeSegBufNotEnough
	.type	SCDDRV_IsFreeSegBufNotEnough, %function
SCDDRV_IsFreeSegBufNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, w20, lsr 3
	cset	w0, ls
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsFreeSegBufNotEnough, .-SCDDRV_IsFreeSegBufNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CheckConditionOfStartSCD
	.type	SCDDRV_CheckConditionOfStartSCD, %function
SCDDRV_CheckConditionOfStartSCD:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w23, w2
	mov	x25, x3
	mov	x21, x4
	mov	x22, x5
	mov	x24, x6
	bl	_mcount
	cbz	x19, .L513
	add	x0, x19, 98304
	ldr	w2, [x0, 20]
	str	w2, [x25]
	ldr	w1, [x0, 12]
	sub	w2, w2, w1
	str	w2, [x25]
	ldr	w2, [x0, 4]
	ldr	w0, [x0]
	sub	w0, w2, w0
	cmp	w0, wzr
	blt	.L518
.L517:
	ldr	w2, [x25]
	cset	w3, eq
	mov	w0, -5
	cmp	w2, 3
	cset	w1, ls
	orr	w1, w3, w1
	cbnz	w1, .L510
	mov	x0, x20
	mov	x4, x24
	mov	x3, x22
	mov	x2, x21
	mov	w1, w23
	bl	SCDDRV_GetSegStreamStatus
	ldr	w0, [x22]
	cmp	w0, 1024
	bls	.L515
	add	x20, x20, 360448
	ldr	w1, [x21]
	mov	w0, -6
	ldr	w2, [x20, 28]
	cmp	w1, w2, lsr 3
	csel	w0, wzr, w0, hi
.L510:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L518:
	cmn	w0, #1024
	b	.L517
	.p2align 3
.L513:
	mov	w0, -5
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L515:
	mov	w0, -6
	b	.L510
	.size	SCDDRV_CheckConditionOfStartSCD, .-SCDDRV_CheckConditionOfStartSCD
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetCtrlReg
	.type	SCDDRV_SetCtrlReg, %function
SCDDRV_SetCtrlReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	w1, [x20, 20]
	cmp	w1, 18
	beq	.L525
	cmp	w1, 6
	cset	w5, eq
	cmp	w1, 1
	cset	w4, eq
	cmp	w1, 15
	cset	w0, eq
	mov	w6, w5
	orr	w4, w4, w0
.L520:
	add	x0, x20, 458752
	mov	w2, 1
	strb	w2, [x19, 2]
	mov	x2, 104
	movk	x2, 0x7, lsl 16
	ldr	w3, [x0, 196]
	add	x2, x20, x2
	str	w3, [x19, 4]
	ldr	x3, [x0, 184]
	str	x3, [x19, 8]
	ldr	w3, [x0, 208]
	str	w3, [x19, 24]
	ldr	w7, [x0, 216]
	ldr	w3, [x0, 308]
	mul	w3, w3, w7
	str	w3, [x19, 28]
	ldr	w3, [x2, 24]
	str	w3, [x19, 32]
	ldp	w7, w3, [x2, 24]
	add	w3, w7, w3
	str	w3, [x19, 36]
	ldr	w3, [x0, 480]
	cmp	w3, 1
	beq	.L530
	ldr	w2, [x0, 476]
	str	w2, [x19, 40]
.L522:
	mov	w2, 1
	strb	w2, [x19]
	ldr	w3, [x20, 48]
	str	w3, [x19, 52]
	str	w6, [x19, 68]
	cbnz	w4, .L526
	sub	w3, w1, #2
	cmp	w3, 1
	cset	w3, ls
	orr	w5, w5, w3
	cbnz	w5, .L531
	strb	wzr, [x19, 1]
.L532:
	mov	w2, 1
	stp	w1, w2, [x19, 44]
	stp	w2, w2, [x19, 56]
	ldr	w0, [x0, 456]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L531:
	strb	w2, [x19, 1]
	mov	w2, 1
	stp	w1, w2, [x19, 44]
	stp	w2, w2, [x19, 56]
	ldr	w0, [x0, 456]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L526:
	mov	w1, 0
	strb	wzr, [x19, 1]
	b	.L532
	.p2align 3
.L530:
	ldr	w2, [x2, 36]
	add	w2, w2, 3
	and	w2, w2, -4
	str	w2, [x19, 40]
	b	.L522
	.p2align 3
.L525:
	mov	w5, 1
	mov	w4, 0
	mov	w6, w5
	mov	w1, 6
	b	.L520
	.size	SCDDRV_SetCtrlReg, .-SCDDRV_SetCtrlReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_RecordStartState
	.type	SCDDRV_RecordStartState, %function
SCDDRV_RecordStartState:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 458752
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	cmp	w22, w21
	str	w22, [x19, 280]
	str	w21, [x19, 284]
	bls	.L536
	strb	wzr, [x20, 2]
.L535:
	mov	w1, 1
	ldr	x0, .LC133
	str	w1, [x19, 240]
	strb	wzr, [x20, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 304]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L536:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L535
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	3
.LC133:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_ConfigReg
	.type	SCD_ConfigReg, %function
SCD_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x19, w2
	mov	x22, x3
	bl	_mcount
	ldr	x0, .LC134
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L544
	cmp	w20, 4
	ldr	x22, .LC135
	beq	.L545
.L540:
	add	x19, x22, x19, lsl 2
	mov	w1, w21
	ldr	w0, [x19, 8]
	add	w0, w20, w0
	bl	MEM_WritePhyWord
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L544:
	mov	w3, w21
	mov	w2, w20
	mov	x0, x22
	mov	w1, 1
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L545:
	add	x0, x22, x19, lsl 2
	ldr	w0, [x0, 8]
	add	w0, w0, 4
	cbnz	w21, .L541
	bl	MEM_ReadPhyWord
	uxth	w21, w0
	b	.L540
	.p2align 3
.L541:
	bl	MEM_ReadPhyWord
	orr	w21, w0, 65536
	b	.L540
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	3
.LC134:
	.xword	g_HalDisable
	.align	3
.LC135:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	stp	x29, x30, [sp, -272]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w24, w0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	ldr	x20, .LC136
	ldrb	w0, [x20]
	cmp	w0, 1
	beq	.L547
	ldr	x3, .LC137
	add	x0, x29, 80
	mov	x2, 188
	mov	w1, 0
	mov	x23, x0
	ldr	x3, [x3, 96]
	blr	x3
.L548:
	ldrb	w0, [x20]
	ldr	w1, [x19, 4]
	cmp	w0, 1
	bne	.L585
	ldr	x22, .LC138
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2052
	bl	MEM_WritePhyWord
.L550:
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	bne	.L586
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2056
	bl	MEM_WritePhyWord
.L552:
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	bne	.L587
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2060
	bl	MEM_WritePhyWord
.L554:
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	bne	.L588
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2064
	bl	MEM_WritePhyWord
.L556:
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	bne	.L589
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2068
	bl	MEM_WritePhyWord
.L558:
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	bne	.L590
	add	x0, x22, x21, sxtw 2
	sxtw	x25, w24
	ldr	w0, [x0, 8]
	add	w0, w0, 2072
	bl	MEM_WritePhyWord
	add	x0, x22, x25, lsl 4
	ldr	x0, [x0, 16]
	add	x0, x0, 458752
	ldr	w1, [x0, 480]
	cmp	w1, 1
	beq	.L591
.L561:
	mov	w2, 3
	ldr	w1, [x0, 464]
	movk	w2, 0x300, lsl 16
	cmp	w1, w2
	beq	.L592
.L566:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L593
	add	x0, x22, x21, sxtw 2
	add	x25, x22, x25, lsl 4
	ldr	w0, [x0, 8]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	cmp	w0, 1
	ldr	x0, [x25, 16]
	add	x0, x0, 458752
	ldrh	w1, [x0, 460]
	bne	.L594
.L572:
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
.L565:
	ldp	w0, w4, [x19, 52]
	ldr	w2, [x19, 44]
	ldr	w5, [x19, 60]
	lsl	w0, w0, 8
	and	w2, w2, 15
	ldrb	w1, [x19, 1]
	orr	w2, w2, w4, lsl 13
	ldrb	w4, [x20]
	orr	w3, w0, w5, lsl 9
	ubfiz	w1, w1, 4, 1
	cmp	w4, 1
	orr	w0, w3, w2
	orr	w1, w0, w1
	bne	.L595
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2080
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 52]
	cbnz	w0, .L596
.L575:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L597
	add	x0, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x0, 8]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldrb	w25, [x20]
	cmp	w25, 1
	beq	.L579
.L600:
	ldr	w1, [x19, 52]
	add	x0, x29, 80
	strb	w21, [x29, 80]
	strb	w1, [x29, 81]
	stp	wzr, w24, [x29, 84]
	bl	VDH_PostTask
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L592:
	ldrh	w0, [x0, 460]
	cbnz	w0, .L566
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L598
	add	x0, x22, x21, sxtw 2
	mov	w1, 3
	ldr	w0, [x0, 8]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
.L568:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L599
	add	x0, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x0, 8]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
	b	.L565
	.p2align 3
.L593:
	mov	w3, w1
	mov	x0, x23
	mov	w1, 1
	mov	w2, 2108
	add	x25, x22, x25, lsl 4
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	cmp	w0, 1
	ldr	x0, [x25, 16]
	add	x0, x0, 458752
	ldrh	w1, [x0, 460]
	beq	.L572
.L594:
	mov	w3, w1
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L565
	.p2align 3
.L597:
	mov	w3, 0
	mov	w2, 2076
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	ldrb	w25, [x20]
	cmp	w25, 1
	bne	.L600
.L579:
	add	x21, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x21, 8]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldrb	w1, [x19, 2]
	cmp	w0, 1
	and	w1, w1, 1
	bne	.L601
	ldr	w0, [x21, 8]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L595:
	mov	w3, w1
	mov	x0, x23
	mov	w2, 2080
	mov	w1, 1
	bl	VDH_Record_RegData
	ldr	w0, [x19, 52]
	cbz	w0, .L575
.L596:
	ldrb	w0, [x20]
	ldr	w1, [x19, 68]
	cmp	w0, 1
	bne	.L602
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 8]
	bl	MEM_WritePhyWord
	b	.L575
	.p2align 3
.L590:
	mov	w3, w1
	mov	x0, x23
	mov	w1, 1
	mov	w2, 2072
	sxtw	x25, w24
	bl	VDH_Record_RegData
	add	x0, x22, x25, lsl 4
	ldr	x0, [x0, 16]
	add	x0, x0, 458752
	ldr	w1, [x0, 480]
	cmp	w1, 1
	bne	.L561
.L591:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L603
	add	x0, x22, x21, sxtw 2
	mov	w1, -1
	ldr	w0, [x0, 8]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
.L563:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L604
	add	x0, x22, x21, sxtw 2
	mov	w1, -1
	ldr	w0, [x0, 8]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
	b	.L565
	.p2align 3
.L589:
	mov	w3, w1
	mov	w2, 2068
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L558
	.p2align 3
.L588:
	mov	w3, w1
	mov	w2, 2064
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L556
	.p2align 3
.L587:
	mov	w3, w1
	mov	w2, 2060
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L554
	.p2align 3
.L586:
	mov	w3, w1
	mov	w2, 2056
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L552
	.p2align 3
.L585:
	mov	w3, w1
	mov	w2, 2052
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	ldr	x22, .LC138
	b	.L550
	.p2align 3
.L547:
	mov	w0, w21
	mov	x23, 0
	bl	ResetSCD
	b	.L548
	.p2align 3
.L602:
	mov	w3, w1
	mov	w2, 0
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L575
	.p2align 3
.L601:
	mov	w3, w1
	mov	x0, x23
	mov	w1, w25
	mov	w2, 2048
	bl	VDH_Record_RegData
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L603:
	mov	w3, -1
	mov	w2, 2108
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L563
	.p2align 3
.L604:
	mov	w3, -1
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L565
	.p2align 3
.L598:
	mov	w3, 3
	mov	w2, 2108
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L568
	.p2align 3
.L599:
	mov	w3, 0
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L565
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	3
.LC136:
	.xword	g_HalDisable
	.align	3
.LC137:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC138:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w26, w0
	mov	x27, x1
	mov	x0, x30
	mov	x25, x4
	sxtw	x1, w26
	mov	x22, x3
	mov	x19, x1
	mov	w23, w2
	stp	w6, w5, [x29, 116]
	str	x1, [x29, 104]
	str	w2, [x29, 124]
	bl	_mcount
	ldr	x0, .LC141
	mov	x2, 16384
	ldr	x11, .LC142
	mov	w1, 0
	add	x0, x0, x19, lsl 4
	str	x11, [x29, 136]
	stp	xzr, xzr, [x29, 144]
	ldr	x3, [x11, 96]
	ldr	x0, [x0, 16]
	stp	xzr, xzr, [x29, 160]
	add	x0, x0, 458752
	add	x20, x0, 592
	mov	x21, x0
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x29, 224]
	add	x19, x0, 472
	mov	x0, x20
	str	x21, [x29, 96]
	add	x28, x21, 468
	blr	x3
	str	x22, [x29, 128]
	add	x1, x29, 144
	mov	x0, x22
	bl	GetFirstRawPacket
	ldr	w26, [x29, 152]
	stp	wzr, wzr, [x25]
	str	wzr, [x25, 8]
	cmp	w26, w23
	str	wzr, [x27, 4]
	bgt	.L606
	ldp	x0, x11, [x29, 128]
	mov	w23, 0
	mov	w22, 0
	mov	w24, 0
	mov	w12, w26
	add	x21, x0, 98304
	.p2align 2
.L609:
	cmp	w12, wzr
	ubfiz	x14, x23, 4, 32
	add	x15, x25, x22, sxtw 2
	mov	x2, 96
	add	x0, x29, 144
	add	x13, x20, x14
	add	w24, w24, 1
	ble	.L607
	ldr	w1, [x29, 148]
	add	w23, w23, 1
	str	w1, [x25, w22, sxtw 2]
	add	w22, w22, 3
	ldr	w3, [x29, 120]
	sub	w1, w1, #1
	add	w1, w1, w12
	ldr	x16, [x29, 184]
	add	w12, w3, w22, lsl 2
	stp	w1, w12, [x15, 4]
	str	x16, [x20, x14]
	ldr	x1, [x29, 184]
	ldrsw	x12, [x29, 152]
	sub	x1, x1, #1
	add	x1, x1, x12
	str	x1, [x13, 8]
	str	wzr, [x29, 152]
.L607:
	str	w26, [x27, 4]
	ldr	w12, [x21, 4]
	ldr	w1, [x21, 16]
	cmp	w1, w12
	sxtw	x1, w1
	lsl	x12, x1, 2
	bne	.L661
	ldr	w0, [x29, 116]
	cbz	w0, .L662
.L610:
	cbz	w24, .L627
	cmp	w22, wzr
	ble	.L613
	add	x3, x25, x22, sxtw 2
	str	wzr, [x3, -4]
.L613:
	ldr	x0, [x29, 104]
	mov	w2, 6
	ldr	x1, .LC141
	ldr	w4, [x27, 4]
	add	x26, x1, x0, lsl 4
	cmp	w4, w2
	csel	w4, w4, w2, le
	ldr	x0, [x26, 16]
	cmp	w4, 5
	add	x0, x0, 458752
	ldr	w1, [x0, 472]
	str	w1, [x0, 464]
	ldrh	w1, [x0, 468]
	strh	w1, [x0, 460]
	bls	.L663
.L630:
	mov	w10, 2
	mov	w9, 4
.L614:
	cmp	w23, wzr
	mov	w8, w23
	mov	x11, -16
	ble	.L623
	.p2align 2
.L645:
	add	x0, x11, x8, sxtw 4
	add	x1, x20, x0
	ldr	x3, [x20, x0]
	ldr	x2, [x1, 8]
	add	w0, w2, 1
	sub	w3, w0, w3
	cmp	w3, w9
	csel	w4, w3, w9, ls
	cbz	w9, .L619
	cbz	w4, .L622
	mov	x0, 0
	.p2align 2
.L621:
	neg	x1, x0
	ldrb	w1, [x1, x2]
	strb	w1, [x19, x0]
	add	x0, x0, 1
	cmp	w4, w0
	bhi	.L621
	sub	w0, w4, #1
	subs	w9, w9, w4
	add	x0, x0, 1
	add	x19, x19, x0
	beq	.L619
.L622:
	subs	w8, w8, #1
	bne	.L645
	.p2align 2
.L623:
	mov	w0, 1
	str	w24, [x27]
	str	w0, [x27, 8]
	mov	w0, 0
.L658:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L661:
	sub	x1, x12, x1
	ldr	x3, [x29, 128]
	ldr	x12, [x11, 104]
	add	x1, x3, x1, lsl 5
	str	x11, [x29, 136]
	blr	x12
	ldr	w0, [x21, 16]
	ldr	w12, [x29, 152]
	add	w0, w0, 1
	ldr	w1, [x29, 124]
	asr	w2, w0, 31
	add	w26, w26, w12
	lsr	w2, w2, 22
	cmp	w1, w26
	add	w0, w0, w2
	mov	w1, 1023
	and	w0, w0, w1
	ccmp	w24, w1, 0, ge
	sub	w0, w0, w2
	str	w0, [x21, 16]
	ldr	x11, [x29, 136]
	ble	.L609
	ldr	w0, [x29, 116]
	cbnz	w0, .L610
.L662:
	ldr	w0, [x29, 152]
	cbz	w0, .L610
.L628:
	ldr	w3, [x29, 124]
	ldr	w1, [x27, 4]
	sub	w2, w3, #16
	cmp	w1, w2
	bge	.L610
	cmp	w3, w26
	mov	w2, 1023
	ccmp	w24, w2, 0, lt
	bgt	.L610
	sub	w1, w3, w1
	cmp	w1, w0
	bgt	.L610
	ldr	w0, [x29, 148]
	add	w24, w24, 1
	str	w0, [x25, w22, sxtw 2]
	sub	w0, w0, #1
	str	w1, [x29, 152]
	add	w1, w0, w1
	add	x0, x25, x22, sxtw 2
	add	w22, w22, 3
	str	w1, [x0, 4]
	ldr	w1, [x29, 120]
	add	w1, w1, w22, lsl 2
	str	w1, [x0, 8]
	ubfiz	x0, x23, 4, 32
	ldr	x1, [x29, 184]
	add	w23, w23, 1
	str	x1, [x20, x0]
	add	x0, x20, x0
	ldr	x1, [x29, 184]
	sub	x2, x1, #1
	ldrsw	x1, [x29, 152]
	add	x1, x2, x1
	str	x1, [x0, 8]
	ldr	w1, [x27, 4]
	ldr	w0, [x29, 152]
	str	wzr, [x29, 152]
	add	w0, w1, w0
	str	w0, [x27, 4]
	b	.L610
	.p2align 3
.L619:
	cbz	w10, .L623
	sub	w1, w3, w4
	sub	x2, x2, x4, uxtw
	cmp	w1, w10
	csel	w1, w1, w10, ls
	cbz	w1, .L659
	mov	x0, 0
	.p2align 2
.L625:
	neg	x3, x0
	ldrb	w3, [x3, x2]
	strb	w3, [x28, x0]
	add	x0, x0, 1
	cmp	w1, w0
	bhi	.L625
	sub	w0, w1, #1
	subs	w10, w10, w1
	add	x0, x0, 1
	add	x28, x28, x0
	beq	.L623
.L659:
	mov	w9, 0
	b	.L622
.L663:
	cmp	w4, 1
	beq	.L664
	mov	x0, 3
	sub	w9, w4, #2
	sub	x9, x0, x9
	subs	w2, w2, w4
	ldr	x0, [x29, 96]
	add	x12, x0, 469
	beq	.L630
	mov	w0, 0
	mov	w11, 2
	.p2align 2
.L616:
	uxtw	x1, w0
	sub	w2, w2, #1
	sub	x3, x9, x1
	sub	x1, x12, x1
	add	w0, w0, 1
	cmp	w2, wzr
	ccmp	w0, 1, 2, ne
	sub	w10, w11, w0
	ldrb	w3, [x19, x3]
	strb	w3, [x1]
	bls	.L616
	mov	w9, 4
	cbnz	w10, .L614
	ldr	x0, [x29, 96]
	add	x25, x0, 475
	mov	x0, 3
	sub	x4, x0, x4, uxtw
	cbz	w2, .L614
	mov	w1, 0
	.p2align 2
.L617:
	uxtw	x0, w1
	add	w1, w1, 1
	sub	x3, x4, x0
	sub	x0, x25, x0
	cmp	w2, w1
	ldrb	w3, [x19, x3]
	strb	w3, [x0]
	bne	.L617
	mov	w9, 4
	sub	w9, w9, w2
	b	.L614
.L664:
	ldr	x2, [x29, 96]
	mov	w10, 0
	mov	w9, w4
	ldrb	w0, [x2, 475]
	ldrb	w1, [x2, 468]
	strb	w0, [x2, 468]
	ldrb	w0, [x2, 473]
	strb	w1, [x2, 469]
	ldrb	w1, [x2, 474]
	strb	w0, [x2, 474]
	ldrb	w0, [x2, 472]
	strb	w1, [x2, 475]
	strb	w0, [x2, 473]
	b	.L614
.L606:
	ldr	w0, [x29, 116]
	cbnz	w0, .L627
	cbz	w26, .L627
	mov	w0, w26
	mov	w23, 0
	mov	w22, 0
	mov	w24, 0
	b	.L628
.L627:
	mov	w0, -6
	b	.L658
	.size	WriteScdMsg, .-WriteScdMsg
	.align	3
.LC141:
	.xword	.LANCHOR0
	.align	3
.LC142:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_StartSCD
	.type	SCDDRV_StartSCD, %function
SCDDRV_StartSCD:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	add	x19, x1, 458752
	mov	x22, x0
	mov	x0, x30
	mov	x20, x1
	mov	w24, w2
	mov	w26, w3
	bl	_mcount
	add	x21, x19, 160
	ldr	w0, [x19, 232]
	add	x20, x20, 80
	ldr	w27, [x19, 196]
	ldr	x25, [x19, 184]
	bl	VCTRL_IfEsBufEnable
	cbz	w0, .L669
	ldr	x23, .LC145
	mov	x2, 12
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x23, 96]
	blr	x3
	ldr	w0, [x19, 232]
	mov	x3, x20
	ldr	w6, [x22, 52]
	mov	w5, w27
	mov	x4, x25
	mov	w2, w24
	mov	x1, x21
	bl	WriteScdMsg
	mov	w20, w0
	cbnz	w0, .L667
	ldr	x0, [x23]
	blr	x0
	ldr	x3, .LC146
	sbfiz	x1, x26, 6, 32
	mov	w2, w26
	add	x3, x3, x1
	mov	x1, x22
	str	w0, [x3, 48]
	ldr	w0, [x19, 232]
	bl	WriteScdVtrlReg
.L667:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L669:
	ldr	x1, .LC144
	mov	w0, 1
	ldr	w2, [x19, 232]
	mov	w20, -7
	bl	dprint_vfmw
	b	.L667
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC145:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC146:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x20, x21, 458752
	bl	_mcount
	str	wzr, [x29, 64]
	add	x6, x29, 144
	add	x1, x21, 98304
	ldr	w2, [x20, 488]
	add	x5, x29, 60
	add	x4, x29, 64
	add	x3, x29, 56
	str	wzr, [x6, -76]!
	add	x1, x1, 104
	add	x0, x21, 80
	stp	wzr, wzr, [x29, 56]
	bl	SCDDRV_CheckConditionOfStartSCD
	mov	w19, w0
	cbnz	w0, .L681
	ldr	w0, [x29, 68]
	cbnz	w0, .L682
.L673:
	ldr	w0, [x20, 232]
	mov	w1, w22
	bl	SM_CfgBuf
	mov	w19, w0
	cbnz	w0, .L683
	ldr	w3, [x20, 308]
	mov	x0, x21
	ldr	w2, [x29, 60]
	add	x1, x29, 72
	str	w2, [x20, 216]
	mul	w2, w2, w3
	lsl	w2, w2, 2
	str	w2, [x20, 212]
	bl	SCDDRV_SetCtrlReg
	ldr	w2, [x29, 64]
	mov	w3, w22
	mov	x1, x21
	add	x0, x29, 72
	bl	SCDDRV_StartSCD
	mov	w2, w0
	cbnz	w0, .L672
	ldr	w1, [x29, 56]
	ldr	w0, [x29, 64]
	str	w1, [x20, 280]
	cmp	w1, w0
	str	w0, [x20, 284]
	bls	.L684
	strb	wzr, [x21, 2]
.L676:
	mov	w1, 1
	ldr	x0, .LC149
	str	w1, [x20, 240]
	strb	wzr, [x21, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x20, 304]
	mov	w2, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L683:
	ldr	x1, .LC151
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w2, w19
.L672:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L682:
	add	x4, x20, 256
	ldr	x2, .LC149
	mov	w0, -1
	strh	w0, [x20, 460]
	strh	w0, [x20, 468]
	mov	w1, 1
	str	w0, [x20, 464]
	ldr	x3, [x2, 96]
	mov	x2, 88
	stp	w0, wzr, [x4, 216]
	stp	w1, wzr, [x4, 224]
	str	wzr, [x20, 488]
	mov	w1, 0
	str	wzr, [x20, 492]
	add	x0, x20, 504
	str	wzr, [x20, 496]
	blr	x3
	b	.L673
	.p2align 3
.L681:
	ldr	x1, .LC148
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w2, w19
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L684:
	mov	w0, 1
	strb	w0, [x21, 2]
	b	.L676
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC149:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC151:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x1, .LC152
	add	x19, x1, x19, sxtw 2
	ldr	w0, [x19, 8]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	str	w0, [x20]
	ldr	w0, [x19, 8]
	add	w0, w0, 2124
	bl	MEM_ReadPhyWord
	lsr	w0, w0, 22
	ldr	w1, [x19, 8]
	str	w0, [x20, 8]
	add	w0, w1, 2124
	bl	MEM_ReadPhyWord
	and	w0, w0, 4194303
	ldr	w1, [x19, 8]
	str	w0, [x20, 12]
	add	w0, w1, 2128
	bl	MEM_ReadPhyWord
	str	w0, [x20, 16]
	ldr	w1, [x19, 8]
	add	w0, w1, 2132
	bl	MEM_ReadPhyWord
	str	w0, [x20, 20]
	ldr	w1, [x19, 8]
	add	w0, w1, 2060
	bl	MEM_ReadPhyWord
	str	w0, [x20, 24]
	ldr	w1, [x19, 8]
	add	w0, w1, 2140
	bl	MEM_ReadPhyWord
	str	w0, [x20, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	3
.LC152:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ParseMpeg4UniqueUpMsg
	.type	ParseMpeg4UniqueUpMsg, %function
ParseMpeg4UniqueUpMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	cmp	w21, 1
	ldrb	w0, [x19]
	beq	.L689
	orr	w0, w0, 1
	strb	w0, [x19]
.L688:
	ldr	w1, [x20, 4]
	ldrb	w0, [x19]
	lsr	w1, w1, 30
	bfi	w0, w1, 1, 1
	strb	w0, [x19]
	ldrh	w1, [x20, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x19]
	ldr	w1, [x20, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x19]
	ldr	w0, [x20, 8]
	ldrh	w1, [x19]
	and	w0, w0, 7
	bfi	w1, w0, 7, 4
	strh	w1, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L689:
	and	w0, w0, -2
	strb	w0, [x19]
	b	.L688
	.size	ParseMpeg4UniqueUpMsg, .-ParseMpeg4UniqueUpMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ConvertByteOrder
	.type	ConvertByteOrder, %function
ConvertByteOrder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	rev	w0, w0
	ldp	x29, x30, [sp], 32
	ret
	.size	ConvertByteOrder, .-ConvertByteOrder
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckSegValid
	.type	CheckSegValid, %function
CheckSegValid:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x20, .L696
	ldr	w0, [x20, 16]
	cbz	w0, .L698
	ldr	x0, [x20]
	cbz	x0, .L698
	add	x1, x19, 360448
	ldp	w2, w0, [x1, 32]
	cmp	w0, w2
	sub	w2, w2, #1
	bhi	.L700
	sub	w0, w2, w0
	bcc	.L694
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L694:
	ldr	w2, [x20, 20]
	mov	w1, -7
	cmp	w2, w0
	csel	w0, wzr, w1, ls
.L692:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L700:
	ldr	w1, [x1, 28]
	add	w2, w2, w1
	sub	w0, w2, w0
	b	.L694
	.p2align 3
.L698:
	mov	w0, -7
	b	.L692
.L696:
	mov	w0, -1
	b	.L692
	.size	CheckSegValid, .-CheckSegValid
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x3
	mov	x21, x2
	mov	w22, w1
	bl	_mcount
	add	x4, x29, 64
	add	x2, x29, 52
	mov	w1, w22
	add	x3, x29, 56
	mov	x0, x20
	str	wzr, [x4, -4]!
	stp	wzr, wzr, [x29, 52]
	bl	GetRawNumOffset
	ldr	w1, [x29, 60]
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x20, x0, lsl 5
	ldr	x1, [x0, 64]
	str	x1, [x19, 32]
	ldr	x2, [x0, 48]
	str	x2, [x19, 48]
	ldr	x2, [x0, 64]
	str	x2, [x19, 40]
	ldr	x2, [x0, 56]
	str	x2, [x19, 56]
	ldr	w2, [x0, 20]
	str	w2, [x19, 64]
	ldr	w2, [x0, 24]
	str	w2, [x19, 68]
	ldr	w2, [x0, 28]
	str	w2, [x19, 72]
	ldr	w0, [x0, 32]
	str	w0, [x19, 76]
	ldr	x0, [x21]
	cmp	x1, x0
	beq	.L704
	str	x1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L704:
	mov	x0, -1
	str	x0, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	GetSegPts, .-GetSegPts
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsVopHeader
	.type	IsVopHeader, %function
IsVopHeader:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 1
	beq	.L710
	cmp	w19, 2
	mov	w0, 0
	beq	.L711
	mov	w1, -33488896
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L710:
	mov	w0, -1241448448
	mov	w1, -33488896
	cmp	w20, w0
	cset	w0, eq
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L711:
	ubfx	x0, x20, 16, 8
	mov	w1, -33488896
	sub	w0, w0, #128
	cmp	w0, 3
	cset	w0, ls
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	IsVopHeader, .-IsVopHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x20, x1
	bl	_mcount
	add	x4, x21, 98304
	sub	w3, w19, #1
	add	x2, x4, 104
	mov	w0, 4096
	add	x2, x2, 360448
	mov	w5, w3
	ldp	w10, w1, [x2, 8]
	sub	w10, w1, w10
	and	w10, w10, 4095
	sub	w10, w0, w10
	tbnz	w3, #31, .L720
	add	x21, x21, 458752
	ldr	w1, [x2, 24]
	ldr	x7, [x4, 104]
	mov	w8, -33488896
	mov	w11, -1241448448
	ldr	w2, [x21, 308]
	ldr	w6, [x21, 252]
	mul	w4, w3, w2
	b	.L719
	.p2align 3
.L714:
	cmp	w6, 2
	beq	.L722
	cmp	w0, w8
	beq	.L717
.L718:
	sub	w5, w5, #1
	mov	w19, w3
	cmn	w5, #1
	sub	w4, w4, w2
	beq	.L720
.L723:
	sub	w3, w3, #1
.L719:
	ldr	w0, [x20, w4, uxtw 2]
	cmp	w6, 1
	sub	w0, w0, w1
	ldr	w0, [x7, x0]
	bne	.L714
	cmp	w0, w11
	cset	w9, eq
.L715:
	cmp	w0, w8
	beq	.L717
	cbz	w9, .L718
	.p2align 2
.L717:
	cmp	w10, w3
	mov	w19, w3
	bcs	.L720
	sub	w5, w5, #1
	sub	w3, w3, #1
	cmn	w5, #1
	mov	w19, w3
	sub	w4, w4, w2
	bne	.L723
.L720:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L722:
	ubfx	x9, x0, 16, 8
	sub	w9, w9, #128
	cmp	w9, 3
	cset	w9, ls
	b	.L715
	.size	GetNextVop, .-GetNextVop
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CorrectRollPhyAddr
	.type	CorrectRollPhyAddr, %function
CorrectRollPhyAddr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	bl	_mcount
	cmp	w20, w21
	mov	w0, w19
	bcs	.L725
	sub	w0, w20, w21
	add	w0, w0, w19
.L725:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	CorrectRollPhyAddr, .-CorrectRollPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CorrectSegNextAddr
	.type	CorrectSegNextAddr, %function
CorrectSegNextAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, w19
	csel	w0, w20, w19, cs
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CorrectSegNextAddr, .-CorrectSegNextAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetLastUnfinishedSegInfo
	.type	SetLastUnfinishedSegInfo, %function
SetLastUnfinishedSegInfo:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w1
	mov	x22, x2
	bl	_mcount
	add	x19, x21, 458752
	add	x0, x29, 88
	add	x1, x29, 120
	str	xzr, [x29, 168]
	add	x24, x19, 504
	ldr	x23, [x19, 200]
	mov	x3, x24
	stp	xzr, xzr, [x0]
	add	x0, x29, 104
	add	x2, x19, 272
	stp	xzr, xzr, [x1]
	add	x1, x29, 136
	add	x25, x21, 98304
	stp	xzr, xzr, [x0]
	ldr	w0, [x19, 308]
	stp	xzr, xzr, [x1]
	add	x1, x29, 152
	mul	w20, w0, w20
	add	x0, x21, 80
	stp	xzr, xzr, [x1]
	add	w1, w20, 1
	ldr	w1, [x23, w1, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	x0, .LC153
	mov	x2, 88
	mov	x1, x24
	ldr	x3, [x0, 104]
	add	x0, x29, x2
	blr	x3
	ldr	w5, [x23, w20, uxtw 2]
	add	x23, x25, 104
	add	x1, x23, 360448
	str	w5, [x19, 484]
	ldr	w0, [x22, 28]
	ldr	w4, [x1, 24]
	cmp	w0, w4
	csel	w0, w0, w4, cs
	str	w0, [x19, 476]
	cmp	w5, w0
	bls	.L729
	mov	w1, 1
	str	w1, [x19, 492]
	ldr	w2, [x22, 28]
	ldr	w1, [x22, 16]
	cmp	w4, w2
	bls	.L730
	add	w1, w1, w2
	sub	w1, w1, w4
.L730:
	sub	w3, w1, w5
	sub	w20, w0, w4
	add	w0, w3, w20
	str	w1, [x19, 496]
	str	w0, [x19, 488]
	ldr	w21, [x21, 52]
	cmp	w21, 1
	beq	.L740
.L732:
	str	wzr, [x19, 480]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L729:
	sub	w3, w0, w5
	str	wzr, [x19, 492]
	str	w3, [x19, 488]
	str	wzr, [x19, 496]
	ldr	w0, [x21, 52]
	cmp	w0, 1
	ccmp	w3, 3, 0, eq
	bls	.L732
	ldr	x6, [x25, 104]
	sub	w4, w5, w4
	ldr	w2, [x19, 232]
	mov	w7, 1
	add	x4, x6, x4
	add	x1, x29, 88
	mov	w6, 2
	mov	x0, x23
	strb	w7, [x29, 98]
	strb	w6, [x29, 97]
	str	x4, [x29, 88]
	stp	w5, w3, [x29, 104]
	bl	InsertStreamSeg
	b	.L732
	.p2align 3
.L740:
	add	x22, x25, 104
	mov	w6, 4096
	add	x22, x22, 360448
	ldp	w1, w2, [x22, 8]
	sub	w1, w2, w1
	and	w1, w1, 4095
	sub	w1, w6, w1
	cmp	w1, 3
	ccmp	w0, 3, 0, hi
	bls	.L732
	ldr	x0, [x25, 104]
	sub	w4, w5, w4
	ldr	w2, [x19, 232]
	add	x1, x29, 88
	add	x4, x0, x4
	mov	x0, x23
	mov	w24, 2
	str	x4, [x29, 88]
	stp	w5, w3, [x29, 104]
	strb	wzr, [x29, 98]
	strb	w24, [x29, 97]
	bl	InsertStreamSeg
	ldr	w4, [x22, 24]
	add	x1, x29, 88
	ldr	x3, [x25, 104]
	mov	x0, x23
	ldr	w2, [x19, 232]
	strb	w21, [x29, 98]
	strb	w24, [x29, 97]
	str	x3, [x29, 88]
	stp	w4, w20, [x29, 104]
	bl	InsertStreamSeg
	b	.L732
	.size	SetLastUnfinishedSegInfo, .-SetLastUnfinishedSegInfo
	.align	3
.LC153:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSegRoll
	.type	ProcessSegRoll, %function
ProcessSegRoll:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x19, x1
	add	x27, x20, 458752
	sxtb	w1, w4
	mov	x0, x30
	add	x20, x20, 98304
	mov	w25, w2
	sxtb	w22, w3
	str	w1, [x29, 108]
	add	x21, x20, 104
	bl	_mcount
	add	x28, x21, 360448
	ldr	x0, [x27, 200]
	ldr	w1, [x27, 484]
	ldr	w2, [x28, 8]
	ldr	w24, [x0]
	sub	w25, w25, w1
	ldr	w26, [x28, 24]
	ldr	w0, [x28, 12]
	str	w1, [x19, 16]
	sub	w24, w24, w26
	sub	w0, w0, w2
	add	w3, w25, w24
	ldr	w2, [x28, 24]
	cmp	w3, 3
	and	w0, w0, 4095
	sub	w1, w1, w2
	ldr	x2, [x20, 104]
	str	w3, [x19, 20]
	add	x1, x2, x1
	str	x1, [x19]
	mov	w1, 4096
	sub	w0, w1, w0
	bls	.L747
	cmp	w0, 2
	bls	.L746
	mov	x1, x21
	mov	x0, x19
	bl	CheckSegValid
	mov	w23, w0
	cbnz	w0, .L746
	str	w25, [x19, 20]
	cbz	w24, .L748
	strb	wzr, [x19, 10]
	mov	x1, x19
	strb	w22, [x19, 9]
	mov	x0, x21
	ldr	w2, [x27, 232]
	bl	InsertStreamSeg
	str	w26, [x19, 16]
	mov	w3, 1
	mov	x0, x21
	ldr	w2, [x28, 24]
	ldr	x1, [x20, 104]
	sub	w26, w26, w2
	ldrb	w2, [x29, 108]
	add	x26, x1, x26
	strb	w3, [x19, 10]
	strb	w2, [x19, 9]
	mov	x1, x19
	str	x26, [x19]
	str	w24, [x19, 20]
	ldr	w2, [x27, 232]
	bl	InsertStreamSeg
.L743:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L748:
	strb	w22, [x19, 9]
	mov	w0, 1
	strb	w0, [x19, 10]
	mov	x1, x19
	mov	x0, x21
	ldr	w2, [x27, 232]
	bl	InsertStreamSeg
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L747:
	ldr	x1, .LC155
	mov	w2, 2842
	mov	w0, 0
	mov	w23, 0
	bl	dprint_vfmw
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L746:
	mov	w23, -4
	b	.L743
	.size	ProcessSegRoll, .-ProcessSegRoll
	.align	3
.LC155:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessLastUnfinishedSeg
	.type	ProcessLastUnfinishedSeg, %function
ProcessLastUnfinishedSeg:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	w23, w1
	bl	_mcount
	add	x21, x19, 98304
	add	x1, x29, 72
	add	x0, x21, 104
	add	x0, x0, 360448
	ldr	w3, [x20, 28]
	str	xzr, [x29, 152]
	stp	xzr, xzr, [x1]
	add	x1, x29, 88
	ldr	w2, [x0, 24]
	ldr	w22, [x20, 16]
	cmp	w2, w3
	stp	xzr, xzr, [x1]
	add	x1, x29, 104
	stp	xzr, xzr, [x1]
	add	x1, x29, 120
	stp	xzr, xzr, [x1]
	add	x1, x29, 136
	stp	xzr, xzr, [x1]
	bls	.L750
	add	w3, w22, w3
	sub	w22, w3, w2
.L750:
	cbnz	w23, .L751
	add	x0, x19, 458752
	ldr	w1, [x0, 284]
	ldr	w3, [x0, 280]
	cmp	w3, w1
	cset	w1, gt
	strb	w1, [x19]
	ldr	w4, [x0, 484]
	cbz	w4, .L762
	ldr	w3, [x0, 488]
	ldr	w1, [x0, 164]
	ldr	w5, [x0, 492]
	add	w3, w3, w1
	str	w3, [x0, 488]
	cbnz	w5, .L754
	ldr	w3, [x20, 28]
	cmp	w4, w3
	bls	.L754
	mov	w3, 1
	str	w22, [x0, 496]
	str	w3, [x0, 492]
.L754:
	str	wzr, [x0, 480]
	ldr	w3, [x20, 28]
	cmp	w3, w2
	csel	w2, w3, w2, cs
	str	w2, [x0, 476]
.L753:
	add	x0, x19, 80
	bl	DeleteRawLen
	mov	w20, w0
.L755:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L751:
	add	x23, x19, 458752
	strb	wzr, [x19]
	mov	w20, 0
	ldr	w0, [x23, 484]
	cbz	w0, .L755
	ldr	x3, .LC156
	mov	x2, 88
	add	x1, x23, 504
	add	x0, x29, 72
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w3, [x23, 492]
	cmp	w3, 1
	beq	.L763
	ldr	x2, [x23, 200]
	ldr	w1, [x23, 484]
	ldr	w0, [x2]
	cmp	w0, w1
	bcc	.L757
	add	x19, x21, 104
	ldr	x3, [x21, 104]
	add	x0, x19, 360448
	str	w1, [x29, 88]
	mov	w4, 1
	ldr	w0, [x0, 24]
	sub	w0, w1, w0
	add	x0, x3, x0
	str	x0, [x29, 72]
	ldr	w3, [x2]
	strb	w4, [x29, 82]
	sub	w3, w3, w1
	strb	w4, [x29, 81]
	cmp	w3, 3
	str	w3, [x29, 92]
	bls	.L764
	mov	x1, x19
	add	x0, x29, 72
	bl	CheckSegValid
	cbnz	w0, .L760
	ldr	w2, [x23, 232]
	add	x1, x29, 72
	mov	x0, x19
	bl	InsertStreamSeg
	mov	w20, w0
	b	.L755
	.p2align 3
.L762:
	ldr	w1, [x0, 164]
	b	.L753
	.p2align 3
.L757:
	mov	w4, 0
	mov	w3, 1
	mov	w2, w22
	add	x1, x29, 72
	mov	x0, x19
	bl	ProcessSegRoll
	mov	w20, w0
	b	.L755
	.p2align 3
.L764:
	ldr	x1, .LC157
	mov	w2, 2931
	mov	w0, 0
	bl	dprint_vfmw
	b	.L755
	.p2align 3
.L763:
	ldr	w2, [x23, 496]
	mov	w4, w3
	add	x1, x29, 72
	mov	x0, x19
	bl	ProcessSegRoll
	mov	w20, w0
	b	.L755
.L760:
	mov	w20, -4
	b	.L755
	.size	ProcessLastUnfinishedSeg, .-ProcessLastUnfinishedSeg
	.align	3
.LC156:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC157:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetPushRawOverState
	.type	SetPushRawOverState, %function
SetPushRawOverState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x19, 8]
	str	w20, [x19, 8]
	cmp	w0, 3
	mov	w0, -7
	ccmp	w20, 2, 0, eq
	beq	.L767
	mov	w0, 0
.L767:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetPushRawOverState, .-SetPushRawOverState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessExceptionalStartCodeNum
	.type	ProcessExceptionalStartCodeNum, %function
ProcessExceptionalStartCodeNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC159
	mov	w3, w20
	mov	w2, 2970
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	add	x0, x19, 80
	bl	DeleteRawPacket
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ProcessExceptionalStartCodeNum, .-ProcessExceptionalStartCodeNum
	.align	3
.LC159:
	.xword	.LC158
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetValidStartCodeNum
	.type	GetValidStartCodeNum, %function
GetValidStartCodeNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	w2, [x19, 24]
	ldr	w0, [x19, 12]
	udiv	w1, w2, w20
	ldp	x19, x20, [sp, 16]
	cmp	w1, w0
	csel	w0, w1, w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	GetValidStartCodeNum, .-GetValidStartCodeNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessNotMpeg4ScdUpMsg
	.type	ProcessNotMpeg4ScdUpMsg, %function
ProcessNotMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	str	x19, [x29, 96]
	mov	x28, x2
	str	w1, [x29, 124]
	bl	_mcount
	add	x0, x29, 136
	add	x22, x19, 458752
	add	x21, x19, 98304
	mov	w25, 1
	add	x21, x21, 104
	mov	w27, 0
	stp	xzr, xzr, [x0]
	add	x0, x29, 152
	ldr	w24, [x22, 308]
	mov	x23, x21
	ldr	x26, [x22, 200]
	str	xzr, [x29, 216]
	stp	xzr, xzr, [x0]
	add	x0, x29, 168
	stp	xzr, xzr, [x0]
	add	x0, x29, 184
	stp	xzr, xzr, [x0]
	add	x0, x29, 200
	stp	xzr, xzr, [x0]
	add	x0, x19, 80
	add	x19, x21, 360448
	str	x0, [x29, 112]
	sub	w0, w24, #1
	str	w0, [x29, 120]
	b	.L771
	.p2align 3
.L788:
	ldr	x4, [x23]
	sub	w3, w3, w0
	sub	w1, w0, w1
	mov	w2, 1
	stp	w0, w3, [x29, 152]
	strb	w2, [x29, 146]
	add	x0, x4, x1
	cmp	w3, 3
	str	x0, [x29, 136]
	bls	.L787
	mov	x1, x21
	add	x0, x29, 136
	bl	CheckSegValid
	cbnz	w0, .L778
	strb	wzr, [x29, 145]
	add	x2, x22, 272
	ldr	x0, [x29, 112]
	add	x3, x29, 136
	ldr	w1, [x26, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 136
	mov	x0, x21
	bl	InsertStreamSeg
	cbnz	w0, .L778
.L774:
	add	w25, w25, w24
	mov	w27, w20
.L771:
	ldr	w0, [x29, 124]
	cmp	w27, w0
	beq	.L778
	ldr	w1, [x29, 120]
	sub	w0, w25, #1
	add	w20, w27, 1
	add	w1, w1, w25
	ldr	w0, [x26, w0, uxtw 2]
	ldr	w3, [x26, w1, uxtw 2]
	ldr	w1, [x19, 24]
	cmp	w0, w3
	bls	.L788
	ldr	w2, [x28, 16]
	sub	w4, w3, w1
	ldr	x8, [x23]
	sub	w2, w2, w0
	add	w3, w2, w4
	stp	w0, w3, [x29, 152]
	sub	w0, w0, w1
	cmp	w3, 3
	add	x0, x8, x0
	str	x0, [x29, 136]
	ldr	w1, [x19, 8]
	ldr	w0, [x19, 12]
	bls	.L789
	sub	w0, w0, w1
	mov	w1, 4096
	and	w0, w0, 4095
	sub	w0, w1, w0
	cmp	w0, 2
	stp	w4, w2, [x29, 104]
	bls	.L778
	mov	x1, x21
	add	x0, x29, 136
	bl	CheckSegValid
	cbnz	w0, .L778
	ldp	w4, w2, [x29, 104]
	cbnz	w4, .L780
	str	w2, [x29, 156]
	mov	w0, 1
	strb	wzr, [x29, 145]
	add	x2, x22, 272
	strb	w0, [x29, 146]
	add	x3, x29, 136
	ldr	x0, [x29, 112]
	ldr	w1, [x26, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 136
	mov	x0, x21
	bl	InsertStreamSeg
	b	.L774
	.p2align 3
.L780:
	str	w2, [x29, 156]
	add	x3, x29, 136
	strb	wzr, [x29, 146]
	add	x2, x22, 272
	strb	wzr, [x29, 145]
	ldr	x0, [x29, 112]
	ldr	w1, [x26, w25, uxtw 2]
	str	w4, [x29, 108]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 136
	mov	x0, x21
	bl	InsertStreamSeg
	strb	wzr, [x29, 145]
	ldr	w8, [x19, 24]
	mov	w3, 1
	ldr	w4, [x29, 108]
	add	x1, x29, 136
	ldr	x6, [x23]
	mov	x0, x21
	ldr	w2, [x22, 232]
	strb	w3, [x29, 146]
	str	x6, [x29, 136]
	stp	w8, w4, [x29, 152]
	bl	InsertStreamSeg
	b	.L774
	.p2align 3
.L789:
	ldr	x1, .LC160
	mov	w2, 3044
	mov	w0, 0
	bl	dprint_vfmw
	b	.L774
	.p2align 3
.L787:
	ldr	x1, .LC160
	mov	w2, 3012
	mov	w0, 0
	bl	dprint_vfmw
	b	.L774
	.p2align 3
.L778:
	cmp	w27, wzr
	ble	.L790
	ldr	w0, [x28, 12]
	sub	w0, w0, #1
	cmp	w27, w0
	bcc	.L791
.L782:
	cmp	w27, w0
	beq	.L792
.L784:
	ldr	x0, [x29, 96]
	mov	x2, x28
	mov	w1, 0
	bl	SetLastUnfinishedSegInfo
.L770:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
	.p2align 3
.L790:
	blt	.L784
	ldr	w0, [x28, 12]
	sub	w0, w0, #1
	b	.L782
.L791:
	mul	w3, w24, w27
	mov	w6, 1
	ldr	x0, .LC161
	add	w3, w3, w6
	mov	w4, -1
	mov	x2, 88
	mov	w1, 0
	ldr	x5, [x0, 96]
	add	x0, x22, 504
	ldr	w19, [x26, w3, uxtw 2]
	add	x3, x22, 256
	strh	w4, [x22, 460]
	strh	w4, [x22, 468]
	and	w19, w19, 1073741823
	str	w4, [x22, 464]
	stp	w4, wzr, [x3, 216]
	stp	w6, wzr, [x3, 224]
	str	wzr, [x22, 488]
	str	wzr, [x22, 492]
	str	wzr, [x22, 496]
	blr	x5
	ldr	x0, [x29, 112]
	mov	w1, w19
	bl	DeleteRawLen
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L792:
	ldr	x0, [x29, 96]
	mov	w1, w27
	mov	x2, x28
	ldr	w19, [x22, 164]
	bl	SetLastUnfinishedSegInfo
	ldr	x0, [x29, 112]
	mov	w1, w19
	bl	DeleteRawLen
	b	.L770
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	3
.LC160:
	.xword	.LC154
	.align	3
.LC161:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMeg4ModeFlag
	.type	GetMeg4ModeFlag, %function
GetMeg4ModeFlag:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	add	x19, x0, 458752
	mov	w20, w1
	mov	x0, x30
	mov	w27, 0
	mov	w28, 0
	bl	_mcount
	ldr	w22, [x19, 308]
	ldr	x21, [x19, 200]
	cbz	w20, .L793
	ldr	x26, .LC165
	mov	w23, 288
	mov	w25, 2
	mov	w24, 1
	b	.L807
	.p2align 3
.L813:
	cmp	w1, 32768
	stp	w24, wzr, [x19, 252]
	beq	.L811
.L799:
	add	w28, w28, 1
	add	w27, w27, w22
	cmp	w28, w20
	beq	.L793
.L807:
	ldr	w0, [x21, w27, uxtw 2]
	bl	MEM_Phy2Vir
	cbz	x0, .L812
	ldr	w1, [x0]
	rev	w1, w1
	cmp	w1, 438
	ccmp	w1, w23, 4, ne
	and	w1, w1, -1024
	beq	.L813
	cmp	w1, 32768
	bne	.L799
	ldr	w0, [x19, 252]
	cmp	w0, 1
	beq	.L814
.L801:
	str	w25, [x19, 252]
.L815:
	add	w28, w28, 1
	add	w27, w27, w22
	cmp	w28, w20
	bne	.L807
.L793:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L811:
	str	w24, [x19, 256]
	b	.L799
	.p2align 3
.L812:
	ldr	x2, .LC162
	mov	w3, 3113
	ldr	x1, .LC164
	mov	w0, 1
	add	x2, x2, 96
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L814:
	ldr	w0, [x19, 256]
	add	w0, w0, 1
	str	w0, [x19, 256]
	cmp	w0, 30
	bls	.L799
	ldr	x4, [x26]
	cbz	x4, .L801
	ldr	w0, [x19, 232]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	str	w25, [x19, 252]
	b	.L815
	.size	GetMeg4ModeFlag, .-GetMeg4ModeFlag
	.align	3
.LC162:
	.xword	.LANCHOR3
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessMpeg4ScdUpMsg
	.type	ProcessMpeg4ScdUpMsg, %function
ProcessMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 458752
	mov	x25, x2
	mov	w23, w1
	str	x2, [x29, 112]
	str	x22, [x29, 96]
	add	x21, x22, 98304
	str	w1, [x29, 108]
	bl	_mcount
	ldr	w1, [x19, 308]
	add	x21, x21, 104
	ldr	w0, [x19, 128]
	mov	w27, 0
	mov	w24, w1
	add	x1, x29, 232
	ldr	x28, [x19, 200]
	mov	x26, x21
	str	w24, [x29, 136]
	stp	xzr, xzr, [x1]
	add	x1, x29, 248
	str	xzr, [x29, 224]
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x1]
	add	x1, x29, 264
	str	xzr, [x29, 312]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x1]
	add	x1, x29, 280
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x1]
	add	x1, x29, 296
	stp	xzr, xzr, [x1]
	bl	MEM_Phy2Vir
	mov	x20, x0
	mov	x0, x25
	add	x1, x22, 80
	str	x1, [x29, 128]
	mov	w25, 1
	ldr	w0, [x0, 16]
	bl	MEM_Phy2Vir
	sub	w3, w24, #1
	str	w3, [x29, 140]
	ldr	x3, .LC166
	mov	x2, 4
	mov	x1, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	x0, x22
	mov	w1, w23
	bl	GetMeg4ModeFlag
	mov	x0, x22
	mov	w2, w23
	mov	x1, x28
	add	x22, x21, 360448
	bl	GetNextVop
	mov	w24, w0
	b	.L817
	.p2align 3
.L849:
	ldr	w0, [x29, 248]
	cbz	w0, .L819
	ldr	w2, [x29, 252]
	mov	x1, x21
	add	x0, x29, 232
	add	w3, w2, w3
	str	w3, [x29, 252]
	bl	CheckSegValid
	cbnz	w0, .L823
	ldr	w2, [x19, 232]
	add	x1, x29, 232
	mov	x0, x21
	strb	wzr, [x29, 241]
	bl	InsertStreamSeg
	mov	w23, w0
	ldr	x0, .LC166
	mov	x2, 88
	mov	w1, 0
	ldr	x6, [x0, 96]
	add	x0, x29, 232
	blr	x6
	cbnz	w23, .L823
.L824:
	ldr	w0, [x29, 136]
	mov	w27, w20
	add	w25, w25, w0
.L817:
	cmp	w27, w24
	beq	.L823
	ldr	w1, [x29, 140]
	sub	w0, w25, #1
	add	w20, w27, 1
	add	w1, w1, w25
	add	x23, x28, x0, uxtw 2
	ldr	w2, [x28, w0, uxtw 2]
	ldr	w0, [x28, w1, uxtw 2]
	sub	w3, w0, w2
	cmp	w3, 3
	bgt	.L849
	sub	w1, w3, #1
	cmp	w1, 2
	bls	.L850
	ldr	x3, [x29, 112]
	ldr	w1, [x22, 24]
	ldr	x10, [x26]
	ldr	w9, [x3, 16]
	sub	w8, w0, w1
	ldr	w0, [x22, 12]
	sub	w9, w9, w2
	add	w3, w9, w8
	stp	w2, w3, [x29, 160]
	sub	w2, w2, w1
	cmp	w3, 3
	add	x2, x10, x2
	str	x2, [x29, 144]
	ldr	w1, [x22, 8]
	bls	.L851
	sub	w0, w0, w1
	mov	w1, 4096
	and	w0, w0, 4095
	sub	w0, w1, w0
	cmp	w0, 2
	stp	w8, w9, [x29, 120]
	bls	.L823
	mov	x1, x21
	add	x0, x29, 144
	bl	CheckSegValid
	cbnz	w0, .L823
	ldp	w8, w9, [x29, 120]
	ldr	w0, [x19, 252]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	cbnz	w8, .L834
	beq	.L852
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L836:
	ldr	w1, [x23, 4]
	mov	w3, 1
	ldrb	w0, [x29, 224]
	add	x2, x19, 272
	lsr	w1, w1, 30
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	ldrh	w1, [x23, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x23, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x23, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	strb	w3, [x29, 154]
	strb	wzr, [x29, 153]
	bfi	w1, w0, 7, 4
	str	w9, [x29, 164]
	add	x3, x29, 144
	strh	w1, [x29, 224]
	ldr	x0, [x29, 128]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x21
	bl	InsertStreamSeg
	b	.L824
	.p2align 3
.L819:
	ldr	w8, [x22, 24]
	mov	w9, 1
	ldr	x10, [x26]
	mov	x1, x21
	sub	w8, w2, w8
	add	x0, x29, 144
	add	x8, x10, x8
	strb	w9, [x29, 154]
	str	x8, [x29, 144]
	stp	w2, w3, [x29, 160]
	bl	CheckSegValid
	cbnz	w0, .L823
	ldr	w0, [x19, 252]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	beq	.L853
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L826:
	ldr	w8, [x23, 4]
	add	x2, x19, 272
	ldrb	w1, [x29, 224]
	add	x3, x29, 144
	lsr	w8, w8, 30
	ldr	x0, [x29, 128]
	bfi	w1, w8, 1, 1
	strb	w1, [x29, 224]
	ldrh	w8, [x23, 10]
	bfi	w1, w8, 2, 1
	strb	w1, [x29, 224]
	ldr	w8, [x23, 8]
	ubfx	x8, x8, 4, 3
	bfi	w1, w8, 3, 4
	strb	w1, [x29, 224]
	ldr	w1, [x23, 8]
	ldrh	w6, [x29, 224]
	and	w1, w1, 7
	bfi	w6, w1, 7, 4
	strh	w6, [x29, 224]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	strb	wzr, [x29, 153]
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x21
	bl	InsertStreamSeg
	cbz	w0, .L824
	.p2align 2
.L823:
	cmp	w27, wzr
	ble	.L822
	ldr	x0, [x29, 112]
	ldr	w0, [x0, 12]
	sub	w0, w0, #1
	cmp	w27, w0
	bcc	.L854
	beq	.L855
.L822:
	ldr	w0, [x29, 108]
	cmp	w0, 1024
	ccmp	w24, wzr, 0, hi
	beq	.L856
.L842:
	ldr	x0, .LC166
	add	x4, x19, 256
	mov	w1, 1
	mov	x2, 88
	ldr	x3, [x0, 96]
	mov	w0, -1
	strh	w0, [x19, 460]
	strh	w0, [x19, 468]
	str	w0, [x19, 464]
	stp	w0, wzr, [x4, 216]
	stp	w1, wzr, [x4, 224]
	str	wzr, [x19, 488]
	mov	w1, 0
	str	wzr, [x19, 492]
	add	x0, x19, 504
	str	wzr, [x19, 496]
	blr	x3
.L816:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L850:
	stp	w3, w2, [x29, 120]
	bl	MEM_Phy2Vir
	ldp	w3, w2, [x29, 120]
	cbz	x0, .L857
	ldr	w0, [x0]
	and	w0, w0, 16777215
	cmp	w0, 65536
	beq	.L824
	ldr	w0, [x19, 252]
	cmp	w0, 1
	ldrb	w0, [x29, 312]
	beq	.L858
	orr	w0, w0, 1
	strb	w0, [x29, 312]
.L832:
	ldr	w1, [x23, 4]
	ldrb	w0, [x29, 312]
	lsr	w1, w1, 30
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 312]
	ldr	w1, [x22, 24]
	ldrh	w7, [x23, 10]
	sub	w1, w2, w1
	bfi	w0, w7, 2, 1
	ldr	x7, [x26]
	strb	w0, [x29, 312]
	add	x1, x7, x1
	str	x1, [x29, 232]
	ldr	w1, [x23, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 312]
	mov	w1, 1
	ldr	w0, [x23, 8]
	strb	w1, [x29, 242]
	ldrh	w1, [x29, 312]
	and	w0, w0, 7
	stp	w2, w3, [x29, 248]
	bfi	w1, w0, 7, 4
	strh	w1, [x29, 312]
	ldr	x0, [x29, 128]
	add	x3, x29, 232
	ldr	w1, [x28, w25, uxtw 2]
	add	x2, x19, 272
	and	w1, w1, 1073741823
	bl	GetSegPts
	b	.L824
	.p2align 3
.L834:
	beq	.L859
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L838:
	ldr	w1, [x23, 4]
	add	x3, x29, 144
	ldrb	w0, [x29, 224]
	add	x2, x19, 272
	lsr	w1, w1, 30
	str	w8, [x29, 124]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	ldrh	w1, [x23, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x23, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x23, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	str	w9, [x29, 164]
	strb	wzr, [x29, 154]
	bfi	w1, w0, 7, 4
	strb	wzr, [x29, 153]
	strh	w1, [x29, 224]
	ldr	x0, [x29, 128]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x21
	bl	InsertStreamSeg
	strb	wzr, [x29, 153]
	ldr	w3, [x22, 24]
	add	x1, x29, 144
	ldr	w8, [x29, 124]
	mov	x0, x21
	ldr	x6, [x26]
	ldr	w2, [x19, 232]
	stp	w3, w8, [x29, 160]
	mov	w3, 1
	str	x6, [x29, 144]
	strb	w3, [x29, 154]
	bl	InsertStreamSeg
	b	.L824
	.p2align 3
.L851:
	ldr	x1, .LC169
	mov	w2, 3253
	mov	w0, 0
	bl	dprint_vfmw
	b	.L824
	.p2align 3
.L853:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L826
	.p2align 3
.L859:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L838
	.p2align 3
.L852:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L836
	.p2align 3
.L858:
	and	w0, w0, -2
	strb	w0, [x29, 312]
	b	.L832
	.p2align 3
.L854:
	ldr	w0, [x29, 136]
	mov	w7, 1
	add	x5, x19, 256
	mov	w4, -1
	mov	x2, 88
	mov	w1, 0
	mul	w3, w0, w27
	ldr	x0, .LC166
	add	w3, w3, w7
	ldr	x6, [x0, 96]
	add	x0, x19, 504
	ldr	w20, [x28, w3, uxtw 2]
	strh	w4, [x19, 460]
	strh	w4, [x19, 468]
	and	w20, w20, 1073741823
	str	w4, [x19, 464]
	stp	w4, wzr, [x5, 216]
	stp	w7, wzr, [x5, 224]
	str	wzr, [x19, 488]
	str	wzr, [x19, 492]
	str	wzr, [x19, 496]
	blr	x6
	ldr	x0, [x29, 128]
	mov	w1, w20
	bl	DeleteRawLen
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L856:
	ldr	x1, .LC171
	mov	x2, x0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x29, 128]
	mov	w1, 1
	bl	DeleteRawPacket
	b	.L842
.L855:
	ldr	x0, [x29, 96]
	mov	w1, w27
	ldr	x2, [x29, 112]
	ldr	w19, [x19, 164]
	bl	SetLastUnfinishedSegInfo
	ldr	x0, [x29, 128]
	mov	w1, w19
	bl	DeleteRawLen
	b	.L816
.L857:
	ldr	x1, .LC168
	mov	w2, 3223
	bl	dprint_vfmw
	b	.L816
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	3
.LC166:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC169:
	.xword	.LC154
	.align	3
.LC171:
	.xword	.LC170
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ProcessScdReturn.part.8, %function
ProcessScdReturn.part.8:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	mov	w1, w19
	add	x0, x29, 32
	bl	ReadScdStateReg
	mov	w0, 34464
	ldr	w1, [x29, 44]
	movk	w0, 0x1, lsl 16
	cmp	w1, w0
	bls	.L861
	ldr	w0, [x20, 20]
	cbz	w0, .L866
.L861:
	add	x2, x20, 458752
	ldr	w0, [x29, 56]
	ldr	w19, [x2, 308]
	udiv	w19, w0, w19
	cmp	w19, w1
	csel	w19, w19, w1, ls
	cmp	w1, w19
	bhi	.L867
.L863:
	mov	w1, w19
	add	x2, x29, 32
	mov	x0, x20
	bl	ProcessLastUnfinishedSeg
	cmp	w0, wzr
	ccmp	w19, wzr, 4, eq
	cset	w1, eq
	cbnz	w1, .L862
	ldr	w0, [x20, 20]
	add	x2, x29, 32
	sub	w1, w19, #1
	cmp	w0, 2
	mov	x0, x20
	beq	.L864
	bl	ProcessNotMpeg4ScdUpMsg
	mov	w0, 0
.L862:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L867:
	ldrsb	w0, [x20, 2]
	cmp	w0, 1
	bne	.L863
	strb	wzr, [x20, 2]
	b	.L863
	.p2align 3
.L864:
	bl	ProcessMpeg4ScdUpMsg
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L866:
	mov	x0, x20
	bl	ProcessExceptionalStartCodeNum
	mov	w0, -7
	b	.L862
	.size	ProcessScdReturn.part.8, .-ProcessScdReturn.part.8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x2, x19, 458752
	add	x2, x2, 160
	ldr	w0, [x2, 8]
	cmp	w0, 3
	beq	.L871
	mov	w0, 2
	mov	w1, w20
	str	w0, [x2, 8]
	mov	x0, x19
	bl	ProcessScdReturn.part.8
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L871:
	mov	w1, 2
	str	w1, [x2, 8]
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ProcessScdReturn, .-ProcessScdReturn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveRawStream
	.type	SCDDRV_SaveRawStream, %function
SCDDRV_SaveRawStream:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x23, x1
	mov	x20, x2
	bl	_mcount
	ldr	x21, .LC172
	ldr	x0, [x21, w22, sxtw 3]
	cbz	x0, .L872
	ldr	x19, .LC173
	mov	w0, 0
	ldr	w24, [x23, 20]
	ldr	x1, [x19, 32]
	blr	x1
	ldrb	w0, [x20, 2]
	cbnz	w0, .L874
	add	x1, x23, 36
	mov	w0, w24
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L882
.L875:
	ldr	x2, [x21, w22, sxtw 3]
	ldr	w1, [x20, 8]
	ldr	x3, [x19, 88]
	ldr	x0, [x20, 40]
	blr	x3
.L874:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L872:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L882:
	ldr	x2, [x21, w22, sxtw 3]
	mov	w1, 4
	ldr	x3, [x19, 88]
	add	x0, x20, 8
	blr	x3
	b	.L875
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	3
.LC172:
	.xword	vfmw_save_str_file
	.align	3
.LC173:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	NeedReadStream
	.type	NeedReadStream, %function
NeedReadStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 60]
	cbz	w0, .L885
	add	x19, x19, 458752
	mov	w0, 0
	ldr	w1, [x19, 152]
	cmp	w1, 8
	bgt	.L884
	ldr	x0, .LC174
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1396]
	cmp	w0, 1
	ccmp	w1, wzr, 4, eq
	cset	w0, le
.L884:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L885:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	NeedReadStream, .-NeedReadStream
	.align	3
.LC174:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillEopRawStream
	.type	FillEopRawStream, %function
FillEopRawStream:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC176
	ldr	x0, .LC175
	mov	x2, 100
	add	x1, x21, 112
	add	x20, x0, x20, sxtw 4
	add	x0, x29, 56
	ldr	x20, [x20, 16]
	bl	memcpy
	cbz	x19, .L901
	ldr	w3, [x20, 20]
	cmp	w3, 18
	bls	.L902
.L890:
	ldr	x1, .LC181
	add	x2, x21, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
.L898:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L902:
	ldr	x0, .LC179
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx892
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx892:
	.section	.rodata
	.align	0
	.align	2
.L892:
	.byte	(.L891 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L890 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.byte	(.L890 - .Lrtx892) / 4
	.byte	(.L893 - .Lrtx892) / 4
	.text
	.p2align 3
.L893:
	ldr	w3, [x19, 8]
	mov	w0, 0
	ldr	w5, [x19, 80]
	mov	w4, 0
	cmp	w3, w5
	bhi	.L894
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L891:
	ldr	w3, [x19, 8]
	ldr	w5, [x19, 80]
	add	w0, w3, 15
	cmp	w0, w5
	bhi	.L903
	ldr	x4, .LC184
	add	x1, x29, 56
	ldr	x0, [x19, 40]
	mov	x2, 15
	add	x0, x0, x3, sxtw
	ldr	x3, [x4, 104]
	blr	x3
	ldr	w1, [x19, 8]
	mov	w0, 0
	add	w1, w1, 15
	str	w1, [x19, 8]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L903:
	mov	w4, 15
.L894:
	ldr	x1, .LC183
	add	x2, x21, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L898
.L901:
	ldr	x1, .LC178
	add	x2, x21, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L898
	.size	FillEopRawStream, .-FillEopRawStream
	.align	3
.LC175:
	.xword	.LANCHOR0
	.align	3
.LC176:
	.xword	.LANCHOR3
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC179:
	.xword	.L892
	.align	3
.LC181:
	.xword	.LC180
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC184:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillEosRawStream
	.type	FillEosRawStream, %function
FillEosRawStream:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC185
	mov	x2, 100
	ldr	x1, .LC186
	add	x19, x0, x19, sxtw 4
	add	x0, x29, 40
	add	x1, x1, 240
	ldr	x19, [x19, 16]
	bl	memcpy
	cbz	x20, .L924
	ldr	w3, [x19, 20]
	cmp	w3, 18
	bls	.L925
.L907:
	ldr	x2, .LC187
	mov	w0, 0
	ldr	x1, .LC190
	bl	dprint_vfmw
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L925:
	ldr	x0, .LC189
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx909
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx909:
	.section	.rodata
	.align	0
	.align	2
.L909:
	.byte	(.L908 - .Lrtx909) / 4
	.byte	(.L910 - .Lrtx909) / 4
	.byte	(.L911 - .Lrtx909) / 4
	.byte	(.L912 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L919 - .Lrtx909) / 4
	.byte	(.L907 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L908 - .Lrtx909) / 4
	.byte	(.L914 - .Lrtx909) / 4
	.byte	(.L922 - .Lrtx909) / 4
	.byte	(.L919 - .Lrtx909) / 4
	.text
	.p2align 3
.L908:
	mov	w19, 15
	add	x1, x29, 40
.L913:
	ldr	w4, [x20, 8]
	cmp	w19, w4
	bls	.L926
	ldr	x2, .LC187
	mov	w3, w19
	ldr	x1, .LC192
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L920
	.p2align 3
.L926:
	ldr	x3, .LC193
	and	x2, x19, 31
	ldr	x0, [x20, 40]
	ldr	x3, [x3, 104]
	blr	x3
	str	w19, [x20, 8]
.L922:
	mov	w0, 0
.L920:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L910:
	ldr	w0, [x19, 36]
	cmp	w0, 1
	bne	.L922
.L919:
	mov	w19, 15
	add	x1, x29, 60
	b	.L913
	.p2align 3
.L914:
	mov	w19, 16
	add	x1, x29, 120
	b	.L913
	.p2align 3
.L912:
	mov	w19, 16
	add	x1, x29, 100
	b	.L913
	.p2align 3
.L911:
	mov	w19, 19
	add	x1, x29, 80
	b	.L913
.L924:
	ldr	x2, .LC187
	mov	w0, 0
	ldr	x1, .LC188
	bl	dprint_vfmw
	mov	w0, -7
	b	.L920
	.size	FillEosRawStream, .-FillEosRawStream
	.align	3
.LC185:
	.xword	.LANCHOR0
	.align	3
.LC186:
	.xword	.LANCHOR3
	.align	3
.LC187:
	.xword	.LANCHOR4
	.align	3
.LC188:
	.xword	.LC177
	.align	3
.LC189:
	.xword	.L909
	.align	3
.LC190:
	.xword	.LC180
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC193:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillVC1ExtraData
	.type	FillVC1ExtraData, %function
FillVC1ExtraData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	w0, [x20, 36]
	cmp	w0, 1
	beq	.L939
	ldr	w0, [x19, 76]
	tbnz	x0, 7, .L940
	add	x20, x20, 458752
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 324]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L941
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC197
	mov	w21, 0
	add	x0, x1, x0, uxtw
.L938:
	ldr	x3, [x22, 112]
	blr	x3
	ldr	w2, [x20, 324]
	add	x1, x20, 328
	ldr	x0, [x19, 40]
	ldr	x3, [x22, 104]
	blr	x3
	ldr	w1, [x19, 8]
	ldr	w0, [x20, 324]
	add	w0, w1, w0
	str	w0, [x19, 8]
.L931:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L940:
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	add	w3, w2, 12
	cmp	w3, 128
	ccmp	w3, w4, 2, le
	bhi	.L942
	ldr	x22, .LC197
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	add	x20, x20, 458752
	mov	w21, 0
	ldr	x3, [x22, 112]
	add	x0, x1, 8
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x19, 84
	ldr	x0, [x19, 40]
	mov	x2, 4
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x22, 104]
	add	x1, x19, 88
	add	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 12
	blr	x3
	mov	w1, 16
	str	w1, [x19, 8]
	str	w1, [x20, 324]
	add	x0, x20, 328
	ldr	x3, [x22, 104]
	ldrsw	x2, [x19, 8]
	ldr	x1, [x19, 40]
	blr	x3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L939:
	ldr	w1, [x19, 76]
	tbnz	x1, 7, .L943
	ldrb	w1, [x19, 72]
	mov	w21, 0
	cbz	w1, .L931
	add	x20, x20, 458752
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w5, [x20, 324]
	add	w3, w2, w5
	cmp	w3, w4
	bhi	.L944
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC197
	add	x0, x1, x5, uxtw
	b	.L938
	.p2align 3
.L943:
	ldr	w3, [x19, 8]
	cmp	w3, 128
	bgt	.L945
	add	x20, x20, 458752
	ldr	x1, .LC197
	add	x0, x20, 328
	mov	w21, 0
	str	w3, [x20, 324]
	ldr	x3, [x1, 104]
	ldrsw	x2, [x19, 8]
	ldr	x1, [x19, 40]
	blr	x3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L942:
	ldr	x2, .LC194
	mov	w5, 128
	ldr	x1, .LC201
	mov	w0, 1
	add	x2, x2, 24
	mov	w21, -2
	bl	dprint_vfmw
	b	.L931
	.p2align 3
.L941:
	ldr	x2, .LC194
	mov	w0, 1
	ldr	x1, .LC199
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L931
.L945:
	ldr	x2, .LC194
	mov	w4, 128
	ldr	x1, .LC196
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L931
.L944:
	ldr	x2, .LC194
	mov	w21, -2
	ldr	x1, .LC199
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L931
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	3
.LC194:
	.xword	.LANCHOR4
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC197:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC201:
	.xword	.LC200
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillDIVX3ExtraData
	.type	FillDIVX3ExtraData, %function
FillDIVX3ExtraData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	add	w3, w2, 8
	cmp	w3, w4
	bhi	.L949
	ldr	x20, .LC205
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	ldr	x3, [x20, 112]
	add	x0, x1, 8
	blr	x3
	ldr	x3, [x20, 104]
	mov	x2, 4
	ldr	x0, [x19, 40]
	add	x1, x19, 84
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x20, 104]
	add	x1, x19, 88
	add	x0, x0, x2
	blr	x3
	ldr	w1, [x19, 8]
	mov	w0, 0
	add	w1, w1, 8
	str	w1, [x19, 8]
.L948:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L949:
	ldr	x2, .LC202
	mov	w0, 1
	ldr	x1, .LC204
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L948
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	3
.LC202:
	.xword	.LANCHOR4
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC205:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillREAL8ExtraData
	.type	FillREAL8ExtraData, %function
FillREAL8ExtraData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 76]
	tbz	x0, 7, .L951
	ldr	w3, [x19, 8]
	cmp	w3, 128
	bgt	.L955
	add	x20, x20, 458752
	ldr	x1, .LC208
	add	x0, x20, 328
	str	w3, [x20, 324]
	ldr	x3, [x1, 104]
	ldrsw	x2, [x19, 8]
	ldr	x1, [x19, 40]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L951:
	add	x20, x20, 458752
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 324]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L956
	ldr	x21, .LC208
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	ldr	x3, [x21, 112]
	add	x0, x1, x0, uxtw
	blr	x3
	ldr	w2, [x20, 324]
	add	x1, x20, 328
	ldr	x0, [x19, 40]
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w2, [x19, 8]
	mov	w0, 0
	ldr	w1, [x20, 324]
	add	w1, w2, w1
	str	w1, [x19, 8]
.L953:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L956:
	ldr	x2, .LC206
	mov	w0, 1
	ldr	x1, .LC210
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L953
	.p2align 3
.L955:
	ldr	x2, .LC206
	mov	w4, 128
	ldr	x1, .LC207
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L953
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	3
.LC206:
	.xword	.LANCHOR4
	.align	3
.LC207:
	.xword	.LC195
	.align	3
.LC208:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC210:
	.xword	.LC209
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	w19, 31, 2, ne
	bhi	.L963
	ldr	w3, [x20, 8]
	cmp	w3, wzr
	ble	.L966
	ldr	x0, .LC214
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	ldr	w1, [x0, 20]
	cmp	w1, 5
	beq	.L960
	cmp	w1, 8
	beq	.L961
	cmp	w1, 1
	beq	.L967
	mov	w0, 0
.L958:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L961:
	mov	x1, x20
	bl	FillREAL8ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L960:
	mov	x1, x20
	bl	FillDIVX3ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L967:
	mov	x1, x20
	bl	FillVC1ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L963:
	mov	w0, -1
	b	.L958
.L966:
	ldr	x2, .LC211
	mov	w0, 1
	ldr	x1, .LC213
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L958
	.size	FillExtraData, .-FillExtraData
	.align	3
.LC211:
	.xword	.LANCHOR4
	.align	3
.LC213:
	.xword	.LC212
	.align	3
.LC214:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w0, w22
	bl	VCTRL_GetStreamInterface
	ldr	x19, .LC215
	mov	x20, x0
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x19, 96]
	blr	x3
	cbz	x20, .L984
	ldr	x3, [x19, 104]
	mov	x2, 24
	mov	x1, x20
	add	x0, x29, 72
	blr	x3
	mov	x2, 96
	ldr	x3, [x19, 104]
	mov	x1, x21
	add	x0, x29, x2
	sxtw	x21, w22
	blr	x3
	ldr	x23, .LC218
	ldr	x0, [x20, 16]
	cbz	x0, .L971
	lsl	x20, x21, 4
	add	x24, x23, 16
	ldr	x0, [x24, x20]
	ldr	w0, [x0, 60]
	cmp	w0, 1
	beq	.L985
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x19, 48]
	mov	w1, w22
	mov	w0, 1
	blr	x2
	ldr	x0, [x24, x20]
	cbz	x0, .L976
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
.L974:
	ldr	x2, [x19, 56]
	mov	w0, 1
	mov	w1, w22
	blr	x2
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	cbz	w20, .L975
.L971:
	mov	w20, -7
.L975:
	add	x21, x23, x21, lsl 4
	mov	w0, w20
	ldr	x1, [x21, 16]
	cbz	x1, .L986
.L970:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L985:
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
	cbz	w20, .L975
	b	.L971
	.p2align 3
.L976:
	mov	w20, -7
	b	.L974
.L984:
	ldr	x1, .LC217
	mov	w2, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L970
.L986:
	ldr	x1, .LC220
	mov	w3, w22
	mov	w2, 4188
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L970
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	3
.LC215:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC218:
	.xword	.LANCHOR0
	.align	3
.LC220:
	.xword	.LC219
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawPacketInBuffer
	.type	DeleteRawPacketInBuffer, %function
DeleteRawPacketInBuffer:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w24, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w24, 31
	bhi	.L1003
	ldr	x28, .LC224
	sxtw	x0, w24
	add	x1, x28, x0, lsl 4
	ldr	x22, [x1, 16]
	cbz	x22, .L999
	cbz	w19, .L1004
.L990:
	adds	x23, x22, 80
	beq	.L999
	add	x1, x23, 98304
	ldr	w21, [x1]
	ldr	w20, [x1, 8]
	cmp	w21, w20
	blt	.L1005
.L1002:
	sub	w21, w21, w20
	cbz	w21, .L999
	ldr	x25, .LC225
	add	x28, x28, 16
	ldr	x26, .LC226
	mov	w27, 0
	add	x25, x25, 112
	add	x28, x28, x0, lsl 4
	b	.L994
	.p2align 3
.L1007:
	beq	.L1006
.L994:
	uxtw	x19, w20
	mov	x2, x25
	lsl	x0, x19, 2
	mov	x1, x26
	sub	x19, x0, x19
	mov	w0, 26
	lsl	x19, x19, 5
	add	w27, w27, 1
	add	x3, x22, x19
	add	w20, w20, 1
	and	w20, w20, 1023
	ldr	w4, [x3, 88]
	ldr	w3, [x3, 84]
	bl	dprint_vfmw
	add	x1, x23, x19
	mov	w0, w24
	bl	ReleaseRawStreamData
	ldr	x0, [x28]
	cmp	w27, w21
	cbnz	x0, .L1007
	mov	w0, -7
.L989:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1004:
	add	x1, x22, 458752
	ldr	w1, [x1, 248]
	cbnz	w1, .L990
.L999:
	mov	w0, -1
	b	.L989
	.p2align 3
.L1005:
	add	w21, w21, 1024
	b	.L1002
	.p2align 3
.L1006:
	add	x23, x23, 98304
	ldr	w20, [x23, 8]
	add	w20, w20, w27
	cmp	w20, 1023
	ble	.L1008
	sub	w20, w20, #1024
	str	w20, [x23, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1008:
	str	w20, [x23, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1003:
	ldr	x1, .LC223
	mov	w2, w24
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L989
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	3
.LC223:
	.xword	.LC222
	.align	3
.LC224:
	.xword	.LANCHOR0
	.align	3
.LC225:
	.xword	.LANCHOR4
	.align	3
.LC226:
	.xword	.LC44
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, 31
	bhi	.L1020
	ldr	x27, .LC229
	sxtw	x23, w22
	add	x0, x27, x23, lsl 4
	ldr	x20, [x0, 16]
	cbz	x20, .L1011
	add	x2, x27, 528
	ldr	w0, [x2, 52]
	cmp	w22, w0
	beq	.L1012
	ldr	x21, .LC232
.L1013:
	ldr	x3, [x21, 104]
	mov	x2, 72
	add	x1, x20, 8
	add	x0, x29, 104
	add	x19, x20, 458752
	add	x23, x27, x23, lsl 4
	blr	x3
	add	x25, x19, 328
	ldr	x3, [x21, 104]
	mov	x2, 128
	mov	x1, x25
	add	x0, x29, 176
	ldr	w24, [x19, 248]
	ldr	w26, [x19, 324]
	blr	x3
	ldr	x0, [x23, 16]
	cbz	x0, .L1014
	add	x0, x0, 458752
	ldr	w1, [x0, 248]
	cbnz	w1, .L1028
.L1014:
	adds	x23, x20, 80
	beq	.L1015
.L1029:
	add	x1, x23, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	cmp	w0, wzr
	add	w1, w0, 1024
	csel	w1, w1, w0, lt
.L1019:
	mov	x0, x23
	sub	w24, w24, #1
	bl	DeleteRawPacket
	mov	w1, 1
	mov	w0, w22
	bl	DeleteRawPacketInBuffer
	ldrsb	w23, [x19, 232]
	ldr	x3, [x21, 96]
	mov	x2, 16976
	movk	x2, 0x7, lsl 16
	mov	w1, 0
	mov	x0, x20
	blr	x3
	str	wzr, [x19, 476]
	mov	w0, -1
	strh	w0, [x19, 460]
	strh	w0, [x19, 468]
	mov	x2, 88
	str	w0, [x19, 464]
	mov	w1, 0
	str	w0, [x19, 472]
	add	x0, x19, 256
	ldr	x3, [x21, 96]
	stp	wzr, wzr, [x0, 228]
	stp	wzr, wzr, [x0, 236]
	mov	w0, 1
	str	w0, [x19, 480]
	add	x0, x19, 504
	blr	x3
	str	w23, [x19, 232]
	mov	w0, 2
	mov	x2, -1
	add	x1, x29, 104
	str	x2, [x19, 272]
	str	w0, [x19, 308]
	mov	w0, w22
	bl	SM_Config
	str	w26, [x19, 324]
	cmp	w24, 1
	ldr	x3, [x21, 104]
	cset	w0, ls
	mov	x2, 128
	str	w0, [x19, 248]
	add	x1, x29, 176
	mov	x0, x25
	blr	x3
	mov	w0, 0
.L1027:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L1028:
	ldr	w1, [x0, 236]
	cmp	w1, wzr
	bgt	.L1014
	str	wzr, [x0, 248]
	adds	x23, x20, 80
	bne	.L1029
	.p2align 2
.L1015:
	ldr	x2, .LC233
	mov	w3, 1284
	ldr	x1, .LC237
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w1, 0
	b	.L1019
	.p2align 3
.L1012:
	lsl	x1, x23, 6
	ldr	x21, .LC232
	add	x1, x1, x23, lsl 3
	mov	w0, 1
	add	x1, x2, x1
	ldr	x2, [x21, 256]
	str	wzr, [x1, 56]
	blr	x2
	ldr	x2, .LC233
	mov	w3, 1266
	ldr	x1, .LC235
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
	b	.L1013
	.p2align 3
.L1020:
	mov	w0, -1
	b	.L1027
.L1011:
	ldr	x1, .LC231
	mov	w2, 1256
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1027
	.size	SM_Reset, .-SM_Reset
	.align	3
.LC229:
	.xword	.LANCHOR0
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC232:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC233:
	.xword	.LANCHOR4
	.align	3
.LC235:
	.xword	.LC234
	.align	3
.LC237:
	.xword	.LC236
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	sxtw	x23, w0
	mov	x0, x30
	mov	x24, x1
	mov	x20, x23
	bl	_mcount
	ldr	x25, .LC239
	ldr	x21, .LC240
	mov	x2, 24
	add	x0, x25, x23, lsl 4
	mov	w1, 0
	ldr	x3, [x21, 96]
	ldr	x19, [x0, 16]
	add	x0, x29, 88
	blr	x3
	cbz	x19, .L1031
	mov	w0, w23
	bl	VCTRL_GetStreamInterface
	mov	x22, x0
	cbz	x0, .L1066
	ldr	x3, [x21, 104]
	mov	x2, 24
	add	x0, x29, 88
	mov	x1, x22
	blr	x3
	ldr	x0, [x22, 8]
	cbz	x0, .L1031
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1067
	ldr	x22, .LC243
	ldr	x0, [x22, w23, sxtw 3]
	cbz	x0, .L1047
	add	x0, x0, 507904
	ldr	w26, [x0, 1356]
.L1037:
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L1038
	add	x0, x0, 507904
	ldr	w0, [x0, 1356]
	cmp	w26, w0
	bne	.L1068
.L1038:
	ldr	x2, [x29, 96]
	mov	x1, x24
	ldr	w0, [x29, 88]
	add	x23, x25, x23, lsl 4
	blr	x2
	mov	w22, w0
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	x0, [x23, 16]
	cbz	x0, .L1069
	cbz	w22, .L1039
.L1031:
	mov	w0, -7
.L1063:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1039:
	ldrb	w21, [x24, 1]
	cmp	w21, 1
	beq	.L1070
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1071
.L1041:
	add	x19, x19, 98304
	ldr	w1, [x24, 8]
	mov	w0, 0
	ldr	w2, [x19, 100]
	add	w1, w2, w1
	str	w1, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1070:
	mov	x1, x24
	mov	w0, w20
	bl	FillEosRawStream
	cbnz	w0, .L1072
	mov	w1, w21
	mov	w0, w20
	bl	VCTRL_SetLastFrameState
	b	.L1041
	.p2align 3
.L1067:
	ldr	w0, [x29, 88]
	mov	x1, x24
	ldr	x2, [x29, 96]
	blr	x2
	mov	w22, w0
	cbz	w22, .L1039
	b	.L1031
	.p2align 3
.L1047:
	mov	w26, 0
	b	.L1037
	.p2align 3
.L1071:
	mov	x1, x24
	mov	w0, w20
	bl	FillExtraData
	cbnz	w0, .L1073
	add	x0, x19, 458752
	ldr	w0, [x0, 320]
	cbz	w0, .L1041
	ldrb	w0, [x24]
	cbnz	w0, .L1041
	mov	x1, x24
	mov	w0, w20
	bl	FillEopRawStream
	b	.L1041
	.p2align 3
.L1073:
	ldr	x1, .LC249
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x29, 88]
	mov	x1, x24
	bl	ReleaseRawStreamData
	cbz	w0, .L1031
	ldr	x1, .LC251
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1063
.L1069:
	ldr	x1, .LC245
	mov	w3, w20
	mov	w2, 4092
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1063
	.p2align 3
.L1068:
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	mov	w0, -7
	b	.L1063
.L1066:
	ldr	x1, .LC242
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1063
.L1072:
	ldr	x1, .LC247
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1063
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	3
.LC239:
	.xword	.LANCHOR0
	.align	3
.LC240:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC242:
	.xword	.LC241
	.align	3
.LC243:
	.xword	s_pstVfmwChan
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC249:
	.xword	.LC248
	.align	3
.LC251:
	.xword	.LC250
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	sxtw	x22, w0
	mov	x0, x30
	mov	x20, x22
	bl	_mcount
	ldr	x24, .LC252
	ldr	x23, .LC253
	mov	x2, 96
	add	x4, x24, x22, lsl 4
	mov	w1, 0
	add	x0, x29, 112
	ldr	x3, [x23, 96]
	ldr	x21, [x4, 16]
	blr	x3
	cbz	x21, .L1074
	ldr	w0, [x21, 20]
	cmp	w0, 20
	beq	.L1074
	lsl	w0, w22, 24
	ldr	x28, .LC254
	str	w0, [x29, 108]
	add	x19, x21, 458752
	ldr	x0, .LC262
	mov	x27, x28
	ldr	x26, .LC256
	ldr	x25, .LC258
	add	x0, x0, 152
	str	x0, [x29, 96]
	.p2align 2
.L1089:
	ldr	w0, [x21, 60]
	cbz	w0, .L1076
	ldr	w0, [x19, 152]
	cmp	w0, 8
	ble	.L1112
.L1074:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1112:
	ldr	x1, [x28, x22, lsl 3]
	add	x1, x1, 507904
	ldr	w1, [x1, 1396]
	cmp	w1, 1
	ccmp	w0, wzr, 4, eq
	bgt	.L1074
	.p2align 2
.L1076:
	cmp	w20, 31
	bhi	.L1080
	add	x0, x24, x22, lsl 4
	ldr	x0, [x0, 16]
	cbz	x0, .L1080
	add	x0, x0, 80
	add	x1, x0, 98304
	ldp	w0, w2, [x1, 4]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	cmp	w0, w2
	beq	.L1080
	add	x1, x29, 112
	mov	w0, w20
	bl	ReadRawStreamData
	cbnz	w0, .L1074
	ldr	w2, [x19, 288]
	ldr	w4, [x19, 312]
	ldr	w1, [x19, 316]
	ldr	w0, [x29, 120]
	ldr	x3, [x23]
	add	w1, w1, 1
	add	w2, w2, w0
	str	w1, [x19, 316]
	add	w0, w4, w0
	str	w2, [x19, 288]
	str	w0, [x19, 312]
	blr	x3
	ldr	w1, [x19, 292]
	cbnz	w1, .L1082
	str	w0, [x19, 292]
.L1083:
	ldr	x2, [x29, 176]
	mov	x1, x26
	mov	w0, 29
	bl	dprint_vfmw
	ldp	w2, w3, [x29, 116]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x1, [x29, 176]
	mov	x0, 4294967295
	cmp	x1, x0
	beq	.L1113
	add	x1, x29, 112
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbnz	w0, .L1114
.L1085:
	mov	w1, 1
	strb	w1, [x21, 3]
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1115
.L1087:
	mov	w0, w20
	add	x2, x29, 112
	mov	x1, x21
	bl	SCDDRV_SaveRawStream
	ldr	x0, [x27, x22, lsl 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1396]
	cmp	w0, 1
	bne	.L1089
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1080:
	ldr	x1, .LC264
	mov	w2, w20
	mov	w0, 23
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1082:
	sub	w1, w0, w1
	cmp	w1, 2000
	bls	.L1083
	ldr	w2, [x19, 288]
	str	w0, [x19, 292]
	lsl	w0, w2, 3
	str	wzr, [x19, 288]
	udiv	w1, w0, w1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	lsl	w0, w0, 1
	sub	w1, w0, w1
	ubfx	x1, x1, 7, 22
	str	w1, [x19, 296]
	b	.L1083
	.p2align 3
.L1115:
	ldr	x0, [x23]
	blr	x0
	ldr	x1, .LC261
	add	x2, x24, 632
	ldr	w3, [x1]
	ldr	w1, [x2, x22, lsl 2]
	sub	w1, w0, w1
	cmp	w1, w3
	bls	.L1087
	str	w0, [x2, x22, lsl 2]
	mov	w1, 3489
	ldr	w2, [x29, 108]
	ldr	x0, [x29, 96]
	bl	DBG_AddTrace
	b	.L1087
	.p2align 3
.L1113:
	mov	x0, -1
	add	x1, x29, 112
	str	x0, [x29, 176]
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbz	w0, .L1085
.L1114:
	ldr	x1, .LC260
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1074
	.size	FillRawData, .-FillRawData
	.align	3
.LC252:
	.xword	.LANCHOR0
	.align	3
.LC253:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC254:
	.xword	s_pstVfmwChan
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC260:
	.xword	.LC259
	.align	3
.LC261:
	.xword	g_TraceBsPeriod
	.align	3
.LC262:
	.xword	.LANCHOR4
	.align	3
.LC264:
	.xword	.LC263
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseSegArrayPackets
	.type	ReleaseSegArrayPackets, %function
ReleaseSegArrayPackets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cmp	w19, 4096
	beq	.L1116
	cmp	w19, w21
	beq	.L1116
	add	x23, x20, 360448
	mov	w22, 2
	.p2align 2
.L1119:
	sxtw	x3, w19
	mov	w1, w19
	lsl	x2, x3, 2
	mov	x0, x20
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	add	x2, x20, x2, lsl 3
	strb	w22, [x2, 16]
	ldr	w4, [x2, 28]
	ldp	w3, w2, [x23, 44]
	subs	w3, w3, w4
	csel	w3, w3, wzr, pl
	subs	w2, w2, #1
	csel	w2, w2, wzr, pl
	stp	w3, w2, [x23, 44]
	bl	ReleaseStreamSeg
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 20
	add	w0, w0, w19
	and	w0, w0, 4095
	sub	w19, w0, w19
	cmp	w21, w19
	bne	.L1119
.L1116:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	add	x21, x0, 360448
	mov	x25, x0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	ldp	w20, w4, [x21, 8]
	ldp	x22, x24, [x23]
	str	w20, [x21, 16]
	.p2align 2
.L1122:
	sxtw	x19, w20
	cmp	w20, w4
	lsl	x3, x19, 2
	mov	w1, w20
	sub	x3, x3, x19
	mov	x0, x25
	lsl	x3, x3, 2
	sub	x19, x3, x19
	beq	.L1133
	add	x19, x25, x19, lsl 3
	ldrsb	w2, [x19, 16]
	cmp	w2, 1
	bne	.L1125
	ldr	x1, [x19, 48]
	add	w0, w20, 1
	cmn	x1, #1
	beq	.L1134
	cmp	x22, x1
	asr	w1, w0, 31
	lsr	w1, w1, 20
	bls	.L1128
	add	w0, w0, w1
	str	w20, [x21, 16]
	and	w20, w0, 4095
	sub	w20, w20, w1
	b	.L1122
	.p2align 3
.L1125:
	bl	ReleaseStreamSeg
	add	w0, w20, 1
	ldr	w4, [x21, 12]
	asr	w20, w0, 31
	lsr	w20, w20, 20
	add	w0, w0, w20
	and	w0, w0, 4095
	sub	w20, w0, w20
	b	.L1122
	.p2align 3
.L1128:
	beq	.L1135
	bcs	.L1122
	ldr	w2, [x21, 16]
	sxtw	x1, w2
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x25, x0, lsl 3
	ldr	x0, [x0, 48]
	cmn	x0, #1
	beq	.L1132
	cmp	x22, x0
	bls	.L1131
	sub	x22, x22, x0
	cmp	x24, x22
	bcs	.L1131
.L1132:
	mov	w2, w20
	str	w20, [x21, 16]
.L1131:
	ldr	w1, [x21, 8]
	mov	x0, x25
	bl	ReleaseSegArrayPackets
	ldrsw	x2, [x21, 16]
	mov	w0, 0
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x25, x25, x1, lsl 3
	ldr	x1, [x25, 48]
	str	x1, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1134:
	asr	w20, w0, 31
	lsr	w20, w20, 20
	add	w0, w0, w20
	and	w0, w0, 4095
	sub	w20, w0, w20
	b	.L1122
	.p2align 3
.L1133:
	ldr	w1, [x21, 8]
	mov	w2, w20
	bl	ReleaseSegArrayPackets
	ldr	x25, [sp, 64]
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L1135:
	ldr	w1, [x21, 8]
	mov	w2, w20
	mov	x0, x25
	bl	ReleaseSegArrayPackets
	ldr	x0, [x19, 48]
	str	x0, [x23]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	SM_SeekPtsInSegArray, .-SM_SeekPtsInSegArray
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsInRawArray
	.type	SM_SeekPtsInRawArray, %function
SM_SeekPtsInRawArray:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	mov	x21, x1
	mov	w22, w3
	bl	_mcount
	ldr	x0, .LC267
	add	x0, x0, x19, sxtw 4
	ldr	x9, [x0, 16]
	cbz	x9, .L1155
	cmp	w22, 1
	mov	w10, 0
	ldp	x8, x11, [x21]
	beq	.L1167
.L1138:
	add	x6, x20, 98304
	ldp	w3, w7, [x6]
	str	w3, [x6, 8]
	mov	w1, w3
	.p2align 2
.L1139:
	sxtw	x5, w1
	add	w0, w1, 1
	asr	w4, w0, 31
	lsl	x2, x5, 2
	sub	x2, x2, x5
	lsr	w4, w4, 22
	cmp	w1, w7
	add	w0, w0, w4
	add	x2, x20, x2, lsl 5
	and	w0, w0, 1023
	beq	.L1168
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1169
	cmp	x8, x2
	bls	.L1145
	str	w1, [x6, 8]
	sub	w1, w0, w4
	b	.L1139
	.p2align 3
.L1169:
	add	w0, w1, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w1, w0, w1
	b	.L1139
	.p2align 3
.L1168:
	cmp	w3, w1
	bgt	.L1170
.L1163:
	sub	w1, w1, w3
	str	w3, [x6, 8]
	mov	x0, x20
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, -2
.L1137:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1170:
	add	w1, w1, 1024
	b	.L1163
	.p2align 3
.L1145:
	beq	.L1171
	ldr	w0, [x6, 8]
	sxtw	x4, w0
	lsl	x2, x4, 2
	sub	x2, x2, x4
	add	x2, x20, x2, lsl 5
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1165
	cmp	x8, x2
	bls	.L1151
	sub	x8, x8, x2
	cmp	x11, x8
	bcs	.L1151
.L1165:
	mov	w0, w1
	str	w1, [x6, 8]
.L1151:
	cmp	w3, w0
	sub	w1, w0, w3
	bgt	.L1172
.L1153:
	cmp	w22, 1
	beq	.L1173
.L1154:
	sxtw	x2, w0
	mov	x0, x20
	lsl	x3, x2, 2
	sub	x2, x3, x2
	add	x20, x20, x2, lsl 5
.L1166:
	ldr	x2, [x20, 64]
	str	x2, [x21]
	ldr	w2, [x6]
	str	w2, [x6, 8]
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1167:
	add	x0, x9, 458752
	ldr	w10, [x0, 168]
	cmp	w10, 1
	bne	.L1138
	mov	w1, 3
	str	w1, [x0, 168]
	b	.L1138
	.p2align 3
.L1172:
	add	w1, w0, 1024
	sub	w1, w1, w3
	b	.L1153
.L1171:
	cmp	w1, w3
	bge	.L1164
	add	w1, w1, 1024
.L1164:
	cmp	w22, 1
	sub	w1, w1, w3
	beq	.L1174
.L1149:
	lsl	x0, x5, 2
	sub	x5, x0, x5
	mov	x0, x20
	add	x20, x20, x5, lsl 5
	b	.L1166
.L1173:
	add	x9, x9, 458752
	ldr	w2, [x9, 160]
	cmp	w1, w2
	ccmp	w10, 1, 0, le
	bne	.L1154
	str	w10, [x9, 168]
	ldr	w0, [x6, 8]
	b	.L1154
.L1174:
	add	x9, x9, 458752
	ldr	w0, [x9, 160]
	cmp	w1, w0
	ccmp	w10, 1, 0, le
	bne	.L1149
	str	w10, [x9, 168]
	b	.L1149
.L1155:
	mov	w0, -1
	b	.L1137
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	3
.LC267:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsAfterFillNewRaw
	.type	SM_SeekPtsAfterFillNewRaw, %function
SM_SeekPtsAfterFillNewRaw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	mov	x21, x1
	bl	_mcount
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, w19
	bl	FillRawData
	mov	w2, w19
	mov	x1, x21
	mov	w3, 0
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_SeekPtsAfterFillNewRaw, .-SM_SeekPtsAfterFillNewRaw
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldr	x0, .LC268
	add	x0, x0, x21, sxtw 4
	ldr	x20, [x0, 16]
	cbz	x20, .L1188
	add	x0, x20, 98304
	mov	x1, x22
	add	x0, x0, 104
	bl	SM_SeekPtsInSegArray
	cbnz	w0, .L1178
.L1179:
	mov	w0, 0
.L1177:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1178:
	mov	w1, 0
	mov	w0, w21
	add	x20, x20, 80
	bl	DeleteRawPacketInBuffer
	mov	w3, 1
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	cbz	w0, .L1179
	add	x1, x20, 98304
	ldp	w3, w0, [x1]
	cmp	w3, w0
	bgt	.L1198
.L1197:
	sub	w3, w0, w3
	ldr	x2, [x22, 16]
	sxtw	x3, w3
	cmp	x3, x2
	bcs	.L1199
	sub	x3, x2, x3
	and	x0, x3, 1023
	lsr	x23, x3, 10
	cbnz	x0, .L1200
.L1184:
	add	w23, w23, 1
	mov	w19, 0
	cmp	w23, wzr
	bgt	.L1193
	b	.L1187
	.p2align 3
.L1201:
	cmp	w19, w23
	beq	.L1187
.L1193:
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	add	w19, w19, 1
	bl	SM_SeekPtsAfterFillNewRaw
	cbnz	w0, .L1201
	b	.L1179
	.p2align 3
.L1198:
	add	w0, w0, 1024
	b	.L1197
	.p2align 3
.L1200:
	add	w23, w23, 1
	b	.L1184
	.p2align 3
.L1187:
	mov	w0, -2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L1188:
	mov	w0, -1
	b	.L1177
.L1199:
	ldr	x1, .LC270
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1177
	.size	SM_SeekPts, .-SM_SeekPts
	.align	3
.LC268:
	.xword	.LANCHOR0
	.align	3
.LC270:
	.xword	.LC269
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 98304
	bl	_mcount
	ldr	w4, [x20, 68]
	ldr	w0, [x24, 84]
	add	w1, w0, 1023
	subs	w22, w0, #1
	csel	w22, w1, w22, mi
	add	w1, w0, 1022
	subs	w0, w0, #2
	csel	w0, w1, w0, mi
	sxtw	x2, w22
	lsl	x1, x2, 2
	sxtw	x0, w0
	sub	x1, x1, x2
	lsl	x21, x0, 2
	lsl	x1, x1, 5
	sub	x0, x21, x0
	add	x23, x20, x1
	add	x1, x1, 80
	add	x21, x20, x0, lsl 5
	add	x19, x20, x1
	ldr	w2, [x23, 88]
	ldr	w0, [x21, 88]
	add	w1, w0, w2
	cmp	w1, w4
	bgt	.L1205
	ldr	x1, .LC271
	sxtw	x2, w2
	ldr	x3, [x21, 120]
	add	x20, x20, 458752
	add	x0, x3, x0, sxtw
	ldr	x3, [x1, 104]
	ldr	x1, [x23, 120]
	blr	x3
	ldr	w2, [x21, 88]
	mov	x1, x19
	ldr	w0, [x23, 88]
	add	w0, w2, w0
	str	w0, [x21, 88]
	ldr	w0, [x20, 232]
	bl	ReleaseRawStreamData
	str	w22, [x24, 84]
	mov	w0, 0
.L1206:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1205:
	ldr	x1, .LC273
	mov	w3, w2
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1206
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	3
.LC271:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC273:
	.xword	.LC272
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 98304
	bl	_mcount
	adds	x24, x22, 104
	beq	.L1217
	add	x0, x24, 360448
	ldp	w23, w25, [x0, 44]
.L1208:
	add	x19, x22, 104
	ldrsb	w0, [x21, 1]
	add	x19, x19, 360448
	ldr	w20, [x19, 28]
	cbnz	w0, .L1209
	add	w20, w20, w20, lsr 31
	mov	w0, 127
	asr	w20, w20, 1
	cmp	w20, w23
	ccmp	w25, w0, 0, gt
	ble	.L1227
.L1207:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1209:
	ldr	x27, .LC274
	add	x26, x21, 458752
	ldr	x0, [x27]
	blr	x0
	ldr	w2, [x26, 264]
	cmp	w0, w2
	bls	.L1212
	sub	w2, w0, w2
	str	w2, [x26, 260]
	cmp	w2, 1000
	ble	.L1207
	cmp	w20, wzr
	add	w0, w20, 3
	csel	w20, w0, w20, lt
	mov	w0, 63
	asr	w20, w20, 2
	cmp	w20, w23
	ccmp	w25, w0, 0, gt
	bgt	.L1207
	cbnz	w23, .L1215
	ldr	w0, [x26, 488]
	cbz	w0, .L1215
	ldr	x1, .LC276
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x26, 232]
	bl	SM_Reset
	cbz	x24, .L1216
	mov	x2, 32768
	ldr	x3, [x27, 96]
	movk	x2, 0x5, lsl 16
	mov	w1, 0
	add	x0, x22, 112
	blr	x3
	str	wzr, [x19, 16]
	ldr	w0, [x19, 24]
	stp	wzr, wzr, [x19, 8]
	stp	w0, w0, [x19, 32]
	b	.L1216
	.p2align 3
.L1212:
	str	wzr, [x26, 260]
	str	w0, [x26, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1215:
	ldr	x1, .LC278
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x24
	bl	ReleaseStreamSeg
.L1216:
	strb	wzr, [x21, 1]
	strb	wzr, [x21]
	b	.L1207
	.p2align 3
.L1217:
	mov	w23, 0
	mov	w25, 0
	b	.L1208
	.p2align 3
.L1227:
	ldr	x0, .LC274
	mov	w1, 1
	strb	w1, [x21, 1]
	add	x21, x21, 458752
	ldr	x0, [x0]
	blr	x0
	str	wzr, [x21, 260]
	str	w0, [x21, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	3
.LC274:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC276:
	.xword	.LC275
	.align	3
.LC278:
	.xword	.LC277
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CanNotSelectInst
	.type	SCDDRV_CanNotSelectInst, %function
SCDDRV_CanNotSelectInst:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC279
	add	x19, x0, x19, sxtw 4
	ldr	x1, [x19, 16]
	cbz	x1, .L1231
	add	x0, x1, 458752
	ldr	w2, [x0, 248]
	cbz	w2, .L1231
	ldr	w0, [x0, 240]
	cmp	w0, 1
	beq	.L1231
	ldr	w0, [x1, 20]
	ldr	x2, [x1, 36]
	ldr	w1, [x1, 44]
	cmp	w0, 19
	str	x2, [x29, 32]
	str	w1, [x29, 40]
	beq	.L1231
	add	x1, x29, 32
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cmp	w0, wzr
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1231:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	3
.LC279:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SM_DoNextInstance.part.11, %function
SM_DoNextInstance.part.11:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w21, w0
	mov	x0, x30
	str	x1, [x29, 104]
	mov	w20, 32
	bl	_mcount
	ldr	x25, .LC280
	sxtw	x0, w21
	ldr	x23, .LC281
	lsl	x1, x0, 6
	ldr	x24, .LC282
	add	x0, x1, x0, lsl 3
	add	x22, x25, 16
	add	x0, x25, x0
	ldr	w19, [x0, 580]
	b	.L1249
	.p2align 3
.L1242:
	subs	w20, w20, #1
	beq	.L1256
.L1249:
	add	w0, w19, 1
	mov	w1, w21
	asr	w19, w0, 31
	lsr	w19, w19, 27
	add	w0, w0, w19
	and	w0, w0, 31
	sub	w19, w0, w19
	mov	w0, w19
	bl	SCDDRV_CanNotSelectInst
	uxtb	w0, w0
	cbnz	w0, .L1242
	sxtw	x28, w19
	ldr	x0, [x23]
	lsl	x1, x28, 4
	ldr	x27, [x22, x1]
	blr	x0
	add	x26, x27, 458752
	ldr	w1, [x26, 304]
	subs	w1, w0, w1
	bmi	.L1257
	ldrsh	w2, [x27, 2]
	cmp	w2, 1
	beq	.L1258
.L1244:
	str	w0, [x26, 304]
	ldrsb	w0, [x27]
	cmp	w0, 1
	beq	.L1259
.L1246:
	strb	wzr, [x27, 1]
.L1247:
	ldr	x2, [x24, x28, lsl 3]
	mov	w1, w21
	mov	x0, x27
	add	x2, x2, 507904
	ldr	w2, [x2, 1384]
	str	w2, [x26, 456]
	bl	CutStreamWithSCD
	cmn	w0, #6
	cset	w1, eq
	strb	w1, [x27]
	cbnz	w0, .L1242
	ldr	x0, [x29, 104]
	add	x2, x25, 760
	ldr	x3, .LC283
	mov	w1, 1
	add	x2, x2, x28, lsl 2
	mov	w4, 4646
	str	w19, [x0]
	add	x3, x3, 168
	mov	w0, w19
	str	w1, [x26, 248]
	bl	RecordPOS
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1257:
	str	w0, [x26, 304]
	ldrsh	w1, [x27, 2]
	cmp	w1, 1
	beq	.L1242
	str	w0, [x26, 304]
	ldrsb	w0, [x27]
	cmp	w0, 1
	bne	.L1246
.L1259:
	mov	x0, x27
	bl	SCDDRV_ProcessSegFull
	b	.L1247
	.p2align 3
.L1258:
	cmp	w1, 499
	bhi	.L1244
	subs	w20, w20, #1
	bne	.L1249
.L1256:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -3
	ldp	x29, x30, [sp], 112
	ret
	.size	SM_DoNextInstance.part.11, .-SM_DoNextInstance.part.11
	.align	3
.LC280:
	.xword	.LANCHOR0
	.align	3
.LC281:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC282:
	.xword	s_pstVfmwChan
	.align	3
.LC283:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SCDDRV_ActivateSCD.part.12, %function
SCDDRV_ActivateSCD.part.12:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC286
	add	x1, x20, x19, lsl 2
	ldr	w0, [x1, 600]
	cbz	w0, .L1261
	cmp	w0, 1
	beq	.L1264
.L1260:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1261:
	add	x1, x29, 60
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1260
	lsl	x1, x19, 6
	ldr	x0, .LC287
	add	x19, x1, x19, lsl 3
	add	x20, x20, 528
	add	x19, x20, x19
	ldr	w2, [x29, 60]
	ldr	x0, [x0]
	mov	w1, 1
	stp	w2, w1, [x19, 52]
	blr	x0
	str	w0, [x19, 60]
	ldr	x2, .LC288
	mov	w3, 4851
	ldr	x1, .LC290
	mov	w0, 26
	add	x2, x2, 192
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1264:
	mov	w0, 2
	str	w0, [x1, 600]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
	.align	3
.LC286:
	.xword	.LANCHOR0
	.align	3
.LC287:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC288:
	.xword	.LANCHOR4
	.align	3
.LC290:
	.xword	.LC289
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x2, .LC292
	add	x2, x2, x19, sxtw 2
	ldr	w0, [x2, 600]
	cbz	w0, .L1266
	cmp	w0, 1
	mov	w0, -3
	beq	.L1269
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1266:
	mov	x1, x20
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1269:
	mov	w1, 2
	str	w1, [x2, 600]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	3
.LC292:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_RecordGlobalState
	.type	SCDDRV_RecordGlobalState, %function
SCDDRV_RecordGlobalState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC293
	ldr	x0, [x0]
	blr	x0
	ldr	x4, .LC294
	sxtw	x1, w19
	add	x3, x4, x1, lsl 6
	ldr	w2, [x3, 48]
	cbz	w2, .L1270
	ldr	w6, [x3, 44]
	add	w5, w6, 49152
	add	w5, w5, 848
	cmp	w2, w5
	bhi	.L1273
	ldr	w3, [x3, 52]
.L1274:
	add	x1, x4, x1, lsl 6
	sub	w2, w0, w2
	sub	w0, w0, w6
	add	w2, w2, w3
	cmp	w0, 999
	stp	wzr, w2, [x1, 48]
	bls	.L1270
	lsl	w3, w2, 6
	str	wzr, [x1, 44]
	sub	w3, w3, w2
	lsl	w3, w3, 1
	sub	w2, w3, w2
	lsl	w2, w2, 3
	udiv	w0, w2, w0
	str	w0, [x1, 56]
.L1270:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1273:
	str	w2, [x3, 44]
	mov	w6, w2
	mov	w3, 0
	b	.L1274
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	3
.LC293:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC294:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_MoveRawByOmxPath
	.type	SCDDRV_MoveRawByOmxPath, %function
SCDDRV_MoveRawByOmxPath:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC295
	add	x19, x0, x19, sxtw 4
	ldr	x19, [x19, 16]
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1286
.L1276:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1286:
	adds	x1, x19, 80
	beq	.L1279
	add	x1, x1, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	add	w1, w0, 1024
	cmp	w0, wzr
	csel	w0, w1, w0, lt
.L1282:
	ldrsb	w20, [x19, 2]
	cmp	w20, 1
	bne	.L1276
	ldr	w1, [x19, 64]
	cmp	w1, w0
	bne	.L1276
	mov	x0, x19
	bl	SM_MoveRawData
	cbz	w0, .L1276
	ldr	x1, .LC297
	mov	w0, w20
	add	x19, x19, 458752
	bl	dprint_vfmw
	ldr	w0, [x19, 232]
	bl	SM_Reset
	b	.L1276
	.p2align 3
.L1279:
	ldr	x1, .LC299
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1282
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	3
.LC295:
	.xword	.LANCHOR0
	.align	3
.LC297:
	.xword	.LC296
	.align	3
.LC299:
	.xword	.LC298
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	sxtw	x22, w0
	mov	x0, x30
	mov	x23, x22
	bl	_mcount
	ldr	x19, .LC300
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	ldr	x21, .LC301
	add	x20, x21, x22, lsl 2
	ldr	w0, [x20, 8]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbnz	x0, 0, .L1304
.L1288:
	ldr	x0, .LC303
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1296
	mov	w1, w23
	mov	w0, 0
	bl	VDH_Notify_ModuleIdle
.L1296:
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1304:
	ldr	w0, [x20, 8]
	mov	w1, 1
	add	x20, x21, 528
	add	w0, w0, 2084
	bl	MEM_WritePhyWord
	lsl	x0, x22, 6
	add	x0, x0, x22, lsl 3
	add	x20, x20, x0
	ldp	w0, w24, [x20, 48]
	cmp	w0, wzr
	add	x0, x21, x24, sxtw 4
	ldr	x25, [x0, 16]
	ccmp	x25, xzr, 4, ne
	beq	.L1305
	ldr	x3, .LC302
	mov	w4, 4734
	add	x2, x21, 888
	mov	w1, 2
	add	x3, x3, 216
	mov	w0, w24
	bl	RecordPOS
	mov	w0, w22
	bl	SCDDRV_RecordGlobalState
	ldr	w0, [x20, 56]
	cmp	w0, 1
	beq	.L1306
.L1290:
	ldr	x1, [x19, 256]
	mov	w0, 1
	blr	x1
	ldr	x1, [x19, 256]
	mov	w0, 0
	blr	x1
	b	.L1288
	.p2align 3
.L1305:
	ldr	x1, [x19, 256]
	mov	w0, 1
	str	wzr, [x20, 56]
	blr	x1
	b	.L1288
	.p2align 3
.L1306:
	add	x20, x25, 458752
	ldr	w0, [x20, 248]
	cmp	w0, 1
	beq	.L1307
.L1291:
	add	x1, x21, x22, lsl 2
	str	wzr, [x20, 240]
	ldr	w0, [x1, 600]
	cbz	w0, .L1294
	cmp	w0, 1
	beq	.L1308
.L1295:
	lsl	x0, x22, 6
	ldr	x1, [x19, 256]
	add	x22, x0, x22, lsl 3
	mov	w0, 1
	add	x21, x21, x22
	str	wzr, [x21, 584]
	blr	x1
	b	.L1290
	.p2align 3
.L1294:
	add	x1, x29, 92
	mov	w0, w23
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1295
	lsl	x0, x22, 6
	add	x20, x21, 528
	add	x22, x0, x22, lsl 3
	ldr	w2, [x29, 92]
	add	x20, x20, x22
	ldr	x0, [x19]
	mov	w1, 1
	stp	w2, w1, [x20, 52]
	blr	x0
	str	w0, [x20, 60]
	b	.L1290
	.p2align 3
.L1307:
	add	x0, x20, 160
	ldr	w1, [x0, 8]
	cmp	w1, 3
	beq	.L1309
	mov	w2, 2
	mov	w1, w22
	str	w2, [x0, 8]
	mov	x0, x25
	bl	ProcessScdReturn.part.8
.L1293:
	mov	w0, w24
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1291
.L1308:
	mov	w0, 2
	str	w0, [x1, 600]
	b	.L1295
.L1309:
	mov	w1, 2
	str	w1, [x0, 8]
	b	.L1293
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	3
.LC300:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC301:
	.xword	.LANCHOR0
	.align	3
.LC302:
	.xword	.LANCHOR4
	.align	3
.LC303:
	.xword	g_HalDisable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1318
	ldr	x21, .LC305
	mov	w4, 0
	ldr	x24, .LC306
	mov	w3, 4784
	add	x20, x21, 528
	ldr	x23, .LC308
	add	x22, x24, 240
	ldr	w5, [x20, 56]
	mov	x2, x22
	mov	x1, x23
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w19, [x20, 56]
	cbz	w19, .L1322
	mov	w5, w19
	mov	w4, 0
	mov	w3, 4794
	mov	x2, x22
	mov	x1, x23
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x19, .LC311
	ldr	x0, [x19]
	blr	x0
	ldr	w4, [x20, 60]
	cmp	w0, w4
	bcs	.L1313
	str	w0, [x20, 60]
.L1314:
	ldr	x1, .LC316
	mov	w4, 0
	mov	w3, 4831
	add	x2, x24, 240
	mov	w0, 26
	mov	w19, 1
	bl	dprint_vfmw
.L1311:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1313:
	sub	w4, w0, w4
	cmp	w4, 2000
	bls	.L1314
	ldr	x1, .LC313
	mov	w3, 0
	ldr	w2, [x20, 52]
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC314
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1315
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L1316:
	ldr	x1, [x19, 256]
	mov	w0, 1
	str	wzr, [x21, 584]
	blr	x1
	ldr	w0, [x21, 580]
	add	x21, x21, x0, sxtw 4
	ldr	x1, [x21, 16]
	cbz	x1, .L1317
	add	x1, x1, 458752
	str	wzr, [x1, 240]
.L1317:
	bl	DeleteLastSendRaw
	mov	w19, 0
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1322:
	ldr	x1, .LC310
	mov	x2, x22
	mov	w4, 0
	mov	w3, 4788
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1315:
	mov	w0, 0
	bl	ResetSCD
	b	.L1316
	.p2align 3
.L1318:
	mov	w19, -1
	b	.L1311
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	3
.LC305:
	.xword	.LANCHOR0
	.align	3
.LC306:
	.xword	.LANCHOR4
	.align	3
.LC308:
	.xword	.LC307
	.align	3
.LC310:
	.xword	.LC309
	.align	3
.LC311:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC313:
	.xword	.LC312
	.align	3
.LC314:
	.xword	g_HalDisable
	.align	3
.LC316:
	.xword	.LC315
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ActivateSCD
	.type	SCDDRV_ActivateSCD, %function
SCDDRV_ActivateSCD:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1323
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
.L1323:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ActivateSCD, .-SCDDRV_ActivateSCD
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Wakeup
	.type	SM_Wakeup, %function
SM_Wakeup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x20, .LC319
	add	x20, x20, 16
	b	.L1327
	.p2align 3
.L1326:
	add	w19, w19, 1
	cmp	w19, 32
	beq	.L1334
.L1327:
	ldr	x0, [x20]
	add	x20, x20, 16
	add	x1, x0, 458752
	cbz	x0, .L1326
	ldr	w0, [x1, 248]
	cmp	w0, 1
	bne	.L1326
	mov	w0, w19
	add	w19, w19, 1
	bl	FillRawData
	cmp	w19, 32
	bne	.L1327
	.p2align 2
.L1334:
	ldr	x19, .LC320
	mov	w4, 1
	ldr	x1, .LC322
	mov	w3, 0
	add	x19, x19, 264
	mov	w0, 26
	mov	x2, x19
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_CheckDevice
	cbz	w0, .L1328
	ldr	x1, .LC324
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4880
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1328:
	ldr	x1, .LC326
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4875
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Wakeup, .-SM_Wakeup
	.align	3
.LC319:
	.xword	.LANCHOR0
	.align	3
.LC320:
	.xword	.LANCHOR4
	.align	3
.LC322:
	.xword	.LC321
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdVtrlReg
	.type	PrintScdVtrlReg, %function
PrintScdVtrlReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC328
	add	x19, x19, x20, sxtw 2
	ldr	w0, [x19, 8]
	add	w0, w0, 2052
	bl	MEM_ReadPhyWord
	mov	w27, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2056
	bl	MEM_ReadPhyWord
	mov	w26, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2060
	bl	MEM_ReadPhyWord
	mov	w25, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2064
	bl	MEM_ReadPhyWord
	mov	w24, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2068
	bl	MEM_ReadPhyWord
	mov	w23, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2072
	bl	MEM_ReadPhyWord
	mov	w22, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2080
	bl	MEM_ReadPhyWord
	mov	w21, w0
	ldr	w0, [x19, 8]
	add	w0, w0, 2048
	bl	MEM_ReadPhyWord
	mov	w19, w0
	ldr	x1, .LC330
	mov	w2, w20
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC332
	mov	w2, w27
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC334
	mov	w2, w26
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC336
	mov	w2, w25
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC338
	mov	w2, w24
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC340
	mov	w2, w23
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC342
	mov	w2, w22
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC344
	mov	w2, w21
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC346
	sxtb	w2, w19
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	PrintScdVtrlReg, .-PrintScdVtrlReg
	.align	3
.LC328:
	.xword	.LANCHOR0
	.align	3
.LC330:
	.xword	.LC329
	.align	3
.LC332:
	.xword	.LC331
	.align	3
.LC334:
	.xword	.LC333
	.align	3
.LC336:
	.xword	.LC335
	.align	3
.LC338:
	.xword	.LC337
	.align	3
.LC340:
	.xword	.LC339
	.align	3
.LC342:
	.xword	.LC341
	.align	3
.LC344:
	.xword	.LC343
	.align	3
.LC346:
	.xword	.LC345
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdStateReg
	.type	PrintScdStateReg, %function
PrintScdStateReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC348
	mov	w2, w20
	mov	w0, 24
	bl	dprint_vfmw
	ldr	w2, [x19]
	mov	w0, 24
	ldr	x1, .LC350
	bl	dprint_vfmw
	ldr	w2, [x19, 8]
	mov	w0, 24
	ldr	x1, .LC352
	bl	dprint_vfmw
	ldr	w2, [x19, 12]
	mov	w0, 24
	ldr	x1, .LC354
	bl	dprint_vfmw
	ldr	w2, [x19, 16]
	mov	w0, 24
	ldr	x1, .LC356
	bl	dprint_vfmw
	ldr	w2, [x19, 20]
	mov	w0, 24
	ldr	x1, .LC358
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PrintScdStateReg, .-PrintScdStateReg
	.align	3
.LC348:
	.xword	.LC347
	.align	3
.LC350:
	.xword	.LC349
	.align	3
.LC352:
	.xword	.LC351
	.align	3
.LC354:
	.xword	.LC353
	.align	3
.LC356:
	.xword	.LC355
	.align	3
.LC358:
	.xword	.LC357
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbnz	w0, .L1349
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1349:
	ldr	x3, .LC359
	mov	w2, w20
	ldr	x1, .LC361
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x23, [x3, 16]
	bl	dprint_vfmw
	ldr	x1, .LC363
	mov	w0, 26
	add	x22, x23, 80
	add	x19, x22, 98304
	ldr	w2, [x19]
	bl	dprint_vfmw
	ldr	x1, .LC365
	mov	w0, 26
	ldr	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	x1, .LC367
	mov	w0, 26
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC369
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC371
	mov	w0, 26
	ldr	w2, [x19, 16]
	bl	dprint_vfmw
	cmp	w21, 1
	beq	.L1339
.L1343:
	ldr	x1, .LC373
	mov	w2, w20
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1339:
	cbz	x22, .L1340
	ldp	w28, w21, [x19]
	sub	w21, w21, w28
	cmp	w21, wzr
	add	w0, w21, 1024
	csel	w21, w0, w21, lt
	cmp	w21, wzr
	ble	.L1343
	ldr	x27, .LC375
	add	w0, w28, w21
	ldr	x26, .LC377
	ldr	x25, .LC379
	ldr	x24, .LC381
	str	w0, [x29, 108]
	.p2align 2
.L1342:
	sxtw	x19, w28
	mov	x1, x27
	lsl	x0, x19, 2
	add	w28, w28, 1
	sub	x19, x0, x19
	mov	w0, 26
	lsl	x19, x19, 5
	add	x21, x23, x19
	add	x19, x22, x19
	ldr	w2, [x21, 84]
	bl	dprint_vfmw
	ldr	x2, [x19, 40]
	mov	x1, x26
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x21, 88]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x2, [x19, 64]
	mov	x1, x24
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w0, [x29, 108]
	cmp	w28, w0
	bne	.L1342
	b	.L1343
	.p2align 3
.L1340:
	ldr	x2, .LC382
	mov	w3, 4953
	ldr	x1, .LC384
	mov	w0, 22
	add	x2, x2, 280
	bl	dprint_vfmw
	b	.L1343
	.size	PrintScdRawState, .-PrintScdRawState
	.align	3
.LC359:
	.xword	.LANCHOR0
	.align	3
.LC361:
	.xword	.LC360
	.align	3
.LC363:
	.xword	.LC362
	.align	3
.LC365:
	.xword	.LC364
	.align	3
.LC367:
	.xword	.LC366
	.align	3
.LC369:
	.xword	.LC368
	.align	3
.LC371:
	.xword	.LC370
	.align	3
.LC373:
	.xword	.LC372
	.align	3
.LC375:
	.xword	.LC374
	.align	3
.LC377:
	.xword	.LC376
	.align	3
.LC379:
	.xword	.LC378
	.align	3
.LC381:
	.xword	.LC380
	.align	3
.LC382:
	.xword	.LANCHOR4
	.align	3
.LC384:
	.xword	.LC383
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w20, w0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbnz	w0, .L1359
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1359:
	ldr	x3, .LC385
	mov	w2, w20
	ldr	x1, .LC387
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x23, [x3, 16]
	bl	dprint_vfmw
	ldr	x1, .LC389
	mov	w0, 26
	add	x24, x23, 98304
	add	x21, x24, 104
	add	x19, x21, 360448
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC391
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC393
	mov	w0, 26
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	x1, .LC395
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC397
	mov	w0, 26
	ldr	x2, [x24, 104]
	bl	dprint_vfmw
	ldr	x1, .LC399
	mov	w0, 26
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, .LC401
	mov	w0, 26
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	x1, .LC403
	mov	w0, 26
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	cmp	w22, 1
	beq	.L1352
.L1353:
	ldr	x1, .LC405
	mov	w2, w20
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1352:
	ldp	w24, w22, [x19, 8]
	sub	w22, w22, w24
	ands	w22, w22, 4095
	beq	.L1353
	ldr	x28, .LC407
	add	w22, w24, w22
	ldr	x27, .LC409
	ldr	x26, .LC411
	ldr	x25, .LC413
	str	x21, [x29, 104]
	.p2align 2
.L1354:
	sxtw	x19, w24
	mov	x1, x28
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	ldr	x0, [x29, 104]
	add	x19, x0, x19, lsl 3
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	mov	w0, 88
	mov	x1, x27
	smaddl	x3, w24, w0, x23
	mov	w0, 26
	add	w24, w24, 1
	add	x21, x3, 98304
	ldr	x2, [x21, 112]
	bl	dprint_vfmw
	ldr	w2, [x19, 28]
	mov	x1, x26
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x19, 32]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldrsb	w2, [x21, 120]
	mov	w0, 26
	ldr	x1, .LC415
	bl	dprint_vfmw
	ldrb	w2, [x21, 122]
	mov	w0, 26
	ldr	x1, .LC417
	bl	dprint_vfmw
	ldr	x1, .LC419
	mov	w0, 26
	ldr	x2, [x19, 40]
	bl	dprint_vfmw
	cmp	w24, w22
	bne	.L1354
	b	.L1353
	.size	PrintScdSegState, .-PrintScdSegState
	.align	3
.LC385:
	.xword	.LANCHOR0
	.align	3
.LC387:
	.xword	.LC386
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
.LC397:
	.xword	.LC396
	.align	3
.LC399:
	.xword	.LC398
	.align	3
.LC401:
	.xword	.LC400
	.align	3
.LC403:
	.xword	.LC402
	.align	3
.LC405:
	.xword	.LC404
	.align	3
.LC407:
	.xword	.LC406
	.align	3
.LC409:
	.xword	.LC408
	.align	3
.LC411:
	.xword	.LC410
	.align	3
.LC413:
	.xword	.LC412
	.align	3
.LC415:
	.xword	.LC414
	.align	3
.LC417:
	.xword	.LC416
	.align	3
.LC419:
	.xword	.LC418
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
	.align	3
.LANCHOR3 = . + 0
	.type	__func__.50266, %object
	.size	__func__.50266, 19
__func__.50266:
	.string	"SCDDRV_LoadDspCode"
	.zero	5
	.type	__func__.50338, %object
	.size	__func__.50338, 16
__func__.50338:
	.string	"DeleteRawPacket"
	.type	__FUNCTION__.50448, %object
	.size	__FUNCTION__.50448, 17
__FUNCTION__.50448:
	.string	"ReleaseStreamSeg"
	.zero	7
	.type	__func__.50517, %object
	.size	__func__.50517, 14
__func__.50517:
	.string	"SM_OpenSCDDrv"
	.zero	2
	.type	__func__.50601, %object
	.size	__func__.50601, 16
__func__.50601:
	.string	"SM_CopyRawToSeg"
	.type	__func__.50932, %object
	.size	__func__.50932, 16
__func__.50932:
	.string	"GetMeg4ModeFlag"
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
	.zero	4
	.type	__func__.51006, %object
	.size	__func__.51006, 17
__func__.51006:
	.string	"FillEopRawStream"
	.zero	7
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
	.align	3
.LANCHOR4 = . + 0
	.type	__func__.51034, %object
	.size	__func__.51034, 17
__func__.51034:
	.string	"FillEosRawStream"
	.zero	7
	.type	__func__.51059, %object
	.size	__func__.51059, 17
__func__.51059:
	.string	"FillVC1ExtraData"
	.zero	7
	.type	__func__.51064, %object
	.size	__func__.51064, 19
__func__.51064:
	.string	"FillDIVX3ExtraData"
	.zero	5
	.type	__func__.51069, %object
	.size	__func__.51069, 19
__func__.51069:
	.string	"FillREAL8ExtraData"
	.zero	5
	.type	__func__.51077, %object
	.size	__func__.51077, 14
__func__.51077:
	.string	"FillExtraData"
	.zero	2
	.type	__func__.50352, %object
	.size	__func__.50352, 24
__func__.50352:
	.string	"DeleteRawPacketInBuffer"
	.type	__FUNCTION__.50491, %object
	.size	__FUNCTION__.50491, 9
__FUNCTION__.50491:
	.string	"SM_Reset"
	.zero	7
	.type	__FUNCTION__.50996, %object
	.size	__FUNCTION__.50996, 12
__FUNCTION__.50996:
	.string	"FillRawData"
	.zero	4
	.type	__FUNCTION__.51190, %object
	.size	__FUNCTION__.51190, 18
__FUNCTION__.51190:
	.string	"SM_DoNextInstance"
	.zero	6
	.type	__func__.51227, %object
	.size	__func__.51227, 19
__func__.51227:
	.string	"SCDDRV_ActivateSCD"
	.zero	5
	.type	__FUNCTION__.51214, %object
	.size	__FUNCTION__.51214, 19
__FUNCTION__.51214:
	.string	"SM_SCDIntServeProc"
	.zero	5
	.type	__func__.51221, %object
	.size	__func__.51221, 19
__func__.51221:
	.string	"SCDDRV_CheckDevice"
	.zero	5
	.type	__func__.51236, %object
	.size	__func__.51236, 10
__func__.51236:
	.string	"SM_Wakeup"
	.zero	6
	.type	__FUNCTION__.51256, %object
	.size	__FUNCTION__.51256, 17
__FUNCTION__.51256:
	.string	"PrintScdRawState"
	.data
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 17408
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
	.size	g_pScdDrvParamBase, 8
g_pScdDrvParamBase:
	.xword	g_ScdDrvParam
	.type	g_hex_flag, %object
	.size	g_hex_flag, 4
g_hex_flag:
	.word	1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC5:
	ASCII(.string	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\n" )
	.zero	5
.LC10:
	ASCII(.string	"Warn: eVidStd = %d have not DSP vfmw bin file!!\n" )
	.zero	7
.LC13:
	ASCII(.string	"%s failed!\n" )
	.zero	4
.LC15:
	ASCII(.string	"%s success!\n" )
	.zero	3
.LC26:
	ASCII(.string	"Ignore the reset request when the SCD[%d] clock is closed.\n" )
	.zero	4
.LC28:
	ASCII(.string	"SCD[%d]   ResetSCD ERROR!!!\n" )
	.zero	3
.LC39:
	ASCII(.string	"line: %d Get SmID fail!" )
.LC41:
	ASCII(.string	"DelRaw err PacketNum = %d, DelNum = %d\n" )
.LC44:
	ASCII(.string	"%s release RawPhyAddr = 0x%x, Len = %d\n" )
.LC48:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = %d,Next Length = %d,is_extern_eop_flag = %d\n\n" )
	.zero	7
.LC51:
	ASCII(.string	"line: %d pSmInstArray is NULL!\n" )
.LC60:
	ASCII(.string	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLastSeg=%d\n" )
	.zero	5
.LC62:
	ASCII(.string	"-------- forece release seg[%d] -----------\n" )
	.zero	3
.LC64:
	ASCII(.string	"\n" )
	.zero	6
.LC66:
	ASCII(.string	"0x%02x," )
.LC68:
	ASCII(.string	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d StreamID=%d\n" )
	.zero	4
.LC71:
	ASCII(.string	"Array out of bound in function %s\n" )
	.zero	5
.LC86:
	ASCII(.string	"ScdId is wrong! %s error\n" )
	.zero	6
.LC88:
	ASCII(.string	"%s,line: %d\n" )
	.zero	3
.LC93:
	ASCII(.string	"%s: g_hex_base_vir_addr = NULL\n" )
.LC100:
	ASCII(.string	"line: %d, SmID = %d, pSmCfg = %p is not expected!\n" )
	.zero	5
.LC105:
	ASCII(.string	"line: %d, SmID = %d is not expected!\n" )
	.zero	2
.LC107:
	ASCII(.string	"line: %d, SmID = %d, ScdId = %d is not expected!\n" )
	.zero	6
.LC116:
	ASCII(.string	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\n" )
	.zero	6
.LC118:
	ASCII(.string	"line: %d, delet raw failed!\n" )
	.zero	3
.LC121:
	ASCII(.string	"[%s %d] VirAddr is null!!\n" )
	.zero	5
.LC125:
	ASCII(.string	"copy raw to seg fail\n" )
	.zero	2
.LC143:
	ASCII(.string	"InstID = %d EsRelease!\n" )
.LC147:
	ASCII(.string	"Cann't Start SCD, Ret = %d\n" )
	.zero	4
.LC150:
	ASCII(.string	"SM_CfgBuf Err! ret =%d\n" )
.LC154:
	ASCII(.string	"Line: %d, The length of seg packet is invalid: %d\n" )
	.zero	5
.LC158:
	ASCII(.string	"Line: %d, start code num from scd state reg: %d, release raw packet anyway!\n" )
	.zero	3
.LC163:
	ASCII(.string	"[%s %d] pCurrentStartCodeVirAddr is null!!\n" )
	.zero	4
.LC167:
	ASCII(.string	"Line: %d, pNextStartCodeVirAddr is null!\n" )
	.zero	6
.LC170:
	ASCII(.string	"ValidSegNum = %d, FilteredSegNum = 0, release raw packet anyway!\n" )
	.zero	6
.LC177:
	ASCII(.string	"%s: pRawPacket = NULL!\n" )
.LC180:
	ASCII(.string	"%s: unkown standard type = %d!\n" )
.LC182:
	ASCII(.string	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\n" )
	.zero	7
.LC191:
	ASCII(.string	"%s: FlagLen(%d) > RawPacketLength(%d)\n" )
	.zero	1
.LC195:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, header_buf: %d)\n" )
.LC198:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, str_buf: %d)\n" )
	.zero	3
.LC200:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf: %d, header_buf: %d)\n" )
	.zero	4
.LC203:
	ASCII(.string	"Func: %s, buffer has no enough space, (act: %d, str_buf: %d)\n" )
	.zero	2
.LC209:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf:%d)\n" )
	.zero	5
.LC212:
	ASCII(.string	"%s: RawPacket Length %d <= 0\n" )
	.zero	2
.LC216:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReleaseRawStreamData pStreamIntf is NULL!" )
.LC219:
	ASCII(.string	"line: %d s_SmIIS[%d].pSmInstArray is NULL\n" )
	.zero	5
.LC222:
	ASCII(.string	"SmID = %d is not expected!\n" )
	.zero	4
.LC230:
	ASCII(.string	"line: %d, pScdInstance is NULL!\n" )
	.zero	7
.LC234:
	ASCII(.string	"%s %d force to clear SCDState = 0\n" )
	.zero	5
.LC236:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum !!\n" )
	.zero	3
.LC241:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReadRawStreamData pStreamIntf is NULL!" )
	.zero	3
.LC244:
	ASCII(.string	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\n" )
	.zero	5
.LC246:
	ASCII(.string	"Chan %d FillEosRawStream failed!\n" )
	.zero	6
.LC248:
	ASCII(.string	"Chan %d FillExtraData failed!\n" )
	.zero	1
.LC250:
	ASCII(.string	"Release this packet failed!\n" )
	.zero	3
.LC255:
	ASCII(.string	"raw_pts: %lld\n" )
	.zero	1
.LC257:
	ASCII(.string	"Get RawPhyAddr=0x%x,Len=%d\n" )
	.zero	4
.LC259:
	ASCII(.string	"!!!push raw err!!!\n" )
	.zero	4
.LC263:
	ASCII(.string	"Chan%d raw full\n" )
	.zero	7
.LC269:
	ASCII(.string	"RawNum %lld <= RawNumInVfmw %lld\n" )
	.zero	6
.LC272:
	ASCII(.string	"No space for raw move, total:%d+%d > max:%d!\n" )
	.zero	2
.LC275:
	ASCII(.string	"scd buffer is full, reset scd!\n" )
.LC277:
	ASCII(.string	"(%d ms) not release stream seg, release anyway!\n" )
	.zero	7
.LC289:
	ASCII(.string	"%s,%d, active scd Success!\n" )
	.zero	4
.LC296:
	ASCII(.string	"Move raw data failed, force to reset scd.\n" )
	.zero	5
.LC298:
	ASCII(.string	"SCD GetRawStreamNum Fail.\n" )
	.zero	5
.LC307:
	ASCII(.string	"%s,%d,SCD(ID = %d) SCDState = %d\n" )
	.zero	6
.LC309:
	ASCII(.string	"%s,%d,SCD(ID = %d) return Idle!\n" )
	.zero	7
.LC312:
	ASCII(.string	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\n" )
	.zero	4
.LC315:
	ASCII(.string	"%s,%d,SCD(ID = %d) really busy!\n" )
	.zero	7
.LC321:
	ASCII(.string	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\n" )
.LC323:
	ASCII(.string	"%s,%d,SCD(ID = %d) return BUSY!!\n" )
	.zero	6
.LC325:
	ASCII(.string	"%s,%d,find idle SCD(ID = %d)\n" )
	.zero	2
.LC329:
	ASCII(.string	"***Print Scd[%d] Vtrl Reg Now\n" )
	.zero	1
.LC331:
	ASCII(.string	"DownMsgPhyAddr = %x\n" )
	.zero	3
.LC333:
	ASCII(.string	"UpMsgPhyAddr = %x\n" )
	.zero	5
.LC335:
	ASCII(.string	"UpLen = %x\n" )
	.zero	4
.LC337:
	ASCII(.string	"BufferFirst = %x\n" )
	.zero	6
.LC339:
	ASCII(.string	"BufferLast = %x\n" )
	.zero	7
.LC341:
	ASCII(.string	"BufferIni = %x\n" )
.LC343:
	ASCII(.string	"ScdProtocol = %x\n" )
	.zero	6
.LC345:
	ASCII(.string	"ScdStart = %x\n" )
	.zero	1
.LC347:
	ASCII(.string	"***Print Scd[%d] State Reg\n" )
	.zero	4
.LC349:
	ASCII(.string	"Scdover = %d \n" )
	.zero	1
.LC351:
	ASCII(.string	"ShortScdNum = %d \n" )
	.zero	5
.LC353:
	ASCII(.string	"ScdNum = %d \n" )
	.zero	2
.LC355:
	ASCII(.string	"ScdRollAddr = %0x \n" )
	.zero	4
.LC357:
	ASCII(.string	"SrcEaten = %d \n" )
.LC360:
	ASCII(.string	"********** SmID [%d] RawState begin **********\n" )
.LC362:
	ASCII(.string	"RawHead=%d\n" )
	.zero	4
.LC364:
	ASCII(.string	"RawTail=%d\n" )
	.zero	4
.LC366:
	ASCII(.string	"RawHistory=%d\n" )
	.zero	1
.LC368:
	ASCII(.string	"RawFirstPacketOffset=%d\n" )
	.zero	7
.LC370:
	ASCII(.string	"CurShowIndex=%d\n" )
	.zero	7
.LC372:
	ASCII(.string	"********** SmID [%d] RawState end   **********\n" )
.LC374:
	ASCII(.string	"RawPhyAddr=0x%x\n" )
	.zero	7
.LC376:
	ASCII(.string	"RawVirAddr=0x%x\n" )
	.zero	7
.LC378:
	ASCII(.string	"RawLength=%d\n" )
	.zero	2
.LC380:
	ASCII(.string	"RawPts=%ld\n" )
	.zero	4
.LC383:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum!!\n" )
	.zero	4
.LC386:
	ASCII(.string	"********** SmID [%d] SegState begin **********\n" )
.LC388:
	ASCII(.string	"SegHead=%d\n" )
	.zero	4
.LC390:
	ASCII(.string	"SegTail=%d\n" )
	.zero	4
.LC392:
	ASCII(.string	"SegCurrent=%d\n" )
	.zero	1
.LC394:
	ASCII(.string	"SegBufPhyAddr=%p\n" )
	.zero	6
.LC396:
	ASCII(.string	"SegBufVirAddr=%p\n" )
	.zero	6
.LC398:
	ASCII(.string	"SegBufSize=%d\n" )
	.zero	1
.LC400:
	ASCII(.string	"SegBufReadAddr=%p\n" )
	.zero	5
.LC402:
	ASCII(.string	"SegBufWriteAddr=%pd\n" )
	.zero	3
.LC404:
	ASCII(.string	"********** SmID [%d] SegState end   **********\n" )
.LC406:
	ASCII(.string	"SegPhyAddr=0x%x\n" )
	.zero	7
.LC408:
	ASCII(.string	"SegVirAddr=0x%x\n" )
	.zero	7
.LC410:
	ASCII(.string	"SegLength=%d\n" )
	.zero	2
.LC412:
	ASCII(.string	"SegStreamID=%d\n" )
.LC414:
	ASCII(.string	"SegState=%d\n" )
	.zero	3
.LC416:
	ASCII(.string	"SegIsLastSeg=%d\n" )
	.zero	7
.LC418:
	ASCII(.string	"SegPts=%lld\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.zero	4
	.zero	4
	.type	s_ScdRegPhyBaseAddr, %object
	.size	s_ScdRegPhyBaseAddr, 4
s_ScdRegPhyBaseAddr:
	.zero	4
	.zero	4
	.type	s_SmIIS, %object
	.size	s_SmIIS, 512
s_SmIIS:
	.zero	512
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 72
g_ScdDrvParam:
	.zero	72
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.zero	4
	.zero	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 8
g_hex_base_vir_addr:
	.zero	8
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.zero	4
	.zero	4
	.type	s_ScdRegResetPhyAddr, %object
	.size	s_ScdRegResetPhyAddr, 4
s_ScdRegResetPhyAddr:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.50991, %object
	.size	last_rec_pos_time.50991, 128
last_rec_pos_time.50991:
	.zero	128
	.type	LastRecPosTime.51187, %object
	.size	LastRecPosTime.51187, 128
LastRecPosTime.51187:
	.zero	128
	.type	last_rec_pos_time.51212, %object
	.size	last_rec_pos_time.51212, 128
last_rec_pos_time.51212:
	.zero	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.zero	4
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
