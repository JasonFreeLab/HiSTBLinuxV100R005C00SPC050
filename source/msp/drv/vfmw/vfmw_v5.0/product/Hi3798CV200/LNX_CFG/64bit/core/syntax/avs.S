#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"avs.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	avs_f_v
	.type	avs_f_v, %function
avs_f_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	mov	w19, w0
	ldr	x1, .LC1
	mov	w4, w20
	mov	w3, w0
	mov	x2, x21
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	avs_f_v, .-avs_f_v
	.align	3
.LC1:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	avs_u_v
	.type	avs_u_v, %function
avs_u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	mov	x2, x21
	mov	w1, w20
	mov	x0, x19
	bl	avs_f_v
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	avs_u_v, .-avs_u_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	avs_ue_v
	.type	avs_ue_v, %function
avs_ue_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	mov	w1, 32
	mov	x0, x21
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	mov	w19, w0
	bls	.L7
	mov	w20, -1
	mov	w4, 32
.L4:
	ldr	x1, .LC2
	mov	w3, w20
	mov	x2, x22
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L7:
	mov	w1, w0
	mov	x0, x21
	add	w23, w19, 1
	bl	BsSkip
	mov	w1, w23
	mov	x0, x21
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w23
	mov	x0, x21
	bl	BsSkip
	lsl	w4, w19, 1
	add	w4, w4, 1
	b	.L4
	.size	avs_ue_v, .-avs_ue_v
	.align	3
.LC2:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	avs_se_v
	.type	avs_se_v, %function
avs_se_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	mov	w19, w0
	bls	.L13
	mov	w20, 2147483647
	mov	w4, 32
.L9:
	ldr	x1, .LC3
	mov	w3, w20
	mov	x2, x21
	mov	w0, 7
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L13:
	mov	w1, w0
	mov	x0, x20
	add	w22, w19, 1
	bl	BsSkip
	mov	w1, w22
	mov	x0, x20
	bl	BsShow
	sub	w0, w0, #1
	and	w1, w0, 1
	asr	w3, w0, 1
	cmp	w1, wzr
	mov	x0, x20
	mov	w1, w22
	neg	w20, w3
	csinc	w20, w20, w3, eq
	bl	BsSkip
	lsl	w4, w19, 1
	add	w4, w4, 1
	b	.L9
	.size	avs_se_v, .-avs_se_v
	.align	3
.LC3:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_next_start_code
	.type	AVS_next_start_code, %function
AVS_next_start_code:
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
	bgt	.L21
	b	.L18
	.p2align 3
.L24:
	bl	BsSkip
	cmp	w19, w21
	beq	.L18
.L21:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L24
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L18:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_next_start_code, .-AVS_next_start_code
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_sequence_header
	.type	AVS_sequence_header, %function
AVS_sequence_header:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	add	x21, x23, 12288
	mov	x19, x1
	bl	_mcount
	ldr	x2, .LC5
	mov	w1, 32
	ldr	x20, [x21, 3224]
	ldr	w4, [x21, 2828]
	mov	x0, x20
	and	w4, w4, -65537
	str	w4, [x21, 2828]
	bl	avs_f_v
	ldr	x2, .LC7
	mov	w1, 8
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 16]
	ldr	x2, .LC9
	mov	w1, 8
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 20]
	ldr	x2, .LC11
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 15]
	ldr	x2, .LC13
	mov	w1, 14
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 24]
	ldr	x2, .LC15
	mov	w1, 14
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 28]
	ldr	x2, .LC17
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 11]
	ldr	x2, .LC19
	mov	w1, 3
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 12]
	ldr	x2, .LC21
	mov	w1, 4
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 13]
	ldr	x2, .LC23
	mov	w1, 4
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 14]
	ldr	x2, .LC25
	mov	w1, 18
	mov	x0, x20
	bl	avs_f_v
	ldr	x22, .LC27
	mov	w1, 1
	str	w0, [x19, 32]
	mov	x2, x22
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 10]
	ldr	x2, .LC29
	mov	w1, 12
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 36]
	ldr	x2, .LC31
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 9]
	mov	x2, x22
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 10]
	ldr	x2, .LC33
	mov	w1, 18
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 40]
	ldr	x2, .LC35
	mov	w1, 3
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 8]
	ldrb	w1, [x19, 14]
	cmp	w1, 15
	bhi	.L26
	ldr	x0, .LC36
	ldr	w2, [x19, 24]
	ldr	w0, [x0, w1, sxtw 2]
	str	w0, [x19, 44]
	ldr	w1, [x21, 2868]
	cmp	w2, w1
	beq	.L34
.L28:
	ldr	x0, .LC37
	mov	w2, 1
	str	w2, [x21, 2840]
	ldr	x4, [x0]
	cbz	x4, .L29
	ldp	w3, w2, [x19, 24]
	ldr	w5, [x21, 2872]
	ldr	w0, [x23, 4]
	strh	w1, [x29, 72]
	mov	w1, 2
	strh	w3, [x29, 76]
	mov	w3, 8
	strh	w2, [x29, 78]
	add	x2, x29, 72
	strh	w5, [x29, 74]
	blr	x4
.L29:
	mov	x1, x19
	mov	x2, 376
	add	x0, x21, 2844
	bl	memcpy
	ldr	w1, [x21, 2828]
	mov	w0, 1
	ldr	w2, [x21, 2836]
	str	w0, [x21, 2832]
	orr	w1, w1, 65536
	add	w2, w2, w0
	str	w1, [x21, 2828]
	str	w2, [x21, 2836]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L26:
	mov	w0, -1
	str	w0, [x19, 44]
	ldr	w2, [x19, 24]
	ldr	w1, [x21, 2868]
	cmp	w2, w1
	bne	.L28
.L34:
	ldr	w2, [x19, 28]
	ldr	w0, [x21, 2872]
	cmp	w2, w0
	bne	.L28
	b	.L29
	.size	AVS_sequence_header, .-AVS_sequence_header
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
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
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC36:
	.xword	.LANCHOR0
	.align	3
.LC37:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_i_picture_header
	.type	AVS_i_picture_header, %function
AVS_i_picture_header:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x3, .LC40
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 80
	ldr	x20, [x21, 568]
	ldr	x3, [x3, 96]
	blr	x3
	ldr	w3, [x21, 172]
	mov	w1, 32
	ldr	x2, .LC42
	mov	x0, x20
	and	w3, w3, -262145
	str	w3, [x21, 172]
	bl	avs_f_v
	ldr	x2, .LC44
	mov	w1, 16
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 96]
	ldr	w1, [x19, 16]
	ldr	x22, .LC45
	cmp	w1, 72
	beq	.L69
	ldr	x2, .LC49
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 90]
	beq	.L70
.L37:
	mov	x2, x22
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 108]
	ldr	x2, .LC53
	mov	w1, 8
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 112]
	ldrb	w1, [x19, 9]
	cmp	w1, 1
	beq	.L71
.L38:
	ldr	x2, .LC57
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	ldrb	w1, [x19, 15]
	strb	w0, [x19, 80]
	cmp	w1, 1
	beq	.L72
	cbz	w0, .L73
.L40:
	mov	w0, 1
	strb	w0, [x19, 81]
.L41:
	ldr	x2, .LC61
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 82]
	ldr	x2, .LC63
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 83]
	ldr	x2, .LC65
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 84]
	ldr	x2, .LC67
	mov	w1, 6
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 85]
	ldrh	w1, [x19, 80]
	cbz	w1, .L74
.L42:
	ldr	x2, .LC70
	mov	w1, 4
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 87]
	ldr	x2, .LC72
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	stp	wzr, wzr, [x19, 120]
	strb	w0, [x19, 88]
	cbz	w0, .L75
.L44:
	ldr	w0, [x19, 16]
	cmp	w0, 72
	beq	.L76
.L46:
	str	wzr, [x19, 348]
	mov	w0, 1
	strb	w0, [x19, 93]
	ldr	w0, [x21, 172]
	orr	w0, w0, 262144
	str	w0, [x21, 172]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L73:
	ldr	x2, .LC59
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 81]
	b	.L41
	.p2align 3
.L75:
	ldr	x2, .LC74
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	strb	w0, [x19, 89]
	cbz	w0, .L44
	ldr	x1, .LC76
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 120]
	ldr	x1, .LC78
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 124]
	b	.L44
	.p2align 3
.L74:
	ldr	x2, .LC69
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 86]
	b	.L42
	.p2align 3
.L72:
	strb	w1, [x19, 80]
	b	.L40
	.p2align 3
.L76:
	ldr	x2, .LC80
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 128]
	cbnz	w0, .L47
.L55:
	ldr	x2, .LC82
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 332]
	b	.L46
	.p2align 3
.L69:
	mov	w1, 1
	mov	x2, x22
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 108]
	ldr	x2, .LC47
	mov	w1, 7
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 100]
	ldr	w1, [x19, 96]
	mov	w2, 1
	strb	w2, [x19]
	ldr	x2, .LC49
	orr	w0, w0, w1, lsl 7
	mov	w1, 1
	str	w0, [x19, 96]
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 90]
	bne	.L37
	.p2align 2
.L70:
	ldr	x2, .LC51
	mov	w1, 24
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 104]
	b	.L37
	.p2align 3
.L71:
	ldr	x1, .LC55
	mov	x0, x20
	bl	avs_ue_v
	str	w0, [x19, 116]
	b	.L38
	.p2align 3
.L47:
	ldr	x2, .LC84
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 132]
	ldr	x2, .LC86
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 136]
	cbz	w0, .L77
.L48:
	ldr	x2, .LC92
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 148]
	ldr	x2, .LC94
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 152]
	ldr	w1, [x19, 148]
	cmp	w1, 1
	beq	.L49
	ldr	w0, [x19, 132]
	cmp	w0, wzr
	ccmp	w1, 3, 0, eq
	beq	.L49
	cmp	w1, 2
	add	x22, x19, 180
	bne	.L55
.L54:
	ldr	x23, .LC98
	add	x24, x19, 204
	.p2align 2
.L53:
	mov	x1, x23
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x22], 4
	cmp	x22, x24
	bne	.L53
	b	.L55
	.p2align 3
.L77:
	ldr	x1, .LC88
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 140]
	ldr	x1, .LC90
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 144]
	b	.L48
	.p2align 3
.L49:
	ldr	x24, .LC96
	add	x23, x19, 156
	add	x22, x19, 180
	.p2align 2
.L51:
	mov	x1, x24
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x23], 4
	cmp	x23, x22
	bne	.L51
	ldr	w0, [x19, 148]
	cmp	w0, 2
	beq	.L54
	ldr	w1, [x19, 132]
	cmp	w1, wzr
	ccmp	w0, 3, 0, eq
	beq	.L54
	b	.L55
	.size	AVS_i_picture_header, .-AVS_i_picture_header
	.align	3
.LC40:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	.LC26
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
.LC53:
	.xword	.LC52
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
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
.LC70:
	.xword	.LC34
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC84:
	.xword	.LC83
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC98:
	.xword	.LC97
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_pb_picture_header
	.type	AVS_pb_picture_header, %function
AVS_pb_picture_header:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x3, .LC99
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 80
	ldr	x20, [x21, 568]
	ldr	x3, [x3, 96]
	blr	x3
	ldr	w3, [x21, 172]
	mov	w1, 32
	ldr	x2, .LC101
	mov	x0, x20
	and	w3, w3, -262145
	str	w3, [x21, 172]
	bl	avs_f_v
	ldr	x2, .LC102
	mov	w1, 16
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 96]
	ldr	w1, [x19, 16]
	cmp	w1, 72
	beq	.L123
.L79:
	ldr	x2, .LC106
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 91]
	ldr	x2, .LC107
	mov	w1, 8
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 112]
	ldrb	w1, [x19, 9]
	cmp	w1, 1
	beq	.L124
.L80:
	ldr	x2, .LC109
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	strb	w0, [x19, 80]
	cbz	w0, .L125
	mov	w0, 1
	strb	w0, [x19, 81]
.L82:
	ldr	x2, .LC113
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 82]
	ldr	x2, .LC114
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 83]
	ldr	x2, .LC115
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 84]
	ldr	x2, .LC116
	mov	w1, 6
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 85]
	ldrb	w1, [x19, 91]
	cmp	w1, 2
	beq	.L126
.L83:
	ldr	x2, .LC118
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 93]
.L85:
	ldr	x2, .LC120
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	wzr, [x19, 340]
	ldrb	w1, [x19, 91]
	strb	w0, [x19, 94]
	cmp	w1, 2
	str	wzr, [x19, 344]
	beq	.L127
	ldr	x2, .LC124
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 340]
.L87:
	ldrb	w0, [x19, 81]
	cmp	w0, 1
	beq	.L88
	ldr	w0, [x19, 16]
	cmp	w0, 72
	beq	.L89
.L88:
	str	wzr, [x19, 340]
	str	wzr, [x19, 344]
.L89:
	ldr	x2, .LC125
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 87]
	ldr	x2, .LC126
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 86]
	ldr	x2, .LC127
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	stp	wzr, wzr, [x19, 120]
	strb	w0, [x19, 88]
	cbz	w0, .L128
.L91:
	ldr	w0, [x19, 16]
	cmp	w0, 72
	beq	.L129
.L93:
	ldrb	w0, [x19, 91]
	cmp	w0, 1
	beq	.L122
	mov	w0, 2
.L122:
	str	w0, [x19, 348]
	ldr	w0, [x21, 172]
	orr	w0, w0, 262144
	str	w0, [x21, 172]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L126:
	ldrb	w0, [x19, 81]
	cmp	w0, 1
	bne	.L83
	strb	w0, [x19, 93]
	b	.L85
	.p2align 3
.L125:
	ldr	x2, .LC110
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	strb	w0, [x19, 81]
	cbnz	w0, .L82
	ldr	x2, .LC112
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	strb	w0, [x19, 92]
	b	.L82
	.p2align 3
.L128:
	ldr	x2, .LC128
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	uxtb	w0, w0
	strb	w0, [x19, 89]
	cbz	w0, .L91
	ldr	x1, .LC129
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 120]
	ldr	x1, .LC130
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 124]
	b	.L91
	.p2align 3
.L127:
	ldr	x2, .LC122
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 344]
	b	.L87
	.p2align 3
.L129:
	ldr	x2, .LC131
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	cmp	w0, 1
	str	w0, [x19, 128]
	mov	w22, w0
	beq	.L94
.L102:
	ldr	x2, .LC132
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 332]
	b	.L93
	.p2align 3
.L123:
	ldr	x2, .LC103
	mov	w1, 1
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 108]
	ldr	x2, .LC104
	mov	w1, 7
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 100]
	ldr	w1, [x19, 96]
	mov	w2, 1
	strb	w2, [x19]
	orr	w0, w0, w1, lsl 7
	str	w0, [x19, 96]
	b	.L79
	.p2align 3
.L124:
	ldr	x1, .LC108
	mov	x0, x20
	bl	avs_ue_v
	str	w0, [x19, 116]
	b	.L80
	.p2align 3
.L94:
	ldr	x2, .LC133
	mov	w1, w0
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 132]
	ldr	x2, .LC134
	mov	w1, w22
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 136]
	cbz	w0, .L130
.L95:
	ldr	x2, .LC137
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 148]
	ldr	x2, .LC138
	mov	w1, 2
	mov	x0, x20
	bl	avs_f_v
	str	w0, [x19, 152]
	ldr	w1, [x19, 148]
	cmp	w1, 1
	beq	.L96
	ldr	w0, [x19, 132]
	cmp	w0, wzr
	ccmp	w1, 3, 0, eq
	beq	.L96
	cmp	w1, 2
	add	x22, x19, 180
	bne	.L102
.L101:
	ldr	x23, .LC140
	add	x24, x19, 204
	.p2align 2
.L100:
	mov	x1, x23
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x22], 4
	cmp	x22, x24
	bne	.L100
	b	.L102
.L96:
	ldr	x24, .LC139
	add	x23, x19, 156
	add	x22, x19, 180
	.p2align 2
.L98:
	mov	x1, x24
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x23], 4
	cmp	x23, x22
	bne	.L98
	ldr	w0, [x19, 148]
	cmp	w0, 2
	beq	.L101
	ldr	w1, [x19, 132]
	cmp	w1, wzr
	ccmp	w0, 3, 0, eq
	beq	.L101
	b	.L102
.L130:
	ldr	x1, .LC135
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 140]
	ldr	x1, .LC136
	mov	x0, x20
	bl	avs_se_v
	str	w0, [x19, 144]
	b	.L95
	.size	AVS_pb_picture_header, .-AVS_pb_picture_header
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC102:
	.xword	.LC43
	.align	3
