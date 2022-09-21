#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"mpeg2.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	MP2_SearchStartCode.part.3, %function
MP2_SearchStartCode.part.3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x4, x20, x19, sxtw
	add	x2, x20, 2
	.p2align 2
.L12:
	cmp	x4, x2
	bls	.L2
.L15:
	ldrb	w3, [x2]
	cmp	w3, 1
	bls	.L14
.L8:
	add	x2, x2, 3
	cmp	x4, x2
	bhi	.L15
.L2:
	sub	w0, w19, #3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L14:
	cbnz	w3, .L5
	ldrb	w3, [x2, -1]
	cbnz	w3, .L6
	add	x2, x2, 1
	b	.L12
	.p2align 3
.L5:
	bne	.L12
	ldrb	w0, [x2, -2]
	cbnz	w0, .L8
	ldrb	w0, [x2, -1]
	cbnz	w0, .L8
	sub	x2, x2, x20
	sub	w0, w2, #2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L6:
	ldrb	w1, [x2, 1]
	add	x0, x2, 2
	add	x2, x2, 4
	cmp	w1, wzr
	csel	x2, x2, x0, ne
	b	.L12
	.size	MP2_SearchStartCode.part.3, .-MP2_SearchStartCode.part.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_VerifyMemPara
	.type	MP2_VerifyMemPara, %function
MP2_VerifyMemPara:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	MP2_VerifyMemPara, .-MP2_VerifyMemPara
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ArrangeVHBMem
	.type	MP2_ArrangeVHBMem, %function
MP2_ArrangeVHBMem:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 86016
	bl	_mcount
	ldr	x0, [x20, 2232]
	ldp	w2, w3, [x0, 56]
	cmp	w2, 31
	bls	.L19
	mov	w1, 8160
	sub	w4, w3, #32
	mov	w0, 8192
	cmp	w4, w1
	ccmp	w2, w0, 2, ls
	bhi	.L19
	ldr	x0, [x19]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L49
	mov	w22, w2
	mov	w21, w3
	mov	w24, 5
	mov	w23, 2
	mov	w25, 3
.L28:
	ldr	x0, .LC5
	mov	w1, 0
	mov	x2, 20
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x19]
	stp	w22, w21, [x29, 92]
	stp	w22, w21, [x29, 100]
	ldr	w1, [x0, 28]
	cmp	w1, 24
	beq	.L33
	strb	w25, [x29, 89]
	sxtb	w1, w23
	strb	w24, [x29, 90]
.L39:
	ldr	w2, [x0, 684]
	ldr	w3, [x0, 688]
	strb	w1, [x29, 91]
	mul	w0, w22, w21
	mul	w1, w2, w3
	cmp	w0, w1
	ble	.L34
	ldr	x1, .LC7
	mov	w4, w22
	mov	w5, w21
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, .LC8
	ldr	x4, [x0]
	cbz	x4, .L42
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
	b	.L43
	.p2align 3
.L19:
	ldr	x1, .LC2
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L34:
	ldr	w0, [x20, 2856]
	add	x1, x29, 88
	bl	FSP_ConfigInstance
	cbnz	w0, .L35
	ldr	x1, [x19]
	add	x3, x29, 84
	ldr	w0, [x20, 2856]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	mov	w1, w0
	beq	.L50
	mov	w0, 1
	cbz	w1, .L43
.L37:
	ldr	x1, .LC10
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L43
	.p2align 3
.L49:
	ldr	w1, [x0, 724]
	cbz	w1, .L51
	ldr	w4, [x0, 684]
	ldr	w5, [x0, 688]
	cmp	w2, w4
	bhi	.L30
	cmp	w3, w5
	bhi	.L30
	ldr	w4, [x0, 712]
	mov	w22, w2
	ldr	w1, [x0, 708]
	mov	w21, w3
	mov	w23, 1
	add	w25, w1, 2
	cbz	w4, .L32
.L47:
	add	w1, w1, w23
	mov	w23, 17
	cmp	w1, w23
	csel	w23, w1, w23, le
.L32:
	ldrsb	w24, [x0, 732]
	b	.L28
	.p2align 3
.L35:
	ldr	x1, .LC12
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L43
	.p2align 3
.L51:
	ldr	w22, [x0, 684]
	cmp	w2, w22
	bhi	.L52
	ldr	w21, [x0, 688]
	cmp	w3, w21
	bhi	.L53
	ldr	w2, [x0, 712]
	mov	w23, 1
	ldr	w1, [x0, 708]
	add	w25, w1, 2
	cbnz	w2, .L47
	ldrsb	w24, [x0, 732]
	b	.L28
	.p2align 3
.L33:
	mov	w1, 1
	strb	w24, [x29, 90]
	strb	w1, [x29, 89]
	mov	w1, 1
	b	.L39
	.p2align 3
.L30:
	ldr	x1, .LC4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L43
	.p2align 3
.L42:
	mov	w0, -1
	b	.L43
.L53:
	mov	w5, w21
.L25:
	ldr	x1, .LC4
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L43
.L52:
	ldr	w5, [x0, 688]
	b	.L25
.L50:
	add	x0, x20, 2248
	bl	ResetVoQueue
	b	.L37
	.size	MP2_ArrangeVHBMem, .-MP2_ArrangeVHBMem
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC8:
	.xword	g_event_report
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_DecodingDecide
	.type	MP2_DecodingDecide, %function
MP2_DecodingDecide:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x19, x23, 45056
	mov	w20, -1
	bl	_mcount
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w3, [x0, 588]
	tbnz	x3, 23, .L134
.L55:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L134:
	add	x25, x23, 86016
	ldr	x21, [x25, 2232]
	ldrb	w1, [x21, 17]
	cmp	w1, 3
	beq	.L56
	ldr	w0, [x0, 600]
	cmp	w0, 1
	beq	.L56
	ands	w20, w3, 255
	bne	.L135
.L58:
	add	x22, x19, 264
	add	x22, x22, 40960
	ldr	w0, [x22, 656]
	cbz	w0, .L136
	ldr	w0, [x22, 576]
	sub	w0, w0, #2
	cmp	w0, 1
	ldr	x0, [x23]
	ldr	w2, [x0, 8]
	bls	.L137
.L62:
	add	x0, x19, 264
	sub	w1, w2, #1
	add	x0, x0, 40960
	cmp	w1, 3
	str	w2, [x0, 576]
	bls	.L138
	ldrb	w27, [x21, 30]
	mov	w24, 1
	ldrb	w28, [x21, 17]
.L73:
	add	x22, x19, 264
	add	x22, x22, 40960
	ldr	w0, [x22, 520]
	ldr	w26, [x22, 660]
	ldr	w2, [x22, 596]
	add	w26, w26, w0
	add	x0, x25, 1128
	str	w2, [x29, 108]
	bl	BsPos
	add	w5, w26, w0, lsr 3
	ldr	x1, .LC22
	mov	w4, w28
	ldr	w2, [x29, 108]
	mov	w3, w27
	mov	w0, 18
	bl	dprint_vfmw
	ldr	w1, [x22, 588]
	mov	w0, -14155777
	and	w0, w1, w0
	str	w0, [x22, 588]
	ldr	x0, [x23]
	ldr	w0, [x0, 620]
	cmp	w0, 1
	beq	.L139
	ldr	w0, [x22, 648]
	cbz	w0, .L140
	cmp	w0, 1
	bls	.L141
.L84:
	add	x22, x19, 264
	ldr	w0, [x25, 2856]
	add	x22, x22, 40960
	ldr	w1, [x22, 684]
	bl	FSP_GetFsImagePtr
	mov	x26, x0
	ldr	w1, [x22, 688]
	ldr	w0, [x25, 2856]
	bl	FSP_GetFsImagePtr
	cmp	x26, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L142
	ldrb	w1, [x21, 30]
	cmp	w1, 2
	beq	.L143
	cmp	w1, 3
	beq	.L144
.L92:
	cbnz	w24, .L106
	ldrb	w0, [x21, 17]
	cmp	w0, 3
	beq	.L98
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w0, [x0, 600]
	cbnz	w0, .L55
.L98:
	ldrb	w0, [x21, 35]
	cmp	w0, 1
	beq	.L145
	ldrb	w0, [x21, 26]
	cmp	w0, 1
	beq	.L146
	add	x1, x19, 264
	add	x1, x1, 40960
	ldr	w0, [x1, 772]
	add	w0, w0, 1
	str	w0, [x1, 772]
	lsl	w0, w0, 1
	str	w0, [x1, 768]
.L100:
	ldr	w0, [x25, 1028]
	add	x19, x19, 264
	add	x19, x19, 40960
	add	w0, w0, 1
	str	w0, [x25, 1028]
	ldr	w0, [x19, 596]
	add	w0, w0, 1
	str	w0, [x19, 596]
	b	.L55
	.p2align 3
.L135:
	ldr	x0, .LC13
	ldr	x4, [x0]
	cbz	x4, .L59
	ldr	w0, [x25, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 103
	blr	x4
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w3, [x0, 588]
.L59:
	add	x19, x19, 264
	ldr	x1, .LC15
	add	x19, x19, 40960
	mov	w0, 22
	mov	w20, 0
	ldr	w2, [x19, 596]
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L56:
	ldr	w0, [x25, 2860]
	ands	w20, w3, 255
	add	w0, w0, 1
	str	w0, [x25, 2860]
	beq	.L58
	b	.L135
	.p2align 3
.L138:
	ldr	x0, .LC20
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx69
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx69:
	.section	.rodata
	.align	0
	.align	2
.L69:
	.byte	(.L68 - .Lrtx69) / 4
	.byte	(.L70 - .Lrtx69) / 4
	.byte	(.L71 - .Lrtx69) / 4
	.byte	(.L72 - .Lrtx69) / 4
	.text
	.p2align 3
.L140:
	ldrb	w1, [x21, 30]
	sub	w0, w1, #2
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L147
.L87:
	cmp	w1, 3
	bne	.L84
	ldr	x1, .LC30
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	b	.L84
	.p2align 3
.L144:
	cbz	x26, .L148
	ldr	x1, [x23]
	ldr	w2, [x26, 152]
	ldr	w3, [x1]
	cmp	w2, w3
	bhi	.L94
	ldr	w2, [x0, 152]
	cbz	x0, .L97
	cmp	w3, w2
	bcs	.L92
.L97:
	ldr	x1, .LC41
	mov	w0, 1
	bl	dprint_vfmw
	b	.L55
	.p2align 3
.L71:
	ldrb	w27, [x21, 30]
	mov	w24, 0
	ldrb	w28, [x21, 17]
	b	.L73
	.p2align 3
.L70:
	ldrb	w27, [x21, 30]
	sub	w0, w27, #2
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L149
.L131:
	ldrb	w28, [x21, 17]
	mov	w24, 1
	b	.L73
	.p2align 3
.L68:
	ldrb	w27, [x21, 30]
	cmp	w27, 3
	bne	.L131
	ldrb	w27, [x21, 17]
	cmp	w27, 3
	beq	.L150
.L79:
	add	x0, x19, 264
	mov	w24, 0
	add	x0, x0, 40960
	ldr	w1, [x0, 600]
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x0, 600]
	ldrb	w27, [x21, 30]
	ldrb	w28, [x21, 17]
	b	.L73
	.p2align 3
.L72:
	ldrb	w0, [x21, 30]
	cmp	w0, 1
	mov	w27, w0
	beq	.L151
	cmp	w0, 3
	beq	.L152
.L78:
	cmp	w0, 2
	beq	.L82
	mov	w27, w0
	b	.L131
	.p2align 3
.L139:
	ldr	w1, [x22, 648]
	cbnz	w1, .L84
	ldrb	w1, [x21, 30]
	cmp	w1, 3
	beq	.L153
	cmp	w1, 2
	bne	.L84
	ldr	x1, .LC26
	bl	dprint_vfmw
	b	.L84
	.p2align 3
.L137:
	cmp	w2, 1
	ccmp	w2, 4, 4, hi
	bne	.L62
	ldr	x1, .LC19
	mov	w0, 2
	bl	dprint_vfmw
	ldrb	w0, [x21, 30]
	cmp	w0, 1
	beq	.L127
	ldr	w0, [x22, 588]
	ldr	w1, [x22, 688]
	orr	w0, w0, 128
	str	w0, [x22, 588]
	ldr	w0, [x25, 2856]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L65
	ldr	w0, [x25, 2856]
	ldr	x1, [x24, 544]
	bl	FreeUsdByDec
	ldr	w0, [x25, 2856]
	ldr	x1, [x24, 552]
	bl	FreeUsdByDec
	ldr	w0, [x25, 2856]
	ldr	x1, [x24, 560]
	bl	FreeUsdByDec
	ldr	w0, [x25, 2856]
	ldr	x1, [x24, 568]
	bl	FreeUsdByDec
	add	x0, x24, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x22, 688]
	ldr	w0, [x25, 2856]
	bl	FSP_ClearLogicFs
	ldr	w0, [x25, 2856]
	mov	w2, 1
	ldr	w1, [x22, 684]
	bl	FSP_ClearLogicFs
	str	wzr, [x22, 684]
	str	wzr, [x22, 688]
	ldr	w0, [x25, 2856]
	bl	FSP_GetFspType
	cbnz	w0, .L154
.L65:
	add	x0, x19, 264
	add	x0, x0, 40960
	str	wzr, [x0, 648]
.L127:
	ldr	x0, [x23]
	ldr	w2, [x0, 8]
	b	.L62
	.p2align 3
.L136:
	ldr	x1, .LC17
	mov	w0, 1
	ldr	w2, [x22, 596]
	bl	dprint_vfmw
	b	.L55
	.p2align 3
.L143:
	cbz	x26, .L90
	ldr	x0, [x23]
	ldr	w2, [x26, 152]
	ldr	w3, [x0]
	cmp	w2, w3
	bls	.L92
	ldr	x1, .LC37
	mov	w0, 1
	bl	dprint_vfmw
	b	.L55
	.p2align 3
.L106:
	mov	w20, 1
	b	.L55
	.p2align 3
.L142:
	ldr	x2, .LC31
	mov	w3, 879
	ldr	x1, .LC33
	mov	w0, 1
	bl	dprint_vfmw
	b	.L55
.L145:
	add	x0, x19, 264
	ldrb	w1, [x21, 18]
	add	x0, x0, 40960
	ldrb	w2, [x21, 24]
	add	w2, w2, w1
	ldr	w1, [x0, 772]
	add	w2, w2, 1
	add	w1, w2, w1
	str	w1, [x0, 772]
	lsl	w1, w1, 1
	str	w1, [x0, 768]
	b	.L100
.L148:
	ldr	x0, [x23]
	ldr	w2, [x26, 152]
	ldr	w3, [x0]
.L94:
	ldr	x1, .LC39
	mov	w0, 1
	bl	dprint_vfmw
	b	.L55
.L151:
	str	wzr, [x25, 2868]
	ldrb	w0, [x21, 30]
	cmp	w0, 3
	bne	.L78
.L81:
	ldrb	w28, [x21, 17]
	cmp	w28, 3
	bne	.L79
	mov	w27, w28
	mov	w24, 0
	b	.L73
.L149:
	cmp	w27, 2
	beq	.L155
.L76:
	ldrb	w28, [x21, 17]
	cmp	w28, 3
	bne	.L79
	mov	w24, 0
	b	.L73
.L146:
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w2, [x0, 772]
	ldr	w1, [x0, 768]
	add	w2, w2, 1
	str	w2, [x0, 772]
	ldrb	w2, [x21, 24]
	add	w2, w2, 2
	add	w1, w2, w1
	str	w1, [x0, 768]
	b	.L100
.L82:
	mov	w24, 1
	str	w24, [x25, 2868]
	ldrb	w27, [x21, 30]
	ldrb	w28, [x21, 17]
	b	.L73
.L147:
	ldr	x1, .LC28
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	b	.L84
.L152:
	ldr	w0, [x25, 2868]
	cbnz	w0, .L131
	b	.L81
.L90:
	ldr	x2, .LC31
	mov	w3, 889
	ldr	x1, .LC35
	mov	w0, 1
	bl	dprint_vfmw
	b	.L55
.L153:
	ldr	x1, .LC24
	mov	w24, 0
	bl	dprint_vfmw
	b	.L84
.L155:
	ldrb	w0, [x19, 265]
	cmp	w0, 3
	beq	.L76
	ldrb	w24, [x19, 264]
	cmp	w24, 1
	bne	.L76
	ldrb	w28, [x21, 17]
	b	.L73
.L150:
	mov	w28, w27
	mov	w24, 0
	b	.L73
.L154:
	ldr	w0, [x25, 2856]
	bl	FSP_GetNullLogicFs
	str	w0, [x22, 684]
	str	w0, [x22, 688]
	b	.L65
.L141:
	ldrb	w1, [x21, 30]
	b	.L87
	.size	MP2_DecodingDecide, .-MP2_DecodingDecide
	.align	3
.LC13:
	.xword	g_event_report
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
.LC20:
	.xword	.L69
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC24:
	.xword	.LC23
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
.LC31:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_EstimatePicQp
	.type	MP2_EstimatePicQp, %function
MP2_EstimatePicQp:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC42
	mov	x2, 128
	add	x0, x29, 32
	add	x1, x1, 24
	bl	memcpy
	add	x1, x19, 86016
	ldr	w0, [x19, 292]
	ldr	w2, [x1, 908]
	cmp	w2, 1
	beq	.L157
	ldr	x1, [x1, 2232]
	ldrb	w1, [x1, 21]
	cbnz	w1, .L162
	lsl	w0, w0, 1
