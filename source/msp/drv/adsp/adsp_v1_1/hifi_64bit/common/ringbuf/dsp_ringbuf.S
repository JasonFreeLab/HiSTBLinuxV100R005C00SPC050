#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"dsp_ringbuf.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	RBUF_Create
	.type	RBUF_Create, %function
RBUF_Create:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w1, 120
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L7
	ldr	x21, .LC0
	mov	x2, 120
	mov	w1, 0
	ldr	x3, [x21, 40]
	blr	x3
	ldr	x3, [x21, 48]
	mov	x2, 56
	mov	x1, x20
	mov	x0, x19
	blr	x3
	ldr	w0, [x20]
	cbz	w0, .L4
	ldr	w3, [x19, 16]
	ldr	x0, [x19, 8]
.L5:
	ldp	x2, x4, [x19, 24]
	stp	x2, x4, [x19, 56]
	str	x0, [x19, 72]
	str	w3, [x19, 80]
	str	wzr, [x2]
	ldr	x0, [x19, 64]
	str	wzr, [x0]
	str	x19, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4:
	ldr	w1, [x20, 16]
	mov	w0, 26
	ldr	w2, [x20, 44]
	bl	HI_ADSP_VMALLOC_Aligned
	cbz	x0, .L9
	str	x0, [x19, 8]
	ldr	w3, [x20, 16]
	str	w3, [x19, 16]
	b	.L5
.L9:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L7:
	str	xzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	RBUF_Create, .-RBUF_Create
	.align	3
.LC0:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_Create_EXT
	.type	RBUF_Create_EXT, %function
RBUF_Create_EXT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w1, 120
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L16
	ldr	x21, .LC1
	mov	x2, 120
	mov	w1, 0
	ldr	x3, [x21, 40]
	blr	x3
	ldr	x3, [x21, 48]
	mov	x2, 56
	mov	x1, x20
	mov	x0, x19
	blr	x3
	ldr	w0, [x20]
	cbz	w0, .L13
	ldr	w2, [x19, 16]
	ldr	x0, [x19, 8]
.L14:
	ldp	x4, x3, [x19, 24]
	stp	x4, x3, [x19, 56]
	str	x0, [x19, 72]
	str	w2, [x19, 80]
	str	x19, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L13:
	ldr	w1, [x20, 16]
	mov	w0, 26
	ldr	w2, [x20, 44]
	bl	HI_ADSP_VMALLOC_Aligned
	cbz	x0, .L17
	str	x0, [x19, 8]
	ldr	w2, [x20, 16]
	str	w2, [x19, 16]
	b	.L14
.L17:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L16:
	str	xzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	RBUF_Create_EXT, .-RBUF_Create_EXT
	.align	3
.LC1:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_Destroy
	.type	RBUF_Destroy, %function
RBUF_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L18
	ldr	w0, [x19]
	cbz	w0, .L24
.L20:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L18:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L24:
	ldr	x1, [x19, 8]
	mov	w0, 26
	bl	HI_ADSP_VFREE_Aligned
	b	.L20
	.size	RBUF_Destroy, .-RBUF_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_ReadData
	.type	RBUF_ReadData, %function
RBUF_ReadData:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x26, x1
	mov	w22, w2
	bl	_mcount
	cbz	x20, .L39
	ldr	w0, [x20, 92]
	add	x23, x20, 56
	ldr	x2, [x20, 56]
	mov	x24, 0
	add	w0, w0, 1
	str	w0, [x20, 92]
	mov	x27, 0
	ldr	x1, [x23, 8]
	ldr	w19, [x1]
	ldr	w0, [x2]
	cmp	w19, w0
	bhi	.L27
	add	w2, w22, w19
	cmp	w0, w2
	bcc	.L52
.L41:
	mov	w21, w22
	mov	w22, 0
