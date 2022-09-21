#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"fsp.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	FSP_ClearContext, %function
FSP_ClearContext:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L5
	ldr	x20, .LC4
	mov	w0, 8
	add	x21, x19, 24576
	ldr	x1, [x20, 24]
	blr	x1
	strb	wzr, [x19, 2]
	strb	wzr, [x19, 4]
	mov	x2, 20
	strb	wzr, [x19, 5]
	mov	w1, 0
	strb	wzr, [x19, 3]
	add	x0, x19, 36
	stp	wzr, wzr, [x19, 8]
	stp	wzr, wzr, [x19, 16]
	str	wzr, [x19, 24]
	str	wzr, [x19, 32]
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 56
	blr	x3
	ldr	x3, [x20, 96]
	add	x0, x19, 20480
	mov	x2, 2816
	mov	w1, 0
	add	x0, x0, 1424
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 2816
	mov	w1, 0
	add	x0, x21, 144
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 256
	mov	w1, 0
	add	x0, x21, 2960
	blr	x3
	ldr	x1, [x20, 32]
	mov	w0, 8
	blr	x1
	mov	w0, 0
.L3:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L5:
	ldr	x3, .LC1
	mov	w2, 136
	ldr	x1, .LC3
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3
	.size	FSP_ClearContext, .-FSP_ClearContext
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	FSP_IsSpecialFrm.part.3, %function
FSP_IsSpecialFrm.part.3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, .LC5
	ldr	x3, [x0, w20, sxtw 3]
	cbz	x3, .L10
	sub	w1, w19, #1
	mov	w0, 0
	cmn	w1, #3
	bhi	.L7
	add	x2, x3, 294912
	ldr	w1, [x2, 1168]
	cbz	w1, .L7
	ldr	w0, [x2, 644]
	cmp	w19, w0
	beq	.L14
	mov	w2, 0
	b	.L8
	.p2align 3
.L9:
	add	x0, x0, 2088
	add	x0, x3, x0, lsl 4
	ldr	w0, [x0, 4]
	cmp	w19, w0
	beq	.L14
.L8:
	add	w2, w2, 1
	cmp	w2, w1
	sxtw	x0, w2
	add	x0, x0, 16384
	bne	.L9
.L10:
	mov	w0, 0
.L7:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L14:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsSpecialFrm.part.3, .-FSP_IsSpecialFrm.part.3
	.align	3
.LC5:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	FSP_IsDecFsAvailable.part.4, %function
FSP_IsDecFsAvailable.part.4:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	mov	w0, 1
	ble	.L18
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L18:
	ldr	w1, [x20, 8]
	mov	w0, w19
	bl	FSP_IsSpecialFrm.part.3
	cmp	w0, wzr
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsDecFsAvailable.part.4, .-FSP_IsDecFsAvailable.part.4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC6
	mov	x2, 256
	ldr	x0, .LC7
	mov	w1, 0
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x29, x30, [sp], 16
	ret
	.size	FSP_Init, .-FSP_Init
	.align	3
.LC6:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC7:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigAttribute
	.type	FSP_ConfigAttribute, %function
FSP_ConfigAttribute:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L24
	ldr	x0, .LC11
	ldr	x2, [x0, w19, sxtw 3]
	ldr	w0, [x2, 28]
	cmp	w0, 1
	bne	.L25
	ldrsb	w1, [x20]
	mov	w0, 0
	strb	w1, [x2, 1]
.L22:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L25:
	ldr	x3, .LC13
	mov	w2, 395
	ldr	x1, .LC10
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L22
	.p2align 3
.L24:
	ldr	x3, .LC9
	mov	w2, 394
	ldr	x1, .LC10
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L22
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC10:
	.xword	.LC2
	.align	3
.LC11:
	.xword	.LANCHOR0
	.align	3
.LC13:
	.xword	.LC12
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearContextAll
	.type	FSP_ClearContextAll, %function
FSP_ClearContextAll:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L30
	ldr	x0, .LC16
	ldr	x19, [x0, w19, sxtw 3]
	cbz	x19, .L31
	ldr	x3, .LC19
	mov	x2, 27792
	mov	w1, 0
	mov	x0, x19
	ldrsb	w22, [x19, 3]
	ldr	x3, [x3, 96]
	ldrsb	w21, [x19, 5]
	ldrsb	w25, [x19]
	ldrsb	w24, [x19, 1]
	ldp	w23, w20, [x19, 28]
	blr	x3
	strb	w25, [x19]
	strb	w24, [x19, 1]
	mov	w0, 0
	strb	w22, [x19, 3]
	strb	w21, [x19, 5]
	stp	w23, w20, [x19, 28]
.L28:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L30:
	ldr	x3, .LC14
	mov	w2, 415
	ldr	x1, .LC15
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L28
.L31:
	ldr	x3, .LC18
	mov	w2, 416
	ldr	x1, .LC15
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L28
	.size	FSP_ClearContextAll, .-FSP_ClearContextAll
	.align	3
.LC14:
	.xword	.LC8
	.align	3
.LC15:
	.xword	.LC2
	.align	3
.LC16:
	.xword	.LANCHOR0
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC19:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_EnableInstance
	.type	FSP_EnableInstance, %function
FSP_EnableInstance:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L36
	ldr	x21, .LC22
	ldr	x0, [x21, w20, sxtw 3]
	cbnz	x0, .L37
	ldr	x3, .LC25
	mov	x2, 27792
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	strb	w20, [x19]
	mov	w0, 1
	stp	w0, wzr, [x19, 28]
	str	x19, [x21, w20, sxtw 3]
	mov	w0, 0
.L34:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L37:
	ldr	x3, .LC24
	mov	w2, 442
	ldr	x1, .LC21
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L36:
	ldr	x3, .LC20
	mov	w2, 441
	ldr	x1, .LC21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L34
	.size	FSP_EnableInstance, .-FSP_EnableInstance
	.align	3
.LC20:
	.xword	.LC8
	.align	3
.LC21:
	.xword	.LC2
	.align	3
.LC22:
	.xword	.LANCHOR0
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC25:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_DisableInstance
	.type	FSP_DisableInstance, %function
FSP_DisableInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L43
	ldr	x1, .LC28
	ldr	x0, [x1, w19, sxtw 3]
	cbz	x0, .L44
	ldr	w2, [x0, 28]
	cmp	w2, 1
	beq	.L45
.L42:
	str	xzr, [x1, w19, sxtw 3]
.L38:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L45:
	str	wzr, [x0, 28]
	b	.L42
	.p2align 3
.L43:
	ldr	x3, .LC26
	mov	w2, 458
	ldr	x1, .LC27
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L44:
	ldr	x3, .LC29
	mov	w2, 459
	ldr	x1, .LC27
	bl	dprint_vfmw
	b	.L38
	.size	FSP_DisableInstance, .-FSP_DisableInstance
	.align	3
.LC26:
	.xword	.LC8
	.align	3
.LC27:
	.xword	.LC2
	.align	3
.LC28:
	.xword	.LANCHOR0
	.align	3
.LC29:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_Exit
	.type	FSP_Exit, %function
FSP_Exit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	x19, 0
	bl	_mcount
	ldr	x20, .LC32
	b	.L48
	.p2align 3
.L47:
	add	x19, x19, 1
	cmp	x19, 32
	beq	.L56
.L48:
	ldr	x0, [x20, x19, lsl 3]
	cbz	x0, .L47
	ldr	w0, [x0, 28]
	cbz	w0, .L47
	mov	w0, w19
	add	x19, x19, 1
	bl	FSP_DisableInstance
	cmp	x19, 32
	bne	.L48
.L56:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_Exit, .-FSP_Exit
	.align	3
.LC32:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ResetInstance
	.type	FSP_ResetInstance, %function
FSP_ResetInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC33
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L60
	bl	FSP_ClearContext
	mov	w0, 0
.L59:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L60:
	ldr	x3, .LC34
	mov	w2, 477
	ldr	x1, .LC35
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	3
.LC33:
	.xword	.LANCHOR0
	.align	3
.LC34:
	.xword	.LC17
	.align	3
.LC35:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L81
	ldr	x0, .LC41
	ldr	x21, [x0, w20, sxtw 3]
	cbz	x21, .L82
	ldr	x3, .LC43
	mov	x2, 21760
	mov	w1, 0
	add	x0, x21, 144
	ldr	x3, [x3, 96]
	blr	x3
	ldrsb	w0, [x21, 3]
	cmp	w0, wzr
	ble	.L71
	sub	w0, w0, #1
	mov	w22, 88
	mov	x1, 21994
	add	x19, x21, 20480
	add	x19, x19, 1426
	mov	w23, 4
	umaddl	x22, w0, w22, x1
	add	x22, x21, x22
	.p2align 2
.L70:
	cmp	w20, 31
	ble	.L83
.L68:
	strb	wzr, [x19]
.L69:
	strb	wzr, [x19, -1]
	add	x19, x19, 88
	strb	wzr, [x19, -90]
	str	wzr, [x19, -18]
	cmp	x19, x22
	bne	.L70
.L71:
	ldrsb	w0, [x21, 4]
	cmp	w0, wzr
	ble	.L67
	sub	w0, w0, #1
	mov	w22, 88
	mov	x1, 24810
	add	x19, x21, 24576
	add	x19, x19, 146
	mov	w23, 4
	umaddl	x22, w0, w22, x1
	add	x22, x21, x22
	.p2align 2
.L76:
	cmp	w20, 31
	ble	.L84
.L74:
	strb	wzr, [x19]
.L75:
	strb	wzr, [x19, -1]
	add	x19, x19, 88
	strb	wzr, [x19, -90]
	str	wzr, [x19, -18]
	cmp	x19, x22
	bne	.L76
.L67:
	ldrsb	w0, [x21, 5]
	cmp	w0, wzr
	ble	.L73
	sub	w1, w0, #1
	mov	x3, 27548
	add	x0, x21, 24576
	mov	w2, 1
	add	x1, x3, x1, uxtw 3
	add	x0, x0, 2964
	add	x1, x21, x1
	.p2align 2
.L77:
	strb	w2, [x0]
	add	x0, x0, 8
	strb	wzr, [x0, -7]
	cmp	x1, x0
	bne	.L77
.L73:
	mov	w0, 0
	str	wzr, [x21, 12]
.L63:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L83:
	ldr	w1, [x19, 6]
	mov	w0, w20
	bl	FSP_IsSpecialFrm.part.3
	cmp	w0, 1
	bne	.L68
	strb	w23, [x19]
	b	.L69
	.p2align 3
