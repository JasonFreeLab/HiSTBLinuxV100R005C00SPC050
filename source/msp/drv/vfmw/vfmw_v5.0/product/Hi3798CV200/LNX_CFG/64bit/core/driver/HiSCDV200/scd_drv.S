#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"scd_drv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	GetFreeSegBufSize.part.4, %function
GetFreeSegBufSize.part.4:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x0, x19, 163840
	str	wzr, [x20]
	ldp	w2, w3, [x0, 32]
	cmp	w3, w2
	sub	w2, w2, #1
	bls	.L2
	ldr	w0, [x0, 28]
	add	w2, w0, w2
	sub	w2, w2, w3
.L3:
	cmp	w2, w0
	bgt	.L1
	str	w2, [x20]
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2:
	bcs	.L4
	sub	w2, w2, w3
	ldr	w0, [x0, 28]
	b	.L3
	.p2align 3
.L4:
	ldr	w0, [x0, 28]
	sub	w2, w0, #1
	b	.L3
	.size	GetFreeSegBufSize.part.4, .-GetFreeSegBufSize.part.4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteCabacTabDsp
	.type	WriteCabacTabDsp, %function
WriteCabacTabDsp:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L10
	ldr	x3, .LC4
	mov	x2, 5120
	ldr	x1, .LC5
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L10:
	ldr	x1, .LC3
	mov	w2, 64
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC5:
	.xword	g_CabacMN
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
	cbz	w19, .L26
.L11:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L26:
	ldr	x20, .LC6
	ldr	w0, [x20]
	bl	MEM_Phy2Vir
	cbz	x0, .L27
	cmp	w22, 1
	beq	.L28
	cmp	w22, 2
	beq	.L29
	ldr	x1, .LC13
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L29:
	ldr	x21, .LC9
	mov	x2, 17920
	ldr	x1, .LC11
	ldr	x3, [x21, 104]
	add	x1, x1, 512
	blr	x3
	ldr	w0, [x20, 8]
	mov	w1, 0
	bl	MEM_WritePhyWord
.L16:
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
	b	.L19
	.p2align 3
.L30:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L20
.L19:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	w0, [x20, 8]
	add	w0, w0, 260
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L30
	cmp	w19, 999
	bhi	.L20
	ldr	x2, .LC14
	mov	w0, 0
	ldr	x1, .LC18
	bl	dprint_vfmw
.L22:
	cmp	w22, 1
	beq	.L31
	cmp	w22, 2
	bne	.L11
	ldr	x0, .LC19
	mov	w1, 1
	str	w1, [x0]
	b	.L11
	.p2align 3
.L20:
	ldr	x2, .LC14
	mov	w0, 0
	ldr	x1, .LC16
	bl	dprint_vfmw
	b	.L22
	.p2align 3
.L28:
	ldr	x21, .LC9
	mov	x2, 17920
	ldr	x1, .LC10
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w0, [x20, 8]
	mov	w1, w22
	bl	MEM_WritePhyWord
	b	.L16
	.p2align 3
.L31:
	ldr	x0, .LC19
	mov	w1, 2
	str	w1, [x0]
	b	.L11
.L27:
	ldr	x1, .LC8
	ldr	w2, [x20]
	bl	dprint_vfmw
	b	.L11
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC10:
	.xword	.LANCHOR1
	.align	3
.LC11:
	.xword	.LANCHOR2
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	.LANCHOR3
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC19:
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
	ldr	x3, .LC22
	mov	x0, 0
	b	.L35
	.p2align 3
.L33:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L41
.L35:
	add	x1, x3, x0, lsl 4
	ldr	x1, [x1, 16]
	add	x2, x1, 80
	cmp	x19, x2
	cbz	x1, .L33
	bne	.L33
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L41:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	3
.LC22:
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
	ldr	x3, .LC23
	lsl	x1, x0, 6
	ldr	x2, .LC24
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
.LC23:
	.xword	.LANCHOR0
	.align	3
.LC24:
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
	ldr	x2, .LC25
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
.LC25:
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
	ldr	x20, .LC26
	mov	w1, 3
	add	x22, x20, x23, lsl 2
	ldr	w0, [x22, 8]
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	ldr	w0, [x22, 8]
	add	w0, w0, 2076
	bl	MEM_ReadPhyWord
	ldr	x22, .LC27
	mov	w24, w0
	ldr	x2, [x22]
	cbnz	w23, .L46
	ldr	w21, [x2, 120]
	tbz	x21, 0, .L62
	orr	w21, w21, 32
	str	w21, [x2, 120]
.L46:
	mov	w0, 0
	mov	w3, 10000
	b	.L50
	.p2align 3
.L53:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L63
.L50:
	ldr	w1, [x2, 372]
	cbnz	w19, .L53
	tbz	x1, 1, .L53
	mov	w1, 9999
	cmp	w0, w1
	bhi	.L64
.L55:
	and	w21, w21, -33
	str	w21, [x2, 120]
.L54:
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
.L63:
	ldr	x1, .LC31
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w19, .L54
	b	.L56
	.p2align 3
.L64:
	ldr	x1, .LC31
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
.L56:
	ldr	x2, [x22]
	b	.L55
	.p2align 3
.L62:
	ldr	x1, .LC29
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
.LC26:
	.xword	.LANCHOR0
	.align	3
.LC27:
	.xword	g_pstRegCrg
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
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
	ldr	x19, .LC32
	ldr	w0, [x19, 580]
	cmp	w20, w0
	beq	.L69
.L65:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L69:
	ldr	x0, .LC33
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L67
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L68:
	ldr	x1, .LC34
	mov	w0, 1
	str	wzr, [x19, 584]
	ldr	x1, [x1, 256]
	blr	x1
	b	.L65
	.p2align 3
.L67:
	mov	w0, 0
	bl	ResetSCD
	b	.L68
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	g_HalDisable
	.align	3
.LC34:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_MaskInt
	.type	SCDDRV_MaskInt, %function
SCDDRV_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC35
	mov	w1, 1
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 8]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_MaskInt, .-SCDDRV_MaskInt
	.align	3
.LC35:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_EnableInt
	.type	SCDDRV_EnableInt, %function
SCDDRV_EnableInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC36
	mov	w1, 0
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 8]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_EnableInt, .-SCDDRV_EnableInt
	.align	3
.LC36:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetRawStreamArray
	.type	ResetRawStreamArray, %function
ResetRawStreamArray:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L72
	ldr	x3, .LC37
	mov	x2, 32792
	movk	x2, 0x1, lsl 16
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
.L72:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetRawStreamArray, .-ResetRawStreamArray
	.align	3
.LC37:
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
	ldr	x0, .LC38
	add	x19, x0, x19, sxtw 4
	ldr	w0, [x20, 4]
	cmp	w0, wzr
	ldr	x0, [x19, 16]
	ccmp	x0, xzr, 4, ne
	beq	.L80
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
	beq	.L81
	sxtw	x3, w3
	ldr	x5, .LC39
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
.L79:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L81:
	mov	w0, -4
	b	.L79
.L80:
	mov	w0, -1
	b	.L79
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	3
.LC38:
	.xword	.LANCHOR0
	.align	3
.LC39:
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
	bhi	.L85
	ldr	x0, .LC40
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L85
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
.L83:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	mov	w0, -4
	b	.L83
	.size	GetRawState, .-GetRawState
	.align	3
.LC40:
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
	beq	.L89
	sxtw	x0, w0
	ldr	x1, .LC41
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
.L88:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L89:
	mov	w0, -3
	b	.L88
	.size	ShowRawPacket, .-ShowRawPacket
	.align	3
.LC41:
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
	cbz	x23, .L91
	add	x20, x23, 98304
	ldp	w1, w0, [x20]
	cmp	w1, w0
	beq	.L92
	ldr	w24, [x20, 12]
	str	w1, [x20, 16]
	mov	w21, w24
	sxtw	x22, w24
.L93:
	sxtw	x1, w1
	ldr	x3, .LC42
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
.L94:
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
.L92:
	mov	x22, 0
	mov	w21, 0
	mov	w24, 0
	str	w1, [x20, 16]
	b	.L94
	.p2align 3
.L91:
	mov	x20, 98304
	mov	x22, 0
	mov	w21, 0
	mov	w24, 0
	ldp	w1, w0, [x20]
	str	w1, [x20, 16]
	cmp	w1, w0
	beq	.L94
	b	.L93
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	3
.LC42:
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
	cbz	x19, .L101
	add	x3, x19, 98304
	ldp	w0, w2, [x3]
	cmp	w0, w2
	beq	.L100
	sxtw	x0, w0
	ldr	w4, [x3, 12]
	lsl	x2, x0, 2
	sub	x0, x2, x0
	add	w1, w20, w4
	add	x0, x19, x0, lsl 5
	ldr	w0, [x0, 8]
	cmp	w1, w0
	bge	.L101
	mov	w0, 0
	str	w1, [x3, 12]
.L98:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L101:
	mov	w0, -1
	b	.L98
	.p2align 3
.L100:
	mov	w0, -3
	b	.L98
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
	beq	.L104
	add	x0, x19, 98304
	ldp	w2, w1, [x0]
	cmp	w2, w1
	beq	.L105
	ldr	w1, [x0, 12]
	mov	w0, 0
	str	w1, [x20]
.L103:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L104:
	mov	w0, -1
	b	.L103
	.p2align 3
.L105:
	mov	w0, -3
	b	.L103
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
	beq	.L122
	ldr	x27, .LC43
	mov	x0, 0
	b	.L110
	.p2align 3
.L108:
	cmp	x0, 32
	beq	.L111
.L110:
	add	x1, x27, x0, lsl 4
	mov	w3, w0
	add	x0, x0, 1
	ldr	x1, [x1, 16]
	add	x2, x1, 80
	cmp	x26, x2
	cbz	x1, .L108
	bne	.L108
	tbnz	w3, #31, .L111
	add	x23, x26, 98304
	ldp	w0, w2, [x23]
	cmp	w0, w2
	bgt	.L133
.L130:
	sub	w2, w2, w0
	cmp	w2, w20
	bcc	.L134
	mov	w24, w0
	cbz	w20, .L116
	ldr	x21, .LC48
	add	x27, x27, 16
	ldr	x22, .LC50
	mov	w25, 0
	add	x21, x21, 24
	add	x27, x27, x3, sxtw 4
	.p2align 2
.L117:
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
	bne	.L117
	ldr	w0, [x23]
	add	w20, w20, w0
	str	w20, [x23]
	cmp	w20, 1023
	ble	.L120
	sub	w20, w20, #1024
	str	w20, [x23]
.L120:
	str	wzr, [x23, 12]
.L131:
	mov	w0, 0
.L128:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L133:
	add	w2, w2, 1024
	b	.L130
.L116:
	cmp	w0, 1023
	str	w0, [x23]
	ble	.L131
	sub	w0, w0, #1024
	str	w0, [x23]
	b	.L131
	.p2align 3
.L122:
	mov	w0, -1
	b	.L128
.L134:
	ldr	x1, .LC47
	mov	w3, w20
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, -1
	b	.L128
	.p2align 3
.L111:
	ldr	x1, .LC45
	mov	w2, 484
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L128
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	3
.LC43:
	.xword	.LANCHOR0
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR3
	.align	3
.LC50:
	.xword	.LC49
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
	blt	.L142
	add	x8, x22, 98304
	ldr	w7, [x8]
	ldr	w4, [x8, 12]
	sxtw	x1, w7
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 8]
	sub	w4, w0, w4
	cbz	x22, .L143
	ldr	w1, [x8, 4]
	sub	w1, w1, w7
	add	w0, w1, 1024
	cmp	w1, wzr
	csel	w1, w0, w1, lt
.L137:
	add	w1, w7, w1
	cmp	w23, w4
	ccmp	w1, w7, 0, ge
	mov	w0, w7
	bls	.L144
	mov	w6, w7
	b	.L139
	.p2align 3
.L145:
	mov	w4, w2
.L139:
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
	cbz	w3, .L145
	cmp	w7, w6
	beq	.L138
	sub	w4, w23, w4
	str	w4, [x21]
.L141:
	str	w0, [x20]
	mov	w0, 0
	ldr	w1, [x8]
	sub	w6, w6, w1
	str	w6, [x19]
.L136:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L144:
	mov	w6, w7
	.p2align 2
.L138:
	str	w23, [x21]
	b	.L141
	.p2align 3
.L143:
	mov	w1, 0
	b	.L137
.L142:
	mov	w0, -1
	b	.L136
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
	blt	.L149
	stp	wzr, wzr, [x29, 52]
	cbz	x19, .L149
	add	x20, x19, 98304
	ldr	w1, [x20, 12]
	ldr	w0, [x20, 20]
	sub	w0, w0, w1
	asr	w21, w0, 31
	cbnz	w21, .L155
	cmp	w22, w0
	bgt	.L149
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
	ldr	x1, .LC54
	sxtw	x6, w0
	lsl	x2, x6, 2
	sub	x0, x2, x6
	mov	w2, 677
	add	x0, x19, x0, lsl 5
	ldrb	w7, [x0, 2]
	ldr	w6, [x0, 8]
	mov	w0, 26
	bl	dprint_vfmw
	ldrsw	x1, [x29, 60]
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x19, x0, lsl 5
	ldrb	w1, [x0, 2]
	cbnz	w1, .L150
	ldr	w1, [x29, 52]
	mov	x0, x19
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	beq	.L160
.L158:
	sxtw	x0, w0
	ldr	w2, [x20, 12]
	lsl	x1, x0, 2
	ldr	w3, [x29, 56]
	sub	x0, x1, x0
	add	w1, w3, w2
	add	x19, x19, x0, lsl 5
	ldr	w0, [x19, 8]
	cmp	w1, w0
	blt	.L161
.L149:
	mov	w21, -1
.L155:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L161:
	str	w1, [x20, 12]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L150:
	ldr	w5, [x0, 8]
	mov	w2, 682
	ldr	x1, .LC56
	mov	w0, 26
	ldp	w3, w4, [x29, 52]
	bl	dprint_vfmw
	ldr	w1, [x29, 52]
	mov	x0, x19
	add	w1, w1, 1
	stp	w1, wzr, [x29, 52]
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	bne	.L158
.L160:
	mov	w21, -3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DeleteRawLen, .-DeleteRawLen
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC56:
	.xword	.LC55
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
	bhi	.L162
	ldr	x0, .LC57
	ubfiz	x19, x19, 4, 32
	add	x0, x0, 16
	ldr	x0, [x0, x19]
	cbz	x0, .L165
	add	x19, x0, 262144
	ldr	w1, [x19, 160]
	cmp	w1, wzr
	ble	.L162
	add	x0, x0, 80
	bl	DeleteRawPacket
	str	wzr, [x19, 160]
.L162:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L165:
	ldr	x1, .LC59
	mov	w2, 709
	bl	dprint_vfmw
	b	.L162
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	3
.LC57:
	.xword	.LANCHOR0
	.align	3
.LC59:
	.xword	.LC58
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
	cbz	x19, .L168
	add	x19, x19, 98304
	ldr	w2, [x19, 20]
	str	w2, [x20]
	ldr	w0, [x19, 12]
	sub	w0, w2, w0
	str	w0, [x20]
	asr	w0, w0, 31
.L167:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L168:
	mov	w0, -1
	b	.L167
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
	cbz	x19, .L172
	add	x19, x19, 98304
	ldp	w2, w0, [x19]
	subs	w0, w0, w2
	bmi	.L171
	str	w0, [x20]
	mov	w0, 0
.L170:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L171:
	add	w2, w0, 1024
	str	w2, [x20]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L172:
	mov	w0, -1
	b	.L170
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
	beq	.L176
	mov	w0, 262143
	cmp	x22, xzr
	ccmp	w21, w0, 0, ne
	bls	.L176
	ldr	x3, .LC61
	mov	x2, 32824
	movk	x2, 0x2, lsl 16
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x20, 163840
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
.L176:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	3
.LC61:
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
	cbz	x19, .L177
	ldr	x3, .LC62
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	add	x0, x19, 8
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x19, 163840
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L177:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	3
.LC62:
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
	add	x1, x19, 163840
	ldp	w0, w2, [x1, 32]
	cmp	w2, w0
	sub	w0, w0, #1
	bhi	.L186
	sub	w0, w0, w2
	bcc	.L184
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L184:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L186:
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
	bhi	.L188
	add	x1, x19, 294912
	ldr	w0, [x1, 1192]
	add	w0, w0, 1
	str	w0, [x1, 1192]
.L188:
	sub	w2, w20, #1
	add	w0, w20, 79
	uxtb	w2, w2
	uxtb	w0, w0
	cmp	w2, 183
	ccmp	w0, 4, 0, ls
	bls	.L189
	add	w20, w20, 73
	uxtb	w20, w20
	cmp	w20, 3
	bls	.L189
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L189:
	add	x0, x19, 294912
	ldr	w1, [x0, 1196]
	add	w1, w1, 1
	str	w1, [x0, 1196]
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
	add	x0, x19, 294912
	ldr	w1, [x0, 1200]
	cmp	w1, 2
	ble	.L194
	and	w20, w20, 31
	cbz	w20, .L194
	ldr	w2, [x0, 1208]
	ldr	w1, [x0, 1212]
	sub	w3, w1, w2
	cmp	w3, 1
	beq	.L205
.L196:
	cmp	w1, w2
	beq	.L206
.L194:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L206:
	ldr	w2, [x0, 1204]
	cmp	w1, w2
	bne	.L194
.L197:
	cmp	w1, 20
	ccmp	w1, 1, 4, ne
	beq	.L194
	ldr	w1, [x0, 1192]
	cmp	w1, wzr
	ble	.L198
	sub	w1, w1, #1
	str	w1, [x0, 1192]
.L198:
	ldr	w1, [x0, 1196]
	add	w1, w1, 1
	str	w1, [x0, 1196]
	b	.L194
	.p2align 3
.L205:
	ldr	w3, [x0, 1204]
	sub	w3, w2, w3
	cmp	w3, 1
	bne	.L196
	b	.L197
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
	ldr	x0, .LC63
	ldr	x19, [x0, w21, sxtw 3]
	cbz	x19, .L207
	ldr	w0, [x19, 600]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	bne	.L207
	add	x20, x19, 294912
	ldr	w0, [x20, 1200]
	cmp	w0, 199
	bgt	.L207
	ldrb	w1, [x22]
	cbz	w1, .L225
.L215:
	mov	w3, 0
	mov	w22, 0
.L211:
	add	x4, x20, 1024
	ldr	w2, [x20, 1208]
	ldr	w1, [x20, 1212]
	add	w0, w0, 1
	stp	w1, w3, [x4, 184]
	stp	w0, w2, [x4, 176]
	mov	w1, w22
	mov	x0, x19
	bl	CheckData
	mov	x0, x19
	mov	w1, w22
	bl	CheckStartCodeCnt
	ldr	w0, [x20, 1200]
	cmp	w0, 199
	ble	.L207
	ldr	w1, [x20, 1192]
	ldr	w0, [x20, 1196]
	sub	w2, w1, w0
	cmp	w2, 49
	bgt	.L226
.L212:
	sub	w0, w0, w1
	cmp	w0, 49
	ble	.L207
	ldr	w0, [x19, 600]
	cbnz	w0, .L207
	ldr	x0, .LC64
	ldr	x4, [x0]
	cbz	x4, .L207
	mov	w3, 0
	mov	x2, 0
	mov	w1, 124
	mov	w0, w21
	blr	x4
.L207:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L225:
	ldrb	w1, [x22, 1]
	cbnz	w1, .L215
	ldrb	w1, [x22, 2]
	cmp	w1, 1
	bne	.L215
	ldrb	w22, [x22, 3]
	and	w3, w22, 31
	b	.L211
	.p2align 3
.L226:
	ldr	w2, [x19, 600]
	cmp	w2, 3
	bne	.L212
	ldr	x0, .LC64
	ldr	x4, [x0]
	cbz	x4, .L207
	mov	w1, 124
	mov	w3, 0
	mov	x2, 0
	mov	w0, w21
	blr	x4
	ldr	w1, [x20, 1192]
	ldr	w0, [x20, 1196]
	b	.L212
	.size	CheckStream, .-CheckStream
	.align	3
