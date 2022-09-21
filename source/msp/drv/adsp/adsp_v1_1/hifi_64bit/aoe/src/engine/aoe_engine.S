#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_engine.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	ENGINEDestroyChn, %function
ENGINEDestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1
	ldr	w0, [x19, 12]
	cbz	w0, .L11
.L3:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L11:
	ldr	x1, [x19, 104]
	cbz	x1, .L3
	mov	w0, 26
	bl	HI_ADSP_FREE
	str	xzr, [x19, 104]
	b	.L3
	.size	ENGINEDestroyChn, .-ENGINEDestroyChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEOutRawFrame, %function
ENGINEOutRawFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	bl	_mcount
	mov	w0, w19
	bl	AIP_GetRingIn
	mov	x19, x0
	mov	w0, w20
	bl	AOP_GetRingOut
	cmp	x19, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L12
	mov	x1, x0
	mov	w3, 3
	mov	w2, w21
	mov	x0, x19
	bl	RBUF_CopyData
.L12:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ENGINEOutRawFrame, .-ENGINEOutRawFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEMixData, %function
ENGINEMixData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x23, x2
	bl	_mcount
	str	xzr, [x29, 104]
	add	x0, x29, 72
	add	x2, x29, 88
	mov	x1, x0
	ldp	w24, w22, [x19]
	stp	xzr, xzr, [x0]
	mov	w0, w20
	stp	xzr, xzr, [x2]
	bl	AIP_QueryFiFoInfo
	ldr	w2, [x19, 76]
	ldr	w0, [x29, 96]
	cmp	w0, w2
	bcc	.L17
	ldr	w21, [x29, 92]
	cmp	w21, w2
	bcc	.L21
	ldr	w5, [x19, 80]
	mov	w3, w24
	ldr	w1, [x29, 80]
	mov	x0, x23
	ldr	x4, [x29, 72]
	udiv	w2, w2, w5
	add	x1, x4, x1
	mul	w2, w2, w22
	bl	UTIL_MixerPro
.L20:
	ldr	w1, [x19, 76]
	mov	w0, w20
	bl	AIP_ReadDataComplete
.L17:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L21:
	ldr	w2, [x19, 80]
	mov	w3, w24
	ldr	w0, [x29, 80]
	ldr	x1, [x29, 72]
	udiv	w2, w21, w2
	add	x1, x1, x0
	mov	x0, x23
	mul	w2, w2, w22
	bl	UTIL_MixerPro
	ldp	w2, w4, [x19, 76]
	ldr	x1, [x29, 72]
	mov	w3, w24
	sub	w2, w2, w21
	add	x0, x23, x21, uxtw
	udiv	w2, w2, w4
	mul	w2, w2, w22
	bl	UTIL_MixerPro
	b	.L20
	.size	ENGINEMixData, .-ENGINEMixData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINECheckAipData.isra.0, %function
ENGINECheckAipData.isra.0:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	uxtw	x20, w0
	mov	x0, x30
	uxtw	x19, w1
	uxtw	x21, w2
	bl	_mcount
	cmp	w19, wzr
	ccmp	w20, wzr, 4, ne
	beq	.L23
	mov	w0, 0
	cbz	w20, .L24
	mov	w3, 0
	uxtw	x2, w21
	.p2align 2
.L26:
	asr	x4, x20, x3
	asr	x1, x2, x3
	tbz	x4, 0, .L28
	tbz	x1, 0, .L44
	orr	w0, w0, 1
.L28:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L26
.L24:
	cbz	w19, .L29
.L45:
	mov	w3, 0
	.p2align 2
.L32:
	asr	x4, x19, x3
	asr	x1, x21, x3
	tbz	x4, 0, .L30
	tbz	x1, 0, .L31
	orr	w0, w0, 2
.L30:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L32
.L29:
	and	w0, w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L23:
	cmp	w21, wzr
	ldr	x21, [sp, 32]
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L31:
	and	w0, w0, -3
	b	.L29
	.p2align 3
