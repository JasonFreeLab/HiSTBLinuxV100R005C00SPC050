#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vfmw_write_yuv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	YUV_DumpFrame_Cmp
	.type	YUV_DumpFrame_Cmp, %function
YUV_DumpFrame_Cmp:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC0
	mov	w0, 32
	ldr	x1, .LC2
	bl	dprint_vfmw
	ldp	x29, x30, [sp], 16
	ret
	.size	YUV_DumpFrame_Cmp, .-YUV_DumpFrame_Cmp
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	YUV_DumpFrame_Tile
	.type	YUV_DumpFrame_Tile, %function
YUV_DumpFrame_Tile:
	sub	sp, sp, #208
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	mov	x20, x0
	mov	x0, x30
	mov	x25, x1
	mov	x27, x2
	mov	w24, w3
	mov	w19, w4
	mov	w21, w5
	mov	w22, w6
	mov	w23, w7
	ldr	w28, [x29, 192]
	ldr	x26, [x29, 216]
	bl	_mcount
	add	x0, x29, 104
	str	xzr, [x29, 184]
	stp	xzr, xzr, [x0]
	add	x0, x29, 120
	stp	xzr, xzr, [x0]
	add	x0, x29, 136
	stp	xzr, xzr, [x0]
	add	x0, x29, 152
	stp	xzr, xzr, [x0]
	add	x0, x29, 168
	stp	xzr, xzr, [x0]
	cbz	x20, .L2
	sub	w0, w28, #1
	cmp	w0, 16
	bls	.L60
.L4:
	cmp	w28, 16
	add	w4, w24, 255
	and	w4, w4, -256
	beq	.L61
.L9:
	sub	w28, w28, #17
	cmp	w28, 1
	bls	.L8
	add	w5, w19, 31
	mov	w3, 0
	and	w5, w5, -32
	mov	w2, 0
.L10:
	ldr	w0, [x26, 168]
	cmp	w0, 10
	beq	.L62
.L39:
	mov	x3, 0
	mov	x4, 0
.L12:
	ldr	w1, [x26, 112]
	cmp	w0, wzr
	ldr	w2, [x26, 144]
	stp	w1, w2, [x29, 180]
	ldrb	w1, [x26, 66]
	mov	w2, 8
	stp	x27, x3, [x29, 152]
	ldr	w3, [x29, 208]
	csel	w0, w0, w2, ne
	eor	x1, x1, 2
	str	w0, [x29, 168]
	cmp	w0, w3
	ubfx	x0, x1, 1, 1
	stp	x25, x4, [x29, 136]
	csel	w25, w3, w2, ge
	mov	w1, w24
	stp	w25, w0, [x29, 172]
	ldr	x0, .LC4
	add	x3, x29, 104
	mov	w2, w19
	ldr	x0, [x0]
	str	x0, [x29, 104]
	add	x0, x0, 9437184
	str	x0, [x29, 120]
	ldr	x0, .LC5
	ldr	x0, [x0]
	str	x0, [x29, 112]
	add	x0, x0, 9437184
	str	x0, [x29, 128]
	add	x0, x29, 136
	bl	IMAGE_ConvertTo2D
	ldr	w0, [x29, 172]
	cmp	w0, 10
	beq	.L63
	mul	w27, w24, w19
	ldr	x0, [x29, 104]
.L19:
	ldr	x26, .LC7
	mov	x2, x20
	mov	w1, w27
	ldr	x3, [x26, 88]
	blr	x3
.L20:
	ldr	w0, [x29, 172]
	cmp	w0, 10
	beq	.L64
	lsr	w10, w19, 1
	ldr	x2, [x29, 120]
	cbz	w10, .L65
.L24:
	ldr	x25, .LC8
	lsr	w7, w24, 1
	ldr	x6, .LC9
	ubfiz	x12, x24, 1, 31
	mov	w9, 0
	mov	w8, 0
	uxtw	x11, w24
	.p2align 2
.L34:
	cmp	w0, 10
	beq	.L27
	cbz	w7, .L29
	lsr	w0, w9, 1
	mov	w1, 1
	add	w13, w7, w0
	.p2align 2
