#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"syntax.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	InitVoQueue
	.type	InitVoQueue, %function
InitVoQueue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC1
	mov	w0, 12
	bl	dprint_vfmw
	strh	wzr, [x19, 2]
	mov	w1, 64
	strh	w1, [x19]
	add	x1, x19, 512
	strh	wzr, [x19, 4]
	strh	wzr, [x19, 6]
	mov	w0, -1
	strh	wzr, [x19, 8]
	stp	w0, w0, [x1, 16]
	stp	w0, w0, [x1, 24]
	str	w0, [x19, 544]
	str	w0, [x19, 548]
	mov	w0, 1
	str	wzr, [x19, 572]
	str	wzr, [x19, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	InitVoQueue, .-InitVoQueue
	.align	3
.LC1:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC3
	mov	w0, 1
	ldrh	w4, [x20, 8]
	ldrh	w3, [x20, 4]
	ldrh	w2, [x20, 6]
	bl	dprint_vfmw
	ldr	x22, .LC5
	ldrh	w0, [x20, 4]
	ldrh	w1, [x20, 8]
	and	w19, w0, 63
	cmp	w19, w1
	beq	.L5
	ldr	x21, .LC7
	b	.L6
	.p2align 3
.L4:
	uxtw	x2, w19
	mov	x1, x21
	add	x2, x2, 2
	mov	w0, 1
	ldr	x2, [x20, x2, lsl 3]
	ldr	w2, [x2, 148]
	bl	dprint_vfmw
	add	w0, w19, 1
	ldrh	w1, [x20, 8]
	and	w19, w0, 63
	cmp	w19, w1
	beq	.L5
.L6:
	and	w0, w0, 7
	cbnz	w0, .L4
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4
	.p2align 3
.L5:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PrintVoQueue, .-PrintVoQueue
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetVoQueue
	.type	ResetVoQueue, %function
ResetVoQueue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC8
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w2, [x19, 6]
	ldrh	w3, [x19, 4]
	ldrh	w4, [x19, 8]
	cmp	w2, w3
	beq	.L13
.L11:
	ldr	x1, .LC10
	mov	w0, 1
	bl	dprint_vfmw
.L12:
	add	x4, x19, 512
	strh	wzr, [x19, 2]
	strh	wzr, [x19, 4]
	mov	w0, 64
	strh	wzr, [x19, 6]
	mov	x3, -1
	strh	w0, [x19]
	mov	w0, -1
	strh	wzr, [x19, 8]
	ldr	w1, [x19, 600]
	ldr	x2, [x20, 32]
	stp	w0, w0, [x4, 16]
	stp	w0, w0, [x4, 24]
	add	w1, w1, 100
	str	w0, [x19, 544]
	str	w0, [x19, 548]
	mov	w0, 2
	str	x3, [x19, 584]
	str	w1, [x19, 600]
	str	wzr, [x19, 572]
	str	wzr, [x19, 580]
	str	xzr, [x19, 592]
	blr	x2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L13:
	cmp	w2, w4
	bne	.L11
	b	.L12
	.size	ResetVoQueue, .-ResetVoQueue
	.align	3
.LC8:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReturnImageToSyntax
	.type	ReturnImageToSyntax, %function
ReturnImageToSyntax:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cmp	w19, 20
	bhi	.L14
	ldr	x0, .LC11
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx17
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx17:
	.section	.rodata
	.align	0
	.align	2
.L17:
	.byte	(.L16 - .Lrtx17) / 4
	.byte	(.L18 - .Lrtx17) / 4
	.byte	(.L19 - .Lrtx17) / 4
	.byte	(.L20 - .Lrtx17) / 4
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L21 - .Lrtx17) / 4
	.byte	(.L22 - .Lrtx17) / 4
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L23 - .Lrtx17) / 4
	.byte	(.L24 - .Lrtx17) / 4
	.byte	(.L25 - .Lrtx17) / 4
	.byte	(.L25 - .Lrtx17) / 4
	.byte	(.L25 - .Lrtx17) / 4
	.byte	(.L26 - .Lrtx17) / 4
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L27 - .Lrtx17) / 4
	.byte	(.L28 - .Lrtx17) / 4
	.byte	(.L29 - .Lrtx17) / 4
	.byte	(.L30 - .Lrtx17) / 4
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L31 - .Lrtx17) / 4
	.text
	.p2align 3
.L31:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	USERDEC_RecycleImage
.L14:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L16:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	H264DEC_RecycleImage
	b	.L14
	.p2align 3
.L18:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	VC1DEC_RecycleImage
	b	.L14
	.p2align 3
.L19:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	MPEG4DEC_RecycleImage
	b	.L14
	.p2align 3
.L20:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	MPEG2DEC_RecycleImage
	b	.L14
	.p2align 3
.L21:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	DIVX3DEC_RecycleImage
	b	.L14
	.p2align 3
.L22:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	AVSDEC_RecycleImage
	b	.L14
	.p2align 3
.L23:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	REAL8DEC_RecycleImage
	b	.L14
	.p2align 3
.L24:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	REAL9DEC_RecycleImage
	b	.L14
	.p2align 3
.L25:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	VP6DEC_RecycleImage
	b	.L14
	.p2align 3
.L26:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	VP8DEC_RecycleImage
	b	.L14
	.p2align 3
.L27:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	MVC_DEC_RecycleImage
	b	.L14
	.p2align 3
.L28:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	HEVC_DECRecycleImage
	b	.L14
	.p2align 3
.L29:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	VP9DEC_RecycleImage
	b	.L14
	.p2align 3
.L30:
	ldr	w1, [x21, 148]
	mov	x0, x20
	bl	AVS2DEC_RecycleImage
	b	.L14
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.align	3
.LC11:
	.xword	.L17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProduceTimeStamp
	.type	ProduceTimeStamp, %function
ProduceTimeStamp:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	w19, w2
	bl	_mcount
	cmp	w19, 20
	ldr	x0, [x20, 584]
	beq	.L33
	ldr	x2, [x21, 584]
	sub	w19, w19, #8
	sub	x1, x0, x2
	cmp	x1, 5
	ccmn	x2, #1, 4, ls
	beq	.L43
	cmp	w19, 1
	mov	x0, -1
	bls	.L35
.L33:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L43:
	cmp	w19, 1
	bhi	.L33
	ldrb	w1, [x20, 64]
	and	w1, w1, 3
	cmp	w1, 2
	bne	.L33
.L35:
	mov	x0, -1
	str	x0, [x20, 576]
	b	.L33
	.size	ProduceTimeStamp, .-ProduceTimeStamp
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertImgToVoQueue_PtsProcess
	.type	InsertImgToVoQueue_PtsProcess, %function
InsertImgToVoQueue_PtsProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x3
	mov	w20, w1
	mov	x22, x2
	bl	_mcount
	ldr	x1, .LC12
	ldrb	w0, [x19, 66]
	ldr	x3, [x19, 584]
	ldr	x1, [x1, w21, sxtw 3]
	ldr	w1, [x1, 128]
	str	x3, [x19, 576]
	cmp	w1, 1
	cset	w1, eq
	cmp	w20, 20
	bfi	w0, w1, 2, 1
	strb	w0, [x19, 66]
	beq	.L48
	ldr	x0, [x22, 584]
	sub	w20, w20, #8
	sub	x1, x3, x0
	cmp	x1, 5
	ccmn	x0, #1, 4, ls
	beq	.L54
	cmp	w20, 1
	bls	.L47
	mov	x2, x3
	mov	x3, -1
.L45:
	ldr	x4, [x19, 592]
	mov	w0, 29
	ldr	x1, .LC14
	str	x3, [x19, 584]
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L54:
	cmp	w20, 1
	mov	x2, x3
	bhi	.L45
	ldrb	w0, [x19, 64]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L45
.L47:
	mov	x2, -1
	str	x2, [x19, 576]
	mov	x3, x2
	b	.L45
	.p2align 3
.L48:
	mov	x2, x3
	b	.L45
	.size	InsertImgToVoQueue_PtsProcess, .-InsertImgToVoQueue_PtsProcess
	.align	3
.LC12:
	.xword	s_pstVfmwChan
	.align	3
.LC14:
	.xword	.LC13
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertImgToVoQueue_FillImageInfo
	.type	InsertImgToVoQueue_FillImageInfo, %function
InsertImgToVoQueue_FillImageInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x3
	mov	w23, w0
	mov	x0, x30
	mov	w20, w1
	mov	x24, x2
	bl	_mcount
	ldr	w0, [x19, 76]
	cbz	w0, .L56
	ldr	w0, [x19, 80]
	cbnz	w0, .L81
.L56:
	ldp	w1, w0, [x19, 68]
	stp	w1, w0, [x19, 76]
	lsr	w2, w1, 1
	lsr	w0, w0, 1
	str	w2, [x19, 84]
	str	w0, [x19, 88]
.L57:
	add	x20, x24, 528
	str	w1, [x20, 28]
	ldr	w3, [x20, 8]
	ldr	w0, [x19, 72]
	str	w0, [x20, 32]
	ldrb	w0, [x19, 64]
	ubfx	x0, x0, 5, 3
	str	w0, [x20, 36]
	ldr	w0, [x19, 64]
	str	w0, [x20, 40]
	ldr	w0, [x19, 148]
	add	w0, w0, 2
	str	w0, [x20, 24]
	ldrb	w27, [x19, 65]
	ldr	w0, [x19, 64]
	ldr	w2, [x19, 156]
	ubfx	x27, x27, 0, 2
	ldp	w21, w1, [x19, 80]
	ldrh	w22, [x19, 88]
	cmp	w2, w3
	ubfx	x0, x0, 14, 3
	ldrh	w3, [x19, 76]
	uxtb	w25, w27
	orr	w22, w22, w1, lsl 16
	uxtb	w26, w0
	orr	w21, w3, w21, lsl 16
	beq	.L58
	str	w2, [x20, 48]
.L58:
	ldr	w1, [x20, 44]
	add	w2, w1, 1
	str	w2, [x20, 44]
	str	w1, [x19, 160]
	ldr	w1, [x24, 528]
	cmp	w26, w1
	beq	.L59
	ldr	x2, .LC15
	ldr	x4, [x2]
	cbz	x4, .L60
	strb	w1, [x29, 104]
	mov	w3, 2
	strb	w0, [x29, 105]
	add	x2, x29, 104
	mov	w1, 7
	mov	w0, w23
	blr	x4
.L60:
	str	w26, [x24, 528]
.L59:
	ldr	w0, [x20, 4]
	cmp	w25, w0
	beq	.L61
	ldr	x0, .LC15
	ldr	x4, [x0]
	cbz	x4, .L62
	add	x2, x29, 112
	mov	w3, 1
	mov	w1, 4
	mov	w0, w23
	strb	w27, [x2, -8]!
	blr	x4