.L44:
	and	w0, w0, -2
	cbz	w19, .L29
	b	.L45
	.size	ENGINECheckAipData.isra.0, .-ENGINECheckAipData.isra.0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINECheckAopSpace.isra.1, %function
ENGINECheckAopSpace.isra.1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	uxtw	x19, w2
	mov	w20, w1
	bl	_mcount
	mov	w0, 0
	cbz	w19, .L68
	cbz	w21, .L48
	uxtw	x5, w21
	mov	w3, 0
	uxtw	x2, w19
	.p2align 2
.L50:
	asr	x4, x5, x3
	asr	x1, x2, x3
	tbz	x4, 0, .L52
	tbz	x1, 0, .L70
	orr	w0, w0, 1
.L52:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L50
.L48:
	cbz	w20, .L53
.L72:
	uxtw	x1, w20
	mov	w3, 0
	.p2align 2
.L57:
	asr	x4, x1, x3
	asr	x2, x19, x3
	tbz	x4, 0, .L54
	tbz	x2, 0, .L55
	orr	w0, w0, 2
.L54:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L57
.L56:
	cbnz	w21, .L58
	and	w0, w0, 2
.L68:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L53:
	cbz	w21, .L71
.L58:
	and	w0, w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L71:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L55:
	and	w0, w0, -3
	b	.L56
	.p2align 3
.L70:
	and	w0, w0, -2
	cbz	w20, .L53
	b	.L72
	.size	ENGINECheckAopSpace.isra.1, .-ENGINECheckAopSpace.isra.1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINECreateChn, %function
ENGINECreateChn:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC1
	ldr	x3, .LC0
	mov	w1, 0
	mov	x2, 28
	add	x0, x29, 64
	ldr	x19, [x3, w21, uxtw 3]
	ldr	x3, [x20, 40]
	blr	x3
	ldr	w1, [x19]
	add	x0, x29, 64
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L91
	ldr	w1, [x19]
	add	x0, x29, 68
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L91
	ldr	w1, [x19]
	add	x0, x29, 72
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L91
	ldr	w1, [x19]
	add	x0, x29, 76
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L91
	mov	w1, 168
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L91
	ldr	x3, [x20, 40]
	mov	x2, 168
	mov	w1, 0
	blr	x3
	ldr	x3, [x20, 48]
	mov	x2, 28
	add	x1, x29, 64
	mov	x0, x19
	blr	x3
	ldp	w1, w0, [x19]
	bl	UTIL_CalcFrameSize
	ldr	w2, [x19, 8]
	mov	w1, 19923
	mov	w3, 48000
	movk	w1, 0x1062, lsl 16
	cmp	w2, w3
	add	w2, w2, w2, lsl 2
	umull	x1, w2, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	beq	.L92
	and	w2, w1, 3
	cbz	w2, .L77
	and	w1, w1, -4
	add	w1, w1, 4
.L77:
	mul	w2, w0, w1
	ldp	w1, w0, [x19]
	str	w2, [x19, 76]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 80]
	ldr	w1, [x19, 76]
	ldr	w2, [x19, 12]
	udiv	w0, w1, w0
	str	w0, [x19, 16]
	cbz	w2, .L93
.L78:
	str	w21, [x19, 72]
	mov	w0, 1
	str	w0, [x19, 84]
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L93:
	ldp	w5, w6, [x19]
	ldr	w4, [x19, 8]
	mov	x2, 32
	ldr	x3, [x20, 48]
	stp	w1, w0, [x19, 112]
	stp	w5, w6, [x19, 120]
	stp	w4, wzr, [x19, 128]
	add	x1, x19, 104
	str	xzr, [x19, 104]
	add	x0, x19, 136
	blr	x3
	ldr	w22, [x19, 112]
	ldr	w1, [x19, 144]
	mov	w0, 26
	add	w22, w22, w1
	mov	w1, w22
	bl	HI_ADSP_MALLOC
	mov	x23, x0
	cbz	x0, .L79
	ldr	x3, [x20, 40]
	uxtw	x2, w22
	mov	w1, 0
	blr	x3
	str	x23, [x19, 104]
	ldr	w0, [x19, 112]
	add	x23, x23, x0
	str	x23, [x19, 136]
	b	.L78