.LC103:
	.xword	.LC26
	.align	3
.LC104:
	.xword	.LC46
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC107:
	.xword	.LC52
	.align	3
.LC108:
	.xword	.LC54
	.align	3
.LC109:
	.xword	.LC56
	.align	3
.LC110:
	.xword	.LC58
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC113:
	.xword	.LC60
	.align	3
.LC114:
	.xword	.LC62
	.align	3
.LC115:
	.xword	.LC64
	.align	3
.LC116:
	.xword	.LC66
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC125:
	.xword	.LC34
	.align	3
.LC126:
	.xword	.LC68
	.align	3
.LC127:
	.xword	.LC71
	.align	3
.LC128:
	.xword	.LC73
	.align	3
.LC129:
	.xword	.LC75
	.align	3
.LC130:
	.xword	.LC77
	.align	3
.LC131:
	.xword	.LC79
	.align	3
.LC132:
	.xword	.LC81
	.align	3
.LC133:
	.xword	.LC83
	.align	3
.LC134:
	.xword	.LC85
	.align	3
.LC135:
	.xword	.LC87
	.align	3
.LC136:
	.xword	.LC89
	.align	3
.LC137:
	.xword	.LC91
	.align	3
.LC138:
	.xword	.LC93
	.align	3
.LC139:
	.xword	.LC95
	.align	3
.LC140:
	.xword	.LC97
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_user_data
	.type	AVS_user_data, %function
AVS_user_data:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 12288
	mov	w22, w1
	add	x20, x21, 2656
	bl	_mcount
	ldr	x2, .LC142
	mov	w1, 32
	ldr	x0, [x20, 568]
	bl	avs_f_v
	ldr	w0, [x20, 172]
	orr	w0, w0, 1048576
	str	w0, [x20, 172]
	cbnz	w22, .L132
	ldr	x1, [x20, 872]
	cbz	x1, .L133
	ldr	w0, [x19, 4]
	bl	FreeUsdByDec
	str	xzr, [x20, 872]
.L133:
	ldr	w0, [x19, 4]
	bl	GetUsd
	str	x0, [x21, 3528]
	add	x1, x21, 2656
	cbz	x0, .L143
	ldr	x3, [x19, 16]
	mov	w2, 10
	add	x20, x19, 16384
	ldr	x3, [x3, 56]
	str	x3, [x0, 1056]
	ldr	x0, [x1, 872]
	str	w2, [x0, 1040]
	ldr	x0, [x1, 872]
	ldr	w2, [x1, 180]
	str	w2, [x0, 1044]
	ldr	x2, [x1, 872]
	ldr	w0, [x20, 512]
	sub	w0, w0, #4
	str	w0, [x2, 1052]
	ldr	x0, [x1, 872]
	ldr	w2, [x0, 1052]
	cmp	w2, 1024
	ble	.L136
	mov	w2, 1024
	str	w2, [x0, 1052]
	ldr	x0, [x1, 872]
	ldr	w2, [x0, 1052]
.L136:
	ldr	x22, .LC143
	sxtw	x2, w2
	ldr	x1, [x19, 16880]
	ldr	x3, [x22, 104]
	add	x1, x1, 4
	blr	x3
	ldrb	w0, [x20, 505]
	cbnz	w0, .L138
	ldr	x2, [x21, 3528]
	ldr	w0, [x20, 592]
	ldr	w3, [x2, 1052]
	add	w0, w3, w0
	str	w0, [x2, 1052]
	ldr	x3, [x21, 3528]
	ldr	w2, [x3, 1052]
	cmp	w2, 1024
	ble	.L139
	mov	w0, 1024
	str	w0, [x3, 1052]
	ldr	x3, [x21, 3528]
	ldr	w2, [x3, 1052]
.L139:
	ldr	w1, [x20, 512]
	sub	w2, w2, w1
	add	w2, w2, 4
	cmp	w2, wzr
	ble	.L138
	sxtw	x1, w1
	ldr	x4, [x22, 104]
	sub	x0, x1, #4
	ldr	x1, [x19, 16960]
	sxtw	x2, w2
	add	x0, x3, x0
	blr	x4
.L138:
	ldr	x0, .LC144
	ldr	x4, [x0]
	cbz	x4, .L162
	ldr	x2, [x21, 3528]
	mov	w3, 1064
	ldr	w0, [x19, 4]
	mov	w1, 6
	blr	x4
.L162:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L132:
	ldr	x1, [x20, 880]
	cbz	x1, .L142
	ldr	w0, [x19, 4]
	bl	FreeUsdByDec
	str	xzr, [x20, 880]
.L142:
	ldr	w0, [x19, 4]
	bl	GetUsd
	str	x0, [x21, 3536]
	cbz	x0, .L143
	ldr	x3, [x19, 16]
	mov	w2, 11
	add	x20, x19, 16384
	ldr	x3, [x3, 56]
	str	x3, [x0, 1056]
	ldr	x0, [x21, 3536]
	str	w2, [x0, 1040]
	ldr	x0, [x21, 3536]
	ldr	w2, [x21, 2836]
	str	w2, [x0, 1044]
	ldr	x2, [x21, 3536]
	ldr	w0, [x20, 512]
	sub	w0, w0, #4
	str	w0, [x2, 1052]
	ldr	x0, [x21, 3536]
	ldr	w2, [x0, 1052]
	cmp	w2, 1024
	ble	.L144
	mov	w2, 1024
	str	w2, [x0, 1052]
	ldr	x0, [x21, 3536]
	ldr	w2, [x0, 1052]
.L144:
	ldr	x22, .LC143
	sxtw	x2, w2
	ldr	x1, [x19, 16880]
	ldr	x3, [x22, 104]
	add	x1, x1, 4
	blr	x3
	ldrb	w0, [x20, 505]
	cbnz	w0, .L146
	ldr	x2, [x21, 3536]
	ldr	w0, [x20, 592]
	ldr	w3, [x2, 1052]
	add	w0, w3, w0
	str	w0, [x2, 1052]
	ldr	x3, [x21, 3536]
	ldr	w2, [x3, 1052]
	cmp	w2, 1024
	ble	.L147
	mov	w0, 1024
	str	w0, [x3, 1052]
	ldr	x3, [x21, 3536]
	ldr	w2, [x3, 1052]
.L147:
	ldr	w1, [x20, 512]
	sub	w2, w2, w1
	add	w2, w2, 4
	cmp	w2, wzr
	ble	.L146
	sxtw	x1, w1
	ldr	x4, [x22, 104]
	sub	x0, x1, #4
	ldr	x1, [x19, 16960]
	sxtw	x2, w2
	add	x0, x3, x0
	blr	x4
.L146:
	ldr	x0, .LC144
	ldr	x4, [x0]
	cbz	x4, .L162
	ldr	x2, [x21, 3536]
	mov	w3, 1064
	ldr	w0, [x19, 4]
	mov	w1, 6
	blr	x4
	b	.L162
	.p2align 3
.L143:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_user_data, .-AVS_user_data
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC143:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC144:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_sequence_display_extension
	.type	AVS_sequence_display_extension, %function
AVS_sequence_display_extension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x19, [x21, 568]
	mov	w1, 4
	ldr	x2, .LC146
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC148
	mov	w1, 3
	mov	x0, x19
	bl	avs_f_v
	strb	w0, [x20, 50]
	ldr	x2, .LC150
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	strb	w0, [x20, 51]
	ldr	x2, .LC152
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 52]
	beq	.L166
.L165:
	ldr	x2, .LC160
	mov	w1, 14
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x20, 68]
	ldr	x2, .LC161
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	strb	w0, [x20, 49]
	ldr	x2, .LC163
	mov	w1, 14
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x20, 72]
	ldr	x2, .LC164
	mov	w1, 2
	mov	x0, x19
	bl	avs_f_v
	strb	w0, [x20, 48]
	mov	x0, x19
	bl	AVS_next_start_code
	ldr	w1, [x21, 172]
	mov	w0, 1
	orr	w1, w1, 131072
	str	w1, [x21, 172]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L166:
	ldr	x2, .LC154
	mov	w1, 8
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x20, 56]
	ldr	x2, .LC156
	mov	w1, 8
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x20, 60]
	ldr	x2, .LC158
	mov	w1, 8
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x20, 64]
	b	.L165
	.size	AVS_sequence_display_extension, .-AVS_sequence_display_extension
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC161:
	.xword	.LC26
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC164:
	.xword	.LC34
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_copyright_extension
	.type	AVS_copyright_extension, %function
AVS_copyright_extension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x20, 568]
	mov	w1, 4
	ldr	x2, .LC165
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC167
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC169
	mov	w1, 8
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC171
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC172
	mov	w1, 7
	mov	x0, x19
	bl	avs_f_v
	ldr	x21, .LC173
	mov	w1, 1
	mov	x0, x19
	mov	x2, x21
	bl	avs_f_v
	ldr	x2, .LC175
	mov	w1, 20
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x21
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC177
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x21
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC179
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x0, x19
	bl	AVS_next_start_code
	ldr	w1, [x20, 172]
	mov	w0, 1
	orr	w1, w1, 2097152
	str	w1, [x20, 172]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_copyright_extension, .-AVS_copyright_extension
	.align	3
.LC165:
	.xword	.LC145
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC172:
	.xword	.LC34
	.align	3
.LC173:
	.xword	.LC26
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC177:
	.xword	.LC176
	.align	3
.LC179:
	.xword	.LC178
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_camera_parameters_extension
	.type	AVS_camera_parameters_extension, %function
AVS_camera_parameters_extension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x21, 568]
	mov	w1, 4
	ldr	x2, .LC180
	mov	x0, x19
	bl	avs_f_v
	ldr	x22, .LC181
	mov	w1, 1
	mov	x0, x19
	mov	x2, x22
	bl	avs_f_v
	ldr	x2, .LC183
	mov	w1, 7
	mov	x0, x19
	bl	avs_f_v
	ldr	x20, .LC184
	mov	w1, 1
	mov	x0, x19
	mov	x2, x20
	bl	avs_f_v
	ldr	x2, .LC186
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC188
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC190
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC192
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC194
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC196
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC198
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC200
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC202
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC204
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC206
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC208
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC210
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC212
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC214
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	x2, .LC216
	mov	w1, 22
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x22
	mov	w1, 32
	mov	x0, x19
	bl	avs_f_v
	mov	x0, x19
	bl	AVS_next_start_code
	ldr	w1, [x21, 172]
	mov	w0, 1
	orr	w1, w1, 4194304
	str	w1, [x21, 172]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_camera_parameters_extension, .-AVS_camera_parameters_extension
	.align	3
.LC180:
	.xword	.LC145
	.align	3
.LC181:
	.xword	.LC34
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC184:
	.xword	.LC26
	.align	3
.LC186:
	.xword	.LC185
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC190:
	.xword	.LC189
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC194:
	.xword	.LC193
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC204:
	.xword	.LC203
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
	.align	3
.LC216:
	.xword	.LC215
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_picture_display_extension
	.type	AVS_picture_display_extension, %function
AVS_picture_display_extension:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x26, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldr	x19, [x26, 568]
	mov	w1, 4
	ldr	x2, .LC217
	mov	x0, x19
	bl	avs_f_v
	ldrb	w0, [x22, 15]
	cmp	w0, 1
	beq	.L186
	ldrb	w0, [x22, 81]
	cbnz	w0, .L187
.L171:
	mov	w0, 1
	str	w0, [x22, 4]
.L173:
	ldr	x25, .LC219
	mov	w20, 0
	ldr	x23, .LC220
	ldr	x24, .LC222
	.p2align 2
.L175:
	add	x21, x22, x20, sxtw 2
	mov	x2, x25
	mov	w1, 16
	mov	x0, x19
	add	w20, w20, 1
	bl	avs_f_v
	str	w0, [x21, 352]
	mov	w1, 1
	mov	x2, x23
	mov	x0, x19
	bl	avs_f_v
	mov	x2, x24
	mov	w1, 16
	mov	x0, x19
	bl	avs_f_v
	str	w0, [x21, 364]
	mov	x2, x23
	mov	w1, 1
	mov	x0, x19
	bl	avs_f_v
	ldr	w0, [x22, 4]
	cmp	w0, w20
	bgt	.L175
	mov	x0, x19
	bl	AVS_next_start_code
	ldr	w0, [x26, 172]
	orr	w0, w0, 524288
	str	w0, [x26, 172]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L187:
	ldrb	w0, [x22, 83]
	cmp	w0, 1
	beq	.L174
.L172:
	mov	w0, 2
	str	w0, [x22, 4]
	b	.L173
	.p2align 3
.L186:
	ldrb	w0, [x22, 83]
	cmp	w0, 1
	bne	.L171
	ldrb	w0, [x22, 82]
	cmp	w0, 1
	bne	.L172
	.p2align 2
.L174:
	mov	w0, 3
	str	w0, [x22, 4]
	b	.L173
	.size	AVS_picture_display_extension, .-AVS_picture_display_extension
	.align	3
.LC217:
	.xword	.LC145
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC220:
	.xword	.LC26
	.align	3
.LC222:
	.xword	.LC221
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_extension
	.type	AVS_extension, %function
AVS_extension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x19, [x20, 568]
	mov	w1, 32
	ldr	x2, .LC224
	mov	x0, x19
	bl	avs_f_v
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	sub	w0, w0, #2
	cmp	w0, 9
	bls	.L196
.L189:
	mov	w1, 4
	mov	x0, x19
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L196:
	ldr	x1, .LC225
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx191
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx191:
	.section	.rodata
	.align	0
	.align	2
.L191:
	.byte	(.L190 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L192 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L193 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L189 - .Lrtx191) / 4
	.byte	(.L194 - .Lrtx191) / 4
	.text
	.p2align 3
.L194:
	mov	x1, x21
	mov	x0, x20
	bl	AVS_camera_parameters_extension
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L193:
	mov	x1, x21
	mov	x0, x20
	bl	AVS_picture_display_extension
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L192:
	mov	x1, x21
	mov	x0, x20
	bl	AVS_copyright_extension
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L190:
	mov	x1, x21
	mov	x0, x20
	bl	AVS_sequence_display_extension
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_extension, .-AVS_extension
	.align	3
.LC224:
	.xword	.LC223
	.align	3
.LC225:
	.xword	.L191
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_extension_and_userdata
	.type	AVS_extension_and_userdata, %function
AVS_extension_and_userdata:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	add	x21, x23, 12288
	mov	w24, w1
	add	x22, x21, 2656
	bl	_mcount
	mov	w20, 178
	add	x21, x21, 3600
	ldr	x19, [x22, 568]
	b	.L201
	.p2align 3
.L200:
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	uxtb	w0, w0
	cmp	w0, 178
	beq	.L205
.L201:
	mov	x0, x19
	bl	BsResidBits
	cmp	w0, 40
	mov	x0, x19
	ble	.L206
.L202:
	bl	AVS_next_start_code
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	uxtb	w0, w0
	cmp	w0, 181
	ccmp	w0, w20, 4, ne
	bne	.L203
	cmp	w0, 181
	bne	.L200
	mov	x1, x21
	mov	x0, x22
	bl	AVS_extension
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	uxtb	w0, w0
	cmp	w0, 178
	bne	.L201
	.p2align 2
.L205:
	mov	w1, w24
	mov	x0, x23
	bl	AVS_user_data
	mov	x0, x19
	bl	BsResidBits
	cmp	w0, 40
	mov	x0, x19
	bgt	.L202
.L206:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L203:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	AVS_extension_and_userdata, .-AVS_extension_and_userdata
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_AllocateVHB
	.type	AVS_AllocateVHB, %function
AVS_AllocateVHB:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 15160]
	mov	w0, 8160
	ldr	w20, [x19, 15156]
	sub	w2, w3, #32
	sub	w1, w20, #32
	cmp	w2, w0
	ccmp	w1, w0, 2, ls
	bhi	.L240
	ldr	x0, [x19, 16]
	ldr	w21, [x0, 724]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	cbnz	w21, .L210
	beq	.L241
.L229:
	mov	w21, 4
	mov	w23, 5
	mov	w22, w21
.L211:
	ldr	x0, .LC230
	mov	x2, 20
	mov	w1, 0
	str	w3, [x29, 76]
	ldr	x4, [x0, 96]
	add	x0, x29, 88
	blr	x4
	ldr	x0, [x19, 16]
	ldr	w3, [x29, 76]
	stp	w20, w3, [x29, 92]
	ldr	w0, [x0, 28]
	stp	w20, w3, [x29, 100]
	cmp	w0, 24
	beq	.L220
	strb	w22, [x29, 89]
	sxtb	w21, w21
	strb	w23, [x29, 90]
