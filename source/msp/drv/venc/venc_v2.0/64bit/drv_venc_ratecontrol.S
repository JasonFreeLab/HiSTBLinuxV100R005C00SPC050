#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"drv_venc_ratecontrol.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcMinQPForVBR
	.type	VEDU_DRV_RCCalcMinQPForVBR, %function
VEDU_DRV_RCCalcMinQPForVBR:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 20]
	cbnz	w0, .L9
	ldr	w2, [x19, 84]
	mov	w3, 34079
	movk	w3, 0x51eb, lsl 16
	mov	w0, 200
	smull	x1, w2, w3
	asr	x1, x1, 38
	sub	w1, w1, w2, asr 31
	msub	w0, w1, w0, w2
	cbz	w0, .L4
	ldr	w1, [x19, 580]
.L5:
	cmp	w1, 19
	mov	w0, 20
	ble	.L6
	mov	w0, 30
	cmp	w1, w0
	csel	w0, w1, w0, le
.L6:
	str	w0, [x19, 580]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4:
	ldr	w0, [x19, 568]
	ldr	w2, [x19, 580]
	add	w0, w0, 200
	str	wzr, [x19, 568]
	add	w1, w2, 1
	sub	w2, w2, #1
	umull	x0, w0, w3
	lsr	x0, x0, 32
	lsr	w0, w0, 6
	cmp	w0, w1
	csel	w1, w2, w1, cc
	b	.L5
	.p2align 3
.L9:
	ldr	w0, [x19, 184]
	add	w0, w0, 5
	str	w0, [x19, 580]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCCalcMinQPForVBR, .-VEDU_DRV_RCCalcMinQPForVBR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetVBRMaxBitRate
	.type	VEDU_DRV_RCGetVBRMaxBitRate, %function
VEDU_DRV_RCGetVBRMaxBitRate:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	cmp	w0, 1280
	bhi	.L15
	cmp	w0, 720
	bhi	.L16
	cmp	w0, 352
	bhi	.L17
	mov	w0, 1536
	str	w0, [x19, 584]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L16:
	mov	w0, 5242880
	str	w0, [x19, 584]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L15:
	mov	w0, 8388608
	str	w0, [x19, 584]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L17:
	mov	w0, 3072
	str	w0, [x19, 584]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCGetVBRMaxBitRate, .-VEDU_DRV_RCGetVBRMaxBitRate
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetRecodingQP
	.type	VEDU_DRV_RCGetRecodingQP, %function
VEDU_DRV_RCGetRecodingQP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 272]
	str	w0, [x19, 172]
	lsr	w1, w0, 6
	add	w0, w0, 128
	str	w1, [x19, 180]
	str	w0, [x19, 104]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCGetRecodingQP, .-VEDU_DRV_RCGetRecodingQP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCInitInfo
	.type	VEDU_DRV_RCInitInfo, %function
VEDU_DRV_RCInitInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w4, w5, [x19, 36]
	ldr	w7, [x19, 28]
	mov	w1, 4
	ldp	w2, w3, [x19, 188]
	lsl	w0, w4, 3
	str	w4, [x19, 560]
	udiv	w6, w4, w7
	cmp	w2, w1
	csel	w1, w2, w1, ge
	add	w0, w0, w4, lsl 1
	cmp	w3, w1
	mov	w2, 1
	csel	w1, w3, w1, le
	uxtw	x3, w5
	stp	w1, w2, [x19, 208]
	lsr	w0, w0, 3
	ldr	w4, [x19, 76]
	stp	wzr, w0, [x19, 216]
	stp	w0, w2, [x19, 224]
	sxtw	x1, w6
	str	w6, [x19, 96]
	str	w7, [x19, 552]
	mul	x0, x1, x3
	str	w5, [x19, 556]
	str	x0, [x19, 88]
	cbz	w4, .L19
	str	wzr, [x19, 84]
.L19:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCInitInfo, .-VEDU_DRV_RCInitInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCInitInstantBits
	.type	VEDU_DRV_RCInitInstantBits, %function
VEDU_DRV_RCInitInstantBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC2
	add	x4, x19, 512
	ldr	w1, [x19, 28]
	mov	x2, 260
	ldr	x3, [x0]
	add	x0, x19, 276
	stp	w1, wzr, [x4, 24]
	stp	wzr, wzr, [x4, 32]
	mov	w1, 0
	blr	x3
	ldr	x0, [x19, 88]
	mov	x1, 4294967295
	cmp	x0, x1
	bls	.L25
	ldr	w1, [x19, 96]
	ldr	w3, [x19, 208]
.L26:
	mul	w3, w1, w3
	ldr	w0, [x19, 540]
	ldr	w2, [x19, 536]
	str	w3, [x19, 276]
	add	w3, w3, w0
	cmp	w2, 1
	str	w3, [x19, 540]
	bls	.L27
	sub	w2, w2, #2
	add	x0, x19, 280
	mov	x4, x2
	add	x2, x2, 71
	add	x2, x19, x2, lsl 2
	.p2align 2
.L28:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L28
	madd	w1, w1, w4, w1
	add	w3, w3, w1
	str	w3, [x19, 540]
.L27:
	str	w3, [x19, 548]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L25:
	ldr	w1, [x19, 40]
	ldr	w3, [x19, 208]
	sub	w1, w1, #1
	add	w1, w1, w3
	udiv	w1, w0, w1
	b	.L26
	.size	VEDU_DRV_RCInitInstantBits, .-VEDU_DRV_RCInitInstantBits
	.align	3
.LC2:
	.xword	venc_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCInitFrameBits
	.type	VEDU_DRV_RCInitFrameBits, %function