.L28:
	cbz	w21, .L30
	cbz	x26, .L31
	ldr	x28, .LC2
	uxtw	x25, w21
	ldr	x1, [x23, 16]
	mov	x2, x25
	mov	x0, x26
	ubfx	x24, x24, 32, 32
	ldr	x3, [x28, 48]
	add	x1, x1, x19, uxtw
	add	w19, w19, w21
	blr	x3
	add	x0, x26, x25
	cbz	w24, .L32
	ubfx	x25, x27, 32, 32
	cbz	x0, .L34
	ldr	x1, [x23, 16]
	uxtw	x2, w24
	ldr	x3, [x28, 48]
	add	x1, x1, x25, uxtw
	blr	x3
.L34:
	ldr	x1, [x23, 8]
	add	w19, w24, w25
.L30:
	ldr	w0, [x23, 24]
	cmp	w0, w19
	csel	w19, w19, wzr, ne
	adds	w0, w21, w22
	str	w19, [x1]
	bne	.L37
	ldr	w1, [x20, 96]
	add	w1, w1, 1
	str	w1, [x20, 96]
.L37:
	ldr	w1, [x20, 88]
	add	w1, w1, w0
	str	w1, [x20, 88]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L27:
	ldr	w21, [x23, 24]
	add	w2, w22, w19
	cmp	w2, w21
	bls	.L41
	sub	w21, w21, w19
	sub	w22, w22, w21
	cmp	w0, w22
	bcs	.L35
	bfi	x24, x0, 32, 32
	mov	w22, w0
	b	.L28
	.p2align 3
.L31:
	ubfx	x24, x24, 32, 32
	add	w19, w19, w21
	ubfx	x25, x27, 32, 32
	cbnz	w24, .L34
.L32:
	ldr	x1, [x23, 8]
	b	.L30
	.p2align 3
.L39:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L52:
	sub	w21, w0, w19
	mov	w22, 0
	b	.L28
	.p2align 3
.L35:
	bfi	x24, x22, 32, 32
	b	.L28
	.size	RBUF_ReadData, .-RBUF_ReadData
	.align	3
.LC2:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_ReadDataComplete
	.type	RBUF_ReadDataComplete, %function
RBUF_ReadDataComplete:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L53
	add	x3, x19, 56
	ldr	x0, [x19, 56]
	ldr	x2, [x3, 8]
	ldr	w1, [x2]
	ldr	w0, [x0]
	cmp	w1, w0
	bhi	.L55
	add	w4, w20, w1
	cmp	w0, w4
	bcc	.L56
	mov	w4, w20
	ldr	w3, [x3, 24]
	cbnz	w4, .L62
.L69:
	mov	w0, w1
.L59:
	cmp	w3, w0
	csel	w0, w0, wzr, ne
	str	w0, [x2]
	ldr	w1, [x19, 88]
	add	w20, w1, w20
	str	w20, [x19, 88]
.L53:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L55:
	ldr	w3, [x3, 24]
	add	w4, w20, w1
	cmp	w4, w3
	bls	.L63
	sub	w4, w3, w1
	sub	w5, w20, w4
	cmp	w0, w5
	csel	w0, w0, w5, ls
	cbz	w4, .L69
	cbnz	w0, .L59
	.p2align 2
.L62:
	add	w0, w1, w4
	b	.L59
	.p2align 3
.L63:
	mov	w4, w20
	cbz	w4, .L69
	b	.L62
	.p2align 3
.L56:
	sub	w4, w0, w1
	ldr	w3, [x3, 24]
	cbz	w4, .L69
	b	.L62
	.size	RBUF_ReadDataComplete, .-RBUF_ReadDataComplete
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_WriteDataComplete
	.type	RBUF_WriteDataComplete, %function
RBUF_WriteDataComplete:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L71
	add	x0, x19, 56
	ldr	x2, [x19, 56]
	ldr	x1, [x0, 8]
	ldr	w3, [x1]
	ldr	w1, [x2]
	cmp	w3, w1
	ldr	w3, [x0, 24]
	bhi	.L74
	add	w0, w20, w1
	cmp	w3, w0
	bcs	.L74
	sub	w4, w3, w1
	sub	w0, w20, w4
	cbz	w4, .L78
	cbnz	w0, .L75
	add	w0, w1, w4
	b	.L75
	.p2align 3
.L74:
	cbnz	w20, .L84
.L78:
	mov	w0, w1
