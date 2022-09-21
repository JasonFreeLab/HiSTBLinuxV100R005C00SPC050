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
	ldr	w0, [x19, 4692]
	mov	w4, 1888
	ldr	x2, [x19, 2352]
	add	x13, x19, 4096
	add	x17, x13, 1492
	ldr	x1, [x19, 2344]
	mov	w3, 12660
	ldr	w7, [x19, 5588]
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
	ldr	w3, [x19, 2764]
	mov	w9, 0
	mov	w8, 0
	.p2align 2
.L6:
	sxtw	x16, w15
	cbz	w3, .L12
	add	x12, x19, x16, lsl 2
	mov	w14, 0
	mov	w0, 0
	ldr	w4, [x12, 4744]
	b	.L9
	.p2align 3
.L47:
	ldr	x1, [x2, 2784]
	ldr	w2, [x1, 60]
	cbz	w2, .L8
	ldr	w6, [x1, 8]
	ldr	w2, [x12, 5688]
	cmp	w6, w2
	beq	.L44
.L8:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L46
.L9:
	add	x2, x19, x0, sxtw 3
	cbnz	w4, .L47
	ldr	x1, [x2, 2784]
	ldr	w2, [x1, 60]
	cbz	w2, .L8
	ldr	w11, [x1, 8]
	ldr	w10, [x12, 5688]
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
	add	x10, x13, 1492
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
	ldr	x2, [x2, 2784]
	ldr	w4, [x2, 60]
	cbnz	w4, .L15
	ldr	w4, [x10, x1, lsl 2]
	ldr	w6, [x19, 4668]
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
	ldr	w1, [x19, 4688]
	sxtw	x2, w12
	add	x0, x2, 8
	ldr	w4, [x19, 4668]
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
	ldr	w1, [x19, 4688]
	add	x2, x16, 8
	ldr	w4, [x19, 4668]
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
	ldr	w3, [x19, 2764]
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
	ldr	w2, [x19, 2760]
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
	add	x3, x3, 1920
	mov	x2, x19
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L60
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 612]
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
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	str	w0, [x19, -4]
	mov	w1, 16
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x19, 8]
	cmp	x19, x22
	bne	.L63
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 28]
	mov	w1, 16
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x21, 32]
	mov	w1, 32
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x21, 36]
	mov	w1, 32
	ldr	x0, [x20, 2328]
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
	add	x0, x0, 3632
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 3332]
	add	x0, x19, 3072
	stp	xzr, xzr, [x0, 280]
	stp	xzr, xzr, [x0, 296]
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
	ldr	w2, [x19, 4692]
	mov	w5, 1888
	ldr	x1, [x19, 2352]
	add	x3, x19, 8192
	add	x4, x3, 3632
	ldr	x0, [x19, 2344]
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
	add	x4, x19, 3336
	ldr	w0, [x4, 8]
	ldr	x1, [x4, 16]
	add	x0, x0, x1
	str	x0, [x4, 40]
.L68:
	add	x3, x3, 3632
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
	ldrb	w0, [x19, 3328]
	add	x4, x19, 3336
	cbnz	w0, .L77
	ldp	x1, x5, [x4, 16]
.L71:
	ldr	w6, [x4, 8]
	add	x0, x6, x1
	str	x0, [x4, 16]
	cmp	x0, x5
	str	x0, [x4, 40]
	bge	.L68
	add	x3, x3, 3632
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
	add	x4, x19, 3336
	ldrsw	x0, [x19, 3332]
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
	ldr	x0, [x20, 3376]
	str	x0, [x20, 3360]
.L78:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	ldr	x0, [x20, 2424]
	ldr	x0, [x0, 56]
	cmn	x0, #1
	beq	.L80
	ldr	x1, [x20, 11856]
	str	x0, [x20, 11848]
	str	x1, [x20, 11864]
.L80:
	add	x0, x20, 8192
	mov	w1, 1
	strb	w1, [x0, 3632]
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
	ldr	w4, [x19, 11836]
	ldr	w5, [x19, 11840]
	ldr	x6, [x19, 11848]
	ldr	x3, [x19, 11856]
	ldr	x7, [x19, 11864]
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
	str	x1, [x19, 4608]
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
	ldr	x4, [x24, 2416]
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
	ldr	w2, [x19, 4724]
	bl	dprint_vfmw
	ldr	w0, [x19, 4724]
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
	ldr	x3, [x21, 2448]
	bl	dprint_vfmw
	ldr	x2, [x21, 2448]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L175
	ldr	x2, [x2, 16]
	bl	dprint_vfmw
	ldr	x0, [x21, 2448]
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
	ldr	w0, [x19, 4724]
	cmp	w0, w20
	bhi	.L177
.L178:
	ldr	x1, .LC30
	mov	w0, 1
	ldr	w2, [x19, 4728]
	bl	dprint_vfmw
	ldr	w0, [x19, 4728]
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
	ldr	x3, [x21, 2584]
	bl	dprint_vfmw
	ldr	x2, [x21, 2584]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L180
	ldr	x2, [x2, 16]
	bl	dprint_vfmw
	ldr	x0, [x21, 2584]
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
	ldr	w0, [x19, 4728]
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
	mov	x23, 14064
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
	add	x3, x3, 1152
	umaddl	x27, w20, w24, x23
	ldr	w4, [x4, 13488]
	add	x3, x21, x3
	ldrb	w6, [x5, 1154]
	add	x27, x21, x27
	ldrb	w5, [x5, 1153]
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
	ldr	w4, [x19, 952]
	mov	w2, 0
	ldr	w3, [x19, 956]
	mov	w0, 1
	ldr	x1, .LC56
	add	x19, x19, 960
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
	ldr	w2, [x19, 2760]
	ldr	w3, [x19, 2764]
	ldr	w6, [x19, 2772]
	ldr	w4, [x19, 2776]
	ldr	w5, [x19, 2780]
	bl	dprint_vfmw
	ldr	w0, [x19, 2764]
	cbz	w0, .L208
	.p2align 2
.L207:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 252]
	ldr	x2, [x21, 2784]
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
	ldr	x1, [x21, 2784]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetRef
	mov	w27, w0
	ldr	x1, [x21, 2784]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDisplay
	ldr	x8, [x21, 2784]
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
	ldr	w0, [x19, 2764]
	cmp	w0, w20
	bhi	.L207
.L208:
	ldr	x24, .LC65
	mov	w0, 1
	mov	x1, x24
	bl	dprint_vfmw
	ldr	w0, [x19, 2764]
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
	ldr	w0, [x19, 2764]
	cmp	w0, w21
	bls	.L206
.L215:
	add	x22, x19, x21, uxtw 3
	ldr	w0, [x19, 252]
	ldr	x1, [x22, 2784]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	x1, [x22, 2784]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDecPhyFs
	mov	x23, x0
	ldr	x1, [x22, 2784]
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
	ldr	w0, [x19, 2764]
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
	ldr	w0, [x19, 3968]
	cbnz	w0, .L232
	ldr	x1, [x19, 2424]
	mov	x2, 4294967296
	ldr	x3, [x1, 648]
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
	ldr	w2, [x1, 656]
	cbnz	w2, .L231
	ldr	w0, [x1, 612]
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
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2328]
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
	ldr	x0, [x22, 2400]
	ldr	x1, [x22, 2392]
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
	ldr	x0, [x22, 2400]
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
	ldr	x1, [x22, 2400]
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
	ldr	x1, [x19, 2328]
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
	ldr	x1, [x19, 2328]
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
	ldr	x0, [x20, 2328]
	mov	w1, 8
	mov	w21, 3
	bl	BsGet
	mov	w22, w0
.L283:
	cbnz	w22, .L278
	mov	w19, 16
	.p2align 2
.L279:
	ldr	x0, [x20, 2328]
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
	ldr	x0, [x20, 2328]
	mov	w1, 32
	bl	BsGet
	subs	w21, w21, #1
	bne	.L283
	b	.L288
.L287:
	ldr	x0, [x20, 2328]
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
	ldr	x0, [x19, 2328]
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
	ldr	x0, [x20, 2328]
	bl	BsGet
	strh	w0, [x19, 2]
	mov	w1, 16
	ldr	x0, [x20, 2328]
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
	ldr	x0, [x20, 2328]
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
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
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
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L308
.L306:
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L305:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L308:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
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
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 4
	ldr	x0, [x20, 2328]
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
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L320
	subs	w21, w21, #16
	mov	w19, 0
	beq	.L317
	.p2align 2
.L319:
	ldr	x0, [x20, 2328]
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
	ldr	w3, [x19, 4724]
	cbnz	w3, .L365
.L325:
	mov	w0, 0
.L363:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L365:
	ldr	x0, [x19, 2448]
	cbz	x0, .L347
	ldr	x0, [x0, 16]
	mov	w20, 0
	cbnz	x0, .L331
	b	.L327
	.p2align 3
.L367:
	ldr	x1, [x0, 32]
	cbz	x1, .L332
	ldr	w3, [x19, 4724]
	add	w20, w20, 1
	cmp	w3, w20
	add	x0, x19, x20, sxtw 3
	bls	.L366
	ldr	x0, [x0, 2448]
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
	ldr	x3, [x19, 2448]
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
	ldr	w0, [x19, 4728]
	cbz	w0, .L325
	ldr	x0, [x19, 2584]
	cbz	x0, .L349
	ldr	x0, [x0, 16]
	mov	w20, 0
	cbnz	x0, .L342
	b	.L339
	.p2align 3
.L370:
	ldr	x1, [x0, 32]
	cbz	x1, .L343
	ldr	w0, [x19, 4728]
	add	w20, w20, 1
	cmp	w0, w20
	add	x1, x19, x20, sxtw 3
	bls	.L325
	ldr	x0, [x1, 2584]
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
	ldr	w3, [x19, 4724]
.L339:
	ldr	x1, .LC116
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L363
.L368:
	ldr	w3, [x19, 4724]
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
	ldr	w3, [x19, 2764]
	cmp	w3, 16
	bhi	.L373
	mov	w4, 2147483647
	mov	w0, 0
	cbz	w3, .L378
	.p2align 2
.L381:
	add	x2, x19, x0, uxtw 3
	ldr	x2, [x2, 2784]
	ldr	w5, [x2, 8]
	cmp	w5, w4
	bge	.L376
	ldr	w2, [x2]
	tst	w2, 16776960
	bne	.L376
	str	w0, [x20]
	mov	w4, w5
	ldr	w3, [x19, 2764]
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
	ldr	w3, [x20, 2760]
	cmp	w3, 16
	bhi	.L388
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	mov	w19, w0
	ldr	w2, [x20, 252]
	ldr	w0, [x20, 3972]
	ldr	w1, [x20, 3976]
	bl	FSP_GetOccupiedNum
	subs	w0, w19, w0
	csel	w0, w0, wzr, pl
	ldr	x2, .LC126
	cmp	w0, wzr
	ble	.L387
	ldr	w3, [x20, 2760]
	add	w3, w3, 1
	cmp	w3, w0
	bhi	.L387
	ldr	x1, .LC130
	add	x2, x2, 216
	mov	w0, 13
	str	w3, [x20, 2760]
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
	str	w1, [x20, 2760]
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
	ldr	w0, [x19, 4684]
	sub	w1, w0, #16
	cmp	w1, 5
	bhi	.L390
	str	w0, [x19, 3956]
	str	wzr, [x19, 3968]
.L389:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L390:
	ldr	w0, [x19, 3956]
	sub	w0, w0, #16
	cmp	w0, 5
	bls	.L389
	ldr	w0, [x19, 4676]
	cmp	w0, 1
	beq	.L392
	cmp	w0, 2
	beq	.L393
	cbnz	w0, .L389
	mov	w0, 2
	str	w0, [x19, 3968]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L392:
	ldr	w1, [x19, 3968]
	cmp	w1, 2
	beq	.L389
	str	w0, [x19, 3968]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L393:
	ldr	w0, [x19, 3968]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L389
	str	wzr, [x19, 3968]
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
	ldr	w1, [x19, 4684]
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
	ldr	x3, [x20, 2400]
	ldrb	w0, [x3, 13]
	cbz	w0, .L440
	ldp	w6, w11, [x3, 68]
	ldr	x0, [x20, 2392]
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
	ldr	x3, [x20, 2400]
	ldrb	w0, [x3, 13]
	cbz	w0, .L475
	ldp	w8, w4, [x3, 68]
	ldr	x0, [x20, 2392]
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
	add	x0, x0, 1140
	blr	x3
	str	wzr, [x19, 9328]
	ldr	x1, [x19, 2400]
	ldr	x2, [x19, 2392]
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
	ldr	w0, [x19, 9328]
	mul	w14, w17, w10
	mov	w12, 0
	mov	w13, 0
	lsl	x9, x9, 1
.L501:
	uxtw	x2, w0
	add	x3, x1, x9
	uxtw	x11, w12
	add	x5, x19, x2, lsl 3
	str	w4, [x5, 9332]
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
	ldr	x1, [x19, 2400]
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
	ldr	w0, [x19, 9328]
	uxtw	x2, w0
.L497:
	add	x2, x19, x2, lsl 3
	sub	w3, w4, #1
	add	w0, w0, 1
	add	x11, x1, x11, lsl 1
	add	w12, w12, 1
	str	w3, [x2, 9336]
	str	w0, [x19, 9328]
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
	add	x24, x19, 8192
	bl	_mcount
	ldr	w3, [x19, 3988]
	mov	w0, 2
	ldr	w2, [x19, 4172]
	ldr	x1, .LC140
	bl	dprint_vfmw
	ldr	x1, .LC142
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w21, [x19, 3960]
	add	x9, x19, 3840
	ldr	w5, [x19, 4136]
	ldr	x3, [x19, 2392]
	ldp	w4, w1, [x9, 228]
	ldp	w0, w2, [x9, 220]
	str	w5, [x19, 7920]
	ldr	w5, [x19, 4140]
	sub	w2, w2, w0
	str	w5, [x19, 7924]
	sub	w0, w4, w0
	ldr	w5, [x19, 4172]
	str	w5, [x19, 7912]
	ldr	w5, [x19, 3988]
	str	w5, [x19, 7916]
	ldr	w5, [x19, 4160]
	str	w5, [x19, 7932]
	ldr	w5, [x19, 4164]
	str	w0, [x19, 7944]
	str	w5, [x19, 7936]
	ldr	x0, [x19, 2432]
	ldr	w5, [x19, 4168]
	str	w21, [x19, 6656]
	uxtw	x21, w21
	str	w2, [x19, 7928]
	lsl	x22, x21, 2
	str	x0, [x19, 9120]
	sub	w0, w1, w4
	str	w5, [x19, 7940]
	sub	x22, x22, x21
	str	wzr, [x19, 204]
	mov	x2, 64
	str	w0, [x19, 7948]
	add	x22, x21, x22, lsl 3
	lsl	x22, x22, 3
	ldrb	w0, [x3, 10]
	add	x1, x22, 12288
	strb	w0, [x20, 2534]
	add	x1, x19, x1
	add	x1, x1, 1088
	ldrb	w0, [x3, 3]
	strb	w0, [x20, 2535]
	add	x0, x20, 2656
	ldrb	w4, [x3, 7]
	strb	w4, [x20, 2536]
	ldrb	w4, [x3, 6]
	strb	w4, [x20, 2537]
	ldrb	w4, [x3, 5]
	strb	w4, [x20, 2538]
	ldr	w4, [x3, 60]
	str	w4, [x19, 6636]
	ldr	w4, [x3, 104]
	strb	w4, [x20, 2544]
	ldr	w4, [x3, 192]
	sub	w4, w4, #1
	str	w4, [x19, 6644]
	ldr	w4, [x3, 188]
	sub	w4, w4, #1
	str	w4, [x19, 6648]
	ldr	w4, [x19, 3964]
	str	w4, [x19, 6652]
	ldr	x4, [x19, 2400]
	ldr	w5, [x4, 84]
	sub	w5, w5, #2
	str	w5, [x19, 6660]
	ldrb	w5, [x4, 11]
	strb	w5, [x20, 2568]
	ldrb	w4, [x4, 10]
	strb	w4, [x20, 2569]
	ldr	w4, [x3, 164]
	str	w4, [x19, 6668]
	ldr	w4, [x3, 168]
	str	w4, [x19, 6672]
	ldr	w4, [x3, 156]
	str	w4, [x19, 6676]
	ldr	w4, [x3, 160]
	str	w4, [x19, 6680]
	ldr	w4, [x3, 148]
	str	w4, [x19, 6684]
	ldr	w4, [x3, 152]
	str	w4, [x19, 6688]
	ldr	w4, [x3, 172]
	str	w4, [x19, 6692]
	ldr	x5, .LC143
	ldr	w4, [x3, 124]
	str	w4, [x19, 6696]
	ldr	w4, [x3, 128]
	str	w4, [x19, 6700]
	ldr	w4, [x3, 100]
	str	w4, [x19, 6704]
	ldr	w4, [x3, 92]
	str	w4, [x19, 6708]
	ldr	w4, [x3, 112]
	str	w4, [x19, 6712]
	ldr	w4, [x3, 108]
	str	w4, [x19, 6716]
	ldr	w4, [x3, 96]
	str	w4, [x19, 6720]
	ldr	w4, [x3, 88]
	ldr	x3, [x5, 104]
	str	w4, [x19, 6724]
	blr	x3
	ldr	x4, [x19, 2392]
	add	x3, x24, 764
	add	x2, x24, 684
	add	x1, x24, 172
	mov	x0, x19
	ldr	w5, [x4, 68]
	str	w5, [x19, 6816]
	ldr	w4, [x4, 64]
	str	w4, [x19, 6820]
	bl	HEVC_CalcTileInfo
	cbnz	w0, .L531
	ldr	x0, [x19, 2400]
	ldrb	w1, [x0, 16]
	strb	w1, [x20, 2748]
	ldrb	w1, [x0, 7]
	strb	w1, [x20, 2749]
	ldrb	w1, [x0, 3]
	strb	w1, [x20, 2750]
	ldrb	w1, [x0, 14]
	strb	w1, [x20, 2751]
	ldrb	w1, [x0, 15]
	strb	w1, [x20, 2752]
	ldrb	w1, [x0, 13]
	strb	w1, [x20, 2753]
	ldr	x1, [x19, 2392]
	ldr	w2, [x0, 56]
	ldr	w1, [x1, 128]
	sub	w1, w1, w2
	str	w1, [x19, 6852]
	ldr	w1, [x0, 52]
	str	w1, [x19, 6856]
	ldrb	w1, [x0, 8]
	strb	w1, [x20, 2764]
	ldrb	w1, [x0, 12]
	strb	w1, [x20, 2765]
	ldrb	w1, [x0, 6]
	strb	w1, [x20, 2766]
	ldr	w1, [x0, 60]
	str	w1, [x19, 6864]
	ldr	w1, [x0, 64]
	str	w1, [x19, 6868]
	ldr	w1, [x0, 72]
	sub	w1, w1, #1
	str	w1, [x19, 6872]
	ldr	w1, [x0, 68]
	sub	w1, w1, #1
	str	w1, [x19, 6876]
	ldrb	w1, [x0, 10]
	strb	w1, [x20, 2569]
	ldrb	w0, [x0, 11]
	strb	w0, [x20, 2568]
	ldr	x1, [x19, 4016]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x23, x0
	cbz	x0, .L532
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L518
	cbz	x3, .L518
	ldr	w0, [x19, 252]
	add	x3, x24, 44
	add	x2, x20, 3872
	add	x1, x20, 4000
	add	x22, x19, x22
	bl	FSP_GetDecFsAddrTab
	ldr	x3, [x23, 32]
	add	x1, x24, 36
	ldr	w0, [x19, 252]
	add	x2, x20, 4004
	ldr	w3, [x3, 4]
	str	w3, [x19, 7912]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x19, 3988]
	mov	w1, 0
	str	w0, [x19, 7916]
	ldr	w0, [x23, 12]
	str	w0, [x19, 8232]
	ldr	x0, [x23, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 9320]
	ldr	x0, [x23, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 9324]
	ldr	w4, [x22, 13240]
	str	w4, [x19, 9108]
	cbz	w4, .L523
	lsl	x3, x21, 3
	sub	x3, x3, x21
	add	x21, x21, x3, lsl 3
	sub	x3, x21, x3
	.p2align 2
.L526:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x3, x0
	cmp	w1, w4
	add	x0, x19, x0, lsl 2
	add	x2, x19, x2, lsl 2
	ldr	w2, [x2, 13312]
	str	w2, [x0, 9044]
	bne	.L526
.L523:
	add	x22, x20, 2788
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
	add	x2, x20, 3044
	mov	x1, x19
	add	x22, x20, 3300
	mov	w21, 2
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 3108
	mov	x1, x19
	mov	w0, 5
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 3172
	mov	x1, x19
	mov	w0, 0
	bl	HEVC_WriteQmatrix_16x16
	add	x2, x20, 3236
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
	add	x2, x20, 3556
	mov	x1, x19
	mov	w0, 0
	add	x22, x20, 3684
	mov	w21, 0
	bl	HEVC_WriteQmatrix_32x32
	add	x2, x20, 3620
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
	ldr	w4, [x19, 3988]
	orr	w1, w5, w2
	str	w0, [x19, 7880]
	str	w1, [x19, 7876]
	mov	w0, 0
	str	w4, [x19, 7908]
.L515:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L531:
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
.L532:
	ldr	x2, [x19, 4016]
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
	add	x0, x0, 560
	ldrb	w1, [x0, 1]
	cbz	w1, .L535
	ldrsb	w1, [x19, 11]
	add	x0, x19, 8192
	add	x0, x0, 3692
	cbz	w1, .L567
.L535:
	ldp	w4, w5, [x0, 68]
	cmp	w4, 16
	bhi	.L568
	cmp	w5, 16
	bhi	.L539
	cbz	w4, .L540
	ldr	x0, [x19, 2448]
	cbz	x0, .L553
	ldr	x0, [x0, 16]
	cbz	x0, .L569
	add	x0, x19, 2456
	mov	w2, 0
	b	.L545
	.p2align 3
.L546:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L541
	ldr	x1, [x1, 16]
	cbz	x1, .L542
.L545:
	add	w2, w2, 1
	cmp	w4, w2
	bne	.L546
.L540:
	cbz	w5, .L555
	ldr	x0, [x19, 2584]
	cbz	x0, .L556
	ldr	x0, [x0, 16]
	cbz	x0, .L570
	add	x0, x19, 2592
	mov	w2, 0
	b	.L551
	.p2align 3
.L552:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L547
	ldr	x1, [x1, 16]
	cbz	x1, .L548
.L551:
	add	w2, w2, 1
	cmp	w5, w2
	bne	.L552
.L555:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L553:
	mov	w2, 0
	.p2align 2
.L541:
	ldr	x1, .LC159
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L537:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L569:
	mov	w2, 0
.L542:
	ldr	x1, .LC161
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L556:
	mov	w2, 0
.L547:
	ldr	x1, .LC163
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L570:
	mov	w2, 0
.L548:
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L567:
	ldr	x2, .LC151
	mov	w0, 0
	ldr	x1, .LC153
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, -1
	b	.L537
.L539:
	ldr	x1, .LC157
	mov	w3, 17
	mov	w2, w5
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L537
.L568:
	ldr	x1, .LC155
	mov	w3, 17
	mov	w2, w4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L537
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
	ldr	w24, [x19, 3960]
	bl	HEVC_CheckListX
	mov	w23, w0
	cbnz	w0, .L612
	ldr	w3, [x19, 152]
	ldr	w0, [x19, 204]
	cmp	w0, w3
	bcs	.L648
	mov	w21, 1368
	ldr	x22, .LC168
	ldr	x20, [x19, 2432]
	mov	x2, 1368
	umull	x0, w0, w21
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x20, x20, x0
	mov	x0, x20
	blr	x3
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 64
	add	x0, x29, 96
	blr	x3
	ldr	w0, [x19, 204]
	ldr	w1, [x19, 152]
	add	w0, w0, 1
	str	w0, [x19, 204]
	cmp	w0, w1
	bcc	.L649
	str	xzr, [x20, 1360]
.L575:
	ldr	w21, [x19, 176]
	ldr	w0, [x19, 236]
	ldr	w1, [x19, 4692]
	add	w21, w21, 1
	ldr	x3, [x19, 2368]
	add	w0, w0, 1
	str	w21, [x19, 176]
	str	w1, [x19, 208]
	str	w0, [x19, 236]
	ldrb	w1, [x3]
	ldr	w0, [x3, 8]
	cmp	w1, 1
	ccmp	w1, w0, 2, ls
	bcs	.L576
	.p2align 2
.L577:
	uxtw	x0, w1
	lsl	x2, x0, 5
	add	x3, x3, x2
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 60]
	str	w3, [x0, 8]
	ldr	x3, [x19, 2368]
	add	x3, x3, x2
	ldr	w3, [x3, 56]
	str	w3, [x20, w1, uxtw 2]
	add	w1, w1, 1
	ldr	x3, [x19, 2368]
	add	x2, x3, x2
	ldr	w2, [x2, 64]
	str	w2, [x0, 16]
	ldr	x3, [x19, 2368]
	ldr	w0, [x3, 8]
	cmp	w0, w1
	ccmp	w1, 1, 2, hi
	bls	.L577
.L576:
	cmp	w0, 1
	bhi	.L582
	.p2align 2
.L633:
	add	x1, x20, x0, uxtw 2
	str	wzr, [x1, 8]
	str	wzr, [x20, w0, uxtw 2]
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 16]
	bne	.L633
.L582:
	add	x26, x19, 4096
	add	x25, x19, 8192
	ldrb	w0, [x26, 561]
	cbz	w0, .L650
.L580:
	ldr	w0, [x19, 11952]
	cbz	w0, .L583
	mov	w1, 0
	.p2align 2
.L584:
	uxtw	x0, w1
	add	x5, x29, 160
	add	w1, w1, 1
	add	x2, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x3, [x2, 2448]
	ldr	w3, [x3, 4]
	str	w3, [x0, 116]
	ldr	x4, [x2, 2448]
	ldr	x2, [x4, 16]
	ldp	w3, w2, [x2, 20]
	add	x3, x19, x3, lsl 2
	add	x2, x5, x2, lsl 2
	ldr	w3, [x3, 8100]
	str	w3, [x2, -64]
	ldr	x2, [x4, 16]
	ldr	w2, [x2, 24]
	str	w2, [x0, 372]
	ldr	w0, [x19, 11952]
	cmp	w0, w1
	bhi	.L584
	ldr	w3, [x19, 11956]
	cbz	w3, .L585
.L611:
	mov	w1, 0
	.p2align 2
.L586:
	uxtw	x0, w1
	add	x5, x29, 160
	add	w1, w1, 1
	add	x2, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x3, [x2, 2584]
	ldr	w3, [x3, 4]
	str	w3, [x0, 180]
	ldr	x4, [x2, 2584]
	ldr	x2, [x4, 16]
	ldp	w3, w2, [x2, 20]
	add	x3, x19, x3, lsl 2
	add	x2, x5, x2, lsl 2
	ldr	w3, [x3, 8100]
	str	w3, [x2, -64]
	ldr	x2, [x4, 16]
	ldr	w2, [x2, 24]
	str	w2, [x0, 436]
	ldr	w3, [x19, 11956]
	cmp	w3, w1
	bhi	.L586
	ldr	w0, [x19, 11952]
.L585:
	cbz	w0, .L587
	uxtw	x1, w24
	ldr	w2, [x20, 372]
	lsl	x4, x1, 3
	ldr	w5, [x19, 3964]
	sub	x4, x4, x1
	lsl	x6, x4, 3
	sub	x4, x6, x4
	add	x4, x4, x1
	add	x1, x4, x2
	add	x1, x19, x1, lsl 2
	ldr	w1, [x1, 13376]
	cmp	w5, w1
	blt	.L618
	sub	w0, w0, #1
	mov	x1, x20
	add	x2, x20, x0, lsl 2
	b	.L590
	.p2align 3
.L591:
	ldr	w0, [x1, 376]
	add	x1, x1, 4
	add	x0, x4, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13376]
	cmp	w0, w5
	bgt	.L618
.L590:
	cmp	x2, x1
	bne	.L591
.L587:
	ldr	w0, [x19, 11904]
	cbnz	w0, .L647
	mov	w0, 1
	cbz	w3, .L588
	uxtw	x1, w24
	ldr	w0, [x20, 436]
	lsl	x2, x1, 3
	ldr	w4, [x19, 3964]
	sub	x2, x2, x1
	lsl	x5, x2, 3
	sub	x2, x5, x2
	add	x1, x2, x1
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13376]
	cmp	w4, w0
	blt	.L618
	sub	w3, w3, #1
	mov	x2, x20
	add	x3, x20, x3, lsl 2
	b	.L593
	.p2align 3
.L594:
	ldr	w0, [x2, 440]
	add	x2, x2, 4
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 13376]
	cmp	w0, w4
	bgt	.L618
.L593:
	cmp	x2, x3
	bne	.L594
.L647:
	mov	w0, 1
.L588:
	strb	w0, [x20, 24]
	ldrb	w0, [x26, 561]
	strb	w0, [x20, 25]
	ldr	w0, [x19, 11900]
	str	w0, [x20, 28]
	ldrb	w1, [x25, 3699]
	strb	w1, [x20, 32]
	ldr	w1, [x19, 11924]
	str	w1, [x20, 36]
	ldr	x2, [x19, 4016]
	ldr	w3, [x19, 204]
	ldr	w4, [x2, 316]
	sub	w1, w3, #1
	madd	w0, w1, w4, w0
	udiv	w0, w0, w3
	str	w0, [x2, 68]
	ldr	w0, [x19, 11904]
	cbz	w0, .L651
	cmp	w0, 1
	mov	w24, 0
	beq	.L596
.L597:
	str	w24, [x20, 40]
	ldr	w0, [x19, 11928]
	str	w0, [x20, 48]
	ldrb	w0, [x25, 3700]
	strb	w0, [x20, 52]
	ldr	w0, [x19, 11932]
	str	w0, [x20, 44]
	ldr	w0, [x19, 11960]
	cbz	w0, .L598
	sub	w0, w0, #1
	str	w0, [x20, 60]
.L599:
	ldr	w0, [x19, 11964]
	cbz	w0, .L600
	sub	w0, w0, #1
	str	w0, [x20, 56]
.L601:
	ldrb	w0, [x25, 3696]
	strb	w0, [x20, 64]
	ldrb	w0, [x25, 3698]
	strb	w0, [x20, 65]
	ldr	w0, [x19, 11952]
	str	w0, [x20, 68]
	ldr	w0, [x19, 11956]
	str	w0, [x20, 72]
	ldr	w0, [x19, 11904]
	str	w0, [x20, 76]
	ldr	w0, [x19, 4696]
	str	w0, [x20, 80]
	ldr	x0, [x19, 2392]
	ldr	w3, [x19, 4696]
	ldr	w1, [x0, 188]
	mov	x0, x19
	udiv	w2, w3, w1
	msub	w1, w2, w1, w3
	str	w1, [x20, 84]
	ldr	x1, [x19, 2392]
	ldr	w2, [x1, 188]
	ldr	w1, [x19, 4696]
	udiv	w1, w1, w2
	str	w1, [x20, 88]
	ldr	w1, [x19, 4696]
	bl	HEVC_CtbRsAddrToTsAddr
	str	w0, [x20, 92]
	ldr	w0, [x19, 11936]
	str	w0, [x20, 96]
	ldr	w0, [x19, 11940]
	str	w0, [x20, 100]
	ldr	w0, [x19, 11948]
	str	w0, [x20, 104]
	ldr	w0, [x19, 11944]
	str	w0, [x20, 108]
	ldrb	w0, [x25, 3695]
	strb	w0, [x20, 112]
	ldrb	w0, [x25, 3694]
	strb	w0, [x20, 113]
	ldrb	w0, [x25, 3701]
	strb	w0, [x20, 114]
	ldrb	w0, [x25, 3702]
	strb	w0, [x20, 115]
	ldr	x0, [x19, 2400]
	ldrb	w1, [x0, 10]
	cbz	w1, .L602
	ldr	w1, [x19, 11904]
	cmp	w1, 1
	beq	.L603
.L602:
	ldrb	w0, [x0, 11]
	cmp	w0, 1
	beq	.L652
.L605:
	ldrb	w0, [x25, 3696]
	cbz	w0, .L607
	add	x0, x29, 160
	add	x24, x0, x24, sxtw 2
	ldr	w0, [x24, -64]
	str	w0, [x20, 564]
.L608:
	ldr	x0, [x19, 2408]
	ldr	x1, [x19, 2368]
	str	x1, [x0, w21, uxtw 3]
	str	xzr, [x19, 2368]
	ldrb	w0, [x26, 2753]
	cbz	w0, .L626
	ldr	w0, [x19, 236]
	cmp	w0, 1
	beq	.L653
	sub	w1, w0, #2
	ldr	w2, [x20, 92]
	sub	w0, w0, #1
	add	x1, x19, x1, lsl 3
	sub	w2, w2, #1
	add	x3, x19, x0, lsl 3
	str	w2, [x1, 10216]
	ldr	w1, [x20, 92]
	str	w1, [x3, 10212]
.L610:
	ldr	w1, [x19, 6644]
	add	x0, x19, x0, lsl 3
	ldr	w2, [x19, 6648]
	mov	w3, 36863
	madd	w2, w1, w2, w2
	add	w1, w2, w1
	str	w1, [x0, 10216]
	ldr	w1, [x20, 92]
	sub	w1, w1, #1
	cmp	w1, w3
	bhi	.L626
	mov	x0, x19
	bl	HEVC_CtbTsAddrToRsAddr
	str	w0, [x20, 568]
.L626:
	mov	w0, w23
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L649:
	ldr	x1, [x19, 2432]
	umull	x0, w0, w21
	add	x0, x1, x0
	str	x0, [x20, 1360]
	b	.L575
	.p2align 3
.L618:
	mov	w0, 0
	b	.L588
	.p2align 3
.L600:
	str	wzr, [x20, 56]
	b	.L601
	.p2align 3
.L607:
	ldr	w0, [x19, 8100]
	str	w0, [x20, 564]
	b	.L608
	.p2align 3
.L598:
	str	wzr, [x20, 60]
	b	.L599
	.p2align 3
.L651:
	ldrb	w0, [x25, 3700]
	cbnz	w0, .L596
	ldrsw	x0, [x19, 11928]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 436]
	b	.L597
	.p2align 3
.L596:
	ldrsw	x0, [x19, 11928]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 372]
	b	.L597
	.p2align 3
.L650:
	ldr	x3, [x22, 104]
	mov	x2, 1356
	add	x1, x26, 560
	add	x0, x25, 3692
	blr	x3
	mov	w0, 1
	strb	w0, [x19, 11]
	b	.L580
	.p2align 3
.L652:
	ldr	w0, [x19, 11904]
	cbnz	w0, .L605
.L603:
	ldr	w0, [x19, 12040]
	mov	x2, 64
	str	w0, [x20, 580]
	add	x1, x25, 3984
	ldr	x3, [x22, 104]
	add	x27, x19, 12288
	ldr	w0, [x19, 12172]
	str	w0, [x20, 584]
	add	x0, x20, 588
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 64
	add	x1, x25, 3852
	add	x0, x20, 716
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 128
	add	x1, x25, 4048
	add	x0, x20, 844
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 128
	add	x1, x27, 80
	add	x0, x20, 1100
	blr	x3
	ldr	w0, [x19, 11904]
	cbnz	w0, .L605
	ldr	x3, [x22, 104]
	add	x1, x27, 208
	mov	x2, 64
	add	x0, x20, 652
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x25, 3916
	mov	x2, 64
	add	x0, x20, 780
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x27, 272
	mov	x2, 128
	add	x0, x20, 972
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 128
	add	x1, x27, 400
	add	x0, x20, 1228
	blr	x3
	b	.L605
	.p2align 3
.L653:
	ldr	w1, [x20, 92]
	mov	x0, 0
	str	w1, [x19, 10212]
	b	.L610
.L583:
	ldr	w0, [x19, 11956]
	cbnz	w0, .L611
	mov	w0, 1
	b	.L588
.L612:
	mov	w23, -1
	b	.L626
.L648:
	ldr	x1, .LC167
	mov	w2, w0
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L626
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
	ldr	w1, [x19, 3980]
	ldr	w0, [x19, 204]
	ldr	w2, [x19, 3984]
	cmp	w1, wzr
	str	w0, [x19, 9112]
	cset	w1, eq
	str	w2, [x19, 7956]
	mov	w0, 0
	str	w1, [x19, 7964]
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
	ldr	w3, [x19, 4692]
	ldr	w4, [x19, 164]
	tbnz	w3, #31, .L659
	cmp	w3, w4
	bge	.L659
	ldr	x0, [x19, 2352]
	mov	w1, 1888
	ldr	w4, [x19, 160]
	smaddl	x3, w3, w1, x0
	ldr	w3, [x3, 32]
	tbnz	w3, #31, .L663
	cmp	w3, w4
	bge	.L663
	add	x20, x19, 4096
	ldr	x2, [x19, 2344]
	mov	w4, 12660
	ldr	w5, [x19, 5588]
	ldr	w6, [x20, 1496]
	mov	w0, 1
	smaddl	x3, w3, w4, x2
	ldr	w9, [x20, 1500]
	add	w8, w5, w6
	ldr	w2, [x3, 116]
	cmp	w8, w9
	mov	w3, w8
	lsl	w2, w0, w2
	bcs	.L675
	cmp	w8, 15
	bgt	.L666
	ldr	w4, [x19, 3964]
	b	.L668
	.p2align 3
.L686:
	cmp	w9, w3
	bls	.L675
	cmp	w3, 16
	beq	.L666
.L668:
	add	x0, x19, x3, sxtw 2
	mov	w1, w4
	add	w3, w3, 1
	ldr	w7, [x0, 4744]
	ldr	w0, [x0, 5688]
	cbnz	w7, .L669
	sdiv	w1, w4, w2
	sdiv	w7, w0, w2
	msub	w1, w1, w2, w4
	msub	w0, w7, w2, w0
