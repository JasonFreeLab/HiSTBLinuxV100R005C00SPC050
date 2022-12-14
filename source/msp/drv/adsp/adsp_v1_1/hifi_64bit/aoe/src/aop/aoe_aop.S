#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_aop.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	AOP_Flush
	.type	AOP_Flush, %function
AOP_Flush:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	AOP_Flush, .-AOP_Flush
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOPFlushChnBuf
	.type	AOPFlushChnBuf, %function
AOPFlushChnBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 136]
	cbz	x0, .L2
	bl	RBUF_Flush
.L2:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOPFlushChnBuf, .-AOPFlushChnBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_ProcDelayCompensation
	.type	AOP_ProcDelayCompensation, %function
AOP_ProcDelayCompensation:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC0
	add	x0, x2, x21, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L8
	ldr	w0, [x19, 144]
	cbz	w0, .L8
	ldr	w0, [x19, 156]
	cmp	w0, 1
	beq	.L43
	ldr	w20, [x19, 148]
	cmp	w20, 9
	bhi	.L44
.L8:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L44:
	ldr	x0, [x19, 136]
	add	x1, x29, 56
	ldr	x21, [x2, w21, uxtw 3]
	bl	RBUF_QueryInfo
	ldp	w1, w0, [x19, 48]
	bl	UTIL_CalcFrameSize
	mov	w3, w0
	ldr	w0, [x19, 56]
	mov	w2, 19923
	movk	w2, 0x1062, lsl 16
	mul	w20, w20, w0
	umull	x2, w20, w2
	lsr	x2, x2, 32
	lsr	w2, w2, 6
	and	w0, w2, 3
	cbz	w0, .L16
	and	w2, w2, -4
	add	w2, w2, 4
.L16:
	ldp	w1, w0, [x19, 48]
	mul	w20, w3, w2
	bl	UTIL_CalcFrameSize
	ldr	w3, [x19, 56]
	mov	w1, 19923
	movk	w1, 0x1062, lsl 16
	lsl	w2, w3, 3
	add	w3, w2, w3, lsl 1
	umull	x1, w3, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	and	w2, w1, 3
	cbz	w2, .L17
	and	w1, w1, -4
	add	w1, w1, 4
.L17:
	ldr	w2, [x29, 80]
	cmp	w20, w2
	bcc	.L8
	sub	w2, w20, w2
	madd	w2, w0, w1, w2
	cbz	w2, .L8
	ldr	w3, [x29, 88]
	mov	x1, 0
	ldr	x0, [x19, 136]
	cmp	w2, w3
	csel	w2, w2, w3, ls
	bl	RBUF_WriteData
	ldr	w0, [x21, 100]
	add	w0, w0, 1
	str	w0, [x21, 100]
	b	.L8
	.p2align 3
.L43:
	add	x0, x29, 56
	ldr	x21, [x2, w21, uxtw 3]
	str	xzr, [x29, 88]
	add	x1, x29, 56
	stp	xzr, xzr, [x0]
	add	x0, x29, 72
	stp	xzr, xzr, [x0]
	ldr	w0, [x21, 4]
	orr	w0, w0, 1048576
	str	w0, [x21, 4]
	ldr	x0, [x19, 136]
	bl	RBUF_QueryInfo
	ldr	x0, [x19, 136]
	cbz	x0, .L11
	bl	RBUF_Flush
.L11:
	ldp	w1, w0, [x19, 48]
	ldr	w20, [x19, 152]
	bl	UTIL_CalcFrameSize
	mov	w22, w0
	ldr	w0, [x19, 56]
	mov	w2, 19923
	movk	w2, 0x1062, lsl 16
	mul	w20, w20, w0
	umull	x2, w20, w2
	lsr	x2, x2, 32
	lsr	w2, w2, 6
	and	w0, w2, 3
	cbz	w0, .L12
	and	w2, w2, -4
	add	w2, w2, 4
.L12:
	ldp	w1, w0, [x19, 48]
	mul	w22, w22, w2
	ldr	w20, [x19, 148]
	bl	UTIL_CalcFrameSize
	ldr	w2, [x19, 56]
	mov	w1, 19923
	movk	w1, 0x1062, lsl 16
	mul	w20, w20, w2
	umull	x1, w20, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	and	w2, w1, 3
	cbz	w2, .L13
	and	w1, w1, -4
	add	w1, w1, 4