.L62:
	str	w25, [x20, 4]
.L61:
	ldr	w0, [x20, 16]
	cmp	w21, w0
	beq	.L82
.L63:
	ldr	x0, .LC15
	stp	w21, w22, [x20, 16]
	ldr	x4, [x0]
	cbz	x4, .L64
	ldp	w3, w2, [x19, 76]
	ldp	w1, w0, [x19, 84]
	strh	w3, [x29, 104]
	mov	w3, 8
	strh	w2, [x29, 106]
	add	x2, x29, 104
	strh	w1, [x29, 108]
	mov	w1, 1
	strh	w0, [x29, 110]
	mov	w0, w23
	blr	x4
.L64:
	ldp	w1, w0, [x19, 36]
	ldp	w3, w2, [x19, 112]
	stp	w1, w0, [x19, 20]
	add	w1, w3, w1
	add	w0, w2, w0
	stp	w1, w0, [x19, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L81:
	sub	w0, w20, #15
	cmp	w0, 1
	ccmp	w20, wzr, 4, hi
	bne	.L56
	ldr	w1, [x19, 68]
	b	.L57
	.p2align 3
.L82:
	ldr	w0, [x20, 20]
	cmp	w22, w0
	bne	.L63
	b	.L64
	.size	InsertImgToVoQueue_FillImageInfo, .-InsertImgToVoQueue_FillImageInfo
	.align	3
.LC15:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertImgToVoQueue_ReportIMG
	.type	InsertImgToVoQueue_ReportIMG, %function
InsertImgToVoQueue_ReportIMG:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC16
	ldr	x4, [x0]
	cbz	x4, .L83
	mov	w3, 632
	mov	x2, x20
	mov	w1, 5
	mov	w0, w19
	blr	x4
.L83:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	InsertImgToVoQueue_ReportIMG, .-InsertImgToVoQueue_ReportIMG
	.align	3
.LC16:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w23, w0
	mov	x26, x4
	mov	x0, x30
	mov	w22, w1
	mov	x24, x2
	mov	x27, x3
	bl	_mcount
	cbz	x26, .L119
	ldr	x1, .LC20
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x20, .LC21
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w19, [x27, 4]
	ldrh	w3, [x27, 8]
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L95
	ldr	x25, .LC23
	mov	w21, 1000
	b	.L117
	.p2align 3
.L94:
	add	w19, w19, 1
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L95
.L117:
	sxtw	x0, w19
	ldr	w1, [x26, 148]
	add	x0, x0, 2
	ldr	x0, [x27, x0, lsl 3]
	ldr	w2, [x0, 148]
	cmp	w2, w1
	bne	.L94
	mov	x1, x25
	mov	w0, 0
	add	w19, w19, 1
	bl	dprint_vfmw
	str	w21, [x26, 152]
	and	w19, w19, 63
	ldrh	w3, [x27, 8]
	cmp	w19, w3
	bne	.L117
	.p2align 2
.L95:
	ldr	w2, [x26, 152]
	cmp	w2, 100
	bhi	.L120
	ldp	w3, w4, [x26, 68]
	cmp	w3, 31
	bhi	.L121
.L97:
	ldr	x1, .LC25
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x26, 152]
	cmp	w0, 1000
	beq	.L100
	mov	x2, x26
	mov	x1, x24
	mov	w0, w22
	bl	ReturnImageToSyntax
.L100:
	ldr	x1, [x20, 32]
	mov	w0, 2
	blr	x1
	mov	w0, 1
.L90:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L121:
	cmp	w4, 31
	bls	.L97
	add	x1, x26, 416
	mov	w0, w23
	str	w22, [x26, 216]
	sxtw	x19, w23
	bl	VCTRL_GetHDRConfigInfo
	mov	x3, x26
	mov	x2, x27
	mov	w1, w22
	mov	w0, w23
	bl	InsertImgToVoQueue_PtsProcess
	mov	x3, x26
	mov	x2, x27
	mov	w1, w22
	mov	w0, w23
	bl	InsertImgToVoQueue_FillImageInfo
	ldr	w5, [x26, 148]
	mov	w0, 12
	ldrh	w4, [x27, 8]
	ldrh	w3, [x27, 6]
	ldrh	w2, [x27, 4]
	ldr	x1, .LC27
	bl	dprint_vfmw
	ldr	x21, .LC29
	ldrh	w0, [x27, 8]
	lsl	x1, x19, 4
	ldr	x4, .LC28
	add	x1, x1, x19, lsl 2
	add	w2, w0, 1
	add	x0, x0, 2
	and	w2, w2, 63
	add	x3, x21, x1, lsl 4
	sub	x3, x3, x1
	mov	w1, 5
	str	x26, [x27, x0, lsl 3]
	mov	w0, w23
	strh	w2, [x27, 8]
	ldr	x2, [x4, w23, sxtw 3]
	add	x2, x2, 507904
	ldr	w4, [x2, 1392]
	add	w4, w4, 1
	str	w4, [x2, 1392]
	str	wzr, [x26, 264]
	ldr	w2, [x26, 52]
	str	w2, [x3, 20]
	ldr	w2, [x26, 160]
	bl	VDEC_Lowdelay_Event_Time
	ldr	x3, .LC30
	mov	w0, 2
	ldr	w1, [x26, 160]
	ldr	x2, [x20, 32]
	add	w1, w1, 1
	str	w1, [x3, w23, sxtw 2]
	blr	x2
	ldr	x0, .LC31
	ldr	x4, [x0]
	cbz	x4, .L101
	mov	w3, 632
	mov	x2, x26
	mov	w1, 5
	mov	w0, w23
	blr	x4
.L101:
	mov	w0, 8
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L122
.L103:
	lsl	x0, x19, 4
	ldr	x1, [x20]
	add	x0, x0, x19, lsl 2
	lsl	x20, x0, 4
	sub	x20, x20, x0
	add	x22, x21, x20
	ldr	w0, [x22, 4]
	add	w0, w0, 1
	str	w0, [x22, 4]
	blr	x1
	mov	w2, w0
	ldr	w1, [x21, x20]
	mov	w0, 1
	sub	w1, w2, w1
	cmp	w1, 299
	bls	.L90
	ldr	w0, [x22, 4]
	cbz	w0, .L105
	mov	w3, 10000
	mul	w0, w0, w3
	udiv	w1, w0, w1
	str	w1, [x22, 8]
.L105:
	lsl	x1, x19, 4
	mov	w0, 1
	add	x19, x1, x19, lsl 2
	lsl	x1, x19, 4
	sub	x19, x1, x19
	add	x1, x21, x19
	str	w2, [x21, x19]
	str	wzr, [x1, 4]
	b	.L90
	.p2align 3
.L120:
	ldp	w3, w4, [x26, 68]
	b	.L97
.L122:
	ldr	x0, [x20]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC32
	ldr	x1, .LC33
	ldr	w0, [x3, w23, sxtw 2]
	ldr	w1, [x1]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L103
	lsl	w2, w23, 24
	ldr	x0, .LC34
	add	w2, w2, 524288
	mov	w1, 517
	str	w4, [x3, w23, sxtw 2]
	bl	DBG_AddTrace
	b	.L103
.L119:
	ldr	x1, .LC18
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L90
	.size	InsertImgToVoQueue, .-InsertImgToVoQueue
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC21:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC28:
	.xword	s_pstVfmwChan
	.align	3
.LC29:
	.xword	g_VfmwChanStat
	.align	3
.LC30:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC31:
	.xword	g_event_report
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	g_TraceFramePeriod
	.align	3
.LC34:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetQueueImgNum
	.type	GetQueueImgNum, %function
GetQueueImgNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	ldrh	w0, [x19, 6]
	ldrh	w3, [x19, 4]
	cmp	w0, w3
	bcc	.L124
	sub	w3, w0, w3
.L125:
	ldrh	w4, [x19, 8]
	cmp	w0, w4
	bls	.L128
	add	w4, w4, 64
.L128:
	str	w3, [x21]
	sub	w0, w4, w0
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L124:
	add	w1, w0, 64
	sub	w3, w1, w3
	b	.L125
	.size	GetQueueImgNum, .-GetQueueImgNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_GetVoQue
	.type	SYNTAX_GetVoQue, %function
SYNTAX_GetVoQue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L148
.L147:
	mov	x0, 0
	b	.L130
	.p2align 3
.L148:
	ldr	x1, .LC35
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx132
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx132:
	.section	.rodata
	.align	0
	.align	2
.L132:
	.byte	(.L146 - .Lrtx132) / 4
	.byte	(.L133 - .Lrtx132) / 4
	.byte	(.L134 - .Lrtx132) / 4
	.byte	(.L135 - .Lrtx132) / 4
	.byte	(.L147 - .Lrtx132) / 4
	.byte	(.L136 - .Lrtx132) / 4
	.byte	(.L137 - .Lrtx132) / 4
	.byte	(.L147 - .Lrtx132) / 4
	.byte	(.L138 - .Lrtx132) / 4
	.byte	(.L139 - .Lrtx132) / 4
	.byte	(.L140 - .Lrtx132) / 4
	.byte	(.L140 - .Lrtx132) / 4
	.byte	(.L140 - .Lrtx132) / 4
	.byte	(.L141 - .Lrtx132) / 4
	.byte	(.L147 - .Lrtx132) / 4
	.byte	(.L142 - .Lrtx132) / 4
	.byte	(.L143 - .Lrtx132) / 4
	.byte	(.L144 - .Lrtx132) / 4
	.byte	(.L145 - .Lrtx132) / 4
	.byte	(.L147 - .Lrtx132) / 4
	.byte	(.L146 - .Lrtx132) / 4
	.text
	.p2align 3
.L146:
	add	x0, x19, 16
.L130:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L133:
	add	x19, x19, 53248
	add	x0, x19, 248
	b	.L130
	.p2align 3
.L138:
	add	x19, x19, 53248
	add	x0, x19, 1216
	b	.L130
	.p2align 3
.L139:
	add	x19, x19, 53248
	add	x0, x19, 1192
	b	.L130
	.p2align 3
.L134:
	add	x19, x19, 20480
	add	x0, x19, 2248
	b	.L130
	.p2align 3
.L135:
	add	x19, x19, 86016
	add	x0, x19, 2272
	b	.L130
	.p2align 3
.L136:
	add	x19, x19, 40960
	add	x0, x19, 1160
	b	.L130
	.p2align 3
.L137:
	add	x19, x19, 12288
	add	x0, x19, 3984
	b	.L130
	.p2align 3
