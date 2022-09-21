#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"avs2.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AVS2_ue_v.isra.2, %function
AVS2_ue_v.isra.2:
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
	bls	.L5
	ldr	x1, .LC1
	mov	w2, w0
	mov	w3, -4370
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -4370
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5:
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
	.size	AVS2_ue_v.isra.2, .-AVS2_ue_v.isra.2
	.align	3
.LC1:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AVS2_se_v.isra.3, %function
AVS2_se_v.isra.3:
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
	bls	.L11
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L11:
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
	.size	AVS2_se_v.isra.3, .-AVS2_se_v.isra.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AVS2_UpdateSceneBuf.part.7, %function
AVS2_UpdateSceneBuf.part.7:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 16384
	add	x20, x21, 20480
	add	x22, x21, 8192
	bl	_mcount
	add	x19, x19, 2560
	add	x20, x20, 128
	b	.L16
	.p2align 3
.L14:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L21
.L16:
	ldrb	w0, [x19, 7]
	sub	w0, w0, #5
	uxtb	w0, w0
	cmp	w0, 1
	bhi	.L14
	ldrb	w0, [x19, 6]
	and	w1, w0, 1
	tbz	x0, 1, .L14
	ldr	x0, [x22, 2440]
	cmp	x0, x19
	beq	.L14
	strb	w1, [x19, 6]
	cbnz	w1, .L14
	strb	wzr, [x19, 5]
	mov	w2, 0
	ldr	w1, [x19, 56]
	add	x19, x19, 104
	ldr	w0, [x21, 4]
	bl	FSP_SetRef
	cmp	x19, x20
	bne	.L16
.L21:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_UpdateSceneBuf.part.7, .-AVS2_UpdateSceneBuf.part.7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SkipToNextStartCode
	.type	AVS2_SkipToNextStartCode, %function
AVS2_SkipToNextStartCode:
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
	bgt	.L29
	b	.L26
	.p2align 3
.L32:
	bl	BsSkip
	cmp	w19, w21
	beq	.L26
.L29:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L32
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L26:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_SkipToNextStartCode, .-AVS2_SkipToNextStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DumpDpbStatus
	.type	AVS2_DumpDpbStatus, %function
AVS2_DumpDpbStatus:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	stp	x23, x24, [sp, 80]
	str	x25, [sp, 96]
	mov	x19, x0
	mov	x0, x30
	uxtb	w21, w1
	add	x19, x19, 16384
	bl	_mcount
	mov	w25, 0
	ldr	x1, .LC10
	mov	w0, 32
	mov	w20, 0
	add	x19, x19, 2566
	bl	dprint_vfmw
	ldr	x1, .LC12
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, .LC15
	cmp	w21, 1
	ldr	x22, .LC8
	ldr	x24, .LC13
	cset	w21, eq
	b	.L36
	.p2align 3
.L34:
	add	w20, w20, 1
	add	x19, x19, 104
	cmp	w20, 16
	beq	.L42
.L36:
	ldrb	w4, [x19]
	cmp	w4, wzr
	cset	w0, ne
	orr	w0, w21, w0
	cbz	w0, .L34
	ldrb	w3, [x19, 1]
	mov	w2, w20
	mov	x1, x23
	mov	w0, 32
	cmp	w3, 6
	add	w25, w25, 1
	uxtb	x5, w3
	mov	x3, x22
	bhi	.L35
	ldr	x3, [x24, x5, lsl 3]
.L35:
	ldr	w8, [x19, 74]
	add	w20, w20, 1
	ldrsh	w7, [x19, -6]
	add	x19, x19, 104
	ldrb	w6, [x19, -106]
	ldrb	w5, [x19, -105]
	str	w8, [sp, 24]
	ldr	w8, [x19, -50]
	str	w8, [sp, 16]
	ldr	w8, [x19, -54]
	str	w8, [sp, 8]
	ldrsh	w8, [x19, -108]
	str	w8, [sp]
	bl	dprint_vfmw
	cmp	w20, 16
	bne	.L36
.L42:
	ldr	x1, .LC17
	mov	w2, w25
	mov	w0, 32
	bl	dprint_vfmw
	add	sp, x29, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	AVS2_DumpDpbStatus, .-AVS2_DumpDpbStatus
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC17:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearPacket
	.type	AVS2_ClearPacket, %function
AVS2_ClearPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 16384
	bl	_mcount
	ldr	w0, [x20, 4]
	ldr	w1, [x19, 2408]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 2394]
	cbnz	w0, .L43
	ldrb	w0, [x19, 2482]
	cmp	w0, 1
	beq	.L48
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L48:
	ldr	w0, [x19, 2488]
	cbz	w0, .L43
	ldr	w1, [x19, 2496]
	ldr	w0, [x20, 4]
	bl	SM_ReleaseStreamSeg
	b	.L43
	.size	AVS2_ClearPacket, .-AVS2_ClearPacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearPicSlice
	.type	AVS2_ClearPicSlice, %function
AVS2_ClearPicSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w0, [x21, 1236]
	cbnz	w0, .L56
	b	.L53
	.p2align 3
.L51:
	ldr	w0, [x21, 1236]
	cmp	w0, w20
	bls	.L53
.L56:
	uxtw	x1, w20
	ldr	w0, [x21, 4]
	lsl	x19, x1, 5
	add	w20, w20, 1
	add	x19, x19, x1, lsl 2
	add	x19, x21, x19
	ldr	w1, [x19, 1268]
	bl	SM_ReleaseStreamSeg
	ldrh	w0, [x19, 1264]
	cmp	w0, 256
	bne	.L51
	ldr	w0, [x19, 1252]
	cbz	w0, .L51
	ldr	w1, [x19, 1272]
	ldr	w0, [x21, 4]
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x21, 1236]
	cmp	w0, w20
	bhi	.L56
.L53:
	str	wzr, [x21, 1236]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ClearPicSlice, .-AVS2_ClearPicSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearDpb
	.type	AVS2_ClearDpb, %function
AVS2_ClearDpb:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 16384
	add	x20, x21, 20480
	bl	_mcount
	add	x19, x19, 2566
	add	x20, x20, 134
	b	.L62
	.p2align 3
.L61:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L67
.L62:
	ldrb	w0, [x19]
	cbz	w0, .L61
	ldr	w1, [x19, 50]
	mov	w2, 0
	ldr	w0, [x21, 4]
	add	x19, x19, 104
	bl	FSP_ClearLogicFs
	strb	wzr, [x19, -104]
	cmp	x19, x20
	bne	.L62
.L67:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ClearDpb, .-AVS2_ClearDpb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SequenceDisplayExtension
	.type	AVS2_SequenceDisplayExtension, %function
AVS2_SequenceDisplayExtension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 56
	add	x19, x19, 16384
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 508]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 512]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 516]
	cbnz	w0, .L74
.L69:
	mov	w1, 14
	mov	x0, x20
	add	x19, x19, 508
	bl	BsGet
	str	w0, [x19, 24]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 28]
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 32]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 36]
	cmp	w0, 1
	mov	w21, w0
	beq	.L75
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L74:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 520]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 524]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 528]
	b	.L69
	.p2align 3
.L75:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 40]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 44]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_SequenceDisplayExtension, .-AVS2_SequenceDisplayExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CopyrightExtension
	.type	AVS2_CopyrightExtension, %function
AVS2_CopyrightExtension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 7
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 20
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_CopyrightExtension, .-AVS2_CopyrightExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CameraParametersExtension
	.type	AVS2_CameraParametersExtension, %function
AVS2_CameraParametersExtension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 7
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_CameraParametersExtension, .-AVS2_CameraParametersExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_TemporalScalabilityExtension
	.type	AVS2_TemporalScalabilityExtension, %function
AVS2_TemporalScalabilityExtension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 56
	mov	w21, 0
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	add	x1, x22, 16384
	add	x23, x1, 1628
	str	w0, [x1, 1628]
	cbz	w0, .L84
	.p2align 2
.L82:
	add	x19, x22, x21, uxtw 2
	mov	w1, 4
	add	x19, x19, 16384
	mov	x0, x20
	add	w21, w21, 1
	bl	BsGet
	mov	w1, 18
	str	w0, [x19, 1632]
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1660]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1692]
	ldr	w0, [x23]
	cmp	w0, w21
	bhi	.L82
.L84:
	mov	w0, 1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	AVS2_TemporalScalabilityExtension, .-AVS2_TemporalScalabilityExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PictureDisplayExtension
	.type	AVS2_PictureDisplayExtension, %function
AVS2_PictureDisplayExtension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	add	x20, x23, 56
	add	x22, x23, 12288
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	ldr	w0, [x22, 2192]
	cmp	w0, 1
	beq	.L102
	ldr	w0, [x22, 4828]
	cbnz	w0, .L103
.L87:
	mov	w0, 1
	str	w0, [x23, 14468]
.L89:
	mov	w21, 0
	add	x22, x22, 2180
	.p2align 2
.L91:
	add	x19, x23, x21, sxtw 2
	mov	w1, 16
	add	x19, x19, 16384
	mov	x0, x20
	bl	BsGet
	mov	w1, 1
	str	w0, [x19, 1604]
	mov	x0, x20
	add	w21, w21, w1
	bl	BsGet
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1616]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w0, [x22]
	cmp	w0, w21
	bhi	.L91
	mov	x0, x20
	bl	AVS2_SkipToNextStartCode
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L103:
	ldr	w0, [x22, 4836]
	cmp	w0, 1
	beq	.L90
.L88:
	mov	w0, 2
	str	w0, [x23, 14468]
	b	.L89
	.p2align 3
.L102:
	ldr	w0, [x22, 4836]
	cmp	w0, 1
	bne	.L87
	ldr	w0, [x22, 4832]
	cmp	w0, 1
	bne	.L88
	.p2align 2
.L90:
	mov	w0, 3
	str	w0, [x23, 14468]
	b	.L89
	.size	AVS2_PictureDisplayExtension, .-AVS2_PictureDisplayExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_MasteringMetadataExtension
	.type	AVS2_MasteringMetadataExtension, %function
AVS2_MasteringMetadataExtension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 16384
	add	x19, x19, 56
	bl	_mcount
	add	x20, x21, 1728
	mov	w1, 4
	mov	x0, x19
	add	x22, x21, 1740
	bl	BsGet
.L105:
	add	x20, x20, 4
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, -4]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	cmp	x20, x22
	bne	.L105
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1752]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1756]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1760]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1764]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1768]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 1772]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	str	w1, [x21, 1720]
	str	w1, [x21, 1724]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_MasteringMetadataExtension, .-AVS2_MasteringMetadataExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_Extension
	.type	AVS2_Extension, %function
AVS2_Extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 56
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	sub	w0, w0, #2
	cmp	w0, 10
	bls	.L118
.L108:
	mov	w1, 4
	mov	x0, x19
	bl	BsSkip
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L118:
	ldr	x1, .LC18
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx110
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx110:
	.section	.rodata
	.align	0
	.align	2
.L110:
	.byte	(.L109 - .Lrtx110) / 4
	.byte	(.L111 - .Lrtx110) / 4
	.byte	(.L112 - .Lrtx110) / 4
	.byte	(.L108 - .Lrtx110) / 4
	.byte	(.L108 - .Lrtx110) / 4
	.byte	(.L113 - .Lrtx110) / 4
	.byte	(.L108 - .Lrtx110) / 4
	.byte	(.L108 - .Lrtx110) / 4
	.byte	(.L114 - .Lrtx110) / 4
	.byte	(.L115 - .Lrtx110) / 4
	.byte	(.L117 - .Lrtx110) / 4
	.text
	.p2align 3
.L117:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L109:
	mov	x0, x20
	bl	AVS2_SequenceDisplayExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L111:
	mov	x0, x20
	bl	AVS2_TemporalScalabilityExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L112:
	mov	x0, x20
	bl	AVS2_CopyrightExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L113:
	mov	x0, x20
	bl	AVS2_PictureDisplayExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	mov	x0, x20
	bl	AVS2_MasteringMetadataExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L115:
	mov	x0, x20
	bl	AVS2_CameraParametersExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_Extension, .-AVS2_Extension
	.align	3
.LC18:
	.xword	.L110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_User_Data
	.type	AVS2_User_Data, %function
AVS2_User_Data:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	ldr	x1, .LC20
	mov	w0, 7
	bl	dprint_vfmw
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	b	.L120
	.p2align 3
.L123:
	ldr	w4, [x19, 24]
	ldr	w3, [x19, 32]
	add	w2, w3, 8
	cmp	w2, w4, lsl 3
	bhi	.L124
	bl	BsGet
.L120:
	mov	w1, 24
	mov	x0, x19
	bl	BsShow
	cmp	w0, 1
	mov	w1, 8
	mov	x0, x19
	bne	.L123
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L124:
	ldr	x2, .LC21
	mov	w0, 1
	ldr	x1, .LC23
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_User_Data, .-AVS2_User_Data
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC21:
	.xword	.LANCHOR1
	.align	3
.LC23:
	.xword	.LC22
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_WriteSliceMsg
	.type	AVS2_WriteSliceMsg, %function
AVS2_WriteSliceMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 1236]
	cmp	w2, 255
	bhi	.L131
	add	x20, x19, 56
	mov	w1, 24
	mov	x0, x20
	bl	BsSkip
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	cmp	w0, 143
	mov	w21, w0
	bhi	.L132
	add	x22, x19, 12288
	ldr	w2, [x22, 2260]
	mov	w0, 144
	ldr	w1, [x22, 2208]
	lsl	w0, w0, w2
	cmp	w1, w0
	bhi	.L133
.L129:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w23, w0
	ldr	w2, [x22, 2260]
	mov	w0, 255
	ldr	w1, [x22, 2200]
	lsl	w0, w0, w2
	cmp	w1, w0
	bhi	.L134
.L130:
	ldr	w1, [x19, 1236]
	mov	w0, 1
	add	x3, x19, 16384
	add	w4, w1, w0
	uxtw	x1, w1
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	x1, x19, x1
	strh	w21, [x1, 1242]
	strh	w23, [x1, 1240]
	ldrh	w2, [x22, 4592]
	madd	w21, w2, w21, w23
	str	w21, [x1, 1244]
	ldr	w2, [x3, 2400]
	str	w2, [x1, 1248]
	ldr	w2, [x3, 2488]
	str	w2, [x1, 1252]
	ldr	w2, [x3, 2404]
	str	w2, [x1, 1256]
	ldr	w2, [x3, 2492]
	str	w2, [x1, 1260]
	ldrb	w2, [x3, 2394]
	strb	w2, [x1, 1264]
	ldrb	w2, [x3, 2482]
	strb	w2, [x1, 1265]
	ldr	w2, [x3, 2408]
	str	w2, [x1, 1268]
	ldr	w2, [x3, 2496]
	str	w2, [x1, 1272]
	str	w4, [x19, 1236]
	ldr	w1, [x19, 12]
	orr	w1, w1, 32768
	str	w1, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L131:
	ldr	x1, .LC25
	mov	w3, 256
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L132:
	ldr	x1, .LC27
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L134:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	add	w23, w23, w0, lsl 8
	b	.L130
	.p2align 3
.L133:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	add	w21, w21, w0, lsl 7
	b	.L129
	.size	AVS2_WriteSliceMsg, .-AVS2_WriteSliceMsg
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_Head_GetRefConfigSet
	.type	AVS2_Head_GetRefConfigSet, %function
AVS2_Head_GetRefConfigSet:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	w20, 0
	bl	_mcount
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	str	w0, [x19]
	mov	w1, 3
	mov	x0, x21
	bl	BsGet
	str	w0, [x19, 4]
	cbz	w0, .L140
	.p2align 2
.L143:
	mov	w1, 6
	mov	x0, x21
	bl	BsGet
	add	x1, x19, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 8]
	ldr	w0, [x19, 4]
	cmp	w0, w20
	bhi	.L143
.L140:
	mov	w1, 3
	mov	x0, x21
	mov	w20, 0
	bl	BsGet
	str	w0, [x19, 36]
	cbz	w0, .L138
	.p2align 2
.L142:
	mov	w1, 6
	mov	x0, x21
	bl	BsGet
	add	x1, x19, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 40]
	ldr	w0, [x19, 36]
	cmp	w0, w20
	bhi	.L142
.L138:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_Head_GetRefConfigSet, .-AVS2_Head_GetRefConfigSet
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_WeightQuantMatrix
	.type	AVS2_WeightQuantMatrix, %function
AVS2_WeightQuantMatrix:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	add	x23, x22, 16
	mov	x20, x2
	bl	_mcount
	.p2align 2
.L149:
	mov	x19, 0
	.p2align 2
