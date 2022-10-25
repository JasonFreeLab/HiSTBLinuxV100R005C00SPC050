#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vc1.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VC1_Vfmw_GenerateIntensityMap, %function
VC1_Vfmw_GenerateIntensityMap:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	uxtb	w22, w3
	bl	_mcount
	cmp	w20, 32
	sub	w0, w20, #64
	csel	w20, w0, w20, ge
	cbnz	w21, .L3
	lsl	w2, w20, 25
	mov	w4, -64
	sub	w2, w2, w20
	lsl	w2, w2, 7
	add	w2, w2, 12288
	add	w2, w2, 4032
.L4:
	cbnz	w22, .L5
	mov	x0, x19
	add	w2, w2, 32
	add	x5, x19, 256
	mov	w3, 255
	.p2align 2
.L6:
	asr	w1, w2, 6
	add	w2, w2, w4
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 255
	csel	w1, w1, w3, le
	strb	w1, [x0], 1
	cmp	x5, x0
	bne	.L6
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5:
	lsl	w2, w4, 25
	mov	x0, x19
	sub	w2, w2, w4
	add	x5, x19, 256
	lsl	w2, w2, 7
	mov	w3, 255
	add	w2, w2, 8192
	add	w2, w2, 32
	.p2align 2
.L7:
	asr	w1, w2, 6
	add	w2, w2, w4
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 255
	csel	w1, w1, w3, le
	strb	w1, [x0], 1
	cmp	x5, x0
	bne	.L7
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3:
	add	w4, w21, 32
	lsl	w2, w20, 6
	b	.L4
	.size	VC1_Vfmw_GenerateIntensityMap, .-VC1_Vfmw_GenerateIntensityMap
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, %function
VC1_Vfmw_UpdataLastPicRNDCTRL.part.5:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 8192
	ldrb	w0, [x1, 2459]
	and	w2, w0, -5
	cbz	w2, .L15
	cmp	w0, 1
	ldrsb	w0, [x19, 10]
	uxtb	w2, w0
	beq	.L16
	strb	w0, [x19, 10]
	strb	w2, [x1, 2478]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L15:
	mov	w2, 1
	mov	w0, w2
	strb	w0, [x19, 10]
	strb	w2, [x1, 2478]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L16:
	cmp	w0, wzr
	cset	w0, eq
	mov	w2, w0
	sxtb	w0, w0
	strb	w0, [x19, 10]
	strb	w2, [x1, 2478]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, .-VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	emp_print
	.type	emp_print, %function
emp_print:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	mov	x0, x30
	stp	x2, x3, [x29, 16]
	stp	x4, x5, [x29, 32]
	stp	x6, x7, [x29, 48]
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 64
	ret
	.size	emp_print, .-emp_print
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AbandonBitsLenthNoUse
	.type	AbandonBitsLenthNoUse, %function
AbandonBitsLenthNoUse:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19]
	mov	w0, 0
	cbz	w1, .L27
	b	.L31
	.p2align 3
.L25:
	mov	w0, w2
.L27:
	ldrb	w1, [x19, -1]!
	add	w2, w0, 8
	cbz	w1, .L25
	add	w0, w0, 9
.L23:
	tbz	x1, 0, .L28
	b	.L21
	.p2align 3
.L26:
	mov	w2, w0
.L28:
	lsr	w1, w1, 1
	add	w0, w2, 1
	tbz	x1, 0, .L26
	add	w0, w2, 2
.L21:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L31:
	mov	w0, 1
	mov	w2, 0
	b	.L23
	.size	AbandonBitsLenthNoUse, .-AbandonBitsLenthNoUse
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Init
	.type	VC1DEC_Init, %function
VC1DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x20, 53248
	bl	_mcount
	ldr	x3, .LC12
	mov	x2, 54104
	mov	w1, 0
	mov	x0, x20
	ldr	w22, [x19, 840]
	ldr	x3, [x3, 96]
	blr	x3
	str	w22, [x19, 840]
	add	x0, x19, 240
	bl	ResetVoQueue
	add	x4, x20, 12288
	ldr	w1, [x21, 32]
	str	x21, [x20]
	mov	w5, 1
	add	w1, w1, 255
	mov	x0, x20
	strb	w5, [x4, 2529]
	and	w1, w1, -256
	add	w3, w1, 4096
	add	w2, w1, 8192
	ldr	w6, [x21, 8]
	str	w6, [x19, 188]
	add	w6, w1, 2048
	str	w1, [x19, 160]
	add	w1, w1, 12288
	str	w3, [x19, 168]
	add	w3, w3, 2048
	str	w2, [x19, 176]
	add	w2, w2, 2048
	str	w6, [x19, 164]
	str	w3, [x19, 172]
	stp	w2, w1, [x19, 180]
	strb	w5, [x4, 2530]
	stp	wzr, wzr, [x19, 120]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 848]
	beq	.L35
	ldr	x1, .LC16
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
.L34:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L35:
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L34
	.size	VC1DEC_Init, .-VC1DEC_Init
	.align	3
.LC12:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vc1SMPSeqHdr
	.type	Vc1SMPSeqHdr, %function
Vc1SMPSeqHdr:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x2
	mov	w21, w1
	bl	_mcount
	lsl	w2, w21, 3
	mov	x1, x20
	add	x0, x29, 56
	bl	BsInit
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 8
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 16
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w0, w20, w0, lsl 24
	mov	w1, 8
	str	w0, [x19, 8]
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 8
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 16
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w0, w20, w0, lsl 24
	ldr	w1, [x19, 8]
	str	w0, [x19, 12]
	cmp	w1, 8192
	bgt	.L40
	cmp	w0, 8192
	bgt	.L41
	cmp	w1, 31
	ble	.L40
	cmp	w0, 31
	ble	.L41
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 16]
	bhi	.L43
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L43
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 5
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 18]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L43
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 20]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 22]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 25]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	cbnz	w0, .L43
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 26]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 27]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 28]
	ldrb	w1, [x19, 16]
	cbnz	w1, .L44
	strb	wzr, [x19, 28]
.L44:
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 29]
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 30]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 31]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	mov	w1, 32
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L49
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L49:
	ldr	x1, .LC27
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L43:
	ldr	x3, .LC25
.L48:
	ldr	x2, .LC19
	mov	w0, 0
	ldr	x1, .LC21
	mov	w20, -1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L41:
	ldr	x3, .LC23
	b	.L48
	.p2align 3
.L40:
	ldr	x3, .LC18
	b	.L48
	.size	Vc1SMPSeqHdr, .-Vc1SMPSeqHdr
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC21:
	.xword	.LC20
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetImgFormat
	.type	VC1_SetImgFormat, %function
VC1_SetImgFormat:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	bl	_mcount
	add	x22, x20, 2520
	add	x1, x22, 20480
	add	x0, x21, 53248
	ldr	w1, [x1, 3668]
	ldr	w0, [x0, 848]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L50
	mov	w23, 1
	str	w23, [x0, 296]
	ldrsb	w0, [x20, 2523]
	cmp	w0, 3
	beq	.L59
	ldr	x3, .LC28
	mov	x2, 4
	strb	wzr, [x19, 284]
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
	ldrb	w0, [x19, 65]
	orr	w0, w0, 12
	bfi	w0, w23, 4, 2
	strb	w0, [x19, 65]
.L54:
	add	x20, x20, 2520
	ldrb	w3, [x19, 66]
	add	x2, x20, 36864
	add	x20, x20, 20480
	mov	w1, 0
	mov	x0, x19
	ldrb	w4, [x2, 1769]
	bfi	w3, w4, 1, 1
	strb	w3, [x19, 66]
	ldr	w2, [x2, 1772]
	str	w2, [x19, 120]
	ldr	w2, [x20, 3612]
	str	w2, [x19, 72]
	ldr	w2, [x20, 3608]
	str	w2, [x19, 68]
	bl	SetAspectRatio
	ldr	w2, [x21, 14592]
	ldr	w1, [x19, 36]
	ldr	w3, [x19, 112]
	ldr	x4, [x19, 504]
	add	w0, w2, w1
	stp	w1, w0, [x19, 20]
	str	w0, [x19, 40]
	add	w1, w3, w1
	add	w0, w3, w0
	add	x2, x4, x2, uxtw
	stp	w1, w0, [x19, 28]
	str	x2, [x19, 512]
	mov	w1, 8
	ldr	w0, [x19, 68]
	mov	w2, 1
	ldr	w3, [x20, 3612]
	str	w3, [x19, 80]
	add	w0, w0, 511
	and	w0, w0, -512
	ldr	w3, [x20, 3608]
	lsr	w0, w0, 5
	strb	w2, [x19, 291]
	strb	w2, [x19, 289]
	str	w3, [x19, 76]
	str	w0, [x19, 136]
	str	w1, [x19, 300]
	str	w1, [x19, 304]
	str	w1, [x19, 308]
.L50:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L59:
	mov	w0, 4
	strb	w0, [x19, 284]
	ldrb	w1, [x19, 65]
	mov	w5, 0
	ldrb	w3, [x21, 24]
	ubfx	x2, x1, 2, 2
	mov	x0, x1
	add	w1, w3, w23
	orr	w1, w1, w2
	and	w2, w1, 3
	cmp	w1, 3
	csel	w1, w2, w5, ls
	bfi	w0, w1, 2, 2
	bfi	w0, w23, 0, 2
	bfi	w0, w23, 4, 2
	strb	w0, [x19, 65]
	b	.L54
	.size	VC1_SetImgFormat, .-VC1_SetImgFormat
	.align	3
.LC28:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Destroy
	.type	VC1DEC_Destroy, %function
VC1DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1DEC_Destroy, .-VC1DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_RecycleImage
	.type	VC1DEC_RecycleImage, %function
VC1DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L63
	add	x19, x19, 53248
	mov	w1, w20
	mov	w2, 0
	ldr	w0, [x19, 848]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 848]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L64
	ldr	w0, [x19, 848]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 848]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L64:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1DEC_RecycleImage, .-VC1DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_GetRemainImg
	.type	VC1DEC_GetRemainImg, %function
VC1DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	add	x19, x19, 2520
	bl	_mcount
	ldr	x0, [x19, 24048]
	cbz	x0, .L72
	ldr	x0, [x20]
	add	x21, x20, 53248
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L67
	add	x23, x19, 20480
	add	x21, x20, 53248
	ldr	w1, [x23, 3664]
	ldr	w0, [x21, 848]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L67
	ldr	w0, [x21, 848]
	ldr	w1, [x23, 3664]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L81
.L67:
	add	x19, x21, 240
.L71:
	mov	x0, x19
	bl	GetVoLastImageID
.L78:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L81:
	mov	x0, x20
	bl	VC1_SetImgFormat
	str	xzr, [x22, 544]
	mov	w2, 1
	str	xzr, [x22, 552]
	str	w2, [x22, 180]
	ldr	w1, [x22, 148]
	ldr	w0, [x21, 848]
	bl	FSP_SetDisplay
	ldr	x0, [x19, 24048]
	ldrb	w1, [x0]
	cmp	w1, 1
	beq	.L82
.L68:
	add	x19, x21, 240
	ldr	w0, [x21, 848]
	mov	x4, x22
	mov	x3, x19
	mov	x2, x20
	mov	w1, 1
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L69
	ldr	w1, [x22, 148]
	mov	x0, x20
	bl	VC1DEC_RecycleImage
	ldr	w0, [x21, 848]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x21, 848]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L71
	.p2align 3
.L69:
	ldr	w0, [x22, 152]
	cmp	w0, 100
	bhi	.L67
	ldr	w0, [x22, 68]
	cmp	w0, 31
	bls	.L67
	ldr	w1, [x22, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L78
	b	.L71
	.p2align 3
.L82:
	strb	w1, [x0, 1]
	mov	w0, 3
	ldr	x1, [x19, 24048]
	strb	wzr, [x1]
	strb	w0, [x19, 1]
	b	.L68
.L72:
	mov	w0, -1
	b	.L78
	.size	VC1DEC_GetRemainImg, .-VC1DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ArrangeVahbMem
	.type	VC1_ArrangeVahbMem, %function
VC1_ArrangeVahbMem:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	mov	w23, w2
	bl	_mcount
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L84
	sub	w1, w23, #32
	cmp	w1, w0
	bhi	.L84
	add	x0, x22, 28672
	mov	w1, 0
	add	x0, x0, 144
	.p2align 2
.L87:
	str	w1, [x0, 1188]
	add	w1, w1, 1
	strb	wzr, [x0, 1]
	cmp	w1, 5
	strb	wzr, [x0]
	add	x0, x0, 1672
	bne	.L87
	ldr	x0, [x22]
	ldr	w19, [x0, 764]
	ldr	w2, [x0, 28]
	cmp	w2, 25
	cbnz	w19, .L88
	beq	.L114
.L108:
	mov	w19, w1
	mov	w24, 3
	mov	w20, 2
.L89:
	ldr	x0, .LC35
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 72
	blr	x3
	ldr	x0, [x22]
	stp	w21, w23, [x29, 76]
	stp	w21, w23, [x29, 84]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L99
	strb	w19, [x29, 74]
	sxtb	w19, w20
	strb	w24, [x29, 73]
.L104:
	add	x20, x22, 53248
	add	x1, x29, 72
	strb	w19, [x29, 75]
	ldr	w0, [x20, 848]
	bl	FSP_ConfigInstance
	mov	w19, w0
	cbnz	w0, .L100
	ldr	x1, [x22]
	add	x3, x29, 68
	ldr	w0, [x20, 848]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L115
	cbnz	w0, .L102
	mov	w19, 1
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L84:
	ldr	x1, .LC32
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
.L110:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L88:
	bne	.L108
	ldr	w4, [x0, 724]
	ldr	w5, [x0, 728]
	cmp	w21, w4
	bhi	.L96
	cmp	w23, w5
	bhi	.L96
	ldr	w2, [x0, 752]
	mov	w20, 1
	ldr	w1, [x0, 748]
	add	w24, w1, 2
	cbnz	w2, .L116
	ldrsb	w19, [x0, 772]
	b	.L89
	.p2align 3
.L100:
	ldr	x1, .LC39
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L114:
	ldr	w4, [x0, 724]
	cmp	w21, w4
	bhi	.L117
	ldr	w1, [x0, 728]
	cmp	w23, w1
	mov	w5, w1
	bhi	.L91
	add	x2, x22, 12288
	mov	w19, 1
	ldrb	w2, [x2, 2520]
	tbnz	x2, 3, .L110
	ldr	w3, [x0, 752]
	mov	w20, w19
	ldr	w2, [x0, 748]
	add	w24, w2, 2
	cbz	w3, .L94
	add	w2, w2, w19
	mov	w19, 17
	cmp	w2, w19
	csel	w20, w2, w19, ls
.L94:
	ldrsb	w19, [x0, 772]
	mov	w23, w1
	mov	w21, w4
	b	.L89
	.p2align 3
.L99:
	mov	w0, 1
	strb	w19, [x29, 74]
	strb	w0, [x29, 73]
	mov	w19, 1
	b	.L104
	.p2align 3
.L96:
	ldr	x1, .LC34
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	b	.L110
	.p2align 3
.L115:
	add	x0, x20, 240
	bl	ResetVoQueue
.L102:
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	b	.L110
	.p2align 3
.L116:
	mov	w19, 17
	add	w1, w1, w20
	cmp	w1, w19
	csel	w20, w1, w19, ls
	ldrsb	w19, [x0, 772]
	b	.L89
.L117:
	ldr	w5, [x0, 728]
.L91:
	ldr	x1, .LC34
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	b	.L110
	.size	VC1_ArrangeVahbMem, .-VC1_ArrangeVahbMem
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC35:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_WritePicMsg
	.type	VC1_WritePicMsg, %function
VC1_WritePicMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	mov	x19, x1
	add	x21, x20, 2520
	bl	_mcount
	add	x22, x22, 53248
	add	x1, x21, 20480
	ldr	w0, [x22, 848]
	ldr	w1, [x1, 3668]
	bl	FSP_GetLogicFs
	cbz	x0, .L143
	ldrsb	w1, [x21, 3104]
	cbz	w1, .L121
	ldr	w2, [x21, 10804]
	add	x1, x21, 8192
	strb	w2, [x19, 5]
	mov	w2, 3
	ldrb	w3, [x1, 2224]
	strb	w3, [x19, 4]
	ldrb	w1, [x1, 2569]
	cmp	w1, 4
	csel	w1, w1, w2, ne
	strb	w1, [x19, 3]
	ldr	w1, [x21, 10804]
	add	x21, x21, 36864
	cmp	w1, w2
	ldr	w1, [x21, 1716]
	beq	.L144
	sub	w1, w1, #1
	strh	w1, [x19, 84]
.L124:
	add	x4, x20, 2520
	add	x2, x4, 36864
	add	x1, x4, 8192
	add	x6, x4, 20480
	ldr	w2, [x2, 1712]
	sub	w2, w2, #1
	strh	w2, [x19, 82]
	ldrb	w2, [x1, 2609]
	strb	w2, [x19, 8]
	ldrb	w2, [x1, 2400]
	strb	w2, [x19, 6]
	ldrb	w2, [x1, 2600]
	strb	w2, [x19, 9]
	ldrb	w2, [x20, 2528]
	strb	w2, [x19, 7]
	ldrsw	x5, [x6, 3632]
	lsl	x2, x5, 3
	sub	x2, x2, x5
	lsl	x3, x2, 4
	sub	x2, x3, x2
	lsl	x2, x2, 1
	sub	x2, x2, x5
	add	x2, x4, x2, lsl 3
	add	x2, x2, 12288
	ldrb	w2, [x2, 2747]
	strb	w2, [x19, 10]
	ldrsw	x5, [x6, 3648]
	lsl	x2, x5, 3
	sub	x2, x2, x5
	lsl	x3, x2, 4
	sub	x2, x3, x2
	lsl	x2, x2, 1
	sub	x2, x2, x5
	add	x2, x4, x2, lsl 3
	add	x2, x2, 12288
	ldrb	w2, [x2, 2747]
	strb	w2, [x19, 11]
	ldrb	w2, [x1, 2598]
	strb	w2, [x19, 15]
	ldrb	w2, [x1, 2401]
	strb	w2, [x19, 13]
	ldrb	w2, [x1, 2405]
	strb	w2, [x19, 14]
	ldrb	w2, [x1, 2568]
	strb	w2, [x19, 12]
	ldrb	w2, [x1, 2736]
	strb	w2, [x19, 18]
	ldrb	w2, [x1, 2571]
	strb	w2, [x19, 19]
	ldrb	w2, [x1, 2578]
	strb	w2, [x19, 17]
	ldr	w2, [x20, 13396]
	strb	w2, [x19, 16]
	ldrb	w2, [x1, 2406]
	cbnz	w2, .L125
	ldrb	w1, [x1, 2578]
	cmp	w1, 8
	cset	w1, ls
	strb	w1, [x19, 20]
.L126:
	add	x2, x20, 2520
	add	x1, x2, 8192
	add	x4, x2, 36864
	ldrb	w3, [x1, 2730]
	strb	w3, [x19, 24]
	ldrb	w3, [x1, 2729]
	strb	w3, [x19, 23]
	ldrb	w3, [x1, 2403]
	strb	w3, [x19, 22]
	ldrb	w3, [x1, 2728]
	strb	w3, [x19, 25]
	ldr	w3, [x20, 13452]
	strb	w3, [x19, 26]
	ldrb	w3, [x1, 2731]
	strb	w3, [x19, 21]
	ldrb	w3, [x1, 2582]
	strb	w3, [x19, 27]
	ldrb	w3, [x1, 2583]
	strb	w3, [x19, 28]
	ldrb	w3, [x1, 2601]
	strb	w3, [x19, 34]
	ldrb	w3, [x1, 2593]
	strb	w3, [x19, 33]
	ldr	x5, [x20, 26568]
	ldrb	w3, [x1, 2609]
	add	x3, x5, x3
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 30]
	ldrb	w3, [x1, 2609]
	ldr	x5, [x20, 26560]
	add	x3, x5, x3
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 29]
	ldrb	w3, [x1, 2581]
	strb	w3, [x19, 31]
	ldrb	w3, [x1, 2599]
	strb	w3, [x19, 32]
	ldrb	w3, [x1, 2592]
	strb	w3, [x19, 35]
	ldrb	w3, [x1, 2404]
	strb	w3, [x19, 36]
	ldrb	w3, [x1, 2588]
	strb	w3, [x19, 37]
	ldrb	w3, [x1, 2590]
	strb	w3, [x19, 38]
	ldrb	w3, [x1, 2591]
	strb	w3, [x19, 39]
	ldrb	w3, [x1, 2589]
	strb	w3, [x19, 40]
	ldrb	w3, [x1, 2605]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 46]
	ldrb	w3, [x1, 2603]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 42]
	ldrb	w3, [x1, 2607]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 44]
	ldrb	w3, [x1, 2608]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 41]
	ldrb	w3, [x1, 2602]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 43]
	ldrb	w3, [x1, 2606]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 47]
	ldrb	w3, [x1, 2604]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 45]
	ldrb	w3, [x1, 2570]
	strb	w3, [x19, 50]
	ldrb	w3, [x1, 2587]
	strb	w3, [x19, 49]
	ldrb	w3, [x1, 2586]
	strb	w3, [x19, 48]
	ldrb	w3, [x1, 2597]
	strb	w3, [x19, 53]
	ldrb	w3, [x1, 2594]
	strb	w3, [x19, 54]
	ldrb	w3, [x1, 2595]
	strb	w3, [x19, 51]
	ldrb	w3, [x1, 2596]
	strb	w3, [x19, 52]
	ldr	w3, [x20, 13428]
	str	w3, [x19, 14424]
	ldr	w3, [x4, 1688]
	str	w3, [x19, 14428]
	ldr	w3, [x4, 1692]
	str	w3, [x19, 14432]
	ldrb	w3, [x1, 2409]
	strb	w3, [x19, 55]
	ldrb	w3, [x1, 2410]
	strb	w3, [x19, 56]
	ldrb	w3, [x1, 2411]
	strb	w3, [x19, 57]
	ldrb	w3, [x1, 2412]
	strb	w3, [x19, 58]
	ldr	w2, [x20, 13324]
	cmp	w2, 3
	beq	.L145
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 333]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 334]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 335]
	ldrb	w1, [x1, 2412]
	strb	w1, [x0, 336]
.L131:
	add	x1, x20, 2520
	add	x2, x1, 8192
	ldrb	w2, [x2, 2224]
	strb	w2, [x0, 338]
	ldrb	w0, [x20, 2531]
	strb	w0, [x19, 63]
	b	.L132
	.p2align 3