.L224:
	ldr	w0, [x19, 4]
	add	x1, x29, 88
	strb	w21, [x29, 91]
	bl	FSP_ConfigInstance
	mov	w21, w0
	cbnz	w0, .L221
	ldr	x1, [x19, 16]
	add	x3, x29, 84
	ldr	w0, [x19, 4]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L242
	cbnz	w0, .L243
	mov	w21, 1
	str	w21, [x19, 8]
	b	.L232
	.p2align 3
.L240:
	ldr	x1, .LC227
	mov	w2, w20
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
.L232:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L210:
	bne	.L229
	ldr	w4, [x0, 684]
	ldr	w5, [x0, 688]
	cmp	w20, w4
	bhi	.L217
	cmp	w3, w5
	bhi	.L217
.L218:
	ldr	w2, [x0, 712]
	mov	w21, 1
	ldr	w1, [x0, 708]
	add	w22, w1, 2
	cbz	w2, .L219
	add	w21, w1, w21
	mov	w1, 17
	cmp	w21, w1
	csel	w21, w21, w1, le
.L219:
	ldrsb	w23, [x0, 732]
	b	.L211
	.p2align 3
.L221:
	ldr	x1, .LC234
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	b	.L232
	.p2align 3
.L243:
	ldr	x1, .LC232
	mov	w0, 0
	bl	dprint_vfmw
	b	.L232
	.p2align 3
.L220:
	mov	w0, 1
	strb	w23, [x29, 90]
	strb	w0, [x29, 89]
	mov	w21, 1
	b	.L224
	.p2align 3
.L241:
	ldr	w4, [x0, 684]
	ldr	w5, [x0, 688]
	cmp	w20, w4
	bhi	.L213
	cmp	w5, w3
	bcc	.L213
	ldr	w21, [x19, 8]
	cmp	w21, 1
	bne	.L218
	b	.L232
	.p2align 3
.L217:
	ldr	x1, .LC229
	mov	w2, w20
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	b	.L232
	.p2align 3
.L213:
	ldr	x1, .LC229
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	b	.L232
.L242:
	add	x0, x19, 12288
	mov	w21, 3
	add	x0, x0, 3976
	bl	ResetVoQueue
	b	.L232
	.size	AVS_AllocateVHB, .-AVS_AllocateVHB
	.align	3
.LC227:
	.xword	.LC226
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC230:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC232:
	.xword	.LC231
	.align	3
.LC234:
	.xword	.LC233
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_StartDecode
	.type	AVS_StartDecode, %function
AVS_StartDecode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 16384
	add	x19, x21, 32
	bl	_mcount
	add	x20, x22, 656
	ldr	w0, [x22, 656]
	strb	w0, [x21, 32]
	ldr	w0, [x20, 4]
	strb	w0, [x19, 1]
	ldr	w0, [x20, 8]
	strb	w0, [x19, 2]
	ldr	w0, [x20, 12]
	strb	w0, [x19, 3]
	ldr	w0, [x20, 16]
	strb	w0, [x19, 4]
	ldr	w0, [x20, 28]
	str	w0, [x19, 8]
	ldr	w0, [x20, 32]
	str	w0, [x19, 76]
	ldr	w0, [x20, 52]
	str	w0, [x19, 12]
	ldr	w0, [x20, 180]
	str	w0, [x19, 88]
	ldr	w0, [x20, 192]
	str	w0, [x19, 92]
	ldr	w0, [x20, 184]
	str	w0, [x19, 96]
	ldr	w0, [x20, 196]
	str	w0, [x19, 100]
	ldr	w0, [x20, 188]
	str	w0, [x19, 104]
	ldr	w0, [x20, 200]
	str	w0, [x19, 108]
	ldr	w0, [x20, 60]
	strh	w0, [x19, 72]
	ldr	w0, [x20, 56]
	strh	w0, [x19, 74]
	ldr	w0, [x20, 64]
	strb	w0, [x19, 39]
	ldr	w0, [x20, 68]
	strb	w0, [x19, 40]
	ldr	w0, [x20, 104]
	strb	w0, [x19, 16]
	ldr	w0, [x20, 108]
	strb	w0, [x19, 17]
	ldr	w0, [x20, 72]
	strb	w0, [x19, 18]
	ldr	w0, [x20, 76]
	strb	w0, [x19, 19]
	ldr	w0, [x20, 84]
	strb	w0, [x19, 20]
	ldr	w0, [x20, 88]
	strb	w0, [x19, 21]
	ldr	w0, [x20, 92]
	strb	w0, [x19, 22]
	ldr	w0, [x20, 96]
	strb	w0, [x19, 23]
	ldr	w0, [x20, 100]
	strb	w0, [x19, 24]
	ldr	w0, [x20, 112]
	strb	w0, [x19, 25]
	ldr	w0, [x20, 116]
	strb	w0, [x19, 26]
	ldr	w0, [x20, 120]
	strb	w0, [x19, 27]
	ldr	w0, [x20, 124]
	strb	w0, [x19, 28]
	ldr	w0, [x20, 128]
	strb	w0, [x19, 29]
	ldr	w0, [x20, 172]
	strb	w0, [x19, 30]
	ldr	w0, [x20, 80]
	strb	w0, [x19, 31]
	ldr	w0, [x20, 136]
	strb	w0, [x19, 32]
	ldr	w0, [x20, 132]
	strb	w0, [x19, 33]
	ldr	w0, [x20, 152]
	strb	w0, [x19, 34]
	ldr	w0, [x20, 148]
	strb	w0, [x19, 35]
	ldr	w0, [x20, 144]
	strb	w0, [x19, 36]
	ldr	w0, [x20, 140]
	strb	w0, [x19, 37]
	ldr	w0, [x20, 176]
	strb	w0, [x19, 38]
	ldr	w0, [x20, 156]
	str	w0, [x19, 14452]
	ldr	w0, [x20, 160]
	str	w0, [x19, 14456]
	ldr	w0, [x20, 164]
	str	w0, [x19, 14460]
	ldr	w0, [x20, 232]
	str	w0, [x19, 14468]
	ldr	w0, [x20, 244]
	str	w0, [x19, 14472]
	ldr	x1, [x21, 15072]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetLogicFs
	cbz	x0, .L259
	ldr	x1, [x0, 40]
	add	x2, x21, 12288
	add	x5, x2, 2356
	add	x3, x22, 1036
	add	x4, x2, 2612
	ldr	w1, [x1, 24]
	str	w1, [x19, 14868]
	ldr	x1, [x0, 40]
	ldr	w1, [x1, 60]
	str	w1, [x19, 14876]
	ldr	x1, [x0, 40]
	ldr	w1, [x1, 44]
	str	w1, [x19, 14880]
	mov	x1, x5
	ldr	x0, [x0, 40]
	ldr	w0, [x0, 48]
	str	w0, [x19, 14884]
	ldr	w0, [x20, 52]
	str	w0, [x19, 14464]
	ldr	w0, [x20, 168]
	str	w0, [x19, 14476]
	ldr	w0, [x20, 376]
	str	w0, [x19, 14480]
	ldr	w0, [x20, 204]
	strb	w0, [x19, 41]
	ldr	w0, [x20, 208]
	strb	w0, [x19, 42]
	ldr	w0, [x20, 216]
	strb	w0, [x19, 43]
	ldr	w0, [x20, 212]
	strb	w0, [x19, 44]
	ldr	w0, [x20, 220]
	strb	w0, [x19, 45]
	ldr	w0, [x20, 224]
	strb	w0, [x19, 46]
	ldr	w0, [x20, 228]
	strb	w0, [x19, 47]
	.p2align 2
.L247:
	ldrsh	w0, [x3], 2
	str	w0, [x1], 4
	cmp	x1, x4
	bne	.L247
	ldr	w0, [x22, 692]
	str	w0, [x19, 14888]
	add	x0, x2, 2228
	ldr	w1, [x22, 696]
	str	w1, [x19, 14892]
	ldr	w1, [x22, 700]
	str	w1, [x19, 14896]
	ldr	w1, [x22, 704]
	str	w1, [x19, 14900]
	.p2align 2
.L248:
	ldr	w1, [x0, 2772]
	str	w1, [x0], 4
	cmp	x0, x5
	bne	.L248
	ldr	w0, [x21, 15808]
	ldr	x1, [x21, 16]
	add	w0, w0, 1
	str	x19, [x21, 24]
	str	w0, [x21, 15808]
	ldr	w0, [x1, 880]
	cmp	w0, 1
	beq	.L260
	cmp	w0, 2
	beq	.L261
.L250:
	ldr	w2, [x1, 592]
	mov	w0, 1
	str	w2, [x19, 14904]
	ldr	w1, [x1, 644]
	str	w1, [x19, 14908]
.L246:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L260:
	cbz	x19, .L250
	ldr	x3, [x21, 15072]
	ldrb	w0, [x3, 9]
	cmp	w0, 2
	bne	.L250
	str	xzr, [x21, 24]
	mov	w2, 0
	ldr	w0, [x21, 4]
	ldr	w1, [x3, 12]
	bl	FSP_SetDisplay
	mov	w0, 0
	b	.L246
	.p2align 3
.L261:
	ldr	w0, [x1, 884]
	cmp	w0, wzr
	ccmp	x19, xzr, 4, gt
	beq	.L250
	ldr	x3, [x21, 15072]
	ldrb	w0, [x3, 9]
	cmp	w0, 2
	bne	.L250
	str	xzr, [x21, 24]
	mov	w2, 0
	ldr	w0, [x21, 4]
	ldr	w1, [x3, 12]
	bl	FSP_SetDisplay
	ldr	x2, [x21, 16]
	mov	w0, 0
	ldr	w1, [x2, 884]
	sub	w1, w1, #1
	str	w1, [x2, 884]
	b	.L246
.L259:
	ldr	x1, .LC238
	mov	w2, 2208
	bl	dprint_vfmw
	mov	w0, 0
	b	.L246
	.size	AVS_StartDecode, .-AVS_StartDecode
	.align	3
.LC238:
	.xword	.LC237
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_SetImgFormat
	.type	AVS_SetImgFormat, %function
AVS_SetImgFormat:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	bl	_mcount
	ldrb	w1, [x20, 2859]
	ldrb	w24, [x20, 2894]
	cmp	w1, 1
	ldr	w26, [x20, 3192]
	beq	.L269
	ldrb	w0, [x20, 2924]
	cmp	w0, 1
	cset	w23, ne
.L263:
	ldrb	w0, [x20, 2857]
	mov	w27, 0
	ldrb	w22, [x20, 2926]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 3
	bhi	.L264
	ldr	x1, .LC239
	uxtb	x0, w0
	ldr	w27, [x1, x0, lsl 2]
.L264:
	add	x25, x20, 2656
	ldr	x1, [x25, 128]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L272
	ldrb	w1, [x0, 64]
	ldrb	w2, [x0, 65]
	bfi	w1, w26, 0, 2
	bfi	w2, w23, 0, 2
	and	w1, w1, -29
	orr	w2, w2, 12
	bfi	w1, w24, 5, 3
	bfi	w2, w22, 4, 2
	strb	w1, [x0, 64]
	strb	w2, [x0, 65]
	mov	w1, w27
	ldr	w2, [x0, 64]
	bfi	w2, w27, 14, 3
	str	w2, [x0, 64]
	ldr	x3, [x25, 128]
	ldrb	w2, [x0, 66]
	ldrb	w3, [x3]
	bfi	w2, w3, 1, 1
	strb	w2, [x0, 66]
	ldr	x2, [x25, 128]
	ldr	w2, [x2, 4]
	str	w2, [x0, 120]
	ldr	w2, [x25, 856]
	str	w2, [x0, 152]
	stp	w26, w26, [x0, 56]
	bl	SetAspectRatio
	ldr	w0, [x20, 2868]
	str	w0, [x19, 68]
	ldr	w0, [x20, 2872]
	str	w0, [x19, 72]
	ldr	w1, [x20, 2888]
	str	w1, [x19, 108]
	ldr	x1, [x21, 16]
	ldr	w1, [x1, 28]
	cmp	w1, 25
	beq	.L273
.L267:
	mov	w0, 6
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 8
	ldrb	w3, [x20, 2925]
	mov	w2, 1
	str	w1, [x19, 300]
	cmp	w3, 1
	strb	w2, [x19, 291]
	strb	w2, [x19, 289]
	csel	w0, wzr, w0, eq
	str	w1, [x19, 304]
	strb	w0, [x19, 284]
	str	w1, [x19, 308]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L269:
	mov	w23, 0
	b	.L263
	.p2align 3
.L273:
	ldr	w3, [x19, 112]
	add	w0, w0, 15
	lsr	w1, w0, 4
	ldr	w2, [x19, 36]
	lsl	w0, w3, 4
	ldr	x4, [x19, 504]
	add	w5, w3, w2
	mul	w0, w1, w0
	add	w1, w0, w2
	str	w1, [x19, 40]
	add	w3, w3, w1
	add	x0, x4, x0, sxtw
	stp	w2, w1, [x19, 20]
	stp	w5, w3, [x19, 28]
	str	x0, [x19, 512]
	b	.L267
	.p2align 3
.L272:
	ldr	x1, .LC241
	mov	w2, 2332
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	AVS_SetImgFormat, .-AVS_SetImgFormat
	.align	3
.LC239:
	.xword	.LANCHOR1
	.align	3
.LC241:
	.xword	.LC240
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_GetImageBuffer
	.type	AVS_GetImageBuffer, %function
AVS_GetImageBuffer:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 12288
	bl	_mcount
	ldr	w0, [x20, 16236]
	cmp	w0, 2
	beq	.L275
	ldr	w0, [x22, 3240]
	add	x2, x22, 2656
	add	x21, x22, 2656
	add	w1, w0, 1
	asr	w3, w1, 31
	sxtw	x0, w0
	lsr	w3, w3, 30
	lsl	x19, x0, 4
	add	x19, x19, x0, lsl 2
	add	w1, w1, w3
	add	x19, x2, x19
	and	w1, w1, 3
	sub	w1, w1, w3
	add	x19, x19, 28
	str	w1, [x22, 3240]
	mov	w1, 1
	str	x19, [x22, 2784]
	ldr	w0, [x20, 4]
	bl	FSP_NewLogicFs
	str	w0, [x19, 12]
	ldr	x0, [x21, 128]
	ldr	w1, [x0, 12]
	tbnz	w1, #31, .L291
.L277:
	ldr	w0, [x20, 4]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L292
	ldr	x2, [x21, 128]
	mov	w0, 18
	ldr	x1, .LC246
	ldr	w2, [x2, 12]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L281
	ldr	x1, [x19, 40]
	cbz	x1, .L281
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC248
	bl	dprint_vfmw
.L281:
	mov	w0, 1
	str	wzr, [x19, 200]
.L279:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L275:
	add	x19, x22, 2764
	str	x19, [x22, 2784]
	mov	w1, 1
	add	x21, x22, 2656
	ldr	w0, [x20, 4]
	bl	FSP_NewLogicFs
	str	w0, [x19, 12]
	ldr	x0, [x21, 128]
	ldr	w1, [x0, 12]
	tbz	w1, #31, .L277
.L291:
	ldr	x1, .LC243
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x21, 136]
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L278
	ldr	x1, [x21, 128]
	mov	w2, 1
	ldr	w0, [x20, 4]
	add	x23, x22, 2664
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x21, 136]
	mov	w2, 1
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x21, 144]
	mov	w2, 1
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x21, 152]
	mov	w2, 1
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	w0, [x20, 4]
	ldr	x1, [x19, 544]
	bl	FreeUsdByDec
	ldr	w0, [x20, 4]
	ldr	x1, [x19, 552]
	bl	FreeUsdByDec
	ldr	w0, [x20, 4]
	ldr	x1, [x19, 560]
	bl	FreeUsdByDec
	ldr	w0, [x20, 4]
	ldr	x1, [x19, 568]
	bl	FreeUsdByDec
	add	x0, x19, 512
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	stp	x23, x23, [x21, 128]
	stp	x23, x23, [x21, 144]
	ldr	w0, [x20, 4]
	bl	FSP_GetNullLogicFs
	str	w0, [x23, 12]
.L278:
	str	wzr, [x22, 3508]
	add	x1, x22, 3976
	ldr	w0, [x20, 4]
	bl	FSP_ClearNotInVoQueue
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L292:
	ldr	x1, .LC244
	mov	w2, 2437
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L279
	.size	AVS_GetImageBuffer, .-AVS_GetImageBuffer
	.align	3
.LC243:
	.xword	.LC242
	.align	3
.LC244:
	.xword	.LC237
	.align	3