.L148:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, 4
	bne	.L148
	add	x22, x22, 4
	cmp	x22, x23
	bne	.L149
	add	x22, x21, 64
	.p2align 2
.L151:
	mov	x19, 0
	.p2align 2
.L150:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	strb	w0, [x21, x19]
	add	x19, x19, 1
	cmp	x19, 8
	bne	.L150
	add	x21, x21, 8
	cmp	x21, x22
	bne	.L151
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	AVS2_WeightQuantMatrix, .-AVS2_WeightQuantMatrix
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupWqMatrix84DataIdx01
	.type	AVS2_SetupWqMatrix84DataIdx01, %function
AVS2_SetupWqMatrix84DataIdx01:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x29, 56
	bl	_mcount
	ldr	x22, .LC33
	mov	x2, 6
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x20, .LC32
	ldr	w0, [x19, 2716]
	cbz	w0, .L183
	cmp	w0, 1
	beq	.L184
	cmp	w0, 2
	beq	.L185
.L158:
	ldr	w0, [x19, 2720]
	cbz	w0, .L172
	cmp	w0, 1
	beq	.L186
	add	x3, x20, 240
	add	x4, x20, 176
	mov	x0, x19
	add	x7, x3, 16
	mov	x6, x19
	mov	w2, 0
	.p2align 2
.L165:
	mov	x1, 0
	b	.L168
	.p2align 3
.L166:
	ldrb	w2, [x3, x1]
.L168:
	sub	x5, x29, #4032
	add	x2, x5, x2, sxtw
	add	x5, x6, x1
	add	x1, x1, 1
	cmp	x1, 4
	ldrb	w2, [x2, 4088]
	strb	w2, [x5, 2486]
	bne	.L166
	add	x3, x3, 4
	add	x6, x6, 4
	cmp	x3, x7
	beq	.L167
	ldrb	w2, [x3]
	b	.L165
.L172:
	add	x4, x20, 16
	add	x3, x20, 80
.L164:
	mov	x0, x19
	add	x7, x3, 16
	mov	x6, x19
	mov	w2, 0
	b	.L165
	.p2align 3
.L167:
	add	x5, x4, 64
	.p2align 2
.L170:
	mov	x1, 0
	.p2align 2
.L169:
	ldrb	w2, [x4, x1]
	sub	x6, x29, #4032
	add	x3, x0, x1
	add	x1, x1, 1
	add	x2, x6, x2
	cmp	x1, 8
	ldrb	w2, [x2, 4088]
	strb	w2, [x3, 2502]
	bne	.L169
	add	x4, x4, 8
	add	x0, x0, 8
	cmp	x4, x5
	bne	.L170
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L183:
	ldr	x3, [x22, 104]
	mov	x2, 6
	mov	x0, x21
	add	x1, x20, 256
	blr	x3
	b	.L158
.L184:
	mov	x0, 0
	mov	w2, 67
	b	.L161
	.p2align 3
.L187:
	ldrb	w2, [x0, x3]
.L161:
	add	x1, x19, x0
	add	x3, x20, 264
	ldrb	w1, [x1, 2474]
	add	w1, w2, w1
	strb	w1, [x21, x0]
	add	x0, x0, 1
	cmp	x0, 6
	bne	.L187
	b	.L158
.L185:
	mov	x0, 0
	mov	w2, 64
	b	.L163
	.p2align 3
.L188:
	ldrb	w2, [x0, x3]
.L163:
	add	x1, x19, x0
	add	x3, x20, 272
	ldrb	w1, [x1, 2480]
	add	w1, w2, w1
	strb	w1, [x21, x0]
	add	x0, x0, 1
	cmp	x0, 6
	bne	.L188
	b	.L158
.L186:
	add	x4, x20, 96
	add	x3, x20, 160
	b	.L164
	.size	AVS2_SetupWqMatrix84DataIdx01, .-AVS2_SetupWqMatrix84DataIdx01
	.align	3
.LC32:
	.xword	.LANCHOR1
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupWqMatrix84
	.type	AVS2_SetupWqMatrix84, %function
AVS2_SetupWqMatrix84:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2696]
	cbz	w0, .L194
	ldr	w0, [x19, 2700]
	cbz	w0, .L195
	cmp	w0, 1
	beq	.L196
.L189:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L195:
	ldr	w0, [x19, 88]
	cbnz	w0, .L193
	ldr	x21, .LC36
	mov	x2, 16
	ldr	x20, .LC37
	add	x0, x19, 2486
	ldr	x3, [x21, 104]
	add	x1, x20, 280
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 296
	mov	x2, 64
	add	x0, x19, 2502
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L194:
	ldr	x20, .LC36
	mov	x2, 16
	mov	w1, 64
	add	x0, x19, 2486
	ldr	x3, [x20, 96]
	blr	x3
	mov	x2, 64
	ldr	x3, [x20, 96]
	add	x0, x19, 2502
	mov	w1, w2
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L193:
	ldr	x20, .LC36
	add	x1, x19, 108
	mov	x2, 16
	add	x0, x19, 2486
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x19, 124
	mov	x2, 64
	add	x0, x19, 2502
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L196:
	mov	x0, x19
	bl	AVS2_SetupWqMatrix84DataIdx01
	b	.L189
	.size	AVS2_SetupWqMatrix84, .-AVS2_SetupWqMatrix84
	.align	3
.LC36:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC37:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ALF_ParameterSet
	.type	AVS2_ALF_ParameterSet, %function
AVS2_ALF_ParameterSet:
	sub	sp, sp, #608
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w24, [x19, 252]
	cmp	w24, 1
	beq	.L198
.L226:
	ldr	w0, [x19, 256]
	cmp	w0, 1
	beq	.L255
.L200:
	ldr	w0, [x19, 260]
	cmp	w0, 1
	beq	.L232
	mov	w0, 1
.L248:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 608
	ret
	.p2align 3
.L232:
	mov	x0, x20
	add	x22, x19, 948
	mov	w21, 0
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	str	w0, [x19, 944]
	b	.L237
	.p2align 3
.L235:
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x22], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L256
.L237:
	add	w1, w3, 64
	mov	x0, x20
	cmp	w1, 127
	bls	.L235
	ldr	x1, .LC57
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
	.p2align 3
.L255:
	mov	x0, x20
	add	x22, x19, 912
	mov	w21, 0
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	str	w0, [x19, 908]
	b	.L231
	.p2align 3
.L229:
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x22], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L257
.L231:
	add	w1, w3, 64
	mov	x0, x20
	cmp	w1, 127
	bls	.L229
	ldr	x1, .LC53
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
	.p2align 3
.L198:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 15
	str	w0, [x19, 264]
	bhi	.L201
	cmn	w0, #1
	mov	w25, 0
	beq	.L258
	str	w24, [x29, 108]
.L240:
	cmp	w25, wzr
	ccmp	w0, 15, 4, gt
	beq	.L205
	mov	x0, x20
	sxtw	x23, w25
	bl	AVS2_ue_v.isra.2
	sub	w2, w0, #1
	add	x1, x19, x23, lsl 2
	cmp	w2, 14
	str	w0, [x1, 268]
	bhi	.L259
.L207:
	mov	x0, x20
	lsl	x22, x23, 2
	add	x27, x22, x23, lsl 5
	add	x26, x29, 128
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	add	x0, x29, 704
	add	x28, x27, 4
	add	x0, x0, x27
	mov	w21, 0
	sub	x0, x0, #4096
	add	x28, x26, x28
	str	w3, [x0, 3520]
	b	.L209
	.p2align 3
.L261:
	ldr	w2, [x24, 268]
	cmp	w2, 63
	bhi	.L212
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x28], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L260
.L209:
	cmn	w3, #64
	add	x24, x19, x22
	mov	x0, x20
	bge	.L261
.L212:
	ldr	x1, .LC47
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
	.p2align 3
.L205:
	cmp	w25, wzr
	sxtw	x23, w25
	ble	.L207
	add	x0, x19, x23, lsl 2
	ldr	w1, [x29, 108]
	str	w1, [x0, 268]
	b	.L207
	.p2align 3
.L201:
	ldr	x1, .LC41
	mov	w2, w0
	mov	w0, w24
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
.L259:
	ldr	x1, .LC43
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
.L258:
	strb	wzr, [x29, 112]
	mov	w0, 0
	add	x26, x29, 128
	sub	x21, x29, #3392
.L216:
	sxtw	x3, w0
	.p2align 2
.L224:
	add	x1, x21, x3
	add	x2, x21, x0, sxtw
	add	w0, w0, 1
	cmp	w0, 15
	ldrb	w1, [x1, 3504]
	strb	w1, [x2, 3504]
	ble	.L224
.L225:
	ldr	x23, .LC48
	add	x22, x19, 332
	add	x24, x19, 908
	mov	w0, 0
	add	x23, x23, 361
	ldr	x25, .LC49
	b	.L223
	.p2align 3
.L262:
	ldrb	w0, [x23], 1
.L223:
	add	x0, x21, x0, sxtw
	ldr	x3, [x25, 104]
	mov	x2, 36
	ldrb	w0, [x0, 3504]
	lsl	x1, x0, 5
	add	x1, x1, x0, lsl 2
	mov	x0, x22
	add	x1, x26, x1
	add	x22, x22, x2
	blr	x3
	cmp	x22, x24
	bne	.L262
	b	.L226
.L256:
	add	w0, w3, 1088
	cmp	w0, 2159
	bhi	.L233
	add	x0, x19, 944
	add	x3, x19, 976
	mov	w1, 64
	.p2align 2
.L234:
	ldr	w2, [x0], 4
	cmp	x3, x0
	sub	w1, w1, w2, lsl 1
	bne	.L234
	ldr	w2, [x19, 976]
	mov	w0, 1
	add	w1, w2, w1
	str	w1, [x19, 976]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 608
	ret
.L260:
	cmn	w3, #1088
	blt	.L210
	ldr	w0, [x24, 268]
	cmp	w0, 1071
	bhi	.L210
	add	x0, x29, 128
	mov	w1, 64
	add	x27, x0, x27
	mov	x0, 0
	.p2align 2
.L211:
	ldr	w2, [x27, x0]
	add	x0, x0, 4
	cmp	x0, 32
	sub	w1, w1, w2, lsl 1
	bne	.L211
	lsl	x3, x23, 5
	add	x2, x29, 704
	add	x3, x3, x23, lsl 2
	ldr	w0, [x19, 264]
	add	x3, x2, x3
	add	w25, w25, 1
	sub	x3, x3, #4096
	add	w7, w0, 1
	cmp	w7, w25
	ldr	w2, [x3, 3552]
	add	w1, w2, w1
	str	w1, [x3, 3552]
	bhi	.L240
	strb	wzr, [x29, 112]
	cmp	w7, 1
	bls	.L238
	mov	w2, 0
	mov	w5, 0
	mov	w9, 1
	sub	x21, x29, #3392
	.p2align 2
.L217:
	add	x0, x19, x9, sxtw 2
	ldr	w8, [x0, 268]
	subs	w6, w8, #1
	beq	.L222
	mov	w0, w5
	mov	w1, 0
	b	.L221
	.p2align 3
.L218:
	ldrb	w2, [x4, 3504]
.L221:
	add	w0, w0, 1
	add	w1, w1, 1
	cmp	w1, w6
	add	x3, x21, x0, sxtw
	uxtb	w0, w0
	add	x4, x21, x0, sxtw
	strb	w2, [x3, 3504]
	bne	.L218
	add	w5, w5, 1
	sub	w8, w8, #2
	add	w5, w8, w5, uxtb
	uxtb	w5, w5
	add	x0, x21, x5, sxtw
	ldrb	w2, [x0, 3504]
.L222:
	add	w5, w5, 1
	add	w9, w9, 1
	add	w2, w2, 1
	cmp	w7, w9
	add	x0, x21, x5, sxtw
	uxtb	w5, w5
	strb	w2, [x0, 3504]
	beq	.L219
	add	x0, x21, x5, sxtw
	ldrb	w2, [x0, 3504]
	b	.L217
.L219:
	cmp	w5, 15
	mov	w0, w5
	ble	.L216
	b	.L225
.L257:
	add	w0, w3, 1088
	cmp	w0, 2159
	bhi	.L227
	add	x0, x19, 908
	add	x3, x19, 940
	mov	w1, 64
	.p2align 2
.L228:
	ldr	w2, [x0], 4
	cmp	x3, x0
	sub	w1, w1, w2, lsl 1
	bne	.L228
	ldr	w0, [x19, 940]
	add	w1, w0, w1
	str	w1, [x19, 940]
	b	.L200
.L227:
	ldr	x1, .LC51
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
.L233:
	ldr	x1, .LC55
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
.L238:
	mov	w0, 0
	sub	x21, x29, #3392
	b	.L216
.L210:
	ldr	x1, .LC45
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L248
	.size	AVS2_ALF_ParameterSet, .-AVS2_ALF_ParameterSet
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR1
	.align	3
.LC49:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DeriveMaxDpbNum
	.type	AVS2_DeriveMaxDpbNum, %function
AVS2_DeriveMaxDpbNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 4]
	cmp	w2, 34
	bls	.L272
	ldr	w0, [x19, 16]
	cmp	w2, 74
	ldr	w1, [x19, 24]
	add	w0, w0, 7
	add	w1, w1, 7
	and	w0, w0, -8
	and	w1, w1, -8
	mul	w1, w0, w1
	bhi	.L266
	mov	w0, 13369344
.L271:
	udiv	w0, w0, w1
	mov	w2, 16
	cmp	w0, w2
	csel	w0, w0, w2, ls
	cmp	w1, 2088960
	sub	w0, w0, #1
	mov	w2, 6
	mov	w1, 7
	csel	w1, w1, w2, ls
	uxtb	w0, w0
	cmp	w0, w1
	csel	w0, w0, w1, cs
	strb	w0, [x19, 2412]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L266:
	cmp	w2, 90
	mov	w0, 56623104
	bls	.L271
	mov	w0, 213909504
	b	.L271
	.p2align 3
.L272:
	mov	w0, 15
	strb	w0, [x19, 2412]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DeriveMaxDpbNum, .-AVS2_DeriveMaxDpbNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_IntraPictureHeader
	.type	AVS2_IntraPictureHeader, %function
AVS2_IntraPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 16384
	add	x20, x22, 56
	bl	_mcount
	ldr	x24, .LC58
	ldr	w3, [x22, 12]
	mov	x2, 16
	mov	w1, 0
	add	x0, x19, 824
	and	w3, w3, -262145
	str	w3, [x22, 12]
	ldr	x3, [x24, 96]
	blr	x3
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 652]
	ldr	w0, [x22, 14472]
	cmp	w0, 72
	beq	.L347
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 660]
	beq	.L348
.L275:
	add	x21, x22, 12288
	ldr	w0, [x21, 2272]
	cbz	w0, .L349
	str	wzr, [x19, 696]
.L278:
	add	x23, x19, 556
	str	wzr, [x19, 700]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2252]
	cmp	w0, 1
	beq	.L350
.L280:
	str	wzr, [x23, 152]
.L281:
	ldr	w0, [x21, 2248]
	cbnz	w0, .L282
	ldr	w1, [x19, 696]
	cbz	w1, .L283
	ldr	w0, [x19, 700]
	cmp	w0, 1
	beq	.L283
.L282:
	str	wzr, [x19, 712]
.L284:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 716]
	cbz	w0, .L285
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtw	x1, w0
	lsl	x4, x1, 6
	ldr	x3, [x24, 104]
	add	x1, x4, x1, lsl 2
	str	w0, [x19, 720]
	add	x1, x21, x1
	mov	x2, 68
	add	x1, x1, 2400
	add	x0, x19, 1536
	blr	x3
	ldr	w0, [x21, 2248]
	cmp	w0, 1
	beq	.L351
.L287:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 728]
	add	x1, x21, 2184
	ldr	w3, [x1, 8]
	cmp	w3, 1
	beq	.L352
.L288:
	ldr	w1, [x1, 12]
	cmp	w1, 1
	beq	.L353
	cbz	w0, .L292
.L290:
	mov	w0, 1
	str	w0, [x19, 732]
.L325:
	mov	w1, 1
	add	x23, x19, 556
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 180]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 184]
	ldr	w24, [x21, 2196]
	cmp	w24, 1
	beq	.L354
	mov	w0, 1
	str	w0, [x23, 188]
.L294:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 748]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 752]
	add	x1, x21, 2184
	ldrb	w23, [x1, 2413]
	lsl	w23, w23, 3
	sub	w23, w23, #1
	cmp	w23, w0
	bcc	.L355
.L295:
	add	x23, x19, 556
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 208]
	cbz	w0, .L356
.L297:
	add	x23, x19, 556
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 232]
	cbz	w0, .L357
	stp	wzr, wzr, [x23, 236]
