#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"hevc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	HEVC_ComparePicByPocAsc, %function
HEVC_ComparePicByPocAsc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 8]
	ldr	w2, [x2, 8]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	HEVC_ComparePicByPocAsc, .-HEVC_ComparePicByPocAsc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.7, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.7:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 4724]
	mov	w4, 1888
	ldr	x2, [x19, 2384]
	add	x13, x19, 4096
	add	x17, x13, 1524
	ldr	x1, [x19, 2376]
	mov	w3, 12660
	ldr	w7, [x19, 5620]
	smaddl	x2, w0, w4, x2
	ldr	w4, [x17, 4]
	mov	w0, 1
	ldr	w18, [x17, 8]
	ldr	w2, [x2, 32]
	add	w7, w7, w4
	cmp	w7, w18
	mov	w15, w7
	smaddl	x1, w2, w3, x1
	ldr	w5, [x1, 116]
	lsl	w5, w0, w5
	bcs	.L5
	ldr	w3, [x19, 2796]
	mov	w9, 0
	mov	w8, 0
	.p2align 2
.L6:
	sxtw	x16, w15
	cbz	w3, .L12
	add	x12, x19, x16, lsl 2
	mov	w14, 0
	mov	w0, 0
	ldr	w4, [x12, 4776]
	b	.L9
	.p2align 3
.L47:
	ldr	x1, [x2, 2816]
	ldr	w2, [x1, 60]
	cbz	w2, .L8
	ldr	w6, [x1, 8]
	ldr	w2, [x12, 5720]
	cmp	w6, w2
	beq	.L44
.L8:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L46
.L9:
	add	x2, x19, x0, sxtw 3
	cbnz	w4, .L47
	ldr	x1, [x2, 2816]
	ldr	w2, [x1, 60]
	cbz	w2, .L8
	ldr	w11, [x1, 8]
	ldr	w10, [x12, 5720]
	sdiv	w6, w11, w5
	sdiv	w2, w10, w5
	msub	w6, w6, w5, w11
	msub	w2, w2, w5, w10
	cmp	w6, w2
	bne	.L8
.L44:
	ldrb	w1, [x1, 1]
	add	w0, w0, 1
	cmp	w1, wzr
	csinc	w14, w14, wzr, eq
	cmp	w0, w3
	bne	.L9
	.p2align 2
.L46:
	cbz	w14, .L12
.L10:
	add	w15, w15, 1
	cmp	w18, w15
	bne	.L6
	cbz	w7, .L14
.L13:
	mov	w12, 0
	add	x10, x13, 1524
	.p2align 2
.L18:
	mov	w11, 0
	mov	w0, 0
	sxtw	x5, w12
	cbnz	w3, .L36
	b	.L20
	.p2align 3
.L15:
	cmp	w0, w3
	beq	.L48
.L36:
	add	x2, x19, x0, sxtw 3
	add	x1, x5, 8
	add	w0, w0, 1
	ldr	x2, [x2, 2816]
	ldr	w4, [x2, 60]
	cbnz	w4, .L15
	ldr	w4, [x10, x1, lsl 2]
	ldr	w6, [x19, 4700]
	ldr	w1, [x2, 8]
	add	w4, w6, w4
	cmp	w1, w4
	bne	.L15
	ldrb	w1, [x2, 1]
	cmp	w1, wzr
	csinc	w11, w11, wzr, eq
	cmp	w0, w3
	bne	.L36
	.p2align 2
.L48:
	cbz	w11, .L20
.L17:
	add	w12, w12, 1
	cmp	w7, w12
	bhi	.L18
.L14:
	mov	w0, 1
	cbz	w8, .L35
	mov	w0, 0
	str	w9, [x20]
.L35:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L20:
	ldr	w1, [x19, 4720]
	sxtw	x2, w12
	add	x0, x2, 8
	ldr	w4, [x19, 4700]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x10, x0, lsl 2]
	ldr	w1, [x1, 228]
	add	w0, w4, w0
	cmp	w0, w1
	blt	.L17
	add	x2, x10, x2
	ldrb	w1, [x2, 12]
	cmp	w1, wzr
	csel	w9, w9, w0, eq
	csinc	w8, w8, wzr, eq
	b	.L17
	.p2align 3
.L12:
	ldr	w1, [x19, 4720]
	add	x2, x16, 8
	ldr	w4, [x19, 4700]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x17, x2, lsl 2]
	add	w0, w4, w0
	ldr	w1, [x1, 228]
	cmp	w0, w1
	blt	.L10
	add	x16, x17, x16
	ldrb	w1, [x16, 12]
	cmp	w1, wzr
	csel	w9, w9, w0, eq
	csinc	w8, w8, wzr, eq
	b	.L10
.L5:
	cbz	w7, .L35
	mov	w9, 0
	mov	w8, 0
	ldr	w3, [x19, 2796]
	b	.L13
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.7, .-HEVC_CheckThatAllRefPicsAreAvailable.part.7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_SetFrmRepeatCount.part.8, %function
HEVC_SetFrmRepeatCount.part.8:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x19, 284]
	ldr	w2, [x19, 2792]
	ldr	w0, [x19, 280]
	add	w2, w3, w2
	add	w3, w2, 1
	cmp	w0, w3
	bcc	.L50
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L51
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x19, 284]
	add	w0, w0, 2
	str	w0, [x19, 284]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L50:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L51:
	mov	w0, 1
	str	w0, [x20, 16]
	ldr	w0, [x19, 284]
	add	w0, w0, 1
	str	w0, [x19, 284]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount.part.8, .-HEVC_SetFrmRepeatCount.part.8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_OutputFrame.isra.9, %function
HEVC_OutputFrame.isra.9:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 252]
	ldr	w1, [x21]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L59
	ldr	w0, [x19, 252]
	mov	w2, 1
	ldr	w1, [x21]
	bl	FSP_SetDisplay
	add	x3, x19, 4096
	ldr	w0, [x19, 252]
	mov	x4, x20
	add	x3, x3, 1952
	mov	x2, x19
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L60
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L61
	str	wzr, [x20, 16]
.L58:
	ldr	w1, [x19, 284]
	mov	w0, 0
	ldr	w2, [x19, 292]
	add	w1, w1, 1
	str	w1, [x19, 284]
	add	w2, w2, 1
	str	w2, [x19, 292]
.L55:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L61:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.8
	b	.L58
	.p2align 3
.L60:
	ldr	x2, .LC0
	mov	w0, 1
	ldr	x1, .LC4
	bl	dprint_vfmw
	ldr	w0, [x19, 252]
	mov	w2, 0
	ldr	w1, [x21]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L55
.L59:
	ldr	x2, .LC0
	mov	w0, 0
	ldr	x1, .LC2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L55
	.size	HEVC_OutputFrame.isra.9, .-HEVC_OutputFrame.isra.9
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC4:
	.xword	.LC3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_Sei_Mastering_Display_Colour_Volume.part.14, %function
HEVC_Sei_Mastering_Display_Colour_Volume.part.14:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x1, 4
	add	x22, x1, 16
	bl	_mcount
.L63:
	add	x19, x19, 4
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	str	w0, [x19, -4]
	mov	w1, 16
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x19, 8]
	cmp	x19, x22
	bne	.L63
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 28]
	mov	w1, 16
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x21, 32]
	mov	w1, 32
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x21, 36]
	mov	w1, 32
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x21, 40]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_Sei_Mastering_Display_Colour_Volume.part.14, .-HEVC_Sei_Mastering_Display_Colour_Volume.part.14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_ParsePts_Init
	.type	HEVC_Sei_ParsePts_Init, %function
HEVC_Sei_ParsePts_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC7
	add	x0, x19, 8192
	mov	x2, 56
	mov	w1, 0
	add	x0, x0, 3664
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 3364]
	add	x0, x19, 3072
	stp	xzr, xzr, [x0, 312]
	stp	xzr, xzr, [x0, 328]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_ParsePts_Init, .-HEVC_Sei_ParsePts_Init
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Dpb_Output_Time
	.type	HEVC_Sei_Get_Dpb_Output_Time, %function
HEVC_Sei_Get_Dpb_Output_Time:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldr	w2, [x19, 4724]
	mov	w5, 1888
	ldr	x1, [x19, 2384]
	add	x3, x19, 8192
	add	x4, x3, 3664
	ldr	x0, [x19, 2376]
	ldr	w6, [x20, 36]
	smaddl	x1, w2, w5, x1
	ldr	w2, [x4, 4]
	mov	w5, 12660
	ldr	w1, [x1, 32]
	cmp	w2, 1
	str	w6, [x4, 12]
	smaddl	x0, w1, w5, x0
	ldr	w2, [x20, 40]
	str	w2, [x4, 16]
	ldr	w1, [x0, 52]
	add	x0, x0, x1, lsl 2
	ldrb	w2, [x0, 360]
	beq	.L74
	ldrb	w0, [x4, 1]
	cbnz	w0, .L75
	add	x4, x19, 3368
	ldr	w0, [x4, 8]
	ldr	x1, [x4, 16]
	add	x0, x0, x1
	str	x0, [x4, 40]
.L68:
	add	x3, x3, 3664
	str	x0, [x4, 32]
	ldr	x1, [x3, 32]
	strb	wzr, [x3, 1]
	str	x1, [x3, 48]
	ldrb	w1, [x20, 2]
	cbnz	w1, .L76
.L72:
	ldr	w1, [x4, 12]
	add	x0, x1, x0
	sub	x0, x0, x2, uxtb
	str	x0, [x3, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L75:
	ldrb	w0, [x19, 3360]
	add	x4, x19, 3368
	cbnz	w0, .L77
	ldp	x1, x5, [x4, 16]
.L71:
	ldr	w6, [x4, 8]
	add	x0, x6, x1
	str	x0, [x4, 16]
	cmp	x0, x5
	str	x0, [x4, 40]
	bge	.L68
	add	x3, x3, 3664
	add	x0, x6, x5
	str	x0, [x4, 16]
	str	x0, [x4, 40]
	str	x0, [x4, 32]
	strb	wzr, [x3, 1]
	ldr	x1, [x3, 32]
	str	x1, [x3, 48]
	ldrb	w1, [x20, 2]
	cbz	w1, .L72
.L76:
	ldr	w1, [x4, 12]
	add	x1, x1, x0
	asr	x1, x1, 1
	sub	x0, x1, x2, uxtb
	str	x0, [x3, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L74:
	add	x4, x19, 3368
	ldrsw	x0, [x19, 3364]
	str	x0, [x4, 16]
	str	x0, [x4, 40]
	b	.L68
	.p2align 3
.L77:
	ldr	x5, [x4, 24]
	mov	x1, x5
	b	.L71
	.size	HEVC_Sei_Get_Dpb_Output_Time, .-HEVC_Sei_Get_Dpb_Output_Time
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Get_Last_IDR_Frame_Info
	.type	HEVC_Get_Last_IDR_Frame_Info, %function
HEVC_Get_Last_IDR_Frame_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	sub	w0, w19, #19
	cmp	w0, 1
	bls	.L85
.L79:
	sub	w19, w19, #6
	cmp	w19, 3
	bls	.L78
	ldr	x0, [x20, 3408]
	str	x0, [x20, 3392]
.L78:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	ldr	x0, [x20, 2456]
	ldr	x0, [x0, 56]
	cmn	x0, #1
	beq	.L80
	ldr	x1, [x20, 11888]
	str	x0, [x20, 11880]
	str	x1, [x20, 11896]
.L80:
	add	x0, x20, 8192
	mov	w1, 1
	strb	w1, [x0, 3664]
	b	.L79
	.size	HEVC_Get_Last_IDR_Frame_Info, .-HEVC_Get_Last_IDR_Frame_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Frame_Pts
	.type	HEVC_Sei_Get_Frame_Pts, %function
HEVC_Sei_Get_Frame_Pts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 11868]
	ldr	w5, [x19, 11872]
	ldr	x6, [x19, 11880]
	ldr	x3, [x19, 11888]
	ldr	x7, [x19, 11896]
	cbz	w4, .L89
	mov	w1, w4
	mov	w2, w5
	b	.L88
	.p2align 3
.L90:
	mov	w1, w0
.L88:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L90
.L87:
	udiv	w4, w4, w1
	sub	x0, x3, x7
	lsl	w2, w0, 6
	sub	w2, w2, w0
	lsl	w2, w2, 1
	sub	w0, w2, w0
	lsl	w0, w0, 3
	udiv	w1, w5, w1
	mul	w0, w0, w4
	udiv	w1, w0, w1
	add	x1, x1, x6
	str	x1, [x19, 4640]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L89:
	mov	w1, w5
	b	.L87
	.size	HEVC_Sei_Get_Frame_Pts, .-HEVC_Sei_Get_Frame_Pts
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w5
	mov	x20, x4
	bl	_mcount
	cmp	w21, 15
	bgt	.L92
	cmp	w21, 8
	mul	w10, w21, w21
	beq	.L127
	mov	x8, x20
	cbz	w10, .L92
.L98:
	mov	w7, 1
	mov	w1, 0
	mov	w9, 0
	sub	w7, w7, w21
.L102:
	cmp	w21, w9
	mov	w0, w9
	mov	w2, 0
	bgt	.L104
	.p2align 2
.L118:
	sub	w0, w0, #1
	add	w2, w2, 1
	cmp	w21, w0
	ble	.L118
.L104:
	cmp	w0, wzr
	ccmp	w21, w2, 4, ge
	ble	.L100
	madd	w3, w21, w0, w2
	sub	w2, w2, w1
	.p2align 2
.L101:
	str	w3, [x8, w1, uxtw 2]
	sub	w0, w0, #1
	add	w1, w1, 1
	cmp	w0, wzr
	add	w6, w2, w1
	add	w3, w3, w7
	ccmp	w21, w6, 4, ge
	bgt	.L101
.L100:
	cmp	w10, w1
	add	w9, w9, 1
	bhi	.L102
.L92:
	cmp	w21, 4
	ble	.L91
	asr	w14, w21, 2
	add	x0, x19, x14, uxtw
	mul	w16, w14, w14
	ldrsb	w0, [x0, 12]
	add	w0, w0, 1
	cbz	w16, .L91
.L96:
	ldr	x15, .LC9
	sbfiz	x0, x0, 16, 32
	mov	w9, 1
	add	x13, x19, 340
	add	x15, x15, x0
	mov	x12, 0
	sub	w9, w9, w21
.L113:
	cmp	w21, 32
	ldr	w3, [x15, x12, lsl 2]
	beq	.L128
.L106:
	udiv	w2, w3, w14
	lsl	w8, w12, 4
	mov	w10, 0
	mov	w0, 0
	mov	w7, 0
	mov	w1, 0
	madd	w3, w2, w21, w3
	msub	w2, w2, w14, w3
	lsl	w11, w2, 2
	.p2align 2
.L107:
	cmp	w1, wzr
	ccmp	w7, 3, 0, ge
	bgt	.L108
	madd	w2, w21, w1, w7
	sub	w7, w7, w0
	add	w2, w2, w11
	.p2align 2
.L109:
	add	w6, w0, w8
	sub	w1, w1, #1
	add	w0, w0, 1
	cmp	w1, wzr
	add	w3, w7, w0
	str	w2, [x20, w6, uxtw 2]
	ccmp	w3, 3, 0, ge
	add	w2, w2, w9
	ble	.L109
.L108:
	cmp	w0, 15
	add	w10, w10, 1
	bhi	.L110
	cmp	w10, 3
	ble	.L129
	sub	w7, w10, #3
	mov	w1, 3
	b	.L107
.L110:
	add	x12, x12, 1
	add	x13, x13, 4
	cmp	w16, w12
	bhi	.L113
.L91:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L128:
	ldr	w3, [x13]
	b	.L106
.L127:
	add	x8, x19, 340
	cbnz	w10, .L98
	ldrsb	w0, [x19, 14]
	mov	w14, 2
	mov	w16, 4
	add	w0, w0, 1
	b	.L96
.L129:
	mov	w1, w10
	mov	w7, 0
	b	.L107
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	3
.LC9:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x22, 12
	add	x2, x22, 141
	mov	w1, -1
	.p2align 2
.L131:
	strb	w1, [x0], 1
	cmp	x2, x0
	bne	.L131
	ldr	x21, .LC12
	mov	w3, 1
	mov	w2, 2
	mov	w1, 3
	mov	w0, 4
	strb	wzr, [x22, 16]
	strb	w3, [x22, 20]
	mov	w20, 2
	strb	w2, [x22, 28]
	mov	w19, 0
	strb	w1, [x22, 44]
	strb	w0, [x22, 76]
	.p2align 2
.L132:
	mov	w7, w19
	mov	w6, w20
	mov	w5, w20
	mov	x4, x21
	mov	x3, 0
	mov	x2, 0
	mov	x1, 0
	mov	x0, x22
	add	w19, w19, 1
	lsl	w20, w20, 1
	bl	HEVC_InitSigLastScan
	add	x21, x21, 65536
	cmp	w19, 7
	bne	.L132
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.align	3
.LC12:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetDar
	.type	HEVC_GetDar, %function
HEVC_GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w23, w2
	mov	w22, w3
	mov	w24, w4
	mov	w20, 0
	bl	_mcount
	cbz	w19, .L136
	mov	w0, 255
	cmp	w19, 16
	ccmp	w19, w0, 4, gt
	bne	.L136
	cmp	w21, wzr
	ccmp	w23, wzr, 4, ne
	ccmp	w19, w0, 0, eq
	beq	.L136
	cmp	w19, 1
	mov	w20, 5
	beq	.L136
	cmp	w19, w0
	beq	.L137
	ldr	x0, .LC13
	sbfiz	x19, x19, 3, 32
	add	x0, x0, 24
	add	x1, x0, x19
	ldr	w21, [x0, x19]
	ldr	w23, [x1, 4]
.L137:
	lsl	w4, w21, 10
	lsl	w22, w22, 10
	sdiv	w2, w4, w23
	sdiv	w4, w22, w24
	mul	w4, w2, w4
	cmp	w4, wzr
	add	w0, w4, 1023
	csel	w4, w0, w4, lt
	asr	w4, w4, 10
	subs	w1, w4, #2406
	bmi	.L159
.L138:
	subs	w0, w4, #2263
	bmi	.L160
	cmp	w1, w0
	mov	w20, 4
	bge	.L142
.L136:
	ldr	x1, .LC15
	mov	w2, w20
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L160:
	mov	w0, 2263
	mov	w20, 4
	sub	w0, w0, w4
	cmp	w1, w0
	blt	.L136
.L142:
	subs	w1, w4, #1820
	bmi	.L161
	cmp	w0, w1
	mov	w20, 3
	blt	.L136
.L143:
	subs	w0, w4, #1365
	bmi	.L162
.L141:
	mov	w20, 2
	cmp	w1, w0
	csinc	w20, w20, wzr, lt
	b	.L136
	.p2align 3
.L159:
	mov	w1, 2406
	sub	w1, w1, w4
	b	.L138
	.p2align 3
.L161:
	mov	w1, 1820
	mov	w20, 3
	sub	w1, w1, w4
	cmp	w0, w1
	blt	.L136
	b	.L143
.L162:
	mov	w0, 1365
	sub	w0, w0, w4
	b	.L141
	.size	HEVC_GetDar, .-HEVC_GetDar
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC15:
	.xword	.LC14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC18
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, .LC20
	ldr	w0, [x24, 168]
	cmn	w0, #1
	beq	.L167
	mov	w20, 52429
	ldr	x22, .LC24
	mov	w19, 0
	mov	w21, 104
	movk	w20, 0xcccc, lsl 16
	b	.L166
	.p2align 3
.L165:
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bls	.L167
.L166:
	umull	x0, w19, w21
	ldr	x4, [x24, 2448]
	mov	w2, w19
	mov	x1, x22
	add	x4, x4, x0
	mov	w0, 1
	mov	x3, x4
	ldr	w4, [x4, 32]
	bl	dprint_vfmw
	umull	x0, w19, w20
	lsr	x0, x0, 32
	lsr	w0, w0, 3
	lsl	w1, w0, 3
	add	w0, w1, w0, lsl 1
	cmp	w19, w0
	add	w19, w19, 1
	bne	.L165
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bhi	.L166
.L167:
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC22
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC26
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC28
	mov	w0, 1
	ldr	w2, [x19, 4756]
	bl	dprint_vfmw
	ldr	w0, [x19, 4756]
	cbz	w0, .L178
	ldr	x24, .LC32
	mov	w20, 0
	ldr	x22, .LC37
	ldr	x23, .LC34
	ldr	x25, .LC36
	.p2align 2
.L177:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 2480]
	bl	dprint_vfmw
	ldr	x2, [x21, 2480]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L175
	ldr	x2, [x2, 16]
	bl	dprint_vfmw
	ldr	x0, [x21, 2480]
	ldr	x0, [x0, 16]
	cbz	x0, .L175
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L175:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 4756]
	cmp	w0, w20
	bhi	.L177
.L178:
	ldr	x1, .LC30
	mov	w0, 1
	ldr	w2, [x19, 4760]
	bl	dprint_vfmw
	ldr	w0, [x19, 4760]
	cbz	w0, .L173
	ldr	x22, .LC37
	mov	w20, 0
	ldr	x24, .LC41
	ldr	x23, .LC34
	ldr	x25, .LC36
	.p2align 2
.L182:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 2616]
	bl	dprint_vfmw
	ldr	x2, [x21, 2616]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L180
	ldr	x2, [x2, 16]
	bl	dprint_vfmw
	ldr	x0, [x21, 2616]
	ldr	x0, [x0, 16]
	cbz	x0, .L180
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L180:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 4760]
	cmp	w0, w20
	bhi	.L182
.L173:
	ldr	x1, .LC39
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC28:
	.xword	.LC27
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC37:
	.xword	.LC19
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC45
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 180]
	cbz	w0, .L196
	ldr	x26, .LC49
	mov	w20, 0
	ldr	x22, .LC51
	mov	w24, 712
	ldr	x25, .LC52
	mov	x23, 14096
	.p2align 2
.L195:
	uxtw	x5, w20
	mov	w2, w20
	lsl	x3, x5, 2
	mov	x1, x26
	sub	x3, x3, x5
	mov	w0, 1
	lsl	x4, x3, 4
	mov	w19, 0
	sub	x3, x4, x3
	lsl	x3, x3, 1
	sub	x3, x3, x5
	lsl	x3, x3, 3
	add	x4, x21, x3
	add	x3, x3, 12288
	add	x5, x4, 12288
	add	x3, x3, 1184
	umaddl	x27, w20, w24, x23
	ldr	w4, [x4, 13520]
	add	x3, x21, x3
	ldrb	w6, [x5, 1186]
	add	x27, x21, x27
	ldrb	w5, [x5, 1185]
	bl	dprint_vfmw
.L194:
	ldr	x3, [x27], 8
	mov	w2, w19
	mov	w0, 1
	mov	x1, x22
	add	w19, w19, w0
	bl	dprint_vfmw
	cmp	w19, 4
	bne	.L194
	mov	w0, 1
	mov	x1, x25
	add	w20, w20, w0
	bl	dprint_vfmw
	ldr	w0, [x21, 180]
	cmp	w0, w20
	bhi	.L195
.L196:
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC52:
	.xword	.LC19
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	mov	w20, 0
	bl	_mcount
	ldr	x1, .LC54
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w4, [x19, 984]
	mov	w2, 0
	ldr	w3, [x19, 988]
	mov	w0, 1
	ldr	x1, .LC56
	add	x19, x19, 992
	bl	dprint_vfmw
	ldr	x21, .LC58
	.p2align 2
.L201:
	ldr	w4, [x19, 64]
	mov	w2, w20
	ldr	w5, [x19, 128]
	mov	w0, 1
	ldr	w3, [x19], 4
	mov	x1, x21
	add	w20, w20, w0
	bl	dprint_vfmw
	cmp	w20, 16
	bne	.L201
	ldr	x1, .LC60
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
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
.LC60:
	.xword	.LC59
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
	sub	sp, sp, #176
	stp	x29, x30, [sp, 64]
	add	x29, sp, 64
	stp	x19, x20, [sp, 80]
	stp	x21, x22, [sp, 96]
	stp	x23, x24, [sp, 112]
	stp	x25, x26, [sp, 128]
	stp	x27, x28, [sp, 144]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x1, .LC62
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC64
	mov	w0, 1
	ldr	w2, [x19, 2792]
	ldr	w3, [x19, 2796]
	ldr	w6, [x19, 2804]
	ldr	w4, [x19, 2808]
	ldr	w5, [x19, 2812]
	bl	dprint_vfmw
	ldr	w0, [x19, 2796]
	cbz	w0, .L208
	.p2align 2
.L207:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 252]
	ldr	x2, [x21, 2816]
	ldrb	w7, [x2, 1]
	ldp	w1, w28, [x2, 28]
	ldr	w6, [x2, 48]
	ldrb	w25, [x2]
	ldrb	w22, [x2, 2]
	ldr	w23, [x2, 8]
	ldr	w24, [x2, 60]
	stp	w6, w7, [x29, 104]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	x1, [x21, 2816]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetRef
	mov	w27, w0
	ldr	x1, [x21, 2816]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDisplay
	ldr	x8, [x21, 2816]
	mov	w2, w20
	ldp	w6, w7, [x29, 104]
	mov	x3, x8
	mov	w5, w25
	ldr	w1, [x8, 228]
	mov	w4, w28
	str	w1, [sp, 56]
	add	w20, w20, 1
	ldr	x1, .LC67
	ldr	w8, [x8, 28]
	str	w8, [sp, 48]
	str	w0, [sp, 40]
	mov	w0, 1
	str	w22, [sp]
	str	w23, [sp, 8]
	str	w24, [sp, 16]
	str	x26, [sp, 24]
	str	w27, [sp, 32]
	bl	dprint_vfmw
	ldr	w0, [x19, 2796]
	cmp	w0, w20
	bhi	.L207
.L208:
	ldr	x24, .LC65
	mov	w0, 1
	mov	x1, x24
	bl	dprint_vfmw
	ldr	w0, [x19, 2796]
	cbz	w0, .L206
	ldr	x26, .LC71
	mov	w21, 0
	ldr	x28, .LC73
	ldr	x27, .LC75
	ldr	x25, .LC83
	b	.L215
	.p2align 3
.L219:
	mov	x2, x20
	mov	x1, x28
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x20, 20]
	mov	x1, x27
	mov	w0, 1
	bl	dprint_vfmw
	ldrsb	w2, [x20]
	mov	w0, 1
	ldr	x1, .LC77
	bl	dprint_vfmw
	ldrsb	w2, [x20, 1]
	mov	w0, 1
	ldr	x1, .LC79
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbz	x23, .L211
.L220:
	bl	dprint_vfmw
	ldr	w2, [x23, 72]
	mov	w0, 1
	ldr	x1, .LC85
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbz	x22, .L213
.L221:
	ldr	x1, .LC89
	bl	dprint_vfmw
	ldr	x1, .LC91
	mov	w0, 1
	ldr	w2, [x22, 72]
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 2796]
	cmp	w0, w21
	bls	.L206
.L215:
	add	x22, x19, x21, uxtw 3
	ldr	w0, [x19, 252]
	ldr	x1, [x22, 2816]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	x1, [x22, 2816]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDecPhyFs
	mov	x23, x0
	ldr	x1, [x22, 2816]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	mov	x22, x0
	mov	w2, w21
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
	cbnz	x20, .L219
	ldr	x1, .LC81
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbnz	x23, .L220
	.p2align 2
.L211:
	ldr	x1, .LC87
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbnz	x22, .L221
	.p2align 2
.L213:
	ldr	x1, .LC93
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 2796]
	cmp	w0, w21
	bhi	.L215
.L206:
	ldr	x1, .LC69
	mov	w0, 1
	bl	dprint_vfmw
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC65:
	.xword	.LC19
	.align	3
.LC67:
	.xword	.LC66
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
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 9
	mov	w0, 1
	bls	.L223
	sub	w19, w19, #16
	cmp	w19, 5
	cset	w0, ls
.L223:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 5
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ands	w19, w19, -7
	mov	w0, 1
	beq	.L227
	cmp	w19, 8
	cset	w0, eq
.L227:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 4
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4000]
	cbnz	w0, .L232
	ldr	x1, [x19, 2456]
	mov	x2, 4294967296
	ldr	x3, [x1, 688]
	cmp	x3, x2
	beq	.L235
.L231:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L232:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L235:
	ldr	w2, [x1, 696]
	cbnz	w2, .L231
	ldr	w0, [x1, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	cset	w0, hi
	b	.L231
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsEosNal
	.type	HEVC_IsEosNal, %function
HEVC_IsEosNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsEosNal, .-HEVC_IsEosNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	mov	x21, x3
	bl	_mcount
	ldr	x0, [x22, 2432]
	ldr	x1, [x22, 2424]
	ldp	w23, w26, [x0, 68]
	ldr	w25, [x1, 128]
	sub	w0, w23, #1
	cmp	w0, 9
	bhi	.L265
	sub	w0, w26, #1
	cmp	w0, 10
	bhi	.L266
	ldr	x24, .LC99
	mov	x2, 512
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x24, 96]
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x20
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x21
	blr	x3
	cmp	w23, wzr
	ble	.L246
	sub	w7, w25, #4
	mov	x2, x20
	mov	w1, 0
	mov	w6, 0
.L245:
	str	w1, [x2]
	lsl	w3, w1, w7
	ldr	x0, [x22, 2432]
	add	x0, x0, x6, sxtw 1
	ldrsh	w5, [x0, 172]
	add	w5, w5, w1
	lsl	w1, w5, w7
	sub	w0, w5, #1
	cmp	w3, w1
	str	w0, [x2, 4]
	bge	.L251
	cmp	w3, 255
	bhi	.L247
	uxtb	w4, w6
	b	.L249
	.p2align 3
.L250:
	cmp	w3, 255
	bhi	.L247
.L249:
	strb	w4, [x19, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w1
	blt	.L250
.L251:
	add	w6, w6, 1
	add	x2, x2, 8
	cmp	w23, w6
	mov	w1, w5
	bne	.L245
.L246:
	cmp	w26, wzr
	ble	.L243
	sub	w25, w25, #4
	mov	w0, 0
	mov	w5, 0
.L253:
	str	w0, [x21]
	lsl	w3, w0, w25
	ldr	x1, [x22, 2432]
	add	x1, x1, x5, sxtw 1
	ldrsh	w4, [x1, 212]
	add	w4, w4, w0
	lsl	w0, w4, w25
	sub	w1, w4, #1
	cmp	w3, w0
	str	w1, [x21, 4]
	bge	.L258
	cmp	w3, 255
	bhi	.L254
	uxtb	w2, w5
	add	x1, x19, 256
	b	.L256
	.p2align 3
.L257:
	cmp	w3, 255
	bhi	.L254
.L256:
	strb	w2, [x1, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w0
	blt	.L257
.L258:
	add	w5, w5, 1
	add	x21, x21, 8
	cmp	w26, w5
	mov	w0, w4
	bne	.L253
.L243:
	mov	w0, 0
	b	.L239
	.p2align 3
.L247:
	ldr	x2, .LC94
	mov	w0, 1
	ldr	x1, .LC101
	add	x2, x2, 160
	bl	dprint_vfmw
	mov	w0, -1
.L239:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L254:
	ldr	x2, .LC94
	mov	w0, 1
	ldr	x1, .LC103
	add	x2, x2, 160
	bl	dprint_vfmw
	mov	w0, -1
	b	.L239
.L266:
	ldr	x2, .LC94
	mov	w4, 11
	ldr	x1, .LC98
	mov	w3, w26
	add	x2, x2, 160
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L239
.L265:
	ldr	x2, .LC94
	mov	w4, 10
	ldr	x1, .LC96
	mov	w3, w23
	add	x2, x2, 160
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L239
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	3
.LC94:
	.xword	.LANCHOR0
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC98:
	.xword	.LC97
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC103:
	.xword	.LC102
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x1, [x19, 2360]
	mov	x0, x1
	ldp	w2, w19, [x1, 32]
	sub	w19, w2, w19
	bl	BsIsByteAligned
	cmp	w20, w19
	ccmp	w0, wzr, 4, ne
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x3, .LC104
	mov	x2, 40
	ldr	x1, [x19, 2360]
	add	x0, x29, x2
	ldr	x3, [x3, 104]
	blr	x3
	ldp	w0, w1, [x29, 72]
	sub	w0, w0, w1
	mov	w1, 0
	cmp	w0, w20
	bcc	.L275
.L269:
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L275:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	mov	w1, 1
	cbz	w0, .L269
	add	x0, x29, 40
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
	b	.L270
	.p2align 3
.L271:
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
.L270:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	cmp	w19, w20
	mov	w1, 1
	cset	w2, cc
	cmp	w0, wzr
	cset	w3, eq
	add	x0, x29, 40
	tst	w2, w3
	bne	.L271
	mov	w1, w2
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	3
.LC104:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L284
	ldr	x0, [x20, 2360]
	mov	w1, 8
	mov	w21, 3
	bl	BsGet
	mov	w22, w0
.L283:
	cbnz	w22, .L278
	mov	w19, 16
	.p2align 2
.L279:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L279
.L280:
	subs	w21, w21, #1
	bne	.L283
.L288:
	mov	w0, 0
.L277:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L278:
	cmp	w22, 1
	beq	.L287
	cmp	w22, 2
	bne	.L280
	ldr	x0, [x20, 2360]
	mov	w1, 32
	bl	BsGet
	subs	w21, w21, #1
	bne	.L283
	b	.L288
.L287:
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	subs	w21, w21, #1
	bne	.L283
	b	.L288
.L284:
	mov	w0, -1
	b	.L277
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L291
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	mov	w0, 0
.L290:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L291:
	mov	w0, -1
	b	.L290
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Mastering_Display_Colour_Volume
	.type	HEVC_Sei_Mastering_Display_Colour_Volume, %function
HEVC_Sei_Mastering_Display_Colour_Volume:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L294
	mov	w0, 1
	mov	x1, x19
	strb	w0, [x19]
	mov	x0, x20
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.14
.L293:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L294:
	mov	w0, -1
	b	.L293
	.size	HEVC_Sei_Mastering_Display_Colour_Volume, .-HEVC_Sei_Mastering_Display_Colour_Volume
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Content_Light_Level_Information
	.type	HEVC_Sei_Content_Light_Level_Information, %function
HEVC_Sei_Content_Light_Level_Information:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L297
	mov	w0, 1
	strb	w0, [x19]
	mov	w1, 16
	ldr	x0, [x20, 2360]
	bl	BsGet
	strh	w0, [x19, 2]
	mov	w1, 16
	ldr	x0, [x20, 2360]
	bl	BsGet
	strh	w0, [x19, 4]
	mov	w1, 0
.L296:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L297:
	mov	w1, -1
	b	.L296
	.size	HEVC_Sei_Content_Light_Level_Information, .-HEVC_Sei_Content_Light_Level_Information
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_HLGHDR_Comapitibility_Info
	.type	HEVC_Sei_HLGHDR_Comapitibility_Info, %function
HEVC_Sei_HLGHDR_Comapitibility_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L300
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x19]
	mov	w1, 0
.L299:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L300:
	mov	w1, -1
	b	.L299
	.size	HEVC_Sei_HLGHDR_Comapitibility_Info, .-HEVC_Sei_HLGHDR_Comapitibility_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L303
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L302:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L303:
	mov	w0, -1
	b	.L302
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L307
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L308
.L306:
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L305:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L308:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	b	.L306
	.p2align 3
.L307:
	mov	w0, -1
	b	.L305
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_TSI
	.type	HEVC_Sei_TSI, %function
HEVC_Sei_TSI:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L311
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 4
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
.L310:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L311:
	mov	w0, -1
	b	.L310
	.size	HEVC_Sei_TSI, .-HEVC_Sei_TSI
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	w19, 16
	bl	_mcount
	cmp	w21, 15
	bls	.L323
	.p2align 2
.L320:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L320
	subs	w21, w21, #16
	mov	w19, 0
	beq	.L317
	.p2align 2
.L319:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L319
.L317:
	mov	w0, 0
.L314:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L323:
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L314
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	3
.LC106:
	.xword	.LC105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 4756]
	cbnz	w3, .L365
.L325:
	mov	w0, 0
.L363:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L365:
	ldr	x0, [x19, 2480]
	cbz	x0, .L347
	ldr	x0, [x0, 16]
	mov	w20, 0
	cbnz	x0, .L331
	b	.L327
	.p2align 3
.L367:
	ldr	x1, [x0, 32]
	cbz	x1, .L332
	ldr	w3, [x19, 4756]
	add	w20, w20, 1
	cmp	w3, w20
	add	x0, x19, x20, sxtw 3
	bls	.L366
	ldr	x0, [x0, 2480]
	cbz	x0, .L326
	ldr	x0, [x0, 16]
	cbz	x0, .L327
.L331:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetLogicFs
	cbnz	x0, .L367
.L332:
	add	x19, x19, x20, sxtw 3
	ldr	x1, .LC112
	mov	x4, x0
	mov	w2, w20
	mov	w0, 1
	ldr	x3, [x19, 2480]
	ldr	x3, [x3, 16]
	bl	dprint_vfmw
	mov	w0, -1
.L371:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L366:
	cbz	w3, .L325
	ldr	w0, [x19, 4760]
	cbz	w0, .L325
	ldr	x0, [x19, 2616]
	cbz	x0, .L349
	ldr	x0, [x0, 16]
	mov	w20, 0
	cbnz	x0, .L342
	b	.L339
	.p2align 3
.L370:
	ldr	x1, [x0, 32]
	cbz	x1, .L343
	ldr	w0, [x19, 4760]
	add	w20, w20, 1
	cmp	w0, w20
	add	x1, x19, x20, sxtw 3
	bls	.L325
	ldr	x0, [x1, 2616]
	cbz	x0, .L368
	ldr	x0, [x0, 16]
	cbz	x0, .L369
.L342:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetLogicFs
	cbnz	x0, .L370
.L343:
	ldr	x1, .LC118
	mov	x3, x0
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L363
.L347:
	mov	w20, 0
	.p2align 2
.L326:
	ldr	x1, .LC108
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L371
	.p2align 3
.L327:
	ldr	x1, .LC110
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L371
.L369:
	ldr	w3, [x19, 4756]
.L339:
	ldr	x1, .LC116
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L363
.L368:
	ldr	w3, [x19, 4756]
.L338:
	ldr	x1, .LC114
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L363
.L349:
	mov	w20, 0
	b	.L338
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, -1
	bl	_mcount
	str	w21, [x20]
	ldr	w3, [x19, 2796]
	cmp	w3, 16
	bhi	.L373
	mov	w4, 2147483647
	mov	w0, 0
	cbz	w3, .L378
	.p2align 2
.L381:
	add	x2, x19, x0, uxtw 3
	ldr	x2, [x2, 2816]
	ldr	w5, [x2, 8]
	cmp	w5, w4
	bge	.L376
	ldr	w2, [x2]
	tst	w2, 16776960
	bne	.L376
	str	w0, [x20]
	mov	w4, w5
	ldr	w3, [x19, 2796]
.L376:
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L381
	ldr	w3, [x20]
	cmn	w3, #1
	beq	.L378
	ldr	x2, .LC119
	mov	w0, 1
	ldr	x1, .LC125
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, 0
.L375:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L378:
	ldr	x2, .LC119
	mov	w0, 1
	ldr	x1, .LC121
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, -1
	b	.L375
.L373:
	ldr	x2, .LC119
	mov	w0, 1
	ldr	x1, .LC123
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, w21
	b	.L375
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC125:
	.xword	.LC124
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x20, 2792]
	cmp	w3, 16
	bhi	.L388
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	mov	w19, w0
	ldr	w2, [x20, 252]
	ldr	w0, [x20, 4004]
	ldr	w1, [x20, 4008]
	bl	FSP_GetOccupiedNum
	subs	w0, w19, w0
	csel	w0, w0, wzr, pl
	ldr	x2, .LC126
	cmp	w0, wzr
	ble	.L387
	ldr	w3, [x20, 2792]
	add	w3, w3, 1
	cmp	w3, w0
	bhi	.L387
	ldr	x1, .LC130
	add	x2, x2, 216
	mov	w0, 13
	str	w3, [x20, 2792]
	bl	dprint_vfmw
	mov	w0, 0
.L386:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L387:
	ldr	x1, .LC132
	mov	w3, w0
	add	x2, x2, 216
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L386
	.p2align 3
.L388:
	ldr	x2, .LC126
	mov	w4, 17
	ldr	x1, .LC128
	mov	w0, 1
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, 17
	mov	w0, -1
	str	w1, [x20, 2792]
	b	.L386
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	3
.LC126:
	.xword	.LANCHOR0
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4716]
	sub	w1, w0, #16
	cmp	w1, 5
	bhi	.L390
	str	w0, [x19, 3988]
	str	wzr, [x19, 4000]
.L389:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L390:
	ldr	w0, [x19, 3988]
	sub	w0, w0, #16
	cmp	w0, 5
	bls	.L389
	ldr	w0, [x19, 4708]
	cmp	w0, 1
	beq	.L392
	cmp	w0, 2
	beq	.L393
	cbnz	w0, .L389
	mov	w0, 2
	str	w0, [x19, 4000]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L392:
	ldr	w1, [x19, 4000]
	cmp	w1, 2
	beq	.L389
	str	w0, [x19, 4000]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L393:
	ldr	w0, [x19, 4000]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L389
	str	wzr, [x19, 4000]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 4716]
	cmp	w1, 15
	bhi	.L399
	mov	w0, 1
	tbnz	x1, 0, .L400
.L399:
	sub	w1, w1, #16
	cmp	w1, 7
	cset	w0, ls
.L400:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	ubfiz	x20, x20, 6, 32
	bl	_mcount
	add	x1, x21, x20
	ldrb	w4, [x1, 600]
	ldr	w3, [x1, 608]
	ldr	w2, [x1, 604]
	ldrb	w0, [x1, 596]
	ubfiz	w2, w2, 8, 8
	orr	w2, w2, w4, lsl 16
	orr	w0, w0, w3, lsl 24
	orr	w0, w2, w0
	str	w0, [x19]
	ldrb	w4, [x1, 609]
	ldrb	w2, [x1, 601]
	ldr	w3, [x1, 604]
	ldrb	w0, [x1, 597]
	lsl	w2, w2, 16
	and	w3, w3, 65280
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 4]
	ldrb	w4, [x1, 610]
	ldrb	w2, [x1, 606]
	ldr	w3, [x1, 600]
	ldrb	w0, [x1, 598]
	lsl	w2, w2, 8
	and	w3, w3, 16711680
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 8]
	ldrb	w3, [x1, 603]
	ldrb	w2, [x1, 607]
	ldr	w0, [x1, 608]
	ldrb	w1, [x1, 599]
	lsl	w2, w2, 8
	and	w0, w0, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 18
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1764]
	ldr	w3, [x0, 1772]
	ldr	w4, [x0, 1756]
	ldrb	w2, [x1, 596]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1796]
	ldr	w3, [x0, 1804]
	ldr	w4, [x0, 1788]
	ldrb	w2, [x0, 1780]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1773]
	ldrb	w4, [x0, 1765]
	ldr	w3, [x0, 1756]
	ldrb	w2, [x1, 597]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1805]
	ldrb	w4, [x0, 1797]
	ldr	w3, [x0, 1788]
	ldrb	w2, [x0, 1781]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1774]
	ldrb	w4, [x0, 1758]
	ldr	w3, [x0, 1764]
	ldrb	w2, [x1, 598]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1806]
	ldrb	w4, [x0, 1790]
	ldr	w3, [x0, 1796]
	ldrb	w2, [x0, 1782]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1767]
	ldrb	w3, [x0, 1759]
	ldr	w5, [x0, 1772]
	ldrb	w2, [x1, 599]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1799]
	ldrb	w3, [x0, 1791]
	ldr	w1, [x0, 1804]
	ldrb	w2, [x0, 1783]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1768]
	ldr	w2, [x0, 1776]
	ldr	w3, [x0, 1760]
	ldrb	w1, [x0, 1752]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1800]
	ldr	w2, [x0, 1808]
	ldr	w3, [x0, 1792]
	ldrb	w1, [x0, 1784]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1777]
	ldrb	w3, [x0, 1769]
	ldr	w2, [x0, 1760]
	ldrb	w1, [x0, 1753]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1809]
	ldrb	w3, [x0, 1801]
	ldr	w2, [x0, 1792]
	ldrb	w1, [x0, 1785]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1778]
	ldrb	w3, [x0, 1762]
	ldr	w2, [x0, 1768]
	ldrb	w1, [x0, 1754]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1810]
	ldrb	w3, [x0, 1794]
	ldr	w2, [x0, 1800]
	ldrb	w1, [x0, 1786]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1771]
	ldrb	w3, [x0, 1763]
	ldr	w1, [x0, 1776]
	ldrb	w2, [x0, 1755]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1803]
	ldrb	w2, [x0, 1795]
	ldr	w4, [x0, 1808]
	ldrb	w1, [x0, 1787]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 6
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1012]
	ldr	w3, [x0, 1028]
	ldr	w4, [x0, 996]
	ldrb	w2, [x1, 596]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1020]
	ldr	w3, [x0, 1036]
	ldr	w4, [x0, 1004]
	ldrb	w2, [x0, 988]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1029]
	ldrb	w4, [x0, 1013]
	ldr	w3, [x0, 996]
	ldrb	w2, [x1, 597]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1037]
	ldrb	w4, [x0, 1021]
	ldr	w3, [x0, 1004]
	ldrb	w2, [x0, 989]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1030]
	ldrb	w4, [x0, 998]
	ldr	w3, [x0, 1012]
	ldrb	w2, [x1, 598]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1038]
	ldrb	w4, [x0, 1006]
	ldr	w3, [x0, 1020]
	ldrb	w2, [x0, 990]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1015]
	ldrb	w3, [x0, 999]
	ldr	w5, [x0, 1028]
	ldrb	w2, [x1, 599]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1023]
	ldrb	w3, [x0, 1007]
	ldr	w1, [x0, 1036]
	ldrb	w2, [x0, 991]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1016]
	ldr	w2, [x0, 1032]
	ldr	w3, [x0, 1000]
	ldrb	w1, [x0, 984]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1024]
	ldr	w2, [x0, 1040]
	ldr	w3, [x0, 1008]
	ldrb	w1, [x0, 992]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1033]
	ldrb	w3, [x0, 1017]
	ldr	w2, [x0, 1000]
	ldrb	w1, [x0, 985]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1041]
	ldrb	w3, [x0, 1025]
	ldr	w2, [x0, 1008]
	ldrb	w1, [x0, 993]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1034]
	ldrb	w3, [x0, 1002]
	ldr	w2, [x0, 1016]
	ldrb	w1, [x0, 986]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1042]
	ldrb	w3, [x0, 1010]
	ldr	w2, [x0, 1024]
	ldrb	w1, [x0, 994]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1019]
	ldrb	w3, [x0, 1003]
	ldr	w1, [x0, 1032]
	ldrb	w2, [x0, 987]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1027]
	ldrb	w2, [x0, 1011]
	ldr	w4, [x0, 1040]
	ldrb	w1, [x0, 995]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 12
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1380]
	ldr	w3, [x0, 1388]
	ldr	w4, [x0, 1372]
	ldrb	w2, [x1, 596]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1412]
	ldr	w3, [x0, 1420]
	ldr	w4, [x0, 1404]
	ldrb	w2, [x0, 1396]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1389]
	ldrb	w4, [x0, 1381]
	ldr	w3, [x0, 1372]
	ldrb	w2, [x1, 597]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1421]
	ldrb	w4, [x0, 1413]
	ldr	w3, [x0, 1404]
	ldrb	w2, [x0, 1397]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1390]
	ldrb	w4, [x0, 1374]
	ldr	w3, [x0, 1380]
	ldrb	w2, [x1, 598]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1422]
	ldrb	w4, [x0, 1406]
	ldr	w3, [x0, 1412]
	ldrb	w2, [x0, 1398]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1383]
	ldrb	w3, [x0, 1375]
	ldr	w5, [x0, 1388]
	ldrb	w2, [x1, 599]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1415]
	ldrb	w3, [x0, 1407]
	ldr	w1, [x0, 1420]
	ldrb	w2, [x0, 1399]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1384]
	ldr	w2, [x0, 1392]
	ldr	w3, [x0, 1376]
	ldrb	w1, [x0, 1368]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1416]
	ldr	w2, [x0, 1424]
	ldr	w3, [x0, 1408]
	ldrb	w1, [x0, 1400]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1393]
	ldrb	w3, [x0, 1385]
	ldr	w2, [x0, 1376]
	ldrb	w1, [x0, 1369]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1425]
	ldrb	w3, [x0, 1417]
	ldr	w2, [x0, 1408]
	ldrb	w1, [x0, 1401]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1394]
	ldrb	w3, [x0, 1378]
	ldr	w2, [x0, 1384]
	ldrb	w1, [x0, 1370]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1426]
	ldrb	w3, [x0, 1410]
	ldr	w2, [x0, 1416]
	ldrb	w1, [x0, 1402]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1387]
	ldrb	w3, [x0, 1379]
	ldr	w1, [x0, 1392]
	ldrb	w2, [x0, 1371]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1419]
	ldrb	w2, [x0, 1411]
	ldr	w4, [x0, 1424]
	ldrb	w1, [x0, 1403]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 2432]
	ldrb	w0, [x3, 13]
	cbz	w0, .L440
	ldp	w6, w11, [x3, 68]
	ldr	x0, [x20, 2424]
	mov	w1, 0
	subs	w8, w11, #1
	ldrb	w7, [x3, 15]
	sub	w12, w6, #1
	ldr	w4, [x0, 64]
	ldr	w5, [x0, 128]
	bmi	.L412
	.p2align 2
.L443:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w11, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L443
.L412:
	mov	w1, 0
	tbnz	w12, #31, .L410
	.p2align 2
.L442:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w6, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bne	.L442
.L410:
	mov	w1, 1
	lsl	w0, w1, w5
	sdiv	w5, w4, w0
	msub	w0, w5, w0, w4
	cmp	w0, wzr
	csinc	w5, w5, w5, eq
	sdiv	w9, w19, w5
	msub	w5, w9, w5, w19
	cbz	w7, .L455
	tbnz	w8, #31, .L452
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	.p2align 2
.L424:
	tbnz	w12, #31, .L435
	add	x0, x29, 224
	mov	w7, w4
	add	x0, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x0, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L421
	.p2align 3
.L433:
	mov	w7, w4
.L421:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L419
	cmp	w9, w10
	blt	.L427
.L419:
	cmp	w6, w2
	mov	w1, w3
	bne	.L433
.L425:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L434
	cmp	w9, w10
	blt	.L450
.L434:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	bne	.L424
.L451:
	sub	w9, w9, w10
	mov	w1, w3
	mul	w0, w9, w0
	.p2align 2
.L417:
	sub	w19, w5, w1
	add	w0, w19, w0
	add	w19, w0, w7
.L440:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L455:
	tbnz	w8, #31, .L452
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	tbnz	w12, #31, .L438
	.p2align 2
.L456:
	add	x0, x29, 224
	mov	w7, w4
	add	x3, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x3, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L428
	.p2align 3
.L436:
	mov	w7, w4
.L428:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L426
	cmp	w9, w10
	blt	.L427
.L426:
	cmp	w6, w2
	mov	w1, w3
	bne	.L436
.L432:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L437
	cmp	w9, w10
	blt	.L450
.L437:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	beq	.L451
	tbz	w12, #31, .L456
.L438:
	mov	w3, 0
	add	w10, w14, w8
	b	.L432
	.p2align 3
.L427:
	sub	w9, w9, w14
	mul	w0, w9, w0
	b	.L417
.L435:
	mov	w3, 0
	add	w10, w14, w8
	b	.L425
.L452:
	mov	w0, 0
	mov	w1, 0
	mov	w7, 0
	b	.L417
.L450:
	sub	w9, w9, w14
	mov	w1, w3
	mul	w0, w9, w0
	b	.L417
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 2432]
	ldrb	w0, [x3, 13]
	cbz	w0, .L475
	ldp	w8, w4, [x3, 68]
	ldr	x0, [x20, 2424]
	subs	w13, w4, #1
	sub	w12, w8, #1
	ldr	w5, [x0, 64]
	ldr	w6, [x0, 128]
	bmi	.L459
	mov	w1, 0
	.p2align 2
.L460:
	sxtw	x0, w1
	add	x7, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x7, x0, lsl 2
	cmp	w4, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L460
	tbnz	w12, #31, .L492
.L462:
	mov	w1, 0
	.p2align 2
.L465:
	sxtw	x0, w1
	add	x4, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x4, x0, lsl 2
	cmp	w12, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bge	.L465
	mov	w1, 1
	lsl	w0, w1, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	tbnz	w13, #31, .L463
.L464:
	ldr	w11, [x29, 140]
	mov	w10, 0
	mov	w9, 0
	mov	w4, 0
	mov	w1, 0
	mov	w7, 0
	mov	w2, 0
	add	w11, w11, 1
	.p2align 2
.L471:
	tbnz	w12, #31, .L477
	add	x1, x29, 224
	add	x1, x1, x9, sxtw 2
	ldr	w7, [x1, -172]
	add	w7, w7, 1
	madd	w5, w11, w7, w4
	cmp	w19, w5
	blt	.L478
	mov	w1, w4
	mov	w2, w11
	mov	w6, 0
	mov	w3, 0
	mov	w4, w5
	b	.L468
	.p2align 3
.L469:
	ldr	w2, [x5, -84]
	mov	w1, w4
	add	w2, w2, 1
	madd	w5, w2, w7, w4
	cmp	w5, w19
	bgt	.L470
	mov	w4, w5
.L468:
	add	w3, w3, 1
	add	x5, x29, 224
	cmp	w8, w3
	add	w6, w6, w2
	add	x5, x5, x3, sxtw 2
	bne	.L469
.L472:
	cmp	w4, w19
	bgt	.L476
	add	w9, w9, 1
	add	w10, w10, w7
	cmp	w13, w9
	bge	.L471
.L476:
	mov	w4, w1
	.p2align 2
.L470:
	cbz	w2, .L463
	sub	w4, w19, w4
	sdiv	w1, w4, w2
	add	w10, w1, w10
	msub	w4, w1, w2, w4
	add	w6, w4, w6
	madd	w0, w10, w0, w6
.L487:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L475:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L477:
	mov	w6, 0
	b	.L472
.L478:
	mov	w2, w11
	mov	w6, 0
	b	.L470
.L492:
	mov	w0, 1
	lsl	w0, w0, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	b	.L464
.L459:
	tbz	w12, #31, .L462
.L463:
	ldr	x1, .LC134
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L487
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	3
.LC134:
	.xword	.LC133
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC135
	ldr	x20, .LC136
	mov	x2, 16384
	movk	x2, 0x2, lsl 16
	mov	w1, 0
	ldr	x3, [x21, 96]
	add	x0, x20, 1792
	blr	x3
	ldr	x0, .LC137
	mov	x2, 36864
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 1280
	blr	x3
	add	x0, x19, 8192
	ldr	x3, [x21, 96]
	mov	x2, 880
	mov	w1, 0
	add	x0, x0, 1172
	blr	x3
	str	wzr, [x19, 9360]
	ldr	x1, [x19, 2432]
	ldr	x2, [x19, 2424]
	ldr	w0, [x1, 72]
	ldr	w10, [x2, 188]
	cbz	w0, .L493
	mov	w15, 0
	mov	w17, 0
	mov	w4, 0
.L502:
	ldr	w0, [x1, 68]
	uxtw	x16, w15
	cbz	w0, .L503
	add	x9, x16, 104
	ldr	w0, [x19, 9360]
	mul	w14, w17, w10
	mov	w12, 0
	mov	w13, 0
	lsl	x9, x9, 1
.L501:
	uxtw	x2, w0
	add	x3, x1, x9
	uxtw	x11, w12
	add	x5, x19, x2, lsl 3
	str	w4, [x5, 9364]
	ldrsh	w3, [x3, 4]
	cbz	w3, .L497
	add	x5, x11, 80
	add	w8, w13, w14
	mov	w7, 0
	lsl	x5, x5, 1
	.p2align 2
.L499:
	add	x2, x1, x5
	mov	w0, w4
	sub	w6, w8, w4
	ldrsh	w2, [x2, 12]
	cbz	w2, .L500
	.p2align 2
.L507:
	add	x1, x20, 1792
	add	w2, w6, w0
	str	w2, [x1, w0, sxtw 2]
	add	w0, w0, 1
	sub	w2, w0, w4
	ldr	x1, [x19, 2432]
	add	x3, x1, x5
	ldrsh	w3, [x3, 12]
	cmp	w3, w2
	bhi	.L507
	mov	w4, w0
.L500:
	add	x0, x1, x9
	add	w7, w7, 1
	add	w8, w8, w10
	ldrsh	w0, [x0, 4]
	cmp	w0, w7
	bhi	.L499
	ldr	w0, [x19, 9360]
	uxtw	x2, w0
.L497:
	add	x2, x19, x2, lsl 3
	sub	w3, w4, #1
	add	w0, w0, 1
	add	x11, x1, x11, lsl 1
	add	w12, w12, 1
	str	w3, [x2, 9368]
	str	w0, [x19, 9360]
	ldr	w3, [x1, 68]
	ldrsh	w2, [x11, 172]
	cmp	w3, w12
	add	w13, w13, w2
	bhi	.L501
.L503:
	add	x16, x1, x16, lsl 1
	ldr	w0, [x1, 72]
	add	w15, w15, 1
	cmp	w0, w15
	ldrsh	w0, [x16, 212]
	add	w17, w17, w0
	bhi	.L502
.L493:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	3
.LC135:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC136:
	.xword	.LANCHOR2
	.align	3
.LC137:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 4096
	add	x23, x19, 8192
	bl	_mcount
	ldr	w3, [x19, 4020]
	mov	w0, 2
	ldr	w2, [x19, 4204]
	ldr	x1, .LC140
	bl	dprint_vfmw
	ldr	x1, .LC142
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w21, [x19, 3992]
	ldr	w5, [x19, 4168]
	str	w5, [x19, 7952]
	ldr	w5, [x19, 4172]
	str	w5, [x19, 7956]
	ldr	w5, [x19, 4204]
	str	w5, [x19, 7944]
	ldr	w4, [x19, 4100]
	ldr	w0, [x19, 4092]
	ldr	w5, [x19, 4020]
	ldr	w2, [x19, 4096]
	str	w5, [x19, 7948]
	ldr	w5, [x19, 4192]
	sub	w2, w2, w0
	str	w5, [x19, 7964]
	sub	w0, w4, w0
	ldr	w1, [x19, 4104]
	ldr	w5, [x19, 4196]
	ldr	x3, [x19, 2424]
	str	w0, [x19, 7976]
	str	w5, [x19, 7968]
	ldr	x0, [x19, 2464]
	ldr	w5, [x19, 4200]
	str	w21, [x19, 6688]
	uxtw	x21, w21
	str	w2, [x19, 7960]
	lsl	x22, x21, 2
	str	x0, [x19, 9152]
	sub	w0, w1, w4
	str	w5, [x19, 7972]
	sub	x22, x22, x21
	str	wzr, [x19, 204]
	mov	x2, 64
	str	w0, [x19, 7980]
	add	x22, x21, x22, lsl 3
	lsl	x22, x22, 3
	ldrb	w0, [x3, 10]
	add	x1, x22, 12288
	strb	w0, [x20, 2566]
	add	x1, x19, x1
	add	x1, x1, 1120
	ldrb	w0, [x3, 3]
	strb	w0, [x20, 2567]
	add	x0, x20, 2688
	ldrb	w4, [x3, 7]
	strb	w4, [x20, 2568]
	ldrb	w4, [x3, 6]
	strb	w4, [x20, 2569]
	ldrb	w4, [x3, 5]
	strb	w4, [x20, 2570]
	ldr	w4, [x3, 60]
	str	w4, [x19, 6668]
	ldr	w4, [x3, 104]
	strb	w4, [x20, 2576]
	ldr	w4, [x3, 192]
	sub	w4, w4, #1
	str	w4, [x19, 6676]
	ldr	w4, [x3, 188]
	sub	w4, w4, #1
	str	w4, [x19, 6680]
	ldr	w4, [x19, 3996]
	str	w4, [x19, 6684]
	ldr	x4, [x19, 2432]
	ldr	w5, [x4, 84]
	sub	w5, w5, #2
	str	w5, [x19, 6692]
	ldrb	w5, [x4, 11]
	strb	w5, [x20, 2600]
	ldrb	w4, [x4, 10]
	strb	w4, [x20, 2601]
	ldr	w4, [x3, 164]
	str	w4, [x19, 6700]
	ldr	w4, [x3, 168]
	str	w4, [x19, 6704]
	ldr	w4, [x3, 156]
	str	w4, [x19, 6708]
	ldr	w4, [x3, 160]
	str	w4, [x19, 6712]
	ldr	w4, [x3, 148]
	str	w4, [x19, 6716]
	ldr	w4, [x3, 152]
	str	w4, [x19, 6720]
	ldr	w4, [x3, 172]
	str	w4, [x19, 6724]
	ldr	x5, .LC143
	ldr	w4, [x3, 124]
	str	w4, [x19, 6728]
	ldr	w4, [x3, 128]
	str	w4, [x19, 6732]
	ldr	w4, [x3, 100]
	str	w4, [x19, 6736]
	ldr	w4, [x3, 92]
	str	w4, [x19, 6740]
	ldr	w4, [x3, 112]
	str	w4, [x19, 6744]
	ldr	w4, [x3, 108]
	str	w4, [x19, 6748]
	ldr	w4, [x3, 96]
	str	w4, [x19, 6752]
	ldr	w4, [x3, 88]
	ldr	x3, [x5, 104]
	str	w4, [x19, 6756]
	blr	x3
	ldr	x4, [x19, 2424]
	add	x3, x23, 796
	add	x2, x23, 716
	add	x1, x23, 204
	mov	x0, x19
	ldr	w5, [x4, 68]
	str	w5, [x19, 6848]
	ldr	w4, [x4, 64]
	str	w4, [x19, 6852]
	bl	HEVC_CalcTileInfo
	cbnz	w0, .L533
	ldr	x1, [x19, 2432]
	mov	w0, 0
	ldrb	w2, [x1, 16]
	strb	w2, [x20, 2780]
	ldrb	w2, [x1, 7]
	strb	w2, [x20, 2781]
	ldrb	w2, [x1, 3]
	strb	w2, [x20, 2782]
	ldrb	w2, [x1, 14]
	strb	w2, [x20, 2783]
	ldrb	w2, [x1, 15]
	strb	w2, [x20, 2784]
	ldrb	w2, [x1, 13]
	strb	w2, [x20, 2785]
	ldr	x2, [x19, 2424]
	ldr	w3, [x1, 56]
	ldr	w2, [x2, 128]
	sub	w2, w2, w3
	str	w2, [x19, 6884]
	ldr	w2, [x1, 52]
	str	w2, [x19, 6888]
	ldrb	w2, [x1, 8]
	strb	w2, [x20, 2796]
	ldrb	w2, [x1, 12]
	strb	w2, [x20, 2797]
	ldrb	w2, [x1, 6]
	strb	w2, [x20, 2798]
	ldr	w2, [x1, 60]
	str	w2, [x19, 6896]
	ldr	w2, [x1, 64]
	str	w2, [x19, 6900]
	ldr	w2, [x1, 72]
	sub	w2, w2, #1
	str	w2, [x19, 6904]
	ldr	w2, [x1, 68]
	sub	w2, w2, #1
	str	w2, [x19, 6908]
	ldrb	w2, [x1, 10]
	strb	w2, [x20, 2601]
	ldrb	w1, [x1, 11]
	strb	w1, [x20, 2600]
	str	wzr, [x19, 2348]
	ldr	w1, [x19, 2332]
	cmp	w1, 1
	beq	.L515
	ldr	x1, [x19, 4048]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cbz	x0, .L534
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L518
	cbz	x3, .L518
	ldr	w0, [x19, 252]
	add	x3, x23, 76
	add	x2, x20, 3904
	add	x1, x20, 4032
	add	x22, x19, x22
	bl	FSP_GetDecFsAddrTab
	ldr	x3, [x24, 32]
	add	x1, x23, 68
	ldr	w0, [x19, 252]
	add	x2, x20, 4036
	ldr	w3, [x3, 4]
	str	w3, [x19, 7944]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x19, 4020]
	mov	w1, 0
	str	w0, [x19, 7948]
	ldr	w0, [x24, 12]
	str	w0, [x19, 8264]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 9352]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 9356]
	ldr	w4, [x22, 13272]
	str	w4, [x19, 9140]
	cbz	w4, .L523
	lsl	x3, x21, 3
	sub	x3, x3, x21
	add	x21, x21, x3, lsl 3
	sub	x3, x21, x3
	.p2align 2
.L527:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x3, x0
	cmp	w1, w4
	add	x0, x19, x0, lsl 2
	add	x2, x19, x2, lsl 2
	ldr	w2, [x2, 13344]
	str	w2, [x0, 9076]
	bne	.L527
.L523:
	add	x22, x20, 2820
	mov	w21, 0
.L521:
	mov	x2, x22
	mov	w0, w21
	mov	x1, x19
	add	w21, w21, 1
	add	x22, x22, 64
	bl	HEVC_WriteQmatrix_8x8
	cmp	w21, 4
	bne	.L521
	mov	w0, w21
	add	x2, x20, 3076
	mov	x1, x19
	add	x22, x20, 3332
	mov	w21, 2
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 3140
	mov	x1, x19
	mov	w0, 5
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 3204
	mov	x1, x19
	mov	w0, 0
	bl	HEVC_WriteQmatrix_16x16
	add	x2, x20, 3268
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_16x16
.L524:
	mov	x2, x22
	mov	w0, w21
	mov	x1, x19
	add	w21, w21, 1
	add	x22, x22, 64
	bl	HEVC_WriteQmatrix_16x16
	cmp	w21, 6
	bne	.L524
	add	x2, x20, 3588
	mov	x1, x19
	mov	w0, 0
	add	x22, x20, 3716
	mov	w21, 0
	bl	HEVC_WriteQmatrix_32x32
	add	x2, x20, 3652
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_32x32
	.p2align 2
.L525:
	mov	x2, x22
	mov	w0, w21
	mov	x1, x19
	add	w21, w21, 1
	add	x22, x22, 16
	bl	HEVC_WriteQmatrix_4x4
	cmp	w21, 6
	bne	.L525
	add	x0, x19, 2048
	add	x8, x19, 2048
	ldp	w5, w6, [x0, 236]
	ldp	w3, w4, [x8, 252]
	ldp	w7, w2, [x0, 228]
	ldp	w0, w1, [x8, 244]
	lsl	w3, w3, 16
	lsl	w5, w5, 16
	orr	w3, w3, w4, lsl 24
	orr	w5, w5, w6, lsl 24
	orr	w0, w0, w1, lsl 8
	orr	w2, w7, w2, lsl 8
	orr	w0, w3, w0
	ldr	w4, [x19, 4020]
	orr	w1, w5, w2
	str	w0, [x19, 7912]
	str	w1, [x19, 7908]
	mov	w0, 0
	str	w4, [x19, 7940]
.L515:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L533:
	ldr	x2, .LC144
	mov	w0, 1
	ldr	x1, .LC146
	add	x2, x2, 240
	bl	dprint_vfmw
	mov	w0, -1
	b	.L515
.L518:
	ldr	x1, .LC150
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L515
.L534:
	ldr	x2, [x19, 4048]
	mov	w0, 1
	ldr	x1, .LC148
	ldr	w2, [x2, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L515
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
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
	.xword	.LANCHOR0
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC150:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	add	x0, x0, 592
	ldrb	w1, [x0, 1]
	cbz	w1, .L537
	ldrsb	w1, [x19, 11]
	add	x0, x19, 8192
	add	x0, x0, 3724
	cbz	w1, .L569
.L537:
	ldp	w4, w5, [x0, 68]
	cmp	w4, 16
	bhi	.L570
	cmp	w5, 16
	bhi	.L541
	cbz	w4, .L542
	ldr	x0, [x19, 2480]
	cbz	x0, .L555
	ldr	x0, [x0, 16]
	cbz	x0, .L571
	add	x0, x19, 2488
	mov	w2, 0
	b	.L547
	.p2align 3
.L548:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L543
	ldr	x1, [x1, 16]
	cbz	x1, .L544
.L547:
	add	w2, w2, 1
	cmp	w4, w2
	bne	.L548
.L542:
	cbz	w5, .L557
	ldr	x0, [x19, 2616]
	cbz	x0, .L558
	ldr	x0, [x0, 16]
	cbz	x0, .L572
	add	x0, x19, 2624
	mov	w2, 0
	b	.L553
	.p2align 3
.L554:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L549
	ldr	x1, [x1, 16]
	cbz	x1, .L550
.L553:
	add	w2, w2, 1
	cmp	w5, w2
	bne	.L554
.L557:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L555:
	mov	w2, 0
	.p2align 2
.L543:
	ldr	x1, .LC159
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L539:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L571:
	mov	w2, 0
.L544:
	ldr	x1, .LC161
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L558:
	mov	w2, 0
.L549:
	ldr	x1, .LC163
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L572:
	mov	w2, 0
.L550:
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L569:
	ldr	x2, .LC151
	mov	w0, 0
	ldr	x1, .LC153
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L541:
	ldr	x1, .LC157
	mov	w3, 17
	mov	w2, w5
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L570:
	ldr	x1, .LC155
	mov	w3, 17
	mov	w2, w4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	3
.LC151:
	.xword	.LANCHOR0
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC165:
	.xword	.LC164
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	ldr	w24, [x19, 3992]
	bl	HEVC_CheckListX
	mov	w23, w0
	cbnz	w0, .L616
	ldr	w3, [x19, 152]
	ldr	w0, [x19, 204]
	cmp	w0, w3
	bcs	.L652
	mov	w22, 1368
	ldr	x21, .LC168
	ldr	x20, [x19, 2464]
	mov	x2, 1368
	umull	x0, w0, w22
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x20, x20, x0
	mov	x0, x20
	blr	x3
	ldr	x3, [x21, 96]
	mov	w1, 0
	mov	x2, 64
	add	x0, x29, 96
	blr	x3
	ldr	w0, [x19, 204]
	ldr	w1, [x19, 152]
	add	w0, w0, 1
	str	w0, [x19, 204]
	cmp	w0, w1
	bcc	.L653
	str	xzr, [x20, 1360]
.L577:
	ldr	w22, [x19, 176]
	ldr	w0, [x19, 236]
	ldr	w1, [x19, 4724]
	add	w22, w22, 1
	ldr	x3, [x19, 2400]
	add	w0, w0, 1
	str	w22, [x19, 176]
	str	w1, [x19, 208]
	str	w0, [x19, 236]
	ldrb	w1, [x3]
	ldr	w0, [x3, 8]
	cmp	w1, 1
	ccmp	w1, w0, 2, ls
	bcs	.L578
	.p2align 2
.L579:
	uxtw	x0, w1
	lsl	x2, x0, 5
	add	x3, x3, x2
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 60]
	str	w3, [x0, 8]
	ldr	x3, [x19, 2400]
	add	x3, x3, x2
	ldr	w3, [x3, 56]
	str	w3, [x20, w1, uxtw 2]
	add	w1, w1, 1
	ldr	x3, [x19, 2400]
	add	x2, x3, x2
	ldr	w2, [x2, 64]
	str	w2, [x0, 16]
	ldr	x3, [x19, 2400]
	ldr	w0, [x3, 8]
	cmp	w0, w1
	ccmp	w1, 1, 2, hi
	bls	.L579
.L578:
	cmp	w0, 1
	bhi	.L584
	.p2align 2
.L637:
	add	x1, x20, x0, uxtw 2
	str	wzr, [x1, 8]
	str	wzr, [x20, w0, uxtw 2]
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 16]
	bne	.L637
.L584:
	add	x26, x19, 4096
	add	x25, x19, 8192
	ldrb	w0, [x26, 593]
	cbz	w0, .L654
.L582:
	ldr	w0, [x19, 11984]
	cbz	w0, .L585
	mov	w1, 0
	.p2align 2
.L586:
	uxtw	x0, w1
	add	x5, x29, 160
	add	w1, w1, 1
	add	x2, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x3, [x2, 2480]
	ldr	w3, [x3, 4]
	str	w3, [x0, 116]
	ldr	x4, [x2, 2480]
	ldr	x2, [x4, 16]
	ldp	w3, w2, [x2, 20]
	add	x3, x19, x3, lsl 2
	add	x2, x5, x2, lsl 2
	ldr	w3, [x3, 8132]
	str	w3, [x2, -64]
	ldr	x2, [x4, 16]
	ldr	w2, [x2, 24]
	str	w2, [x0, 372]
	ldr	w0, [x19, 11984]
	cmp	w0, w1
	bhi	.L586
	ldr	w3, [x19, 11988]
	cbz	w3, .L587
.L615:
	mov	w1, 0
	.p2align 2
.L588:
	uxtw	x0, w1
	add	x5, x29, 160
	add	w1, w1, 1
	add	x2, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x3, [x2, 2616]
	ldr	w3, [x3, 4]
	str	w3, [x0, 180]
	ldr	x4, [x2, 2616]
	ldr	x2, [x4, 16]
	ldp	w3, w2, [x2, 20]
	add	x3, x19, x3, lsl 2
	add	x2, x5, x2, lsl 2
	ldr	w3, [x3, 8132]
	str	w3, [x2, -64]
	ldr	x2, [x4, 16]
	ldr	w2, [x2, 24]
	str	w2, [x0, 436]
	ldr	w3, [x19, 11988]
	cmp	w3, w1
	bhi	.L588
	ldr	w0, [x19, 11984]
.L587:
	cbz	w0, .L589
	uxtw	x1, w24
	ldr	w2, [x20, 372]
	lsl	x4, x1, 3
	ldr	w5, [x19, 3996]
	sub	x4, x4, x1
	lsl	x6, x4, 3
	sub	x4, x6, x4
	add	x4, x4, x1
	add	x1, x4, x2
	add	x1, x19, x1, lsl 2
	ldr	w1, [x1, 13408]
	cmp	w5, w1
	blt	.L622
	sub	w0, w0, #1
	mov	x1, x20
	add	x2, x20, x0, lsl 2
	b	.L592
	.p2align 3
.L593:
	ldr	w0, [x1, 376]
	add	x1, x1, 4
	add	x0, x4, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13408]
	cmp	w0, w5
	bgt	.L622
.L592:
	cmp	x2, x1
	bne	.L593
.L589:
	ldr	w0, [x19, 11936]
	cbnz	w0, .L651
	mov	w0, 1
	cbz	w3, .L590
	uxtw	x1, w24
	ldr	w0, [x20, 436]
	lsl	x2, x1, 3
	ldr	w4, [x19, 3996]
	sub	x2, x2, x1
	lsl	x5, x2, 3
	sub	x2, x5, x2
	add	x1, x2, x1
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13408]
	cmp	w4, w0
	blt	.L622
	sub	w3, w3, #1
	mov	x2, x20
	add	x3, x20, x3, lsl 2
	b	.L595
	.p2align 3
.L596:
	ldr	w0, [x2, 440]
	add	x2, x2, 4
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13408]
	cmp	w0, w4
	bgt	.L622
.L595:
	cmp	x2, x3
	bne	.L596
.L651:
	mov	w0, 1
.L590:
	strb	w0, [x20, 24]
	ldrb	w0, [x26, 593]
	strb	w0, [x20, 25]
	ldr	w2, [x19, 11932]
	str	w2, [x20, 28]
	ldrb	w0, [x25, 3731]
	strb	w0, [x20, 32]
	ldr	w0, [x19, 11956]
	str	w0, [x20, 36]
	ldr	w0, [x19, 2332]
	cbnz	w0, .L597
	ldr	x3, [x19, 4048]
	ldr	w4, [x19, 204]
	ldr	w0, [x3, 316]
	sub	w1, w4, #1
	madd	w0, w1, w0, w2
	udiv	w0, w0, w4
	str	w0, [x3, 68]
.L597:
	ldr	w0, [x19, 11936]
	cbz	w0, .L655
	cmp	w0, 1
	mov	w24, 0
	beq	.L599
.L600:
	str	w24, [x20, 40]
	ldr	w0, [x19, 11960]
	str	w0, [x20, 48]
	ldrb	w0, [x25, 3732]
	strb	w0, [x20, 52]
	ldr	w0, [x19, 11964]
	str	w0, [x20, 44]
	ldr	w0, [x19, 11992]
	cbz	w0, .L601
	sub	w0, w0, #1
	str	w0, [x20, 60]
.L602:
	ldr	w0, [x19, 11996]
	cbz	w0, .L603
	sub	w0, w0, #1
	str	w0, [x20, 56]
.L604:
	ldrb	w0, [x25, 3728]
	strb	w0, [x20, 64]
	ldrb	w0, [x25, 3730]
	strb	w0, [x20, 65]
	ldr	w0, [x19, 11984]
	str	w0, [x20, 68]
	ldr	w0, [x19, 11988]
	str	w0, [x20, 72]
	ldr	w0, [x19, 11936]
	str	w0, [x20, 76]
	ldr	w0, [x19, 4728]
	str	w0, [x20, 80]
	ldr	x0, [x19, 2424]
	ldr	w3, [x19, 4728]
	ldr	w1, [x0, 188]
	mov	x0, x19
	udiv	w2, w3, w1
	msub	w1, w2, w1, w3
	str	w1, [x20, 84]
	ldr	x1, [x19, 2424]
	ldr	w2, [x1, 188]
	ldr	w1, [x19, 4728]
	udiv	w1, w1, w2
	str	w1, [x20, 88]
	ldr	w1, [x19, 4728]
	bl	HEVC_CtbRsAddrToTsAddr
	str	w0, [x20, 92]
	ldr	w0, [x19, 11968]
	str	w0, [x20, 96]
	ldr	w0, [x19, 11972]
	str	w0, [x20, 100]
	ldr	w0, [x19, 11980]
	str	w0, [x20, 104]
	ldr	w0, [x19, 11976]
	str	w0, [x20, 108]
	ldrb	w0, [x25, 3727]
	strb	w0, [x20, 112]
	ldrb	w0, [x25, 3726]
	strb	w0, [x20, 113]
	ldrb	w0, [x25, 3733]
	strb	w0, [x20, 114]
	ldrb	w0, [x25, 3734]
	strb	w0, [x20, 115]
	ldr	x0, [x19, 2432]
	ldrb	w1, [x0, 10]
	cbz	w1, .L605
	ldr	w1, [x19, 11936]
	cmp	w1, 1
	beq	.L606
.L605:
	ldrb	w0, [x0, 11]
	cmp	w0, 1
	beq	.L656
.L608:
	ldrb	w0, [x25, 3728]
	cbz	w0, .L610
	add	x0, x29, 160
	add	x24, x0, x24, sxtw 2
	ldr	w0, [x24, -64]
	str	w0, [x20, 564]
.L611:
	ldr	w0, [x19, 2332]
	cbnz	w0, .L612
	ldr	x0, [x19, 2440]
	ldr	x1, [x19, 2400]
	str	x1, [x0, w22, uxtw 3]
	str	xzr, [x19, 2400]
.L612:
	ldrb	w0, [x26, 2785]
	cbz	w0, .L630
	ldr	w0, [x19, 236]
	cmp	w0, 1
	beq	.L657
	sub	w1, w0, #2
	ldr	w2, [x20, 92]
	sub	w0, w0, #1
	add	x1, x19, x1, lsl 3
	sub	w2, w2, #1
	add	x3, x19, x0, lsl 3
	str	w2, [x1, 10248]
	ldr	w1, [x20, 92]
	str	w1, [x3, 10244]
.L614:
	ldr	w1, [x19, 6676]
	add	x0, x19, x0, lsl 3
	ldr	w2, [x19, 6680]
	mov	w3, 36863
	madd	w2, w1, w2, w2
	add	w1, w2, w1
	str	w1, [x0, 10248]
	ldr	w1, [x20, 92]
	sub	w1, w1, #1
	cmp	w1, w3
	bhi	.L630
	mov	x0, x19
	bl	HEVC_CtbTsAddrToRsAddr
	str	w0, [x20, 568]
.L630:
	mov	w0, w23
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L653:
	ldr	x1, [x19, 2464]
	umull	x0, w0, w22
	add	x0, x1, x0
	str	x0, [x20, 1360]
	b	.L577
	.p2align 3
.L622:
	mov	w0, 0
	b	.L590
	.p2align 3
.L603:
	str	wzr, [x20, 56]
	b	.L604
	.p2align 3
.L610:
	ldr	w0, [x19, 8132]
	str	w0, [x20, 564]
	b	.L611
	.p2align 3
.L601:
	str	wzr, [x20, 60]
	b	.L602
	.p2align 3
.L655:
	ldrb	w0, [x25, 3732]
	cbnz	w0, .L599
	ldrsw	x0, [x19, 11960]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 436]
	b	.L600
	.p2align 3
.L599:
	ldrsw	x0, [x19, 11960]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 372]
	b	.L600
	.p2align 3
.L654:
	ldr	x3, [x21, 104]
	mov	x2, 1356
	add	x1, x26, 592
	add	x0, x25, 3724
	blr	x3
	mov	w0, 1
	strb	w0, [x19, 11]
	b	.L582
	.p2align 3
.L656:
	ldr	w0, [x19, 11936]
	cbnz	w0, .L608
.L606:
	ldr	w0, [x19, 12072]
	mov	x2, 64
	str	w0, [x20, 580]
	add	x1, x25, 4016
	ldr	x3, [x21, 104]
	add	x27, x19, 12288
	ldr	w0, [x19, 12204]
	str	w0, [x20, 584]
	add	x0, x20, 588
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 64
	add	x1, x25, 3884
	add	x0, x20, 716
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x25, 4080
	add	x0, x20, 844
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x27, 112
	add	x0, x20, 1100
	blr	x3
	ldr	w0, [x19, 11936]
	cbnz	w0, .L608
	ldr	x3, [x21, 104]
	add	x1, x27, 240
	mov	x2, 64
	add	x0, x20, 652
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x25, 3948
	mov	x2, 64
	add	x0, x20, 780
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x27, 304
	mov	x2, 128
	add	x0, x20, 972
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x27, 432
	add	x0, x20, 1228
	blr	x3
	b	.L608
	.p2align 3
.L657:
	ldr	w1, [x20, 92]
	mov	x0, 0
	str	w1, [x19, 10244]
	b	.L614
.L585:
	ldr	w0, [x19, 11988]
	cbnz	w0, .L615
	mov	w0, 1
	b	.L590
.L616:
	mov	w23, -1
	b	.L630
.L652:
	ldr	x1, .LC167
	mov	w2, w0
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L630
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC168:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x19, x20, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	w0, w19, w20, lsl 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 4012]
	ldr	w0, [x19, 204]
	ldr	w2, [x19, 4016]
	cmp	w1, wzr
	str	w0, [x19, 9144]
	cset	w1, eq
	str	w2, [x19, 7988]
	mov	w0, 0
	str	w1, [x19, 7996]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 4724]
	ldr	w4, [x19, 164]
	tbnz	w3, #31, .L663
	cmp	w3, w4
	bge	.L663
	ldr	x0, [x19, 2384]
	mov	w1, 1888
	ldr	w4, [x19, 160]
	smaddl	x3, w3, w1, x0
	ldr	w3, [x3, 32]
	tbnz	w3, #31, .L667
	cmp	w3, w4
	bge	.L667
	add	x20, x19, 4096
	ldr	x2, [x19, 2376]
	mov	w4, 12660
	ldr	w5, [x19, 5620]
	ldr	w6, [x20, 1528]
	mov	w0, 1
	smaddl	x3, w3, w4, x2
	ldr	w9, [x20, 1532]
	add	w8, w5, w6
	ldr	w2, [x3, 116]
	cmp	w8, w9
	mov	w3, w8
	lsl	w2, w0, w2
	bcs	.L679
	cmp	w8, 15
	bgt	.L670
	ldr	w4, [x19, 3996]
	b	.L672
	.p2align 3
.L690:
	cmp	w9, w3
	bls	.L679
	cmp	w3, 16
	beq	.L670
.L672:
	add	x0, x19, x3, sxtw 2
	mov	w1, w4
	add	w3, w3, 1
	ldr	w7, [x0, 4776]
	ldr	w0, [x0, 5720]
	cbnz	w7, .L673
	sdiv	w1, w4, w2
	sdiv	w7, w0, w2
	msub	w1, w1, w2, w4
	msub	w0, w7, w2, w0
.L673:
	cmp	w1, w0
	bne	.L690
	mov	w21, 1
.L669:
	cbz	w8, .L665
	ldr	w3, [x19, 4700]
	add	x1, x20, 1560
	ldr	w0, [x20, 1556]
	mov	w4, 0
	ldr	w2, [x19, 3996]
	add	w0, w3, w0
	cmp	w2, w0
	bne	.L677
	b	.L683
	.p2align 3
.L676:
	ldr	w0, [x1], 4
	add	w0, w3, w0
	cmp	w0, w2
	beq	.L683
.L677:
	add	w4, w4, 1
	cmp	w4, w8
	beq	.L665
	cmp	w4, 17
	bne	.L676
	ldr	x1, .LC176
	mov	w3, w4
	mov	w2, 8976
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L667:
	ldr	x1, .LC172
	mov	w2, 8927
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
.L665:
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L663:
	ldr	x1, .LC170
	mov	w2, 8915
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L679:
	mov	w21, 0
	b	.L669
	.p2align 3
.L670:
	ldr	x1, .LC174
	mov	w5, w9
	mov	w4, 16
	mov	w2, 8947
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	w5, [x19, 5620]
	ldr	w6, [x20, 1528]
	add	w8, w5, w6
	b	.L669
	.p2align 3
.L683:
	mov	w21, 1
	b	.L665
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC172:
	.xword	.LC171
	.align	3
.LC174:
	.xword	.LC173
	.align	3
.LC176:
	.xword	.LC175
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicVPSRefresh
	.type	HEVC_IsPicVPSRefresh, %function
HEVC_IsPicVPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 2416]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	beq	.L694
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L694:
	ldrb	w0, [x19, 2]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicVPSRefresh, .-HEVC_IsPicVPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicVPS
	.type	HEVC_UpdatePicVPS, %function
HEVC_UpdatePicVPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 132
	mov	x20, -132
	bl	_mcount
	strb	wzr, [x22, 2]
	ldr	x3, .LC177
	mov	x1, x22
	ldr	w0, [x19, 156]
	mov	x2, 132
	ldr	x4, [x19, 2368]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 156]
	ldr	x1, [x19, 2368]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 2416]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicVPS, .-HEVC_UpdatePicVPS
	.align	3
.LC177:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicSPSRefresh
	.type	HEVC_IsPicSPSRefresh, %function
HEVC_IsPicSPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 2424]
	ldr	w0, [x19, 56]
	ldr	w1, [x1, 56]
	cmp	w1, w0
	beq	.L699
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L699:
	ldrb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicSPSRefresh, .-HEVC_IsPicSPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicSPS
	.type	HEVC_UpdatePicSPS, %function
HEVC_UpdatePicSPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 12660
	mov	x20, -12660
	bl	_mcount
	strb	wzr, [x22]
	ldr	x3, .LC178
	mov	x1, x22
	ldr	w0, [x19, 160]
	mov	x2, 12660
	ldr	x4, [x19, 2376]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 160]
	ldr	x1, [x19, 2376]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 2424]
	ldr	w1, [x0, 56]
	str	w1, [x19, 264]
	ldr	w1, [x0, 64]
	str	w1, [x19, 268]
	ldr	w1, [x0, 68]
	str	w1, [x19, 272]
	ldr	w0, [x0, 128]
	str	w0, [x19, 276]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicSPS, .-HEVC_UpdatePicSPS
	.align	3
.LC178:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicPPSRefresh
	.type	HEVC_IsPicPPSRefresh, %function
HEVC_IsPicPPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 2432]
	ldr	w0, [x19, 28]
	ldr	w1, [x1, 28]
	cmp	w1, w0
	beq	.L704
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L704:
	ldrb	w0, [x19, 1]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicPPSRefresh, .-HEVC_IsPicPPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicPPS
	.type	HEVC_UpdatePicPPS, %function
HEVC_UpdatePicPPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x2
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	strb	wzr, [x19, 1]
	ldrb	w0, [x19, 13]
	cbz	w0, .L706
	ldrb	w0, [x19, 15]
	cbnz	w0, .L726
	ldr	w0, [x19, 68]
	ldr	w2, [x21, 188]
	sub	w3, w0, #1
	add	x1, x19, x0, sxtw 1
	cmp	w3, wzr
	strh	w2, [x1, 170]
	ble	.L718
	sub	w4, w0, #2
	add	x0, x19, 88
	add	x4, x4, 45
	add	x4, x19, x4, lsl 1
	.p2align 2
.L717:
	ldrsh	w3, [x0]
	add	x0, x0, 2
	strh	w3, [x0, 82]
	cmp	x0, x4
	ldrh	w2, [x1, 170]
	sub	w2, w2, w3
	strh	w2, [x1, 170]
	bne	.L717
.L718:
	ldr	w0, [x19, 72]
	ldr	w1, [x21, 192]
	sub	w2, w0, #1
	add	x3, x19, x0, sxtw 1
	cmp	w2, wzr
	strh	w1, [x3, 210]
	ble	.L713
	sub	w4, w0, #2
	add	x0, x19, 128
	add	x4, x4, 65
	add	x4, x19, x4, lsl 1
	.p2align 2
.L719:
	ldrsh	w2, [x0]
	add	x0, x0, 2
	strh	w2, [x0, 82]
	cmp	x4, x0
	ldrh	w1, [x3, 210]
	sub	w1, w1, w2
	strh	w1, [x3, 210]
	bne	.L719
	b	.L713
	.p2align 3
.L706:
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L713:
	ldr	w0, [x20, 164]
	mov	w22, 1888
	ldr	x1, .LC181
	mov	x21, -1888
	ldr	x4, [x20, 2384]
	mov	x2, 1888
	smaddl	x0, w0, w22, x21
	ldr	x3, [x1, 104]
	mov	x1, x19
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x20, 164]
	ldr	x1, [x20, 2384]
	smaddl	x0, w0, w22, x21
	add	x0, x1, x0
	str	x0, [x20, 2432]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L726:
	ldr	w4, [x19, 68]
	add	x1, x19, 172
	mov	w3, 0
	cmp	w4, wzr
	ble	.L712
	.p2align 2
.L721:
	add	w3, w3, 1
	ldr	w5, [x21, 188]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L721
.L712:
	ldr	w4, [x19, 72]
	add	x1, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L713
	.p2align 2
.L720:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L720
	b	.L713
	.size	HEVC_UpdatePicPPS, .-HEVC_UpdatePicPPS
	.align	3
.LC181:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPicInfo
	.type	HEVC_InitPicInfo, %function
HEVC_InitPicInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4716]
	mov	w3, 1
	ldr	x1, [x19, 2424]
	ldr	w2, [x19, 4700]
	strb	w3, [x19, 3985]
	str	w0, [x19, 3988]
	mov	w0, -1
	str	w2, [x19, 3996]
	str	w0, [x19, 4016]
	ldrsw	x3, [x19, 252]
	ldr	w4, [x1, 64]
	ldr	x0, .LC182
	str	w4, [x19, 4004]
	ldr	x0, [x0, x3, lsl 3]
	ldr	w3, [x1, 68]
	str	w3, [x19, 4008]
	str	wzr, [x19, 4012]
	ldrsb	w3, [x0, 44]
	cmp	w3, 1
	beq	.L740
.L728:
	ldr	w0, [x19, 2332]
	cbnz	w0, .L731
	ldr	x0, [x19, 2456]
	mov	x1, -1
	ldr	x2, [x0, 56]
	str	x2, [x19, 4640]
	ldr	x2, [x0, 72]
	str	x2, [x19, 4648]
	ldr	x2, [x0, 88]
	str	x2, [x19, 4656]
	ldr	w2, [x0, 104]
	str	w2, [x19, 4056]
	ldr	w2, [x0, 108]
	str	w2, [x19, 4060]
	ldr	w2, [x0, 112]
	str	w2, [x19, 4064]
	ldr	w2, [x0, 128]
	str	w2, [x19, 4068]
	str	x1, [x0, 56]
	ldr	x1, [x19, 2424]
.L731:
	ldr	w0, [x1, 64]
	add	x3, x19, 4096
	str	w0, [x19, 4124]
	add	x0, x19, 4056
	ldr	w2, [x1, 68]
	str	w2, [x19, 4128]
	str	wzr, [x19, 4108]
	ldr	w5, [x1, 60]
	ldr	w4, [x1, 2084]
	ldrb	w2, [x3, 24]
	cmp	w5, 1
	bfi	w2, w4, 5, 3
	cset	w4, ne
	bfi	w2, w4, 2, 3
	strb	w2, [x3, 24]
	ldr	w1, [x1, 2068]
	and	w1, w1, 7
	bl	SetAspectRatio
	ldr	w0, [x19, 2332]
	cmp	w0, 1
	beq	.L727
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4700]
	str	w1, [x0, 8]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4120]
	str	w1, [x0, 144]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4108]
	str	w1, [x0, 132]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4160]
	str	w1, [x0, 184]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4156]
	str	w1, [x0, 180]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4124]
	str	w1, [x0, 148]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4128]
	str	w1, [x0, 152]
	ldr	x1, [x19, 4048]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L733
	ldr	w3, [x19, 4108]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 252]
	cset	w3, ne
	bl	FSP_SetStoreType
.L733:
	ldr	x0, [x19, 2424]
	ldr	x4, [x19, 4048]
	ldr	w1, [x0, 72]
	str	w1, [x19, 4276]
	ldr	w3, [x0, 76]
	str	w3, [x19, 4280]
	ldr	w6, [x0, 80]
	str	w6, [x19, 4284]
	ldr	w5, [x0, 84]
	str	w5, [x19, 4288]
	ldr	w2, [x0, 64]
	sub	w1, w2, w1
	sub	w1, w1, w3
	str	w1, [x19, 4132]
	ldr	w3, [x0, 68]
	sub	w2, w3, w6
	sub	w2, w2, w5
	str	w2, [x19, 4136]
	ldr	w2, [x0, 60]
	str	w2, [x19, 4220]
	ldr	w2, [x0, 88]
	str	w2, [x19, 4224]
	ldr	w0, [x0, 96]
	str	w0, [x19, 4228]
	ldr	w0, [x4, 164]
	str	w0, [x19, 4140]
	ldr	w0, [x4, 168]
	str	w0, [x19, 4144]
	str	w1, [x4, 156]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4136]
	str	w1, [x0, 160]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4140]
	str	w1, [x0, 164]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4144]
	str	w1, [x0, 168]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4224]
	str	w1, [x0, 248]
	ldr	x0, [x19, 4048]
	ldr	w1, [x19, 4228]
	str	w1, [x0, 252]
	str	wzr, [x19, 4000]
.L727:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L740:
	ldr	w3, [x0, 156]
	cbnz	w3, .L728
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L728
	add	x0, x19, 8192
	ldrb	w0, [x0, 3664]
	cmp	w0, 1
	bne	.L728
	ldr	x3, [x19, 11888]
	ldr	x0, [x19, 11904]
	cmp	x3, x0
	bls	.L729
	sub	x4, x3, x0
	cmp	x4, 16
	bls	.L729
.L730:
	ldr	w3, [x19, 260]
	sub	w2, w2, w3
	add	x0, x0, x2, sxtw
	str	x0, [x19, 11888]
	b	.L728
.L729:
	cmp	x3, x0
	bcs	.L728
	sub	x3, x0, x3
	cmp	x3, 16
	bls	.L728
	b	.L730
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	3
.LC182:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x26, 4708]
	cmp	w3, 1
	beq	.L743
	cmp	w3, 2
	beq	.L759
	cbz	w3, .L758
	ldr	x2, .LC183
	mov	w0, 1
	ldr	x1, .LC185
	add	x2, x2, 280
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L746:
	ldr	x0, [x26, 2456]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L754
	mov	w0, 1
	str	w0, [x28]
	ldr	x0, [x26, 4048]
	add	x0, x0, 56
	str	x0, [x23, -8]
	.p2align 2
.L754:
	add	w27, w27, 1
	add	x28, x28, 4
	cmp	w27, w22
	add	x23, x23, 136
	bcc	.L756
.L759:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L758:
	mov	w22, 2
.L745:
	ldr	x21, .LC183
	add	x28, x26, 4096
	add	x28, x28, 660
	add	x23, x26, 2488
	add	x0, x21, 280
	mov	w27, 0
	str	x0, [x29, 104]
	.p2align 2
.L756:
	ldr	w1, [x28]
	cbz	w1, .L746
	ldr	x2, [x23, -8]
	cbnz	x2, .L760
	mov	x3, x23
	mov	w0, 0
	b	.L748
	.p2align 3
.L750:
	ldr	x24, [x3], 8
	cbnz	x24, .L765
.L748:
	add	w0, w0, 1
	cmp	w1, w0
	bne	.L750
	mov	w20, -1
.L749:
	ldr	x0, [x26, 2456]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L751
	ldr	x24, [x26, 4048]
	add	x24, x24, 56
.L747:
	mov	x0, x2
	uxtw	x25, w27
	mov	w19, 0
	lsl	x21, x25, 4
	cbz	x0, .L766
	.p2align 2
.L752:
	add	w19, w19, 1
	add	x0, x21, x25
	cmp	w1, w19
	add	x0, x0, x19, uxtw
	add	x0, x0, 310
	bls	.L754
	ldr	x0, [x26, x0, lsl 3]
	cbnz	x0, .L752
.L766:
	ldr	x1, .LC189
	mov	w4, w19
	ldr	x2, [x29, 104]
	mov	w5, w20
	mov	w3, w27
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x21, x25
	add	x0, x0, x19, uxtw
	add	x0, x0, 310
	str	x24, [x26, x0, lsl 3]
	ldr	w1, [x28]
	b	.L752
	.p2align 3
.L765:
	sxtb	w20, w0
	cmn	w20, #1
	ccmp	x24, xzr, 4, ne
	bne	.L747
	b	.L749
	.p2align 3
.L760:
	mov	x24, x2
	mov	w20, 0
	b	.L747
.L743:
	mov	w22, w3
	b	.L745
.L751:
	ldr	x2, .LC183
	mov	w3, w27
	ldr	x1, .LC187
	mov	w0, 1
	add	x2, x2, 280
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	3
.LC183:
	.xword	.LANCHOR0
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC187:
	.xword	.LC186
	.align	3
.LC189:
	.xword	.LC188
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L803
	ldr	x20, .LC191
	add	x21, x29, 48
	mov	x2, 272
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x20, 96]
	blr	x3
	ldr	w0, [x19, 2808]
	cbz	w0, .L804
	sub	w3, w0, #1
	mov	w5, 0
	add	x3, x3, 370
	add	x0, x19, 2952
	add	x3, x19, x3, lsl 3
	b	.L771
	.p2align 3
.L770:
	cmp	x0, x3
	beq	.L769
.L771:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L770
	ldr	w2, [x1, 60]
	cbnz	w2, .L770
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L770
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x5, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w5, w5, 1
	str	x1, [x2, 3824]
	bne	.L771
	.p2align 2
.L769:
	ldr	w0, [x19, 2812]
	cbz	w0, .L805
	sub	w3, w0, #1
	mov	w4, w5
	add	x3, x3, 387
	add	x0, x19, 3088
	add	x3, x19, x3, lsl 3
	b	.L774
	.p2align 3
.L773:
	cmp	x0, x3
	beq	.L832
.L774:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L773
	ldr	w2, [x1, 60]
	cbnz	w2, .L773
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L773
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x4, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w4, w4, 1
	str	x1, [x2, 3824]
	bne	.L774
	.p2align 2
.L832:
	sub	w6, w4, w5
.L772:
	ldr	w0, [x19, 2804]
	sub	w8, w4, #1
	cbz	w0, .L775
	sub	w2, w0, #1
	add	x0, x19, 3224
	add	x2, x2, 404
	add	x2, x19, x2, lsl 3
	b	.L777
	.p2align 3
.L776:
	cmp	x2, x0
	beq	.L833
.L777:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 1]
	cmp	w3, 1
	bne	.L776
	ldr	w3, [x1, 60]
	cmp	w3, 1
	bne	.L776
	ldr	w7, [x1, 64]
	add	x3, x29, 320
	add	x3, x3, x4, uxtw 3
	add	x1, x1, 56
	sub	x3, x3, #4096
	cbnz	w7, .L776
	str	x1, [x3, 3824]
	cmp	x2, x0
	add	w4, w4, 1
	bne	.L777
	.p2align 2
.L833:
	sub	w0, w4, w5
	sub	w0, w0, w6
.L775:
	cbz	w4, .L834
	ldr	w7, [x19, 4708]
	cbnz	w7, .L835
	cbz	w6, .L783
	add	x3, x21, 136
	add	w9, w6, w5
	mov	w1, w5
	.p2align 2
.L784:
	add	x2, x29, 320
	add	x2, x2, x1, uxtw 3
	add	w1, w1, 1
	sub	x2, x2, #4096
	cmp	w9, w1
	ldr	x2, [x2, 3824]
	str	x2, [x3], 8
	bne	.L784
.L783:
	cbz	w5, .L785
	mov	x1, 0
	.p2align 2
.L786:
	add	w2, w6, w1
	add	x9, x29, 320
	ldr	x3, [x21, x1, lsl 3]
	add	x1, x1, 1
	add	x2, x9, x2, lsl 3
	cmp	w5, w1
	str	x3, [x2, -136]
	bhi	.L786
	add	w6, w6, w5
.L785:
	cbz	w0, .L787
	add	w1, w0, w6
	mov	w2, w6
	.p2align 2
.L788:
	add	w3, w2, 1
	add	x0, x29, 320
	add	x5, x0, x2, uxtw 3
	sub	w0, w3, w6
	add	w0, w0, w8
	mov	w2, w3
	cmp	w1, w3
	add	x3, x29, 320
	add	x0, x3, x0, lsl 3
	sub	x0, x0, #4096
	ldr	x0, [x0, 3824]
	str	x0, [x5, -136]
	bne	.L788
.L787:
	ldr	w5, [x19, 4764]
	ldr	w8, [x19, 4768]
	str	w5, [x19, 4756]
	str	w8, [x19, 4760]
	cbnz	w5, .L781
	.p2align 2
.L801:
	cbz	w8, .L793
	add	x0, x19, 4096
	add	x3, x19, 2616
	add	x2, x0, 1820
	mov	w1, 0
	ldrb	w6, [x0, 1689]
	.p2align 2
.L796:
	cbz	w6, .L794
	ldr	w0, [x2]
.L795:
	add	x7, x29, 320
	add	w1, w1, 1
	add	x0, x7, x0, uxtw 3
	cmp	w1, w8
	add	x2, x2, 4
	ldr	x0, [x0, -136]
	str	x0, [x3], 8
	bne	.L796
	mov	w0, w5
.L792:
	cmp	w0, 16
	bhi	.L806
	.p2align 2
.L798:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 2480]
	add	w0, w0, 1
	cmp	w0, 16
	str	x2, [x1, 2480]
	bls	.L798
.L806:
	cmp	w8, 16
	mov	w0, w8
	bhi	.L799
	.p2align 2
.L800:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 2616]
	add	w0, w0, 1
	cmp	w0, 17
	str	x2, [x1, 2616]
	bne	.L800
.L799:
	mov	w0, 0
.L829:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L835:
	ldr	w5, [x19, 4764]
	ldr	w8, [x19, 4768]
	str	w5, [x19, 4756]
	str	w8, [x19, 4760]
	cbz	w5, .L836
.L781:
	add	x1, x19, 4096
	add	x3, x19, 2480
	add	x2, x1, 1692
	mov	w0, 0
	ldrb	w6, [x1, 1688]
	.p2align 2
.L791:
	cbz	w6, .L789
	ldr	w1, [x2]
.L790:
	add	x9, x29, 320
	add	w0, w0, 1
	add	x1, x9, x1, uxtw 3
	cmp	w0, w5
	sub	x1, x1, #4096
	add	x2, x2, 4
	ldr	x1, [x1, 3824]
	str	x1, [x3], 8
	bne	.L791
	cbnz	w7, .L792
	b	.L801
	.p2align 3
.L789:
	udiv	w1, w0, w4
	msub	w1, w1, w4, w0
	b	.L790
	.p2align 3
.L794:
	udiv	w0, w1, w4
	msub	w0, w0, w4, w1
	b	.L795
	.p2align 3
.L834:
	ldr	x3, [x20, 96]
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 2480
	str	wzr, [x19, 4756]
	str	wzr, [x19, 4760]
	blr	x3
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L799
	ldr	x1, [x19, 4048]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x19, 4756]
	add	x1, x1, 56
	str	x1, [x19, 2480]
	b	.L829
.L793:
	ldr	x3, [x20, 104]
	mov	x2, 136
	add	x1, x19, 2480
	add	x0, x19, 2616
	blr	x3
	ldr	w8, [x19, 4756]
	str	w8, [x19, 4760]
	mov	w0, w8
	b	.L792
.L804:
	mov	w5, 0
	b	.L769
.L805:
	mov	w4, w5
	mov	w6, 0
	b	.L772
.L836:
	mov	w0, 0
	b	.L798
.L803:
	mov	w0, -1
	b	.L829
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	3
.LC191:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4708]
	cmp	w0, 2
	beq	.L843
	mov	x0, x19
	bl	HEVC_InitListX
	cbnz	w0, .L844
	mov	x0, x19
	bl	HEVC_RepairList
	mov	w1, 0
	cbnz	w0, .L845
.L839:
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L843:
	str	wzr, [x19, 4756]
	mov	w1, 0
	str	wzr, [x19, 4760]
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L844:
	ldr	x1, .LC193
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L839
.L845:
	ldr	x1, .LC195
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L839
	.size	HEVC_DecList, .-HEVC_DecList
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ArrangeMem
	.type	HEVC_ArrangeMem, %function
HEVC_ArrangeMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2424]
	mov	w1, 8160
	ldr	w20, [x0, 128]
	ldr	w21, [x0, 192]
	ldr	w0, [x0, 188]
	lsl	w21, w21, w20
	sub	w2, w21, #32
	lsl	w20, w0, w20
	sub	w0, w20, #32
	cmp	w2, w1
	ccmp	w0, w1, 2, ls
	bhi	.L847
	ldr	x3, .LC196
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 2456]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L856
	ldrsb	w2, [x19, 2792]
	strb	w2, [x29, 57]
.L852:
	ldr	w0, [x19, 252]
	add	x1, x29, 56
	strb	w2, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L857
	ldr	x1, [x19, 2456]
	add	x3, x29, 52
	ldr	w0, [x19, 252]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
.L854:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L856:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 57]
	b	.L852
	.p2align 3
.L847:
	ldr	x2, .LC197
	mov	w4, w21
	ldr	x1, .LC199
	mov	w3, w20
	add	x2, x2, 296
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, -20
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L857:
	ldr	x2, .LC197
	mov	w0, 1
	ldr	x1, .LC201
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L854
	.size	HEVC_ArrangeMem, .-HEVC_ArrangeMem
	.align	3
.LC196:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC197:
	.xword	.LANCHOR0
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC201:
	.xword	.LC200
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x19, x20, uxtw 3
	ldr	x1, [x0, 2816]
	ldr	w4, [x1, 32]
	cbnz	w4, .L861
	ldr	w0, [x1, 24]
	cmp	w0, 15
	bhi	.L858
	add	x0, x19, x0, uxtw 2
	mov	w2, 16
	str	wzr, [x0, 13280]
	str	wzr, [x0, 13344]
	str	wzr, [x0, 13408]
	ldr	w0, [x1, 20]
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 2132]
	str	w2, [x1, 24]
	ldr	w0, [x19, 13276]
	sub	w0, w0, #1
	str	w0, [x19, 13276]
.L858:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L861:
	ldr	x2, .LC202
	mov	w3, w20
	ldr	x1, .LC204
	mov	w0, 1
	add	x2, x2, 312
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	3
.LC202:
	.xword	.LANCHOR0
	.align	3
.LC204:
	.xword	.LC203
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w1, [x20, 2796]
	cbnz	w1, .L867
	b	.L862
	.p2align 3
.L864:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L862
.L867:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 2816]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L864
	mov	w1, w19
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	ldr	w1, [x20, 2796]
	cmp	w1, w19
	bhi	.L867
.L862:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	w21, 1
	mov	w25, 0
	bl	_mcount
	ldr	w2, [x23, 4724]
	mov	w5, 1888
	ldr	x1, [x23, 2384]
	mov	w4, 12660
	ldr	x0, [x23, 2376]
	ldr	w3, [x23, 2796]
	smaddl	x1, w2, w5, x1
	ldr	w1, [x1, 32]
	smaddl	x0, w1, w4, x0
	ldr	w24, [x0, 116]
	lsl	w24, w21, w24
	cbz	w3, .L869
	add	x19, x23, 4096
	mov	w22, w21
	add	x19, x19, 1524
	b	.L900
	.p2align 3
.L872:
	add	w25, w25, 1
	cmp	w3, w25
	bls	.L869
.L900:
	add	x26, x23, x25, sxtw 3
	ldr	w0, [x23, 4720]
	ldr	x1, [x26, 2816]
	ldr	w2, [x1, 32]
	cmp	w2, w0
	bne	.L872
	ldp	w3, w0, [x19]
	ldr	w2, [x19, 8]
	add	w0, w3, w0
	cmp	w0, w2
	mov	w20, w0
	bcs	.L911
	ldr	w0, [x1, 8]
	mov	w4, 0
	.p2align 2
.L880:
	add	x2, x23, x20, sxtw 2
	ldr	w3, [x2, 4776]
	cbz	w3, .L875
	ldr	w3, [x1, 60]
	cbz	w3, .L876
	ldr	w3, [x2, 5720]
	cmp	w3, w0
	beq	.L910
.L876:
	cbnz	w4, .L908
	ldrb	w4, [x1, 1]
	ldr	w3, [x2, 5720]
	mov	w2, w0
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	beq	.L912
.L891:
	mov	w2, w0
	mov	w4, 0
.L879:
	ldr	w3, [x19, 8]
	add	w20, w20, 1
	mov	w0, w2
	cmp	w3, w20
	bhi	.L880
	ldp	w3, w0, [x19]
	add	w0, w3, w0
.L874:
	ldr	w5, [x23, 4700]
	cbz	w0, .L882
	mov	w20, 0
	.p2align 2
.L884:
	ldr	w0, [x1, 60]
	add	x3, x19, x20, sxtw 2
	add	w20, w20, 1
	cbnz	w0, .L883
	ldr	w0, [x3, 32]
	add	w0, w5, w0
	cmp	w0, w2
	beq	.L913
.L883:
	ldp	w3, w0, [x19]
	add	w0, w3, w0
	cmp	w0, w20
	bhi	.L884
.L882:
	cmp	w4, wzr
	ccmp	w2, w5, 4, eq
	beq	.L909
	strb	wzr, [x1, 1]
	ldr	x0, [x26, 2816]
	str	wzr, [x0, 60]
	ldr	x0, [x26, 2816]
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L909
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
.L909:
	ldr	w3, [x23, 2796]
	add	w25, w25, 1
	cmp	w3, w25
	bhi	.L900
.L869:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L875:
	ldr	w3, [x1, 60]
	cbz	w3, .L878
	sdiv	w3, w0, w24
	ldr	w6, [x2, 5720]
	sdiv	w5, w6, w24
	msub	w3, w3, w24, w0
	msub	w5, w5, w24, w6
	cmp	w3, w5
	bne	.L878
.L910:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2816]
	str	w21, [x0, 48]
	ldr	x0, [x26, 2816]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
	ldr	x1, [x26, 2816]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L879
	.p2align 3
.L878:
	cbnz	w4, .L908
	ldr	w4, [x2, 5720]
	sdiv	w2, w0, w24
	sdiv	w3, w4, w24
	msub	w2, w2, w24, w0
	msub	w3, w3, w24, w4
	ldrb	w4, [x1, 1]
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	bne	.L891
.L912:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2816]
	str	w21, [x0, 60]
	ldr	x0, [x26, 2816]
	str	w21, [x0, 48]
	ldr	x0, [x26, 2816]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
	ldr	x1, [x26, 2816]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L879
	.p2align 3
.L908:
	mov	w2, w0
	b	.L879
	.p2align 3
.L913:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2816]
	str	w21, [x0, 48]
	ldr	x1, [x26, 2816]
	ldr	w0, [x23, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x26, 2816]
	mov	w4, 1
	ldr	w5, [x23, 4700]
	ldr	w2, [x1, 8]
	b	.L883
.L911:
	mov	w4, 0
	ldr	w2, [x1, 8]
	b	.L874
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 4716]
	sub	w0, w0, #19
	cmp	w0, 2
	bls	.L916
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L916:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L918
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.8
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L918:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 12288
	add	x5, x19, 24576
	add	x2, x2, 1184
	add	x5, x5, 3136
	mov	w0, 0
	.p2align 2
.L925:
	ldr	w1, [x2, 48]
	cbnz	w1, .L921
	cbz	x2, .L922
	ldr	w4, [x19, 2796]
	cbz	w4, .L922
	ldr	x1, [x19, 2816]
	cmp	x1, x2
	beq	.L921
	sub	w4, w4, #1
	mov	x1, x19
	add	x4, x19, x4, lsl 3
	b	.L923
	.p2align 3
.L924:
	ldr	x3, [x1, 2816]
	cmp	x3, x2
	beq	.L921
.L923:
	cmp	x4, x1
	add	x1, x1, 8
	bne	.L924
.L922:
	add	w0, w0, 1
.L921:
	add	x2, x2, 712
	cmp	x2, x5
	bne	.L925
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 5620]
	cbz	w1, .L955
	add	x24, x20, 4096
	mov	w22, 0
	mov	w21, 0
	add	x23, x24, 1524
	mov	w26, 1
	mov	w25, 1
	.p2align 2
.L941:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L937
	add	x0, x0, 8
	ldr	w5, [x20, 2796]
	ldr	w4, [x20, 4700]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L937
	add	x1, x20, 2816
	mov	w0, 0
	b	.L940
	.p2align 3
.L938:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L937
.L940:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L938
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 4720]
	cmp	w6, w3
	bne	.L938
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 2816]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L983
.L939:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 2816]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 2816]
	str	x1, [x0, 2952]
	.p2align 2
.L937:
	ldr	w1, [x23]
	add	w21, w21, 1
	cmp	w1, w21
	bhi	.L941
.L936:
	ldr	w0, [x20, 2792]
	str	w22, [x20, 2808]
	cmp	w0, w22
	bls	.L946
	.p2align 2
.L970:
	add	x2, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w22, w0
	str	xzr, [x2, 2952]
	bne	.L970
.L946:
	add	x23, x24, 1524
	mov	w22, 0
	mov	w26, 1
	mov	w25, 1
	ldr	w24, [x23, 4]
	add	w24, w1, w24
	cmp	w24, w21
	bls	.L944
	.p2align 2
.L969:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L947
	add	x0, x0, 8
	ldr	w5, [x20, 2796]
	ldr	w4, [x20, 4700]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L947
	add	x1, x20, 2816
	mov	w0, 0
	b	.L950
	.p2align 3
.L948:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L947
.L950:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L948
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 4720]
	cmp	w6, w3
	bne	.L948
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 2816]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L984
.L949:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 2816]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 2816]
	str	x1, [x0, 3088]
	.p2align 2
.L947:
	add	w21, w21, 1
	cmp	w24, w21
	bhi	.L969
	ldr	w0, [x20, 2792]
.L944:
	cmp	w0, w22
	str	w22, [x20, 2812]
	bls	.L935
	.p2align 2
.L968:
	add	x1, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w0, w22
	str	xzr, [x1, 3088]
	bne	.L968
.L935:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L983:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	ldr	x0, [x19, 2816]
	b	.L939
.L984:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	ldr	x0, [x19, 2816]
	b	.L949
.L955:
	mov	w22, 0
	mov	w21, 0
	add	x24, x20, 4096
	b	.L936
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 4724]
	mov	w2, 1888
	ldr	x0, [x19, 2384]
	mov	w5, 12660
	ldr	w6, [x19, 5620]
	add	x1, x19, 4096
	ldr	w9, [x19, 5628]
	add	x1, x1, 1524
	smaddl	x2, w3, w2, x0
	ldr	w0, [x19, 5624]
	sub	w9, w9, #1
	ldr	x4, [x19, 2376]
	mov	w3, 1
	ldr	w2, [x2, 32]
	add	w0, w6, w0
	sub	w0, w0, #1
	cmp	w9, w0
	smaddl	x0, w2, w5, x4
	ldr	w0, [x0, 116]
	lsl	w0, w3, w0
	ble	.L995
	mov	w10, 0
	mov	x11, x1
	sub	w7, w0, #1
	mov	w13, w3
	mov	w12, w3
	.p2align 2
.L992:
	sxtw	x0, w9
	add	x1, x11, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L987
	add	x0, x19, x0, lsl 2
	ldr	w8, [x19, 2796]
	ldr	w6, [x0, 4776]
	ldr	w5, [x0, 5720]
	uxtb	w6, w6
	and	w0, w5, w7
	cmp	w6, wzr
	csel	w5, w0, w5, eq
	cmp	w8, wzr
	ble	.L987
	add	x2, x19, 2816
	mov	w1, 0
	b	.L991
	.p2align 3
.L990:
	add	w1, w1, 1
	cmp	w1, w8
	beq	.L987
.L991:
	ldr	x3, [x2]
	cmp	w6, wzr
	add	x2, x2, 8
	ldr	w0, [x3, 8]
	and	w4, w0, w7
	csel	w0, w4, w0, eq
	cmp	w5, w0
	bne	.L990
	ldr	w4, [x3, 32]
	ldr	w0, [x19, 4720]
	cmp	w4, w0
	bne	.L990
	add	x1, x19, x1, sxtw 3
	strb	w13, [x3, 1]
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	ldr	x2, [x1, 2816]
	str	wzr, [x2, 64]
	ldr	x2, [x1, 2816]
	str	w12, [x2, 60]
	ldr	x1, [x1, 2816]
	str	x1, [x0, 3224]
	.p2align 2
.L987:
	ldp	w1, w0, [x11]
	sub	w9, w9, #1
	add	w0, w1, w0
	sub	w0, w0, #1
	cmp	w0, w9
	blt	.L992
	mov	w0, w10
.L986:
	ldr	w1, [x19, 2792]
	str	w0, [x19, 2804]
	cmp	w1, w10
	ble	.L985
	.p2align 2
.L998:
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	cmp	w10, w1
	str	xzr, [x0, 3224]
	bne	.L998
.L985:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L995:
	mov	w0, 0
	mov	w10, 0
	b	.L986
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x23, x1
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1022
	ldr	w20, [x22, 3992]
	uxtw	x21, w20
	lsl	x0, x21, 2
	sub	x0, x0, x21
	add	x0, x21, x0, lsl 3
	add	x0, x22, x0, lsl 3
	ldr	w2, [x0, 13272]
	cbz	w2, .L1006
	ldr	w0, [x0, 13280]
	cbz	w0, .L1023
	mov	w0, 200
	mov	x1, 13284
	mov	w19, 0
	umaddl	x0, w20, w0, x1
	add	x0, x22, x0
	b	.L1009
	.p2align 3
.L1012:
	ldr	w1, [x0], 4
	cbz	w1, .L1007
.L1009:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L1012
.L1006:
	ldr	x1, .LC214
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1019:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1023:
	mov	w19, 0
	.p2align 2
.L1007:
	ldr	w0, [x22, 252]
	ldr	w1, [x23, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1010
	ldr	x1, [x0, 32]
	cbz	x1, .L1010
	uxtw	x3, w19
	mov	w4, 50
	mov	w2, 1
	lsl	x1, x21, 2
	umaddl	x20, w20, w4, x3
	sub	x1, x1, x21
	mov	w3, w19
	add	x20, x22, x20, lsl 2
	add	x21, x21, x1, lsl 3
	ldr	x1, .LC210
	add	x22, x22, x21, lsl 3
	str	w2, [x20, 13280]
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 13344]
	ldr	w0, [x23, 8]
	str	w0, [x20, 13408]
	mov	w0, 13
	ldr	w2, [x22, 13276]
	add	w2, w2, 1
	str	w2, [x22, 13276]
	ldr	w2, [x23, 228]
	bl	dprint_vfmw
	str	w19, [x23, 24]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1010:
	ldrb	w4, [x23, 1]
	mov	x5, x0
	ldr	x1, .LC212
	mov	x6, 0
	ldr	w3, [x23, 8]
	mov	w0, 0
	ldr	w2, [x23, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1019
.L1022:
	ldr	x2, .LC206
	mov	w3, 11486
	ldr	x1, .LC208
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1019
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC208:
	.xword	.LC207
	.align	3
.LC210:
	.xword	.LC209
	.align	3
.LC212:
	.xword	.LC211
	.align	3
.LC214:
	.xword	.LC213
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	cbz	x0, .L1025
	ldrsb	w4, [x0, 1]
	cmp	w4, 3
	ccmp	w4, wzr, 4, ne
	beq	.L1045
	ldr	w0, [x19, 52]
	cmp	w0, 1
	beq	.L1031
	ldr	w4, [x19, 48]
	ldrb	w5, [x19]
	cbz	w4, .L1030
	cmp	w5, 1
	mov	w0, 0
	beq	.L1030
.L1039:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1045:
	ldr	x2, .LC215
	mov	w0, 13
	ldr	x1, .LC217
	ldr	w3, [x19, 28]
	add	x2, x2, 336
	bl	dprint_vfmw
.L1027:
	ldr	w0, [x19, 52]
	cmp	w0, 1
	bne	.L1046
.L1031:
	mov	w1, 1
	mov	w0, 2
	strb	w1, [x19, 2]
	str	w0, [x19, 52]
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1025:
	ldr	x1, .LC219
	mov	x2, x19
	ldr	w3, [x19, 8]
	mov	w0, 1
	ldr	w5, [x19, 28]
	ldr	w4, [x19, 52]
	bl	dprint_vfmw
	b	.L1027
.L1046:
	ldr	x2, .LC215
	mov	w0, 1
	ldr	x1, .LC221
	ldr	w3, [x19, 8]
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -3
	b	.L1039
	.p2align 3
.L1030:
	ldr	x2, .LC215
	mov	x3, x19
	ldr	x1, .LC223
	mov	w0, 1
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1039
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	3
.LC215:
	.xword	.LANCHOR0
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC223:
	.xword	.LC222
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w23, [x21, 12]
	ldr	x0, [x21, 664]
	cmn	x0, #1
	beq	.L1049
	ldr	w1, [x20, 2796]
	cbz	w1, .L1049
	mov	w25, -1
	mov	x24, -2
	mov	w19, 0
	b	.L1052
	.p2align 3
.L1087:
	ldr	x0, [x22, 2816]
	ldr	w1, [x20, 2796]
	ldr	x0, [x0, 664]
	cmp	x0, x24
	bcs	.L1051
	mov	w25, w19
	mov	x24, x0
.L1051:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1089
.L1052:
	add	x22, x20, x19, sxtw 3
	ldr	x0, [x22, 2816]
	cbz	x0, .L1051
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	cbz	x0, .L1088
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	bne	.L1087
.L1088:
	ldr	w1, [x20, 2796]
	add	w19, w19, 1
	cmp	w1, w19
	bhi	.L1052
.L1089:
	cmn	w25, #1
	beq	.L1049
	ldr	x1, [x21, 664]
	cmp	x1, x24
	bhi	.L1090
.L1049:
	ldrb	w0, [x21, 145]
	ldrb	w1, [x21, 144]
	and	w0, w0, -64
	strb	w0, [x21, 145]
	and	w1, w1, -4
	strb	w1, [x21, 144]
	ldr	w2, [x20, 144]
	str	w2, [x21, 188]
	ldr	x2, [x20, 2416]
	ldrh	w2, [x2, 124]
	cmp	w2, 1
	beq	.L1060
	cmp	w2, 257
	bne	.L1061
	ldr	w2, [x20, 3372]
	cmp	w2, 1
	cset	w4, ne
.L1053:
	ldr	x3, [x20, 2424]
	mov	w2, 3
	ldrb	w3, [x3, 2066]
	cbz	w3, .L1054
	ldr	w3, [x21, 40]
	mov	w2, 1
	cmp	w3, w2
	ccmp	w3, 11, 4, ne
	cset	w4, eq
	cbz	w4, .L1091
.L1055:
	ldr	w3, [x21, 44]
	cmp	w3, wzr
	cset	w4, eq
.L1054:
	mov	w3, 2
	ldrb	w6, [x21, 3]
	bfi	w0, w3, 4, 2
	ldrb	w3, [x21, 146]
	bfi	w0, w2, 2, 2
	ldrb	w5, [x21, 4]
	ldr	w2, [x21, 48]
	bfi	w0, w4, 0, 2
	bfi	w1, w23, 0, 2
	bfi	w3, w6, 1, 1
	strb	w0, [x21, 145]
	strb	w1, [x21, 144]
	strb	w3, [x21, 146]
	str	w5, [x21, 200]
	cbz	w2, .L1056
	ldr	w0, [x21, 16]
	str	w0, [x21, 232]
.L1056:
	ldr	x0, [x20, 2456]
	ldr	w1, [x21, 28]
	ldr	w0, [x0, 636]
	str	w0, [x21, 204]
	ldr	x0, [x20, 2456]
	ldr	w0, [x0, 640]
	str	w0, [x21, 208]
	ldr	x0, [x20, 2456]
	ldr	w0, [x0, 644]
	str	w0, [x21, 212]
	ldr	w0, [x20, 252]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1047
	ldr	x3, .LC226
	mov	x2, 632
	add	x1, x21, 80
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 16
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 1
	ldr	w2, [x21, 56]
	strb	w1, [x19, 291]
	cmp	w2, wzr
	strb	w1, [x19, 289]
	csel	w0, w0, wzr, ne
	strb	w0, [x19, 284]
	ldr	w0, [x21, 68]
	str	w0, [x19, 236]
.L1047:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1090:
	ldr	w0, [x20, 252]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L1049
	ldr	x1, .LC225
	mov	x3, x24
	ldr	x2, [x21, 664]
	mov	w0, 29
	add	x25, x20, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x25, 2816]
	ldr	x1, [x21, 664]
	str	x1, [x0, 664]
	str	x24, [x21, 664]
	b	.L1049
	.p2align 3
.L1091:
	mov	w4, 2
	and	w3, w3, -9
	mov	w2, 3
	cmp	w3, w4
	csel	w2, w2, w4, ne
	b	.L1055
	.p2align 3
.L1060:
	mov	w4, 0
	b	.L1053
	.p2align 3
.L1061:
	mov	w4, 1
	b	.L1053
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC226:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 19
	bhi	.L1094
	uxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x2, x0, 4
	sub	x0, x2, x0
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x0, x20, x0, lsl 3
	add	x0, x0, 12288
	ldrb	w0, [x0, 1185]
	cmp	w0, wzr
	cset	w0, ne
.L1093:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1094:
	mov	w0, -1
	b	.L1093
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	w0, [x21, 252]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L1100
	ldrsb	w1, [x0, 1]
	add	x19, x0, 592
	add	x20, x0, 624
	cbz	w1, .L1106
.L1103:
	ldr	x2, [x19]
	mov	x1, x2
	cbz	x2, .L1098
	ldr	w0, [x21, 252]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1098:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L1103
	ldr	w0, [x21, 252]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L1096:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1106:
	ldr	x1, .LC228
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1096
.L1100:
	mov	w0, -1
	b	.L1096
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	3
.LC228:
	.xword	.LC227
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1MasteringDisplayInfo
	.type	HEVC_GetSLHDR1MasteringDisplayInfo, %function
HEVC_GetSLHDR1MasteringDisplayInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x1, x19, 568
	mov	w2, 14999
	ldr	w0, [x1, 4]
	cmp	w0, w2
	bhi	.L1111
	sub	w2, w0, #8192
	mov	w3, 4749
	sub	w2, w2, #308
	cmp	w2, w3
	bhi	.L1110
	mov	w0, 1
	strb	w0, [x20, 3]
	b	.L1109
	.p2align 3
.L1110:
	sub	w0, w0, #12288
	sub	w0, w0, #962
	cmp	w0, 1749
	bls	.L1114
.L1111:
	strb	wzr, [x20, 3]
.L1109:
	ldr	w2, [x1, 36]
	mov	w0, 56963
	movk	w0, 0x431b, lsl 16
	mov	w3, 10000
	add	w2, w2, 249856
	mov	w5, 2063
	add	w2, w2, 144
	movk	w5, 0x5f6, lsl 16
	mov	w4, w3
	umull	x2, w2, w0
	lsr	x2, x2, 32
	lsr	w2, w2, 17
	lsl	w0, w2, 3
	sub	w0, w0, w2
	add	w2, w2, w0, lsl 3
	sub	w0, w2, w0
	cmp	w0, w3
	csel	w0, w0, w3, ls
	strh	w0, [x20, 4]
	ldr	w0, [x1, 40]
	cmp	w0, w5
	bhi	.L1112
	mov	w1, 5977
	movk	w1, 0xd1b7, lsl 16
	umull	x0, w0, w1
	ubfx	x4, x0, 45, 16
.L1112:
	strh	w4, [x20, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1114:
	mov	w0, 2
	strb	w0, [x20, 3]
	b	.L1109
	.size	HEVC_GetSLHDR1MasteringDisplayInfo, .-HEVC_GetSLHDR1MasteringDisplayInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintSLHDR1Info
	.type	HEVC_PrintSLHDR1Info, %function
HEVC_PrintSLHDR1Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x21]
	mov	w0, 32
	ldr	x1, .LC230
	bl	dprint_vfmw
	ldrb	w2, [x21, 1]
	mov	w0, 32
	ldr	x1, .LC232
	bl	dprint_vfmw
	ldrb	w2, [x21, 2]
	mov	w0, 32
	ldr	x1, .LC234
	bl	dprint_vfmw
	ldrb	w2, [x21, 3]
	mov	w0, 32
	ldr	x1, .LC236
	bl	dprint_vfmw
	ldrh	w2, [x21, 4]
	mov	w0, 32
	ldr	x1, .LC238
	bl	dprint_vfmw
	ldrh	w2, [x21, 6]
	mov	w0, 32
	ldr	x1, .LC240
	bl	dprint_vfmw
	ldrb	w2, [x21, 8]
	mov	w0, 32
	ldr	x1, .LC242
	bl	dprint_vfmw
	ldrb	w2, [x21, 9]
	mov	w0, 32
	ldr	x1, .LC244
	bl	dprint_vfmw
	ldrb	w0, [x21, 1]
	ldrb	w2, [x21, 10]
	cbnz	w0, .L1116
	ldr	x1, .LC246
	add	x19, x21, 10
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w2, [x19, 1]
	mov	w0, 32
	ldr	x1, .LC248
	bl	dprint_vfmw
	ldrb	w2, [x19, 2]
	mov	w0, 32
	ldr	x1, .LC250
	bl	dprint_vfmw
	ldrb	w2, [x19, 3]
	mov	w0, 32
	ldr	x1, .LC252
	bl	dprint_vfmw
	ldrb	w2, [x19, 4]
	mov	w0, 32
	ldr	x1, .LC254
	bl	dprint_vfmw
	ldrb	w2, [x19, 5]
	mov	w0, 32
	ldr	x1, .LC256
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cbz	w0, .L1121
	ldr	x23, .LC260
	mov	w20, 0
	ldr	x22, .LC262
	.p2align 2
.L1120:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 6]
	bl	dprint_vfmw
	ldrb	w2, [x21, 17]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cmp	w0, w20
	bhi	.L1120
.L1121:
	ldrb	w2, [x19, 28]
	mov	w0, 32
	ldr	x1, .LC258
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cbz	w0, .L1122
	ldr	x23, .LC264
	mov	w20, 0
	ldr	x22, .LC266
	.p2align 2
.L1123:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 29]
	bl	dprint_vfmw
	ldrb	w2, [x21, 36]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cmp	w0, w20
	bhi	.L1123
.L1122:
	ldr	x1, .LC284
	mov	x2, 290
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1116:
	ldr	x1, .LC268
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21, 10]
	cbz	w0, .L1134
	ldr	x24, .LC272
	mov	w20, 0
	ldr	x23, .LC274
	add	x19, x21, 10
	.p2align 2
.L1127:
	add	x22, x21, x20, uxtw 1
	mov	w2, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w3, [x22, 12]
	bl	dprint_vfmw
	ldrh	w3, [x22, 80]
	mov	w2, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19]
	cmp	w0, w20
	bhi	.L1127
.L1128:
	ldrb	w2, [x19, 138]
	mov	w0, 32
	ldr	x1, .LC270
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cbz	w0, .L1126
	ldr	x24, .LC280
	mov	w20, 0
	ldr	x23, .LC282
	.p2align 2
.L1129:
	add	x22, x21, x20, uxtw 1
	mov	w3, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w2, [x22, 150]
	bl	dprint_vfmw
	ldrh	w2, [x22, 218]
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cmp	w0, w20
	bhi	.L1129
.L1126:
	ldrh	w2, [x19, 276]
	mov	w0, 32
	ldr	x1, .LC276
	bl	dprint_vfmw
	ldrh	w2, [x19, 278]
	mov	w0, 32
	ldr	x1, .LC278
	bl	dprint_vfmw
	b	.L1122
.L1134:
	add	x19, x21, 10
	b	.L1128
	.size	HEVC_PrintSLHDR1Info, .-HEVC_PrintSLHDR1Info
	.align	3
.LC230:
	.xword	.LC229
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
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC242:
	.xword	.LC241
	.align	3
.LC244:
	.xword	.LC243
	.align	3
.LC246:
	.xword	.LC245
	.align	3
.LC248:
	.xword	.LC247
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.align	3
.LC254:
	.xword	.LC253
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC260:
	.xword	.LC259
	.align	3
.LC262:
	.xword	.LC261
	.align	3
.LC264:
	.xword	.LC263
	.align	3
.LC266:
	.xword	.LC265
	.align	3
.LC268:
	.xword	.LC267
	.align	3
.LC270:
	.xword	.LC269
	.align	3
.LC272:
	.xword	.LC271
	.align	3
.LC274:
	.xword	.LC273
	.align	3
.LC276:
	.xword	.LC275
	.align	3
.LC278:
	.xword	.LC277
	.align	3
.LC280:
	.xword	.LC279
	.align	3
.LC282:
	.xword	.LC281
	.align	3
.LC284:
	.xword	.LC283
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1Info
	.type	HEVC_GetSLHDR1Info, %function
HEVC_GetSLHDR1Info:
	stp	x29, x30, [sp, -352]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	mov	x2, 290
	mov	w1, 0
	add	x0, x29, 56
	bl	memset
	ldrb	w3, [x21, 1]
	ldrb	w4, [x19, 56]
	ldrb	w5, [x19, 568]
	cbz	w3, .L1175
	cbnz	w4, .L1178
.L1175:
	ldrb	w6, [x19, 59]
	ldrb	w7, [x19, 128]
.L1137:
	ldr	x2, .LC285
	mov	w0, 22
	ldr	x1, .LC287
	add	x2, x2, 360
	bl	dprint_vfmw
	strb	wzr, [x20, 466]
.L1135:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 352
	ret
	.p2align 3
.L1178:
	cbz	w5, .L1175
	ldrb	w0, [x19, 59]
	cbnz	w0, .L1140
	ldrb	w7, [x19, 128]
	cbz	w7, .L1179
.L1140:
	mov	w0, 1
	strb	w0, [x20, 466]
	ldr	w1, [x21, 24]
	ldrb	w3, [x19, 57]
	ldrb	w2, [x19, 58]
	cmp	w1, 9
	strb	w3, [x29, 56]
	strb	w2, [x29, 57]
	beq	.L1180
.L1142:
	ldrb	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1143
	ldrb	w1, [x19, 129]
	cmp	w1, 1
	beq	.L1143
	cmp	w1, 9
	ccmp	w0, 9, 4, ne
	beq	.L1181
	ldrb	w0, [x29, 64]
	strb	w0, [x29, 58]
.L1143:
	mov	x1, x19
	add	x0, x29, 56
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	w1, [x29, 64]
	ldrb	w0, [x29, 58]
	cmp	w1, w0
	beq	.L1182
	strb	wzr, [x29, 65]
.L1146:
	ldrb	w0, [x29, 57]
	cbnz	w0, .L1147
	add	x5, x19, 59
	ldrb	w6, [x5, 2]
	ldrb	w4, [x5, 3]
	ldrb	w3, [x5, 4]
	ldrb	w2, [x5, 5]
	ldrb	w1, [x5, 6]
	ldrb	w0, [x5, 7]
	strb	w6, [x29, 66]
	strb	w4, [x29, 67]
	strb	w3, [x29, 68]
	strb	w2, [x29, 69]
	strb	w1, [x29, 70]
	strb	w0, [x29, 71]
	cbz	w0, .L1152
	sub	w4, w0, #1
	add	x2, x29, 56
	add	x4, x4, 17
	add	x0, x29, 72
	add	x1, x19, 82
	add	x4, x2, x4
	.p2align 2
.L1151:
	ldrb	w3, [x1, -15]
	add	x0, x0, 1
	ldrb	w2, [x1], 1
	strb	w3, [x0, -1]
	strb	w2, [x0, 10]
	cmp	x0, x4
	bne	.L1151
.L1152:
	ldrb	w0, [x5, 38]
	strb	w0, [x29, 94]
	cbz	w0, .L1150
	sub	w3, w0, #1
	add	x1, x29, 56
	add	x3, x3, 40
	add	x0, x29, 95
	add	x19, x19, 113
	add	x3, x1, x3
	.p2align 2
.L1155:
	ldrb	w2, [x19, -15]
	add	x0, x0, 1
	ldrb	w1, [x19], 1
	strb	w2, [x0, -1]
	strb	w1, [x0, 6]
	cmp	x0, x3
	bne	.L1155
.L1150:
	ldr	w0, [x20, 472]
	cbnz	w0, .L1183
	ldr	x2, .LC285
	mov	w0, 1
	ldr	x1, .LC289
	add	x2, x2, 360
	bl	dprint_vfmw
	b	.L1135
	.p2align 3
.L1147:
	add	x5, x19, 128
	ldrb	w0, [x5, 40]
	add	w0, w0, 1
	ldp	w2, w1, [x5, 8]
	uxtb	w0, w0
	strh	w2, [x29, 342]
	strb	w0, [x29, 66]
	strh	w1, [x29, 344]
	cbz	w0, .L1159
	sub	w2, w0, #1
	add	x1, x29, 68
	add	x2, x2, 87
	add	x0, x19, 172
	add	x2, x19, x2, lsl 1
	.p2align 2
.L1158:
	ldrh	w4, [x0]
	add	x0, x0, 2
	ldrh	w3, [x0, 196]
	cmp	x0, x2
	strh	w4, [x1]
	add	x1, x1, 2
	strh	w3, [x1, 66]
	bne	.L1158
.L1159:
	ldrb	w0, [x5, 41]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x29, 204]
	cbz	w0, .L1150
	sub	w2, w0, #1
	add	x1, x29, 206
	add	x2, x2, 120
	add	x0, x19, 238
	add	x19, x19, x2, lsl 1
	.p2align 2
.L1160:
	ldrh	w3, [x0]
	add	x0, x0, 2
	ldrh	w2, [x0, 196]
	cmp	x0, x19
	strh	w3, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 66]
	bne	.L1160
	b	.L1150
	.p2align 3
.L1183:
	ldr	x3, .LC290
	mov	x2, 290
	ldr	x0, [x20, 480]
	add	x1, x29, 56
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 290
	str	w0, [x20, 468]
	b	.L1135
	.p2align 3
.L1179:
	mov	w6, 0
	b	.L1137
	.p2align 3
.L1181:
	mov	w0, 1
	strb	w0, [x29, 58]
	b	.L1143
	.p2align 3
.L1182:
	ldrb	w0, [x29, 59]
	strb	w0, [x29, 65]
	b	.L1146
	.p2align 3
.L1180:
	ldr	w1, [x21, 32]
	cmp	w1, 9
	bne	.L1142
	strb	w0, [x29, 64]
	b	.L1142
	.size	HEVC_GetSLHDR1Info, .-HEVC_GetSLHDR1Info
	.align	3
.LC285:
	.xword	.LANCHOR0
	.align	3
.LC287:
	.xword	.LC286
	.align	3
.LC289:
	.xword	.LC288
	.align	3
.LC290:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ConvertHDRInfo
	.type	HEVC_ConvertHDRInfo, %function
HEVC_ConvertHDRInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	x19, x2
	bl	_mcount
	add	x3, x21, 464
	add	x0, x19, 572
	ldrb	w1, [x20]
	add	x2, x21, 496
	add	x4, x19, 584
	strb	w1, [x3, 24]
	ldr	w1, [x20, 24]
	strb	w1, [x3, 25]
	ldr	w1, [x20, 32]
	strb	w1, [x3, 26]
	ldr	w1, [x20, 28]
	str	w1, [x3, 28]
	ldrb	w1, [x19, 568]
	strb	w1, [x21, 464]
.L1185:
	ldr	w1, [x0]
	add	x0, x0, 4
	strh	w1, [x2]
	add	x2, x2, 2
	cmp	x0, x4
	ldr	w1, [x0, 8]
	strh	w1, [x2, 4]
	bne	.L1185
	ldr	w0, [x19, 596]
	mov	x2, x19
	strh	w0, [x3, 44]
	mov	x1, x20
	mov	x0, x21
	ldr	w4, [x19, 600]
	strh	w4, [x3, 46]
	ldr	w4, [x19, 604]
	str	w4, [x3, 48]
	ldr	w4, [x19, 608]
	str	w4, [x3, 52]
	ldrb	w4, [x19, 612]
	strb	w4, [x3, 1]
	ldrh	w4, [x19, 614]
	str	w4, [x3, 56]
	ldrh	w4, [x19, 616]
	str	w4, [x3, 60]
	ldrb	w4, [x19, 618]
	strb	w4, [x3, 64]
	bl	HEVC_GetSLHDR1Info
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ConvertHDRInfo, .-HEVC_ConvertHDRInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	bl	_mcount
	add	x19, x19, 1184
	ldr	w1, [x20, 4724]
	mov	w5, 1888
	ldr	x0, [x20, 2384]
	mov	w4, 12660
	ldr	x2, [x20, 2376]
	mov	x3, 0
	smaddl	x0, w1, w5, x0
	ldr	w21, [x0, 32]
	strb	wzr, [x20, 3985]
	smaddl	x21, w21, w4, x2
	.p2align 2
.L1193:
	ldr	w0, [x19, 48]
	cbnz	w0, .L1188
	cbz	x19, .L1189
	ldr	w2, [x20, 2796]
	cbz	w2, .L1189
	ldr	x0, [x20, 2816]
	cmp	x0, x19
	beq	.L1188
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L1191
	.p2align 3
.L1192:
	ldr	x1, [x0, 2816]
	cmp	x1, x19
	beq	.L1188
.L1191:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L1192
.L1189:
	lsl	x22, x3, 2
	mov	w0, 101
	sub	x22, x22, x3
	str	w0, [x20, 4024]
	lsl	x0, x22, 4
	mov	w1, 1
	sub	x22, x0, x22
	add	x23, x20, 4056
	lsl	x22, x22, x1
	strb	w1, [x20, 3985]
	sub	x3, x22, x3
	mov	x2, 632
	mov	x0, x23
	add	x22, x20, x3, lsl 3
	add	x24, x22, 12288
	add	x1, x24, 1264
	bl	memcpy
	str	x19, [x20, 4048]
	str	wzr, [x20, 4208]
	str	wzr, [x22, 13488]
	strb	wzr, [x24, 1186]
	strb	wzr, [x19]
	ldr	x0, [x20, 4048]
	str	wzr, [x0, 60]
	ldr	x0, [x20, 4048]
	str	wzr, [x0, 64]
	ldr	x0, [x20, 4048]
	str	wzr, [x0, 52]
	ldrb	w1, [x20, 3985]
	cmp	w1, 1
	bne	.L1197
	ldr	w0, [x20, 252]
	bl	FSP_NewLogicFs
	mov	w24, w0
	mov	w1, w0
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	mov	x22, x0
	cmp	w24, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L1195
	add	x2, x20, 3360
	add	x1, x21, 2064
	add	x19, x0, 48
	bl	HEVC_ConvertHDRInfo
	ldr	x0, [x20, 2456]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1210
.L1196:
	ldr	x21, .LC293
	mov	x2, 632
	ldr	x0, [x20, 4048]
	mov	x1, x19
	ldr	x3, [x21, 104]
	add	x0, x0, 80
	blr	x3
	ldr	x1, [x20, 4048]
	mov	x2, 632
	ldr	x3, [x21, 104]
	mov	x0, x23
	add	x1, x1, 80
	blr	x3
	ldr	x1, [x20, 4048]
	mov	w0, 0
	str	w24, [x1, 28]
	ldrsb	w1, [x22, 4]
	str	w1, [x20, 4020]
.L1208:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1188:
	add	w3, w3, 1
	add	x19, x19, 712
	cmp	w3, 20
	bne	.L1193
.L1197:
	ldr	x1, .LC292
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1210:
	ldr	x2, [x20, 2424]
	ldr	w21, [x19, 112]
	ldr	w1, [x19, 36]
	ldr	w0, [x2, 68]
	ldr	w2, [x2, 64]
	stp	w2, w0, [x19, 68]
	mul	w21, w0, w21
	stp	wzr, wzr, [x19, 240]
	add	w0, w21, w1
	str	wzr, [x19, 256]
	stp	wzr, wzr, [x19, 248]
	str	w0, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w1, [x19, 20]
	ldr	w2, [x19, 116]
	add	w0, w21, w1
	str	w0, [x19, 24]
	add	w0, w2, w0
	str	w0, [x19, 32]
	b	.L1196
.L1195:
	ldr	x1, .LC295
	mov	w0, 0
	strb	wzr, [x20, 3985]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1208
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC293:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC295:
	.xword	.LC294
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x20, 252]
	bl	FSP_GetFspType
	cmn	w0, #1
	mov	w21, w0
	bne	.L1217
	b	.L1219
	.p2align 3
.L1214:
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1216
	cmp	w19, 32
	beq	.L1220
.L1217:
	ldr	w0, [x20, 252]
	mov	w1, w19
	add	w19, w19, 1
	bl	FSP_GetLogicFs
	cbnz	x0, .L1214
	ldr	x1, .LC299
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1219:
	ldr	x1, .LC297
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1216:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1220:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	3
.LC297:
	.xword	.LC296
	.align	3
.LC299:
	.xword	.LC298
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	add	x23, x22, 24576
	bl	_mcount
	add	x20, x20, 1185
	add	x0, x22, 4096
	add	x23, x23, 3137
	add	x0, x0, 1952
	bl	ResetVoQueue
	.p2align 2
.L1224:
	strb	wzr, [x20]
	add	x19, x20, 623
	add	x21, x20, 655
	str	wzr, [x20, 47]
.L1223:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1222
	ldr	w0, [x22, 252]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1222:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1223
	add	x20, x20, 712
	cmp	x20, x23
	bne	.L1224
	ldr	w0, [x22, 184]
	cbz	w0, .L1221
	sub	w1, w0, #1
	add	x0, x22, 2132
	add	x1, x1, 534
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1226:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1226
.L1221:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x21, w1
	mov	x20, x0
	mov	x0, x30
	mov	x19, x21
	add	x22, x20, x21, lsl 3
	bl	_mcount
	ldr	x0, [x22, 2816]
	str	wzr, [x0, 48]
	ldr	x1, [x22, 2816]
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1235
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1236
	ldr	x1, [x22, 2816]
	mov	w2, 0
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
.L1236:
	ldr	x1, [x22, 2816]
	mov	w2, 0
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
.L1235:
	ldr	w2, [x20, 2796]
	sub	w2, w2, #1
	cmp	w19, w2
	bhi	.L1239
	.p2align 2
.L1245:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 2816]
	str	x0, [x1, 2816]
	bls	.L1245
.L1239:
	add	x0, x20, x2, uxtw 3
	str	xzr, [x0, 2816]
	str	w2, [x20, 2796]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, 0
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 2796]
	cbnz	w2, .L1256
	b	.L1249
	.p2align 3
.L1251:
	add	w19, w19, 1
	cmp	w2, w19
	mov	w21, w19
	bls	.L1249
.L1256:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 2816]
	ldrb	w1, [x0]
	cbz	w1, .L1251
	mov	w1, w21
	strb	wzr, [x0]
	mov	x0, x20
	sub	w19, w19, #1
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x20
	mov	w21, w19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w2, [x20, 2796]
	cmp	w2, w19
	bhi	.L1256
.L1249:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w25, 0
	bl	_mcount
	ldr	w22, [x21, 2796]
	cbz	w22, .L1260
	mov	w26, 0
	mov	w20, 0
	mov	w24, -1
	mov	w23, 1
	.p2align 2
.L1267:
	add	x19, x21, x26, uxtw 3
	ldr	w0, [x21, 252]
	ldr	x1, [x19, 2816]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1261
	ldrsb	w1, [x0]
	cbnz	w1, .L1276
	ldrsb	w0, [x0, 1]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	ldr	x0, [x19, 2816]
	bne	.L1263
.L1279:
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1263
	str	w24, [x0, 28]
	ldr	x0, [x19, 2816]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 2816]
	strb	w23, [x0, 2]
.L1276:
	ldr	x0, [x19, 2816]
.L1263:
	ldr	w0, [x0]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1280
	add	w26, w26, 1
.L1266:
	add	w20, w20, 1
	cmp	w22, w20
	bne	.L1267
.L1260:
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1261:
	ldr	x0, [x19, 2816]
	b	.L1279
	.p2align 3
.L1280:
	mov	w1, w26
	mov	x0, x21
	mov	w25, 1
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1266
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 13272]
	ldr	w1, [x19, 13276]
	cmp	w1, w0
	bcs	.L1285
	ldr	w0, [x19, 2792]
	ldr	w1, [x19, 2796]
	cmp	w1, w0
	bcc	.L1281
	cmp	w0, 15
	bls	.L1287
.L1285:
	ldr	x0, [x19, 2816]
	mov	w2, 0
	strb	wzr, [x0, 1]
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_SetRef
	mov	x0, x19
	mov	w1, 0
	bl	HEVC_RemoveApcStore
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L1281:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1287:
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L1285
	b	.L1281
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	str	wzr, [x21]
	mov	w0, 2147483647
	str	w0, [x20]
	ldr	w3, [x19, 2792]
	ldr	w2, [x19, 2796]
	cmp	w2, w3
	bhi	.L1296
.L1289:
	mov	w0, 0
	cbz	w2, .L1288
	.p2align 2
.L1294:
	add	x1, x19, x0, uxtw 3
	ldr	w2, [x20]
	ldr	x1, [x1, 2816]
	ldr	w1, [x1, 8]
	cmp	w2, w1
	ble	.L1291
	str	w1, [x20]
	str	w0, [x21]
.L1291:
	ldr	w1, [x19, 2796]
	add	w0, w0, 1
	cmp	w1, w0
	bhi	.L1294
.L1288:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1296:
	ldr	x1, .LC301
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x19, 2792]
	str	w2, [x19, 2796]
	b	.L1289
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	3
.LC301:
	.xword	.LC300
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w4
	mov	w22, w2
	bl	_mcount
	ldr	w5, [x19, 4724]
	mov	w3, 1888
	ldr	x2, [x19, 2384]
	mov	w1, 12660
	ldr	x0, [x19, 2376]
	smaddl	x3, w5, w3, x2
	ldr	w3, [x3, 32]
	smaddl	x0, w3, w1, x0
	ldr	w1, [x0, 64]
	cmp	w1, w21
	ccmp	w20, wzr, 0, eq
	bne	.L1299
	ldr	w1, [x0, 68]
	mov	w0, 1
	cmp	w1, w22
	beq	.L1303
.L1298:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1299:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1303:
	ldr	w1, [x19, 172]
	cbz	w1, .L1298
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 944]
	cmp	w0, wzr
	cset	w0, ne
	b	.L1298
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x5, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldrb	w4, [x5]
	ldr	w6, [x0, 32]
	cbz	w4, .L1315
	sub	w2, w4, #1
	mov	w7, 32
	mov	x3, 80
	add	x0, x5, 48
	mov	w1, 0
	umaddl	x3, w2, w7, x3
	add	x3, x5, x3
	.p2align 2
.L1306:
	ldr	w2, [x0], 32
	cmp	x0, x3
	add	w1, w1, w2
	bne	.L1306
.L1305:
	sbfiz	x4, x4, 5, 32
	and	w0, w6, 7
	add	x4, x5, x4
	str	w0, [x4, 60]
	ldr	x3, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w3, [x4, 52]
	add	w0, w3, w0, lsr 3
	sub	w0, w0, w1
	str	w0, [x4, 64]
	ldr	x3, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w2, [x4, 48]
	add	w1, w1, w2
	lsl	w1, w1, 3
	sub	w0, w1, w0
	str	w0, [x4, 56]
	ldr	x1, [x19, 2400]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w2, w1, [x0, 60]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w2
	str	w1, [x0, 60]
	ldr	x1, [x19, 2400]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldr	w1, [x0, 64]
	and	w1, w1, -4
	str	w1, [x0, 64]
	ldr	x3, [x19, 2400]
	ldr	w2, [x3, 8]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1323
	ldrb	w0, [x3]
	add	w4, w0, 1
	cmp	w4, 1
	ccmp	w2, w4, 0, ls
	bls	.L1309
	add	w2, w0, 2
	.p2align 2
.L1310:
	sub	w0, w2, #1
	cmp	w2, 1
	lsl	x1, x0, 5
	add	x0, x0, 1
	add	x3, x3, x1
	lsl	x0, x0, 5
	cset	w5, ls
	str	wzr, [x3, 60]
	ldr	x3, [x19, 2400]
	add	x4, x3, x0
	add	x3, x3, x1
	ldr	w4, [x4, 20]
	str	w4, [x3, 64]
	ldr	x3, [x19, 2400]
	add	x0, x3, x0
	add	x3, x3, x1
	ldr	w0, [x0, 16]
	lsl	w0, w0, 3
	str	w0, [x3, 56]
	ldr	x0, [x19, 2400]
	add	x0, x0, x1
	ldp	w4, w3, [x0, 60]
	ubfiz	w3, w3, 3, 4
	add	w3, w3, w4
	str	w3, [x0, 60]
	ldr	x0, [x19, 2400]
	add	x1, x0, x1
	ldr	w0, [x1, 64]
	and	w0, w0, -16
	str	w0, [x1, 64]
	ldr	x3, [x19, 2400]
	ldr	w0, [x3, 8]
	cmp	w0, w2
	add	w2, w2, 1
	cset	w1, hi
	tst	w5, w1
	bne	.L1310
	sub	w1, w0, #1
.L1309:
	ubfiz	x0, x1, 5, 32
	ldr	w1, [x3, 12]
	add	x3, x3, x0
	ldr	w0, [x3, 56]
	sub	w0, w0, w1
	str	w0, [x3, 56]
	ldr	x3, [x19, 2400]
	ldrb	w0, [x3]
	ldr	w4, [x3, 8]
	cmp	w0, w4
	bcs	.L1304
	.p2align 2
.L1318:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x19, 4016]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 64]
	cmp	w1, w2
	bcs	.L1312
	str	w1, [x19, 4016]
	ldr	w4, [x3, 8]
.L1312:
	cmp	w4, w0
	bhi	.L1318
.L1304:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1323:
	ldr	x1, .LC303
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1315:
	mov	w1, 0
	b	.L1305
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	3
.LC303:
	.xword	.LC302
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 164]
	ldr	w2, [x19, 4724]
	cmp	w2, w0
	bge	.L1332
	mov	w0, 1888
	ldr	x1, [x19, 2384]
	smull	x0, w2, w0
	add	x3, x1, x0
	ldrb	w0, [x1, x0]
	cbz	w0, .L1333
	ldr	w2, [x3, 32]
	ldr	w0, [x19, 160]
	cmp	w2, w0
	bge	.L1334
	ldr	x1, [x19, 2376]
	mov	w0, 12660
	smaddl	x0, w2, w0, x1
	ldrb	w1, [x0, 1]
	cbz	w1, .L1335
	ldr	w2, [x0, 48]
	ldr	w0, [x19, 156]
	cmp	w2, w0
	bcs	.L1336
	uxtw	x1, w2
	ldr	x3, [x19, 2368]
	lsl	x4, x1, 7
	mov	w0, 0
	add	x1, x4, x1, lsl 2
	ldrb	w1, [x3, x1]
	cbz	w1, .L1337
.L1326:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1332:
	ldr	x1, .LC305
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.p2align 3
.L1333:
	ldr	x1, .LC307
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.p2align 3
.L1334:
	ldr	x1, .LC309
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.p2align 3
.L1335:
	ldr	x1, .LC311
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.p2align 3
.L1336:
	ldr	x1, .LC313
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.p2align 3
.L1337:
	ldr	x1, .LC315
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1326
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
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
.LC311:
	.xword	.LC310
	.align	3
.LC313:
	.xword	.LC312
	.align	3
.LC315:
	.xword	.LC314
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4720]
	mov	w1, 2147483647
	ldr	x2, [x19, 2400]
	add	x3, x19, x0, lsl 2
	ldr	w5, [x3, 228]
	cmp	w5, w1
	ldr	w1, [x2, 16]
	sub	w4, w1, #16
	beq	.L1365
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	beq	.L1343
.L1351:
	sub	w1, w1, #19
	cmp	w1, 1
	bls	.L1366
.L1343:
	ldr	w4, [x19, 4700]
	cmp	w4, w5
	bge	.L1342
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bls	.L1367
.L1344:
	add	x1, x19, x0
	ldrb	w8, [x1, 10]
	cbz	w8, .L1345
	ldr	w6, [x3, 232]
	cmp	w6, w4
	bgt	.L1368
.L1345:
	add	x1, x19, 4096
	ldrb	w5, [x1, 593]
	cbnz	w5, .L1346
	ldr	w2, [x2, 16]
	sub	w5, w2, #19
	cmp	w5, 1
	bls	.L1363
	cmp	w2, 21
	beq	.L1363
	sub	w2, w2, #16
	cmp	w2, 2
	bhi	.L1346
	add	x0, x19, x0
	str	w4, [x3, 232]
	mov	w2, 1
	strb	w2, [x0, 10]
	.p2align 2
.L1346:
	ldr	w0, [x19, 236]
	ldrb	w2, [x1, 592]
	ldr	w1, [x19, 4724]
	cbz	w0, .L1350
	ldr	w0, [x19, 208]
	cmp	w1, w0
	csinc	w2, w2, wzr, eq
.L1350:
	ldr	w3, [x19, 296]
	mov	w0, 1
	cmp	w3, w1
	beq	.L1369
.L1360:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1365:
	cmp	w4, 5
	bhi	.L1364
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	bne	.L1351
	ldr	w4, [x19, 4700]
	str	w4, [x3, 228]
.L1342:
	add	x1, x19, x0
	ldrb	w5, [x1, 5]
	cbz	w5, .L1344
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bhi	.L1344
	ldr	x2, .LC316
	mov	w3, 12854
	ldr	x1, .LC320
	mov	w0, 1
	add	x2, x2, 384
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1360
	.p2align 3
.L1368:
	ldr	w7, [x2, 16]
	sub	w1, w7, #8
	cmp	w1, 1
	bhi	.L1345
	ldr	x2, .LC316
	mov	w5, w4
	ldr	x1, .LC322
	mov	w4, w8
	mov	w3, 12863
	add	x2, x2, 384
	mov	w0, 1
	bl	dprint_vfmw
.L1364:
	mov	w0, 2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1363:
	add	x0, x19, x0
	str	w4, [x3, 232]
	strb	wzr, [x0, 10]
	b	.L1346
	.p2align 3
.L1366:
	mov	w5, -2147483647
	str	w5, [x3, 228]
	b	.L1343
	.p2align 3
.L1369:
	ldr	w0, [x19, 260]
	ldr	x19, [sp, 16]
	cmp	w0, w4
	csinc	w0, w2, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1367:
	ldr	x2, .LC316
	mov	w3, 12847
	ldr	x1, .LC318
	mov	w0, 1
	add	x2, x2, 384
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1360
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	3
.LC316:
	.xword	.LANCHOR0
	.align	3
.LC318:
	.xword	.LC317
	.align	3
.LC320:
	.xword	.LC319
	.align	3
.LC322:
	.xword	.LC321
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1375
	ldr	x0, [x19, 2360]
	mov	w20, 0
	bl	BsBitsToNextByte
	mov	w1, w0
	cbz	w0, .L1372
	ldr	x0, [x19, 2360]
	bl	BsGet
	mov	w2, w0
	ldr	x1, .LC326
	mov	w0, 19
	bl	dprint_vfmw
.L1372:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1375:
	ldr	x1, .LC324
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1372
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4716]
	ldr	x19, [sp, 16]
	sub	w0, w0, #16
	cmp	w0, 5
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4716]
	ldr	x19, [sp, 16]
	sub	w0, w0, #19
	cmp	w0, 1
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w24, w2
	mov	x22, x1
	mov	w23, w3
	bl	_mcount
	ldr	x0, [x20, 2360]
	cbnz	w24, .L1416
.L1414:
	mov	w1, 8
	bl	BsGet
	str	w0, [x22, 4]
	cmp	w23, wzr
	ble	.L1384
	sub	w21, w23, #1
	mov	x19, 0
	add	x21, x21, 1
	add	x25, x29, 88
	add	x22, x29, 80
	.p2align 2
.L1385:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x25, x19]
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, x21
	bne	.L1385
	cmp	w23, 7
	mov	w19, w23
	ble	.L1403
	b	.L1395
	.p2align 3
.L1388:
	cmp	w19, 8
	beq	.L1395
.L1403:
	ldr	x0, [x20, 2360]
	mov	w1, 2
	add	w19, w19, 1
	bl	BsGet
	cbz	w0, .L1388
	ldr	x1, .LC328
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1395:
	mov	x21, 0
	.p2align 2
.L1393:
	cbz	w24, .L1390
	ldrb	w0, [x25, x21]
	cbnz	w0, .L1417
.L1390:
	ldrb	w0, [x22, x21]
	cbnz	w0, .L1418
.L1392:
	add	x21, x21, 1
	cmp	w23, w21
	bgt	.L1393
.L1384:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1418:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	b	.L1392
	.p2align 3
.L1417:
	ldr	x0, [x20, 2360]
	mov	w1, 2
	mov	w19, 32
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 5
	bl	BsGet
	.p2align 2
.L1391:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	subs	w19, w19, #1
	bne	.L1391
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 12
	bl	BsGet
	b	.L1390
.L1416:
	mov	w1, 2
	add	x19, x29, 96
	add	x21, x29, 128
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 5
	bl	BsGet
	mov	w25, w0
	.p2align 2
.L1380:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19], 1
	cmp	x19, x21
	bne	.L1380
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	sub	w0, w25, #4
	cmp	w0, 3
	bls	.L1381
	ldrb	w0, [x29, 100]
	cbnz	w0, .L1381
	ldrb	w0, [x29, 101]
	cbnz	w0, .L1381
	ldrb	w0, [x29, 102]
	cbnz	w0, .L1381
	ldrb	w0, [x29, 103]
	cbnz	w0, .L1381
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 11
	bl	BsGet
	b	.L1383
	.p2align 3
.L1381:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 2
	bl	BsGet
.L1383:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	str	w25, [x20, 300]
	ldrb	w2, [x29, 97]
	ldrb	w1, [x29, 98]
	ldr	x0, [x20, 2360]
	str	w2, [x20, 304]
	str	w1, [x20, 308]
	b	.L1414
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	3
.LC328:
	.xword	.LC327
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x26, x20, 2212
	mov	w25, 0
	bl	_mcount
	ldr	x21, .LC330
	ldr	x22, .LC329
	mov	w23, 16
	ldr	x24, .LC331
.L1420:
	ldr	w0, [x26]
	cbz	w0, .L1429
	uxtw	x0, w25
	mov	w27, 0
	lsl	x28, x0, 2
	sub	x28, x28, x0
	lsl	x28, x28, 1
	.p2align 2
.L1426:
	uxtw	x19, w27
	add	x1, x21, 400
	add	x0, x19, x28
	cmp	w25, 3
	mov	x2, 64
	cbz	w25, .L1433
	add	x0, x20, x0, lsl 6
	beq	.L1434
	cmp	w27, 3
	ldr	x4, [x24, 104]
	add	x0, x0, 596
	csel	x1, x22, x1, cc
	blr	x4
.L1422:
	add	x19, x28, x19
	add	w27, w27, 1
	add	x19, x20, x19, lsl 2
	str	w23, [x19, 2228]
	ldr	w0, [x26]
	cmp	w0, w27
	bhi	.L1426
.L1429:
	add	w25, w25, 1
	add	x26, x26, 4
	cmp	w25, 4
	bne	.L1420
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1433:
	add	x0, x20, x19, lsl 6
	ldr	x1, .LC332
	ldr	x4, [x24, 104]
	mov	x2, 16
	add	x0, x0, 596
	blr	x4
	b	.L1422
.L1434:
	ldr	x0, .LC330
	uxtw	x19, w27
	cmp	w27, wzr
	ldr	x4, [x24, 104]
	add	x1, x0, 400
	ldr	x0, .LC329
	mov	x2, 64
	csel	x1, x0, x1, eq
	add	x0, x20, x19, lsl 6
	add	x0, x0, 1748
	blr	x4
	b	.L1422
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	3
.LC329:
	.xword	.LANCHOR4
	.align	3
.LC330:
	.xword	.LANCHOR0
	.align	3
.LC331:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC332:
	.xword	.LANCHOR0+464
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2424]
	ldrb	w1, [x0, 3]
	cbz	w1, .L1455
	ldr	x20, [x19, 2432]
	add	x20, x20, 256
	ldrb	w1, [x20, -235]
	cbz	w1, .L1463
.L1438:
	cbz	x20, .L1439
	ldr	x21, .LC333
	mov	x2, 1536
	mov	w1, 0
	add	x0, x19, 596
	ldr	x3, [x21, 96]
	blr	x3
	add	x16, x20, 1
	add	x15, x19, 324
	mov	w12, 0
	mov	w17, 64
	mov	w14, 6
.L1441:
	ldr	w13, [x15, 1888]
	cbz	w13, .L1450
	ldr	w8, [x15]
	mov	x9, x16
	mov	w11, 0
	cmp	w8, 64
	csel	w8, w8, w17, ls
	lsr	w10, w8, 2
.L1448:
	uxtw	x7, w11
	mov	w4, 0
	umaddl	x7, w12, w14, x7
	lsl	x7, x7, 4
	.p2align 2
.L1442:
	cmp	w10, w4
	bls	.L1445
	cbz	w8, .L1442
	add	x0, x7, x4, uxtw
	ldrb	w1, [x9, -1]
	mov	x6, x9
	mov	w3, 0
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 596]
	orr	w1, w2, w1
	str	w1, [x0, 596]
	.p2align 2
.L1451:
	add	w3, w3, 1
	add	x0, x7, x4, uxtw
	cmp	w3, w8
	and	w5, w3, 3
	add	x0, x19, x0, lsl 2
	lsl	w1, w5, 3
	beq	.L1442
	ldrb	w2, [x6], 1
	cmp	w5, 3
	ldr	w5, [x0, 596]
	csinc	w4, w4, w4, ne
	lsl	w1, w2, w1
	orr	w1, w5, w1
	str	w1, [x0, 596]
	b	.L1451
.L1463:
	ldrb	w1, [x0, 4]
	cbnz	w1, .L1464
.L1439:
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
.L1455:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1445:
	add	w11, w11, 1
	add	x9, x9, 64
	cmp	w11, w13
	bne	.L1448
.L1450:
	add	w12, w12, 1
	add	x16, x16, 384
	cmp	w12, 4
	add	x15, x15, 4
	bne	.L1441
	ldr	x3, [x21, 104]
	add	x1, x20, 1536
	mov	x2, 96
	add	x0, x19, 2228
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1464:
	add	x20, x0, 432
	b	.L1438
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	3
.LC333:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	uxtw	x22, w3
	mov	x21, x1
	bl	_mcount
	add	x0, x20, x19, uxtw 2
	mov	w9, 6
	mov	w8, 64
	mov	w5, 0
	umaddl	x9, w19, w9, x22
	ldr	w0, [x0, 324]
	lsl	x9, x9, 4
	cmp	w0, w8
	csel	w8, w0, w8, ls
	lsr	w10, w8, 2
	.p2align 2
.L1466:
	cmp	w5, w10
	bcs	.L1465
	cbz	w8, .L1466
	add	x0, x9, x5, uxtw
	mov	x7, x21
	mov	w4, 0
	add	x0, x20, x0, lsl 2
	ldrb	w2, [x7], 1
	ldr	w3, [x0, 596]
	orr	w2, w3, w2
	str	w2, [x0, 596]
	.p2align 2
.L1472:
	add	w4, w4, 1
	add	x0, x9, x5, uxtw
	cmp	w8, w4
	and	w6, w4, 3
	add	x0, x20, x0, lsl 2
	lsl	w2, w6, 3
	beq	.L1466
	ldrb	w3, [x7], 1
	cmp	w6, 3
	ldr	w6, [x0, 596]
	csinc	w5, w5, w5, ne
	lsl	w2, w3, w2
	orr	w2, w6, w2
	str	w2, [x0, 596]
	b	.L1472
.L1465:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 3
	bls	.L1486
	ldr	x1, .LC337
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1486:
	ldr	x0, .LC335
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1476
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1476:
	.section	.rodata
	.align	0
	.align	2
.L1476:
	.byte	(.L1480 - .Lrtx1476) / 4
	.byte	(.L1478 - .Lrtx1476) / 4
	.byte	(.L1478 - .Lrtx1476) / 4
	.byte	(.L1479 - .Lrtx1476) / 4
	.text
	.p2align 3
.L1478:
	cmp	w20, 2
	ldr	x0, .LC334
	bhi	.L1483
.L1484:
	add	x0, x0, 144
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1479:
	ldr	x0, .LC334
	cbz	w20, .L1484
.L1483:
	add	x0, x0, 80
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1480:
	ldr	x0, .LC334
	ldp	x19, x20, [sp, 16]
	add	x0, x0, 64
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	3
.LC334:
	.xword	.LANCHOR4
	.align	3
.LC335:
	.xword	.L1476
	.align	3
.LC337:
	.xword	.LC336
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	x23, x2
	mov	w20, w3
	bl	_mcount
	cmp	x21, xzr
	ccmp	x23, xzr, 4, ne
	ccmp	x22, xzr, 4, ne
	beq	.L1497
	sub	w0, w20, #1
	mov	w19, 1
	asr	w0, w0, 1
	cbz	w0, .L1489
	.p2align 2
.L1490:
	asr	w0, w0, 1
	add	w19, w19, 1
	cbnz	w0, .L1490
.L1489:
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w20, 1
	strb	w0, [x23]
	cset	w24, hi
	cmp	w0, wzr
	cset	w0, ne
	tst	w24, w0
	beq	.L1494
	ldr	w0, [x21, 76]
	cbz	w0, .L1494
	mov	w20, 0
	.p2align 2
.L1495:
	ldr	x0, [x22, 2360]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 4]
	ldr	w0, [x21, 76]
	cmp	w0, w20
	bhi	.L1495
.L1494:
	ldr	w0, [x21, 20]
	cbz	w0, .L1512
.L1493:
	mov	w0, 0
.L1488:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1512:
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, wzr
	strb	w0, [x23, 1]
	cset	w0, ne
	tst	w24, w0
	beq	.L1493
	ldr	w0, [x21, 80]
	cbz	w0, .L1493
	mov	w20, 0
	.p2align 2
.L1496:
	ldr	x0, [x22, 2360]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 132]
	ldr	w0, [x21, 80]
	cmp	w0, w20
	bhi	.L1496
	b	.L1493
.L1497:
	mov	w0, -1
	b	.L1488
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1515
	ldr	x1, [x19, 2400]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	cset	w0, cc
	ret
	.p2align 3
.L1515:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2360]
	ldr	w2, [x0, 24]
	ldr	w3, [x0, 32]
	lsl	w2, w2, 3
	cmp	w2, w3
	bls	.L1519
	mov	w1, 8
	bl	BsShow
	cmp	w0, 128
	cset	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1519:
	ldr	x1, .LC339
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	3
.LC339:
	.xword	.LC338
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
.L1533:
	ldr	x1, [x20, 2400]
	mov	w3, 0
	ldr	w5, [x1, 8]
	sub	w5, w5, #1
	add	x2, x1, x5, lsl 5
	ldr	w0, [x2, 48]
	ldr	x2, [x2, 40]
	sub	x0, x0, #1
	add	x0, x2, x0
	.p2align 2
.L1521:
	ldrb	w2, [x0]
	add	x19, x5, 1
	lsl	x19, x19, 5
	add	x4, x1, x19
	cbnz	w2, .L1534
	ldr	x2, [x1, 40]
	add	w3, w3, 1
	cmp	x0, x2
	beq	.L1535
	ldr	x2, [x4, 8]
	cmp	x0, x2
	sub	x0, x0, #1
	bne	.L1521
	add	x1, x1, x5, lsl 5
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 68]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x20, 2400]
	add	x19, x0, x19
	str	xzr, [x19, 8]
	ldr	x1, [x20, 2400]
	ldr	w0, [x1, 8]
	sub	w0, w0, #1
	str	w0, [x1, 8]
	b	.L1533
	.p2align 3
.L1534:
	mov	w0, 1
	mov	w5, w0
	tbnz	x2, 0, .L1528
	.p2align 2
.L1531:
	lsl	w4, w5, w0
	add	w0, w0, 1
	tst	w4, w2
	bne	.L1528
	cmp	w0, 8
	bne	.L1531
	ldr	x1, .LC343
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1535:
	ldr	x1, .LC341
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1528:
	str	wzr, [x1, 4]
	add	w3, w0, w3, lsl 3
	mov	w0, 0
	ldr	x1, [x20, 2400]
	str	w3, [x1, 12]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	3
.LC341:
	.xword	.LC340
	.align	3
.LC343:
	.xword	.LC342
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 168]
	ldr	w0, [x19, 148]
	add	w3, w3, 1
	cmp	w3, wzr
	ble	.L1537
	udiv	w1, w0, w3
	mov	w4, 104
	ldr	x5, [x19, 2448]
	msub	w0, w1, w3, w0
	umull	x1, w0, w4
	add	x1, x5, x1
	ldr	w1, [x1, 32]
	cbz	w1, .L1538
	mov	w1, 0
	b	.L1540
	.p2align 3
.L1541:
	udiv	w0, w2, w3
	msub	w0, w0, w3, w2
	umull	x2, w0, w4
	add	x2, x5, x2
	ldr	w2, [x2, 32]
	cbz	w2, .L1538
.L1540:
	add	w1, w1, 1
	cmp	w3, w1
	add	w2, w1, w0
	bne	.L1541
.L1537:
	str	w0, [x19, 148]
.L1552:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1538:
	cmp	w0, w3
	str	w0, [x19, 148]
	bcs	.L1552
	mov	w1, 104
	mov	w2, 1
	umull	x1, w0, w1
	add	x5, x5, x1
	str	w2, [x5, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1562
	ldr	x24, .LC346
	add	x19, x20, 40
	ldr	x23, .LC348
	add	x22, x20, 104
	stp	wzr, wzr, [x20, 32]
.L1557:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L1556
	ldr	w1, [x19, 28]
	bl	SM_ReleaseStreamSeg
	ldr	w4, [x19, 8]
	mov	x2, x24
	ldr	x3, [x19]
	mov	x1, x23
	mov	w0, 7
	bl	dprint_vfmw
	str	xzr, [x19]
	str	wzr, [x19, 8]
	str	wzr, [x19, 20]
.L1556:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L1557
	ldr	x3, .LC349
	mov	x2, 104
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
.L1553:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1562:
	ldr	x2, .LC344
	mov	w3, 14174
	ldr	x1, .LC345
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1553
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	3
.LC344:
	.xword	.LC205
	.align	3
.LC345:
	.xword	.LC207
	.align	3
.LC346:
	.xword	.LANCHOR5
	.align	3
.LC348:
	.xword	.LC347
	.align	3
.LC349:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecBuffers
	.type	HEVC_InitDecBuffers, %function
HEVC_InitDecBuffers:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 2792]
	cmp	w0, 17
	bhi	.L1597
.L1564:
	add	x2, x20, 2560
	add	x0, x20, 2952
	add	x1, x20, 3088
	stp	wzr, wzr, [x2, 236]
	stp	wzr, wzr, [x2, 244]
	str	wzr, [x20, 2812]
	.p2align 2
.L1565:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x0, x1
	bne	.L1565
	add	x26, x20, 12288
	ldr	x22, .LC353
	add	x19, x26, 1184
	mov	w21, 0
	mov	w25, 20
	mov	w24, 16
	.p2align 2
.L1566:
	ldr	x3, [x22, 96]
	add	x0, x19, 80
	mov	x2, 632
	mov	w1, 0
	mov	w23, 16
	blr	x3
	str	w21, [x19, 228]
	add	w21, w21, 1
	strb	wzr, [x19]
	strb	wzr, [x19, 1]
	cmp	w21, 20
	strb	wzr, [x19, 2]
	str	wzr, [x19, 8]
	stp	w25, w24, [x19, 20]
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	str	x19, [x19, 72]
	add	x19, x19, 712
	bne	.L1566
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 200
	add	x0, x26, 984
	blr	x3
	str	w23, [x20, 13272]
	add	x1, x20, 2480
	add	x0, x20, 2616
	str	wzr, [x20, 13276]
.L1568:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L1568
	add	x1, x20, 2752
	str	wzr, [x20, 4756]
	.p2align 2
.L1569:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L1569
	ldr	w0, [x20, 184]
	str	wzr, [x20, 4760]
	cbz	w0, .L1574
	sub	w1, w0, #1
	add	x0, x20, 2132
	add	x1, x1, 534
	add	x1, x20, x1, lsl 2
	.p2align 2
.L1573:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L1573
.L1574:
	ldr	w3, [x20, 168]
	mov	w19, 0
	cbz	w3, .L1563
	.p2align 2
.L1587:
	ldr	x0, [x20, 2440]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L1575
	ldr	x2, [x20, 2400]
	cmp	x0, x2
	beq	.L1575
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2440]
	mov	w2, 2
	str	xzr, [x0, x21, lsl 3]
	ldr	w1, [x20, 204]
	ldr	w0, [x20, 236]
	ldr	w4, [x20, 176]
	cmp	w1, wzr
	cset	w7, ne
	cmp	w0, wzr
	cset	w5, ne
	sub	w6, w4, #1
	cmp	w4, 3
	ldr	w3, [x20, 168]
	sub	w1, w1, w7
	csel	w2, w6, w2, cs
	sub	w0, w0, w5
	str	w2, [x20, 176]
	str	w1, [x20, 204]
	str	w0, [x20, 236]
.L1575:
	cmp	w3, w19
	bhi	.L1587
.L1563:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1597:
	ldr	x2, .LC350
	mov	w4, 17
	ldr	x1, .LC352
	mov	w3, w4
	add	x2, x2, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 2792]
	b	.L1564
	.size	HEVC_InitDecBuffers, .-HEVC_InitDecBuffers
	.align	3
.LC350:
	.xword	.LANCHOR5
	.align	3
.LC352:
	.xword	.LC351
	.align	3
.LC353:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1609
	ldr	w3, [x20, 2796]
	mov	w0, 0
	mov	w4, 1
	cbz	w3, .L1604
	.p2align 2
.L1618:
	add	x1, x20, x0, uxtw 3
	add	w0, w0, 1
	ldr	x1, [x1, 2816]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L1602
	strb	w4, [x1, 2]
	ldr	w3, [x20, 2796]
.L1602:
	cmp	w3, w0
	bhi	.L1618
.L1604:
	mov	w0, -2147483647
	add	x19, x20, 2816
	add	x21, x20, 2952
	str	w0, [x20, 212]
.L1601:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L1605
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1605:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L1606
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1606:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L1607
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1607:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L1608
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1608:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L1601
	mov	x0, x20
	bl	HEVC_InitDecBuffers
	mov	w0, 0
.L1599:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1609:
	mov	w0, -1
	b	.L1599
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2400]
	cbz	x0, .L1628
	ldr	w0, [x0, 48]
	cmp	w0, 4095
	bhi	.L1625
	ldr	x1, .LC357
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	ldr	x3, .LC358
	ldr	w2, [x1, 48]
	ldr	x0, [x1, 72]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 40]
	sub	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 2400]
	mov	w3, 1
	ldr	w2, [x0, 100]
	ldr	w1, [x0, 68]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2400]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2400]
	ldr	w4, [x0, 48]
	ldr	x2, [x0, 72]
	sub	x2, x2, x4
	str	x2, [x0, 40]
	ldr	x0, [x19, 2400]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 84]
	sub	w2, w2, w4
	str	w2, [x0, 52]
	ldr	x0, [x19, 2400]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 80]
	add	w2, w4, w2
	str	w2, [x0, 48]
	ldr	x0, [x19, 2400]
	str	w3, [x0, 8]
	ldr	w0, [x19, 252]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 2400]
	str	xzr, [x0, 72]
	ldr	x0, [x19, 2400]
	str	wzr, [x0, 92]
	ldr	x0, [x19, 2400]
	str	wzr, [x0, 80]
.L1625:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1628:
	ldr	x1, .LC355
	bl	dprint_vfmw
	b	.L1625
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	3
.LC355:
	.xword	.LC354
	.align	3
.LC357:
	.xword	.LC356
	.align	3
.LC358:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1634
	ldr	w3, [x19, 2796]
	cbz	w3, .L1634
	ldr	x0, [x19, 2816]
	cmp	x20, x0
	beq	.L1636
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1631
	.p2align 3
.L1632:
	ldr	x2, [x0, 2816]
	cmp	x20, x2
	beq	.L1636
.L1631:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1632
.L1634:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1636:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_u_v, .-HEVC_u_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_f_v, .-HEVC_f_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L1643
	mov	w0, -4370
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1643:
	mov	w1, w0
	mov	x0, x19
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x19
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w21
	mov	x0, x19
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ue_v, .-HEVC_ue_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC360
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1664
.L1649:
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	mov	w0, 0
.L1647:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1664:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 8
	mov	w22, w0
	bhi	.L1665
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 4
	mov	w1, w0
	mov	w0, 0
	bhi	.L1647
	ldr	x0, .LC363
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1648
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1648:
	.section	.rodata
	.align	0
	.align	2
.L1648:
	.byte	(.L1649 - .Lrtx1648) / 4
	.byte	(.L1649 - .Lrtx1648) / 4
	.byte	(.L1650 - .Lrtx1648) / 4
	.byte	(.L1651 - .Lrtx1648) / 4
	.byte	(.L1652 - .Lrtx1648) / 4
	.text
	.p2align 3
.L1650:
	mov	w2, 1
	lsl	w22, w2, w22
	cbz	w22, .L1663
	add	w21, w21, 7
	mov	w20, 0
	and	w21, w21, -8
	.p2align 2
.L1654:
	ldr	x0, [x19, 2360]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	cmp	w22, w20
	bne	.L1654
.L1663:
	mov	w0, 0
.L1666:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1651:
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	cmp	w0, 256
	mov	w23, w0
	bhi	.L1656
	cbz	w0, .L1663
	add	w21, w21, 7
	add	w22, w22, 7
	and	w21, w21, -8
	and	w22, w22, -8
	mov	w20, 0
	.p2align 2
.L1658:
	ldr	x0, [x19, 2360]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, w22
	bl	BsGet
	cmp	w20, w23
	bne	.L1658
	mov	w0, 0
	b	.L1666
	.p2align 3
.L1652:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	beq	.L1667
.L1659:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	mov	w0, 0
	b	.L1666
	.p2align 3
.L1667:
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	b	.L1659
.L1665:
	ldr	x1, .LC362
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1647
.L1656:
	ldr	x1, .LC365
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1647
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	3
.LC360:
	.xword	.LC359
	.align	3
.LC362:
	.xword	.LC361
	.align	3
.LC363:
	.xword	.L1648
	.align	3
.LC365:
	.xword	.LC364
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC367
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1669
	ldr	x0, [x19, 2360]
	mov	w1, 7
	bl	BsGet
	mov	w21, w0
	sub	w0, w0, #3
	cmp	w0, 2
	bhi	.L1676
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w20, w0
	ldr	x0, [x19, 2360]
	mov	w1, 6
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	cmp	w20, wzr
	ccmp	w21, 5, 4, eq
	bne	.L1677
.L1672:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
.L1669:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L1671:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1677:
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	b	.L1672
	.p2align 3
.L1676:
	ldr	x1, .LC369
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1671
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	3
.LC367:
	.xword	.LC366
	.align	3
.LC369:
	.xword	.LC368
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	cmp	x21, xzr
	ccmp	x20, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L1682
	ldr	x1, .LC371
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldrb	w0, [x20, 3]
	cbnz	w0, .L1689
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1690
.L1681:
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L1679:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1689:
	ldr	w1, [x20, 4]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1681
.L1690:
	ldr	w1, [x20, 8]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	b	.L1681
	.p2align 3
.L1682:
	mov	w0, -1
	b	.L1679
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	3
.LC371:
	.xword	.LC370
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC373
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 15
	bgt	.L1692
	tbnz	w0, #31, .L1696
	ldr	x22, .LC377
	add	w21, w0, 1
	mov	w19, 0
	.p2align 2
.L1695:
	ldr	x0, [x20, 2360]
	mov	x1, x22
	add	w19, w19, 1
	bl	HEVC_ue_v
	cmp	w21, w19
	bne	.L1695
.L1696:
	ldr	x0, [x20, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L1694:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1692:
	ldr	x1, .LC375
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1694
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	3
.LC373:
	.xword	.LC372
	.align	3
.LC375:
	.xword	.LC374
	.align	3
.LC377:
	.xword	.LC376
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x22, x2
	bl	_mcount
	ldr	x1, .LC379
	ldr	x0, [x19, 2360]
	str	wzr, [x19, 11864]
	bl	HEVC_ue_v
	cmp	w0, 15
	bhi	.L1724
	add	x0, x19, 8192
	mov	w1, 1
	mov	w24, 0
	strb	w1, [x0, 3665]
	ldrb	w0, [x22, 2]
	cbz	w0, .L1725
.L1701:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	mov	w21, w1
	mov	w20, 0
	bl	BsGet
	strb	w0, [x23]
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2360]
	add	w1, w1, w21
	bl	BsGet
.L1702:
	cbz	w20, .L1726
	cmp	w20, 1
	beq	.L1727
.L1707:
	cmp	w21, 1
	bhi	.L1706
.L1705:
	add	w20, w20, 1
	add	w21, w21, 1
	b	.L1702
	.p2align 3
.L1706:
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L1722:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1725:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w24, w0
	cbz	w24, .L1701
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 20]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	b	.L1701
.L1724:
	ldr	x1, .LC381
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1722
.L1726:
	ldrb	w0, [x22]
	cbz	w0, .L1707
	ldr	w0, [x22, 24]
	mov	w23, 0
	cmn	w0, #1
	bne	.L1710
	b	.L1705
	.p2align 3
.L1709:
	ldr	w0, [x22, 24]
	add	w0, w0, 1
	cmp	w0, w23
	bls	.L1707
.L1710:
	ldr	w1, [x22, 12]
	add	w23, w23, 1
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x22, 2]
	orr	w0, w0, w24
	cbz	w0, .L1709
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	b	.L1709
.L1727:
	ldrb	w0, [x22, 1]
	cbz	w0, .L1706
	ldr	w0, [x22, 24]
	cmn	w0, #1
	beq	.L1706
	mov	w23, 0
	b	.L1710
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	3
.LC379:
	.xword	.LC378
	.align	3
.LC381:
	.xword	.LC380
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	x22, x1
	bl	_mcount
	ldr	w1, [x19, 11860]
	ldr	w0, [x19, 11864]
	add	w1, w1, 1
	str	w1, [x19, 11860]
	add	w0, w0, 1
	str	w0, [x19, 11864]
	ldrb	w0, [x20, 2]
	cbnz	w0, .L1755
.L1729:
	ldrh	w0, [x20, 44]
	add	x21, x20, 44
	cbz	w0, .L1731
	ldr	w1, [x21, 16]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x22, 8]
	ldr	w1, [x21, 20]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	str	w0, [x22, 12]
	ldrb	w0, [x21, 2]
	cbnz	w0, .L1732
.L1735:
	ldrsw	x1, [x19, 252]
	ldr	x0, .LC382
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L1756
.L1731:
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L1738:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1755:
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	str	w0, [x22]
	mov	w1, 2
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x19, 2360]
	bl	BsGet
	b	.L1729
	.p2align 3
.L1756:
	ldr	w1, [x0, 156]
	cbnz	w1, .L1731
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L1731
	mov	x2, x20
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1731
	.p2align 3
.L1732:
	ldr	w1, [x21, 8]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x21, 2]
	cbz	w0, .L1735
	ldrb	w0, [x21, 3]
	cbz	w0, .L1735
	ldr	x1, .LC384
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	mov	w24, w0
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w25, w0
	cbnz	w25, .L1757
.L1736:
	cmp	w24, 255
	bhi	.L1758
	ldr	x26, .LC388
	add	w24, w24, 1
	mov	w23, 0
	b	.L1740
	.p2align 3
.L1739:
	cmp	w23, w24
	beq	.L1735
.L1740:
	ldr	x0, [x19, 2360]
	mov	x1, x26
	add	w23, w23, 1
	bl	HEVC_ue_v
	cbnz	w25, .L1739
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	b	.L1739
	.p2align 3
.L1757:
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2360]
	add	w1, w1, 1
	bl	BsGet
	b	.L1736
.L1758:
	ldr	x1, .LC386
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1738
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	3
.LC382:
	.xword	s_pstVfmwChan
	.align	3
.LC384:
	.xword	.LC383
	.align	3
.LC386:
	.xword	.LC385
	.align	3
.LC388:
	.xword	.LC387
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Volume_Reconstruction_Info
	.type	HEVC_Sei_Color_Volume_Reconstruction_Info, %function
HEVC_Sei_Color_Volume_Reconstruction_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L1769
	ldr	x1, .LC390
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1761
.L1765:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x20]
.L1760:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1761:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L1774
.L1762:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	mov	w21, 0
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x20, 5]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x20, 6]
	mov	w1, 4
	ldr	x0, [x19, 2360]
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 7]
	cbz	w1, .L1767
	.p2align 2
.L1771:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2360]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 8]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x22, 23]
	ldrb	w0, [x20, 7]
	cmp	w0, w21
	bhi	.L1771
.L1767:
	ldr	x0, [x19, 2360]
	mov	w1, 4
	mov	w21, 0
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 38]
	cbz	w1, .L1765
	.p2align 2
.L1770:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2360]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 39]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x22, 54]
	ldrb	w0, [x20, 38]
	cmp	w0, w21
	bhi	.L1770
	b	.L1765
	.p2align 3
.L1769:
	mov	w0, -1
	b	.L1760
	.p2align 3
.L1774:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	b	.L1762
	.size	HEVC_Sei_Color_Volume_Reconstruction_Info, .-HEVC_Sei_Color_Volume_Reconstruction_Info
	.align	3
.LC390:
	.xword	.LC389
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Registered_Itu_T_T35
	.type	HEVC_Sei_User_Data_Registered_Itu_T_T35, %function
HEVC_Sei_User_Data_Registered_Itu_T_T35:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L1782
	cmp	w21, 3
	bls	.L1786
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 2
	beq	.L1787
	cmp	w0, 4
	beq	.L1788
	subs	w21, w21, #4
	mov	w19, 0
	beq	.L1781
	.p2align 2
.L1784:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L1784
.L1781:
	mov	w0, 0
.L1776:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1787:
	add	x1, x20, 3416
	mov	x0, x20
	bl	HEVC_Sei_TSI
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1788:
	add	x1, x20, 3419
	mov	x0, x20
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1782:
	mov	w0, -1
	b	.L1776
.L1786:
	ldr	x1, .LC392
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1776
	.size	HEVC_Sei_User_Data_Registered_Itu_T_T35, .-HEVC_Sei_User_Data_Registered_Itu_T_T35
	.align	3
.LC392:
	.xword	.LC391
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	w20, w3
	mov	x0, x30
	mov	x27, x1
	mov	x19, x2
	bl	_mcount
	cbnz	w20, .L1836
.L1790:
	ldr	x1, .LC406
	ldr	x0, [x22, 2360]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19]
	bhi	.L1837
	ldr	x1, .LC410
	ldr	x0, [x22, 2360]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19, 4]
	bhi	.L1838
	ldr	w1, [x19]
	add	w2, w0, w1
	str	w2, [x19, 8]
	cmp	w2, 16
	bhi	.L1815
	mov	w20, 0
	cbz	w1, .L1817
	ldr	x25, .LC416
	mov	w21, 0
	mov	w23, 0
	mov	w24, 32767
	b	.L1819
	.p2align 3
.L1818:
	str	w23, [x19, x2, lsl 2]
	add	x20, x19, x20
	ldr	x0, [x22, 2360]
	bl	BsGet
	strb	w0, [x20, 12]
	ldr	w20, [x19]
	cmp	w20, w21
	bls	.L1839
.L1819:
	ldr	x0, [x22, 2360]
	mov	x1, x25
	uxtw	x20, w21
	add	w21, w21, 1
	bl	HEVC_ue_v
	cmp	w0, w24
	mvn	w1, w0
	add	x2, x20, 8
	add	w23, w23, w1
	mov	w1, 1
	bls	.L1818
	ldr	x1, .LC418
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1836:
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1790
	ldr	w0, [x27, 176]
	cmp	w20, w0
	beq	.L1840
	sub	w20, w20, #1
.L1794:
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x1, .LC400
	ldr	x0, [x22, 2360]
	bl	HEVC_ue_v
	uxtw	x1, w20
	mov	w4, 1
	lsl	x2, x1, 2
	sub	w25, w4, w25, lsl 1
	sub	x3, x2, x1
	lsl	x2, x3, 3
	sub	x2, x2, x3
	lsl	x24, x2, 1
	sub	x24, x24, x1
	madd	w25, w0, w25, w25
	add	x28, x27, x24, lsl 2
	ldr	w2, [x28, 2172]
	cmp	w2, 16
	bhi	.L1841
	mov	w21, 0
	mov	w26, 0
	mov	w20, 0
	mov	w23, 0
	b	.L1801
	.p2align 3
.L1796:
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L1842
.L1797:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L1843
.L1801:
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L1796
	ldr	x0, [x22, 2360]
	mov	w1, 1
	bl	BsGet
	lsl	w0, w0, 1
	sub	w1, w0, #1
	cmp	w1, 1
	bhi	.L1797
.L1842:
	ldr	w5, [x28, 2172]
	add	x1, x24, x21, uxtw
	uxtw	x2, w23
	cmp	w5, w21
	add	x4, x2, 8
	add	x3, x19, x2
	add	x2, x27, x1, lsl 2
	mov	w1, 0
	bls	.L1798
	ldr	w1, [x2, 2196]
.L1798:
	cmp	w0, 1
	add	w0, w1, w25
	str	w0, [x19, x4, lsl 2]
	cset	w1, eq
	strb	w1, [x3, 12]
	tbnz	w0, #31, .L1844
	add	w26, w26, 1
	add	w23, w23, 1
.L1845:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcs	.L1801
.L1843:
	cmp	w23, 16
	str	w23, [x19, 8]
	ccmp	w20, 16, 2, ls
	ccmp	w26, 16, 2, ls
	stp	w20, w26, [x19]
	bhi	.L1802
	cmp	w23, 1
	bls	.L1808
	sub	w10, w23, #2
	add	x9, x19, 36
	add	x10, x10, 1
	mov	x7, 0
	.p2align 2
.L1807:
	add	x0, x19, x7
	mov	w3, w7
	ldr	w5, [x9]
	ldrb	w8, [x0, 13]
	tbnz	w7, #31, .L1811
	.p2align 2
.L1826:
	sxtw	x1, w3
	add	w0, w3, 1
	add	x4, x19, x1
	add	x1, x19, x1, lsl 2
	sxtw	x0, w0
	add	x6, x0, 8
	add	x0, x19, x0
	ldr	w2, [x1, 32]
	cmp	w5, w2
	bge	.L1809
	str	w2, [x19, x6, lsl 2]
	ldrb	w2, [x4, 12]
	strb	w2, [x0, 12]
	str	w5, [x1, 32]
	strb	w8, [x4, 12]
.L1809:
	subs	w3, w3, #1
	bpl	.L1826
.L1811:
	add	x7, x7, 1
	add	x9, x9, 4
	cmp	x10, x7
	bne	.L1807
.L1808:
	lsr	w7, w20, 1
	sub	w20, w20, #1
	cbz	w7, .L1805
	add	x2, x19, 32
	add	x1, x19, 12
	sub	w7, w20, w7
	.p2align 2
.L1812:
	sxtw	x0, w20
	ldrb	w4, [x1]
	add	x3, x19, x0
	ldr	w5, [x2]
	add	x0, x19, x0, lsl 2
	sub	w20, w20, #1
	cmp	w20, w7
	ldr	w6, [x0, 32]
	str	w6, [x2], 4
	ldrb	w6, [x3, 12]
	strb	w6, [x1], 1
	str	w5, [x0, 32]
	strb	w4, [x3, 12]
	bne	.L1812
.L1805:
	mov	w0, 0
.L1835:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1844:
	add	w20, w20, 1
	add	w23, w23, 1
	b	.L1845
.L1839:
	ldr	w2, [x19, 8]
.L1817:
	cmp	w2, w20
	bls	.L1805
	ldr	x24, .LC420
	mov	w23, 0
	.p2align 2
.L1820:
	ldr	x0, [x22, 2360]
	mov	x1, x24
	uxtw	x21, w20
	add	w20, w20, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x2, x21, 8
	add	w23, w23, w0
	add	x21, x19, x21
	mov	w1, 1
	str	w23, [x19, x2, lsl 2]
	ldr	x0, [x22, 2360]
	bl	BsGet
	strb	w0, [x21, 12]
	ldr	w0, [x19, 8]
	cmp	w0, w20
	bhi	.L1820
	b	.L1805
.L1840:
	ldr	x1, .LC394
	ldr	x0, [x22, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w20, w2
	bcc	.L1846
	sub	w3, w20, #1
	sub	w20, w3, w0
	cmp	w20, w3
	bls	.L1794
	ldr	x1, .LC398
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1802:
	ldr	x1, .LC404
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1838:
	ldr	x1, .LC412
	mov	w0, 1
	ldr	w2, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1846:
	ldr	x1, .LC396
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1841:
	ldr	x1, .LC402
	mov	w0, w4
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1837:
	ldr	x1, .LC408
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
.L1815:
	ldr	x1, .LC414
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1835
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	3
.LC394:
	.xword	.LC393
	.align	3
.LC396:
	.xword	.LC395
	.align	3
.LC398:
	.xword	.LC397
	.align	3
.LC400:
	.xword	.LC399
	.align	3
.LC402:
	.xword	.LC401
	.align	3
.LC404:
	.xword	.LC403
	.align	3
.LC406:
	.xword	.LC405
	.align	3
.LC408:
	.xword	.LC407
	.align	3
.LC410:
	.xword	.LC409
	.align	3
.LC412:
	.xword	.LC411
	.align	3
.LC414:
	.xword	.LC413
	.align	3
.LC416:
	.xword	.LC415
	.align	3
.LC418:
	.xword	.LC417
	.align	3
.LC420:
	.xword	.LC419
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	uxtb	w19, w2
	mov	w23, w3
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L1870
	cbnz	w19, .L1894
.L1850:
	ldr	x27, .LC424
	mov	w19, 0
	ldr	x25, .LC422
	ldr	x26, .LC426
	ldr	x28, .LC428
	.p2align 2
.L1866:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	uxtw	x21, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1895
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
.L1869:
	ldr	x0, [x20, 2360]
	mov	x1, x25
	bl	HEVC_ue_v
.L1856:
	ldr	x0, [x20, 2360]
	mov	x1, x27
	bl	HEVC_ue_v
	add	x1, x22, x21, lsl 2
	str	w0, [x1, 24]
.L1857:
	cmp	w0, 31
	bhi	.L1896
	mov	w24, 0
.L1859:
	cbz	w24, .L1897
	cmp	w24, 1
	beq	.L1892
.L1865:
	add	w24, w24, 1
	cmp	w24, 2
	bne	.L1859
.L1864:
	add	w19, w19, 1
	cmp	w23, w19
	bcs	.L1866
	mov	w0, 0
.L1891:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1896:
	mov	w2, w0
	mov	x1, x26
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
	b	.L1859
	.p2align 3
.L1895:
	add	x24, x22, x21, lsl 2
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	str	wzr, [x24, 24]
	uxtb	w0, w0
	cbnz	w0, .L1869
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1856
	ldr	w0, [x24, 24]
	b	.L1857
	.p2align 3
.L1894:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x22, 1]
	ldrh	w0, [x22]
	cbz	w0, .L1850
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22, 2]
	cbnz	w0, .L1898
.L1852:
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	ldrb	w0, [x22, 2]
	cbnz	w0, .L1899
.L1853:
	ldr	x0, [x20, 2360]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 12]
	mov	w1, 5
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x22, 16]
	mov	w1, 5
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L1850
.L1870:
	mov	w0, -1
	b	.L1891
.L1899:
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	b	.L1853
.L1898:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x22, 3]
	mov	w1, 5
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L1852
.L1897:
	ldrb	w0, [x22]
	cbnz	w0, .L1872
	mov	w24, 1
.L1892:
	ldrb	w0, [x22, 1]
	cbz	w0, .L1864
.L1872:
	add	x0, x21, 4
	str	wzr, [x29, 108]
	lsl	x0, x0, 2
	str	x0, [x29, 96]
	b	.L1868
.L1867:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x29, 96]
	ldr	w1, [x29, 108]
	add	x0, x22, x0
	ldr	w0, [x0, 8]
	cmp	w0, w1
	bcc	.L1865
.L1868:
	ldr	w2, [x29, 108]
	mov	x1, x28
	ldr	x0, [x20, 2360]
	add	w2, w2, 1
	str	w2, [x29, 108]
	bl	HEVC_ue_v
	ldr	x1, .LC430
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldrb	w0, [x22, 2]
	cbz	w0, .L1867
	ldr	x1, .LC432
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC434
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	b	.L1867
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	3
.LC422:
	.xword	.LC421
	.align	3
.LC424:
	.xword	.LC423
	.align	3
.LC426:
	.xword	.LC425
	.align	3
.LC428:
	.xword	.LC427
	.align	3
.LC430:
	.xword	.LC429
	.align	3
.LC432:
	.xword	.LC431
	.align	3
.LC434:
	.xword	.LC433
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21, 3]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L1901
	ldr	x1, .LC436
	uxtb	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
.L1901:
	ldr	x0, [x20, 2360]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 63
	str	w0, [x21, 8]
	bhi	.L1949
	ldr	x0, [x20, 2360]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 7
	mov	w24, w0
	bhi	.L1950
	str	w0, [x21, 12]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x21, 1]
	mov	w1, 16
	ldr	x0, [x20, 2360]
	bl	BsGet
	mov	w1, 65535
	cmp	w0, w1
	bne	.L1951
	mov	w3, w24
	mov	w2, 1
	add	x1, x21, 124
	mov	x0, x20
	bl	HEVC_DecPTL
	cbnz	w0, .L1952
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w25, w0
	tbnz	w24, #31, .L1911
	ldr	x28, .LC448
	add	w23, w24, 1
	ldr	x27, .LC450
	mov	w19, 0
	ldr	x26, .LC452
	b	.L1913
	.p2align 3
.L1910:
	cmp	w23, w19
	beq	.L1911
.L1913:
	add	x22, x21, x19, sxtw 2
	ldr	x0, [x20, 2360]
	mov	x1, x28
	add	w19, w19, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 28]
	mov	x1, x27
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x22, 60]
	mov	x1, x26
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x22, 92]
	cbnz	w25, .L1910
	cmp	w24, w19
	blt	.L1911
	.p2align 2
.L1936:
	add	x0, x21, x19, sxtw 2
	ldr	w1, [x21, 28]
	add	w19, w19, 1
	cmp	w23, w19
	str	w1, [x0, 28]
	ldr	w1, [x21, 60]
	str	w1, [x0, 60]
	ldr	w1, [x21, 92]
	str	w1, [x0, 92]
	bne	.L1936
.L1911:
	ldr	x0, [x20, 2360]
	mov	w1, 6
	bl	BsGet
	str	w0, [x21, 16]
	ldr	x1, .LC446
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 1023
	str	w0, [x21, 20]
	bhi	.L1953
	cmp	w0, wzr
	mov	w22, 1
	ble	.L1915
	.p2align 2
.L1935:
	mov	w19, 0
	.p2align 2
.L1916:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	add	w19, w19, w1
	bl	BsGet
	ldr	w0, [x21, 16]
	cmp	w0, w19
	bcs	.L1916
	ldr	w0, [x21, 20]
	add	w22, w22, 1
	cmp	w0, w22
	bge	.L1935
.L1915:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1924
	ldr	x0, [x20, 2360]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1954
.L1921:
	ldr	x1, .LC458
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 1024
	str	w0, [x21, 24]
	bhi	.L1922
	cmp	w0, wzr
	ble	.L1924
	ldr	x22, .LC462
	mov	w19, 0
	ldr	x0, [x20, 2360]
	mov	x1, x22
	bl	HEVC_ue_v
	mov	w2, 1
	.p2align 2
.L1929:
	mov	w3, w24
	add	x1, x29, 104
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_DecHrdParam
	cbnz	w0, .L1955
.L1926:
	ldr	w0, [x21, 24]
	mov	x1, x22
	cmp	w0, w19
	ble	.L1924
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	mov	w2, 1
	cbz	w19, .L1929
	ldr	x0, [x20, 2360]
	mov	w1, w2
	add	w19, w19, 1
	bl	BsGet
	mov	w2, w0
	mov	w3, w24
	add	x1, x29, 104
	mov	x0, x20
	bl	HEVC_DecHrdParam
	cbz	w0, .L1926
.L1955:
	ldr	x1, .LC464
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1924:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1920
	.p2align 2
.L1944:
	ldr	x0, [x20, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1920
	ldr	x2, [x20, 2400]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L1956
.L1920:
	mov	w0, 0
.L1945:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1956:
	ldr	x0, [x20, 2360]
	bl	BsGet
	b	.L1944
.L1954:
	ldr	x1, .LC456
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	b	.L1921
.L1951:
	ldr	x1, .LC442
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1945
.L1949:
	ldr	x1, .LC438
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1945
.L1952:
	ldr	x1, .LC444
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1945
.L1950:
	ldr	x1, .LC440
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1945
.L1953:
	ldr	x1, .LC454
.L1947:
	mov	w2, w0
	mov	w3, 1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1945
.L1922:
	ldr	x1, .LC460
	b	.L1947
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	3
.LC436:
	.xword	.LC435
	.align	3
.LC438:
	.xword	.LC437
	.align	3
.LC440:
	.xword	.LC439
	.align	3
.LC442:
	.xword	.LC441
	.align	3
.LC444:
	.xword	.LC443
	.align	3
.LC446:
	.xword	.LC445
	.align	3
.LC448:
	.xword	.LC447
	.align	3
.LC450:
	.xword	.LC449
	.align	3
.LC452:
	.xword	.LC451
	.align	3
.LC454:
	.xword	.LC453
	.align	3
.LC456:
	.xword	.LC455
	.align	3
.LC458:
	.xword	.LC457
	.align	3
.LC460:
	.xword	.LC459
	.align	3
.LC462:
	.xword	.LC461
	.align	3
.LC464:
	.xword	.LC463
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	cmp	w0, 15
	mov	w21, w0
	bhi	.L1963
	uxtw	x19, w0
	ldr	x0, [x20, 2368]
	lsl	x1, x19, 7
	add	x19, x1, x19, lsl 2
	add	x1, x0, x19
	ldrb	w0, [x0, x19]
	cbnz	w0, .L1964
	str	w21, [x1, 4]
	mov	x0, x20
	ldr	x1, [x20, 2368]
	add	x1, x1, x19
	bl	HEVC_ProcessVPS
	mov	w22, w0
	cbnz	w0, .L1965
	ldr	x0, [x20, 2368]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2368]
	strb	w1, [x0, x19]
.L1959:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1964:
	ldr	x25, .LC467
	mov	x2, 132
	ldr	x24, .LC468
	mov	w1, 0
	add	x23, x24, 3328
	ldr	x3, [x25, 96]
	mov	x0, x23
	blr	x3
	str	w21, [x23, 4]
	mov	x1, x23
	mov	x0, x20
	bl	HEVC_ProcessVPS
	mov	w22, w0
	cbnz	w0, .L1966
	ldr	x0, [x20, 2368]
	mov	w1, 1
	ldr	x3, [x25, 112]
	mov	x2, 132
	strb	w1, [x23, 2]
	add	x0, x0, x19
	strb	w1, [x24, 3328]
	mov	x1, x23
	blr	x3
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1966:
	ldr	x1, .LC470
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1959
	.p2align 3
.L1963:
	ldr	x1, .LC466
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1959
.L1965:
	ldr	x1, .LC472
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x20, 2368]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2368]
	strb	wzr, [x0, x19]
	b	.L1959
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	3
.LC466:
	.xword	.LC465
	.align	3
.LC467:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC468:
	.xword	.LANCHOR6
	.align	3
.LC470:
	.xword	.LC469
	.align	3
.LC472:
	.xword	.LC471
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2012
.L1969:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2013
.L1971:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2014
.L1973:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2015
.L1975:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 1
	ldr	x0, [x19, 2360]
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1976
	ldr	x1, .LC479
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	w0, [x21, 60]
	cmp	w0, 3
	bhi	.L2016
	ldr	x1, .LC483
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC485
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC487
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
.L1976:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1979
	ldr	x0, [x19, 2360]
	mov	w1, 32
	bl	BsGet
	str	w0, [x20, 36]
	mov	w1, 32
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x20, 40]
	ldr	w1, [x20, 36]
	cbnz	w1, .L2017
.L1980:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2018
.L1981:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2019
.L1979:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	mov	w0, 0
	cbnz	w1, .L2020
.L1978:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2020:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC494
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	cmp	w0, 4095
	bhi	.L2021
.L1982:
	ldr	x1, .LC498
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC500
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC502
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC504
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2015:
	ldr	x1, .LC475
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC477
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	b	.L1975
	.p2align 3
.L2012:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	str	w0, [x20, 8]
	bne	.L1969
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsGet
	str	w0, [x20, 12]
	mov	w1, 16
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x20, 16]
	b	.L1969
	.p2align 3
.L2014:
	ldr	x0, [x19, 2360]
	mov	w1, 3
	bl	BsGet
	str	w0, [x20, 20]
	mov	w1, 1
	ldr	x0, [x19, 2360]
	bl	BsGet
	strb	w0, [x20]
	mov	w1, 1
	ldr	x0, [x19, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L1973
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x20, 28]
	mov	w1, 8
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x20, 32]
	b	.L1973
	.p2align 3
.L2013:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	b	.L1971
	.p2align 3
.L2019:
	ldr	w3, [x21, 52]
	mov	w2, 1
	add	x1, x20, 44
	mov	x0, x19
	bl	HEVC_DecHrdParam
	cbz	w0, .L1979
	ldr	x1, .LC492
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1978
	.p2align 3
.L2018:
	ldr	x1, .LC490
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	b	.L1981
	.p2align 3
.L2017:
	ldr	x2, .LC488
	mov	w3, 10000
	umull	x0, w0, w3
	ldr	x2, [x2, 472]
	blr	x2
	add	w0, w0, 5
	mov	w1, 52429
	movk	w1, 0xcccc, lsl 16
	umull	x0, w0, w1
	lsr	x0, x0, 35
	str	w0, [x19, 144]
	b	.L1980
	.p2align 3
.L2021:
	ldr	x1, .LC496
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1982
	.p2align 3
.L2016:
	ldr	x1, .LC481
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1978
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	3
.LC475:
	.xword	.LC474
	.align	3
.LC477:
	.xword	.LC476
	.align	3
.LC479:
	.xword	.LC478
	.align	3
.LC481:
	.xword	.LC480
	.align	3
.LC483:
	.xword	.LC482
	.align	3
.LC485:
	.xword	.LC484
	.align	3
.LC487:
	.xword	.LC486
	.align	3
.LC488:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC490:
	.xword	.LC489
	.align	3
.LC492:
	.xword	.LC491
	.align	3
.LC494:
	.xword	.LC493
	.align	3
.LC496:
	.xword	.LC495
	.align	3
.LC498:
	.xword	.LC497
	.align	3
.LC500:
	.xword	.LC499
	.align	3
.LC502:
	.xword	.LC501
	.align	3
.LC504:
	.xword	.LC503
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L2027
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2027:
	mov	w1, w0
	mov	x0, x20
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	sub	w0, w0, #1
	asr	w2, w0, 1
	and	w0, w0, 1
	cmp	w0, wzr
	mov	w1, w21
	mov	x0, x20
	neg	w19, w2
	csinc	w19, w19, w2, eq
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_se_v, .-HEVC_se_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC506
	ldr	x0, [x21, 2360]
	bl	HEVC_ue_v
	ldr	x1, .LC508
	ldr	x0, [x21, 2360]
	bl	HEVC_ue_v
	cmp	w0, 1024
	mov	w22, w0
	bhi	.L2029
	mov	w19, 0
	cbz	w0, .L2035
	ldr	x24, .LC512
	ldr	x23, .LC514
	.p2align 2
.L2038:
	ldr	x0, [x21, 2360]
	mov	w1, 6
	bl	BsGet
	sub	w20, w0, #19
	ldr	x0, [x21, 2360]
	mov	w1, 3
	bl	BsGet
	cmp	w20, 1
	mov	x1, x24
	bls	.L2032
	ldr	x0, [x21, 2360]
	bl	HEVC_ue_v
.L2032:
	mov	x1, x23
	cbz	w19, .L2033
	ldr	x0, [x21, 2360]
	bl	HEVC_se_v
.L2033:
	add	w19, w19, 1
	cmp	w22, w19
	bne	.L2038
.L2035:
	ldr	x0, [x21, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L2031:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2029:
	ldr	x1, .LC510
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2031
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	3
.LC506:
	.xword	.LC505
	.align	3
.LC508:
	.xword	.LC507
	.align	3
.LC510:
	.xword	.LC509
	.align	3
.LC512:
	.xword	.LC511
	.align	3
.LC514:
	.xword	.LC513
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L2043
	ldr	x1, .LC516
	ldr	x0, [x19, 2360]
	bl	HEVC_se_v
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
	mov	w0, 0
.L2042:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2043:
	mov	w0, -1
	b	.L2042
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	3
.LC516:
	.xword	.LC515
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Remapping_Info
	.type	HEVC_Sei_Color_Remapping_Info, %function
HEVC_Sei_Color_Remapping_Info:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2062
	ldr	x1, .LC518
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2046
.L2059:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x22]
.L2045:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2046:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2070
.L2047:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	mov	w23, 3
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
.L2049:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	uxtb	w1, w0
	cbz	w1, .L2052
	and	w0, w0, 255
	mov	w19, 0
	add	w21, w0, 1
	.p2align 2
.L2051:
	ldr	x0, [x20, 2360]
	mov	w1, 16
	add	w19, w19, 1
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 16
	bl	BsGet
	cmp	w21, w19
	bne	.L2051
.L2052:
	subs	w23, w23, #1
	bne	.L2049
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2053
.L2057:
	add	x26, x22, 3
	mov	x23, x22
	mov	w25, 33
.L2054:
	ldr	x0, [x20, 2360]
	mov	w1, 8
	sub	w24, w23, w22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 40]
	cbz	w0, .L2061
	mov	w21, 0
	.p2align 2
.L2060:
	uxtw	x19, w21
	ldr	x0, [x20, 2360]
	mov	w1, 16
	add	w21, w21, 1
	umaddl	x19, w24, w25, x19
	bl	BsGet
	mov	w1, 16
	add	x19, x22, x19, lsl 1
	strh	w0, [x19, 44]
	ldr	x0, [x20, 2360]
	bl	BsGet
	strh	w0, [x19, 242]
	ldrb	w0, [x23, 40]
	add	w0, w0, 1
	cmp	w0, w21
	bhi	.L2060
.L2061:
	add	x23, x23, 1
	cmp	x23, x26
	bne	.L2054
	b	.L2059
	.p2align 3
.L2062:
	mov	w0, -1
	b	.L2045
.L2053:
	ldr	x0, [x20, 2360]
	mov	w1, 4
	add	x19, x22, 4
	add	x24, x22, 40
	bl	BsGet
	ldr	x23, .LC520
.L2055:
	add	x21, x19, 12
.L2056:
	ldr	x0, [x20, 2360]
	mov	x1, x23
	bl	HEVC_se_v
	str	w0, [x19], 4
	cmp	x19, x21
	bne	.L2056
	cmp	x19, x24
	bne	.L2055
	b	.L2057
.L2070:
	ldr	x0, [x20, 2360]
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 8
	ldr	x0, [x20, 2360]
	bl	BsGet
	ldr	x0, [x20, 2360]
	mov	w1, 8
	bl	BsGet
	b	.L2047
	.size	HEVC_Sei_Color_Remapping_Info, .-HEVC_Sei_Color_Remapping_Info
	.align	3
.LC518:
	.xword	.LC517
	.align	3
.LC520:
	.xword	.LC519
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	x23, x2
	mov	w20, w3
	mov	w21, w4
	bl	_mcount
	ldr	x0, [x19, 2400]
	ldr	w0, [x0, 16]
	cmp	w0, 39
	beq	.L2120
	cmp	w20, 5
	beq	.L2100
	cmp	w20, 132
	beq	.L2101
	mov	w20, 0
	cbz	w21, .L2094
	.p2align 2
.L2114:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2114
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbnz	w0, .L2104
	.p2align 2
.L2108:
	mov	w0, 0
.L2096:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2100:
	mov	w2, w21
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Unregistered
	cbnz	w0, .L2097
.L2094:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbz	w0, .L2108
.L2104:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_Payload_Extension_Present
	cbnz	w0, .L2121
	.p2align 2
.L2107:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	bl	BsIsByteAligned
	cbz	w0, .L2107
	b	.L2108
	.p2align 3
.L2120:
	cmp	w20, 147
	bls	.L2122
.L2073:
	mov	w20, 0
	cbz	w21, .L2094
	.p2align 2
.L2113:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2113
	b	.L2094
	.p2align 3
.L2101:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Decoded_Picture_Hash
	cbz	w0, .L2094
	.p2align 2
.L2097:
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2122:
	ldr	x0, .LC521
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx2075
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2075:
	.section	.rodata
	.align	0
	.align	2
.L2075:
	.byte	(.L2074 - .Lrtx2075) / 4
	.byte	(.L2076 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2077 - .Lrtx2075) / 4
	.byte	(.L2100 - .Lrtx2075) / 4
	.byte	(.L2079 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2080 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2081 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2082 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2083 - .Lrtx2075) / 4
	.byte	(.L2084 - .Lrtx2075) / 4
	.byte	(.L2085 - .Lrtx2075) / 4
	.byte	(.L2086 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2087 - .Lrtx2075) / 4
	.byte	(.L2088 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2089 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2090 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2091 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2073 - .Lrtx2075) / 4
	.byte	(.L2092 - .Lrtx2075) / 4
	.text
	.p2align 3
.L2121:
	ldr	x1, .LC523
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	b	.L2107
.L2092:
	add	x0, x22, 618
	cmp	x19, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L2097
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 618]
	b	.L2094
.L2091:
	add	x1, x22, 612
	mov	x0, x19
	bl	HEVC_Sei_Content_Light_Level_Information
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2090:
	add	x1, x22, 128
	mov	x0, x19
	bl	HEVC_Sei_Color_Remapping_Info
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2089:
	add	x1, x22, 568
	cmp	x19, xzr
	ccmp	x1, xzr, 4, ne
	beq	.L2097
	mov	w0, 1
	strb	w0, [x22, 568]
	mov	x0, x19
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.14
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2088:
	add	x22, x22, 568
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2097
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	b	.L2094
.L2087:
	mov	w3, w21
	mov	x2, x23
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Scalable_Nesting
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2086:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2085:
	add	x2, x23, 2108
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Dec_Unit_Info
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2084:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Active_Param_sets
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2083:
	mov	w2, w21
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2082:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Display_Orientation
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2081:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2080:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Tone_Mapping_Info
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2079:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Recovery_Point
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2077:
	mov	w2, w21
	add	x1, x22, 56
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2076:
	add	x2, x23, 2064
	add	x1, x22, 8
	mov	x0, x19
	bl	HEVC_Sei_Pic_Timming
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.p2align 3
.L2074:
	add	x2, x23, 2108
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Buf_Period
	cbz	w0, .L2094
	mov	w0, -1
	b	.L2096
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	3
.LC521:
	.xword	.L2075
	.align	3
.LC523:
	.xword	.LC522
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	x23, x2
	bl	_mcount
	mov	w20, 0
	ldr	x0, [x19, 2360]
	b	.L2124
	.p2align 3
.L2126:
	bl	BsSkip
	add	w20, w20, 255
	ldr	x0, [x19, 2360]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2133
.L2124:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2360]
	beq	.L2126
	bl	BsGet
	mov	w21, 0
	mov	w24, w0
	ldr	x0, [x19, 2360]
	b	.L2127
	.p2align 3
.L2128:
	bl	BsSkip
	add	w21, w21, 255
	ldr	x0, [x19, 2360]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2134
.L2127:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2360]
	beq	.L2128
	bl	BsGet
	add	w4, w0, w21
	mov	x1, x22
	add	w3, w24, w20
	mov	x2, x23
	mov	x0, x19
	bl	HEVC_Sei_Payload
	mov	w1, 0
	cbnz	w0, .L2135
.L2125:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2133:
	ldr	x1, .LC525
	mov	w2, 5022
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2134:
	ldr	x1, .LC525
	mov	w2, 5043
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2135:
	ldr	x1, .LC527
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L2125
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	3
.LC525:
	.xword	.LC524
	.align	3
.LC527:
	.xword	.LC526
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L2142
	ldr	x20, [x19, 2392]
	add	x21, x19, 3360
	cbnz	x20, .L2145
	b	.L2148
	.p2align 3
.L2140:
	ldr	x0, [x19, 2360]
	bl	BsIsByteAligned
	cbz	w0, .L2149
	mov	x0, x19
	bl	HEVC_More_Rbsp_Data
	cbz	w0, .L2150
.L2145:
	mov	x2, x20
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbz	w0, .L2140
	ldr	x1, .LC531
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2138:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2150:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 128
	bne	.L2151
.L2142:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2149:
	ldr	x1, .LC533
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2151:
	ldr	x1, .LC535
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2138
.L2148:
	ldr	x1, .LC529
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2138
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	3
.LC529:
	.xword	.LC528
	.align	3
.LC531:
	.xword	.LC530
	.align	3
.LC533:
	.xword	.LC532
	.align	3
.LC535:
	.xword	.LC534
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x2
	mov	x21, x1
	bl	_mcount
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2153
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	mov	w20, w0
	ldr	x1, .LC537
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	cmp	w0, 63
	mov	w23, w0
	bhi	.L2168
	and	w20, w20, 255
	cmp	w0, w20
	bcc	.L2159
	ldr	x24, .LC541
	.p2align 2
.L2158:
	ldr	x0, [x19, 2360]
	mov	w1, 3
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2360]
	mov	x1, x24
	bl	HEVC_ue_v
	cmp	w23, w20
	bcs	.L2158
.L2159:
	ldr	x0, [x19, 2360]
	bl	BsToNextByte
.L2157:
	mov	x2, x22
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbnz	w0, .L2169
	ldr	x0, [x19, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2163
	ldr	x1, [x19, 2400]
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	bcc	.L2157
.L2163:
	mov	w0, 0
.L2155:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2153:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2159
	ldr	x0, [x19, 2360]
	mov	w1, 3
	mov	w20, 0
	bl	BsGet
	ldr	x1, .LC543
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	cmp	w0, 63
	add	w23, w0, 1
	bhi	.L2170
	.p2align 2
.L2164:
	ldr	x0, [x19, 2360]
	mov	w1, 6
	add	w20, w20, 1
	bl	BsGet
	cmp	w20, w23
	bne	.L2164
	b	.L2159
	.p2align 3
.L2169:
	ldr	x1, .LC546
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2168:
	ldr	x1, .LC539
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2155
.L2170:
	ldr	x1, .LC545
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2155
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	3
.LC537:
	.xword	.LC536
	.align	3
.LC539:
	.xword	.LC538
	.align	3
.LC541:
	.xword	.LC540
	.align	3
.LC543:
	.xword	.LC542
	.align	3
.LC545:
	.xword	.LC544
	.align	3
.LC546:
	.xword	.LC530
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	str	x1, [x29, 112]
	bl	_mcount
	add	x27, x20, 324
	ldr	x3, .LC548
	add	x1, x19, 1216
	add	x4, x19, 1536
	mov	x2, 64
	add	x0, x19, 1344
	mov	w25, 0
	ldr	x3, [x3, 104]
	stp	x4, x19, [x29, 136]
	blr	x3
	ldr	x23, .LC560
	ldr	x0, .LC547
	add	x1, x19, 1632
	add	x0, x0, 65536
	stp	x0, x1, [x29, 96]
.L2172:
	ldr	w0, [x27, 1888]
	cbz	w0, .L2192
	uxtw	x0, w25
	mov	w24, 0
	ldp	x1, x21, [x29, 136]
	str	x0, [x29, 128]
	lsl	x0, x0, 2
	str	x1, [x29, 152]
	str	x0, [x29, 120]
.L2191:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	w19, [x27]
	mov	w1, 64
	uxtb	w0, w0
	cmp	w19, 64
	csel	w19, w19, w1, le
	cbz	w25, .L2173
	add	x22, x20, 340
	cbz	w0, .L2205
	cmp	w25, 1
	bls	.L2198
	ldr	x1, .LC556
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 254
	bhi	.L2206
	add	w28, w0, 8
	ldr	x0, [x29, 152]
	str	w28, [x0]
.L2184:
	cmp	w19, wzr
	mov	x26, 0
	bgt	.L2188
	b	.L2183
	.p2align 3
.L2187:
	ldr	w0, [x22, x26, lsl 2]
	add	w1, w1, w2
	and	w1, w1, 255
	add	x26, x26, 1
	sub	w28, w1, w2
	cmp	w19, w26
	strb	w28, [x21, x0]
	ble	.L2183
.L2188:
	ldr	x0, [x20, 2360]
	mov	x1, x23
	bl	HEVC_se_v
	add	w2, w0, w28
	add	w0, w0, 128
	add	w1, w2, 256
	cmp	w0, 255
	asr	w2, w1, 31
	lsr	w2, w2, 24
	bls	.L2187
	ldr	x1, .LC562
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2203:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L2205:
	ldr	x1, .LC550
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L2195
	sub	w0, w24, w0
	cmp	w25, 1
	uxtb	w0, w0
	bls	.L2178
	cmp	w0, w24
	beq	.L2197
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	ldr	x2, [x29, 112]
	lsl	x1, x1, 1
	add	x1, x1, x0, uxtb
	add	x1, x1, 384
	ldr	w1, [x2, x1, lsl 2]
.L2179:
	ldr	x2, [x29, 152]
	str	w1, [x2]
.L2178:
	cmp	w0, w24
	beq	.L2207
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	lsl	x1, x1, 1
	add	x0, x1, x0, uxtb
	ldr	x1, [x29, 112]
	add	x1, x1, x0, lsl 6
.L2181:
	cbz	x1, .L2208
	ldr	x0, .LC548
	sxtw	x2, w19
	ldr	x3, [x0, 104]
	mov	x0, x21
	blr	x3
.L2183:
	add	w24, w24, 1
	cmp	w24, 6
	beq	.L2192
	ldr	x0, [x29, 152]
	add	x21, x21, 64
	add	x0, x0, 4
	str	x0, [x29, 152]
	ldr	w0, [x27, 1888]
	cmp	w0, w24
	bhi	.L2191
	.p2align 2
.L2192:
	ldr	x0, [x29, 136]
	add	w25, w25, 1
	ldr	x1, [x29, 104]
	add	x27, x27, 4
	add	x0, x0, 24
	str	x0, [x29, 136]
	cmp	x0, x1
	ldr	x0, [x29, 144]
	add	x0, x0, 384
	str	x0, [x29, 144]
	bne	.L2172
	mov	w0, 0
	b	.L2203
	.p2align 3
.L2198:
	mov	w28, 8
	b	.L2184
.L2207:
	mov	w1, w24
	mov	w0, w25
	bl	HEVC_GetScalingListDefaultAddress
	mov	x1, x0
	b	.L2181
.L2197:
	mov	w1, 16
	b	.L2179
.L2206:
	ldr	x1, .LC558
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2203
.L2195:
	ldr	x1, .LC552
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2203
.L2208:
	ldr	x1, .LC554
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2203
.L2173:
	cbz	w0, .L2193
	mov	w28, 8
	ldr	x22, [x29, 96]
	b	.L2184
.L2193:
	ldr	x1, .LC550
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L2195
	sub	w0, w24, w0
	uxtb	w0, w0
	b	.L2178
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	3
.LC547:
	.xword	.LANCHOR1
	.align	3
.LC548:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC550:
	.xword	.LC549
	.align	3
.LC552:
	.xword	.LC551
	.align	3
.LC554:
	.xword	.LC553
	.align	3
.LC556:
	.xword	.LC555
	.align	3
.LC558:
	.xword	.LC557
	.align	3
.LC560:
	.xword	.LC559
	.align	3
.LC562:
	.xword	.LC561
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC565
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 1
	str	w0, [x19, 60]
	mov	w21, w0
	beq	.L2210
	cmp	w0, 3
	bhi	.L2360
	ldr	x1, .LC569
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2351:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2360:
	ldr	x1, .LC567
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2210:
	ldr	x1, .LC571
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 8192
	str	w0, [x19, 64]
	bhi	.L2361
	ldr	x1, .LC576
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 4096
	str	w0, [x19, 68]
	bhi	.L2362
	ldr	w2, [x19, 428]
	ldr	w1, [x19, 64]
	cmp	w2, 120
	mul	w0, w0, w1
	beq	.L2218
	bgt	.L2219
	cmp	w2, 60
	beq	.L2283
	ble	.L2363
	cmp	w2, 90
	beq	.L2223
	cmp	w2, 93
	beq	.L2224
	cmp	w2, 63
	beq	.L2364
.L2217:
	ldr	x1, .LC580
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
	.p2align 3
.L2361:
	ldr	x1, .LC573
.L2356:
	mov	w0, w21
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbz	x4, .L2353
.L2355:
	ldr	w0, [x20, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
.L2381:
	ldr	x1, .LC667
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2353:
	mov	w0, -1
	b	.L2351
	.p2align 3
.L2283:
	mov	w2, 30720
	mov	w1, 122880
	.p2align 2
.L2220:
	cmp	w0, w2
	bhi	.L2229
	mov	w0, 16
	str	w0, [x19, 184]
.L2230:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2233
	ldr	x1, .LC582
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldr	x21, .LC583
	ldr	w2, [x19, 60]
	add	x22, x21, 40
	ldr	x1, .LC585
	ldr	w2, [x22, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 72]
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldp	w2, w1, [x19, 60]
	ldr	w3, [x19, 72]
	ldr	w2, [x22, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 76]
	sub	w1, w1, w0
	tbnz	w1, #31, .L2365
	ldr	x1, .LC589
	add	x21, x21, 56
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	x1, .LC591
	ldr	w2, [x21, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 80]
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	w1, [x19, 68]
	ldr	w3, [x19, 80]
	ldr	w2, [x21, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 84]
	sub	w1, w1, w0
	tbnz	w1, #31, .L2366
.L2233:
	ldr	x1, .LC595
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 2
	str	w2, [x19, 88]
	bhi	.L2367
	ldr	x1, .LC599
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 6
	str	w2, [x19, 96]
	bhi	.L2368
	ldr	w0, [x19, 88]
	str	w0, [x20, 196]
	ldr	x1, .LC603
	ldr	w0, [x19, 96]
	str	w0, [x20, 200]
	ldr	w4, [x19, 88]
	ldr	w3, [x19, 96]
	lsl	w2, w4, 2
	lsl	w0, w3, 2
	sub	w2, w2, w4
	sub	w0, w0, w3
	lsl	w2, w2, 1
	lsl	w0, w0, 1
	sub	w2, w2, #48
	sub	w0, w0, #48
	str	w2, [x19, 92]
	str	w0, [x19, 100]
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 12
	bhi	.L2369
	add	w0, w0, 4
	mov	w1, 1
	stp	w0, w0, [x19, 116]
	mov	w23, 0
	mov	w21, 0
	ldr	x0, [x20, 2360]
	bl	BsGet
	ldr	x26, .LC607
	mov	w27, w0
	ldr	x25, .LC609
	ldr	x24, .LC611
	b	.L2244
	.p2align 3
.L2238:
	ldr	w0, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w0
	bhi	.L2243
.L2244:
	add	x22, x19, x21, uxtw 2
	ldr	x0, [x20, 2360]
	mov	x1, x26
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 328]
	mov	x1, x25
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x22, 360]
	mov	x1, x24
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x22, 392]
	ldr	w0, [x22, 328]
	cmp	w23, w0
	csel	w23, w23, w0, cs
	cbnz	w27, .L2238
	ldr	w2, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w2
	bhi	.L2243
	.p2align 2
.L2325:
	add	x0, x19, x21, uxtw 2
	ldr	w1, [x19, 328]
	add	w21, w21, 1
	cmp	w21, w2
	str	w1, [x0, 328]
	ldr	w1, [x19, 360]
	str	w1, [x0, 360]
	ldr	w1, [x19, 392]
	str	w1, [x0, 392]
	bls	.L2325
.L2243:
	ldr	w0, [x19, 184]
	ldr	x1, .LC613
	cmp	w0, w23
	csel	w23, w0, w23, ls
	str	w23, [x19, 184]
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L2370
	ldr	x1, .LC617
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w21, w0
	bhi	.L2371
	add	w2, w22, 3
	add	w1, w0, w2
	sub	w0, w1, #4
	cmp	w0, 2
	stp	w2, w1, [x19, 124]
	bhi	.L2372
	ldp	w4, w0, [x19, 64]
	mov	w23, 1
	lsl	w1, w23, w1
	lsl	w2, w23, w2
	stp	w2, w1, [x19, 132]
	udiv	w3, w4, w1
	stp	w1, w1, [x19, 140]
	udiv	w2, w0, w1
	msub	w4, w3, w1, w4
	cmp	w4, wzr
	csinc	w3, w3, w3, eq
	str	w3, [x19, 188]
	msub	w0, w2, w1, w0
	ldr	x1, .LC623
	cmp	w0, wzr
	csinc	w2, w2, w2, eq
	str	w2, [x19, 192]
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L2373
	ldr	x1, .LC627
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 3
	bhi	.L2374
	ldr	w2, [x19, 124]
	add	w1, w22, 2
	str	w1, [x19, 148]
	cmp	w1, w2
	bcs	.L2375
	add	w1, w0, w1
	str	w1, [x19, 152]
	cmp	w1, 5
	bhi	.L2254
	ldr	w0, [x19, 128]
	cmp	w1, w0
	bhi	.L2254
	ldr	x1, .LC635
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x19, 164]
	ldr	w1, [x19, 128]
	ldr	w2, [x19, 148]
	sub	w1, w1, w2
	cmp	w0, w1
	bhi	.L2376
	ldr	x1, .LC639
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x19, 168]
	ldr	w1, [x19, 128]
	ldr	w4, [x19, 148]
	sub	w1, w1, w4
	cmp	w0, w1
	bhi	.L2257
	ldr	w2, [x19, 140]
	mov	w3, 1
	lsl	w0, w3, w4
	mov	w1, 0
	lsr	w2, w2, w21
	cmp	w2, w0
	bls	.L2259
	.p2align 2
.L2324:
	add	w1, w1, 1
	add	w0, w4, w1
	lsl	w0, w3, w0
	cmp	w0, w2
	bcc	.L2324
.L2259:
	add	w1, w21, w1
	str	w1, [x19, 172]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3]
	cbz	w0, .L2261
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 4]
	cbnz	w0, .L2377
.L2261:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 6]
	cbnz	w0, .L2262
	ldr	w2, [x19, 68]
	cmp	w2, 64
	bls	.L2378
.L2262:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	str	w0, [x19, 104]
	cbz	w0, .L2263
	ldr	x0, [x20, 2360]
	mov	w1, 4
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 108]
	mov	w1, 4
	ldr	x0, [x20, 2360]
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 112]
	ldr	x1, .LC647
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w21, w0
	bhi	.L2379
.L2264:
	ldr	x1, .LC651
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w22, w0
	bhi	.L2380
.L2265:
	add	w0, w21, 3
	str	w0, [x19, 156]
	add	w0, w22, w0
	str	w0, [x19, 160]
	cmp	w0, 5
	bhi	.L2266
	ldr	w1, [x19, 128]
	cmp	w0, w1
	bhi	.L2266
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 7]
.L2263:
	ldr	x1, .LC657
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 64
	str	w0, [x19, 176]
	bhi	.L2268
	mov	w21, 0
	cbnz	w0, .L2323
	b	.L2274
	.p2align 3
.L2272:
	ldr	w0, [x19, 176]
	cmp	w21, w0
	bcs	.L2274
.L2323:
	uxtw	x5, w21
	mov	w3, w21
	lsl	x2, x5, 2
	mov	x1, x19
	sub	x2, x2, x5
	mov	x0, x20
	lsl	x4, x2, 3
	add	w21, w21, 1
	sub	x2, x4, x2
	lsl	x2, x2, 1
	sub	x2, x2, x5
	add	x2, x19, x2, lsl 2
	add	x2, x2, 2164
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L2272
	ldr	x1, .LC661
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
	.p2align 3
.L2229:
	cmp	w0, w1, lsr 1
	bhi	.L2231
	mov	w0, 12
	str	w0, [x19, 184]
	b	.L2230
	.p2align 3
.L2362:
	ldr	x1, .LC578
	b	.L2356
	.p2align 3
.L2219:
	cmp	w2, 156
	beq	.L2226
	bgt	.L2227
	cmp	w2, 150
	beq	.L2226
	cmp	w2, 153
	beq	.L2226
	cmp	w2, 123
	bne	.L2217
.L2218:
	mov	w2, 32768
	mov	w1, 2228224
	movk	w2, 0x8, lsl 16
	b	.L2220
	.p2align 3
.L2231:
	lsl	w2, w1, 2
	sub	w1, w2, w1
	cmp	w0, w1, lsr 2
	bhi	.L2232
	mov	w0, 8
	str	w0, [x19, 184]
	b	.L2230
	.p2align 3
.L2367:
	ldr	x1, .LC597
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbz	x4, .L2353
	ldr	w1, [x19, 88]
	mov	w3, 8
	ldr	w0, [x20, 252]
	add	x2, x29, 104
	stp	wzr, w1, [x29, 104]
	mov	w1, 119
	blr	x4
	mov	w0, -1
	b	.L2351
	.p2align 3
.L2274:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbz	w0, .L2271
	ldr	x1, .LC663
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 32
	str	w0, [x19, 180]
	bhi	.L2277
	mov	w22, 0
	cbz	w0, .L2271
	.p2align 2
.L2322:
	ldr	w1, [x19, 116]
	uxtw	x21, w22
	ldr	x0, [x20, 2360]
	add	w22, w22, 1
	bl	BsGet
	add	x2, x19, x21, lsl 2
	add	x21, x19, x21
	mov	w1, 1
	str	w0, [x2, 196]
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x21, 13]
	ldr	w0, [x19, 180]
	cmp	w22, w0
	bcc	.L2322
.L2271:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 11]
	cbz	w0, .L2276
	mov	x2, x19
	add	x1, x19, 2064
	mov	x0, x20
	bl	HEVC_DecVuiParam
	cbnz	w0, .L2381
.L2276:
	ldp	w3, w4, [x19, 64]
	ldr	w1, [x19, 2076]
	ldr	w2, [x19, 2080]
	ldr	w0, [x19, 2072]
	bl	HEVC_GetDar
	str	w0, [x19, 2068]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 12]
	cbnz	w0, .L2350
	.p2align 2
.L2281:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
	b	.L2351
	.p2align 3
.L2382:
	ldr	x0, [x20, 2360]
	bl	BsGet
.L2350:
	ldr	x0, [x20, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2281
	ldr	x2, [x20, 2400]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcs	.L2281
	b	.L2382
	.p2align 3
.L2227:
	cmp	w2, 183
	beq	.L2228
	cmp	w2, 186
	beq	.L2228
	cmp	w2, 180
	bne	.L2217
.L2228:
	mov	w2, 8912896
	mov	w1, 35651584
	b	.L2220
	.p2align 3
.L2363:
	cbz	w2, .L2222
	cmp	w2, 30
	bne	.L2217
.L2222:
	mov	w2, 9216
	mov	w1, 36864
	b	.L2220
	.p2align 3
.L2226:
	mov	w2, 2228224
	mov	w1, 8912896
	b	.L2220
	.p2align 3
.L2223:
	mov	w2, 7168
	mov	w1, 28672
	movk	w2, 0x2, lsl 16
	movk	w1, 0x8, lsl 16
	b	.L2220
.L2364:
	mov	w2, 61440
	mov	w1, 245760
	b	.L2220
	.p2align 3
.L2224:
	mov	w2, 245760
	mov	w1, 983040
	b	.L2220
	.p2align 3
.L2232:
	mov	w0, 6
	str	w0, [x19, 184]
	b	.L2230
.L2378:
	ldr	x1, .LC645
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbnz	x4, .L2355
	mov	w0, -1
	b	.L2351
.L2377:
	add	x1, x19, 432
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbz	w0, .L2261
	ldr	x1, .LC643
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
	.p2align 3
.L2254:
	ldr	x1, .LC633
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2380:
	ldr	x1, .LC653
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2265
.L2379:
	ldr	x1, .LC649
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2264
.L2369:
	ldr	x1, .LC605
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2370:
	ldr	x1, .LC615
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2373:
	ldr	x1, .LC625
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2376:
	ldr	x1, .LC637
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2266:
	ldr	x1, .LC655
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2372:
	ldr	x1, .LC621
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2371:
	ldr	x1, .LC619
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2374:
	ldr	x1, .LC629
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2368:
	ldr	x1, .LC601
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2375:
	ldr	x1, .LC631
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2257:
	ldr	x1, .LC641
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2365:
	ldr	x1, .LC587
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2268:
	ldr	x1, .LC659
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2366:
	ldr	x1, .LC593
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
.L2277:
	ldr	x1, .LC665
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2351
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	3
.LC565:
	.xword	.LC564
	.align	3
.LC567:
	.xword	.LC566
	.align	3
.LC569:
	.xword	.LC568
	.align	3
.LC571:
	.xword	.LC570
	.align	3
.LC573:
	.xword	.LC572
	.align	3
.LC574:
	.xword	g_event_report
	.align	3
.LC576:
	.xword	.LC575
	.align	3
.LC578:
	.xword	.LC577
	.align	3
.LC580:
	.xword	.LC579
	.align	3
.LC582:
	.xword	.LC581
	.align	3
.LC583:
	.xword	.LANCHOR5
	.align	3
.LC585:
	.xword	.LC584
	.align	3
.LC587:
	.xword	.LC586
	.align	3
.LC589:
	.xword	.LC588
	.align	3
.LC591:
	.xword	.LC590
	.align	3
.LC593:
	.xword	.LC592
	.align	3
.LC595:
	.xword	.LC594
	.align	3
.LC597:
	.xword	.LC596
	.align	3
.LC599:
	.xword	.LC598
	.align	3
.LC601:
	.xword	.LC600
	.align	3
.LC603:
	.xword	.LC602
	.align	3
.LC605:
	.xword	.LC604
	.align	3
.LC607:
	.xword	.LC606
	.align	3
.LC609:
	.xword	.LC608
	.align	3
.LC611:
	.xword	.LC610
	.align	3
.LC613:
	.xword	.LC612
	.align	3
.LC615:
	.xword	.LC614
	.align	3
.LC617:
	.xword	.LC616
	.align	3
.LC619:
	.xword	.LC618
	.align	3
.LC621:
	.xword	.LC620
	.align	3
.LC623:
	.xword	.LC622
	.align	3
.LC625:
	.xword	.LC624
	.align	3
.LC627:
	.xword	.LC626
	.align	3
.LC629:
	.xword	.LC628
	.align	3
.LC631:
	.xword	.LC630
	.align	3
.LC633:
	.xword	.LC632
	.align	3
.LC635:
	.xword	.LC634
	.align	3
.LC637:
	.xword	.LC636
	.align	3
.LC639:
	.xword	.LC638
	.align	3
.LC641:
	.xword	.LC640
	.align	3
.LC643:
	.xword	.LC642
	.align	3
.LC645:
	.xword	.LC644
	.align	3
.LC647:
	.xword	.LC646
	.align	3
.LC649:
	.xword	.LC648
	.align	3
.LC651:
	.xword	.LC650
	.align	3
.LC653:
	.xword	.LC652
	.align	3
.LC655:
	.xword	.LC654
	.align	3
.LC657:
	.xword	.LC656
	.align	3
.LC659:
	.xword	.LC658
	.align	3
.LC661:
	.xword	.LC660
	.align	3
.LC663:
	.xword	.LC662
	.align	3
.LC665:
	.xword	.LC664
	.align	3
.LC667:
	.xword	.LC666
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x22, .LC670
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 96
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x0, [x19, 2360]
	mov	w1, 4
	bl	BsGet
	mov	w24, w0
	ldr	w2, [x19, 156]
	cmp	w2, w0
	bls	.L2396
	ldr	x0, [x19, 2400]
	ldr	w0, [x0, 24]
	cbz	w0, .L2397
	mov	w20, 0
	mov	w25, 0
.L2386:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	mov	w3, w20
	mov	w2, 1
	add	x1, x29, 96
	mov	x0, x19
	bl	HEVC_DecPTL
	cbnz	w0, .L2398
	ldr	x1, .LC678
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	mov	w21, w0
	ldr	w2, [x19, 160]
	cmp	w0, w2
	bcs	.L2399
	mov	w20, 12660
	ldr	x1, [x19, 2376]
	uxtb	w26, w23
	umull	x20, w0, w20
	add	x1, x1, x20
	ldrb	w0, [x1, 1]
	cbz	w0, .L2390
	ldr	x27, .LC682
	mov	x2, 12660
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x23, x27, 3328
	mov	x0, x23
	blr	x3
	strb	w26, [x23, 2]
	ldr	x3, [x22, 104]
	add	x1, x29, 96
	mov	x2, 8
	strb	wzr, [x23, 46]
	stp	w24, w25, [x23, 48]
	add	x0, x27, 3752
	blr	x3
	str	w21, [x23, 56]
	mov	x1, x23
	mov	x0, x19
	bl	HEVC_ProcessSPS
	mov	w24, w0
	cbnz	w0, .L2400
	ldr	x0, [x19, 2376]
	mov	w1, 1
	ldr	x3, [x22, 112]
	mov	x2, 12660
	strb	w1, [x27, 3328]
	add	x0, x0, x20
	strb	w1, [x23, 1]
	mov	x1, x23
	blr	x3
	ldr	x0, [x19, 2376]
	add	x20, x0, x20
	str	x20, [x19, 2392]
.L2385:
	mov	w0, w24
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2397:
	ldr	x0, [x19, 2360]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 8
	mov	w20, w0
	mov	w25, w0
	bls	.L2386
	ldr	x1, .LC674
	mov	w2, 8
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2385
	.p2align 3
.L2390:
	str	w24, [x1, 48]
	mov	x2, 8
	add	x1, x29, 96
	ldr	x0, [x19, 2376]
	add	x0, x0, x20
	str	w25, [x0, 52]
	ldr	x0, [x19, 2376]
	add	x0, x0, x20
	strb	w26, [x0, 2]
	ldr	x0, [x19, 2376]
	add	x0, x0, x20
	strb	wzr, [x0, 46]
	ldr	x0, [x19, 2376]
	ldr	x3, [x22, 104]
	add	x0, x0, x20
	add	x0, x0, 424
	blr	x3
	ldr	x1, [x19, 2376]
	mov	x0, x19
	add	x1, x1, x20
	str	w21, [x1, 56]
	ldr	x1, [x19, 2376]
	add	x1, x1, x20
	bl	HEVC_ProcessSPS
	mov	w24, w0
	cbnz	w0, .L2401
	ldr	x0, [x19, 2376]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2376]
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2376]
	add	x20, x0, x20
	str	x20, [x19, 2392]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2399:
	ldr	x1, .LC680
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 160]
	cmp	w21, w1
	bcc	.L2395
	ldr	x0, .LC681
	ldr	x4, [x0]
	cbz	x4, .L2395
	ldr	w0, [x19, 252]
	add	x2, x29, 104
	stp	w21, w1, [x29, 104]
	mov	w3, 8
	mov	w1, 109
	mov	w24, -1
	blr	x4
	ldr	x27, [sp, 80]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2395:
	mov	w24, -1
	b	.L2385
	.p2align 3
.L2398:
	ldr	x1, .LC676
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2385
	.p2align 3
.L2396:
	ldr	x1, .LC672
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2385
	.p2align 3
.L2400:
	ldr	x3, [x19, 2376]
	mov	w2, w21
	ldr	x1, .LC684
	mov	w0, 1
	add	x20, x3, x20
	str	x20, [x19, 2392]
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2385
.L2401:
	ldr	x1, .LC686
	mov	w2, w21
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2376]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2376]
	add	x20, x0, x20
	strb	wzr, [x20, 1]
	b	.L2385
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	3
.LC670:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC672:
	.xword	.LC671
	.align	3
.LC674:
	.xword	.LC673
	.align	3
.LC676:
	.xword	.LC675
	.align	3
.LC678:
	.xword	.LC677
	.align	3
.LC680:
	.xword	.LC679
	.align	3
.LC681:
	.xword	g_event_report
	.align	3
.LC682:
	.xword	.LANCHOR6
	.align	3
.LC684:
	.xword	.LC683
	.align	3
.LC686:
	.xword	.LC685
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	w22, 1
	bl	_mcount
	mov	w0, 1
	strb	w0, [x19, 16]
	stp	w22, w22, [x19, 68]
	ldr	x1, .LC689
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	str	w0, [x19, 32]
	tbnz	w0, #31, .L2403
	ldr	w1, [x20, 160]
	cmp	w0, w1
	bge	.L2403
	ldr	x1, [x20, 2376]
	mov	w21, 12660
	smaddl	x21, w0, w21, x1
	ldrb	w1, [x21, 1]
	cbz	w1, .L2511
	ldr	x0, [x20, 2360]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, w22
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 3
	ldr	x0, [x20, 2360]
	bl	BsGet
	str	w0, [x19, 36]
	mov	w1, w22
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, w22
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 5]
	ldr	x1, .LC695
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 40]
	bhi	.L2512
	ldr	x1, .LC699
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 44]
	bhi	.L2513
	ldr	x1, .LC703
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w2, w0, 26
	str	w2, [x19, 48]
	mov	w0, 51
	ldr	w3, [x21, 92]
	neg	w1, w3
	cmp	w2, w1
	ccmp	w2, w0, 0, ge
	bgt	.L2514
	ldr	x0, [x20, 2360]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, w22
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, w22
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbnz	w0, .L2515
	mov	w0, 0
	str	wzr, [x19, 52]
.L2412:
	str	w0, [x19, 56]
	ldr	x1, .LC711
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 60]
	bhi	.L2516
	ldr	x1, .LC715
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 64]
	bhi	.L2517
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 11]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 14]
	ldrb	w1, [x19, 13]
	cbnz	w1, .L2518
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L2449:
	ldr	w3, [x19, 68]
	cmp	w3, wzr
	ble	.L2454
.L2448:
	ldr	w4, [x21, 140]
	add	x0, x19, 172
	mov	w1, 0
	.p2align 2
.L2453:
	ldrsh	w2, [x0]
	add	w1, w1, 1
	add	x0, x0, 2
	mul	w2, w2, w4
	cmp	w2, 64
	bhi	.L2452
	ldr	w5, [x21, 64]
	cmp	w5, 64
	bhi	.L2519
.L2452:
	cmp	w1, w3
	blt	.L2453
.L2454:
	ldr	w1, [x19, 72]
	cmp	w1, wzr
	ble	.L2451
	ldrsh	w2, [x19, 212]
	ldr	w3, [x21, 140]
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L2455
	sub	w1, w1, #1
	mov	x0, x19
	add	x1, x19, x1, lsl 1
	b	.L2457
	.p2align 3
.L2458:
	ldrsh	w2, [x0, 214]
	add	x0, x0, 2
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L2455
.L2457:
	cmp	x1, x0
	bne	.L2458
.L2451:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 18]
	cbnz	w0, .L2520
.L2460:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 21]
	cbz	w0, .L2463
	add	x1, x19, 256
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbnz	w0, .L2521
.L2463:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 22]
	ldr	x1, .LC758
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 2
	cmp	w2, 1
	str	w2, [x19, 84]
	ble	.L2464
	ldr	w0, [x21, 128]
	cmp	w2, w0
	bhi	.L2464
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 24]
	cbz	w0, .L2467
	ldr	x0, [x20, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2467
	.p2align 2
.L2522:
	ldr	x2, [x20, 2400]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcs	.L2467
	ldr	x0, [x20, 2360]
	bl	BsGet
	strb	w0, [x19, 25]
	ldr	x0, [x20, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	bgt	.L2522
.L2467:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2515:
	ldr	x1, .LC707
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	cmp	w0, 3
	str	w0, [x19, 52]
	bls	.L2412
	ldr	x1, .LC709
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
	.p2align 3
.L2518:
	ldr	x1, .LC719
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 19
	str	w2, [x19, 68]
	bhi	.L2523
	ldr	x1, .LC723
	ldr	x0, [x20, 2360]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 21
	str	w2, [x19, 72]
	bhi	.L2524
	ldr	w3, [x19, 68]
	cmp	w3, 10
	bgt	.L2525
	cmp	w2, 11
	ble	.L2420
	ldr	x1, .LC730
	mov	w3, w2
	mov	w2, 11
.L2508:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC728
	ldr	x4, [x0]
	cbz	x4, .L2503
.L2505:
	ldr	w0, [x20, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2499:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2455:
	ldr	x1, .LC746
.L2507:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC728
	ldr	x4, [x0]
	cbnz	x4, .L2505
.L2503:
	mov	w0, -1
.L2530:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2519:
	ldr	x1, .LC744
	b	.L2507
	.p2align 3
.L2514:
	ldr	x1, .LC705
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2420:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 15]
	cbnz	w0, .L2526
	ldr	w0, [x19, 68]
	sub	w1, w0, #1
	cmp	w1, wzr
	ble	.L2425
	ldr	x23, .LC732
	mov	w22, 0
	b	.L2429
	.p2align 3
.L2528:
	cmp	w3, w4
	bhi	.L2427
	ldr	w0, [x19, 68]
	add	w22, w22, 1
	sub	w1, w0, #1
	cmp	w1, w22
	ble	.L2527
.L2429:
	ldr	x0, [x20, 2360]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 88]
	ldr	w4, [x21, 188]
	tbz	w3, #31, .L2528
.L2427:
	ldr	x1, .LC734
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2525:
	ldr	x1, .LC727
	mov	w2, 10
	b	.L2508
.L2520:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	ldr	x0, [x20, 2360]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 20]
	cbnz	w0, .L2460
	ldr	x1, .LC748
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 76]
	bhi	.L2529
.L2462:
	ldr	x1, .LC752
	ldr	x0, [x20, 2360]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 80]
	bls	.L2460
	ldr	x1, .LC754
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 80]
	b	.L2460
.L2526:
	ldr	w0, [x19, 68]
.L2431:
	cmp	w0, wzr
	add	x5, x19, 172
	mov	w3, 0
	ble	.L2424
	.p2align 2
.L2483:
	add	w3, w3, 1
	ldr	w4, [x21, 188]
	sub	w2, w3, #1
	cmp	w3, w0
	mul	w1, w3, w4
	mul	w2, w2, w4
	udiv	w1, w1, w0
	udiv	w2, w2, w0
	sub	w1, w1, w2
	strh	w1, [x5], 2
	bne	.L2483
.L2424:
	ldr	w4, [x19, 72]
	add	x6, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L2439
	.p2align 2
.L2482:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w2, w3, #1
	cmp	w3, w4
	mul	w1, w3, w5
	mul	w2, w2, w5
	udiv	w1, w1, w4
	udiv	w2, w2, w4
	sub	w1, w1, w2
	strh	w1, [x6], 2
	bne	.L2482
.L2439:
	cmp	w0, 1
	bne	.L2447
	ldr	w3, [x19, 72]
	cmp	w3, 1
	beq	.L2448
.L2447:
	ldr	x0, [x20, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L2449
.L2403:
	ldr	x1, .LC691
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2511:
	ldr	x1, .LC693
	mov	w2, w0
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2512:
	ldr	x1, .LC697
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2513:
	ldr	x1, .LC701
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2516:
	ldr	x1, .LC713
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2517:
	ldr	x1, .LC717
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2464:
	ldr	x1, .LC760
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2530
.L2527:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	ble	.L2437
.L2430:
	ldr	x23, .LC736
	mov	w22, 0
	b	.L2436
	.p2align 3
.L2532:
	cmp	w3, w4
	bhi	.L2434
	ldr	w0, [x19, 72]
	add	w22, w22, 1
	sub	w0, w0, #1
	cmp	w0, w22
	ble	.L2531
.L2436:
	ldr	x0, [x20, 2360]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 128]
	ldr	w4, [x21, 192]
	tbz	w3, #31, .L2532
.L2434:
	ldr	x1, .LC738
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2523:
	ldr	x1, .LC721
	mov	w3, 20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2529:
	ldr	x1, .LC750
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 76]
	b	.L2462
.L2531:
	ldr	w0, [x19, 68]
.L2437:
	ldrb	w1, [x19, 15]
	cbnz	w1, .L2431
	add	x5, x19, x0, sxtw 1
	sub	w2, w0, #1
	ldrsh	w3, [x21, 188]
	cmp	w2, wzr
	strh	w3, [x5, 170]
	ble	.L2442
	sub	w6, w0, #2
	add	x4, x19, 88
	add	x6, x6, 45
	add	x6, x19, x6, lsl 1
	.p2align 2
.L2443:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 170]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 170]
	bne	.L2443
.L2442:
	cmp	w3, wzr
	ble	.L2533
	ldr	w1, [x19, 72]
	ldrsh	w3, [x21, 192]
	sub	w2, w1, #1
	add	x5, x19, x1, sxtw 1
	cmp	w2, wzr
	strh	w3, [x5, 210]
	ble	.L2445
	sub	w6, w1, #2
	add	x4, x19, 128
	add	x6, x6, 65
	add	x6, x19, x6, lsl 1
	.p2align 2
.L2446:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x6, x4
	ldrh	w1, [x5, 210]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 210]
	bne	.L2446
.L2445:
	cmp	w3, wzr
	bgt	.L2439
	ldr	x1, .LC742
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
	.p2align 3
.L2524:
	ldr	x1, .LC725
	mov	w3, 22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2521:
	ldr	x1, .LC756
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
.L2425:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	bgt	.L2430
	add	x1, x19, x0, sxtw 1
	ldrsh	w3, [x21, 188]
	sub	w2, w0, #1
	strh	w3, [x1, 170]
	b	.L2442
.L2533:
	ldr	x1, .LC740
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2499
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	3
.LC689:
	.xword	.LC688
	.align	3
.LC691:
	.xword	.LC690
	.align	3
.LC693:
	.xword	.LC692
	.align	3
.LC695:
	.xword	.LC694
	.align	3
.LC697:
	.xword	.LC696
	.align	3
.LC699:
	.xword	.LC698
	.align	3
.LC701:
	.xword	.LC700
	.align	3
.LC703:
	.xword	.LC702
	.align	3
.LC705:
	.xword	.LC704
	.align	3
.LC707:
	.xword	.LC706
	.align	3
.LC709:
	.xword	.LC708
	.align	3
.LC711:
	.xword	.LC710
	.align	3
.LC713:
	.xword	.LC712
	.align	3
.LC715:
	.xword	.LC714
	.align	3
.LC717:
	.xword	.LC716
	.align	3
.LC719:
	.xword	.LC718
	.align	3
.LC721:
	.xword	.LC720
	.align	3
.LC723:
	.xword	.LC722
	.align	3
.LC725:
	.xword	.LC724
	.align	3
.LC727:
	.xword	.LC726
	.align	3
.LC728:
	.xword	g_event_report
	.align	3
.LC730:
	.xword	.LC729
	.align	3
.LC732:
	.xword	.LC731
	.align	3
.LC734:
	.xword	.LC733
	.align	3
.LC736:
	.xword	.LC735
	.align	3
.LC738:
	.xword	.LC737
	.align	3
.LC740:
	.xword	.LC739
	.align	3
.LC742:
	.xword	.LC741
	.align	3
.LC744:
	.xword	.LC743
	.align	3
.LC746:
	.xword	.LC745
	.align	3
.LC748:
	.xword	.LC747
	.align	3
.LC750:
	.xword	.LC749
	.align	3
.LC752:
	.xword	.LC751
	.align	3
.LC754:
	.xword	.LC753
	.align	3
.LC756:
	.xword	.LC755
	.align	3
.LC758:
	.xword	.LC757
	.align	3
.LC760:
	.xword	.LC759
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC762
	ldr	x0, [x19, 2360]
	bl	HEVC_ue_v
	mov	w21, w0
	ldr	w3, [x19, 164]
	cmp	w0, w3
	bcs	.L2540
	mov	w20, 1888
	umull	x20, w0, w20
	ldr	x0, [x19, 2384]
	add	x1, x0, x20
	ldrb	w0, [x0, x20]
	cbnz	w0, .L2541
	str	w21, [x1, 28]
	mov	x0, x19
	ldr	x1, [x19, 2384]
	add	x1, x1, x20
	bl	HEVC_ProcessPPS
	mov	w22, w0
	cbnz	w0, .L2542
	ldr	x0, [x19, 2384]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2384]
	strb	w1, [x0, x20]
.L2536:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2541:
	ldr	x25, .LC765
	mov	x2, 1888
	ldr	x24, .LC766
	mov	w1, 0
	add	x23, x24, 3328
	ldr	x3, [x25, 96]
	mov	x0, x23
	blr	x3
	str	w21, [x23, 28]
	mov	x1, x23
	mov	x0, x19
	bl	HEVC_ProcessPPS
	mov	w22, w0
	cbnz	w0, .L2543
	ldr	x0, [x19, 2384]
	mov	w1, 1
	ldr	x3, [x25, 112]
	mov	x2, 1888
	strb	w1, [x23, 1]
	add	x0, x0, x20
	strb	w1, [x24, 3328]
	mov	x1, x23
	blr	x3
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2543:
	ldr	x1, .LC768
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2536
	.p2align 3
.L2540:
	ldr	x1, .LC764
	mov	w2, w0
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2536
.L2542:
	ldr	x1, .LC768
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2384]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2384]
	strb	wzr, [x0, x20]
	b	.L2536
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	3
.LC762:
	.xword	.LC761
	.align	3
.LC764:
	.xword	.LC763
	.align	3
.LC765:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC766:
	.xword	.LANCHOR6
	.align	3
.LC768:
	.xword	.LC767
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x28, 4708]
	mov	w4, 1888
	ldr	w0, [x28, 4724]
	ldr	x2, [x28, 2384]
	cmp	w1, 1
	smaddl	x2, w0, w4, x2
	beq	.L2618
	cbnz	w1, .L2548
	ldrb	w0, [x2, 11]
	cbz	w0, .L2548
.L2546:
	ldr	x1, .LC771
	ldr	x0, [x28, 2360]
	ldr	w19, [x2, 32]
	add	x2, x28, 4096
	mov	x21, x2
	ldr	x20, [x28, 2376]
	str	x2, [x29, 104]
	bl	HEVC_ue_v
	cmp	w0, 7
	str	w0, [x28, 4844]
	add	x22, x21, 748
	bhi	.L2619
	mov	w1, 12660
	smaddl	x19, w19, w1, x20
	ldr	w1, [x19, 60]
	cbnz	w1, .L2620
	str	w0, [x22, 132]
.L2590:
	ldr	w0, [x28, 4764]
	mov	w20, 0
	cbz	w0, .L2560
	.p2align 2
.L2603:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4764]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L2603
	ldr	w0, [x19, 60]
	cbz	w0, .L2556
	mov	w20, 0
	cbz	w1, .L2560
	.p2align 2
.L2602:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4764]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L2602
.L2556:
	mov	w27, 0
	cbz	w1, .L2560
	ldr	x0, [x29, 104]
	ldr	x26, .LC789
	add	x21, x0, 748
	b	.L2601
	.p2align 3
.L2562:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 4848]
	str	w0, [x20, 4980]
.L2564:
	ldr	w0, [x19, 60]
	cbz	w0, .L2566
	add	x0, x29, 240
	add	x0, x0, x22, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L2567
	lsl	x22, x22, 3
	ldr	w2, [x21, 132]
	add	x1, x28, x22
	add	x22, x21, x22
	mov	w0, 1
	lsl	w0, w0, w2
	str	wzr, [x1, 5172]
	str	w0, [x1, 5044]
	str	w0, [x22, 204]
	str	wzr, [x22, 332]
.L2566:
	ldr	w0, [x28, 4764]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L2560
.L2601:
	uxtw	x22, w27
	add	x0, x29, 240
	lsl	x20, x22, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L2562
	ldr	x1, .LC781
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L2621
	ldr	w2, [x21]
	add	x20, x28, x20
	mov	w23, 1
	ldr	x1, .LC785
	lsl	w2, w23, w2
	add	w0, w2, w0
	str	w0, [x20, 4980]
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	str	w0, [x20, 4848]
	bls	.L2564
	ldr	x1, .LC787
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
	.p2align 3
.L2618:
	ldrb	w0, [x2, 10]
	cbnz	w0, .L2546
.L2548:
	mov	w0, 0
.L2616:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L2567:
	ldr	x0, [x28, 2360]
	mov	x1, x26
	add	x20, x22, 1
	add	x25, x28, x22, lsl 3
	mov	w24, 128
	mov	w22, 1
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	add	x20, x28, x20, lsl 3
	mov	w23, 127
	ldr	x1, .LC793
	bhi	.L2622
.L2568:
	ldr	w6, [x21, 132]
	lsl	w6, w22, w6
	add	w0, w6, w0
	str	w0, [x25, 5044]
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w6, -128
	bhi	.L2623
	ldr	w1, [x25, 5044]
	add	x25, x25, 4
	ldr	w7, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w7
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w23, le
	cmn	w0, #128
	csel	w0, w0, w6, ge
	cmp	x20, x25
	str	w0, [x25, 5168]
	beq	.L2566
	ldr	x0, [x28, 2360]
	mov	x1, x26
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	ldr	x1, .LC793
	bls	.L2568
.L2622:
	ldr	x1, .LC791
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L2560:
	ldr	w0, [x28, 4708]
	cbnz	w0, .L2548
	ldr	w0, [x28, 4768]
	cbz	w0, .L2548
	mov	w20, 0
	.p2align 2
.L2574:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4768]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L2574
	ldr	w0, [x19, 60]
	cbnz	w0, .L2624
.L2575:
	mov	w25, 0
	cbz	w1, .L2548
	ldr	x0, [x29, 104]
	ldr	x23, .LC805
	add	x21, x0, 748
	b	.L2599
	.p2align 3
.L2579:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 4912]
	str	w0, [x20, 5300]
.L2581:
	ldr	w0, [x19, 60]
	cbz	w0, .L2583
	add	x0, x29, 240
	add	x0, x0, x26, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L2584
	lsl	x26, x26, 3
	ldr	w4, [x21, 132]
	add	x1, x28, x26
	add	x26, x21, x26
	mov	w0, 1
	lsl	w0, w0, w4
	str	wzr, [x1, 5492]
	str	w0, [x1, 5364]
	str	w0, [x26, 524]
	str	wzr, [x26, 652]
.L2583:
	ldr	w0, [x28, 4768]
	add	w25, w25, 1
	cmp	w0, w25
	bls	.L2548
.L2599:
	uxtw	x26, w25
	add	x0, x29, 240
	lsl	x20, x26, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L2579
	ldr	x1, .LC797
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L2625
	ldr	w1, [x21]
	add	x20, x28, x20
	mov	w27, 1
	lsl	w1, w27, w1
	add	w0, w1, w0
	str	w0, [x20, 5300]
	ldr	x1, .LC801
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	str	w0, [x20, 4912]
	add	w0, w0, 128
	cmp	w0, 255
	bls	.L2581
	ldr	x1, .LC803
	mov	w0, w27
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
	.p2align 3
.L2584:
	add	x22, x28, x26, lsl 3
	add	x26, x26, 1
	mov	w20, 1
	mov	w24, 128
	add	x26, x28, x26, lsl 3
	mov	w27, 127
.L2587:
	ldr	x0, [x28, 2360]
	mov	x1, x23
	bl	HEVC_se_v
	add	w5, w0, 128
	cmp	w5, 255
	ldr	x1, .LC809
	bhi	.L2626
	ldr	w5, [x21, 132]
	lsl	w5, w20, w5
	add	w0, w5, w0
	str	w0, [x22, 5364]
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w5, -128
	bhi	.L2627
	ldr	w1, [x22, 5364]
	add	x22, x22, 4
	ldr	w6, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w6
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w27, le
	cmn	w0, #128
	csel	w0, w0, w5, ge
	str	w0, [x22, 5488]
	cmp	x22, x26
	bne	.L2587
	b	.L2583
	.p2align 3
.L2620:
	ldr	x1, .LC775
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 14
	bhi	.L2628
	ldr	w1, [x28, 4844]
	add	w0, w0, w1
	str	w0, [x22, 132]
	cmp	w0, 7
	bls	.L2590
	ldr	x1, .LC779
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
	.p2align 3
.L2623:
	ldr	x1, .LC795
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2624:
	mov	w20, 0
	cbz	w1, .L2548
	.p2align 2
.L2600:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4768]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L2600
	b	.L2575
.L2621:
	ldr	x1, .LC783
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2626:
	ldr	x1, .LC807
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2627:
	ldr	x1, .LC811
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2625:
	ldr	x1, .LC799
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2619:
	ldr	x1, .LC773
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
.L2628:
	ldr	x1, .LC777
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2616
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	3
.LC771:
	.xword	.LC770
	.align	3
.LC773:
	.xword	.LC772
	.align	3
.LC775:
	.xword	.LC774
	.align	3
.LC777:
	.xword	.LC776
	.align	3
.LC779:
	.xword	.LC778
	.align	3
.LC781:
	.xword	.LC780
	.align	3
.LC783:
	.xword	.LC782
	.align	3
.LC785:
	.xword	.LC784
	.align	3
.LC787:
	.xword	.LC786
	.align	3
.LC789:
	.xword	.LC788
	.align	3
.LC791:
	.xword	.LC790
	.align	3
.LC793:
	.xword	.LC792
	.align	3
.LC795:
	.xword	.LC794
	.align	3
.LC797:
	.xword	.LC796
	.align	3
.LC799:
	.xword	.LC798
	.align	3
.LC801:
	.xword	.LC800
	.align	3
.LC803:
	.xword	.LC802
	.align	3
.LC805:
	.xword	.LC804
	.align	3
.LC807:
	.xword	.LC806
	.align	3
.LC809:
	.xword	.LC808
	.align	3
.LC811:
	.xword	.LC810
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x24, x28, 4096
	bl	_mcount
	ldr	x2, [x28, 2400]
	mov	w1, 1
	ldr	x0, [x28, 2360]
	ldr	w20, [x2, 24]
	bl	BsGet
	strb	w0, [x24, 592]
	ldr	w22, [x28, 4716]
	sub	w0, w22, #16
	str	w0, [x29, 120]
	cmp	w0, 5
	bls	.L2886
.L2630:
	ldr	x1, .LC813
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	str	w0, [x28, 4724]
	ldr	w4, [x28, 164]
	tbnz	w0, #31, .L2632
	cmp	w0, w4
	bge	.L2632
	mov	x0, x28
	bl	HEVC_VpsSpsPpsCheck
	cbnz	w0, .L2887
	ldr	x0, [x28, 2384]
	mov	w3, 1888
	ldr	w21, [x28, 4724]
	mov	w2, 12660
	ldr	x1, [x28, 2376]
	smaddl	x21, w21, w3, x0
	ldr	w19, [x21, 32]
	ldrb	w0, [x21, 2]
	smaddl	x19, w19, w2, x1
	cbnz	w0, .L2888
.L2638:
	strb	wzr, [x24, 593]
.L2639:
	ldp	w2, w3, [x19, 140]
	cbz	w2, .L2641
	cbz	w3, .L2641
	ldp	w0, w1, [x19, 64]
	add	w0, w2, w0
	add	w1, w3, w1
	sub	w1, w1, #1
	sub	w0, w0, #1
	udiv	w0, w0, w2
	udiv	w2, w1, w3
	ldr	w1, [x19, 172]
	mov	w3, 1
	lsl	w1, w1, 1
	lsl	w23, w3, w1
	mov	w1, 0
	mul	w2, w0, w2
	cmp	w2, 1
	ble	.L2643
	.p2align 2
.L2644:
	add	w1, w1, 1
	lsl	w0, w3, w1
	cmp	w2, w0
	bgt	.L2644
.L2643:
	ldrb	w0, [x24, 592]
	str	wzr, [x29, 124]
	cbz	w0, .L2889
.L2645:
	ldr	w0, [x28, 192]
	str	w0, [x28, 4700]
	ldrb	w0, [x24, 593]
	cbz	w0, .L2890
.L2648:
	ldr	w0, [x21, 12]
	tst	w0, 16776960
	bne	.L2740
.L2747:
	ldrb	w0, [x21, 23]
	cbnz	w0, .L2891
.L2742:
	ldr	w0, [x29, 124]
	cbnz	w0, .L2892
	ldrb	w0, [x28, 3]
	cbz	w0, .L2756
	ldr	w0, [x29, 120]
	cmp	w0, 5
	bhi	.L2757
	ldr	w0, [x28, 4720]
	mov	w2, 1
	add	x1, x28, x0
	strb	w2, [x1, 5]
.L2758:
	ldr	w1, [x28, 4700]
	cmp	w1, wzr
	ldr	w1, [x29, 120]
	ccmp	w1, 5, 2, ne
	bhi	.L2759
	ldr	w1, [x28, 4716]
	add	x0, x28, x0
	cmp	w1, 21
	beq	.L2893
	.p2align 2
.L2878:
	strb	wzr, [x0, 4]
.L2761:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 4840]
	mov	x0, x28
	bl	HEVC_ReadByteAlignment
	cmp	w0, wzr
	csetm	w0, ne
.L2871:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2888:
	ldrb	w0, [x24, 592]
	cbnz	w0, .L2638
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 593]
	b	.L2639
	.p2align 3
.L2890:
	ldr	w0, [x21, 36]
	mov	w23, 0
	cbz	w0, .L2653
	.p2align 2
.L2836:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	add	w23, w23, w1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w23
	bhi	.L2836
.L2653:
	ldr	x1, .LC824
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	cmp	w0, 2
	str	w0, [x28, 4708]
	bhi	.L2894
	ldrb	w0, [x21, 4]
	cbnz	w0, .L2895
	sub	w22, w22, #19
	cmp	w22, 1
	bls	.L2655
.L2926:
	ldrb	w0, [x28, 1]
	cbz	w0, .L2896
	ldr	w1, [x19, 116]
	mov	w2, 1
	ldr	w0, [x28, 188]
	lsl	w1, w2, w1
	mov	w2, w1
	str	w2, [x29, 112]
	udiv	w1, w0, w1
	msub	w1, w1, w2, w0
	sub	w0, w0, w1
	cbnz	w1, .L2762
	str	wzr, [x29, 116]
.L2658:
	ldr	w1, [x28, 4716]
	add	x20, x28, x20, uxtw 2
	sub	w1, w1, #16
	cmp	w1, 2
	ldr	w1, [x29, 116]
	csel	w0, w0, wzr, hi
	add	w3, w0, w1
	str	w3, [x28, 4700]
	ldr	w2, [x20, 212]
	cmp	w3, w2
	bge	.L2660
	ldrb	w0, [x24, 592]
	cmp	w0, 1
	beq	.L2897
.L2660:
	ldr	w0, [x28, 2332]
	cbnz	w0, .L2661
	ldr	w0, [x28, 4700]
	str	w0, [x28, 192]
.L2661:
	ldr	w0, [x28, 4712]
	cbnz	w0, .L2662
	ldr	w0, [x28, 4716]
	cmp	w0, 15
	bhi	.L2663
	mov	w1, 1
	tbz	x0, 0, .L2663
.L2664:
	sub	w0, w0, #7
	tst	w0, -3
	cset	w0, ne
	tst	w1, w0
	beq	.L2662
	ldr	w0, [x28, 4700]
	str	w0, [x28, 188]
	.p2align 2
.L2662:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2665
	ldr	w3, [x19, 176]
	mov	w1, 0
	mov	w2, 1
	mov	w0, 0
	cmp	w3, 1
	bls	.L2667
	.p2align 2
.L2835:
	add	w1, w1, 1
	lsl	w0, w2, w1
	cmp	w0, w3
	bcc	.L2835
	mov	w0, 0
	cbnz	w1, .L2898
.L2670:
	sxtw	x4, w0
	mov	x2, 164
	lsl	x1, x4, 2
	add	x0, x24, 1524
	sub	x1, x1, x4
	lsl	x3, x1, 3
	sub	x1, x3, x1
	lsl	x1, x1, 1
	sub	x1, x1, x4
	add	x1, x19, x1, lsl 2
	add	x1, x1, 2164
	bl	memcpy
	str	x0, [x29, 104]
.L2668:
	ldrb	w0, [x19, 8]
	cbz	w0, .L2672
	ldr	w0, [x19, 180]
	ldr	w1, [x24, 1528]
	ldr	w20, [x28, 5620]
	add	w20, w20, w1
	cbnz	w0, .L2899
	mov	w25, 0
	str	wzr, [x29, 140]
.L2673:
	ldr	x1, .LC838
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	ldr	w3, [x24, 1528]
	add	x1, x24, 1524
	ldr	w2, [x28, 5620]
	add	w0, w0, w25
	mov	w4, w0
	add	w0, w2, w3
	add	w0, w0, w4
	str	w4, [x29, 136]
	cmp	w0, 16
	bhi	.L2900
	ldr	w2, [x29, 136]
	mov	w23, 0
	mov	w27, 0
	add	w0, w20, w2
	str	w0, [x29, 100]
	sub	w22, w0, #1
	cbz	w2, .L2689
	str	x1, [x29, 128]
	b	.L2834
	.p2align 3
.L2903:
	ldr	w1, [x29, 140]
	cbnz	w1, .L2901
.L2680:
	sxtw	x0, w0
	ldr	x1, [x29, 128]
	add	x4, x19, x0
	add	x1, x1, x26
	add	x0, x19, x0, lsl 2
	ldrb	w4, [x4, 13]
	ldr	w20, [x0, 196]
	strb	w4, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2360]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbnz	w0, .L2902
.L2684:
	str	w20, [x1, 5720]
	csel	w23, w23, wzr, ne
	str	wzr, [x1, 4776]
	ldr	w0, [x28, 4700]
	sub	w20, w20, w0
	str	w20, [x1, 5652]
.L2686:
	ldr	w0, [x29, 136]
	add	w27, w27, 1
	sub	w22, w22, #1
	cmp	w0, w27
	beq	.L2689
.L2834:
	cmp	w27, w25
	uxtw	x26, w22
	mov	w0, 0
	bcc	.L2903
	ldr	w1, [x19, 120]
	uxtw	x26, w22
	ldr	x0, [x28, 2360]
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 128]
	add	x1, x1, x26
	strb	w0, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2360]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbz	w0, .L2684
.L2902:
	ldr	x1, .LC844
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	add	w23, w23, w0
	add	x3, x28, x26, lsl 2
	cmp	w27, wzr
	ccmp	w27, w25, 4, ne
	mov	w1, 1
	str	w1, [x3, 4776]
	cset	w1, eq
	cmp	w1, wzr
	csel	w23, w23, w0, eq
	ldr	w0, [x29, 112]
	ldr	w1, [x28, 4700]
	msub	w20, w23, w0, w20
	ldr	w0, [x29, 116]
	sub	w0, w1, w0
	add	w20, w20, w0
	str	w20, [x3, 5720]
	sub	w20, w20, w1
	str	w20, [x3, 5652]
	b	.L2686
	.p2align 3
.L2892:
	ldr	w0, [x28, 4720]
	add	x1, x28, x0
	ldrb	w1, [x1, 5]
	cbnz	w1, .L2758
.L2759:
	add	x0, x28, x0
	b	.L2878
	.p2align 3
.L2886:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	b	.L2630
	.p2align 3
.L2889:
	ldr	x0, [x28, 2360]
	bl	BsGet
	str	w0, [x28, 4728]
	ldp	w1, w3, [x19, 188]
	mul	w3, w1, w3
	tbnz	w0, #31, .L2647
	cmp	w3, w0
	bls	.L2647
	mul	w0, w23, w0
	str	w0, [x29, 124]
	b	.L2645
	.p2align 3
.L2740:
	ldr	x1, .LC896
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	mov	w20, w0
	ldr	w0, [x21, 12]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L2904
	cmp	w0, 256
	ldr	w0, [x21, 68]
	beq	.L2905
	ldr	w1, [x19, 192]
	mul	w0, w0, w1
	sub	w0, w0, #1
.L2744:
	cmp	w0, 255
	mov	w1, 255
	csel	w3, w0, w1, ls
	cmp	w20, w3
	bhi	.L2906
	cbz	w20, .L2747
	ldr	x1, .LC900
	mov	w19, 0
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	cmp	w0, 31
	add	w22, w0, 1
	bhi	.L2907
	.p2align 2
.L2833:
	ldr	x0, [x28, 2360]
	mov	w1, w22
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L2833
	ldrb	w0, [x21, 23]
	cbz	w0, .L2742
.L2891:
	ldr	x1, .LC904
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	cmp	w0, 256
	mov	w20, w0
	bhi	.L2908
	ldr	x0, [x28, 2360]
	bl	BsResidBits
	cmp	w20, w0
	bhi	.L2753
	mov	w19, 0
	cbz	w20, .L2742
	.p2align 2
.L2832:
	ldr	x0, [x28, 2360]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L2832
	b	.L2742
	.p2align 3
.L2756:
	ldr	w0, [x29, 120]
	cmp	w0, 5
	bhi	.L2757
	ldr	w0, [x28, 4720]
	add	x1, x28, x0
	add	x0, x28, x0
	strb	wzr, [x1, 5]
	b	.L2878
	.p2align 3
.L2762:
	ldr	w2, [x29, 112]
	str	wzr, [x29, 116]
	cmp	w1, w2, lsr 1
	bcc	.L2658
.L2770:
	ldr	w1, [x29, 112]
	add	w0, w0, w1
	b	.L2658
.L2904:
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	b	.L2744
	.p2align 3
.L2663:
	sub	w1, w0, #16
	cmp	w1, 7
	cset	w1, ls
	b	.L2664
	.p2align 3
.L2901:
	ldr	x0, [x28, 2360]
	bl	BsGet
	ldr	w4, [x19, 180]
	sub	w4, w4, #1
	tbnz	w0, #31, .L2682
	cmp	w4, w0
	bcs	.L2680
.L2682:
	ldr	x1, .LC842
	mov	w3, w0
	mov	w2, w27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2689:
	ldr	w0, [x29, 100]
	str	w0, [x24, 1532]
	cmp	w0, 16
	bhi	.L2909
.L2672:
	ldrb	w0, [x19, 9]
	cbnz	w0, .L2910
	strb	wzr, [x24, 596]
.L2691:
	ldrb	w0, [x19, 6]
	cbnz	w0, .L2911
.L2766:
	ldr	w0, [x28, 4708]
	cmp	w0, 2
	bne	.L2912
.L2694:
	ldrb	w0, [x24, 596]
	cbnz	w0, .L2913
.L2716:
	mov	w4, 2
.L2723:
	ldrb	w0, [x21, 11]
	cbz	w0, .L2714
	cbnz	w4, .L2714
.L2726:
	mov	x0, x28
	bl	HEVC_DecPredWeightTable
	cbnz	w0, .L2914
	ldr	w4, [x28, 4708]
.L2714:
	cmp	w4, 2
	beq	.L2727
	ldr	x1, .LC868
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	mov	w3, 4
	mov	w1, 5
	sub	w3, w3, w0
	sub	w2, w1, w0
	cmp	w3, 4
	str	w2, [x28, 4736]
	bhi	.L2915
.L2727:
	ldr	x1, .LC872
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	ldr	w2, [x21, 48]
	mov	w1, 51
	add	w0, w0, w2
	str	w0, [x28, 4704]
	ldr	w3, [x19, 92]
	neg	w2, w3
	cmp	w0, w2
	ccmp	w0, w1, 0, ge
	bgt	.L2916
	ldrb	w0, [x21, 9]
	cbnz	w0, .L2917
.L2729:
	ldrb	w0, [x21, 18]
	cbz	w0, .L2877
	ldrb	w0, [x21, 19]
	cbnz	w0, .L2918
.L2735:
	ldrb	w0, [x21, 20]
	strb	w0, [x24, 601]
	ldr	w1, [x21, 76]
	str	w1, [x28, 4748]
	ldr	w1, [x21, 80]
	str	w1, [x28, 4752]
.L2734:
	ldrb	w2, [x19, 6]
	mov	w1, 0
	cbz	w2, .L2738
	ldrh	w1, [x28, 4690]
	cmp	w1, wzr
	cset	w1, ne
.L2738:
	ldrb	w2, [x21, 17]
	cbz	w2, .L2739
	cmp	w0, wzr
	cset	w0, eq
	orr	w1, w0, w1
	cbnz	w1, .L2919
.L2739:
	strb	w2, [x24, 602]
	b	.L2648
	.p2align 3
.L2912:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 597]
	cbnz	w0, .L2920
	ldr	w0, [x21, 40]
	ldr	w4, [x28, 4708]
	str	w0, [x28, 4764]
	cbnz	w4, .L2702
	ldr	w0, [x21, 44]
	mov	w20, 0
	mov	w22, 0
	str	w0, [x28, 4768]
.L2700:
	ldr	x0, [x29, 104]
	cbz	x0, .L2921
	ldr	x0, [x29, 104]
	ldr	w2, [x0, 8]
	cmp	w2, 16
	bhi	.L2704
	cbz	w2, .L2706
	ldr	x0, [x29, 104]
	sub	w2, w2, #1
	add	x2, x2, 13
	mov	w3, 0
	add	x2, x0, x2
	add	x0, x0, 12
	.p2align 2
.L2708:
	ldrb	w1, [x0], 1
	cmp	w1, wzr
	csinc	w3, w3, w3, eq
	cmp	x2, x0
	bne	.L2708
	ldrb	w0, [x21, 22]
	cmp	w0, wzr
	ccmp	w3, 1, 4, ne
	ble	.L2706
	add	x2, x24, 1688
	add	x1, x24, 592
	mov	x0, x28
	bl	HEVC_DecRefPicListsModification
	cbnz	w0, .L2873
	ldr	w4, [x28, 4708]
	cbnz	w4, .L2709
.L2767:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 598]
	ldr	w4, [x28, 4708]
.L2709:
	cmp	w4, 2
	beq	.L2694
.L2768:
	ldrb	w0, [x21, 5]
	cbnz	w0, .L2922
.L2710:
	ldrb	w0, [x24, 596]
	cbz	w0, .L2719
	cbz	w4, .L2923
	mov	w0, 1
	cmp	w4, 2
	strb	w0, [x24, 600]
	beq	.L2716
.L2715:
	ldr	w0, [x28, 4764]
	cmp	w0, 1
	bls	.L2876
.L2718:
	ldr	x1, .LC862
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	str	w0, [x28, 4732]
	ldrb	w2, [x24, 600]
	cbnz	w2, .L2924
	sub	w4, w20, #1
.L2721:
	cmp	w4, w0
	ccmp	w0, wzr, 1, cs
	bge	.L2876
	ldr	x1, .LC864
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2876:
	ldr	w4, [x28, 4708]
.L2719:
	ldrb	w0, [x21, 10]
	cbz	w0, .L2723
	cmp	w4, 1
	bne	.L2723
	b	.L2726
	.p2align 3
.L2757:
	ldr	w0, [x28, 4720]
	add	x0, x28, x0
	b	.L2878
.L2918:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2735
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 601]
	cbnz	w0, .L2734
	ldr	x1, .LC888
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 4748]
	bhi	.L2925
.L2736:
	ldr	x1, .LC892
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 4752]
	bls	.L2877
	ldr	x1, .LC894
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 80]
	str	w0, [x28, 4752]
	.p2align 2
.L2877:
	ldrb	w0, [x24, 601]
	b	.L2734
	.p2align 3
.L2706:
	cbnz	w4, .L2768
	b	.L2767
	.p2align 3
.L2895:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	sub	w22, w22, #19
	bl	BsGet
	cmp	w22, 1
	bhi	.L2926
.L2655:
	ldr	w0, [x28, 2332]
	str	wzr, [x28, 4700]
	cbnz	w0, .L2692
	str	wzr, [x28, 192]
.L2692:
	ldr	w0, [x28, 4712]
	cbnz	w0, .L2693
	str	wzr, [x28, 188]
.L2693:
	ldrb	w0, [x19, 6]
	cbz	w0, .L2764
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 594]
	mov	w1, 1
	ldr	x0, [x28, 2360]
	bl	BsGet
	strb	w0, [x24, 595]
.L2764:
	strb	wzr, [x24, 596]
	str	xzr, [x29, 104]
	b	.L2766
	.p2align 3
.L2632:
	ldr	x2, .LC814
	mov	w3, w0
	ldr	x1, .LC816
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2917:
	ldr	x1, .LC876
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 4740]
	bhi	.L2927
	ldr	w3, [x21, 60]
	add	w1, w0, w3
	add	w1, w1, 12
	cmp	w1, 24
	bhi	.L2928
	ldr	x1, .LC882
	ldr	x0, [x28, 2360]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 4744]
	bhi	.L2929
	ldr	w1, [x21, 64]
	add	w2, w0, w1
	add	w0, w2, 12
	cmp	w0, 24
	bls	.L2729
	ldr	x1, .LC886
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2896:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2360]
	bl	BsGet
	mov	w4, w0
	ldr	w0, [x19, 116]
	mov	w1, 1
	lsl	w1, w1, w0
	ldr	w0, [x28, 188]
	mov	w3, w1
	stp	w3, w4, [x29, 112]
	udiv	w1, w0, w1
	msub	w1, w1, w3, w0
	cmp	w4, w1
	sub	w0, w0, w1
	bcc	.L2930
.L2657:
	ldr	w2, [x29, 116]
	cmp	w2, w1
	bls	.L2658
	sub	w1, w2, w1
	ldr	w2, [x29, 112]
	cmp	w1, w2, lsr 1
	sub	w1, w0, w2
	csel	w0, w1, w0, hi
	b	.L2658
	.p2align 3
.L2665:
	ldr	w3, [x19, 176]
	add	x2, x24, 1524
	mov	x1, x19
	mov	x0, x28
	str	x2, [x29, 104]
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L2668
	ldr	x1, .LC830
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2898:
	ldr	x0, [x28, 2360]
	bl	BsGet
	ldr	w3, [x19, 176]
	tbnz	w0, #31, .L2931
.L2667:
	sub	w3, w3, #1
	cmp	w3, w0
	bcs	.L2670
.L2671:
	ldr	x1, .LC832
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2922:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 599]
	ldr	w4, [x28, 4708]
	b	.L2710
.L2910:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 596]
	b	.L2691
.L2702:
	mov	w22, 0
	str	wzr, [x28, 4768]
.L2701:
	cmp	w4, 2
	beq	.L2694
	mov	w20, 0
	b	.L2700
.L2920:
	ldr	x1, .LC848
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	add	w22, w0, 1
	cmp	w22, 16
	bhi	.L2932
	ldr	w4, [x28, 4708]
	str	w22, [x28, 4764]
	cbz	w4, .L2933
	str	wzr, [x28, 4768]
	b	.L2701
.L2913:
	mov	w0, 1
	mov	w4, 2
	strb	w0, [x24, 600]
	b	.L2719
.L2919:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 602]
	b	.L2648
.L2930:
	sub	w2, w1, w4
	cmp	w2, w3, lsr 1
	bcc	.L2657
	b	.L2770
	.p2align 3
.L2924:
	sub	w4, w22, #1
	b	.L2721
.L2893:
	mov	w1, 1
	strb	w1, [x0, 4]
	b	.L2761
.L2933:
	ldr	x1, .LC852
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	add	w20, w0, 1
	cmp	w20, 16
	bhi	.L2934
	ldr	w4, [x28, 4708]
	str	w20, [x28, 4768]
	cmp	w4, 2
	bne	.L2700
	b	.L2694
	.p2align 3
.L2908:
	ldr	x1, .LC906
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2909:
	ldr	x1, .LC846
	mov	w3, 16
	ldr	w2, [x29, 100]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2931:
	sub	w3, w3, #1
	b	.L2671
	.p2align 3
.L2923:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 600]
	ldr	w4, [x28, 4708]
	cmp	w4, 2
	beq	.L2727
	cbnz	w0, .L2715
	ldr	w0, [x28, 4768]
	cmp	w0, 1
	bhi	.L2718
	b	.L2719
.L2641:
	ldr	x1, .LC820
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2905:
	ldr	w1, [x21, 72]
	mul	w0, w0, w1
	sub	w0, w0, #1
	b	.L2744
.L2899:
	ldr	x1, .LC834
	ldr	x0, [x28, 2360]
	bl	HEVC_ue_v
	mov	w25, w0
	ldr	w3, [x19, 180]
	cmp	w0, w3
	bhi	.L2935
	cmp	w3, 1
	str	wzr, [x29, 140]
	bls	.L2673
	mov	w1, 1
	.p2align 2
.L2675:
	ldr	w0, [x29, 140]
	add	w0, w0, 1
	str	w0, [x29, 140]
	lsl	w0, w1, w0
	cmp	w3, w0
	bhi	.L2675
	b	.L2673
.L2887:
	ldr	w0, [x28, 236]
	cbz	w0, .L2636
	ldr	w0, [x28, 192]
	str	w0, [x28, 4700]
.L2637:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 4840]
	ldr	x1, .LC818
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2897:
	ldr	x1, .LC828
	bl	dprint_vfmw
	b	.L2660
.L2636:
	str	wzr, [x28, 4700]
	b	.L2637
.L2916:
	ldr	x1, .LC874
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2647:
	ldr	x1, .LC822
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2894:
	ldr	x1, .LC826
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2704:
	ldr	x1, .LC858
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2753:
	ldr	x1, .LC908
	mov	w2, w0
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2906:
	ldr	x1, .LC898
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2928:
	ldr	x1, .LC880
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2915:
	ldr	x1, .LC870
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2925:
	ldr	x1, .LC890
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 76]
	str	w0, [x28, 4748]
	b	.L2736
.L2900:
	ldr	x1, .LC840
	mov	w5, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2927:
	ldr	x1, .LC878
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2914:
	ldr	x1, .LC866
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2929:
	ldr	x1, .LC884
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2935:
	ldr	x1, .LC836
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2873:
	ldr	x1, .LC860
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2907:
	ldr	x1, .LC902
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2921:
	ldr	x1, .LC856
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2932:
	ldr	x1, .LC850
	mov	w3, 16
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2934:
	ldr	x1, .LC854
	mov	w3, 16
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2871
.L2911:
	ldr	x0, [x28, 2360]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 594]
	mov	w1, 1
	ldr	x0, [x28, 2360]
	bl	BsGet
	strb	w0, [x24, 595]
	b	.L2766
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	3
.LC813:
	.xword	.LC812
	.align	3
.LC814:
	.xword	.LANCHOR5
	.align	3
.LC816:
	.xword	.LC815
	.align	3
.LC818:
	.xword	.LC817
	.align	3
.LC820:
	.xword	.LC819
	.align	3
.LC822:
	.xword	.LC821
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC826:
	.xword	.LC825
	.align	3
.LC828:
	.xword	.LC827
	.align	3
.LC830:
	.xword	.LC829
	.align	3
.LC832:
	.xword	.LC831
	.align	3
.LC834:
	.xword	.LC833
	.align	3
.LC836:
	.xword	.LC835
	.align	3
.LC838:
	.xword	.LC837
	.align	3
.LC840:
	.xword	.LC839
	.align	3
.LC842:
	.xword	.LC841
	.align	3
.LC844:
	.xword	.LC843
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC848:
	.xword	.LC847
	.align	3
.LC850:
	.xword	.LC849
	.align	3
.LC852:
	.xword	.LC851
	.align	3
.LC854:
	.xword	.LC853
	.align	3
.LC856:
	.xword	.LC855
	.align	3
.LC858:
	.xword	.LC857
	.align	3
.LC860:
	.xword	.LC859
	.align	3
.LC862:
	.xword	.LC861
	.align	3
.LC864:
	.xword	.LC863
	.align	3
.LC866:
	.xword	.LC865
	.align	3
.LC868:
	.xword	.LC867
	.align	3
.LC870:
	.xword	.LC869
	.align	3
.LC872:
	.xword	.LC871
	.align	3
.LC874:
	.xword	.LC873
	.align	3
.LC876:
	.xword	.LC875
	.align	3
.LC878:
	.xword	.LC877
	.align	3
.LC880:
	.xword	.LC879
	.align	3
.LC882:
	.xword	.LC881
	.align	3
.LC884:
	.xword	.LC883
	.align	3
.LC886:
	.xword	.LC885
	.align	3
.LC888:
	.xword	.LC887
	.align	3
.LC890:
	.xword	.LC889
	.align	3
.LC892:
	.xword	.LC891
	.align	3
.LC894:
	.xword	.LC893
	.align	3
.LC896:
	.xword	.LC895
	.align	3
.LC898:
	.xword	.LC897
	.align	3
.LC900:
	.xword	.LC899
	.align	3
.LC902:
	.xword	.LC901
	.align	3
.LC904:
	.xword	.LC903
	.align	3
.LC906:
	.xword	.LC905
	.align	3
.LC908:
	.xword	.LC907
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 2400]
	cbz	x1, .L2938
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L2938:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrSlice
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 168]
	cbz	w2, .L2947
	.p2align 2
.L2950:
	ldr	x0, [x20, 2440]
	ldr	x0, [x0, w19, uxtw 3]
	mov	x1, x0
	cbz	x0, .L2945
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2440]
	str	xzr, [x0, w19, uxtw 3]
	ldr	w2, [x20, 168]
.L2945:
	add	w19, w19, 1
	cmp	w2, w19
	bhi	.L2950
.L2947:
	strb	wzr, [x20, 11]
	mov	w0, 2
	str	wzr, [x20, 204]
	str	w0, [x20, 176]
	mov	w0, 0
	str	wzr, [x20, 236]
	str	wzr, [x20, 244]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	add	x19, x20, 2816
	bl	_mcount
	add	x21, x20, 2952
	mov	x0, x20
	bl	HEVC_ClearAllSlice
	.p2align 2
.L2959:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L2955
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2955:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L2956
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2956:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L2957
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2957:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L2958
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2958:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L2959
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 2792]
	cmp	w0, 17
	bhi	.L2998
.L2960:
	ldr	x1, .LC911
	add	x4, x20, 2560
	add	x0, x20, 12288
	mov	x2, 200
	add	x0, x0, 984
	ldr	x3, [x1, 96]
	mov	w1, 0
	stp	wzr, wzr, [x4, 236]
	stp	wzr, wzr, [x4, 244]
	str	wzr, [x20, 2812]
	blr	x3
	str	wzr, [x20, 13276]
	mov	w0, 16
	add	x1, x20, 2480
	str	w0, [x20, 13272]
	add	x0, x20, 2616
	.p2align 2
.L2961:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L2961
	add	x1, x20, 2752
	str	wzr, [x20, 4756]
	.p2align 2
.L2962:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L2962
	str	wzr, [x20, 4760]
	cbnz	w22, .L2963
	ldr	x0, [x20, 2456]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	beq	.L2963
.L2964:
	ldr	w0, [x20, 184]
	cbz	w0, .L2973
	sub	w1, w0, #1
	add	x0, x20, 2132
	add	x1, x1, 534
	add	x1, x20, x1, lsl 2
	.p2align 2
.L2972:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L2972
.L2973:
	ldr	w2, [x20, 168]
	mov	w19, 0
	cbz	w2, .L2971
	.p2align 2
.L2987:
	ldr	x0, [x20, 2440]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L2974
	ldr	x3, [x20, 2400]
	cmp	x0, x3
	beq	.L2974
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2440]
	str	xzr, [x0, x21, lsl 3]
	ldr	w2, [x20, 168]
.L2974:
	cmp	w2, w19
	bhi	.L2987
.L2971:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2963:
	mov	w19, 20
	mov	x0, x20
	stp	w19, w19, [x20, 180]
	bl	HEVC_ArrangeMem
	cbz	w0, .L2965
	cmp	w0, 2
	beq	.L2999
	ldr	x2, .LC909
	mov	w0, 0
	ldr	x1, .LC913
	add	x2, x2, 104
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2998:
	ldr	x2, .LC909
	mov	w4, 17
	ldr	x1, .LC910
	mov	w3, w4
	add	x2, x2, 104
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 2792]
	b	.L2960
.L2965:
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	cmp	w0, 20
	mov	w0, w19
	ble	.L3000
	str	w0, [x20, 180]
	b	.L2964
.L2999:
	add	x0, x20, 4096
	add	x0, x0, 1952
	bl	ResetVoQueue
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L3000:
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	str	w0, [x20, 180]
	b	.L2964
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	3
.LC909:
	.xword	.LANCHOR5
	.align	3
.LC910:
	.xword	.LC351
	.align	3
.LC911:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC913:
	.xword	.LC912
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	mov	w21, 104
	bl	_mcount
	ldr	w2, [x20, 168]
	cmn	w2, #1
	bne	.L3006
	b	.L3005
	.p2align 3
.L3003:
	add	w0, w2, 1
	cmp	w0, w19
	bls	.L3005
.L3006:
	umull	x1, w19, w21
	ldr	x0, [x20, 2448]
	add	w19, w19, 1
	add	x1, x0, x1
	ldr	w0, [x1, 32]
	cmp	w0, 1
	bne	.L3003
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	w2, [x20, 168]
	add	w0, w2, 1
	cmp	w0, w19
	bhi	.L3006
.L3005:
	strb	wzr, [x20, 7]
	mov	w0, 0
	str	wzr, [x20, 148]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x23, x20, 4096
	add	x25, x20, 12288
	bl	_mcount
	add	x19, x25, 1184
	ldr	x1, .LC915
	mov	w0, 22
	mov	w21, 0
	mov	w26, 20
	mov	w24, 16
	bl	dprint_vfmw
	strb	wzr, [x20, 4]
	mov	w0, -2147483647
	mov	w2, 1
	mov	w1, 2147483647
	strb	w2, [x20, 5]
	stp	w1, w0, [x20, 228]
	str	w0, [x20, 212]
	mov	x0, x20
	strb	wzr, [x20, 10]
	bl	HEVC_ClearAllNal
	add	x0, x23, 1952
	bl	ResetVoQueue
	ldr	x22, .LC916
	.p2align 2
.L3010:
	strb	wzr, [x19]
	add	x0, x19, 80
	strb	wzr, [x19, 1]
	mov	x2, 632
	strb	wzr, [x19, 2]
	mov	w1, 0
	str	wzr, [x19, 8]
	stp	w26, w24, [x19, 20]
	str	wzr, [x19, 48]
	ldr	x3, [x22, 96]
	blr	x3
	str	w21, [x19, 228]
	add	w21, w21, 1
	str	wzr, [x19, 56]
	str	x19, [x19, 72]
	cmp	w21, 20
	add	x19, x19, 712
	bne	.L3010
	add	x0, x20, 2132
	add	x1, x20, 2212
	.p2align 2
.L3011:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L3011
	ldr	w1, [x20, 168]
	mov	w0, 0
	cbz	w1, .L3015
	.p2align 2
.L3017:
	ldr	x1, [x20, 2440]
	str	xzr, [x1, w0, uxtw 3]
	add	w0, w0, 1
	ldr	w1, [x20, 168]
	cmp	w1, w0
	bhi	.L3017
.L3015:
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 200
	add	x0, x25, 984
	blr	x3
	mov	w1, 16
	add	x0, x20, 2952
	str	w1, [x20, 13272]
	add	x1, x20, 3088
.L3013:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x1, x0
	bne	.L3013
	add	x2, x20, 2560
	mov	w0, 17
	add	x19, x20, 2616
	stp	w0, wzr, [x2, 232]
	stp	wzr, wzr, [x2, 240]
	str	wzr, [x20, 2808]
	add	x0, x20, 2752
	str	wzr, [x20, 2812]
	.p2align 2
.L3016:
	str	xzr, [x19, -136]
	add	x19, x19, 8
	str	xzr, [x19, -8]
	cmp	x19, x0
	bne	.L3016
	ldr	x3, [x22, 96]
	mov	w21, 2
	mov	x2, 1356
	str	w21, [x20, 176]
	mov	w1, 0
	add	x0, x23, 592
	str	wzr, [x20, 204]
	str	wzr, [x20, 236]
	str	wzr, [x20, 244]
	str	xzr, [x20, 2400]
	blr	x3
	strb	wzr, [x20, 6]
	mov	w1, 8
	mov	w3, 1
	stp	w1, w1, [x20, 196]
	add	x1, x20, 2048
	strb	w3, [x20, 3]
	str	wzr, [x20, 172]
	mov	w2, 20
	stp	w2, w2, [x20, 180]
	ldr	x4, [x22, 96]
	mov	w0, 6
	mov	w2, 16
	stp	w0, w21, [x1, 172]
	stp	w0, w0, [x1, 164]
	mov	w1, 64
	str	w2, [x20, 324]
	str	w1, [x20, 328]
	mov	w2, 256
	mov	w1, 1025
	str	w21, [x20, 4708]
	str	w3, [x20, 4840]
	mov	x0, x19
	str	w2, [x20, 332]
	mov	x2, 40
	str	w1, [x20, 336]
	mov	w1, 0
	blr	x4
	str	x19, [x20, 2360]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	3
.LC915:
	.xword	.LC914
	.align	3
.LC916:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	ldr	x0, [x19, 4048]
	cbz	x0, .L3024
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x19, 252]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 4048]
	str	wzr, [x0, 48]
	str	xzr, [x19, 4048]
.L3024:
	strb	wzr, [x19, 3985]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	cbnz	w20, .L3031
	add	x0, x19, 4096
	add	x0, x0, 1952
	bl	ResetVoQueue
	ldr	w0, [x19, 252]
	bl	FSP_EmptyInstance
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3031:
	add	x1, x19, 4096
	ldr	w0, [x19, 252]
	add	x1, x1, 1952
	bl	FSP_ClearNotInVoQueue
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 4724]
	tbnz	w3, #31, .L3048
	ldr	w1, [x19, 164]
	mov	w0, 0
	cmp	w3, w1
	bge	.L3061
	add	x1, x19, 256
	mov	w26, 1888
	mov	w0, 12660
	ldr	w2, [x19, 4720]
	ldr	x5, [x19, 2376]
	mov	w21, 1
	ldp	w25, w22, [x1, 8]
	ldp	w24, w23, [x1, 16]
	ldr	x1, [x19, 2384]
	add	x2, x19, x2, lsl 2
	ldr	x6, [x19, 2368]
	smaddl	x26, w3, w26, x1
	ldr	w4, [x26, 32]
	smull	x4, w4, w0
	add	x20, x5, x4
	ldr	w0, [x20, 48]
	str	w3, [x2, 224]
	ldr	w1, [x26, 32]
	str	w1, [x2, 220]
	lsl	x1, x0, 7
	add	x0, x1, x0, lsl 2
	add	x1, x6, x0
	ldr	w0, [x20, 48]
	str	w0, [x2, 216]
	ldr	w0, [x19, 172]
	ldr	w2, [x20, 128]
	cmp	w0, wzr
	ldr	w0, [x20, 64]
	cset	w27, eq
	cmp	w2, w23
	cset	w28, ne
	cmp	w22, w0
	beq	.L3067
.L3034:
	ldr	x0, [x19, 2416]
	orr	w28, w27, w28
	ldr	w2, [x1, 4]
	orr	w28, w28, w21
	ldr	w0, [x0, 4]
	cmp	w2, w0
	beq	.L3068
.L3035:
	ldr	x0, .LC917
	mov	w6, 132
	strb	wzr, [x1, 2]
	mov	x3, -132
	stp	x5, x4, [x29, 96]
	ldr	x7, [x0, 104]
	ldr	w0, [x19, 156]
	ldr	x2, [x19, 2368]
	str	x3, [x29, 112]
	smaddl	x0, w0, w6, x3
	str	w6, [x29, 124]
	add	x0, x2, x0
	mov	x2, 132
	blr	x7
	ldr	w0, [x19, 156]
	ldr	w6, [x29, 124]
	ldr	x3, [x29, 112]
	ldr	x1, [x19, 2368]
	ldp	x5, x4, [x29, 96]
	smaddl	x0, w0, w6, x3
	add	x0, x1, x0
	str	x0, [x19, 2416]
.L3036:
	ldr	x0, [x19, 2424]
	mov	w3, w28
	ldr	w1, [x20, 56]
	ldr	w2, [x0, 56]
	cmp	w2, w1
	beq	.L3069
.L3047:
	ldr	w0, [x0, 184]
	ldr	w1, [x20, 184]
	str	w3, [x29, 124]
	cmp	w1, w0
	mov	x1, x20
	mov	x0, x19
	cset	w28, ne
	bl	HEVC_UpdatePicSPS
	ldr	w3, [x29, 124]
.L3038:
	ldr	x0, [x19, 2432]
	ldr	w1, [x0, 28]
	ldr	w0, [x26, 28]
	cmp	w1, w0
	beq	.L3070
.L3039:
	mov	x2, x26
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_UpdatePicPPS
.L3040:
	ldr	x0, [x19, 2424]
	ldr	x2, [x19, 2456]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	str	w0, [x2, 940]
	ldr	w0, [x19, 2332]
	cbnz	w0, .L3041
	ldr	w0, [x20, 56]
	cmp	w0, w25
	beq	.L3071
.L3042:
	mov	w4, w28
	mov	w3, w23
	mov	w2, w24
	mov	w1, w22
	mov	x0, x19
	bl	HEVC_GetReRangeFlag
	cbnz	w0, .L3043
	ldr	x0, [x19, 2456]
	ldr	w1, [x0, 928]
	cmp	w1, 1
	beq	.L3043
.L3045:
	str	wzr, [x0, 944]
.L3044:
	mov	x0, x19
	bl	HEVC_AllocFrameStore
	mov	w20, w0
	cbz	w0, .L3041
	ldr	x1, .LC921
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
.L3061:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3041:
	mov	x0, x19
	bl	HEVC_InitPicInfo
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3071:
	orr	w21, w27, w21
	orr	w21, w21, w28
	cbnz	w21, .L3042
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	bne	.L3044
	.p2align 2
.L3043:
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_InitDPB
	cmn	w0, #2
	beq	.L3061
	cbnz	w0, .L3046
	ldr	x0, [x19, 2456]
	b	.L3045
	.p2align 3
.L3048:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3070:
	ldrb	w0, [x26, 1]
	cmp	w0, wzr
	cset	w0, ne
	orr	w3, w3, w0
	cbz	w3, .L3040
	b	.L3039
	.p2align 3
.L3069:
	ldrb	w1, [x5, x4]
	cmp	w1, wzr
	cset	w1, ne
	orr	w1, w28, w1
	mov	w28, 0
	cbz	w1, .L3038
	b	.L3047
	.p2align 3
.L3068:
	ldrb	w0, [x1, 2]
	cmp	w0, wzr
	cset	w0, ne
	orr	w0, w27, w0
	cbz	w0, .L3036
	b	.L3035
	.p2align 3
.L3067:
	ldr	w0, [x20, 68]
	cmp	w0, w24
	cset	w21, ne
	b	.L3034
.L3046:
	ldr	x1, .LC919
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L3061
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	3
.LC917:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC919:
	.xword	.LC918
	.align	3
.LC921:
	.xword	.LC920
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, [x19, 4048]
	mov	x2, 632
	ldr	w3, [x19, 4024]
	add	x1, x19, 4056
	add	x0, x20, 80
	str	w3, [x20, 16]
	bl	memcpy
	mov	x0, x19
	mov	x1, x20
	bl	HEVC_GetImagePara
	ldrb	w0, [x19, 3984]
	cbnz	w0, .L3080
.L3073:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	mov	w1, 0
	cbnz	w0, .L3081
.L3074:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3080:
	ldr	w0, [x19, 252]
	mov	w2, 1
	ldr	w1, [x20, 28]
	bl	FSP_SetRef
	b	.L3073
	.p2align 3
.L3081:
	ldr	x2, .LC922
	mov	w0, 0
	ldr	x1, .LC924
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w1, -1
	b	.L3074
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	3
.LC922:
	.xword	.LANCHOR5
	.align	3
.LC924:
	.xword	.LC923
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	mov	w20, w0
	cbnz	w0, .L3085
	ldr	x0, [x19, 4048]
	mov	w2, 2
	mov	w1, 1
	str	w2, [x0, 52]
	str	w1, [x19, 11912]
	ldr	w0, [x19, 3992]
	ldr	w2, [x19, 3996]
	add	x0, x19, x0, lsl 2
	str	w2, [x0, 212]
	ldr	x0, [x19, 4048]
	strb	w1, [x0, 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3085:
	ldr	x2, .LC925
	mov	w0, 1
	ldr	x1, .LC927
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	3
.LC925:
	.xword	.LANCHOR5
	.align	3
.LC927:
	.xword	.LC926
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L3094
	cmn	w0, #3
	bne	.L3095
.L3090:
	mov	w0, 0
.L3089:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3094:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	cbz	w0, .L3090
	ldr	x2, .LC928
	mov	w0, 0
	ldr	x1, .LC929
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L3089
	.p2align 3
.L3095:
	ldr	x1, .LC931
	mov	w3, w0
	mov	w2, 11772
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 228]
	mov	x0, x19
	bl	HEVC_DECRecycleImage
	mov	w0, -1
	b	.L3089
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	3
.LC928:
	.xword	.LANCHOR5
	.align	3
.LC929:
	.xword	.LC923
	.align	3
.LC931:
	.xword	.LC930
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x20, 4048]
	mov	w4, 2
	mov	w3, 1
	add	x1, x20, 4056
	mov	x2, 632
	add	x0, x19, 80
	str	w4, [x19, 48]
	strb	wzr, [x19, 1]
	strb	w3, [x19, 2]
	ldr	w3, [x20, 4000]
	str	w3, [x19, 12]
	ldr	w3, [x20, 4024]
	str	w3, [x19, 16]
	bl	memcpy
	str	wzr, [x19, 56]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_OutputFrmToVO
	str	wzr, [x19, 48]
	ldr	x3, .LC932
	mov	w21, w0
	mov	x2, 704
	mov	w1, 0
	add	x0, x20, 3984
	ldr	x3, [x3, 96]
	blr	x3
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	3
.LC932:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_DirectOutput
	ldr	w2, [x19, 184]
	ldr	w1, [x19, 4020]
	cmp	w1, w2
	beq	.L3098
	add	x1, x19, x1, uxtw 2
	str	wzr, [x1, 2132]
	str	w2, [x19, 4020]
.L3098:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w5, [x20, 2796]
	ldr	w27, [x20, 3992]
	cbz	w5, .L3100
	sub	w3, w5, #1
	uxtw	x4, w27
	add	x3, x3, 353
	add	x4, x4, 52
	add	x0, x20, 2816
	mov	w22, 0
	add	x3, x20, x3, lsl 3
	lsl	x4, x4, 2
	b	.L3102
	.p2align 3
.L3101:
	cmp	x0, x3
	beq	.L3127
.L3102:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cbnz	w2, .L3101
	ldr	w2, [x1, 32]
	cmp	w27, w2
	bne	.L3101
	add	x2, x20, x4
	ldr	w6, [x1, 8]
	ldr	w1, [x2, 4]
	cmp	w6, w1
	csinc	w22, w22, w22, le
	cmp	x0, x3
	bne	.L3102
	.p2align 2
.L3127:
	ldr	w0, [x20, 2340]
	cmp	w0, 1
	beq	.L3114
.L3103:
	ldr	w0, [x20, 4712]
	ldr	x1, [x20, 2424]
	add	x0, x1, x0, lsl 2
	ldr	w25, [x0, 360]
.L3105:
	cbz	w5, .L3115
	uxtw	x24, w27
	ldr	x21, .LC933
	add	x28, x24, 52
	ldr	x23, .LC935
	mov	w19, 0
	add	x21, x21, 192
	lsl	x28, x28, 2
	str	wzr, [x29, 108]
	.p2align 2
.L3113:
	add	x26, x20, x19, uxtw 3
	ldr	x0, [x26, 2816]
	ldrb	w1, [x0, 2]
	cbnz	w1, .L3107
	ldr	w2, [x0, 32]
	cmp	w27, w2
	beq	.L3128
.L3107:
	add	x2, x20, x28
	ldr	w3, [x2, 4]
.L3109:
	cbnz	w3, .L3111
	ldr	w4, [x0, 8]
	tbz	w4, #31, .L3111
	cbz	w1, .L3129
.L3112:
	mov	x2, x21
	mov	x1, x23
	mov	w0, 31
	bl	dprint_vfmw
	ldr	w5, [x20, 2796]
.L3111:
	add	w19, w19, 1
	cmp	w5, w19
	bhi	.L3113
.L3126:
	ldr	w0, [x29, 108]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3128:
	add	x7, x20, x24, lsl 2
	ldr	w2, [x0, 8]
	ldr	w3, [x7, 212]
	cmp	w2, w3
	ble	.L3109
	ldr	w8, [x20, 4712]
	add	x4, x20, 4096
	add	x4, x4, 592
	cmp	w8, 7
	ccmp	w25, w22, 2, ls
	bcs	.L3109
	ldr	w4, [x4, 12]
	cmp	w2, w4
	blt	.L3110
	add	x2, x20, x24
	ldrb	w2, [x2, 4]
	cbz	w2, .L3109
.L3110:
	mov	w1, 1
	strb	w1, [x0, 2]
	mov	x0, x20
	str	x7, [x29, 96]
	ldr	x1, [x26, 2816]
	sub	w22, w22, #1
	bl	HEVC_OutputFrmToVO
	str	w0, [x29, 108]
	ldr	x0, [x26, 2816]
	ldr	x7, [x29, 96]
	ldr	w0, [x0, 8]
	str	w0, [x7, 212]
	ldr	w5, [x20, 2796]
	b	.L3111
	.p2align 3
.L3129:
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x20, 252]
	bl	FSP_SetDisplay
	ldr	x0, [x26, 2816]
	ldr	w4, [x0, 8]
	add	x0, x20, x28
	ldr	w3, [x0, 4]
	b	.L3112
.L3100:
	ldr	w0, [x20, 2340]
	mov	w22, 0
	cmp	w0, 1
	bne	.L3103
	.p2align 2
.L3114:
	ldr	x2, [x20, 2424]
	mov	w25, 0
	add	x0, x2, 360
	add	x2, x2, 392
	.p2align 2
.L3104:
	ldr	w1, [x0], 4
	cmp	w25, w1
	csel	w25, w25, w1, cs
	cmp	x2, x0
	bne	.L3104
	b	.L3105
.L3115:
	str	wzr, [x29, 108]
	b	.L3126
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	3
.LC933:
	.xword	.LANCHOR5
	.align	3
.LC935:
	.xword	.LC934
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, x21, uxtw 3
	bl	_mcount
	mov	w2, 1
	mov	x0, x19
	ldr	x1, [x20, 2816]
	strb	w2, [x1, 2]
	ldr	x1, [x20, 2816]
	bl	HEVC_OutputFrmToVO
	mov	w22, w0
	ldr	x0, [x20, 2816]
	ldr	w1, [x0, 32]
	ldr	w2, [x0, 8]
	add	x1, x19, x1, lsl 2
	str	w2, [x1, 212]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L3131
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L3131:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x29, 44
	mov	x0, x19
	bl	HEVC_GetUnRefPicWithMinPoc
	cbnz	w0, .L3137
	ldr	w1, [x29, 44]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	mov	w1, 0
	cbnz	w0, .L3138
.L3134:
	ldr	x19, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3137:
	ldr	x2, .LC937
	mov	w0, 1
	ldr	x1, .LC939
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, -1
	b	.L3134
	.p2align 3
.L3138:
	ldr	x2, .LC937
	mov	w0, 1
	ldr	x1, .LC941
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, -1
	b	.L3134
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	3
.LC937:
	.xword	.LANCHOR5
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC941:
	.xword	.LC940
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3148
	ldr	w0, [x19, 2796]
	mov	w20, 0
	mov	w22, 1
	cbnz	w0, .L3151
	b	.L3147
	.p2align 3
.L3155:
	strb	w22, [x1, 2]
	ldr	x1, [x21, 2816]
	bl	HEVC_OutputFrmToVO
	cmn	w0, #1
	mov	w21, w0
	beq	.L3154
.L3144:
	ldr	w0, [x19, 2796]
	cmp	w0, w20
	bls	.L3147
.L3151:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 252]
	mov	w2, 0
	add	w20, w20, 1
	ldr	x1, [x21, 2816]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x21, 2816]
	mov	x0, x19
	ldrb	w2, [x1, 2]
	cbz	w2, .L3155
	ldr	w1, [x1, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L3144
	ldr	x1, [x21, 2816]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 2796]
	cmp	w0, w20
	bhi	.L3151
.L3147:
	mov	w1, -2147483647
	mov	x0, x19
	str	w1, [x19, 212]
	mov	w21, 0
	bl	HEVC_InitDecBuffers
.L3140:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3154:
	ldr	x2, .LC942
	mov	w0, 0
	ldr	x1, .LC944
	add	x2, x2, 248
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L3148:
	mov	w21, -1
	b	.L3140
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	3
.LC942:
	.xword	.LANCHOR5
	.align	3
.LC944:
	.xword	.LC943
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 2400]
	str	wzr, [x19, 320]
	cbz	x0, .L3186
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 2456]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L3187
.L3163:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L3164
	ldr	x1, [x19, 2400]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bls	.L3165
	ldr	w2, [x1, 36]
	cmp	w2, 1
	beq	.L3164
.L3165:
	ldr	w2, [x20, 24]
	cmp	w2, wzr
	ble	.L3166
	ldr	x2, [x20, 8]
	cbz	x2, .L3166
	ldr	w3, [x20, 16]
	cbnz	w3, .L3188
.L3166:
	mov	w0, 1
	str	w0, [x1, 36]
	ldr	w0, [x19, 252]
	ldr	w1, [x20, 28]
	bl	SM_ReleaseStreamSeg
.L3162:
	ldr	x0, [x19, 2400]
	ldr	w0, [x0, 36]
	cmp	w0, wzr
	csetm	w0, eq
.L3160:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3188:
	uxtw	x0, w0
	add	x0, x1, x0, lsl 5
	str	x2, [x0, 40]
	ldr	x1, [x19, 2400]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 48]
	ldr	x1, [x19, 2400]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 52]
	ldr	x1, [x19, 2400]
	ldr	w2, [x20, 28]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 68]
	ldr	x1, [x19, 2400]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 60]
	ldr	x1, [x19, 2400]
	ldr	w0, [x1, 8]
	add	w0, w0, 1
	str	w0, [x1, 8]
	ldr	x0, [x19, 2456]
	ldrb	w0, [x0, 952]
	cmp	w0, 1
	beq	.L3167
	ldr	w0, [x19, 4036]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4040]
	add	w1, w0, w1
	str	w1, [x19, 4036]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4040]
.L3167:
	mov	x0, x19
	bl	HEVC_CombinePacket
	mov	w0, 1
	str	w0, [x19, 320]
	b	.L3162
	.p2align 3
.L3187:
	ldr	w0, [x0, 928]
	cbnz	w0, .L3162
	b	.L3163
	.p2align 3
.L3186:
	ldr	w0, [x20, 24]
	cmp	w0, wzr
	ble	.L3158
	ldr	x0, [x20, 8]
	cbz	x0, .L3158
	ldr	w0, [x20, 16]
	cbz	w0, .L3158
	mov	x0, x19
	bl	HEVC_FindNaluArraySlot
	cmn	w0, #1
	mov	w21, w0
	beq	.L3189
	ldr	x0, [x19, 2448]
	mov	w2, 104
	mov	w1, 1
	smaddl	x0, w21, w2, x0
	str	x0, [x19, 2400]
	ldr	x2, [x20, 8]
	str	x2, [x0, 40]
	ldr	x0, [x19, 2400]
	ldr	w2, [x20, 24]
	str	w2, [x0, 48]
	ldr	x0, [x19, 2400]
	ldr	w2, [x20, 28]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2400]
	ldr	w2, [x20, 16]
	str	w2, [x0, 52]
	ldr	x0, [x19, 2400]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2400]
	str	w1, [x0, 8]
	ldr	x0, [x19, 2400]
	strb	wzr, [x0]
	ldr	x0, [x19, 2400]
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 2456]
	ldrb	w0, [x0, 952]
	cmp	w0, 1
	beq	.L3161
	ldr	w0, [x19, 4036]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4040]
	add	w1, w0, w1
	str	w1, [x19, 4036]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4040]
.L3161:
	ldr	w0, [x20, 20]
	str	w0, [x19, 2328]
	b	.L3162
	.p2align 3
.L3164:
	ldr	x1, .LC950
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3160
	.p2align 3
.L3158:
	ldr	x1, .LC948
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3160
.L3189:
	ldr	x1, .LC946
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, w21
	b	.L3160
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	3
.LC946:
	.xword	.LC945
	.align	3
.LC948:
	.xword	.LC947
	.align	3
.LC950:
	.xword	.LC949
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w2, [x19, 2796]
	cbnz	w2, .L3202
	b	.L3192
	.p2align 3
.L3193:
	cmp	w2, w20
	bls	.L3192
.L3202:
	add	x0, x19, x20, uxtw 3
	add	w20, w20, 1
	ldr	x0, [x0, 2816]
	ldrb	w1, [x0, 1]
	cbz	w1, .L3193
	strb	wzr, [x0, 1]
	mov	w2, 0
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_SetRef
	ldr	w2, [x19, 2796]
	cmp	w2, w20
	bhi	.L3202
	.p2align 2
.L3192:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbz	w0, .L3196
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L3192
	b	.L3196
	.p2align 3
.L3198:
	bl	HEVC_GetMinPOC
	ldr	w1, [x29, 40]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L3197
.L3196:
	ldr	w3, [x19, 2796]
	add	x2, x29, 40
	add	x1, x29, 44
	mov	x0, x19
	cbnz	w3, .L3198
	mov	w0, 0
.L3197:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_FlushDPB
	cbz	w0, .L3208
	ldr	x2, .LC951
	mov	w3, w0
	ldr	x1, .LC953
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L3208:
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	3
.LC951:
	.xword	.LANCHOR5
	.align	3
.LC953:
	.xword	.LC952
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC954
	ldr	x22, .LC956
	add	x21, x20, 296
	b	.L3213
	.p2align 3
.L3215:
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L3223
.L3213:
	ldr	w5, [x19, 2792]
	mov	x2, x21
	ldr	w6, [x19, 2796]
	mov	x1, x22
	mov	w0, 13
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcs	.L3215
.L3212:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3223:
	ldr	x1, .LC958
	mov	x2, x21
	mov	w0, 1
	add	x20, x20, 296
	bl	dprint_vfmw
	ldr	x21, .LC960
	.p2align 2
.L3214:
	ldr	w5, [x19, 2792]
	mov	x2, x20
	ldr	w6, [x19, 2796]
	mov	x1, x21
	mov	w0, 1
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcc	.L3212
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_OutputUnRefPicWithMinPoc
	cbz	w0, .L3214
	ldr	x1, .LC961
	mov	x2, x20
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	mov	x0, x19
	bl	HEVC_ClearDPB
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	3
.LC954:
	.xword	.LANCHOR5
	.align	3
.LC956:
	.xword	.LC955
	.align	3
.LC958:
	.xword	.LC957
	.align	3
.LC960:
	.xword	.LC959
	.align	3
.LC961:
	.xword	.LC940
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	mov	x19, x2
	bl	_mcount
	cmp	w22, 16
	bhi	.L3228
	add	x20, x21, x22, uxtw 3
	ldr	x0, [x19, 64]
	mov	w1, 1
	mov	w2, w1
	str	x0, [x20, 2816]
	str	w1, [x0, 48]
	ldr	x1, [x20, 2816]
	ldr	w0, [x21, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldrb	w1, [x19]
	mov	x2, 632
	ldr	x0, [x20, 2816]
	cmp	w1, wzr
	add	x1, x19, 72
	cset	w3, ne
	strb	w3, [x0, 1]
	ldr	x0, [x20, 2816]
	ldr	w3, [x19, 36]
	str	w3, [x0, 20]
	ldr	x0, [x20, 2816]
	add	x0, x0, 80
	bl	memcpy
	ldr	x0, [x20, 2816]
	add	w1, w22, 1
	ldr	w4, [x19, 40]
	mov	w2, 8
	ldr	x3, .LC966
	str	w4, [x0, 16]
	add	x0, x21, 2816
	ldr	x4, [x20, 2816]
	ldr	x5, [x19, 64]
	str	x5, [x4, 72]
	ldr	x4, [x20, 2816]
	ldr	w5, [x19, 16]
	str	w5, [x4, 12]
	ldr	x4, [x20, 2816]
	ldr	w5, [x19, 12]
	str	w5, [x4, 8]
	ldr	x4, [x20, 2816]
	ldr	w5, [x19, 8]
	str	w5, [x4, 32]
	bl	qsort
	ldr	w1, [x21, 2796]
	mov	x0, x21
	add	w1, w1, 1
	str	w1, [x21, 2796]
	ldr	x1, [x19, 64]
	bl	HEVC_GetAPC
	cbnz	w0, .L3229
	strb	wzr, [x19, 1]
	mov	w0, 0
.L3226:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3228:
	ldr	x2, .LC963
	mov	w3, w22
	ldr	x1, .LC965
	mov	w0, 0
	add	x2, x2, 320
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L3226
	.p2align 3
.L3229:
	ldr	x2, .LC963
	mov	w3, w0
	ldr	x1, .LC968
	mov	w0, 0
	add	x2, x2, 320
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_PrintDPBState
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L3226
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	3
.LC963:
	.xword	.LANCHOR5
	.align	3
.LC965:
	.xword	.LC964
	.align	3
.LC966:
	.xword	HEVC_ComparePicByPocAsc
	.align	3
.LC968:
	.xword	.LC967
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 3984]
	cbnz	w0, .L3243
	ldr	x0, [x19, 4048]
	mov	w1, 2
	str	w1, [x0, 48]
.L3232:
	ldr	x1, [x19, 4048]
	mov	w2, 1
	mov	x0, x19
	strb	w2, [x1, 2]
	ldr	x1, [x19, 4048]
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L3244
	cmn	w0, #3
	beq	.L3236
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L3245
.L3236:
	mov	w0, 0
.L3233:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3243:
	mov	x0, x19
	bl	HEVC_SimpleSlideDPB
	ldr	w1, [x19, 2796]
	add	x2, x19, 3984
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbz	w0, .L3232
	ldr	x2, .LC969
	mov	w4, w0
	ldr	x1, .LC971
	mov	w3, 10933
	add	x2, x2, 344
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3233
	.p2align 3
.L3245:
	ldr	x2, .LC969
	mov	w0, 0
	ldr	x1, .LC974
	add	x2, x2, 344
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3233
.L3244:
	ldr	x2, .LC969
	mov	w0, 0
	ldr	x1, .LC973
	add	x2, x2, 344
	bl	dprint_vfmw
	mov	w0, w20
	b	.L3233
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	3
.LC969:
	.xword	.LANCHOR5
	.align	3
.LC971:
	.xword	.LC970
	.align	3
.LC973:
	.xword	.LC972
	.align	3
.LC974:
	.xword	.LC926
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2792]
	ldr	w1, [x19, 2796]
	cmp	w1, w0
	bcs	.L3258
.L3247:
	add	x2, x19, 3984
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3259
	ldr	x1, [x19, 4048]
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L3260
	cmn	w0, #3
	beq	.L3253
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L3261
.L3253:
	mov	w0, 0
.L3250:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3258:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L3257
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC977
	add	x2, x2, 368
	bl	dprint_vfmw
.L3257:
	ldr	w1, [x19, 2796]
	b	.L3247
.L3261:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC981
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3250
	.p2align 3
.L3259:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC979
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3250
.L3260:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC980
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, w20
	b	.L3250
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	3
.LC975:
	.xword	.LANCHOR5
	.align	3
.LC977:
	.xword	.LC976
	.align	3
.LC979:
	.xword	.LC978
	.align	3
.LC980:
	.xword	.LC972
	.align	3
.LC981:
	.xword	.LC926
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 11912]
	cmp	w0, 1
	beq	.L3263
	mov	x0, x19
	bl	HEVC_FirstFrameFastOut
	cbnz	w0, .L3280
.L3263:
	ldr	w0, [x19, 2792]
	ldr	w1, [x19, 2796]
	cmp	w1, w0
	bcs	.L3281
.L3265:
	add	x2, x19, 3984
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3282
	ldr	w0, [x19, 2796]
	cbnz	w0, .L3268
.L3269:
	mov	w0, 0
.L3264:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3268:
	mov	x0, x19
	bl	HEVC_OutputFrmFromDPB
	cbz	w0, .L3269
	ldr	x2, .LC982
	mov	w0, 1
	ldr	x1, .LC990
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3264
	.p2align 3
.L3281:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L3279
	ldr	x1, .LC986
	mov	w0, 0
	bl	dprint_vfmw
.L3279:
	ldr	w1, [x19, 2796]
	b	.L3265
	.p2align 3
.L3282:
	ldr	x1, .LC988
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3264
.L3280:
	ldr	x2, .LC982
	mov	w0, 0
	ldr	x1, .LC984
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3264
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	3
.LC982:
	.xword	.LANCHOR5
	.align	3
.LC984:
	.xword	.LC983
	.align	3
.LC986:
	.xword	.LC985
	.align	3
.LC988:
	.xword	.LC987
	.align	3
.LC990:
	.xword	.LC989
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrsw	x1, [x19, 252]
	ldr	x0, .LC991
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L3322
.L3284:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w0, [x19, 3985]
	cbz	w0, .L3323
	ldr	w0, [x19, 4024]
	cbz	w0, .L3289
	ldr	w1, [x19, 4000]
	cbz	w1, .L3324
.L3290:
	ldr	x1, [x19, 2456]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bcc	.L3325
.L3289:
	ldr	x1, [x19, 2472]
	ldr	x0, [x19, 4048]
	ldr	w1, [x1, 5192]
	str	w1, [x0, 40]
	ldr	x1, [x19, 2472]
	ldr	x0, [x19, 4048]
	ldr	w1, [x1, 5196]
	str	w1, [x0, 44]
	ldr	w0, [x19, 256]
	cmp	w0, 2
	beq	.L3326
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	beq	.L3327
	cmp	w0, 1
	beq	.L3328
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3302
.L3300:
	mov	x0, x19
	bl	HEVC_DispOrderProcess
	mov	w20, w0
	cbnz	w0, .L3329
.L3301:
	strb	wzr, [x19, 3985]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3322:
	ldr	w1, [x0, 156]
	cbnz	w1, .L3284
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L3284
	add	x0, x19, 8192
	ldrb	w0, [x0, 3664]
	cmp	w0, 1
	bne	.L3284
	ldr	w4, [x19, 11868]
	ldr	w5, [x19, 11872]
	ldr	x6, [x19, 11880]
	ldr	x3, [x19, 11888]
	ldr	x7, [x19, 11896]
	cbz	w4, .L3303
	mov	w1, w4
	mov	w2, w5
	b	.L3286
	.p2align 3
.L3304:
	mov	w1, w0
.L3286:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L3304
.L3285:
	udiv	w0, w4, w1
	sub	x3, x3, x7
	lsl	w2, w3, 6
	sub	w2, w2, w3
	lsl	w2, w2, 1
	sub	w2, w2, w3
	lsl	w2, w2, 3
	udiv	w1, w5, w1
	mul	w0, w2, w0
	udiv	w0, w0, w1
	add	x0, x0, x6
	str	x0, [x19, 4640]
	b	.L3284
	.p2align 3
.L3323:
	ldr	x2, .LC992
	mov	w0, 1
	ldr	x1, .LC994
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3325:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x3, [x19, 2456]
	mov	w0, 1
	ldr	w2, [x19, 4024]
	ldr	x1, .LC999
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3327:
	mov	x0, x19
	bl	HEVC_SimpleDPBProcess
	mov	w20, w0
	cbnz	w0, .L3330
.L3297:
	ldr	x1, .LC1003
	mov	w3, 11210
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L3295:
	cmn	w20, #1
	bne	.L3301
	.p2align 2
.L3302:
	mov	x0, x19
	mov	w20, -1
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC992
	mov	w0, 1
	ldr	x1, .LC1011
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3301
	.p2align 3
.L3324:
	ldr	x2, .LC992
	mov	w0, 1
	ldr	x1, .LC996
	add	x2, x2, 416
	bl	dprint_vfmw
	ldr	x0, .LC997
	ldr	x4, [x0]
	cbz	x4, .L3321
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3321:
	ldr	w0, [x19, 4024]
	b	.L3290
	.p2align 3
.L3326:
	mov	x0, x19
	bl	HEVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 184]
	ldr	w0, [x19, 4020]
	cmp	w0, w1
	beq	.L3293
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 2132]
	str	w1, [x19, 4020]
.L3293:
	cbnz	w20, .L3331
.L3294:
	ldr	x1, .LC1003
	mov	w3, 11195
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3295
	.p2align 3
.L3328:
	mov	x0, x19
	bl	HEVC_DecOrderProcess
	mov	w20, w0
	cbnz	w0, .L3299
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3301
	b	.L3300
	.p2align 3
.L3329:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1009
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3295
	.p2align 3
.L3299:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1007
	add	x2, x2, 416
	bl	dprint_vfmw
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3295
	b	.L3300
	.p2align 3
.L3331:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1001
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3294
	.p2align 3
.L3330:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1005
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3297
.L3303:
	mov	w1, w5
	b	.L3285
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	3
.LC991:
	.xword	s_pstVfmwChan
	.align	3
.LC992:
	.xword	.LANCHOR5
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC996:
	.xword	.LC995
	.align	3
.LC997:
	.xword	g_event_report
	.align	3
.LC999:
	.xword	.LC998
	.align	3
.LC1001:
	.xword	.LC1000
	.align	3
.LC1003:
	.xword	.LC1002
	.align	3
.LC1005:
	.xword	.LC1004
	.align	3
.LC1007:
	.xword	.LC1006
	.align	3
.LC1009:
	.xword	.LC1008
	.align	3
.LC1011:
	.xword	.LC1010
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	sub	sp, sp, #704
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w1
	add	x19, x20, 12288
	bl	_mcount
	mov	w21, 0
	ldr	x3, .LC1012
	mov	x2, 704
	mov	w1, 0
	add	x0, x29, 80
	add	x19, x19, 1184
	ldr	x3, [x3, 96]
	blr	x3
	.p2align 2
.L3338:
	ldr	w0, [x19, 48]
	cbnz	w0, .L3333
	cbz	x19, .L3334
	ldr	w2, [x20, 2796]
	cbz	w2, .L3334
	ldr	x0, [x20, 2816]
	cmp	x19, x0
	beq	.L3333
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L3336
	.p2align 3
.L3337:
	ldr	x1, [x0, 2816]
	cmp	x19, x1
	beq	.L3333
.L3336:
	cmp	x2, x0
	add	x0, x0, 8
	bne	.L3337
.L3334:
	sxtw	x22, w21
	mov	w24, 1
	lsl	x1, x22, 2
	mov	w4, 101
	sub	x3, x1, x22
	mov	x2, 632
	lsl	x1, x3, 4
	add	x0, x29, 152
	sub	x1, x1, x3
	strb	w24, [x29, 81]
	lsl	x1, x1, x24
	strb	w24, [x29, 80]
	sub	x22, x1, x22
	str	w23, [x29, 92]
	str	w4, [x29, 120]
	add	x22, x20, x22, lsl 3
	add	x25, x22, 12288
	add	x1, x25, 1264
	bl	memcpy
	strb	w24, [x25, 1186]
	str	wzr, [x22, 13524]
	cmp	w21, 19
	strb	w24, [x25, 1184]
	str	x19, [x29, 144]
	str	wzr, [x29, 304]
	bgt	.L3339
	ldr	w5, [x20, 2796]
	cbz	w5, .L3341
	mov	w6, 0
	mov	w3, 2147483647
	mov	w1, 0
	.p2align 2
.L3344:
	add	x0, x20, x1, sxtw 3
	add	w1, w1, 1
	ldr	x4, [x0, 2816]
	ldr	w0, [x4, 8]
	sub	w0, w0, w23
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w3
	bge	.L3343
	ldrb	w0, [x4, 1]
	cmp	w0, wzr
	csel	w3, w3, w2, eq
	csinc	w6, w6, wzr, eq
.L3343:
	cmp	w1, w5
	bne	.L3344
	cbz	w6, .L3341
	mov	w1, 0
	b	.L3345
	.p2align 3
.L3346:
	cmp	w5, w1
	beq	.L3347
.L3345:
	sxtw	x19, w1
	add	w1, w1, 1
	add	x19, x19, 350
	add	x19, x20, x19, lsl 3
	ldr	x2, [x19, 16]
	ldr	w0, [x2, 8]
	sub	w0, w0, w23
	sxtw	x0, w0
	eor	x4, x0, x0, asr 63
	sub	x4, x4, x0, asr 63
	cmp	w3, w4
	bne	.L3346
	ldrb	w0, [x2, 1]
	cbz	w0, .L3346
	ldp	w1, w22, [x2, 28]
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	mov	x21, x0
	ldr	x2, [x19, 16]
	mov	w3, w23
	ldr	x1, .LC1020
	mov	w0, 1
	ldr	w2, [x2, 8]
	bl	dprint_vfmw
	cbz	x21, .L3347
	ldr	x0, [x21, 32]
	cbz	x0, .L3380
	ldr	w0, [x20, 252]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	mov	w19, w0
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	mov	x1, x0
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L3350
	ldr	x3, [x29, 144]
	add	x2, x29, 80
	mov	x0, x20
	str	w19, [x3, 28]
	ldr	x3, [x21, 32]
	str	x3, [x1, 32]
	ldr	x3, [x21, 40]
	str	x3, [x1, 40]
	ldrsb	w3, [x21, 4]
	ldr	w1, [x20, 2796]
	str	w22, [x29, 88]
	str	w3, [x29, 116]
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3381
	ldr	w0, [x20, 252]
	mov	w2, 0
	mov	w1, w19
	bl	FSP_SetDisplay
	ldr	w1, [x20, 4720]
	mov	w2, 2147483647
	mov	w0, 0
	add	x20, x20, x1, lsl 2
	ldr	w1, [x20, 228]
	cmp	w1, w2
	bne	.L3366
	str	w23, [x20, 228]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L3333:
	add	w21, w21, 1
	add	x19, x19, 712
	cmp	w21, 20
	bne	.L3338
.L3339:
	ldr	x1, .LC1014
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L3366:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L3347:
	ldr	x1, .LC1016
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	mov	w0, -1
	add	sp, sp, 704
	ret
.L3350:
	ldr	x2, [x29, 144]
	mov	w0, 0
	ldr	x1, .LC1024
	strb	wzr, [x2]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3366
.L3381:
	ldr	x0, [x29, 144]
	mov	w2, 1
	mov	w1, w19
	strb	wzr, [x0]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1026
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3366
.L3341:
	ldr	x1, .LC1018
	mov	w0, 0
	strb	wzr, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3366
.L3380:
	ldr	x1, .LC1022
	bl	dprint_vfmw
	mov	x0, x20
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L3366
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	3
.LC1012:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1016:
	.xword	.LC1015
	.align	3
.LC1018:
	.xword	.LC1017
	.align	3
.LC1020:
	.xword	.LC1019
	.align	3
.LC1022:
	.xword	.LC1021
	.align	3
.LC1024:
	.xword	.LC1023
	.align	3
.LC1026:
	.xword	.LC1025
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	mov	x0, x19
	bl	HEVC_ApplyReferencePictureSet
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	ldr	x20, .LC1028
	b	.L3383
	.p2align 3
.L3386:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.7
	cbnz	w0, .L3388
	ldr	w2, [x29, 44]
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2456]
	mov	x0, x19
	ldr	w1, [x1, 4]
	cbz	w1, .L3384
	ldr	w1, [x29, 44]
	bl	HEVC_CreateLostPicture
	cbnz	w0, .L3391
.L3383:
	ldr	w2, [x19, 4716]
	add	x1, x29, 44
	mov	x0, x19
	sub	w2, w2, #19
	cmp	w2, 2
	bhi	.L3386
.L3388:
	mov	x0, x19
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
	mov	x0, x19
	bl	HEVC_RecoverDPBProcess
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3384:
	ldr	w3, [x19, 4700]
	mov	w2, 0
	ldr	w4, [x29, 44]
	mov	w0, 1
	ldr	x1, .LC1030
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3391:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	3
.LC1028:
	.xword	.LC1027
	.align	3
.LC1030:
	.xword	.LC1029
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 176]
	cmp	w0, 2
	bls	.L3451
	ldr	w0, [x19, 288]
	mov	w2, 1
	ldr	w1, [x19, 292]
	add	w0, w0, 1
	ldr	x3, [x19, 2456]
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 288]
	sub	w0, w0, w1
	str	w0, [x3, 616]
	strb	w2, [x19, 3984]
	ldr	w20, [x19, 248]
	ldr	w2, [x19, 256]
	ubfx	x20, x20, 16, 3
	cmp	w20, w2
	beq	.L3397
	sub	w0, w2, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L3397
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L3452
.L3397:
	cmp	w20, 2
	str	w20, [x19, 256]
	beq	.L3399
	cmp	w20, 3
	bne	.L3448
.L3450:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
.L3447:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3448:
	ldr	w0, [x19, 236]
	cbz	w0, .L3418
	cmp	w20, 4
	ldr	w0, [x19, 4000]
	bne	.L3405
	cbnz	w0, .L3405
	mov	w0, 2
	strb	w0, [x19, 6]
	.p2align 2
.L3409:
	ldr	w2, [x19, 240]
	mov	w0, 2
	ldr	x1, .LC1040
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x19, 204]
	cbz	w0, .L3453
	ldr	w2, [x19, 4012]
	ldr	x1, [x19, 2456]
	ldr	w3, [x19, 4016]
	cmp	w2, wzr
	str	w3, [x19, 7988]
	cset	w3, eq
	str	w0, [x19, 9144]
	add	x0, x19, 4096
	str	w3, [x19, 7996]
	ldr	w3, [x1, 632]
	strb	w3, [x0, 2560]
	ldr	w3, [x1, 636]
	strb	w3, [x0, 2561]
	ldr	w3, [x1, 640]
	strb	w3, [x0, 2563]
	ldr	w3, [x1, 644]
	strb	w3, [x0, 2564]
	ldr	w3, [x1, 684]
	ldr	w1, [x19, 240]
	str	w3, [x19, 7984]
	cbz	w1, .L3414
	add	x0, x0, 2560
	ldr	w1, [x19, 4028]
	str	x0, [x19, 2472]
	add	w2, w2, 1
	str	w1, [x0, 5192]
	ldr	w1, [x19, 4032]
	str	w1, [x0, 5196]
	str	w2, [x19, 4012]
	str	wzr, [x0, 5188]
	ldr	w0, [x19, 4000]
	cbnz	w0, .L3414
	ldr	x1, [x19, 9152]
	mov	w4, 0
	cbz	x1, .L3416
	.p2align 2
.L3417:
	ldp	w2, w0, [x1]
	ldr	x1, [x1, 1360]
	add	w0, w2, w0
	add	w0, w0, 7
	add	w4, w4, w0, lsr 3
	cbnz	x1, .L3417
.L3416:
	ldr	x0, .LC1031
	ldr	x5, [x0]
	cbz	x5, .L3414
	add	x2, x29, 48
	ldr	w0, [x19, 252]
	mov	w3, 4
	mov	w1, 20
	str	w4, [x2, -8]!
	blr	x5
.L3414:
	ldr	w4, [x19, 4040]
	mov	w0, 0
	ldr	x3, [x19, 4048]
	ldr	w1, [x19, 4036]
	str	w4, [x19, 4036]
	sub	w1, w1, w4
	ldr	w2, [x3, 320]
	add	w2, w2, w1
	str	w2, [x3, 320]
	ldr	w2, [x19, 4296]
	add	w1, w2, w1
	str	w1, [x19, 4296]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3399:
	ldr	w0, [x19, 4000]
	cbnz	w0, .L3403
	ldr	w1, [x19, 236]
	cbz	w1, .L3418
.L3405:
	cmp	w0, 2
	beq	.L3454
	cmp	w0, 1
	bne	.L3409
	strb	w0, [x19, 6]
	b	.L3409
	.p2align 3
.L3454:
	ldrb	w0, [x19, 6]
	cmp	w0, 2
	bne	.L3409
	ldr	x0, .LC1038
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3409
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3409
	mov	w3, 1
	ldr	x1, .LC1045
	ldr	w2, [x19, 3996]
	mov	w0, w3
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3455
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, -1
	b	.L3447
	.p2align 3
.L3418:
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3403
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3403:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L3447
.L3452:
	ldr	x1, .LC1037
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	str	w20, [x19, 256]
	b	.L3450
	.p2align 3
.L3455:
	mov	w0, -1
	b	.L3447
	.p2align 3
.L3453:
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3412
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3412:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1041
	mov	w0, 0
	ldr	x1, .LC1043
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3447
	.p2align 3
.L3451:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3394
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3394:
	ldr	w0, [x19, 244]
	cmp	w0, 524288
	bls	.L3395
	ldr	x1, .LC1033
	mov	w0, 0
	bl	dprint_vfmw
.L3395:
	ldr	x1, .LC1035
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3447
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	3
.LC1031:
	.xword	g_event_report
	.align	3
.LC1033:
	.xword	.LC1032
	.align	3
.LC1035:
	.xword	.LC1034
	.align	3
.LC1037:
	.xword	.LC1036
	.align	3
.LC1038:
	.xword	g_allow_B_before_P
	.align	3
.LC1040:
	.xword	.LC1039
	.align	3
.LC1041:
	.xword	.LANCHOR5
	.align	3
.LC1043:
	.xword	.LC1042
	.align	3
.LC1045:
	.xword	.LC1044
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w23, w2
	mov	w25, w3
	mov	w20, w1
	bl	_mcount
	ldr	x0, [x19, 2360]
	mov	w1, 16
	str	xzr, [x29, 88]
	add	x22, x19, 4096
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	and	w24, w0, 31
	ldr	x0, [x19, 2360]
	mov	w1, 24
	bl	BsBack
	str	wzr, [x22, 380]
	ldr	x1, [x22, 392]
	str	x1, [x29, 88]
	cbz	w20, .L3458
	cmp	w20, 1
	beq	.L3459
	ldr	x1, .LC1062
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
.L3466:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3459:
	mov	w0, 31745
	cmp	w21, w0
	cbz	w23, .L3616
	ccmp	w24, 25, 0, eq
	bne	.L3487
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3488
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3488:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2400]
	cbz	w0, .L3617
.L3611:
	cbz	x1, .L3492
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3492:
	ldr	x4, [x20]
	cbz	x4, .L3591
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3591:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3458:
	cbnz	w23, .L3460
	mov	w0, 31745
	cmp	w21, w0
	ccmp	w24, 25, 0, eq
	bne	.L3461
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3462
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3462:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2400]
	cbnz	w0, .L3611
	ldr	w0, [x1, 48]
	add	x23, x22, 376
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L3467
	ldr	x1, .LC1048
	mov	w3, 2348
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	b	.L3611
	.p2align 3
.L3460:
	mov	w0, 31745
	and	w21, w21, -513
	cmp	w21, w0
	mov	w0, 1
	bne	.L3466
	ldr	x2, .LC1049
	mov	w3, 2434
	ldr	x1, .LC1058
.L3595:
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	cbz	x1, .L3591
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	mov	w0, -1
	b	.L3466
	.p2align 3
.L3616:
	ccmp	w25, 1, 0, eq
	ccmp	w24, 25, 0, eq
	beq	.L3618
	mov	w1, 32257
	cmp	w21, w1
	beq	.L3619
	cmp	w21, w0
	bne	.L3620
.L3499:
	ldr	x1, [x19, 2400]
.L3602:
	cbz	x1, .L3592
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3592:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3487:
	mov	w1, 32257
	mov	w0, w20
	cmp	w21, w1
	bne	.L3466
	ldr	x2, .LC1049
	mov	w3, 2579
	ldr	x1, .LC1060
	b	.L3595
	.p2align 3
.L3461:
	mov	w1, 32257
	mov	w0, 1
	cmp	w21, w1
	bne	.L3466
	b	.L3499
	.p2align 3
.L3617:
	ldr	w0, [x1, 48]
	add	x23, x22, 376
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L3491
	ldr	x1, .LC1048
	mov	w3, 2513
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	b	.L3611
	.p2align 3
.L3620:
	ldr	x0, [x19, 2360]
	mov	w1, 8
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2360]
	mov	w1, 8
	ubfx	x20, x20, 1, 6
	bl	BsSkip
	cmp	w20, 49
	bne	.L3499
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L3499
	ldr	x1, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2360]
	mov	w1, 24
	bl	BsSkip
	mov	w0, 2
	b	.L3466
	.p2align 3
.L3618:
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3481
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3481:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2400]
	cbz	w0, .L3602
	b	.L3611
	.p2align 3
.L3491:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 252]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3621
	ldr	x21, .LC1052
	mov	x2, 5
	ldr	x1, .LC1053
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2400]
	ldr	x0, [x29, 88]
	ldr	w2, [x23, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x21, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x19, 2400]
	ldr	w2, [x1, 80]
	cbz	w2, .L3494
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L3495
	uxtw	x2, w0
	ldr	x1, .LC1048
	mov	w3, 2537
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	cbz	x1, .L3496
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3496:
	ldr	x4, [x20]
	cbz	x4, .L3497
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3497:
	ldr	w0, [x19, 252]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3591
	ldr	x2, .LC1049
	mov	w3, 2544
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
	.p2align 3
.L3467:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 252]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3622
	ldr	x21, .LC1052
	mov	x2, 5
	ldr	x1, .LC1053
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2400]
	ldr	x0, [x29, 88]
	ldr	w2, [x23, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x21, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x19, 2400]
	ldr	w2, [x1, 80]
	cbz	w2, .L3471
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L3472
	uxtw	x2, w0
	ldr	x1, .LC1048
	mov	w3, 2372
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	cbz	x1, .L3473
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3473:
	ldr	x4, [x20]
	cbz	x4, .L3474
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3474:
	ldr	w0, [x19, 252]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3591
	ldr	x2, .LC1049
	mov	w3, 2379
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
.L3472:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2400]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L3471:
	ldr	x20, .LC1056
	ldr	w0, [x19, 252]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L3475
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 252]
	ldr	w1, [x22, 380]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 252]
.L3475:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3499
	ldr	x2, .LC1049
	mov	w3, 2407
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
	.p2align 3
.L3495:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2400]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L3494:
	ldr	x20, .LC1056
	ldr	w0, [x19, 252]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L3498
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 252]
	ldr	w1, [x22, 380]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 252]
.L3498:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3499
	ldr	x2, .LC1049
	mov	w3, 2567
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
	.p2align 3
.L3619:
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsSkip
	mov	w0, w20
	b	.L3466
.L3621:
	ldr	x2, .LC1049
	mov	w3, 2525
	ldr	x1, .LC1051
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
.L3622:
	ldr	x2, .LC1049
	mov	w3, 2360
	ldr	x1, .LC1051
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3466
	.size	HEVC_VES_Splitter, .-HEVC_VES_Splitter
	.align	3
.LC1046:
	.xword	g_event_report
	.align	3
.LC1048:
	.xword	.LC1047
	.align	3
.LC1049:
	.xword	.LANCHOR5
	.align	3
.LC1051:
	.xword	.LC1050
	.align	3
.LC1052:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1053:
	.xword	.LANCHOR4
	.align	3
.LC1055:
	.xword	.LC1054
	.align	3
.LC1056:
	.xword	vfmw_save_metadata_file
	.align	3
.LC1058:
	.xword	.LC1057
	.align	3
.LC1060:
	.xword	.LC1059
	.align	3
.LC1062:
	.xword	.LC1061
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CRAOutputFrame
	.type	HEVC_CRAOutputFrame, %function
HEVC_CRAOutputFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2796]
	cbz	w0, .L3635
	sub	w2, w0, #1
	mov	w20, 0
	add	x2, x2, 353
	add	x0, x19, 2816
	add	x2, x19, x2, lsl 3
	.p2align 2
.L3626:
	ldr	x1, [x0], 8
	ldrb	w1, [x1, 2]
	cmp	w1, wzr
	csinc	w20, w20, w20, ne
	cmp	x0, x2
	bne	.L3626
	.p2align 2
.L3627:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L3627
	cmp	w20, wzr
	ble	.L3629
	.p2align 2
.L3642:
	ldr	w1, [x19, 2796]
	cbz	w1, .L3630
	ldr	x0, [x19, 2816]
	ldrb	w0, [x0, 2]
	cbz	w0, .L3637
	add	x2, x19, 2824
	mov	w0, 0
	b	.L3634
	.p2align 3
.L3631:
	ldr	x3, [x2], 8
	ldrb	w3, [x3, 2]
	cbz	w3, .L3636
.L3634:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3631
.L3630:
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L3632
	subs	w20, w20, #1
	bne	.L3642
.L3629:
	mov	w0, 0
.L3632:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3636:
	mov	w1, w0
	b	.L3630
.L3637:
	mov	w1, 0
	b	.L3630
.L3635:
	mov	w20, 0
	b	.L3627
	.size	HEVC_CRAOutputFrame, .-HEVC_CRAOutputFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2400]
	ldrsw	x3, [x19, 252]
	ldr	x2, .LC1063
	ldr	w1, [x0, 16]
	str	w1, [x19, 4716]
	ldr	w4, [x0, 28]
	str	w4, [x19, 4712]
	ldr	w20, [x0, 24]
	strb	wzr, [x19, 3]
	str	w20, [x19, 4720]
	ldr	x2, [x2, x3, lsl 3]
	ldrsb	w3, [x2, 44]
	cmp	w3, 1
	beq	.L3711
.L3650:
	ldr	w0, [x19, 4840]
	cmp	w0, 1
	beq	.L3712
.L3654:
	ldr	w0, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w0
	bcs	.L3713
	ldrb	w0, [x19, 3985]
	cbz	w0, .L3714
	mov	x0, x19
	bl	HEVC_PicTypeStatistic
	mov	x0, x19
	bl	HEVC_CalcStreamBits
	ldr	w0, [x19, 4840]
	cmp	w0, 2
	beq	.L3671
	ldr	w0, [x19, 2332]
	cbnz	w0, .L3672
	add	x0, x19, 4096
	ldrb	w0, [x0, 593]
	cbz	w0, .L3715
.L3672:
	mov	x0, x19
	bl	HEVC_WriteSliceMsg
	cbnz	w0, .L3716
.L3675:
	ldr	w0, [x19, 2332]
	cbz	w0, .L3717
.L3677:
	ldr	w0, [x19, 3372]
	ldr	w1, [x19, 3368]
	str	w0, [x19, 4032]
	mov	w0, 0
	str	w1, [x19, 4028]
.L3659:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3717:
	ldr	w1, [x19, 4700]
	mov	w0, 1
	ldr	w2, [x19, 4724]
	str	w0, [x19, 172]
	str	w1, [x19, 260]
	str	w2, [x19, 296]
	b	.L3677
	.p2align 3
.L3712:
	ldr	w0, [x19, 2332]
	cbnz	w0, .L3656
	cmp	w20, wzr
	sub	w1, w1, #16
	cset	w21, eq
	cmp	w1, 4
	cset	w0, ls
	tst	w21, w0
	beq	.L3718
.L3657:
	mov	x0, x19
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L3719
.L3658:
	add	x0, x19, x20, uxtw
	ldrb	w0, [x0, 4]
	cmp	w0, 1
	cset	w0, eq
	tst	w21, w0
	beq	.L3660
	ldr	w0, [x19, 2796]
	cbnz	w0, .L3720
	.p2align 2
.L3660:
	ldr	x1, [x19, 2456]
	ldr	w0, [x1, 12]
	cbnz	w0, .L3661
	ldr	w0, [x19, 2340]
	cmp	w0, 1
	beq	.L3721
	ldr	w0, [x19, 4712]
	ldr	x2, [x19, 2424]
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 360]
	cbnz	w20, .L3661
.L3726:
	ldr	w3, [x19, 212]
	mov	w20, -2147483647
	cmp	w3, w20
	beq	.L3661
	ldr	w2, [x19, 4700]
	add	w0, w3, w0
	cmp	w2, w0
	bcs	.L3661
	ldr	w0, [x19, 4716]
	cmp	w0, 21
	bne	.L3661
	ldr	x1, .LC1070
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_CRAOutputFrame
	str	w20, [x19, 212]
	ldr	x1, [x19, 2456]
	.p2align 2
.L3661:
	ldr	w0, [x1, 8]
	cmp	w0, 2
	beq	.L3656
	ldr	w0, [x1, 24]
	cmp	w0, 2
	mov	x0, x19
	beq	.L3722
	bl	HEVC_RefPicProcess
	cbnz	w0, .L3678
.L3656:
	mov	x0, x19
	bl	HEVC_InitPic
	cmn	w0, #2
	beq	.L3659
	cbnz	w0, .L3723
	ldr	w1, [x19, 240]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x19, 240]
	bl	HEVC_SetScalingList
	mov	x0, x19
	bl	HEVC_WritePicMsg
	cbz	w0, .L3654
	ldr	x1, .LC1074
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3711:
	ldr	w3, [x2, 156]
	cbnz	w3, .L3650
	ldr	w2, [x2, 160]
	cmp	w2, 1
	bne	.L3650
	ldr	w0, [x0, 16]
	sub	w2, w0, #19
	cmp	w2, 1
	bls	.L3724
.L3652:
	sub	w0, w0, #6
	cmp	w0, 3
	bls	.L3650
	ldr	x2, [x19, 3408]
	str	x2, [x19, 3392]
	b	.L3650
	.p2align 3
.L3671:
	ldr	x1, [x19, 2400]
	cbz	x1, .L3675
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	b	.L3675
	.p2align 3
.L3715:
	mov	x0, x19
	bl	HEVC_DecList
	cbnz	w0, .L3725
	mov	x0, x19
	bl	HEVC_IsRefListWrong
	cbz	w0, .L3672
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	x1, .LC1085
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3718:
	ldr	w0, [x19, 4000]
	cbnz	w0, .L3658
	ldr	x0, [x19, 2456]
	mov	x1, 4294967296
	ldr	x2, [x0, 688]
	cmp	x2, x1
	bne	.L3658
	ldr	w1, [x0, 696]
	cbnz	w1, .L3658
	ldr	w0, [x0, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L3658
	b	.L3657
.L3720:
	mov	x0, x19
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L3660
	ldr	x2, .LC1064
	mov	w0, 1
	ldr	x1, .LC1068
	add	x2, x2, 480
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3678:
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3722:
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
	b	.L3656
	.p2align 3
.L3714:
	ldr	x1, .LC1081
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3721:
	ldr	x4, [x19, 2424]
	mov	w0, 0
	add	x2, x4, 360
	add	x4, x4, 392
	.p2align 2
.L3663:
	ldr	w3, [x2], 4
	cmp	w0, w3
	csel	w0, w0, w3, cs
	cmp	x2, x4
	bne	.L3663
	cbnz	w20, .L3661
	b	.L3726
	.p2align 3
.L3713:
	ldr	x1, .LC1076
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w1
	bcc	.L3669
	ldr	x0, .LC1077
	ldr	x4, [x0]
	cbz	x4, .L3669
	ldr	w0, [x19, 252]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L3669:
	ldr	x1, .LC1079
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3716:
	ldr	x1, .LC1087
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3723:
	ldr	x1, .LC1072
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.p2align 3
.L3724:
	ldr	x2, [x19, 2456]
	ldr	x2, [x2, 56]
	cmn	x2, #1
	beq	.L3653
	ldr	x3, [x19, 11888]
	str	x2, [x19, 11880]
	str	x3, [x19, 11896]
.L3653:
	add	x2, x19, 8192
	mov	w3, 1
	strb	w3, [x2, 3664]
	b	.L3652
.L3725:
	ldr	x1, .LC1083
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
.L3719:
	ldr	x2, .LC1064
	mov	w0, 1
	ldr	x1, .LC1066
	add	x2, x2, 480
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3659
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	3
.LC1063:
	.xword	s_pstVfmwChan
	.align	3
.LC1064:
	.xword	.LANCHOR5
	.align	3
.LC1066:
	.xword	.LC1065
	.align	3
.LC1068:
	.xword	.LC1067
	.align	3
.LC1070:
	.xword	.LC1069
	.align	3
.LC1072:
	.xword	.LC1071
	.align	3
.LC1074:
	.xword	.LC1073
	.align	3
.LC1076:
	.xword	.LC1075
	.align	3
.LC1077:
	.xword	g_event_report
	.align	3
.LC1079:
	.xword	.LC1078
	.align	3
.LC1081:
	.xword	.LC1080
	.align	3
.LC1083:
	.xword	.LC1082
	.align	3
.LC1085:
	.xword	.LC1084
	.align	3
.LC1087:
	.xword	.LC1086
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, [x19, 2400]
	ldr	w0, [x3, 8]
	cbz	w0, .L3732
	ldr	w2, [x19, 244]
	mov	w0, 0
	.p2align 2
.L3731:
	uxtw	x1, w0
	add	w0, w0, 1
	add	x1, x3, x1, lsl 5
	ldr	w1, [x1, 48]
	add	w2, w2, w1
	str	w2, [x19, 244]
	ldr	w1, [x3, 8]
	cmp	w1, w0
	bhi	.L3731
.L3732:
	strb	wzr, [x3]
	ldr	x0, [x19, 2400]
	ldr	w1, [x0, 16]
	sub	w1, w1, #36
	cmp	w1, 1
	bls	.L3875
.L3730:
	ldr	w1, [x0, 4]
	add	w1, w1, 16
	str	w1, [x0, 4]
	ldr	x1, [x19, 2400]
	ldr	w2, [x1, 16]
	cmp	w2, 49
	bls	.L3876
.L3733:
	ldr	x1, .LC1099
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	ldr	w0, [x1, 16]
	cmp	w0, 63
	bhi	.L3760
	cbnz	x1, .L3862
	.p2align 2
.L3860:
	mov	w0, 0
.L3879:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3876:
	ldr	x0, .LC1088
	ldrb	w0, [x0,w2,uxtw]
	adr	x3, .Lrtx3735
	add	x0, x3, w0, sxtb #2
	br	x0
.Lrtx3735:
	.section	.rodata
	.align	0
	.align	2
.L3735:
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3734 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3736 - .Lrtx3735) / 4
	.byte	(.L3737 - .Lrtx3735) / 4
	.byte	(.L3738 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3739 - .Lrtx3735) / 4
	.byte	(.L3739 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3733 - .Lrtx3735) / 4
	.byte	(.L3740 - .Lrtx3735) / 4
	.byte	(.L3741 - .Lrtx3735) / 4
	.text
	.p2align 3
.L3875:
	mov	w1, 1
	strb	w1, [x19, 3]
	b	.L3730
.L3741:
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L3877
.L3757:
	ldr	x1, [x19, 2400]
	cbz	x1, .L3860
.L3862:
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	mov	w0, 0
.L3859:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3734:
	mov	x0, x19
	bl	HEVC_DecSlice
	cmn	w0, #2
	beq	.L3859
	cbz	w0, .L3860
	ldr	x1, [x19, 2400]
	cbz	x1, .L3873
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3873:
	ldr	x0, .LC1091
	ldr	x4, [x0]
	cbz	x4, .L3861
.L3863:
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3861:
	mov	w0, -1
.L3878:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3737:
	mov	x0, x19
	bl	HEVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 2400]
	cbz	x1, .L3747
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3747:
	cbz	w20, .L3860
	ldr	x1, .LC1093
	b	.L3870
.L3738:
	mov	x0, x19
	bl	HEVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 2400]
	cbz	x1, .L3749
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3749:
	cbz	w20, .L3860
	ldr	x1, .LC1095
	b	.L3870
.L3736:
	mov	x0, x19
	bl	HEVC_DecVPS
	mov	w20, w0
	ldr	x1, [x19, 2400]
	cbz	x1, .L3742
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3742:
	cbz	w20, .L3860
	ldr	x1, .LC1090
.L3870:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1091
	ldr	x4, [x21]
	cbz	x4, .L3861
	add	x2, x29, 64
	ldr	w0, [x19, 252]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L3861
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L3739:
	mov	x0, x19
	bl	HEVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 2400]
	cbz	x1, .L3750
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3750:
	cbz	w20, .L3860
	ldr	x1, .LC1097
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3873
.L3740:
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	beq	.L3755
	cbz	x1, .L3754
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3754:
	ldrb	w0, [x19, 3985]
	cbz	w0, .L3860
.L3755:
	add	x20, x19, 2752
	mov	w1, 32
	strb	wzr, [x19, 8]
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L3860
	ldr	x20, .LC1091
	ldr	x4, [x20]
	cbz	x4, .L3756
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3756:
	ldrb	w0, [x19, 3985]
	cbz	w0, .L3860
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L3860
.L3759:
	ldr	x4, [x20]
	cbnz	x4, .L3863
	mov	w0, -1
	b	.L3878
	.p2align 3
.L3760:
	ldr	x20, .LC1091
	ldr	x4, [x20]
	cbz	x4, .L3761
	ldr	w0, [x19, 252]
	mov	w1, 102
	mov	w3, 0
	mov	x2, 0
	blr	x4
	ldr	x1, [x19, 2400]
	cbz	x1, .L3762
.L3763:
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L3762:
	ldr	x4, [x20]
	cbz	x4, .L3860
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, 0
	b	.L3879
.L3761:
	cbnz	x1, .L3763
	mov	w0, 0
	b	.L3879
.L3877:
	ldr	x20, .LC1091
	strb	w0, [x19, 9]
	ldr	x4, [x20]
	cbz	x4, .L3758
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3758:
	ldrb	w0, [x19, 3985]
	cbz	w0, .L3757
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L3757
	ldr	x1, [x19, 2400]
	cbz	x1, .L3759
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	b	.L3759
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	3
.LC1088:
	.xword	.L3735
	.align	3
.LC1090:
	.xword	.LC1089
	.align	3
.LC1091:
	.xword	g_event_report
	.align	3
.LC1093:
	.xword	.LC1092
	.align	3
.LC1095:
	.xword	.LC1094
	.align	3
.LC1097:
	.xword	.LC1096
	.align	3
.LC1099:
	.xword	.LC1098
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x19, 1]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x21, x2
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	str	wzr, [x21]
	ldr	x3, .LC1100
	add	x0, x19, 4096
	str	wzr, [x22]
	mov	x2, 1356
	mov	w1, 0
	add	x0, x0, 592
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, [x19, 2400]
	mov	x0, x19
	ldr	w2, [x1, 16]
	str	w2, [x19, 4716]
	ldr	w2, [x1, 28]
	str	w2, [x19, 4712]
	ldr	w1, [x1, 24]
	str	w1, [x19, 4720]
	bl	HEVC_DecSliceSegmentHeader
	cbnz	w0, .L3898
	ldr	w1, [x19, 4724]
	mov	w3, 1888
	ldr	x0, [x19, 2384]
	mov	w20, 12660
	ldr	w23, [x19, 2332]
	ldr	x2, [x19, 2376]
	smaddl	x0, w1, w3, x0
	cmp	w23, 1
	ldr	w0, [x0, 32]
	smaddl	x20, w0, w20, x2
	beq	.L3899
	ldr	w0, [x19, 4840]
	cmp	w0, 1
	cset	w0, eq
	str	w0, [x22]
	ldr	x0, [x19, 2424]
	ldr	x1, [x19, 2456]
	ldr	w2, [x20, 184]
	ldp	w5, w3, [x0, 64]
	ldr	w0, [x0, 184]
	ldp	w6, w4, [x20, 64]
	cmp	w2, w0
	ldr	w0, [x1, 880]
	cset	w2, ne
	cmp	w0, 1
	beq	.L3900
.L3887:
	cmp	w6, w5
	cset	w0, ne
	cmp	w4, w3
	orr	w0, w2, w0
	cset	w1, ne
	orr	w0, w1, w0
	cbz	w0, .L3890
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21]
.L3883:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3899:
	ldr	x0, [x19, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	ldp	w2, w1, [x20, 188]
	ldr	w3, [x19, 204]
	mul	w1, w1, w2
	add	w3, w3, 1
	udiv	w3, w1, w3
	ccmp	w0, w3, 1, ge
	blt	.L3885
.L3890:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3898:
	ldr	x1, .LC1102
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1103
	ldr	x4, [x0]
	cbz	x4, .L3891
	add	x2, x29, 80
	ldr	w0, [x19, 252]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3900:
	ldr	w7, [x20, 96]
	ldr	w0, [x20, 88]
	cmp	w0, w7
	csel	w0, w0, w7, cs
	str	w0, [x1, 940]
	ldr	x0, [x19, 2424]
	ldr	x7, [x19, 2456]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	ldr	w1, [x7, 940]
	cmp	w0, 8
	ccmp	w1, 8, 0, hi
	bne	.L3901
.L3888:
	mov	w0, 1
	str	w0, [x7, 944]
	str	w0, [x21]
	b	.L3887
	.p2align 3
.L3891:
	mov	w0, -1
	b	.L3883
	.p2align 3
.L3901:
	cmp	w0, 8
	ccmp	w1, 8, 4, eq
	ble	.L3887
	b	.L3888
.L3885:
	ldr	x1, .LC1105
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3883
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	3
.LC1100:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1102:
	.xword	.LC1101
	.align	3
.LC1103:
	.xword	g_event_report
	.align	3
.LC1105:
	.xword	.LC1104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w0, [x19, 204]
	cbnz	w0, .L3903
	ldrb	w0, [x19, 3985]
	mov	w20, -1
	cbnz	w0, .L3907
.L3903:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3907:
	ldr	x2, .LC1106
	mov	w0, 0
	ldr	x1, .LC1108
	add	x2, x2, 496
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	3
.LC1106:
	.xword	.LANCHOR5
	.align	3
.LC1108:
	.xword	.LC1107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19, 9152]
	mov	w0, 0
	cbz	x2, .L3909
	.p2align 2
.L3910:
	ldp	w3, w1, [x2]
	ldr	x2, [x2, 1360]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L3910
.L3909:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFrameEndNal
	.type	HEVC_IsFrameEndNal, %function
HEVC_IsFrameEndNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sub	w0, w19, #32
	sub	w19, w19, #48
	cmp	w0, 2
	ccmp	w19, 1, 0, hi
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFrameEndNal, .-HEVC_IsFrameEndNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_CheckSedOnly
	.type	HEVCDEC_CheckSedOnly, %function
HEVCDEC_CheckSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2328]
	str	wzr, [x19, 2332]
	cmp	w0, 2
	str	wzr, [x19, 2340]
	beq	.L3944
	cmp	w0, 1
	mov	w0, 0
	beq	.L3945
.L3936:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3945:
	ldr	w1, [x19, 2336]
	cmp	w1, 1
	bne	.L3936
	str	wzr, [x19, 2336]
	.p2align 2
.L3942:
	mov	w0, -1
	b	.L3936
	.p2align 3
.L3944:
	ldr	w0, [x19, 2324]
	cbz	w0, .L3942
	ldr	w1, [x19, 2336]
	mov	w0, 0
	cmp	w1, 1
	beq	.L3936
	ldr	w0, [x19, 252]
	bl	VCTRL_CheckFreshSeg
	cbz	w0, .L3942
	ldr	w0, [x19, 252]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L3942
	ldr	x1, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2360]
	mov	w1, 24
	bl	BsSkip
	ldr	x0, [x19, 2360]
	bl	BsResidBits
	cmp	w0, 15
	ble	.L3942
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsSkip
	ldr	x0, [x19, 2360]
	mov	w1, 6
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2360]
	mov	w1, 9
	bl	BsSkip
	mov	w0, w20
	bl	HEVC_IsSliceUnit
	sxtb	w21, w0
	cmp	w21, 1
	beq	.L3946
	ldr	w0, [x19, 204]
	cbz	w0, .L3942
	sub	w0, w20, #32
	sub	w20, w20, #48
	cmp	w0, 2
	ccmp	w20, 1, 0, hi
	bhi	.L3942
.L3923:
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L3942
	mov	w1, 1
	mov	w0, -1
	strb	w1, [x19, 3984]
	str	w1, [x19, 2340]
	b	.L3936
	.p2align 3
.L3946:
	ldr	x0, [x19, 2360]
	bl	BsResidBits
	cmp	w0, wzr
	mov	w0, 0
	ble	.L3920
	ldr	x0, [x19, 2360]
	mov	w1, w21
	bl	BsGet
.L3920:
	ldr	w1, [x19, 204]
	cbnz	w1, .L3947
.L3921:
	ldrb	w0, [x19, 3985]
	mov	w1, 1
	str	w0, [x19, 2344]
	mov	w0, 0
	str	w1, [x19, 2332]
	str	wzr, [x19, 2336]
	b	.L3936
.L3947:
	sub	w1, w20, #32
	sub	w20, w20, #48
	cmp	w1, 2
	ccmp	w20, 1, 0, hi
	ccmp	w0, wzr, 0, hi
	beq	.L3921
	b	.L3923
	.size	HEVCDEC_CheckSedOnly, .-HEVCDEC_CheckSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_IsNeedSedOnly
	.type	HEVCDEC_IsNeedSedOnly, %function
HEVCDEC_IsNeedSedOnly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 204]
	cbz	w0, .L3951
	ldr	x1, [x19, 2472]
	cbz	x1, .L3956
.L3951:
	mov	w0, 0
.L3950:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3956:
	ldr	w1, [x19, 6680]
	cmp	w1, 1
	bls	.L3951
	ldr	w1, [x19, 2348]
	cmp	w0, w1
	beq	.L3951
	ldr	w0, [x19, 2332]
	cmp	w0, 1
	beq	.L3957
	cbnz	w0, .L3951
	ldr	w0, [x19, 252]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L3951
	ldr	w0, [x19, 252]
	bl	VCTRL_CheckFreshSeg
	cmp	w0, wzr
	cset	w0, ne
	b	.L3950
	.p2align 3
.L3957:
	ldr	x0, [x19, 2400]
	cmp	x0, xzr
	cset	w0, ne
	b	.L3950
	.size	HEVCDEC_IsNeedSedOnly, .-HEVCDEC_IsNeedSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_SetDecParam
	.type	HEVCDEC_SetDecParam, %function
HEVCDEC_SetDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19, 2336]
	cmp	w20, 1
	beq	.L3972
.L3959:
	mov	x0, x19
	bl	HEVCDEC_IsNeedSedOnly
	cmp	w0, 1
	beq	.L3973
	ldr	w0, [x19, 2332]
	cmp	w0, 1
	beq	.L3974
.L3958:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3974:
	ldr	w2, [x19, 176]
	ldr	w3, [x19, 204]
	ldr	w0, [x19, 236]
	sub	w2, w2, #1
	ldr	w4, [x19, 2344]
	sub	w3, w3, #1
	ldr	x1, [x19, 2400]
	sub	w0, w0, #1
	strb	w4, [x19, 3985]
	str	w2, [x19, 176]
	str	w3, [x19, 204]
	str	w0, [x19, 236]
	cbz	x1, .L3958
.L3971:
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3972:
	ldr	w0, [x19, 204]
	cbz	w0, .L3959
	ldr	x0, [x19, 2472]
	cbnz	x0, .L3959
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L3975
	ldr	x1, [x19, 2400]
	cbnz	x1, .L3971
	b	.L3958
	.p2align 3
.L3973:
	ldr	w1, [x19, 204]
	ldr	x2, [x19, 2456]
	str	w0, [x19, 11844]
	add	x0, x19, 4096
	str	w1, [x19, 2348]
	add	x0, x0, 2560
	str	w1, [x19, 9144]
	ldr	w1, [x2, 684]
	str	w1, [x19, 7984]
	str	wzr, [x19, 2336]
	str	x0, [x19, 2472]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L3975:
	strb	w20, [x19, 3984]
	str	w20, [x19, 2340]
	b	.L3958
	.size	HEVCDEC_SetDecParam, .-HEVCDEC_SetDecParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMProcSedOnly
	.type	HEVCDEC_VDMProcSedOnly, %function
HEVCDEC_VDMProcSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x3, w20
	ldr	x1, [x19, 2472]
	lsl	x0, x3, 2
	ldr	x20, .LC1110
	sub	x3, x0, x3
	ldr	x4, .LC1109
	lsl	x0, x3, 4
	ldrsw	x5, [x19, 252]
	ldp	w21, w2, [x1, 20]
	sub	x3, x0, x3
	ldr	x1, .LC1112
	mov	w0, 22
	ldr	x22, [x4, x5, lsl 3]
	add	x20, x20, x3, lsl 2
	madd	w21, w2, w21, w21
	ldr	w3, [x20, 20]
	add	w21, w21, w2
	mov	w2, w21
	bl	dprint_vfmw
	ldr	w0, [x20, 20]
	cmp	w21, w0
	ldr	w0, [x19, 2332]
	beq	.L3986
	cmp	w0, 1
	beq	.L3987
.L3981:
	str	xzr, [x19, 2472]
.L3979:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3987:
	ldr	w2, [x19, 176]
	ldr	w3, [x19, 204]
	ldr	w0, [x19, 236]
	sub	w2, w2, #1
	ldr	w4, [x19, 2344]
	sub	w3, w3, #1
	ldr	x1, [x19, 2400]
	sub	w0, w0, #1
	strb	w4, [x19, 3985]
	str	w2, [x19, 176]
	str	w3, [x19, 204]
	str	w0, [x19, 236]
	str	wzr, [x19, 2336]
	cbz	x1, .L3981
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	b	.L3981
	.p2align 3
.L3986:
	cmp	w0, 1
	beq	.L3978
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L3979
	mov	w0, 1
	strb	w0, [x19, 3984]
	str	w0, [x19, 2340]
	b	.L3979
	.p2align 3
.L3978:
	ldr	w2, [x19, 176]
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 236]
	sub	w2, w2, #1
	ldr	w4, [x19, 2344]
	sub	w3, w3, #1
	str	w0, [x19, 2336]
	sub	w1, w1, #1
	strb	w4, [x19, 3985]
	str	w2, [x19, 176]
	str	w3, [x19, 204]
	str	w1, [x19, 236]
	strb	w0, [x22, 745]
	strb	w0, [x19, 7]
	mov	w0, 0
	str	xzr, [x19, 2472]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	3
.LC1109:
	.xword	s_pstVfmwChan
	.align	3
.LC1110:
	.xword	g_BackUp
	.align	3
.LC1112:
	.xword	.LC1111
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x20, .LC1113
	mov	x2, 27712
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x19, 6648]
	ldr	x3, [x20, 96]
	blr	x3
	str	x21, [x19, 2456]
	str	xzr, [x19, 2472]
	str	w22, [x19, 6648]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L3997
	mov	w0, 17
	mov	w3, 65
	mov	w2, 200
	mov	w1, 210
	stp	w2, w0, [x19, 152]
	stp	w0, w3, [x19, 160]
	str	w1, [x19, 168]
.L3990:
	ldr	w0, [x21, 624]
	bl	MEM_Phy2Vir
	cbz	x0, .L3998
	ldr	x8, [x19, 2456]
	mov	w22, 12660
	ldr	w2, [x19, 156]
	ldpsw	x6, x5, [x19, 160]
	ldr	w7, [x8, 620]
	lsl	w4, w2, 7
	add	w4, w4, w2, lsl 2
	lsl	w1, w5, 4
	add	w4, w4, w7
	sub	w1, w1, w5
	ldr	w3, [x19, 168]
	lsl	w1, w1, 2
	madd	w6, w22, w6, w4
	sub	w5, w1, w5
	add	x4, x0, x4, uxtw
	add	w1, w3, 1
	str	x4, [x19, 2376]
	lsl	w4, w1, 3
	add	w5, w6, w5, lsl 5
	sub	w4, w4, w1
	add	x6, x0, x6, uxtw
	lsl	w4, w4, 1
	str	x6, [x19, 2384]
	ldrsw	x6, [x19, 152]
	sub	w1, w4, w1
	mov	w4, 1368
	add	x7, x0, x7, uxtw
	str	x7, [x19, 2368]
	sxtw	x2, w2
	madd	w4, w4, w6, w5
	add	x5, x0, x5, uxtw
	str	x5, [x19, 2464]
	add	w1, w4, w1, lsl 3
	add	x4, x0, x4, uxtw
	str	x4, [x19, 2448]
	add	x4, x0, x1, uxtw
	str	x4, [x19, 2440]
	add	w3, w1, w3, lsl 3
	ldr	w4, [x8, 628]
	cmp	w3, w4
	bhi	.L3999
	ldr	w0, [x21, 656]
	cbz	w0, .L4000
.L3994:
	lsl	x2, x6, 2
	ldr	x3, [x20, 96]
	sub	x2, x2, x6
	mov	x0, x5
	lsl	x2, x2, 2
	mov	w1, 0
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	lsl	x2, x2, 3
	blr	x3
	ldr	w2, [x19, 168]
	mov	w4, 104
	ldr	x3, [x20, 96]
	mov	w1, 0
	add	w2, w2, 1
	ldr	x0, [x19, 2448]
	smull	x2, w2, w4
	blr	x3
	ldrsw	x2, [x19, 168]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2440]
	lsl	x2, x2, 3
	blr	x3
	ldp	w5, w4, [x19, 156]
	mov	x1, -132
	mov	w0, 132
	ldr	w2, [x19, 164]
	mov	w8, 1888
	ldr	x9, [x19, 2368]
	mov	x7, -1888
	smaddl	x0, w5, w0, x1
	mov	w3, 12660
	mov	x1, -12660
	ldr	x6, [x19, 2384]
	smaddl	x3, w4, w3, x1
	ldr	x4, [x19, 2376]
	add	x1, x9, x0
	smaddl	x0, w2, w8, x7
	str	x1, [x19, 2416]
	add	x2, x4, x3
	add	x0, x6, x0
	str	x2, [x19, 2424]
	str	x0, [x19, 2432]
	mov	x0, x19
	str	w5, [x1, 4]
	ldr	x1, [x19, 2432]
	ldr	w2, [x19, 160]
	str	w2, [x1, 28]
	ldr	x1, [x19, 2424]
	ldr	w2, [x19, 164]
	str	w2, [x1, 56]
	bl	HEVC_InitScalingOrderTable
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 252]
	beq	.L4001
	mov	w1, -2147483647
	mov	x0, x19
	str	w1, [x19, 212]
	bl	HEVC_InitDecPara
	str	wzr, [x19, 2352]
	ldr	w0, [x19, 164]
	mov	w2, 9999
	ldr	x1, [x19, 2456]
	str	w0, [x19, 296]
	mov	w0, 1
	str	w2, [x19, 260]
	strb	w0, [x19]
	mov	w0, 0
	str	wzr, [x19, 11912]
	ldr	w1, [x1, 672]
	str	w1, [x19, 2324]
.L3996:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4000:
	lsl	x0, x2, 7
	ldr	x3, [x20, 96]
	add	x2, x0, x2, lsl 2
	mov	w1, 0
	mov	x0, x7
	blr	x3
	ldr	w2, [x19, 160]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2376]
	smull	x2, w2, w22
	blr	x3
	ldr	w4, [x19, 164]
	mov	w2, 1888
	ldr	x0, [x19, 2384]
	mov	w1, 0
	ldr	x3, [x20, 96]
	smull	x2, w4, w2
	blr	x3
	ldrsw	x6, [x19, 152]
	ldr	x5, [x19, 2464]
	b	.L3994
	.p2align 3
.L3997:
	ldr	w0, [x21, 736]
	str	w0, [x19, 156]
	ldr	w0, [x21, 740]
	str	w0, [x19, 160]
	ldr	w0, [x21, 744]
	str	w0, [x19, 164]
	ldr	w0, [x21, 732]
	str	w0, [x19, 152]
	add	w0, w0, 5
	str	w0, [x19, 168]
	b	.L3990
.L3999:
	ldr	x2, .LC1114
	mov	w0, 0
	ldr	x1, .LC1118
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3996
.L4001:
	ldr	x2, .LC1114
	mov	w0, 0
	ldr	x1, .LC1120
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3996
.L3998:
	ldr	x2, .LC1114
	ldr	x1, .LC1116
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3996
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	3
.LC1113:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1114:
	.xword	.LANCHOR5
	.align	3
.LC1116:
	.xword	.LC1115
	.align	3
.LC1118:
	.xword	.LC1117
	.align	3
.LC1120:
	.xword	.LC1119
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 180]
	cbz	w0, .L4005
	ldrb	w0, [x19, 3985]
	cmp	w0, 1
	beq	.L4005
	add	x1, x19, 12288
	add	x4, x19, 24576
	add	x1, x1, 1184
	add	x4, x4, 3136
	.p2align 2
.L4011:
	ldr	w0, [x1, 48]
	cbnz	w0, .L4006
	cbz	x1, .L4007
	ldr	w3, [x19, 2796]
	cbz	w3, .L4007
	ldr	x0, [x19, 2816]
	cmp	x0, x1
	beq	.L4006
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L4008
	.p2align 3
.L4009:
	ldr	x2, [x0, 2816]
	cmp	x2, x1
	beq	.L4006
.L4008:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L4009
.L4007:
	ldr	w0, [x19, 252]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L4005
	cmn	w0, #1
	beq	.L4030
.L4029:
	mov	w0, 0
.L4031:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4005:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4006:
	add	x1, x1, 712
	cmp	x1, x4
	bne	.L4011
	add	x0, x19, 4096
	add	x2, x29, 44
	add	x1, x29, 40
	add	x0, x0, 1952
	bl	GetQueueImgNum
	mov	x0, x19
	bl	HEVC_PrintFrameStoreState
	ldr	x1, .LC1124
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	w0, [x19, 180]
	ldr	w2, [x19, 2796]
	ldp	w3, w4, [x29, 40]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w4
	cmp	w1, w0
	bge	.L4029
	ldr	x2, .LC1125
	mov	w0, 0
	ldr	x1, .LC1127
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	ret
.L4030:
	ldr	x1, .LC1122
	mov	w0, 1
	bl	dprint_vfmw
	add	x1, x19, 4096
	ldr	w0, [x19, 252]
	add	x1, x1, 1952
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L4031
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	3
.LC1122:
	.xword	.LC1121
	.align	3
.LC1124:
	.xword	.LC1123
	.align	3
.LC1125:
	.xword	.LANCHOR5
	.align	3
.LC1127:
	.xword	.LC1126
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 100]
	stp	wzr, wzr, [x29, 92]
	cbz	x20, .L4108
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L4109
	ldr	x2, [x19, 2456]
	ldrb	w0, [x19, 7]
	cmp	w0, 1
	ldr	w0, [x2, 8]
	ubfiz	w0, w0, 16, 3
	str	w0, [x19, 248]
	beq	.L4036
	ldr	w0, [x2, 880]
	cmp	w0, 1
	beq	.L4110
.L4037:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_ReceivePacket
	mov	w20, w0
	ldr	x0, [x19, 2400]
	str	x0, [x19, 2408]
.L4038:
	strb	wzr, [x19, 7]
	cbz	w20, .L4039
.L4062:
	mov	w20, 0
.L4104:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4039:
	mov	x0, x19
	bl	HEVCDEC_CheckSedOnly
	mov	w20, w0
	cbz	w0, .L4111
.L4106:
	ldr	x1, [x19, 2400]
	cbz	x1, .L4044
	ldr	w0, [x19, 252]
	mov	w20, -1
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4110:
	ldr	w0, [x2, 928]
	cmp	w0, 1
	bne	.L4037
	ldr	w0, [x19, 320]
	cmp	w0, 1
	bne	.L4037
	ldr	x0, [x19, 2408]
	mov	w20, 0
	strb	wzr, [x19, 7]
	str	wzr, [x19, 320]
	str	x0, [x19, 2400]
	b	.L4104
	.p2align 3
.L4036:
	ldr	x0, [x19, 2400]
	cmp	x0, xzr
	csetm	w20, eq
	cbz	w20, .L4038
	ldr	x1, .LC1133
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4104
	.p2align 3
.L4111:
	ldr	x0, [x19, 2400]
	str	wzr, [x0, 4]
	ldr	x1, [x19, 2400]
	ldr	x0, [x19, 2360]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2360]
	mov	w1, 24
	bl	BsSkip
	ldr	x24, .LC1134
	ldrsw	x0, [x19, 252]
	ldr	x0, [x24, x0, lsl 3]
	ldrsb	w21, [x0, 44]
	cmp	w21, 1
	beq	.L4112
	mov	w23, 2
	mov	w22, 0
	mov	w25, w23
.L4042:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x21, [x19, 2400]
	ldr	x0, [x19, 2360]
	mov	w1, 6
	bl	BsGet
	str	w0, [x21, 16]
	mov	w1, 6
	ldr	x21, [x19, 2400]
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x21, 24]
	ldr	x21, [x19, 2400]
	ldr	w2, [x21, 24]
	cbnz	w2, .L4113
	ldr	x0, [x19, 2360]
	mov	w1, 3
	bl	BsGet
	str	w0, [x21, 28]
	ldr	x21, [x19, 2400]
	ldr	w0, [x21, 28]
	cbz	w0, .L4045
	sub	w0, w0, #1
	str	w0, [x21, 28]
	ldr	x21, [x19, 2400]
.L4045:
	ldr	w0, [x21, 16]
	bl	HEVC_IsSliceUnit
	sxtb	w26, w0
	cmp	w26, 1
	beq	.L4114
	str	wzr, [x21, 4]
	add	x0, x19, 2752
	ldr	x1, [x19, 2400]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2360]
	mov	w1, 24
	bl	BsSkip
	cmp	w25, 1
	ccmp	w23, wzr, 0, eq
	ccmp	w22, 1, 4, eq
	beq	.L4060
	ldr	x0, [x19, 2360]
	mov	w1, 16
	bl	BsSkip
.L4060:
	ldr	x0, [x19, 2360]
	mov	w1, 1
	bl	BsGet
	ldr	x21, [x19, 2400]
	ldr	x0, [x19, 2360]
	mov	w1, 6
	bl	BsGet
	str	w0, [x21, 16]
	mov	w1, 6
	ldr	x21, [x19, 2400]
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x21, 24]
	mov	w1, 3
	ldr	x21, [x19, 2400]
	ldr	x0, [x19, 2360]
	bl	BsGet
	str	w0, [x21, 28]
	ldr	x1, [x19, 2400]
	ldr	w0, [x1, 28]
	cbz	w0, .L4050
	sub	w0, w0, #1
	str	w0, [x1, 28]
.L4050:
	mov	x0, x19
	bl	HEVC_DecOneNal
	cmn	w0, #2
	beq	.L4067
	cbnz	w0, .L4115
	ldr	w0, [x19, 2324]
	str	wzr, [x19, 4040]
	cmp	w0, 1
	bne	.L4062
	mov	x0, x19
	bl	HEVCDEC_SetDecParam
	b	.L4104
	.p2align 3
.L4044:
	mov	w20, -1
	b	.L4104
	.p2align 3
.L4114:
	add	x2, x29, 108
	add	x1, x29, 104
	mov	x0, x19
	bl	HEVC_InquireSliceProperty
	cbnz	w0, .L4047
	ldr	w21, [x29, 104]
	cmp	w21, 1
	beq	.L4116
.L4048:
	ldr	w21, [x29, 108]
	cmp	w21, 1
	bne	.L4050
	ldr	x0, [x19, 2400]
	ldr	w0, [x0, 24]
	add	x0, x19, x0
	ldrb	w22, [x0, 4]
	mov	x0, x19
	cmp	w22, 1
	beq	.L4117
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L4118
.L4053:
	ldr	w0, [x19, 252]
	bl	FSP_GetFspType
	cbnz	w0, .L4050
	ldr	w0, [x19, 252]
	add	x3, x29, 100
	add	x2, x29, 96
	add	x1, x29, 92
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 2456]
	ldr	w0, [x0, 764]
	cmp	w0, 1
	bne	.L4050
	ldr	w1, [x29, 100]
	cmp	w1, wzr
	bgt	.L4056
	ldr	w2, [x29, 96]
	cmp	w2, 32
	bgt	.L4056
	ldr	x2, [x19, 2472]
	cbnz	x2, .L4056
	ldr	w2, [x29, 108]
	cbz	w2, .L4050
	ldr	w3, [x19, 240]
	cbz	w3, .L4050
	ldr	x3, [x19, 2424]
	ldr	w4, [x19, 312]
	ldr	w6, [x3, 68]
	cmp	w6, w4
	beq	.L4050
	ldr	w5, [x3, 64]
	cmp	w1, wzr
	ldr	w3, [x19, 316]
	ccmp	w5, w3, 4, eq
	beq	.L4050
	ldr	x1, .LC1142
	bl	dprint_vfmw
	ldr	x0, [x19, 2424]
	ldr	x1, .LC1143
	ldr	w2, [x0, 68]
	str	w2, [x19, 312]
	ldr	x4, [x1]
	ldr	w0, [x0, 64]
	str	w0, [x19, 316]
	cbz	x4, .L4050
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L4050
	.p2align 3
.L4109:
	ldr	x1, .LC1131
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L4104
	.p2align 3
.L4112:
	ldp	w25, w23, [x0, 152]
	ldr	w3, [x0, 160]
	mov	x0, x19
	mov	w2, w23
	mov	w1, w25
	bl	HEVC_VES_Splitter
	cmp	w0, 2
	beq	.L4065
	cmp	w0, 1
	mov	w22, 0
	beq	.L4042
.L4067:
	mov	w20, w0
	b	.L4104
	.p2align 3
.L4113:
	ldr	x1, .LC1136
	mov	w3, 0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4106
.L4065:
	mov	w22, w21
	b	.L4042
.L4047:
	ldr	x1, .LC1145
	mov	w0, w26
	bl	dprint_vfmw
	ldr	x1, [x19, 2400]
	cbz	x1, .L4058
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2400]
.L4058:
	ldr	x0, .LC1143
	ldr	x4, [x0]
	cbz	x4, .L4059
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4059:
	ldrsw	x0, [x19, 252]
	ldr	x0, [x24, x0, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	bne	.L4044
	ldr	w1, [x0, 156]
	cbnz	w1, .L4044
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L4044
	add	x0, x19, 8192
	ldrb	w1, [x0, 3664]
	cbnz	w1, .L4044
	ldr	x3, .LC1146
	mov	x2, 56
	add	x0, x0, 3664
	mov	w20, -1
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 3364]
	add	x0, x19, 3072
	stp	xzr, xzr, [x0, 312]
	stp	xzr, xzr, [x0, 328]
	b	.L4104
.L4108:
	ldr	x1, .LC1129
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L4104
.L4116:
	ldr	w1, [x19, 204]
	cbnz	w1, .L4049
	ldrb	w1, [x19, 3985]
	cbz	w1, .L4048
	ldr	x2, .LC1137
	ldr	x1, .LC1138
	add	x2, x2, 496
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L4048
.L4049:
	ldr	x3, [x19, 2400]
	mov	w2, 13
	ldr	x1, .LC1137
	add	x0, x19, 2752
	mov	w20, -2
	str	wzr, [x3, 4]
	add	x1, x1, 584
	bl	BsInit
	ldr	x0, [x19, 2360]
	mov	w1, 40
	bl	BsSkip
	ldr	x1, [x19, 2400]
	mov	w2, 48
	mov	x0, x19
	str	w2, [x1, 16]
	strb	w21, [x19, 8]
	bl	HEVC_DecOneNal
	strb	w21, [x19, 7]
	ldr	w0, [x19, 280]
	add	w0, w0, 1
	str	w0, [x19, 280]
	b	.L4104
.L4115:
	ldr	x1, .LC1148
	mov	w0, 22
	mov	w20, -1
	bl	dprint_vfmw
	b	.L4104
.L4117:
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L4053
	ldr	x2, .LC1137
	mov	w0, w22
	ldr	x1, .LC1139
	add	x2, x2, 560
	bl	dprint_vfmw
	b	.L4053
.L4118:
	ldr	x2, .LC1137
	mov	w0, w21
	ldr	x1, .LC1140
	add	x2, x2, 560
	bl	dprint_vfmw
	b	.L4053
.L4056:
	mov	w0, 1
	mov	w20, -2
	strb	w0, [x19, 7]
	b	.L4104
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	3
.LC1129:
	.xword	.LC1128
	.align	3
.LC1131:
	.xword	.LC1130
	.align	3
.LC1133:
	.xword	.LC1132
	.align	3
.LC1134:
	.xword	s_pstVfmwChan
	.align	3
.LC1136:
	.xword	.LC1135
	.align	3
.LC1137:
	.xword	.LANCHOR5
	.align	3
.LC1138:
	.xword	.LC1107
	.align	3
.LC1139:
	.xword	.LC1067
	.align	3
.LC1140:
	.xword	.LC1065
	.align	3
.LC1142:
	.xword	.LC1141
	.align	3
.LC1143:
	.xword	g_event_report
	.align	3
.LC1145:
	.xword	.LC1144
	.align	3
.LC1146:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1148:
	.xword	.LC1147
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w24, w1
	mov	x22, x3
	mov	w23, w4
	mov	w20, w5
	bl	_mcount
	ldr	x0, [x19, 2456]
	ldr	x2, [x19, 4048]
	ldr	w21, [x0, 676]
	str	w24, [x19, 4024]
	cbz	x2, .L4120
	add	x0, x19, 4096
	ldrb	w1, [x0, 2565]
	strb	w1, [x2, 3]
	ldrb	w0, [x0, 2560]
	strb	w0, [x2, 4]
	ldr	x0, [x19, 2456]
.L4120:
	ldr	w1, [x19, 2352]
	cmp	w1, 1
	bls	.L4121
.L4124:
	ldr	w1, [x19, 4004]
	cmp	w1, 1920
	bls	.L4122
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L4122
	str	wzr, [x19, 2324]
	cbz	w23, .L4127
.L4157:
	ldr	x5, .LC1149
	sbfiz	x20, x20, 6, 32
	add	x20, x5, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L4154
	cmp	w0, 1
	beq	.L4127
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbnz	w0, .L4155
.L4131:
	cmp	w21, 1
	beq	.L4156
.L4132:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x19, 172]
.L4129:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4121:
	add	w1, w1, 1
	str	w1, [x19, 2352]
	cmp	w1, 1
	bhi	.L4124
.L4122:
	ldr	w0, [x0, 672]
	str	w0, [x19, 2324]
	cbnz	w23, .L4157
.L4127:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbz	w0, .L4131
.L4155:
	ldr	x1, .LC1151
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4156:
	ldr	x22, [x19, 2472]
	ldr	w0, [x22, 1292]
	add	x0, x22, x0, lsl 2
	ldr	w23, [x0, 1476]
	mov	w0, w23
	bl	MEM_Phy2Vir
	mov	x20, x0
	ldr	w2, [x22, 76]
	ldp	w3, w5, [x22, 192]
	lsl	w21, w21, w2
	ldr	x1, .LC1152
	sub	w3, w3, #1
	sub	w5, w5, #1
	add	w5, w5, w21
	add	w21, w3, w21
	lsr	w5, w5, w2
	lsr	w21, w21, w2
	ldr	x3, [x1, 280]
	mov	w1, w23
	mul	w21, w5, w21
	lsl	w2, w21, 4
	blr	x3
	cbz	w21, .L4143
	mov	w5, 0
	mov	w8, 0
	mov	w7, 2147483647
	mov	w4, 0
	mov	w2, 0
	b	.L4140
	.p2align 3
.L4159:
	csel	w7, w7, w0, le
.L4139:
	add	w2, w2, 1
	add	w5, w5, w0
	cmp	w21, w2
	beq	.L4158
.L4140:
	ubfiz	x1, x2, 4, 28
	add	x1, x20, x1
	ldrsh	w3, [x1, 4]
	neg	w0, w3
	and	w6, w3, 32767
	tbz	x3, 15, .L4135
	and	w6, w0, 32767
.L4135:
	ldrsh	w1, [x1, 6]
	neg	w3, w1
	and	w0, w1, 32767
	tbz	x1, 15, .L4137
	and	w0, w3, 32767
.L4137:
	add	w0, w6, w0
	cmp	w4, w0
	csel	w4, w4, w0, ge
	cmp	w7, w0
	cbnz	w0, .L4159
	add	w8, w8, 1
	b	.L4139
	.p2align 3
.L4154:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	w0, 0
	b	.L4129
	.p2align 3
.L4158:
	lsl	w0, w8, 2
	sub	w0, w0, w8
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w8, w0, w8
.L4133:
	udiv	w8, w8, w21
	ldr	x0, [x19, 4048]
	cmp	w8, 100
	csel	w7, w7, wzr, ne
	udiv	w5, w5, w21
	cbz	x0, .L4142
	str	w4, [x0, 324]
	ldr	x0, [x19, 4048]
	str	w7, [x0, 328]
	ldr	x0, [x19, 4048]
	str	w5, [x0, 332]
	ldr	x0, [x19, 4048]
	str	w8, [x0, 336]
	str	w4, [x19, 4300]
	str	w7, [x19, 4304]
	str	w5, [x19, 4308]
	str	w8, [x19, 4312]
	b	.L4132
.L4143:
	mov	w8, 0
	mov	w5, 0
	mov	w7, 2147483647
	mov	w4, 0
	b	.L4133
.L4142:
	ldr	x1, .LC1154
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4132
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	3
.LC1149:
	.xword	g_VdmDrvParam
	.align	3
.LC1151:
	.xword	.LC1150
	.align	3
.LC1152:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1154:
	.xword	.LC1153
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2424]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w2, [x0, 132]
	ldr	w0, [x0, 64]
	add	w1, w2, w0
	neg	w2, w2
	sub	w0, w1, #1
	and	w0, w0, w2
	ret
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2424]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w2, [x0, 132]
	ldr	w0, [x0, 68]
	add	w1, w2, w0
	neg	w2, w2
	sub	w0, w1, #1
	and	w0, w0, w2
	ret
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2796]
	cbz	w0, .L4167
	ldr	x0, .LC1155
	mov	w21, 1
	ldr	x23, .LC1156
	add	x22, x0, 600
	.p2align 2
.L4163:
	add	x2, x29, 72
	add	x1, x29, 76
	mov	x0, x19
	bl	HEVC_GetMinPOC
	ldr	w2, [x29, 72]
	mov	x0, x19
	add	x1, x19, x2, uxtw 3
	ldr	x20, [x1, 2816]
	mov	x1, x20
	cbz	x20, .L4164
	ldrb	w3, [x20, 2]
	cmp	w3, 1
	beq	.L4164
	strb	w21, [x20, 2]
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L4178
.L4177:
	ldr	w2, [x29, 72]
.L4164:
	mov	w1, w2
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	ldr	w1, [x29, 72]
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w0, [x19, 2796]
	cbnz	w0, .L4163
.L4167:
	add	x0, x19, 4096
	add	x0, x0, 1952
	bl	GetVoLastImageID
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4178:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	cbz	w0, .L4177
	mov	x1, x23
	mov	x2, x22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	b	.L4177
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	3
.LC1155:
	.xword	.LANCHOR5
	.align	3
.LC1156:
	.xword	.LC923
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	s_TmpParam
	.global	g_RpuStartCode
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.12868, %object
	.size	__func__.12868, 17
__func__.12868:
	.string	"HEVC_OutputFrame"
	.zero	7
	.type	SarTable.11537, %object
	.size	SarTable.11537, 136
SarTable.11537:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.11695, %object
	.size	__func__.11695, 18
__func__.11695:
	.string	"HEVC_CalcTileInfo"
	.zero	6
	.type	__func__.12175, %object
	.size	__func__.12175, 27
__func__.12175:
	.string	"HEVC_GetUnRefPicWithMinPoc"
	.zero	5
	.type	__func__.12184, %object
	.size	__func__.12184, 21
__func__.12184:
	.string	"HEVC_IncreaseDPBSize"
	.zero	3
	.type	__func__.12436, %object
	.size	__func__.12436, 17
__func__.12436:
	.string	"HEVC_WritePicMsg"
	.zero	7
	.type	__func__.12465, %object
	.size	__func__.12465, 16
__func__.12465:
	.string	"HEVC_CheckListX"
	.type	__func__.12629, %object
	.size	__func__.12629, 16
__func__.12629:
	.string	"HEVC_RepairList"
	.type	__func__.12696, %object
	.size	__func__.12696, 16
__func__.12696:
	.string	"HEVC_ArrangeMem"
	.type	__func__.12769, %object
	.size	__func__.12769, 20
__func__.12769:
	.string	"HEVC_RemoveApcStore"
	.zero	4
	.type	__func__.13038, %object
	.size	__func__.13038, 21
__func__.13038:
	.string	"HEVC_CheckFrameStore"
	.zero	3
	.type	__func__.13106, %object
	.size	__func__.13106, 19
__func__.13106:
	.string	"HEVC_GetSLHDR1Info"
	.zero	5
	.type	__func__.13233, %object
	.size	__func__.13233, 14
__func__.13233:
	.string	"HEVC_IsNewPic"
	.zero	2
	.type	g_Quant8InterDefault, %object
	.size	g_Quant8InterDefault, 64
g_Quant8InterDefault:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	g_QuantTsDefault, %object
	.size	g_QuantTsDefault, 16
g_QuantTsDefault:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.align	3
.LANCHOR5 = . + 0
	.type	__func__.13548, %object
	.size	__func__.13548, 16
__func__.13548:
	.string	"HEVC_ReleaseNAL"
	.type	__func__.12728, %object
	.size	__func__.12728, 20
__func__.12728:
	.string	"HEVC_InitDecBuffers"
	.zero	4
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.12289, %object
	.size	__func__.12289, 27
__func__.12289:
	.string	"HEVC_DecSliceSegmentHeader"
	.zero	5
	.type	__func__.12707, %object
	.size	__func__.12707, 13
__func__.12707:
	.string	"HEVC_InitDPB"
	.zero	3
	.type	__func__.12875, %object
	.size	__func__.12875, 19
__func__.12875:
	.string	"HEVC_OutputCurrPic"
	.zero	5
	.type	__func__.12880, %object
	.size	__func__.12880, 23
__func__.12880:
	.string	"HEVC_FirstFrameFastOut"
	.zero	1
	.type	__func__.13030, %object
	.size	__func__.13030, 19
__func__.13030:
	.string	"HEVC_OutputFrmToVO"
	.zero	5
	.type	__func__.12992, %object
	.size	__func__.12992, 22
__func__.12992:
	.string	"HEVC_OutputFrmFromDPB"
	.zero	2
	.type	__func__.12190, %object
	.size	__func__.12190, 30
__func__.12190:
	.string	"HEVC_OutputUnRefPicWithMinPoc"
	.zero	2
	.type	__func__.13005, %object
	.size	__func__.13005, 27
__func__.13005:
	.string	"HEVC_FlushOutputFrmFromDPB"
	.zero	5
	.type	__func__.13611, %object
	.size	__func__.13611, 14
__func__.13611:
	.string	"HEVC_ClearDPB"
	.zero	2
	.type	__func__.12195, %object
	.size	__func__.12195, 23
__func__.12195:
	.string	"HEVC_RecoverDPBProcess"
	.zero	1
	.type	__func__.12966, %object
	.size	__func__.12966, 20
__func__.12966:
	.string	"HEVC_InsertFrmInDPB"
	.zero	4
	.type	__func__.12885, %object
	.size	__func__.12885, 22
__func__.12885:
	.string	"HEVC_SimpleDPBProcess"
	.zero	2
	.type	__func__.12890, %object
	.size	__func__.12890, 21
__func__.12890:
	.string	"HEVC_DecOrderProcess"
	.zero	3
	.type	__func__.12895, %object
	.size	__func__.12895, 22
__func__.12895:
	.string	"HEVC_DispOrderProcess"
	.zero	2
	.type	__func__.12909, %object
	.size	__func__.12909, 19
__func__.12909:
	.string	"HEVC_StorePicInDPB"
	.zero	5
	.type	__func__.12551, %object
	.size	__func__.12551, 12
__func__.12551:
	.string	"HEVC_DecVDM"
	.zero	4
	.type	__func__.11425, %object
	.size	__func__.11425, 18
__func__.11425:
	.string	"HEVC_VES_Splitter"
	.zero	6
	.type	__func__.12226, %object
	.size	__func__.12226, 14
__func__.12226:
	.string	"HEVC_DecSlice"
	.zero	2
	.type	__func__.13693, %object
	.size	__func__.13693, 20
__func__.13693:
	.string	"HEVC_HaveSliceToDec"
	.zero	4
	.type	__func__.13739, %object
	.size	__func__.13739, 13
__func__.13739:
	.string	"HEVCDEC_Init"
	.zero	3
	.type	__func__.13753, %object
	.size	__func__.13753, 23
__func__.13753:
	.string	"HEVCDEC_GetImageBuffer"
	.zero	1
	.type	__func__.13768, %object
	.size	__func__.13768, 21
__func__.13768:
	.string	"HEVCDEC_DecodePacket"
	.zero	3
	.type	g_HevcNalTypeEOP, %object
	.size	g_HevcNalTypeEOP, 13
g_HevcNalTypeEOP:
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
	.zero	3
	.type	__func__.13817, %object
	.size	__func__.13817, 21
__func__.13817:
	.string	"HEVCDEC_GetRemainImg"
	.data
	.align	3
.LANCHOR4 = . + 0
	.type	g_Quant8IntraDefault, %object
	.size	g_Quant8IntraDefault, 64
g_Quant8IntraDefault:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_QuantTSDefault4x4, %object
	.size	g_QuantTSDefault4x4, 16
g_QuantTSDefault4x4:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	g_QuantInterDefault8x8, %object
	.size	g_QuantInterDefault8x8, 64
g_QuantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_QuantIntraDefault8x8, %object
	.size	g_QuantIntraDefault8x8, 64
g_QuantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.type	g_RpuStartCode, %object
	.size	g_RpuStartCode, 5
g_RpuStartCode:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	25
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"%s: pImg is NULL!\n" )
	.zero	5
.LC3:
	ASCII(.string	"%s: InsertImgToVoQueue failed!\n" )
.LC14:
	ASCII(.string	"dar=%d\n" )
.LC17:
	ASCII(.string	"--------------- PrintNaluArraySlot START ---------------\n" )
	.zero	6
.LC19:
	ASCII(.string	"\n" )
	.zero	6
.LC21:
	ASCII(.string	"--------------- PrintNaluArraySlot END ---------------\n" )
.LC23:
	ASCII(.string	"NalArray[%d]=%p,is_valid=%d   " )
	.zero	1
.LC25:
	ASCII(.string	"--------------- PrintCurrSlicelistX START ---------------\n" )
	.zero	5
.LC27:
	ASCII(.string	"List0, size: %d\n" )
	.zero	7
.LC29:
	ASCII(.string	"List1, size: %d\n" )
	.zero	7
.LC31:
	ASCII(.string	"pListX[0][%d]:%p " )
	.zero	6
.LC33:
	ASCII(.string	"pFrameStore:%p " )
.LC35:
	ASCII(.string	"pLogicFs:%p " )
	.zero	3
.LC38:
	ASCII(.string	"--------------- PrintCurrSlicelistX END ---------------\n" )
	.zero	7
.LC40:
	ASCII(.string	"pListX[1][%d]: %p" )
	.zero	6
.LC44:
	ASCII(.string	"--------------- PrintFrameStoreState START ---------------\n" )
	.zero	4
.LC46:
	ASCII(.string	"--------------- PrintFrameStoreState END ---------------\n" )
	.zero	6
.LC48:
	ASCII(.string	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displayed=%d " )
	.zero	5
.LC50:
	ASCII(.string	"p_usrdat[%d]=%p " )
	.zero	7
.LC53:
	ASCII(.string	"--------------- PrintAPCState START ---------------\n" )
	.zero	3
.LC55:
	ASCII(.string	"Layer %d: APC.used_size:%d, APC.size:%d\n" )
	.zero	7
.LC57:
	ASCII(.string	"%d: is_used=%d, idc=%d, poc=%d\n" )
.LC59:
	ASCII(.string	"--------------- PrintAPCState END ---------------\n" )
	.zero	5
.LC61:
	ASCII(.string	"--------------- PrintDPBState START ---------------\n" )
	.zero	3
.LC63:
	ASCII(.string	"DPB: size:%d, used_size:%d, negative:%d, positive:%d, longterm:%d\n" )
	.zero	5
.LC66:
	ASCII(.string	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d fsp_disp:%d logic_id:%d img_id:%d\n" )
.LC68:
	ASCII(.string	"--------------- PrintDPBState END ---------------\n" )
	.zero	5
.LC70:
	ASCII(.string	"fs[%d]\t" )
.LC72:
	ASCII(.string	"LogicFs:%p\t" )
	.zero	4
.LC74:
	ASCII(.string	"LogicTick:%d\t" )
	.zero	2
.LC76:
	ASCII(.string	"IsRef:%d\t" )
	.zero	6
.LC78:
	ASCII(.string	"DispState:%d\t" )
	.zero	2
.LC80:
	ASCII(.string	"LogicFs:Null\t" )
	.zero	2
.LC82:
	ASCII(.string	"DecFs:%p\t" )
	.zero	6
.LC84:
	ASCII(.string	"DecTick:%d\t" )
	.zero	4
.LC86:
	ASCII(.string	"DecFs:Null\t" )
	.zero	4
.LC88:
	ASCII(.string	"DispFs:%p\t" )
	.zero	5
.LC90:
	ASCII(.string	"DispTick:%d\t" )
	.zero	3
.LC92:
	ASCII(.string	"DispFs:Null\t" )
	.zero	3
.LC95:
	ASCII(.string	"%s num_tile_columns(%d) out of range(0, %d].\n" )
	.zero	2
.LC97:
	ASCII(.string	"%s num_tile_rows(%d) out of range(0, %d].\n" )
	.zero	5
.LC100:
	ASCII(.string	"%s 0 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC102:
	ASCII(.string	"%s 1 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC105:
	ASCII(.string	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\n" )
	.zero	6
.LC107:
	ASCII(.string	"pListX[0][%d] = NULL, listXsize[0] = %d\n" )
	.zero	7
.LC109:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %d\n" )
	.zero	2
.LC111:
	ASCII(.string	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) invalid\n" )
	.zero	1
.LC113:
	ASCII(.string	"pListX[1][%d] = NULL, listXsize[1] = %d\n" )
	.zero	7
.LC115:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %d\n" )
	.zero	2
.LC117:
	ASCII(.string	"pListX[i][%d] pstLogicFs(%p) invalid\n" )
	.zero	2
.LC120:
	ASCII(.string	"%s can't find such pic.\n" )
	.zero	7
.LC122:
	ASCII(.string	"%s DPB.used_size(%d) >= 17.\n" )
	.zero	3
.LC124:
	ASCII(.string	"%s find pos=%d, poc=%d.\n" )
	.zero	7
.LC127:
	ASCII(.string	"%s DPB.size(%d) already reached max(%d).\n" )
	.zero	6
.LC129:
	ASCII(.string	"%s increase DPB size to %d\n" )
	.zero	4
.LC131:
	ASCII(.string	"%s no enough fs(total_fs_num=%d) to increase DPB size.\n" )
.LC133:
	ASCII(.string	"TileWidthInCtb is 0\n" )
	.zero	3
.LC139:
	ASCII(.string	"image_id=%d, pmv_idc=%d\n" )
	.zero	7
.LC141:
	ASCII(.string	"pic msg burst0:\n" )
	.zero	7
.LC145:
	ASCII(.string	"%s call HEVC_CalcTileInfo failed.\n" )
	.zero	5
.LC147:
	ASCII(.string	"logic frame id(=%d): get LogicFs error!\n" )
	.zero	7
.LC149:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC152:
	ASCII(.string	"%s ERROR: bHaveIndependentSlice = 0\n\n" )
	.zero	2
.LC154:
	ASCII(.string	"ListX ERROR: list0size >= %d\n" )
	.zero	2
.LC156:
	ASCII(.string	"ListX ERROR: list1size >= %d\n" )
	.zero	2
.LC158:
	ASCII(.string	"pListX[0][%d] = NULL\n" )
	.zero	2
.LC160:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL\n" )
	.zero	5
.LC162:
	ASCII(.string	"pListX[1][%d] = NULL\n" )
	.zero	2
.LC164:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL\n" )
	.zero	5
.LC166:
	ASCII(.string	"NumSlicePara(%d) >= MaxSliceNum(%d)\n" )
	.zero	3
.LC169:
	ASCII(.string	"line:%d pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC171:
	ASCII(.string	"line:%d seq_parameter_set_id(%d) out of range[0,%d].\n" )
	.zero	2
.LC173:
	ASCII(.string	"line:%d, i(%d) > Max(%d) num_of_pics %d\n" )
	.zero	7
.LC175:
	ASCII(.string	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\n" )
	.zero	7
.LC184:
	ASCII(.string	"%s unkown slice type(%d).\n" )
	.zero	5
.LC186:
	ASCII(.string	"%s pListX[%d] no available pic to repair.\n" )
	.zero	5
.LC188:
	ASCII(.string	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\n" )
	.zero	4
.LC192:
	ASCII(.string	"HEVC_InitListX error.\n" )
	.zero	1
.LC194:
	ASCII(.string	"HEVC_RepairList error.\n" )
.LC198:
	ASCII(.string	"%s image size abnormal(%dx%d)\n" )
	.zero	1
.LC200:
	ASCII(.string	"%s HEVC FSP_ConfigInstance failed!\n" )
	.zero	4
.LC203:
	ASCII(.string	"%s fs[%d]->view_id = %d invalid.\n" )
	.zero	6
.LC205:
	ASCII(.string	"../../core/syntax/hevc.c" )
	.zero	7
.LC207:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC209:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC211:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%d, logic_fs=%p, dec_fs=%p)\n" )
	.zero	1
.LC213:
	ASCII(.string	"Cant find free apc slot.\n" )
	.zero	6
.LC216:
	ASCII(.string	"%s frame logic_fs_id=%d, state=%d\n" )
	.zero	5
.LC218:
	ASCII(.string	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null, logic_fs_id = %d\n" )
	.zero	2
.LC220:
	ASCII(.string	"%s frame poc=%d, is already output\n" )
	.zero	4
.LC222:
	ASCII(.string	"%s frame(%p) invalid, state:%d, non_existing:%d\n" )
	.zero	7
.LC224:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC227:
	ASCII(.string	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STATE_NOT_USED\n" )
.LC229:
	ASCII(.string	"%-5d   specVersion\n" )
	.zero	4
.LC231:
	ASCII(.string	"%-5d   payloadMode\n" )
	.zero	4
.LC233:
	ASCII(.string	"%-5d   hdrPicColourSpace\n" )
	.zero	6
.LC235:
	ASCII(.string	"%-5d   hdrMasterDisplayColourSpace\n" )
	.zero	4
.LC237:
	ASCII(.string	"%-5d   hdrMasterDisplayMaxLuminance\n" )
	.zero	3
.LC239:
	ASCII(.string	"%-5d   hdrMasterDisplayMinLuminance\n" )
	.zero	3
.LC241:
	ASCII(.string	"%-5d   sdrPicColourSpace\n" )
	.zero	6
.LC243:
	ASCII(.string	"%-5d   sdrMasterDisplayColourSpace\n" )
	.zero	4
.LC245:
	ASCII(.string	"%-5d   tmInputSignalBlackLevelOffset\n" )
	.zero	2
.LC247:
	ASCII(.string	"%-5d   tmInputSignalWhiteLevelOffset\n" )
	.zero	2
.LC249:
	ASCII(.string	"%-5d   shadowGain\n" )
	.zero	5
.LC251:
	ASCII(.string	"%-5d   highlightGain\n" )
	.zero	2
.LC253:
	ASCII(.string	"%-5d   midToneWidthAdjFactor\n" )
	.zero	2
.LC255:
	ASCII(.string	"%-5d   tmOutputFineTuningNumVal\n" )
	.zero	7
.LC257:
	ASCII(.string	"%-5d   saturationGainNumVal\n" )
	.zero	3
.LC259:
	ASCII(.string	"%-5d   tmOutputFineTuningX[%d]\n" )
.LC261:
	ASCII(.string	"%-5d   tmOutputFineTuningY[%d]\n" )
.LC263:
	ASCII(.string	"%-5d   saturationGainX[%d]\n" )
	.zero	4
.LC265:
	ASCII(.string	"%-5d   saturationGainY[%d]\n" )
	.zero	4
.LC267:
	ASCII(.string	"%-5d   luminanceMappingNumVal\n" )
	.zero	1
.LC269:
	ASCII(.string	"%-5d   colourCorrectionNumVal\n" )
	.zero	1
.LC271:
	ASCII(.string	"%-5d   luminanceMappingX[%d]\n" )
	.zero	2
.LC273:
	ASCII(.string	"%-5d   luminanceMappingY[%d]\n" )
	.zero	2
.LC275:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuA\n" )
	.zero	7
.LC277:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuB\n" )
	.zero	7
.LC279:
	ASCII(.string	"%-5d   colourCorrectionX[%d]\n" )
	.zero	2
.LC281:
	ASCII(.string	"%-5d   colourCorrectionY[%d]\n" )
	.zero	2
.LC283:
	ASCII(.string	"======SL_HDR1_METADATA= %d=======\n" )
	.zero	5
.LC286:
	ASCII(.string	"%s, [%d %d %d %d %d]\n" )
	.zero	2
.LC288:
	ASCII(.string	"%s HDR_Metadata_phy_addr is invalid!!\n" )
	.zero	1
.LC291:
	ASCII(.string	"FS_ALLOC_ERR, ClearAll\n" )
.LC294:
	ASCII(.string	"Can not new logic fs! ClearAll\n" )
.LC296:
	ASCII(.string	"FSP_GetFspType -1\n" )
	.zero	5
.LC298:
	ASCII(.string	"FSP_GetLogicFs return NULL\n" )
	.zero	4
.LC300:
	ASCII(.string	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), error resilence.\n" )
	.zero	6
.LC302:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC304:
	ASCII(.string	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC306:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC308:
	ASCII(.string	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC310:
	ASCII(.string	"sps with this seq_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC312:
	ASCII(.string	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of range\n" )
	.zero	7
.LC314:
	ASCII(.string	"vps with this video_parameter_set_id = %d havn't be decoded\n" )
	.zero	3
.LC317:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, nal_unit_type = %d, should skip this frame\n" )
	.zero	2
.LC319:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d, nal_unit_type = %d, should skip this frame\n" )
.LC321:
	ASCII(.string	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocCRA = %d, nal_unit_type = %d, should skip this frame\n" )
.LC323:
	ASCII(.string	"HEVC_ReadByteAlignment: code should not be zero.\n" )
	.zero	6
.LC325:
	ASCII(.string	"HEVC_ReadByteAlignment: code:%d\n" )
	.zero	7
.LC327:
	ASCII(.string	"reserved_zero_2bits not equal 0.\n" )
	.zero	6
.LC336:
	ASCII(.string	"HEVC_GetScalingListDefaultAddress NULL.\n" )
	.zero	7
.LC338:
	ASCII(.string	"Error, BsLen: 0x%x, TotalPos: 0x%x\n" )
	.zero	4
.LC340:
	ASCII(.string	"Panic: All zero data sequence in RBSP \n" )
.LC342:
	ASCII(.string	"nal_trail_zero_bit_num err\n" )
	.zero	4
.LC347:
	ASCII(.string	"%s release streambuff=%p, bitstream_length=%d\n" )
	.zero	1
.LC351:
	ASCII(.string	"%s DPB size exceed %d, force to %d\n" )
	.zero	4
.LC354:
	ASCII(.string	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\n" )
	.zero	6
.LC356:
	ASCII(.string	"END of the bit buffer, copy the first packet!\n" )
	.zero	1
.LC359:
	ASCII(.string	"tone_map_id" )
	.zero	4
.LC361:
	ASCII(.string	"Unsupport: target_bit_depth(%d) > 8\n" )
	.zero	3
.LC364:
	ASCII(.string	"pTon->num_pivots > 256\n" )
.LC366:
	ASCII(.string	"frame_packing_arrangement_id" )
	.zero	3
.LC368:
	ASCII(.string	"frame_packing_arrangement_type(%d) out of range\n" )
	.zero	7
.LC370:
	ASCII(.string	"decoding_unit_idx" )
	.zero	6
.LC372:
	ASCII(.string	"num_sps_ids_minus1" )
	.zero	5
.LC374:
	ASCII(.string	"pAct->num_sps_ids_minus1 > 15\n" )
	.zero	1
.LC376:
	ASCII(.string	"active_seq_parameter_set_id" )
	.zero	4
.LC378:
	ASCII(.string	"bp_seq_parameter_set_id" )
.LC380:
	ASCII(.string	"Wrong bp_seq_parameter_set_id = %d, should be 0 to 15!\n" )
.LC383:
	ASCII(.string	"num_decoding_units_minus1" )
	.zero	6
.LC385:
	ASCII(.string	"pPic->num_decoding_units_minus1 > 255\n" )
	.zero	1
.LC387:
	ASCII(.string	"num_nalus_in_du_minus1" )
	.zero	1
.LC389:
	ASCII(.string	"cv_rec_id" )
	.zero	6
.LC391:
	ASCII(.string	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize < 4!!\n" )
	.zero	5
.LC393:
	ASCII(.string	"delta_idx_minus1" )
	.zero	7
.LC395:
	ASCII(.string	"delta_idx(%d) > idx(%d).\n" )
	.zero	6
.LC397:
	ASCII(.string	"rIdx(%d) > (idx-1)(%d) or < 0).\n" )
	.zero	7
.LC399:
	ASCII(.string	"abs_delta_rps_minus1" )
	.zero	3
.LC401:
	ASCII(.string	"pTempRPset->num_of_pics(%d) out of range(0,15).\n" )
	.zero	7
.LC403:
	ASCII(.string	"num_of_pics out of range(0,15).\n" )
	.zero	7
.LC405:
	ASCII(.string	"num_negative_pics" )
	.zero	6
.LC407:
	ASCII(.string	"pTempRPset->num_negative_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC409:
	ASCII(.string	"num_positive_pics" )
	.zero	6
.LC411:
	ASCII(.string	"pTempRPset->num_positive_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC413:
	ASCII(.string	"pShortTermRpset->num_of_pics(%d) out of range[0,%d].\n" )
	.zero	2
.LC415:
	ASCII(.string	"delta_poc_s0_minus1" )
	.zero	4
.LC417:
	ASCII(.string	"delta_poc_s0_minus1(%d) out of range.\n" )
	.zero	1
.LC419:
	ASCII(.string	"delta_poc_s1_minus1" )
	.zero	4
.LC421:
	ASCII(.string	"elemental_duration_in_tc_minus1" )
.LC423:
	ASCII(.string	"cpb_cnt_minus1" )
	.zero	1
.LC425:
	ASCII(.string	"cpb_cnt_minus1(%d) out of range(0,31).\n" )
.LC427:
	ASCII(.string	"bit_rate_value_minus1" )
	.zero	2
.LC429:
	ASCII(.string	"cpb_size_value_minus1" )
	.zero	2
.LC431:
	ASCII(.string	"cpb_size_du_value_minus1" )
	.zero	7
.LC433:
	ASCII(.string	"bit_rate_du_value_minus1" )
	.zero	7
.LC435:
	ASCII(.string	"vps_base_layer_available_flag(%d) not equal 0x1.\n" )
	.zero	6
.LC437:
	ASCII(.string	"vps_max_layers_minus1 %d out of range[0,63].\n" )
	.zero	2
.LC439:
	ASCII(.string	"vps_max_sub_layers_minus1=%d\n" )
	.zero	2
.LC441:
	ASCII(.string	"vps_reserved_0xffff_16bits not equal 0xffff.\n" )
	.zero	2
.LC443:
	ASCII(.string	"VPS HEVC_DecPTL error.\n" )
.LC445:
	ASCII(.string	"vps_num_layer_sets_minus1" )
	.zero	6
.LC447:
	ASCII(.string	"vps_max_dec_pic_buffering_minus1[i]" )
	.zero	4
.LC449:
	ASCII(.string	"vps_num_reorder_pics[i]" )
.LC451:
	ASCII(.string	"vps_max_latency_increase_plus1[i]" )
	.zero	6
.LC453:
	ASCII(.string	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\n" )
	.zero	5
.LC455:
	ASCII(.string	"vps_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC457:
	ASCII(.string	"vps_num_hrd_parameters" )
	.zero	1
.LC459:
	ASCII(.string	"vps_num_hrd_parameters(%d) out of range[0,%d].\n" )
.LC461:
	ASCII(.string	"hrd_layer_set_idx" )
	.zero	6
.LC463:
	ASCII(.string	"VPS HEVC_DecHrdParam error.\n" )
	.zero	3
.LC465:
	ASCII(.string	"pVPS->vps_video_parameter_set_id out of range(0,15).\n" )
	.zero	2
.LC469:
	ASCII(.string	"VPS[%d] decode error0.\n" )
.LC471:
	ASCII(.string	"VPS[%d] decode error1.\n" )
.LC474:
	ASCII(.string	"chroma_sample_loc_type_top_field" )
	.zero	7
.LC476:
	ASCII(.string	"chroma_sample_loc_type_bottom_field" )
	.zero	4
.LC478:
	ASCII(.string	"def_disp_win_left_offset" )
	.zero	7
.LC480:
	ASCII(.string	"VUI pSps->chroma_format_idc out of range(0,3).\n" )
.LC482:
	ASCII(.string	"def_disp_win_right_offset" )
	.zero	6
.LC484:
	ASCII(.string	"def_disp_win_top_offset" )
.LC486:
	ASCII(.string	"def_disp_win_bottom_offset" )
	.zero	5
.LC489:
	ASCII(.string	"vui_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC491:
	ASCII(.string	"VUI HEVC_DecHrdParam error.\n" )
	.zero	3
.LC493:
	ASCII(.string	"min_spatial_segmentation_idc" )
	.zero	3
.LC495:
	ASCII(.string	"VUI min_spatial_segmentation_idc out of range(0,4095).\n" )
.LC497:
	ASCII(.string	"max_bytes_per_pic_denom" )
.LC499:
	ASCII(.string	"max_bits_per_min_cu_denom" )
	.zero	6
.LC501:
	ASCII(.string	"log2_max_mv_length_horizontal" )
	.zero	2
.LC503:
	ASCII(.string	"log2_max_mv_length_vertical" )
	.zero	4
.LC505:
	ASCII(.string	"sop_seq_parameter_set_id" )
	.zero	7
.LC507:
	ASCII(.string	"num_entries_in_sop_minus1" )
	.zero	6
.LC509:
	ASCII(.string	"num_entries_in_sop_minus1 out of range(0,1024)\n" )
.LC511:
	ASCII(.string	"sop_short_term_rps_idx" )
	.zero	1
.LC513:
	ASCII(.string	"sop_poc_delta" )
	.zero	2
.LC515:
	ASCII(.string	"recovery_poc_cnt" )
	.zero	7
.LC517:
	ASCII(.string	"colour_remap_id" )
.LC519:
	ASCII(.string	"colour_remap_coeffs" )
	.zero	4
.LC522:
	ASCII(.string	"reserved_payload_extension_data" )
.LC524:
	ASCII(.string	"line:%d Cosume TotalPos(%d > %d)!!!\n" )
	.zero	3
.LC526:
	ASCII(.string	"HEVC_SeiMessage HEVC_Sei_Payload error.\n" )
	.zero	7
.LC528:
	ASCII(.string	"SEI pSEISPS = NULL.\n" )
	.zero	3
.LC530:
	ASCII(.string	"SEI HEVC_SeiMessage error.\n" )
	.zero	4
.LC532:
	ASCII(.string	"SEI BsIsByteAligned error.\n" )
	.zero	4
.LC534:
	ASCII(.string	"SEI rbsp_trailing_bits(%d) not equal 0x80.\n" )
	.zero	4
.LC536:
	ASCII(.string	"nesting_num_ops_minus1" )
	.zero	1
.LC538:
	ASCII(.string	"nesting_num_ops_minus1 out of range(0,%d)\n" )
	.zero	5
.LC540:
	ASCII(.string	"nesting_op_idx" )
	.zero	1
.LC542:
	ASCII(.string	"nesting_num_layers_minus1" )
	.zero	6
.LC544:
	ASCII(.string	"nesting_num_layers_minus1 out of range(0,63)\n" )
	.zero	2
.LC549:
	ASCII(.string	"scaling_list_pred_matrix_id_delta" )
	.zero	6
.LC551:
	ASCII(.string	"scaling_list_pred_matrix_id_delta out of range(0,matrixId).\n" )
	.zero	3
.LC553:
	ASCII(.string	"HEVC_DecScalingListData pMatrixAddress NULL.\n" )
	.zero	2
.LC555:
	ASCII(.string	"scaling_list_dc_coef_minus8" )
	.zero	4
.LC557:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-7,247).\n" )
	.zero	5
.LC559:
	ASCII(.string	"scaling_list_delta_coef" )
.LC561:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-128,127).\n" )
	.zero	3
.LC564:
	ASCII(.string	"chroma_format_idc" )
	.zero	6
.LC566:
	ASCII(.string	"pSPS->chroma_format_idc out of range(0,3).\n" )
	.zero	4
.LC568:
	ASCII(.string	"pSPS->chroma_format_idc not equal(%d) 1.\n" )
	.zero	6
.LC570:
	ASCII(.string	"pic_width_in_luma_samples" )
	.zero	6
.LC572:
	ASCII(.string	"pic_width_in_luma_samples out of range(0,8192).\n" )
	.zero	7
.LC575:
	ASCII(.string	"pic_height_in_luma_samples" )
	.zero	5
.LC577:
	ASCII(.string	"pic_height_in_luma_samples out of range(0,4096).\n" )
	.zero	6
.LC579:
	ASCII(.string	"ERROR Unkown level: %d\n" )
.LC581:
	ASCII(.string	"conf_win_left_offset" )
	.zero	3
.LC584:
	ASCII(.string	"conf_win_right_offset" )
	.zero	2
.LC586:
	ASCII(.string	"conf_win_left_offset+conf_win_right_offset out of range.\n" )
	.zero	6
.LC588:
	ASCII(.string	"conf_win_top_offset" )
	.zero	4
.LC590:
	ASCII(.string	"conf_win_bottom_offset" )
	.zero	1
.LC592:
	ASCII(.string	"conf_win_top_offset+conf_win_bottom_offset out of range.\n" )
	.zero	6
.LC594:
	ASCII(.string	"bit_depth_luma_minus8" )
	.zero	2
.LC596:
	ASCII(.string	"bit_depth_luma(%d) out of range(8,10).\n" )
.LC598:
	ASCII(.string	"bit_depth_chroma_minus8" )
.LC600:
	ASCII(.string	"bit_depth_chroma(%d) out of range[8,14].\n" )
	.zero	6
.LC602:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4" )
	.zero	6
.LC604:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12].\n" )
	.zero	1
.LC606:
	ASCII(.string	"sps_max_dec_pic_buffering_minus1" )
	.zero	7
.LC608:
	ASCII(.string	"sps_num_reorder_pics" )
	.zero	3
.LC610:
	ASCII(.string	"sps_max_latency_increase_plus1" )
	.zero	1
.LC612:
	ASCII(.string	"log2_min_coding_block_size_minus3" )
	.zero	6
.LC614:
	ASCII(.string	"log2_min_luma_coding_block_size_minus3 out of range(0,3).\n" )
	.zero	5
.LC616:
	ASCII(.string	"log2_diff_max_min_coding_block_size" )
	.zero	4
.LC618:
	ASCII(.string	"log2_diff_max_min_luma_coding_block_size out of range(0,3).\n" )
	.zero	3
.LC620:
	ASCII(.string	"log2_ctb_sizeY out of range(4,6).\n" )
	.zero	5
.LC622:
	ASCII(.string	"log2_min_transform_block_size_minus2" )
	.zero	3
.LC624:
	ASCII(.string	"log2_min_transform_block_size_minus2 out of range(0,3).\n" )
	.zero	7
.LC626:
	ASCII(.string	"log2_diff_max_min_transform_block_size" )
	.zero	1
.LC628:
	ASCII(.string	"log2_diff_max_min_transform_block_size out of range(0,3).\n" )
	.zero	5
.LC630:
	ASCII(.string	"quadtree_tu_log2_min_size not less than log2_min_cb_sizeY.\n" )
	.zero	4
.LC632:
	ASCII(.string	"quadtree_tu_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC634:
	ASCII(.string	"max_transform_hierarchy_depth_inter" )
	.zero	4
.LC636:
	ASCII(.string	"max_transform_hierarchy_depth_inter out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC638:
	ASCII(.string	"max_transform_hierarchy_depth_intra" )
	.zero	4
.LC640:
	ASCII(.string	"max_transform_hierarchy_depth_intra out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC642:
	ASCII(.string	"SPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC644:
	ASCII(.string	"SPS sao is off and pic height(%d) is too small.(Logic Unsupported).\n" )
	.zero	3
.LC646:
	ASCII(.string	"log2_min_pcm_luma_coding_block_size_minus3" )
	.zero	5
.LC648:
	ASCII(.string	"log2_min_pcm_coding_block_size_minus3(%d) out of range[0,2].\n" )
	.zero	2
.LC650:
	ASCII(.string	"log2_diff_max_min_pcm_luma_coding_block_size" )
	.zero	3
.LC652:
	ASCII(.string	"log2_diff_max_min_pcm_coding_block_size(%d) out of range[0,2].\n" )
.LC654:
	ASCII(.string	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC656:
	ASCII(.string	"num_short_term_ref_pic_sets" )
	.zero	4
.LC658:
	ASCII(.string	"num_short_term_ref_pic_sets out of range[0,%d].\n" )
	.zero	7
.LC660:
	ASCII(.string	"SPS HEVC_DecShortTermRefPicSet error.\n" )
	.zero	1
.LC662:
	ASCII(.string	"num_long_term_ref_pic_sps" )
	.zero	6
.LC664:
	ASCII(.string	"num_long_term_ref_pic_sps out of range[0,32].\n" )
	.zero	1
.LC666:
	ASCII(.string	"SPS HEVC_DecVuiParam error.\n" )
	.zero	3
.LC671:
	ASCII(.string	"sps_video_parameter_set_id out of range(0,%d).\n" )
.LC673:
	ASCII(.string	"sps_max_sub_layers_minus1 out of range(0,%d).\n" )
	.zero	1
.LC675:
	ASCII(.string	"SPS HEVC_DecPTL error.\n" )
.LC677:
	ASCII(.string	"sps_seq_parameter_set_id" )
	.zero	7
.LC679:
	ASCII(.string	"sps_seq_parameter_set_id out of range(0,%d).\n" )
	.zero	2
.LC683:
	ASCII(.string	"SPS[%d] decode error0.\n" )
.LC685:
	ASCII(.string	"SPS[%d] decode error.\n" )
	.zero	1
.LC688:
	ASCII(.string	"pps_seq_parameter_set_id" )
	.zero	7
.LC690:
	ASCII(.string	"pic_parameter_set_id(%d) out of range[0,15].\n" )
	.zero	2
.LC692:
	ASCII(.string	"SPS(%d) haven't decode.\n" )
	.zero	7
.LC694:
	ASCII(.string	"num_ref_idx_l0_default_active_minus1" )
	.zero	3
.LC696:
	ASCII(.string	"num_ref_idx_l0_default_active out of range[0,15].\n" )
	.zero	5
.LC698:
	ASCII(.string	"num_ref_idx_l1_default_active_minus1" )
	.zero	3
.LC700:
	ASCII(.string	"num_ref_idx_l1_default_active out of range[0,15].\n" )
	.zero	5
.LC702:
	ASCII(.string	"init_qp_minus26" )
.LC704:
	ASCII(.string	"pic_init_qp(%d) out of range[-%d,51].\n" )
	.zero	1
.LC706:
	ASCII(.string	"diff_cu_qp_delta_depth" )
	.zero	1
.LC708:
	ASCII(.string	"diff_cu_qp_delta_depth out of range[0,3].\n" )
	.zero	5
.LC710:
	ASCII(.string	"pps_cb_qp_offset" )
	.zero	7
.LC712:
	ASCII(.string	"pic_cb_qp_offset out of range[-12,12].\n" )
.LC714:
	ASCII(.string	"pps_cr_qp_offset" )
	.zero	7
.LC716:
	ASCII(.string	"pic_cr_qp_offset out of range[-12,12].\n" )
.LC718:
	ASCII(.string	"num_tile_columns_minus1" )
.LC720:
	ASCII(.string	"num_tile_columns(%d) out of range(0,%d).\n" )
	.zero	6
.LC722:
	ASCII(.string	"num_tile_rows_minus1" )
	.zero	3
.LC724:
	ASCII(.string	"num_tile_rows out(%d) of range(0,%d).\n" )
	.zero	1
.LC726:
	ASCII(.string	"Logic limit(%d), num_tile_columns(%d) exceed.\n" )
	.zero	1
.LC729:
	ASCII(.string	"Logic limit(%d), num_tile_rows(%d) exceed.\n" )
	.zero	4
.LC731:
	ASCII(.string	"column_width_minus1" )
	.zero	4
.LC733:
	ASCII(.string	"column_width[%d](%d) out of range (0 %d)\n" )
	.zero	6
.LC735:
	ASCII(.string	"row_height_minus1" )
	.zero	6
.LC737:
	ASCII(.string	"row_height[%d](%d) out of range (0 %d)\n" )
.LC739:
	ASCII(.string	"column_bd[%d](%d) <= 0, invalid!\n" )
	.zero	6
.LC741:
	ASCII(.string	"row_bd[%d](%d) <= 0, invalid!\n" )
	.zero	1
.LC743:
	ASCII(.string	"PPS tile width(%d) is too small.(Logic Unsupport)\n" )
	.zero	5
.LC745:
	ASCII(.string	"PPS tile height(%d) is too small.(Logic Unsupport)\n" )
	.zero	4
.LC747:
	ASCII(.string	"pps_beta_offset_div2" )
	.zero	3
.LC749:
	ASCII(.string	"pps_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	2
.LC751:
	ASCII(.string	"pps_tc_offset_div2" )
	.zero	5
.LC753:
	ASCII(.string	"pps_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	4
.LC755:
	ASCII(.string	"PPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC757:
	ASCII(.string	"log2_parallel_merge_level_minus2" )
	.zero	7
.LC759:
	ASCII(.string	"log2_parallel_merge_level(%d) out of range(2,log2_ctb_sizeY).\n" )
	.zero	1
.LC761:
	ASCII(.string	"pps_pic_parameter_set_id" )
	.zero	7
.LC763:
	ASCII(.string	"pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC767:
	ASCII(.string	"PPS[%d] decode error.\n" )
	.zero	1
.LC770:
	ASCII(.string	"luma_log2_weight_denom" )
	.zero	1
.LC772:
	ASCII(.string	"luma_log2_weight_denom out of range(0,7).\n" )
	.zero	5
.LC774:
	ASCII(.string	"delta_chroma_log2_weight_denom" )
	.zero	1
.LC776:
	ASCII(.string	"delta_chroma_log2_weight_denom out of range(-7,7).\n" )
	.zero	4
.LC778:
	ASCII(.string	"chroma_log2_weight_denom out of range(0,7).\n" )
	.zero	3
.LC780:
	ASCII(.string	"delta_luma_weight_l0" )
	.zero	3
.LC782:
	ASCII(.string	"delta_luma_weight_l0(%d) out of range(-128,127).\n" )
	.zero	6
.LC784:
	ASCII(.string	"luma_offset_l0" )
	.zero	1
.LC786:
	ASCII(.string	"luma_offset_l0(%d) out of range(-128,127).\n" )
	.zero	4
.LC788:
	ASCII(.string	"delta_chroma_weight_l0" )
	.zero	1
.LC790:
	ASCII(.string	"delta_chroma_weight_l0 out of range(-128,127).\n" )
.LC792:
	ASCII(.string	"delta_chroma_offset_l0" )
	.zero	1
.LC794:
	ASCII(.string	"delta_chroma_offset_l0 out of range(-512,511).\n" )
.LC796:
	ASCII(.string	"delta_luma_weight_l1" )
	.zero	3
.LC798:
	ASCII(.string	"delta_luma_weight_l1 out of range(-128,127).\n" )
	.zero	2
.LC800:
	ASCII(.string	"luma_offset_l1" )
	.zero	1
.LC802:
	ASCII(.string	"luma_offset_l1 out of range(-128,127).\n" )
.LC804:
	ASCII(.string	"delta_chroma_weight_l1" )
	.zero	1
.LC806:
	ASCII(.string	"delta_chroma_weight_l1 out of range(-128,127).\n" )
.LC808:
	ASCII(.string	"delta_chroma_offset_l1" )
	.zero	1
.LC810:
	ASCII(.string	"delta_chroma_offset_l1 out of range(-512,511).\n" )
.LC812:
	ASCII(.string	"slice_pic_parameter_set_id" )
	.zero	5
.LC815:
	ASCII(.string	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\n" )
	.zero	6
.LC817:
	ASCII(.string	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\n" )
.LC819:
	ASCII(.string	"max_cu_width(%d)/max_cu_height(%d) = 0\n" )
.LC821:
	ASCII(.string	"slice_segment_address(%d) out of range(0,%d).\n" )
	.zero	1
.LC823:
	ASCII(.string	"slice_type" )
	.zero	5
.LC825:
	ASCII(.string	"slice_type(%d) out of range(0,2].\n" )
	.zero	5
.LC827:
	ASCII(.string	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \n" )
	.zero	7
.LC829:
	ASCII(.string	"SH HEVC_DecShortTermRefPicSet error.\n" )
	.zero	2
.LC831:
	ASCII(.string	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\n" )
	.zero	4
.LC833:
	ASCII(.string	"num_long_term_sps" )
	.zero	6
.LC835:
	ASCII(.string	"num_long_term_sps(%d) out of range[0,%d].\n" )
	.zero	5
.LC837:
	ASCII(.string	"num_long_term_pics" )
	.zero	5
.LC839:
	ASCII(.string	"SH ERROR: (num_negative_pics(%d) + num_positive_pics(%d) + num_of_longterm_pics(%d)) > %d\n" )
	.zero	5
.LC841:
	ASCII(.string	"lt_idx_sps[%d] = %d, but out of range[0,%d].\n" )
	.zero	2
.LC843:
	ASCII(.string	"delta_poc_msb_cycle_lt" )
	.zero	1
.LC845:
	ASCII(.string	"ERROR: pRPS->num_of_pics(%d) > %d.\n" )
	.zero	4
.LC847:
	ASCII(.string	"num_ref_idx_l0_active_minus1" )
	.zero	3
.LC849:
	ASCII(.string	"num_ref_idx_l0_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC851:
	ASCII(.string	"num_ref_idx_l1_active_minus1" )
	.zero	3
.LC853:
	ASCII(.string	"num_ref_idx_l1_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC855:
	ASCII(.string	"pRPS is null.\n" )
	.zero	1
.LC857:
	ASCII(.string	"pRPS->num_of_pics out(%d) of range(0,%d).\n" )
	.zero	5
.LC859:
	ASCII(.string	"SH HEVC_DecRefPicListsModification error.\n" )
	.zero	5
.LC861:
	ASCII(.string	"collocated_ref_idx" )
	.zero	5
.LC863:
	ASCII(.string	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) out of range(0,%d).\n" )
.LC865:
	ASCII(.string	"SH HEVC_DecPredWeightTable error.\n" )
	.zero	5
.LC867:
	ASCII(.string	"five_minus_max_num_merge_cand" )
	.zero	2
.LC869:
	ASCII(.string	"SH max_num_merge_cand(%d) out of range(1,5).\n" )
	.zero	2
.LC871:
	ASCII(.string	"slice_qp_delta" )
	.zero	1
.LC873:
	ASCII(.string	"SH slice_qp(%d) out of range [-%d,51].\n" )
.LC875:
	ASCII(.string	"slice_cb_qp_offset" )
	.zero	5
.LC877:
	ASCII(.string	"SH slice_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC879:
	ASCII(.string	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	2
.LC881:
	ASCII(.string	"slice_cr_qp_offset" )
	.zero	5
.LC883:
	ASCII(.string	"SH slice_cr_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC885:
	ASCII(.string	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) out of range[-12,12].\n" )
.LC887:
	ASCII(.string	"slice_beta_offset_div2" )
	.zero	1
.LC889:
	ASCII(.string	"SH slice_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	5
.LC891:
	ASCII(.string	"slice_tc_offset_div2" )
	.zero	3
.LC893:
	ASCII(.string	"SH slice_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	7
.LC895:
	ASCII(.string	"num_entry_point_offsets" )
.LC897:
	ASCII(.string	"CurrSlice.num_entry_point_offsets(%d) out of range[0,%d].\n" )
	.zero	5
.LC899:
	ASCII(.string	"offset_len_minus1" )
	.zero	6
.LC901:
	ASCII(.string	"CurrSlice.offset_len(%d) out of range[1,32].\n" )
	.zero	2
.LC903:
	ASCII(.string	"slice_segment_header_extension_length" )
	.zero	2
.LC905:
	ASCII(.string	"slice_segment_header_extension_length(%d) out of range [0,256]\n" )
.LC907:
	ASCII(.string	"bitsLeft(%d) < slice_segment_header_extension_length(%d)\n" )
	.zero	6
.LC912:
	ASCII(.string	"%s arrange mem failed.\n" )
.LC914:
	ASCII(.string	"Init dec para\n" )
	.zero	1
.LC918:
	ASCII(.string	"HEVC_InitDPB error, return %d\n" )
	.zero	1
.LC920:
	ASCII(.string	"HEVC_AllocFrameStore error\n" )
	.zero	4
.LC923:
	ASCII(.string	"%s: HEVC_OutputFrame failed!\n" )
	.zero	2
.LC926:
	ASCII(.string	"%s output current picture failed\n" )
	.zero	6
.LC930:
	ASCII(.string	"HEVC.c line %d: frame para err(ret=%d), recycle image self\n" )
	.zero	4
.LC934:
	ASCII(.string	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\n" )
.LC938:
	ASCII(.string	"%s call HEVC_GetUnRefPicWithMinPoc failed\n" )
	.zero	5
.LC940:
	ASCII(.string	"%s call HEVC_OutputOneFrmFromDPB failed\n" )
	.zero	7
.LC943:
	ASCII(.string	"%s: HEVC_OutputFrmToVO err!\n" )
	.zero	3
.LC945:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC947:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC949:
	ASCII(.string	"nal_release_err\n" )
	.zero	7
.LC952:
	ASCII(.string	"%s: flush dpb failed, return %d\n" )
	.zero	7
.LC955:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), need to increase DPB size.\n" )
	.zero	5
.LC957:
	ASCII(.string	"%s call HEVC_IncreaseDPBSize failed\n" )
	.zero	3
.LC959:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpoc frame.\n" )
	.zero	3
.LC964:
	ASCII(.string	"%s with invalid pos(%d)\n" )
	.zero	7
.LC967:
	ASCII(.string	"%s get APC error, ret %d\n" )
	.zero	6
.LC970:
	ASCII(.string	"%s %d: InsertFrmInDPB failed, return %d\n" )
	.zero	7
.LC972:
	ASCII(.string	"%s call HEVC_CheckFrameStore failed!\n" )
	.zero	2
.LC976:
	ASCII(.string	"%s call HEVC_RemoveUnUsedFrameStore Failed.\n" )
	.zero	3
.LC978:
	ASCII(.string	"%s call HEVC_InsertFrmInDPB Failed.\n" )
	.zero	3
.LC983:
	ASCII(.string	"%s call HEVC_FirstFrameFastOut Failed\n" )
	.zero	1
.LC985:
	ASCII(.string	"DPB.used_size may bigger than DPB.size\n" )
.LC987:
	ASCII(.string	"HEVC_InsertFrmInDPB Failed, ret = %d\n" )
	.zero	2
.LC989:
	ASCII(.string	"%s call HEVC_OutputFrmFromDPB failed\n" )
	.zero	2
.LC993:
	ASCII(.string	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_NORMAL\n" )
	.zero	5
.LC995:
	ASCII(.string	"%s, REPORT_IFRAME_ERR\n" )
	.zero	1
.LC998:
	ASCII(.string	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n" )
	.zero	1
.LC1000:
	ASCII(.string	"%s call HEVC_IModeProcess Failed\n" )
	.zero	6
.LC1002:
	ASCII(.string	"HEVC_StorePicInDpb return(%d) from L%d\n" )
.LC1004:
	ASCII(.string	"%s call HEVC_SimpleDPBProcess Failed\n" )
	.zero	2
.LC1006:
	ASCII(.string	"%s call HEVC_DecOrderProcess Failed\n" )
	.zero	3
.LC1008:
	ASCII(.string	"%s call HEVC_DispOrderProcess Failed\n" )
	.zero	2
.LC1010:
	ASCII(.string	"%s return HEVC_DEC_ERR\n" )
.LC1013:
	ASCII(.string	"No frame store for lost pic.\n" )
	.zero	2
.LC1015:
	ASCII(.string	"DPB ERROR: Can not get ref_fs!\n" )
.LC1017:
	ASCII(.string	"DPB no suited fs for lost pic.\n" )
.LC1019:
	ASCII(.string	"Take poc(%d) to creat lost poc(%d).\n" )
	.zero	3
.LC1021:
	ASCII(.string	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\n" )
	.zero	5
.LC1023:
	ASCII(.string	"ERROR: Can not new logic fs!\n" )
	.zero	2
.LC1025:
	ASCII(.string	"Lost pic insert in DPB Failed!\n" )
.LC1027:
	ASCII(.string	"Ref frame(poc %d) lost.\n" )
	.zero	7
.LC1029:
	ASCII(.string	"s32OutErrThr = %d,drop poc %d because lost ref frame(pod %d)\n" )
	.zero	2
.LC1032:
	ASCII(.string	"DecVDM MaxBytesReceived exceed threshold!\n" )
	.zero	5
.LC1034:
	ASCII(.string	"DecVDM no slice and needn't start VDM\n" )
	.zero	1
.LC1036:
	ASCII(.string	"IPBDecMode Changed (%d -> %d)\n" )
	.zero	1
.LC1039:
	ASCII(.string	"VDM start, TotalPicNum=%d.\n" )
	.zero	4
.LC1042:
	ASCII(.string	"%s no correct slice in the pic\n" )
.LC1044:
	ASCII(.string	"Discard this B(poc=%d) before P, is_ref_idc=%d.\n" )
	.zero	7
.LC1047:
	ASCII(.string	"metadatasize is too large:%d at line:%d\n" )
	.zero	7
.LC1050:
	ASCII(.string	"%s:%d Metadata map failed\n" )
	.zero	5
.LC1054:
	ASCII(.string	"%s:%d Metadata unmap failed\n" )
	.zero	3
.LC1057:
	ASCII(.string	"*****[%s][%d],BL Codec can only dec BL stream!!*****\n" )
	.zero	2
.LC1059:
	ASCII(.string	"*****[%s][%d],EL Codec can only dec EL stream in DV_DUAL_VES_IMP stream!!*****\n" )
.LC1061:
	ASCII(.string	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****\n" )
	.zero	3
.LC1065:
	ASCII(.string	"%s call HEVC_FlushOutputFrmFromDPB failed\n" )
	.zero	5
.LC1067:
	ASCII(.string	"%s call HEVC_EmptyFrmFromDPB failed\n" )
	.zero	3
.LC1069:
	ASCII(.string	"Meet CRA frame, force output remain frame, CurPoc %d, LastPoc %d\n" )
	.zero	6
.LC1071:
	ASCII(.string	"Init pic err, exit\n" )
	.zero	4
.LC1073:
	ASCII(.string	"HEVC_WritePicMsg failed!\n" )
	.zero	6
.LC1075:
	ASCII(.string	"Start Reason: SliceParaNum= %d\n" )
.LC1078:
	ASCII(.string	"Too many slice , err!\n" )
	.zero	1
.LC1080:
	ASCII(.string	"Cur pic not init yet, discard this slice!\n" )
	.zero	5
.LC1082:
	ASCII(.string	"Dec List error, ret=%d\n" )
.LC1084:
	ASCII(.string	"Ref List is Wrong!\n" )
	.zero	4
.LC1086:
	ASCII(.string	"HEVC_WriteSliceMsg err.\n" )
	.zero	7
.LC1089:
	ASCII(.string	"VPS decode error.\n" )
	.zero	5
.LC1092:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1094:
	ASCII(.string	"PPS decode error.\n" )
	.zero	5
.LC1096:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1098:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d\n" )
.LC1101:
	ASCII(.string	"HEVC_DecSliceSegmentHeader dec err\n" )
	.zero	4
.LC1104:
	ASCII(.string	"CurBitsLen = %d, MinBitsLen = %d\n" )
	.zero	6
.LC1107:
	ASCII(.string	"%s last frame fs unrelease, fix it!\n" )
	.zero	3
.LC1111:
	ASCII(.string	"CtbNumOneFrame=%d, SedEnd0=%d\n" )
	.zero	1
.LC1115:
	ASCII(.string	"%s: Get context addr failed!\n" )
	.zero	2
.LC1117:
	ASCII(.string	"%s FATAL: MemOffset %d > ContextMemSize %d.\n" )
	.zero	3
.LC1119:
	ASCII(.string	"%s: VCTRL_GetChanIDByCtx() return -1!\n" )
	.zero	1
.LC1121:
	ASCII(.string	"Fs leak, clear dpb fs not in vo queue.\n" )
.LC1123:
	ASCII(.string	"No frame store available!\n" )
	.zero	5
.LC1126:
	ASCII(.string	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak, ClearAll!\n" )
.LC1128:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pPacket!\n" )
	.zero	1
.LC1130:
	ASCII(.string	"HevcCtx not init!\n" )
	.zero	5
.LC1132:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\n" )
	.zero	6
.LC1135:
	ASCII(.string	"nal_layer_id out %d of range[0,1].\n" )
	.zero	4
.LC1141:
	ASCII(.string	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	4
.LC1144:
	ASCII(.string	"HEVC_InquireSliceProperty error.\n" )
	.zero	6
.LC1147:
	ASCII(.string	"HEVC_DecOneNal ERR\n" )
	.zero	4
.LC1150:
	ASCII(.string	"HEVC_StorePicInDPB failed, ret = %d\n" )
	.zero	3
.LC1153:
	ASCII(.string	"pHevcCtx->CurrPic.frame_store is null pointer\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 456960
.LANCHOR3 = . + 604928
.LANCHOR6 = . + 639744
	.type	g_SigLastScan, %object
	.size	g_SigLastScan, 458752
g_SigLastScan:
	.zero	458752
	.type	g_TsToRsMap, %object
	.size	g_TsToRsMap, 147456
g_TsToRsMap:
	.zero	147456
	.type	g_IsDeced, %object
	.size	g_IsDeced, 36864
g_IsDeced:
	.zero	36864
	.type	s_TmpParam, %object
	.size	s_TmpParam, 12660
s_TmpParam:
	.zero	12660
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