VEDU_DRV_RCInitFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 176]
	mov	w1, -1
	ldr	w2, [x19, 208]
	stp	w0, w0, [x19, 232]
	str	w1, [x19, 260]
	udiv	w0, w0, w2
	str	w1, [x19, 264]
	stp	w0, w0, [x19, 240]
	stp	w0, w0, [x19, 248]
	str	w0, [x19, 256]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCInitFrameBits, .-VEDU_DRV_RCInitFrameBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_EflRcInitQp
	.type	VEDU_DRV_EflRcInitQp, %function
VEDU_DRV_EflRcInitQp:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	bl	_mcount
	lsl	w0, w20, 2
	lsl	w3, w19, 2
	sub	w2, w0, w20
	sub	w0, w3, w19
	lsl	w3, w0, 5
	mul	w1, w2, w21
	add	w0, w0, w3
	add	w19, w0, w19
	lsr	w1, w1, 1
	mov	w0, 7
	udiv	w19, w19, w1
	cmp	w19, 170
	bhi	.L32
	sub	w1, w19, #121
	mov	w0, 15
	cmp	w1, 49
	bls	.L32
	sub	w1, w19, #81
	mov	w0, 20
	cmp	w1, 39
	bls	.L32
	sub	w1, w19, #41
	mov	w0, 25
	cmp	w1, 39
	bls	.L32
	sub	w1, w19, #16
	mov	w0, 30
	cmp	w1, 24
	bls	.L32
	sub	w1, w19, #6
	mov	w0, 38
	cmp	w1, 9
	bls	.L32
	sub	w19, w19, #3
	mov	w0, 40
	mov	w1, 43
	cmp	w19, 3
	csel	w0, w0, w1, cc
.L32:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VEDU_DRV_EflRcInitQp, .-VEDU_DRV_EflRcInitQp
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCModifyQPDeltaOfIP
	.type	VEDU_DRV_RCModifyQPDeltaOfIP, %function
VEDU_DRV_RCModifyQPDeltaOfIP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x4, [x19, 88]
	mov	x1, 4294967295
	ldr	w0, [x19, 24]
	cmp	x4, x1
	ldr	w5, [x19, 40]
	bls	.L41
	ldr	w1, [x19, 96]
	lsl	w2, w1, 4
	add	w3, w2, w1, lsl 2
.L42:
	cmp	w3, w0
	ldr	w5, [x19, 216]
	bcc	.L44
	cbz	w5, .L40
.L44:
	sub	w2, w0, w3
	mov	w1, -256
	lsl	w2, w2, 8
	ldr	w4, [x19, 100]
	mov	w6, 3264
	mov	w0, 256
	udiv	w2, w2, w3
	ldr	x3, .LC3
	cmp	w2, w1
	csel	w1, w2, w1, ge
	cmp	w4, wzr
	csel	w2, w4, wzr, ge
	cmp	w2, w6
	csel	w2, w2, w6, le
	cmp	w1, w0
	csel	w1, w1, w0, le
	lsr	w2, w2, 6
	add	w0, w5, w1, asr 6
	cmp	w0, wzr
	ldr	w1, [x3, w2, uxtw 2]
	csel	w0, w0, wzr, ge
	cmp	w1, w0
	csel	w0, w1, w0, le
	str	w0, [x19, 216]
.L40:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L41:
	lsl	w3, w4, 4
	add	w5, w5, 19
	add	w4, w3, w4, lsl 2
	udiv	w3, w4, w5
	b	.L42
	.size	VEDU_DRV_RCModifyQPDeltaOfIP, .-VEDU_DRV_RCModifyQPDeltaOfIP
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RcModifyQPForLargeFrmBits
	.type	VEDU_DRV_RcModifyQPForLargeFrmBits, %function
VEDU_DRV_RcModifyQPForLargeFrmBits:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VEDU_DRV_RcModifyQPForLargeFrmBits, .-VEDU_DRV_RcModifyQPForLargeFrmBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcQPDeltaByFrameBits
	.type	VEDU_DRV_RCCalcQPDeltaByFrameBits, %function
VEDU_DRV_RCCalcQPDeltaByFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x20
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits
	ldr	w19, [x20, 24]
	ldr	w20, [x20, 108]
	cmp	w19, w20
	bcc	.L57
	sub	w19, w19, w20
	lsl	w19, w19, 6
	udiv	w1, w19, w20
.L58:
	add	w1, w1, w0
	mov	w0, -54
	cmp	w1, w0
	mov	w2, 256
	csel	w0, w1, w0, ge
	cmp	w0, w2
	csel	w0, w0, w2, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L57:
	sub	w19, w20, w19
	lsl	w2, w19, 3
	sub	w2, w2, w19
	lsl	w2, w2, 3
	udiv	w1, w2, w20
	neg	w1, w1
	b	.L58
	.size	VEDU_DRV_RCCalcQPDeltaByFrameBits, .-VEDU_DRV_RCCalcQPDeltaByFrameBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcQPDeltaByInstantBits
	.type	VEDU_DRV_RCCalcQPDeltaByInstantBits, %function
VEDU_DRV_RCCalcQPDeltaByInstantBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 548]
	mov	w6, 63
	ldr	w3, [x19, 36]
	ldr	w5, [x19, 540]
	lsl	w0, w4, 5
	ldr	x2, .LC4
	udiv	w0, w0, w3
	lsl	w1, w5, 5
	add	x2, x2, 208
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	udiv	w1, w1, w3
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, w6
	csel	w1, w1, w6, le
	cmp	w0, w6
	csel	w0, w0, w6, le
	cmp	w5, w4
	lsr	w6, w3, 4
	ldr	w1, [x2, w1, sxtw 2]
	ldr	w0, [x2, w0, sxtw 2]
	sub	w2, w1, w0
	bls	.L60
	sub	w0, w3, w6
	cmp	w4, w0
	bls	.L60
	lsl	w1, w2, 2
	mov	w3, -128
	sub	w0, w1, w2
	mov	w1, 256
	lsl	w0, w0, 1
	cmp	w0, w3
	csel	w0, w0, w3, ge
	cmp	w0, w1
	csel	w0, w0, w1, le