.L84:
	ldr	w1, [x19, 6]
	mov	w0, w20
	bl	FSP_IsSpecialFrm.part.3
	cmp	w0, 1
	bne	.L74
	strb	w23, [x19]
	b	.L75
.L81:
	ldr	x3, .LC39
	mov	w2, 491
	ldr	x1, .LC40
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L63
.L82:
	ldr	x3, .LC42
	mov	w2, 492
	ldr	x1, .LC40
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L63
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	3
.LC39:
	.xword	.LC8
	.align	3
.LC40:
	.xword	.LC2
	.align	3
.LC41:
	.xword	.LANCHOR0
	.align	3
.LC42:
	.xword	.LC17
	.align	3
.LC43:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L95
	cbz	x21, .L96
	ldr	x0, .LC48
	ldr	x19, [x0, w20, sxtw 3]
	cbz	x19, .L89
	ldr	w0, [x19, 28]
	cmp	w0, 1
	bne	.L89
	ldr	x0, .LC51
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 290816
	ldr	w0, [x0, 1120]
	cbz	w0, .L97
.L91:
	ldr	x3, .LC52
	mov	x2, 20
	mov	x1, x21
	add	x0, x19, 36
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L87:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L97:
	mov	x0, x19
	bl	FSP_ClearContext
	b	.L91
	.p2align 3
.L89:
	ldr	x3, .LC50
	mov	w2, 572
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L87
	.p2align 3
.L95:
	ldr	x3, .LC44
	mov	w2, 569
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L87
.L96:
	ldr	x3, .LC47
	mov	w2, 570
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L87
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	3
.LC44:
	.xword	.LC8
	.align	3
.LC45:
	.xword	.LC2
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR0
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC51:
	.xword	s_pstVfmwChan
	.align	3
.LC52:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigFrameBuf
	.type	FSP_ConfigFrameBuf, %function
FSP_ConfigFrameBuf:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	mov	w27, w0
	mov	x0, x30
	mov	w25, w1
	mov	w26, w2
	mov	x20, x3
	bl	_mcount
	ldr	x19, .LC53
	mov	x2, 1232
	ldr	x22, .LC54
	mov	w1, 0
	ldr	x3, [x19, 96]
	add	x0, x22, 256
	blr	x3
	cmp	w27, 31
	bhi	.L152
	ldr	x21, [x22, w27, sxtw 3]
	cbz	x21, .L153
	ldr	x24, .LC58
	ldr	x0, [x24, w27, sxtw 3]
	add	x1, x0, 294912
	ldr	w1, [x1, 1180]
	cmp	w1, 1
	beq	.L102
	mov	w0, w27
	add	x23, x21, 36
	bl	VCTRL_GetChanCapLevel
	cmp	w0, 32
	bls	.L154
	ldrsb	w1, [x21, 36]
	cmp	w1, 1
	bne	.L155
	ldp	w4, w5, [x23, 4]
	ldr	x0, [x24, w27, sxtw 3]
	mul	w1, w4, w5
.L133:
	ldp	w2, w3, [x0, 144]
	mul	w6, w2, w3
	cmp	w6, w1
	blt	.L156
.L107:
	ldr	w1, [x0, 1448]
	ldrsb	w28, [x23, 1]
	cmp	w1, 1
	beq	.L157
.L108:
	add	x0, x0, 290816
	ldr	w1, [x0, 1128]
	cmp	w28, w1
	beq	.L110
	mov	w1, 1
	str	w1, [x0, 1144]
.L111:
	ldr	x1, .LC67
	ldr	x8, [x1, 128]
	ldrsb	w1, [x23, 1]
	str	w1, [x0, 1128]
	cbz	x8, .L112
	ldrsb	w6, [x21, 36]
	mov	w1, w26
	ldrsb	w4, [x23, 3]
	mov	w0, w25
	ldp	w2, w3, [x23, 4]
	add	x25, x22, 256
	mov	w7, w27
	mov	w5, 32
	str	x25, [sp]
	mov	w26, 32
	blr	x8
	ldr	x1, [x24, w27, sxtw 3]
	add	x1, x1, 290816
	ldr	w1, [x1, 3512]
	cmp	w1, 32
	csel	w1, w1, w26, le
	cmp	w0, 2
	strb	w1, [x21, 5]
	beq	.L158
	cbnz	w0, .L115
	ldr	w0, [x25, 48]
	strb	w0, [x21, 2]
	mov	w0, 31
	ldr	x1, .LC71
	ldr	x2, [x24, w27, sxtw 3]
	strb	wzr, [x2, 1520]
	str	wzr, [x2, 1496]
	bl	dprint_vfmw
	ldr	w4, [x25, 48]
	cmp	w28, w4
	bgt	.L159
	strb	wzr, [x21, 4]
	ldr	w0, [x25, 48]
	cmp	w0, 32
	csel	w0, w0, w26, le
	strb	w0, [x21, 3]
	mov	w0, 8
	ldr	x1, [x19, 24]
	blr	x1
	ldr	w0, [x25, 60]
	cbz	w0, .L160
	ldr	w13, [x21, 16]
	sxtw	x4, w27
	ldp	w5, w6, [x23, 4]
	ldp	w11, w10, [x25, 4]
	ldr	w9, [x25, 12]
	mov	x2, x25
	mov	w3, 0
	mov	w7, 4
	mov	w8, 1
	.p2align 2
.L123:
	uxtw	x12, w13
	uxtw	x0, w3
	lsl	x1, x12, 2
	lsl	x15, x0, 2
	sub	x1, x1, x12
	sub	x15, x15, x0
	lsl	x1, x1, 2
	add	x0, x0, 20
	sub	x1, x1, x12
	add	x15, x2, x15, lsl 2
	ldr	w17, [x2, 20]
	add	x1, x21, x1, lsl 3
	ldr	w18, [x2, x0, lsl 2]
	add	x0, x1, 20480
	ldr	w1, [x15, 468]
	ldr	w16, [x15, 464]
	ldr	x14, [x24, x4, lsl 3]
	str	w1, [x0, 1436]
	add	x1, x0, 1280
	str	w16, [x0, 1432]
	strb	wzr, [x0, 1425]
	strb	wzr, [x0, 1426]
	str	w13, [x0, 1428]
	ldr	w15, [x2, 32]
	stp	w18, w11, [x1, 164]
	stp	w10, w17, [x1, 172]
	str	w15, [x0, 1464]
	add	x15, x14, 294912
	ldr	w1, [x2, 16]
	ldr	w16, [x2, 28]
	str	w16, [x0, 1460]
	str	w1, [x0, 1472]
	ldr	w17, [x2, 36]
	ldp	w16, w1, [x2, 40]
	str	w9, [x0, 1468]
	str	w5, [x0, 1476]
	str	w6, [x0, 1480]
	str	w17, [x0, 1484]
	str	w16, [x0, 1488]
	str	w1, [x0, 1492]
	ldr	w0, [x15, 1172]
	cbnz	w0, .L120
	ldr	w0, [x15, 1168]
	cbz	w0, .L120
	ldr	x5, [x22, x4, lsl 3]
	mov	w1, 0
	ldr	w6, [x5, 16]
	lsl	x0, x6, 2
	sub	x0, x0, x6
	lsl	x0, x0, 2
	sub	x0, x0, x6
	add	x5, x5, x0, lsl 3
	add	x0, x5, 20480
	ldr	w6, [x0, 1432]
	b	.L122
	.p2align 3
.L121:
	ldr	w0, [x15, 1168]
	cmp	w1, w0
	bcs	.L161
.L122:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 16384
	add	x0, x0, 2088
	add	x0, x14, x0, lsl 4
	ldr	w0, [x0, 4]
	cmp	w6, w0
	bne	.L121
	add	x0, x5, 20480
	strb	w7, [x0, 1426]
	ldr	w0, [x15, 1168]
	cmp	w1, w0
	bcc	.L122
.L161:
	ldr	w13, [x21, 16]
	ldp	w5, w6, [x23, 4]
	uxtw	x12, w13
.L120:
	lsl	x0, x12, 2
	add	w13, w13, 1
	sub	x0, x0, x12
	add	w3, w3, 1
	lsl	x0, x0, 2
	sub	x0, x0, x12
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	str	w8, [x0, 1508]
	str	w13, [x21, 16]
	ldr	w0, [x2, 60]
	cmp	w0, w3
	bhi	.L123
.L119:
	add	x8, x22, 256
	ldr	w0, [x8, 68]
	cbz	w0, .L128
	ldr	w3, [x21, 24]
	mov	w2, 0
	.p2align 2
.L127:
	uxtw	x4, w3
	uxtw	x7, w2
	lsl	x0, x4, 2
	lsl	x1, x7, 2
	sub	x0, x0, x4
	sub	x1, x1, x7
	lsl	x0, x0, 2
	add	w3, w3, 1
	sub	x0, x0, x4
	add	x1, x8, x1, lsl 2
	add	w2, w2, 1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	ldr	w1, [x1, 848]
	str	w1, [x0, 1440]
	str	w3, [x21, 24]
	ldr	w0, [x8, 68]
	cmp	w0, w2
	bhi	.L127
.L128:
	add	x3, x22, 256
	ldr	w0, [x3, 56]
	mov	w1, 32
	cmp	w0, w1
	csel	w0, w0, w1, le
	strb	w0, [x21, 5]
	ldr	w0, [x3, 64]
	cbz	w0, .L126
	ldr	w2, [x21, 20]
	mov	w1, 0
	mov	w7, 1
	.p2align 2
.L129:
	add	x0, x21, x2, uxtw 3
	add	x4, x3, x1, uxtw 3
	add	x0, x0, 24576
	add	w2, w2, 1
	add	w1, w1, 1
	ldr	w4, [x4, 208]
	strb	wzr, [x0, 2965]
	strb	w7, [x0, 2964]
	str	w4, [x0, 2960]
	str	w2, [x21, 20]
	ldr	w0, [x3, 64]
	cmp	w0, w1
	bhi	.L129