.L79:
	mov	x0, x19
	bl	ENGINEDestroyChn
.L91:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	x0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L92:
	and	w2, w1, 255
	cbz	w2, .L77
	and	w1, w1, -256
	add	w1, w1, 256
	b	.L77
	.size	ENGINECreateChn, .-ENGINECreateChn
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC1:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_Process
	.type	ENGINE_Process, %function
ENGINE_Process:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x22, .LC6
	ldr	x28, .LC5
	.p2align 2
.L193:
	ldr	x1, [x28]
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L95
	ldr	w0, [x1, 4]
	ands	w0, w0, 3
	beq	.L97
	cmp	w0, 1
	beq	.L98
	ldr	w0, [x1, 4]
	mov	w2, 4
	bfi	w0, w2, 3, 4
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, w2
	str	w0, [x1, 4]
.L95:
	ldr	x27, [x28, 48]
.L106:
	cbz	x27, .L109
.L102:
	ldr	w0, [x27, 84]
	cmp	w0, 1
	beq	.L287
.L109:
	add	w19, w19, 1
	add	x28, x28, 8
	cmp	w19, 6
	bne	.L193
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L98:
	ldr	x27, [x28, 48]
	cbz	x27, .L109
	ldr	w0, [x27, 84]
	cmp	w0, 1
	beq	.L288
.L107:
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L102
	ldr	w0, [x1, 4]
	and	w0, w0, -121
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, 4
	str	w0, [x1, 4]
	ldr	w0, [x27, 84]
	cmp	w0, 1
	bne	.L109
	.p2align 2
.L287:
	ldr	w0, [x27]
	mov	w21, 0
	str	w0, [x29, 112]
	mov	w23, 0
	ldr	w0, [x27, 4]
	mov	w26, 0
	str	w0, [x29, 100]
	ldr	x24, [x28]
	ldr	w0, [x27, 16]
	str	w0, [x29, 108]
	ldr	w20, [x24, 12]
	stp	wzr, wzr, [x29, 116]
	str	wzr, [x29, 124]
	uxth	w20, w20
	uxth	x25, w20
	b	.L116
	.p2align 3
.L111:
	add	w26, w26, 1
	cmp	w26, 8
	beq	.L289
.L116:
	asr	x0, x25, x26
	tbz	x0, 0, .L111
	mov	w0, w26
	add	x1, x29, 176
	bl	AOP_GetChnStatus
	ldr	w0, [x29, 176]
	cmp	w0, 1
	bne	.L111
	ldr	w0, [x29, 180]
	cmp	w0, 1
	mov	x0, 1
	lsl	x6, x0, x26
	beq	.L290
	ldr	w0, [x29, 124]
	orr	w0, w0, w6
	str	w0, [x29, 124]
.L113:
	ldr	w1, [x29, 112]
	ldr	w0, [x29, 184]
	cmp	w1, w0
	beq	.L291
.L114:
	orr	w23, w23, w6
.L115:
	ldr	w0, [x29, 108]
	ldr	w1, [x29, 192]
	str	w6, [x29, 104]
	mul	w1, w0, w1
	mov	w0, w26
	add	w26, w26, 1
	bl	AOP_QueryRbfFree
	cmp	w0, wzr
	ldr	w6, [x29, 104]
	orr	w6, w21, w6
	csel	w21, w6, w21, ne
	cmp	w26, 8
	bne	.L116
	.p2align 2