.L157:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L162:
	add	x1, x29, 160
	ldr	x19, [sp, 16]
	add	x0, x1, x0, sxtw 2
	ldr	w0, [x0, -128]
	ldp	x29, x30, [sp], 160
	ret
	.size	MP2_EstimatePicQp, .-MP2_EstimatePicQp
	.align	3
.LC42:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetSequenceInfo
	.type	MP2_GetSequenceInfo, %function
MP2_GetSequenceInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x24, x0
	mov	x0, x30
	add	x19, x24, 45056
	add	x20, x24, 86016
	bl	_mcount
	str	wzr, [x29, 100]
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	x21, [x20, 2232]
	stp	wzr, wzr, [x29, 92]
	ldr	x25, [x20, 2240]
	ldr	w2, [x0, 644]
	cmp	w2, 1
	beq	.L165
	cmp	w2, 2
	bne	.L232
	ldr	w1, [x0, 588]
	mov	w0, 1769472
	and	w0, w1, w0
	cmp	w0, 589824
	beq	.L168
.L167:
	ldr	x1, .LC44
	mov	w0, 17
	bl	dprint_vfmw
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w0, [x0, 644]
	cmp	w0, 1
	beq	.L233
.L170:
	ldr	w0, [x21, 56]
	add	x2, x19, 264
	add	x2, x2, 40960
	add	w0, w0, 15
	lsr	w0, w0, 4
	str	w0, [x21, 64]
	ldr	w1, [x2, 644]
	cmp	w1, 2
	beq	.L234
	ldr	w3, [x21, 60]
	add	w1, w3, 15
	lsr	w1, w1, 4
	stp	w1, wzr, [x21, 68]
	ldr	w2, [x2, 644]
	cmp	w2, 2
	beq	.L235
.L173:
	add	x2, x19, 264
	add	x2, x2, 40960
	ldr	w2, [x2, 656]
	cbz	w2, .L175
	ldr	w3, [x25, 64]
	cmp	w0, w3
	beq	.L236
.L175:
	add	x22, x19, 264
	ldr	w0, [x20, 2856]
	add	x22, x22, 40960
	ldr	w1, [x22, 688]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L178
	ldr	w0, [x20, 2856]
	ldr	x1, [x23, 544]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2856]
	ldr	x1, [x23, 552]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2856]
	ldr	x1, [x23, 560]
	bl	FreeUsdByDec
	ldr	w0, [x20, 2856]
	ldr	x1, [x23, 568]
	bl	FreeUsdByDec
	add	x0, x23, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x20, 2856]
	ldr	w1, [x22, 688]
	bl	FSP_ClearLogicFs
	ldr	w0, [x20, 2856]
	mov	w2, 1
	ldr	w1, [x22, 684]
	bl	FSP_ClearLogicFs
	str	wzr, [x22, 684]
	str	wzr, [x22, 688]
	ldr	w0, [x20, 2856]
	bl	FSP_GetFspType
	cbnz	w0, .L237
.L178:
	add	x22, x19, 264
	add	x1, x20, 2248
	add	x22, x22, 40960
	str	wzr, [x22, 648]
	ldr	w0, [x20, 2856]
	bl	FSP_ClearNotInVoQueue
	ldr	x0, [x24]
	ldr	w1, [x0, 724]
	cbnz	w1, .L180
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L238
.L180:
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 656]
	cbz	w1, .L182
	ldr	w1, [x25, 64]
	cbz	w1, .L182
	ldr	w1, [x25, 68]
	cbnz	w1, .L239
	.p2align 2
.L182:
	ldr	w0, [x20, 2856]
	bl	FSP_GetFspType
	cbz	w0, .L223
	ldr	x23, .LC49
.L183:
	add	x22, x19, 264
	mov	w1, 0
	add	x22, x22, 40960
	mov	x0, x24
	str	wzr, [x22, 656]
	str	wzr, [x22, 672]
	bl	MP2_ArrangeVHBMem
	str	w0, [x22, 656]
	ldr	x1, .LC51
	mov	w0, 1
	ldp	w2, w3, [x21, 64]
	lsl	w3, w3, 4
	lsl	w2, w2, 4
	bl	dprint_vfmw
.L181:
	ldr	x4, [x23]
	cbz	x4, .L230
	ldp	w2, w1, [x21, 64]
	ldp	w5, w3, [x25, 64]
	ldr	w0, [x20, 2856]
	strh	w2, [x29, 108]
	add	x2, x29, 104
	strh	w1, [x29, 110]
	mov	w1, 2
	strh	w3, [x29, 106]
	mov	w3, 8
	strh	w5, [x29, 104]
	blr	x4
.L230:
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w2, [x0, 656]
.L176:
	add	x19, x19, 264
	add	x19, x19, 40960
	str	w2, [x19, 584]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L232:
	ldr	w1, [x0, 588]
	mov	w2, 3538944
	tst	w1, w2
	beq	.L168
	mov	w2, 2
	str	w2, [x0, 644]
	tbnz	x1, 17, .L169
	orr	w1, w1, w2
	str	w1, [x0, 588]
.L169:
	mov	w2, 2
	tbnz	x1, 20, .L167
	add	x0, x19, 264
	orr	w1, w1, 16
	add	x0, x0, 40960
	str	w1, [x0, 588]
	b	.L167
	.p2align 3
.L168:
	add	x0, x19, 264
	mov	w1, 1
	add	x0, x0, 40960
	mov	w2, w1
	str	w1, [x0, 644]
	mov	w0, 17
	ldr	x1, .LC44
	bl	dprint_vfmw
	add	x0, x19, 264
	add	x0, x0, 40960
	ldr	w0, [x0, 644]
	cmp	w0, 1
	bne	.L170
.L233:
	mov	w2, 3
	mov	w1, 5
	strb	w0, [x21, 35]
	strb	w0, [x21, 26]
	strb	w2, [x21, 17]
	strb	w0, [x21, 19]
	strb	w0, [x21, 36]
	strb	wzr, [x21, 20]
	strb	wzr, [x21, 21]
	strb	wzr, [x21, 22]
	strb	wzr, [x21, 23]
	strb	wzr, [x21, 16]
	str	w1, [x21, 152]
	b	.L170
	.p2align 3
.L223:
	ldr	w0, [x20, 2856]
	add	x2, x29, 96
	add	x3, x29, 100
	add	x1, x29, 92
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x24]
	ldr	w2, [x0, 724]
	cmp	w2, 1
	beq	.L240
.L228:
	ldr	x23, .LC49
.L185:
	strb	wzr, [x20, 2873]
	b	.L183
	.p2align 3
.L165:
	mov	w1, 18
	ldr	w3, [x0, 588]
	movk	w1, 0x12, lsl 16
	and	w1, w3, w1
	cmp	w1, 1179648
	bne	.L167
	mov	w2, 2
	str	w2, [x0, 644]
	b	.L167
	.p2align 3
.L234:
	ldrb	w1, [x21, 35]
	cbnz	w1, .L172
	ldr	w3, [x21, 60]
	add	w1, w3, 31
	lsr	w1, w1, 5
	lsl	w1, w1, 1
	stp	w1, wzr, [x21, 68]
	ldr	w2, [x2, 644]
	cmp	w2, 2
	bne	.L173
	add	w2, w3, 15
	mov	w3, w1
	lsr	w2, w2, 4
	b	.L174
	.p2align 3
.L235:
	ldrb	w2, [x21, 35]
	cbnz	w2, .L173
	add	w3, w3, 31
	mov	w2, w1
	lsr	w3, w3, 5
	lsl	w3, w3, 1
.L174:
	sub	w2, w3, w2
	str	w2, [x21, 72]
	b	.L173
	.p2align 3
.L172:
	ldr	w1, [x21, 60]
	add	w1, w1, 15
	lsr	w1, w1, 4
	stp	w1, wzr, [x21, 68]
	b	.L173
	.p2align 3
.L240:
	ldr	w0, [x29, 100]
	cmp	w0, wzr
	ble	.L241
.L186:
	mov	w0, 1
	strb	w0, [x20, 2873]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L239:
	ldr	x1, .LC46
	str	wzr, [x0, 656]
	mov	w0, 1
	bl	dprint_vfmw
	b	.L182
	.p2align 3
.L236:
	ldr	w0, [x25, 68]
	cmp	w0, w1
	bne	.L175
	b	.L176
	.p2align 3
.L237:
	ldr	w0, [x20, 2856]
	bl	FSP_GetNullLogicFs
	str	w0, [x22, 684]
	str	w0, [x22, 688]
	b	.L178
	.p2align 3
.L238:
	ldr	w0, [x22, 656]
	cbz	w0, .L242
	ldr	x23, .LC49
	b	.L181
	.p2align 3
.L242:
	mov	w1, 0
	mov	x0, x24
	bl	MP2_ArrangeVHBMem
	str	wzr, [x22, 672]
	str	w0, [x22, 656]
	ldr	x23, .LC49
	b	.L181
	.p2align 3
.L241:
	ldr	w0, [x29, 96]
	cmp	w0, 32
	bgt	.L186
	ldr	x0, [x24, 8]
	cbnz	x0, .L186
	ldr	w3, [x20, 2860]
	cbz	w3, .L228
	ldr	w6, [x21, 64]
	cbz	w6, .L228
	ldr	w5, [x20, 2880]
	ldr	w7, [x21, 68]
	cmp	w7, w5
	beq	.L228
	ldr	w4, [x20, 2876]
	ldr	x23, .LC49
	cmp	w6, w4
	beq	.L185
	ldr	x1, .LC48
	mov	w0, w2
	bl	dprint_vfmw
	ldr	w0, [x21, 68]
	str	w0, [x20, 2880]
	ldr	x4, [x23]
	ldr	w0, [x21, 64]
	str	w0, [x20, 2876]
	cbz	x4, .L185
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	strb	wzr, [x20, 2873]
	b	.L183
	.size	MP2_GetSequenceInfo, .-MP2_GetSequenceInfo
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC49:
	.xword	g_event_report
	.align	3
.LC51:
	.xword	.LC50
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_CalcRealEncFrameRate
	.type	MP2_CalcRealEncFrameRate, %function
MP2_CalcRealEncFrameRate:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 86016
	ldr	x3, [x0, 2232]
	ldrb	w0, [x3, 30]
	cmp	w0, 1
	beq	.L248
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L248:
	add	x19, x19, 45056
	ldr	w5, [x3, 80]
	add	x2, x19, 264
	add	x2, x2, 40960
	ldr	w0, [x2, 740]
	ldr	w1, [x2, 752]
	ldr	w6, [x2, 744]
	ldr	w4, [x2, 756]
	add	w0, w0, w1
	cmp	w0, wzr
	add	w4, w6, w4
	ccmp	w5, wzr, 4, gt
	ccmp	w4, wzr, 4, gt
	ble	.L245
	ldrb	w1, [x3, 35]
	cmp	w1, 1
	beq	.L249
	lsl	w1, w0, 1
	mul	w0, w1, w5
	sdiv	w0, w0, w4
.L247:
	lsl	w2, w0, 2
	mov	w1, 19923
	sub	w2, w2, w0
	movk	w1, 0x1062, lsl 16
	lsl	w3, w2, 5
	add	x19, x19, 264
	add	w2, w2, w3
	add	x19, x19, 40960
	add	w0, w2, w0
	smull	x1, w0, w1
	asr	x1, x1, 38
	sub	w0, w1, w0, asr 31
	str	w0, [x19, 776]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L245:
	str	wzr, [x2, 776]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L249:
	ldr	w3, [x2, 748]
	ldr	w1, [x2, 760]
	mul	w0, w0, w5
	add	w1, w3, w1
	sdiv	w0, w0, w1
	b	.L247
	.size	MP2_CalcRealEncFrameRate, .-MP2_CalcRealEncFrameRate
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_CalcDar
	.type	MP2_CalcDar, %function
MP2_CalcDar:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 86016
	bl	_mcount
	ldr	x0, [x19, 2232]
	ldr	w0, [x0, 92]
	sub	w0, w0, #1
	cmp	w0, 2
	bhi	.L252
	ldr	x1, .LC52
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x1, w0, uxtw 2]
	ret
	.p2align 3
.L252:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_CalcDar, .-MP2_CalcDar
	.align	3
.LC52:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_SetImgFormat
	.type	MP2_SetImgFormat, %function
MP2_SetImgFormat:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 45056
	add	x23, x22, 86016
	bl	_mcount
	add	x1, x21, 264
	add	x1, x1, 40960
	ldr	w0, [x23, 2856]
	ldr	x20, [x23, 2232]
	ldr	w1, [x1, 692]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L253
	ldrb	w0, [x20, 30]
	cmp	w0, 4
	beq	.L264
	sub	w0, w0, #1
	and	w0, w0, 3
	mov	w4, w0
	uxtb	w2, w0
.L255:
	ldrb	w0, [x20, 35]
	mov	w5, 1
	ldrb	w3, [x19, 65]
	ldrb	w1, [x20, 17]
	cmp	w0, wzr
	ubfx	x3, x3, 2, 2
	cset	w8, eq
	orr	w3, w1, w3
	ldr	w7, [x20, 136]
	cbnz	w0, .L256
	cmp	w1, 3
	beq	.L271
	add	x0, x21, 264
	cmp	w1, 1
	add	x0, x0, 40960
	cset	w5, eq
	ldr	w0, [x0, 600]
	cbz	w0, .L256
	cset	w5, ne
.L256:
	ldr	x0, [x23, 2232]
	ldr	w0, [x0, 92]
	sub	w0, w0, #1
	cmp	w0, 2
	bhi	.L266
.L273:
	ldr	x1, .LC53
	ldr	w1, [x1, w0, uxtw 2]
	and	w6, w1, 7
.L259:
	ldrb	w0, [x19, 65]
	bfi	w0, w8, 0, 2
	bfi	w0, w3, 2, 2
	bfi	w0, w5, 4, 2
	strb	w0, [x19, 65]
	ldrb	w0, [x19, 64]
	bfi	w0, w2, 0, 2
	and	w0, w0, -29
	bfi	w0, w7, 5, 3
	strb	w0, [x19, 64]
	mov	x0, x19
	ldr	w2, [x19, 64]
	bfi	w2, w6, 14, 3
	str	w2, [x19, 64]
	lsr	w2, w2, 16
	ldrb	w3, [x20, 4]
	bfi	w2, w3, 1, 1
	strb	w2, [x19, 66]
	ldr	w2, [x20, 8]
	str	w2, [x19, 120]
	stp	w4, w4, [x19, 56]
	bl	SetAspectRatio
	mov	w0, 3
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w2, 1
	ldrb	w1, [x20, 17]
	strb	w2, [x19, 291]
	cmp	w1, 3
	csel	w0, w0, wzr, ne
	strb	w0, [x19, 284]
	ldr	x0, [x22, 8]
	cbz	x0, .L261
	ldrb	w0, [x0, 145]
	str	w0, [x19, 300]
.L262:
	str	w0, [x19, 304]
	str	w0, [x19, 308]
	mov	w0, 1
	strb	w0, [x19, 289]
	ldr	w0, [x20, 80]
	str	w0, [x19, 108]
	ldr	w2, [x20, 56]
	str	w2, [x19, 68]
	ldr	w1, [x20, 60]
	str	w1, [x19, 72]
	ldr	x0, [x22]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L272
.L263:
	lsr	w3, w2, 1
	lsr	w0, w1, 1
	stp	w3, w0, [x19, 84]
	mov	x0, x22
	ldr	w3, [x20, 156]
	str	w3, [x19, 92]
	ldr	w3, [x20, 160]
	str	w3, [x19, 96]
	stp	w2, w1, [x19, 76]
	ldrb	w1, [x20, 35]
	str	w1, [x19, 396]
	ldrb	w1, [x20, 26]
	str	w1, [x19, 400]
	ldr	w1, [x20, 152]
	str	w1, [x19, 408]
	bl	MP2_CalcRealEncFrameRate
	add	x0, x21, 264
	add	x0, x0, 40960
	ldr	w0, [x0, 776]
	str	w0, [x19, 404]
.L253:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L266:
	mov	w1, 0
	mov	w6, 0
	b	.L259
	.p2align 3
.L272:
	ldr	w3, [x19, 112]
	add	w0, w1, 15
	lsr	w0, w0, 4
	ldr	w4, [x19, 36]
	lsl	w5, w3, 4
	mul	w0, w0, w5
	add	w5, w0, w4
	str	w5, [x19, 40]
	stp	w4, w5, [x19, 20]
	add	w4, w3, w4
	add	w3, w3, w5
	stp	w4, w3, [x19, 28]
	ldr	x3, [x19, 504]
	add	x0, x3, x0, sxtw
	str	x0, [x19, 512]
	b	.L263
	.p2align 3
.L264:
	mov	w4, 0
	mov	w2, 0
	b	.L255
	.p2align 3
.L261:
	mov	w0, 32
	strb	wzr, [x19, 291]
	str	w0, [x19, 300]
	b	.L262
	.p2align 3
.L271:
	ldr	x0, [x23, 2232]
	ldrb	w5, [x20, 18]
	ldr	w0, [x0, 92]
	and	w5, w5, 1
	sub	w0, w0, #1
	cmp	w0, 2
	bhi	.L266
	b	.L273
	.size	MP2_SetImgFormat, .-MP2_SetImgFormat
	.align	3
