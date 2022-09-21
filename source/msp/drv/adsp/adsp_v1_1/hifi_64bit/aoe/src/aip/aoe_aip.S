#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_aip.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AIPDestroyChn, %function
AIPDestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1
	ldr	x0, [x19, 168]
	str	wzr, [x19, 208]
	cbz	x0, .L3
	bl	RBUF_Destroy
.L3:
	ldr	x0, [x19, 176]
	cbz	x0, .L4
	bl	RBUF_Destroy
.L4:
	ldr	x0, [x19, 200]
	cbz	x0, .L5
	bl	FADE_Destroy
.L5:
	ldr	x0, [x19, 184]
	cbz	x0, .L6
	bl	LSRC_Destroy
.L6:
	ldr	x0, [x19, 192]
	cbz	x0, .L7
	bl	ResamplerFree
.L7:
	ldr	x1, [x19, 272]
	cbz	x1, .L8
	mov	w0, 26
	bl	HI_ADSP_FREE
.L8:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPDestroyChn, .-AIPDestroyChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPGainPcmData, %function
AIPGainPcmData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x29, 56]
	ldr	x0, .LC0
	add	x1, x29, 40
	mov	x2, 20
	ldr	x3, [x0, 48]
	add	x0, x29, 40
	stp	xzr, xzr, [x1]
	add	x1, x20, 212
	blr	x3
	ldr	w2, [x20, 232]
	ldr	w0, [x29, 44]
	add	w0, w2, w0
	cmp	w0, 120
	bhi	.L32
	ldr	w1, [x29, 48]
	mov	w0, 0
	str	wzr, [x29, 44]
	add	w1, w2, w1
	cmp	w1, 120
	bls	.L42
.L34:
	sub	w1, w1, #121
	ldr	w3, [x20, 236]
	str	w1, [x29, 48]
	cmp	w0, 121
	ldp	w2, w1, [x29, 52]
	add	w2, w3, w2
	add	w0, w3, w1
	stp	w2, w0, [x29, 52]
	beq	.L43
.L36:
	add	x2, x29, 40
	mov	x0, x19
	mov	w1, 0
	bl	UTIL_LRGainProcess
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L32:
	ldr	w1, [x29, 48]
	sub	w0, w0, #121
	str	w0, [x29, 44]
	add	w1, w2, w1
	cmp	w1, 120
	bhi	.L34
.L42:
	ldp	w2, w1, [x29, 52]
	ldr	w3, [x20, 236]
	cmp	w0, 121
	str	wzr, [x29, 48]
	add	w2, w3, w2
	add	w0, w3, w1
	stp	w2, w0, [x29, 52]
	bne	.L36
.L43:
	ldr	w1, [x29, 48]
	cmp	w1, 121
	ccmp	w2, wzr, 0, eq
	ccmp	w0, wzr, 0, eq
	bne	.L36
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	AIPGainPcmData, .-AIPGainPcmData
	.align	3
.LC0:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetPcmType
	.type	AIP_GetPcmType, %function
AIP_GetPcmType:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC1
	ldr	x0, [x0, w19, uxtw 3]
	cbz	x0, .L47
	ldr	w0, [x0]
	ubfx	x0, x0, 11, 3
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L47:
	mov	w0, 3
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_GetPcmType, .-AIP_GetPcmType
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFadeoutChnData
	.type	AIPFadeoutChnData, %function
AIPFadeoutChnData:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	str	xzr, [x29, 88]
	add	x0, x29, 56
	add	x2, x29, 72
	add	x1, x29, 56
	stp	xzr, xzr, [x0]
	ldr	x0, [x19, 176]
	stp	xzr, xzr, [x2]
	bl	RBUF_QueryInfo
	ldr	x0, [x29, 56]
	cbz	x0, .L48
	ldp	w20, w3, [x29, 76]
	ldr	w21, [x19, 156]
	mov	w2, 8
	ldr	x0, [x19, 200]
	mov	w1, 2
	udiv	w20, w20, w21
	udiv	w21, w3, w21
	bl	FADE_Active
	ldp	w2, w3, [x19, 88]
	ldr	w1, [x19, 96]
	ldr	x0, [x19, 200]
	bl	FADE_Flush
	ldr	w1, [x29, 64]
	mov	w2, w20
	ldr	x3, [x29, 56]
	ldr	x0, [x19, 200]
	add	x1, x3, x1
	bl	FADE_OutProcess
	ldr	x0, [x19, 200]
	sub	w2, w21, w20
	ldr	x1, [x29, 56]
	bl	FADE_OutProcess
.L48:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	AIPFadeoutChnData, .-AIPFadeoutChnData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetRbfFiFoAttr
	.type	AIPGetRbfFiFoAttr, %function
AIPGetRbfFiFoAttr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC2
	add	x0, x19, 88
	ldr	x20, [x1, w20, uxtw 3]
	ldr	w1, [x20, 4]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L57
	ldr	w1, [x20, 4]
	add	x0, x19, 92
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L57
	ldr	w1, [x20, 4]
	add	x0, x19, 96
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L57
	ldr	w1, [x20, 4]
	add	x0, x19, 100
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L57
	ldr	w1, [x20, 4]
	add	x0, x29, 60
	ubfx	x1, x1, 10, 6
	bl	AOE_REG_ReadBufLatencyMs
	mov	w21, w0
	cbnz	w0, .L57
	ldp	w1, w0, [x19, 88]
	bl	UTIL_CalcFrameSize
	mov	w22, w0
	mov	w1, w0
	ldr	w2, [x19, 96]
	ldr	w0, [x29, 60]
	bl	UTIL_LatencyMs2ByteSize
	str	wzr, [x19, 112]
	ldr	w2, [x29, 60]
	add	x3, x20, 68
	str	w0, [x19, 128]
	add	x20, x20, 72
	stp	w0, w2, [x19, 160]
	str	w2, [x19, 104]
	mov	w0, w21
	stp	x3, x20, [x19, 136]
	stp	wzr, w22, [x19, 152]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L57:
	mov	w21, -1
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	AIPGetRbfFiFoAttr, .-AIPGetRbfFiFoAttr
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetRbfInAttr
	.type	AIPGetRbfInAttr, %function