.L75:
	cmp	w3, w0
	csel	w0, w0, wzr, ne
	str	w0, [x2]
	ldr	w1, [x19, 104]
	add	w20, w1, w20
	str	w20, [x19, 104]
.L71:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L84:
	mov	w4, w20
	add	w0, w1, w4
	b	.L75
	.size	RBUF_WriteDataComplete, .-RBUF_WriteDataComplete
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_QueryInfo
	.type	RBUF_QueryInfo, %function
RBUF_QueryInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x20, .L94
	ldp	w4, w0, [x20, 44]
	str	w0, [x19, 36]
	add	x2, x20, 56
	ldr	x0, [x20, 72]
	str	x0, [x19]
	ldr	w0, [x20, 80]
	str	w0, [x19, 16]
	ldr	x0, [x20, 56]
	ldr	w0, [x0]
	str	w0, [x19, 12]
	ldr	x0, [x20, 64]
	ldr	w0, [x0]
	str	w0, [x19, 8]
	ldr	x1, [x2, 8]
	ldr	x0, [x20, 56]
	ldr	w3, [x1]
	ldr	w0, [x0]
	cmp	w3, w0
	bls	.L95
	ldr	w5, [x2, 24]
	add	w1, w0, w5
	sub	w5, w5, w3
	sub	w0, w1, w3
	stp	w5, w0, [x19, 20]
	ldr	x0, [x2, 8]
	ldr	x1, [x20, 56]
	ldr	w0, [x0]
	ldr	w1, [x1]
	cmp	w0, w1
	bhi	.L90
.L97:
	ldr	w2, [x2, 24]
	add	w0, w0, w2
	sub	w2, w2, w1
	sub	w0, w0, w1
	cmp	w4, w0
	stp	w2, w0, [x19, 28]
	bcs	.L96
.L92:
	ldp	w2, w1, [x19, 28]
	sub	w0, w0, w4
	sub	w1, w1, w2
	cmp	w4, w1
	bls	.L93
	str	w0, [x19, 28]
.L93:
	str	w0, [x19, 32]
.L85:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L95:
	sub	w0, w0, w3
	stp	w0, w0, [x19, 20]
	ldr	x0, [x2, 8]
	ldr	x1, [x20, 56]
	ldr	w0, [x0]
	ldr	w1, [x1]
	cmp	w0, w1
	bls	.L97
.L90:
	sub	w0, w0, w1
	cmp	w4, w0
	stp	w0, w0, [x19, 28]
	bcc	.L92
.L96:
	stp	wzr, wzr, [x19, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L94:
	ldr	x3, .LC3
	mov	x2, 40
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 40]
	blr	x3
	b	.L85
	.size	RBUF_QueryInfo, .-RBUF_QueryInfo
	.align	3
.LC3:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_QueryBusy_ProvideRptr
	.type	RBUF_QueryBusy_ProvideRptr, %function
RBUF_QueryBusy_ProvideRptr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L101
	add	x2, x19, 56
	ldr	x0, [x19, 56]
	ldr	x3, [x2, 8]
	ldr	w1, [x20]
	ldr	w3, [x3]
	ldr	w0, [x0]
	cmp	w1, w0
	bhi	.L103
.L102:
	sub	w0, w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L103:
	ldr	w2, [x2, 24]
	add	w0, w0, w2
	b	.L102
	.p2align 3
.L101:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_QueryBusy_ProvideRptr, .-RBUF_QueryBusy_ProvideRptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_QueryBusy
	.type	RBUF_QueryBusy, %function
RBUF_QueryBusy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L107
	add	x2, x19, 56
	ldr	x0, [x19, 56]
	ldr	x1, [x2, 8]
	ldr	w1, [x1]
	ldr	w0, [x0]
	cmp	w1, w0
	bhi	.L109
.L108:
	sub	w0, w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L109:
	ldr	w2, [x2, 24]
	add	w0, w0, w2
	b	.L108
	.p2align 3
.L107:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_QueryBusy, .-RBUF_QueryBusy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_QueryFree
	.type	RBUF_QueryFree, %function
RBUF_QueryFree:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L114
	ldp	x1, x2, [x19, 56]
	ldr	w4, [x19, 44]
	ldr	w3, [x2]
	ldr	w2, [x1]
	cmp	w3, w2
	sub	w1, w3, w2
	bls	.L116