.L126:
	ldr	w1, [x22, 308]
	add	x4, x21, 20480
	str	w1, [x21, 8]
	mov	w2, 1
	str	wzr, [x21, 60]
	ldr	w3, [x22, 260]
	ldr	w7, [x4, 1432]
	ldr	w4, [x22, 264]
	stp	w3, w4, [x21, 80]
	stp	w5, w6, [x21, 108]
	ldr	w3, [x22, 284]
	ldr	w5, [x22, 276]
	ldr	w0, [x22, 300]
	stp	w5, w3, [x21, 88]
	ldr	w4, [x22, 292]
	ldr	w5, [x22, 288]
	ldr	w3, [x22, 296]
	ldr	w1, [x22, 256]
	str	w0, [x21, 124]
	mov	w0, 8
	strb	wzr, [x21, 57]
	strb	wzr, [x21, 58]
	str	w7, [x21, 64]
	str	w2, [x21, 140]
	str	w4, [x21, 116]
	str	w5, [x21, 96]
	str	w3, [x21, 120]
	str	w1, [x20]
	ldr	x1, [x19, 32]
	blr	x1
	mov	w0, 0
.L138:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L154:
	uxtw	x2, w0
	lsl	x1, x2, 3
	sub	x1, x1, x2
	ldr	x2, .LC59
	lsl	x1, x1, 2
	add	x6, x2, x1
	ldp	w4, w5, [x23, 4]
	ldr	w3, [x2, x1]
	ldr	w2, [x6, 4]
	mul	w1, w4, w5
	mul	w6, w3, w2
	cmp	w1, w6
	ccmp	w0, 25, 4, gt
	beq	.L148
	ldrsb	w6, [x21, 36]
	cmp	w6, 1
	bne	.L132
.L148:
	ldr	x0, [x24, w27, sxtw 3]
	ldp	w2, w3, [x0, 144]
	mul	w6, w2, w3
	cmp	w6, w1
	bge	.L107
.L156:
	ldr	x1, .LC65
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, .LC66
	ldr	x4, [x0]
	cbz	x4, .L134
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w27
	blr	x4
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L102:
	add	x23, x21, 36
	ldp	w4, w5, [x23, 4]
	mul	w1, w4, w5
	b	.L133
	.p2align 3
.L158:
	ldr	w1, [x25, 48]
	add	sp, x29, 0
	strb	w1, [x21, 2]
	mov	w2, 1
	ldr	x1, [x24, w27, sxtw 3]
	strb	w2, [x1, 1520]
	str	w2, [x1, 1496]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L134:
	mov	w0, -1
	b	.L138
	.p2align 3
.L157:
	add	x1, x0, 262144
	ldr	w1, [x1, 2032]
	tst	w1, -3
	beq	.L108
	cmp	w1, 1
	mov	w0, 0
	beq	.L138
	strb	wzr, [x21, 2]
	mov	w0, 31
	ldr	x1, .LC69
	ldr	x2, [x24, w27, sxtw 3]
	add	x2, x2, 262144
	ldr	w2, [x2, 2032]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L138
	.p2align 3
.L112:
	ldr	w1, [x0, 3512]
	mov	w2, 32
	mov	w0, -1
	cmp	w1, w2
	csel	w1, w1, w2, le
	strb	w1, [x21, 5]
.L115:
	strb	wzr, [x21, 2]
	mov	w2, w0
	ldr	x1, .LC73
	mov	w0, 0
	ldr	x3, [x24, w27, sxtw 3]
	strb	wzr, [x3, 1520]
	str	wzr, [x3, 1496]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L138
	.p2align 3
.L110:
	str	wzr, [x0, 1144]
	b	.L111
.L132:
	ldr	x1, .LC63
	mov	w6, w5
	mov	w5, w4
	mov	w4, w2
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
.L106:
	strb	wzr, [x21, 2]
	mov	w0, -1
	b	.L138
.L160:
	ldp	w5, w6, [x23, 4]
	b	.L119
.L155:
	ldr	x1, .LC61
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	b	.L106
.L152:
	ldr	x3, .LC55
	mov	w2, 601
	ldr	x1, .LC56
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L138
.L159:
	ldr	x1, .LC75
	mov	w3, w28
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L138
.L153:
	ldr	x3, .LC57
	mov	w2, 602
	ldr	x1, .LC56
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L138
	.size	FSP_ConfigFrameBuf, .-FSP_ConfigFrameBuf
	.align	3
.LC53:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC54:
	.xword	.LANCHOR0
	.align	3
.LC55:
	.xword	.LC8
	.align	3
.LC56:
	.xword	.LC2
	.align	3
.LC57:
	.xword	.LC17
	.align	3
.LC58:
	.xword	s_pstVfmwChan
	.align	3
.LC59:
	.xword	CapItem
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC66:
	.xword	g_event_report
	.align	3
.LC67:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetOccupiedNum
	.type	FSP_GetOccupiedNum, %function
FSP_GetOccupiedNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cmp	w19, 1088
	mov	w0, 1
	bgt	.L163
	ldr	x1, .LC77
	mov	w0, 4
	ldr	x1, [x1, w20, sxtw 3]
	add	x1, x1, 294912
	ldr	w1, [x1, 1228]
	cmp	w1, wzr
	csinc	w0, w0, wzr, eq
.L163:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetOccupiedNum, .-FSP_GetOccupiedNum
	.align	3
.LC77:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsDecFsAvailable
	.type	FSP_IsDecFsAvailable, %function
FSP_IsDecFsAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 84]
	cmp	w0, 1
	beq	.L170
	mov	w0, 0
.L167:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L170:
	ldr	w1, [x19]
	mov	w0, 0
	tst	w1, 16776960
	bne	.L167
	mov	x1, x19
	mov	w0, w20
	bl	FSP_IsDecFsAvailable.part.4
	uxtb	w0, w0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsDecFsAvailable, .-FSP_IsDecFsAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsPmvAvailable
	.type	FSP_IsPmvAvailable, %function
FSP_IsPmvAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsPmvAvailable, .-FSP_IsPmvAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, 31
	bhi	.L213
	ldr	x23, .LC80
	ldr	x21, [x23, w22, sxtw 3]
	cbz	x21, .L214
	ldrsb	w0, [x21, 3]
	cbnz	w0, .L176
.L189:
	mov	w0, 1
.L211:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L176:
	mov	w0, w22
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L177
	ldrsb	w24, [x21, 3]
	cmp	w24, wzr
	ble	.L184
	add	x19, x21, 20480
	mov	w20, 0
	add	x19, x19, 1424
	b	.L183
	.p2align 3
.L181:
	add	w20, w20, 1
	add	x19, x19, 88
	cmp	w20, w24
	beq	.L184
.L183:
	ldr	w0, [x19, 84]
	cmp	w0, 1
	bne	.L181
	sxtw	x1, w20
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	ldr	w0, [x0, 1424]
	tst	w0, 16776960
	bne	.L181
	mov	x1, x19
	mov	w0, w22
	bl	FSP_IsDecFsAvailable.part.4
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L181
	cmp	w24, w20
	ble	.L184
.L185:
	mov	w0, w22
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L189
	ldrsb	w2, [x21, 5]
	cmp	w2, wzr
	ble	.L190
	add	x0, x21, 24576
	ldrh	w0, [x0, 2964]
	cmp	w0, 1
	beq	.L189
	mov	w1, 0
	b	.L191
	.p2align 3
.L192:
	add	x0, x21, x0, lsl 3
	ldrh	w0, [x0, 4]
	cmp	w0, 1
	beq	.L189
.L191:
	add	w1, w1, 1
	cmp	w1, w2
	sxtw	x0, w1
	add	x0, x0, 3442
	bne	.L192
.L193:
	mov	w0, w22
	bl	VCTRL_GetVidStd
	cbz	w0, .L189
	mov	w0, w22
	bl	VCTRL_GetVidStd
	cmp	w0, 16
	beq	.L189
	mov	w0, w22
	bl	VCTRL_GetVidStd
	cmp	w0, 15
	beq	.L189
	.p2align 2
.L184:
	ldr	x0, [x23, w22, sxtw 3]
	cbz	x0, .L215
	mov	w0, 0
.L216:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L177:
	ldr	x0, .LC82
	add	x19, x21, 20480
	add	x19, x19, 1424
	mov	w20, 0
	ldr	x0, [x0, w22, sxtw 3]
	add	x0, x0, 593920
	ldr	w24, [x0, 928]
	b	.L188
	.p2align 3
.L186:
	add	w20, w20, 1
	add	x19, x19, 88
	cmp	w20, 32
	beq	.L184
.L188:
	ldr	w0, [x19, 84]
	cmp	w0, 1
	bne	.L186
	sxtw	x1, w20
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	ldr	w0, [x0, 1424]
	tst	w0, 16776960
	bne	.L186
	mov	x1, x19
	mov	w0, w22
	bl	FSP_IsDecFsAvailable.part.4
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L186
	ldr	w0, [x19, 12]
	cmp	w24, w0
	bne	.L186
	cmp	w20, 31
	ble	.L185
	b	.L184
	.p2align 3
.L215:
	ldr	x1, .LC84
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L216
.L190:
	bne	.L184
	b	.L193
	.p2align 3
.L213:
	ldr	x3, .LC78
	mov	w2, 818
	ldr	x1, .LC79
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L211
.L214:
	ldr	x3, .LC81
	mov	w2, 819
	ldr	x1, .LC79
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L211
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	3
.LC78:
	.xword	.LC8
	.align	3
.LC79:
	.xword	.LC2
	.align	3
.LC80:
	.xword	.LANCHOR0
	.align	3
.LC81:
	.xword	.LC17
	.align	3
.LC82:
	.xword	s_pstVfmwChan
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w25, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cmp	w25, 31
	bhi	.L253
	ldr	x23, .LC87
	ldr	x0, [x23, w25, sxtw 3]
	cbz	x0, .L254
	ldr	x22, .LC89
	mov	w0, 3
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x20, [x23, w25, sxtw 3]
	mov	w1, 0
	add	x0, x20, 144
	.p2align 2
.L223:
	ldrsb	w2, [x0]
	cbnz	w2, .L221
	ldrsb	w2, [x0, 1]
	cbz	w2, .L255
.L221:
	add	w1, w1, 1
	add	x0, x0, 680
	cmp	w1, 32
	bne	.L223
.L224:
	ldr	x1, .LC91
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
.L250:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L255:
	sxtw	x24, w1
	lsl	x19, x24, 5
	add	x19, x19, x24, lsl 3
	add	x19, x19, x19, lsl 4
	add	x0, x20, x19
	add	x19, x19, 144
	adds	x19, x20, x19
	strb	w1, [x0, 147]
	strb	wzr, [x0, 146]
	beq	.L224
	str	wzr, [x0, 152]
	stp	xzr, xzr, [x0, 176]
	cbnz	w21, .L225
	add	x1, x20, 24576
	add	x2, x20, 56
	stp	x2, x2, [x0, 176]
	mov	w2, 1
	ldr	w1, [x1, 2960]
	str	w1, [x0, 152]
	ldrb	w1, [x20, 5]
	strb	w2, [x0, 146]
	sub	w1, w1, #1
	strb	w1, [x0, 148]