.L669:
	cmp	w1, w0
	bne	.L686
	mov	w21, 1
.L665:
	cbz	w8, .L661
	ldr	w3, [x19, 4668]
	add	x1, x20, 1528
	ldr	w0, [x20, 1524]
	mov	w4, 0
	ldr	w2, [x19, 3964]
	add	w0, w3, w0
	cmp	w2, w0
	bne	.L673
	b	.L679
	.p2align 3
.L672:
	ldr	w0, [x1], 4
	add	w0, w3, w0
	cmp	w0, w2
	beq	.L679
.L673:
	add	w4, w4, 1
	cmp	w4, w8
	beq	.L661
	cmp	w4, 17
	bne	.L672
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
.L663:
	ldr	x1, .LC172
	mov	w2, 8927
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
.L661:
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L659:
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
.L675:
	mov	w21, 0
	b	.L665
	.p2align 3
.L666:
	ldr	x1, .LC174
	mov	w5, w9
	mov	w4, 16
	mov	w2, 8947
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	w5, [x19, 5588]
	ldr	w6, [x20, 1496]
	add	w8, w5, w6
	b	.L665
	.p2align 3
.L679:
	mov	w21, 1
	b	.L661
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
	ldr	x1, [x20, 2384]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	beq	.L690
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L690:
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
	ldr	x4, [x19, 2336]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 156]
	ldr	x1, [x19, 2336]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 2384]
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
	ldr	x1, [x20, 2392]
	ldr	w0, [x19, 56]
	ldr	w1, [x1, 56]
	cmp	w1, w0
	beq	.L695
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L695:
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
	ldr	x4, [x19, 2344]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 160]
	ldr	x1, [x19, 2344]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 2392]
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
	ldr	x1, [x20, 2400]
	ldr	w0, [x19, 28]
	ldr	w1, [x1, 28]
	cmp	w1, w0
	beq	.L700
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L700:
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
	cbz	w0, .L702
	ldrb	w0, [x19, 15]
	cbnz	w0, .L722
	ldr	w0, [x19, 68]
	ldr	w2, [x21, 188]
	sub	w3, w0, #1
	add	x1, x19, x0, sxtw 1
	cmp	w3, wzr
	strh	w2, [x1, 170]
	ble	.L714
	sub	w4, w0, #2
	add	x0, x19, 88
	add	x4, x4, 45
	add	x4, x19, x4, lsl 1
	.p2align 2
.L713:
	ldrsh	w3, [x0]
	add	x0, x0, 2
	strh	w3, [x0, 82]
	cmp	x0, x4
	ldrh	w2, [x1, 170]
	sub	w2, w2, w3
	strh	w2, [x1, 170]
	bne	.L713
.L714:
	ldr	w0, [x19, 72]
	ldr	w1, [x21, 192]
	sub	w2, w0, #1
	add	x3, x19, x0, sxtw 1
	cmp	w2, wzr
	strh	w1, [x3, 210]
	ble	.L709
	sub	w4, w0, #2
	add	x0, x19, 128
	add	x4, x4, 65
	add	x4, x19, x4, lsl 1
	.p2align 2
.L715:
	ldrsh	w2, [x0]
	add	x0, x0, 2
	strh	w2, [x0, 82]
	cmp	x4, x0
	ldrh	w1, [x3, 210]
	sub	w1, w1, w2
	strh	w1, [x3, 210]
	bne	.L715
	b	.L709
	.p2align 3
.L702:
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L709:
	ldr	w0, [x20, 164]
	mov	w22, 1888
	ldr	x1, .LC181
	mov	x21, -1888
	ldr	x4, [x20, 2352]
	mov	x2, 1888
	smaddl	x0, w0, w22, x21
	ldr	x3, [x1, 104]
	mov	x1, x19
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x20, 164]
	ldr	x1, [x20, 2352]
	smaddl	x0, w0, w22, x21
	add	x0, x1, x0
	str	x0, [x20, 2400]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L722:
	ldr	w4, [x19, 68]
	add	x1, x19, 172
	mov	w3, 0
	cmp	w4, wzr
	ble	.L708
	.p2align 2
.L717:
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
	bne	.L717
.L708:
	ldr	w4, [x19, 72]
	add	x1, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L709
	.p2align 2
.L716:
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
	bne	.L716
	b	.L709
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
	ldr	w1, [x19, 4684]
	mov	w3, 1
	ldr	x0, [x19, 2392]
	ldr	w2, [x19, 4668]
	strb	w3, [x19, 3953]
	str	w1, [x19, 3956]
	mov	w1, -1
	str	w2, [x19, 3964]
	str	w1, [x19, 3984]
	ldrsw	x3, [x19, 252]
	ldr	w4, [x0, 64]
	ldr	x1, .LC182
	str	w4, [x19, 3972]
	ldr	x1, [x1, x3, lsl 3]
	ldr	w0, [x0, 68]
	str	w0, [x19, 3976]
	str	wzr, [x19, 3980]
	ldrsb	w0, [x1, 44]
	cmp	w0, 1
	beq	.L731
.L724:
	ldr	x1, [x19, 2424]
	mov	x2, -1
	add	x0, x19, 4024
	ldr	x3, [x1, 56]
	str	x3, [x19, 4608]
	ldr	x3, [x1, 72]
	str	x3, [x19, 4616]
	ldr	x3, [x1, 88]
	str	x3, [x19, 4624]
	ldr	w3, [x1, 104]
	str	w3, [x19, 4024]
	ldr	w3, [x1, 108]
	str	w3, [x19, 4028]
	ldr	w3, [x1, 112]
	str	w3, [x19, 4032]
	ldr	w3, [x1, 128]
	str	w3, [x19, 4036]
	str	x2, [x1, 56]
	ldr	x1, [x19, 2392]
	ldrb	w2, [x19, 4088]
	ldr	w3, [x1, 64]
	str	w3, [x19, 4092]
	ldr	w3, [x1, 68]
	str	w3, [x19, 4096]
	str	wzr, [x19, 4076]
	ldr	w4, [x1, 60]
	ldr	w3, [x1, 2084]
	cmp	w4, 1
	bfi	w2, w3, 5, 3
	cset	w3, ne
	bfi	w2, w3, 2, 3
	strb	w2, [x19, 4088]
	ldr	w1, [x1, 2068]
	and	w1, w1, 7
	bl	SetAspectRatio
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4668]
	str	w1, [x0, 8]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4088]
	str	w1, [x0, 144]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4076]
	str	w1, [x0, 132]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4128]
	str	w1, [x0, 184]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4124]
	str	w1, [x0, 180]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4092]
	str	w1, [x0, 148]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4096]
	str	w1, [x0, 152]
	ldr	x1, [x19, 4016]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L727
	ldr	w3, [x19, 4076]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 252]
	cset	w3, ne
	bl	FSP_SetStoreType
.L727:
	ldr	x0, [x19, 2392]
	ldr	x4, [x19, 4016]
	ldr	w1, [x0, 72]
	str	w1, [x19, 4244]
	ldr	w3, [x0, 76]
	str	w3, [x19, 4248]
	ldr	w6, [x0, 80]
	str	w6, [x19, 4252]
	ldr	w5, [x0, 84]
	str	w5, [x19, 4256]
	ldr	w2, [x0, 64]
	sub	w1, w2, w1
	sub	w1, w1, w3
	str	w1, [x19, 4100]
	ldr	w3, [x0, 68]
	sub	w2, w3, w6
	sub	w2, w2, w5
	str	w2, [x19, 4104]
	ldr	w2, [x0, 60]
	str	w2, [x19, 4188]
	ldr	w2, [x0, 88]
	str	w2, [x19, 4192]
	ldr	w0, [x0, 96]
	str	w0, [x19, 4196]
	ldr	w0, [x4, 164]
	str	w0, [x19, 4108]
	ldr	w0, [x4, 168]
	str	w0, [x19, 4112]
	str	w1, [x4, 156]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4104]
	str	w1, [x0, 160]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4108]
	str	w1, [x0, 164]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4112]
	str	w1, [x0, 168]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4192]
	str	w1, [x0, 248]
	ldr	x0, [x19, 4016]
	ldr	w1, [x19, 4196]
	str	w1, [x0, 252]
	str	wzr, [x19, 3968]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L731:
	ldr	w0, [x1, 156]
	cbnz	w0, .L724
	ldr	w0, [x1, 160]
	cmp	w0, 1
	bne	.L724
	add	x0, x19, 8192
	ldrb	w0, [x0, 3632]
	cmp	w0, 1
	bne	.L724
	ldr	x1, [x19, 11856]
	ldr	x0, [x19, 11872]
	cmp	x1, x0
	bls	.L725
	sub	x3, x1, x0
	cmp	x3, 16
	bls	.L725
.L726:
	ldr	w1, [x19, 260]
	sub	w2, w2, w1
	add	x0, x0, x2, sxtw
	str	x0, [x19, 11856]
	b	.L724
.L725:
	cmp	x1, x0
	bcs	.L724
	sub	x1, x0, x1
	cmp	x1, 16
	bls	.L724
	b	.L726
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
	ldr	w3, [x26, 4676]
	cmp	w3, 1
	beq	.L734
	cmp	w3, 2
	beq	.L750
	cbz	w3, .L749
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
.L737:
	ldr	x0, [x26, 2424]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L745
	mov	w0, 1
	str	w0, [x28]
	ldr	x0, [x26, 4016]
	add	x0, x0, 56
	str	x0, [x23, -8]
	.p2align 2
.L745:
	add	w27, w27, 1
	add	x28, x28, 4
	cmp	w27, w22
	add	x23, x23, 136
	bcc	.L747
.L750:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L749:
	mov	w22, 2
.L736:
	ldr	x21, .LC183
	add	x28, x26, 4096
	add	x28, x28, 628
	add	x23, x26, 2456
	add	x0, x21, 280
	mov	w27, 0
	str	x0, [x29, 104]
	.p2align 2
.L747:
	ldr	w1, [x28]
	cbz	w1, .L737
	ldr	x2, [x23, -8]
	cbnz	x2, .L751
	mov	x3, x23
	mov	w0, 0
	b	.L739
	.p2align 3
.L741:
	ldr	x24, [x3], 8
	cbnz	x24, .L756
.L739:
	add	w0, w0, 1
	cmp	w1, w0
	bne	.L741
	mov	w20, -1
.L740:
	ldr	x0, [x26, 2424]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L742
	ldr	x24, [x26, 4016]
	add	x24, x24, 56
.L738:
	mov	x0, x2
	uxtw	x25, w27
	mov	w19, 0
	lsl	x21, x25, 4
	cbz	x0, .L757
	.p2align 2
.L743:
	add	w19, w19, 1
	add	x0, x21, x25
	cmp	w1, w19
	add	x0, x0, x19, uxtw
	add	x0, x0, 306
	bls	.L745
	ldr	x0, [x26, x0, lsl 3]
	cbnz	x0, .L743
.L757:
	ldr	x1, .LC189
	mov	w4, w19
	ldr	x2, [x29, 104]
	mov	w5, w20
	mov	w3, w27
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x21, x25
	add	x0, x0, x19, uxtw
	add	x0, x0, 306
	str	x24, [x26, x0, lsl 3]
	ldr	w1, [x28]
	b	.L743
	.p2align 3
.L756:
	sxtb	w20, w0
	cmn	w20, #1
	ccmp	x24, xzr, 4, ne
	bne	.L738
	b	.L740
	.p2align 3
.L751:
	mov	x24, x2
	mov	w20, 0
	b	.L738
.L734:
	mov	w22, w3
	b	.L736
.L742:
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
	cbz	x19, .L794
	ldr	x20, .LC191
	add	x21, x29, 48
	mov	x2, 272
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x20, 96]
	blr	x3
	ldr	w0, [x19, 2776]
	cbz	w0, .L795
	sub	w3, w0, #1
	mov	w5, 0
	add	x3, x3, 366
	add	x0, x19, 2920
	add	x3, x19, x3, lsl 3
	b	.L762
	.p2align 3
.L761:
	cmp	x0, x3
	beq	.L760
.L762:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L761
	ldr	w2, [x1, 60]
	cbnz	w2, .L761
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L761
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x5, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w5, w5, 1
	str	x1, [x2, 3824]
	bne	.L762
	.p2align 2
.L760:
	ldr	w0, [x19, 2780]
	cbz	w0, .L796
	sub	w3, w0, #1
	mov	w4, w5
	add	x3, x3, 383
	add	x0, x19, 3056
	add	x3, x19, x3, lsl 3
	b	.L765
	.p2align 3
.L764:
	cmp	x0, x3
	beq	.L823
.L765:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L764
	ldr	w2, [x1, 60]
	cbnz	w2, .L764
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L764
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x4, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w4, w4, 1
	str	x1, [x2, 3824]
	bne	.L765
	.p2align 2
.L823:
	sub	w6, w4, w5
.L763:
	ldr	w0, [x19, 2772]
	sub	w8, w4, #1
	cbz	w0, .L766
	sub	w2, w0, #1
	add	x0, x19, 3192
	add	x2, x2, 400
	add	x2, x19, x2, lsl 3
	b	.L768
	.p2align 3
.L767:
	cmp	x2, x0
	beq	.L824
.L768:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 1]
	cmp	w3, 1
	bne	.L767
	ldr	w3, [x1, 60]
	cmp	w3, 1
	bne	.L767
	ldr	w7, [x1, 64]
	add	x3, x29, 320
	add	x3, x3, x4, uxtw 3
	add	x1, x1, 56
	sub	x3, x3, #4096
	cbnz	w7, .L767
	str	x1, [x3, 3824]
	cmp	x2, x0
	add	w4, w4, 1
	bne	.L768
	.p2align 2
.L824:
	sub	w0, w4, w5
	sub	w0, w0, w6
.L766:
	cbz	w4, .L825
	ldr	w7, [x19, 4676]
	cbnz	w7, .L826
	cbz	w6, .L774
	add	x3, x21, 136
	add	w9, w6, w5
	mov	w1, w5
	.p2align 2
.L775:
	add	x2, x29, 320
	add	x2, x2, x1, uxtw 3
	add	w1, w1, 1
	sub	x2, x2, #4096
	cmp	w9, w1
	ldr	x2, [x2, 3824]
	str	x2, [x3], 8
	bne	.L775
.L774:
	cbz	w5, .L776
	mov	x1, 0
	.p2align 2
.L777:
	add	w2, w6, w1
	add	x9, x29, 320
	ldr	x3, [x21, x1, lsl 3]
	add	x1, x1, 1
	add	x2, x9, x2, lsl 3
	cmp	w5, w1
	str	x3, [x2, -136]
	bhi	.L777
	add	w6, w6, w5
.L776:
	cbz	w0, .L778
	add	w1, w0, w6
	mov	w2, w6
	.p2align 2
.L779:
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
	bne	.L779
.L778:
	ldr	w5, [x19, 4732]
	ldr	w8, [x19, 4736]
	str	w5, [x19, 4724]
	str	w8, [x19, 4728]
	cbnz	w5, .L772
	.p2align 2
.L792:
	cbz	w8, .L784
	add	x0, x19, 4096
	add	x3, x19, 2584
	add	x2, x0, 1788
	mov	w1, 0
	ldrb	w6, [x0, 1657]
	.p2align 2
.L787:
	cbz	w6, .L785
	ldr	w0, [x2]
.L786:
	add	x7, x29, 320
	add	w1, w1, 1
	add	x0, x7, x0, uxtw 3
	cmp	w1, w8
	add	x2, x2, 4
	ldr	x0, [x0, -136]
	str	x0, [x3], 8
	bne	.L787
	mov	w0, w5
.L783:
	cmp	w0, 16
	bhi	.L797
	.p2align 2
.L789:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 2448]
	add	w0, w0, 1
	cmp	w0, 16
	str	x2, [x1, 2448]
	bls	.L789
.L797:
	cmp	w8, 16
	mov	w0, w8
	bhi	.L790
	.p2align 2
.L791:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 2584]
	add	w0, w0, 1
	cmp	w0, 17
	str	x2, [x1, 2584]
	bne	.L791
.L790:
	mov	w0, 0
.L820:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L826:
	ldr	w5, [x19, 4732]
	ldr	w8, [x19, 4736]
	str	w5, [x19, 4724]
	str	w8, [x19, 4728]
	cbz	w5, .L827
.L772:
	add	x1, x19, 4096
	add	x3, x19, 2448
	add	x2, x1, 1660
	mov	w0, 0
	ldrb	w6, [x1, 1656]
	.p2align 2
.L782:
	cbz	w6, .L780
	ldr	w1, [x2]
.L781:
	add	x9, x29, 320
	add	w0, w0, 1
	add	x1, x9, x1, uxtw 3
	cmp	w0, w5
	sub	x1, x1, #4096
	add	x2, x2, 4
	ldr	x1, [x1, 3824]
	str	x1, [x3], 8
	bne	.L782
	cbnz	w7, .L783
	b	.L792
	.p2align 3
.L780:
	udiv	w1, w0, w4
	msub	w1, w1, w4, w0
	b	.L781
	.p2align 3
.L785:
	udiv	w0, w1, w4
	msub	w0, w0, w4, w1
	b	.L786
	.p2align 3
.L825:
	ldr	x3, [x20, 96]
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 2448
	str	wzr, [x19, 4724]
	str	wzr, [x19, 4728]
	blr	x3
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L790
	ldr	x1, [x19, 4016]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x19, 4724]
	add	x1, x1, 56
	str	x1, [x19, 2448]
	b	.L820
.L784:
	ldr	x3, [x20, 104]
	mov	x2, 136
	add	x1, x19, 2448
	add	x0, x19, 2584
	blr	x3
	ldr	w8, [x19, 4724]
	str	w8, [x19, 4728]
	mov	w0, w8
	b	.L783
.L795:
	mov	w5, 0
	b	.L760
.L796:
	mov	w4, w5
	mov	w6, 0
	b	.L763
.L827:
	mov	w0, 0
	b	.L789
.L794:
	mov	w0, -1
	b	.L820
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
	ldr	w0, [x19, 4676]
	cmp	w0, 2
	beq	.L834
	mov	x0, x19
	bl	HEVC_InitListX
	cbnz	w0, .L835
	mov	x0, x19
	bl	HEVC_RepairList
	mov	w1, 0
	cbnz	w0, .L836
.L830:
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L834:
	str	wzr, [x19, 4724]
	mov	w1, 0
	str	wzr, [x19, 4728]
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L835:
	ldr	x1, .LC193
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L830
.L836:
	ldr	x1, .LC195
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L830
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
	ldr	x0, [x19, 2392]
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
	bhi	.L838
	ldr	x3, .LC196
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 2424]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L847
	ldrsb	w2, [x19, 2760]
	strb	w2, [x29, 57]
.L843:
	ldr	w0, [x19, 252]
	add	x1, x29, 56
	strb	w2, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L848
	ldr	x1, [x19, 2424]
	add	x3, x29, 52
	ldr	w0, [x19, 252]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
.L845:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L847:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 57]
	b	.L843
	.p2align 3
.L838:
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
.L848:
	ldr	x2, .LC197
	mov	w0, 1
	ldr	x1, .LC201
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L845
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
	ldr	x1, [x0, 2784]
	ldr	w4, [x1, 32]
	cbnz	w4, .L852
	ldr	w0, [x1, 24]
	cmp	w0, 15
	bhi	.L849
	add	x0, x19, x0, uxtw 2
	mov	w2, 16
	str	wzr, [x0, 13248]
	str	wzr, [x0, 13312]
	str	wzr, [x0, 13376]
	ldr	w0, [x1, 20]
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 2132]
	str	w2, [x1, 24]
	ldr	w0, [x19, 13244]
	sub	w0, w0, #1
	str	w0, [x19, 13244]
.L849:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L852:
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
	ldr	w1, [x20, 2764]
	cbnz	w1, .L858
	b	.L853
	.p2align 3
.L855:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L853
.L858:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 2784]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L855
	mov	w1, w19
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	ldr	w1, [x20, 2764]
	cmp	w1, w19
	bhi	.L858
.L853:
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
	ldr	w2, [x23, 4692]
	mov	w5, 1888
	ldr	x1, [x23, 2352]
	mov	w4, 12660
	ldr	x0, [x23, 2344]
	ldr	w3, [x23, 2764]
	smaddl	x1, w2, w5, x1
	ldr	w1, [x1, 32]
	smaddl	x0, w1, w4, x0
	ldr	w24, [x0, 116]
	lsl	w24, w21, w24
	cbz	w3, .L860
	add	x19, x23, 4096
	mov	w22, w21
	add	x19, x19, 1492
	b	.L891
	.p2align 3
.L863:
	add	w25, w25, 1
	cmp	w3, w25
	bls	.L860
.L891:
	add	x26, x23, x25, sxtw 3
	ldr	w0, [x23, 4688]
	ldr	x1, [x26, 2784]
	ldr	w2, [x1, 32]
	cmp	w2, w0
	bne	.L863
	ldp	w3, w0, [x19]
	ldr	w2, [x19, 8]
	add	w0, w3, w0
	cmp	w0, w2
	mov	w20, w0
	bcs	.L902
	ldr	w0, [x1, 8]
	mov	w4, 0
	.p2align 2
.L871:
	add	x2, x23, x20, sxtw 2
	ldr	w3, [x2, 4744]
	cbz	w3, .L866
	ldr	w3, [x1, 60]
	cbz	w3, .L867
	ldr	w3, [x2, 5688]
	cmp	w3, w0
	beq	.L901
.L867:
	cbnz	w4, .L899
	ldrb	w4, [x1, 1]
	ldr	w3, [x2, 5688]
	mov	w2, w0
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	beq	.L903
.L882:
	mov	w2, w0
	mov	w4, 0
.L870:
	ldr	w3, [x19, 8]
	add	w20, w20, 1
	mov	w0, w2
	cmp	w3, w20
	bhi	.L871
	ldp	w3, w0, [x19]
	add	w0, w3, w0
.L865:
	ldr	w5, [x23, 4668]
	cbz	w0, .L873
	mov	w20, 0
	.p2align 2
.L875:
	ldr	w0, [x1, 60]
	add	x3, x19, x20, sxtw 2
	add	w20, w20, 1
	cbnz	w0, .L874
	ldr	w0, [x3, 32]
	add	w0, w5, w0
	cmp	w0, w2
	beq	.L904
.L874:
	ldp	w3, w0, [x19]
	add	w0, w3, w0
	cmp	w0, w20
	bhi	.L875
.L873:
	cmp	w4, wzr
	ccmp	w2, w5, 4, eq
	beq	.L900
	strb	wzr, [x1, 1]
	ldr	x0, [x26, 2784]
	str	wzr, [x0, 60]
	ldr	x0, [x26, 2784]
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L900
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
.L900:
	ldr	w3, [x23, 2764]
	add	w25, w25, 1
	cmp	w3, w25
	bhi	.L891
.L860:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L866:
	ldr	w3, [x1, 60]
	cbz	w3, .L869
	sdiv	w3, w0, w24
	ldr	w6, [x2, 5688]
	sdiv	w5, w6, w24
	msub	w3, w3, w24, w0
	msub	w5, w5, w24, w6
	cmp	w3, w5
	bne	.L869
.L901:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2784]
	str	w21, [x0, 48]
	ldr	x0, [x26, 2784]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
	ldr	x1, [x26, 2784]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L870
	.p2align 3
.L869:
	cbnz	w4, .L899
	ldr	w4, [x2, 5688]
	sdiv	w2, w0, w24
	sdiv	w3, w4, w24
	msub	w2, w2, w24, w0
	msub	w3, w3, w24, w4
	ldrb	w4, [x1, 1]
	cmp	w4, wzr
	ccmp	w2, w3, 0, ne
	bne	.L882
.L903:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2784]
	str	w21, [x0, 60]
	ldr	x0, [x26, 2784]
	str	w21, [x0, 48]
	ldr	x0, [x26, 2784]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 252]
	bl	FSP_SetRef
	ldr	x1, [x26, 2784]
	mov	w4, 1
	ldr	w2, [x1, 8]
	b	.L870
	.p2align 3
.L899:
	mov	w2, w0
	b	.L870
	.p2align 3
.L904:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x26, 2784]
	str	w21, [x0, 48]
	ldr	x1, [x26, 2784]
	ldr	w0, [x23, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x26, 2784]
	mov	w4, 1
	ldr	w5, [x23, 4668]
	ldr	w2, [x1, 8]
	b	.L874
.L902:
	mov	w4, 0
	ldr	w2, [x1, 8]
	b	.L865
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
	ldr	w0, [x19, 4684]
	sub	w0, w0, #19
	cmp	w0, 2
	bls	.L907
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L907:
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
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 612]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L909
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.8
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L909:
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
	add	x2, x2, 1152
	add	x5, x5, 3104
	mov	w0, 0
	.p2align 2
.L916:
	ldr	w1, [x2, 48]
	cbnz	w1, .L912
	cbz	x2, .L913
	ldr	w4, [x19, 2764]
	cbz	w4, .L913
	ldr	x1, [x19, 2784]
	cmp	x1, x2
	beq	.L912
	sub	w4, w4, #1
	mov	x1, x19
	add	x4, x19, x4, lsl 3
	b	.L914
	.p2align 3
.L915:
	ldr	x3, [x1, 2784]
	cmp	x3, x2
	beq	.L912
.L914:
	cmp	x4, x1
	add	x1, x1, 8
	bne	.L915
.L913:
	add	w0, w0, 1
.L912:
	add	x2, x2, 712
	cmp	x2, x5
	bne	.L916
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
	ldr	w1, [x20, 5588]
	cbz	w1, .L946
	add	x24, x20, 4096
	mov	w22, 0
	mov	w21, 0
	add	x23, x24, 1492
	mov	w26, 1
	mov	w25, 1
	.p2align 2
.L932:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L928
	add	x0, x0, 8
	ldr	w5, [x20, 2764]
	ldr	w4, [x20, 4668]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L928
	add	x1, x20, 2784
	mov	w0, 0
	b	.L931
	.p2align 3
.L929:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L928
.L931:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L929
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 4688]
	cmp	w6, w3
	bne	.L929
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 2784]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L974
.L930:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 2784]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 2784]
	str	x1, [x0, 2920]
	.p2align 2
.L928:
	ldr	w1, [x23]
	add	w21, w21, 1
	cmp	w1, w21
	bhi	.L932
.L927:
	ldr	w0, [x20, 2760]
	str	w22, [x20, 2776]
	cmp	w0, w22
	bls	.L937
	.p2align 2
.L961:
	add	x2, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w22, w0
	str	xzr, [x2, 2920]
	bne	.L961
.L937:
	add	x23, x24, 1492
	mov	w22, 0
	mov	w26, 1
	mov	w25, 1
	ldr	w24, [x23, 4]
	add	w24, w1, w24
	cmp	w24, w21
	bls	.L935
	.p2align 2
.L960:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L938
	add	x0, x0, 8
	ldr	w5, [x20, 2764]
	ldr	w4, [x20, 4668]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L938
	add	x1, x20, 2784
	mov	w0, 0
	b	.L941
	.p2align 3
.L939:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L938
.L941:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L939
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 4688]
	cmp	w6, w3
	bne	.L939
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 2784]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L975
.L940:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 2784]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 2784]
	str	x1, [x0, 3056]
	.p2align 2
.L938:
	add	w21, w21, 1
	cmp	w24, w21
	bhi	.L960
	ldr	w0, [x20, 2760]
.L935:
	cmp	w0, w22
	str	w22, [x20, 2780]
	bls	.L926
	.p2align 2
.L959:
	add	x1, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w0, w22
	str	xzr, [x1, 3056]
	bne	.L959
.L926:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L974:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	ldr	x0, [x19, 2784]
	b	.L930
.L975:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 252]
	bl	FSP_SetRef
	ldr	x0, [x19, 2784]
	b	.L940
.L946:
	mov	w22, 0
	mov	w21, 0
	add	x24, x20, 4096
	b	.L927
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
	ldr	w3, [x19, 4692]
	mov	w2, 1888
	ldr	x0, [x19, 2352]
	mov	w5, 12660
	ldr	w6, [x19, 5588]
	add	x1, x19, 4096
	ldr	w9, [x19, 5596]
	add	x1, x1, 1492
	smaddl	x2, w3, w2, x0
	ldr	w0, [x19, 5592]
	sub	w9, w9, #1
	ldr	x4, [x19, 2344]
	mov	w3, 1
	ldr	w2, [x2, 32]
	add	w0, w6, w0
	sub	w0, w0, #1
	cmp	w9, w0
	smaddl	x0, w2, w5, x4
	ldr	w0, [x0, 116]
	lsl	w0, w3, w0
	ble	.L986
	mov	w10, 0
	mov	x11, x1
	sub	w7, w0, #1
	mov	w13, w3
	mov	w12, w3
	.p2align 2
.L983:
	sxtw	x0, w9
	add	x1, x11, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L978
	add	x0, x19, x0, lsl 2
	ldr	w8, [x19, 2764]
	ldr	w6, [x0, 4744]
	ldr	w5, [x0, 5688]
	uxtb	w6, w6
	and	w0, w5, w7
	cmp	w6, wzr
	csel	w5, w0, w5, eq
	cmp	w8, wzr
	ble	.L978
	add	x2, x19, 2784
	mov	w1, 0
	b	.L982
	.p2align 3
.L981:
	add	w1, w1, 1
	cmp	w1, w8
	beq	.L978
.L982:
	ldr	x3, [x2]
	cmp	w6, wzr
	add	x2, x2, 8
	ldr	w0, [x3, 8]
	and	w4, w0, w7
	csel	w0, w4, w0, eq
	cmp	w5, w0
	bne	.L981
	ldr	w4, [x3, 32]
	ldr	w0, [x19, 4688]
	cmp	w4, w0
	bne	.L981
	add	x1, x19, x1, sxtw 3
	strb	w13, [x3, 1]
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	ldr	x2, [x1, 2784]
	str	wzr, [x2, 64]
	ldr	x2, [x1, 2784]
	str	w12, [x2, 60]
	ldr	x1, [x1, 2784]
	str	x1, [x0, 3192]
	.p2align 2
.L978:
	ldp	w1, w0, [x11]
	sub	w9, w9, #1
	add	w0, w1, w0
	sub	w0, w0, #1
	cmp	w0, w9
	blt	.L983
	mov	w0, w10
.L977:
	ldr	w1, [x19, 2760]
	str	w0, [x19, 2772]
	cmp	w1, w10
	ble	.L976
	.p2align 2
.L989:
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	cmp	w10, w1
	str	xzr, [x0, 3192]
	bne	.L989
.L976:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L986:
	mov	w0, 0
	mov	w10, 0
	b	.L977
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
	cbz	x23, .L1013
	ldr	w20, [x22, 3960]
	uxtw	x21, w20
	lsl	x0, x21, 2
	sub	x0, x0, x21
	add	x0, x21, x0, lsl 3
	add	x0, x22, x0, lsl 3
	ldr	w2, [x0, 13240]
	cbz	w2, .L997
	ldr	w0, [x0, 13248]
	cbz	w0, .L1014
	mov	w0, 200
	mov	x1, 13252
	mov	w19, 0
	umaddl	x0, w20, w0, x1
	add	x0, x22, x0
	b	.L1000
	.p2align 3
.L1003:
	ldr	w1, [x0], 4
	cbz	w1, .L998
.L1000:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L1003
.L997:
	ldr	x1, .LC214
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1010:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1014:
	mov	w19, 0
	.p2align 2
.L998:
	ldr	w0, [x22, 252]
	ldr	w1, [x23, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1001
	ldr	x1, [x0, 32]
	cbz	x1, .L1001
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
	str	w2, [x20, 13248]
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 13312]
	ldr	w0, [x23, 8]
	str	w0, [x20, 13376]
	mov	w0, 13
	ldr	w2, [x22, 13244]
	add	w2, w2, 1
	str	w2, [x22, 13244]
	ldr	w2, [x23, 228]
	bl	dprint_vfmw
	str	w19, [x23, 24]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1001:
	ldrb	w4, [x23, 1]
	mov	x5, x0
	ldr	x1, .LC212
	mov	x6, 0
	ldr	w3, [x23, 8]
	mov	w0, 0
	ldr	w2, [x23, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1010
.L1013:
	ldr	x2, .LC206
	mov	w3, 11486
	ldr	x1, .LC208
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1010
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
	cbz	x0, .L1016
	ldrsb	w4, [x0, 1]
	cmp	w4, 3
	ccmp	w4, wzr, 4, ne
	beq	.L1036
	ldr	w0, [x19, 52]
	cmp	w0, 1
	beq	.L1022
	ldr	w4, [x19, 48]
	ldrb	w5, [x19]
	cbz	w4, .L1021
	cmp	w5, 1
	mov	w0, 0
	beq	.L1021
.L1030:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1036:
	ldr	x2, .LC215
	mov	w0, 13
	ldr	x1, .LC217
	ldr	w3, [x19, 28]
	add	x2, x2, 336
	bl	dprint_vfmw
.L1018:
	ldr	w0, [x19, 52]
	cmp	w0, 1
	bne	.L1037
.L1022:
	mov	w1, 1
	mov	w0, 2
	strb	w1, [x19, 2]
	str	w0, [x19, 52]
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1016:
	ldr	x1, .LC219
	mov	x2, x19
	ldr	w3, [x19, 8]
	mov	w0, 1
	ldr	w5, [x19, 28]
	ldr	w4, [x19, 52]
	bl	dprint_vfmw
	b	.L1018
.L1037:
	ldr	x2, .LC215
	mov	w0, 1
	ldr	x1, .LC221
	ldr	w3, [x19, 8]
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -3
	b	.L1030
	.p2align 3
.L1021:
	ldr	x2, .LC215
	mov	x3, x19
	ldr	x1, .LC223
	mov	w0, 1
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1030
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
	beq	.L1040
	ldr	w1, [x20, 2764]
	cbz	w1, .L1040
	mov	w25, -1
	mov	x24, -2
	mov	w19, 0
	b	.L1043
	.p2align 3
.L1078:
	ldr	x0, [x22, 2784]
	ldr	w1, [x20, 2764]
	ldr	x0, [x0, 664]
	cmp	x0, x24
	bcs	.L1042
	mov	w25, w19
	mov	x24, x0
.L1042:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1080
.L1043:
	add	x22, x20, x19, sxtw 3
	ldr	x0, [x22, 2784]
	cbz	x0, .L1042
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	cbz	x0, .L1079
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	bne	.L1078
.L1079:
	ldr	w1, [x20, 2764]
	add	w19, w19, 1
	cmp	w1, w19
	bhi	.L1043
.L1080:
	cmn	w25, #1
	beq	.L1040
	ldr	x1, [x21, 664]
	cmp	x1, x24
	bhi	.L1081
.L1040:
	ldrb	w0, [x21, 145]
	ldrb	w1, [x21, 144]
	and	w0, w0, -64
	strb	w0, [x21, 145]
	and	w1, w1, -4
	strb	w1, [x21, 144]
	ldr	w2, [x20, 144]
	str	w2, [x21, 188]
	ldr	x2, [x20, 2384]
	ldrh	w2, [x2, 124]
	cmp	w2, 1
	beq	.L1051
	cmp	w2, 257
	bne	.L1052
	ldr	w2, [x20, 3340]
	cmp	w2, 1
	cset	w4, ne
.L1044:
	ldr	x3, [x20, 2392]
	mov	w2, 3
	ldrb	w3, [x3, 2066]
	cbz	w3, .L1045
	ldr	w3, [x21, 40]
	mov	w2, 1
	cmp	w3, w2
	ccmp	w3, 11, 4, ne
	cset	w4, eq
	cbz	w4, .L1082
.L1046:
	ldr	w3, [x21, 44]
	cmp	w3, wzr
	cset	w4, eq
.L1045:
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
	cbz	w2, .L1047
	ldr	w0, [x21, 16]
	str	w0, [x21, 232]
.L1047:
	ldr	x0, [x20, 2424]
	ldr	w1, [x21, 28]
	ldr	w0, [x0, 596]
	str	w0, [x21, 204]
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 600]
	str	w0, [x21, 208]
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 604]
	str	w0, [x21, 212]
	ldr	w0, [x20, 252]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1038
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
.L1038:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1081:
	ldr	w0, [x20, 252]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L1040
	ldr	x1, .LC225
	mov	x3, x24
	ldr	x2, [x21, 664]
	mov	w0, 29
	add	x25, x20, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x25, 2784]
	ldr	x1, [x21, 664]
	str	x1, [x0, 664]
	str	x24, [x21, 664]
	b	.L1040
	.p2align 3
.L1082:
	mov	w4, 2
	and	w3, w3, -9
	mov	w2, 3
	cmp	w3, w4
	csel	w2, w2, w4, ne
	b	.L1046
	.p2align 3
.L1051:
	mov	w4, 0
	b	.L1044
	.p2align 3
.L1052:
	mov	w4, 1
	b	.L1044
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
	bhi	.L1085
	uxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x2, x0, 4
	sub	x0, x2, x0
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x0, x20, x0, lsl 3
	add	x0, x0, 12288
	ldrb	w0, [x0, 1153]
	cmp	w0, wzr
	cset	w0, ne
.L1084:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1085:
	mov	w0, -1
	b	.L1084
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
	cbz	x0, .L1091
	ldrsb	w1, [x0, 1]
	add	x19, x0, 592
	add	x20, x0, 624
	cbz	w1, .L1097
.L1094:
	ldr	x2, [x19]
	mov	x1, x2
	cbz	x2, .L1089
	ldr	w0, [x21, 252]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1089:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L1094
	ldr	w0, [x21, 252]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L1087:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1097:
	ldr	x1, .LC228
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1087
.L1091:
	mov	w0, -1
	b	.L1087
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
	bhi	.L1102
	sub	w2, w0, #8192
	mov	w3, 4749
	sub	w2, w2, #308
	cmp	w2, w3
	bhi	.L1101
	mov	w0, 1
	strb	w0, [x20, 3]
	b	.L1100
	.p2align 3