.LC246:
	.xword	.LC245
	.align	3
.LC248:
	.xword	.LC247
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_OutputOneFrame
	.type	AVS_OutputOneFrame, %function
AVS_OutputOneFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4]
	ldr	w1, [x20, 12]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L299
	ldr	w0, [x19, 4]
	mov	w2, 1
	ldr	w1, [x20, 12]
	bl	FSP_SetDisplay
	add	x3, x19, 12288
	ldr	w0, [x19, 4]
	mov	x4, x21
	add	x3, x3, 3976
	mov	x2, x19
	mov	w1, 6
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L295
	ldr	w0, [x19, 4]
	mov	w2, 0
	ldr	w1, [x20, 12]
	bl	FSP_SetDisplay
	ldr	x1, .LC252
	mov	w0, 1
	ldr	w2, [x20, 12]
	bl	dprint_vfmw
	mov	w0, 0
.L295:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L299:
	ldr	x1, .LC250
	mov	w2, 2478
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_OutputOneFrame, .-AVS_OutputOneFrame
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdateTableIdx2Dist
	.type	AVS_UpdateTableIdx2Dist, %function
AVS_UpdateTableIdx2Dist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 269]
	cmp	w0, 1
	ldr	w0, [x19, 536]
	beq	.L312
	cbnz	w0, .L306
	ldr	x0, [x19, 136]
	ldr	w0, [x0, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 624]
.L305:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L306:
	cmp	w0, 1
	bne	.L307
	ldr	x0, [x19, 144]
	add	x1, x19, 8
	cmp	x0, x1
	beq	.L313
	ldr	w0, [x0, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 620]
.L309:
	ldp	x2, x1, [x19, 128]
	add	w0, w0, 1
	str	w0, [x19, 616]
	ldr	w1, [x1, 16]
	str	w0, [x19, 636]
	lsl	w0, w1, 1
	str	w0, [x19, 612]
	add	w1, w0, 1
	str	w0, [x19, 632]
	str	w1, [x19, 608]
	str	w1, [x19, 628]
	ldr	w0, [x2, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 624]
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L312:
	cmp	w0, 1
	beq	.L314
	cmp	w0, 2
	bne	.L305
	ldr	x0, [x19, 144]
	add	x1, x19, 8
	cmp	x0, x1
	beq	.L304
	ldr	w0, [x0, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 608]
.L304:
	ldr	x0, [x19, 136]
	ldr	w0, [x0, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 616]
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L307:
	cmp	w0, 2
	bne	.L305
	ldr	x0, [x19, 144]
	add	x1, x19, 8
	cmp	x0, x1
	beq	.L315
	ldr	w1, [x0, 16]
	lsl	w1, w1, 1
	str	w1, [x19, 612]
.L311:
	ldr	x0, [x19, 136]
	add	w2, w1, 1
	str	w2, [x19, 608]
	ldr	w0, [x0, 16]
	str	w1, [x19, 628]
	lsl	w0, w0, 1
	str	w2, [x19, 624]
	str	w0, [x19, 616]
	add	w1, w0, 1
	str	w0, [x19, 632]
	mov	w0, 1
	str	w1, [x19, 620]
	str	w1, [x19, 636]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L314:
	ldp	x0, x1, [x19, 136]
	add	x2, x19, 8
	cmp	x1, x2
	ldr	w0, [x0, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 608]
	beq	.L305
	ldr	w0, [x1, 16]
	lsl	w0, w0, 1
	str	w0, [x19, 612]
	b	.L305
	.p2align 3
.L313:
	ldr	w0, [x19, 620]
	b	.L309
	.p2align 3
.L315:
	ldr	w1, [x19, 612]
	b	.L311
	.size	AVS_UpdateTableIdx2Dist, .-AVS_UpdateTableIdx2Dist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdateTableMvEScale
	.type	AVS_UpdateTableMvEScale, %function
AVS_UpdateTableMvEScale:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 269]
	cmp	w0, 1
	beq	.L376
	ldr	w5, [x19, 536]
	cbz	w5, .L377
	cmp	w5, 1
	bne	.L329
	ldr	x12, [x19, 128]
	mov	w9, 0
	mov	w7, 4
	mov	w11, 0
	mov	w10, 512
.L334:
	ldr	w6, [x12, 16]
	lsl	w5, w9, 2
	sub	w5, w5, w9
	mov	w8, w9
	add	w6, w11, w6, lsl 1
.L330:
	add	x0, x19, x8, sxtw 2
	mov	w1, w9
	ldr	w4, [x0, 608]
	sub	w4, w6, w4
	and	w4, w4, 511
.L332:
	add	x0, x19, x1, sxtw 2
	add	w3, w5, w1
	mov	w2, 1
	add	x3, x19, x3, sxtw 2
	add	w1, w1, w2
	ldr	w0, [x0, 608]
	sub	w0, w6, w0
	ands	w0, w0, 511
	beq	.L331
	sdiv	w2, w10, w0
.L331:
	mul	w2, w4, w2
	cmp	w1, w7
	str	w2, [x3, 640]
	bne	.L332
	add	w8, w8, 1
	add	w5, w5, 4
	cmp	w8, w7
	bne	.L330
	add	w11, w11, 1
	add	w7, w7, 4
	cmp	w11, 2
	add	w9, w9, 4
	bne	.L334
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L377:
	mov	w0, 512
	str	w0, [x19, 704]
.L321:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L376:
	ldr	x1, [x19, 128]
	ldr	w2, [x19, 536]
	ldr	w1, [x1, 16]
	cmp	w2, 1
	lsl	w1, w1, 1
	beq	.L378
	cmp	w2, 2
	bne	.L321
	ldr	w2, [x19, 608]
	sub	w2, w1, w2
	ands	w2, w2, 511
	beq	.L326
	mov	w0, 512
	sdiv	w0, w0, w2
.L326:
	ldr	w3, [x19, 616]
	mul	w0, w2, w0
	sub	w1, w3, w1
	str	w0, [x19, 640]
	ands	w1, w1, 511
	mov	w0, 1
	beq	.L327
	mov	w0, 512
	sdiv	w0, w0, w1
.L327:
	mul	w1, w1, w0
	str	w1, [x19, 656]
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L329:
	cmp	w5, 2
	bne	.L321
	ldr	x9, [x19, 128]
	add	x4, x19, 620
	mov	w7, 9
	mov	w6, 0
	mov	w8, 512
.L344:
	ldr	w1, [x9, 16]
	lsl	w10, w6, 2
	lsl	w3, w6, 3
	add	w1, w6, w1, lsl 1
.L335:
	add	x11, x19, x10, sxtw 2
	ldr	w2, [x4, -12]
	mov	w12, 1
	add	x13, x19, x3, sxtw 2
	sub	w2, w1, w2
	ldr	w0, [x11, 608]
	ands	w2, w2, 511
	mov	w11, w12
	sub	w0, w1, w0
	and	w0, w0, 511
	beq	.L337
	sdiv	w11, w8, w2
.L337:
	mul	w11, w11, w0
	str	w11, [x13, 640]
	ldr	w2, [x4, -8]
	sub	w2, w1, w2
	ands	w2, w2, 511
	beq	.L338
	sdiv	w12, w8, w2
.L338:
	add	w2, w3, 1
	add	w10, w10, 1
	mul	w0, w0, w12
	add	x2, x19, x2, sxtw 2
	cmp	w5, w10
	add	w3, w3, 2
	str	w0, [x2, 640]
	bne	.L335
	sub	w10, w7, #4
	mov	w12, w5
.L336:
	add	x11, x19, x12, sxtw 2
	ldr	w2, [x4, -4]
	sub	w3, w10, #1
	mov	w13, 1
	sub	w2, w2, w1
	ldr	w0, [x11, 608]
	ands	w2, w2, 511
	add	x3, x19, x3, sxtw 2
	mov	w11, w13
	sub	w0, w0, w1
	and	w0, w0, 511
	beq	.L341
	sdiv	w11, w8, w2
.L341:
	mul	w11, w11, w0
	str	w11, [x3, 640]
	ldr	w2, [x4]
	sub	w2, w2, w1
	ands	w2, w2, 511
	beq	.L342
	sdiv	w13, w8, w2
.L342:
	add	x2, x19, x10, sxtw 2
	add	w10, w10, 2
	mul	w0, w0, w13
	cmp	w10, w7
	add	w12, w12, 1
	str	w0, [x2, 640]
	bne	.L336
	add	w6, w6, 1
	add	w7, w7, 8
	cmp	w6, 2
	add	x4, x4, 16
	add	w5, w5, 4
	bne	.L344
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L378:
	add	x5, x19, 608
	add	x3, x19, 644
	add	x7, x19, 676
	mov	w8, 512
.L320:
	ldr	w2, [x19, 608]
	mov	w6, 1
	ldr	w0, [x5]
	mov	w4, w6
	sub	w2, w1, w2
	ands	w2, w2, 511
	sub	w0, w1, w0
	and	w0, w0, 511
	beq	.L322
	sdiv	w4, w8, w2
.L322:
	mul	w4, w4, w0
	str	w4, [x3, -4]
	ldr	w2, [x19, 612]
	sub	w2, w1, w2
	ands	w2, w2, 511
	beq	.L323
	sdiv	w6, w8, w2
.L323:
	mul	w0, w0, w6
	str	w0, [x3], 16
	add	x5, x5, 4
	cmp	x7, x3
	bne	.L320
	b	.L321
	.size	AVS_UpdateTableMvEScale, .-AVS_UpdateTableMvEScale
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdateTableDirectScale
	.type	AVS_UpdateTableDirectScale, %function
AVS_UpdateTableDirectScale:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 269]
	cmp	w0, 1
	beq	.L402
	ldr	x7, [x19, 136]
	add	x5, x19, 8
	add	x3, x19, 768
	mov	w1, 1
	mov	w2, 0
	mov	w9, 16384
	ldr	w6, [x7, 16]
	mov	w8, 32
	lsl	w6, w6, 1
.L386:
	sub	w0, w1, #1
	and	w4, w1, 1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	add	w0, w0, 1
	add	x0, x19, x0, sxtw 3
	ldr	x0, [x0, 136]
	cmp	x0, x5
	beq	.L384
	ldr	w2, [x0, 16]
	add	w2, w4, w2, lsl 1
	sub	w0, w6, w2
	ands	w0, w0, 511
	bne	.L385
	str	w8, [x3]
.L384:
	add	w1, w1, 1
	add	x3, x3, 4
	cmp	w1, 5
	bne	.L386
	ldr	w9, [x19, 896]
	ldr	w8, [x7, 16]
	lsl	w8, w8, 1
	cbz	w9, .L403
	add	x6, x19, 784
	mov	w3, 1
	mov	w4, 0
	mov	w10, 32
	mov	w11, 16384
	.p2align 2
.L396:
	cbz	w9, .L389
	add	w0, w4, w4, lsr 31
	asr	w0, w0, 1
	add	w0, w0, 1
	add	x0, x19, x0, sxtw 3
	ldr	x0, [x0, 136]
	cmp	x0, x5
	beq	.L390
	ldr	w2, [x0, 16]
	and	w0, w3, 1
	add	w2, w0, w2, lsl 1
	sub	w1, w8, w2
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w7, w0, 23
	add	w1, w1, w7
	and	w0, w1, 511
	subs	w0, w0, w7
	bne	.L391
	str	w10, [x6, -16]
.L392:
	str	w10, [x6]
.L395:
	add	w3, w3, 1
	add	w4, w4, 1
	cmp	w3, 5
	add	x6, x6, 4
	bne	.L396
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L389:
	add	w0, w3, w3, lsr 31
	asr	w0, w0, 1
	add	x0, x19, x0, sxtw 3
	ldr	x0, [x0, 136]
	cmp	x0, x5
	beq	.L390
	ldr	w2, [x0, 16]
	and	w0, w4, 1
	add	w2, w0, w2, lsl 1
.L390:
	sub	w1, w8, w2
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w7, w0, 23
	add	w1, w1, w7
	and	w0, w1, 511
	subs	w0, w0, w7
	beq	.L392
	sdiv	w0, w11, w0
	str	w0, [x6]
	b	.L395
	.p2align 3
.L385:
	sdiv	w0, w9, w0
	str	w0, [x3]
	b	.L384
	.p2align 3
.L391:
	sdiv	w0, w11, w0
	str	w0, [x6, -16]
	str	w0, [x6]
	b	.L395
	.p2align 3
.L403:
	add	w8, w8, 1
	add	x6, x19, 784
	mov	w3, 1
	mov	w4, 0
	mov	w10, 32
	mov	w11, 16384
	b	.L396
	.p2align 3
.L402:
	ldr	x0, [x19, 136]
	add	x4, x19, 8
	add	x2, x19, 144
	add	x1, x19, 768
	mov	w6, 16384
	mov	w5, 32
	ldr	w3, [x0, 16]
	add	x19, x19, 776
	lsl	w3, w3, 1
.L383:
	ldr	x0, [x2]
	cmp	x0, x4
	beq	.L381
	ldr	w0, [x0, 16]
	sub	w0, w3, w0, lsl 1
	ands	w0, w0, 511
	bne	.L382
	str	w5, [x1]
.L381:
	add	x1, x1, 4
	add	x2, x2, 8
	cmp	x19, x1
	bne	.L383
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L382:
	sdiv	w0, w6, w0
	str	w0, [x1]
	b	.L381
	.size	AVS_UpdateTableDirectScale, .-AVS_UpdateTableDirectScale
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdateTableSymScale
	.type	AVS_UpdateTableSymScale, %function
AVS_UpdateTableSymScale:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 144]
	add	x0, x19, 8
	cmp	x1, x0
	beq	.L411
	ldrb	w0, [x19, 269]
	cmp	w0, 1
	beq	.L406
	ldr	x12, [x19, 128]
	mov	w6, 0
	mov	w11, 512
.L409:
	ldr	w5, [x12, 16]
	lsl	w8, w6, 2
	lsl	w10, w6, 1
	mov	x2, 0
	add	w9, w8, 3
	add	w5, w6, w5, lsl 1
.L408:
	add	w3, w8, w2
	sub	w4, w9, w2
	add	w1, w2, w10
	mov	w7, 1
	add	x3, x19, x3, sxtw 2
	add	x4, x19, x4, sxtw 2
	add	x2, x2, 1
	add	x1, x19, x1, sxtw 2
	ldr	w3, [x3, 608]
	ldr	w0, [x4, 608]
	sub	w3, w5, w3
	ands	w3, w3, 511
	sub	w0, w0, w5
	and	w0, w0, 511
	beq	.L407
	sdiv	w7, w11, w3
.L407:
	mul	w0, w0, w7
	cmp	x2, 2
	str	w0, [x1, 800]
	bne	.L408
	add	w6, w6, 1
	cmp	w6, 2
	bne	.L409
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L406:
	ldp	x4, x2, [x19, 128]
	ldr	w3, [x1, 16]
	ldr	w1, [x4, 16]
	ldr	w2, [x2, 16]
	lsl	w4, w1, 1
	lsl	w1, w2, 1
	sub	w2, w4, w3, lsl 1
	ands	w2, w2, 511
	sub	w1, w1, w4
	and	w1, w1, 511
	bne	.L418
.L410:
	mul	w1, w1, w0
	str	w1, [x19, 800]
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L418:
	mov	w0, 512
	sdiv	w0, w0, w2
	b	.L410
	.p2align 3
.L411:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_UpdateTableSymScale, .-AVS_UpdateTableSymScale
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdateTabBBlkDist
	.type	AVS_UpdateTabBBlkDist, %function
AVS_UpdateTabBBlkDist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 144]
	add	x0, x19, 8
	cmp	x1, x0
	beq	.L422
	ldrb	w0, [x19, 269]
	cmp	w0, 1
	beq	.L423
	ldr	x7, [x19, 128]
	add	x0, x19, 512
	ldr	w5, [x19, 624]
	ldr	w4, [x19, 632]
	ldp	w3, w1, [x0, 104]
	ldp	w6, w2, [x0, 96]
	ldr	w0, [x7, 16]
	lsl	w0, w0, 1
	sub	w3, w3, w0
	sub	w2, w0, w2
	sub	w6, w0, w6
	sub	w0, w1, w0
	and	w1, w3, 511
	and	w6, w6, 511
	str	w1, [x19, 824]
	and	w0, w0, 511
	str	w6, [x19, 816]
	and	w1, w2, 511
	str	w0, [x19, 828]
	mov	w0, 1
	str	w1, [x19, 820]
	ldr	w3, [x19, 628]
	ldr	w1, [x7, 16]
	ldr	w2, [x19, 636]
	lsl	w1, w1, 1
	add	w1, w1, w0
	sub	w3, w1, w3
	sub	w5, w1, w5
	sub	w4, w4, w1
	sub	w1, w2, w1
	and	w2, w3, 511
	add	x3, x19, 768
	and	w5, w5, 511
	and	w4, w4, 511
	and	w1, w1, 511
	stp	w5, w2, [x3, 64]
	stp	w4, w1, [x3, 72]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L423:
	ldp	x3, x4, [x19, 128]
	ldr	w2, [x1, 16]
	ldr	w3, [x3, 16]
	ldr	w1, [x4, 16]
	lsl	w3, w3, 1
	lsl	w1, w1, 1
	sub	w2, w3, w2, lsl 1
	sub	w1, w1, w3
	and	w2, w2, 511
	and	w1, w1, 511
	str	w2, [x19, 816]
	str	w1, [x19, 824]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L422:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_UpdateTabBBlkDist, .-AVS_UpdateTabBBlkDist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_UpdatePmvTable
	.type	AVS_UpdatePmvTable, %function