.L289:
	ldr	w0, [x29, 120]
	str	w0, [x27, 48]
	ldr	w0, [x29, 124]
	str	w0, [x27, 52]
	ldr	w0, [x29, 116]
	stp	wzr, w20, [x27, 40]
	stp	w23, w21, [x27, 60]
	stp	wzr, wzr, [x27, 32]
	str	w0, [x27, 56]
	mov	w21, 0
	mov	x20, 1
	ldr	w0, [x24, 8]
	uxth	w0, w0
	str	w0, [x27, 28]
	b	.L129
	.p2align 3
.L117:
	add	w21, w21, 1
	cmp	w21, 8
	beq	.L128
.L294:
	ldr	w0, [x27, 28]
.L129:
	uxtw	x0, w0
	asr	x0, x0, x21
	tbz	x0, 0, .L117
	mov	w0, w21
	add	x1, x29, 176
	bl	AIP_GetChnStatus
	ldr	w0, [x29, 176]
	cmp	w0, 1
	beq	.L292
	ldr	w0, [x27, 12]
	cbnz	w0, .L117
	ldr	w23, [x27, 112]
	mov	w0, w21
	bl	AIP_QueryFiFoBusy
	cmp	w23, w0
	bhi	.L117
	cbz	w23, .L117
	ldr	w1, [x27, 40]
	lsl	x0, x20, x21
	orr	w1, w1, w0
	str	w1, [x27, 40]
	ldr	w1, [x29, 180]
	cmp	w1, 1
	beq	.L293
	ldr	w1, [x27, 36]
	add	w21, w21, 1
	cmp	w21, 8
	orr	w0, w1, w0
	str	w0, [x27, 36]
	bne	.L294
	.p2align 2
.L128:
	ldr	x25, [x28, 48]
	ldr	w0, [x25, 12]
	cbnz	w0, .L295
	ldr	w0, [x25, 96]
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L152
	mov	w24, 0
	mov	w21, 0
	mov	w23, 0
	mov	w20, 0
	mov	x26, 1
	b	.L155
	.p2align 3
.L153:
	add	w20, w20, 1
	cmp	w20, 8
	beq	.L296
.L155:
	ldr	w0, [x25, 28]
	asr	x0, x0, x20
	tbz	x0, 0, .L153
	add	x1, x29, 176
	mov	w0, w20
	bl	AIP_GetChnStatus
	ldr	w1, [x29, 176]
	lsl	x2, x26, x20
	orr	w3, w21, w2
	cbnz	w1, .L154
	ldr	w0, [x29, 184]
	add	w20, w20, 1
	orr	w23, w23, w2
	cmp	w0, 1
	csel	w21, w3, w21, eq
	cmp	w20, 8
	bne	.L155
	.p2align 2
.L296:
	ldr	w20, [x25, 92]
	uxtw	x27, w21
	mov	w26, 0
	str	w23, [x25, 92]
	b	.L157
	.p2align 3
.L156:
	add	w26, w26, 1
	cmp	w26, 8
	beq	.L297
.L157:
	asr	x0, x27, x26
	tbz	x0, 0, .L156
	mov	w0, w26
	add	w26, w26, 1
	bl	AIP_FlushCutoffFlag
	cmp	w26, 8
	bne	.L157
.L297:
	cbnz	w24, .L298
	sub	w23, w23, w20
	cmp	w23, w21
	bls	.L299
	mov	w0, 2
	str	wzr, [x25, 88]
	str	w0, [x25, 96]
.L162:
	ldp	w0, w1, [x25, 48]
	ldr	w2, [x25, 64]
	bl	ENGINECheckAopSpace.isra.1
	cbz	w0, .L109
	ldp	w0, w1, [x25, 32]
	ldr	w2, [x25, 40]
	bl	ENGINECheckAipData.isra.0
	cbz	w0, .L109
	mov	w0, 3
	str	w0, [x29, 176]
	ldr	w2, [x25, 12]
	cbz	w2, .L300
.L173:
	ldr	w0, [x25, 96]
	cmp	w0, 2
	bne	.L109
.L178:
	ldr	w0, [x25, 88]
	add	w0, w0, 1
	str	w0, [x25, 88]