.LC63:
	.xword	s_pstVfmwChan
	.align	3
.LC64:
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
	mov	x22, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x22, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L229
	add	x19, x22, 163840
	ldp	w1, w0, [x19, 8]
	add	w0, w0, 1
	asr	w3, w0, 31
	lsr	w3, w3, 21
	add	w0, w0, w3
	and	w0, w0, 2047
	sub	w0, w0, w3
	cmp	w0, w1
	beq	.L230
	ldr	x0, [x20]
	mov	w1, w21
	bl	CheckStream
	ldrsw	x0, [x19, 12]
	mov	x2, 80
	ldr	x3, .LC65
	mov	x1, x20
	lsl	x21, x0, 6
	add	x21, x21, x0, lsl 4
	add	x21, x22, x21
	ldr	x3, [x3, 104]
	add	x0, x21, 8
	blr	x3
	ldr	w4, [x19, 12]
	mov	w5, 1
	mov	w0, 0
	add	w1, w4, 1
	sxtw	x2, w4
	lsl	x3, x2, 6
	add	x2, x3, x2, lsl 4
	asr	w3, w1, 31
	add	x22, x22, x2
	lsr	w2, w3, 21
	add	w1, w1, w2
	and	w1, w1, 2047
	strb	w5, [x22, 16]
	sub	w1, w1, w2
	str	w4, [x21, 28]
	str	w1, [x19, 12]
	ldr	w1, [x19, 40]
	ldp	w3, w4, [x20, 12]
	ldp	w5, w2, [x19, 44]
	add	w4, w3, w4
	str	w4, [x19, 36]
	add	w2, w2, 1
	ldr	w3, [x20, 16]
	add	w3, w1, w3
	str	w3, [x19, 40]
	ldr	w1, [x20, 16]
	add	w1, w5, w1
	stp	w1, w2, [x19, 44]
.L228:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L229:
	mov	w0, -1
	b	.L228
	.p2align 3
.L230:
	mov	w0, -4
	b	.L228
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetStreamSeg
	.type	SCDDRV_GetStreamSeg, %function
SCDDRV_GetStreamSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L238
	add	x20, x19, 163840
	ldp	w0, w3, [x20, 8]
	cmp	w0, w3
	beq	.L240
	sxtw	x2, w0
	lsl	x1, x2, 6
	b	.L245
	.p2align 3
.L235:
	add	w1, w0, 1
	asr	w0, w1, 31
	lsr	w0, w0, 21
	add	w1, w1, w0
	and	w1, w1, 2047
	sub	w0, w1, w0
	cmp	w0, w3
	sxtw	x2, w0
	lsl	x1, x2, 6
	beq	.L240
.L245:
	add	x1, x1, x2, lsl 4
	add	x1, x19, x1
	ldrsb	w1, [x1, 16]
	cmp	w1, 1
	bne	.L235
	lsl	x0, x2, 6
	add	x2, x0, x2, lsl 4
	add	x19, x19, x2
	adds	x1, x19, 8
	beq	.L240
	ldr	x3, .LC66
	mov	x2, 80
	mov	x0, x21
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 2
	strb	w0, [x19, 16]
	ldr	w5, [x19, 24]
	mov	w0, 26
	ldp	w4, w2, [x20, 44]
	ldr	x1, .LC68
	mov	w3, w5
	subs	w4, w4, w5
	csel	w4, w4, wzr, pl
	subs	w2, w2, #1
	csel	w2, w2, wzr, pl
	stp	w4, w2, [x20, 44]
	ldrb	w4, [x19, 17]
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	mov	w0, 0
.L232:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L240:
	mov	w0, -3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L238:
	mov	w0, -1
	b	.L232
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	3
.LC66:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC68:
	.xword	.LC67
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
	cbz	x20, .L267
	sub	w0, w22, #2048
	cmn	w0, #2050
	bls	.L267
	cmn	w22, #1
	add	x24, x20, 163840
	beq	.L280
	ldp	w0, w1, [x24, 8]
	cmp	w0, w1
	bne	.L277
	b	.L255
	.p2align 3
.L258:
	add	w0, w0, 1
	and	w0, w0, 2047
	cmp	w0, w1
	beq	.L255
.L277:
	cmp	w22, w0
	bne	.L258
	uxtw	x0, w0
	lsl	x19, x0, 6
	add	x0, x19, x0, lsl 4
	add	x0, x20, x0
	add	x19, x0, 8
	ldrsb	w1, [x0, 16]
	cmp	w1, 2
	beq	.L252
.L255:
	mov	w0, -3
.L276:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L280:
	ldp	w22, w0, [x24, 8]
	cmp	w22, w0
	beq	.L255
	sxtw	x0, w22
	ldr	x1, .LC70
	lsl	x25, x0, 6
	mov	w2, w22
	add	x25, x25, x0, lsl 4
	mov	w0, 0
	add	x25, x20, x25
	bl	dprint_vfmw
	add	x19, x25, 8
	ldr	w0, [x25, 24]
	cbz	w0, .L254
	ldr	x26, .LC74
	mov	x23, 0
	mov	w21, 0
	.p2align 2
.L253:
	ldr	x2, [x25, 8]
	mov	x1, x26
	mov	w0, 0
	add	w21, w21, 1
	ldrb	w2, [x2, x23]
	add	x23, x23, 1
	bl	dprint_vfmw
	ldr	w0, [x25, 24]
	cmp	w0, w21
	ccmp	w21, 15, 2, hi
	bls	.L253
.L254:
	ldr	x1, .LC72
	mov	w0, 0
	bl	dprint_vfmw
.L252:
	cbz	x19, .L255
	ldrb	w4, [x19, 9]
	mov	w5, w22
	ldr	x1, .LC76
	mov	w0, 26
	ldp	w2, w3, [x19, 12]
	strb	wzr, [x19, 8]
	bl	dprint_vfmw
	ldr	w21, [x24, 8]
	cmp	w22, w21
	beq	.L281
.L260:
	ldr	w2, [x19, 16]
	mov	w0, 0
	ldr	w1, [x24, 40]
	subs	w1, w1, w2
	csel	w1, w1, wzr, pl
	str	w1, [x24, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L281:
	ldr	x22, .LC77
	ldr	x23, .LC79
	add	x22, x22, 40
	b	.L263
	.p2align 3
.L261:
	ldr	w1, [x24, 12]
	add	x0, x20, x0
	cmp	w21, w1
	beq	.L264
	ldrsb	w1, [x0, 16]
	cbnz	w1, .L282
.L262:
	add	w21, w21, 1
	and	w21, w21, 2047
.L263:
	uxtw	x0, w21
	cmp	w21, 2047
	lsl	x1, x0, 6
	add	x0, x1, x0, lsl 4
	bls	.L261
	mov	x1, x23
	mov	x2, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x24, 12]
	cmp	w21, w1
	bne	.L262
	.p2align 2
.L264:
	ldr	w0, [x24, 36]
	str	w1, [x24, 8]
	str	w0, [x24, 32]
	b	.L260
	.p2align 3
.L282:
	str	w21, [x24, 8]
	ldr	w0, [x0, 20]
	str	w0, [x24, 32]
	b	.L260
.L267:
	mov	w0, -1
	b	.L276
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	3
.LC70:
	.xword	.LC69
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
.LC77:
	.xword	.LANCHOR3
	.align	3
.LC79:
	.xword	.LC78
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
	cbz	x19, .L285
	add	x19, x19, 163840
	mov	w0, 0
	ldr	w1, [x19, 40]
	str	w1, [x20]
.L284:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L285:
	mov	w0, -1
	b	.L284
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
	add	x1, x19, 163840
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x1, 12]
	ldr	w1, [x1, 8]
	sub	w0, w0, w1
	and	w0, w0, 2047
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
	cbz	x19, .L287
	add	x19, x19, 163840
	ldr	w0, [x19, 48]
	str	w0, [x21]
	ldr	w0, [x19, 44]
	str	w0, [x20]
.L287:
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
	ldr	x1, .LC81
	sxtw	x0, w19
	add	x2, x1, x0, lsl 2
	ldr	w3, [x2, 600]
	cbnz	w3, .L295
	lsl	x3, x0, 6
	add	x0, x3, x0, lsl 3
	add	x0, x1, x0
	ldr	w0, [x0, 584]
	cbz	w0, .L296
	mov	w1, 1
	mov	w0, 0
	str	w1, [x2, 600]