.L113:
	sub	w0, w1, w4
	cmp	w4, w1
	csel	w0, w0, wzr, cc
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L116:
	ldr	w0, [x19, 80]
	add	w1, w3, w0
	sub	w1, w1, w2
	b	.L113
	.p2align 3
.L114:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_QueryFree, .-RBUF_QueryFree
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_CheckFree
	.type	RBUF_CheckFree, %function
RBUF_CheckFree:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L123
	add	x0, x19, 56
	ldr	x2, [x19, 56]
	ldr	x3, [x0, 8]
	ldr	w1, [x19, 44]
	ldr	w0, [x0, 24]
	ldr	w4, [x3]
	ldr	w5, [x2]
	cmp	w4, w5
	bls	.L124
	sub	w3, w4, w5
	add	w2, w5, w0
	cmp	w1, w3
	sub	w2, w2, w4
	bcc	.L121
.L125:
	add	w2, w20, w2
	mov	w1, 1
.L122:
	ldr	w0, [x19, 48]
	ldp	x19, x20, [sp, 16]
	cmp	w0, w2
	cset	w0, cc
	orr	w0, w1, w0
	eor	w0, w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L124:
	add	w0, w4, w0
	sub	w2, w5, w4
	sub	w3, w0, w5
	cmp	w1, w3
	bcs	.L125
.L121:
	sub	w3, w3, w1
	add	w2, w20, w2
	cmp	w20, w3
	cset	w1, cs
	b	.L122
	.p2align 3
.L123:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_CheckFree, .-RBUF_CheckFree
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_Flush
	.type	RBUF_Flush, %function
RBUF_Flush:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L126
	ldp	x1, x0, [x19, 56]
	ldr	w1, [x1]
	str	w1, [x0]
.L126:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_Flush, .-RBUF_Flush
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_ReadDataDma
	.type	RBUF_ReadDataDma, %function
RBUF_ReadDataDma:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	mov	x25, x1
	mov	w23, w2
	mov	x27, x3
	bl	_mcount
	cbz	x24, .L151
	cbz	x27, .L162
	add	x26, x24, 56
	ldr	x0, [x24, 56]
	ldr	x1, [x26, 8]
	mov	x21, 0
	ldr	w19, [x27]
	mov	x28, 0
	ldr	w1, [x1]
	ldr	w0, [x0]
.L149:
	cmp	w19, w0
	bhi	.L134
	add	w1, w23, w19
	cmp	w1, w0
	bls	.L137
	sub	w20, w0, w19
	ubfx	x22, x21, 32, 32
.L136:
	cbz	w20, .L139
	cbz	x25, .L140
	ldr	x3, .LC4
	uxtw	x23, w20
	ldr	x1, [x26, 16]
	mov	x2, x23
	mov	x0, x25
	ubfx	x21, x21, 32, 32
	ldr	x4, [x3, 48]
	add	x1, x1, x19, uxtw
	str	x3, [x29, 104]
	add	w19, w19, w20
	blr	x4
	add	x0, x25, x23
	cbz	w21, .L139
	ubfx	x23, x28, 32, 32
	ldr	x3, [x29, 104]
	cbz	x0, .L143
	ldr	x1, [x26, 16]
	uxtw	x2, w21
	ldr	x3, [x3, 48]
	add	x1, x1, x23, uxtw
	blr	x3
.L143:
	add	w19, w23, w21
.L139:
	ldr	w0, [x26, 24]
	cmp	w0, w19
	csel	w19, w19, wzr, ne
	cbz	x27, .L163
	str	w19, [x27]
	add	w0, w20, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L134:
	ldr	w20, [x26, 24]
	add	w1, w23, w19
	cmp	w1, w20
	bls	.L137
	sub	w20, w20, w19
	sub	w22, w23, w20
	cmp	w22, w0
	bls	.L144
	bfi	x21, x0, 32, 32
	mov	w22, w0
	b	.L136
	.p2align 3
.L137:
	ubfx	x22, x21, 32, 32
	mov	w20, w23
	b	.L136
	.p2align 3