.L142:
	add	x0, x19, 920
	b	.L130
	.p2align 3
.L143:
	add	x19, x19, 4096
	add	x0, x19, 2840
	b	.L130
	.p2align 3
.L144:
	add	x19, x19, 274432
	add	x0, x19, 4048
	b	.L130
	.p2align 3
.L145:
	add	x19, x19, 16384
	add	x0, x19, 1784
	b	.L130
	.p2align 3
.L140:
	add	x19, x19, 12288
	add	x0, x19, 480
	b	.L130
	.p2align 3
.L141:
	add	x19, x19, 8192
	add	x0, x19, 48
	b	.L130
	.size	SYNTAX_GetVoQue, .-SYNTAX_GetVoQue
	.align	3
.LC35:
	.xword	.L132
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReceiveImage
	.type	SYNTAX_ReceiveImage, %function
SYNTAX_ReceiveImage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L153
	mov	x0, x19
	bl	SYNTAX_GetVoQue
	mov	x19, x0
	cbz	x0, .L155
	ldr	x22, .LC39
	mov	w0, 2
	mov	w21, -3
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w0, [x19, 6]
	ldrh	w1, [x19, 8]
	cmp	w1, w0
	beq	.L152
	add	x1, x0, 2
	ldr	x3, [x22, 104]
	mov	x2, 632
	mov	x0, x20
	ldr	x23, [x20, 496]
	mov	w21, 1
	ldr	x1, [x19, x1, lsl 3]
	blr	x3
	str	x23, [x20, 496]
	ldr	x1, .LC41
	mov	w0, 12
	ldr	w5, [x20, 148]
	ldrh	w4, [x19, 8]
	ldrh	w3, [x19, 6]
	ldrh	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	w1, [x20, 148]
	ldr	w0, [x19, 600]
	add	w0, w1, w0
	str	w0, [x20, 148]
	ldrh	w0, [x19, 6]
	add	w0, w0, w21
	and	w0, w0, 63
	strh	w0, [x19, 6]
.L152:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w21
.L150:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L153:
	mov	w0, -2
	b	.L150
.L155:
	ldr	x2, .LC36
	mov	w0, 1
	ldr	x1, .LC38
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -2
	b	.L150
	.size	SYNTAX_ReceiveImage, .-SYNTAX_ReceiveImage
	.align	3
.LC36:
	.xword	.LANCHOR1
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC39:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC41:
	.xword	.LC40
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReleaseImage_RecycleImage_CheckRet
	.type	SYNTAX_ReleaseImage_RecycleImage_CheckRet, %function
SYNTAX_ReleaseImage_RecycleImage_CheckRet:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	w0, [x20]
	cmp	w0, 17
	bls	.L170
.L157:
	cmn	w19, #2
	beq	.L168
	cmp	w19, 1
	mov	w0, -20
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L170:
	ldr	x1, .LC42
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx159
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx159:
	.section	.rodata
	.align	0
	.align	2
.L159:
	.byte	(.L162 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L157 - .Lrtx159) / 4
	.byte	(.L162 - .Lrtx159) / 4
	.byte	(.L162 - .Lrtx159) / 4
	.byte	(.L162 - .Lrtx159) / 4
	.text
	.p2align 3
.L162:
	mov	w0, -20
	cmp	w19, wzr
	csinc	w0, w0, wzr, ne
.L163:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L168:
	mov	w0, w19
	b	.L163
	.size	SYNTAX_ReleaseImage_RecycleImage_CheckRet, .-SYNTAX_ReleaseImage_RecycleImage_CheckRet
	.align	3
.LC42:
	.xword	.L159
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReleaseImage_RecycleImage
	.type	SYNTAX_ReleaseImage_RecycleImage, %function
SYNTAX_ReleaseImage_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L190
.L189:
	mov	w1, -2
	b	.L172
	.p2align 3
.L190:
	ldr	x1, .LC43
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx174
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx174:
	.section	.rodata
	.align	0
	.align	2
.L174:
	.byte	(.L173 - .Lrtx174) / 4
	.byte	(.L175 - .Lrtx174) / 4
	.byte	(.L176 - .Lrtx174) / 4
	.byte	(.L177 - .Lrtx174) / 4
	.byte	(.L189 - .Lrtx174) / 4
	.byte	(.L178 - .Lrtx174) / 4
	.byte	(.L179 - .Lrtx174) / 4
	.byte	(.L189 - .Lrtx174) / 4
	.byte	(.L180 - .Lrtx174) / 4
	.byte	(.L181 - .Lrtx174) / 4
	.byte	(.L182 - .Lrtx174) / 4
	.byte	(.L182 - .Lrtx174) / 4
	.byte	(.L182 - .Lrtx174) / 4
	.byte	(.L183 - .Lrtx174) / 4
	.byte	(.L189 - .Lrtx174) / 4
	.byte	(.L184 - .Lrtx174) / 4
	.byte	(.L185 - .Lrtx174) / 4
	.byte	(.L186 - .Lrtx174) / 4
	.byte	(.L187 - .Lrtx174) / 4
	.byte	(.L189 - .Lrtx174) / 4
	.byte	(.L188 - .Lrtx174) / 4
	.text
	.p2align 3
.L173:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	H264DEC_RecycleImage
	mov	w1, w0
.L172:
	mov	x0, x19
	bl	SYNTAX_ReleaseImage_RecycleImage_CheckRet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L175:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VC1DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L176:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MPEG4DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L177:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MPEG2DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L178:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	DIVX3DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L179:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	AVSDEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L180:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	REAL8DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L181:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	REAL9DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L182:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP6DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L183:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP8DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L184:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MVC_DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L185:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	HEVC_DECRecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L186:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP9DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L187:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	AVS2DEC_RecycleImage
	mov	w1, w0
	b	.L172
	.p2align 3
.L188:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	USERDEC_RecycleImage
	mov	w1, w0
	b	.L172
	.size	SYNTAX_ReleaseImage_RecycleImage, .-SYNTAX_ReleaseImage_RecycleImage
	.align	3
.LC43:
	.xword	.L174
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReleaseImage
	.type	SYNTAX_ReleaseImage, %function
SYNTAX_ReleaseImage:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	bl	_mcount
	cmp	x24, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L210
	mov	x0, x21
	bl	SYNTAX_GetVoQue
	mov	x25, x0
	cbz	x0, .L211
	ldr	x22, .LC48
	mov	w0, 2
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w20, [x25, 4]
	ldrh	w1, [x25, 6]
	and	w20, w20, 63
	ldr	w26, [x24, 148]
	ldr	w0, [x25, 600]
	cmp	w20, w1
	sub	w26, w26, w0
	beq	.L202
	ldr	x23, .LC52
	b	.L208
	.p2align 3
.L199:
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	beq	.L202
.L208:
	sxtw	x19, w20
	add	x0, x19, 2
	ldr	x0, [x25, x0, lsl 3]
	cbz	x0, .L197
	ldr	w0, [x0, 148]
	cmp	w26, w0
	bne	.L199
	mov	w5, 1
.L198:
	ldrh	w4, [x25, 4]
	b	.L201
	.p2align 3
.L206:
	mov	w20, w1
.L201:
	cmp	w20, wzr
	sub	w0, w20, #1
	mov	w1, 63
	add	x2, x19, 2
	csel	w1, w0, w1, ne
	cmp	w20, w4
	sxtw	x0, w1
	add	x3, x0, 2
	mov	x19, x0
	ldr	x0, [x25, x3, lsl 3]
	str	x0, [x25, x2, lsl 3]
	bne	.L206
	ldr	w0, [x24, 148]
	cmp	w5, 1
	ldr	w1, [x25, 600]
	sub	w0, w0, w1
	str	w0, [x24, 148]
	ldrh	w2, [x25, 4]
	add	w2, w2, 1
	and	w2, w2, 63
	strh	w2, [x25, 4]
	beq	.L212
	ldrh	w1, [x25, 6]
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	bne	.L208
.L202:
	ldr	x1, .LC50
	mov	w2, w26
	mov	w0, 1
	mov	w19, -2
	bl	dprint_vfmw
.L196:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w19
.L193:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L197:
	mov	w2, w20
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	mov	w5, 2
	b	.L198
.L212:
	ldrh	w4, [x25, 8]
	mov	w0, 12
	ldrh	w3, [x25, 6]
	ldr	x1, .LC54
	ldr	w5, [x24, 148]
	bl	dprint_vfmw
	mov	x1, x24
	mov	x0, x21
	bl	SYNTAX_ReleaseImage_RecycleImage
	mov	w19, w0
	b	.L196
.L210:
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L193
.L211:
	ldr	x2, .LC46
	mov	w0, 1
	ldr	x1, .LC47
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L193
	.size	SYNTAX_ReleaseImage, .-SYNTAX_ReleaseImage
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC46:
	.xword	.LANCHOR1
	.align	3
.LC47:
	.xword	.LC37
	.align	3
.LC48:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC54:
	.xword	.LC53
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReturnImage
	.type	SYNTAX_ReturnImage, %function
SYNTAX_ReturnImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L233
.L232:
	mov	w0, -2
	b	.L214
	.p2align 3
.L233:
	ldr	x1, .LC55
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx216
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx216:
	.section	.rodata
	.align	0
	.align	2
.L216:
	.byte	(.L230 - .Lrtx216) / 4
	.byte	(.L217 - .Lrtx216) / 4
	.byte	(.L218 - .Lrtx216) / 4
	.byte	(.L219 - .Lrtx216) / 4
	.byte	(.L232 - .Lrtx216) / 4
	.byte	(.L220 - .Lrtx216) / 4
	.byte	(.L221 - .Lrtx216) / 4
	.byte	(.L232 - .Lrtx216) / 4
	.byte	(.L222 - .Lrtx216) / 4
	.byte	(.L223 - .Lrtx216) / 4
	.byte	(.L224 - .Lrtx216) / 4
	.byte	(.L224 - .Lrtx216) / 4
	.byte	(.L224 - .Lrtx216) / 4
	.byte	(.L225 - .Lrtx216) / 4
	.byte	(.L232 - .Lrtx216) / 4
	.byte	(.L226 - .Lrtx216) / 4
	.byte	(.L227 - .Lrtx216) / 4
	.byte	(.L228 - .Lrtx216) / 4
	.byte	(.L229 - .Lrtx216) / 4
	.byte	(.L232 - .Lrtx216) / 4
	.byte	(.L230 - .Lrtx216) / 4
	.text
	.p2align 3
.L230:
	add	x19, x19, 16
	.p2align 2