.L179:
	ldr	w21, [x25, 48]
	str	w21, [x29, 136]
	ldr	w0, [x25, 52]
	str	w0, [x29, 140]
	cbnz	w2, .L109
	mov	x24, 0
	add	x23, x25, 104
.L192:
	cbz	w21, .L191
	uxtw	x21, w21
	mov	w20, 0
	b	.L190
	.p2align 3
.L186:
	add	w20, w20, 1
	cmp	w20, 8
	beq	.L191
.L190:
	asr	x0, x21, x20
	tbz	x0, 0, .L186
	mov	w0, w20
	bl	AOP_WriteBuffProcTryCnt
	mov	w0, w20
	add	x1, x29, 144
	bl	AOP_GetChnStatus
	ldr	w0, [x25, 64]
	asr	x0, x0, x20
	tbz	x0, 0, .L186
	mov	w0, w20
	bl	AOP_WriteBuffProcOKCnt
	ldr	w0, [x25, 68]
	mov	x2, 32
	cbz	w0, .L188
	ldr	w0, [x29, 164]
	cbz	w0, .L301
.L188:
	ldr	x3, [x22, 48]
	mov	x1, x23
	add	x0, x29, 176
	blr	x3
.L189:
	mov	w0, w20
	add	x1, x29, 176
	bl	AOP_WriteRbfData
	mov	w0, w20
	bl	AOP_ProcDelayCompensation
	b	.L186
	.p2align 3
.L97:
	ldr	x0, [x28, 48]
	cbz	x0, .L302
	ldr	w2, [x0, 84]
	cbz	w2, .L303
.L104:
	mov	w2, 1
	str	w2, [x0, 84]
	ldr	w2, [x1, 4]
	tbnz	x2, 2, .L198
	mov	x2, x0
.L103:
	ldr	w0, [x1, 4]
	mov	x27, x2
	and	w0, w0, -121
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, 4
	str	w0, [x1, 4]
	b	.L106
	.p2align 3
.L292:
	ldr	w0, [x29, 180]
	cmp	w0, 1
	beq	.L304
	ldr	w1, [x27, 36]
	lsl	x0, x20, x21
	orr	w0, w1, w0
	str	w0, [x27, 36]
.L120:
	ldr	w0, [x27, 12]
	cbz	w0, .L121
	ldr	w23, [x27, 76]
	mov	w0, w21
	bl	AIP_QueryBusy
	cmp	w23, w0
	bhi	.L117
.L123:
	cbz	w23, .L117
	ldr	w1, [x27, 40]
	lsl	x0, x20, x21
	orr	w0, w1, w0
	str	w0, [x27, 40]
	b	.L117
	.p2align 3
.L154:
	orr	w24, w24, w2
	b	.L153
	.p2align 3
.L198:
	mov	x27, x0
	b	.L106
	.p2align 3
.L121:
	ldr	w23, [x27, 112]
	mov	w0, w21
	bl	AIP_QueryFiFoBusy
	cmp	w23, w0
	bls	.L123
	b	.L117
	.p2align 3
.L298:
	ldr	w0, [x25, 96]
.L152:
	cmp	w0, 1
	beq	.L194
	cmp	w0, 2
	bne	.L162
	ldr	w0, [x25, 88]
	cmp	w0, 2
	beq	.L194
	b	.L162
	.p2align 3
.L291:
	ldr	w1, [x29, 100]
	ldr	w0, [x29, 188]
	cmp	w1, w0
	bne	.L114
	ldr	w0, [x29, 116]
	orr	w0, w0, w6
	str	w0, [x29, 116]
	b	.L115
	.p2align 3
.L295:
	str	wzr, [x29, 136]
	str	wzr, [x29, 144]
	ldr	w0, [x25, 44]
	uxtw	x1, w0
	tbnz	x0, 0, .L131
	mov	w21, 1
	.p2align 2