AIPGetRbfInAttr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC3
	add	x0, x20, 16
	ldr	x19, [x1, w19, uxtw 3]
	ldr	w1, [x19]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L61
	ldr	w1, [x19]
	add	x0, x20, 20
	ubfx	x1, x1, 2, 3
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L61
	ldr	w1, [x19]
	add	x0, x20, 24
	ubfx	x1, x1, 5, 4
	bl	AOE_REG_ReadSampelRate
	cbz	w0, .L64
	ldr	w0, [x19]
	ubfx	x0, x0, 5, 4
	cmp	w0, 15
	beq	.L73
.L64:
	ldr	w1, [x19]
	add	x0, x20, 28
	ubfx	x1, x1, 9, 2
	bl	AOE_REG_ReadDataFormat
	mov	w21, w0
	cbnz	w0, .L61
	ldr	w0, [x20, 28]
	cbnz	w0, .L68
	ldr	w1, [x19]
	mov	x0, x20
	ubfx	x1, x1, 11, 3
	bl	AOE_REG_ReadPcmType
	cbnz	w0, .L61
.L68:
	ldr	w2, [x19]
	ldp	w1, w0, [x20, 16]
	ubfx	x2, x2, 14, 1
	str	w2, [x20, 4]
	bl	UTIL_CalcFrameSize
	mov	w1, 1
	str	w1, [x20, 32]
	add	x1, x20, 32
	mov	x2, 0
	ldr	w4, [x19, 16]
	ldr	w3, [x19, 20]
	bfi	x2, x4, 0, 32
	bfi	x2, x3, 32, 32
	str	x2, [x1, 8]
	ldr	w2, [x19, 24]
	ubfx	x2, x2, 0, 24
	str	w2, [x1, 16]
	ldr	w3, [x19, 24]
	tbnz	x3, 24, .L66
	add	x4, x19, 28
	add	x3, x19, 36
	stp	x4, x3, [x1, 24]
.L69:
	ldr	w3, [x19, 24]
	stp	w0, w2, [x1, 44]
	str	wzr, [x1, 52]
	ubfx	x0, x3, 24, 1
	str	w0, [x1, 40]
	mov	w1, 16
	mov	w0, 8
	stp	w1, w0, [x20, 8]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L66:
	ldr	w6, [x19, 28]
	mov	x4, 0
	ldr	w5, [x19, 32]
	mov	x3, 0
	bfi	x4, x6, 0, 32
	bfi	x4, x5, 32, 32
	str	x4, [x1, 24]
	ldr	w5, [x19, 36]
	ldr	w4, [x19, 40]
	bfi	x3, x5, 0, 32
	bfi	x3, x4, 32, 32
	str	x3, [x1, 32]
	b	.L69
	.p2align 3
.L73:
	ldr	w0, [x19, 12]
	mov	w1, 56928
	movk	w1, 0x2, lsl 16
	ubfx	x0, x0, 0, 24
	str	w0, [x20, 24]
	sub	w0, w0, #4000
	cmp	w0, w1
	bhi	.L61
	ldr	w0, [x20, 20]
	cmp	w0, 2
	bhi	.L61
	ldr	w0, [x20, 16]
	cmp	w0, 16
	beq	.L64
.L61:
	mov	w21, -1
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AIPGetRbfInAttr, .-AIPGetRbfInAttr
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetChnCreateAttr
	.type	AIPGetChnCreateAttr, %function
AIPGetChnCreateAttr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	x1, x20
	mov	w0, w19
	bl	AIPGetRbfInAttr
	cbnz	w0, .L75
	mov	x1, x20
	mov	w0, w19
	bl	AIPGetRbfFiFoAttr
.L75:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPGetChnCreateAttr, .-AIPGetChnCreateAttr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPIsChnAttrChange
	.type	AIPIsChnAttrChange, %function
AIPIsChnAttrChange:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC4
	mov	w0, w19
	add	x1, x29, 40
	add	x19, x2, x19, uxtw 3
	ldr	x19, [x19, 64]
	bl	AIPGetChnCreateAttr
	ldp	w0, w1, [x29, 56]
	ldp	w5, w3, [x29, 64]
	ldp	w2, w7, [x19, 16]
	ldp	w6, w4, [x19, 24]
	cmp	w2, w0
	cset	w0, ne
	cmp	w7, w1
	csinc	w0, w0, w0, eq
	cmp	w6, w5
	ldp	w2, w6, [x19]
	ldp	w1, w5, [x29, 40]
	csinc	w0, w0, w0, eq
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	ldr	x4, [x19, 40]
	ldr	x3, [x29, 80]
	cmp	w2, w1
	csinc	w0, w0, w0, eq
	ldr	w2, [x19, 48]
	ldr	w1, [x29, 88]
	cmp	w6, w5
	csinc	w0, w0, w0, eq
	ldr	w6, [x19, 72]
	ldr	w5, [x29, 112]
	cmp	x4, x3
	csinc	w0, w0, w0, eq
	cmp	w2, w1
	ldp	w4, w2, [x19, 88]
	ldp	w3, w1, [x29, 128]
	csinc	w0, w0, w0, eq
	cmp	w6, w5
	csinc	w0, w0, w0, eq
	ldr	w6, [x19, 96]
	ldr	w5, [x29, 136]
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	cmp	w2, w1
	ldp	w4, w2, [x19, 100]
	ldp	w3, w1, [x29, 140]
	csinc	w0, w0, w0, eq
	cmp	w6, w5
	csinc	w0, w0, w0, eq
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	cmp	w2, w1
	ldr	x19, [sp, 16]
	csinc	w0, w0, w0, eq
	ldp	x29, x30, [sp], 208
	ret
	.size	AIPIsChnAttrChange, .-AIPIsChnAttrChange
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPCreateChn
	.type	AIPCreateChn, %function