.L231:
	ldr	x20, .LC56
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w1, [x19, 6]
	mov	w0, 2
	sub	w1, w1, #1
	and	w1, w1, 63
	strh	w1, [x19, 6]
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, 1
.L214:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L217:
	add	x19, x19, 53248
	add	x19, x19, 248
	b	.L231
	.p2align 3
.L222:
	add	x19, x19, 53248
	add	x19, x19, 1216
	b	.L231
	.p2align 3
.L223:
	add	x19, x19, 53248
	add	x19, x19, 1192
	b	.L231
	.p2align 3
.L218:
	add	x19, x19, 20480
	add	x19, x19, 2248
	b	.L231
	.p2align 3
.L219:
	add	x19, x19, 86016
	add	x19, x19, 2272
	b	.L231
	.p2align 3
.L220:
	add	x19, x19, 40960
	add	x19, x19, 1160
	b	.L231
	.p2align 3
.L221:
	add	x19, x19, 12288
	add	x19, x19, 3984
	b	.L231
	.p2align 3
.L226:
	add	x19, x19, 920
	b	.L231
	.p2align 3
.L227:
	add	x19, x19, 4096
	add	x19, x19, 2840
	b	.L231
	.p2align 3
.L228:
	add	x19, x19, 274432
	add	x19, x19, 4048
	b	.L231
	.p2align 3
.L229:
	add	x19, x19, 16384
	add	x19, x19, 1784
	b	.L231
	.p2align 3
.L224:
	add	x19, x19, 12288
	add	x19, x19, 480
	b	.L231
	.p2align 3
.L225:
	add	x19, x19, 8192
	add	x19, x19, 48
	b	.L231
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	3
.LC55:
	.xword	.L216
	.align	3
.LC56:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_H264
	.type	DecodeStream_H264, %function
DecodeStream_H264:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x2, [x19, 8]
	add	x1, x29, 40
	ldr	x3, [x19, 40]
	mov	x0, x20
	ldrb	w5, [x19, 18]
	ldp	w7, w6, [x19, 24]
	ldr	w4, [x19, 32]
	str	x2, [x29, 48]
	str	x3, [x29, 72]
	ldrsb	w2, [x19, 17]
	ldrb	w3, [x19, 20]
	strb	w5, [x29, 40]
	stp	w7, w6, [x29, 56]
	str	w4, [x29, 64]
	strb	w3, [x29, 41]
	str	w2, [x29, 68]
	bl	H264DEC_DecodePacket
	cmn	w0, #2
	add	x0, x20, 65536
	beq	.L238
	strb	wzr, [x19, 1]
	ldr	x1, .LC57
	ldrsw	x2, [x0, 1644]
	ldr	x1, [x1, x2, lsl 3]
	strb	wzr, [x1, 1560]
	ldr	x1, [x20, 616]
	cbz	x1, .L239
.L234:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L238:
	mov	w1, 1
	strb	w1, [x19, 1]
	ldr	x2, .LC57
	ldrsw	x3, [x0, 1644]
	ldr	x2, [x2, x3, lsl 3]
	strb	w1, [x2, 1560]
	ldr	x1, [x20, 616]
	cbnz	x1, .L234
.L239:
	add	x20, x20, 12288
	ldrb	w1, [x20, 2640]
	cmp	w1, 1
	bne	.L234
	ldr	w0, [x0, 1644]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2640]
	b	.L234
	.size	DecodeStream_H264, .-DecodeStream_H264
	.align	3
.LC57:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_HEVC
	.type	DecodeStream_HEVC, %function
DecodeStream_HEVC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldp	w6, w5, [x19, 24]
	ldrb	w4, [x19, 18]
	add	x1, x29, 32
	ldrsb	w2, [x19, 17]
	mov	x0, x20
	ldr	w3, [x19, 32]
	ldr	x7, [x19, 8]
	strb	w4, [x29, 32]
	str	x7, [x29, 40]
	stp	w6, w2, [x29, 48]
	stp	w5, w3, [x29, 56]
	bl	HEVCDEC_DecodePacket
	cmn	w0, #2
	beq	.L241
	ldrb	w0, [x20, 9]
	cbz	w0, .L242
.L241:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x1, .LC58
	ldrsw	x2, [x20, 276]
	ldr	x1, [x1, x2, lsl 3]
	strb	w0, [x1, 1560]
	ldr	x0, [x20, 3048]
	cbz	x0, .L248
.L240:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L242:
	strb	wzr, [x19, 1]
	ldr	x0, .LC58
	ldrsw	x1, [x20, 276]
	ldr	x0, [x0, x1, lsl 3]
	strb	wzr, [x0, 1560]
	ldr	x0, [x20, 3048]
	cbnz	x0, .L240
.L248:
	ldrb	w0, [x20, 11]
	cmp	w0, 1
	bne	.L240
	ldr	w0, [x20, 276]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 11]
	b	.L240
	.size	DecodeStream_HEVC, .-DecodeStream_HEVC
	.align	3
.LC58:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP9
	.type	DecodeStream_VP9, %function
DecodeStream_VP9:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L263
	ldr	x23, .LC59
	add	x22, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x22
	add	x21, x20, 311296
	ldr	x3, [x23, 104]
	blr	x3
	ldr	x3, [x23, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x22
	mov	x0, x20
	bl	VP9DEC_DecodePacket
	ldr	w0, [x21, 3172]
	cbnz	w0, .L264
	ldr	w0, [x21, 3168]
	cbz	w0, .L265
.L253:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x0, [x20, 8]
	cbz	x0, .L266
.L249:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L264:
	ldr	w0, [x21, 3208]
	ldr	w1, [x21, 3212]
	cmp	w1, w0
	bne	.L253
	ldr	w0, [x21, 3168]
	cbnz	w0, .L253
.L265:
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 8]
	cbnz	x0, .L249
.L266:
	add	x20, x20, 262144
	ldrb	w0, [x20, 1044]
	cbnz	w0, .L249
	ldr	x3, [x23, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x21, 3272]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC60
	ldr	x4, [x0]
	cbz	x4, .L249
	ldr	w0, [x21, 3272]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L249
	.p2align 3
.L263:
	add	x20, x20, 311296
	ldr	w0, [x20, 3272]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 3272]
	bl	SM_ReleaseStreamSeg
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DecodeStream_VP9, .-DecodeStream_VP9
	.align	3
.LC59:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC60:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MVC
	.type	DecodeStream_MVC, %function
DecodeStream_MVC:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w3, [x19, 18]
	add	x1, x29, 40
	ldp	w5, w4, [x19, 24]
	ldr	w2, [x19, 32]
	mov	x0, x20
	ldr	x6, [x19, 8]
	ldr	x7, [x19, 40]
	strb	w3, [x29, 40]
	str	x6, [x29, 48]
	stp	w5, w4, [x29, 56]
	str	w2, [x29, 64]
	str	x7, [x29, 72]
	bl	MVC_DEC_DecodePacket
	cmn	w0, #2
	beq	.L271
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 232]
	cbz	x0, .L272
.L267:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L271:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x0, [x20, 232]
	cbnz	x0, .L267
.L272:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L267
	ldr	w0, [x20, 120]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 1]
	b	.L267
	.size	DecodeStream_MVC, .-DecodeStream_MVC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1_Smp
	.type	DecodeStream_VC1_Smp, %function
DecodeStream_VC1_Smp:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L286
	ldr	x21, .LC61
	add	x22, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x22
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	ldr	w0, [x19, 116]
	cmp	w0, 15
	bls	.L287
	add	x2, x20, 16384
	ldr	x0, [x19, 96]
	add	x2, x2, 1528
	mov	w1, 16
	bl	Vc1SMPSeqHdr
	cbz	w0, .L288
	ldr	x1, .LC66
.L285:
	mov	w0, 0
	add	x20, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x19, 120]
	ldr	w0, [x20, 848]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC64
	ldr	x4, [x0]
	cbz	x4, .L273
	ldr	w0, [x20, 848]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L273:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L287:
	ldr	x1, .LC63
	b	.L285
	.p2align 3
.L286:
	add	x20, x20, 53248
	ldr	w0, [x20, 848]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 848]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L288:
	ldp	w0, w3, [x19, 112]
	ldr	x2, [x19, 96]
	mov	x1, x22
	add	w0, w0, 16
	sub	w3, w3, #16
	add	x2, x2, 16
	str	x2, [x19, 96]
	stp	w0, w3, [x19, 112]
	mov	x0, x20
	bl	VC1DEC_Decode
	ldr	x3, [x21, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	DecodeStream_VC1_Smp, .-DecodeStream_VC1_Smp
	.align	3
.LC61:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC64:
	.xword	g_event_report
	.align	3
.LC66:
	.xword	.LC65
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_REAL8
	.type	DecodeStream_REAL8, %function
DecodeStream_REAL8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L299
	ldr	x22, .LC67
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL8DEC_Decode
	cmn	w0, #2
	beq	.L300
	strb	wzr, [x19, 1]
.L293:
	ldr	x0, [x20, 8]
	cbz	x0, .L301
.L289:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L300:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L293
	.p2align 3
.L299:
	add	x20, x20, 53248
	ldr	w0, [x20, 1816]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L301:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC68
	ldr	x4, [x0]
	cbz	x4, .L289
	ldr	w0, [x20, 1816]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L289
	.size	DecodeStream_REAL8, .-DecodeStream_REAL8
	.align	3
.LC67:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC68:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_REAL9
	.type	DecodeStream_REAL9, %function
DecodeStream_REAL9:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L312
	ldr	x22, .LC69
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL9DEC_Decode
	cmn	w0, #2
	beq	.L313
	strb	wzr, [x19, 1]
.L306:
	ldr	x0, [x20, 8]
	cbz	x0, .L314
.L302:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L313:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L306
	.p2align 3
.L312:
	add	x20, x20, 53248
	ldr	w0, [x20, 1792]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L314:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC70
	ldr	x4, [x0]
	cbz	x4, .L302
	ldr	w0, [x20, 1792]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L302
	.size	DecodeStream_REAL9, .-DecodeStream_REAL9
	.align	3
.LC69:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC70:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_DIVX3
	.type	DecodeStream_DIVX3, %function
DecodeStream_DIVX3:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L325
	ldr	x22, .LC71
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	DIVX3DEC_Decode
	cmn	w0, #2
	beq	.L326
	strb	wzr, [x19, 1]
.L319:
	ldr	x0, [x20, 8]
	cbz	x0, .L327
.L315:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L326:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L319
	.p2align 3
.L325:
	add	x20, x20, 40960
	ldr	w0, [x20, 1760]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L327:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 40960
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC72
	ldr	x4, [x0]
	cbz	x4, .L315
	ldr	w0, [x20, 1760]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L315
	.size	DecodeStream_DIVX3, .-DecodeStream_DIVX3
	.align	3
.LC71:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC72:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP8
	.type	DecodeStream_VP8, %function
DecodeStream_VP8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L338
	ldr	x22, .LC73
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP8DEC_Decode
	cmn	w0, #2
	beq	.L339
	strb	wzr, [x19, 1]
.L332:
	ldr	x0, [x20, 8]
	cbz	x0, .L340
.L328:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L339:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L332
	.p2align 3
.L338:
	ldr	w0, [x20, 8840]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L340:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC74
	ldr	x4, [x0]
	cbz	x4, .L328
	ldr	w0, [x20, 8840]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L328
	.size	DecodeStream_VP8, .-DecodeStream_VP8
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC74:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP6x
	.type	DecodeStream_VP6x, %function
DecodeStream_VP6x:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L351
	ldr	x22, .LC75
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP6DEC_Decode
	cmn	w0, #2
	beq	.L352
	strb	wzr, [x19, 1]
.L345:
	ldr	x0, [x20, 8]
	cbz	x0, .L353
.L341:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L352:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L345
	.p2align 3
.L351:
	ldr	w0, [x20, 13368]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L353:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC76
	ldr	x4, [x0]
	cbz	x4, .L341
	ldr	w0, [x20, 13368]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L341
	.size	DecodeStream_VP6x, .-DecodeStream_VP6x
	.align	3
.LC75:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC76:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SegMan
	.type	SegMan, %function
SegMan:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L355
	ldr	x0, [x19, 8]
	cbz	x0, .L355
	ldr	x1, .LC79
	ldr	x1, [x1, w20, sxtw 3]
	ldr	w2, [x1, 1488]
	cmp	w2, 1
	beq	.L375
.L358:
	ldrb	w1, [x19, 18]
	strb	wzr, [x19, 448]
	cmp	w1, 1
	beq	.L376
	cbnz	w1, .L374
	ldr	x21, .LC80
	add	x23, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x23
	add	x22, x19, 184
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldrb	w0, [x19, 2]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x19, 2]
	cmp	w0, 1
	bls	.L374
	ldr	w1, [x19, 120]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 208]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x23
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	x1, .LC82
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC83
	ldr	x4, [x0]
	cbz	x4, .L362
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w0, w20
	blr	x4