.L293:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L296:
	mov	w1, 2
	str	w1, [x2, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L295:
	mov	w0, -1
	b	.L293
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	3
.LC81:
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
	ldr	x0, .LC82
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	3
.LC82:
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
	ldr	x0, .LC83
	add	x0, x0, x19, sxtw 2
	ldr	w1, [x0, 600]
	cmp	w1, 2
	beq	.L298
	mov	w1, 2
	str	w1, [x0, 600]
.L298:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	3
.LC83:
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
	ldr	x0, .LC84
	add	x19, x0, x19, sxtw 2
	str	wzr, [x19, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	3
.LC84:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L306
	ldr	x20, .LC86
	sbfiz	x19, x19, 4, 32
	ldr	x0, .LC85
	mov	x2, 464
	add	x20, x20, 16
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	ldr	x0, [x20, x19]
	blr	x3
	ldr	x1, [x20, x19]
	mov	x2, -1
	mov	w0, 0
	add	x1, x1, 262144
	str	x2, [x1, 272]
.L305:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L306:
	mov	w0, -1
	b	.L305
	.size	SM_ClearInst, .-SM_ClearInst
	.align	3
.LC85:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC86:
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
	ldr	x20, .LC88
	ldr	x21, .LC89
	add	x19, x20, 16
	add	x20, x20, 528
	.p2align 2
.L308:
	ldr	x3, [x21, 96]
	mov	x0, x19
	mov	x2, 16
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	cmp	x19, x20
	bne	.L308
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_InstInit, .-SM_InstInit
	.align	3
.LC88:
	.xword	.LANCHOR0
	.align	3
.LC89:
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
	cbz	w20, .L312
	cmp	w20, 1
	ldr	x2, .LC91
	bne	.L324
	ldr	x1, .LC95
	mov	w3, 1306
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -7
	b	.L314
	.p2align 3
.L312:
	ldr	x21, .LC96
	mov	w1, 49152
	movk	w1, 0xf8c3, lsl 16
	add	x20, x21, 528
	ldr	w0, [x20, 48]
	str	w1, [x21, 8]
	cmp	w0, 1
	beq	.L317
	ldr	x3, .LC97
	mov	x2, 72
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	str	w19, [x21, 528]
	ldr	x2, .LC98
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
	add	w19, w19, 28672
	add	w19, w19, 127
	bl	MEM_Phy2Vir
	add	w19, w19, w22
	str	x0, [x20, 24]
	and	w19, w19, -128
	mov	w0, 16384
	str	w0, [x20, 36]
	mov	w0, w19
	str	w19, [x21]
	bl	MEM_Phy2Vir
	str	x0, [x21, 608]
	cbz	x0, .L325
	add	w22, w22, 45056
	ldr	w2, [x21, 8]
	add	w22, w22, 1536
	ldr	w0, [x21, 624]
	mov	w1, 17920
	cmp	w23, w22
	stp	w2, w0, [x20, 40]
	str	w1, [x21, 616]
	blt	.L317
	ldr	x0, [x20, 8]
	cbz	x0, .L317
	ldr	x0, [x20, 24]
	cbz	x0, .L317
	mov	w1, 1
	mov	w0, 0
	str	w1, [x20, 48]
.L314:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L324:
	ldr	x1, .LC93
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
.L317:
	mov	w0, -7
	b	.L314
.L325:
	ldr	x2, .LC91
	ldr	x1, .LC100
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L314
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	3
.LC91:
	.xword	.LANCHOR3
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC96:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC98:
	.xword	g_VfmwGlobalStat
	.align	3
.LC100:
	.xword	.LC99
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
	ldr	x4, .LC102
	add	x0, x4, 16
	add	x3, x4, 528
	b	.L328
	.p2align 3
.L327:
	cmp	x0, x3
	beq	.L336
.L328:
	ldr	x1, [x0]
	add	x0, x0, 16
	add	x2, x1, 262144
	cbz	x1, .L327
	ldr	w1, [x2, 248]
	cbz	w1, .L327
	ldr	w1, [x2, 236]
	cmp	w1, wzr
	bgt	.L327
	str	wzr, [x2, 248]
	cmp	x0, x3
	bne	.L328
.L336:
	sxtw	x1, w19
	ldr	x3, .LC103
	lsl	x0, x1, 6
	ldr	x5, .LC104
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
.LC102:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	g_VfmwGlobalStat
	.align	3
.LC104:
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
	beq	.L351
	ldr	x1, .LC108
	add	x0, x1, x21, sxtw 4
	ldr	x5, [x0, 16]
	cbz	x5, .L343
	add	x22, x5, 262144
	ldr	w0, [x19, 48]
	str	w0, [x22, 320]
	ldr	w2, [x5, 24]
	ldr	w0, [x19, 16]
	cmp	w2, w0
	beq	.L352
	cbz	w0, .L343
	ldr	x0, [x19]
	cbz	x0, .L343
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
	mov	w0, 2048
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
	ble	.L343
	add	x0, x5, 98304
	add	x20, x5, 8
	add	x0, x0, 104
	bl	ConfigStreamSegArray
	ldr	x23, .LC109
	mov	x2, 72
	mov	x1, x19
	mov	x0, x20
	ldr	x3, [x23, 104]
	blr	x3
	str	wzr, [x22, 236]
.L342:
	ldr	x3, [x23, 104]
	mov	x2, 72
	mov	x1, x19
	mov	x0, x20
	blr	x3
	mov	w0, 2
	str	w0, [x22, 308]
	ldr	w0, [x19, 12]
	cmp	w0, 2
	beq	.L353
.L344:
	mov	w0, 0
	str	w21, [x22, 232]
.L339:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L353:
	mov	w0, 3
	str	w0, [x22, 308]
	b	.L344
	.p2align 3
.L352:
	add	x20, x5, 8
	ldr	x23, .LC109
	b	.L342
	.p2align 3
.L343:
	mov	w0, -1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L351:
	ldr	x1, .LC107
	mov	x4, x19
	mov	w3, w21
	mov	w2, 1399
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L339
	.size	SM_Config, .-SM_Config
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	.LANCHOR0
	.align	3
.LC109:
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
	bhi	.L362
	cbnz	w20, .L363
	ldr	x1, .LC115
	add	x19, x1, x19, sxtw 4
	ldr	x2, [x19, 16]
	cbz	x2, .L358
	add	x2, x2, 262144
	ldr	w0, [x2, 236]
	cbz	w0, .L356
	add	x0, x1, 528
	ldr	w4, [x0, 32]
	ldr	x6, [x0, 8]
	ldr	x3, [x0, 24]
	ldp	w7, w5, [x0, 16]
	ldr	w0, [x0, 36]
	stp	w4, w0, [x2, 208]
	mov	w0, 2048
	str	x6, [x2, 184]
	str	w0, [x2, 216]
	mov	w0, 0
	stp	w5, w7, [x2, 192]
	str	x3, [x2, 200]
	str	wzr, [x2, 236]
.L356:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L362:
	ldr	x1, .LC112
	mov	w3, w19
	mov	w2, 1479
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L356
	.p2align 3
.L363:
	ldr	x1, .LC114
	mov	w3, w20
	mov	w2, 1486
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L356
.L358:
	mov	w0, -1
	b	.L356
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC115:
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
	ldr	x0, .LC117
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L368
	ldr	w1, [x0, 28]
	cbz	w1, .L368
	add	x1, x0, 262144
	ldr	w0, [x1, 248]
	cbnz	w0, .L368
	mov	w2, 1
	str	w2, [x1, 248]
.L365:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L368:
	mov	w0, -7
	b	.L365
	.size	SM_Start, .-SM_Start
	.align	3
.LC117:
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
	ldr	x0, .LC118
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	cbz	x0, .L371
	add	x1, x0, 262144
	ldr	w0, [x1, 248]
	cbz	w0, .L370
	ldr	w0, [x1, 236]
	cmp	w0, wzr
	bgt	.L372
	mov	w0, 0
	str	wzr, [x1, 248]
.L370:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L372:
	mov	w0, -7
	b	.L370
	.p2align 3
.L371:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Stop, .-SM_Stop
	.align	3
.LC118:
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
	bhi	.L383
	ldr	x0, .LC119
	add	x20, x0, x20, sxtw 4
	ldr	x0, [x20, 16]
	cbz	x0, .L389
	add	x2, x0, 262144
	adds	x1, x0, 80
	ldr	w3, [x2, 248]
	strb	w3, [x19]
	ldr	w2, [x2, 300]
	str	w2, [x19, 20]
	beq	.L379
	add	x3, x1, 98304
	ldr	w2, [x3, 4]
	ldr	w3, [x3]
	subs	w2, w2, w3
	bmi	.L390
	str	w2, [x19, 4]
.L381:
	add	x1, x1, 98304
	ldr	w2, [x1, 20]
	str	w2, [x19, 12]
	ldr	w1, [x1, 12]
	sub	w2, w2, w1
	str	w2, [x19, 12]
.L379:
	add	x0, x0, 98304
	add	x0, x0, 104
	add	x2, x0, 163840
	ldp	w3, w1, [x2, 8]
	sub	w1, w1, w3
	and	w1, w1, 2047
	str	w1, [x19, 8]
	cbz	x0, .L384
	ldr	w1, [x2, 40]
	mov	w0, 0
	str	w1, [x19, 16]
.L388:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L390:
	add	w2, w2, 1024
	str	w2, [x19, 4]
	b	.L381
	.p2align 3
.L389:
	cbz	x19, .L383
	strb	wzr, [x19]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L384:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L383:
	mov	w0, -1
	b	.L388
	.size	SM_GetInfo, .-SM_GetInfo
	.align	3
.LC119:
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
	b	.L392
	.p2align 3
.L394:
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	ldr	w1, [x21]
	ldr	w3, [x4, 8]
	add	w3, w1, w3
	str	w3, [x21]
	ldr	w1, [x2, 4]
	cmp	w0, w1
	beq	.L396
	ldr	w1, [x19]
	cmp	w1, 1024
	bhi	.L396
.L392:
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
	cbnz	w1, .L394
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L396:
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
	cbz	w4, .L402
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w6, [x0, 8]
	cmp	w6, 2
	bgt	.L403
	mov	w0, w6
	mov	w3, 3
	mov	w2, 0
	b	.L400
	.p2align 3
.L401:
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 8]
	add	w6, w6, w0
	cmp	w6, 2
	bgt	.L405
.L400:
	add	w2, w2, 1
	add	w5, w5, 1
	cmp	w2, w4
	sub	w3, w3, w0
	and	w5, w5, 1023
	bne	.L401
.L402:
	mov	w0, -4
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L405:
	sxtw	x3, w3
.L399:
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
.L403:
	mov	x3, 3
	mov	w2, 0
	b	.L399
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
	ldr	x0, .LC120
	mov	x1, x19
	add	x0, x0, x1, sxtw 4
	ldr	x28, [x0, 16]
	cbz	x28, .L427
	add	x22, x28, 80
	add	x25, x28, 98304
	add	x0, x25, 104
	cmp	x22, xzr
	ccmp	x0, xzr, 4, ne
	str	x0, [x29, 104]
	ccmp	x26, xzr, 4, ne
	beq	.L427
	add	x0, x22, 98304
	ldp	w23, w4, [x0]
	cmp	w4, w23
	beq	.L447
	uxtw	x1, w23
	mov	w0, w23
	lsl	x2, x1, 2
	mov	x3, x1
	sub	x2, x2, x1
	mov	w21, 1
	add	x1, x22, x2, lsl 5
	ldr	w27, [x1, 8]
	b	.L409
	.p2align 3
.L411:
	add	w21, w21, 1
	ldr	w1, [x2, 8]
	cmp	w21, 1024
	ccmp	w4, w0, 4, ls
	add	w27, w27, w1
	beq	.L447
.L409:
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
	cbnz	w1, .L411
	ldr	x0, [x29, 104]
	cbz	x0, .L424
	ldr	x0, .LC121
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	ldr	x3, [x0, 96]
	add	x0, x25, 112
	blr	x3
	add	x0, x25, 104
	add	x0, x0, 163840
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L424:
	add	x0, x25, 104
	add	x0, x0, 163840
	ldr	w1, [x0, 28]
	cmp	w1, w27
	blt	.L449
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
	beq	.L414
	cbz	w21, .L447
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w25, [x1, 8]
	cmp	w25, 2
	bgt	.L428
	mov	w6, 3
	mov	w2, 0
	mov	w5, w25
	b	.L417
	.p2align 3
.L418:
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w5, [x1, 8]
	add	w25, w25, w5
	cmp	w25, 2
	bgt	.L450
.L417:
	add	w2, w2, 1
	add	w23, w23, 1
	cmp	w2, w21
	sub	w6, w6, w5
	and	w23, w23, 1023
	bne	.L418
	.p2align 2
.L447:
	mov	w0, -4
.L444:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L450:
	sxtw	x6, w6
.L415:
	lsl	x1, x20, 2
	sub	w21, w21, w2
	sub	x1, x1, x20
	sub	w25, w25, #3
	add	x1, x22, x1, lsl 5
	ldr	x28, [x1, 40]
	add	x28, x28, x6
	.p2align 2
.L414:
	str	w0, [x26, 12]
	bl	MEM_Phy2Vir
	str	x0, [x26]
	lsl	x1, x19, 2
	sub	x2, x24, x0
	sub	x1, x1, x19
	str	w2, [x26, 16]
	mov	w3, 1
	add	x1, x22, x1, lsl 5
	ldr	x2, [x1, 64]
	str	x2, [x26, 24]
	ldr	x2, [x1, 64]
	str	x2, [x26, 32]
	ldr	x2, [x1, 48]
	str	x2, [x26, 40]
	strb	w3, [x26, 9]
	ldr	x2, [x1, 56]
	str	x2, [x26, 48]
	ldr	w2, [x1, 20]
	str	w2, [x26, 56]
	ldr	w2, [x1, 24]
	str	w2, [x26, 60]
	ldr	w2, [x1, 28]
	str	w2, [x26, 64]
	ldr	w1, [x1, 32]
	str	w1, [x26, 68]
	cbz	w21, .L419
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L447
	ldr	x0, .LC121
	mov	w19, 0
	uxtw	x20, w23
	str	x0, [x29, 112]
	b	.L421
	.p2align 3
.L422:
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L447
.L421:
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
	ldr	w1, [x26, 16]
	sub	x2, x2, x20
	uxtw	x20, w23
	lsl	x0, x20, 2
	add	w25, w1, w25
	add	x2, x22, x2, lsl 5
	sub	x0, x0, x20
	cmp	w21, w19
	add	x0, x22, x0, lsl 5
	ldrb	w1, [x2, 1]
	strb	w1, [x26, 10]
	str	w25, [x26, 16]
	ldr	w25, [x0, 8]
	ldr	x28, [x0, 40]
	bne	.L422
	ldr	x0, [x26]
.L419:
	cbz	x0, .L451
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
.L449:
	ldr	x1, .LC123
	mov	w2, w27
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	cbz	w0, .L447
	ldr	x1, .LC125
	mov	w2, 1713
	mov	w0, 0
	bl	dprint_vfmw
	b	.L447
.L427:
	mov	w0, -1
	b	.L444
.L428:
	mov	x6, 3
	mov	w2, 0
	b	.L415
.L451:
	ldr	x2, .LC126
	mov	w3, 1774
	ldr	x1, .LC128
	mov	w0, 1
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -4
	b	.L444
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	3
.LC120:
	.xword	.LANCHOR0
	.align	3
.LC121:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC126:
	.xword	.LANCHOR3
	.align	3
.LC128:
	.xword	.LC127
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
	beq	.L456
	sub	w0, w19, #2
	cmp	w0, 1
	ccmp	w19, 6, 4, hi
	beq	.L456
	cmp	w19, 1
	beq	.L458
.L454:
	cmp	w19, 15
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L456:
	mov	w0, 0
.L453:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L458:
	ldr	w1, [x20]
	mov	w0, 0
	cbz	w1, .L454
	b	.L453
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldr	x20, .LC129
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L459
	ldr	x19, .LC130
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	w1, [x22, 16]
	ldr	x2, [x20, w21, sxtw 3]
	ldr	x3, [x19, 88]
	ldr	x0, [x22]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L459:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	3
.LC129:
	.xword	vfmw_save_seg_file
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC131
	cmp	x20, xzr
	add	x0, x0, x21, sxtw 4
	ldr	x19, [x0, 16]
	ccmp	x19, xzr, 4, ne
	beq	.L468
	ldr	w0, [x19, 20]
	add	x1, x19, 36
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L475
.L466:
	add	x0, x19, 98304
	mov	x1, x20
	add	x0, x0, 104
	add	x19, x19, 262144
	bl	SCDDRV_GetStreamSeg
	cbz	w0, .L476
	ldr	w1, [x19, 300]
	add	w1, w1, 1
	str	w1, [x19, 300]
.L465:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L475:
	mov	x1, x20
	mov	w0, w21
	bl	SM_CopyRawToSeg
	cbz	w0, .L466
	ldr	x1, .LC133
	add	x19, x19, 262144
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w1, [x19, 300]
	mov	w0, -7
	add	w1, w1, 1
	str	w1, [x19, 300]
	b	.L465
	.p2align 3
.L476:
	mov	x1, x20
	mov	w0, w21
	str	wzr, [x19, 300]
	bl	SCDDRV_SaveStreamSeg
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L468:
	mov	w0, -1
	b	.L465
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	3
.LC131:
	.xword	.LANCHOR0
	.align	3
.LC133:
	.xword	.LC132
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
	ldr	x0, .LC134
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
.LC134:
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
	ldr	x1, .LC135
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	3
.LC135:
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
	ldr	x0, .LC136
	ldr	x0, [x0]
	blr	x0
	mov	w3, w0
	add	x1, x19, 262144
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
.LC136:
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
	ldr	x0, .LC137
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
.LC137:
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
	bl	GetFreeSegBufSize.part.4
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
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	bne	.L504
.L501:
	ldr	w0, [x20]
	cmp	w0, 78
	bls	.L505
	sub	w0, w0, #79
	str	w0, [x20]
.L503:
	add	x19, x19, 163840
	mov	w2, 2048
	ldp	w0, w1, [x19, 8]
	sub	w0, w1, w0
	and	w0, w0, 2047
	sub	w0, w2, w0
	str	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L505:
	str	wzr, [x20]
	b	.L503
	.p2align 3
.L504:
	mov	x1, x20
	mov	x0, x19
	bl	GetFreeSegBufSize.part.4
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
	cmp	w19, 512
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
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x23, x2
	mov	x21, x3
	mov	x22, x4
	bl	_mcount
	cbz	x19, .L513
	add	x0, x19, 98304
	ldr	w1, [x0, 20]
	str	w1, [x23]
	ldr	w2, [x0, 12]
	sub	w1, w1, w2
	str	w1, [x23]
	ldr	w1, [x0, 4]
	ldr	w0, [x0]
	sub	w0, w1, w0
	cmp	w0, wzr
	blt	.L518
.L517:
	ldr	w2, [x23]
	cset	w3, eq
	mov	w0, -5
	cmp	w2, 3
	cset	w1, ls
	orr	w1, w3, w1
	cbnz	w1, .L510
	mov	x0, x20
	mov	x2, x22
	mov	x1, x21
	bl	SCDDRV_GetSegStreamStatus
	ldr	w0, [x22]
	cmp	w0, 512
	bls	.L515
	add	x20, x20, 163840
	ldr	w1, [x21]
	mov	w0, -6
	ldr	w2, [x20, 28]
	cmp	w1, w2, lsr 3
	csel	w0, wzr, w0, hi
.L510:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L518:
	cmn	w0, #1024
	b	.L517
	.p2align 3
.L513:
	mov	w0, -5
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
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
	add	x0, x20, 262144
	ldr	w2, [x20, 20]
	mov	w4, 1
	strb	w4, [x19, 2]
	mov	x1, 104
	cmp	w2, 6
	ldr	w3, [x0, 196]
	movk	x1, 0x4, lsl 16
	str	w3, [x19, 4]
	add	x1, x20, x1
	cset	w5, eq
	cmp	w2, 1
	ldr	x3, [x0, 184]
	ccmp	w2, 15, 4, ne
	str	x3, [x19, 8]
	ldr	w3, [x0, 208]
	str	w3, [x19, 24]
	ldr	w6, [x0, 216]
	ldr	w3, [x0, 308]
	mul	w3, w3, w6
	str	w3, [x19, 28]
	ldr	w3, [x1, 24]
	str	w3, [x19, 32]
	ldp	w6, w3, [x1, 24]
	add	w3, w6, w3
	str	w3, [x19, 36]
	ldr	w1, [x1, 36]
	strb	w4, [x19]
	add	w1, w1, 3
	and	w1, w1, -4
	str	w1, [x19, 40]
	ldr	w1, [x20, 48]
	str	w1, [x19, 52]
	str	w5, [x19, 68]
	beq	.L524
	cmp	w2, 6
	beq	.L522
	sub	w1, w2, #2
	cmp	w1, 1
	bhi	.L520
.L522:
	strb	w4, [x19, 1]
	mov	w1, 1
	stp	w2, w1, [x19, 44]
	stp	w1, w1, [x19, 56]
	ldr	w0, [x0, 456]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L524:
	mov	w2, 0
.L520:
	strb	wzr, [x19, 1]
	mov	w1, 1
	stp	w2, w1, [x19, 44]
	stp	w1, w1, [x19, 56]
	ldr	w0, [x0, 456]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
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
	add	x19, x20, 262144
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	cmp	w22, w21
	str	w22, [x19, 280]
	str	w21, [x19, 284]
	bls	.L528
	strb	wzr, [x20, 2]
.L527:
	mov	w1, 1
	ldr	x0, .LC139
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
.L528:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L527
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	3
.LC139:
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
	ldr	x0, .LC140
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L536
	cmp	w20, 4
	ldr	x22, .LC141
	beq	.L537
.L532:
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
.L536:
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
.L537:
	add	x0, x22, x19, lsl 2
	ldr	w0, [x0, 8]
	add	w0, w0, 4
	cbnz	w21, .L533
	bl	MEM_ReadPhyWord
	uxth	w21, w0
	b	.L532
	.p2align 3
.L533:
	bl	MEM_ReadPhyWord
	orr	w21, w0, 65536
	b	.L532
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	3
.LC140:
	.xword	g_HalDisable
	.align	3
.LC141:
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
	beq	.L541
	orr	w0, w0, 1
	strb	w0, [x19]
.L540:
	ldr	w1, [x20]
	ldrb	w0, [x19]
	lsr	w1, w1, 31
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
.L541:
	and	w0, w0, -2
	strb	w0, [x19]
	b	.L540
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
	cbz	x20, .L548
	ldr	w0, [x20, 12]
	cbz	w0, .L550
	ldr	x0, [x20]
	cbz	x0, .L550
	add	x1, x19, 163840
	ldp	w2, w0, [x1, 32]
	cmp	w0, w2
	sub	w2, w2, #1
	bhi	.L552
	sub	w0, w2, w0
	bcc	.L546
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L546:
	ldr	w2, [x20, 16]
	mov	w1, -7
	cmp	w2, w0
	csel	w0, wzr, w1, ls
.L544:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L552:
	ldr	w1, [x1, 28]
	add	w2, w2, w1
	sub	w0, w2, w0
	b	.L546
	.p2align 3
.L550:
	mov	w0, -7
	b	.L544
.L548:
	mov	w0, -1
	b	.L544
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
	str	x1, [x19, 24]
	ldr	x2, [x0, 48]
	str	x2, [x19, 40]
	ldr	x2, [x0, 64]
	str	x2, [x19, 32]
	ldr	x2, [x0, 56]
	str	x2, [x19, 48]
	ldr	w2, [x0, 20]
	str	w2, [x19, 56]
	ldr	w2, [x0, 24]
	str	w2, [x19, 60]
	ldr	w2, [x0, 28]
	str	w2, [x19, 64]
	ldr	w0, [x0, 32]
	str	w0, [x19, 68]
	ldr	x0, [x21]
	cmp	x1, x0
	beq	.L556
	str	x1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L556:
	mov	x0, -1
	str	x0, [x19, 24]
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
	beq	.L562
	cmp	w19, 2
	mov	w0, 0
	beq	.L563
	mov	w1, -33488896
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L562:
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
.L563:
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
	.global	CorrectSegPhyAddr
	.type	CorrectSegPhyAddr, %function
CorrectSegPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, w20
	orr	w0, w19, -2147483648
	csel	w0, w0, w19, cc
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CorrectSegPhyAddr, .-CorrectSegPhyAddr
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
	mov	w0, 2048
	add	x2, x2, 163840
	mov	w5, w3
	ldp	w10, w1, [x2, 8]
	sub	w10, w1, w10
	and	w10, w10, 2047
	sub	w10, w0, w10
	tbnz	w3, #31, .L576
	add	x21, x21, 262144
	ldr	x1, [x4, 104]
	mov	w9, -33488896
	mov	w11, -1241448448
	ldr	w6, [x2, 24]
	ldr	w8, [x21, 308]
	ldr	w7, [x21, 252]
	mul	w4, w3, w8
	b	.L575
	.p2align 3
.L570:
	cmp	w7, 2
	beq	.L578
	cmp	w0, w9
	beq	.L573
.L574:
	sub	w5, w5, #1
	mov	w19, w3
	cmn	w5, #1
	sub	w4, w4, w8
	beq	.L576
.L579:
	sub	w3, w3, #1
.L575:
	ldr	w0, [x20, w4, uxtw 2]
	and	w0, w0, 2147483647
	cmp	w0, w6
	orr	w2, w0, -2147483648
	csel	w0, w2, w0, cc
	cmp	w7, 1
	sub	w0, w0, w6
	ldr	w0, [x1, x0]
	bne	.L570
	cmp	w0, w11
	cset	w2, eq
.L571:
	cmp	w0, w9
	beq	.L573
	cbz	w2, .L574
	.p2align 2
.L573:
	cmp	w10, w3
	mov	w19, w3
	bcs	.L576
	sub	w5, w5, #1
	sub	w3, w3, #1
	cmn	w5, #1
	mov	w19, w3
	sub	w4, w4, w8
	bne	.L579
.L576:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L578:
	ubfx	x2, x0, 16, 8
	sub	w2, w2, #128
	cmp	w2, 3
	cset	w2, ls
	b	.L571
	.size	GetNextVop, .-GetNextVop
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
	beq	.L582
	mov	w0, 0
.L582:
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
	ldr	x1, .LC143
	mov	w3, w20
	mov	w2, 2541
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
.LC143:
	.xword	.LC142
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
	.global	ProcessNoSeg
	.type	ProcessNoSeg, %function
ProcessNoSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	add	x0, x19, 262144
	ldr	w1, [x0, 284]
	ldr	w2, [x0, 280]
	ldr	w20, [x0, 164]
	cmp	w2, w1
	cset	w1, gt
	strb	w1, [x19]
	cbnz	w21, .L586
	sub	w1, w20, #3
	cmp	w20, 4
	csel	w1, w1, wzr, cs
.L587:
	add	x0, x19, 80
	bl	DeleteRawLen
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L586:
	ldr	w1, [x0, 132]
	ldr	x2, [x0, 200]
	lsl	w0, w1, 2
	sub	w0, w0, w1
	ldr	w1, [x2, 4]
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	and	w1, w1, 2147483647
	sub	w2, w20, w1
	cmp	w2, w0, asr 2
	bls	.L587
	ldr	x1, .LC145
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w20
	add	x0, x19, 80
	bl	DeleteRawLen
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ProcessNoSeg, .-ProcessNoSeg
	.align	3
.LC145:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessNotMpeg4ScdUpMsg
	.type	ProcessNotMpeg4ScdUpMsg, %function
ProcessNotMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	add	x22, x27, 262144
	add	x21, x27, 98304
	mov	w25, w1
	str	w2, [x29, 104]
	bl	_mcount
	add	x21, x21, 104
	ldr	w23, [x22, 308]
	add	x0, x27, 80
	mov	w26, 1
	str	x0, [x29, 112]
	mov	x24, x21
	sub	w0, w23, #1
	add	x19, x21, 163840
	mov	w27, 0
	stp	xzr, xzr, [x29, 128]
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	ldr	x28, [x22, 200]
	str	w0, [x29, 124]
	b	.L590
	.p2align 3
.L604:
	ldr	x4, [x24]
	sub	w3, w3, w0
	sub	w1, w0, w1
	mov	w2, 1
	add	x1, x4, x1
	strb	w2, [x29, 137]
	cmp	w3, 3
	str	x1, [x29, 128]
	stp	w0, w3, [x29, 140]
	ble	.L603
	mov	x1, x21
	add	x0, x29, 128
	bl	CheckSegValid
	cbnz	w0, .L599
	ldr	w1, [x28, w26, uxtw 2]
	add	x2, x22, 272
	ldr	x0, [x29, 112]
	add	x3, x29, 128
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 128
	mov	x0, x21
	bl	InsertStreamSeg
	cbnz	w0, .L599
.L595:
	add	w26, w26, w23
	mov	w27, w20
.L590:
	cmp	w27, w25
	beq	.L599
	ldr	w1, [x29, 124]
	sub	w0, w26, #1
	add	w20, w27, 1
	add	w2, w1, w26
	ldr	w1, [x19, 24]
	ldr	w0, [x28, w0, uxtw 2]
	ldr	w3, [x28, w2, uxtw 2]
	and	w0, w0, 2147483647
	orr	w2, w0, -2147483648
	cmp	w1, w0
	and	w3, w3, 2147483647
	csel	w0, w2, w0, hi
	cmp	w1, w3
	orr	w2, w3, -2147483648
	csel	w3, w2, w3, hi
	cmp	w0, w3
	bls	.L604
	ldr	w2, [x29, 104]
	sub	w4, w3, w1
	ldr	x8, [x24]
	sub	w1, w0, w1
	sub	w2, w2, w0
	add	w3, w2, w4
	add	x1, x8, x1
	stp	w0, w3, [x29, 140]
	str	x1, [x29, 128]
	cmp	w3, 3
	ldp	w1, w0, [x19, 8]
	ble	.L605
	sub	w0, w0, w1
	mov	w1, 2048
	and	w0, w0, 2047
	str	w4, [x29, 108]
	sub	w0, w1, w0
	str	w2, [x29, 120]
	cmp	w0, 2
	bls	.L599
	mov	x1, x21
	add	x0, x29, 128
	bl	CheckSegValid
	cbnz	w0, .L599
	ldr	w4, [x29, 108]
	ldr	w2, [x29, 120]
	cbnz	w4, .L601
	str	w2, [x29, 144]
	mov	w0, 1
	strb	w0, [x29, 137]
	add	x2, x22, 272
	ldr	x0, [x29, 112]
	add	x3, x29, 128
	ldr	w1, [x28, w26, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 128
	mov	x0, x21
	bl	InsertStreamSeg
	b	.L595
	.p2align 3
.L601:
	str	w2, [x29, 144]
	add	x3, x29, 128
	strb	wzr, [x29, 137]
	add	x2, x22, 272
	ldr	x0, [x29, 112]
	ldr	w1, [x28, w26, uxtw 2]
	str	w4, [x29, 120]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x22, 232]
	add	x1, x29, 128
	mov	x0, x21
	bl	InsertStreamSeg
	ldr	w8, [x19, 24]
	mov	w3, 1
	ldr	w4, [x29, 120]
	add	x1, x29, 128
	ldr	x6, [x24]
	mov	x0, x21
	ldr	w2, [x22, 232]
	strb	w3, [x29, 137]
	str	x6, [x29, 128]
	stp	w8, w4, [x29, 140]
	bl	InsertStreamSeg
	b	.L595
	.p2align 3
.L605:
	ldr	x1, .LC147
	mov	w2, 2641
	mov	w0, 0
	bl	dprint_vfmw
	b	.L595
	.p2align 3
.L603:
	ldr	x1, .LC147
	mov	w2, 2610
	mov	w0, 0
	bl	dprint_vfmw
	b	.L595
	.p2align 3
.L599:
	cmp	w27, wzr
	ble	.L589
	mul	w1, w23, w27
	ldr	x0, [x29, 112]
	add	w1, w1, 1
	ldr	w1, [x28, w1, uxtw 2]
	and	w1, w1, 2147483647
	bl	DeleteRawLen
.L589:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	3
.LC147:
	.xword	.LC146
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
	add	x27, x0, 262144
	mov	w19, w1
	mov	x0, x30
	mov	w25, 0
	mov	w26, 0
	bl	_mcount
	ldr	w20, [x27, 308]
	ldr	x28, [x27, 200]
	cbz	w19, .L606
	ldr	x24, .LC151
	mov	w21, 288
	mov	w23, 2
	mov	w22, 1
	b	.L621
	.p2align 3
.L627:
	cmp	w1, 32768
	stp	w22, wzr, [x27, 252]
	beq	.L625
.L613:
	add	w26, w26, 1
	add	w25, w25, w20
	cmp	w26, w19
	beq	.L606
.L621:
	ldr	w1, [x28, w25, uxtw 2]
	ldr	w2, [x27, 128]
	and	w1, w1, 2147483647
	orr	w0, w1, -2147483648
	cmp	w2, w1
	csel	w0, w0, w1, hi
	bl	MEM_Phy2Vir
	cbz	x0, .L626
	ldr	w1, [x0]
	rev	w1, w1
	cmp	w1, 438
	ccmp	w1, w21, 4, ne
	and	w1, w1, -1024
	beq	.L627
	cmp	w1, 32768
	bne	.L613
	ldr	w0, [x27, 252]
	cmp	w0, 1
	beq	.L628
.L615:
	str	w23, [x27, 252]
.L629:
	add	w26, w26, 1
	add	w25, w25, w20
	cmp	w26, w19
	bne	.L621
.L606:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L625:
	str	w22, [x27, 256]
	b	.L613
	.p2align 3
.L626:
	ldr	x2, .LC148
	mov	w3, 2696
	ldr	x1, .LC150
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
.L628:
	ldr	w0, [x27, 256]
	add	w0, w0, 1
	str	w0, [x27, 256]
	cmp	w0, 30
	bls	.L613
	ldr	x4, [x24]
	cbz	x4, .L615
	ldr	w0, [x27, 232]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	str	w23, [x27, 252]
	b	.L629
	.size	GetMeg4ModeFlag, .-GetMeg4ModeFlag
	.align	3
.LC148:
	.xword	.LANCHOR3
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC151:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessMpeg4ScdUpMsg
	.type	ProcessMpeg4ScdUpMsg, %function
ProcessMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 262144
	mov	w25, w2
	stp	w1, w2, [x29, 108]
	mov	w23, w1
	bl	_mcount
	ldr	w1, [x19, 308]
	add	x22, x20, 98304
	ldr	w0, [x19, 128]
	add	x22, x22, 104
	mov	w24, w1
	add	x1, x29, 256
	ldr	x28, [x19, 200]
	mov	w27, 0
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x1]
	add	x1, x29, 272
	str	w24, [x29, 132]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x1]
	add	x1, x29, 288
	mov	x26, x22
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x1]
	stp	xzr, xzr, [x29, 224]
	stp	xzr, xzr, [x29, 240]
	bl	MEM_Phy2Vir
	mov	x21, x0
	add	x1, x20, 80
	mov	w0, w25
	str	x1, [x29, 120]
	mov	w25, 1
	bl	MEM_Phy2Vir
	ldr	x3, .LC152
	mov	x2, 4
	mov	x1, x21
	ldr	x3, [x3, 104]
	blr	x3
	mov	x0, x20
	mov	w1, w23
	bl	GetMeg4ModeFlag
	mov	x0, x20
	mov	w2, w23
	mov	x1, x28
	add	x20, x22, 163840
	bl	GetNextVop
	str	w0, [x29, 140]
	sub	w0, w24, #1
	str	w0, [x29, 136]
	b	.L631
	.p2align 3