.L33:
	sub	w5, w1, #1
	uxtw	x3, w0
	ldr	x4, [x25]
	add	w0, w0, 1
	cmp	w13, w0
	ldrb	w5, [x2, x5]
	strb	w5, [x4, x3]
	ldr	x4, [x6]
	ldrb	w5, [x2, w1, uxtw]
	add	w1, w1, 2
	strb	w5, [x4, x3]
	bne	.L33
	ldr	w0, [x29, 172]
.L29:
	add	x2, x2, x11
.L32:
	add	w8, w8, 1
	add	w9, w9, w24
	cmp	w8, w10
	bcc	.L34
.L25:
	cmp	w0, 10
	beq	.L36
.L26:
	lsr	w27, w27, 2
.L58:
	ldr	x0, [x6]
	mov	x2, x20
	ldr	x3, [x26, 88]
	mov	w1, w27
	blr	x3
	ldr	x3, [x26, 88]
	mov	x2, x20
	ldr	x0, [x25]
	mov	w1, w27
	blr	x3
	ldp	w7, w0, [x29, 168]
	str	w0, [sp]
	mov	w6, w23
	ldr	x1, .LC10
	mov	w5, w21
	ldr	x0, .LC12
	mov	w4, w22
	ldr	x8, [x26, 128]
	mov	w3, w19
	mov	w2, w24
	add	x1, x1, 24
	blr	x8
.L2:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
.L60:
	ldr	x2, .LC3
	ldrh	w0, [x2,w0,uxtw #1]
	adr	x1, .Lrtx6
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx6:
	.section	.rodata
	.align	0
	.align	2
.L6:
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L5 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L4 - .Lrtx6) / 4
	.2byte	(.L7 - .Lrtx6) / 4
	.text
.L61:
	ldr	w0, [x29, 200]
	mov	w5, w19
	cmp	w0, 8
	ble	.L38
	ldr	w0, [x26, 168]
	cmp	w4, wzr
	add	w2, w4, 3
	add	w3, w19, 31
	csel	w2, w2, w4, lt
	cmp	w0, 10
	asr	w2, w2, 2
	and	w3, w3, -32
	bne	.L39
.L62:
	mul	w4, w5, w4
	mul	w2, w2, w3
	lsl	w3, w4, 2
	sub	w4, w3, w4
	asr	w4, w4, 1
	add	x4, x25, x4, sxtw
	add	x3, x4, x2, sxtw
	b	.L12
.L7:
	add	w24, w24, 7
	add	w19, w19, 7
	and	w24, w24, -8
	and	w19, w19, -8
	add	w4, w24, 255
	and	w4, w4, -256
.L8:
	ldr	w0, [x29, 200]
	add	w5, w19, 63
	and	w5, w5, -64
	cmp	w0, 8
	ble	.L38
	cmp	w4, wzr
	add	w2, w4, 3
	csel	w2, w2, w4, lt
	mov	w3, w5
	asr	w2, w2, 2
	b	.L10
.L5:
	add	w24, w24, 15
	cmp	w28, 16
	and	w24, w24, -16
	add	w19, w19, 15
	add	w4, w24, 255
	and	w19, w19, -16
	and	w4, w4, -256
	bne	.L9
	b	.L61
.L38:
	mov	w3, 0
	mov	w2, 0
	b	.L10
	.p2align 3
.L27:
	cbz	w7, .L30
	and	w4, w9, -2
	mov	w3, 2
	mov	w1, 0
	.p2align 2
.L31:
	ubfiz	x13, x1, 2, 30
	uxtw	x0, w4
	ldr	x5, [x25]
	add	w1, w1, 1
	cmp	w1, w7
	add	w4, w4, 2
	ldrh	w13, [x2, x13]
	strh	w13, [x5, x0]
	ldr	x5, [x6]
	ldrh	w13, [x2, w3, uxtw]
	add	w3, w3, 4
	strh	w13, [x5, x0]
	bne	.L31
	ldr	w0, [x29, 172]
.L30:
	add	x2, x2, x12
	b	.L32
.L64:
	ldr	x1, .LC6
	cbz	w27, .L22
	mov	w0, 0
	.p2align 2