.L362:
	strb	wzr, [x19, 2]
.L374:
	mov	w0, -1
.L373:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L375:
	ldr	w1, [x1, 1536]
	cmp	w1, 1
	bne	.L358
	ldrb	w1, [x19, 448]
	cmp	w1, 1
	bne	.L358
	mov	x2, 176
	add	x1, x19, 272
	add	x0, x19, 96
	bl	memcpy
	strb	wzr, [x19, 448]
	mov	w0, 0
	b	.L373
	.p2align 3
.L376:
	ldrb	w21, [x19, 2]
	cbz	w21, .L377
	cmp	w21, 1
	bne	.L374
	ldr	w2, [x19, 116]
	cmp	w2, 1023
	bhi	.L364
	ldr	x22, .LC80
	uxtw	x2, w2
	ldr	x1, [x19, 96]
	sub	x0, x0, x2
	ldr	x3, [x22, 104]
	blr	x3
	strb	w21, [x19, 106]
	ldp	w0, w1, [x19, 116]
	ldp	w2, w4, [x19, 24]
	ldr	x3, [x19, 8]
	sub	w2, w2, w0
	sub	x3, x3, x0, uxtw
	add	w0, w4, w0
	str	x3, [x19, 96]
	stp	w2, w0, [x19, 112]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x19, 32]
	mov	x2, 88
	ldr	x3, [x22, 96]
	mov	w1, 0
	str	w0, [x19, 120]
	add	x0, x19, 184
	blr	x3
.L365:
	mov	w0, 1
	add	x1, x19, 96
	strb	w0, [x19, 448]
	mov	x2, 176
	strb	wzr, [x19, 2]
	add	x0, x19, 272
	bl	memcpy
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L364:
	ldr	x3, .LC80
	mov	x2, 88
	add	x1, x19, 8
	add	x0, x19, 184
	ldr	x3, [x3, 104]
	blr	x3
	b	.L365
	.p2align 3
.L377:
	ldr	x20, .LC80
	mov	x2, 88
	add	x1, x19, 8
	add	x0, x19, 96
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	strb	wzr, [x19, 2]
	mov	w0, 0
	b	.L373
	.p2align 3
.L355:
	ldr	x1, .LC78
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L373
	.size	SegMan, .-SegMan
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC79:
	.xword	s_pstVfmwChan
	.align	3
.LC80:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC83:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1_Adv
	.type	DecodeStream_VC1_Adv, %function
DecodeStream_VC1_Adv:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	add	x21, x1, 53248
	bl	_mcount
	mov	x0, x19
	ldr	w22, [x21, 848]
	bl	VC1_GetPacketState
	cmp	w0, 2
	beq	.L383
.L379:
	ldr	w0, [x21, 848]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L384
	ldr	x0, [x19, 8]
	cbz	x0, .L385
.L378:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L384:
	add	x20, x20, 96
	mov	x0, x19
	mov	x1, x20
	bl	VC1DEC_Decode
	ldr	x3, .LC85
	mov	x2, 176
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 8]
	cbnz	x0, .L378
.L385:
	add	x19, x19, 12288
	ldrb	w0, [x19, 2527]
	cmp	w0, 1
	bne	.L378
	ldr	w0, [x21, 848]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19, 2527]
	b	.L378
	.p2align 3
.L383:
	ldr	x0, .LC84
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1488]
	cmp	w1, 1
	beq	.L386
.L380:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 2344
	bl	VC1DEC_Decode
	b	.L379
	.p2align 3
.L386:
	ldr	w0, [x0, 1536]
	cbnz	w0, .L379
	b	.L380
	.size	DecodeStream_VC1_Adv, .-DecodeStream_VC1_Adv
	.align	3
.LC84:
	.xword	s_pstVfmwChan
	.align	3
.LC85:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1
	.type	DecodeStream_VC1, %function
DecodeStream_VC1:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w2, [x19, 18]
	mov	w0, 22
	ldr	x1, .LC87
	bl	dprint_vfmw
	ldr	x1, .LC89
	mov	w0, 22
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC91
	mov	w0, 22
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, [x20]
	ldr	w0, [x1, 596]
	cmp	w0, 1
	bhi	.L392
	ldr	w2, [x1, 600]
	cmp	w2, 8
	bgt	.L393
	add	x2, x20, 16384
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x2, 1528]
	ldr	w0, [x1, 600]
	mov	x1, x20
	strb	w0, [x2, 1530]
	mov	x0, x19
	beq	.L394
	bl	DecodeStream_VC1_Smp
.L387:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L392:
	ldr	x1, .LC93
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L393:
	ldr	x1, .LC95
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L394:
	bl	DecodeStream_VC1_Adv
	b	.L387
	.size	DecodeStream_VC1, .-DecodeStream_VC1
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
	.align	3
.LC95:
	.xword	.LC94
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MPEG2
	.type	DecodeStream_MPEG2, %function
DecodeStream_MPEG2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	add	x20, x1, 86016
	bl	_mcount
	mov	x0, x19
	ldr	w22, [x20, 2872]
	bl	MP2_GetPacketState
	cmp	w0, 2
	beq	.L401
.L396:
	ldr	w0, [x20, 2872]
	mov	x1, x21
	bl	SegMan
	cbz	w0, .L402
	ldr	x0, [x19, 8]
	cbz	x0, .L403
.L395:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L402:
	add	x1, x21, 96
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldrb	w0, [x20, 2889]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x21, 1]
	ldr	x0, [x19, 8]
	cbnz	x0, .L395
.L403:
	ldrb	w0, [x20, 2890]
	cmp	w0, 1
	bne	.L395
	ldr	w0, [x20, 2872]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2890]
	b	.L395
	.p2align 3
.L401:
	ldr	x0, .LC96
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1488]
	cmp	w1, 1
	beq	.L404
.L397:
	add	x1, x20, 1680
	mov	x0, x19
	bl	MPEG2DEC_Decode
	b	.L396
	.p2align 3
.L404:
	ldr	w0, [x0, 1536]
	cbnz	w0, .L396
	b	.L397
	.size	DecodeStream_MPEG2, .-DecodeStream_MPEG2
	.align	3
.LC96:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MPEG4
	.type	DecodeStream_MPEG4, %function
DecodeStream_MPEG4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	add	x20, x1, 20480
	bl	_mcount
	mov	x0, x19
	ldr	w22, [x20, 2848]
	bl	MP4_GetPacketState
	cmp	w0, 3
	beq	.L410
.L406:
	ldr	w0, [x20, 2848]
	mov	x1, x21
	bl	SegMan
	cbz	w0, .L411
	ldr	x0, [x19, 1040]
	cbz	x0, .L412
.L405:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L411:
	add	x1, x21, 96
	mov	x0, x19
	bl	MPEG4DEC_Decode
	ldr	x0, [x19, 1040]
	cbnz	x0, .L405
.L412:
	ldrb	w0, [x20, 2884]
	cmp	w0, 1
	bne	.L405
	ldr	w0, [x20, 2848]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2884]
	b	.L405
	.p2align 3
.L410:
	ldr	x0, .LC97
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1488]
	cmp	w1, 1
	beq	.L413
.L407:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 3440
	bl	MPEG4DEC_Decode
	b	.L406
	.p2align 3
.L413:
	ldr	w0, [x0, 1536]
	cbnz	w0, .L406
	b	.L407
	.size	DecodeStream_MPEG4, .-DecodeStream_MPEG4
	.align	3
.LC97:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_AVS
	.type	DecodeStream_AVS, %function
DecodeStream_AVS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	x0, x19
	ldr	w21, [x19, 4]
	bl	AVS_GetPacketState
	cbnz	w0, .L415
	ldr	x0, .LC98
	ldr	x0, [x0, w21, sxtw 3]
	ldr	w1, [x0, 1488]
	cmp	w1, 1
	beq	.L419
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
.L415:
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L420
	ldr	x0, [x19, 24]
	cbz	x0, .L421
.L414:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L419:
	ldr	w0, [x0, 1536]
	cbnz	w0, .L415
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
	b	.L415
	.p2align 3
.L420:
	add	x1, x20, 96
	mov	x0, x19
	bl	AVSDEC_Decode
	ldr	x0, [x19, 24]
	cbnz	x0, .L414
.L421:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L414
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L414
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	3
.LC98:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_AVS2
	.type	DecodeStream_AVS2, %function
DecodeStream_AVS2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L427
	ldr	w0, [x19, 8]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 48]
	cbz	x0, .L428