.L121:
	add	x1, x21, 8192
	strb	wzr, [x19, 5]
	add	x3, x21, 36864
	mov	w4, 3
	ldrb	w2, [x1, 2208]
	strb	w2, [x19, 4]
	ldrb	w2, [x1, 2459]
	cmp	w2, 4
	csel	w2, w2, w4, ne
	strb	w2, [x19, 3]
	ldr	w2, [x3, 1716]
	sub	w2, w2, #1
	strh	w2, [x19, 84]
	ldr	w2, [x3, 1712]
	strb	wzr, [x19, 8]
	sub	w2, w2, #1
	strh	w2, [x19, 82]
	ldrb	w2, [x1, 2211]
	strb	w2, [x19, 6]
	strb	wzr, [x19, 9]
	ldrb	w2, [x21, 8]
	strb	w2, [x19, 7]
	strb	wzr, [x19, 10]
	strb	wzr, [x19, 11]
	ldrb	w2, [x1, 2214]
	strb	w2, [x19, 13]
	ldrb	w2, [x1, 2218]
	strb	w2, [x19, 14]
	ldrb	w2, [x1, 2478]
	strb	w2, [x19, 12]
	ldrb	w2, [x1, 2488]
	strb	w2, [x19, 18]
	ldrb	w2, [x1, 2463]
	strb	w2, [x19, 19]
	ldrb	w2, [x1, 2462]
	strb	w2, [x19, 17]
	ldr	w2, [x21, 10752]
	strb	w2, [x19, 16]
	ldrb	w2, [x1, 2222]
	cbnz	w2, .L134
	ldrb	w1, [x1, 2462]
	cmp	w1, 8
	cset	w1, ls
	strb	w1, [x19, 20]
.L135:
	add	x2, x20, 2520
	add	x1, x2, 8192
	ldrb	w3, [x1, 2482]
	strb	w3, [x19, 24]
	ldrb	w3, [x1, 2481]
	strb	w3, [x19, 23]
	ldrb	w3, [x1, 2216]
	strb	w3, [x19, 22]
	ldrb	w3, [x1, 2480]
	strb	w3, [x19, 25]
	ldr	w3, [x20, 13204]
	strb	w3, [x19, 26]
	ldrb	w3, [x1, 2483]
	strb	w3, [x19, 21]
	ldrb	w3, [x1, 2467]
	strb	w3, [x19, 27]
	ldrb	w3, [x1, 2468]
	strb	w3, [x19, 28]
	ldr	x3, [x20, 26568]
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 30]
	ldr	x3, [x20, 26560]
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 29]
	ldrb	w3, [x1, 2465]
	strb	w3, [x19, 31]
	ldrb	w3, [x1, 2599]
	strb	w3, [x19, 32]
	ldrb	w3, [x1, 2477]
	strb	w3, [x19, 35]
	ldrb	w3, [x1, 2217]
	strb	w3, [x19, 36]
	ldrb	w3, [x1, 2473]
	strb	w3, [x19, 37]
	ldrb	w3, [x1, 2475]
	strb	w3, [x19, 38]
	ldrb	w3, [x1, 2476]
	strb	w3, [x19, 39]
	ldrb	w3, [x1, 2474]
	strb	w3, [x19, 40]
	ldr	w3, [x20, 13264]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 42]
	ldr	w3, [x20, 13260]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 43]
	ldr	w3, [x20, 13268]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 45]
	ldrb	w3, [x1, 2460]
	strb	w3, [x19, 50]
	ldrb	w3, [x1, 2472]
	strb	w3, [x19, 49]
	ldrb	w3, [x1, 2471]
	strb	w3, [x19, 48]
	ldr	w3, [x20, 13276]
	str	w3, [x19, 14424]
	ldrb	w3, [x1, 2220]
	cmp	w3, 1
	beq	.L146
	mov	w4, 0
	mov	w2, 0
	mov	w5, 0
	mov	w3, 0
.L138:
	add	x1, x20, 2520
	strb	w3, [x19, 59]
	strb	w5, [x19, 60]
	add	x1, x1, 8192
	strb	w2, [x19, 61]
	str	w4, [x0, 360]
	ldrb	w1, [x1, 2208]
	strb	w1, [x0, 338]
.L132:
	add	x2, x20, 2520
	add	x20, x20, 2533
	add	x0, x2, 20480
	add	x1, x2, 36864
	ldr	x5, .LC42
	ldrh	w4, [x19, 82]
	ldr	w3, [x0, 3676]
	strh	w3, [x19, 76]
	add	w4, w4, 1
	ldr	w3, [x0, 3608]
	strh	w3, [x19, 78]
	ldr	w3, [x0, 3612]
	strh	w3, [x19, 80]
	ldrb	w3, [x2, 11]
	strb	w3, [x19, 63]
	ldrb	w2, [x2, 12]
	strb	w2, [x19, 62]
	ldr	w2, [x0, 3592]
	add	w3, w2, 254
	adds	w2, w2, 127
	csel	w2, w3, w2, mi
	asr	w2, w2, 7
	lsl	w2, w2, 4
	str	w2, [x19, 14456]
	ldr	w0, [x1, 1736]
	str	w0, [x19, 14460]
	ldr	w0, [x1, 1740]
	str	w0, [x19, 14464]
	ldr	w0, [x1, 1744]
	str	w0, [x19, 14468]
	ldr	w0, [x1, 1748]
	str	w0, [x19, 14472]
	ldr	w0, [x1, 1752]
	str	w0, [x19, 14476]
	ldr	w0, [x1, 1756]
	str	w0, [x19, 14480]
	ldr	w0, [x1, 1760]
	str	w0, [x19, 14484]
	str	x20, [x19, 64]
	ldrsw	x0, [x22, 848]
	ldr	x0, [x5, x0, lsl 3]
	str	w4, [x0, 1540]
	ldrsw	x1, [x22, 848]
	ldrh	w0, [x19, 84]
	ldr	x1, [x5, x1, lsl 3]
	add	w0, w0, 1
	str	w0, [x1, 1544]
.L118:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L134:
	cmp	w2, 1
	beq	.L147
	cmp	w2, 2
	beq	.L148
	mov	w1, 1
	strb	w1, [x19, 20]
	b	.L135
	.p2align 3
.L125:
	cmp	w2, 1
	beq	.L149
	cmp	w2, 2
	beq	.L150
	mov	w1, 1
	strb	w1, [x19, 20]
	b	.L126
	.p2align 3
.L149:
	ldrb	w1, [x1, 2579]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 20]
	b	.L126
	.p2align 3
.L147:
	ldrb	w1, [x1, 2464]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 20]
	b	.L135
	.p2align 3
.L145:
	ldrb	w2, [x1, 2609]
	cbnz	w2, .L130
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 333]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 334]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 335]
	ldrb	w2, [x1, 2412]
	strb	w2, [x0, 336]
	ldrb	w2, [x1, 2609]
.L130:
	cmp	w2, 1
	bne	.L131
	add	x1, x20, 2520
	add	x1, x1, 8192
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 328]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 329]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 330]
	ldrb	w1, [x1, 2412]
	strb	w1, [x0, 331]
	b	.L131
	.p2align 3
.L144:
	add	w1, w1, 1
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	sub	w1, w1, #1
	strh	w1, [x19, 84]
	b	.L124
	.p2align 3
.L146:
	add	x3, x2, 20480
	ldr	w7, [x3, 3632]
	ldr	w6, [x3, 3648]
	lsl	x4, x7, 3
	sub	x4, x4, x7
	lsl	x3, x6, 3
	lsl	x5, x4, 4
	sub	x3, x3, x6
	sub	x4, x5, x4
	lsl	x4, x4, 1
	sub	x4, x4, x7
	add	x4, x2, x4, lsl 3
	add	x4, x4, 12288
	ldrb	w5, [x4, 1722]
	lsl	x4, x3, 4
	sub	x3, x4, x3
	ldrb	w4, [x1, 2459]
	lsl	x3, x3, 1
	sub	x3, x3, x6
	sub	w4, w4, #2
	and	w4, w4, -3
	add	x2, x2, x3, lsl 3
	add	x2, x2, 12288
	uxtb	w3, w4
	ldrb	w2, [x2, 1722]
	cbnz	w3, .L139
	mov	w4, w2
	mov	w3, w2
	b	.L138
	.p2align 3
.L139:
	ldrb	w3, [x1, 2458]
	mov	w4, w3
	b	.L138
	.p2align 3
.L148:
	strb	wzr, [x19, 20]
	b	.L135
	.p2align 3
.L150:
	strb	wzr, [x19, 20]
	b	.L126
	.p2align 3
.L143:
	ldr	x1, .LC41
	mov	w2, 1032
	mov	w0, 22
	bl	dprint_vfmw
	b	.L118
	.size	VC1_WritePicMsg, .-VC1_WritePicMsg
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_WriteSliceMsg
	.type	VC1_WriteSliceMsg, %function
VC1_WriteSliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x2, x19, 20480
	ldr	x4, .LC43
	add	x1, x2, 3680
	add	x0, x20, 88
	ldr	w3, [x2, 3676]
	strb	w3, [x20, 74]
	ldr	w3, [x2, 3676]
	ldr	x4, [x4, 104]
	lsl	x2, x3, 3
	sub	x2, x2, x3
	lsl	x2, x2, 3
	blr	x4
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_WriteSliceMsg, .-VC1_WriteSliceMsg
	.align	3
.LC43:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_CfgVDH
	.type	VC1_CfgVDH, %function
VC1_CfgVDH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrsb	w0, [x19, 3104]
	cbz	w0, .L153
	ldr	w0, [x19, 10804]
	cmp	w0, 3
	beq	.L158
.L153:
	add	x0, x19, 36864
	ldr	w0, [x0, 1720]
	sub	w0, w0, #1
	str	w0, [x20, 14504]
.L154:
	add	x3, x19, 20480
	ldr	w1, [x20, 14600]
	mov	w0, 16385
	movk	w0, 0x2001, lsl 16
	ubfiz	w1, w1, 30, 1
	ldr	w4, [x3, 3616]
	cmp	w4, wzr
	add	w2, w4, 63
	csel	w2, w2, w4, lt
	asr	w2, w2, 6
	add	w0, w0, w2, lsl 4
	orr	w0, w0, w1
	str	w0, [x20, 14508]
	ldrsw	x5, [x3, 3648]
	ldrsw	x4, [x3, 3632]
	lsl	x3, x5, 3
	ldr	x6, [x19, 24040]
	sub	x1, x3, x5
	lsl	x0, x4, 3
	sub	x0, x0, x4
	lsl	x3, x1, 4
	sub	x3, x3, x1
	lsl	x2, x0, 4
	sub	x0, x2, x0
	lsl	x2, x3, 1
	sub	x2, x2, x5
	lsl	x0, x0, 1
	sub	x0, x0, x4
	ldr	w4, [x6, 1092]
	add	x2, x19, x2, lsl 3
	add	x0, x19, x0, lsl 3
	and	w4, w4, 3
	ubfiz	w4, w4, 4, 4
	ldr	w3, [x2, 15100]
	ldr	w2, [x0, 15100]
	and	w0, w3, 3
	strb	wzr, [x20, 73]
	and	w2, w2, 3
	orr	w0, w4, w0, lsl 2
	orr	w0, w0, w2
	strb	w0, [x20, 72]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L158:
	add	x0, x19, 36864
	ldr	w1, [x0, 1716]
	ldr	w2, [x0, 1712]
	add	w0, w1, 1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	mul	w0, w0, w2
	sub	w0, w0, #1
	str	w0, [x20, 14504]
	b	.L154
	.size	VC1_CfgVDH, .-VC1_CfgVDH
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GenerateDecPara
	.type	VC1_Vfmw_GenerateDecPara, %function
VC1_Vfmw_GenerateDecPara:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1_Vfmw_GenerateDecPara, .-VC1_Vfmw_GenerateDecPara
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_GetImageBuffer
	.type	VC1DEC_GetImageBuffer, %function
VC1DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 12288
	add	x0, x0, 2520
	ldrsb	w1, [x0, 3]
	cmp	w1, 3
	beq	.L171
.L161:
	add	x19, x19, 53248
	ldr	w0, [x19, 848]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L163
	ldr	w0, [x19, 848]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	bne	.L162
	ldr	w0, [x19, 848]
	add	x1, x19, 240
	bl	FSP_ClearNotInVoQueue
	b	.L162
	.p2align 3
.L171:
	ldrb	w0, [x0, 9]
	cmp	w0, 1
	beq	.L161
.L163:
	mov	w20, 1
.L162:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1DEC_GetImageBuffer, .-VC1DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GetImageBuffer
	.type	VC1_Vfmw_GetImageBuffer, %function
VC1_Vfmw_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 53248
	add	x19, x21, 12288
	bl	_mcount
	mov	w1, 1
	ldr	w0, [x22, 848]
	bl	FSP_NewLogicFs
	mov	w1, w0
	add	x0, x19, 2520
	add	x20, x0, 20480
	str	w1, [x20, 3668]
	tbnz	w1, #31, .L192
	add	x20, x21, 28672
	add	x0, x0, 12288
	add	x0, x0, 1720
	ldrh	w2, [x20, 144]
	cbz	w2, .L182
	add	x21, x21, 36864
	add	x0, x20, 1816
	add	x4, x21, 312
.L179:
	ldrh	w3, [x0]
	mov	x2, x0
	add	x0, x0, 1672
	cmp	x0, x4
	cbz	w3, .L176
	bne	.L179
	ldr	w0, [x22, 848]
	mov	w2, 1
	add	x21, x21, 313
	bl	FSP_ClearLogicFs
	ldr	x1, .LC49
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x20, 145
.L181:
	strb	wzr, [x0]
	strb	wzr, [x0, -1]
	add	x0, x0, 1672
	cmp	x0, x21
	bne	.L181
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L182:
	mov	x2, x0
.L176:
	str	x2, [x19, 26560]
	mov	w0, 1
	mov	w1, 0
	strb	w0, [x2, 1]
	.p2align 2
.L178:
	ldr	x4, [x19, 26560]
	sxtw	x0, w1
	uxtb	w2, w1
	add	w1, w1, 1
	add	x4, x4, x0
	cmp	w1, 256
	strb	w2, [x4, 3]
	ldr	x4, [x19, 26560]
	add	x4, x4, x0
	strb	w2, [x4, 259]
	ldr	x4, [x19, 26560]
	add	x4, x4, x0
	strb	w2, [x4, 515]
	ldr	x3, [x19, 26560]
	add	x0, x3, x0
	strb	w2, [x0, 771]
	bne	.L178
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L192:
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 3664]
	ldr	w0, [x22, 848]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L174
	ldr	w0, [x22, 848]
	ldr	x1, [x21, 544]
	bl	FreeUsdByDec
	ldr	w0, [x22, 848]
	ldr	x1, [x21, 552]
	bl	FreeUsdByDec
	ldr	w0, [x22, 848]
	ldr	x1, [x21, 560]
	bl	FreeUsdByDec
	ldr	w0, [x22, 848]
	ldr	x1, [x21, 568]
	bl	FreeUsdByDec
	add	x0, x21, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x20, 3664]
	ldr	w0, [x22, 848]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 3660]
	mov	w2, 1
	ldr	w0, [x22, 848]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 3660]
	str	wzr, [x20, 3664]
	ldr	w0, [x22, 848]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 3660]
	str	w0, [x20, 3664]
.L174:
	add	x0, x19, 2520
	add	x1, x22, 240
	add	x0, x0, 20480
	str	wzr, [x0, 3656]
	ldr	w0, [x22, 848]
	bl	FSP_ClearNotInVoQueue
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_GetImageBuffer, .-VC1_Vfmw_GetImageBuffer
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_MemMove
	.type	VC1_Vfmw_MemMove, %function
VC1_Vfmw_MemMove:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	ldr	x5, [x19, 24040]
	ldr	x1, [x19, 24048]
	ldr	x4, .LC50
	ldr	w3, [x0, 3596]
	ldr	w2, [x0, 3616]
	add	w3, w3, 1
	ldr	x4, [x4, 104]
	ldr	x1, [x1, 1544]
	add	w3, w3, w3, lsr 31
	ldr	x0, [x5, 1544]
	asr	w3, w3, 1
	lsl	w3, w3, 5
	mul	w2, w3, w2
	lsl	w3, w2, 2
	sub	w2, w3, w2
	asr	w2, w2, 1
	sxtw	x2, w2
	blr	x4
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_Vfmw_MemMove, .-VC1_Vfmw_MemMove
	.align	3
.LC50:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_BuildRefList
	.type	VC1_Vfmw_BuildRefList, %function
VC1_Vfmw_BuildRefList:
	sub	sp, sp, #512
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w25, w3
	mov	w19, w1
	mov	w24, w2
	bl	_mcount
	mov	x2, 256
	mov	w1, 0
	add	x0, x29, 96
	add	x22, x21, 20480
	bl	memset
	mov	x2, 256
	mov	w1, 0
	add	x0, x29, 352
	bl	memset
	ldr	x20, .LC51
	mov	x2, 16
	mov	w1, 0
	add	x0, x22, 3624
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x22, 3640
	blr	x3
	ldrsb	w0, [x21, 4]
	tst	w0, -3
	bne	.L195
	cmp	w19, 1
	beq	.L258
	cmp	w19, 2
	beq	.L259
.L204:
	str	wzr, [x22, 3628]
	str	wzr, [x22, 3644]
.L256:
	mov	w0, 1
.L241:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 512
	ret
	.p2align 3
.L195:
	add	x26, x21, 8192
	ldrb	w0, [x26, 2572]
	cmp	w0, 1
	ldrb	w0, [x26, 2609]
	beq	.L260
	cbz	w0, .L261
.L215:
	ldr	x0, [x21, 24056]
	ldr	w27, [x0, 1188]
	mov	w23, w27
.L214:
	cmp	w19, 1
	beq	.L262
.L216:
	cmp	w19, 2
	bne	.L204
	mov	w0, 1
	strb	wzr, [x22, 3624]
	strb	w0, [x22, 3625]
	str	w19, [x22, 3628]
	str	w19, [x22, 3644]
	cbz	w24, .L230
	cbz	w25, .L231
	ldr	x0, [x21, 24056]
	ldr	x1, [x21, 24040]
	ldr	w7, [x0, 1188]
	str	w7, [x22, 3632]
	b	.L233
	.p2align 3
.L261:
	ldr	x0, [x21, 24048]
	cmp	w19, 1
	ldr	x1, [x21, 24056]
	ldr	w23, [x0, 1188]
	ldr	w27, [x1, 1188]
	bne	.L216
.L262:
	ldrb	w0, [x26, 2600]
	strb	w19, [x22, 3625]
	add	w0, w0, 1
	strb	wzr, [x22, 3624]
	str	w0, [x22, 3628]
	str	wzr, [x22, 3644]
	cbz	w24, .L217
	cbz	w25, .L218
	ldr	x0, [x21, 24056]
	ldr	x1, [x21, 24040]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3632]
	b	.L220
	.p2align 3
.L258:
	strb	wzr, [x22, 3624]
	str	w19, [x22, 3628]
	str	wzr, [x22, 3644]
	ldr	x0, [x21, 24056]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3632]
	ldrsb	w0, [x21, 3104]
	cbz	w0, .L197
	ldr	w1, [x21, 10804]
	add	x0, x21, 8192
	cmp	w1, 2
	ldrb	w20, [x0, 2584]
	ldrb	w22, [x0, 2585]
	ldrb	w0, [x0, 2582]
	beq	.L263
.L198:
	cmp	w0, 4
	beq	.L199
.L202:
	mov	w2, 1672
	add	x1, x21, 13
	smull	x2, w19, w2
	add	x2, x2, 12288
	add	x0, x2, 1723
	add	x2, x2, 1979
	add	x0, x21, x0
	add	x2, x21, x2
	.p2align 2
.L200:
	ldrb	w3, [x0]
	add	x0, x0, 1
	strb	w3, [x1]
	add	x1, x1, 1
	cmp	x0, x2
	ldrb	w3, [x0, 255]
	strb	w3, [x1, 255]
	ldrb	w3, [x0, 511]
	strb	w3, [x1, 511]
	ldrb	w3, [x0, 767]
	strb	w3, [x1, 767]
	bne	.L200
	b	.L256
	.p2align 3
.L260:
	cbz	w0, .L215
	ldr	x1, [x21, 24048]
	ldr	x0, [x21, 24056]
	ldr	w27, [x1, 1188]
	ldr	w23, [x0, 1188]
	b	.L214
.L259:
	strb	wzr, [x22, 3624]
	mov	w0, 1
	str	w0, [x22, 3628]
	str	w0, [x22, 3644]
	ldr	x0, [x21, 24056]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3632]
	strb	wzr, [x22, 3640]
	ldr	x0, [x21, 24048]
	ldr	w20, [x0, 1188]
	str	w20, [x22, 3648]
	ldrsb	w0, [x21, 3104]
	cbz	w0, .L205
	add	x0, x21, 8192
	ldrb	w22, [x0, 2584]
	ldrb	w23, [x0, 2585]
	ldrb	w0, [x0, 2582]
.L206:
	cmp	w0, 4
	beq	.L207
.L210:
	mov	w1, 1672
	mov	x3, 14011
	add	x0, x21, 13
	add	x4, x21, 269
	smaddl	x2, w19, w1, x3
	smaddl	x1, w20, w1, x3
	add	x2, x21, x2
	add	x1, x21, x1
	.p2align 2
.L208:
	add	x0, x0, 1
	ldrb	w3, [x2]
	add	x2, x2, 1
	add	x1, x1, 1
	cmp	x0, x4
	strb	w3, [x0, -1]
	ldrb	w3, [x2, 255]
	strb	w3, [x0, 255]
	ldrb	w3, [x2, 511]
	strb	w3, [x0, 511]
	ldrb	w3, [x2, 767]
	strb	w3, [x0, 767]
	ldrb	w3, [x1, -1]
	strb	w3, [x0, 1023]
	ldrb	w3, [x1, 255]
	strb	w3, [x0, 1279]
	ldrb	w3, [x1, 511]
	strb	w3, [x0, 1535]
	ldrb	w3, [x1, 767]
	strb	w3, [x0, 1791]
	bne	.L208
	b	.L256
.L197:
	add	x0, x21, 8192
	ldrb	w20, [x0, 2469]
	ldrb	w22, [x0, 2470]
	ldrb	w0, [x0, 2467]
	b	.L198
.L217:
	ldr	x0, [x21, 24056]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3632]
	ldr	x1, [x21, 24040]
.L220:
	ldr	w0, [x0, 1188]
	str	w0, [x22, 3636]
	ldr	w0, [x21, 10888]
	ldr	w20, [x1, 1188]
	cmp	w0, 1
	bls	.L264
.L221:
	tst	w0, -3
	bne	.L222
	ldrb	w1, [x26, 2582]
	cmp	w1, 4
	beq	.L265
.L222:
	mov	w3, 1672
	mov	x2, 14011
	add	x0, x21, 13
	add	x4, x21, 269
	smaddl	x1, w19, w3, x2
	smaddl	x2, w20, w3, x2
	add	x1, x21, x1
	add	x2, x21, x2
	.p2align 2
.L229:
	add	x0, x0, 1
	ldrb	w3, [x1]
	add	x1, x1, 1
	add	x2, x2, 1
	cmp	x0, x4
	strb	w3, [x0, -1]
	ldrb	w3, [x1, 255]
	strb	w3, [x0, 255]
	ldrb	w3, [x1, 511]
	strb	w3, [x0, 511]
	ldrb	w3, [x1, 767]
	strb	w3, [x0, 767]
	ldrb	w3, [x2, -1]
	strb	w3, [x0, 2047]
	ldrb	w3, [x2, 255]
	strb	w3, [x0, 2303]
	ldrb	w3, [x2, 511]
	strb	w3, [x0, 2559]
	ldrb	w3, [x2, 767]
	strb	w3, [x0, 2815]
	bne	.L229
	b	.L256