.L226:
	lsl	x0, x24, 5
	mov	w1, 1
	add	x0, x0, x24, lsl 3
	mov	w2, 1
	add	x19, x19, 48
	add	x0, x0, x0, lsl 4
	add	x21, x20, x0
	add	x0, x0, 192
	add	x0, x20, x0
	ldr	x3, [x21, 184]
	strb	w1, [x21, 145]
	strb	w1, [x3, 2]
	str	w2, [x21, 168]
	mov	x2, 632
	ldr	x3, [x21, 176]
	ldr	w1, [x20, 12]
	str	w1, [x21, 164]
	str	w1, [x3, 72]
	ldr	x1, [x21, 184]
	ldr	w3, [x21, 164]
	str	w3, [x1, 72]
	ldr	w1, [x20, 12]
	add	w1, w1, 1
	str	w1, [x20, 12]
	mov	w1, 0
	ldr	x3, [x22, 96]
	ldp	x20, x23, [x21, 176]
	blr	x3
	ldrsb	w0, [x21, 147]
	str	w0, [x19, 148]
	ldr	w0, [x20, 52]
	str	w0, [x19, 68]
	ldr	w0, [x20, 56]
	str	w0, [x19, 72]
	ldr	w0, [x23, 24]
	str	w0, [x19, 112]
	ldr	w0, [x23, 28]
	str	w0, [x19, 116]
	ldr	w0, [x23, 44]
	str	w0, [x19, 136]
	ldr	w0, [x23, 48]
	str	w0, [x19, 140]
	ldr	w0, [x20, 8]
	str	w0, [x19, 36]
	bl	MEM_Phy2Vir
	str	x0, [x19, 504]
	ldr	w1, [x19, 36]
	ldr	w0, [x20, 60]
	add	w0, w1, w0
	str	w0, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w3, [x19, 36]
	ldr	w1, [x23, 8]
	str	w1, [x19, 20]
	ldr	x2, [x19, 504]
	ldr	w0, [x23, 60]
	add	w0, w1, w0
	str	w0, [x19, 24]
	ldr	w4, [x23, 24]
	add	w1, w4, w1
	str	w1, [x19, 28]
	ldr	w1, [x23, 28]
	add	w0, w1, w0
	str	w0, [x19, 32]
	ldr	w0, [x20, 32]
	str	w0, [x19, 144]
	ldr	w0, [x20, 36]
	add	w0, w0, w3
	str	w0, [x19, 44]
	ldrsw	x0, [x20, 36]
	add	x0, x0, x2
	str	x0, [x19, 528]
	ldp	w1, w0, [x20, 36]
	add	w0, w1, w0
	add	w3, w0, w3
	str	w3, [x19, 48]
	ldpsw	x1, x0, [x20, 36]
	add	x0, x1, x0
	add	x2, x0, x2
	str	x2, [x19, 536]
	ldr	w0, [x20, 20]
	str	w0, [x19, 212]
	ldr	w0, [x20, 20]
	bl	MEM_Phy2Vir
	str	x0, [x19, 520]
	ldr	w0, [x20, 16]
	str	w0, [x19, 424]
	bl	MEM_Phy2Vir
	str	x0, [x19, 432]
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	ldr	x27, [sp, 80]
	ldrsb	w0, [x21, 147]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L225:
	mov	w0, w25
	ldr	x26, [x23, w25, sxtw 3]
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L227
	ldrsb	w27, [x26, 3]
	cmp	w27, wzr
	ble	.L228
	add	x21, x26, 20480
	mov	w23, 0
	add	x21, x21, 1424
	b	.L230
	.p2align 3
.L229:
	add	w23, w23, 1
	add	x21, x21, 88
	cmp	w23, w27
	beq	.L228
.L230:
	ldr	w0, [x21, 84]
	cmp	w0, 1
	bne	.L229
	sxtw	x1, w23
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x26, x0, lsl 3
	add	x0, x0, 20480
	ldr	w0, [x0, 1424]
	tst	w0, 16776960
	bne	.L229
	mov	x1, x21
	mov	w0, w25
	bl	FSP_IsDecFsAvailable.part.4
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L229
	str	x21, [x19, 32]
.L228:
	lsl	x0, x24, 5
	add	x0, x0, x24, lsl 3
	add	x0, x0, x0, lsl 4
	add	x21, x20, x0
	ldr	x1, [x21, 176]
	cbz	x1, .L256
	ldrsb	w0, [x20, 5]
	cmp	w0, wzr
	ble	.L234
	mov	w0, w25
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L235
	ldrsb	w2, [x20, 5]
	add	x4, x20, 24576
	cmp	w2, wzr
	ble	.L236
	ldrh	w0, [x4, 2964]
	cmp	w0, 1
	beq	.L237
	mov	w1, 0
	b	.L238
	.p2align 3
.L240:
	add	x0, x20, x0, lsl 3
	ldrh	w3, [x0, 4]
	cmp	w3, 1
	beq	.L257
.L238:
	add	w1, w1, 1
	cmp	w1, w2
	sxtw	x0, w1
	add	x0, x0, 3442
	bne	.L240
.L236:
	cmp	w2, wzr
	ldr	w5, [x20, 8]
	ble	.L242
.L239:
	sub	w2, w2, #1
	mov	x0, 27549
	add	x1, x4, 2965
	add	x0, x0, x2, uxtw 3
	add	x0, x20, x0
	.p2align 2
.L241:
	strb	wzr, [x1], 8
	cmp	x1, x0
	bne	.L241
.L242:
	lsl	x2, x24, 5
	ldr	x1, .LC97
	add	x2, x2, x24, lsl 3
	mov	w0, 0
	add	x2, x2, x2, lsl 4
	add	x21, x20, x2
	strb	wzr, [x21, 148]
	ldr	w2, [x4, 2960]
	stp	w2, w5, [x21, 152]
	bl	dprint_vfmw
	ldr	x1, [x21, 176]
	.p2align 2
.L234:
	lsl	x0, x24, 5
	add	x0, x0, x24, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	str	x1, [x0, 184]
	b	.L226
.L227:
	ldr	x0, .LC92
	add	x21, x26, 20480
	add	x21, x21, 1424
	mov	w23, 0
	ldr	x0, [x0, w25, sxtw 3]
	add	x0, x0, 593920
	ldr	w27, [x0, 928]
	b	.L232
	.p2align 3
.L231:
	add	w23, w23, 1
	add	x21, x21, 88
	cmp	w23, 32
	beq	.L228
.L232:
	ldr	w0, [x21, 84]
	cmp	w0, 1
	bne	.L231
	sxtw	x1, w23
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x26, x0, lsl 3
	add	x0, x0, 20480
	ldr	w0, [x0, 1424]
	tst	w0, 16776960
	bne	.L231
	mov	x1, x21
	mov	w0, w25
	bl	FSP_IsDecFsAvailable.part.4
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L231
	ldr	w0, [x21, 12]
	cmp	w27, w0
	bne	.L231
	str	x21, [x19, 32]
	b	.L228
.L257:
	lsl	x3, x24, 5
	cmp	w1, w2
	add	x3, x3, x24, lsl 3
	add	x3, x3, x3, lsl 4
	add	x3, x20, x3
	strb	w1, [x3, 148]
	ldr	w0, [x0]
	str	w0, [x3, 152]
	ldr	w5, [x20, 8]
	str	w5, [x3, 156]
	bge	.L239
.L243:
	lsl	x0, x24, 5
	add	x0, x0, x24, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldr	x1, [x0, 176]
	b	.L234
.L235:
	add	x0, x20, 24576
	strb	wzr, [x21, 148]
	ldr	x1, [x21, 176]
	ldr	w0, [x0, 2960]
	str	w0, [x21, 152]
	ldr	w0, [x20, 8]
	str	w0, [x21, 156]
	b	.L234
.L253:
	ldr	x3, .LC85
	mov	w2, 913
	ldr	x1, .LC86
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L250
.L254:
	ldr	x3, .LC88
	mov	w2, 914
	ldr	x1, .LC86
	bl	dprint_vfmw
	mov	w0, -1
	b	.L250
.L237:
	strb	wzr, [x21, 148]
	ldr	w0, [x4, 2960]
	str	w0, [x21, 152]
	ldr	w0, [x20, 8]
	str	w0, [x21, 156]
	b	.L243
.L256:
	ldr	x2, .LC93
	mov	w0, 0
	ldr	x1, .LC95
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
	b	.L250
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	3
.LC85:
	.xword	.LC8
	.align	3
.LC86:
	.xword	.LC2
	.align	3
.LC87:
	.xword	.LANCHOR0
	.align	3
.LC88:
	.xword	.LC17
	.align	3
.LC89:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC92:
	.xword	s_pstVfmwChan
	.align	3
.LC93:
	.xword	.LANCHOR1
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPhyFsNum
	.type	FSP_GetPhyFsNum, %function
FSP_GetPhyFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	w20, w1
	mov	w19, 0
	bl	_mcount
	ldr	x21, .LC98
	mov	w0, 3
	ldr	x1, [x21, 24]
	blr	x1
	ldr	x0, .LC99
	ldr	x2, [x0, w22, sxtw 3]
	add	x0, x2, 20480
	add	x2, x2, 24576
	add	x0, x0, 1508
	add	x3, x2, 228
	b	.L260
	.p2align 3
.L259:
	add	x0, x0, 88
	cmp	x0, x3
	beq	.L264
.L260:
	ldr	w2, [x0]
	cmp	w2, 1
	bne	.L259
	ldr	w1, [x0, -72]
	add	x0, x0, 88
	cmp	w1, w20
	ccmp	w20, wzr, 4, ne
	csinc	w19, w19, w19, ne
	cmp	x0, x3
	bne	.L260
.L264:
	ldr	x1, [x21, 32]
	mov	w0, 3
	blr	x1
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FSP_GetPhyFsNum, .-FSP_GetPhyFsNum
	.align	3
.LC98:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC99:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_RelsePhyFs
	.type	FSP_RelsePhyFs, %function