.LC53:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_SearchStartCode
	.type	MP2_SearchStartCode, %function
MP2_SearchStartCode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 4
	mov	w0, 0
	ble	.L275
	mov	w1, w19
	mov	x0, x20
	bl	MP2_SearchStartCode.part.3
.L275:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_SearchStartCode, .-MP2_SearchStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ProtocolPPSCheck
	.type	MP2_ProtocolPPSCheck, %function
MP2_ProtocolPPSCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 45056
	add	x19, x19, 86016
	bl	_mcount
	add	x1, x20, 264
	add	x1, x1, 40960
	ldr	x3, [x19, 2232]
	ldr	w0, [x1, 644]
	cmp	w0, 1
	beq	.L279
	cmp	w0, 2
	beq	.L280
	ldr	w0, [x1, 588]
	orr	w0, w0, 63
	str	w0, [x1, 588]
	ldrb	w2, [x3, 30]
.L286:
	tst	w0, 24
	beq	.L288
.L304:
	cmp	w2, 3
	bne	.L289
.L277:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L280:
	ldr	w0, [x1, 588]
	tbnz	x0, 20, .L287
	orr	w0, w0, 16
	str	w0, [x1, 588]
.L287:
	ldrb	w2, [x3, 30]
	sub	w1, w2, #1
	uxtb	w1, w1
	cmp	w1, 2
	bls	.L286
.L302:
	add	x1, x20, 264
	orr	w0, w0, 8
	add	x1, x1, 40960
	tst	w0, 24
	str	w0, [x1, 588]
	ldrb	w2, [x3, 30]
	bne	.L304
.L288:
	cmp	w2, 1
	bne	.L277
	add	x20, x20, 264
	and	w0, w0, -193
	add	x20, x20, 40960
	str	w0, [x20, 588]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L279:
	ldrb	w2, [x3, 30]
	sub	w0, w2, #1
	uxtb	w0, w0
	cmp	w0, 3
	ldr	w0, [x1, 588]
	bhi	.L305
.L282:
	sub	w1, w2, #2
	uxtb	w1, w1
	cmp	w1, 1
	bls	.L306
.L283:
	cmp	w2, 3
	beq	.L307
	tst	w0, 24
	beq	.L288
.L289:
	add	x21, x20, 264
	orr	w0, w0, 64
	add	x21, x21, 40960
	str	w0, [x21, 588]
	ldr	w1, [x21, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L292
	ldr	w0, [x19, 2856]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x22, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x22, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x22, 568]
	bl	FreeUsdByDec
	add	x0, x22, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x19, 2856]
	ldr	w1, [x21, 688]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2856]
	mov	w2, 1
	ldr	w1, [x21, 684]
	bl	FSP_ClearLogicFs
	str	wzr, [x21, 684]
	str	wzr, [x21, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFspType
	cbnz	w0, .L308
.L292:
	add	x20, x20, 264
	add	x20, x20, 40960
	str	wzr, [x20, 648]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L305:
	orr	w0, w0, 8
	str	w0, [x1, 588]
	ldrb	w2, [x3, 30]
	b	.L282
	.p2align 3
.L308:
	ldr	w0, [x19, 2856]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 684]
	str	w0, [x21, 688]
	b	.L292
	.p2align 3
.L307:
	ldrb	w1, [x3, 34]
	cbnz	w1, .L277
	b	.L302
	.p2align 3
.L306:
	ldrb	w1, [x3, 32]
	cbnz	w1, .L283
	add	x1, x20, 264
	orr	w0, w0, 8
	add	x1, x1, 40960
	str	w0, [x1, 588]
	ldrb	w2, [x3, 30]
	b	.L283
	.size	MP2_ProtocolPPSCheck, .-MP2_ProtocolPPSCheck
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetImageBuffer
	.type	MP2_GetImageBuffer, %function
MP2_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x1, x0
	mov	x0, x30
	add	x21, x1, 86016
	add	x19, x1, 45056
	add	x20, x19, 264
	bl	_mcount
	add	x20, x20, 40960
	mov	w1, 1
	ldr	w0, [x21, 2856]
	bl	FSP_NewLogicFs
	str	w0, [x20, 692]
	mov	w1, w0
	tbnz	w0, #31, .L321
	ldr	w0, [x21, 2856]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L322
	ldr	x1, .LC59
	mov	w0, 18
	ldr	w2, [x20, 692]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L317
	ldr	x1, [x19, 40]
	cbz	x1, .L317
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC61
	bl	dprint_vfmw
	mov	w0, 1
.L314:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L321:
	ldr	x1, .LC55
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 688]
	ldr	w0, [x21, 2856]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L312
	ldr	w0, [x21, 2856]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	ldr	w0, [x21, 2856]
	ldr	x1, [x22, 552]
	bl	FreeUsdByDec
	ldr	w0, [x21, 2856]
	ldr	x1, [x22, 560]
	bl	FreeUsdByDec
	ldr	w0, [x21, 2856]
	ldr	x1, [x22, 568]
	bl	FreeUsdByDec
	add	x0, x22, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x20, 688]
	ldr	w0, [x21, 2856]
	bl	FSP_ClearLogicFs
	ldr	w0, [x21, 2856]
	mov	w2, 1
	ldr	w1, [x20, 684]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 684]
	str	wzr, [x20, 688]
	ldr	w0, [x21, 2856]
	bl	FSP_GetFspType
	cbnz	w0, .L323
.L312:
	add	x19, x19, 264
	add	x1, x21, 2248
	add	x19, x19, 40960
	str	wzr, [x19, 648]
	ldr	w0, [x21, 2856]
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L317:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L323:
	ldr	w0, [x21, 2856]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 684]
	str	w0, [x20, 688]
	b	.L312
	.p2align 3
.L322:
	ldr	x1, .LC57
	mov	w2, 1860
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L314
	.size	MP2_GetImageBuffer, .-MP2_GetImageBuffer
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetPictureInfo
	.type	MP2_GetPictureInfo, %function
MP2_GetPictureInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x22, x23, 45056
	add	x19, x23, 86016
	bl	_mcount
	add	x0, x22, 264
	add	x0, x0, 40960
	ldr	x20, [x19, 2232]
	ldr	x24, [x19, 2240]
	ldr	w0, [x0, 644]
	cmp	w0, 1
	beq	.L370
.L325:
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	beq	.L326
	add	x21, x22, 264
	add	x21, x21, 40960
	ldr	w0, [x21, 600]
	ldr	w1, [x21, 652]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x21, 600]
	ldr	w2, [x20, 164]
	cmp	w2, w1
	cset	w1, ne
	tst	w0, w1
	bne	.L371
.L328:
	ldrb	w2, [x20, 17]
	add	x0, x22, 264
	strb	w2, [x22, 265]
	add	x1, x0, 40960
	add	x21, x23, 16
	ldr	w0, [x20, 164]
	str	w0, [x1, 652]
	ldr	w0, [x20, 64]
	strh	w0, [x21, 150]
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	ldr	w0, [x20, 68]
	beq	.L333
	lsr	w0, w0, 1
	strh	w0, [x21, 146]
	ldr	w0, [x20, 68]
	strh	w0, [x21, 148]
.L334:
	ldrb	w1, [x20, 19]
	add	x0, x22, 264
	strb	w1, [x21, 5]
	add	x0, x0, 40960
	ldrb	w1, [x20, 17]
	strb	w1, [x21, 3]
	ldr	w1, [x0, 600]
	strb	w1, [x21, 4]
	ldrb	w2, [x20, 20]
	strb	w2, [x21, 7]
	ldrb	w2, [x20, 30]
	strb	w2, [x23, 16]
	ldr	w0, [x0, 644]
	cmp	w0, 1
	cset	w2, eq
	str	w2, [x21, 176]
	beq	.L372
.L335:
	ldrb	w0, [x20, 12]
	strb	w0, [x21, 12]
	ldrb	w0, [x20, 13]
	strb	w0, [x21, 13]
	ldrb	w0, [x20, 14]
	strb	w0, [x21, 14]
	ldrb	w0, [x20, 15]
	strb	w0, [x21, 15]
	ldrb	w0, [x20, 18]
	strb	w0, [x21, 6]
	ldrb	w0, [x20, 16]
	strb	w0, [x21, 11]
	ldrb	w0, [x20, 21]
	strb	w0, [x21, 10]
	ldrb	w0, [x20, 22]
	strb	w0, [x21, 9]
	ldrb	w0, [x20, 23]
	strb	w0, [x21, 8]
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	ccmp	w1, wzr, 4, ne
	bne	.L337
	mov	x1, 0
	mov	x0, x23
	bl	MP2_GetImageBuffer
	mov	w25, w0
	cbz	w0, .L373
	add	x1, x22, 264
	ldr	w0, [x19, 2856]
	add	x1, x1, 40960
	ldr	w1, [x1, 692]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L340
	ldr	x2, [x23]
	mov	x3, -1
	ldr	x1, .LC72
	mov	w0, 29
	ldr	x2, [x2, 56]
	str	x2, [x24, 584]
	ldr	x2, [x23]
	ldr	x2, [x2, 72]
	str	x2, [x24, 592]
	ldr	x2, [x23]
	ldr	x2, [x2, 88]
	str	x2, [x24, 600]
	ldr	x2, [x23]
	ldr	w2, [x2, 104]
	str	w2, [x24]
	ldr	x2, [x23]
	ldr	w2, [x2, 108]
	str	w2, [x24, 4]
	ldr	x2, [x23]
	ldr	w2, [x2, 112]
	str	w2, [x24, 8]
	ldr	x2, [x23]
	ldr	w2, [x2, 128]
	str	w2, [x24, 12]
	ldr	x2, [x23]
	str	x3, [x2, 56]
	ldr	x2, [x24, 584]
	ldr	x3, [x24, 592]
	bl	dprint_vfmw
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	cset	w0, ne
	str	w0, [x24, 52]
.L340:
	ldrb	w0, [x20, 30]
	cmp	w0, 3
	beq	.L337
	add	x20, x22, 264
	mov	w0, 2
	add	x20, x20, 40960
	ldr	w1, [x20, 648]
	ldr	w2, [x20, 684]
	ldr	w3, [x20, 688]
	cmp	w1, wzr
	csinc	w0, w0, wzr, ne
	str	w0, [x20, 648]
	cmp	w2, w3
	beq	.L343
	ldr	x1, .LC74
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x19, 2856]
	mov	w2, 0
	ldr	w1, [x20, 684]
	bl	FSP_SetRef
	ldr	w3, [x20, 688]
.L343:
	add	x20, x22, 264
	mov	w2, 1
	add	x20, x20, 40960
	ldr	w1, [x20, 692]
	str	w3, [x20, 684]
	str	w1, [x20, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_SetRef
	ldr	w0, [x19, 2856]
	ldr	w1, [x20, 684]
	bl	FSP_RemovePmv
	ldr	x1, .LC76
	mov	w0, 13
	ldr	w2, [x20, 692]
	bl	dprint_vfmw
.L337:
	add	x20, x22, 264
	ldr	w0, [x19, 2856]
	add	x20, x20, 40960
	ldr	w1, [x20, 692]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x20, 684]
	ldr	w0, [x19, 2856]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	w1, [x20, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_GetLogicFs
	mov	x27, x0
	cmp	x24, xzr
	ccmp	x26, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L374
	ldr	x1, [x24, 32]
	cbz	x1, .L345
	ldr	x0, [x24, 40]
	cbz	x0, .L345
	ldr	x0, [x27, 32]
	cbz	x0, .L347
	ldr	w5, [x0, 8]
.L348:
	str	w5, [x21, 180]
	ldr	x0, [x26, 32]
	cbz	x0, .L375
.L369:
	ldr	w4, [x0, 8]
	str	w4, [x21, 184]
	ldr	x1, .LC82
	ldr	x0, [x24, 32]
	ldr	w2, [x0, 8]
	str	w2, [x21, 188]
	ldr	w6, [x24, 8]
	str	w6, [x21, 224]
	ldr	x0, [x24, 40]
	ldr	w3, [x0, 8]
	str	w3, [x21, 200]
	ldr	w0, [x27, 100]
	str	w0, [x21, 192]
	ldr	w0, [x26, 100]
	str	w0, [x21, 196]
	mov	w0, 13
	bl	dprint_vfmw
	ldr	x2, [x24, 40]
	add	x0, x19, 1168
	add	x1, x23, 96
	add	x3, x19, 1424
	ldr	w2, [x2, 24]
	str	w2, [x21, 208]
	ldr	x2, [x24, 40]
	ldr	w2, [x2, 60]
	str	w2, [x21, 212]
	ldr	x2, [x24, 40]
	ldr	w2, [x2, 44]
	str	w2, [x21, 216]
	ldr	x2, [x24, 40]
	ldr	w2, [x2, 48]
	str	w2, [x21, 220]
	.p2align 2
.L351:
	ldr	w2, [x0]
	add	x0, x0, 4
	strb	w2, [x1]
	add	x1, x1, 1
	cmp	x0, x3
	ldr	w2, [x0, 252]
	strb	w2, [x1, -65]
	bne	.L351
	mov	x0, x23
	mov	w25, 1
	bl	MP2_EstimatePicQp
	strb	w0, [x21, 145]
.L339:
	mov	w0, w25
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L373:
	add	x2, x22, 264
	ldr	x1, .LC70
	add	x2, x2, 40960
	ldr	w2, [x2, 596]
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L372:
	ldrb	w0, [x20, 33]
	strb	w0, [x21, 1]
	ldrb	w0, [x20, 31]
	strb	w0, [x21, 2]
	b	.L335
.L333:
	ldr	w1, [x20, 72]
	sub	w0, w0, w1
	strh	w0, [x21, 146]
	ldr	w0, [x20, 68]
	strh	w0, [x21, 148]
	b	.L334
.L326:
	ldrb	w4, [x22, 265]
	add	x0, x22, 264
	cmp	w4, 3
	beq	.L331
	add	x21, x0, 40960
	ldr	w0, [x21, 600]
	cbz	w0, .L376
.L331:
	add	x0, x22, 264
	mov	w1, 1
	add	x0, x0, 40960
	str	w1, [x0, 600]
	b	.L328
.L370:
	ldrb	w1, [x20, 34]
	ldrb	w0, [x20, 32]
	strb	w1, [x20, 15]
	strb	w1, [x20, 14]
	strb	w0, [x20, 13]
	strb	w0, [x20, 12]
	b	.L325
.L374:
	ldr	w0, [x19, 2856]
	mov	w2, 1
	ldr	w1, [x20, 692]
	mov	w25, 0
	bl	FSP_ClearLogicFs
	ldr	x1, .LC78
	mov	x5, x27
	mov	x4, x26
	mov	x3, x24
	mov	w2, 1180
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L376:
	ldr	x1, .LC68
	mov	w3, 0
	ldr	w2, [x21, 596]
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 2856]
	mov	w2, 1
	ldr	w1, [x21, 692]
	bl	FSP_ClearLogicFs
	ldrb	w0, [x24, 30]
	cmp	w0, 3
	beq	.L331
	ldr	w0, [x21, 588]
	orr	w0, w0, 192
	str	w0, [x21, 588]
	b	.L331
.L345:
	add	x22, x22, 264
	ldr	w0, [x19, 2856]
	add	x19, x22, 40960
	mov	w2, 1
	mov	w25, 0
	ldr	w1, [x19, 692]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC80
	mov	w0, 0
	ldr	w2, [x19, 684]
	ldr	w4, [x19, 688]
	ldr	w3, [x19, 692]
	ldp	x5, x6, [x24, 32]
	bl	dprint_vfmw
	b	.L339
.L375:
	ldr	x0, [x24, 32]
	b	.L369
.L347:
	ldr	w5, [x1, 8]
	b	.L348
.L371:
	ldr	x1, .LC66
	mov	w0, 1
	ldr	w2, [x21, 596]
	bl	dprint_vfmw
	str	wzr, [x21, 600]
	ldr	w1, [x21, 692]
	mov	w2, 1
	ldr	w0, [x19, 2856]
	bl	FSP_ClearLogicFs
	ldrb	w0, [x24, 30]
	cmp	w0, 3
	beq	.L328
	ldr	w0, [x21, 588]
	orr	w0, w0, 192
	str	w0, [x21, 588]
	b	.L328
	.size	MP2_GetPictureInfo, .-MP2_GetPictureInfo
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_SetVDMInf
	.type	MP2_SetVDMInf, %function
MP2_SetVDMInf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, 20744
	mov	x19, x0
	mov	x0, x30
	movk	x20, 0x1, lsl 16
	add	x20, x19, x20
	bl	_mcount
	add	x0, x19, 86016
	add	x0, x0, 1128
	ldrsb	w1, [x20, 528]
	ldr	w3, [x20, 520]
	cmp	w1, 1
	ldr	w4, [x0, 32]
	ldr	w1, [x20, 532]
	lsr	w2, w4, 3
	beq	.L380
	add	w3, w3, w2
	add	w2, w1, w2
	str	w3, [x20, 520]
	add	w1, w4, w1, lsl 3
	ldr	w21, [x20, 536]
	and	w2, w2, -4
	and	w1, w1, 31
	str	w2, [x19, 168]
	str	w1, [x19, 176]
	and	w21, w21, -4
	bl	BsResidBits
	str	w21, [x19, 172]
	str	w0, [x19, 184]
	ldr	w0, [x20, 536]
	ubfiz	w0, w0, 3, 2
	str	w0, [x19, 180]
	ldr	w0, [x20, 544]
	lsl	w0, w0, 3
	str	w0, [x19, 188]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L380:
	add	w3, w3, w2
	add	w2, w1, w2
	str	w3, [x20, 520]
	add	w1, w4, w1, lsl 3
	and	w2, w2, -4
	and	w1, w1, 31
	str	w2, [x19, 168]
	str	w1, [x19, 176]
	bl	BsResidBits
	str	wzr, [x19, 172]
	stp	wzr, w0, [x19, 180]
	str	wzr, [x19, 188]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP2_SetVDMInf, .-MP2_SetVDMInf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_DecNewPic
	.type	MP2_DecNewPic, %function