.L205:
	add	x0, x21, 8192
	ldrb	w22, [x0, 2469]
	ldrb	w23, [x0, 2470]
	ldrb	w0, [x0, 2467]
	b	.L206
.L230:
	ldr	x0, [x21, 24056]
	ldr	w7, [x0, 1188]
	str	w7, [x22, 3632]
	ldr	x1, [x21, 24040]
.L233:
	strb	wzr, [x22, 3640]
	mov	w0, 1
	strb	w0, [x22, 3641]
	ldr	x0, [x21, 24048]
	ldr	w6, [x0, 1188]
	str	w6, [x22, 3648]
	ldr	w0, [x0, 1188]
	str	w0, [x22, 3652]
	ldr	w0, [x21, 10888]
	ldr	w1, [x1, 1188]
	cmp	w0, 1
	bls	.L266
	ands	w0, w0, -3
	beq	.L267
.L235:
	mov	w8, 1672
	mov	x0, x21
	mov	x4, 0
	smull	x7, w7, w8
	smull	x6, w6, w8
	smull	x8, w1, w8
	.p2align 2
.L236:
	add	x3, x4, x7
	add	x0, x0, 1
	add	x3, x21, x3
	add	x2, x4, x6
	add	x3, x3, 12288
	add	x2, x21, x2
	add	x2, x2, 12288
	add	x1, x4, x8
	add	x1, x21, x1
	add	x4, x4, 1
	ldrb	w5, [x3, 1723]
	add	x1, x1, 12288
	strb	w5, [x0, 12]
	cmp	x4, 256
	ldrb	w5, [x3, 1979]
	strb	w5, [x0, 268]
	ldrb	w5, [x3, 2235]
	strb	w5, [x0, 524]
	ldrb	w3, [x3, 2491]
	strb	w3, [x0, 780]
	ldrb	w3, [x2, 1723]
	strb	w3, [x0, 1036]
	ldrb	w3, [x2, 1979]
	strb	w3, [x0, 1292]
	ldrb	w3, [x2, 2235]
	strb	w3, [x0, 1548]
	ldrb	w2, [x2, 2491]
	strb	w2, [x0, 1804]
	ldrb	w2, [x1, 1723]
	strb	w2, [x0, 2060]
	ldrb	w2, [x1, 1979]
	strb	w2, [x0, 2316]
	ldrb	w2, [x1, 2235]
	strb	w2, [x0, 2572]
	ldrb	w1, [x1, 2491]
	strb	w1, [x0, 2828]
	bne	.L236
	b	.L256
.L267:
	ldrb	w2, [x26, 2582]
	cmp	w2, 4
	bne	.L235
	b	.L241
.L218:
	ldr	x1, [x21, 24040]
	ldr	x0, [x21, 24056]
	ldr	w19, [x1, 1188]
	str	w19, [x22, 3632]
	b	.L220
.L231:
	ldr	x1, [x21, 24040]
	ldr	w7, [x1, 1188]
	str	w7, [x22, 3632]
	b	.L233
.L265:
	cbnz	w0, .L226
	ldr	w22, [x21, 10892]
	ldr	w24, [x21, 10896]
	uxtb	w22, w22
	uxtb	w24, w24
.L227:
	mov	w3, 0
	mov	w2, w24
	add	x0, x29, 96
	mov	w1, w22
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, w24
	mov	w1, w22
	add	x0, x29, 352
	mov	w3, 1
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, 1672
	sub	x0, x29, #3488
	smull	x2, w23, w2
	add	x2, x2, 12288
	add	x1, x2, 2235
	add	x2, x2, 2491
	add	x1, x21, x1
	add	x4, x21, x2
	.p2align 2
.L228:
	ldrb	w3, [x1]
	add	x1, x1, 1
	ldrb	w2, [x1, 255]
	cmp	x1, x4
	add	x3, x0, x3
	add	x2, x0, x2
	ldrb	w3, [x3, 3584]
	ldrb	w2, [x2, 3840]
	strb	w3, [x1, -1]
	strb	w2, [x1, 255]
	bne	.L228
	b	.L222
.L264:
	ldrb	w0, [x26, 2582]
	cmp	w0, 4
	bne	.L222
	ldrb	w22, [x26, 2584]
	mov	w3, 0
	ldrb	w24, [x26, 2585]
	add	x0, x29, 96
	mov	w1, w22
	mov	w2, w24
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w1, w22
	mov	w3, 1
	add	x0, x29, 352
	mov	w2, w24
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w0, 1672
	smull	x0, w27, w0
	add	x0, x0, 12288
	add	x1, x0, 1723
	add	x0, x0, 1979
	add	x3, x21, x0
	add	x1, x21, x1
	sub	x0, x29, #3488
	.p2align 2
.L223:
	ldrb	w2, [x1]
	add	x1, x1, 1
	add	x2, x0, x2
	ldrb	w2, [x2, 3584]
	strb	w2, [x1, -1]
	ldrb	w2, [x1, 255]
	add	x2, x0, x2
	ldrb	w2, [x2, 3840]
	strb	w2, [x1, 255]
	cmp	x1, x3
	bne	.L223
	ldr	w0, [x21, 10888]
	b	.L221
.L266:
	ldrb	w0, [x26, 2582]
	cmp	w0, 4
	bne	.L235
	mov	w0, 0
	b	.L241
.L263:
	ldr	w1, [x21, 10880]
	cmp	w1, 1
	bne	.L198
.L199:
	mov	w3, 0
	mov	w2, w22
	mov	w1, w20
	add	x0, x29, 96
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, w22
	mov	w1, w20
	add	x0, x29, 352
	mov	w3, 1
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, 1672
	sub	x0, x29, #3488
	smull	x2, w19, w2
	add	x2, x2, 12288
	add	x1, x2, 1723
	add	x2, x2, 1979
	add	x1, x21, x1
	add	x6, x21, x2
	.p2align 2
.L201:
	ldrb	w5, [x1]
	add	x1, x1, 1
	ldrb	w4, [x1, 255]
	ldrb	w3, [x1, 511]
	add	x5, x0, x5
	ldrb	w2, [x1, 767]
	add	x4, x0, x4
	add	x3, x0, x3
	cmp	x1, x6
	add	x2, x0, x2
	ldrb	w5, [x5, 3584]
	ldrb	w4, [x4, 3840]
	ldrb	w3, [x3, 3584]
	ldrb	w2, [x2, 3840]
	strb	w5, [x1, -1]
	strb	w4, [x1, 255]
	strb	w3, [x1, 511]
	strb	w2, [x1, 767]
	bne	.L201
	b	.L202
.L207:
	mov	w3, 0
	mov	w2, w23
	mov	w1, w22
	add	x0, x29, 96
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w3, 1
	mov	w2, w23
	mov	w1, w22
	add	x0, x29, 352
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w1, 1672
	mov	x2, 14011
	sub	x0, x29, #3488
	smull	x3, w19, w1
	smaddl	x2, w20, w1, x2
	add	x3, x3, 12288
	add	x1, x3, 1723
	add	x3, x3, 1979
	add	x1, x21, x1
	add	x2, x21, x2
	add	x7, x21, x3
	.p2align 2
.L209:
	ldrb	w6, [x1]
	add	x1, x1, 1
	ldrb	w5, [x1, 255]
	add	x2, x2, 1
	ldrb	w4, [x1, 511]
	add	x6, x0, x6
	ldrb	w3, [x1, 767]
	add	x5, x0, x5
	add	x4, x0, x4
	cmp	x1, x7
	add	x3, x0, x3
	ldrb	w6, [x6, 3584]
	ldrb	w5, [x5, 3840]
	ldrb	w4, [x4, 3584]
	ldrb	w3, [x3, 3840]
	strb	w6, [x1, -1]
	strb	w5, [x1, 255]
	strb	w4, [x1, 511]
	strb	w3, [x1, 767]
	ldrb	w6, [x2, -1]
	ldrb	w5, [x2, 255]
	ldrb	w4, [x2, 511]
	add	x6, x0, x6
	ldrb	w3, [x2, 767]
	add	x5, x0, x5
	add	x4, x0, x4
	add	x3, x0, x3
	ldrb	w6, [x6, 3584]
	ldrb	w5, [x5, 3840]
	ldrb	w4, [x4, 3584]
	ldrb	w3, [x3, 3840]
	strb	w6, [x2, -1]
	strb	w5, [x2, 255]
	strb	w4, [x2, 511]
	strb	w3, [x2, 767]
	bne	.L209
	b	.L210
.L226:
	ldrb	w22, [x26, 2584]
	ldrb	w24, [x26, 2585]
	b	.L227
	.size	VC1_Vfmw_BuildRefList, .-VC1_Vfmw_BuildRefList
	.align	3
.LC51:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GetStreamInfo
	.type	VC1_Vfmw_GetStreamInfo, %function
VC1_Vfmw_GetStreamInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	bl	_mcount
	add	x0, x19, 2520
	add	x1, x0, 20480
	ldrsb	w2, [x0, 3104]
	ldr	w22, [x1, 3592]
	cbz	w2, .L269
	ldr	w0, [x19, 13324]
	ldr	w21, [x1, 3596]
	cmp	w0, 3
	beq	.L351
.L348:
	ldrh	w0, [x19, 5878]
	ldrh	w1, [x19, 5876]
	add	w0, w0, 15
	add	w1, w1, 15
	asr	w0, w0, 4
	mul	w21, w21, w22
	asr	w1, w1, 4
.L321:
	lsl	w2, w1, 4
	mov	w4, 8160
	sub	w3, w2, #32
	cmp	w3, w4
	lsl	w3, w0, 4
	bhi	.L272
	sub	w5, w3, #32
	cmp	w5, w4
	bhi	.L272
	add	x4, x19, 2520
	add	x2, x4, 20480
	ldr	w3, [x2, 3604]
	cmp	w0, w3
	beq	.L352
.L275:
	add	x1, x19, 2520
	lsl	w0, w22, 4
	add	x2, x1, 20480
	add	w0, w0, 63
	and	w0, w0, -64
	mov	w3, 1
	ldr	w4, [x2, 3596]
	str	w22, [x2, 3600]
	str	w4, [x2, 3604]
	str	w0, [x2, 3616]
	ldrb	w0, [x19, 2528]
	cbz	w0, .L283
.L277:
	ldrsb	w1, [x19, 2523]
	cmp	w1, 3
	beq	.L353
.L280:
	ldrb	w1, [x19, 2520]
	eor	x1, x1, 8
	ubfx	x1, x1, 3, 1
	orr	w0, w3, w1
	cbnz	w0, .L283
.L287:
	mov	x0, x20
	bl	VC1_Vfmw_GetImageBuffer
	mov	w23, w0
	cbz	w0, .L354
	add	x1, x19, 2520
	add	x23, x20, 53248
	add	x1, x1, 20480
	ldr	w0, [x23, 848]
	ldr	w1, [x1, 3668]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L289
	ldr	x3, [x20]
	mov	x4, -1
	ldr	x1, .LC58
	mov	w0, 29
	ldr	x3, [x3, 56]
	str	x3, [x2, 584]
	ldr	x3, [x20]
	ldr	x3, [x3, 72]
	str	x3, [x2, 592]
	ldr	x3, [x20]
	ldr	x3, [x3, 88]
	str	x3, [x2, 600]
	ldr	x3, [x20]
	ldr	w3, [x3, 104]
	str	w3, [x2]
	ldr	x3, [x20]
	ldr	w3, [x3, 108]
	str	w3, [x2, 4]
	ldr	x3, [x20]
	ldr	w3, [x3, 112]
	str	w3, [x2, 8]
	ldr	x3, [x20]
	ldr	w3, [x3, 128]
	str	w3, [x2, 12]
	ldr	x3, [x20]
	str	x4, [x3, 56]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
.L289:
	add	x0, x19, 2520
	ldrsb	w1, [x0, 3104]
	cbz	w1, .L290
	ldr	w1, [x19, 13324]
	cmp	w1, 3
	beq	.L355
.L290:
	ldr	x0, [x19, 26560]
	str	wzr, [x0, 1092]
.L291:
	ldr	x1, [x19, 26560]
	add	x0, x19, 2520
	strb	wzr, [x1, 2]
	ldrsb	w1, [x0, 3104]
	cbnz	w1, .L292
	add	x1, x0, 8192
	ldrb	w2, [x1, 2220]
	cmp	w2, 1
	beq	.L356
.L292:
	add	x24, x19, 2520
	ldrb	w0, [x24, 2]
	cmp	w0, 1
	ccmp	w0, 5, 4, hi
	bne	.L293
	add	x24, x24, 20480
	mov	w0, 2
	ldr	w1, [x24, 3656]
	ldr	w2, [x24, 3660]
	ldr	w3, [x24, 3664]
	cmp	w1, wzr
	csinc	w0, w0, wzr, ne
	str	w0, [x24, 3656]
	cmp	w2, w3
	beq	.L295
	ldr	x1, .LC61
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x23, 848]
	mov	w2, 0
	ldr	w1, [x24, 3660]
	bl	FSP_SetRef
	ldr	w3, [x24, 3664]
.L295:
	add	x24, x19, 2520
	mov	w2, 1
	add	x25, x24, 20480
	ldr	w1, [x25, 3668]
	str	w3, [x25, 3660]
	str	w1, [x25, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_SetRef
	ldr	w0, [x23, 848]
	ldr	w1, [x25, 3660]
	bl	FSP_RemovePmv
	ldrb	w0, [x24, 2]
	cmp	w0, 1
	ccmp	w0, 5, 4, hi
	bne	.L297
	ldr	x0, [x24, 24056]
	mov	w1, 1
	strb	wzr, [x0]
	ldr	x0, [x24, 24040]
	strb	w1, [x0]
	ldr	x1, [x24, 24048]
	ldr	x0, [x24, 24040]
	str	x0, [x24, 24048]
	str	x1, [x24, 24056]
.L297:
	add	x25, x19, 2520
	ldr	w0, [x23, 848]
	add	x26, x25, 20480
	ldr	w1, [x26, 3668]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x26, 3660]
	ldr	w0, [x23, 848]
	bl	FSP_GetLogicFs
	mov	x28, x0
	ldr	w1, [x26, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_GetLogicFs
	mov	x27, x0
	cmp	x24, xzr
	ccmp	x28, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L357
	ldrsb	w0, [x25, 3104]
	cbnz	w0, .L358
.L303:
	str	wzr, [x24, 100]
.L304:
	ldrb	w1, [x19, 2522]
	add	x0, x19, 2520
	cmp	w1, 5
	beq	.L359
.L305:
	ldr	x1, [x24, 32]
	cbz	x1, .L306
	ldr	x0, [x24, 40]
	cbz	x0, .L306
	ldr	x0, [x27, 32]
	cbz	x0, .L308
	ldr	w0, [x0, 8]
.L309:
	str	w0, [x20, 14460]
	ldr	x0, [x28, 32]
	cbz	x0, .L360
.L349:
	ldr	w0, [x0, 8]
	str	w0, [x20, 14456]
	ldr	x0, [x24, 32]
	ldr	w0, [x0, 8]
	str	w0, [x20, 14584]
	ldr	w0, [x24, 8]
	str	w0, [x20, 14464]
	ldr	w0, [x27, 8]
	str	w0, [x20, 14468]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x20, 14452]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 24]
	str	w0, [x20, 14532]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 28]
	str	w0, [x20, 14536]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x20, 14540]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 44]
	str	w0, [x20, 14544]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 48]
	str	w0, [x20, 14548]
	ldr	x0, [x24, 32]
	ldr	x24, [x19, 26560]
	ldr	w0, [x0, 8]
	bl	MEM_Phy2Vir
	str	x0, [x24, 1544]
	ldr	x24, [x19, 26576]
	ldr	w0, [x20, 14456]
	bl	MEM_Phy2Vir
	str	x0, [x24, 1544]
	ldr	x23, [x19, 26568]
	ldr	w0, [x20, 14460]
	bl	MEM_Phy2Vir
	str	x0, [x23, 1544]
.L282:
	add	x0, x19, 2520
	ldr	x2, [x0, 24040]
	ldrsb	w1, [x0, 3104]
	cbnz	w1, .L312
	strb	wzr, [x2, 1027]
	add	x1, x0, 8192
	ldr	x2, [x0, 24040]
	ldrb	w3, [x1, 2459]
	strb	w3, [x2, 1028]
	ldrb	w3, [x1, 2467]
	ldr	x2, [x0, 24040]
	sub	w0, w3, #2
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L326
	cmp	w3, 4
	mov	w0, 0
	beq	.L361
.L313:
	add	x24, x19, 2520
	strb	w0, [x2, 1030]
	add	x21, x24, 20480
	strb	w0, [x2, 1029]
	mov	w0, 1
	add	x22, x24, 36864
	strb	wzr, [x21, 3696]
	str	w0, [x21, 3676]
	ldr	x0, [x19, 5656]
	ldr	x23, [x22, 1640]
	bl	BsPos
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	asr	w0, w0, 3
	add	x0, x23, x0, sxtw
	str	x0, [x19, 26680]
	ldr	x0, [x19, 5656]
	ldr	w23, [x22, 1660]
	bl	BsPos
	add	w1, w0, 7
	cmp	w0, wzr
	csel	w0, w1, w0, lt
	add	w0, w23, w0, asr 3
	str	w0, [x21, 3700]
	ldr	x0, [x19, 5656]
	bl	BsPos
	and	w0, w0, 7
	str	w0, [x21, 3704]
	ldr	w23, [x22, 1668]
	ldr	x0, [x19, 5656]
	lsl	w23, w23, 3
	bl	BsPos
	sub	w0, w23, w0
	str	w0, [x21, 3708]
	ldr	w1, [x22, 1716]
	ldr	w0, [x22, 1712]
	mul	w0, w0, w1
	sub	w0, w0, #1
	str	w0, [x21, 3712]
	ldrb	w1, [x19, 2522]
.L314:
	add	x19, x19, 2520
	mov	w3, 1
	mov	w2, 0
	mov	x0, x19
	bl	VC1_Vfmw_BuildRefList
	mov	w23, w0
	cbz	w0, .L362
	mov	w23, 1
	b	.L347
	.p2align 3
.L272:
	ldr	x1, .LC52
	mov	w0, 0
	mov	w23, 0
	bl	dprint_vfmw
.L347:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L269:
	ldr	w0, [x1, 3596]
	mov	w1, w22
	mul	w21, w22, w0
	b	.L321
	.p2align 3
.L351:
	add	w21, w21, 1
	add	w21, w21, w21, lsr 31
	asr	w21, w21, 1
	b	.L348
	.p2align 3
