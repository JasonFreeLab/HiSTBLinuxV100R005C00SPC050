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
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L14 - .Lrtx17) / 4
	.byte	(.L30 - .Lrtx17) / 4
	.text
	.p2align 3
.L30:
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
	beq	.L32
	ldr	x2, [x21, 584]
	sub	w19, w19, #8
	sub	x1, x0, x2
	cmp	x1, 5
	ccmn	x2, #1, 4, ls
	beq	.L42
	cmp	w19, 1
	mov	x0, -1
	bls	.L34
.L32:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L42:
	cmp	w19, 1
	bhi	.L32
	ldrb	w1, [x20, 64]
	and	w1, w1, 3
	cmp	w1, 2
	bne	.L32
.L34:
	mov	x0, -1
	str	x0, [x20, 576]
	b	.L32
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
	beq	.L47
	ldr	x0, [x22, 584]
	sub	w20, w20, #8
	sub	x1, x3, x0
	cmp	x1, 5
	ccmn	x0, #1, 4, ls
	beq	.L53
	cmp	w20, 1
	bls	.L46
	mov	x2, x3
	mov	x3, -1
.L44:
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
.L53:
	cmp	w20, 1
	mov	x2, x3
	bhi	.L44
	ldrb	w0, [x19, 64]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L44
.L46:
	mov	x2, -1
	str	x2, [x19, 576]
	mov	x3, x2
	b	.L44
	.p2align 3
.L47:
	mov	x2, x3
	b	.L44
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
	cbz	w0, .L55
	ldr	w0, [x19, 80]
	cbnz	w0, .L80
.L55:
	ldp	w1, w0, [x19, 68]
	stp	w1, w0, [x19, 76]
	lsr	w2, w1, 1
	lsr	w0, w0, 1
	str	w2, [x19, 84]
	str	w0, [x19, 88]
.L56:
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
	beq	.L57
	str	w2, [x20, 48]
.L57:
	ldr	w1, [x20, 44]
	add	w2, w1, 1
	str	w2, [x20, 44]
	str	w1, [x19, 160]
	ldr	w1, [x24, 528]
	cmp	w26, w1
	beq	.L58
	ldr	x2, .LC15
	ldr	x4, [x2]
	cbz	x4, .L59
	strb	w1, [x29, 104]
	mov	w3, 2
	strb	w0, [x29, 105]
	add	x2, x29, 104
	mov	w1, 7
	mov	w0, w23
	blr	x4
.L59:
	str	w26, [x24, 528]
.L58:
	ldr	w0, [x20, 4]
	cmp	w25, w0
	beq	.L60
	ldr	x0, .LC15
	ldr	x4, [x0]
	cbz	x4, .L61
	add	x2, x29, 112
	mov	w3, 1
	mov	w1, 4
	mov	w0, w23
	strb	w27, [x2, -8]!
	blr	x4
.L61:
	str	w25, [x20, 4]
.L60:
	ldr	w0, [x20, 16]
	cmp	w21, w0
	beq	.L81
.L62:
	ldr	x0, .LC15
	stp	w21, w22, [x20, 16]
	ldr	x4, [x0]
	cbz	x4, .L63
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
.L63:
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
.L80:
	sub	w0, w20, #15
	cmp	w0, 1
	ccmp	w20, wzr, 4, hi
	bne	.L55
	ldr	w1, [x19, 68]
	b	.L56
	.p2align 3
.L81:
	ldr	w0, [x20, 20]
	cmp	w22, w0
	bne	.L62
	b	.L63
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
	cbz	x4, .L82
	mov	w3, 632
	mov	x2, x20
	mov	w1, 5
	mov	w0, w19
	blr	x4
.L82:
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
	cbz	x26, .L118
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
	beq	.L94
	ldr	x25, .LC23
	mov	w21, 1000
	b	.L116
	.p2align 3
.L93:
	add	w19, w19, 1
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L94
.L116:
	sxtw	x0, w19
	ldr	w1, [x26, 148]
	add	x0, x0, 2
	ldr	x0, [x27, x0, lsl 3]
	ldr	w2, [x0, 148]
	cmp	w2, w1
	bne	.L93
	mov	x1, x25
	mov	w0, 0
	add	w19, w19, 1
	bl	dprint_vfmw
	str	w21, [x26, 152]
	and	w19, w19, 63
	ldrh	w3, [x27, 8]
	cmp	w19, w3
	bne	.L116
	.p2align 2
.L94:
	ldr	w2, [x26, 152]
	cmp	w2, 100
	bhi	.L119
	ldp	w3, w4, [x26, 68]
	cmp	w3, 31
	bhi	.L120
.L96:
	ldr	x1, .LC25
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x26, 152]
	cmp	w0, 1000
	beq	.L99
	mov	x2, x26
	mov	x1, x24
	mov	w0, w22
	bl	ReturnImageToSyntax
.L99:
	ldr	x1, [x20, 32]
	mov	w0, 2
	blr	x1
	mov	w0, 1
.L89:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L120:
	cmp	w4, 31
	bls	.L96
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
	add	x2, x2, 294912
	ldr	w4, [x2, 1224]
	add	w4, w4, 1
	str	w4, [x2, 1224]
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
	cbz	x4, .L100
	mov	w3, 632
	mov	x2, x26
	mov	w1, 5
	mov	w0, w23
	blr	x4
.L100:
	mov	w0, 8
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L121
.L102:
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
	bls	.L89
	ldr	w0, [x22, 4]
	cbz	w0, .L104
	mov	w3, 10000
	mul	w0, w0, w3
	udiv	w1, w0, w1
	str	w1, [x22, 8]
.L104:
	lsl	x1, x19, 4
	mov	w0, 1
	add	x19, x1, x19, lsl 2
	lsl	x1, x19, 4
	sub	x19, x1, x19
	add	x1, x21, x19
	str	w2, [x21, x19]
	str	wzr, [x1, 4]
	b	.L89
	.p2align 3
.L119:
	ldp	w3, w4, [x26, 68]
	b	.L96
.L121:
	ldr	x0, [x20]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC32
	ldr	x1, .LC33
	ldr	w0, [x3, w23, sxtw 2]
	ldr	w1, [x1]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L102
	lsl	w2, w23, 24
	ldr	x0, .LC34
	add	w2, w2, 524288
	mov	w1, 517
	str	w4, [x3, w23, sxtw 2]
	bl	DBG_AddTrace
	b	.L102
.L118:
	ldr	x1, .LC18
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L89
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
	bcc	.L123
	sub	w3, w0, w3
.L124:
	ldrh	w4, [x19, 8]
	cmp	w0, w4
	bls	.L127
	add	w4, w4, 64
.L127:
	str	w3, [x21]
	sub	w0, w4, w0
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L123:
	add	w1, w0, 64
	sub	w3, w1, w3
	b	.L124
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
	bls	.L146
.L145:
	mov	x0, 0
	b	.L129
	.p2align 3
.L146:
	ldr	x1, .LC35
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx131
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx131:
	.section	.rodata
	.align	0
	.align	2