AIPCreateChn:
	stp	x29, x30, [sp, -288]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC5
	add	x1, x29, 120
	mov	w0, w20
	stp	xzr, xzr, [x29, 48]
	ldr	x21, [x2, w20, uxtw 3]
	stp	xzr, xzr, [x29, 64]
	bl	AIPGetChnCreateAttr
	cbnz	w0, .L96
	mov	w1, 376
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L80
	ldr	x22, .LC6
	mov	x2, 376
	mov	w1, 0
	ldr	x3, [x22, 40]
	blr	x3
	ldr	x3, [x22, 48]
	mov	x2, 168
	add	x1, x29, 120
	mov	x0, x19
	blr	x3
	str	w20, [x19, 296]
	add	x0, x29, 64
	add	x1, x29, 152
	bl	RBUF_Create_EXT
	ldr	x0, [x29, 64]
	cbz	x0, .L80
	ldr	w1, [x29, 148]
	str	x0, [x19, 168]
	cbz	w1, .L127
	str	wzr, [x21, 60]
	ldr	w0, [x21, 64]
	and	w0, w0, -65536
	str	w0, [x21, 64]
.L82:
	mov	w1, 768
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	str	x0, [x19, 272]
	cbz	x0, .L80
	ldr	w0, [x29, 148]
	cbnz	w0, .L84
	ldr	w0, [x29, 144]
	ldr	w1, [x29, 216]
	cmp	w0, w1
	beq	.L85
	mov	w2, 32000
	cmp	w0, w2
	beq	.L86
	bls	.L128
	mov	w2, 22664
	movk	w2, 0x1, lsl 16
	cmp	w0, w2
	beq	.L86
	bhi	.L90
.L86:
	mov	w2, 1
	ldr	w3, [x29, 208]
	str	w2, [x19, 300]
	mov	w4, 0
	ldr	w2, [x29, 212]
	bl	ResamplerCreate
	cbz	x0, .L80
	ldr	w1, [x29, 216]
	str	x0, [x19, 192]
.L85:
	ldp	w3, w4, [x29, 208]
	add	x0, x29, 48
	mov	w2, w1
	bl	LSRC_Create
	ldr	x0, [x29, 48]
	cbz	x0, .L80
	str	x0, [x19, 184]
	str	wzr, [x21, 80]
	ldr	w0, [x19]
	cbnz	w0, .L129
.L84:
	ldp	w1, w0, [x19, 88]
	mov	w3, 256
	mov	w2, 3
	str	w3, [x19, 348]
	str	w2, [x19, 352]
	stp	wzr, wzr, [x19, 212]
	str	wzr, [x19, 220]
	str	wzr, [x19, 244]
	bl	UTIL_CalcFrameSize
	ldr	w2, [x19, 96]
	mov	w1, 19923
	mov	w3, 48000
	movk	w1, 0x1062, lsl 16
	cmp	w2, w3
	add	w2, w2, w2, lsl 2
	umull	x1, w2, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	beq	.L130
	and	w2, w1, 3
	cbz	w2, .L95
	and	w1, w1, -4
	add	w1, w1, 4
.L95:
	mul	w2, w0, w1
	ldp	w1, w0, [x19, 88]
	str	w2, [x19, 280]
	bl	UTIL_CalcFrameSize
	ldr	w3, [x19, 96]
	mov	w4, 19923
	ldr	w2, [x19, 104]
	movk	w4, 0x1062, lsl 16
	ldr	w1, [x19, 88]
	mul	w2, w3, w2
	umull	x2, w2, w4
	lsr	x2, x2, 38
	mul	w2, w2, w0
	ldr	w0, [x19, 92]
	str	w2, [x19, 292]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 284]
	ldr	w1, [x19, 16]
	ldr	w0, [x19, 20]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 288]
	ldr	x0, [x19, 200]
	mov	w1, 1
	mov	w2, 8
	str	w1, [x19, 208]
	bl	FADE_Active
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L127:
	add	x0, x29, 72
	add	x1, x29, 232
	bl	RBUF_Create
	ldr	x0, [x29, 72]
	cbz	x0, .L80
	add	x1, x29, 80
	str	x0, [x19, 176]
	bl	RBUF_QueryInfo
	ldrh	w1, [x29, 96]
	ldr	w0, [x21, 64]
	bfi	w0, w1, 0, 16
	str	w0, [x21, 64]
	b	.L82
	.p2align 3
.L96:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	x0, 0
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L129:
	ldp	w2, w3, [x29, 136]
	ldr	w1, [x29, 144]
	add	x0, x29, 56
	bl	FADE_Create
	ldr	x0, [x29, 56]
	cbz	x0, .L80
	str	x0, [x19, 200]
	str	wzr, [x19, 260]
	b	.L84
	.p2align 3
.L130:
	ands	w2, w1, 255
	beq	.L95
	add	w1, w1, 256
	sub	w1, w1, w2
	b	.L95
	.p2align 3
.L90:
	b	.L86
	.p2align 3
.L80:
	mov	x0, x19
	bl	AIPDestroyChn
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L128:
	mov	w2, 12000
	cmp	w0, w2
	beq	.L86
	bls	.L86
	b	.L86
	.size	AIPCreateChn, .-AIPCreateChn
	.align	3
.LC5:
	.xword	.LANCHOR0
	.align	3
.LC6:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnCtx
	.type	AIPFlushChnCtx, %function
AIPFlushChnCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 192]
	cbz	x0, .L132
	bl	ResampleFlush
.L132:
	ldr	x0, [x19, 184]
	cbz	x0, .L133
	bl	LSRC_Flush
.L133:
	ldr	x0, [x19, 200]
	str	wzr, [x19, 268]
	cbz	x0, .L131
	mov	w2, 8
	mov	w1, 1
	bl	FADE_Active
.L131:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnCtx, .-AIPFlushChnCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnRufIn
	.type	AIPFlushChnRufIn, %function
AIPFlushChnRufIn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 168]
	cbz	x0, .L144
	bl	RBUF_Flush
.L144:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnRufIn, .-AIPFlushChnRufIn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnFifo
	.type	AIPFlushChnFifo, %function
AIPFlushChnFifo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 176]
	cbz	x0, .L149
	bl	RBUF_Flush
.L149:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnFifo, .-AIPFlushChnFifo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChn
	.type	AIPFlushChn, %function
AIPFlushChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	tbnz	x19, 0, .L173
.L155:
	tbz	x19, 1, .L156
	ldr	x0, [x20, 168]
	cbz	x0, .L156
	bl	RBUF_Flush
.L156:
	tbz	x19, 2, .L154
	ldr	x0, [x20, 176]
	cbz	x0, .L154
	bl	RBUF_Flush
.L154:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L173:
	mov	x0, x20
	bl	AIPFlushChnCtx
	b	.L155
	.size	AIPFlushChn, .-AIPFlushChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPWriteMuteFrame
	.type	AIPWriteMuteFrame, %function
AIPWriteMuteFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 176]
	cbz	x0, .L174
	ldr	w20, [x19, 280]
	bl	RBUF_QueryFree
	cmp	w20, w0
	bcc	.L178
.L174:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L178:
	ldr	x0, [x19, 176]
	mov	w2, w20
	mov	x1, 0
	bl	RBUF_WriteData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPWriteMuteFrame, .-AIPWriteMuteFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetChnCmd
	.type	AIPGetChnCmd, %function
AIPGetChnCmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC7
	ldr	x0, [x0, w20, uxtw 3]
	ldr	w1, [x0, 8]
	tbz	x1, 3, .L188
	mov	w0, 4
.L180:
	str	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L188:
	ldr	w0, [x0, 8]
	ldr	x1, .LC8
	and	w0, w0, 3
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx182
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx182:
	.section	.rodata
	.align	0
	.align	2
.L182:
	.byte	(.L187 - .Lrtx182) / 4
	.byte	(.L183 - .Lrtx182) / 4
	.byte	(.L184 - .Lrtx182) / 4
	.byte	(.L185 - .Lrtx182) / 4
	.text
	.p2align 3
.L187:
	mov	w0, 0
	b	.L180
	.p2align 3
.L185:
	mov	w0, 3
	b	.L180
	.p2align 3
.L184:
	mov	w0, 2
	b	.L180
	.p2align 3
.L183:
	mov	w0, 1
	b	.L180
	.size	AIPGetChnCmd, .-AIPGetChnCmd
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.L182
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPAckChnCmd
	.type	AIPAckChnCmd, %function
AIPAckChnCmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC9
	ldr	x0, [x0, w19, uxtw 3]
	ldr	w2, [x0, 8]
	tbnz	x2, 3, .L189
	ldr	w2, [x0, 8]
	bfi	w2, w20, 4, 4
	str	w2, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L189:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPAckChnCmd, .-AIPAckChnCmd
	.align	3
.LC9:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsDataEnoughForFadeout
	.type	IsDataEnoughForFadeout, %function
IsDataEnoughForFadeout:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 168]
	bl	RBUF_QueryBusy
	mov	w20, w0
	ldp	w1, w0, [x19, 16]
	bl	UTIL_CalcFrameSize
	mov	w1, w0
	ldr	w2, [x19, 24]
	mov	w0, w20
	bl	UTIL_LatencyMs
	mov	w20, w0
	ldr	x0, [x19, 176]
	bl	RBUF_QueryBusy
	mov	w21, w0
	ldp	w1, w0, [x19, 88]
	bl	UTIL_CalcFrameSize
	mov	w1, w0
	ldr	w2, [x19, 96]
	mov	w0, w21
	bl	UTIL_LatencyMs
	ldr	x21, [sp, 32]
	ldr	w1, [x19, 268]
	ldr	w2, [x19, 96]
	udiv	w2, w1, w2
	lsl	w1, w2, 6
	sub	w1, w1, w2
	lsl	w1, w1, 1
	sub	w1, w1, w2
	add	w0, w0, w1, lsl 3
	cmp	w0, 4
	ccmp	w20, 4, 2, ls
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	IsDataEnoughForFadeout, .-IsDataEnoughForFadeout
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPStopChnCmdProc
	.type	AIPStopChnCmdProc, %function
AIPStopChnCmdProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC10
	add	x0, x20, x21, uxtw 3
	ldr	x22, [x20, w21, uxtw 3]
	ldr	x19, [x0, 64]
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L192
	ldr	w1, [x19, 208]
	mov	x0, x22
	sub	w1, w1, #1
	cmp	w1, 1
	bls	.L200
.L195:
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L192
	ldr	w1, [x0, 8]
	and	w1, w1, -241
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L192:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L200:
	mov	x0, x19
	bl	IsDataEnoughForFadeout
	cbnz	w0, .L201
	mov	x0, x19
	mov	w1, 4
	bl	AIPFlushChn
	mov	w0, 1
	str	w0, [x19, 304]
.L197:
	mov	w1, 3
	mov	x0, x19
	bl	AIPFlushChn
	mov	x0, x19
	bl	AIPWriteMuteFrame
	str	wzr, [x19, 208]
	ldr	x0, [x20, w21, uxtw 3]
	str	wzr, [x22, 80]
	b	.L195
	.p2align 3
.L201:
	mov	x0, x19
	bl	AIPFadeoutChnData
	str	wzr, [x19, 304]
	b	.L197
	.size	AIPStopChnCmdProc, .-AIPStopChnCmdProc
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIFlushChnCmdProc
	.type	AIFlushChnCmdProc, %function
AIFlushChnCmdProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC11
	add	x0, x20, x21, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L202
	ldr	w22, [x19, 208]
	cmp	w22, 1
	beq	.L208
	cmp	w22, 2
	beq	.L209
.L206:
	ldr	x0, [x20, w21, uxtw 3]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L202
	ldr	w1, [x0, 8]
	and	w1, w1, -241
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L202:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L208:
	mov	x0, x19
	bl	AIPFadeoutChnData
	mov	w1, 3
	mov	x0, x19
	bl	AIPFlushChn
	mov	x0, x19
	bl	AIPWriteMuteFrame
	ldr	x0, [x19, 200]
	mov	w2, 8
	mov	w1, w22
	bl	FADE_Active
	b	.L206
	.p2align 3