.L283:
	add	x0, x19, 2520
	add	x23, x20, 53248
	add	x25, x0, 20480
	add	x1, x25, 1888
	str	x1, [x19, 26560]
	str	x1, [x19, 26568]
	str	x1, [x19, 26576]
	str	x1, [x19, 26584]
	ldr	w0, [x23, 848]
	ldr	w1, [x25, 3664]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L279
	ldr	w0, [x23, 848]
	ldr	x1, [x24, 544]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x24, 552]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x24, 560]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x24, 568]
	bl	FreeUsdByDec
	add	x0, x24, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x23, 848]
	ldr	w1, [x25, 3664]
	bl	FSP_ClearLogicFs
	ldr	w0, [x23, 848]
	mov	w2, 1
	ldr	w1, [x25, 3660]
	bl	FSP_ClearLogicFs
	str	wzr, [x25, 3660]
	str	wzr, [x25, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_GetNullLogicFs
	str	w0, [x25, 3660]
	str	w0, [x25, 3664]
.L279:
	add	x2, x19, 2520
	add	x0, x20, 28672
	add	x2, x2, 20480
	add	x1, x20, 36864
	add	x0, x0, 145
	add	x1, x1, 313
	str	wzr, [x2, 3656]
	.p2align 2
.L285:
	strb	wzr, [x0]
	strb	wzr, [x0, -1]
	add	x0, x0, 1672
	cmp	x1, x0
	bne	.L285
	add	x24, x23, 240
	ldr	w0, [x23, 848]
	mov	x1, x24
	bl	FSP_ClearNotInVoQueue
	ldrb	w0, [x19, 2520]
	tbnz	x0, 3, .L287
	mov	x0, x24
	bl	ResetVoQueue
	ldr	x1, [x20]
	ldr	w0, [x1, 724]
	ldr	w3, [x1, 728]
	adds	w1, w0, 15
	add	w0, w0, 30
	add	w2, w3, 30
	csel	w1, w0, w1, mi
	adds	w0, w3, 15
	asr	w1, w1, 4
	csel	w0, w2, w0, mi
	str	w1, [x20, 14624]
	asr	w0, w0, 4
	mov	w3, 2
	add	w2, w0, 1
	str	w0, [x20, 14628]
	lsl	w1, w1, 4
	mov	x0, x20
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
	lsl	w2, w2, 5
	bl	VC1_ArrangeVahbMem
	cmp	w0, 1
	bne	.L286
	ldrb	w0, [x19, 2520]
	orr	w0, w0, 8
	strb	w0, [x19, 2520]
	b	.L287
	.p2align 3
.L354:
	ldr	x1, .LC56
	mov	w0, 1
	bl	dprint_vfmw
	b	.L347
	.p2align 3
.L352:
	ldr	w0, [x2, 3600]
	cmp	w1, w0
	bne	.L275
	lsl	w0, w22, 4
	mov	w3, 0
	add	w0, w0, 63
	and	w0, w0, -64
	str	w0, [x2, 3616]
	ldrb	w0, [x4, 8]
	cbz	w0, .L280
	b	.L277
	.p2align 3
.L293:
	add	x0, x24, 20480
	ldr	w1, [x0, 3656]
	cmp	w1, 1
	bhi	.L297
	ldr	w1, [x0, 3668]
	mov	w2, 1
	ldr	w0, [x23, 848]
	mov	w23, 0
	bl	FSP_ClearLogicFs
	ldr	x2, [x24, 24040]
	mov	w0, 1
	ldr	x1, .LC63
	strb	wzr, [x2]
	ldr	x2, [x24, 24040]
	strb	wzr, [x2, 1]
	bl	dprint_vfmw
	b	.L347
	.p2align 3
.L357:
	ldr	w0, [x23, 848]
	mov	w2, 1
	ldr	w1, [x26, 3668]
	bl	FSP_ClearLogicFs
	ldr	x0, [x25, 24040]
	mov	x5, x27
	ldr	x1, .LC65
	mov	x4, x28
	mov	x3, x24
	mov	w2, 2291
	strb	wzr, [x0]
	mov	w0, 0
	ldr	x6, [x25, 24040]
	strb	wzr, [x6, 1]
	bl	dprint_vfmw
	ldrb	w0, [x25, 2]
	cmp	w0, 5
	beq	.L363
.L301:
	ldr	x1, .LC67
	mov	w0, 1
	mov	w23, 0
	bl	dprint_vfmw
	b	.L347
	.p2align 3
.L312:
	ldr	w3, [x0, 10804]
	add	x1, x0, 8192
	strb	w3, [x2, 1027]
	ldr	x2, [x0, 24040]
	ldrb	w3, [x1, 2569]
	strb	w3, [x2, 1028]
	ldrb	w3, [x1, 2582]
	ldr	x5, [x0, 24040]
	sub	w2, w3, #2
	ldrb	w0, [x1, 2609]
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L328
	cmp	w3, 4
	mov	w4, 0
	beq	.L364
.L315:
	add	x0, x5, x0, sxtw
	add	x3, x19, 2520
	add	x2, x3, 20480
	strb	w4, [x0, 1029]
	ldr	w1, [x2, 3676]
	cbz	w1, .L316
	sub	w5, w1, #1
	mov	w1, 0
	mov	w4, w5
	cbz	w5, .L350
	.p2align 2
.L339:
	sxtw	x2, w1
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 3
	add	x2, x3, x0
	add	x0, x0, 20480
	add	x2, x2, 20480
	add	x0, x3, x0
	strb	w1, [x2, 3696]
	add	w1, w1, 1
	cmp	w4, w1
	ldr	w0, [x0, 3768]
	mul	w0, w22, w0
	sub	w0, w0, #1
	str	w0, [x2, 3712]
	bne	.L339
	uxtb	w4, w4
.L318:
	uxtw	x1, w5
	add	x2, x19, 2520
	lsl	x0, x1, 3
	sub	w21, w21, #1
	sub	x0, x0, x1
	add	x0, x2, x0, lsl 3
	add	x0, x0, 20480
	strb	w4, [x0, 3696]
	str	w21, [x0, 3712]
	ldrb	w1, [x19, 2522]
	cmp	w1, 2
	bne	.L314
	add	x0, x2, 8192
	ldr	w3, [x19, 13428]
	add	x2, x2, 36864
	ldrb	w0, [x0, 2599]
	mul	w3, w0, w3
	asr	w3, w3, 8
	str	w3, [x2, 1688]
	sub	w0, w0, w3
	subs	w0, w0, #1
	csel	w0, w0, wzr, pl
	str	w0, [x2, 1692]
	b	.L314
	.p2align 3
.L358:
	ldr	w0, [x25, 10804]
	cmp	w0, 3
	bne	.L303
	ldr	x0, .LC59
	ldr	w0, [x0]
	cmp	w0, 1
	bne	.L303
	str	w0, [x24, 100]
	b	.L304
	.p2align 3
.L363:
	add	x25, x25, 36864
	ldr	w0, [x25, 1732]
	cmp	w0, wzr
	ble	.L301
	sub	w0, w0, #1
	str	w0, [x25, 1732]
	b	.L301
	.p2align 3
.L353:
	ldrb	w0, [x19, 2529]
	cmp	w0, 1
	bne	.L282
	b	.L280
	.p2align 3
.L362:
	add	x0, x19, 20480
	add	x20, x20, 53248
	mov	w2, 1
	ldr	w1, [x0, 3668]
	ldr	w0, [x20, 848]
	bl	FSP_ClearLogicFs
	ldr	x2, [x19, 24040]
	mov	w0, 1
	ldr	x1, .LC71
	strb	wzr, [x2]
	ldr	x2, [x19, 24040]
	strb	wzr, [x2, 1]
	bl	dprint_vfmw
	b	.L347
	.p2align 3
.L316:
	mov	w0, 1
	mov	w5, 0
	str	w0, [x2, 3676]
.L350:
	mov	w4, 0
	b	.L318
	.p2align 3
.L359:
	ldr	w1, [x28, 100]
	add	x0, x0, 36864
	str	w1, [x24, 100]
	ldr	x2, [x19, 26576]
	ldr	x1, [x19, 26560]
	ldr	w2, [x2, 1092]
	str	w2, [x1, 1092]
	ldr	w1, [x0, 1732]
	add	w1, w1, 1
	str	w1, [x0, 1732]
	b	.L305
	.p2align 3
.L356:
	ldr	x0, [x19, 26560]
	ldrb	w1, [x1, 2458]
	strb	w1, [x0, 2]
	b	.L292
	.p2align 3
.L355:
	ldr	x1, .LC59
	ldr	w1, [x1]
	cmp	w1, 1
	bne	.L290
	ldr	x0, [x19, 26560]
	str	w1, [x0, 1092]
	b	.L291
	.p2align 3
.L306:
	add	x19, x19, 2520
	ldr	w0, [x23, 848]
	add	x20, x19, 20480
	mov	w2, 1
	ldr	w1, [x20, 3668]
	bl	FSP_ClearLogicFs
	ldr	x2, [x19, 24040]
	mov	w0, 0
	ldr	x1, .LC69
	strb	wzr, [x2]
	ldr	x2, [x19, 24040]
	strb	wzr, [x2, 1]
	ldr	w2, [x20, 3660]
	ldr	w4, [x20, 3664]
	ldr	w3, [x20, 3668]
	ldp	x5, x6, [x24, 32]
	bl	dprint_vfmw
	ldrb	w0, [x19, 2]
	cmp	w0, 5
	bne	.L301
	add	x19, x19, 36864
	ldr	w0, [x19, 1732]
	cmp	w0, wzr
	ble	.L301
	sub	w0, w0, #1
	str	w0, [x19, 1732]
	b	.L301
	.p2align 3
.L286:
	ldr	x1, .LC54
	mov	w0, 1
	mov	w23, 0
	bl	dprint_vfmw
	ldrb	w0, [x19, 2520]
	and	w0, w0, -9
	strb	w0, [x19, 2520]
	b	.L347
	.p2align 3
.L328:
	mov	w4, 1
	b	.L315
	.p2align 3
.L326:
	mov	w0, 1
	b	.L313
	.p2align 3
.L308:
	ldr	w0, [x1, 8]
	b	.L309
	.p2align 3
.L360:
	ldr	x0, [x24, 32]
	b	.L349
	.p2align 3
.L364:
	ldrb	w1, [x1, 2583]
	sub	w1, w1, #2
	uxtb	w1, w1
	cmp	w1, 1
	cset	w4, ls
	b	.L315
	.p2align 3
.L361:
	ldrb	w0, [x1, 2468]
	sub	w0, w0, #2
	uxtb	w0, w0
	cmp	w0, 1
	cset	w0, ls
	b	.L313
	.size	VC1_Vfmw_GetStreamInfo, .-VC1_Vfmw_GetStreamInfo
	.align	3
.LC52:
	.xword	.LC31
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC56:
	.xword	.LC55
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC59:
	.xword	USE_FF_APT_EN
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
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC71:
	.xword	.LC70
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_PrepareDecode
	.type	VC1_Vfmw_PrepareDecode, %function
VC1_Vfmw_PrepareDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	VC1_Vfmw_GetStreamInfo
	mov	w19, w0
	cbz	w0, .L368
	mov	w19, 1
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L368:
	ldr	x1, .LC73
	bl	dprint_vfmw
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_Vfmw_PrepareDecode, .-VC1_Vfmw_PrepareDecode
	.align	3
.LC73:
	.xword	.LC72
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvrange
	.type	VC1_DecMvrange, %function
VC1_DecMvrange:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC74
	mov	w1, 3
	mov	x0, x19
	ldp	x8, x9, [x3, 16]
	ldp	x6, x7, [x3, 32]
	ldp	x4, x5, [x3, 48]
	ldp	x2, x3, [x3, 64]
	stp	x8, x9, [x29, 32]
	stp	x6, x7, [x29, 48]
	stp	x4, x5, [x29, 64]
	stp	x2, x3, [x29, 80]
	bl	BsShow
	add	x1, x29, 96
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -64]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.size	VC1_DecMvrange, .-VC1_DecMvrange
	.align	3
.LC74:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecTransacfrm
	.type	VC1_DecTransacfrm, %function
VC1_DecTransacfrm:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w2, 2
	mov	w3, 1
	mov	w1, w2
	mov	x0, x19
	stp	xzr, xzr, [x29, 32]
	str	w3, [x29, 36]
	stp	w3, w3, [x29, 44]
	stp	w2, w2, [x29, 52]
	str	w2, [x29, 60]
	stp	xzr, xzr, [x29, 64]
	stp	xzr, xzr, [x29, 80]
	bl	BsShow
	add	x1, x29, 96
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -64]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.size	VC1_DecTransacfrm, .-VC1_DecTransacfrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetCurPicResolutionInfo
	.type	VC1_SetCurPicResolutionInfo, %function
VC1_SetCurPicResolutionInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x1, x19, 20480
	cmp	w20, 1
	add	x0, x19, 36864
	ldr	w2, [x1, 3592]
	beq	.L373
	cmp	w20, 2
	beq	.L379
	cbz	w20, .L378
	add	w2, w2, 1
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
.L379:
	str	w2, [x0, 1712]
	ldr	w1, [x1, 3596]
	add	w1, w1, 1
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	str	w1, [x0, 1716]
	b	.L376
	.p2align 3
.L373:
	add	w2, w2, 1
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
.L378:
	str	w2, [x0, 1712]
	ldr	w1, [x1, 3596]
	str	w1, [x0, 1716]
.L376:
	mul	w3, w2, w1
	str	w3, [x0, 1720]
	lsl	w2, w2, 4
	lsl	w1, w1, 4
	str	w2, [x0, 1704]
	str	w1, [x0, 1708]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_SetCurPicResolutionInfo, .-VC1_SetCurPicResolutionInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeProgrP
	.type	VC1_DecMvmodeProgrP, %function
VC1_DecMvmodeProgrP:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsShow
	cmp	w0, 1
	ldr	x1, .LC76
	add	x2, x1, 104
	ldp	x4, x5, [x1, 80]
	ldr	w3, [x1, 96]
	ldp	x6, x7, [x2]
	add	x2, x29, 72
	ldr	w1, [x1, 120]
	stp	x4, x5, [x29, 48]
	str	w3, [x29, 64]
	stp	x6, x7, [x2]
	str	w1, [x29, 88]
	ble	.L388
	cmp	w0, 3
	ble	.L386
	cmp	w0, 8
	mov	w1, 2
	csinc	w1, w1, wzr, lt
	cset	w19, lt
.L382:
	mov	x0, x20
	sbfiz	x19, x19, 2, 32
	bl	BsSkip
	cmp	w21, 12
	add	x0, x29, 96
	add	x19, x0, x19
	bhi	.L389
.L383:
	ldr	w0, [x19, -24]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L386:
	mov	w1, 3
	mov	x0, x20
	mov	w19, 2
	bl	BsSkip
	sbfiz	x19, x19, 2, 32
	cmp	w21, 12
	add	x0, x29, 96
	add	x19, x0, x19
	bls	.L383
.L389:
	ldr	w0, [x19, -48]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L388:
	mov	w1, 4
	mov	w19, 3
	cbz	w0, .L382
	mov	w19, w1
	b	.L382
	.size	VC1_DecMvmodeProgrP, .-VC1_DecMvmodeProgrP
	.align	3
.LC76:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeProgrB
	.type	VC1_DecMvmodeProgrB, %function
VC1_DecMvmodeProgrB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	ldr	x19, [sp, 16]
	add	x1, x29, 48
	mov	w2, 3
	add	x0, x1, x0, sxtw 2
	mov	w1, 1
	stp	w2, w1, [x29, 40]
	ldr	w0, [x0, -8]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_DecMvmodeProgrB, .-VC1_DecMvmodeProgrB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeInterB
	.type	VC1_DecMvmodeInterB, %function
VC1_DecMvmodeInterB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 3
	mov	x0, x20
	bl	BsShow
	str	wzr, [x29, 88]
	add	x1, x29, 72
	mov	w3, 1
	mov	w2, 2
	cmp	w0, w3
	stp	w2, wzr, [x29, 64]
	stp	xzr, xzr, [x1]
	str	w3, [x29, 72]
	mov	w1, 3
	stp	w1, w3, [x29, 56]
	stp	w2, w1, [x29, 80]
	ble	.L398
	cmp	w0, 4
	csinc	w1, w2, wzr, lt
	cset	w19, lt
.L393:
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 12
	sbfiz	x2, x19, 2, 32
	add	x0, x29, 96
	add	x2, x0, x2
	bhi	.L399
	ldr	w0, [x2, -24]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L399:
	ldr	w0, [x2, -40]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L398:
	mov	w19, w1
	cbz	w0, .L393
	mov	w19, w2
	b	.L393
	.size	VC1_DecMvmodeInterB, .-VC1_DecMvmodeInterB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmode2
	.type	VC1_DecMvmode2, %function
VC1_DecMvmode2:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 3
	mov	x0, x20
	bl	BsShow
	mov	w3, 1
	mov	w1, 3
	mov	w2, 2
	cmp	w0, w3
	stp	w1, w3, [x29, 48]
	stp	w2, wzr, [x29, 56]
	stp	w3, wzr, [x29, 64]
	stp	w2, w1, [x29, 72]
	ble	.L407
	cmp	w0, 4
	csinc	w1, w2, wzr, lt
	cset	w19, lt
.L402:
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 12
	sbfiz	x2, x19, 2, 32
	add	x0, x29, 80
	add	x2, x0, x2
	bhi	.L408
	ldr	w0, [x2, -16]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L408:
	ldr	w0, [x2, -32]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L407:
	mov	w19, w1
	cbz	w0, .L402
	mov	w19, w2
	b	.L402
	.size	VC1_DecMvmode2, .-VC1_DecMvmode2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecBfractionSMP
	.type	VC1_DecBfractionSMP, %function
VC1_DecBfractionSMP:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	x22, x2
	bl	_mcount
	ldr	x0, .LC78
	add	x1, x0, 248
	add	x8, x0, 304
	ldp	x4, x5, [x0, 128]
	ldr	w3, [x0, 184]
	ldr	x6, [x0, 144]
	stp	x4, x5, [x29, 48]
	ldr	x4, [x0, 176]
	ldr	w7, [x0, 152]
	str	x6, [x29, 64]
	str	x4, [x29, 96]
	ldr	x6, [x0, 240]
	ldp	x4, x5, [x0, 192]
	str	w3, [x29, 104]
	ldr	x3, [x0, 296]
	str	w7, [x29, 72]
	stp	x4, x5, [x29, 144]
	str	x6, [x29, 192]
	ldp	x4, x5, [x0, 208]
	ldp	x6, x7, [x0, 160]
	str	x3, [x29, 248]
	ldp	x2, x3, [x0, 224]
	add	x0, x29, 200
	stp	x6, x7, [x29, 80]
	ldp	x6, x7, [x1]
	stp	x6, x7, [x0]
	ldp	x6, x7, [x8]
	stp	x6, x7, [x29, 112]
	add	x6, x29, 216
	mov	x0, x21
	stp	x4, x5, [x29, 160]
	ldp	x4, x5, [x1, 16]
	stp	x4, x5, [x6]
	add	x4, x29, 232
	stp	x2, x3, [x29, 176]
	ldp	x2, x3, [x1, 32]
	stp	x2, x3, [x4]
	ldp	x2, x3, [x8, 16]
	mov	w1, 3
	stp	x2, x3, [x29, 128]
	bl	BsShow
	cmp	w0, 6
	mov	w19, w0
	bgt	.L410
	mov	w1, 3
	mov	x0, x21
	bl	BsSkip
	add	x0, x29, 256
	add	x0, x0, x19, sxtw 2
	ldr	w2, [x0, -208]
	ldr	w1, [x0, -176]
.L411:
	sub	w1, w1, #1
	add	x3, x29, 256
	mov	w0, w19
	add	x1, x3, x1, sxtw 2
	ldr	w1, [x1, -144]
	mul	w1, w1, w2
	str	w1, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L410:
	mov	w1, 7
	mov	x0, x21
	bl	BsGet
	and	w19, w0, 15
	cmp	w19, 15
	beq	.L414
	sub	w0, w0, #112
	add	x1, x29, 256
	add	w19, w19, 7
	add	x0, x1, x0, sxtw 2
	ldr	w2, [x0, -112]
	ldr	w1, [x0, -56]
	b	.L411
	.p2align 3
.L414:
	mov	w1, 4
	strb	w1, [x22]
	mov	w0, 22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.size	VC1_DecBfractionSMP, .-VC1_DecBfractionSMP
	.align	3
.LC78:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecBfraction
	.type	VC1_DecBfraction, %function
VC1_DecBfraction:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x19, .LC84
	add	x0, x19, 248
	ldr	w6, [x19, 152]
	ldr	x8, [x19, 176]
	str	w6, [x29, 72]
	add	x6, x29, 200
	ldr	w5, [x19, 184]
	ldr	x4, [x19, 240]
	str	x8, [x29, 96]
	add	x8, x29, 216
	ldp	x2, x3, [x19, 128]
	str	w5, [x29, 104]
	str	x4, [x29, 192]
	ldp	x4, x5, [x0]
	stp	x4, x5, [x6]
	stp	x2, x3, [x29, 48]
	ldp	x4, x5, [x0, 16]
	ldp	x2, x3, [x19, 160]
	add	x6, x19, 304
	ldr	x7, [x19, 144]
	stp	x4, x5, [x8]
	stp	x2, x3, [x29, 80]
	add	x4, x29, 232
	str	x7, [x29, 64]
	ldp	x2, x3, [x19, 192]
	stp	x2, x3, [x29, 144]
	ldp	x2, x3, [x19, 208]
	stp	x2, x3, [x29, 160]
	ldp	x2, x3, [x0, 32]
	stp	x2, x3, [x4]
	ldp	x2, x3, [x6]
	ldp	x0, x1, [x19, 224]
	ldr	x7, [x19, 296]
	stp	x2, x3, [x29, 112]
	ldp	x2, x3, [x6, 16]
	stp	x0, x1, [x29, 176]
	mov	w1, 3
	mov	x0, x22
	str	x7, [x29, 248]
	stp	x2, x3, [x29, 128]
	bl	BsShow
	cmp	w0, 6
	mov	w20, w0
	bgt	.L416
	mov	w1, 3
	mov	x0, x22
	bl	BsSkip
	add	x0, x29, 256
	add	x0, x0, x20, sxtw 2
	ldr	w4, [x0, -176]
	ldr	w1, [x0, -208]
	sub	w0, w4, #1
	cmp	w0, 7
	bhi	.L420
.L422:
	add	x2, x29, 256
	add	x0, x2, x0, sxtw 2
	ldr	w0, [x0, -144]
	mul	w0, w1, w0
.L421:
	str	w0, [x21]
.L418:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L416:
	mov	w1, 7
	mov	x0, x22
	bl	BsGet
	and	w20, w0, 15
	sub	w1, w20, #14
	add	w20, w20, 7
	cmp	w1, 1
	bls	.L418
	sub	w1, w0, #112
	cmp	w1, 13
	bhi	.L419
	add	x0, x29, 256
	add	x0, x0, x1, sxtw 2
	ldr	w4, [x0, -56]
	ldr	w1, [x0, -112]
	sub	w0, w4, #1
	cmp	w0, 7
	bls	.L422
.L420:
	ldr	x1, .LC88
	mov	w3, 3466
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L421
	.p2align 3
.L419:
	ldr	x1, .LC86
	mov	w4, w0
	mov	w3, 3456
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC88
	mov	w4, 0
	mov	w3, 3466
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L421
	.size	VC1_DecBfraction, .-VC1_DecBfraction
	.align	3
.LC84:
	.xword	.LANCHOR0
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_VopDQuant
	.type	VC1_VopDQuant, %function
VC1_VopDQuant:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	uxtb	w21, w1
	uxtb	w20, w2
	mov	x19, x3
	bl	_mcount
	cmp	w21, 2
	beq	.L441
	mov	w1, 1
	mov	x0, x22
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x19]
	beq	.L442
.L427:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L441:
	mov	w0, 1
	mov	w1, 3
	strb	w0, [x19, 3]
	strb	w0, [x19]
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 7
	strb	w0, [x19, 4]
	beq	.L443
	add	w20, w20, 1
	add	w0, w0, w20
	strb	w0, [x19, 8]
.L426:
	mov	w0, 1
	str	w0, [x19, 12]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L442:
	mov	w1, 2
	mov	x0, x22
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 1]
	cbnz	w1, .L429
	str	w21, [x19, 12]
.L430:
	ldr	w0, [x19]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L427
	mov	w0, 1
	mov	w1, 3
	strb	w0, [x19, 3]
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 7
	strb	w0, [x19, 4]
	beq	.L444
	add	w20, w20, 1
	add	w0, w0, w20
	strb	w0, [x19, 8]
	b	.L427
	.p2align 3
.L429:
	cmp	w1, 2
	beq	.L445
	cmp	w1, 1
	beq	.L446
	cmp	w1, 3
	beq	.L447
	str	wzr, [x19, 12]
	b	.L430
.L447:
	mov	w1, w21
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 10
	mov	w2, 11
	cmp	w0, wzr
	strb	w0, [x19, 2]
	csel	w0, w1, w2, ne
	str	w0, [x19, 12]
	b	.L430
	.p2align 3
.L443:
	mov	w1, 5
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 5]
	strb	w0, [x19, 8]
	b	.L426
.L445:
	mov	x0, x22
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x19, 6]
	add	w0, w1, 6
	str	w0, [x19, 12]
	b	.L430
.L446:
	mov	w1, 2
	mov	x0, x22
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x19, 7]
	add	w0, w1, 2
	str	w0, [x19, 12]
	b	.L430
.L444:
	mov	w1, 5
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 5]
	strb	w0, [x19, 8]
	b	.L427
	.size	VC1_VopDQuant, .-VC1_VopDQuant
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecNormDiff6Tile
	.type	VC1_DecNormDiff6Tile, %function
VC1_DecNormDiff6Tile:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x1
	mov	x20, x0
	mov	x0, x30
	mov	w22, 0
	bl	_mcount
	ldr	w24, [x23]
	b	.L449
	.p2align 3
.L459:
	mov	w22, w19
.L449:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 3
	mov	x0, x20
	cbnz	w21, .L458
	bl	BsGet
	cmp	w0, 1
	mov	w19, w0
	mov	w1, w0
	mov	x0, x20
	bgt	.L468
	bne	.L452
	bl	BsGet
	cbz	w0, .L453
	cbz	w22, .L459
.L465:
	str	w24, [x23]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L458:
	mov	w0, 0
.L450:
	eor	w1, w0, 63
	cmp	w22, wzr
	csel	w0, w1, w0, ne
	mov	w21, 1
	str	w0, [x23]
.L470:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L468:
	sub	w19, w19, #2
	mov	w0, 1
	lsl	w0, w0, w19
	b	.L450
	.p2align 3
.L452:
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	cmp	w0, 255
	beq	.L465
	ldr	x1, .LC94
	add	x1, x1, 488
	ldr	w0, [x1, w0, sxtw 2]
	b	.L450
	.p2align 3
.L453:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	ldr	x1, .LC94
	add	x1, x1, 360
	ldr	w1, [x1, w0, sxtw 2]
	cmp	w1, 2
	beq	.L469
	cmp	w1, 3
	beq	.L450
	str	w0, [x23]
	b	.L470
.L469:
	orr	w0, w0, 32
	b	.L450
	.size	VC1_DecNormDiff6Tile, .-VC1_DecNormDiff6Tile
	.align	3