.L140:
	ubfx	x21, x21, 32, 32
	add	w19, w19, w20
	ubfx	x23, x28, 32, 32
	cbnz	w21, .L143
	b	.L139
	.p2align 3
.L144:
	bfi	x21, x22, 32, 32
	b	.L136
	.p2align 3
.L163:
	ldr	x1, [x26, 8]
	adds	w0, w20, w22
	str	w19, [x1]
	bne	.L148
	ldr	w1, [x24, 96]
	add	w1, w1, 1
	str	w1, [x24, 96]
.L148:
	ldr	w1, [x24, 88]
	add	w1, w1, w0
	str	w1, [x24, 88]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L162:
	ldr	w0, [x24, 92]
	add	x26, x24, 56
	ldr	x1, [x24, 56]
	mov	x21, 0
	add	w0, w0, 1
	str	w0, [x24, 92]
	mov	x28, 0
	ldr	x0, [x26, 8]
	ldr	w19, [x0]
	ldr	w0, [x1]
	b	.L149
	.p2align 3
.L151:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
	.size	RBUF_ReadDataDma, .-RBUF_ReadDataDma
	.align	3
.LC4:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_WriteDataDma
	.type	RBUF_WriteDataDma, %function
RBUF_WriteDataDma:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	mov	w19, w2
	bl	_mcount
	cbz	x21, .L178
	ldr	w0, [x21, 108]
	add	x28, x21, 56
	ldr	x2, [x21, 56]
	add	w0, w0, 1
	str	w0, [x21, 108]
	stp	wzr, wzr, [x29, 112]
	ldr	x0, [x28, 8]
	ldr	w0, [x0]
	ldr	w1, [x2]
	stp	w1, wzr, [x29, 120]
	cmp	w0, w1
	bhi	.L166
	ldr	w0, [x28, 24]
	add	w3, w19, w1
	cmp	w0, w3
	bcc	.L167
.L169:
	mov	w22, w19
	stp	wzr, w19, [x29, 108]
.L168:
	cbz	w22, .L172
	ldr	x20, .LC7
	add	x26, x29, 116
	mov	w25, w22
	mov	x23, 0
	add	x27, x29, 120
.L175:
	ldr	w19, [x27, x23]
	uxtw	x3, w25
	ldr	x0, [x28, 16]
	mov	x1, x24
	mov	x2, x3
	add	x0, x0, x19, uxtw
	cbz	x24, .L187
	ldr	x4, [x20, 48]
	add	x24, x24, x3
	blr	x4
.L174:
	cmp	x23, 4
	add	w1, w19, w25
	add	x23, x23, 4
	beq	.L185
	ldr	w25, [x26], 4
	cbnz	w25, .L175
	.p2align 2
.L185:
	ldr	x2, [x21, 56]
.L172:
	ldr	w0, [x28, 24]
	cmp	w0, w1
	ldr	w0, [x29, 108]
	csel	w1, w1, wzr, hi
	str	w1, [x2]
	adds	w0, w0, w22
	bne	.L177
	ldr	w1, [x21, 112]
	add	w1, w1, 1
	str	w1, [x21, 112]
.L177:
	ldr	w1, [x21, 104]
	add	w1, w1, w0
	str	w1, [x21, 104]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L166:
	add	w3, w19, w1
	cmp	w0, w3
	bhi	.L169
	sub	w22, w0, w1
	stp	wzr, w22, [x29, 108]
	b	.L168
	.p2align 3
.L178:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L187:
	ldr	x3, [x20, 40]
	mov	w1, 0
	blr	x3
	b	.L174
	.p2align 3
.L167:
	sub	w22, w0, w1
	sub	w0, w19, w22
	str	w0, [x29, 116]
	stp	w0, w22, [x29, 108]
	b	.L168
	.size	RBUF_WriteDataDma, .-RBUF_WriteDataDma
	.align	3
.LC7:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_WriteData
	.type	RBUF_WriteData, %function
RBUF_WriteData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	mov	w2, w21
	mov	x1, x20
	mov	x0, x19
	bl	RBUF_WriteDataDma
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	RBUF_WriteData, .-RBUF_WriteData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_CopyData
	.type	RBUF_CopyData, %function