.L422:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L427:
	add	x1, x20, 96
	mov	x0, x19
	bl	AVS2DEC_Decode
	ldr	w0, [x19, 8]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 48]
	cbnz	x0, .L422
.L428:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L422
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L422
	.size	DecodeStream_AVS2, .-DecodeStream_AVS2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	mov	w0, 6
	bl	VCTRL_RecordPosTime
	cmp	w19, 18
	bls	.L447
.L430:
	ldr	x2, .LC100
	mov	w3, 1782
	ldr	x1, .LC102
	mov	w0, 32
	add	x2, x2, 72
	bl	dprint_vfmw
.L446:
	mov	w0, 7
	bl	VCTRL_RecordPosTime
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L447:
	ldr	x0, .LC99
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx432
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx432:
	.section	.rodata
	.align	0
	.align	2
.L432:
	.byte	(.L431 - .Lrtx432) / 4
	.byte	(.L433 - .Lrtx432) / 4
	.byte	(.L434 - .Lrtx432) / 4
	.byte	(.L435 - .Lrtx432) / 4
	.byte	(.L430 - .Lrtx432) / 4
	.byte	(.L436 - .Lrtx432) / 4
	.byte	(.L437 - .Lrtx432) / 4
	.byte	(.L430 - .Lrtx432) / 4
	.byte	(.L438 - .Lrtx432) / 4
	.byte	(.L439 - .Lrtx432) / 4
	.byte	(.L440 - .Lrtx432) / 4
	.byte	(.L440 - .Lrtx432) / 4
	.byte	(.L440 - .Lrtx432) / 4
	.byte	(.L441 - .Lrtx432) / 4
	.byte	(.L430 - .Lrtx432) / 4
	.byte	(.L442 - .Lrtx432) / 4
	.byte	(.L443 - .Lrtx432) / 4
	.byte	(.L444 - .Lrtx432) / 4
	.byte	(.L445 - .Lrtx432) / 4
	.text
	.p2align 3
.L445:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_AVS2
	b	.L446
	.p2align 3
.L431:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_H264
	b	.L446
	.p2align 3
.L433:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VC1
	b	.L446
	.p2align 3
.L434:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MPEG4
	b	.L446
	.p2align 3
.L435:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MPEG2
	b	.L446
	.p2align 3
.L436:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_DIVX3
	b	.L446
	.p2align 3
.L437:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_AVS
	b	.L446
	.p2align 3
.L438:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_REAL8
	b	.L446
	.p2align 3
.L439:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_REAL9
	b	.L446
	.p2align 3
.L440:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP6x
	b	.L446
	.p2align 3
.L441:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP8
	b	.L446
	.p2align 3
.L442:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MVC
	b	.L446
	.p2align 3
.L443:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_HEVC
	b	.L446
	.p2align 3
.L444:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP9
	b	.L446
	.size	DecodeStream, .-DecodeStream
	.align	3
.LC99:
	.xword	.L432
	.align	3
.LC100:
	.xword	.LANCHOR1
	.align	3
.LC102:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleasePacket
	.type	ReleasePacket, %function
ReleasePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	sub	w0, w20, #5
	cmp	w0, 12
	bls	.L473
.L449:
	ldr	x1, .LC112
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L473:
	ldr	x1, .LC103
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx451
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx451:
	.section	.rodata
	.align	0
	.align	2
.L451:
	.byte	(.L450 - .Lrtx451) / 4
	.byte	(.L449 - .Lrtx451) / 4
	.byte	(.L449 - .Lrtx451) / 4
	.byte	(.L452 - .Lrtx451) / 4
	.byte	(.L453 - .Lrtx451) / 4
	.byte	(.L454 - .Lrtx451) / 4
	.byte	(.L454 - .Lrtx451) / 4
	.byte	(.L454 - .Lrtx451) / 4
	.byte	(.L455 - .Lrtx451) / 4
	.byte	(.L449 - .Lrtx451) / 4
	.byte	(.L449 - .Lrtx451) / 4
	.byte	(.L449 - .Lrtx451) / 4
	.byte	(.L456 - .Lrtx451) / 4
	.text
	.p2align 3
.L456:
	ldr	x20, [x19]
	add	x19, x19, 311296
	ldr	w1, [x20, 256]
	ldr	w0, [x19, 3272]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 242]
	cmp	w0, 1
	beq	.L463
	ldr	x1, .LC110
	mov	w0, 1
	bl	dprint_vfmw
.L463:
	ldr	x3, .LC104
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 232
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L450:
	ldr	x20, [x19]
	ldrb	w1, [x20, 242]
	cmp	w1, 1
	bne	.L463
	add	x19, x19, 40960
	ldr	w1, [x20, 256]
	ldr	w0, [x19, 1760]
	bl	SM_ReleaseStreamSeg
	b	.L463
	.p2align 3
.L452:
	ldr	x20, [x19]
	ldrb	w1, [x20, 242]
	cmp	w1, 1
	bne	.L463
	add	x19, x19, 53248
	ldr	w1, [x20, 256]
	ldr	w0, [x19, 1816]
	bl	SM_ReleaseStreamSeg
	b	.L463
	.p2align 3
.L453:
	ldr	x20, [x19]
	ldrb	w1, [x20, 242]
	cmp	w1, 1
	bne	.L463
	add	x19, x19, 53248
	ldr	w1, [x20, 256]
	ldr	w0, [x19, 1792]
	bl	SM_ReleaseStreamSeg
	b	.L463
	.p2align 3
.L454:
	ldr	x20, [x19]
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 256]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 242]
	cmp	w0, 1
	beq	.L463
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	b	.L463
	.p2align 3
.L455:
	ldr	x20, [x19]
	ldr	w0, [x19, 8840]
	ldr	w1, [x20, 256]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 242]
	cmp	w0, 1
	beq	.L463
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	b	.L463
	.size	ReleasePacket, .-ReleasePacket
	.align	3
.LC103:
	.xword	.L451
	.align	3
.LC104:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_VPx
	.type	ReleaseCurPic_VPx, %function
ReleaseCurPic_VPx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	sub	w0, w19, #10
	cmp	w0, 7
	bhi	.L474
	ldr	x1, .LC113
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx477
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx477:
	.section	.rodata
	.align	0
	.align	2
.L477:
	.byte	(.L476 - .Lrtx477) / 4
	.byte	(.L476 - .Lrtx477) / 4
	.byte	(.L476 - .Lrtx477) / 4
	.byte	(.L478 - .Lrtx477) / 4
	.byte	(.L474 - .Lrtx477) / 4
	.byte	(.L474 - .Lrtx477) / 4
	.byte	(.L474 - .Lrtx477) / 4
	.byte	(.L479 - .Lrtx477) / 4
	.text
	.p2align 3
.L476:
	ldr	x19, [x20]
	ldr	w0, [x20, 13368]
	ldr	w1, [x19, 256]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 242]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC117
	mov	w0, 1
	bl	dprint_vfmw
.L482:
	ldr	x3, .LC115
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 232
	ldr	x3, [x3, 96]
	blr	x3
.L474:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L479:
	ldr	x19, [x20]
	add	x20, x20, 311296
	ldr	w1, [x19, 256]
	ldr	w0, [x20, 3272]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 242]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC114
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC115
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 232
	ldr	x3, [x3, 96]
	blr	x3
	b	.L474
	.p2align 3
.L478:
	ldr	x19, [x20]
	ldr	w0, [x20, 8840]
	ldr	w1, [x19, 256]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 242]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC116
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC115
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 232
	ldr	x3, [x3, 96]
	blr	x3
	b	.L474
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	3
.LC113:
	.xword	.L477
	.align	3
.LC114:
	.xword	.LC109
	.align	3
.LC115:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC116:
	.xword	.LC105
	.align	3
.LC117:
	.xword	.LC107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_Realx
	.type	ReleaseCurPic_Realx, %function
ReleaseCurPic_Realx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 8
	beq	.L494
	cmp	w19, 9
	bne	.L492
	ldr	x19, [x20]
	ldrb	w1, [x19, 242]
	cmp	w1, 1
	beq	.L498
.L497:
	ldr	x3, .LC118
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 232
	ldr	x3, [x3, 96]
	blr	x3
.L492:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L494:
	ldr	x19, [x20]
	ldrb	w1, [x19, 242]
	cmp	w1, 1
	bne	.L497
	add	x20, x20, 53248
	ldr	w1, [x19, 256]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	b	.L497
	.p2align 3
.L498:
	add	x20, x20, 53248
	ldr	w1, [x19, 256]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	b	.L497
	.size	ReleaseCurPic_Realx, .-ReleaseCurPic_Realx
	.align	3
.LC118:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_DIVX3
	.type	ReleaseCurPic_DIVX3, %function
ReleaseCurPic_DIVX3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x20]
	ldrb	w1, [x19, 242]
	cmp	w1, 1
	beq	.L501
.L500:
	ldr	x3, .LC119
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 232
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L501:
	add	x20, x20, 40960
	ldr	w1, [x19, 256]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	b	.L500
	.size	ReleaseCurPic_DIVX3, .-ReleaseCurPic_DIVX3
	.align	3
.LC119:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 18
	bls	.L520
.L503:
	ldr	x1, .LC121
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
.L502:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L520:
	ldr	x0, .LC120
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx505
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx505:
	.section	.rodata
	.align	0
	.align	2
.L505:
	.byte	(.L504 - .Lrtx505) / 4
	.byte	(.L506 - .Lrtx505) / 4
	.byte	(.L507 - .Lrtx505) / 4
	.byte	(.L508 - .Lrtx505) / 4
	.byte	(.L503 - .Lrtx505) / 4
	.byte	(.L509 - .Lrtx505) / 4
	.byte	(.L510 - .Lrtx505) / 4
	.byte	(.L503 - .Lrtx505) / 4
	.byte	(.L511 - .Lrtx505) / 4
	.byte	(.L512 - .Lrtx505) / 4
	.byte	(.L513 - .Lrtx505) / 4
	.byte	(.L513 - .Lrtx505) / 4
	.byte	(.L513 - .Lrtx505) / 4
	.byte	(.L514 - .Lrtx505) / 4
	.byte	(.L503 - .Lrtx505) / 4
	.byte	(.L515 - .Lrtx505) / 4
	.byte	(.L516 - .Lrtx505) / 4
	.byte	(.L517 - .Lrtx505) / 4
	.byte	(.L518 - .Lrtx505) / 4
	.text
	.p2align 3
.L518:
	mov	x0, x20
	bl	AVS2DEC_ClearCurPic
	b	.L502
	.p2align 3
.L504:
	mov	x0, x20
	bl	H264_ClearCurrPic
	b	.L502
	.p2align 3