.L61:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L60:
	cmp	w5, w4
	mov	w0, 0
	bcs	.L61
	add	w3, w3, w6
	cmp	w4, w3
	bcs	.L61
	lsl	w0, w2, 2
	mov	w2, -128
	cmp	w0, w2
	mov	w1, 256
	csel	w0, w0, w2, ge
	ldr	x19, [sp, 16]
	cmp	w0, w1
	csel	w0, w0, w1, le
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCCalcQPDeltaByInstantBits, .-VEDU_DRV_RCCalcQPDeltaByInstantBits
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalculateCurQP
	.type	VEDU_DRV_RCCalculateCurQP, %function
VEDU_DRV_RCCalculateCurQP:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19, 228]
	cbnz	w20, .L75
.L65:
	mov	x0, x19
	bl	VEDU_DRV_RCCalcQPDeltaByFrameBits
	mov	w21, w0
	mov	x0, x19
	bl	VEDU_DRV_RCCalcQPDeltaByInstantBits
	add	w0, w21, w0
	ldr	w4, [x19, 36]
	ldr	w2, [x19, 540]
	cmp	w2, w4
	bls	.L66
	sub	w2, w2, w4
	lsl	w3, w2, 2
	sub	w2, w3, w2
	lsl	w3, w2, 5
	udiv	w4, w3, w4
.L67:
	ldp	w5, w3, [x19, 220]
	cmn	w4, #64
	mov	w2, -64
	sub	w1, w3, w5
	csel	w3, w4, w2, ge
	lsl	w4, w1, 2
	mov	w8, -32
	sub	w4, w4, w1
	mov	w7, 64
	lsl	w2, w4, 5
	mov	w6, 32
	add	w2, w4, w2
	ldr	w4, [x19, 172]
	add	w2, w2, w1
	lsl	w2, w2, 2
	sdiv	w2, w2, w5
	cmp	w2, w8
	csel	w1, w2, w8, ge
	cmp	w3, w7
	csel	w3, w3, w7, le
	cmp	w1, w6
	add	w3, w3, w0
	csel	w1, w1, w6, le
	add	w1, w3, w1
	add	w1, w1, w4
	str	w1, [x19, 172]
	cbz	w20, .L68
	ldr	w0, [x19, 104]
	cmp	w1, w0
	bcs	.L68
	add	w1, w1, w0
	lsr	w1, w1, 1
.L68:
	ldp	w2, w0, [x19, 4]
	lsl	w2, w2, 6
	lsl	w0, w0, 6
	cmp	w1, w2
	csel	w1, w1, w2, ge
	cmp	w0, w1
	csel	w1, w0, w1, le
	str	w1, [x19, 172]
	lsr	w1, w1, 6
	str	w1, [x19, 180]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L66:
	sub	w2, w4, w2
	lsl	w3, w2, 6
	add	w2, w3, w2, lsl 3
	udiv	w4, w2, w4
	neg	w4, w4
	b	.L67
	.p2align 3
.L75:
	mov	x0, x19
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	w20, [x19, 228]
	b	.L65
	.size	VEDU_DRV_RCCalculateCurQP, .-VEDU_DRV_RCCalculateCurQP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcQPDeltaByBitRate
	.type	VEDU_DRV_RCCalcQPDeltaByBitRate, %function
VEDU_DRV_RCCalcQPDeltaByBitRate:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, w20
	bls	.L77
	sub	w19, w19, w20
	lsl	w1, w19, 2
	sub	w1, w1, w19
	lsl	w1, w1, 5
	udiv	w1, w1, w20
.L78:
	cmn	w1, #64
	mov	w0, -64
	csel	w1, w1, w0, ge
	mov	w0, 64
	cmp	w1, w0
	csel	w0, w1, w0, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L77:
	sub	w19, w20, w19
	lsl	w1, w19, 6
	add	w19, w1, w19, lsl 3
	udiv	w1, w19, w20
	neg	w1, w1
	b	.L78
	.size	VEDU_DRV_RCCalcQPDeltaByBitRate, .-VEDU_DRV_RCCalcQPDeltaByBitRate
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcQPDeltaByWaterline
	.type	VEDU_DRV_RCCalcQPDeltaByWaterline, %function
VEDU_DRV_RCCalcQPDeltaByWaterline:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w4, w2, [x19, 220]
	mov	w5, -32
	mov	w0, 32
	sub	w1, w2, w4
	ldr	x19, [sp, 16]
	lsl	w2, w1, 2
	sub	w2, w2, w1
	lsl	w3, w2, 5
	add	w2, w2, w3
	add	w2, w2, w1
	lsl	w2, w2, 2
	ldp	x29, x30, [sp], 32
	sdiv	w1, w2, w4
	cmp	w1, w5
	csel	w1, w1, w5, ge
	cmp	w1, w0
	csel	w0, w1, w0, le
	ret
	.size	VEDU_DRV_RCCalcQPDeltaByWaterline, .-VEDU_DRV_RCCalcQPDeltaByWaterline
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits
	.type	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits, %function
VEDU_DRV_RCCalcVBRQPDeltaByInstantBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 540]
	ldr	w2, [x19, 584]
	lsl	w1, w0, 2
	sub	w1, w1, w0
	lsl	w6, w2, 2
	sub	w5, w6, w2
	lsl	w4, w1, 5
	lsl	w3, w5, 5
	add	w1, w1, w4
	add	w1, w1, w0
	sub	w3, w3, w2
	cmp	w1, w3
	mov	w0, 192
	bls	.L85