MP2_DecNewPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	MP2_SetVDMInf
	ldr	x1, [x19]
	add	x2, x19, 45056
	add	x0, x19, 86016
	ldr	w3, [x1, 592]
	str	w3, [x2, 256]
	ldr	w3, [x1, 644]
	str	w3, [x2, 260]
	ldr	x2, [x0, 2232]
	ldrb	w3, [x2, 30]
	cmp	w3, 3
	beq	.L399
	cmp	w3, 2
	beq	.L400
.L383:
	add	x4, x19, 16
	str	x4, [x19, 8]
	ldr	w3, [x1, 880]
	cmp	w3, 1
	beq	.L401
.L385:
	cmp	w3, 2
	beq	.L402
.L386:
	ldr	w1, [x0, 852]
	mov	w20, 1
	and	w1, w1, -16252929
	str	w1, [x0, 852]
	ldrb	w1, [x2, 30]
	cmp	w1, w20
	beq	.L403
.L384:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L400:
	mov	w3, 1
	str	w3, [x0, 2868]
	add	x4, x19, 16
	str	x4, [x19, 8]
	ldr	w3, [x1, 880]
	cmp	w3, 1
	bne	.L385
.L401:
	cbz	x4, .L386
	ldrb	w1, [x2, 30]
	cmp	w1, 3
	bne	.L386
	mov	w20, 0
	str	xzr, [x19, 8]
	b	.L384
	.p2align 3
.L403:
	ldr	x1, .LC83
	ldr	x5, [x1]
	cbz	x5, .L384
	ldp	w4, w1, [x19, 184]
	add	x2, x29, 48
	ldr	w0, [x0, 2856]
	add	w4, w4, w1
	mov	w3, 4
	cmp	w4, wzr
	add	w1, w4, 7
	csel	w4, w1, w4, lt
	mov	w1, 20
	asr	w4, w4, 3
	str	w4, [x2, -8]!
	blr	x5
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L399:
	ldr	w3, [x0, 2868]
	cbnz	w3, .L383
	ldr	w3, [x0, 912]
	cmp	w3, 2
	beq	.L383
	ldrb	w1, [x2, 17]
	cmp	w1, 3
	beq	.L387
	ldr	w1, [x0, 864]
	mov	w20, 0
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x0, 864]
	b	.L384
	.p2align 3
.L402:
	ldr	w3, [x1, 884]
	cmp	w3, wzr
	ccmp	x4, xzr, 4, gt
	beq	.L386
	ldrb	w3, [x2, 30]
	cmp	w3, 3
	bne	.L386
	str	xzr, [x19, 8]
	mov	w20, 0
	ldr	w0, [x1, 884]
	sub	w0, w0, #1
	str	w0, [x1, 884]
	b	.L384
	.p2align 3
.L387:
	mov	w20, 0
	b	.L384
	.size	MP2_DecNewPic, .-MP2_DecNewPic
	.align	3
.LC83:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_RecordVFMWState
	.type	MP2_RecordVFMWState, %function
MP2_RecordVFMWState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 86016
	ldr	x2, [x19]
	ldr	x1, [x0, 2232]
	ldr	w3, [x1, 48]
	str	w3, [x2, 568]
	ldr	x2, [x19]
	ldr	w1, [x1, 52]
	str	w1, [x2, 572]
	ldr	w2, [x0, 2860]
	ldr	w1, [x0, 2864]
	ldr	x3, [x19]
	sub	w0, w2, w1
	cmp	w2, w1
	csel	w0, w0, wzr, ge
	str	w0, [x3, 576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_RecordVFMWState, .-MP2_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetUsrData
	.type	MP2_GetUsrData, %function
MP2_GetUsrData:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x24, x0
	mov	x0, x30
	add	x23, x24, 86016
	bl	_mcount
	add	x20, x23, 1128
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w22, w1, w0, lt
	asr	w22, w22, 3
	cmp	w22, wzr
	ble	.L426
	ldr	x25, .LC86
	mov	w21, 0
	mov	w19, 0
	b	.L412
	.p2align 3
.L443:
	bl	BsGet
	add	w19, w19, 1
	strb	w0, [x25, w21, sxtw]
	cmp	w22, w19
	add	w21, w21, 1
	beq	.L408
.L412:
	mov	w1, 24
	mov	x0, x20
	bl	BsShow
	and	w2, w0, 16777215
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	beq	.L427
	cmp	w21, 1023
	ble	.L443
	mov	w1, 8
	mov	x0, x20
	add	w19, w19, 1
	bl	BsGet
	cmp	w22, w19
	bne	.L412
.L408:
	add	x22, x24, 45056
	add	x25, x22, 264
	add	x25, x25, 40960
	ldrsb	w0, [x25, 528]
	cbz	w0, .L425
.L442:
	mov	w19, 0
.L409:
	add	x0, x22, 264
	add	x0, x0, 40960
	ldr	w20, [x0, 640]
	cmp	w20, 3
	ble	.L417
	add	x20, x23, 872
	add	x25, x23, 904
.L418:
	ldr	x1, [x20]
	ldr	w0, [x23, 2856]
	bl	FreeUsdByDec
	str	xzr, [x20], 8
	cmp	x20, x25
	bne	.L418
	add	x0, x22, 264
	mov	w20, 0
	add	x0, x0, 40960
	str	wzr, [x0, 640]
.L417:
	ldr	w0, [x23, 2856]
	add	x20, x24, x20, uxtw 3
	add	x20, x20, 86016
	bl	GetUsd
	add	x3, x22, 264
	str	x0, [x20, 872]
	add	x4, x3, 40960
	ldr	w2, [x4, 640]
	sxtw	x1, w2
	add	x1, x1, 4096
	add	x1, x1, 1100
	ldr	x1, [x3, x1, lsl 3]
	cbz	x1, .L419
	ldr	x1, [x24]
	ldr	x1, [x1, 56]
	str	x1, [x0, 1056]
	ldr	x0, [x20, 872]
	ldr	w1, [x4, 592]
	str	w1, [x0, 1044]
	ldr	x0, [x20, 872]
	str	w21, [x0, 1052]
	ldr	x1, [x23, 2232]
	ldr	x0, [x20, 872]
	ldrb	w1, [x1, 30]
	strb	w1, [x0, 1024]
	ldr	x0, [x20, 872]
	ldr	w1, [x23, 2860]
	str	w1, [x0, 1032]
	ldr	x1, [x23, 2232]
	ldr	x0, [x20, 872]
	ldrb	w1, [x1, 18]
	strb	w1, [x0, 1025]
	ldr	w0, [x4, 588]
	tbz	x0, 19, .L420
	ldr	x0, [x20, 872]
	mov	w1, 3
	str	w1, [x0, 1040]
.L421:
	ldr	x0, [x20, 872]
	ldr	w2, [x0, 1052]
	cmp	w2, 1024
	ble	.L422
	mov	w1, 1024
	str	w1, [x0, 1052]
	ldr	x0, [x20, 872]
	ldr	w2, [x0, 1052]
.L422:
	ldr	x3, .LC89
	sxtw	x2, w2
	ldr	x1, .LC86
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x0, .LC90
	ldr	x4, [x0]
	cbz	x4, .L423
	ldr	w0, [x23, 2856]
	mov	w3, 1064
	ldr	x2, [x20, 872]
	mov	w1, 6
	blr	x4
.L423:
	add	x22, x22, 264
	add	x22, x22, 40960
	ldr	w0, [x22, 640]
	add	w0, w0, 1
	str	w0, [x22, 640]
.L441:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L425:
	ldrsb	w0, [x25, 529]
	mov	w19, 0
	cbz	w0, .L409
	ldr	w19, [x25, 544]
	cbz	w19, .L409
	ldr	x1, .LC88
	mov	w0, 0
	mov	w19, 1
	bl	dprint_vfmw
	ldr	x2, .LC89
	ldrsw	x1, [x25, 540]
	ldr	x3, [x25, 560]
	ldr	x0, [x25, 568]
	sub	x1, x1, #3
	add	x1, x3, x1
	ldr	x3, [x2, 104]
	sub	x0, x0, #3
	mov	x2, 3
	blr	x3
	strb	w19, [x25, 528]
	add	x3, x25, 512
	ldr	w0, [x25, 536]
	ldr	w2, [x25, 544]
	ldr	x1, [x25, 568]
	sub	w0, w0, #3
	strb	wzr, [x25, 529]
	add	w2, w2, 3
	stp	w0, wzr, [x3, 20]
	stp	w2, wzr, [x3, 28]
	sub	x1, x1, #3
	mov	x0, x20
	str	x1, [x25, 560]
	str	xzr, [x25, 568]
	bl	BsInit
	strb	w19, [x25, 529]
	strb	wzr, [x25, 528]
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w19, w1, w0, lt
	asr	w19, w19, 3
	sub	w19, w19, #3
	cmp	w19, wzr
	ble	.L442
	ldr	x26, .LC86
	mov	w25, 0
	b	.L415
	.p2align 3
.L444:
	bl	BsGet
	strb	w0, [x26, w21, sxtw]
	add	w21, w21, 1
.L414:
	add	w25, w25, 1
	cmp	w19, w25
	beq	.L442
.L415:
	mov	w1, 24
	mov	x0, x20
	bl	BsShow
	and	w2, w0, 16777215
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	beq	.L430
	cmp	w21, 1023
	ble	.L444
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	b	.L414
	.p2align 3
.L427:
	mov	w19, w2
	add	x22, x24, 45056
	b	.L409
	.p2align 3
.L420:
	ldr	x0, [x20, 872]
	mov	w1, 1
	str	w1, [x0, 1040]
	b	.L421
.L419:
	ldr	x1, .LC92
	mov	w0, 0
	bl	dprint_vfmw
	b	.L441
.L426:
	mov	w21, 0
	b	.L408
.L430:
	mov	w19, w2
	b	.L409
	.size	MP2_GetUsrData, .-MP2_GetUsrData
	.align	3
.LC86:
	.xword	.LANCHOR2
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC89:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC90:
	.xword	g_event_report
	.align	3
.LC92:
	.xword	.LC91
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	next_start_code
	.type	next_start_code, %function
next_start_code:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 86016
	bl	_mcount
	add	x20, x20, 1128
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsGetNextBytePtr
	mov	x19, x0
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w2, w1, w0, lt
	mov	w1, 0
	asr	w2, w2, 3
	cmp	w2, 4
	bgt	.L471
.L446:
	mov	x0, x20
	mov	w19, 0
	bl	BsLongSkip
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #3
	cmp	w21, wzr
	bgt	.L465
	b	.L453
	.p2align 3
.L450:
	bl	BsSkip
	cmp	w19, w21
	beq	.L453
.L465:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	cmp	w0, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L450
.L455:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L453:
	mov	x0, 20744
	movk	x0, 0x1, lsl 16
	add	x22, x22, x0
	ldrsb	w0, [x22, 528]
	cbnz	w0, .L449
	ldrsb	w0, [x22, 529]
	cbz	w0, .L449
	ldr	w0, [x22, 544]
	cbz	w0, .L449
	ldr	x1, .LC93
	mov	w0, 7
	mov	w19, 1
	bl	dprint_vfmw
	ldr	x3, .LC94
	mov	x2, 3
	ldrsw	x1, [x22, 540]
	ldr	x4, [x22, 560]
	ldr	x0, [x22, 568]
	sub	x1, x1, #3
	ldr	x3, [x3, 104]
	add	x1, x4, x1
	sub	x0, x0, #3
	blr	x3
	strb	w19, [x22, 528]
	add	x6, x22, 512
	ldr	x4, [x22, 568]
	ldr	w5, [x22, 536]
	mov	x0, x20
	ldr	w3, [x22, 544]
	sub	x4, x4, #3
	strb	wzr, [x22, 529]
	sub	w5, w5, #3
	add	w3, w3, 3
	mov	x1, x4
	stp	w5, wzr, [x6, 20]
	stp	w3, wzr, [x6, 28]
	mov	w2, w3
	str	x4, [x22, 560]
	str	xzr, [x22, 568]
	bl	BsInit
	strb	w19, [x22, 529]
	strb	wzr, [x22, 528]
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsGetNextBytePtr
	mov	x19, x0
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w2, w1, w0, lt
	mov	w1, 0
	asr	w2, w2, 3
	cmp	w2, 4
	bgt	.L472
.L454:
	mov	x0, x20
	bl	BsLongSkip
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #3
	cmp	w21, wzr
	ble	.L449
	mov	w19, 0
	b	.L456
	.p2align 3
.L473:
	bl	BsSkip
	cmp	w19, w21
	beq	.L449
.L456:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	cmp	w0, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L473
	b	.L455
	.p2align 3
.L449:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L471:
	mov	w1, w2
	mov	x0, x19
	bl	MP2_SearchStartCode.part.3
	lsl	w1, w0, 3
	b	.L446
.L472:
	mov	w1, w2
	mov	x0, x19
	bl	MP2_SearchStartCode.part.3
	lsl	w1, w0, 3
	b	.L454
	.size	next_start_code, .-next_start_code
	.align	3
.LC93:
	.xword	.LC87
	.align	3
.LC94:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSliceHdr
	.type	GetSliceHdr, %function
GetSliceHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, 20744
	mov	x21, x0
	mov	x0, x30
	add	x23, x21, 86016
	movk	x22, 0x1, lsl 16
	add	x20, x23, 1128
	bl	_mcount
	add	x22, x21, x22
	b	.L475
	.p2align 3
.L482:
	bl	BsShow
	mov	w19, w0
	mov	x0, x20
	sub	w19, w19, #257
	bl	BsPos
	str	w0, [x22, 668]
	cmp	w19, 174
	mov	w1, 32
	mov	x0, x20
	bls	.L490
	bl	BsSkip
.L475:
	mov	x0, x21
	bl	next_start_code
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 32
	mov	x0, x20
	beq	.L482
	cmn	w2, #1
	mov	w19, w2
	beq	.L477
.L480:
	mov	w0, w19
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L484:
	mov	w19, -1
.L477:
	ldr	x0, .LC95
	ldr	x4, [x0]
	cbz	x4, .L480
	ldr	w0, [x23, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L490:
	bl	BsResidBits
	cmp	w0, 40
	ble	.L484
	ldr	w0, [x22, 584]
	str	wzr, [x22, 664]
	cbnz	w0, .L481
	mov	x0, x21
	mov	w19, 0
	bl	MP2_GetSequenceInfo
	ldr	w0, [x22, 656]
	cbz	w0, .L480
.L481:
	mov	x0, x21
	mov	w19, 1
	bl	MP2_ProtocolPPSCheck
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	GetSliceHdr, .-GetSliceHdr
	.align	3
.LC95:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	sequence_header
	.type	sequence_header, %function
sequence_header:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, 20744
	mov	x21, x0
	movk	x19, 0x1, lsl 16
	mov	x0, x30
	add	x23, x21, 86016
	add	x19, x21, x19
	bl	_mcount
	add	x20, x23, 1128
	mov	w2, 65536
	mov	w1, 12
	ldr	x24, [x23, 2232]
	mov	x0, x20
	str	w2, [x19, 588]
	str	wzr, [x19, 584]
	bl	BsGet
	str	w0, [x24, 56]
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	str	w0, [x24, 60]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	str	w0, [x24, 92]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	str	w0, [x24, 96]
	mov	w1, 18
	mov	x0, x20
	bl	BsGet
	str	w0, [x24, 100]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L492
	ldr	w0, [x19, 588]
	orr	w0, w0, 1
	str	w0, [x19, 588]
.L492:
	mov	w1, 10
	mov	x0, x20
	bl	BsGet
	str	w0, [x24, 104]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x24, 1]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 84]
	ldr	x22, .LC98
	beq	.L509
	add	x0, x22, 64
	add	x1, x23, 1168
	add	x3, x0, 64
	.p2align 2
.L497:
	ldrb	w2, [x0], 1
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L497
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 88]
	beq	.L510
.L506:
	add	x0, x23, 1424
	mov	w1, 16
	add	x23, x23, 1680
	.p2align 2
.L500:
	str	w1, [x0], 4
	cmp	x0, x23
	bne	.L500
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L509:
	mov	x26, x22
	add	x25, x22, 64
	.p2align 2
.L494:
	ldrb	w19, [x26], 1
	mov	w1, 8
	mov	x0, x20
	add	x19, x19, 20480
	add	x19, x19, 1316
	bl	BsGet
	cmp	x26, x25
	str	w0, [x21, x19, lsl 2]
	bne	.L494
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 88]
	bne	.L506
.L510:
	add	x23, x22, 64
	.p2align 2