.L506:
	add	x1, x20, 53248
	add	x0, x20, 12288
	add	x0, x0, 2520
	ldr	w1, [x1, 848]
	bl	VC1_ClearCurPic
	b	.L502
	.p2align 3
.L507:
	mov	x0, x20
	bl	MP4_ClearCurPic
	mov	x0, x20
	bl	MP4_Clean_HeadPacket
	b	.L502
	.p2align 3
.L508:
	mov	x0, x20
	bl	MP2_ClearCurPic
	b	.L502
	.p2align 3
.L509:
	mov	x1, x20
	mov	w0, 5
	bl	ReleaseCurPic_DIVX3
	b	.L502
	.p2align 3
.L510:
	mov	x0, x20
	bl	AVS_ClearCurPic
	b	.L502
	.p2align 3
.L511:
	mov	x1, x20
	mov	w0, 8
	bl	ReleaseCurPic_Realx
	b	.L502
	.p2align 3
.L512:
	mov	x1, x20
	mov	w0, 9
	bl	ReleaseCurPic_Realx
	b	.L502
	.p2align 3
.L513:
	mov	x1, x20
	mov	w0, w19
	bl	ReleaseCurPic_VPx
	b	.L502
	.p2align 3
.L514:
	mov	x1, x20
	mov	w0, 13
	bl	ReleaseCurPic_VPx
	b	.L502
	.p2align 3
.L515:
	mov	x0, x20
	bl	MVC_ClearCurrPic
	b	.L502
	.p2align 3
.L516:
	mov	x0, x20
	bl	HEVC_ClearCurrPic
	b	.L502
	.p2align 3
.L517:
	mov	x1, x20
	mov	w0, 17
	bl	ReleaseCurPic_VPx
	b	.L502
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	3
.LC120:
	.xword	.L505
	.align	3
.LC121:
	.xword	.LC111
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegMpeg2
	.type	CheckNewPicSegMpeg2, %function
CheckNewPicSegMpeg2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x20, 3]
	mov	w1, 179
	add	w0, w2, 73
	cmp	w2, wzr
	ccmp	w2, w1, 4, ne
	uxtb	w0, w0
	ccmp	w0, 1, 0, ne
	bhi	.L525
	ldr	w0, [x19]
	cbnz	w0, .L525
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
.L522:
	cbnz	w2, .L523
	str	wzr, [x19]
.L523:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L525:
	mov	w0, -1
	b	.L522
	.size	CheckNewPicSegMpeg2, .-CheckNewPicSegMpeg2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegMpeg4
	.type	CheckNewPicSegMpeg4, %function
CheckNewPicSegMpeg4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	bl	_mcount
	ldrb	w3, [x20, 3]
	mov	w1, 47
	mov	w0, 176
	cmp	w3, 254
	add	w4, w3, 75
	ccmp	w3, w1, 0, ne
	cset	w1, ls
	cmp	w3, 179
	ccmp	w3, w0, 4, ne
	uxtb	w4, w4
	cset	w0, eq
	cmp	w4, 1
	orr	w0, w1, w0
	cset	w1, ls
	orr	w0, w1, w0
	cbnz	w0, .L538
.L527:
	cmp	w21, 1
	bne	.L531
.L528:
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w3, [x20, 3]
.L529:
	cmp	w3, 182
	bne	.L530
	str	wzr, [x19]
.L530:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L538:
	ldr	w0, [x19]
	cbz	w0, .L528
	b	.L527
	.p2align 3
.L531:
	mov	w0, -1
	b	.L529
	.size	CheckNewPicSegMpeg4, .-CheckNewPicSegMpeg4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegAVS
	.type	CheckNewPicSegAVS, %function
CheckNewPicSegAVS:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x20, 3]
	add	w0, w2, 74
	cmp	w2, 179
	cset	w3, eq
	uxtb	w0, w0
	cmp	w0, 1
	cset	w1, ls
	cmp	w2, 176
	cset	w0, eq
	orr	w0, w3, w0
	orr	w0, w1, w0
	cbz	w0, .L543
	ldr	w0, [x19]
	cbnz	w0, .L543
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
	cmp	w2, 179
	cset	w3, eq
.L540:
	cmp	w2, 182
	cset	w1, eq
	orr	w1, w3, w1
	cbz	w1, .L541
	str	wzr, [x19]
.L541:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L543:
	mov	w0, -1
	b	.L540
	.size	CheckNewPicSegAVS, .-CheckNewPicSegAVS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegAVS2
	.type	CheckNewPicSegAVS2, %function
CheckNewPicSegAVS2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x20, 3]
	add	w3, w2, 80
	add	w0, w2, 74
	cmp	w2, 179
	uxtb	w3, w3
	cset	w4, eq
	uxtb	w0, w0
	cmp	w3, 1
	ccmp	w0, 1, 0, hi
	cset	w0, ls
	orr	w0, w4, w0
	cbz	w0, .L551
	ldr	w0, [x19]
	cbnz	w0, .L551
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
	cmp	w2, 179
	cset	w4, eq
.L548:
	cmp	w2, 182
	cset	w1, eq
	orr	w1, w4, w1
	cbz	w1, .L549
	str	wzr, [x19]
.L549:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L551:
	mov	w0, -1
	b	.L548
	.size	CheckNewPicSegAVS2, .-CheckNewPicSegAVS2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegVC1
	.type	CheckNewPicSegVC1, %function
CheckNewPicSegVC1:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x20, 3]
	sub	w0, w2, #12
	uxtb	w0, w0
	cmp	w0, 3
	ccmp	w2, 10, 4, hi
	bne	.L559
	ldr	w0, [x19]
	cbnz	w0, .L559
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
.L556:
	cmp	w2, 13
	bne	.L557
	str	wzr, [x19]
.L557:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L559:
	mov	w0, -1
	b	.L556
	.size	CheckNewPicSegVC1, .-CheckNewPicSegVC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckNewPicSegByVidStd
	.type	CheckNewPicSegByVidStd, %function
CheckNewPicSegByVidStd:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	cmp	w19, 18
	ldr	x1, [x21]
	bls	.L582
.L573:
	mov	w0, -1
.L561:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L582:
	ldr	x0, .LC122
	ldrb	w0, [x0,w19,uxtw]
	adr	x2, .Lrtx563
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx563:
	.section	.rodata
	.align	0
	.align	2
.L563:
	.byte	(.L562 - .Lrtx563) / 4
	.byte	(.L564 - .Lrtx563) / 4
	.byte	(.L565 - .Lrtx563) / 4
	.byte	(.L566 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L567 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L568 - .Lrtx563) / 4
	.byte	(.L569 - .Lrtx563) / 4
	.byte	(.L573 - .Lrtx563) / 4
	.byte	(.L570 - .Lrtx563) / 4
	.text
	.p2align 3
.L562:
	mov	x0, x20
	bl	H264_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L564:
	ldrb	w2, [x1, 3]
	mov	w0, -1
	sub	w3, w2, #12
	uxtb	w3, w3
	cmp	w3, 3
	ccmp	w2, 10, 4, hi
	cset	w3, eq
	cbnz	w3, .L583
.L572:
	cmp	w2, 13
	bne	.L561
	str	wzr, [x20]
	b	.L561
	.p2align 3
.L565:
	mov	w2, w22
	mov	x0, x20
	bl	CheckNewPicSegMpeg4
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L566:
	ldrb	w2, [x1, 3]
	mov	w4, 179
	mov	w0, -1
	add	w3, w2, 73
	cmp	w2, wzr
	ccmp	w2, w4, 4, ne
	uxtb	w3, w3
	ccmp	w3, 1, 0, ne
	cset	w3, ls
	cbnz	w3, .L584
.L571:
	cbnz	w2, .L561
.L581:
	str	wzr, [x20]
	b	.L561
	.p2align 3
.L567:
	mov	x0, x20
	bl	CheckNewPicSegAVS
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L568:
	mov	x0, x20
	bl	MVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L569:
	mov	x0, x20
	bl	HEVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L570:
	mov	x0, x20
	bl	CheckNewPicSegAVS2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L584:
	ldr	w3, [x20]
	cbnz	w3, .L571
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cbz	w2, .L581
	b	.L561
	.p2align 3
.L583:
	ldr	w3, [x20]
	cbnz	w3, .L572
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	b	.L572
	.size	CheckNewPicSegByVidStd, .-CheckNewPicSegByVidStd
	.align	3
.LC122:
	.xword	.L563
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsNewpicSeg
	.type	IsNewpicSeg, %function
IsNewpicSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 2
	mov	w3, 0
	ldr	x0, [x19]
	beq	.L596
.L586:
	ldrb	w2, [x0]
	ldrb	w5, [x0, 1]
	ldrb	w4, [x0, 2]
	cbnz	w2, .L589
	cbnz	w5, .L589
	cmp	w4, 1
	bne	.L589
.L587:
	mov	x2, x19
	mov	w1, w20
	mov	x0, x21
	bl	CheckNewPicSegByVidStd
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L596:
	ldrb	w1, [x19, 80]
	and	w3, w1, 1
	tbz	x1, 0, .L586
	b	.L587
	.p2align 3
.L589:
	ldr	x1, .LC124
	mov	w3, w5
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	3
.LC124:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenUsdPool
	.type	OpenUsdPool, %function
OpenUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC127
	add	x19, x19, 128
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L603
.L598:
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L600:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L600
	mov	w0, 0
.L599:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L603:
	ldr	x1, .LC128
	mov	w0, 7688
	movk	w0, 0x3, lsl 16
	ldr	x1, [x1, 416]
	blr	x1
	str	x0, [x19, w20, sxtw 3]
	cbnz	x0, .L598
	mov	w0, -1
	b	.L599
	.size	OpenUsdPool, .-OpenUsdPool
	.align	3
.LC127:
	.xword	.LANCHOR0
	.align	3
.LC128:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseUsdPool
	.type	CloseUsdPool, %function
CloseUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC130
	add	x19, x19, 128
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L604
	ldr	x1, .LC131
	ldr	x1, [x1, 424]
	blr	x1
	str	xzr, [x19, w20, sxtw 3]
.L604:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool, .-CloseUsdPool
	.align	3
.LC130:
	.xword	.LANCHOR0
	.align	3
.LC131:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenUsdPool_WithMem
	.type	OpenUsdPool_WithMem, %function
OpenUsdPool_WithMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC133
	add	x1, x1, 128
	ldr	x0, [x1, w19, sxtw 3]
	cbz	x0, .L615
.L610:
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L612:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L612
	mov	w0, 0
.L611:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L615:
	str	x20, [x1, w19, sxtw 3]
	cbz	x20, .L613
	mov	x0, x20
	b	.L610