.LC94:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvSeqHdr
	.type	VC1_Vfmw_ParseAdvSeqHdr, %function
VC1_Vfmw_ParseAdvSeqHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	bl	_mcount
	add	x19, x22, 16
	ldr	x3, .LC97
	mov	x2, 172
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 168]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	mov	w0, 2
	mov	w1, 3
	strb	w0, [x22, 16]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	uxth	w0, w0
	add	w2, w0, 1
	mov	w1, 12
	ubfiz	w2, w2, 1, 15
	mov	x0, x20
	strh	w2, [x19, 156]
	bl	BsGet
	uxth	w0, w0
	add	w2, w0, 1
	mov	w1, 1
	ubfiz	w2, w2, 1, 15
	mov	x0, x20
	strh	w2, [x19, 158]
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x19, 10]
	beq	.L485
	ldrh	w1, [x19, 156]
	ldrh	w0, [x19, 158]
	strh	w1, [x19, 160]
	strh	w0, [x19, 162]
.L478:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 23]
	beq	.L479
.L481:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 168]
	mov	w2, 1
	sub	w0, w0, w1
	str	w0, [x19, 168]
.L480:
	mov	w0, w2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L479:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 31
	strb	w0, [x19, 24]
	mov	w2, 0
	bhi	.L480
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 25]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 26]
	ldrb	w1, [x19, 24]
	cbz	w1, .L481
	mov	w21, 0
	.p2align 2
.L482:
	add	x23, x22, x21, sxtw 1
	mov	w1, 16
	mov	x0, x20
	add	w21, w21, 1
	bl	BsGet
	strh	w0, [x23, 44]
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	strh	w0, [x23, 108]
	ldrb	w0, [x19, 24]
	cmp	w0, w21
	bgt	.L482
	b	.L481
	.p2align 3
.L485:
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	mov	w1, 14
	strh	w0, [x19, 160]
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	mov	w1, w21
	strh	w0, [x19, 162]
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	beq	.L486
.L474:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	strb	w1, [x19, 15]
	beq	.L487
.L476:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 19]
	bne	.L478
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 20]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 22]
	b	.L478
	.p2align 3
.L487:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 16]
	cbnz	w0, .L477
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L476
	.p2align 3
.L486:
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 15
	strb	w0, [x19, 12]
	bne	.L474
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L474
.L477:
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	strh	w0, [x19, 164]
	b	.L476
	.size	VC1_Vfmw_ParseAdvSeqHdr, .-VC1_Vfmw_ParseAdvSeqHdr
	.align	3
.LC97:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvEntptHdr
	.type	VC1_Vfmw_ParseAdvEntptHdr, %function
VC1_Vfmw_ParseAdvEntptHdr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	add	x19, x21, 188
	ldr	x3, .LC98
	mov	x2, 60
	mov	w1, 0
	mov	x0, x19
	add	x22, x21, 16
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 56]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 188]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 10]
	ldrb	w0, [x22, 23]
	cmp	w0, 1
	beq	.L489
.L492:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	beq	.L509
.L507:
	ldrh	w0, [x19, 52]
.L494:
	ldrh	w1, [x19, 50]
	ldrh	w2, [x22, 156]
	cmp	w1, 15
	ccmp	w1, w2, 2, hi
	bls	.L495
	strh	w2, [x19, 50]
.L495:
	ldrh	w1, [x22, 158]
	cmp	w0, 15
	ccmp	w1, w0, 0, hi
	bcs	.L496
	strh	w1, [x19, 52]
.L496:
	ldrb	w1, [x19, 6]
	cmp	w1, 1
	beq	.L510
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 13]
	beq	.L511
.L498:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 15]
	beq	.L512
.L499:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 56]
	sub	w1, w0, w1
	str	w1, [x19, 56]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L489:
	ldrb	w0, [x22, 24]
	cbz	w0, .L492
	mov	w21, 0
	.p2align 2
.L493:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	add	x1, x19, x21, sxtw
	add	w21, w21, 1
	strb	w0, [x1, 17]
	ldrb	w0, [x22, 24]
	cmp	w0, w21
	bgt	.L493
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	bne	.L507
.L509:
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	ubfiz	w0, w0, 1, 15
	mov	w1, 12
	strh	w0, [x19, 50]
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	ubfiz	w0, w0, 1, 15
	strh	w0, [x19, 52]
	b	.L494
	.p2align 3
.L512:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L499
	.p2align 3
.L510:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 13]
	bne	.L498
	.p2align 2
.L511:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L498
	.size	VC1_Vfmw_ParseAdvEntptHdr, .-VC1_Vfmw_ParseAdvEntptHdr
	.align	3
.LC98:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecFcm
	.type	VC1_DecFcm, %function
VC1_DecFcm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	cmp	w0, 1
	mov	w19, w0
	ble	.L516
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L516:
	mov	w1, 1
	mov	x0, x20
	mov	w19, 0
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_DecFcm, .-VC1_DecFcm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecAdvPtype
	.type	VC1_DecAdvPtype, %function
VC1_DecAdvPtype:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	cmp	w0, 7
	ble	.L519
	cmp	w0, 11
	bgt	.L523
	mov	w1, 2
	mov	w20, w1
.L518:
	mov	x0, x19
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L523:
	cmp	w0, 13
	ble	.L521
	cmp	w0, 14
	mov	w1, 4
	beq	.L522
	mov	w20, 5
	b	.L518
	.p2align 3
.L519:
	mov	w1, 1
	mov	x0, x19
	mov	w20, w1
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L521:
	mov	w1, 3
	mov	w20, 0
	b	.L518
	.p2align 3
.L522:
	mov	w20, w1
	b	.L518
	.size	VC1_DecAdvPtype, .-VC1_DecAdvPtype
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecRefdist
	.type	VC1_DecRefdist, %function
VC1_DecRefdist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	cmp	w0, 23
	mov	w2, w0
	bgt	.L525
	mov	w1, 2
	mov	x0, x20
	asr	w19, w2, 3
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L525:
	cmp	w0, 27
	mov	w19, 3
	bgt	.L531
	mov	w1, w19
	mov	x0, x20
	bl	BsSkip
	mov	w0, w19
.L532:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L531:
	mov	w0, 5
	cmp	w2, 29
	mov	w19, 4
	csel	w19, w0, w19, gt
	mov	x0, x20
	mov	w1, w19
	bl	BsSkip
	mov	w0, w19
	b	.L532
	.size	VC1_DecRefdist, .-VC1_DecRefdist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecIntCompField
	.type	VC1_DecIntCompField, %function
VC1_DecIntCompField:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC99
	mov	w1, 2
	mov	x0, x19
	add	x2, x2, 552
	ldp	x4, x5, [x2]
	ldp	x2, x3, [x2, 16]
	stp	x4, x5, [x29, 32]
	stp	x2, x3, [x29, 48]
	bl	BsShow
	add	x1, x29, 64
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -32]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_DecIntCompField, .-VC1_DecIntCompField
	.align	3
.LC99:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_next_start_code
	.type	VC1_Vfmw_next_start_code, %function
VC1_Vfmw_next_start_code:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #3
	cmp	w21, wzr
	bgt	.L541
	b	.L538
	.p2align 3
.L544:
	bl	BsSkip
	cmp	w19, w21
	beq	.L538
.L541:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L544
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L538:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_next_start_code, .-VC1_Vfmw_next_start_code
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UserData
	.type	VC1_Vfmw_UserData, %function
VC1_Vfmw_UserData:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1_Vfmw_UserData, .-VC1_Vfmw_UserData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_RecordSlcStream
	.type	VC1_RecordSlcStream, %function
VC1_RecordSlcStream:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 20480
	mov	x21, x1
	mov	x23, x2
	bl	_mcount
	add	x1, x21, 536
	add	x5, x20, 3680
	ldr	w0, [x20, 3676]
	ldr	x4, [x22, 3136]
	uxtw	x21, w0
	lsl	x3, x21, 3
	sub	x3, x3, x21
	lsl	x3, x3, 3
	add	x19, x5, x3
	strb	w0, [x19, 16]
	ldr	w0, [x4, 32]
	ubfx	x0, x0, 3, 29
	add	x0, x23, x0
	str	x0, [x5, x3]
	ldr	w2, [x4, 32]
	and	w2, w2, 7
	str	w2, [x19, 24]
	ldr	w3, [x4, 24]
	ldr	w2, [x4, 32]
	lsl	w3, w3, 3
	sub	w3, w3, w2
	lsl	x2, x21, 2
	sub	x2, x2, x21
	str	w3, [x19, 28]
	add	x21, x1, x2, lsl 2
	bl	MEM_Vir2Phy
	add	x2, x22, 36864
	str	w0, [x19, 20]
	add	x0, x2, 1640
	ldr	w1, [x2, 1676]
	str	w1, [x19, 48]
	ldr	x1, [x2, 1648]
	cbz	x1, .L547
	ldr	w2, [x2, 1664]
	cbnz	w2, .L566
.L547:
	mov	x1, 0
	str	xzr, [x19, 8]
	stp	wzr, wzr, [x19, 36]
	str	wzr, [x19, 44]
	str	wzr, [x19, 52]
.L548:
	ldr	w4, [x20, 3592]
	ldr	w0, [x20, 3596]
	ldrb	w2, [x22, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L549
	add	w0, w0, 1
	ldr	w3, [x21, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x19, 32]
	cmp	w4, w3
	ccmp	w3, wzr, 4, cc
	bgt	.L567
.L550:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L552
	cbz	x1, .L553
	ldr	w0, [x19, 44]
	cmp	w0, wzr
	ble	.L552
.L553:
	ldr	w1, [x20, 3676]
	mov	w0, 1
	add	w1, w1, w0
	str	w1, [x20, 3676]
.L551:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L549:
	ldr	w3, [x21, 4]
	str	w3, [x19, 32]
	cmp	w4, w3
	bcs	.L550
	ldr	w2, [x21, 4]
	mov	w0, 1
	ldr	x1, .LC104
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L566:
	str	x1, [x19, 8]
	str	wzr, [x19, 40]
	ldr	w2, [x0, 32]
	lsl	w2, w2, 3
	str	w2, [x19, 44]
	ldr	w2, [x0, 24]
	str	w2, [x19, 36]
	ldr	w0, [x0, 40]
	str	w0, [x19, 52]
	b	.L548
	.p2align 3
.L567:
	ldr	x1, .LC102
	mov	w0, 1
	ldr	w4, [x20, 3596]
	ldr	w2, [x21, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L551
	.p2align 3
.L552:
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_RecordSlcStream, .-VC1_RecordSlcStream
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UpdateAdvSPS
	.type	VC1_Vfmw_UpdateAdvSPS, %function
VC1_Vfmw_UpdateAdvSPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	add	x21, x0, 8192
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrh	w1, [x19, 238]
	ldrh	w0, [x21, 2446]
	cmp	w0, w1
	beq	.L569
	add	x0, x20, 20480
	add	w1, w1, 15
	asr	w1, w1, 4
	str	w1, [x0, 3592]
	ldrh	w1, [x19, 238]
	str	w1, [x0, 3608]
	ldrh	w1, [x19, 240]
	ldrh	w2, [x21, 2448]
	cmp	w2, w1
	beq	.L570
.L571:
	add	w1, w1, 15
	asr	w1, w1, 4
	str	w1, [x0, 3596]
	ldrh	w1, [x19, 240]
	str	w1, [x0, 3612]
.L570:
	add	x1, x19, 16
	add	x0, x21, 2224
	add	x19, x19, 188
	mov	x2, 172
	add	x21, x21, 2396
	bl	memcpy
	ldp	x0, x1, [x19]
	stp	x0, x1, [x21]
	mov	w0, 1
	ldp	x2, x3, [x19, 16]
	stp	x2, x3, [x21, 16]
	ldp	x2, x3, [x19, 32]
	stp	x2, x3, [x21, 32]
	ldr	x1, [x19, 48]
	str	x1, [x21, 48]
	ldr	w1, [x19, 56]
	str	w1, [x21, 56]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L569:
	ldrh	w1, [x19, 240]
	ldrh	w0, [x21, 2448]
	cmp	w0, w1
	bne	.L576
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L576:
	add	x0, x20, 20480
	b	.L571
	.size	VC1_Vfmw_UpdateAdvSPS, .-VC1_Vfmw_UpdateAdvSPS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UpdataLastPicRNDCTRL
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL, %function
VC1_Vfmw_UpdataLastPicRNDCTRL:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrsb	w0, [x19, 3104]
	cbnz	w0, .L578
	mov	x0, x19
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
.L578:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL, .-VC1_Vfmw_UpdataLastPicRNDCTRL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_DecPQUANT
	.type	VC1_Vfmw_DecPQUANT, %function
VC1_Vfmw_DecPQUANT:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x1, .LC107
	mov	x2, 128
	add	x0, x29, 32
	add	x1, x1, 584
	bl	memcpy
	mov	w0, w19
	cbnz	w20, .L580
	add	x0, x29, 160
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, -128]
.L580:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 160
	ret
	.size	VC1_Vfmw_DecPQUANT, .-VC1_Vfmw_DecPQUANT
	.align	3
.LC107:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPIPicHdr
	.type	VC1_Vfmw_ParseSMPIPicHdr, %function
VC1_Vfmw_ParseSMPIPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x23, x1
	bl	_mcount
	add	x19, x21, 248
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	mov	w1, 0
	cbz	w22, .L583
	ldrb	w24, [x21, 14]
	mov	w1, w22
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L594
	strb	wzr, [x19, 7]
.L585:
	cmp	w24, 1
	beq	.L595
	strb	wzr, [x19, 8]
.L587:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L596
	strb	wzr, [x19, 9]
.L589:
	ldrb	w0, [x19, 3]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbz	w0, .L592
	ldrb	w0, [x21, 4]
	cmp	w0, 1
	beq	.L597
.L592:
	ldrb	w1, [x19, 10]
.L591:
	mov	x0, x23
	bl	VC1_SetCurPicResolutionInfo
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 20]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
.L583:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L594:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w24, [x21, 14]
	b	.L585
	.p2align 3
.L596:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L589
	.p2align 3
.L595:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L587
	.p2align 3
.L597:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 10]
	b	.L591
	.size	VC1_Vfmw_ParseSMPIPicHdr, .-VC1_Vfmw_ParseSMPIPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPPPicHdr
	.type	VC1_Vfmw_ParseSMPPPicHdr, %function
VC1_Vfmw_ParseSMPPPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x23, x1
	add	x19, x21, 248
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	cbz	w22, .L610
	ldrb	w24, [x21, 14]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L621
	strb	wzr, [x19, 7]
.L602:
	cmp	w24, 1
	beq	.L622
	strb	wzr, [x19, 8]
.L604:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L623
	strb	wzr, [x19, 9]
.L606:
	ldrb	w0, [x21, 4]
	cmp	w0, 1
	beq	.L607
	ldrb	w1, [x19, 10]
.L608:
	mov	x0, x23
	bl	VC1_SetCurPicResolutionInfo
	mov	x0, x20
	bl	BsPos
	mov	w2, w0
	ldr	x1, .LC109
	mov	w0, 18
	bl	dprint_vfmw
	ldrb	w1, [x19, 104]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 11]
	beq	.L624
.L609:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x23
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L610
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 15]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	ldrb	w1, [x21, 8]
	cbnz	w1, .L625
.L611:
	mov	x0, x20
	bl	BsPos
	mov	w2, w0
	ldr	x1, .LC111
	mov	w0, 18
	bl	dprint_vfmw
	ldrb	w1, [x21, 9]
	cmp	w1, 1
	beq	.L626
.L613:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L610:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L621:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w24, [x21, 14]
	b	.L602
	.p2align 3
.L625:
	ldrb	w2, [x19, 104]
	add	x3, x21, 272
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L611
	.p2align 3
.L624:
	ldrb	w1, [x19, 104]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 12]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L609
	.p2align 3
.L607:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 10]
	b	.L608
	.p2align 3
.L623:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L606
	.p2align 3
.L622:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L604
	.p2align 3
.L626:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 17]
	bne	.L613
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L613
	.size	VC1_Vfmw_ParseSMPPPicHdr, .-VC1_Vfmw_ParseSMPPPicHdr
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseMPBPicHdr
	.type	VC1_Vfmw_ParseMPBPicHdr, %function
VC1_Vfmw_ParseMPBPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x24, x1
	add	x19, x21, 248
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	cbz	w22, .L637
	ldrb	w23, [x21, 14]
	uxtb	w1, w0
	mov	w0, w23
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L649
	strb	wzr, [x19, 7]
.L631:
	cmp	w23, 1
	beq	.L650
	strb	wzr, [x19, 8]
.L633:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L651
	strb	wzr, [x19, 9]
.L635:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 3
	mov	w3, 0
	csinc	w0, w1, wzr, eq
	mov	x2, x21
	strb	w0, [x19, 11]
	mov	x1, x24
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L637
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 15]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	ldrb	w1, [x21, 8]
	cbnz	w1, .L652
.L638:
	ldrb	w1, [x21, 9]
	cmp	w1, 1
	beq	.L653
.L640:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L637:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L649:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w23, [x21, 14]
	b	.L631
	.p2align 3
.L652:
	ldrb	w2, [x19, 104]
	add	x3, x21, 272
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L638
	.p2align 3
.L651:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L635
	.p2align 3
.L650:
	mov	w1, w23
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L633
	.p2align 3
.L653:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 17]
	bne	.L640
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L640
	.size	VC1_Vfmw_ParseMPBPicHdr, .-VC1_Vfmw_ParseMPBPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPPicHdr
	.type	VC1_Vfmw_ParseSMPPicHdr, %function
VC1_Vfmw_ParseSMPPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	add	x19, x2, 248
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	x22, x2
	bl	_mcount
	ldrb	w23, [x19, 10]
	mov	x0, x21
	mov	w1, w23
	bl	VC1_SetCurPicResolutionInfo
	ldr	w0, [x20, 24]
	cmp	w0, 1
	ble	.L692
	ldr	x25, .LC112
	mov	x2, 112
	mov	w1, 0
	mov	x0, x19
	add	x24, x21, 36864
	ldr	x3, [x25, 96]
	blr	x3
	strb	w23, [x19, 10]
	ldr	x3, [x25, 96]
	add	x0, x21, 20480
	mov	x2, 14336
	mov	w1, 0
	add	x0, x0, 3680
	blr	x3
	ldr	x1, .LC114
	mov	w0, 18
	ldr	w2, [x24, 1632]
	bl	dprint_vfmw
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 88]
	ldrb	w0, [x22, 15]
	cbnz	w0, .L657
	ldrb	w2, [x22, 248]
.L658:
	ldr	x1, .LC116
	mov	w0, 18
	bl	dprint_vfmw
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	ldrb	w0, [x22, 12]
	cbnz	w0, .L693
.L659:
	ldrb	w0, [x22, 13]
	mov	w1, 1
	cbnz	w0, .L660
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	cset	w0, ne
	strb	w0, [x19, 3]
.L661:
	strb	w0, [x21, 2]
	strb	wzr, [x21, 4]
	ldrb	w0, [x19, 3]
	cmp	w0, 4
	bhi	.L690
	ldr	x1, .LC117
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx666
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx666:
	.section	.rodata
	.align	0
	.align	2
.L666:
	.byte	(.L665 - .Lrtx666) / 4
	.byte	(.L667 - .Lrtx666) / 4
	.byte	(.L668 - .Lrtx666) / 4
	.byte	(.L690 - .Lrtx666) / 4
	.byte	(.L669 - .Lrtx666) / 4
	.text
	.p2align 3
.L667:
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPPPicHdr
	mov	w21, w0
.L670:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 88]
	sub	w0, w0, w1
	str	w0, [x19, 88]
	mov	x0, x20
	ldr	w19, [x24, 1668]
	bl	BsPos
	lsl	w19, w19, 3
	sub	w19, w19, w0
	mov	w0, w21
	cmp	w19, wzr
	bgt	.L683
	ldr	x1, .LC123
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L690:
	mov	w0, 0
.L683:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L692:
	mov	w0, 5
	strb	w0, [x19, 3]
	strb	w0, [x21, 2]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L660:
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	beq	.L694
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	beq	.L695
	mov	w0, 2
	add	x2, x22, 251
	strb	w0, [x19, 3]
	add	x1, x22, 356
	mov	x0, x20
	bl	VC1_DecBfractionSMP
	uxtb	w0, w0
	cmp	w0, 21
	strb	w0, [x19, 4]
	beq	.L690
	ldrb	w0, [x19, 3]
	b	.L661
	.p2align 3
.L657:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w2, w0
	strb	w2, [x22, 248]
	b	.L658
	.p2align 3
.L694:
	strb	w0, [x19, 3]
	b	.L661
	.p2align 3
.L669:
	ldrb	w23, [x21, 3120]
	cmp	w23, 1
	bne	.L690
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPIPicHdr
	cmp	w0, 1
	mov	w21, w0
	beq	.L670
	ldr	x1, .LC121
	mov	w0, w23
	bl	dprint_vfmw
	b	.L670
	.p2align 3
.L668:
	ldrb	w23, [x21, 3120]
	cmp	w23, 1
	bne	.L690
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseMPBPicHdr
	cmp	w0, 1
	mov	w21, w0
	beq	.L670
	ldr	x1, .LC119
	mov	w0, w23
	bl	dprint_vfmw
	b	.L670
	.p2align 3
.L665:
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPIPicHdr
	mov	w21, w0
	b	.L670
	.p2align 3
.L693:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	b	.L659
	.p2align 3
.L695:
	strb	wzr, [x19, 3]
	mov	w0, 0
	b	.L661
	.size	VC1_Vfmw_ParseSMPPicHdr, .-VC1_Vfmw_ParseSMPPicHdr
	.align	3
.LC112:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC117:
	.xword	.L666
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvIPicHdr
	.type	VC1_Vfmw_ParseAdvIPicHdr, %function
VC1_Vfmw_ParseAdvIPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	add	x23, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w1, [x23, 7]
	cmp	w1, 1
	beq	.L712
.L697:
	ldr	w0, [x19, 44]
	cbnz	w0, .L698
	ldrb	w1, [x23, 9]
	cmp	w1, 1
	beq	.L713
.L698:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L706
	add	x26, x21, 188
	ldrb	w24, [x26, 10]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L714
	strb	wzr, [x19, 3]
.L702:
	cmp	w24, 1
	beq	.L715
	strb	wzr, [x19, 11]
.L704:
	ldrb	w0, [x23, 5]
	cmp	w0, 1
	beq	.L716
.L705:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L706
	mov	x0, x20
	mov	w22, 1
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 23]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	ldrb	w1, [x26, 7]
	cbz	w1, .L700
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L706:
	mov	w22, 0
.L700:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L714:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x26, 10]
	b	.L702
	.p2align 3
.L713:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	b	.L698
	.p2align 3
.L712:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L697
	.p2align 3
.L716:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L705
	.p2align 3
.L715:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L704
	.size	VC1_Vfmw_ParseAdvIPicHdr, .-VC1_Vfmw_ParseAdvIPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPPicHdr
	.type	VC1_Vfmw_ParseAdvPPicHdr, %function