.L13:
	ldr	w2, [x29, 80]
	mul	w3, w0, w1
	cmp	w22, w2
	bhi	.L14
	sub	w2, w2, w22
	add	w3, w3, w2
.L14:
	ldr	w2, [x29, 88]
	mov	x1, 0
	ldr	x0, [x19, 136]
	cmp	w2, w3
	csel	w2, w2, w3, ls
	bl	RBUF_WriteData
	ldr	w0, [x21, 100]
	add	w0, w0, 1
	str	w0, [x21, 100]
	ldr	w0, [x19, 148]
	stp	w0, wzr, [x19, 152]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	AOP_ProcDelayCompensation, .-AOP_ProcDelayCompensation
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_DestroyChn
	.type	AOP_DestroyChn, %function
AOP_DestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1
	add	x0, x0, x20, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L45
	ldr	w0, [x19, 132]
	cmp	w0, 1
	beq	.L51
.L47:
	ldr	x0, [x19, 136]
	bl	RBUF_Destroy
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L45:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L51:
	mov	w0, w20
	bl	CAST_Destroy
	b	.L47
	.size	AOP_DestroyChn, .-AOP_DestroyChn
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_Init
	.type	AOP_Init, %function
AOP_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x23
	add	x22, x23, 1024
	bl	_mcount
	ldr	x20, .LC4
	ldr	x21, .LC5
	add	x20, x20, 64
	.p2align 2
.L53:
	mov	x2, 128
	ldr	x3, [x21, 40]
	str	x19, [x20, -64]
	mov	x0, x19
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	ldr	w0, [x19, -124]
	cmp	x19, x22
	orr	w0, w0, 4
	str	w0, [x19, -124]
	str	xzr, [x20], 8
	bne	.L53
	mov	x0, x23
	bl	CAST_Init
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	AOP_Init, .-AOP_Init
	.align	3
.LC4:
	.xword	.LANCHOR0
	.align	3
.LC5:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_DeInit
	.type	AOP_DeInit, %function
AOP_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x20, .LC6
	add	x20, x20, 64
	.p2align 2
.L56:
	mov	w0, w19
	add	w19, w19, 1
	bl	AOP_DestroyChn
	str	xzr, [x20], 8
	cmp	w19, 8
	bne	.L56
	mov	w0, w19
	bl	CAST_DeInit
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_DeInit, .-AOP_DeInit
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_Process
	.type	AOP_Process, %function
AOP_Process:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	mov	w21, 0
	add	x23, x29, 100
	bl	_mcount
	ldr	x20, .LC7
	ldr	x22, .LC8
	b	.L81
	.p2align 3
.L75:
	add	w21, w21, 1
	add	x20, x20, 8
	cmp	w21, 8
	beq	.L101
.L81:
	ldr	x19, [x20]
	ldr	w0, [x19, 4]
	tbnz	x0, 2, .L82
	ldr	w0, [x19, 4]
	ands	w0, w0, 3
	beq	.L61
	cmp	w0, 1
	beq	.L62
	ldr	w0, [x19, 4]
	mov	w1, 4
	bfi	w0, w1, 3, 4
	str	w0, [x19, 4]
	ldr	w0, [x19, 4]
	orr	w0, w0, w1
	str	w0, [x19, 4]
	.p2align 2
.L82:
	ldr	x19, [x20, 64]
	cbz	x19, .L75
	ldr	w0, [x19, 144]
	cmp	w0, 1
	bne	.L75
	ldr	x24, [x20]
	str	wzr, [x19, 20]
	ldr	w0, [x24, 12]
	uxtb	w0, w0
	str	w0, [x19, 24]
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 8, 8
	str	w0, [x19, 28]
	ldr	w0, [x24, 12]
	tbnz	x0, 19, .L77
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 16, 3
	str	w0, [x19, 32]
.L78:
	str	w0, [x19, 36]
	ldr	w0, [x24, 12]
	tbnz	x0, 30, .L79
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 24, 6
	str	w0, [x19, 40]