.L499:
	ldrb	w19, [x22], 1
	mov	w1, 8
	mov	x0, x20
	add	x19, x19, 20480
	add	x19, x19, 1380
	bl	BsGet
	cmp	x22, x23
	str	w0, [x21, x19, lsl 2]
	bne	.L499
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	sequence_header, .-sequence_header
	.align	3
.LC98:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	group_of_pictures_header
	.type	group_of_pictures_header, %function
group_of_pictures_header:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 86016
	add	x20, x19, 1128
	bl	_mcount
	mov	w1, 1
	mov	x0, x20
	ldr	x21, [x19, 2232]
	bl	BsGet
	mov	w1, 5
	strb	w0, [x21, 2]
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 108]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 112]
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 116]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 120]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 124]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 128]
	add	x1, x19, 1004
	add	x2, x19, 1028
	ldr	x3, [x19, 1016]
	ldr	x4, [x1]
	str	x4, [x19, 992]
	ldr	w4, [x19, 1012]
	str	w4, [x19, 1000]
	str	x3, [x1]
	ldr	w3, [x19, 1024]
	str	w3, [x19, 1012]
	ldr	x1, [x2]
	str	x1, [x19, 1016]
	ldr	w1, [x19, 1036]
	str	wzr, [x19, 1028]
	str	wzr, [x19, 1032]
	str	w1, [x19, 1024]
	str	wzr, [x19, 1036]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	group_of_pictures_header, .-group_of_pictures_header
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	sequence_extension
	.type	sequence_extension, %function
sequence_extension:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	add	x23, x22, 45056
	add	x22, x22, 86016
	add	x21, x23, 264
	bl	_mcount
	add	x21, x21, 40960
	add	x20, x22, 1128
	ldr	x19, [x22, 2232]
	mov	w1, 8
	mov	x0, x20
	ldr	w2, [x21, 588]
	str	wzr, [x21, 584]
	orr	w2, w2, 131072
	str	w2, [x21, 588]
	bl	BsGet
	str	w0, [x19, 132]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 35]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 36]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	mov	w25, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	mov	w26, w0
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	mov	w24, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L513
	ldr	w0, [x21, 588]
	orr	w0, w0, 2
	str	w0, [x21, 588]
.L512:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L513:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 37]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 38]
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	and	w2, w0, 255
	ldrb	w1, [x19, 38]
	add	w2, w2, 1
	strb	w0, [x19, 39]
	add	w0, w1, 1
	ldr	x1, .LC101
	sdiv	w0, w0, w2
	add	x1, x1, 16
	ldr	w2, [x19, 96]
	ldr	w2, [x1, x2, lsl 2]
	ldr	w1, [x19, 132]
	mul	w0, w0, w2
	str	w0, [x19, 80]
	tbnz	x1, 7, .L536
	ubfx	x0, x1, 4, 3
	and	w1, w1, 15
	stp	w0, w1, [x19, 48]
.L516:
	ldp	w0, w1, [x19, 56]
	and	w1, w1, 4095
	and	w0, w0, 4095
	orr	w26, w1, w26, lsl 12
	orr	w25, w0, w25, lsl 12
	cmp	w26, wzr
	ccmp	w25, wzr, 4, ne
	stp	w25, w26, [x19, 56]
	bne	.L517
	add	x0, x23, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 588]
	orr	w1, w1, 1
	str	w1, [x0, 588]
	ldr	w25, [x19, 56]
.L517:
	cmp	w25, 8192
	bhi	.L518
	ldr	w0, [x19, 60]
	cmp	w0, 8192
	bls	.L519
.L518:
	add	x23, x23, 264
	ldr	x0, .LC102
	add	x23, x23, 40960
	ldr	x4, [x0]
	ldr	w0, [x23, 588]
	orr	w0, w0, 1
	str	w0, [x23, 588]
	cbz	x4, .L519
	ldr	w0, [x22, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
.L519:
	ldp	w0, w3, [x19, 100]
	mov	w1, 400
	ldr	w2, [x19, 48]
	add	w24, w0, w24, lsl 18
	add	w21, w3, w21, lsl 10
	sub	w0, w2, #4
	stp	w24, w21, [x19, 100]
	mul	w24, w24, w1
	cmp	w0, 1
	str	w24, [x19, 76]
	bls	.L521
	ldr	x0, .LC102
	ldr	x4, [x0]
	cbz	x4, .L522
	ldr	w0, [x22, 2856]
	mov	x2, 0
	mov	w3, 0
	mov	w1, 102
	blr	x4
	ldr	w2, [x19, 48]
.L522:
	ldr	x1, .LC104
	mov	w0, 1
	bl	dprint_vfmw
.L521:
	ldr	w2, [x19, 52]
	sub	w0, w2, #4
	cmp	w0, 6
	bls	.L512
	ldr	x0, .LC102
	ldr	x4, [x0]
	cbz	x4, .L523
	ldr	w0, [x22, 2856]
	mov	x2, 0
	mov	w3, 0
	mov	w1, 102
	blr	x4
	ldr	w2, [x19, 52]
.L523:
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L536:
	and	w1, w1, 15
	cmp	w1, 5
	bne	.L516
	mov	w1, 133
	mov	w0, 8
	stp	w1, w0, [x19, 48]
	b	.L516
	.size	sequence_extension, .-sequence_extension
	.align	3
.LC101:
	.xword	.LANCHOR1
	.align	3
.LC102:
	.xword	g_event_report
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	sequence_display_extension
	.type	sequence_display_extension, %function
sequence_display_extension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 45056
	add	x19, x19, 86016
	bl	_mcount
	add	x20, x19, 1128
	add	x2, x21, 264
	mov	w1, 3
	ldr	x19, [x19, 2232]
	add	x2, x2, 40960
	mov	x0, x20
	stp	wzr, wzr, [x19, 156]
	ldr	w3, [x2, 588]
	orr	w3, w3, 262144
	str	w3, [x2, 588]
	bl	BsGet
	str	w0, [x19, 136]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 140]
	cbnz	w0, .L544
.L538:
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 156]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L539
	add	x21, x21, 264
	add	x21, x21, 40960
	ldr	w0, [x21, 588]
	orr	w0, w0, 4
	str	w0, [x21, 588]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L539:
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 160]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L544:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 144]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 148]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 152]
	b	.L538
	.size	sequence_display_extension, .-sequence_display_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	quant_matrix_extension
	.type	quant_matrix_extension, %function
quant_matrix_extension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x21, 86016
	mov	w1, 1
	add	x20, x2, 1128
	mov	x0, x20
	ldr	x24, [x2, 2232]
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 84]
	beq	.L546
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 88]
	beq	.L564
.L548:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbz	w0, .L552
	mov	w19, 64
	.p2align 2
.L556:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	subs	w19, w19, #1
	bne	.L556
.L552:
	mov	w1, 1
	mov	x0, x20
	mov	w19, 64
	bl	BsGet
	cbz	w0, .L545
	.p2align 2
.L558:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	subs	w19, w19, #1
	bne	.L558
.L545:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L546:
	ldr	x22, .LC108
	add	x23, x22, 64
	.p2align 2
.L549:
	ldrb	w19, [x22], 1
	mov	w1, 8
	mov	x0, x20
	add	x19, x19, 20480
	add	x19, x19, 1316
	bl	BsGet
	cmp	x22, x23
	str	w0, [x21, x19, lsl 2]
	bne	.L549
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x24, 88]
	bne	.L548
.L564:
	ldr	x22, .LC108
	add	x23, x22, 64
	.p2align 2
.L553:
	ldrb	w19, [x22], 1
	mov	w1, 8
	mov	x0, x20
	add	x19, x19, 20480
	add	x19, x19, 1380
	bl	BsGet
	cmp	x23, x22
	str	w0, [x21, x19, lsl 2]
	bne	.L553
	b	.L548
	.size	quant_matrix_extension, .-quant_matrix_extension
	.align	3
.LC108:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	picture_display_extension
	.type	picture_display_extension, %function
picture_display_extension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x23, x19, 45056
	add	x19, x19, 86016
	bl	_mcount
	add	x20, x19, 1128
	add	x0, x23, 264
	add	x0, x0, 40960
	ldr	x19, [x19, 2232]
	ldr	w1, [x0, 588]
	orr	w1, w1, 2097152
	str	w1, [x0, 588]
	ldrb	w0, [x19, 35]
	cbz	w0, .L566
	ldrb	w0, [x19, 24]
	mov	w22, 1
	cbnz	w0, .L579
.L567:
	add	x19, x19, 172
	mov	w21, 0
	b	.L571
	.p2align 3
.L580:
	mov	w1, 16
	mov	x0, x20
	add	x19, x19, 4
	bl	BsGet
	mov	w1, 1
	str	w0, [x19, 8]
	mov	x0, x20
	bl	BsGet
	cbz	w0, .L578
	cmp	w21, w22
	bge	.L565
.L571:
	mov	w1, 16
	mov	x0, x20
	add	w21, w21, 1
	bl	BsGet
	str	w0, [x19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L580
.L578:
	add	x0, x23, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 588]
	orr	w1, w1, 32
	str	w1, [x0, 588]
.L565:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L566:
	ldrb	w0, [x19, 17]
	mov	w22, 1
	cmp	w0, 3
	bne	.L567
	ldrb	w1, [x19, 24]
	mov	w22, 2
	cmp	w1, wzr
	csel	w22, w22, w0, eq
	b	.L567
	.p2align 3
.L579:
	ldrb	w1, [x19, 18]
	mov	w0, 2
	mov	w22, 3
	cmp	w1, wzr
	csel	w22, w0, w22, eq
	b	.L567
	.size	picture_display_extension, .-picture_display_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	picture_coding_extension
	.type	picture_coding_extension, %function
picture_coding_extension:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x22, x19, 45056
	add	x19, x19, 86016
	bl	_mcount
	add	x20, x19, 1128
	add	x1, x22, 264
	add	x1, x1, 40960
	ldr	x21, [x19, 2232]
	mov	x23, x1
	mov	x25, x21
	add	x24, x21, 4
	ldr	w0, [x1, 588]
	orr	w0, w0, 1048576
	str	w0, [x1, 588]
.L582:
	mov	x19, 0
.L584:
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	sub	w2, w0, #10
	add	x1, x25, x19
	add	x19, x19, 1
	uxtb	w2, w2
	cmp	w2, 4
	strb	w0, [x1, 12]
	ccmp	w0, wzr, 4, hi
	bne	.L583
	ldr	w0, [x23, 588]
	orr	w0, w0, 16
	str	w0, [x23, 588]
.L583:
	cmp	x19, 2
	bne	.L584
	add	x25, x25, 2
	cmp	x25, x24
	bne	.L582
	mov	w1, w19
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 16]
	mov	w1, w19
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, 17]
	cbnz	w0, .L586
	add	x22, x22, 264
	add	x22, x22, 40960
	ldr	w0, [x22, 588]
	orr	w0, w0, 16
	str	w0, [x22, 588]
.L581:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L586:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 18]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 20]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 21]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 23]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 24]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 25]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 26]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, 3]
	cbz	w0, .L581
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 27]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 28]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 29]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 40]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 44]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	picture_coding_extension, .-picture_coding_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	extra_bit_information
	.type	extra_bit_information, %function
extra_bit_information:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 86016
	mov	w20, 0
	bl	_mcount
	add	x19, x19, 1128
	b	.L596
	.p2align 3
.L598:
	mov	w1, 8
	mov	x0, x19
	add	w20, w20, 1
	bl	BsSkip
	mov	x0, x19
	bl	BsResidBits
	cmp	w0, 8
	ble	.L597
.L596:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	cbnz	w0, .L598
.L597:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	extra_bit_information, .-extra_bit_information
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	picture_header
	.type	picture_header, %function
picture_header:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	mov	x3, 20744
	add	x4, x21, 86016
	movk	x3, 0x1, lsl 16
	add	x20, x4, 1128
	add	x3, x21, x3
	mov	w1, 10
	ldr	x19, [x4, 2232]
	mov	x0, x20
	ldr	w2, [x3, 588]
	and	w2, w2, -3670073
	orr	w2, w2, 524288
	str	w2, [x3, 588]
	bl	BsGet
	str	w0, [x19, 164]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 30]
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	ldrb	w22, [x19, 30]
	str	w0, [x19, 168]
	sub	w0, w22, #2
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L602
.L600:
	cmp	w22, 3
	beq	.L603
	mov	x0, x21
	bl	extra_bit_information
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L603:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 33]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 34]
	mov	x0, x21
	bl	extra_bit_information
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L602:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 31]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	ldrb	w22, [x19, 30]
	strb	w0, [x19, 32]
	b	.L600
	.size	picture_header, .-picture_header
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	copyright_extension
	.type	copyright_extension, %function
copyright_extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 86016
	mov	w1, 32
	add	x0, x0, 1128
	bl	BsSkip
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	copyright_extension, .-copyright_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	picture_temporal_scalable_extension
	.type	picture_temporal_scalable_extension, %function
picture_temporal_scalable_extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	copyright_extension
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	picture_temporal_scalable_extension, .-picture_temporal_scalable_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	picture_spatial_scalable_extension
	.type	picture_spatial_scalable_extension, %function
picture_spatial_scalable_extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	copyright_extension
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	picture_spatial_scalable_extension, .-picture_spatial_scalable_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	sequence_scalable_extension
	.type	sequence_scalable_extension, %function
sequence_scalable_extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	copyright_extension
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	sequence_scalable_extension, .-sequence_scalable_extension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	extension
	.type	extension, %function
extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 86016
	mov	w1, 4
	add	x20, x2, 1128
	mov	x0, x20
	ldr	x2, [x2, 2232]
	stp	wzr, wzr, [x2, 136]
	stp	wzr, wzr, [x2, 144]
	str	wzr, [x2, 152]
	bl	BsGet
	sub	w0, w0, #1
	cmp	w0, 9
	bhi	.L609
	ldr	x1, .LC110
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx611
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx611:
	.section	.rodata
	.align	0
	.align	2
.L611:
	.byte	(.L610 - .Lrtx611) / 4
	.byte	(.L612 - .Lrtx611) / 4
	.byte	(.L613 - .Lrtx611) / 4
	.byte	(.L614 - .Lrtx611) / 4
	.byte	(.L614 - .Lrtx611) / 4
	.byte	(.L609 - .Lrtx611) / 4
	.byte	(.L616 - .Lrtx611) / 4
	.byte	(.L617 - .Lrtx611) / 4
	.byte	(.L614 - .Lrtx611) / 4
	.byte	(.L614 - .Lrtx611) / 4
	.text
	.p2align 3
.L614:
	mov	w1, 32
	mov	x0, x20
	bl	BsSkip
.L609:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L613:
	mov	x0, x19
	bl	quant_matrix_extension
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L617:
	mov	x0, x19
	bl	picture_coding_extension
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L616:
	mov	x0, x19
	bl	picture_display_extension
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L610:
	mov	x0, x19
	bl	sequence_extension
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L612:
	mov	x0, x19
	bl	sequence_display_extension
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	extension, .-extension
	.align	3
.LC110:
	.xword	.L611
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_Init
	.type	MPEG2DEC_Init, %function
MPEG2DEC_Init:
	sub	sp, sp, #912
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x27, .LC111
	ldr	w0, [x22, 616]
	cmp	w0, 1
	beq	.L626
	mov	w24, 0
	mov	w25, 0
	mov	w26, 0
	add	x21, x20, 45056
	add	x19, x20, 86016
.L621:
	ldr	x3, [x27, 96]
	mov	x2, 23368
	mov	w1, 0
	movk	x2, 0x1, lsl 16
	mov	x0, x20
	ldr	w23, [x19, 2848]
	blr	x3
	str	w23, [x19, 2848]
	add	x0, x19, 2248
	mov	w23, 1
	bl	ResetVoQueue
	str	x22, [x20]
	add	x1, x21, 264
	str	wzr, [x19, 2868]
	add	x21, x1, 40960
	add	x0, x19, 1840
	add	x2, x19, 2036
	str	x0, [x19, 2240]
	str	x2, [x19, 2232]
	mov	w2, 3
	str	w23, [x21, 600]
	mov	x0, x20
	strb	w2, [x1, 1]
	str	wzr, [x21, 664]
	ldr	w1, [x22, 8]
	str	w1, [x21, 576]
	str	wzr, [x21, 656]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 2856]
	beq	.L627
	ldr	w20, [x22, 616]
	cmp	w20, 1
	beq	.L628
	mov	w20, w23
.L623:
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 912
	ret
	.p2align 3
.L628:
	ldr	w0, [x21, 588]
	add	x1, x29, 496
	ldr	x3, [x27, 104]
	mov	x2, 256
	orr	w0, w0, 65536
	str	w24, [x21, 584]
	str	w0, [x21, 588]
	add	x0, x19, 1168
	str	w26, [x21, 644]
	str	w25, [x21, 656]
	blr	x3
	ldr	x3, [x27, 104]
	add	x1, x29, 752
	mov	x2, 256
	add	x0, x19, 1424
	blr	x3
	ldr	x3, [x27, 104]
	add	x1, x29, 96
	ldr	x0, [x19, 2232]
	mov	x2, 196
	blr	x3
	ldr	x0, [x19, 2240]
	mov	x2, 196
	ldr	x3, [x27, 104]
	add	x1, x29, 296
	blr	x3
	b	.L623
	.p2align 3