.L665:
	ldr	w0, [x29, 236]
	cbz	w0, .L635
	ldr	w2, [x29, 240]
	mov	x1, x22
	add	x0, x29, 224
	add	w3, w2, w3
	str	w3, [x29, 240]
	bl	CheckSegValid
	cbnz	w0, .L639
	ldr	w2, [x19, 232]
	add	x1, x29, 224
	mov	x0, x22
	bl	InsertStreamSeg
	mov	w23, w0
	ldr	x0, .LC152
	mov	x2, 80
	mov	w1, 0
	ldr	x4, [x0, 96]
	add	x0, x29, 224
	blr	x4
	cbnz	w23, .L639
.L640:
	ldr	w0, [x29, 132]
	mov	w27, w21
	add	w25, w25, w0
.L631:
	ldr	w0, [x29, 140]
	cmp	w27, w0
	beq	.L639
	ldr	w0, [x29, 136]
	sub	w23, w25, #1
	ldr	w4, [x20, 24]
	add	w21, w27, 1
	add	w0, w0, w25
	add	x24, x28, x23, uxtw 2
	ldr	w2, [x28, w23, uxtw 2]
	ldr	w0, [x28, w0, uxtw 2]
	and	w2, w2, 2147483647
	orr	w1, w2, -2147483648
	cmp	w4, w2
	and	w0, w0, 2147483647
	csel	w2, w1, w2, hi
	cmp	w4, w0
	orr	w1, w0, -2147483648
	csel	w0, w1, w0, hi
	sub	w3, w0, w2
	cmp	w3, 3
	bgt	.L665
	sub	w1, w3, #1
	cmp	w1, 2
	bls	.L666
	ldr	w1, [x29, 112]
	sub	w10, w0, w4
	ldr	x0, [x26]
	sub	w4, w2, w4
	sub	w11, w1, w2
	ldr	w1, [x20, 8]
	add	w3, w11, w10
	add	x4, x0, x4
	cmp	w3, 3
	str	x4, [x29, 144]
	stp	w2, w3, [x29, 156]
	ldr	w0, [x20, 12]
	ble	.L667
	sub	w0, w0, w1
	mov	w1, 2048
	and	w0, w0, 2047
	str	w10, [x29, 116]
	sub	w0, w1, w0
	str	w11, [x29, 128]
	cmp	w0, 2
	bls	.L639
	mov	x1, x22
	add	x0, x29, 144
	bl	CheckSegValid
	cbnz	w0, .L639
	ldr	w10, [x29, 116]
	ldr	w0, [x19, 252]
	ldr	w11, [x29, 128]
	cmp	w0, 1
	ldrb	w0, [x29, 216]
	cbnz	w10, .L650
	beq	.L668
	orr	w0, w0, 1
	strb	w0, [x29, 216]
.L652:
	ldr	w1, [x28, w23, uxtw 2]
	mov	w7, 1
	ldrb	w0, [x29, 216]
	add	x2, x19, 272
	lsr	w1, w1, 31
	add	x3, x29, 144
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 216]
	ldrh	w1, [x24, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 216]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 216]
	ldr	x0, [x29, 120]
	ldr	w1, [x24, 8]
	ldrh	w4, [x29, 216]
	and	w1, w1, 7
	strb	w7, [x29, 153]
	bfi	w4, w1, 7, 4
	str	w11, [x29, 160]
	strh	w4, [x29, 216]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x22
	bl	InsertStreamSeg
	b	.L640
	.p2align 3
.L635:
	ldr	x10, [x26]
	sub	w4, w2, w4
	mov	x1, x22
	add	x0, x29, 144
	add	x4, x10, x4
	mov	w10, 1
	str	x4, [x29, 144]
	strb	w10, [x29, 153]
	stp	w2, w3, [x29, 156]
	bl	CheckSegValid
	cbnz	w0, .L639
	ldr	w0, [x19, 252]
	cmp	w0, 1
	ldrb	w0, [x29, 216]
	beq	.L669
	orr	w0, w0, 1
	strb	w0, [x29, 216]
.L642:
	ldr	w4, [x28, w23, uxtw 2]
	add	x2, x19, 272
	ldrb	w1, [x29, 216]
	add	x3, x29, 144
	lsr	w4, w4, 31
	ldr	x0, [x29, 120]
	bfi	w1, w4, 1, 1
	strb	w1, [x29, 216]
	ldrh	w4, [x24, 10]
	bfi	w1, w4, 2, 1
	strb	w1, [x29, 216]
	ldr	w4, [x24, 8]
	ubfx	x4, x4, 4, 3
	bfi	w1, w4, 3, 4
	strb	w1, [x29, 216]
	ldr	w1, [x24, 8]
	ldrh	w4, [x29, 216]
	and	w1, w1, 7
	bfi	w4, w1, 7, 4
	strh	w4, [x29, 216]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x22
	bl	InsertStreamSeg
	cbz	w0, .L640
	.p2align 2
.L639:
	cmp	w27, wzr
	ble	.L670
	ldr	w0, [x29, 132]
	mul	w1, w0, w27
	ldr	x0, [x29, 120]
	add	w1, w1, 1
	ldr	w1, [x28, w1, uxtw 2]
	and	w1, w1, 2147483647
	bl	DeleteRawLen
.L630:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L666:
	str	w3, [x29, 116]
	str	w2, [x29, 128]
	bl	MEM_Phy2Vir
	ldr	w3, [x29, 116]
	ldr	w2, [x29, 128]
	cbz	x0, .L671
	ldr	w0, [x0]
	and	w0, w0, 16777215
	cmp	w0, 65536
	beq	.L640
	ldr	w0, [x19, 252]
	cmp	w0, 1
	ldrb	w0, [x29, 296]
	beq	.L672
	orr	w0, w0, 1
	strb	w0, [x29, 296]
.L648:
	ldr	w1, [x28, w23, uxtw 2]
	ldrb	w0, [x29, 296]
	lsr	w1, w1, 31
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 296]
	ldr	w1, [x20, 24]
	ldrh	w4, [x24, 10]
	sub	w1, w2, w1
	bfi	w0, w4, 2, 1
	ldr	x4, [x26]
	strb	w0, [x29, 296]
	add	x1, x4, x1
	str	x1, [x29, 224]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 296]
	ldr	w0, [x24, 8]
	ldrh	w1, [x29, 296]
	and	w0, w0, 7
	stp	w2, w3, [x29, 236]
	bfi	w1, w0, 7, 4
	mov	w2, 1
	strh	w1, [x29, 296]
	add	x3, x29, 224
	strb	w2, [x29, 233]
	add	x2, x19, 272
	ldr	x0, [x29, 120]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	b	.L640
	.p2align 3
.L650:
	beq	.L673
	orr	w0, w0, 1
	strb	w0, [x29, 216]
.L654:
	ldr	w1, [x28, w23, uxtw 2]
	add	x3, x29, 144
	ldrb	w0, [x29, 216]
	add	x2, x19, 272
	lsr	w1, w1, 31
	str	w10, [x29, 128]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 216]
	ldrh	w1, [x24, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 216]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 216]
	ldr	w0, [x24, 8]
	ldrh	w1, [x29, 216]
	and	w0, w0, 7
	str	w11, [x29, 160]
	strb	wzr, [x29, 153]
	bfi	w1, w0, 7, 4
	strh	w1, [x29, 216]
	ldr	x0, [x29, 120]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 232]
	add	x1, x29, 144
	mov	x0, x22
	bl	InsertStreamSeg
	ldr	w3, [x20, 24]
	add	x1, x29, 144
	ldr	w10, [x29, 128]
	mov	x0, x22
	ldr	x4, [x26]
	ldr	w2, [x19, 232]
	stp	w3, w10, [x29, 156]
	mov	w3, 1
	str	x4, [x29, 144]
	strb	w3, [x29, 153]
	bl	InsertStreamSeg
	b	.L640
	.p2align 3
.L667:
	ldr	x1, .LC156
	mov	w2, 2832
	mov	w0, 0
	bl	dprint_vfmw
	b	.L640
	.p2align 3
.L669:
	and	w0, w0, -2
	strb	w0, [x29, 216]
	b	.L642
	.p2align 3
.L673:
	and	w0, w0, -2
	strb	w0, [x29, 216]
	b	.L654
	.p2align 3
.L668:
	and	w0, w0, -2
	strb	w0, [x29, 216]
	b	.L652
	.p2align 3
.L672:
	and	w0, w0, -2
	strb	w0, [x29, 296]
	b	.L648
	.p2align 3
.L670:
	ldr	w0, [x29, 108]
	cmp	w0, 2048
	ldr	w0, [x29, 140]
	ccmp	w0, wzr, 0, hi
	bne	.L630
	ldr	w2, [x29, 108]
	mov	w0, 0
	ldr	x1, .LC158
	bl	dprint_vfmw
	ldr	x0, [x29, 120]
	mov	w1, 1
	bl	DeleteRawPacket
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
.L671:
	ldr	x2, .LC153
	mov	w3, 2804
	ldr	x1, .LC155
	mov	w0, 1
	add	x2, x2, 112
	bl	dprint_vfmw
	b	.L630
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	3
.LC152:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC153:
	.xword	.LANCHOR3
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC156:
	.xword	.LC146
	.align	3
.LC158:
	.xword	.LC157
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
	ldr	x21, .LC159
	ldr	x0, [x21, w22, sxtw 3]
	cbz	x0, .L674
	ldr	x19, .LC160
	mov	w0, 0
	ldr	w24, [x23, 20]
	ldr	x1, [x19, 32]
	blr	x1
	ldrb	w0, [x20, 2]
	cbnz	w0, .L676
	add	x1, x23, 36
	mov	w0, w24
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L684
.L677:
	ldr	x2, [x21, w22, sxtw 3]
	ldr	w1, [x20, 8]
	ldr	x3, [x19, 88]
	ldr	x0, [x20, 40]
	blr	x3
.L676:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L674:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L684:
	ldr	x2, [x21, w22, sxtw 3]
	mov	w1, 4
	ldr	x3, [x19, 88]
	add	x0, x20, 8
	blr	x3
	b	.L677
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	3
.LC159:
	.xword	vfmw_save_str_file
	.align	3
.LC160:
	.xword	vfmw_Osal_Func_Ptr_S
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
	ldr	x21, .LC162
	ldr	x0, .LC161
	mov	x2, 100
	add	x1, x21, 136
	add	x20, x0, x20, sxtw 4
	add	x0, x29, 56
	ldr	x20, [x20, 16]
	bl	memcpy
	cbz	x19, .L699
	ldr	w3, [x20, 20]
	cmp	w3, 16
	bls	.L700
.L688:
	ldr	x1, .LC167
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
.L696:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L700:
	ldr	x0, .LC165
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx690
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx690:
	.section	.rodata
	.align	0
	.align	2
.L690:
	.byte	(.L689 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L688 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.byte	(.L691 - .Lrtx690) / 4
	.text
	.p2align 3
.L691:
	ldr	w3, [x19, 8]
	mov	w0, 0
	ldr	w5, [x19, 80]
	mov	w4, 0
	cmp	w3, w5
	bhi	.L692
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L689:
	ldr	w3, [x19, 8]
	ldr	w5, [x19, 80]
	add	w0, w3, 15
	cmp	w0, w5
	bhi	.L701
	ldr	x4, .LC170
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
.L701:
	mov	w4, 15
.L692:
	ldr	x1, .LC169
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L696
.L699:
	ldr	x1, .LC164
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L696
	.size	FillEopRawStream, .-FillEopRawStream
	.align	3
.LC161:
	.xword	.LANCHOR0
	.align	3
.LC162:
	.xword	.LANCHOR3
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	.L690
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC170:
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
	ldr	x0, .LC171
	mov	x2, 100
	ldr	x1, .LC172
	add	x19, x0, x19, sxtw 4
	add	x0, x29, 40
	add	x1, x1, 264
	ldr	x19, [x19, 16]
	bl	memcpy
	cbz	x20, .L722
	ldr	w3, [x19, 20]
	cmp	w3, 17
	bls	.L723
.L705:
	ldr	x2, .LC173
	mov	w0, 0
	ldr	x1, .LC176
	bl	dprint_vfmw
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L723:
	ldr	x0, .LC175
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx707
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx707:
	.section	.rodata
	.align	0
	.align	2
.L707:
	.byte	(.L706 - .Lrtx707) / 4
	.byte	(.L708 - .Lrtx707) / 4
	.byte	(.L709 - .Lrtx707) / 4
	.byte	(.L710 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L717 - .Lrtx707) / 4
	.byte	(.L705 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.byte	(.L706 - .Lrtx707) / 4
	.byte	(.L712 - .Lrtx707) / 4
	.byte	(.L720 - .Lrtx707) / 4
	.text
	.p2align 3
.L706:
	mov	w19, 15
	add	x1, x29, 40
.L711:
	ldr	w4, [x20, 8]
	cmp	w19, w4
	bls	.L724
	ldr	x2, .LC173
	mov	w3, w19
	ldr	x1, .LC178
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L718
	.p2align 3
.L724:
	ldr	x3, .LC179
	and	x2, x19, 31
	ldr	x0, [x20, 40]
	ldr	x3, [x3, 104]
	blr	x3
	str	w19, [x20, 8]
.L720:
	mov	w0, 0
.L718:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L708:
	ldr	w0, [x19, 36]
	cmp	w0, 1
	bne	.L720
.L717:
	mov	w19, 15
	add	x1, x29, 60
	b	.L711
	.p2align 3
.L712:
	mov	w19, 16
	add	x1, x29, 120
	b	.L711
	.p2align 3
.L710:
	mov	w19, 16
	add	x1, x29, 100
	b	.L711
	.p2align 3
.L709:
	mov	w19, 19
	add	x1, x29, 80
	b	.L711
.L722:
	ldr	x2, .LC173
	mov	w0, 0
	ldr	x1, .LC174
	bl	dprint_vfmw
	mov	w0, -7
	b	.L718
	.size	FillEosRawStream, .-FillEosRawStream
	.align	3
.LC171:
	.xword	.LANCHOR0
	.align	3
.LC172:
	.xword	.LANCHOR3
	.align	3
.LC173:
	.xword	.LANCHOR4
	.align	3
.LC174:
	.xword	.LC163
	.align	3
.LC175:
	.xword	.L707
	.align	3
.LC176:
	.xword	.LC166
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC179:
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
	beq	.L737
	ldr	w0, [x19, 76]
	tbnz	x0, 7, .L738
	add	x20, x20, 262144
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 324]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L739
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC183
	mov	w21, 0
	add	x0, x1, x0, uxtw
.L736:
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
.L729:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L738:
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	add	w3, w2, 12
	cmp	w3, 128
	ccmp	w3, w4, 2, le
	bhi	.L740
	ldr	x22, .LC183
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	add	x20, x20, 262144
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
.L737:
	ldr	w1, [x19, 76]
	tbnz	x1, 7, .L741
	ldrb	w1, [x19, 72]
	mov	w21, 0
	cbz	w1, .L729
	add	x20, x20, 262144
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w5, [x20, 324]
	add	w3, w2, w5
	cmp	w3, w4
	bhi	.L742
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC183
	add	x0, x1, x5, uxtw
	b	.L736
	.p2align 3
.L741:
	ldr	w3, [x19, 8]
	cmp	w3, 128
	bgt	.L743
	add	x20, x20, 262144
	ldr	x1, .LC183
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
.L740:
	ldr	x2, .LC180
	mov	w5, 128
	ldr	x1, .LC187
	mov	w0, 1
	add	x2, x2, 24
	mov	w21, -2
	bl	dprint_vfmw
	b	.L729
	.p2align 3
.L739:
	ldr	x2, .LC180
	mov	w0, 1
	ldr	x1, .LC185
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L729
.L743:
	ldr	x2, .LC180
	mov	w4, 128
	ldr	x1, .LC182
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L729
.L742:
	ldr	x2, .LC180
	mov	w21, -2
	ldr	x1, .LC185
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L729
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	3
.LC180:
	.xword	.LANCHOR4
	.align	3
.LC182:
	.xword	.LC181
	.align	3
.LC183:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC187:
	.xword	.LC186
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
	bhi	.L747
	ldr	x20, .LC191
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
.L746:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L747:
	ldr	x2, .LC188
	mov	w0, 1
	ldr	x1, .LC190
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L746
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	3
.LC188:
	.xword	.LANCHOR4
	.align	3
.LC190:
	.xword	.LC189
	.align	3
.LC191:
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
	tbz	x0, 7, .L749
	ldr	w3, [x19, 8]
	cmp	w3, 128
	bgt	.L753
	add	x20, x20, 262144
	ldr	x1, .LC194
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
.L749:
	add	x20, x20, 262144
	ldr	w2, [x19, 8]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 324]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L754
	ldr	x21, .LC194
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
.L751:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L754:
	ldr	x2, .LC192
	mov	w0, 1
	ldr	x1, .LC196
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L751
	.p2align 3