.L1101:
	sub	w0, w0, #12288
	sub	w0, w0, #962
	cmp	w0, 1749
	bls	.L1105
.L1102:
	strb	wzr, [x20, 3]
.L1100:
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
	bhi	.L1103
	mov	w1, 5977
	movk	w1, 0xd1b7, lsl 16
	umull	x0, w0, w1
	ubfx	x4, x0, 45, 16
.L1103:
	strh	w4, [x20, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1105:
	mov	w0, 2
	strb	w0, [x20, 3]
	b	.L1100
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
	cbnz	w0, .L1107
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
	cbz	w0, .L1112
	ldr	x23, .LC260
	mov	w20, 0
	ldr	x22, .LC262
	.p2align 2
.L1111:
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
	bhi	.L1111
.L1112:
	ldrb	w2, [x19, 28]
	mov	w0, 32
	ldr	x1, .LC258
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cbz	w0, .L1113
	ldr	x23, .LC264
	mov	w20, 0
	ldr	x22, .LC266
	.p2align 2
.L1114:
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
	bhi	.L1114
.L1113:
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
.L1107:
	ldr	x1, .LC268
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21, 10]
	cbz	w0, .L1125
	ldr	x24, .LC272
	mov	w20, 0
	ldr	x23, .LC274
	add	x19, x21, 10
	.p2align 2
.L1118:
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
	bhi	.L1118
.L1119:
	ldrb	w2, [x19, 138]
	mov	w0, 32
	ldr	x1, .LC270
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cbz	w0, .L1117
	ldr	x24, .LC280
	mov	w20, 0
	ldr	x23, .LC282
	.p2align 2
.L1120:
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
	bhi	.L1120
.L1117:
	ldrh	w2, [x19, 276]
	mov	w0, 32
	ldr	x1, .LC276
	bl	dprint_vfmw
	ldrh	w2, [x19, 278]
	mov	w0, 32
	ldr	x1, .LC278
	bl	dprint_vfmw
	b	.L1113
.L1125:
	add	x19, x21, 10
	b	.L1119
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
	cbz	w3, .L1166
	cbnz	w4, .L1169
.L1166:
	ldrb	w6, [x19, 59]
	ldrb	w7, [x19, 128]
.L1128:
	ldr	x2, .LC285
	mov	w0, 22
	ldr	x1, .LC287
	add	x2, x2, 360
	bl	dprint_vfmw
	strb	wzr, [x20, 466]
.L1126:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 352
	ret
	.p2align 3
.L1169:
	cbz	w5, .L1166
	ldrb	w0, [x19, 59]
	cbnz	w0, .L1131
	ldrb	w7, [x19, 128]
	cbz	w7, .L1170
.L1131:
	mov	w0, 1
	strb	w0, [x20, 466]
	ldr	w1, [x21, 24]
	ldrb	w3, [x19, 57]
	ldrb	w2, [x19, 58]
	cmp	w1, 9
	strb	w3, [x29, 56]
	strb	w2, [x29, 57]
	beq	.L1171
.L1133:
	ldrb	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1134
	ldrb	w1, [x19, 129]
	cmp	w1, 1
	beq	.L1134
	cmp	w1, 9
	ccmp	w0, 9, 4, ne
	beq	.L1172
	ldrb	w0, [x29, 64]
	strb	w0, [x29, 58]
.L1134:
	mov	x1, x19
	add	x0, x29, 56
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	w1, [x29, 64]
	ldrb	w0, [x29, 58]
	cmp	w1, w0
	beq	.L1173
	strb	wzr, [x29, 65]
.L1137:
	ldrb	w0, [x29, 57]
	cbnz	w0, .L1138
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
	cbz	w0, .L1143
	sub	w4, w0, #1
	add	x2, x29, 56
	add	x4, x4, 17
	add	x0, x29, 72
	add	x1, x19, 82
	add	x4, x2, x4
	.p2align 2
.L1142:
	ldrb	w3, [x1, -15]
	add	x0, x0, 1
	ldrb	w2, [x1], 1
	strb	w3, [x0, -1]
	strb	w2, [x0, 10]
	cmp	x0, x4
	bne	.L1142
.L1143:
	ldrb	w0, [x5, 38]
	strb	w0, [x29, 94]
	cbz	w0, .L1141
	sub	w3, w0, #1
	add	x1, x29, 56
	add	x3, x3, 40
	add	x0, x29, 95
	add	x19, x19, 113
	add	x3, x1, x3
	.p2align 2
.L1146:
	ldrb	w2, [x19, -15]
	add	x0, x0, 1
	ldrb	w1, [x19], 1
	strb	w2, [x0, -1]
	strb	w1, [x0, 6]
	cmp	x0, x3
	bne	.L1146
.L1141:
	ldr	w0, [x20, 472]
	cbnz	w0, .L1174
	ldr	x2, .LC285
	mov	w0, 1
	ldr	x1, .LC289
	add	x2, x2, 360
	bl	dprint_vfmw
	b	.L1126
	.p2align 3
.L1138:
	add	x5, x19, 128
	ldrb	w0, [x5, 40]
	add	w0, w0, 1
	ldp	w2, w1, [x5, 8]
	uxtb	w0, w0
	strh	w2, [x29, 342]
	strb	w0, [x29, 66]
	strh	w1, [x29, 344]
	cbz	w0, .L1150
	sub	w2, w0, #1
	add	x1, x29, 68
	add	x2, x2, 87
	add	x0, x19, 172
	add	x2, x19, x2, lsl 1
	.p2align 2
.L1149:
	ldrh	w4, [x0]
	add	x0, x0, 2
	ldrh	w3, [x0, 196]
	cmp	x0, x2
	strh	w4, [x1]
	add	x1, x1, 2
	strh	w3, [x1, 66]
	bne	.L1149
.L1150:
	ldrb	w0, [x5, 41]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x29, 204]
	cbz	w0, .L1141
	sub	w2, w0, #1
	add	x1, x29, 206
	add	x2, x2, 120
	add	x0, x19, 238
	add	x19, x19, x2, lsl 1
	.p2align 2
.L1151:
	ldrh	w3, [x0]
	add	x0, x0, 2
	ldrh	w2, [x0, 196]
	cmp	x0, x19
	strh	w3, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 66]
	bne	.L1151
	b	.L1141
	.p2align 3
.L1174:
	ldr	x3, .LC290
	mov	x2, 290
	ldr	x0, [x20, 480]
	add	x1, x29, 56
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 290
	str	w0, [x20, 468]
	b	.L1126
	.p2align 3
.L1170:
	mov	w6, 0
	b	.L1128
	.p2align 3
.L1172:
	mov	w0, 1
	strb	w0, [x29, 58]
	b	.L1134
	.p2align 3
.L1173:
	ldrb	w0, [x29, 59]
	strb	w0, [x29, 65]
	b	.L1137
	.p2align 3
.L1171:
	ldr	w1, [x21, 32]
	cmp	w1, 9
	bne	.L1133
	strb	w0, [x29, 64]
	b	.L1133
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
.L1176:
	ldr	w1, [x0]
	add	x0, x0, 4
	strh	w1, [x2]
	add	x2, x2, 2
	cmp	x0, x4
	ldr	w1, [x0, 8]
	strh	w1, [x2, 4]
	bne	.L1176
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
	add	x19, x19, 1152
	ldr	w1, [x20, 4692]
	mov	w5, 1888
	ldr	x0, [x20, 2352]
	mov	w4, 12660
	ldr	x2, [x20, 2344]
	mov	x3, 0
	smaddl	x0, w1, w5, x0
	ldr	w21, [x0, 32]
	strb	wzr, [x20, 3953]
	smaddl	x21, w21, w4, x2
	.p2align 2
.L1184:
	ldr	w0, [x19, 48]
	cbnz	w0, .L1179
	cbz	x19, .L1180
	ldr	w2, [x20, 2764]
	cbz	w2, .L1180
	ldr	x0, [x20, 2784]
	cmp	x0, x19
	beq	.L1179
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L1182
	.p2align 3
.L1183:
	ldr	x1, [x0, 2784]
	cmp	x1, x19
	beq	.L1179
.L1182:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L1183
.L1180:
	lsl	x22, x3, 2
	mov	w0, 101
	sub	x22, x22, x3
	str	w0, [x20, 3992]
	lsl	x0, x22, 4
	mov	w1, 1
	sub	x22, x0, x22
	add	x23, x20, 4024
	lsl	x22, x22, x1
	strb	w1, [x20, 3953]
	sub	x3, x22, x3
	mov	x2, 632
	mov	x0, x23
	add	x22, x20, x3, lsl 3
	add	x24, x22, 12288
	add	x1, x24, 1232
	bl	memcpy
	str	x19, [x20, 4016]
	str	wzr, [x20, 4176]
	str	wzr, [x22, 13456]
	strb	wzr, [x24, 1154]
	strb	wzr, [x19]
	ldr	x0, [x20, 4016]
	str	wzr, [x0, 60]
	ldr	x0, [x20, 4016]
	str	wzr, [x0, 64]
	ldr	x0, [x20, 4016]
	str	wzr, [x0, 52]
	ldrb	w1, [x20, 3953]
	cmp	w1, 1
	bne	.L1188
	ldr	w0, [x20, 252]
	bl	FSP_NewLogicFs
	mov	w24, w0
	mov	w1, w0
	ldr	w0, [x20, 252]
	bl	FSP_GetLogicFs
	mov	x22, x0
	cmp	w24, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L1186
	add	x2, x20, 3328
	add	x1, x21, 2064
	add	x19, x0, 48
	bl	HEVC_ConvertHDRInfo
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1201
.L1187:
	ldr	x21, .LC293
	mov	x2, 632
	ldr	x0, [x20, 4016]
	mov	x1, x19
	ldr	x3, [x21, 104]
	add	x0, x0, 80
	blr	x3
	ldr	x1, [x20, 4016]
	mov	x2, 632
	ldr	x3, [x21, 104]
	mov	x0, x23
	add	x1, x1, 80
	blr	x3
	ldr	x1, [x20, 4016]
	mov	w0, 0
	str	w24, [x1, 28]
	ldrsb	w1, [x22, 4]
	str	w1, [x20, 3988]
.L1199:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1179:
	add	w3, w3, 1
	add	x19, x19, 712
	cmp	w3, 20
	bne	.L1184
.L1188:
	ldr	x1, .LC292
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1201:
	ldr	x2, [x20, 2392]
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
	b	.L1187
.L1186:
	ldr	x1, .LC295
	mov	w0, 0
	strb	wzr, [x20, 3953]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1199
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
	bne	.L1208
	b	.L1210
	.p2align 3
.L1205:
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1207
	cmp	w19, 32
	beq	.L1211
.L1208:
	ldr	w0, [x20, 252]
	mov	w1, w19
	add	w19, w19, 1
	bl	FSP_GetLogicFs
	cbnz	x0, .L1205
	ldr	x1, .LC299
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1210:
	ldr	x1, .LC297
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1207:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1211:
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
	add	x20, x20, 1153
	add	x0, x22, 4096
	add	x23, x23, 3105
	add	x0, x0, 1920
	bl	ResetVoQueue
	.p2align 2
.L1215:
	strb	wzr, [x20]
	add	x19, x20, 623
	add	x21, x20, 655
	str	wzr, [x20, 47]
.L1214:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1213
	ldr	w0, [x22, 252]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1213:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1214
	add	x20, x20, 712
	cmp	x20, x23
	bne	.L1215
	ldr	w0, [x22, 184]
	cbz	w0, .L1212
	sub	w1, w0, #1
	add	x0, x22, 2132
	add	x1, x1, 534
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1217:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1217
.L1212:
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
	ldr	x0, [x22, 2784]
	str	wzr, [x0, 48]
	ldr	x1, [x22, 2784]
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1226
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1227
	ldr	x1, [x22, 2784]
	mov	w2, 0
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
.L1227:
	ldr	x1, [x22, 2784]
	mov	w2, 0
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
.L1226:
	ldr	w2, [x20, 2764]
	sub	w2, w2, #1
	cmp	w19, w2
	bhi	.L1230
	.p2align 2
.L1236:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 2784]
	str	x0, [x1, 2784]
	bls	.L1236
.L1230:
	add	x0, x20, x2, uxtw 3
	str	xzr, [x0, 2784]
	str	w2, [x20, 2764]
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
	ldr	w2, [x20, 2764]
	cbnz	w2, .L1247
	b	.L1240
	.p2align 3
.L1242:
	add	w19, w19, 1
	cmp	w2, w19
	mov	w21, w19
	bls	.L1240
.L1247:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 2784]
	ldrb	w1, [x0]
	cbz	w1, .L1242
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
	ldr	w2, [x20, 2764]
	cmp	w2, w19
	bhi	.L1247
.L1240:
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
	ldr	w22, [x21, 2764]
	cbz	w22, .L1251
	mov	w26, 0
	mov	w20, 0
	mov	w24, -1
	mov	w23, 1
	.p2align 2
.L1258:
	add	x19, x21, x26, uxtw 3
	ldr	w0, [x21, 252]
	ldr	x1, [x19, 2784]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1252
	ldrsb	w1, [x0]
	cbnz	w1, .L1267
	ldrsb	w0, [x0, 1]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	ldr	x0, [x19, 2784]
	bne	.L1254
.L1270:
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1254
	str	w24, [x0, 28]
	ldr	x0, [x19, 2784]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 2784]
	strb	w23, [x0, 2]
.L1267:
	ldr	x0, [x19, 2784]
.L1254:
	ldr	w0, [x0]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1271
	add	w26, w26, 1
.L1257:
	add	w20, w20, 1
	cmp	w22, w20
	bne	.L1258
.L1251:
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1252:
	ldr	x0, [x19, 2784]
	b	.L1270
	.p2align 3
.L1271:
	mov	w1, w26
	mov	x0, x21
	mov	w25, 1
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1257
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
	ldr	w0, [x19, 13240]
	ldr	w1, [x19, 13244]
	cmp	w1, w0
	bcs	.L1276
	ldr	w0, [x19, 2760]
	ldr	w1, [x19, 2764]
	cmp	w1, w0
	bcc	.L1272
	cmp	w0, 15
	bls	.L1278
.L1276:
	ldr	x0, [x19, 2784]
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
.L1272:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1278:
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L1276
	b	.L1272
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
	ldr	w3, [x19, 2760]
	ldr	w2, [x19, 2764]
	cmp	w2, w3
	bhi	.L1287
.L1280:
	mov	w0, 0
	cbz	w2, .L1279
	.p2align 2
.L1285:
	add	x1, x19, x0, uxtw 3
	ldr	w2, [x20]
	ldr	x1, [x1, 2784]
	ldr	w1, [x1, 8]
	cmp	w2, w1
	ble	.L1282
	str	w1, [x20]
	str	w0, [x21]
.L1282:
	ldr	w1, [x19, 2764]
	add	w0, w0, 1
	cmp	w1, w0
	bhi	.L1285
.L1279:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1287:
	ldr	x1, .LC301
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x19, 2760]
	str	w2, [x19, 2764]
	b	.L1280
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
	ldr	w5, [x19, 4692]
	mov	w3, 1888
	ldr	x2, [x19, 2352]
	mov	w1, 12660
	ldr	x0, [x19, 2344]
	smaddl	x3, w5, w3, x2
	ldr	w3, [x3, 32]
	smaddl	x0, w3, w1, x0
	ldr	w1, [x0, 64]
	cmp	w1, w21
	ccmp	w20, wzr, 0, eq
	bne	.L1290
	ldr	w1, [x0, 68]
	mov	w0, 1
	cmp	w1, w22
	beq	.L1294
.L1289:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1290:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1294:
	ldr	w1, [x19, 172]
	cbz	w1, .L1289
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 904]
	cmp	w0, wzr
	cset	w0, ne
	b	.L1289
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
	ldr	x5, [x19, 2368]
	ldr	x0, [x19, 2328]
	ldrb	w4, [x5]
	ldr	w6, [x0, 32]
	cbz	w4, .L1306
	sub	w2, w4, #1
	mov	w7, 32
	mov	x3, 80
	add	x0, x5, 48
	mov	w1, 0
	umaddl	x3, w2, w7, x3
	add	x3, x5, x3
	.p2align 2
.L1297:
	ldr	w2, [x0], 32
	cmp	x0, x3
	add	w1, w1, w2
	bne	.L1297
.L1296:
	sbfiz	x4, x4, 5, 32
	and	w0, w6, 7
	add	x4, x5, x4
	str	w0, [x4, 60]
	ldr	x3, [x19, 2368]
	ldr	x0, [x19, 2328]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w3, [x4, 52]
	add	w0, w3, w0, lsr 3
	sub	w0, w0, w1
	str	w0, [x4, 64]
	ldr	x3, [x19, 2368]
	ldr	x0, [x19, 2328]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w2, [x4, 48]
	add	w1, w1, w2
	lsl	w1, w1, 3
	sub	w0, w1, w0
	str	w0, [x4, 56]
	ldr	x1, [x19, 2368]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w2, w1, [x0, 60]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w2
	str	w1, [x0, 60]
	ldr	x1, [x19, 2368]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldr	w1, [x0, 64]
	and	w1, w1, -4
	str	w1, [x0, 64]
	ldr	x3, [x19, 2368]
	ldr	w2, [x3, 8]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1314
	ldrb	w0, [x3]
	add	w4, w0, 1
	cmp	w4, 1
	ccmp	w2, w4, 0, ls
	bls	.L1300
	add	w2, w0, 2
	.p2align 2
.L1301:
	sub	w0, w2, #1
	cmp	w2, 1
	lsl	x1, x0, 5
	add	x0, x0, 1
	add	x3, x3, x1
	lsl	x0, x0, 5
	cset	w5, ls
	str	wzr, [x3, 60]
	ldr	x3, [x19, 2368]
	add	x4, x3, x0
	add	x3, x3, x1
	ldr	w4, [x4, 20]
	str	w4, [x3, 64]
	ldr	x3, [x19, 2368]
	add	x0, x3, x0
	add	x3, x3, x1
	ldr	w0, [x0, 16]
	lsl	w0, w0, 3
	str	w0, [x3, 56]
	ldr	x0, [x19, 2368]
	add	x0, x0, x1
	ldp	w4, w3, [x0, 60]
	ubfiz	w3, w3, 3, 4
	add	w3, w3, w4
	str	w3, [x0, 60]
	ldr	x0, [x19, 2368]
	add	x1, x0, x1
	ldr	w0, [x1, 64]
	and	w0, w0, -16
	str	w0, [x1, 64]
	ldr	x3, [x19, 2368]
	ldr	w0, [x3, 8]
	cmp	w0, w2
	add	w2, w2, 1
	cset	w1, hi
	tst	w5, w1
	bne	.L1301
	sub	w1, w0, #1
.L1300:
	ubfiz	x0, x1, 5, 32
	ldr	w1, [x3, 12]
	add	x3, x3, x0
	ldr	w0, [x3, 56]
	sub	w0, w0, w1
	str	w0, [x3, 56]
	ldr	x3, [x19, 2368]
	ldrb	w0, [x3]
	ldr	w4, [x3, 8]
	cmp	w0, w4
	bcs	.L1295
	.p2align 2
.L1309:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x19, 3984]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 64]
	cmp	w1, w2
	bcs	.L1303
	str	w1, [x19, 3984]
	ldr	w4, [x3, 8]
.L1303:
	cmp	w4, w0
	bhi	.L1309
.L1295:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1314:
	ldr	x1, .LC303
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1306:
	mov	w1, 0
	b	.L1296
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
	ldr	w2, [x19, 4692]
	cmp	w2, w0
	bge	.L1323
	mov	w0, 1888
	ldr	x1, [x19, 2352]
	smull	x0, w2, w0
	add	x3, x1, x0
	ldrb	w0, [x1, x0]
	cbz	w0, .L1324
	ldr	w2, [x3, 32]
	ldr	w0, [x19, 160]
	cmp	w2, w0
	bge	.L1325
	ldr	x1, [x19, 2344]
	mov	w0, 12660
	smaddl	x0, w2, w0, x1
	ldrb	w1, [x0, 1]
	cbz	w1, .L1326
	ldr	w2, [x0, 48]
	ldr	w0, [x19, 156]
	cmp	w2, w0
	bcs	.L1327
	uxtw	x1, w2
	ldr	x3, [x19, 2336]
	lsl	x4, x1, 7
	mov	w0, 0
	add	x1, x4, x1, lsl 2
	ldrb	w1, [x3, x1]
	cbz	w1, .L1328
.L1317:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1323:
	ldr	x1, .LC305
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
	.p2align 3
.L1324:
	ldr	x1, .LC307
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
	.p2align 3
.L1325:
	ldr	x1, .LC309
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
	.p2align 3
.L1326:
	ldr	x1, .LC311
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
	.p2align 3
.L1327:
	ldr	x1, .LC313
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
	.p2align 3
.L1328:
	ldr	x1, .LC315
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1317
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
	ldr	w0, [x19, 4688]
	mov	w1, 2147483647
	ldr	x2, [x19, 2368]
	add	x3, x19, x0, lsl 2
	ldr	w5, [x3, 228]
	cmp	w5, w1
	ldr	w1, [x2, 16]
	sub	w4, w1, #16
	beq	.L1356
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	beq	.L1334
.L1342:
	sub	w1, w1, #19
	cmp	w1, 1
	bls	.L1357
.L1334:
	ldr	w4, [x19, 4668]
	cmp	w4, w5
	bge	.L1333
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bls	.L1358
.L1335:
	add	x1, x19, x0
	ldrb	w8, [x1, 10]
	cbz	w8, .L1336
	ldr	w6, [x3, 232]
	cmp	w6, w4
	bgt	.L1359
.L1336:
	add	x1, x19, 4096
	ldrb	w5, [x1, 561]
	cbnz	w5, .L1337
	ldr	w2, [x2, 16]
	sub	w5, w2, #19
	cmp	w5, 1
	bls	.L1354
	cmp	w2, 21
	beq	.L1354
	sub	w2, w2, #16
	cmp	w2, 2
	bhi	.L1337
	add	x0, x19, x0
	str	w4, [x3, 232]
	mov	w2, 1
	strb	w2, [x0, 10]
	.p2align 2
.L1337:
	ldr	w0, [x19, 236]
	ldrb	w2, [x1, 560]
	ldr	w1, [x19, 4692]
	cbz	w0, .L1341
	ldr	w0, [x19, 208]
	cmp	w1, w0
	csinc	w2, w2, wzr, eq
.L1341:
	ldr	w3, [x19, 296]
	mov	w0, 1
	cmp	w3, w1
	beq	.L1360
.L1351:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1356:
	cmp	w4, 5
	bhi	.L1355
	cmp	w4, 2
	ccmp	w1, 21, 4, hi
	bne	.L1342
	ldr	w4, [x19, 4668]
	str	w4, [x3, 228]
.L1333:
	add	x1, x19, x0
	ldrb	w5, [x1, 5]
	cbz	w5, .L1335
	ldr	w6, [x2, 16]
	sub	w1, w6, #8
	cmp	w1, 1
	bhi	.L1335
	ldr	x2, .LC316
	mov	w3, 12854
	ldr	x1, .LC320
	mov	w0, 1
	add	x2, x2, 384
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1351
	.p2align 3
.L1359:
	ldr	w7, [x2, 16]
	sub	w1, w7, #8
	cmp	w1, 1
	bhi	.L1336
	ldr	x2, .LC316
	mov	w5, w4
	ldr	x1, .LC322
	mov	w4, w8
	mov	w3, 12863
	add	x2, x2, 384
	mov	w0, 1
	bl	dprint_vfmw
.L1355:
	mov	w0, 2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1354:
	add	x0, x19, x0
	str	w4, [x3, 232]
	strb	wzr, [x0, 10]
	b	.L1337
	.p2align 3
.L1357:
	mov	w5, -2147483647
	str	w5, [x3, 228]
	b	.L1334
	.p2align 3
.L1360:
	ldr	w0, [x19, 260]
	ldr	x19, [sp, 16]
	cmp	w0, w4
	csinc	w0, w2, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1358:
	ldr	x2, .LC316
	mov	w3, 12847
	ldr	x1, .LC318
	mov	w0, 1
	add	x2, x2, 384
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1351
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
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1366
	ldr	x0, [x19, 2328]
	mov	w20, 0
	bl	BsBitsToNextByte
	mov	w1, w0
	cbz	w0, .L1363
	ldr	x0, [x19, 2328]
	bl	BsGet
	mov	w2, w0
	ldr	x1, .LC326
	mov	w0, 19
	bl	dprint_vfmw
.L1363:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1366:
	ldr	x1, .LC324
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1363
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
	ldr	w0, [x19, 4684]
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
	ldr	w0, [x19, 4684]
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
	ldr	x0, [x20, 2328]
	cbnz	w24, .L1407
.L1405:
	mov	w1, 8
	bl	BsGet
	str	w0, [x22, 4]
	cmp	w23, wzr
	ble	.L1375
	sub	w21, w23, #1
	mov	x19, 0
	add	x21, x21, 1
	add	x25, x29, 88
	add	x22, x29, 80
	.p2align 2
.L1376:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x25, x19]
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, x21
	bne	.L1376
	cmp	w23, 7
	mov	w19, w23
	ble	.L1394
	b	.L1386
	.p2align 3
.L1379:
	cmp	w19, 8
	beq	.L1386
.L1394:
	ldr	x0, [x20, 2328]
	mov	w1, 2
	add	w19, w19, 1
	bl	BsGet
	cbz	w0, .L1379
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
.L1386:
	mov	x21, 0
	.p2align 2
.L1384:
	cbz	w24, .L1381
	ldrb	w0, [x25, x21]
	cbnz	w0, .L1408
.L1381:
	ldrb	w0, [x22, x21]
	cbnz	w0, .L1409
.L1383:
	add	x21, x21, 1
	cmp	w23, w21
	bgt	.L1384
.L1375:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1409:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	b	.L1383
	.p2align 3
.L1408:
	ldr	x0, [x20, 2328]
	mov	w1, 2
	mov	w19, 32
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 5
	bl	BsGet
	.p2align 2
.L1382:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	subs	w19, w19, #1
	bne	.L1382
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 12
	bl	BsGet
	b	.L1381
.L1407:
	mov	w1, 2
	add	x19, x29, 96
	add	x21, x29, 128
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 5
	bl	BsGet
	mov	w25, w0
	.p2align 2
.L1371:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19], 1
	cmp	x19, x21
	bne	.L1371
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	sub	w0, w25, #4
	cmp	w0, 3
	bls	.L1372
	ldrb	w0, [x29, 100]
	cbnz	w0, .L1372
	ldrb	w0, [x29, 101]
	cbnz	w0, .L1372
	ldrb	w0, [x29, 102]
	cbnz	w0, .L1372
	ldrb	w0, [x29, 103]
	cbnz	w0, .L1372
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 11
	bl	BsGet
	b	.L1374
	.p2align 3
.L1372:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 2
	bl	BsGet
.L1374:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	str	w25, [x20, 300]
	ldrb	w2, [x29, 97]
	ldrb	w1, [x29, 98]
	ldr	x0, [x20, 2328]
	str	w2, [x20, 304]
	str	w1, [x20, 308]
	b	.L1405
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
.L1411:
	ldr	w0, [x26]
	cbz	w0, .L1420
	uxtw	x0, w25
	mov	w27, 0
	lsl	x28, x0, 2
	sub	x28, x28, x0
	lsl	x28, x28, 1
	.p2align 2
.L1417:
	uxtw	x19, w27
	add	x1, x21, 400
	add	x0, x19, x28
	cmp	w25, 3
	mov	x2, 64
	cbz	w25, .L1424
	add	x0, x20, x0, lsl 6
	beq	.L1425
	cmp	w27, 3
	ldr	x4, [x24, 104]
	add	x0, x0, 596
	csel	x1, x22, x1, cc
	blr	x4
.L1413:
	add	x19, x28, x19
	add	w27, w27, 1
	add	x19, x20, x19, lsl 2
	str	w23, [x19, 2228]
	ldr	w0, [x26]
	cmp	w0, w27
	bhi	.L1417
.L1420:
	add	w25, w25, 1
	add	x26, x26, 4
	cmp	w25, 4
	bne	.L1411
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1424:
	add	x0, x20, x19, lsl 6
	ldr	x1, .LC332
	ldr	x4, [x24, 104]
	mov	x2, 16
	add	x0, x0, 596
	blr	x4
	b	.L1413
.L1425:
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
	b	.L1413
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
	ldr	x0, [x19, 2392]
	ldrb	w1, [x0, 3]
	cbz	w1, .L1446
	ldr	x20, [x19, 2400]
	add	x20, x20, 256
	ldrb	w1, [x20, -235]
	cbz	w1, .L1454
.L1429:
	cbz	x20, .L1430
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
.L1432:
	ldr	w13, [x15, 1888]
	cbz	w13, .L1441
	ldr	w8, [x15]
	mov	x9, x16
	mov	w11, 0
	cmp	w8, 64
	csel	w8, w8, w17, ls
	lsr	w10, w8, 2
.L1439:
	uxtw	x7, w11
	mov	w4, 0
	umaddl	x7, w12, w14, x7
	lsl	x7, x7, 4
	.p2align 2
.L1433:
	cmp	w10, w4
	bls	.L1436
	cbz	w8, .L1433
	add	x0, x7, x4, uxtw
	ldrb	w1, [x9, -1]
	mov	x6, x9
	mov	w3, 0
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 596]
	orr	w1, w2, w1
	str	w1, [x0, 596]
	.p2align 2
.L1442:
	add	w3, w3, 1
	add	x0, x7, x4, uxtw
	cmp	w3, w8
	and	w5, w3, 3
	add	x0, x19, x0, lsl 2
	lsl	w1, w5, 3
	beq	.L1433
	ldrb	w2, [x6], 1
	cmp	w5, 3
	ldr	w5, [x0, 596]
	csinc	w4, w4, w4, ne
	lsl	w1, w2, w1
	orr	w1, w5, w1
	str	w1, [x0, 596]
	b	.L1442
.L1454:
	ldrb	w1, [x0, 4]
	cbnz	w1, .L1455
.L1430:
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
.L1446:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1436:
	add	w11, w11, 1
	add	x9, x9, 64
	cmp	w11, w13
	bne	.L1439
.L1441:
	add	w12, w12, 1
	add	x16, x16, 384
	cmp	w12, 4
	add	x15, x15, 4
	bne	.L1432
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
.L1455:
	add	x20, x0, 432
	b	.L1429
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
.L1457:
	cmp	w5, w10
	bcs	.L1456
	cbz	w8, .L1457
	add	x0, x9, x5, uxtw
	mov	x7, x21
	mov	w4, 0
	add	x0, x20, x0, lsl 2
	ldrb	w2, [x7], 1
	ldr	w3, [x0, 596]
	orr	w2, w3, w2
	str	w2, [x0, 596]
	.p2align 2
.L1463:
	add	w4, w4, 1
	add	x0, x9, x5, uxtw
	cmp	w8, w4
	and	w6, w4, 3
	add	x0, x20, x0, lsl 2
	lsl	w2, w6, 3
	beq	.L1457
	ldrb	w3, [x7], 1
	cmp	w6, 3
	ldr	w6, [x0, 596]
	csinc	w5, w5, w5, ne
	lsl	w2, w3, w2
	orr	w2, w6, w2
	str	w2, [x0, 596]
	b	.L1463
.L1456:
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
	bls	.L1477
	ldr	x1, .LC337
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1477:
	ldr	x0, .LC335
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1467
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1467:
	.section	.rodata
	.align	0
	.align	2
.L1467:
	.byte	(.L1471 - .Lrtx1467) / 4
	.byte	(.L1469 - .Lrtx1467) / 4
	.byte	(.L1469 - .Lrtx1467) / 4
	.byte	(.L1470 - .Lrtx1467) / 4
	.text
	.p2align 3
.L1469:
	cmp	w20, 2
	ldr	x0, .LC334
	bhi	.L1474
.L1475:
	add	x0, x0, 144
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1470:
	ldr	x0, .LC334
	cbz	w20, .L1475
.L1474:
	add	x0, x0, 80
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1471:
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
	.xword	.L1467
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
	beq	.L1488
	sub	w0, w20, #1
	mov	w19, 1
	asr	w0, w0, 1
	cbz	w0, .L1480
	.p2align 2
.L1481:
	asr	w0, w0, 1
	add	w19, w19, 1
	cbnz	w0, .L1481
.L1480:
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w20, 1
	strb	w0, [x23]
	cset	w24, hi
	cmp	w0, wzr
	cset	w0, ne
	tst	w24, w0
	beq	.L1485
	ldr	w0, [x21, 76]
	cbz	w0, .L1485
	mov	w20, 0
	.p2align 2
.L1486:
	ldr	x0, [x22, 2328]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 4]
	ldr	w0, [x21, 76]
	cmp	w0, w20
	bhi	.L1486
.L1485:
	ldr	w0, [x21, 20]
	cbz	w0, .L1503
.L1484:
	mov	w0, 0
.L1479:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1503:
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, wzr
	strb	w0, [x23, 1]
	cset	w0, ne
	tst	w24, w0
	beq	.L1484
	ldr	w0, [x21, 80]
	cbz	w0, .L1484
	mov	w20, 0
	.p2align 2
.L1487:
	ldr	x0, [x22, 2328]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 132]
	ldr	w0, [x21, 80]
	cmp	w0, w20
	bhi	.L1487
	b	.L1484
.L1488:
	mov	w0, -1
	b	.L1479
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
	ldr	x0, [x19, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1506
	ldr	x1, [x19, 2368]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	cset	w0, cc
	ret
	.p2align 3
.L1506:
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
	ldr	x0, [x19, 2328]
	ldr	w2, [x0, 24]
	ldr	w3, [x0, 32]
	lsl	w2, w2, 3
	cmp	w2, w3
	bls	.L1510
	mov	w1, 8
	bl	BsShow
	cmp	w0, 128
	cset	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1510:
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
.L1524:
	ldr	x1, [x20, 2368]
	mov	w3, 0
	ldr	w5, [x1, 8]
	sub	w5, w5, #1
	add	x2, x1, x5, lsl 5
	ldr	w0, [x2, 48]
	ldr	x2, [x2, 40]
	sub	x0, x0, #1
	add	x0, x2, x0
	.p2align 2
.L1512:
	ldrb	w2, [x0]
	add	x19, x5, 1
	lsl	x19, x19, 5
	add	x4, x1, x19
	cbnz	w2, .L1525
	ldr	x2, [x1, 40]
	add	w3, w3, 1
	cmp	x0, x2
	beq	.L1526
	ldr	x2, [x4, 8]
	cmp	x0, x2
	sub	x0, x0, #1
	bne	.L1512
	add	x1, x1, x5, lsl 5
	ldr	w0, [x20, 252]
	ldr	w1, [x1, 68]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x20, 2368]
	add	x19, x0, x19
	str	xzr, [x19, 8]
	ldr	x1, [x20, 2368]
	ldr	w0, [x1, 8]
	sub	w0, w0, #1
	str	w0, [x1, 8]
	b	.L1524
	.p2align 3
.L1525:
	mov	w0, 1
	mov	w5, w0
	tbnz	x2, 0, .L1519
	.p2align 2
.L1522:
	lsl	w4, w5, w0
	add	w0, w0, 1
	tst	w4, w2
	bne	.L1519
	cmp	w0, 8
	bne	.L1522
	ldr	x1, .LC343
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1526:
	ldr	x1, .LC341
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1519:
	str	wzr, [x1, 4]
	add	w3, w0, w3, lsl 3
	mov	w0, 0
	ldr	x1, [x20, 2368]
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
	ble	.L1528
	udiv	w1, w0, w3
	mov	w4, 104
	ldr	x5, [x19, 2416]
	msub	w0, w1, w3, w0
	umull	x1, w0, w4
	add	x1, x5, x1
	ldr	w1, [x1, 32]
	cbz	w1, .L1529
	mov	w1, 0
	b	.L1531
	.p2align 3
.L1532:
	udiv	w0, w2, w3
	msub	w0, w0, w3, w2
	umull	x2, w0, w4
	add	x2, x5, x2
	ldr	w2, [x2, 32]
	cbz	w2, .L1529
.L1531:
	add	w1, w1, 1
	cmp	w3, w1
	add	w2, w1, w0
	bne	.L1532
.L1528:
	str	w0, [x19, 148]
.L1543:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1529:
	cmp	w0, w3
	str	w0, [x19, 148]
	bcs	.L1543
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
	cbz	x20, .L1553
	ldr	x24, .LC346
	add	x19, x20, 40
	ldr	x23, .LC348
	add	x22, x20, 104
	stp	wzr, wzr, [x20, 32]
.L1548:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L1547
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
.L1547:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L1548
	ldr	x3, .LC349
	mov	x2, 104
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
.L1544:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1553:
	ldr	x2, .LC344
	mov	w3, 14174
	ldr	x1, .LC345
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1544
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
	ldr	x0, [x20, 2392]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 2760]
	cmp	w0, 17
	bhi	.L1588
.L1555:
	add	x2, x20, 2560
	add	x0, x20, 2920
	add	x1, x20, 3056
	stp	wzr, wzr, [x2, 204]
	stp	wzr, wzr, [x2, 212]
	str	wzr, [x20, 2780]
	.p2align 2
.L1556:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x0, x1
	bne	.L1556
	add	x26, x20, 12288
	ldr	x22, .LC353
	add	x19, x26, 1152
	mov	w21, 0
	mov	w25, 20
	mov	w24, 16
	.p2align 2
.L1557:
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
	bne	.L1557
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 200
	add	x0, x26, 952
	blr	x3
	str	w23, [x20, 13240]
	add	x1, x20, 2448
	add	x0, x20, 2584
	str	wzr, [x20, 13244]
.L1559:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L1559
	add	x1, x20, 2720
	str	wzr, [x20, 4724]
	.p2align 2
