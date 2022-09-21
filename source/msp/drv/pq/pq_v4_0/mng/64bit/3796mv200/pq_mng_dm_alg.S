#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_dm_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	DM_Blend
	.type	DM_Blend, %function
DM_Blend:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w3
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	mov	w0, 0
	cbz	w19, .L2
	sub	w0, w19, w21
	add	w4, w19, w19, lsr 31
	mul	w20, w20, w21
	madd	w0, w0, w22, w20
	add	w0, w0, w4, asr 1
	sdiv	w0, w0, w19
.L2:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	DM_Blend, .-DM_Blend
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DM_GetDetRatio
	.type	DM_GetDetRatio, %function
DM_GetDetRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 164]
	mov	w0, 15
	ldr	x19, [sp, 16]
	cmp	w1, wzr
	csel	w0, w0, wzr, gt
	ldp	x29, x30, [sp], 32
	ret
	.size	DM_GetDetRatio, .-DM_GetDetRatio
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DM_GetDMParaFlag
	.type	DM_GetDMParaFlag, %function
DM_GetDMParaFlag:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	uxth	w19, w0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldrh	w0, [x20]
	cmp	w0, w19
	bhi	.L13
	ldrh	w0, [x20, 2]
	cmp	w0, w19
	bhi	.L14
	ldrh	w0, [x20, 4]
	cmp	w0, w19
	bhi	.L15
	ldrh	w0, [x20, 6]
	cmp	w0, w19
	bhi	.L16
	ldrb	w0, [x21, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L13:
	mov	x0, 0
	ldrb	w0, [x21, x0]
.L17:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L14:
	mov	x0, 1
	ldrb	w0, [x21, x0]
	b	.L17
	.p2align 3
.L15:
	mov	x0, 2
	ldrb	w0, [x21, x0]
	b	.L17
	.p2align 3
.L16:
	mov	x0, 3
	ldrb	w0, [x21, x0]
	b	.L17
	.size	DM_GetDMParaFlag, .-DM_GetDMParaFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_UpdateDMCfg
	.type	PQ_MNG_ALG_UpdateDMCfg, %function
PQ_MNG_ALG_UpdateDMCfg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	strb	wzr, [x29, 36]
	ldr	w0, [x20, 164]
	add	x2, x20, 184
	str	wzr, [x29, 32]
	cmp	w0, 720
	str	xzr, [x29, 40]
	bgt	.L19
	ldrb	w1, [x20, 169]
	cmp	w1, 1
	beq	.L46
.L19:
	ldrb	w1, [x20, 168]
.L32:
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x1, x1, 4
	add	x0, x2, x1
	ldrh	w1, [x2, x1]
	strh	w1, [x19, 106]
	ldrh	w1, [x0, 2]
	strh	w1, [x19, 108]
	ldrh	w1, [x0, 4]
	strh	w1, [x19, 116]
	ldrh	w1, [x0, 6]
	strh	w1, [x19, 118]
	ldrb	w1, [x0, 8]
	strb	w1, [x19, 306]
	ldrb	w1, [x0, 9]
	strb	w1, [x19, 307]
	ldrsh	w5, [x0, 10]
	strh	w5, [x19, 126]
	ldrsh	w3, [x0, 12]
	strh	w3, [x19, 128]
	ldrsh	w4, [x0, 14]
	strh	w4, [x19, 130]
	ldrsh	w2, [x0, 16]
	strh	w2, [x19, 132]
	ldrb	w1, [x0, 20]
	strb	w1, [x19, 305]
	cmp	w1, 1
	beq	.L47
.L33:
	ldrb	w2, [x0, 19]
	add	x1, x19, 138
	strb	w2, [x19, 304]
	ldrb	w2, [x0, 18]
	strb	w2, [x19, 124]
	ldr	x2, [x0, 40]
	ldp	x4, x5, [x2]
	stp	x4, x5, [x1]
	ldp	x4, x5, [x2, 16]
	stp	x4, x5, [x1, 16]
	ldp	x4, x5, [x2, 32]
	stp	x4, x5, [x1, 32]
	ldr	x3, [x2, 48]
	str	x3, [x19, 186]
	ldr	x2, [x2, 54]
	str	x2, [x19, 192]
	ldrh	w1, [x0, 22]
	strh	w1, [x19, 310]
	ldrh	w1, [x0, 24]
	strh	w1, [x19, 312]
	ldrb	w1, [x0, 26]
	strb	w1, [x19, 308]
	ldrb	w1, [x0, 27]
	strb	w1, [x19, 309]
	ldrb	w1, [x0, 28]
	strb	w1, [x19, 110]
	ldrh	w1, [x0, 30]
	strh	w1, [x19, 112]
	ldrh	w1, [x0, 32]
	strh	w1, [x19, 114]
	ldrh	w1, [x0, 34]
	strh	w1, [x19, 120]
	ldrh	w0, [x0, 36]
	strh	w0, [x19, 122]
	ldr	x0, .LC1
	ldr	w0, [x0]
	strb	w0, [x19, 104]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L46:
	mov	w3, 15
	cmp	w0, wzr
	csel	w3, wzr, w3, le
	cbz	x20, .L21
	ldr	x5, .LC0
	ldr	w4, [x5]
	cmp	w4, 31
	bhi	.L36
	uxtw	x0, w4
	add	w1, w4, 1
	lsl	x7, x0, 2
.L22:
	add	x4, x20, x0, lsl 2
	str	w1, [x5]
	add	x6, x20, 12
	add	x0, x6, x7
	str	w3, [x4, 12]
	str	x0, [x20, 152]
	ldr	w5, [x20, 140]
	cmp	w5, wzr
	beq	.L23
	mov	w3, 0
	mov	w1, 0
	add	x7, x20, 136
	ble	.L25
	.p2align 2
.L42:
	ldr	w4, [x0], -4
	add	w3, w3, 1
	cmp	x0, x6
	add	w1, w1, w4
	csel	x0, x0, x7, cs
	cmp	w5, w3
	bne	.L42
.L25:
	sdiv	w1, w1, w5
	uxth	w1, w1
.L26:
	ldr	x0, [x20, 170]
	ldr	w3, [x20, 178]
	str	w3, [x29, 32]
	ldr	w3, [x20, 179]
	cmp	w1, w0, uxth
	str	x0, [x29, 40]
	str	w3, [x29, 33]
	bcc	.L37
.L34:
	ldrh	w0, [x29, 42]
	cmp	w0, w1
	bhi	.L38
	ldrh	w0, [x29, 44]
	cmp	w0, w1
	bhi	.L39
	ldrh	w0, [x29, 46]
	cmp	w0, w1
	bhi	.L48
	ldrb	w1, [x29, 36]
	b	.L32
	.p2align 3
.L47:
	cmp	w5, w4
	ccmp	w3, w2, 4, gt
	bgt	.L33
	strb	wzr, [x19, 305]
	b	.L33
	.p2align 3
.L23:
	ldrh	w1, [x6, x7]
	b	.L26
	.p2align 3
.L36:
	mov	x7, 0
	mov	x0, 0
	b	.L22
	.p2align 3
.L21:
	mov	x0, 178
	ldr	x1, [x20, 170]
	str	x1, [x29, 40]
	mov	w1, 65535
	ldr	w3, [x0]
	str	w3, [x29, 32]
	ldr	w0, [x0, 1]
	str	w0, [x29, 33]
	b	.L34
.L37:
	add	x0, x29, 32
	ldrb	w1, [x0]
	b	.L32
.L38:
	mov	x0, 1
.L30:
	add	x1, x29, 32
	add	x0, x1, x0
	ldrb	w1, [x0]
	b	.L32
.L39:
	mov	x0, 2
	b	.L30
.L48:
	mov	x0, 3
	b	.L30
	.size	PQ_MNG_ALG_UpdateDMCfg, .-PQ_MNG_ALG_UpdateDMCfg
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC1:
	.xword	.LANCHOR1
	.global	g_u32DmStr
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_u32DmStr, %object
	.size	g_u32DmStr, 4
g_u32DmStr:
	.word	8
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	i.2016, %object
	.size	i.2016, 4
i.2016:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