VC1_Vfmw_ParseAdvPPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x26, x1
	bl	_mcount
	add	x22, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L718
	ldr	w0, [x19, 44]
	cmp	w0, 2
	beq	.L718
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	beq	.L754
.L720:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w23, w0
	strb	w23, [x19, 10]
	cbz	w23, .L734
	add	x24, x21, 188
	ldrb	w25, [x24, 10]
	uxtb	w1, w0
	mov	w0, w25
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w23, 8
	bls	.L755
	strb	wzr, [x19, 3]
.L724:
	cmp	w25, 1
	beq	.L756
	strb	wzr, [x19, 11]
.L726:
	ldrb	w0, [x22, 5]
	cmp	w0, 1
	beq	.L757
.L727:
	ldrb	w0, [x24, 6]
	cmp	w0, 1
	beq	.L758
.L728:
	ldr	w0, [x19, 44]
	cbz	w0, .L759
	ldrb	w0, [x24, 12]
	cmp	w0, 1
	beq	.L760
	strb	wzr, [x19, 25]
.L732:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 26]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 120]
	beq	.L761
.L733:
	strb	wzr, [x19, 34]
.L730:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x26
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L734
	ldr	w1, [x19, 44]
	cmp	w1, 2
	beq	.L762
.L735:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	ldr	w1, [x19, 44]
	cbnz	w1, .L736
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
.L737:
	ldr	w22, [x19, 44]
	strb	w0, [x19, 19]
	cmp	w22, 2
	beq	.L763
.L738:
	ldrb	w1, [x24, 7]
	cbnz	w1, .L764
.L740:
	ldrb	w1, [x24, 8]
	cmp	w1, 1
	beq	.L765
.L742:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L734:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L718:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	bne	.L720
.L754:
	ldr	w0, [x19, 44]
	cbnz	w0, .L720
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	b	.L720
	.p2align 3
.L736:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	b	.L737
	.p2align 3
.L755:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w25, [x24, 10]
	b	.L724
	.p2align 3
.L761:
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	b	.L733
	.p2align 3
.L759:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 14]
	bne	.L730
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 15]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	b	.L730
	.p2align 3
.L764:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L740
	.p2align 3
.L756:
	mov	w1, w25
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L726
	.p2align 3
.L758:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L728
	.p2align 3
.L757:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L727
	.p2align 3
.L762:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	b	.L735
	.p2align 3
.L763:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 28]
	ldrb	w1, [x19, 26]
	mov	w0, 0
	cmp	w1, 1
	beq	.L766
	strb	w0, [x19, 29]
	b	.L738
	.p2align 3
.L765:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L742
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L742
	.p2align 3
.L760:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L732
.L766:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 29]
	b	.L738
	.size	VC1_Vfmw_ParseAdvPPicHdr, .-VC1_Vfmw_ParseAdvPPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvBPicHdr
	.type	VC1_Vfmw_ParseAdvBPicHdr, %function
VC1_Vfmw_ParseAdvBPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	add	x22, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L768
	ldr	w2, [x19, 44]
	cmp	w2, 2
	beq	.L768
.L769:
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	beq	.L809
.L770:
	cbnz	w2, .L774
	add	x1, x21, 508
	mov	x0, x20
	bl	VC1_DecBfraction
	uxtb	w0, w0
	cmp	w0, 21
	strb	w0, [x19, 2]
	beq	.L772
.L774:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w23, w0
	strb	w23, [x19, 10]
	cbz	w23, .L772
	add	x24, x21, 188
	ldrb	w26, [x24, 10]
	uxtb	w1, w0
	mov	w0, w26
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w23, 8
	bls	.L810
	strb	wzr, [x19, 3]
.L777:
	cmp	w26, 1
	beq	.L811
	strb	wzr, [x19, 11]
.L779:
	ldrb	w0, [x22, 5]
	cmp	w0, 1
	beq	.L812
.L780:
	ldr	w0, [x19, 44]
	cmp	w0, 2
	beq	.L813
.L781:
	ldrb	w0, [x24, 6]
	cmp	w0, 1
	beq	.L814
.L782:
	ldr	w0, [x19, 44]
	cbz	w0, .L815
	ldrb	w0, [x24, 12]
	cmp	w0, 1
	beq	.L816
.L786:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 120]
.L785:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L772
	ldr	w1, [x19, 44]
	cmp	w1, 2
	beq	.L817
.L787:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	ldr	w1, [x19, 44]
	cbnz	w1, .L788
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
.L789:
	ldr	w22, [x19, 44]
	strb	w0, [x19, 19]
	cmp	w22, 2
	beq	.L818
.L790:
	ldrb	w1, [x24, 7]
	cbnz	w1, .L819
.L791:
	ldrb	w1, [x24, 8]
	cmp	w1, 1
	beq	.L820
.L793:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L772:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L809:
	cbnz	w2, .L774
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	ldr	w2, [x19, 44]
	b	.L770
	.p2align 3
.L768:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	ldr	w2, [x19, 44]
	b	.L769
	.p2align 3
.L788:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	b	.L789
	.p2align 3
.L810:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w26, [x24, 10]
	b	.L777
	.p2align 3
.L815:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 3
	csinc	w1, w1, wzr, eq
	strb	w1, [x19, 14]
	b	.L785
	.p2align 3
.L819:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L791
	.p2align 3
.L814:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L782
	.p2align 3
.L813:
	add	x1, x21, 508
	mov	x0, x20
	bl	VC1_DecBfraction
	strb	w0, [x19, 2]
	b	.L781
	.p2align 3
.L812:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L780
	.p2align 3
.L811:
	mov	w1, w26
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L779
	.p2align 3
.L820:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L793
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L793
	.p2align 3
.L818:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 28]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	b	.L790
	.p2align 3
.L817:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	b	.L787
	.p2align 3
.L816:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L786
	.size	VC1_Vfmw_ParseAdvBPicHdr, .-VC1_Vfmw_ParseAdvBPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvFramePicHdr
	.type	VC1_Vfmw_ParseAdvFramePicHdr, %function
VC1_Vfmw_ParseAdvFramePicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x21, x2
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	cmp	w0, 7
	ble	.L842
	cmp	w0, 11
	bgt	.L854
	mov	w24, 2
	mov	w1, w24
.L822:
	add	x20, x21, 360
	mov	x0, x19
	add	x22, x21, 16
	bl	BsSkip
	strb	w24, [x20, 1]
	ldrb	w0, [x23, 3545]
	strb	w0, [x23, 2]
	ldrb	w0, [x22, 8]
	cbnz	w0, .L855
.L823:
	ldrb	w0, [x22, 6]
	cbz	w0, .L824
	ldrb	w0, [x22, 7]
	cbnz	w0, .L825
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 6]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	ldrb	w0, [x22, 6]
	beq	.L829
.L858:
	cmp	w0, 1
	bne	.L828
	ldrb	w0, [x20, 6]
	add	w0, w0, 1
	str	w0, [x20, 144]
.L831:
	ldrb	w1, [x21, 190]
	cmp	w1, 1
	beq	.L832
.L840:
	ldrb	w0, [x20, 1]
	cmp	w0, 5
	bls	.L856
.L846:
	mov	w0, 0
	b	.L833
	.p2align 3
.L856:
	ldr	x1, .LC124
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx835
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx835:
	.section	.rodata
	.align	0
	.align	2
.L835:
	.byte	(.L838 - .Lrtx835) / 4
	.byte	(.L836 - .Lrtx835) / 4
	.byte	(.L837 - .Lrtx835) / 4
	.byte	(.L846 - .Lrtx835) / 4
	.byte	(.L838 - .Lrtx835) / 4
	.byte	(.L839 - .Lrtx835) / 4
	.text
	.p2align 3
.L854:
	cmp	w0, 13
	ble	.L844
	cmp	w0, 14
	beq	.L857
	mov	w24, 5
	mov	w1, 4
	b	.L822
	.p2align 3
.L838:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvIPicHdr
.L833:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L824:
	mov	w0, 1
	strb	w0, [x20, 4]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L827
.L828:
	mov	w0, 1
	str	w0, [x20, 144]
	ldrb	w1, [x21, 190]
	cmp	w1, 1
	bne	.L840
.L832:
	mov	x0, x19
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 7]
	bne	.L840
	ldr	w0, [x20, 144]
	cmp	w0, wzr
	ble	.L840
	mov	w24, 0
	.p2align 2
.L841:
	add	x22, x21, x24, sxtw 2
	mov	w1, 18
	mov	x0, x19
	add	w24, w24, 1
	bl	BsGet
	str	w0, [x22, 412]
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 428]
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 444]
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 460]
	ldr	w0, [x20, 144]
	cmp	w0, w24
	bgt	.L841
	b	.L840
	.p2align 3
.L827:
	mov	w0, 2
	str	w0, [x20, 144]
	b	.L831
	.p2align 3
.L842:
	mov	w24, 1
	mov	w1, w24
	b	.L822
	.p2align 3
.L855:
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 48]
	b	.L823
	.p2align 3
.L825:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 5]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	ldrb	w0, [x22, 6]
	bne	.L858
.L829:
	cmp	w0, 1
	bne	.L827
	ldrb	w0, [x20, 5]
	add	w0, w0, 2
	str	w0, [x20, 144]
	b	.L831
	.p2align 3
.L836:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvPPicHdr
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L839:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L837:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvBPicHdr
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L844:
	mov	w24, 0
	mov	w1, 3
	b	.L822
	.p2align 3
.L857:
	mov	w24, 4
	mov	w1, w24
	b	.L822
	.size	VC1_Vfmw_ParseAdvFramePicHdr, .-VC1_Vfmw_ParseAdvFramePicHdr
	.align	3
.LC124:
	.xword	.L835
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvIFieldHdr
	.type	VC1_Vfmw_ParseAdvIFieldHdr, %function
VC1_Vfmw_ParseAdvIFieldHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	add	x19, x21, 360
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L867
	add	x24, x21, 188
	ldrb	w23, [x24, 10]
	uxtb	w1, w0
	mov	w0, w23
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L873
	strb	wzr, [x19, 3]
.L863:
	cmp	w23, 1
	beq	.L874
	strb	wzr, [x19, 11]
.L865:
	ldrb	w0, [x21, 21]
	cmp	w0, 1
	beq	.L875
.L866:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L867
	mov	x0, x20
	mov	w22, 1
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 23]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	ldrb	w1, [x24, 7]
	cbz	w1, .L861
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L867:
	mov	w22, 0
.L861:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L873:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w23, [x24, 10]
	b	.L863
	.p2align 3
.L875:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L866
	.p2align 3
.L874:
	mov	w1, w23
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L865
	.size	VC1_Vfmw_ParseAdvIFieldHdr, .-VC1_Vfmw_ParseAdvIFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPFieldHdr
	.type	VC1_Vfmw_ParseAdvPFieldHdr, %function
VC1_Vfmw_ParseAdvPFieldHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x2
	add	x19, x23, 360
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	mov	w1, 0
	cbz	w22, .L877
	add	x21, x23, 188
	ldrb	w24, [x21, 10]
	mov	w1, w22
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L904
	strb	wzr, [x19, 3]
.L879:
	cmp	w24, 1
	beq	.L905
	strb	wzr, [x19, 11]
.L881:
	ldrb	w0, [x23, 21]
	cmp	w0, 1
	beq	.L906
.L882:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 32]
	cbz	w0, .L907
.L883:
	ldrb	w0, [x21, 6]
	cmp	w0, 1
	beq	.L908
.L884:
	ldrb	w0, [x21, 12]
	cmp	w0, 1
	beq	.L909
.L885:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 14]
	beq	.L910
.L887:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	ldrb	w1, [x19, 32]
	cbnz	w1, .L889
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 3
	strb	w0, [x19, 18]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbz	w1, .L891
.L913:
	ldrh	w0, [x19, 14]
	cmp	w0, 4
	beq	.L891
	ldrb	w1, [x21, 7]
	cbnz	w1, .L911
.L893:
	ldrb	w1, [x21, 8]
	cmp	w1, 1
	beq	.L912
.L895:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
.L877:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L889:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 3
	strb	w0, [x19, 18]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbnz	w1, .L913
.L891:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	ldrb	w1, [x21, 7]
	cbz	w1, .L893
.L911:
	ldrb	w2, [x19, 116]
	add	x3, x23, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L893
	.p2align 3
.L904:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x21, 10]
	b	.L879
	.p2align 3
.L907:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	cset	w0, eq
	strb	w0, [x19, 33]
	b	.L883
	.p2align 3
.L910:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 15]
	mov	x0, x20
	bl	VC1_DecIntCompField
	str	w0, [x19, 128]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	ldr	w1, [x19, 128]
	cbnz	w1, .L887
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 132]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 136]
	b	.L887
	.p2align 3
.L909:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L885
	.p2align 3
.L912:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L895
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L895
	.p2align 3
.L908:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L884
	.p2align 3
.L906:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L882
	.p2align 3
.L905:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L881
	.size	VC1_Vfmw_ParseAdvPFieldHdr, .-VC1_Vfmw_ParseAdvPFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvBFieldHdr
	.type	VC1_Vfmw_ParseAdvBFieldHdr, %function
VC1_Vfmw_ParseAdvBFieldHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x19, x2, 360
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	mov	w0, 1
	mov	w1, 5
	strb	w0, [x19, 32]
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L924
	add	x23, x21, 188
	ldrb	w24, [x23, 10]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L936
	strb	wzr, [x19, 3]
.L918:
	cmp	w24, 1
	beq	.L937
	strb	wzr, [x19, 11]
.L920:
	ldrb	w0, [x21, 21]
	cmp	w0, 1
	beq	.L938
.L921:
	ldrb	w0, [x23, 6]
	cmp	w0, 1
	beq	.L939
.L922:
	ldrb	w0, [x23, 12]
	cmp	w0, 1
	beq	.L940
.L923:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeInterB
	strb	w0, [x19, 14]
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L924
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbz	w1, .L941
.L925:
	ldrb	w1, [x23, 7]
	cbnz	w1, .L942
.L926:
	ldrb	w1, [x23, 8]
	cmp	w1, 1
	beq	.L943
.L928:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L924:
	mov	w1, 0
	ldr	x25, [sp, 64]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L936:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x23, 10]
	b	.L918
	.p2align 3
.L942:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L926
	.p2align 3
.L941:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	b	.L925
	.p2align 3
.L940:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L923
	.p2align 3
.L939:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L922
	.p2align 3
.L938:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L921
	.p2align 3
.L937:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L920
	.p2align 3
.L943:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L928
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L928
	.size	VC1_Vfmw_ParseAdvBFieldHdr, .-VC1_Vfmw_ParseAdvBFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvFieldPicHdr
	.type	VC1_Vfmw_ParseAdvFieldPicHdr, %function
VC1_Vfmw_ParseAdvFieldPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x1
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	bl	_mcount
	ldrb	w0, [x20, 8]
	cbz	w0, .L945
	add	x0, x20, 20480
	ldr	w0, [x0, 3676]
	cbnz	w0, .L945
	add	x19, x22, 360
	ldr	w0, [x19, 156]
	strb	w0, [x19, 1]
	ldrb	w0, [x20, 3545]
	strb	w0, [x20, 2]
.L964:
	ldrb	w0, [x19, 1]
	cmp	w0, 4
	bls	.L985
.L973:
	ldrb	w1, [x19, 4]
	mov	w0, 0
	cbz	w1, .L971
.L990:
	ldrb	w1, [x20, 8]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 41]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L945:
	mov	w1, 3
	mov	x0, x21
	add	x19, x22, 360
	add	x23, x22, 16
	bl	BsGet
	sbfiz	x1, x0, 3, 32
	ldr	x2, .LC125
	str	w0, [x19, 124]
	add	x0, x2, x1
	ldr	w1, [x2, x1]
	ldr	w0, [x0, 4]
	stp	w1, w0, [x19, 152]
	uxtb	w1, w1
	ldrb	w2, [x20, 8]
	uxtb	w0, w0
	cmp	w2, wzr
	csel	w0, w0, w1, ne
	strb	w0, [x19, 1]
	ldrb	w0, [x20, 3545]
	strb	w0, [x20, 2]
	ldrb	w0, [x23, 8]
	cbnz	w0, .L986
	ldrb	w0, [x23, 6]
	cbnz	w0, .L987
.L950:
	mov	w0, 1
	strb	w0, [x19, 4]
	ldrb	w0, [x23, 7]
	cmp	w0, 1
	beq	.L953
.L954:
	mov	w0, 1
	str	w0, [x19, 144]
.L957:
	add	x23, x22, 188
	ldrb	w1, [x23, 2]
	cmp	w1, 1
	beq	.L958
.L961:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x22, 360]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 8]
	ldrb	w0, [x23, 3]
	cmp	w0, 1
	beq	.L988
.L960:
	ldr	w0, [x19, 124]
	cmp	w0, 3
	ble	.L964
.L965:
	add	x1, x22, 508
	mov	x0, x21
	bl	VC1_DecBfraction
	strb	w0, [x19, 2]
	ldrb	w0, [x19, 1]
	cmp	w0, 4
	bhi	.L973
	.p2align 2
.L985:
	ldr	x1, .LC126
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx968
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx968:
	.section	.rodata
	.align	0
	.align	2
.L968:
	.byte	(.L967 - .Lrtx968) / 4
	.byte	(.L969 - .Lrtx968) / 4
	.byte	(.L970 - .Lrtx968) / 4
	.byte	(.L973 - .Lrtx968) / 4
	.byte	(.L967 - .Lrtx968) / 4
	.text
	.p2align 3
.L987:
	ldrb	w0, [x23, 7]
	cbz	w0, .L989
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 5]
.L952:
	ldrb	w0, [x23, 7]
	cmp	w0, 1
	ldrb	w0, [x23, 6]
	beq	.L955
	cmp	w0, 1
	bne	.L954
	ldrb	w0, [x19, 6]
	add	w0, w0, 1
	str	w0, [x19, 144]
	b	.L957
	.p2align 3
.L970:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvBFieldHdr
.L966:
	ldrb	w1, [x19, 4]
	cbnz	w1, .L990
.L971:
	ldrb	w1, [x20, 8]
	cmp	w1, 1
	cset	w1, ne
	strb	w1, [x19, 41]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L969:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvPFieldHdr
	b	.L966
	.p2align 3
.L967:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvIFieldHdr
	b	.L966
	.p2align 3
.L986:
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	str	w0, [x19, 48]
	ldrb	w0, [x23, 6]
	cbz	w0, .L950
	b	.L987
	.p2align 3
.L989:
	mov	w1, 2
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 6]
	b	.L952
	.p2align 3
.L988:
	ldr	w0, [x19, 124]
	cmp	w0, 3
	bgt	.L965
	mov	x0, x21
	bl	VC1_DecRefdist
	strb	w0, [x19, 31]
	b	.L960
	.p2align 3
.L953:
	mov	w0, 2
	str	w0, [x19, 144]
	b	.L957
	.p2align 3
.L955:
	cmp	w0, 1
	bne	.L953
	ldrb	w0, [x19, 5]
	add	w0, w0, 2
	str	w0, [x19, 144]
	b	.L957
	.p2align 3
.L958:
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 7]
	bne	.L961
	ldr	w0, [x19, 144]
	cmp	w0, wzr
	ble	.L961
	mov	w25, 0
	.p2align 2
.L962:
	add	x24, x22, x25, sxtw 2
	mov	w1, 18
	mov	x0, x21
	add	w25, w25, 1
	bl	BsGet
	str	w0, [x24, 412]
	mov	w1, 18
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 428]
	mov	w1, 14
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 444]
	mov	w1, 14
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 460]
	ldr	w0, [x19, 144]
	cmp	w0, w25
	bgt	.L962
	b	.L961
	.size	VC1_Vfmw_ParseAdvFieldPicHdr, .-VC1_Vfmw_ParseAdvFieldPicHdr
	.align	3
.LC125:
	.xword	.LANCHOR1
	.align	3
.LC126:
	.xword	.L968
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPicHdr
	.type	VC1_Vfmw_ParseAdvPicHdr, %function
VC1_Vfmw_ParseAdvPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	add	x2, x19, 20480
	add	x0, x19, 36864
	ldr	w1, [x2, 3592]
	str	w1, [x0, 1712]
	lsl	w4, w1, 4
	ldr	w3, [x2, 3596]
	str	w3, [x0, 1716]
	str	w4, [x0, 1704]
	lsl	w4, w3, 4
	mul	w1, w1, w3
	str	w1, [x0, 1720]
	str	w4, [x0, 1708]
	ldrb	w0, [x19, 8]
	cbz	w0, .L992
	ldr	w0, [x2, 3676]
	cbz	w0, .L1002
.L992:
	ldrb	w23, [x20, 23]
	cmp	w23, 1
	beq	.L1003
	mov	w1, 0
	mov	w0, 0
.L994:
	str	w0, [x20, 404]
	mov	x2, x20
	cbz	w1, .L1004
.L996:
	mov	x1, x19
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvFieldPicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1002:
	ldr	w1, [x20, 404]
	mov	x2, x20
	and	w1, w1, -3
	cbnz	w1, .L996
.L1004:
	mov	x1, x19
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvFramePicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1003:
	mov	w1, 2
	mov	x0, x21
	bl	BsShow
	cmp	w0, 1
	mov	w22, w0
	ble	.L1005
	mov	w1, 2
	mov	x0, x21
	bl	BsSkip
	and	w1, w22, -3
	mov	w0, w22
	b	.L994
	.p2align 3
.L1005:
	mov	w1, w23
	mov	x0, x21
	bl	BsSkip
	mov	w1, 0
	mov	w0, 0
	b	.L994
	.size	VC1_Vfmw_ParseAdvPicHdr, .-VC1_Vfmw_ParseAdvPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvSlcHdr
	.type	VC1_Vfmw_ParseAdvSlcHdr, %function
VC1_Vfmw_ParseAdvSlcHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	x21, x2
	bl	_mcount
	add	x2, x22, 20480
	mov	w1, 9
	mov	x0, x20
	ldr	w19, [x2, 3676]
	bl	BsGet
	mov	w1, 1
	uxtw	x19, w19
	lsl	x2, x19, 2
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	str	w0, [x19, 540]
	mov	x0, x20
	bl	BsGet
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 536]
	beq	.L1009
	mov	w0, 1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1009:
	add	x19, x22, 4096
	add	x4, x21, 188
	add	x3, x19, 2884
	mov	x2, 172
	add	x23, x19, 2696
	ldp	x0, x1, [x4]
	stp	x0, x1, [x3]
	add	x1, x21, 16
	add	x0, x19, 2712
	ldp	x6, x7, [x4, 16]
	stp	x6, x7, [x3, 16]
	ldp	x6, x7, [x4, 32]
	stp	x6, x7, [x3, 32]
	ldr	x5, [x21, 236]
	str	x5, [x3, 48]
	ldr	w4, [x21, 244]
	str	w4, [x22, 7036]
	bl	memcpy
	add	x1, x21, 360
	mov	x2, 176
	add	x0, x19, 3056
	bl	memcpy
	mov	x2, x23
	mov	x1, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseAdvPicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_Vfmw_ParseAdvSlcHdr, .-VC1_Vfmw_ParseAdvSlcHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ClearCurPacket
	.type	VC1_ClearCurPacket, %function