.L303:
	add	x23, x19, 556
	mov	w0, 2
	strb	w0, [x23, 1]
	ldr	w0, [x21, 2264]
	cbnz	w0, .L358
	stp	wzr, wzr, [x23, 224]
.L310:
	ldr	w0, [x21, 2388]
	cmp	w0, 1
	beq	.L359
.L313:
	str	wzr, [x19, 808]
	str	wzr, [x19, 812]
	str	wzr, [x19, 816]
.L316:
	ldr	w0, [x19, 816]
	cbz	w0, .L319
.L320:
	mov	x1, x20
	add	x0, x19, 556
	bl	AVS2_ALF_ParameterSet
	mov	w20, w0
	cbz	w0, .L360
.L319:
	add	x0, x19, 556
	ldr	w1, [x0, 140]
	cbz	w1, .L361
	ldr	w1, [x0, 144]
	cmp	w1, 1
	beq	.L362
	mov	w1, 6
	str	w1, [x0, 132]
.L323:
	mov	w20, 1
	add	x0, x21, 2180
	strb	wzr, [x19, 556]
	str	w20, [x19, 692]
	bl	AVS2_SetupWqMatrix84
	ldr	w0, [x22, 12]
	orr	w0, w0, 262144
	str	w0, [x22, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L285:
	add	x0, x19, 1536
	mov	x1, x20
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x21, 2248]
	cmp	w0, 1
	bne	.L287
.L351:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	str	w0, [x19, 724]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 728]
	add	x1, x21, 2184
	ldr	w3, [x1, 8]
	cmp	w3, 1
	bne	.L288
	.p2align 2
.L352:
	str	w3, [x19, 728]
	ldr	w0, [x1, 12]
	cmp	w0, 1
	bne	.L290
.L289:
	ldr	x1, .LC62
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 728]
.L292:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 732]
	b	.L325
	.p2align 3
.L361:
	str	wzr, [x0, 132]
	b	.L323
	.p2align 3
.L283:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 63
	str	w0, [x19, 712]
	bls	.L284
	ldr	x1, .LC60
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 63
	str	w0, [x19, 712]
	b	.L284
	.p2align 3
.L349:
	add	x23, x19, 556
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 140]
	bne	.L278
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 144]
	add	x23, x19, 556
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2252]
	cmp	w0, 1
	bne	.L280
	.p2align 2
.L350:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 152]
	b	.L281
	.p2align 3
.L358:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 224]
	cbnz	w0, .L363
	str	wzr, [x23, 228]
	ldr	w0, [x21, 2388]
	cmp	w0, 1
	bne	.L313
.L359:
	add	x23, x19, 808
	add	x24, x19, 820
.L314:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23], 4
	cmp	x24, x23
	bne	.L314
	add	x0, x19, 556
	ldr	w1, [x0, 252]
	cbnz	w1, .L320
	ldr	w0, [x0, 256]
	cbnz	w0, .L320
	b	.L316
	.p2align 3
.L357:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x23, 236]
	bhi	.L364
.L302:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x19, 796]
	bls	.L303
	ldr	x1, .LC72
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 796]
	b	.L303
	.p2align 3
.L356:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 212]
	cbnz	w0, .L365
	stp	wzr, wzr, [x23, 216]
	b	.L297
	.p2align 3
.L355:
	ldr	x1, .LC64
	mov	w2, w0
	mov	w4, w23
	mov	w3, w23
	mov	w0, 1
	bl	dprint_vfmw
	str	w23, [x19, 752]
	b	.L295
	.p2align 3
.L353:
	cbnz	w0, .L289
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 732]
	b	.L325
	.p2align 3
.L360:
	ldr	x2, .LC73
	mov	w0, 1
	ldr	x1, .LC75
	add	x2, x2, 376
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L347:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 668]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 656]
	ldr	w1, [x19, 652]
	orr	w0, w0, w1, lsl 7
	mov	w1, 1
	str	w0, [x19, 652]
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 660]
	bne	.L275
	.p2align 2
.L348:
	mov	w1, 24
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 664]
	b	.L275
	.p2align 3
.L354:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 188]
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	b	.L294
	.p2align 3
.L362:
	mov	w1, 5
	str	w1, [x0, 132]
	b	.L323
	.p2align 3
.L365:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x23, 216]
	bhi	.L366
.L299:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x19, 776]
	bls	.L297
	ldr	x1, .LC68
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 776]
	b	.L297
	.p2align 3
.L364:
	ldr	x1, .LC70
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 236]
	b	.L302
	.p2align 3
.L363:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 228]
	beq	.L367
	cmp	w0, 2
	bne	.L310
	mov	x2, x20
	add	x1, x19, 586
	add	x0, x19, 570
	bl	AVS2_WeightQuantMatrix
	b	.L310
	.p2align 3
.L366:
	ldr	x1, .LC66
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 216]
	b	.L299
	.p2align 3
.L367:
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 244]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 248]
	ldr	w1, [x23, 244]
	cmp	w1, 1
	beq	.L368
.L307:
	cmp	w1, 2
	bne	.L310
	add	x23, x19, 564
	add	x24, x19, 570
	.p2align 2
.L311:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x24, x23
	bne	.L311
	b	.L310
.L368:
	add	x23, x19, 558
	add	x24, x19, 564
	.p2align 2
.L308:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L308
	ldr	w1, [x19, 800]
	b	.L307
	.size	AVS2_IntraPictureHeader, .-AVS2_IntraPictureHeader
	.align	3
.LC58:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
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
.LC73:
	.xword	.LANCHOR1
	.align	3
.LC75:
	.xword	.LC74
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_InterPictureHeader
	.type	AVS2_InterPictureHeader, %function
AVS2_InterPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 56
	add	x19, x22, 16384
	bl	_mcount
	ldr	w2, [x22, 12]
	mov	w1, 32
	mov	x0, x20
	and	w2, w2, -262145
	str	w2, [x22, 12]
	bl	BsGet
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 652]
	ldr	w0, [x22, 14472]
	cmp	w0, 72
	beq	.L442
.L370:
	add	x23, x19, 556
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 116]
	cbz	w0, .L443
	add	x21, x22, 12288
	cmp	w0, 1
	ldr	w0, [x21, 2272]
	ccmp	w0, wzr, 0, eq
	beq	.L444
	str	wzr, [x23, 120]
.L374:
	str	wzr, [x19, 680]
	cbz	w0, .L445
.L375:
	add	x23, x19, 556
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2252]
	cmp	w0, 1
	beq	.L446
	str	wzr, [x23, 152]
.L377:
	ldr	w0, [x21, 2248]
	cbz	w0, .L447
	str	wzr, [x19, 712]
.L379:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 716]
	cbnz	w0, .L448
	add	x0, x19, 1536
	mov	x1, x20
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x21, 2248]
	cmp	w0, 1
	beq	.L449
.L382:
	mov	w1, 1
	mov	x0, x20
	add	x23, x21, 2184
	bl	BsGet
	str	w0, [x19, 728]
	ldr	w1, [x23, 8]
	cmp	w1, 1
	ccmp	w0, 1, 4, eq
	beq	.L383
	ldr	x1, .LC82
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x19, 728]
	ldr	w0, [x23, 12]
	cmp	w0, 1
	beq	.L387
	.p2align 2
.L384:
	mov	w0, 1
	str	w0, [x19, 732]
.L423:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 736]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 740]
	ldr	w24, [x21, 2196]
	cmp	w24, 1
	beq	.L450
.L388:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 748]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 752]
	add	x1, x21, 2184
	ldrb	w23, [x1, 2413]
	lsl	w23, w23, 3
	sub	w23, w23, #1
	cmp	w23, w0
	bcc	.L451
.L389:
	ldr	w1, [x19, 672]
	cmp	w1, 2
	bne	.L390
	ldr	w0, [x19, 732]
	cmp	w0, 1
	beq	.L391
.L390:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 760]
.L391:
	mov	w1, 1
	add	x23, x19, 556
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 128]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 208]
	cbz	w0, .L452
.L393:
	add	x23, x19, 556
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 232]
	cbz	w0, .L453
	stp	wzr, wzr, [x23, 236]
.L399:
	add	x23, x19, 556
	mov	w0, 2
	strb	w0, [x23, 1]
	ldr	w0, [x21, 2264]
	cbnz	w0, .L454
	str	wzr, [x23, 224]
.L406:
	ldr	w0, [x21, 2388]
	cmp	w0, 1
	beq	.L455
	str	wzr, [x19, 808]
	str	wzr, [x19, 812]
	str	wzr, [x19, 816]
.L412:
	ldr	w0, [x19, 816]
	cbnz	w0, .L416
.L415:
	add	x1, x19, 556
	ldr	w0, [x1, 116]
	cmp	w0, 1
	beq	.L456
	cmp	w0, 2
	beq	.L424
	cmp	w0, 3
	bne	.L425
.L424:
	str	w0, [x1, 132]
	ldrb	w0, [x1, 984]
	strb	w0, [x19, 556]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 6
	bhi	.L457
.L422:
	add	x0, x21, 2180
	str	wzr, [x19, 692]
	mov	w20, 1
	bl	AVS2_SetupWqMatrix84
	ldr	w0, [x22, 12]
	orr	w0, w0, 262144
	str	w0, [x22, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L448:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtw	x1, w0
	ldr	x3, .LC80
	lsl	x4, x1, 6
	add	x1, x4, x1, lsl 2
	str	w0, [x19, 720]
	add	x1, x21, x1
	mov	x2, 68
	ldr	x3, [x3, 104]
	add	x1, x1, 2400
	add	x0, x19, 1536
	blr	x3
	ldr	w0, [x21, 2248]
	cmp	w0, 1
	bne	.L382
.L449:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	str	w0, [x19, 724]
	b	.L382
	.p2align 3
.L445:
	ldr	w0, [x19, 672]
	cmp	w0, 2
	beq	.L375
	ldr	w0, [x19, 676]
	cbnz	w0, .L375
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 680]
	b	.L375
	.p2align 3
.L455:
	add	x23, x19, 808
	add	x24, x19, 820
.L410:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23], 4
	cmp	x23, x24
	bne	.L410
	add	x0, x19, 556
	ldr	w1, [x0, 252]
	cbz	w1, .L413
.L416:
	mov	x1, x20
	add	x0, x19, 556
	bl	AVS2_ALF_ParameterSet
	mov	w20, w0
	cbnz	w0, .L415
	ldr	x2, .LC95
	mov	w0, 1
	ldr	x1, .LC96
	add	x2, x2, 400
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L456:
	ldr	w2, [x1, 120]
	cbnz	w2, .L418
	str	w0, [x1, 132]
	ldr	w0, [x1, 984]
	strb	w0, [x19, 556]
.L425:
	ldrb	w0, [x19, 556]
.L464:
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 6
	bls	.L422
.L457:
	ldr	x2, .LC95
	mov	w3, 7
	ldr	x1, .LC98
	mov	w0, 1
	add	x2, x2, 400
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L383:
	ldr	w1, [x23, 12]
	cmp	w1, 1
	beq	.L458
	cbnz	w0, .L384
	.p2align 2
.L385:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 732]
	b	.L423
	.p2align 3
.L447:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 63
	str	w0, [x19, 712]
	bls	.L379
	ldr	x1, .LC79
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 63
	str	w0, [x19, 712]
	b	.L379
	.p2align 3
.L454:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 224]
	cbnz	w0, .L459
	str	wzr, [x23, 228]
	b	.L406
	.p2align 3
.L453:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x23, 236]
	bhi	.L460
.L398:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x19, 796]
	bls	.L399
	ldr	x1, .LC94
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 796]
	b	.L399
	.p2align 3
.L452:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 212]
	cbnz	w0, .L461
	stp	wzr, wzr, [x23, 216]
	b	.L393
	.p2align 3
.L451:
	ldr	x1, .LC86
	mov	w2, w0
	mov	w4, w23
	mov	w3, w23
	mov	w0, 1
	bl	dprint_vfmw
	str	w23, [x19, 752]
	b	.L389
	.p2align 3
.L443:
	ldr	x1, .LC77
	mov	w2, 0
	mov	w0, 1
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L461:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x23, 216]
	bhi	.L462
.L395:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x19, 776]
	bls	.L393
	ldr	x1, .LC90
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 776]
	b	.L393
	.p2align 3
.L459:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 228]
	beq	.L463
	cmp	w0, 2
	bne	.L406
	mov	x2, x20
	add	x1, x19, 586
	add	x0, x19, 570
	bl	AVS2_WeightQuantMatrix
	b	.L406
	.p2align 3
.L460:
	ldr	x1, .LC92
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 236]
	b	.L398
	.p2align 3
.L458:
	cbz	w0, .L385
.L387:
	ldr	x1, .LC84
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 728]
	b	.L385
	.p2align 3
.L442:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 668]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 656]
	ldr	w1, [x19, 652]
	orr	w0, w0, w1, lsl 7
	str	w0, [x19, 652]
	b	.L370
	.p2align 3
.L450:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 744]
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	b	.L388
	.p2align 3
.L446:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 152]
	b	.L377
	.p2align 3
.L418:
	mov	w2, 4
	str	w2, [x1, 132]
	strb	w0, [x19, 556]
	ldrb	w0, [x19, 556]
	b	.L464
	.p2align 3
.L444:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 120]
	ldr	w0, [x21, 2272]
	b	.L374
	.p2align 3
.L462:
	ldr	x1, .LC88
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 216]
	b	.L395
.L463:
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 244]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 248]
	ldr	w1, [x23, 244]
	cmp	w1, 1
	beq	.L465
.L403:
	cmp	w1, 2
	bne	.L406
	add	x23, x19, 564
	add	x24, x19, 570
	.p2align 2
.L407:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L407
	b	.L406
.L465:
	add	x23, x19, 558
	add	x24, x19, 564
	.p2align 2
.L404:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L404
	ldr	w1, [x19, 800]
	b	.L403
.L413:
	ldr	w0, [x0, 256]
	cbnz	w0, .L416
	b	.L412
	.size	AVS2_InterPictureHeader, .-AVS2_InterPictureHeader
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC80:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC95:
	.xword	.LANCHOR1
	.align	3
.LC96:
	.xword	.LC74
	.align	3
.LC98:
	.xword	.LC97
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SequenceHeader
	.type	AVS2_SequenceHeader, %function
AVS2_SequenceHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 56
	add	x22, x20, 12288
	bl	_mcount
	add	x21, x22, 2184
	ldr	x1, .LC100
	mov	w0, 7
	bl	dprint_vfmw
	ldr	w2, [x20, 12]
	mov	w1, 32
	mov	x0, x19
	and	w2, w2, -65537
	str	w2, [x20, 12]
	bl	BsGet
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	and	w1, w0, -3
	cmp	w1, 32
	str	w0, [x20, 14472]
	ccmp	w0, 18, 4, ne
	bne	.L505
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 4]
	cbz	w0, .L506
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 12]
	ldr	w1, [x21, 8]
	cmp	w1, 1
	ccmp	w0, 1, 0, eq
	beq	.L507
.L470:
	add	x21, x22, 2184
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 16]
	cbz	w0, .L508
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 24]
	cbz	w0, .L509
	ldr	w1, [x21, 16]
	add	w2, w0, 7
	and	w2, w2, -8
	str	w0, [x21, 28]
	stp	w1, w2, [x21, 20]
	add	w1, w1, 7
	mov	x0, x19
	and	w1, w1, -8
	str	w1, [x21, 16]
	mov	w1, 2
	bl	BsGet
	cmp	w0, 1
	str	w0, [x21, 32]
	mov	w23, w0
	beq	.L473
	ldr	x1, .LC112
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L506:
	ldr	x1, .LC104
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L468:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L505:
	ldr	x1, .LC102
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L509:
	ldr	x1, .LC110
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L508:
	ldr	x1, .LC108
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L473:
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 3
	lsl	w2, w0, 1
	str	w2, [x21, 36]
	and	w1, w2, -3
	cmp	w1, 8
	bne	.L510
	ldr	w0, [x20, 14472]
	cmp	w0, 34
	beq	.L511
	strb	w1, [x21, 2413]
	mov	w2, w1
	str	wzr, [x21, 40]
.L478:
	ldr	x3, [x20, 40]
	mov	w1, 4
	mov	x0, x19
	str	w2, [x3, 940]
	bl	BsGet
	str	w0, [x22, 2228]
	cbz	w0, .L512
.L479:
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2232]
	cbz	w0, .L513
.L480:
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2236]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2240]
	mov	w1, 12
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2244]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2248]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2240]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2252]
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2256]
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2260]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	cmp	w0, 1
	str	w0, [x22, 2264]
	beq	.L514