.L1560:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L1560
	ldr	w0, [x20, 184]
	str	wzr, [x20, 4728]
	cbz	w0, .L1565
	sub	w1, w0, #1
	add	x0, x20, 2132
	add	x1, x1, 534
	add	x1, x20, x1, lsl 2
	.p2align 2
.L1564:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L1564
.L1565:
	ldr	w3, [x20, 168]
	mov	w19, 0
	cbz	w3, .L1554
	.p2align 2
.L1578:
	ldr	x0, [x20, 2408]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L1566
	ldr	x2, [x20, 2368]
	cmp	x0, x2
	beq	.L1566
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2408]
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
.L1566:
	cmp	w3, w19
	bhi	.L1578
.L1554:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1588:
	ldr	x2, .LC350
	mov	w4, 17
	ldr	x1, .LC352
	mov	w3, w4
	add	x2, x2, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 2760]
	b	.L1555
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
	cbz	x20, .L1600
	ldr	w3, [x20, 2764]
	mov	w0, 0
	mov	w4, 1
	cbz	w3, .L1595
	.p2align 2
.L1609:
	add	x1, x20, x0, uxtw 3
	add	w0, w0, 1
	ldr	x1, [x1, 2784]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L1593
	strb	w4, [x1, 2]
	ldr	w3, [x20, 2764]
.L1593:
	cmp	w3, w0
	bhi	.L1609
.L1595:
	mov	w0, -2147483647
	add	x19, x20, 2784
	add	x21, x20, 2920
	str	w0, [x20, 212]
.L1592:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L1596
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1596:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L1597
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1597:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L1598
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1598:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L1599
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L1599:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L1592
	mov	x0, x20
	bl	HEVC_InitDecBuffers
	mov	w0, 0
.L1590:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1600:
	mov	w0, -1
	b	.L1590
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
	ldr	x0, [x19, 2368]
	cbz	x0, .L1619
	ldr	w0, [x0, 48]
	cmp	w0, 4095
	bhi	.L1616
	ldr	x1, .LC357
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	ldr	x3, .LC358
	ldr	w2, [x1, 48]
	ldr	x0, [x1, 72]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 40]
	sub	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 2368]
	mov	w3, 1
	ldr	w2, [x0, 100]
	ldr	w1, [x0, 68]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2368]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2368]
	ldr	w4, [x0, 48]
	ldr	x2, [x0, 72]
	sub	x2, x2, x4
	str	x2, [x0, 40]
	ldr	x0, [x19, 2368]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 84]
	sub	w2, w2, w4
	str	w2, [x0, 52]
	ldr	x0, [x19, 2368]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 80]
	add	w2, w4, w2
	str	w2, [x0, 48]
	ldr	x0, [x19, 2368]
	str	w3, [x0, 8]
	ldr	w0, [x19, 252]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 2368]
	str	xzr, [x0, 72]
	ldr	x0, [x19, 2368]
	str	wzr, [x0, 92]
	ldr	x0, [x19, 2368]
	str	wzr, [x0, 80]
.L1616:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1619:
	ldr	x1, .LC355
	bl	dprint_vfmw
	b	.L1616
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
	cbz	x20, .L1625
	ldr	w3, [x19, 2764]
	cbz	w3, .L1625
	ldr	x0, [x19, 2784]
	cmp	x20, x0
	beq	.L1627
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1622
	.p2align 3
.L1623:
	ldr	x2, [x0, 2784]
	cmp	x20, x2
	beq	.L1627
.L1622:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1623
.L1625:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1627:
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
	bls	.L1634
	mov	w0, -4370
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1634:
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
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1655
.L1640:
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	mov	w0, 0
.L1638:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1655:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 8
	mov	w22, w0
	bhi	.L1656
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 4
	mov	w1, w0
	mov	w0, 0
	bhi	.L1638
	ldr	x0, .LC363
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1639
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1639:
	.section	.rodata
	.align	0
	.align	2
.L1639:
	.byte	(.L1640 - .Lrtx1639) / 4
	.byte	(.L1640 - .Lrtx1639) / 4
	.byte	(.L1641 - .Lrtx1639) / 4
	.byte	(.L1642 - .Lrtx1639) / 4
	.byte	(.L1643 - .Lrtx1639) / 4
	.text
	.p2align 3
.L1641:
	mov	w2, 1
	lsl	w22, w2, w22
	cbz	w22, .L1654
	add	w21, w21, 7
	mov	w20, 0
	and	w21, w21, -8
	.p2align 2
.L1645:
	ldr	x0, [x19, 2328]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	cmp	w22, w20
	bne	.L1645
.L1654:
	mov	w0, 0
.L1657:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1642:
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	cmp	w0, 256
	mov	w23, w0
	bhi	.L1647
	cbz	w0, .L1654
	add	w21, w21, 7
	add	w22, w22, 7
	and	w21, w21, -8
	and	w22, w22, -8
	mov	w20, 0
	.p2align 2
.L1649:
	ldr	x0, [x19, 2328]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, w22
	bl	BsGet
	cmp	w20, w23
	bne	.L1649
	mov	w0, 0
	b	.L1657
	.p2align 3
.L1643:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	beq	.L1658
.L1650:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	mov	w0, 0
	b	.L1657
	.p2align 3
.L1658:
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	b	.L1650
.L1656:
	ldr	x1, .LC362
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1638
.L1647:
	ldr	x1, .LC365
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1638
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	3
.LC360:
	.xword	.LC359
	.align	3
.LC362:
	.xword	.LC361
	.align	3
.LC363:
	.xword	.L1639
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
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1660
	ldr	x0, [x19, 2328]
	mov	w1, 7
	bl	BsGet
	mov	w21, w0
	sub	w0, w0, #3
	cmp	w0, 2
	bhi	.L1667
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w20, w0
	ldr	x0, [x19, 2328]
	mov	w1, 6
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	cmp	w20, wzr
	ccmp	w21, 5, 4, eq
	bne	.L1668
.L1663:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
.L1660:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L1662:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1668:
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	b	.L1663
	.p2align 3
.L1667:
	ldr	x1, .LC369
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1662
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
	beq	.L1673
	ldr	x1, .LC371
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldrb	w0, [x20, 3]
	cbnz	w0, .L1680
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1681
.L1672:
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L1670:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1680:
	ldr	w1, [x20, 4]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1672
.L1681:
	ldr	w1, [x20, 8]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	b	.L1672
	.p2align 3
.L1673:
	mov	w0, -1
	b	.L1670
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
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC373
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 15
	bgt	.L1683
	tbnz	w0, #31, .L1687
	ldr	x22, .LC377
	add	w21, w0, 1
	mov	w19, 0
	.p2align 2
.L1686:
	ldr	x0, [x20, 2328]
	mov	x1, x22
	add	w19, w19, 1
	bl	HEVC_ue_v
	cmp	w21, w19
	bne	.L1686
.L1687:
	ldr	x0, [x20, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L1685:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1683:
	ldr	x1, .LC375
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1685
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
	ldr	x0, [x19, 2328]
	str	wzr, [x19, 11832]
	bl	HEVC_ue_v
	cmp	w0, 15
	bhi	.L1715
	add	x0, x19, 8192
	mov	w1, 1
	mov	w24, 0
	strb	w1, [x0, 3633]
	ldrb	w0, [x22, 2]
	cbz	w0, .L1716
.L1692:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	mov	w21, w1
	mov	w20, 0
	bl	BsGet
	strb	w0, [x23]
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2328]
	add	w1, w1, w21
	bl	BsGet
.L1693:
	cbz	w20, .L1717
	cmp	w20, 1
	beq	.L1718
.L1698:
	cmp	w21, 1
	bhi	.L1697
.L1696:
	add	w20, w20, 1
	add	w21, w21, 1
	b	.L1693
	.p2align 3
.L1697:
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L1713:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1716:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w24, w0
	cbz	w24, .L1692
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 20]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	b	.L1692
.L1715:
	ldr	x1, .LC381
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1713
.L1717:
	ldrb	w0, [x22]
	cbz	w0, .L1698
	ldr	w0, [x22, 24]
	mov	w23, 0
	cmn	w0, #1
	bne	.L1701
	b	.L1696
	.p2align 3
.L1700:
	ldr	w0, [x22, 24]
	add	w0, w0, 1
	cmp	w0, w23
	bls	.L1698
.L1701:
	ldr	w1, [x22, 12]
	add	w23, w23, 1
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x22, 2]
	orr	w0, w0, w24
	cbz	w0, .L1700
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	b	.L1700
.L1718:
	ldrb	w0, [x22, 1]
	cbz	w0, .L1697
	ldr	w0, [x22, 24]
	cmn	w0, #1
	beq	.L1697
	mov	w23, 0
	b	.L1701
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
	ldr	w1, [x19, 11828]
	ldr	w0, [x19, 11832]
	add	w1, w1, 1
	str	w1, [x19, 11828]
	add	w0, w0, 1
	str	w0, [x19, 11832]
	ldrb	w0, [x20, 2]
	cbnz	w0, .L1746
.L1720:
	ldrh	w0, [x20, 44]
	add	x21, x20, 44
	cbz	w0, .L1722
	ldr	w1, [x21, 16]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x22, 8]
	ldr	w1, [x21, 20]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	str	w0, [x22, 12]
	ldrb	w0, [x21, 2]
	cbnz	w0, .L1723
.L1726:
	ldrsw	x1, [x19, 252]
	ldr	x0, .LC382
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L1747
.L1722:
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L1729:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1746:
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	str	w0, [x22]
	mov	w1, 2
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x19, 2328]
	bl	BsGet
	b	.L1720
	.p2align 3
.L1747:
	ldr	w1, [x0, 156]
	cbnz	w1, .L1722
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L1722
	mov	x2, x20
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1722
	.p2align 3
.L1723:
	ldr	w1, [x21, 8]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x21, 2]
	cbz	w0, .L1726
	ldrb	w0, [x21, 3]
	cbz	w0, .L1726
	ldr	x1, .LC384
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	mov	w24, w0
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w25, w0
	cbnz	w25, .L1748
.L1727:
	cmp	w24, 255
	bhi	.L1749
	ldr	x26, .LC388
	add	w24, w24, 1
	mov	w23, 0
	b	.L1731
	.p2align 3
.L1730:
	cmp	w23, w24
	beq	.L1726
.L1731:
	ldr	x0, [x19, 2328]
	mov	x1, x26
	add	w23, w23, 1
	bl	HEVC_ue_v
	cbnz	w25, .L1730
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	b	.L1730
	.p2align 3
.L1748:
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2328]
	add	w1, w1, 1
	bl	BsGet
	b	.L1727
.L1749:
	ldr	x1, .LC386
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1729
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
	beq	.L1760
	ldr	x1, .LC390
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1752
.L1756:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x20]
.L1751:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1752:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L1765
.L1753:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	mov	w21, 0
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x20, 5]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x20, 6]
	mov	w1, 4
	ldr	x0, [x19, 2328]
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 7]
	cbz	w1, .L1758
	.p2align 2
.L1762:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2328]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 8]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x22, 23]
	ldrb	w0, [x20, 7]
	cmp	w0, w21
	bhi	.L1762
.L1758:
	ldr	x0, [x19, 2328]
	mov	w1, 4
	mov	w21, 0
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 38]
	cbz	w1, .L1756
	.p2align 2
.L1761:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2328]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 39]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x22, 54]
	ldrb	w0, [x20, 38]
	cmp	w0, w21
	bhi	.L1761
	b	.L1756
	.p2align 3
.L1760:
	mov	w0, -1
	b	.L1751
	.p2align 3
.L1765:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	b	.L1753
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
	beq	.L1773
	cmp	w21, 3
	bls	.L1777
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 2
	beq	.L1778
	cmp	w0, 4
	beq	.L1779
	subs	w21, w21, #4
	mov	w19, 0
	beq	.L1772
	.p2align 2
.L1775:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L1775
.L1772:
	mov	w0, 0
.L1767:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1778:
	add	x1, x20, 3384
	mov	x0, x20
	bl	HEVC_Sei_TSI
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1779:
	add	x1, x20, 3387
	mov	x0, x20
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1773:
	mov	w0, -1
	b	.L1767
.L1777:
	ldr	x1, .LC392
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1767
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
	cbnz	w20, .L1827
.L1781:
	ldr	x1, .LC406
	ldr	x0, [x22, 2328]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19]
	bhi	.L1828
	ldr	x1, .LC410
	ldr	x0, [x22, 2328]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19, 4]
	bhi	.L1829
	ldr	w1, [x19]
	add	w2, w0, w1
	str	w2, [x19, 8]
	cmp	w2, 16
	bhi	.L1806
	mov	w20, 0
	cbz	w1, .L1808
	ldr	x25, .LC416
	mov	w21, 0
	mov	w23, 0
	mov	w24, 32767
	b	.L1810
	.p2align 3
.L1809:
	str	w23, [x19, x2, lsl 2]
	add	x20, x19, x20
	ldr	x0, [x22, 2328]
	bl	BsGet
	strb	w0, [x20, 12]
	ldr	w20, [x19]
	cmp	w20, w21
	bls	.L1830
.L1810:
	ldr	x0, [x22, 2328]
	mov	x1, x25
	uxtw	x20, w21
	add	w21, w21, 1
	bl	HEVC_ue_v
	cmp	w0, w24
	mvn	w1, w0
	add	x2, x20, 8
	add	w23, w23, w1
	mov	w1, 1
	bls	.L1809
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
.L1827:
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1781
	ldr	w0, [x27, 176]
	cmp	w20, w0
	beq	.L1831
	sub	w20, w20, #1
.L1785:
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x1, .LC400
	ldr	x0, [x22, 2328]
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
	bhi	.L1832
	mov	w21, 0
	mov	w26, 0
	mov	w20, 0
	mov	w23, 0
	b	.L1792
	.p2align 3
.L1787:
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L1833
.L1788:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L1834
.L1792:
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L1787
	ldr	x0, [x22, 2328]
	mov	w1, 1
	bl	BsGet
	lsl	w0, w0, 1
	sub	w1, w0, #1
	cmp	w1, 1
	bhi	.L1788
.L1833:
	ldr	w5, [x28, 2172]
	add	x1, x24, x21, uxtw
	uxtw	x2, w23
	cmp	w5, w21
	add	x4, x2, 8
	add	x3, x19, x2
	add	x2, x27, x1, lsl 2
	mov	w1, 0
	bls	.L1789
	ldr	w1, [x2, 2196]
.L1789:
	cmp	w0, 1
	add	w0, w1, w25
	str	w0, [x19, x4, lsl 2]
	cset	w1, eq
	strb	w1, [x3, 12]
	tbnz	w0, #31, .L1835
	add	w26, w26, 1
	add	w23, w23, 1
.L1836:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcs	.L1792
.L1834:
	cmp	w23, 16
	str	w23, [x19, 8]
	ccmp	w20, 16, 2, ls
	ccmp	w26, 16, 2, ls
	stp	w20, w26, [x19]
	bhi	.L1793
	cmp	w23, 1
	bls	.L1799
	sub	w10, w23, #2
	add	x9, x19, 36
	add	x10, x10, 1
	mov	x7, 0
	.p2align 2
.L1798:
	add	x0, x19, x7
	mov	w3, w7
	ldr	w5, [x9]
	ldrb	w8, [x0, 13]
	tbnz	w7, #31, .L1802
	.p2align 2
.L1817:
	sxtw	x1, w3
	add	w0, w3, 1
	add	x4, x19, x1
	add	x1, x19, x1, lsl 2
	sxtw	x0, w0
	add	x6, x0, 8
	add	x0, x19, x0
	ldr	w2, [x1, 32]
	cmp	w5, w2
	bge	.L1800
	str	w2, [x19, x6, lsl 2]
	ldrb	w2, [x4, 12]
	strb	w2, [x0, 12]
	str	w5, [x1, 32]
	strb	w8, [x4, 12]
.L1800:
	subs	w3, w3, #1
	bpl	.L1817
.L1802:
	add	x7, x7, 1
	add	x9, x9, 4
	cmp	x10, x7
	bne	.L1798
.L1799:
	lsr	w7, w20, 1
	sub	w20, w20, #1
	cbz	w7, .L1796
	add	x2, x19, 32
	add	x1, x19, 12
	sub	w7, w20, w7
	.p2align 2
.L1803:
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
	bne	.L1803
.L1796:
	mov	w0, 0
.L1826:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1835:
	add	w20, w20, 1
	add	w23, w23, 1
	b	.L1836
.L1830:
	ldr	w2, [x19, 8]
.L1808:
	cmp	w2, w20
	bls	.L1796
	ldr	x24, .LC420
	mov	w23, 0
	.p2align 2
.L1811:
	ldr	x0, [x22, 2328]
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
	ldr	x0, [x22, 2328]
	bl	BsGet
	strb	w0, [x21, 12]
	ldr	w0, [x19, 8]
	cmp	w0, w20
	bhi	.L1811
	b	.L1796
.L1831:
	ldr	x1, .LC394
	ldr	x0, [x22, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w20, w2
	bcc	.L1837
	sub	w3, w20, #1
	sub	w20, w3, w0
	cmp	w20, w3
	bls	.L1785
	ldr	x1, .LC398
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1793:
	ldr	x1, .LC404
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1829:
	ldr	x1, .LC412
	mov	w0, 1
	ldr	w2, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1837:
	ldr	x1, .LC396
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1832:
	ldr	x1, .LC402
	mov	w0, w4
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1828:
	ldr	x1, .LC408
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
.L1806:
	ldr	x1, .LC414
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1826
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
	beq	.L1861
	cbnz	w19, .L1885
.L1841:
	ldr	x27, .LC424
	mov	w19, 0
	ldr	x25, .LC422
	ldr	x26, .LC426
	ldr	x28, .LC428
	.p2align 2
.L1857:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	uxtw	x21, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1886
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
.L1860:
	ldr	x0, [x20, 2328]
	mov	x1, x25
	bl	HEVC_ue_v
.L1847:
	ldr	x0, [x20, 2328]
	mov	x1, x27
	bl	HEVC_ue_v
	add	x1, x22, x21, lsl 2
	str	w0, [x1, 24]
.L1848:
	cmp	w0, 31
	bhi	.L1887
	mov	w24, 0
.L1850:
	cbz	w24, .L1888
	cmp	w24, 1
	beq	.L1883
.L1856:
	add	w24, w24, 1
	cmp	w24, 2
	bne	.L1850
.L1855:
	add	w19, w19, 1
	cmp	w23, w19
	bcs	.L1857
	mov	w0, 0
.L1882:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1887:
	mov	w2, w0
	mov	x1, x26
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
	b	.L1850
	.p2align 3
.L1886:
	add	x24, x22, x21, lsl 2
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	str	wzr, [x24, 24]
	uxtb	w0, w0
	cbnz	w0, .L1860
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1847
	ldr	w0, [x24, 24]
	b	.L1848
	.p2align 3
.L1885:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x22, 1]
	ldrh	w0, [x22]
	cbz	w0, .L1841
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22, 2]
	cbnz	w0, .L1889
.L1843:
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	ldrb	w0, [x22, 2]
	cbnz	w0, .L1890
.L1844:
	ldr	x0, [x20, 2328]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 12]
	mov	w1, 5
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x22, 16]
	mov	w1, 5
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L1841
.L1861:
	mov	w0, -1
	b	.L1882
.L1890:
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	b	.L1844
.L1889:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x22, 3]
	mov	w1, 5
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L1843
.L1888:
	ldrb	w0, [x22]
	cbnz	w0, .L1863
	mov	w24, 1
.L1883:
	ldrb	w0, [x22, 1]
	cbz	w0, .L1855
.L1863:
	add	x0, x21, 4
	str	wzr, [x29, 108]
	lsl	x0, x0, 2
	str	x0, [x29, 96]
	b	.L1859
.L1858:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x29, 96]
	ldr	w1, [x29, 108]
	add	x0, x22, x0
	ldr	w0, [x0, 8]
	cmp	w0, w1
	bcc	.L1856
.L1859:
	ldr	w2, [x29, 108]
	mov	x1, x28
	ldr	x0, [x20, 2328]
	add	w2, w2, 1
	str	w2, [x29, 108]
	bl	HEVC_ue_v
	ldr	x1, .LC430
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldrb	w0, [x22, 2]
	cbz	w0, .L1858
	ldr	x1, .LC432
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC434
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	b	.L1858
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
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21, 3]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L1892
	ldr	x1, .LC436
	uxtb	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
.L1892:
	ldr	x0, [x20, 2328]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 63
	str	w0, [x21, 8]
	bhi	.L1940
	ldr	x0, [x20, 2328]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 7
	mov	w24, w0
	bhi	.L1941
	str	w0, [x21, 12]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x21, 1]
	mov	w1, 16
	ldr	x0, [x20, 2328]
	bl	BsGet
	mov	w1, 65535
	cmp	w0, w1
	bne	.L1942
	mov	w3, w24
	mov	w2, 1
	add	x1, x21, 124
	mov	x0, x20
	bl	HEVC_DecPTL
	cbnz	w0, .L1943
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w25, w0
	tbnz	w24, #31, .L1902
	ldr	x28, .LC448
	add	w23, w24, 1
	ldr	x27, .LC450
	mov	w19, 0
	ldr	x26, .LC452
	b	.L1904
	.p2align 3
.L1901:
	cmp	w23, w19
	beq	.L1902
.L1904:
	add	x22, x21, x19, sxtw 2
	ldr	x0, [x20, 2328]
	mov	x1, x28
	add	w19, w19, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 28]
	mov	x1, x27
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x22, 60]
	mov	x1, x26
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x22, 92]
	cbnz	w25, .L1901
	cmp	w24, w19
	blt	.L1902
	.p2align 2
.L1927:
	add	x0, x21, x19, sxtw 2
	ldr	w1, [x21, 28]
	add	w19, w19, 1
	cmp	w23, w19
	str	w1, [x0, 28]
	ldr	w1, [x21, 60]
	str	w1, [x0, 60]
	ldr	w1, [x21, 92]
	str	w1, [x0, 92]
	bne	.L1927
.L1902:
	ldr	x0, [x20, 2328]
	mov	w1, 6
	bl	BsGet
	str	w0, [x21, 16]
	ldr	x1, .LC446
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 1023
	str	w0, [x21, 20]
	bhi	.L1944
	cmp	w0, wzr
	mov	w22, 1
	ble	.L1906
	.p2align 2
.L1926:
	mov	w19, 0
	.p2align 2
.L1907:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	add	w19, w19, w1
	bl	BsGet
	ldr	w0, [x21, 16]
	cmp	w0, w19
	bcs	.L1907
	ldr	w0, [x21, 20]
	add	w22, w22, 1
	cmp	w0, w22
	bge	.L1926
.L1906:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1915
	ldr	x0, [x20, 2328]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1945
.L1912:
	ldr	x1, .LC458
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 1024
	str	w0, [x21, 24]
	bhi	.L1913
	cmp	w0, wzr
	ble	.L1915
	ldr	x22, .LC462
	mov	w19, 0
	ldr	x0, [x20, 2328]
	mov	x1, x22
	bl	HEVC_ue_v
	mov	w2, 1
	.p2align 2
.L1920:
	mov	w3, w24
	add	x1, x29, 104
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_DecHrdParam
	cbnz	w0, .L1946
.L1917:
	ldr	w0, [x21, 24]
	mov	x1, x22
	cmp	w0, w19
	ble	.L1915
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	mov	w2, 1
	cbz	w19, .L1920
	ldr	x0, [x20, 2328]
	mov	w1, w2
	add	w19, w19, 1
	bl	BsGet
	mov	w2, w0
	mov	w3, w24
	add	x1, x29, 104
	mov	x0, x20
	bl	HEVC_DecHrdParam
	cbz	w0, .L1917
.L1946:
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
.L1915:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1911
	.p2align 2
.L1935:
	ldr	x0, [x20, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1911
	ldr	x2, [x20, 2368]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L1947
.L1911:
	mov	w0, 0
.L1936:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L1947:
	ldr	x0, [x20, 2328]
	bl	BsGet
	b	.L1935
.L1945:
	ldr	x1, .LC456
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	b	.L1912
.L1942:
	ldr	x1, .LC442
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
.L1940:
	ldr	x1, .LC438
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
.L1943:
	ldr	x1, .LC444
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
.L1941:
	ldr	x1, .LC440
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
.L1944:
	ldr	x1, .LC454
.L1938:
	mov	w2, w0
	mov	w3, 1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1936
.L1913:
	ldr	x1, .LC460
	b	.L1938
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
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	cmp	w0, 15
	mov	w21, w0
	bhi	.L1954
	uxtw	x19, w0
	ldr	x0, [x20, 2336]
	lsl	x1, x19, 7
	add	x19, x1, x19, lsl 2
	add	x1, x0, x19
	ldrb	w0, [x0, x19]
	cbnz	w0, .L1955
	str	w21, [x1, 4]
	mov	x0, x20
	ldr	x1, [x20, 2336]
	add	x1, x1, x19
	bl	HEVC_ProcessVPS
	mov	w22, w0
	cbnz	w0, .L1956
	ldr	x0, [x20, 2336]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2336]
	strb	w1, [x0, x19]
.L1950:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1955:
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
	cbnz	w0, .L1957
	ldr	x0, [x20, 2336]
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
.L1957:
	ldr	x1, .LC470
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1950
	.p2align 3
.L1954:
	ldr	x1, .LC466
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1950
.L1956:
	ldr	x1, .LC472
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x20, 2336]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2336]
	strb	wzr, [x0, x19]
	b	.L1950
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
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2003
.L1960:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2004
.L1962:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2005
.L1964:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2006
.L1966:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 1
	ldr	x0, [x19, 2328]
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1967
	ldr	x1, .LC479
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	w0, [x21, 60]
	cmp	w0, 3
	bhi	.L2007
	ldr	x1, .LC483
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC485
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC487
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
.L1967:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1970
	ldr	x0, [x19, 2328]
	mov	w1, 32
	bl	BsGet
	str	w0, [x20, 36]
	mov	w1, 32
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 40]
	ldr	w1, [x20, 36]
	cbnz	w1, .L2008
.L1971:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2009
.L1972:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2010
.L1970:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	mov	w0, 0
	cbnz	w1, .L2011
.L1969:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2011:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC494
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	cmp	w0, 4095
	bhi	.L2012
.L1973:
	ldr	x1, .LC498
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC500
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC502
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC504
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2006:
	ldr	x1, .LC475
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC477
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	b	.L1966
	.p2align 3
.L2003:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	str	w0, [x20, 8]
	bne	.L1960
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsGet
	str	w0, [x20, 12]
	mov	w1, 16
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 16]
	b	.L1960
	.p2align 3
.L2005:
	ldr	x0, [x19, 2328]
	mov	w1, 3
	bl	BsGet
	str	w0, [x20, 20]
	mov	w1, 1
	ldr	x0, [x19, 2328]
	bl	BsGet
	strb	w0, [x20]
	mov	w1, 1
	ldr	x0, [x19, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L1964
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 28]
	mov	w1, 8
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 32]
	b	.L1964
	.p2align 3
.L2004:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	b	.L1962
	.p2align 3
.L2010:
	ldr	w3, [x21, 52]
	mov	w2, 1
	add	x1, x20, 44
	mov	x0, x19
	bl	HEVC_DecHrdParam
	cbz	w0, .L1970
	ldr	x1, .LC492
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1969
	.p2align 3
.L2009:
	ldr	x1, .LC490
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	b	.L1972
	.p2align 3
.L2008:
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
	b	.L1971
	.p2align 3
.L2012:
	ldr	x1, .LC496
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1973
	.p2align 3
.L2007:
	ldr	x1, .LC481
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1969
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
	bls	.L2018
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2018:
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
	ldr	x0, [x21, 2328]
	bl	HEVC_ue_v
	ldr	x1, .LC508
	ldr	x0, [x21, 2328]
	bl	HEVC_ue_v
	cmp	w0, 1024
	mov	w22, w0
	bhi	.L2020
	mov	w19, 0
	cbz	w0, .L2026
	ldr	x24, .LC512
	ldr	x23, .LC514
	.p2align 2
.L2029:
	ldr	x0, [x21, 2328]
	mov	w1, 6
	bl	BsGet
	sub	w20, w0, #19
	ldr	x0, [x21, 2328]
	mov	w1, 3
	bl	BsGet
	cmp	w20, 1
	mov	x1, x24
	bls	.L2023
	ldr	x0, [x21, 2328]
	bl	HEVC_ue_v
.L2023:
	mov	x1, x23
	cbz	w19, .L2024
	ldr	x0, [x21, 2328]
	bl	HEVC_se_v
.L2024:
	add	w19, w19, 1
	cmp	w22, w19
	bne	.L2029
.L2026:
	ldr	x0, [x21, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L2022:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2020:
	ldr	x1, .LC510
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2022
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
	beq	.L2034
	ldr	x1, .LC516
	ldr	x0, [x19, 2328]
	bl	HEVC_se_v
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
	mov	w0, 0
.L2033:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2034:
	mov	w0, -1
	b	.L2033
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
	beq	.L2053
	ldr	x1, .LC518
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2037
.L2050:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x22]
.L2036:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2037:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2061
.L2038:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	mov	w23, 3
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
.L2040:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	uxtb	w1, w0
	cbz	w1, .L2043
	and	w0, w0, 255
	mov	w19, 0
	add	w21, w0, 1
	.p2align 2
.L2042:
	ldr	x0, [x20, 2328]
	mov	w1, 16
	add	w19, w19, 1
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 16
	bl	BsGet
	cmp	w21, w19
	bne	.L2042
.L2043:
	subs	w23, w23, #1
	bne	.L2040
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2044
.L2048:
	add	x26, x22, 3
	mov	x23, x22
	mov	w25, 33
.L2045:
	ldr	x0, [x20, 2328]
	mov	w1, 8
	sub	w24, w23, w22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 40]
	cbz	w0, .L2052
	mov	w21, 0
	.p2align 2
.L2051:
	uxtw	x19, w21
	ldr	x0, [x20, 2328]
	mov	w1, 16
	add	w21, w21, 1
	umaddl	x19, w24, w25, x19
	bl	BsGet
	mov	w1, 16
	add	x19, x22, x19, lsl 1
	strh	w0, [x19, 44]
	ldr	x0, [x20, 2328]
	bl	BsGet
	strh	w0, [x19, 242]
	ldrb	w0, [x23, 40]
	add	w0, w0, 1
	cmp	w0, w21
	bhi	.L2051
.L2052:
	add	x23, x23, 1
	cmp	x23, x26
	bne	.L2045
	b	.L2050
	.p2align 3
.L2053:
	mov	w0, -1
	b	.L2036
.L2044:
	ldr	x0, [x20, 2328]
	mov	w1, 4
	add	x19, x22, 4
	add	x24, x22, 40
	bl	BsGet
	ldr	x23, .LC520
.L2046:
	add	x21, x19, 12
.L2047:
	ldr	x0, [x20, 2328]
	mov	x1, x23
	bl	HEVC_se_v
	str	w0, [x19], 4
	cmp	x19, x21
	bne	.L2047
	cmp	x19, x24
	bne	.L2046
	b	.L2048
.L2061:
	ldr	x0, [x20, 2328]
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 8
	ldr	x0, [x20, 2328]
	bl	BsGet
	ldr	x0, [x20, 2328]
	mov	w1, 8
	bl	BsGet
	b	.L2038
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
	ldr	x0, [x19, 2368]
	ldr	w0, [x0, 16]
	cmp	w0, 39
	beq	.L2111
	cmp	w20, 5
	beq	.L2091
	cmp	w20, 132
	beq	.L2092
	mov	w20, 0
	cbz	w21, .L2085
	.p2align 2
.L2105:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2105
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbnz	w0, .L2095
	.p2align 2
.L2099:
	mov	w0, 0
.L2087:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2091:
	mov	w2, w21
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Unregistered
	cbnz	w0, .L2088
.L2085:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbz	w0, .L2099
.L2095:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_Payload_Extension_Present
	cbnz	w0, .L2112
	.p2align 2
.L2098:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	bl	BsIsByteAligned
	cbz	w0, .L2098
	b	.L2099
	.p2align 3
.L2111:
	cmp	w20, 147
	bls	.L2113
.L2064:
	mov	w20, 0
	cbz	w21, .L2085
	.p2align 2
.L2104:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2104
	b	.L2085
	.p2align 3
.L2092:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Decoded_Picture_Hash
	cbz	w0, .L2085
	.p2align 2
.L2088:
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2113:
	ldr	x0, .LC521
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx2066
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2066:
	.section	.rodata
	.align	0
	.align	2
.L2066:
	.byte	(.L2065 - .Lrtx2066) / 4
	.byte	(.L2067 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2068 - .Lrtx2066) / 4
	.byte	(.L2091 - .Lrtx2066) / 4
	.byte	(.L2070 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2071 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2072 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2073 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2074 - .Lrtx2066) / 4
	.byte	(.L2075 - .Lrtx2066) / 4
	.byte	(.L2076 - .Lrtx2066) / 4
	.byte	(.L2077 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2078 - .Lrtx2066) / 4
	.byte	(.L2079 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2080 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2081 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2082 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2064 - .Lrtx2066) / 4
	.byte	(.L2083 - .Lrtx2066) / 4
	.text
	.p2align 3
.L2112:
	ldr	x1, .LC523
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	b	.L2098
.L2083:
	add	x0, x22, 618
	cmp	x19, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L2088
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 618]
	b	.L2085
.L2082:
	add	x1, x22, 612
	mov	x0, x19
	bl	HEVC_Sei_Content_Light_Level_Information
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2081:
	add	x1, x22, 128
	mov	x0, x19
	bl	HEVC_Sei_Color_Remapping_Info
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2080:
	add	x1, x22, 568
	cmp	x19, xzr
	ccmp	x1, xzr, 4, ne
	beq	.L2088
	mov	w0, 1
	strb	w0, [x22, 568]
	mov	x0, x19
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.14
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2079:
	add	x22, x22, 568
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2088
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	b	.L2085
.L2078:
	mov	w3, w21
	mov	x2, x23
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Scalable_Nesting
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2077:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2076:
	add	x2, x23, 2108
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Dec_Unit_Info
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2075:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Active_Param_sets
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2074:
	mov	w2, w21
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2073:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Display_Orientation
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2072:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2071:
	add	x1, x22, 619
	mov	x0, x19
	bl	HEVC_Sei_Tone_Mapping_Info
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2070:
	add	x1, x22, 568
	mov	x0, x19
	bl	HEVC_Sei_Recovery_Point
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2068:
	mov	w2, w21
	add	x1, x22, 56
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2067:
	add	x2, x23, 2064
	add	x1, x22, 8
	mov	x0, x19
	bl	HEVC_Sei_Pic_Timming
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.p2align 3
.L2065:
	add	x2, x23, 2108
	mov	x1, x22
	mov	x0, x19
	bl	HEVC_Sei_Buf_Period
	cbz	w0, .L2085
	mov	w0, -1
	b	.L2087
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	3
.LC521:
	.xword	.L2066
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
	ldr	x0, [x19, 2328]
	b	.L2115
	.p2align 3
.L2117:
	bl	BsSkip
	add	w20, w20, 255
	ldr	x0, [x19, 2328]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2124
.L2115:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2328]
	beq	.L2117
	bl	BsGet
	mov	w21, 0
	mov	w24, w0
	ldr	x0, [x19, 2328]
	b	.L2118
	.p2align 3
.L2119:
	bl	BsSkip
	add	w21, w21, 255
	ldr	x0, [x19, 2328]
	ldr	w3, [x0, 32]
	ldr	w4, [x0, 24]
	add	w1, w3, 8
	cmp	w1, w4
	bhi	.L2125
.L2118:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2328]
	beq	.L2119
	bl	BsGet
	add	w4, w0, w21
	mov	x1, x22
	add	w3, w24, w20
	mov	x2, x23
	mov	x0, x19
	bl	HEVC_Sei_Payload
	mov	w1, 0
	cbnz	w0, .L2126
.L2116:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2124:
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
.L2125:
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
.L2126:
	ldr	x1, .LC527
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L2116
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
	beq	.L2133
	ldr	x20, [x19, 2360]
	add	x21, x19, 3328
	cbnz	x20, .L2136
	b	.L2139
	.p2align 3
.L2131:
	ldr	x0, [x19, 2328]
	bl	BsIsByteAligned
	cbz	w0, .L2140
	mov	x0, x19
	bl	HEVC_More_Rbsp_Data
	cbz	w0, .L2141
.L2136:
	mov	x2, x20
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbz	w0, .L2131
	ldr	x1, .LC531
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2129:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2141:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 128
	bne	.L2142
.L2133:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2140:
	ldr	x1, .LC533
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2142:
	ldr	x1, .LC535
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2129
.L2139:
	ldr	x1, .LC529
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2129
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
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2144
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	mov	w20, w0
	ldr	x1, .LC537
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	cmp	w0, 63
	mov	w23, w0
	bhi	.L2159
	and	w20, w20, 255
	cmp	w0, w20
	bcc	.L2150
	ldr	x24, .LC541
	.p2align 2
.L2149:
	ldr	x0, [x19, 2328]
	mov	w1, 3
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2328]
	mov	x1, x24
	bl	HEVC_ue_v
	cmp	w23, w20
	bcs	.L2149
.L2150:
	ldr	x0, [x19, 2328]
	bl	BsToNextByte