.L131:
	.byte	(.L144 - .Lrtx131) / 4
	.byte	(.L132 - .Lrtx131) / 4
	.byte	(.L133 - .Lrtx131) / 4
	.byte	(.L134 - .Lrtx131) / 4
	.byte	(.L145 - .Lrtx131) / 4
	.byte	(.L135 - .Lrtx131) / 4
	.byte	(.L136 - .Lrtx131) / 4
	.byte	(.L145 - .Lrtx131) / 4
	.byte	(.L137 - .Lrtx131) / 4
	.byte	(.L138 - .Lrtx131) / 4
	.byte	(.L139 - .Lrtx131) / 4
	.byte	(.L139 - .Lrtx131) / 4
	.byte	(.L139 - .Lrtx131) / 4
	.byte	(.L140 - .Lrtx131) / 4
	.byte	(.L145 - .Lrtx131) / 4
	.byte	(.L141 - .Lrtx131) / 4
	.byte	(.L142 - .Lrtx131) / 4
	.byte	(.L143 - .Lrtx131) / 4
	.byte	(.L145 - .Lrtx131) / 4
	.byte	(.L145 - .Lrtx131) / 4
	.byte	(.L144 - .Lrtx131) / 4
	.text
	.p2align 3
.L144:
	add	x0, x19, 16
.L129:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L136:
	add	x19, x19, 12288
	add	x0, x19, 3984
	b	.L129
	.p2align 3
.L137:
	add	x19, x19, 53248
	add	x0, x19, 1216
	b	.L129
	.p2align 3
.L138:
	add	x19, x19, 53248
	add	x0, x19, 1192
	b	.L129
	.p2align 3
.L133:
	add	x19, x19, 20480
	add	x0, x19, 2216
	b	.L129
	.p2align 3
.L135:
	add	x19, x19, 40960
	add	x0, x19, 1160
	b	.L129
	.p2align 3
.L142:
	add	x19, x19, 4096
	add	x0, x19, 1928
	b	.L129
	.p2align 3
.L140:
	add	x19, x19, 8192
	add	x0, x19, 48
	b	.L129
	.p2align 3
.L141:
	add	x0, x19, 920
	b	.L129
	.p2align 3
.L134:
	add	x19, x19, 86016
	add	x0, x19, 2256
	b	.L129
	.p2align 3
.L132:
	add	x19, x19, 53248
	add	x0, x19, 232
	b	.L129
	.p2align 3
.L143:
	add	x19, x19, 274432
	add	x0, x19, 1424
	b	.L129
	.p2align 3
.L139:
	add	x19, x19, 12288
	add	x0, x19, 480
	b	.L129
	.size	SYNTAX_GetVoQue, .-SYNTAX_GetVoQue
	.align	3
.LC35:
	.xword	.L131
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
	beq	.L151
	mov	x0, x19
	bl	SYNTAX_GetVoQue
	mov	x19, x0
	cbz	x0, .L153
	ldr	x22, .LC39
	mov	w0, 2
	mov	w21, -3
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w0, [x19, 6]
	ldrh	w1, [x19, 8]
	cmp	w1, w0
	beq	.L150
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
.L150:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w21
.L148:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L151:
	mov	w0, -2
	b	.L148
.L153:
	ldr	x2, .LC36
	mov	w0, 1
	ldr	x1, .LC38
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -2
	b	.L148
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
	bls	.L168
.L155:
	cmn	w19, #2
	beq	.L166
	cmp	w19, 1
	mov	w0, -20
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L168:
	ldr	x1, .LC42
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx157
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx157:
	.section	.rodata
	.align	0
	.align	2
.L157:
	.byte	(.L160 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L155 - .Lrtx157) / 4
	.byte	(.L160 - .Lrtx157) / 4
	.byte	(.L160 - .Lrtx157) / 4
	.byte	(.L160 - .Lrtx157) / 4
	.text
	.p2align 3
.L160:
	mov	w0, -20
	cmp	w19, wzr
	csinc	w0, w0, wzr, ne
.L161:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L166:
	mov	w0, w19
	b	.L161
	.size	SYNTAX_ReleaseImage_RecycleImage_CheckRet, .-SYNTAX_ReleaseImage_RecycleImage_CheckRet
	.align	3
.LC42:
	.xword	.L157
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
	bls	.L187
.L186:
	mov	w1, -2
	b	.L170
	.p2align 3
.L187:
	ldr	x1, .LC43
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx172
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx172:
	.section	.rodata
	.align	0
	.align	2
.L172:
	.byte	(.L171 - .Lrtx172) / 4
	.byte	(.L173 - .Lrtx172) / 4
	.byte	(.L174 - .Lrtx172) / 4
	.byte	(.L175 - .Lrtx172) / 4
	.byte	(.L186 - .Lrtx172) / 4
	.byte	(.L176 - .Lrtx172) / 4
	.byte	(.L177 - .Lrtx172) / 4
	.byte	(.L186 - .Lrtx172) / 4
	.byte	(.L178 - .Lrtx172) / 4
	.byte	(.L179 - .Lrtx172) / 4
	.byte	(.L180 - .Lrtx172) / 4
	.byte	(.L180 - .Lrtx172) / 4
	.byte	(.L180 - .Lrtx172) / 4
	.byte	(.L181 - .Lrtx172) / 4
	.byte	(.L186 - .Lrtx172) / 4
	.byte	(.L182 - .Lrtx172) / 4
	.byte	(.L183 - .Lrtx172) / 4
	.byte	(.L184 - .Lrtx172) / 4
	.byte	(.L186 - .Lrtx172) / 4
	.byte	(.L186 - .Lrtx172) / 4
	.byte	(.L185 - .Lrtx172) / 4
	.text
	.p2align 3
.L171:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	H264DEC_RecycleImage
	mov	w1, w0
.L170:
	mov	x0, x19
	bl	SYNTAX_ReleaseImage_RecycleImage_CheckRet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L173:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VC1DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L174:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MPEG4DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L175:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MPEG2DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L176:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	DIVX3DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L177:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	AVSDEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L178:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	REAL8DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L179:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	REAL9DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L180:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP6DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L181:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP8DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L182:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	MVC_DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L183:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	HEVC_DECRecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L184:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	VP9DEC_RecycleImage
	mov	w1, w0
	b	.L170
	.p2align 3
.L185:
	ldr	w1, [x20, 148]
	add	x0, x19, 8
	bl	USERDEC_RecycleImage
	mov	w1, w0
	b	.L170
	.size	SYNTAX_ReleaseImage_RecycleImage, .-SYNTAX_ReleaseImage_RecycleImage
	.align	3
.LC43:
	.xword	.L172
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
	beq	.L207
	mov	x0, x21
	bl	SYNTAX_GetVoQue
	mov	x25, x0
	cbz	x0, .L208
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
	beq	.L199
	ldr	x23, .LC52
	b	.L205
	.p2align 3