.L626:
	add	x21, x20, 45056
	add	x19, x20, 86016
	add	x3, x21, 264
	ldr	x4, [x27, 104]
	add	x3, x3, 40960
	add	x1, x19, 1168
	mov	x2, 256
	add	x0, x29, 496
	ldr	w24, [x3, 584]
	ldr	w26, [x3, 644]
	ldr	w25, [x3, 656]
	blr	x4
	ldr	x3, [x27, 104]
	add	x1, x19, 1424
	mov	x2, 256
	add	x0, x29, 752
	blr	x3
	ldr	x1, [x19, 2232]
	mov	x2, 196
	ldr	x3, [x27, 104]
	add	x0, x29, 96
	blr	x3
	ldr	x1, [x19, 2240]
	mov	x2, 196
	ldr	x3, [x27, 104]
	add	x0, x29, 296
	blr	x3
	b	.L621
.L627:
	ldr	x1, .LC113
	mov	w0, 0
	mov	w20, -20
	bl	dprint_vfmw
	b	.L623
	.size	MPEG2DEC_Init, .-MPEG2DEC_Init
	.align	3
.LC111:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC113:
	.xword	.LC112
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_Destroy
	.type	MPEG2DEC_Destroy, %function
MPEG2DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, 20744
	ldr	x1, .LC115
	movk	x0, 0x1, lsl 16
	add	x2, x19, x0
	mov	w0, 2
	ldr	w2, [x2, 596]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG2DEC_Destroy, .-MPEG2DEC_Destroy
	.align	3
.LC115:
	.xword	.LC114
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_RecycleImage
	.type	MPEG2DEC_RecycleImage, %function
MPEG2DEC_RecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbz	x20, .L635
	add	x20, x20, 86016
	mov	w1, w19
	mov	w2, 0
	ldr	w0, [x20, 2856]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 2856]
	mov	w1, w19
	bl	FSP_GetFsImagePtr
	add	x19, x0, 544
	add	x21, x0, 576
	cbz	x0, .L634
.L636:
	ldr	x1, [x19]
	ldr	w0, [x20, 2856]
	bl	FreeUsdByDec
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L636
.L634:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L635:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MPEG2DEC_RecycleImage, .-MPEG2DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_GetRemainImg
	.type	MPEG2DEC_GetRemainImg, %function
MPEG2DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 86016
	bl	_mcount
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L639
	add	x23, x19, 45056
	add	x20, x19, 86016
	add	x21, x23, 264
	add	x21, x21, 40960
	ldr	w0, [x20, 2856]
	ldr	w1, [x21, 688]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L639
	ldr	w0, [x20, 2856]
	ldr	w1, [x21, 688]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L658
.L639:
	add	x21, x20, 2248
.L645:
	mov	x0, x21
	bl	GetVoLastImageID
.L653:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L658:
	mov	x0, x19
	bl	MP2_SetImgFormat
	add	x1, x20, 872
	add	x0, x22, 544
	add	x3, x22, 576
.L641:
	ldr	x2, [x1]
	cbz	x2, .L640
	str	x2, [x0]
.L640:
	add	x0, x0, 8
	str	xzr, [x1], 8
	cmp	x0, x3
	bne	.L641
	add	x23, x23, 264
	mov	w0, 1
	add	x23, x23, 40960
	mov	w2, w0
	add	x21, x20, 2248
	str	wzr, [x23, 640]
	str	w0, [x22, 180]
	ldr	w1, [x22, 148]
	ldr	w0, [x20, 2856]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 2856]
	mov	x4, x22
	mov	x3, x21
	mov	x2, x19
	mov	w1, 3
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L642
	ldr	w1, [x22, 148]
	mov	x0, x19
	bl	MPEG2DEC_RecycleImage
	b	.L645
	.p2align 3
.L642:
	ldr	w0, [x22, 152]
	cmp	w0, 100
	bhi	.L639
	ldr	w0, [x22, 68]
	cmp	w0, 31
	bls	.L639
	ldr	w1, [x22, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L653
	b	.L645
	.size	MPEG2DEC_GetRemainImg, .-MPEG2DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_GetImageBuffer
	.type	MPEG2DEC_GetImageBuffer, %function
MPEG2DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 45056
	add	x0, x0, 264
	ldrb	w1, [x0, 1]
	cmp	w1, 3
	beq	.L660
	add	x0, x0, 40960
	ldr	w0, [x0, 600]
	cbz	w0, .L662
.L660:
	add	x19, x19, 86016
	ldr	w0, [x19, 2856]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L662
	ldr	w0, [x19, 2856]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	bne	.L661
	ldr	w0, [x19, 2856]
	add	x1, x19, 2248
	bl	FSP_ClearNotInVoQueue
	b	.L661
	.p2align 3
.L662:
	mov	w20, 1
.L661:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MPEG2DEC_GetImageBuffer, .-MPEG2DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ClearCurPacket
	.type	MP2_ClearCurPacket, %function
MP2_ClearCurPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 20]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldrsb	w0, [x19]
	cmp	w0, 1
	beq	.L671
	ldr	w1, [x19, 24]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
.L671:
	ldr	x3, .LC116
	mov	x2, 48
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_ClearCurPacket, .-MP2_ClearCurPacket
	.align	3
.LC116:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ReceivePacket
	.type	MP2_ReceivePacket, %function
MP2_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	w22, w2
	bl	_mcount
	cbz	x20, .L681
	add	x1, x19, 40960
	str	wzr, [x1, 520]
	ldr	w0, [x20, 16]
	str	w0, [x1, 580]
	ldr	w0, [x20, 12]
	str	w0, [x1, 532]
	ldr	x0, [x20]
	str	x0, [x1, 560]
	ldr	w0, [x20, 16]
	str	w0, [x1, 540]
	ldrb	w0, [x20, 9]
	strb	w0, [x1, 528]
	ldr	w0, [x20, 20]
	str	w0, [x1, 548]
	ldrb	w21, [x20, 9]
	cmp	w21, 1
	beq	.L678
	ldr	w0, [x20, 92]
	mov	w21, 1
	str	w0, [x1, 536]
	ldr	x0, [x20, 80]
	str	x0, [x1, 568]
	ldr	w0, [x20, 96]
	str	w0, [x1, 544]
	ldrb	w0, [x20, 89]
	strb	w0, [x1, 529]
	ldr	w0, [x20, 100]
	str	w0, [x1, 552]
	ldrb	w0, [x20, 89]
	cmp	w0, w21
	beq	.L677
	add	x1, x1, 528
	mov	w0, w22
	bl	MP2_ClearCurPacket
	ldrb	w2, [x20, 89]
	mov	w0, w21
	ldr	x1, .LC120
	mov	w21, 0
	bl	dprint_vfmw
.L677:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L678:
	strb	wzr, [x1, 529]
	mov	w0, w21
	str	wzr, [x1, 536]
	str	wzr, [x1, 544]
	str	wzr, [x1, 552]
	str	xzr, [x1, 568]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L681:
	add	x19, x19, 40960
	ldr	x1, .LC118
	mov	w0, 1
	mov	w21, 0
	ldr	w2, [x19, 596]
	bl	dprint_vfmw
	b	.L677
	.size	MP2_ReceivePacket, .-MP2_ReceivePacket
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ClearCurPic
	.type	MP2_ClearCurPic, %function
MP2_ClearCurPic:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 16
	mov	w20, 0
	bl	_mcount
	add	x21, x21, 86016
	add	x0, x22, 45056
	mov	x23, x0
	ldr	w0, [x0, 236]
	cbnz	w0, .L691
	b	.L686
	.p2align 3
.L684:
	ldr	w0, [x23, 236]
	cmp	w0, w20
	bls	.L686
.L691:
	sxtw	x19, w20
	ldr	w0, [x21, 2856]
	lsl	x1, x19, 2
	add	w20, w20, 1
	sub	x1, x1, x19
	lsl	x1, x1, 2
	sub	x19, x1, x19
	add	x19, x22, x19, lsl 2
	ldr	w1, [x19, 260]
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x19, 240]
	cbz	w0, .L684
	ldr	w0, [x19, 248]
	cbz	w0, .L684
	ldr	w1, [x19, 264]
	ldr	w0, [x21, 2856]
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x23, 236]
	cmp	w0, w20
	bhi	.L691
.L686:
	add	x22, x22, 45056
	str	wzr, [x22, 236]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MP2_ClearCurPic, .-MP2_ClearCurPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_VDMPostProc
	.type	MPEG2DEC_VDMPostProc, %function
MPEG2DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 45056
	add	x19, x20, 86016
	add	x21, x22, 264
	mov	w23, w1
	add	x21, x21, 40960
	bl	_mcount
	ldrb	w0, [x20, 161]
	mov	w2, w23
	ldr	x1, .LC122
	add	x25, x20, 16
	ldr	x24, [x19, 2232]
	strb	w0, [x21, 788]
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x0, [x20, 8]
	ldr	x1, [x19, 2232]
	ldrb	w2, [x0, 144]
	add	x0, x0, 45056
	strb	w2, [x1, 4]
	ldr	w0, [x0, 240]
	str	w0, [x1, 8]
	ldr	x0, [x19, 2232]
	ldr	x1, [x20]
	ldr	w2, [x0, 48]
	str	w2, [x1, 568]
	ldr	x1, [x20]
	ldr	w0, [x0, 52]
	str	w0, [x1, 572]
	ldr	w1, [x19, 2864]
	ldr	w0, [x19, 2860]
	ldr	x2, [x20]
	cmp	w0, w1
	sub	w0, w0, w1
	csel	w1, w0, wzr, ge
	mov	x0, x20
	str	w1, [x2, 576]
	bl	MP2_ClearCurPic
	ldr	x3, .LC123
	mov	x2, 45304
	mov	w1, 0
	mov	x0, x25
	ldr	x3, [x3, 96]
	blr	x3
	ldr	w1, [x21, 692]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	ldr	w1, [x21, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFsImagePtr
	mov	x26, x0
	ldr	w1, [x21, 684]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFsImagePtr
	cbz	x25, .L765
	ldrb	w0, [x24, 30]
	strb	w0, [x22, 264]
	str	w23, [x25, 152]
	tbnz	w23, #31, .L700
	cmp	w23, 100
	mov	w0, 100
	csel	w23, w23, w0, le
	str	w23, [x25, 152]
	ldrb	w0, [x24, 30]
	cmp	w0, 3
	beq	.L701
	ldr	x0, [x20]
	ldr	w0, [x0]
	cmp	w23, w0
	bhi	.L766
.L701:
	ldr	x1, .LC127
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	MP2_SetImgFormat
	ldrb	w0, [x24, 17]
	cmp	w0, 3
	beq	.L705
	add	x1, x22, 264
	mov	w0, 1
	add	x1, x1, 40960
	ldr	w1, [x1, 600]
	cmp	w1, w0
	beq	.L705
.L750:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L766:
	ldr	w0, [x19, 2856]
	mov	w2, 1
	ldr	w1, [x21, 692]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2856]
	ldr	w1, [x21, 688]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L703
	ldr	w0, [x19, 2856]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x20, 552]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x20, 560]
	bl	FreeUsdByDec
	ldr	w0, [x19, 2856]
	ldr	x1, [x20, 568]
	bl	FreeUsdByDec
	add	x0, x20, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x19, 2856]
	ldr	w1, [x21, 688]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2856]
	mov	w2, 1
	ldr	w1, [x21, 684]
	bl	FSP_ClearLogicFs
	str	wzr, [x21, 684]
	str	wzr, [x21, 688]
	ldr	w0, [x19, 2856]
	bl	FSP_GetFspType
	cbz	w0, .L703
	ldr	w0, [x19, 2856]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 684]
	str	w0, [x21, 688]
.L703:
	add	x22, x22, 264
	mov	w0, 1
	add	x22, x22, 40960
	str	wzr, [x22, 648]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L705:
	add	x0, x25, 544
	add	x1, x19, 872
	add	x25, x25, 576
.L707:
	ldr	x2, [x1]
	cbz	x2, .L706
	str	x2, [x0]
.L706:
	add	x0, x0, 8
	str	xzr, [x1], 8
	cmp	x0, x25
	bne	.L707
	add	x0, x22, 264
	add	x0, x0, 40960
	str	wzr, [x0, 640]
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbz	w1, .L767
.L708:
	add	x0, x22, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 692]
	str	w1, [x0, 696]
.L709:
	cmn	w1, #1
	beq	.L711
	ldr	w0, [x19, 2856]
	bl	FSP_GetDisplay
	cmp	w0, 1
	beq	.L715
	add	x1, x22, 264
	ldr	w0, [x19, 2856]
	add	x1, x1, 40960
	ldr	w1, [x1, 696]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L715
.L711:
	ldrb	w0, [x24, 35]
	cmp	w0, 1
	beq	.L768
	ldrb	w0, [x24, 26]
	cmp	w0, 1
	beq	.L769
	add	x1, x22, 264
	add	x1, x1, 40960
	ldr	w0, [x1, 772]
	add	w0, w0, 1
	str	w0, [x1, 772]
	lsl	w0, w0, 1
	str	w0, [x1, 768]
.L730:
	ldr	w1, [x19, 1028]
	add	x22, x22, 264
	mov	w0, 1
	add	x22, x22, 40960
	add	w1, w1, w0
	str	w1, [x19, 1028]
	ldr	w1, [x22, 596]
	add	w1, w1, w0
	str	w1, [x22, 596]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L700:
	str	wzr, [x25, 152]
	b	.L701
	.p2align 3
.L767:
	ldrb	w1, [x24, 30]
	cmp	w1, 3
	beq	.L708
	ldr	w1, [x0, 684]
	str	w1, [x0, 696]
	b	.L709
	.p2align 3
.L769:
	add	x0, x22, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 772]
	ldr	w2, [x0, 768]
	add	w1, w1, 1
	str	w1, [x0, 772]
	ldrb	w1, [x24, 24]
	add	w1, w1, 2
	add	w1, w1, w2
	str	w1, [x0, 768]
	b	.L730
	.p2align 3
.L715:
	add	x1, x22, 264
	ldr	w0, [x19, 2856]
	add	x1, x1, 40960
	ldr	w1, [x1, 696]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L770
	ldr	w2, [x0, 152]
	cbz	w2, .L717
	ldr	x0, [x20]
	ldr	w3, [x0, 4]
	cmp	w2, w3
	bhi	.L718
.L717:
	add	x23, x22, 264
	ldr	w0, [x19, 2856]
	add	x23, x23, 40960
	ldr	w25, [x23, 696]
	mov	w1, w25
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC130
	mov	w2, w25
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w1, [x23, 696]
	mov	w2, 1
	ldr	w0, [x19, 2856]
	bl	FSP_SetDisplay
	ldr	w23, [x19, 2856]
	ldr	w1, [x19, 952]
	mov	w0, w23
	bl	FSP_GetFsImagePtr
	mov	x26, x0
	ldr	w1, [x19, 960]
	mov	w0, w23
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	cmp	x26, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L771
	ldr	x0, [x0, 584]
	cmn	x0, #1
	beq	.L720
	ldr	w1, [x19, 952]
	mov	w0, w23
	bl	FSP_GetDisplay
	cmp	w0, 1
	beq	.L725
	ldr	w1, [x19, 952]
	mov	w0, w23
	bl	FSP_GetDisplay
	cmp	w0, 2
	bne	.L720
.L725:
	ldr	x1, [x25, 584]
	ldr	x2, [x26, 584]
	cmp	x1, x2
	bls	.L720
	mov	w0, w23
	bl	IsPtsRewind
	cbnz	w0, .L720
	ldr	x1, .LC134
	mov	w0, 29
	ldr	x2, [x25, 584]
	ldr	x3, [x26, 584]
	bl	dprint_vfmw
	ldr	x1, [x26, 584]
	ldr	x0, [x25, 584]
	str	x1, [x25, 584]
	str	x0, [x26, 584]
	.p2align 2
.L720:
	ldr	w0, [x19, 2856]
	mov	x4, x21
	add	x3, x19, 2248
	mov	x2, x20
	mov	w1, 3
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L726
	add	x20, x21, 544
	add	x21, x21, 576
.L727:
	ldr	x1, [x20]
	ldr	w0, [x19, 2856]
	bl	FreeUsdByDec
	str	xzr, [x20], 8
	cmp	x21, x20
	bne	.L727
	add	x1, x22, 264
	ldr	w0, [x19, 2856]
	add	x1, x1, 40960
	mov	w2, 0
	ldr	w1, [x1, 696]
	bl	FSP_SetDisplay
	mov	w0, 0
	b	.L750
	.p2align 3
.L768:
	add	x0, x22, 264
	ldrb	w2, [x24, 24]
	add	x0, x0, 40960
	ldrb	w1, [x24, 18]
	add	w1, w2, w1
	ldr	w2, [x0, 772]
	add	w1, w1, 1
	add	w1, w1, w2
	str	w1, [x0, 772]
	lsl	w1, w1, 1
	str	w1, [x0, 768]
	b	.L730
	.p2align 3
.L718:
	ldr	x1, .LC136
	mov	w0, 1
	add	x20, x21, 544
	add	x21, x21, 576
	bl	dprint_vfmw
.L728:
	ldr	x1, [x20]
	ldr	w0, [x19, 2856]
	bl	FreeUsdByDec
	str	xzr, [x20], 8
	cmp	x20, x21
	bne	.L728
	add	x1, x22, 264
	ldr	w0, [x19, 2856]
	add	x1, x1, 40960
	mov	w2, 0
	ldr	w1, [x1, 696]
	bl	FSP_SetDisplay
	b	.L711
	.p2align 3