.L80:
	ldr	w0, [x24, 12]
	ldr	w1, [x19, 48]
	ubfx	x0, x0, 31, 1
	str	w0, [x19, 44]
	ldr	w0, [x24, 4]
	ubfx	x0, x0, 8, 1
	str	w0, [x19, 128]
	ldr	w0, [x19, 52]
	ldr	w26, [x24]
	ubfx	x26, x26, 20, 12
	str	w26, [x19, 124]
	bl	UTIL_CalcFrameSize
	mov	w1, w0
	ldr	w2, [x19, 56]
	mov	w0, w26
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x19, 120]
	ldr	x0, [x19, 136]
	add	x1, x19, 72
	bl	RBUF_UpdateAttr
	ldr	w0, [x24, 4]
	ldr	w1, [x19, 152]
	ubfx	x0, x0, 21, 9
	str	w0, [x19, 148]
	cmp	w0, w1
	beq	.L75
	add	w21, w21, 1
	mov	w0, 1
	cmp	w21, 8
	str	w0, [x19, 156]
	add	x20, x20, 8
	bne	.L81
.L101:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L62:
	mov	w0, w21
	bl	AOP_DestroyChn
	str	xzr, [x20, 64]
	ldr	x0, [x20]
.L73:
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L75
.L86:
	ldr	w1, [x0, 4]
	and	w1, w1, -121
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L82
	.p2align 3
.L61:
	str	xzr, [x29, 88]
	add	x0, x29, 96
	ldr	w1, [x19]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L66
	ldr	w1, [x19]
	mov	x0, x23
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L66
	ldr	w1, [x19]
	add	x0, x29, 104
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L66
	ldr	w1, [x19]
	add	x0, x29, 108
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L66
	ldr	w1, [x19]
	add	x0, x29, 84
	ubfx	x1, x1, 20, 12
	bl	AOE_REG_ReadBufLatencyMs
	cbnz	w0, .L66
	ldr	w2, [x19]
	ldp	w1, w0, [x29, 96]
	ubfx	x2, x2, 10, 1
	str	w2, [x29, 112]
	bl	UTIL_CalcFrameSize
	mov	w1, 1
	str	w1, [x29, 120]
	mov	x2, 0
	ldr	w1, [x19, 24]
	ubfx	x1, x1, 24, 1
	str	w1, [x29, 160]
	ldr	w4, [x19, 16]
	ldr	w3, [x19, 20]
	bfi	x2, x4, 0, 32
	bfi	x2, x3, 32, 32
	str	x2, [x29, 128]
	ldr	w2, [x19, 24]
	ubfx	x2, x2, 0, 24
	str	w2, [x29, 136]
	cbz	w1, .L64
	ldr	w2, [x19, 28]
	mov	x1, 0
	bfi	x1, x2, 0, 32
	ldr	w2, [x19, 32]
	bfi	x1, x2, 32, 32
	str	x1, [x29, 144]
	mov	x1, 0
	ldr	w2, [x19, 36]
	bfi	x1, x2, 0, 32
	ldr	w2, [x19, 40]
	bfi	x1, x2, 32, 32
	str	x1, [x29, 152]
.L65:
	ldr	w3, [x29, 84]
	mov	w1, w0
	ldr	w2, [x29, 104]
	str	w0, [x29, 164]
	mov	w0, w3
	str	w3, [x29, 172]
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x29, 168]
	add	x1, x29, 120
	add	x0, x29, 88
	bl	RBUF_Create
	ldr	x0, [x29, 88]
	cbz	x0, .L66
	mov	w1, 160
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L67
	ldr	x3, [x22, 40]
	mov	x2, 160
	mov	w1, 0
	add	x24, x0, 48
	blr	x3
	ldr	x3, [x22, 48]
	add	x1, x29, 96
	mov	x2, 80
	mov	x0, x24
	blr	x3
	ldr	x0, [x29, 88]
	str	x0, [x19, 136]
	ldr	x0, [x20]
	ldr	w1, [x0, 4]
	tbnz	x1, 19, .L102
.L68:
	str	wzr, [x19, 132]
.L84:
	mov	w0, 121
	stp	wzr, wzr, [x19, 16]
	stp	wzr, w0, [x19]
	stp	w0, wzr, [x19, 8]
	stp	w0, w0, [x19, 24]
	stp	wzr, wzr, [x19, 32]
	stp	wzr, wzr, [x19, 148]
	mov	w0, 1
	str	w0, [x19, 144]
	str	x19, [x20, 64]