.L753:
	ldr	x2, .LC192
	mov	w4, 128
	ldr	x1, .LC193
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L751
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	3
.LC192:
	.xword	.LANCHOR4
	.align	3
.LC193:
	.xword	.LC181
	.align	3
.LC194:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC196:
	.xword	.LC195
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
	bhi	.L761
	ldr	w3, [x20, 8]
	cmp	w3, wzr
	ble	.L764
	ldr	x0, .LC200
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 16]
	ldr	w1, [x0, 20]
	cmp	w1, 5
	beq	.L758
	cmp	w1, 8
	beq	.L759
	cmp	w1, 1
	beq	.L765
	mov	w0, 0
.L756:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L759:
	mov	x1, x20
	bl	FillREAL8ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L758:
	mov	x1, x20
	bl	FillDIVX3ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L765:
	mov	x1, x20
	bl	FillVC1ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L761:
	mov	w0, -1
	b	.L756
.L764:
	ldr	x2, .LC197
	mov	w0, 1
	ldr	x1, .LC199
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L756
	.size	FillExtraData, .-FillExtraData
	.align	3
.LC197:
	.xword	.LANCHOR4
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC200:
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
	ldr	x19, .LC201
	mov	x20, x0
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x19, 96]
	blr	x3
	cbz	x20, .L782
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
	ldr	x23, .LC204
	ldr	x0, [x20, 16]
	cbz	x0, .L769
	lsl	x20, x21, 4
	add	x24, x23, 16
	ldr	x0, [x24, x20]
	ldr	w0, [x0, 60]
	cmp	w0, 1
	beq	.L783
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x19, 48]
	mov	w1, w22
	mov	w0, 1
	blr	x2
	ldr	x0, [x24, x20]
	cbz	x0, .L774
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
.L772:
	ldr	x2, [x19, 56]
	mov	w0, 1
	mov	w1, w22
	blr	x2
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	cbz	w20, .L773
.L769:
	mov	w20, -7
.L773:
	add	x21, x23, x21, lsl 4
	mov	w0, w20
	ldr	x1, [x21, 16]
	cbz	x1, .L784
.L768:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L783:
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
	cbz	w20, .L773
	b	.L769
	.p2align 3
.L774:
	mov	w20, -7
	b	.L772
.L782:
	ldr	x1, .LC203
	mov	w2, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L768
.L784:
	ldr	x1, .LC206
	mov	w3, w22
	mov	w2, 3771
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L768
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	3
.LC201:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC203:
	.xword	.LC202
	.align	3
.LC204:
	.xword	.LANCHOR0
	.align	3
.LC206:
	.xword	.LC205
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
	bhi	.L801
	ldr	x28, .LC210
	sxtw	x0, w24
	add	x1, x28, x0, lsl 4
	ldr	x22, [x1, 16]
	cbz	x22, .L797
	cbz	w19, .L802
.L788:
	adds	x23, x22, 80
	beq	.L797
	add	x1, x23, 98304
	ldr	w21, [x1]
	ldr	w20, [x1, 8]
	cmp	w21, w20
	blt	.L803
.L800:
	sub	w21, w21, w20
	cbz	w21, .L797
	ldr	x25, .LC211
	add	x28, x28, 16
	ldr	x26, .LC213
	mov	w27, 0
	add	x25, x25, 112
	add	x28, x28, x0, lsl 4
	b	.L792
	.p2align 3
.L805:
	beq	.L804
.L792:
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
	cbnz	x0, .L805
	mov	w0, -7
.L787:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L802:
	add	x1, x22, 262144
	ldr	w1, [x1, 248]
	cbnz	w1, .L788
.L797:
	mov	w0, -1
	b	.L787
	.p2align 3
.L803:
	add	w21, w21, 1024
	b	.L800
	.p2align 3
.L804:
	add	x23, x23, 98304
	ldr	w20, [x23, 8]
	add	w20, w20, w27
	cmp	w20, 1023
	ble	.L806
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
.L806:
	str	w20, [x23, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L801:
	ldr	x1, .LC209
	mov	w2, w24
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L787
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC210:
	.xword	.LANCHOR0
	.align	3
.LC211:
	.xword	.LANCHOR4
	.align	3
.LC213:
	.xword	.LC212
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
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 31
	bhi	.L818
	ldr	x27, .LC216
	sxtw	x26, w21
	add	x0, x27, x26, lsl 4
	ldr	x20, [x0, 16]
	cbz	x20, .L809
	add	x4, x27, 528
	ldr	w0, [x4, 52]
	cmp	w21, w0
	bne	.L811
	ldr	x2, .LC219
	mov	w3, 1211
	ldr	x1, .LC221
	mov	w0, 22
	add	x2, x2, 136
	str	wzr, [x4, 56]
	bl	dprint_vfmw
.L811:
	ldr	x22, .LC222
	mov	x2, 72
	add	x1, x20, 8
	add	x0, x29, 104
	add	x19, x20, 262144
	add	x26, x27, x26, lsl 4
	ldr	x3, [x22, 104]
	add	x24, x19, 328
	blr	x3
	ldr	w23, [x19, 248]
	ldr	x3, [x22, 104]
	mov	x2, 128
	mov	x1, x24
	add	x0, x29, 176
	ldr	w25, [x19, 324]
	blr	x3
	ldr	x0, [x26, 16]
	cbz	x0, .L812
	add	x0, x0, 262144
	ldr	w1, [x0, 248]
	cbnz	w1, .L827
.L812:
	adds	x26, x20, 80
	beq	.L813
.L829:
	add	x1, x26, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	cmp	w0, wzr
	add	w1, w0, 1024
	csel	w1, w1, w0, lt
.L817:
	mov	x0, x26
	sub	w23, w23, #1
	bl	DeleteRawPacket
	mov	w1, 1
	mov	w0, w21
	bl	DeleteRawPacketInBuffer
	ldr	x3, [x22, 96]
	mov	x2, 464
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	mov	x0, x20
	blr	x3
	mov	x1, -1
	mov	w0, 2
	str	x1, [x19, 272]
	add	x1, x29, 104
	str	w0, [x19, 308]
	mov	w0, w21
	bl	SM_Config
	cmp	w23, 1
	bls	.L828
	str	wzr, [x19, 248]
.L816:
	ldr	x3, [x22, 104]
	mov	x2, 128
	add	x1, x29, 176
	mov	x0, x24
	str	w25, [x19, 324]
	blr	x3
	mov	w0, 0
.L825:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L827:
	ldr	w1, [x0, 236]
	cmp	w1, wzr
	bgt	.L812
	str	wzr, [x0, 248]
	adds	x26, x20, 80
	bne	.L829
	.p2align 2
.L813:
	ldr	x2, .LC219
	mov	w3, 1229
	ldr	x1, .LC224
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w1, 0
	b	.L817
	.p2align 3
.L828:
	mov	w0, 1
	str	w0, [x19, 248]
	b	.L816
	.p2align 3
.L818:
	mov	w0, -1
	b	.L825
.L809:
	ldr	x1, .LC218
	mov	w2, 1201
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L825
	.size	SM_Reset, .-SM_Reset
	.align	3
.LC216:
	.xword	.LANCHOR0
	.align	3
.LC218:
	.xword	.LC217
	.align	3
.LC219:
	.xword	.LANCHOR4
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC222:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC224:
	.xword	.LC223
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
	ldr	x25, .LC226
	ldr	x21, .LC227
	mov	x2, 24
	add	x0, x25, x23, lsl 4
	mov	w1, 0
	ldr	x3, [x21, 96]
	ldr	x19, [x0, 16]
	add	x0, x29, 88
	blr	x3
	cbz	x19, .L831
	mov	w0, w23
	bl	VCTRL_GetStreamInterface
	mov	x22, x0
	cbz	x0, .L866
	ldr	x3, [x21, 104]
	mov	x2, 24
	add	x0, x29, 88
	mov	x1, x22
	blr	x3
	ldr	x0, [x22, 8]
	cbz	x0, .L831
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L867
	ldr	x22, .LC230
	ldr	x0, [x22, w23, sxtw 3]
	cbz	x0, .L847
	add	x0, x0, 294912
	ldr	w26, [x0, 1188]
.L837:
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L838
	add	x0, x0, 294912
	ldr	w0, [x0, 1188]
	cmp	w26, w0
	bne	.L868
.L838:
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
	cbz	x0, .L869
	cbz	w22, .L839
.L831:
	mov	w0, -7
.L863:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L839:
	ldrb	w21, [x24, 1]
	cmp	w21, 1
	beq	.L870
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L871
.L841:
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
.L870:
	mov	x1, x24
	mov	w0, w20
	bl	FillEosRawStream
	cbnz	w0, .L872
	mov	w1, w21
	mov	w0, w20
	bl	VCTRL_SetLastFrameState
	b	.L841
	.p2align 3
.L867:
	ldr	w0, [x29, 88]
	mov	x1, x24
	ldr	x2, [x29, 96]
	blr	x2
	mov	w22, w0
	cbz	w22, .L839
	b	.L831
	.p2align 3
.L847:
	mov	w26, 0
	b	.L837
	.p2align 3
.L871:
	mov	x1, x24
	mov	w0, w20
	bl	FillExtraData
	cbnz	w0, .L873
	add	x0, x19, 262144
	ldr	w0, [x0, 320]
	cbz	w0, .L841
	ldrb	w0, [x24]
	cbnz	w0, .L841
	mov	x1, x24
	mov	w0, w20
	bl	FillEopRawStream
	b	.L841
	.p2align 3
.L873:
	ldr	x1, .LC236
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x29, 88]
	mov	x1, x24
	bl	ReleaseRawStreamData
	cbz	w0, .L831
	ldr	x1, .LC238
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L863
.L869:
	ldr	x1, .LC232
	mov	w3, w20
	mov	w2, 3675
	bl	dprint_vfmw
	mov	w0, -7
	b	.L863
	.p2align 3
.L868:
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	mov	w0, -7
	b	.L863
.L866:
	ldr	x1, .LC229
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L863
.L872:
	ldr	x1, .LC234
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L863
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	3
.LC226:
	.xword	.LANCHOR0
	.align	3
.LC227:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC230:
	.xword	s_pstVfmwChan
	.align	3
.LC232:
	.xword	.LC231
	.align	3
.LC234:
	.xword	.LC233
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
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
	cmp	w19, 2048
	beq	.L874
	cmp	w19, w21
	beq	.L874
	add	x23, x20, 163840
	mov	w22, 2
	.p2align 2
.L877:
	sxtw	x2, w19
	mov	w1, w19
	lsl	x3, x2, 6
	mov	x0, x20
	add	x2, x3, x2, lsl 4
	add	x2, x20, x2
	strb	w22, [x2, 16]
	ldr	w4, [x2, 24]
	ldp	w3, w2, [x23, 44]
	subs	w3, w3, w4
	csel	w3, w3, wzr, pl
	subs	w2, w2, #1
	csel	w2, w2, wzr, pl
	stp	w3, w2, [x23, 44]
	bl	ReleaseStreamSeg
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 21
	add	w0, w0, w19
	and	w0, w0, 2047
	sub	w19, w0, w19
	cmp	w21, w19
	bne	.L877
.L874:
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
	add	x20, x0, 163840
	mov	x24, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldp	w19, w4, [x20, 8]
	ldp	x21, x23, [x22]
	str	w19, [x20, 16]
	.p2align 2
.L880:
	sxtw	x3, w19
	cmp	w19, w4
	lsl	x2, x3, 6
	mov	w1, w19
	add	x3, x2, x3, lsl 4
	mov	x0, x24
	add	x3, x24, x3
	beq	.L891
.L881:
	ldrsb	w2, [x3, 16]
	add	x25, x3, 40
	cmp	w2, 1
	bne	.L883
	ldr	x1, [x3, 40]
	add	w0, w19, 1
	cmn	x1, #1
	beq	.L892
	cmp	x21, x1
	asr	w1, w0, 31
	lsr	w1, w1, 21
	bls	.L886
	add	w0, w0, w1
	str	w19, [x20, 16]
	and	w19, w0, 2047
	mov	x0, x24
	sub	w19, w19, w1
	cmp	w19, w4
	mov	w1, w19
	sxtw	x3, w19
	lsl	x2, x3, 6
	add	x3, x2, x3, lsl 4
	add	x3, x24, x3
	bne	.L881
.L891:
	ldr	w1, [x20, 8]
	mov	w2, w19
	bl	ReleaseSegArrayPackets
	ldr	x25, [sp, 64]
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L883:
	bl	ReleaseStreamSeg
	add	w0, w19, 1
	ldr	w4, [x20, 12]
	asr	w19, w0, 31
	lsr	w19, w19, 21
	add	w0, w0, w19
	and	w0, w0, 2047
	sub	w19, w0, w19
	b	.L880
	.p2align 3
.L886:
	beq	.L893
	bcs	.L880
	ldr	w2, [x20, 16]
	sxtw	x0, w2
	lsl	x1, x0, 6
	add	x0, x1, x0, lsl 4
	add	x0, x24, x0
	ldr	x0, [x0, 40]
	cmn	x0, #1
	beq	.L890
	cmp	x21, x0
	bls	.L889
	sub	x21, x21, x0
	cmp	x23, x21
	bcs	.L889
.L890:
	mov	w2, w19
	str	w19, [x20, 16]
.L889:
	ldr	w1, [x20, 8]
	mov	x0, x24
	bl	ReleaseSegArrayPackets
	ldrsw	x1, [x20, 16]
	mov	w0, 0
	lsl	x2, x1, 6
	add	x1, x2, x1, lsl 4
	add	x24, x24, x1
	ldr	x1, [x24, 40]
	str	x1, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L892:
	asr	w19, w0, 31
	lsr	w19, w19, 21
	add	w0, w0, w19
	and	w0, w0, 2047
	sub	w19, w0, w19
	b	.L880
.L893:
	ldr	w1, [x20, 8]
	mov	w2, w19
	mov	x0, x24
	bl	ReleaseSegArrayPackets
	ldr	x0, [x25]
	str	x0, [x22]
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
	ldr	x0, .LC239
	add	x0, x0, x19, sxtw 4
	ldr	x9, [x0, 16]
	cbz	x9, .L913
	cmp	w22, 1
	mov	w10, 0
	ldp	x8, x11, [x21]
	beq	.L925
.L896:
	add	x6, x20, 98304
	ldp	w3, w7, [x6]
	str	w3, [x6, 8]
	mov	w1, w3
	.p2align 2
.L897:
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
	beq	.L926
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L927
	cmp	x8, x2
	bls	.L903
	str	w1, [x6, 8]
	sub	w1, w0, w4
	b	.L897
	.p2align 3
.L927:
	add	w0, w1, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w1, w0, w1
	b	.L897
	.p2align 3
.L926:
	cmp	w3, w1
	bgt	.L928
.L921:
	sub	w1, w1, w3
	str	w3, [x6, 8]
	mov	x0, x20
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, -2
.L895:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L928:
	add	w1, w1, 1024
	b	.L921
	.p2align 3
.L903:
	beq	.L929
	ldr	w0, [x6, 8]
	sxtw	x4, w0
	lsl	x2, x4, 2
	sub	x2, x2, x4
	add	x2, x20, x2, lsl 5
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L923
	cmp	x8, x2
	bls	.L909
	sub	x8, x8, x2
	cmp	x11, x8
	bcs	.L909
.L923:
	mov	w0, w1
	str	w1, [x6, 8]
.L909:
	cmp	w3, w0
	sub	w1, w0, w3
	bgt	.L930
.L911:
	cmp	w22, 1
	beq	.L931
.L912:
	sxtw	x2, w0
	mov	x0, x20
	lsl	x3, x2, 2
	sub	x2, x3, x2
	add	x20, x20, x2, lsl 5
.L924:
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
.L925:
	add	x0, x9, 262144
	ldr	w10, [x0, 168]
	cmp	w10, 1
	bne	.L896
	mov	w1, 3
	str	w1, [x0, 168]
	b	.L896
	.p2align 3
.L930:
	add	w1, w0, 1024
	sub	w1, w1, w3
	b	.L911
.L929:
	cmp	w1, w3
	bge	.L922
	add	w1, w1, 1024
.L922:
	cmp	w22, 1
	sub	w1, w1, w3
	beq	.L932
.L907:
	lsl	x0, x5, 2
	sub	x5, x0, x5
	mov	x0, x20
	add	x20, x20, x5, lsl 5
	b	.L924
.L931:
	add	x9, x9, 262144
	ldr	w2, [x9, 160]
	cmp	w1, w2
	ccmp	w10, 1, 0, le
	bne	.L912
	str	w10, [x9, 168]
	ldr	w0, [x6, 8]
	b	.L912
.L932:
	add	x9, x9, 262144
	ldr	w0, [x9, 160]
	cmp	w1, w0
	ccmp	w10, 1, 0, le
	bne	.L907
	str	w10, [x9, 168]
	b	.L907
.L913:
	mov	w0, -1
	b	.L895
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	3
.LC239:
	.xword	.LANCHOR0
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
	bgt	.L936
	ldr	x1, .LC240
	sxtw	x2, w2
	ldr	x3, [x21, 120]
	add	x20, x20, 262144
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
.L937:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L936:
	ldr	x1, .LC242
	mov	w3, w2
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -7
	b	.L937
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	3
.LC240:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC242:
	.xword	.LC241
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x20, 98304
	adds	x21, x0, 104
	beq	.L946
	add	x1, x21, 163840
	ldp	w23, w22, [x1, 44]
.L939:
	add	x0, x0, 104
	ldrsb	w1, [x20, 1]
	add	x0, x0, 163840
	ldr	w19, [x0, 28]
	cbnz	w1, .L940
	add	w19, w19, w19, lsr 31
	mov	w0, 127
	asr	w19, w19, 1
	cmp	w19, w23
	ccmp	w22, w0, 0, gt
	ble	.L950
.L938:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L940:
	ldr	x0, .LC243
	ldr	x0, [x0]
	blr	x0
	add	x1, x20, 262144
	ldr	w2, [x1, 264]
	cmp	w0, w2
	bls	.L943
	sub	w2, w0, w2
	str	w2, [x1, 260]
	cmp	w2, 1000
	ble	.L938
	cmp	w19, wzr
	add	w0, w19, 3
	csel	w19, w0, w19, lt
	mov	w0, 63
	asr	w19, w19, 2
	cmp	w19, w23
	ccmp	w22, w0, 0, gt
	bgt	.L938
	ldr	x1, .LC245
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x21
	bl	ReleaseStreamSeg
	strb	wzr, [x20, 1]
	strb	wzr, [x20]
	b	.L938
	.p2align 3