FSP_RelsePhyFs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	mov	w19, 0
	bl	_mcount
	ldr	x25, .LC100
	mov	w0, 3
	ldr	x1, [x25, 24]
	blr	x1
	ldr	x0, .LC101
	ldr	x1, [x0, w20, sxtw 3]
	add	x0, x1, 20480
	add	x0, x0, 1508
	b	.L269
	.p2align 3
.L266:
	add	w19, w19, 1
	add	x0, x0, 88
	cmp	w19, 32
	beq	.L293
.L269:
	ldr	w2, [x0]
	cmp	w2, 1
	bne	.L266
	ldrsb	w2, [x0, -83]
	cbnz	w2, .L266
	ldrsb	w2, [x0, -82]
	cbnz	w2, .L266
	ldr	w2, [x0, -72]
	cmp	w2, w21
	beq	.L266
	sxtw	x24, w19
	lsl	x0, x24, 2
	sub	x0, x0, x24
	lsl	x0, x0, 2
	sub	x24, x0, x24
	add	x1, x1, x24, lsl 3
	add	x24, x1, 20480
	ldr	w23, [x24, 1432]
	mov	w0, w23
	bl	MEM_Phy2Vir
	ldr	w21, [x24, 1436]
	cmp	w19, 31
	mov	x22, x0
	bgt	.L293
	mov	x1, x0
	str	wzr, [x24, 1508]
	mov	w2, w21
	mov	w0, w23
	uxtw	x19, w19
	bl	MEM_DelMemRecord
	ldr	x24, .LC102
	lsl	x1, x19, 6
	add	x19, x1, x19, lsl 3
	ldr	x0, [x24, w20, sxtw 3]
	add	x0, x0, x19
	add	x0, x0, 290816
	ldr	w1, [x0, 1160]
	cmp	w1, 255
	beq	.L271
	ldr	w26, [x0, 1216]
	mov	w0, w26
	bl	MEM_Phy2Vir
	mov	x1, x0
	ldr	x2, [x24, w20, sxtw 3]
	mov	w0, w26
	add	x19, x2, x19
	add	x2, x19, 290816
	ldr	w2, [x2, 1172]
	bl	MEM_DelMemRecord
.L271:
	ldr	x1, [x25, 32]
	mov	w0, 3
	blr	x1
	ldr	x1, [x25, 24]
	mov	w0, 8
	blr	x1
	ldr	x4, [x24, w20, sxtw 3]
	mov	w1, 0
	add	x2, x4, 290816
	add	x0, x2, 3928
	b	.L275
	.p2align 3
.L273:
	add	w1, w1, 1
	add	x0, x0, 12
	cmp	w1, 32
	beq	.L276
.L275:
	ldrb	w3, [x0]
	cmp	w3, 1
	bne	.L273
	ldr	w3, [x0, -8]
	cmp	w23, w3
	bne	.L273
	cmp	w1, 31
	bgt	.L276
	sxtw	x1, w1
	lsl	x3, x1, 2
	sub	x1, x3, x1
	add	x1, x2, x1, lsl 2
	strb	wzr, [x1, 3928]
.L276:
	add	x0, x2, 1152
	mov	w19, 0
	b	.L279
	.p2align 3
.L277:
	add	w19, w19, 1
	add	x0, x0, 72
	cmp	w19, 32
	beq	.L280
.L279:
	ldr	w1, [x0]
	cmp	w1, 255
	beq	.L277
	ldr	w1, [x0, 32]
	cmp	w23, w1
	bne	.L277
	cmp	w19, 31
	bgt	.L280
	sxtw	x0, w19
	ldr	x2, .LC103
	lsl	x1, x0, 6
	add	x0, x1, x0, lsl 3
	mov	w1, 255
	add	x0, x4, x0
	ldr	x4, [x2]
	add	x0, x0, 290816
	str	w1, [x0, 1152]
	cbz	x4, .L280
	uxtw	x23, w23
	uxtw	x21, w21
	mov	w3, 24
	add	x2, x29, 88
	mov	w1, 123
	mov	w0, w20
	stp	x23, x22, [x29, 88]
	str	x21, [x29, 104]
	blr	x4
.L280:
	ldr	x1, [x25, 32]
	mov	w0, 8
	blr	x1
	cmp	w19, 31
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	csetm	w0, gt
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L293:
	ldr	x1, [x25, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.size	FSP_RelsePhyFs, .-FSP_RelsePhyFs
	.align	3
.LC100:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	s_pstVfmwChan
	.align	3
.LC103:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L302
	cmp	w19, 31
	bhi	.L303
	ldr	x0, .LC108
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L304
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x2, x0
	ldr	w1, [x0, 168]
	cmp	w1, 2
	beq	.L305
.L296:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L305:
	ldrsb	w0, [x0, 148]
	uxtb	w1, w0
	cmp	w1, 31
	bhi	.L301
	sxtw	x0, w0
	add	x0, x0, 3442
	add	x0, x2, x0, lsl 3
	strb	wzr, [x0, 5]
.L301:
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x2, x19
	str	wzr, [x19, 168]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L302:
	ldr	x3, .LC104
	mov	w2, 1153
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L303:
	ldr	x3, .LC107
	mov	w2, 1154
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L304:
	ldr	x3, .LC109
	mov	w2, 1155
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	b	.L296
	.size	FSP_RemovePmv, .-FSP_RemovePmv
	.align	3
.LC104:
	.xword	.LC8
	.align	3
.LC105:
	.xword	.LC2
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	.LANCHOR0
	.align	3
.LC109:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetRef
	.type	FSP_SetRef, %function
FSP_SetRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	mov	w21, w2
	bl	_mcount
	cmp	w20, 31
	bhi	.L335
	cmp	w19, 31
	bhi	.L336
	ldr	x0, .LC113
	ldr	x20, [x0, w20, sxtw 3]
	cbz	x20, .L337
	lsl	x0, x19, 5
	sxtb	w1, w21
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldrsb	w2, [x0, 146]
	strb	w1, [x0, 144]
	cbnz	w2, .L306
	ldr	x2, [x0, 176]
	cbz	x2, .L312
	ldr	w0, [x0, 164]
	ldr	w3, [x2, 72]
	cmp	w3, w0
	beq	.L338
.L312:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldrsb	w3, [x0, 148]
	uxtb	w1, w3
	cmp	w1, 31
	bhi	.L313
	cmp	w21, 1
	beq	.L339
	cbnz	w21, .L316
	ldr	w1, [x0, 168]
	cmp	w1, 2
	beq	.L340
.L317:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldr	x0, [x0, 184]
	cbz	x0, .L326
	ldrsb	w1, [x0, 2]
	cmp	w1, 1
	beq	.L341
.L326:
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x20, x20, x19
	str	xzr, [x20, 176]
.L306:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L335:
	ldr	x3, .LC110
	mov	w2, 1178
	ldr	x1, .LC111
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L339:
	ldr	w1, [x0, 168]
	cmp	w1, 1
	beq	.L342
.L315:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldr	x1, [x0, 184]
	cbz	x1, .L306
.L321:
	lsl	x0, x19, 5
	ldr	w3, [x1, 72]
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldr	w2, [x0, 164]
	cmp	w3, w2
	ccmp	w21, 1, 0, eq
	beq	.L343
.L318:
	cbz	w21, .L326
.L334:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L336:
	ldr	x3, .LC112
	mov	w2, 1179
	ldr	x1, .LC111
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L313:
	ldr	x1, .LC116
	mov	w2, 1232
	mov	w0, 0
	bl	dprint_vfmw
	cbz	w21, .L317
	b	.L315
	.p2align 3
.L338:
	strb	w1, [x2, 1]
	b	.L312
	.p2align 3
.L342:
	sxtw	x1, w3
	mov	w2, 2
	add	x1, x1, 3442
	add	x1, x20, x1, lsl 3
	strb	w21, [x1, 5]
	str	w2, [x0, 168]
.L316:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x20, x0
	ldr	x1, [x0, 184]
	cbnz	x1, .L321
	cbz	w21, .L326
	b	.L334
	.p2align 3
.L343:
	ldrsb	w2, [x1, 2]
	cmp	w2, 1
	bne	.L318
	mov	w2, 2
	strb	w2, [x1, 2]
	strb	w2, [x0, 145]
	cbz	w21, .L326
	b	.L334
	.p2align 3
.L341:
	strb	wzr, [x0, 2]
	b	.L326
	.p2align 3
.L340:
	sxtw	x1, w3
	add	x1, x1, 3442
	add	x1, x20, x1, lsl 3
	strb	wzr, [x1, 5]
	str	wzr, [x0, 152]
	str	wzr, [x0, 168]
	b	.L317
	.p2align 3
.L337:
	ldr	x3, .LC114
	mov	w2, 1180
	ldr	x1, .LC111
	mov	w0, 0
	bl	dprint_vfmw
	b	.L306
	.size	FSP_SetRef, .-FSP_SetRef
	.align	3
.LC110:
	.xword	.LC8
	.align	3
.LC111:
	.xword	.LC2
	.align	3
.LC112:
	.xword	.LC106
	.align	3
.LC113:
	.xword	.LANCHOR0
	.align	3
.LC114:
	.xword	.LC17
	.align	3
.LC116:
	.xword	.LC115
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetRef
	.type	FSP_GetRef, %function
FSP_GetRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L349
	cmp	w19, 31
	bhi	.L350
	ldr	x0, .LC122
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L351
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x0, x19
	ldrsb	w0, [x19, 144]
.L346:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L349:
	ldr	x3, .LC118
	mov	w2, 1264
	ldr	x1, .LC119
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L346
	.p2align 3
.L350:
	ldr	x3, .LC121
	mov	w2, 1265
	ldr	x1, .LC119
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L346
.L351:
	ldr	x3, .LC124
	mov	w2, 1266
	ldr	x1, .LC119
	bl	dprint_vfmw
	mov	w0, -1
	b	.L346
	.size	FSP_GetRef, .-FSP_GetRef
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC119:
	.xword	.LC2
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC122:
	.xword	.LANCHOR0
	.align	3
.LC124:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetDisplay
	.type	FSP_SetDisplay, %function
FSP_SetDisplay:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	mov	w23, w2
	bl	_mcount
	cmp	w20, 31
	bhi	.L379
	cmp	w19, 31
	bhi	.L380
	ldr	x22, .LC128
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L381
	ldr	x24, .LC130
	sxtw	x21, w19
	mov	w0, 3
	lsl	x19, x21, 5
	add	x19, x19, x21, lsl 3
	mov	w25, w0
	ldr	x1, [x24, 24]
	add	x19, x19, x19, lsl 4
	blr	x1
	ldr	x22, [x22, w20, sxtw 3]
	cmp	w23, wzr
	add	x19, x22, x19
	csel	w1, wzr, w25, eq
	ldrsb	w0, [x19, 146]
	strb	w1, [x19, 145]
	cbnz	w0, .L365
	ldr	x1, [x19, 184]
	cbz	x1, .L365
	ldr	w3, [x1, 72]
	ldr	w2, [x19, 164]
	cmp	w3, w2
	bne	.L382
	cbnz	w23, .L361
	strb	wzr, [x19, 145]
	mov	w0, w20
	strb	wzr, [x1, 2]
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L383
.L363:
	lsl	x0, x21, 5
	add	x0, x0, x21, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x22, x0
	str	xzr, [x0, 184]
.L365:
	ldr	x1, [x24, 32]
	mov	w0, 3
	blr	x1
.L352:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L379:
	ldr	x3, .LC125
	mov	w2, 1279
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L361:
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L384
.L364:
	lsl	x0, x21, 5
	mov	w1, 3
	add	x0, x0, x21, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x22, x0
	ldr	x2, [x0, 184]
	strb	w1, [x0, 145]
	strb	w1, [x2, 2]
	b	.L365
	.p2align 3
.L380:
	ldr	x3, .LC127
	mov	w2, 1280
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L382:
	ldr	x1, .LC132
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x24, 32]
	mov	w0, w25
	blr	x1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L381:
	ldr	x3, .LC129
	mov	w2, 1281
	ldr	x1, .LC126
	bl	dprint_vfmw
	b	.L352
	.p2align 3