.L613:
	mov	w0, -1
	b	.L611
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	3
.LC133:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseUsdPool_WithMem
	.type	CloseUsdPool_WithMem, %function
CloseUsdPool_WithMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC135
	add	x0, x0, 128
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L616
	str	xzr, [x0, w19, sxtw 3]
.L616:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	3
.LC135:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitUsdPool
	.type	InitUsdPool, %function
InitUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC137
	add	x0, x0, 128
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L624
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L623:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L623
	mov	w0, 0
.L622:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L624:
	mov	w0, -1
	b	.L622
	.size	InitUsdPool, .-InitUsdPool
	.align	3
.LC137:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetUsd
	.type	GetUsd, %function
GetUsd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC139
	add	x0, x0, 128
	ldr	x3, [x0, w19, sxtw 3]
	cbz	x3, .L630
	add	x0, x3, 1048
	mov	w1, 0
	b	.L629
	.p2align 3
.L628:
	add	w1, w1, 1
	add	x0, x0, 1064
	cmp	w1, 192
	beq	.L630
.L629:
	ldr	w2, [x0]
	cbnz	w2, .L628
	ldr	w2, [x0, -4]
	cbnz	w2, .L628
	sxtw	x0, w1
	lsl	x1, x0, 7
	add	x1, x1, x0, lsl 2
	add	x0, x1, x0
	add	x1, x3, x0, lsl 3
	add	x0, x1, 8
	strb	wzr, [x1, 1034]
	strb	wzr, [x1, 1035]
	strb	wzr, [x1, 1036]
	strh	wzr, [x1, 1038]
	str	wzr, [x1, 1044]
	str	wzr, [x1, 1052]
	str	wzr, [x1, 1056]
	str	wzr, [x1, 1060]
	str	xzr, [x1, 1064]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L630:
	mov	x0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetUsd, .-GetUsd
	.align	3
.LC139:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FreeUsdByDec
	.type	FreeUsdByDec, %function
FreeUsdByDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L632
	str	wzr, [x19, 1040]
.L632:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FreeUsdByDec, .-FreeUsdByDec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkUsdByDnr
	.type	MarkUsdByDnr, %function
MarkUsdByDnr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L637
	mov	w0, 1
	str	w0, [x19, 1036]
.L637:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkUsdByDnr
	.type	UnMarkUsdByDnr, %function
UnMarkUsdByDnr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L642
	str	wzr, [x19, 1036]
.L642:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsImageInVoQueue
	.type	IsImageInVoQueue, %function
IsImageInVoQueue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L659
	ldrh	w0, [x19, 4]
	ldrh	w4, [x19, 8]
	and	w0, w0, 63
	.p2align 2
.L658:
	cmp	w0, w4
	beq	.L652
	sxtw	x2, w0
	add	w0, w0, 1
	add	x2, x2, 2
	and	w0, w0, 63
	ldr	x2, [x19, x2, lsl 3]
	cbz	x2, .L658
	ldr	w3, [x2, 148]
	ldr	w2, [x20, 148]
	cmp	w3, w2
	bne	.L658
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L652:
	mov	w0, -1
.L649:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L659:
	ldr	x1, .LC141
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L649
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	3
.LC141:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsVoQueueEmpty
	.type	IsVoQueueEmpty, %function
IsVoQueueEmpty:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L664
	ldrh	w2, [x19, 6]
	mov	w0, 0
	ldrh	w1, [x19, 8]
	cmp	w1, w2
	beq	.L665
.L662:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L665:
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, w1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L664:
	ldr	x2, .LC142
	mov	w0, 0
	ldr	x1, .LC144
	add	x2, x2, 88
	bl	dprint_vfmw
	mov	w0, 0
	b	.L662
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	3
.LC142:
	.xword	.LANCHOR1
	.align	3
.LC144:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetAspectRatio
	.type	SetAspectRatio, %function
SetAspectRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 5
	bls	.L676
	ldr	x1, .LC147
	mov	w2, w20
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L676:
	ldr	x0, .LC145
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx669
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx669:
	.section	.rodata
	.align	0
	.align	2
.L669:
	.byte	(.L668 - .Lrtx669) / 4
	.byte	(.L670 - .Lrtx669) / 4
	.byte	(.L671 - .Lrtx669) / 4
	.byte	(.L672 - .Lrtx669) / 4
	.byte	(.L673 - .Lrtx669) / 4
	.byte	(.L674 - .Lrtx669) / 4
	.text
	.p2align 3
.L673:
	mov	w1, 235
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L674:
	mov	w0, 2
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L668:
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L670:
	mov	w1, 4
	mov	w0, 3
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L671:
	mov	w1, 16
	mov	w0, 9
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L672:
	mov	w1, 221
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetAspectRatio, .-SetAspectRatio
	.align	3
.LC145:
	.xword	.L669
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetVoLastImageID
	.type	GetVoLastImageID, %function
GetVoLastImageID:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 552]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	csinv	w0, w0, wzr, hi
	ldp	x29, x30, [sp], 32
	ret
	.size	GetVoLastImageID, .-GetVoLastImageID
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsMain10Profile
	.type	IsMain10Profile, %function
IsMain10Profile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 324]
	cmp	w1, 1
	beq	.L683
	ldr	w2, [x19, 328]
	mov	w0, 0
	cmp	w2, 1
	beq	.L686
	cmp	w1, 2
	ldr	w1, [x19, 332]
	beq	.L685
	cmp	w1, 1
	cset	w0, eq
.L682:
	cmp	w1, 1
	cset	w1, eq
	orr	w0, w1, w0
.L686:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L683:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L685:
	mov	w0, 1
	b	.L682
	.size	IsMain10Profile, .-IsMain10Profile
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsPtsRewind
	.type	IsPtsRewind, %function
IsPtsRewind:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	sub	x19, x19, x20
	ldr	x0, .LC148
	ldr	x0, [x0, w21, sxtw 3]
	ldr	w0, [x0, 128]
	cbnz	w0, .L691
	cmp	x19, 1000
	ldr	x21, [sp, 32]
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L691:
	mov	x0, 16960
	ldr	x21, [sp, 32]
	movk	x0, 0xf, lsl 16
	cmp	x19, x0
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	IsPtsRewind, .-IsPtsRewind
	.align	3
.LC148:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MetadataMapToSec
	.type	MetadataMapToSec, %function
MetadataMapToSec:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MetadataMapToSec, .-MetadataMapToSec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MetadataUnMapToSec
	.type	MetadataUnMapToSec, %function
MetadataUnMapToSec:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MetadataUnMapToSec, .-MetadataUnMapToSec
	.global	pstVdecUsdPool
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__FUNCTION__.13063, %object
	.size	__FUNCTION__.13063, 19
__FUNCTION__.13063:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__func__.13100, %object
	.size	__func__.13100, 20
__func__.13100:
	.string	"SYNTAX_ReceiveImage"
	.zero	4
	.type	__func__.13147, %object
	.size	__func__.13147, 20
__func__.13147:
	.string	"SYNTAX_ReleaseImage"
	.zero	4
	.type	__func__.13284, %object
	.size	__func__.13284, 13
__func__.13284:
	.string	"DecodeStream"
	.zero	3
	.type	__func__.13465, %object
	.size	__func__.13465, 15
__func__.13465:
	.string	"IsVoQueueEmpty"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"Initializing VO queue\n" )
	.zero	1
.LC2:
	ASCII(.string	"VoQueue state: head(%d) history(%d) tail(%d)" )
	.zero	3
.LC4:
	ASCII(.string	"\n" )
	.zero	6
.LC6:
	ASCII(.string	"%d " )
	.zero	4
.LC9:
	ASCII(.string	"ResetVoQueue but queue not empty: head(%d) history(%d) tail(%d)\n" )
	.zero	7
.LC13:
	ASCII(.string	"out_pts: %lld -> %lld Usertag %lld\n" )
	.zero	4
.LC17:
	ASCII(.string	"image point NULL\n" )
	.zero	6
.LC19:
	ASCII(.string	"call InsertVOQueue\n" )
	.zero	4
.LC22:
	ASCII(.string	"FATAL: p_image(id=%d) has already in the VoQueue!\n" )
	.zero	5
.LC24:
	ASCII(.string	"error=%d,W=%d,H=%d,not acceptable!\n" )
	.zero	4
.LC26:
	ASCII(.string	"Queue=(%02d,%02d,%02d) + F%d\n" )
	.zero	2
.LC37:
	ASCII(.string	"%s, pstVoQue is NULL!!!\n" )
	.zero	7
.LC40:
	ASCII(.string	"Queue=(%02d,%02d,%02d) - F%d\n" )
	.zero	2
.LC44:
	ASCII(.string	"SYNTAX_ReleaseImage p_image is null\n" )
	.zero	3
.LC49:
	ASCII(.string	"Image %d not found in vo queue.\n" )
	.zero	7
.LC51:
	ASCII(.string	"image[%d] null\n" )
.LC53:
	ASCII(.string	"Queue=(%02d,%02d,%02d) x F%d\n" )
	.zero	2
.LC62:
	ASCII(.string	"LENTH ERROR: VC1 S/MP BS is wrong!\n" )
	.zero	4
.LC65:
	ASCII(.string	"SYNTAX ERROR: VC1 S/MP BS is wrong!\n" )
	.zero	3
.LC77:
	ASCII(.string	"pSegMan error!\n" )
.LC81:
	ASCII(.string	"More than two packet!!!ERROR!!!\n" )
	.zero	7
.LC86:
	ASCII(.string	"pSegMan->CurrSeg.IsLastSeg=%d\n" )
	.zero	1
.LC88:
	ASCII(.string	"pSegMan->CurrSeg.PhyAddr=%#x\n" )
	.zero	2
.LC90:
	ASCII(.string	"pSegMan->CurrSeg.LenInByte=%#x\n" )
.LC92:
	ASCII(.string	"ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\n" )
	.zero	5
.LC94:
	ASCII(.string	"ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\n" )
	.zero	5
.LC101:
	ASCII(.string	"Func: %s, Line: %d\n" )
	.zero	4
.LC105:
	ASCII(.string	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC107:
	ASCII(.string	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC109:
	ASCII(.string	"ERROR: VFMW_VP9 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC111:
	ASCII(.string	"VidStd=%d Error!\n" )
	.zero	6
.LC123:
	ASCII(.string	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\n" )
	.zero	2
.LC143:
	ASCII(.string	"%s pstVoQue NULL\n" )
	.zero	6
.LC146:
	ASCII(.string	"WARNNING: aspect ration (%d) is not expected!\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	last_rec_pos_time.13060, %object
	.size	last_rec_pos_time.13060, 128
last_rec_pos_time.13060:
	.zero	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 256
pstVdecUsdPool:
	.zero	256
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