.L2148:
	mov	x2, x22
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbnz	w0, .L2160
	ldr	x0, [x19, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2154
	ldr	x1, [x19, 2368]
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	bcc	.L2148
.L2154:
	mov	w0, 0
.L2146:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2144:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2150
	ldr	x0, [x19, 2328]
	mov	w1, 3
	mov	w20, 0
	bl	BsGet
	ldr	x1, .LC543
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	cmp	w0, 63
	add	w23, w0, 1
	bhi	.L2161
	.p2align 2
.L2155:
	ldr	x0, [x19, 2328]
	mov	w1, 6
	add	w20, w20, 1
	bl	BsGet
	cmp	w20, w23
	bne	.L2155
	b	.L2150
	.p2align 3
.L2160:
	ldr	x1, .LC546
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2159:
	ldr	x1, .LC539
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2146
.L2161:
	ldr	x1, .LC545
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2146
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
.L2163:
	ldr	w0, [x27, 1888]
	cbz	w0, .L2183
	uxtw	x0, w25
	mov	w24, 0
	ldp	x1, x21, [x29, 136]
	str	x0, [x29, 128]
	lsl	x0, x0, 2
	str	x1, [x29, 152]
	str	x0, [x29, 120]
.L2182:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	w19, [x27]
	mov	w1, 64
	uxtb	w0, w0
	cmp	w19, 64
	csel	w19, w19, w1, le
	cbz	w25, .L2164
	add	x22, x20, 340
	cbz	w0, .L2196
	cmp	w25, 1
	bls	.L2189
	ldr	x1, .LC556
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 254
	bhi	.L2197
	add	w28, w0, 8
	ldr	x0, [x29, 152]
	str	w28, [x0]
.L2175:
	cmp	w19, wzr
	mov	x26, 0
	bgt	.L2179
	b	.L2174
	.p2align 3
.L2178:
	ldr	w0, [x22, x26, lsl 2]
	add	w1, w1, w2
	and	w1, w1, 255
	add	x26, x26, 1
	sub	w28, w1, w2
	cmp	w19, w26
	strb	w28, [x21, x0]
	ble	.L2174
.L2179:
	ldr	x0, [x20, 2328]
	mov	x1, x23
	bl	HEVC_se_v
	add	w2, w0, w28
	add	w0, w0, 128
	add	w1, w2, 256
	cmp	w0, 255
	asr	w2, w1, 31
	lsr	w2, w2, 24
	bls	.L2178
	ldr	x1, .LC562
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2194:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L2196:
	ldr	x1, .LC550
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L2186
	sub	w0, w24, w0
	cmp	w25, 1
	uxtb	w0, w0
	bls	.L2169
	cmp	w0, w24
	beq	.L2188
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	ldr	x2, [x29, 112]
	lsl	x1, x1, 1
	add	x1, x1, x0, uxtb
	add	x1, x1, 384
	ldr	w1, [x2, x1, lsl 2]
.L2170:
	ldr	x2, [x29, 152]
	str	w1, [x2]
.L2169:
	cmp	w0, w24
	beq	.L2198
	ldp	x1, x2, [x29, 120]
	sub	x1, x1, x2
	lsl	x1, x1, 1
	add	x0, x1, x0, uxtb
	ldr	x1, [x29, 112]
	add	x1, x1, x0, lsl 6
.L2172:
	cbz	x1, .L2199
	ldr	x0, .LC548
	sxtw	x2, w19
	ldr	x3, [x0, 104]
	mov	x0, x21
	blr	x3
.L2174:
	add	w24, w24, 1
	cmp	w24, 6
	beq	.L2183
	ldr	x0, [x29, 152]
	add	x21, x21, 64
	add	x0, x0, 4
	str	x0, [x29, 152]
	ldr	w0, [x27, 1888]
	cmp	w0, w24
	bhi	.L2182
	.p2align 2
.L2183:
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
	bne	.L2163
	mov	w0, 0
	b	.L2194
	.p2align 3
.L2189:
	mov	w28, 8
	b	.L2175
.L2198:
	mov	w1, w24
	mov	w0, w25
	bl	HEVC_GetScalingListDefaultAddress
	mov	x1, x0
	b	.L2172
.L2188:
	mov	w1, 16
	b	.L2170
.L2197:
	ldr	x1, .LC558
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2194
.L2186:
	ldr	x1, .LC552
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2194
.L2199:
	ldr	x1, .LC554
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2194
.L2164:
	cbz	w0, .L2184
	mov	w28, 8
	ldr	x22, [x29, 96]
	b	.L2175
.L2184:
	ldr	x1, .LC550
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L2186
	sub	w0, w24, w0
	uxtb	w0, w0
	b	.L2169
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
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 1
	str	w0, [x19, 60]
	mov	w21, w0
	beq	.L2201
	cmp	w0, 3
	bhi	.L2351
	ldr	x1, .LC569
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2342:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2351:
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
.L2201:
	ldr	x1, .LC571
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 8192
	str	w0, [x19, 64]
	bhi	.L2352
	ldr	x1, .LC576
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 4096
	str	w0, [x19, 68]
	bhi	.L2353
	ldr	w2, [x19, 428]
	ldr	w1, [x19, 64]
	cmp	w2, 120
	mul	w0, w0, w1
	beq	.L2209
	bgt	.L2210
	cmp	w2, 60
	beq	.L2274
	ble	.L2354
	cmp	w2, 90
	beq	.L2214
	cmp	w2, 93
	beq	.L2215
	cmp	w2, 63
	beq	.L2355
.L2208:
	ldr	x1, .LC580
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
	.p2align 3
.L2352:
	ldr	x1, .LC573
.L2347:
	mov	w0, w21
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbz	x4, .L2344
.L2346:
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
.L2372:
	ldr	x1, .LC667
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2344:
	mov	w0, -1
	b	.L2342
	.p2align 3
.L2274:
	mov	w2, 30720
	mov	w1, 122880
	.p2align 2
.L2211:
	cmp	w0, w2
	bhi	.L2220
	mov	w0, 16
	str	w0, [x19, 184]
.L2221:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2224
	ldr	x1, .LC582
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldr	x21, .LC583
	ldr	w2, [x19, 60]
	add	x22, x21, 40
	ldr	x1, .LC585
	ldr	w2, [x22, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 72]
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldp	w2, w1, [x19, 60]
	ldr	w3, [x19, 72]
	ldr	w2, [x22, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 76]
	sub	w1, w1, w0
	tbnz	w1, #31, .L2356
	ldr	x1, .LC589
	add	x21, x21, 56
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	x1, .LC591
	ldr	w2, [x21, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 80]
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	w1, [x19, 68]
	ldr	w3, [x19, 80]
	ldr	w2, [x21, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 84]
	sub	w1, w1, w0
	tbnz	w1, #31, .L2357
.L2224:
	ldr	x1, .LC595
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 2
	str	w2, [x19, 88]
	bhi	.L2358
	ldr	x1, .LC599
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 6
	str	w2, [x19, 96]
	bhi	.L2359
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
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 12
	bhi	.L2360
	add	w0, w0, 4
	mov	w1, 1
	stp	w0, w0, [x19, 116]
	mov	w23, 0
	mov	w21, 0
	ldr	x0, [x20, 2328]
	bl	BsGet
	ldr	x26, .LC607
	mov	w27, w0
	ldr	x25, .LC609
	ldr	x24, .LC611
	b	.L2235
	.p2align 3
.L2229:
	ldr	w0, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w0
	bhi	.L2234
.L2235:
	add	x22, x19, x21, uxtw 2
	ldr	x0, [x20, 2328]
	mov	x1, x26
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 328]
	mov	x1, x25
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x22, 360]
	mov	x1, x24
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x22, 392]
	ldr	w0, [x22, 328]
	cmp	w23, w0
	csel	w23, w23, w0, cs
	cbnz	w27, .L2229
	ldr	w2, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w2
	bhi	.L2234
	.p2align 2
.L2316:
	add	x0, x19, x21, uxtw 2
	ldr	w1, [x19, 328]
	add	w21, w21, 1
	cmp	w21, w2
	str	w1, [x0, 328]
	ldr	w1, [x19, 360]
	str	w1, [x0, 360]
	ldr	w1, [x19, 392]
	str	w1, [x0, 392]
	bls	.L2316
.L2234:
	ldr	w0, [x19, 184]
	ldr	x1, .LC613
	cmp	w0, w23
	csel	w23, w0, w23, ls
	str	w23, [x19, 184]
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L2361
	ldr	x1, .LC617
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w21, w0
	bhi	.L2362
	add	w2, w22, 3
	add	w1, w0, w2
	sub	w0, w1, #4
	cmp	w0, 2
	stp	w2, w1, [x19, 124]
	bhi	.L2363
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
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L2364
	ldr	x1, .LC627
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 3
	bhi	.L2365
	ldr	w2, [x19, 124]
	add	w1, w22, 2
	str	w1, [x19, 148]
	cmp	w1, w2
	bcs	.L2366
	add	w1, w0, w1
	str	w1, [x19, 152]
	cmp	w1, 5
	bhi	.L2245
	ldr	w0, [x19, 128]
	cmp	w1, w0
	bhi	.L2245
	ldr	x1, .LC635
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x19, 164]
	ldr	w1, [x19, 128]
	ldr	w2, [x19, 148]
	sub	w1, w1, w2
	cmp	w0, w1
	bhi	.L2367
	ldr	x1, .LC639
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x19, 168]
	ldr	w1, [x19, 128]
	ldr	w4, [x19, 148]
	sub	w1, w1, w4
	cmp	w0, w1
	bhi	.L2248
	ldr	w2, [x19, 140]
	mov	w3, 1
	lsl	w0, w3, w4
	mov	w1, 0
	lsr	w2, w2, w21
	cmp	w2, w0
	bls	.L2250
	.p2align 2
.L2315:
	add	w1, w1, 1
	add	w0, w4, w1
	lsl	w0, w3, w0
	cmp	w0, w2
	bcc	.L2315
.L2250:
	add	w1, w21, w1
	str	w1, [x19, 172]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3]
	cbz	w0, .L2252
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 4]
	cbnz	w0, .L2368
.L2252:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 6]
	cbnz	w0, .L2253
	ldr	w2, [x19, 68]
	cmp	w2, 64
	bls	.L2369
.L2253:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	str	w0, [x19, 104]
	cbz	w0, .L2254
	ldr	x0, [x20, 2328]
	mov	w1, 4
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 108]
	mov	w1, 4
	ldr	x0, [x20, 2328]
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 112]
	ldr	x1, .LC647
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w21, w0
	bhi	.L2370
.L2255:
	ldr	x1, .LC651
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w22, w0
	bhi	.L2371
.L2256:
	add	w0, w21, 3
	str	w0, [x19, 156]
	add	w0, w22, w0
	str	w0, [x19, 160]
	cmp	w0, 5
	bhi	.L2257
	ldr	w1, [x19, 128]
	cmp	w0, w1
	bhi	.L2257
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 7]
.L2254:
	ldr	x1, .LC657
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 64
	str	w0, [x19, 176]
	bhi	.L2259
	mov	w21, 0
	cbnz	w0, .L2314
	b	.L2265
	.p2align 3
.L2263:
	ldr	w0, [x19, 176]
	cmp	w21, w0
	bcs	.L2265
.L2314:
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
	cbz	w0, .L2263
	ldr	x1, .LC661
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
	.p2align 3
.L2220:
	cmp	w0, w1, lsr 1
	bhi	.L2222
	mov	w0, 12
	str	w0, [x19, 184]
	b	.L2221
	.p2align 3
.L2353:
	ldr	x1, .LC578
	b	.L2347
	.p2align 3
.L2210:
	cmp	w2, 156
	beq	.L2217
	bgt	.L2218
	cmp	w2, 150
	beq	.L2217
	cmp	w2, 153
	beq	.L2217
	cmp	w2, 123
	bne	.L2208
.L2209:
	mov	w2, 32768
	mov	w1, 2228224
	movk	w2, 0x8, lsl 16
	b	.L2211
	.p2align 3
.L2222:
	lsl	w2, w1, 2
	sub	w1, w2, w1
	cmp	w0, w1, lsr 2
	bhi	.L2223
	mov	w0, 8
	str	w0, [x19, 184]
	b	.L2221
	.p2align 3
.L2358:
	ldr	x1, .LC597
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbz	x4, .L2344
	ldr	w1, [x19, 88]
	mov	w3, 8
	ldr	w0, [x20, 252]
	add	x2, x29, 104
	stp	wzr, w1, [x29, 104]
	mov	w1, 119
	blr	x4
	mov	w0, -1
	b	.L2342
	.p2align 3
.L2265:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbz	w0, .L2262
	ldr	x1, .LC663
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 32
	str	w0, [x19, 180]
	bhi	.L2268
	mov	w22, 0
	cbz	w0, .L2262
	.p2align 2
.L2313:
	ldr	w1, [x19, 116]
	uxtw	x21, w22
	ldr	x0, [x20, 2328]
	add	w22, w22, 1
	bl	BsGet
	add	x2, x19, x21, lsl 2
	add	x21, x19, x21
	mov	w1, 1
	str	w0, [x2, 196]
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x21, 13]
	ldr	w0, [x19, 180]
	cmp	w22, w0
	bcc	.L2313
.L2262:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 11]
	cbz	w0, .L2267
	mov	x2, x19
	add	x1, x19, 2064
	mov	x0, x20
	bl	HEVC_DecVuiParam
	cbnz	w0, .L2372
.L2267:
	ldp	w3, w4, [x19, 64]
	ldr	w1, [x19, 2076]
	ldr	w2, [x19, 2080]
	ldr	w0, [x19, 2072]
	bl	HEVC_GetDar
	str	w0, [x19, 2068]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 12]
	cbnz	w0, .L2341
	.p2align 2
.L2272:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
	b	.L2342
	.p2align 3
.L2373:
	ldr	x0, [x20, 2328]
	bl	BsGet
.L2341:
	ldr	x0, [x20, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2272
	ldr	x2, [x20, 2368]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcs	.L2272
	b	.L2373
	.p2align 3
.L2218:
	cmp	w2, 183
	beq	.L2219
	cmp	w2, 186
	beq	.L2219
	cmp	w2, 180
	bne	.L2208
.L2219:
	mov	w2, 8912896
	mov	w1, 35651584
	b	.L2211
	.p2align 3
.L2354:
	cbz	w2, .L2213
	cmp	w2, 30
	bne	.L2208
.L2213:
	mov	w2, 9216
	mov	w1, 36864
	b	.L2211
	.p2align 3
.L2217:
	mov	w2, 2228224
	mov	w1, 8912896
	b	.L2211
	.p2align 3
.L2214:
	mov	w2, 7168
	mov	w1, 28672
	movk	w2, 0x2, lsl 16
	movk	w1, 0x8, lsl 16
	b	.L2211
.L2355:
	mov	w2, 61440
	mov	w1, 245760
	b	.L2211
	.p2align 3
.L2215:
	mov	w2, 245760
	mov	w1, 983040
	b	.L2211
	.p2align 3
.L2223:
	mov	w0, 6
	str	w0, [x19, 184]
	b	.L2221
.L2369:
	ldr	x1, .LC645
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC574
	ldr	x4, [x0]
	cbnz	x4, .L2346
	mov	w0, -1
	b	.L2342
.L2368:
	add	x1, x19, 432
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbz	w0, .L2252
	ldr	x1, .LC643
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
	.p2align 3
.L2245:
	ldr	x1, .LC633
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2371:
	ldr	x1, .LC653
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2256
.L2370:
	ldr	x1, .LC649
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2255
.L2360:
	ldr	x1, .LC605
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2361:
	ldr	x1, .LC615
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2364:
	ldr	x1, .LC625
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2367:
	ldr	x1, .LC637
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2257:
	ldr	x1, .LC655
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2363:
	ldr	x1, .LC621
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2362:
	ldr	x1, .LC619
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2365:
	ldr	x1, .LC629
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2359:
	ldr	x1, .LC601
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2366:
	ldr	x1, .LC631
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2248:
	ldr	x1, .LC641
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2356:
	ldr	x1, .LC587
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2259:
	ldr	x1, .LC659
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2357:
	ldr	x1, .LC593
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
.L2268:
	ldr	x1, .LC665
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2342
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
	ldr	x0, [x19, 2328]
	mov	w1, 4
	bl	BsGet
	mov	w24, w0
	ldr	w2, [x19, 156]
	cmp	w2, w0
	bls	.L2387
	ldr	x0, [x19, 2368]
	ldr	w0, [x0, 24]
	cbz	w0, .L2388
	mov	w20, 0
	mov	w25, 0
.L2377:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	mov	w3, w20
	mov	w2, 1
	add	x1, x29, 96
	mov	x0, x19
	bl	HEVC_DecPTL
	cbnz	w0, .L2389
	ldr	x1, .LC678
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	mov	w21, w0
	ldr	w2, [x19, 160]
	cmp	w0, w2
	bcs	.L2390
	mov	w20, 12660
	ldr	x1, [x19, 2344]
	uxtb	w26, w23
	umull	x20, w0, w20
	add	x1, x1, x20
	ldrb	w0, [x1, 1]
	cbz	w0, .L2381
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
	cbnz	w0, .L2391
	ldr	x0, [x19, 2344]
	mov	w1, 1
	ldr	x3, [x22, 112]
	mov	x2, 12660
	strb	w1, [x27, 3328]
	add	x0, x0, x20
	strb	w1, [x23, 1]
	mov	x1, x23
	blr	x3
	ldr	x0, [x19, 2344]
	add	x20, x0, x20
	str	x20, [x19, 2360]
.L2376:
	mov	w0, w24
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2388:
	ldr	x0, [x19, 2328]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 8
	mov	w20, w0
	mov	w25, w0
	bls	.L2377
	ldr	x1, .LC674
	mov	w2, 8
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2376
	.p2align 3
.L2381:
	str	w24, [x1, 48]
	mov	x2, 8
	add	x1, x29, 96
	ldr	x0, [x19, 2344]
	add	x0, x0, x20
	str	w25, [x0, 52]
	ldr	x0, [x19, 2344]
	add	x0, x0, x20
	strb	w26, [x0, 2]
	ldr	x0, [x19, 2344]
	add	x0, x0, x20
	strb	wzr, [x0, 46]
	ldr	x0, [x19, 2344]
	ldr	x3, [x22, 104]
	add	x0, x0, x20
	add	x0, x0, 424
	blr	x3
	ldr	x1, [x19, 2344]
	mov	x0, x19
	add	x1, x1, x20
	str	w21, [x1, 56]
	ldr	x1, [x19, 2344]
	add	x1, x1, x20
	bl	HEVC_ProcessSPS
	mov	w24, w0
	cbnz	w0, .L2392
	ldr	x0, [x19, 2344]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2344]
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2344]
	add	x20, x0, x20
	str	x20, [x19, 2360]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2390:
	ldr	x1, .LC680
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 160]
	cmp	w21, w1
	bcc	.L2386
	ldr	x0, .LC681
	ldr	x4, [x0]
	cbz	x4, .L2386
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
.L2386:
	mov	w24, -1
	b	.L2376
	.p2align 3
.L2389:
	ldr	x1, .LC676
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2376
	.p2align 3
.L2387:
	ldr	x1, .LC672
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2376
	.p2align 3
.L2391:
	ldr	x3, [x19, 2344]
	mov	w2, w21
	ldr	x1, .LC684
	mov	w0, 1
	add	x20, x3, x20
	str	x20, [x19, 2360]
	mov	w24, -1
	bl	dprint_vfmw
	b	.L2376
.L2392:
	ldr	x1, .LC686
	mov	w2, w21
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2344]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2344]
	add	x20, x0, x20
	strb	wzr, [x20, 1]
	b	.L2376
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
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	str	w0, [x19, 32]
	tbnz	w0, #31, .L2394
	ldr	w1, [x20, 160]
	cmp	w0, w1
	bge	.L2394
	ldr	x1, [x20, 2344]
	mov	w21, 12660
	smaddl	x21, w0, w21, x1
	ldrb	w1, [x21, 1]
	cbz	w1, .L2502
	ldr	x0, [x20, 2328]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, w22
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 3
	ldr	x0, [x20, 2328]
	bl	BsGet
	str	w0, [x19, 36]
	mov	w1, w22
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, w22
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 5]
	ldr	x1, .LC695
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 40]
	bhi	.L2503
	ldr	x1, .LC699
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 44]
	bhi	.L2504
	ldr	x1, .LC703
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w2, w0, 26
	str	w2, [x19, 48]
	mov	w0, 51
	ldr	w3, [x21, 92]
	neg	w1, w3
	cmp	w2, w1
	ccmp	w2, w0, 0, ge
	bgt	.L2505
	ldr	x0, [x20, 2328]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, w22
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, w22
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbnz	w0, .L2506
	mov	w0, 0
	str	wzr, [x19, 52]
.L2403:
	str	w0, [x19, 56]
	ldr	x1, .LC711
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 60]
	bhi	.L2507
	ldr	x1, .LC715
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 64]
	bhi	.L2508
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 11]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 14]
	ldrb	w1, [x19, 13]
	cbnz	w1, .L2509
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L2440:
	ldr	w3, [x19, 68]
	cmp	w3, wzr
	ble	.L2445
.L2439:
	ldr	w4, [x21, 140]
	add	x0, x19, 172
	mov	w1, 0
	.p2align 2
.L2444:
	ldrsh	w2, [x0]
	add	w1, w1, 1
	add	x0, x0, 2
	mul	w2, w2, w4
	cmp	w2, 64
	bhi	.L2443
	ldr	w5, [x21, 64]
	cmp	w5, 64
	bhi	.L2510
.L2443:
	cmp	w1, w3
	blt	.L2444
.L2445:
	ldr	w1, [x19, 72]
	cmp	w1, wzr
	ble	.L2442
	ldrsh	w2, [x19, 212]
	ldr	w3, [x21, 140]
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L2446
	sub	w1, w1, #1
	mov	x0, x19
	add	x1, x19, x1, lsl 1
	b	.L2448
	.p2align 3
.L2449:
	ldrsh	w2, [x0, 214]
	add	x0, x0, 2
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L2446
.L2448:
	cmp	x1, x0
	bne	.L2449
.L2442:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 18]
	cbnz	w0, .L2511
.L2451:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 21]
	cbz	w0, .L2454
	add	x1, x19, 256
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbnz	w0, .L2512
.L2454:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 22]
	ldr	x1, .LC758
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 2
	cmp	w2, 1
	str	w2, [x19, 84]
	ble	.L2455
	ldr	w0, [x21, 128]
	cmp	w2, w0
	bhi	.L2455
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 24]
	cbz	w0, .L2458
	ldr	x0, [x20, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2458
	.p2align 2
.L2513:
	ldr	x2, [x20, 2368]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcs	.L2458
	ldr	x0, [x20, 2328]
	bl	BsGet
	strb	w0, [x19, 25]
	ldr	x0, [x20, 2328]
	bl	BsResidBits
	cmp	w0, wzr
	bgt	.L2513
.L2458:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2506:
	ldr	x1, .LC707
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	cmp	w0, 3
	str	w0, [x19, 52]
	bls	.L2403
	ldr	x1, .LC709
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
	.p2align 3
.L2509:
	ldr	x1, .LC719
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 19
	str	w2, [x19, 68]
	bhi	.L2514
	ldr	x1, .LC723
	ldr	x0, [x20, 2328]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 21
	str	w2, [x19, 72]
	bhi	.L2515
	ldr	w3, [x19, 68]
	cmp	w3, 10
	bgt	.L2516
	cmp	w2, 11
	ble	.L2411
	ldr	x1, .LC730
	mov	w3, w2
	mov	w2, 11
.L2499:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC728
	ldr	x4, [x0]
	cbz	x4, .L2494
.L2496:
	ldr	w0, [x20, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2490:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2446:
	ldr	x1, .LC746
.L2498:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC728
	ldr	x4, [x0]
	cbnz	x4, .L2496
.L2494:
	mov	w0, -1
.L2521:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2510:
	ldr	x1, .LC744
	b	.L2498
	.p2align 3
.L2505:
	ldr	x1, .LC705
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2411:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 15]
	cbnz	w0, .L2517
	ldr	w0, [x19, 68]
	sub	w1, w0, #1
	cmp	w1, wzr
	ble	.L2416
	ldr	x23, .LC732
	mov	w22, 0
	b	.L2420
	.p2align 3
.L2519:
	cmp	w3, w4
	bhi	.L2418
	ldr	w0, [x19, 68]
	add	w22, w22, 1
	sub	w1, w0, #1
	cmp	w1, w22
	ble	.L2518
.L2420:
	ldr	x0, [x20, 2328]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 88]
	ldr	w4, [x21, 188]
	tbz	w3, #31, .L2519
.L2418:
	ldr	x1, .LC734
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2516:
	ldr	x1, .LC727
	mov	w2, 10
	b	.L2499
.L2511:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	ldr	x0, [x20, 2328]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 20]
	cbnz	w0, .L2451
	ldr	x1, .LC748
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 76]
	bhi	.L2520
.L2453:
	ldr	x1, .LC752
	ldr	x0, [x20, 2328]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 80]
	bls	.L2451
	ldr	x1, .LC754
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 80]
	b	.L2451
.L2517:
	ldr	w0, [x19, 68]
.L2422:
	cmp	w0, wzr
	add	x5, x19, 172
	mov	w3, 0
	ble	.L2415
	.p2align 2
.L2474:
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
	bne	.L2474
.L2415:
	ldr	w4, [x19, 72]
	add	x6, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L2430
	.p2align 2
.L2473:
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
	bne	.L2473
.L2430:
	cmp	w0, 1
	bne	.L2438
	ldr	w3, [x19, 72]
	cmp	w3, 1
	beq	.L2439
.L2438:
	ldr	x0, [x20, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L2440
.L2394:
	ldr	x1, .LC691
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2502:
	ldr	x1, .LC693
	mov	w2, w0
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2503:
	ldr	x1, .LC697
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2504:
	ldr	x1, .LC701
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2507:
	ldr	x1, .LC713
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2508:
	ldr	x1, .LC717
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2455:
	ldr	x1, .LC760
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2521
.L2518:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	ble	.L2428
.L2421:
	ldr	x23, .LC736
	mov	w22, 0
	b	.L2427
	.p2align 3
.L2523:
	cmp	w3, w4
	bhi	.L2425
	ldr	w0, [x19, 72]
	add	w22, w22, 1
	sub	w0, w0, #1
	cmp	w0, w22
	ble	.L2522
.L2427:
	ldr	x0, [x20, 2328]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 128]
	ldr	w4, [x21, 192]
	tbz	w3, #31, .L2523
.L2425:
	ldr	x1, .LC738
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2514:
	ldr	x1, .LC721
	mov	w3, 20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2520:
	ldr	x1, .LC750
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 76]
	b	.L2453
.L2522:
	ldr	w0, [x19, 68]
.L2428:
	ldrb	w1, [x19, 15]
	cbnz	w1, .L2422
	add	x5, x19, x0, sxtw 1
	sub	w2, w0, #1
	ldrsh	w3, [x21, 188]
	cmp	w2, wzr
	strh	w3, [x5, 170]
	ble	.L2433
	sub	w6, w0, #2
	add	x4, x19, 88
	add	x6, x6, 45
	add	x6, x19, x6, lsl 1
	.p2align 2
.L2434:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 170]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 170]
	bne	.L2434
.L2433:
	cmp	w3, wzr
	ble	.L2524
	ldr	w1, [x19, 72]
	ldrsh	w3, [x21, 192]
	sub	w2, w1, #1
	add	x5, x19, x1, sxtw 1
	cmp	w2, wzr
	strh	w3, [x5, 210]
	ble	.L2436
	sub	w6, w1, #2
	add	x4, x19, 128
	add	x6, x6, 65
	add	x6, x19, x6, lsl 1
	.p2align 2
.L2437:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x6, x4
	ldrh	w1, [x5, 210]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 210]
	bne	.L2437
.L2436:
	cmp	w3, wzr
	bgt	.L2430
	ldr	x1, .LC742
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
	.p2align 3
.L2515:
	ldr	x1, .LC725
	mov	w3, 22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2512:
	ldr	x1, .LC756
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
.L2416:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	bgt	.L2421
	add	x1, x19, x0, sxtw 1
	ldrsh	w3, [x21, 188]
	sub	w2, w0, #1
	strh	w3, [x1, 170]
	b	.L2433
.L2524:
	ldr	x1, .LC740
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2490
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
	ldr	x0, [x19, 2328]
	bl	HEVC_ue_v
	mov	w21, w0
	ldr	w3, [x19, 164]
	cmp	w0, w3
	bcs	.L2531
	mov	w20, 1888
	umull	x20, w0, w20
	ldr	x0, [x19, 2352]
	add	x1, x0, x20
	ldrb	w0, [x0, x20]
	cbnz	w0, .L2532
	str	w21, [x1, 28]
	mov	x0, x19
	ldr	x1, [x19, 2352]
	add	x1, x1, x20
	bl	HEVC_ProcessPPS
	mov	w22, w0
	cbnz	w0, .L2533
	ldr	x0, [x19, 2352]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2352]
	strb	w1, [x0, x20]
.L2527:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2532:
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
	cbnz	w0, .L2534
	ldr	x0, [x19, 2352]
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
.L2534:
	ldr	x1, .LC768
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2527
	.p2align 3
.L2531:
	ldr	x1, .LC764
	mov	w2, w0
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2527
.L2533:
	ldr	x1, .LC768
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2352]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2352]
	strb	wzr, [x0, x20]
	b	.L2527
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
	ldr	w1, [x28, 4676]
	mov	w4, 1888
	ldr	w0, [x28, 4692]
	ldr	x2, [x28, 2352]
	cmp	w1, 1
	smaddl	x2, w0, w4, x2
	beq	.L2609
	cbnz	w1, .L2539
	ldrb	w0, [x2, 11]
	cbz	w0, .L2539
.L2537:
	ldr	x1, .LC771
	ldr	x0, [x28, 2328]
	ldr	w19, [x2, 32]
	add	x2, x28, 4096
	mov	x21, x2
	ldr	x20, [x28, 2344]
	str	x2, [x29, 104]
	bl	HEVC_ue_v
	cmp	w0, 7
	str	w0, [x28, 4812]
	add	x22, x21, 716
	bhi	.L2610
	mov	w1, 12660
	smaddl	x19, w19, w1, x20
	ldr	w1, [x19, 60]
	cbnz	w1, .L2611
	str	w0, [x22, 132]
.L2581:
	ldr	w0, [x28, 4732]
	mov	w20, 0
	cbz	w0, .L2551
	.p2align 2
.L2594:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4732]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L2594
	ldr	w0, [x19, 60]
	cbz	w0, .L2547
	mov	w20, 0
	cbz	w1, .L2551
	.p2align 2
.L2593:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4732]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L2593
.L2547:
	mov	w27, 0
	cbz	w1, .L2551
	ldr	x0, [x29, 104]
	ldr	x26, .LC789
	add	x21, x0, 716
	b	.L2592
	.p2align 3
.L2553:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 4816]
	str	w0, [x20, 4948]
.L2555:
	ldr	w0, [x19, 60]
	cbz	w0, .L2557
	add	x0, x29, 240
	add	x0, x0, x22, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L2558
	lsl	x22, x22, 3
	ldr	w2, [x21, 132]
	add	x1, x28, x22
	add	x22, x21, x22
	mov	w0, 1
	lsl	w0, w0, w2
	str	wzr, [x1, 5140]
	str	w0, [x1, 5012]
	str	w0, [x22, 204]
	str	wzr, [x22, 332]
.L2557:
	ldr	w0, [x28, 4732]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L2551
.L2592:
	uxtw	x22, w27
	add	x0, x29, 240
	lsl	x20, x22, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L2553
	ldr	x1, .LC781
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L2612
	ldr	w2, [x21]
	add	x20, x28, x20
	mov	w23, 1
	ldr	x1, .LC785
	lsl	w2, w23, w2
	add	w0, w2, w0
	str	w0, [x20, 4948]
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	str	w0, [x20, 4816]
	bls	.L2555
	ldr	x1, .LC787
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
	.p2align 3
.L2609:
	ldrb	w0, [x2, 10]
	cbnz	w0, .L2537
.L2539:
	mov	w0, 0
.L2607:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L2558:
	ldr	x0, [x28, 2328]
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
	bhi	.L2613
.L2559:
	ldr	w6, [x21, 132]
	lsl	w6, w22, w6
	add	w0, w6, w0
	str	w0, [x25, 5012]
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w6, -128
	bhi	.L2614
	ldr	w1, [x25, 5012]
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
	str	w0, [x25, 5136]
	beq	.L2557
	ldr	x0, [x28, 2328]
	mov	x1, x26
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	ldr	x1, .LC793
	bls	.L2559
.L2613:
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
.L2551:
	ldr	w0, [x28, 4676]
	cbnz	w0, .L2539
	ldr	w0, [x28, 4736]
	cbz	w0, .L2539
	mov	w20, 0
	.p2align 2
.L2565:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4736]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L2565
	ldr	w0, [x19, 60]
	cbnz	w0, .L2615
.L2566:
	mov	w25, 0
	cbz	w1, .L2539
	ldr	x0, [x29, 104]
	ldr	x23, .LC805
	add	x21, x0, 716
	b	.L2590
	.p2align 3
.L2570:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 4880]
	str	w0, [x20, 5268]
.L2572:
	ldr	w0, [x19, 60]
	cbz	w0, .L2574
	add	x0, x29, 240
	add	x0, x0, x26, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L2575
	lsl	x26, x26, 3
	ldr	w4, [x21, 132]
	add	x1, x28, x26
	add	x26, x21, x26
	mov	w0, 1
	lsl	w0, w0, w4
	str	wzr, [x1, 5460]
	str	w0, [x1, 5332]
	str	w0, [x26, 524]
	str	wzr, [x26, 652]
.L2574:
	ldr	w0, [x28, 4736]
	add	w25, w25, 1
	cmp	w0, w25
	bls	.L2539
.L2590:
	uxtw	x26, w25
	add	x0, x29, 240
	lsl	x20, x26, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L2570
	ldr	x1, .LC797
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L2616
	ldr	w1, [x21]
	add	x20, x28, x20
	mov	w27, 1
	lsl	w1, w27, w1
	add	w0, w1, w0
	str	w0, [x20, 5268]
	ldr	x1, .LC801
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	str	w0, [x20, 4880]
	add	w0, w0, 128
	cmp	w0, 255
	bls	.L2572
	ldr	x1, .LC803
	mov	w0, w27
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
	.p2align 3
.L2575:
	add	x22, x28, x26, lsl 3
	add	x26, x26, 1
	mov	w20, 1
	mov	w24, 128
	add	x26, x28, x26, lsl 3
	mov	w27, 127
.L2578:
	ldr	x0, [x28, 2328]
	mov	x1, x23
	bl	HEVC_se_v
	add	w5, w0, 128
	cmp	w5, 255
	ldr	x1, .LC809
	bhi	.L2617
	ldr	w5, [x21, 132]
	lsl	w5, w20, w5
	add	w0, w5, w0
	str	w0, [x22, 5332]
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w5, -128
	bhi	.L2618
	ldr	w1, [x22, 5332]
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
	str	w0, [x22, 5456]
	cmp	x22, x26
	bne	.L2578
	b	.L2574
	.p2align 3
.L2611:
	ldr	x1, .LC775
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 14
	bhi	.L2619
	ldr	w1, [x28, 4812]
	add	w0, w0, w1
	str	w0, [x22, 132]
	cmp	w0, 7
	bls	.L2581
	ldr	x1, .LC779
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
	.p2align 3
.L2614:
	ldr	x1, .LC795
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2615:
	mov	w20, 0
	cbz	w1, .L2539
	.p2align 2
.L2591:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 4736]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L2591
	b	.L2566
.L2612:
	ldr	x1, .LC783
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2617:
	ldr	x1, .LC807
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2618:
	ldr	x1, .LC811
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2616:
	ldr	x1, .LC799
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2610:
	ldr	x1, .LC773
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
.L2619:
	ldr	x1, .LC777
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2607
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
	ldr	x2, [x28, 2368]
	mov	w1, 1
	ldr	x0, [x28, 2328]
	ldr	w20, [x2, 24]
	bl	BsGet
	strb	w0, [x24, 560]
	ldr	w22, [x28, 4684]
	sub	w0, w22, #16
	str	w0, [x29, 120]
	cmp	w0, 5
	bls	.L2876
.L2621:
	ldr	x1, .LC813
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	str	w0, [x28, 4692]
	ldr	w4, [x28, 164]
	tbnz	w0, #31, .L2623
	cmp	w0, w4
	bge	.L2623
	mov	x0, x28
	bl	HEVC_VpsSpsPpsCheck
	cbnz	w0, .L2877
	ldr	x0, [x28, 2352]
	mov	w3, 1888
	ldr	w21, [x28, 4692]
	mov	w2, 12660
	ldr	x1, [x28, 2344]
	smaddl	x21, w21, w3, x0
	ldr	w19, [x21, 32]
	ldrb	w0, [x21, 2]
	smaddl	x19, w19, w2, x1
	cbnz	w0, .L2878
.L2629:
	strb	wzr, [x24, 561]
.L2630:
	ldp	w2, w3, [x19, 140]
	cbz	w2, .L2632
	cbz	w3, .L2632
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
	ble	.L2634
	.p2align 2
.L2635:
	add	w1, w1, 1
	lsl	w0, w3, w1
	cmp	w2, w0
	bgt	.L2635
.L2634:
	ldrb	w0, [x24, 560]
	str	wzr, [x29, 124]
	cbz	w0, .L2879
.L2636:
	ldr	w0, [x28, 192]
	str	w0, [x28, 4668]
	ldrb	w0, [x24, 561]
	cbz	w0, .L2880
.L2639:
	ldr	w0, [x21, 12]
	tst	w0, 16776960
	bne	.L2729
.L2736:
	ldrb	w0, [x21, 23]
	cbnz	w0, .L2881
.L2731:
	ldr	w0, [x29, 124]
	cbnz	w0, .L2882
	ldrb	w0, [x28, 3]
	cbz	w0, .L2745
	ldr	w0, [x29, 120]
	cmp	w0, 5
	bhi	.L2746
	ldr	w0, [x28, 4688]
	mov	w2, 1
	add	x1, x28, x0
	strb	w2, [x1, 5]
.L2747:
	ldr	w1, [x28, 4668]
	cmp	w1, wzr
	ldr	w1, [x29, 120]
	ccmp	w1, 5, 2, ne
	bhi	.L2748
	ldr	w1, [x28, 4684]
	add	x0, x28, x0
	cmp	w1, 21
	beq	.L2883
	.p2align 2