.L81:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	lsl	w3, w5, 4
	mov	w0, 128
	sub	w5, w3, w5
	cmp	w1, w5, lsl 1
	bhi	.L81
	add	w2, w6, w2
	mov	w0, 64
	ldr	x19, [sp, 16]
	add	w2, w2, w2, lsl 4
	cmp	w1, w2
	csel	w0, wzr, w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCCalcVBRQPDeltaByInstantBits, .-VEDU_DRV_RCCalcVBRQPDeltaByInstantBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcVBRQPDeltaByPicBits
	.type	VEDU_DRV_RCCalcVBRQPDeltaByPicBits, %function
VEDU_DRV_RCCalcVBRQPDeltaByPicBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 84]
	cmp	w2, 200
	beq	.L87
	ldr	w3, [x19, 572]
	ldr	w4, [x19, 576]
	sub	w1, w4, w3
	cmp	w1, wzr
	ble	.L88
	lsl	w5, w1, 3
	mov	w0, 64
	add	w1, w5, w1, lsl 1
	cmp	w4, w1
	csel	w0, wzr, w0, ge
.L89:
	cmp	w2, 1000
	str	wzr, [x19, 572]
	str	w3, [x19, 576]
	bne	.L93
	str	wzr, [x19, 84]
.L93:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L87:
	ldr	w1, [x19, 572]
	mov	w0, 0
	str	wzr, [x19, 572]
	str	w1, [x19, 576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L88:
	neg	w1, w1
	mov	w0, -64
	lsl	w5, w1, 3
	add	w1, w5, w1, lsl 1
	cmp	w4, w1
	csel	w0, wzr, w0, ge
	b	.L89
	.size	VEDU_DRV_RCCalcVBRQPDeltaByPicBits, .-VEDU_DRV_RCCalcVBRQPDeltaByPicBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetQPDeltaForVBR
	.type	VEDU_DRV_RCGetQPDeltaForVBR, %function
VEDU_DRV_RCGetQPDeltaForVBR:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 192
	bl	_mcount
	ldr	w0, [x20, 540]
	ldr	w1, [x20, 584]
	lsl	w2, w0, 2
	sub	w2, w2, w0
	lsl	w6, w1, 2
	sub	w5, w6, w1
	lsl	w4, w2, 5
	lsl	w3, w5, 5
	add	w2, w2, w4
	sub	w3, w3, w1
	add	w0, w2, w0
	cmp	w0, w3
	bhi	.L95
	lsl	w2, w5, 4
	mov	w19, 128
	sub	w5, w2, w5
	cmp	w0, w5, lsl 1
	bls	.L101
.L95:
	ldr	w1, [x20, 84]
	mov	w2, 34079
	movk	w2, 0x51eb, lsl 16
	mov	w3, 200
	mov	w0, 0
	smull	x2, w1, w2
	asr	x2, x2, 38
	sub	w2, w2, w1, asr 31
	msub	w1, w2, w3, w1
	cbnz	w1, .L96
	mov	x0, x20
	bl	VEDU_DRV_RCCalcVBRQPDeltaByPicBits
.L96:
	add	w0, w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L101:
	add	w1, w6, w1
	mov	w19, 64
	add	w1, w1, w1, lsl 4
	cmp	w0, w1
	csel	w19, wzr, w19, ls
	b	.L95
	.size	VEDU_DRV_RCGetQPDeltaForVBR, .-VEDU_DRV_RCGetQPDeltaForVBR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateFrameBits
	.type	VEDU_DRV_RCUpdateFrameBits, %function
VEDU_DRV_RCUpdateFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 228]
	cbz	w0, .L103
	ldr	w0, [x19, 260]
	add	w0, w0, 1
	cmp	w0, 1
	bls	.L109
	mov	w0, 0
	str	wzr, [x19, 260]
.L105:
	add	x0, x19, x0, uxtw 2
	ldr	w1, [x19, 24]
	str	w1, [x0, 232]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L103:
	ldr	w1, [x19, 264]
	add	w1, w1, 1
	cmp	w1, 4
	bhi	.L107
	mov	w0, w1
	str	w1, [x19, 264]
.L108:
	add	x0, x19, x0, uxtw 2
	ldr	w1, [x19, 24]
	str	w1, [x0, 240]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L107:
	str	wzr, [x19, 264]
	b	.L108
	.p2align 3
.L109:
	str	w0, [x19, 260]
	b	.L105
	.size	VEDU_DRV_RCUpdateFrameBits, .-VEDU_DRV_RCUpdateFrameBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalcTimeOfP
	.type	VEDU_DRV_RCCalcTimeOfP, %function
VEDU_DRV_RCCalcTimeOfP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w3, w2, [x19, 232]
	add	x0, x19, 240
	add	x4, x19, 260
	mov	w1, 0
	add	w2, w3, w2
	.p2align 2
.L111:
	ldr	w3, [x0], 4
	cmp	x4, x0
	add	w1, w1, w3
	bne	.L111
	cmp	w1, wzr
	ccmp	w2, wzr, 4, ne
	beq	.L114
	add	w2, w2, w2, lsl 2
	lsl	w1, w1, 1
	mov	w0, 3
	sdiv	w1, w2, w1
	cmp	w1, 2
	bgt	.L117
.L113:
	mov	w1, 1
	stp	w0, w1, [x19, 208]
	mov	w0, 0
.L112:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L117:
	mov	w0, 5
	cmp	w1, w0
	csel	w0, w1, w0, le
	b	.L113
.L114:
	mov	w0, -1
	b	.L112
	.size	VEDU_DRV_RCCalcTimeOfP, .-VEDU_DRV_RCCalcTimeOfP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetTimeOfP
	.type	VEDU_DRV_RCGetTimeOfP, %function
VEDU_DRV_RCGetTimeOfP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	VEDU_DRV_RCUpdateFrameBits
	mov	x0, x19
	bl	VEDU_DRV_RCCalcTimeOfP
	cmp	w0, wzr
	csetm	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCGetTimeOfP, .-VEDU_DRV_RCGetTimeOfP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetTargetFrameBits
	.type	VEDU_DRV_RCGetTargetFrameBits, %function