.L765:
	ldr	x1, .LC125
	mov	x4, x0
	mov	x3, x26
	mov	x2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L750
	.p2align 3
.L726:
	ldr	w0, [x19, 2864]
	add	w0, w0, 1
	str	w0, [x19, 2864]
	b	.L711
.L771:
	ldr	x1, .LC132
	mov	w0, 0
	bl	dprint_vfmw
	b	.L720
.L770:
	ldr	x1, .LC128
	mov	w2, 3535
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L750
	.size	MPEG2DEC_VDMPostProc, .-MPEG2DEC_VDMPostProc
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC123:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC128:
	.xword	.LC56
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.align	3
.LC134:
	.xword	.LC133
	.align	3
.LC136:
	.xword	.LC135
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_u_v
	.type	MP2_u_v, %function
MP2_u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	mov	w21, w1
	bl	_mcount
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, w21
	mov	x0, x20
	bl	BsSkip
	ldr	x1, .LC138
	mov	w3, w19
	mov	x2, x22
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP2_u_v, .-MP2_u_v
	.align	3
.LC138:
	.xword	.LC137
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_DecSliceHeader
	.type	MP2_DecSliceHeader, %function
MP2_DecSliceHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 4]
	mov	w1, 1
	str	wzr, [x20, 24]
	mov	w4, 0
	cmp	w0, 175
	str	w1, [x20, 16]
	ldr	x19, [x20, 56]
	bls	.L774
	ldr	w0, [x20]
	cbz	w0, .L785
.L774:
	ldr	w3, [x20, 20]
	mov	w1, 5
	ldr	w5, [x20, 8]
	mov	x0, x19
	sub	w3, w3, #1
	ldr	x2, .LC142
	add	w4, w3, w4
	mul	w3, w4, w5
	cmp	w3, wzr
	cset	w4, ne
	sub	w3, w3, w4
	str	w3, [x20, 28]
	bl	MP2_u_v
	str	wzr, [x20, 32]
	str	w0, [x20, 44]
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	cbnz	w0, .L776
	ldr	x20, .LC144
.L778:
	mov	x2, x20
	mov	w1, 1
	mov	x0, x19
	bl	MP2_u_v
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L776:
	ldr	x2, .LC146
	mov	w1, 1
	mov	x0, x19
	bl	MP2_u_v
	ldr	x2, .LC148
	mov	w1, 1
	mov	x0, x19
	bl	MP2_u_v
	str	w0, [x20, 32]
	ldr	x2, .LC150
	mov	w1, 7
	mov	x0, x19
	bl	MP2_u_v
	ldr	x20, .LC144
	ldr	x21, .LC152
	b	.L777
	.p2align 3
.L786:
	bl	BsShow
	cbz	w0, .L778
	mov	w1, 1
	mov	x2, x20
	mov	x0, x19
	bl	MP2_u_v
	mov	x2, x21
	mov	w1, 8
	mov	x0, x19
	bl	MP2_u_v
.L777:
	mov	x0, x19
	bl	BsResidBits
	cmp	w0, wzr
	mov	w1, 1
	mov	x0, x19
	bgt	.L786
	b	.L778
	.p2align 3
.L785:
	ldr	x2, .LC140
	mov	w1, 3
	mov	x0, x19
	bl	MP2_u_v
	lsl	w4, w0, 7
	str	w0, [x20, 24]
	b	.L774
	.size	MP2_DecSliceHeader, .-MP2_DecSliceHeader
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_ExitMb
	.type	MP2_ExitMb, %function
MP2_ExitMb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	str	wzr, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_ExitMb, .-MP2_ExitMb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_WriteSliceInfo
	.type	MP2_WriteSliceInfo, %function
MP2_WriteSliceInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 16
	bl	_mcount
	add	x2, x21, 45056
	add	x0, x20, 86016
	ldr	w2, [x2, 236]
	ldr	w4, [x0, 1096]
	cmp	w2, 1023
	uxtw	x3, w2
	lsl	x19, x3, 2
	sub	x19, x19, x3
	lsl	x19, x19, 2
	sub	x19, x19, x3
	add	x19, x21, x19, lsl 2
	str	w4, [x19, 272]
	ldr	w3, [x0, 1108]
	str	w3, [x19, 276]
	ldr	w1, [x0, 1104]
	str	w1, [x19, 268]
	bhi	.L794
	mov	x1, 20744
	add	x0, x0, 1128
	movk	x1, 0x1, lsl 16
	add	x20, x20, x1
	ldr	w1, [x0, 32]
	ldr	w2, [x20, 532]
	and	w3, w1, 7
	str	w3, [x19, 252]
	add	w1, w2, w1, lsr 3
	str	w1, [x19, 236]
	ldr	w1, [x20, 548]
	str	w1, [x19, 260]
	bl	BsResidBits
	str	w0, [x19, 244]
	ldrsh	w0, [x20, 528]
	cmp	w0, 1
	beq	.L795
	cmp	w0, 256
	bne	.L793
	ldr	w0, [x20, 536]
	str	w0, [x19, 240]
	str	wzr, [x19, 256]
	ldr	w0, [x20, 552]
	str	w0, [x19, 264]
	ldr	w0, [x20, 544]
	lsl	w0, w0, 3
	str	w0, [x19, 248]
.L792:
	add	x21, x21, 45056
	mov	w0, 1
	ldr	w1, [x21, 236]
	add	w1, w1, w0
	str	w1, [x21, 236]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L794:
	ldr	x1, .LC154
	mov	w3, 1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	MP2_ClearCurPic
	mov	x0, 20744
	mov	w1, -5767169
	movk	x0, 0x1, lsl 16
	add	x20, x20, x0
	mov	w0, 0
	ldr	w2, [x20, 588]
	str	wzr, [x20, 664]
	and	w1, w2, w1
	str	w1, [x20, 588]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L795:
	str	wzr, [x19, 240]
	str	wzr, [x19, 248]
	str	wzr, [x19, 256]
	str	wzr, [x19, 264]
	b	.L792
	.p2align 3
.L793:
	ldrsb	w3, [x20, 529]
	mov	w0, 1
	ldrsb	w2, [x20, 528]
	ldr	x1, .LC156
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP2_WriteSliceInfo, .-MP2_WriteSliceInfo
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_MbAddrInc
	.type	MP2_MbAddrInc, %function
MP2_MbAddrInc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 4
	mov	x0, x21
	bl	BsShow
	ldr	x20, .LC157
	ubfiz	x0, x0, 3, 32
	add	x1, x20, 80
	add	x2, x1, x0
	ldr	w19, [x1, x0]
	ldr	w1, [x2, 4]
	cmp	w19, 6
	bls	.L800
	cmp	w19, 9
	beq	.L801
	mov	w1, 11
	mov	x0, x21
	add	x20, x20, 208
	bl	BsShow
	and	w0, w0, 127
	sub	w1, w0, #24
	ldr	x2, .LC159
	lsl	x1, x1, 3
	mov	x0, x21
	add	x3, x20, x1
	ldr	w19, [x20, x1]
	ldr	w1, [x3, 4]
	bl	MP2_u_v
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L800:
	ldr	x2, .LC159
	mov	x0, x21
	bl	MP2_u_v
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L801:
	ldr	x2, .LC159
	mov	x0, x21
	bl	MP2_u_v
	ldr	x21, [sp, 32]
	sub	w0, w19, w0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP2_MbAddrInc, .-MP2_MbAddrInc
	.align	3
.LC157:
	.xword	.LANCHOR1
	.align	3
.LC159:
	.xword	.LC158
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_InitMb
	.type	MP2_InitMb, %function
MP2_InitMb:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x21, .LC165
	ldr	x19, [x22, 56]
	b	.L803
	.p2align 3
.L807:
	cmp	w0, 15
	beq	.L804
	cmp	w0, 8
	add	w20, w20, 33
	bne	.L815
.L804:
	mov	x2, x21
	mov	w1, 11
	mov	x0, x19
	bl	MP2_u_v
.L803:
	mov	w1, 11
	mov	x0, x19
	bl	BsShow
	cmp	w0, 23
	bls	.L807
	mov	x0, x19
	bl	MP2_MbAddrInc
	ldr	w1, [x22, 16]
	cbz	w1, .L808
	ldr	w2, [x22, 28]
	add	w0, w20, w0
	cbnz	w2, .L816
	sub	w2, w0, #1
.L810:
	ldr	w3, [x22, 12]
	mov	w0, 1
	str	w2, [x22, 40]
	sub	w3, w3, #1
	cmp	w2, w3
	bls	.L806
	ldr	x1, .LC167
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L815:
	ldr	x1, .LC163
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L806:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L816:
	add	w2, w0, w2
	b	.L810
	.p2align 3
.L808:
	ldr	x1, .LC169
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MP2_InitMb, .-MP2_InitMb
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetFirstMbInSlice
	.type	MP2_GetFirstMbInSlice, %function
MP2_GetFirstMbInSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	MP2_DecSliceHeader
	mov	x0, x19
	bl	MP2_InitMb
	str	wzr, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_GetFirstMbInSlice, .-MP2_GetFirstMbInSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_DecSlice
	.type	MP2_DecSlice, %function
MP2_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w23, w1
	add	x20, x21, 86016
	bl	_mcount
	add	x19, x20, 1064
	mov	x0, 20744
	movk	x0, 0x1, lsl 16
	ldr	x3, [x20, 2232]
	add	x0, x21, x0
	ldr	x1, [x0, 560]
	str	x1, [x19, 48]
	ldr	w1, [x0, 540]
	str	w1, [x19, 36]
	ldr	w0, [x0, 644]
	cmp	w0, 1
	cset	w0, eq
	str	w0, [x20, 1064]
	ldr	w0, [x3, 68]
	str	w0, [x19, 4]
	ldr	w0, [x3, 64]
	str	w0, [x19, 8]
	ldp	w2, w0, [x3, 56]
	add	w2, w2, 15
	add	w0, w0, 15
	lsr	w2, w2, 4
	lsr	w0, w0, 4
	mul	w0, w2, w0
	str	w0, [x19, 12]
	ldrb	w1, [x3, 17]
	cmp	w1, 3
	beq	.L819
	lsr	w0, w0, 1
	str	w0, [x19, 12]
.L819:
	add	x1, x20, 1128
	mov	x0, x19
	str	x1, [x20, 1120]
	and	w23, w23, 255
	str	w23, [x20, 1084]
	bl	MP2_DecSliceHeader
	mov	x0, x19
	bl	MP2_InitMb
	str	wzr, [x20, 1080]
	cmp	w0, 1
	mov	w19, w0
	beq	.L820
	ldr	x1, .LC171
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC172
	ldr	x4, [x0]
	cbz	x4, .L833
.L834:
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L833:
	mov	w0, 0
.L822:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L820:
	mov	x0, x21
	bl	MP2_WriteSliceInfo
	cmp	w0, 1
	beq	.L822
	ldr	x1, .LC174
	mov	w0, w19
	bl	dprint_vfmw
	ldr	x0, .LC172
	ldr	x4, [x0]
	cbnz	x4, .L834
	b	.L833
	.size	MP2_DecSlice, .-MP2_DecSlice
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC172:
	.xword	g_event_report
	.align	3
.LC174:
	.xword	.LC173
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetHDR
	.type	MP2_GetHDR, %function
MP2_GetHDR:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	add	x20, x27, 86016
	add	x23, x27, 45056
	bl	_mcount
	add	x21, x20, 1128
	mov	w1, 32
	mov	x0, x21
	strb	wzr, [x20, 2872]
	add	x22, x23, 264
	add	x22, x22, 40960
	ldr	x24, [x20, 2232]
	ldr	x25, [x20, 2240]
	bl	BsShow
	mov	w19, w0
	mov	x0, x21
	ldr	w26, [x22, 588]
	bl	BsPos
	str	w0, [x22, 668]
	mov	w1, 32
	mov	x0, x21
	bl	BsSkip
	cmp	w19, 439
	beq	.L907
	mov	w0, 440
	cmp	w19, 435
	ccmp	w19, w0, 4, ne
	bne	.L842
.L838:
	add	x0, x23, 264
	add	x0, x0, 40960
	ldr	w1, [x0, 664]
	cmp	w1, 1
	beq	.L908
.L839:
	cmp	w19, 435
	beq	.L844
.L911:
	ble	.L909
	cmp	w19, 437
	beq	.L848
	blt	.L865
	cmp	w19, 439
	beq	.L865
	cmp	w19, 440
	bne	.L843
	add	x19, x23, 264
	mov	x0, x21
	add	x19, x19, 40960
	ldr	w1, [x19, 520]
	ldr	w22, [x19, 660]
	add	w22, w22, w1
	bl	BsPos
	ldr	x1, .LC182
	add	w2, w22, w0, lsr 3
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x27
	bl	group_of_pictures_header
	mov	x0, x21
	bl	BsResidBits
	tbnz	w0, #31, .L910
.L865:
	mov	w21, 0
.L841:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L842:
	mov	w0, 439
	cmp	w19, 256
	ccmp	w19, w0, 4, ne
	beq	.L838
	cmp	w19, 435
	bne	.L911
.L844:
	add	x19, x23, 264
	add	x19, x19, 40960
	ldr	w0, [x19, 520]
	ldr	w22, [x19, 660]
	add	w22, w22, w0
	mov	x0, x21
	bl	BsPos
	add	w2, w22, w0, lsr 3
	ldr	x1, .LC177
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x27
	bl	sequence_header
	mov	x0, x21
	bl	BsResidBits
	tbnz	w0, #31, .L912
	ldr	w0, [x19, 588]
	and	w0, w0, 7
	cbnz	w0, .L853
	mov	w0, 1
	mov	x2, 196
	strb	w0, [x24]
	mov	x1, x24
	mov	x0, x25
	mov	w21, 0
	bl	memcpy
	ldr	w0, [x19, 592]
	add	w0, w0, 1
	str	w0, [x19, 592]
	b	.L841
	.p2align 3
.L909:
	cmp	w19, 256
	beq	.L846
	blt	.L843
	cmp	w19, 433
	blt	.L843
	add	x23, x23, 264
	mov	x0, x21
	add	x23, x23, 40960
	ldr	w1, [x23, 520]
	ldr	w19, [x23, 660]
	add	w19, w19, w1
	bl	BsPos
	ldr	x1, .LC190
	add	w2, w19, w0, lsr 3
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x27
	bl	MP2_GetUsrData
	mov	w21, w0
	cbnz	w0, .L859
	ldr	w0, [x20, 2856]
	add	x1, x23, 528
	bl	MP2_ClearCurPacket
	ldr	x0, .LC178
	ldr	x4, [x0]
	cbz	x4, .L866
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w21, -1
	blr	x4
	b	.L841
	.p2align 3
.L846:
	add	x19, x23, 264
	mov	x0, x21
	add	x19, x19, 40960
	ldr	w1, [x19, 520]
	ldr	w22, [x19, 660]
	add	w22, w22, w1
	bl	BsPos
	ldr	x1, .LC186
	add	w2, w22, w0, lsr 3
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x27
	bl	picture_header
	mov	x0, x21
	bl	BsResidBits
	tbz	w0, #31, .L865
	ldr	x0, .LC178
	str	w26, [x19, 588]
	ldr	x4, [x0]
	cbz	x4, .L858
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L858:
	ldr	w0, [x20, 2856]
	mov	x1, 41752
	add	x1, x23, x1
	mov	w21, -1
	bl	MP2_ClearCurPacket
	ldr	x1, .LC188
	mov	w2, 256
	mov	w0, 1
	bl	dprint_vfmw
	b	.L841
	.p2align 3
.L908:
	ldr	w2, [x0, 588]
	tbz	x2, 22, .L839
	strb	w1, [x20, 2872]
	orr	w2, w2, 8388608
	str	wzr, [x0, 664]
	mov	w21, w1
	str	w2, [x0, 588]
	mov	x0, x27
	bl	MP2_ProtocolPPSCheck
	b	.L841
	.p2align 3
.L907:
	ldr	x0, .LC175
	mov	x2, 40
	mov	x1, x21
	ldr	x3, [x0, 104]
	add	x0, x29, 104
	blr	x3
	mov	w1, 32
	add	x0, x29, 104
	bl	BsGet
	mov	w28, w0
	mov	w1, 32
	add	x0, x29, 104
	bl	BsGet
	mov	w1, 20553
	movk	w1, 0x4853, lsl 16
	cmp	w28, w1
	mov	w1, 20036
	movk	w1, 0x4345, lsl 16
	ccmp	w0, w1, 0, eq
	bne	.L838
	ldr	w21, [x22, 664]
	cmp	w21, 1
	beq	.L913
.L840:
	mov	w0, 1
	mov	w21, 0
	strb	w0, [x20, 2874]
	b	.L841
	.p2align 3
.L843:
	sub	w0, w19, #257
	cmp	w0, 174
	bhi	.L861
	add	x22, x23, 264
	add	x22, x22, 40960
	ldr	w0, [x22, 584]
	cbz	w0, .L862
.L864:
	add	x23, x23, 264
	mov	w1, 589824
	add	x23, x23, 40960
	ldr	w0, [x23, 588]
	tst	w0, w1
	beq	.L865
	orr	w0, w0, 4194304
	mov	w20, 1
	str	w0, [x23, 588]
	mov	w1, w19
	str	w20, [x23, 664]
	mov	x0, x27
	bl	MP2_DecSlice
	cmp	w0, w20
	mov	w21, w0
	beq	.L841
	ldr	x1, .LC196
	mov	w2, w19
	mov	w0, w20
	mov	w21, 0
	bl	dprint_vfmw
	b	.L841
	.p2align 3