.L209:
	mov	w1, 7
	mov	x0, x19
	bl	AIPFlushChn
	b	.L206
	.size	AIFlushChnCmdProc, .-AIFlushChnCmdProc
	.align	3
.LC11:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPPauseChnCmdProc
	.type	AIPPauseChnCmdProc, %function
AIPPauseChnCmdProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC12
	add	x0, x20, x21, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L210
	ldr	w22, [x19, 208]
	cmp	w22, 1
	beq	.L215
.L213:
	ldr	x0, [x20, w21, uxtw 3]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L210
	ldr	w1, [x0, 8]
	and	w1, w1, -241
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L210:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L215:
	mov	x0, x19
	bl	AIPFadeoutChnData
	mov	x0, x19
	mov	w1, w22
	bl	AIPFlushChn
	mov	w0, 2
	str	w0, [x19, 208]
	b	.L213
	.size	AIPPauseChnCmdProc, .-AIPPauseChnCmdProc
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPStartChnCmdProc
	.type	AIPStartChnCmdProc, %function
AIPStartChnCmdProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x19, w0
	mov	x0, x30
	mov	x21, x19
	add	x19, x19, 8
	bl	_mcount
	ldr	x20, .LC13
	ldr	x22, [x20, x19, lsl 3]
	cbz	x22, .L225
	ldr	w0, [x22, 208]
	cbz	w0, .L227
	cmp	w0, 2
	beq	.L226
.L221:
	ldr	x0, [x20, w21, uxtw 3]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L216
	ldr	w1, [x0, 8]
	and	w1, w1, -241
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L216:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L227:
	mov	w0, w21
	bl	AIPIsChnAttrChange
	cbz	w0, .L226
	ldr	x0, [x20, x19, lsl 3]
	bl	AIPDestroyChn
.L225:
	mov	w0, w21
	bl	AIPCreateChn
	str	x0, [x20, x19, lsl 3]
	cbnz	x0, .L221
.L228:
	ldr	x0, [x20, w21, uxtw 3]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L216
	ldr	w1, [x0, 8]
	mov	w2, 1
	bfi	w1, w2, 4, 4
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
	b	.L216
	.p2align 3
.L226:
	ldr	x0, [x22, 200]
	mov	w1, 1
	mov	w2, 8
	str	w1, [x22, 208]
	bl	FADE_Active
	ldr	x0, [x20, x19, lsl 3]
	cbnz	x0, .L221
	b	.L228
	.size	AIPStartChnCmdProc, .-AIPStartChnCmdProc
	.align	3
.LC13:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_Init
	.type	AIP_Init, %function
AIP_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w22, 121
	add	x21, x19, 768
	bl	_mcount
	ldr	x20, .LC16
	ldr	x24, .LC17
	mov	w23, 3
	add	x20, x20, 64
	.p2align 2
.L230:
	ldr	x3, [x24, 40]
	mov	x0, x19
	str	x19, [x20, -64]
	mov	x2, 96
	mov	w1, 0
	blr	x3
	ldr	w0, [x19, 8]
	orr	w0, w0, 8
	str	w0, [x19, 8]
	ldr	w0, [x19, 8]
	bfi	w0, w22, 8, 7
	str	w0, [x19, 8]
	ldr	w0, [x19]
	bfi	w0, w23, 11, 3
	str	w0, [x19], 96
	str	xzr, [x20], 8
	cmp	x19, x21
	bne	.L230
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	AIP_Init, .-AIP_Init
	.align	3
.LC16:
	.xword	.LANCHOR0
	.align	3
.LC17:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_DeInit
	.type	AIP_DeInit, %function
AIP_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC18
	add	x19, x20, 64
	add	x20, x20, 128
	.p2align 2
.L233:
	ldr	x0, [x19]
	bl	AIPDestroyChn
	str	xzr, [x19], 8
	cmp	x19, x20
	bne	.L233
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_DeInit, .-AIP_DeInit
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_Process
	.type	AIP_Process, %function
AIP_Process:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	mov	w21, 0
	bl	_mcount
	ldr	x23, .LC22
	ldr	x24, .LC20
	ldr	x22, .LC21
	mov	x25, x23
	mov	x26, x23
	mov	x20, x24
	.p2align 2
.L290:
	ldr	x0, [x20]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L243
	ldr	w0, [x0, 8]
	and	w0, w0, 3
	ldrb	w0, [x22,w0,uxtw]
	adr	x1, .Lrtx239
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx239:
	.section	.rodata
	.align	0
	.align	2
.L239:
	.byte	(.L238 - .Lrtx239) / 4
	.byte	(.L240 - .Lrtx239) / 4
	.byte	(.L241 - .Lrtx239) / 4
	.byte	(.L242 - .Lrtx239) / 4
	.text
	.p2align 3
.L241:
	mov	w0, w21
	bl	AIPPauseChnCmdProc
	.p2align 2
.L243:
	ldr	x19, [x20, 64]
	cbz	x19, .L244
	ldr	w0, [x19, 208]
	cmp	w0, 1
	beq	.L347
.L244:
	add	w21, w21, 1
	add	x20, x20, 8
	cmp	w21, 8
	bne	.L290
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L240:
	mov	w0, w21
	bl	AIPStopChnCmdProc
	b	.L243
	.p2align 3
.L242:
	mov	w0, w21
	bl	AIFlushChnCmdProc
	b	.L243
	.p2align 3
.L238:
	mov	w0, w21
	bl	AIPStartChnCmdProc
	b	.L243
	.p2align 3
.L347:
	ldr	w0, [x19, 28]
	cbnz	w0, .L244
	ldr	x1, [x20]
	str	wzr, [x19, 212]
	ldr	w0, [x1, 48]
	uxtb	w0, w0
	str	w0, [x19, 216]
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 8, 8
	str	w0, [x19, 220]
	ldr	w0, [x1, 76]
	uxtb	w0, w0
	str	w0, [x19, 232]
	ldr	w0, [x1, 76]
	tbnz	x0, 11, .L245
	ldr	w0, [x1, 76]
	ubfx	x0, x0, 8, 3
	str	w0, [x19, 236]