.L135:
	asr	x0, x1, x21
	tbnz	x0, 0, .L305
	add	w21, w21, 1
	cmp	w21, 8
	bne	.L135
	ldr	w0, [x25, 28]
	uxtw	x1, w0
	tbnz	x0, 0, .L109
	mov	w2, 1
.L134:
	mov	w20, 1
	b	.L138
	.p2align 3
.L137:
	add	w20, w20, 1
	cmp	w20, 8
	beq	.L109
.L138:
	asr	x0, x1, x20
	tbz	x0, 0, .L137
	cmp	w20, 8
	cset	w0, eq
.L133:
	orr	w0, w2, w0
	cbnz	w0, .L109
.L196:
	add	x1, x29, 176
	mov	w0, w20
	bl	AIP_GetChnStatus
	ldr	w23, [x29, 176]
	cbnz	w23, .L139
	ldr	w0, [x25, 12]
	stp	wzr, wzr, [x25, 20]
	cmp	w0, 2
	beq	.L109
.L140:
	ldp	w0, w1, [x25, 48]
	ldr	w2, [x25, 64]
	bl	ENGINECheckAopSpace.isra.1
	cbz	w0, .L109
	ldp	w0, w1, [x25, 32]
	ldr	w2, [x25, 40]
	bl	ENGINECheckAipData.isra.0
	cbz	w0, .L109
	ldr	w2, [x25, 76]
	mov	w0, w20
	mov	w1, w21
	bl	ENGINEOutRawFrame
	mov	w0, w21
	bl	AOP_ProcDelayCompensation
	b	.L109
	.p2align 3
.L303:
	bl	ENGINEDestroyChn
	mov	w0, w19
	bl	ENGINECreateChn
	str	x0, [x28, 48]
	cbz	x0, .L105
	ldr	x1, [x28]
	b	.L104
	.p2align 3
.L288:
	str	wzr, [x27, 84]
	b	.L107
	.p2align 3
.L290:
	ldr	w0, [x29, 120]
	orr	w0, w0, w6
	str	w0, [x29, 120]
	b	.L113
	.p2align 3
.L304:
	ldr	w1, [x27, 32]
	lsl	x0, x20, x21
	orr	w0, w1, w0
	str	w0, [x27, 32]
	b	.L120
	.p2align 3
.L299:
	mov	w0, 1
	str	w0, [x25, 96]
.L194:
	bl	AOE_GetWKBuf
	str	x0, [x29, 144]
	ldr	x0, .LC6
	mov	x2, 32
	add	x1, x29, 144
	mov	w20, 0
	ldr	x3, [x0, 48]
	ldr	w0, [x25, 76]
	str	w0, [x29, 152]
	add	x0, x29, 176
	ldr	w5, [x25, 16]
	str	w5, [x29, 156]
	ldr	w5, [x25, 4]
	str	w5, [x29, 164]
	ldr	w5, [x25]
	str	w5, [x29, 160]
	ldr	w5, [x25, 8]
	str	w5, [x29, 168]
	ldr	w5, [x25, 12]
	str	w5, [x29, 172]
	blr	x3
	bl	AOE_GetWKBuf
	.p2align 2
.L166:
	ldr	w1, [x25, 48]
	mov	w0, w20
	asr	x1, x1, x20
	tbnz	x1, 0, .L164
	ldr	w1, [x25, 52]
	asr	x1, x1, x20
	tbz	x1, 0, .L165
.L164:
	bl	AOP_Flush
.L165:
	add	w20, w20, 1
	cmp	w20, 8
	bne	.L166
	str	wzr, [x25, 88]
	str	wzr, [x25, 96]
	b	.L162
	.p2align 3
.L191:
	add	x24, x24, 4
	cmp	x24, 8
	beq	.L109
	add	x0, x29, 136
	ldr	w21, [x24, x0]
	b	.L192
	.p2align 3