.L196:
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	beq	.L199
.L205:
	sxtw	x19, w20
	add	x0, x19, 2
	ldr	x0, [x25, x0, lsl 3]
	cbz	x0, .L194
	ldr	w0, [x0, 148]
	cmp	w26, w0
	bne	.L196
	mov	w5, 1
.L195:
	ldrh	w4, [x25, 4]
	b	.L198
	.p2align 3
.L203:
	mov	w20, w1
.L198:
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
	bne	.L203
	ldr	w0, [x24, 148]
	cmp	w5, 1
	ldr	w1, [x25, 600]
	sub	w0, w0, w1
	str	w0, [x24, 148]
	ldrh	w2, [x25, 4]
	add	w2, w2, 1
	and	w2, w2, 63
	strh	w2, [x25, 4]
	beq	.L209
	ldrh	w1, [x25, 6]
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	bne	.L205
.L199:
	ldr	x1, .LC50
	mov	w2, w26
	mov	w0, 1
	mov	w19, -2
	bl	dprint_vfmw
.L193:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w19
.L190:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L194:
	mov	w2, w20
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	mov	w5, 2
	b	.L195
.L209:
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
	b	.L193
.L207:
	ldr	x1, .LC45
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L190
.L208:
	ldr	x2, .LC46
	mov	w0, 1
	ldr	x1, .LC47
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L190
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
	bls	.L229
.L228:
	mov	w0, -2
	b	.L211
	.p2align 3
.L229:
	ldr	x1, .LC55
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx213
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx213:
	.section	.rodata
	.align	0
	.align	2
.L213:
	.byte	(.L226 - .Lrtx213) / 4
	.byte	(.L214 - .Lrtx213) / 4
	.byte	(.L215 - .Lrtx213) / 4
	.byte	(.L216 - .Lrtx213) / 4
	.byte	(.L228 - .Lrtx213) / 4
	.byte	(.L217 - .Lrtx213) / 4
	.byte	(.L218 - .Lrtx213) / 4
	.byte	(.L228 - .Lrtx213) / 4
	.byte	(.L219 - .Lrtx213) / 4
	.byte	(.L220 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L222 - .Lrtx213) / 4
	.byte	(.L228 - .Lrtx213) / 4
	.byte	(.L223 - .Lrtx213) / 4
	.byte	(.L224 - .Lrtx213) / 4
	.byte	(.L225 - .Lrtx213) / 4
	.byte	(.L228 - .Lrtx213) / 4
	.byte	(.L228 - .Lrtx213) / 4
	.byte	(.L226 - .Lrtx213) / 4
	.text
	.p2align 3
.L226:
	add	x19, x19, 16
	.p2align 2
.L227:
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
.L211:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L218:
	add	x19, x19, 12288
	add	x19, x19, 3984
	b	.L227
	.p2align 3
.L219:
	add	x19, x19, 53248
	add	x19, x19, 1216
	b	.L227
	.p2align 3
.L220:
	add	x19, x19, 53248
	add	x19, x19, 1192
	b	.L227
	.p2align 3
.L215:
	add	x19, x19, 20480
	add	x19, x19, 2216
	b	.L227
	.p2align 3
.L217:
	add	x19, x19, 40960
	add	x19, x19, 1160
	b	.L227
	.p2align 3
.L224:
	add	x19, x19, 4096
	add	x19, x19, 1928
	b	.L227
	.p2align 3
.L222:
	add	x19, x19, 8192
	add	x19, x19, 48
	b	.L227
	.p2align 3
.L223:
	add	x19, x19, 920
	b	.L227
	.p2align 3
.L216:
	add	x19, x19, 86016
	add	x19, x19, 2256
	b	.L227
	.p2align 3
.L214:
	add	x19, x19, 53248
	add	x19, x19, 232
	b	.L227
	.p2align 3
.L225:
	add	x19, x19, 274432
	add	x19, x19, 1424
	b	.L227
	.p2align 3
.L221:
	add	x19, x19, 12288
	add	x19, x19, 480
	b	.L227
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	3
.LC55:
	.xword	.L213
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
	ldrb	w4, [x19, 17]
	mov	x0, x20
	ldp	w6, w5, [x19, 20]
	ldr	w3, [x19, 28]
	ldr	x7, [x19, 32]
	str	x2, [x29, 48]
	ldrb	w2, [x19, 19]
	strb	w4, [x29, 40]
	stp	w6, w5, [x29, 56]
	str	w3, [x29, 64]
	str	x7, [x29, 72]
	strb	w2, [x29, 41]
	bl	H264DEC_DecodePacket
	cmn	w0, #2
	add	x0, x20, 65536
	beq	.L234
	strb	wzr, [x19, 1]
	ldr	x1, .LC57
	ldrsw	x2, [x0, 1644]
	ldr	x1, [x1, x2, lsl 3]
	strb	wzr, [x1, 1520]
	ldr	x1, [x20, 616]
	cbz	x1, .L235
.L230:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L234:
	mov	w1, 1
	strb	w1, [x19, 1]
	ldr	x2, .LC57
	ldrsw	x3, [x0, 1644]
	ldr	x2, [x2, x3, lsl 3]
	strb	w1, [x2, 1520]
	ldr	x1, [x20, 616]
	cbnz	x1, .L230
.L235:
	add	x20, x20, 12288
	ldrb	w1, [x20, 2640]
	cmp	w1, 1
	bne	.L230
	ldr	w0, [x0, 1644]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2640]
	b	.L230
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
	ldp	w5, w4, [x19, 20]
	ldrb	w3, [x19, 17]
	add	x1, x29, 32
	ldr	w2, [x19, 28]
	mov	x0, x20
	ldr	x6, [x19, 8]
	strb	w3, [x29, 32]
	str	x6, [x29, 40]
	str	w5, [x29, 48]
	stp	w4, w2, [x29, 56]
	bl	HEVCDEC_DecodePacket
	cmn	w0, #2
	beq	.L237
	ldrb	w0, [x20, 7]
	cbz	w0, .L238
.L237:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x1, .LC58
	ldrsw	x2, [x20, 252]
	ldr	x1, [x1, x2, lsl 3]
	strb	w0, [x1, 1520]
	ldr	x0, [x20, 2440]
	cbz	x0, .L244
.L236:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L238:
	strb	wzr, [x19, 1]
	ldr	x0, .LC58
	ldrsw	x1, [x20, 252]
	ldr	x0, [x0, x1, lsl 3]
	strb	wzr, [x0, 1520]
	ldr	x0, [x20, 2440]
	cbnz	x0, .L236
.L244:
	ldrb	w0, [x20, 9]
	cmp	w0, 1
	bne	.L236
	ldr	w0, [x20, 252]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 9]
	b	.L236
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L259
	ldr	x23, .LC59
	add	x22, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x22
	add	x21, x20, 294912
	ldr	x3, [x23, 104]
	blr	x3
	ldr	x3, [x23, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x22
	mov	x0, x20
	bl	VP9DEC_DecodePacket
	ldr	w0, [x21, 3828]
	cbnz	w0, .L260
	ldr	w0, [x21, 3824]
	cbz	w0, .L261
.L249:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x0, [x20, 8]
	cbz	x0, .L262
.L245:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L260:
	ldr	w0, [x21, 3864]
	ldr	w1, [x21, 3868]
	cmp	w1, w0
	bne	.L249
	ldr	w0, [x21, 3824]
	cbnz	w0, .L249
.L261:
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 8]
	cbnz	x0, .L245