.L384:
	ldr	x0, [x19, 184]
	cbz	x0, .L364
	ldr	w1, [x0, 80]
	add	w1, w1, 1
	str	w1, [x0, 80]
	b	.L364
	.p2align 3
.L383:
	ldr	x0, [x19, 184]
	cbz	x0, .L363
	ldr	w1, [x0, 80]
	cbz	w1, .L363
	sub	w1, w1, #1
	str	w1, [x0, 80]
	ldr	x0, [x19, 184]
	ldr	w1, [x0, 80]
	cbz	w1, .L363
	mov	w1, 3
	strb	w1, [x0, 2]
	b	.L363
	.size	FSP_SetDisplay, .-FSP_SetDisplay
	.align	3
.LC125:
	.xword	.LC8
	.align	3
.LC126:
	.xword	.LC2
	.align	3
.LC127:
	.xword	.LC106
	.align	3
.LC128:
	.xword	.LANCHOR0
	.align	3
.LC129:
	.xword	.LC17
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearNotInVoQueue
	.type	FSP_ClearNotInVoQueue, %function
FSP_ClearNotInVoQueue:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L396
	cbz	x22, .L397
	ldr	x0, .LC137
	ldr	x19, [x0, w20, sxtw 3]
	cbz	x19, .L398
	add	x21, x19, 20480
	add	x19, x19, 192
	add	x21, x21, 1472
	b	.L391
	.p2align 3
.L390:
	add	x19, x19, 680
	cmp	x19, x21
	beq	.L399
.L391:
	ldr	w1, [x19, 148]
	mov	w0, w20
	mov	w2, 0
	bl	FSP_SetRef
	mov	x1, x19
	mov	x0, x22
	bl	IsImageInVoQueue
	cbz	w0, .L390
	ldr	w1, [x19, 148]
	mov	w2, 0
	mov	w0, w20
	add	x19, x19, 680
	bl	FSP_SetDisplay
	cmp	x19, x21
	bne	.L391
.L399:
	mov	w0, 0
.L387:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L396:
	ldr	x3, .LC133
	mov	w2, 546
	ldr	x1, .LC134
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L387
.L398:
	ldr	x3, .LC138
	mov	w2, 548
	ldr	x1, .LC134
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L387
.L397:
	ldr	x3, .LC136
	mov	w2, 547
	ldr	x1, .LC134
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L387
	.size	FSP_ClearNotInVoQueue, .-FSP_ClearNotInVoQueue
	.align	3
.LC133:
	.xword	.LC8
	.align	3
.LC134:
	.xword	.LC2
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC137:
	.xword	.LANCHOR0
	.align	3
.LC138:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDisplay
	.type	FSP_GetDisplay, %function
FSP_GetDisplay:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, .LC139
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L403
	sxtw	x1, w19
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 3
	add	x1, x1, x1, lsl 4
	add	x1, x0, x1
	ldrsb	w0, [x1, 145]
.L402:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L403:
	ldr	x3, .LC140
	mov	w2, 1354
	ldr	x1, .LC141
	bl	dprint_vfmw
	mov	w0, -1
	b	.L402
	.size	FSP_GetDisplay, .-FSP_GetDisplay
	.align	3
.LC139:
	.xword	.LANCHOR0
	.align	3
.LC140:
	.xword	.LC17
	.align	3
.LC141:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetStoreType
	.type	FSP_SetStoreType, %function
FSP_SetStoreType:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w22, w1
	sxtw	x19, w2
	mov	w20, w3
	bl	_mcount
	cmp	w21, 31
	bhi	.L412
	ldr	x0, .LC144
	ldr	x3, [x0, w21, sxtw 3]
	cbz	x3, .L413
	cbz	w22, .L414
	cmp	w22, 1
	bne	.L411
	ldrsb	w0, [x3, 4]
	cmp	w19, w0
	bge	.L411
	lsl	x2, x19, 2
	mov	w0, 0
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	add	x19, x3, x2, lsl 3
	add	x19, x19, 24576
	str	w20, [x19, 220]
.L406:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L414:
	ldrsb	w0, [x3, 3]
	cmp	w0, w19
	ble	.L411
	lsl	x2, x19, 2
	mov	w0, 0
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x19, x2, x19
	add	x19, x3, x19, lsl 3
	add	x19, x19, 20480
	str	w20, [x19, 1500]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L411:
	mov	w0, -1
	b	.L406
	.p2align 3
.L412:
	ldr	x3, .LC142
	mov	w2, 1367
	ldr	x1, .LC143
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L406
.L413:
	ldr	x3, .LC145
	mov	w2, 1368
	ldr	x1, .LC143
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L406
	.size	FSP_SetStoreType, .-FSP_SetStoreType
	.align	3
.LC142:
	.xword	.LC8
	.align	3
.LC143:
	.xword	.LC2
	.align	3
.LC144:
	.xword	.LANCHOR0
	.align	3
.LC145:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetStoreType
	.type	FSP_GetStoreType, %function
FSP_GetStoreType:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 31
	bhi	.L423
	ldr	x0, .LC148
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L424
	cbnz	w21, .L419
	ldrsb	w2, [x1, 3]
	mov	w0, 2
	cmp	w2, w20
	bgt	.L425
.L417:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L423:
	ldr	x3, .LC146
	mov	w2, 1397
	ldr	x1, .LC147
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L419:
	cmp	w21, 1
	mov	w0, 2
	bne	.L417
	ldrsb	w2, [x1, 4]
	cmp	w20, w2
	bge	.L417
	lsl	x0, x20, 2
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	add	x0, x1, x0, lsl 3
	add	x0, x0, 24576
	ldr	w0, [x0, 220]
	b	.L417
	.p2align 3
.L425:
	lsl	x0, x20, 2
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x1, x1, x20, lsl 3
	add	x1, x1, 20480
	ldr	w0, [x1, 1500]
	b	.L417
	.p2align 3
.L424:
	ldr	x3, .LC149
	mov	w2, 1398
	ldr	x1, .LC147
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L417
	.size	FSP_GetStoreType, .-FSP_GetStoreType
	.align	3
.LC146:
	.xword	.LC8
	.align	3
.LC147:
	.xword	.LC2
	.align	3
.LC148:
	.xword	.LANCHOR0
	.align	3
.LC149:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearLogicFs
	.type	FSP_ClearLogicFs, %function
FSP_ClearLogicFs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	ccmp	w20, 31, 2, ls
	bhi	.L426
	ldr	x21, .LC150
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L426
	mov	w2, 0
	mov	w1, w20
	mov	w0, w19
	bl	FSP_SetRef
	sxtw	x1, w20
	ldr	x2, [x21, w19, sxtw 3]
	lsl	x0, x1, 5
	add	x0, x0, x1, lsl 3
	add	x0, x0, x0, lsl 4
	add	x0, x2, x0
	ldrsb	w0, [x0, 145]
	cmp	w0, 3
	beq	.L426
	mov	w2, 0
	mov	w1, w20
	mov	w0, w19
	bl	FSP_SetDisplay
.L426:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FSP_ClearLogicFs, .-FSP_ClearLogicFs
	.align	3
.LC150:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetLogicFs
	.type	FSP_GetLogicFs, %function
FSP_GetLogicFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L439
	ldr	x0, .LC151
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L439
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x19, 144
	add	x0, x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L439:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetLogicFs, .-FSP_GetLogicFs
	.align	3
.LC151:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetFsImagePtr
	.type	FSP_GetFsImagePtr, %function
FSP_GetFsImagePtr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L443
	ldr	x0, .LC152
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L443
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x19, 192
	add	x0, x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L443:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetFsImagePtr, .-FSP_GetFsImagePtr
	.align	3
.LC152:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDecPhyFs
	.type	FSP_GetDecPhyFs, %function
FSP_GetDecPhyFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L447
	ldr	x0, .LC153
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L447
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x0, x19
	ldr	x0, [x19, 176]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L447:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetDecPhyFs, .-FSP_GetDecPhyFs
	.align	3
.LC153:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDispPhyFs
	.type	FSP_GetDispPhyFs, %function
FSP_GetDispPhyFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L451
	ldr	x0, .LC154
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L451
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x0, x19
	ldr	x0, [x19, 184]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L451:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetDispPhyFs, .-FSP_GetDispPhyFs
	.align	3
.LC154:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPmvAddr
	.type	FSP_GetPmvAddr, %function
FSP_GetPmvAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L455
	ldr	x0, .LC155
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L455
	lsl	x1, x19, 5
	add	x19, x1, x19, lsl 3
	add	x19, x19, x19, lsl 4
	add	x19, x0, x19
	ldr	w0, [x19, 152]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L455:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetPmvAddr, .-FSP_GetPmvAddr
	.align	3