VC1_ClearCurPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 36]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldrsb	w0, [x19, 16]
	cmp	w0, 1
	beq	.L1011
	ldr	w1, [x19, 40]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
.L1011:
	ldr	x3, .LC127
	mov	x2, 48
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_ClearCurPacket, .-VC1_ClearCurPacket
	.align	3
.LC127:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ClearCurPic
	.type	VC1_ClearCurPic, %function
VC1_ClearCurPic:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	ldrsb	w0, [x22, 3104]
	cbz	w0, .L1016
	add	x24, x22, 20480
	mov	w20, 0
	ldr	w0, [x24, 3676]
	cbnz	w0, .L1026
	b	.L1015
	.p2align 3
.L1019:
	ldr	w0, [x24, 3676]
	cmp	w0, w20
	bls	.L1015
.L1026:
	sxtw	x19, w20
	mov	w0, w23
	lsl	x1, x19, 3
	add	w20, w20, 1
	sub	x19, x1, x19
	add	x19, x22, x19, lsl 3
	add	x21, x19, 20480
	ldr	w1, [x21, 3728]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 24168]
	cbz	x0, .L1019
	ldr	w0, [x21, 3716]
	cbz	w0, .L1019
	ldr	w1, [x21, 3732]
	mov	w0, w23
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x24, 3676]
	cmp	w0, w20
	bhi	.L1026
.L1015:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1016:
	add	x1, x22, 36864
	mov	w0, w23
	add	x1, x1, 1640
	bl	VC1_ClearCurPacket
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_ClearCurPic, .-VC1_ClearCurPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_VDMPostProc
	.type	VC1DEC_VDMPostProc, %function
VC1DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x20, x21, 12288
	bl	_mcount
	add	x23, x20, 2520
	ldr	x2, [x21, 8]
	add	x1, x23, 36864
	add	x19, x21, 53248
	add	x24, x23, 20480
	mov	x0, x23
	ldrb	w3, [x2, 75]
	strb	w3, [x1, 1769]
	ldr	w2, [x2, 14600]
	str	w2, [x1, 1772]
	ldr	w1, [x19, 848]
	bl	VC1_ClearCurPic
	ldr	w1, [x24, 3668]
	ldr	w0, [x19, 848]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	ldr	w1, [x24, 3664]
	ldr	w0, [x19, 848]
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	ldr	w1, [x24, 3660]
	ldr	w0, [x19, 848]
	bl	FSP_GetFsImagePtr
	cbz	x23, .L1063
	tbnz	w22, #31, .L1050
	mov	w0, 100
	cmp	w22, w0
	csel	w22, w22, w0, le
.L1033:
	mov	x0, x21
	str	w22, [x23, 152]
	bl	VC1_SetImgFormat
	ldrsb	w1, [x20, 2523]
	cmp	w1, 3
	beq	.L1064
.L1034:
	str	xzr, [x23, 544]
	str	xzr, [x23, 552]
	ldr	x0, [x21]
	ldr	w0, [x0, 24]
	cbz	w0, .L1065
	add	x0, x20, 2520
	mov	w24, 0
	add	x0, x0, 20480
	ldr	w1, [x0, 3668]
	str	w1, [x0, 3672]
.L1038:
	add	x23, x20, 2520
	cmn	w1, #1
	add	x0, x23, 36864
	ldr	w2, [x0, 1632]
	add	w2, w2, 1
	str	w2, [x0, 1632]
	beq	.L1039
.L1069:
	ldr	w0, [x19, 848]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L1066
	ldr	w2, [x0, 152]
	cbz	w2, .L1041
	ldr	x0, [x21]
	ldr	w3, [x0, 4]
	cmp	w2, w3
	bhi	.L1042
.L1041:
	add	x23, x20, 2520
	ldr	w0, [x19, 848]
	add	x25, x23, 20480
	ldr	w26, [x25, 3672]
	mov	w1, w26
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC133
	mov	w2, w26
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x19, 848]
	mov	w2, 1
	ldr	w1, [x25, 3672]
	bl	FSP_SetDisplay
	cbnz	w24, .L1067
	ldr	x1, [x23, 24040]
	mov	w2, 1
	mov	w0, 2
	strb	w2, [x1, 1]
	strb	w0, [x23, 1]
.L1044:
	ldr	w0, [x19, 848]
	mov	x4, x22
	add	x3, x19, 240
	mov	x2, x21
	mov	w1, 1
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L1045
	ldr	w0, [x19, 848]
	add	x20, x20, 2520
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x19, 848]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	add	x0, x20, 20480
	mov	w2, 0
	ldr	w1, [x0, 3672]
	ldr	w0, [x19, 848]
	bl	FSP_SetDisplay
	cbnz	w24, .L1068
	ldr	x1, [x20, 24040]
	mov	w0, 0
	strb	wzr, [x1, 1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1065:
	add	x1, x20, 2520
	ldrb	w0, [x1, 2]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbz	w0, .L1036
	add	x1, x1, 20480
	ldr	w2, [x1, 3656]
	cmp	w2, 1
	bls	.L1051
	ldr	w1, [x1, 3660]
.L1037:
	add	x0, x20, 2520
	add	x23, x20, 2520
	add	x0, x0, 20480
	cmp	w2, 1
	cset	w24, hi
	cmn	w1, #1
	str	w1, [x0, 3672]
	add	x0, x23, 36864
	ldr	w2, [x0, 1632]
	add	w2, w2, 1
	str	w2, [x0, 1632]
	bne	.L1069
	.p2align 2
.L1039:
	mov	w0, 1
.L1032:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1064:
	ldrb	w0, [x20, 2529]
	cmp	w0, 1
	bne	.L1039
	b	.L1034
	.p2align 3
.L1050:
	mov	w22, 0
	b	.L1033
	.p2align 3
.L1036:
	add	x0, x1, 20480
	ldr	w1, [x0, 3668]
	str	w1, [x0, 3672]
	cbz	x25, .L1052
	ldr	x2, [x23, 584]
	mov	w24, 0
	ldr	x3, [x25, 584]
	cmp	x3, x2
	bge	.L1038
	str	x3, [x23, 584]
	str	x2, [x25, 584]
	ldr	w1, [x0, 3672]
	b	.L1038
	.p2align 3
.L1045:
	add	x20, x20, 2520
	ldrsb	w1, [x20, 1]
	cmp	w1, 3
	beq	.L1070
	cmp	w1, 1
	beq	.L1071
	cmp	w1, 2
	bne	.L1039
	ldr	x1, [x20, 24040]
	strb	wzr, [x1, 1]
	strb	wzr, [x20, 1]
	b	.L1032
	.p2align 3
.L1067:
	ldr	x0, [x23, 24056]
	strb	w24, [x0, 1]
	strb	w24, [x23, 1]
	b	.L1044
	.p2align 3
.L1042:
	ldr	x1, .LC135
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 848]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x19, 848]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	add	x0, x23, 20480
	mov	w2, 0
	ldr	w1, [x0, 3672]
	ldr	w0, [x19, 848]
	bl	FSP_SetDisplay
	cbnz	w24, .L1072
	ldr	x1, [x23, 24040]
	mov	w0, 1
	strb	wzr, [x1, 1]
	b	.L1032
	.p2align 3
.L1068:
	ldr	x1, [x20, 24056]
	mov	w0, 0
	strb	wzr, [x1, 1]
	b	.L1032
	.p2align 3
.L1051:
	mov	w1, -1
	b	.L1037
	.p2align 3
.L1071:
	ldr	x2, [x20, 24056]
	mov	w0, w1
	strb	wzr, [x2, 1]
	strb	wzr, [x20, 1]
	b	.L1032
	.p2align 3
.L1070:
	ldr	x0, [x20, 24048]
	strb	wzr, [x0, 1]
	strb	wzr, [x20, 1]
	b	.L1039
	.p2align 3
.L1063:
	ldr	x1, .LC129
	mov	x4, x0
	mov	x3, x25
	mov	x2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1032
	.p2align 3
.L1052:
	mov	w24, 0
	b	.L1038
	.p2align 3
.L1066:
	ldr	x1, .LC131
	mov	w2, 644
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1032
	.p2align 3
.L1072:
	ldr	x1, [x23, 24056]
	mov	w0, w24
	strb	wzr, [x1, 1]
	b	.L1032
	.size	VC1DEC_VDMPostProc, .-VC1DEC_VDMPostProc
	.align	3
.LC129:
	.xword	.LC128
	.align	3
.LC131:
	.xword	.LC130
	.align	3
.LC133:
	.xword	.LC132
	.align	3
.LC135:
	.xword	.LC134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_DecodeArbiter
	.type	VC1_Vfmw_DecodeArbiter, %function
VC1_Vfmw_DecodeArbiter:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	bl	_mcount
	add	x3, x19, 2520
	ldrb	w0, [x19, 2520]
	tbz	x0, 4, .L1126
	mov	w2, -21
	add	x1, x3, 36864
	and	w0, w0, w2
	strb	w0, [x19, 2520]
	ldr	w0, [x1, 1764]
	sub	w0, w0, #2
	cmp	w0, 1
	ldr	x0, [x20]
	bls	.L1076
	add	x3, x3, 20480
	ldr	w2, [x0, 8]
	ldr	w3, [x3, 3656]
.L1077:
	add	x0, x19, 2520
	sub	w1, w2, #1
	add	x0, x0, 36864
	cmp	w1, 3
	str	w2, [x0, 1764]
	bls	.L1128
.L1104:
	mov	w4, 1
	.p2align 2
.L1083:
	cbz	w3, .L1094
.L1093:
	cmp	w3, 1
	bls	.L1129
.L1097:
	cbz	w4, .L1096
	add	x19, x19, 2520
	add	x20, x20, 16384
	ldrsb	w0, [x19, 3104]
	cbnz	w0, .L1099
	add	x1, x20, 1608
	add	x19, x19, 8192
	add	x0, x19, 2048
	add	x20, x20, 1856
	add	x19, x19, 2456
	ldp	x2, x3, [x1]
	stp	x2, x3, [x0, 160]
	mov	w0, 1
	ldp	x2, x3, [x20]
	stp	x2, x3, [x19]
	ldp	x2, x3, [x20, 16]
	stp	x2, x3, [x19, 16]
	ldp	x2, x3, [x20, 32]
	stp	x2, x3, [x19, 32]
	ldp	x2, x3, [x20, 48]
	stp	x2, x3, [x19, 48]
	ldp	x2, x3, [x20, 64]
	stp	x2, x3, [x19, 64]
	ldp	x2, x3, [x20, 80]
	stp	x2, x3, [x19, 80]
	ldp	x2, x3, [x20, 96]
	stp	x2, x3, [x19, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1125:
	ldr	x0, [x20]
	ldr	w1, [x0, 8]
	add	x0, x19, 2520
	add	x0, x0, 36864
	sub	w2, w1, #1
	cmp	w2, 3
	str	w1, [x0, 1764]
	bls	.L1130
	mov	w4, 1
	.p2align 2
.L1094:
	ldrb	w0, [x19, 2522]
	sub	w2, w0, #1
	sub	w1, w0, #4
	uxtb	w2, w2
	uxtb	w1, w1
	cmp	w2, 1
	ccmp	w1, 1, 0, hi
	bls	.L1100
.L1095:
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbnz	w0, .L1097
	ldr	x1, .LC142
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L1096:
	add	x20, x20, 53248
	add	x0, x19, 2520
	ldr	w1, [x20, 848]
	bl	VC1_ClearCurPic
	ldr	x0, .LC144
	ldr	x4, [x0]
	cbz	x4, .L1126
	ldr	w0, [x20, 848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L1126:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1128:
	ldr	x0, .LC138
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1085
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1085:
	.section	.rodata
	.align	0
	.align	2
.L1085:
	.byte	(.L1084 - .Lrtx1085) / 4
	.byte	(.L1086 - .Lrtx1085) / 4
	.byte	(.L1087 - .Lrtx1085) / 4
	.byte	(.L1088 - .Lrtx1085) / 4
	.text
	.p2align 3
.L1076:
	ldr	w2, [x0, 8]
	cmp	w2, 1
	ccmp	w2, 4, 4, hi
	beq	.L1078
	add	x3, x3, 20480
	ldr	w3, [x3, 3656]
	b	.L1077
	.p2align 3
.L1087:
	mov	w4, 0
	b	.L1083
	.p2align 3
.L1086:
	ldrb	w0, [x19, 2522]
	cmp	w0, wzr
	cset	w4, eq
	b	.L1083
	.p2align 3
.L1088:
	add	x0, x19, 2520
	ldrb	w1, [x0, 2]
	cbnz	w1, .L1089
	add	x0, x0, 36864
	mov	w4, 1
	str	wzr, [x0, 1696]
	b	.L1083
	.p2align 3
.L1084:
	ldrb	w0, [x19, 2522]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cmp	w0, wzr
	cset	w4, ne
	b	.L1083
	.p2align 3
.L1089:
	cmp	w1, 2
	bne	.L1091
	add	x0, x0, 36864
	ldr	w0, [x0, 1696]
	cbnz	w0, .L1104
	mov	w4, 0
	cbnz	w3, .L1093
	.p2align 2
.L1100:
	ldr	x1, .LC140
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1096
	.p2align 3
.L1099:
	add	x21, x19, 8192
	add	x1, x20, 1624
	mov	x2, 172
	add	x0, x21, 2224
	bl	memcpy
	add	x4, x20, 1796
	add	x3, x21, 2396
	mov	x2, 176
	ldp	x0, x1, [x4]
	stp	x0, x1, [x3]
	add	x1, x20, 1968
	add	x0, x21, 2568
	ldp	x6, x7, [x4, 16]
	stp	x6, x7, [x3, 16]
	ldp	x6, x7, [x4, 32]
	stp	x6, x7, [x3, 32]
	ldr	x5, [x4, 48]
	str	x5, [x3, 48]
	ldr	w4, [x20, 1852]
	str	w4, [x19, 10644]
	bl	memcpy
	ldr	w0, [x20, 2012]
	add	x3, x19, 20480
	strb	w0, [x19, 4]
	add	x1, x20, 2144
	ldr	x2, .LC143
	add	x0, x21, 2744
	ldr	w3, [x3, 3676]
	ldr	x4, [x2, 104]
	lsl	x2, x3, 2
	sub	x2, x2, x3
	lsl	x2, x2, 2
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1091:
	and	w1, w1, -5
	uxtb	w1, w1
	cmp	w1, 1
	bne	.L1104
	add	x0, x0, 36864
	mov	w4, w1
	str	w1, [x0, 1696]
	cbz	w3, .L1100
	b	.L1093
	.p2align 3
.L1078:
	ldr	x1, .LC137
	add	x21, x3, 20480
	mov	w0, 2
	add	x23, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x21, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L1079
	ldr	w0, [x23, 848]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x22, 552]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x22, 560]
	bl	FreeUsdByDec
	ldr	w0, [x23, 848]
	ldr	x1, [x22, 568]
	bl	FreeUsdByDec
	add	x0, x22, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x21, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_ClearLogicFs
	ldr	w1, [x21, 3660]
	mov	w2, 1
	ldr	w0, [x23, 848]
	bl	FSP_ClearLogicFs
	str	wzr, [x21, 3660]
	str	wzr, [x21, 3664]
	ldr	w0, [x23, 848]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 3660]
	str	w0, [x21, 3664]
.L1079:
	add	x0, x19, 2520
	add	x1, x0, 20480
	str	wzr, [x1, 3656]
	ldr	x2, [x0, 24048]
	cbz	x2, .L1125
	ldr	x3, [x0, 24056]
	cbz	x3, .L1125
	strb	wzr, [x2, 1]
	ldr	x2, [x0, 24056]
	strb	wzr, [x2, 1]
	ldr	x2, [x0, 24048]
	strb	wzr, [x2]
	ldr	x0, [x0, 24056]
	strb	wzr, [x0]
	ldr	x0, [x20]
	ldr	w3, [x1, 3656]
	ldr	w2, [x0, 8]
	b	.L1077