.L262:
	add	x20, x20, 262144
	ldrb	w0, [x20, 1044]
	cbnz	w0, .L245
	ldr	x3, [x23, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x21, 3928]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC60
	ldr	x4, [x0]
	cbz	x4, .L245
	ldr	w0, [x21, 3928]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L245
	.p2align 3
.L259:
	add	x20, x20, 294912
	ldr	w0, [x20, 3928]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 3928]
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
	ldrb	w3, [x19, 17]
	add	x1, x29, 40
	ldp	w5, w4, [x19, 20]
	ldr	w2, [x19, 28]
	mov	x0, x20
	ldr	x6, [x19, 8]
	ldr	x7, [x19, 32]
	strb	w3, [x29, 40]
	str	x6, [x29, 48]
	stp	w5, w4, [x29, 56]
	str	w2, [x29, 64]
	str	x7, [x29, 72]
	bl	MVC_DEC_DecodePacket
	cmn	w0, #2
	beq	.L267
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 232]
	cbz	x0, .L268
.L263:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L267:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x0, [x20, 232]
	cbnz	x0, .L263
.L268:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L263
	ldr	w0, [x20, 120]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 1]
	b	.L263
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L282
	ldr	x21, .LC61
	add	x22, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x22
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	ldr	w0, [x19, 104]
	cmp	w0, 15
	ble	.L283
	add	x2, x20, 16384
	ldr	x0, [x19, 88]
	add	x2, x2, 1512
	mov	w1, 16
	bl	Vc1SMPSeqHdr
	cbz	w0, .L284
	ldr	x1, .LC66
.L281:
	mov	w0, 0
	add	x20, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x19, 108]
	ldr	w0, [x20, 832]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC64
	ldr	x4, [x0]
	cbz	x4, .L269
	ldr	w0, [x20, 832]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L269:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L283:
	ldr	x1, .LC63
	b	.L281
	.p2align 3
.L282:
	add	x20, x20, 53248
	ldr	w0, [x20, 832]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 832]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L284:
	ldp	w0, w3, [x19, 100]
	ldr	x2, [x19, 88]
	mov	x1, x22
	add	w0, w0, 16
	sub	w3, w3, #16
	add	x2, x2, 16
	str	x2, [x19, 88]
	stp	w0, w3, [x19, 100]
	mov	x0, x20
	bl	VC1DEC_Decode
	ldr	x3, [x21, 96]
	mov	x2, 160
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L295
	ldr	x22, .LC67
	add	x21, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL8DEC_Decode
	cmn	w0, #2
	beq	.L296
	strb	wzr, [x19, 1]
.L289:
	ldr	x0, [x20, 8]
	cbz	x0, .L297
.L285:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L296:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L289
	.p2align 3
.L295:
	add	x20, x20, 53248
	ldr	w0, [x20, 1816]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L297:
	ldr	x3, [x22, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC68
	ldr	x4, [x0]
	cbz	x4, .L285
	ldr	w0, [x20, 1816]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L285
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L308
	ldr	x22, .LC69
	add	x21, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL9DEC_Decode
	cmn	w0, #2
	beq	.L309
	strb	wzr, [x19, 1]
.L302:
	ldr	x0, [x20, 8]
	cbz	x0, .L310
.L298:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L309:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L302
	.p2align 3
.L308:
	add	x20, x20, 53248
	ldr	w0, [x20, 1792]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L310:
	ldr	x3, [x22, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC70
	ldr	x4, [x0]
	cbz	x4, .L298
	ldr	w0, [x20, 1792]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L298
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L321
	ldr	x22, .LC71
	add	x21, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	DIVX3DEC_Decode
	cmn	w0, #2
	beq	.L322
	strb	wzr, [x19, 1]
.L315:
	ldr	x0, [x20, 8]
	cbz	x0, .L323
.L311:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L322:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L315
	.p2align 3
.L321:
	add	x20, x20, 40960
	ldr	w0, [x20, 1760]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L323:
	ldr	x3, [x22, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 40960
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC72
	ldr	x4, [x0]
	cbz	x4, .L311
	ldr	w0, [x20, 1760]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L311
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L334
	ldr	x22, .LC73
	add	x21, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP8DEC_Decode
	cmn	w0, #2
	beq	.L335
	strb	wzr, [x19, 1]
.L328:
	ldr	x0, [x20, 8]
	cbz	x0, .L336
.L324:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L335:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L328
	.p2align 3
.L334:
	ldr	w0, [x20, 8840]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L336:
	ldr	x3, [x22, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC74
	ldr	x4, [x0]
	cbz	x4, .L324
	ldr	w0, [x20, 8840]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L324
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
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L347
	ldr	x22, .LC75
	add	x21, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP6DEC_Decode
	cmn	w0, #2
	beq	.L348
	strb	wzr, [x19, 1]
.L341:
	ldr	x0, [x20, 8]
	cbz	x0, .L349
.L337:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L348:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L341
	.p2align 3
.L347:
	ldr	w0, [x20, 13368]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L349:
	ldr	x3, [x22, 96]
	mov	x2, 160
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC76
	ldr	x4, [x0]
	cbz	x4, .L337
	ldr	w0, [x20, 13368]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L337
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
	cbz	x19, .L351
	ldr	x0, [x19, 8]
	cbz	x0, .L351
	ldr	x1, .LC79
	ldr	x1, [x1, w20, sxtw 3]
	ldr	w2, [x1, 1448]
	cmp	w2, 1
	beq	.L371
.L354:
	ldrb	w1, [x19, 17]
	strb	wzr, [x19, 408]
	cmp	w1, 1
	beq	.L372
	cbnz	w1, .L370
	ldr	x21, .LC80
	add	x23, x19, 88
	mov	x2, 80
	add	x1, x19, 8
	mov	x0, x23
	add	x22, x19, 168
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldrb	w0, [x19, 2]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x19, 2]
	cmp	w0, 1
	bls	.L370
	ldr	w1, [x19, 108]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 188]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	x3, [x21, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x23
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	x1, .LC82
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC83
	ldr	x4, [x0]
	cbz	x4, .L358
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w0, w20
	blr	x4
.L358:
	strb	wzr, [x19, 2]
.L370:
	mov	w0, -1
.L369:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L371:
	ldr	w1, [x1, 1496]
	cmp	w1, 1
	bne	.L354
	ldrb	w1, [x19, 408]
	cmp	w1, 1
	bne	.L354
	mov	x2, 160
	add	x1, x19, 248
	add	x0, x19, 88
	bl	memcpy
	strb	wzr, [x19, 408]
	mov	w0, 0
	b	.L369
	.p2align 3
.L372:
	ldrb	w21, [x19, 2]
	cbz	w21, .L373
	cmp	w21, 1
	bne	.L370
	ldr	w2, [x19, 104]
	cmp	w2, 1023
	bgt	.L360
	ldr	x22, .LC80
	sxtw	x2, w2
	ldr	x1, [x19, 88]
	sub	x0, x0, x2
	ldr	x3, [x22, 104]
	blr	x3
	strb	w21, [x19, 97]
	ldp	w0, w1, [x19, 104]
	ldp	w2, w4, [x19, 20]
	ldr	x3, [x19, 8]
	sub	w2, w2, w0
	sub	x3, x3, x0, sxtw
	add	w0, w4, w0
	str	x3, [x19, 88]
	stp	w2, w0, [x19, 100]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x19, 28]
	mov	x2, 80
	ldr	x3, [x22, 96]
	mov	w1, 0
	str	w0, [x19, 108]
	add	x0, x19, 168
	blr	x3
.L361:
	mov	w0, 1
	add	x1, x19, 88
	strb	w0, [x19, 408]
	mov	x2, 160
	strb	wzr, [x19, 2]
	add	x0, x19, 248
	bl	memcpy
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L360:
	ldr	x3, .LC80
	mov	x2, 80
	add	x1, x19, 8
	add	x0, x19, 168
	ldr	x3, [x3, 104]
	blr	x3
	b	.L361
	.p2align 3
.L373:
	ldr	x20, .LC80
	mov	x2, 80
	add	x1, x19, 8
	add	x0, x19, 88
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 80
	mov	w1, 0
	add	x0, x19, 168
	blr	x3
	strb	wzr, [x19, 2]
	mov	w0, 0
	b	.L369
	.p2align 3
.L351:
	ldr	x1, .LC78
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L369
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
	ldr	w22, [x21, 832]
	bl	VC1_GetPacketState
	cmp	w0, 2
	beq	.L379
.L375:
	ldr	w0, [x21, 832]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L380
	ldr	x0, [x19, 8]
	cbz	x0, .L381
.L374:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L380:
	add	x20, x20, 88
	mov	x0, x19
	mov	x1, x20
	bl	VC1DEC_Decode
	ldr	x3, .LC85
	mov	x2, 160
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 8]
	cbnz	x0, .L374
.L381:
	add	x19, x19, 12288
	ldrb	w0, [x19, 2511]
	cmp	w0, 1
	bne	.L374
	ldr	w0, [x21, 832]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19, 2511]
	b	.L374
	.p2align 3