.L246:
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 16, 1
	str	w0, [x19, 240]
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 17, 3
	str	w0, [x19, 244]
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 23, 2
	str	w0, [x19, 248]
	cmp	w0, 1
	beq	.L348
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 25, 7
	neg	w0, w0
	str	w0, [x19, 348]
.L248:
	ldr	w0, [x1, 48]
	ubfx	x0, x0, 20, 3
	str	w0, [x19, 352]
	ldr	w0, [x1, 8]
	ubfx	x0, x0, 29, 2
	cbz	w0, .L349
	ldr	w0, [x1, 8]
	ubfx	x0, x0, 29, 2
	cmp	w0, 1
	beq	.L350
.L250:
	ldr	w0, [x1]
	ubfx	x0, x0, 14, 1
	str	w0, [x19, 4]
	ldr	w2, [x1, 4]
	ubfx	x2, x2, 22, 1
	str	w2, [x19, 308]
	ldr	w3, [x1, 76]
	ubfx	x3, x3, 24, 1
	str	w3, [x19, 312]
	ldr	w0, [x1, 76]
	ubfx	x0, x0, 12, 4
	str	w0, [x19, 316]
	ldr	w1, [x1, 76]
	ubfx	x1, x1, 16, 8
	str	w1, [x19, 320]
	cbnz	w2, .L289
	cbnz	w3, .L252
	ldr	w0, [x19, 324]
	cmp	w0, 1
	beq	.L351
.L262:
	ldr	w1, [x19, 268]
	ldr	w0, [x19, 284]
	ldr	w27, [x19, 280]
	mul	w2, w1, w0
	cmp	w2, w27
	bcc	.L263
	ldr	x0, [x19, 176]
	cbz	x0, .L289
	mov	w1, w27
	bl	RBUF_CheckFree
	cbz	w0, .L289
	cbz	w27, .L289
	ldr	x1, [x19, 272]
	ldr	w2, [x19, 280]
	ldr	x0, [x19, 176]
	bl	RBUF_WriteData
	ldr	w0, [x19, 280]
	ldr	w1, [x19, 284]
	udiv	w1, w0, w1
	ldr	w0, [x19, 268]
	sub	w0, w0, w1
	str	w0, [x19, 268]
	.p2align 2
.L289:
	ldr	x19, [x20, 64]
	ldr	x27, [x20]
	ldr	x0, [x19, 176]
	bl	RBUF_QueryBusy
	ldr	w1, [x19, 284]
	ldr	w2, [x19, 96]
	bl	UTIL_LatencyMs
	ldr	w1, [x27, 4]
	bfi	w1, w0, 16, 6
	str	w1, [x27, 4]
	b	.L244
	.p2align 3
.L349:
	ldr	w0, [x1, 8]
	ubfx	x0, x0, 24, 5
	str	w0, [x19, 264]
	b	.L250
	.p2align 3
.L245:
	ldr	w0, [x1, 76]
	tbz	x0, 11, .L246
	ldr	w0, [x1, 76]
	ubfx	x0, x0, 8, 3
	neg	w0, w0
	str	w0, [x19, 236]
	b	.L246
	.p2align 3
.L252:
	ldr	w1, [x19, 324]
	cbz	w1, .L255
	ldr	w1, [x19, 328]
.L256:
	ldr	w27, [x19, 280]
	str	w1, [x29, 116]
	mov	w1, w27
	bl	AOP_QueryRbfFree
	cbz	w0, .L262
	ldr	x0, [x19, 168]
	add	x1, x29, 116
	bl	RBUF_QueryBusy_ProvideRptr
	cmp	w27, w0
	bhi	.L262
	bl	AOE_GetWKBuf
	mov	x1, x0
	str	x0, [x29, 120]
	add	x3, x29, 116
	ldr	w0, [x19, 20]
	mov	w2, w27
	str	w0, [x29, 140]
	ldr	w0, [x19, 288]
	ldr	w4, [x19, 16]
	str	w27, [x29, 128]
	udiv	w0, w27, w0
	stp	w0, w4, [x29, 132]
	ldr	w4, [x19, 24]
	str	w4, [x29, 144]
	ldr	w4, [x19, 28]
	ldr	x0, [x19, 168]
	str	w4, [x29, 148]
	bl	RBUF_ReadDataDma
	ldr	w0, [x19, 248]
	cmp	w0, 1
	beq	.L352
.L259:
	add	x1, x29, 120
	mov	x0, x19
	bl	AIPGainPcmData
	ldr	w1, [x19, 244]
	sub	w0, w1, #1
	cmp	w0, 6
	bls	.L353
.L260:
	ldr	w0, [x19, 240]
	cmp	w0, 1
	beq	.L354
.L261:
	ldr	w0, [x19, 316]
	add	x1, x29, 120
	bl	AOP_WriteRbfData
	ldr	w0, [x29, 116]
	str	w0, [x19, 328]
	b	.L262
	.p2align 3
.L263:
	ldr	w2, [x19, 28]
	mov	w28, w27
	cbz	w2, .L355
.L266:
	ldr	x0, [x19, 168]
	bl	RBUF_QueryBusy
	cmp	w0, w28
	bcc	.L289
	cbz	w28, .L289
	ldr	x0, [x19, 176]
	cbz	x0, .L289
	mov	w1, w27
	bl	RBUF_CheckFree
	cbz	w0, .L289
	cbz	w27, .L289
	bl	AOE_GetWKBuf
	mov	x1, x0
	str	x0, [x29, 120]
	mov	w2, w28
	ldr	w0, [x19, 20]
	mov	x3, 0
	str	w0, [x29, 140]
	ldr	w0, [x19, 288]
	ldr	w4, [x19, 16]
	str	w28, [x29, 128]
	udiv	w0, w28, w0
	stp	w0, w4, [x29, 132]
	ldr	w4, [x19, 24]
	str	w4, [x29, 144]
	ldr	w4, [x19, 28]
	ldr	x0, [x19, 168]
	str	w4, [x29, 148]
	bl	RBUF_ReadDataDma
	ldr	w0, [x19, 28]
	cbz	w0, .L356
.L273:
	ldr	w0, [x19, 240]
	cmp	w0, 1
	beq	.L357