AVS_UpdatePmvTable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 536]
	cmp	w1, 1
	beq	.L426
	cbz	w1, .L427
	cmp	w1, 2
	beq	.L428
	mov	w19, 0
.L425:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L428:
	mov	x0, x20
	mov	w19, 1
	bl	AVS_UpdateTableIdx2Dist
	mov	x0, x20
	bl	AVS_UpdateTableMvEScale
	mov	x0, x20
	bl	AVS_UpdateTableDirectScale
	mov	x0, x20
	bl	AVS_UpdateTabBBlkDist
	mov	x0, x20
	bl	AVS_UpdateTableSymScale
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L427:
	ldrb	w0, [x20, 269]
	mov	w19, 1
	cmp	w0, w19
	beq	.L425
	mov	x0, x20
	bl	AVS_UpdateTableIdx2Dist
	mov	x0, x20
	bl	AVS_UpdateTableMvEScale
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L426:
	mov	x0, x20
	mov	w19, w1
	bl	AVS_UpdateTableIdx2Dist
	mov	x0, x20
	bl	AVS_UpdateTableMvEScale
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_UpdatePmvTable, .-AVS_UpdatePmvTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_GetStreamInf
	.type	AVS_GetStreamInf, %function
AVS_GetStreamInf:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	bl	_mcount
	ldr	w1, [x20, 2840]
	ldrb	w2, [x20, 2856]
	cmp	w1, 1
	str	w2, [x20, 3548]
	beq	.L435
	ldr	w0, [x19, 8]
	cmp	w0, 1
	beq	.L436
.L435:
	ldr	x1, .LC256
	mov	w0, 22
	bl	dprint_vfmw
	add	x3, x29, 80
	ldr	w0, [x19, 4]
	add	x2, x29, 72
	add	x1, x29, 68
	stp	wzr, wzr, [x29, 68]
	str	wzr, [x3, -4]!
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 16]
	ldr	w2, [x0, 724]
	cmp	w2, 1
	beq	.L524
.L438:
	add	x0, x20, 2844
	add	x1, x20, 2656
	ldr	w2, [x0, 24]
	add	w2, w2, 15
	lsr	w2, w2, 4
	str	w2, [x1, 164]
	ldrb	w3, [x0, 15]
	cmp	w3, 1
	ldr	w3, [x0, 28]
	beq	.L525
	add	w3, w3, 31
	lsr	w3, w3, 5
	lsl	w3, w3, 1
	str	w3, [x1, 168]
.L444:
	cmp	w2, 512
	bgt	.L445
	cmp	w3, 512
	ble	.L446
.L445:
	ldr	x1, .LC261
	mov	w0, 18
	mov	w22, 0
	bl	dprint_vfmw
.L441:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L446:
	add	x22, x20, 2656
	ldr	x1, [x22, 136]
	ldr	w0, [x19, 4]
	add	x21, x20, 2664
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L448
	ldr	x1, [x22, 128]
	mov	w2, 1
	ldr	w0, [x19, 4]
	add	x21, x20, 2664
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x22, 136]
	mov	w2, 1
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x22, 144]
	mov	w2, 1
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x22, 152]
	mov	w2, 1
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 4]
	ldr	x1, [x23, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 4]
	ldr	x1, [x23, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 4]
	ldr	x1, [x23, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 4]
	ldr	x1, [x23, 568]
	bl	FreeUsdByDec
	add	x0, x23, 512
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	stp	x21, x21, [x22, 128]
	stp	x21, x21, [x22, 144]
	ldr	w0, [x19, 4]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 12]
.L448:
	str	wzr, [x20, 3508]
	add	x22, x20, 3976
	mov	x1, x22
	ldr	w0, [x19, 4]
	bl	FSP_ClearNotInVoQueue
	ldr	x0, [x19, 16]
	ldr	w1, [x0, 724]
	cbnz	w1, .L449
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L526
.L449:
	ldr	w0, [x19, 4]
	bl	FSP_GetFspType
	cbz	w0, .L522
.L451:
	add	x23, x20, 2656
	mov	x0, x19
	str	wzr, [x23, 184]
	mov	w22, 3
	stp	x21, x21, [x23, 128]
	stp	x21, x21, [x23, 144]
	bl	AVS_AllocateVHB
	cmp	w0, w22
	beq	.L441
	cbz	w0, .L527
	str	wzr, [x23, 184]
.L436:
	add	x21, x20, 2844
	add	x23, x20, 2656
	ldrb	w2, [x21, 11]
	mov	x0, x19
	ldr	x1, [x23, 128]
	str	w2, [x23, 888]
	ldrb	w2, [x21, 81]
	strb	w2, [x1, 8]
	bl	AVS_GetImageBuffer
	mov	w22, w0
	cbz	w0, .L528
	ldr	x1, [x23, 128]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L529
	ldr	x3, [x19, 16]
	mov	x4, -1
	ldr	x1, .LC268
	mov	w0, 29
	ldr	x3, [x3, 56]
	str	x3, [x2, 584]
	ldr	x3, [x19, 16]
	ldr	x3, [x3, 72]
	str	x3, [x2, 592]
	ldr	x3, [x19, 16]
	ldr	x3, [x3, 88]
	str	x3, [x2, 600]
	ldr	x3, [x19, 16]
	ldr	w3, [x3, 104]
	str	w3, [x2]
	ldr	x3, [x19, 16]
	ldr	w3, [x3, 108]
	str	w3, [x2, 4]
	ldr	x3, [x19, 16]
	ldr	w3, [x3, 112]
	str	w3, [x2, 8]
	ldr	x3, [x19, 16]
	ldr	w3, [x3, 128]
	str	w3, [x2, 12]
	ldrb	w3, [x21, 81]
	cmp	w3, wzr
	cset	w3, eq
	str	w3, [x2, 52]
	ldr	x3, [x19, 16]
	str	x4, [x3, 56]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
	ldr	x0, [x23, 128]
	mov	w1, 1
	ldr	w2, [x21, 112]
	str	w2, [x0, 16]
	ldr	x0, [x23, 128]
	ldrb	w2, [x21, 81]
	strb	w2, [x0, 8]
	ldr	x0, [x23, 128]
	ldr	w2, [x21, 348]
	strb	w2, [x0, 9]
	ldrb	w0, [x21, 81]
	ldr	x2, [x23, 128]
	cbz	w0, .L456
	ldrsb	w1, [x21, 82]
.L456:
	strb	w1, [x2, 10]
	ldrb	w1, [x20, 2925]
	cbnz	w1, .L457
	ldr	w0, [x20, 3192]
	cbz	w0, .L530
.L457:
	add	x22, x20, 2844
	add	x23, x20, 2656
	ldr	w1, [x22, 344]
	mov	x0, x23
	str	w1, [x20, 3552]
	add	x21, x19, 16384
	bl	AVS_UpdatePmvTable
	ldr	w4, [x20, 2820]
	add	x1, x21, 656
	ldr	w3, [x20, 2824]
	mov	w2, 1
	mul	w0, w4, w3
	sub	w0, w0, #1
	str	w0, [x21, 656]
	stp	wzr, w2, [x1, 4]
	ldr	w2, [x20, 3252]
	stp	w3, w4, [x1, 56]
	cmp	w2, wzr
	add	w0, w2, 63
	csel	w0, w0, w2, lt
	mov	w2, 6
	asr	w0, w0, 6
	mov	w3, 3
	stp	w0, w2, [x1, 12]
	add	x0, x20, 3048
	add	x2, x20, 3176
	ldr	w4, [x20, 3548]
	str	w4, [x1, 64]
	ldr	w4, [x20, 3544]
	str	w4, [x1, 68]
	ldrb	w4, [x22, 94]
	str	w4, [x1, 72]
	ldrb	w4, [x22, 93]
	str	w4, [x1, 76]
	ldrb	w4, [x22, 92]
	str	w4, [x1, 80]
	ldrb	w4, [x22, 86]
	str	w4, [x1, 84]
	ldrb	w4, [x22, 85]
	str	w4, [x1, 88]
	ldrb	w4, [x22, 84]
	str	w4, [x1, 92]
	ldrb	w4, [x22, 83]
	str	w4, [x1, 96]
	ldrb	w4, [x22, 82]
	str	w4, [x1, 100]
	ldr	w4, [x22, 348]
	str	w4, [x1, 104]
	ldrb	w4, [x22, 81]
	cmp	w4, wzr
	csinc	w3, w3, wzr, ne
	str	w3, [x1, 108]
	ldrb	w3, [x22, 80]
	str	w3, [x1, 112]
	ldr	w3, [x22, 124]
	str	w3, [x1, 116]
	ldr	w3, [x22, 120]
	str	w3, [x1, 120]
	ldrb	w3, [x22, 89]
	str	w3, [x1, 124]
	ldrb	w3, [x22, 88]
	str	w3, [x1, 128]
	ldr	w3, [x22, 128]
	str	w3, [x1, 204]
	ldr	w3, [x22, 136]
	str	w3, [x1, 208]
	ldr	w3, [x22, 140]
	str	w3, [x1, 216]
	ldr	w3, [x22, 144]
	str	w3, [x1, 212]
	.p2align 2
.L460:
	ldrh	w1, [x0]
	add	x0, x0, 2
	cmp	x0, x2
	strh	w1, [x0, 2082]
	bne	.L460
	add	x22, x21, 656
	ldr	w1, [x20, 3176]
	add	x23, x20, 2656
	str	w1, [x22, 220]
	ldr	w1, [x20, 3188]
	str	w1, [x22, 228]
	ldr	w0, [x20, 3184]
	str	w0, [x22, 224]
	ldp	x0, x1, [x23, 128]
	ldrb	w0, [x0, 9]
	ldr	w1, [x1, 12]
	cmp	w0, 2
	ldr	w0, [x19, 4]
	beq	.L531
	bl	FSP_GetFsImagePtr
	cbz	x0, .L532
	ldr	x1, [x23, 136]
	mov	w24, 3
	ldrb	w2, [x1, 8]
	cmp	w2, 1
	csinc	w2, w24, wzr, eq
	str	w2, [x22, 132]
	ldrsb	w2, [x1, 10]
	str	w2, [x22, 136]
	ldr	w2, [x0, 36]
	str	w2, [x22, 156]
	ldrb	w2, [x1, 8]
	cmp	w2, 1
	csinc	w2, w24, wzr, eq
	str	w2, [x22, 148]
	ldrsb	w1, [x1, 10]
	str	w1, [x22, 152]
	ldr	w0, [x0, 36]
	str	w0, [x22, 160]
	ldr	x1, [x23, 144]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L533
	ldr	x1, [x23, 144]
.L523:
	ldrb	w2, [x1, 8]
	add	x23, x20, 2656
	cmp	w2, 1
	csinc	w24, w24, wzr, eq
	str	w24, [x22, 140]
	ldrsb	w1, [x1, 10]
	str	w1, [x22, 144]
	ldr	w0, [x0, 36]
	str	w0, [x22, 164]
	ldr	x1, [x23, 136]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L534
	add	x22, x21, 656
	ldr	w0, [x0, 52]
	str	w0, [x22, 36]
	ldr	x1, [x23, 144]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L535
	ldr	w0, [x0, 52]
	str	w0, [x22, 40]
	ldr	x1, [x23, 152]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L536
	ldr	w0, [x0, 52]
	str	w0, [x22, 44]
	ldr	x1, [x23, 128]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L537
	ldr	w2, [x0, 52]
	mov	w1, 3
	str	w2, [x22, 48]
	ldr	w2, [x0, 36]
	str	w2, [x22, 52]
	ldr	w0, [x0, 20]
	str	w0, [x22, 168]
	ldr	x2, [x23, 136]
	ldrb	w0, [x2, 8]
	cmp	w0, 1
	csinc	w0, w1, wzr, eq
	str	w0, [x22, 172]
	ldrb	w0, [x2, 9]
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x22, 176]
	ldr	x1, [x23, 128]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetPmvAddr
	str	w0, [x22, 232]
	ldr	x1, [x23, 136]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetPmvAddr
	str	w0, [x22, 244]
	mov	w6, 4
	mov	w4, 8
	ldr	w5, [x20, 3192]
	mov	w1, 16
	mov	w3, 32
	mov	w2, 0
	cmp	w5, 2
	add	x0, x20, 3296
	csel	w6, w6, wzr, eq
	csel	w4, w4, wzr, eq
	csel	w3, w1, w3, eq
	.p2align 2
.L481:
	ldr	w1, [x0]
	add	x0, x0, 4
	add	w2, w2, 1
	and	w1, w1, 262143
	cmp	w3, w2
	str	w1, [x0, 1700]
	bgt	.L481
	cbz	w4, .L486
	add	x2, x20, 3424
	add	w4, w4, 16
	mov	w0, 16
	add	x5, x21, 656
	.p2align 2
.L485:
	add	x3, x5, x0, sxtw 2
	ldr	w1, [x2], 4
	add	w0, w0, 1
	and	w1, w1, 32767
	cmp	w4, w0
	str	w1, [x3, 248]
	bne	.L485
.L486:
	cbz	w6, .L484
	lsl	w8, w6, 1
	mov	w4, 24
	mov	w2, 0
	add	x7, x21, 656
	.p2align 2
.L487:
	add	w0, w2, 1
	add	x1, x20, 2656
	add	x3, x1, x2, sxtw 2
	add	x5, x7, x4, sxtw 2
	add	x1, x1, x0, sxtw 2
	add	w2, w2, 2
	cmp	w2, w8
	add	w4, w4, 1
	ldr	w0, [x3, 816]
	ldr	w3, [x1, 816]
	and	w1, w0, 511
	ubfiz	w0, w3, 9, 9
	orr	w0, w0, w1
	str	w0, [x5, 248]
	bne	.L487
	add	x2, x20, 3456
	add	w4, w6, 28
	mov	w0, 28
	add	x5, x21, 656
	.p2align 2
.L488:
	add	x3, x5, x0, sxtw 2
	ldr	w1, [x2], 4
	add	w0, w0, 1
	and	w1, w1, 262143
	cmp	w4, w0
	str	w1, [x3, 248]
	bne	.L488
.L484:
	ldr	w0, [x20, 3248]
	mov	w22, 1
	str	w0, [x21, 1032]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L524:
	ldr	w0, [x29, 76]
	cmp	w0, wzr
	ble	.L538
.L439:
	mov	w22, 3
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L525:
	add	w3, w3, 15
	lsr	w3, w3, 4
	str	w3, [x1, 168]
	b	.L444
	.p2align 3
.L528:
	ldr	x1, .LC265
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L526:
	ldr	w0, [x19, 8]
	cbnz	w0, .L451
.L522:
	mov	x0, x22
	bl	ResetVoQueue
	b	.L451
.L538:
	ldr	w0, [x29, 72]
	cmp	w0, 32
	bgt	.L439
	ldr	x0, [x19, 24]
	cbnz	x0, .L439
	ldr	w3, [x19, 15124]
	cbz	w3, .L438
	ldr	w7, [x19, 15912]
	cbz	w7, .L438
	add	x21, x19, 16384
	ldr	w5, [x21, 1164]
	cmp	w7, w5
	beq	.L438
	ldr	w6, [x19, 15916]
	ldr	w4, [x21, 1168]
	cmp	w6, w4
	beq	.L438
	ldr	x1, .LC258
	mov	w0, w2
	bl	dprint_vfmw
	ldr	w0, [x19, 15912]
	ldr	x1, .LC259
	str	w0, [x21, 1164]
	ldr	x4, [x1]
	ldr	w0, [x19, 15916]
	str	w0, [x21, 1168]
	cbz	x4, .L438
	ldr	w0, [x19, 4]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L438
	.p2align 3