.L943:
	str	wzr, [x1, 260]
	str	w0, [x1, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L946:
	mov	w23, 0
	mov	w22, 0
	b	.L939
	.p2align 3
.L950:
	ldr	x0, .LC243
	mov	w1, 1
	strb	w1, [x20, 1]
	add	x20, x20, 262144
	ldr	x0, [x0]
	blr	x0
	str	wzr, [x20, 260]
	str	w0, [x20, 264]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	3
.LC243:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC245:
	.xword	.LC244
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
	ldr	x0, .LC246
	add	x19, x0, x19, sxtw 4
	ldr	x1, [x19, 16]
	cbz	x1, .L954
	add	x0, x1, 262144
	ldr	w2, [x0, 248]
	cbz	w2, .L954
	ldr	w0, [x0, 240]
	cmp	w0, 1
	beq	.L954
	ldr	w0, [x1, 20]
	ldr	x2, [x1, 36]
	ldr	w1, [x1, 44]
	cmp	w0, 19
	str	x2, [x29, 32]
	str	w1, [x29, 40]
	beq	.L954
	add	x1, x29, 32
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cmp	w0, wzr
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L954:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	3
.LC246:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC247
	ldr	x23, .LC248
	ldr	x22, .LC250
	add	x20, x21, 16
	add	x21, x21, 528
	.p2align 2
.L969:
	ldr	x19, [x20]
	cbz	x19, .L965
	ldr	w2, [x19, 48]
	mov	x1, x22
	mov	w0, 0
	cbz	w2, .L965
	ldp	w4, w3, [x23]
	cmp	w4, 1
	mov	w2, w4
	beq	.L978
.L968:
	bl	dprint_vfmw
.L977:
	add	x19, x19, 262144
	str	wzr, [x19, 244]
.L965:
	add	x20, x20, 16
	cmp	x20, x21
	bne	.L969
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L978:
	cmp	w3, 1
	beq	.L977
	cmp	w3, 2
	bne	.L968
	add	x19, x19, 262144
	str	w4, [x19, 244]
	b	.L965
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	3
.LC247:
	.xword	.LANCHOR0
	.align	3
.LC248:
	.xword	g_DspDrvState
	.align	3
.LC250:
	.xword	.LC249
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
	ldr	x0, .LC253
	ldr	x0, [x0]
	blr	x0
	ldr	x4, .LC254
	sxtw	x1, w19
	add	x3, x4, x1, lsl 6
	ldr	w2, [x3, 48]
	cbz	w2, .L979
	ldr	w6, [x3, 44]
	add	w5, w6, 49152
	add	w5, w5, 848
	cmp	w2, w5
	bhi	.L982
	ldr	w3, [x3, 52]
.L983:
	add	x1, x4, x1, lsl 6
	sub	w2, w0, w2
	sub	w0, w0, w6
	add	w2, w2, w3
	cmp	w0, 999
	stp	wzr, w2, [x1, 48]
	bls	.L979
	lsl	w3, w2, 6
	str	wzr, [x1, 44]
	sub	w3, w3, w2
	lsl	w3, w3, 1
	sub	w2, w3, w2
	lsl	w2, w2, 3
	udiv	w0, w2, w0
	str	w0, [x1, 56]
.L979:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L982:
	str	w2, [x3, 44]
	mov	w6, w2
	mov	w3, 0
	b	.L983
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	3
.LC253:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC254:
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
	ldr	x0, .LC255
	add	x19, x0, x19, sxtw 4
	ldr	x19, [x19, 16]
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L995
.L985:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L995:
	adds	x1, x19, 80
	beq	.L988
	add	x1, x1, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	add	w1, w0, 1024
	cmp	w0, wzr
	csel	w0, w1, w0, lt
.L991:
	ldrsb	w20, [x19, 2]
	cmp	w20, 1
	bne	.L985
	ldr	w1, [x19, 64]
	cmp	w1, w0
	bne	.L985
	mov	x0, x19
	bl	SM_MoveRawData
	cbz	w0, .L985
	ldr	x1, .LC257
	mov	w0, w20
	add	x19, x19, 262144
	bl	dprint_vfmw
	ldr	w0, [x19, 232]
	bl	SM_Reset
	b	.L985
	.p2align 3
.L988:
	ldr	x1, .LC259
	bl	dprint_vfmw
	mov	w0, 0
	b	.L991
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	3
.LC255:
	.xword	.LANCHOR0
	.align	3
.LC257:
	.xword	.LC256
	.align	3
.LC259:
	.xword	.LC258
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
	cbnz	w19, .L1004
	ldr	x21, .LC260
	mov	w4, 0
	ldr	x24, .LC261
	mov	w3, 4413
	add	x20, x21, 528
	ldr	x23, .LC263
	add	x22, x24, 152
	ldr	w5, [x20, 56]
	mov	x2, x22
	mov	x1, x23
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w19, [x20, 56]
	cbz	w19, .L1008
	mov	w5, w19
	mov	w4, 0
	mov	w3, 4423
	mov	x2, x22
	mov	x1, x23
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x19, .LC266
	ldr	x0, [x19]
	blr	x0
	ldr	w4, [x20, 60]
	cmp	w0, w4
	bcs	.L999
	str	w0, [x20, 60]
.L1000:
	ldr	x1, .LC271
	mov	w4, 0
	mov	w3, 4460
	add	x2, x24, 152
	mov	w0, 26
	mov	w19, 1
	bl	dprint_vfmw
.L997:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L999:
	sub	w4, w0, w4
	cmp	w4, 2000
	bls	.L1000
	ldr	x1, .LC268
	mov	w3, 0
	ldr	w2, [x20, 52]
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC269
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1001
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L1002:
	ldr	x1, [x19, 256]
	mov	w0, 1
	str	wzr, [x21, 584]
	blr	x1
	ldr	w0, [x21, 580]
	add	x21, x21, x0, sxtw 4
	ldr	x1, [x21, 16]
	cbz	x1, .L1003
	add	x1, x1, 262144
	str	wzr, [x1, 240]
.L1003:
	bl	DeleteLastSendRaw
	mov	w19, 0
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1008:
	ldr	x1, .LC265
	mov	x2, x22
	mov	w4, 0
	mov	w3, 4417
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1001:
	mov	w0, 0
	bl	ResetSCD
	b	.L1002
	.p2align 3
.L1004:
	mov	w19, -1
	b	.L997
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	3
.LC260:
	.xword	.LANCHOR0
	.align	3
.LC261:
	.xword	.LANCHOR4
	.align	3
.LC263:
	.xword	.LC262
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC266:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC268:
	.xword	.LC267
	.align	3
.LC269:
	.xword	g_HalDisable
	.align	3
.LC271:
	.xword	.LC270
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_MarkReloadDsp
	.type	SCDDRV_MarkReloadDsp, %function
SCDDRV_MarkReloadDsp:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbnz	w20, .L1009
	add	w0, w19, 1
	cmp	w0, 32
	bhi	.L1009
	ldr	x1, .LC274
	mov	w0, 1
	cmn	w19, #1
	str	w0, [x1, 592]
	beq	.L1009
	add	x19, x1, x19, sxtw 4
	mov	w1, -1
	ldr	x0, [x19, 16]
	add	x0, x0, 262144
	str	w1, [x0, 244]
.L1009:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_MarkReloadDsp, .-SCDDRV_MarkReloadDsp
	.align	3
.LC274:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_UpdateMatchMode
	.type	SM_UpdateMatchMode, %function
SM_UpdateMatchMode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbnz	w20, .L1016
	cmp	w19, 31
	bhi	.L1016
	ldr	x1, .LC275
	mov	w2, 1
	add	x19, x1, x19, sxtw 4
	ldr	x0, [x19, 16]
	add	x0, x0, 262144
	str	w2, [x0, 244]
.L1016:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_UpdateMatchMode, .-SM_UpdateMatchMode
	.align	3
.LC275:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x22, .LC276
	lsl	x1, x20, 6
	add	x1, x1, x20, lsl 3
	add	x1, x22, x1
	ldr	w0, [x1, 584]
	cmp	w0, 1
	beq	.L1019
.L1021:
	mov	w0, 0
.L1020:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1019:
	ldr	x23, .LC277
	mov	w19, 41248
	movk	w19, 0x7, lsl 16
	lsl	x20, x20, 2
	ldr	x0, [x23]
	blr	x0
	mov	w21, w0
	b	.L1025
	.p2align 3
.L1029:
	ldr	x0, [x23]
	blr	x0
	cmp	w21, w0
	sub	w4, w21, w0
	mvn	w4, w4
	bhi	.L1023
	sub	w4, w0, w21
.L1023:
	cmp	w4, 1000
	bhi	.L1027
	subs	w19, w19, #1
	beq	.L1028
.L1025:
	add	x0, x22, x20
	ldr	w0, [x0, 8]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L1029
	b	.L1021
	.p2align 3
.L1027:
	ldr	x1, .LC279
	mov	w3, w0
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1020
.L1028:
	mov	w0, -7
	b	.L1020
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	3
.LC276:
	.xword	.LANCHOR0
	.align	3
.LC277:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC279:
	.xword	.LC278
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
	ldr	x19, .LC280
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
	ldr	x1, .LC282
	mov	w2, w20
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC284
	mov	w2, w27
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC286
	mov	w2, w26
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC288
	mov	w2, w25
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC290
	mov	w2, w24
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC292
	mov	w2, w23
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC294
	mov	w2, w22
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC296
	mov	w2, w21
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC298
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
.LC280:
	.xword	.LANCHOR0
	.align	3
.LC282:
	.xword	.LC281
	.align	3
.LC284:
	.xword	.LC283
	.align	3
.LC286:
	.xword	.LC285
	.align	3
.LC288:
	.xword	.LC287
	.align	3
.LC290:
	.xword	.LC289
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC294:
	.xword	.LC293
	.align	3
.LC296:
	.xword	.LC295
	.align	3
.LC298:
	.xword	.LC297
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w23, w0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	ldr	x20, .LC299
	ldrb	w0, [x20]
	cmp	w0, 1
	beq	.L1032
	ldr	x3, .LC300
	add	x0, x29, 64
	mov	x2, 188
	mov	w1, 0
	mov	x22, x0
	ldr	x3, [x3, 96]
	blr	x3
.L1033:
	ldrb	w0, [x20]
	ldr	w1, [x19, 4]
	cmp	w0, 1
	bne	.L1060
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2052
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	bne	.L1061
.L1036:
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2056
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	bne	.L1062
.L1038:
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2060
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	bne	.L1063
.L1040:
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2064
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	bne	.L1064
.L1042:
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2068
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	bne	.L1065
.L1044:
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2072
	bl	MEM_WritePhyWord
.L1045:
	ldrb	w0, [x19, 1]
	ldrb	w3, [x20]
	ldr	w2, [x19, 44]
	ubfiz	w0, w0, 4, 1
	ldr	w1, [x19, 52]
	cmp	w3, 1
	ldr	w4, [x19, 60]
	and	w2, w2, 15
	lsl	w1, w1, 8
	orr	w0, w0, w2
	orr	w1, w1, w4, lsl 9
	orr	w1, w0, w1
	bne	.L1066
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2080
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 52]
	cbnz	w0, .L1067
.L1048:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L1068
	ldr	x0, .LC301
	mov	w1, 0
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldrb	w24, [x20]
	cmp	w24, 1
	beq	.L1052
.L1069:
	ldr	w1, [x19, 52]
	add	x0, x29, 64
	strb	w21, [x29, 64]
	strb	w1, [x29, 65]
	stp	wzr, w23, [x29, 68]
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L1060:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2052
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	beq	.L1036
.L1061:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2056
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	beq	.L1038
.L1062:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2060
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	beq	.L1040
.L1063:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2064
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	beq	.L1042
.L1064:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2068
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	beq	.L1044
.L1065:
	mov	w3, w1
	mov	w2, 2072
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	b	.L1045
	.p2align 3
.L1068:
	mov	w3, 0
	mov	w2, 2076
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	ldrb	w24, [x20]
	cmp	w24, 1
	bne	.L1069
.L1052:
	mov	w0, w21
	bl	PrintScdVtrlReg
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L1070
	ldr	x0, .LC301
	mov	w1, 0
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
.L1055:
	ldrb	w0, [x20]
	ldrb	w1, [x19, 2]
	cmp	w0, 1
	and	w1, w1, 1
	bne	.L1071
	ldr	x0, .LC301
	add	x21, x0, x21, sxtw 2
	ldr	w0, [x21, 8]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L1066:
	mov	w3, w1
	mov	x0, x22
	mov	w2, 2080
	mov	w1, 1
	bl	VDH_Record_RegData
	ldr	w0, [x19, 52]
	cbz	w0, .L1048
.L1067:
	ldrb	w0, [x20]
	ldr	w1, [x19, 68]
	cmp	w0, 1
	bne	.L1072
	ldr	x0, .LC301
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 8]
	bl	MEM_WritePhyWord
	b	.L1048
	.p2align 3
.L1032:
	mov	w0, w21
	mov	x22, 0
	bl	ResetSCD
	b	.L1033
	.p2align 3
.L1072:
	mov	w3, w1
	mov	w2, 0
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	b	.L1048
	.p2align 3
.L1071:
	mov	w3, w1
	mov	x0, x22
	mov	w2, 2048
	mov	w1, 1
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L1070:
	mov	w3, 0
	mov	w2, 2048
	mov	w1, w24
	mov	x0, x22
	bl	VDH_Record_RegData
	b	.L1055
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	3
.LC299:
	.xword	g_HalDisable
	.align	3
.LC300:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC301:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintDownMsg
	.type	PrintDownMsg, %function
PrintDownMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w3
	mov	x20, x1
	mov	w22, w2
	bl	_mcount
	ldr	x1, .LC303
	mov	w2, w21
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC305
	mov	x2, x20
	mov	w0, 24
	bl	dprint_vfmw
	ldr	x1, .LC307
	mov	w2, w19
	mov	w0, 24
	bl	dprint_vfmw
	cmp	w22, wzr
	ble	.L1073
	lsl	w0, w22, 2
	ldr	x21, .LC309
	ldr	x23, .LC310
	sub	w22, w0, w22
	mov	w19, 0
	.p2align 2
.L1075:
	ldr	w3, [x20, w19, sxtw 2]
	mov	w2, w19
	mov	x1, x21
	mov	w0, 24
	bl	dprint_vfmw
	add	w3, w19, 1
	mov	x1, x21
	mov	w2, w3
	mov	w0, 24
	ldr	w3, [x20, w3, sxtw 2]
	bl	dprint_vfmw
	add	w3, w19, 2
	mov	x1, x21
	mov	w2, w3
	mov	w0, 24
	add	w19, w19, 3
	ldr	w3, [x20, w3, sxtw 2]
	bl	dprint_vfmw
	mov	x1, x23
	mov	w0, 24
	bl	dprint_vfmw
	cmp	w22, w19
	bne	.L1075
.L1073:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	PrintDownMsg, .-PrintDownMsg
	.align	3
.LC303:
	.xword	.LC302
	.align	3
.LC305:
	.xword	.LC304
	.align	3
.LC307:
	.xword	.LC306
	.align	3
.LC309:
	.xword	.LC308
	.align	3
.LC310:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	mov	x21, x2
	stp	w6, w5, [x29, 100]
	mov	x19, x3
	str	w4, [x29, 108]
	bl	_mcount
	add	x1, x29, 112
	mov	x0, x21
	stp	xzr, xzr, [x29, 112]
	stp	xzr, xzr, [x29, 128]
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	bl	GetFirstRawPacket
	ldr	w6, [x29, 120]
	cmp	w6, w22
	mov	w26, w6
	bgt	.L1079
	ldr	x24, .LC311
	mov	w27, 0
	mov	w25, 0
	add	x28, x21, 98304
	mov	w23, 1023
	.p2align 2
.L1082:
	cmp	w6, wzr
	mov	x2, 96
	add	x0, x29, 112
	add	x7, x19, x27, sxtw 2
	add	w25, w25, 1
	ble	.L1080
	ldr	w1, [x29, 116]
	str	w1, [x19, w27, sxtw 2]
	add	w27, w27, 3
	ldr	w3, [x29, 108]
	sub	w1, w1, #1
	add	w1, w1, w6
	add	w8, w3, w27, lsl 2
	stp	w1, w8, [x7, 4]
.L1080:
	str	w26, [x20, 4]
	ldr	w7, [x28, 4]
	ldr	w1, [x28, 16]
	cmp	w1, w7
	sxtw	x1, w1
	lsl	x7, x1, 2
	bne	.L1096
	ldr	w0, [x29, 104]
	cbz	w0, .L1097
.L1083:
	cbz	w25, .L1087
	cmp	w27, wzr
	ble	.L1086
	add	x27, x19, x27, sxtw 2
	str	wzr, [x27, -4]
.L1086:
	mov	w0, 1
	ldr	w3, [x29, 100]
	str	w0, [x20, 8]
	mov	w2, w25
	ldr	w0, [x29, 108]
	mov	x1, x19
	str	w25, [x20]
	bl	PrintDownMsg
	mov	w0, 0
.L1094:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1096:
	sub	x1, x7, x1
	ldr	x6, [x24, 104]
	add	x1, x21, x1, lsl 5
	blr	x6
	ldr	w0, [x28, 16]
	ldr	w6, [x29, 120]
	add	w0, w0, 1
	asr	w1, w0, 31
	add	w26, w26, w6
	lsr	w1, w1, 22
	cmp	w22, w26
	add	w0, w0, w1
	ccmp	w25, w23, 0, ge
	and	w0, w0, 1023
	sub	w0, w0, w1
	str	w0, [x28, 16]
	ble	.L1082
	ldr	w0, [x29, 104]
	cbnz	w0, .L1083
.L1097:
	ldr	w0, [x20, 4]
	sub	w1, w22, #16
	cmp	w0, w1
	bge	.L1083
.L1088:
	cmp	w22, w26
	mov	w1, 1023
	ccmp	w25, w1, 0, lt
	bgt	.L1083
	sub	w0, w22, w0
	cmp	w6, w0
	blt	.L1083
	ldr	w1, [x29, 116]
	add	x2, x19, x27, sxtw 2
	str	w1, [x19, w27, sxtw 2]
	add	w27, w27, 3
	sub	w1, w1, #1
	str	w0, [x29, 120]
	add	w1, w1, w0
	str	w1, [x2, 4]
	ldr	w1, [x29, 108]
	add	w25, w25, 1
	add	w1, w1, w27, lsl 2
	str	w1, [x2, 8]
	ldr	w1, [x20, 4]
	add	w0, w1, w0
	str	w0, [x20, 4]
	b	.L1083
.L1079:
	ldr	w0, [x29, 104]
	cbnz	w0, .L1087
	ldr	w0, [x20, 4]
	sub	w1, w22, #16
	cmp	w0, w1
	bge	.L1087
	mov	w27, 0
	mov	w25, 0
	b	.L1088
.L1087:
	mov	w0, -6
	b	.L1094
	.size	WriteScdMsg, .-WriteScdMsg
	.align	3
.LC311:
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
	mov	x23, x0
	mov	x0, x30
	mov	x21, x1
	mov	w25, w2
	mov	w22, w3
	bl	_mcount
	ldr	x24, .LC312
	add	x19, x21, 262144
	add	x20, x19, 160
	mov	x2, 12
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x24, 96]
	ldr	w27, [x19, 196]
	ldr	x26, [x19, 184]
	blr	x3
	ldr	w5, [x23, 52]
	mov	x0, x20
	mov	w6, w22
	mov	w4, w27
	mov	x3, x26
	add	x2, x21, 80
	mov	w1, w25
	bl	WriteScdMsg
	mov	w20, w0
	cbnz	w0, .L1099
	ldr	x0, [x24]
	blr	x0
	ldr	x3, .LC313
	sbfiz	x1, x22, 6, 32
	mov	w2, w22
	add	x3, x3, x1
	mov	x1, x23
	str	w0, [x3, 48]
	ldr	w0, [x19, 232]
	bl	WriteScdVtrlReg