.L284:
	ldr	w0, [x19, 268]
	ldr	w2, [x19, 284]
	ldr	w28, [x19, 280]
	mul	w2, w0, w2
	cbnz	w2, .L358
.L285:
	ldr	w0, [x29, 128]
	cbz	w28, .L287
	cmp	w28, w0
	csel	w28, w28, w0, ls
	cbz	w28, .L287
	ldr	x0, [x19, 176]
	mov	w2, w28
	ldr	x1, [x29, 120]
	bl	RBUF_WriteData
	ldr	w0, [x29, 128]
.L287:
	subs	w27, w0, w28
	beq	.L288
	ldr	x1, [x29, 120]
	uxtw	x2, w27
	ldr	x0, [x19, 272]
	ldr	x3, [x23, 48]
	add	x1, x1, x28, uxtw
	blr	x3
.L288:
	ldr	w0, [x19, 284]
	udiv	w0, w27, w0
	str	w0, [x19, 268]
	b	.L289
	.p2align 3
.L348:
	mov	w0, 256
	str	w0, [x19, 348]
	b	.L248
.L355:
	udiv	w0, w27, w0
	ldr	w2, [x19, 96]
	ldp	w3, w4, [x19, 88]
	sub	w28, w0, w1
	mov	w1, w2
	ldr	x0, [x19, 184]
	bl	LSRC_UpdateChange
	ldr	w1, [x19, 264]
	ldr	x0, [x19, 184]
	bl	LSRC_SetSpeedAdjust
	ldr	x0, [x19, 184]
	mov	w1, w28
	bl	LSRC_GetMinInputNum
	mov	w1, w0
	ldr	x0, [x19, 192]
	cbz	x0, .L359
	bl	ResamplerGetMinInputNum
.L268:
	and	w1, w0, 3
	cbz	w1, .L269
	and	w0, w0, -4
	add	w0, w0, 4
.L269:
	ldr	w28, [x19, 288]
	mul	w28, w0, w28
	b	.L266
.L255:
	ldp	w1, w0, [x19, 88]
	mov	w27, 19923
	movk	w27, 0x1062, lsl 16
	bl	UTIL_CalcFrameSize
	ldr	w2, [x19, 24]
	ldr	w1, [x19, 320]
	mul	w1, w1, w2
	mul	w0, w1, w0
	add	x1, x29, 152
	umull	x27, w0, w27
	ldr	x0, [x19, 168]
	lsr	x27, x27, 32
	lsr	w27, w27, 6
	bl	RBUF_QueryInfo
	ldr	w0, [x29, 184]
	ldr	w2, [x29, 168]
	cmp	w27, w0
	csel	w27, w27, w0, ls
	ldr	w0, [x29, 160]
	add	w1, w0, w27
	cmp	w2, w1
	bls	.L360
.L346:
	mov	w2, 1
	ldr	w0, [x19, 316]
	str	w2, [x19, 324]
	str	w1, [x19, 328]
	b	.L256
.L351:
	str	wzr, [x19, 324]
	b	.L262
	.p2align 3
.L350:
	ldr	w0, [x1, 8]
	ubfx	x0, x0, 24, 5
	neg	w0, w0
	str	w0, [x19, 264]
	b	.L250
.L360:
	sub	w0, w0, w2
	add	w1, w0, w27
	b	.L346
.L356:
	ldp	w27, w28, [x19, 88]
	ldr	w0, [x29, 140]
	cmp	w28, w0
	beq	.L274
	bls	.L275
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w28
	bl	UTIL_UpmixPcmData
.L274:
	ldr	w0, [x29, 136]
	cmp	w27, w0
	beq	.L276
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w27
	bl	UTIL_UnifyBitDepthPcmData
.L276:
	ldr	x0, [x19, 192]
	cbz	x0, .L277
	ldr	w27, [x19, 96]
	bl	AOE_GetWKBuf
	ldr	w3, [x29, 132]
	mov	x2, x0
	mov	x28, x0
	ldr	w4, [x29, 144]
	ldr	x1, [x29, 120]
	mov	w6, 1
	ldr	x0, [x19, 192]
	mov	w5, w27
	bl	ResamplerProcessFrame
	str	w0, [x29, 132]
	ldr	w1, [x29, 136]
	ldr	w0, [x29, 140]
	str	x28, [x29, 120]
	str	w27, [x29, 144]
	bl	UTIL_CalcFrameSize
	ldr	w1, [x29, 132]
	mul	w0, w1, w0
	str	w0, [x29, 128]
.L277:
	ldr	x0, [x19, 184]
	cbz	x0, .L279
	ldr	w1, [x19, 296]
	ldr	x27, [x24, x1, lsl 3]
	bl	LSRC_CheckDoSRC
	cbz	w0, .L279
	ldr	w3, [x29, 132]
	str	w3, [x29, 108]
	bl	AOE_GetWKBuf
	mov	x2, x0
	mov	x28, x0
	ldr	w3, [x29, 108]
	ldr	x1, [x29, 120]
	ldr	x0, [x19, 184]
	bl	LSRC_ProcessFrame
	str	w0, [x29, 132]
	ldr	w1, [x29, 136]
	ldr	w0, [x29, 140]
	str	x28, [x29, 120]
	bl	UTIL_CalcFrameSize
	ldr	w1, [x29, 132]
	mul	w0, w1, w0
	str	w0, [x29, 128]
	ldr	w0, [x27, 80]
	add	w0, w0, 1
	str	w0, [x27, 80]
.L279:
	ldr	w0, [x19, 248]
	cmp	w0, 1
	beq	.L361
.L281:
	add	x1, x29, 120
	mov	x0, x19
	bl	AIPGainPcmData
	ldr	w1, [x19, 244]
	sub	w0, w1, #1
	cmp	w0, 6
	bls	.L362
.L282:
	ldr	x0, [x19, 200]
	cbz	x0, .L273
	ldp	w2, w3, [x29, 136]
	ldr	w1, [x29, 144]
	bl	FADE_Flush
	ldr	w2, [x29, 132]
	ldr	x0, [x19, 200]
	ldr	x1, [x29, 120]
	bl	FADE_InProcess
	b	.L273