VEDU_DRV_RCGetTargetFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 36]
	ldr	w1, [x19, 560]
	cmp	w1, w0
	beq	.L129
	ldr	w1, [x19, 28]
	str	w0, [x19, 560]
	udiv	w0, w0, w1
	str	w0, [x19, 96]
.L121:
	ldp	w1, w5, [x19, 40]
	sxtw	x4, w0
	uxtw	x2, w1
	mul	x4, x2, x4
	str	x4, [x19, 88]
	cbnz	w5, .L130
	ldr	w2, [x19, 212]
.L123:
	cmp	w1, 999
	bhi	.L124
	ldr	w0, [x19, 556]
	cmp	w1, w0
	beq	.L125
	str	w1, [x19, 556]
.L125:
	uxtw	x0, w2
	mov	x2, 4294967295
	mul	x0, x0, x4
	cmp	x0, x2
	bhi	.L131
.L127:
	ldr	w2, [x19, 208]
	cmp	w5, wzr
	sub	w2, w2, #1
	add	w1, w2, w1
	udiv	w0, w0, w1
	str	w0, [x19, 176]
	cset	w0, ne
	str	w0, [x19, 228]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L124:
	mul	w0, w0, w2
	cmp	w5, wzr
	str	w0, [x19, 176]
	cset	w0, ne
	str	w0, [x19, 228]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L130:
	ldp	w2, w6, [x19, 188]
	ldr	w3, [x19, 208]
	cmp	w3, w2
	csel	w2, w3, w2, ge
	cmp	w2, w6
	csel	w2, w2, w6, le
	str	w2, [x19, 208]
	b	.L123
	.p2align 3
.L129:
	ldr	w0, [x19, 96]
	b	.L121
	.p2align 3
.L131:
	ldr	x1, .LC6
	ldr	x0, .LC8
	ldr	x1, [x1, 16]
	blr	x1
	mov	w0, -1
	ldp	w1, w5, [x19, 40]
	b	.L127
	.size	VEDU_DRV_RCGetTargetFrameBits, .-VEDU_DRV_RCGetTargetFrameBits
	.align	3
.LC6:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCofFirstFrame
	.type	VEDU_DRV_RCofFirstFrame, %function
VEDU_DRV_RCofFirstFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	VEDU_DRV_RCInitInfo
	mov	x0, x19
	bl	VEDU_DRV_RCInitInstantBits
	mov	x0, x19
	bl	VEDU_DRV_RCGetTargetFrameBits
	ldr	w0, [x19, 176]
	mov	w4, -1
	ldr	w3, [x19, 208]
	ldp	w1, w2, [x19, 12]
	str	w4, [x19, 260]
	udiv	w3, w0, w3
	str	w4, [x19, 264]
	stp	w3, w3, [x19, 240]
	stp	w3, w3, [x19, 248]
	str	w3, [x19, 256]
	stp	w0, w0, [x19, 232]
	bl	VEDU_DRV_EflRcInitQp
	lsl	w1, w0, 6
	ldr	w3, [x19, 216]
	add	w2, w1, 128
	str	w1, [x19, 172]
	str	w2, [x19, 104]
	sub	w0, w0, w3
	stp	w0, w0, [x19, 180]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCofFirstFrame, .-VEDU_DRV_RCofFirstFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_RcOpenOneFrm
	.type	VENC_DRV_RcOpenOneFrm, %function
VENC_DRV_RcOpenOneFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 268]
	cbnz	w0, .L147
	ldr	w0, [x19, 20]
	cbnz	w0, .L148
	ldr	w1, [x19, 28]
	mov	x0, x19
	str	w1, [x19, 536]
	bl	VEDU_DRV_RCCalculateCurQP
	mov	x0, x19
	bl	VEDU_DRV_RCUpdateFrameBits
	mov	x0, x19
	bl	VEDU_DRV_RCCalcTimeOfP
	cbnz	w0, .L140
	mov	x0, x19
	bl	VEDU_DRV_RCGetTargetFrameBits
.L137:
	ldr	w0, [x19, 76]
	cbz	w0, .L138
	ldr	w0, [x19, 180]
	mov	w1, 23
	add	w0, w0, 1
	cmp	w0, 22
	bgt	.L149
.L139:
	str	wzr, [x19, 76]
	str	w1, [x19, 180]
.L138:
	ldr	w1, [x19, 72]
	mov	w0, 0
	cbz	w1, .L135
	ldr	w1, [x19, 180]
	add	w1, w1, 1
	str	w1, [x19, 180]
.L135:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L148:
	mov	x0, x19
	bl	VEDU_DRV_RCofFirstFrame
	b	.L137
	.p2align 3
.L147:
	ldr	w1, [x19, 272]
	mov	w0, 0
	str	w1, [x19, 172]
	lsr	w2, w1, 6
	add	w1, w1, 128
	str	w2, [x19, 180]
	str	w1, [x19, 104]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L149:
	mov	w1, 35
	cmp	w0, w1
	csel	w1, w0, w1, le
	b	.L139
	.p2align 3
.L140:
	mov	w0, -1
	b	.L135
	.size	VENC_DRV_RcOpenOneFrm, .-VENC_DRV_RcOpenOneFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ModifyInfoForBitRatesChange
	.type	ModifyInfoForBitRatesChange, %function
ModifyInfoForBitRatesChange:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w1, w2, [x19, 36]
	ldr	w0, [x19, 28]
	str	w1, [x19, 560]
	udiv	w0, w1, w0
	str	w0, [x19, 96]
	sxtw	x0, w0
	mul	x0, x2, x0
	str	x0, [x19, 88]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ModifyInfoForBitRatesChange, .-ModifyInfoForBitRatesChange
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_EflRCGetCurTimeOfP
	.type	VEDU_DRV_EflRCGetCurTimeOfP, %function