.LC155:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDecFsAddrTab
	.type	FSP_GetDecFsAddrTab, %function
FSP_GetDecFsAddrTab:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	mov	x21, x3
	bl	_mcount
	cmp	w22, 31
	bhi	.L467
	cbz	x20, .L468
	cbz	x19, .L469
	ldr	x2, .LC162
	ldr	x0, [x2, w22, sxtw 3]
	cbz	x0, .L470
	ldrsb	w3, [x0, 3]
	mov	w1, 88
	str	w3, [x19]
	mov	w0, 0
	cmp	w3, wzr
	ldr	x6, [x2, w22, sxtw 3]
	add	x6, x6, 20480
	add	x6, x6, 1424
	ble	.L456
	.p2align 2
.L465:
	smaddl	x4, w0, w1, x6
	ldr	w5, [x4, 8]
	str	w5, [x20, w0, sxtw 2]
	ldr	w4, [x4, 20]
	str	w4, [x21, w0, sxtw 2]
	add	w0, w0, 1
	ldr	w4, [x19]
	cmp	w4, w0
	bgt	.L465
.L456:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L467:
	ldr	x3, .LC156
	mov	w2, 1515
	ldr	x1, .LC157
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L468:
	ldr	x3, .LC159
	mov	w2, 1516
	ldr	x1, .LC157
	mov	w0, 0
	bl	dprint_vfmw
	b	.L456
.L469:
	ldr	x3, .LC161
	mov	w2, 1517
	ldr	x1, .LC157
	mov	w0, 0
	bl	dprint_vfmw
	b	.L456
.L470:
	ldr	x3, .LC163
	mov	w2, 1518
	ldr	x1, .LC157
	bl	dprint_vfmw
	b	.L456
	.size	FSP_GetDecFsAddrTab, .-FSP_GetDecFsAddrTab
	.align	3
.LC156:
	.xword	.LC8
	.align	3
.LC157:
	.xword	.LC2
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC162:
	.xword	.LANCHOR0
	.align	3
.LC163:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPmvAddrTab
	.type	FSP_GetPmvAddrTab, %function
FSP_GetPmvAddrTab:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 31
	bhi	.L482
	cbz	x19, .L483
	cbz	x21, .L484
	ldr	x0, .LC170
	ldr	x4, [x0, w20, sxtw 3]
	cbz	x4, .L485
	ldrsb	w0, [x4, 5]
	mov	w3, 0
	str	w0, [x21]
	ldrsb	w0, [x4, 5]
	cmp	w0, wzr
	ble	.L471
	.p2align 2
.L480:
	sxtw	x0, w3
	add	x0, x0, 3442
	lsl	x0, x0, 3
	ldr	w0, [x4, x0]
	str	w0, [x19, w3, sxtw 2]
	add	w3, w3, 1
	ldrsb	w0, [x4, 5]
	cmp	w0, w3
	bgt	.L480
.L471:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L482:
	ldr	x3, .LC164
	mov	w2, 1539
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L483:
	ldr	x3, .LC167
	mov	w2, 1540
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	b	.L471
.L484:
	ldr	x3, .LC169
	mov	w2, 1541
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	b	.L471
.L485:
	ldr	x3, .LC171
	mov	w2, 1542
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	b	.L471
	.size	FSP_GetPmvAddrTab, .-FSP_GetPmvAddrTab
	.align	3
.LC164:
	.xword	.LC8
	.align	3
.LC165:
	.xword	.LC2
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC170:
	.xword	.LANCHOR0
	.align	3
.LC171:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetInstInfo
	.type	FSP_GetInstInfo, %function
FSP_GetInstInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC172
	ldr	x3, [x0, w20, sxtw 3]
	cbz	x3, .L489
	ldrsb	w1, [x3, 3]
	add	x0, x3, 20480
	strb	w1, [x19, 2]
	mov	x2, 2816
	ldr	x5, .LC175
	add	x1, x0, 1424
	ldr	w6, [x0, 1432]
	ldr	w4, [x0, 1520]
	add	x0, x19, 8
	sub	w4, w4, w6
	str	w4, [x19, 4]
	ldrsb	w4, [x3, 4]
	strb	w4, [x19, 3]
	ldrsb	w4, [x3]
	strb	w4, [x19]
	ldrsb	w3, [x3, 5]
	strb	w3, [x19, 1]
	ldr	x3, [x5, 104]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L489:
	ldr	x3, .LC173
	mov	w2, 1559
	ldr	x1, .LC174
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetInstInfo, .-FSP_GetInstInfo
	.align	3
.LC172:
	.xword	.LANCHOR0
	.align	3
.LC173:
	.xword	.LC17
	.align	3
.LC174:
	.xword	.LC2
	.align	3
.LC175:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetLogicIdByPhyAddr
	.type	FSP_GetLogicIdByPhyAddr, %function
FSP_GetLogicIdByPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L502
	ldr	x1, .LC178
	mov	w0, 0
	ldr	x1, [x1, w20, sxtw 3]
	add	x2, x1, 176
	cbnz	x1, .L499
	b	.L503
	.p2align 3
.L494:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L504
.L499:
	ldr	x3, [x2]
	add	x2, x2, 680
	cbz	x3, .L494
	ldr	w3, [x3, 8]
	cmp	w3, w19
	bne	.L494
.L492:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L504:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L502:
	ldr	x3, .LC176
	mov	w2, 1580
	ldr	x1, .LC177
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L492
.L503:
	ldr	x3, .LC179
	mov	w2, 1581
	ldr	x1, .LC177
	bl	dprint_vfmw
	mov	w0, -1
	b	.L492
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	3
.LC176:
	.xword	.LC8
	.align	3
.LC177:
	.xword	.LC2
	.align	3
.LC178:
	.xword	.LANCHOR0
	.align	3
.LC179:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetNullLogicFs
	.type	FSP_GetNullLogicFs, %function
FSP_GetNullLogicFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC180
	ldr	x3, [x0, w19, sxtw 3]
	add	x1, x3, 20480
	ldrsb	w0, [x1, 745]
	cbz	w0, .L508
	add	x1, x1, 65
	mov	w0, 30
	b	.L507
	.p2align 3
.L514:
	sub	w0, w0, #1
	cmn	w0, #1
	beq	.L513
.L507:
	ldrsb	w2, [x1]
	sub	x1, x1, #680
	cbnz	w2, .L514
.L506:
	sxtw	x2, w0
	lsl	x1, x2, 5
	add	x2, x1, x2, lsl 3
	add	x2, x2, x2, lsl 4
	add	x1, x3, x2
	stp	xzr, xzr, [x1, 176]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L513:
	mov	w0, 0
	b	.L506
.L508:
	mov	w0, 31
	b	.L506
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	3
.LC180:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L519
	ldr	x0, .LC183
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L520
	ldr	w0, [x0, 28]
	cmp	w0, 1
	csetm	w0, ne
.L517:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L519:
	ldr	x3, .LC181
	mov	w2, 1626
	ldr	x1, .LC182
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L517
.L520:
	ldr	x3, .LC184
	mov	w2, 1627
	ldr	x1, .LC182
	bl	dprint_vfmw
	mov	w0, -1
	b	.L517
	.size	FSP_GetFspType, .-FSP_GetFspType
	.align	3
.LC181:
	.xword	.LC8
	.align	3
.LC182:
	.xword	.LC2
	.align	3
.LC183:
	.xword	.LANCHOR0
	.align	3
.LC184:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetTotalValidFsNum
	.type	FSP_GetTotalValidFsNum, %function
FSP_GetTotalValidFsNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L525
	ldr	x0, .LC187
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L526
	ldrsb	w0, [x0, 2]
.L523:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L525:
	ldr	x3, .LC185
	mov	w2, 1641
	ldr	x1, .LC186
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L523
.L526:
	ldr	x3, .LC188
	mov	w2, 1642
	ldr	x1, .LC186
	bl	dprint_vfmw
	mov	w0, -1
	b	.L523
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.align	3
.LC185:
	.xword	.LC8
	.align	3
.LC186:
	.xword	.LC2
	.align	3
.LC187:
	.xword	.LANCHOR0
	.align	3
.LC188:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsSpecialFrm
	.type	FSP_IsSpecialFrm, %function
FSP_IsSpecialFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	mov	w0, 0
	bgt	.L528
	mov	w1, w20
	mov	w0, w19
	bl	FSP_IsSpecialFrm.part.3
.L528:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsSpecialFrm, .-FSP_IsSpecialFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetSingleFrameBuf
	.type	FSP_SetSingleFrameBuf, %function
FSP_SetSingleFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC189
	mov	w7, 32
	ldr	x8, [x0, w20, sxtw 3]
	add	x6, x8, 290816
	add	x0, x8, 294912
	ldr	w1, [x6, 1132]
	ldr	w0, [x0, 592]
	cmp	w1, w7
	csel	w7, w1, w7, le
	str	w7, [x6, 3504]
	ldr	w1, [x19]
	cmp	w1, 255
	beq	.L549
	ldrb	w1, [x6, 3928]
	cbz	w1, .L550
	add	x2, x6, 3940
	mov	x3, 1
	b	.L533
	.p2align 3
.L577:
	add	w3, w3, 1
	cmp	w3, 32
	beq	.L576
.L533:
	ldrb	w4, [x2]
	add	x2, x2, 12
	cbnz	w4, .L577
.L532:
	uxtw	x5, w3
	add	x4, x6, 3456
	lsl	x1, x5, 2
	ldr	w2, [x19, 32]
	sub	x1, x1, x5
	mov	w9, 1
	add	w2, w2, 1023
	add	x5, x5, 20
	add	x1, x4, x1, lsl 2
	and	w2, w2, -1024
	add	w0, w0, w2
	str	w2, [x1, 464]
	ldr	w2, [x19, 12]
	str	w2, [x1, 468]
	strb	w9, [x1, 472]
	ldr	w2, [x4, 60]
	add	w2, w2, 1
	str	w2, [x4, 60]
	str	w0, [x4, x5, lsl 2]
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L531
	ldr	w0, [x19, 48]
	str	w0, [x1, 848]
	strb	w9, [x1, 856]
	ldr	w0, [x4, 68]
	add	w0, w0, 1
	str	w0, [x4, 68]
.L531:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L547
	ldrb	w0, [x6, 3668]
	cbz	w0, .L578
	add	x2, x6, 3676
	mov	w0, 1
	b	.L536
	.p2align 3