.L358:
	ldr	x0, [x19, 176]
	sub	w28, w28, w2
	ldr	x1, [x19, 272]
	bl	RBUF_WriteData
	b	.L285
.L359:
	mov	w0, w1
	b	.L268
.L357:
	ldr	w2, [x29, 128]
	mov	w1, 0
	ldr	x3, [x25, 40]
	ldr	x0, [x29, 120]
	blr	x3
	b	.L284
.L275:
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w28
	bl	UTIL_DownmixPcmData
	b	.L274
.L354:
	ldr	w2, [x29, 128]
	mov	w1, 0
	ldr	x3, [x26, 40]
	ldr	x0, [x29, 120]
	blr	x3
	b	.L261
.L362:
	ldr	w2, [x19, 88]
	add	x0, x29, 120
	bl	UTIL_ChannelModeProcess
	b	.L282
.L361:
	add	x1, x19, 332
	add	x0, x29, 120
	bl	UTIL_DRE_16BIT_Process
	b	.L281
.L353:
	ldr	w2, [x19, 88]
	add	x0, x29, 120
	bl	UTIL_ChannelModeProcess
	b	.L260
.L352:
	add	x1, x19, 332
	add	x0, x29, 120
	bl	UTIL_DRE_16BIT_Process
	b	.L259
	.size	AIP_Process, .-AIP_Process
	.align	3
.LC20:
	.xword	.LANCHOR0
	.align	3
.LC21:
	.xword	.L239
	.align	3
.LC22:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetChnStatus
	.type	AIP_GetChnStatus, %function
AIP_GetChnStatus:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC23
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L366
	ldr	w1, [x0, 208]
	str	w1, [x20]
	ldr	w1, [x0, 4]
	str	w1, [x20, 4]
	ldr	w0, [x0, 304]
	str	w0, [x20, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L366:
	str	wzr, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_GetChnStatus, .-AIP_GetChnStatus
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_FlushCutoffFlag
	.type	AIP_FlushCutoffFlag, %function
AIP_FlushCutoffFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC24
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L367
	str	wzr, [x0, 304]
.L367:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_FlushCutoffFlag, .-AIP_FlushCutoffFlag
	.align	3
.LC24:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryFiFoInfo
	.type	AIP_QueryFiFoInfo, %function
AIP_QueryFiFoInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC25
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L376
	ldr	w1, [x0, 308]
	cbz	w1, .L377
	ldr	w1, [x0, 208]
	cmp	w1, 1
	beq	.L378
.L376:
	ldr	x3, .LC26
	mov	x2, 40
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 40]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L377:
	ldr	x0, [x0, 176]
	mov	x1, x20
	bl	RBUF_QueryInfo
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L378:
	ldr	x0, [x0, 168]
	mov	x1, x20
	bl	RBUF_QueryInfo
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryFiFoInfo, .-AIP_QueryFiFoInfo
	.align	3
.LC25:
	.xword	.LANCHOR0
	.align	3
.LC26:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryFiFoBusy
	.type	AIP_QueryFiFoBusy, %function
AIP_QueryFiFoBusy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC27
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L382
	ldr	w1, [x0, 308]
	cbz	w1, .L383
	ldr	x0, [x0, 168]
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L383:
	ldr	x0, [x0, 176]
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L382:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryFiFoBusy, .-AIP_QueryFiFoBusy
	.align	3
.LC27:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryBusy
	.type	AIP_QueryBusy, %function
AIP_QueryBusy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC28
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L387
	ldr	x0, [x0, 168]
	cbz	x0, .L387
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L387:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryBusy, .-AIP_QueryBusy
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_ReadDataComplete
	.type	AIP_ReadDataComplete, %function
AIP_ReadDataComplete:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x2, .LC29
	add	x0, x2, x20, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L388
	ldr	w0, [x19, 308]
	cbz	w0, .L394
	ldr	x0, [x19, 168]
	mov	w1, w21
	bl	RBUF_ReadDataComplete
.L388:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L394:
	ldr	x0, [x19, 176]
	mov	w1, w21
	ldr	x20, [x2, w20, uxtw 3]
	bl	RBUF_ReadDataComplete
	ldr	x0, [x19, 176]
	bl	RBUF_QueryBusy
	ldr	w2, [x19, 96]
	ldr	w1, [x19, 284]
	bl	UTIL_LatencyMs
	ldr	w1, [x20, 4]
	bfi	w1, w0, 16, 6
	str	w1, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AIP_ReadDataComplete, .-AIP_ReadDataComplete
	.align	3
.LC29:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_UnderFlowCalc
	.type	AIP_UnderFlowCalc, %function
AIP_UnderFlowCalc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC30
	add	x2, x0, x19, uxtw 3
	ldr	x1, [x0, w19, uxtw 3]
	ldr	x0, [x2, 64]
	cbz	x0, .L395
	ldr	w0, [x1, 64]
	ldr	w2, [x1, 64]
	lsr	w0, w0, 16
	add	w0, w0, 1
	uxth	w0, w0
	bfi	w2, w0, 16, 16
	str	w2, [x1, 64]
.L395:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_UnderFlowCalc, .-AIP_UnderFlowCalc
	.align	3
.LC30:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetRingIn
	.type	AIP_GetRingIn, %function
AIP_GetRingIn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC31
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L402
	ldr	x0, [x0, 168]
.L401:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L402:
	mov	x0, 0
	b	.L401
	.size	AIP_GetRingIn, .-AIP_GetRingIn
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetCompressInfo
	.type	AIP_GetCompressInfo, %function
AIP_GetCompressInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC32
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L406
	ldr	x0, [x0, 168]
	mov	x2, x21
	mov	x1, x20
	bl	RBUF_GetCompressInfo
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L406:
	str	wzr, [x20]
	str	wzr, [x21]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AIP_GetCompressInfo, .-AIP_GetCompressInfo
	.align	3
.LC32:
	.xword	.LANCHOR0
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stAipRm, %object
	.size	g_stAipRm, 128
g_stAipRm:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