.L70:
	ldr	x0, [x20]
	ldr	w1, [x0, 4]
	tbz	x1, 2, .L86
	b	.L82
.L103:
.L71:
.L72:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L67:
	ldr	x0, [x29, 88]
	bl	RBUF_Destroy
	.p2align 2
.L66:
	ldr	x0, [x20]
	str	xzr, [x20, 64]
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L73
	ldr	w1, [x0, 4]
	mov	w2, 1
	bfi	w1, w2, 3, 4
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L70
	.p2align 3
.L64:
	add	x1, x19, 28
	add	x19, x19, 36
	stp	x1, x19, [x29, 144]
	b	.L65
	.p2align 3
.L79:
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 24, 6
	neg	w0, w0
	str	w0, [x19, 40]
	b	.L80
	.p2align 3
.L77:
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 16, 3
	neg	w0, w0
	str	w0, [x19, 32]
	b	.L78
	.p2align 3
.L102:
	ldr	w0, [x0, 4]
	ubfx	x0, x0, 18, 1
	cbz	w0, .L68
	str	w0, [x19, 132]
	add	x1, x19, 72
	ldr	w2, [x19, 48]
	mov	w0, w21
	ldp	w3, w4, [x24, 4]
	bl	CAST_Create
	mov	x24, x0
	cbz	x0, .L103
	ldr	x1, [x19, 136]
	mov	w0, w21
	bl	CAST_SetAopBuf
	str	x24, [x19, 136]
	b	.L84
	.size	AOP_Process, .-AOP_Process
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_GetChnStatus
	.type	AOP_GetChnStatus, %function