.L482:
	add	x23, x22, 2184
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 88]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 92]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 96]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 100]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 184]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 188]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 192]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 196]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 200]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 204]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 208]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 56]
	mov	w1, 6
	mov	x0, x19
	bl	BsGet
	cmp	w0, 32
	str	w0, [x23, 212]
	bhi	.L484
	mov	w21, 0
	cbz	w0, .L489
	.p2align 2
.L499:
	uxtw	x0, w21
	mov	x1, x19
	lsl	x2, x0, 6
	add	w21, w21, 1
	add	x0, x2, x0, lsl 2
	add	x0, x23, x0
	add	x0, x0, 216
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x23, 212]
	cmp	w0, w21
	bhi	.L499
.L489:
	ldr	w0, [x22, 2248]
	cbz	w0, .L515
	str	wzr, [x22, 4576]
.L490:
	mov	x0, x19
	mov	w1, 1
	add	x19, x22, 2184
	bl	BsGet
	str	w0, [x22, 4580]
	mov	w1, 1
	mov	x0, x19
	ldr	w3, [x19, 76]
	ldr	w2, [x19, 16]
	lsl	w1, w1, w3
	sub	w2, w2, #1
	uxth	w1, w1
	add	w2, w1, w2
	uxth	w2, w2
	asr	w2, w2, w3
	strh	w2, [x22, 4592]
	ldr	w2, [x19, 24]
	sub	w2, w2, #1
	add	w1, w1, w2
	uxth	w1, w1
	asr	w1, w1, w3
	strh	w1, [x22, 4594]
	bl	AVS2_DeriveMaxDpbNum
	ldr	w0, [x20, 10796]
	cbz	w0, .L491
	ldr	w1, [x20, 10804]
	cbz	w1, .L491
	ldr	w2, [x19, 16]
	cmp	w0, w2
	beq	.L516
.L494:
	mov	w0, 1
	str	w0, [x20, 20]
.L493:
	ldr	w1, [x20, 12]
	mov	w0, 1
	orr	w1, w1, 65536
	str	w1, [x20, 12]
	b	.L468
	.p2align 3
.L510:
	ldr	x1, .LC114
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, 0
	b	.L468
	.p2align 3
.L491:
	str	wzr, [x20, 20]
	b	.L493
	.p2align 3
.L507:
	ldr	x1, .LC106
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x21, 12]
	b	.L470
	.p2align 3
.L513:
	ldr	x1, .LC120
	mov	w0, 1
	bl	dprint_vfmw
	b	.L480
	.p2align 3
.L512:
	ldr	x1, .LC118
	mov	w0, 1
	bl	dprint_vfmw
	b	.L479
	.p2align 3
.L515:
	mov	w1, 5
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 4576]
	b	.L490
.L484:
	ldr	x1, .LC122
	mov	w2, w0
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L468
.L511:
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	add	w2, w0, 3
	ubfiz	w2, w2, 1, 7
	str	w0, [x21, 40]
	and	w0, w2, 252
	strb	w2, [x21, 2413]
	cmp	w0, 8
	ldr	w3, [x21, 36]
	bne	.L477
	cmp	w2, w3
	bcs	.L478
.L477:
	ldr	x1, .LC116
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L468
.L514:
	mov	w1, w0
	mov	x0, x19
	bl	BsGet
	cmp	w0, 1
	str	w0, [x22, 2268]
	bne	.L482
	mov	x2, x19
	add	x1, x22, 2304
	add	x0, x22, 2288
	bl	AVS2_WeightQuantMatrix
	b	.L482
.L516:
	ldr	w0, [x19, 24]
	cmp	w1, w0
	bne	.L494
	b	.L493
	.size	AVS2_SequenceHeader, .-AVS2_SequenceHeader
	.align	3
.LC100:
	.xword	.LC99
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
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
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_AllocateVHB
	.type	AVS2_AllocateVHB, %function
AVS2_AllocateVHB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	bl	_mcount
	str	wzr, [x29, 88]
	add	x1, x20, 2184
	add	x0, x29, 72
	ldr	w6, [x1, 16]
	ldr	w3, [x1, 24]
	stp	xzr, xzr, [x0]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	add	w0, w6, 15
	lsr	w2, w0, 4
	beq	.L550
	add	w3, w3, 31
	lsr	w3, w3, 5
	lsl	w3, w3, 1
.L519:
	sub	w0, w2, #2
	cmp	w0, 510
	bhi	.L520
	sub	w0, w3, #2
	cmp	w0, 510
	bhi	.L520
	ldr	x0, [x19, 40]
	ldr	w21, [x0, 764]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	cbnz	w21, .L523
	beq	.L551
.L524:
	add	x0, x19, 16384
	mov	w22, 0
	ldrb	w23, [x0, 500]
	add	w23, w23, 1
	mov	w21, w23
.L529:
	ldr	x3, .LC129
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x2, [x19, 40]
	ldr	w1, [x20, 2200]
	ldr	w0, [x20, 2208]
	ldr	w2, [x2, 28]
	stp	w1, w0, [x29, 84]
	add	w1, w1, 15
	add	w0, w0, 15
	and	w1, w1, -16
	and	w0, w0, -16
	cmp	w2, 24
	stp	w1, w0, [x29, 76]
	beq	.L535
	strb	w23, [x29, 73]
	sxtb	w21, w21
	strb	w22, [x29, 74]
.L540:
	ldr	w0, [x19, 4]
	add	x1, x29, 72
	strb	w21, [x29, 75]
	bl	FSP_ConfigInstance
	mov	w21, w0
	cbnz	w0, .L536
	ldr	x1, [x19, 40]
	add	x3, x29, 96
	ldr	w0, [x19, 4]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	str	wzr, [x3, -28]!
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L552
	cbnz	w0, .L553
	mov	w21, 1
	str	w21, [x19, 24]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L520:
	ldr	x1, .LC124
	mov	w0, 1
	mov	w21, 0
	bl	dprint_vfmw
.L544:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L550:
	add	w3, w3, 15
	lsr	w3, w3, 4
	b	.L519
	.p2align 3
.L523:
	bne	.L524
	ldr	w4, [x0, 724]
	ldr	w5, [x0, 728]
	cmp	w6, w4
	ldr	w3, [x20, 2208]
	bhi	.L532
	cmp	w3, w5
	bhi	.L532
.L533:
	ldr	w2, [x0, 752]
	mov	w21, 1
	ldr	w1, [x0, 748]
	add	w23, w1, 2
	cbnz	w2, .L554
	ldrsb	w22, [x0, 772]
	b	.L529
	.p2align 3
.L536:
	ldr	x1, .LC133
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L551:
	ldr	w4, [x0, 724]
	ldr	w5, [x0, 728]
	cmp	w6, w4
	ldr	w3, [x20, 2208]
	bhi	.L526
	cmp	w3, w5
	bhi	.L526
	ldr	w21, [x19, 24]
	cmp	w21, 1
	bne	.L533
	b	.L544
	.p2align 3
.L535:
	strb	wzr, [x29, 73]
	mov	w21, 1
	strb	w22, [x29, 74]
	b	.L540
	.p2align 3
.L553:
	ldr	x1, .LC131
	mov	w0, 0
	bl	dprint_vfmw
	b	.L544
	.p2align 3
.L532:
	ldr	x1, .LC128
	mov	w2, w6
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	b	.L544
	.p2align 3
.L554:
	add	w1, w1, w21
	mov	w21, 17
	cmp	w1, w21
	ldrsb	w22, [x0, 772]
	csel	w21, w1, w21, le
	b	.L529
	.p2align 3
.L526:
	ldr	x1, .LC126
	mov	w2, w6
	mov	w0, 0
	bl	dprint_vfmw
	b	.L544
	.p2align 3
.L552:
	add	x0, x19, 16384
	mov	w21, 3
	add	x0, x0, 1776
	bl	ResetVoQueue
	b	.L544
	.size	AVS2_AllocateVHB, .-AVS2_AllocateVHB
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC129:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC131:
	.xword	.LC130
	.align	3
.LC133:
	.xword	.LC132
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_OutputOneFrame
	.type	AVS2_OutputOneFrame, %function
AVS2_OutputOneFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x20, 56]
	ldr	w0, [x19, 4]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L561
	ldr	w0, [x19, 4]
	mov	w2, 1
	mov	w1, w20
	bl	FSP_SetDisplay
	add	x3, x19, 16384
	ldr	w0, [x19, 4]
	mov	x4, x21
	add	x3, x3, 1776
	mov	x2, x19
	mov	w1, 18
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L557
	ldr	w0, [x19, 4]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	x1, .LC137
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L557:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L561:
	ldr	x1, .LC135
	mov	w2, 2186
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_OutputOneFrame, .-AVS2_OutputOneFrame
	.align	3
.LC135:
	.xword	.LC134
	.align	3
.LC137:
	.xword	.LC136
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DisplayFrameInPOI
	.type	AVS2_DisplayFrameInPOI, %function
AVS2_DisplayFrameInPOI:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	w22, 0
	bl	_mcount
	add	x2, x23, 8192
	add	x0, x23, 16384
	mov	w1, 0
	add	x0, x0, 2570
	ldrsh	w3, [x2, 2266]
	.p2align 2
.L564:
	ldrsh	w2, [x0]
	cmp	w2, w3
	bgt	.L563
	ldrb	w2, [x0, -6]
	cbnz	w2, .L563
	sub	x2, x29, #4000
	add	w4, w22, 1
	add	x5, x2, x22, sxtw
	ldrb	w2, [x0, -4]
	cbz	w2, .L563
	strb	w1, [x5, 4080]
	uxtb	w22, w4
	.p2align 2
.L563:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L564
	cbz	w22, .L562
	ldr	x20, .LC139
	mov	w24, 0
	mov	w25, 0
	mov	w19, 32767
	mov	w21, 1
	.p2align 2
.L566:
	cbz	w22, .L569
	mov	x1, 0
	mov	w5, 32767
	add	x4, x29, 80
	.p2align 2
.L568:
	ldrb	w2, [x4, x1]
	add	x1, x1, 1
	lsl	x0, x2, 3
	mov	x3, x2
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x23, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w2, [x0, 2564]
	cbnz	w2, .L567
	ldrsh	w0, [x0, 2562]
	cmp	w0, w5
	bgt	.L567
	mov	w5, w0
	mov	w25, w3
.L567:
	cmp	w22, w1
	bgt	.L568
	cmp	w5, w19
	beq	.L569
	sxtw	x2, w25
	mov	x0, x23
	lsl	x1, x2, 3
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	lsl	x1, x1, 3
	add	x26, x23, x1
	add	x1, x1, 16384
	add	x26, x26, 16384
	add	x1, x1, 2560
	add	x1, x23, x1
	strb	w21, [x26, 2564]
	bl	AVS2_OutputOneFrame
	ldrsh	w2, [x26, 2562]
	mov	x1, x20
	mov	w0, 13
	bl	dprint_vfmw
.L569:
	add	w24, w24, 1
	uxtb	w24, w24
	cmp	w22, w24
	bne	.L566
.L562:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	AVS2_DisplayFrameInPOI, .-AVS2_DisplayFrameInPOI
	.align	3
.LC139:
	.xword	.LC138
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateSceneBuf
	.type	AVS2_UpdateSceneBuf, %function
AVS2_UpdateSceneBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 13380]
	sub	w0, w0, #5
	cmp	w0, 1
	bhi	.L580
	mov	x0, x19
	bl	AVS2_UpdateSceneBuf.part.7
.L580:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_UpdateSceneBuf, .-AVS2_UpdateSceneBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateRefBuf
	.type	AVS2_UpdateRefBuf, %function
AVS2_UpdateRefBuf:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x25, x23, 12288
	add	x25, x25, 1940
	bl	_mcount
	ldr	x1, .LC141
	mov	w0, 13
	ldr	w2, [x25, 36]
	bl	dprint_vfmw
	ldr	w0, [x25, 36]
	cbz	w0, .L582
	ldr	x22, .LC143
	mov	w24, 0
	add	x21, x23, 8192
	add	x20, x23, 16384
	.p2align 2
.L588:
	add	x4, x25, x24, sxtw 2
	ldrh	w3, [x21, 2266]
	mov	x1, x22
	mov	w2, w24
	mov	w0, 13
	ldr	w19, [x4, 40]
	sub	w19, w3, w19
	sxth	w19, w19
	mov	w3, w19
	bl	dprint_vfmw
	add	x0, x20, 2566
	mov	w1, 0
	b	.L587
	.p2align 3
.L584:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L586
.L587:
	ldrsh	w2, [x0, -6]
	cmp	w2, w19
	bne	.L584
	ldrb	w2, [x0]
	and	w3, w2, 2
	cbz	w2, .L584
	ldrb	w2, [x0, 1]
	uxtb	w3, w3
	sub	w2, w2, #5
	uxtb	w2, w2
	cmp	w2, 1
	bhi	.L585
	strb	w3, [x0]
	cbnz	w3, .L584
.L585:
	sxtw	x1, w1
	mov	w2, 0
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x0, x23, x0, lsl 3
	add	x0, x0, 16384
	strb	wzr, [x0, 2565]
	ldr	w1, [x0, 2616]
	ldr	w0, [x23, 4]
	bl	FSP_SetRef
	.p2align 2
.L586:
	ldr	w0, [x25, 36]
	add	w24, w24, 1
	cmp	w0, w24
	bhi	.L588
.L582:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	AVS2_UpdateRefBuf, .-AVS2_UpdateRefBuf
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_RefreshBuf
	.type	AVS2_RefreshBuf, %function
AVS2_RefreshBuf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 16384
	mov	w19, 0
	bl	_mcount
	add	x20, x20, 2566
	b	.L599
	.p2align 3
.L597:
	cmp	w19, 16
	add	x20, x20, 104
	beq	.L601
.L599:
	sxtw	x1, w19
	ldrb	w2, [x20]
	lsl	x0, x1, 3
	add	w19, w19, 1
	sub	x0, x0, x1
	lsl	x0, x0, 1
	cbz	w2, .L597
	sub	x0, x0, x1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 16384
	ldrh	w0, [x0, 2564]
	cmp	w0, 1
	bne	.L597
	and	w2, w2, 2
	uxtb	w2, w2
	strb	w2, [x20]
	cbnz	w2, .L597
	ldr	w1, [x20, 50]
	add	x20, x20, 104
	ldr	w0, [x21, 4]
	bl	FSP_SetRef
	cmp	w19, 16
	bne	.L599
.L601:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_RefreshBuf, .-AVS2_RefreshBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetPicInfo
	.type	AVS2_SetPicInfo, %function
AVS2_SetPicInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x5, x19, 8192
	ldr	w0, [x5, 5204]
	ldr	w3, [x5, 5212]
	add	x6, x5, 2584
	ldr	w2, [x5, 4980]
	sxth	w7, w0
	add	w0, w3, w0
	sub	w0, w0, w2
	strh	w7, [x5, 2266]
	strh	w0, [x5, 2268]
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L604
	ldrsh	w0, [x5, 2264]
	cmp	w0, w7
	ble	.L604
	add	x0, x19, 16384
	add	x4, x19, 20480
	ldr	w6, [x6, 16]
	add	x0, x0, 2562
	add	x4, x4, 130
	.p2align 2
.L606:
	ldrh	w1, [x0]
	ldrh	w3, [x0, -2]
	sub	w1, w1, #256
	ldrh	w2, [x0, 8]
	sub	w3, w3, #256
	strh	w3, [x0, -2]
	sxth	w1, w1
	sub	w2, w2, #256
	strh	w1, [x0]
	lsl	w1, w1, 1
	strh	w2, [x0, 8]
	strh	w1, [x0, 6]
	cbnz	w6, .L605
	ldr	w2, [x5, 5244]
	add	w1, w1, 1
	cbnz	w2, .L605
	strh	w1, [x0, 6]
.L605:
	add	x0, x0, 104
	cmp	x0, x4
	bne	.L606
.L604:
	strh	w7, [x5, 2264]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_SetPicInfo, .-AVS2_SetPicInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_VarifyDecMode
	.type	AVS2_VarifyDecMode, %function
AVS2_VarifyDecMode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 40]
	ldr	w19, [x0, 8]
	cmp	w19, 2
	beq	.L611
	cmp	w19, 3
	beq	.L612
	cmp	w19, 1
	mov	w21, 1
	beq	.L627
.L610:
	str	w19, [x20, 32]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L627:
	ldr	w0, [x20, 13380]
	add	x22, x20, 12288
	mov	w21, w19
	add	x22, x22, 960
	cmp	w0, 2
	beq	.L628