.L379:
	ldr	x0, .LC84
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1448]
	cmp	w1, 1
	beq	.L382
.L376:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 2344
	bl	VC1DEC_Decode
	b	.L375
	.p2align 3
.L382:
	ldr	w0, [x0, 1496]
	cbnz	w0, .L375
	b	.L376
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
	ldrb	w2, [x19, 17]
	mov	w0, 22
	ldr	x1, .LC87
	bl	dprint_vfmw
	ldr	x1, .LC89
	mov	w0, 22
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	x1, .LC91
	mov	w0, 22
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, [x20]
	ldr	w0, [x1, 556]
	cmp	w0, 1
	bhi	.L388
	ldr	w2, [x1, 560]
	cmp	w2, 8
	bgt	.L389
	add	x2, x20, 16384
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x2, 1512]
	ldr	w0, [x1, 560]
	mov	x1, x20
	strb	w0, [x2, 1514]
	mov	x0, x19
	beq	.L390
	bl	DecodeStream_VC1_Smp
.L383:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L388:
	ldr	x1, .LC93
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L389:
	ldr	x1, .LC95
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L390:
	bl	DecodeStream_VC1_Adv
	b	.L383
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
	ldr	w22, [x20, 2856]
	bl	MP2_GetPacketState
	cmp	w0, 2
	beq	.L397
.L392:
	ldr	w0, [x20, 2856]
	mov	x1, x21
	bl	SegMan
	cbz	w0, .L398
	ldr	x0, [x19, 8]
	cbz	x0, .L399
.L391:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L398:
	add	x1, x21, 88
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldrb	w0, [x20, 2873]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x21, 1]
	ldr	x0, [x19, 8]
	cbnz	x0, .L391
.L399:
	ldrb	w0, [x20, 2874]
	cmp	w0, 1
	bne	.L391
	ldr	w0, [x20, 2856]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2874]
	b	.L391
	.p2align 3
.L397:
	ldr	x0, .LC96
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1448]
	cmp	w1, 1
	beq	.L400
.L393:
	add	x1, x20, 1680
	mov	x0, x19
	bl	MPEG2DEC_Decode
	b	.L392
	.p2align 3
.L400:
	ldr	w0, [x0, 1496]
	cbnz	w0, .L392
	b	.L393
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
	ldr	w22, [x20, 2816]
	bl	MP4_GetPacketState
	cmp	w0, 3
	beq	.L406
.L402:
	ldr	w0, [x20, 2816]
	mov	x1, x21
	bl	SegMan
	cbz	w0, .L407
	ldr	x0, [x19, 1040]
	cbz	x0, .L408
.L401:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L407:
	add	x1, x21, 88
	mov	x0, x19
	bl	MPEG4DEC_Decode
	ldr	x0, [x19, 1040]
	cbnz	x0, .L401
.L408:
	ldrb	w0, [x20, 2852]
	cmp	w0, 1
	bne	.L401
	ldr	w0, [x20, 2816]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2852]
	b	.L401
	.p2align 3
.L406:
	ldr	x0, .LC97
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1448]
	cmp	w1, 1
	beq	.L409
.L403:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 3440
	bl	MPEG4DEC_Decode
	b	.L402
	.p2align 3
.L409:
	ldr	w0, [x0, 1496]
	cbnz	w0, .L402
	b	.L403
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
	cbnz	w0, .L411
	ldr	x0, .LC98
	ldr	x0, [x0, w21, sxtw 3]
	ldr	w1, [x0, 1448]
	cmp	w1, 1
	beq	.L415
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
.L411:
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L416
	ldr	x0, [x19, 24]
	cbz	x0, .L417
.L410:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L415:
	ldr	w0, [x0, 1496]
	cbnz	w0, .L411
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
	b	.L411
	.p2align 3
.L416:
	add	x1, x20, 88
	mov	x0, x19
	bl	AVSDEC_Decode
	ldr	x0, [x19, 24]
	cbnz	x0, .L410
.L417:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L410
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L410
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	3
.LC98:
	.xword	s_pstVfmwChan
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
	cmp	w19, 17
	bls	.L435
.L419:
	ldr	x2, .LC100
	mov	w3, 1782
	ldr	x1, .LC102
	mov	w0, 32
	add	x2, x2, 72
	bl	dprint_vfmw
.L434:
	mov	w0, 7
	bl	VCTRL_RecordPosTime
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L435:
	ldr	x0, .LC99
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx421
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx421:
	.section	.rodata
	.align	0
	.align	2