.L1130:
	ldr	x0, .LC145
	mov	w3, 0
	ldrh	w0, [x0,w2,uxtw #1]
	adr	x1, .Lrtx1103
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx1103:
	.section	.rodata
	.align	0
	.align	2
.L1103:
	.2byte	(.L1084 - .Lrtx1103) / 4
	.2byte	(.L1086 - .Lrtx1103) / 4
	.2byte	(.L1087 - .Lrtx1103) / 4
	.2byte	(.L1088 - .Lrtx1103) / 4
	.text
.L1129:
	ldrb	w0, [x19, 2522]
	b	.L1095
	.size	VC1_Vfmw_DecodeArbiter, .-VC1_Vfmw_DecodeArbiter
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC138:
	.xword	.L1085
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC143:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC144:
	.xword	g_event_report
	.align	3
.LC145:
	.xword	.L1103
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_StartDecode
	.type	VC1_Vfmw_StartDecode, %function
VC1_Vfmw_StartDecode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 16
	add	x22, x20, 12288
	bl	_mcount
	add	x21, x22, 2520
	ldr	x0, [x20]
	ldr	w1, [x0, 632]
	str	w1, [x19, 14600]
	ldr	w0, [x0, 684]
	str	w0, [x19, 14604]
	ldrsb	w0, [x21, 3104]
	cbz	w0, .L1146
.L1132:
	mov	x1, x19
	mov	x0, x20
	add	x23, x22, 2520
	bl	VC1_WritePicMsg
	add	x2, x23, 20480
	ldr	x3, .LC146
	add	x1, x2, 3680
	add	x0, x20, 104
	ldr	w2, [x2, 3676]
	strb	w2, [x19, 74]
	uxtw	x2, w2
	ldr	x4, [x3, 104]
	lsl	x3, x2, 3
	sub	x2, x3, x2
	lsl	x2, x2, 3
	blr	x4
	mov	x0, x21
	mov	x1, x19
	bl	VC1_CfgVDH
	ldrb	w0, [x22, 2522]
	cmp	w0, 1
	bls	.L1147
.L1133:
	cmp	w0, 5
	beq	.L1148
	strb	wzr, [x19, 1]
	add	x23, x22, 2520
	ldrsb	w1, [x22, 2524]
	ldrb	w0, [x22, 2528]
	strb	w1, [x20, 16]
	strb	w1, [x23, 3]
	strb	w0, [x23, 9]
	ldrb	w1, [x19, 3]
	cmp	w1, 2
	beq	.L1149
.L1136:
	and	w0, w1, -5
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L1137
	add	x23, x23, 36864
	str	w0, [x23, 1696]
.L1137:
	ldr	x2, [x20]
	str	x19, [x20, 8]
	ldr	w0, [x2, 920]
	cmp	w0, 1
	beq	.L1150
	cmp	w0, 2
	beq	.L1151
.L1141:
	mov	w0, 1
.L1138:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1151:
	ldr	w0, [x2, 924]
	cmp	w0, wzr
	ccmp	x19, xzr, 4, gt
	beq	.L1141
	sub	w1, w1, #2
	mov	w0, 1
	and	w1, w1, -3
	uxtb	w1, w1
	cbnz	w1, .L1138
	ldr	x1, [x22, 26560]
	add	x3, x20, 53248
	mov	x0, x21
	strb	wzr, [x1, 1]
	ldr	x2, [x20]
	ldr	w1, [x2, 924]
	sub	w1, w1, #1
	str	w1, [x2, 924]
	ldr	w1, [x3, 848]
	bl	VC1_ClearCurPic
	str	xzr, [x20, 8]
	mov	w0, 0
	b	.L1138
	.p2align 3
.L1148:
	mov	w3, 1
	strb	w3, [x19, 1]
	add	x2, x22, 2520
	strb	w3, [x22, 2528]
	ldrsb	w1, [x22, 2525]
	add	x4, x2, 36864
	strb	w1, [x22, 2524]
	add	x23, x22, 2520
	mov	w0, 1
	ldr	w2, [x4, 1720]
	sub	w2, w2, #1
	str	w2, [x19, 14504]
	strb	w1, [x20, 16]
	strb	w1, [x23, 3]
	strb	w0, [x23, 9]
	ldrb	w1, [x19, 3]
	cmp	w1, 2
	bne	.L1136
.L1149:
	add	x24, x23, 36864
	ldr	w0, [x24, 1696]
	cbnz	w0, .L1137
	add	x1, x20, 53248
	mov	x0, x21
	ldr	w1, [x1, 848]
	bl	VC1_ClearCurPic
	ldr	x1, [x23, 24040]
	mov	w0, 0
	strb	wzr, [x1]
	ldr	w1, [x24, 1700]
	add	w1, w1, 1
	str	w1, [x24, 1700]
	str	xzr, [x20, 8]
	b	.L1138
	.p2align 3
.L1147:
	ldrb	w1, [x22, 2524]
	strb	w1, [x22, 2525]
	b	.L1133
	.p2align 3
.L1150:
	cbz	x19, .L1138
	sub	w1, w1, #2
	and	w1, w1, -3
	uxtb	w1, w1
	cbnz	w1, .L1138
	ldr	x2, [x22, 26560]
	add	x1, x20, 53248
	mov	x0, x21
	strb	wzr, [x2, 1]
	ldr	w1, [x1, 848]
	bl	VC1_ClearCurPic
	str	xzr, [x20, 8]
	mov	w0, 0
	b	.L1138
	.p2align 3
.L1146:
	mov	x0, x21
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	b	.L1132
	.size	VC1_Vfmw_StartDecode, .-VC1_Vfmw_StartDecode
	.align	3
.LC146:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvHdr
	.type	VC1_Vfmw_ParseAdvHdr, %function
VC1_Vfmw_ParseAdvHdr:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w24, w2
	mov	x25, x1
	bl	_mcount
	add	x22, x20, 36864
	ldr	x21, [x20, 3136]
	mov	w1, 32
	strb	wzr, [x20, 6]
	add	x23, x22, 1640
	mov	x0, x21
	bl	BsGet
	ldr	x19, [x22, 1640]
	ldr	w3, [x21, 32]
	uxtb	w26, w0
	ldr	w2, [x23, 28]
	mov	x0, x21
	lsr	w3, w3, 3
	add	x19, x19, x3
	sub	w2, w2, w3
	mov	x1, x19
	bl	BsInit
	sub	w0, w26, #10
	cmp	w0, 5
	bhi	.L1153
	cmp	w26, 11
	beq	.L1221
	ldrb	w1, [x20]
	and	w2, w1, 7
	cmp	w2, 7
	beq	.L1222
	add	x27, x20, 20480
	strb	wzr, [x20, 8]
	ldr	x2, .LC154
	str	wzr, [x27, 3676]
	ldrh	w0, [x2,w0,uxtw #1]
	adr	x2, .Lrtx1169
	add	x0, x2, w0, sxth #2
	br	x0
.Lrtx1169:
	.section	.rodata
	.align	0
	.align	2
.L1169:
	.2byte	(.L1168 - .Lrtx1169) / 4
	.2byte	(.L1185 - .Lrtx1169) / 4
	.2byte	(.L1170 - .Lrtx1169) / 4
	.2byte	(.L1186 - .Lrtx1169) / 4
	.2byte	(.L1172 - .Lrtx1169) / 4
	.2byte	(.L1173 - .Lrtx1169) / 4
	.text
	.p2align 3
.L1153:
	sub	w0, w26, #27
	cmp	w0, 4
	bls	.L1223
	cmp	w26, 254
	beq	.L1224
.L1185:
	mov	w0, w24
	mov	x1, x23
	bl	VC1_ClearCurPacket
	mov	w0, 0
.L1158:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1221:
	ldrb	w0, [x20]
	and	w0, w0, 7
	cmp	w0, 7
	bne	.L1185
	mov	x0, x21
	mov	x2, x25
	mov	x1, x20
	bl	VC1_Vfmw_ParseAdvSlcHdr
	cmp	w0, 1
	mov	w21, w0
	bne	.L1156
	add	x27, x20, 20480
	ldr	w0, [x27, 3676]
	cmp	w0, 255
	bls	.L1157
	mov	w1, w24
	mov	x0, x20
	bl	VC1_ClearCurPic
	ldr	x1, .LC148
	mov	w0, w21
	ldr	w2, [x27, 3676]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
	.p2align 3
.L1223:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1186:
	ldr	x26, .LC155
.L1216:
	ldr	x3, [x26, 96]
	mov	x2, 176
	mov	w1, 0
	add	x0, x25, 360
	ldrb	w28, [x25, 391]
	blr	x3
	strb	w28, [x25, 391]
.L1174:
	ldr	x3, [x26, 96]
	add	x28, x27, 3680
	mov	x2, 14336
	mov	w1, 0
	mov	x0, x28
	blr	x3
	mov	x0, x21
	bl	BsPos
	str	w0, [x25, 500]
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvPicHdr
	cmp	w0, 1
	mov	w26, w0
	beq	.L1225
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC157
	mov	w2, 6001
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w26
	b	.L1158
	.p2align 3
.L1224:
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w19, w0
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w19, w2
	ccmp	w0, w1, 0, eq
	bne	.L1185
	add	x1, x20, 20480
	mov	w0, 1
	strb	w0, [x20, 7]
	mov	w0, 1
	ldr	w1, [x1, 3676]
	cbz	w1, .L1158
	ldrb	w1, [x20]
	strb	w0, [x20, 6]
	orr	w1, w1, 16
	strb	w1, [x20]
	b	.L1158
	.p2align 3
.L1222:
	mov	w0, 1
	orr	w1, w1, 16
	strb	w0, [x20, 6]
	mov	w0, 1
	strb	w1, [x20]
	b	.L1158
	.p2align 3
.L1168:
	orr	w0, w1, 32
	mov	x1, x23
	strb	w0, [x20]
	mov	w0, w24
	bl	VC1_ClearCurPacket
	mov	w0, 1
	b	.L1158
	.p2align 3
.L1172:
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvEntptHdr
	cmp	w0, 1
	mov	w19, w0
	beq	.L1226
.L1183:
	mov	w0, w24
	mov	x1, x23
	bl	VC1_ClearCurPacket
	mov	w0, w19
	b	.L1158
	.p2align 3
.L1173:
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvSeqHdr
	cmp	w0, 1
	mov	w19, w0
	bne	.L1183
	ldrb	w0, [x20]
	orr	w0, w0, 1
	strb	w0, [x20]
	b	.L1183
	.p2align 3
.L1170:
	ldr	x26, .LC155
	mov	w0, 1
	strb	w0, [x20, 8]
	mov	x2, 16
	mov	w1, 0
	add	x0, x25, 520
	ldr	x3, [x26, 96]
	blr	x3
	ldrb	w0, [x20, 8]
	cbnz	w0, .L1174
	b	.L1216
	.p2align 3
.L1156:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC153
	mov	w2, 5912
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	b	.L1158
	.p2align 3
.L1225:
	mov	x0, x21
	add	x22, x22, 1640
	bl	BsPos
	ldr	w1, [x25, 500]
	sub	w0, w0, w1
	str	w0, [x25, 500]
	mov	x0, x21
	ldrb	w1, [x20]
	orr	w1, w1, 4
	strb	w1, [x20]
	bl	BsPos
	add	w0, w0, 32
	ldr	w1, [x22, 28]
	cmp	w0, w1, lsl 3
	bge	.L1176
	ldr	w3, [x27, 3676]
	add	x23, x25, 536
	ldr	x2, [x20, 3136]
	uxtw	x0, w3
	lsl	x1, x0, 3
	sub	x1, x1, x0
	lsl	x1, x1, 3
	add	x21, x28, x1
	strb	w3, [x21, 16]
	lsl	x3, x0, 2
	sub	x0, x3, x0
	add	x23, x23, x0, lsl 2
	ldr	w0, [x2, 32]
	ubfx	x0, x0, 3, 29
	add	x0, x19, x0
	str	x0, [x28, x1]
	ldr	w1, [x2, 32]
	and	w1, w1, 7
	str	w1, [x21, 24]
	ldr	w1, [x2, 24]
	ldr	w2, [x2, 32]
	lsl	w1, w1, 3
	sub	w1, w1, w2
	str	w1, [x21, 28]
	bl	MEM_Vir2Phy
	str	w0, [x21, 20]
	ldr	w0, [x22, 36]
	str	w0, [x21, 48]
	ldr	x1, [x22, 8]
	cbz	x1, .L1177
	ldr	w0, [x22, 24]
	cbz	w0, .L1177
	str	x1, [x21, 8]
	str	wzr, [x21, 40]
	ldr	w0, [x22, 32]
	lsl	w0, w0, 3
	str	w0, [x21, 44]
	ldr	w0, [x22, 24]
	str	w0, [x21, 36]
	ldr	w0, [x22, 40]
	str	w0, [x21, 52]
.L1178:
	ldr	w4, [x27, 3592]
	ldr	w0, [x27, 3596]
	ldrb	w2, [x20, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L1179
	add	w0, w0, 1
	ldr	w3, [x23, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x21, 32]
	cmp	w3, wzr
	ccmp	w4, w3, 2, gt
	bcc	.L1227
.L1162:
	ldr	w0, [x21, 28]
	cmp	w0, wzr
	ble	.L1165
	cbz	x1, .L1181
	ldr	w0, [x21, 44]
	cmp	w0, wzr
	ble	.L1165
.L1181:
	ldr	w1, [x27, 3676]
	mov	w0, 1
	add	w1, w1, w0
	str	w1, [x27, 3676]
	b	.L1158
	.p2align 3
.L1176:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC157
	mov	w2, 5995
	mov	w0, w26
	bl	dprint_vfmw
	mov	w0, w26
	b	.L1158
	.p2align 3
.L1157:
	uxtw	x4, w0
	add	x3, x27, 3680
	lsl	x1, x4, 3
	ldr	x2, [x20, 3136]
	sub	x1, x1, x4
	add	x22, x25, 536
	lsl	x1, x1, 3
	add	x21, x3, x1
	strb	w0, [x21, 16]
	lsl	x0, x4, 2
	sub	x4, x0, x4
	ldr	w0, [x2, 32]
	add	x22, x22, x4, lsl 2
	ubfx	x0, x0, 3, 29
	add	x0, x19, x0
	str	x0, [x3, x1]
	ldr	w1, [x2, 32]
	and	w1, w1, 7
	str	w1, [x21, 24]
	ldr	w1, [x2, 24]
	ldr	w2, [x2, 32]
	lsl	w1, w1, 3
	sub	w1, w1, w2
	str	w1, [x21, 28]
	bl	MEM_Vir2Phy
	str	w0, [x21, 20]
	ldr	w0, [x23, 36]
	str	w0, [x21, 48]
	ldr	x1, [x23, 8]
	cbz	x1, .L1159
	ldr	w0, [x23, 24]
	cbz	w0, .L1159
	str	x1, [x21, 8]
	str	wzr, [x21, 40]
	ldr	w0, [x23, 32]
	lsl	w0, w0, 3
	str	w0, [x21, 44]
	ldr	w0, [x23, 24]
	str	w0, [x21, 36]
	ldr	w0, [x23, 40]
	str	w0, [x21, 52]
.L1160:
	ldr	w4, [x27, 3592]
	ldr	w0, [x27, 3596]
	ldrb	w2, [x20, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L1161
	add	w0, w0, 1
	ldr	w3, [x22, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x21, 32]
	cmp	w3, wzr
	ccmp	w4, w3, 2, gt
	bcs	.L1162
	ldr	x1, .LC149
	mov	w0, 1
	ldr	w2, [x22, 4]
	ldr	w4, [x27, 3596]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
	.p2align 3
.L1177:
	mov	x1, 0
	str	xzr, [x21, 8]
	stp	wzr, wzr, [x21, 36]
	str	wzr, [x21, 44]
	str	wzr, [x21, 52]
	b	.L1178
.L1226:
	mov	x1, x25
	mov	x0, x20
	bl	VC1_Vfmw_UpdateAdvSPS
	ldrb	w0, [x20]
	orr	w0, w0, 2
	strb	w0, [x20]
	b	.L1183
.L1179:
	ldr	w3, [x23, 4]
	str	w3, [x21, 32]
	cmp	w4, w3
	bcs	.L1162
	ldr	x1, .LC150
	mov	w0, 1
	ldr	w2, [x23, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
.L1159:
	mov	x1, 0
	str	xzr, [x21, 8]
	stp	wzr, wzr, [x21, 36]
	str	wzr, [x21, 44]
	str	wzr, [x21, 52]
	b	.L1160
.L1161:
	ldr	w3, [x22, 4]
	str	w3, [x21, 32]
	cmp	w4, w3
	bcs	.L1162
	ldr	x1, .LC150
	mov	w0, 1
	ldr	w2, [x22, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
.L1165:
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
.L1227:
	ldr	x1, .LC149
	mov	w0, 1
	ldr	w2, [x23, 4]
	ldr	w4, [x27, 3596]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1158
	.size	VC1_Vfmw_ParseAdvHdr, .-VC1_Vfmw_ParseAdvHdr
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC149:
	.xword	.LC101
	.align	3
.LC150:
	.xword	.LC103
	.align	3
.LC151:
	.xword	.LC105
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC154:
	.xword	.L1169
	.align	3
.LC155:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC157:
	.xword	.LC156
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseHeader
	.type	VC1_Vfmw_ParseHeader, %function
VC1_Vfmw_ParseHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	ldrsb	w0, [x19, 3104]
	cbnz	w0, .L1229
	ldrb	w3, [x19]
	mov	x2, x20
	ldr	x0, [x19, 3136]
	mov	x1, x19
	orr	w3, w3, 3
	strb	w3, [x19]
	bl	VC1_Vfmw_ParseSMPPicHdr
	cmp	w0, 1
	beq	.L1231
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1229:
	mov	w2, w21
	mov	x1, x20
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvHdr
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1231:
	ldrb	w2, [x19]
	mov	w1, 20
	orr	w1, w2, w1
	strb	w1, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_ParseHeader, .-VC1_Vfmw_ParseHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetCodeInfo
	.type	VC1_SetCodeInfo, %function
VC1_SetCodeInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	mov	x21, x1
	bl	_mcount
	add	x2, x19, 2520
	add	x0, x2, 3144
	str	x0, [x19, 5656]
	ldrb	w1, [x2, 3106]
	cmp	w1, 8
	beq	.L1237
	strb	wzr, [x2, 12]
	strb	w1, [x2, 11]
.L1234:
	add	x20, x19, 2520
	ldr	w2, [x21, 28]
	ldrsb	w1, [x20, 3104]
	cbz	w1, .L1238
	ldr	x1, [x21]
	bl	BsInit
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1238:
	ldr	x1, [x21]
	bl	BsInit
	ldr	w1, [x19, 5632]
	add	x2, x20, 20480
	add	x3, x20, 3120
	add	x20, x20, 3184
	adds	w4, w1, 15
	add	w0, w1, 30
	csel	w0, w0, w4, mi
	asr	w0, w0, 4
	str	w0, [x2, 3592]
	ldr	w0, [x19, 5636]
	str	w0, [x2, 3612]
	str	w1, [x2, 3608]
	add	w1, w0, 30
	adds	w0, w0, 15
	csel	w0, w1, w0, mi
	asr	w0, w0, 4
	str	w0, [x2, 3596]
	ldp	x0, x1, [x3]
	stp	x0, x1, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1237:
	mov	w3, 1
	mov	w1, 6
	strb	w3, [x2, 12]
	strb	w1, [x2, 11]
	b	.L1234
	.size	VC1_SetCodeInfo, .-VC1_SetCodeInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ReceivePacket
	.type	VC1_ReceivePacket, %function
VC1_ReceivePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 53248
	add	x1, x0, 64
	cbz	x19, .L1247
	ldr	w2, [x19, 16]
	str	w2, [x1, 20]
	ldr	x2, [x19]
	str	x2, [x0, 64]
	ldr	w2, [x19, 20]
	str	w2, [x1, 28]
	ldrb	w2, [x19, 10]
	strb	w2, [x1, 16]
	ldr	w2, [x19, 24]
	str	w2, [x1, 36]
	ldrb	w2, [x19, 10]
	cmp	w2, 1
	beq	.L1242
	ldr	w2, [x19, 104]
	str	w2, [x1, 24]
	ldr	x2, [x19, 88]
	str	x2, [x1, 8]
	ldr	w2, [x19, 108]
	str	w2, [x1, 32]
	ldrb	w2, [x19, 98]
	strb	w2, [x1, 17]
	ldr	w2, [x19, 112]
	str	w2, [x1, 40]
	ldrb	w2, [x19, 98]
	cmp	w2, 1
	bne	.L1248
.L1243:
	mov	x0, x20
	bl	VC1_SetCodeInfo
	mov	w0, 1
.L1241:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1248:
	ldr	w0, [x0, 848]
	bl	VC1_ClearCurPacket
	ldrb	w2, [x19, 98]
	mov	w0, 1
	ldr	x1, .LC161
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1242:
	strb	wzr, [x1, 17]
	str	xzr, [x1, 8]
	str	wzr, [x1, 24]
	str	wzr, [x1, 32]
	str	wzr, [x1, 40]
	b	.L1243
	.p2align 3
.L1247:
	ldr	x1, .LC159
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1241
	.size	VC1_ReceivePacket, .-VC1_ReceivePacket
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Decode
	.type	VC1DEC_Decode, %function
VC1DEC_Decode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	add	x20, x19, 12288
	bl	_mcount
	add	x21, x20, 2344
	ldr	x3, .LC162
	mov	x2, 176
	mov	x1, x22
	mov	x0, x21
	ldr	x3, [x3, 104]
	blr	x3
	mov	x1, x21
	mov	x0, x19
	bl	VC1_ReceivePacket
	mov	w21, w0
	cbz	w0, .L1276
	ldr	x0, [x19]
	add	x22, x19, 53248
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L1277
.L1252:
	ldrb	w0, [x20, 2520]
	strb	w0, [x22, 192]
.L1253:
	add	x20, x20, 2520
	add	x1, x19, 16384
	ldr	w2, [x22, 848]
	add	x1, x1, 1608
	mov	x0, x20
	bl	VC1_Vfmw_ParseHeader
	mov	w23, w0
	cbnz	w0, .L1254
	ldr	w0, [x22, 848]
	add	x1, x22, 64
	bl	VC1_ClearCurPacket
	ldr	x0, .LC165
	ldr	x4, [x0]
	cbz	x4, .L1256
	ldr	w0, [x22, 848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w21, 0
	blr	x4
.L1273:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1254:
	mov	x0, x19
	bl	VC1_Vfmw_DecodeArbiter
	cbnz	w0, .L1278
.L1256:
	mov	w21, 0
.L1280:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1277:
	ldr	w0, [x0, 928]
	cmp	w0, 1
	bne	.L1252
	ldrb	w0, [x22, 192]
	strb	w0, [x20, 2520]
	b	.L1253
	.p2align 3
.L1276:
	add	x19, x19, 53248
	ldr	x1, .LC164
	ldr	w2, [x19, 56]
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1278:
	mov	x0, x19
	bl	VC1_Vfmw_GetStreamInfo
	mov	w21, w0
	cbz	w0, .L1279
	mov	x0, x19
	bl	VC1_Vfmw_StartDecode
	mov	w21, w0
	cbz	w0, .L1260
	mov	w21, w23
	b	.L1273
	.p2align 3
.L1279:
	ldr	x1, .LC166
	bl	dprint_vfmw
	ldr	x0, [x19]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	bne	.L1258
	ldr	w0, [x0, 928]
	cmp	w0, 1
	beq	.L1259
.L1258:
	ldr	w1, [x22, 848]
	mov	x0, x20
	bl	VC1_ClearCurPic
.L1259:
	ldr	x0, .LC165
	ldr	x4, [x0]
	cbz	x4, .L1256
.L1274:
	ldr	w0, [x22, 848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L1273
	.p2align 3
.L1260:
	add	x19, x19, 36864
	ldr	w0, [x22, 848]
	mov	w2, 1
	ldr	w1, [x19, 2092]
	bl	FSP_ClearLogicFs
	ldr	x1, [x19, 1984]
	ldr	x0, .LC165
	strb	wzr, [x1]
	ldr	x1, [x19, 1984]
	strb	wzr, [x1, 1]
	ldr	x4, [x0]
	cbnz	x4, .L1274
	mov	w21, 0
	b	.L1280
	.size	VC1DEC_Decode, .-VC1DEC_Decode
	.align	3
.LC162:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	g_event_report
	.align	3
.LC166:
	.xword	.LC72
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_GetPacketState
	.type	VC1_GetPacketState, %function
VC1_GetPacketState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	bl	_mcount
	mov	w0, 2
	ldrsb	w1, [x19, 2526]
	ldr	x19, [sp, 16]
	cmp	w1, 1
	csel	w0, w0, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_GetPacketState, .-VC1_GetPacketState
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11519, %object
	.size	__func__.11519, 13
__func__.11519:
	.string	"Vc1SMPSeqHdr"
	.zero	3
.LC0:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
.LC1:
	.word	3
	.word	1
	.word	2
	.word	0
	.word	4
	.zero	4
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.word	4
	.zero	4
.LC3:
	.word	1
	.word	1
	.word	2
	.word	1
	.word	3
	.word	1
	.word	2
	.zero	4
.LC4:
	.word	2
	.word	3
	.word	3
	.word	4
	.word	4
	.word	5
	.word	5
	.zero	4
.LC5:
	.word	3
	.word	4
	.word	1
	.word	5
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	1
	.word	3
	.word	5
	.word	7
.LC6:
	.word	5
	.word	5
	.word	6
	.word	6
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
.LC7:
	.word	256
	.word	128
	.word	85
	.word	64
	.word	51
	.word	43
	.word	37
	.word	32
	.type	__func__.11830, %object
	.size	__func__.11830, 17
__func__.11830:
	.string	"VC1_DecBfraction"
	.zero	7
	.type	aCount, %object
	.size	aCount, 128
aCount:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	2
	.word	3
	.word	3
	.word	4
	.word	3
	.word	4
	.word	4
	.word	5
	.type	a2On4Off, %object
	.size	a2On4Off, 60
a2On4Off:
	.word	3
	.word	5
	.word	6
	.word	9
	.word	10
	.word	12
	.word	17
	.word	18
	.word	20
	.word	24
	.word	33
	.word	34
	.word	36
	.word	40
	.word	48
	.zero	4
.LC8:
	.word	1
	.word	2
	.word	2
	.word	2
	.word	0
	.word	1
	.word	0
	.word	1
.LC9:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	27
	.word	29
	.word	31
	.align	3
.LANCHOR1 = . + 0
	.type	FldPTypeTab, %object
	.size	FldPTypeTab, 64
FldPTypeTab:
	.word	0
	.word	0
	.word	0
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	4
	.word	4
	.word	2
	.word	4
	.word	4
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC13:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC15:
	ASCII(.string	"VC1 INIT!!!\n" )
	.zero	3
.LC17:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC20:
	ASCII(.string	"%s: %s\n" )
.LC22:
	ASCII(.string	"picture height out of range" )
	.zero	4
.LC24:
	ASCII(.string	"Vc1SMPSeqHdr Err, BS is wrong" )
	.zero	2
.LC26:
	ASCII(.string	"Vc1SMPSeqHdr Err, BS is wrong\n" )
	.zero	1
.LC31:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC33:
	ASCII(.string	"vc1 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC36:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC38:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC40:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC44:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC46:
	ASCII(.string	"VC1_Vfmw_GetImageBuffer get imgbuf err, clear all ref!\n" )
.LC48:
	ASCII(.string	"VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogicFs.\n" )
.LC53:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\n" )
.LC55:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!\n" )
	.zero	3
.LC57:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC60:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC62:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 err!\n" )
	.zero	7
.LC64:
	ASCII(.string	"line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\n" )
	.zero	3
.LC66:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\n" )
	.zero	5
.LC68:
	ASCII(.string	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p)\n" )
	.zero	6
.LC70:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\n" )
	.zero	5
.LC72:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo error! Release all packets!\n" )
	.zero	4
.LC85:
	ASCII(.string	"%s:%d Code(%d) is invalid\n" )
	.zero	5
.LC87:
	ASCII(.string	"%s:%d Denominator(%d) is invalid\n" )
	.zero	6
.LC101:
	ASCII(.string	"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\n" )
	.zero	1
.LC103:
	ASCII(.string	"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\n" )
	.zero	6
.LC105:
	ASCII(.string	"VC1_RecordSlcStream stream len <= 0\n" )
	.zero	3
.LC108:
	ASCII(.string	"Check Pos 2: %d\n" )
	.zero	7
.LC110:
	ASCII(.string	"Check Pos 3: %d\n" )
	.zero	7
.LC113:
	ASCII(.string	"\n======PicNum  :%6d=========\n" )
	.zero	2
.LC115:
	ASCII(.string	"INTERPFRM  :%#x\n" )
	.zero	7
.LC118:
	ASCII(.string	"VC1_Vfmw_ParseMPBPicHdr err!\n" )
	.zero	2
.LC120:
	ASCII(.string	"VC1_Vfmw_ParseSMPIPicHdr err!\n" )
	.zero	1
.LC122:
	ASCII(.string	"After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\n" )
.LC128:
	ASCII(.string	"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\n" )
.LC130:
	ASCII(.string	"line: %d, pToQueImg is Null!\n" )
	.zero	2
.LC132:
	ASCII(.string	"insert buf %d ref %d\n" )
	.zero	2
.LC134:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC136:
	ASCII(.string	"----------------- VC1 Imode -> %d ------------------\n" )
	.zero	2
.LC139:
	ASCII(.string	"NOTE: Drop non-I\n" )
	.zero	6
.LC141:
	ASCII(.string	"NOTE: Drop B\n" )
	.zero	2
.LC147:
	ASCII(.string	" pCodecInf->SlcNum = %d >= 256 \n" )
	.zero	7
.LC152:
	ASCII(.string	"line %d, Code = VC1_SCSLC failed!\n" )
	.zero	5
.LC156:
	ASCII(.string	"line %d, Code = VC1_SCFRM failed!\n" )
	.zero	5
.LC158:
	ASCII(.string	"bitsream para error -----\n" )
	.zero	5
.LC160:
	ASCII(.string	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\n" )
.LC163:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