.L2867:
	strb	wzr, [x0, 4]
.L2750:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 4808]
	mov	x0, x28
	bl	HEVC_ReadByteAlignment
	cmp	w0, wzr
	csetm	w0, ne
.L2860:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2878:
	ldrb	w0, [x24, 560]
	cbnz	w0, .L2629
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 561]
	b	.L2630
	.p2align 3
.L2880:
	ldr	w0, [x21, 36]
	mov	w23, 0
	cbz	w0, .L2644
	.p2align 2
.L2825:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	add	w23, w23, w1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w23
	bhi	.L2825
.L2644:
	ldr	x1, .LC824
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	cmp	w0, 2
	str	w0, [x28, 4676]
	bhi	.L2884
	ldrb	w0, [x21, 4]
	cbnz	w0, .L2885
	sub	w22, w22, #19
	cmp	w22, 1
	bls	.L2646
.L2915:
	ldrb	w0, [x28, 1]
	cbz	w0, .L2886
	ldr	w1, [x19, 116]
	mov	w2, 1
	ldr	w0, [x28, 188]
	lsl	w1, w2, w1
	mov	w2, w1
	str	w2, [x29, 112]
	udiv	w1, w0, w1
	msub	w1, w1, w2, w0
	sub	w0, w0, w1
	cbnz	w1, .L2751
	str	wzr, [x29, 116]
.L2649:
	ldr	w1, [x28, 4684]
	add	x20, x28, x20, uxtw 2
	sub	w1, w1, #16
	cmp	w1, 2
	ldr	w1, [x29, 116]
	csel	w0, w0, wzr, hi
	add	w3, w0, w1
	str	w3, [x28, 4668]
	ldr	w2, [x20, 212]
	cmp	w3, w2
	bge	.L2651
	ldrb	w0, [x24, 560]
	cmp	w0, 1
	beq	.L2887
.L2651:
	ldr	w0, [x28, 4680]
	str	w3, [x28, 192]
	cbnz	w0, .L2652
	ldr	w0, [x28, 4684]
	cmp	w0, 15
	bhi	.L2653
	mov	w1, 1
	tbz	x0, 0, .L2653
.L2654:
	sub	w0, w0, #7
	tst	w0, -3
	cset	w0, ne
	tst	w1, w0
	beq	.L2652
	str	w3, [x28, 188]
	.p2align 2
.L2652:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2655
	ldr	w3, [x19, 176]
	mov	w1, 0
	mov	w2, 1
	mov	w0, 0
	cmp	w3, 1
	bls	.L2657
	.p2align 2
.L2824:
	add	w1, w1, 1
	lsl	w0, w2, w1
	cmp	w0, w3
	bcc	.L2824
	mov	w0, 0
	cbnz	w1, .L2888
.L2660:
	sxtw	x4, w0
	mov	x2, 164
	lsl	x1, x4, 2
	add	x0, x24, 1492
	sub	x1, x1, x4
	lsl	x3, x1, 3
	sub	x1, x3, x1
	lsl	x1, x1, 1
	sub	x1, x1, x4
	add	x1, x19, x1, lsl 2
	add	x1, x1, 2164
	bl	memcpy
	str	x0, [x29, 104]
.L2658:
	ldrb	w0, [x19, 8]
	cbz	w0, .L2662
	ldr	w0, [x19, 180]
	ldr	w1, [x24, 1496]
	ldr	w20, [x28, 5588]
	add	w20, w20, w1
	cbnz	w0, .L2889
	mov	w25, 0
	str	wzr, [x29, 140]
.L2663:
	ldr	x1, .LC838
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	ldr	w3, [x24, 1496]
	add	x1, x24, 1492
	ldr	w2, [x28, 5588]
	add	w0, w0, w25
	mov	w4, w0
	add	w0, w2, w3
	add	w0, w0, w4
	str	w4, [x29, 136]
	cmp	w0, 16
	bhi	.L2890
	ldr	w2, [x29, 136]
	mov	w23, 0
	mov	w27, 0
	add	w0, w20, w2
	str	w0, [x29, 100]
	sub	w22, w0, #1
	cbz	w2, .L2679
	str	x1, [x29, 128]
	b	.L2823
	.p2align 3
.L2893:
	ldr	w1, [x29, 140]
	cbnz	w1, .L2891
.L2670:
	sxtw	x0, w0
	ldr	x1, [x29, 128]
	add	x4, x19, x0
	add	x1, x1, x26
	add	x0, x19, x0, lsl 2
	ldrb	w4, [x4, 13]
	ldr	w20, [x0, 196]
	strb	w4, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2328]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbnz	w0, .L2892
.L2674:
	str	w20, [x1, 5688]
	csel	w23, w23, wzr, ne
	str	wzr, [x1, 4744]
	ldr	w0, [x28, 4668]
	sub	w20, w20, w0
	str	w20, [x1, 5620]
.L2676:
	ldr	w0, [x29, 136]
	add	w27, w27, 1
	sub	w22, w22, #1
	cmp	w0, w27
	beq	.L2679
.L2823:
	cmp	w27, w25
	uxtw	x26, w22
	mov	w0, 0
	bcc	.L2893
	ldr	w1, [x19, 120]
	uxtw	x26, w22
	ldr	x0, [x28, 2328]
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 128]
	add	x1, x1, x26
	strb	w0, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2328]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbz	w0, .L2674
.L2892:
	ldr	x1, .LC844
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	add	w23, w23, w0
	add	x3, x28, x26, lsl 2
	cmp	w27, wzr
	ccmp	w27, w25, 4, ne
	mov	w1, 1
	str	w1, [x3, 4744]
	cset	w1, eq
	cmp	w1, wzr
	csel	w23, w23, w0, eq
	ldr	w0, [x29, 112]
	ldr	w1, [x28, 4668]
	msub	w20, w23, w0, w20
	ldr	w0, [x29, 116]
	sub	w0, w1, w0
	add	w20, w20, w0
	str	w20, [x3, 5688]
	sub	w20, w20, w1
	str	w20, [x3, 5620]
	b	.L2676
	.p2align 3
.L2882:
	ldr	w0, [x28, 4688]
	add	x1, x28, x0
	ldrb	w1, [x1, 5]
	cbnz	w1, .L2747
.L2748:
	add	x0, x28, x0
	b	.L2867
	.p2align 3
.L2876:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	b	.L2621
	.p2align 3
.L2879:
	ldr	x0, [x28, 2328]
	bl	BsGet
	str	w0, [x28, 4696]
	ldp	w1, w3, [x19, 188]
	mul	w3, w1, w3
	tbnz	w0, #31, .L2638
	cmp	w3, w0
	bls	.L2638
	mul	w0, w23, w0
	str	w0, [x29, 124]
	b	.L2636
	.p2align 3
.L2729:
	ldr	x1, .LC896
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	mov	w20, w0
	ldr	w0, [x21, 12]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L2894
	cmp	w0, 256
	ldr	w0, [x21, 68]
	beq	.L2895
	ldr	w1, [x19, 192]
	mul	w0, w0, w1
	sub	w0, w0, #1
.L2733:
	cmp	w0, 255
	mov	w1, 255
	csel	w3, w0, w1, ls
	cmp	w20, w3
	bhi	.L2896
	cbz	w20, .L2736
	ldr	x1, .LC900
	mov	w19, 0
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	cmp	w0, 31
	add	w22, w0, 1
	bhi	.L2897
	.p2align 2
.L2822:
	ldr	x0, [x28, 2328]
	mov	w1, w22
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L2822
	ldrb	w0, [x21, 23]
	cbz	w0, .L2731
.L2881:
	ldr	x1, .LC904
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	cmp	w0, 256
	mov	w20, w0
	bhi	.L2898
	ldr	x0, [x28, 2328]
	bl	BsResidBits
	cmp	w20, w0
	bhi	.L2742
	mov	w19, 0
	cbz	w20, .L2731
	.p2align 2
.L2821:
	ldr	x0, [x28, 2328]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L2821
	b	.L2731
	.p2align 3
.L2745:
	ldr	w0, [x29, 120]
	cmp	w0, 5
	bhi	.L2746
	ldr	w0, [x28, 4688]
	add	x1, x28, x0
	add	x0, x28, x0
	strb	wzr, [x1, 5]
	b	.L2867
	.p2align 3
.L2751:
	ldr	w2, [x29, 112]
	str	wzr, [x29, 116]
	cmp	w1, w2, lsr 1
	bcc	.L2649
.L2759:
	ldr	w1, [x29, 112]
	add	w0, w0, w1
	b	.L2649
.L2894:
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	b	.L2733
	.p2align 3
.L2653:
	sub	w1, w0, #16
	cmp	w1, 7
	cset	w1, ls
	b	.L2654
	.p2align 3
.L2891:
	ldr	x0, [x28, 2328]
	bl	BsGet
	ldr	w4, [x19, 180]
	sub	w4, w4, #1
	tbnz	w0, #31, .L2672
	cmp	w4, w0
	bcs	.L2670
.L2672:
	ldr	x1, .LC842
	mov	w3, w0
	mov	w2, w27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
	.p2align 3
.L2679:
	ldr	w0, [x29, 100]
	str	w0, [x24, 1500]
	cmp	w0, 16
	bhi	.L2899
.L2662:
	ldrb	w0, [x19, 9]
	cbnz	w0, .L2900
	strb	wzr, [x24, 564]
.L2681:
	ldrb	w0, [x19, 6]
	cbz	w0, .L2753
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 562]
	mov	w1, 1
	ldr	x0, [x28, 2328]
	bl	BsGet
	strb	w0, [x24, 563]
.L2753:
	ldr	w0, [x28, 4676]
	cmp	w0, 2
	bne	.L2901
.L2683:
	ldrb	w0, [x24, 564]
	cbnz	w0, .L2902
.L2705:
	mov	w4, 2
.L2712:
	ldrb	w0, [x21, 11]
	cbz	w0, .L2703
	cbnz	w4, .L2703
.L2715:
	mov	x0, x28
	bl	HEVC_DecPredWeightTable
	cbnz	w0, .L2903
	ldr	w4, [x28, 4676]
.L2703:
	cmp	w4, 2
	beq	.L2716
	ldr	x1, .LC868
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	mov	w3, 4
	mov	w1, 5
	sub	w3, w3, w0
	sub	w2, w1, w0
	cmp	w3, 4
	str	w2, [x28, 4704]
	bhi	.L2904
.L2716:
	ldr	x1, .LC872
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	ldr	w2, [x21, 48]
	mov	w1, 51
	add	w0, w0, w2
	str	w0, [x28, 4672]
	ldr	w3, [x19, 92]
	neg	w2, w3
	cmp	w0, w2
	ccmp	w0, w1, 0, ge
	bgt	.L2905
	ldrb	w0, [x21, 9]
	cbnz	w0, .L2906
.L2718:
	ldrb	w0, [x21, 18]
	cbz	w0, .L2866
	ldrb	w0, [x21, 19]
	cbnz	w0, .L2907
.L2724:
	ldrb	w0, [x21, 20]
	strb	w0, [x24, 569]
	ldr	w1, [x21, 76]
	str	w1, [x28, 4716]
	ldr	w1, [x21, 80]
	str	w1, [x28, 4720]
.L2723:
	ldrb	w2, [x19, 6]
	mov	w1, 0
	cbz	w2, .L2727
	ldrh	w1, [x28, 4658]
	cmp	w1, wzr
	cset	w1, ne
.L2727:
	ldrb	w2, [x21, 17]
	cbz	w2, .L2728
	cmp	w0, wzr
	cset	w0, eq
	orr	w1, w0, w1
	cbnz	w1, .L2908
.L2728:
	strb	w2, [x24, 570]
	b	.L2639
	.p2align 3
.L2901:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 565]
	cbnz	w0, .L2909
	ldr	w0, [x21, 40]
	ldr	w4, [x28, 4676]
	str	w0, [x28, 4732]
	cbnz	w4, .L2691
	ldr	w0, [x21, 44]
	mov	w20, 0
	mov	w22, 0
	str	w0, [x28, 4736]
.L2689:
	ldr	x0, [x29, 104]
	cbz	x0, .L2910
	ldr	x0, [x29, 104]
	ldr	w2, [x0, 8]
	cmp	w2, 16
	bhi	.L2693
	cbz	w2, .L2695
	ldr	x0, [x29, 104]
	sub	w2, w2, #1
	add	x2, x2, 13
	mov	w3, 0
	add	x2, x0, x2
	add	x0, x0, 12
	.p2align 2
.L2697:
	ldrb	w1, [x0], 1
	cmp	w1, wzr
	csinc	w3, w3, w3, eq
	cmp	x2, x0
	bne	.L2697
	ldrb	w0, [x21, 22]
	cmp	w0, wzr
	ccmp	w3, 1, 4, ne
	ble	.L2695
	add	x2, x24, 1656
	add	x1, x24, 560
	mov	x0, x28
	bl	HEVC_DecRefPicListsModification
	cbnz	w0, .L2862
	ldr	w4, [x28, 4676]
	cbnz	w4, .L2698
.L2756:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 566]
	ldr	w4, [x28, 4676]
.L2698:
	cmp	w4, 2
	beq	.L2683
.L2757:
	ldrb	w0, [x21, 5]
	cbnz	w0, .L2911
.L2699:
	ldrb	w0, [x24, 564]
	cbz	w0, .L2708
	cbz	w4, .L2912
	mov	w0, 1
	cmp	w4, 2
	strb	w0, [x24, 568]
	beq	.L2705
.L2704:
	ldr	w0, [x28, 4732]
	cmp	w0, 1
	bls	.L2865
.L2707:
	ldr	x1, .LC862
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	str	w0, [x28, 4700]
	ldrb	w2, [x24, 568]
	cbnz	w2, .L2913
	sub	w4, w20, #1
.L2710:
	cmp	w4, w0
	ccmp	w0, wzr, 1, cs
	bge	.L2865
	ldr	x1, .LC864
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
	.p2align 3
.L2865:
	ldr	w4, [x28, 4676]
.L2708:
	ldrb	w0, [x21, 10]
	cbz	w0, .L2712
	cmp	w4, 1
	bne	.L2712
	b	.L2715
	.p2align 3
.L2746:
	ldr	w0, [x28, 4688]
	add	x0, x28, x0
	b	.L2867
.L2907:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2724
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 569]
	cbnz	w0, .L2723
	ldr	x1, .LC888
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 4716]
	bhi	.L2914
.L2725:
	ldr	x1, .LC892
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 4720]
	bls	.L2866
	ldr	x1, .LC894
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 80]
	str	w0, [x28, 4720]
	.p2align 2
.L2866:
	ldrb	w0, [x24, 569]
	b	.L2723
	.p2align 3
.L2695:
	cbnz	w4, .L2757
	b	.L2756
	.p2align 3
.L2885:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	sub	w22, w22, #19
	bl	BsGet
	cmp	w22, 1
	bhi	.L2915
.L2646:
	ldr	w0, [x28, 4680]
	str	wzr, [x28, 192]
	str	wzr, [x28, 4668]
	cbnz	w0, .L2682
	str	wzr, [x28, 188]
.L2682:
	ldrb	w0, [x19, 6]
	cbnz	w0, .L2916
.L2755:
	strb	wzr, [x24, 564]
	str	xzr, [x29, 104]
	b	.L2753
	.p2align 3
.L2623:
	ldr	x2, .LC814
	mov	w3, w0
	ldr	x1, .LC816
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
	.p2align 3
.L2906:
	ldr	x1, .LC876
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 4708]
	bhi	.L2917
	ldr	w3, [x21, 60]
	add	w1, w0, w3
	add	w1, w1, 12
	cmp	w1, 24
	bhi	.L2918
	ldr	x1, .LC882
	ldr	x0, [x28, 2328]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 4712]
	bhi	.L2919
	ldr	w1, [x21, 64]
	add	w2, w0, w1
	add	w0, w2, 12
	cmp	w0, 24
	bls	.L2718
	ldr	x1, .LC886
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
	.p2align 3
.L2886:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2328]
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
	bcc	.L2920
.L2648:
	ldr	w2, [x29, 116]
	cmp	w2, w1
	bls	.L2649
	sub	w1, w2, w1
	ldr	w2, [x29, 112]
	cmp	w1, w2, lsr 1
	sub	w1, w0, w2
	csel	w0, w1, w0, hi
	b	.L2649
	.p2align 3
.L2655:
	ldr	w3, [x19, 176]
	add	x2, x24, 1492
	mov	x1, x19
	mov	x0, x28
	str	x2, [x29, 104]
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L2658
	ldr	x1, .LC830
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
	.p2align 3
.L2888:
	ldr	x0, [x28, 2328]
	bl	BsGet
	ldr	w3, [x19, 176]
	tbnz	w0, #31, .L2921
.L2657:
	sub	w3, w3, #1
	cmp	w3, w0
	bcs	.L2660
.L2661:
	ldr	x1, .LC832
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2911:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 567]
	ldr	w4, [x28, 4676]
	b	.L2699
.L2900:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 564]
	b	.L2681
.L2691:
	mov	w22, 0
	str	wzr, [x28, 4736]
.L2690:
	cmp	w4, 2
	beq	.L2683
	mov	w20, 0
	b	.L2689
.L2909:
	ldr	x1, .LC848
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	add	w22, w0, 1
	cmp	w22, 16
	bhi	.L2922
	ldr	w4, [x28, 4676]
	str	w22, [x28, 4732]
	cbz	w4, .L2923
	str	wzr, [x28, 4736]
	b	.L2690
.L2902:
	mov	w0, 1
	mov	w4, 2
	strb	w0, [x24, 568]
	b	.L2708
.L2908:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 570]
	b	.L2639
.L2920:
	sub	w2, w1, w4
	cmp	w2, w3, lsr 1
	bcc	.L2648
	b	.L2759
	.p2align 3
.L2913:
	sub	w4, w22, #1
	b	.L2710
.L2883:
	mov	w1, 1
	strb	w1, [x0, 4]
	b	.L2750
.L2923:
	ldr	x1, .LC852
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	add	w20, w0, 1
	cmp	w20, 16
	bhi	.L2924
	ldr	w4, [x28, 4676]
	str	w20, [x28, 4736]
	cmp	w4, 2
	bne	.L2689
	b	.L2683
	.p2align 3
.L2898:
	ldr	x1, .LC906
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2899:
	ldr	x1, .LC846
	mov	w3, 16
	ldr	w2, [x29, 100]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2921:
	sub	w3, w3, #1
	b	.L2661
	.p2align 3
.L2912:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 568]
	ldr	w4, [x28, 4676]
	cmp	w4, 2
	beq	.L2716
	cbnz	w0, .L2704
	ldr	w0, [x28, 4736]
	cmp	w0, 1
	bhi	.L2707
	b	.L2708
.L2632:
	ldr	x1, .LC820
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2895:
	ldr	w1, [x21, 72]
	mul	w0, w0, w1
	sub	w0, w0, #1
	b	.L2733
.L2889:
	ldr	x1, .LC834
	ldr	x0, [x28, 2328]
	bl	HEVC_ue_v
	mov	w25, w0
	ldr	w3, [x19, 180]
	cmp	w0, w3
	bhi	.L2925
	cmp	w3, 1
	str	wzr, [x29, 140]
	bls	.L2663
	mov	w1, 1
	.p2align 2
.L2665:
	ldr	w0, [x29, 140]
	add	w0, w0, 1
	str	w0, [x29, 140]
	lsl	w0, w1, w0
	cmp	w3, w0
	bhi	.L2665
	b	.L2663
.L2877:
	ldr	w0, [x28, 236]
	cbz	w0, .L2627
	ldr	w0, [x28, 192]
	str	w0, [x28, 4668]
.L2628:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 4808]
	ldr	x1, .LC818
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2887:
	ldr	x1, .LC828
	bl	dprint_vfmw
	ldr	w3, [x28, 4668]
	b	.L2651
.L2905:
	ldr	x1, .LC874
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2627:
	str	wzr, [x28, 4668]
	b	.L2628
.L2916:
	ldr	x0, [x28, 2328]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 562]
	mov	w1, 1
	ldr	x0, [x28, 2328]
	bl	BsGet
	strb	w0, [x24, 563]
	b	.L2755
.L2638:
	ldr	x1, .LC822
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2884:
	ldr	x1, .LC826
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2693:
	ldr	x1, .LC858
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2896:
	ldr	x1, .LC898
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2914:
	ldr	x1, .LC890
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 76]
	str	w0, [x28, 4716]
	b	.L2725
.L2742:
	ldr	x1, .LC908
	mov	w2, w0
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2918:
	ldr	x1, .LC880
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2904:
	ldr	x1, .LC870
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2890:
	ldr	x1, .LC840
	mov	w5, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2917:
	ldr	x1, .LC878
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2919:
	ldr	x1, .LC884
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2903:
	ldr	x1, .LC866
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2925:
	ldr	x1, .LC836
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2862:
	ldr	x1, .LC860
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2897:
	ldr	x1, .LC902
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2922:
	ldr	x1, .LC850
	mov	w3, 16
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2910:
	ldr	x1, .LC856
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
.L2924:
	ldr	x1, .LC854
	mov	w3, 16
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2860
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
	ldr	x1, [x19, 2368]
	cbz	x1, .L2928
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L2928:
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
	cbz	w2, .L2937
	.p2align 2
.L2940:
	ldr	x0, [x20, 2408]
	ldr	x0, [x0, w19, uxtw 3]
	mov	x1, x0
	cbz	x0, .L2935
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2408]
	str	xzr, [x0, w19, uxtw 3]
	ldr	w2, [x20, 168]
.L2935:
	add	w19, w19, 1
	cmp	w2, w19
	bhi	.L2940
.L2937:
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
	add	x19, x20, 2784
	bl	_mcount
	add	x21, x20, 2920
	mov	x0, x20
	bl	HEVC_ClearAllSlice
	.p2align 2
.L2949:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L2945
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2945:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L2946
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2946:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L2947
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2947:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L2948
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 252]
	bl	FSP_ClearLogicFs
.L2948:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L2949
	ldr	x0, [x20, 2392]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 2760]
	cmp	w0, 17
	bhi	.L2988
.L2950:
	ldr	x1, .LC911
	add	x4, x20, 2560
	add	x0, x20, 12288
	mov	x2, 200
	add	x0, x0, 952
	ldr	x3, [x1, 96]
	mov	w1, 0
	stp	wzr, wzr, [x4, 204]
	stp	wzr, wzr, [x4, 212]
	str	wzr, [x20, 2780]
	blr	x3
	str	wzr, [x20, 13244]
	mov	w0, 16
	add	x1, x20, 2448
	str	w0, [x20, 13240]
	add	x0, x20, 2584
	.p2align 2
.L2951:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L2951
	add	x1, x20, 2720
	str	wzr, [x20, 4724]
	.p2align 2
.L2952:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L2952
	str	wzr, [x20, 4728]
	cbnz	w22, .L2953
	ldr	x0, [x20, 2424]
	ldr	w0, [x0, 888]
	cmp	w0, 1
	beq	.L2953
.L2954:
	ldr	w0, [x20, 184]
	cbz	w0, .L2963
	sub	w1, w0, #1
	add	x0, x20, 2132
	add	x1, x1, 534
	add	x1, x20, x1, lsl 2
	.p2align 2
.L2962:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L2962
.L2963:
	ldr	w2, [x20, 168]
	mov	w19, 0
	cbz	w2, .L2961
	.p2align 2
.L2977:
	ldr	x0, [x20, 2408]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L2964
	ldr	x3, [x20, 2368]
	cmp	x0, x3
	beq	.L2964
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 2408]
	str	xzr, [x0, x21, lsl 3]
	ldr	w2, [x20, 168]
.L2964:
	cmp	w2, w19
	bhi	.L2977
.L2961:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2953:
	mov	w19, 20
	mov	x0, x20
	stp	w19, w19, [x20, 180]
	bl	HEVC_ArrangeMem
	cbz	w0, .L2955
	cmp	w0, 2
	beq	.L2989
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
.L2988:
	ldr	x2, .LC909
	mov	w4, 17
	ldr	x1, .LC910
	mov	w3, w4
	add	x2, x2, 104
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 2760]
	b	.L2950
.L2955:
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	cmp	w0, 20
	mov	w0, w19
	ble	.L2990
	str	w0, [x20, 180]
	b	.L2954
.L2989:
	add	x0, x20, 4096
	add	x0, x0, 1920
	bl	ResetVoQueue
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2990:
	ldr	w0, [x20, 252]
	bl	FSP_GetTotalValidFsNum
	str	w0, [x20, 180]
	b	.L2954
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
	bne	.L2996
	b	.L2995
	.p2align 3
.L2993:
	add	w0, w2, 1
	cmp	w0, w19
	bls	.L2995
.L2996:
	umull	x1, w19, w21
	ldr	x0, [x20, 2416]
	add	w19, w19, 1
	add	x1, x0, x1
	ldr	w0, [x1, 32]
	cmp	w0, 1
	bne	.L2993
	ldr	w0, [x20, 252]
	bl	HEVC_ReleaseNAL
	ldr	w2, [x20, 168]
	add	w0, w2, 1
	cmp	w0, w19
	bhi	.L2996
.L2995:
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
	add	x19, x25, 1152
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
	add	x0, x23, 1920
	bl	ResetVoQueue
	ldr	x22, .LC916
	.p2align 2
.L3000:
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
	bne	.L3000
	add	x0, x20, 2132
	add	x1, x20, 2212
	.p2align 2
.L3001:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L3001
	ldr	w1, [x20, 168]
	mov	w0, 0
	cbz	w1, .L3005
	.p2align 2
.L3007:
	ldr	x1, [x20, 2408]
	str	xzr, [x1, w0, uxtw 3]
	add	w0, w0, 1
	ldr	w1, [x20, 168]
	cmp	w1, w0
	bhi	.L3007
.L3005:
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 200
	add	x0, x25, 952
	blr	x3
	mov	w1, 16
	add	x0, x20, 2920
	str	w1, [x20, 13240]
	add	x1, x20, 3056
.L3003:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x1, x0
	bne	.L3003
	add	x2, x20, 2560
	mov	w0, 17
	add	x19, x20, 2584
	stp	w0, wzr, [x2, 200]
	stp	wzr, wzr, [x2, 208]
	str	wzr, [x20, 2776]
	add	x0, x20, 2720
	str	wzr, [x20, 2780]
	.p2align 2
.L3006:
	str	xzr, [x19, -136]
	add	x19, x19, 8
	str	xzr, [x19, -8]
	cmp	x19, x0
	bne	.L3006
	ldr	x3, [x22, 96]
	mov	w21, 2
	mov	x2, 1356
	str	w21, [x20, 176]
	mov	w1, 0
	add	x0, x23, 560
	str	wzr, [x20, 204]
	str	wzr, [x20, 236]
	str	wzr, [x20, 244]
	str	xzr, [x20, 2368]
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
	str	w21, [x20, 4676]
	str	w3, [x20, 4808]
	mov	x0, x19
	str	w2, [x20, 332]
	mov	x2, 40
	str	w1, [x20, 336]
	mov	w1, 0
	blr	x4
	str	x19, [x20, 2328]
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
	ldr	x0, [x19, 4016]
	cbz	x0, .L3014
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x19, 252]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 4016]
	str	wzr, [x0, 48]
	str	xzr, [x19, 4016]
.L3014:
	strb	wzr, [x19, 3953]
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
	cbnz	w20, .L3021
	add	x0, x19, 4096
	add	x0, x0, 1920
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
.L3021:
	add	x1, x19, 4096
	ldr	w0, [x19, 252]
	add	x1, x1, 1920
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
	ldr	w3, [x19, 4692]
	tbnz	w3, #31, .L3038
	ldr	w1, [x19, 164]
	mov	w0, 0
	cmp	w3, w1
	bge	.L3049
	add	x1, x19, 256
	mov	w26, 1888
	mov	w0, 12660
	ldr	w2, [x19, 4688]
	ldr	x5, [x19, 2344]
	mov	w21, 1
	ldp	w24, w22, [x1, 8]
	ldp	w25, w23, [x1, 16]
	ldr	x1, [x19, 2352]
	add	x2, x19, x2, lsl 2
	ldr	x6, [x19, 2336]
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
	beq	.L3054
.L3024:
	ldr	x0, [x19, 2384]
	orr	w28, w27, w28
	ldr	w2, [x1, 4]
	orr	w28, w28, w21
	ldr	w0, [x0, 4]
	cmp	w2, w0
	beq	.L3055
.L3025:
	ldr	x0, .LC917
	mov	w6, 132
	strb	wzr, [x1, 2]
	mov	x3, -132
	stp	x5, x4, [x29, 96]
	ldr	x7, [x0, 104]
	ldr	w0, [x19, 156]
	ldr	x2, [x19, 2336]
	str	x3, [x29, 112]
	smaddl	x0, w0, w6, x3
	str	w6, [x29, 124]
	add	x0, x2, x0
	mov	x2, 132
	blr	x7
	ldr	w0, [x19, 156]
	ldr	w6, [x29, 124]
	ldr	x3, [x29, 112]
	ldr	x1, [x19, 2336]
	ldp	x5, x4, [x29, 96]
	smaddl	x0, w0, w6, x3
	add	x0, x1, x0
	str	x0, [x19, 2384]
.L3026:
	ldr	x0, [x19, 2392]
	mov	w3, w28
	ldr	w1, [x20, 56]
	ldr	w2, [x0, 56]
	cmp	w2, w1
	beq	.L3056
.L3037:
	ldr	w0, [x0, 184]
	ldr	w1, [x20, 184]
	str	w3, [x29, 124]
	cmp	w1, w0
	mov	x1, x20
	mov	x0, x19
	cset	w28, ne
	bl	HEVC_UpdatePicSPS
	ldr	w3, [x29, 124]
.L3028:
	ldr	x0, [x19, 2400]
	ldr	w1, [x0, 28]
	ldr	w0, [x26, 28]
	cmp	w1, w0
	beq	.L3057
.L3029:
	mov	x2, x26
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_UpdatePicPPS
.L3030:
	ldr	x0, [x19, 2392]
	ldr	x2, [x19, 2424]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	str	w0, [x2, 900]
	ldr	w0, [x20, 56]
	cmp	w0, w24
	beq	.L3058
.L3031:
	mov	w4, w28
	mov	w3, w23
	mov	w2, w25
	mov	w1, w22
	mov	x0, x19
	bl	HEVC_GetReRangeFlag
	cbnz	w0, .L3032
	ldr	x0, [x19, 2424]
	ldr	w1, [x0, 888]
	cmp	w1, 1
	beq	.L3032
.L3034:
	str	wzr, [x0, 904]
.L3033:
	mov	x0, x19
	bl	HEVC_AllocFrameStore
	mov	w20, w0
	cbnz	w0, .L3059
	mov	x0, x19
	bl	HEVC_InitPicInfo
	mov	w0, 0
.L3049:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3058:
	orr	w21, w27, w21
	orr	w21, w21, w28
	cbnz	w21, .L3031
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 888]
	cmp	w0, 1
	bne	.L3033
	.p2align 2
.L3032:
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_InitDPB
	cmn	w0, #2
	beq	.L3049
	cbnz	w0, .L3035
	ldr	x0, [x19, 2424]
	b	.L3034
	.p2align 3
.L3038:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3059:
	ldr	x1, .LC921
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3057:
	ldrb	w0, [x26, 1]
	cmp	w0, wzr
	cset	w0, ne
	orr	w3, w3, w0
	cbz	w3, .L3030
	b	.L3029
	.p2align 3
.L3056:
	ldrb	w1, [x5, x4]
	cmp	w1, wzr
	cset	w1, ne
	orr	w1, w28, w1
	mov	w28, 0
	cbz	w1, .L3028
	b	.L3037
	.p2align 3
.L3055:
	ldrb	w0, [x1, 2]
	cmp	w0, wzr
	cset	w0, ne
	orr	w0, w27, w0
	cbz	w0, .L3026
	b	.L3025
	.p2align 3
.L3054:
	ldr	w0, [x20, 68]
	cmp	w0, w25
	cset	w21, ne
	b	.L3024
.L3035:
	ldr	x1, .LC919
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L3049
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
	ldr	x20, [x19, 4016]
	mov	x2, 632
	ldr	w3, [x19, 3992]
	add	x1, x19, 4024
	add	x0, x20, 80
	str	w3, [x20, 16]
	bl	memcpy
	mov	x0, x19
	mov	x1, x20
	bl	HEVC_GetImagePara
	ldrb	w0, [x19, 3952]
	cbnz	w0, .L3068
.L3061:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	mov	w1, 0
	cbnz	w0, .L3069
.L3062:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3068:
	ldr	w0, [x19, 252]
	mov	w2, 1
	ldr	w1, [x20, 28]
	bl	FSP_SetRef
	b	.L3061
	.p2align 3
.L3069:
	ldr	x2, .LC922
	mov	w0, 0
	ldr	x1, .LC924
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w1, -1
	b	.L3062
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
	cbnz	w0, .L3073
	ldr	x0, [x19, 4016]
	mov	w2, 2
	mov	w1, 1
	str	w2, [x0, 52]
	str	w1, [x19, 11880]
	ldr	w0, [x19, 3960]
	ldr	w2, [x19, 3964]
	add	x0, x19, x0, lsl 2
	str	w2, [x0, 212]
	ldr	x0, [x19, 4016]
	strb	w1, [x0, 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3073:
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
	cbz	w0, .L3082
	cmn	w0, #3
	bne	.L3083
.L3078:
	mov	w0, 0
.L3077:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3082:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	cbz	w0, .L3078
	ldr	x2, .LC928
	mov	w0, 0
	ldr	x1, .LC929
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L3077
	.p2align 3
.L3083:
	ldr	x1, .LC931
	mov	w3, w0
	mov	w2, 11772
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 228]
	mov	x0, x19
	bl	HEVC_DECRecycleImage
	mov	w0, -1
	b	.L3077
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
	ldr	x19, [x20, 4016]
	mov	w4, 2
	mov	w3, 1
	add	x1, x20, 4024
	mov	x2, 632
	add	x0, x19, 80
	str	w4, [x19, 48]
	strb	wzr, [x19, 1]
	strb	w3, [x19, 2]
	ldr	w3, [x20, 3968]
	str	w3, [x19, 12]
	ldr	w3, [x20, 3992]
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
	add	x0, x20, 3952
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
	ldr	w1, [x19, 3988]
	cmp	w1, w2
	beq	.L3086
	add	x1, x19, x1, uxtw 2
	str	wzr, [x1, 2132]
	str	w2, [x19, 3988]
.L3086:
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
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w6, [x28, 2764]
	ldr	w27, [x28, 3960]
	cbz	w6, .L3098
	uxtw	x25, w27
	sub	w4, w6, #1
	add	x4, x4, 349
	add	x0, x28, 2784
	add	x26, x28, x25, lsl 2
	mov	w21, 0
	add	x4, x28, x4, lsl 3
	ldr	w3, [x26, 212]
	b	.L3090
	.p2align 3
.L3089:
	cmp	x0, x4
	beq	.L3109
.L3090:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cbnz	w2, .L3089
	ldr	w2, [x1, 32]
	cmp	w27, w2
	bne	.L3089
	ldr	w1, [x1, 8]
	cmp	w3, w1
	csinc	w21, w21, w21, ge
	cmp	x0, x4
	bne	.L3090
	.p2align 2
.L3109:
	add	x23, x28, 4096
	ldr	w0, [x23, 584]
	ldr	x1, [x28, 2392]
	mov	w19, 0
	ldr	x20, .LC933
	mov	w24, 0
	add	x0, x1, x0, lsl 2
	ldr	x22, .LC935
	add	x20, x20, 192
	ldr	w0, [x0, 360]
	str	w0, [x29, 108]
	.p2align 2
.L3097:
	add	x5, x28, x19, uxtw 3
	ldr	x0, [x5, 2784]
	ldrb	w1, [x0, 2]
	cbnz	w1, .L3092
	ldr	w2, [x0, 32]
	cmp	w27, w2
	beq	.L3110
.L3092:
	cbnz	w3, .L3094
	ldr	w4, [x0, 8]
	tbz	w4, #31, .L3094
	cbz	w1, .L3111
.L3095:
	mov	x2, x20
	mov	x1, x22
	mov	w0, 31
	bl	dprint_vfmw
	ldr	w6, [x28, 2764]
.L3094:
	add	w19, w19, 1
	cmp	w6, w19
	bls	.L3107
.L3096:
	ldr	w3, [x26, 212]
	b	.L3097
	.p2align 3
.L3110:
	ldr	w2, [x0, 8]
	cmp	w2, w3
	ble	.L3092
	ldr	w9, [x23, 584]
	ldr	w7, [x29, 108]
	cmp	w9, 7
	ccmp	w21, w7, 0, ls
	bls	.L3092
	ldr	w4, [x23, 572]
	cmp	w2, w4
	blt	.L3093
	add	x2, x28, x25
	ldrb	w2, [x2, 4]
	cbz	w2, .L3092
.L3093:
	mov	w1, 1
	strb	w1, [x0, 2]
	mov	x0, x28
	str	x5, [x29, 96]
	ldr	x1, [x5, 2784]
	add	w19, w19, 1
	sub	w21, w21, #1
	bl	HEVC_OutputFrmToVO
	mov	w24, w0
	ldr	x5, [x29, 96]
	ldr	x0, [x5, 2784]
	ldr	w0, [x0, 8]
	str	w0, [x26, 212]
	ldr	w6, [x28, 2764]
	cmp	w6, w19
	bhi	.L3096
.L3107:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3111:
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x28, 252]
	str	x5, [x29, 96]
	bl	FSP_SetDisplay
	ldr	x5, [x29, 96]
	ldr	w3, [x26, 212]
	ldr	x0, [x5, 2784]
	ldr	w4, [x0, 8]
	b	.L3095