.L531:
	bl	FSP_GetFsImagePtr
	cbz	x0, .L539
	ldr	x1, [x23, 136]
	mov	w24, 3
	ldrb	w2, [x1, 8]
	cmp	w2, 1
	csinc	w2, w24, wzr, eq
	str	w2, [x22, 132]
	ldrsb	w1, [x1, 10]
	str	w1, [x22, 136]
	ldr	w0, [x0, 36]
	str	w0, [x22, 156]
	ldr	x1, [x23, 144]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L540
	ldr	x1, [x23, 144]
	ldrb	w2, [x1, 8]
	cmp	w2, 1
	csinc	w2, w24, wzr, eq
	str	w2, [x22, 148]
	ldrsb	w1, [x1, 10]
	str	w1, [x22, 152]
	ldr	w0, [x0, 36]
	str	w0, [x22, 160]
	ldr	x1, [x23, 152]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L541
	ldr	x1, [x23, 152]
	b	.L523
.L530:
	ldr	x1, [x20, 2784]
	mov	w2, 1
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 12]
	bl	FSP_SetRef
	ldr	x0, [x20, 2808]
	add	x1, x20, 2664
	cmp	x0, x1
	beq	.L458
	ldr	w1, [x0, 12]
	mov	w2, 0
	ldr	w0, [x19, 4]
	bl	FSP_SetRef
.L458:
	ldr	x2, [x20, 2792]
	ldr	x3, [x20, 2800]
	ldr	x1, [x20, 2784]
	str	x1, [x20, 2792]
	str	x2, [x20, 2800]
	str	x3, [x20, 2808]
	b	.L457
.L529:
	ldr	x1, .LC266
	mov	w2, 1886
	mov	w0, 0
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L527:
	ldr	x1, .LC263
	mov	w0, 1
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L534:
	ldr	x1, .LC266
	mov	w2, 2013
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L535:
	ldr	x1, .LC266
	mov	w2, 2017
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L536:
	ldr	x1, .LC266
	mov	w2, 2021
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L533:
	ldr	x1, .LC266
	mov	w2, 2006
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L532:
	ldr	x1, .LC266
	mov	w2, 1997
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L537:
	ldr	x1, .LC266
	mov	w2, 2025
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L541:
	ldr	x1, .LC266
	mov	w2, 1989
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L540:
	ldr	x1, .LC266
	mov	w2, 1983
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
.L539:
	ldr	x1, .LC266
	mov	w2, 1977
	mov	w22, 0
	bl	dprint_vfmw
	b	.L441
	.size	AVS_GetStreamInf, .-AVS_GetStreamInf
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC259:
	.xword	g_event_report
	.align	3
.LC261:
	.xword	.LC260
	.align	3
.LC263:
	.xword	.LC262
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC266:
	.xword	.LC249
	.align	3
.LC268:
	.xword	.LC267
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_PrepareDecode
	.type	AVS_PrepareDecode, %function
AVS_PrepareDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS_GetStreamInf
	cmp	w0, 3
	beq	.L543
	cmp	w0, wzr
	cset	w0, ne
.L543:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_PrepareDecode, .-AVS_PrepareDecode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_VerifyMemPara
	.type	AVS_VerifyMemPara, %function
AVS_VerifyMemPara:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	AVS_VerifyMemPara, .-AVS_VerifyMemPara
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_Init
	.type	AVSDEC_Init, %function
AVSDEC_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	add	x20, x21, 16384
	bl	_mcount
	ldr	x23, .LC269
	mov	x2, 17560
	mov	w1, 0
	mov	x0, x21
	add	x19, x21, 12288
	ldr	x3, [x23, 96]
	add	x22, x19, 3976
	ldr	w25, [x20, 480]
	blr	x3
	str	w25, [x20, 480]
	mov	x0, x22
	add	x20, x19, 2656
	add	x25, x19, 3560
	bl	ResetVoQueue
	str	x24, [x21, 16]
	mov	x0, x21
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x21, 4]
	beq	.L549
	ldr	x3, [x23, 96]
	mov	w1, 0
	mov	x2, 904
	mov	x0, x20
	add	x19, x19, 2664
	blr	x3
	str	x25, [x20, 568]
	mov	w0, 1024
	str	x22, [x20, 600]
	str	w0, [x20, 596]
	mov	w0, 1
	stp	x19, x19, [x20, 128]
	stp	x19, x19, [x20, 144]
	ldr	x1, [x21, 16]
	str	wzr, [x1, 888]
.L548:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L549:
	ldr	x1, .LC271
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L548
	.size	AVSDEC_Init, .-AVSDEC_Init
	.align	3
.LC269:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC271:
	.xword	.LC270
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_Destroy
	.type	AVSDEC_Destroy, %function
AVSDEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	AVSDEC_Destroy, .-AVSDEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_RecycleImage
	.type	AVSDEC_RecycleImage, %function
AVSDEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L553
	ldr	w0, [x19, 4]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 4]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L554
	ldr	w0, [x19, 4]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 4]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L553:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L554:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVSDEC_RecycleImage, .-AVSDEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_GetRemainImg
	.type	AVSDEC_GetRemainImg, %function
AVSDEC_GetRemainImg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 12288
	bl	_mcount
	ldr	x0, [x20, 16]
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L562
	mov	w21, 3
	add	x19, x24, 2808
	mov	w23, -1
	add	x25, x24, 3976
.L561:
	ldr	x1, [x19]
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L558
	ldr	x1, [x19]
	mov	w23, 1
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L570
.L558:
	subs	w21, w21, #1
	sub	x19, x19, #8
	bne	.L561
	cbnz	w23, .L562
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L562:
	add	x0, x24, 3976
	bl	GetVoLastImageID
	mov	w23, w0
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L570:
	mov	x0, x20
	mov	w23, -1
	bl	AVS_SetImgFormat
	mov	w2, 1
	cmp	w21, w2
	beq	.L571
.L559:
	ldr	x1, [x19]
	ldr	w0, [x20, 4]
	ldr	w1, [x1, 12]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 4]
	mov	x4, x22
	mov	x3, x25
	mov	x2, x20
	mov	w1, 6
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	x0, x20
	beq	.L560
	ldr	w1, [x22, 148]
	bl	AVSDEC_RecycleImage
	ldr	w0, [x20, 4]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x20, 4]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L558
	.p2align 3
.L560:
	ldr	w0, [x22, 152]
	mov	w23, -1
	cmp	w0, 100
	bhi	.L558
	ldr	w0, [x22, 68]
	cmp	w0, 31
	bls	.L558
	ldr	w0, [x22, 72]
	cmp	w0, 31
	csetm	w23, ls
	b	.L558
.L571:
	str	w21, [x22, 180]
	b	.L559
	.size	AVSDEC_GetRemainImg, .-AVSDEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_GetImageBuffer
	.type	AVSDEC_GetImageBuffer, %function
AVSDEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 4]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w19, w0
	beq	.L573
	ldr	w0, [x20, 4]
	mov	w19, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L578
.L573:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L578:
	add	x1, x20, 12288
	ldr	w0, [x20, 4]
	add	x1, x1, 3976
	bl	FSP_ClearNotInVoQueue
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVSDEC_GetImageBuffer, .-AVSDEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearSlice
	.type	ClearSlice, %function
ClearSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	x20, x1
	add	x19, x1, 8
	add	x21, x1, 16
	bl	_mcount
.L581:
	ldr	w0, [x19]
	cmp	w0, wzr
	ble	.L580
	ldr	w0, [x19, -8]
	cbnz	w0, .L586
.L580:
	str	wzr, [x19, -8]
	add	x19, x19, 4
	str	wzr, [x19, -4]
	cmp	x19, x21
	str	wzr, [x20, 16]
	bne	.L581
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L586:
	ldr	w1, [x19, 12]
	mov	w0, w22
	bl	SM_ReleaseStreamSeg
	b	.L580
	.size	ClearSlice, .-ClearSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AVS_DecodeArbiter.part.4, %function
AVS_DecodeArbiter.part.4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x21, 16]
	ldr	w0, [x0, 8]
	cmp	w0, 4
	bls	.L616
.L609:
	mov	w1, 1
	add	x22, x21, 12288
.L588:
	str	w0, [x22, 3504]
	cbnz	w1, .L595
	add	x20, x21, 32
	ldr	w0, [x20, 14448]
	mov	w19, 0
	cmp	w0, wzr
	ble	.L608
	.p2align 2
.L610:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L610
.L608:
	str	wzr, [x20, 14448]
	mov	w0, 16383
	ldr	x2, .LC273
	movk	w0, 0xfffb, lsl 16
	ldr	w1, [x22, 2828]
	ldr	x4, [x2]
	and	w0, w1, w0
	str	w0, [x22, 2828]
	cbz	x4, .L615
	ldr	w0, [x21, 4]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L615:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L589:
	add	x22, x21, 12288
	ldr	w2, [x22, 3504]
	cmp	w2, 2
	bne	.L593
	str	wzr, [x22, 3508]
.L593:
	str	w0, [x22, 3504]
.L595:
	ldr	w0, [x22, 3948]
	cmp	w0, 1
	beq	.L617
	cmp	w0, 2
	bne	.L603
	ldr	w0, [x22, 3508]
	cmp	w0, 1
	ble	.L606
.L603:
	add	x1, x22, 3600
	mov	x2, 376
	add	x0, x22, 2844
	bl	memcpy
	ldrb	w4, [x22, 2925]
	mov	w0, 18
	ldr	w3, [x22, 3192]
	ldr	w2, [x22, 3520]
	ldr	x1, .LC275
	bl	dprint_vfmw
	ldr	w2, [x22, 2828]
	mov	w1, 16383
	movk	w1, 0xfffb, lsl 16
	mov	w0, 1
	and	w1, w2, w1
	str	w1, [x22, 2828]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L616:
	ldr	x1, .LC272
	ldrb	w1, [x1,w0,uxtw]
	adr	x2, .Lrtx590
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx590:
	.section	.rodata
	.align	0
	.align	2
.L590:
	.byte	(.L589 - .Lrtx590) / 4
	.byte	(.L591 - .Lrtx590) / 4
	.byte	(.L592 - .Lrtx590) / 4
	.byte	(.L609 - .Lrtx590) / 4
	.byte	(.L589 - .Lrtx590) / 4
	.text
	.p2align 3
.L592:
	add	x22, x21, 12288
	ldr	w1, [x22, 3948]
	cmp	w1, wzr
	cset	w1, eq
	b	.L588
	.p2align 3
.L591:
	add	x22, x21, 12288
	ldr	w2, [x22, 3504]
	cmp	w2, 2
	beq	.L618
.L594:
	ldr	w1, [x22, 3948]
	cmp	w1, 2
	cset	w1, ne
	b	.L588
	.p2align 3
.L617:
	ldr	w0, [x22, 3508]
	cmp	w0, wzr
	bgt	.L603
.L606:
	add	x20, x21, 32
	ldr	w0, [x20, 14448]
	mov	w19, 0
	cmp	w0, wzr
	ble	.L608
	.p2align 2
.L611:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L611
	b	.L608
	.p2align 3
.L618:
	str	wzr, [x22, 3508]
	b	.L594
	.size	AVS_DecodeArbiter.part.4, .-AVS_DecodeArbiter.part.4
	.align	3
.LC272:
	.xword	.L590
	.align	3
.LC273:
	.xword	g_event_report
	.align	3
.LC275:
	.xword	.LC274
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_DecodeArbiter
	.type	AVS_DecodeArbiter, %function
AVS_DecodeArbiter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 49152
	ldr	w1, [x19, 15116]
	movk	w0, 0x5, lsl 16
	and	w0, w1, w0
	cmp	w0, 376832
	beq	.L622
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L622:
	mov	x0, x19
	bl	AVS_DecodeArbiter.part.4
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_DecodeArbiter, .-AVS_DecodeArbiter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_VDMPostProc
	.type	AVSDEC_VDMPostProc, %function
AVSDEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x20, x21, 32
	bl	_mcount
	mov	w19, 0
	ldr	x1, [x21, 24]
	ldr	x0, [x21, 15072]
	ldrb	w2, [x1, 48]
	strb	w2, [x0]
	ldr	w1, [x1, 14904]
	str	w1, [x0, 4]
	ldr	w0, [x20, 14448]
	cmp	w0, wzr
	ble	.L628
	.p2align 2
.L668:
	sxtw	x3, w19
	ldr	w0, [x21, 4]
	lsl	x1, x3, 3
	add	w19, w19, 1
	sub	x1, x1, x3
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L668
.L628:
	ldr	x0, .LC276
	add	x19, x21, 12288
	add	x23, x19, 2844
	mov	x2, 14912
	mov	w1, 0
	str	wzr, [x20, 14448]
	ldr	x3, [x0, 96]
	mov	x0, x20
	blr	x3
	ldr	w0, [x23, 348]
	cbnz	w0, .L681
	str	w22, [x19, 3512]
	mov	w2, w22
	ldr	x0, [x21, 16]
	ldr	w3, [x0]
	cmp	w2, w3
	bgt	.L682
.L633:
	mov	x0, x21
	add	x20, x19, 2656
	bl	AVS_SetImgFormat
	ldr	x1, [x20, 128]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L683
	ldr	x1, [x20, 872]
	cbz	x1, .L636
	str	x1, [x0, 544]
.L636:
	ldr	x2, [x19, 3536]
	str	xzr, [x19, 3528]
	cbz	x2, .L637
	str	x2, [x0, 552]
.L637:
	add	x20, x19, 2656
	str	xzr, [x20, 880]
	ldr	w0, [x19, 3192]
	cmp	w0, 1
	bls	.L684
	ldr	x20, [x20, 128]
.L643:
	ldr	w1, [x20, 12]
	ldr	w0, [x21, 4]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L685
	add	x0, x19, 2664
	add	x19, x19, 2656
	cmp	x20, x0
	beq	.L648
	ldr	x0, [x21, 16]
	ldr	w2, [x19, 856]
	ldr	w3, [x0, 4]
	cmp	w3, w2
	bge	.L646
	ldr	x1, .LC281
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 12]
	mov	w2, 0
	ldr	w0, [x21, 4]
	bl	FSP_SetDisplay
	ldr	x1, [x22, 544]
	cbnz	x1, .L686
.L647:
	ldr	x1, [x22, 552]
	cbnz	x1, .L687
.L648:
	mov	w19, 1
.L631:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L646:
	mov	x1, x21
	mov	x0, x20
	bl	AVS_OutputOneFrame
	mov	w19, w0
	cbnz	w0, .L648
	ldr	x1, [x22, 544]
	cbnz	x1, .L688
.L649:
	ldr	x1, [x22, 552]
	cbz	x1, .L631
	ldr	w0, [x21, 4]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L631
	.p2align 3
.L681:
	add	x20, x19, 2656
	ldr	x1, [x20, 136]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L689
	ldr	x2, [x20, 144]
	ldr	w24, [x0, 152]
	ldr	w0, [x21, 4]
	ldr	w1, [x2, 12]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L690
	ldr	w2, [x0, 152]
	mov	w0, 100
	add	w2, w24, w2
	add	w2, w2, w22
	cmp	w2, w0
	csel	w2, w2, w0, le
	str	w2, [x20, 856]
	ldr	w0, [x23, 348]
	cmp	w0, 2
	beq	.L633
	ldr	x0, [x21, 16]
	ldr	w3, [x0]
	cmp	w2, w3
	ble	.L633
	.p2align 2
.L682:
	ldr	x1, .LC279
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 3508]
	ldr	x0, [x19, 2792]
	ldr	w1, [x0, 12]
	ldr	w0, [x21, 4]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L634
	ldr	x1, [x19, 2784]
	mov	w2, 1
	ldr	w0, [x21, 4]
	add	x23, x19, 2664
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x19, 2792]
	mov	w2, 1
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x19, 2800]
	mov	w2, 1
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	x1, [x19, 2808]
	mov	w2, 1
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_ClearLogicFs
	ldr	w0, [x21, 4]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	ldr	w0, [x21, 4]
	ldr	x1, [x22, 552]
	bl	FreeUsdByDec
	ldr	w0, [x21, 4]
	ldr	x1, [x22, 560]
	bl	FreeUsdByDec
	ldr	w0, [x21, 4]
	ldr	x1, [x22, 568]
	bl	FreeUsdByDec
	add	x0, x22, 512
	add	x1, x19, 2560
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	stp	x23, x23, [x1, 224]
	stp	x23, x23, [x1, 240]
	ldr	w0, [x21, 4]
	bl	FSP_GetNullLogicFs
	str	w0, [x23, 12]