.L614:
	ldr	w0, [x20, 32]
	cmp	w0, 1
	beq	.L610
	mov	x0, x20
	bl	AVS2_ClearDpb
	str	w19, [x20, 32]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L612:
	str	w19, [x20, 32]
	mov	w21, 0
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L611:
	ldr	w0, [x20, 13384]
	str	w19, [x20, 32]
	cmp	w0, wzr
	cset	w21, ne
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L628:
	ldr	w0, [x22, 980]
	cbnz	w0, .L614
	mov	x0, x20
	bl	AVS2_DisplayFrameInPOI
	ldr	w0, [x22, 1016]
	cbnz	w0, .L629
.L615:
	mov	x0, x20
	mov	w21, 0
	bl	AVS2_RefreshBuf
	b	.L614
.L629:
	mov	x0, x20
	bl	AVS2_UpdateRefBuf
	b	.L615
	.size	AVS2_VarifyDecMode, .-AVS2_VarifyDecMode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_VarifyFrame
	.type	AVS2_VarifyFrame, %function
AVS2_VarifyFrame:
	sub	sp, sp, #80
	stp	x29, x30, [sp, 48]
	add	x29, sp, 48
	stp	x19, x20, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 16384
	mov	w2, 0
	add	x0, x0, 2566
	b	.L635
	.p2align 3
.L631:
	add	w2, w2, 1
	add	x0, x0, 104
	cmp	w2, 16
	beq	.L644
.L635:
	ldrb	w3, [x0]
	cbz	w3, .L631
	ldr	w1, [x0, 50]
	ldr	w4, [x19, 56]
	cmp	w4, w1
	beq	.L632
	ldr	w5, [x0, 54]
	ldr	w6, [x19, 100]
	cmp	w6, w5
	beq	.L645
	ldr	w7, [x0, 74]
	ldr	w6, [x19, 80]
	cmp	w6, w7
	bne	.L631
	ldrb	w8, [x0, -1]
	cmp	w8, 1
	beq	.L638
	tbz	x3, 1, .L631
.L638:
	mov	w9, w6
	sxtw	x2, w2
.L634:
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x2, x0, x2
	mov	w0, 1
	add	x2, x20, x2, lsl 3
	add	x2, x2, 16384
	ldrb	w7, [x2, 2567]
	str	w9, [sp, 40]
	str	w1, [sp, 24]
	str	w5, [sp, 32]
	ldrsh	w1, [x2, 2560]
	str	w1, [sp, 16]
	str	w8, [sp, 8]
	str	w3, [sp]
	ldr	x1, .LC145
	ldrsh	w3, [x19]
	ldrb	w2, [x19, 7]
	ldr	w5, [x19, 60]
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L644:
	add	sp, x29, 0
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L632:
	sxtw	x2, w2
	ldr	w6, [x19, 80]
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x20, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w8, [x0, 2565]
	ldr	w5, [x0, 2620]
	ldr	w9, [x0, 2640]
	b	.L634
.L645:
	sxtw	x2, w2
	ldr	w6, [x19, 80]
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x20, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w8, [x0, 2565]
	ldr	w9, [x0, 2640]
	b	.L634
	.size	AVS2_VarifyFrame, .-AVS2_VarifyFrame
	.align	3
.LC145:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ReleaseFrameBuf
	.type	AVS2_ReleaseFrameBuf, %function
AVS2_ReleaseFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 8192
	bl	_mcount
	add	x19, x19, 2264
	ldr	x0, [x20, 10632]
	cbz	x0, .L647
	ldr	w1, [x0, 56]
	mov	w2, 0
	ldr	w0, [x20, 4]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 176]
	strb	wzr, [x0, 6]
.L647:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_ReleaseFrameBuf, .-AVS2_ReleaseFrameBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupFrameBuf
	.type	AVS2_SetupFrameBuf, %function
AVS2_SetupFrameBuf:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 8192
	bl	_mcount
	add	x3, x21, 16384
	ldr	w0, [x22, 5188]
	cmp	w0, 6
	beq	.L652
.L656:
	ldrb	w0, [x3, 2566]
	cbz	w0, .L688
	add	x0, x3, 2670
	mov	w19, 1
.L661:
	ldrb	w1, [x0]
	add	x0, x0, 104
	cbz	w1, .L653
	add	w19, w19, 1
	cmp	w19, 16
	bne	.L661
.L660:
	ldr	x2, .LC146
	mov	w0, 1
	ldr	x1, .LC148
	mov	w20, 0
	add	x2, x2, 424
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L688:
	mov	w19, 0
.L653:
	sxtw	x19, w19
	mov	w1, 1
	lsl	x0, x19, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	lsl	x19, x19, 3
	add	x19, x19, 16384
	add	x19, x19, 2560
	add	x19, x21, x19
	str	x19, [x22, 2440]
	ldr	w0, [x21, 4]
	bl	FSP_NewLogicFs
	mov	w23, w0
	cbz	x19, .L660
.L657:
	ldr	w0, [x21, 4]
	mov	w1, w23
	bl	FSP_GetLogicFs
	cmp	w23, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L689
	ldr	w0, [x21, 4]
	mov	w1, w23
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L690
	str	w23, [x19, 56]
	mov	w1, w23
	ldr	w0, [x0, 112]
	str	w0, [x19, 88]
	ldr	w0, [x20, 116]
	str	w0, [x19, 92]
	ldr	w0, [x20, 140]
	str	w0, [x19, 96]
	ldp	w2, w0, [x20, 36]
	sub	w0, w0, w2
	str	w0, [x19, 84]
	ldr	w0, [x20, 36]
	str	w0, [x19, 60]
	ldr	w0, [x20, 40]
	str	w0, [x19, 64]
	ldr	w0, [x21, 4]
	bl	FSP_GetPmvAddr
	str	w0, [x19, 80]
	add	x1, x21, 12288
	mov	x3, -1
	ldr	w2, [x20, 212]
	str	w2, [x19, 100]
	ldr	w2, [x20, 144]
	str	w2, [x19, 68]
	ldr	w4, [x20, 36]
	ldr	w2, [x20, 44]
	sub	w2, w2, w4
	str	w2, [x19, 72]
	ldp	w4, w2, [x20, 44]
	sub	w2, w2, w4
	str	w2, [x19, 76]
	ldr	w2, [x21, 28]
	str	w2, [x20, 176]
	ldrb	w2, [x1, 905]
	str	w2, [x20, 168]
	ldrb	w1, [x1, 905]
	str	w1, [x20, 172]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 56]
	str	x1, [x20, 584]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 72]
	str	x1, [x20, 592]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 88]
	str	x1, [x20, 600]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 104]
	str	w1, [x20]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 108]
	str	w1, [x20, 4]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 112]
	str	w1, [x20, 8]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 128]
	str	w1, [x20, 12]
	ldr	w1, [x22, 5232]
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x20, 52]
	ldr	x1, [x21, 40]
	str	x3, [x1, 56]
	ldrsh	w1, [x22, 2266]
	strh	w1, [x19]
	ldrsh	w1, [x22, 2268]
	strh	w1, [x19, 2]
	lsl	w1, w1, 1
	ldr	w2, [x22, 5188]
	strb	w2, [x19, 7]
	ldr	w2, [x22, 6036]
	strb	w2, [x19, 5]
	strb	wzr, [x19, 4]
	ldrh	w0, [x22, 2266]
	ldr	w2, [x22, 5212]
	strh	w1, [x19, 8]
	add	w0, w2, w0
	strh	w0, [x19, 10]
	ldr	w0, [x22, 2600]
	cbnz	w0, .L685
	ldr	w0, [x22, 5244]
	cbz	w0, .L691
.L666:
	strb	w0, [x19, 12]
	mov	x1, x19
	mov	x0, x21
	ldr	w2, [x22, 5232]
	strb	w2, [x19, 13]
	ldr	w2, [x22, 5236]
	strb	w2, [x19, 14]
	strb	wzr, [x19, 6]
	bl	AVS2_VarifyFrame
	mov	w20, w0
	cbz	w0, .L692
	ldrb	w0, [x19, 7]
	cmp	w0, 4
	bls	.L693
	cmp	w0, 6
	beq	.L694
	mov	w0, 3
	strb	w0, [x19, 6]
.L669:
	ldr	w1, [x19, 56]
	mov	w2, 1
	ldr	w0, [x21, 4]
	mov	w20, w2
	bl	FSP_SetRef
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L691:
	add	w1, w1, 1
	strh	w1, [x19, 8]
.L685:
	ldr	w0, [x22, 5244]
	b	.L666
	.p2align 3
.L689:
	ldr	x2, .LC146
	mov	w0, 1
	ldr	x1, .LC150
	mov	w20, 0
	add	x2, x2, 424
	bl	dprint_vfmw
.L662:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L652:
	mov	w1, 0
	add	x0, x3, 2566
	b	.L658
	.p2align 3
.L655:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L656
.L658:
	ldrb	w2, [x0]
	cbz	w2, .L655
	ldrb	w2, [x0, 1]
	cmp	w2, 6
	bne	.L655
	ldrsh	w5, [x0, -6]
	ldrsh	w4, [x22, 2266]
	cmp	w5, w4
	bne	.L655
	sxtw	x1, w1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x1, x0, x1
	lsl	x0, x1, 3
	add	x19, x0, 16384
	add	x0, x21, x0
	add	x19, x19, 2560
	add	x0, x0, 16384
	add	x19, x21, x19
	str	x19, [x22, 2440]
	ldr	w23, [x0, 2616]
	cbnz	x19, .L657
	b	.L656
	.p2align 3
.L693:
	ldrb	w0, [x19, 5]
	mov	w1, 1
	strb	w1, [x19, 6]
	mov	w20, 1
	cbnz	w0, .L669
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L690:
	ldr	x2, .LC146
	mov	w0, 1
	ldr	x1, .LC152
	add	x2, x2, 424
	bl	dprint_vfmw
	b	.L662
	.p2align 3
.L692:
	ldrsh	w2, [x19]
	mov	w0, 1
	ldr	x1, .LC154
	bl	dprint_vfmw
	mov	x0, x21
	bl	AVS2_ReleaseFrameBuf
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L694:
	mov	w0, 2
	strb	w0, [x19, 6]
	b	.L669
	.size	AVS2_SetupFrameBuf, .-AVS2_SetupFrameBuf
	.align	3
.LC146:
	.xword	.LANCHOR1
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupRefFrame
	.type	AVS2_SetupRefFrame, %function
AVS2_SetupRefFrame:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x24, x19, 8192
	bl	_mcount
	add	x0, x24, 2448
	add	x1, x24, 2568
	.p2align 2
.L696:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L696
	add	x26, x19, 12288
	ldr	w0, [x26, 1092]
	cmp	w0, 4
	beq	.L733
	add	x23, x26, 1940
	ldr	w3, [x23, 4]
	sub	w1, w3, #1
	cmp	w1, 6
	bhi	.L701
	cbz	w3, .L702
	ldr	x20, .LC160
	mov	w21, 0
	mov	w22, 0
	add	x25, x19, 16384
	.p2align 2
.L707:
	add	x0, x23, x22, sxtw 2
	ldrsh	w2, [x24, 2266]
	ldr	w3, [x0, 8]
	sub	w3, w2, w3
	sxth	w3, w3
	cmp	w2, w3
	beq	.L703
	add	x0, x25, 2566
	mov	w1, 0
	b	.L706
	.p2align 3
.L704:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L705
.L706:
	ldrb	w4, [x0]
	tbz	x4, 0, .L704
	ldrsh	w4, [x0, -6]
	cmp	w4, w3
	bne	.L704
	ldrb	w4, [x0, -1]
	cmp	w4, 1
	bne	.L704
	ldrb	w4, [x0, 1]
	cmp	w4, 6
	beq	.L704
	cmp	w1, 15
	sxtw	x1, w1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x1, x24, x21, uxtw 3
	lsl	x0, x0, 3
	add	w21, w21, 1
	add	x0, x0, 16384
	add	x0, x0, 2560
	add	x0, x19, x0
	str	x0, [x1, 2448]
	bgt	.L705
	.p2align 2
.L703:
	ldr	w3, [x23, 4]
	add	w22, w22, 1
	cmp	w3, w22
	bhi	.L707
.L735:
	cmp	w3, w21
	bhi	.L708
	ldr	w0, [x26, 1092]
.L702:
	and	w0, w0, -3
	cmp	w0, 1
	bne	.L710
	ldr	w0, [x26, 1084]
	cmp	w0, 1
	beq	.L734
.L710:
	mov	w0, 1
.L699:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L705:
	mov	x1, x20
	mov	w0, 1
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w3, [x23, 4]
	cmp	w3, w22
	bhi	.L707
	b	.L735
.L733:
	add	x0, x19, 16384
	mov	w1, 0
	add	x0, x0, 2566
	.p2align 2
.L700:
	ldrb	w2, [x0]
	tbz	x2, 1, .L698
	ldrb	w2, [x0, 1]
	sub	w2, w2, #5
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L736
.L698:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L700
	ldr	x1, .LC158
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L708:
	ldr	x1, .LC162
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L734:
	sub	w0, w3, #1
	add	x1, x19, 16384
	add	x2, x19, 20480
	add	x1, x1, 2560
	add	x0, x24, x0, lsl 3
	add	x2, x2, 128
	add	x0, x0, 2440
	b	.L712
	.p2align 3
.L711:
	add	x1, x1, 104
	cmp	x2, x1
	beq	.L710
.L712:
	ldrb	w3, [x1, 6]
	tbz	x3, 1, .L711
	ldrb	w3, [x1, 7]
	sub	w3, w3, #5
	uxtb	w3, w3
	cmp	w3, 1
	bhi	.L711
	str	x1, [x0, 8]
	b	.L711
.L701:
	ldr	x2, .LC163
	mov	w4, 7
	ldr	x1, .LC165
	mov	w0, 1
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L736:
	sxtw	x1, w1
	mov	w0, 1
	lsl	x2, x1, 3
	sub	x2, x2, x1
	lsl	x2, x2, 1
	sub	x1, x2, x1
	lsl	x1, x1, 3
	add	x1, x1, 16384
	add	x1, x1, 2560
	add	x19, x19, x1
	str	x19, [x24, 2448]
	b	.L699
	.size	AVS2_SetupRefFrame, .-AVS2_SetupRefFrame
	.align	3
.LC158:
	.xword	.LC157
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC163:
	.xword	.LANCHOR1
	.align	3
.LC165:
	.xword	.LC164
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupHalConfig
	.type	AVS2_SetupHalConfig, %function
AVS2_SetupHalConfig:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 96
	add	x20, x21, 8192
	bl	_mcount
	ldr	x1, [x21, 40]
	add	x0, x20, 2584
	ldr	x22, [x20, 2448]
	ldr	w3, [x1, 632]
	strb	w3, [x19, 2]
	ldr	w3, [x1, 664]
	strb	w3, [x19, 4]
	ldr	w1, [x1, 684]
	strb	w1, [x19, 1]
	ldr	x2, [x20, 2440]
	ldr	w1, [x2, 60]
	str	w1, [x19, 92]
	ldr	w1, [x2, 88]
	str	w1, [x19, 260]
	ldr	w1, [x2, 92]
	str	w1, [x19, 264]
	ldr	w1, [x2, 84]
	str	w1, [x19, 268]
	ldr	w1, [x2, 96]
	str	w1, [x19, 272]
	ldr	w1, [x2, 100]
	str	w1, [x19, 96]
	ldr	w1, [x2, 68]
	str	w1, [x19, 276]
	ldr	w1, [x2, 72]
	str	w1, [x19, 280]
	ldr	w1, [x2, 76]
	str	w1, [x19, 284]
	ldr	w1, [x20, 2604]
	str	w1, [x19, 100]
	ldr	w1, [x20, 2612]
	str	w1, [x19, 104]
	ldrh	w1, [x20, 4996]
	str	w1, [x19, 108]
	ldrh	w1, [x20, 4998]
	str	w1, [x19, 112]
	ldr	w1, [x20, 5244]
	str	w1, [x19, 120]
	ldrb	w3, [x0, 2417]
	strb	w3, [x21, 96]
	ldr	w3, [x20, 5252]
	str	w3, [x19, 124]
	ldr	w3, [x20, 5248]
	str	w3, [x19, 128]
	ldr	w3, [x20, 5188]
	str	w3, [x19, 132]
	ldr	w0, [x20, 2600]
	cmp	w0, 1
	beq	.L758
	str	wzr, [x19, 136]