.L421:
	.byte	(.L420 - .Lrtx421) / 4
	.byte	(.L422 - .Lrtx421) / 4
	.byte	(.L423 - .Lrtx421) / 4
	.byte	(.L424 - .Lrtx421) / 4
	.byte	(.L419 - .Lrtx421) / 4
	.byte	(.L425 - .Lrtx421) / 4
	.byte	(.L426 - .Lrtx421) / 4
	.byte	(.L419 - .Lrtx421) / 4
	.byte	(.L427 - .Lrtx421) / 4
	.byte	(.L428 - .Lrtx421) / 4
	.byte	(.L429 - .Lrtx421) / 4
	.byte	(.L429 - .Lrtx421) / 4
	.byte	(.L429 - .Lrtx421) / 4
	.byte	(.L430 - .Lrtx421) / 4
	.byte	(.L419 - .Lrtx421) / 4
	.byte	(.L431 - .Lrtx421) / 4
	.byte	(.L432 - .Lrtx421) / 4
	.byte	(.L433 - .Lrtx421) / 4
	.text
	.p2align 3
.L433:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP9
	b	.L434
	.p2align 3
.L420:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_H264
	b	.L434
	.p2align 3
.L422:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VC1
	b	.L434
	.p2align 3
.L423:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MPEG4
	b	.L434
	.p2align 3
.L424:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MPEG2
	b	.L434
	.p2align 3
.L425:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_DIVX3
	b	.L434
	.p2align 3
.L426:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_AVS
	b	.L434
	.p2align 3
.L427:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_REAL8
	b	.L434
	.p2align 3
.L428:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_REAL9
	b	.L434
	.p2align 3
.L429:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP6x
	b	.L434
	.p2align 3
.L430:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_VP8
	b	.L434
	.p2align 3
.L431:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_MVC
	b	.L434
	.p2align 3
.L432:
	mov	x1, x21
	mov	x0, x20
	bl	DecodeStream_HEVC
	b	.L434
	.size	DecodeStream, .-DecodeStream
	.align	3
.LC99:
	.xword	.L421
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
	bls	.L461
.L437:
	ldr	x1, .LC112
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L461:
	ldr	x1, .LC103
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx439
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx439:
	.section	.rodata
	.align	0
	.align	2
.L439:
	.byte	(.L438 - .Lrtx439) / 4
	.byte	(.L437 - .Lrtx439) / 4
	.byte	(.L437 - .Lrtx439) / 4
	.byte	(.L440 - .Lrtx439) / 4
	.byte	(.L441 - .Lrtx439) / 4
	.byte	(.L442 - .Lrtx439) / 4
	.byte	(.L442 - .Lrtx439) / 4
	.byte	(.L442 - .Lrtx439) / 4
	.byte	(.L443 - .Lrtx439) / 4
	.byte	(.L437 - .Lrtx439) / 4
	.byte	(.L437 - .Lrtx439) / 4
	.byte	(.L437 - .Lrtx439) / 4
	.byte	(.L444 - .Lrtx439) / 4
	.text
	.p2align 3
.L444:
	ldr	x20, [x19]
	add	x19, x19, 294912
	ldr	w1, [x20, 244]
	ldr	w0, [x19, 3928]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 233]
	cmp	w0, 1
	beq	.L451
	ldr	x1, .LC110
	mov	w0, 1
	bl	dprint_vfmw
.L451:
	ldr	x3, .LC104
	mov	x2, 160
	mov	w1, 0
	add	x0, x20, 224
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L438:
	ldr	x20, [x19]
	ldrb	w1, [x20, 233]
	cmp	w1, 1
	bne	.L451
	add	x19, x19, 40960
	ldr	w1, [x20, 244]
	ldr	w0, [x19, 1760]
	bl	SM_ReleaseStreamSeg
	b	.L451
	.p2align 3
.L440:
	ldr	x20, [x19]
	ldrb	w1, [x20, 233]
	cmp	w1, 1
	bne	.L451
	add	x19, x19, 53248
	ldr	w1, [x20, 244]
	ldr	w0, [x19, 1816]
	bl	SM_ReleaseStreamSeg
	b	.L451
	.p2align 3
.L441:
	ldr	x20, [x19]
	ldrb	w1, [x20, 233]
	cmp	w1, 1
	bne	.L451
	add	x19, x19, 53248
	ldr	w1, [x20, 244]
	ldr	w0, [x19, 1792]
	bl	SM_ReleaseStreamSeg
	b	.L451
	.p2align 3
.L442:
	ldr	x20, [x19]
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 244]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 233]
	cmp	w0, 1
	beq	.L451
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	b	.L451
	.p2align 3
.L443:
	ldr	x20, [x19]
	ldr	w0, [x19, 8840]
	ldr	w1, [x20, 244]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 233]
	cmp	w0, 1
	beq	.L451
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	b	.L451
	.size	ReleasePacket, .-ReleasePacket
	.align	3
.LC103:
	.xword	.L439
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
	bhi	.L462
	ldr	x1, .LC113
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx465
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx465:
	.section	.rodata
	.align	0
	.align	2
.L465:
	.byte	(.L464 - .Lrtx465) / 4
	.byte	(.L464 - .Lrtx465) / 4
	.byte	(.L464 - .Lrtx465) / 4
	.byte	(.L466 - .Lrtx465) / 4
	.byte	(.L462 - .Lrtx465) / 4
	.byte	(.L462 - .Lrtx465) / 4
	.byte	(.L462 - .Lrtx465) / 4
	.byte	(.L467 - .Lrtx465) / 4
	.text
	.p2align 3
.L464:
	ldr	x19, [x20]
	ldr	w0, [x20, 13368]
	ldr	w1, [x19, 244]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 233]
	cmp	w0, 1
	beq	.L470
	ldr	x1, .LC117
	mov	w0, 1
	bl	dprint_vfmw
.L470:
	ldr	x3, .LC115
	mov	x2, 160
	mov	w1, 0
	add	x0, x19, 224
	ldr	x3, [x3, 96]
	blr	x3
.L462:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L467:
	ldr	x19, [x20]
	add	x20, x20, 294912
	ldr	w1, [x19, 244]
	ldr	w0, [x20, 3928]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 233]
	cmp	w0, 1
	beq	.L470
	ldr	x1, .LC114
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC115
	mov	x2, 160
	mov	w1, 0
	add	x0, x19, 224
	ldr	x3, [x3, 96]
	blr	x3
	b	.L462
	.p2align 3
.L466:
	ldr	x19, [x20]
	ldr	w0, [x20, 8840]
	ldr	w1, [x19, 244]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 233]
	cmp	w0, 1
	beq	.L470
	ldr	x1, .LC116
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC115
	mov	x2, 160
	mov	w1, 0
	add	x0, x19, 224
	ldr	x3, [x3, 96]
	blr	x3
	b	.L462
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	3
.LC113:
	.xword	.L465
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
	beq	.L482
	cmp	w19, 9
	bne	.L480
	ldr	x19, [x20]
	ldrb	w1, [x19, 233]
	cmp	w1, 1
	beq	.L486