.L634:
	str	wzr, [x19, 3508]
	mov	w19, 0
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L687:
	ldr	w0, [x21, 4]
	mov	w19, 1
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L631
	.p2align 3
.L684:
	ldr	w2, [x20, 852]
	cmp	w2, 1
	csinc	w2, w2, w2, gt
	str	w2, [x20, 852]
	ldrb	w1, [x19, 2925]
	cmp	w1, 1
	ccmp	w0, wzr, 0, ne
	beq	.L640
	ldr	x1, [x20, 128]
	mov	w2, 1
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 12]
	bl	FSP_SetRef
	ldr	x0, [x20, 152]
	add	x1, x19, 2664
	cmp	x0, x1
	beq	.L641
	ldr	w1, [x0, 12]
	mov	w2, 0
	ldr	w0, [x21, 4]
	bl	FSP_SetRef
.L641:
	ldr	x2, [x19, 2792]
	ldr	x3, [x19, 2800]
	ldr	x1, [x19, 2784]
	str	x1, [x19, 2792]
	str	x2, [x19, 2800]
	str	x3, [x19, 2808]
.L640:
	ldr	x0, [x21, 16]
	ldr	w0, [x0, 24]
	cbnz	w0, .L642
	ldr	x20, [x19, 2800]
	b	.L643
.L642:
	ldr	x20, [x19, 2784]
	b	.L643
.L686:
	ldr	w0, [x21, 4]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	b	.L647
.L688:
	ldr	w0, [x21, 4]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	b	.L649
.L683:
	ldr	x1, .LC277
	mov	w2, 3297
	mov	w19, 0
	bl	dprint_vfmw
	b	.L631
.L685:
	ldr	x1, .LC277
	mov	w2, 3337
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	b	.L631
.L689:
	ldr	x1, .LC277
	mov	w2, 3272
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	b	.L631
.L690:
	ldr	x1, .LC277
	mov	w2, 3276
	mov	w19, 0
	bl	dprint_vfmw
	b	.L631
	.size	AVSDEC_VDMPostProc, .-AVSDEC_VDMPostProc
	.align	3
.LC276:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC277:
	.xword	.LC249
	.align	3
.LC279:
	.xword	.LC278
	.align	3
.LC281:
	.xword	.LC280
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_ClearCurPic
	.type	AVS_ClearCurPic, %function
AVS_ClearCurPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 32
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x20, 14448]
	cmp	w0, wzr
	ble	.L694
	.p2align 2
.L695:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w0, w19
	bgt	.L695
.L694:
	str	wzr, [x20, 14448]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS_ClearCurPic, .-AVS_ClearCurPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearPacket
	.type	ClearPacket, %function
ClearPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 16384
	bl	_mcount
	ldr	w0, [x20, 4]
	ldr	w1, [x19, 516]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 505]
	cbnz	w0, .L699
	ldrb	w0, [x19, 585]
	cmp	w0, 1
	beq	.L703
.L699:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L703:
	ldr	w0, [x19, 588]
	cbz	w0, .L699
	ldr	w1, [x19, 596]
	ldr	w0, [x20, 4]
	bl	SM_ReleaseStreamSeg
	b	.L699
	.size	ClearPacket, .-ClearPacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteAvsSliceMsg
	.type	WriteAvsSliceMsg, %function
WriteAvsSliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x4, x19, 32
	ldr	w2, [x4, 14448]
	cmp	w2, 511
	bgt	.L713
	cmp	w2, wzr
	ble	.L707
	sub	w1, w2, #1
	ldr	x5, [x19, 16880]
	ldr	w0, [x19, 15912]
	sxtw	x1, w1
	lsl	x3, x1, 3
	add	w0, w0, 15
	sub	x1, x3, x1
	ldrb	w3, [x5, 3]
	lsr	w0, w0, 4
	add	x1, x4, x1, lsl 2
	mul	w0, w0, w3
	ldr	w3, [x1, 128]
	cmp	w0, w3
	bls	.L714
.L707:
	sxtw	x7, w2
	add	x3, x19, 16384
	lsl	x1, x7, 3
	sub	x1, x1, x7
	ldr	w0, [x3, 508]
	add	x1, x4, x1, lsl 2
	str	w0, [x1, 112]
	ldr	w0, [x3, 516]
	str	w0, [x1, 132]
	ldr	w0, [x3, 512]
	str	w0, [x1, 120]
	cbnz	w2, .L708
	str	wzr, [x4, 128]
.L709:
	ldrb	w0, [x3, 505]
	cmp	w0, 1
	lsl	x0, x7, 3
	beq	.L715
	sub	x7, x0, x7
	ldr	w1, [x3, 588]
	add	x7, x4, x7, lsl 2
	str	w1, [x7, 116]
	ldr	w0, [x3, 596]
	str	w0, [x7, 136]
	ldr	w0, [x3, 592]
	str	w0, [x7, 124]
.L711:
	add	w2, w2, 1
	str	w2, [x4, 14448]
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L708:
	ldr	x6, [x19, 16880]
	ldr	w0, [x19, 15912]
	ldrb	w6, [x6, 3]
	add	w0, w0, 15
	lsr	w0, w0, 4
	mul	w6, w0, w6
	str	w6, [x1, 128]
	mov	w0, 0
	ldr	w1, [x19, 15156]
	ldr	w8, [x19, 15160]
	add	w1, w1, 15
	add	w8, w8, 15
	lsr	w5, w1, 4
	lsr	w1, w8, 4
	mul	w1, w5, w1
	sub	w1, w1, #1
	cmp	w6, w1
	bls	.L709
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L713:
	ldr	x1, .LC283
	mov	w3, 512
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L714:
	ldr	x1, .LC285
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearPacket
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L715:
	sub	x7, x0, x7
	add	x7, x4, x7, lsl 2
	str	wzr, [x7, 116]
	str	wzr, [x7, 124]
	str	wzr, [x7, 136]
	b	.L711
	.size	WriteAvsSliceMsg, .-WriteAvsSliceMsg
	.align	3
.LC283:
	.xword	.LC282
	.align	3
.LC285:
	.xword	.LC284
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_GetPacketState
	.type	AVS_GetPacketState, %function
AVS_GetPacketState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 16384
	bl	_mcount
	ldr	w0, [x19, 488]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS_GetPacketState, .-AVS_GetPacketState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Avs_Vfmw_WQMatrix
	.type	Avs_Vfmw_WQMatrix, %function
Avs_Vfmw_WQMatrix:
	stp	x29, x30, [sp, -352]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	str	xzr, [x29, 40]
	ldr	w8, [x19, 148]
	str	wzr, [x29, 48]
	cmp	w8, 1
	str	xzr, [x29, 56]
	str	wzr, [x29, 64]
	ldr	w6, [x19, 132]
	beq	.L719
	cmp	w8, 3
	ccmp	w6, wzr, 0, eq
	beq	.L719
	cmp	w8, 2
	beq	.L790
.L723:
	cbz	w6, .L725
	mov	w0, 128
	strh	w0, [x29, 72]
	strh	w0, [x29, 74]
	strh	w0, [x29, 76]
	strh	w0, [x29, 78]
	strh	w0, [x29, 80]
	strh	w0, [x29, 82]
	strh	w0, [x29, 84]
	strh	w0, [x29, 86]
	strh	w0, [x29, 88]
	strh	w0, [x29, 90]
	strh	w0, [x29, 92]
	strh	w0, [x29, 94]
	cbnz	w8, .L791
	ldr	x3, .LC286
	add	x1, x29, 84
	add	x0, x3, 12
	add	x3, x3, 24
	.p2align 2
.L739:
	ldrh	w2, [x0], 2
	strh	w2, [x1], 2
	cmp	x0, x3
	bne	.L739
.L734:
	add	x3, x19, 204
	add	x2, x19, 332
	mov	x0, x3
	mov	w1, 128
	.p2align 2
.L731:
	strh	w1, [x0], 2
	cmp	x0, x2
	bne	.L731
	ldr	w0, [x19, 128]
	cbz	w0, .L743
	ldr	x6, .LC287
	mov	w9, 0
	ldr	w0, [x19, 152]
	add	x6, x6, 16
	add	x6, x6, x0, lsl 6
.L744:
	uxtw	x5, w9
	mov	w1, 0
	lsl	x0, x5, 2
	lsl	x7, x5, 6
	sub	x5, x0, x5
	lsl	x5, x5, 1
	.p2align 2
.L752:
	add	w4, w1, 8
	.p2align 2
.L750:
	uxtw	x0, w1
	add	x10, x29, 352
	add	x2, x7, x0
	add	w1, w1, 1
	cmp	w1, w4
	ldrb	w0, [x6, x0]
	add	x2, x10, x2, lsl 1
	add	x0, x5, x0
	add	x0, x10, x0, lsl 1
	sub	x0, x0, #4096
	ldrh	w0, [x0, 3816]
	strh	w0, [x2, -256]
	bne	.L750
	cmp	w1, 64
	bne	.L752
	add	w9, w9, 1
	cmp	w9, 2
	bne	.L744
	cbnz	w8, .L753
.L795:
	add	x0, x29, 224
	add	x2, x29, 352
	.p2align 2
.L754:
	ldrh	w1, [x0], 2
	strh	w1, [x3], 2
	cmp	x2, x0
	bne	.L754
.L717:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 352
	ret
.L725:
	ldr	x0, .LC286
	mov	x1, 0
	add	x4, x29, 72
	.p2align 2
.L728:
	ldrh	w2, [x0, x1]
	strh	w2, [x4, x1]
	add	x1, x1, 2
	cmp	x1, 12
	bne	.L728
	add	x6, x4, 12
	add	x1, x0, 12
	mov	x2, x6
	add	x0, x0, 24
	.p2align 2
.L729:
	ldrh	w3, [x1], 2
	strh	w3, [x2], 2
	cmp	x1, x0
	bne	.L729
	cbz	w8, .L734
	cmp	w8, 1
	beq	.L792
	cmp	w8, 2
	beq	.L793
	cmp	w8, 3
	bne	.L734
	mov	x0, 0
	add	x5, x29, 40
.L737:
	ldrh	w1, [x5, x0]
	strh	w1, [x4, x0]
	add	x0, x0, 2
	cmp	x0, 12
	bne	.L737
	mov	x0, 0
	add	x5, x29, 56
.L738:
	ldrh	w1, [x5, x0]
	add	x0, x0, 2
	strh	w1, [x6], 2
	cmp	x0, 12
	bne	.L738
	b	.L734
.L791:
	cmp	w8, 1
	beq	.L794
	cmp	w8, 2
	bne	.L734
	add	x1, x29, 84
	mov	x0, 0
	add	x5, x29, 56
.L742:
	ldrh	w2, [x5, x0]
	add	x0, x0, 2
	strh	w2, [x1], 2
	cmp	x0, 12
	bne	.L742
	b	.L734
	.p2align 3
.L743:
	mov	w6, 0
	mov	w5, 128
.L747:
	mov	w0, 0
	ubfiz	x4, x6, 6, 32
	.p2align 2
.L749:
	add	w2, w0, 8
	.p2align 2
.L745:
	add	x1, x4, x0, uxtw
	add	x7, x29, 352
	add	w0, w0, 1
	add	x1, x7, x1, lsl 1
	cmp	w2, w0
	strh	w5, [x1, -256]
	bne	.L745
	cmp	w2, 64
	mov	w0, w2
	bne	.L749
	add	w6, w6, 1
	cmp	w6, 2
	bne	.L747
	cbz	w8, .L795
.L753:
	cmp	w8, 1
	beq	.L796
	cmp	w8, 2
	bne	.L717
	add	x0, x29, 224
	add	x2, x29, 352
	.p2align 2
.L758:
	ldrh	w1, [x0], 2
	strh	w1, [x3], 2
	cmp	x2, x0
	bne	.L758
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 352
	ret
.L719:
	ldr	x0, .LC286
	add	x3, x19, 156
	mov	x1, 0
	add	x5, x29, 40
	.p2align 2
.L721:
	ldrh	w2, [x0, x1]
	ldr	w4, [x3], 4
	add	w2, w4, w2
	strh	w2, [x5, x1]
	add	x1, x1, 2
	cmp	x1, 12
	bne	.L721
	cmp	w8, 2
	beq	.L722
	cmp	w8, 3
	ccmp	w6, wzr, 0, eq
	bne	.L723
.L722:
	add	x3, x19, 180
	add	x0, x0, 12
	mov	x1, 0
	add	x5, x29, 56
	.p2align 2
.L724:
	ldr	w4, [x3], 4
	ldrh	w2, [x0], 2
	add	w2, w4, w2
	strh	w2, [x5, x1]
	add	x1, x1, 2
	cmp	x1, 12
	bne	.L724
	b	.L723
.L790:
	ldr	x0, .LC286
	b	.L722
.L794:
	mov	x0, 0
	add	x5, x29, 40
	add	x4, x29, 72
.L741:
	ldrh	w1, [x5, x0]
	strh	w1, [x4, x0]
	add	x0, x0, 2
	cmp	x0, 12
	bne	.L741
	b	.L734
.L792:
	mov	x0, 0
	add	x5, x29, 40
.L733:
	ldrh	w1, [x5, x0]
	strh	w1, [x4, x0]
	add	x0, x0, 2
	cmp	x0, 12
	bne	.L733
	b	.L734
.L796:
	add	x0, x29, 96
	add	x2, x0, 128
	.p2align 2
.L756:
	ldrh	w1, [x0], 2
	strh	w1, [x3], 2
	cmp	x2, x0
	bne	.L756
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 352
	ret
.L793:
	mov	x0, 0
	add	x5, x29, 56
.L736:
	ldrh	w1, [x5, x0]
	add	x0, x0, 2
	strh	w1, [x6], 2
	cmp	x0, 12
	bne	.L736
	b	.L734
	.size	Avs_Vfmw_WQMatrix, .-Avs_Vfmw_WQMatrix
	.align	3
.LC286:
	.xword	.LANCHOR2
	.align	3
.LC287:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS_ParseHeader
	.type	AVS_ParseHeader, %function
AVS_ParseHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	add	x21, x20, 16384
	add	x23, x19, 2656
	bl	_mcount
	mov	w1, 32
	add	x24, x19, 3600
	ldr	x22, [x23, 568]
	str	wzr, [x21, 488]
	mov	x0, x22
	bl	BsShow
	uxtb	w0, w0
	sub	w1, w0, #176
	cmp	w1, 78
	bls	.L847
.L798:
	cmp	w0, 175
	bhi	.L841
	ldr	w1, [x19, 2828]
	mov	w0, 327680
	add	x19, x19, 2656
	and	w0, w1, w0
	cmp	w0, 327680
	beq	.L848
.L841:
	mov	x0, x20
	bl	ClearPacket
.L840:
	mov	w0, 1
.L810:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L847:
	ldr	x2, .LC290
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx800
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx800:
	.section	.rodata
	.align	0
	.align	2
.L800:
	.byte	(.L799 - .Lrtx800) / 4
	.byte	(.L801 - .Lrtx800) / 4
	.byte	(.L802 - .Lrtx800) / 4
	.byte	(.L803 - .Lrtx800) / 4
	.byte	(.L841 - .Lrtx800) / 4
	.byte	(.L805 - .Lrtx800) / 4
	.byte	(.L806 - .Lrtx800) / 4
	.byte	(.L807 - .Lrtx800) / 4
	.byte	(.L841 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L798 - .Lrtx800) / 4
	.byte	(.L808 - .Lrtx800) / 4
	.text
	.p2align 3
.L803:
	add	x19, x19, 2656
	ldr	w0, [x19, 172]
	tbnz	x0, 15, .L838
	tbz	x0, 18, .L813
	mov	w2, 16383
	mov	x1, x24
	movk	w2, 0xfffb, lsl 16
	and	w2, w0, w2
	mov	x0, x23
	str	w2, [x19, 172]
	bl	AVS_i_picture_header
	b	.L844
	.p2align 3
.L805:
	ldr	w1, [x19, 2828]
	mov	w0, 327680
	tst	w1, w0
	beq	.L845
	mov	x1, x24
	mov	x0, x23
	bl	AVS_extension
	mov	x0, x20
	bl	ClearPacket
	mov	w0, 1
	b	.L810
	.p2align 3
.L806:
	add	x19, x19, 2656
	ldr	w0, [x19, 172]
	tbnz	x0, 15, .L838
	tbz	x0, 18, .L815
	mov	w2, 16383
	mov	x1, x24
	movk	w2, 0xfffb, lsl 16
	and	w2, w0, w2
	mov	x0, x23
	str	w2, [x19, 172]
	bl	AVS_pb_picture_header