.L740:
	ldr	w1, [x20, 4984]
	add	x0, x20, 2584
	str	w1, [x19, 140]
	ldr	w1, [x20, 2776]
	str	w1, [x19, 144]
	ldr	w1, [x20, 2620]
	str	w1, [x19, 148]
	ldr	w1, [x20, 2780]
	str	w1, [x19, 152]
	ldr	w1, [x20, 2680]
	str	w1, [x19, 156]
	ldr	w1, [x20, 2688]
	str	w1, [x19, 160]
	ldr	w1, [x20, 2684]
	str	w1, [x19, 164]
	ldrb	w1, [x0, 2472]
	str	w1, [x19, 168]
	ldr	w1, [x20, 2772]
	str	w1, [x19, 172]
	ldr	w1, [x20, 5312]
	ldr	w4, [x20, 5316]
	ldr	w3, [x20, 5308]
	lsl	w1, w1, 1
	orr	w1, w1, w4, lsl 2
	orr	w1, w1, w3
	str	w1, [x19, 176]
	ldr	w1, [x20, 2788]
	str	w1, [x19, 180]
	ldr	w1, [x20, 2792]
	str	w1, [x19, 184]
	ldr	w1, [x20, 2664]
	str	w1, [x19, 116]
	ldr	w1, [x20, 2784]
	str	w1, [x19, 188]
	ldr	w0, [x20, 2668]
	str	w0, [x19, 192]
	ldr	w0, [x20, 5280]
	str	w0, [x19, 208]
	ldr	w0, [x20, 5296]
	str	w0, [x19, 196]
	ldr	w0, [x20, 5292]
	str	w0, [x19, 200]
	ldr	w0, [x20, 5288]
	str	w0, [x19, 204]
	ldr	w0, [x20, 5276]
	str	w0, [x19, 212]
	ldr	w0, [x20, 5272]
	str	w0, [x19, 216]
	ldr	w0, [x20, 5268]
	str	w0, [x19, 220]
	ldr	w0, [x20, 5264]
	str	w0, [x19, 224]
	ldrb	w0, [x2, 12]
	str	w0, [x19, 228]
	ldrb	w0, [x2, 13]
	str	w0, [x19, 232]
	ldrb	w0, [x2, 14]
	str	w0, [x19, 236]
	ldr	w0, [x20, 5192]
	cbnz	w0, .L741
	add	x4, x20, 2456
	mov	x0, x21
	mov	x1, x22
	mov	w3, 7
	b	.L744
	.p2align 3
.L759:
	ldr	x1, [x4], 8
.L744:
	subs	w3, w3, #1
	cbz	x1, .L742
	ldrb	w5, [x1, 12]
	str	w5, [x0, 412]
	ldrb	w5, [x1, 13]
	str	w5, [x0, 440]
	ldrb	w5, [x1, 14]
	str	w5, [x0, 468]
	ldr	w1, [x1, 60]
	str	w1, [x0, 496]
.L742:
	add	x0, x0, 4
	bne	.L759
	ldr	w0, [x2, 80]
	str	w0, [x19, 240]
	cbz	x22, .L745
.L761:
	ldr	w0, [x22, 80]
	str	w0, [x19, 244]
.L746:
	ldr	x23, .LC166
	add	x24, x20, 2584
	mov	x2, 576
	add	x1, x24, 2804
	add	x0, x21, 588
	ldr	x3, [x23, 104]
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 72
	add	x1, x24, 3380
	add	x0, x21, 1164
	blr	x3
	ldr	w0, [x20, 5192]
	cbz	w0, .L760
	ldrb	w0, [x24, 2473]
	str	w0, [x19, 248]
	ldr	w0, [x24, 212]
	str	w0, [x19, 252]
	ldr	w0, [x20, 5180]
	str	w0, [x19, 256]
.L748:
	ldr	x3, [x23, 96]
	mov	x2, 28
	mov	w1, 0
	add	x0, x21, 384
	blr	x3
.L749:
	add	x20, x20, 2584
	ldr	x3, [x23, 104]
	add	x1, x20, 2486
	mov	x2, 16
	add	x0, x21, 101
	blr	x3
	ldr	x3, [x23, 104]
	add	x1, x20, 2502
	mov	x2, 64
	add	x0, x21, 117
	blr	x3
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L741:
	ldrb	w0, [x2, 12]
	str	w0, [x19, 316]
	ldrb	w0, [x2, 13]
	str	w0, [x19, 344]
	ldrb	w0, [x2, 14]
	str	w0, [x19, 372]
	ldr	w0, [x2, 60]
	str	w0, [x19, 400]
	ldr	w0, [x2, 80]
	str	w0, [x19, 240]
	cbnz	x22, .L761
.L745:
	str	wzr, [x19, 244]
	b	.L746
	.p2align 3
.L760:
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2276
	add	x0, x21, 524
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2304
	add	x0, x21, 540
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2290
	add	x0, x21, 556
	blr	x3
	ldr	x3, [x23, 104]
	add	x1, x20, 2318
	mov	x2, 14
	add	x0, x21, 572
	blr	x3
	strh	wzr, [x19, 442]
	strh	wzr, [x19, 458]
	strh	wzr, [x19, 474]
	strh	wzr, [x19, 490]
	ldrb	w1, [x24, 2473]
	ldr	w0, [x20, 5192]
	str	w1, [x19, 248]
	ldr	w1, [x24, 212]
	str	w1, [x19, 252]
	ldr	w1, [x20, 5180]
	str	w1, [x19, 256]
	cbnz	w0, .L748
	ldrb	w0, [x22, 46]
	str	w0, [x19, 288]
	ldrb	w0, [x22, 47]
	str	w0, [x19, 292]
	ldrb	w0, [x22, 48]
	str	w0, [x19, 296]
	ldrb	w0, [x22, 49]
	str	w0, [x19, 300]
	ldrb	w0, [x22, 50]
	str	w0, [x19, 304]
	ldrb	w0, [x22, 51]
	str	w0, [x19, 308]
	ldrb	w0, [x22, 52]
	str	w0, [x19, 312]
	b	.L749
	.p2align 3
.L758:
	mov	w0, 2
	cmp	w1, 1
	csel	w1, w1, w0, eq
	str	w1, [x19, 136]
	b	.L740
	.size	AVS2_SetupHalConfig, .-AVS2_SetupHalConfig
	.align	3
.LC166:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CalDistance
	.type	AVS2_CalDistance, %function
AVS2_CalDistance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x5, x19, 8192
	add	x1, x5, 2264
	ldr	x0, [x1, 184]
	cbz	x0, .L788
	add	x7, x19, 12288
	ldrb	w3, [x7, 960]
	sub	w0, w3, #1
	uxtb	w0, w0
	cmp	w0, 6
	bhi	.L764
	ldr	x3, [x1, 176]
	mov	w2, 1
	mov	w1, 16384
	add	x6, x3, 18
	add	x8, x3, 32
	mov	x0, x6
.L767:
	strh	w2, [x0]
	add	x0, x0, 2
	strh	w1, [x0, 12]
	cmp	x0, x8
	bne	.L767
	ldrb	w2, [x7, 960]
	add	x0, x7, 960
	cbz	w2, .L768
	ldrsh	w10, [x3, 2]
	mov	w4, 0
	add	x9, x5, 2264
	mov	w12, 1
	mov	w11, 16384
	b	.L773
	.p2align 3
.L790:
	ldrsh	w0, [x3, 8]
	add	x13, x3, x2, lsl 1
	ldrsh	w1, [x1, 8]
	sub	w1, w0, w1
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w0, w0, 23
	add	w1, w1, w0
	and	w1, w1, 511
	sub	w0, w1, w0
	mov	w1, 16384
	sxth	w0, w0
	strh	w0, [x14, 18]
	cbz	w0, .L771
.L791:
	sdiv	w0, w11, w0
	add	x2, x2, 16
	add	w4, w4, 1
	sxth	w1, w0
	strh	w1, [x3, x2, lsl 1]
	ldrb	w2, [x7, 960]
	cmp	w2, w4
	bls	.L789
.L773:
	uxtw	x2, w4
	add	x0, x3, x2
	add	x1, x9, x2, lsl 3
	add	x14, x3, x2, lsl 1
	ldr	x1, [x1, 184]
	ldrb	w13, [x1, 12]
	strb	w13, [x0, 46]
	ldrsh	w0, [x1, 2]
	cmp	w0, w10
	blt	.L790
	ldrsh	w0, [x1, 8]
	add	x13, x3, x2, lsl 1
	ldrsh	w1, [x3, 8]
	sub	w1, w0, w1
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w0, w0, 23
	add	w1, w1, w0
	and	w1, w1, 511
	sub	w0, w1, w0
	mov	w1, 16384
	sxth	w0, w0
	strh	w0, [x14, 18]
	cbnz	w0, .L791
.L771:
	add	x2, x2, 16
	strh	w12, [x13, 18]
	add	w4, w4, 1
	strh	w1, [x3, x2, lsl 1]
	ldrb	w2, [x7, 960]
	cmp	w2, w4
	bhi	.L773
.L789:
	ldr	w0, [x7, 1084]
	ldr	x1, [x5, 2448]
	cmp	w0, 1
	beq	.L792
.L774:
	add	x0, x5, 2276
	add	x1, x1, 18
	.p2align 2
.L778:
	ldrsh	w2, [x6]
	add	x1, x1, 2
	strh	w2, [x0]
	add	x0, x0, 2
	add	x6, x6, 2
	ldrsh	w2, [x1, -2]
	cmp	x6, x8
	strh	w2, [x0, 26]
	ldrsh	w2, [x6, 12]
	strh	w2, [x0, 12]
	ldrsh	w2, [x1, 12]
	strh	w2, [x0, 40]
	bne	.L778
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L788:
	add	x19, x19, 12288
	ldrb	w3, [x19, 960]
	.p2align 2
.L764:
	ldr	x2, .LC167
	mov	w4, 7
	ldr	x1, .LC169
	mov	w0, 1
	add	x2, x2, 472
	bl	dprint_vfmw
.L762:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L792:
	cmp	w2, 1
	beq	.L793
.L775:
	add	x0, x5, 2276
	add	x1, x1, 18
	.p2align 2
.L777:
	ldrsh	w3, [x6]
	add	x1, x1, 2
	strh	w3, [x0]
	add	x0, x0, 2
	add	x6, x6, 2
	ldrsh	w3, [x1, -2]
	cmp	x6, x8
	strh	w3, [x0, 26]
	ldrsh	w3, [x6, 12]
	strh	w3, [x0, 12]
	ldrsh	w3, [x1, 12]
	strh	w3, [x0, 40]
	bne	.L777
	add	x0, x19, x2, uxtb 1
	mov	w1, 16384
	add	x0, x0, 8192
	mov	w2, 1
	strh	w1, [x0, 2288]
	strh	w2, [x0, 2274]
	b	.L762
.L768:
	ldr	w0, [x0, 124]
	ldr	x1, [x5, 2448]
	cmp	w0, 1
	bne	.L774
	b	.L775
.L793:
	add	x1, x5, 2276
	add	x0, x5, 2290
	mov	w3, 16384
	.p2align 2
.L776:
	strh	w2, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 26]
	strh	w3, [x1, 12]
	strh	w3, [x1, 40]
	cmp	x1, x0
	bne	.L776
	b	.L762
	.size	AVS2_CalDistance, .-AVS2_CalDistance
	.align	3
.LC167:
	.xword	.LANCHOR1
	.align	3
.LC169:
	.xword	.LC168
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetImgFormat
	.type	AVS2_SetImgFormat, %function
AVS2_SetImgFormat:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 8192
	bl	_mcount
	ldr	w0, [x20, 2596]
	ldr	w24, [x20, 5008]
	cmp	w0, 1
	ldr	w26, [x20, 5188]
	beq	.L801
	ldr	w0, [x20, 5228]
	cmp	w0, 1
	cset	w23, ne
.L795:
	ldr	w0, [x20, 2632]
	mov	w27, 0
	ldr	w25, [x20, 5236]
	sub	w0, w0, #1
	cmp	w0, 3
	bhi	.L796
	ldr	x1, .LC170
	add	x1, x1, 496
	ldr	w27, [x1, w0, uxtw 2]
.L796:
	add	x22, x20, 2264
	ldr	x1, [x22, 176]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 56]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L804
	ldr	w2, [x0, 64]
	mov	w1, w27
	bfi	w2, w27, 14, 3
	str	w2, [x0, 64]
	lsr	w3, w2, 8
	bfi	w2, w24, 5, 3
	bfi	w3, w25, 4, 2
	and	w2, w2, -29
	orr	w3, w3, 12
	bfi	w2, w26, 0, 2
	bfi	w3, w23, 0, 2
	strb	w2, [x0, 64]
	strb	w3, [x0, 65]
	ldrb	w2, [x0, 66]
	ldr	x3, [x22, 176]
	ldrb	w3, [x3, 15]
	bfi	w2, w3, 1, 1
	strb	w2, [x0, 66]
	ldr	w2, [x22, 8]
	str	w2, [x0, 152]
	stp	w26, w26, [x0, 56]
	bl	SetAspectRatio
	ldr	x1, [x22, 176]
	ldrb	w1, [x1, 16]
	str	w1, [x19, 120]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 636]
	str	w1, [x19, 124]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 640]
	str	w1, [x19, 128]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 644]
	str	w1, [x19, 132]
	ldr	w1, [x20, 2604]
	str	w1, [x19, 68]
	ldr	w1, [x20, 2612]
	str	w1, [x19, 72]
	ldr	w2, [x20, 2608]
	str	w2, [x19, 76]
	ldr	w0, [x20, 2616]
	str	w0, [x19, 80]
	ldr	w0, [x20, 5004]
	str	w0, [x19, 108]
	ldr	x0, [x21, 40]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L805
.L799:
	mov	w0, 18
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 8
	ldr	w3, [x20, 5232]
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
.L801:
	mov	w23, 0
	b	.L795
	.p2align 3
.L805:
	ldr	w3, [x19, 112]
	add	w1, w1, 15
	lsr	w0, w1, 4
	ldr	w2, [x19, 36]
	lsl	w1, w3, 4
	ldr	x4, [x19, 504]
	add	w5, w3, w2
	mul	w1, w0, w1
	add	w0, w1, w2
	str	w0, [x19, 40]
	add	w3, w3, w0
	add	x1, x4, x1, sxtw
	stp	w2, w0, [x19, 20]
	stp	w5, w3, [x19, 28]
	str	x1, [x19, 512]
	b	.L799
	.p2align 3
.L804:
	ldr	x1, .LC172
	mov	w2, 3053
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	AVS2_SetImgFormat, .-AVS2_SetImgFormat
	.align	3
.LC170:
	.xword	.LANCHOR1
	.align	3
.LC172:
	.xword	.LC171
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SimpleDirectProcess
	.type	AVS2_SimpleDirectProcess, %function
AVS2_SimpleDirectProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x20, 10632]
	mov	w1, 1
	ldrb	w0, [x19, 7]
	strb	w1, [x19, 4]
	cmp	w0, 6
	beq	.L809
	mov	x1, x19
	mov	x0, x20
	bl	AVS2_OutputOneFrame
.L808:
	strb	wzr, [x19, 5]
	mov	w2, 0
	ldr	w1, [x19, 56]
	ldr	w0, [x20, 4]
	bl	FSP_SetRef
	strb	wzr, [x19, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L809:
	ldr	w1, [x19, 56]
	mov	w2, 0
	ldr	w0, [x20, 4]
	bl	FSP_SetDisplay
	b	.L808
	.size	AVS2_SimpleDirectProcess, .-AVS2_SimpleDirectProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DispOrderProcess
	.type	AVS2_DispOrderProcess, %function
AVS2_DispOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 8192
	add	x1, x1, 2264
	ldr	x0, [x1, 176]
	ldrb	w2, [x0, 7]
	cmp	w2, 6
	beq	.L813
	ldrb	w2, [x19, 1]
	cbnz	w2, .L812
	ldr	x2, [x19, 40]
	ldr	w2, [x2, 12]
	cbz	w2, .L814
.L812:
	mov	x0, x19
	bl	AVS2_DisplayFrameInPOI
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L814:
	mov	w20, 1
	strb	w20, [x0, 4]
	mov	x0, x19
	ldr	x1, [x1, 176]
	bl	AVS2_OutputOneFrame
	strb	w20, [x19, 1]
	mov	x0, x19
	bl	AVS2_DisplayFrameInPOI
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L813:
	mov	w2, 1
	strb	w2, [x0, 4]
	mov	w2, 0
	ldr	x1, [x1, 176]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 56]
	bl	FSP_SetDisplay
	b	.L812
	.size	AVS2_DispOrderProcess, .-AVS2_DispOrderProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DecOrderProcess
	.type	AVS2_DecOrderProcess, %function
AVS2_DecOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 10632]
	mov	w2, 1
	ldrb	w0, [x1, 7]
	strb	w2, [x1, 4]
	cmp	w0, 6
	beq	.L818
	mov	x0, x19
	bl	AVS2_OutputOneFrame
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L818:
	ldr	w0, [x19, 4]
	mov	w2, 0
	ldr	w1, [x1, 56]
	bl	FSP_SetDisplay
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DecOrderProcess, .-AVS2_DecOrderProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateFrameBuf
	.type	AVS2_UpdateFrameBuf, %function