.L579:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L547
.L536:
	ldrb	w4, [x2]
	add	x2, x2, 8
	cbnz	w4, .L579
.L535:
	add	x0, x8, x0, uxtw 3
	ldr	w4, [x19, 64]
	add	x0, x0, 290816
	mov	w2, 1
	str	w4, [x0, 3664]
	strb	w2, [x0, 3668]
	ldr	w0, [x6, 3520]
	add	w0, w0, 1
	str	w0, [x6, 3520]
.L547:
	ldr	x0, .LC190
	ldr	x5, [x0, w20, sxtw 3]
	add	x8, x5, 20480
	strb	w7, [x5, 3]
	strb	wzr, [x5, 4]
	ldrsb	w7, [x6, 3512]
	strb	w7, [x5, 5]
	ldr	w0, [x8, 1508]
	cbz	w0, .L551
	add	x2, x8, 1596
	mov	x0, 1
	b	.L539
	.p2align 3
.L538:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L580
.L539:
	ldr	w4, [x2]
	add	x2, x2, 88
	cbnz	w4, .L538
	mov	w9, w0
.L537:
	lsl	x2, x0, 2
	ldr	w4, [x5, 16]
	sub	x2, x2, x0
	lsl	x1, x3, 2
	lsl	x2, x2, 2
	sub	x1, x1, x3
	sub	x0, x2, x0
	add	w2, w4, 1
	str	w2, [x5, 16]
	add	x2, x6, 3456
	add	x0, x5, x0, lsl 3
	add	x1, x2, x1, lsl 2
	add	x0, x0, 20480
	add	x3, x3, 20
	add	x4, x5, 36
	str	w9, [x0, 1428]
	mov	w9, 1
	ldr	w10, [x1, 464]
	str	w10, [x0, 1432]
	ldr	w1, [x1, 468]
	str	w1, [x0, 1436]
	ldr	w1, [x2, x3, lsl 2]
	str	w1, [x0, 1444]
	ldr	w1, [x2, 4]
	str	w1, [x0, 1448]
	ldr	w1, [x2, 8]
	str	w1, [x0, 1452]
	ldr	w1, [x2, 20]
	str	w1, [x0, 1456]
	ldr	w1, [x2, 28]
	str	w1, [x0, 1460]
	ldr	w1, [x2, 32]
	str	w1, [x0, 1464]
	ldr	w1, [x2, 12]
	str	w1, [x0, 1468]
	ldr	w1, [x2, 16]
	str	w1, [x0, 1472]
	ldr	w3, [x4, 4]
	str	w3, [x0, 1476]
	ldr	w4, [x4, 8]
	str	w4, [x0, 1480]
	ldr	w1, [x2, 36]
	str	w1, [x0, 1484]
	ldr	w1, [x2, 40]
	str	w1, [x0, 1488]
	ldr	w1, [x2, 44]
	str	w1, [x0, 1492]
	str	w9, [x0, 1508]
	strb	wzr, [x0, 1425]
	strb	wzr, [x0, 1426]
	ldr	w0, [x5, 20]
	cmp	w0, w7
	bcs	.L541
	ldr	w1, [x19, 8]
	cmp	w1, 255
	beq	.L541
	uxtw	x1, w0
	add	w0, w0, 1
	add	x2, x2, x1, lsl 3
	add	x1, x5, x1, lsl 3
	add	x1, x1, 24576
	ldr	w2, [x2, 208]
	str	w2, [x1, 2960]
	strb	wzr, [x1, 2965]
	strb	w9, [x1, 2964]
	str	w0, [x5, 20]
.L541:
	ldr	w1, [x5, 24]
	add	x2, x6, 3456
	ldr	w0, [x6, 3504]
	cmp	w1, w0
	bcc	.L581
.L542:
	ldr	w2, [x6, 3508]
	mov	w0, 0
	ldr	w1, [x5, 140]
	add	x6, x6, 3456
	str	w2, [x5, 8]
	cbnz	w1, .L562
	str	wzr, [x5, 60]
	mov	w1, 1
	ldr	w2, [x8, 1432]
	str	w2, [x5, 64]
	ldr	w2, [x6, 4]
	str	w2, [x5, 80]
	ldr	w2, [x6, 8]
	str	w2, [x5, 84]
	stp	w3, w4, [x5, 108]
	ldr	w2, [x6, 36]
	str	w2, [x5, 116]
	ldr	w2, [x6, 40]
	str	w2, [x5, 120]
	ldr	w2, [x6, 44]
	str	w2, [x5, 124]
	strb	wzr, [x5, 57]
	strb	wzr, [x5, 58]
	str	w1, [x5, 140]
.L562:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L581:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L542
	uxtw	x10, w1
	ldr	w7, [x6, 3524]
	lsl	x0, x10, 2
	add	w1, w1, 1
	sub	w9, w7, #1
	sub	x0, x0, x10
	lsl	x0, x0, 2
	lsl	x7, x9, 2
	sub	x0, x0, x10
	sub	x7, x7, x9
	add	x0, x5, x0, lsl 3
	add	x2, x2, x7, lsl 2
	add	x0, x0, 20480
	ldr	w2, [x2, 848]
	str	w2, [x0, 1440]
	str	w1, [x5, 24]
	b	.L542
	.p2align 3
.L580:
	ldr	x2, .LC191
	mov	w0, 1
	ldr	x1, .LC195
	add	x2, x2, 16
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L549:
	mov	x3, 0
	b	.L531
	.p2align 3
.L576:
	ldr	x2, .LC191
	mov	w0, 1
	ldr	x1, .LC193
	add	x2, x2, 16
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L551:
	mov	w9, 0
	mov	x0, 0
	b	.L537
.L550:
	mov	x3, 0
	b	.L532
.L578:
	mov	w0, 0
	b	.L535
	.size	FSP_SetSingleFrameBuf, .-FSP_SetSingleFrameBuf
	.align	3
.LC189:
	.xword	s_pstVfmwChan
	.align	3
.LC190:
	.xword	.LANCHOR0
	.align	3
.LC191:
	.xword	.LANCHOR1
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetInst
	.type	FSP_GetInst, %function
FSP_GetInst:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L585
	ldr	x0, .LC199
	ldr	x0, [x0, w19, sxtw 3]
.L584:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L585:
	ldr	x2, .LC196
	mov	w3, w19
	ldr	x1, .LC198
	mov	w0, 1
	add	x2, x2, 40
	bl	dprint_vfmw
	mov	x0, 0
	b	.L584
	.size	FSP_GetInst, .-FSP_GetInst
	.align	3
.LC196:
	.xword	.LANCHOR1
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	.LANCHOR0
	.global	s_pFspInst
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11517, %object
	.size	__func__.11517, 15
__func__.11517:
	.string	"FSP_NewLogicFs"
	.zero	1
	.type	__func__.11709, %object
	.size	__func__.11709, 22
__func__.11709:
	.string	"FSP_SetSingleFrameBuf"
	.zero	2
	.type	__func__.11719, %object
	.size	__func__.11719, 12
__func__.11719:
	.string	"FSP_GetInst"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"pFspInst = NULL" )
.LC2:
	ASCII(.string	"fsp.c,L%d: %s\n" )
	.zero	1
.LC8:
	ASCII(.string	"InstID out of range" )
	.zero	4
.LC12:
	ASCII(.string	"fsp instance not in used" )
	.zero	7
.LC17:
	ASCII(.string	"fsp is not inited" )
	.zero	6
.LC23:
	ASCII(.string	"fsp is already inited" )
	.zero	2
.LC46:
	ASCII(.string	"pstFspInstCfg = NULL" )
	.zero	3
.LC49:
	ASCII(.string	"This inst is not active" )
.LC60:
	ASCII(.string	"eChanCapLevel = %d is not expected!\n" )
	.zero	3
.LC62:
	ASCII(.string	"decode channel CapLevel is %d(w=%d,h=%d), this stream (w=%d,h=%d) can NOT be decoded!\n" )
	.zero	1
.LC64:
	ASCII(.string	"user set decode channel max resolution is (w=%d,h=%d), this stream (w=%d,h=%d) can NOT be decoded!\n" )
	.zero	4
.LC68:
	ASCII(.string	"DFS, Wrong Partition State. State: 0x%x\n" )
	.zero	7
.LC70:
	ASCII(.string	"DFS, Mem Element Fill Successed! Ready to Decode!\n" )
	.zero	5
.LC72:
	ASCII(.string	"Fsp arrange failed, return %d\n" )
	.zero	1
.LC74:
	ASCII(.string	"arrange ret %d, min = %d, actual = %d\n" )
	.zero	1
.LC83:
	ASCII(.string	"FSP_IsFsLeak: fsp is not inited \n" )
	.zero	6
.LC90:
	ASCII(.string	"no logic frame store!!!\n" )
	.zero	7
.LC94:
	ASCII(.string	"%s no decode phy fs\n" )
	.zero	3
.LC96:
	ASCII(.string	"no pmv memory\n" )
	.zero	1
.LC106:
	ASCII(.string	"LogicFrameID out of range" )
	.zero	6
.LC115:
	ASCII(.string	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d)\n" )
	.zero	2
.LC117:
	ASCII(.string	"FSP_GetRef: InstID out of range" )
.LC120:
	ASCII(.string	"FSP_GetRef: LogicFrameID out of range" )
	.zero	2
.LC123:
	ASCII(.string	"FSP_GetRef: Fsp is not inited" )
	.zero	2
.LC131:
	ASCII(.string	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\n" )
	.zero	4
.LC135:
	ASCII(.string	"pstVoQue is NULL" )
	.zero	7
.LC158:
	ASCII(.string	"DecFsAddrTab is NULL\n" )
	.zero	2
.LC160:
	ASCII(.string	"DecFsNum is NULL\n" )
	.zero	6
.LC166:
	ASCII(.string	"PmvAddrTab is NULL\n" )
	.zero	4
.LC168:
	ASCII(.string	"PmvNum is NULL\n" )
.LC192:
	ASCII(.string	"%s no free frame record position.\n" )
	.zero	5
.LC194:
	ASCII(.string	"%s no free dec fs record position.\n" )
	.zero	4
.LC197:
	ASCII(.string	"%s InstID %d out of range\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	s_pFspInst, %object
	.size	s_pFspInst, 256
s_pFspInst:
	.zero	256
	.type	MemArrange.11467, %object
	.size	MemArrange.11467, 1232
MemArrange.11467:
	.zero	1232
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