.L844:
	mov	x0, x24
	bl	Avs_Vfmw_WQMatrix
.L845:
	mov	x0, x20
	bl	ClearPacket
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L807:
	add	x19, x19, 2656
	ldr	w1, [x19, 172]
	tbnz	x1, 15, .L842
	mov	w0, 327680
	tst	w1, w0
	beq	.L840
.L846:
	mov	w2, 16383
	mov	x0, x20
	movk	w2, 0xfffb, lsl 16
	and	w1, w1, w2
	str	w1, [x19, 172]
	bl	ClearPacket
	mov	w0, 0
	b	.L810
	.p2align 3
.L801:
	add	x19, x19, 2656
	ldr	w1, [x19, 172]
	tbnz	x1, 15, .L842
	mov	w0, 327680
	tst	w1, w0
	beq	.L841
	b	.L846
	.p2align 3
.L799:
	add	x19, x19, 2656
	ldr	w2, [x19, 172]
	tbnz	x2, 15, .L849
	tbz	x2, 16, .L811
	mov	w0, 16383
	mov	x1, x24
	movk	w0, 0xfffb, lsl 16
	and	w2, w2, w0
	mov	x0, x20
	str	w2, [x19, 172]
	bl	AVS_sequence_header
	mov	x0, x20
	bl	ClearPacket
	mov	w0, 0
	b	.L810
	.p2align 3
.L808:
	mov	w1, 32
	mov	x0, x22
	bl	BsSkip
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w23, w0
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w23, w2
	ccmp	w0, w1, 0, eq
	bne	.L845
	add	x2, x19, 2656
	mov	w0, 1
	strb	w0, [x20]
	mov	w19, 1
	str	w19, [x21, 488]
	mov	x0, x20
	ldr	w1, [x2, 172]
	orr	w1, w1, 16384
	str	w1, [x2, 172]
	bl	ClearPacket
	mov	w0, w19
	b	.L810
	.p2align 3
.L802:
	ldr	w0, [x19, 2828]
	mov	w1, 1
	tbnz	x0, 18, .L839
	tbz	x0, 16, .L845
	mov	w1, 0
.L839:
	mov	x0, x20
	bl	AVS_user_data
	b	.L841
	.p2align 3
.L842:
	mov	w0, 1
	str	w0, [x21, 488]
	orr	w1, w1, 16384
	str	w1, [x19, 172]
	b	.L810
	.p2align 3
.L815:
	mov	x1, x24
	mov	x0, x23
	bl	AVS_pb_picture_header
.L843:
	mov	x0, x24
	bl	Avs_Vfmw_WQMatrix
	mov	x0, x20
	bl	ClearPacket
	mov	w0, 1
	b	.L810
	.p2align 3
.L813:
	mov	x1, x24
	mov	x0, x23
	bl	AVS_i_picture_header
	b	.L843
	.p2align 3
.L811:
	mov	x1, x24
	mov	x0, x20
	bl	AVS_sequence_header
	mov	x0, x20
	bl	ClearPacket
	mov	w0, 1
	b	.L810
.L848:
	orr	w1, w1, 32768
	mov	x0, x20
	str	w1, [x19, 172]
	bl	WriteAvsSliceMsg
	cbnz	w0, .L840
	b	.L845
	.p2align 3
.L838:
	mov	w20, 1
	str	w20, [x21, 488]
	orr	w1, w0, 16384
	mov	x0, x24
	str	w1, [x19, 172]
	bl	Avs_Vfmw_WQMatrix
	mov	w0, w20
	b	.L810
	.p2align 3
.L849:
	mov	w0, 1
	str	w0, [x21, 488]
	orr	w2, w2, 16384
	str	w2, [x19, 172]
	b	.L810
	.size	AVS_ParseHeader, .-AVS_ParseHeader
	.align	3
.LC290:
	.xword	.L800
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVSDEC_Decode
	.type	AVSDEC_Decode, %function
AVSDEC_Decode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x19, x1
	mov	x0, x30
	add	x22, x21, 12288
	add	x20, x22, 2656
	bl	_mcount
	ldr	w2, [x19, 16]
	add	x0, x22, 3560
	ldr	x1, [x19]
	bl	BsInit
	ldr	x3, .LC291
	add	x0, x21, 16384
	mov	x2, 160
	mov	x1, x19
	add	x0, x0, 496
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w0, [x20, 172]
	str	w0, [x20, 900]
	mov	x0, x21
	bl	AVS_ParseHeader
	cbz	w0, .L873
	mov	w0, 49152
	ldr	w1, [x20, 172]
	movk	w0, 0x5, lsl 16
	and	w0, w1, w0
	cmp	w0, 376832
	beq	.L856
.L857:
	mov	w2, 0
.L853:
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L873:
	ldr	x1, .LC293
	add	x20, x21, 32
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 14448]
	cmp	w0, wzr
	ble	.L855
	.p2align 2
.L866:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L866
.L855:
	mov	w2, 0
	str	wzr, [x20, 14448]
.L875:
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L856:
	mov	x0, x21
	bl	AVS_DecodeArbiter.part.4
	cbz	w0, .L857
	mov	x0, x21
	bl	AVS_GetStreamInf
	cmp	w0, 3
	beq	.L858
	cbnz	w0, .L874
	ldr	x1, .LC295
	add	x20, x21, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 14448]
	cmp	w0, wzr
	ble	.L855
	mov	w19, 0
	.p2align 2
.L861:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L861
	mov	w2, 0
	str	wzr, [x20, 14448]
	b	.L875
	.p2align 3
.L874:
	mov	x0, x21
	bl	AVS_StartDecode
	mov	w2, 1
	cbnz	w0, .L853
	ldr	x1, .LC297
	add	x20, x21, 32
	mov	w0, w2
	bl	dprint_vfmw
	ldr	w0, [x20, 14448]
	cmp	w0, wzr
	ble	.L855
	mov	w19, 0
	.p2align 2
.L862:
	sxtw	x2, w19
	ldr	w0, [x21, 4]
	lsl	x1, x2, 3
	add	w19, w19, 1
	sub	x1, x1, x2
	add	x1, x20, x1, lsl 2
	add	x1, x1, 112
	bl	ClearSlice
	ldr	w0, [x20, 14448]
	cmp	w19, w0
	blt	.L862
	b	.L855
	.p2align 3
.L858:
	ldr	w1, [x20, 900]
	mov	w2, w0
	str	w1, [x20, 172]
	b	.L853
	.size	AVSDEC_Decode, .-AVSDEC_Decode
	.align	3
.LC291:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC293:
	.xword	.LC292
	.align	3
.LC295:
	.xword	.LC294
	.align	3
.LC297:
	.xword	.LC296
	.global	g_tmp
	.global	wq_param_default
	.global	g_AvsCfg
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	24551
	.word	24576
	.word	25600
	.word	30689
	.word	30720
	.word	51200
	.word	61378
	.word	61440
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.align	3
.LANCHOR1 = . + 0
	.type	CSWTCH.58, %object
	.size	CSWTCH.58, 16
CSWTCH.58:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	WeightQuantModel, %object
	.size	WeightQuantModel, 256
WeightQuantModel:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	1
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.data
	.align	3
.LANCHOR2 = . + 0
	.type	wq_param_default, %object
	.size	wq_param_default, 24
wq_param_default:
	.hword	135
	.hword	143
	.hword	143
	.hword	160
	.hword	160
	.hword	213
	.hword	128
	.hword	98
	.hword	106
	.hword	116
	.hword	116
	.hword	128
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"%-40s     %#-8x(%db)\n" )
	.zero	2
.LC4:
	ASCII(.string	"video_sequence_start_code" )
	.zero	6
.LC6:
	ASCII(.string	"profile_id" )
	.zero	5
.LC8:
	ASCII(.string	"level_id" )
	.zero	7
.LC10:
	ASCII(.string	"progressive_sequence" )
	.zero	3
.LC12:
	ASCII(.string	"horizontal_size" )
.LC14:
	ASCII(.string	"vertical_size" )
	.zero	2
.LC16:
	ASCII(.string	"chroma_format" )
	.zero	2
.LC18:
	ASCII(.string	"sample_precision" )
	.zero	7
.LC20:
	ASCII(.string	"aspect_ratio" )
	.zero	3
.LC22:
	ASCII(.string	"frame_rate_code" )
.LC24:
	ASCII(.string	"bit_rate_lower" )
	.zero	1
.LC26:
	ASCII(.string	"marker_bit" )
	.zero	5
.LC28:
	ASCII(.string	"bit_rate_upper" )
	.zero	1
.LC30:
	ASCII(.string	"low_delay" )
	.zero	6
.LC32:
	ASCII(.string	"bbv_buffer_size" )
.LC34:
	ASCII(.string	"reserved_bits" )
	.zero	2
.LC41:
	ASCII(.string	"i_picture_start_code" )
	.zero	3
.LC43:
	ASCII(.string	"bbv_delay" )
	.zero	6
.LC46:
	ASCII(.string	"bbv_delay_extension" )
	.zero	4
.LC48:
	ASCII(.string	"time_code_flag" )
	.zero	1
.LC50:
	ASCII(.string	"time_code" )
	.zero	6
.LC52:
	ASCII(.string	"picture_distance" )
	.zero	7
.LC54:
	ASCII(.string	"bbv_check_times" )
.LC56:
	ASCII(.string	"progressive_frame" )
	.zero	6
.LC58:
	ASCII(.string	"picture_structure" )
	.zero	6
.LC60:
	ASCII(.string	"top_field_first" )
.LC62:
	ASCII(.string	"repeat_first_field" )
	.zero	5
.LC64:
	ASCII(.string	"fixed_picture_qp" )
	.zero	7
.LC66:
	ASCII(.string	"picture_qp" )
	.zero	5
.LC68:
	ASCII(.string	"skip_mode_flag" )
	.zero	1
.LC71:
	ASCII(.string	"loop_filter_disable" )
	.zero	4
.LC73:
	ASCII(.string	"loop_filter_parameter_flag" )
	.zero	5
.LC75:
	ASCII(.string	"alpha_c_offset" )
	.zero	1
.LC77:
	ASCII(.string	"beta_offset" )
	.zero	4
.LC79:
	ASCII(.string	"weighting_quant_flag" )
	.zero	3
.LC81:
	ASCII(.string	"aec_enable" )
	.zero	5
.LC83:
	ASCII(.string	"mb_adapt_weighting_quant_disable" )
	.zero	7
.LC85:
	ASCII(.string	"chroma_quant_param_disable" )
	.zero	5
.LC87:
	ASCII(.string	"chroma_quant_param_delta_u" )
	.zero	5
.LC89:
	ASCII(.string	"chroma_quant_param_delta_v" )
	.zero	5
.LC91:
	ASCII(.string	"weighting_quant_param_index" )
	.zero	4
.LC93:
	ASCII(.string	"weighting_quant_model" )
	.zero	2
.LC95:
	ASCII(.string	"weighting_quant_param_deltal1" )
	.zero	2
.LC97:
	ASCII(.string	"weighting_quant_param_deltal2" )
	.zero	2
.LC100:
	ASCII(.string	"pb_picture_start_code" )
	.zero	2
.LC105:
	ASCII(.string	"picture_coding_type" )
	.zero	4
.LC111:
	ASCII(.string	"advanced_pred_mode_disable" )
	.zero	5
.LC117:
	ASCII(.string	"picture_reference_flag" )
	.zero	1
.LC119:
	ASCII(.string	"no_forward_reference_flag" )
	.zero	6
.LC121:
	ASCII(.string	"b_filed_enhanced_flag" )
	.zero	2
.LC123:
	ASCII(.string	"p_filed_enhanced_flag" )
	.zero	2
.LC141:
	ASCII(.string	"user_data_start_code" )
	.zero	3
.LC145:
	ASCII(.string	"extension_ID" )
	.zero	3
.LC147:
	ASCII(.string	"video_format" )
	.zero	3
.LC149:
	ASCII(.string	"sample_range" )
	.zero	3
.LC151:
	ASCII(.string	"colour_description" )
	.zero	5
.LC153:
	ASCII(.string	"colour_primaries" )
	.zero	7
.LC155:
	ASCII(.string	"transfer_characteristics" )
	.zero	7
.LC157:
	ASCII(.string	"matrix_coefficients" )
	.zero	4
.LC159:
	ASCII(.string	"display_horizontal_size" )
.LC162:
	ASCII(.string	"display_vertical_size" )
	.zero	2
.LC166:
	ASCII(.string	"copyright_flag" )
	.zero	1
.LC168:
	ASCII(.string	"copyright_id" )
	.zero	3
.LC170:
	ASCII(.string	"original_or_copy" )
	.zero	7
.LC174:
	ASCII(.string	"copyright_number_1" )
	.zero	5
.LC176:
	ASCII(.string	"copyright_number_2" )
	.zero	5
.LC178:
	ASCII(.string	"copyright_number_3" )
	.zero	5
.LC182:
	ASCII(.string	"camera_id" )
	.zero	6
.LC185:
	ASCII(.string	"height_of_image_device" )
	.zero	1
.LC187:
	ASCII(.string	"focal_length" )
	.zero	3
.LC189:
	ASCII(.string	"f_number" )
	.zero	7
.LC191:
	ASCII(.string	"vertical_angle_of_view" )
	.zero	1
.LC193:
	ASCII(.string	"camera_position_x_upper" )
.LC195:
	ASCII(.string	"camera_position_x_lower" )
.LC197:
	ASCII(.string	"camera_position_y_upper" )
.LC199:
	ASCII(.string	"camera_position_y_lower" )
.LC201:
	ASCII(.string	"camera_position_z_upper" )
.LC203:
	ASCII(.string	"camera_position_z_lower" )
.LC205:
	ASCII(.string	"camera_direction_x" )
	.zero	5
.LC207:
	ASCII(.string	"camera_direction_y" )
	.zero	5
.LC209:
	ASCII(.string	"camera_direction_z" )
	.zero	5
.LC211:
	ASCII(.string	"image_plane_vertical_x" )
	.zero	1
.LC213:
	ASCII(.string	"image_plane_vertical_y" )
	.zero	1
.LC215:
	ASCII(.string	"image_plane_vertical_z" )
	.zero	1
.LC218:
	ASCII(.string	"frame_centre_horizontal_offset" )
	.zero	1
.LC221:
	ASCII(.string	"frame_centre_vertical_offset" )
	.zero	3
.LC223:
	ASCII(.string	"extension_start_code" )
	.zero	3
.LC226:
	ASCII(.string	"ERROR: image size abnormal(%dx%d)\n" )
	.zero	5
.LC228:
	ASCII(.string	"avs actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC231:
	ASCII(.string	"ERROR: partition fs memory fail!\n" )
	.zero	6
.LC233:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC237:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC240:
	ASCII(.string	"line: %d pImage is null\n" )
	.zero	7
.LC242:
	ASCII(.string	"ERROR: get frame store fail!\n" )
	.zero	2
.LC245:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC247:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC249:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC251:
	ASCII(.string	"ERROR: AVS_OutputOneFrame is err(%d)\n" )
	.zero	2
.LC255:
	ASCII(.string	"size change\n" )
	.zero	3
.LC257:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC260:
	ASCII(.string	"MbWidth = %d, MbHeight = %d, don't support!\n" )
	.zero	3
.LC262:
	ASCII(.string	"ERROR: allocate vhb\n" )
	.zero	3
.LC264:
	ASCII(.string	"ERROR: get img buf err\n" )
.LC267:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC270:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC274:
	ASCII(.string	"-----Pic %5d, type %d, struct %d-----\n" )
	.zero	1
.LC278:
	ASCII(.string	"ERROR: err_level(%d) over ref_thr(%d)\n" )
	.zero	1
.LC280:
	ASCII(.string	"ERROR: err_level(%d) over out_thr(%d)\n" )
	.zero	1
.LC282:
	ASCII(.string	"SlcNum %d > %d Write slice msg failed\n" )
	.zero	1
.LC284:
	ASCII(.string	"This slice's start mbn %d <= LastSliceFirstMb %d, Write slice msg failed\n" )
	.zero	6
.LC292:
	ASCII(.string	"ERROR: paseHeader err\n" )
	.zero	1
.LC294:
	ASCII(.string	"ERROR: AVS_PrepareDecode err\n" )
	.zero	2
.LC296:
	ASCII(.string	"ERROR: AVS_StartDecode err\n" )
	.bss
	.align	3
	.type	g_tmp, %object
	.size	g_tmp, 1024
g_tmp:
	.zero	1024
	.type	g_AvsCfg, %object
	.size	g_AvsCfg, 508
g_AvsCfg:
	.zero	508
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