VEDU_DRV_EflRCGetCurTimeOfP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 44]
	cbz	w0, .L152
	ldp	w0, w2, [x19, 188]
	ldr	w1, [x19, 208]
	cmp	w1, w0
	csel	w0, w1, w0, ge
	cmp	w0, w2
	csel	w0, w0, w2, le
	str	w0, [x19, 208]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L152:
	ldr	w0, [x19, 212]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_EflRCGetCurTimeOfP, .-VEDU_DRV_EflRCGetCurTimeOfP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_EflRCCalcTargetFrameBits
	.type	VEDU_DRV_EflRCCalcTargetFrameBits, %function
VEDU_DRV_EflRCCalcTargetFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	uxtw	x19, w1
	bl	_mcount
	ldr	w2, [x20, 40]
	ldr	w0, [x20, 556]
	cmp	w0, w2
	beq	.L159
	ldrsw	x3, [x20, 96]
	uxtw	x0, w2
	str	w2, [x20, 556]
	mul	x0, x3, x0
	str	x0, [x20, 88]
.L156:
	mul	x0, x19, x0
	mov	x1, 4294967295
	cmp	x0, x1
	bls	.L158
	ldr	x1, .LC9
	ldr	x0, .LC10
	ldr	x1, [x1, 16]
	blr	x1
	ldr	w2, [x20, 40]
	mov	w0, -1
.L158:
	ldr	w1, [x20, 208]
	ldp	x19, x20, [sp, 16]
	sub	w1, w1, #1
	add	w2, w1, w2
	ldp	x29, x30, [sp], 32
	udiv	w0, w0, w2
	ret
	.p2align 3
.L159:
	ldr	x0, [x20, 88]
	b	.L156
	.size	VEDU_DRV_EflRCCalcTargetFrameBits, .-VEDU_DRV_EflRCCalcTargetFrameBits
	.align	3
.LC9:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC10:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ModifyInfoForGopChange
	.type	ModifyInfoForGopChange, %function
ModifyInfoForGopChange:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 40]
	ldrsw	x1, [x19, 96]
	str	w0, [x19, 556]
	uxtw	x0, w0
	mul	x0, x1, x0
	str	x0, [x19, 88]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ModifyInfoForGopChange, .-ModifyInfoForGopChange
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCModifyQPForSpecialScene
	.type	VEDU_DRV_RCModifyQPForSpecialScene, %function
VEDU_DRV_RCModifyQPForSpecialScene:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 76]
	cbz	w0, .L162
	ldr	w0, [x19, 180]
	mov	w1, 23
	add	w0, w0, 1
	cmp	w0, 22
	bgt	.L172
.L163:
	str	wzr, [x19, 76]
	str	w1, [x19, 180]
.L162:
	ldr	w0, [x19, 72]
	cbz	w0, .L161
	ldr	w0, [x19, 180]
	add	w0, w0, 1
	str	w0, [x19, 180]
.L161:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L172:
	mov	w1, 35
	cmp	w0, w1
	csel	w1, w0, w1, le
	b	.L163
	.size	VEDU_DRV_RCModifyQPForSpecialScene, .-VEDU_DRV_RCModifyQPForSpecialScene
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateWaterline
	.type	VEDU_DRV_RCUpdateWaterline, %function
VEDU_DRV_RCUpdateWaterline:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 268]
	cbz	w0, .L176
	ldr	w2, [x19, 544]
	ldr	w0, [x19, 176]
	ldr	w1, [x19, 224]
	add	x2, x19, x2, lsl 2
	add	w1, w0, w1
	ldr	w2, [x2, 276]
	sub	w1, w1, w2
	ldr	w2, [x19, 24]
	sub	w0, w1, w0
	add	w0, w2, w0
	str	w0, [x19, 224]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L176:
	ldr	w1, [x19, 224]
	ldr	w0, [x19, 176]
	ldr	w2, [x19, 24]
	sub	w0, w1, w0
	add	w0, w2, w0
	str	w0, [x19, 224]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCUpdateWaterline, .-VEDU_DRV_RCUpdateWaterline
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateInstantBits
	.type	VEDU_DRV_RCUpdateInstantBits, %function
VEDU_DRV_RCUpdateInstantBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 536]
	ldr	w0, [x19, 552]
	cmp	w4, w0
	beq	.L184
	ldr	w1, [x19, 28]
	add	x0, x19, 276
	ldr	w3, [x19, 36]
	add	x2, x19, 536
	udiv	w1, w3, w1
	.p2align 2
.L180:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L180
	mov	w2, 1
	mov	w1, 0
	str	w3, [x19, 540]
	str	wzr, [x19, 544]
	str	w4, [x19, 552]
.L179:
	ldr	w0, [x19, 268]
	cbnz	w0, .L181
	str	w3, [x19, 548]
.L181:
	add	x1, x19, x1, uxtw 2
	ldr	w5, [x19, 24]
	cmp	w4, w2
	add	w3, w3, w5
	csel	w2, w2, wzr, hi
	ldr	w0, [x1, 276]
	sub	w0, w3, w0
	str	w0, [x19, 540]
	str	w5, [x1, 276]
	str	w2, [x19, 544]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L184:
	ldr	w1, [x19, 544]
	ldr	w3, [x19, 540]
	add	w2, w1, 1
	b	.L179
	.size	VEDU_DRV_RCUpdateInstantBits, .-VEDU_DRV_RCUpdateInstantBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateInfo
	.type	VEDU_DRV_RCUpdateInfo, %function
VEDU_DRV_RCUpdateInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 268]
	cbz	w0, .L186
	ldr	w0, [x19, 544]
	cbz	w0, .L191
	sub	w0, w0, #1
	str	w0, [x19, 544]
.L188:
	add	x3, x19, x0, uxtw 2
	ldr	w1, [x19, 176]
	ldr	w2, [x19, 224]
	ldr	w0, [x3, 276]
	add	w2, w1, w2
	sub	w0, w2, w0
	b	.L189
	.p2align 3