.L302:
	mov	w0, w19
	bl	ENGINECreateChn
	str	x0, [x28, 48]
	mov	x27, x0
	cbz	x0, .L105
	mov	w0, 1
	str	w0, [x27, 84]
	mov	x2, x27
	ldr	x1, [x28]
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L102
	b	.L103
	.p2align 3
.L305:
	ldr	w0, [x25, 28]
	cmp	w21, 8
	cset	w2, eq
	uxtw	x1, w0
	tbz	x0, 0, .L134
	mov	w0, 0
	mov	w20, 0
	b	.L133
	.p2align 3
.L293:
	ldr	w1, [x27, 32]
	orr	w0, w1, w0
	str	w0, [x27, 32]
	b	.L117
.L105:
	ldr	x0, [x28]
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L109
	ldr	w1, [x0, 4]
	mov	w2, 3
	bfi	w1, w2, 3, 4
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L109
.L139:
	ldr	w0, [x25, 12]
	cmp	w0, 2
	bne	.L140
	ldp	w0, w1, [x25, 48]
	ldr	w2, [x25, 64]
	bl	ENGINECheckAopSpace.isra.1
	cmp	w23, 1
	ccmp	w0, wzr, 4, eq
	beq	.L109
	ldr	w1, [x25, 20]
	str	w1, [x29, 136]
	mov	w23, w1
	ldr	w0, [x25, 24]
	str	w0, [x29, 144]
	orr	w0, w1, w0
	cbz	w0, .L306
.L141:
	cbz	w23, .L144
	ldr	w24, [x25, 76]
	cmp	w24, w23
	bhi	.L145
	ldp	w0, w1, [x25, 32]
	ldr	w2, [x25, 40]
	bl	ENGINECheckAipData.isra.0
	cbz	w0, .L109
.L146:
	mov	w0, w20
	mov	w2, w24
	mov	w1, w21
	bl	ENGINEOutRawFrame
	ldr	w0, [x29, 136]
	sub	w0, w0, w24
	str	w0, [x29, 136]
	cbnz	w0, .L147
	ldr	w0, [x25, 76]
	cmp	w24, w0
	bcs	.L147
	sub	w20, w0, w24
	ldr	w0, [x29, 144]
	cmp	w20, w0
	bls	.L307
.L147:
	mov	w0, w21
	bl	AOP_ProcDelayCompensation
	ldr	w1, [x29, 136]
	ldr	w0, [x29, 144]
.L149:
	stp	w1, w0, [x25, 20]
	b	.L109
	.p2align 3
.L300:
	ldr	x0, .LC6
	mov	w1, 0
	ldr	w2, [x25, 112]
	mov	w20, 0
	ldr	x3, [x0, 40]
	ldr	x0, [x25, 104]
	blr	x3
	.p2align 2
.L172:
	ldr	w2, [x25, 28]
	mov	w0, w20
	add	x1, x29, 176
	asr	x2, x2, x20
	tbz	x2, 0, .L169
	ldr	w2, [x25, 12]
	cbnz	w2, .L173
	bl	AIP_GetPcmType
	ldr	w0, [x29, 176]
	cmp	w0, 1
	bls	.L308
.L169:
	add	w20, w20, 1
	cmp	w20, 8
	bne	.L172
	ldr	w2, [x25, 12]
	cbnz	w2, .L173
	mov	w0, 3
	mov	w20, 0
	str	w0, [x29, 176]
	b	.L177
	.p2align 3
.L175:
	add	w20, w20, 1
	cmp	w20, 8
	beq	.L176
.L177:
	ldr	w0, [x25, 28]
	asr	x0, x0, x20
	tbz	x0, 0, .L175
	mov	w0, w20
	add	x1, x29, 176
	bl	AIP_GetPcmType
	ldr	w0, [x29, 176]
	cmp	w0, 2
	bne	.L175
	ldr	x2, [x25, 104]
	mov	w1, w20
	mov	x0, x25
	bl	ENGINEMixData