.L23:
	ldp	x2, x3, [x29, 120]
	ubfx	x4, x0, 2, 30
	ldr	x9, [x1]
	add	w8, w0, 1
	add	w7, w0, 2
	ldrb	w2, [x2, w0, uxtw]
	add	w5, w0, 3
	ldrb	w6, [x3, x4]
	ubfiz	w3, w2, 2, 14
	and	w2, w6, 3
	add	w2, w2, w3
	strh	w2, [x9, w0, uxtw 1]
	add	w0, w0, 4
	ldp	x2, x3, [x29, 120]
	ldr	x6, [x1]
	cmp	w0, w27
	ldrb	w3, [x3, x4]
	ldrb	w2, [x2, w8, uxtw]
	ubfx	x3, x3, 2, 2
	ubfiz	w2, w2, 2, 14
	add	w2, w3, w2
	strh	w2, [x6, w8, uxtw 1]
	ldp	x2, x3, [x29, 120]
	ldr	x6, [x1]
	ldrb	w3, [x3, x4]
	ldrb	w2, [x2, w7, uxtw]
	ubfx	x3, x3, 4, 2
	ubfiz	w2, w2, 2, 14
	add	w2, w3, w2
	strh	w2, [x6, w7, uxtw 1]
	ldp	x2, x3, [x29, 120]
	ldr	x6, [x1]
	ldrb	w2, [x2, w5, uxtw]
	ldrb	w3, [x3, x4]
	ubfiz	w2, w2, 2, 14
	add	w2, w2, w3, lsr 6
	strh	w2, [x6, w5, uxtw 1]
	bcc	.L23
	lsr	w10, w19, 1
	ldr	w0, [x29, 172]
	ldr	x2, [x1]
	cbnz	w10, .L24
	ldr	x25, .LC8
	ldr	x6, .LC9
	b	.L25
	.p2align 3
.L63:
	mul	w27, w24, w19
	ldr	x1, .LC6
	cbz	w27, .L16
	mov	w0, 0
	.p2align 2
.L17:
	ldp	x2, x3, [x29, 104]
	ubfx	x4, x0, 2, 30
	ldr	x9, [x1]
	add	w8, w0, 1
	add	w7, w0, 2
	ldrb	w2, [x2, w0, uxtw]
	add	w6, w0, 3
	ldrb	w5, [x3, x4]
	ubfiz	w3, w2, 2, 14
	and	w2, w5, 3
	add	w2, w2, w3
	strh	w2, [x9, w0, uxtw 1]
	add	w0, w0, 4
	ldp	x2, x3, [x29, 104]
	ldr	x5, [x1]
	cmp	w0, w27
	ldrb	w3, [x3, x4]
	ldrb	w2, [x2, w8, uxtw]
	ubfx	x3, x3, 2, 2
	ubfiz	w2, w2, 2, 14
	add	w2, w3, w2
	strh	w2, [x5, w8, uxtw 1]
	ldp	x2, x3, [x29, 104]
	ldr	x5, [x1]
	ldrb	w3, [x3, x4]
	ldrb	w2, [x2, w7, uxtw]
	ubfx	x3, x3, 4, 2
	ubfiz	w2, w2, 2, 14
	add	w2, w3, w2
	strh	w2, [x5, w7, uxtw 1]
	ldp	x2, x3, [x29, 104]
	ldr	x5, [x1]
	ldrb	w2, [x2, w6, uxtw]
	ldrb	w3, [x3, x4]
	ubfiz	w2, w2, 2, 14
	add	w2, w2, w3, lsr 6
	strh	w2, [x5, w6, uxtw 1]
	bcc	.L17
	ldr	w2, [x29, 172]
	ldr	x0, [x1]
	cmp	w2, 10
	bne	.L19
.L18:
	ldr	x26, .LC7
	mov	x2, x20
	lsl	w1, w27, 1
	ldr	x3, [x26, 88]
	blr	x3
	b	.L20
.L22:
	lsr	w10, w19, 1
	ldr	x2, [x1]
	cbnz	w10, .L24
	ldr	x25, .LC8
	ldr	x6, .LC9
.L36:
	lsr	w27, w27, 1
	b	.L58
.L65:
	ldr	x25, .LC8
	ldr	x6, .LC9
	b	.L26
.L16:
	ldr	x0, [x1]
	b	.L18
	.size	YUV_DumpFrame_Tile, .-YUV_DumpFrame_Tile
	.align	3