.L186:
	ldr	w1, [x19, 176]
	ldr	w0, [x19, 224]
.L189:
	ldr	w2, [x19, 24]
	sub	w1, w0, w1
	mov	x0, x19
	add	w1, w2, w1
	str	w1, [x19, 224]
	bl	VEDU_DRV_RCUpdateInstantBits
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L191:
	ldr	w0, [x19, 536]
	sub	w0, w0, #1
	str	w0, [x19, 544]
	b	.L188
	.size	VEDU_DRV_RCUpdateInfo, .-VEDU_DRV_RCUpdateInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ModifyInfoForFrmRateChange
	.type	ModifyInfoForFrmRateChange, %function
ModifyInfoForFrmRateChange:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 536]
	ldr	w0, [x19, 552]
	cmp	w3, w0
	beq	.L192
	ldr	w1, [x19, 28]
	add	x0, x19, 276
	ldr	w4, [x19, 36]
	add	x2, x19, 536
	udiv	w1, w4, w1
	.p2align 2
.L194:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L194
	str	w4, [x19, 540]
	str	wzr, [x19, 544]
	str	w3, [x19, 552]
.L192:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ModifyInfoForFrmRateChange, .-ModifyInfoForFrmRateChange
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCIsNeedRecoding
	.type	VEDU_DRV_RCIsNeedRecoding, %function
VEDU_DRV_RCIsNeedRecoding:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 68]
	cbnz	w0, .L199
	ldr	w0, [x19, 268]
	cbnz	w0, .L199
	ldr	w0, [x19, 44]
	ldr	w1, [x19, 176]
	cbnz	w0, .L202
	ldr	w0, [x19, 24]
	cmp	w0, w1, lsl 1
	cset	w1, hi
.L201:
	eor	w0, w1, 1
	str	w1, [x19, 268]
	neg	w0, w0
.L198:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L202:
	lsl	w0, w1, 2
	ldr	w2, [x19, 24]
	sub	w0, w0, w1
	cmp	w2, w0, lsr 1
	cset	w1, hi
	b	.L201
	.p2align 3
.L199:
	mov	w0, -1
	str	wzr, [x19, 268]
	b	.L198
	.size	VEDU_DRV_RCIsNeedRecoding, .-VEDU_DRV_RCIsNeedRecoding
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCStartQPChange
	.type	VEDU_DRV_RCStartQPChange, %function
VEDU_DRV_RCStartQPChange:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 24]
	mov	w1, 0
	ldr	w0, [x19, 176]
	cmp	w0, w3
	bhi	.L204
	.p2align 2
.L205:
	lsl	w2, w0, 7
	add	w1, w1, 1
	add	w0, w2, w0, lsl 4
	asr	w0, w0, 7
	cmp	w0, w3
	bls	.L205
	lsl	w1, w1, 6
.L204:
	ldp	w0, w2, [x19, 4]
	ldr	w3, [x19, 172]
	lsl	w0, w0, 6
	lsl	w2, w2, 6
	add	w1, w3, w1
	cmp	w1, w0
	csel	w0, w1, w0, ge
	cmp	w2, w0
	csel	w0, w2, w0, le
	str	w0, [x19, 272]
	cmp	w3, w0
	csetm	w0, eq
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VEDU_DRV_RCStartQPChange, .-VEDU_DRV_RCStartQPChange
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	D_VENC_RC_CLIP3
	.type	D_VENC_RC_CLIP3, %function
D_VENC_RC_CLIP3:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w2
	bl	_mcount
	cmp	w19, w21
	csel	w0, w19, w21, ge
	ldr	x21, [sp, 32]
	cmp	w20, w0
	csel	w0, w20, w0, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	D_VENC_RC_CLIP3, .-D_VENC_RC_CLIP3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateIMBInfo
	.type	VEDU_DRV_RCUpdateIMBInfo, %function
VEDU_DRV_RCUpdateIMBInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 80]
	cmp	w0, 1
	beq	.L210
	ldr	w1, [x19, 116]
.L211:
	mov	x0, x19
	ldr	w6, [x19, 136]
	ldp	w2, w3, [x19, 120]
	ldp	w4, w5, [x19, 128]
	stp	w4, w5, [x19, 132]
	stp	w2, w3, [x19, 124]
	str	w6, [x19, 140]
	add	x5, x19, 144
	str	w1, [x0, 120]!
	mov	w3, 0
	mov	w2, 6
	b	.L214
	.p2align 3
.L218:
	ldr	w1, [x0]
.L214:
	cmp	w1, wzr
	add	x0, x0, 4
	cset	w4, eq
	cmp	x5, x0
	add	w3, w3, w1
	sub	w2, w2, w4
	bne	.L218
	mov	w0, 0
	cbz	w2, .L215
	sdiv	w0, w3, w2
.L215:
	str	w0, [x19, 144]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L210:
	ldr	w1, [x19, 144]
	str	w1, [x19, 116]
	b	.L211
	.size	VEDU_DRV_RCUpdateIMBInfo, .-VEDU_DRV_RCUpdateIMBInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_RcCloseOneFrm
	.type	VENC_DRV_RcCloseOneFrm, %function
VENC_DRV_RcCloseOneFrm:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	mov	x22, x3
	bl	_mcount
	ldr	w0, [x19, 60]
	cbnz	w0, .L220
	ldr	w0, [x19, 64]
	cbnz	w0, .L220
	str	wzr, [x19, 20]
	mov	w4, 0
	ldr	w2, [x19, 32]
	ldr	w1, [x21]
	sub	w1, w1, w2
	str	w1, [x21]
	ldr	w1, [x19, 44]
	cbz	w1, .L242