RBUF_CopyData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x1
	mov	w19, w2
	bl	_mcount
	cmp	x20, xzr
	cset	w2, eq
	cmp	x23, xzr
	cset	w0, eq
	orr	w2, w2, w0
	mov	w0, 0
	cbz	w2, .L211
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L211:
	add	x24, x20, 56
	ldr	x1, [x20, 56]
	ldr	x3, [x23, 56]
	add	x25, x23, 56
	ldr	x26, [x25, 16]
	ldp	x0, x28, [x24, 8]
	ldr	w5, [x0]
	ldr	w4, [x3]
	ldr	w0, [x0]
	ldr	w1, [x1]
	cmp	w0, w1
	bls	.L212
	ldr	w21, [x24, 24]
	add	w6, w19, w0
	cmp	w6, w21
	bls	.L205
	sub	w21, w21, w0
	mov	w6, 2
	sub	w20, w19, w21
	cmp	w1, w20
	csel	w22, w1, w20, ls
.L192:
	ldr	x0, [x25, 8]
	ldr	w0, [x0]
	ldr	w20, [x3]
	cmp	w0, w20
	bhi	.L193
	ldr	w1, [x25, 24]
	add	w0, w19, w20
	cmp	w1, w0
	bcs	.L206
	sub	w20, w1, w20
	mov	w0, 2
	sub	w27, w19, w20
.L195:
	cmp	w0, 2
	cset	w0, eq
	tst	w2, w0
	bne	.L213
	cmp	w20, w21
	beq	.L214
	bcs	.L200
	sub	w3, w21, w20
	ldr	x21, .LC8
	add	x0, x26, x4, uxtw
	uxtw	x2, w20
	uxtw	x4, w3
	str	x4, [x29, 104]
	ldr	x4, [x21, 48]
	add	x1, x28, x5, uxtw
	add	w27, w3, w22
	str	w5, [x29, 100]
	blr	x4
	ldr	w5, [x29, 100]
	mov	x0, x26
	ldr	x4, [x21, 48]
	add	w1, w5, w20
	ldr	x20, [x29, 104]
	add	x1, x28, x1
	mov	x2, x20
	blr	x4
	ldr	x4, [x21, 48]
	add	x0, x26, x20
	mov	x1, x28
	uxtw	x2, w22
	blr	x4