AVS2_UpdateFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 13380]
	sub	w0, w0, #5
	cmp	w0, 1
	bls	.L821
	mov	x0, x19
	bl	AVS2_UpdateRefBuf
	mov	x0, x19
	bl	AVS2_RefreshBuf
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L821:
	mov	x0, x19
	bl	AVS2_UpdateSceneBuf.part.7
	mov	x0, x19
	bl	AVS2_UpdateRefBuf
	mov	x0, x19
	bl	AVS2_RefreshBuf
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_UpdateFrameBuf, .-AVS2_UpdateFrameBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_FlushFrameInDpb
	.type	AVS2_FlushFrameInDpb, %function
AVS2_FlushFrameInDpb:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	add	x19, x24, 16384
	mov	w23, 0
	bl	_mcount
	add	x0, x19, 2564
	mov	w1, 0
	.p2align 2
.L824:
	ldrb	w2, [x0]
	cbnz	w2, .L823
	sub	x2, x29, #3984
	add	w3, w23, 1
	add	x4, x2, x23, sxtw
	ldrb	w2, [x0, 2]
	cbz	w2, .L823
	strb	w1, [x4, 4080]
	uxtb	w23, w3
.L823:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L824
	cbz	w23, .L825
	ldr	x21, .LC174
	mov	w25, 0
	mov	w26, 0
	mov	w20, 32767
	mov	w22, 1
	.p2align 2
.L826:
	cbz	w23, .L829
	mov	x1, 0
	mov	w5, 32767
	add	x4, x29, 96
	.p2align 2
.L828:
	ldrb	w2, [x4, x1]
	add	x1, x1, 1
	lsl	x0, x2, 3
	mov	x3, x2
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x24, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w2, [x0, 2564]
	cbnz	w2, .L827
	ldrsh	w0, [x0, 2562]
	cmp	w0, w5
	bgt	.L827
	mov	w5, w0
	mov	w26, w3
.L827:
	cmp	w23, w1
	bgt	.L828
	cmp	w5, w20
	beq	.L829
	sxtw	x2, w26
	mov	x0, x24
	lsl	x1, x2, 3
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	lsl	x1, x1, 3
	add	x27, x24, x1
	add	x1, x1, 16384
	add	x27, x27, 16384
	add	x1, x1, 2560
	add	x1, x24, x1
	strb	w22, [x27, 2564]
	bl	AVS2_OutputOneFrame
	ldrsh	w2, [x27, 2562]
	mov	x1, x21
	mov	w0, 13
	bl	dprint_vfmw
.L829:
	add	w25, w25, 1
	uxtb	w25, w25
	cmp	w23, w25
	bne	.L826
.L825:
	add	x0, x24, 20480
	add	x19, x19, 2566
	add	x0, x0, 134
	b	.L832
	.p2align 3
.L831:
	add	x19, x19, 104
	cmp	x0, x19
	beq	.L843
.L832:
	ldrb	w1, [x19, -2]
	cmp	w1, 1
	bne	.L831
	ldrb	w1, [x19, -1]
	cbnz	w1, .L831
	ldrb	w1, [x19]
	add	x19, x19, 104
	and	w1, w1, 2
	strb	w1, [x19, -104]
	cmp	x0, x19
	bne	.L832
.L843:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	AVS2_FlushFrameInDpb, .-AVS2_FlushFrameInDpb
	.align	3
.LC174:
	.xword	.LC138
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_FlushPreSizeImg
	.type	AVS2_FlushPreSizeImg, %function
AVS2_FlushPreSizeImg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x3, x29, 48
	ldr	w0, [x19, 4]
	add	x2, x29, 40
	add	x1, x29, 36
	stp	wzr, wzr, [x29, 36]
	str	wzr, [x3, -4]!
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 764]
	cmp	w0, 1
	beq	.L849
	mov	w0, 1
.L845:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L849:
	ldr	w1, [x29, 44]
	mov	w0, 0
	cmp	w1, wzr
	bgt	.L845
	ldr	w1, [x29, 40]
	cmp	w1, 32
	bgt	.L845
	ldr	x0, [x19, 48]
	cmp	x0, xzr
	cset	w0, eq
	b	.L845
	.size	AVS2_FlushPreSizeImg, .-AVS2_FlushPreSizeImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ArrangeFrameBuf
	.type	AVS2_ArrangeFrameBuf, %function
AVS2_ArrangeFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 20]
	cbz	w0, .L851
	mov	x0, x19
	bl	AVS2_FlushPreSizeImg
	cbnz	w0, .L852
.L854:
	mov	w0, 3
.L853:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L852:
	mov	x0, x19
	bl	AVS2_ClearDpb
	add	x1, x19, 16384
	ldr	w0, [x19, 4]
	add	x1, x1, 1776
	bl	FSP_ClearNotInVoQueue
	str	wzr, [x19, 20]
	.p2align 2
.L851:
	mov	x0, x19
	str	wzr, [x19, 24]
	bl	AVS2_AllocateVHB
	cmp	w0, 3
	mov	w1, w0
	beq	.L854
	mov	w0, 1
	cbnz	w1, .L853
	ldr	x1, .LC176
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_ArrangeFrameBuf, .-AVS2_ArrangeFrameBuf
	.align	3
.LC176:
	.xword	.LC175
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ParseHeader
	.type	AVS2_ParseHeader, %function
AVS2_ParseHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 56
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	str	wzr, [x19, 8]
	bl	BsShow
	uxtb	w21, w0
	sub	w0, w21, #176
	cmp	w0, 78
	bls	.L902
.L863:
	cmp	w21, 143
	bhi	.L876
	ldr	w1, [x19, 12]
	mov	w0, 327680
	and	w0, w1, w0
	cmp	w0, 327680
	beq	.L903
.L876:
	mov	x0, x19
	mov	w20, 0
	bl	AVS2_ClearPacket
.L872:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L902:
	ldr	x1, .LC177
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx865
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx865:
	.section	.rodata
	.align	0
	.align	2
.L865:
	.byte	(.L864 - .Lrtx865) / 4
	.byte	(.L866 - .Lrtx865) / 4
	.byte	(.L867 - .Lrtx865) / 4
	.byte	(.L868 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L869 - .Lrtx865) / 4
	.byte	(.L868 - .Lrtx865) / 4
	.byte	(.L866 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L863 - .Lrtx865) / 4
	.byte	(.L870 - .Lrtx865) / 4
	.text
	.p2align 3
.L864:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L900
	ldr	w0, [x19, 28]
	cmn	w0, #1
	mov	x0, x19
	beq	.L904
	bl	AVS2_FlushFrameInDpb
.L874:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_SequenceHeader
	mov	x0, x19
	bl	AVS2_ClearPacket
	b	.L872
	.p2align 3
.L866:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L900
	cmp	w21, 177
	beq	.L905
	ldr	x1, .LC182
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x20, .LC178
.L885:
	ldr	w0, [x20]
	tbnz	x0, 0, .L901
	mov	x0, x19
	bl	AVS2_ClearDpb
.L901:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_ClearPacket
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L867:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_User_Data
	mov	x0, x19
	bl	AVS2_ClearPacket
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L868:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L900
	tbz	x0, 16, .L876
	ldr	w0, [x19, 20]
	cmp	w0, 1
	beq	.L877
	ldr	w0, [x19, 24]
	cbnz	w0, .L878
.L877:
	mov	x0, x19
	bl	AVS2_ArrangeFrameBuf
	cmp	w0, 1
	mov	w20, w0
	beq	.L878
	cmp	w0, 3
	bne	.L899
	mov	w0, 1
	str	w0, [x19, 8]
	b	.L872
	.p2align 3
.L869:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_Extension
	mov	x0, x19
	bl	AVS2_ClearPacket
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L870:
	mov	w1, 32
	mov	x0, x20
	bl	BsSkip
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	ldr	w1, [x19, 12]
	tbnz	x1, 15, .L906
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L876
	mov	w1, -1
	mov	w0, 1
	str	w1, [x19, 28]
	strb	w0, [x19]
	b	.L901
	.p2align 3
.L900:
	mov	w20, 1
	orr	w0, w0, 16384
	stp	w20, w0, [x19, 8]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L906:
	mov	w20, 1
	orr	w1, w1, 16384
	stp	w20, w1, [x19, 8]
	b	.L872
	.p2align 3
.L905:
	ldr	x20, .LC178
	ldr	w0, [x20]
	tbz	x0, 0, .L907
.L884:
	ldr	x1, .LC180
	mov	w0, 1
	bl	dprint_vfmw
	b	.L885
	.p2align 3
.L878:
	ldr	w0, [x19, 28]
	cmp	w21, 179
	add	w0, w0, 1
	str	w0, [x19, 28]
	mov	x0, x19
	beq	.L908
	bl	AVS2_InterPictureHeader
	b	.L901
	.p2align 3
.L904:
	bl	AVS2_ClearDpb
	b	.L874
	.p2align 3
.L903:
	mov	x0, x19
	bl	AVS2_WriteSliceMsg
	mov	w20, w0
	cbnz	w0, .L872
.L899:
	mov	x0, x19
	bl	AVS2_ClearPacket
	b	.L872
	.p2align 3
.L907:
	mov	x0, x19
	bl	AVS2_FlushFrameInDpb
	b	.L884
	.p2align 3
.L908:
	bl	AVS2_IntraPictureHeader
	b	.L901
	.size	AVS2_ParseHeader, .-AVS2_ParseHeader
	.align	3
.LC177:
	.xword	.L865
	.align	3
.LC178:
	.xword	g_StandardObedience
	.align	3
.LC180:
	.xword	.LC179
	.align	3
.LC182:
	.xword	.LC181
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DecodeArbiter
	.type	AVS2_DecodeArbiter, %function
AVS2_DecodeArbiter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 49152
	ldr	w20, [x19, 12]
	movk	w0, 0x5, lsl 16
	and	w0, w20, w0
	cmp	w0, 376832
	beq	.L912
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L912:
	add	x0, x19, 8192
	add	x1, x19, 12288
	mov	x2, 3692
	add	x1, x1, 2180
	add	x0, x0, 2584
	bl	memcpy
	mov	w0, 16383
	movk	w0, 0xfffb, lsl 16
	and	w20, w20, w0
	str	w20, [x19, 12]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DecodeArbiter, .-AVS2_DecodeArbiter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PrepareDecode
	.type	AVS2_PrepareDecode, %function
AVS2_PrepareDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_SetPicInfo
	ldr	w3, [x19, 1236]
	sub	w0, w3, #1
	cmp	w0, 255
	bhi	.L928
	mov	x0, x19
	bl	AVS2_VarifyDecMode
	cbnz	w0, .L929
.L927:
	mov	w0, 0
.L915:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L929:
	mov	x0, x19
	bl	AVS2_SetupFrameBuf
	cbz	w0, .L927
	ldr	w0, [x19, 13384]
	cbnz	w0, .L918
	mov	x0, x19
	bl	AVS2_SetupRefFrame
	cbz	w0, .L920
	mov	x0, x19
	bl	AVS2_CalDistance
.L918:
	mov	x0, x19
	bl	AVS2_SetupHalConfig
	cbz	w0, .L920
	mov	w0, 1
	b	.L915
	.p2align 3
.L928:
	ldr	x2, .LC183
	mov	w0, 1
	ldr	x1, .LC185
	add	x2, x2, 512
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L920:
	mov	x0, x19
	bl	AVS2_ReleaseFrameBuf
	b	.L927
	.size	AVS2_PrepareDecode, .-AVS2_PrepareDecode
	.align	3
.LC183:
	.xword	.LANCHOR1
	.align	3
.LC185:
	.xword	.LC184
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_StartDecode
	.type	AVS2_StartDecode, %function
AVS2_StartDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 40]
	add	x0, x19, 96
	str	x0, [x19, 48]
	ldr	w2, [x1, 632]
	strb	w2, [x19, 98]
	ldr	w1, [x1, 684]
	strb	w1, [x19, 97]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_StartDecode, .-AVS2_StartDecode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PostProcess
	.type	AVS2_PostProcess, %function
AVS2_PostProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_SetImgFormat
	ldr	x0, [x19, 40]
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L938
	ldr	w2, [x0, 24]
	cbz	w2, .L939
	sub	w0, w2, #1
	cmp	w0, 1
	bls	.L937
	ldr	x1, .LC187
	mov	w0, 1
	bl	dprint_vfmw
.L937:
	mov	x0, x19
	bl	AVS2_DecOrderProcess
.L935:
	mov	x0, x19
	bl	AVS2_UpdateFrameBuf
.L931:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L939:
	mov	x0, x19
	bl	AVS2_DispOrderProcess
	b	.L935
	.p2align 3
.L938:
	mov	x0, x19
	bl	AVS2_SimpleDirectProcess
	b	.L931
	.size	AVS2_PostProcess, .-AVS2_PostProcess
	.align	3
.LC187:
	.xword	.LC186
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Init
	.type	AVS2DEC_Init, %function
AVS2DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	add	x20, x19, 16384
	bl	_mcount
	ldr	x3, .LC188
	mov	x2, 20608
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x20, 2376]
	ldr	x3, [x3, 96]
	blr	x3
	str	w22, [x20, 2376]
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 4]
	beq	.L943
	add	x0, x20, 1776
	bl	ResetVoQueue
	str	x21, [x19, 40]
	str	wzr, [x21, 928]
	mov	w1, -1
	mov	w0, 1
	str	w1, [x19, 28]
.L942:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L943:
	ldr	x2, .LC189
	mov	w0, 0
	ldr	x1, .LC191
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -20
	b	.L942
	.size	AVS2DEC_Init, .-AVS2DEC_Init
	.align	3
.LC188:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC189:
	.xword	.LANCHOR1
	.align	3
.LC191:
	.xword	.LC190
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Destroy
	.type	AVS2DEC_Destroy, %function
AVS2DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	AVS2DEC_Destroy, .-AVS2DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_GetImageBuffer
	.type	AVS2DEC_GetImageBuffer, %function
AVS2DEC_GetImageBuffer:
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
	beq	.L946
	ldr	w0, [x20, 4]
	mov	w19, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L951
.L946:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L951:
	add	x1, x20, 16384
	ldr	w0, [x20, 4]
	add	x1, x1, 1776
	bl	FSP_ClearNotInVoQueue
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_GetImageBuffer, .-AVS2DEC_GetImageBuffer
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Decode
	.type	AVS2DEC_Decode, %function
AVS2DEC_Decode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x20, 20]
	add	x0, x19, 56
	ldr	x1, [x20]
	bl	BsInit
	ldr	x3, .LC192
	add	x0, x19, 16384
	mov	x2, 176
	mov	x1, x20
	add	x0, x0, 2384
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w0, [x19, 12]
	str	w0, [x19, 16]
	mov	x0, x19
	bl	AVS2_ParseHeader
	cmp	w0, 3
	beq	.L959
	mov	w20, 0
	cbz	w0, .L954
	mov	w0, 49152
	ldr	w21, [x19, 12]
	movk	w0, 0x5, lsl 16
	and	w0, w21, w0
	cmp	w0, 376832
	beq	.L960
.L954:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L960:
	add	x0, x19, 8192
	add	x1, x19, 12288
	mov	x2, 3692
	add	x1, x1, 2180
	add	x0, x0, 2584
	bl	memcpy
	mov	w0, 16383
	movk	w0, 0xfffb, lsl 16
	and	w21, w21, w0
	mov	x0, x19
	str	w21, [x19, 12]
	bl	AVS2_PrepareDecode
	cbz	w0, .L961
	ldr	x1, [x19, 40]
	add	x0, x19, 96
	str	x0, [x19, 48]
	mov	w20, 1
	mov	w0, w20
	ldr	w2, [x1, 632]
	strb	w2, [x19, 98]
	ldr	w1, [x1, 684]
	strb	w1, [x19, 97]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L959:
	ldr	w1, [x19, 16]
	mov	w20, w0
	str	w1, [x19, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L961:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	b	.L954
	.size	AVS2DEC_Decode, .-AVS2DEC_Decode
	.align	3
.LC192:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_VDMPostProc
	.type	AVS2DEC_VDMPostProc, %function
AVS2DEC_VDMPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w22, w2
	mov	w20, w3
	bl	_mcount
	ldr	x0, [x19, 10632]
	ldrb	w2, [x19, 99]
	strb	w2, [x0, 15]
	ldrb	w1, [x19, 98]
	strb	w1, [x0, 16]
	cbz	w22, .L963
	ldr	x3, .LC193
	sbfiz	x20, x20, 6, 32
	add	x20, x3, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L971
	cmp	w0, 1
	beq	.L963
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 4]
	cmp	w0, w21
	mov	x0, x19
	blt	.L972