.L485:
	ldr	x3, .LC118
	mov	x2, 160
	mov	w1, 0
	add	x0, x19, 224
	ldr	x3, [x3, 96]
	blr	x3
.L480:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L482:
	ldr	x19, [x20]
	ldrb	w1, [x19, 233]
	cmp	w1, 1
	bne	.L485
	add	x20, x20, 53248
	ldr	w1, [x19, 244]
	ldr	w0, [x20, 1816]
	bl	SM_ReleaseStreamSeg
	b	.L485
	.p2align 3
.L486:
	add	x20, x20, 53248
	ldr	w1, [x19, 244]
	ldr	w0, [x20, 1792]
	bl	SM_ReleaseStreamSeg
	b	.L485
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
	ldrb	w1, [x19, 233]
	cmp	w1, 1
	beq	.L489
.L488:
	ldr	x3, .LC119
	mov	x2, 160
	mov	w1, 0
	add	x0, x19, 224
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L489:
	add	x20, x20, 40960
	ldr	w1, [x19, 244]
	ldr	w0, [x20, 1760]
	bl	SM_ReleaseStreamSeg
	b	.L488
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
	cmp	w19, 17
	bls	.L507
.L491:
	ldr	x1, .LC121
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
.L490:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L507:
	ldr	x0, .LC120
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx493
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx493:
	.section	.rodata
	.align	0
	.align	2
.L493:
	.byte	(.L492 - .Lrtx493) / 4
	.byte	(.L494 - .Lrtx493) / 4
	.byte	(.L495 - .Lrtx493) / 4
	.byte	(.L496 - .Lrtx493) / 4
	.byte	(.L491 - .Lrtx493) / 4
	.byte	(.L497 - .Lrtx493) / 4
	.byte	(.L498 - .Lrtx493) / 4
	.byte	(.L491 - .Lrtx493) / 4
	.byte	(.L499 - .Lrtx493) / 4
	.byte	(.L500 - .Lrtx493) / 4
	.byte	(.L501 - .Lrtx493) / 4
	.byte	(.L501 - .Lrtx493) / 4
	.byte	(.L501 - .Lrtx493) / 4
	.byte	(.L502 - .Lrtx493) / 4
	.byte	(.L491 - .Lrtx493) / 4
	.byte	(.L503 - .Lrtx493) / 4
	.byte	(.L504 - .Lrtx493) / 4
	.byte	(.L505 - .Lrtx493) / 4
	.text
	.p2align 3
.L505:
	mov	x1, x20
	mov	w0, 17
	bl	ReleaseCurPic_VPx
	b	.L490
	.p2align 3
.L492:
	mov	x0, x20
	bl	H264_ClearCurrPic
	b	.L490
	.p2align 3
.L494:
	add	x1, x20, 53248
	add	x0, x20, 12288
	add	x0, x0, 2504
	ldr	w1, [x1, 832]
	bl	VC1_ClearCurPic
	b	.L490
	.p2align 3
.L495:
	mov	x0, x20
	bl	MP4_ClearCurPic
	mov	x0, x20
	bl	MP4_Clean_HeadPacket
	b	.L490
	.p2align 3
.L496:
	mov	x0, x20
	bl	MP2_ClearCurPic
	b	.L490
	.p2align 3
.L497:
	mov	x1, x20
	mov	w0, 5
	bl	ReleaseCurPic_DIVX3
	b	.L490
	.p2align 3
.L498:
	mov	x0, x20
	bl	AVS_ClearCurPic
	b	.L490
	.p2align 3
.L499:
	mov	x1, x20
	mov	w0, 8
	bl	ReleaseCurPic_Realx
	b	.L490
	.p2align 3
.L500:
	mov	x1, x20
	mov	w0, 9
	bl	ReleaseCurPic_Realx
	b	.L490
	.p2align 3
.L501:
	mov	x1, x20
	mov	w0, w19
	bl	ReleaseCurPic_VPx
	b	.L490
	.p2align 3
.L502:
	mov	x1, x20
	mov	w0, 13
	bl	ReleaseCurPic_VPx
	b	.L490
	.p2align 3
.L503:
	mov	x0, x20
	bl	MVC_ClearCurrPic
	b	.L490
	.p2align 3
.L504:
	mov	x0, x20
	bl	HEVC_ClearCurrPic
	b	.L490
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	3
.LC120:
	.xword	.L493
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
	bhi	.L512
	ldr	w0, [x19]
	cbnz	w0, .L512
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
.L509:
	cbnz	w2, .L510
	str	wzr, [x19]
.L510:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L512:
	mov	w0, -1
	b	.L509
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
	cbnz	w0, .L525
.L514:
	cmp	w21, 1
	bne	.L518
.L515:
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w3, [x20, 3]
.L516:
	cmp	w3, 182
	bne	.L517
	str	wzr, [x19]
.L517:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L525:
	ldr	w0, [x19]
	cbz	w0, .L515
	b	.L514
	.p2align 3
.L518:
	mov	w0, -1
	b	.L516
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
	cbz	w0, .L530
	ldr	w0, [x19]
	cbnz	w0, .L530
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
	cmp	w2, 179
	cset	w3, eq
.L527:
	cmp	w2, 182
	cset	w1, eq
	orr	w1, w3, w1
	cbz	w1, .L528
	str	wzr, [x19]
.L528:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L530:
	mov	w0, -1
	b	.L527
	.size	CheckNewPicSegAVS, .-CheckNewPicSegAVS
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
	bne	.L538
	ldr	w0, [x19]
	cbnz	w0, .L538
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x20, 3]
.L535:
	cmp	w2, 13
	bne	.L536
	str	wzr, [x19]
.L536:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L538:
	mov	w0, -1
	b	.L535
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
	cmp	w19, 16
	ldr	x1, [x21]
	bls	.L560
.L551:
	mov	w0, -1
.L540:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L560:
	ldr	x0, .LC122
	ldrb	w0, [x0,w19,uxtw]
	adr	x2, .Lrtx542
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx542:
	.section	.rodata
	.align	0
	.align	2
.L542:
	.byte	(.L541 - .Lrtx542) / 4
	.byte	(.L543 - .Lrtx542) / 4
	.byte	(.L544 - .Lrtx542) / 4
	.byte	(.L545 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L546 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L551 - .Lrtx542) / 4
	.byte	(.L547 - .Lrtx542) / 4
	.byte	(.L548 - .Lrtx542) / 4
	.text
	.p2align 3
.L541:
	mov	x0, x20
	bl	H264_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L543:
	ldrb	w2, [x1, 3]
	mov	w0, -1
	sub	w3, w2, #12
	uxtb	w3, w3
	cmp	w3, 3
	ccmp	w2, 10, 4, hi
	cset	w3, eq
	cbnz	w3, .L561
.L550:
	cmp	w2, 13
	bne	.L540
	str	wzr, [x20]