.L197:
	ldr	w4, [x24, 24]
	mov	w0, w19
	ldr	x2, [x24, 8]
	cmp	w4, w22
	ldr	w1, [x25, 24]
	csel	w22, w22, wzr, ne
	str	w22, [x2]
	cmp	w1, w27
	csel	w27, w27, wzr, ne
	ldr	x1, [x23, 56]
	str	w27, [x1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L212:
	add	w2, w19, w0
	cmp	w1, w2
	bcs	.L205
	mov	w2, 1
	sub	w21, w1, w0
	mov	w22, 0
	mov	w6, w2
	b	.L192
	.p2align 3
.L193:
	add	w1, w19, w20
	cmp	w0, w1
	sub	w0, w0, w20
	csel	w20, w0, w19, ls
.L194:
	cmp	w6, 1
	beq	.L215
	cmp	w6, 2
	beq	.L216
	mov	w27, 0
	mov	w0, 1
	b	.L195
	.p2align 3
.L205:
	mov	w2, 1
	mov	w21, w19
	mov	w22, 0
	mov	w6, w2
	b	.L192
	.p2align 3
.L215:
	ldr	x6, .LC8
	add	x0, x26, x4, uxtw
	add	w27, w19, w4
	uxtw	x2, w19
	add	x1, x28, x5, uxtw
	add	w22, w19, w5
	ldr	x4, [x6, 48]
	blr	x4
	b	.L197
	.p2align 3
.L206:
	mov	w20, w19
	b	.L194
	.p2align 3
.L216:
	ldr	x20, .LC8
	uxtw	x2, w21
	add	x0, x26, x4, uxtw
	add	w21, w4, w21
	add	x1, x28, x5, uxtw
	add	w27, w21, w22
	ldr	x4, [x20, 48]
	blr	x4
	ldr	x4, [x20, 48]
	add	x0, x26, x21, uxtw
	mov	x1, x28
	uxtw	x2, w22
	blr	x4
	b	.L197
	.p2align 3
.L200:
	sub	w3, w20, w21
	ldr	x20, .LC8
	add	x1, x28, x5, uxtw
	uxtw	x2, w21
	add	x0, x26, x4, uxtw
	str	w4, [x29, 100]
	ldr	x6, [x20, 48]
	uxtw	x4, w3
	add	w22, w27, w3
	str	x4, [x29, 104]
	blr	x6
	ldr	w4, [x29, 100]
	mov	x1, x28
	add	w0, w4, w21
	ldr	x21, [x29, 104]
	ldr	x4, [x20, 48]
	add	x0, x26, x0
	mov	x2, x21
	blr	x4
	ldr	x4, [x20, 48]
	add	x1, x28, x21
	mov	x0, x26
	uxtw	x2, w27
	blr	x4
	b	.L197
	.p2align 3
.L213:
	ldr	x3, .LC8
	add	x0, x26, x4, uxtw
	uxtw	x2, w20
	add	x1, x28, x5, uxtw
	add	w21, w5, w20
	str	x3, [x29, 104]
	ldr	x4, [x3, 48]
	add	w22, w27, w21
	blr	x4
	ldr	x3, [x29, 104]
	add	x1, x28, x21, uxtw
	mov	x0, x26
	uxtw	x2, w27
	ldr	x4, [x3, 48]
	blr	x4
	b	.L197
	.p2align 3
.L214:
	uxtw	x2, w20
	ldr	x20, .LC8
	add	x0, x26, x4, uxtw
	add	x1, x28, x5, uxtw
	mov	w22, w27
	ldr	x4, [x20, 48]
	blr	x4
	ldr	x4, [x20, 48]
	uxtw	x2, w27
	mov	x1, x28
	mov	x0, x26
	blr	x4
	b	.L197
	.size	RBUF_CopyData, .-RBUF_CopyData
	.align	3
.LC8:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_GetCompressInfo
	.type	RBUF_GetCompressInfo, %function
RBUF_GetCompressInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cbz	x19, .L229
	add	x0, x19, 56
	ldr	w1, [x0, 24]
	ldp	x2, x4, [x0, 8]
	ldr	w3, [x2]
	add	w6, w3, 2
	cmp	w6, w1
	uxtw	x3, w3
	bcs	.L224
	uxtw	x1, w6
.L220:
	ldrh	w5, [x4, x3]
	cbz	w5, .L217
	mov	w7, 65535
	add	x2, x4, x1
	cmp	w5, w7
	beq	.L221
	ldrh	w1, [x4, x1]
	cmp	w1, w5
	bcc	.L217
.L221:
	str	w5, [x20]
	mov	w1, 65535
	ldrh	w7, [x4, x3]
	cmp	w7, w1
	beq	.L230
	ldrh	w0, [x2]
	mov	w6, -1934
	mov	w1, 19999
	sub	w5, w0, w5
	str	w5, [x21]
	strh	w6, [x4, x3]
	strh	w1, [x2]
.L217:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L224:
	mov	x1, 0
	mov	w6, 0
	b	.L220
	.p2align 3
.L229:
	str	wzr, [x20]
	str	wzr, [x21]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L230:
	str	wzr, [x20]
	add	w6, w6, 2
	ldrh	w1, [x2]
	str	w1, [x21]
	ldr	w1, [x0, 24]
	ldr	x0, [x0, 8]
	cmp	w6, w1
	csel	w6, w6, wzr, cc
	str	w6, [x0]
	b	.L217
	.size	RBUF_GetCompressInfo, .-RBUF_GetCompressInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RBUF_UpdateAttr
	.type	RBUF_UpdateAttr, %function
RBUF_UpdateAttr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L231
	ldr	w0, [x20, 52]
	str	w0, [x19, 52]
	ldr	w0, [x20, 48]
	str	w0, [x19, 48]
.L231:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	RBUF_UpdateAttr, .-RBUF_UpdateAttr
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