AOP_GetChnStatus:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC9
	add	x20, x0, x20, uxtw 3
	ldr	x0, [x20, 64]
	cbz	x0, .L107
	ldr	w1, [x0, 144]
	str	w1, [x19]
	ldr	w1, [x0, 64]
	str	w1, [x19, 4]
	ldr	w1, [x0, 116]
	str	w1, [x19, 16]
	ldr	w1, [x0, 48]
	str	w1, [x19, 8]
	ldr	w1, [x0, 52]
	str	w1, [x19, 12]
	ldr	w1, [x0, 128]
	str	w1, [x19, 20]
	ldr	w1, [x0, 132]
	str	w1, [x19, 24]
	ldr	w0, [x0, 148]
	str	w0, [x19, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L107:
	str	wzr, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_GetChnStatus, .-AOP_GetChnStatus
	.align	3
.LC9:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_QueryRbfFree
	.type	AOP_QueryRbfFree, %function
AOP_QueryRbfFree:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC10
	add	x19, x0, x19, uxtw 3
	ldr	x2, [x19, 64]
	cbz	x2, .L110
	ldr	w3, [x2, 144]
	mov	w0, 0
	cbz	w3, .L109
	ldr	x2, [x2, 136]
	cbz	x2, .L109
	mov	w1, w20
	mov	x0, x2
	bl	RBUF_CheckFree
.L109:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L110:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_QueryRbfFree, .-AOP_QueryRbfFree
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteBuffProcTryCnt
	.type	AOP_WriteBuffProcTryCnt, %function
AOP_WriteBuffProcTryCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC11
	add	x0, x0, x19, uxtw 3
	ldr	x0, [x0, 64]
	cbz	x0, .L114
	ldr	w0, [x0, 132]
	cmp	w0, 1
	beq	.L119
.L114:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L119:
	mov	w0, w19
	bl	CAST_FiFoTryCnt
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_WriteBuffProcTryCnt, .-AOP_WriteBuffProcTryCnt
	.align	3
.LC11:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteBuffProcOKCnt
	.type	AOP_WriteBuffProcOKCnt, %function
AOP_WriteBuffProcOKCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC12
	add	x0, x0, x19, uxtw 3
	ldr	x0, [x0, 64]
	cbz	x0, .L120
	ldr	w0, [x0, 132]
	cmp	w0, 1
	beq	.L125
.L120:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L125:
	mov	w0, w19
	bl	CAST_FiFoFreeCnt
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_WriteBuffProcOKCnt, .-AOP_WriteBuffProcOKCnt
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteRbfData
	.type	AOP_WriteRbfData, %function
AOP_WriteRbfData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC13
	add	x19, x0, x19, uxtw 3
	ldr	x19, [x19, 64]
	cbz	x19, .L141
	ldr	w1, [x19, 144]
	mov	w0, 0
	cbz	w1, .L127
	ldr	w0, [x20, 28]
	cbz	w0, .L150
.L129:
	ldr	w0, [x19, 132]
	ldr	w2, [x20, 8]
	cmp	w0, 1
	ldr	x1, [x20]
	ldr	x0, [x19, 136]
	beq	.L151
	bl	RBUF_WriteDataDma
.L127:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L150:
	ldr	x0, [x19, 48]
	ldr	x1, [x20, 16]
	cmp	x1, x0
	beq	.L131
	ldr	w0, [x19, 48]
	ldr	w1, [x20, 16]
	cmp	w1, w0
	beq	.L132
	bl	AOE_GetWKBuf
	mov	x1, x0
	ldr	w0, [x19, 48]
	mov	x2, x20
	bl	UTIL_UnifyBitDepthPcmData
.L132:
	ldr	w0, [x19, 52]
	ldr	w1, [x20, 20]
	cmp	w1, w0
	beq	.L131
	bl	AOE_GetWKBuf
	mov	x1, x0
	ldr	w0, [x19, 52]
	mov	x2, x20
	bl	UTIL_UpmixPcmData
.L131:
	ldr	w0, [x19, 44]
	cbz	w0, .L134
	bl	AOE_GetWKBuf
	mov	x21, x0
	ldr	x3, .LC14
	mov	w1, 0
	ldr	w2, [x20, 8]
	ldr	x3, [x3, 40]
	blr	x3
	str	x21, [x20]
.L134:
	ldr	w0, [x19, 4]
	ldr	w1, [x19, 24]
	cmp	w1, w0
	beq	.L152
.L135:
	ldr	w0, [x19, 132]
	cmp	w0, 1
	beq	.L136
	bl	AOE_GetWKBuf
	ldr	x22, .LC14
	ldr	w2, [x20, 8]
	mov	x23, x0
	ldr	x1, [x20]
	add	x21, x19, 20
	ldr	x3, [x22, 48]
	blr	x3
	str	x23, [x20]
	mov	x2, x19
	mov	x0, x20
	ldr	w1, [x19, 40]
	mov	x3, x21
	bl	UTIL_LRFadeGainProcess
	ldr	x3, [x22, 48]
	mov	x2, 20
	mov	x1, x21
	mov	x0, x19
	blr	x3
	b	.L129
	.p2align 3
.L151:
	bl	RBUF_WriteData
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L141:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L152:
	ldr	w0, [x19, 12]
	ldr	w1, [x19, 32]
	cmp	w1, w0
	bne	.L135
	.p2align 2
.L136:
	mov	x0, 121
	ldr	x1, [x19, 24]
	movk	x0, 0x79, lsl 32
	cmp	x1, x0
	bne	.L138
	ldr	x0, [x19, 32]
	cbnz	x0, .L138
	ldr	w0, [x19, 40]
	cbz	w0, .L129
.L138:
	bl	AOE_GetWKBuf
	mov	x21, x0
	ldr	x3, .LC14
	ldr	w2, [x20, 8]
	ldr	x1, [x20]
	ldr	x3, [x3, 48]
	blr	x3
	str	x21, [x20]
	add	x2, x19, 20
	mov	x0, x20
	ldr	w1, [x19, 40]
	bl	UTIL_LRGainProcess
	b	.L129
	.size	AOP_WriteRbfData, .-AOP_WriteRbfData
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_GetRingOut
	.type	AOP_GetRingOut, %function
AOP_GetRingOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC15
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L155
	ldr	x0, [x0, 136]
.L154:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L155:
	mov	x0, 0
	b	.L154
	.size	AOP_GetRingOut, .-AOP_GetRingOut
	.align	3
.LC15:
	.xword	.LANCHOR0
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stAopRm, %object
	.size	g_stAopRm, 128
g_stAopRm:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