.L176:
	ldr	w0, [x25, 96]
	ldr	w2, [x25, 12]
	cmp	w0, 2
	bne	.L179
	b	.L178
.L306:
	mov	w0, w20
	bl	AIP_QueryBusy
	cmp	w0, 3
	bls	.L109
	mov	w0, w20
	add	x2, x29, 144
	add	x1, x29, 136
	bl	AIP_GetCompressInfo
	ldr	w23, [x29, 136]
	ldr	w0, [x29, 144]
	cbnz	w23, .L143
	cbnz	w0, .L143
	mov	w0, w20
	bl	AIP_GetRingIn
	bl	RBUF_Flush
	ldr	w23, [x29, 136]
	ldr	w0, [x29, 144]
.L143:
	stp	w23, w0, [x25, 20]
	b	.L141
	.p2align 3
.L308:
	ldr	x2, [x25, 104]
	mov	w1, w20
	mov	x0, x25
	bl	ENGINEMixData
	b	.L169
.L131:
	ldr	w0, [x25, 28]
	uxtw	x1, w0
	tbnz	x0, 0, .L202
	mov	w2, 0
	mov	w21, 0
	b	.L134
.L301:
	ldr	x0, .LC6
	add	x1, x25, 136
	ldr	x3, [x0, 48]
	add	x0, x29, 176
	blr	x3
	b	.L189
.L202:
	mov	w20, 0
	mov	w21, 0
	b	.L196
.L144:
	ldr	w1, [x29, 144]
	mov	w0, 0
	cbz	w1, .L149
	ldr	w20, [x25, 76]
	mov	w0, w21
	cmp	w20, w1
	csel	w20, w20, w1, ls
	bl	AOP_GetRingOut
	cbz	x0, .L150
	mov	w2, w20
	mov	x1, 0
	bl	RBUF_WriteDataDma
.L150:
	ldr	w0, [x29, 144]
	ldr	w1, [x29, 136]
	sub	w0, w0, w20
	stp	w1, w0, [x25, 20]
	b	.L109
.L145:
	mov	w0, w20
	bl	AIP_QueryBusy
	cmp	w0, w23
	bcc	.L109
	mov	w24, w23
	b	.L146
.L307:
	mov	w0, w21
	bl	AOP_GetRingOut
	cbz	x0, .L148
	mov	w2, w20
	mov	x1, 0
	bl	RBUF_WriteDataDma
.L148:
	ldr	w0, [x29, 144]
	sub	w20, w0, w20
	str	w20, [x29, 144]
	b	.L147
	.size	ENGINE_Process, .-ENGINE_Process
	.align	3
.LC5:
	.xword	.LANCHOR0
	.align	3
.LC6:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_Init
	.type	ENGINE_Init, %function
ENGINE_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w23, 1
	add	x21, x19, 768
	bl	_mcount
	ldr	x20, .LC7
	ldr	x22, .LC8
	add	x20, x20, 48
	.p2align 2
.L310:
	mov	x2, 128
	ldr	x3, [x22, 40]
	str	x19, [x20, -48]
	mov	x0, x19
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	ldr	w0, [x19, -124]
	cmp	x19, x21
	orr	w0, w0, 4
	str	w0, [x19, -124]
	ldr	w0, [x19, -124]
	bfi	w0, w23, 0, 2
	str	w0, [x19, -124]
	str	xzr, [x20], 8
	bne	.L310
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ENGINE_Init, .-ENGINE_Init
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_DeInit
	.type	ENGINE_DeInit, %function
ENGINE_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC9
	add	x19, x20, 48
	add	x20, x20, 96
	.p2align 2
.L313:
	ldr	x0, [x19]
	bl	ENGINEDestroyChn
	str	xzr, [x19], 8
	cmp	x19, x20
	bne	.L313
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ENGINE_DeInit, .-ENGINE_DeInit
	.align	3
.LC9:
	.xword	.LANCHOR0
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stEneRm, %object
	.size	g_stEneRm, 96
g_stEneRm:
	.zero	96
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