.L3098:
	mov	w24, 0
	b	.L3107
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
	ldr	x1, [x20, 2784]
	strb	w2, [x1, 2]
	ldr	x1, [x20, 2784]
	bl	HEVC_OutputFrmToVO
	mov	w22, w0
	ldr	x0, [x20, 2784]
	ldr	w1, [x0, 32]
	ldr	w2, [x0, 8]
	add	x1, x19, x1, lsl 2
	str	w2, [x1, 212]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L3113
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L3113:
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
	cbnz	w0, .L3119
	ldr	w1, [x29, 44]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	mov	w1, 0
	cbnz	w0, .L3120
.L3116:
	ldr	x19, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3119:
	ldr	x2, .LC937
	mov	w0, 1
	ldr	x1, .LC939
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, -1
	b	.L3116
	.p2align 3
.L3120:
	ldr	x2, .LC937
	mov	w0, 1
	ldr	x1, .LC941
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w1, -1
	b	.L3116
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
	cbz	x19, .L3130
	ldr	w0, [x19, 2764]
	mov	w20, 0
	mov	w22, 1
	cbnz	w0, .L3133
	b	.L3129
	.p2align 3
.L3137:
	strb	w22, [x1, 2]
	ldr	x1, [x21, 2784]
	bl	HEVC_OutputFrmToVO
	cmn	w0, #1
	mov	w21, w0
	beq	.L3136
.L3126:
	ldr	w0, [x19, 2764]
	cmp	w0, w20
	bls	.L3129
.L3133:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 252]
	mov	w2, 0
	add	w20, w20, 1
	ldr	x1, [x21, 2784]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x21, 2784]
	mov	x0, x19
	ldrb	w2, [x1, 2]
	cbz	w2, .L3137
	ldr	w1, [x1, 28]
	ldr	w0, [x19, 252]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L3126
	ldr	x1, [x21, 2784]
	ldr	w0, [x19, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 2764]
	cmp	w0, w20
	bhi	.L3133
.L3129:
	mov	w1, -2147483647
	mov	x0, x19
	str	w1, [x19, 212]
	mov	w21, 0
	bl	HEVC_InitDecBuffers
.L3122:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3136:
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
.L3130:
	mov	w21, -1
	b	.L3122
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
	ldr	x0, [x19, 2368]
	str	wzr, [x19, 320]
	cbz	x0, .L3166
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 2424]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L3167
.L3145:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L3147
	ldr	x1, [x19, 2368]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bls	.L3148
	ldr	w2, [x1, 36]
	cmp	w2, 1
	beq	.L3147
.L3148:
	ldr	w2, [x20, 24]
	cmp	w2, wzr
	ble	.L3149
	ldr	x2, [x20, 8]
	cbz	x2, .L3149
	ldr	w3, [x20, 16]
	cbnz	w3, .L3168
.L3149:
	mov	w0, 1
	str	w0, [x1, 36]
	ldr	w0, [x19, 252]
	ldr	w1, [x20, 28]
	bl	SM_ReleaseStreamSeg
.L3144:
	ldr	x0, [x19, 2368]
	ldr	w0, [x0, 36]
	cmp	w0, wzr
	csetm	w0, eq
.L3142:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3168:
	uxtw	x0, w0
	add	x0, x1, x0, lsl 5
	str	x2, [x0, 40]
	ldr	x1, [x19, 2368]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 48]
	ldr	x1, [x19, 2368]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 52]
	ldr	x1, [x19, 2368]
	ldr	w2, [x20, 28]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 68]
	ldr	x1, [x19, 2368]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 60]
	ldr	x1, [x19, 2368]
	ldr	w0, [x1, 8]
	add	w0, w0, 1
	str	w0, [x1, 8]
	ldr	x0, [x19, 2424]
	ldrb	w0, [x0, 912]
	cmp	w0, 1
	beq	.L3150
	ldr	w0, [x19, 4004]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4008]
	add	w1, w0, w1
	str	w1, [x19, 4004]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4008]
.L3150:
	mov	x0, x19
	bl	HEVC_CombinePacket
	mov	w0, 1
	str	w0, [x19, 320]
	b	.L3144
	.p2align 3
.L3167:
	ldr	w0, [x0, 888]
	cbnz	w0, .L3144
	b	.L3145
	.p2align 3
.L3166:
	ldr	w0, [x20, 24]
	cmp	w0, wzr
	ble	.L3140
	ldr	x0, [x20, 8]
	cbz	x0, .L3140
	ldr	w0, [x20, 16]
	cbz	w0, .L3140
	mov	x0, x19
	bl	HEVC_FindNaluArraySlot
	cmn	w0, #1
	mov	w21, w0
	beq	.L3169
	ldr	x0, [x19, 2416]
	mov	w2, 104
	mov	w1, 1
	smaddl	x0, w21, w2, x0
	str	x0, [x19, 2368]
	ldr	x2, [x20, 8]
	str	x2, [x0, 40]
	ldr	x0, [x19, 2368]
	ldr	w2, [x20, 24]
	str	w2, [x0, 48]
	ldr	x0, [x19, 2368]
	ldr	w2, [x20, 28]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2368]
	ldr	w2, [x20, 16]
	str	w2, [x0, 52]
	ldr	x0, [x19, 2368]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2368]
	str	w1, [x0, 8]
	ldr	x0, [x19, 2368]
	strb	wzr, [x0]
	ldr	x0, [x19, 2368]
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 2424]
	ldrb	w0, [x0, 912]
	cmp	w0, 1
	beq	.L3144
	ldr	w0, [x19, 4004]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4008]
	add	w1, w0, w1
	str	w1, [x19, 4004]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4008]
	b	.L3144
	.p2align 3
.L3147:
	ldr	x1, .LC950
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3142
	.p2align 3
.L3140:
	ldr	x1, .LC948
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3142
.L3169:
	ldr	x1, .LC946
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, w21
	b	.L3142
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
	ldr	w2, [x19, 2764]
	cbnz	w2, .L3182
	b	.L3172
	.p2align 3
.L3173:
	cmp	w2, w20
	bls	.L3172
.L3182:
	add	x0, x19, x20, uxtw 3
	add	w20, w20, 1
	ldr	x0, [x0, 2784]
	ldrb	w1, [x0, 1]
	cbz	w1, .L3173
	strb	wzr, [x0, 1]
	mov	w2, 0
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 252]
	bl	FSP_SetRef
	ldr	w2, [x19, 2764]
	cmp	w2, w20
	bhi	.L3182
	.p2align 2
.L3172:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbz	w0, .L3176
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L3172
	b	.L3176
	.p2align 3
.L3178:
	bl	HEVC_GetMinPOC
	ldr	w1, [x29, 40]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L3177
.L3176:
	ldr	w3, [x19, 2764]
	add	x2, x29, 40
	add	x1, x29, 44
	mov	x0, x19
	cbnz	w3, .L3178
	mov	w0, 0
.L3177:
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
	cbz	w0, .L3188
	ldr	x2, .LC951
	mov	w3, w0
	ldr	x1, .LC953
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L3188:
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
	b	.L3193
	.p2align 3
.L3195:
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L3203
.L3193:
	ldr	w5, [x19, 2760]
	mov	x2, x21
	ldr	w6, [x19, 2764]
	mov	x1, x22
	mov	w0, 13
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcs	.L3195
.L3192:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3203:
	ldr	x1, .LC958
	mov	x2, x21
	mov	w0, 1
	add	x20, x20, 296
	bl	dprint_vfmw
	ldr	x21, .LC960
	.p2align 2
.L3194:
	ldr	w5, [x19, 2760]
	mov	x2, x20
	ldr	w6, [x19, 2764]
	mov	x1, x21
	mov	w0, 1
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcc	.L3192
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_OutputUnRefPicWithMinPoc
	cbz	w0, .L3194
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
	bhi	.L3208
	add	x20, x21, x22, uxtw 3
	ldr	x0, [x19, 64]
	mov	w1, 1
	mov	w2, w1
	str	x0, [x20, 2784]
	str	w1, [x0, 48]
	ldr	x1, [x20, 2784]
	ldr	w0, [x21, 252]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldrb	w1, [x19]
	mov	x2, 632
	ldr	x0, [x20, 2784]
	cmp	w1, wzr
	add	x1, x19, 72
	cset	w3, ne
	strb	w3, [x0, 1]
	ldr	x0, [x20, 2784]
	ldr	w3, [x19, 36]
	str	w3, [x0, 20]
	ldr	x0, [x20, 2784]
	add	x0, x0, 80
	bl	memcpy
	ldr	x0, [x20, 2784]
	add	w1, w22, 1
	ldr	w4, [x19, 40]
	mov	w2, 8
	ldr	x3, .LC966
	str	w4, [x0, 16]
	add	x0, x21, 2784
	ldr	x4, [x20, 2784]
	ldr	x5, [x19, 64]
	str	x5, [x4, 72]
	ldr	x4, [x20, 2784]
	ldr	w5, [x19, 16]
	str	w5, [x4, 12]
	ldr	x4, [x20, 2784]
	ldr	w5, [x19, 12]
	str	w5, [x4, 8]
	ldr	x4, [x20, 2784]
	ldr	w5, [x19, 8]
	str	w5, [x4, 32]
	bl	qsort
	ldr	w1, [x21, 2764]
	mov	x0, x21
	add	w1, w1, 1
	str	w1, [x21, 2764]
	ldr	x1, [x19, 64]
	bl	HEVC_GetAPC
	cbnz	w0, .L3209
	strb	wzr, [x19, 1]
	mov	w0, 0
.L3206:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3208:
	ldr	x2, .LC963
	mov	w3, w22
	ldr	x1, .LC965
	mov	w0, 0
	add	x2, x2, 320
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L3206
	.p2align 3
.L3209:
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
	b	.L3206
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
	ldrb	w0, [x19, 3952]
	cbnz	w0, .L3223
	ldr	x0, [x19, 4016]
	mov	w1, 2
	str	w1, [x0, 48]
.L3212:
	ldr	x1, [x19, 4016]
	mov	w2, 1
	mov	x0, x19
	strb	w2, [x1, 2]
	ldr	x1, [x19, 4016]
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L3224
	cmn	w0, #3
	beq	.L3216
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L3225
.L3216:
	mov	w0, 0
.L3213:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3223:
	mov	x0, x19
	bl	HEVC_SimpleSlideDPB
	ldr	w1, [x19, 2764]
	add	x2, x19, 3952
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbz	w0, .L3212
	ldr	x2, .LC969
	mov	w4, w0
	ldr	x1, .LC971
	mov	w3, 10933
	add	x2, x2, 344
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
	.p2align 3
.L3225:
	ldr	x2, .LC969
	mov	w0, 0
	ldr	x1, .LC974
	add	x2, x2, 344
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3213
.L3224:
	ldr	x2, .LC969
	mov	w0, 0
	ldr	x1, .LC973
	add	x2, x2, 344
	bl	dprint_vfmw
	mov	w0, w20
	b	.L3213
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
	ldr	w0, [x19, 2760]
	ldr	w1, [x19, 2764]
	cmp	w1, w0
	bcs	.L3238
.L3227:
	add	x2, x19, 3952
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3239
	ldr	x1, [x19, 4016]
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L3240
	cmn	w0, #3
	beq	.L3233
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L3241
.L3233:
	mov	w0, 0
.L3230:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3238:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L3237
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC977
	add	x2, x2, 368
	bl	dprint_vfmw
.L3237:
	ldr	w1, [x19, 2764]
	b	.L3227
.L3241:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC981
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3230
	.p2align 3
.L3239:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC979
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3230
.L3240:
	ldr	x2, .LC975
	mov	w0, 0
	ldr	x1, .LC980
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, w20
	b	.L3230
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
	ldr	w0, [x19, 11880]
	cmp	w0, 1
	beq	.L3243
	mov	x0, x19
	bl	HEVC_FirstFrameFastOut
	cbnz	w0, .L3260
.L3243:
	ldr	w0, [x19, 2760]
	ldr	w1, [x19, 2764]
	cmp	w1, w0
	bcs	.L3261
.L3245:
	add	x2, x19, 3952
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3262
	ldr	w0, [x19, 2764]
	cbnz	w0, .L3248
.L3249:
	mov	w0, 0
.L3244:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3248:
	mov	x0, x19
	bl	HEVC_OutputFrmFromDPB
	cbz	w0, .L3249
	ldr	x2, .LC982
	mov	w0, 1
	ldr	x1, .LC990
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
	.p2align 3
.L3261:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L3259
	ldr	x1, .LC986
	mov	w0, 0
	bl	dprint_vfmw
.L3259:
	ldr	w1, [x19, 2764]
	b	.L3245
	.p2align 3
.L3262:
	ldr	x1, .LC988
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
.L3260:
	ldr	x2, .LC982
	mov	w0, 0
	ldr	x1, .LC984
	add	x2, x2, 392
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
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
	beq	.L3302
.L3264:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w0, [x19, 3953]
	cbz	w0, .L3303
	ldr	w0, [x19, 3992]
	cbz	w0, .L3269
	ldr	w1, [x19, 3968]
	cbz	w1, .L3304
.L3270:
	ldr	x1, [x19, 2424]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bcc	.L3305
.L3269:
	ldr	x1, [x19, 2440]
	ldr	x0, [x19, 4016]
	ldr	w1, [x1, 5188]
	str	w1, [x0, 40]
	ldr	x1, [x19, 2440]
	ldr	x0, [x19, 4016]
	ldr	w1, [x1, 5192]
	str	w1, [x0, 44]
	ldr	w0, [x19, 256]
	cmp	w0, 2
	beq	.L3306
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	beq	.L3307
	cmp	w0, 1
	beq	.L3308
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3282
.L3280:
	mov	x0, x19
	bl	HEVC_DispOrderProcess
	mov	w20, w0
	cbnz	w0, .L3309
.L3281:
	strb	wzr, [x19, 3953]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3302:
	ldr	w1, [x0, 156]
	cbnz	w1, .L3264
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L3264
	add	x0, x19, 8192
	ldrb	w0, [x0, 3632]
	cmp	w0, 1
	bne	.L3264
	ldr	w4, [x19, 11836]
	ldr	w5, [x19, 11840]
	ldr	x6, [x19, 11848]
	ldr	x3, [x19, 11856]
	ldr	x7, [x19, 11864]
	cbz	w4, .L3283
	mov	w1, w4
	mov	w2, w5
	b	.L3266
	.p2align 3
.L3284:
	mov	w1, w0
.L3266:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L3284
.L3265:
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
	str	x0, [x19, 4608]
	b	.L3264
	.p2align 3
.L3303:
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
.L3305:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x3, [x19, 2424]
	mov	w0, 1
	ldr	w2, [x19, 3992]
	ldr	x1, .LC999
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3307:
	mov	x0, x19
	bl	HEVC_SimpleDPBProcess
	mov	w20, w0
	cbnz	w0, .L3310
.L3277:
	ldr	x1, .LC1003
	mov	w3, 11210
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L3275:
	cmn	w20, #1
	bne	.L3281
	.p2align 2
.L3282:
	mov	x0, x19
	mov	w20, -1
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC992
	mov	w0, 1
	ldr	x1, .LC1011
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3281
	.p2align 3
.L3304:
	ldr	x2, .LC992
	mov	w0, 1
	ldr	x1, .LC996
	add	x2, x2, 416
	bl	dprint_vfmw
	ldr	x0, .LC997
	ldr	x4, [x0]
	cbz	x4, .L3301
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3301:
	ldr	w0, [x19, 3992]
	b	.L3270
	.p2align 3
.L3306:
	mov	x0, x19
	bl	HEVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 184]
	ldr	w0, [x19, 3988]
	cmp	w0, w1
	beq	.L3273
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 2132]
	str	w1, [x19, 3988]
.L3273:
	cbnz	w20, .L3311
.L3274:
	ldr	x1, .LC1003
	mov	w3, 11195
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3275
	.p2align 3
.L3308:
	mov	x0, x19
	bl	HEVC_DecOrderProcess
	mov	w20, w0
	cbnz	w0, .L3279
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3281
	b	.L3280
	.p2align 3
.L3309:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1009
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3275
	.p2align 3
.L3279:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1007
	add	x2, x2, 416
	bl	dprint_vfmw
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3275
	b	.L3280
	.p2align 3
.L3311:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1001
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3274
	.p2align 3
.L3310:
	ldr	x2, .LC992
	mov	w0, 0
	ldr	x1, .LC1005
	add	x2, x2, 416
	bl	dprint_vfmw
	b	.L3277
.L3283:
	mov	w1, w5
	b	.L3265
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
	add	x19, x19, 1152
	ldr	x3, [x3, 96]
	blr	x3
	.p2align 2
.L3318:
	ldr	w0, [x19, 48]
	cbnz	w0, .L3313
	cbz	x19, .L3314
	ldr	w2, [x20, 2764]
	cbz	w2, .L3314
	ldr	x0, [x20, 2784]
	cmp	x19, x0
	beq	.L3313
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L3316
	.p2align 3
.L3317:
	ldr	x1, [x0, 2784]
	cmp	x19, x1
	beq	.L3313
.L3316:
	cmp	x2, x0
	add	x0, x0, 8
	bne	.L3317
.L3314:
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
	add	x1, x25, 1232
	bl	memcpy
	strb	w24, [x25, 1154]
	str	wzr, [x22, 13492]
	cmp	w21, 19
	strb	w24, [x25, 1152]
	str	x19, [x29, 144]
	str	wzr, [x29, 304]
	bgt	.L3319
	ldr	w5, [x20, 2764]
	cbz	w5, .L3321
	mov	w6, 0
	mov	w3, 2147483647
	mov	w1, 0
	.p2align 2
.L3324:
	add	x0, x20, x1, sxtw 3
	add	w1, w1, 1
	ldr	x4, [x0, 2784]
	ldr	w0, [x4, 8]
	sub	w0, w0, w23
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w3
	bge	.L3323
	ldrb	w0, [x4, 1]
	cmp	w0, wzr
	csel	w3, w3, w2, eq
	csinc	w6, w6, wzr, eq
.L3323:
	cmp	w1, w5
	bne	.L3324
	cbz	w6, .L3321
	mov	w1, 0
	b	.L3325
	.p2align 3
.L3326:
	cmp	w5, w1
	beq	.L3327
.L3325:
	sxtw	x19, w1
	add	w1, w1, 1
	add	x19, x19, 346
	add	x19, x20, x19, lsl 3
	ldr	x2, [x19, 16]
	ldr	w0, [x2, 8]
	sub	w0, w0, w23
	sxtw	x0, w0
	eor	x4, x0, x0, asr 63
	sub	x4, x4, x0, asr 63
	cmp	w3, w4
	bne	.L3326
	ldrb	w0, [x2, 1]
	cbz	w0, .L3326
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
	cbz	x21, .L3327
	ldr	x0, [x21, 32]
	cbz	x0, .L3360
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
	beq	.L3330
	ldr	x3, [x29, 144]
	add	x2, x29, 80
	mov	x0, x20
	str	w19, [x3, 28]
	ldr	x3, [x21, 32]
	str	x3, [x1, 32]
	ldr	x3, [x21, 40]
	str	x3, [x1, 40]
	ldrsb	w3, [x21, 4]
	ldr	w1, [x20, 2764]
	str	w22, [x29, 88]
	str	w3, [x29, 116]
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L3361
	ldr	w0, [x20, 252]
	mov	w2, 0
	mov	w1, w19
	bl	FSP_SetDisplay
	ldr	w1, [x20, 4688]
	mov	w2, 2147483647
	mov	w0, 0
	add	x20, x20, x1, lsl 2
	ldr	w1, [x20, 228]
	cmp	w1, w2
	bne	.L3346
	str	w23, [x20, 228]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L3313:
	add	w21, w21, 1
	add	x19, x19, 712
	cmp	w21, 20
	bne	.L3318
.L3319:
	ldr	x1, .LC1014
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L3346:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 704
	ret
	.p2align 3
.L3327:
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
.L3330:
	ldr	x2, [x29, 144]
	mov	w0, 0
	ldr	x1, .LC1024
	strb	wzr, [x2]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3346
.L3361:
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
	b	.L3346
.L3321:
	ldr	x1, .LC1018
	mov	w0, 0
	strb	wzr, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3346
.L3360:
	ldr	x1, .LC1022
	bl	dprint_vfmw
	mov	x0, x20
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L3346
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
	b	.L3363
	.p2align 3
.L3366:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.7
	cbnz	w0, .L3368
	ldr	w2, [x29, 44]
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2424]
	mov	x0, x19
	ldr	w1, [x1, 4]
	cbz	w1, .L3364
	ldr	w1, [x29, 44]
	bl	HEVC_CreateLostPicture
	cbnz	w0, .L3371
.L3363:
	ldr	w2, [x19, 4684]
	add	x1, x29, 44
	mov	x0, x19
	sub	w2, w2, #19
	cmp	w2, 2
	bhi	.L3366
.L3368:
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
.L3364:
	ldr	w3, [x19, 4668]
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
.L3371:
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
	bls	.L3431
	ldr	w0, [x19, 288]
	mov	w2, 1
	ldr	w1, [x19, 292]
	add	w0, w0, 1
	ldr	x3, [x19, 2424]
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 288]
	sub	w0, w0, w1
	str	w0, [x3, 576]
	strb	w2, [x19, 3952]
	ldr	w20, [x19, 248]
	ldr	w2, [x19, 256]
	ubfx	x20, x20, 16, 3
	cmp	w20, w2
	beq	.L3377
	sub	w0, w2, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L3377
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L3432
.L3377:
	cmp	w20, 2
	str	w20, [x19, 256]
	beq	.L3379
	cmp	w20, 3
	bne	.L3428
.L3430:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
.L3427:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3428:
	ldr	w0, [x19, 236]
	cbz	w0, .L3398
	cmp	w20, 4
	ldr	w0, [x19, 3968]
	bne	.L3385
	cbnz	w0, .L3385
	mov	w0, 2
	strb	w0, [x19, 6]
	.p2align 2
.L3389:
	ldr	w2, [x19, 240]
	mov	w0, 2
	ldr	x1, .LC1040
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x19, 204]
	cbz	w0, .L3433
	ldr	w2, [x19, 3980]
	ldr	x1, [x19, 2424]
	ldr	w3, [x19, 3984]
	cmp	w2, wzr
	str	w3, [x19, 7956]
	cset	w3, eq
	str	w0, [x19, 9112]
	add	x0, x19, 4096
	str	w3, [x19, 7964]
	ldr	w3, [x1, 592]
	strb	w3, [x0, 2528]
	ldr	w3, [x1, 596]
	strb	w3, [x0, 2529]
	ldr	w3, [x1, 600]
	strb	w3, [x0, 2531]
	ldr	w3, [x1, 604]
	strb	w3, [x0, 2532]
	ldr	w3, [x1, 644]
	ldr	w1, [x19, 240]
	str	w3, [x19, 7952]
	cbz	w1, .L3394
	add	x0, x0, 2528
	ldr	w1, [x19, 3996]
	str	x0, [x19, 2440]
	add	w2, w2, 1
	str	w1, [x0, 5188]
	ldr	w1, [x19, 4000]
	str	w1, [x0, 5192]
	str	w2, [x19, 3980]
	ldr	w0, [x19, 3968]
	cbnz	w0, .L3394
	ldr	x1, [x19, 9120]
	mov	w4, 0
	cbz	x1, .L3396
	.p2align 2
.L3397:
	ldp	w2, w0, [x1]
	ldr	x1, [x1, 1360]
	add	w0, w2, w0
	add	w0, w0, 7
	add	w4, w4, w0, lsr 3
	cbnz	x1, .L3397
.L3396:
	ldr	x0, .LC1031
	ldr	x5, [x0]
	cbz	x5, .L3394
	add	x2, x29, 48
	ldr	w0, [x19, 252]
	mov	w3, 4
	mov	w1, 20
	str	w4, [x2, -8]!
	blr	x5
.L3394:
	ldr	w4, [x19, 4008]
	mov	w0, 0
	ldr	x3, [x19, 4016]
	ldr	w1, [x19, 4004]
	str	w4, [x19, 4004]
	sub	w1, w1, w4
	ldr	w2, [x3, 320]
	add	w2, w2, w1
	str	w2, [x3, 320]
	ldr	w2, [x19, 4264]
	add	w1, w2, w1
	str	w1, [x19, 4264]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3379:
	ldr	w0, [x19, 3968]
	cbnz	w0, .L3383
	ldr	w1, [x19, 236]
	cbz	w1, .L3398
.L3385:
	cmp	w0, 2
	beq	.L3434
	cmp	w0, 1
	bne	.L3389
	strb	w0, [x19, 6]
	b	.L3389
	.p2align 3
.L3434:
	ldrb	w0, [x19, 6]
	cmp	w0, 2
	bne	.L3389
	ldr	x0, .LC1038
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3389
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L3389
	mov	w3, 1
	ldr	x1, .LC1045
	ldr	w2, [x19, 3964]
	mov	w0, w3
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3435
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, -1
	b	.L3427
	.p2align 3
.L3398:
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3383
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3383:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L3427
.L3432:
	ldr	x1, .LC1037
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	str	w20, [x19, 256]
	b	.L3430
	.p2align 3
.L3435:
	mov	w0, -1
	b	.L3427
	.p2align 3
.L3433:
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3392
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3392:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1041
	mov	w0, 0
	ldr	x1, .LC1043
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3427
	.p2align 3
.L3431:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1031
	ldr	x4, [x0]
	cbz	x4, .L3374
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3374:
	ldr	w0, [x19, 244]
	cmp	w0, 524288
	bls	.L3375
	ldr	x1, .LC1033
	mov	w0, 0
	bl	dprint_vfmw
.L3375:
	ldr	x1, .LC1035
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3427
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
	ldr	x0, [x19, 2328]
	mov	w1, 16
	str	xzr, [x29, 88]
	add	x22, x19, 4096
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	and	w24, w0, 31
	ldr	x0, [x19, 2328]
	mov	w1, 24
	bl	BsBack
	str	wzr, [x22, 348]
	ldr	x1, [x22, 360]
	str	x1, [x29, 88]
	cbz	w20, .L3438
	cmp	w20, 1
	beq	.L3439
	ldr	x1, .LC1062
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
.L3446:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3439:
	mov	w0, 31745
	cmp	w21, w0
	cbz	w23, .L3596
	ccmp	w24, 25, 0, eq
	bne	.L3467
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3468
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3468:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2368]
	cbz	w0, .L3597
.L3591:
	cbz	x1, .L3472
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3472:
	ldr	x4, [x20]
	cbz	x4, .L3571
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3571:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3438:
	cbnz	w23, .L3440
	mov	w0, 31745
	cmp	w21, w0
	ccmp	w24, 25, 0, eq
	bne	.L3441
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3442
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3442:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2368]
	cbnz	w0, .L3591
	ldr	w0, [x1, 48]
	add	x23, x22, 344
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L3447
	ldr	x1, .LC1048
	mov	w3, 2348
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	b	.L3591
	.p2align 3
.L3440:
	mov	w0, 31745
	and	w21, w21, -513
	cmp	w21, w0
	mov	w0, 1
	bne	.L3446
	ldr	x2, .LC1049
	mov	w3, 2434
	ldr	x1, .LC1058
.L3575:
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	cbz	x1, .L3571
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
	mov	w0, -1
	b	.L3446
	.p2align 3
.L3596:
	ccmp	w25, 1, 0, eq
	ccmp	w24, 25, 0, eq
	beq	.L3598
	mov	w1, 32257
	cmp	w21, w1
	beq	.L3599
	cmp	w21, w0
	bne	.L3600
.L3479:
	ldr	x1, [x19, 2368]
.L3582:
	cbz	x1, .L3572
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3572:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3467:
	mov	w1, 32257
	mov	w0, w20
	cmp	w21, w1
	bne	.L3446
	ldr	x2, .LC1049
	mov	w3, 2579
	ldr	x1, .LC1060
	b	.L3575
	.p2align 3
.L3441:
	mov	w1, 32257
	mov	w0, 1
	cmp	w21, w1
	bne	.L3446
	b	.L3479
	.p2align 3
.L3597:
	ldr	w0, [x1, 48]
	add	x23, x22, 344
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x23, 4]
	cmp	x2, 1024
	bls	.L3471
	ldr	x1, .LC1048
	mov	w3, 2513
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	b	.L3591
	.p2align 3
.L3600:
	ldr	x0, [x19, 2328]
	mov	w1, 8
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2328]
	mov	w1, 8
	ubfx	x20, x20, 1, 6
	bl	BsSkip
	cmp	w20, 49
	bne	.L3479
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L3479
	ldr	x1, [x19, 2368]
	ldr	x0, [x19, 2328]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2328]
	mov	w1, 24
	bl	BsSkip
	mov	w0, 2
	b	.L3446
	.p2align 3
.L3598:
	ldr	x20, .LC1046
	ldr	x4, [x20]
	cbz	x4, .L3461
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3461:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2368]
	cbz	w0, .L3582
	b	.L3591
	.p2align 3
.L3471:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 252]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3601
	ldr	x21, .LC1052
	mov	x2, 5
	ldr	x1, .LC1053
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2368]
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
	ldr	x1, [x19, 2368]
	ldr	w2, [x1, 80]
	cbz	w2, .L3474
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L3475
	uxtw	x2, w0
	ldr	x1, .LC1048
	mov	w3, 2537
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	cbz	x1, .L3476
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3476:
	ldr	x4, [x20]
	cbz	x4, .L3477
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3477:
	ldr	w0, [x19, 252]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3571
	ldr	x2, .LC1049
	mov	w3, 2544
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
	.p2align 3
.L3447:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 252]
	add	w3, w3, w2
	ldr	w1, [x23, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3602
	ldr	x21, .LC1052
	mov	x2, 5
	ldr	x1, .LC1053
	ldr	x0, [x29, 88]
	ldr	x3, [x21, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2368]
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
	ldr	x1, [x19, 2368]
	ldr	w2, [x1, 80]
	cbz	w2, .L3451
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L3452
	uxtw	x2, w0
	ldr	x1, .LC1048
	mov	w3, 2372
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	cbz	x1, .L3453
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3453:
	ldr	x4, [x20]
	cbz	x4, .L3454
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3454:
	ldr	w0, [x19, 252]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3571
	ldr	x2, .LC1049
	mov	w3, 2379
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
.L3452:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2368]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L3451:
	ldr	x20, .LC1056
	ldr	w0, [x19, 252]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L3455
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 252]
	ldr	w1, [x22, 348]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 252]
.L3455:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3479
	ldr	x2, .LC1049
	mov	w3, 2407
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
	.p2align 3
.L3475:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x21, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2368]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x23, 4]
.L3474:
	ldr	x20, .LC1056
	ldr	w0, [x19, 252]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L3478
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 252]
	ldr	w1, [x22, 348]
	ldr	x3, [x21, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 252]
.L3478:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L3479
	ldr	x2, .LC1049
	mov	w3, 2567
	ldr	x1, .LC1055
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
	.p2align 3
.L3599:
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsSkip
	mov	w0, w20
	b	.L3446
.L3601:
	ldr	x2, .LC1049
	mov	w3, 2525
	ldr	x1, .LC1051
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
.L3602:
	ldr	x2, .LC1049
	mov	w3, 2360
	ldr	x1, .LC1051
	mov	w0, 0
	add	x2, x2, 456
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3446
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
	ldr	w0, [x19, 2764]
	cbz	w0, .L3615
	sub	w2, w0, #1
	mov	w20, 0
	add	x2, x2, 349
	add	x0, x19, 2784
	add	x2, x19, x2, lsl 3
	.p2align 2
.L3606:
	ldr	x1, [x0], 8
	ldrb	w1, [x1, 2]
	cmp	w1, wzr
	csinc	w20, w20, w20, ne
	cmp	x0, x2
	bne	.L3606
	.p2align 2
.L3607:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L3607
	cmp	w20, wzr
	ble	.L3609
	.p2align 2
.L3622:
	ldr	w1, [x19, 2764]
	cbz	w1, .L3610
	ldr	x0, [x19, 2784]
	ldrb	w0, [x0, 2]
	cbz	w0, .L3617
	add	x2, x19, 2792
	mov	w0, 0
	b	.L3614
	.p2align 3
.L3611:
	ldr	x3, [x2], 8
	ldrb	w3, [x3, 2]
	cbz	w3, .L3616
.L3614:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3611
.L3610:
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L3612
	subs	w20, w20, #1
	bne	.L3622
.L3609:
	mov	w0, 0
.L3612:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3616:
	mov	w1, w0
	b	.L3610
.L3617:
	mov	w1, 0
	b	.L3610
.L3615:
	mov	w20, 0
	b	.L3607
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
	ldr	x0, [x19, 2368]
	ldrsw	x3, [x19, 252]
	ldr	x2, .LC1063
	ldr	w1, [x0, 16]
	str	w1, [x19, 4684]
	ldr	w4, [x0, 28]
	str	w4, [x19, 4680]
	ldr	w20, [x0, 24]
	strb	wzr, [x19, 3]
	str	w20, [x19, 4688]
	ldr	x2, [x2, x3, lsl 3]
	ldrsb	w3, [x2, 44]
	cmp	w3, 1
	beq	.L3683
.L3630:
	ldr	w0, [x19, 4808]
	cmp	w0, 1
	beq	.L3684
.L3634:
	ldr	w0, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w0
	bcs	.L3685
	ldrb	w0, [x19, 3953]
	cbz	w0, .L3686
	mov	x0, x19
	bl	HEVC_PicTypeStatistic
	mov	x0, x19
	bl	HEVC_CalcStreamBits
	ldr	w0, [x19, 4808]
	cmp	w0, 2
	beq	.L3648
	add	x0, x19, 4096
	ldrb	w0, [x0, 561]
	cbz	w0, .L3687
.L3649:
	mov	x0, x19
	bl	HEVC_WriteSliceMsg
	cbnz	w0, .L3688
.L3652:
	ldr	w0, [x19, 3340]
	mov	w2, 1
	ldr	w1, [x19, 3336]
	ldr	w3, [x19, 4668]
	ldr	w4, [x19, 4692]
	str	w0, [x19, 4000]
	mov	w0, 0
	str	w2, [x19, 172]
	str	w3, [x19, 260]
	str	w4, [x19, 296]
	str	w1, [x19, 3996]
.L3637:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3687:
	mov	x0, x19
	bl	HEVC_DecList
	cbnz	w0, .L3689
	mov	x0, x19
	bl	HEVC_IsRefListWrong
	cbz	w0, .L3649
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	x1, .LC1085
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3684:
	cmp	w20, wzr
	sub	w1, w1, #16
	cset	w21, eq
	cmp	w1, 4
	cset	w0, ls
	tst	w21, w0
	beq	.L3690
.L3635:
	mov	x0, x19
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L3691
.L3636:
	add	x0, x19, x20, uxtw
	ldrb	w0, [x0, 4]
	cmp	w0, 1
	cset	w0, eq
	tst	w21, w0
	beq	.L3638
	ldr	w0, [x19, 2764]
	cbz	w0, .L3638
	mov	x0, x19
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L3638
	ldr	x2, .LC1064
	mov	w0, 1
	ldr	x1, .LC1068
	add	x2, x2, 480
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3690:
	ldr	w0, [x19, 3968]
	cbnz	w0, .L3636
	ldr	x0, [x19, 2424]
	mov	x1, 4294967296
	ldr	x2, [x0, 648]
	cmp	x2, x1
	bne	.L3636
	ldr	w1, [x0, 656]
	cbnz	w1, .L3636
	ldr	w0, [x0, 612]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L3636
	b	.L3635
	.p2align 3
.L3638:
	ldr	x0, [x19, 2424]
	ldr	w1, [x0, 12]
	cbnz	w1, .L3639
	cbnz	w20, .L3639
	ldr	w3, [x19, 212]
	mov	w20, -2147483647
	cmp	w3, w20
	beq	.L3639
	ldr	w1, [x19, 4680]
	ldr	x4, [x19, 2392]
	ldr	w2, [x19, 4668]
	add	x1, x4, x1, lsl 2
	ldr	w1, [x1, 360]
	add	w1, w3, w1
	cmp	w2, w1
	bcs	.L3639
	ldr	w1, [x19, 4684]
	cmp	w1, 21
	bne	.L3639
	ldr	x1, .LC1070
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_CRAOutputFrame
	str	w20, [x19, 212]
	ldr	x0, [x19, 2424]
	.p2align 2
.L3639:
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L3641
	ldr	w0, [x0, 24]
	cmp	w0, 2
	mov	x0, x19
	beq	.L3692
	bl	HEVC_RefPicProcess
	cbnz	w0, .L3654
.L3641:
	mov	x0, x19
	bl	HEVC_InitPic
	cmn	w0, #2
	beq	.L3637
	cbnz	w0, .L3693
	ldr	w1, [x19, 240]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x19, 240]
	bl	HEVC_SetScalingList
	mov	x0, x19
	bl	HEVC_WritePicMsg
	cbz	w0, .L3634
	ldr	x1, .LC1074
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3683:
	ldr	w3, [x2, 156]
	cbnz	w3, .L3630
	ldr	w2, [x2, 160]
	cmp	w2, 1
	bne	.L3630
	ldr	w0, [x0, 16]
	sub	w2, w0, #19
	cmp	w2, 1
	bls	.L3694
.L3632:
	sub	w0, w0, #6
	cmp	w0, 3
	bls	.L3630
	ldr	x2, [x19, 3376]
	str	x2, [x19, 3360]
	b	.L3630
	.p2align 3
.L3648:
	ldr	x1, [x19, 2368]
	cbz	x1, .L3652
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
	b	.L3652
	.p2align 3
.L3692:
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
	b	.L3641
.L3654:
	mov	w0, -1
	b	.L3637
.L3691:
	ldr	x2, .LC1064
	mov	w0, 1
	ldr	x1, .LC1066
	add	x2, x2, 480
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3686:
	ldr	x1, .LC1081
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3685:
	ldr	x1, .LC1076
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w1
	bcc	.L3646
	ldr	x0, .LC1077
	ldr	x4, [x0]
	cbz	x4, .L3646
	ldr	w0, [x19, 252]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L3646:
	ldr	x1, .LC1079
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3689:
	ldr	x1, .LC1083
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3688:
	ldr	x1, .LC1087
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
	.p2align 3