.L1099:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	3
.LC312:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC313:
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
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	str	wzr, [x29, 68]
	add	x1, x20, 98304
	add	x4, x29, 64
	add	x3, x29, 68
	add	x2, x29, 60
	add	x1, x1, 104
	add	x0, x20, 80
	stp	wzr, wzr, [x29, 60]
	bl	SCDDRV_CheckConditionOfStartSCD
	mov	w19, w0
	cbnz	w0, .L1107
	add	x21, x20, 262144
	mov	w1, w22
	ldr	w0, [x21, 232]
	bl	SM_CfgBuf
	mov	w19, w0
	cbnz	w0, .L1108
	ldr	w3, [x21, 308]
	mov	x0, x20
	ldr	w2, [x29, 64]
	add	x1, x29, 72
	str	w2, [x21, 216]
	mul	w2, w2, w3
	lsl	w2, w2, 2
	str	w2, [x21, 212]
	bl	SCDDRV_SetCtrlReg
	ldr	w2, [x29, 68]
	mov	w3, w22
	mov	x1, x20
	add	x0, x29, 72
	bl	SCDDRV_StartSCD
	mov	w19, w0
	cbnz	w0, .L1102
	ldr	w1, [x29, 60]
	ldr	w0, [x29, 68]
	str	w1, [x21, 280]
	cmp	w1, w0
	str	w0, [x21, 284]
	bls	.L1109
	strb	wzr, [x20, 2]
.L1105:
	mov	w1, 1
	ldr	x0, .LC318
	str	w1, [x21, 240]
	mov	w19, 0
	strb	wzr, [x20, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x21, 304]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1108:
	ldr	x1, .LC317
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
.L1102:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1107:
	ldr	x1, .LC315
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1109:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L1105
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	3
.LC315:
	.xword	.LC314
	.align	3
.LC317:
	.xword	.LC316
	.align	3
.LC318:
	.xword	vfmw_Osal_Func_Ptr_S
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
	ldr	x1, .LC320
	mov	w2, w20
	mov	w0, 24
	bl	dprint_vfmw
	ldr	w2, [x19]
	mov	w0, 24
	ldr	x1, .LC322
	bl	dprint_vfmw
	ldr	w2, [x19, 8]
	mov	w0, 24
	ldr	x1, .LC324
	bl	dprint_vfmw
	ldr	w2, [x19, 12]
	mov	w0, 24
	ldr	x1, .LC326
	bl	dprint_vfmw
	ldr	w2, [x19, 16]
	mov	w0, 24
	ldr	x1, .LC328
	bl	dprint_vfmw
	ldr	w2, [x19, 20]
	mov	w0, 24
	ldr	x1, .LC330
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PrintScdStateReg, .-PrintScdStateReg
	.align	3
.LC320:
	.xword	.LC319
	.align	3
.LC322:
	.xword	.LC321
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.align	3
.LC328:
	.xword	.LC327
	.align	3
.LC330:
	.xword	.LC329
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x19, .LC331
	add	x19, x19, x21, sxtw 2
	ldr	w0, [x19, 8]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	str	w0, [x20]
	ldr	w0, [x19, 8]
	add	w0, w0, 2116
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	ldr	w1, [x19, 8]
	str	w0, [x20, 4]
	add	w0, w1, 2124
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
	mov	w1, w21
	mov	x0, x20
	bl	PrintScdStateReg
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	3
.LC331:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ProcessScdReturn.part.8, %function
ProcessScdReturn.part.8:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x29, 32
	mov	w1, w20
	bl	ReadScdStateReg
	mov	w0, 34464
	ldr	w2, [x29, 44]
	movk	w0, 0x1, lsl 16
	cmp	w2, w0
	bls	.L1113
	ldr	w0, [x19, 20]
	cbz	w0, .L1117
.L1113:
	add	x1, x19, 262144
	ldr	w0, [x29, 56]
	ldr	w1, [x1, 308]
	udiv	w0, w0, w1
	cmp	w0, w2
	csel	w1, w0, w2, ls
	cmp	w1, 1
	bls	.L1118
	ldr	w0, [x19, 20]
	sub	w1, w1, #1
	strb	wzr, [x19]
	cmp	w0, 2
	ldr	w2, [x29, 48]
	mov	x0, x19
	beq	.L1116
	bl	ProcessNotMpeg4ScdUpMsg
	mov	w0, 0
.L1114:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1116:
	bl	ProcessMpeg4ScdUpMsg
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1118:
	mov	x0, x19
	bl	ProcessNoSeg
	b	.L1114
.L1117:
	mov	x0, x19
	mov	w1, w2
	bl	ProcessExceptionalStartCodeNum
	mov	w0, -7
	b	.L1114
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
	add	x2, x19, 262144
	add	x2, x2, 160
	ldr	w0, [x2, 8]
	cmp	w0, 3
	beq	.L1122
	mov	w0, 2
	mov	w1, w20
	str	w0, [x2, 8]
	mov	x0, x19
	bl	ProcessScdReturn.part.8
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1122:
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
	cbnz	w0, .L1135
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1135:
	ldr	x3, .LC332
	mov	w2, w20
	ldr	x1, .LC334
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x23, [x3, 16]
	bl	dprint_vfmw
	ldr	x1, .LC336
	mov	w0, 26
	add	x22, x23, 80
	add	x19, x22, 98304
	ldr	w2, [x19]
	bl	dprint_vfmw
	ldr	x1, .LC338
	mov	w0, 26
	ldr	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	x1, .LC340
	mov	w0, 26
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC342
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC344
	mov	w0, 26
	ldr	w2, [x19, 16]
	bl	dprint_vfmw
	cmp	w21, 1
	beq	.L1125
.L1129:
	ldr	x1, .LC346
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
.L1125:
	cbz	x22, .L1126
	ldp	w28, w21, [x19]
	sub	w21, w21, w28
	cmp	w21, wzr
	add	w0, w21, 1024
	csel	w21, w0, w21, lt
	cmp	w21, wzr
	ble	.L1129
	ldr	x27, .LC348
	add	w0, w21, w28
	ldr	x26, .LC350
	ldr	x25, .LC352
	ldr	x24, .LC354
	str	w0, [x29, 108]
	.p2align 2
.L1128:
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
	bne	.L1128
	b	.L1129
	.p2align 3
.L1126:
	ldr	x2, .LC355
	mov	w3, 4676
	ldr	x1, .LC357
	mov	w0, 22
	add	x2, x2, 176
	bl	dprint_vfmw
	b	.L1129
	.size	PrintScdRawState, .-PrintScdRawState
	.align	3
.LC332:
	.xword	.LANCHOR0
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
.LC355:
	.xword	.LANCHOR4
	.align	3
.LC357:
	.xword	.LC356
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
	stp	x29, x30, [sp, -304]!
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
	ldr	x25, .LC358
	ldr	x21, .LC359
	mov	x2, 96
	add	x4, x25, x22, lsl 4
	mov	w1, 0
	add	x0, x29, 208
	ldr	x3, [x21, 96]
	ldr	x19, [x4, 16]
	blr	x3
	cbz	x19, .L1136
	ldr	w0, [x19, 20]
	cmp	w0, 20
	beq	.L1136
	ldr	x26, .LC367
	lsl	w28, w22, 24
	ldr	x24, .LC361
	add	x0, x26, 200
	ldr	x23, .LC363
	ldr	x27, .LC366
	str	x0, [x29, 104]
	b	.L1150
	.p2align 3
.L1168:
	add	x0, x25, x22, lsl 4
	ldr	x0, [x0, 16]
	cbz	x0, .L1140
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
	beq	.L1140
	add	x1, x29, 208
	mov	w0, w20
	bl	ReadRawStreamData
	cbnz	w0, .L1136
	add	x26, x19, 262144
	ldr	w0, [x29, 216]
	ldr	x4, [x21]
	ldr	w3, [x26, 288]
	ldr	w5, [x26, 312]
	ldr	w2, [x26, 316]
	add	w3, w3, w0
	add	w0, w5, w0
	str	w3, [x26, 288]
	add	w2, w2, 1
	str	w0, [x26, 312]
	str	w2, [x26, 316]
	blr	x4
	ldr	w2, [x26, 292]
	cbnz	w2, .L1142
	str	w0, [x26, 292]
.L1143:
	ldr	x2, [x29, 272]
	mov	x1, x24
	mov	w0, 29
	bl	dprint_vfmw
	ldp	w2, w3, [x29, 212]
	mov	x1, x23
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x1, [x29, 272]
	mov	x0, 4294967295
	cmp	x1, x0
	beq	.L1164
	add	x1, x29, 208
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbnz	w0, .L1165
.L1145:
	mov	w1, 1
	strb	w1, [x19, 3]
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1166
.L1148:
	add	x3, x29, 256
	add	x2, x29, 112
	ldp	x8, x9, [x29, 208]
	ldp	x6, x7, [x29, 224]
	ldp	x10, x11, [x3]
	add	x3, x29, 272
	mov	x1, x19
	ldp	x4, x5, [x29, 240]
	mov	w0, w20
	ldp	x12, x13, [x3]
	add	x3, x29, 288
	ldp	x14, x15, [x3]
	stp	x14, x15, [x29, 192]
	stp	x8, x9, [x29, 112]
	stp	x6, x7, [x29, 128]
	stp	x4, x5, [x29, 144]
	stp	x10, x11, [x29, 160]
	stp	x12, x13, [x29, 176]
	bl	SCDDRV_SaveRawStream
.L1150:
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1167
.L1138:
	cmp	w20, 31
	bls	.L1168
.L1140:
	ldr	x1, .LC369
	mov	w2, w20
	mov	w0, 23
	add	x19, x19, 262144
	bl	dprint_vfmw
	ldr	w0, [x19, 232]
	mov	w1, 0
	bl	PrintScdRawState
.L1136:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L1142:
	sub	w2, w0, w2
	cmp	w2, 2000
	bls	.L1143
	ldr	w3, [x26, 288]
	str	w0, [x26, 292]
	lsl	w0, w3, 3
	str	wzr, [x26, 288]
	udiv	w2, w0, w2
	lsl	w0, w2, 6
	sub	w0, w0, w2
	lsl	w0, w0, 1
	sub	w2, w0, w2
	ubfx	x2, x2, 7, 22
	str	w2, [x26, 296]
	b	.L1143
	.p2align 3
.L1167:
	add	x0, x19, 262144
	ldr	w0, [x0, 152]
	cmp	w0, 8
	ble	.L1138
	b	.L1136
	.p2align 3
.L1166:
	ldr	x0, [x21]
	blr	x0
	add	x2, x25, 632
	ldr	w3, [x27]
	ldr	w1, [x2, x22, lsl 2]
	sub	w1, w0, w1
	cmp	w1, w3
	bls	.L1148
	str	w0, [x2, x22, lsl 2]
	mov	w1, 3041
	ldr	x0, [x29, 104]
	mov	w2, w28
	bl	DBG_AddTrace
	b	.L1148
	.p2align 3
.L1164:
	mov	x0, -1
	add	x1, x29, 208
	str	x0, [x29, 272]
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbz	w0, .L1145
.L1165:
	ldr	x1, .LC365
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.size	FillRawData, .-FillRawData
	.align	3
.LC358:
	.xword	.LANCHOR0
	.align	3
.LC359:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC366:
	.xword	g_TraceBsPeriod
	.align	3
.LC367:
	.xword	.LANCHOR4
	.align	3
.LC369:
	.xword	.LC368
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
	ldr	x0, .LC372
	add	x0, x0, x21, sxtw 4
	ldr	x20, [x0, 16]
	cbz	x20, .L1182
	add	x0, x20, 98304
	mov	x1, x22
	add	x0, x0, 104
	bl	SM_SeekPtsInSegArray
	cbnz	w0, .L1172
.L1173:
	mov	w0, 0
.L1171:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1172:
	mov	w1, 0
	mov	w0, w21
	add	x20, x20, 80
	bl	DeleteRawPacketInBuffer
	mov	w3, 1
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	cbz	w0, .L1173
	add	x1, x20, 98304
	ldp	w3, w0, [x1]
	cmp	w3, w0
	bgt	.L1192
.L1191:
	sub	w3, w0, w3
	ldr	x2, [x22, 16]
	sxtw	x3, w3
	cmp	x3, x2
	bcs	.L1193
	sub	x3, x2, x3
	and	x0, x3, 1023
	lsr	x23, x3, 10
	cbnz	x0, .L1194
.L1178:
	add	w23, w23, 1
	mov	w19, 0
	cmp	w23, wzr
	bgt	.L1187
	b	.L1181
	.p2align 3
.L1195:
	cmp	w19, w23
	beq	.L1181
.L1187:
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	add	w19, w19, 1
	bl	SM_SeekPtsAfterFillNewRaw
	cbnz	w0, .L1195
	b	.L1173
	.p2align 3
.L1192:
	add	w0, w0, 1024
	b	.L1191
	.p2align 3
.L1194:
	add	w23, w23, 1
	b	.L1178
	.p2align 3
.L1181:
	mov	w0, -2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L1182:
	mov	w0, -1
	b	.L1171
.L1193:
	ldr	x1, .LC374
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1171
	.size	SM_SeekPts, .-SM_SeekPts
	.align	3
.LC372:
	.xword	.LANCHOR0
	.align	3
.LC374:
	.xword	.LC373
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
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbnz	w0, .L1205
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1205:
	ldr	x3, .LC375
	mov	w2, w21
	ldr	x1, .LC377
	mov	w0, 26
	add	x3, x3, x21, sxtw 4
	ldr	x23, [x3, 16]
	bl	dprint_vfmw
	ldr	x1, .LC379
	mov	w0, 26
	add	x22, x23, 98304
	add	x4, x22, 104
	str	x4, [x29, 104]
	add	x19, x4, 163840
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC381
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC383
	mov	w0, 26
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	x1, .LC385
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC387
	mov	w0, 26
	ldr	x2, [x22, 104]
	bl	dprint_vfmw
	ldr	x1, .LC389
	mov	w0, 26
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, .LC391
	mov	w0, 26
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	x1, .LC393
	mov	w0, 26
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	cmp	w20, 1
	ldr	x4, [x29, 104]
	beq	.L1198
.L1199:
	ldr	x1, .LC395
	mov	w2, w21
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
.L1198:
	ldp	w24, w22, [x19, 8]
	sub	w22, w22, w24
	ands	w22, w22, 2047
	beq	.L1199
	ldr	x28, .LC397
	add	w22, w24, w22
	ldr	x27, .LC399
	ldr	x26, .LC401
	ldr	x25, .LC403
	str	x4, [x29, 104]
	.p2align 2
.L1200:
	sxtw	x0, w24
	mov	x1, x28
	lsl	x19, x0, 6
	add	w24, w24, 1
	add	x19, x19, x0, lsl 4
	ldr	x0, [x29, 104]
	add	x20, x23, x19
	add	x20, x20, 98304
	add	x19, x0, x19
	mov	w0, 26
	ldr	w2, [x20, 124]
	bl	dprint_vfmw
	ldr	x2, [x20, 112]
	mov	x1, x27
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x19, 24]
	mov	x1, x26
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x19, 28]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldrsb	w2, [x20, 120]
	mov	w0, 26
	ldr	x1, .LC405
	bl	dprint_vfmw
	ldrb	w2, [x20, 121]
	mov	w0, 26
	ldr	x1, .LC407
	bl	dprint_vfmw
	ldr	x1, .LC409
	mov	w0, 26
	ldr	x2, [x19, 32]
	bl	dprint_vfmw
	cmp	w24, w22
	bne	.L1200
	b	.L1199
	.size	PrintScdSegState, .-PrintScdSegState
	.align	3
.LC375:
	.xword	.LANCHOR0
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
.LC383:
	.xword	.LC382
	.align	3
.LC385:
	.xword	.LC384
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
	ldr	x25, .LC410
	sxtw	x0, w21
	ldr	x23, .LC411
	lsl	x1, x0, 6
	ldr	x24, .LC412
	add	x0, x1, x0, lsl 3
	add	x22, x25, 16
	add	x0, x25, x0
	ldr	w19, [x0, 580]
	b	.L1212
	.p2align 3
.L1207:
	subs	w20, w20, #1
	beq	.L1215
.L1212:
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
	cbnz	w0, .L1207
	mov	w0, w19
	mov	w1, 0
	sxtw	x28, w19
	bl	PrintScdRawState
	mov	w1, 0
	mov	w0, w19
	bl	PrintScdSegState
	lsl	x1, x28, 4
	ldr	x0, [x23]
	ldr	x27, [x22, x1]
	blr	x0
	add	x26, x27, 262144
	ldr	w1, [x26, 304]
	subs	w1, w0, w1
	bmi	.L1208
	ldrsh	w2, [x27, 2]
	cmp	w2, 1
	beq	.L1216
.L1208:
	str	w0, [x26, 304]
	ldrsb	w0, [x27]
	cmp	w0, 1
	beq	.L1217
	strb	wzr, [x27, 1]
.L1210:
	ldr	x2, [x24, x28, lsl 3]
	mov	w1, w21
	mov	x0, x27
	add	x2, x2, 294912
	ldr	w2, [x2, 1216]
	str	w2, [x26, 456]
	bl	CutStreamWithSCD
	cmn	w0, #6
	cset	w1, eq
	strb	w1, [x27]
	cbnz	w0, .L1207
	ldr	x0, [x29, 104]
	add	x2, x25, 760
	ldr	x3, .LC413
	mov	w1, 1
	add	x2, x2, x28, lsl 2
	mov	w4, 4222
	str	w19, [x0]
	add	x3, x3, 216
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
.L1216:
	cmp	w1, 199
	bhi	.L1208
	subs	w20, w20, #1
	bne	.L1212
.L1215:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -3
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1217:
	mov	x0, x27
	bl	SCDDRV_ProcessSegFull
	b	.L1210
	.size	SM_DoNextInstance.part.11, .-SM_DoNextInstance.part.11
	.align	3
.LC410:
	.xword	.LANCHOR0
	.align	3
.LC411:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC412:
	.xword	s_pstVfmwChan
	.align	3
.LC413:
	.xword	.LANCHOR4
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
	ldr	x2, .LC416
	add	x2, x2, x19, sxtw 2
	ldr	w0, [x2, 600]
	cbz	w0, .L1219
	cmp	w0, 1
	mov	w0, -3
	beq	.L1222
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1219:
	mov	x1, x20
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1222:
	mov	w1, 2
	str	w1, [x2, 600]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	3
.LC416:
	.xword	.LANCHOR0
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
	ldr	x20, .LC417
	add	x1, x20, x19, lsl 2
	ldr	w0, [x1, 600]
	cbz	w0, .L1224
	cmp	w0, 1
	beq	.L1227
.L1223:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1224:
	add	x1, x29, 60
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1223
	lsl	x1, x19, 6
	ldr	x0, .LC418
	add	x19, x1, x19, lsl 3
	add	x20, x20, 528
	add	x19, x20, x19
	ldr	w2, [x29, 60]
	ldr	x0, [x0]
	mov	w1, 1
	stp	w2, w1, [x19, 52]
	blr	x0
	str	w0, [x19, 60]
	ldr	x2, .LC419
	mov	w3, 4480
	ldr	x1, .LC421
	mov	w0, 26
	add	x2, x2, 240
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1227:
	mov	w0, 2
	str	w0, [x1, 600]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
	.align	3
.LC417:
	.xword	.LANCHOR0
	.align	3
.LC418:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC419:
	.xword	.LANCHOR4
	.align	3
.LC421:
	.xword	.LC420
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
	cbnz	w19, .L1228
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
.L1228:
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
	ldr	x20, .LC423
	add	x20, x20, 16
	b	.L1232
	.p2align 3
.L1231:
	add	w19, w19, 1
	cmp	w19, 32
	beq	.L1239
.L1232:
	ldr	x0, [x20]
	add	x20, x20, 16
	add	x1, x0, 262144
	cbz	x0, .L1231
	ldr	w0, [x1, 248]
	cmp	w0, 1
	bne	.L1231
	mov	w0, w19
	add	w19, w19, 1
	bl	FillRawData
	cmp	w19, 32
	bne	.L1232
	.p2align 2