.L848:
	add	x19, x23, 264
	mov	x0, x21
	add	x19, x19, 40960
	ldr	w1, [x19, 520]
	ldr	w22, [x19, 660]
	add	w22, w22, w1
	bl	BsPos
	ldr	x1, .LC194
	add	w2, w22, w0, lsr 3
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x27
	bl	extension
	mov	x0, x21
	bl	BsResidBits
	tbz	w0, #31, .L865
	ldr	x0, .LC178
	str	w26, [x19, 588]
	ldr	x4, [x0]
	cbz	x4, .L860
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L860:
	mov	x1, 41752
	ldr	w0, [x20, 2856]
	add	x1, x23, x1
	mov	w21, -1
	bl	MP2_ClearCurPacket
	b	.L841
	.p2align 3
.L853:
	ldrb	w0, [x25]
	cmp	w0, 1
	beq	.L914
.L861:
	ldr	x0, .LC178
	ldr	x4, [x0]
	cbz	x4, .L865
.L903:
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w21, 0
	blr	x4
	b	.L841
	.p2align 3
.L859:
	ldr	x1, .LC192
	mov	w0, 1
	bl	dprint_vfmw
	b	.L841
	.p2align 3
.L913:
	ldr	w0, [x22, 588]
	tbz	x0, 22, .L840
	strb	w21, [x20, 2874]
	orr	w0, w0, 8388608
	strb	w21, [x20, 2872]
	str	w0, [x22, 588]
	mov	x0, x27
	str	wzr, [x22, 664]
	bl	MP2_ProtocolPPSCheck
	b	.L841
	.p2align 3
.L866:
	mov	w21, -1
	b	.L841
	.p2align 3
.L862:
	mov	x0, x27
	mov	w21, 0
	bl	MP2_GetSequenceInfo
	ldr	w0, [x22, 656]
	cbz	w0, .L841
	ldrb	w0, [x20, 2873]
	cmp	w0, 1
	beq	.L841
	ldr	w0, [x22, 584]
	cbnz	w0, .L864
	b	.L841
	.p2align 3
.L914:
	mov	x1, x25
	mov	x2, 196
	mov	x0, x24
	bl	memcpy
	ldr	x1, .LC178
	ldr	w0, [x19, 588]
	ldr	x4, [x1]
	and	w0, w0, -8
	str	w0, [x19, 588]
	cbnz	x4, .L903
	b	.L865
.L910:
	ldr	x0, .LC178
	str	w26, [x19, 588]
	ldr	x4, [x0]
	cbz	x4, .L857
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L857:
	ldr	w0, [x20, 2856]
	mov	x1, 41752
	add	x1, x23, x1
	mov	w21, -1
	bl	MP2_ClearCurPacket
	ldr	x1, .LC184
	mov	w2, 440
	mov	w0, 1
	bl	dprint_vfmw
	b	.L841
.L912:
	ldr	x0, .LC178
	str	w26, [x19, 588]
	ldr	x4, [x0]
	cbz	x4, .L852
	ldr	w0, [x20, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L852:
	ldr	w0, [x20, 2856]
	mov	x1, 41752
	add	x1, x23, x1
	mov	w21, -1
	bl	MP2_ClearCurPacket
	ldr	x1, .LC180
	mov	w2, 435
	mov	w0, 1
	bl	dprint_vfmw
	b	.L841
	.size	MP2_GetHDR, .-MP2_GetHDR
	.align	3
.LC175:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC177:
	.xword	.LC176
	.align	3
.LC178:
	.xword	g_event_report
	.align	3
.LC180:
	.xword	.LC179
	.align	3
.LC182:
	.xword	.LC181
	.align	3
.LC184:
	.xword	.LC183
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MPEG2DEC_Decode
	.type	MPEG2DEC_Decode, %function
MPEG2DEC_Decode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x20, 86016
	bl	_mcount
	add	x22, x19, 1680
	ldr	x3, .LC197
	mov	x1, x21
	mov	x2, 160
	mov	x0, x22
	add	x23, x20, 45056
	ldr	x3, [x3, 104]
	add	x21, x23, 264
	blr	x3
	ldr	w2, [x19, 2856]
	mov	x1, x22
	mov	x0, x21
	bl	MP2_ReceivePacket
	cmp	w0, 1
	beq	.L916
	ldr	x1, .LC199
	mov	w0, 1
	mov	w21, 0
	bl	dprint_vfmw
.L917:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L916:
	add	x21, x21, 40960
	add	x0, x19, 1128
	ldr	x1, [x21, 560]
	ldr	w2, [x21, 540]
	bl	BsInit
	ldr	x0, [x20]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L947
.L918:
	ldr	w0, [x19, 852]
	str	w0, [x19, 1056]
.L919:
	mov	x0, x20
	bl	MP2_GetHDR
	add	w0, w0, 1
	cmp	w0, 1
	bls	.L948
	mov	x0, x20
	bl	MP2_DecodingDecide
	cbz	w0, .L949
	cmn	w0, #1
	beq	.L922
	mov	x0, x20
	bl	MP2_GetPictureInfo
	cbnz	w0, .L925
	ldr	w0, [x19, 2856]
	mov	x1, 41752
	add	x1, x23, x1
	bl	MP2_ClearCurPacket
	mov	x0, x20
	bl	MP2_ClearCurPic
	ldr	x0, .LC200
	ldr	x4, [x0]
	cbz	x4, .L926
	ldr	w0, [x19, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L926:
	ldr	x1, .LC204
	mov	w0, 1
	mov	w21, 0
	bl	dprint_vfmw
	b	.L917
	.p2align 3
.L948:
	ldr	x0, [x20]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L950
.L921:
	ldrb	w0, [x19, 2873]
	cmp	w0, 1
	beq	.L922
	mov	x1, 41752
	ldr	w0, [x19, 2856]
	add	x1, x23, x1
	mov	w21, 0
	bl	MP2_ClearCurPacket
	b	.L917
	.p2align 3
.L950:
	ldr	w0, [x0, 888]
	cbz	w0, .L921
.L922:
	mov	w21, 0
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L947:
	ldr	w0, [x0, 888]
	cmp	w0, 1
	bne	.L918
	ldr	w0, [x19, 1056]
	str	w0, [x19, 852]
	b	.L919
	.p2align 3
.L949:
	ldr	w0, [x19, 2856]
	mov	x1, 41752
	add	x1, x23, x1
	bl	MP2_ClearCurPacket
	mov	x0, x20
	bl	MP2_ClearCurPic
	ldr	x0, .LC200
	ldr	x4, [x0]
	cbz	x4, .L924
	ldr	w0, [x19, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L924:
	ldr	x1, .LC202
	mov	w0, 22
	mov	w21, 0
	bl	dprint_vfmw
	b	.L917
	.p2align 3
.L925:
	mov	x0, x20
	bl	MP2_DecNewPic
	mov	w21, w0
	cbz	w0, .L951
	add	x0, x23, 264
	add	x0, x0, 40960
	ldr	w2, [x0, 660]
	ldr	w21, [x0, 520]
	ldr	w1, [x0, 540]
	lsl	w21, w21, 3
	add	w1, w2, w1
	str	w1, [x0, 660]
	b	.L917
	.p2align 3
.L951:
	add	x22, x23, 264
	ldr	w0, [x19, 2856]
	add	x22, x22, 40960
	mov	w2, 1
	ldr	w1, [x22, 692]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 2856]
	add	x1, x22, 528
	bl	MP2_ClearCurPacket
	mov	x0, x20
	bl	MP2_ClearCurPic
	ldr	x0, .LC200
	ldr	x4, [x0]
	cbz	x4, .L928
	ldr	w0, [x19, 2856]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L928:
	ldr	x1, .LC206
	mov	w0, 1
	bl	dprint_vfmw
	b	.L917
	.size	MPEG2DEC_Decode, .-MPEG2DEC_Decode
	.align	3
.LC197:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC200:
	.xword	g_event_report
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC206:
	.xword	.LC205
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MP2_GetPacketState
	.type	MP2_GetPacketState, %function
MP2_GetPacketState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 86016
	bl	_mcount
	mov	w0, 2
	ldrb	w1, [x19, 2872]
	ldr	x19, [sp, 16]
	cmp	w1, 1
	csel	w0, w0, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MP2_GetPacketState, .-MP2_GetPacketState
	.global	g_tmpusd
	.global	zigzag
	.global	default_intra_quantizer_matrix
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__FUNCTION__.11533, %object
	.size	__FUNCTION__.11533, 19
__FUNCTION__.11533:
	.string	"MP2_DecodingDecide"
	.zero	5
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	10
	.word	12
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	24
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	48
	.word	52
	.word	56
	.word	64
	.word	72
	.word	80
	.word	88
	.word	96
	.word	104
	.word	112
	.align	3
.LANCHOR1 = . + 0
	.type	CSWTCH.50, %object
	.size	CSWTCH.50, 12
CSWTCH.50:
	.word	5
	.word	1
	.word	2
	.zero	4
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	23976
	.word	24000
	.word	25000
	.word	29970
	.word	30000
	.word	50000
	.word	59940
	.word	60000
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	tab_for_first_4bit, %object
	.size	tab_for_first_4bit, 128
tab_for_first_4bit:
	.word	8
	.word	4
	.word	9
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	3
	.word	2
	.word	3
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.type	tab_for_last_7bit, %object
	.size	tab_for_last_7bit, 832
tab_for_last_7bit:
	.word	33
	.word	11
	.word	32
	.word	11
	.word	31
	.word	11
	.word	30
	.word	11
	.word	29
	.word	11
	.word	28
	.word	11
	.word	27
	.word	11
	.word	26
	.word	11
	.word	25
	.word	11
	.word	24
	.word	11
	.word	23
	.word	11
	.word	22
	.word	11
	.word	21
	.word	10
	.word	21
	.word	10
	.word	20
	.word	10
	.word	20
	.word	10
	.word	19
	.word	10
	.word	19
	.word	10
	.word	18
	.word	10
	.word	18
	.word	10
	.word	17
	.word	10
	.word	17
	.word	10
	.word	16
	.word	10
	.word	16
	.word	10
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.data
	.align	3
.LANCHOR3 = . + 0
	.type	zigzag, %object
	.size	zigzag, 64
zigzag:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.type	default_intra_quantizer_matrix, %object
	.size	default_intra_quantizer_matrix, 64
default_intra_quantizer_matrix:
	.byte	8
	.byte	16
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	16
	.byte	16
	.byte	22
	.byte	24
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	34
	.byte	38
	.byte	22
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	40
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	58
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	27
	.byte	29
	.byte	35
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	83
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC3:
	ASCII(.string	"mp2 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC6:
	ASCII(.string	"user set decode channel max resolution is (w=%d,h=%d), this stream (w=%d,h=%d) can NOT be decoded!\n" )
	.zero	4
.LC9:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC11:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC14:
	ASCII(.string	"ERROR: frm %d, integrality: %#x\n" )
	.zero	7
.LC16:
	ASCII(.string	"ERROR: frm %d, No Img buffer is allocated\n" )
	.zero	5
.LC18:
	ASCII(.string	"----------------- mp2 Imode -> %d ------------------\n" )
	.zero	2
.LC21:
	ASCII(.string	"frm %d pic type %d struct is %d total pos %#x\n" )
	.zero	1
.LC23:
	ASCII(.string	"NOTE: Drop non-I, cur is B\n" )
	.zero	4
.LC25:
	ASCII(.string	"NOTE: Drop non-I, cur is P\n" )
	.zero	4
.LC27:
	ASCII(.string	"NOTE: Drop non-I\n" )
	.zero	6
.LC29:
	ASCII(.string	"NOTE: Drop B\n" )
	.zero	2
.LC32:
	ASCII(.string	"%s %d pFwdImg = NULL,  pBwdImg = NULL!!\n" )
	.zero	7
.LC34:
	ASCII(.string	"fuction return value is null,%s %d !!\n" )
	.zero	1
.LC36:
	ASCII(.string	"dec P frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC38:
	ASCII(.string	"dec B frame, bwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC40:
	ASCII(.string	"dec B frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC43:
	ASCII(.string	"Protocol %d\n" )
	.zero	3
.LC45:
	ASCII(.string	"seq size change, call vpss to release all frames.\n" )
	.zero	5
.LC47:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC50:
	ASCII(.string	"new seq size %dx%d\n" )
	.zero	4
.LC54:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC56:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC58:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC60:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC65:
	ASCII(.string	"ERROR: frm %d, lost one field\n" )
	.zero	1
.LC67:
	ASCII(.string	"ERROR: frm %d, lost one field flg = %d, last_struct = %d\n" )
	.zero	6
.LC69:
	ASCII(.string	"Fatal Error: frm%d, get image buffer failed\n" )
	.zero	3
.LC71:
	ASCII(.string	"dec_pts: %lld Usertag: %lld\n" )
	.zero	3
.LC73:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC75:
	ASCII(.string	"++++++++++ ref %d\n" )
	.zero	5
.LC77:
	ASCII(.string	"line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\n" )
.LC79:
	ASCII(.string	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\n" )
	.zero	3
.LC81:
	ASCII(.string	"dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\n" )
	.zero	6
.LC87:
	ASCII(.string	"\nmpeg2 copy last 3 bytes of the first packet!\n\n" )
.LC91:
	ASCII(.string	"pMp2CodecInfo->pUsrDatArray[%d] is null\n" )
	.zero	7
.LC103:
	ASCII(.string	"ERROR: unsupported profile %d\n" )
	.zero	1
.LC105:
	ASCII(.string	"ERROR: unsupported level %d\n" )
	.zero	3
.LC112:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC114:
	ASCII(.string	"Decoding quits at frm %d\n" )
	.zero	6
.LC117:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
.LC119:
	ASCII(.string	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\n" )
.LC121:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC124:
	ASCII(.string	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\n" )
	.zero	5
.LC126:
	ASCII(.string	"DEBUG: DEC over\n" )
	.zero	7
.LC129:
	ASCII(.string	"insert buf %d ref %d\n" )
	.zero	2
.LC131:
	ASCII(.string	"ERROR,pBwdImg == NULL || pToQueImg == NULL\n" )
	.zero	4
.LC133:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC135:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC137:
	ASCII(.string	"%-40s%20d\n" )
	.zero	5
.LC139:
	ASCII(.string	"slice_vertical_position" )
.LC141:
	ASCII(.string	"quantiser_scale_code" )
	.zero	3
.LC143:
	ASCII(.string	"extra_bit_slice" )
.LC145:
	ASCII(.string	"intra_slice_flag" )
	.zero	7
.LC147:
	ASCII(.string	"intra_slice" )
	.zero	4
.LC149:
	ASCII(.string	"reserved_bits" )
	.zero	2
.LC151:
	ASCII(.string	"extra_infrmation_slice" )
	.zero	1
.LC153:
	ASCII(.string	"Slice num = %d >= %d\n" )
	.zero	2
.LC155:
	ASCII(.string	"seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] = %d\n" )
	.zero	7
.LC158:
	ASCII(.string	"macroblock_address_increment" )
	.zero	3
.LC162:
	ASCII(.string	"macroblock_escape ERROR\n" )
	.zero	7
.LC164:
	ASCII(.string	"macroblock_escape" )
	.zero	6
.LC166:
	ASCII(.string	"SlcStartMbNum = %d > PicEndMum = %d\n" )
	.zero	3
.LC168:
	ASCII(.string	"FirstMbInSliceFlag = %d\n" )
	.zero	7
.LC170:
	ASCII(.string	"MP2_GetFirstMbInSlice Failed!\n" )
	.zero	1
.LC173:
	ASCII(.string	"MP2_WriteSliceInfo Failed!\n" )
	.zero	4
.LC176:
	ASCII(.string	"found sh %#x\n" )
	.zero	2
.LC179:
	ASCII(.string	"SEQUENCE_HEADER_CODE Bitstream is not enough!\n" )
	.zero	1
.LC181:
	ASCII(.string	"found gh %#x\n" )
	.zero	2
.LC183:
	ASCII(.string	"GROUP_START_CODE Bitstream is not enough!\n" )
	.zero	5
.LC185:
	ASCII(.string	"found ph %#x\n" )
	.zero	2
.LC187:
	ASCII(.string	"PICTURE_START_CODE Bitstream is not enough!\n" )
	.zero	3
.LC189:
	ASCII(.string	"found ud %#x\n" )
	.zero	2
.LC191:
	ASCII(.string	"cann't get ud pointer\n" )
	.zero	1
.LC193:
	ASCII(.string	"found ext %#x\n" )
	.zero	1
.LC195:
	ASCII(.string	"MP2_DecSlice is wrong!\n" )
.LC198:
	ASCII(.string	"line %d, MP2_ReceivePacket receive packet failed!\n" )
	.zero	5
.LC201:
	ASCII(.string	"MP2 Decode Decide is wrong!\n" )
	.zero	3
.LC203:
	ASCII(.string	"MP2 get picture info is wrong!\n" )
.LC205:
	ASCII(.string	"MP2 dec new pic failed!\n" )
	.bss
	.align	3
.LANCHOR2 = . + 0
	.type	g_tmpusd, %object
	.size	g_tmpusd, 1024
g_tmpusd:
	.zero	1024
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