.L563:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L544:
	mov	w2, w22
	mov	x0, x20
	bl	CheckNewPicSegMpeg4
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L545:
	ldrb	w2, [x1, 3]
	mov	w4, 179
	mov	w0, -1
	add	w3, w2, 73
	cmp	w2, wzr
	ccmp	w2, w4, 4, ne
	uxtb	w3, w3
	ccmp	w3, 1, 0, ne
	cset	w3, ls
	cbnz	w3, .L562
.L549:
	cbnz	w2, .L540
.L559:
	str	wzr, [x20]
	b	.L563
	.p2align 3
.L547:
	mov	x0, x20
	bl	MVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L548:
	mov	x0, x20
	bl	HEVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L546:
	mov	x0, x20
	bl	CheckNewPicSegAVS
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L562:
	ldr	w3, [x20]
	cbnz	w3, .L549
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cbz	w2, .L559
	b	.L540
	.p2align 3
.L561:
	ldr	w3, [x20]
	cbnz	w3, .L550
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	b	.L550
	.size	CheckNewPicSegByVidStd, .-CheckNewPicSegByVidStd
	.align	3
.LC122:
	.xword	.L542
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
	beq	.L575
.L565:
	ldrb	w2, [x0]
	ldrb	w5, [x0, 1]
	ldrb	w4, [x0, 2]
	cbnz	w2, .L568
	cbnz	w5, .L568
	cmp	w4, 1
	bne	.L568
.L566:
	mov	x2, x19
	mov	w1, w20
	mov	x0, x21
	bl	CheckNewPicSegByVidStd
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L575:
	ldrb	w1, [x19, 72]
	and	w3, w1, 1
	tbz	x1, 0, .L565
	b	.L566
	.p2align 3
.L568:
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
	cbz	x0, .L582
.L577:
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L579:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L579
	mov	w0, 0
.L578:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L582:
	ldr	x1, .LC128
	mov	w0, 7688
	movk	w0, 0x3, lsl 16
	ldr	x1, [x1, 416]
	blr	x1
	str	x0, [x19, w20, sxtw 3]
	cbnz	x0, .L577
	mov	w0, -1
	b	.L578
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
	cbz	x0, .L583
	ldr	x1, .LC131
	ldr	x1, [x1, 424]
	blr	x1
	str	xzr, [x19, w20, sxtw 3]
.L583:
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
	cbz	x0, .L594
.L589:
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L591:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L591
	mov	w0, 0
.L590:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L594:
	str	x20, [x1, w19, sxtw 3]
	cbz	x20, .L592
	mov	x0, x20
	b	.L589
.L592:
	mov	w0, -1
	b	.L590
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
	cbz	x1, .L595
	str	xzr, [x0, w19, sxtw 3]
.L595:
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
	cbz	x0, .L603
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L602:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L602
	mov	w0, 0
.L601:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L603:
	mov	w0, -1
	b	.L601
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
	cbz	x3, .L609
	add	x0, x3, 1048
	mov	w1, 0
	b	.L608
	.p2align 3
.L607:
	add	w1, w1, 1
	add	x0, x0, 1064
	cmp	w1, 192
	beq	.L609
.L608:
	ldr	w2, [x0]
	cbnz	w2, .L607
	ldr	w2, [x0, -4]
	cbnz	w2, .L607
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
.L609:
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
	cbz	x19, .L611
	str	wzr, [x19, 1040]
.L611:
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
	cbz	x19, .L616
	mov	w0, 1
	str	w0, [x19, 1036]
.L616:
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
	cbz	x19, .L621
	str	wzr, [x19, 1036]
.L621:
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
	cbz	x20, .L638
	ldrh	w0, [x19, 4]
	ldrh	w4, [x19, 8]
	and	w0, w0, 63
	.p2align 2
.L637:
	cmp	w0, w4
	beq	.L631
	sxtw	x2, w0
	add	w0, w0, 1
	add	x2, x2, 2
	and	w0, w0, 63
	ldr	x2, [x19, x2, lsl 3]
	cbz	x2, .L637
	ldr	w3, [x2, 148]
	ldr	w2, [x20, 148]
	cmp	w3, w2
	bne	.L637
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L631:
	mov	w0, -1
.L628:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L638:
	ldr	x1, .LC141
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L628
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
	cbz	x19, .L643
	ldrh	w2, [x19, 6]
	mov	w0, 0
	ldrh	w1, [x19, 8]
	cmp	w1, w2
	beq	.L644
.L641:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L644:
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, w1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L643:
	ldr	x2, .LC142
	mov	w0, 0
	ldr	x1, .LC144
	add	x2, x2, 88
	bl	dprint_vfmw
	mov	w0, 0
	b	.L641
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
	bls	.L655
	ldr	x1, .LC147
	mov	w2, w20
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L655:
	ldr	x0, .LC145
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx648
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx648:
	.section	.rodata
	.align	0
	.align	2
.L648:
	.byte	(.L647 - .Lrtx648) / 4
	.byte	(.L649 - .Lrtx648) / 4
	.byte	(.L650 - .Lrtx648) / 4
	.byte	(.L651 - .Lrtx648) / 4
	.byte	(.L652 - .Lrtx648) / 4
	.byte	(.L653 - .Lrtx648) / 4
	.text
	.p2align 3
.L652:
	mov	w1, 235
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L653:
	mov	w0, 2
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L647:
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L649:
	mov	w1, 4
	mov	w0, 3
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L650:
	mov	w1, 16
	mov	w0, 9
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L651:
	mov	w1, 221
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetAspectRatio, .-SetAspectRatio
	.align	3
.LC145:
	.xword	.L648
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
	ldr	w1, [x19, 300]
	cmp	w1, 1
	beq	.L662
	ldr	w2, [x19, 304]
	mov	w0, 0
	cmp	w2, 1
	beq	.L665
	cmp	w1, 2
	ldr	w1, [x19, 308]
	beq	.L664
	cmp	w1, 1
	cset	w0, eq
.L661:
	cmp	w1, 1
	cset	w1, eq
	orr	w0, w1, w0
.L665:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L662:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L664:
	mov	w0, 1
	b	.L661
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
	cbnz	w0, .L670
	cmp	x19, 1000
	ldr	x21, [sp, 32]
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L670:
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
	.type	__FUNCTION__.12524, %object
	.size	__FUNCTION__.12524, 19
__FUNCTION__.12524:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__func__.12560, %object
	.size	__func__.12560, 20
__func__.12560:
	.string	"SYNTAX_ReceiveImage"
	.zero	4
	.type	__func__.12606, %object
	.size	__func__.12606, 20
__func__.12606:
	.string	"SYNTAX_ReleaseImage"
	.zero	4
	.type	__func__.12735, %object
	.size	__func__.12735, 13
__func__.12735:
	.string	"DecodeStream"
	.zero	3
	.type	__func__.12908, %object
	.size	__func__.12908, 15
__func__.12908:
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
	.type	last_rec_pos_time.12521, %object
	.size	last_rec_pos_time.12521, 128
last_rec_pos_time.12521:
	.zero	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 256
pstVdecUsdPool:
	.zero	256
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