.LC3:
	.xword	.L6
	.align	3
.LC4:
	.xword	pY
	.align	3
.LC5:
	.xword	pY_2bit
	.align	3
.LC6:
	.xword	pPixelArray
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	pVl
	.align	3
.LC9:
	.xword	pUl
	.align	3
.LC10:
	.xword	.LANCHOR0
	.align	3
.LC12:
	.xword	.LC11
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	YUV_DumpImage
	.type	YUV_DumpImage, %function
YUV_DumpImage:
	sub	sp, sp, #128
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	str	x23, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC13
	stp	xzr, xzr, [x29, 64]
	stp	xzr, xzr, [x29, 80]
	ldr	x0, [x21, w22, sxtw 3]
	cbz	x0, .L68
	ldr	x20, [x19, 504]
	ldrb	w23, [x19, 64]
	cbz	x20, .L69
	ldr	x2, [x19, 512]
	cbnz	x2, .L72
.L69:
	ldr	x1, .LC14
	ldr	w0, [x19, 20]
	str	w0, [x29, 80]
	add	x0, x29, 64
	ldr	x1, [x1, 320]
	blr	x1
	mov	x20, x0
	cbz	x0, .L92
	ldp	w2, w0, [x19, 20]
	sub	w2, w0, w2
	add	x2, x20, x2
.L72:
	cmp	x20, xzr
	ccmp	x2, xzr, 4, ne
	beq	.L68
	ldr	x0, .LC17
	ldr	x1, [x0, w22, sxtw 3]
	ldr	w0, [x1, 1200]
	cbz	w0, .L74
	ldr	x2, .LC18
	mov	w0, 32
	ldr	x1, .LC19
	bl	dprint_vfmw
.L75:
	ldr	x1, .LC14
	mov	x0, x20
	ldr	x1, [x1, 328]
	blr	x1
.L68:
	ldr	x0, .LC21
	ldr	x2, [x0, w22, sxtw 3]
	cbz	x2, .L76
	ldr	x0, [x19, 432]
	cbz	x0, .L76
	ldr	w1, [x19, 420]
	cbnz	w1, .L93
.L76:
	add	sp, x29, 0
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L93:
	ldr	x3, .LC14
	ldr	x3, [x3, 88]
	blr	x3
	add	sp, x29, 0
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L74:
	ldr	w3, [x19, 168]
	tst	w23, 28
	ldr	x0, .LC20
	cset	w7, eq
	str	w3, [sp, 8]
	mov	w5, 0
	str	x19, [sp, 24]
	ldr	w0, [x0]
	ldr	w4, [x19, 72]
	ldr	w6, [x19, 112]
	str	w0, [sp, 16]
	ldr	x0, [x21, w22, sxtw 3]
	ldr	w1, [x1, 52]
	ldr	w3, [x19, 68]
	str	w1, [sp]
	mov	x1, x20
	bl	YUV_DumpFrame_Tile
	b	.L75
	.p2align 3
.L92:
	ldr	x1, .LC16
	mov	w0, 32
	bl	dprint_vfmw
	b	.L68
	.size	YUV_DumpImage, .-YUV_DumpImage
	.align	3
.LC13:
	.xword	vfmw_save_yuv_file
	.align	3
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC17:
	.xword	s_pstVfmwChan
	.align	3
.LC18:
	.xword	.LANCHOR0
	.align	3
.LC19:
	.xword	.LC1
	.align	3
.LC20:
	.xword	g_SaveYUVBitWidth
	.align	3
.LC21:
	.xword	vfmw_save_metadata_reorder_file
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11382, %object
	.size	__func__.11382, 18
__func__.11382:
	.string	"YUV_DumpFrame_Cmp"
	.zero	6
	.type	__func__.11439, %object
	.size	__func__.11439, 19
__func__.11439:
	.string	"YUV_DumpFrame_Tile"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"%s not support now.\n" )
	.zero	3
.LC11:
	ASCII(.string	"%s: Width=%d, Height=%d, Stride=%d, PicStructure=%d, ChromaIDC=%d, RealBitDepth=%d, SaveBitDepth=%d\n" )
	.zero	3
.LC15:
	ASCII(.string	" luma_vir_addr MAP return error\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