.L1239:
	ldr	x19, .LC424
	mov	w4, 1
	ldr	x1, .LC426
	mov	w3, 0
	add	x19, x19, 264
	mov	w0, 26
	mov	x2, x19
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_CheckDevice
	cbz	w0, .L1233
	ldr	x1, .LC428
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4538
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1233:
	ldr	x1, .LC430
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4533
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Wakeup, .-SM_Wakeup
	.align	3
.LC423:
	.xword	.LANCHOR0
	.align	3
.LC424:
	.xword	.LANCHOR4
	.align	3
.LC426:
	.xword	.LC425
	.align	3
.LC428:
	.xword	.LC427
	.align	3
.LC430:
	.xword	.LC429
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
	stp	x25, x26, [sp, 64]
	sxtw	x22, w0
	mov	x0, x30
	mov	x23, x22
	bl	_mcount
	ldr	x19, .LC432
	mov	w0, 0
	ldr	x1, [x19, 24]
	blr	x1
	ldr	x21, .LC433
	add	x20, x21, x22, lsl 2
	ldr	w0, [x20, 8]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbnz	x0, 0, .L1257
.L1241:
	ldr	x0, .LC435
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1249
	mov	w1, w23
	mov	w0, 0
	bl	VDH_Notify_ModuleIdle
.L1249:
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1257:
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
	beq	.L1258
	ldr	x3, .LC434
	mov	w4, 4358
	add	x2, x21, 888
	mov	w1, 2
	add	x3, x3, 280
	mov	w0, w24
	bl	RecordPOS
	mov	w0, w22
	bl	SCDDRV_RecordGlobalState
	ldr	w0, [x20, 56]
	cmp	w0, 1
	beq	.L1259
.L1243:
	ldr	x1, [x19, 256]
	mov	w0, 1
	blr	x1
	ldr	x1, [x19, 256]
	mov	w0, 0
	blr	x1
	b	.L1241
	.p2align 3
.L1258:
	ldr	x1, [x19, 256]
	mov	w0, 1
	str	wzr, [x20, 56]
	blr	x1
	b	.L1241
	.p2align 3
.L1259:
	add	x26, x25, 262144
	ldr	w0, [x26, 248]
	cmp	w0, 1
	beq	.L1260
.L1244:
	add	x1, x21, x22, lsl 2
	str	wzr, [x26, 240]
	ldr	w0, [x1, 600]
	cbz	w0, .L1247
	cmp	w0, 1
	beq	.L1261
.L1248:
	lsl	x0, x22, 6
	ldr	x1, [x19, 256]
	add	x22, x0, x22, lsl 3
	mov	w0, 1
	add	x21, x21, x22
	str	wzr, [x21, 584]
	blr	x1
	b	.L1243
	.p2align 3
.L1247:
	add	x1, x29, 92
	mov	w0, w23
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1248
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
	b	.L1243
.L1261:
	mov	w0, 2
	str	w0, [x1, 600]
	b	.L1248
.L1260:
	ldr	w0, [x20, 52]
	mov	w1, 0
	bl	PrintScdRawState
	ldr	w0, [x20, 52]
	mov	w1, 0
	bl	PrintScdSegState
	ldr	w1, [x26, 168]
	add	x0, x26, 160
	cmp	w1, 3
	beq	.L1262
	mov	w2, 2
	mov	w1, w22
	str	w2, [x0, 8]
	mov	x0, x25
	bl	ProcessScdReturn.part.8
.L1246:
	mov	w0, w24
	add	x20, x21, 528
	bl	SCDDRV_MoveRawByOmxPath
	lsl	x0, x22, 6
	mov	w1, 0
	add	x0, x0, x22, lsl 3
	add	x20, x20, x0
	ldr	w0, [x20, 52]
	bl	PrintScdRawState
	ldr	w0, [x20, 52]
	mov	w1, 0
	bl	PrintScdSegState
	b	.L1244
.L1262:
	mov	w1, 2
	str	w1, [x0, 8]
	b	.L1246
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	3
.LC432:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC433:
	.xword	.LANCHOR0
	.align	3
.LC434:
	.xword	.LANCHOR4
	.align	3
.LC435:
	.xword	g_HalDisable
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
	.type	__func__.51629, %object
	.size	__func__.51629, 19
__func__.51629:
	.string	"SCDDRV_LoadDspCode"
	.zero	5
	.type	__func__.51710, %object
	.size	__func__.51710, 16
__func__.51710:
	.string	"DeleteRawPacket"
	.type	__FUNCTION__.51820, %object
	.size	__FUNCTION__.51820, 17
__FUNCTION__.51820:
	.string	"ReleaseStreamSeg"
	.zero	7
	.type	__func__.51885, %object
	.size	__func__.51885, 14
__func__.51885:
	.string	"SM_OpenSCDDrv"
	.zero	2
	.type	__func__.51969, %object
	.size	__func__.51969, 16
__func__.51969:
	.string	"SM_CopyRawToSeg"
	.type	__func__.52219, %object
	.size	__func__.52219, 16
__func__.52219:
	.string	"GetMeg4ModeFlag"
	.type	__func__.52246, %object
	.size	__func__.52246, 21
__func__.52246:
	.string	"ProcessMpeg4ScdUpMsg"
	.zero	3
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
	.type	__func__.52289, %object
	.size	__func__.52289, 17
__func__.52289:
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
	.type	__func__.52316, %object
	.size	__func__.52316, 17
__func__.52316:
	.string	"FillEosRawStream"
	.zero	7
	.type	__func__.52340, %object
	.size	__func__.52340, 17
__func__.52340:
	.string	"FillVC1ExtraData"
	.zero	7
	.type	__func__.52345, %object
	.size	__func__.52345, 19
__func__.52345:
	.string	"FillDIVX3ExtraData"
	.zero	5
	.type	__func__.52350, %object
	.size	__func__.52350, 19
__func__.52350:
	.string	"FillREAL8ExtraData"
	.zero	5
	.type	__func__.52358, %object
	.size	__func__.52358, 14
__func__.52358:
	.string	"FillExtraData"
	.zero	2
	.type	__func__.51724, %object
	.size	__func__.51724, 24
__func__.51724:
	.string	"DeleteRawPacketInBuffer"
	.type	__FUNCTION__.51859, %object
	.size	__FUNCTION__.51859, 9
__FUNCTION__.51859:
	.string	"SM_Reset"
	.zero	7
	.type	__func__.52511, %object
	.size	__func__.52511, 19
__func__.52511:
	.string	"SCDDRV_CheckDevice"
	.zero	5
	.type	__FUNCTION__.52578, %object
	.size	__FUNCTION__.52578, 17
__FUNCTION__.52578:
	.string	"PrintScdRawState"
	.zero	7
	.type	__FUNCTION__.52279, %object
	.size	__FUNCTION__.52279, 12
__FUNCTION__.52279:
	.string	"FillRawData"
	.zero	4
	.type	__FUNCTION__.52471, %object
	.size	__FUNCTION__.52471, 18
__FUNCTION__.52471:
	.string	"SM_DoNextInstance"
	.zero	6
	.type	__func__.52517, %object
	.size	__func__.52517, 19
__func__.52517:
	.string	"SCDDRV_ActivateSCD"
	.zero	5
	.type	__func__.52537, %object
	.size	__func__.52537, 10
__func__.52537:
	.string	"SM_Wakeup"
	.zero	6
	.type	__FUNCTION__.52504, %object
	.size	__FUNCTION__.52504, 19
__FUNCTION__.52504:
	.string	"SM_SCDIntServeProc"
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
.LC2:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC7:
	ASCII(.string	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\n" )
	.zero	5
.LC12:
	ASCII(.string	"Warn: eVidStd = %d have not DSP vfmw bin file!!\n" )
	.zero	7
.LC15:
	ASCII(.string	"%s failed!\n" )
	.zero	4
.LC17:
	ASCII(.string	"%s success!\n" )
	.zero	3
.LC28:
	ASCII(.string	"Ignore the reset request when the SCD[%d] clock is closed.\n" )
	.zero	4
.LC30:
	ASCII(.string	"SCD[%d]   ResetSCD ERROR!!!\n" )
	.zero	3
.LC44:
	ASCII(.string	"line: %d Get SmID fail!" )
.LC46:
	ASCII(.string	"DelRaw err PacketNum = %d, DelNum = %d\n" )
.LC49:
	ASCII(.string	"%s release RawPhyAddr = 0x%x,Len = %d\n" )
	.zero	1
.LC53:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = %d,Next Length = %d,is_extern_eop_flag = %d\n\n" )
	.zero	7
.LC55:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,Next Length = %d\n\n" )
	.zero	3
.LC58:
	ASCII(.string	"line: %d pSmInstArray is NULL!\n" )
.LC67:
	ASCII(.string	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLastSeg=%d\n" )
	.zero	5
.LC69:
	ASCII(.string	"-------- forece release seg[%d] -----------\n" )
	.zero	3
.LC71:
	ASCII(.string	"\n" )
	.zero	6
.LC73:
	ASCII(.string	"0x%02x," )
.LC75:
	ASCII(.string	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d StreamID=%d\n" )
	.zero	4
.LC78:
	ASCII(.string	"Array out of bound in function %s\n" )
	.zero	5
.LC92:
	ASCII(.string	"ScdId is wrong! %s error\n" )
	.zero	6
.LC94:
	ASCII(.string	"%s,line: %d\n" )
	.zero	3
.LC99:
	ASCII(.string	"%s: g_hex_base_vir_addr = NULL\n" )
.LC106:
	ASCII(.string	"line: %d, SmID = %d, pSmCfg = %p is not expected!\n" )
	.zero	5
.LC111:
	ASCII(.string	"line: %d, SmID = %d is not expected!\n" )
	.zero	2
.LC113:
	ASCII(.string	"line: %d, SmID = %d, ScdId = %d is not expected!\n" )
	.zero	6
.LC122:
	ASCII(.string	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\n" )
	.zero	6
.LC124:
	ASCII(.string	"line: %d, delet raw failed!\n" )
	.zero	3
.LC127:
	ASCII(.string	"[%s %d] VirAddr is null!!\n" )
	.zero	5
.LC132:
	ASCII(.string	"copy raw to seg fail\n" )
	.zero	2
.LC142:
	ASCII(.string	"Line: %d, start code num from scd state reg: %d, release raw packet anyway!\n" )
	.zero	3
.LC144:
	ASCII(.string	"Error, discard raw packet!\n" )
	.zero	4
.LC146:
	ASCII(.string	"Line: %d, The length of seg packet is invalid: %d\n" )
	.zero	5
.LC149:
	ASCII(.string	"[%s %d] pCurrentStartCodeVirAddr is null!!\n" )
	.zero	4
.LC154:
	ASCII(.string	"[%s %d] pNextStartCodeVirAddr is null!!\n" )
	.zero	7
.LC157:
	ASCII(.string	"ValidSegNum = %d, FilteredSegNum = 0, release raw packet anyway!\n" )
	.zero	6
.LC163:
	ASCII(.string	"%s: pRawPacket = NULL!\n" )
.LC166:
	ASCII(.string	"%s: unkown standard type = %d!\n" )
.LC168:
	ASCII(.string	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\n" )
	.zero	7
.LC177:
	ASCII(.string	"%s: FlagLen(%d) > RawPacketLength(%d)\n" )
	.zero	1
.LC181:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, header_buf: %d)\n" )
.LC184:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, str_buf: %d)\n" )
	.zero	3
.LC186:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf: %d, header_buf: %d)\n" )
	.zero	4
.LC189:
	ASCII(.string	"Func: %s, buffer has no enough space, (act: %d, str_buf: %d)\n" )
	.zero	2
.LC195:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf:%d)\n" )
	.zero	5
.LC198:
	ASCII(.string	"%s: RawPacket Length %d <= 0\n" )
	.zero	2
.LC202:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReleaseRawStreamData pStreamIntf is NULL!" )
.LC205:
	ASCII(.string	"line: %d s_SmIIS[%d].pSmInstArray is NULL\n" )
	.zero	5
.LC208:
	ASCII(.string	"SmID = %d is not expected!\n" )
	.zero	4
.LC212:
	ASCII(.string	"%s release RawPhyAddr = 0x%x, Len = %d\n" )
.LC217:
	ASCII(.string	"line: %d, pSmInstArray is NULL!\n" )
	.zero	7
.LC220:
	ASCII(.string	"%s %d force to clear SCDState = 0\n" )
	.zero	5
.LC223:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum !!\n" )
	.zero	3
.LC228:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReadRawStreamData pStreamIntf is NULL!" )
	.zero	3
.LC231:
	ASCII(.string	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\n" )
	.zero	5
.LC233:
	ASCII(.string	"Chan %d FillEosRawStream failed!\n" )
	.zero	6
.LC235:
	ASCII(.string	"Chan %d FillExtraData failed!\n" )
	.zero	1
.LC237:
	ASCII(.string	"Release this packet failed!\n" )
	.zero	3
.LC241:
	ASCII(.string	"No space for raw move, total:%d+%d > max:%d!\n" )
	.zero	2
.LC244:
	ASCII(.string	"(%d ms) not release stream seg, release anyway!\n" )
	.zero	7
.LC249:
	ASCII(.string	"Error:now DspState[0]= %d,[1]= %d not except!!\n" )
.LC256:
	ASCII(.string	"Move raw data failed, force to reset scd.\n" )
	.zero	5
.LC258:
	ASCII(.string	"SCD GetRawStreamNum Fail.\n" )
	.zero	5
.LC262:
	ASCII(.string	"%s,%d,SCD(ID = %d) SCDState = %d\n" )
	.zero	6
.LC264:
	ASCII(.string	"%s,%d,SCD(ID = %d) return Idle!\n" )
	.zero	7
.LC267:
	ASCII(.string	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\n" )
	.zero	4
.LC270:
	ASCII(.string	"%s,%d,SCD(ID = %d) really busy!\n" )
	.zero	7
.LC278:
	ASCII(.string	"scd time out: t_start,t_now,t_wait = %d,%d,%d\n" )
	.zero	1
.LC281:
	ASCII(.string	"***Print Scd[%d] Vtrl Reg Now\n" )
	.zero	1
.LC283:
	ASCII(.string	"DownMsgPhyAddr = %x\n" )
	.zero	3
.LC285:
	ASCII(.string	"UpMsgPhyAddr = %x\n" )
	.zero	5
.LC287:
	ASCII(.string	"UpLen = %x\n" )
	.zero	4
.LC289:
	ASCII(.string	"BufferFirst = %x\n" )
	.zero	6
.LC291:
	ASCII(.string	"BufferLast = %x\n" )
	.zero	7
.LC293:
	ASCII(.string	"BufferIni = %x\n" )
.LC295:
	ASCII(.string	"ScdProtocol = %x\n" )
	.zero	6
.LC297:
	ASCII(.string	"ScdStart = %x\n" )
	.zero	1
.LC302:
	ASCII(.string	"***Print SCD[%d] Down Msg Now\n" )
	.zero	1
.LC304:
	ASCII(.string	"DownMsgVirAddr = %x   \n" )
.LC306:
	ASCII(.string	"DownMsgPhyAddr = %x   \n" )
.LC308:
	ASCII(.string	"DownMsg[%d] = %x   " )
	.zero	4
.LC314:
	ASCII(.string	"Cann't Start SCD, Ret = %d\n" )
	.zero	4
.LC316:
	ASCII(.string	"SM_CfgBuf Err! ret =%d\n" )
.LC319:
	ASCII(.string	"***Print Scd[%d] State Reg\n" )
	.zero	4
.LC321:
	ASCII(.string	"Scdover = %d \n" )
	.zero	1
.LC323:
	ASCII(.string	"ShortScdNum = %d \n" )
	.zero	5
.LC325:
	ASCII(.string	"ScdNum = %d \n" )
	.zero	2
.LC327:
	ASCII(.string	"ScdRollAddr = %0x \n" )
	.zero	4
.LC329:
	ASCII(.string	"SrcEaten = %d \n" )
.LC333:
	ASCII(.string	"********** SmID [%d] RawState begin **********\n" )
.LC335:
	ASCII(.string	"RawHead=%d\n" )
	.zero	4
.LC337:
	ASCII(.string	"RawTail=%d\n" )
	.zero	4
.LC339:
	ASCII(.string	"RawHistory=%d\n" )
	.zero	1
.LC341:
	ASCII(.string	"RawFirstPacketOffset=%d\n" )
	.zero	7
.LC343:
	ASCII(.string	"CurShowIndex=%d\n" )
	.zero	7
.LC345:
	ASCII(.string	"********** SmID [%d] RawState end   **********\n" )
.LC347:
	ASCII(.string	"RawPhyAddr=0x%x\n" )
	.zero	7
.LC349:
	ASCII(.string	"RawVirAddr=0x%x\n" )
	.zero	7
.LC351:
	ASCII(.string	"RawLength=%d\n" )
	.zero	2
.LC353:
	ASCII(.string	"RawPts=%ld\n" )
	.zero	4
.LC356:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum!!\n" )
	.zero	4
.LC360:
	ASCII(.string	"raw_pts: %lld\n" )
	.zero	1
.LC362:
	ASCII(.string	"Get RawPhyAddr=0x%x,Len=%d\n" )
	.zero	4
.LC364:
	ASCII(.string	"!!!push raw err!!!\n" )
	.zero	4
.LC368:
	ASCII(.string	"Chan%d raw full\n" )
	.zero	7
.LC373:
	ASCII(.string	"RawNum %lld <= RawNumInVfmw %lld\n" )
	.zero	6
.LC376:
	ASCII(.string	"********** SmID [%d] SegState begin **********\n" )
.LC378:
	ASCII(.string	"SegHead=%d\n" )
	.zero	4
.LC380:
	ASCII(.string	"SegTail=%d\n" )
	.zero	4
.LC382:
	ASCII(.string	"SegCurrent=%d\n" )
	.zero	1
.LC384:
	ASCII(.string	"SegBufPhyAddr=%p\n" )
	.zero	6
.LC386:
	ASCII(.string	"SegBufVirAddr=%p\n" )
	.zero	6
.LC388:
	ASCII(.string	"SegBufSize=%d\n" )
	.zero	1
.LC390:
	ASCII(.string	"SegBufReadAddr=%p\n" )
	.zero	5
.LC392:
	ASCII(.string	"SegBufWriteAddr=%pd\n" )
	.zero	3
.LC394:
	ASCII(.string	"********** SmID [%d] SegState end   **********\n" )
.LC396:
	ASCII(.string	"SegPhyAddr=0x%x\n" )
	.zero	7
.LC398:
	ASCII(.string	"SegVirAddr=0x%x\n" )
	.zero	7
.LC400:
	ASCII(.string	"SegLength=%d\n" )
	.zero	2
.LC402:
	ASCII(.string	"SegStreamID=%d\n" )
.LC404:
	ASCII(.string	"SegState=%d\n" )
	.zero	3
.LC406:
	ASCII(.string	"SegIsLastSeg=%d\n" )
	.zero	7
.LC408:
	ASCII(.string	"SegPts=%lld\n" )
	.zero	3
.LC420:
	ASCII(.string	"%s,%d, active scd Success!\n" )
	.zero	4
.LC425:
	ASCII(.string	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\n" )
.LC427:
	ASCII(.string	"%s,%d,SCD(ID = %d) return BUSY!!\n" )
	.zero	6
.LC429:
	ASCII(.string	"%s,%d,find idle SCD(ID = %d)\n" )
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
	.type	last_rec_pos_time.52274, %object
	.size	last_rec_pos_time.52274, 128
last_rec_pos_time.52274:
	.zero	128
	.type	LastRecPosTime.52468, %object
	.size	LastRecPosTime.52468, 128
LastRecPosTime.52468:
	.zero	128
	.type	last_rec_pos_time.52502, %object
	.size	last_rec_pos_time.52502, 128
last_rec_pos_time.52502:
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