.L229:
	str	w4, [x22]
	ldr	x1, [x20]
	ldr	w2, [x19, 24]
	cbz	x1, .L231
	ldp	w3, w4, [x20, 16]
	cmp	w3, w4
	bhi	.L243
	ldr	w3, [x20, 12]
	add	x1, x1, x3, lsl 2
.L233:
	add	w0, w2, w0
	str	w0, [x20, 16]
	str	w2, [x1]
	ldp	w1, w0, [x20, 8]
	add	w0, w0, 1
	str	w0, [x20, 12]
	cmp	w0, w1
	bcc	.L231
	sub	w0, w0, w1
	str	w0, [x20, 12]
.L231:
	mov	x0, x19
	bl	VEDU_DRV_RCUpdateIMBInfo
	ldr	w0, [x19, 44]
	cbnz	w0, .L244
	ldr	w0, [x19, 172]
	str	w0, [x19, 104]
.L236:
	ldr	w0, [x19, 24]
	ldr	w1, [x19, 176]
	stp	w1, w0, [x19, 108]
	mov	w0, 0
.L228:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L244:
	ldr	w0, [x19, 172]
	str	w0, [x19, 100]
	b	.L236
	.p2align 3
.L242:
	ldr	w4, [x22]
	add	w4, w4, 1
	b	.L229
	.p2align 3
.L243:
	ldr	w4, [x20, 12]
	ldr	w0, [x1, w4, uxtw 2]
	add	x1, x1, x4, uxtw 2
	sub	w0, w3, w0
	b	.L233
	.p2align 3
.L220:
	ldp	w3, w2, [x19, 48]
	ldr	w1, [x19, 56]
	mov	w0, 2
	cmp	w3, wzr
	sub	w5, w2, #1
	cset	w4, eq
	ldr	w3, [x19, 20]
	cmp	w2, wzr
	sub	w1, w1, #1
	csel	w0, w5, w0, ne
	str	w1, [x19, 56]
	stp	w4, w0, [x19, 48]
	cbz	w3, .L245
.L224:
	ldr	w1, [x19, 112]
	mov	w0, -1
	str	w1, [x19, 24]
	b	.L228
	.p2align 3
.L245:
	ldr	x0, [x20]
	cbz	x0, .L224
	ldp	w1, w2, [x20, 16]
	cmp	w1, w2
	bls	.L226
	ldr	w2, [x20, 12]
	ldr	w3, [x0, w2, uxtw 2]
	add	x0, x0, x2, uxtw 2
	sub	w1, w1, w3
	str	w1, [x20, 16]
.L227:
	str	wzr, [x0]
	ldp	w1, w0, [x20, 8]
	add	w0, w0, 1
	str	w0, [x20, 12]
	cmp	w0, w1
	bcc	.L224
	sub	w0, w0, w1
	str	w0, [x20, 12]
	b	.L224
	.p2align 3
.L226:
	ldr	w1, [x20, 12]
	str	wzr, [x20, 16]
	add	x0, x0, x1, lsl 2
	b	.L227
	.size	VENC_DRV_RcCloseOneFrm, .-VENC_DRV_RcCloseOneFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_EflRcAverage
	.type	VENC_DRV_EflRcAverage, %function
VENC_DRV_EflRcAverage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, wzr
	mov	w3, w19
	ble	.L251
	mov	x0, 0
	mov	w4, 0
	.p2align 2
.L249:
	ldr	w2, [x20, x0, lsl 2]
	add	x0, x0, 1
	cmp	w2, wzr
	add	w4, w4, w2
	cset	w2, eq
	cmp	w19, w0
	sub	w3, w3, w2
	bgt	.L249
.L247:
	mov	w0, 0
	cbz	w3, .L250
	sdiv	w0, w4, w3
.L250:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L251:
	mov	w4, 0
	b	.L247
	.size	VENC_DRV_EflRcAverage, .-VENC_DRV_EflRcAverage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_CalRCRatio
	.type	VENC_DRV_CalRCRatio, %function
VENC_DRV_CalRCRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, w20
	bhi	.L258
	sub	w19, w20, w19
	lsl	w0, w19, 2
	sub	w0, w0, w19
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w0, w0, w19
	udiv	w0, w0, w20
	ldp	x19, x20, [sp, 16]
	neg	w0, w0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L258:
	sub	w19, w19, w20
	lsl	w0, w19, 2
	sub	w0, w0, w19
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w0, w0, w19
	udiv	w0, w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VENC_DRV_CalRCRatio, .-VENC_DRV_CalRCRatio
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	MaxIPropDeltaQP, %object
	.size	MaxIPropDeltaQP, 208
MaxIPropDeltaQP:
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	9
	.word	9
	.word	8
	.word	8
	.word	7
	.word	7
	.word	6
	.word	6
	.word	5
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	TabLnx, %object
	.size	TabLnx, 256
TabLnx:
	.word	0
	.word	-1216
	.word	-972
	.word	-830
	.word	-729
	.word	-651
	.word	-587
	.word	-533
	.word	-486
	.word	-445
	.word	-408
	.word	-374
	.word	-344
	.word	-316
	.word	-290
	.word	-265
	.word	-243
	.word	-221
	.word	-201
	.word	-182
	.word	-164
	.word	-147
	.word	-131
	.word	-115
	.word	-100
	.word	-86
	.word	-72
	.word	-59
	.word	-46
	.word	-34
	.word	-22
	.word	-11
	.word	0
	.word	10
	.word	21
	.word	31
	.word	41
	.word	50
	.word	60
	.word	69
	.word	78
	.word	86
	.word	95
	.word	103
	.word	111
	.word	119
	.word	127
	.word	134
	.word	142
	.word	149
	.word	156
	.word	163
	.word	170
	.word	177
	.word	183
	.word	190
	.word	196
	.word	202
	.word	208
	.word	214
	.word	220
	.word	226
	.word	232
	.word	237
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC7:
	ASCII(.string	"u32BitsPerGop > 0xffffffff!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