.L3694:
	ldr	x2, [x19, 2424]
	ldr	x2, [x2, 56]
	cmn	x2, #1
	beq	.L3633
	ldr	x3, [x19, 11856]
	str	x2, [x19, 11848]
	str	x3, [x19, 11864]
.L3633:
	add	x2, x19, 8192
	mov	w3, 1
	strb	w3, [x2, 3632]
	b	.L3632
	.p2align 3
.L3693:
	ldr	x1, .LC1072
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3637
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
	ldr	x3, [x19, 2368]
	ldr	w0, [x3, 8]
	cbz	w0, .L3700
	ldr	w2, [x19, 244]
	mov	w0, 0
	.p2align 2
.L3699:
	uxtw	x1, w0
	add	w0, w0, 1
	add	x1, x3, x1, lsl 5
	ldr	w1, [x1, 48]
	add	w2, w2, w1
	str	w2, [x19, 244]
	ldr	w1, [x3, 8]
	cmp	w1, w0
	bhi	.L3699
.L3700:
	strb	wzr, [x3]
	ldr	x0, [x19, 2368]
	ldr	w1, [x0, 16]
	sub	w1, w1, #36
	cmp	w1, 1
	bls	.L3843
.L3698:
	ldr	w1, [x0, 4]
	add	w1, w1, 16
	str	w1, [x0, 4]
	ldr	x1, [x19, 2368]
	ldr	w2, [x1, 16]
	cmp	w2, 49
	bls	.L3844
.L3701:
	ldr	x1, .LC1099
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	ldr	w0, [x1, 16]
	cmp	w0, 63
	bhi	.L3728
	cbnz	x1, .L3830
	.p2align 2
.L3828:
	mov	w0, 0
.L3847:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3844:
	ldr	x0, .LC1088
	ldrb	w0, [x0,w2,uxtw]
	adr	x3, .Lrtx3703
	add	x0, x3, w0, sxtb #2
	br	x0
.Lrtx3703:
	.section	.rodata
	.align	0
	.align	2
.L3703:
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3702 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3704 - .Lrtx3703) / 4
	.byte	(.L3705 - .Lrtx3703) / 4
	.byte	(.L3706 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3707 - .Lrtx3703) / 4
	.byte	(.L3707 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3701 - .Lrtx3703) / 4
	.byte	(.L3708 - .Lrtx3703) / 4
	.byte	(.L3709 - .Lrtx3703) / 4
	.text
	.p2align 3
.L3843:
	mov	w1, 1
	strb	w1, [x19, 3]
	b	.L3698
.L3709:
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L3845
.L3725:
	ldr	x1, [x19, 2368]
	cbz	x1, .L3828
.L3830:
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
	mov	w0, 0
.L3827:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3702:
	mov	x0, x19
	bl	HEVC_DecSlice
	cmn	w0, #2
	beq	.L3827
	cbz	w0, .L3828
	ldr	x1, [x19, 2368]
	cbz	x1, .L3841
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3841:
	ldr	x0, .LC1091
	ldr	x4, [x0]
	cbz	x4, .L3829
.L3831:
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3829:
	mov	w0, -1
.L3846:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3705:
	mov	x0, x19
	bl	HEVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 2368]
	cbz	x1, .L3715
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3715:
	cbz	w20, .L3828
	ldr	x1, .LC1093
	b	.L3838
.L3706:
	mov	x0, x19
	bl	HEVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 2368]
	cbz	x1, .L3717
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3717:
	cbz	w20, .L3828
	ldr	x1, .LC1095
	b	.L3838
.L3704:
	mov	x0, x19
	bl	HEVC_DecVPS
	mov	w20, w0
	ldr	x1, [x19, 2368]
	cbz	x1, .L3710
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3710:
	cbz	w20, .L3828
	ldr	x1, .LC1090
.L3838:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1091
	ldr	x4, [x21]
	cbz	x4, .L3829
	add	x2, x29, 64
	ldr	w0, [x19, 252]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L3829
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
.L3707:
	mov	x0, x19
	bl	HEVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 2368]
	cbz	x1, .L3718
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3718:
	cbz	w20, .L3828
	ldr	x1, .LC1097
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3841
.L3708:
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	beq	.L3723
	cbz	x1, .L3722
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3722:
	ldrb	w0, [x19, 3953]
	cbz	w0, .L3828
.L3723:
	add	x20, x19, 2720
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
	bne	.L3828
	ldr	x20, .LC1091
	ldr	x4, [x20]
	cbz	x4, .L3724
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3724:
	ldrb	w0, [x19, 3953]
	cbz	w0, .L3828
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L3828
.L3727:
	ldr	x4, [x20]
	cbnz	x4, .L3831
	mov	w0, -1
	b	.L3846
	.p2align 3
.L3728:
	ldr	x20, .LC1091
	ldr	x4, [x20]
	cbz	x4, .L3729
	ldr	w0, [x19, 252]
	mov	w1, 102
	mov	w3, 0
	mov	x2, 0
	blr	x4
	ldr	x1, [x19, 2368]
	cbz	x1, .L3730
.L3731:
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3730:
	ldr	x4, [x20]
	cbz	x4, .L3828
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, 0
	b	.L3847
.L3729:
	cbnz	x1, .L3731
	mov	w0, 0
	b	.L3847
.L3845:
	ldr	x20, .LC1091
	strb	w0, [x19, 9]
	ldr	x4, [x20]
	cbz	x4, .L3726
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L3726:
	ldrb	w0, [x19, 3953]
	cbz	w0, .L3725
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L3725
	ldr	x1, [x19, 2368]
	cbz	x1, .L3727
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
	b	.L3727
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	3
.LC1088:
	.xword	.L3703
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
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x2
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	str	wzr, [x20]
	ldr	x3, .LC1100
	add	x0, x19, 4096
	str	wzr, [x21]
	mov	x2, 1356
	mov	w1, 0
	add	x0, x0, 560
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, [x19, 2368]
	mov	x0, x19
	ldr	w2, [x1, 16]
	str	w2, [x19, 4684]
	ldr	w2, [x1, 28]
	str	w2, [x19, 4680]
	ldr	w1, [x1, 24]
	str	w1, [x19, 4688]
	bl	HEVC_DecSliceSegmentHeader
	cbnz	w0, .L3861
	ldr	w2, [x19, 4692]
	mov	w5, 1888
	ldr	x1, [x19, 2352]
	mov	w3, 12660
	ldr	w4, [x19, 4808]
	ldr	x0, [x19, 2344]
	smaddl	x1, w2, w5, x1
	cmp	w4, 1
	cset	w2, eq
	ldr	w1, [x1, 32]
	str	w2, [x21]
	smaddl	x0, w1, w3, x0
	ldr	x2, [x19, 2392]
	ldr	x1, [x19, 2424]
	ldr	w4, [x0, 184]
	ldr	w3, [x2, 184]
	ldr	w5, [x1, 840]
	cmp	w4, w3
	ldr	w6, [x0, 64]
	cset	w3, ne
	cmp	w5, 1
	ldr	w4, [x0, 68]
	ldp	w5, w2, [x2, 64]
	beq	.L3862
.L3853:
	cmp	w6, w5
	cset	w0, ne
	cmp	w4, w2
	orr	w0, w3, w0
	cset	w1, ne
	orr	w0, w1, w0
	cbz	w0, .L3857
	mov	w1, 1
	mov	w0, 0
	str	w1, [x20]
.L3851:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3861:
	ldr	x1, .LC1102
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1103
	ldr	x4, [x0]
	cbz	x4, .L3856
	add	x2, x29, 64
	ldr	w0, [x19, 252]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3862:
	ldr	w7, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w7
	csel	w0, w0, w7, cs
	str	w0, [x1, 900]
	ldr	x0, [x19, 2392]
	ldr	x7, [x19, 2424]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	ldr	w1, [x7, 900]
	cmp	w0, 8
	ccmp	w1, 8, 0, hi
	bne	.L3863
.L3854:
	mov	w0, 1
	str	w0, [x7, 904]
	str	w0, [x20]
	b	.L3853
	.p2align 3
.L3857:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3856:
	mov	w0, -1
	b	.L3851
	.p2align 3
.L3863:
	cmp	w0, 8
	ccmp	w1, 8, 4, eq
	ble	.L3853
	b	.L3854
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
	cbnz	w0, .L3865
	ldrb	w0, [x19, 3953]
	mov	w20, -1
	cbnz	w0, .L3869
.L3865:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3869:
	ldr	x2, .LC1104
	mov	w0, 0
	ldr	x1, .LC1106
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
.LC1104:
	.xword	.LANCHOR5
	.align	3
.LC1106:
	.xword	.LC1105
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
	ldr	x2, [x19, 9120]
	mov	w0, 0
	cbz	x2, .L3871
	.p2align 2
.L3872:
	ldp	w3, w1, [x2]
	ldr	x2, [x2, 1360]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L3872
.L3871:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
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
	ldr	x20, .LC1107
	mov	x2, 27680
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x19, 6616]
	ldr	x3, [x20, 96]
	blr	x3
	str	x21, [x19, 2424]
	str	xzr, [x19, 2440]
	str	w22, [x19, 6616]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L3884
	mov	w0, 17
	mov	w3, 65
	mov	w2, 200
	mov	w1, 210
	stp	w2, w0, [x19, 152]
	stp	w0, w3, [x19, 160]
	str	w1, [x19, 168]
.L3877:
	ldr	w0, [x21, 584]
	bl	MEM_Phy2Vir
	cbz	x0, .L3885
	ldr	x8, [x19, 2424]
	mov	w22, 12660
	ldr	w2, [x19, 156]
	ldpsw	x6, x5, [x19, 160]
	ldr	w7, [x8, 580]
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
	str	x4, [x19, 2344]
	lsl	w4, w1, 3
	add	w5, w6, w5, lsl 5
	sub	w4, w4, w1
	add	x6, x0, x6, uxtw
	lsl	w4, w4, 1
	str	x6, [x19, 2352]
	ldrsw	x6, [x19, 152]
	sub	w1, w4, w1
	mov	w4, 1368
	add	x7, x0, x7, uxtw
	str	x7, [x19, 2336]
	sxtw	x2, w2
	madd	w4, w4, w6, w5
	add	x5, x0, x5, uxtw
	str	x5, [x19, 2432]
	add	w1, w4, w1, lsl 3
	add	x4, x0, x4, uxtw
	str	x4, [x19, 2416]
	add	x4, x0, x1, uxtw
	str	x4, [x19, 2408]
	add	w3, w1, w3, lsl 3
	ldr	w4, [x8, 588]
	cmp	w3, w4
	bhi	.L3886
	ldr	w0, [x21, 616]
	cbz	w0, .L3887
.L3881:
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
	ldr	x0, [x19, 2416]
	smull	x2, w2, w4
	blr	x3
	ldrsw	x2, [x19, 168]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2408]
	lsl	x2, x2, 3
	blr	x3
	ldp	w5, w4, [x19, 156]
	mov	x1, -132
	mov	w0, 132
	ldr	w2, [x19, 164]
	mov	w8, 1888
	ldr	x9, [x19, 2336]
	mov	x7, -1888
	smaddl	x0, w5, w0, x1
	mov	w3, 12660
	mov	x1, -12660
	ldr	x6, [x19, 2352]
	smaddl	x3, w4, w3, x1
	ldr	x4, [x19, 2344]
	add	x1, x9, x0
	smaddl	x0, w2, w8, x7
	str	x1, [x19, 2384]
	add	x2, x4, x3
	add	x0, x6, x0
	str	x2, [x19, 2392]
	str	x0, [x19, 2400]
	mov	x0, x19
	str	w5, [x1, 4]
	ldr	x1, [x19, 2400]
	ldr	w2, [x19, 160]
	str	w2, [x1, 28]
	ldr	x1, [x19, 2392]
	ldr	w2, [x19, 164]
	str	w2, [x1, 56]
	bl	HEVC_InitScalingOrderTable
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 252]
	beq	.L3888
	mov	w1, -2147483647
	mov	x0, x19
	str	w1, [x19, 212]
	bl	HEVC_InitDecPara
	str	wzr, [x19, 11880]
	mov	w0, 1
	ldr	w2, [x19, 164]
	mov	w1, 9999
	strb	w0, [x19]
	str	w1, [x19, 260]
	mov	w0, 0
	str	w2, [x19, 296]
.L3883:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3887:
	lsl	x0, x2, 7
	ldr	x3, [x20, 96]
	add	x2, x0, x2, lsl 2
	mov	w1, 0
	mov	x0, x7
	blr	x3
	ldr	w2, [x19, 160]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2344]
	smull	x2, w2, w22
	blr	x3
	ldr	w4, [x19, 164]
	mov	w2, 1888
	ldr	x0, [x19, 2352]
	mov	w1, 0
	ldr	x3, [x20, 96]
	smull	x2, w4, w2
	blr	x3
	ldrsw	x6, [x19, 152]
	ldr	x5, [x19, 2432]
	b	.L3881
	.p2align 3
.L3884:
	ldr	w0, [x21, 696]
	str	w0, [x19, 156]
	ldr	w0, [x21, 700]
	str	w0, [x19, 160]
	ldr	w0, [x21, 704]
	str	w0, [x19, 164]
	ldr	w0, [x21, 692]
	str	w0, [x19, 152]
	add	w0, w0, 5
	str	w0, [x19, 168]
	b	.L3877
.L3886:
	ldr	x2, .LC1108
	mov	w0, 0
	ldr	x1, .LC1112
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3883
.L3888:
	ldr	x2, .LC1108
	mov	w0, 0
	ldr	x1, .LC1114
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3883
.L3885:
	ldr	x2, .LC1108
	ldr	x1, .LC1110
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3883
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	3
.LC1107:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1108:
	.xword	.LANCHOR5
	.align	3
.LC1110:
	.xword	.LC1109
	.align	3
.LC1112:
	.xword	.LC1111
	.align	3
.LC1114:
	.xword	.LC1113
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
	cbz	w0, .L3892
	ldrb	w0, [x19, 3953]
	cmp	w0, 1
	beq	.L3892
	add	x1, x19, 12288
	add	x4, x19, 24576
	add	x1, x1, 1152
	add	x4, x4, 3104
	.p2align 2
.L3898:
	ldr	w0, [x1, 48]
	cbnz	w0, .L3893
	cbz	x1, .L3894
	ldr	w3, [x19, 2764]
	cbz	w3, .L3894
	ldr	x0, [x19, 2784]
	cmp	x0, x1
	beq	.L3893
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L3895
	.p2align 3
.L3896:
	ldr	x2, [x0, 2784]
	cmp	x2, x1
	beq	.L3893
.L3895:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L3896
.L3894:
	ldr	w0, [x19, 252]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L3892
	cmn	w0, #1
	beq	.L3917
.L3916:
	mov	w0, 0
.L3918:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3892:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3893:
	add	x1, x1, 712
	cmp	x1, x4
	bne	.L3898
	add	x0, x19, 4096
	add	x2, x29, 44
	add	x1, x29, 40
	add	x0, x0, 1920
	bl	GetQueueImgNum
	mov	x0, x19
	bl	HEVC_PrintFrameStoreState
	ldr	x1, .LC1118
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	w0, [x19, 180]
	ldr	w2, [x19, 2764]
	ldp	w3, w4, [x29, 40]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w4
	cmp	w1, w0
	bge	.L3916
	ldr	x2, .LC1119
	mov	w0, 0
	ldr	x1, .LC1121
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	ret
.L3917:
	ldr	x1, .LC1116
	mov	w0, 1
	bl	dprint_vfmw
	add	x1, x19, 4096
	ldr	w0, [x19, 252]
	add	x1, x1, 1920
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L3918
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	3
.LC1116:
	.xword	.LC1115
	.align	3
.LC1118:
	.xword	.LC1117
	.align	3
.LC1119:
	.xword	.LANCHOR5
	.align	3
.LC1121:
	.xword	.LC1120
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
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 100]
	stp	wzr, wzr, [x29, 92]
	cbz	x20, .L3989
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L3990
	ldr	x2, [x19, 2424]
	ldrb	w0, [x19, 7]
	cmp	w0, 1
	ldr	w0, [x2, 8]
	ubfiz	w0, w0, 16, 3
	str	w0, [x19, 248]
	beq	.L3923
	ldr	w0, [x2, 840]
	cmp	w0, 1
	beq	.L3991
.L3924:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_ReceivePacket
	mov	w20, w0
	ldr	x1, [x19, 2368]
	str	x1, [x19, 2376]
.L3925:
	strb	wzr, [x19, 7]
	mov	w0, 0
	cbz	w20, .L3992
.L3975:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3991:
	ldr	w0, [x2, 888]
	cmp	w0, 1
	bne	.L3924
	ldr	w0, [x19, 320]
	cmp	w0, 1
	bne	.L3924
	ldr	x0, [x19, 2376]
	str	x0, [x19, 2368]
	mov	w0, 0
	strb	wzr, [x19, 7]
	str	wzr, [x19, 320]
	b	.L3975
	.p2align 3
.L3992:
	str	wzr, [x1, 4]
	ldr	x1, [x19, 2368]
	ldr	x0, [x19, 2328]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2328]
	mov	w1, 24
	bl	BsSkip
	ldr	x22, .LC1128
	ldrsw	x0, [x19, 252]
	ldr	x0, [x22, x0, lsl 3]
	ldrsb	w20, [x0, 44]
	cmp	w20, 1
	beq	.L3993
	mov	w21, 2
	mov	w24, 0
	mov	w23, w21
.L3926:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x20, [x19, 2368]
	ldr	x0, [x19, 2328]
	mov	w1, 6
	bl	BsGet
	str	w0, [x20, 16]
	mov	w1, 6
	ldr	x20, [x19, 2368]
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 24]
	ldr	x20, [x19, 2368]
	ldr	w2, [x20, 24]
	cbnz	w2, .L3994
	ldr	x0, [x19, 2328]
	mov	w1, 3
	bl	BsGet
	str	w0, [x20, 28]
	ldr	x20, [x19, 2368]
	ldr	w0, [x20, 28]
	cbnz	w0, .L3995
.L3929:
	ldr	w0, [x20, 16]
	bl	HEVC_IsSliceUnit
	sxtb	w25, w0
	cmp	w25, 1
	beq	.L3996
	str	wzr, [x20, 4]
	add	x0, x19, 2720
	ldr	x1, [x19, 2368]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2328]
	mov	w1, 24
	bl	BsSkip
	cmp	w23, 1
	ccmp	w21, wzr, 0, eq
	ccmp	w24, 1, 4, eq
	beq	.L3945
	ldr	x0, [x19, 2328]
	mov	w1, 16
	bl	BsSkip
.L3945:
	ldr	x0, [x19, 2328]
	mov	w1, 1
	bl	BsGet
	ldr	x20, [x19, 2368]
	ldr	x0, [x19, 2328]
	mov	w1, 6
	bl	BsGet
	str	w0, [x20, 16]
	mov	w1, 6
	ldr	x20, [x19, 2368]
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 3
	ldr	x20, [x19, 2368]
	ldr	x0, [x19, 2328]
	bl	BsGet
	str	w0, [x20, 28]
	ldr	x1, [x19, 2368]
	ldr	w0, [x1, 28]
	cbz	w0, .L3934
	sub	w0, w0, #1
	str	w0, [x1, 28]
.L3934:
	mov	x0, x19
	bl	HEVC_DecOneNal
	cmn	w0, #2
	beq	.L3975
	cbnz	w0, .L3997
	str	wzr, [x19, 4008]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3923:
	ldr	x1, [x19, 2368]
	cmp	x1, xzr
	csetm	w20, eq
	cbz	w20, .L3925
	ldr	x1, .LC1127
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w20
	b	.L3975
	.p2align 3
.L3995:
	sub	w0, w0, #1
	str	w0, [x20, 28]
	ldr	x20, [x19, 2368]
	b	.L3929
	.p2align 3
.L3993:
	ldp	w23, w21, [x0, 152]
	ldr	w3, [x0, 160]
	mov	x0, x19
	mov	w2, w21
	mov	w1, w23
	bl	HEVC_VES_Splitter
	cmp	w0, 2
	beq	.L3950
	cmp	w0, 1
	mov	w24, 0
	bne	.L3975
	b	.L3926
	.p2align 3
.L3994:
	ldr	x1, .LC1130
	mov	w3, 0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	cbz	x1, .L3987
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3987:
	mov	w0, -1
	b	.L3975
	.p2align 3
.L3996:
	add	x2, x29, 108
	add	x1, x29, 104
	mov	x0, x19
	bl	HEVC_InquireSliceProperty
	cbnz	w0, .L3931
	ldr	w20, [x29, 104]
	cmp	w20, 1
	beq	.L3998
.L3932:
	ldr	w20, [x29, 108]
	cmp	w20, 1
	bne	.L3934
	ldr	x0, [x19, 2368]
	ldr	w0, [x0, 24]
	add	x0, x19, x0
	ldrb	w21, [x0, 4]
	mov	x0, x19
	cmp	w21, 1
	beq	.L3999
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L4000
.L3937:
	ldr	w0, [x19, 252]
	bl	FSP_GetFspType
	cbnz	w0, .L3934
	ldr	w0, [x19, 252]
	add	x3, x29, 100
	add	x2, x29, 96
	add	x1, x29, 92
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 2424]
	ldr	w0, [x0, 724]
	cmp	w0, 1
	bne	.L3934
	ldr	w1, [x29, 100]
	cmp	w1, wzr
	bgt	.L3940
	ldr	w2, [x29, 96]
	cmp	w2, 32
	bgt	.L3940
	ldr	x2, [x19, 2440]
	cbnz	x2, .L3940
	ldr	w2, [x29, 108]
	cbz	w2, .L3934
	ldr	w3, [x19, 240]
	cbz	w3, .L3934
	ldr	x3, [x19, 2392]
	ldr	w4, [x19, 312]
	ldr	w6, [x3, 68]
	cmp	w6, w4
	beq	.L3934
	ldr	w5, [x3, 64]
	cmp	w1, wzr
	ldr	w3, [x19, 316]
	ccmp	w5, w3, 4, eq
	beq	.L3934
	ldr	x1, .LC1136
	bl	dprint_vfmw
	ldr	x0, [x19, 2392]
	ldr	x1, .LC1137
	ldr	w2, [x0, 68]
	str	w2, [x19, 312]
	ldr	x4, [x1]
	ldr	w0, [x0, 64]
	str	w0, [x19, 316]
	cbz	x4, .L3934
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L3934
	.p2align 3
.L3990:
	ldr	x1, .LC1125
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3975
	.p2align 3
.L3950:
	mov	w24, w20
	b	.L3926
	.p2align 3
.L3931:
	ldr	x1, .LC1139
	mov	w0, w25
	bl	dprint_vfmw
	ldr	x1, [x19, 2368]
	cbz	x1, .L3942
	ldr	w0, [x19, 252]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2368]
.L3942:
	ldr	x0, .LC1137
	ldr	x4, [x0]
	cbz	x4, .L3943
	ldr	w0, [x19, 252]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3943:
	ldrsw	x0, [x19, 252]
	ldr	x0, [x22, x0, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	bne	.L3987
	ldr	w1, [x0, 156]
	cbnz	w1, .L3987
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L3987
	add	x0, x19, 8192
	ldrb	w1, [x0, 3632]
	cbnz	w1, .L3987
	ldr	x3, .LC1140
	mov	x2, 56
	add	x0, x0, 3632
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 3332]
	add	x1, x19, 3072
	mov	w0, -1
	stp	xzr, xzr, [x1, 280]
	stp	xzr, xzr, [x1, 296]
	b	.L3975
.L3998:
	ldr	w1, [x19, 204]
	cbnz	w1, .L3933
	ldrb	w1, [x19, 3953]
	cbz	w1, .L3932
	ldr	x2, .LC1131
	ldr	x1, .LC1132
	add	x2, x2, 496
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L3932
.L3933:
	ldr	x3, [x19, 2368]
	mov	w2, 13
	ldr	x1, .LC1131
	add	x0, x19, 2720
	str	wzr, [x3, 4]
	add	x1, x1, 584
	bl	BsInit
	ldr	x0, [x19, 2328]
	mov	w1, 40
	bl	BsSkip
	ldr	x1, [x19, 2368]
	mov	w2, 48
	mov	x0, x19
	str	w2, [x1, 16]
	strb	w20, [x19, 8]
	bl	HEVC_DecOneNal
	strb	w20, [x19, 7]
	ldr	w1, [x19, 280]
	mov	w0, -2
	add	w1, w1, 1
	str	w1, [x19, 280]
	b	.L3975
.L3989:
	ldr	x1, .LC1123
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3975
.L3999:
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L3937
	ldr	x2, .LC1131
	mov	w0, w21
	ldr	x1, .LC1133
	add	x2, x2, 560
	bl	dprint_vfmw
	b	.L3937
.L3997:
	ldr	x1, .LC1142
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3975
.L4000:
	ldr	x2, .LC1131
	mov	w0, w20
	ldr	x1, .LC1134
	add	x2, x2, 560
	bl	dprint_vfmw
	b	.L3937
.L3940:
	mov	w1, 1
	mov	w0, -2
	strb	w1, [x19, 7]
	b	.L3975
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	3
.LC1123:
	.xword	.LC1122
	.align	3
.LC1125:
	.xword	.LC1124
	.align	3
.LC1127:
	.xword	.LC1126
	.align	3
.LC1128:
	.xword	s_pstVfmwChan
	.align	3
.LC1130:
	.xword	.LC1129
	.align	3
.LC1131:
	.xword	.LANCHOR5
	.align	3
.LC1132:
	.xword	.LC1105
	.align	3
.LC1133:
	.xword	.LC1067
	.align	3
.LC1134:
	.xword	.LC1065
	.align	3
.LC1136:
	.xword	.LC1135
	.align	3
.LC1137:
	.xword	g_event_report
	.align	3
.LC1139:
	.xword	.LC1138
	.align	3
.LC1140:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1142:
	.xword	.LC1141
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
	mov	x23, x3
	mov	w22, w4
	mov	w20, w5
	bl	_mcount
	ldr	x1, [x19, 2424]
	ldr	x0, [x19, 4016]
	ldr	w21, [x1, 636]
	str	w24, [x19, 3992]
	cbz	x0, .L4002
	add	x1, x19, 4096
	ldrb	w2, [x1, 2533]
	strb	w2, [x0, 3]
	ldrb	w1, [x1, 2528]
	strb	w1, [x0, 4]
.L4002:
	cbz	w22, .L4003
	ldr	x5, .LC1143
	sbfiz	x20, x20, 6, 32
	add	x20, x5, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L4028
	cmp	w0, 1
	beq	.L4003
.L4006:
	mov	x1, x23
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbnz	w0, .L4029
	cmp	w21, 1
	beq	.L4030
.L4008:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x19, 172]
.L4005:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4029:
	ldr	x1, .LC1145
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
.L4003:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	b	.L4006
	.p2align 3
.L4030:
	ldr	x22, [x19, 2440]
	ldr	w0, [x22, 1292]
	add	x0, x22, x0, lsl 2
	ldr	w23, [x0, 1476]
	mov	w0, w23
	bl	MEM_Phy2Vir
	mov	x20, x0
	ldr	w2, [x22, 76]
	ldp	w3, w5, [x22, 192]
	lsl	w21, w21, w2
	ldr	x1, .LC1146
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
	cbz	w21, .L4019
	mov	w5, 0
	mov	w8, 0
	mov	w7, 2147483647
	mov	w4, 0
	mov	w2, 0
	b	.L4016
	.p2align 3
.L4032:
	csel	w7, w7, w0, le
.L4015:
	add	w2, w2, 1
	add	w5, w5, w0
	cmp	w21, w2
	beq	.L4031
.L4016:
	ubfiz	x1, x2, 4, 28
	add	x1, x20, x1
	ldrsh	w3, [x1, 4]
	neg	w0, w3
	and	w6, w3, 32767
	tbz	x3, 15, .L4011
	and	w6, w0, 32767
.L4011:
	ldrsh	w1, [x1, 6]
	neg	w3, w1
	and	w0, w1, 32767
	tbz	x1, 15, .L4013
	and	w0, w3, 32767
.L4013:
	add	w0, w6, w0
	cmp	w4, w0
	csel	w4, w4, w0, ge
	cmp	w7, w0
	cbnz	w0, .L4032
	add	w8, w8, 1
	b	.L4015
	.p2align 3
.L4028:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	w0, 0
	b	.L4005
	.p2align 3
.L4031:
	lsl	w0, w8, 2
	sub	w0, w0, w8
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w8, w0, w8
.L4009:
	udiv	w8, w8, w21
	ldr	x0, [x19, 4016]
	cmp	w8, 100
	csel	w7, w7, wzr, ne
	udiv	w5, w5, w21
	cbz	x0, .L4018
	str	w4, [x0, 324]
	ldr	x0, [x19, 4016]
	str	w7, [x0, 328]
	ldr	x0, [x19, 4016]
	str	w5, [x0, 332]
	ldr	x0, [x19, 4016]
	str	w8, [x0, 336]
	str	w4, [x19, 4268]
	str	w7, [x19, 4272]
	str	w5, [x19, 4276]
	str	w8, [x19, 4280]
	b	.L4008
.L4019:
	mov	w8, 0
	mov	w5, 0
	mov	w7, 2147483647
	mov	w4, 0
	b	.L4009
.L4018:
	ldr	x1, .LC1148
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4008
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	3
.LC1143:
	.xword	g_VdmDrvParam
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
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2392]
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
	ldr	x0, [x19, 2392]
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
	ldr	w0, [x19, 2764]
	cbz	w0, .L4040
	ldr	x0, .LC1149
	mov	w21, 1
	ldr	x23, .LC1150
	add	x22, x0, 600
	.p2align 2
.L4036:
	add	x2, x29, 72
	add	x1, x29, 76
	mov	x0, x19
	bl	HEVC_GetMinPOC
	ldr	w2, [x29, 72]
	mov	x0, x19
	add	x1, x19, x2, uxtw 3
	ldr	x20, [x1, 2784]
	mov	x1, x20
	cbz	x20, .L4037
	ldrb	w3, [x20, 2]
	cmp	w3, 1
	beq	.L4037
	strb	w21, [x20, 2]
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L4051
.L4050:
	ldr	w2, [x29, 72]
.L4037:
	mov	w1, w2
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	ldr	w1, [x29, 72]
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w0, [x19, 2764]
	cbnz	w0, .L4036
.L4040:
	add	x0, x19, 4096
	add	x0, x0, 1920
	bl	GetVoLastImageID
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4051:
	add	x1, x20, 28
	mov	x0, x19
	bl	HEVC_OutputFrame.isra.9
	cbz	w0, .L4050
	mov	x1, x23
	mov	x2, x22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	b	.L4050
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	3
.LC1149:
	.xword	.LANCHOR5
	.align	3
.LC1150:
	.xword	.LC923
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	s_TmpParam
	.global	g_RpuStartCode
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.12834, %object
	.size	__func__.12834, 17
__func__.12834:
	.string	"HEVC_OutputFrame"
	.zero	7
	.type	SarTable.11507, %object
	.size	SarTable.11507, 136
SarTable.11507:
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
	.type	__func__.11665, %object
	.size	__func__.11665, 18
__func__.11665:
	.string	"HEVC_CalcTileInfo"
	.zero	6
	.type	__func__.12145, %object
	.size	__func__.12145, 27
__func__.12145:
	.string	"HEVC_GetUnRefPicWithMinPoc"
	.zero	5
	.type	__func__.12154, %object
	.size	__func__.12154, 21
__func__.12154:
	.string	"HEVC_IncreaseDPBSize"
	.zero	3
	.type	__func__.12402, %object
	.size	__func__.12402, 17
__func__.12402:
	.string	"HEVC_WritePicMsg"
	.zero	7
	.type	__func__.12431, %object
	.size	__func__.12431, 16
__func__.12431:
	.string	"HEVC_CheckListX"
	.type	__func__.12595, %object
	.size	__func__.12595, 16
__func__.12595:
	.string	"HEVC_RepairList"
	.type	__func__.12662, %object
	.size	__func__.12662, 16
__func__.12662:
	.string	"HEVC_ArrangeMem"
	.type	__func__.12735, %object
	.size	__func__.12735, 20
__func__.12735:
	.string	"HEVC_RemoveApcStore"
	.zero	4
	.type	__func__.13001, %object
	.size	__func__.13001, 21
__func__.13001:
	.string	"HEVC_CheckFrameStore"
	.zero	3
	.type	__func__.13069, %object
	.size	__func__.13069, 19
__func__.13069:
	.string	"HEVC_GetSLHDR1Info"
	.zero	5
	.type	__func__.13196, %object
	.size	__func__.13196, 14
__func__.13196:
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
	.type	__func__.13511, %object
	.size	__func__.13511, 16
__func__.13511:
	.string	"HEVC_ReleaseNAL"
	.type	__func__.12694, %object
	.size	__func__.12694, 20
__func__.12694:
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
	.type	__func__.12255, %object
	.size	__func__.12255, 27
__func__.12255:
	.string	"HEVC_DecSliceSegmentHeader"
	.zero	5
	.type	__func__.12673, %object
	.size	__func__.12673, 13
__func__.12673:
	.string	"HEVC_InitDPB"
	.zero	3
	.type	__func__.12841, %object
	.size	__func__.12841, 19
__func__.12841:
	.string	"HEVC_OutputCurrPic"
	.zero	5
	.type	__func__.12846, %object
	.size	__func__.12846, 23
__func__.12846:
	.string	"HEVC_FirstFrameFastOut"
	.zero	1
	.type	__func__.12993, %object
	.size	__func__.12993, 19
__func__.12993:
	.string	"HEVC_OutputFrmToVO"
	.zero	5
	.type	__func__.12955, %object
	.size	__func__.12955, 22
__func__.12955:
	.string	"HEVC_OutputFrmFromDPB"
	.zero	2
	.type	__func__.12160, %object
	.size	__func__.12160, 30
__func__.12160:
	.string	"HEVC_OutputUnRefPicWithMinPoc"
	.zero	2
	.type	__func__.12968, %object
	.size	__func__.12968, 27
__func__.12968:
	.string	"HEVC_FlushOutputFrmFromDPB"
	.zero	5
	.type	__func__.13574, %object
	.size	__func__.13574, 14
__func__.13574:
	.string	"HEVC_ClearDPB"
	.zero	2
	.type	__func__.12165, %object
	.size	__func__.12165, 23
__func__.12165:
	.string	"HEVC_RecoverDPBProcess"
	.zero	1
	.type	__func__.12932, %object
	.size	__func__.12932, 20
__func__.12932:
	.string	"HEVC_InsertFrmInDPB"
	.zero	4
	.type	__func__.12851, %object
	.size	__func__.12851, 22
__func__.12851:
	.string	"HEVC_SimpleDPBProcess"
	.zero	2
	.type	__func__.12856, %object
	.size	__func__.12856, 21
__func__.12856:
	.string	"HEVC_DecOrderProcess"
	.zero	3
	.type	__func__.12861, %object
	.size	__func__.12861, 22
__func__.12861:
	.string	"HEVC_DispOrderProcess"
	.zero	2
	.type	__func__.12875, %object
	.size	__func__.12875, 19
__func__.12875:
	.string	"HEVC_StorePicInDPB"
	.zero	5
	.type	__func__.12517, %object
	.size	__func__.12517, 12
__func__.12517:
	.string	"HEVC_DecVDM"
	.zero	4
	.type	__func__.11395, %object
	.size	__func__.11395, 18
__func__.11395:
	.string	"HEVC_VES_Splitter"
	.zero	6
	.type	__func__.12195, %object
	.size	__func__.12195, 14
__func__.12195:
	.string	"HEVC_DecSlice"
	.zero	2
	.type	__func__.13654, %object
	.size	__func__.13654, 20
__func__.13654:
	.string	"HEVC_HaveSliceToDec"
	.zero	4
	.type	__func__.13676, %object
	.size	__func__.13676, 13
__func__.13676:
	.string	"HEVCDEC_Init"
	.zero	3
	.type	__func__.13690, %object
	.size	__func__.13690, 23
__func__.13690:
	.string	"HEVCDEC_GetImageBuffer"
	.zero	1
	.type	__func__.13705, %object
	.size	__func__.13705, 21
__func__.13705:
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
	.type	__func__.13754, %object
	.size	__func__.13754, 21
__func__.13754:
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
.LC1105:
	ASCII(.string	"%s last frame fs unrelease, fix it!\n" )
	.zero	3
.LC1109:
	ASCII(.string	"%s: Get context addr failed!\n" )
	.zero	2
.LC1111:
	ASCII(.string	"%s FATAL: MemOffset %d > ContextMemSize %d.\n" )
	.zero	3
.LC1113:
	ASCII(.string	"%s: VCTRL_GetChanIDByCtx() return -1!\n" )
	.zero	1
.LC1115:
	ASCII(.string	"Fs leak, clear dpb fs not in vo queue.\n" )
.LC1117:
	ASCII(.string	"No frame store available!\n" )
	.zero	5
.LC1120:
	ASCII(.string	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak, ClearAll!\n" )
.LC1122:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pPacket!\n" )
	.zero	1
.LC1124:
	ASCII(.string	"HevcCtx not init!\n" )
	.zero	5
.LC1126:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\n" )
	.zero	6
.LC1129:
	ASCII(.string	"nal_layer_id out %d of range[0,1].\n" )
	.zero	4
.LC1135:
	ASCII(.string	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	4
.LC1138:
	ASCII(.string	"HEVC_InquireSliceProperty error.\n" )
	.zero	6
.LC1141:
	ASCII(.string	"HEVC_DecOneNal ERR\n" )
	.zero	4
.LC1144:
	ASCII(.string	"HEVC_StorePicInDPB failed, ret = %d\n" )
	.zero	3
.LC1147:
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