.L967:
	bl	AVS2_PostProcess
	mov	w0, 1
.L965:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L963:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 4]
	cmp	w0, w21
	mov	x0, x19
	bge	.L967
.L972:
	bl	AVS2_ClearPicSlice
	mov	x0, x19
	bl	AVS2_ReleaseFrameBuf
	ldr	x3, [x19, 40]
	mov	w2, w21
	ldr	x1, .LC195
	mov	w0, 1
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L971:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	mov	w0, 1
	b	.L965
	.size	AVS2DEC_VDMPostProc, .-AVS2DEC_VDMPostProc
	.align	3
.LC193:
	.xword	g_VdmDrvParam
	.align	3
.LC195:
	.xword	.LC194
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_RecycleImage
	.type	AVS2DEC_RecycleImage, %function
AVS2DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	w0, [x20, 4]
	mov	w1, w19
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x20, 4]
	mov	w1, w19
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L974
	ldr	w0, [x20, 4]
	ldr	x1, [x19, 544]
	bl	FreeUsdByDec
	str	xzr, [x19, 544]
	ldr	x1, [x19, 552]
	ldr	w0, [x20, 4]
	bl	FreeUsdByDec
	str	xzr, [x19, 552]
.L974:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_RecycleImage, .-AVS2DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_GetRemainImg
	.type	AVS2DEC_GetRemainImg, %function
AVS2DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_FlushFrameInDpb
	add	x0, x19, 16384
	add	x0, x0, 1776
	bl	GetVoLastImageID
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_GetRemainImg, .-AVS2DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_ClearCurPic
	.type	AVS2DEC_ClearCurPic, %function
AVS2DEC_ClearCurPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	mov	x0, x19
	bl	AVS2_ReleaseFrameBuf
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_ClearCurPic, .-AVS2DEC_ClearCurPic
	.global	AVS2_WqM4x4IdxModel2
	.global	AVS2_WqM4x4IdxModel1
	.global	AVS2_WqM4x4IdxModel0
	.global	AVS2_WqM8x8IdxModel2
	.global	AVS2_WqM8x8IdxModel1
	.global	AVS2_WqM8x8IdxModel0
	.global	AVS2_WQM_8x8Default
	.global	AVS2_WQM_4x4Default
	.global	AVS2_WeightQuantParamBase2
	.global	AVS2_WeightQuantParamBase1
	.global	AVS2_WeightQuantParamDefault
	.global	Avs2_AlfRegionTable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	CSWTCH.29, %object
	.size	CSWTCH.29, 56
CSWTCH.29:
	.xword	.LC196
	.xword	.LC197
	.xword	.LC198
	.xword	.LC199
	.xword	.LC200
	.xword	.LC201
	.xword	.LC202
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.12016, %object
	.size	__func__.12016, 15
__func__.12016:
	.string	"AVS2_User_Data"
	.zero	1
	.type	AVS2_WqM8x8IdxModel0, %object
	.size	AVS2_WqM8x8IdxModel0, 64
AVS2_WqM8x8IdxModel0:
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
	.type	AVS2_WqM4x4IdxModel0, %object
	.size	AVS2_WqM4x4IdxModel0, 16
AVS2_WqM4x4IdxModel0:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	2
	.byte	1
	.byte	5
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel1, %object
	.size	AVS2_WqM8x8IdxModel1, 64
AVS2_WqM8x8IdxModel1:
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
	.type	AVS2_WqM4x4IdxModel1, %object
	.size	AVS2_WqM4x4IdxModel1, 16
AVS2_WqM4x4IdxModel1:
	.byte	0
	.byte	4
	.byte	4
	.byte	5
	.byte	3
	.byte	2
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel2, %object
	.size	AVS2_WqM8x8IdxModel2, 64
AVS2_WqM8x8IdxModel2:
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
	.type	AVS2_WqM4x4IdxModel2, %object
	.size	AVS2_WqM4x4IdxModel2, 16
AVS2_WqM4x4IdxModel2:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WeightQuantParamDefault, %object
	.size	AVS2_WeightQuantParamDefault, 6
AVS2_WeightQuantParamDefault:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.zero	2
	.type	AVS2_WeightQuantParamBase1, %object
	.size	AVS2_WeightQuantParamBase1, 6
AVS2_WeightQuantParamBase1:
	.byte	67
	.byte	71
	.byte	71
	.byte	80
	.byte	80
	.byte	106
	.zero	2
	.type	AVS2_WeightQuantParamBase2, %object
	.size	AVS2_WeightQuantParamBase2, 6
AVS2_WeightQuantParamBase2:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.zero	2
	.type	AVS2_WQM_4x4Default, %object
	.size	AVS2_WQM_4x4Default, 16
AVS2_WQM_4x4Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	64
	.byte	68
	.byte	76
	.byte	80
	.byte	72
	.byte	76
	.byte	84
	.byte	96
	.type	AVS2_WQM_8x8Default, %object
	.size	AVS2_WQM_8x8Default, 64
AVS2_WQM_8x8Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	68
	.byte	72
	.byte	76
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	84
	.byte	92
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	80
	.byte	88
	.byte	100
	.byte	64
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	100
	.byte	112
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	112
	.byte	-128
	.byte	76
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	116
	.byte	-124
	.byte	-104
	.byte	96
	.byte	100
	.byte	104
	.byte	116
	.byte	124
	.byte	-116
	.byte	-92
	.byte	-68
	.byte	104
	.byte	108
	.byte	116
	.byte	-128
	.byte	-104
	.byte	-84
	.byte	-64
	.byte	-40
	.type	Avs2_AlfRegionTable, %object
	.size	Avs2_AlfRegionTable, 16
Avs2_AlfRegionTable:
	.byte	0
	.byte	1
	.byte	4
	.byte	5
	.byte	15
	.byte	2
	.byte	3
	.byte	6
	.byte	14
	.byte	11
	.byte	10
	.byte	7
	.byte	13
	.byte	12
	.byte	9
	.byte	8
	.type	__func__.12163, %object
	.size	__func__.12163, 24
__func__.12163:
	.string	"AVS2_IntraPictureHeader"
	.type	__func__.12181, %object
	.size	__func__.12181, 24
__func__.12181:
	.string	"AVS2_InterPictureHeader"
	.type	__func__.12318, %object
	.size	__func__.12318, 19
__func__.12318:
	.string	"AVS2_SetupFrameBuf"
	.zero	5
	.type	__func__.12337, %object
	.size	__func__.12337, 19
__func__.12337:
	.string	"AVS2_SetupRefFrame"
	.zero	5
	.type	__func__.12368, %object
	.size	__func__.12368, 17
__func__.12368:
	.string	"AVS2_CalDistance"
	.zero	7
	.type	CSWTCH.73, %object
	.size	CSWTCH.73, 16
CSWTCH.73:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	__func__.12476, %object
	.size	__func__.12476, 19
__func__.12476:
	.string	"AVS2_PrepareDecode"
	.zero	5
	.type	__func__.12493, %object
	.size	__func__.12493, 13
__func__.12493:
	.string	"AVS2DEC_Init"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"AVS2_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x%x\n" )
	.zero	1
.LC7:
	ASCII(.string	"Unkown" )
	.zero	1
.LC9:
	ASCII(.string	"\n" )
	.zero	6
.LC11:
	ASCII(.string	" ----> Dump Dpb Status:\n" )
	.zero	7
.LC14:
	ASCII(.string	"Pic %2d, Type %6s, Occupied %d, Ref %d, Disp %d, DOI %d, POI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x\n" )
	.zero	4
.LC16:
	ASCII(.string	" ----> Dump End: Totoal Occupied Frame %d\n\n" )
	.zero	4
.LC19:
	ASCII(.string	"User Data:\n" )
	.zero	4
.LC22:
	ASCII(.string	"%s: cosume TotalPos(%d > %d)!\n" )
	.zero	1
.LC24:
	ASCII(.string	"Slice num out of slot: %d > %d\n" )
.LC26:
	ASCII(.string	"Stream ERROR: slice_vertical_position %d out of range [0, 0x8F].\n" )
	.zero	6
.LC40:
	ASCII(.string	"Stream ERROR: alf_filter_num_minus1 %d > 15.\n" )
	.zero	2
.LC42:
	ASCII(.string	"ALF ERROR: alf_region_distance %d out of range [1, 15].\n" )
	.zero	7
.LC44:
	ASCII(.string	"ALF ERROR: alf_coef_luma_8 %d out of range [-1088, 1071].\n" )
	.zero	5
.LC46:
	ASCII(.string	"ALF ERROR: alf_coef_luma_%d %d out of range [-64, 63].\n" )
.LC50:
	ASCII(.string	"ALF ERROR: alf_coef_chroma0_8 %d out of range [-1088, 1071].\n" )
	.zero	2
.LC52:
	ASCII(.string	"ALF ERROR: alf_coef_chroma0_%d %d out of range [-64, 63].\n" )
	.zero	5
.LC54:
	ASCII(.string	"ALF ERROR: alf_coef_chroma1_8 %d out of range [-1088, 1071].\n" )
	.zero	2
.LC56:
	ASCII(.string	"ALF ERROR: alf_coef_chroma1_%d %d out of range [-64, 63].\n" )
	.zero	5
.LC59:
	ASCII(.string	"Intra stream ERROR: picture_output_delay out of range [0, 63], force 63.\n" )
	.zero	6
.LC61:
	ASCII(.string	"Intra stream ERROR: force progressive_frame to 0 for field_coded_sequence = 1\n" )
	.zero	1
.LC63:
	ASCII(.string	"Intra stream ERROR: picture_qp %d out of range [0, %d], force %d.\n" )
	.zero	5
.LC65:
	ASCII(.string	"Intra stream ERROR: alpha_c_offset %d out of range [-8, 8], force 0.\n" )
	.zero	2
.LC67:
	ASCII(.string	"Intra stream ERROR: beta_offset %d out of range [-8, 8], force 0.\n" )
	.zero	5
.LC69:
	ASCII(.string	"Intra stream ERROR: chroma_quant_param_delta_cb %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC71:
	ASCII(.string	"Intra stream ERROR: chroma_quant_param_delta_cr %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC74:
	ASCII(.string	"%s call AVS2_alf_parameter_set failed\n" )
	.zero	1
.LC76:
	ASCII(.string	"Inter stream ERROR: picture_coding_type should not equal 0.\n" )
	.zero	3
.LC78:
	ASCII(.string	"Inter stream ERROR: picture_output_delay out of range [0, 63], force 63.\n" )
	.zero	6
.LC81:
	ASCII(.string	"Inter stream ERROR: force progressive_frame to 1 for progressive_sequence = 1\n" )
	.zero	1
.LC83:
	ASCII(.string	"Inter stream ERROR: force progressive_frame to 0 for field_coded_sequence = 1\n" )
	.zero	1
.LC85:
	ASCII(.string	"Inter stream ERROR: picture_qp %d out of range [0, %d], force %d.\n" )
	.zero	5
.LC87:
	ASCII(.string	"Inter stream ERROR: alpha_c_offset %d out of range [-8, 8], force 0.\n" )
	.zero	2
.LC89:
	ASCII(.string	"Inter stream ERROR: beta_offset %d out of range [-8, 8], force 0.\n" )
	.zero	5
.LC91:
	ASCII(.string	"Inter stream ERROR: chroma_quant_param_delta_cb %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC93:
	ASCII(.string	"Inter stream ERROR: chroma_quant_param_delta_cr %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC97:
	ASCII(.string	"%s ERROR: ucRefPicNum out of range [1, %d].\n" )
	.zero	3
.LC99:
	ASCII(.string	"Sequence Header:\n" )
	.zero	6
.LC101:
	ASCII(.string	"Stream ERROR: profile_id 0x%x unsupport.\n" )
	.zero	6
.LC103:
	ASCII(.string	"Stream ERROR: level_id should not equal 0.\n" )
	.zero	4
.LC105:
	ASCII(.string	"Stream ERROR: field_coded_sequence should be 0 when progressive_sequence = 1\n" )
	.zero	2
.LC107:
	ASCII(.string	"Stream ERROR: horizontal_size should not equal 0.\n" )
	.zero	5
.LC109:
	ASCII(.string	"Stream ERROR: vertical_size should not equal 0.\n" )
	.zero	7
.LC111:
	ASCII(.string	"Stream ERROR: chroma_format %d not support, only 4:2:0 now.\n" )
	.zero	3
.LC113:
	ASCII(.string	"Stream ERROR: sample_precision %d should equal to 8/10\n" )
.LC115:
	ASCII(.string	"AVS2 sequence ERROR: ucBitDepth %d should equal to 8/10, and not less than sample_precision %d\n" )
.LC117:
	ASCII(.string	"Stream ERROR: aspect_ratio = 0 is forbidden!\n" )
	.zero	2
.LC119:
	ASCII(.string	"Stream ERROR: frame_rate_code = 0 is forbidden!\n" )
	.zero	7
.LC121:
	ASCII(.string	"Stream ERROR: num_of_rcs %d out of range [0, %d]\n" )
	.zero	6
.LC123:
	ASCII(.string	"MbWidth = %d, MbHeight = %d, don't support!\n" )
	.zero	3
.LC125:
	ASCII(.string	"avs2 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	1
.LC127:
	ASCII(.string	"avs2 actual frame size(%dx%d) exceed max config(%dx%d)\n" )
.LC130:
	ASCII(.string	"ERROR: partition fs memory failed!\n" )
	.zero	4
.LC132:
	ASCII(.string	"ERROR: FSP_ConfigInstance failed!\n" )
	.zero	5
.LC134:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC136:
	ASCII(.string	"ERROR: AVS2_OutputOneFrame is err(%d)\n" )
	.zero	1
.LC138:
	ASCII(.string	"Dump frame, POI: %d\n" )
	.zero	3
.LC140:
	ASCII(.string	"NumOfRemovedPicture: %d\n" )
	.zero	7
.LC142:
	ASCII(.string	"Target removal DOI[%d]: %d\n" )
	.zero	4
.LC144:
	ASCII(.string	"Conflict: cur frame(Type %d, DOI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x) with frame(Type %d, Occupied %d, UsedAsRef %d, DOI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x)\n" )
	.zero	5
.LC147:
	ASCII(.string	"%s: Can't find non-occupied frame memory buffer!!!\n" )
	.zero	4
.LC149:
	ASCII(.string	"%s ERROR: get frame store fail!\n" )
	.zero	7
.LC151:
	ASCII(.string	"%s ERROR: get image pointer fail!\n" )
	.zero	5
.LC153:
	ASCII(.string	"Varify current frame DOI %d failed!\n" )
	.zero	3
.LC157:
	ASCII(.string	"Can't find G or GB picture for the reference of S picture.\n" )
	.zero	4
.LC159:
	ASCII(.string	"CurPic Doi %d cant find ref frame TargetDoi %d\n" )
.LC161:
	ASCII(.string	"Found ref num %d < num_of_reference_picture %d\n" )
.LC164:
	ASCII(.string	"%s ERROR: num_of_reference_picture %d out of range [1, %d].\n" )
	.zero	3
.LC168:
	ASCII(.string	"%s ERROR: pstRefFrmMem[0] = NULL or ucRefPicNum %d out of range [1, %d].\n" )
	.zero	6
.LC171:
	ASCII(.string	"line: %d pImage is null\n" )
	.zero	7
.LC175:
	ASCII(.string	"ERROR: allocate vhb\n" )
	.zero	3
.LC179:
	ASCII(.string	"AVS2_VIDEO_SEQUENCE_END_CODE\n" )
	.zero	2
.LC181:
	ASCII(.string	"AVS2_VIDEO_EDIT_CODE\n" )
	.zero	2
.LC184:
	ASCII(.string	"%s SliceNum %d invalid.\n" )
	.zero	7
.LC186:
	ASCII(.string	"AVS2 unsupport output order %d, force dec order output.\n" )
	.zero	7
.LC190:
	ASCII(.string	"%s get chan id failed!\n" )
.LC194:
	ASCII(.string	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n" )
	.zero	1
.LC196:
	ASCII(.string	"I_PIC" )
	.zero	2
.LC197:
	ASCII(.string	"P_PIC" )
	.zero	2
.LC198:
	ASCII(.string	"B_PIC" )
	.zero	2
.LC199:
	ASCII(.string	"F_PIC" )
	.zero	2
.LC200:
	ASCII(.string	"S_PIC" )
	.zero	2
.LC201:
	ASCII(.string	"G_PIC" )
	.zero	2
.LC202:
	ASCII(.string	"GB_PIC" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
